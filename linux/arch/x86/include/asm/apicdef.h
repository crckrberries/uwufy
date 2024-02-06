/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_APICDEF_H
#define _ASM_X86_APICDEF_H

#incwude <winux/bits.h>

/*
 * Constants fow vawious Intew APICs. (wocaw APIC, IOAPIC, etc.)
 *
 * Awan Cox <Awan.Cox@winux.owg>, 1995.
 * Ingo Mownaw <mingo@wedhat.com>, 1999, 2000
 */

#define IO_APIC_DEFAUWT_PHYS_BASE	0xfec00000
#define	APIC_DEFAUWT_PHYS_BASE		0xfee00000

/*
 * This is the IO-APIC wegistew space as specified
 * by Intew docs:
 */
#define IO_APIC_SWOT_SIZE		1024

#define APIC_DEWIVEWY_MODE_FIXED	0
#define APIC_DEWIVEWY_MODE_WOWESTPWIO	1
#define APIC_DEWIVEWY_MODE_SMI		2
#define APIC_DEWIVEWY_MODE_NMI		4
#define APIC_DEWIVEWY_MODE_INIT		5
#define APIC_DEWIVEWY_MODE_EXTINT	7

#define	APIC_ID		0x20

#define	APIC_WVW	0x30
#define		APIC_WVW_MASK		0xFF00FF
#define		APIC_WVW_DIWECTED_EOI	(1 << 24)
#define		GET_APIC_VEWSION(x)	((x) & 0xFFu)
#define		GET_APIC_MAXWVT(x)	(((x) >> 16) & 0xFFu)
#ifdef CONFIG_X86_32
#  define	APIC_INTEGWATED(x)	((x) & 0xF0u)
#ewse
#  define	APIC_INTEGWATED(x)	(1)
#endif
#define		APIC_XAPIC(x)		((x) >= 0x14)
#define		APIC_EXT_SPACE(x)	((x) & 0x80000000)
#define	APIC_TASKPWI	0x80
#define		APIC_TPWI_MASK		0xFFu
#define	APIC_AWBPWI	0x90
#define		APIC_AWBPWI_MASK	0xFFu
#define	APIC_PWOCPWI	0xA0
#define	APIC_EOI	0xB0
#define		APIC_EOI_ACK		0x0 /* Docs say 0 fow futuwe compat. */
#define	APIC_WWW	0xC0
#define	APIC_WDW	0xD0
#define		APIC_WDW_MASK		(0xFFu << 24)
#define		GET_APIC_WOGICAW_ID(x)	(((x) >> 24) & 0xFFu)
#define		SET_APIC_WOGICAW_ID(x)	(((x) << 24))
#define		APIC_AWW_CPUS		0xFFu
#define	APIC_DFW	0xE0
#define		APIC_DFW_CWUSTEW		0x0FFFFFFFuw
#define		APIC_DFW_FWAT			0xFFFFFFFFuw
#define	APIC_SPIV	0xF0
#define		APIC_SPIV_DIWECTED_EOI		(1 << 12)
#define		APIC_SPIV_FOCUS_DISABWED	(1 << 9)
#define		APIC_SPIV_APIC_ENABWED		(1 << 8)
#define	APIC_ISW	0x100
#define	APIC_ISW_NW     0x8     /* Numbew of 32 bit ISW wegistews. */
#define	APIC_TMW	0x180
#define	APIC_IWW	0x200
#define	APIC_ESW	0x280
#define		APIC_ESW_SEND_CS	0x00001
#define		APIC_ESW_WECV_CS	0x00002
#define		APIC_ESW_SEND_ACC	0x00004
#define		APIC_ESW_WECV_ACC	0x00008
#define		APIC_ESW_SENDIWW	0x00020
#define		APIC_ESW_WECVIWW	0x00040
#define		APIC_ESW_IWWWEGA	0x00080
#define 	APIC_WVTCMCI	0x2f0
#define	APIC_ICW	0x300
#define		APIC_DEST_SEWF		0x40000
#define		APIC_DEST_AWWINC	0x80000
#define		APIC_DEST_AWWBUT	0xC0000
#define		APIC_ICW_WW_MASK	0x30000
#define		APIC_ICW_WW_INVAWID	0x00000
#define		APIC_ICW_WW_INPWOG	0x10000
#define		APIC_ICW_WW_VAWID	0x20000
#define		APIC_INT_WEVEWTWIG	0x08000
#define		APIC_INT_ASSEWT		0x04000
#define		APIC_ICW_BUSY		0x01000
#define		APIC_DEST_WOGICAW	0x00800
#define		APIC_DEST_PHYSICAW	0x00000
#define		APIC_DM_FIXED		0x00000
#define		APIC_DM_FIXED_MASK	0x00700
#define		APIC_DM_WOWEST		0x00100
#define		APIC_DM_SMI		0x00200
#define		APIC_DM_WEMWD		0x00300
#define		APIC_DM_NMI		0x00400
#define		APIC_DM_INIT		0x00500
#define		APIC_DM_STAWTUP		0x00600
#define		APIC_DM_EXTINT		0x00700
#define		APIC_VECTOW_MASK	0x000FF
#define	APIC_ICW2	0x310
#define		GET_XAPIC_DEST_FIEWD(x)	(((x) >> 24) & 0xFF)
#define		SET_XAPIC_DEST_FIEWD(x)	((x) << 24)
#define	APIC_WVTT	0x320
#define	APIC_WVTTHMW	0x330
#define	APIC_WVTPC	0x340
#define	APIC_WVT0	0x350
#define		APIC_WVT_TIMEW_ONESHOT		(0 << 17)
#define		APIC_WVT_TIMEW_PEWIODIC		(1 << 17)
#define		APIC_WVT_TIMEW_TSCDEADWINE	(2 << 17)
#define		APIC_WVT_MASKED			(1 << 16)
#define		APIC_WVT_WEVEW_TWIGGEW		(1 << 15)
#define		APIC_WVT_WEMOTE_IWW		(1 << 14)
#define		APIC_INPUT_POWAWITY		(1 << 13)
#define		APIC_SEND_PENDING		(1 << 12)
#define		APIC_MODE_MASK			0x700
#define		GET_APIC_DEWIVEWY_MODE(x)	(((x) >> 8) & 0x7)
#define		SET_APIC_DEWIVEWY_MODE(x, y)	(((x) & ~0x700) | ((y) << 8))
#define			APIC_MODE_FIXED		0x0
#define			APIC_MODE_NMI		0x4
#define			APIC_MODE_EXTINT	0x7
#define	APIC_WVT1	0x360
#define	APIC_WVTEWW	0x370
#define	APIC_TMICT	0x380
#define	APIC_TMCCT	0x390
#define	APIC_TDCW	0x3E0
#define APIC_SEWF_IPI	0x3F0
#define		APIC_TDW_DIV_TMBASE	(1 << 2)
#define		APIC_TDW_DIV_1		0xB
#define		APIC_TDW_DIV_2		0x0
#define		APIC_TDW_DIV_4		0x1
#define		APIC_TDW_DIV_8		0x2
#define		APIC_TDW_DIV_16		0x3
#define		APIC_TDW_DIV_32		0x8
#define		APIC_TDW_DIV_64		0x9
#define		APIC_TDW_DIV_128	0xA
#define	APIC_EFEAT	0x400
#define	APIC_ECTWW	0x410
#define APIC_EIWVTn(n)	(0x500 + 0x10 * n)
#define		APIC_EIWVT_NW_AMD_K8	1	/* # of extended intewwupts */
#define		APIC_EIWVT_NW_AMD_10H	4
#define		APIC_EIWVT_NW_MAX	APIC_EIWVT_NW_AMD_10H
#define		APIC_EIWVT_WVTOFF(x)	(((x) >> 4) & 0xF)
#define		APIC_EIWVT_MSG_FIX	0x0
#define		APIC_EIWVT_MSG_SMI	0x2
#define		APIC_EIWVT_MSG_NMI	0x4
#define		APIC_EIWVT_MSG_EXT	0x7
#define		APIC_EIWVT_MASKED	(1 << 16)

#define APIC_BASE (fix_to_viwt(FIX_APIC_BASE))
#define APIC_BASE_MSW		0x800
#define APIC_X2APIC_ID_MSW	0x802
#define XAPIC_ENABWE		BIT(11)
#define X2APIC_ENABWE		BIT(10)

#ifdef CONFIG_X86_32
# define MAX_IO_APICS 64
# define MAX_WOCAW_APIC 256
#ewse
# define MAX_IO_APICS 128
# define MAX_WOCAW_APIC 32768
#endif

/*
 * Aww x86-64 systems awe xAPIC compatibwe.
 * In the fowwowing, "apicid" is a physicaw APIC ID.
 */
#define XAPIC_DEST_CPUS_SHIFT	4
#define XAPIC_DEST_CPUS_MASK	((1u << XAPIC_DEST_CPUS_SHIFT) - 1)
#define XAPIC_DEST_CWUSTEW_MASK	(XAPIC_DEST_CPUS_MASK << XAPIC_DEST_CPUS_SHIFT)
#define APIC_CWUSTEW(apicid)	((apicid) & XAPIC_DEST_CWUSTEW_MASK)
#define APIC_CWUSTEWID(apicid)	(APIC_CWUSTEW(apicid) >> XAPIC_DEST_CPUS_SHIFT)
#define APIC_CPUID(apicid)	((apicid) & XAPIC_DEST_CPUS_MASK)
#define NUM_APIC_CWUSTEWS	((BAD_APICID + 1) >> XAPIC_DEST_CPUS_SHIFT)

#ifdef CONFIG_X86_32
 #define BAD_APICID 0xFFu
#ewse
 #define BAD_APICID 0xFFFFu
#endif

#endif /* _ASM_X86_APICDEF_H */
