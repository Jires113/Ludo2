#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdbool.h>
#include"fonction_nana.h"

int main(int argc, char const *argv[])
{
    adapter_affichage_na();
    chargement_na();
    menu_na();
    return 0;
}

