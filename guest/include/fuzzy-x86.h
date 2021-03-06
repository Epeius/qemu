#define FUZZY_INSTRUCTION_COMPLEX(val1, val2)             \
    ".byte 0x0F, 0x3F\n"                                \
    ".byte 0x00, 0x" #val1 ", 0x" #val2 ", 0x00\n"      \
    ".byte 0x00, 0x00, 0x00, 0x00\n"

#define FUZZY_INSTRUCTION_SIMPLE(val)                     \
    FUZZY_INSTRUCTION_COMPLEX(val, 00)



/** Get fuzzy version or 0 when running without fuzzy. */
static inline int fuzzy_version(void)
{
    int version;
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(00)
        : "=a" (version)  : "a" (0)
    );
    return version;
}

/** Enable symbolic execution. */
static inline void fuzzy_CurTime(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(01)
    );
}

/** Disable symbolic execution. */
static inline void fuzzy_disable_symbolic(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(02)
    );
}

/** Print message to the fuzzy log. */
static inline void fuzzy_message(const char *message)
{
    __fuzzy_touch_string(message);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(10)
        : : "a" (message)
    );
}

/** Print warning to the fuzzy log and fuzzy stdout. */
static inline void fuzzy_warning(const char *message)
{
    __fuzzy_touch_string(message);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(10, 01)
        : : "a" (message)
    );
}

/** Print symbolic expression to the fuzzy log. */
static inline void fuzzy_print_expression(const char *name, int expression)
{
    __fuzzy_touch_string(name);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(07, 01)
        : : "a" (expression), "c" (name)
    );
}

/** Enable forking on symbolic conditions. */
static inline void fuzzy_enable_forking(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(09)
    );
}

/** Disable forking on symbolic conditions. */
static inline void fuzzy_disable_forking(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(0A)
    );
}

/** Yield the current state */
static inline void fuzzy_yield(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(0F)
    );
}

/** Get the current execution path/state id. */
static inline unsigned fuzzy_get_path_id(void)
{
    unsigned id;
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(05)
        : "=a" (id)
    );
    return id;
}

/** Fill buffer with unconstrained symbolic values. */
static inline void fuzzy_make_symbolic(void *buf, int size, const char *name)
{
    __fuzzy_touch_string(name);
    __fuzzy_touch_buffer(buf, size);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(03)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (buf), "d" (size), "c" (name) : "memory"
    );
}

/** Fill buffer with unconstrained symbolic values without discarding concrete data. */
static inline void fuzzy_make_concolic(void *buf, int size, const char *name)
{
    __fuzzy_touch_string(name);
    __fuzzy_touch_buffer(buf, size);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(11)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (buf), "d" (size), "c" (name) : "memory"
    );
}


/** Adds a constraint to the current state. The constraint must be satisfiable. */
static inline void fuzzy_assume(int expression)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(0c)
        : : "a" (expression)
    );
}


/** Returns true if ptr points to symbolic memory */
static inline int fuzzy_is_symbolic(void *ptr, size_t size)
{
    int result;
    __fuzzy_touch_buffer(ptr, 1);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(04)
        : "=a" (result) : "a" (size), "c" (ptr)
    );
    return result;
}

/** Concretize the expression. */
static inline void fuzzy_concretize(void *buf, int size)
{
    __fuzzy_touch_buffer(buf, size);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(20)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (buf), "d" (size) : "memory"
    );
}

/** Get example value for expression (without adding state constraints). */
static inline void fuzzy_get_example(void *buf, int size)
{
    __fuzzy_touch_buffer(buf, size);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(21)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (buf), "d" (size) : "memory"
    );
}

/** Get example value for expression (without adding state constraints). */
/** Convenience function to be used in printfs */
static inline unsigned fuzzy_get_example_uint(unsigned val)
{
    unsigned buf = val;
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(21)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (&buf), "d" (sizeof(buf)) : "memory"
    );
    return buf;
}

/** Terminate current state. */
static inline void fuzzy_kill_state(int status, const char *message)
{
    __fuzzy_touch_string(message);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(06)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (status), "d" (message)
    );
}

/** fork current state, we don't need any arguments and returns. */
static inline void fuzzy_fork_state(void)
{
    __asm__ __volatile__(
            FUZZY_INSTRUCTION_SIMPLE(12)
        );
}

/** Tell alf we finish. */
static inline void fuzzy_tell_afl(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(13)
    );
}

/** Disable timer interrupt in the guest. */
static inline void fuzzy_disable_timer_interrupt(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(50, 01)
    );
}

/** Enable timer interrupt in the guest. */
static inline void fuzzy_enable_timer_interrupt(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(50)
    );
}

/** Disable all APIC interrupts in the guest. */
static inline void fuzzy_disable_all_apic_interrupts(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(51, 01)
    );
}

/** Enable all APIC interrupts in the guest. */
static inline void fuzzy_enable_all_apic_interrupts(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(51)
    );
}

/** Get the current fuzzy_RAM_OBJECT_BITS configuration macro */
static inline int fuzzy_get_ram_object_bits(void)
{
    int bits;
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(52)
        : "=a" (bits)  : "a" (0)
    );
    return bits;
}

/** Declare a merge point: fuzzy will try to merge
 *  all states when they reach this point.
 *
 * NOTE: This requires the merge searcher to be enabled. */
static inline void fuzzy_merge_point(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(70)
    );
}

/** Open file from the guest.
 *
 * NOTE: This requires the HostFiles plugin. */
static inline int fuzzy_open(const char *fname)
{
    int fd;
    __fuzzy_touch_string(fname);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(EE)
        : "=a" (fd) : "a"(-1), "b" (fname), "c" (0)
    );
    return fd;
}

/** Close file from the guest.
 *
 * NOTE: This requires the HostFiles plugin. */
static inline int fuzzy_close(int fd)
{
    int res;
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(EE, 01)
        : "=a" (res) : "a" (-1), "b" (fd)
    );
    return res;
}

/** Read file content from the guest.
 *
 * NOTE: This requires the HostFiles plugin. */
static inline int fuzzy_read(int fd, char *buf, int count)
{
    int res;
    __fuzzy_touch_buffer(buf, count);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rsi, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%esi, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_COMPLEX(EE, 02)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : "=a" (res) : "a" (-1), "S" (fd), "c" (buf), "d" (count)
    );
    return res;
}

/** delete file from the guest.
 *
 * NOTE: This requires the HostFiles plugin. */
static inline int fuzzy_deletefile(const char *fname)
{
    int res;
    __fuzzy_touch_string(fname);
    __asm__ __volatile__(
       FUZZY_INSTRUCTION_COMPLEX(EE, 04)
       : "=a" (res) : "a"(0), "b" (fname)
   );
   return res;
}

/** find file from the guest.
 *
 * NOTE: This requires the HostFiles plugin. */
static inline int fuzzy_find(const char *fname)
{
    int res;
    __fuzzy_touch_string(fname);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(EE, 05)
        : "=a" (res) : "a"(0), "b" (fname)
    );
    return res;
}

/** wait afl to generate testcase.
 *
 * NOTE: This requires that fuzzy is started by AFL so that we can get some pipes. */
static inline int fuzzy_wait_afl_testcase(void)
{
    __asm__ __volatile__(
            FUZZY_INSTRUCTION_SIMPLE(EA) // EA 00 indicates waitting for AFL
    );
}

/** Enable memory tracing */
static inline void fuzzy_memtracer_enable(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(AC)
    );
}

/** Disable memory tracing */
static inline void fuzzy_memtracer_disable(void)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(AC, 01)
    );
}

/** Raw monitor plugin */
/** Communicates to fuzzy the coordinates of loaded modules. Useful when there is
    no plugin to automatically parse OS data structures. */
static inline void fuzzy_rawmon_loadmodule(const char *name, unsigned loadbase, unsigned size)
{
    __fuzzy_touch_string(name);
    __asm__ __volatile__(
#ifdef __x86_64__
        "push %%rbx\n"
        "mov %%rdx, %%rbx\n"
#else
        "pushl %%ebx\n"
        "movl %%edx, %%ebx\n"
#endif
        FUZZY_INSTRUCTION_SIMPLE(AA)
#ifdef __x86_64__
        "pop %%rbx\n"
#else
        "popl %%ebx\n"
#endif
        : : "a" (name), "d" (loadbase), "c" (size)
    );
}

/** Raw monitor plugin */
/** Communicates to fuzzy the coordinates of loaded modules. Useful when there is
    no plugin to automatically parse OS data structures. */
static inline void fuzzy_rawmon_loadmodule2(const char *name,
                                          uint64_t nativebase,
                                          uint64_t loadbase,
                                          uint64_t entrypoint,
                                          uint64_t size,
                                          unsigned kernelMode)
{
    fuzzy_opcode_module_config_t cfg;
    cfg.name = (uintptr_t) name;
    cfg.nativeBase = nativebase;
    cfg.loadBase = loadbase;
    cfg.entryPoint = entrypoint;
    cfg.size = size;
    cfg.kernelMode = kernelMode;

    __fuzzy_touch_string(name);

    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(AA, 02)
        : : "c" (&cfg)
    );
}

/** CodeSelector plugin */
/** Enable forking in the current process (entire address space or user mode only). */
static inline void fuzzy_codeselector_enable_address_space(unsigned user_mode_only)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(AE)
        : : "c" (user_mode_only)
    );
}

/** Disable forking in the specified process (represented by its page directory).
    If pagedir is 0, disable forking in the current process. */
static inline void fuzzy_codeselector_disable_address_space(uint64_t pagedir)
{
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(AE, 01)
        : : "c" (pagedir)
    );
}

static inline void fuzzy_codeselector_select_module(const char *moduleId)
{
    __fuzzy_touch_string(moduleId);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_COMPLEX(AE, 02)
        : : "c" (moduleId)
    );
}

/** Programmatically add a new configuration entry to the ModuleExecutionDetector plugin. */
static inline void fuzzy_moduleexec_add_module(const char *moduleId, const char *moduleName, int kernelMode)
{
    __fuzzy_touch_string(moduleId);
    __fuzzy_touch_string(moduleName);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(AF)
            : : "c" (moduleId), "a" (moduleName), "d" (kernelMode)
    );
}

/** TELL fuzzy we are target */
static inline void fuzzy_moduleexec_inform_target()
{
    __asm__ __volatile__(
            FUZZY_INSTRUCTION_COMPLEX(AF, 01)
    );
}

/**
 *  Transmits a buffer of dataSize length to the plugin named in pluginName.
 *  eax contains the failure code upon return, 0 for success.
 */
static inline int fuzzy_invoke_plugin(const char *pluginName, void *data, uint32_t dataSize)
{
    int result;
    __fuzzy_touch_string(pluginName);
    __fuzzy_touch_buffer(data, dataSize);
    __asm__ __volatile__(
        FUZZY_INSTRUCTION_SIMPLE(0B)
        : "=a" (result) : "a" (pluginName), "c" (data), "d" (dataSize) : "memory"
    );

    return result;
}
