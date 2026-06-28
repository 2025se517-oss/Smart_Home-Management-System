# Smart Home Management System (SHMS) - Core Backend

A high-performance C++ backend application designed to automate, monitor, and optimize residential living spaces. Built using pure Object-Oriented Programming (OOP) principles, this system acts as a centralized controller to manage smart appliances, lighting, climate zones, and security infrastructures dynamically.

## 🚀 Key Features & Core Logic
*   **Intelligent Energy Optimization:** Automatically controls climate zones and shuts down high-power appliances when rooms are vacant to reduce costs.
*   **Emergency Response Mitigation:** Instantly triggers safety protocols (e.g., locking digital doors, gas valve shutdown) upon detecting threat vectors like fire or gas leaks.
*   **Predictive Device Maintenance:** Analyzes device runtimes and utility logs to generate system alerts before physical hardware failures occur.
*   **Dynamic Rule & Event Overrides:** Executes automated schedules (e.g., night modes) while maintaining sub-millisecond priority for manual user overrides.

---

## 🛠️ Tech Stack & OOP Concepts Implemented
*   **Language:** C++ (Standard: C++17 or higher)
*   **Encapsulation:** Safe data protection within localized device classes (`SmartLight`, `Thermostat`, `SecurityCamera`).
*   **Inheritance & Polymorphism:** Implementation of a base class `SmartDevice` with virtual functions to dynamically register and handle different appliance types at runtime.
*   **Data Structures:** STL vectors, maps, and queues to manage active device states and prioritize concurrent event logs.
*   **File I/O:** File handling simulation to persistently store system configurations, device logs, and security history.

---

## ⚙️ How to Compile and Run Locally

Ensure you have a C++ compiler installed (GCC/G++ or Clang).

### 1. Clone the Repository
```bash
git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
cd your-repo-name
