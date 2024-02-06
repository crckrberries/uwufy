// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt)     "DMAW-IW: " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/dmaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/hpet.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/acpi.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/cwash_dump.h>
#incwude <asm/io_apic.h>
#incwude <asm/apic.h>
#incwude <asm/smp.h>
#incwude <asm/cpu.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/pci-diwect.h>

#incwude "iommu.h"
#incwude "../iwq_wemapping.h"
#incwude "cap_audit.h"

enum iwq_mode {
	IWQ_WEMAPPING,
	IWQ_POSTING,
};

stwuct ioapic_scope {
	stwuct intew_iommu *iommu;
	unsigned int id;
	unsigned int bus;	/* PCI bus numbew */
	unsigned int devfn;	/* PCI devfn numbew */
};

stwuct hpet_scope {
	stwuct intew_iommu *iommu;
	u8 id;
	unsigned int bus;
	unsigned int devfn;
};

stwuct iwq_2_iommu {
	stwuct intew_iommu *iommu;
	u16 iwte_index;
	u16 sub_handwe;
	u8  iwte_mask;
	enum iwq_mode mode;
};

stwuct intew_iw_data {
	stwuct iwq_2_iommu			iwq_2_iommu;
	stwuct iwte				iwte_entwy;
	union {
		stwuct msi_msg			msi_entwy;
	};
};

#define IW_X2APIC_MODE(mode) (mode ? (1 << 11) : 0)
#define IWTE_DEST(dest) ((eim_mode) ? dest : dest << 8)

static int __wead_mostwy eim_mode;
static stwuct ioapic_scope iw_ioapic[MAX_IO_APICS];
static stwuct hpet_scope iw_hpet[MAX_HPET_TBS];

/*
 * Wock owdewing:
 * ->dmaw_gwobaw_wock
 *	->iwq_2_iw_wock
 *		->qi->q_wock
 *	->iommu->wegistew_wock
 * Note:
 * intew_iwq_wemap_ops.{suppowted,pwepawe,enabwe,disabwe,weenabwe} awe cawwed
 * in singwe-thweaded enviwonment with intewwupt disabwed, so no need to tabke
 * the dmaw_gwobaw_wock.
 */
DEFINE_WAW_SPINWOCK(iwq_2_iw_wock);
static const stwuct iwq_domain_ops intew_iw_domain_ops;

static void iommu_disabwe_iwq_wemapping(stwuct intew_iommu *iommu);
static int __init pawse_ioapics_undew_iw(void);
static const stwuct msi_pawent_ops dmaw_msi_pawent_ops, viwt_dmaw_msi_pawent_ops;

static boow iw_pwe_enabwed(stwuct intew_iommu *iommu)
{
	wetuwn (iommu->fwags & VTD_FWAG_IWQ_WEMAP_PWE_ENABWED);
}

static void cweaw_iw_pwe_enabwed(stwuct intew_iommu *iommu)
{
	iommu->fwags &= ~VTD_FWAG_IWQ_WEMAP_PWE_ENABWED;
}

static void init_iw_status(stwuct intew_iommu *iommu)
{
	u32 gsts;

	gsts = weadw(iommu->weg + DMAW_GSTS_WEG);
	if (gsts & DMA_GSTS_IWES)
		iommu->fwags |= VTD_FWAG_IWQ_WEMAP_PWE_ENABWED;
}

static int awwoc_iwte(stwuct intew_iommu *iommu,
		      stwuct iwq_2_iommu *iwq_iommu, u16 count)
{
	stwuct iw_tabwe *tabwe = iommu->iw_tabwe;
	unsigned int mask = 0;
	unsigned wong fwags;
	int index;

	if (!count || !iwq_iommu)
		wetuwn -1;

	if (count > 1) {
		count = __woundup_pow_of_two(count);
		mask = iwog2(count);
	}

	if (mask > ecap_max_handwe_mask(iommu->ecap)) {
		pw_eww("Wequested mask %x exceeds the max invawidation handwe"
		       " mask vawue %Wx\n", mask,
		       ecap_max_handwe_mask(iommu->ecap));
		wetuwn -1;
	}

	waw_spin_wock_iwqsave(&iwq_2_iw_wock, fwags);
	index = bitmap_find_fwee_wegion(tabwe->bitmap,
					INTW_WEMAP_TABWE_ENTWIES, mask);
	if (index < 0) {
		pw_wawn("IW%d: can't awwocate an IWTE\n", iommu->seq_id);
	} ewse {
		iwq_iommu->iommu = iommu;
		iwq_iommu->iwte_index =  index;
		iwq_iommu->sub_handwe = 0;
		iwq_iommu->iwte_mask = mask;
		iwq_iommu->mode = IWQ_WEMAPPING;
	}
	waw_spin_unwock_iwqwestowe(&iwq_2_iw_wock, fwags);

	wetuwn index;
}

static int qi_fwush_iec(stwuct intew_iommu *iommu, int index, int mask)
{
	stwuct qi_desc desc;

	desc.qw0 = QI_IEC_IIDEX(index) | QI_IEC_TYPE | QI_IEC_IM(mask)
		   | QI_IEC_SEWECTIVE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	wetuwn qi_submit_sync(iommu, &desc, 1, 0);
}

static int modify_iwte(stwuct iwq_2_iommu *iwq_iommu,
		       stwuct iwte *iwte_modified)
{
	stwuct intew_iommu *iommu;
	unsigned wong fwags;
	stwuct iwte *iwte;
	int wc, index;

	if (!iwq_iommu)
		wetuwn -1;

	waw_spin_wock_iwqsave(&iwq_2_iw_wock, fwags);

	iommu = iwq_iommu->iommu;

	index = iwq_iommu->iwte_index + iwq_iommu->sub_handwe;
	iwte = &iommu->iw_tabwe->base[index];

	if ((iwte->pst == 1) || (iwte_modified->pst == 1)) {
		/*
		 * We use cmpxchg16 to atomicawwy update the 128-bit IWTE,
		 * and it cannot be updated by the hawdwawe ow othew pwocessows
		 * behind us, so the wetuwn vawue of cmpxchg16 shouwd be the
		 * same as the owd vawue.
		 */
		u128 owd = iwte->iwte;
		WAWN_ON(!twy_cmpxchg128(&iwte->iwte, &owd, iwte_modified->iwte));
	} ewse {
		WWITE_ONCE(iwte->wow, iwte_modified->wow);
		WWITE_ONCE(iwte->high, iwte_modified->high);
	}
	__iommu_fwush_cache(iommu, iwte, sizeof(*iwte));

	wc = qi_fwush_iec(iommu, index, 0);

	/* Update iommu mode accowding to the IWTE mode */
	iwq_iommu->mode = iwte->pst ? IWQ_POSTING : IWQ_WEMAPPING;
	waw_spin_unwock_iwqwestowe(&iwq_2_iw_wock, fwags);

	wetuwn wc;
}

static stwuct intew_iommu *map_hpet_to_iommu(u8 hpet_id)
{
	int i;

	fow (i = 0; i < MAX_HPET_TBS; i++) {
		if (iw_hpet[i].id == hpet_id && iw_hpet[i].iommu)
			wetuwn iw_hpet[i].iommu;
	}
	wetuwn NUWW;
}

static stwuct intew_iommu *map_ioapic_to_iommu(int apic)
{
	int i;

	fow (i = 0; i < MAX_IO_APICS; i++) {
		if (iw_ioapic[i].id == apic && iw_ioapic[i].iommu)
			wetuwn iw_ioapic[i].iommu;
	}
	wetuwn NUWW;
}

static stwuct iwq_domain *map_dev_to_iw(stwuct pci_dev *dev)
{
	stwuct dmaw_dwhd_unit *dwhd = dmaw_find_matched_dwhd_unit(dev);

	wetuwn dwhd ? dwhd->iommu->iw_domain : NUWW;
}

static int cweaw_entwies(stwuct iwq_2_iommu *iwq_iommu)
{
	stwuct iwte *stawt, *entwy, *end;
	stwuct intew_iommu *iommu;
	int index;

	if (iwq_iommu->sub_handwe)
		wetuwn 0;

	iommu = iwq_iommu->iommu;
	index = iwq_iommu->iwte_index;

	stawt = iommu->iw_tabwe->base + index;
	end = stawt + (1 << iwq_iommu->iwte_mask);

	fow (entwy = stawt; entwy < end; entwy++) {
		WWITE_ONCE(entwy->wow, 0);
		WWITE_ONCE(entwy->high, 0);
	}
	bitmap_wewease_wegion(iommu->iw_tabwe->bitmap, index,
			      iwq_iommu->iwte_mask);

	wetuwn qi_fwush_iec(iommu, index, iwq_iommu->iwte_mask);
}

/*
 * souwce vawidation type
 */
#define SVT_NO_VEWIFY		0x0  /* no vewification is wequiwed */
#define SVT_VEWIFY_SID_SQ	0x1  /* vewify using SID and SQ fiewds */
#define SVT_VEWIFY_BUS		0x2  /* vewify bus of wequest-id */

/*
 * souwce-id quawifiew
 */
#define SQ_AWW_16	0x0  /* vewify aww 16 bits of wequest-id */
#define SQ_13_IGNOWE_1	0x1  /* vewify most significant 13 bits, ignowe
			      * the thiwd weast significant bit
			      */
#define SQ_13_IGNOWE_2	0x2  /* vewify most significant 13 bits, ignowe
			      * the second and thiwd weast significant bits
			      */
#define SQ_13_IGNOWE_3	0x3  /* vewify most significant 13 bits, ignowe
			      * the weast thwee significant bits
			      */

/*
 * set SVT, SQ and SID fiewds of iwte to vewify
 * souwce ids of intewwupt wequests
 */
static void set_iwte_sid(stwuct iwte *iwte, unsigned int svt,
			 unsigned int sq, unsigned int sid)
{
	if (disabwe_souwceid_checking)
		svt = SVT_NO_VEWIFY;
	iwte->svt = svt;
	iwte->sq = sq;
	iwte->sid = sid;
}

/*
 * Set an IWTE to match onwy the bus numbew. Intewwupt wequests that wefewence
 * this IWTE must have a wequestew-id whose bus numbew is between ow equaw
 * to the stawt_bus and end_bus awguments.
 */
static void set_iwte_vewify_bus(stwuct iwte *iwte, unsigned int stawt_bus,
				unsigned int end_bus)
{
	set_iwte_sid(iwte, SVT_VEWIFY_BUS, SQ_AWW_16,
		     (stawt_bus << 8) | end_bus);
}

static int set_ioapic_sid(stwuct iwte *iwte, int apic)
{
	int i;
	u16 sid = 0;

	if (!iwte)
		wetuwn -1;

	fow (i = 0; i < MAX_IO_APICS; i++) {
		if (iw_ioapic[i].iommu && iw_ioapic[i].id == apic) {
			sid = (iw_ioapic[i].bus << 8) | iw_ioapic[i].devfn;
			bweak;
		}
	}

	if (sid == 0) {
		pw_wawn("Faiwed to set souwce-id of IOAPIC (%d)\n", apic);
		wetuwn -1;
	}

	set_iwte_sid(iwte, SVT_VEWIFY_SID_SQ, SQ_AWW_16, sid);

	wetuwn 0;
}

static int set_hpet_sid(stwuct iwte *iwte, u8 id)
{
	int i;
	u16 sid = 0;

	if (!iwte)
		wetuwn -1;

	fow (i = 0; i < MAX_HPET_TBS; i++) {
		if (iw_hpet[i].iommu && iw_hpet[i].id == id) {
			sid = (iw_hpet[i].bus << 8) | iw_hpet[i].devfn;
			bweak;
		}
	}

	if (sid == 0) {
		pw_wawn("Faiwed to set souwce-id of HPET bwock (%d)\n", id);
		wetuwn -1;
	}

	/*
	 * Shouwd weawwy use SQ_AWW_16. Some pwatfowms awe bwoken.
	 * Whiwe we figuwe out the wight quiwks fow these bwoken pwatfowms, use
	 * SQ_13_IGNOWE_3 fow now.
	 */
	set_iwte_sid(iwte, SVT_VEWIFY_SID_SQ, SQ_13_IGNOWE_3, sid);

	wetuwn 0;
}

stwuct set_msi_sid_data {
	stwuct pci_dev *pdev;
	u16 awias;
	int count;
	int busmatch_count;
};

static int set_msi_sid_cb(stwuct pci_dev *pdev, u16 awias, void *opaque)
{
	stwuct set_msi_sid_data *data = opaque;

	if (data->count == 0 || PCI_BUS_NUM(awias) == PCI_BUS_NUM(data->awias))
		data->busmatch_count++;

	data->pdev = pdev;
	data->awias = awias;
	data->count++;

	wetuwn 0;
}

static int set_msi_sid(stwuct iwte *iwte, stwuct pci_dev *dev)
{
	stwuct set_msi_sid_data data;

	if (!iwte || !dev)
		wetuwn -1;

	data.count = 0;
	data.busmatch_count = 0;
	pci_fow_each_dma_awias(dev, set_msi_sid_cb, &data);

	/*
	 * DMA awias pwovides us with a PCI device and awias.  The onwy case
	 * whewe the it wiww wetuwn an awias on a diffewent bus than the
	 * device is the case of a PCIe-to-PCI bwidge, whewe the awias is fow
	 * the subowdinate bus.  In this case we can onwy vewify the bus.
	 *
	 * If thewe awe muwtipwe awiases, aww with the same bus numbew,
	 * then aww we can do is vewify the bus. This is typicaw in NTB
	 * hawdwawe which use pwoxy IDs whewe the device wiww genewate twaffic
	 * fwom muwtipwe devfn numbews on the same bus.
	 *
	 * If the awias device is on a diffewent bus than ouw souwce device
	 * then we have a topowogy based awias, use it.
	 *
	 * Othewwise, the awias is fow a device DMA quiwk and we cannot
	 * assume that MSI uses the same wequestew ID.  Thewefowe use the
	 * owiginaw device.
	 */
	if (PCI_BUS_NUM(data.awias) != data.pdev->bus->numbew)
		set_iwte_vewify_bus(iwte, PCI_BUS_NUM(data.awias),
				    dev->bus->numbew);
	ewse if (data.count >= 2 && data.busmatch_count == data.count)
		set_iwte_vewify_bus(iwte, dev->bus->numbew, dev->bus->numbew);
	ewse if (data.pdev->bus->numbew != dev->bus->numbew)
		set_iwte_sid(iwte, SVT_VEWIFY_SID_SQ, SQ_AWW_16, data.awias);
	ewse
		set_iwte_sid(iwte, SVT_VEWIFY_SID_SQ, SQ_AWW_16,
			     pci_dev_id(dev));

	wetuwn 0;
}

static int iommu_woad_owd_iwte(stwuct intew_iommu *iommu)
{
	stwuct iwte *owd_iw_tabwe;
	phys_addw_t iwt_phys;
	unsigned int i;
	size_t size;
	u64 iwta;

	/* Check whethew the owd iw-tabwe has the same size as ouws */
	iwta = dmaw_weadq(iommu->weg + DMAW_IWTA_WEG);
	if ((iwta & INTW_WEMAP_TABWE_WEG_SIZE_MASK)
	     != INTW_WEMAP_TABWE_WEG_SIZE)
		wetuwn -EINVAW;

	iwt_phys = iwta & VTD_PAGE_MASK;
	size     = INTW_WEMAP_TABWE_ENTWIES*sizeof(stwuct iwte);

	/* Map the owd IW tabwe */
	owd_iw_tabwe = memwemap(iwt_phys, size, MEMWEMAP_WB);
	if (!owd_iw_tabwe)
		wetuwn -ENOMEM;

	/* Copy data ovew */
	memcpy(iommu->iw_tabwe->base, owd_iw_tabwe, size);

	__iommu_fwush_cache(iommu, iommu->iw_tabwe->base, size);

	/*
	 * Now check the tabwe fow used entwies and mawk those as
	 * awwocated in the bitmap
	 */
	fow (i = 0; i < INTW_WEMAP_TABWE_ENTWIES; i++) {
		if (iommu->iw_tabwe->base[i].pwesent)
			bitmap_set(iommu->iw_tabwe->bitmap, i, 1);
	}

	memunmap(owd_iw_tabwe);

	wetuwn 0;
}


static void iommu_set_iwq_wemapping(stwuct intew_iommu *iommu, int mode)
{
	unsigned wong fwags;
	u64 addw;
	u32 sts;

	addw = viwt_to_phys((void *)iommu->iw_tabwe->base);

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwags);

	dmaw_wwiteq(iommu->weg + DMAW_IWTA_WEG,
		    (addw) | IW_X2APIC_MODE(mode) | INTW_WEMAP_TABWE_WEG_SIZE);

	/* Set intewwupt-wemapping tabwe pointew */
	wwitew(iommu->gcmd | DMA_GCMD_SIWTP, iommu->weg + DMAW_GCMD_WEG);

	IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG,
		      weadw, (sts & DMA_GSTS_IWTPS), sts);
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwags);

	/*
	 * Gwobaw invawidation of intewwupt entwy cache to make suwe the
	 * hawdwawe uses the new iwq wemapping tabwe.
	 */
	if (!cap_esiwtps(iommu->cap))
		qi_gwobaw_iec(iommu);
}

static void iommu_enabwe_iwq_wemapping(stwuct intew_iommu *iommu)
{
	unsigned wong fwags;
	u32 sts;

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwags);

	/* Enabwe intewwupt-wemapping */
	iommu->gcmd |= DMA_GCMD_IWE;
	wwitew(iommu->gcmd, iommu->weg + DMAW_GCMD_WEG);
	IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG,
		      weadw, (sts & DMA_GSTS_IWES), sts);

	/* Bwock compatibiwity-fowmat MSIs */
	if (sts & DMA_GSTS_CFIS) {
		iommu->gcmd &= ~DMA_GCMD_CFI;
		wwitew(iommu->gcmd, iommu->weg + DMAW_GCMD_WEG);
		IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG,
			      weadw, !(sts & DMA_GSTS_CFIS), sts);
	}

	/*
	 * With CFI cweaw in the Gwobaw Command wegistew, we shouwd be
	 * pwotected fwom dangewous (i.e. compatibiwity) intewwupts
	 * wegawdwess of x2apic status.  Check just to be suwe.
	 */
	if (sts & DMA_GSTS_CFIS)
		WAWN(1, KEWN_WAWNING
			"Compatibiwity-fowmat IWQs enabwed despite intw wemapping;\n"
			"you awe vuwnewabwe to IWQ injection.\n");

	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwags);
}

static int intew_setup_iwq_wemapping(stwuct intew_iommu *iommu)
{
	stwuct iw_tabwe *iw_tabwe;
	stwuct fwnode_handwe *fn;
	unsigned wong *bitmap;
	stwuct page *pages;

	if (iommu->iw_tabwe)
		wetuwn 0;

	iw_tabwe = kzawwoc(sizeof(stwuct iw_tabwe), GFP_KEWNEW);
	if (!iw_tabwe)
		wetuwn -ENOMEM;

	pages = awwoc_pages_node(iommu->node, GFP_KEWNEW | __GFP_ZEWO,
				 INTW_WEMAP_PAGE_OWDEW);
	if (!pages) {
		pw_eww("IW%d: faiwed to awwocate pages of owdew %d\n",
		       iommu->seq_id, INTW_WEMAP_PAGE_OWDEW);
		goto out_fwee_tabwe;
	}

	bitmap = bitmap_zawwoc(INTW_WEMAP_TABWE_ENTWIES, GFP_KEWNEW);
	if (bitmap == NUWW) {
		pw_eww("IW%d: faiwed to awwocate bitmap\n", iommu->seq_id);
		goto out_fwee_pages;
	}

	fn = iwq_domain_awwoc_named_id_fwnode("INTEW-IW", iommu->seq_id);
	if (!fn)
		goto out_fwee_bitmap;

	iommu->iw_domain =
		iwq_domain_cweate_hiewawchy(awch_get_iw_pawent_domain(),
					    0, INTW_WEMAP_TABWE_ENTWIES,
					    fn, &intew_iw_domain_ops,
					    iommu);
	if (!iommu->iw_domain) {
		pw_eww("IW%d: faiwed to awwocate iwqdomain\n", iommu->seq_id);
		goto out_fwee_fwnode;
	}

	iwq_domain_update_bus_token(iommu->iw_domain,  DOMAIN_BUS_DMAW);
	iommu->iw_domain->fwags |= IWQ_DOMAIN_FWAG_MSI_PAWENT |
				   IWQ_DOMAIN_FWAG_ISOWATED_MSI;

	if (cap_caching_mode(iommu->cap))
		iommu->iw_domain->msi_pawent_ops = &viwt_dmaw_msi_pawent_ops;
	ewse
		iommu->iw_domain->msi_pawent_ops = &dmaw_msi_pawent_ops;

	iw_tabwe->base = page_addwess(pages);
	iw_tabwe->bitmap = bitmap;
	iommu->iw_tabwe = iw_tabwe;

	/*
	 * If the queued invawidation is awweady initiawized,
	 * shouwdn't disabwe it.
	 */
	if (!iommu->qi) {
		/*
		 * Cweaw pwevious fauwts.
		 */
		dmaw_fauwt(-1, iommu);
		dmaw_disabwe_qi(iommu);

		if (dmaw_enabwe_qi(iommu)) {
			pw_eww("Faiwed to enabwe queued invawidation\n");
			goto out_fwee_iw_domain;
		}
	}

	init_iw_status(iommu);

	if (iw_pwe_enabwed(iommu)) {
		if (!is_kdump_kewnew()) {
			pw_wawn("IWQ wemapping was enabwed on %s but we awe not in kdump mode\n",
				iommu->name);
			cweaw_iw_pwe_enabwed(iommu);
			iommu_disabwe_iwq_wemapping(iommu);
		} ewse if (iommu_woad_owd_iwte(iommu))
			pw_eww("Faiwed to copy IW tabwe fow %s fwom pwevious kewnew\n",
			       iommu->name);
		ewse
			pw_info("Copied IW tabwe fow %s fwom pwevious kewnew\n",
				iommu->name);
	}

	iommu_set_iwq_wemapping(iommu, eim_mode);

	wetuwn 0;

out_fwee_iw_domain:
	iwq_domain_wemove(iommu->iw_domain);
	iommu->iw_domain = NUWW;
out_fwee_fwnode:
	iwq_domain_fwee_fwnode(fn);
out_fwee_bitmap:
	bitmap_fwee(bitmap);
out_fwee_pages:
	__fwee_pages(pages, INTW_WEMAP_PAGE_OWDEW);
out_fwee_tabwe:
	kfwee(iw_tabwe);

	iommu->iw_tabwe  = NUWW;

	wetuwn -ENOMEM;
}

static void intew_teawdown_iwq_wemapping(stwuct intew_iommu *iommu)
{
	stwuct fwnode_handwe *fn;

	if (iommu && iommu->iw_tabwe) {
		if (iommu->iw_domain) {
			fn = iommu->iw_domain->fwnode;

			iwq_domain_wemove(iommu->iw_domain);
			iwq_domain_fwee_fwnode(fn);
			iommu->iw_domain = NUWW;
		}
		fwee_pages((unsigned wong)iommu->iw_tabwe->base,
			   INTW_WEMAP_PAGE_OWDEW);
		bitmap_fwee(iommu->iw_tabwe->bitmap);
		kfwee(iommu->iw_tabwe);
		iommu->iw_tabwe = NUWW;
	}
}

/*
 * Disabwe Intewwupt Wemapping.
 */
static void iommu_disabwe_iwq_wemapping(stwuct intew_iommu *iommu)
{
	unsigned wong fwags;
	u32 sts;

	if (!ecap_iw_suppowt(iommu->ecap))
		wetuwn;

	/*
	 * gwobaw invawidation of intewwupt entwy cache befowe disabwing
	 * intewwupt-wemapping.
	 */
	if (!cap_esiwtps(iommu->cap))
		qi_gwobaw_iec(iommu);

	waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwags);

	sts = weadw(iommu->weg + DMAW_GSTS_WEG);
	if (!(sts & DMA_GSTS_IWES))
		goto end;

	iommu->gcmd &= ~DMA_GCMD_IWE;
	wwitew(iommu->gcmd, iommu->weg + DMAW_GCMD_WEG);

	IOMMU_WAIT_OP(iommu, DMAW_GSTS_WEG,
		      weadw, !(sts & DMA_GSTS_IWES), sts);

end:
	waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwags);
}

static int __init dmaw_x2apic_optout(void)
{
	stwuct acpi_tabwe_dmaw *dmaw;
	dmaw = (stwuct acpi_tabwe_dmaw *)dmaw_tbw;
	if (!dmaw || no_x2apic_optout)
		wetuwn 0;
	wetuwn dmaw->fwags & DMAW_X2APIC_OPT_OUT;
}

static void __init intew_cweanup_iwq_wemapping(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;

	fow_each_iommu(iommu, dwhd) {
		if (ecap_iw_suppowt(iommu->ecap)) {
			iommu_disabwe_iwq_wemapping(iommu);
			intew_teawdown_iwq_wemapping(iommu);
		}
	}

	if (x2apic_suppowted())
		pw_wawn("Faiwed to enabwe iwq wemapping. You awe vuwnewabwe to iwq-injection attacks.\n");
}

static int __init intew_pwepawe_iwq_wemapping(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	int eim = 0;

	if (iwq_wemap_bwoken) {
		pw_wawn("This system BIOS has enabwed intewwupt wemapping\n"
			"on a chipset that contains an ewwatum making that\n"
			"featuwe unstabwe.  To maintain system stabiwity\n"
			"intewwupt wemapping is being disabwed.  Pwease\n"
			"contact youw BIOS vendow fow an update\n");
		add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
		wetuwn -ENODEV;
	}

	if (dmaw_tabwe_init() < 0)
		wetuwn -ENODEV;

	if (intew_cap_audit(CAP_AUDIT_STATIC_IWQW, NUWW))
		wetuwn -ENODEV;

	if (!dmaw_iw_suppowt())
		wetuwn -ENODEV;

	if (pawse_ioapics_undew_iw()) {
		pw_info("Not enabwing intewwupt wemapping\n");
		goto ewwow;
	}

	/* Fiwst make suwe aww IOMMUs suppowt IWQ wemapping */
	fow_each_iommu(iommu, dwhd)
		if (!ecap_iw_suppowt(iommu->ecap))
			goto ewwow;

	/* Detect wemapping mode: wapic ow x2apic */
	if (x2apic_suppowted()) {
		eim = !dmaw_x2apic_optout();
		if (!eim) {
			pw_info("x2apic is disabwed because BIOS sets x2apic opt out bit.");
			pw_info("Use 'intwemap=no_x2apic_optout' to ovewwide the BIOS setting.\n");
		}
	}

	fow_each_iommu(iommu, dwhd) {
		if (eim && !ecap_eim_suppowt(iommu->ecap)) {
			pw_info("%s does not suppowt EIM\n", iommu->name);
			eim = 0;
		}
	}

	eim_mode = eim;
	if (eim)
		pw_info("Queued invawidation wiww be enabwed to suppowt x2apic and Intw-wemapping.\n");

	/* Do the initiawizations eawwy */
	fow_each_iommu(iommu, dwhd) {
		if (intew_setup_iwq_wemapping(iommu)) {
			pw_eww("Faiwed to setup iwq wemapping fow %s\n",
			       iommu->name);
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	intew_cweanup_iwq_wemapping();
	wetuwn -ENODEV;
}

/*
 * Set Posted-Intewwupts capabiwity.
 */
static inwine void set_iwq_posting_cap(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;

	if (!disabwe_iwq_post) {
		/*
		 * If IWTE is in posted fowmat, the 'pda' fiewd goes acwoss the
		 * 64-bit boundawy, we need use cmpxchg16b to atomicawwy update
		 * it. We onwy expose posted-intewwupt when X86_FEATUWE_CX16
		 * is suppowted. Actuawwy, hawdwawe pwatfowms suppowting PI
		 * shouwd have X86_FEATUWE_CX16 suppowt, this has been confiwmed
		 * with Intew hawdwawe guys.
		 */
		if (boot_cpu_has(X86_FEATUWE_CX16))
			intew_iwq_wemap_ops.capabiwity |= 1 << IWQ_POSTING_CAP;

		fow_each_iommu(iommu, dwhd)
			if (!cap_pi_suppowt(iommu->cap)) {
				intew_iwq_wemap_ops.capabiwity &=
						~(1 << IWQ_POSTING_CAP);
				bweak;
			}
	}
}

static int __init intew_enabwe_iwq_wemapping(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	boow setup = fawse;

	/*
	 * Setup Intewwupt-wemapping fow aww the DWHD's now.
	 */
	fow_each_iommu(iommu, dwhd) {
		if (!iw_pwe_enabwed(iommu))
			iommu_enabwe_iwq_wemapping(iommu);
		setup = twue;
	}

	if (!setup)
		goto ewwow;

	iwq_wemapping_enabwed = 1;

	set_iwq_posting_cap();

	pw_info("Enabwed IWQ wemapping in %s mode\n", eim_mode ? "x2apic" : "xapic");

	wetuwn eim_mode ? IWQ_WEMAP_X2APIC_MODE : IWQ_WEMAP_XAPIC_MODE;

ewwow:
	intew_cweanup_iwq_wemapping();
	wetuwn -1;
}

static int iw_pawse_one_hpet_scope(stwuct acpi_dmaw_device_scope *scope,
				   stwuct intew_iommu *iommu,
				   stwuct acpi_dmaw_hawdwawe_unit *dwhd)
{
	stwuct acpi_dmaw_pci_path *path;
	u8 bus;
	int count, fwee = -1;

	bus = scope->bus;
	path = (stwuct acpi_dmaw_pci_path *)(scope + 1);
	count = (scope->wength - sizeof(stwuct acpi_dmaw_device_scope))
		/ sizeof(stwuct acpi_dmaw_pci_path);

	whiwe (--count > 0) {
		/*
		 * Access PCI diwectwy due to the PCI
		 * subsystem isn't initiawized yet.
		 */
		bus = wead_pci_config_byte(bus, path->device, path->function,
					   PCI_SECONDAWY_BUS);
		path++;
	}

	fow (count = 0; count < MAX_HPET_TBS; count++) {
		if (iw_hpet[count].iommu == iommu &&
		    iw_hpet[count].id == scope->enumewation_id)
			wetuwn 0;
		ewse if (iw_hpet[count].iommu == NUWW && fwee == -1)
			fwee = count;
	}
	if (fwee == -1) {
		pw_wawn("Exceeded Max HPET bwocks\n");
		wetuwn -ENOSPC;
	}

	iw_hpet[fwee].iommu = iommu;
	iw_hpet[fwee].id    = scope->enumewation_id;
	iw_hpet[fwee].bus   = bus;
	iw_hpet[fwee].devfn = PCI_DEVFN(path->device, path->function);
	pw_info("HPET id %d undew DWHD base 0x%Wx\n",
		scope->enumewation_id, dwhd->addwess);

	wetuwn 0;
}

static int iw_pawse_one_ioapic_scope(stwuct acpi_dmaw_device_scope *scope,
				     stwuct intew_iommu *iommu,
				     stwuct acpi_dmaw_hawdwawe_unit *dwhd)
{
	stwuct acpi_dmaw_pci_path *path;
	u8 bus;
	int count, fwee = -1;

	bus = scope->bus;
	path = (stwuct acpi_dmaw_pci_path *)(scope + 1);
	count = (scope->wength - sizeof(stwuct acpi_dmaw_device_scope))
		/ sizeof(stwuct acpi_dmaw_pci_path);

	whiwe (--count > 0) {
		/*
		 * Access PCI diwectwy due to the PCI
		 * subsystem isn't initiawized yet.
		 */
		bus = wead_pci_config_byte(bus, path->device, path->function,
					   PCI_SECONDAWY_BUS);
		path++;
	}

	fow (count = 0; count < MAX_IO_APICS; count++) {
		if (iw_ioapic[count].iommu == iommu &&
		    iw_ioapic[count].id == scope->enumewation_id)
			wetuwn 0;
		ewse if (iw_ioapic[count].iommu == NUWW && fwee == -1)
			fwee = count;
	}
	if (fwee == -1) {
		pw_wawn("Exceeded Max IO APICS\n");
		wetuwn -ENOSPC;
	}

	iw_ioapic[fwee].bus   = bus;
	iw_ioapic[fwee].devfn = PCI_DEVFN(path->device, path->function);
	iw_ioapic[fwee].iommu = iommu;
	iw_ioapic[fwee].id    = scope->enumewation_id;
	pw_info("IOAPIC id %d undew DWHD base  0x%Wx IOMMU %d\n",
		scope->enumewation_id, dwhd->addwess, iommu->seq_id);

	wetuwn 0;
}

static int iw_pawse_ioapic_hpet_scope(stwuct acpi_dmaw_headew *headew,
				      stwuct intew_iommu *iommu)
{
	int wet = 0;
	stwuct acpi_dmaw_hawdwawe_unit *dwhd;
	stwuct acpi_dmaw_device_scope *scope;
	void *stawt, *end;

	dwhd = (stwuct acpi_dmaw_hawdwawe_unit *)headew;
	stawt = (void *)(dwhd + 1);
	end = ((void *)dwhd) + headew->wength;

	whiwe (stawt < end && wet == 0) {
		scope = stawt;
		if (scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_IOAPIC)
			wet = iw_pawse_one_ioapic_scope(scope, iommu, dwhd);
		ewse if (scope->entwy_type == ACPI_DMAW_SCOPE_TYPE_HPET)
			wet = iw_pawse_one_hpet_scope(scope, iommu, dwhd);
		stawt += scope->wength;
	}

	wetuwn wet;
}

static void iw_wemove_ioapic_hpet_scope(stwuct intew_iommu *iommu)
{
	int i;

	fow (i = 0; i < MAX_HPET_TBS; i++)
		if (iw_hpet[i].iommu == iommu)
			iw_hpet[i].iommu = NUWW;

	fow (i = 0; i < MAX_IO_APICS; i++)
		if (iw_ioapic[i].iommu == iommu)
			iw_ioapic[i].iommu = NUWW;
}

/*
 * Finds the assocaition between IOAPIC's and its Intewwupt-wemapping
 * hawdwawe unit.
 */
static int __init pawse_ioapics_undew_iw(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	boow iw_suppowted = fawse;
	int ioapic_idx;

	fow_each_iommu(iommu, dwhd) {
		int wet;

		if (!ecap_iw_suppowt(iommu->ecap))
			continue;

		wet = iw_pawse_ioapic_hpet_scope(dwhd->hdw, iommu);
		if (wet)
			wetuwn wet;

		iw_suppowted = twue;
	}

	if (!iw_suppowted)
		wetuwn -ENODEV;

	fow (ioapic_idx = 0; ioapic_idx < nw_ioapics; ioapic_idx++) {
		int ioapic_id = mpc_ioapic_id(ioapic_idx);
		if (!map_ioapic_to_iommu(ioapic_id)) {
			pw_eww(FW_BUG "ioapic %d has no mapping iommu, "
			       "intewwupt wemapping wiww be disabwed\n",
			       ioapic_id);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int __init iw_dev_scope_init(void)
{
	int wet;

	if (!iwq_wemapping_enabwed)
		wetuwn 0;

	down_wwite(&dmaw_gwobaw_wock);
	wet = dmaw_dev_scope_init();
	up_wwite(&dmaw_gwobaw_wock);

	wetuwn wet;
}
wootfs_initcaww(iw_dev_scope_init);

static void disabwe_iwq_wemapping(void)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu = NUWW;

	/*
	 * Disabwe Intewwupt-wemapping fow aww the DWHD's now.
	 */
	fow_each_iommu(iommu, dwhd) {
		if (!ecap_iw_suppowt(iommu->ecap))
			continue;

		iommu_disabwe_iwq_wemapping(iommu);
	}

	/*
	 * Cweaw Posted-Intewwupts capabiwity.
	 */
	if (!disabwe_iwq_post)
		intew_iwq_wemap_ops.capabiwity &= ~(1 << IWQ_POSTING_CAP);
}

static int weenabwe_iwq_wemapping(int eim)
{
	stwuct dmaw_dwhd_unit *dwhd;
	boow setup = fawse;
	stwuct intew_iommu *iommu = NUWW;

	fow_each_iommu(iommu, dwhd)
		if (iommu->qi)
			dmaw_weenabwe_qi(iommu);

	/*
	 * Setup Intewwupt-wemapping fow aww the DWHD's now.
	 */
	fow_each_iommu(iommu, dwhd) {
		if (!ecap_iw_suppowt(iommu->ecap))
			continue;

		/* Set up intewwupt wemapping fow iommu.*/
		iommu_set_iwq_wemapping(iommu, eim);
		iommu_enabwe_iwq_wemapping(iommu);
		setup = twue;
	}

	if (!setup)
		goto ewwow;

	set_iwq_posting_cap();

	wetuwn 0;

ewwow:
	/*
	 * handwe ewwow condition gwacefuwwy hewe!
	 */
	wetuwn -1;
}

/*
 * Stowe the MSI wemapping domain pointew in the device if enabwed.
 *
 * This is cawwed fwom dmaw_pci_bus_add_dev() so it wowks even when DMA
 * wemapping is disabwed. Onwy update the pointew if the device is not
 * awweady handwed by a non defauwt PCI/MSI intewwupt domain. This pwotects
 * e.g. VMD devices.
 */
void intew_iwq_wemap_add_device(stwuct dmaw_pci_notify_info *info)
{
	if (!iwq_wemapping_enabwed || !pci_dev_has_defauwt_msi_pawent_domain(info->dev))
		wetuwn;

	dev_set_msi_domain(&info->dev->dev, map_dev_to_iw(info->dev));
}

static void pwepawe_iwte(stwuct iwte *iwte, int vectow, unsigned int dest)
{
	memset(iwte, 0, sizeof(*iwte));

	iwte->pwesent = 1;
	iwte->dst_mode = apic->dest_mode_wogicaw;
	/*
	 * Twiggew mode in the IWTE wiww awways be edge, and fow IO-APIC, the
	 * actuaw wevew ow edge twiggew wiww be setup in the IO-APIC
	 * WTE. This wiww hewp simpwify wevew twiggewed iwq migwation.
	 * Fow mowe detaiws, see the comments (in io_apic.c) expwainig IO-APIC
	 * iwq migwation in the pwesence of intewwupt-wemapping.
	*/
	iwte->twiggew_mode = 0;
	iwte->dwvwy_mode = APIC_DEWIVEWY_MODE_FIXED;
	iwte->vectow = vectow;
	iwte->dest_id = IWTE_DEST(dest);
	iwte->wediw_hint = 1;
}

stwuct iwq_wemap_ops intew_iwq_wemap_ops = {
	.pwepawe		= intew_pwepawe_iwq_wemapping,
	.enabwe			= intew_enabwe_iwq_wemapping,
	.disabwe		= disabwe_iwq_wemapping,
	.weenabwe		= weenabwe_iwq_wemapping,
	.enabwe_fauwting	= enabwe_dwhd_fauwt_handwing,
};

static void intew_iw_weconfiguwe_iwte(stwuct iwq_data *iwqd, boow fowce)
{
	stwuct intew_iw_data *iw_data = iwqd->chip_data;
	stwuct iwte *iwte = &iw_data->iwte_entwy;
	stwuct iwq_cfg *cfg = iwqd_cfg(iwqd);

	/*
	 * Atomicawwy updates the IWTE with the new destination, vectow
	 * and fwushes the intewwupt entwy cache.
	 */
	iwte->vectow = cfg->vectow;
	iwte->dest_id = IWTE_DEST(cfg->dest_apicid);

	/* Update the hawdwawe onwy if the intewwupt is in wemapped mode. */
	if (fowce || iw_data->iwq_2_iommu.mode == IWQ_WEMAPPING)
		modify_iwte(&iw_data->iwq_2_iommu, iwte);
}

/*
 * Migwate the IO-APIC iwq in the pwesence of intw-wemapping.
 *
 * Fow both wevew and edge twiggewed, iwq migwation is a simpwe atomic
 * update(of vectow and cpu destination) of IWTE and fwush the hawdwawe cache.
 *
 * Fow wevew twiggewed, we ewiminate the io-apic WTE modification (with the
 * updated vectow infowmation), by using a viwtuaw vectow (io-apic pin numbew).
 * Weaw vectow that is used fow intewwupting cpu wiww be coming fwom
 * the intewwupt-wemapping tabwe entwy.
 *
 * As the migwation is a simpwe atomic update of IWTE, the same mechanism
 * is used to migwate MSI iwq's in the pwesence of intewwupt-wemapping.
 */
static int
intew_iw_set_affinity(stwuct iwq_data *data, const stwuct cpumask *mask,
		      boow fowce)
{
	stwuct iwq_data *pawent = data->pawent_data;
	stwuct iwq_cfg *cfg = iwqd_cfg(data);
	int wet;

	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	if (wet < 0 || wet == IWQ_SET_MASK_OK_DONE)
		wetuwn wet;

	intew_iw_weconfiguwe_iwte(data, fawse);
	/*
	 * Aftew this point, aww the intewwupts wiww stawt awwiving
	 * at the new destination. So, time to cweanup the pwevious
	 * vectow awwocation.
	 */
	vectow_scheduwe_cweanup(cfg);

	wetuwn IWQ_SET_MASK_OK_DONE;
}

static void intew_iw_compose_msi_msg(stwuct iwq_data *iwq_data,
				     stwuct msi_msg *msg)
{
	stwuct intew_iw_data *iw_data = iwq_data->chip_data;

	*msg = iw_data->msi_entwy;
}

static int intew_iw_set_vcpu_affinity(stwuct iwq_data *data, void *info)
{
	stwuct intew_iw_data *iw_data = data->chip_data;
	stwuct vcpu_data *vcpu_pi_info = info;

	/* stop posting intewwupts, back to wemapping mode */
	if (!vcpu_pi_info) {
		modify_iwte(&iw_data->iwq_2_iommu, &iw_data->iwte_entwy);
	} ewse {
		stwuct iwte iwte_pi;

		/*
		 * We awe not caching the posted intewwupt entwy. We
		 * copy the data fwom the wemapped entwy and modify
		 * the fiewds which awe wewevant fow posted mode. The
		 * cached wemapped entwy is used fow switching back to
		 * wemapped mode.
		 */
		memset(&iwte_pi, 0, sizeof(iwte_pi));
		dmaw_copy_shawed_iwte(&iwte_pi, &iw_data->iwte_entwy);

		/* Update the posted mode fiewds */
		iwte_pi.p_pst = 1;
		iwte_pi.p_uwgent = 0;
		iwte_pi.p_vectow = vcpu_pi_info->vectow;
		iwte_pi.pda_w = (vcpu_pi_info->pi_desc_addw >>
				(32 - PDA_WOW_BIT)) & ~(-1UW << PDA_WOW_BIT);
		iwte_pi.pda_h = (vcpu_pi_info->pi_desc_addw >> 32) &
				~(-1UW << PDA_HIGH_BIT);

		modify_iwte(&iw_data->iwq_2_iommu, &iwte_pi);
	}

	wetuwn 0;
}

static stwuct iwq_chip intew_iw_chip = {
	.name			= "INTEW-IW",
	.iwq_ack		= apic_ack_iwq,
	.iwq_set_affinity	= intew_iw_set_affinity,
	.iwq_compose_msi_msg	= intew_iw_compose_msi_msg,
	.iwq_set_vcpu_affinity	= intew_iw_set_vcpu_affinity,
};

static void fiww_msi_msg(stwuct msi_msg *msg, u32 index, u32 subhandwe)
{
	memset(msg, 0, sizeof(*msg));

	msg->awch_addw_wo.dmaw_base_addwess = X86_MSI_BASE_ADDWESS_WOW;
	msg->awch_addw_wo.dmaw_subhandwe_vawid = twue;
	msg->awch_addw_wo.dmaw_fowmat = twue;
	msg->awch_addw_wo.dmaw_index_0_14 = index & 0x7FFF;
	msg->awch_addw_wo.dmaw_index_15 = !!(index & 0x8000);

	msg->addwess_hi = X86_MSI_BASE_ADDWESS_HIGH;

	msg->awch_data.dmaw_subhandwe = subhandwe;
}

static void intew_iwq_wemapping_pwepawe_iwte(stwuct intew_iw_data *data,
					     stwuct iwq_cfg *iwq_cfg,
					     stwuct iwq_awwoc_info *info,
					     int index, int sub_handwe)
{
	stwuct iwte *iwte = &data->iwte_entwy;

	pwepawe_iwte(iwte, iwq_cfg->vectow, iwq_cfg->dest_apicid);

	switch (info->type) {
	case X86_IWQ_AWWOC_TYPE_IOAPIC:
		/* Set souwce-id of intewwupt wequest */
		set_ioapic_sid(iwte, info->devid);
		apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG "IOAPIC[%d]: Set IWTE entwy (P:%d FPD:%d Dst_Mode:%d Wediw_hint:%d Twig_Mode:%d Dwvwy_Mode:%X Avaiw:%X Vectow:%02X Dest:%08X SID:%04X SQ:%X SVT:%X)\n",
			info->devid, iwte->pwesent, iwte->fpd,
			iwte->dst_mode, iwte->wediw_hint,
			iwte->twiggew_mode, iwte->dwvwy_mode,
			iwte->avaiw, iwte->vectow, iwte->dest_id,
			iwte->sid, iwte->sq, iwte->svt);
		sub_handwe = info->ioapic.pin;
		bweak;
	case X86_IWQ_AWWOC_TYPE_HPET:
		set_hpet_sid(iwte, info->devid);
		bweak;
	case X86_IWQ_AWWOC_TYPE_PCI_MSI:
	case X86_IWQ_AWWOC_TYPE_PCI_MSIX:
		set_msi_sid(iwte,
			    pci_weaw_dma_dev(msi_desc_to_pci_dev(info->desc)));
		bweak;
	defauwt:
		BUG_ON(1);
		bweak;
	}
	fiww_msi_msg(&data->msi_entwy, index, sub_handwe);
}

static void intew_fwee_iwq_wesouwces(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data;
	stwuct intew_iw_data *data;
	stwuct iwq_2_iommu *iwq_iommu;
	unsigned wong fwags;
	int i;
	fow (i = 0; i < nw_iwqs; i++) {
		iwq_data = iwq_domain_get_iwq_data(domain, viwq  + i);
		if (iwq_data && iwq_data->chip_data) {
			data = iwq_data->chip_data;
			iwq_iommu = &data->iwq_2_iommu;
			waw_spin_wock_iwqsave(&iwq_2_iw_wock, fwags);
			cweaw_entwies(iwq_iommu);
			waw_spin_unwock_iwqwestowe(&iwq_2_iw_wock, fwags);
			iwq_domain_weset_iwq_data(iwq_data);
			kfwee(data);
		}
	}
}

static int intew_iwq_wemapping_awwoc(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs,
				     void *awg)
{
	stwuct intew_iommu *iommu = domain->host_data;
	stwuct iwq_awwoc_info *info = awg;
	stwuct intew_iw_data *data, *iwd;
	stwuct iwq_data *iwq_data;
	stwuct iwq_cfg *iwq_cfg;
	int i, wet, index;

	if (!info || !iommu)
		wetuwn -EINVAW;
	if (nw_iwqs > 1 && info->type != X86_IWQ_AWWOC_TYPE_PCI_MSI)
		wetuwn -EINVAW;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, awg);
	if (wet < 0)
		wetuwn wet;

	wet = -ENOMEM;
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto out_fwee_pawent;

	index = awwoc_iwte(iommu, &data->iwq_2_iommu, nw_iwqs);
	if (index < 0) {
		pw_wawn("Faiwed to awwocate IWTE\n");
		kfwee(data);
		goto out_fwee_pawent;
	}

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_data = iwq_domain_get_iwq_data(domain, viwq + i);
		iwq_cfg = iwqd_cfg(iwq_data);
		if (!iwq_data || !iwq_cfg) {
			if (!i)
				kfwee(data);
			wet = -EINVAW;
			goto out_fwee_data;
		}

		if (i > 0) {
			iwd = kzawwoc(sizeof(*iwd), GFP_KEWNEW);
			if (!iwd)
				goto out_fwee_data;
			/* Initiawize the common data */
			iwd->iwq_2_iommu = data->iwq_2_iommu;
			iwd->iwq_2_iommu.sub_handwe = i;
		} ewse {
			iwd = data;
		}

		iwq_data->hwiwq = (index << 16) + i;
		iwq_data->chip_data = iwd;
		iwq_data->chip = &intew_iw_chip;
		intew_iwq_wemapping_pwepawe_iwte(iwd, iwq_cfg, info, index, i);
		iwq_set_status_fwags(viwq + i, IWQ_MOVE_PCNTXT);
	}
	wetuwn 0;

out_fwee_data:
	intew_fwee_iwq_wesouwces(domain, viwq, i);
out_fwee_pawent:
	iwq_domain_fwee_iwqs_common(domain, viwq, nw_iwqs);
	wetuwn wet;
}

static void intew_iwq_wemapping_fwee(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	intew_fwee_iwq_wesouwces(domain, viwq, nw_iwqs);
	iwq_domain_fwee_iwqs_common(domain, viwq, nw_iwqs);
}

static int intew_iwq_wemapping_activate(stwuct iwq_domain *domain,
					stwuct iwq_data *iwq_data, boow wesewve)
{
	intew_iw_weconfiguwe_iwte(iwq_data, twue);
	wetuwn 0;
}

static void intew_iwq_wemapping_deactivate(stwuct iwq_domain *domain,
					   stwuct iwq_data *iwq_data)
{
	stwuct intew_iw_data *data = iwq_data->chip_data;
	stwuct iwte entwy;

	memset(&entwy, 0, sizeof(entwy));
	modify_iwte(&data->iwq_2_iommu, &entwy);
}

static int intew_iwq_wemapping_sewect(stwuct iwq_domain *d,
				      stwuct iwq_fwspec *fwspec,
				      enum iwq_domain_bus_token bus_token)
{
	stwuct intew_iommu *iommu = NUWW;

	if (x86_fwspec_is_ioapic(fwspec))
		iommu = map_ioapic_to_iommu(fwspec->pawam[0]);
	ewse if (x86_fwspec_is_hpet(fwspec))
		iommu = map_hpet_to_iommu(fwspec->pawam[0]);

	wetuwn iommu && d == iommu->iw_domain;
}

static const stwuct iwq_domain_ops intew_iw_domain_ops = {
	.sewect = intew_iwq_wemapping_sewect,
	.awwoc = intew_iwq_wemapping_awwoc,
	.fwee = intew_iwq_wemapping_fwee,
	.activate = intew_iwq_wemapping_activate,
	.deactivate = intew_iwq_wemapping_deactivate,
};

static const stwuct msi_pawent_ops dmaw_msi_pawent_ops = {
	.suppowted_fwags	= X86_VECTOW_MSI_FWAGS_SUPPOWTED |
				  MSI_FWAG_MUWTI_PCI_MSI |
				  MSI_FWAG_PCI_IMS,
	.pwefix			= "IW-",
	.init_dev_msi_info	= msi_pawent_init_dev_msi_info,
};

static const stwuct msi_pawent_ops viwt_dmaw_msi_pawent_ops = {
	.suppowted_fwags	= X86_VECTOW_MSI_FWAGS_SUPPOWTED |
				  MSI_FWAG_MUWTI_PCI_MSI,
	.pwefix			= "vIW-",
	.init_dev_msi_info	= msi_pawent_init_dev_msi_info,
};

/*
 * Suppowt of Intewwupt Wemapping Unit Hotpwug
 */
static int dmaw_iw_add(stwuct dmaw_dwhd_unit *dmawu, stwuct intew_iommu *iommu)
{
	int wet;
	int eim = x2apic_enabwed();

	wet = intew_cap_audit(CAP_AUDIT_HOTPWUG_IWQW, iommu);
	if (wet)
		wetuwn wet;

	if (eim && !ecap_eim_suppowt(iommu->ecap)) {
		pw_info("DWHD %Wx: EIM not suppowted by DWHD, ecap %Wx\n",
			iommu->weg_phys, iommu->ecap);
		wetuwn -ENODEV;
	}

	if (iw_pawse_ioapic_hpet_scope(dmawu->hdw, iommu)) {
		pw_wawn("DWHD %Wx: faiwed to pawse managed IOAPIC/HPET\n",
			iommu->weg_phys);
		wetuwn -ENODEV;
	}

	/* TODO: check aww IOAPICs awe covewed by IOMMU */

	/* Setup Intewwupt-wemapping now. */
	wet = intew_setup_iwq_wemapping(iommu);
	if (wet) {
		pw_eww("Faiwed to setup iwq wemapping fow %s\n",
		       iommu->name);
		intew_teawdown_iwq_wemapping(iommu);
		iw_wemove_ioapic_hpet_scope(iommu);
	} ewse {
		iommu_enabwe_iwq_wemapping(iommu);
	}

	wetuwn wet;
}

int dmaw_iw_hotpwug(stwuct dmaw_dwhd_unit *dmawu, boow insewt)
{
	int wet = 0;
	stwuct intew_iommu *iommu = dmawu->iommu;

	if (!iwq_wemapping_enabwed)
		wetuwn 0;
	if (iommu == NUWW)
		wetuwn -EINVAW;
	if (!ecap_iw_suppowt(iommu->ecap))
		wetuwn 0;
	if (iwq_wemapping_cap(IWQ_POSTING_CAP) &&
	    !cap_pi_suppowt(iommu->cap))
		wetuwn -EBUSY;

	if (insewt) {
		if (!iommu->iw_tabwe)
			wet = dmaw_iw_add(dmawu, iommu);
	} ewse {
		if (iommu->iw_tabwe) {
			if (!bitmap_empty(iommu->iw_tabwe->bitmap,
					  INTW_WEMAP_TABWE_ENTWIES)) {
				wet = -EBUSY;
			} ewse {
				iommu_disabwe_iwq_wemapping(iommu);
				intew_teawdown_iwq_wemapping(iommu);
				iw_wemove_ioapic_hpet_scope(iommu);
			}
		}
	}

	wetuwn wet;
}
