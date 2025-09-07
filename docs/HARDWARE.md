# InfoDrops Hardware Assembly Guide

This guide provides complete instructions for building an InfoDrops device. The design is simple, low-cost, and reliable, making it perfect for both beginners and experienced makers.

## 🎯 Design Philosophy

- **Compact & Discreet**: Small enough to fit in a standard weatherproof junction box.
- **Flexible Power**: Works with a simple USB power bank **(Portable Mode)** or a self-sustaining solar power system **(Deployed Mode)**.
- **Smart Operation**: An optional light sensor allows the device to activate only during the day, saving power.
- **Low Cost**: The basic portable version can be built for under $15, with the full solar-powered version costing around $20-$30.

---

## ✅ The Core Component: ESP32-C3 SuperMini

We chose the ESP32-C3 SuperMini board as the brain of this project for a few key reasons:

- **Tiny Size**: Its small footprint (22.5mm x 18mm) is perfect for a discreet device.
- **Built-in Wi-Fi & Bluetooth**: Everything needed for connectivity is on the board.
- **Extremely Low Power**: Its deep sleep mode uses a tiny amount of power (\~43µA), which is **essential for solar-powered applications**.
- **Modern Port**: It uses a **USB-C** connector for power and programming.

---

## 📋 Bill of Materials (BOM)

This table lists all the parts you might need. The **"Mode"** column tells you which build requires the part.

| Component              | Specification                         | Mode                | Est. Cost |
| :--------------------- | :------------------------------------ | :------------------ | :-------: |
| **ESP32-C3 SuperMini** | Development board with USB-C          | Portable & Deployed |  $2 - $4  |
| **USB Power Bank**     | Any type, 5000mAh+ recommended        | Portable Only       | $5 - $10  |
| **Solar Panel**        | 6V, 1-2W                              | Deployed Only       | $8 - $12  |
| **Charge Controller**  | TP4056 module with battery protection | Deployed Only       |  $1 - $2  |
| **Li-ion Battery**     | 18650, 3000mAh, **protected cell**    | Deployed Only       |  $5 - $8  |
| **Battery Holder**     | 18650 holder with wires               | Deployed Only       |    $1     |
| **Diode**              | 1N4007 Rectifier Diode                | Deployed Only       |   $0.10   |
| _Light Sensor (LDR)_   | 5mm photoresistor                     | Deployed (Optional) |   $0.10   |
| _Resistor_             | 10kΩ, 1/4W                            | Deployed (Optional) |   $0.05   |

**Total Estimated Cost:**

- **Portable Mode:** \~$7 - $14
- **Deployed Mode (Full Solar):** \~$20 - $30

---

## 🔧 Assembly Instructions

### Option 1: Portable Mode (5 Minutes)

This mode is perfect for events and temporary use. No soldering or assembly is required\!

1. **Configure Firmware**: Make sure `USE_LIGHT_SENSOR` is set to `false` in the code.
2. **Connect Power**: Plug the ESP32-C3 into your USB power bank using a USB-C cable.
3. **Done\!**: The device will run as long as the power bank has a charge.

### Option 2: Deployed Mode (1-2 Hours)

This build creates a self-sufficient, solar-powered beacon that can run indefinitely.

**Required Tools**: Soldering iron, wire strippers, and a multimeter for testing.

#### **Circuit Diagram**

This diagram shows how the light sensor and solar power system connect to the ESP32.

- **Solar Power Circuit**: `Solar Panel` ➔ `TP4056 (IN)` ➔ `TP4056 (B)` connects to `Battery` ➔ `TP4056 (OUT)` ➔ `Diode` ➔ `ESP32 (VIN)`
- **Light Sensor Circuit**: `ESP32 (3V3)` ➔ `LDR` ➔ `ESP32 (A2)` ➔ `10kΩ Resistor` ➔ `ESP32 (GND)`

#### **Step 1: Build the Solar Power System**

This circuit safely charges the battery from the sun and powers the ESP32.

1. **Connect the Solar Panel**: Solder the panel's positive (red) and negative (black) wires to the `IN+` and `IN-` pads on the TP4056 charge controller.
2. **Connect the Battery Holder**: Solder the holder's wires to the `B+` and `B-` pads on the TP4056. **Check polarity carefully\!**
3. **Connect the Output to the ESP32**:
   - Solder the **diode** to the `OUT+` pad on the TP4056. The end of the diode with the silver stripe should point away from the board.
   - Solder a wire from the other end of the diode (the striped end) to the **`VIN`** pin on the ESP32.
   - Solder a wire from the `OUT-` pad on the TP4056 to any **`GND`** pin on the ESP32.

> **Why the diode?** The 1N4007 diode acts like a one-way valve. It prevents the battery's power from flowing backward into the solar panel at night, which would waste energy.

#### **Step 2: Add the Light Sensor (Optional)**

This circuit allows the ESP32 to know if it's daytime or nighttime.

1. Solder one leg of the **LDR** (light-dependent resistor) to the **`3V3`** pin on the ESP32.
2. Solder the other leg of the LDR to the **`A2`** pin.
3. Solder the **10kΩ resistor** between the **`A2`** pin and a **`GND`** pin.

#### **Step 3: Prepare the Enclosure**

A weatherproof enclosure (like a small electrical junction box) is crucial for outdoor deployment.

1. **Plan Layout**: Arrange the components inside the box, ensuring the Wi-Fi antenna on the ESP32 is not blocked by the battery or other metal parts.
2. **Mount Components**: Use double-sided tape or hot glue to secure the battery holder, TP4056, and ESP32.
3. **Expose Sensors**: Drill a small, sealed hole for the LDR to see outside, or mount it behind a clear part of the enclosure. The solar panel will be mounted on the outside.
4. **Weatherproof**: Use silica gel packets inside to absorb moisture and ensure all openings are sealed against rain.

---

## ⚡ Power & Battery Life

The combination of the ESP32's deep sleep mode and a solar panel allows for extremely long run times.

| Operating Mode  | Current Draw | Purpose                                  |
| :-------------- | :----------- | :--------------------------------------- |
| **Active Mode** | \~80mA       | Serving the web portal to users.         |
| **Deep Sleep**  | **\~43µA**   | Conserving power during nighttime hours. |

**Expected Performance (with 3000mAh battery):**

- **No Sun**: The battery alone can run the device for **3-4 days** of typical use (8 hours active, 16 hours sleep).
- **With Sun**: A 1-2W solar panel receiving **4-6 hours of sun** per day should be enough to run the device indefinitely.
