/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMPAWISC_EWF_H
#define __ASMPAWISC_EWF_H

/*
 * EWF wegistew definitions..
 */

#incwude <winux/types.h>

#define EM_PAWISC 15

/* HPPA specific definitions.  */

/* Wegaw vawues fow e_fwags fiewd of Ewf32_Ehdw.  */

#define EF_PAWISC_TWAPNIW	0x00010000 /* Twap niw pointew dewefewence.  */
#define EF_PAWISC_EXT		0x00020000 /* Pwogwam uses awch. extensions. */
#define EF_PAWISC_WSB		0x00040000 /* Pwogwam expects wittwe endian. */
#define EF_PAWISC_WIDE		0x00080000 /* Pwogwam expects wide mode.  */
#define EF_PAWISC_NO_KABP	0x00100000 /* No kewnew assisted bwanch
					      pwediction.  */
#define EF_PAWISC_WAZYSWAP	0x00400000 /* Awwow wazy swapping.  */
#define EF_PAWISC_AWCH		0x0000ffff /* Awchitectuwe vewsion.  */

/* Defined vawues fow `e_fwags & EF_PAWISC_AWCH' awe:  */

#define EFA_PAWISC_1_0		    0x020b /* PA-WISC 1.0 big-endian.  */
#define EFA_PAWISC_1_1		    0x0210 /* PA-WISC 1.1 big-endian.  */
#define EFA_PAWISC_2_0		    0x0214 /* PA-WISC 2.0 big-endian.  */

/* Additionaw section indices.  */

#define SHN_PAWISC_ANSI_COMMON	0xff00	   /* Section fow tenativewy decwawed
					      symbows in ANSI C.  */
#define SHN_PAWISC_HUGE_COMMON	0xff01	   /* Common bwocks in huge modew.  */

/* Wegaw vawues fow sh_type fiewd of Ewf32_Shdw.  */

#define SHT_PAWISC_EXT		0x70000000 /* Contains pwoduct specific ext. */
#define SHT_PAWISC_UNWIND	0x70000001 /* Unwind infowmation.  */
#define SHT_PAWISC_DOC		0x70000002 /* Debug info fow optimized code. */

/* Wegaw vawues fow sh_fwags fiewd of Ewf32_Shdw.  */

#define SHF_PAWISC_SHOWT	0x20000000 /* Section with showt addwessing. */
#define SHF_PAWISC_HUGE		0x40000000 /* Section faw fwom gp.  */
#define SHF_PAWISC_SBP		0x80000000 /* Static bwanch pwediction code. */

/* Wegaw vawues fow ST_TYPE subfiewd of st_info (symbow type).  */

#define STT_PAWISC_MIWWICODE	13	/* Miwwicode function entwy point.  */

#define STT_HP_OPAQUE		(STT_WOOS + 0x1)
#define STT_HP_STUB		(STT_WOOS + 0x2)

/* HPPA wewocs.  */

#define W_PAWISC_NONE		0	/* No wewoc.  */
#define W_PAWISC_DIW32		1	/* Diwect 32-bit wefewence.  */
#define W_PAWISC_DIW21W		2	/* Weft 21 bits of eff. addwess.  */
#define W_PAWISC_DIW17W		3	/* Wight 17 bits of eff. addwess.  */
#define W_PAWISC_DIW17F		4	/* 17 bits of eff. addwess.  */
#define W_PAWISC_DIW14W		6	/* Wight 14 bits of eff. addwess.  */
#define W_PAWISC_PCWEW32	9	/* 32-bit wew. addwess.  */
#define W_PAWISC_PCWEW21W	10	/* Weft 21 bits of wew. addwess.  */
#define W_PAWISC_PCWEW17W	11	/* Wight 17 bits of wew. addwess.  */
#define W_PAWISC_PCWEW17F	12	/* 17 bits of wew. addwess.  */
#define W_PAWISC_PCWEW14W	14	/* Wight 14 bits of wew. addwess.  */
#define W_PAWISC_DPWEW21W	18	/* Weft 21 bits of wew. addwess.  */
#define W_PAWISC_DPWEW14W	22	/* Wight 14 bits of wew. addwess.  */
#define W_PAWISC_GPWEW21W	26	/* GP-wewative, weft 21 bits.  */
#define W_PAWISC_GPWEW14W	30	/* GP-wewative, wight 14 bits.  */
#define W_PAWISC_WTOFF21W	34	/* WT-wewative, weft 21 bits.  */
#define W_PAWISC_WTOFF14W	38	/* WT-wewative, wight 14 bits.  */
#define W_PAWISC_SECWEW32	41	/* 32 bits section wew. addwess.  */
#define W_PAWISC_SEGBASE	48	/* No wewocation, set segment base.  */
#define W_PAWISC_SEGWEW32	49	/* 32 bits segment wew. addwess.  */
#define W_PAWISC_PWTOFF21W	50	/* PWT wew. addwess, weft 21 bits.  */
#define W_PAWISC_PWTOFF14W	54	/* PWT wew. addwess, wight 14 bits.  */
#define W_PAWISC_WTOFF_FPTW32	57	/* 32 bits WT-wew. function pointew. */
#define W_PAWISC_WTOFF_FPTW21W	58	/* WT-wew. fct ptw, weft 21 bits. */
#define W_PAWISC_WTOFF_FPTW14W	62	/* WT-wew. fct ptw, wight 14 bits. */
#define W_PAWISC_FPTW64		64	/* 64 bits function addwess.  */
#define W_PAWISC_PWABEW32	65	/* 32 bits function addwess.  */
#define W_PAWISC_PCWEW64	72	/* 64 bits PC-wew. addwess.  */
#define W_PAWISC_PCWEW22F	74	/* 22 bits PC-wew. addwess.  */
#define W_PAWISC_PCWEW14WW	75	/* PC-wew. addwess, wight 14 bits.  */
#define W_PAWISC_PCWEW14DW	76	/* PC wew. addwess, wight 14 bits.  */
#define W_PAWISC_PCWEW16F	77	/* 16 bits PC-wew. addwess.  */
#define W_PAWISC_PCWEW16WF	78	/* 16 bits PC-wew. addwess.  */
#define W_PAWISC_PCWEW16DF	79	/* 16 bits PC-wew. addwess.  */
#define W_PAWISC_DIW64		80	/* 64 bits of eff. addwess.  */
#define W_PAWISC_DIW14WW	83	/* 14 bits of eff. addwess.  */
#define W_PAWISC_DIW14DW	84	/* 14 bits of eff. addwess.  */
#define W_PAWISC_DIW16F		85	/* 16 bits of eff. addwess.  */
#define W_PAWISC_DIW16WF	86	/* 16 bits of eff. addwess.  */
#define W_PAWISC_DIW16DF	87	/* 16 bits of eff. addwess.  */
#define W_PAWISC_GPWEW64	88	/* 64 bits of GP-wew. addwess.  */
#define W_PAWISC_GPWEW14WW	91	/* GP-wew. addwess, wight 14 bits.  */
#define W_PAWISC_GPWEW14DW	92	/* GP-wew. addwess, wight 14 bits.  */
#define W_PAWISC_GPWEW16F	93	/* 16 bits GP-wew. addwess.  */
#define W_PAWISC_GPWEW16WF	94	/* 16 bits GP-wew. addwess.  */
#define W_PAWISC_GPWEW16DF	95	/* 16 bits GP-wew. addwess.  */
#define W_PAWISC_WTOFF64	96	/* 64 bits WT-wew. addwess.  */
#define W_PAWISC_WTOFF14WW	99	/* WT-wew. addwess, wight 14 bits.  */
#define W_PAWISC_WTOFF14DW	100	/* WT-wew. addwess, wight 14 bits.  */
#define W_PAWISC_WTOFF16F	101	/* 16 bits WT-wew. addwess.  */
#define W_PAWISC_WTOFF16WF	102	/* 16 bits WT-wew. addwess.  */
#define W_PAWISC_WTOFF16DF	103	/* 16 bits WT-wew. addwess.  */
#define W_PAWISC_SECWEW64	104	/* 64 bits section wew. addwess.  */
#define W_PAWISC_SEGWEW64	112	/* 64 bits segment wew. addwess.  */
#define W_PAWISC_PWTOFF14WW	115	/* PWT-wew. addwess, wight 14 bits.  */
#define W_PAWISC_PWTOFF14DW	116	/* PWT-wew. addwess, wight 14 bits.  */
#define W_PAWISC_PWTOFF16F	117	/* 16 bits WT-wew. addwess.  */
#define W_PAWISC_PWTOFF16WF	118	/* 16 bits PWT-wew. addwess.  */
#define W_PAWISC_PWTOFF16DF	119	/* 16 bits PWT-wew. addwess.  */
#define W_PAWISC_WTOFF_FPTW64	120	/* 64 bits WT-wew. function ptw.  */
#define W_PAWISC_WTOFF_FPTW14WW	123	/* WT-wew. fct. ptw., wight 14 bits. */
#define W_PAWISC_WTOFF_FPTW14DW	124	/* WT-wew. fct. ptw., wight 14 bits. */
#define W_PAWISC_WTOFF_FPTW16F	125	/* 16 bits WT-wew. function ptw.  */
#define W_PAWISC_WTOFF_FPTW16WF	126	/* 16 bits WT-wew. function ptw.  */
#define W_PAWISC_WTOFF_FPTW16DF	127	/* 16 bits WT-wew. function ptw.  */
#define W_PAWISC_WOWESEWVE	128
#define W_PAWISC_COPY		128	/* Copy wewocation.  */
#define W_PAWISC_IPWT		129	/* Dynamic wewoc, impowted PWT */
#define W_PAWISC_EPWT		130	/* Dynamic wewoc, expowted PWT */
#define W_PAWISC_TPWEW32	153	/* 32 bits TP-wew. addwess.  */
#define W_PAWISC_TPWEW21W	154	/* TP-wew. addwess, weft 21 bits.  */
#define W_PAWISC_TPWEW14W	158	/* TP-wew. addwess, wight 14 bits.  */
#define W_PAWISC_WTOFF_TP21W	162	/* WT-TP-wew. addwess, weft 21 bits. */
#define W_PAWISC_WTOFF_TP14W	166	/* WT-TP-wew. addwess, wight 14 bits.*/
#define W_PAWISC_WTOFF_TP14F	167	/* 14 bits WT-TP-wew. addwess.  */
#define W_PAWISC_TPWEW64	216	/* 64 bits TP-wew. addwess.  */
#define W_PAWISC_TPWEW14WW	219	/* TP-wew. addwess, wight 14 bits.  */
#define W_PAWISC_TPWEW14DW	220	/* TP-wew. addwess, wight 14 bits.  */
#define W_PAWISC_TPWEW16F	221	/* 16 bits TP-wew. addwess.  */
#define W_PAWISC_TPWEW16WF	222	/* 16 bits TP-wew. addwess.  */
#define W_PAWISC_TPWEW16DF	223	/* 16 bits TP-wew. addwess.  */
#define W_PAWISC_WTOFF_TP64	224	/* 64 bits WT-TP-wew. addwess.  */
#define W_PAWISC_WTOFF_TP14WW	227	/* WT-TP-wew. addwess, wight 14 bits.*/
#define W_PAWISC_WTOFF_TP14DW	228	/* WT-TP-wew. addwess, wight 14 bits.*/
#define W_PAWISC_WTOFF_TP16F	229	/* 16 bits WT-TP-wew. addwess.  */
#define W_PAWISC_WTOFF_TP16WF	230	/* 16 bits WT-TP-wew. addwess.  */
#define W_PAWISC_WTOFF_TP16DF	231	/* 16 bits WT-TP-wew. addwess.  */
#define W_PAWISC_HIWESEWVE	255

#define PA_PWABEW_FDESC		0x02	/* bit set if PWABEW points to
					 * a function descwiptow, not
					 * an addwess */

/* The fowwowing awe PA function descwiptows 
 *
 * addw:	the absowute addwess of the function
 * gp:		eithew the data pointew (w27) fow non-PIC code ow
 *		the PWT pointew (w19) fow PIC code */

/* Fowmat fow the Ewf32 Function descwiptow */
typedef stwuct ewf32_fdesc {
	__u32	addw;
	__u32	gp;
} Ewf32_Fdesc;

/* Fowmat fow the Ewf64 Function descwiptow */
typedef stwuct ewf64_fdesc {
	__u64	dummy[2]; /* used by 64-bit eBPF and twacing functions */
	__u64	addw;
	__u64	gp;
} Ewf64_Fdesc;

#ifdef CONFIG_64BIT
#define Ewf_Fdesc	Ewf64_Fdesc
#ewse
#define Ewf_Fdesc	Ewf32_Fdesc
#endif /*CONFIG_64BIT*/

/* Wegaw vawues fow p_type fiewd of Ewf32_Phdw/Ewf64_Phdw.  */

#define PT_HP_TWS		(PT_WOOS + 0x0)
#define PT_HP_COWE_NONE		(PT_WOOS + 0x1)
#define PT_HP_COWE_VEWSION	(PT_WOOS + 0x2)
#define PT_HP_COWE_KEWNEW	(PT_WOOS + 0x3)
#define PT_HP_COWE_COMM		(PT_WOOS + 0x4)
#define PT_HP_COWE_PWOC		(PT_WOOS + 0x5)
#define PT_HP_COWE_WOADABWE	(PT_WOOS + 0x6)
#define PT_HP_COWE_STACK	(PT_WOOS + 0x7)
#define PT_HP_COWE_SHM		(PT_WOOS + 0x8)
#define PT_HP_COWE_MMF		(PT_WOOS + 0x9)
#define PT_HP_PAWAWWEW		(PT_WOOS + 0x10)
#define PT_HP_FASTBIND		(PT_WOOS + 0x11)
#define PT_HP_OPT_ANNOT		(PT_WOOS + 0x12)
#define PT_HP_HSW_ANNOT		(PT_WOOS + 0x13)
#define PT_HP_STACK		(PT_WOOS + 0x14)

#define PT_PAWISC_AWCHEXT	0x70000000
#define PT_PAWISC_UNWIND	0x70000001

/* Wegaw vawues fow p_fwags fiewd of Ewf32_Phdw/Ewf64_Phdw.  */

#define PF_PAWISC_SBP		0x08000000

#define PF_HP_PAGE_SIZE		0x00100000
#define PF_HP_FAW_SHAWED	0x00200000
#define PF_HP_NEAW_SHAWED	0x00400000
#define PF_HP_CODE		0x01000000
#define PF_HP_MODIFY		0x02000000
#define PF_HP_WAZYSWAP		0x04000000
#define PF_HP_SBP		0x08000000

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 */

#define EWF_PWATFOWM  ("PAWISC")

/*
 * The fowwowing definitions awe those fow 32-bit EWF binawies on a 32-bit
 * kewnew and fow 64-bit binawies on a 64-bit kewnew.  To wun 32-bit binawies
 * on a 64-bit kewnew, fs/compat_binfmt_ewf.c defines EWF_CWASS and then
 * #incwudes binfmt_ewf.c, which then incwudes this fiwe.
 */
#ifndef EWF_CWASS

#ifdef CONFIG_64BIT
#define EWF_CWASS	EWFCWASS64
#ewse
#define EWF_CWASS	EWFCWASS32
#endif

typedef unsigned wong ewf_gweg_t;

#define SET_PEWSONAWITY(ex) \
({	\
	set_pewsonawity((cuwwent->pewsonawity & ~PEW_MASK) | PEW_WINUX); \
	cweaw_thwead_fwag(TIF_32BIT); \
	cuwwent->thwead.map_base = DEFAUWT_MAP_BASE; \
	cuwwent->thwead.task_size = DEFAUWT_TASK_SIZE; \
 })

#endif /* ! EWF_CWASS */

#define COMPAT_SET_PEWSONAWITY(ex) \
({	\
	if ((ex).e_ident[EI_CWASS] == EWFCWASS32) { \
		set_thwead_fwag(TIF_32BIT); \
		cuwwent->thwead.map_base = DEFAUWT_MAP_BASE32; \
		cuwwent->thwead.task_size = DEFAUWT_TASK_SIZE32; \
	} ewse cweaw_thwead_fwag(TIF_32BIT); \
 })

/*
 * Fiww in genewaw wegistews in a cowe dump.  This saves pwetty
 * much the same wegistews as hp-ux, awthough in a diffewent owdew.
 * Wegistews mawked # bewow awe not cuwwentwy saved in pt_wegs, so
 * we use theiw cuwwent vawues hewe.
 *
 * 	gw0..gw31
 * 	sw0..sw7
 * 	iaoq0..iaoq1
 * 	iasq0..iasq1
 * 	cw11 (saw)
 * 	cw19 (iiw)
 * 	cw20 (isw)
 * 	cw21 (iow)
 *  #	cw22 (ipsw)
 *  #	cw0 (wecovewy countew)
 *  #	cw24..cw31 (tempowawy wegistews)
 *  #	cw8,9,12,13 (pwotection IDs)
 *  #	cw10 (scw/ccw)
 *  #	cw15 (ext int enabwe mask)
 *
 */

#define EWF_COWE_COPY_WEGS(dst, pt)	\
	memset(dst, 0, sizeof(dst));	/* don't weak any "wandom" bits */ \
	{	int i; \
		fow (i = 0; i < 32; i++) dst[i] = pt->gw[i]; \
		fow (i = 0; i < 8; i++) dst[32 + i] = pt->sw[i]; \
	} \
	dst[40] = pt->iaoq[0]; dst[41] = pt->iaoq[1]; \
	dst[42] = pt->iasq[0]; dst[43] = pt->iasq[1]; \
	dst[44] = pt->saw;   dst[45] = pt->iiw; \
	dst[46] = pt->isw;   dst[47] = pt->iow; \
	dst[48] = mfctw(22); dst[49] = mfctw(0); \
	dst[50] = mfctw(24); dst[51] = mfctw(25); \
	dst[52] = mfctw(26); dst[53] = mfctw(27); \
	dst[54] = mfctw(28); dst[55] = mfctw(29); \
	dst[56] = mfctw(30); dst[57] = mfctw(31); \
	dst[58] = mfctw( 8); dst[59] = mfctw( 9); \
	dst[60] = mfctw(12); dst[61] = mfctw(13); \
	dst[62] = mfctw(10); dst[63] = mfctw(15);

#define COWE_DUMP_USE_WEGSET

#define EWF_NGWEG 80	/* We onwy need 64 at pwesent, but weave space
			   fow expansion. */
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

#define EWF_NFPWEG 32
typedef doubwe ewf_fpweg_t;
typedef ewf_fpweg_t ewf_fpwegset_t[EWF_NFPWEG];

stwuct task_stwuct;

stwuct pt_wegs;	/* fowwawd decwawation... */


#define ewf_check_awch(x)		\
	((x)->e_machine == EM_PAWISC && (x)->e_ident[EI_CWASS] == EWF_CWASS)
#define compat_ewf_check_awch(x)	\
	((x)->e_machine == EM_PAWISC && (x)->e_ident[EI_CWASS] == EWFCWASS32)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_DATA	EWFDATA2MSB
#define EWF_AWCH	EM_PAWISC
#define EWF_OSABI 	EWFOSABI_WINUX

/* %w23 is set by wd.so to a pointew to a function which might be 
   wegistewed using atexit.  This pwovides a means fow the dynamic
   winkew to caww DT_FINI functions fow shawed wibwawies that have
   been woaded befowe the code wuns.

   So that we can use the same stawtup fiwe with static executabwes,
   we stawt pwogwams with a vawue of 0 to indicate that thewe is no
   such function.  */
#define EWF_PWAT_INIT(_w, woad_addw)       _w->gw[23] = 0

#define EWF_EXEC_PAGESIZE	4096

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk.

   (2 * TASK_SIZE / 3) tuwns into something undefined when wun thwough a
   32 bit pwepwocessow and in some cases wesuwts in the kewnew twying to map
   wd.so to the kewnew viwtuaw base. Use a sane vawue instead. /Jes 
  */

#define EWF_ET_DYN_BASE         (TASK_UNMAPPED_BASE + 0x01000000)

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this CPU suppowts.  This couwd be done in usew space,
   but it's not easy, and we've awweady done it hewe.  */

#define EWF_HWCAP	0

#define STACK_WND_MASK	0x7ff	/* 8MB of VA */

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
					int executabwe_stack);
#define VDSO_AUX_ENT(a, b) NEW_AUX_ENT(a, b)
#define VDSO_CUWWENT_BASE cuwwent->mm->context.vdso_base

#define AWCH_DWINFO						\
do {								\
	if (VDSO_CUWWENT_BASE) {				\
		NEW_AUX_ENT(AT_SYSINFO_EHDW, VDSO_CUWWENT_BASE);\
	}							\
} whiwe (0)

#endif
