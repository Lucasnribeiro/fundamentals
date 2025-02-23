// chip8.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chip8.h"

Chip8 *chip8_create(void)
{
    Chip8 *chip8 = (Chip8 *)malloc(sizeof(Chip8));
    if (chip8 == NULL)
    {
        return NULL;
    }

    if (!chip8_initialize(chip8))
    {
        free(chip8);
        return NULL;
    }

    return chip8;
}

bool chip8_initialize(Chip8 *chip8)
{
    if (chip8 == NULL)
    {
        return false;
    }

    // Clear everything
    memset(chip8->memory, 0, MEMORY_SIZE);
    memset(chip8->V, 0, NUM_REGISTERS);
    memset(chip8->display, 0, SCREEN_WIDTH * SCREEN_HEIGHT);

    // Set initial values
    chip8->I = 0;
    chip8->pc = 0x200; // Program starts at 0x200
    chip8->sp = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->draw_flag = false;

    return true;
}

void chip8_cycle(Chip8 *chip8)
{
    // Fetch
    uint16_t opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1];

    // For this example, let's just implement the clear screen instruction (0x00E0)
    switch (opcode)
    {
    case 0x00E0: // Clear screen
        memset(chip8->display, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
        chip8->draw_flag = true;
        chip8->pc += 2;
        break;
    case 0x00EE:
        // Decrease sp first
        chip8->sp--;
        // Now sp points to the top value
        chip8->pc = chip8->stack[chip8->sp];
        // Move to next instruction
        chip8->pc += 2;
        break;
    case 0x1000:
        chip8->pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        // Save current PC at current sp (it's already pointing to free spot)
        chip8->stack[chip8->sp] = chip8->pc;
        // Move sp to next free spot
        chip8->sp++;
        // Jump to subroutine
        chip8->pc = opcode & 0x0FFF;
        break;
    case 0x3000:
        // Get the register x from 3xkk
        uint8_t x = (opcode & 0x0F00) >> 8;
        // Get the value kk from 3xkk
        uint8_t kk = opcode & 0x00FF;
        // Compare the value to kk
        if (chip8->V[x] == kk)
        {
            // If they are, jump 4 addresses
            chip8->pc += 4;
        }
        break;
    case 0x4000:
        // Get the register x from 3xkk
        uint8_t x = (opcode & 0x0F00) >> 8;
        // Get the value kk from 3xkk
        uint8_t kk = opcode & 0x00FF;
        // Compare the value to kk
        if (chip8->V[x] != kk)
        {
            // If they are, jump 4 addresses
            chip8->pc += 4;
        }
        break;
    case 0x4000:
        // Get the register x from 3xkk
        uint8_t x = (opcode & 0x0F00) >> 8;
        // Get the value kk from 3xkk
        uint8_t kk = opcode & 0x00FF;
        // Compare the value to kk
        if (chip8->V[x] != kk)
        {
            // If they are, jump 4 addresses
            chip8->pc += 4;
        }
        break;
    default:
        printf("Unknown opcode: 0x%X\n", opcode);
        chip8->pc += 2;
    }
}

void chip8_destroy(Chip8 *chip8)
{
    if (chip8 != NULL)
    {
        free(chip8);
    }
}