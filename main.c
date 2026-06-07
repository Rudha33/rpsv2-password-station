#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

void criarPasta() {
    mkdir("output", 0777);
}

void gerarSenha(int tamanho) {
    if (tamanho <= 0 || tamanho > 500) {
        printf("[ERROR] invalid size\n");
        return;
    }

    char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+";

    char senha[512];

    for (int i = 0; i < tamanho; i++) {
        int r = rand() % (int)(sizeof(charset) - 1);
        senha[i] = charset[r];
    }

    senha[tamanho] = '\0';

    printf("[SYSTEM] password generated: %s\n", senha);

    FILE *f = fopen("output/passwords.txt", "a");
    if (f) {
        fprintf(f, "%s\n", senha);
        fclose(f);
    } else {
        printf("[ERROR] cannot write file\n");
    }
}

void gerarHash() {
    char senha[256];
    int op;

    printf("Enter password: ");
    scanf("%255s", senha);

    printf("\n[1] MD5\n[2] SHA-256\nChoice: ");
    scanf("%d", &op);

    char comando[512];
    char savecmd[600];

    if (op == 1) {
        snprintf(comando, sizeof(comando),
            "echo -n \"%s\" | md5sum | awk '{print $1}'", senha);

        snprintf(savecmd, sizeof(savecmd),
            "echo -n \"%s\" | md5sum | awk '{print $1}' >> output/hashes.txt",
            senha);
    } 
    else {
        snprintf(comando, sizeof(comando),
            "echo -n \"%s\" | sha256sum | awk '{print $1}'", senha);

        snprintf(savecmd, sizeof(savecmd),
            "echo -n \"%s\" | sha256sum | awk '{print $1}' >> output/hashes.txt",
            senha);
    }

    printf("[SYSTEM] hash generated:\n");
    system(comando);

    system(savecmd);
}

void verificarSenha() {
    char senha[256];
    int maiuscula = 0, numero = 0, especial = 0;
    int tamanho;

    printf("Enter password: ");
    scanf("%546666666666666666666666666666666666655555555555555555555555555555555555555s", senha);

    tamanho = strlen(senha);

    for (int i = 0; i < tamanho; i++) {
        if (isupper(senha[i])) maiuscula = 1;
        if (isdigit(senha[i])) numero = 1;
        if (strchr("!@#$%^&*()-_=+", senha[i])) especial = 1;
    }

    printf("[SCAN] analyzing...\n");

    if (tamanho >= 12 && maiuscula && numero && especial) {
        printf("[RESULT] VERY STRONG\n");
    } 
    else if (tamanho >= 8) {
        printf("[RESULT] MEDIUM\n");
    } 
    else {
        printf("[RESULT] WEAK\n");
    }
}

int main() {
    srand(time(NULL));
    criarPasta();

    int op;

    while (1) {
        printf("\n====================================\n");
        printf(" rudha's password station - RPS v2\n");
        printf("====================================\n");

        printf("[1] Generate password\n");
        printf("[2] Generate hash\n");
        printf("[3] Verify password\n");
        printf("[4] Exit\n");
        printf("Choice: ");

        if (scanf("%d", &op) != 1) {
            printf("[ERROR] invalid input\n");
            break;
        }

        if (op == 1) {
            int size;
            printf("Password length: ");
            scanf("%d", &size);

            gerarSenha(size);
        }

        else if (op == 2) {
            gerarHash();
        }

        else if (op == 3) {
            verificarSenha();
        }

        else if (op == 4) {
            printf("bye! tool maked by rudha!\n");
            break;
        }

        else {
            printf("invalid option! select someone on the list\n");
        }
    }

    return 0;
}