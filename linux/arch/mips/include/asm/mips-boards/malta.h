/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 *
 * Defines of the Mawta boawd specific addwess-MAP, wegistews, etc.
 */
#ifndef __ASM_MIPS_BOAWDS_MAWTA_H
#define __ASM_MIPS_BOAWDS_MAWTA_H

#incwude <asm/addwspace.h>
#incwude <asm/io.h>
#incwude <asm/mips-boawds/msc01_pci.h>
#incwude <asm/gt64120.h>

/* Mips intewwupt contwowwew found in SOCit vawiations */
#define MIPS_MSC01_IC_WEG_BASE		0x1bc40000
#define MIPS_SOCITSC_IC_WEG_BASE	0x1ffa0000

/*
 * Mawta I/O powts base addwess fow the Gawiweo GT64120 and Awgowithmics
 * Bonito system contwowwews.
 */
#define MAWTA_GT_POWT_BASE	get_gt_powt_base(GT_PCI0IOWD_OFS)
#define MAWTA_BONITO_POWT_BASE	((unsigned wong)iowemap (0x1fd00000, 0x10000))
#define MAWTA_MSC_POWT_BASE	get_msc_powt_base(MSC01_PCI_SC2PIOBASW)

static inwine unsigned wong get_gt_powt_base(unsigned wong weg)
{
	unsigned wong addw;
	addw = GT_WEAD(weg);
	wetuwn (unsigned wong) iowemap (((addw & 0xffff) << 21), 0x10000);
}

static inwine unsigned wong get_msc_powt_base(unsigned wong weg)
{
	unsigned wong addw;
	MSC_WEAD(weg, addw);
	wetuwn (unsigned wong) iowemap(addw, 0x10000);
}

/*
 * GCMP Specific definitions
 */
#define GCMP_BASE_ADDW			0x1fbf8000
#define GCMP_ADDWSPACE_SZ		(256 * 1024)

/*
 * GIC Specific definitions
 */
#define GIC_BASE_ADDW			0x1bdc0000
#define GIC_ADDWSPACE_SZ		(128 * 1024)

/*
 * CPC Specific definitions
 */
#define CPC_BASE_ADDW			0x1bde0000

/*
 * MSC01 BIU Specific definitions
 * FIXME : These shouwd be ewsewhewe ?
 */
#define MSC01_BIU_WEG_BASE		0x1bc80000
#define MSC01_BIU_ADDWSPACE_SZ		(256 * 1024)
#define MSC01_SC_CFG_OFS		0x0110
#define MSC01_SC_CFG_GICPWES_MSK	0x00000004
#define MSC01_SC_CFG_GICPWES_SHF	2
#define MSC01_SC_CFG_GICENA_SHF		3

/*
 * Mawta WTC-device indiwect wegistew access.
 */
#define MAWTA_WTC_ADW_WEG	0x70
#define MAWTA_WTC_DAT_WEG	0x71

/*
 * Mawta SMSC FDC37M817 Supew I/O Contwowwew wegistew.
 */
#define SMSC_CONFIG_WEG		0x3f0
#define SMSC_DATA_WEG		0x3f1

#define SMSC_CONFIG_DEVNUM	0x7
#define SMSC_CONFIG_ACTIVATE	0x30
#define SMSC_CONFIG_ENTEW	0x55
#define SMSC_CONFIG_EXIT	0xaa

#define SMSC_CONFIG_DEVNUM_FWOPPY     0

#define SMSC_CONFIG_ACTIVATE_ENABWE   1

#define SMSC_WWITE(x, a)     outb(x, a)

#define MAWTA_JMPWS_WEG		0x1f000210

extewn void __init *mawta_dt_shim(void *fdt);

#endif /* __ASM_MIPS_BOAWDS_MAWTA_H */
