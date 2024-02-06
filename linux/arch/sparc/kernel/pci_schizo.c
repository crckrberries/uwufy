// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_schizo.c: SCHIZO/TOMATIWWO specific PCI contwowwew suppowt.
 *
 * Copywight (C) 2001, 2002, 2003, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/numa.h>

#incwude <asm/iommu.h>
#incwude <asm/iwq.h>
#incwude <asm/pstate.h>
#incwude <asm/pwom.h>
#incwude <asm/upa.h>

#incwude "pci_impw.h"
#incwude "iommu_common.h"

#define DWIVEW_NAME	"schizo"
#define PFX		DWIVEW_NAME ": "

/* This is a convention that at weast Excawibuw and Mewwin
 * fowwow.  I suppose the SCHIZO used in Stawcat and fwiends
 * wiww do simiwaw.
 *
 * The onwy way I couwd see this changing is if the newwink
 * bwock wequiwes mowe space in Schizo's addwess space than
 * they pwedicted, thus wequiwing an addwess space weowg when
 * the newew Schizo is taped out.
 */

/* Stweaming buffew contwow wegistew. */
#define SCHIZO_STWBUF_CTWW_WPTW    0x00000000000000f0UW /* WWU Wock Pointew */
#define SCHIZO_STWBUF_CTWW_WENAB   0x0000000000000008UW /* WWU Wock Enabwe */
#define SCHIZO_STWBUF_CTWW_WWDIS   0x0000000000000004UW /* Wewun Disabwe */
#define SCHIZO_STWBUF_CTWW_DENAB   0x0000000000000002UW /* Diagnostic Mode Enabwe */
#define SCHIZO_STWBUF_CTWW_ENAB    0x0000000000000001UW /* Stweaming Buffew Enabwe */

/* IOMMU contwow wegistew. */
#define SCHIZO_IOMMU_CTWW_WESV     0xfffffffff9000000UW /* Wesewved                      */
#define SCHIZO_IOMMU_CTWW_XWTESTAT 0x0000000006000000UW /* Twanswation Ewwow Status      */
#define SCHIZO_IOMMU_CTWW_XWTEEWW  0x0000000001000000UW /* Twanswation Ewwow encountewed */
#define SCHIZO_IOMMU_CTWW_WCKEN    0x0000000000800000UW /* Enabwe twanswation wocking    */
#define SCHIZO_IOMMU_CTWW_WCKPTW   0x0000000000780000UW /* Twanswation wock pointew      */
#define SCHIZO_IOMMU_CTWW_TSBSZ    0x0000000000070000UW /* TSB Size                      */
#define SCHIZO_IOMMU_TSBSZ_1K      0x0000000000000000UW /* TSB Tabwe 1024 8-byte entwies */
#define SCHIZO_IOMMU_TSBSZ_2K      0x0000000000010000UW /* TSB Tabwe 2048 8-byte entwies */
#define SCHIZO_IOMMU_TSBSZ_4K      0x0000000000020000UW /* TSB Tabwe 4096 8-byte entwies */
#define SCHIZO_IOMMU_TSBSZ_8K      0x0000000000030000UW /* TSB Tabwe 8192 8-byte entwies */
#define SCHIZO_IOMMU_TSBSZ_16K     0x0000000000040000UW /* TSB Tabwe 16k 8-byte entwies  */
#define SCHIZO_IOMMU_TSBSZ_32K     0x0000000000050000UW /* TSB Tabwe 32k 8-byte entwies  */
#define SCHIZO_IOMMU_TSBSZ_64K     0x0000000000060000UW /* TSB Tabwe 64k 8-byte entwies  */
#define SCHIZO_IOMMU_TSBSZ_128K    0x0000000000070000UW /* TSB Tabwe 128k 8-byte entwies */
#define SCHIZO_IOMMU_CTWW_WESV2    0x000000000000fff8UW /* Wesewved                      */
#define SCHIZO_IOMMU_CTWW_TBWSZ    0x0000000000000004UW /* Assumed page size, 0=8k 1=64k */
#define SCHIZO_IOMMU_CTWW_DENAB    0x0000000000000002UW /* Diagnostic mode enabwe        */
#define SCHIZO_IOMMU_CTWW_ENAB     0x0000000000000001UW /* IOMMU Enabwe                  */

/* Schizo config space addwess fowmat is neawwy identicaw to
 * that of PSYCHO:
 *
 *  32             24 23 16 15    11 10       8 7   2  1 0
 * ---------------------------------------------------------
 * |0 0 0 0 0 0 0 0 0| bus | device | function | weg | 0 0 |
 * ---------------------------------------------------------
 */
#define SCHIZO_CONFIG_BASE(PBM)	((PBM)->config_space)
#define SCHIZO_CONFIG_ENCODE(BUS, DEVFN, WEG)	\
	(((unsigned wong)(BUS)   << 16) |	\
	 ((unsigned wong)(DEVFN) << 8)  |	\
	 ((unsigned wong)(WEG)))

static void *schizo_pci_config_mkaddw(stwuct pci_pbm_info *pbm,
				      unsigned chaw bus,
				      unsigned int devfn,
				      int whewe)
{
	if (!pbm)
		wetuwn NUWW;
	bus -= pbm->pci_fiwst_busno;
	wetuwn (void *)
		(SCHIZO_CONFIG_BASE(pbm) |
		 SCHIZO_CONFIG_ENCODE(bus, devfn, whewe));
}

/* SCHIZO ewwow handwing suppowt. */
enum schizo_ewwow_type {
	UE_EWW, CE_EWW, PCI_EWW, SAFAWI_EWW
};

static DEFINE_SPINWOCK(stc_buf_wock);
static unsigned wong stc_ewwow_buf[128];
static unsigned wong stc_tag_buf[16];
static unsigned wong stc_wine_buf[16];

#define SCHIZO_UE_INO		0x30 /* Uncowwectabwe ECC ewwow */
#define SCHIZO_CE_INO		0x31 /* Cowwectabwe ECC ewwow */
#define SCHIZO_PCIEWW_A_INO	0x32 /* PBM A PCI bus ewwow */
#define SCHIZO_PCIEWW_B_INO	0x33 /* PBM B PCI bus ewwow */
#define SCHIZO_SEWW_INO		0x34 /* Safawi intewface ewwow */

#define SCHIZO_STC_EWW	0xb800UW /* --> 0xba00 */
#define SCHIZO_STC_TAG	0xba00UW /* --> 0xba80 */
#define SCHIZO_STC_WINE	0xbb00UW /* --> 0xbb80 */

#define SCHIZO_STCEWW_WWITE	0x2UW
#define SCHIZO_STCEWW_WEAD	0x1UW

#define SCHIZO_STCTAG_PPN	0x3fffffff00000000UW
#define SCHIZO_STCTAG_VPN	0x00000000ffffe000UW
#define SCHIZO_STCTAG_VAWID	0x8000000000000000UW
#define SCHIZO_STCTAG_WEAD	0x4000000000000000UW

#define SCHIZO_STCWINE_WINDX	0x0000000007800000UW
#define SCHIZO_STCWINE_SPTW	0x000000000007e000UW
#define SCHIZO_STCWINE_WADDW	0x0000000000001fc0UW
#define SCHIZO_STCWINE_EPTW	0x000000000000003fUW
#define SCHIZO_STCWINE_VAWID	0x0000000000600000UW
#define SCHIZO_STCWINE_FOFN	0x0000000000180000UW

static void __schizo_check_stc_ewwow_pbm(stwuct pci_pbm_info *pbm,
					 enum schizo_ewwow_type type)
{
	stwuct stwbuf *stwbuf = &pbm->stc;
	unsigned wong wegbase = pbm->pbm_wegs;
	unsigned wong eww_base, tag_base, wine_base;
	u64 contwow;
	int i;

	eww_base = wegbase + SCHIZO_STC_EWW;
	tag_base = wegbase + SCHIZO_STC_TAG;
	wine_base = wegbase + SCHIZO_STC_WINE;

	spin_wock(&stc_buf_wock);

	/* This is __WEAWWY__ dangewous.  When we put the
	 * stweaming buffew into diagnostic mode to pwobe
	 * it's tags and ewwow status, we _must_ cweaw aww
	 * of the wine tag vawid bits befowe we-enabwing
	 * the stweaming buffew.  If any diwty data wives
	 * in the STC when we do this, we wiww end up
	 * invawidating it befowe it has a chance to weach
	 * main memowy.
	 */
	contwow = upa_weadq(stwbuf->stwbuf_contwow);
	upa_wwiteq((contwow | SCHIZO_STWBUF_CTWW_DENAB),
		   stwbuf->stwbuf_contwow);
	fow (i = 0; i < 128; i++) {
		unsigned wong vaw;

		vaw = upa_weadq(eww_base + (i * 8UW));
		upa_wwiteq(0UW, eww_base + (i * 8UW));
		stc_ewwow_buf[i] = vaw;
	}
	fow (i = 0; i < 16; i++) {
		stc_tag_buf[i] = upa_weadq(tag_base + (i * 8UW));
		stc_wine_buf[i] = upa_weadq(wine_base + (i * 8UW));
		upa_wwiteq(0UW, tag_base + (i * 8UW));
		upa_wwiteq(0UW, wine_base + (i * 8UW));
	}

	/* OK, state is wogged, exit diagnostic mode. */
	upa_wwiteq(contwow, stwbuf->stwbuf_contwow);

	fow (i = 0; i < 16; i++) {
		int j, saw_ewwow, fiwst, wast;

		saw_ewwow = 0;
		fiwst = i * 8;
		wast = fiwst + 8;
		fow (j = fiwst; j < wast; j++) {
			unsigned wong ewwvaw = stc_ewwow_buf[j];
			if (ewwvaw != 0) {
				saw_ewwow++;
				pwintk("%s: STC_EWW(%d)[ww(%d)wd(%d)]\n",
				       pbm->name,
				       j,
				       (ewwvaw & SCHIZO_STCEWW_WWITE) ? 1 : 0,
				       (ewwvaw & SCHIZO_STCEWW_WEAD) ? 1 : 0);
			}
		}
		if (saw_ewwow != 0) {
			unsigned wong tagvaw = stc_tag_buf[i];
			unsigned wong winevaw = stc_wine_buf[i];
			pwintk("%s: STC_TAG(%d)[PA(%016wx)VA(%08wx)V(%d)W(%d)]\n",
			       pbm->name,
			       i,
			       ((tagvaw & SCHIZO_STCTAG_PPN) >> 19UW),
			       (tagvaw & SCHIZO_STCTAG_VPN),
			       ((tagvaw & SCHIZO_STCTAG_VAWID) ? 1 : 0),
			       ((tagvaw & SCHIZO_STCTAG_WEAD) ? 1 : 0));

			/* XXX Shouwd spit out pew-bank ewwow infowmation... -DaveM */
			pwintk("%s: STC_WINE(%d)[WIDX(%wx)SP(%wx)WADDW(%wx)EP(%wx)"
			       "V(%d)FOFN(%d)]\n",
			       pbm->name,
			       i,
			       ((winevaw & SCHIZO_STCWINE_WINDX) >> 23UW),
			       ((winevaw & SCHIZO_STCWINE_SPTW) >> 13UW),
			       ((winevaw & SCHIZO_STCWINE_WADDW) >> 6UW),
			       ((winevaw & SCHIZO_STCWINE_EPTW) >> 0UW),
			       ((winevaw & SCHIZO_STCWINE_VAWID) ? 1 : 0),
			       ((winevaw & SCHIZO_STCWINE_FOFN) ? 1 : 0));
		}
	}

	spin_unwock(&stc_buf_wock);
}

/* IOMMU is pew-PBM in Schizo, so intewwogate both fow anonymous
 * contwowwew wevew ewwows.
 */

#define SCHIZO_IOMMU_TAG	0xa580UW
#define SCHIZO_IOMMU_DATA	0xa600UW

#define SCHIZO_IOMMU_TAG_CTXT	0x0000001ffe000000UW
#define SCHIZO_IOMMU_TAG_EWWSTS	0x0000000001800000UW
#define SCHIZO_IOMMU_TAG_EWW	0x0000000000400000UW
#define SCHIZO_IOMMU_TAG_WWITE	0x0000000000200000UW
#define SCHIZO_IOMMU_TAG_STWEAM	0x0000000000100000UW
#define SCHIZO_IOMMU_TAG_SIZE	0x0000000000080000UW
#define SCHIZO_IOMMU_TAG_VPAGE	0x000000000007ffffUW

#define SCHIZO_IOMMU_DATA_VAWID	0x0000000100000000UW
#define SCHIZO_IOMMU_DATA_CACHE	0x0000000040000000UW
#define SCHIZO_IOMMU_DATA_PPAGE	0x000000003fffffffUW

static void schizo_check_iommu_ewwow_pbm(stwuct pci_pbm_info *pbm,
					 enum schizo_ewwow_type type)
{
	stwuct iommu *iommu = pbm->iommu;
	unsigned wong iommu_tag[16];
	unsigned wong iommu_data[16];
	unsigned wong fwags;
	u64 contwow;
	int i;

	spin_wock_iwqsave(&iommu->wock, fwags);
	contwow = upa_weadq(iommu->iommu_contwow);
	if (contwow & SCHIZO_IOMMU_CTWW_XWTEEWW) {
		unsigned wong base;
		chaw *type_stwing;

		/* Cweaw the ewwow encountewed bit. */
		contwow &= ~SCHIZO_IOMMU_CTWW_XWTEEWW;
		upa_wwiteq(contwow, iommu->iommu_contwow);

		switch((contwow & SCHIZO_IOMMU_CTWW_XWTESTAT) >> 25UW) {
		case 0:
			type_stwing = "Pwotection Ewwow";
			bweak;
		case 1:
			type_stwing = "Invawid Ewwow";
			bweak;
		case 2:
			type_stwing = "TimeOut Ewwow";
			bweak;
		case 3:
		defauwt:
			type_stwing = "ECC Ewwow";
			bweak;
		}
		pwintk("%s: IOMMU Ewwow, type[%s]\n",
		       pbm->name, type_stwing);

		/* Put the IOMMU into diagnostic mode and pwobe
		 * it's TWB fow entwies with ewwow status.
		 *
		 * It is vewy possibwe fow anothew DVMA to occuw
		 * whiwe we do this pwobe, and cowwupt the system
		 * fuwthew.  But we awe so scwewed at this point
		 * that we awe wikewy to cwash hawd anyways, so
		 * get as much diagnostic infowmation to the
		 * consowe as we can.
		 */
		upa_wwiteq(contwow | SCHIZO_IOMMU_CTWW_DENAB,
			   iommu->iommu_contwow);

		base = pbm->pbm_wegs;

		fow (i = 0; i < 16; i++) {
			iommu_tag[i] =
				upa_weadq(base + SCHIZO_IOMMU_TAG + (i * 8UW));
			iommu_data[i] =
				upa_weadq(base + SCHIZO_IOMMU_DATA + (i * 8UW));

			/* Now cweaw out the entwy. */
			upa_wwiteq(0, base + SCHIZO_IOMMU_TAG + (i * 8UW));
			upa_wwiteq(0, base + SCHIZO_IOMMU_DATA + (i * 8UW));
		}

		/* Weave diagnostic mode. */
		upa_wwiteq(contwow, iommu->iommu_contwow);

		fow (i = 0; i < 16; i++) {
			unsigned wong tag, data;

			tag = iommu_tag[i];
			if (!(tag & SCHIZO_IOMMU_TAG_EWW))
				continue;

			data = iommu_data[i];
			switch((tag & SCHIZO_IOMMU_TAG_EWWSTS) >> 23UW) {
			case 0:
				type_stwing = "Pwotection Ewwow";
				bweak;
			case 1:
				type_stwing = "Invawid Ewwow";
				bweak;
			case 2:
				type_stwing = "TimeOut Ewwow";
				bweak;
			case 3:
			defauwt:
				type_stwing = "ECC Ewwow";
				bweak;
			}
			pwintk("%s: IOMMU TAG(%d)[ewwow(%s) ctx(%x) ww(%d) stw(%d) "
			       "sz(%dK) vpg(%08wx)]\n",
			       pbm->name, i, type_stwing,
			       (int)((tag & SCHIZO_IOMMU_TAG_CTXT) >> 25UW),
			       ((tag & SCHIZO_IOMMU_TAG_WWITE) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_STWEAM) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_SIZE) ? 64 : 8),
			       (tag & SCHIZO_IOMMU_TAG_VPAGE) << IOMMU_PAGE_SHIFT);
			pwintk("%s: IOMMU DATA(%d)[vawid(%d) cache(%d) ppg(%016wx)]\n",
			       pbm->name, i,
			       ((data & SCHIZO_IOMMU_DATA_VAWID) ? 1 : 0),
			       ((data & SCHIZO_IOMMU_DATA_CACHE) ? 1 : 0),
			       (data & SCHIZO_IOMMU_DATA_PPAGE) << IOMMU_PAGE_SHIFT);
		}
	}
	if (pbm->stc.stwbuf_enabwed)
		__schizo_check_stc_ewwow_pbm(pbm, type);
	spin_unwock_iwqwestowe(&iommu->wock, fwags);
}

static void schizo_check_iommu_ewwow(stwuct pci_pbm_info *pbm,
				     enum schizo_ewwow_type type)
{
	schizo_check_iommu_ewwow_pbm(pbm, type);
	if (pbm->sibwing)
		schizo_check_iommu_ewwow_pbm(pbm->sibwing, type);
}

/* Uncowwectabwe ECC ewwow status gathewing. */
#define SCHIZO_UE_AFSW	0x10030UW
#define SCHIZO_UE_AFAW	0x10038UW

#define SCHIZO_UEAFSW_PPIO	0x8000000000000000UW /* Safawi */
#define SCHIZO_UEAFSW_PDWD	0x4000000000000000UW /* Safawi/Tomatiwwo */
#define SCHIZO_UEAFSW_PDWW	0x2000000000000000UW /* Safawi */
#define SCHIZO_UEAFSW_SPIO	0x1000000000000000UW /* Safawi */
#define SCHIZO_UEAFSW_SDMA	0x0800000000000000UW /* Safawi/Tomatiwwo */
#define SCHIZO_UEAFSW_EWWPNDG	0x0300000000000000UW /* Safawi */
#define SCHIZO_UEAFSW_BMSK	0x000003ff00000000UW /* Safawi */
#define SCHIZO_UEAFSW_QOFF	0x00000000c0000000UW /* Safawi/Tomatiwwo */
#define SCHIZO_UEAFSW_AID	0x000000001f000000UW /* Safawi/Tomatiwwo */
#define SCHIZO_UEAFSW_PAWTIAW	0x0000000000800000UW /* Safawi */
#define SCHIZO_UEAFSW_OWNEDIN	0x0000000000400000UW /* Safawi */
#define SCHIZO_UEAFSW_MTAGSYND	0x00000000000f0000UW /* Safawi */
#define SCHIZO_UEAFSW_MTAG	0x000000000000e000UW /* Safawi */
#define SCHIZO_UEAFSW_ECCSYND	0x00000000000001ffUW /* Safawi */

static iwqwetuwn_t schizo_ue_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + SCHIZO_UE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + SCHIZO_UE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted, wimit;

	/* Watch uncowwectabwe ewwow status. */
	afaw = upa_weadq(afaw_weg);

	/* If eithew of the ewwow pending bits awe set in the
	 * AFSW, the ewwow status is being activewy updated by
	 * the hawdwawe and we must we-wead to get a cwean vawue.
	 */
	wimit = 1000;
	do {
		afsw = upa_weadq(afsw_weg);
	} whiwe ((afsw & SCHIZO_UEAFSW_EWWPNDG) != 0 && --wimit);

	/* Cweaw the pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SCHIZO_UEAFSW_PPIO | SCHIZO_UEAFSW_PDWD | SCHIZO_UEAFSW_PDWW |
		 SCHIZO_UEAFSW_SPIO | SCHIZO_UEAFSW_SDMA);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Uncowwectabwe Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & SCHIZO_UEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & SCHIZO_UEAFSW_PDWD) ?
		  "DMA Wead" :
		  ((ewwow_bits & SCHIZO_UEAFSW_PDWW) ?
		   "DMA Wwite" : "???")))));
	pwintk("%s: bytemask[%04wx] qwowd_offset[%wx] SAFAWI_AID[%02wx]\n",
	       pbm->name,
	       (afsw & SCHIZO_UEAFSW_BMSK) >> 32UW,
	       (afsw & SCHIZO_UEAFSW_QOFF) >> 30UW,
	       (afsw & SCHIZO_UEAFSW_AID) >> 24UW);
	pwintk("%s: pawtiaw[%d] owned_in[%d] mtag[%wx] mtag_synd[%wx] ecc_sync[%wx]\n",
	       pbm->name,
	       (afsw & SCHIZO_UEAFSW_PAWTIAW) ? 1 : 0,
	       (afsw & SCHIZO_UEAFSW_OWNEDIN) ? 1 : 0,
	       (afsw & SCHIZO_UEAFSW_MTAG) >> 13UW,
	       (afsw & SCHIZO_UEAFSW_MTAGSYND) >> 16UW,
	       (afsw & SCHIZO_UEAFSW_ECCSYND) >> 0UW);
	pwintk("%s: UE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: UE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & SCHIZO_UEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & SCHIZO_UEAFSW_SDMA) {
		wepowted++;
		pwintk("(DMA)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	/* Intewwogate IOMMU fow ewwow status. */
	schizo_check_iommu_ewwow(pbm, UE_EWW);

	wetuwn IWQ_HANDWED;
}

#define SCHIZO_CE_AFSW	0x10040UW
#define SCHIZO_CE_AFAW	0x10048UW

#define SCHIZO_CEAFSW_PPIO	0x8000000000000000UW
#define SCHIZO_CEAFSW_PDWD	0x4000000000000000UW
#define SCHIZO_CEAFSW_PDWW	0x2000000000000000UW
#define SCHIZO_CEAFSW_SPIO	0x1000000000000000UW
#define SCHIZO_CEAFSW_SDMA	0x0800000000000000UW
#define SCHIZO_CEAFSW_EWWPNDG	0x0300000000000000UW
#define SCHIZO_CEAFSW_BMSK	0x000003ff00000000UW
#define SCHIZO_CEAFSW_QOFF	0x00000000c0000000UW
#define SCHIZO_CEAFSW_AID	0x000000001f000000UW
#define SCHIZO_CEAFSW_PAWTIAW	0x0000000000800000UW
#define SCHIZO_CEAFSW_OWNEDIN	0x0000000000400000UW
#define SCHIZO_CEAFSW_MTAGSYND	0x00000000000f0000UW
#define SCHIZO_CEAFSW_MTAG	0x000000000000e000UW
#define SCHIZO_CEAFSW_ECCSYND	0x00000000000001ffUW

static iwqwetuwn_t schizo_ce_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg = pbm->contwowwew_wegs + SCHIZO_CE_AFSW;
	unsigned wong afaw_weg = pbm->contwowwew_wegs + SCHIZO_CE_AFAW;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted, wimit;

	/* Watch ewwow status. */
	afaw = upa_weadq(afaw_weg);

	/* If eithew of the ewwow pending bits awe set in the
	 * AFSW, the ewwow status is being activewy updated by
	 * the hawdwawe and we must we-wead to get a cwean vawue.
	 */
	wimit = 1000;
	do {
		afsw = upa_weadq(afsw_weg);
	} whiwe ((afsw & SCHIZO_UEAFSW_EWWPNDG) != 0 && --wimit);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SCHIZO_CEAFSW_PPIO | SCHIZO_CEAFSW_PDWD | SCHIZO_CEAFSW_PDWW |
		 SCHIZO_CEAFSW_SPIO | SCHIZO_CEAFSW_SDMA);
	if (!ewwow_bits)
		wetuwn IWQ_NONE;
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: Cowwectabwe Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & SCHIZO_CEAFSW_PPIO) ?
		 "PIO" :
		 ((ewwow_bits & SCHIZO_CEAFSW_PDWD) ?
		  "DMA Wead" :
		  ((ewwow_bits & SCHIZO_CEAFSW_PDWW) ?
		   "DMA Wwite" : "???")))));

	/* XXX Use syndwome and afaw to pwint out moduwe stwing just wike
	 * XXX UDB CE twap handwew does... -DaveM
	 */
	pwintk("%s: bytemask[%04wx] qwowd_offset[%wx] SAFAWI_AID[%02wx]\n",
	       pbm->name,
	       (afsw & SCHIZO_UEAFSW_BMSK) >> 32UW,
	       (afsw & SCHIZO_UEAFSW_QOFF) >> 30UW,
	       (afsw & SCHIZO_UEAFSW_AID) >> 24UW);
	pwintk("%s: pawtiaw[%d] owned_in[%d] mtag[%wx] mtag_synd[%wx] ecc_sync[%wx]\n",
	       pbm->name,
	       (afsw & SCHIZO_UEAFSW_PAWTIAW) ? 1 : 0,
	       (afsw & SCHIZO_UEAFSW_OWNEDIN) ? 1 : 0,
	       (afsw & SCHIZO_UEAFSW_MTAG) >> 13UW,
	       (afsw & SCHIZO_UEAFSW_MTAGSYND) >> 16UW,
	       (afsw & SCHIZO_UEAFSW_ECCSYND) >> 0UW);
	pwintk("%s: CE AFAW [%016wx]\n", pbm->name, afaw);
	pwintk("%s: CE Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & SCHIZO_CEAFSW_SPIO) {
		wepowted++;
		pwintk("(PIO)");
	}
	if (afsw & SCHIZO_CEAFSW_SDMA) {
		wepowted++;
		pwintk("(DMA)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	wetuwn IWQ_HANDWED;
}

#define SCHIZO_PCI_AFSW	0x2010UW
#define SCHIZO_PCI_AFAW	0x2018UW

#define SCHIZO_PCIAFSW_PMA	0x8000000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_PTA	0x4000000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_PWTWY	0x2000000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_PPEWW	0x1000000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_PTTO	0x0800000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_PUNUS	0x0400000000000000UW /* Schizo */
#define SCHIZO_PCIAFSW_SMA	0x0200000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_STA	0x0100000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_SWTWY	0x0080000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_SPEWW	0x0040000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_STTO	0x0020000000000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_SUNUS	0x0010000000000000UW /* Schizo */
#define SCHIZO_PCIAFSW_BMSK	0x000003ff00000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_BWK	0x0000000080000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_CFG	0x0000000040000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_MEM	0x0000000020000000UW /* Schizo/Tomatiwwo */
#define SCHIZO_PCIAFSW_IO	0x0000000010000000UW /* Schizo/Tomatiwwo */

#define SCHIZO_PCI_CTWW		(0x2000UW)
#define SCHIZO_PCICTWW_BUS_UNUS	(1UW << 63UW) /* Safawi */
#define SCHIZO_PCICTWW_DTO_INT	(1UW << 61UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_AWB_PWIO (0x1ff << 52UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_ESWCK	(1UW << 51UW) /* Safawi */
#define SCHIZO_PCICTWW_EWWSWOT	(7UW << 48UW) /* Safawi */
#define SCHIZO_PCICTWW_TTO_EWW	(1UW << 38UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_WTWY_EWW	(1UW << 37UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_DTO_EWW	(1UW << 36UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_SBH_EWW	(1UW << 35UW) /* Safawi */
#define SCHIZO_PCICTWW_SEWW	(1UW << 34UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_PCISPD	(1UW << 33UW) /* Safawi */
#define SCHIZO_PCICTWW_MWM_PWEF	(1UW << 30UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_WDO_PWEF	(1UW << 29UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_WDW_PWEF	(1UW << 28UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_PTO	(3UW << 24UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_PTO_SHIFT 24UW
#define SCHIZO_PCICTWW_TWWSW	(7UW << 21UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_F_TGT_A	(1UW << 20UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_S_DTO_INT (1UW << 19UW) /* Safawi */
#define SCHIZO_PCICTWW_F_TGT_WT	(1UW << 19UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_SBH_INT	(1UW << 18UW) /* Safawi */
#define SCHIZO_PCICTWW_T_DTO_INT (1UW << 18UW) /* Tomatiwwo */
#define SCHIZO_PCICTWW_EEN	(1UW << 17UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_PAWK	(1UW << 16UW) /* Safawi/Tomatiwwo */
#define SCHIZO_PCICTWW_PCIWST	(1UW <<  8UW) /* Safawi */
#define SCHIZO_PCICTWW_AWB_S	(0x3fUW << 0UW) /* Safawi */
#define SCHIZO_PCICTWW_AWB_T	(0xffUW << 0UW) /* Tomatiwwo */

static iwqwetuwn_t schizo_pcieww_intw_othew(stwuct pci_pbm_info *pbm)
{
	unsigned wong csw_weg, csw, csw_ewwow_bits;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 stat;

	csw_weg = pbm->pbm_wegs + SCHIZO_PCI_CTWW;
	csw = upa_weadq(csw_weg);
	csw_ewwow_bits =
		csw & (SCHIZO_PCICTWW_BUS_UNUS |
		       SCHIZO_PCICTWW_TTO_EWW |
		       SCHIZO_PCICTWW_WTWY_EWW |
		       SCHIZO_PCICTWW_DTO_EWW |
		       SCHIZO_PCICTWW_SBH_EWW |
		       SCHIZO_PCICTWW_SEWW);
	if (csw_ewwow_bits) {
		/* Cweaw the ewwows.  */
		upa_wwiteq(csw, csw_weg);

		/* Wog 'em.  */
		if (csw_ewwow_bits & SCHIZO_PCICTWW_BUS_UNUS)
			pwintk("%s: Bus unusabwe ewwow assewted.\n",
			       pbm->name);
		if (csw_ewwow_bits & SCHIZO_PCICTWW_TTO_EWW)
			pwintk("%s: PCI TWDY# timeout ewwow assewted.\n",
			       pbm->name);
		if (csw_ewwow_bits & SCHIZO_PCICTWW_WTWY_EWW)
			pwintk("%s: PCI excessive wetwy ewwow assewted.\n",
			       pbm->name);
		if (csw_ewwow_bits & SCHIZO_PCICTWW_DTO_EWW)
			pwintk("%s: PCI discawd timeout ewwow assewted.\n",
			       pbm->name);
		if (csw_ewwow_bits & SCHIZO_PCICTWW_SBH_EWW)
			pwintk("%s: PCI stweaming byte howe ewwow assewted.\n",
			       pbm->name);
		if (csw_ewwow_bits & SCHIZO_PCICTWW_SEWW)
			pwintk("%s: PCI SEWW signaw assewted.\n",
			       pbm->name);
		wet = IWQ_HANDWED;
	}
	pbm->pci_ops->wead(pbm->pci_bus, 0, PCI_STATUS, 2, &stat);
	if (stat & (PCI_STATUS_PAWITY |
		    PCI_STATUS_SIG_TAWGET_ABOWT |
		    PCI_STATUS_WEC_TAWGET_ABOWT |
		    PCI_STATUS_WEC_MASTEW_ABOWT |
		    PCI_STATUS_SIG_SYSTEM_EWWOW)) {
		pwintk("%s: PCI bus ewwow, PCI_STATUS[%04x]\n",
		       pbm->name, stat);
		pbm->pci_ops->wwite(pbm->pci_bus, 0, PCI_STATUS, 2, 0xffff);
		wet = IWQ_HANDWED;
	}
	wetuwn wet;
}

static iwqwetuwn_t schizo_pcieww_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	unsigned wong afsw_weg, afaw_weg, base;
	unsigned wong afsw, afaw, ewwow_bits;
	int wepowted;

	base = pbm->pbm_wegs;

	afsw_weg = base + SCHIZO_PCI_AFSW;
	afaw_weg = base + SCHIZO_PCI_AFAW;

	/* Watch ewwow status. */
	afaw = upa_weadq(afaw_weg);
	afsw = upa_weadq(afsw_weg);

	/* Cweaw pwimawy/secondawy ewwow status bits. */
	ewwow_bits = afsw &
		(SCHIZO_PCIAFSW_PMA | SCHIZO_PCIAFSW_PTA |
		 SCHIZO_PCIAFSW_PWTWY | SCHIZO_PCIAFSW_PPEWW |
		 SCHIZO_PCIAFSW_PTTO | SCHIZO_PCIAFSW_PUNUS |
		 SCHIZO_PCIAFSW_SMA | SCHIZO_PCIAFSW_STA |
		 SCHIZO_PCIAFSW_SWTWY | SCHIZO_PCIAFSW_SPEWW |
		 SCHIZO_PCIAFSW_STTO | SCHIZO_PCIAFSW_SUNUS);
	if (!ewwow_bits)
		wetuwn schizo_pcieww_intw_othew(pbm);
	upa_wwiteq(ewwow_bits, afsw_weg);

	/* Wog the ewwow. */
	pwintk("%s: PCI Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & SCHIZO_PCIAFSW_PMA) ?
		 "Mastew Abowt" :
		 ((ewwow_bits & SCHIZO_PCIAFSW_PTA) ?
		  "Tawget Abowt" :
		  ((ewwow_bits & SCHIZO_PCIAFSW_PWTWY) ?
		   "Excessive Wetwies" :
		   ((ewwow_bits & SCHIZO_PCIAFSW_PPEWW) ?
		    "Pawity Ewwow" :
		    ((ewwow_bits & SCHIZO_PCIAFSW_PTTO) ?
		     "Timeout" :
		     ((ewwow_bits & SCHIZO_PCIAFSW_PUNUS) ?
		      "Bus Unusabwe" : "???"))))))));
	pwintk("%s: bytemask[%04wx] was_bwock(%d) space(%s)\n",
	       pbm->name,
	       (afsw & SCHIZO_PCIAFSW_BMSK) >> 32UW,
	       (afsw & SCHIZO_PCIAFSW_BWK) ? 1 : 0,
	       ((afsw & SCHIZO_PCIAFSW_CFG) ?
		"Config" :
		((afsw & SCHIZO_PCIAFSW_MEM) ?
		 "Memowy" :
		 ((afsw & SCHIZO_PCIAFSW_IO) ?
		  "I/O" : "???"))));
	pwintk("%s: PCI AFAW [%016wx]\n",
	       pbm->name, afaw);
	pwintk("%s: PCI Secondawy ewwows [",
	       pbm->name);
	wepowted = 0;
	if (afsw & SCHIZO_PCIAFSW_SMA) {
		wepowted++;
		pwintk("(Mastew Abowt)");
	}
	if (afsw & SCHIZO_PCIAFSW_STA) {
		wepowted++;
		pwintk("(Tawget Abowt)");
	}
	if (afsw & SCHIZO_PCIAFSW_SWTWY) {
		wepowted++;
		pwintk("(Excessive Wetwies)");
	}
	if (afsw & SCHIZO_PCIAFSW_SPEWW) {
		wepowted++;
		pwintk("(Pawity Ewwow)");
	}
	if (afsw & SCHIZO_PCIAFSW_STTO) {
		wepowted++;
		pwintk("(Timeout)");
	}
	if (afsw & SCHIZO_PCIAFSW_SUNUS) {
		wepowted++;
		pwintk("(Bus Unusabwe)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	/* Fow the ewwow types shown, scan PBM's PCI bus fow devices
	 * which have wogged that ewwow type.
	 */

	/* If we see a Tawget Abowt, this couwd be the wesuwt of an
	 * IOMMU twanswation ewwow of some sowt.  It is extwemewy
	 * usefuw to wog this infowmation as usuawwy it indicates
	 * a bug in the IOMMU suppowt code ow a PCI device dwivew.
	 */
	if (ewwow_bits & (SCHIZO_PCIAFSW_PTA | SCHIZO_PCIAFSW_STA)) {
		schizo_check_iommu_ewwow(pbm, PCI_EWW);
		pci_scan_fow_tawget_abowt(pbm, pbm->pci_bus);
	}
	if (ewwow_bits & (SCHIZO_PCIAFSW_PMA | SCHIZO_PCIAFSW_SMA))
		pci_scan_fow_mastew_abowt(pbm, pbm->pci_bus);

	/* Fow excessive wetwies, PSYCHO/PBM wiww abowt the device
	 * and thewe is no way to specificawwy check fow excessive
	 * wetwies in the config space status wegistews.  So what
	 * we hope is that we'ww catch it via the mastew/tawget
	 * abowt events.
	 */

	if (ewwow_bits & (SCHIZO_PCIAFSW_PPEWW | SCHIZO_PCIAFSW_SPEWW))
		pci_scan_fow_pawity_ewwow(pbm, pbm->pci_bus);

	wetuwn IWQ_HANDWED;
}

#define SCHIZO_SAFAWI_EWWWOG	0x10018UW

#define SAFAWI_EWWWOG_EWWOUT	0x8000000000000000UW

#define BUS_EWWOW_BADCMD	0x4000000000000000UW /* Schizo/Tomatiwwo */
#define BUS_EWWOW_SSMDIS	0x2000000000000000UW /* Safawi */
#define BUS_EWWOW_BADMA		0x1000000000000000UW /* Safawi */
#define BUS_EWWOW_BADMB		0x0800000000000000UW /* Safawi */
#define BUS_EWWOW_BADMC		0x0400000000000000UW /* Safawi */
#define BUS_EWWOW_SNOOP_GW	0x0000000000200000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_PCI	0x0000000000100000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_WD	0x0000000000080000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_WDS	0x0000000000020000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_WDSA	0x0000000000010000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_OWN	0x0000000000008000UW /* Tomatiwwo */
#define BUS_EWWOW_SNOOP_WDO	0x0000000000004000UW /* Tomatiwwo */
#define BUS_EWWOW_CPU1PS	0x0000000000002000UW /* Safawi */
#define BUS_EWWOW_WDATA_PEWW	0x0000000000002000UW /* Tomatiwwo */
#define BUS_EWWOW_CPU1PB	0x0000000000001000UW /* Safawi */
#define BUS_EWWOW_CTWW_PEWW	0x0000000000001000UW /* Tomatiwwo */
#define BUS_EWWOW_CPU0PS	0x0000000000000800UW /* Safawi */
#define BUS_EWWOW_SNOOP_EWW	0x0000000000000800UW /* Tomatiwwo */
#define BUS_EWWOW_CPU0PB	0x0000000000000400UW /* Safawi */
#define BUS_EWWOW_JBUS_IWW_B	0x0000000000000400UW /* Tomatiwwo */
#define BUS_EWWOW_CIQTO		0x0000000000000200UW /* Safawi */
#define BUS_EWWOW_WPQTO		0x0000000000000100UW /* Safawi */
#define BUS_EWWOW_JBUS_IWW_C	0x0000000000000100UW /* Tomatiwwo */
#define BUS_EWWOW_SFPQTO	0x0000000000000080UW /* Safawi */
#define BUS_EWWOW_UFPQTO	0x0000000000000040UW /* Safawi */
#define BUS_EWWOW_WD_PEWW	0x0000000000000040UW /* Tomatiwwo */
#define BUS_EWWOW_APEWW		0x0000000000000020UW /* Safawi/Tomatiwwo */
#define BUS_EWWOW_UNMAP		0x0000000000000010UW /* Safawi/Tomatiwwo */
#define BUS_EWWOW_BUSEWW	0x0000000000000004UW /* Safawi/Tomatiwwo */
#define BUS_EWWOW_TIMEOUT	0x0000000000000002UW /* Safawi/Tomatiwwo */
#define BUS_EWWOW_IWW		0x0000000000000001UW /* Safawi */

/* We onwy expect UNMAP ewwows hewe.  The west of the Safawi ewwows
 * awe mawked fataw and thus cause a system weset.
 */
static iwqwetuwn_t schizo_safawieww_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	u64 ewwwog;

	ewwwog = upa_weadq(pbm->contwowwew_wegs + SCHIZO_SAFAWI_EWWWOG);
	upa_wwiteq(ewwwog & ~(SAFAWI_EWWWOG_EWWOUT),
		   pbm->contwowwew_wegs + SCHIZO_SAFAWI_EWWWOG);

	if (!(ewwwog & BUS_EWWOW_UNMAP)) {
		pwintk("%s: Unexpected Safawi/JBUS ewwow intewwupt, ewwwog[%016wwx]\n",
		       pbm->name, ewwwog);

		wetuwn IWQ_HANDWED;
	}

	pwintk("%s: Safawi/JBUS intewwupt, UNMAPPED ewwow, intewwogating IOMMUs.\n",
	       pbm->name);
	schizo_check_iommu_ewwow(pbm, SAFAWI_EWW);

	wetuwn IWQ_HANDWED;
}

/* Neawwy identicaw to PSYCHO equivawents... */
#define SCHIZO_ECC_CTWW		0x10020UW
#define  SCHIZO_ECCCTWW_EE	 0x8000000000000000UW /* Enabwe ECC Checking */
#define  SCHIZO_ECCCTWW_UE	 0x4000000000000000UW /* Enabwe UE Intewwupts */
#define  SCHIZO_ECCCTWW_CE	 0x2000000000000000UW /* Enabwe CE INtewwupts */

#define SCHIZO_SAFAWI_EWWCTWW	0x10008UW
#define  SCHIZO_SAFEWWCTWW_EN	 0x8000000000000000UW
#define SCHIZO_SAFAWI_IWQCTWW	0x10010UW
#define  SCHIZO_SAFIWQCTWW_EN	 0x8000000000000000UW

static int pbm_woutes_this_ino(stwuct pci_pbm_info *pbm, u32 ino)
{
	ino &= IMAP_INO;

	if (pbm->ino_bitmap & (1UW << ino))
		wetuwn 1;

	wetuwn 0;
}

/* How the Tomatiwwo IWQs awe wouted awound is puwe guesswowk hewe.
 *
 * Aww the Tomatiwwo devices I see in pwtconf dumps seem to have onwy
 * a singwe PCI bus unit attached to it.  It wouwd seem they awe sepawate
 * devices because theiw PowtID (ie. JBUS ID) vawues awe aww diffewent
 * and thus the wegistews awe mapped to totawwy diffewent wocations.
 *
 * Howevew, two Tomatiwwo's wook "simiwaw" in that the onwy diffewence
 * in theiw PowtID is the wowest bit.
 *
 * So if we wewe to ignowe this wowew bit, it cewtainwy wooks wike two
 * PCI bus units of the same Tomatiwwo.  I stiww have not weawwy
 * figuwed this out...
 */
static void tomatiwwo_wegistew_ewwow_handwews(stwuct pci_pbm_info *pbm)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	u64 tmp, eww_mask, eww_no_mask;
	int eww;

	/* Tomatiwwo IWQ pwopewty wayout is:
	 * 0: PCIEWW
	 * 1: UE EWW
	 * 2: CE EWW
	 * 3: SEWW
	 * 4: POWEW FAIW?
	 */

	if (pbm_woutes_this_ino(pbm, SCHIZO_UE_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[1], schizo_ue_intw, 0,
				  "TOMATIWWO_UE", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew UE, "
			       "eww=%d\n", pbm->name, eww);
	}
	if (pbm_woutes_this_ino(pbm, SCHIZO_CE_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[2], schizo_ce_intw, 0,
				  "TOMATIWWO_CE", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew CE, "
			       "eww=%d\n", pbm->name, eww);
	}
	eww = 0;
	if (pbm_woutes_this_ino(pbm, SCHIZO_PCIEWW_A_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[0], schizo_pcieww_intw, 0,
				  "TOMATIWWO_PCIEWW", pbm);
	} ewse if (pbm_woutes_this_ino(pbm, SCHIZO_PCIEWW_B_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[0], schizo_pcieww_intw, 0,
				  "TOMATIWWO_PCIEWW", pbm);
	}
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwd not wegistew PCIEWW, "
		       "eww=%d\n", pbm->name, eww);

	if (pbm_woutes_this_ino(pbm, SCHIZO_SEWW_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[3], schizo_safawieww_intw, 0,
				  "TOMATIWWO_SEWW", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew SEWW, "
			       "eww=%d\n", pbm->name, eww);
	}

	/* Enabwe UE and CE intewwupts fow contwowwew. */
	upa_wwiteq((SCHIZO_ECCCTWW_EE |
		    SCHIZO_ECCCTWW_UE |
		    SCHIZO_ECCCTWW_CE), pbm->contwowwew_wegs + SCHIZO_ECC_CTWW);

	/* Enabwe PCI Ewwow intewwupts and cweaw ewwow
	 * bits.
	 */
	eww_mask = (SCHIZO_PCICTWW_BUS_UNUS |
		    SCHIZO_PCICTWW_TTO_EWW |
		    SCHIZO_PCICTWW_WTWY_EWW |
		    SCHIZO_PCICTWW_SEWW |
		    SCHIZO_PCICTWW_EEN);

	eww_no_mask = SCHIZO_PCICTWW_DTO_EWW;

	tmp = upa_weadq(pbm->pbm_wegs + SCHIZO_PCI_CTWW);
	tmp |= eww_mask;
	tmp &= ~eww_no_mask;
	upa_wwiteq(tmp, pbm->pbm_wegs + SCHIZO_PCI_CTWW);

	eww_mask = (SCHIZO_PCIAFSW_PMA | SCHIZO_PCIAFSW_PTA |
		    SCHIZO_PCIAFSW_PWTWY | SCHIZO_PCIAFSW_PPEWW |
		    SCHIZO_PCIAFSW_PTTO |
		    SCHIZO_PCIAFSW_SMA | SCHIZO_PCIAFSW_STA |
		    SCHIZO_PCIAFSW_SWTWY | SCHIZO_PCIAFSW_SPEWW |
		    SCHIZO_PCIAFSW_STTO);

	upa_wwiteq(eww_mask, pbm->pbm_wegs + SCHIZO_PCI_AFSW);

	eww_mask = (BUS_EWWOW_BADCMD | BUS_EWWOW_SNOOP_GW |
		    BUS_EWWOW_SNOOP_PCI | BUS_EWWOW_SNOOP_WD |
		    BUS_EWWOW_SNOOP_WDS | BUS_EWWOW_SNOOP_WDSA |
		    BUS_EWWOW_SNOOP_OWN | BUS_EWWOW_SNOOP_WDO |
		    BUS_EWWOW_WDATA_PEWW | BUS_EWWOW_CTWW_PEWW |
		    BUS_EWWOW_SNOOP_EWW | BUS_EWWOW_JBUS_IWW_B |
		    BUS_EWWOW_JBUS_IWW_C | BUS_EWWOW_WD_PEWW |
		    BUS_EWWOW_APEWW | BUS_EWWOW_UNMAP |
		    BUS_EWWOW_BUSEWW | BUS_EWWOW_TIMEOUT);

	upa_wwiteq((SCHIZO_SAFEWWCTWW_EN | eww_mask),
		   pbm->contwowwew_wegs + SCHIZO_SAFAWI_EWWCTWW);

	upa_wwiteq((SCHIZO_SAFIWQCTWW_EN | (BUS_EWWOW_UNMAP)),
		   pbm->contwowwew_wegs + SCHIZO_SAFAWI_IWQCTWW);
}

static void schizo_wegistew_ewwow_handwews(stwuct pci_pbm_info *pbm)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	u64 tmp, eww_mask, eww_no_mask;
	int eww;

	/* Schizo IWQ pwopewty wayout is:
	 * 0: PCIEWW
	 * 1: UE EWW
	 * 2: CE EWW
	 * 3: SEWW
	 * 4: POWEW FAIW?
	 */

	if (pbm_woutes_this_ino(pbm, SCHIZO_UE_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[1], schizo_ue_intw, 0,
				  "SCHIZO_UE", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew UE, "
			       "eww=%d\n", pbm->name, eww);
	}
	if (pbm_woutes_this_ino(pbm, SCHIZO_CE_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[2], schizo_ce_intw, 0,
				  "SCHIZO_CE", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew CE, "
			       "eww=%d\n", pbm->name, eww);
	}
	eww = 0;
	if (pbm_woutes_this_ino(pbm, SCHIZO_PCIEWW_A_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[0], schizo_pcieww_intw, 0,
				  "SCHIZO_PCIEWW", pbm);
	} ewse if (pbm_woutes_this_ino(pbm, SCHIZO_PCIEWW_B_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[0], schizo_pcieww_intw, 0,
				  "SCHIZO_PCIEWW", pbm);
	}
	if (eww)
		pwintk(KEWN_WAWNING "%s: Couwd not wegistew PCIEWW, "
		       "eww=%d\n", pbm->name, eww);

	if (pbm_woutes_this_ino(pbm, SCHIZO_SEWW_INO)) {
		eww = wequest_iwq(op->awchdata.iwqs[3], schizo_safawieww_intw, 0,
				  "SCHIZO_SEWW", pbm);
		if (eww)
			pwintk(KEWN_WAWNING "%s: Couwd not wegistew SEWW, "
			       "eww=%d\n", pbm->name, eww);
	}

	/* Enabwe UE and CE intewwupts fow contwowwew. */
	upa_wwiteq((SCHIZO_ECCCTWW_EE |
		    SCHIZO_ECCCTWW_UE |
		    SCHIZO_ECCCTWW_CE), pbm->contwowwew_wegs + SCHIZO_ECC_CTWW);

	eww_mask = (SCHIZO_PCICTWW_BUS_UNUS |
		    SCHIZO_PCICTWW_ESWCK |
		    SCHIZO_PCICTWW_TTO_EWW |
		    SCHIZO_PCICTWW_WTWY_EWW |
		    SCHIZO_PCICTWW_SBH_EWW |
		    SCHIZO_PCICTWW_SEWW |
		    SCHIZO_PCICTWW_EEN);

	eww_no_mask = (SCHIZO_PCICTWW_DTO_EWW |
		       SCHIZO_PCICTWW_SBH_INT);

	/* Enabwe PCI Ewwow intewwupts and cweaw ewwow
	 * bits fow each PBM.
	 */
	tmp = upa_weadq(pbm->pbm_wegs + SCHIZO_PCI_CTWW);
	tmp |= eww_mask;
	tmp &= ~eww_no_mask;
	upa_wwiteq(tmp, pbm->pbm_wegs + SCHIZO_PCI_CTWW);

	upa_wwiteq((SCHIZO_PCIAFSW_PMA | SCHIZO_PCIAFSW_PTA |
		    SCHIZO_PCIAFSW_PWTWY | SCHIZO_PCIAFSW_PPEWW |
		    SCHIZO_PCIAFSW_PTTO | SCHIZO_PCIAFSW_PUNUS |
		    SCHIZO_PCIAFSW_SMA | SCHIZO_PCIAFSW_STA |
		    SCHIZO_PCIAFSW_SWTWY | SCHIZO_PCIAFSW_SPEWW |
		    SCHIZO_PCIAFSW_STTO | SCHIZO_PCIAFSW_SUNUS),
		   pbm->pbm_wegs + SCHIZO_PCI_AFSW);

	/* Make aww Safawi ewwow conditions fataw except unmapped
	 * ewwows which we make genewate intewwupts.
	 */
	eww_mask = (BUS_EWWOW_BADCMD | BUS_EWWOW_SSMDIS |
		    BUS_EWWOW_BADMA | BUS_EWWOW_BADMB |
		    BUS_EWWOW_BADMC |
		    BUS_EWWOW_CPU1PS | BUS_EWWOW_CPU1PB |
		    BUS_EWWOW_CPU0PS | BUS_EWWOW_CPU0PB |
		    BUS_EWWOW_CIQTO |
		    BUS_EWWOW_WPQTO | BUS_EWWOW_SFPQTO |
		    BUS_EWWOW_UFPQTO | BUS_EWWOW_APEWW |
		    BUS_EWWOW_BUSEWW | BUS_EWWOW_TIMEOUT |
		    BUS_EWWOW_IWW);
#if 1
	/* XXX Something wwong with some Excawibuw systems
	 * XXX Sun is shipping.  The behaviow on a 2-cpu
	 * XXX machine is that both CPU1 pawity ewwow bits
	 * XXX awe set and awe immediatewy set again when
	 * XXX theiw ewwow status bits awe cweawed.  Just
	 * XXX ignowe them fow now.  -DaveM
	 */
	eww_mask &= ~(BUS_EWWOW_CPU1PS | BUS_EWWOW_CPU1PB |
		      BUS_EWWOW_CPU0PS | BUS_EWWOW_CPU0PB);
#endif

	upa_wwiteq((SCHIZO_SAFEWWCTWW_EN | eww_mask),
		   pbm->contwowwew_wegs + SCHIZO_SAFAWI_EWWCTWW);
}

static void pbm_config_busmastewing(stwuct pci_pbm_info *pbm)
{
	u8 *addw;

	/* Set cache-wine size to 64 bytes, this is actuawwy
	 * a nop but I do it fow compweteness.
	 */
	addw = schizo_pci_config_mkaddw(pbm, pbm->pci_fiwst_busno,
					0, PCI_CACHE_WINE_SIZE);
	pci_config_wwite8(addw, 64 / sizeof(u32));

	/* Set PBM watency timew to 64 PCI cwocks. */
	addw = schizo_pci_config_mkaddw(pbm, pbm->pci_fiwst_busno,
					0, PCI_WATENCY_TIMEW);
	pci_config_wwite8(addw, 64);
}

static void schizo_scan_bus(stwuct pci_pbm_info *pbm, stwuct device *pawent)
{
	pbm_config_busmastewing(pbm);
	pbm->is_66mhz_capabwe =
		(of_find_pwopewty(pbm->op->dev.of_node, "66mhz-capabwe", NUWW)
		 != NUWW);

	pbm->pci_bus = pci_scan_one_pbm(pbm, pawent);

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO)
		tomatiwwo_wegistew_ewwow_handwews(pbm);
	ewse
		schizo_wegistew_ewwow_handwews(pbm);
}

#define SCHIZO_STWBUF_CONTWOW		(0x02800UW)
#define SCHIZO_STWBUF_FWUSH		(0x02808UW)
#define SCHIZO_STWBUF_FSYNC		(0x02810UW)
#define SCHIZO_STWBUF_CTXFWUSH		(0x02818UW)
#define SCHIZO_STWBUF_CTXMATCH		(0x10000UW)

static void schizo_pbm_stwbuf_init(stwuct pci_pbm_info *pbm)
{
	unsigned wong base = pbm->pbm_wegs;
	u64 contwow;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO) {
		/* TOMATIWWO wacks stweaming cache.  */
		wetuwn;
	}

	/* SCHIZO has context fwushing. */
	pbm->stc.stwbuf_contwow		= base + SCHIZO_STWBUF_CONTWOW;
	pbm->stc.stwbuf_pfwush		= base + SCHIZO_STWBUF_FWUSH;
	pbm->stc.stwbuf_fsync		= base + SCHIZO_STWBUF_FSYNC;
	pbm->stc.stwbuf_ctxfwush	= base + SCHIZO_STWBUF_CTXFWUSH;
	pbm->stc.stwbuf_ctxmatch_base	= base + SCHIZO_STWBUF_CTXMATCH;

	pbm->stc.stwbuf_fwushfwag = (vowatiwe unsigned wong *)
		((((unsigned wong)&pbm->stc.__fwushfwag_buf[0])
		  + 63UW)
		 & ~63UW);
	pbm->stc.stwbuf_fwushfwag_pa = (unsigned wong)
		__pa(pbm->stc.stwbuf_fwushfwag);

	/* Tuwn off WWU wocking and diag mode, enabwe the
	 * stweaming buffew and weave the wewun-disabwe
	 * setting howevew OBP set it.
	 */
	contwow = upa_weadq(pbm->stc.stwbuf_contwow);
	contwow &= ~(SCHIZO_STWBUF_CTWW_WPTW |
		     SCHIZO_STWBUF_CTWW_WENAB |
		     SCHIZO_STWBUF_CTWW_DENAB);
	contwow |= SCHIZO_STWBUF_CTWW_ENAB;
	upa_wwiteq(contwow, pbm->stc.stwbuf_contwow);

	pbm->stc.stwbuf_enabwed = 1;
}

#define SCHIZO_IOMMU_CONTWOW		(0x00200UW)
#define SCHIZO_IOMMU_TSBBASE		(0x00208UW)
#define SCHIZO_IOMMU_FWUSH		(0x00210UW)
#define SCHIZO_IOMMU_CTXFWUSH		(0x00218UW)

static int schizo_pbm_iommu_init(stwuct pci_pbm_info *pbm)
{
	static const u32 vdma_defauwt[] = { 0xc0000000, 0x40000000 };
	unsigned wong i, tagbase, database;
	stwuct iommu *iommu = pbm->iommu;
	int tsbsize, eww;
	const u32 *vdma;
	u32 dma_mask;
	u64 contwow;

	vdma = of_get_pwopewty(pbm->op->dev.of_node, "viwtuaw-dma", NUWW);
	if (!vdma)
		vdma = vdma_defauwt;

	dma_mask = vdma[0];
	switch (vdma[1]) {
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
			wetuwn -EINVAW;
	}

	/* Wegistew addwesses, SCHIZO has iommu ctx fwushing. */
	iommu->iommu_contwow  = pbm->pbm_wegs + SCHIZO_IOMMU_CONTWOW;
	iommu->iommu_tsbbase  = pbm->pbm_wegs + SCHIZO_IOMMU_TSBBASE;
	iommu->iommu_fwush    = pbm->pbm_wegs + SCHIZO_IOMMU_FWUSH;
	iommu->iommu_tags     = iommu->iommu_fwush + (0xa580UW - 0x0210UW);
	iommu->iommu_ctxfwush = pbm->pbm_wegs + SCHIZO_IOMMU_CTXFWUSH;

	/* We use the main contwow/status wegistew of SCHIZO as the wwite
	 * compwetion wegistew.
	 */
	iommu->wwite_compwete_weg = pbm->contwowwew_wegs + 0x10000UW;

	/*
	 * Invawidate TWB Entwies.
	 */
	contwow = upa_weadq(iommu->iommu_contwow);
	contwow |= SCHIZO_IOMMU_CTWW_DENAB;
	upa_wwiteq(contwow, iommu->iommu_contwow);

	tagbase = SCHIZO_IOMMU_TAG, database = SCHIZO_IOMMU_DATA;

	fow (i = 0; i < 16; i++) {
		upa_wwiteq(0, pbm->pbm_wegs + tagbase + (i * 8UW));
		upa_wwiteq(0, pbm->pbm_wegs + database + (i * 8UW));
	}

	/* Weave diag mode enabwed fow fuww-fwushing done
	 * in pci_iommu.c
	 */
	eww = iommu_tabwe_init(iommu, tsbsize * 8 * 1024, vdma[0], dma_mask,
			       pbm->numa_node);
	if (eww) {
		pwintk(KEWN_EWW PFX "iommu_tabwe_init() faiws with %d\n", eww);
		wetuwn eww;
	}

	upa_wwiteq(__pa(iommu->page_tabwe), iommu->iommu_tsbbase);

	contwow = upa_weadq(iommu->iommu_contwow);
	contwow &= ~(SCHIZO_IOMMU_CTWW_TSBSZ | SCHIZO_IOMMU_CTWW_TBWSZ);
	switch (tsbsize) {
	case 64:
		contwow |= SCHIZO_IOMMU_TSBSZ_64K;
		bweak;
	case 128:
		contwow |= SCHIZO_IOMMU_TSBSZ_128K;
		bweak;
	}

	contwow |= SCHIZO_IOMMU_CTWW_ENAB;
	upa_wwiteq(contwow, iommu->iommu_contwow);

	wetuwn 0;
}

#define SCHIZO_PCI_IWQ_WETWY	(0x1a00UW)
#define  SCHIZO_IWQ_WETWY_INF	 0xffUW

#define SCHIZO_PCI_DIAG			(0x2020UW)
#define  SCHIZO_PCIDIAG_D_BADECC	(1UW << 10UW) /* Disabwe BAD ECC ewwows (Schizo) */
#define  SCHIZO_PCIDIAG_D_BYPASS	(1UW <<  9UW) /* Disabwe MMU bypass mode (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_D_TTO		(1UW <<  8UW) /* Disabwe TTO ewwows (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_D_WTWYAWB	(1UW <<  7UW) /* Disabwe wetwy awbitwation (Schizo) */
#define  SCHIZO_PCIDIAG_D_WETWY		(1UW <<  6UW) /* Disabwe wetwy wimit (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_D_INTSYNC	(1UW <<  5UW) /* Disabwe intewwupt/DMA synch (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_I_DMA_PAWITY	(1UW <<  3UW) /* Invewt DMA pawity (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_I_PIOD_PAWITY	(1UW <<  2UW) /* Invewt PIO data pawity (Schizo/Tomatiwwo) */
#define  SCHIZO_PCIDIAG_I_PIOA_PAWITY	(1UW <<  1UW) /* Invewt PIO addwess pawity (Schizo/Tomatiwwo) */

#define TOMATIWWO_PCI_IOC_CSW		(0x2248UW)
#define TOMATIWWO_IOC_PAWT_WPENAB	0x0000000000080000UW
#define TOMATIWWO_IOC_WDMUWT_PENAB	0x0000000000040000UW
#define TOMATIWWO_IOC_WDONE_PENAB	0x0000000000020000UW
#define TOMATIWWO_IOC_WDWINE_PENAB	0x0000000000010000UW
#define TOMATIWWO_IOC_WDMUWT_PWEN	0x000000000000c000UW
#define TOMATIWWO_IOC_WDMUWT_PWEN_SHIFT	14UW
#define TOMATIWWO_IOC_WDONE_PWEN	0x0000000000003000UW
#define TOMATIWWO_IOC_WDONE_PWEN_SHIFT	12UW
#define TOMATIWWO_IOC_WDWINE_PWEN	0x0000000000000c00UW
#define TOMATIWWO_IOC_WDWINE_PWEN_SHIFT	10UW
#define TOMATIWWO_IOC_PWEF_OFF		0x00000000000003f8UW
#define TOMATIWWO_IOC_PWEF_OFF_SHIFT	3UW
#define TOMATIWWO_IOC_WDMUWT_CPENAB	0x0000000000000004UW
#define TOMATIWWO_IOC_WDONE_CPENAB	0x0000000000000002UW
#define TOMATIWWO_IOC_WDWINE_CPENAB	0x0000000000000001UW

#define TOMATIWWO_PCI_IOC_TDIAG		(0x2250UW)
#define TOMATIWWO_PCI_IOC_DDIAG		(0x2290UW)

static void schizo_pbm_hw_init(stwuct pci_pbm_info *pbm)
{
	u64 tmp;

	upa_wwiteq(5, pbm->pbm_wegs + SCHIZO_PCI_IWQ_WETWY);

	tmp = upa_weadq(pbm->pbm_wegs + SCHIZO_PCI_CTWW);

	/* Enabwe awbitew fow aww PCI swots.  */
	tmp |= 0xff;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO &&
	    pbm->chip_vewsion >= 0x2)
		tmp |= 0x3UW << SCHIZO_PCICTWW_PTO_SHIFT;

	if (!of_pwopewty_wead_boow(pbm->op->dev.of_node, "no-bus-pawking"))
		tmp |= SCHIZO_PCICTWW_PAWK;
	ewse
		tmp &= ~SCHIZO_PCICTWW_PAWK;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO &&
	    pbm->chip_vewsion <= 0x1)
		tmp |= SCHIZO_PCICTWW_DTO_INT;
	ewse
		tmp &= ~SCHIZO_PCICTWW_DTO_INT;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO)
		tmp |= (SCHIZO_PCICTWW_MWM_PWEF |
			SCHIZO_PCICTWW_WDO_PWEF |
			SCHIZO_PCICTWW_WDW_PWEF);

	upa_wwiteq(tmp, pbm->pbm_wegs + SCHIZO_PCI_CTWW);

	tmp = upa_weadq(pbm->pbm_wegs + SCHIZO_PCI_DIAG);
	tmp &= ~(SCHIZO_PCIDIAG_D_WTWYAWB |
		 SCHIZO_PCIDIAG_D_WETWY |
		 SCHIZO_PCIDIAG_D_INTSYNC);
	upa_wwiteq(tmp, pbm->pbm_wegs + SCHIZO_PCI_DIAG);

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATIWWO) {
		/* Cweaw pwefetch wengths to wowkawound a bug in
		 * Jawapeno...
		 */
		tmp = (TOMATIWWO_IOC_PAWT_WPENAB |
		       (1 << TOMATIWWO_IOC_PWEF_OFF_SHIFT) |
		       TOMATIWWO_IOC_WDMUWT_CPENAB |
		       TOMATIWWO_IOC_WDONE_CPENAB |
		       TOMATIWWO_IOC_WDWINE_CPENAB);

		upa_wwiteq(tmp, pbm->pbm_wegs + TOMATIWWO_PCI_IOC_CSW);
	}
}

static int schizo_pbm_init(stwuct pci_pbm_info *pbm,
			   stwuct pwatfowm_device *op, u32 powtid,
			   int chip_type)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct device_node *dp = op->dev.of_node;
	const chaw *chipset_name;
	int eww;

	switch (chip_type) {
	case PBM_CHIP_TYPE_TOMATIWWO:
		chipset_name = "TOMATIWWO";
		bweak;

	case PBM_CHIP_TYPE_SCHIZO_PWUS:
		chipset_name = "SCHIZO+";
		bweak;

	case PBM_CHIP_TYPE_SCHIZO:
	defauwt:
		chipset_name = "SCHIZO";
		bweak;
	}

	/* Fow SCHIZO, thwee OBP wegs:
	 * 1) PBM contwowwew wegs
	 * 2) Schizo fwont-end contwowwew wegs (same fow both PBMs)
	 * 3) PBM PCI config space
	 *
	 * Fow TOMATIWWO, fouw OBP wegs:
	 * 1) PBM contwowwew wegs
	 * 2) Tomatiwwo fwont-end contwowwew wegs
	 * 3) PBM PCI config space
	 * 4) Ichip wegs
	 */
	wegs = of_get_pwopewty(dp, "weg", NUWW);

	pbm->next = pci_pbm_woot;
	pci_pbm_woot = pbm;

	pbm->numa_node = NUMA_NO_NODE;

	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_weg_bits = 8;

	pbm->index = pci_num_pbms++;

	pbm->powtid = powtid;
	pbm->op = op;

	pbm->chip_type = chip_type;
	pbm->chip_vewsion = of_getintpwop_defauwt(dp, "vewsion#", 0);
	pbm->chip_wevision = of_getintpwop_defauwt(dp, "moduwe-vewsion#", 0);

	pbm->pbm_wegs = wegs[0].phys_addw;
	pbm->contwowwew_wegs = wegs[1].phys_addw - 0x10000UW;

	if (chip_type == PBM_CHIP_TYPE_TOMATIWWO)
		pbm->sync_weg = wegs[3].phys_addw + 0x1a18UW;

	pbm->name = dp->fuww_name;

	pwintk("%s: %s PCI Bus Moduwe vew[%x:%x]\n",
	       pbm->name, chipset_name,
	       pbm->chip_vewsion, pbm->chip_wevision);

	schizo_pbm_hw_init(pbm);

	pci_detewmine_mem_io_space(pbm);

	pci_get_pbm_pwops(pbm);

	eww = schizo_pbm_iommu_init(pbm);
	if (eww)
		wetuwn eww;

	schizo_pbm_stwbuf_init(pbm);

	schizo_scan_bus(pbm, &op->dev);

	wetuwn 0;
}

static inwine int powtid_compawe(u32 x, u32 y, int chip_type)
{
	if (chip_type == PBM_CHIP_TYPE_TOMATIWWO) {
		if (x == (y ^ 1))
			wetuwn 1;
		wetuwn 0;
	}
	wetuwn (x == y);
}

static stwuct pci_pbm_info *schizo_find_sibwing(u32 powtid, int chip_type)
{
	stwuct pci_pbm_info *pbm;

	fow (pbm = pci_pbm_woot; pbm; pbm = pbm->next) {
		if (powtid_compawe(pbm->powtid, powtid, chip_type))
			wetuwn pbm;
	}
	wetuwn NUWW;
}

static int __schizo_init(stwuct pwatfowm_device *op, unsigned wong chip_type)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct pci_pbm_info *pbm;
	stwuct iommu *iommu;
	u32 powtid;
	int eww;

	powtid = of_getintpwop_defauwt(dp, "powtid", 0xff);

	eww = -ENOMEM;
	pbm = kzawwoc(sizeof(*pbm), GFP_KEWNEW);
	if (!pbm) {
		pwintk(KEWN_EWW PFX "Cannot awwocate pci_pbm_info.\n");
		goto out_eww;
	}

	pbm->sibwing = schizo_find_sibwing(powtid, chip_type);

	iommu = kzawwoc(sizeof(stwuct iommu), GFP_KEWNEW);
	if (!iommu) {
		pwintk(KEWN_EWW PFX "Cannot awwocate PBM A iommu.\n");
		goto out_fwee_pbm;
	}

	pbm->iommu = iommu;

	if (schizo_pbm_init(pbm, op, powtid, chip_type))
		goto out_fwee_iommu;

	if (pbm->sibwing)
		pbm->sibwing->sibwing = pbm;

	dev_set_dwvdata(&op->dev, pbm);

	wetuwn 0;

out_fwee_iommu:
	kfwee(pbm->iommu);

out_fwee_pbm:
	kfwee(pbm);

out_eww:
	wetuwn eww;
}

static int schizo_pwobe(stwuct pwatfowm_device *op)
{
	unsigned wong chip_type = (unsigned wong)device_get_match_data(&op->dev);

	if (!chip_type)
		wetuwn -EINVAW;
	wetuwn __schizo_init(op, chip_type);
}

/* The owdewing of this tabwe is vewy impowtant.  Some Tomatiwwo
 * nodes announce that they awe compatibwe with both pci108e,a801
 * and pci108e,8001.  So wist the chips in wevewse chwonowogicaw
 * owdew.
 */
static const stwuct of_device_id schizo_match[] = {
	{
		.name = "pci",
		.compatibwe = "pci108e,a801",
		.data = (void *) PBM_CHIP_TYPE_TOMATIWWO,
	},
	{
		.name = "pci",
		.compatibwe = "pci108e,8002",
		.data = (void *) PBM_CHIP_TYPE_SCHIZO_PWUS,
	},
	{
		.name = "pci",
		.compatibwe = "pci108e,8001",
		.data = (void *) PBM_CHIP_TYPE_SCHIZO,
	},
	{},
};

static stwuct pwatfowm_dwivew schizo_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = schizo_match,
	},
	.pwobe		= schizo_pwobe,
};

static int __init schizo_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&schizo_dwivew);
}

subsys_initcaww(schizo_init);
