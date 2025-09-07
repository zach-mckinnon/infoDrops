# InfoDrops: A Community Information Beacon

A discrete, solar-powered device for sharing critical information when the internet isn't an option.

---

## ⚠️ Important Legal and Ethical Notice

**This project is for educational and legitimate resistance purposes only.** Its goal is to provide access to information during emergencies, connectivity outages, or periods of information suppression.

**Your Responsibilities:**

1. **Comply with local laws.** You are solely responsible for how you use this device.
2. **Use for peaceful purposes only.** This tool is for sharing information, not inciting violence.
3. **Respect property.** Do not deploy on private property without permission.
4. **Prioritize safety.** Never deploy a device if it puts you or your community at risk.

## 🎯 Mission

To empower communities with access to vital, offline information during a crisis. InfoDrops creates a network of discrete, solar-powered beacons to support **democratic education**, **community organizing**, **emergency preparedness**, and **digital rights**.

## 🔧 How It Works

Think of an InfoDrop as a tiny, digital lighthouse. It requires no internet connection. When you're nearby, you connect to its free Wi-Fi, and a webpage automatically opens on your phone with the stored information.

- **The Device**: A tiny, low-power `ESP32-C3` microcontroller creates a local Wi-Fi network.
- **The Portal**: This network uses a **captive portal**—the same technology hotels and airports use for Wi-Fi logins—to automatically direct your phone's browser to the locally-stored content.
- **The Power**: It can be powered by a simple USB power bank for portable use or a small solar panel for long-term, autonomous deployment.

## 🚀 Quick Start Guide

### 1. Hardware Required

| Component                  | Portable Setup (Basic) | Deployed Setup (Advanced) | Purpose                                      |
| -------------------------- | :--------------------: | :-----------------------: | -------------------------------------------- |
| **ESP32-C3 SuperMini**     |      **Required**      |       **Required**        | The brain of the device.                     |
| **USB-C Power Bank**       |      **Required**      |         Optional          | Easy, portable power source.                 |
| **Solar Panel & Battery**  |           -            |       **Required**        | For long-term, autonomous operation.         |
| **Light Sensor (LDR)**     |           -            |         Optional          | Activates device only during daylight hours. |
| **Weatherproof Enclosure** |           -            |         Optional          | Protects the device when installed outdoors. |

### 2. Software Setup

1. **Install** the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode) in VS Code.
2. **Clone** this project's repository to your computer.
3. **Upload Filesystem Image**: This step loads the web portal content (`index.html`, `style.css`, etc.) onto the device's memory.
4. **Compile & Upload Firmware**: This step loads the main program code onto the device.
5. **Activate**: Power on the device. It will begin broadcasting a Wi-Fi network named **"A_Free_Community"**.

## 📱 Usage Modes

You can use the device in two primary ways. Choose your mode by editing the `main.cpp` file before uploading the firmware.

| Mode          | Portable Mode (`USE_LIGHT_SENSOR = false`)                         | Deployed Mode (`USE_LIGHT_SENSOR = true`)                                  |
| ------------- | ------------------------------------------------------------------ | -------------------------------------------------------------------------- |
| **Purpose**   | Temporary info sharing at events, meetings, or protests.           | Long-term, autonomous installations in public spaces.                      |
| **Power**     | USB power bank.                                                    | Solar panel and battery.                                                   |
| **Operation** | Runs continuously as long as it has power.                         | Activates automatically in daylight and sleeps at night to conserve power. |
| **Hardware**  | Just the ESP32-C3 and a power bank.                                | Requires a solar setup and an optional light sensor (LDR).                 |
| **Best For**  | Quick, mobile deployment where you can retrieve the device easily. | "Set it and forget it" deployments in a stable, secure location.           |

## ⚖️ Safety & Legal Considerations

- **Public vs. Private Space**: Operating low-power Wi-Fi in public spaces is generally permissible, but always check local regulations. **Obtain permission for placement on private property.**
- **Operational Security (OpSec)**: For sensitive deployments, consider anonymous hardware purchases and take precautions to protect your identity.
- **Content is Key**: The default content focuses on legal resistance methods and educational resources. You are responsible for any content you add or modify. Ensure it complies with local laws and serves your community constructively.
- **No User Tracking**: The device is designed for privacy. It **does not log IP addresses or track user activity**.

## 🛠️ Customization

1. **Edit Content**: Modify the files in the `data/` folder. The main page is `index.html`.
2. **Change Styles**: Customize the look and feel by editing `data/minimal.css`.
3. **Add Files**: Add images, PDFs, and other resources into the `data/` folder. Remember to update the filesystem image after making changes.

## 🌍 Use Cases

| Category                 | Examples                                                                            |
| ------------------------ | ----------------------------------------------------------------------------------- |
| **Crisis Response**      | Emergency contacts, shelter locations, safety guides during natural disasters.      |
| **Community Organizing** | Mutual aid resources, voter guides, schedules for local meetings.                   |
| **Educational Outreach** | Digital privacy tools, civic education, historical documents.                       |
| **Information Access**   | A backup communication channel during internet blackouts or infrastructure failure. |

## ⚡ Technical Specifications

| Feature               | Specification                                  |
| --------------------- | ---------------------------------------------- |
| **Power Consumption** | ~80mA (Active), <1µA (Deep Sleep)              |
| **WiFi Standard**     | 802.11 b/g/n (2.4GHz)                          |
| **WiFi Range**        | ~50-100 meters (line of sight)                 |
| **Concurrent Users**  | Up to 4 recommended                            |
| **Content Storage**   | ~2MB available for HTML, CSS, images, and PDFs |

## 🤝 How to Contribute

We welcome contributions! You can help by:

- **Developing Content**: Create educational materials or translate existing ones.
- **Improving Code**: Optimize the software or add new features.
- **Writing Documentation**: Improve setup guides and safety protocols.
- **Testing**: Report bugs and validate functionality.

Please see our contribution guidelines for details on submitting a pull request.

## 📄 License

This project is released under the **GNU General Public License v3.0**.

**Disclaimer**: This software is provided "as is" without warranty. The developers are not liable for any misuse. You are responsible for using this tool ethically, legally, and safely.

---

> _The price of liberty is eternal vigilance. In the digital age, that vigilance includes ensuring our communities have access to the information and tools they need to resist authoritarianism and build stronger, more connected societies._

**Stay informed. Stay connected. Stay free.**
