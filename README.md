# Banking Management System in C++

Welcome to this simple and easy-to-use **Banking Management System** implemented in C++.  
It lets you manage clients and users with permissions, do transactions, and keep everything saved in files.  

---

## 🌟 Features

| Feature             | Description                             |
|---------------------|---------------------------------------|
| User Login          | Secure login with username & password |
| User Permissions    | Control what users can/can't do        |
| Client Management   | Add, update, delete, find clients      |
| Transactions        | Deposit, withdraw, show total balances |
| User Management     | Add, update, delete, find users        |
| File Storage        | Save/load users and clients to files   |

---

## 📂 Files

| File Name       | Purpose                     |
|-----------------|-----------------------------|
| `main.cpp`      | Source code                 |
| `UsersFile.txt` | Stores user information     |
| `ClientFile.txt`| Stores client information   |

---

## 🔐 Permissions

Each user has a permissions number controlling what they can do.  
Permissions are bit flags where each bit means:

| Bit Position | Permission           | Description              |
|--------------|----------------------|--------------------------|
| 0            | Show Client List      | Can view clients         |
| 1            | Add New Client        | Can add clients          |
| 2            | Delete Client         | Can delete clients       |
| 3            | Update Client Info    | Can update client info   |
| 4            | Find Client           | Can search clients       |
| 5            | Transactions          | Can deposit/withdraw     |
| 6            | Manage Users          | Can manage users         |

If permission is `-1`, the user has **full access**.

---

## 💡 Tips & Notes

- Use clear and unique usernames for users and unique account numbers for clients.
- Deposits and withdrawals check for valid account numbers.
- Withdrawal amount cannot exceed the current client balance.
- User passwords are stored in plain text — consider hashing for better security.
- The program uses a simple text-based menu system for easy navigation.

---
