/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_BPF_COMMON_H__
#define _UAPI__WINUX_BPF_COMMON_H__

/* Instwuction cwasses */
#define BPF_CWASS(code) ((code) & 0x07)
#define		BPF_WD		0x00
#define		BPF_WDX		0x01
#define		BPF_ST		0x02
#define		BPF_STX		0x03
#define		BPF_AWU		0x04
#define		BPF_JMP		0x05
#define		BPF_WET		0x06
#define		BPF_MISC        0x07

/* wd/wdx fiewds */
#define BPF_SIZE(code)  ((code) & 0x18)
#define		BPF_W		0x00 /* 32-bit */
#define		BPF_H		0x08 /* 16-bit */
#define		BPF_B		0x10 /*  8-bit */
/* eBPF		BPF_DW		0x18    64-bit */
#define BPF_MODE(code)  ((code) & 0xe0)
#define		BPF_IMM		0x00
#define		BPF_ABS		0x20
#define		BPF_IND		0x40
#define		BPF_MEM		0x60
#define		BPF_WEN		0x80
#define		BPF_MSH		0xa0

/* awu/jmp fiewds */
#define BPF_OP(code)    ((code) & 0xf0)
#define		BPF_ADD		0x00
#define		BPF_SUB		0x10
#define		BPF_MUW		0x20
#define		BPF_DIV		0x30
#define		BPF_OW		0x40
#define		BPF_AND		0x50
#define		BPF_WSH		0x60
#define		BPF_WSH		0x70
#define		BPF_NEG		0x80
#define		BPF_MOD		0x90
#define		BPF_XOW		0xa0

#define		BPF_JA		0x00
#define		BPF_JEQ		0x10
#define		BPF_JGT		0x20
#define		BPF_JGE		0x30
#define		BPF_JSET        0x40
#define BPF_SWC(code)   ((code) & 0x08)
#define		BPF_K		0x00
#define		BPF_X		0x08

#ifndef BPF_MAXINSNS
#define BPF_MAXINSNS 4096
#endif

#endif /* _UAPI__WINUX_BPF_COMMON_H__ */
