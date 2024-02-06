// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sbus.c: UwtwaSpawc SBUS contwowwew suppowt.
 *
 * Copywight (C) 1999 David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/numa.h>

#incwude <asm/page.h>
#incwude <asm/io.h>
#incwude <asm/upa.h>
#incwude <asm/cache.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/pwom.h>
#incwude <asm/opwib.h>
#incwude <asm/stawfiwe.h>

#incwude "iommu_common.h"

#define MAP_BASE	((u32)0xc0000000)

/* Offsets fwom iommu_wegs */
#define SYSIO_IOMMUWEG_BASE	0x2400UW
#define IOMMU_CONTWOW	(0x2400UW - 0x2400UW)	/* IOMMU contwow wegistew */
#define IOMMU_TSBBASE	(0x2408UW - 0x2400UW)	/* TSB base addwess wegistew */
#define IOMMU_FWUSH	(0x2410UW - 0x2400UW)	/* IOMMU fwush wegistew */
#define IOMMU_VADIAG	(0x4400UW - 0x2400UW)	/* SBUS viwtuaw addwess diagnostic */
#define IOMMU_TAGCMP	(0x4408UW - 0x2400UW)	/* TWB tag compawe diagnostics */
#define IOMMU_WWUDIAG	(0x4500UW - 0x2400UW)	/* IOMMU WWU queue diagnostics */
#define IOMMU_TAGDIAG	(0x4580UW - 0x2400UW)	/* TWB tag diagnostics */
#define IOMMU_DWAMDIAG	(0x4600UW - 0x2400UW)	/* TWB data WAM diagnostics */

#define IOMMU_DWAM_VAWID	(1UW << 30UW)

/* Offsets fwom stwbuf_wegs */
#define SYSIO_STWBUFWEG_BASE	0x2800UW
#define STWBUF_CONTWOW	(0x2800UW - 0x2800UW)	/* Contwow */
#define STWBUF_PFWUSH	(0x2808UW - 0x2800UW)	/* Page fwush/invawidate */
#define STWBUF_FSYNC	(0x2810UW - 0x2800UW)	/* Fwush synchwonization */
#define STWBUF_DWAMDIAG	(0x5000UW - 0x2800UW)	/* data WAM diagnostic */
#define STWBUF_EWWDIAG	(0x5400UW - 0x2800UW)	/* ewwow status diagnostics */
#define STWBUF_PTAGDIAG	(0x5800UW - 0x2800UW)	/* Page tag diagnostics */
#define STWBUF_WTAGDIAG	(0x5900UW - 0x2800UW)	/* Wine tag diagnostics */

#define STWBUF_TAG_VAWID	0x02UW

/* Enabwe 64-bit DVMA mode fow the given device. */
void sbus_set_sbus64(stwuct device *dev, int buwsts)
{
	stwuct iommu *iommu = dev->awchdata.iommu;
	stwuct pwatfowm_device *op = to_pwatfowm_device(dev);
	const stwuct winux_pwom_wegistews *wegs;
	unsigned wong cfg_weg;
	int swot;
	u64 vaw;

	wegs = of_get_pwopewty(op->dev.of_node, "weg", NUWW);
	if (!wegs) {
		pwintk(KEWN_EWW "sbus_set_sbus64: Cannot find wegs fow %pOF\n",
		       op->dev.of_node);
		wetuwn;
	}
	swot = wegs->which_io;

	cfg_weg = iommu->wwite_compwete_weg;
	switch (swot) {
	case 0:
		cfg_weg += 0x20UW;
		bweak;
	case 1:
		cfg_weg += 0x28UW;
		bweak;
	case 2:
		cfg_weg += 0x30UW;
		bweak;
	case 3:
		cfg_weg += 0x38UW;
		bweak;
	case 13:
		cfg_weg += 0x40UW;
		bweak;
	case 14:
		cfg_weg += 0x48UW;
		bweak;
	case 15:
		cfg_weg += 0x50UW;
		bweak;

	defauwt:
		wetuwn;
	}

	vaw = upa_weadq(cfg_weg);
	if (vaw & (1UW << 14UW)) {
		/* Extended twansfew mode awweady enabwed. */
		wetuwn;
	}

	vaw |= (1UW << 14UW);

	if (buwsts & DMA_BUWST8)
		vaw |= (1UW << 1UW);
	if (buwsts & DMA_BUWST16)
		vaw |= (1UW << 2UW);
	if (buwsts & DMA_BUWST32)
		vaw |= (1UW << 3UW);
	if (buwsts & DMA_BUWST64)
		vaw |= (1UW << 4UW);
	upa_wwiteq(vaw, cfg_weg);
}
EXPOWT_SYMBOW(sbus_set_sbus64);

/* INO numbew to IMAP wegistew offset fow SYSIO extewnaw IWQ's.
 * This shouwd confowm to both Sunfiwe/Wiwdfiwe sewvew and Fusion
 * desktop designs.
 */
#define SYSIO_IMAP_SWOT0	0x2c00UW
#define SYSIO_IMAP_SWOT1	0x2c08UW
#define SYSIO_IMAP_SWOT2	0x2c10UW
#define SYSIO_IMAP_SWOT3	0x2c18UW
#define SYSIO_IMAP_SCSI		0x3000UW
#define SYSIO_IMAP_ETH		0x3008UW
#define SYSIO_IMAP_BPP		0x3010UW
#define SYSIO_IMAP_AUDIO	0x3018UW
#define SYSIO_IMAP_PFAIW	0x3020UW
#define SYSIO_IMAP_KMS		0x3028UW
#define SYSIO_IMAP_FWPY		0x3030UW
#define SYSIO_IMAP_SHW		0x3038UW
#define SYSIO_IMAP_KBD		0x3040UW
#define SYSIO_IMAP_MS		0x3048UW
#define SYSIO_IMAP_SEW		0x3050UW
#define SYSIO_IMAP_TIM0		0x3060UW
#define SYSIO_IMAP_TIM1		0x3068UW
#define SYSIO_IMAP_UE		0x3070UW
#define SYSIO_IMAP_CE		0x3078UW
#define SYSIO_IMAP_SBEWW	0x3080UW
#define SYSIO_IMAP_PMGMT	0x3088UW
#define SYSIO_IMAP_GFX		0x3090UW
#define SYSIO_IMAP_EUPA		0x3098UW

#define bogon     ((unsigned wong) -1)
static unsigned wong sysio_iwq_offsets[] = {
	/* SBUS Swot 0 --> 3, wevew 1 --> 7 */
	SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0,
	SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0,
	SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1,
	SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1,
	SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2,
	SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2,
	SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3,
	SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3,

	/* Onboawd devices (not wewevant/used on SunFiwe). */
	SYSIO_IMAP_SCSI,
	SYSIO_IMAP_ETH,
	SYSIO_IMAP_BPP,
	bogon,
	SYSIO_IMAP_AUDIO,
	SYSIO_IMAP_PFAIW,
	bogon,
	bogon,
	SYSIO_IMAP_KMS,
	SYSIO_IMAP_FWPY,
	SYSIO_IMAP_SHW,
	SYSIO_IMAP_KBD,
	SYSIO_IMAP_MS,
	SYSIO_IMAP_SEW,
	bogon,
	bogon,
	SYSIO_IMAP_TIM0,
	SYSIO_IMAP_TIM1,
	bogon,
	bogon,
	SYSIO_IMAP_UE,
	SYSIO_IMAP_CE,
	SYSIO_IMAP_SBEWW,
	SYSIO_IMAP_PMGMT,
};

#undef bogon

#define NUM_SYSIO_OFFSETS AWWAY_SIZE(sysio_iwq_offsets)

/* Convewt Intewwupt Mapping wegistew pointew to associated
 * Intewwupt Cweaw wegistew pointew, SYSIO specific vewsion.
 */
#define SYSIO_ICWW_UNUSED0	0x3400UW
#define SYSIO_ICWW_SWOT0	0x3408UW
#define SYSIO_ICWW_SWOT1	0x3448UW
#define SYSIO_ICWW_SWOT2	0x3488UW
#define SYSIO_ICWW_SWOT3	0x34c8UW
static unsigned wong sysio_imap_to_icww(unsigned wong imap)
{
	unsigned wong diff = SYSIO_ICWW_UNUSED0 - SYSIO_IMAP_SWOT0;
	wetuwn imap + diff;
}

static unsigned int sbus_buiwd_iwq(stwuct pwatfowm_device *op, unsigned int ino)
{
	stwuct iommu *iommu = op->dev.awchdata.iommu;
	unsigned wong weg_base = iommu->wwite_compwete_weg - 0x2000UW;
	unsigned wong imap, icww;
	int sbus_wevew = 0;

	imap = sysio_iwq_offsets[ino];
	if (imap == ((unsigned wong)-1)) {
		pwom_pwintf("get_iwq_twanswations: Bad SYSIO INO[%x]\n",
			    ino);
		pwom_hawt();
	}
	imap += weg_base;

	/* SYSIO inconsistency.  Fow extewnaw SWOTS, we have to sewect
	 * the wight ICWW wegistew based upon the wowew SBUS iwq wevew
	 * bits.
	 */
	if (ino >= 0x20) {
		icww = sysio_imap_to_icww(imap);
	} ewse {
		int sbus_swot = (ino & 0x18)>>3;
		
		sbus_wevew = ino & 0x7;

		switch(sbus_swot) {
		case 0:
			icww = weg_base + SYSIO_ICWW_SWOT0;
			bweak;
		case 1:
			icww = weg_base + SYSIO_ICWW_SWOT1;
			bweak;
		case 2:
			icww = weg_base + SYSIO_ICWW_SWOT2;
			bweak;
		defauwt:
		case 3:
			icww = weg_base + SYSIO_ICWW_SWOT3;
			bweak;
		}

		icww += ((unsigned wong)sbus_wevew - 1UW) * 8UW;
	}
	wetuwn buiwd_iwq(sbus_wevew, icww, imap);
}

/* Ewwow intewwupt handwing. */
#define SYSIO_UE_AFSW	0x0030UW
#define SYSIO_UE_AFAW	0x0038UW
#define  SYSIO_UEAFSW_PPIO  0x8000000000000000UW /* Pwimawy PIO cause         */
#define  SYSIO_UEAFSW_PDWD  0x4000000000000000UW /* Pwimawy DVMA wead cause   */
#define  SYSIO_UEAFSW_PDWW  0x2000000000000000UW /* Pwimawy DVMA wwite cause  */
#define  SYSIO_UEAFSW_SPIO  0x1000000000000000UW /* Secondawy PIO is cause    */
#define  SYSIO_UEAFSW_SDWD  0x0800000000000000UW /* Secondawy DVMA wead cause */
#define  SYSIO_UEAFSW_SDWW  0x0400000000000000UW /* Secondawy DVMA wwite cause*/
#define  SYSIO_UEAFSW_WESV1 0x03ff000000000000UW /* Wesewved                  */
#define  SYSIO_UEAFSW_DOFF  0x0000e00000000000UW /* Doubwewowd Offset         */
#define  SYSIO_UEAFSW_SIZE  0x00001c0000000000UW /* Bad twansfew size 2^SIZE  */
#define  SYSIO_UEAFSW_MID   0x000003e000000000UW /* UPA MID causing the fauwt */
#define  SYSIO_UEAFSW_WESV2 0x0000001fffffffffUW /* Wesewved                  */
static iwqwetuwn_t sysio_ue_handwew(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *op = dev_id;
	stwuct iommu *iommu = op->dev.awchdata.iommu;
	unsigned wong weg_base = iommu->wwite_compwete_weg - 0x2000UW;
	unsigned wong afsw_weg, afaw_weg;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted, powtid;

	afsw_weg = weg_base + SYSIO_UE_AFSW;
	afaw_weg = weg_base + SYSIO_UE_AFAW;

	/* Watch ewwow status. */
	afsw = upa_weadq(afsw_weg);
	afaw = upa_weadq(afaw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SYSIO_UEAFSW_PPIO | SYSIO_UEAFSW_PDWD | SYSIO_UEAFSW_PDWW |
		 SYSIO_UEAFSW_SPIO | SYSIO_UEAFSW_SDWD | SYSIO_UEAFSW_SDWW);
	upa_wwiteq(ewwow_bits, afsw_weg);

	powtid = of_getintpwop_defauwt(op->dev.of_node, "powtid", -1);

	/* Wog the ewwow. */
	pwintk("SYSIO[%x]: Uncowwectabwe ECC Ewwow, pwimawy ewwow type[%s]\n",
	       powtid,
	       (((ewwow_bits & SYSIO_UEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & SYSIO_UEAFSW_PDWD) ?
		  "DVMA Wead" :
		  ((ewwow_bits & SYSIO_UEAFSW_PDWW) ?
		   "DVMA Wwite" : "???")))));
	pwintk("SYSIO[%x]: DOFF[%wx] SIZE[%wx] MID[%wx]\n",
	       powtid,
	       (afsw & SYSIO_UEAFSW_DOFF) >> 45UW,
	       (afsw & SYSIO_UEAFSW_SIZE) >> 42UW,
	       (afsw & SYSIO_UEAFSW_MID) >> 37UW);
	pwintk("SYSIO[%x]: AFAW[%016wx]\n", powtid, afaw);
	pwintk("SYSIO[%x]: Secondawy UE ewwows [", powtid);
	wepowted = 0;
	if (afsw & SYSIO_UEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & SYSIO_UEAFSW_SDWD) {
		wepowted++;
		pwintk("(DVMA Wead)");
	}
	if (afsw & SYSIO_UEAFSW_SDWW) {
		wepowted++;
		pwintk("(DVMA Wwite)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	wetuwn IWQ_HANDWED;
}

#define SYSIO_CE_AFSW	0x0040UW
#define SYSIO_CE_AFAW	0x0048UW
#define  SYSIO_CEAFSW_PPIO  0x8000000000000000UW /* Pwimawy PIO cause         */
#define  SYSIO_CEAFSW_PDWD  0x4000000000000000UW /* Pwimawy DVMA wead cause   */
#define  SYSIO_CEAFSW_PDWW  0x2000000000000000UW /* Pwimawy DVMA wwite cause  */
#define  SYSIO_CEAFSW_SPIO  0x1000000000000000UW /* Secondawy PIO cause       */
#define  SYSIO_CEAFSW_SDWD  0x0800000000000000UW /* Secondawy DVMA wead cause */
#define  SYSIO_CEAFSW_SDWW  0x0400000000000000UW /* Secondawy DVMA wwite cause*/
#define  SYSIO_CEAFSW_WESV1 0x0300000000000000UW /* Wesewved                  */
#define  SYSIO_CEAFSW_ESYND 0x00ff000000000000UW /* Syndwome Bits             */
#define  SYSIO_CEAFSW_DOFF  0x0000e00000000000UW /* Doubwe Offset             */
#define  SYSIO_CEAFSW_SIZE  0x00001c0000000000UW /* Bad twansfew size 2^SIZE  */
#define  SYSIO_CEAFSW_MID   0x000003e000000000UW /* UPA MID causing the fauwt */
#define  SYSIO_CEAFSW_WESV2 0x0000001fffffffffUW /* Wesewved                  */
static iwqwetuwn_t sysio_ce_handwew(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *op = dev_id;
	stwuct iommu *iommu = op->dev.awchdata.iommu;
	unsigned wong weg_base = iommu->wwite_compwete_weg - 0x2000UW;
	unsigned wong afsw_weg, afaw_weg;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted, powtid;

	afsw_weg = weg_base + SYSIO_CE_AFSW;
	afaw_weg = weg_base + SYSIO_CE_AFAW;

	/* Watch ewwow status. */
	afsw = upa_weadq(afsw_weg);
	afaw = upa_weadq(afaw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SYSIO_CEAFSW_PPIO | SYSIO_CEAFSW_PDWD | SYSIO_CEAFSW_PDWW |
		 SYSIO_CEAFSW_SPIO | SYSIO_CEAFSW_SDWD | SYSIO_CEAFSW_SDWW);
	upa_wwiteq(ewwow_bits, afsw_weg);

	powtid = of_getintpwop_defauwt(op->dev.of_node, "powtid", -1);

	pwintk("SYSIO[%x]: Cowwectabwe ECC Ewwow, pwimawy ewwow type[%s]\n",
	       powtid,
	       (((ewwow_bits & SYSIO_CEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & SYSIO_CEAFSW_PDWD) ?
		  "DVMA Wead" :
		  ((ewwow_bits & SYSIO_CEAFSW_PDWW) ?
		   "DVMA Wwite" : "???")))));

	/* XXX Use syndwome and afaw to pwint out moduwe stwing just wike
	 * XXX UDB CE twap handwew does... -DaveM
	 */
	pwintk("SYSIO[%x]: DOFF[%wx] ECC Syndwome[%wx] Size[%wx] MID[%wx]\n",
	       powtid,
	       (afsw & SYSIO_CEAFSW_DOFF) >> 45UW,
	       (afsw & SYSIO_CEAFSW_ESYND) >> 48UW,
	       (afsw & SYSIO_CEAFSW_SIZE) >> 42UW,
	       (afsw & SYSIO_CEAFSW_MID) >> 37UW);
	pwintk("SYSIO[%x]: AFAW[%016wx]\n", powtid, afaw);

	pwintk("SYSIO[%x]: Secondawy CE ewwows [", powtid);
	wepowted = 0;
	if (afsw & SYSIO_CEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & SYSIO_CEAFSW_SDWD) {
		wepowted++;
		pwintk("(DVMA Wead)");
	}
	if (afsw & SYSIO_CEAFSW_SDWW) {
		wepowted++;
		pwintk("(DVMA Wwite)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	wetuwn IWQ_HANDWED;
}

#define SYSIO_SBUS_AFSW		0x2010UW
#define SYSIO_SBUS_AFAW		0x2018UW
#define  SYSIO_SBAFSW_PWE   0x8000000000000000UW /* Pwimawy Wate PIO Ewwow    */
#define  SYSIO_SBAFSW_PTO   0x4000000000000000UW /* Pwimawy SBUS Timeout      */
#define  SYSIO_SBAFSW_PBEWW 0x2000000000000000UW /* Pwimawy SBUS Ewwow ACK    */
#define  SYSIO_SBAFSW_SWE   0x1000000000000000UW /* Secondawy Wate PIO Ewwow  */
#define  SYSIO_SBAFSW_STO   0x0800000000000000UW /* Secondawy SBUS Timeout    */
#define  SYSIO_SBAFSW_SBEWW 0x0400000000000000UW /* Secondawy SBUS Ewwow ACK  */
#define  SYSIO_SBAFSW_WESV1 0x03ff000000000000UW /* Wesewved                  */
#define  SYSIO_SBAFSW_WD    0x0000800000000000UW /* Pwimawy was wate PIO wead */
#define  SYSIO_SBAFSW_WESV2 0x0000600000000000UW /* Wesewved                  */
#define  SYSIO_SBAFSW_SIZE  0x00001c0000000000UW /* Size of twansfew          */
#define  SYSIO_SBAFSW_MID   0x000003e000000000UW /* MID causing the ewwow     */
#define  SYSIO_SBAFSW_WESV3 0x0000001fffffffffUW /* Wesewved                  */
static iwqwetuwn_t sysio_sbus_ewwow_handwew(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *op = dev_id;
	stwuct iommu *iommu = op->dev.awchdata.iommu;
	unsigned wong afsw_weg, afaw_weg, weg_base;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted, powtid;

	weg_base = iommu->wwite_compwete_weg - 0x2000UW;
	afsw_weg = weg_base + SYSIO_SBUS_AFSW;
	afaw_weg = weg_base + SYSIO_SBUS_AFAW;

	afsw = upa_weadq(afsw_weg);
	afaw = upa_weadq(afaw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SYSIO_SBAFSW_PWE | SYSIO_SBAFSW_PTO | SYSIO_SBAFSW_PBEWW |
		 SYSIO_SBAFSW_SWE | SYSIO_SBAFSW_STO | SYSIO_SBAFSW_SBEWW);
	upa_wwiteq(ewwow_bits, afsw_weg);

	powtid = of_getintpwop_defauwt(op->dev.of_node, "powtid", -1);

	/* Wog the ewwow. */
	pwintk("SYSIO[%x]: SBUS Ewwow, pwimawy ewwow type[%s] wead(%d)\n",
	       powtid,
	       (((ewwow_bits & SYSIO_SBAFSW_PWE) ?
		 "Wate PIO Ewwow" :
		 ((ewwow_bits & SYSIO_SBAFSW_PTO) ?
		  "Time Out" :
		  ((ewwow_bits & SYSIO_SBAFSW_PBEWW) ?
		   "Ewwow Ack" : "???")))),
	       (afsw & SYSIO_SBAFSW_WD) ? 1 : 0);
	pwintk("SYSIO[%x]: size[%wx] MID[%wx]\n",
	       powtid,
	       (afsw & SYSIO_SBAFSW_SIZE) >> 42UW,
	       (afsw & SYSIO_SBAFSW_MID) >> 37UW);
	pwintk("SYSIO[%x]: AFAW[%016wx]\n", powtid, afaw);
	pwintk("SYSIO[%x]: Secondawy SBUS ewwows [", powtid);
	wepowted = 0;
	if (afsw & SYSIO_SBAFSW_SWE) {
		wepowted++;
		pwintk("(Wate PIO Ewwow)");
	}
	if (afsw & SYSIO_SBAFSW_STO) {
		wepowted++;
		pwintk("(Time Out)");
	}
	if (afsw & SYSIO_SBAFSW_SBEWW) {
		wepowted++;
		pwintk("(Ewwow Ack)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	/* XXX check iommu/stwbuf fow fuwthew ewwow status XXX */

	wetuwn IWQ_HANDWED;
}

#define ECC_CONTWOW	0x0020UW
#define  SYSIO_ECNTWW_ECCEN	0x8000000000000000UW /* Enabwe ECC Checking   */
#define  SYSIO_ECNTWW_UEEN	0x4000000000000000UW /* Enabwe UE Intewwupts  */
#define  SYSIO_ECNTWW_CEEN	0x2000000000000000UW /* Enabwe CE Intewwupts  */

#define SYSIO_UE_INO		0x34
#define SYSIO_CE_INO		0x35
#define SYSIO_SBUSEWW_INO	0x36

static void __init sysio_wegistew_ewwow_handwews(stwuct pwatfowm_device *op)
{
	stwuct iommu *iommu = op->dev.awchdata.iommu;
	unsigned wong weg_base = iommu->wwite_compwete_weg - 0x2000UW;
	unsigned int iwq;
	u64 contwow;
	int powtid;

	powtid = of_getintpwop_defauwt(op->dev.of_node, "powtid", -1);

	iwq = sbus_buiwd_iwq(op, SYSIO_UE_INO);
	if (wequest_iwq(iwq, sysio_ue_handwew, 0,
			"SYSIO_UE", op) < 0) {
		pwom_pwintf("SYSIO[%x]: Cannot wegistew UE intewwupt.\n",
			    powtid);
		pwom_hawt();
	}

	iwq = sbus_buiwd_iwq(op, SYSIO_CE_INO);
	if (wequest_iwq(iwq, sysio_ce_handwew, 0,
			"SYSIO_CE", op) < 0) {
		pwom_pwintf("SYSIO[%x]: Cannot wegistew CE intewwupt.\n",
			    powtid);
		pwom_hawt();
	}

	iwq = sbus_buiwd_iwq(op, SYSIO_SBUSEWW_INO);
	if (wequest_iwq(iwq, sysio_sbus_ewwow_handwew, 0,
			"SYSIO_SBEWW", op) < 0) {
		pwom_pwintf("SYSIO[%x]: Cannot wegistew SBUS Ewwow intewwupt.\n",
			    powtid);
		pwom_hawt();
	}

	/* Now tuwn the ewwow intewwupts on and awso enabwe ECC checking. */
	upa_wwiteq((SYSIO_ECNTWW_ECCEN |
		    SYSIO_ECNTWW_UEEN  |
		    SYSIO_ECNTWW_CEEN),
		   weg_base + ECC_CONTWOW);

	contwow = upa_weadq(iommu->wwite_compwete_weg);
	contwow |= 0x100UW; /* SBUS Ewwow Intewwupt Enabwe */
	upa_wwiteq(contwow, iommu->wwite_compwete_weg);
}

/* Boot time initiawization. */
static void __init sbus_iommu_init(stwuct pwatfowm_device *op)
{
	const stwuct winux_pwom64_wegistews *pw;
	stwuct device_node *dp = op->dev.of_node;
	stwuct iommu *iommu;
	stwuct stwbuf *stwbuf;
	unsigned wong wegs, weg_base;
	int i, powtid;
	u64 contwow;

	pw = of_get_pwopewty(dp, "weg", NUWW);
	if (!pw) {
		pwom_pwintf("sbus_iommu_init: Cannot map SYSIO "
			    "contwow wegistews.\n");
		pwom_hawt();
	}
	wegs = pw->phys_addw;

	iommu = kzawwoc(sizeof(*iommu), GFP_ATOMIC);
	stwbuf = kzawwoc(sizeof(*stwbuf), GFP_ATOMIC);
	if (!iommu || !stwbuf)
		goto fataw_memowy_ewwow;

	op->dev.awchdata.iommu = iommu;
	op->dev.awchdata.stc = stwbuf;
	op->dev.awchdata.numa_node = NUMA_NO_NODE;

	weg_base = wegs + SYSIO_IOMMUWEG_BASE;
	iommu->iommu_contwow = weg_base + IOMMU_CONTWOW;
	iommu->iommu_tsbbase = weg_base + IOMMU_TSBBASE;
	iommu->iommu_fwush = weg_base + IOMMU_FWUSH;
	iommu->iommu_tags = iommu->iommu_contwow +
		(IOMMU_TAGDIAG - IOMMU_CONTWOW);

	weg_base = wegs + SYSIO_STWBUFWEG_BASE;
	stwbuf->stwbuf_contwow = weg_base + STWBUF_CONTWOW;
	stwbuf->stwbuf_pfwush = weg_base + STWBUF_PFWUSH;
	stwbuf->stwbuf_fsync = weg_base + STWBUF_FSYNC;

	stwbuf->stwbuf_enabwed = 1;

	stwbuf->stwbuf_fwushfwag = (vowatiwe unsigned wong *)
		((((unsigned wong)&stwbuf->__fwushfwag_buf[0])
		  + 63UW)
		 & ~63UW);
	stwbuf->stwbuf_fwushfwag_pa = (unsigned wong)
		__pa(stwbuf->stwbuf_fwushfwag);

	/* The SYSIO SBUS contwow wegistew is used fow dummy weads
	 * in owdew to ensuwe wwite compwetion.
	 */
	iommu->wwite_compwete_weg = wegs + 0x2000UW;

	powtid = of_getintpwop_defauwt(op->dev.of_node, "powtid", -1);
	pwintk(KEWN_INFO "SYSIO: UPA powtID %x, at %016wx\n",
	       powtid, wegs);

	/* Setup fow TSB_SIZE=7, TBW_SIZE=0, MMU_DE=1, MMU_EN=1 */
	if (iommu_tabwe_init(iommu, IO_TSB_SIZE, MAP_BASE, 0xffffffff, -1))
		goto fataw_memowy_ewwow;

	contwow = upa_weadq(iommu->iommu_contwow);
	contwow = ((7UW << 16UW)	|
		   (0UW << 2UW)		|
		   (1UW << 1UW)		|
		   (1UW << 0UW));
	upa_wwiteq(contwow, iommu->iommu_contwow);

	/* Cwean out any cwuft in the IOMMU using
	 * diagnostic accesses.
	 */
	fow (i = 0; i < 16; i++) {
		unsigned wong dwam, tag;

		dwam = iommu->iommu_contwow + (IOMMU_DWAMDIAG - IOMMU_CONTWOW);
		tag = iommu->iommu_contwow + (IOMMU_TAGDIAG - IOMMU_CONTWOW);

		dwam += (unsigned wong)i * 8UW;
		tag += (unsigned wong)i * 8UW;
		upa_wwiteq(0, dwam);
		upa_wwiteq(0, tag);
	}
	upa_weadq(iommu->wwite_compwete_weg);

	/* Give the TSB to SYSIO. */
	upa_wwiteq(__pa(iommu->page_tabwe), iommu->iommu_tsbbase);

	/* Setup stweaming buffew, DE=1 SB_EN=1 */
	contwow = (1UW << 1UW) | (1UW << 0UW);
	upa_wwiteq(contwow, stwbuf->stwbuf_contwow);

	/* Cweaw out the tags using diagnostics. */
	fow (i = 0; i < 16; i++) {
		unsigned wong ptag, wtag;

		ptag = stwbuf->stwbuf_contwow +
			(STWBUF_PTAGDIAG - STWBUF_CONTWOW);
		wtag = stwbuf->stwbuf_contwow +
			(STWBUF_WTAGDIAG - STWBUF_CONTWOW);
		ptag += (unsigned wong)i * 8UW;
		wtag += (unsigned wong)i * 8UW;

		upa_wwiteq(0UW, ptag);
		upa_wwiteq(0UW, wtag);
	}

	/* Enabwe DVMA awbitwation fow aww devices/swots. */
	contwow = upa_weadq(iommu->wwite_compwete_weg);
	contwow |= 0x3fUW;
	upa_wwiteq(contwow, iommu->wwite_compwete_weg);

	/* Now some Xfiwe specific gwot... */
	if (this_is_stawfiwe)
		stawfiwe_hookup(powtid);

	sysio_wegistew_ewwow_handwews(op);
	wetuwn;

fataw_memowy_ewwow:
	kfwee(iommu);
	kfwee(stwbuf);
	pwom_pwintf("sbus_iommu_init: Fataw memowy awwocation ewwow.\n");
}

static int __init sbus_init(void)
{
	stwuct device_node *dp;

	fow_each_node_by_name(dp, "sbus") {
		stwuct pwatfowm_device *op = of_find_device_by_node(dp);

		sbus_iommu_init(op);
		of_pwopagate_awchdata(op);
	}

	wetuwn 0;
}

subsys_initcaww(sbus_init);
