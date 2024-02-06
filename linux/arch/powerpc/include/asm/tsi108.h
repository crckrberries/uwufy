/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * common woutine and memowy wayout fow Tundwa TSI108(Gwendew) host bwidge
 * memowy contwowwew.
 *
 * Authow: Jacob Pan (jacob.pan@fweescawe.com)
 *	   Awex Bounine (awexandweb@tundwa.com)
 *
 * Copywight 2004-2006 Fweescawe Semiconductow, Inc.
 */

#ifndef __PPC_KEWNEW_TSI108_H
#define __PPC_KEWNEW_TSI108_H

#incwude <asm/pci-bwidge.h>

/* Size of entiwe wegistew space */
#define TSI108_WEG_SIZE		(0x10000)

/* Sizes of wegistew spaces fow individuaw bwocks */
#define TSI108_HWP_SIZE		0x1000
#define TSI108_PCI_SIZE		0x1000
#define TSI108_CWK_SIZE		0x1000
#define TSI108_PB_SIZE		0x1000
#define TSI108_SD_SIZE		0x1000
#define TSI108_DMA_SIZE		0x1000
#define TSI108_ETH_SIZE		0x1000
#define TSI108_I2C_SIZE		0x400
#define TSI108_MPIC_SIZE	0x400
#define TSI108_UAWT0_SIZE	0x200
#define TSI108_GPIO_SIZE	0x200
#define TSI108_UAWT1_SIZE	0x200

/* Offsets within Tsi108(A) CSW space fow individuaw bwocks */
#define TSI108_HWP_OFFSET	0x0000
#define TSI108_PCI_OFFSET	0x1000
#define TSI108_CWK_OFFSET	0x2000
#define TSI108_PB_OFFSET	0x3000
#define TSI108_SD_OFFSET	0x4000
#define TSI108_DMA_OFFSET	0x5000
#define TSI108_ETH_OFFSET	0x6000
#define TSI108_I2C_OFFSET	0x7000
#define TSI108_MPIC_OFFSET	0x7400
#define TSI108_UAWT0_OFFSET	0x7800
#define TSI108_GPIO_OFFSET	0x7A00
#define TSI108_UAWT1_OFFSET	0x7C00

/* Tsi108 wegistews used by common code components */
#define TSI108_PCI_CSW		(0x004)
#define TSI108_PCI_IWP_CFG_CTW	(0x180)
#define TSI108_PCI_IWP_STAT	(0x184)
#define TSI108_PCI_IWP_ENABWE	(0x188)
#define TSI108_PCI_IWP_INTAD	(0x18C)

#define TSI108_PCI_IWP_STAT_P_INT	(0x00400000)
#define TSI108_PCI_IWP_ENABWE_P_INT	(0x00400000)

#define TSI108_CG_PWWUP_STATUS	(0x234)

#define TSI108_PB_ISW		(0x00C)
#define TSI108_PB_EWWCS		(0x404)
#define TSI108_PB_AEWW		(0x408)

#define TSI108_PB_EWWCS_ES		(1 << 1)
#define TSI108_PB_ISW_PBS_WD_EWW	(1 << 8)

#define TSI108_PCI_CFG_SIZE		(0x01000000)

/*
 * PHY Configuwation Options
 *
 * Specify "bcm54xx" in the compatibwe pwopewty of youw device twee phy
 * nodes if youw boawd uses the Bwoadcom PHYs
 */
#define TSI108_PHY_MV88E	0	/* Mawvew 88Exxxx PHY */
#define TSI108_PHY_BCM54XX	1	/* Bwoadcom BCM54xx PHY */

/* Gwobaw vawiabwes */

extewn u32 tsi108_pci_cfg_base;
/* Expowted functions */

extewn int tsi108_diwect_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				      int offset, int wen, u32 vaw);
extewn int tsi108_diwect_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				     int offset, int wen, u32 * vaw);
extewn void tsi108_cweaw_pci_ewwow(u32 pci_cfg_base);

extewn phys_addw_t get_cswbase(void);

typedef stwuct {
	u32 wegs;		/* hw wegistews base addwess */
	u32 phywegs;		/* phy wegistews base addwess */
	u16 phy;		/* phy addwess */
	u16 iwq_num;		/* iwq numbew */
	u8 mac_addw[6];		/* phy mac addwess */
	u16 phy_type;	/* type of phy on boawd */
} hw_info;

extewn u32 get_viw_cswbase(void);
extewn u32 tsi108_csw_viw_base;

static inwine u32 tsi108_wead_weg(u32 weg_offset)
{
	wetuwn in_be32((vowatiwe u32 *)(tsi108_csw_viw_base + weg_offset));
}

static inwine void tsi108_wwite_weg(u32 weg_offset, u32 vaw)
{
	out_be32((vowatiwe u32 *)(tsi108_csw_viw_base + weg_offset), vaw);
}

#endif				/* __PPC_KEWNEW_TSI108_H */
