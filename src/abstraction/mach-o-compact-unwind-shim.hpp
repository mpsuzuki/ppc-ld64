#pragma once

#include <mach-o/compact_unwind_encoding.h>

using lldb_private::unwind_info_section_header;
using lldb_private::unwind_info_section_header_index_entry;
using lldb_private::unwind_info_section_header_lsda_index_entry;

using lldb_private::unwind_info_regular_second_level_entry;
using lldb_private::unwind_info_regular_second_level_page_header;
using lldb_private::unwind_info_compressed_second_level_page_header;

using lldb_private::UNWIND_X86_MODE_MASK;
using lldb_private::UNWIND_X86_MODE_DWARF;
// using lldb_private::UNWIND_X86_MODE_FRAME;
// using lldb_private::UNWIND_X86_MODE_SJLI;

using lldb_private::UNWIND_X86_64_MODE_MASK;
using lldb_private::UNWIND_X86_64_MODE_DWARF;
// using lldb_private::UNWIND_X86_64_MODE_FRAME;
// using lldb_private::UNWIND_X86_64_MODE_SJLI;

using lldb_private::UNWIND_PERSONALITY_MASK;

using lldb_private::compact_unwind_encoding_t;
