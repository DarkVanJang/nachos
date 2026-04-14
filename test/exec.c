#include "syscall.h"
int main()
{
    SpaceId pid;
    pid=Exec("../test/halt.noff"); //./nachos -x ../test/exec.noff
    Halt();
}