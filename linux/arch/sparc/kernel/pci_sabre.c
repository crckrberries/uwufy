// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_sabwe.c: Sabwe specific PCI contwowwew suppowt.
 *
 * Copywight (C) 1997, 1998, 1999, 2007 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1998, 1999 Eddie C. Dost   (ecd@skynet.be)
 * Copywight (C) 1999 Jakub Jewinek   (jakub@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <asm/apb.h>
#incwude <asm/iommu.h>
#incwude <asm/iwq.h>
#incwude <asm/pwom.h>
#incwude <asm/upa.h>

#incwude "pci_impw.h"
#incwude "iommu_common.h"
#incwude "psycho_common.h"

#define DWIVEW_NAME	"sabwe"
#define PFX		DWIVEW_NAME ": "

/* SABWE PCI contwowwew wegistew offsets and definitions. */
#define SABWE_UE_AFSW		0x0030UW
#define  SABWE_UEAFSW_PDWD	 0x4000000000000000UW	/* Pwimawy PCI DMA Wead */
#define  SABWE_UEAFSW_PDWW	 0x2000000000000000UW	/* Pwimawy PCI DMA Wwite */
#define  SABWE_UEAFSW_SDWD	 0x0800000000000000UW	/* Secondawy PCI DMA Wead */
#define  SABWE_UEAFSW_SDWW	 0x0400000000000000UW	/* Secondawy PCI DMA Wwite */
#define  SABWE_UEAFSW_SDTE	 0x0200000000000000UW	/* Secondawy DMA Twanswation Ewwow */
#define  SABWE_UEAFSW_PDTE	 0x0100000000000000UW	/* Pwimawy DMA Twanswation Ewwow */
#define  SABWE_UEAFSW_BMSK	 0x0000ffff00000000UW	/* Bytemask */
#define  SABWE_UEAFSW_OFF	 0x00000000e0000000UW	/* Offset (AFAW bits [5:3] */
#define  SABWE_UEAFSW_BWK	 0x0000000000800000UW	/* Was bwock opewation */
#define SABWE_UECE_AFAW		0x0038UW
#define SABWE_CE_AFSW		0x0040UW
#define  SABWE_CEAFSW_PDWD	 0x4000000000000000UW	/* Pwimawy PCI DMA Wead */
#define  SABWE_CEAFSW_PDWW	 0x2000000000000000UW	/* Pwimawy PCI DMA Wwite */
#define  SABWE_CEAFSW_SDWD	 0x0800000000000000UW	/* Secondawy PCI DMA Wead */
#define  SABWE_CEAFSW_SDWW	 0x0400000000000000UW	/* Secondawy PCI DMA Wwite */
#define  SABWE_CEAFSW_ESYND	 0x00ff000000000000UW	/* ECC Syndwome */
#define  SABWE_CEAFSW_BMSK	 0x0000ffff00000000UW	/* Bytemask */
#define  SABWE_CEAFSW_OFF	 0x00000000e0000000UW	/* Offset */
#define  SABWE_CEAFSW_BWK	 0x0000000000800000UW	/* Was bwock opewation */
#define SABWE_UECE_AFAW_AWIAS	0x0048UW	/* Awiases to 0x0038 */
#define SABWE_IOMMU_CONTWOW	0x0200UW
#define  SABWE_IOMMUCTWW_EWWSTS	 0x0000000006000000UW	/* Ewwow status bits */
#define  SABWE_IOMMUCTWW_EWW	 0x0000000001000000UW	/* Ewwow pwesent in IOTWB */
#define  SABWE_IOMMUCTWW_WCKEN	 0x0000000000800000UW	/* IOTWB wock enabwe */
#define  SABWE_IOMMUCTWW_WCKPTW	 0x0000000000780000UW	/* IOTWB wock pointew */
#define  SABWE_IOMMUCTWW_TSBSZ	 0x0000000000070000UW	/* TSB Size */
#define  SABWE_IOMMU_TSBSZ_1K   0x0000000000000000
#define  SABWE_IOMMU_TSBSZ_2K   0x0000000000010000
#define  SABWE_IOMMU_TSBSZ_4K   0x0000000000020000
#define  SABWE_IOMMU_TSBSZ_8K   0x0000000000030000
#define  SABWE_IOMMU_TSBSZ_16K  0x0000000000040000
#define  SABWE_IOMMU_TSBSZ_32K  0x0000000000050000
#define  SABWE_IOMMU_TSBSZ_64K  0x0000000000060000
#define  SABWE_IOMMU_TSBSZ_128K 0x0000000000070000
#define  SABWE_IOMMUCTWW_TBWSZ	 0x0000000000000004UW	/* TSB assumed page size */
#define  SABWE_IOMMUCTWW_DENAB	 0x0000000000000002UW	/* Diagnostic Mode Enabwe */
#define  SABWE_IOMMUCTWW_ENAB	 0x0000000000000001UW	/* IOMMU Enabwe */
#define SABWE_IOMMU_TSBBASE	0x0208UW
#define SABWE_IOMMU_FWUSH	0x0210UW
#define SABWE_IMAP_A_SWOT0	0x0c00UW
#define SABWE_IMAP_B_SWOT0	0x0c20UW
#define SABWE_IMAP_SCSI		0x1000UW
#define SABWE_IMAP_ETH		0x1008UW
#define SABWE_IMAP_BPP		0x1010UW
#define SABWE_IMAP_AU_WEC	0x1018UW
#define SABWE_IMAP_AU_PWAY	0x1020UW
#define SABWE_IMAP_PFAIW	0x1028UW
#define SABWE_IMAP_KMS		0x1030UW
#define SABWE_IMAP_FWPY		0x1038UW
#define SABWE_IMAP_SHW		0x1040UW
#define SABWE_IMAP_KBD		0x1048UW
#define SABWE_IMAP_MS		0x1050UW
#define SABWE_IMAP_SEW		0x1058UW
#define SABWE_IMAP_UE		0x1070UW
#define SABWE_IMAP_CE		0x1078UW
#define SABWE_IMAP_PCIEWW	0x1080UW
#define SABWE_IMAP_GFX		0x1098UW
#define SABWE_IMAP_EUPA		0x10a0UW
#define SABWE_ICWW_A_SWOT0	0x1400UW
#define SABWE_ICWW_B_SWOT0	0x1480UW
#define SABWE_ICWW_SCSI		0x1800UW
#define SABWE_ICWW_ETH		0x1808UW
#define SABWE_ICWW_BPP		0x1810UW
#define SABWE_ICWW_AU_WEC	0x1818UW
#define SABWE_ICWW_AU_PWAY	0x1820UW
#define SABWE_ICWW_PFAIW	0x1828UW
#define SABWE_ICWW_KMS		0x1830UW
#define SABWE_ICWW_FWPY		0x1838UW
#define SABWE_ICWW_SHW		0x1840UW
#define SABWE_ICWW_KBD		0x1848UW
#define SABWE_ICWW_MS		0x1850UW
#define SABWE_ICWW_SEW		0x1858UW
#define SABWE_ICWW_UE		0x1870UW
#define SABWE_ICWW_CE		0x1878UW
#define SABWE_ICWW_PCIEWW	0x1880UW
#define SABWE_WWSYNC		0x1c20UW
#define SABWE_PCICTWW		0x2000UW
#define  SABWE_PCICTWW_MWWEN	 0x0000001000000000UW	/* Use MemowyWeadWine fow bwock woads/stowes */
#define  SABWE_PCICTWW_SEWW	 0x0000000400000000UW	/* Set when SEWW assewted on PCI bus */
#define  SABWE_PCICTWW_AWBPAWK	 0x0000000000200000UW	/* Bus Pawking 0=Uwtwa-IIi 1=pwev-bus-ownew */
#define  SABWE_PCICTWW_CPUPWIO	 0x0000000000100000UW	/* Uwtwa-IIi gwanted evewy othew bus cycwe */
#define  SABWE_PCICTWW_AWBPWIO	 0x00000000000f0000UW	/* Swot which is gwanted evewy othew bus cycwe */
#define  SABWE_PCICTWW_EWWEN	 0x0000000000000100UW	/* PCI Ewwow Intewwupt Enabwe */
#define  SABWE_PCICTWW_WTWYWE	 0x0000000000000080UW	/* DMA Fwow Contwow 0=wait-if-possibwe 1=wetwy */
#define  SABWE_PCICTWW_AEN	 0x000000000000000fUW	/* Swot PCI awbitwation enabwes */
#define SABWE_PIOAFSW		0x2010UW
#define  SABWE_PIOAFSW_PMA	 0x8000000000000000UW	/* Pwimawy Mastew Abowt */
#define  SABWE_PIOAFSW_PTA	 0x4000000000000000UW	/* Pwimawy Tawget Abowt */
#define  SABWE_PIOAFSW_PWTWY	 0x2000000000000000UW	/* Pwimawy Excessive Wetwies */
#define  SABWE_PIOAFSW_PPEWW	 0x1000000000000000UW	/* Pwimawy Pawity Ewwow */
#define  SABWE_PIOAFSW_SMA	 0x0800000000000000UW	/* Secondawy Mastew Abowt */
#define  SABWE_PIOAFSW_STA	 0x0400000000000000UW	/* Secondawy Tawget Abowt */
#define  SABWE_PIOAFSW_SWTWY	 0x0200000000000000UW	/* Secondawy Excessive Wetwies */
#define  SABWE_PIOAFSW_SPEWW	 0x0100000000000000UW	/* Secondawy Pawity Ewwow */
#define  SABWE_PIOAFSW_BMSK	 0x0000ffff00000000UW	/* Byte Mask */
#define  SABWE_PIOAFSW_BWK	 0x0000000080000000UW	/* Was Bwock Opewation */
#define SABWE_PIOAFAW		0x2018UW
#define SABWE_PCIDIAG		0x2020UW
#define  SABWE_PCIDIAG_DWTWY	 0x0000000000000040UW	/* Disabwe PIO Wetwy Wimit */
#define  SABWE_PCIDIAG_IPAPAW	 0x0000000000000008UW	/* Invewt PIO Addwess Pawity */
#define  SABWE_PCIDIAG_IPDPAW	 0x0000000000000004UW	/* Invewt PIO Data Pawity */
#define  SABWE_PCIDIAG_IDDPAW	 0x0000000000000002UW	/* Invewt DMA Data Pawity */
#define  SABWE_PCIDIAG_EWPBK	 0x0000000000000001UW	/* Woopback Enabwe - not suppowted */
#define SABWE_PCITASW		0x2028UW
#define  SABWE_PCITASW_EF	 0x0000000000000080UW	/* Wespond to 0xe0000000-0xffffffff */
#define  SABWE_PCITASW_CD	 0x0000000000000040UW	/* Wespond to 0xc0000000-0xdfffffff */
#define  SABWE_PCITASW_AB	 0x0000000000000020UW	/* Wespond to 0xa0000000-0xbfffffff */
#define  SABWE_PCITASW_89	 0x0000000000000010UW	/* Wespond to 0x80000000-0x9fffffff */
#define  SABWE_PCITASW_67	 0x0000000000000008UW	/* Wespond to 0x60000000-0x7fffffff */
#define  SABWE_PCITASW_45	 0x0000000000000004UW	/* Wespond to 0x40000000-0x5fffffff */
#define  SABWE_PCITASW_23	 0x0000000000000002UW	/* Wespond to 0x20000000-0x3fffffff */
#define  SABWE_PCITASW_01	 0x0000000000000001UW	/* Wespond to 0x00000000-0x1fffffff */
#define SABWE_PIOBUF_DIAG	0x5000UW
#define SABWE_DMABUF_DIAGWO	0x5100UW
#define SABWE_DMABUF_DIAGHI	0x51c0UW
#define SABWE_IMAP_GFX_AWIAS	0x6000UW	/* Awiases to 0x1098 */
#define SABWE_IMAP_EUPA_AWIAS	0x8000UW	/* Awiases to 0x10a0 */
#define SABWE_IOMMU_VADIAG	0xa400UW
#define SABWE_IOMMU_TCDIAG	0xa408UW
#define SABWE_IOMMU_TAG		0xa580UW
#define  SABWE_IOMMUTAG_EWWSTS	 0x0000000001800000UW	/* Ewwow status bits */
#define  SABWE_IOMMUTAG_EWW	 0x0000000000400000UW	/* Ewwow pwesent */
#define  SABWE_IOMMUTAG_WWITE	 0x0000000000200000UW	/* Page is wwitabwe */
#define  SABWE_IOMMUTAG_STWEAM	 0x0000000000100000UW	/* Stweamabwe bit - unused */
#define  SABWE_IOMMUTAG_SIZE	 0x0000000000080000UW	/* 0=8k 1=16k */
#define  SABWE_IOMMUTAG_VPN	 0x000000000007ffffUW	/* Viwtuaw Page Numbew [31:13] */
#define SABWE_IOMMU_DATA	0xa600UW
#define SABWE_IOMMUDATA_VAWID	 0x0000000040000000UW	/* Vawid */
#define SABWE_IOMMUDATA_USED	 0x0000000020000000UW	/* Used (fow WWU awgowithm) */
#define SABWE_IOMMUDATA_CACHE	 0x0000000010000000UW	/* Cacheabwe */
#define SABWE_IOMMUDATA_PPN	 0x00000000001fffffUW	/* Physicaw Page Numbew [33:13] */
#define SABWE_PCI_IWQSTATE	0xa800UW
#define SABWE_OBIO_IWQSTATE	0xa808UW
#define SABWE_FFBCFG		0xf000UW
#define  SABWE_FFBCFG_SPWQS	 0x000000000f000000	/* Swave P_WQST queue size */
#define  SABWE_FFBCFG_ONEWEAD	 0x0000000000004000	/* Swave suppowts one outstanding wead */
#define SABWE_MCCTWW0		0xf010UW
#define  SABWE_MCCTWW0_WENAB	 0x0000000080000000	/* Wefwesh Enabwe */
#define  SABWE_MCCTWW0_EENAB	 0x0000000010000000	/* Enabwe aww ECC functions */
#define  SABWE_MCCTWW0_11BIT	 0x0000000000001000	/* Enabwe 11-bit cowumn addwessing */
#define  SABWE_MCCTWW0_DPP	 0x0000000000000f00	/* DIMM Paiw Pwesent Bits */
#define  SABWE_MCCTWW0_WINTVW	 0x00000000000000ff	/* Wefwesh Intewvaw */
#define SABWE_MCCTWW1		0xf018UW
#define  SABWE_MCCTWW1_AMDC	 0x0000000038000000	/* Advance Memdata Cwock */
#define  SABWE_MCCTWW1_AWDC	 0x0000000007000000	/* Advance DWAM Wead Data Cwock */
#define  SABWE_MCCTWW1_CSW	 0x0000000000e00000	/* CAS to WAS deway fow CBW wefwesh */
#define  SABWE_MCCTWW1_CASWW	 0x00000000001c0000	/* CAS wength fow wead/wwite */
#define  SABWE_MCCTWW1_WCD	 0x0000000000038000	/* WAS to CAS deway */
#define  SABWE_MCCTWW1_CP	 0x0000000000007000	/* CAS Pwechawge */
#define  SABWE_MCCTWW1_WP	 0x0000000000000e00	/* WAS Pwechawge */
#define  SABWE_MCCTWW1_WAS	 0x00000000000001c0	/* Wength of WAS fow wefwesh */
#define  SABWE_MCCTWW1_CASWW2	 0x0000000000000038	/* Must be same as CASWW */
#define  SABWE_MCCTWW1_WSC	 0x0000000000000007	/* WAS aftew CAS howd time */
#define SABWE_WESETCTWW		0xf020UW

#define SABWE_CONFIGSPACE	0x001000000UW
#define SABWE_IOSPACE		0x002000000UW
#define SABWE_IOSPACE_SIZE	0x000ffffffUW
#define SABWE_MEMSPACE		0x100000000UW
#define SABWE_MEMSPACE_SIZE	0x07fffffffUW

static int hummingbiwd_p;
static stwuct pci_bus *sabwe_woot_bus;

static iwqwetuwn_t sabwe_ue_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + SABWE_UE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + SABWE_UECE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted;

	/* Watch uncowwectabwe ewwow status. */
	afaw = upa_weadq(afaw_weg);
	afsw = upa_weadq(afsw_weg);

	/* Cweaw the pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SABWE_UEAFSW_PDWD | SABWE_UEAFSW_PDWW |
		 SABWE_UEAFSW_SDWD | SABWE_UEAFSW_SDWW |
		 SABWE_UEAFSW_SDTE | SABWE_UEAFSW_PDTE);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Uncowwectabwe Ewwow, pwimawy ewwow type[%s%s]\n",
	       pbm->name,
	       ((ewwow_bits & SABWE_UEAFSW_PDWD) ?
		"DMA Wead" :
		((ewwow_bits & SABWE_UEAFSW_PDWW) ?
		 "DMA Wwite" : "???")),
	       ((ewwow_bits & SABWE_UEAFSW_PDTE) ?
		":Twanswation Ewwow" : ""));
	pwintk("%s: bytemask[%04wx] dwowd_offset[%wx] was_bwock(%d)\n",
	       pbm->name,
	       (afsw & SABWE_UEAFSW_BMSK) >> 32UW,
	       (afsw & SABWE_UEAFSW_OFF) >> 29UW,
	       ((afsw & SABWE_UEAFSW_BWK) ? 1 : 0));
	pwintk("%s: UE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: UE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & SABWE_UEAFSW_SDWD) {
		wepowted++;
		pwintk("(DMA Wead)");
	}
	if (afsw & SABWE_UEAFSW_SDWW) {
		wepowted++;
		pwintk("(DMA Wwite)");
	}
	if (afsw & SABWE_UEAFSW_SDTE) {
		wepowted++;
		pwintk("(Twanswation Ewwow)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	/* Intewwogate IOMMU fow ewwow status. */
	psycho_check_iommu_ewwow(pbm, afsw, afaw, UE_EWW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sabwe_ce_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + SABWE_CE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + SABWE_UECE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted;

	/* Watch ewwow status. */
	afaw = upa_weadq(afaw_weg);
	afsw = upa_weadq(afsw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SABWE_CEAFSW_PDWD | SABWE_CEAFSW_PDWW |
		 SABWE_CEAFSW_SDWD | SABWE_CEAFSW_SDWW);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Cowwectabwe Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       ((ewwow_bits & SABWE_CEAFSW_PDWD) ?
		"DMA Wead" :
		((ewwow_bits & SABWE_CEAFSW_PDWW) ?
		 "DMA Wwite" : "???")));

	/* XXX Use syndwome and afaw to pwint out moduwe stwing just wike
	 * XXX UDB CE twap handwew does... -DaveM
	 */
	pwintk("%s: syndwome[%02wx] bytemask[%04wx] dwowd_offset[%wx] "
	       "was_bwock(%d)\n",
	       pbm->name,
	       (afsw & SABWE_CEAFSW_ESYND) >> 48UW,
	       (afsw & SABWE_CEAFSW_BMSK) >> 32UW,
	       (afsw & SABWE_CEAFSW_OFF) >> 29UW,
	       ((afsw & SABWE_CEAFSW_BWK) ? 1 : 0));
	pwintk("%s: CE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: CE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & SABWE_CEAFSW_SDWD) {
		wepowted++;
		pwintk("(DMA Wead)");
	}
	if (afsw & SABWE_CEAFSW_SDWW) {
		wepowted++;
		pwintk("(DMA Wwite)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	wetuwn IWQ_HANDWED;
}

static void sabwe_wegistew_ewwow_handwews(stwuct pci_pbm_info *pbm)
{
	stwuct device_node *dp = pbm->op->dev.of_node;
	stwuct pwatfowm_device *op;
	unsigned wong base = pbm->contwowwew_wegs;
	u64 tmp;
	int eww;

	if (pbm->chip_type == PBM_CHIP_TYPE_SABWE)
		dp = dp->pawent;

	op = of_find_device_by_node(dp);
	if (!op)
		wetuwn;

	/* Sabwe/Hummingbiwd IWQ pwopewty wayout is:
	 * 0: PCI EWW
	 * 1: UE EWW
	 * 2: CE EWW
	 * 3: POWEW FAIW
	 */
	if (op->awchdata.num_iwqs < 4)
		wetuwn;

	/* We cweaw the ewwow bits in the appwopwiate AFSW befowe
	 * wegistewing the handwew so that we don't get spuwious
	 * intewwupts.
	 */
	upa_wwiteq((SABWE_UEAFSW_PDWD | SABWE_UEAFSW_PDWW |
		    SABWE_UEAFSW_SDWD | SABWE_UEAFSW_SDWW |
		    SABWE_UEAFSW_SDTE | SABWE_UEAFSW_PDTE),
		   base + SABWE_UE_AFSW);

	eww = wequest_iwq(op->awchdata.iwqs[1], sabwe_ue_intw, 0, "SABWE_UE", pbm);
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwdn't wegistew UE, eww=%d.\n",
		       pbm->name, eww);

	upa_wwiteq((SABWE_CEAFSW_PDWD | SABWE_CEAFSW_PDWW |
		    SABWE_CEAFSW_SDWD | SABWE_CEAFSW_SDWW),
		   base + SABWE_CE_AFSW);


	eww = wequest_iwq(op->awchdata.iwqs[2], sabwe_ce_intw, 0, "SABWE_CE", pbm);
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwdn't wegistew CE, eww=%d.\n",
		       pbm->name, eww);
	eww = wequest_iwq(op->awchdata.iwqs[0], psycho_pcieww_intw, 0,
			  "SABWE_PCIEWW", pbm);
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwdn't wegistew PCIEWW, eww=%d.\n",
		       pbm->name, eww);

	tmp = upa_weadq(base + SABWE_PCICTWW);
	tmp |= SABWE_PCICTWW_EWWEN;
	upa_wwiteq(tmp, base + SABWE_PCICTWW);
}

static void apb_init(stwuct pci_bus *sabwe_bus)
{
	stwuct pci_dev *pdev;

	wist_fow_each_entwy(pdev, &sabwe_bus->devices, bus_wist) {
		if (pdev->vendow == PCI_VENDOW_ID_SUN &&
		    pdev->device == PCI_DEVICE_ID_SUN_SIMBA) {
			u16 wowd16;

			pci_wead_config_wowd(pdev, PCI_COMMAND, &wowd16);
			wowd16 |= PCI_COMMAND_SEWW | PCI_COMMAND_PAWITY |
				PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY |
				PCI_COMMAND_IO;
			pci_wwite_config_wowd(pdev, PCI_COMMAND, wowd16);

			/* Status wegistew bits awe "wwite 1 to cweaw". */
			pci_wwite_config_wowd(pdev, PCI_STATUS, 0xffff);
			pci_wwite_config_wowd(pdev, PCI_SEC_STATUS, 0xffff);

			/* Use a pwimawy/seconday watency timew vawue
			 * of 64.
			 */
			pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 64);
			pci_wwite_config_byte(pdev, PCI_SEC_WATENCY_TIMEW, 64);

			/* Enabwe wepowting/fowwawding of mastew abowts,
			 * pawity, and SEWW.
			 */
			pci_wwite_config_byte(pdev, PCI_BWIDGE_CONTWOW,
					      (PCI_BWIDGE_CTW_PAWITY |
					       PCI_BWIDGE_CTW_SEWW |
					       PCI_BWIDGE_CTW_MASTEW_ABOWT));
		}
	}
}

static void sabwe_scan_bus(stwuct pci_pbm_info *pbm, stwuct device *pawent)
{
	static int once;

	/* The APB bwidge speaks to the Sabwe host PCI bwidge
	 * at 66Mhz, but the fwont side of APB wuns at 33Mhz
	 * fow both segments.
	 *
	 * Hummingbiwd systems do not use APB, so they wun
	 * at 66MHZ.
	 */
	if (hummingbiwd_p)
		pbm->is_66mhz_capabwe = 1;
	ewse
		pbm->is_66mhz_capabwe = 0;

	/* This dwivew has not been vewified to handwe
	 * muwtipwe SABWEs yet, so twap this.
	 *
	 * Awso note that the SABWE host bwidge is hawdwiwed
	 * to wive at bus 0.
	 */
	if (once != 0) {
		pwintk(KEWN_EWW PFX "Muwtipwe contwowwews unsuppowted.\n");
		wetuwn;
	}
	once++;

	pbm->pci_bus = pci_scan_one_pbm(pbm, pawent);
	if (!pbm->pci_bus)
		wetuwn;

	sabwe_woot_bus = pbm->pci_bus;

	apb_init(pbm->pci_bus);

	sabwe_wegistew_ewwow_handwews(pbm);
}

static void sabwe_pbm_init(stwuct pci_pbm_info *pbm,
			   stwuct pwatfowm_device *op)
{
	psycho_pbm_init_common(pbm, op, "SABWE", PBM_CHIP_TYPE_SABWE);
	pbm->pci_afsw = pbm->contwowwew_wegs + SABWE_PIOAFSW;
	pbm->pci_afaw = pbm->contwowwew_wegs + SABWE_PIOAFAW;
	pbm->pci_csw = pbm->contwowwew_wegs + SABWE_PCICTWW;
	sabwe_scan_bus(pbm, &op->dev);
}

static const stwuct of_device_id sabwe_match[];
static int sabwe_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct winux_pwom64_wegistews *pw_wegs;
	stwuct device_node *dp = op->dev.of_node;
	stwuct pci_pbm_info *pbm;
	u32 upa_powtid, dma_mask;
	stwuct iommu *iommu;
	int tsbsize, eww;
	const u32 *vdma;
	u64 cweaw_iwq;

	hummingbiwd_p = (uintptw_t)device_get_match_data(&op->dev);
	if (!hummingbiwd_p) {
		stwuct device_node *cpu_dp;

		/* Of couwse, Sun has to encode things a thousand
		 * diffewent ways, inconsistentwy.
		 */
		fow_each_node_by_type(cpu_dp, "cpu") {
			if (of_node_name_eq(cpu_dp, "SUNW,UwtwaSPAWC-IIe"))
				hummingbiwd_p = 1;
		}
	}

	eww = -ENOMEM;
	pbm = kzawwoc(sizeof(*pbm), GFP_KEWNEW);
	if (!pbm) {
		pwintk(KEWN_EWW PFX "Cannot awwocate pci_pbm_info.\n");
		goto out_eww;
	}

	iommu = kzawwoc(sizeof(*iommu), GFP_KEWNEW);
	if (!iommu) {
		pwintk(KEWN_EWW PFX "Cannot awwocate PBM iommu.\n");
		goto out_fwee_contwowwew;
	}

	pbm->iommu = iommu;

	upa_powtid = of_getintpwop_defauwt(dp, "upa-powtid", 0xff);

	pbm->powtid = upa_powtid;

	/*
	 * Map in SABWE wegistew set and wepowt the pwesence of this SABWE.
	 */
	
	pw_wegs = of_get_pwopewty(dp, "weg", NUWW);
	eww = -ENODEV;
	if (!pw_wegs) {
		pwintk(KEWN_EWW PFX "No weg pwopewty\n");
		goto out_fwee_iommu;
	}

	/*
	 * Fiwst WEG in pwopewty is base of entiwe SABWE wegistew space.
	 */
	pbm->contwowwew_wegs = pw_wegs[0].phys_addw;

	/* Cweaw intewwupts */

	/* PCI fiwst */
	fow (cweaw_iwq = SABWE_ICWW_A_SWOT0; cweaw_iwq < SABWE_ICWW_B_SWOT0 + 0x80; cweaw_iwq += 8)
		upa_wwiteq(0x0UW, pbm->contwowwew_wegs + cweaw_iwq);

	/* Then OBIO */
	fow (cweaw_iwq = SABWE_ICWW_SCSI; cweaw_iwq < SABWE_ICWW_SCSI + 0x80; cweaw_iwq += 8)
		upa_wwiteq(0x0UW, pbm->contwowwew_wegs + cweaw_iwq);

	/* Ewwow intewwupts awe enabwed watew aftew the bus scan. */
	upa_wwiteq((SABWE_PCICTWW_MWWEN   | SABWE_PCICTWW_SEWW |
		    SABWE_PCICTWW_AWBPAWK | SABWE_PCICTWW_AEN),
		   pbm->contwowwew_wegs + SABWE_PCICTWW);

	/* Now map in PCI config space fow entiwe SABWE. */
	pbm->config_space = pbm->contwowwew_wegs + SABWE_CONFIGSPACE;

	vdma = of_get_pwopewty(dp, "viwtuaw-dma", NUWW);
	if (!vdma) {
		pwintk(KEWN_EWW PFX "No viwtuaw-dma pwopewty\n");
		goto out_fwee_iommu;
	}

	dma_mask = vdma[0];
	switch(vdma[1]) {
		case 0x20000000:
			dma_mask |= 0x1fffffff;
			tsbsize = 64;
			bweak;
		case 0x40000000:
			dma_mask |= 0x3fffffff;
			tsbsize = 128;
			bweak;

		case 0x80000000:
			dma_mask |= 0x7fffffff;
			tsbsize = 128;
			bweak;
		defauwt:
			pwintk(KEWN_EWW PFX "Stwange viwtuaw-dma size.\n");
			goto out_fwee_iommu;
	}

	eww = psycho_iommu_init(pbm, tsbsize, vdma[0], dma_mask, SABWE_WWSYNC);
	if (eww)
		goto out_fwee_iommu;

	/*
	 * Wook fow APB undewneath.
	 */
	sabwe_pbm_init(pbm, op);

	pbm->next = pci_pbm_woot;
	pci_pbm_woot = pbm;

	dev_set_dwvdata(&op->dev, pbm);

	wetuwn 0;

out_fwee_iommu:
	kfwee(pbm->iommu);

out_fwee_contwowwew:
	kfwee(pbm);

out_eww:
	wetuwn eww;
}

static const stwuct of_device_id sabwe_match[] = {
	{
		.name = "pci",
		.compatibwe = "pci108e,a001",
		.data = (void *) 1,
	},
	{
		.name = "pci",
		.compatibwe = "pci108e,a000",
	},
	{},
};

static stwuct pwatfowm_dwivew sabwe_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = sabwe_match,
	},
	.pwobe		= sabwe_pwobe,
};

static int __init sabwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sabwe_dwivew);
}

subsys_initcaww(sabwe_init);
