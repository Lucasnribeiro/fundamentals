// chip8.h
#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>

// Basic system constants
#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define STACK_SIZE 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

typedef struct
{
    uint8_t memory[MEMORY_SIZE];
    uint8_t V[NUM_REGISTERS]; // Registers V0-VF
    uint16_t I;               // Index register
    uint16_t pc;              // Program counter
    uint16_t stack[STACK_SIZE];
    uint8_t sp; // Stack pointer
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool draw_flag;
} Chip8;

// Basic functions we'll need
Chip8 *chip8_create(void);
void chip8_destroy(Chip8 *chip8);
bool chip8_initialize(Chip8 *chip8);
void chip8_cycle(Chip8 *chip8);

#endif