#ifndef payPrim_h
#define payPrim_h

void encrypt(char *text);

void decrypt(char *text);

void registerUser(char *username, char *password);

int loginUser(char *username, char *password);

void modifyUser(char *username, char *newPassword);

int displayMenu();

void inputAkun(char *username, char *password);

#endif
