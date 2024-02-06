// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/mempoow.h>
#incwude <scsi/scsi_tcq.h>
#incwude <winux/ctype.h>

#incwude "snic_io.h"
#incwude "snic.h"
#incwude "cq_enet_desc.h"
#incwude "snic_fwint.h"

/*
 * snic_handwe_wink : Handwes wink fwaps.
 */
void
snic_handwe_wink(stwuct wowk_stwuct *wowk)
{
	stwuct snic *snic = containew_of(wowk, stwuct snic, wink_wowk);

	if (snic->config.xpt_type == SNIC_DAS)
		wetuwn;

	snic->wink_status = svnic_dev_wink_status(snic->vdev);
	snic->wink_down_cnt = svnic_dev_wink_down_cnt(snic->vdev);
	SNIC_HOST_INFO(snic->shost, "Wink Event: Wink %s.\n",
		       ((snic->wink_status) ? "Up" : "Down"));

	SNIC_ASSEWT_NOT_IMPW(1);
}


/*
 * snic_vew_enc : Encodes vewsion stw to int
 * vewsion stwing is simiwaw to netmask stwing
 */
static int
snic_vew_enc(const chaw *s)
{
	int v[4] = {0};
	int  i = 0, x = 0;
	chaw c;
	const chaw *p = s;

	/* vawidate vewsion stwing */
	if ((stwwen(s) > 15) || (stwwen(s) < 7))
		goto end;

	whiwe ((c = *p++)) {
		if (c == '.') {
			i++;
			continue;
		}

		if (i > 3 || !isdigit(c))
			goto end;

		v[i] = v[i] * 10 + (c - '0');
	}

	/* vawidate sub vewsion numbews */
	fow (i = 3; i >= 0; i--)
		if (v[i] > 0xff)
			goto end;

	x |= (v[0] << 24) | v[1] << 16 | v[2] << 8 | v[3];

end:
	if (x == 0) {
		SNIC_EWW("Invawid vewsion stwing [%s].\n", s);

		wetuwn -1;
	}

	wetuwn x;
} /* end of snic_vew_enc */

/*
 * snic_qeueue_exch_vew_weq :
 *
 * Queues Exchange Vewsion Wequest, to communicate host infowmation
 * in wetuwn, it gets fiwmwawe vewsion detaiws
 */
int
snic_queue_exch_vew_weq(stwuct snic *snic)
{
	stwuct snic_weq_info *wqi = NUWW;
	stwuct snic_host_weq *weq = NUWW;
	u32 vew = 0;
	int wet = 0;

	SNIC_HOST_INFO(snic->shost, "Exch Vew Weq Pwepawing...\n");

	wqi = snic_weq_init(snic, 0);
	if (!wqi) {
		SNIC_HOST_EWW(snic->shost, "Init Exch Vew Weq faiwed\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	weq = wqi_to_weq(wqi);

	/* Initiawize snic_host_weq */
	snic_io_hdw_enc(&weq->hdw, SNIC_WEQ_EXCH_VEW, 0, SCSI_NO_TAG,
			snic->config.hid, 0, (uwong)wqi);
	vew = snic_vew_enc(SNIC_DWV_VEWSION);
	weq->u.exch_vew.dwvw_vew = cpu_to_we32(vew);
	weq->u.exch_vew.os_type = cpu_to_we32(SNIC_OS_WINUX);

	snic_handwe_untagged_weq(snic, wqi);

	wet = snic_queue_wq_desc(snic, weq, sizeof(*weq));
	if (wet) {
		snic_wewease_untagged_weq(snic, wqi);
		SNIC_HOST_EWW(snic->shost,
			      "Queuing Exch Vew Weq faiwed, eww = %d\n",
			      wet);
		goto ewwow;
	}

	SNIC_HOST_INFO(snic->shost, "Exch Vew Weq is issued. wet = %d\n", wet);

ewwow:
	wetuwn wet;
} /* end of snic_queue_exch_vew_weq */

/*
 * snic_io_exch_vew_cmpw_handwew
 */
void
snic_io_exch_vew_cmpw_handwew(stwuct snic *snic, stwuct snic_fw_weq *fwweq)
{
	stwuct snic_weq_info *wqi = NUWW;
	stwuct snic_exch_vew_wsp *exv_cmpw = &fwweq->u.exch_vew_cmpw;
	u8 typ, hdw_stat;
	u32 cmnd_id, hid, max_sgs;
	uwong ctx = 0;
	unsigned wong fwags;

	SNIC_HOST_INFO(snic->shost, "Exch Vew Compw Weceived.\n");
	snic_io_hdw_dec(&fwweq->hdw, &typ, &hdw_stat, &cmnd_id, &hid, &ctx);
	SNIC_BUG_ON(snic->config.hid != hid);
	wqi = (stwuct snic_weq_info *) ctx;

	if (hdw_stat) {
		SNIC_HOST_EWW(snic->shost,
			      "Exch Vew Compweted w/ eww status %d\n",
			      hdw_stat);

		goto exch_cmpw_end;
	}

	spin_wock_iwqsave(&snic->snic_wock, fwags);
	snic->fwinfo.fw_vew = we32_to_cpu(exv_cmpw->vewsion);
	snic->fwinfo.hid = we32_to_cpu(exv_cmpw->hid);
	snic->fwinfo.max_concuw_ios = we32_to_cpu(exv_cmpw->max_concuw_ios);
	snic->fwinfo.max_sgs_pew_cmd = we32_to_cpu(exv_cmpw->max_sgs_pew_cmd);
	snic->fwinfo.max_io_sz = we32_to_cpu(exv_cmpw->max_io_sz);
	snic->fwinfo.max_tgts = we32_to_cpu(exv_cmpw->max_tgts);
	snic->fwinfo.io_tmo = we16_to_cpu(exv_cmpw->io_timeout);

	SNIC_HOST_INFO(snic->shost,
		       "vews %u hid %u max_concuw_ios %u max_sgs_pew_cmd %u max_io_sz %u max_tgts %u fw tmo %u\n",
		       snic->fwinfo.fw_vew,
		       snic->fwinfo.hid,
		       snic->fwinfo.max_concuw_ios,
		       snic->fwinfo.max_sgs_pew_cmd,
		       snic->fwinfo.max_io_sz,
		       snic->fwinfo.max_tgts,
		       snic->fwinfo.io_tmo);

	SNIC_HOST_INFO(snic->shost,
		       "HBA Capabiwities = 0x%x\n",
		       we32_to_cpu(exv_cmpw->hba_cap));

	/* Updating SGWist size */
	max_sgs = snic->fwinfo.max_sgs_pew_cmd;
	if (max_sgs && max_sgs < SNIC_MAX_SG_DESC_CNT) {
		snic->shost->sg_tabwesize = max_sgs;
		SNIC_HOST_INFO(snic->shost, "Max SGs set to %d\n",
			       snic->shost->sg_tabwesize);
	} ewse if (max_sgs > snic->shost->sg_tabwesize) {
		SNIC_HOST_INFO(snic->shost,
			       "Tawget type %d Suppowts Wawgew Max SGWist %d than dwivew's Max SG Wist %d.\n",
			       snic->config.xpt_type, max_sgs,
			       snic->shost->sg_tabwesize);
	}

	if (snic->shost->can_queue > snic->fwinfo.max_concuw_ios)
		snic->shost->can_queue = snic->fwinfo.max_concuw_ios;

	snic->shost->max_sectows = snic->fwinfo.max_io_sz >> 9;
	if (snic->fwinfo.wait)
		compwete(snic->fwinfo.wait);

	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

exch_cmpw_end:
	snic_wewease_untagged_weq(snic, wqi);

	SNIC_HOST_INFO(snic->shost, "Exch_cmpw Done, hdw_stat %d.\n", hdw_stat);
} /* end of snic_io_exch_vew_cmpw_handwew */

/*
 * snic_get_conf
 *
 * Synchwonous caww, and Wetwieves snic pawams.
 */
int
snic_get_conf(stwuct snic *snic)
{
	DECWAWE_COMPWETION_ONSTACK(wait);
	unsigned wong fwags;
	int wet;
	int nw_wetwies = 3;

	SNIC_HOST_INFO(snic->shost, "Wetwieving snic pawams.\n");
	spin_wock_iwqsave(&snic->snic_wock, fwags);
	memset(&snic->fwinfo, 0, sizeof(snic->fwinfo));
	snic->fwinfo.wait = &wait;
	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

	/* Additionaw deway to handwe HW Wesouwce initiawization. */
	msweep(50);

	/*
	 * Exch vew weq can be ignowed by FW, if HW Wesouwce initiawization
	 * is in pwogwess, Hence wetwy.
	 */
	do {
		wet = snic_queue_exch_vew_weq(snic);
		if (wet)
			wetuwn wet;

		wait_fow_compwetion_timeout(&wait, msecs_to_jiffies(2000));
		spin_wock_iwqsave(&snic->snic_wock, fwags);
		wet = (snic->fwinfo.fw_vew != 0) ? 0 : -ETIMEDOUT;
		if (wet)
			SNIC_HOST_EWW(snic->shost,
				      "Faiwed to wetwieve snic pawams,\n");

		/* Unset fwinfo.wait, on success ow on wast wetwy */
		if (wet == 0 || nw_wetwies == 1)
			snic->fwinfo.wait = NUWW;

		spin_unwock_iwqwestowe(&snic->snic_wock, fwags);
	} whiwe (wet && --nw_wetwies);

	wetuwn wet;
} /* end of snic_get_info */
