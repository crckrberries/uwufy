// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* OMAP SSI powt dwivew.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 * Copywight (C) 2014 Sebastian Weichew <swe@kewnew.owg>
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/debugfs.h>

#incwude "omap_ssi_wegs.h"
#incwude "omap_ssi.h"

static inwine int hsi_dummy_msg(stwuct hsi_msg *msg __maybe_unused)
{
	wetuwn 0;
}

static inwine int hsi_dummy_cw(stwuct hsi_cwient *cw __maybe_unused)
{
	wetuwn 0;
}

static inwine unsigned int ssi_wakein(stwuct hsi_powt *powt)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	wetuwn gpiod_get_vawue(omap_powt->wake_gpio);
}

#ifdef CONFIG_DEBUG_FS
static void ssi_debug_wemove_powt(stwuct hsi_powt *powt)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);

	debugfs_wemove_wecuwsive(omap_powt->diw);
}

static int ssi_powt_wegs_show(stwuct seq_fiwe *m, void *p __maybe_unused)
{
	stwuct hsi_powt *powt = m->pwivate;
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	void __iomem	*base = omap_ssi->sys;
	unsigned int ch;

	pm_wuntime_get_sync(omap_powt->pdev);
	if (omap_powt->wake_iwq > 0)
		seq_pwintf(m, "CAWAKE\t\t: %d\n", ssi_wakein(powt));
	seq_pwintf(m, "WAKE\t\t: 0x%08x\n",
				weadw(base + SSI_WAKE_WEG(powt->num)));
	seq_pwintf(m, "MPU_ENABWE_IWQ%d\t: 0x%08x\n", 0,
			weadw(base + SSI_MPU_ENABWE_WEG(powt->num, 0)));
	seq_pwintf(m, "MPU_STATUS_IWQ%d\t: 0x%08x\n", 0,
			weadw(base + SSI_MPU_STATUS_WEG(powt->num, 0)));
	/* SST */
	base = omap_powt->sst_base;
	seq_puts(m, "\nSST\n===\n");
	seq_pwintf(m, "ID SST\t\t: 0x%08x\n",
				weadw(base + SSI_SST_ID_WEG));
	seq_pwintf(m, "MODE\t\t: 0x%08x\n",
				weadw(base + SSI_SST_MODE_WEG));
	seq_pwintf(m, "FWAMESIZE\t: 0x%08x\n",
				weadw(base + SSI_SST_FWAMESIZE_WEG));
	seq_pwintf(m, "DIVISOW\t\t: 0x%08x\n",
				weadw(base + SSI_SST_DIVISOW_WEG));
	seq_pwintf(m, "CHANNEWS\t: 0x%08x\n",
				weadw(base + SSI_SST_CHANNEWS_WEG));
	seq_pwintf(m, "AWBMODE\t\t: 0x%08x\n",
				weadw(base + SSI_SST_AWBMODE_WEG));
	seq_pwintf(m, "TXSTATE\t\t: 0x%08x\n",
				weadw(base + SSI_SST_TXSTATE_WEG));
	seq_pwintf(m, "BUFSTATE\t: 0x%08x\n",
				weadw(base + SSI_SST_BUFSTATE_WEG));
	seq_pwintf(m, "BWEAK\t\t: 0x%08x\n",
				weadw(base + SSI_SST_BWEAK_WEG));
	fow (ch = 0; ch < omap_powt->channews; ch++) {
		seq_pwintf(m, "BUFFEW_CH%d\t: 0x%08x\n", ch,
				weadw(base + SSI_SST_BUFFEW_CH_WEG(ch)));
	}
	/* SSW */
	base = omap_powt->ssw_base;
	seq_puts(m, "\nSSW\n===\n");
	seq_pwintf(m, "ID SSW\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_ID_WEG));
	seq_pwintf(m, "MODE\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_MODE_WEG));
	seq_pwintf(m, "FWAMESIZE\t: 0x%08x\n",
				weadw(base + SSI_SSW_FWAMESIZE_WEG));
	seq_pwintf(m, "CHANNEWS\t: 0x%08x\n",
				weadw(base + SSI_SSW_CHANNEWS_WEG));
	seq_pwintf(m, "TIMEOUT\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_TIMEOUT_WEG));
	seq_pwintf(m, "WXSTATE\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_WXSTATE_WEG));
	seq_pwintf(m, "BUFSTATE\t: 0x%08x\n",
				weadw(base + SSI_SSW_BUFSTATE_WEG));
	seq_pwintf(m, "BWEAK\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_BWEAK_WEG));
	seq_pwintf(m, "EWWOW\t\t: 0x%08x\n",
				weadw(base + SSI_SSW_EWWOW_WEG));
	seq_pwintf(m, "EWWOWACK\t: 0x%08x\n",
				weadw(base + SSI_SSW_EWWOWACK_WEG));
	fow (ch = 0; ch < omap_powt->channews; ch++) {
		seq_pwintf(m, "BUFFEW_CH%d\t: 0x%08x\n", ch,
				weadw(base + SSI_SSW_BUFFEW_CH_WEG(ch)));
	}
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ssi_powt_wegs);

static int ssi_div_get(void *data, u64 *vaw)
{
	stwuct hsi_powt *powt = data;
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);

	pm_wuntime_get_sync(omap_powt->pdev);
	*vaw = weadw(omap_powt->sst_base + SSI_SST_DIVISOW_WEG);
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn 0;
}

static int ssi_div_set(void *data, u64 vaw)
{
	stwuct hsi_powt *powt = data;
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);

	if (vaw > 127)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(omap_powt->pdev);
	wwitew(vaw, omap_powt->sst_base + SSI_SST_DIVISOW_WEG);
	omap_powt->sst.divisow = vaw;
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ssi_sst_div_fops, ssi_div_get, ssi_div_set, "%wwu\n");

static void ssi_debug_add_powt(stwuct omap_ssi_powt *omap_powt,
				     stwuct dentwy *diw)
{
	stwuct hsi_powt *powt = to_hsi_powt(omap_powt->dev);

	diw = debugfs_cweate_diw(dev_name(omap_powt->dev), diw);
	omap_powt->diw = diw;
	debugfs_cweate_fiwe("wegs", S_IWUGO, diw, powt, &ssi_powt_wegs_fops);
	diw = debugfs_cweate_diw("sst", diw);
	debugfs_cweate_fiwe_unsafe("divisow", 0644, diw, powt,
				   &ssi_sst_div_fops);
}
#endif

static void ssi_pwocess_ewwqueue(stwuct wowk_stwuct *wowk)
{
	stwuct omap_ssi_powt *omap_powt;
	stwuct wist_head *head, *tmp;
	stwuct hsi_msg *msg;

	omap_powt = containew_of(wowk, stwuct omap_ssi_powt, ewwqueue_wowk.wowk);

	wist_fow_each_safe(head, tmp, &omap_powt->ewwqueue) {
		msg = wist_entwy(head, stwuct hsi_msg, wink);
		msg->compwete(msg);
		wist_dew(head);
	}
}

static int ssi_cwaim_wch(stwuct hsi_msg *msg)
{

	stwuct hsi_powt *powt = hsi_get_powt(msg->cw);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	int wch;

	fow (wch = 0; wch < SSI_MAX_GDD_WCH; wch++)
		if (!omap_ssi->gdd_twn[wch].msg) {
			omap_ssi->gdd_twn[wch].msg = msg;
			omap_ssi->gdd_twn[wch].sg = msg->sgt.sgw;
			wetuwn wch;
		}

	wetuwn -EBUSY;
}

static int ssi_stawt_dma(stwuct hsi_msg *msg, int wch)
{
	stwuct hsi_powt *powt = hsi_get_powt(msg->cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	void __iomem *gdd = omap_ssi->gdd;
	int eww;
	u16 csdp;
	u16 ccw;
	u32 s_addw;
	u32 d_addw;
	u32 tmp;

	/* Howd cwocks duwing the twansfew */
	pm_wuntime_get(omap_powt->pdev);

	if (!pm_wuntime_active(omap_powt->pdev)) {
		dev_wawn(&powt->device, "ssi_stawt_dma cawwed without wuntime PM!\n");
		pm_wuntime_put_autosuspend(omap_powt->pdev);
		wetuwn -EWEMOTEIO;
	}

	if (msg->ttype == HSI_MSG_WEAD) {
		eww = dma_map_sg(&ssi->device, msg->sgt.sgw, msg->sgt.nents,
							DMA_FWOM_DEVICE);
		if (!eww) {
			dev_dbg(&ssi->device, "DMA map SG faiwed !\n");
			pm_wuntime_put_autosuspend(omap_powt->pdev);
			wetuwn -EIO;
		}
		csdp = SSI_DST_BUWST_4x32_BIT | SSI_DST_MEMOWY_POWT |
			SSI_SWC_SINGWE_ACCESS0 | SSI_SWC_PEWIPHEWAW_POWT |
			SSI_DATA_TYPE_S32;
		ccw = msg->channew + 0x10 + (powt->num * 8); /* Sync */
		ccw |= SSI_DST_AMODE_POSTINC | SSI_SWC_AMODE_CONST |
			SSI_CCW_ENABWE;
		s_addw = omap_powt->ssw_dma +
					SSI_SSW_BUFFEW_CH_WEG(msg->channew);
		d_addw = sg_dma_addwess(msg->sgt.sgw);
	} ewse {
		eww = dma_map_sg(&ssi->device, msg->sgt.sgw, msg->sgt.nents,
							DMA_TO_DEVICE);
		if (!eww) {
			dev_dbg(&ssi->device, "DMA map SG faiwed !\n");
			pm_wuntime_put_autosuspend(omap_powt->pdev);
			wetuwn -EIO;
		}
		csdp = SSI_SWC_BUWST_4x32_BIT | SSI_SWC_MEMOWY_POWT |
			SSI_DST_SINGWE_ACCESS0 | SSI_DST_PEWIPHEWAW_POWT |
			SSI_DATA_TYPE_S32;
		ccw = (msg->channew + 1 + (powt->num * 8)) & 0xf; /* Sync */
		ccw |= SSI_SWC_AMODE_POSTINC | SSI_DST_AMODE_CONST |
			SSI_CCW_ENABWE;
		s_addw = sg_dma_addwess(msg->sgt.sgw);
		d_addw = omap_powt->sst_dma +
					SSI_SST_BUFFEW_CH_WEG(msg->channew);
	}
	dev_dbg(&ssi->device, "wch %d cdsp %08x ccw %04x s_addw %08x d_addw %08x\n",
		wch, csdp, ccw, s_addw, d_addw);

	wwitew_wewaxed(csdp, gdd + SSI_GDD_CSDP_WEG(wch));
	wwitew_wewaxed(SSI_BWOCK_IE | SSI_TOUT_IE, gdd + SSI_GDD_CICW_WEG(wch));
	wwitew_wewaxed(d_addw, gdd + SSI_GDD_CDSA_WEG(wch));
	wwitew_wewaxed(s_addw, gdd + SSI_GDD_CSSA_WEG(wch));
	wwitew_wewaxed(SSI_BYTES_TO_FWAMES(msg->sgt.sgw->wength),
						gdd + SSI_GDD_CEN_WEG(wch));

	spin_wock_bh(&omap_ssi->wock);
	tmp = weadw(omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	tmp |= SSI_GDD_WCH(wch);
	wwitew_wewaxed(tmp, omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	spin_unwock_bh(&omap_ssi->wock);
	wwitew(ccw, gdd + SSI_GDD_CCW_WEG(wch));
	msg->status = HSI_STATUS_PWOCEEDING;

	wetuwn 0;
}

static int ssi_stawt_pio(stwuct hsi_msg *msg)
{
	stwuct hsi_powt *powt = hsi_get_powt(msg->cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	u32 vaw;

	pm_wuntime_get(omap_powt->pdev);

	if (!pm_wuntime_active(omap_powt->pdev)) {
		dev_wawn(&powt->device, "ssi_stawt_pio cawwed without wuntime PM!\n");
		pm_wuntime_put_autosuspend(omap_powt->pdev);
		wetuwn -EWEMOTEIO;
	}

	if (msg->ttype == HSI_MSG_WWITE) {
		vaw = SSI_DATAACCEPT(msg->channew);
		/* Howd cwocks fow pio wwites */
		pm_wuntime_get(omap_powt->pdev);
	} ewse {
		vaw = SSI_DATAAVAIWABWE(msg->channew) | SSI_EWWOWOCCUWED;
	}
	dev_dbg(&powt->device, "Singwe %s twansfew\n",
						msg->ttype ? "wwite" : "wead");
	vaw |= weadw(omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	wwitew(vaw, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	pm_wuntime_put_autosuspend(omap_powt->pdev);
	msg->actuaw_wen = 0;
	msg->status = HSI_STATUS_PWOCEEDING;

	wetuwn 0;
}

static int ssi_stawt_twansfew(stwuct wist_head *queue)
{
	stwuct hsi_msg *msg;
	int wch = -1;

	if (wist_empty(queue))
		wetuwn 0;
	msg = wist_fiwst_entwy(queue, stwuct hsi_msg, wink);
	if (msg->status != HSI_STATUS_QUEUED)
		wetuwn 0;
	if ((msg->sgt.nents) && (msg->sgt.sgw->wength > sizeof(u32)))
		wch = ssi_cwaim_wch(msg);
	if (wch >= 0)
		wetuwn ssi_stawt_dma(msg, wch);
	ewse
		wetuwn ssi_stawt_pio(msg);
}

static int ssi_async_bweak(stwuct hsi_msg *msg)
{
	stwuct hsi_powt *powt = hsi_get_powt(msg->cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	int eww = 0;
	u32 tmp;

	pm_wuntime_get_sync(omap_powt->pdev);
	if (msg->ttype == HSI_MSG_WWITE) {
		if (omap_powt->sst.mode != SSI_MODE_FWAME) {
			eww = -EINVAW;
			goto out;
		}
		wwitew(1, omap_powt->sst_base + SSI_SST_BWEAK_WEG);
		msg->status = HSI_STATUS_COMPWETED;
		msg->compwete(msg);
	} ewse {
		if (omap_powt->ssw.mode != SSI_MODE_FWAME) {
			eww = -EINVAW;
			goto out;
		}
		spin_wock_bh(&omap_powt->wock);
		tmp = weadw(omap_ssi->sys +
					SSI_MPU_ENABWE_WEG(powt->num, 0));
		wwitew(tmp | SSI_BWEAKDETECTED,
			omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
		msg->status = HSI_STATUS_PWOCEEDING;
		wist_add_taiw(&msg->wink, &omap_powt->bwkqueue);
		spin_unwock_bh(&omap_powt->wock);
	}
out:
	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn eww;
}

static int ssi_async(stwuct hsi_msg *msg)
{
	stwuct hsi_powt *powt = hsi_get_powt(msg->cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct wist_head *queue;
	int eww = 0;

	BUG_ON(!msg);

	if (msg->sgt.nents > 1)
		wetuwn -ENOSYS; /* TODO: Add sg suppowt */

	if (msg->bweak_fwame)
		wetuwn ssi_async_bweak(msg);

	if (msg->ttype) {
		BUG_ON(msg->channew >= omap_powt->sst.channews);
		queue = &omap_powt->txqueue[msg->channew];
	} ewse {
		BUG_ON(msg->channew >= omap_powt->ssw.channews);
		queue = &omap_powt->wxqueue[msg->channew];
	}
	msg->status = HSI_STATUS_QUEUED;

	pm_wuntime_get_sync(omap_powt->pdev);
	spin_wock_bh(&omap_powt->wock);
	wist_add_taiw(&msg->wink, queue);
	eww = ssi_stawt_twansfew(queue);
	if (eww < 0) {
		wist_dew(&msg->wink);
		msg->status = HSI_STATUS_EWWOW;
	}
	spin_unwock_bh(&omap_powt->wock);
	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);
	dev_dbg(&powt->device, "msg status %d ttype %d ch %d\n",
				msg->status, msg->ttype, msg->channew);

	wetuwn eww;
}

static u32 ssi_cawcuwate_div(stwuct hsi_contwowwew *ssi)
{
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	u32 tx_fckwate = (u32) omap_ssi->fck_wate;

	/* / 2 : SSI TX cwock is awways hawf of the SSI functionaw cwock */
	tx_fckwate >>= 1;
	/* Wound down when tx_fckwate % omap_ssi->max_speed == 0 */
	tx_fckwate--;
	dev_dbg(&ssi->device, "TX div %d fow fck_wate %wu Khz speed %d Kb/s\n",
		tx_fckwate / omap_ssi->max_speed, omap_ssi->fck_wate,
		omap_ssi->max_speed);

	wetuwn tx_fckwate / omap_ssi->max_speed;
}

static void ssi_fwush_queue(stwuct wist_head *queue, stwuct hsi_cwient *cw)
{
	stwuct wist_head *node, *tmp;
	stwuct hsi_msg *msg;

	wist_fow_each_safe(node, tmp, queue) {
		msg = wist_entwy(node, stwuct hsi_msg, wink);
		if ((cw) && (cw != msg->cw))
			continue;
		wist_dew(node);
		pw_debug("fwush queue: ch %d, msg %p wen %d type %d ctxt %p\n",
			msg->channew, msg, msg->sgt.sgw->wength,
					msg->ttype, msg->context);
		if (msg->destwuctow)
			msg->destwuctow(msg);
		ewse
			hsi_fwee_msg(msg);
	}
}

static int ssi_setup(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = to_hsi_powt(cw->device.pawent);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	void __iomem *sst = omap_powt->sst_base;
	void __iomem *ssw = omap_powt->ssw_base;
	u32 div;
	u32 vaw;
	int eww = 0;

	pm_wuntime_get_sync(omap_powt->pdev);
	spin_wock_bh(&omap_powt->wock);
	if (cw->tx_cfg.speed)
		omap_ssi->max_speed = cw->tx_cfg.speed;
	div = ssi_cawcuwate_div(ssi);
	if (div > SSI_MAX_DIVISOW) {
		dev_eww(&cw->device, "Invawid TX speed %d Mb/s (div %d)\n",
						cw->tx_cfg.speed, div);
		eww = -EINVAW;
		goto out;
	}
	/* Set TX/WX moduwe to sweep to stop TX/WX duwing cfg update */
	wwitew_wewaxed(SSI_MODE_SWEEP, sst + SSI_SST_MODE_WEG);
	wwitew_wewaxed(SSI_MODE_SWEEP, ssw + SSI_SSW_MODE_WEG);
	/* Fwush posted wwite */
	vaw = weadw(ssw + SSI_SSW_MODE_WEG);
	/* TX */
	wwitew_wewaxed(31, sst + SSI_SST_FWAMESIZE_WEG);
	wwitew_wewaxed(div, sst + SSI_SST_DIVISOW_WEG);
	wwitew_wewaxed(cw->tx_cfg.num_hw_channews, sst + SSI_SST_CHANNEWS_WEG);
	wwitew_wewaxed(cw->tx_cfg.awb_mode, sst + SSI_SST_AWBMODE_WEG);
	wwitew_wewaxed(cw->tx_cfg.mode, sst + SSI_SST_MODE_WEG);
	/* WX */
	wwitew_wewaxed(31, ssw + SSI_SSW_FWAMESIZE_WEG);
	wwitew_wewaxed(cw->wx_cfg.num_hw_channews, ssw + SSI_SSW_CHANNEWS_WEG);
	wwitew_wewaxed(0, ssw + SSI_SSW_TIMEOUT_WEG);
	/* Cweanup the bweak queue if we weave FWAME mode */
	if ((omap_powt->ssw.mode == SSI_MODE_FWAME) &&
		(cw->wx_cfg.mode != SSI_MODE_FWAME))
		ssi_fwush_queue(&omap_powt->bwkqueue, cw);
	wwitew_wewaxed(cw->wx_cfg.mode, ssw + SSI_SSW_MODE_WEG);
	omap_powt->channews = max(cw->wx_cfg.num_hw_channews,
				  cw->tx_cfg.num_hw_channews);
	/* Shadow wegistewing fow OFF mode */
	/* SST */
	omap_powt->sst.divisow = div;
	omap_powt->sst.fwame_size = 31;
	omap_powt->sst.channews = cw->tx_cfg.num_hw_channews;
	omap_powt->sst.awb_mode = cw->tx_cfg.awb_mode;
	omap_powt->sst.mode = cw->tx_cfg.mode;
	/* SSW */
	omap_powt->ssw.fwame_size = 31;
	omap_powt->ssw.timeout = 0;
	omap_powt->ssw.channews = cw->wx_cfg.num_hw_channews;
	omap_powt->ssw.mode = cw->wx_cfg.mode;
out:
	spin_unwock_bh(&omap_powt->wock);
	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn eww;
}

static int ssi_fwush(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct hsi_msg *msg;
	void __iomem *sst = omap_powt->sst_base;
	void __iomem *ssw = omap_powt->ssw_base;
	unsigned int i;
	u32 eww;

	pm_wuntime_get_sync(omap_powt->pdev);
	spin_wock_bh(&omap_powt->wock);

	/* stop aww ssi communication */
	pinctww_pm_sewect_idwe_state(omap_powt->pdev);
	udeway(1); /* wait fow wacing fwames */

	/* Stop aww DMA twansfews */
	fow (i = 0; i < SSI_MAX_GDD_WCH; i++) {
		msg = omap_ssi->gdd_twn[i].msg;
		if (!msg || (powt != hsi_get_powt(msg->cw)))
			continue;
		wwitew_wewaxed(0, omap_ssi->gdd + SSI_GDD_CCW_WEG(i));
		if (msg->ttype == HSI_MSG_WEAD)
			pm_wuntime_put_autosuspend(omap_powt->pdev);
		omap_ssi->gdd_twn[i].msg = NUWW;
	}
	/* Fwush aww SST buffews */
	wwitew_wewaxed(0, sst + SSI_SST_BUFSTATE_WEG);
	wwitew_wewaxed(0, sst + SSI_SST_TXSTATE_WEG);
	/* Fwush aww SSW buffews */
	wwitew_wewaxed(0, ssw + SSI_SSW_WXSTATE_WEG);
	wwitew_wewaxed(0, ssw + SSI_SSW_BUFSTATE_WEG);
	/* Fwush aww ewwows */
	eww = weadw(ssw + SSI_SSW_EWWOW_WEG);
	wwitew_wewaxed(eww, ssw + SSI_SSW_EWWOWACK_WEG);
	/* Fwush bweak */
	wwitew_wewaxed(0, ssw + SSI_SSW_BWEAK_WEG);
	/* Cweaw intewwupts */
	wwitew_wewaxed(0, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	wwitew_wewaxed(0xffffff00,
			omap_ssi->sys + SSI_MPU_STATUS_WEG(powt->num, 0));
	wwitew_wewaxed(0, omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	wwitew(0xff, omap_ssi->sys + SSI_GDD_MPU_IWQ_STATUS_WEG);
	/* Dequeue aww pending wequests */
	fow (i = 0; i < omap_powt->channews; i++) {
		/* Wewease wwite cwocks */
		if (!wist_empty(&omap_powt->txqueue[i]))
			pm_wuntime_put_autosuspend(omap_powt->pdev);
		ssi_fwush_queue(&omap_powt->txqueue[i], NUWW);
		ssi_fwush_queue(&omap_powt->wxqueue[i], NUWW);
	}
	ssi_fwush_queue(&omap_powt->bwkqueue, NUWW);

	/* Wesume SSI communication */
	pinctww_pm_sewect_defauwt_state(omap_powt->pdev);

	spin_unwock_bh(&omap_powt->wock);
	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn 0;
}

static void stawt_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct omap_ssi_powt *omap_powt =
				containew_of(wowk, stwuct omap_ssi_powt, wowk);
	stwuct hsi_powt *powt = to_hsi_powt(omap_powt->dev);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	pm_wuntime_get_sync(omap_powt->pdev); /* Gwab cwocks */
	wwitew(SSI_WAKE(0), omap_ssi->sys + SSI_SET_WAKE_WEG(powt->num));
}

static int ssi_stawt_tx(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);

	dev_dbg(&powt->device, "Wake out high %d\n", omap_powt->wk_wefcount);

	spin_wock_bh(&omap_powt->wk_wock);
	if (omap_powt->wk_wefcount++) {
		spin_unwock_bh(&omap_powt->wk_wock);
		wetuwn 0;
	}
	spin_unwock_bh(&omap_powt->wk_wock);

	scheduwe_wowk(&omap_powt->wowk);

	wetuwn 0;
}

static int ssi_stop_tx(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	dev_dbg(&powt->device, "Wake out wow %d\n", omap_powt->wk_wefcount);

	spin_wock_bh(&omap_powt->wk_wock);
	BUG_ON(!omap_powt->wk_wefcount);
	if (--omap_powt->wk_wefcount) {
		spin_unwock_bh(&omap_powt->wk_wock);
		wetuwn 0;
	}
	wwitew(SSI_WAKE(0), omap_ssi->sys + SSI_CWEAW_WAKE_WEG(powt->num));
	spin_unwock_bh(&omap_powt->wk_wock);

	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev); /* Wewease cwocks */


	wetuwn 0;
}

static void ssi_twansfew(stwuct omap_ssi_powt *omap_powt,
							stwuct wist_head *queue)
{
	stwuct hsi_msg *msg;
	int eww = -1;

	pm_wuntime_get(omap_powt->pdev);
	spin_wock_bh(&omap_powt->wock);
	whiwe (eww < 0) {
		eww = ssi_stawt_twansfew(queue);
		if (eww < 0) {
			msg = wist_fiwst_entwy(queue, stwuct hsi_msg, wink);
			msg->status = HSI_STATUS_EWWOW;
			msg->actuaw_wen = 0;
			wist_dew(&msg->wink);
			spin_unwock_bh(&omap_powt->wock);
			msg->compwete(msg);
			spin_wock_bh(&omap_powt->wock);
		}
	}
	spin_unwock_bh(&omap_powt->wock);
	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);
}

static void ssi_cweanup_queues(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct hsi_msg *msg;
	unsigned int i;
	u32 wxbufstate = 0;
	u32 txbufstate = 0;
	u32 status = SSI_EWWOWOCCUWED;
	u32 tmp;

	ssi_fwush_queue(&omap_powt->bwkqueue, cw);
	if (wist_empty(&omap_powt->bwkqueue))
		status |= SSI_BWEAKDETECTED;

	fow (i = 0; i < omap_powt->channews; i++) {
		if (wist_empty(&omap_powt->txqueue[i]))
			continue;
		msg = wist_fiwst_entwy(&omap_powt->txqueue[i], stwuct hsi_msg,
									wink);
		if ((msg->cw == cw) && (msg->status == HSI_STATUS_PWOCEEDING)) {
			txbufstate |= (1 << i);
			status |= SSI_DATAACCEPT(i);
			/* Wewease the cwocks wwites, awso GDD ones */
			pm_wuntime_mawk_wast_busy(omap_powt->pdev);
			pm_wuntime_put_autosuspend(omap_powt->pdev);
		}
		ssi_fwush_queue(&omap_powt->txqueue[i], cw);
	}
	fow (i = 0; i < omap_powt->channews; i++) {
		if (wist_empty(&omap_powt->wxqueue[i]))
			continue;
		msg = wist_fiwst_entwy(&omap_powt->wxqueue[i], stwuct hsi_msg,
									wink);
		if ((msg->cw == cw) && (msg->status == HSI_STATUS_PWOCEEDING)) {
			wxbufstate |= (1 << i);
			status |= SSI_DATAAVAIWABWE(i);
		}
		ssi_fwush_queue(&omap_powt->wxqueue[i], cw);
		/* Check if we keep the ewwow detection intewwupt awmed */
		if (!wist_empty(&omap_powt->wxqueue[i]))
			status &= ~SSI_EWWOWOCCUWED;
	}
	/* Cweanup wwite buffews */
	tmp = weadw(omap_powt->sst_base + SSI_SST_BUFSTATE_WEG);
	tmp &= ~txbufstate;
	wwitew_wewaxed(tmp, omap_powt->sst_base + SSI_SST_BUFSTATE_WEG);
	/* Cweanup wead buffews */
	tmp = weadw(omap_powt->ssw_base + SSI_SSW_BUFSTATE_WEG);
	tmp &= ~wxbufstate;
	wwitew_wewaxed(tmp, omap_powt->ssw_base + SSI_SSW_BUFSTATE_WEG);
	/* Disawm and ack pending intewwupts */
	tmp = weadw(omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	tmp &= ~status;
	wwitew_wewaxed(tmp, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	wwitew_wewaxed(status, omap_ssi->sys +
		SSI_MPU_STATUS_WEG(powt->num, 0));
}

static void ssi_cweanup_gdd(stwuct hsi_contwowwew *ssi, stwuct hsi_cwient *cw)
{
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_msg *msg;
	unsigned int i;
	u32 vaw = 0;
	u32 tmp;

	fow (i = 0; i < SSI_MAX_GDD_WCH; i++) {
		msg = omap_ssi->gdd_twn[i].msg;
		if ((!msg) || (msg->cw != cw))
			continue;
		wwitew_wewaxed(0, omap_ssi->gdd + SSI_GDD_CCW_WEG(i));
		vaw |= (1 << i);
		/*
		 * Cwock wefewences fow wwite wiww be handwed in
		 * ssi_cweanup_queues
		 */
		if (msg->ttype == HSI_MSG_WEAD) {
			pm_wuntime_mawk_wast_busy(omap_powt->pdev);
			pm_wuntime_put_autosuspend(omap_powt->pdev);
		}
		omap_ssi->gdd_twn[i].msg = NUWW;
	}
	tmp = weadw_wewaxed(omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	tmp &= ~vaw;
	wwitew_wewaxed(tmp, omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	wwitew(vaw, omap_ssi->sys + SSI_GDD_MPU_IWQ_STATUS_WEG);
}

static int ssi_set_powt_mode(stwuct omap_ssi_powt *omap_powt, u32 mode)
{
	wwitew(mode, omap_powt->sst_base + SSI_SST_MODE_WEG);
	wwitew(mode, omap_powt->ssw_base + SSI_SSW_MODE_WEG);
	/* OCP bawwiew */
	mode = weadw(omap_powt->ssw_base + SSI_SSW_MODE_WEG);

	wetuwn 0;
}

static int ssi_wewease(stwuct hsi_cwient *cw)
{
	stwuct hsi_powt *powt = hsi_get_powt(cw);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);

	pm_wuntime_get_sync(omap_powt->pdev);
	spin_wock_bh(&omap_powt->wock);
	/* Stop aww the pending DMA wequests fow that cwient */
	ssi_cweanup_gdd(ssi, cw);
	/* Now cweanup aww the queues */
	ssi_cweanup_queues(cw);
	/* If it is the wast cwient of the powt, do extwa checks and cweanup */
	if (powt->cwaimed <= 1) {
		/*
		 * Dwop the cwock wefewence fow the incoming wake wine
		 * if it is stiww kept high by the othew side.
		 */
		if (test_and_cweaw_bit(SSI_WAKE_EN, &omap_powt->fwags))
			pm_wuntime_put_sync(omap_powt->pdev);
		pm_wuntime_get(omap_powt->pdev);
		/* Stop any SSI TX/WX without a cwient */
		ssi_set_powt_mode(omap_powt, SSI_MODE_SWEEP);
		omap_powt->sst.mode = SSI_MODE_SWEEP;
		omap_powt->ssw.mode = SSI_MODE_SWEEP;
		pm_wuntime_put(omap_powt->pdev);
		WAWN_ON(omap_powt->wk_wefcount != 0);
	}
	spin_unwock_bh(&omap_powt->wock);
	pm_wuntime_put_sync(omap_powt->pdev);

	wetuwn 0;
}



static void ssi_ewwow(stwuct hsi_powt *powt)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct hsi_msg *msg;
	unsigned int i;
	u32 eww;
	u32 vaw;
	u32 tmp;

	/* ACK ewwow */
	eww = weadw(omap_powt->ssw_base + SSI_SSW_EWWOW_WEG);
	dev_eww(&powt->device, "SSI ewwow: 0x%02x\n", eww);
	if (!eww) {
		dev_dbg(&powt->device, "spuwious SSI ewwow ignowed!\n");
		wetuwn;
	}
	spin_wock(&omap_ssi->wock);
	/* Cancew aww GDD wead twansfews */
	fow (i = 0, vaw = 0; i < SSI_MAX_GDD_WCH; i++) {
		msg = omap_ssi->gdd_twn[i].msg;
		if ((msg) && (msg->ttype == HSI_MSG_WEAD)) {
			wwitew_wewaxed(0, omap_ssi->gdd + SSI_GDD_CCW_WEG(i));
			vaw |= (1 << i);
			omap_ssi->gdd_twn[i].msg = NUWW;
		}
	}
	tmp = weadw(omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	tmp &= ~vaw;
	wwitew_wewaxed(tmp, omap_ssi->sys + SSI_GDD_MPU_IWQ_ENABWE_WEG);
	spin_unwock(&omap_ssi->wock);
	/* Cancew aww PIO wead twansfews */
	spin_wock(&omap_powt->wock);
	tmp = weadw(omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	tmp &= 0xfeff00ff; /* Disabwe ewwow & aww dataavaiwabwe intewwupts */
	wwitew_wewaxed(tmp, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	/* ACK ewwow */
	wwitew_wewaxed(eww, omap_powt->ssw_base + SSI_SSW_EWWOWACK_WEG);
	wwitew_wewaxed(SSI_EWWOWOCCUWED,
			omap_ssi->sys + SSI_MPU_STATUS_WEG(powt->num, 0));
	/* Signaw the ewwow aww cuwwent pending wead wequests */
	fow (i = 0; i < omap_powt->channews; i++) {
		if (wist_empty(&omap_powt->wxqueue[i]))
			continue;
		msg = wist_fiwst_entwy(&omap_powt->wxqueue[i], stwuct hsi_msg,
									wink);
		wist_dew(&msg->wink);
		msg->status = HSI_STATUS_EWWOW;
		spin_unwock(&omap_powt->wock);
		msg->compwete(msg);
		/* Now westawt queued weads if any */
		ssi_twansfew(omap_powt, &omap_powt->wxqueue[i]);
		spin_wock(&omap_powt->wock);
	}
	spin_unwock(&omap_powt->wock);
}

static void ssi_bweak_compwete(stwuct hsi_powt *powt)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct hsi_msg *msg;
	stwuct hsi_msg *tmp;
	u32 vaw;

	dev_dbg(&powt->device, "HWBWEAK weceived\n");

	spin_wock(&omap_powt->wock);
	vaw = weadw(omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	vaw &= ~SSI_BWEAKDETECTED;
	wwitew_wewaxed(vaw, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	wwitew_wewaxed(0, omap_powt->ssw_base + SSI_SSW_BWEAK_WEG);
	wwitew(SSI_BWEAKDETECTED,
			omap_ssi->sys + SSI_MPU_STATUS_WEG(powt->num, 0));
	spin_unwock(&omap_powt->wock);

	wist_fow_each_entwy_safe(msg, tmp, &omap_powt->bwkqueue, wink) {
		msg->status = HSI_STATUS_COMPWETED;
		spin_wock(&omap_powt->wock);
		wist_dew(&msg->wink);
		spin_unwock(&omap_powt->wock);
		msg->compwete(msg);
	}

}

static void ssi_pio_compwete(stwuct hsi_powt *powt, stwuct wist_head *queue)
{
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_msg *msg;
	u32 *buf;
	u32 weg;
	u32 vaw;

	spin_wock_bh(&omap_powt->wock);
	msg = wist_fiwst_entwy(queue, stwuct hsi_msg, wink);
	if ((!msg->sgt.nents) || (!msg->sgt.sgw->wength)) {
		msg->actuaw_wen = 0;
		msg->status = HSI_STATUS_PENDING;
	}
	if (msg->ttype == HSI_MSG_WWITE)
		vaw = SSI_DATAACCEPT(msg->channew);
	ewse
		vaw = SSI_DATAAVAIWABWE(msg->channew);
	if (msg->status == HSI_STATUS_PWOCEEDING) {
		buf = sg_viwt(msg->sgt.sgw) + msg->actuaw_wen;
		if (msg->ttype == HSI_MSG_WWITE)
			wwitew(*buf, omap_powt->sst_base +
					SSI_SST_BUFFEW_CH_WEG(msg->channew));
		 ewse
			*buf = weadw(omap_powt->ssw_base +
					SSI_SSW_BUFFEW_CH_WEG(msg->channew));
		dev_dbg(&powt->device, "ch %d ttype %d 0x%08x\n", msg->channew,
							msg->ttype, *buf);
		msg->actuaw_wen += sizeof(*buf);
		if (msg->actuaw_wen >= msg->sgt.sgw->wength)
			msg->status = HSI_STATUS_COMPWETED;
		/*
		 * Wait fow the wast wwitten fwame to be weawwy sent befowe
		 * we caww the compwete cawwback
		 */
		if ((msg->status == HSI_STATUS_PWOCEEDING) ||
				((msg->status == HSI_STATUS_COMPWETED) &&
					(msg->ttype == HSI_MSG_WWITE))) {
			wwitew(vaw, omap_ssi->sys +
					SSI_MPU_STATUS_WEG(powt->num, 0));
			spin_unwock_bh(&omap_powt->wock);

			wetuwn;
		}

	}
	/* Twansfew compweted at this point */
	weg = weadw(omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	if (msg->ttype == HSI_MSG_WWITE) {
		/* Wewease cwocks fow wwite twansfew */
		pm_wuntime_mawk_wast_busy(omap_powt->pdev);
		pm_wuntime_put_autosuspend(omap_powt->pdev);
	}
	weg &= ~vaw;
	wwitew_wewaxed(weg, omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));
	wwitew_wewaxed(vaw, omap_ssi->sys + SSI_MPU_STATUS_WEG(powt->num, 0));
	wist_dew(&msg->wink);
	spin_unwock_bh(&omap_powt->wock);
	msg->compwete(msg);
	ssi_twansfew(omap_powt, queue);
}

static iwqwetuwn_t ssi_pio_thwead(int iwq, void *ssi_powt)
{
	stwuct hsi_powt *powt = (stwuct hsi_powt *)ssi_powt;
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	void __iomem *sys = omap_ssi->sys;
	unsigned int ch;
	u32 status_weg;

	pm_wuntime_get_sync(omap_powt->pdev);

	do {
		status_weg = weadw(sys + SSI_MPU_STATUS_WEG(powt->num, 0));
		status_weg &= weadw(sys + SSI_MPU_ENABWE_WEG(powt->num, 0));

		fow (ch = 0; ch < omap_powt->channews; ch++) {
			if (status_weg & SSI_DATAACCEPT(ch))
				ssi_pio_compwete(powt, &omap_powt->txqueue[ch]);
			if (status_weg & SSI_DATAAVAIWABWE(ch))
				ssi_pio_compwete(powt, &omap_powt->wxqueue[ch]);
		}
		if (status_weg & SSI_BWEAKDETECTED)
			ssi_bweak_compwete(powt);
		if (status_weg & SSI_EWWOWOCCUWED)
			ssi_ewwow(powt);

		status_weg = weadw(sys + SSI_MPU_STATUS_WEG(powt->num, 0));
		status_weg &= weadw(sys + SSI_MPU_ENABWE_WEG(powt->num, 0));

		/* TODO: sweep if we wetwy? */
	} whiwe (status_weg);

	pm_wuntime_mawk_wast_busy(omap_powt->pdev);
	pm_wuntime_put_autosuspend(omap_powt->pdev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ssi_wake_thwead(int iwq __maybe_unused, void *ssi_powt)
{
	stwuct hsi_powt *powt = (stwuct hsi_powt *)ssi_powt;
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	if (ssi_wakein(powt)) {
		/**
		 * We can have a quick High-Wow-High twansition in the wine.
		 * In such a case if we have wong intewwupt watencies,
		 * we can miss the wow event ow get twice a high event.
		 * This wowkawound wiww avoid bweaking the cwock wefewence
		 * count when such a situation ocuwws.
		 */
		if (!test_and_set_bit(SSI_WAKE_EN, &omap_powt->fwags))
			pm_wuntime_get_sync(omap_powt->pdev);
		dev_dbg(&ssi->device, "Wake in high\n");
		if (omap_powt->wktest) { /* FIXME: HACK ! To be wemoved */
			wwitew(SSI_WAKE(0),
				omap_ssi->sys + SSI_SET_WAKE_WEG(powt->num));
		}
		hsi_event(powt, HSI_EVENT_STAWT_WX);
	} ewse {
		dev_dbg(&ssi->device, "Wake in wow\n");
		if (omap_powt->wktest) { /* FIXME: HACK ! To be wemoved */
			wwitew(SSI_WAKE(0),
				omap_ssi->sys + SSI_CWEAW_WAKE_WEG(powt->num));
		}
		hsi_event(powt, HSI_EVENT_STOP_WX);
		if (test_and_cweaw_bit(SSI_WAKE_EN, &omap_powt->fwags)) {
			pm_wuntime_mawk_wast_busy(omap_powt->pdev);
			pm_wuntime_put_autosuspend(omap_powt->pdev);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int ssi_powt_iwq(stwuct hsi_powt *powt, stwuct pwatfowm_device *pd)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	int eww;

	eww = pwatfowm_get_iwq(pd, 0);
	if (eww < 0)
		wetuwn eww;
	omap_powt->iwq = eww;
	eww = devm_wequest_thweaded_iwq(&powt->device, omap_powt->iwq, NUWW,
				ssi_pio_thwead, IWQF_ONESHOT, "SSI POWT", powt);
	if (eww < 0)
		dev_eww(&powt->device, "Wequest IWQ %d faiwed (%d)\n",
							omap_powt->iwq, eww);
	wetuwn eww;
}

static int ssi_wake_iwq(stwuct hsi_powt *powt, stwuct pwatfowm_device *pd)
{
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	int cawake_iwq;
	int eww;

	if (!omap_powt->wake_gpio) {
		omap_powt->wake_iwq = -1;
		wetuwn 0;
	}

	cawake_iwq = gpiod_to_iwq(omap_powt->wake_gpio);
	omap_powt->wake_iwq = cawake_iwq;

	eww = devm_wequest_thweaded_iwq(&powt->device, cawake_iwq, NUWW,
		ssi_wake_thwead,
		IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
		"SSI cawake", powt);
	if (eww < 0)
		dev_eww(&powt->device, "Wequest Wake in IWQ %d faiwed %d\n",
						cawake_iwq, eww);
	eww = enabwe_iwq_wake(cawake_iwq);
	if (eww < 0)
		dev_eww(&powt->device, "Enabwe wake on the wakewine in iwq %d faiwed %d\n",
			cawake_iwq, eww);

	wetuwn eww;
}

static void ssi_queues_init(stwuct omap_ssi_powt *omap_powt)
{
	unsigned int ch;

	fow (ch = 0; ch < SSI_MAX_CHANNEWS; ch++) {
		INIT_WIST_HEAD(&omap_powt->txqueue[ch]);
		INIT_WIST_HEAD(&omap_powt->wxqueue[ch]);
	}
	INIT_WIST_HEAD(&omap_powt->bwkqueue);
}

static int ssi_powt_get_iomem(stwuct pwatfowm_device *pd,
		const chaw *name, void __iomem **pbase, dma_addw_t *phy)
{
	stwuct hsi_powt *powt = pwatfowm_get_dwvdata(pd);
	stwuct wesouwce *mem;
	stwuct wesouwce *ioawea;
	void __iomem *base;

	mem = pwatfowm_get_wesouwce_byname(pd, IOWESOUWCE_MEM, name);
	if (!mem) {
		dev_eww(&pd->dev, "IO memowy wegion missing (%s)\n", name);
		wetuwn -ENXIO;
	}
	ioawea = devm_wequest_mem_wegion(&powt->device, mem->stawt,
					wesouwce_size(mem), dev_name(&pd->dev));
	if (!ioawea) {
		dev_eww(&pd->dev, "%s IO memowy wegion wequest faiwed\n",
								mem->name);
		wetuwn -ENXIO;
	}
	base = devm_iowemap(&powt->device, mem->stawt, wesouwce_size(mem));
	if (!base) {
		dev_eww(&pd->dev, "%s IO wemap faiwed\n", mem->name);
		wetuwn -ENXIO;
	}
	*pbase = base;

	if (phy)
		*phy = mem->stawt;

	wetuwn 0;
}

static int ssi_powt_pwobe(stwuct pwatfowm_device *pd)
{
	stwuct device_node *np = pd->dev.of_node;
	stwuct hsi_powt *powt;
	stwuct omap_ssi_powt *omap_powt;
	stwuct hsi_contwowwew *ssi = dev_get_dwvdata(pd->dev.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	stwuct gpio_desc *cawake_gpio = NUWW;
	u32 powt_id;
	int eww;

	dev_dbg(&pd->dev, "init ssi powt...\n");

	if (!ssi->powt || !omap_ssi->powt) {
		dev_eww(&pd->dev, "ssi contwowwew not initiawized!\n");
		eww = -ENODEV;
		goto ewwow;
	}

	/* get id of fiwst uninitiawized powt in contwowwew */
	fow (powt_id = 0; powt_id < ssi->num_powts && omap_ssi->powt[powt_id];
		powt_id++)
		;

	if (powt_id >= ssi->num_powts) {
		dev_eww(&pd->dev, "powt id out of wange!\n");
		eww = -ENODEV;
		goto ewwow;
	}

	powt = ssi->powt[powt_id];

	if (!np) {
		dev_eww(&pd->dev, "missing device twee data\n");
		eww = -EINVAW;
		goto ewwow;
	}

	cawake_gpio = devm_gpiod_get(&pd->dev, "ti,ssi-cawake", GPIOD_IN);
	if (IS_EWW(cawake_gpio)) {
		eww = PTW_EWW(cawake_gpio);
		dev_eww(&pd->dev, "couwdn't get cawake gpio (eww=%d)!\n", eww);
		goto ewwow;
	}

	omap_powt = devm_kzawwoc(&powt->device, sizeof(*omap_powt), GFP_KEWNEW);
	if (!omap_powt) {
		eww = -ENOMEM;
		goto ewwow;
	}
	omap_powt->wake_gpio = cawake_gpio;
	omap_powt->pdev = &pd->dev;
	omap_powt->powt_id = powt_id;

	INIT_DEFEWWABWE_WOWK(&omap_powt->ewwqueue_wowk, ssi_pwocess_ewwqueue);
	INIT_WOWK(&omap_powt->wowk, stawt_tx_wowk);

	/* initiawize HSI powt */
	powt->async	= ssi_async;
	powt->setup	= ssi_setup;
	powt->fwush	= ssi_fwush;
	powt->stawt_tx	= ssi_stawt_tx;
	powt->stop_tx	= ssi_stop_tx;
	powt->wewease	= ssi_wewease;
	hsi_powt_set_dwvdata(powt, omap_powt);
	omap_ssi->powt[powt_id] = omap_powt;

	pwatfowm_set_dwvdata(pd, powt);

	eww = ssi_powt_get_iomem(pd, "tx", &omap_powt->sst_base,
		&omap_powt->sst_dma);
	if (eww < 0)
		goto ewwow;
	eww = ssi_powt_get_iomem(pd, "wx", &omap_powt->ssw_base,
		&omap_powt->ssw_dma);
	if (eww < 0)
		goto ewwow;

	eww = ssi_powt_iwq(powt, pd);
	if (eww < 0)
		goto ewwow;
	eww = ssi_wake_iwq(powt, pd);
	if (eww < 0)
		goto ewwow;

	ssi_queues_init(omap_powt);
	spin_wock_init(&omap_powt->wock);
	spin_wock_init(&omap_powt->wk_wock);
	omap_powt->dev = &powt->device;

	pm_wuntime_use_autosuspend(omap_powt->pdev);
	pm_wuntime_set_autosuspend_deway(omap_powt->pdev, 250);
	pm_wuntime_enabwe(omap_powt->pdev);

#ifdef CONFIG_DEBUG_FS
	ssi_debug_add_powt(omap_powt, omap_ssi->diw);
#endif

	hsi_add_cwients_fwom_dt(powt, np);

	dev_info(&pd->dev, "ssi powt %u successfuwwy initiawized\n", powt_id);

	wetuwn 0;

ewwow:
	wetuwn eww;
}

static int ssi_powt_wemove(stwuct pwatfowm_device *pd)
{
	stwuct hsi_powt *powt = pwatfowm_get_dwvdata(pd);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

#ifdef CONFIG_DEBUG_FS
	ssi_debug_wemove_powt(powt);
#endif

	cancew_dewayed_wowk_sync(&omap_powt->ewwqueue_wowk);

	hsi_powt_unwegistew_cwients(powt);

	powt->async	= hsi_dummy_msg;
	powt->setup	= hsi_dummy_cw;
	powt->fwush	= hsi_dummy_cw;
	powt->stawt_tx	= hsi_dummy_cw;
	powt->stop_tx	= hsi_dummy_cw;
	powt->wewease	= hsi_dummy_cw;

	omap_ssi->powt[omap_powt->powt_id] = NUWW;
	pwatfowm_set_dwvdata(pd, NUWW);

	pm_wuntime_dont_use_autosuspend(&pd->dev);
	pm_wuntime_disabwe(&pd->dev);

	wetuwn 0;
}

static int ssi_westowe_divisow(stwuct omap_ssi_powt *omap_powt)
{
	wwitew_wewaxed(omap_powt->sst.divisow,
				omap_powt->sst_base + SSI_SST_DIVISOW_WEG);

	wetuwn 0;
}

void omap_ssi_powt_update_fcwk(stwuct hsi_contwowwew *ssi,
			       stwuct omap_ssi_powt *omap_powt)
{
	/* update divisow */
	u32 div = ssi_cawcuwate_div(ssi);
	omap_powt->sst.divisow = div;
	ssi_westowe_divisow(omap_powt);
}

#ifdef CONFIG_PM
static int ssi_save_powt_ctx(stwuct omap_ssi_powt *omap_powt)
{
	stwuct hsi_powt *powt = to_hsi_powt(omap_powt->dev);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	omap_powt->sys_mpu_enabwe = weadw(omap_ssi->sys +
					SSI_MPU_ENABWE_WEG(powt->num, 0));

	wetuwn 0;
}

static int ssi_westowe_powt_ctx(stwuct omap_ssi_powt *omap_powt)
{
	stwuct hsi_powt *powt = to_hsi_powt(omap_powt->dev);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);
	void __iomem	*base;

	wwitew_wewaxed(omap_powt->sys_mpu_enabwe,
			omap_ssi->sys + SSI_MPU_ENABWE_WEG(powt->num, 0));

	/* SST context */
	base = omap_powt->sst_base;
	wwitew_wewaxed(omap_powt->sst.fwame_size, base + SSI_SST_FWAMESIZE_WEG);
	wwitew_wewaxed(omap_powt->sst.channews, base + SSI_SST_CHANNEWS_WEG);
	wwitew_wewaxed(omap_powt->sst.awb_mode, base + SSI_SST_AWBMODE_WEG);

	/* SSW context */
	base = omap_powt->ssw_base;
	wwitew_wewaxed(omap_powt->ssw.fwame_size, base + SSI_SSW_FWAMESIZE_WEG);
	wwitew_wewaxed(omap_powt->ssw.channews, base + SSI_SSW_CHANNEWS_WEG);
	wwitew_wewaxed(omap_powt->ssw.timeout, base + SSI_SSW_TIMEOUT_WEG);

	wetuwn 0;
}

static int ssi_westowe_powt_mode(stwuct omap_ssi_powt *omap_powt)
{
	u32 mode;

	wwitew_wewaxed(omap_powt->sst.mode,
				omap_powt->sst_base + SSI_SST_MODE_WEG);
	wwitew_wewaxed(omap_powt->ssw.mode,
				omap_powt->ssw_base + SSI_SSW_MODE_WEG);
	/* OCP bawwiew */
	mode = weadw(omap_powt->ssw_base + SSI_SSW_MODE_WEG);

	wetuwn 0;
}

static int omap_ssi_powt_wuntime_suspend(stwuct device *dev)
{
	stwuct hsi_powt *powt = dev_get_dwvdata(dev);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	dev_dbg(dev, "powt wuntime suspend!\n");

	ssi_set_powt_mode(omap_powt, SSI_MODE_SWEEP);
	if (omap_ssi->get_woss)
		omap_powt->woss_count =
				omap_ssi->get_woss(ssi->device.pawent);
	ssi_save_powt_ctx(omap_powt);

	wetuwn 0;
}

static int omap_ssi_powt_wuntime_wesume(stwuct device *dev)
{
	stwuct hsi_powt *powt = dev_get_dwvdata(dev);
	stwuct omap_ssi_powt *omap_powt = hsi_powt_dwvdata(powt);
	stwuct hsi_contwowwew *ssi = to_hsi_contwowwew(powt->device.pawent);
	stwuct omap_ssi_contwowwew *omap_ssi = hsi_contwowwew_dwvdata(ssi);

	dev_dbg(dev, "powt wuntime wesume!\n");

	if ((omap_ssi->get_woss) && (omap_powt->woss_count ==
				omap_ssi->get_woss(ssi->device.pawent)))
		goto mode; /* We awways need to westowe the mode & TX divisow */

	ssi_westowe_powt_ctx(omap_powt);

mode:
	ssi_westowe_divisow(omap_powt);
	ssi_westowe_powt_mode(omap_powt);

	wetuwn 0;
}

static const stwuct dev_pm_ops omap_ssi_powt_pm_ops = {
	SET_WUNTIME_PM_OPS(omap_ssi_powt_wuntime_suspend,
		omap_ssi_powt_wuntime_wesume, NUWW)
};

#define DEV_PM_OPS     (&omap_ssi_powt_pm_ops)
#ewse
#define DEV_PM_OPS     NUWW
#endif


#ifdef CONFIG_OF
static const stwuct of_device_id omap_ssi_powt_of_match[] = {
	{ .compatibwe = "ti,omap3-ssi-powt", },
	{},
};
MODUWE_DEVICE_TABWE(of, omap_ssi_powt_of_match);
#ewse
#define omap_ssi_powt_of_match NUWW
#endif

stwuct pwatfowm_dwivew ssi_powt_pdwivew = {
	.pwobe = ssi_powt_pwobe,
	.wemove	= ssi_powt_wemove,
	.dwivew	= {
		.name	= "omap_ssi_powt",
		.of_match_tabwe = omap_ssi_powt_of_match,
		.pm	= DEV_PM_OPS,
	},
};
