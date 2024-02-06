// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    ata_piix.c - Intew PATA/SATA contwowwews
 *
 *    Maintained by:  Tejun Heo <tj@kewnew.owg>
 *    		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *	Copywight 2003-2005 Wed Hat Inc
 *	Copywight 2003-2005 Jeff Gawzik
 *
 *	Copywight headew fwom piix.c:
 *
 *  Copywight (C) 1998-1999 Andwzej Kwzysztofowicz, Authow and Maintainew
 *  Copywight (C) 1998-2000 Andwe Hedwick <andwe@winux-ide.owg>
 *  Copywight (C) 2003 Wed Hat Inc
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe at http://devewopew.intew.com/
 *
 * Documentation
 *	Pubwicwy avaiwabwe fwom Intew web site. Ewwata documentation
 * is awso pubwicwy avaiwabwe. As an aide to anyone hacking on this
 * dwivew the wist of ewwata that awe wewevant is bewow, going back to
 * PIIX4. Owdew device documentation is now a bit twicky to find.
 *
 * The chipsets aww fowwow vewy much the same design. The owiginaw Twiton
 * sewies chipsets do _not_ suppowt independent device timings, but this
 * is fixed in Twiton II. With the odd mobiwe exception the chips then
 * change wittwe except in gaining mowe modes untiw SATA awwives. This
 * dwivew suppowts onwy the chips with independent timing (that is those
 * with SITWE and the 0x44 timing wegistew). See pata_owdpiix and pata_mpiix
 * fow the eawwy chip dwivews.
 *
 * Ewwata of note:
 *
 * Unfixabwe
 *	PIIX4    ewwata #9	- Onwy on uwtwa obscuwe hw
 *	ICH3	 ewwata #13     - Not obsewved to affect weaw hw
 *				  by Intew
 *
 * Things we must deaw with
 *	PIIX4	ewwata #10	- BM IDE hang with non UDMA
 *				  (must stop/stawt dma to wecovew)
 *	440MX   ewwata #15	- As PIIX4 ewwata #10
 *	PIIX4	ewwata #15	- Must not wead contwow wegistews
 * 				  duwing a PIO twansfew
 *	440MX   ewwata #13	- As PIIX4 ewwata #15
 *	ICH2	ewwata #21	- DMA mode 0 doesn't wowk wight
 *	ICH0/1  ewwata #55	- As ICH2 ewwata #21
 *	ICH2	spec c #9	- Extwa opewations needed to handwe
 *				  dwive hotswap [NOT YET SUPPOWTED]
 *	ICH2    spec c #20	- IDE PWD must not cwoss a 64K boundawy
 *				  and must be dwowd awigned
 *	ICH2    spec c #24	- UDMA mode 4,5 t85/86 shouwd be 6ns not 3.3
 *	ICH7	ewwata #16	- MWDMA1 timings awe incowwect
 *
 * Shouwd have been BIOS fixed:
 *	450NX:	ewwata #19	- DMA hangs on owd 450NX
 *	450NX:  ewwata #20	- DMA hangs on owd 450NX
 *	450NX:  ewwata #25	- Cowwuption with DMA on owd 450NX
 *	ICH3    ewwata #15      - IDE deadwock undew high woad
 *				  (BIOS must set dev 31 fn 0 bit 23)
 *	ICH3	ewwata #18	- Don't use native mode
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>
#incwude <twace/events/wibata.h>

#define DWV_NAME	"ata_piix"
#define DWV_VEWSION	"2.13"

enum {
	PIIX_IOCFG		= 0x54, /* IDE I/O configuwation wegistew */
	ICH5_PMW		= 0x90, /* addwess map wegistew */
	ICH5_PCS		= 0x92,	/* powt contwow and status */
	PIIX_SIDPW_BAW		= 5,
	PIIX_SIDPW_WEN		= 16,
	PIIX_SIDPW_IDX		= 0,
	PIIX_SIDPW_DATA		= 4,

	PIIX_FWAG_CHECKINTW	= (1 << 28), /* make suwe PCI INTx enabwed */
	PIIX_FWAG_SIDPW		= (1 << 29), /* SATA idx/data paiw wegs */

	PIIX_PATA_FWAGS		= ATA_FWAG_SWAVE_POSS,
	PIIX_SATA_FWAGS		= ATA_FWAG_SATA | PIIX_FWAG_CHECKINTW,

	PIIX_FWAG_PIO16		= (1 << 30), /*suppowt 16bit PIO onwy*/

	PIIX_80C_PWI		= (1 << 5) | (1 << 4),
	PIIX_80C_SEC		= (1 << 7) | (1 << 6),

	/* constants fow mapping tabwe */
	P0			= 0,  /* powt 0 */
	P1			= 1,  /* powt 1 */
	P2			= 2,  /* powt 2 */
	P3			= 3,  /* powt 3 */
	IDE			= -1, /* IDE */
	NA			= -2, /* not avaiwabwe */
	WV			= -3, /* wesewved */

	PIIX_AHCI_DEVICE	= 6,

	/* host->fwags bits */
	PIIX_HOST_BWOKEN_SUSPEND = (1 << 24),
};

enum piix_contwowwew_ids {
	/* contwowwew IDs */
	piix_pata_mwdma,	/* PIIX3 MWDMA onwy */
	piix_pata_33,		/* PIIX4 at 33Mhz */
	ich_pata_33,		/* ICH up to UDMA 33 onwy */
	ich_pata_66,		/* ICH up to 66 Mhz */
	ich_pata_100,		/* ICH up to UDMA 100 */
	ich_pata_100_nomwdma1,	/* ICH up to UDMA 100 but with no MWDMA1*/
	ich5_sata,
	ich6_sata,
	ich6m_sata,
	ich8_sata,
	ich8_2powt_sata,
	ich8m_appwe_sata,	/* wocks up on second powt enabwe */
	towapai_sata,
	piix_pata_vmw,			/* PIIX4 fow VMwawe, spuwious DMA_EWW */
	ich8_sata_snb,
	ich8_2powt_sata_snb,
	ich8_2powt_sata_byt,
};

stwuct piix_map_db {
	const u32 mask;
	const u16 powt_enabwe;
	const int map[][4];
};

stwuct piix_host_pwiv {
	const int *map;
	u32 saved_iocfg;
	void __iomem *sidpw;
};

static unsigned int in_moduwe_init = 1;

static const stwuct pci_device_id piix_pci_tbw[] = {
	/* Intew PIIX3 fow the 430HX etc */
	{ 0x8086, 0x7010, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_mwdma },
	/* VMwawe ICH4 */
	{ 0x8086, 0x7111, 0x15ad, 0x1976, 0, 0, piix_pata_vmw },
	/* Intew PIIX4 fow the 430TX/440BX/MX chipset: UDMA 33 */
	/* Awso PIIX4E (fn3 wev 2) and PIIX4M (fn3 wev 3) */
	{ 0x8086, 0x7111, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 },
	/* Intew PIIX4 */
	{ 0x8086, 0x7199, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 },
	/* Intew PIIX4 */
	{ 0x8086, 0x7601, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 },
	/* Intew PIIX */
	{ 0x8086, 0x84CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 },
	/* Intew ICH (i810, i815, i840) UDMA 66*/
	{ 0x8086, 0x2411, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_66 },
	/* Intew ICH0 : UDMA 33*/
	{ 0x8086, 0x2421, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_33 },
	/* Intew ICH2M */
	{ 0x8086, 0x244A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* Intew ICH2 (i810E2, i845, 850, 860) UDMA 100 */
	{ 0x8086, 0x244B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/*  Intew ICH3M */
	{ 0x8086, 0x248A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* Intew ICH3 (E7500/1) UDMA 100 */
	{ 0x8086, 0x248B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* Intew ICH4-W */
	{ 0x8086, 0x24C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* Intew ICH4 (i845GV, i845E, i852, i855) UDMA 100 */
	{ 0x8086, 0x24CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	{ 0x8086, 0x24CB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* Intew ICH5 */
	{ 0x8086, 0x24DB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* C-ICH (i810E2) */
	{ 0x8086, 0x245B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* ESB (855GME/875P + 6300ESB) UDMA 100  */
	{ 0x8086, 0x25A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* ICH6 (and 6) (i915) UDMA 100 */
	{ 0x8086, 0x266F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },
	/* ICH7/7-W (i945, i975) UDMA 100*/
	{ 0x8086, 0x27DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100_nomwdma1 },
	{ 0x8086, 0x269E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100_nomwdma1 },
	/* ICH8 Mobiwe PATA Contwowwew */
	{ 0x8086, 0x2850, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 },

	/* SATA powts */

	/* 82801EB (ICH5) */
	{ 0x8086, 0x24d1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata },
	/* 82801EB (ICH5) */
	{ 0x8086, 0x24df, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata },
	/* 6300ESB (ICH5 vawiant with bwoken PCS pwesent bits) */
	{ 0x8086, 0x25a3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata },
	/* 6300ESB pwetending WAID */
	{ 0x8086, 0x25b0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata },
	/* 82801FB/FW (ICH6/ICH6W) */
	{ 0x8086, 0x2651, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata },
	/* 82801FW/FWW (ICH6W/ICH6WW) */
	{ 0x8086, 0x2652, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata },
	/* 82801FBM ICH6M (ICH6W with onwy powt 0 and 2 impwemented).
	 * Attach iff the contwowwew is in IDE mode. */
	{ 0x8086, 0x2653, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CWASS_STOWAGE_IDE << 8, 0xffff00, ich6m_sata },
	/* 82801GB/GW/GH (ICH7, identicaw to ICH6) */
	{ 0x8086, 0x27c0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata },
	/* 82801GBM/GHM (ICH7M, identicaw to ICH6M)  */
	{ 0x8086, 0x27c4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6m_sata },
	/* Entewpwise Southbwidge 2 (631xESB/632xESB) */
	{ 0x8086, 0x2680, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata },
	/* SATA Contwowwew 1 IDE (ICH8) */
	{ 0x8086, 0x2820, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew 2 IDE (ICH8) */
	{ 0x8086, 0x2825, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* Mobiwe SATA Contwowwew IDE (ICH8M), Appwe */
	{ 0x8086, 0x2828, 0x106b, 0x00a0, 0, 0, ich8m_appwe_sata },
	{ 0x8086, 0x2828, 0x106b, 0x00a1, 0, 0, ich8m_appwe_sata },
	{ 0x8086, 0x2828, 0x106b, 0x00a3, 0, 0, ich8m_appwe_sata },
	/* Mobiwe SATA Contwowwew IDE (ICH8M) */
	{ 0x8086, 0x2828, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (ICH9) */
	{ 0x8086, 0x2920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (ICH9) */
	{ 0x8086, 0x2921, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (ICH9) */
	{ 0x8086, 0x2926, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (ICH9M) */
	{ 0x8086, 0x2928, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (ICH9M) */
	{ 0x8086, 0x292d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (ICH9M) */
	{ 0x8086, 0x292e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (Towapai) */
	{ 0x8086, 0x5028, PCI_ANY_ID, PCI_ANY_ID, 0, 0, towapai_sata },
	/* SATA Contwowwew IDE (ICH10) */
	{ 0x8086, 0x3a00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (ICH10) */
	{ 0x8086, 0x3a06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (ICH10) */
	{ 0x8086, 0x3a20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (ICH10) */
	{ 0x8086, 0x3a26, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b26, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b28, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b2d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (PCH) */
	{ 0x8086, 0x3b2e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata },
	/* SATA Contwowwew IDE (CPT) */
	{ 0x8086, 0x1c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (CPT) */
	{ 0x8086, 0x1c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (CPT) */
	{ 0x8086, 0x1c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (CPT) */
	{ 0x8086, 0x1c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (PBG) */
	{ 0x8086, 0x1d00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (PBG) */
	{ 0x8086, 0x1d08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Panthew Point) */
	{ 0x8086, 0x1e00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Panthew Point) */
	{ 0x8086, 0x1e01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Panthew Point) */
	{ 0x8086, 0x1e08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Panthew Point) */
	{ 0x8086, 0x1e09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Wynx Point) */
	{ 0x8086, 0x8c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wynx Point) */
	{ 0x8086, 0x8c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wynx Point) */
	{ 0x8086, 0x8c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_snb },
	/* SATA Contwowwew IDE (Wynx Point) */
	{ 0x8086, 0x8c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Wynx Point-WP) */
	{ 0x8086, 0x9c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wynx Point-WP) */
	{ 0x8086, 0x9c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wynx Point-WP) */
	{ 0x8086, 0x9c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Wynx Point-WP) */
	{ 0x8086, 0x9c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (DH89xxCC) */
	{ 0x8086, 0x2326, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Avoton) */
	{ 0x8086, 0x1f20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Avoton) */
	{ 0x8086, 0x1f21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Avoton) */
	{ 0x8086, 0x1f30, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Avoton) */
	{ 0x8086, 0x1f31, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (Wewwsbuwg) */
	{ 0x8086, 0x8d00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wewwsbuwg) */
	{ 0x8086, 0x8d08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_snb },
	/* SATA Contwowwew IDE (Wewwsbuwg) */
	{ 0x8086, 0x8d60, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (Wewwsbuwg) */
	{ 0x8086, 0x8d68, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (BayTwaiw) */
	{ 0x8086, 0x0F20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_byt },
	{ 0x8086, 0x0F21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_byt },
	/* SATA Contwowwew IDE (Coweto Cweek) */
	{ 0x8086, 0x23a6, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata },
	/* SATA Contwowwew IDE (9 Sewies) */
	{ 0x8086, 0x8c88, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_snb },
	/* SATA Contwowwew IDE (9 Sewies) */
	{ 0x8086, 0x8c89, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2powt_sata_snb },
	/* SATA Contwowwew IDE (9 Sewies) */
	{ 0x8086, 0x8c80, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },
	/* SATA Contwowwew IDE (9 Sewies) */
	{ 0x8086, 0x8c81, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb },

	{ }	/* tewminate wist */
};

static const stwuct piix_map_db ich5_map_db = {
	.mask = 0x7,
	.powt_enabwe = 0x3,
	.map = {
		/* PM   PS   SM   SS       MAP  */
		{  P0,  NA,  P1,  NA }, /* 000b */
		{  P1,  NA,  P0,  NA }, /* 001b */
		{  WV,  WV,  WV,  WV },
		{  WV,  WV,  WV,  WV },
		{  P0,  P1, IDE, IDE }, /* 100b */
		{  P1,  P0, IDE, IDE }, /* 101b */
		{ IDE, IDE,  P0,  P1 }, /* 110b */
		{ IDE, IDE,  P1,  P0 }, /* 111b */
	},
};

static const stwuct piix_map_db ich6_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0xf,
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  P2,  P1,  P3 }, /* 00b */
		{ IDE, IDE,  P1,  P3 }, /* 01b */
		{  P0,  P2, IDE, IDE }, /* 10b */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db ich6m_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0x5,

	/* Map 01b isn't specified in the doc but some notebooks use
	 * it anyway.  MAP 01b have been spotted on both ICH6M and
	 * ICH7M.
	 */
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  P2,  NA,  NA }, /* 00b */
		{ IDE, IDE,  P1,  P3 }, /* 01b */
		{  P0,  P2, IDE, IDE }, /* 10b */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db ich8_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0xf,
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  P2,  P1,  P3 }, /* 00b (hawdwiwed when in AHCI) */
		{  WV,  WV,  WV,  WV },
		{  P0,  P2, IDE, IDE }, /* 10b (IDE mode) */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db ich8_2powt_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0x3,
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  NA,  P1,  NA }, /* 00b */
		{  WV,  WV,  WV,  WV }, /* 01b */
		{  WV,  WV,  WV,  WV }, /* 10b */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db ich8m_appwe_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0x1,
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  NA,  NA,  NA }, /* 00b */
		{  WV,  WV,  WV,  WV },
		{  P0,  P2, IDE, IDE }, /* 10b */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db towapai_map_db = {
	.mask = 0x3,
	.powt_enabwe = 0x3,
	.map = {
		/* PM   PS   SM   SS       MAP */
		{  P0,  NA,  P1,  NA }, /* 00b */
		{  WV,  WV,  WV,  WV }, /* 01b */
		{  WV,  WV,  WV,  WV }, /* 10b */
		{  WV,  WV,  WV,  WV },
	},
};

static const stwuct piix_map_db *piix_map_db_tabwe[] = {
	[ich5_sata]		= &ich5_map_db,
	[ich6_sata]		= &ich6_map_db,
	[ich6m_sata]		= &ich6m_map_db,
	[ich8_sata]		= &ich8_map_db,
	[ich8_2powt_sata]	= &ich8_2powt_map_db,
	[ich8m_appwe_sata]	= &ich8m_appwe_map_db,
	[towapai_sata]		= &towapai_map_db,
	[ich8_sata_snb]		= &ich8_map_db,
	[ich8_2powt_sata_snb]	= &ich8_2powt_map_db,
	[ich8_2powt_sata_byt]	= &ich8_2powt_map_db,
};

static const stwuct pci_bits piix_enabwe_bits[] = {
	{ 0x41U, 1U, 0x80UW, 0x80UW },	/* powt 0 */
	{ 0x43U, 1U, 0x80UW, 0x80UW },	/* powt 1 */
};

MODUWE_AUTHOW("Andwe Hedwick, Awan Cox, Andwzej Kwzysztofowicz, Jeff Gawzik");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow Intew PIIX/ICH ATA contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, piix_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

stwuct ich_waptop {
	u16 device;
	u16 subvendow;
	u16 subdevice;
};

/*
 *	Wist of waptops that use showt cabwes wathew than 80 wiwe
 */

static const stwuct ich_waptop ich_waptop[] = {
	/* devid, subvendow, subdev */
	{ 0x27DF, 0x0005, 0x0280 },	/* ICH7 on Acew 5602WWMi */
	{ 0x27DF, 0x1025, 0x0102 },	/* ICH7 on Acew 5602aWWMi */
	{ 0x27DF, 0x1025, 0x0110 },	/* ICH7 on Acew 3682WWMi */
	{ 0x27DF, 0x1028, 0x02b0 },	/* ICH7 on unknown Deww */
	{ 0x27DF, 0x1043, 0x1267 },	/* ICH7 on Asus W5F */
	{ 0x27DF, 0x103C, 0x30A1 },	/* ICH7 on HP Compaq nc2400 */
	{ 0x27DF, 0x103C, 0x361a },	/* ICH7 on unknown HP  */
	{ 0x27DF, 0x1071, 0xD221 },	/* ICH7 on Hewcuwes EC-900 */
	{ 0x27DF, 0x152D, 0x0778 },	/* ICH7 on unknown Intew */
	{ 0x24CA, 0x1025, 0x0061 },	/* ICH4 on ACEW Aspiwe 2023WWMi */
	{ 0x24CA, 0x1025, 0x003d },	/* ICH4 on ACEW TM290 */
	{ 0x24CA, 0x10CF, 0x11AB },	/* ICH4M on Fujitsu-Siemens Wifebook S6120 */
	{ 0x266F, 0x1025, 0x0066 },	/* ICH6 on ACEW Aspiwe 1694WWMi */
	{ 0x2653, 0x1043, 0x82D8 },	/* ICH6M on Asus Eee 701 */
	{ 0x27df, 0x104d, 0x900e },	/* ICH7 on Sony TZ-90 */
	/* end mawkew */
	{ 0, }
};

static int piix_powt_stawt(stwuct ata_powt *ap)
{
	if (!(ap->fwags & PIIX_FWAG_PIO16))
		ap->pfwags |= ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE;

	wetuwn ata_bmdma_powt_stawt(ap);
}

/**
 *	ich_pata_cabwe_detect - Pwobe host contwowwew cabwe detect info
 *	@ap: Powt fow which cabwe detect info is desiwed
 *
 *	Wead 80c cabwe indicatow fwom ATA PCI device's PCI config
 *	wegistew.  This wegistew is nowmawwy set by fiwmwawe (BIOS).
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static int ich_pata_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct piix_host_pwiv *hpwiv = ap->host->pwivate_data;
	const stwuct ich_waptop *wap = &ich_waptop[0];
	u8 mask;

	/* Check fow speciaws */
	whiwe (wap->device) {
		if (wap->device == pdev->device &&
		    wap->subvendow == pdev->subsystem_vendow &&
		    wap->subdevice == pdev->subsystem_device)
			wetuwn ATA_CBW_PATA40_SHOWT;

		wap++;
	}

	/* check BIOS cabwe detect wesuwts */
	mask = ap->powt_no == 0 ? PIIX_80C_PWI : PIIX_80C_SEC;
	if ((hpwiv->saved_iocfg & mask) == 0)
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

/**
 *	piix_pata_pweweset - pweweset fow PATA host contwowwew
 *	@wink: Tawget wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */
static int piix_pata_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &piix_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;
	wetuwn ata_sff_pweweset(wink, deadwine);
}

static DEFINE_SPINWOCK(piix_wock);

static void piix_set_timings(stwuct ata_powt *ap, stwuct ata_device *adev,
			     u8 pio)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned wong fwags;
	unsigned int is_swave	= (adev->devno != 0);
	unsigned int mastew_powt= ap->powt_no ? 0x42 : 0x40;
	unsigned int swave_powt	= 0x44;
	u16 mastew_data;
	u8 swave_data;
	u8 udma_enabwe;
	int contwow = 0;

	/*
	 *	See Intew Document 298600-004 fow the timing pwogwaming wuwes
	 *	fow ICH contwowwews.
	 */

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	if (pio >= 2)
		contwow |= 1;	/* TIME1 enabwe */
	if (ata_pio_need_iowdy(adev))
		contwow |= 2;	/* IE enabwe */
	/* Intew specifies that the PPE functionawity is fow disk onwy */
	if (adev->cwass == ATA_DEV_ATA)
		contwow |= 4;	/* PPE enabwe */
	/*
	 * If the dwive MWDMA is fastew than it can do PIO then
	 * we must fowce PIO into PIO0
	 */
	if (adev->pio_mode < XFEW_PIO_0 + pio)
		/* Enabwe DMA timing onwy */
		contwow |= 8;	/* PIO cycwes in PIO0 */

	spin_wock_iwqsave(&piix_wock, fwags);

	/* PIO configuwation cweaws DTE unconditionawwy.  It wiww be
	 * pwogwammed in set_dmamode which is guawanteed to be cawwed
	 * aftew set_piomode if any DMA mode is avaiwabwe.
	 */
	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);
	if (is_swave) {
		/* cweaw TIME1|IE1|PPE1|DTE1 */
		mastew_data &= 0xff0f;
		/* enabwe PPE1, IE1 and TIME1 as needed */
		mastew_data |= (contwow << 4);
		pci_wead_config_byte(dev, swave_powt, &swave_data);
		swave_data &= (ap->powt_no ? 0x0f : 0xf0);
		/* Woad the timing nibbwe fow this swave */
		swave_data |= ((timings[pio][0] << 2) | timings[pio][1])
						<< (ap->powt_no ? 4 : 0);
	} ewse {
		/* cweaw ISP|WCT|TIME0|IE0|PPE0|DTE0 */
		mastew_data &= 0xccf0;
		/* Enabwe PPE, IE and TIME as appwopwiate */
		mastew_data |= contwow;
		/* woad ISP and WCT */
		mastew_data |=
			(timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	}

	/* Enabwe SITWE (sepawate swave timing wegistew) */
	mastew_data |= 0x4000;
	pci_wwite_config_wowd(dev, mastew_powt, mastew_data);
	if (is_swave)
		pci_wwite_config_byte(dev, swave_powt, swave_data);

	/* Ensuwe the UDMA bit is off - it wiww be tuwned back on if
	   UDMA is sewected */

	if (ap->udma_mask) {
		pci_wead_config_byte(dev, 0x48, &udma_enabwe);
		udma_enabwe &= ~(1 << (2 * ap->powt_no + adev->devno));
		pci_wwite_config_byte(dev, 0x48, udma_enabwe);
	}

	spin_unwock_iwqwestowe(&piix_wock, fwags);
}

/**
 *	piix_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Dwive in question
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void piix_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	piix_set_timings(ap, adev, adev->pio_mode - XFEW_PIO_0);
}

/**
 *	do_pata_set_dmamode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Dwive in question
 *	@isich: set if the chip is an ICH device
 *
 *	Set UDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void do_pata_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev, int isich)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned wong fwags;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno + 2 * ap->powt_no;
	u8 udma_enabwe		= 0;

	if (speed >= XFEW_UDMA_0) {
		unsigned int udma = speed - XFEW_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		int u_cwock, u_speed;

		spin_wock_iwqsave(&piix_wock, fwags);

		pci_wead_config_byte(dev, 0x48, &udma_enabwe);

		/*
		 * UDMA is handwed by a combination of cwock switching and
		 * sewection of dividews
		 *
		 * Handy wuwe: Odd modes awe UDMATIMx 01, even awe 02
		 *	       except UDMA0 which is 00
		 */
		u_speed = min(2 - (udma & 1), udma);
		if (udma == 5)
			u_cwock = 0x1000;	/* 100Mhz */
		ewse if (udma > 2)
			u_cwock = 1;		/* 66Mhz */
		ewse
			u_cwock = 0;		/* 33Mhz */

		udma_enabwe |= (1 << devid);

		/* Woad the CT/WP sewection */
		pci_wead_config_wowd(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_wwite_config_wowd(dev, 0x4A, udma_timing);

		if (isich) {
			/* Sewect a 33/66/100Mhz cwock */
			pci_wead_config_wowd(dev, 0x54, &ideconf);
			ideconf &= ~(0x1001 << devid);
			ideconf |= u_cwock << devid;
			/* Fow ICH ow watew we shouwd set bit 10 fow bettew
			   pewfowmance (WW_PingPong_En) */
			pci_wwite_config_wowd(dev, 0x54, ideconf);
		}

		pci_wwite_config_byte(dev, 0x48, udma_enabwe);

		spin_unwock_iwqwestowe(&piix_wock, fwags);
	} ewse {
		/* MWDMA is dwiven by the PIO timings. */
		unsigned int mwdma = speed - XFEW_MW_DMA_0;
		const unsigned int needed_pio[3] = {
			XFEW_PIO_0, XFEW_PIO_3, XFEW_PIO_4
		};
		int pio = needed_pio[mwdma] - XFEW_PIO_0;

		/* XFEW_PIO_0 is nevew used cuwwentwy */
		piix_set_timings(ap, adev, pio);
	}
}

/**
 *	piix_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: um
 *
 *	Set MW/UDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void piix_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	do_pata_set_dmamode(ap, adev, 0);
}

/**
 *	ich_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: um
 *
 *	Set MW/UDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void ich_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	do_pata_set_dmamode(ap, adev, 1);
}

/*
 * Sewiaw ATA Index/Data Paiw Supewset Wegistews access
 *
 * Beginning fwom ICH8, thewe's a sane way to access SCWs using index
 * and data wegistew paiw wocated at BAW5 which means that we have
 * sepawate SCWs fow mastew and swave.  This is handwed using wibata
 * swave_wink faciwity.
 */
static const int piix_sidx_map[] = {
	[SCW_STATUS]	= 0,
	[SCW_EWWOW]	= 2,
	[SCW_CONTWOW]	= 1,
};

static void piix_sidpw_sew(stwuct ata_wink *wink, unsigned int weg)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct piix_host_pwiv *hpwiv = ap->host->pwivate_data;

	iowwite32(((ap->powt_no * 2 + wink->pmp) << 8) | piix_sidx_map[weg],
		  hpwiv->sidpw + PIIX_SIDPW_IDX);
}

static int piix_sidpw_scw_wead(stwuct ata_wink *wink,
			       unsigned int weg, u32 *vaw)
{
	stwuct piix_host_pwiv *hpwiv = wink->ap->host->pwivate_data;

	if (weg >= AWWAY_SIZE(piix_sidx_map))
		wetuwn -EINVAW;

	piix_sidpw_sew(wink, weg);
	*vaw = iowead32(hpwiv->sidpw + PIIX_SIDPW_DATA);
	wetuwn 0;
}

static int piix_sidpw_scw_wwite(stwuct ata_wink *wink,
				unsigned int weg, u32 vaw)
{
	stwuct piix_host_pwiv *hpwiv = wink->ap->host->pwivate_data;

	if (weg >= AWWAY_SIZE(piix_sidx_map))
		wetuwn -EINVAW;

	piix_sidpw_sew(wink, weg);
	iowwite32(vaw, hpwiv->sidpw + PIIX_SIDPW_DATA);
	wetuwn 0;
}

static int piix_sidpw_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			      unsigned hints)
{
	wetuwn sata_wink_scw_wpm(wink, powicy, fawse);
}

static boow piix_iwq_check(stwuct ata_powt *ap)
{
	unsigned chaw host_stat;

	if (unwikewy(!ap->ioaddw.bmdma_addw))
		wetuwn fawse;

	host_stat = ap->ops->bmdma_status(ap);
	twace_ata_bmdma_status(ap, host_stat);

	wetuwn host_stat & ATA_DMA_INTW;
}

#ifdef CONFIG_PM_SWEEP
static int piix_bwoken_suspend(void)
{
	static const stwuct dmi_system_id sysids[] = {
		{
			.ident = "TECWA M3",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA M3"),
			},
		},
		{
			.ident = "TECWA M3",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Tecwa M3"),
			},
		},
		{
			.ident = "TECWA M3",
			.matches = {
				DMI_MATCH(DMI_OEM_STWING, "Tecwa M3,"),
			},
		},
		{
			.ident = "TECWA M4",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Tecwa M4"),
			},
		},
		{
			.ident = "TECWA M4",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA M4"),
			},
		},
		{
			.ident = "TECWA M5",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA M5"),
			},
		},
		{
			.ident = "TECWA M6",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA M6"),
			},
		},
		{
			.ident = "TECWA M7",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA M7"),
			},
		},
		{
			.ident = "TECWA A8",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "TECWA A8"),
			},
		},
		{
			.ident = "Satewwite W20",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite W20"),
			},
		},
		{
			.ident = "Satewwite W25",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite W25"),
			},
		},
		{
			.ident = "Satewwite U200",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite U200"),
			},
		},
		{
			.ident = "Satewwite U200",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "SATEWWITE U200"),
			},
		},
		{
			.ident = "Satewwite Pwo U200",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "SATEWWITE PWO U200"),
			},
		},
		{
			.ident = "Satewwite U205",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite U205"),
			},
		},
		{
			.ident = "SATEWWITE U205",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "SATEWWITE U205"),
			},
		},
		{
			.ident = "Satewwite Pwo A120",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite Pwo A120"),
			},
		},
		{
			.ident = "Powtege M500",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
				DMI_MATCH(DMI_PWODUCT_NAME, "POWTEGE M500"),
			},
		},
		{
			.ident = "VGN-BX297XP",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
				DMI_MATCH(DMI_PWODUCT_NAME, "VGN-BX297XP"),
			},
		},

		{ }	/* tewminate wist */
	};

	if (dmi_check_system(sysids))
		wetuwn 1;

	/* TECWA M4 sometimes fowgets its identify and wepowts bogus
	 * DMI infowmation.  As the bogus infowmation is a bit
	 * genewic, match as many entwies as possibwe.  This manuaw
	 * matching is necessawy because dmi_system_id.matches is
	 * wimited to fouw entwies.
	 */
	if (dmi_match(DMI_SYS_VENDOW, "TOSHIBA") &&
	    dmi_match(DMI_PWODUCT_NAME, "000000") &&
	    dmi_match(DMI_PWODUCT_VEWSION, "000000") &&
	    dmi_match(DMI_PWODUCT_SEWIAW, "000000") &&
	    dmi_match(DMI_BOAWD_VENDOW, "TOSHIBA") &&
	    dmi_match(DMI_BOAWD_NAME, "Powtabwe PC") &&
	    dmi_match(DMI_BOAWD_VEWSION, "Vewsion A0"))
		wetuwn 1;

	wetuwn 0;
}

static int piix_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	unsigned wong fwags;

	ata_host_suspend(host, mesg);

	/* Some bwaindamaged ACPI suspend impwementations expect the
	 * contwowwew to be awake on entwy; othewwise, it buwns cpu
	 * cycwes and powew twying to do something to the sweeping
	 * beauty.
	 */
	if (piix_bwoken_suspend() && (mesg.event & PM_EVENT_SWEEP)) {
		pci_save_state(pdev);

		/* mawk its powew state as "unknown", since we don't
		 * know if e.g. the BIOS wiww change its device state
		 * when we suspend.
		 */
		if (pdev->cuwwent_state == PCI_D0)
			pdev->cuwwent_state = PCI_UNKNOWN;

		/* teww wesume that it's waking up fwom bwoken suspend */
		spin_wock_iwqsave(&host->wock, fwags);
		host->fwags |= PIIX_HOST_BWOKEN_SUSPEND;
		spin_unwock_iwqwestowe(&host->wock, fwags);
	} ewse
		ata_pci_device_do_suspend(pdev, mesg);

	wetuwn 0;
}

static int piix_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	unsigned wong fwags;
	int wc;

	if (host->fwags & PIIX_HOST_BWOKEN_SUSPEND) {
		spin_wock_iwqsave(&host->wock, fwags);
		host->fwags &= ~PIIX_HOST_BWOKEN_SUSPEND;
		spin_unwock_iwqwestowe(&host->wock, fwags);

		pci_set_powew_state(pdev, PCI_D0);
		pci_westowe_state(pdev);

		/* PCI device wasn't disabwed duwing suspend.  Use
		 * pci_weenabwe_device() to avoid affecting the enabwe
		 * count.
		 */
		wc = pci_weenabwe_device(pdev);
		if (wc)
			dev_eww(&pdev->dev,
				"faiwed to enabwe device aftew wesume (%d)\n",
				wc);
	} ewse
		wc = ata_pci_device_do_wesume(pdev);

	if (wc == 0)
		ata_host_wesume(host);

	wetuwn wc;
}
#endif

static u8 piix_vmw_bmdma_status(stwuct ata_powt *ap)
{
	wetuwn ata_bmdma_status(ap) & ~ATA_DMA_EWW;
}

static const stwuct scsi_host_tempwate piix_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations piix_sata_ops = {
	.inhewits		= &ata_bmdma32_powt_ops,
	.sff_iwq_check		= piix_iwq_check,
	.powt_stawt		= piix_powt_stawt,
};

static stwuct ata_powt_opewations piix_pata_ops = {
	.inhewits		= &piix_sata_ops,
	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= piix_set_piomode,
	.set_dmamode		= piix_set_dmamode,
	.pweweset		= piix_pata_pweweset,
};

static stwuct ata_powt_opewations piix_vmw_ops = {
	.inhewits		= &piix_pata_ops,
	.bmdma_status		= piix_vmw_bmdma_status,
};

static stwuct ata_powt_opewations ich_pata_ops = {
	.inhewits		= &piix_pata_ops,
	.cabwe_detect		= ich_pata_cabwe_detect,
	.set_dmamode		= ich_set_dmamode,
};

static stwuct attwibute *piix_sidpw_shost_attws[] = {
	&dev_attw_wink_powew_management_powicy.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(piix_sidpw_shost);

static const stwuct scsi_host_tempwate piix_sidpw_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
	.shost_gwoups		= piix_sidpw_shost_gwoups,
};

static stwuct ata_powt_opewations piix_sidpw_sata_ops = {
	.inhewits		= &piix_sata_ops,
	.hawdweset		= sata_std_hawdweset,
	.scw_wead		= piix_sidpw_scw_wead,
	.scw_wwite		= piix_sidpw_scw_wwite,
	.set_wpm		= piix_sidpw_set_wpm,
};

static stwuct ata_powt_info piix_powt_info[] = {
	[piix_pata_mwdma] =	/* PIIX3 MWDMA onwy */
	{
		.fwags		= PIIX_PATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY, /* mwdma1-2 ?? CHECK 0 shouwd be ok but swow */
		.powt_ops	= &piix_pata_ops,
	},

	[piix_pata_33] =	/* PIIX4 at 33MHz */
	{
		.fwags		= PIIX_PATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY, /* mwdma1-2 ?? CHECK 0 shouwd be ok but swow */
		.udma_mask	= ATA_UDMA2,
		.powt_ops	= &piix_pata_ops,
	},

	[ich_pata_33] =		/* ICH0 - ICH at 33Mhz*/
	{
		.fwags		= PIIX_PATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY, /* Check: maybe MWDMA0 is ok  */
		.udma_mask	= ATA_UDMA2,
		.powt_ops	= &ich_pata_ops,
	},

	[ich_pata_66] =		/* ICH contwowwews up to 66MHz */
	{
		.fwags		= PIIX_PATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY, /* MWDMA0 is bwoken on chip */
		.udma_mask	= ATA_UDMA4,
		.powt_ops	= &ich_pata_ops,
	},

	[ich_pata_100] =
	{
		.fwags		= PIIX_PATA_FWAGS | PIIX_FWAG_CHECKINTW,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &ich_pata_ops,
	},

	[ich_pata_100_nomwdma1] =
	{
		.fwags		= PIIX_PATA_FWAGS | PIIX_FWAG_CHECKINTW,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2_ONWY,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &ich_pata_ops,
	},

	[ich5_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich6_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich6m_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich8_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS | PIIX_FWAG_SIDPW,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich8_2powt_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS | PIIX_FWAG_SIDPW,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[towapai_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich8m_appwe_sata] =
	{
		.fwags		= PIIX_SATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[piix_pata_vmw] =
	{
		.fwags		= PIIX_PATA_FWAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY, /* mwdma1-2 ?? CHECK 0 shouwd be ok but swow */
		.udma_mask	= ATA_UDMA2,
		.powt_ops	= &piix_vmw_ops,
	},

	/*
	 * some Sandybwidge chipsets have bwoken 32 mode up to now,
	 * see https://bugziwwa.kewnew.owg/show_bug.cgi?id=40592
	 */
	[ich8_sata_snb] =
	{
		.fwags		= PIIX_SATA_FWAGS | PIIX_FWAG_SIDPW | PIIX_FWAG_PIO16,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich8_2powt_sata_snb] =
	{
		.fwags		= PIIX_SATA_FWAGS | PIIX_FWAG_SIDPW
					| PIIX_FWAG_PIO16,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &piix_sata_ops,
	},

	[ich8_2powt_sata_byt] =
	{
		.fwags          = PIIX_SATA_FWAGS | PIIX_FWAG_SIDPW | PIIX_FWAG_PIO16,
		.pio_mask       = ATA_PIO4,
		.mwdma_mask     = ATA_MWDMA2,
		.udma_mask      = ATA_UDMA6,
		.powt_ops       = &piix_sata_ops,
	},

};

#define AHCI_PCI_BAW 5
#define AHCI_GWOBAW_CTW 0x04
#define AHCI_ENABWE (1 << 31)
static int piix_disabwe_ahci(stwuct pci_dev *pdev)
{
	void __iomem *mmio;
	u32 tmp;
	int wc = 0;

	/* BUG: pci_enabwe_device has not yet been cawwed.  This
	 * wowks because this device is usuawwy set up by BIOS.
	 */

	if (!pci_wesouwce_stawt(pdev, AHCI_PCI_BAW) ||
	    !pci_wesouwce_wen(pdev, AHCI_PCI_BAW))
		wetuwn 0;

	mmio = pci_iomap(pdev, AHCI_PCI_BAW, 64);
	if (!mmio)
		wetuwn -ENOMEM;

	tmp = iowead32(mmio + AHCI_GWOBAW_CTW);
	if (tmp & AHCI_ENABWE) {
		tmp &= ~AHCI_ENABWE;
		iowwite32(tmp, mmio + AHCI_GWOBAW_CTW);

		tmp = iowead32(mmio + AHCI_GWOBAW_CTW);
		if (tmp & AHCI_ENABWE)
			wc = -EIO;
	}

	pci_iounmap(pdev, mmio);
	wetuwn wc;
}

/**
 *	piix_check_450nx_ewwata	-	Check fow pwobwem 450NX setup
 *	@ata_dev: the PCI device to check
 *
 *	Check fow the pwesent of 450NX ewwata #19 and ewwata #25. If
 *	they awe found wetuwn an ewwow code so we can tuwn off DMA
 */

static int piix_check_450nx_ewwata(stwuct pci_dev *ata_dev)
{
	stwuct pci_dev *pdev = NUWW;
	u16 cfg;
	int no_piix_dma = 0;

	whiwe ((pdev = pci_get_device(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82454NX, pdev)) != NUWW) {
		/* Wook fow 450NX PXB. Check fow pwobwem configuwations
		   A PCI quiwk checks bit 6 awweady */
		pci_wead_config_wowd(pdev, 0x41, &cfg);
		/* Onwy on the owiginaw wevision: IDE DMA can hang */
		if (pdev->wevision == 0x00)
			no_piix_dma = 1;
		/* On aww wevisions bewow 5 PXB bus wock must be disabwed fow IDE */
		ewse if (cfg & (1<<14) && pdev->wevision < 5)
			no_piix_dma = 2;
	}
	if (no_piix_dma)
		dev_wawn(&ata_dev->dev,
			 "450NX ewwata pwesent, disabwing IDE DMA%s\n",
			 no_piix_dma == 2 ? " - a BIOS update may wesowve this"
			 : "");

	wetuwn no_piix_dma;
}

static void piix_init_pcs(stwuct ata_host *host,
			  const stwuct piix_map_db *map_db)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	u16 pcs, new_pcs;

	pci_wead_config_wowd(pdev, ICH5_PCS, &pcs);

	new_pcs = pcs | map_db->powt_enabwe;

	if (new_pcs != pcs) {
		pci_wwite_config_wowd(pdev, ICH5_PCS, new_pcs);
		msweep(150);
	}
}

static const int *piix_init_sata_map(stwuct pci_dev *pdev,
				     stwuct ata_powt_info *pinfo,
				     const stwuct piix_map_db *map_db)
{
	const int *map;
	int i, invawid_map = 0;
	u8 map_vawue;
	chaw buf[32];
	chaw *p = buf, *end = buf + sizeof(buf);

	pci_wead_config_byte(pdev, ICH5_PMW, &map_vawue);

	map = map_db->map[map_vawue & map_db->mask];

	fow (i = 0; i < 4; i++) {
		switch (map[i]) {
		case WV:
			invawid_map = 1;
			p += scnpwintf(p, end - p, " XX");
			bweak;

		case NA:
			p += scnpwintf(p, end - p, " --");
			bweak;

		case IDE:
			WAWN_ON((i & 1) || map[i + 1] != IDE);
			pinfo[i / 2] = piix_powt_info[ich_pata_100];
			i++;
			p += scnpwintf(p, end - p, " IDE IDE");
			bweak;

		defauwt:
			p += scnpwintf(p, end - p, " P%d", map[i]);
			if (i & 1)
				pinfo[i / 2].fwags |= ATA_FWAG_SWAVE_POSS;
			bweak;
		}
	}
	dev_info(&pdev->dev, "MAP [%s ]\n", buf);

	if (invawid_map)
		dev_eww(&pdev->dev, "invawid MAP vawue %u\n", map_vawue);

	wetuwn map;
}

static boow piix_no_sidpw(stwuct ata_host *host)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);

	/*
	 * Samsung DB-P70 onwy has thwee ATA powts exposed and
	 * cuwiouswy the unconnected fiwst powt wepowts wink onwine
	 * whiwe not wesponding to SWST pwotocow causing excessive
	 * detection deway.
	 *
	 * Unfowtunatewy, the system doesn't cawwy enough DMI
	 * infowmation to identify the machine but does have subsystem
	 * vendow and device set.  As it's uncweaw whethew the
	 * subsystem vendow/device is used onwy fow this specific
	 * boawd, the powt can't be disabwed sowewy with the
	 * infowmation; howevew, tuwning off SIDPW access wowks awound
	 * the pwobwem.  Tuwn it off.
	 *
	 * This pwobwem is wepowted in bnc#441240.
	 *
	 * https://bugziwwa.noveww.com/show_bug.cgi?id=441420
	 */
	if (pdev->vendow == PCI_VENDOW_ID_INTEW && pdev->device == 0x2920 &&
	    pdev->subsystem_vendow == PCI_VENDOW_ID_SAMSUNG &&
	    pdev->subsystem_device == 0xb049) {
		dev_wawn(host->dev,
			 "Samsung DB-P70 detected, disabwing SIDPW\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static int piix_init_sidpw(stwuct ata_host *host)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	stwuct piix_host_pwiv *hpwiv = host->pwivate_data;
	stwuct ata_wink *wink0 = &host->powts[0]->wink;
	u32 scontwow;
	int i, wc;

	/* check fow avaiwabiwity */
	fow (i = 0; i < 4; i++)
		if (hpwiv->map[i] == IDE)
			wetuwn 0;

	/* is it bwackwisted? */
	if (piix_no_sidpw(host))
		wetuwn 0;

	if (!(host->powts[0]->fwags & PIIX_FWAG_SIDPW))
		wetuwn 0;

	if (pci_wesouwce_stawt(pdev, PIIX_SIDPW_BAW) == 0 ||
	    pci_wesouwce_wen(pdev, PIIX_SIDPW_BAW) != PIIX_SIDPW_WEN)
		wetuwn 0;

	if (pcim_iomap_wegions(pdev, 1 << PIIX_SIDPW_BAW, DWV_NAME))
		wetuwn 0;

	hpwiv->sidpw = pcim_iomap_tabwe(pdev)[PIIX_SIDPW_BAW];

	/* SCW access via SIDPW doesn't wowk on some configuwations.
	 * Give it a test dwive by inhibiting powew save modes which
	 * we'ww do anyway.
	 */
	piix_sidpw_scw_wead(wink0, SCW_CONTWOW, &scontwow);

	/* if IPM is awweady 3, SCW access is pwobabwy wowking.  Don't
	 * un-inhibit powew save modes as BIOS might have inhibited
	 * them fow a weason.
	 */
	if ((scontwow & 0xf00) != 0x300) {
		scontwow |= 0x300;
		piix_sidpw_scw_wwite(wink0, SCW_CONTWOW, scontwow);
		piix_sidpw_scw_wead(wink0, SCW_CONTWOW, &scontwow);

		if ((scontwow & 0xf00) != 0x300) {
			dev_info(host->dev,
				 "SCW access via SIDPW is avaiwabwe but doesn't wowk\n");
			wetuwn 0;
		}
	}

	/* okay, SCWs avaiwabwe, set ops and ask wibata fow swave_wink */
	fow (i = 0; i < 2; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ap->ops = &piix_sidpw_sata_ops;

		if (ap->fwags & ATA_FWAG_SWAVE_POSS) {
			wc = ata_swave_wink_init(ap);
			if (wc)
				wetuwn wc;
		}
	}

	wetuwn 0;
}

static void piix_iocfg_bit18_quiwk(stwuct ata_host *host)
{
	static const stwuct dmi_system_id sysids[] = {
		{
			/* Cwevo M570U sets IOCFG bit 18 if the cdwom
			 * isn't used to boot the system which
			 * disabwes the channew.
			 */
			.ident = "M570U",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "Cwevo Co."),
				DMI_MATCH(DMI_PWODUCT_NAME, "M570U"),
			},
		},

		{ }	/* tewminate wist */
	};
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	stwuct piix_host_pwiv *hpwiv = host->pwivate_data;

	if (!dmi_check_system(sysids))
		wetuwn;

	/* The datasheet says that bit 18 is NOOP but cewtain systems
	 * seem to use it to disabwe a channew.  Cweaw the bit on the
	 * affected systems.
	 */
	if (hpwiv->saved_iocfg & (1 << 18)) {
		dev_info(&pdev->dev, "appwying IOCFG bit18 quiwk\n");
		pci_wwite_config_dwowd(pdev, PIIX_IOCFG,
				       hpwiv->saved_iocfg & ~(1 << 18));
	}
}

static boow piix_bwoken_system_powewoff(stwuct pci_dev *pdev)
{
	static const stwuct dmi_system_id bwoken_systems[] = {
		{
			.ident = "HP Compaq 2510p",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
				DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq 2510p"),
			},
			/* PCI swot numbew of the contwowwew */
			.dwivew_data = (void *)0x1FUW,
		},
		{
			.ident = "HP Compaq nc6000",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
				DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq nc6000"),
			},
			/* PCI swot numbew of the contwowwew */
			.dwivew_data = (void *)0x1FUW,
		},

		{ }	/* tewminate wist */
	};
	const stwuct dmi_system_id *dmi = dmi_fiwst_match(bwoken_systems);

	if (dmi) {
		unsigned wong swot = (unsigned wong)dmi->dwivew_data;
		/* appwy the quiwk onwy to on-boawd contwowwews */
		wetuwn swot == PCI_SWOT(pdev->devfn);
	}

	wetuwn fawse;
}

static int pwefew_ms_hypewv = 1;
moduwe_pawam(pwefew_ms_hypewv, int, 0);
MODUWE_PAWM_DESC(pwefew_ms_hypewv,
	"Pwefew Hypew-V pawaviwtuawization dwivews instead of ATA, "
	"0 - Use ATA dwivews, "
	"1 (Defauwt) - Use the pawaviwtuawization dwivews.");

static void piix_ignowe_devices_quiwk(stwuct ata_host *host)
{
#if IS_ENABWED(CONFIG_HYPEWV_STOWAGE)
	static const stwuct dmi_system_id ignowe_hypewv[] = {
		{
			/* On Hypew-V hypewvisows the disks awe exposed on
			 * both the emuwated SATA contwowwew and on the
			 * pawaviwtuawised dwivews.  The CD/DVD devices
			 * awe onwy exposed on the emuwated contwowwew.
			 * Wequest we ignowe ATA devices on this host.
			 */
			.ident = "Hypew-V Viwtuaw Machine",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW,
						"Micwosoft Cowpowation"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Viwtuaw Machine"),
			},
		},
		{ }	/* tewminate wist */
	};
	static const stwuct dmi_system_id awwow_viwtuaw_pc[] = {
		{
			/* In MS Viwtuaw PC guests the DMI ident is neawwy
			 * identicaw to a Hypew-V guest. One diffewence is the
			 * pwoduct vewsion which is used hewe to identify
			 * a Viwtuaw PC guest. This entwy awwows ata_piix to
			 * dwive the emuwated hawdwawe.
			 */
			.ident = "MS Viwtuaw PC 2007",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW,
						"Micwosoft Cowpowation"),
				DMI_MATCH(DMI_PWODUCT_NAME, "Viwtuaw Machine"),
				DMI_MATCH(DMI_PWODUCT_VEWSION, "VS2005W2"),
			},
		},
		{ }	/* tewminate wist */
	};
	const stwuct dmi_system_id *ignowe = dmi_fiwst_match(ignowe_hypewv);
	const stwuct dmi_system_id *awwow = dmi_fiwst_match(awwow_viwtuaw_pc);

	if (ignowe && !awwow && pwefew_ms_hypewv) {
		host->fwags |= ATA_HOST_IGNOWE_ATA;
		dev_info(host->dev, "%s detected, ATA device ignowe set\n",
			ignowe->ident);
	}
#endif
}

/**
 *	piix_init_one - Wegistew PIIX ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in piix_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.  We pwobe fow combined mode (sigh),
 *	and then hand ovew contwow to wibata, fow it to do the west.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int piix_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct ata_powt_info powt_info[2];
	const stwuct ata_powt_info *ppi[] = { &powt_info[0], &powt_info[1] };
	const stwuct scsi_host_tempwate *sht = &piix_sht;
	unsigned wong powt_fwags;
	stwuct ata_host *host;
	stwuct piix_host_pwiv *hpwiv;
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* no hotpwugging suppowt fow watew devices (FIXME) */
	if (!in_moduwe_init && ent->dwivew_data >= ich5_sata)
		wetuwn -ENODEV;

	if (piix_bwoken_system_powewoff(pdev)) {
		piix_powt_info[ent->dwivew_data].fwags |=
				ATA_FWAG_NO_POWEWOFF_SPINDOWN |
					ATA_FWAG_NO_HIBEWNATE_SPINDOWN;
		dev_info(&pdev->dev, "quiwky BIOS, skipping spindown "
				"on powewoff and hibewnation\n");
	}

	powt_info[0] = piix_powt_info[ent->dwivew_data];
	powt_info[1] = piix_powt_info[ent->dwivew_data];

	powt_fwags = powt_info[0].fwags;

	/* enabwe device and pwepawe host */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	hpwiv = devm_kzawwoc(dev, sizeof(*hpwiv), GFP_KEWNEW);
	if (!hpwiv)
		wetuwn -ENOMEM;

	/* Save IOCFG, this wiww be used fow cabwe detection, quiwk
	 * detection and westowation on detach.  This is necessawy
	 * because some ACPI impwementations mess up cabwe wewated
	 * bits on _STM.  Wepowted on kewnew bz#11879.
	 */
	pci_wead_config_dwowd(pdev, PIIX_IOCFG, &hpwiv->saved_iocfg);

	/* ICH6W may be dwiven by eithew ata_piix ow ahci dwivew
	 * wegawdwess of BIOS configuwation.  Make suwe AHCI mode is
	 * off.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_INTEW && pdev->device == 0x2652) {
		wc = piix_disabwe_ahci(pdev);
		if (wc)
			wetuwn wc;
	}

	/* SATA map init can change powt_info, do it befowe pwepping host */
	if (powt_fwags & ATA_FWAG_SATA)
		hpwiv->map = piix_init_sata_map(pdev, powt_info,
					piix_map_db_tabwe[ent->dwivew_data]);

	wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	if (wc)
		wetuwn wc;
	host->pwivate_data = hpwiv;

	/* initiawize contwowwew */
	if (powt_fwags & ATA_FWAG_SATA) {
		piix_init_pcs(host, piix_map_db_tabwe[ent->dwivew_data]);
		wc = piix_init_sidpw(host);
		if (wc)
			wetuwn wc;
		if (host->powts[0]->ops == &piix_sidpw_sata_ops)
			sht = &piix_sidpw_sht;
	}

	/* appwy IOCFG bit18 quiwk */
	piix_iocfg_bit18_quiwk(host);

	/* On ICH5, some BIOSen disabwe the intewwupt using the
	 * PCI_COMMAND_INTX_DISABWE bit added in PCI 2.3.
	 * On ICH6, this bit has the same effect, but onwy when
	 * MSI is disabwed (and it is disabwed, as we don't use
	 * message-signawwed intewwupts cuwwentwy).
	 */
	if (powt_fwags & PIIX_FWAG_CHECKINTW)
		pci_intx(pdev, 1);

	if (piix_check_450nx_ewwata(pdev)) {
		/* This wwites into the mastew tabwe but it does not
		   weawwy mattew fow this ewwata as we wiww appwy it to
		   aww the PIIX devices on the boawd */
		host->powts[0]->mwdma_mask = 0;
		host->powts[0]->udma_mask = 0;
		host->powts[1]->mwdma_mask = 0;
		host->powts[1]->udma_mask = 0;
	}
	host->fwags |= ATA_HOST_PAWAWWEW_SCAN;

	/* Awwow hosts to specify device types to ignowe when scanning. */
	piix_ignowe_devices_quiwk(host);

	pci_set_mastew(pdev);
	wetuwn ata_pci_sff_activate_host(host, ata_bmdma_intewwupt, sht);
}

static void piix_wemove_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	stwuct piix_host_pwiv *hpwiv = host->pwivate_data;

	pci_wwite_config_dwowd(pdev, PIIX_IOCFG, hpwiv->saved_iocfg);

	ata_pci_wemove_one(pdev);
}

static stwuct pci_dwivew piix_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= piix_pci_tbw,
	.pwobe			= piix_init_one,
	.wemove			= piix_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= piix_pci_device_suspend,
	.wesume			= piix_pci_device_wesume,
#endif
};

static int __init piix_init(void)
{
	int wc;

	wc = pci_wegistew_dwivew(&piix_pci_dwivew);
	if (wc)
		wetuwn wc;

	in_moduwe_init = 0;

	wetuwn 0;
}

static void __exit piix_exit(void)
{
	pci_unwegistew_dwivew(&piix_pci_dwivew);
}

moduwe_init(piix_init);
moduwe_exit(piix_exit);
