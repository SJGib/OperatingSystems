#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void init();

void *check_row(void *arg);

void *check_column(void *arg);

void *check_grid(void *arg);