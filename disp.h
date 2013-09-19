#ifndef __DISP
#define __DISP

void init();
void end();

void getkeyval(char *key, char *val);
void getkey(char *key);
void display(Table *t);
void dispval(char *val);

char in();

#endif /* !__DISP */
