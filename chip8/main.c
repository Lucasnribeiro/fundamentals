// main.c
#include <stdio.h>
#include "chip8.h"

int main()
{
    Chip8 *chip8 = chip8_create();
    if (chip8 == NULL)
    {
        printf("Failed to create CHIP-8 system\n");
        return 1;
    }

    // Let's manually put a clear screen instruction in memory
    chip8->memory[0x200] = 0x00;
    chip8->memory[0x201] = 0xE0;

    // Run one cycle
    chip8_cycle(chip8);

    // Check if screen was cleared
    bool is_screen_clear = true;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        if (chip8->display[i] != 0)
        {
            is_screen_clear = false;
            break;
        }
    }

    printf("Screen cleared: %s\n", is_screen_clear ? "Yes" : "No");
    printf("Program counter: 0x%X\n", chip8->pc);

    chip8_destroy(chip8);
    return 0;
}