#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdarg.h>
typedef struct _fuzzy_opcode_module_config_t {
    uint64_t name;
    uint64_t nativeBase;
    uint64_t loadBase;
    uint64_t entryPoint;
    uint64_t size;
    uint32_t kernelMode;
} __attribute__((packed)) fuzzy_opcode_module_config_t;


#ifdef __x86_64__
#define FUZZY_INSTRUCTION_REGISTERS_COMPLEX(val1, val2)   \
        "push %%rbx\n"                                  \
        "mov %%rdx, %%rbx\n"                            \
        FUZZY_INSTRUCTION_COMPLEX(val1, val2)             \
        "pop %%rbx\n"
#else
#define FUZZY_INSTRUCTION_REGISTERS_COMPLEX(val1, val2)   \
        "pushl %%ebx\n"                                 \
        "movl %%edx, %%ebx\n"                           \
        FUZZY_INSTRUCTION_COMPLEX(val1, val2)             \
        "popl %%ebx\n"
#endif

#define FUZZY_INSTRUCTION_REGISTERS_SIMPLE(val)           \
    FUZZY_INSTRUCTION_REGISTERS_COMPLEX(val, 00)

/** Forces the read of every byte of the specified string.
  * This makes sure the memory pages occupied by the string are paged in
  * before passing them to FUZZY, which can't page in memory by itself. */

static inline void __fuzzy_touch_string(volatile const char *string)
{
    while (*string) {
        ++string;
    }
}

static inline void __fuzzy_touch_buffer(volatile void *buffer, unsigned size)
{
    unsigned i;
    volatile char *b = (volatile char *) buffer;
    for (i = 0; i < size; ++i) {
        *b; ++b;
    }
}


#if defined(__i386__) || defined (__amd64__)
#include "fuzzy-x86.h"
#endif

