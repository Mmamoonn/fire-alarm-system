# 🔥 Fire Alarm System

A fire/smoke detection alarm system implemented in **two ways** — a purely analog transistor-based hardware circuit, and a digital Arduino-based simulation on Autodesk Tinkercad using a gas sensor. Both approaches achieve the same goal: detect smoke/fire and trigger an alarm with visual and audio indicators.

---

## 📁 Repository Structure

```
fire-alarm-system/
│
├── analog/                          ← Transistor-based analog hardware
│   ├── hardware-photos/
│   │   ├── hardware_build.jpeg      ← Circuit build photo
│   │   └── hardware_working.jpeg    ← Circuit in operation (LED ON)
│   └── README.md                    ← Analog implementation details
│
├── arduino-simulation/              ← Arduino + Gas Sensor (Tinkercad)
│   ├── src/
│   │   └── fire_alarm.ino           ← Arduino sketch
│   ├── simulation/
│   │   └── tinkercad_simulation.png ← Tinkercad screenshot
│   └── README.md                    ← Simulation implementation details
│
├── README.md                        ← You are here
├── TROUBLESHOOTING.md               ← Combined troubleshooting guide
└── LICENSE
```

---

## 🔀 Two Implementations at a Glance

| Feature | Analog (Transistor) | Arduino (Tinkercad) |
|--------|---------------------|---------------------|
| Controller | No MCU — pure transistor logic | Arduino UNO |
| Sensor | IR / Light-dependent sensor | MQ-2 Gas Sensor |
| Alarm | Buzzer | Buzzer |
| Indicator | Blue LED | Red & Green LEDs |
| Display | None | 16x2 LCD |
| Platform | Real breadboard hardware | Autodesk Tinkercad |
| Complexity | Simple, low-cost | Programmable, flexible |

---

## 🧭 Navigate to Each Implementation

- 👉 [Analog Transistor-Based Implementation](analog/README.md)
- 👉 [Arduino Simulation (Tinkercad)](arduino-simulation/README.md)

---

## 📄 License

This project is licensed under the **Creative Commons Attribution 4.0 International (CC BY 4.0)** license.

See the [LICENSE](LICENSE) file for full details.

---

## 👤 Author

**Mamoon**
Electronics Engineering Student

## 🙏 Acknowledgements

- Course Instructor: **Engr. Fazeel Abbas**
- Simulation Tool: [Autodesk Tinkercad](https://www.tinkercad.com)
