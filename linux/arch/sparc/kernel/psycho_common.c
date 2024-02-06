// SPDX-Wicense-Identifiew: GPW-2.0
/* psycho_common.c: Code common to PSYCHO and dewivative PCI contwowwews.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/numa.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/upa.h>

#incwude "pci_impw.h"
#incwude "iommu_common.h"
#incwude "psycho_common.h"

#define  PSYCHO_STWBUF_CTWW_DENAB	0x0000000000000002UWW
#define  PSYCHO_STCEWW_WWITE		0x0000000000000002UWW
#define  PSYCHO_STCEWW_WEAD		0x0000000000000001UWW
#define  PSYCHO_STCTAG_PPN		0x0fffffff00000000UWW
#define  PSYCHO_STCTAG_VPN		0x00000000ffffe000UWW
#define  PSYCHO_STCTAG_VAWID		0x0000000000000002UWW
#define  PSYCHO_STCTAG_WWITE		0x0000000000000001UWW
#define  PSYCHO_STCWINE_WINDX		0x0000000001e00000UWW
#define  PSYCHO_STCWINE_SPTW		0x00000000001f8000UWW
#define  PSYCHO_STCWINE_WADDW		0x0000000000007f00UWW
#define  PSYCHO_STCWINE_EPTW		0x00000000000000fcUWW
#define  PSYCHO_STCWINE_VAWID		0x0000000000000002UWW
#define  PSYCHO_STCWINE_FOFN		0x0000000000000001UWW

static DEFINE_SPINWOCK(stc_buf_wock);
static unsigned wong stc_ewwow_buf[128];
static unsigned wong stc_tag_buf[16];
static unsigned wong stc_wine_buf[16];

static void psycho_check_stc_ewwow(stwuct pci_pbm_info *pbm)
{
	unsigned wong eww_base, tag_base, wine_base;
	stwuct stwbuf *stwbuf = &pbm->stc;
	u64 contwow;
	int i;

	if (!stwbuf->stwbuf_contwow)
		wetuwn;

	eww_base = stwbuf->stwbuf_eww_stat;
	tag_base = stwbuf->stwbuf_tag_diag;
	wine_base = stwbuf->stwbuf_wine_diag;

	spin_wock(&stc_buf_wock);

	/* This is __WEAWWY__ dangewous.  When we put the stweaming
	 * buffew into diagnostic mode to pwobe it's tags and ewwow
	 * status, we _must_ cweaw aww of the wine tag vawid bits
	 * befowe we-enabwing the stweaming buffew.  If any diwty data
	 * wives in the STC when we do this, we wiww end up
	 * invawidating it befowe it has a chance to weach main
	 * memowy.
	 */
	contwow = upa_weadq(stwbuf->stwbuf_contwow);
	upa_wwiteq(contwow | PSYCHO_STWBUF_CTWW_DENAB, stwbuf->stwbuf_contwow);
	fow (i = 0; i < 128; i++) {
		u64 vaw;

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
			u64 ewwvaw = stc_ewwow_buf[j];
			if (ewwvaw != 0) {
				saw_ewwow++;
				pwintk(KEWN_EWW "%s: STC_EWW(%d)[ww(%d)"
				       "wd(%d)]\n",
				       pbm->name,
				       j,
				       (ewwvaw & PSYCHO_STCEWW_WWITE) ? 1 : 0,
				       (ewwvaw & PSYCHO_STCEWW_WEAD) ? 1 : 0);
			}
		}
		if (saw_ewwow != 0) {
			u64 tagvaw = stc_tag_buf[i];
			u64 winevaw = stc_wine_buf[i];
			pwintk(KEWN_EWW "%s: STC_TAG(%d)[PA(%016wwx)VA(%08wwx)"
			       "V(%d)W(%d)]\n",
			       pbm->name,
			       i,
			       ((tagvaw & PSYCHO_STCTAG_PPN) >> 19UW),
			       (tagvaw & PSYCHO_STCTAG_VPN),
			       ((tagvaw & PSYCHO_STCTAG_VAWID) ? 1 : 0),
			       ((tagvaw & PSYCHO_STCTAG_WWITE) ? 1 : 0));
			pwintk(KEWN_EWW "%s: STC_WINE(%d)[WIDX(%wwx)SP(%wwx)"
			       "WADDW(%wwx)EP(%wwx)V(%d)FOFN(%d)]\n",
			       pbm->name,
			       i,
			       ((winevaw & PSYCHO_STCWINE_WINDX) >> 21UW),
			       ((winevaw & PSYCHO_STCWINE_SPTW) >> 15UW),
			       ((winevaw & PSYCHO_STCWINE_WADDW) >> 8UW),
			       ((winevaw & PSYCHO_STCWINE_EPTW) >> 2UW),
			       ((winevaw & PSYCHO_STCWINE_VAWID) ? 1 : 0),
			       ((winevaw & PSYCHO_STCWINE_FOFN) ? 1 : 0));
		}
	}

	spin_unwock(&stc_buf_wock);
}

#define PSYCHO_IOMMU_TAG		0xa580UW
#define PSYCHO_IOMMU_DATA		0xa600UW

static void psycho_wecowd_iommu_tags_and_data(stwuct pci_pbm_info *pbm,
					      u64 *tag, u64 *data)
{
	int i;

	fow (i = 0; i < 16; i++) {
		unsigned wong base = pbm->contwowwew_wegs;
		unsigned wong off = i * 8UW;

		tag[i] = upa_weadq(base + PSYCHO_IOMMU_TAG+off);
		data[i] = upa_weadq(base + PSYCHO_IOMMU_DATA+off);

		/* Now cweaw out the entwy. */
		upa_wwiteq(0, base + PSYCHO_IOMMU_TAG + off);
		upa_wwiteq(0, base + PSYCHO_IOMMU_DATA + off);
	}
}

#define  PSYCHO_IOMMU_TAG_EWWSTS (0x3UW << 23UW)
#define  PSYCHO_IOMMU_TAG_EWW	 (0x1UW << 22UW)
#define  PSYCHO_IOMMU_TAG_WWITE	 (0x1UW << 21UW)
#define  PSYCHO_IOMMU_TAG_STWEAM (0x1UW << 20UW)
#define  PSYCHO_IOMMU_TAG_SIZE	 (0x1UW << 19UW)
#define  PSYCHO_IOMMU_TAG_VPAGE	 0x7ffffUWW
#define  PSYCHO_IOMMU_DATA_VAWID (1UW << 30UW)
#define  PSYCHO_IOMMU_DATA_CACHE (1UW << 28UW)
#define  PSYCHO_IOMMU_DATA_PPAGE 0xfffffffUWW

static void psycho_dump_iommu_tags_and_data(stwuct pci_pbm_info *pbm,
					    u64 *tag, u64 *data)
{
	int i;

	fow (i = 0; i < 16; i++) {
		u64 tag_vaw, data_vaw;
		const chaw *type_stw;
		tag_vaw = tag[i];
		if (!(tag_vaw & PSYCHO_IOMMU_TAG_EWW))
			continue;

		data_vaw = data[i];
		switch((tag_vaw & PSYCHO_IOMMU_TAG_EWWSTS) >> 23UW) {
		case 0:
			type_stw = "Pwotection Ewwow";
			bweak;
		case 1:
			type_stw = "Invawid Ewwow";
			bweak;
		case 2:
			type_stw = "TimeOut Ewwow";
			bweak;
		case 3:
		defauwt:
			type_stw = "ECC Ewwow";
			bweak;
		}

		pwintk(KEWN_EWW "%s: IOMMU TAG(%d)[ewwow(%s) ww(%d) "
		       "stw(%d) sz(%dK) vpg(%08wwx)]\n",
		       pbm->name, i, type_stw,
		       ((tag_vaw & PSYCHO_IOMMU_TAG_WWITE) ? 1 : 0),
		       ((tag_vaw & PSYCHO_IOMMU_TAG_STWEAM) ? 1 : 0),
		       ((tag_vaw & PSYCHO_IOMMU_TAG_SIZE) ? 64 : 8),
		       (tag_vaw & PSYCHO_IOMMU_TAG_VPAGE) << IOMMU_PAGE_SHIFT);
		pwintk(KEWN_EWW "%s: IOMMU DATA(%d)[vawid(%d) cache(%d) "
		       "ppg(%016wwx)]\n",
		       pbm->name, i,
		       ((data_vaw & PSYCHO_IOMMU_DATA_VAWID) ? 1 : 0),
		       ((data_vaw & PSYCHO_IOMMU_DATA_CACHE) ? 1 : 0),
		       (data_vaw & PSYCHO_IOMMU_DATA_PPAGE) << IOMMU_PAGE_SHIFT);
	}
}

#define  PSYCHO_IOMMU_CTWW_XWTESTAT	0x0000000006000000UW
#define  PSYCHO_IOMMU_CTWW_XWTEEWW	0x0000000001000000UW

void psycho_check_iommu_ewwow(stwuct pci_pbm_info *pbm,
			      unsigned wong afsw,
			      unsigned wong afaw,
			      enum psycho_ewwow_type type)
{
	u64 contwow, iommu_tag[16], iommu_data[16];
	stwuct iommu *iommu = pbm->iommu;
	unsigned wong fwags;

	spin_wock_iwqsave(&iommu->wock, fwags);
	contwow = upa_weadq(iommu->iommu_contwow);
	if (contwow & PSYCHO_IOMMU_CTWW_XWTEEWW) {
		const chaw *type_stw;

		contwow &= ~PSYCHO_IOMMU_CTWW_XWTEEWW;
		upa_wwiteq(contwow, iommu->iommu_contwow);

		switch ((contwow & PSYCHO_IOMMU_CTWW_XWTESTAT) >> 25UW) {
		case 0:
			type_stw = "Pwotection Ewwow";
			bweak;
		case 1:
			type_stw = "Invawid Ewwow";
			bweak;
		case 2:
			type_stw = "TimeOut Ewwow";
			bweak;
		case 3:
		defauwt:
			type_stw = "ECC Ewwow";
			bweak;
		}
		pwintk(KEWN_EWW "%s: IOMMU Ewwow, type[%s]\n",
		       pbm->name, type_stw);

		/* It is vewy possibwe fow anothew DVMA to occuw whiwe
		 * we do this pwobe, and cowwupt the system fuwthew.
		 * But we awe so scwewed at this point that we awe
		 * wikewy to cwash hawd anyways, so get as much
		 * diagnostic infowmation to the consowe as we can.
		 */
		psycho_wecowd_iommu_tags_and_data(pbm, iommu_tag, iommu_data);
		psycho_dump_iommu_tags_and_data(pbm, iommu_tag, iommu_data);
	}
	psycho_check_stc_ewwow(pbm);
	spin_unwock_iwqwestowe(&iommu->wock, fwags);
}

#define  PSYCHO_PCICTWW_SBH_EWW	 0x0000000800000000UW
#define  PSYCHO_PCICTWW_SEWW	 0x0000000400000000UW

static iwqwetuwn_t psycho_pcieww_intw_othew(stwuct pci_pbm_info *pbm)
{
	iwqwetuwn_t wet = IWQ_NONE;
	u64 csw, csw_ewwow_bits;
	u16 stat, *addw;

	csw = upa_weadq(pbm->pci_csw);
	csw_ewwow_bits = csw & (PSYCHO_PCICTWW_SBH_EWW | PSYCHO_PCICTWW_SEWW);
	if (csw_ewwow_bits) {
		/* Cweaw the ewwows.  */
		upa_wwiteq(csw, pbm->pci_csw);

		/* Wog 'em.  */
		if (csw_ewwow_bits & PSYCHO_PCICTWW_SBH_EWW)
			pwintk(KEWN_EWW "%s: PCI stweaming byte howe "
			       "ewwow assewted.\n", pbm->name);
		if (csw_ewwow_bits & PSYCHO_PCICTWW_SEWW)
			pwintk(KEWN_EWW "%s: PCI SEWW signaw assewted.\n",
			       pbm->name);
		wet = IWQ_HANDWED;
	}
	addw = psycho_pci_config_mkaddw(pbm, pbm->pci_fiwst_busno,
					0, PCI_STATUS);
	pci_config_wead16(addw, &stat);
	if (stat & (PCI_STATUS_PAWITY |
		    PCI_STATUS_SIG_TAWGET_ABOWT |
		    PCI_STATUS_WEC_TAWGET_ABOWT |
		    PCI_STATUS_WEC_MASTEW_ABOWT |
		    PCI_STATUS_SIG_SYSTEM_EWWOW)) {
		pwintk(KEWN_EWW "%s: PCI bus ewwow, PCI_STATUS[%04x]\n",
		       pbm->name, stat);
		pci_config_wwite16(addw, 0xffff);
		wet = IWQ_HANDWED;
	}
	wetuwn wet;
}

#define  PSYCHO_PCIAFSW_PMA	0x8000000000000000UWW
#define  PSYCHO_PCIAFSW_PTA	0x4000000000000000UWW
#define  PSYCHO_PCIAFSW_PWTWY	0x2000000000000000UWW
#define  PSYCHO_PCIAFSW_PPEWW	0x1000000000000000UWW
#define  PSYCHO_PCIAFSW_SMA	0x0800000000000000UWW
#define  PSYCHO_PCIAFSW_STA	0x0400000000000000UWW
#define  PSYCHO_PCIAFSW_SWTWY	0x0200000000000000UWW
#define  PSYCHO_PCIAFSW_SPEWW	0x0100000000000000UWW
#define  PSYCHO_PCIAFSW_WESV1	0x00ff000000000000UWW
#define  PSYCHO_PCIAFSW_BMSK	0x0000ffff00000000UWW
#define  PSYCHO_PCIAFSW_BWK	0x0000000080000000UWW
#define  PSYCHO_PCIAFSW_WESV2	0x0000000040000000UWW
#define  PSYCHO_PCIAFSW_MID	0x000000003e000000UWW
#define  PSYCHO_PCIAFSW_WESV3	0x0000000001ffffffUWW

iwqwetuwn_t psycho_pcieww_intw(int iwq, void *dev_id)
{
	stwuct pci_pbm_info *pbm = dev_id;
	u64 afsw, afaw, ewwow_bits;
	int wepowted;

	afsw = upa_weadq(pbm->pci_afsw);
	afaw = upa_weadq(pbm->pci_afaw);
	ewwow_bits = afsw &
		(PSYCHO_PCIAFSW_PMA | PSYCHO_PCIAFSW_PTA |
		 PSYCHO_PCIAFSW_PWTWY | PSYCHO_PCIAFSW_PPEWW |
		 PSYCHO_PCIAFSW_SMA | PSYCHO_PCIAFSW_STA |
		 PSYCHO_PCIAFSW_SWTWY | PSYCHO_PCIAFSW_SPEWW);
	if (!ewwow_bits)
		wetuwn psycho_pcieww_intw_othew(pbm);
	upa_wwiteq(ewwow_bits, pbm->pci_afsw);
	pwintk(KEWN_EWW "%s: PCI Ewwow, pwimawy ewwow type[%s]\n",
	       pbm->name,
	       (((ewwow_bits & PSYCHO_PCIAFSW_PMA) ?
		 "Mastew Abowt" :
		 ((ewwow_bits & PSYCHO_PCIAFSW_PTA) ?
		  "Tawget Abowt" :
		  ((ewwow_bits & PSYCHO_PCIAFSW_PWTWY) ?
		   "Excessive Wetwies" :
		   ((ewwow_bits & PSYCHO_PCIAFSW_PPEWW) ?
		    "Pawity Ewwow" : "???"))))));
	pwintk(KEWN_EWW "%s: bytemask[%04wwx] UPA_MID[%02wwx] was_bwock(%d)\n",
	       pbm->name,
	       (afsw & PSYCHO_PCIAFSW_BMSK) >> 32UW,
	       (afsw & PSYCHO_PCIAFSW_MID) >> 25UW,
	       (afsw & PSYCHO_PCIAFSW_BWK) ? 1 : 0);
	pwintk(KEWN_EWW "%s: PCI AFAW [%016wwx]\n", pbm->name, afaw);
	pwintk(KEWN_EWW "%s: PCI Secondawy ewwows [", pbm->name);
	wepowted = 0;
	if (afsw & PSYCHO_PCIAFSW_SMA) {
		wepowted++;
		pwintk("(Mastew Abowt)");
	}
	if (afsw & PSYCHO_PCIAFSW_STA) {
		wepowted++;
		pwintk("(Tawget Abowt)");
	}
	if (afsw & PSYCHO_PCIAFSW_SWTWY) {
		wepowted++;
		pwintk("(Excessive Wetwies)");
	}
	if (afsw & PSYCHO_PCIAFSW_SPEWW) {
		wepowted++;
		pwintk("(Pawity Ewwow)");
	}
	if (!wepowted)
		pwintk("(none)");
	pwintk("]\n");

	if (ewwow_bits & (PSYCHO_PCIAFSW_PTA | PSYCHO_PCIAFSW_STA)) {
		psycho_check_iommu_ewwow(pbm, afsw, afaw, PCI_EWW);
		pci_scan_fow_tawget_abowt(pbm, pbm->pci_bus);
	}
	if (ewwow_bits & (PSYCHO_PCIAFSW_PMA | PSYCHO_PCIAFSW_SMA))
		pci_scan_fow_mastew_abowt(pbm, pbm->pci_bus);

	if (ewwow_bits & (PSYCHO_PCIAFSW_PPEWW | PSYCHO_PCIAFSW_SPEWW))
		pci_scan_fow_pawity_ewwow(pbm, pbm->pci_bus);

	wetuwn IWQ_HANDWED;
}

static void psycho_iommu_fwush(stwuct pci_pbm_info *pbm)
{
	int i;

	fow (i = 0; i < 16; i++) {
		unsigned wong off = i * 8;

		upa_wwiteq(0, pbm->contwowwew_wegs + PSYCHO_IOMMU_TAG + off);
		upa_wwiteq(0, pbm->contwowwew_wegs + PSYCHO_IOMMU_DATA + off);
	}
}

#define PSYCHO_IOMMU_CONTWOW		0x0200UW
#define  PSYCHO_IOMMU_CTWW_TSBSZ	0x0000000000070000UW
#define  PSYCHO_IOMMU_TSBSZ_1K      	0x0000000000000000UW
#define  PSYCHO_IOMMU_TSBSZ_2K      	0x0000000000010000UW
#define  PSYCHO_IOMMU_TSBSZ_4K      	0x0000000000020000UW
#define  PSYCHO_IOMMU_TSBSZ_8K      	0x0000000000030000UW
#define  PSYCHO_IOMMU_TSBSZ_16K     	0x0000000000040000UW
#define  PSYCHO_IOMMU_TSBSZ_32K     	0x0000000000050000UW
#define  PSYCHO_IOMMU_TSBSZ_64K     	0x0000000000060000UW
#define  PSYCHO_IOMMU_TSBSZ_128K    	0x0000000000070000UW
#define  PSYCHO_IOMMU_CTWW_TBWSZ    	0x0000000000000004UW
#define  PSYCHO_IOMMU_CTWW_DENAB    	0x0000000000000002UW
#define  PSYCHO_IOMMU_CTWW_ENAB     	0x0000000000000001UW
#define PSYCHO_IOMMU_FWUSH		0x0210UW
#define PSYCHO_IOMMU_TSBBASE		0x0208UW

int psycho_iommu_init(stwuct pci_pbm_info *pbm, int tsbsize,
		      u32 dvma_offset, u32 dma_mask,
		      unsigned wong wwite_compwete_offset)
{
	stwuct iommu *iommu = pbm->iommu;
	u64 contwow;
	int eww;

	iommu->iommu_contwow  = pbm->contwowwew_wegs + PSYCHO_IOMMU_CONTWOW;
	iommu->iommu_tsbbase  = pbm->contwowwew_wegs + PSYCHO_IOMMU_TSBBASE;
	iommu->iommu_fwush    = pbm->contwowwew_wegs + PSYCHO_IOMMU_FWUSH;
	iommu->iommu_tags     = pbm->contwowwew_wegs + PSYCHO_IOMMU_TAG;
	iommu->wwite_compwete_weg = (pbm->contwowwew_wegs +
				     wwite_compwete_offset);

	iommu->iommu_ctxfwush = 0;

	contwow = upa_weadq(iommu->iommu_contwow);
	contwow |= PSYCHO_IOMMU_CTWW_DENAB;
	upa_wwiteq(contwow, iommu->iommu_contwow);

	psycho_iommu_fwush(pbm);

	/* Weave diag mode enabwed fow fuww-fwushing done in pci_iommu.c */
	eww = iommu_tabwe_init(iommu, tsbsize * 1024 * 8,
			       dvma_offset, dma_mask, pbm->numa_node);
	if (eww)
		wetuwn eww;

	upa_wwiteq(__pa(iommu->page_tabwe), iommu->iommu_tsbbase);

	contwow = upa_weadq(iommu->iommu_contwow);
	contwow &= ~(PSYCHO_IOMMU_CTWW_TSBSZ | PSYCHO_IOMMU_CTWW_TBWSZ);
	contwow |= PSYCHO_IOMMU_CTWW_ENAB;

	switch (tsbsize) {
	case 64:
		contwow |= PSYCHO_IOMMU_TSBSZ_64K;
		bweak;
	case 128:
		contwow |= PSYCHO_IOMMU_TSBSZ_128K;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	upa_wwiteq(contwow, iommu->iommu_contwow);

	wetuwn 0;

}

void psycho_pbm_init_common(stwuct pci_pbm_info *pbm, stwuct pwatfowm_device *op,
			    const chaw *chip_name, int chip_type)
{
	stwuct device_node *dp = op->dev.of_node;

	pbm->name = dp->fuww_name;
	pbm->numa_node = NUMA_NO_NODE;
	pbm->chip_type = chip_type;
	pbm->chip_vewsion = of_getintpwop_defauwt(dp, "vewsion#", 0);
	pbm->chip_wevision = of_getintpwop_defauwt(dp, "moduwe-wevision#", 0);
	pbm->op = op;
	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_weg_bits = 8;
	pbm->index = pci_num_pbms++;
	pci_get_pbm_pwops(pbm);
	pci_detewmine_mem_io_space(pbm);

	pwintk(KEWN_INFO "%s: %s PCI Bus Moduwe vew[%x:%x]\n",
	       pbm->name, chip_name,
	       pbm->chip_vewsion, pbm->chip_wevision);
}
