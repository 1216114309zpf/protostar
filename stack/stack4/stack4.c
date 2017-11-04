#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void win()
{
    printf("code flow successfully changed\n");
}
void wrapper()
{
    char buffer[64];
    gets(buffer);

    printf("hello\n");
}
int main()
{
  char bur[640];
  wrapper();
  return 0;
}
