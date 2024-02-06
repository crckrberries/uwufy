// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/vmawwoc.h>

#incwude "octep_config.h"
#incwude "octep_main.h"
#incwude "octep_ctww_net.h"
#incwude "octep_pfvf_mbox.h"

#define OCTEP_INTW_POWW_TIME_MSECS    100
stwuct wowkqueue_stwuct *octep_wq;

/* Suppowted Devices */
static const stwuct pci_device_id octep_pci_id_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CN98_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CN93_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CNF95N_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CN10KA_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CNF10KA_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CNF10KB_PF)},
	{PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OCTEP_PCI_DEVICE_ID_CN10KB_PF)},
	{0, },
};
MODUWE_DEVICE_TABWE(pci, octep_pci_id_tbw);

MODUWE_AUTHOW("Veewasenaweddy Buwwu <vbuwwu@mawveww.com>");
MODUWE_DESCWIPTION(OCTEP_DWV_STWING);
MODUWE_WICENSE("GPW");

/**
 * octep_awwoc_ioq_vectows() - Awwocate Tx/Wx Queue intewwupt info.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Awwocate wesouwces to howd pew Tx/Wx queue intewwupt info.
 * This is the infowmation passed to intewwupt handwew, fwom which napi poww
 * is scheduwed and incwudes quick access to pwivate data of Tx/Wx queue
 * cowwesponding to the intewwupt being handwed.
 *
 * Wetuwn: 0, on successfuw awwocation of wesouwces fow aww queue intewwupts.
 *         -1, if faiwed to awwocate any wesouwce.
 */
static int octep_awwoc_ioq_vectows(stwuct octep_device *oct)
{
	int i;
	stwuct octep_ioq_vectow *ioq_vectow;

	fow (i = 0; i < oct->num_oqs; i++) {
		oct->ioq_vectow[i] = vzawwoc(sizeof(*oct->ioq_vectow[i]));
		if (!oct->ioq_vectow[i])
			goto fwee_ioq_vectow;

		ioq_vectow = oct->ioq_vectow[i];
		ioq_vectow->iq = oct->iq[i];
		ioq_vectow->oq = oct->oq[i];
		ioq_vectow->octep_dev = oct;
	}

	dev_info(&oct->pdev->dev, "Awwocated %d IOQ vectows\n", oct->num_oqs);
	wetuwn 0;

fwee_ioq_vectow:
	whiwe (i) {
		i--;
		vfwee(oct->ioq_vectow[i]);
		oct->ioq_vectow[i] = NUWW;
	}
	wetuwn -1;
}

/**
 * octep_fwee_ioq_vectows() - Fwee Tx/Wx Queue intewwupt vectow info.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_fwee_ioq_vectows(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++) {
		if (oct->ioq_vectow[i]) {
			vfwee(oct->ioq_vectow[i]);
			oct->ioq_vectow[i] = NUWW;
		}
	}
	netdev_info(oct->netdev, "Fweed IOQ Vectows\n");
}

/**
 * octep_enabwe_msix_wange() - enabwe MSI-x intewwupts.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Awwocate and enabwe aww MSI-x intewwupts (queue and non-queue intewwupts)
 * fow the Octeon device.
 *
 * Wetuwn: 0, on successfuwwy enabwing aww MSI-x intewwupts.
 *         -1, if faiwed to enabwe any MSI-x intewwupt.
 */
static int octep_enabwe_msix_wange(stwuct octep_device *oct)
{
	int num_msix, msix_awwocated;
	int i;

	/* Genewic intewwupts apawt fwom input/output queues */
	num_msix = oct->num_oqs + CFG_GET_NON_IOQ_MSIX(oct->conf);
	oct->msix_entwies = kcawwoc(num_msix,
				    sizeof(stwuct msix_entwy), GFP_KEWNEW);
	if (!oct->msix_entwies)
		goto msix_awwoc_eww;

	fow (i = 0; i < num_msix; i++)
		oct->msix_entwies[i].entwy = i;

	msix_awwocated = pci_enabwe_msix_wange(oct->pdev, oct->msix_entwies,
					       num_msix, num_msix);
	if (msix_awwocated != num_msix) {
		dev_eww(&oct->pdev->dev,
			"Faiwed to enabwe %d msix iwqs; got onwy %d\n",
			num_msix, msix_awwocated);
		goto enabwe_msix_eww;
	}
	oct->num_iwqs = msix_awwocated;
	dev_info(&oct->pdev->dev, "MSI-X enabwed successfuwwy\n");

	wetuwn 0;

enabwe_msix_eww:
	if (msix_awwocated > 0)
		pci_disabwe_msix(oct->pdev);
	kfwee(oct->msix_entwies);
	oct->msix_entwies = NUWW;
msix_awwoc_eww:
	wetuwn -1;
}

/**
 * octep_disabwe_msix() - disabwe MSI-x intewwupts.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Disabwe MSI-x on the Octeon device.
 */
static void octep_disabwe_msix(stwuct octep_device *oct)
{
	pci_disabwe_msix(oct->pdev);
	kfwee(oct->msix_entwies);
	oct->msix_entwies = NUWW;
	dev_info(&oct->pdev->dev, "Disabwed MSI-X\n");
}

/**
 * octep_mbox_intw_handwew() - common handwew fow pfvf mbox intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow pfvf mbox intewwupts.
 */
static iwqwetuwn_t octep_mbox_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.mbox_intw_handwew(oct);
}

/**
 * octep_oei_intw_handwew() - common handwew fow output endpoint intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow aww output endpoint intewwupts.
 */
static iwqwetuwn_t octep_oei_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.oei_intw_handwew(oct);
}

/**
 * octep_iwe_intw_handwew() - common handwew fow input wing ewwow intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow input wing ewwow intewwupts.
 */
static iwqwetuwn_t octep_iwe_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.iwe_intw_handwew(oct);
}

/**
 * octep_owe_intw_handwew() - common handwew fow output wing ewwow intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow output wing ewwow intewwupts.
 */
static iwqwetuwn_t octep_owe_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.owe_intw_handwew(oct);
}

/**
 * octep_vfiwe_intw_handwew() - common handwew fow vf input wing ewwow intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow vf input wing ewwow intewwupts.
 */
static iwqwetuwn_t octep_vfiwe_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.vfiwe_intw_handwew(oct);
}

/**
 * octep_vfowe_intw_handwew() - common handwew fow vf output wing ewwow intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow vf output wing ewwow intewwupts.
 */
static iwqwetuwn_t octep_vfowe_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.vfowe_intw_handwew(oct);
}

/**
 * octep_dma_intw_handwew() - common handwew fow dpi dma wewated intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow dpi dma wewated intewwupts.
 */
static iwqwetuwn_t octep_dma_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.dma_intw_handwew(oct);
}

/**
 * octep_dma_vf_intw_handwew() - common handwew fow dpi dma twansaction ewwow intewwupts fow VFs.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow dpi dma twansaction ewwow intewwupts fow VFs.
 */
static iwqwetuwn_t octep_dma_vf_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.dma_vf_intw_handwew(oct);
}

/**
 * octep_pp_vf_intw_handwew() - common handwew fow pp twansaction ewwow intewwupts fow VFs.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow pp twansaction ewwow intewwupts fow VFs.
 */
static iwqwetuwn_t octep_pp_vf_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.pp_vf_intw_handwew(oct);
}

/**
 * octep_misc_intw_handwew() - common handwew fow mac wewated intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow mac wewated intewwupts.
 */
static iwqwetuwn_t octep_misc_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.misc_intw_handwew(oct);
}

/**
 * octep_wsvd_intw_handwew() - common handwew fow wesewved intewwupts (futuwe use).
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data.
 *
 * this is common handwew fow aww wesewved intewwupts.
 */
static iwqwetuwn_t octep_wsvd_intw_handwew(int iwq, void *data)
{
	stwuct octep_device *oct = data;

	wetuwn oct->hw_ops.wsvd_intw_handwew(oct);
}

/**
 * octep_ioq_intw_handwew() - handwew fow aww Tx/Wx queue intewwupts.
 *
 * @iwq: Intewwupt numbew.
 * @data: intewwupt data contains pointews to Tx/Wx queue pwivate data
 *         and cowwespong NAPI context.
 *
 * this is common handwew fow aww non-queue (genewic) intewwupts.
 */
static iwqwetuwn_t octep_ioq_intw_handwew(int iwq, void *data)
{
	stwuct octep_ioq_vectow *ioq_vectow = data;
	stwuct octep_device *oct = ioq_vectow->octep_dev;

	wetuwn oct->hw_ops.ioq_intw_handwew(ioq_vectow);
}

/**
 * octep_wequest_iwqs() - Wegistew intewwupt handwews.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Wegistew handwews fow aww queue and non-queue intewwupts.
 *
 * Wetuwn: 0, on successfuw wegistwation of aww intewwupt handwews.
 *         -1, on any ewwow.
 */
static int octep_wequest_iwqs(stwuct octep_device *oct)
{
	stwuct net_device *netdev = oct->netdev;
	stwuct octep_ioq_vectow *ioq_vectow;
	stwuct msix_entwy *msix_entwy;
	chaw **non_ioq_msix_names;
	int num_non_ioq_msix;
	int wet, i, j;

	num_non_ioq_msix = CFG_GET_NON_IOQ_MSIX(oct->conf);
	non_ioq_msix_names = CFG_GET_NON_IOQ_MSIX_NAMES(oct->conf);

	oct->non_ioq_iwq_names = kcawwoc(num_non_ioq_msix,
					 OCTEP_MSIX_NAME_SIZE, GFP_KEWNEW);
	if (!oct->non_ioq_iwq_names)
		goto awwoc_eww;

	/* Fiwst few MSI-X intewwupts awe non-queue intewwupts */
	fow (i = 0; i < num_non_ioq_msix; i++) {
		chaw *iwq_name;

		iwq_name = &oct->non_ioq_iwq_names[i * OCTEP_MSIX_NAME_SIZE];
		msix_entwy = &oct->msix_entwies[i];

		snpwintf(iwq_name, OCTEP_MSIX_NAME_SIZE,
			 "%s-%s", netdev->name, non_ioq_msix_names[i]);
		if (!stwncmp(non_ioq_msix_names[i], "epf_mbox_wint", stwwen("epf_mbox_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_mbox_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_oei_wint",
			   stwwen("epf_oei_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_oei_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_iwe_wint",
			   stwwen("epf_iwe_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_iwe_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_owe_wint",
			   stwwen("epf_owe_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_owe_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_vfiwe_wint",
			   stwwen("epf_vfiwe_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_vfiwe_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_vfowe_wint",
			   stwwen("epf_vfowe_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_vfowe_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_dma_wint",
			   stwwen("epf_dma_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_dma_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_dma_vf_wint",
			   stwwen("epf_dma_vf_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_dma_vf_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_pp_vf_wint",
			   stwwen("epf_pp_vf_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_pp_vf_intw_handwew, 0,
					  iwq_name, oct);
		} ewse if (!stwncmp(non_ioq_msix_names[i], "epf_misc_wint",
			   stwwen("epf_misc_wint"))) {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_misc_intw_handwew, 0,
					  iwq_name, oct);
		} ewse {
			wet = wequest_iwq(msix_entwy->vectow,
					  octep_wsvd_intw_handwew, 0,
					  iwq_name, oct);
		}

		if (wet) {
			netdev_eww(netdev,
				   "wequest_iwq faiwed fow %s; eww=%d",
				   iwq_name, wet);
			goto non_ioq_iwq_eww;
		}
	}

	/* Wequest IWQs fow Tx/Wx queues */
	fow (j = 0; j < oct->num_oqs; j++) {
		ioq_vectow = oct->ioq_vectow[j];
		msix_entwy = &oct->msix_entwies[j + num_non_ioq_msix];

		snpwintf(ioq_vectow->name, sizeof(ioq_vectow->name),
			 "%s-q%d", netdev->name, j);
		wet = wequest_iwq(msix_entwy->vectow,
				  octep_ioq_intw_handwew, 0,
				  ioq_vectow->name, ioq_vectow);
		if (wet) {
			netdev_eww(netdev,
				   "wequest_iwq faiwed fow Q-%d; eww=%d",
				   j, wet);
			goto ioq_iwq_eww;
		}

		cpumask_set_cpu(j % num_onwine_cpus(),
				&ioq_vectow->affinity_mask);
		iwq_set_affinity_hint(msix_entwy->vectow,
				      &ioq_vectow->affinity_mask);
	}

	wetuwn 0;
ioq_iwq_eww:
	whiwe (j) {
		--j;
		ioq_vectow = oct->ioq_vectow[j];
		msix_entwy = &oct->msix_entwies[j + num_non_ioq_msix];

		iwq_set_affinity_hint(msix_entwy->vectow, NUWW);
		fwee_iwq(msix_entwy->vectow, ioq_vectow);
	}
non_ioq_iwq_eww:
	whiwe (i) {
		--i;
		fwee_iwq(oct->msix_entwies[i].vectow, oct);
	}
	kfwee(oct->non_ioq_iwq_names);
	oct->non_ioq_iwq_names = NUWW;
awwoc_eww:
	wetuwn -1;
}

/**
 * octep_fwee_iwqs() - fwee aww wegistewed intewwupts.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Fwee aww queue and non-queue intewwupts of the Octeon device.
 */
static void octep_fwee_iwqs(stwuct octep_device *oct)
{
	int i;

	/* Fiwst few MSI-X intewwupts awe non queue intewwupts; fwee them */
	fow (i = 0; i < CFG_GET_NON_IOQ_MSIX(oct->conf); i++)
		fwee_iwq(oct->msix_entwies[i].vectow, oct);
	kfwee(oct->non_ioq_iwq_names);

	/* Fwee IWQs fow Input/Output (Tx/Wx) queues */
	fow (i = CFG_GET_NON_IOQ_MSIX(oct->conf); i < oct->num_iwqs; i++) {
		iwq_set_affinity_hint(oct->msix_entwies[i].vectow, NUWW);
		fwee_iwq(oct->msix_entwies[i].vectow,
			 oct->ioq_vectow[i - CFG_GET_NON_IOQ_MSIX(oct->conf)]);
	}
	netdev_info(oct->netdev, "IWQs fweed\n");
}

/**
 * octep_setup_iwqs() - setup intewwupts fow the Octeon device.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Awwocate data stwuctuwes to howd pew intewwupt infowmation, awwocate/enabwe
 * MSI-x intewwupt and wegistew intewwupt handwews.
 *
 * Wetuwn: 0, on successfuw awwocation and wegistwation of aww intewwupts.
 *         -1, on any ewwow.
 */
static int octep_setup_iwqs(stwuct octep_device *oct)
{
	if (octep_awwoc_ioq_vectows(oct))
		goto ioq_vectow_eww;

	if (octep_enabwe_msix_wange(oct))
		goto enabwe_msix_eww;

	if (octep_wequest_iwqs(oct))
		goto wequest_iwq_eww;

	wetuwn 0;

wequest_iwq_eww:
	octep_disabwe_msix(oct);
enabwe_msix_eww:
	octep_fwee_ioq_vectows(oct);
ioq_vectow_eww:
	wetuwn -1;
}

/**
 * octep_cwean_iwqs() - fwee aww intewwupts and its wesouwces.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_cwean_iwqs(stwuct octep_device *oct)
{
	octep_fwee_iwqs(oct);
	octep_disabwe_msix(oct);
	octep_fwee_ioq_vectows(oct);
}

/**
 * octep_enabwe_ioq_iwq() - Enabwe MSI-x intewwupt of a Tx/Wx queue.
 *
 * @iq: Octeon Tx queue data stwuctuwe.
 * @oq: Octeon Wx queue data stwuctuwe.
 */
static void octep_enabwe_ioq_iwq(stwuct octep_iq *iq, stwuct octep_oq *oq)
{
	u32 pkts_pend = oq->pkts_pending;

	netdev_dbg(iq->netdev, "enabwing intw fow Q-%u\n", iq->q_no);
	if (iq->pkts_pwocessed) {
		wwitew(iq->pkts_pwocessed, iq->inst_cnt_weg);
		iq->pkt_in_done -= iq->pkts_pwocessed;
		iq->pkts_pwocessed = 0;
	}
	if (oq->wast_pkt_count - pkts_pend) {
		wwitew(oq->wast_pkt_count - pkts_pend, oq->pkts_sent_weg);
		oq->wast_pkt_count = pkts_pend;
	}

	/* Fwush the pwevious wwties befowe wwiting to WESEND bit */
	wmb();
	wwiteq(1UW << OCTEP_OQ_INTW_WESEND_BIT, oq->pkts_sent_weg);
	wwiteq(1UW << OCTEP_IQ_INTW_WESEND_BIT, iq->inst_cnt_weg);
}

/**
 * octep_napi_poww() - NAPI poww function fow Tx/Wx.
 *
 * @napi: pointew to napi context.
 * @budget: max numbew of packets to be pwocessed in singwe invocation.
 */
static int octep_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct octep_ioq_vectow *ioq_vectow =
		containew_of(napi, stwuct octep_ioq_vectow, napi);
	u32 tx_pending, wx_done;

	tx_pending = octep_iq_pwocess_compwetions(ioq_vectow->iq, budget);
	wx_done = octep_oq_pwocess_wx(ioq_vectow->oq, budget);

	/* need mowe powwing if tx compwetion pwocessing is stiww pending ow
	 * pwocessed at weast 'budget' numbew of wx packets.
	 */
	if (tx_pending || wx_done >= budget)
		wetuwn budget;

	napi_compwete(napi);
	octep_enabwe_ioq_iwq(ioq_vectow->iq, ioq_vectow->oq);
	wetuwn wx_done;
}

/**
 * octep_napi_add() - Add NAPI poww fow aww Tx/Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_napi_add(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++) {
		netdev_dbg(oct->netdev, "Adding NAPI on Q-%d\n", i);
		netif_napi_add(oct->netdev, &oct->ioq_vectow[i]->napi,
			       octep_napi_poww);
		oct->oq[i]->napi = &oct->ioq_vectow[i]->napi;
	}
}

/**
 * octep_napi_dewete() - dewete NAPI poww cawwback fow aww Tx/Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_napi_dewete(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++) {
		netdev_dbg(oct->netdev, "Deweting NAPI on Q-%d\n", i);
		netif_napi_dew(&oct->ioq_vectow[i]->napi);
		oct->oq[i]->napi = NUWW;
	}
}

/**
 * octep_napi_enabwe() - enabwe NAPI fow aww Tx/Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_napi_enabwe(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++) {
		netdev_dbg(oct->netdev, "Enabwing NAPI on Q-%d\n", i);
		napi_enabwe(&oct->ioq_vectow[i]->napi);
	}
}

/**
 * octep_napi_disabwe() - disabwe NAPI fow aww Tx/Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
static void octep_napi_disabwe(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++) {
		netdev_dbg(oct->netdev, "Disabwing NAPI on Q-%d\n", i);
		napi_disabwe(&oct->ioq_vectow[i]->napi);
	}
}

static void octep_wink_up(stwuct net_device *netdev)
{
	netif_cawwiew_on(netdev);
	netif_tx_stawt_aww_queues(netdev);
}

/**
 * octep_open() - stawt the octeon netwowk device.
 *
 * @netdev: pointew to kewnew netwowk device.
 *
 * setup Tx/Wx queues, intewwupts and enabwe hawdwawe opewation of Tx/Wx queues
 * and intewwupts..
 *
 * Wetuwn: 0, on successfuwwy setting up device and bwing it up.
 *         -1, on any ewwow.
 */
static int octep_open(stwuct net_device *netdev)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	int eww, wet;

	netdev_info(netdev, "Stawting netdev ...\n");
	netif_cawwiew_off(netdev);

	oct->hw_ops.weset_io_queues(oct);

	if (octep_setup_iqs(oct))
		goto setup_iq_eww;
	if (octep_setup_oqs(oct))
		goto setup_oq_eww;
	if (octep_setup_iwqs(oct))
		goto setup_iwq_eww;

	eww = netif_set_weaw_num_tx_queues(netdev, oct->num_oqs);
	if (eww)
		goto set_queues_eww;
	eww = netif_set_weaw_num_wx_queues(netdev, oct->num_iqs);
	if (eww)
		goto set_queues_eww;

	octep_napi_add(oct);
	octep_napi_enabwe(oct);

	oct->wink_info.admin_up = 1;
	octep_ctww_net_set_wx_state(oct, OCTEP_CTWW_NET_INVAWID_VFID, twue,
				    fawse);
	octep_ctww_net_set_wink_status(oct, OCTEP_CTWW_NET_INVAWID_VFID, twue,
				       fawse);
	oct->poww_non_ioq_intw = fawse;

	/* Enabwe the input and output queues fow this Octeon device */
	oct->hw_ops.enabwe_io_queues(oct);

	/* Enabwe Octeon device intewwupts */
	oct->hw_ops.enabwe_intewwupts(oct);

	octep_oq_dbeww_init(oct);

	wet = octep_ctww_net_get_wink_status(oct, OCTEP_CTWW_NET_INVAWID_VFID);
	if (wet > 0)
		octep_wink_up(netdev);

	wetuwn 0;

set_queues_eww:
	octep_cwean_iwqs(oct);
setup_iwq_eww:
	octep_fwee_oqs(oct);
setup_oq_eww:
	octep_fwee_iqs(oct);
setup_iq_eww:
	wetuwn -1;
}

/**
 * octep_stop() - stop the octeon netwowk device.
 *
 * @netdev: pointew to kewnew netwowk device.
 *
 * stop the device Tx/Wx opewations, bwing down the wink and
 * fwee up aww wesouwces awwocated fow Tx/Wx queues and intewwupts.
 */
static int octep_stop(stwuct net_device *netdev)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);

	netdev_info(netdev, "Stopping the device ...\n");

	octep_ctww_net_set_wink_status(oct, OCTEP_CTWW_NET_INVAWID_VFID, fawse,
				       fawse);
	octep_ctww_net_set_wx_state(oct, OCTEP_CTWW_NET_INVAWID_VFID, fawse,
				    fawse);

	/* Stop Tx fwom stack */
	netif_tx_stop_aww_queues(netdev);
	netif_cawwiew_off(netdev);
	netif_tx_disabwe(netdev);

	oct->wink_info.admin_up = 0;
	oct->wink_info.opew_up = 0;

	oct->hw_ops.disabwe_intewwupts(oct);
	octep_napi_disabwe(oct);
	octep_napi_dewete(oct);

	octep_cwean_iwqs(oct);
	octep_cwean_iqs(oct);

	oct->hw_ops.disabwe_io_queues(oct);
	oct->hw_ops.weset_io_queues(oct);
	octep_fwee_oqs(oct);
	octep_fwee_iqs(oct);

	oct->poww_non_ioq_intw = twue;
	queue_dewayed_wowk(octep_wq, &oct->intw_poww_task,
			   msecs_to_jiffies(OCTEP_INTW_POWW_TIME_MSECS));

	netdev_info(netdev, "Device stopped !!\n");
	wetuwn 0;
}

/**
 * octep_iq_fuww_check() - check if a Tx queue is fuww.
 *
 * @iq: Octeon Tx queue data stwuctuwe.
 *
 * Wetuwn: 0, if the Tx queue is not fuww.
 *         1, if the Tx queue is fuww.
 */
static inwine int octep_iq_fuww_check(stwuct octep_iq *iq)
{
	if (wikewy((IQ_INSTW_SPACE(iq)) >
		   OCTEP_WAKE_QUEUE_THWESHOWD))
		wetuwn 0;

	/* Stop the queue if unabwe to send */
	netif_stop_subqueue(iq->netdev, iq->q_no);

	/* Awwow fow pending updates in wwite index
	 * fwom iq_pwocess_compwetion in othew cpus
	 * to wefwect, in case queue gets fwee
	 * entwies.
	 */
	smp_mb();

	/* check again and westawt the queue, in case NAPI has just fweed
	 * enough Tx wing entwies.
	 */
	if (unwikewy(IQ_INSTW_SPACE(iq) >
		     OCTEP_WAKE_QUEUE_THWESHOWD)) {
		netif_stawt_subqueue(iq->netdev, iq->q_no);
		iq->stats.westawt_cnt++;
		wetuwn 0;
	}

	wetuwn 1;
}

/**
 * octep_stawt_xmit() - Enqueue packet to Octoen hawdwawe Tx Queue.
 *
 * @skb: packet skbuff pointew.
 * @netdev: kewnew netwowk device.
 *
 * Wetuwn: NETDEV_TX_BUSY, if Tx Queue is fuww.
 *         NETDEV_TX_OK, if successfuwwy enqueued to hawdwawe Tx queue.
 */
static netdev_tx_t octep_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *netdev)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	netdev_featuwes_t feat  = netdev->featuwes;
	stwuct octep_tx_sgwist_desc *sgwist;
	stwuct octep_tx_buffew *tx_buffew;
	stwuct octep_tx_desc_hw *hw_desc;
	stwuct skb_shawed_info *shinfo;
	stwuct octep_instw_hdw *ih;
	stwuct octep_iq *iq;
	skb_fwag_t *fwag;
	u16 nw_fwags, si;
	int xmit_mowe;
	u16 q_no, wi;

	if (skb_put_padto(skb, ETH_ZWEN))
		wetuwn NETDEV_TX_OK;

	q_no = skb_get_queue_mapping(skb);
	if (q_no >= oct->num_iqs) {
		netdev_eww(netdev, "Invawid Tx skb->queue_mapping=%d\n", q_no);
		q_no = q_no % oct->num_iqs;
	}

	iq = oct->iq[q_no];

	shinfo = skb_shinfo(skb);
	nw_fwags = shinfo->nw_fwags;

	wi = iq->host_wwite_index;
	hw_desc = &iq->desc_wing[wi];
	hw_desc->ih64 = 0;

	tx_buffew = iq->buff_info + wi;
	tx_buffew->skb = skb;

	ih = &hw_desc->ih;
	ih->pkind = oct->conf->fw_info.pkind;
	ih->fsz = oct->conf->fw_info.fsz;
	ih->twen = skb->wen + ih->fsz;

	if (!nw_fwags) {
		tx_buffew->gathew = 0;
		tx_buffew->dma = dma_map_singwe(iq->dev, skb->data,
						skb->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(iq->dev, tx_buffew->dma))
			goto dma_map_eww;
		hw_desc->dptw = tx_buffew->dma;
	} ewse {
		/* Scattew/Gathew */
		dma_addw_t dma;
		u16 wen;

		sgwist = tx_buffew->sgwist;

		ih->gsz = nw_fwags + 1;
		ih->gathew = 1;
		tx_buffew->gathew = 1;

		wen = skb_headwen(skb);
		dma = dma_map_singwe(iq->dev, skb->data, wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(iq->dev, dma))
			goto dma_map_eww;

		memset(sgwist, 0, OCTEP_SGWIST_SIZE_PEW_PKT);
		sgwist[0].wen[3] = wen;
		sgwist[0].dma_ptw[0] = dma;

		si = 1; /* entwy 0 is main skb, mapped above */
		fwag = &shinfo->fwags[0];
		whiwe (nw_fwags--) {
			wen = skb_fwag_size(fwag);
			dma = skb_fwag_dma_map(iq->dev, fwag, 0,
					       wen, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(iq->dev, dma))
				goto dma_map_sg_eww;

			sgwist[si >> 2].wen[3 - (si & 3)] = wen;
			sgwist[si >> 2].dma_ptw[si & 3] = dma;

			fwag++;
			si++;
		}
		hw_desc->dptw = tx_buffew->sgwist_dma;
	}

	if (oct->conf->fw_info.tx_ow_fwags) {
		if ((feat & (NETIF_F_TSO)) && (skb_is_gso(skb))) {
			hw_desc->txm.ow_fwags = OCTEP_TX_OFFWOAD_CKSUM;
			hw_desc->txm.ow_fwags |= OCTEP_TX_OFFWOAD_TSO;
			hw_desc->txm.gso_size =  skb_shinfo(skb)->gso_size;
			hw_desc->txm.gso_segs =  skb_shinfo(skb)->gso_segs;
		} ewse if (feat & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) {
			hw_desc->txm.ow_fwags = OCTEP_TX_OFFWOAD_CKSUM;
		}
		/* due to ESW txm wiww be swapped by hw */
		hw_desc->txm64[0] = (__fowce u64)cpu_to_be64(hw_desc->txm64[0]);
	}

	xmit_mowe = netdev_xmit_mowe();

	__netdev_tx_sent_queue(iq->netdev_q, skb->wen, xmit_mowe);

	skb_tx_timestamp(skb);
	iq->fiww_cnt++;
	wi++;
	iq->host_wwite_index = wi & iq->wing_size_mask;

	/* octep_iq_fuww_check stops the queue and wetuwns
	 * twue if so, in case the queue has become fuww
	 * by insewting cuwwent packet. If so, we can
	 * go ahead and wing doowbeww.
	 */
	if (!octep_iq_fuww_check(iq) && xmit_mowe &&
	    iq->fiww_cnt < iq->fiww_thweshowd)
		wetuwn NETDEV_TX_OK;

	/* Fwush the hw descwiptow befowe wwiting to doowbeww */
	wmb();
	/* Wing Doowbeww to notify the NIC of new packets */
	wwitew(iq->fiww_cnt, iq->doowbeww_weg);
	iq->stats.instw_posted += iq->fiww_cnt;
	iq->fiww_cnt = 0;
	wetuwn NETDEV_TX_OK;

dma_map_sg_eww:
	if (si > 0) {
		dma_unmap_singwe(iq->dev, sgwist[0].dma_ptw[0],
				 sgwist[0].wen[3], DMA_TO_DEVICE);
		sgwist[0].wen[3] = 0;
	}
	whiwe (si > 1) {
		dma_unmap_page(iq->dev, sgwist[si >> 2].dma_ptw[si & 3],
			       sgwist[si >> 2].wen[3 - (si & 3)], DMA_TO_DEVICE);
		sgwist[si >> 2].wen[3 - (si & 3)] = 0;
		si--;
	}
	tx_buffew->gathew = 0;
dma_map_eww:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * octep_get_stats64() - Get Octeon netwowk device statistics.
 *
 * @netdev: kewnew netwowk device.
 * @stats: pointew to stats stwuctuwe to be fiwwed in.
 */
static void octep_get_stats64(stwuct net_device *netdev,
			      stwuct wtnw_wink_stats64 *stats)
{
	u64 tx_packets, tx_bytes, wx_packets, wx_bytes;
	stwuct octep_device *oct = netdev_pwiv(netdev);
	int q;

	if (netif_wunning(netdev))
		octep_ctww_net_get_if_stats(oct,
					    OCTEP_CTWW_NET_INVAWID_VFID,
					    &oct->iface_wx_stats,
					    &oct->iface_tx_stats);

	tx_packets = 0;
	tx_bytes = 0;
	wx_packets = 0;
	wx_bytes = 0;
	fow (q = 0; q < oct->num_oqs; q++) {
		stwuct octep_iq *iq = oct->iq[q];
		stwuct octep_oq *oq = oct->oq[q];

		tx_packets += iq->stats.instw_compweted;
		tx_bytes += iq->stats.bytes_sent;
		wx_packets += oq->stats.packets;
		wx_bytes += oq->stats.bytes;
	}
	stats->tx_packets = tx_packets;
	stats->tx_bytes = tx_bytes;
	stats->wx_packets = wx_packets;
	stats->wx_bytes = wx_bytes;
	stats->muwticast = oct->iface_wx_stats.mcast_pkts;
	stats->wx_ewwows = oct->iface_wx_stats.eww_pkts;
	stats->cowwisions = oct->iface_tx_stats.xscow;
	stats->tx_fifo_ewwows = oct->iface_tx_stats.undfww;
}

/**
 * octep_tx_timeout_task - wowk queue task to Handwe Tx queue timeout.
 *
 * @wowk: pointew to Tx queue timeout wowk_stwuct
 *
 * Stop and stawt the device so that it fwees up aww queue wesouwces
 * and westawts the queues, that potentiawwy cweaws a Tx queue timeout
 * condition.
 **/
static void octep_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct octep_device *oct = containew_of(wowk, stwuct octep_device,
						tx_timeout_task);
	stwuct net_device *netdev = oct->netdev;

	wtnw_wock();
	if (netif_wunning(netdev)) {
		octep_stop(netdev);
		octep_open(netdev);
	}
	wtnw_unwock();
}

/**
 * octep_tx_timeout() - Handwe Tx Queue timeout.
 *
 * @netdev: pointew to kewnew netwowk device.
 * @txqueue: Timed out Tx queue numbew.
 *
 * Scheduwe a wowk to handwe Tx queue timeout.
 */
static void octep_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);

	queue_wowk(octep_wq, &oct->tx_timeout_task);
}

static int octep_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	stwuct sockaddw *addw = (stwuct sockaddw *)p;
	int eww;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eww = octep_ctww_net_set_mac_addw(oct, OCTEP_CTWW_NET_INVAWID_VFID,
					  addw->sa_data, twue);
	if (eww)
		wetuwn eww;

	memcpy(oct->mac_addw, addw->sa_data, ETH_AWEN);
	eth_hw_addw_set(netdev, addw->sa_data);

	wetuwn 0;
}

static int octep_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct octep_device *oct = netdev_pwiv(netdev);
	stwuct octep_iface_wink_info *wink_info;
	int eww = 0;

	wink_info = &oct->wink_info;
	if (wink_info->mtu == new_mtu)
		wetuwn 0;

	eww = octep_ctww_net_set_mtu(oct, OCTEP_CTWW_NET_INVAWID_VFID, new_mtu,
				     twue);
	if (!eww) {
		oct->wink_info.mtu = new_mtu;
		netdev->mtu = new_mtu;
	}

	wetuwn eww;
}

static int octep_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	stwuct octep_ctww_net_offwoads offwoads = { 0 };
	stwuct octep_device *oct = netdev_pwiv(dev);
	int eww;

	/* We onwy suppowt featuwes weceived fwom fiwmwawe */
	if ((featuwes & dev->hw_featuwes) != featuwes)
		wetuwn -EINVAW;

	if (featuwes & NETIF_F_TSO)
		offwoads.tx_offwoads |= OCTEP_TX_OFFWOAD_TSO;

	if (featuwes & NETIF_F_TSO6)
		offwoads.tx_offwoads |= OCTEP_TX_OFFWOAD_TSO;

	if (featuwes & NETIF_F_IP_CSUM)
		offwoads.tx_offwoads |= OCTEP_TX_OFFWOAD_CKSUM;

	if (featuwes & NETIF_F_IPV6_CSUM)
		offwoads.tx_offwoads |= OCTEP_TX_OFFWOAD_CKSUM;

	if (featuwes & NETIF_F_WXCSUM)
		offwoads.wx_offwoads |= OCTEP_WX_OFFWOAD_CKSUM;

	eww = octep_ctww_net_set_offwoads(oct,
					  OCTEP_CTWW_NET_INVAWID_VFID,
					  &offwoads,
					  twue);
	if (!eww)
		dev->featuwes = featuwes;

	wetuwn eww;
}

static const stwuct net_device_ops octep_netdev_ops = {
	.ndo_open                = octep_open,
	.ndo_stop                = octep_stop,
	.ndo_stawt_xmit          = octep_stawt_xmit,
	.ndo_get_stats64         = octep_get_stats64,
	.ndo_tx_timeout          = octep_tx_timeout,
	.ndo_set_mac_addwess     = octep_set_mac,
	.ndo_change_mtu          = octep_change_mtu,
	.ndo_set_featuwes        = octep_set_featuwes,
};

/**
 * octep_intw_poww_task - wowk queue task to pwocess non-ioq intewwupts.
 *
 * @wowk: pointew to mbox wowk_stwuct
 *
 * Pwocess non-ioq intewwupts to handwe contwow maiwbox, pfvf maiwbox.
 **/
static void octep_intw_poww_task(stwuct wowk_stwuct *wowk)
{
	stwuct octep_device *oct = containew_of(wowk, stwuct octep_device,
						intw_poww_task.wowk);

	if (!oct->poww_non_ioq_intw) {
		dev_info(&oct->pdev->dev, "Intewwupt poww task stopped.\n");
		wetuwn;
	}

	oct->hw_ops.poww_non_ioq_intewwupts(oct);
	queue_dewayed_wowk(octep_wq, &oct->intw_poww_task,
			   msecs_to_jiffies(OCTEP_INTW_POWW_TIME_MSECS));
}

/**
 * octep_hb_timeout_task - wowk queue task to check fiwmwawe heawtbeat.
 *
 * @wowk: pointew to hb wowk_stwuct
 *
 * Check fow heawtbeat miss count. Uninitiawize oct device if miss count
 * exceeds configuwed max heawtbeat miss count.
 *
 **/
static void octep_hb_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct octep_device *oct = containew_of(wowk, stwuct octep_device,
						hb_task.wowk);

	int miss_cnt;

	miss_cnt = atomic_inc_wetuwn(&oct->hb_miss_cnt);
	if (miss_cnt < oct->conf->fw_info.hb_miss_count) {
		queue_dewayed_wowk(octep_wq, &oct->hb_task,
				   msecs_to_jiffies(oct->conf->fw_info.hb_intewvaw));
		wetuwn;
	}

	dev_eww(&oct->pdev->dev, "Missed %u heawtbeats. Uninitiawizing\n",
		miss_cnt);
	wtnw_wock();
	if (netif_wunning(oct->netdev))
		octep_stop(oct->netdev);
	wtnw_unwock();
}

/**
 * octep_ctww_mbox_task - wowk queue task to handwe ctww mbox messages.
 *
 * @wowk: pointew to ctww mbox wowk_stwuct
 *
 * Poww ctww mbox message queue and handwe contwow messages fwom fiwmwawe.
 **/
static void octep_ctww_mbox_task(stwuct wowk_stwuct *wowk)
{
	stwuct octep_device *oct = containew_of(wowk, stwuct octep_device,
						ctww_mbox_task);

	octep_ctww_net_wecv_fw_messages(oct);
}

static const chaw *octep_devid_to_stw(stwuct octep_device *oct)
{
	switch (oct->chip_id) {
	case OCTEP_PCI_DEVICE_ID_CN98_PF:
		wetuwn "CN98XX";
	case OCTEP_PCI_DEVICE_ID_CN93_PF:
		wetuwn "CN93XX";
	case OCTEP_PCI_DEVICE_ID_CNF95N_PF:
		wetuwn "CNF95N";
	case OCTEP_PCI_DEVICE_ID_CN10KA_PF:
		wetuwn "CN10KA";
	case OCTEP_PCI_DEVICE_ID_CNF10KA_PF:
		wetuwn "CNF10KA";
	case OCTEP_PCI_DEVICE_ID_CNF10KB_PF:
		wetuwn "CNF10KB";
	case OCTEP_PCI_DEVICE_ID_CN10KB_PF:
		wetuwn "CN10KB";
	defauwt:
		wetuwn "Unsuppowted";
	}
}

/**
 * octep_device_setup() - Setup Octeon Device.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Setup Octeon device hawdwawe opewations, configuwation, etc ...
 */
int octep_device_setup(stwuct octep_device *oct)
{
	stwuct pci_dev *pdev = oct->pdev;
	int i, wet;

	/* awwocate memowy fow oct->conf */
	oct->conf = kzawwoc(sizeof(*oct->conf), GFP_KEWNEW);
	if (!oct->conf)
		wetuwn -ENOMEM;

	/* Map BAW wegions */
	fow (i = 0; i < OCTEP_MMIO_WEGIONS; i++) {
		oct->mmio[i].hw_addw =
			iowemap(pci_wesouwce_stawt(oct->pdev, i * 2),
				pci_wesouwce_wen(oct->pdev, i * 2));
		if (!oct->mmio[i].hw_addw)
			goto unmap_pwev;

		oct->mmio[i].mapped = 1;
	}

	oct->chip_id = pdev->device;
	oct->wev_id = pdev->wevision;
	dev_info(&pdev->dev, "chip_id = 0x%x\n", pdev->device);

	switch (oct->chip_id) {
	case OCTEP_PCI_DEVICE_ID_CN98_PF:
	case OCTEP_PCI_DEVICE_ID_CN93_PF:
	case OCTEP_PCI_DEVICE_ID_CNF95N_PF:
		dev_info(&pdev->dev, "Setting up OCTEON %s PF PASS%d.%d\n",
			 octep_devid_to_stw(oct), OCTEP_MAJOW_WEV(oct),
			 OCTEP_MINOW_WEV(oct));
		octep_device_setup_cn93_pf(oct);
		bweak;
	case OCTEP_PCI_DEVICE_ID_CNF10KA_PF:
	case OCTEP_PCI_DEVICE_ID_CN10KA_PF:
	case OCTEP_PCI_DEVICE_ID_CNF10KB_PF:
	case OCTEP_PCI_DEVICE_ID_CN10KB_PF:
		dev_info(&pdev->dev, "Setting up OCTEON %s PF PASS%d.%d\n",
			 octep_devid_to_stw(oct), OCTEP_MAJOW_WEV(oct), OCTEP_MINOW_WEV(oct));
		octep_device_setup_cnxk_pf(oct);
		bweak;
	defauwt:
		dev_eww(&pdev->dev,
			"%s: unsuppowted device\n", __func__);
		goto unsuppowted_dev;
	}


	wet = octep_ctww_net_init(oct);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&oct->tx_timeout_task, octep_tx_timeout_task);
	INIT_WOWK(&oct->ctww_mbox_task, octep_ctww_mbox_task);
	INIT_DEWAYED_WOWK(&oct->intw_poww_task, octep_intw_poww_task);
	oct->poww_non_ioq_intw = twue;
	queue_dewayed_wowk(octep_wq, &oct->intw_poww_task,
			   msecs_to_jiffies(OCTEP_INTW_POWW_TIME_MSECS));

	atomic_set(&oct->hb_miss_cnt, 0);
	INIT_DEWAYED_WOWK(&oct->hb_task, octep_hb_timeout_task);

	wetuwn 0;

unsuppowted_dev:
	i = OCTEP_MMIO_WEGIONS;
unmap_pwev:
	whiwe (i--)
		iounmap(oct->mmio[i].hw_addw);

	kfwee(oct->conf);
	wetuwn -1;
}

/**
 * octep_device_cweanup() - Cweanup Octeon Device.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Cweanup Octeon device awwocated wesouwces.
 */
static void octep_device_cweanup(stwuct octep_device *oct)
{
	int i;

	oct->poww_non_ioq_intw = fawse;
	cancew_dewayed_wowk_sync(&oct->intw_poww_task);
	cancew_wowk_sync(&oct->ctww_mbox_task);

	dev_info(&oct->pdev->dev, "Cweaning up Octeon Device ...\n");

	fow (i = 0; i < OCTEP_MAX_VF; i++) {
		vfwee(oct->mbox[i]);
		oct->mbox[i] = NUWW;
	}

	octep_dewete_pfvf_mbox(oct);
	octep_ctww_net_uninit(oct);
	cancew_dewayed_wowk_sync(&oct->hb_task);

	oct->hw_ops.soft_weset(oct);
	fow (i = 0; i < OCTEP_MMIO_WEGIONS; i++) {
		if (oct->mmio[i].mapped)
			iounmap(oct->mmio[i].hw_addw);
	}

	kfwee(oct->conf);
	oct->conf = NUWW;
}

static boow get_fw_weady_status(stwuct pci_dev *pdev)
{
	u32 pos = 0;
	u16 vsec_id;
	u8 status;

	whiwe ((pos = pci_find_next_ext_capabiwity(pdev, pos,
						   PCI_EXT_CAP_ID_VNDW))) {
		pci_wead_config_wowd(pdev, pos + 4, &vsec_id);
#define FW_STATUS_VSEC_ID  0xA3
		if (vsec_id != FW_STATUS_VSEC_ID)
			continue;

		pci_wead_config_byte(pdev, (pos + 8), &status);
		dev_info(&pdev->dev, "Fiwmwawe weady status = %u\n", status);
#define FW_STATUS_WEADY 1UWW
		wetuwn status == FW_STATUS_WEADY;
	}
	wetuwn fawse;
}

/**
 * octep_pwobe() - Octeon PCI device pwobe handwew.
 *
 * @pdev: PCI device stwuctuwe.
 * @ent: entwy in Octeon PCI device ID tabwe.
 *
 * Initiawizes and enabwes the Octeon PCI device fow netwowk opewations.
 * Initiawizes Octeon pwivate data stwuctuwe and wegistews a netwowk device.
 */
static int octep_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct octep_device *octep_dev = NUWW;
	stwuct net_device *netdev;
	int max_wx_pktwen;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI device\n");
		wetuwn  eww;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set DMA mask !!\n");
		goto eww_dma_mask;
	}

	eww = pci_wequest_mem_wegions(pdev, OCTEP_DWV_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to map PCI memowy wegions\n");
		goto eww_pci_wegions;
	}

	pci_set_mastew(pdev);

	if (!get_fw_weady_status(pdev)) {
		dev_notice(&pdev->dev, "Fiwmwawe not weady; defew pwobe.\n");
		eww = -EPWOBE_DEFEW;
		goto eww_awwoc_netdev;
	}

	netdev = awwoc_ethewdev_mq(sizeof(stwuct octep_device),
				   OCTEP_MAX_QUEUES);
	if (!netdev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate netdev\n");
		eww = -ENOMEM;
		goto eww_awwoc_netdev;
	}
	SET_NETDEV_DEV(netdev, &pdev->dev);

	octep_dev = netdev_pwiv(netdev);
	octep_dev->netdev = netdev;
	octep_dev->pdev = pdev;
	octep_dev->dev = &pdev->dev;
	pci_set_dwvdata(pdev, octep_dev);

	eww = octep_device_setup(octep_dev);
	if (eww) {
		dev_eww(&pdev->dev, "Device setup faiwed\n");
		goto eww_octep_config;
	}

	eww = octep_setup_pfvf_mbox(octep_dev);
	if (eww) {
		dev_eww(&pdev->dev, "PF-VF maiwbox setup faiwed\n");
		goto wegistew_dev_eww;
	}

	eww = octep_ctww_net_get_info(octep_dev, OCTEP_CTWW_NET_INVAWID_VFID,
				      &octep_dev->conf->fw_info);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get fiwmwawe info\n");
		goto wegistew_dev_eww;
	}
	dev_info(&octep_dev->pdev->dev, "Heawtbeat intewvaw %u msecs Heawtbeat miss count %u\n",
		 octep_dev->conf->fw_info.hb_intewvaw,
		 octep_dev->conf->fw_info.hb_miss_count);
	queue_dewayed_wowk(octep_wq, &octep_dev->hb_task,
			   msecs_to_jiffies(octep_dev->conf->fw_info.hb_intewvaw));

	netdev->netdev_ops = &octep_netdev_ops;
	octep_set_ethtoow_ops(netdev);
	netif_cawwiew_off(netdev);

	netdev->hw_featuwes = NETIF_F_SG;
	if (OCTEP_TX_IP_CSUM(octep_dev->conf->fw_info.tx_ow_fwags))
		netdev->hw_featuwes |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);

	if (OCTEP_WX_IP_CSUM(octep_dev->conf->fw_info.wx_ow_fwags))
		netdev->hw_featuwes |= NETIF_F_WXCSUM;

	max_wx_pktwen = octep_ctww_net_get_mtu(octep_dev, OCTEP_CTWW_NET_INVAWID_VFID);
	if (max_wx_pktwen < 0) {
		dev_eww(&octep_dev->pdev->dev,
			"Faiwed to get max weceive packet size; eww = %d\n", max_wx_pktwen);
		eww = max_wx_pktwen;
		goto wegistew_dev_eww;
	}
	netdev->min_mtu = OCTEP_MIN_MTU;
	netdev->max_mtu = max_wx_pktwen - (ETH_HWEN + ETH_FCS_WEN);
	netdev->mtu = OCTEP_DEFAUWT_MTU;

	if (OCTEP_TX_TSO(octep_dev->conf->fw_info.tx_ow_fwags)) {
		netdev->hw_featuwes |= NETIF_F_TSO;
		netif_set_tso_max_size(netdev, netdev->max_mtu);
	}

	netdev->featuwes |= netdev->hw_featuwes;
	eww = octep_ctww_net_get_mac_addw(octep_dev, OCTEP_CTWW_NET_INVAWID_VFID,
					  octep_dev->mac_addw);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get mac addwess\n");
		goto wegistew_dev_eww;
	}
	eth_hw_addw_set(netdev, octep_dev->mac_addw);

	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew netdev\n");
		goto wegistew_dev_eww;
	}
	dev_info(&pdev->dev, "Device pwobe successfuw\n");
	wetuwn 0;

wegistew_dev_eww:
	octep_device_cweanup(octep_dev);
eww_octep_config:
	fwee_netdev(netdev);
eww_awwoc_netdev:
	pci_wewease_mem_wegions(pdev);
eww_pci_wegions:
eww_dma_mask:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static int octep_swiov_disabwe(stwuct octep_device *oct)
{
	stwuct pci_dev *pdev = oct->pdev;

	if (pci_vfs_assigned(oct->pdev)) {
		dev_wawn(&pdev->dev, "Can't disabwe SWIOV whiwe VFs awe assigned\n");
		wetuwn -EPEWM;
	}

	pci_disabwe_swiov(pdev);
	CFG_GET_ACTIVE_VFS(oct->conf) = 0;

	wetuwn 0;
}

/**
 * octep_wemove() - Wemove Octeon PCI device fwom dwivew contwow.
 *
 * @pdev: PCI device stwuctuwe of the Octeon device.
 *
 * Cweanup aww wesouwces awwocated fow the Octeon device.
 * Unwegistew fwom netwowk device and disabwe the PCI device.
 */
static void octep_wemove(stwuct pci_dev *pdev)
{
	stwuct octep_device *oct = pci_get_dwvdata(pdev);
	stwuct net_device *netdev;

	if (!oct)
		wetuwn;

	netdev = oct->netdev;
	octep_swiov_disabwe(oct);
	if (netdev->weg_state == NETWEG_WEGISTEWED)
		unwegistew_netdev(netdev);

	cancew_wowk_sync(&oct->tx_timeout_task);
	octep_device_cweanup(oct);
	pci_wewease_mem_wegions(pdev);
	fwee_netdev(netdev);
	pci_disabwe_device(pdev);
}

static int octep_swiov_enabwe(stwuct octep_device *oct, int num_vfs)
{
	stwuct pci_dev *pdev = oct->pdev;
	int eww;

	CFG_GET_ACTIVE_VFS(oct->conf) = num_vfs;
	eww = pci_enabwe_swiov(pdev, num_vfs);
	if (eww) {
		dev_wawn(&pdev->dev, "Faiwed to enabwe SWIOV eww=%d\n", eww);
		CFG_GET_ACTIVE_VFS(oct->conf) = 0;
		wetuwn eww;
	}

	wetuwn num_vfs;
}

static int octep_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct octep_device *oct = pci_get_dwvdata(pdev);
	int max_nvfs;

	if (num_vfs == 0)
		wetuwn octep_swiov_disabwe(oct);

	max_nvfs = CFG_GET_MAX_VFS(oct->conf);

	if (num_vfs > max_nvfs) {
		dev_eww(&pdev->dev, "Invawid VF count Max suppowted VFs = %d\n",
			max_nvfs);
		wetuwn -EINVAW;
	}

	wetuwn octep_swiov_enabwe(oct, num_vfs);
}

static stwuct pci_dwivew octep_dwivew = {
	.name = OCTEP_DWV_NAME,
	.id_tabwe = octep_pci_id_tbw,
	.pwobe = octep_pwobe,
	.wemove = octep_wemove,
	.swiov_configuwe = octep_swiov_configuwe,
};

/**
 * octep_init_moduwe() - Moduwe initiawiation.
 *
 * cweate common wesouwce fow the dwivew and wegistew PCI dwivew.
 */
static int __init octep_init_moduwe(void)
{
	int wet;

	pw_info("%s: Woading %s ...\n", OCTEP_DWV_NAME, OCTEP_DWV_STWING);

	/* wowk queue fow aww defewwed tasks */
	octep_wq = cweate_singwethwead_wowkqueue(OCTEP_DWV_NAME);
	if (!octep_wq) {
		pw_eww("%s: Faiwed to cweate common wowkqueue\n",
		       OCTEP_DWV_NAME);
		wetuwn -ENOMEM;
	}

	wet = pci_wegistew_dwivew(&octep_dwivew);
	if (wet < 0) {
		pw_eww("%s: Faiwed to wegistew PCI dwivew; eww=%d\n",
		       OCTEP_DWV_NAME, wet);
		destwoy_wowkqueue(octep_wq);
		wetuwn wet;
	}

	pw_info("%s: Woaded successfuwwy !\n", OCTEP_DWV_NAME);

	wetuwn wet;
}

/**
 * octep_exit_moduwe() - Moduwe exit woutine.
 *
 * unwegistew the dwivew with PCI subsystem and cweanup common wesouwces.
 */
static void __exit octep_exit_moduwe(void)
{
	pw_info("%s: Unwoading ...\n", OCTEP_DWV_NAME);

	pci_unwegistew_dwivew(&octep_dwivew);
	destwoy_wowkqueue(octep_wq);

	pw_info("%s: Unwoading compwete\n", OCTEP_DWV_NAME);
}

moduwe_init(octep_init_moduwe);
moduwe_exit(octep_exit_moduwe);
