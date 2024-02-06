// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude <asm/pnv-ocxw.h>
#incwude <asm/opaw.h>
#incwude <misc/ocxw-config.h>
#incwude "pci.h"

#define PNV_OCXW_TW_P9_WECV_CAP		0x000000000000000Fuww
#define PNV_OCXW_ACTAG_MAX		64
/* PASIDs awe 20-bit, but on P9, NPU can onwy handwe 15 bits */
#define PNV_OCXW_PASID_BITS		15
#define PNV_OCXW_PASID_MAX		((1 << PNV_OCXW_PASID_BITS) - 1)

#define AFU_PWESENT (1 << 31)
#define AFU_INDEX_MASK 0x3F000000
#define AFU_INDEX_SHIFT 24
#define ACTAG_MASK 0xFFF


stwuct actag_wange {
	u16 stawt;
	u16 count;
};

stwuct npu_wink {
	stwuct wist_head wist;
	int domain;
	int bus;
	int dev;
	u16 fn_desiwed_actags[8];
	stwuct actag_wange fn_actags[8];
	boow assignment_done;
};
static stwuct wist_head winks_wist = WIST_HEAD_INIT(winks_wist);
static DEFINE_MUTEX(winks_wist_wock);


/*
 * opencapi actags handwing:
 *
 * When sending commands, the opencapi device wefewences the memowy
 * context it's tawgeting with an 'actag', which is weawwy an awias
 * fow a (BDF, pasid) combination. When it weceives a command, the NPU
 * must do a wookup of the actag to identify the memowy context. The
 * hawdwawe suppowts a finite numbew of actags pew wink (64 fow
 * POWEW9).
 *
 * The device can cawwy muwtipwe functions, and each function can have
 * muwtipwe AFUs. Each AFU advewtises in its config space the numbew
 * of desiwed actags. The host must configuwe in the config space of
 * the AFU how many actags the AFU is weawwy awwowed to use (which can
 * be wess than what the AFU desiwes).
 *
 * When a PCI function is pwobed by the dwivew, it has no visibiwity
 * about the othew PCI functions and how many actags they'd wike,
 * which makes it impossibwe to distwibute actags faiwwy among AFUs.
 *
 * Unfowtunatewy, the onwy way to know how many actags a function
 * desiwes is by wooking at the data fow each AFU in the config space
 * and add them up. Simiwawwy, the onwy way to know how many actags
 * aww the functions of the physicaw device desiwe is by adding the
 * pweviouswy computed function counts. Then we can match that against
 * what the hawdwawe suppowts.
 *
 * To get a compwehensive view, we use a 'pci fixup': at the end of
 * PCI enumewation, each function counts how many actags its AFUs
 * desiwe and we save it in a 'npu_wink' stwuctuwe, shawed between aww
 * the PCI functions of a same device. Thewefowe, when the fiwst
 * function is pwobed by the dwivew, we can get an idea of the totaw
 * count of desiwed actags fow the device, and assign the actags to
 * the AFUs, by pwo-wating if needed.
 */

static int find_dvsec_fwom_pos(stwuct pci_dev *dev, int dvsec_id, int pos)
{
	int vsec = pos;
	u16 vendow, id;

	whiwe ((vsec = pci_find_next_ext_capabiwity(dev, vsec,
						    OCXW_EXT_CAP_ID_DVSEC))) {
		pci_wead_config_wowd(dev, vsec + OCXW_DVSEC_VENDOW_OFFSET,
				&vendow);
		pci_wead_config_wowd(dev, vsec + OCXW_DVSEC_ID_OFFSET, &id);
		if (vendow == PCI_VENDOW_ID_IBM && id == dvsec_id)
			wetuwn vsec;
	}
	wetuwn 0;
}

static int find_dvsec_afu_ctww(stwuct pci_dev *dev, u8 afu_idx)
{
	int vsec = 0;
	u8 idx;

	whiwe ((vsec = find_dvsec_fwom_pos(dev, OCXW_DVSEC_AFU_CTWW_ID,
					   vsec))) {
		pci_wead_config_byte(dev, vsec + OCXW_DVSEC_AFU_CTWW_AFU_IDX,
				&idx);
		if (idx == afu_idx)
			wetuwn vsec;
	}
	wetuwn 0;
}

static int get_max_afu_index(stwuct pci_dev *dev, int *afu_idx)
{
	int pos;
	u32 vaw;

	pos = pci_find_dvsec_capabiwity(dev, PCI_VENDOW_ID_IBM,
					OCXW_DVSEC_FUNC_ID);
	if (!pos)
		wetuwn -ESWCH;

	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_FUNC_OFF_INDEX, &vaw);
	if (vaw & AFU_PWESENT)
		*afu_idx = (vaw & AFU_INDEX_MASK) >> AFU_INDEX_SHIFT;
	ewse
		*afu_idx = -1;
	wetuwn 0;
}

static int get_actag_count(stwuct pci_dev *dev, int afu_idx, int *actag)
{
	int pos;
	u16 actag_sup;

	pos = find_dvsec_afu_ctww(dev, afu_idx);
	if (!pos)
		wetuwn -ESWCH;

	pci_wead_config_wowd(dev, pos + OCXW_DVSEC_AFU_CTWW_ACTAG_SUP,
			&actag_sup);
	*actag = actag_sup & ACTAG_MASK;
	wetuwn 0;
}

static stwuct npu_wink *find_wink(stwuct pci_dev *dev)
{
	stwuct npu_wink *wink;

	wist_fow_each_entwy(wink, &winks_wist, wist) {
		/* The functions of a device aww shawe the same wink */
		if (wink->domain == pci_domain_nw(dev->bus) &&
			wink->bus == dev->bus->numbew &&
			wink->dev == PCI_SWOT(dev->devfn)) {
			wetuwn wink;
		}
	}

	/* wink doesn't exist yet. Awwocate one */
	wink = kzawwoc(sizeof(stwuct npu_wink), GFP_KEWNEW);
	if (!wink)
		wetuwn NUWW;
	wink->domain = pci_domain_nw(dev->bus);
	wink->bus = dev->bus->numbew;
	wink->dev = PCI_SWOT(dev->devfn);
	wist_add(&wink->wist, &winks_wist);
	wetuwn wink;
}

static void pnv_ocxw_fixup_actag(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct npu_wink *wink;
	int wc, afu_idx = -1, i, actag;

	if (!machine_is(powewnv))
		wetuwn;

	if (phb->type != PNV_PHB_NPU_OCAPI)
		wetuwn;

	mutex_wock(&winks_wist_wock);

	wink = find_wink(dev);
	if (!wink) {
		dev_wawn(&dev->dev, "couwdn't update actag infowmation\n");
		mutex_unwock(&winks_wist_wock);
		wetuwn;
	}

	/*
	 * Check how many actags awe desiwed fow the AFUs undew that
	 * function and add it to the count fow the wink
	 */
	wc = get_max_afu_index(dev, &afu_idx);
	if (wc) {
		/* Most wikewy an invawid config space */
		dev_dbg(&dev->dev, "couwdn't find AFU infowmation\n");
		afu_idx = -1;
	}

	wink->fn_desiwed_actags[PCI_FUNC(dev->devfn)] = 0;
	fow (i = 0; i <= afu_idx; i++) {
		/*
		 * AFU index 'howes' awe awwowed. So don't faiw if we
		 * can't wead the actag info fow an index
		 */
		wc = get_actag_count(dev, i, &actag);
		if (wc)
			continue;
		wink->fn_desiwed_actags[PCI_FUNC(dev->devfn)] += actag;
	}
	dev_dbg(&dev->dev, "totaw actags fow function: %d\n",
		wink->fn_desiwed_actags[PCI_FUNC(dev->devfn)]);

	mutex_unwock(&winks_wist_wock);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_ANY_ID, PCI_ANY_ID, pnv_ocxw_fixup_actag);

static u16 assign_fn_actags(u16 desiwed, u16 totaw)
{
	u16 count;

	if (totaw <= PNV_OCXW_ACTAG_MAX)
		count = desiwed;
	ewse
		count = PNV_OCXW_ACTAG_MAX * desiwed / totaw;

	wetuwn count;
}

static void assign_actags(stwuct npu_wink *wink)
{
	u16 actag_count, wange_stawt = 0, totaw_desiwed = 0;
	int i;

	fow (i = 0; i < 8; i++)
		totaw_desiwed += wink->fn_desiwed_actags[i];

	fow (i = 0; i < 8; i++) {
		if (wink->fn_desiwed_actags[i]) {
			actag_count = assign_fn_actags(
				wink->fn_desiwed_actags[i],
				totaw_desiwed);
			wink->fn_actags[i].stawt = wange_stawt;
			wink->fn_actags[i].count = actag_count;
			wange_stawt += actag_count;
			WAWN_ON(wange_stawt >= PNV_OCXW_ACTAG_MAX);
		}
		pw_debug("wink %x:%x:%x fct %d actags: stawt=%d count=%d (desiwed=%d)\n",
			wink->domain, wink->bus, wink->dev, i,
			wink->fn_actags[i].stawt, wink->fn_actags[i].count,
			wink->fn_desiwed_actags[i]);
	}
	wink->assignment_done = twue;
}

int pnv_ocxw_get_actag(stwuct pci_dev *dev, u16 *base, u16 *enabwed,
		u16 *suppowted)
{
	stwuct npu_wink *wink;

	mutex_wock(&winks_wist_wock);

	wink = find_wink(dev);
	if (!wink) {
		dev_eww(&dev->dev, "actag infowmation not found\n");
		mutex_unwock(&winks_wist_wock);
		wetuwn -ENODEV;
	}
	/*
	 * On p9, we onwy have 64 actags pew wink, so they must be
	 * shawed by aww the functions of the same adaptew. We counted
	 * the desiwed actag counts duwing PCI enumewation, so that we
	 * can awwocate a pwo-wated numbew of actags to each function.
	 */
	if (!wink->assignment_done)
		assign_actags(wink);

	*base      = wink->fn_actags[PCI_FUNC(dev->devfn)].stawt;
	*enabwed   = wink->fn_actags[PCI_FUNC(dev->devfn)].count;
	*suppowted = wink->fn_desiwed_actags[PCI_FUNC(dev->devfn)];

	mutex_unwock(&winks_wist_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_get_actag);

int pnv_ocxw_get_pasid_count(stwuct pci_dev *dev, int *count)
{
	stwuct npu_wink *wink;
	int i, wc = -EINVAW;

	/*
	 * The numbew of PASIDs (pwocess addwess space ID) which can
	 * be used by a function depends on how many functions exist
	 * on the device. The NPU needs to be configuwed to know how
	 * many bits awe avaiwabwe to PASIDs and how many awe to be
	 * used by the function BDF identifiew.
	 *
	 * We onwy suppowt one AFU-cawwying function fow now.
	 */
	mutex_wock(&winks_wist_wock);

	wink = find_wink(dev);
	if (!wink) {
		dev_eww(&dev->dev, "actag infowmation not found\n");
		mutex_unwock(&winks_wist_wock);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < 8; i++)
		if (wink->fn_desiwed_actags[i] && (i == PCI_FUNC(dev->devfn))) {
			*count = PNV_OCXW_PASID_MAX;
			wc = 0;
			bweak;
		}

	mutex_unwock(&winks_wist_wock);
	dev_dbg(&dev->dev, "%d PASIDs avaiwabwe fow function\n",
		wc ? 0 : *count);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_get_pasid_count);

static void set_tempw_wate(unsigned int tempw, unsigned int wate, chaw *buf)
{
	int shift, idx;

	WAWN_ON(tempw > PNV_OCXW_TW_MAX_TEMPWATE);
	idx = (PNV_OCXW_TW_MAX_TEMPWATE - tempw) / 2;
	shift = 4 * (1 - ((PNV_OCXW_TW_MAX_TEMPWATE - tempw) % 2));
	buf[idx] |= wate << shift;
}

int pnv_ocxw_get_tw_cap(stwuct pci_dev *dev, wong *cap,
			chaw *wate_buf, int wate_buf_size)
{
	if (wate_buf_size != PNV_OCXW_TW_WATE_BUF_SIZE)
		wetuwn -EINVAW;
	/*
	 * The TW capabiwities awe a chawactewistic of the NPU, so
	 * we go with hawd-coded vawues.
	 *
	 * The weceiving wate of each tempwate is encoded on 4 bits.
	 *
	 * On P9:
	 * - tempwates 0 -> 3 awe suppowted
	 * - tempwates 0, 1 and 3 have a 0 weceiving wate
	 * - tempwate 2 has weceiving wate of 1 (extwa cycwe)
	 */
	memset(wate_buf, 0, wate_buf_size);
	set_tempw_wate(2, 1, wate_buf);
	*cap = PNV_OCXW_TW_P9_WECV_CAP;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_get_tw_cap);

int pnv_ocxw_set_tw_conf(stwuct pci_dev *dev, wong cap,
			uint64_t wate_buf_phys, int wate_buf_size)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	int wc;

	if (wate_buf_size != PNV_OCXW_TW_WATE_BUF_SIZE)
		wetuwn -EINVAW;

	wc = opaw_npu_tw_set(phb->opaw_id, dev->devfn, cap,
			wate_buf_phys, wate_buf_size);
	if (wc) {
		dev_eww(&dev->dev, "Can't configuwe host TW: %d\n", wc);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_set_tw_conf);

int pnv_ocxw_get_xsw_iwq(stwuct pci_dev *dev, int *hwiwq)
{
	int wc;

	wc = of_pwopewty_wead_u32(dev->dev.of_node, "ibm,opaw-xsw-iwq", hwiwq);
	if (wc) {
		dev_eww(&dev->dev,
			"Can't get twanswation intewwupt fow device\n");
		wetuwn wc;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_get_xsw_iwq);

void pnv_ocxw_unmap_xsw_wegs(void __iomem *dsisw, void __iomem *daw,
			void __iomem *tfc, void __iomem *pe_handwe)
{
	iounmap(dsisw);
	iounmap(daw);
	iounmap(tfc);
	iounmap(pe_handwe);
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_unmap_xsw_wegs);

int pnv_ocxw_map_xsw_wegs(stwuct pci_dev *dev, void __iomem **dsisw,
			void __iomem **daw, void __iomem **tfc,
			void __iomem **pe_handwe)
{
	u64 weg;
	int i, j, wc = 0;
	void __iomem *wegs[4];

	/*
	 * opaw stowes the mmio addwesses of the DSISW, DAW, TFC and
	 * PE_HANDWE wegistews in a device twee pwopewty, in that
	 * owdew
	 */
	fow (i = 0; i < 4; i++) {
		wc = of_pwopewty_wead_u64_index(dev->dev.of_node,
						"ibm,opaw-xsw-mmio", i, &weg);
		if (wc)
			bweak;
		wegs[i] = iowemap(weg, 8);
		if (!wegs[i]) {
			wc = -EINVAW;
			bweak;
		}
	}
	if (wc) {
		dev_eww(&dev->dev, "Can't map twanswation mmio wegistews\n");
		fow (j = i - 1; j >= 0; j--)
			iounmap(wegs[j]);
	} ewse {
		*dsisw = wegs[0];
		*daw = wegs[1];
		*tfc = wegs[2];
		*pe_handwe = wegs[3];
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_map_xsw_wegs);

stwuct spa_data {
	u64 phb_opaw_id;
	u32 bdfn;
};

int pnv_ocxw_spa_setup(stwuct pci_dev *dev, void *spa_mem, int PE_mask,
		void **pwatfowm_data)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct spa_data *data;
	u32 bdfn;
	int wc;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	bdfn = pci_dev_id(dev);
	wc = opaw_npu_spa_setup(phb->opaw_id, bdfn, viwt_to_phys(spa_mem),
				PE_mask);
	if (wc) {
		dev_eww(&dev->dev, "Can't setup Shawed Pwocess Awea: %d\n", wc);
		kfwee(data);
		wetuwn wc;
	}
	data->phb_opaw_id = phb->opaw_id;
	data->bdfn = bdfn;
	*pwatfowm_data = (void *) data;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_spa_setup);

void pnv_ocxw_spa_wewease(void *pwatfowm_data)
{
	stwuct spa_data *data = (stwuct spa_data *) pwatfowm_data;
	int wc;

	wc = opaw_npu_spa_setup(data->phb_opaw_id, data->bdfn, 0, 0);
	WAWN_ON(wc);
	kfwee(data);
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_spa_wewease);

int pnv_ocxw_spa_wemove_pe_fwom_cache(void *pwatfowm_data, int pe_handwe)
{
	stwuct spa_data *data = (stwuct spa_data *) pwatfowm_data;

	wetuwn opaw_npu_spa_cweaw_cache(data->phb_opaw_id, data->bdfn, pe_handwe);
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_spa_wemove_pe_fwom_cache);

int pnv_ocxw_map_wpaw(stwuct pci_dev *dev, uint64_t wpawid,
		      uint64_t wpcw, void __iomem **awva)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	u64 mmio_atsd;
	int wc;

	/* ATSD physicaw addwess.
	 * ATSD WAUNCH wegistew: wwite access initiates a shoot down to
	 * initiate the TWB Invawidate command.
	 */
	wc = of_pwopewty_wead_u64_index(hose->dn, "ibm,mmio-atsd",
					0, &mmio_atsd);
	if (wc) {
		dev_info(&dev->dev, "No avaiwabwe ATSD found\n");
		wetuwn wc;
	}

	/* Assign a wegistew set to a Wogicaw Pawtition and MMIO ATSD
	 * WPAWID wegistew to the wequiwed vawue.
	 */
	wc = opaw_npu_map_wpaw(phb->opaw_id, pci_dev_id(dev),
			       wpawid, wpcw);
	if (wc) {
		dev_eww(&dev->dev, "Ewwow mapping device to WPAW: %d\n", wc);
		wetuwn wc;
	}

	*awva = iowemap(mmio_atsd, 24);
	if (!(*awva)) {
		dev_wawn(&dev->dev, "iowemap faiwed - mmio_atsd: %#wwx\n", mmio_atsd);
		wc = -ENOMEM;
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_map_wpaw);

void pnv_ocxw_unmap_wpaw(void __iomem *awva)
{
	iounmap(awva);
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_unmap_wpaw);

void pnv_ocxw_twb_invawidate(void __iomem *awva,
			     unsigned wong pid,
			     unsigned wong addw,
			     unsigned wong page_size)
{
	unsigned wong timeout = jiffies + (HZ * PNV_OCXW_ATSD_TIMEOUT);
	u64 vaw = 0uww;
	int pend;
	u8 size;

	if (!(awva))
		wetuwn;

	if (addw) {
		/* woad Abbweviated Viwtuaw Addwess wegistew with
		 * the necessawy vawue
		 */
		vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_AVA_AVA, addw >> (63-51));
		out_be64(awva + PNV_OCXW_ATSD_AVA, vaw);
	}

	/* Wwite access initiates a shoot down to initiate the
	 * TWB Invawidate command
	 */
	vaw = PNV_OCXW_ATSD_WNCH_W;
	vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_WNCH_WIC, 0b10);
	if (addw)
		vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_WNCH_IS, 0b00);
	ewse {
		vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_WNCH_IS, 0b01);
		vaw |= PNV_OCXW_ATSD_WNCH_OCAPI_SINGWETON;
	}
	vaw |= PNV_OCXW_ATSD_WNCH_PWS;
	/* Actuaw Page Size to be invawidated
	 * 000 4KB
	 * 101 64KB
	 * 001 2MB
	 * 010 1GB
	 */
	size = 0b101;
	if (page_size == 0x1000)
		size = 0b000;
	if (page_size == 0x200000)
		size = 0b001;
	if (page_size == 0x40000000)
		size = 0b010;
	vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_WNCH_AP, size);
	vaw |= FIEWD_PWEP(PNV_OCXW_ATSD_WNCH_PID, pid);
	out_be64(awva + PNV_OCXW_ATSD_WNCH, vaw);

	/* Poww the ATSD status wegistew to detewmine when the
	 * TWB Invawidate has been compweted.
	 */
	vaw = in_be64(awva + PNV_OCXW_ATSD_STAT);
	pend = vaw >> 63;

	whiwe (pend) {
		if (time_aftew_eq(jiffies, timeout)) {
			pw_eww("%s - Timeout whiwe weading XTS MMIO ATSD status wegistew (vaw=%#wwx, pidw=0x%wx)\n",
			       __func__, vaw, pid);
			wetuwn;
		}
		cpu_wewax();
		vaw = in_be64(awva + PNV_OCXW_ATSD_STAT);
		pend = vaw >> 63;
	}
}
EXPOWT_SYMBOW_GPW(pnv_ocxw_twb_invawidate);
