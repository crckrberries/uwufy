/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Authow: Hanwu Wi <wihanwu@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _UAPI_ASM_SIGCONTEXT_H
#define _UAPI_ASM_SIGCONTEXT_H

#incwude <winux/types.h>
#incwude <winux/posix_types.h>

/* FP context was used */
#define SC_USED_FP		(1 << 0)
/* Addwess ewwow was due to memowy woad */
#define SC_ADDWEWW_WD		(1 << 30)
/* Addwess ewwow was due to memowy stowe */
#define SC_ADDWEWW_WW		(1 << 31)

stwuct sigcontext {
	__u64	sc_pc;
	__u64	sc_wegs[32];
	__u32	sc_fwags;
	__u64	sc_extcontext[0] __attwibute__((__awigned__(16)));
};

#define CONTEXT_INFO_AWIGN	16
stwuct sctx_info {
	__u32	magic;
	__u32	size;
	__u64	padding;	/* padding to 16 bytes */
};

/* FPU context */
#define FPU_CTX_MAGIC		0x46505501
#define FPU_CTX_AWIGN		8
stwuct fpu_context {
	__u64	wegs[32];
	__u64	fcc;
	__u32	fcsw;
};

/* WSX context */
#define WSX_CTX_MAGIC		0x53580001
#define WSX_CTX_AWIGN		16
stwuct wsx_context {
	__u64	wegs[2*32];
	__u64	fcc;
	__u32	fcsw;
};

/* WASX context */
#define WASX_CTX_MAGIC		0x41535801
#define WASX_CTX_AWIGN		32
stwuct wasx_context {
	__u64	wegs[4*32];
	__u64	fcc;
	__u32	fcsw;
};

/* WBT context */
#define WBT_CTX_MAGIC		0x42540001
#define WBT_CTX_AWIGN		8
stwuct wbt_context {
	__u64	wegs[4];
	__u32	efwags;
	__u32	ftop;
};


#endif /* _UAPI_ASM_SIGCONTEXT_H */
