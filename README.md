
# Payment Application

## Project Overview
The **Payment Application** is a modular C-based project that simulates a payment system, incorporating card and terminal interactions with a server-side validation process. This project showcases a comprehensive understanding of embedded software principles, including modular design, flow control, and secure programming practices.

The system provides functionality to authenticate cardholders, validate transactions, and ensure secure account operations. It's designed to handle multiple edge cases such as expired cards, insufficient funds, and invalid accounts.
![cover_image_1615263810 jpg 760x400_q85_crop_upscale](https://github.com/user-attachments/assets/3de1b60f-7431-4a35-aa42-b2b2174163f5)


---

## Flowchart
The application workflow is illustrated in the following flowchart:
![payment-flowchart](https://github.com/user-attachments/assets/f168da14-1b27-46ee-8bed-3f47741fcc3e)


---

## Features
The project achieves the following functionalities:
1. **Card Module**:
    - Get cardholder name.
    - Retrieve card expiration date.
    - Fetch card PAN (Primary Account Number).
   
2. **Terminal Module**:
    - Retrieve the current transaction date.
    - Check if the card is expired.
    - Validate the transaction amount.
    - Check if the amount exceeds the maximum limit.
    - Set the maximum transaction limit.

3. **Server Module**:
    - Simulated database for accounts and transactions.
    - Validate account status.
    - Check the availability of funds.
    - Save transaction records.
   
4. **Application**:
    - Unified application logic that integrates card, terminal, and server modules.
    - Handles transaction approval or rejection with detailed user feedback.

---

## Project Structure
The project is divided into the following modules:
- **Card Module (`card.c` / `card.h`)**:
  Implements card-related operations, including cardholder name retrieval and validation.
- **Terminal Module (`terminal.c` / `terminal.h`)**:
  Manages terminal interactions, such as date checks and transaction limits.
- **Server Module (`server.c` / `server.h`)**:
  Simulates server-side account and transaction operations.
- **Application Module (`app.c` / `app.h`)**:
  Acts as the main entry point to integrate the modules and manage the workflow.

Each module has a corresponding header file with prototypes, typedefs, and header guards.

---

## Project Milestones

### Card Module
- Implemented:
  - `getCardHolderName`
  - `getCardExpiryDate`
  - `getCardPAN`

### Terminal Module
- Implemented:
  - `getTransactionDate`
  - `isCardExpired`
  - `getTransactionAmount`
  - `isBelowMaxAmount`
  - `setMaxAmount`

### Server Module
- Designed and implemented:
  - Server-side accounts database.
  - Server-side transactions database.
  - `isValidAccount`
  - `isAmountAvailable`
  - `saveTransaction`
  - `receiveTransactionData`

### Application
- Developed the `appStart` function, orchestrating all modules.
- Ensured modularity and clean interaction between components.

---

## Testing
The application has been tested for the following user stories:
1. **Transaction Approved**: A successful transaction where all conditions are met.
2. **Exceed Maximum Amount**: Rejection when the transaction exceeds the maximum limit.
3. **Insufficient Funds**: Rejection due to insufficient account balance.
4. **Expired Card**: Rejection when using an expired card.
5. **Invalid Card**: Rejection when using an invalid or unregistered card.

---

## How to Use
1. Code Compilation:
   ```bash
   gcc src/*.c -o Payment_App.exe 
   ```
2. Run the application and follow the on-screen instructions.
   ```bash
   ./Payment_App.exe 
   ```

---

### Test Results

You can view screenshots and videos of the tests conducted for this project by clicking the link below:

[View Test Results](https://drive.google.com/drive/folders/1t4OgRdjimGlKcMnyinoF-8RWbrsZoJZB?usp=sharing)

