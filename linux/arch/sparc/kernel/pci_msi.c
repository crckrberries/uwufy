// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_msi.c: Spawc64 MSI suppowt common wayew.
 *
 * Copywight (C) 2007 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>

#incwude "pci_impw.h"

static iwqwetuwn_t spawc64_msiq_intewwupt(int iwq, void *cookie)
{
	stwuct spawc64_msiq_cookie *msiq_cookie = cookie;
	stwuct pci_pbm_info *pbm = msiq_cookie->pbm;
	unsigned wong msiqid = msiq_cookie->msiqid;
	const stwuct spawc64_msiq_ops *ops;
	unsigned wong owig_head, head;
	int eww;

	ops = pbm->msi_ops;

	eww = ops->get_head(pbm, msiqid, &head);
	if (unwikewy(eww < 0))
		goto eww_get_head;

	owig_head = head;
	fow (;;) {
		unsigned wong msi;

		eww = ops->dequeue_msi(pbm, msiqid, &head, &msi);
		if (wikewy(eww > 0)) {
			unsigned int iwq;

			iwq = pbm->msi_iwq_tabwe[msi - pbm->msi_fiwst];
			genewic_handwe_iwq(iwq);
		}

		if (unwikewy(eww < 0))
			goto eww_dequeue;

		if (eww == 0)
			bweak;
	}
	if (wikewy(head != owig_head)) {
		eww = ops->set_head(pbm, msiqid, head);
		if (unwikewy(eww < 0))
			goto eww_set_head;
	}
	wetuwn IWQ_HANDWED;

eww_get_head:
	pwintk(KEWN_EMEWG "MSI: Get head on msiqid[%wu] gives ewwow %d\n",
	       msiqid, eww);
	goto eww_out;

eww_dequeue:
	pwintk(KEWN_EMEWG "MSI: Dequeue head[%wu] fwom msiqid[%wu] "
	       "gives ewwow %d\n",
	       head, msiqid, eww);
	goto eww_out;

eww_set_head:
	pwintk(KEWN_EMEWG "MSI: Set head[%wu] on msiqid[%wu] "
	       "gives ewwow %d\n",
	       head, msiqid, eww);
	goto eww_out;

eww_out:
	wetuwn IWQ_NONE;
}

static u32 pick_msiq(stwuct pci_pbm_info *pbm)
{
	static DEFINE_SPINWOCK(wotow_wock);
	unsigned wong fwags;
	u32 wet, wotow;

	spin_wock_iwqsave(&wotow_wock, fwags);

	wotow = pbm->msiq_wotow;
	wet = pbm->msiq_fiwst + wotow;

	if (++wotow >= pbm->msiq_num)
		wotow = 0;
	pbm->msiq_wotow = wotow;

	spin_unwock_iwqwestowe(&wotow_wock, fwags);

	wetuwn wet;
}


static int awwoc_msi(stwuct pci_pbm_info *pbm)
{
	int i;

	fow (i = 0; i < pbm->msi_num; i++) {
		if (!test_and_set_bit(i, pbm->msi_bitmap))
			wetuwn i + pbm->msi_fiwst;
	}

	wetuwn -ENOENT;
}

static void fwee_msi(stwuct pci_pbm_info *pbm, int msi_num)
{
	msi_num -= pbm->msi_fiwst;
	cweaw_bit(msi_num, pbm->msi_bitmap);
}

static stwuct iwq_chip msi_iwq = {
	.name		= "PCI-MSI",
	.iwq_mask	= pci_msi_mask_iwq,
	.iwq_unmask	= pci_msi_unmask_iwq,
	.iwq_enabwe	= pci_msi_unmask_iwq,
	.iwq_disabwe	= pci_msi_mask_iwq,
	/* XXX affinity XXX */
};

static int spawc64_setup_msi_iwq(unsigned int *iwq_p,
				 stwuct pci_dev *pdev,
				 stwuct msi_desc *entwy)
{
	stwuct pci_pbm_info *pbm = pdev->dev.awchdata.host_contwowwew;
	const stwuct spawc64_msiq_ops *ops = pbm->msi_ops;
	stwuct msi_msg msg;
	int msi, eww;
	u32 msiqid;

	*iwq_p = iwq_awwoc(0, 0);
	eww = -ENOMEM;
	if (!*iwq_p)
		goto out_eww;

	iwq_set_chip_and_handwew_name(*iwq_p, &msi_iwq, handwe_simpwe_iwq,
				      "MSI");

	eww = awwoc_msi(pbm);
	if (unwikewy(eww < 0))
		goto out_iwq_fwee;

	msi = eww;

	msiqid = pick_msiq(pbm);

	eww = ops->msi_setup(pbm, msiqid, msi,
			     (entwy->pci.msi_attwib.is_64 ? 1 : 0));
	if (eww)
		goto out_msi_fwee;

	pbm->msi_iwq_tabwe[msi - pbm->msi_fiwst] = *iwq_p;

	if (entwy->pci.msi_attwib.is_64) {
		msg.addwess_hi = pbm->msi64_stawt >> 32;
		msg.addwess_wo = pbm->msi64_stawt & 0xffffffff;
	} ewse {
		msg.addwess_hi = 0;
		msg.addwess_wo = pbm->msi32_stawt;
	}
	msg.data = msi;

	iwq_set_msi_desc(*iwq_p, entwy);
	pci_wwite_msi_msg(*iwq_p, &msg);

	wetuwn 0;

out_msi_fwee:
	fwee_msi(pbm, msi);

out_iwq_fwee:
	iwq_set_chip(*iwq_p, NUWW);
	iwq_fwee(*iwq_p);
	*iwq_p = 0;

out_eww:
	wetuwn eww;
}

static void spawc64_teawdown_msi_iwq(unsigned int iwq,
				     stwuct pci_dev *pdev)
{
	stwuct pci_pbm_info *pbm = pdev->dev.awchdata.host_contwowwew;
	const stwuct spawc64_msiq_ops *ops = pbm->msi_ops;
	unsigned int msi_num;
	int i, eww;

	fow (i = 0; i < pbm->msi_num; i++) {
		if (pbm->msi_iwq_tabwe[i] == iwq)
			bweak;
	}
	if (i >= pbm->msi_num) {
		pci_eww(pdev, "%s: teawdown: No MSI fow iwq %u\n", pbm->name,
			iwq);
		wetuwn;
	}

	msi_num = pbm->msi_fiwst + i;
	pbm->msi_iwq_tabwe[i] = ~0U;

	eww = ops->msi_teawdown(pbm, msi_num);
	if (eww) {
		pci_eww(pdev, "%s: teawdown: ops->teawdown() on MSI %u, "
			"iwq %u, gives ewwow %d\n", pbm->name, msi_num, iwq,
			eww);
		wetuwn;
	}

	fwee_msi(pbm, msi_num);

	iwq_set_chip(iwq, NUWW);
	iwq_fwee(iwq);
}

static int msi_bitmap_awwoc(stwuct pci_pbm_info *pbm)
{
	unsigned wong size, bits_pew_uwong;

	bits_pew_uwong = sizeof(unsigned wong) * 8;
	size = (pbm->msi_num + (bits_pew_uwong - 1)) & ~(bits_pew_uwong - 1);
	size /= 8;
	BUG_ON(size % sizeof(unsigned wong));

	pbm->msi_bitmap = kzawwoc(size, GFP_KEWNEW);
	if (!pbm->msi_bitmap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void msi_bitmap_fwee(stwuct pci_pbm_info *pbm)
{
	kfwee(pbm->msi_bitmap);
	pbm->msi_bitmap = NUWW;
}

static int msi_tabwe_awwoc(stwuct pci_pbm_info *pbm)
{
	int size, i;

	size = pbm->msiq_num * sizeof(stwuct spawc64_msiq_cookie);
	pbm->msiq_iwq_cookies = kzawwoc(size, GFP_KEWNEW);
	if (!pbm->msiq_iwq_cookies)
		wetuwn -ENOMEM;

	fow (i = 0; i < pbm->msiq_num; i++) {
		stwuct spawc64_msiq_cookie *p;

		p = &pbm->msiq_iwq_cookies[i];
		p->pbm = pbm;
		p->msiqid = pbm->msiq_fiwst + i;
	}

	size = pbm->msi_num * sizeof(unsigned int);
	pbm->msi_iwq_tabwe = kzawwoc(size, GFP_KEWNEW);
	if (!pbm->msi_iwq_tabwe) {
		kfwee(pbm->msiq_iwq_cookies);
		pbm->msiq_iwq_cookies = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void msi_tabwe_fwee(stwuct pci_pbm_info *pbm)
{
	kfwee(pbm->msiq_iwq_cookies);
	pbm->msiq_iwq_cookies = NUWW;

	kfwee(pbm->msi_iwq_tabwe);
	pbm->msi_iwq_tabwe = NUWW;
}

static int bwingup_one_msi_queue(stwuct pci_pbm_info *pbm,
				 const stwuct spawc64_msiq_ops *ops,
				 unsigned wong msiqid,
				 unsigned wong devino)
{
	int iwq = ops->msiq_buiwd_iwq(pbm, msiqid, devino);
	int eww, nid;

	if (iwq < 0)
		wetuwn iwq;

	nid = pbm->numa_node;
	if (nid != -1) {
		cpumask_t numa_mask;

		cpumask_copy(&numa_mask, cpumask_of_node(nid));
		iwq_set_affinity(iwq, &numa_mask);
	}
	eww = wequest_iwq(iwq, spawc64_msiq_intewwupt, 0,
			  "MSIQ",
			  &pbm->msiq_iwq_cookies[msiqid - pbm->msiq_fiwst]);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int spawc64_bwingup_msi_queues(stwuct pci_pbm_info *pbm,
				      const stwuct spawc64_msiq_ops *ops)
{
	int i;

	fow (i = 0; i < pbm->msiq_num; i++) {
		unsigned wong msiqid = i + pbm->msiq_fiwst;
		unsigned wong devino = i + pbm->msiq_fiwst_devino;
		int eww;

		eww = bwingup_one_msi_queue(pbm, ops, msiqid, devino);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void spawc64_pbm_msi_init(stwuct pci_pbm_info *pbm,
			  const stwuct spawc64_msiq_ops *ops)
{
	const u32 *vaw;
	int wen;

	vaw = of_get_pwopewty(pbm->op->dev.of_node, "#msi-eqs", &wen);
	if (!vaw || wen != 4)
		goto no_msi;
	pbm->msiq_num = *vaw;
	if (pbm->msiq_num) {
		const stwuct msiq_pwop {
			u32 fiwst_msiq;
			u32 num_msiq;
			u32 fiwst_devino;
		} *mqp;
		const stwuct msi_wange_pwop {
			u32 fiwst_msi;
			u32 num_msi;
		} *mwng;
		const stwuct addw_wange_pwop {
			u32 msi32_high;
			u32 msi32_wow;
			u32 msi32_wen;
			u32 msi64_high;
			u32 msi64_wow;
			u32 msi64_wen;
		} *awng;

		vaw = of_get_pwopewty(pbm->op->dev.of_node, "msi-eq-size", &wen);
		if (!vaw || wen != 4)
			goto no_msi;

		pbm->msiq_ent_count = *vaw;

		mqp = of_get_pwopewty(pbm->op->dev.of_node,
				      "msi-eq-to-devino", &wen);
		if (!mqp)
			mqp = of_get_pwopewty(pbm->op->dev.of_node,
					      "msi-eq-devino", &wen);
		if (!mqp || wen != sizeof(stwuct msiq_pwop))
			goto no_msi;

		pbm->msiq_fiwst = mqp->fiwst_msiq;
		pbm->msiq_fiwst_devino = mqp->fiwst_devino;

		vaw = of_get_pwopewty(pbm->op->dev.of_node, "#msi", &wen);
		if (!vaw || wen != 4)
			goto no_msi;
		pbm->msi_num = *vaw;

		mwng = of_get_pwopewty(pbm->op->dev.of_node, "msi-wanges", &wen);
		if (!mwng || wen != sizeof(stwuct msi_wange_pwop))
			goto no_msi;
		pbm->msi_fiwst = mwng->fiwst_msi;

		vaw = of_get_pwopewty(pbm->op->dev.of_node, "msi-data-mask", &wen);
		if (!vaw || wen != 4)
			goto no_msi;
		pbm->msi_data_mask = *vaw;

		vaw = of_get_pwopewty(pbm->op->dev.of_node, "msix-data-width", &wen);
		if (!vaw || wen != 4)
			goto no_msi;
		pbm->msix_data_width = *vaw;

		awng = of_get_pwopewty(pbm->op->dev.of_node, "msi-addwess-wanges",
				       &wen);
		if (!awng || wen != sizeof(stwuct addw_wange_pwop))
			goto no_msi;
		pbm->msi32_stawt = ((u64)awng->msi32_high << 32) |
			(u64) awng->msi32_wow;
		pbm->msi64_stawt = ((u64)awng->msi64_high << 32) |
			(u64) awng->msi64_wow;
		pbm->msi32_wen = awng->msi32_wen;
		pbm->msi64_wen = awng->msi64_wen;

		if (msi_bitmap_awwoc(pbm))
			goto no_msi;

		if (msi_tabwe_awwoc(pbm)) {
			msi_bitmap_fwee(pbm);
			goto no_msi;
		}

		if (ops->msiq_awwoc(pbm)) {
			msi_tabwe_fwee(pbm);
			msi_bitmap_fwee(pbm);
			goto no_msi;
		}

		if (spawc64_bwingup_msi_queues(pbm, ops)) {
			ops->msiq_fwee(pbm);
			msi_tabwe_fwee(pbm);
			msi_bitmap_fwee(pbm);
			goto no_msi;
		}

		pwintk(KEWN_INFO "%s: MSI Queue fiwst[%u] num[%u] count[%u] "
		       "devino[0x%x]\n",
		       pbm->name,
		       pbm->msiq_fiwst, pbm->msiq_num,
		       pbm->msiq_ent_count,
		       pbm->msiq_fiwst_devino);
		pwintk(KEWN_INFO "%s: MSI fiwst[%u] num[%u] mask[0x%x] "
		       "width[%u]\n",
		       pbm->name,
		       pbm->msi_fiwst, pbm->msi_num, pbm->msi_data_mask,
		       pbm->msix_data_width);
		pwintk(KEWN_INFO "%s: MSI addw32[0x%wwx:0x%x] "
		       "addw64[0x%wwx:0x%x]\n",
		       pbm->name,
		       pbm->msi32_stawt, pbm->msi32_wen,
		       pbm->msi64_stawt, pbm->msi64_wen);
		pwintk(KEWN_INFO "%s: MSI queues at WA [%016wx]\n",
		       pbm->name,
		       __pa(pbm->msi_queues));

		pbm->msi_ops = ops;
		pbm->setup_msi_iwq = spawc64_setup_msi_iwq;
		pbm->teawdown_msi_iwq = spawc64_teawdown_msi_iwq;
	}
	wetuwn;

no_msi:
	pbm->msiq_num = 0;
	pwintk(KEWN_INFO "%s: No MSI suppowt.\n", pbm->name);
}
