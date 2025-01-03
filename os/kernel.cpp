#include <stdint.h>

#define ROW_SIZE 160
#define ROW_COUNT 25

/* TODO: I want to use a faster way to clear the memory */
void print_message(
    const char *message, 
    uint32_t row,
    uint8_t text_color
) {
    if (row >= ROW_COUNT) return;

    unsigned char *video_memory = (unsigned char*)0xb8000;
    unsigned char *video_row_start = video_memory + row * ROW_SIZE;

    uint32_t i;

    for (i = 0; message[i] != 0; i++) {
        uint32_t cell_offset = i * 2;

        video_row_start[cell_offset]     = message[i];
        video_row_start[cell_offset + 1] = text_color;
    }

    for (uint32_t j = i; j < ROW_SIZE; j++) {
        uint32_t cell_offset = j * 2;

        video_row_start[cell_offset]     = 0;
        video_row_start[cell_offset + 1] = 0;
    }
}

typedef enum {
    BLACK = 0x0,
    BLUE = 0x1,
    GREEN = 0x2,
    CYAN = 0x3,
    RED = 0x4,
    MAGENTA = 0x5,
    BROWN = 0x6,
    LIGHT_GRAY = 0x7,
    DARK_GRAY = 0x8,
    LIGHT_BLUE = 0x9,
    LIGHT_GREEN = 0xA,
    LIGHT_CYAN = 0xB,
    LIGHT_RED = 0xC,
    LIGHT_MAGENTA = 0xD,
    YELLOW = 0xE,
    WHITE = 0xF
} text_colors;

/* TODO: I want to use a faster way to get the string length */
uint32_t strlen(const char *str) {
    uint32_t i;
    
    for (i = 0; str[i] != 0; i++);

    return i;
}

char nibble_to_hex(uint8_t nibble) {
    switch (nibble) {
        case 0x00:
            return '0';
        case 0x01:
            return '1';
        case 0x02:
            return '2';
        case 0x03:
            return '3';
        case 0x04:
            return '4';
        case 0x05:
            return '5';
        case 0x06:
            return '6';
        case 0x07:
            return '7';
        case 0x08:
            return '8';
        case 0x09:
            return '9';
        case 0x0a:
            return 'A';
        case 0x0b:
            return 'B';
        case 0x0c:
            return 'C';
        case 0x0d:
            return 'D';
        case 0x0e:
            return 'E';
        case 0x0f:
            return 'F';
        default:
            return 'W';
    }
}

void addr_to_string(char *addr_buf, uint32_t addr) {
    addr_buf[0] = '0';
    addr_buf[1] = 'x';

    for (uint8_t i = 0; i < 4; i++) {
        uint8_t byte = (addr >> (i * 8)) & 0xff;

        uint8_t lower_nibble  = byte & 0x0f;
        uint8_t higher_nibble = byte >> 4;

        addr_buf[9 - 2 * i]     = nibble_to_hex(lower_nibble);
        addr_buf[9 - 2 * i - 1] = nibble_to_hex(higher_nibble);
    }
}

typedef struct {
    uint32_t size;        // Size of the entry (not including this field)
    uint64_t addr;        // Start address of the memory region
    uint64_t len;         // Length of the memory region
    uint32_t type;        // Type of the memory region
} __attribute__((packed)) multiboot_memory_map_t;

extern multiboot_memory_map_t *multiboot_info_ptr;

extern "C" void k_entry(void) {
    print_message("Welcome to MushuOS dude!", 0, YELLOW);

    print_message("Testing for address conversions... ", 2, YELLOW);

    char addr_message[15];
    addr_message[0] = 'A';
    addr_message[1] = 'd';
    addr_message[2] = 'd';
    addr_message[3] = 'r';
    addr_message[4] = ' ';

    // Test case 1
    addr_to_string(&addr_message[5], 0x000000ff);
    print_message(addr_message, 4, RED);

    // Test case 2
    addr_to_string(&addr_message[5], 0x0000ff00);
    print_message(addr_message, 5, GREEN);

    // Test case 3
    addr_to_string(&addr_message[5], 0x00ff00ff);
    print_message(addr_message, 6, LIGHT_BLUE);

    // Test case 4
    addr_to_string(&addr_message[5], 0x11002200);
    print_message(addr_message, 7, LIGHT_MAGENTA);

    // Halting to save my computer fans...
    asm volatile("HLT");
}