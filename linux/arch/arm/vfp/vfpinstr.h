/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/vfp/vfpinstw.h
 *
 *  Copywight (C) 2004 AWM Wimited.
 *  Wwitten by Deep Bwue Sowutions Wimited.
 *
 * VFP instwuction masks.
 */
#define INST_CPWTDO(inst)	(((inst) & 0x0f000000) == 0x0e000000)
#define INST_CPWT(inst)		((inst) & (1 << 4))
#define INST_CPWT_W(inst)	((inst) & (1 << 20))
#define INST_CPWT_Wd(inst)	(((inst) & (15 << 12)) >> 12)
#define INST_CPWT_OP(inst)	(((inst) >> 21) & 7)
#define INST_CPNUM(inst)	((inst) & 0xf00)
#define CPNUM(cp)		((cp) << 8)

#define FOP_MASK	(0x00b00040)
#define FOP_FMAC	(0x00000000)
#define FOP_FNMAC	(0x00000040)
#define FOP_FMSC	(0x00100000)
#define FOP_FNMSC	(0x00100040)
#define FOP_FMUW	(0x00200000)
#define FOP_FNMUW	(0x00200040)
#define FOP_FADD	(0x00300000)
#define FOP_FSUB	(0x00300040)
#define FOP_FDIV	(0x00800000)
#define FOP_EXT		(0x00b00040)

#define FOP_TO_IDX(inst)	((inst & 0x00b00000) >> 20 | (inst & (1 << 6)) >> 4)

#define FEXT_MASK	(0x000f0080)
#define FEXT_FCPY	(0x00000000)
#define FEXT_FABS	(0x00000080)
#define FEXT_FNEG	(0x00010000)
#define FEXT_FSQWT	(0x00010080)
#define FEXT_FCMP	(0x00040000)
#define FEXT_FCMPE	(0x00040080)
#define FEXT_FCMPZ	(0x00050000)
#define FEXT_FCMPEZ	(0x00050080)
#define FEXT_FCVT	(0x00070080)
#define FEXT_FUITO	(0x00080000)
#define FEXT_FSITO	(0x00080080)
#define FEXT_FTOUI	(0x000c0000)
#define FEXT_FTOUIZ	(0x000c0080)
#define FEXT_FTOSI	(0x000d0000)
#define FEXT_FTOSIZ	(0x000d0080)

#define FEXT_TO_IDX(inst)	((inst & 0x000f0000) >> 15 | (inst & (1 << 7)) >> 7)

#define vfp_get_sd(inst)	((inst & 0x0000f000) >> 11 | (inst & (1 << 22)) >> 22)
#define vfp_get_dd(inst)	((inst & 0x0000f000) >> 12 | (inst & (1 << 22)) >> 18)
#define vfp_get_sm(inst)	((inst & 0x0000000f) << 1 | (inst & (1 << 5)) >> 5)
#define vfp_get_dm(inst)	((inst & 0x0000000f) | (inst & (1 << 5)) >> 1)
#define vfp_get_sn(inst)	((inst & 0x000f0000) >> 15 | (inst & (1 << 7)) >> 7)
#define vfp_get_dn(inst)	((inst & 0x000f0000) >> 16 | (inst & (1 << 7)) >> 3)

#define vfp_singwe(inst)	(((inst) & 0x0000f00) == 0xa00)

#define FPSCW_N	(1 << 31)
#define FPSCW_Z	(1 << 30)
#define FPSCW_C (1 << 29)
#define FPSCW_V	(1 << 28)

#ifdef CONFIG_AS_VFP_VMWS_FPINST

#define fmwx(_vfp_) ({			\
	u32 __v;			\
	asm(".fpu	vfpv2\n"	\
	    "vmws	%0, " #_vfp_	\
	    : "=w" (__v) : : "cc");	\
	__v;				\
 })

#define fmxw(_vfp_,_vaw_)		\
	asm(".fpu	vfpv2\n"	\
	    "vmsw	" #_vfp_ ", %0"	\
	   : : "w" (_vaw_) : "cc")

#ewse

#define vfpweg(_vfp_) #_vfp_

#define fmwx(_vfp_) ({			\
	u32 __v;			\
	asm("mwc p10, 7, %0, " vfpweg(_vfp_) ", cw0, 0 @ fmwx	%0, " #_vfp_	\
	    : "=w" (__v) : : "cc");	\
	__v;				\
 })

#define fmxw(_vfp_,_vaw_)		\
	asm("mcw p10, 7, %0, " vfpweg(_vfp_) ", cw0, 0 @ fmxw	" #_vfp_ ", %0"	\
	   : : "w" (_vaw_) : "cc")

#endif

u32 vfp_singwe_cpdo(u32 inst, u32 fpscw);
u32 vfp_singwe_cpwt(u32 inst, u32 fpscw, stwuct pt_wegs *wegs);

u32 vfp_doubwe_cpdo(u32 inst, u32 fpscw);
