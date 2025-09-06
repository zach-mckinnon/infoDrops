#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <FS.h>
#include <SPIFFS.h>

#define LDR_PIN A2  // Use GPIO 2 (A2) - safe analog pin on ESP32-C3
#define LIGHT_THRESHOLD 1800
// No timeout - run continuously during daylight hours

bool portalActive = false;

WebServer server(80);
DNSServer dnsServer;

void handleRoot()
{
  // Add headers to prevent HTTPS redirect and caching issues + iOS-specific headers
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.sendHeader("Content-Security-Policy", "default-src 'self' 'unsafe-inline'");
  server.sendHeader("X-Frame-Options", "DENY");
  server.sendHeader("X-Content-Type-Options", "nosniff");
  
  File file = SPIFFS.open("/index.html", "r");
  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  } else {
    // Fallback if SPIFFS fails
    server.send(200, "text/html", 
      "<!DOCTYPE html><html><head><title>Community Information</title></head>"
      "<body><h1>Free Community Information</h1>"
      "<p>Welcome to your community information beacon!</p></body></html>");
  }
}

void handleRedirect()
{
  handleRoot(); // Direct to content instead of redirect
}

void handleCaptiveDetection()
{
  // Force HTTP and prevent HTTPS upgrades that break Android detection
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.send(200, "text/html", "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='0; url=http://" + WiFi.softAPIP().toString() + "/'></head><body>Redirecting...</body></html>");
}

void handleGenerate204()
{
  // Android captive portal detection - must return 204 or redirect to trigger portal
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
  server.send(302, "text/plain", "");
}

void handleMicrosoftNCSI()
{
  // Microsoft NCSI expects specific response
  server.send(200, "text/plain", "Microsoft NCSI");
}

void handleConnectTest()
{
  // Windows 10 connectivity check
  server.send(200, "text/plain", "Microsoft Connect Test");
}

void handleAppleCaptive()
{
  // Apple devices check this URL - must return "Success" for internet detection
  server.send(200, "text/plain", "Success");
}

void handleNotFound()
{
  handleRoot(); // default to index.html
}

void startCaptivePortal()
{
  Serial.println("Setting WiFi mode to AP...");
  WiFi.mode(WIFI_AP);
  
  // Use proven IP configuration from m5stick-nemo - MUST be before softAP()
  IPAddress local_IP(172, 0, 0, 1);   // Proven working IP
  IPAddress gateway(172, 0, 0, 1);    // Same as local IP
  IPAddress subnet(255, 255, 255, 0);
  Serial.println("Configuring AP IP address...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  
  Serial.println("Starting WiFi Access Point...");
  bool apStarted = WiFi.softAP("A_Free_Community", "", 1, 0, 4); // Channel 1, no password, max 4 clients
  
  if (apStarted) {
    Serial.println("WiFi AP started successfully!");
  } else {
    Serial.println("ERROR: Failed to start WiFi AP!");
    return;
  }

  // Delay for stability
  delay(2000);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Device-specific detection URLs that MUST return specific responses
  server.on("/generate_204", []() {
    server.send(204, "text/plain", "");  // Android expects 204 No Content
  });
  server.on("/gen_204", []() {
    server.send(204, "text/plain", "");  // Android alternative
  });
  server.on("/hotspot-detect.html", []() {
    // iOS expects a redirect or non-"Success" response to trigger captive portal
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/", true);
    server.send(302, "text/html", "");
  });
  
  // Additional iOS endpoints
  server.on("/library/test/success.html", []() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/", true);
    server.send(302, "text/html", "");
  });
  server.on("/ncsi.txt", []() {
    server.send(200, "text/plain", "Microsoft NCSI");  // Windows
  });
  server.on("/connecttest.txt", []() {
    server.send(200, "text/plain", "Microsoft Connect Test");  // Windows 10
  });
  
  // iOS success endpoint - when user completes captive portal
  server.on("/success", []() {
    server.send(200, "text/html", 
      "<!DOCTYPE html><html><head><title>Connected</title></head>"
      "<body><h1>Successfully Connected!</h1>"
      "<p>You can now close this page and use the internet.</p></body></html>");
  });
  
  // Main portal pages
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleRoot);  // Catch everything else and serve the portal

  // Start DNS server exactly like m5stick-nemo - simple and proven
  dnsServer.start(53, "*", WiFi.softAPIP());

  server.begin();
  Serial.println("Captive Portal started with enhanced DNS redirection");
}

void enterDeepSleep()
{
  Serial.println("Entering deep sleep...");
  esp_sleep_enable_timer_wakeup(15 * 60 * 1000000); // Wake up after 15 minutes
  esp_deep_sleep_start();
}

void setup()
{
  Serial.begin(115200);
  delay(3000); // Longer delay for USB-CDC
  
  // Basic connectivity test
  for(int i = 0; i < 5; i++) {
    Serial.println("=== ESP32-C3 ALIVE TEST ===");
    Serial.print("Boot attempt: ");
    Serial.println(i + 1);
    delay(1000);
  }
  
  Serial.println("ESP32-C3 Community Beacon Starting...");

  pinMode(LDR_PIN, INPUT);
  Serial.println("LDR pin configured");
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS mount failed!");
    return;
  }

  int lightValue = analogRead(LDR_PIN);
  Serial.printf("LDR value: %d (threshold: %d)\n", lightValue, LIGHT_THRESHOLD);

  if (lightValue > LIGHT_THRESHOLD)
  {
    Serial.println("Light detected - starting captive portal...");
    startCaptivePortal();
    portalActive = true;
    Serial.println("Portal started - will run continuously during daylight hours...");
  }
  else
  {
    Serial.println("Not enough light - going to sleep");
    enterDeepSleep();
  }
}

void loop()
{
  if (portalActive) {
    // Process DNS and web server requests
    dnsServer.processNextRequest();
    server.handleClient();
    
    // Check light levels periodically to conserve power during darkness
    static unsigned long lastLightCheck = 0;
    if (millis() - lastLightCheck >= 60000) {  // Check every minute
      int lightValue = analogRead(LDR_PIN);
      if (lightValue < LIGHT_THRESHOLD) {
        Serial.println("Light level dropped - shutting down portal for power conservation");
        portalActive = false;
        WiFi.mode(WIFI_OFF);
        enterDeepSleep();
      }
      lastLightCheck = millis();
    }
    
    // Print status every 30 minutes during operation
    static unsigned long lastStatusPrint = 0;
    if (millis() - lastStatusPrint >= 1800000) {  // 30 minutes
      Serial.printf("Portal running continuously - uptime: %lu minutes\n", millis() / 60000);
      Serial.printf("Current light level: %d\n", analogRead(LDR_PIN));
      lastStatusPrint = millis();
    }
  }
}
