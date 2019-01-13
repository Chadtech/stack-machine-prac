#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    Push,
    Add,
    Pop,
    Halt
} Instructions;

const int program[] = {
    Push, 5,
    Push, 6,
    Add,
    Pop,
    Halt};

int stackPointer = -1;
int programIndex = 0;
int stack[256];
bool running = true;

void evaluate(int instruction)
{
    switch (instruction)
    {
    case Halt:
    {
        running = false;
        break;
    }
    case Push:
    {
        stackPointer++;
        programIndex++;
        stack[stackPointer] = program[programIndex];
        break;
    }
    case Pop:
    {
        int poppedValue = stack[stackPointer];
        stackPointer--;
        printf("popped %d\n", poppedValue);
        break;
    }
    case Add:
    {
        int a = stack[stackPointer];
        stackPointer--;
        int b = stack[stackPointer];
        stackPointer--;

        // we then add the result and push it to the stack
        int result = b + a;
        stackPointer++;               // increment stack pointer **before**
        stack[stackPointer] = result; // set the value to the top of the stack

        // all done!
        break;
    }
    }
}

int fetch()
{
    return program[programIndex];
}

int main()
{
    while (running)
    {
        evaluate(fetch());
        programIndex++;
    }
}