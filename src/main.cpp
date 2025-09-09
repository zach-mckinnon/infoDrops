#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <FS.h>
#include <SPIFFS.h>

// --- Configuration Options ---
// Set to 'true' to use the LDR for power saving (e.g., outdoor deployment).
// Set to 'false' to run continuously when powered by USB.

#define USE_LIGHT_SENSOR false

#if USE_LIGHT_SENSOR
#define LDR_PIN A2
#define LIGHT_THRESHOLD 1800 // Adjust based on your LDR and environment
#endif

#define WIFI_NAME "A_Free_Community"

bool portalActive = false;
unsigned long visitCount = 0;

WebServer server(80);
DNSServer dnsServer;

void handleRoot()
{
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.sendHeader("Content-Security-Policy", "default-src 'self' 'unsafe-inline'");
  server.sendHeader("X-Frame-Options", "DENY");
  server.sendHeader("X-Content-Type-Options", "nosniff");

  File file = SPIFFS.open("/index.html", "r");
  if (file)
  {
    server.streamFile(file, "text/html");
    file.close();
  }
  else
  {
    server.send(200, "text/html",
                "<!DOCTYPE html><html><head><title>Community Information</title></head>"
                "<body><h1>Free Community Information</h1>"
                "<p>Welcome to your community information beacon!</p></body></html>");
  }
}

void handleRedirect()
{
  handleRoot();
}

void handleCaptiveDetection()
{
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.send(200, "text/html", "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='0; url=http://" + WiFi.softAPIP().toString() + "/'></head><body>Redirecting...</body></html>");
}

void handleGenerate204()
{
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
  server.send(302, "text/plain", "");
}

void handleMicrosoftNCSI()
{
  server.send(200, "text/plain", "Microsoft NCSI");
}

void handleConnectTest()
{
  server.send(200, "text/plain", "Microsoft Connect Test");
}

void handleAppleCaptive()
{
  server.send(200, "text/plain", "Success");
}

void handleNotFound()
{
  handleRoot();
}

void startCaptivePortal()
{
  Serial.println("Setting WiFi mode to AP...");
  WiFi.mode(WIFI_AP);

  IPAddress local_IP(172, 0, 0, 1);
  IPAddress gateway(172, 0, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  Serial.println("Configuring AP IP address...");
  WiFi.softAPConfig(local_IP, gateway, subnet);

  Serial.println("Starting WiFi Access Point...");

  bool apStarted = WiFi.softAP(WIFI_NAME, "", 1, 0, 4);

  if (apStarted)
  {
    Serial.println("WiFi AP started successfully!");
  }
  else
  {
    Serial.println("ERROR: Failed to start WiFi AP!");
    return;
  }

  delay(2000);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/generate_204", []()
            {
              server.send(204, "text/plain", ""); // Android expects 204 No Content
            });
  server.on("/gen_204", []()
            {
              server.send(204, "text/plain", ""); // Android alternative
            });
  server.on("/hotspot-detect.html", []()
            {
    // iOS expects a redirect or non-"Success" response to trigger captive portal
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/", true);
    server.send(302, "text/html", ""); });

  // Additional iOS endpoints
  server.on("/library/test/success.html", []()
            {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/", true);
    server.send(302, "text/html", ""); });
  server.on("/ncsi.txt", []()
            {
              server.send(200, "text/plain", "Microsoft NCSI"); // Windows
            });
  server.on("/connecttest.txt", []()
            {
              server.send(200, "text/plain", "Microsoft Connect Test"); // Windows 10
            });

  // iOS success endpoint - when user completes captive portal
  server.on("/success", []()
            { server.send(200, "text/html",
                          "<!DOCTYPE html><html><head><title>Connected</title></head>"
                          "<body><h1>Successfully Connected!</h1>"
                          "<p>You can now close this page and use the internet.</p></body></html>"); });

  // Serve CSS file
  server.on("/minimal.css", HTTP_GET, []() {
    server.sendHeader("Cache-Control", "public, max-age=3600");
    server.sendHeader("Content-Type", "text/css");
    
    File file = SPIFFS.open("/minimal.css", "r");
    if (file) {
      server.streamFile(file, "text/css");
      file.close();
    } else {
      server.send(404, "text/plain", "CSS file not found");
    }
  });

  // Visit counter endpoint
  server.on("/visit", HTTP_GET, []() {
    visitCount++;
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Content-Type", "text/plain");
    server.send(200, "text/plain", String(visitCount));
  });


  // Main portal pages
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleRoot); // Catch everything else and serve the portal

  dnsServer.start(53, "*", WiFi.softAPIP());

  server.begin();
  Serial.println("Captive Portal started...");
}

void enterDeepSleep()
{
  Serial.println("Entering deep sleep...");
  esp_sleep_enable_timer_wakeup(45 * 60 * 1000000); // Wake up after 45 minutes
  esp_deep_sleep_start();
}

void setup()
{
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 5; i++)
  {
    Serial.println("=== ESP32-C3 ALIVE TEST ===");
    Serial.print("Boot attempt: ");
    Serial.println(i + 1);
    delay(1000);
  }

  Serial.println("ESP32-C3 Community Beacon Starting...");

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS mount failed!");
    return;
  }

#if USE_LIGHT_SENSOR
  pinMode(LDR_PIN, INPUT);
  Serial.println("LDR mode enabled. Checking light levels...");
  int lightValue = analogRead(LDR_PIN);
  Serial.printf("LDR value: %d (threshold: %d)\n", lightValue, LIGHT_THRESHOLD);

  if (lightValue > LIGHT_THRESHOLD)
  {
    Serial.println("Light detected... starting captive portal");
    startCaptivePortal();
    portalActive = true;
    Serial.println("Portal started");
  }
  else
  {
    Serial.println("Not enough light, going to sleep");
    enterDeepSleep();
  }
#else
  Serial.println("Starting captive portal");
  startCaptivePortal();
  portalActive = true;
  Serial.println("Portal started - will run continuously...");
#endif
}

void loop()
{
  if (portalActive)
  {
    dnsServer.processNextRequest();
    server.handleClient();

#if USE_LIGHT_SENSOR
    // Check light levels periodically to conserve power during darkness
    static unsigned long lastLightCheck = 0;
    if (millis() - lastLightCheck >= 60000)
    { // Check every minute
      int lightValue = analogRead(LDR_PIN);
      if (lightValue < LIGHT_THRESHOLD)
      {
        Serial.println("Light level dropped - shutting down portal for power conservation");
        portalActive = false;
        WiFi.mode(WIFI_OFF);
        enterDeepSleep();
      }
      lastLightCheck = millis();
    }
#endif

    static unsigned long lastStatusPrint = 0;
    if (millis() - lastStatusPrint >= 1800000)
    {
      Serial.printf("Portal running - uptime: %lu minutes\n", millis() / 60000);
#if USE_LIGHT_SENSOR
      Serial.printf("Current light level: %d\n", analogRead(LDR_PIN));
#endif
      lastStatusPrint = millis();
    }
  }
}