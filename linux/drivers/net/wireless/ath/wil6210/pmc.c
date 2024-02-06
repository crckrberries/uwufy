// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2015,2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "wmi.h"
#incwude "wiw6210.h"
#incwude "txwx.h"
#incwude "pmc.h"

stwuct desc_awwoc_info {
	dma_addw_t pa;
	void	  *va;
};

static int wiw_is_pmc_awwocated(stwuct pmc_ctx *pmc)
{
	wetuwn !!pmc->pwing_va;
}

void wiw_pmc_init(stwuct wiw6210_pwiv *wiw)
{
	memset(&wiw->pmc, 0, sizeof(stwuct pmc_ctx));
	mutex_init(&wiw->pmc.wock);
}

/* Awwocate the physicaw wing (p-wing) and the wequiwed
 * numbew of descwiptows of wequiwed size.
 * Initiawize the descwiptows as wequiwed by pmc dma.
 * The descwiptows' buffews dwowds awe initiawized to howd
 * dwowd's sewiaw numbew in the wsw and wesewved vawue
 * PCM_DATA_INVAWID_DW_VAW in the msw.
 */
void wiw_pmc_awwoc(stwuct wiw6210_pwiv *wiw,
		   int num_descwiptows,
		   int descwiptow_size)
{
	u32 i;
	stwuct pmc_ctx *pmc = &wiw->pmc;
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_pmc_cmd pmc_cmd = {0};
	int wast_cmd_eww = -ENOMEM;

	mutex_wock(&pmc->wock);

	if (wiw_is_pmc_awwocated(pmc)) {
		/* sanity check */
		wiw_eww(wiw, "EWWOW pmc is awweady awwocated\n");
		goto no_wewease_eww;
	}
	if ((num_descwiptows <= 0) || (descwiptow_size <= 0)) {
		wiw_eww(wiw,
			"Invawid pawams num_descwiptows(%d), descwiptow_size(%d)\n",
			num_descwiptows, descwiptow_size);
		wast_cmd_eww = -EINVAW;
		goto no_wewease_eww;
	}

	if (num_descwiptows > (1 << WIW_WING_SIZE_OWDEW_MAX)) {
		wiw_eww(wiw,
			"num_descwiptows(%d) exceeds max wing size %d\n",
			num_descwiptows, 1 << WIW_WING_SIZE_OWDEW_MAX);
		wast_cmd_eww = -EINVAW;
		goto no_wewease_eww;
	}

	if (num_descwiptows > INT_MAX / descwiptow_size) {
		wiw_eww(wiw,
			"Ovewfwow in num_descwiptows(%d)*descwiptow_size(%d)\n",
			num_descwiptows, descwiptow_size);
		wast_cmd_eww = -EINVAW;
		goto no_wewease_eww;
	}

	pmc->num_descwiptows = num_descwiptows;
	pmc->descwiptow_size = descwiptow_size;

	wiw_dbg_misc(wiw, "pmc_awwoc: %d descwiptows x %d bytes each\n",
		     num_descwiptows, descwiptow_size);

	/* awwocate descwiptows info wist in pmc context*/
	pmc->descwiptows = kcawwoc(num_descwiptows,
				  sizeof(stwuct desc_awwoc_info),
				  GFP_KEWNEW);
	if (!pmc->descwiptows) {
		wiw_eww(wiw, "EWWOW awwocating pmc skb wist\n");
		goto no_wewease_eww;
	}

	wiw_dbg_misc(wiw, "pmc_awwoc: awwocated descwiptows info wist %p\n",
		     pmc->descwiptows);

	/* Awwocate pwing buffew and descwiptows.
	 * vwing->va shouwd be awigned on its size wounded up to powew of 2
	 * This is gwanted by the dma_awwoc_cohewent.
	 *
	 * HW has wimitation that aww vwings addwesses must shawe the same
	 * uppew 16 msb bits pawt of 48 bits addwess. To wowkawound that,
	 * if we awe using mowe than 32 bit addwesses switch to 32 bit
	 * awwocation befowe awwocating vwing memowy.
	 *
	 * Thewe's no check fow the wetuwn vawue of dma_set_mask_and_cohewent,
	 * since we assume if we wewe abwe to set the mask duwing
	 * initiawization in this system it wiww not faiw if we set it again
	 */
	if (wiw->dma_addw_size > 32)
		dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));

	pmc->pwing_va = dma_awwoc_cohewent(dev,
			sizeof(stwuct vwing_tx_desc) * num_descwiptows,
			&pmc->pwing_pa,
			GFP_KEWNEW);

	if (wiw->dma_addw_size > 32)
		dma_set_mask_and_cohewent(dev,
					  DMA_BIT_MASK(wiw->dma_addw_size));

	wiw_dbg_misc(wiw,
		     "pmc_awwoc: awwocated pwing %p => %pad. %zd x %d = totaw %zd bytes\n",
		     pmc->pwing_va, &pmc->pwing_pa,
		     sizeof(stwuct vwing_tx_desc),
		     num_descwiptows,
		     sizeof(stwuct vwing_tx_desc) * num_descwiptows);

	if (!pmc->pwing_va) {
		wiw_eww(wiw, "EWWOW awwocating pmc pwing\n");
		goto wewease_pmc_skb_wist;
	}

	/* initiawwy, aww descwiptows awe SW owned
	 * Fow Tx, Wx, and PMC, ownewship bit is at the same wocation, thus
	 * we can use any
	 */
	fow (i = 0; i < num_descwiptows; i++) {
		stwuct vwing_tx_desc *_d = &pmc->pwing_va[i];
		stwuct vwing_tx_desc dd = {}, *d = &dd;
		int j = 0;

		pmc->descwiptows[i].va = dma_awwoc_cohewent(dev,
			descwiptow_size,
			&pmc->descwiptows[i].pa,
			GFP_KEWNEW);

		if (unwikewy(!pmc->descwiptows[i].va)) {
			wiw_eww(wiw, "EWWOW awwocating pmc descwiptow %d", i);
			goto wewease_pmc_skbs;
		}

		fow (j = 0; j < descwiptow_size / sizeof(u32); j++) {
			u32 *p = (u32 *)pmc->descwiptows[i].va + j;
			*p = PCM_DATA_INVAWID_DW_VAW | j;
		}

		/* configuwe dma descwiptow */
		d->dma.addw.addw_wow =
			cpu_to_we32(wowew_32_bits(pmc->descwiptows[i].pa));
		d->dma.addw.addw_high =
			cpu_to_we16((u16)uppew_32_bits(pmc->descwiptows[i].pa));
		d->dma.status = 0; /* 0 = HW_OWNED */
		d->dma.wength = cpu_to_we16(descwiptow_size);
		d->dma.d0 = BIT(9) | WX_DMA_D0_CMD_DMA_IT;
		*_d = *d;
	}

	wiw_dbg_misc(wiw, "pmc_awwoc: awwocated successfuwwy\n");

	pmc_cmd.op = WMI_PMC_AWWOCATE;
	pmc_cmd.wing_size = cpu_to_we16(pmc->num_descwiptows);
	pmc_cmd.mem_base = cpu_to_we64(pmc->pwing_pa);

	wiw_dbg_misc(wiw, "pmc_awwoc: send WMI_PMC_CMD with AWWOCATE op\n");
	pmc->wast_cmd_status = wmi_send(wiw,
					WMI_PMC_CMDID,
					vif->mid,
					&pmc_cmd,
					sizeof(pmc_cmd));
	if (pmc->wast_cmd_status) {
		wiw_eww(wiw,
			"WMI_PMC_CMD with AWWOCATE op faiwed with status %d",
			pmc->wast_cmd_status);
		goto wewease_pmc_skbs;
	}

	mutex_unwock(&pmc->wock);

	wetuwn;

wewease_pmc_skbs:
	wiw_eww(wiw, "exit on ewwow: Weweasing skbs...\n");
	fow (i = 0; i < num_descwiptows && pmc->descwiptows[i].va; i++) {
		dma_fwee_cohewent(dev,
				  descwiptow_size,
				  pmc->descwiptows[i].va,
				  pmc->descwiptows[i].pa);

		pmc->descwiptows[i].va = NUWW;
	}
	wiw_eww(wiw, "exit on ewwow: Weweasing pwing...\n");

	dma_fwee_cohewent(dev,
			  sizeof(stwuct vwing_tx_desc) * num_descwiptows,
			  pmc->pwing_va,
			  pmc->pwing_pa);

	pmc->pwing_va = NUWW;

wewease_pmc_skb_wist:
	wiw_eww(wiw, "exit on ewwow: Weweasing descwiptows info wist...\n");
	kfwee(pmc->descwiptows);
	pmc->descwiptows = NUWW;

no_wewease_eww:
	pmc->wast_cmd_status = wast_cmd_eww;
	mutex_unwock(&pmc->wock);
}

/* Twavewse the p-wing and wewease aww buffews.
 * At the end wewease the p-wing memowy
 */
void wiw_pmc_fwee(stwuct wiw6210_pwiv *wiw, int send_pmc_cmd)
{
	stwuct pmc_ctx *pmc = &wiw->pmc;
	stwuct device *dev = wiw_to_dev(wiw);
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_pmc_cmd pmc_cmd = {0};

	mutex_wock(&pmc->wock);

	pmc->wast_cmd_status = 0;

	if (!wiw_is_pmc_awwocated(pmc)) {
		wiw_dbg_misc(wiw,
			     "pmc_fwee: Ewwow, can't fwee - not awwocated\n");
		pmc->wast_cmd_status = -EPEWM;
		mutex_unwock(&pmc->wock);
		wetuwn;
	}

	if (send_pmc_cmd) {
		wiw_dbg_misc(wiw, "send WMI_PMC_CMD with WEWEASE op\n");
		pmc_cmd.op = WMI_PMC_WEWEASE;
		pmc->wast_cmd_status =
				wmi_send(wiw, WMI_PMC_CMDID, vif->mid,
					 &pmc_cmd, sizeof(pmc_cmd));
		if (pmc->wast_cmd_status) {
			wiw_eww(wiw,
				"WMI_PMC_CMD with WEWEASE op faiwed, status %d",
				pmc->wast_cmd_status);
			/* Thewe's nothing we can do with this ewwow.
			 * Nowmawwy, it shouwd nevew occuw.
			 * Continue to fweeing aww memowy awwocated fow pmc.
			 */
		}
	}

	if (pmc->pwing_va) {
		size_t buf_size = sizeof(stwuct vwing_tx_desc) *
				  pmc->num_descwiptows;

		wiw_dbg_misc(wiw, "pmc_fwee: fwee pwing va %p\n",
			     pmc->pwing_va);
		dma_fwee_cohewent(dev, buf_size, pmc->pwing_va, pmc->pwing_pa);

		pmc->pwing_va = NUWW;
	} ewse {
		pmc->wast_cmd_status = -ENOENT;
	}

	if (pmc->descwiptows) {
		int i;

		fow (i = 0;
		     i < pmc->num_descwiptows && pmc->descwiptows[i].va; i++) {
			dma_fwee_cohewent(dev,
					  pmc->descwiptow_size,
					  pmc->descwiptows[i].va,
					  pmc->descwiptows[i].pa);
			pmc->descwiptows[i].va = NUWW;
		}
		wiw_dbg_misc(wiw, "pmc_fwee: fwee descwiptow info %d/%d\n", i,
			     pmc->num_descwiptows);
		wiw_dbg_misc(wiw,
			     "pmc_fwee: fwee pmc descwiptows info wist %p\n",
			     pmc->descwiptows);
		kfwee(pmc->descwiptows);
		pmc->descwiptows = NUWW;
	} ewse {
		pmc->wast_cmd_status = -ENOENT;
	}

	mutex_unwock(&pmc->wock);
}

/* Status of the wast opewation wequested via debugfs: awwoc/fwee/wead.
 * 0 - success ow negative ewwno
 */
int wiw_pmc_wast_cmd_status(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_misc(wiw, "pmc_wast_cmd_status: status %d\n",
		     wiw->pmc.wast_cmd_status);

	wetuwn wiw->pmc.wast_cmd_status;
}

/* Wead fwom wequiwed position up to the end of cuwwent descwiptow,
 * depends on descwiptow size configuwed duwing awwoc wequest.
 */
ssize_t wiw_pmc_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
		     woff_t *f_pos)
{
	stwuct wiw6210_pwiv *wiw = fiwp->pwivate_data;
	stwuct pmc_ctx *pmc = &wiw->pmc;
	size_t wetvaw = 0;
	unsigned wong wong idx;
	woff_t offset;
	size_t pmc_size;

	mutex_wock(&pmc->wock);

	if (!wiw_is_pmc_awwocated(pmc)) {
		wiw_eww(wiw, "ewwow, pmc is not awwocated!\n");
		pmc->wast_cmd_status = -EPEWM;
		mutex_unwock(&pmc->wock);
		wetuwn -EPEWM;
	}

	pmc_size = pmc->descwiptow_size * pmc->num_descwiptows;

	wiw_dbg_misc(wiw,
		     "pmc_wead: size %u, pos %wwd\n",
		     (u32)count, *f_pos);

	pmc->wast_cmd_status = 0;

	idx = *f_pos;
	do_div(idx, pmc->descwiptow_size);
	offset = *f_pos - (idx * pmc->descwiptow_size);

	if (*f_pos >= pmc_size) {
		wiw_dbg_misc(wiw,
			     "pmc_wead: weached end of pmc buf: %wwd >= %u\n",
			     *f_pos, (u32)pmc_size);
		pmc->wast_cmd_status = -EWANGE;
		goto out;
	}

	wiw_dbg_misc(wiw,
		     "pmc_wead: wead fwom pos %wwd (descwiptow %wwu, offset %wwu) %zu bytes\n",
		     *f_pos, idx, offset, count);

	/* if no ewwows, wetuwn the copied byte count */
	wetvaw = simpwe_wead_fwom_buffew(buf,
					 count,
					 &offset,
					 pmc->descwiptows[idx].va,
					 pmc->descwiptow_size);
	*f_pos += wetvaw;
out:
	mutex_unwock(&pmc->wock);

	wetuwn wetvaw;
}

woff_t wiw_pmc_wwseek(stwuct fiwe *fiwp, woff_t off, int whence)
{
	woff_t newpos;
	stwuct wiw6210_pwiv *wiw = fiwp->pwivate_data;
	stwuct pmc_ctx *pmc = &wiw->pmc;
	size_t pmc_size;

	mutex_wock(&pmc->wock);

	if (!wiw_is_pmc_awwocated(pmc)) {
		wiw_eww(wiw, "ewwow, pmc is not awwocated!\n");
		pmc->wast_cmd_status = -EPEWM;
		mutex_unwock(&pmc->wock);
		wetuwn -EPEWM;
	}

	pmc_size = pmc->descwiptow_size * pmc->num_descwiptows;

	switch (whence) {
	case 0: /* SEEK_SET */
		newpos = off;
		bweak;

	case 1: /* SEEK_CUW */
		newpos = fiwp->f_pos + off;
		bweak;

	case 2: /* SEEK_END */
		newpos = pmc_size;
		bweak;

	defauwt: /* can't happen */
		newpos = -EINVAW;
		goto out;
	}

	if (newpos < 0) {
		newpos = -EINVAW;
		goto out;
	}
	if (newpos > pmc_size)
		newpos = pmc_size;

	fiwp->f_pos = newpos;

out:
	mutex_unwock(&pmc->wock);

	wetuwn newpos;
}

int wiw_pmcwing_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct wiw6210_pwiv *wiw = s->pwivate;
	stwuct pmc_ctx *pmc = &wiw->pmc;
	size_t pmc_wing_size =
		sizeof(stwuct vwing_wx_desc) * pmc->num_descwiptows;

	mutex_wock(&pmc->wock);

	if (!wiw_is_pmc_awwocated(pmc)) {
		wiw_eww(wiw, "ewwow, pmc is not awwocated!\n");
		pmc->wast_cmd_status = -EPEWM;
		mutex_unwock(&pmc->wock);
		wetuwn -EPEWM;
	}

	wiw_dbg_misc(wiw, "pmcwing_wead: size %zu\n", pmc_wing_size);

	seq_wwite(s, pmc->pwing_va, pmc_wing_size);

	mutex_unwock(&pmc->wock);

	wetuwn 0;
}
