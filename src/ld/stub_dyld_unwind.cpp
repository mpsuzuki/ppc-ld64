#include <stdint.h>

struct dyld_unwind_sections {
    const void*   mh;
    const void*   dwarf_section;
    uintptr_t     dwarf_section_length;
    const void*   compact_unwind_section;
    uintptr_t     compact_unwind_section_length;
};

extern "C" int _dyld_find_unwind_sections(void* addr, dyld_unwind_sections* info) {
    (void)addr;
    (void)info;
#ifdef DEBUG
    fprintf(stderr, "_dyld_find_unwind_sections stub called\n");
#endif
    return 0; // return "not found" always
}
