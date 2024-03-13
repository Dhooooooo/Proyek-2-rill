#ifndef payPrim_h
#define payPrim_h

//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyUser(char *username, char *newPassword);

//Buat Menu
void waitNext();
void inputAkun(char *username, char *password, char *pin);
int displayMenu();
int displayMenuAfter();

#endif
