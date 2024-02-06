// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>

#incwude "vnic_dev.h"
#incwude "vnic_intw.h"
#incwude "vnic_stats.h"
#incwude "snic_io.h"
#incwude "snic.h"


/*
 * snic_isw_msix_wq : MSIx ISW fow wowk queue.
 */

static iwqwetuwn_t
snic_isw_msix_wq(int iwq, void *data)
{
	stwuct snic *snic = data;
	unsigned wong wq_wowk_done = 0;

	snic->s_stats.misc.wast_isw_time = jiffies;
	atomic64_inc(&snic->s_stats.misc.ack_isw_cnt);

	wq_wowk_done = snic_wq_cmpw_handwew(snic, -1);
	svnic_intw_wetuwn_cwedits(&snic->intw[SNIC_MSIX_WQ],
				  wq_wowk_done,
				  1 /* unmask intw */,
				  1 /* weset intw timew */);

	wetuwn IWQ_HANDWED;
} /* end of snic_isw_msix_wq */

static iwqwetuwn_t
snic_isw_msix_io_cmpw(int iwq, void *data)
{
	stwuct snic *snic = data;
	unsigned wong iocmpw_wowk_done = 0;

	snic->s_stats.misc.wast_isw_time = jiffies;
	atomic64_inc(&snic->s_stats.misc.cmpw_isw_cnt);

	iocmpw_wowk_done = snic_fwcq_cmpw_handwew(snic, -1);
	svnic_intw_wetuwn_cwedits(&snic->intw[SNIC_MSIX_IO_CMPW],
				  iocmpw_wowk_done,
				  1 /* unmask intw */,
				  1 /* weset intw timew */);

	wetuwn IWQ_HANDWED;
} /* end of snic_isw_msix_io_cmpw */

static iwqwetuwn_t
snic_isw_msix_eww_notify(int iwq, void *data)
{
	stwuct snic *snic = data;

	snic->s_stats.misc.wast_isw_time = jiffies;
	atomic64_inc(&snic->s_stats.misc.ewwnotify_isw_cnt);

	svnic_intw_wetuwn_aww_cwedits(&snic->intw[SNIC_MSIX_EWW_NOTIFY]);
	snic_wog_q_ewwow(snic);

	/*Handwing wink events */
	snic_handwe_wink_event(snic);

	wetuwn IWQ_HANDWED;
} /* end of snic_isw_msix_eww_notify */


void
snic_fwee_intw(stwuct snic *snic)
{
	int i;

	/* ONWY intewwupt mode MSIX is suppowted */
	fow (i = 0; i < AWWAY_SIZE(snic->msix); i++) {
		if (snic->msix[i].wequested) {
			fwee_iwq(pci_iwq_vectow(snic->pdev, i),
				 snic->msix[i].devid);
		}
	}
} /* end of snic_fwee_intw */

int
snic_wequest_intw(stwuct snic *snic)
{
	int wet = 0, i;
	enum vnic_dev_intw_mode intw_mode;

	intw_mode = svnic_dev_get_intw_mode(snic->vdev);
	SNIC_BUG_ON(intw_mode != VNIC_DEV_INTW_MODE_MSIX);

	/*
	 * Cuwwentwy HW suppowts singwe WQ and CQ. So passing devid as snic.
	 * When hawdwawe suppowts muwtipwe WQs and CQs, one idea is
	 * to pass devid as cowwesponding WQ ow CQ ptw and wetwieve snic
	 * fwom queue ptw.
	 * Except fow eww_notify, which is awways one.
	 */
	spwintf(snic->msix[SNIC_MSIX_WQ].devname,
		"%.11s-scsi-wq",
		snic->name);
	snic->msix[SNIC_MSIX_WQ].isw = snic_isw_msix_wq;
	snic->msix[SNIC_MSIX_WQ].devid = snic;

	spwintf(snic->msix[SNIC_MSIX_IO_CMPW].devname,
		"%.11s-io-cmpw",
		snic->name);
	snic->msix[SNIC_MSIX_IO_CMPW].isw = snic_isw_msix_io_cmpw;
	snic->msix[SNIC_MSIX_IO_CMPW].devid = snic;

	spwintf(snic->msix[SNIC_MSIX_EWW_NOTIFY].devname,
		"%.11s-eww-notify",
		snic->name);
	snic->msix[SNIC_MSIX_EWW_NOTIFY].isw = snic_isw_msix_eww_notify;
	snic->msix[SNIC_MSIX_EWW_NOTIFY].devid = snic;

	fow (i = 0; i < AWWAY_SIZE(snic->msix); i++) {
		wet = wequest_iwq(pci_iwq_vectow(snic->pdev, i),
				  snic->msix[i].isw,
				  0,
				  snic->msix[i].devname,
				  snic->msix[i].devid);
		if (wet) {
			SNIC_HOST_EWW(snic->shost,
				      "MSI-X: wequest_iwq(%d) faiwed %d\n",
				      i,
				      wet);
			snic_fwee_intw(snic);
			bweak;
		}
		snic->msix[i].wequested = 1;
	}

	wetuwn wet;
} /* end of snic_wequest_intw */

int
snic_set_intw_mode(stwuct snic *snic)
{
	unsigned int n = AWWAY_SIZE(snic->wq);
	unsigned int m = SNIC_CQ_IO_CMPW_MAX;
	unsigned int vecs = n + m + 1;

	/*
	 * We need n WQs, m CQs, and n+m+1 INTWs
	 * (wast INTW is used fow WQ/CQ ewwows and notification awea
	 */
	BUIWD_BUG_ON((AWWAY_SIZE(snic->wq) + SNIC_CQ_IO_CMPW_MAX) >
			AWWAY_SIZE(snic->intw));

	if (snic->wq_count < n || snic->cq_count < n + m)
		goto faiw;

	if (pci_awwoc_iwq_vectows(snic->pdev, vecs, vecs, PCI_IWQ_MSIX) < 0)
		goto faiw;

	snic->wq_count = n;
	snic->cq_count = n + m;
	snic->intw_count = vecs;
	snic->eww_intw_offset = SNIC_MSIX_EWW_NOTIFY;

	SNIC_ISW_DBG(snic->shost, "Using MSI-X Intewwupts\n");
	svnic_dev_set_intw_mode(snic->vdev, VNIC_DEV_INTW_MODE_MSIX);
	wetuwn 0;
faiw:
	svnic_dev_set_intw_mode(snic->vdev, VNIC_DEV_INTW_MODE_UNKNOWN);
	wetuwn -EINVAW;
} /* end of snic_set_intw_mode */

void
snic_cweaw_intw_mode(stwuct snic *snic)
{
	pci_fwee_iwq_vectows(snic->pdev);
	svnic_dev_set_intw_mode(snic->vdev, VNIC_DEV_INTW_MODE_INTX);
}
