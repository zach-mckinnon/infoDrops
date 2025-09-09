# InfoDrops Troubleshooting

Simple fixes for common problems.

## 🚨 Quick Checks

**LED Status:**
- **Solid ON**: Working normally
- **Slow Blink**: WiFi running (good)
- **Fast Blink**: Error - check USB connection
- **OFF**: No power or dead battery

**Quick Test:**
1. Check power LED is on
2. Look for "A_Free_Community" WiFi on your phone
3. Connect and see if portal loads
4. If using solar: battery should be >3.2V

## 🔌 Power Problems

**Device Won't Start:**
- Try different USB cable (needs to be data cable, not just charging)
- Try different USB port/power adapter
- Check all connections are tight
- If using solar: make sure battery isn't dead

**Battery Dies Too Fast:**
- Cold weather reduces battery life
- Old batteries (>2 years) need replacing
- Make sure solar panel gets sun and isn't blocked

## 📶 WiFi Problems

**WiFi Network Not Showing Up:**
- If using light sensor: make sure it's bright enough (daytime)
- Move away from other WiFi networks
- Make sure device isn't blocked by metal objects
- Try restarting the device

**Can't Connect to Portal:**
- Try going directly to 192.168.4.1 in your browser
- Clear browser cache or try private browsing
- On iPhone: Go to Settings > WiFi > network name > "Login to Network"
- On Android: Look for "Sign in to network" notification

**Short WiFi Range:**
- Keep device away from metal objects
- Mount higher up if possible
- Trees and walls block the signal

## 📄 Content Problems

**Web Pages Not Loading:**
- Re-upload files: `pio run -t uploadfs`
- Make sure all files are in the `data/` folder
- Check that file paths start with "/" 

**Website/JavaScript Not Working:**
- Press F12 in browser to see errors
- Make sure `minimal.css` is uploaded
- Try different browsers
- Clear browser cache

## 🔧 Programming Problems

**Code Won't Upload:**
- Try different USB cable (must be data cable, not charge-only)
- Try different USB port
- Hold BOOT button, press RESET, release both
- Install ESP32 drivers if on Windows

**Compilation Errors:**
- Install missing libraries with `pio lib install`
- Check that all files are spelled correctly
- If "out of memory" error, the code is too big

**Can't See Serial Output:**
- Make sure baud rate is 115200
- Use `pio device list` to find the right port

## 🌡️ Weather Issues

**Cold Weather:**
- Battery life drops 20-40% in freezing temps
- Use bigger battery for winter deployments

**Hot Weather:**
- Don't let battery get too hot (dangerous)
- Make sure electronics get shade but solar panel gets sun

**Rain/Moisture:**
- Use waterproof enclosure (IP65 rated)
- Add moisture absorption packets inside

## 🆘 When Nothing Works

**Complete Reset:**
- Run `pio run -t erase` then `pio run -t upload`
- Disconnect all power for 30 seconds, then reconnect
- If still broken, probably hardware failure

## 📞 Getting Help

- Check the GitHub repository for similar issues
- Ask on r/esp32 subreddit
- Local makerspaces usually have someone who knows electronics

**When asking for help, include:**
- What ESP32-C3 board you have
- Complete error messages
- Photos of your wiring setup

---

*When you fix something, share the solution to help others.*
