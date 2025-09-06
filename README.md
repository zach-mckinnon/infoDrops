# InfoDrops: Community Information Beacon

A discrete, solar-powered device for sharing critical information in communities facing information suppression or during emergencies.

## ⚠️ Important Legal and Ethical Notice

**This project is designed for educational and legitimate resistance purposes only.** It is intended to help communities access critical information during times of:

- Natural disasters or emergencies
- Information suppression by authoritarian regimes
- Limited internet access situations
- Community organizing and mutual aid efforts

**Users must:**

- Comply with all local laws and regulations
- Use only for peaceful, non-violent resistance
- Respect others' rights and property
- Consider the safety of themselves and their community

## 🎯 Mission Statement

InfoDrops empowers communities to maintain access to vital information during times of crisis or information suppression. By creating a network of discrete, solar-powered information beacons, we enable:

- **Democratic Education**: Access to resources about recognizing and resisting authoritarianism
- **Community Building**: Tools and information for organizing mutual aid networks
- **Emergency Preparedness**: Critical resources during natural disasters or connectivity outages
- **Digital Rights**: Education about privacy protection and digital security

## 🔧 How It Works

### The Device

- **ESP32-C3 SuperMini**: Ultra-compact microcontroller with WiFi capabilities
- **Light-Activated**: Device activates only when exposed to sufficient light (flashlight, sunlight)
- **Captive Portal**: Creates a free WiFi network that automatically opens the information portal
- **Solar Powered**: Can be paired with small solar panels for autonomous operation
- **Discrete**: Small form factor allows for inconspicuous placement

### The Portal

- **Offline Operation**: All content stored locally, no internet required
- **Mobile Optimized**: Responsive design works perfectly on smartphones

## 🚀 Quick Start Guide

### Hardware Required

- ESP32-C3 SuperMini development board
- Light-dependent resistor (LDR) connected to GPIO A2
- Optional: Small solar panel and battery for autonomous operation
- Enclosure for weather protection (if deploying outdoors)

### Software Setup

1. Install PlatformIO in VS Code
2. Clone this repository
3. Upload the filesystem image (contains the web portal)
4. Compile and upload the firmware
5. Device will create "A_Free_Community" WiFi network when activated

### Deployment

1. **Test First**: Verify operation in a safe, controlled environment
2. **Choose Location**: Consider foot traffic, safety, and legal implications
3. **Power Source**: Use battery pack or small solar panel for remote deployment
4. **Monitor**: Check device periodically for functionality and safety

## ⚖️ Legal and Safety Considerations

### Legal Framework

- **Public Spaces**: Generally legal to operate low-power WiFi in public areas
- **Private Property**: Obtain permission before placement
- **Broadcasting Laws**: Complies with standard WiFi regulations (2.4GHz unlicensed band)
- **Content Laws**: Default content focuses on education and legal resistance methods

### Safety Guidelines

- **Personal Safety**: Never deploy if it puts you or others at risk
- **Operational Security**: Consider using anonymous hardware purchases and deployment
- **Content Review**: Customize content to ensure compliance with local laws
- **Community Impact**: Ensure deployment serves and doesn't endanger the community

### Risk Mitigation

- Device runs continuously during daylight hours, automatically entering sleep mode at night
- Light activation prevents accidental operation
- No logging or tracking of users
- Can be quickly retrieved if necessary

## 🛠️ Customization Guide

### Modifying Content

1. Edit files in the `data/` folder
2. **HTML**: `data/index.html` contains the main portal content
3. **Styling**: `data/minimal.css` for visual customization
4. **Assets**: Add images, documents, or other resources to `data/`

### Hardware Modifications

- **Solar Power**: Connect small solar panel through charge controller
- **Extended Battery**: Use larger battery for longer operation
- **Environmental Sensing**: Add temperature, humidity, or other sensors
- **Security**: Add tamper detection or self-destruct capabilities

### Deployment Variations

- **Event Support**: Provide information during protests or gatherings
- **Emergency Response**: Deploy during natural disasters for critical info
- **Community Centers**: Permanent installation in libraries, cafes, community spaces
- **Mobile Units**: Portable versions for rapid deployment

## 🌍 Use Cases and Applications

### Crisis Response

- **Information Blackouts**: Maintain access to news and resources
- **Natural Disasters**: Emergency contact info, shelter locations, safety guidelines
- **Infrastructure Failures**: Communications backup during network outages

### Community Organizing

- **Mutual Aid Networks**: Resource sharing and community support information
- **Local Politics**: Voter guides, candidate information, meeting schedules
- **Skills Sharing**: Community workshops, tool libraries, skill exchanges

### Educational Outreach

- **Digital Literacy**: Privacy tools, security practices, media literacy
- **Civic Education**: Democratic processes, rights awareness, legal resources
- **Historical Context**: Documentation of authoritarianism and resistance movements

## 🔒 Privacy and Security

### User Privacy

- **No Tracking**: Device doesn't log IP addresses or user activity
- **Anonymous Access**: No registration or personal information required
- **Local Operation**: All content served locally, no external connections

### Device Security

- **Minimal Attack Surface**: Simple, focused functionality
- **Open Source**: All code available for security review
- **Physical Security**: Designed for discreet deployment and easy retrieval

## 🤝 Contributing

This project welcomes contributions from developers, activists, educators, and community organizers.

### How to Help

- **Content Development**: Create educational materials, translations
- **Technical Improvements**: Enhance hardware design, optimize software
- **Documentation**: Improve setup guides, safety protocols
- **Testing**: Validate functionality in different environments
- **Community Outreach**: Share knowledge, provide feedback

### Contribution Guidelines

1. Fork the repository
2. Create a feature branch
3. Make your changes with clear commit messages
4. Test thoroughly
5. Submit a pull request with detailed description

## 📚 Additional Resources

### Technical Documentation

- [Hardware Assembly Guide](HARDWARE.md)
- [Software Configuration](docs/SOFTWARE.md)
- [Deployment Best Practices](docs/DEPLOYMENT.md)
- [Troubleshooting Guide](docs/TROUBLESHOOTING.md)

## ⚡ Technical Specifications

### Power Consumption

- **Active Mode**: ~80mA @ 3.3V (WiFi + web server)
- **Sleep Mode**: <1µA (deep sleep between activations)
- **Battery Life**: 8-12 hours on 2000mAh battery (active use)
- **Solar Requirements**: 1-2W panel sufficient for daily operation

### Network Specifications

- **WiFi Standard**: 802.11 b/g/n (2.4GHz)
- **Network Name**: "A_Free_Community" (customizable)
- **Captive Portal**: Automatic redirect to information page
- **Range**: 50-100 meters typical (varies by environment)
- **Concurrent Users**: Up to 4 simultaneous connections

### Content Capacity

- **Flash Memory**: 4MB total (2MB available for content)
- **Current Usage**: ~220KB (room for significant expansion)
- **Supported Formats**: HTML, CSS, JS, images (PNG, JPG), documents (PDF)

## 🔄 Version History

### v1.0 (Current)

- ESP32-C3 SuperMini support
- Light-activated operation
- Mobile-optimized portal
- Continuous daylight operation with automatic nighttime sleep

### Support Contacts

- **Technical Issues**: [Create GitHub Issue](https://github.com/user/infodrops/issues)

## 📄 License and Disclaimer

This project is released under the GNU General Public License v3.0. See [LICENSE](LICENSE) for details.

**Disclaimer**: This software is provided "as is" without warranty. Users are responsible for complying with applicable laws and ensuring safe, ethical use. The developers are not liable for any misuse or consequences of deployment.

---

_The price of liberty is eternal vigilance. In the digital age, that vigilance includes ensuring our communities have access to the information and tools they need to resist authoritarianism and build stronger, more connected societies._

**Stay informed. Stay connected. Stay free.**
