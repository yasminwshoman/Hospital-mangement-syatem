# 🏥 Hospital Queue Management System

A **role-based hospital management system** built in **C++** to efficiently handle **patient registration**, **specialization-based categorization**, and **real-time queue management** across multiple departments.

## 👥 User Roles

### 👨‍⚕️ Doctor
- Views patients filtered by their **specialization**
- Accesses only relevant departments
- Views patient details for consultation

### 🧑‍💼 Administrator
- Registers patients (normal or emergency)
- Manages multiple departments
- Sends patients to doctors
- Views or filters patient lists by specialization

---

## 📌 Features

- ✅ Register and manage patient data
- ✅ Queue system with priority support for emergency cases
- ✅ Specialization-based patient categorization
- ✅ Role-based dashboards for doctors and admins
- ✅ Multi-department support
- ✅ Terminal-based interactive menu system

---

## 🏗️ Project Structure

- `Patient` struct: holds patient info (ID, name, age, etc.)
- `Department` class: handles queue and operations per department
- `User` (abstract base class)
  - `Doctor` class: specialized view
  - `Administrator` class: full management access

---

## 🧪 How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/hospital-queue-system.git
   cd hospital-queue-system
