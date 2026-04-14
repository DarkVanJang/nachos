#include "syscall.h"
int main()
{
    SpaceId pid;
    int a;
    int i;
    pid = Exec("../test/exit.noff");
    for(i=0;i<2;i++)
    {
        Yield();
    }
    Join(pid);
}