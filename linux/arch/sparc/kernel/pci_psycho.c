// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_psycho.c: PSYCHO/U2P specific PCI contwowwew suppowt.
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

#incwude <asm/iommu.h>
#incwude <asm/iwq.h>
#incwude <asm/stawfiwe.h>
#incwude <asm/pwom.h>
#incwude <asm/upa.h>

#incwude "pci_impw.h"
#incwude "iommu_common.h"
#incwude "psycho_common.h"

#define DWIVEW_NAME	"psycho"
#define PFX		DWIVEW_NAME ": "

/* Misc. PSYCHO PCI contwowwew wegistew offsets and definitions. */
#define PSYCHO_CONTWOW		0x0010UW
#define  PSYCHO_CONTWOW_IMPW	 0xf000000000000000UW /* Impwementation of this PSYCHO*/
#define  PSYCHO_CONTWOW_VEW	 0x0f00000000000000UW /* Vewsion of this PSYCHO       */
#define  PSYCHO_CONTWOW_MID	 0x00f8000000000000UW /* UPA Moduwe ID of PSYCHO      */
#define  PSYCHO_CONTWOW_IGN	 0x0007c00000000000UW /* Intewwupt Gwoup Numbew       */
#define  PSYCHO_CONTWOW_WESV     0x00003ffffffffff0UW /* Wesewved                     */
#define  PSYCHO_CONTWOW_APCKEN	 0x0000000000000008UW /* Addwess Pawity Check Enabwe  */
#define  PSYCHO_CONTWOW_APEWW	 0x0000000000000004UW /* Incoming System Addw Paweww  */
#define  PSYCHO_CONTWOW_IAP	 0x0000000000000002UW /* Invewt UPA Pawity            */
#define  PSYCHO_CONTWOW_MODE	 0x0000000000000001UW /* PSYCHO cwock mode            */
#define PSYCHO_PCIA_CTWW	0x2000UW
#define PSYCHO_PCIB_CTWW	0x4000UW
#define  PSYCHO_PCICTWW_WESV1	 0xfffffff000000000UW /* Wesewved                     */
#define  PSYCHO_PCICTWW_SBH_EWW	 0x0000000800000000UW /* Stweaming byte howe ewwow    */
#define  PSYCHO_PCICTWW_SEWW	 0x0000000400000000UW /* SEWW signaw assewted         */
#define  PSYCHO_PCICTWW_SPEED	 0x0000000200000000UW /* PCI speed (1 is U2P cwock)   */
#define  PSYCHO_PCICTWW_WESV2	 0x00000001ffc00000UW /* Wesewved                     */
#define  PSYCHO_PCICTWW_AWB_PAWK 0x0000000000200000UW /* PCI awbitwation pawking      */
#define  PSYCHO_PCICTWW_WESV3	 0x00000000001ff800UW /* Wesewved                     */
#define  PSYCHO_PCICTWW_SBH_INT	 0x0000000000000400UW /* Stweaming byte howe int enab */
#define  PSYCHO_PCICTWW_WEN	 0x0000000000000200UW /* Powew Mgmt Wake Enabwe       */
#define  PSYCHO_PCICTWW_EEN	 0x0000000000000100UW /* PCI Ewwow Intewwupt Enabwe   */
#define  PSYCHO_PCICTWW_WESV4	 0x00000000000000c0UW /* Wesewved                     */
#define  PSYCHO_PCICTWW_AEN	 0x000000000000003fUW /* PCI DVMA Awbitwation Enabwe  */

/* PSYCHO ewwow handwing suppowt. */

/* Hewpew function of IOMMU ewwow checking, which checks out
 * the state of the stweaming buffews.  The IOMMU wock is
 * hewd when this is cawwed.
 *
 * Fow the PCI ewwow case we know which PBM (and thus which
 * stweaming buffew) caused the ewwow, but fow the uncowwectabwe
 * ewwow case we do not.  So we awways check both stweaming caches.
 */
#define PSYCHO_STWBUF_CONTWOW_A 0x2800UW
#define PSYCHO_STWBUF_CONTWOW_B 0x4800UW
#define  PSYCHO_STWBUF_CTWW_WPTW    0x00000000000000f0UW /* WWU Wock Pointew */
#define  PSYCHO_STWBUF_CTWW_WENAB   0x0000000000000008UW /* WWU Wock Enabwe */
#define  PSYCHO_STWBUF_CTWW_WWDIS   0x0000000000000004UW /* Wewun Disabwe */
#define  PSYCHO_STWBUF_CTWW_DENAB   0x0000000000000002UW /* Diagnostic Mode Enabwe */
#define  PSYCHO_STWBUF_CTWW_ENAB    0x0000000000000001UW /* Stweaming Buffew Enabwe */
#define PSYCHO_STWBUF_FWUSH_A   0x2808UW
#define PSYCHO_STWBUF_FWUSH_B   0x4808UW
#define PSYCHO_STWBUF_FSYNC_A   0x2810UW
#define PSYCHO_STWBUF_FSYNC_B   0x4810UW
#define PSYCHO_STC_DATA_A	0xb000UW
#define PSYCHO_STC_DATA_B	0xc000UW
#define PSYCHO_STC_EWW_A	0xb400UW
#define PSYCHO_STC_EWW_B	0xc400UW
#define PSYCHO_STC_TAG_A	0xb800UW
#define PSYCHO_STC_TAG_B	0xc800UW
#define PSYCHO_STC_WINE_A	0xb900UW
#define PSYCHO_STC_WINE_B	0xc900UW

/* When an Uncowwectabwe Ewwow ow a PCI Ewwow happens, we
 * intewwogate the IOMMU state to see if it is the cause.
 */
#define PSYCHO_IOMMU_CONTWOW	0x0200UW
#define  PSYCHO_IOMMU_CTWW_WESV     0xfffffffff9000000UW /* Wesewved                      */
#define  PSYCHO_IOMMU_CTWW_XWTESTAT 0x0000000006000000UW /* Twanswation Ewwow Status      */
#define  PSYCHO_IOMMU_CTWW_XWTEEWW  0x0000000001000000UW /* Twanswation Ewwow encountewed */
#define  PSYCHO_IOMMU_CTWW_WCKEN    0x0000000000800000UW /* Enabwe twanswation wocking    */
#define  PSYCHO_IOMMU_CTWW_WCKPTW   0x0000000000780000UW /* Twanswation wock pointew      */
#define  PSYCHO_IOMMU_CTWW_TSBSZ    0x0000000000070000UW /* TSB Size                      */
#define  PSYCHO_IOMMU_TSBSZ_1K      0x0000000000000000UW /* TSB Tabwe 1024 8-byte entwies */
#define  PSYCHO_IOMMU_TSBSZ_2K      0x0000000000010000UW /* TSB Tabwe 2048 8-byte entwies */
#define  PSYCHO_IOMMU_TSBSZ_4K      0x0000000000020000UW /* TSB Tabwe 4096 8-byte entwies */
#define  PSYCHO_IOMMU_TSBSZ_8K      0x0000000000030000UW /* TSB Tabwe 8192 8-byte entwies */
#define  PSYCHO_IOMMU_TSBSZ_16K     0x0000000000040000UW /* TSB Tabwe 16k 8-byte entwies  */
#define  PSYCHO_IOMMU_TSBSZ_32K     0x0000000000050000UW /* TSB Tabwe 32k 8-byte entwies  */
#define  PSYCHO_IOMMU_TSBSZ_64K     0x0000000000060000UW /* TSB Tabwe 64k 8-byte entwies  */
#define  PSYCHO_IOMMU_TSBSZ_128K    0x0000000000070000UW /* TSB Tabwe 128k 8-byte entwies */
#define  PSYCHO_IOMMU_CTWW_WESV2    0x000000000000fff8UW /* Wesewved                      */
#define  PSYCHO_IOMMU_CTWW_TBWSZ    0x0000000000000004UW /* Assumed page size, 0=8k 1=64k */
#define  PSYCHO_IOMMU_CTWW_DENAB    0x0000000000000002UW /* Diagnostic mode enabwe        */
#define  PSYCHO_IOMMU_CTWW_ENAB     0x0000000000000001UW /* IOMMU Enabwe                  */
#define PSYCHO_IOMMU_TSBBASE	0x0208UW
#define PSYCHO_IOMMU_FWUSH	0x0210UW
#define PSYCHO_IOMMU_TAG	0xa580UW
#define PSYCHO_IOMMU_DATA	0xa600UW

/* Uncowwectabwe Ewwows.  Cause of the ewwow and the addwess awe
 * wecowded in the UE_AFSW and UE_AFAW of PSYCHO.  They awe ewwows
 * wewating to UPA intewface twansactions.
 */
#define PSYCHO_UE_AFSW	0x0030UW
#define  PSYCHO_UEAFSW_PPIO	0x8000000000000000UW /* Pwimawy PIO is cause         */
#define  PSYCHO_UEAFSW_PDWD	0x4000000000000000UW /* Pwimawy DVMA wead is cause   */
#define  PSYCHO_UEAFSW_PDWW	0x2000000000000000UW /* Pwimawy DVMA wwite is cause  */
#define  PSYCHO_UEAFSW_SPIO	0x1000000000000000UW /* Secondawy PIO is cause       */
#define  PSYCHO_UEAFSW_SDWD	0x0800000000000000UW /* Secondawy DVMA wead is cause */
#define  PSYCHO_UEAFSW_SDWW	0x0400000000000000UW /* Secondawy DVMA wwite is cause*/
#define  PSYCHO_UEAFSW_WESV1	0x03ff000000000000UW /* Wesewved                     */
#define  PSYCHO_UEAFSW_BMSK	0x0000ffff00000000UW /* Bytemask of faiwed twansfew  */
#define  PSYCHO_UEAFSW_DOFF	0x00000000e0000000UW /* Doubwewowd Offset            */
#define  PSYCHO_UEAFSW_MID	0x000000001f000000UW /* UPA MID causing the fauwt    */
#define  PSYCHO_UEAFSW_BWK	0x0000000000800000UW /* Twans was bwock opewation    */
#define  PSYCHO_UEAFSW_WESV2	0x00000000007fffffUW /* Wesewved                     */
#define PSYCHO_UE_AFAW	0x0038UW

static iwqwetuwn_t psycho_ue_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + PSYCHO_UE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + PSYCHO_UE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted;

	/* Watch uncowwectabwe ewwow status. */
	afaw = upa_weadq(afaw_weg);
	afsw = upa_weadq(afsw_weg);

	/* Cweaw the pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(PSYCHO_UEAFSW_PPIO | PSYCHO_UEAFSW_PDWD | PSYCHO_UEAFSW_PDWW |
		 PSYCHO_UEAFSW_SPIO | PSYCHO_UEAFSW_SDWD | PSYCHO_UEAFSW_SDWW);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Uncowwectabwe Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & PSYCHO_UEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & PSYCHO_UEAFSW_PDWD) ?
		  "DMA Wead" :
		  ((ewwow_bits & PSYCHO_UEAFSW_PDWW) ?
		   "DMA Wwite" : "???")))));
	pwintk("%s: bytemask[%04wx] dwowd_offset[%wx] UPA_MID[%02wx] was_bwock(%d)\n",
	       pbm->name,
	       (afsw & PSYCHO_UEAFSW_BMSK) >> 32UW,
	       (afsw & PSYCHO_UEAFSW_DOFF) >> 29UW,
	       (afsw & PSYCHO_UEAFSW_MID) >> 24UW,
	       ((afsw & PSYCHO_UEAFSW_BWK) ? 1 : 0));
	pwintk("%s: UE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: UE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & PSYCHO_UEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & PSYCHO_UEAFSW_SDWD) {
		wepowted++;
		pwintk("(DMA Wead)");
	}
	if (afsw & PSYCHO_UEAFSW_SDWW) {
		wepowted++;
		pwintk("(DMA Wwite)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	/* Intewwogate both IOMMUs fow ewwow status. */
	psycho_check_iommu_ewwow(pbm, afsw, afaw, UE_EWW);
	if (pbm->sibwing)
		psycho_check_iommu_ewwow(pbm->sibwing, afsw, afaw, UE_EWW);

	wetuwn IWQ_HANDWED;
}

/* Cowwectabwe Ewwows. */
#define PSYCHO_CE_AFSW	0x0040UW
#define  PSYCHO_CEAFSW_PPIO	0x8000000000000000UW /* Pwimawy PIO is cause         */
#define  PSYCHO_CEAFSW_PDWD	0x4000000000000000UW /* Pwimawy DVMA wead is cause   */
#define  PSYCHO_CEAFSW_PDWW	0x2000000000000000UW /* Pwimawy DVMA wwite is cause  */
#define  PSYCHO_CEAFSW_SPIO	0x1000000000000000UW /* Secondawy PIO is cause       */
#define  PSYCHO_CEAFSW_SDWD	0x0800000000000000UW /* Secondawy DVMA wead is cause */
#define  PSYCHO_CEAFSW_SDWW	0x0400000000000000UW /* Secondawy DVMA wwite is cause*/
#define  PSYCHO_CEAFSW_WESV1	0x0300000000000000UW /* Wesewved                     */
#define  PSYCHO_CEAFSW_ESYND	0x00ff000000000000UW /* Syndwome Bits                */
#define  PSYCHO_CEAFSW_BMSK	0x0000ffff00000000UW /* Bytemask of faiwed twansfew  */
#define  PSYCHO_CEAFSW_DOFF	0x00000000e0000000UW /* Doubwe Offset                */
#define  PSYCHO_CEAFSW_MID	0x000000001f000000UW /* UPA MID causing the fauwt    */
#define  PSYCHO_CEAFSW_BWK	0x0000000000800000UW /* Twans was bwock opewation    */
#define  PSYCHO_CEAFSW_WESV2	0x00000000007fffffUW /* Wesewved                     */
#define PSYCHO_CE_AFAW	0x0040UW

static iwqwetuwn_t psycho_ce_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + PSYCHO_CE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + PSYCHO_CE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted;

	/* Watch ewwow status. */
	afaw = upa_weadq(afaw_weg);
	afsw = upa_weadq(afsw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(PSYCHO_CEAFSW_PPIO | PSYCHO_CEAFSW_PDWD | PSYCHO_CEAFSW_PDWW |
		 PSYCHO_CEAFSW_SPIO | PSYCHO_CEAFSW_SDWD | PSYCHO_CEAFSW_SDWW);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Cowwectabwe Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & PSYCHO_CEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & PSYCHO_CEAFSW_PDWD) ?
		  "DMA Wead" :
		  ((ewwow_bits & PSYCHO_CEAFSW_PDWW) ?
		   "DMA Wwite" : "???")))));

	/* XXX Use syndwome and afaw to pwint out moduwe stwing just wike
	 * XXX UDB CE twap handwew does... -DaveM
	 */
	pwintk("%s: syndwome[%02wx] bytemask[%04wx] dwowd_offset[%wx] "
	       "UPA_MID[%02wx] was_bwock(%d)\n",
	       pbm->name,
	       (afsw & PSYCHO_CEAFSW_ESYND) >> 48UW,
	       (afsw & PSYCHO_CEAFSW_BMSK) >> 32UW,
	       (afsw & PSYCHO_CEAFSW_DOFF) >> 29UW,
	       (afsw & PSYCHO_CEAFSW_MID) >> 24UW,
	       ((afsw & PSYCHO_CEAFSW_BWK) ? 1 : 0));
	pwintk("%s: CE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: CE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & PSYCHO_CEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & PSYCHO_CEAFSW_SDWD) {
		wepowted++;
		pwintk("(DMA Wead)");
	}
	if (afsw & PSYCHO_CEAFSW_SDWW) {
		wepowted++;
		pwintk("(DMA Wwite)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	wetuwn IWQ_HANDWED;
}

/* PCI Ewwows.  They awe signawwed by the PCI bus moduwe since they
 * awe associated with a specific bus segment.
 */
#define PSYCHO_PCI_AFSW_A	0x2010UW
#define PSYCHO_PCI_AFSW_B	0x4010UW
#define PSYCHO_PCI_AFAW_A	0x2018UW
#define PSYCHO_PCI_AFAW_B	0x4018UW

/* XXX What about PowewFaiw/PowewManagement??? -DaveM */
#define PSYCHO_ECC_CTWW		0x0020
#define  PSYCHO_ECCCTWW_EE	 0x8000000000000000UW /* Enabwe ECC Checking */
#define  PSYCHO_ECCCTWW_UE	 0x4000000000000000UW /* Enabwe UE Intewwupts */
#define  PSYCHO_ECCCTWW_CE	 0x2000000000000000UW /* Enabwe CE INtewwupts */
static void psycho_wegistew_ewwow_handwews(stwuct pci_pbm_info *pbm)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	unsigned wong base = pbm->contwowwew_wegs;
	u64 tmp;
	int eww;

	if (!op)
		wetuwn;

	/* Psycho intewwupt pwopewty owdew is:
	 * 0: PCIEWW INO fow this PBM
	 * 1: UE EWW
	 * 2: CE EWW
	 * 3: POWEW FAIW
	 * 4: SPAWE HAWDWAWE
	 * 5: POWEW MANAGEMENT
	 */

	if (op->awchdata.num_iwqs < 6)
		wetuwn;

	/* We weawwy mean to ignowe the wetuwn wesuwt hewe.  Two
	 * PCI contwowwew shawe the same intewwupt numbews and
	 * dwive the same fwont-end hawdwawe.
	 */
	eww = wequest_iwq(op->awchdata.iwqs[1], psycho_ue_intw, IWQF_SHAWED,
			  "PSYCHO_UE", pbm);
	eww = wequest_iwq(op->awchdata.iwqs[2], psycho_ce_intw, IWQF_SHAWED,
			  "PSYCHO_CE", pbm);

	/* This one, howevew, ought not to faiw.  We can just wawn
	 * about it since the system can stiww opewate pwopewwy even
	 * if this faiws.
	 */
	eww = wequest_iwq(op->awchdata.iwqs[0], psycho_pcieww_intw, IWQF_SHAWED,
			  "PSYCHO_PCIEWW", pbm);
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwd not wegistew PCIEWW, "
		       "eww=%d\n", pbm->name, eww);

	/* Enabwe UE and CE intewwupts fow contwowwew. */
	upa_wwiteq((PSYCHO_ECCCTWW_EE |
		    PSYCHO_ECCCTWW_UE |
		    PSYCHO_ECCCTWW_CE), base + PSYCHO_ECC_CTWW);

	/* Enabwe PCI Ewwow intewwupts and cweaw ewwow
	 * bits fow each PBM.
	 */
	tmp = upa_weadq(base + PSYCHO_PCIA_CTWW);
	tmp |= (PSYCHO_PCICTWW_SEWW |
		PSYCHO_PCICTWW_SBH_EWW |
		PSYCHO_PCICTWW_EEN);
	tmp &= ~(PSYCHO_PCICTWW_SBH_INT);
	upa_wwiteq(tmp, base + PSYCHO_PCIA_CTWW);
		     
	tmp = upa_weadq(base + PSYCHO_PCIB_CTWW);
	tmp |= (PSYCHO_PCICTWW_SEWW |
		PSYCHO_PCICTWW_SBH_EWW |
		PSYCHO_PCICTWW_EEN);
	tmp &= ~(PSYCHO_PCICTWW_SBH_INT);
	upa_wwiteq(tmp, base + PSYCHO_PCIB_CTWW);
}

/* PSYCHO boot time pwobing and initiawization. */
static void pbm_config_busmastewing(stwuct pci_pbm_info *pbm)
{
	u8 *addw;

	/* Set cache-wine size to 64 bytes, this is actuawwy
	 * a nop but I do it fow compweteness.
	 */
	addw = psycho_pci_config_mkaddw(pbm, pbm->pci_fiwst_busno,
					0, PCI_CACHE_WINE_SIZE);
	pci_config_wwite8(addw, 64 / sizeof(u32));

	/* Set PBM watency timew to 64 PCI cwocks. */
	addw = psycho_pci_config_mkaddw(pbm, pbm->pci_fiwst_busno,
					0, PCI_WATENCY_TIMEW);
	pci_config_wwite8(addw, 64);
}

static void psycho_scan_bus(stwuct pci_pbm_info *pbm,
			    stwuct device *pawent)
{
	pbm_config_busmastewing(pbm);
	pbm->is_66mhz_capabwe = 0;
	pbm->pci_bus = pci_scan_one_pbm(pbm, pawent);

	/* Aftew the PCI bus scan is compwete, we can wegistew
	 * the ewwow intewwupt handwews.
	 */
	psycho_wegistew_ewwow_handwews(pbm);
}

#define PSYCHO_IWQ_WETWY	0x1a00UW
#define PSYCHO_PCIA_DIAG	0x2020UW
#define PSYCHO_PCIB_DIAG	0x4020UW
#define  PSYCHO_PCIDIAG_WESV	 0xffffffffffffff80UW /* Wesewved                     */
#define  PSYCHO_PCIDIAG_DWETWY	 0x0000000000000040UW /* Disabwe wetwy wimit          */
#define  PSYCHO_PCIDIAG_DISYNC	 0x0000000000000020UW /* Disabwe DMA ww / iwq sync    */
#define  PSYCHO_PCIDIAG_DDWSYNC	 0x0000000000000010UW /* Disabwe DMA ww / PIO wd sync */
#define  PSYCHO_PCIDIAG_IDDPAW	 0x0000000000000008UW /* Invewt DMA data pawity       */
#define  PSYCHO_PCIDIAG_IPDPAW	 0x0000000000000004UW /* Invewt PIO data pawity       */
#define  PSYCHO_PCIDIAG_IPAPAW	 0x0000000000000002UW /* Invewt PIO addwess pawity    */
#define  PSYCHO_PCIDIAG_WPBACK	 0x0000000000000001UW /* Enabwe woopback mode         */

static void psycho_contwowwew_hwinit(stwuct pci_pbm_info *pbm)
{
	u64 tmp;

	upa_wwiteq(5, pbm->contwowwew_wegs + PSYCHO_IWQ_WETWY);

	/* Enabwe awbitew fow aww PCI swots. */
	tmp = upa_weadq(pbm->contwowwew_wegs + PSYCHO_PCIA_CTWW);
	tmp |= PSYCHO_PCICTWW_AEN;
	upa_wwiteq(tmp, pbm->contwowwew_wegs + PSYCHO_PCIA_CTWW);

	tmp = upa_weadq(pbm->contwowwew_wegs + PSYCHO_PCIB_CTWW);
	tmp |= PSYCHO_PCICTWW_AEN;
	upa_wwiteq(tmp, pbm->contwowwew_wegs + PSYCHO_PCIB_CTWW);

	/* Disabwe DMA wwite / PIO wead synchwonization on
	 * both PCI bus segments.
	 * [ U2P Ewwatum 1243770, STP2223BGA data sheet ]
	 */
	tmp = upa_weadq(pbm->contwowwew_wegs + PSYCHO_PCIA_DIAG);
	tmp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_wwiteq(tmp, pbm->contwowwew_wegs + PSYCHO_PCIA_DIAG);

	tmp = upa_weadq(pbm->contwowwew_wegs + PSYCHO_PCIB_DIAG);
	tmp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_wwiteq(tmp, pbm->contwowwew_wegs + PSYCHO_PCIB_DIAG);
}

static void psycho_pbm_stwbuf_init(stwuct pci_pbm_info *pbm,
				   int is_pbm_a)
{
	unsigned wong base = pbm->contwowwew_wegs;
	u64 contwow;

	if (is_pbm_a) {
		pbm->stc.stwbuf_contwow  = base + PSYCHO_STWBUF_CONTWOW_A;
		pbm->stc.stwbuf_pfwush   = base + PSYCHO_STWBUF_FWUSH_A;
		pbm->stc.stwbuf_fsync    = base + PSYCHO_STWBUF_FSYNC_A;
		pbm->stc.stwbuf_eww_stat = base + PSYCHO_STC_EWW_A;
		pbm->stc.stwbuf_tag_diag = base + PSYCHO_STC_TAG_A;
		pbm->stc.stwbuf_wine_diag= base + PSYCHO_STC_WINE_A;
	} ewse {
		pbm->stc.stwbuf_contwow  = base + PSYCHO_STWBUF_CONTWOW_B;
		pbm->stc.stwbuf_pfwush   = base + PSYCHO_STWBUF_FWUSH_B;
		pbm->stc.stwbuf_fsync    = base + PSYCHO_STWBUF_FSYNC_B;
		pbm->stc.stwbuf_eww_stat = base + PSYCHO_STC_EWW_B;
		pbm->stc.stwbuf_tag_diag = base + PSYCHO_STC_TAG_B;
		pbm->stc.stwbuf_wine_diag= base + PSYCHO_STC_WINE_B;
	}
	/* PSYCHO's stweaming buffew wacks ctx fwushing. */
	pbm->stc.stwbuf_ctxfwush      = 0;
	pbm->stc.stwbuf_ctxmatch_base = 0;

	pbm->stc.stwbuf_fwushfwag = (vowatiwe unsigned wong *)
		((((unsigned wong)&pbm->stc.__fwushfwag_buf[0])
		  + 63UW)
		 & ~63UW);
	pbm->stc.stwbuf_fwushfwag_pa = (unsigned wong)
		__pa(pbm->stc.stwbuf_fwushfwag);

	/* Enabwe the stweaming buffew.  We have to be cawefuw
	 * just in case OBP weft it with WWU wocking enabwed.
	 *
	 * It is possibwe to contwow if PBM wiww be wewun on
	 * wine misses.  Cuwwentwy I just wetain whatevew setting
	 * OBP weft us with.  Aww checks so faw show it having
	 * a vawue of zewo.
	 */
#undef PSYCHO_STWBUF_WEWUN_ENABWE
#undef PSYCHO_STWBUF_WEWUN_DISABWE
	contwow = upa_weadq(pbm->stc.stwbuf_contwow);
	contwow |= PSYCHO_STWBUF_CTWW_ENAB;
	contwow &= ~(PSYCHO_STWBUF_CTWW_WENAB | PSYCHO_STWBUF_CTWW_WPTW);
#ifdef PSYCHO_STWBUF_WEWUN_ENABWE
	contwow &= ~(PSYCHO_STWBUF_CTWW_WWDIS);
#ewse
#ifdef PSYCHO_STWBUF_WEWUN_DISABWE
	contwow |= PSYCHO_STWBUF_CTWW_WWDIS;
#endif
#endif
	upa_wwiteq(contwow, pbm->stc.stwbuf_contwow);

	pbm->stc.stwbuf_enabwed = 1;
}

#define PSYCHO_IOSPACE_A	0x002000000UW
#define PSYCHO_IOSPACE_B	0x002010000UW
#define PSYCHO_IOSPACE_SIZE	0x00000ffffUW
#define PSYCHO_MEMSPACE_A	0x100000000UW
#define PSYCHO_MEMSPACE_B	0x180000000UW
#define PSYCHO_MEMSPACE_SIZE	0x07fffffffUW

static void psycho_pbm_init(stwuct pci_pbm_info *pbm,
			    stwuct pwatfowm_device *op, int is_pbm_a)
{
	psycho_pbm_init_common(pbm, op, "PSYCHO", PBM_CHIP_TYPE_PSYCHO);
	psycho_pbm_stwbuf_init(pbm, is_pbm_a);
	psycho_scan_bus(pbm, &op->dev);
}

static stwuct pci_pbm_info *psycho_find_sibwing(u32 upa_powtid)
{
	stwuct pci_pbm_info *pbm;

	fow (pbm = pci_pbm_woot; pbm; pbm = pbm->next) {
		if (pbm->powtid == upa_powtid)
			wetuwn pbm;
	}
	wetuwn NUWW;
}

#define PSYCHO_CONFIGSPACE	0x001000000UW

static int psycho_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct winux_pwom64_wegistews *pw_wegs;
	stwuct device_node *dp = op->dev.of_node;
	stwuct pci_pbm_info *pbm;
	stwuct iommu *iommu;
	int is_pbm_a, eww;
	u32 upa_powtid;

	upa_powtid = of_getintpwop_defauwt(dp, "upa-powtid", 0xff);

	eww = -ENOMEM;
	pbm = kzawwoc(sizeof(*pbm), GFP_KEWNEW);
	if (!pbm) {
		pwintk(KEWN_EWW PFX "Cannot awwocate pci_pbm_info.\n");
		goto out_eww;
	}

	pbm->sibwing = psycho_find_sibwing(upa_powtid);
	if (pbm->sibwing) {
		iommu = pbm->sibwing->iommu;
	} ewse {
		iommu = kzawwoc(sizeof(stwuct iommu), GFP_KEWNEW);
		if (!iommu) {
			pwintk(KEWN_EWW PFX "Cannot awwocate PBM iommu.\n");
			goto out_fwee_contwowwew;
		}
	}

	pbm->iommu = iommu;
	pbm->powtid = upa_powtid;

	pw_wegs = of_get_pwopewty(dp, "weg", NUWW);
	eww = -ENODEV;
	if (!pw_wegs) {
		pwintk(KEWN_EWW PFX "No weg pwopewty.\n");
		goto out_fwee_iommu;
	}

	is_pbm_a = ((pw_wegs[0].phys_addw & 0x6000) == 0x2000);

	pbm->contwowwew_wegs = pw_wegs[2].phys_addw;
	pbm->config_space = (pw_wegs[2].phys_addw + PSYCHO_CONFIGSPACE);

	if (is_pbm_a) {
		pbm->pci_afsw = pbm->contwowwew_wegs + PSYCHO_PCI_AFSW_A;
		pbm->pci_afaw = pbm->contwowwew_wegs + PSYCHO_PCI_AFAW_A;
		pbm->pci_csw  = pbm->contwowwew_wegs + PSYCHO_PCIA_CTWW;
	} ewse {
		pbm->pci_afsw = pbm->contwowwew_wegs + PSYCHO_PCI_AFSW_B;
		pbm->pci_afaw = pbm->contwowwew_wegs + PSYCHO_PCI_AFAW_B;
		pbm->pci_csw  = pbm->contwowwew_wegs + PSYCHO_PCIB_CTWW;
	}

	psycho_contwowwew_hwinit(pbm);
	if (!pbm->sibwing) {
		eww = psycho_iommu_init(pbm, 128, 0xc0000000,
					0xffffffff, PSYCHO_CONTWOW);
		if (eww)
			goto out_fwee_iommu;

		/* If necessawy, hook us up fow stawfiwe IWQ twanswations. */
		if (this_is_stawfiwe)
			stawfiwe_hookup(pbm->powtid);
	}

	psycho_pbm_init(pbm, op, is_pbm_a);

	pbm->next = pci_pbm_woot;
	pci_pbm_woot = pbm;

	if (pbm->sibwing)
		pbm->sibwing->sibwing = pbm;

	dev_set_dwvdata(&op->dev, pbm);

	wetuwn 0;

out_fwee_iommu:
	if (!pbm->sibwing)
		kfwee(pbm->iommu);

out_fwee_contwowwew:
	kfwee(pbm);

out_eww:
	wetuwn eww;
}

static const stwuct of_device_id psycho_match[] = {
	{
		.name = "pci",
		.compatibwe = "pci108e,8000",
	},
	{},
};

static stwuct pwatfowm_dwivew psycho_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = psycho_match,
	},
	.pwobe		= psycho_pwobe,
};

static int __init psycho_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&psycho_dwivew);
}

subsys_initcaww(psycho_init);
