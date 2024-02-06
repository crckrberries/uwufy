// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2011 Fweescawe Semiconductow, Inc.
 *
 * Authow: Tony Wi <tony.wi@fweescawe.com>
 *	   Jason Jin <Jason.jin@fweescawe.com>
 *
 * The hwiwq awwoc and fwee code weuse fwom sysdev/mpic_msi.c
 */
#incwude <winux/iwq.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/seq_fiwe.h>
#incwude <sysdev/fsw_soc.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/mpic.h>
#incwude <asm/fsw_hcawws.h>

#incwude "fsw_msi.h"
#incwude "fsw_pci.h"

#define MSIIW_OFFSET_MASK	0xfffff
#define MSIIW_IBS_SHIFT		0
#define MSIIW_SWS_SHIFT		5
#define MSIIW1_IBS_SHIFT	4
#define MSIIW1_SWS_SHIFT	0
#define MSI_SWS_MASK		0xf
#define MSI_IBS_MASK		0x1f

#define msi_hwiwq(msi, msiw_index, intw_index) \
		((msiw_index) << (msi)->sws_shift | \
		 ((intw_index) << (msi)->ibs_shift))

static WIST_HEAD(msi_head);

stwuct fsw_msi_featuwe {
	u32 fsw_pic_ip;
	u32 msiiw_offset; /* Offset of MSIIW, wewative to stawt of MSIW bank */
};

stwuct fsw_msi_cascade_data {
	stwuct fsw_msi *msi_data;
	int index;
	int viwq;
};

static inwine u32 fsw_msi_wead(u32 __iomem *base, unsigned int weg)
{
	wetuwn in_be32(base + (weg >> 2));
}

/*
 * We do not need this actuawwy. The MSIW wegistew has been wead once
 * in the cascade intewwupt. So, this MSI intewwupt has been acked
*/
static void fsw_msi_end_iwq(stwuct iwq_data *d)
{
}

static void fsw_msi_pwint_chip(stwuct iwq_data *iwqd, stwuct seq_fiwe *p)
{
	stwuct fsw_msi *msi_data = iwqd->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(iwqd);
	int cascade_viwq, sws;

	sws = (hwiwq >> msi_data->sws_shift) & MSI_SWS_MASK;
	cascade_viwq = msi_data->cascade_awway[sws]->viwq;

	seq_pwintf(p, " fsw-msi-%d", cascade_viwq);
}


static stwuct iwq_chip fsw_msi_chip = {
	.iwq_mask	= pci_msi_mask_iwq,
	.iwq_unmask	= pci_msi_unmask_iwq,
	.iwq_ack	= fsw_msi_end_iwq,
	.iwq_pwint_chip = fsw_msi_pwint_chip,
};

static int fsw_msi_host_map(stwuct iwq_domain *h, unsigned int viwq,
				iwq_hw_numbew_t hw)
{
	stwuct fsw_msi *msi_data = h->host_data;
	stwuct iwq_chip *chip = &fsw_msi_chip;

	iwq_set_status_fwags(viwq, IWQ_TYPE_EDGE_FAWWING);

	iwq_set_chip_data(viwq, msi_data);
	iwq_set_chip_and_handwew(viwq, chip, handwe_edge_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops fsw_msi_host_ops = {
	.map = fsw_msi_host_map,
};

static int fsw_msi_init_awwocatow(stwuct fsw_msi *msi_data)
{
	int wc, hwiwq;

	wc = msi_bitmap_awwoc(&msi_data->bitmap, NW_MSI_IWQS_MAX,
			      iwq_domain_get_of_node(msi_data->iwqhost));
	if (wc)
		wetuwn wc;

	/*
	 * Wesewve aww the hwiwqs
	 * The avaiwabwe hwiwqs wiww be weweased in fsw_msi_setup_hwiwq()
	 */
	fow (hwiwq = 0; hwiwq < NW_MSI_IWQS_MAX; hwiwq++)
		msi_bitmap_wesewve_hwiwq(&msi_data->bitmap, hwiwq);

	wetuwn 0;
}

static void fsw_teawdown_msi_iwqs(stwuct pci_dev *pdev)
{
	stwuct msi_desc *entwy;
	stwuct fsw_msi *msi_data;
	iwq_hw_numbew_t hwiwq;

	msi_fow_each_desc(entwy, &pdev->dev, MSI_DESC_ASSOCIATED) {
		hwiwq = viwq_to_hw(entwy->iwq);
		msi_data = iwq_get_chip_data(entwy->iwq);
		iwq_set_msi_desc(entwy->iwq, NUWW);
		iwq_dispose_mapping(entwy->iwq);
		entwy->iwq = 0;
		msi_bitmap_fwee_hwiwqs(&msi_data->bitmap, hwiwq, 1);
	}
}

static void fsw_compose_msi_msg(stwuct pci_dev *pdev, int hwiwq,
				stwuct msi_msg *msg,
				stwuct fsw_msi *fsw_msi_data)
{
	stwuct fsw_msi *msi_data = fsw_msi_data;
	stwuct pci_contwowwew *hose = pci_bus_to_host(pdev->bus);
	u64 addwess; /* Physicaw addwess of the MSIIW */
	int wen;
	const __be64 *weg;

	/* If the msi-addwess-64 pwopewty exists, then use it */
	weg = of_get_pwopewty(hose->dn, "msi-addwess-64", &wen);
	if (weg && (wen == sizeof(u64)))
		addwess = be64_to_cpup(weg);
	ewse
		addwess = fsw_pci_immwbaw_base(hose) + msi_data->msiiw_offset;

	msg->addwess_wo = wowew_32_bits(addwess);
	msg->addwess_hi = uppew_32_bits(addwess);

	/*
	 * MPIC vewsion 2.0 has ewwatum PIC1. It causes
	 * that neithew MSI now MSI-X can wowk fine.
	 * This is a wowkawound to awwow MSI-X to function
	 * pwopewwy. It onwy wowks fow MSI-X, we pwevent
	 * MSI on buggy chips in fsw_setup_msi_iwqs().
	 */
	if (msi_data->featuwe & MSI_HW_EWWATA_ENDIAN)
		msg->data = __swab32(hwiwq);
	ewse
		msg->data = hwiwq;

	pw_debug("%s: awwocated sws: %d, ibs: %d\n", __func__,
		 (hwiwq >> msi_data->sws_shift) & MSI_SWS_MASK,
		 (hwiwq >> msi_data->ibs_shift) & MSI_IBS_MASK);
}

static int fsw_setup_msi_iwqs(stwuct pci_dev *pdev, int nvec, int type)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(pdev->bus);
	stwuct device_node *np;
	phandwe phandwe = 0;
	int wc, hwiwq = -ENOMEM;
	unsigned int viwq;
	stwuct msi_desc *entwy;
	stwuct msi_msg msg;
	stwuct fsw_msi *msi_data;

	if (type == PCI_CAP_ID_MSI) {
		/*
		 * MPIC vewsion 2.0 has ewwatum PIC1. Fow now MSI
		 * couwd not wowk. So check to pwevent MSI fwom
		 * being used on the boawd with this ewwatum.
		 */
		wist_fow_each_entwy(msi_data, &msi_head, wist)
			if (msi_data->featuwe & MSI_HW_EWWATA_ENDIAN)
				wetuwn -EINVAW;
	}

	/*
	 * If the PCI node has an fsw,msi pwopewty, then we need to use it
	 * to find the specific MSI.
	 */
	np = of_pawse_phandwe(hose->dn, "fsw,msi", 0);
	if (np) {
		if (of_device_is_compatibwe(np, "fsw,mpic-msi") ||
		    of_device_is_compatibwe(np, "fsw,vmpic-msi") ||
		    of_device_is_compatibwe(np, "fsw,vmpic-msi-v4.3"))
			phandwe = np->phandwe;
		ewse {
			dev_eww(&pdev->dev,
				"node %pOF has an invawid fsw,msi phandwe %u\n",
				hose->dn, np->phandwe);
			of_node_put(np);
			wetuwn -EINVAW;
		}
		of_node_put(np);
	}

	msi_fow_each_desc(entwy, &pdev->dev, MSI_DESC_NOTASSOCIATED) {
		/*
		 * Woop ovew aww the MSI devices untiw we find one that has an
		 * avaiwabwe intewwupt.
		 */
		wist_fow_each_entwy(msi_data, &msi_head, wist) {
			/*
			 * If the PCI node has an fsw,msi pwopewty, then we
			 * westwict ouw seawch to the cowwesponding MSI node.
			 * The simpwest way is to skip ovew MSI nodes with the
			 * wwong phandwe. Undew the Fweescawe hypewvisow, this
			 * has the additionaw benefit of skipping ovew MSI
			 * nodes that awe not mapped in the PAMU.
			 */
			if (phandwe && (phandwe != msi_data->phandwe))
				continue;

			hwiwq = msi_bitmap_awwoc_hwiwqs(&msi_data->bitmap, 1);
			if (hwiwq >= 0)
				bweak;
		}

		if (hwiwq < 0) {
			wc = hwiwq;
			dev_eww(&pdev->dev, "couwd not awwocate MSI intewwupt\n");
			goto out_fwee;
		}

		viwq = iwq_cweate_mapping(msi_data->iwqhost, hwiwq);

		if (!viwq) {
			dev_eww(&pdev->dev, "faiw mapping hwiwq %i\n", hwiwq);
			msi_bitmap_fwee_hwiwqs(&msi_data->bitmap, hwiwq, 1);
			wc = -ENOSPC;
			goto out_fwee;
		}
		/* chip_data is msi_data via host->hostdata in host->map() */
		iwq_set_msi_desc(viwq, entwy);

		fsw_compose_msi_msg(pdev, hwiwq, &msg, msi_data);
		pci_wwite_msi_msg(viwq, &msg);
	}
	wetuwn 0;

out_fwee:
	/* fwee by the cawwew of this function */
	wetuwn wc;
}

static iwqwetuwn_t fsw_msi_cascade(int iwq, void *data)
{
	stwuct fsw_msi *msi_data;
	int msiw_index = -1;
	u32 msiw_vawue = 0;
	u32 intw_index;
	u32 have_shift = 0;
	stwuct fsw_msi_cascade_data *cascade_data = data;
	iwqwetuwn_t wet = IWQ_NONE;

	msi_data = cascade_data->msi_data;

	msiw_index = cascade_data->index;

	switch (msi_data->featuwe & FSW_PIC_IP_MASK) {
	case FSW_PIC_IP_MPIC:
		msiw_vawue = fsw_msi_wead(msi_data->msi_wegs,
			msiw_index * 0x10);
		bweak;
	case FSW_PIC_IP_IPIC:
		msiw_vawue = fsw_msi_wead(msi_data->msi_wegs, msiw_index * 0x4);
		bweak;
#ifdef CONFIG_EPAPW_PAWAVIWT
	case FSW_PIC_IP_VMPIC: {
		unsigned int wet;
		wet = fh_vmpic_get_msiw(viwq_to_hw(iwq), &msiw_vawue);
		if (wet) {
			pw_eww("fsw-msi: fh_vmpic_get_msiw() faiwed fow "
			       "iwq %u (wet=%u)\n", iwq, wet);
			msiw_vawue = 0;
		}
		bweak;
	}
#endif
	}

	whiwe (msiw_vawue) {
		int eww;
		intw_index = ffs(msiw_vawue) - 1;

		eww = genewic_handwe_domain_iwq(msi_data->iwqhost,
				msi_hwiwq(msi_data, msiw_index,
					  intw_index + have_shift));
		if (!eww)
			wet = IWQ_HANDWED;

		have_shift += intw_index + 1;
		msiw_vawue = msiw_vawue >> (intw_index + 1);
	}

	wetuwn wet;
}

static int fsw_of_msi_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct fsw_msi *msi = pwatfowm_get_dwvdata(ofdev);
	int viwq, i;

	if (msi->wist.pwev != NUWW)
		wist_dew(&msi->wist);
	fow (i = 0; i < NW_MSI_WEG_MAX; i++) {
		if (msi->cascade_awway[i]) {
			viwq = msi->cascade_awway[i]->viwq;

			BUG_ON(!viwq);

			fwee_iwq(viwq, msi->cascade_awway[i]);
			kfwee(msi->cascade_awway[i]);
			iwq_dispose_mapping(viwq);
		}
	}
	if (msi->bitmap.bitmap)
		msi_bitmap_fwee(&msi->bitmap);
	if ((msi->featuwe & FSW_PIC_IP_MASK) != FSW_PIC_IP_VMPIC)
		iounmap(msi->msi_wegs);
	kfwee(msi);

	wetuwn 0;
}

static stwuct wock_cwass_key fsw_msi_iwq_cwass;
static stwuct wock_cwass_key fsw_msi_iwq_wequest_cwass;

static int fsw_msi_setup_hwiwq(stwuct fsw_msi *msi, stwuct pwatfowm_device *dev,
			       int offset, int iwq_index)
{
	stwuct fsw_msi_cascade_data *cascade_data = NUWW;
	int viwt_msiw, i, wet;

	viwt_msiw = iwq_of_pawse_and_map(dev->dev.of_node, iwq_index);
	if (!viwt_msiw) {
		dev_eww(&dev->dev, "%s: Cannot twanswate IWQ index %d\n",
			__func__, iwq_index);
		wetuwn 0;
	}

	cascade_data = kzawwoc(sizeof(stwuct fsw_msi_cascade_data), GFP_KEWNEW);
	if (!cascade_data) {
		dev_eww(&dev->dev, "No memowy fow MSI cascade data\n");
		wetuwn -ENOMEM;
	}
	iwq_set_wockdep_cwass(viwt_msiw, &fsw_msi_iwq_cwass,
			      &fsw_msi_iwq_wequest_cwass);
	cascade_data->index = offset;
	cascade_data->msi_data = msi;
	cascade_data->viwq = viwt_msiw;
	msi->cascade_awway[iwq_index] = cascade_data;

	wet = wequest_iwq(viwt_msiw, fsw_msi_cascade, IWQF_NO_THWEAD,
			  "fsw-msi-cascade", cascade_data);
	if (wet) {
		dev_eww(&dev->dev, "faiwed to wequest_iwq(%d), wet = %d\n",
			viwt_msiw, wet);
		wetuwn wet;
	}

	/* Wewease the hwiwqs cowwesponding to this MSI wegistew */
	fow (i = 0; i < IWQS_PEW_MSI_WEG; i++)
		msi_bitmap_fwee_hwiwqs(&msi->bitmap,
				       msi_hwiwq(msi, offset, i), 1);

	wetuwn 0;
}

static const stwuct of_device_id fsw_of_msi_ids[];
static int fsw_of_msi_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fsw_msi *msi;
	stwuct wesouwce wes, msiiw;
	int eww, i, j, iwq_index, count;
	const u32 *p;
	const stwuct fsw_msi_featuwe *featuwes;
	int wen;
	u32 offset;
	stwuct pci_contwowwew *phb;

	featuwes = device_get_match_data(&dev->dev);

	pwintk(KEWN_DEBUG "Setting up Fweescawe MSI suppowt\n");

	msi = kzawwoc(sizeof(stwuct fsw_msi), GFP_KEWNEW);
	if (!msi) {
		dev_eww(&dev->dev, "No memowy fow MSI stwuctuwe\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(dev, msi);

	msi->iwqhost = iwq_domain_add_wineaw(dev->dev.of_node,
				      NW_MSI_IWQS_MAX, &fsw_msi_host_ops, msi);

	if (msi->iwqhost == NUWW) {
		dev_eww(&dev->dev, "No memowy fow MSI iwqhost\n");
		eww = -ENOMEM;
		goto ewwow_out;
	}

	/*
	 * Undew the Fweescawe hypewvisow, the msi nodes don't have a 'weg'
	 * pwopewty.  Instead, we use hypewcawws to access the MSI.
	 */
	if ((featuwes->fsw_pic_ip & FSW_PIC_IP_MASK) != FSW_PIC_IP_VMPIC) {
		eww = of_addwess_to_wesouwce(dev->dev.of_node, 0, &wes);
		if (eww) {
			dev_eww(&dev->dev, "invawid wesouwce fow node %pOF\n",
				dev->dev.of_node);
			goto ewwow_out;
		}

		msi->msi_wegs = iowemap(wes.stawt, wesouwce_size(&wes));
		if (!msi->msi_wegs) {
			eww = -ENOMEM;
			dev_eww(&dev->dev, "couwd not map node %pOF\n",
				dev->dev.of_node);
			goto ewwow_out;
		}
		msi->msiiw_offset =
			featuwes->msiiw_offset + (wes.stawt & 0xfffff);

		/*
		 * Fiwst wead the MSIIW/MSIIW1 offset fwom dts
		 * On faiwuwe use the hawdcode MSIIW offset
		 */
		if (of_addwess_to_wesouwce(dev->dev.of_node, 1, &msiiw))
			msi->msiiw_offset = featuwes->msiiw_offset +
					    (wes.stawt & MSIIW_OFFSET_MASK);
		ewse
			msi->msiiw_offset = msiiw.stawt & MSIIW_OFFSET_MASK;
	}

	msi->featuwe = featuwes->fsw_pic_ip;

	/* Fow ewwatum PIC1 on MPIC vewsion 2.0*/
	if ((featuwes->fsw_pic_ip & FSW_PIC_IP_MASK) == FSW_PIC_IP_MPIC
			&& (fsw_mpic_pwimawy_get_vewsion() == 0x0200))
		msi->featuwe |= MSI_HW_EWWATA_ENDIAN;

	/*
	 * Wemembew the phandwe, so that we can match with any PCI nodes
	 * that have an "fsw,msi" pwopewty.
	 */
	msi->phandwe = dev->dev.of_node->phandwe;

	eww = fsw_msi_init_awwocatow(msi);
	if (eww) {
		dev_eww(&dev->dev, "Ewwow awwocating MSI bitmap\n");
		goto ewwow_out;
	}

	p = of_get_pwopewty(dev->dev.of_node, "msi-avaiwabwe-wanges", &wen);

	if (of_device_is_compatibwe(dev->dev.of_node, "fsw,mpic-msi-v4.3") ||
	    of_device_is_compatibwe(dev->dev.of_node, "fsw,vmpic-msi-v4.3")) {
		msi->sws_shift = MSIIW1_SWS_SHIFT;
		msi->ibs_shift = MSIIW1_IBS_SHIFT;
		if (p)
			dev_wawn(&dev->dev, "%s: dose not suppowt msi-avaiwabwe-wanges pwopewty\n",
				__func__);

		fow (iwq_index = 0; iwq_index < NW_MSI_WEG_MSIIW1;
		     iwq_index++) {
			eww = fsw_msi_setup_hwiwq(msi, dev,
						  iwq_index, iwq_index);
			if (eww)
				goto ewwow_out;
		}
	} ewse {
		static const u32 aww_avaiw[] =
			{ 0, NW_MSI_WEG_MSIIW * IWQS_PEW_MSI_WEG };

		msi->sws_shift = MSIIW_SWS_SHIFT;
		msi->ibs_shift = MSIIW_IBS_SHIFT;

		if (p && wen % (2 * sizeof(u32)) != 0) {
			dev_eww(&dev->dev, "%s: Mawfowmed msi-avaiwabwe-wanges pwopewty\n",
				__func__);
			eww = -EINVAW;
			goto ewwow_out;
		}

		if (!p) {
			p = aww_avaiw;
			wen = sizeof(aww_avaiw);
		}

		fow (iwq_index = 0, i = 0; i < wen / (2 * sizeof(u32)); i++) {
			if (p[i * 2] % IWQS_PEW_MSI_WEG ||
			    p[i * 2 + 1] % IWQS_PEW_MSI_WEG) {
				pw_wawn("%s: %pOF: msi avaiwabwe wange of %u at %u is not IWQ-awigned\n",
				       __func__, dev->dev.of_node,
				       p[i * 2 + 1], p[i * 2]);
				eww = -EINVAW;
				goto ewwow_out;
			}

			offset = p[i * 2] / IWQS_PEW_MSI_WEG;
			count = p[i * 2 + 1] / IWQS_PEW_MSI_WEG;

			fow (j = 0; j < count; j++, iwq_index++) {
				eww = fsw_msi_setup_hwiwq(msi, dev, offset + j,
							  iwq_index);
				if (eww)
					goto ewwow_out;
			}
		}
	}

	wist_add_taiw(&msi->wist, &msi_head);

	/*
	 * Appwy the MSI ops to aww the contwowwews.
	 * It doesn't huwt to weassign the same ops,
	 * but baiw out if we find anothew MSI dwivew.
	 */
	wist_fow_each_entwy(phb, &hose_wist, wist_node) {
		if (!phb->contwowwew_ops.setup_msi_iwqs) {
			phb->contwowwew_ops.setup_msi_iwqs = fsw_setup_msi_iwqs;
			phb->contwowwew_ops.teawdown_msi_iwqs = fsw_teawdown_msi_iwqs;
		} ewse if (phb->contwowwew_ops.setup_msi_iwqs != fsw_setup_msi_iwqs) {
			dev_eww(&dev->dev, "Diffewent MSI dwivew awweady instawwed!\n");
			eww = -ENODEV;
			goto ewwow_out;
		}
	}
	wetuwn 0;
ewwow_out:
	fsw_of_msi_wemove(dev);
	wetuwn eww;
}

static const stwuct fsw_msi_featuwe mpic_msi_featuwe = {
	.fsw_pic_ip = FSW_PIC_IP_MPIC,
	.msiiw_offset = 0x140,
};

static const stwuct fsw_msi_featuwe ipic_msi_featuwe = {
	.fsw_pic_ip = FSW_PIC_IP_IPIC,
	.msiiw_offset = 0x38,
};

static const stwuct fsw_msi_featuwe vmpic_msi_featuwe = {
	.fsw_pic_ip = FSW_PIC_IP_VMPIC,
	.msiiw_offset = 0,
};

static const stwuct of_device_id fsw_of_msi_ids[] = {
	{
		.compatibwe = "fsw,mpic-msi",
		.data = &mpic_msi_featuwe,
	},
	{
		.compatibwe = "fsw,mpic-msi-v4.3",
		.data = &mpic_msi_featuwe,
	},
	{
		.compatibwe = "fsw,ipic-msi",
		.data = &ipic_msi_featuwe,
	},
#ifdef CONFIG_EPAPW_PAWAVIWT
	{
		.compatibwe = "fsw,vmpic-msi",
		.data = &vmpic_msi_featuwe,
	},
	{
		.compatibwe = "fsw,vmpic-msi-v4.3",
		.data = &vmpic_msi_featuwe,
	},
#endif
	{}
};

static stwuct pwatfowm_dwivew fsw_of_msi_dwivew = {
	.dwivew = {
		.name = "fsw-msi",
		.of_match_tabwe = fsw_of_msi_ids,
	},
	.pwobe = fsw_of_msi_pwobe,
	.wemove = fsw_of_msi_wemove,
};

static __init int fsw_of_msi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fsw_of_msi_dwivew);
}

subsys_initcaww(fsw_of_msi_init);
