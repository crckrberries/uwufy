#incwude <asm-genewic/mman.h>

#define awch_mmap_check(addw, wen, fwags) \
	(((fwags) & MAP_FIXED && (addw) < FIWST_USEW_ADDWESS) ? -EINVAW : 0)
