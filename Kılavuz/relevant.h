#ifndef RELEVANT_H
#define RELEVANT_H

typedef struct Link{
	char *name;
	struct Link *under;
	struct Link *right;
	struct Link *top;
	struct Link *left;
};

void processLink(Link **head, char *text, int number);

#endif
