#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define INSTITUTION_BILLS_H
#define MAX_ACCOUNTS 10
#define ACCOUNT_NUMBER_LENGTH 11
#define PIN_LENGTH 5
#define MAX_WITHDRAWAL_50000 1250000
#define MAX_WITHDRAWAL_100000 2200000
#define MAX_DEPOSIT 5000000
#define ADMIN_FEE 6500
#define UKT_AMOUNT 2500000


typedef struct {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    char pin[PIN_LENGTH];
    char name[100];
    double balance;
} Account;

typedef struct {
    char appCode[4];
    char appName[50];
    double minTopUp;
} PaymentApp;

typedef struct {
    char bankCode[4];
    char bankName[50];
    double adminFee;
} Bank;

typedef struct {
    char uniCode[5];
    char uniName[100];
} University;

typedef struct {
    char phoneNumber[20];
    char userName[100];
} AppAccount;

typedef struct {
    char meterNumber[20];
    char ownerName[100];
} InstitutionAccount;

InstitutionAccount institutionAccounts[3] = {
    {"1234567890", "Juliar"},
    {"0987654321", "Tukiman"},
    {"1122334455", "Darti"}
};

Account accounts[MAX_ACCOUNTS] = {
    {"1234567890", "1234", "Hariansyah", 5000000.0},
    {"0987654321", "4321", "Anjas", 3000000.0},
    {"1111222233", "1111", "Manto", 4000000.0},
    {"4444555566", "2222", "Bobi", 2000000.0}
};

PaymentApp paymentApps[4] = {
    {"001", "Shopee", 10000.0},
    {"002", "Dana", 10000.0},
    {"003", "Gopay", 10000.0},
    {"004", "OVO", 10000.0}
};

Bank banks[15] = {
    {"014", "BCA", 5000.0},
    {"008", "Mandiri", 5000.0},
    {"009", "BNI", 5000.0},
    {"002", "BRI", 7500.0},
    {"022", "CIMB Niaga", 7500.0},
    {"011", "BTN", 7500.0},
    {"032", "OCBC NISP", 10000.0},
    {"016", "HSBC", 10000.0},
    {"037", "Standard Chartered", 10000.0},
    {"200", "MUFG Bank", 10000.0},
    {"098", "Bank Mayapada", 10000.0},
    {"089", "Bank Mega", 10000.0},
    {"003", "Bank Permata", 10000.0},
    {"025", "Bank BTPN", 10000.0},
    {"030", "Bank Sinarmas", 10000.0}
};

University universities[20] = {
    {"001", "UIN Suska"},
    {"002", "Unri"},
    {"003", "UI"},
    {"004", "ITB"},
    {"005", "UGM"},
    {"006", "IPB"},
    {"007", "ITS"},
    {"008", "Unair"},
    {"009", "Undip"},
    {"010", "Unpad"},
    {"011", "Unhas"},
    {"012", "Unsyiah"},
    {"013", "Unmul"},
    {"014", "Unsri"},
    {"015", "Untan"},
    {"016", "Uns"},
    {"017", "Unand"},
    {"018", "Unib"},
    {"019", "Unima"},
    {"020", "Unsrat"}
};

AppAccount appAccounts[4] = {
    {"081234567890", "Syah Shope"},
    {"089876543210", "Syah Dana"},
    {"085612345678", "Syah Gopay"},
    {"087654321098", "Syah OVO"}
};

int currentAccountIndex = -1;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printCentered(const char *text) {
    int len = strlen(text);
    int pos = (80 - len) / 2;
    for (int i = 0; i < pos; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

void printWelcomeMessage() {
    clearScreen();
    printCentered("========================================");
    printCentered("SELAMAT DATANG DI BANK ATM BSI SYAH");
    printCentered("========================================");
    printf("\n\n");
    printf("Apakah anda ingin melakukan transaksi? \n1. Ya \n2. Tidak\n");
    printf("Pilih opsi : ");
    
    int opsi = getchar();
    // Clear the input buffer to handle the '\n' character
    while (getchar() != '\n');

    if (opsi == '2') {
        printf("Terima kasih telah menggunakan layanan kami.\n");
        return; // Exit the function if user chooses 2
    }

    // Proceed to login menu or further actions if opsi == '1'
    if (opsi == '1') {
        // Call the login menu function or further actions here
        printf("Menuju ke menu login...\n");
        // loginMenu(); // Example function call
    } else {
        printf("Opsi tidak valid. Silakan coba lagi.\n");
        // Optionally, you can loop back to asking the question again
    }
}

void mainMenu();
void accountMenu();
void checkBalance();
void withdrawCash();
void depositCash();
void transfer();
void makePayment();
void academicMenu();
void institutionBillsMenu();
void changePin();
void logout();
void login();
void payUKTUniversity();


void askToContinue() {
    int choice;
    printf("Apakah Anda ingin bertransaksi lagi? \n1. Ya \n2. Tidak\n");
    printf("Pilih opsi : ");
    scanf("%d", &choice);
    getchar();  // Consume newline character

    if (choice == 1) {
        accountMenu();
    } else if (choice == 2) {
        logout();
    } else {
        printf("Opsi tidak valid. Silakan coba lagi.\n");
        askToContinue();  // Ask again if the input is invalid
    }
}

void printReceipt(const char *transactionType, double amount, const char *receiverName, const char *receiverAccount) {
    int choice;
    printf("\nApakah Anda ingin mencetak resi? \n1. Ya \n2. Tidak\n");
    printf("Pilih opsi : ");
    scanf("%d", &choice);
    getchar();  // Consume newline character

    if (choice == 1) {
        clearScreen();
        printf("========================================\n");
        printf("               BSI ATM RECEIPT           \n");
        printf("========================================\n");
        printf("Transaction Type: %s\n", transactionType);
        printf("Amount: Rp %.2f\n", amount);
        if (receiverName != NULL && receiverAccount != NULL) {
            printf("Receiver: %s\n", receiverName);
            printf("Receiver Account/Phone: %s\n", receiverAccount);
        }
        printf("Current Balance: Rp %.2f\n", accounts[currentAccountIndex].balance);
        printf("========================================\n");
        printf("            Thank you for using          \n");
        printf("                BSI ATM                  \n");
        printf("========================================\n");
    } else if (choice == 2) {
        printf("Resi tidak dicetak.\n");
    } else {
        printf("Opsi tidak valid. Silakan coba lagi.\n");
        printReceipt(transactionType, amount, receiverName, receiverAccount);  // Ask again if the input is invalid
    }
}



void mainMenu() {
    clearScreen();
    printf("=== Selamat Datang di ATM BSI ===\n");
    printf("1. Login\n");
    printf("2. Keluar\n");
    printf("Pilih opsi: ");
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline character
    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            exit(0);
            break;
        default:
            mainMenu();
    }
}

void login() {
    clearScreen();
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    char pin[PIN_LENGTH];
    printf("Masukkan Nomor Rekening: ");
    scanf("%s", accountNumber);
    printf("Masukkan PIN: ");
    scanf("%s", pin);

    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0 &&
            strcmp(accounts[i].pin, pin) == 0) {
            currentAccountIndex = i;
            accountMenu();
            return;
        }
    }
    printf("Nomor rekening atau PIN salah.\n");
    printf("Tekan Enter untuk kembali ke menu utama.");
    getchar();
    getchar();  // Consume newline character
    mainMenu();
}

void accountMenu() {
    clearScreen();
    printf("=== Selamat Datang, %s ===\n", accounts[currentAccountIndex].name);
    printf("1. Cek Saldo\n");
    printf("2. Tarik Tunai\n");
    printf("3. Setor Tunai\n");
    printf("4. Transfer\n");
    printf("5. Top Up Aplikasi\n");
    printf("6. Akademik\n");
    printf("7. Tagihan Institusi\n");
    printf("8. Ubah PIN\n");
    printf("9. Logout\n");
    printf("Pilih opsi: ");
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline character
    switch (choice) {
        case 1:
            checkBalance();
            break;
        case 2:
            withdrawCash();
            break;
        case 3:
            depositCash();
            break;
        case 4:
            transfer();
            break;
        case 5:
            makePayment();
            break;
        case 6:
            academicMenu();
            break;
        case 7:
            institutionBillsMenu();
            break;
        case 8:
            changePin();
            break;
        case 9:
            logout();
            break;
        default:
            accountMenu();
    }
}

void checkBalance() {
    clearScreen();
    printf("\n\n	Saldo Anda Saat Ini\n");					
	printf("\n           Rp %.2f\n", accounts[currentAccountIndex].balance);
    printReceipt("Cek Saldo", 0.0, NULL, NULL);
    askToContinue();
}

void withdrawCash() {
    clearScreen();
    int denomination;
    printf("Pilih nominal penarikan:\n");
    printf("1. Rp 50,000\n");
    printf("2. Rp 100,000\n");
    printf("3. Rp 200,000\n");
    printf("4. Rp 500,000\n");
    printf("5. Jumlah lainnya (kelipatan Rp 50,000)\n");
    printf("6. Kembali ke menu akun\n");
    printf("Pilih opsi: ");
    scanf("%d", &denomination);
    switch (denomination) {
        case 1:
            if (accounts[currentAccountIndex].balance >= 50000 && accounts[currentAccountIndex].balance <= MAX_WITHDRAWAL_50000) {
                accounts[currentAccountIndex].balance -= 50000;
                printf("Silakan ambil uang Anda.\n");
                printReceipt("Tarik Tunai", 50000.0, NULL, NULL);
            } else {
                printf("Saldo tidak mencukupi atau melebihi batas penarikan.\n");
            }
            break;
        case 2:
            if (accounts[currentAccountIndex].balance >= 100000 && accounts[currentAccountIndex].balance <= MAX_WITHDRAWAL_100000) {
                accounts[currentAccountIndex].balance -= 100000;
                printf("Silakan ambil uang Anda.\n");
                printReceipt("Tarik Tunai", 100000.0, NULL, NULL);
            } else {
                printf("Saldo tidak mencukupi atau melebihi batas penarikan.\n");
            }
            break;
        case 3:
            if (accounts[currentAccountIndex].balance >= 200000) {
                accounts[currentAccountIndex].balance -= 200000;
                printf("Silakan ambil uang Anda.\n");
                printReceipt("Tarik Tunai", 200000.0, NULL, NULL);
            } else {
                printf("Saldo tidak mencukupi.\n");
            }
            break;
        case 4:
            if (accounts[currentAccountIndex].balance >= 500000) {
                accounts[currentAccountIndex].balance -= 500000;
                printf("Silakan ambil uang Anda.\n");
                printReceipt("Tarik Tunai", 500000.0, NULL, NULL);
            } else {
                printf("Saldo tidak mencukupi.\n");
            }
            break;
        case 5: {
            int amount;
            printf("Masukkan jumlah yang ingin ditarik (kelipatan Rp 50,000): ");
            scanf("%d", &amount);
            if (amount % 50000 == 0 && amount <= accounts[currentAccountIndex].balance) {
                accounts[currentAccountIndex].balance -= amount;
                printf("Silakan ambil uang Anda.\n");
                printReceipt("Tarik Tunai", amount, NULL, NULL);
            } else {
                printf("Jumlah tidak valid atau saldo tidak mencukupi.\n");
            }
            break;
        }
        case 6:
            accountMenu();
            break;
        default:
            withdrawCash();
    }
    askToContinue();
}

void depositCash() {
    clearScreen();
    double amount;
    printf("Masukkan jumlah yang ingin disetor (maksimum Rp 5,000,000): Rp ");
    scanf("%lf", &amount);

    if (amount <= MAX_DEPOSIT) {
        int nominal[2] = {50, 100};
        printf("Anda dapat menyetor pecahan 50.000 dan 100.000\n");
    } else {
        printf("Jumlah yang ingin Anda setor lebih dari batas maksimum.\n");
    }
    askToContinue();
}

void transfer() {
    clearScreen();
    char receiverAccount[ACCOUNT_NUMBER_LENGTH];
    printf("Masukkan nomor rekening penerima: ");
    scanf("%s", receiverAccount);

    double amount;
    printf("Masukkan jumlah yang ingin ditransfer: Rp ");
    scanf("%lf", &amount);

    int found = 0;
    // Periksa apakah nomor rekening penerima ada dalam daftar akun BSI
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (strcmp(accounts[i].accountNumber, receiverAccount) == 0) {
            if (amount <= accounts[currentAccountIndex].balance) {
                accounts[i].balance += amount;
                accounts[currentAccountIndex].balance -= amount;
                printf("Transfer berhasil ke %s. Saldo Anda sekarang: Rp %.2f\n", accounts[i].name, accounts[currentAccountIndex].balance);
                printReceipt("Transfer", amount, accounts[i].name, receiverAccount);
            } else {
                printf("Saldo tidak mencukupi untuk transfer ini.\n");
            }
            found = 1;
            break;
        }
    }
    // Jika tidak ditemukan dalam akun BSI, coba cari di bank lain
    if (!found) {
        for (int i = 0; i < 15; i++) {
            if (strcmp(banks[i].bankCode, receiverAccount) == 0) {
                double adminFee = banks[i].adminFee;
                if (amount <= accounts[currentAccountIndex].balance) {
                    accounts[currentAccountIndex].balance -= (amount + adminFee);
                    printf("Transfer antar bank berhasil ke %s. Saldo Anda sekarang: Rp %.2f\n", banks[i].bankName, accounts[currentAccountIndex].balance);
                    printf("Biaya admin: Rp %.2f\n", adminFee);
                    printReceipt("Transfer Antar Bank", amount + adminFee, banks[i].bankName, receiverAccount);
                } else {
                    printf("Saldo tidak mencukupi untuk transfer ini.\n");
                }
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("Nomor rekening penerima tidak ditemukan.\n");
    }
    askToContinue();
}

void makePayment() {
    clearScreen();
    int choice;
    printf("Pilih aplikasi pembayaran:\n");
    printf("1. Shopee\n");
    printf("2. Dana\n");
    printf("3. Gopay\n");
    printf("4. OVO\n");
    printf("5. Kembali ke menu akun\n");
    printf("Pilih opsi: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 4) {
        double minTopUp = paymentApps[choice - 1].minTopUp;
        double amount;
        char phoneNumber[20];
        char *userName = appAccounts[choice - 1].userName; // Mendapatkan nama pengguna aplikasi

        // Meminta nomor telepon tujuan
        printf("Masukkan nomor telepon tujuan: ");
        scanf("%s", phoneNumber);

        printf("Masukkan jumlah yang ingin di-top up (minimum Rp %.2f): Rp ", minTopUp);
        scanf("%lf", &amount);

        if (amount >= minTopUp && amount <= accounts[currentAccountIndex].balance) {
            accounts[currentAccountIndex].balance -= amount;
            printf("Top up %s ke nomor %s berhasil. Saldo Anda sekarang: Rp %.2f\n", paymentApps[choice - 1].appName, phoneNumber, accounts[currentAccountIndex].balance);
            printReceipt("Top Up", amount, userName, phoneNumber); // Menambahkan userName ke resi
        } else if (amount < minTopUp) {
            printf("Jumlah top up kurang dari minimum yang diizinkan.\n");
        } else {
            printf("Saldo tidak mencukupi untuk top up ini.\n");
        }
    } else if (choice == 5) {
        accountMenu();
    } else {
        makePayment();
    }
    askToContinue();
}



void academicMenu() {
    clearScreen();
    int choice;
    printf("=== Menu Akademik ===\n");
    printf("1. Bayar UKT Universitas\n");
    printf("2. Kembali ke menu akun\n");
    printf("Pilih opsi: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            payUKTUniversity();
            break;
        case 2:
            accountMenu();
            break;
        default:
            academicMenu();
    }
}

void payUKTUniversity() {
    clearScreen();
    int choice;
    printf("Pilih universitas untuk membayar UKT:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d. %s\n", i + 1, universities[i].uniName);
    }
    printf("%d. Kembali ke menu akademik\n", 21);
    printf("Pilih opsi: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 20) {
        if (accounts[currentAccountIndex].balance >= UKT_AMOUNT) {
            accounts[currentAccountIndex].balance -= UKT_AMOUNT;
            printf("Pembayaran UKT untuk %s berhasil. Saldo Anda sekarang: Rp %.2f\n", universities[choice - 1].uniName, accounts[currentAccountIndex].balance);
            printReceipt("Bayar UKT", UKT_AMOUNT, universities[choice - 1].uniName, NULL);
        } else {
            printf("Saldo tidak mencukupi untuk membayar UKT.\n");
        }
    } else if (choice == 21) {
        academicMenu();
    } else {
        payUKTUniversity();
    }
    askToContinue();
}

void institutionBillsMenu() {
    clearScreen();
    int choice;
    printf("Pilih jenis tagihan yang ingin dibayar:\n");
    printf("1. Listrik Rumah\n");
    printf("2. PDAM\n");
    printf("3. Tagihan Lainnya\n");
    printf("4. Kembali ke menu akun\n");
    printf("Pilih opsi: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3) {
        char meterNumber[20];
        printf("Masukkan nomor meter: ");
        scanf("%s", meterNumber);

        double amount;
        printf("Masukkan jumlah tagihan: Rp ");
        scanf("%lf", &amount);

        int found = 0;
        for (int i = 0; i < 3; i++) {
            if (strcmp(institutionAccounts[i].meterNumber, meterNumber) == 0) {
                if (amount <= accounts[currentAccountIndex].balance) {
                    accounts[currentAccountIndex].balance -= amount;
                    printf("Pembayaran %s untuk nomor meter %s berhasil. Saldo Anda sekarang: Rp %.2f\n", institutionAccounts[i].ownerName, meterNumber, accounts[currentAccountIndex].balance);
                    printReceipt("Bayar Tagihan", amount, institutionAccounts[i].ownerName, meterNumber);
                } else {
                    printf("Saldo tidak mencukupi untuk membayar tagihan ini.\n");
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Nomor meter tidak ditemukan.\n");
        }
    } else if (choice == 4) {
        accountMenu();
    } else {
        institutionBillsMenu();
    }
    askToContinue();
}

// Function to change PIN
void changePin() {
    clearScreen();
    char oldPIN[PIN_LENGTH];
    char newPIN[PIN_LENGTH];
    char confirmPIN[PIN_LENGTH];

    printf("Masukkan PIN lama: ");
    scanf("%s", oldPIN);

    if (strcmp(accounts[currentAccountIndex].pin, oldPIN) == 0) {
        printf("Masukkan PIN baru: ");
        scanf("%s", newPIN);
        printf("Konfirmasi PIN baru: ");
        scanf("%s", confirmPIN);

        if (strcmp(newPIN, confirmPIN) == 0) {
            strcpy(accounts[currentAccountIndex].pin, newPIN);
            printf("PIN berhasil diubah.\n");
        } else {
            printf("PIN baru tidak cocok.\n");
        }
    } else {
        printf("PIN lama salah.\n");
    }
    askToContinue();
}

// Function to logout
void logout() {
    currentAccountIndex = -1;
    mainMenu();
}

int main() {
    printWelcomeMessage();  // Menampilkan ucapan selamat datang di awal
    mainMenu();
}

