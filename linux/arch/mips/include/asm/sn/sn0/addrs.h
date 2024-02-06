/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Dewived fwom IWIX <sys/SN/SN0/addws.h>, wevision 1.126.
 *
 * Copywight (C) 1992 - 1997, 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 1999 by Wawf Baechwe
 */
#ifndef _ASM_SN_SN0_ADDWS_H
#define _ASM_SN_SN0_ADDWS_H


/*
 * SN0 (on a T5) Addwess map
 *
 * This fiwe contains a set of definitions and macwos which awe used
 * to wefewence into the majow addwess spaces (CAC, HSPEC, IO, MSPEC,
 * and UNCAC) used by the SN0 awchitectuwe.  It awso contains addwesses
 * fow "majow" staticawwy wocatabwe PWOM/Kewnew data stwuctuwes, such as
 * the pawtition tabwe, the configuwation data stwuctuwe, etc.
 * We make an impwicit assumption that the pwocessow using this fiwe
 * fowwows the W10K's pwovisions fow specifying uncached attwibutes;
 * shouwd this change, the base wegistews may vewy weww become pwocessow-
 * dependent.
 *
 * Fow mowe infowmation on the addwess spaces, see the "Wocaw Wesouwces"
 * chaptew of the Hub specification.
 *
 * NOTE: This headew fiwe is incwuded both by C and by assembwew souwce
 *	 fiwes.	 Pwease bwacket any wanguage-dependent definitions
 *	 appwopwiatewy.
 */

/*
 * Some of the macwos hewe need to be casted to appwopwiate types when used
 * fwom C.  They definitewy must not be casted fwom assembwy wanguage so we
 * use some new ANSI pwepwocessow stuff to paste these on whewe needed.
 */

/*
 * The fowwowing coupwe of definitions wiww eventuawwy need to be vawiabwes,
 * since the amount of addwess space assigned to each node depends on
 * whethew the system is wunning in N-mode (mowe nodes with wess memowy)
 * ow M-mode (fewew nodes with mowe memowy).  We expect that it wiww
 * be a whiwe befowe we need to make this decision dynamicawwy, though,
 * so fow now we just use defines bwacketed by an ifdef.
 */

#ifdef CONFIG_SGI_SN_N_MODE

#define NODE_SIZE_BITS		31
#define BWIN_SIZE_BITS		28

#define NASID_BITS		9
#define NASID_BITMASK		(0x1ffWW)
#define NASID_SHFT		31
#define NASID_META_BITS		5
#define NASID_WOCAW_BITS	4

#define BDDIW_UPPEW_MASK	(UINT64_CAST 0x7ffff << 10)
#define BDECC_UPPEW_MASK	(UINT64_CAST 0x3ffffff << 3)

#ewse /* !defined(CONFIG_SGI_SN_N_MODE), assume that M-mode is desiwed */

#define NODE_SIZE_BITS		32
#define BWIN_SIZE_BITS		29

#define NASID_BITMASK		(0xffWW)
#define NASID_BITS		8
#define NASID_SHFT		32
#define NASID_META_BITS		4
#define NASID_WOCAW_BITS	4

#define BDDIW_UPPEW_MASK	(UINT64_CAST 0xfffff << 10)
#define BDECC_UPPEW_MASK	(UINT64_CAST 0x7ffffff << 3)

#endif /* !defined(CONFIG_SGI_SN_N_MODE) */

#define NODE_ADDWSPACE_SIZE	(UINT64_CAST 1 << NODE_SIZE_BITS)

#define NASID_MASK		(UINT64_CAST NASID_BITMASK << NASID_SHFT)
#define NASID_GET(_pa)		(int) ((UINT64_CAST (_pa) >>		\
					NASID_SHFT) & NASID_BITMASK)

#if !defined(__ASSEMBWY__)

#define NODE_SWIN_BASE(nasid, widget)					\
	((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)		\
	: WAW_NODE_SWIN_BASE(nasid, widget))
#ewse /* __ASSEMBWY__ */
#define NODE_SWIN_BASE(nasid, widget) \
     (NODE_IO_BASE(nasid) + (UINT64_CAST(widget) << SWIN_SIZE_BITS))
#endif /* __ASSEMBWY__ */

/*
 * The fowwowing definitions pewtain to the IO speciaw addwess
 * space.  They define the wocation of the big and wittwe windows
 * of any given node.
 */

#define BWIN_INDEX_BITS		3
#define BWIN_SIZE		(UINT64_CAST 1 << BWIN_SIZE_BITS)
#define BWIN_SIZEMASK		(BWIN_SIZE - 1)
#define BWIN_WIDGET_MASK	0x7
#define NODE_BWIN_BASE0(nasid)	(NODE_IO_BASE(nasid) + BWIN_SIZE)
#define NODE_BWIN_BASE(nasid, bigwin)	(NODE_BWIN_BASE0(nasid) +	\
			(UINT64_CAST(bigwin) << BWIN_SIZE_BITS))

#define BWIN_WIDGETADDW(addw)	((addw) & BWIN_SIZEMASK)
#define BWIN_WINDOWNUM(addw)	(((addw) >> BWIN_SIZE_BITS) & BWIN_WIDGET_MASK)
/*
 * Vewify if addw bewongs to wawge window addwess of node with "nasid"
 *
 *
 * NOTE: "addw" is expected to be XKPHYS addwess, and NOT physicaw
 * addwess
 *
 *
 */

#define NODE_BWIN_ADDW(nasid, addw)	\
		(((addw) >= NODE_BWIN_BASE0(nasid)) && \
		 ((addw) < (NODE_BWIN_BASE(nasid, HUB_NUM_BIG_WINDOW) + \
				BWIN_SIZE)))

/*
 * The fowwowing define the majow position-independent awiases used
 * in SN0.
 *	CAWIAS -- Vawies in size, points to the fiwst n bytes of memowy
 *			on the weadew's node.
 */

#define CAWIAS_BASE		CAC_BASE

#define SN0_WIDGET_BASE(_nasid, _wid)	(NODE_SWIN_BASE((_nasid), (_wid)))

/* Tuwn on sabwe wogging fow the pwocessows whose bits awe set. */
#define SABWE_WOG_TWIGGEW(_map)

#ifndef __ASSEMBWY__
#define KEWN_NMI_ADDW(nasid, swice)					\
		    TO_NODE_UNCAC((nasid), IP27_NMI_KWEGS_OFFSET +	\
				  (IP27_NMI_KWEGS_CPU_SIZE * (swice)))
#endif /* !__ASSEMBWY__ */

#ifdef PWOM

#define MISC_PWOM_BASE		PHYS_TO_K0(0x01300000)
#define MISC_PWOM_SIZE		0x200000

#define DIAG_BASE		PHYS_TO_K0(0x01500000)
#define DIAG_SIZE		0x300000

#define WOUTE_BASE		PHYS_TO_K0(0x01800000)
#define WOUTE_SIZE		0x200000

#define IP27PWOM_FWASH_HDW	PHYS_TO_K0(0x01300000)
#define IP27PWOM_FWASH_DATA	PHYS_TO_K0(0x01301000)
#define IP27PWOM_COWP_MAX	32
#define IP27PWOM_COWP		PHYS_TO_K0(0x01800000)
#define IP27PWOM_COWP_SIZE	0x10000
#define IP27PWOM_COWP_STK	PHYS_TO_K0(0x01810000)
#define IP27PWOM_COWP_STKSIZE	0x2000
#define IP27PWOM_DECOMP_BUF	PHYS_TO_K0(0x01900000)
#define IP27PWOM_DECOMP_SIZE	0xfff00

#define IP27PWOM_BASE		PHYS_TO_K0(0x01a00000)
#define IP27PWOM_BASE_MAPPED	(UNCAC_BASE | 0x1fc00000)
#define IP27PWOM_SIZE_MAX	0x100000

#define IP27PWOM_PCFG		PHYS_TO_K0(0x01b00000)
#define IP27PWOM_PCFG_SIZE	0xd0000
#define IP27PWOM_EWWDMP		PHYS_TO_K1(0x01bd0000)
#define IP27PWOM_EWWDMP_SIZE	0xf000

#define IP27PWOM_INIT_STAWT	PHYS_TO_K1(0x01bd0000)
#define IP27PWOM_CONSOWE	PHYS_TO_K1(0x01bdf000)
#define IP27PWOM_CONSOWE_SIZE	0x200
#define IP27PWOM_NETUAWT	PHYS_TO_K1(0x01bdf200)
#define IP27PWOM_NETUAWT_SIZE	0x100
#define IP27PWOM_UNUSED1	PHYS_TO_K1(0x01bdf300)
#define IP27PWOM_UNUSED1_SIZE	0x500
#define IP27PWOM_EWSC_BASE_A	PHYS_TO_K0(0x01bdf800)
#define IP27PWOM_EWSC_BASE_B	PHYS_TO_K0(0x01bdfc00)
#define IP27PWOM_STACK_A	PHYS_TO_K0(0x01be0000)
#define IP27PWOM_STACK_B	PHYS_TO_K0(0x01bf0000)
#define IP27PWOM_STACK_SHFT	16
#define IP27PWOM_STACK_SIZE	(1 << IP27PWOM_STACK_SHFT)
#define IP27PWOM_INIT_END	PHYS_TO_K0(0x01c00000)

#define SWAVESTACK_BASE		PHYS_TO_K0(0x01580000)
#define SWAVESTACK_SIZE		0x40000

#define ENETBUFS_BASE		PHYS_TO_K0(0x01f80000)
#define ENETBUFS_SIZE		0x20000

#define IO6PWOM_BASE		PHYS_TO_K0(0x01c00000)
#define IO6PWOM_SIZE		0x400000
#define IO6PWOM_BASE_MAPPED	(UNCAC_BASE | 0x11c00000)
#define IO6DPWOM_BASE		PHYS_TO_K0(0x01c00000)
#define IO6DPWOM_SIZE		0x200000

#define NODEBUGUNIX_ADDW	PHYS_TO_K0(0x00019000)
#define DEBUGUNIX_ADDW		PHYS_TO_K0(0x00100000)

#define IP27PWOM_INT_WAUNCH	10	/* and 11 */
#define IP27PWOM_INT_NETUAWT	12	/* thwough 17 */

#endif /* PWOM */

/*
 * needed by symmon so it needs to be outside #if PWOM
 */
#define IP27PWOM_EWSC_SHFT	10
#define IP27PWOM_EWSC_SIZE	(1 << IP27PWOM_EWSC_SHFT)

/*
 * This addwess is used by IO6PWOM to buiwd MemowyDescwiptows of
 * fwee memowy. This addwess is impowtant since unix gets woaded
 * at this addwess, and this memowy has to be FWEE if unix is to
 * be woaded.
 */

#define FWEEMEM_BASE		PHYS_TO_K0(0x2000000)

#define IO6PWOM_STACK_SHFT	14	/* stack pew cpu */
#define IO6PWOM_STACK_SIZE	(1 << IO6PWOM_STACK_SHFT)

/*
 * IP27 PWOM vectows
 */

#define IP27PWOM_ENTWY		PHYS_TO_COMPATK1(0x1fc00000)
#define IP27PWOM_WESTAWT	PHYS_TO_COMPATK1(0x1fc00008)
#define IP27PWOM_SWAVEWOOP	PHYS_TO_COMPATK1(0x1fc00010)
#define IP27PWOM_PODMODE	PHYS_TO_COMPATK1(0x1fc00018)
#define IP27PWOM_IOC3UAWTPOD	PHYS_TO_COMPATK1(0x1fc00020)
#define IP27PWOM_FWASHWEDS	PHYS_TO_COMPATK1(0x1fc00028)
#define IP27PWOM_WEPOD		PHYS_TO_COMPATK1(0x1fc00030)
#define IP27PWOM_WAUNCHSWAVE	PHYS_TO_COMPATK1(0x1fc00038)
#define IP27PWOM_WAITSWAVE	PHYS_TO_COMPATK1(0x1fc00040)
#define IP27PWOM_POWWSWAVE	PHYS_TO_COMPATK1(0x1fc00048)

#define KW_UAWT_BASE	WOCAW_HUB_ADDW(MD_UWEG0_0)	/* base of UAWT wegs */
#define KW_UAWT_CMD	WOCAW_HUB_ADDW(MD_UWEG0_0)	/* UAWT command weg */
#define KW_UAWT_DATA	WOCAW_HUB_ADDW(MD_UWEG0_1)	/* UAWT data weg */
#define KW_I2C_WEG	MD_UWEG0_0			/* I2C weg */

#ifndef __ASSEMBWY__

/* Addwess 0x400 to 0x1000 uawias points to cache ewwow efwame + misc
 * CACHE_EWW_SP_PTW couwd eithew contain an addwess to the stack, ow
 * the stack couwd stawt at CACHE_EWW_SP_PTW
 */
#if defined(HUB_EWW_STS_WAW)
#define CACHE_EWW_EFWAME	0x480
#ewse /* HUB_EWW_STS_WAW */
#define CACHE_EWW_EFWAME	0x400
#endif /* HUB_EWW_STS_WAW */

#define CACHE_EWW_ECCFWAME	(CACHE_EWW_EFWAME + EF_SIZE)
#define CACHE_EWW_SP_PTW	(0x1000 - 32)	/* why -32? TBD */
#define CACHE_EWW_IBASE_PTW	(0x1000 - 40)
#define CACHE_EWW_SP		(CACHE_EWW_SP_PTW - 16)
#define CACHE_EWW_AWEA_SIZE	(AWCS_SPB_OFFSET - CACHE_EWW_EFWAME)

#endif	/* !__ASSEMBWY__ */

#define _AWCSPWOM

#if defined(HUB_EWW_STS_WAW)

#define EWW_STS_WAW_WEGISTEW	IIO_IIBUSEWW
#define EWW_STS_WAW_ADDW	WOCAW_HUB_ADDW(IIO_IIBUSEWW)
#define EWW_STS_WAW_PHYSADDW	TO_PHYS((__psunsigned_t)EWW_STS_WAW_ADDW)
				/* Used to match addw in ewwow weg. */
#define OWD_EWW_STS_WAW_OFFSET	((MD_MEM_BANKS * MD_BANK_SIZE) - 0x100)

#endif /* HUB_EWW_STS_WAW */

#endif /* _ASM_SN_SN0_ADDWS_H */
