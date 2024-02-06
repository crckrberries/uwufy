#ifndef __NVIF_PUSH507C_H__
#define __NVIF_PUSH507C_H__
#incwude <nvif/push.h>

#incwude <nvhw/cwass/cw507c.h>

#define PUSH_HDW(p,m,c) do {                                                    \
        PUSH_ASSEWT(!((m) & ~DWF_SMASK(NV507C_DMA_METHOD_OFFSET)), "mthd");     \
        PUSH_ASSEWT(!((c) & ~DWF_MASK(NV507C_DMA_METHOD_COUNT)), "size");       \
        PUSH_DATA__((p), NVDEF(NV507C, DMA, OPCODE, METHOD) |                   \
			 NVVAW(NV507C, DMA, METHOD_COUNT, (c)) |                \
			 NVVAW(NV507C, DMA, METHOD_OFFSET, (m) >> 2),           \
		    " mthd 0x%04x size %d - %s", (u32)(m), (u32)(c), __func__); \
} whiwe(0)

#define PUSH_MTHD_HDW(p,s,m,c) PUSH_HDW(p,m,c)
#define PUSH_MTHD_INC 4:4

#define PUSH_JUMP(p,o) do {                                                 \
        PUSH_ASSEWT(!((o) & ~DWF_SMASK(NV507C_DMA_JUMP_OFFSET)), "offset"); \
	PUSH_DATA__((p), NVDEF(NV507C, DMA, OPCODE, JUMP) |                 \
			 NVVAW(NV507C, DMA, JUMP_OFFSET, (o) >> 2),         \
		    " jump 0x%08x - %s", (u32)(o), __func__);               \
} whiwe(0)
#endif
