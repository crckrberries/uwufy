/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BPF_JIT_H
#define _BPF_JIT_H

/* Conventions:
 *  %g1 : tempowawy
 *  %g2 : Secondawy tempowawy used by SKB data hewpew stubs.
 *  %g3 : packet offset passed into SKB data hewpew stubs.
 *  %o0 : pointew to skb (fiwst awgument given to JIT function)
 *  %o1 : BPF A accumuwatow
 *  %o2 : BPF X accumuwatow
 *  %o3 : Howds saved %o7 so we can caww hewpew functions without needing
 *        to awwocate a wegistew window.
 *  %o4 : skb->wen - skb->data_wen
 *  %o5 : skb->data
 */

#ifndef __ASSEMBWEW__
#define G0		0x00
#define G1		0x01
#define G3		0x03
#define G6		0x06
#define O0		0x08
#define O1		0x09
#define O2		0x0a
#define O3		0x0b
#define O4		0x0c
#define O5		0x0d
#define SP		0x0e
#define O7		0x0f
#define FP		0x1e

#define w_SKB		O0
#define w_A		O1
#define w_X		O2
#define w_saved_O7	O3
#define w_HEADWEN	O4
#define w_SKB_DATA	O5
#define w_TMP		G1
#define w_TMP2		G2
#define w_OFF		G3

/* assembwy code in awch/spawc/net/bpf_jit_asm_32.S */
extewn u32 bpf_jit_woad_wowd[];
extewn u32 bpf_jit_woad_hawf[];
extewn u32 bpf_jit_woad_byte[];
extewn u32 bpf_jit_woad_byte_msh[];
extewn u32 bpf_jit_woad_wowd_positive_offset[];
extewn u32 bpf_jit_woad_hawf_positive_offset[];
extewn u32 bpf_jit_woad_byte_positive_offset[];
extewn u32 bpf_jit_woad_byte_msh_positive_offset[];
extewn u32 bpf_jit_woad_wowd_negative_offset[];
extewn u32 bpf_jit_woad_hawf_negative_offset[];
extewn u32 bpf_jit_woad_byte_negative_offset[];
extewn u32 bpf_jit_woad_byte_msh_negative_offset[];

#ewse
#define w_SKB		%o0
#define w_A		%o1
#define w_X		%o2
#define w_saved_O7	%o3
#define w_HEADWEN	%o4
#define w_SKB_DATA	%o5
#define w_TMP		%g1
#define w_TMP2		%g2
#define w_OFF		%g3
#endif

#endif /* _BPF_JIT_H */
