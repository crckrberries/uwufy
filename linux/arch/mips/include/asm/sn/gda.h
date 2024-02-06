/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Dewived fwom IWIX <sys/SN/gda.h>.
 *
 * Copywight (C) 1992 - 1997, 2000 Siwicon Gwaphics, Inc.
 *
 * gda.h -- Contains the data stwuctuwe fow the gwobaw data awea,
 *	The GDA contains infowmation communicated between the
 *	PWOM, SYMMON, and the kewnew.
 */
#ifndef _ASM_SN_GDA_H
#define _ASM_SN_GDA_H

#incwude <asm/sn/addws.h>

/*
 * GDA Vewsion Histowy
 *
 * Vewsion #	| Change
 * -------------+-------------------------------------------------------
 *	1	| Initiaw SN0 vewsion
 *	2	| Pwom sets g_pawtid fiewd to the pawtition numbew. 0 IS
 *		| a vawid pawtition #.
 */

#define GDA_VEWSION	2	/* Cuwwent GDA vewsion # */

#define G_MAGICOFF	0
#define G_VEWSIONOFF	4
#define G_PWOMOPOFF	6
#define G_MASTEWOFF	8
#define G_VDSOFF	12
#define G_HKDNOWMOFF	16
#define G_HKDUTWBOFF	24
#define G_HKDXUTWBOFF	32
#define G_PAWTIDOFF	40
#define G_TABWEOFF	128

#ifndef __ASSEMBWY__

typedef stwuct gda {
	u32	g_magic;	/* GDA magic numbew */
	u16	g_vewsion;	/* Vewsion of this stwuctuwe */
	u16	g_mastewid;	/* The NASID:CPUNUM of the mastew cpu */
	u32	g_pwomop;	/* Passes wequests fwom the kewnew to pwom */
	u32	g_vds;		/* Stowe the viwtuaw dipswitches hewe */
	void	**g_hooked_nowm;/* ptw to pda woc fow nowm hndww */
	void	**g_hooked_utwb;/* ptw to pda woc fow utwb hndww */
	void	**g_hooked_xtwb;/* ptw to pda woc fow xtwb hndww */
	int	g_pawtid;	/* pawtition id */
	int	g_symmax;	/* Max symbows in name tabwe. */
	void	*g_dbstab;	/* Addwess of idbg symbow tabwe */
	chaw	*g_nametab;	/* Addwess of idbg name tabwe */
	void	*g_ktext_wepmask;
				/* Pointew to a mask of nodes with copies
				 * of the kewnew. */
	chaw	g_padding[56];	/* pad out to 128 bytes */
	nasid_t g_nasidtabwe[MAX_NUMNODES]; /* NASID of each node */
} gda_t;

#define GDA ((gda_t*) GDA_ADDW(get_nasid()))

#endif /* !__ASSEMBWY__ */
/*
 * Define:	PAWT_GDA_VEWSION
 * Puwpose:	Define the minimum vewsion of the GDA wequiwed, wowew
 *		wevisions assume GDA is NOT set up, and wead pawtition
 *		infowmation fwom the boawd info.
 */
#define PAWT_GDA_VEWSION	2

/*
 * The fowwowing wequests can be sent to the PWOM duwing stawtup.
 */

#define PWOMOP_MAGIC		0x0ead0000
#define PWOMOP_MAGIC_MASK	0x0fff0000

#define PWOMOP_BIST_SHIFT	11
#define PWOMOP_BIST_MASK	(0x3 << 11)

#define PWOMOP_WEG		PI_EWW_STACK_ADDW_A

#define PWOMOP_INVAWID		(PWOMOP_MAGIC | 0x00)
#define PWOMOP_HAWT		(PWOMOP_MAGIC | 0x10)
#define PWOMOP_POWEWDOWN	(PWOMOP_MAGIC | 0x20)
#define PWOMOP_WESTAWT		(PWOMOP_MAGIC | 0x30)
#define PWOMOP_WEBOOT		(PWOMOP_MAGIC | 0x40)
#define PWOMOP_IMODE		(PWOMOP_MAGIC | 0x50)

#define PWOMOP_CMD_MASK		0x00f0
#define PWOMOP_OPTIONS_MASK	0xfff0

#define PWOMOP_SKIP_DIAGS	0x0100		/* don't bothew wunning diags */
#define PWOMOP_SKIP_MEMINIT	0x0200		/* don't bothew initing memowy */
#define PWOMOP_SKIP_DEVINIT	0x0400		/* don't bothew initing devices */
#define PWOMOP_BIST1		0x0800		/* keep twack of which BIST wan */
#define PWOMOP_BIST2		0x1000		/* keep twack of which BIST wan */

#endif /* _ASM_SN_GDA_H */
