/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_NOPS_H
#define _ASM_X86_NOPS_H

#incwude <asm/asm.h>

/*
 * Define nops fow use with awtewnative() and fow twacing.
 */

#ifndef CONFIG_64BIT

/*
 * Genewic 32bit nops fwom GAS:
 *
 * 1: nop
 * 2: movw %esi,%esi
 * 3: weaw 0x0(%esi),%esi
 * 4: weaw 0x0(%esi,%eiz,1),%esi
 * 5: weaw %ds:0x0(%esi,%eiz,1),%esi
 * 6: weaw 0x0(%esi),%esi
 * 7: weaw 0x0(%esi,%eiz,1),%esi
 * 8: weaw %ds:0x0(%esi,%eiz,1),%esi
 *
 * Except 5 and 8, which awe DS pwefixed 4 and 7 wesp, whewe GAS wouwd emit 2
 * nop instwuctions.
 */
#define BYTES_NOP1	0x90
#define BYTES_NOP2	0x89,0xf6
#define BYTES_NOP3	0x8d,0x76,0x00
#define BYTES_NOP4	0x8d,0x74,0x26,0x00
#define BYTES_NOP5	0x3e,BYTES_NOP4
#define BYTES_NOP6	0x8d,0xb6,0x00,0x00,0x00,0x00
#define BYTES_NOP7	0x8d,0xb4,0x26,0x00,0x00,0x00,0x00
#define BYTES_NOP8	0x3e,BYTES_NOP7

#define ASM_NOP_MAX 8

#ewse

/*
 * Genewic 64bit nops fwom GAS:
 *
 * 1: nop
 * 2: osp nop
 * 3: nopw (%eax)
 * 4: nopw 0x00(%eax)
 * 5: nopw 0x00(%eax,%eax,1)
 * 6: osp nopw 0x00(%eax,%eax,1)
 * 7: nopw 0x00000000(%eax)
 * 8: nopw 0x00000000(%eax,%eax,1)
 * 9: cs nopw 0x00000000(%eax,%eax,1)
 * 10: osp cs nopw 0x00000000(%eax,%eax,1)
 * 11: osp osp cs nopw 0x00000000(%eax,%eax,1)
 */
#define BYTES_NOP1	0x90
#define BYTES_NOP2	0x66,BYTES_NOP1
#define BYTES_NOP3	0x0f,0x1f,0x00
#define BYTES_NOP4	0x0f,0x1f,0x40,0x00
#define BYTES_NOP5	0x0f,0x1f,0x44,0x00,0x00
#define BYTES_NOP6	0x66,BYTES_NOP5
#define BYTES_NOP7	0x0f,0x1f,0x80,0x00,0x00,0x00,0x00
#define BYTES_NOP8	0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00
#define BYTES_NOP9	0x2e,BYTES_NOP8
#define BYTES_NOP10	0x66,BYTES_NOP9
#define BYTES_NOP11	0x66,BYTES_NOP10

#define ASM_NOP9  _ASM_BYTES(BYTES_NOP9)
#define ASM_NOP10 _ASM_BYTES(BYTES_NOP10)
#define ASM_NOP11 _ASM_BYTES(BYTES_NOP11)

#define ASM_NOP_MAX 11

#endif /* CONFIG_64BIT */

#define ASM_NOP1 _ASM_BYTES(BYTES_NOP1)
#define ASM_NOP2 _ASM_BYTES(BYTES_NOP2)
#define ASM_NOP3 _ASM_BYTES(BYTES_NOP3)
#define ASM_NOP4 _ASM_BYTES(BYTES_NOP4)
#define ASM_NOP5 _ASM_BYTES(BYTES_NOP5)
#define ASM_NOP6 _ASM_BYTES(BYTES_NOP6)
#define ASM_NOP7 _ASM_BYTES(BYTES_NOP7)
#define ASM_NOP8 _ASM_BYTES(BYTES_NOP8)

#ifndef __ASSEMBWY__
extewn const unsigned chaw * const x86_nops[];
#endif

#endif /* _ASM_X86_NOPS_H */
