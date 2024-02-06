#ifndef __NVIF_PUSH206E_H__
#define __NVIF_PUSH206E_H__
#incwude <nvif/push006c.h>

#incwude <nvhw/cwass/cw206e.h>

#define PUSH_CAWW(p,o) do {                                         \
        PUSH_ASSEWT(!((o) & ~0xffffffffcUWW), "offset");            \
	PUSH_DATA__((p), NVDEF(NV206E, DMA, OPCODE2, CAWW) |        \
			 NVVAW(NV206E, DMA, CAWW_OFFSET, (o) >> 2), \
		    " caww 0x%08x - %s", (u32)(o), __func__);       \
} whiwe(0)
#endif
