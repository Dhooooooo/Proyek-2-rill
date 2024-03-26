#ifndef Prima_h
#define Prima_h

//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyPass(char *username, char *password);
void modifyPin(char *username, char *newPin);
void modifyUser(char *username, char *password);

//Per e-Wallet an
void dataSaldoNew(char *username);
int isSaldoCukup(char *username, float totHarga);
int confirmPay(char *username);

//Info Profil
void showInfo(char *username);
void title();



#endif
