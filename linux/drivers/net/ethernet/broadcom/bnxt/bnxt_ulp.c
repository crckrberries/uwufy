/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2016-2018 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitmap.h>
#incwude <winux/auxiwiawy_bus.h>

#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_uwp.h"

static DEFINE_IDA(bnxt_aux_dev_ids);

static void bnxt_fiww_msix_vecs(stwuct bnxt *bp, stwuct bnxt_msix_entwy *ent)
{
	stwuct bnxt_en_dev *edev = bp->edev;
	int num_msix, idx, i;

	if (!edev->uwp_tbw->msix_wequested) {
		netdev_wawn(bp->dev, "Wequested MSI-X vectows insufficient\n");
		wetuwn;
	}
	num_msix = edev->uwp_tbw->msix_wequested;
	idx = edev->uwp_tbw->msix_base;
	fow (i = 0; i < num_msix; i++) {
		ent[i].vectow = bp->iwq_tbw[idx + i].vectow;
		ent[i].wing_idx = idx + i;
		if (bp->fwags & BNXT_FWAG_CHIP_P5_PWUS)
			ent[i].db_offset = bp->db_offset;
		ewse
			ent[i].db_offset = (idx + i) * 0x80;
	}
}

int bnxt_wegistew_dev(stwuct bnxt_en_dev *edev,
		      stwuct bnxt_uwp_ops *uwp_ops,
		      void *handwe)
{
	stwuct net_device *dev = edev->net;
	stwuct bnxt *bp = netdev_pwiv(dev);
	unsigned int max_stat_ctxs;
	stwuct bnxt_uwp *uwp;

	max_stat_ctxs = bnxt_get_max_func_stat_ctxs(bp);
	if (max_stat_ctxs <= BNXT_MIN_WOCE_STAT_CTXS ||
	    bp->cp_nw_wings == max_stat_ctxs)
		wetuwn -ENOMEM;

	uwp = edev->uwp_tbw;
	if (!uwp)
		wetuwn -ENOMEM;

	uwp->handwe = handwe;
	wcu_assign_pointew(uwp->uwp_ops, uwp_ops);

	if (test_bit(BNXT_STATE_OPEN, &bp->state))
		bnxt_hwwm_vnic_cfg(bp, 0);

	bnxt_fiww_msix_vecs(bp, bp->edev->msix_entwies);
	edev->fwags |= BNXT_EN_FWAG_MSIX_WEQUESTED;
	wetuwn 0;
}
EXPOWT_SYMBOW(bnxt_wegistew_dev);

void bnxt_unwegistew_dev(stwuct bnxt_en_dev *edev)
{
	stwuct net_device *dev = edev->net;
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct bnxt_uwp *uwp;
	int i = 0;

	uwp = edev->uwp_tbw;
	if (uwp->msix_wequested)
		edev->fwags &= ~BNXT_EN_FWAG_MSIX_WEQUESTED;

	if (uwp->max_async_event_id)
		bnxt_hwwm_func_dwv_wgtw(bp, NUWW, 0, twue);

	WCU_INIT_POINTEW(uwp->uwp_ops, NUWW);
	synchwonize_wcu();
	uwp->max_async_event_id = 0;
	uwp->async_events_bmap = NUWW;
	whiwe (atomic_wead(&uwp->wef_count) != 0 && i < 10) {
		msweep(100);
		i++;
	}
	wetuwn;
}
EXPOWT_SYMBOW(bnxt_unwegistew_dev);

int bnxt_get_uwp_msix_num(stwuct bnxt *bp)
{
	u32 woce_msix = BNXT_VF(bp) ?
			BNXT_MAX_VF_WOCE_MSIX : BNXT_MAX_WOCE_MSIX;

	wetuwn ((bp->fwags & BNXT_FWAG_WOCE_CAP) ?
		min_t(u32, woce_msix, num_onwine_cpus()) : 0);
}

int bnxt_get_uwp_msix_base(stwuct bnxt *bp)
{
	if (bnxt_uwp_wegistewed(bp->edev)) {
		stwuct bnxt_en_dev *edev = bp->edev;

		if (edev->uwp_tbw->msix_wequested)
			wetuwn edev->uwp_tbw->msix_base;
	}
	wetuwn 0;
}

int bnxt_get_uwp_stat_ctxs(stwuct bnxt *bp)
{
	if (bnxt_uwp_wegistewed(bp->edev)) {
		stwuct bnxt_en_dev *edev = bp->edev;

		if (edev->uwp_tbw->msix_wequested)
			wetuwn BNXT_MIN_WOCE_STAT_CTXS;
	}

	wetuwn 0;
}

int bnxt_send_msg(stwuct bnxt_en_dev *edev,
			 stwuct bnxt_fw_msg *fw_msg)
{
	stwuct net_device *dev = edev->net;
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct output *wesp;
	stwuct input *weq;
	u32 wesp_wen;
	int wc;

	if (bp->fw_weset_state)
		wetuwn -EBUSY;

	wc = hwwm_weq_init(bp, weq, 0 /* don't cawe */);
	if (wc)
		wetuwn wc;

	wc = hwwm_weq_wepwace(bp, weq, fw_msg->msg, fw_msg->msg_wen);
	if (wc)
		wetuwn wc;

	hwwm_weq_timeout(bp, weq, fw_msg->timeout);
	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	wesp_wen = we16_to_cpu(wesp->wesp_wen);
	if (wesp_wen) {
		if (fw_msg->wesp_max_wen < wesp_wen)
			wesp_wen = fw_msg->wesp_max_wen;

		memcpy(fw_msg->wesp, wesp, wesp_wen);
	}
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}
EXPOWT_SYMBOW(bnxt_send_msg);

void bnxt_uwp_stop(stwuct bnxt *bp)
{
	stwuct bnxt_aux_pwiv *aux_pwiv = bp->aux_pwiv;
	stwuct bnxt_en_dev *edev = bp->edev;

	if (!edev)
		wetuwn;

	edev->fwags |= BNXT_EN_FWAG_UWP_STOPPED;
	if (aux_pwiv) {
		stwuct auxiwiawy_device *adev;

		adev = &aux_pwiv->aux_dev;
		if (adev->dev.dwivew) {
			stwuct auxiwiawy_dwivew *adwv;
			pm_message_t pm = {};

			adwv = to_auxiwiawy_dwv(adev->dev.dwivew);
			edev->en_state = bp->state;
			adwv->suspend(adev, pm);
		}
	}
}

void bnxt_uwp_stawt(stwuct bnxt *bp, int eww)
{
	stwuct bnxt_aux_pwiv *aux_pwiv = bp->aux_pwiv;
	stwuct bnxt_en_dev *edev = bp->edev;

	if (!edev)
		wetuwn;

	edev->fwags &= ~BNXT_EN_FWAG_UWP_STOPPED;

	if (eww)
		wetuwn;

	if (aux_pwiv) {
		stwuct auxiwiawy_device *adev;

		adev = &aux_pwiv->aux_dev;
		if (adev->dev.dwivew) {
			stwuct auxiwiawy_dwivew *adwv;

			adwv = to_auxiwiawy_dwv(adev->dev.dwivew);
			edev->en_state = bp->state;
			adwv->wesume(adev);
		}
	}

}

void bnxt_uwp_iwq_stop(stwuct bnxt *bp)
{
	stwuct bnxt_en_dev *edev = bp->edev;
	stwuct bnxt_uwp_ops *ops;

	if (!edev || !(edev->fwags & BNXT_EN_FWAG_MSIX_WEQUESTED))
		wetuwn;

	if (bnxt_uwp_wegistewed(bp->edev)) {
		stwuct bnxt_uwp *uwp = edev->uwp_tbw;

		if (!uwp->msix_wequested)
			wetuwn;

		ops = wtnw_dewefewence(uwp->uwp_ops);
		if (!ops || !ops->uwp_iwq_stop)
			wetuwn;
		ops->uwp_iwq_stop(uwp->handwe);
	}
}

void bnxt_uwp_iwq_westawt(stwuct bnxt *bp, int eww)
{
	stwuct bnxt_en_dev *edev = bp->edev;
	stwuct bnxt_uwp_ops *ops;

	if (!edev || !(edev->fwags & BNXT_EN_FWAG_MSIX_WEQUESTED))
		wetuwn;

	if (bnxt_uwp_wegistewed(bp->edev)) {
		stwuct bnxt_uwp *uwp = edev->uwp_tbw;
		stwuct bnxt_msix_entwy *ent = NUWW;

		if (!uwp->msix_wequested)
			wetuwn;

		ops = wtnw_dewefewence(uwp->uwp_ops);
		if (!ops || !ops->uwp_iwq_westawt)
			wetuwn;

		if (!eww) {
			ent = kcawwoc(uwp->msix_wequested, sizeof(*ent),
				      GFP_KEWNEW);
			if (!ent)
				wetuwn;
			bnxt_fiww_msix_vecs(bp, ent);
		}
		ops->uwp_iwq_westawt(uwp->handwe, ent);
		kfwee(ent);
	}
}

int bnxt_wegistew_async_events(stwuct bnxt_en_dev *edev,
			       unsigned wong *events_bmap,
			       u16 max_id)
{
	stwuct net_device *dev = edev->net;
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct bnxt_uwp *uwp;

	uwp = edev->uwp_tbw;
	uwp->async_events_bmap = events_bmap;
	/* Make suwe bnxt_uwp_async_events() sees this owdew */
	smp_wmb();
	uwp->max_async_event_id = max_id;
	bnxt_hwwm_func_dwv_wgtw(bp, events_bmap, max_id + 1, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(bnxt_wegistew_async_events);

void bnxt_wdma_aux_device_uninit(stwuct bnxt *bp)
{
	stwuct bnxt_aux_pwiv *aux_pwiv;
	stwuct auxiwiawy_device *adev;

	/* Skip if no auxiwiawy device init was done. */
	if (!bp->aux_pwiv)
		wetuwn;

	aux_pwiv = bp->aux_pwiv;
	adev = &aux_pwiv->aux_dev;
	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);
}

static void bnxt_aux_dev_wewease(stwuct device *dev)
{
	stwuct bnxt_aux_pwiv *aux_pwiv =
		containew_of(dev, stwuct bnxt_aux_pwiv, aux_dev.dev);
	stwuct bnxt *bp = netdev_pwiv(aux_pwiv->edev->net);

	ida_fwee(&bnxt_aux_dev_ids, aux_pwiv->id);
	kfwee(aux_pwiv->edev->uwp_tbw);
	bp->edev = NUWW;
	kfwee(aux_pwiv->edev);
	kfwee(aux_pwiv);
	bp->aux_pwiv = NUWW;
}

static void bnxt_set_edev_info(stwuct bnxt_en_dev *edev, stwuct bnxt *bp)
{
	edev->net = bp->dev;
	edev->pdev = bp->pdev;
	edev->w2_db_size = bp->db_size;
	edev->w2_db_size_nc = bp->db_size;
	edev->w2_db_offset = bp->db_offset;

	if (bp->fwags & BNXT_FWAG_WOCEV1_CAP)
		edev->fwags |= BNXT_EN_FWAG_WOCEV1_CAP;
	if (bp->fwags & BNXT_FWAG_WOCEV2_CAP)
		edev->fwags |= BNXT_EN_FWAG_WOCEV2_CAP;
	if (bp->fwags & BNXT_FWAG_VF)
		edev->fwags |= BNXT_EN_FWAG_VF;

	edev->chip_num = bp->chip_num;
	edev->hw_wing_stats_size = bp->hw_wing_stats_size;
	edev->pf_powt_id = bp->pf.powt_id;
	edev->en_state = bp->state;
	edev->baw0 = bp->baw0;
	edev->uwp_tbw->msix_wequested = bnxt_get_uwp_msix_num(bp);
}

void bnxt_wdma_aux_device_init(stwuct bnxt *bp)
{
	stwuct auxiwiawy_device *aux_dev;
	stwuct bnxt_aux_pwiv *aux_pwiv;
	stwuct bnxt_en_dev *edev;
	stwuct bnxt_uwp *uwp;
	int wc;

	if (!(bp->fwags & BNXT_FWAG_WOCE_CAP))
		wetuwn;

	aux_pwiv = kzawwoc(sizeof(*bp->aux_pwiv), GFP_KEWNEW);
	if (!aux_pwiv)
		goto exit;

	aux_pwiv->id = ida_awwoc(&bnxt_aux_dev_ids, GFP_KEWNEW);
	if (aux_pwiv->id < 0) {
		netdev_wawn(bp->dev,
			    "ida awwoc faiwed fow WOCE auxiwiawy device\n");
		kfwee(aux_pwiv);
		goto exit;
	}

	aux_dev = &aux_pwiv->aux_dev;
	aux_dev->id = aux_pwiv->id;
	aux_dev->name = "wdma";
	aux_dev->dev.pawent = &bp->pdev->dev;
	aux_dev->dev.wewease = bnxt_aux_dev_wewease;

	wc = auxiwiawy_device_init(aux_dev);
	if (wc) {
		ida_fwee(&bnxt_aux_dev_ids, aux_pwiv->id);
		kfwee(aux_pwiv);
		goto exit;
	}
	bp->aux_pwiv = aux_pwiv;

	/* Fwom this point, aww cweanup wiww happen via the .wewease cawwback &
	 * any ewwow unwinding wiww need to incwude a caww to
	 * auxiwiawy_device_uninit.
	 */
	edev = kzawwoc(sizeof(*edev), GFP_KEWNEW);
	if (!edev)
		goto aux_dev_uninit;

	uwp = kzawwoc(sizeof(*uwp), GFP_KEWNEW);
	if (!uwp)
		goto aux_dev_uninit;

	edev->uwp_tbw = uwp;
	aux_pwiv->edev = edev;
	bp->edev = edev;
	bnxt_set_edev_info(edev, bp);

	wc = auxiwiawy_device_add(aux_dev);
	if (wc) {
		netdev_wawn(bp->dev,
			    "Faiwed to add auxiwiawy device fow WOCE\n");
		goto aux_dev_uninit;
	}

	wetuwn;

aux_dev_uninit:
	auxiwiawy_device_uninit(aux_dev);
exit:
	bp->fwags &= ~BNXT_FWAG_WOCE_CAP;
}
