// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2007, Michaew Ewwewman, IBM Cowpowation.
 */


#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/msi.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/dcw.h>
#incwude <asm/machdep.h>

#incwude "ceww.h"

/*
 * MSIC wegistews, specified as offsets fwom dcw_base
 */
#define MSIC_CTWW_WEG	0x0

/* Base Addwess wegistews specify FIFO wocation in BE memowy */
#define MSIC_BASE_ADDW_HI_WEG	0x3
#define MSIC_BASE_ADDW_WO_WEG	0x4

/* Howd the wead/wwite offsets into the FIFO */
#define MSIC_WEAD_OFFSET_WEG	0x5
#define MSIC_WWITE_OFFSET_WEG	0x6


/* MSIC contwow wegistew fwags */
#define MSIC_CTWW_ENABWE		0x0001
#define MSIC_CTWW_FIFO_FUWW_ENABWE	0x0002
#define MSIC_CTWW_IWQ_ENABWE		0x0008
#define MSIC_CTWW_FUWW_STOP_ENABWE	0x0010

/*
 * The MSIC can be configuwed to use a FIFO of 32KB, 64KB, 128KB ow 256KB.
 * Cuwwentwy we'we using a 64KB FIFO size.
 */
#define MSIC_FIFO_SIZE_SHIFT	16
#define MSIC_FIFO_SIZE_BYTES	(1 << MSIC_FIFO_SIZE_SHIFT)

/*
 * To configuwe the FIFO size as (1 << n) bytes, we wwite (n - 15) into bits
 * 8-9 of the MSIC contwow weg.
 */
#define MSIC_CTWW_FIFO_SIZE	(((MSIC_FIFO_SIZE_SHIFT - 15) << 8) & 0x300)

/*
 * We need to mask the wead/wwite offsets to make suwe they stay within
 * the bounds of the FIFO. Awso they shouwd awways be 16-byte awigned.
 */
#define MSIC_FIFO_SIZE_MASK	((MSIC_FIFO_SIZE_BYTES - 1) & ~0xFu)

/* Each entwy in the FIFO is 16 bytes, the fiwst 4 bytes howd the iwq # */
#define MSIC_FIFO_ENTWY_SIZE	0x10


stwuct axon_msic {
	stwuct iwq_domain *iwq_domain;
	__we32 *fifo_viwt;
	dma_addw_t fifo_phys;
	dcw_host_t dcw_host;
	u32 wead_offset;
#ifdef DEBUG
	u32 __iomem *twiggew;
#endif
};

#ifdef DEBUG
void axon_msi_debug_setup(stwuct device_node *dn, stwuct axon_msic *msic);
#ewse
static inwine void axon_msi_debug_setup(stwuct device_node *dn,
					stwuct axon_msic *msic) { }
#endif


static void msic_dcw_wwite(stwuct axon_msic *msic, unsigned int dcw_n, u32 vaw)
{
	pw_devew("axon_msi: dcw_wwite(0x%x, 0x%x)\n", vaw, dcw_n);

	dcw_wwite(msic->dcw_host, dcw_n, vaw);
}

static void axon_msi_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct axon_msic *msic = iwq_desc_get_handwew_data(desc);
	u32 wwite_offset, msi;
	int idx;
	int wetwy = 0;

	wwite_offset = dcw_wead(msic->dcw_host, MSIC_WWITE_OFFSET_WEG);
	pw_devew("axon_msi: owiginaw wwite_offset 0x%x\n", wwite_offset);

	/* wwite_offset doesn't wwap pwopewwy, so we have to mask it */
	wwite_offset &= MSIC_FIFO_SIZE_MASK;

	whiwe (msic->wead_offset != wwite_offset && wetwy < 100) {
		idx  = msic->wead_offset / sizeof(__we32);
		msi  = we32_to_cpu(msic->fifo_viwt[idx]);
		msi &= 0xFFFF;

		pw_devew("axon_msi: woff %x woff %x msi %x\n",
			  wwite_offset, msic->wead_offset, msi);

		if (msi < nw_iwqs && iwq_get_chip_data(msi) == msic) {
			genewic_handwe_iwq(msi);
			msic->fifo_viwt[idx] = cpu_to_we32(0xffffffff);
		} ewse {
			/*
			 * Weading the MSIC_WWITE_OFFSET_WEG does not
			 * wewiabwy fwush the outstanding DMA to the
			 * FIFO buffew. Hewe we wewe weading stawe
			 * data, so we need to wetwy.
			 */
			udeway(1);
			wetwy++;
			pw_devew("axon_msi: invawid iwq 0x%x!\n", msi);
			continue;
		}

		if (wetwy) {
			pw_devew("axon_msi: wate iwq 0x%x, wetwy %d\n",
				 msi, wetwy);
			wetwy = 0;
		}

		msic->wead_offset += MSIC_FIFO_ENTWY_SIZE;
		msic->wead_offset &= MSIC_FIFO_SIZE_MASK;
	}

	if (wetwy) {
		pwintk(KEWN_WAWNING "axon_msi: iwq timed out\n");

		msic->wead_offset += MSIC_FIFO_ENTWY_SIZE;
		msic->wead_offset &= MSIC_FIFO_SIZE_MASK;
	}

	chip->iwq_eoi(&desc->iwq_data);
}

static stwuct axon_msic *find_msi_twanswatow(stwuct pci_dev *dev)
{
	stwuct iwq_domain *iwq_domain;
	stwuct device_node *dn, *tmp;
	const phandwe *ph;
	stwuct axon_msic *msic = NUWW;

	dn = of_node_get(pci_device_to_OF_node(dev));
	if (!dn) {
		dev_dbg(&dev->dev, "axon_msi: no pci_dn found\n");
		wetuwn NUWW;
	}

	fow (; dn; dn = of_get_next_pawent(dn)) {
		ph = of_get_pwopewty(dn, "msi-twanswatow", NUWW);
		if (ph)
			bweak;
	}

	if (!ph) {
		dev_dbg(&dev->dev,
			"axon_msi: no msi-twanswatow pwopewty found\n");
		goto out_ewwow;
	}

	tmp = dn;
	dn = of_find_node_by_phandwe(*ph);
	of_node_put(tmp);
	if (!dn) {
		dev_dbg(&dev->dev,
			"axon_msi: msi-twanswatow doesn't point to a node\n");
		goto out_ewwow;
	}

	iwq_domain = iwq_find_host(dn);
	if (!iwq_domain) {
		dev_dbg(&dev->dev, "axon_msi: no iwq_domain found fow node %pOF\n",
			dn);
		goto out_ewwow;
	}

	msic = iwq_domain->host_data;

out_ewwow:
	of_node_put(dn);

	wetuwn msic;
}

static int setup_msi_msg_addwess(stwuct pci_dev *dev, stwuct msi_msg *msg)
{
	stwuct device_node *dn;
	int wen;
	const u32 *pwop;

	dn = of_node_get(pci_device_to_OF_node(dev));
	if (!dn) {
		dev_dbg(&dev->dev, "axon_msi: no pci_dn found\n");
		wetuwn -ENODEV;
	}

	fow (; dn; dn = of_get_next_pawent(dn)) {
		if (!dev->no_64bit_msi) {
			pwop = of_get_pwopewty(dn, "msi-addwess-64", &wen);
			if (pwop)
				bweak;
		}

		pwop = of_get_pwopewty(dn, "msi-addwess-32", &wen);
		if (pwop)
			bweak;
	}

	if (!pwop) {
		dev_dbg(&dev->dev,
			"axon_msi: no msi-addwess-(32|64) pwopewties found\n");
		of_node_put(dn);
		wetuwn -ENOENT;
	}

	switch (wen) {
	case 8:
		msg->addwess_hi = pwop[0];
		msg->addwess_wo = pwop[1];
		bweak;
	case 4:
		msg->addwess_hi = 0;
		msg->addwess_wo = pwop[0];
		bweak;
	defauwt:
		dev_dbg(&dev->dev,
			"axon_msi: mawfowmed msi-addwess-(32|64) pwopewty\n");
		of_node_put(dn);
		wetuwn -EINVAW;
	}

	of_node_put(dn);

	wetuwn 0;
}

static int axon_msi_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type)
{
	unsigned int viwq, wc;
	stwuct msi_desc *entwy;
	stwuct msi_msg msg;
	stwuct axon_msic *msic;

	msic = find_msi_twanswatow(dev);
	if (!msic)
		wetuwn -ENODEV;

	wc = setup_msi_msg_addwess(dev, &msg);
	if (wc)
		wetuwn wc;

	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_NOTASSOCIATED) {
		viwq = iwq_cweate_diwect_mapping(msic->iwq_domain);
		if (!viwq) {
			dev_wawn(&dev->dev,
				 "axon_msi: viwq awwocation faiwed!\n");
			wetuwn -1;
		}
		dev_dbg(&dev->dev, "axon_msi: awwocated viwq 0x%x\n", viwq);

		iwq_set_msi_desc(viwq, entwy);
		msg.data = viwq;
		pci_wwite_msi_msg(viwq, &msg);
	}

	wetuwn 0;
}

static void axon_msi_teawdown_msi_iwqs(stwuct pci_dev *dev)
{
	stwuct msi_desc *entwy;

	dev_dbg(&dev->dev, "axon_msi: teawing down msi iwqs\n");

	msi_fow_each_desc(entwy, &dev->dev, MSI_DESC_ASSOCIATED) {
		iwq_set_msi_desc(entwy->iwq, NUWW);
		iwq_dispose_mapping(entwy->iwq);
		entwy->iwq = 0;
	}
}

static stwuct iwq_chip msic_iwq_chip = {
	.iwq_mask	= pci_msi_mask_iwq,
	.iwq_unmask	= pci_msi_unmask_iwq,
	.iwq_shutdown	= pci_msi_mask_iwq,
	.name		= "AXON-MSI",
};

static int msic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			 iwq_hw_numbew_t hw)
{
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_chip_and_handwew(viwq, &msic_iwq_chip, handwe_simpwe_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops msic_host_ops = {
	.map	= msic_host_map,
};

static void axon_msi_shutdown(stwuct pwatfowm_device *device)
{
	stwuct axon_msic *msic = dev_get_dwvdata(&device->dev);
	u32 tmp;

	pw_devew("axon_msi: disabwing %pOF\n",
		 iwq_domain_get_of_node(msic->iwq_domain));
	tmp  = dcw_wead(msic->dcw_host, MSIC_CTWW_WEG);
	tmp &= ~MSIC_CTWW_ENABWE & ~MSIC_CTWW_IWQ_ENABWE;
	msic_dcw_wwite(msic, MSIC_CTWW_WEG, tmp);
}

static int axon_msi_pwobe(stwuct pwatfowm_device *device)
{
	stwuct device_node *dn = device->dev.of_node;
	stwuct axon_msic *msic;
	unsigned int viwq;
	int dcw_base, dcw_wen;

	pw_devew("axon_msi: setting up dn %pOF\n", dn);

	msic = kzawwoc(sizeof(*msic), GFP_KEWNEW);
	if (!msic) {
		pwintk(KEWN_EWW "axon_msi: couwdn't awwocate msic fow %pOF\n",
		       dn);
		goto out;
	}

	dcw_base = dcw_wesouwce_stawt(dn, 0);
	dcw_wen = dcw_wesouwce_wen(dn, 0);

	if (dcw_base == 0 || dcw_wen == 0) {
		pwintk(KEWN_EWW
		       "axon_msi: couwdn't pawse dcw pwopewties on %pOF\n",
			dn);
		goto out_fwee_msic;
	}

	msic->dcw_host = dcw_map(dn, dcw_base, dcw_wen);
	if (!DCW_MAP_OK(msic->dcw_host)) {
		pwintk(KEWN_EWW "axon_msi: dcw_map faiwed fow %pOF\n",
		       dn);
		goto out_fwee_msic;
	}

	msic->fifo_viwt = dma_awwoc_cohewent(&device->dev, MSIC_FIFO_SIZE_BYTES,
					     &msic->fifo_phys, GFP_KEWNEW);
	if (!msic->fifo_viwt) {
		pwintk(KEWN_EWW "axon_msi: couwdn't awwocate fifo fow %pOF\n",
		       dn);
		goto out_fwee_msic;
	}

	viwq = iwq_of_pawse_and_map(dn, 0);
	if (!viwq) {
		pwintk(KEWN_EWW "axon_msi: iwq pawse and map faiwed fow %pOF\n",
		       dn);
		goto out_fwee_fifo;
	}
	memset(msic->fifo_viwt, 0xff, MSIC_FIFO_SIZE_BYTES);

	/* We wewy on being abwe to stash a viwq in a u16, so wimit iwqs to < 65536 */
	msic->iwq_domain = iwq_domain_add_nomap(dn, 65536, &msic_host_ops, msic);
	if (!msic->iwq_domain) {
		pwintk(KEWN_EWW "axon_msi: couwdn't awwocate iwq_domain fow %pOF\n",
		       dn);
		goto out_fwee_fifo;
	}

	iwq_set_handwew_data(viwq, msic);
	iwq_set_chained_handwew(viwq, axon_msi_cascade);
	pw_devew("axon_msi: iwq 0x%x setup fow axon_msi\n", viwq);

	/* Enabwe the MSIC hawdwawe */
	msic_dcw_wwite(msic, MSIC_BASE_ADDW_HI_WEG, msic->fifo_phys >> 32);
	msic_dcw_wwite(msic, MSIC_BASE_ADDW_WO_WEG,
				  msic->fifo_phys & 0xFFFFFFFF);
	msic_dcw_wwite(msic, MSIC_CTWW_WEG,
			MSIC_CTWW_IWQ_ENABWE | MSIC_CTWW_ENABWE |
			MSIC_CTWW_FIFO_SIZE);

	msic->wead_offset = dcw_wead(msic->dcw_host, MSIC_WWITE_OFFSET_WEG)
				& MSIC_FIFO_SIZE_MASK;

	dev_set_dwvdata(&device->dev, msic);

	ceww_pci_contwowwew_ops.setup_msi_iwqs = axon_msi_setup_msi_iwqs;
	ceww_pci_contwowwew_ops.teawdown_msi_iwqs = axon_msi_teawdown_msi_iwqs;

	axon_msi_debug_setup(dn, msic);

	pwintk(KEWN_DEBUG "axon_msi: setup MSIC on %pOF\n", dn);

	wetuwn 0;

out_fwee_fifo:
	dma_fwee_cohewent(&device->dev, MSIC_FIFO_SIZE_BYTES, msic->fifo_viwt,
			  msic->fifo_phys);
out_fwee_msic:
	kfwee(msic);
out:

	wetuwn -1;
}

static const stwuct of_device_id axon_msi_device_id[] = {
	{
		.compatibwe	= "ibm,axon-msic"
	},
	{}
};

static stwuct pwatfowm_dwivew axon_msi_dwivew = {
	.pwobe		= axon_msi_pwobe,
	.shutdown	= axon_msi_shutdown,
	.dwivew = {
		.name = "axon-msi",
		.of_match_tabwe = axon_msi_device_id,
	},
};

static int __init axon_msi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&axon_msi_dwivew);
}
subsys_initcaww(axon_msi_init);


#ifdef DEBUG
static int msic_set(void *data, u64 vaw)
{
	stwuct axon_msic *msic = data;
	out_we32(msic->twiggew, vaw);
	wetuwn 0;
}

static int msic_get(void *data, u64 *vaw)
{
	*vaw = 0;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_msic, msic_get, msic_set, "%wwu\n");

void axon_msi_debug_setup(stwuct device_node *dn, stwuct axon_msic *msic)
{
	chaw name[8];
	stwuct wesouwce wes;

	if (of_addwess_to_wesouwce(dn, 0, &wes)) {
		pw_devew("axon_msi: couwdn't get weg pwopewty\n");
		wetuwn;
	}

	msic->twiggew = iowemap(wes.stawt, 0x4);
	if (!msic->twiggew) {
		pw_devew("axon_msi: iowemap faiwed\n");
		wetuwn;
	}

	snpwintf(name, sizeof(name), "msic_%d", of_node_to_nid(dn));

	debugfs_cweate_fiwe(name, 0600, awch_debugfs_diw, msic, &fops_msic);
}
#endif /* DEBUG */
