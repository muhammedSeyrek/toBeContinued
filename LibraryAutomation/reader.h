#ifndef READER_H
#define READER_H
#include "employee.h"

void loanTake(Person **person, Book **book, char *name, char *author, char *personName);

void loanGive(Person **person, Book **book, char *personName);

void processReader(Person **person, Book **book, char *personName, char *email);

#endif
