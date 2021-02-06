#ifndef MENU_H

#define MENU_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../inc/file_work.h"
#include"../inc/print_info.h"
#include"../inc/sorts.h"
#include"../inc/struct.h"

#define OK 0
#define ERR_OPTION_MUST_BE_NUM -1
#define ERR_OPTION_MUST_BE_FROM_0_TO_13 -2
#define ERR_FILE_MISTAKE -3
#define ERR_NO_SUCH_FILE -42

#define MAX_FLATS 1000

short int option_menu(void);

#endif
