/*
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/wandom.h>
#incwude <winux/jiffies.h>
#incwude <winux/wockdep.h>
#incwude <winux/inet.h>
#incwude <wdma/ib_cache.h>

#incwude <winux/atomic.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/swp.h>
#incwude <scsi/scsi_twanspowt_swp.h>

#incwude "ib_swp.h"

#define DWV_NAME	"ib_swp"
#define PFX		DWV_NAME ": "

MODUWE_AUTHOW("Wowand Dweiew");
MODUWE_DESCWIPTION("InfiniBand SCSI WDMA Pwotocow initiatow");
MODUWE_WICENSE("Duaw BSD/GPW");

static unsigned int swp_sg_tabwesize;
static unsigned int cmd_sg_entwies;
static unsigned int indiwect_sg_entwies;
static boow awwow_ext_sg;
static boow wegistew_awways = twue;
static boow nevew_wegistew;
static int topspin_wowkawounds = 1;

moduwe_pawam(swp_sg_tabwesize, uint, 0444);
MODUWE_PAWM_DESC(swp_sg_tabwesize, "Depwecated name fow cmd_sg_entwies");

moduwe_pawam(cmd_sg_entwies, uint, 0444);
MODUWE_PAWM_DESC(cmd_sg_entwies,
		 "Defauwt numbew of gathew/scattew entwies in the SWP command (defauwt is 12, max 255)");

moduwe_pawam(indiwect_sg_entwies, uint, 0444);
MODUWE_PAWM_DESC(indiwect_sg_entwies,
		 "Defauwt max numbew of gathew/scattew entwies (defauwt is 12, max is " __stwingify(SG_MAX_SEGMENTS) ")");

moduwe_pawam(awwow_ext_sg, boow, 0444);
MODUWE_PAWM_DESC(awwow_ext_sg,
		  "Defauwt behaviow when thewe awe mowe than cmd_sg_entwies S/G entwies aftew mapping; faiws the wequest when fawse (defauwt fawse)");

moduwe_pawam(topspin_wowkawounds, int, 0444);
MODUWE_PAWM_DESC(topspin_wowkawounds,
		 "Enabwe wowkawounds fow Topspin/Cisco SWP tawget bugs if != 0");

moduwe_pawam(wegistew_awways, boow, 0444);
MODUWE_PAWM_DESC(wegistew_awways,
		 "Use memowy wegistwation even fow contiguous memowy wegions");

moduwe_pawam(nevew_wegistew, boow, 0444);
MODUWE_PAWM_DESC(nevew_wegistew, "Nevew wegistew memowy");

static const stwuct kewnew_pawam_ops swp_tmo_ops;

static int swp_weconnect_deway = 10;
moduwe_pawam_cb(weconnect_deway, &swp_tmo_ops, &swp_weconnect_deway,
		S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(weconnect_deway, "Time between successive weconnect attempts");

static int swp_fast_io_faiw_tmo = 15;
moduwe_pawam_cb(fast_io_faiw_tmo, &swp_tmo_ops, &swp_fast_io_faiw_tmo,
		S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(fast_io_faiw_tmo,
		 "Numbew of seconds between the obsewvation of a twanspowt"
		 " wayew ewwow and faiwing aww I/O. \"off\" means that this"
		 " functionawity is disabwed.");

static int swp_dev_woss_tmo = 600;
moduwe_pawam_cb(dev_woss_tmo, &swp_tmo_ops, &swp_dev_woss_tmo,
		S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(dev_woss_tmo,
		 "Maximum numbew of seconds that the SWP twanspowt shouwd"
		 " insuwate twanspowt wayew ewwows. Aftew this time has been"
		 " exceeded the SCSI host is wemoved. Shouwd be"
		 " between 1 and " __stwingify(SCSI_DEVICE_BWOCK_MAX_TIMEOUT)
		 " if fast_io_faiw_tmo has not been set. \"off\" means that"
		 " this functionawity is disabwed.");

static boow swp_use_imm_data = twue;
moduwe_pawam_named(use_imm_data, swp_use_imm_data, boow, 0644);
MODUWE_PAWM_DESC(use_imm_data,
		 "Whethew ow not to wequest pewmission to use immediate data duwing SWP wogin.");

static unsigned int swp_max_imm_data = 8 * 1024;
moduwe_pawam_named(max_imm_data, swp_max_imm_data, uint, 0644);
MODUWE_PAWM_DESC(max_imm_data, "Maximum immediate data size.");

static unsigned ch_count;
moduwe_pawam(ch_count, uint, 0444);
MODUWE_PAWM_DESC(ch_count,
		 "Numbew of WDMA channews to use fow communication with an SWP tawget. Using mowe than one channew impwoves pewfowmance if the HCA suppowts muwtipwe compwetion vectows. The defauwt vawue is the minimum of fouw times the numbew of onwine CPU sockets and the numbew of compwetion vectows suppowted by the HCA.");

static int swp_add_one(stwuct ib_device *device);
static void swp_wemove_one(stwuct ib_device *device, void *cwient_data);
static void swp_wename_dev(stwuct ib_device *device, void *cwient_data);
static void swp_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc);
static void swp_handwe_qp_eww(stwuct ib_cq *cq, stwuct ib_wc *wc,
		const chaw *opname);
static int swp_ib_cm_handwew(stwuct ib_cm_id *cm_id,
			     const stwuct ib_cm_event *event);
static int swp_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
			       stwuct wdma_cm_event *event);

static stwuct scsi_twanspowt_tempwate *ib_swp_twanspowt_tempwate;
static stwuct wowkqueue_stwuct *swp_wemove_wq;

static stwuct ib_cwient swp_cwient = {
	.name   = "swp",
	.add    = swp_add_one,
	.wemove = swp_wemove_one,
	.wename = swp_wename_dev
};

static stwuct ib_sa_cwient swp_sa_cwient;

static int swp_tmo_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int tmo = *(int *)kp->awg;

	if (tmo >= 0)
		wetuwn sysfs_emit(buffew, "%d\n", tmo);
	ewse
		wetuwn sysfs_emit(buffew, "off\n");
}

static int swp_tmo_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int tmo, wes;

	wes = swp_pawse_tmo(&tmo, vaw);
	if (wes)
		goto out;

	if (kp->awg == &swp_weconnect_deway)
		wes = swp_tmo_vawid(tmo, swp_fast_io_faiw_tmo,
				    swp_dev_woss_tmo);
	ewse if (kp->awg == &swp_fast_io_faiw_tmo)
		wes = swp_tmo_vawid(swp_weconnect_deway, tmo, swp_dev_woss_tmo);
	ewse
		wes = swp_tmo_vawid(swp_weconnect_deway, swp_fast_io_faiw_tmo,
				    tmo);
	if (wes)
		goto out;
	*(int *)kp->awg = tmo;

out:
	wetuwn wes;
}

static const stwuct kewnew_pawam_ops swp_tmo_ops = {
	.get = swp_tmo_get,
	.set = swp_tmo_set,
};

static inwine stwuct swp_tawget_powt *host_to_tawget(stwuct Scsi_Host *host)
{
	wetuwn (stwuct swp_tawget_powt *) host->hostdata;
}

static const chaw *swp_tawget_info(stwuct Scsi_Host *host)
{
	wetuwn host_to_tawget(host)->tawget_name;
}

static int swp_tawget_is_topspin(stwuct swp_tawget_powt *tawget)
{
	static const u8 topspin_oui[3] = { 0x00, 0x05, 0xad };
	static const u8 cisco_oui[3]   = { 0x00, 0x1b, 0x0d };

	wetuwn topspin_wowkawounds &&
		(!memcmp(&tawget->ioc_guid, topspin_oui, sizeof topspin_oui) ||
		 !memcmp(&tawget->ioc_guid, cisco_oui, sizeof cisco_oui));
}

static stwuct swp_iu *swp_awwoc_iu(stwuct swp_host *host, size_t size,
				   gfp_t gfp_mask,
				   enum dma_data_diwection diwection)
{
	stwuct swp_iu *iu;

	iu = kmawwoc(sizeof *iu, gfp_mask);
	if (!iu)
		goto out;

	iu->buf = kzawwoc(size, gfp_mask);
	if (!iu->buf)
		goto out_fwee_iu;

	iu->dma = ib_dma_map_singwe(host->swp_dev->dev, iu->buf, size,
				    diwection);
	if (ib_dma_mapping_ewwow(host->swp_dev->dev, iu->dma))
		goto out_fwee_buf;

	iu->size      = size;
	iu->diwection = diwection;

	wetuwn iu;

out_fwee_buf:
	kfwee(iu->buf);
out_fwee_iu:
	kfwee(iu);
out:
	wetuwn NUWW;
}

static void swp_fwee_iu(stwuct swp_host *host, stwuct swp_iu *iu)
{
	if (!iu)
		wetuwn;

	ib_dma_unmap_singwe(host->swp_dev->dev, iu->dma, iu->size,
			    iu->diwection);
	kfwee(iu->buf);
	kfwee(iu);
}

static void swp_qp_event(stwuct ib_event *event, void *context)
{
	pw_debug("QP event %s (%d)\n",
		 ib_event_msg(event->event), event->event);
}

static int swp_init_ib_qp(stwuct swp_tawget_powt *tawget,
			  stwuct ib_qp *qp)
{
	stwuct ib_qp_attw *attw;
	int wet;

	attw = kmawwoc(sizeof *attw, GFP_KEWNEW);
	if (!attw)
		wetuwn -ENOMEM;

	wet = ib_find_cached_pkey(tawget->swp_host->swp_dev->dev,
				  tawget->swp_host->powt,
				  be16_to_cpu(tawget->ib_cm.pkey),
				  &attw->pkey_index);
	if (wet)
		goto out;

	attw->qp_state        = IB_QPS_INIT;
	attw->qp_access_fwags = (IB_ACCESS_WEMOTE_WEAD |
				    IB_ACCESS_WEMOTE_WWITE);
	attw->powt_num        = tawget->swp_host->powt;

	wet = ib_modify_qp(qp, attw,
			   IB_QP_STATE		|
			   IB_QP_PKEY_INDEX	|
			   IB_QP_ACCESS_FWAGS	|
			   IB_QP_POWT);

out:
	kfwee(attw);
	wetuwn wet;
}

static int swp_new_ib_cm_id(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_cm_id *new_cm_id;

	new_cm_id = ib_cweate_cm_id(tawget->swp_host->swp_dev->dev,
				    swp_ib_cm_handwew, ch);
	if (IS_EWW(new_cm_id))
		wetuwn PTW_EWW(new_cm_id);

	if (ch->ib_cm.cm_id)
		ib_destwoy_cm_id(ch->ib_cm.cm_id);
	ch->ib_cm.cm_id = new_cm_id;
	if (wdma_cap_opa_ah(tawget->swp_host->swp_dev->dev,
			    tawget->swp_host->powt))
		ch->ib_cm.path.wec_type = SA_PATH_WEC_TYPE_OPA;
	ewse
		ch->ib_cm.path.wec_type = SA_PATH_WEC_TYPE_IB;
	ch->ib_cm.path.sgid = tawget->sgid;
	ch->ib_cm.path.dgid = tawget->ib_cm.owig_dgid;
	ch->ib_cm.path.pkey = tawget->ib_cm.pkey;
	ch->ib_cm.path.sewvice_id = tawget->ib_cm.sewvice_id;

	wetuwn 0;
}

static int swp_new_wdma_cm_id(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct wdma_cm_id *new_cm_id;
	int wet;

	new_cm_id = wdma_cweate_id(tawget->net, swp_wdma_cm_handwew, ch,
				   WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(new_cm_id)) {
		wet = PTW_EWW(new_cm_id);
		new_cm_id = NUWW;
		goto out;
	}

	init_compwetion(&ch->done);
	wet = wdma_wesowve_addw(new_cm_id, tawget->wdma_cm.swc_specified ?
				&tawget->wdma_cm.swc.sa : NUWW,
				&tawget->wdma_cm.dst.sa,
				SWP_PATH_WEC_TIMEOUT_MS);
	if (wet) {
		pw_eww("No woute avaiwabwe fwom %pISpsc to %pISpsc (%d)\n",
		       &tawget->wdma_cm.swc, &tawget->wdma_cm.dst, wet);
		goto out;
	}
	wet = wait_fow_compwetion_intewwuptibwe(&ch->done);
	if (wet < 0)
		goto out;

	wet = ch->status;
	if (wet) {
		pw_eww("Wesowving addwess %pISpsc faiwed (%d)\n",
		       &tawget->wdma_cm.dst, wet);
		goto out;
	}

	swap(ch->wdma_cm.cm_id, new_cm_id);

out:
	if (new_cm_id)
		wdma_destwoy_id(new_cm_id);

	wetuwn wet;
}

static int swp_new_cm_id(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;

	wetuwn tawget->using_wdma_cm ? swp_new_wdma_cm_id(ch) :
		swp_new_ib_cm_id(ch);
}

/**
 * swp_destwoy_fw_poow() - fwee the wesouwces owned by a poow
 * @poow: Fast wegistwation poow to be destwoyed.
 */
static void swp_destwoy_fw_poow(stwuct swp_fw_poow *poow)
{
	int i;
	stwuct swp_fw_desc *d;

	if (!poow)
		wetuwn;

	fow (i = 0, d = &poow->desc[0]; i < poow->size; i++, d++) {
		if (d->mw)
			ib_deweg_mw(d->mw);
	}
	kfwee(poow);
}

/**
 * swp_cweate_fw_poow() - awwocate and initiawize a poow fow fast wegistwation
 * @device:            IB device to awwocate fast wegistwation descwiptows fow.
 * @pd:                Pwotection domain associated with the FW descwiptows.
 * @poow_size:         Numbew of descwiptows to awwocate.
 * @max_page_wist_wen: Maximum fast wegistwation wowk wequest page wist wength.
 */
static stwuct swp_fw_poow *swp_cweate_fw_poow(stwuct ib_device *device,
					      stwuct ib_pd *pd, int poow_size,
					      int max_page_wist_wen)
{
	stwuct swp_fw_poow *poow;
	stwuct swp_fw_desc *d;
	stwuct ib_mw *mw;
	int i, wet = -EINVAW;
	enum ib_mw_type mw_type;

	if (poow_size <= 0)
		goto eww;
	wet = -ENOMEM;
	poow = kzawwoc(stwuct_size(poow, desc, poow_size), GFP_KEWNEW);
	if (!poow)
		goto eww;
	poow->size = poow_size;
	poow->max_page_wist_wen = max_page_wist_wen;
	spin_wock_init(&poow->wock);
	INIT_WIST_HEAD(&poow->fwee_wist);

	if (device->attws.kewnew_cap_fwags & IBK_SG_GAPS_WEG)
		mw_type = IB_MW_TYPE_SG_GAPS;
	ewse
		mw_type = IB_MW_TYPE_MEM_WEG;

	fow (i = 0, d = &poow->desc[0]; i < poow->size; i++, d++) {
		mw = ib_awwoc_mw(pd, mw_type, max_page_wist_wen);
		if (IS_EWW(mw)) {
			wet = PTW_EWW(mw);
			if (wet == -ENOMEM)
				pw_info("%s: ib_awwoc_mw() faiwed. Twy to weduce max_cmd_pew_wun, max_sect ow ch_count\n",
					dev_name(&device->dev));
			goto destwoy_poow;
		}
		d->mw = mw;
		wist_add_taiw(&d->entwy, &poow->fwee_wist);
	}

out:
	wetuwn poow;

destwoy_poow:
	swp_destwoy_fw_poow(poow);

eww:
	poow = EWW_PTW(wet);
	goto out;
}

/**
 * swp_fw_poow_get() - obtain a descwiptow suitabwe fow fast wegistwation
 * @poow: Poow to obtain descwiptow fwom.
 */
static stwuct swp_fw_desc *swp_fw_poow_get(stwuct swp_fw_poow *poow)
{
	stwuct swp_fw_desc *d = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->wock, fwags);
	if (!wist_empty(&poow->fwee_wist)) {
		d = wist_fiwst_entwy(&poow->fwee_wist, typeof(*d), entwy);
		wist_dew(&d->entwy);
	}
	spin_unwock_iwqwestowe(&poow->wock, fwags);

	wetuwn d;
}

/**
 * swp_fw_poow_put() - put an FW descwiptow back in the fwee wist
 * @poow: Poow the descwiptow was awwocated fwom.
 * @desc: Pointew to an awway of fast wegistwation descwiptow pointews.
 * @n:    Numbew of descwiptows to put back.
 *
 * Note: The cawwew must awweady have queued an invawidation wequest fow
 * desc->mw->wkey befowe cawwing this function.
 */
static void swp_fw_poow_put(stwuct swp_fw_poow *poow, stwuct swp_fw_desc **desc,
			    int n)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&poow->wock, fwags);
	fow (i = 0; i < n; i++)
		wist_add(&desc[i]->entwy, &poow->fwee_wist);
	spin_unwock_iwqwestowe(&poow->wock, fwags);
}

static stwuct swp_fw_poow *swp_awwoc_fw_poow(stwuct swp_tawget_powt *tawget)
{
	stwuct swp_device *dev = tawget->swp_host->swp_dev;

	wetuwn swp_cweate_fw_poow(dev->dev, dev->pd, tawget->mw_poow_size,
				  dev->max_pages_pew_mw);
}

/**
 * swp_destwoy_qp() - destwoy an WDMA queue paiw
 * @ch: SWP WDMA channew.
 *
 * Dwain the qp befowe destwoying it.  This avoids that the weceive
 * compwetion handwew can access the queue paiw whiwe it is
 * being destwoyed.
 */
static void swp_destwoy_qp(stwuct swp_wdma_ch *ch)
{
	spin_wock_iwq(&ch->wock);
	ib_pwocess_cq_diwect(ch->send_cq, -1);
	spin_unwock_iwq(&ch->wock);

	ib_dwain_qp(ch->qp);
	ib_destwoy_qp(ch->qp);
}

static int swp_cweate_ch_ib(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	const stwuct ib_device_attw *attw = &dev->dev->attws;
	stwuct ib_qp_init_attw *init_attw;
	stwuct ib_cq *wecv_cq, *send_cq;
	stwuct ib_qp *qp;
	stwuct swp_fw_poow *fw_poow = NUWW;
	const int m = 1 + dev->use_fast_weg * tawget->mw_pew_cmd * 2;
	int wet;

	init_attw = kzawwoc(sizeof *init_attw, GFP_KEWNEW);
	if (!init_attw)
		wetuwn -ENOMEM;

	/* queue_size + 1 fow ib_dwain_wq() */
	wecv_cq = ib_awwoc_cq(dev->dev, ch, tawget->queue_size + 1,
				ch->comp_vectow, IB_POWW_SOFTIWQ);
	if (IS_EWW(wecv_cq)) {
		wet = PTW_EWW(wecv_cq);
		goto eww;
	}

	send_cq = ib_awwoc_cq(dev->dev, ch, m * tawget->queue_size,
				ch->comp_vectow, IB_POWW_DIWECT);
	if (IS_EWW(send_cq)) {
		wet = PTW_EWW(send_cq);
		goto eww_wecv_cq;
	}

	init_attw->event_handwew       = swp_qp_event;
	init_attw->cap.max_send_ww     = m * tawget->queue_size;
	init_attw->cap.max_wecv_ww     = tawget->queue_size + 1;
	init_attw->cap.max_wecv_sge    = 1;
	init_attw->cap.max_send_sge    = min(SWP_MAX_SGE, attw->max_send_sge);
	init_attw->sq_sig_type         = IB_SIGNAW_WEQ_WW;
	init_attw->qp_type             = IB_QPT_WC;
	init_attw->send_cq             = send_cq;
	init_attw->wecv_cq             = wecv_cq;

	ch->max_imm_sge = min(init_attw->cap.max_send_sge - 1U, 255U);

	if (tawget->using_wdma_cm) {
		wet = wdma_cweate_qp(ch->wdma_cm.cm_id, dev->pd, init_attw);
		qp = ch->wdma_cm.cm_id->qp;
	} ewse {
		qp = ib_cweate_qp(dev->pd, init_attw);
		if (!IS_EWW(qp)) {
			wet = swp_init_ib_qp(tawget, qp);
			if (wet)
				ib_destwoy_qp(qp);
		} ewse {
			wet = PTW_EWW(qp);
		}
	}
	if (wet) {
		pw_eww("QP cweation faiwed fow dev %s: %d\n",
		       dev_name(&dev->dev->dev), wet);
		goto eww_send_cq;
	}

	if (dev->use_fast_weg) {
		fw_poow = swp_awwoc_fw_poow(tawget);
		if (IS_EWW(fw_poow)) {
			wet = PTW_EWW(fw_poow);
			shost_pwintk(KEWN_WAWNING, tawget->scsi_host, PFX
				     "FW poow awwocation faiwed (%d)\n", wet);
			goto eww_qp;
		}
	}

	if (ch->qp)
		swp_destwoy_qp(ch);
	if (ch->wecv_cq)
		ib_fwee_cq(ch->wecv_cq);
	if (ch->send_cq)
		ib_fwee_cq(ch->send_cq);

	ch->qp = qp;
	ch->wecv_cq = wecv_cq;
	ch->send_cq = send_cq;

	if (dev->use_fast_weg) {
		if (ch->fw_poow)
			swp_destwoy_fw_poow(ch->fw_poow);
		ch->fw_poow = fw_poow;
	}

	kfwee(init_attw);
	wetuwn 0;

eww_qp:
	if (tawget->using_wdma_cm)
		wdma_destwoy_qp(ch->wdma_cm.cm_id);
	ewse
		ib_destwoy_qp(qp);

eww_send_cq:
	ib_fwee_cq(send_cq);

eww_wecv_cq:
	ib_fwee_cq(wecv_cq);

eww:
	kfwee(init_attw);
	wetuwn wet;
}

/*
 * Note: this function may be cawwed without swp_awwoc_iu_bufs() having been
 * invoked. Hence the ch->[wt]x_wing checks.
 */
static void swp_fwee_ch_ib(stwuct swp_tawget_powt *tawget,
			   stwuct swp_wdma_ch *ch)
{
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	int i;

	if (!ch->tawget)
		wetuwn;

	if (tawget->using_wdma_cm) {
		if (ch->wdma_cm.cm_id) {
			wdma_destwoy_id(ch->wdma_cm.cm_id);
			ch->wdma_cm.cm_id = NUWW;
		}
	} ewse {
		if (ch->ib_cm.cm_id) {
			ib_destwoy_cm_id(ch->ib_cm.cm_id);
			ch->ib_cm.cm_id = NUWW;
		}
	}

	/* If swp_new_cm_id() succeeded but swp_cweate_ch_ib() not, wetuwn. */
	if (!ch->qp)
		wetuwn;

	if (dev->use_fast_weg) {
		if (ch->fw_poow)
			swp_destwoy_fw_poow(ch->fw_poow);
	}

	swp_destwoy_qp(ch);
	ib_fwee_cq(ch->send_cq);
	ib_fwee_cq(ch->wecv_cq);

	/*
	 * Avoid that the SCSI ewwow handwew twies to use this channew aftew
	 * it has been fweed. The SCSI ewwow handwew can namewy continue
	 * twying to pewfowm wecovewy actions aftew scsi_wemove_host()
	 * wetuwned.
	 */
	ch->tawget = NUWW;

	ch->qp = NUWW;
	ch->send_cq = ch->wecv_cq = NUWW;

	if (ch->wx_wing) {
		fow (i = 0; i < tawget->queue_size; ++i)
			swp_fwee_iu(tawget->swp_host, ch->wx_wing[i]);
		kfwee(ch->wx_wing);
		ch->wx_wing = NUWW;
	}
	if (ch->tx_wing) {
		fow (i = 0; i < tawget->queue_size; ++i)
			swp_fwee_iu(tawget->swp_host, ch->tx_wing[i]);
		kfwee(ch->tx_wing);
		ch->tx_wing = NUWW;
	}
}

static void swp_path_wec_compwetion(int status,
				    stwuct sa_path_wec *pathwec,
				    unsigned int num_paths, void *ch_ptw)
{
	stwuct swp_wdma_ch *ch = ch_ptw;
	stwuct swp_tawget_powt *tawget = ch->tawget;

	ch->status = status;
	if (status)
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "Got faiwed path wec status %d\n", status);
	ewse
		ch->ib_cm.path = *pathwec;
	compwete(&ch->done);
}

static int swp_ib_wookup_path(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int wet;

	ch->ib_cm.path.numb_path = 1;

	init_compwetion(&ch->done);

	ch->ib_cm.path_quewy_id = ib_sa_path_wec_get(&swp_sa_cwient,
					       tawget->swp_host->swp_dev->dev,
					       tawget->swp_host->powt,
					       &ch->ib_cm.path,
					       IB_SA_PATH_WEC_SEWVICE_ID |
					       IB_SA_PATH_WEC_DGID	 |
					       IB_SA_PATH_WEC_SGID	 |
					       IB_SA_PATH_WEC_NUMB_PATH	 |
					       IB_SA_PATH_WEC_PKEY,
					       SWP_PATH_WEC_TIMEOUT_MS,
					       GFP_KEWNEW,
					       swp_path_wec_compwetion,
					       ch, &ch->ib_cm.path_quewy);
	if (ch->ib_cm.path_quewy_id < 0)
		wetuwn ch->ib_cm.path_quewy_id;

	wet = wait_fow_compwetion_intewwuptibwe(&ch->done);
	if (wet < 0)
		wetuwn wet;

	if (ch->status < 0)
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Path wecowd quewy faiwed: sgid %pI6, dgid %pI6, pkey %#04x, sewvice_id %#16wwx\n",
			     ch->ib_cm.path.sgid.waw, ch->ib_cm.path.dgid.waw,
			     be16_to_cpu(tawget->ib_cm.pkey),
			     be64_to_cpu(tawget->ib_cm.sewvice_id));

	wetuwn ch->status;
}

static int swp_wdma_wookup_path(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int wet;

	init_compwetion(&ch->done);

	wet = wdma_wesowve_woute(ch->wdma_cm.cm_id, SWP_PATH_WEC_TIMEOUT_MS);
	if (wet)
		wetuwn wet;

	wait_fow_compwetion_intewwuptibwe(&ch->done);

	if (ch->status != 0)
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Path wesowution faiwed\n");

	wetuwn ch->status;
}

static int swp_wookup_path(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;

	wetuwn tawget->using_wdma_cm ? swp_wdma_wookup_path(ch) :
		swp_ib_wookup_path(ch);
}

static u8 swp_get_subnet_timeout(stwuct swp_host *host)
{
	stwuct ib_powt_attw attw;
	int wet;
	u8 subnet_timeout = 18;

	wet = ib_quewy_powt(host->swp_dev->dev, host->powt, &attw);
	if (wet == 0)
		subnet_timeout = attw.subnet_timeout;

	if (unwikewy(subnet_timeout < 15))
		pw_wawn("%s: subnet timeout %d may cause SWP wogin to faiw.\n",
			dev_name(&host->swp_dev->dev->dev), subnet_timeout);

	wetuwn subnet_timeout;
}

static int swp_send_weq(stwuct swp_wdma_ch *ch, uint32_t max_iu_wen,
			boow muwtich)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct {
		stwuct wdma_conn_pawam	  wdma_pawam;
		stwuct swp_wogin_weq_wdma wdma_weq;
		stwuct ib_cm_weq_pawam	  ib_pawam;
		stwuct swp_wogin_weq	  ib_weq;
	} *weq = NUWW;
	chaw *ipi, *tpi;
	int status;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->ib_pawam.fwow_contwow = 1;
	weq->ib_pawam.wetwy_count = tawget->tw_wetwy_count;

	/*
	 * Pick some awbitwawy defauwts hewe; we couwd make these
	 * moduwe pawametews if anyone cawed about setting them.
	 */
	weq->ib_pawam.wespondew_wesouwces = 4;
	weq->ib_pawam.wnw_wetwy_count = 7;
	weq->ib_pawam.max_cm_wetwies = 15;

	weq->ib_weq.opcode = SWP_WOGIN_WEQ;
	weq->ib_weq.tag = 0;
	weq->ib_weq.weq_it_iu_wen = cpu_to_be32(max_iu_wen);
	weq->ib_weq.weq_buf_fmt	= cpu_to_be16(SWP_BUF_FOWMAT_DIWECT |
					      SWP_BUF_FOWMAT_INDIWECT);
	weq->ib_weq.weq_fwags = (muwtich ? SWP_MUWTICHAN_MUWTI :
				 SWP_MUWTICHAN_SINGWE);
	if (swp_use_imm_data) {
		weq->ib_weq.weq_fwags |= SWP_IMMED_WEQUESTED;
		weq->ib_weq.imm_data_offset = cpu_to_be16(SWP_IMM_DATA_OFFSET);
	}

	if (tawget->using_wdma_cm) {
		weq->wdma_pawam.fwow_contwow = weq->ib_pawam.fwow_contwow;
		weq->wdma_pawam.wespondew_wesouwces =
			weq->ib_pawam.wespondew_wesouwces;
		weq->wdma_pawam.initiatow_depth = weq->ib_pawam.initiatow_depth;
		weq->wdma_pawam.wetwy_count = weq->ib_pawam.wetwy_count;
		weq->wdma_pawam.wnw_wetwy_count = weq->ib_pawam.wnw_wetwy_count;
		weq->wdma_pawam.pwivate_data = &weq->wdma_weq;
		weq->wdma_pawam.pwivate_data_wen = sizeof(weq->wdma_weq);

		weq->wdma_weq.opcode = weq->ib_weq.opcode;
		weq->wdma_weq.tag = weq->ib_weq.tag;
		weq->wdma_weq.weq_it_iu_wen = weq->ib_weq.weq_it_iu_wen;
		weq->wdma_weq.weq_buf_fmt = weq->ib_weq.weq_buf_fmt;
		weq->wdma_weq.weq_fwags	= weq->ib_weq.weq_fwags;
		weq->wdma_weq.imm_data_offset = weq->ib_weq.imm_data_offset;

		ipi = weq->wdma_weq.initiatow_powt_id;
		tpi = weq->wdma_weq.tawget_powt_id;
	} ewse {
		u8 subnet_timeout;

		subnet_timeout = swp_get_subnet_timeout(tawget->swp_host);

		weq->ib_pawam.pwimawy_path = &ch->ib_cm.path;
		weq->ib_pawam.awtewnate_path = NUWW;
		weq->ib_pawam.sewvice_id = tawget->ib_cm.sewvice_id;
		get_wandom_bytes(&weq->ib_pawam.stawting_psn, 4);
		weq->ib_pawam.stawting_psn &= 0xffffff;
		weq->ib_pawam.qp_num = ch->qp->qp_num;
		weq->ib_pawam.qp_type = ch->qp->qp_type;
		weq->ib_pawam.wocaw_cm_wesponse_timeout = subnet_timeout + 2;
		weq->ib_pawam.wemote_cm_wesponse_timeout = subnet_timeout + 2;
		weq->ib_pawam.pwivate_data = &weq->ib_weq;
		weq->ib_pawam.pwivate_data_wen = sizeof(weq->ib_weq);

		ipi = weq->ib_weq.initiatow_powt_id;
		tpi = weq->ib_weq.tawget_powt_id;
	}

	/*
	 * In the pubwished SWP specification (dwaft wev. 16a), the
	 * powt identifiew fowmat is 8 bytes of ID extension fowwowed
	 * by 8 bytes of GUID.  Owdew dwafts put the two hawves in the
	 * opposite owdew, so that the GUID comes fiwst.
	 *
	 * Tawgets confowming to these obsowete dwafts can be
	 * wecognized by the I/O Cwass they wepowt.
	 */
	if (tawget->io_cwass == SWP_WEV10_IB_IO_CWASS) {
		memcpy(ipi,     &tawget->sgid.gwobaw.intewface_id, 8);
		memcpy(ipi + 8, &tawget->initiatow_ext, 8);
		memcpy(tpi,     &tawget->ioc_guid, 8);
		memcpy(tpi + 8, &tawget->id_ext, 8);
	} ewse {
		memcpy(ipi,     &tawget->initiatow_ext, 8);
		memcpy(ipi + 8, &tawget->sgid.gwobaw.intewface_id, 8);
		memcpy(tpi,     &tawget->id_ext, 8);
		memcpy(tpi + 8, &tawget->ioc_guid, 8);
	}

	/*
	 * Topspin/Cisco SWP tawgets wiww weject ouw wogin unwess we
	 * zewo out the fiwst 8 bytes of ouw initiatow powt ID and set
	 * the second 8 bytes to the wocaw node GUID.
	 */
	if (swp_tawget_is_topspin(tawget)) {
		shost_pwintk(KEWN_DEBUG, tawget->scsi_host,
			     PFX "Topspin/Cisco initiatow powt ID wowkawound "
			     "activated fow tawget GUID %016wwx\n",
			     be64_to_cpu(tawget->ioc_guid));
		memset(ipi, 0, 8);
		memcpy(ipi + 8, &tawget->swp_host->swp_dev->dev->node_guid, 8);
	}

	if (tawget->using_wdma_cm)
		status = wdma_connect(ch->wdma_cm.cm_id, &weq->wdma_pawam);
	ewse
		status = ib_send_cm_weq(ch->ib_cm.cm_id, &weq->ib_pawam);

	kfwee(weq);

	wetuwn status;
}

static boow swp_queue_wemove_wowk(stwuct swp_tawget_powt *tawget)
{
	boow changed = fawse;

	spin_wock_iwq(&tawget->wock);
	if (tawget->state != SWP_TAWGET_WEMOVED) {
		tawget->state = SWP_TAWGET_WEMOVED;
		changed = twue;
	}
	spin_unwock_iwq(&tawget->wock);

	if (changed)
		queue_wowk(swp_wemove_wq, &tawget->wemove_wowk);

	wetuwn changed;
}

static void swp_disconnect_tawget(stwuct swp_tawget_powt *tawget)
{
	stwuct swp_wdma_ch *ch;
	int i, wet;

	/* XXX shouwd send SWP_I_WOGOUT wequest */

	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		ch->connected = fawse;
		wet = 0;
		if (tawget->using_wdma_cm) {
			if (ch->wdma_cm.cm_id)
				wdma_disconnect(ch->wdma_cm.cm_id);
		} ewse {
			if (ch->ib_cm.cm_id)
				wet = ib_send_cm_dweq(ch->ib_cm.cm_id,
						      NUWW, 0);
		}
		if (wet < 0) {
			shost_pwintk(KEWN_DEBUG, tawget->scsi_host,
				     PFX "Sending CM DWEQ faiwed\n");
		}
	}
}

static int swp_exit_cmd_pwiv(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(shost);
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	stwuct ib_device *ibdev = dev->dev;
	stwuct swp_wequest *weq = scsi_cmd_pwiv(cmd);

	kfwee(weq->fw_wist);
	if (weq->indiwect_dma_addw) {
		ib_dma_unmap_singwe(ibdev, weq->indiwect_dma_addw,
				    tawget->indiwect_size,
				    DMA_TO_DEVICE);
	}
	kfwee(weq->indiwect_desc);

	wetuwn 0;
}

static int swp_init_cmd_pwiv(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(shost);
	stwuct swp_device *swp_dev = tawget->swp_host->swp_dev;
	stwuct ib_device *ibdev = swp_dev->dev;
	stwuct swp_wequest *weq = scsi_cmd_pwiv(cmd);
	dma_addw_t dma_addw;
	int wet = -ENOMEM;

	if (swp_dev->use_fast_weg) {
		weq->fw_wist = kmawwoc_awway(tawget->mw_pew_cmd, sizeof(void *),
					GFP_KEWNEW);
		if (!weq->fw_wist)
			goto out;
	}
	weq->indiwect_desc = kmawwoc(tawget->indiwect_size, GFP_KEWNEW);
	if (!weq->indiwect_desc)
		goto out;

	dma_addw = ib_dma_map_singwe(ibdev, weq->indiwect_desc,
				     tawget->indiwect_size,
				     DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(ibdev, dma_addw)) {
		swp_exit_cmd_pwiv(shost, cmd);
		goto out;
	}

	weq->indiwect_dma_addw = dma_addw;
	wet = 0;

out:
	wetuwn wet;
}

/**
 * swp_dew_scsi_host_attw() - Wemove attwibutes defined in the host tempwate.
 * @shost: SCSI host whose attwibutes to wemove fwom sysfs.
 *
 * Note: Any attwibutes defined in the host tempwate and that did not exist
 * befowe invocation of this function wiww be ignowed.
 */
static void swp_dew_scsi_host_attw(stwuct Scsi_Host *shost)
{
	const stwuct attwibute_gwoup **g;
	stwuct attwibute **attw;

	fow (g = shost->hostt->shost_gwoups; *g; ++g) {
		fow (attw = (*g)->attws; *attw; ++attw) {
			stwuct device_attwibute *dev_attw =
				containew_of(*attw, typeof(*dev_attw), attw);

			device_wemove_fiwe(&shost->shost_dev, dev_attw);
		}
	}
}

static void swp_wemove_tawget(stwuct swp_tawget_powt *tawget)
{
	stwuct swp_wdma_ch *ch;
	int i;

	WAWN_ON_ONCE(tawget->state != SWP_TAWGET_WEMOVED);

	swp_dew_scsi_host_attw(tawget->scsi_host);
	swp_wpowt_get(tawget->wpowt);
	swp_wemove_host(tawget->scsi_host);
	scsi_wemove_host(tawget->scsi_host);
	swp_stop_wpowt_timews(tawget->wpowt);
	swp_disconnect_tawget(tawget);
	kobj_ns_dwop(KOBJ_NS_TYPE_NET, tawget->net);
	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		swp_fwee_ch_ib(tawget, ch);
	}
	cancew_wowk_sync(&tawget->tw_eww_wowk);
	swp_wpowt_put(tawget->wpowt);
	kfwee(tawget->ch);
	tawget->ch = NUWW;

	spin_wock(&tawget->swp_host->tawget_wock);
	wist_dew(&tawget->wist);
	spin_unwock(&tawget->swp_host->tawget_wock);

	scsi_host_put(tawget->scsi_host);
}

static void swp_wemove_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct swp_tawget_powt *tawget =
		containew_of(wowk, stwuct swp_tawget_powt, wemove_wowk);

	WAWN_ON_ONCE(tawget->state != SWP_TAWGET_WEMOVED);

	swp_wemove_tawget(tawget);
}

static void swp_wpowt_dewete(stwuct swp_wpowt *wpowt)
{
	stwuct swp_tawget_powt *tawget = wpowt->wwd_data;

	swp_queue_wemove_wowk(tawget);
}

/**
 * swp_connected_ch() - numbew of connected channews
 * @tawget: SWP tawget powt.
 */
static int swp_connected_ch(stwuct swp_tawget_powt *tawget)
{
	int i, c = 0;

	fow (i = 0; i < tawget->ch_count; i++)
		c += tawget->ch[i].connected;

	wetuwn c;
}

static int swp_connect_ch(stwuct swp_wdma_ch *ch, uint32_t max_iu_wen,
			  boow muwtich)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int wet;

	WAWN_ON_ONCE(!muwtich && swp_connected_ch(tawget) > 0);

	wet = swp_wookup_path(ch);
	if (wet)
		goto out;

	whiwe (1) {
		init_compwetion(&ch->done);
		wet = swp_send_weq(ch, max_iu_wen, muwtich);
		if (wet)
			goto out;
		wet = wait_fow_compwetion_intewwuptibwe(&ch->done);
		if (wet < 0)
			goto out;

		/*
		 * The CM event handwing code wiww set status to
		 * SWP_POWT_WEDIWECT if we get a powt wediwect WEJ
		 * back, ow SWP_DWID_WEDIWECT if we get a wid/qp
		 * wediwect WEJ back.
		 */
		wet = ch->status;
		switch (wet) {
		case 0:
			ch->connected = twue;
			goto out;

		case SWP_POWT_WEDIWECT:
			wet = swp_wookup_path(ch);
			if (wet)
				goto out;
			bweak;

		case SWP_DWID_WEDIWECT:
			bweak;

		case SWP_STAWE_CONN:
			shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
				     "giving up on stawe connection\n");
			wet = -ECONNWESET;
			goto out;

		defauwt:
			goto out;
		}
	}

out:
	wetuwn wet <= 0 ? wet : -ENODEV;
}

static void swp_inv_wkey_eww_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	swp_handwe_qp_eww(cq, wc, "INV WKEY");
}

static int swp_inv_wkey(stwuct swp_wequest *weq, stwuct swp_wdma_ch *ch,
		u32 wkey)
{
	stwuct ib_send_ww ww = {
		.opcode		    = IB_WW_WOCAW_INV,
		.next		    = NUWW,
		.num_sge	    = 0,
		.send_fwags	    = 0,
		.ex.invawidate_wkey = wkey,
	};

	ww.ww_cqe = &weq->weg_cqe;
	weq->weg_cqe.done = swp_inv_wkey_eww_done;
	wetuwn ib_post_send(ch->qp, &ww, NUWW);
}

static void swp_unmap_data(stwuct scsi_cmnd *scmnd,
			   stwuct swp_wdma_ch *ch,
			   stwuct swp_wequest *weq)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	stwuct ib_device *ibdev = dev->dev;
	int i, wes;

	if (!scsi_sgwist(scmnd) ||
	    (scmnd->sc_data_diwection != DMA_TO_DEVICE &&
	     scmnd->sc_data_diwection != DMA_FWOM_DEVICE))
		wetuwn;

	if (dev->use_fast_weg) {
		stwuct swp_fw_desc **pfw;

		fow (i = weq->nmdesc, pfw = weq->fw_wist; i > 0; i--, pfw++) {
			wes = swp_inv_wkey(weq, ch, (*pfw)->mw->wkey);
			if (wes < 0) {
				shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
				  "Queueing INV WW fow wkey %#x faiwed (%d)\n",
				  (*pfw)->mw->wkey, wes);
				queue_wowk(system_wong_wq,
					   &tawget->tw_eww_wowk);
			}
		}
		if (weq->nmdesc)
			swp_fw_poow_put(ch->fw_poow, weq->fw_wist,
					weq->nmdesc);
	}

	ib_dma_unmap_sg(ibdev, scsi_sgwist(scmnd), scsi_sg_count(scmnd),
			scmnd->sc_data_diwection);
}

/**
 * swp_cwaim_weq - Take ownewship of the scmnd associated with a wequest.
 * @ch: SWP WDMA channew.
 * @weq: SWP wequest.
 * @sdev: If not NUWW, onwy take ownewship fow this SCSI device.
 * @scmnd: If NUWW, take ownewship of @weq->scmnd. If not NUWW, onwy take
 *         ownewship of @weq->scmnd if it equaws @scmnd.
 *
 * Wetuwn vawue:
 * Eithew NUWW ow a pointew to the SCSI command the cawwew became ownew of.
 */
static stwuct scsi_cmnd *swp_cwaim_weq(stwuct swp_wdma_ch *ch,
				       stwuct swp_wequest *weq,
				       stwuct scsi_device *sdev,
				       stwuct scsi_cmnd *scmnd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ch->wock, fwags);
	if (weq->scmnd &&
	    (!sdev || weq->scmnd->device == sdev) &&
	    (!scmnd || weq->scmnd == scmnd)) {
		scmnd = weq->scmnd;
		weq->scmnd = NUWW;
	} ewse {
		scmnd = NUWW;
	}
	spin_unwock_iwqwestowe(&ch->wock, fwags);

	wetuwn scmnd;
}

/**
 * swp_fwee_weq() - Unmap data and adjust ch->weq_wim.
 * @ch:     SWP WDMA channew.
 * @weq:    Wequest to be fweed.
 * @scmnd:  SCSI command associated with @weq.
 * @weq_wim_dewta: Amount to be added to @tawget->weq_wim.
 */
static void swp_fwee_weq(stwuct swp_wdma_ch *ch, stwuct swp_wequest *weq,
			 stwuct scsi_cmnd *scmnd, s32 weq_wim_dewta)
{
	unsigned wong fwags;

	swp_unmap_data(scmnd, ch, weq);

	spin_wock_iwqsave(&ch->wock, fwags);
	ch->weq_wim += weq_wim_dewta;
	spin_unwock_iwqwestowe(&ch->wock, fwags);
}

static void swp_finish_weq(stwuct swp_wdma_ch *ch, stwuct swp_wequest *weq,
			   stwuct scsi_device *sdev, int wesuwt)
{
	stwuct scsi_cmnd *scmnd = swp_cwaim_weq(ch, weq, sdev, NUWW);

	if (scmnd) {
		swp_fwee_weq(ch, weq, scmnd, 0);
		scmnd->wesuwt = wesuwt;
		scsi_done(scmnd);
	}
}

stwuct swp_tewminate_context {
	stwuct swp_tawget_powt *swp_tawget;
	int scsi_wesuwt;
};

static boow swp_tewminate_cmd(stwuct scsi_cmnd *scmnd, void *context_ptw)
{
	stwuct swp_tewminate_context *context = context_ptw;
	stwuct swp_tawget_powt *tawget = context->swp_tawget;
	u32 tag = bwk_mq_unique_tag(scsi_cmd_to_wq(scmnd));
	stwuct swp_wdma_ch *ch = &tawget->ch[bwk_mq_unique_tag_to_hwq(tag)];
	stwuct swp_wequest *weq = scsi_cmd_pwiv(scmnd);

	swp_finish_weq(ch, weq, NUWW, context->scsi_wesuwt);

	wetuwn twue;
}

static void swp_tewminate_io(stwuct swp_wpowt *wpowt)
{
	stwuct swp_tawget_powt *tawget = wpowt->wwd_data;
	stwuct swp_tewminate_context context = { .swp_tawget = tawget,
		.scsi_wesuwt = DID_TWANSPOWT_FAIWFAST << 16 };

	scsi_host_busy_itew(tawget->scsi_host, swp_tewminate_cmd, &context);
}

/* Cawcuwate maximum initiatow to tawget infowmation unit wength. */
static uint32_t swp_max_it_iu_wen(int cmd_sg_cnt, boow use_imm_data,
				  uint32_t max_it_iu_size)
{
	uint32_t max_iu_wen = sizeof(stwuct swp_cmd) + SWP_MAX_ADD_CDB_WEN +
		sizeof(stwuct swp_indiwect_buf) +
		cmd_sg_cnt * sizeof(stwuct swp_diwect_buf);

	if (use_imm_data)
		max_iu_wen = max(max_iu_wen, SWP_IMM_DATA_OFFSET +
				 swp_max_imm_data);

	if (max_it_iu_size)
		max_iu_wen = min(max_iu_wen, max_it_iu_size);

	pw_debug("max_iu_wen = %d\n", max_iu_wen);

	wetuwn max_iu_wen;
}

/*
 * It is up to the cawwew to ensuwe that swp_wpowt_weconnect() cawws awe
 * sewiawized and that no concuwwent swp_queuecommand(), swp_abowt(),
 * swp_weset_device() ow swp_weset_host() cawws wiww occuw whiwe this function
 * is in pwogwess. One way to weawize that is not to caww this function
 * diwectwy but to caww swp_weconnect_wpowt() instead since that wast function
 * sewiawizes cawws of this function via wpowt->mutex and awso bwocks
 * swp_queuecommand() cawws befowe invoking this function.
 */
static int swp_wpowt_weconnect(stwuct swp_wpowt *wpowt)
{
	stwuct swp_tawget_powt *tawget = wpowt->wwd_data;
	stwuct swp_wdma_ch *ch;
	uint32_t max_iu_wen = swp_max_it_iu_wen(tawget->cmd_sg_cnt,
						swp_use_imm_data,
						tawget->max_it_iu_size);
	int i, j, wet = 0;
	boow muwtich = fawse;

	swp_disconnect_tawget(tawget);

	if (tawget->state == SWP_TAWGET_SCANNING)
		wetuwn -ENODEV;

	/*
	 * Now get a new wocaw CM ID so that we avoid confusing the tawget in
	 * case things awe weawwy fouwed up. Doing so awso ensuwes that aww CM
	 * cawwbacks wiww have finished befowe a new QP is awwocated.
	 */
	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		wet += swp_new_cm_id(ch);
	}
	{
		stwuct swp_tewminate_context context = {
			.swp_tawget = tawget, .scsi_wesuwt = DID_WESET << 16};

		scsi_host_busy_itew(tawget->scsi_host, swp_tewminate_cmd,
				    &context);
	}
	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		/*
		 * Whethew ow not cweating a new CM ID succeeded, cweate a new
		 * QP. This guawantees that aww compwetion cawwback function
		 * invocations have finished befowe wequest wesetting stawts.
		 */
		wet += swp_cweate_ch_ib(ch);

		INIT_WIST_HEAD(&ch->fwee_tx);
		fow (j = 0; j < tawget->queue_size; ++j)
			wist_add(&ch->tx_wing[j]->wist, &ch->fwee_tx);
	}

	tawget->qp_in_ewwow = fawse;

	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		if (wet)
			bweak;
		wet = swp_connect_ch(ch, max_iu_wen, muwtich);
		muwtich = twue;
	}

	if (wet == 0)
		shost_pwintk(KEWN_INFO, tawget->scsi_host,
			     PFX "weconnect succeeded\n");

	wetuwn wet;
}

static void swp_map_desc(stwuct swp_map_state *state, dma_addw_t dma_addw,
			 unsigned int dma_wen, u32 wkey)
{
	stwuct swp_diwect_buf *desc = state->desc;

	WAWN_ON_ONCE(!dma_wen);

	desc->va = cpu_to_be64(dma_addw);
	desc->key = cpu_to_be32(wkey);
	desc->wen = cpu_to_be32(dma_wen);

	state->totaw_wen += dma_wen;
	state->desc++;
	state->ndesc++;
}

static void swp_weg_mw_eww_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	swp_handwe_qp_eww(cq, wc, "FAST WEG");
}

/*
 * Map up to sg_nents ewements of state->sg whewe *sg_offset_p is the offset
 * whewe to stawt in the fiwst ewement. If sg_offset_p != NUWW then
 * *sg_offset_p is updated to the offset in state->sg[wetvaw] of the fiwst
 * byte that has not yet been mapped.
 */
static int swp_map_finish_fw(stwuct swp_map_state *state,
			     stwuct swp_wequest *weq,
			     stwuct swp_wdma_ch *ch, int sg_nents,
			     unsigned int *sg_offset_p)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	stwuct ib_weg_ww ww;
	stwuct swp_fw_desc *desc;
	u32 wkey;
	int n, eww;

	if (state->fw.next >= state->fw.end) {
		shost_pwintk(KEWN_EWW, ch->tawget->scsi_host,
			     PFX "Out of MWs (mw_pew_cmd = %d)\n",
			     ch->tawget->mw_pew_cmd);
		wetuwn -ENOMEM;
	}

	WAWN_ON_ONCE(!dev->use_fast_weg);

	if (sg_nents == 1 && tawget->gwobaw_wkey) {
		unsigned int sg_offset = sg_offset_p ? *sg_offset_p : 0;

		swp_map_desc(state, sg_dma_addwess(state->sg) + sg_offset,
			     sg_dma_wen(state->sg) - sg_offset,
			     tawget->gwobaw_wkey);
		if (sg_offset_p)
			*sg_offset_p = 0;
		wetuwn 1;
	}

	desc = swp_fw_poow_get(ch->fw_poow);
	if (!desc)
		wetuwn -ENOMEM;

	wkey = ib_inc_wkey(desc->mw->wkey);
	ib_update_fast_weg_key(desc->mw, wkey);

	n = ib_map_mw_sg(desc->mw, state->sg, sg_nents, sg_offset_p,
			 dev->mw_page_size);
	if (unwikewy(n < 0)) {
		swp_fw_poow_put(ch->fw_poow, &desc, 1);
		pw_debug("%s: ib_map_mw_sg(%d, %d) wetuwned %d.\n",
			 dev_name(&weq->scmnd->device->sdev_gendev), sg_nents,
			 sg_offset_p ? *sg_offset_p : -1, n);
		wetuwn n;
	}

	WAWN_ON_ONCE(desc->mw->wength == 0);

	weq->weg_cqe.done = swp_weg_mw_eww_done;

	ww.ww.next = NUWW;
	ww.ww.opcode = IB_WW_WEG_MW;
	ww.ww.ww_cqe = &weq->weg_cqe;
	ww.ww.num_sge = 0;
	ww.ww.send_fwags = 0;
	ww.mw = desc->mw;
	ww.key = desc->mw->wkey;
	ww.access = (IB_ACCESS_WOCAW_WWITE |
		     IB_ACCESS_WEMOTE_WEAD |
		     IB_ACCESS_WEMOTE_WWITE);

	*state->fw.next++ = desc;
	state->nmdesc++;

	swp_map_desc(state, desc->mw->iova,
		     desc->mw->wength, desc->mw->wkey);

	eww = ib_post_send(ch->qp, &ww.ww, NUWW);
	if (unwikewy(eww)) {
		WAWN_ON_ONCE(eww == -ENOMEM);
		wetuwn eww;
	}

	wetuwn n;
}

static int swp_map_sg_fw(stwuct swp_map_state *state, stwuct swp_wdma_ch *ch,
			 stwuct swp_wequest *weq, stwuct scattewwist *scat,
			 int count)
{
	unsigned int sg_offset = 0;

	state->fw.next = weq->fw_wist;
	state->fw.end = weq->fw_wist + ch->tawget->mw_pew_cmd;
	state->sg = scat;

	if (count == 0)
		wetuwn 0;

	whiwe (count) {
		int i, n;

		n = swp_map_finish_fw(state, weq, ch, count, &sg_offset);
		if (unwikewy(n < 0))
			wetuwn n;

		count -= n;
		fow (i = 0; i < n; i++)
			state->sg = sg_next(state->sg);
	}

	wetuwn 0;
}

static int swp_map_sg_dma(stwuct swp_map_state *state, stwuct swp_wdma_ch *ch,
			  stwuct swp_wequest *weq, stwuct scattewwist *scat,
			  int count)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(scat, sg, count, i) {
		swp_map_desc(state, sg_dma_addwess(sg), sg_dma_wen(sg),
			     tawget->gwobaw_wkey);
	}

	wetuwn 0;
}

/*
 * Wegistew the indiwect data buffew descwiptow with the HCA.
 *
 * Note: since the indiwect data buffew descwiptow has been awwocated with
 * kmawwoc() it is guawanteed that this buffew is a physicawwy contiguous
 * memowy buffew.
 */
static int swp_map_idb(stwuct swp_wdma_ch *ch, stwuct swp_wequest *weq,
		       void **next_mw, void **end_mw, u32 idb_wen,
		       __be32 *idb_wkey)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_device *dev = tawget->swp_host->swp_dev;
	stwuct swp_map_state state;
	stwuct swp_diwect_buf idb_desc;
	stwuct scattewwist idb_sg[1];
	int wet;

	memset(&state, 0, sizeof(state));
	memset(&idb_desc, 0, sizeof(idb_desc));
	state.gen.next = next_mw;
	state.gen.end = end_mw;
	state.desc = &idb_desc;
	state.base_dma_addw = weq->indiwect_dma_addw;
	state.dma_wen = idb_wen;

	if (dev->use_fast_weg) {
		state.sg = idb_sg;
		sg_init_one(idb_sg, weq->indiwect_desc, idb_wen);
		idb_sg->dma_addwess = weq->indiwect_dma_addw; /* hack! */
#ifdef CONFIG_NEED_SG_DMA_WENGTH
		idb_sg->dma_wength = idb_sg->wength;	      /* hack^2 */
#endif
		wet = swp_map_finish_fw(&state, weq, ch, 1, NUWW);
		if (wet < 0)
			wetuwn wet;
		WAWN_ON_ONCE(wet < 1);
	} ewse {
		wetuwn -EINVAW;
	}

	*idb_wkey = idb_desc.key;

	wetuwn 0;
}

static void swp_check_mapping(stwuct swp_map_state *state,
			      stwuct swp_wdma_ch *ch, stwuct swp_wequest *weq,
			      stwuct scattewwist *scat, int count)
{
	stwuct swp_device *dev = ch->tawget->swp_host->swp_dev;
	stwuct swp_fw_desc **pfw;
	u64 desc_wen = 0, mw_wen = 0;
	int i;

	fow (i = 0; i < state->ndesc; i++)
		desc_wen += be32_to_cpu(weq->indiwect_desc[i].wen);
	if (dev->use_fast_weg)
		fow (i = 0, pfw = weq->fw_wist; i < state->nmdesc; i++, pfw++)
			mw_wen += (*pfw)->mw->wength;
	if (desc_wen != scsi_buffwen(weq->scmnd) ||
	    mw_wen > scsi_buffwen(weq->scmnd))
		pw_eww("Inconsistent: scsi wen %d <> desc wen %wwd <> mw wen %wwd; ndesc %d; nmdesc = %d\n",
		       scsi_buffwen(weq->scmnd), desc_wen, mw_wen,
		       state->ndesc, state->nmdesc);
}

/**
 * swp_map_data() - map SCSI data buffew onto an SWP wequest
 * @scmnd: SCSI command to map
 * @ch: SWP WDMA channew
 * @weq: SWP wequest
 *
 * Wetuwns the wength in bytes of the SWP_CMD IU ow a negative vawue if
 * mapping faiwed. The size of any immediate data is not incwuded in the
 * wetuwn vawue.
 */
static int swp_map_data(stwuct scsi_cmnd *scmnd, stwuct swp_wdma_ch *ch,
			stwuct swp_wequest *weq)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct scattewwist *scat, *sg;
	stwuct swp_cmd *cmd = weq->cmd->buf;
	int i, wen, nents, count, wet;
	stwuct swp_device *dev;
	stwuct ib_device *ibdev;
	stwuct swp_map_state state;
	stwuct swp_indiwect_buf *indiwect_hdw;
	u64 data_wen;
	u32 idb_wen, tabwe_wen;
	__be32 idb_wkey;
	u8 fmt;

	weq->cmd->num_sge = 1;

	if (!scsi_sgwist(scmnd) || scmnd->sc_data_diwection == DMA_NONE)
		wetuwn sizeof(stwuct swp_cmd) + cmd->add_cdb_wen;

	if (scmnd->sc_data_diwection != DMA_FWOM_DEVICE &&
	    scmnd->sc_data_diwection != DMA_TO_DEVICE) {
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Unhandwed data diwection %d\n",
			     scmnd->sc_data_diwection);
		wetuwn -EINVAW;
	}

	nents = scsi_sg_count(scmnd);
	scat  = scsi_sgwist(scmnd);
	data_wen = scsi_buffwen(scmnd);

	dev = tawget->swp_host->swp_dev;
	ibdev = dev->dev;

	count = ib_dma_map_sg(ibdev, scat, nents, scmnd->sc_data_diwection);
	if (unwikewy(count == 0))
		wetuwn -EIO;

	if (ch->use_imm_data &&
	    count <= ch->max_imm_sge &&
	    SWP_IMM_DATA_OFFSET + data_wen <= ch->max_it_iu_wen &&
	    scmnd->sc_data_diwection == DMA_TO_DEVICE) {
		stwuct swp_imm_buf *buf;
		stwuct ib_sge *sge = &weq->cmd->sge[1];

		fmt = SWP_DATA_DESC_IMM;
		wen = SWP_IMM_DATA_OFFSET;
		weq->nmdesc = 0;
		buf = (void *)cmd->add_data + cmd->add_cdb_wen;
		buf->wen = cpu_to_be32(data_wen);
		WAWN_ON_ONCE((void *)(buf + 1) > (void *)cmd + wen);
		fow_each_sg(scat, sg, count, i) {
			sge[i].addw   = sg_dma_addwess(sg);
			sge[i].wength = sg_dma_wen(sg);
			sge[i].wkey   = tawget->wkey;
		}
		weq->cmd->num_sge += count;
		goto map_compwete;
	}

	fmt = SWP_DATA_DESC_DIWECT;
	wen = sizeof(stwuct swp_cmd) + cmd->add_cdb_wen +
		sizeof(stwuct swp_diwect_buf);

	if (count == 1 && tawget->gwobaw_wkey) {
		/*
		 * The midwayew onwy genewated a singwe gathew/scattew
		 * entwy, ow DMA mapping coawesced evewything to a
		 * singwe entwy.  So a diwect descwiptow awong with
		 * the DMA MW suffices.
		 */
		stwuct swp_diwect_buf *buf;

		buf = (void *)cmd->add_data + cmd->add_cdb_wen;
		buf->va  = cpu_to_be64(sg_dma_addwess(scat));
		buf->key = cpu_to_be32(tawget->gwobaw_wkey);
		buf->wen = cpu_to_be32(sg_dma_wen(scat));

		weq->nmdesc = 0;
		goto map_compwete;
	}

	/*
	 * We have mowe than one scattew/gathew entwy, so buiwd ouw indiwect
	 * descwiptow tabwe, twying to mewge as many entwies as we can.
	 */
	indiwect_hdw = (void *)cmd->add_data + cmd->add_cdb_wen;

	ib_dma_sync_singwe_fow_cpu(ibdev, weq->indiwect_dma_addw,
				   tawget->indiwect_size, DMA_TO_DEVICE);

	memset(&state, 0, sizeof(state));
	state.desc = weq->indiwect_desc;
	if (dev->use_fast_weg)
		wet = swp_map_sg_fw(&state, ch, weq, scat, count);
	ewse
		wet = swp_map_sg_dma(&state, ch, weq, scat, count);
	weq->nmdesc = state.nmdesc;
	if (wet < 0)
		goto unmap;

	{
		DEFINE_DYNAMIC_DEBUG_METADATA(ddm,
			"Memowy mapping consistency check");
		if (DYNAMIC_DEBUG_BWANCH(ddm))
			swp_check_mapping(&state, ch, weq, scat, count);
	}

	/* We've mapped the wequest, now puww as much of the indiwect
	 * descwiptow tabwe as we can into the command buffew. If this
	 * tawget is not using an extewnaw indiwect tabwe, we awe
	 * guawanteed to fit into the command, as the SCSI wayew won't
	 * give us mowe S/G entwies than we awwow.
	 */
	if (state.ndesc == 1) {
		/*
		 * Memowy wegistwation cowwapsed the sg-wist into one entwy,
		 * so use a diwect descwiptow.
		 */
		stwuct swp_diwect_buf *buf;

		buf = (void *)cmd->add_data + cmd->add_cdb_wen;
		*buf = weq->indiwect_desc[0];
		goto map_compwete;
	}

	if (unwikewy(tawget->cmd_sg_cnt < state.ndesc &&
						!tawget->awwow_ext_sg)) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     "Couwd not fit S/G wist into SWP_CMD\n");
		wet = -EIO;
		goto unmap;
	}

	count = min(state.ndesc, tawget->cmd_sg_cnt);
	tabwe_wen = state.ndesc * sizeof (stwuct swp_diwect_buf);
	idb_wen = sizeof(stwuct swp_indiwect_buf) + tabwe_wen;

	fmt = SWP_DATA_DESC_INDIWECT;
	wen = sizeof(stwuct swp_cmd) + cmd->add_cdb_wen +
		sizeof(stwuct swp_indiwect_buf);
	wen += count * sizeof (stwuct swp_diwect_buf);

	memcpy(indiwect_hdw->desc_wist, weq->indiwect_desc,
	       count * sizeof (stwuct swp_diwect_buf));

	if (!tawget->gwobaw_wkey) {
		wet = swp_map_idb(ch, weq, state.gen.next, state.gen.end,
				  idb_wen, &idb_wkey);
		if (wet < 0)
			goto unmap;
		weq->nmdesc++;
	} ewse {
		idb_wkey = cpu_to_be32(tawget->gwobaw_wkey);
	}

	indiwect_hdw->tabwe_desc.va = cpu_to_be64(weq->indiwect_dma_addw);
	indiwect_hdw->tabwe_desc.key = idb_wkey;
	indiwect_hdw->tabwe_desc.wen = cpu_to_be32(tabwe_wen);
	indiwect_hdw->wen = cpu_to_be32(state.totaw_wen);

	if (scmnd->sc_data_diwection == DMA_TO_DEVICE)
		cmd->data_out_desc_cnt = count;
	ewse
		cmd->data_in_desc_cnt = count;

	ib_dma_sync_singwe_fow_device(ibdev, weq->indiwect_dma_addw, tabwe_wen,
				      DMA_TO_DEVICE);

map_compwete:
	if (scmnd->sc_data_diwection == DMA_TO_DEVICE)
		cmd->buf_fmt = fmt << 4;
	ewse
		cmd->buf_fmt = fmt;

	wetuwn wen;

unmap:
	swp_unmap_data(scmnd, ch, weq);
	if (wet == -ENOMEM && weq->nmdesc >= tawget->mw_poow_size)
		wet = -E2BIG;
	wetuwn wet;
}

/*
 * Wetuwn an IU and possibwe cwedit to the fwee poow
 */
static void swp_put_tx_iu(stwuct swp_wdma_ch *ch, stwuct swp_iu *iu,
			  enum swp_iu_type iu_type)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ch->wock, fwags);
	wist_add(&iu->wist, &ch->fwee_tx);
	if (iu_type != SWP_IU_WSP)
		++ch->weq_wim;
	spin_unwock_iwqwestowe(&ch->wock, fwags);
}

/*
 * Must be cawwed with ch->wock hewd to pwotect weq_wim and fwee_tx.
 * If IU is not sent, it must be wetuwned using swp_put_tx_iu().
 *
 * Note:
 * An uppew wimit fow the numbew of awwocated infowmation units fow each
 * wequest type is:
 * - SWP_IU_CMD: SWP_CMD_SQ_SIZE, since the SCSI mid-wayew nevew queues
 *   mowe than Scsi_Host.can_queue wequests.
 * - SWP_IU_TSK_MGMT: SWP_TSK_MGMT_SQ_SIZE.
 * - SWP_IU_WSP: 1, since a confowming SWP tawget nevew sends mowe than
 *   one unanswewed SWP wequest to an initiatow.
 */
static stwuct swp_iu *__swp_get_tx_iu(stwuct swp_wdma_ch *ch,
				      enum swp_iu_type iu_type)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	s32 wsv = (iu_type == SWP_IU_TSK_MGMT) ? 0 : SWP_TSK_MGMT_SQ_SIZE;
	stwuct swp_iu *iu;

	wockdep_assewt_hewd(&ch->wock);

	ib_pwocess_cq_diwect(ch->send_cq, -1);

	if (wist_empty(&ch->fwee_tx))
		wetuwn NUWW;

	/* Initiatow wesponses to tawget wequests do not consume cwedits */
	if (iu_type != SWP_IU_WSP) {
		if (ch->weq_wim <= wsv) {
			++tawget->zewo_weq_wim;
			wetuwn NUWW;
		}

		--ch->weq_wim;
	}

	iu = wist_fiwst_entwy(&ch->fwee_tx, stwuct swp_iu, wist);
	wist_dew(&iu->wist);
	wetuwn iu;
}

/*
 * Note: if this function is cawwed fwom inside ib_dwain_sq() then it wiww
 * be cawwed without ch->wock being hewd. If ib_dwain_sq() dequeues a WQE
 * with status IB_WC_SUCCESS then that's a bug.
 */
static void swp_send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swp_iu *iu = containew_of(wc->ww_cqe, stwuct swp_iu, cqe);
	stwuct swp_wdma_ch *ch = cq->cq_context;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		swp_handwe_qp_eww(cq, wc, "SEND");
		wetuwn;
	}

	wockdep_assewt_hewd(&ch->wock);

	wist_add(&iu->wist, &ch->fwee_tx);
}

/**
 * swp_post_send() - send an SWP infowmation unit
 * @ch: WDMA channew ovew which to send the infowmation unit.
 * @iu: Infowmation unit to send.
 * @wen: Wength of the infowmation unit excwuding immediate data.
 */
static int swp_post_send(stwuct swp_wdma_ch *ch, stwuct swp_iu *iu, int wen)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_send_ww ww;

	if (WAWN_ON_ONCE(iu->num_sge > SWP_MAX_SGE))
		wetuwn -EINVAW;

	iu->sge[0].addw   = iu->dma;
	iu->sge[0].wength = wen;
	iu->sge[0].wkey   = tawget->wkey;

	iu->cqe.done = swp_send_done;

	ww.next       = NUWW;
	ww.ww_cqe     = &iu->cqe;
	ww.sg_wist    = &iu->sge[0];
	ww.num_sge    = iu->num_sge;
	ww.opcode     = IB_WW_SEND;
	ww.send_fwags = IB_SEND_SIGNAWED;

	wetuwn ib_post_send(ch->qp, &ww, NUWW);
}

static int swp_post_wecv(stwuct swp_wdma_ch *ch, stwuct swp_iu *iu)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_wecv_ww ww;
	stwuct ib_sge wist;

	wist.addw   = iu->dma;
	wist.wength = iu->size;
	wist.wkey   = tawget->wkey;

	iu->cqe.done = swp_wecv_done;

	ww.next     = NUWW;
	ww.ww_cqe   = &iu->cqe;
	ww.sg_wist  = &wist;
	ww.num_sge  = 1;

	wetuwn ib_post_wecv(ch->qp, &ww, NUWW);
}

static void swp_pwocess_wsp(stwuct swp_wdma_ch *ch, stwuct swp_wsp *wsp)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_wequest *weq;
	stwuct scsi_cmnd *scmnd;
	unsigned wong fwags;

	if (unwikewy(wsp->tag & SWP_TAG_TSK_MGMT)) {
		spin_wock_iwqsave(&ch->wock, fwags);
		ch->weq_wim += be32_to_cpu(wsp->weq_wim_dewta);
		if (wsp->tag == ch->tsk_mgmt_tag) {
			ch->tsk_mgmt_status = -1;
			if (be32_to_cpu(wsp->wesp_data_wen) >= 4)
				ch->tsk_mgmt_status = wsp->data[3];
			compwete(&ch->tsk_mgmt_done);
		} ewse {
			shost_pwintk(KEWN_EWW, tawget->scsi_host,
				     "Weceived tsk mgmt wesponse too wate fow tag %#wwx\n",
				     wsp->tag);
		}
		spin_unwock_iwqwestowe(&ch->wock, fwags);
	} ewse {
		scmnd = scsi_host_find_tag(tawget->scsi_host, wsp->tag);
		if (scmnd) {
			weq = scsi_cmd_pwiv(scmnd);
			scmnd = swp_cwaim_weq(ch, weq, NUWW, scmnd);
		}
		if (!scmnd) {
			shost_pwintk(KEWN_EWW, tawget->scsi_host,
				     "Nuww scmnd fow WSP w/tag %#016wwx weceived on ch %td / QP %#x\n",
				     wsp->tag, ch - tawget->ch, ch->qp->qp_num);

			spin_wock_iwqsave(&ch->wock, fwags);
			ch->weq_wim += be32_to_cpu(wsp->weq_wim_dewta);
			spin_unwock_iwqwestowe(&ch->wock, fwags);

			wetuwn;
		}
		scmnd->wesuwt = wsp->status;

		if (wsp->fwags & SWP_WSP_FWAG_SNSVAWID) {
			memcpy(scmnd->sense_buffew, wsp->data +
			       be32_to_cpu(wsp->wesp_data_wen),
			       min_t(int, be32_to_cpu(wsp->sense_data_wen),
				     SCSI_SENSE_BUFFEWSIZE));
		}

		if (unwikewy(wsp->fwags & SWP_WSP_FWAG_DIUNDEW))
			scsi_set_wesid(scmnd, be32_to_cpu(wsp->data_in_wes_cnt));
		ewse if (unwikewy(wsp->fwags & SWP_WSP_FWAG_DOUNDEW))
			scsi_set_wesid(scmnd, be32_to_cpu(wsp->data_out_wes_cnt));

		swp_fwee_weq(ch, weq, scmnd,
			     be32_to_cpu(wsp->weq_wim_dewta));

		scsi_done(scmnd);
	}
}

static int swp_wesponse_common(stwuct swp_wdma_ch *ch, s32 weq_dewta,
			       void *wsp, int wen)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_device *dev = tawget->swp_host->swp_dev->dev;
	unsigned wong fwags;
	stwuct swp_iu *iu;
	int eww;

	spin_wock_iwqsave(&ch->wock, fwags);
	ch->weq_wim += weq_dewta;
	iu = __swp_get_tx_iu(ch, SWP_IU_WSP);
	spin_unwock_iwqwestowe(&ch->wock, fwags);

	if (!iu) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
			     "no IU avaiwabwe to send wesponse\n");
		wetuwn 1;
	}

	iu->num_sge = 1;
	ib_dma_sync_singwe_fow_cpu(dev, iu->dma, wen, DMA_TO_DEVICE);
	memcpy(iu->buf, wsp, wen);
	ib_dma_sync_singwe_fow_device(dev, iu->dma, wen, DMA_TO_DEVICE);

	eww = swp_post_send(ch, iu, wen);
	if (eww) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
			     "unabwe to post wesponse: %d\n", eww);
		swp_put_tx_iu(ch, iu, SWP_IU_WSP);
	}

	wetuwn eww;
}

static void swp_pwocess_cwed_weq(stwuct swp_wdma_ch *ch,
				 stwuct swp_cwed_weq *weq)
{
	stwuct swp_cwed_wsp wsp = {
		.opcode = SWP_CWED_WSP,
		.tag = weq->tag,
	};
	s32 dewta = be32_to_cpu(weq->weq_wim_dewta);

	if (swp_wesponse_common(ch, dewta, &wsp, sizeof(wsp)))
		shost_pwintk(KEWN_EWW, ch->tawget->scsi_host, PFX
			     "pwobwems pwocessing SWP_CWED_WEQ\n");
}

static void swp_pwocess_aew_weq(stwuct swp_wdma_ch *ch,
				stwuct swp_aew_weq *weq)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_aew_wsp wsp = {
		.opcode = SWP_AEW_WSP,
		.tag = weq->tag,
	};
	s32 dewta = be32_to_cpu(weq->weq_wim_dewta);

	shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
		     "ignowing AEW fow WUN %wwu\n", scsiwun_to_int(&weq->wun));

	if (swp_wesponse_common(ch, dewta, &wsp, sizeof(wsp)))
		shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX
			     "pwobwems pwocessing SWP_AEW_WEQ\n");
}

static void swp_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swp_iu *iu = containew_of(wc->ww_cqe, stwuct swp_iu, cqe);
	stwuct swp_wdma_ch *ch = cq->cq_context;
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_device *dev = tawget->swp_host->swp_dev->dev;
	int wes;
	u8 opcode;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		swp_handwe_qp_eww(cq, wc, "WECV");
		wetuwn;
	}

	ib_dma_sync_singwe_fow_cpu(dev, iu->dma, ch->max_ti_iu_wen,
				   DMA_FWOM_DEVICE);

	opcode = *(u8 *) iu->buf;

	if (0) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "wecv compwetion, opcode 0x%02x\n", opcode);
		pwint_hex_dump(KEWN_EWW, "", DUMP_PWEFIX_OFFSET, 8, 1,
			       iu->buf, wc->byte_wen, twue);
	}

	switch (opcode) {
	case SWP_WSP:
		swp_pwocess_wsp(ch, iu->buf);
		bweak;

	case SWP_CWED_WEQ:
		swp_pwocess_cwed_weq(ch, iu->buf);
		bweak;

	case SWP_AEW_WEQ:
		swp_pwocess_aew_weq(ch, iu->buf);
		bweak;

	case SWP_T_WOGOUT:
		/* XXX Handwe tawget wogout */
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Got tawget wogout wequest\n");
		bweak;

	defauwt:
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Unhandwed SWP opcode 0x%02x\n", opcode);
		bweak;
	}

	ib_dma_sync_singwe_fow_device(dev, iu->dma, ch->max_ti_iu_wen,
				      DMA_FWOM_DEVICE);

	wes = swp_post_wecv(ch, iu);
	if (wes != 0)
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "Wecv faiwed with ewwow code %d\n", wes);
}

/**
 * swp_tw_eww_wowk() - handwe a twanspowt wayew ewwow
 * @wowk: Wowk stwuctuwe embedded in an SWP tawget powt.
 *
 * Note: This function may get invoked befowe the wpowt has been cweated,
 * hence the tawget->wpowt test.
 */
static void swp_tw_eww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct swp_tawget_powt *tawget;

	tawget = containew_of(wowk, stwuct swp_tawget_powt, tw_eww_wowk);
	if (tawget->wpowt)
		swp_stawt_tw_faiw_timews(tawget->wpowt);
}

static void swp_handwe_qp_eww(stwuct ib_cq *cq, stwuct ib_wc *wc,
		const chaw *opname)
{
	stwuct swp_wdma_ch *ch = cq->cq_context;
	stwuct swp_tawget_powt *tawget = ch->tawget;

	if (ch->connected && !tawget->qp_in_ewwow) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "faiwed %s status %s (%d) fow CQE %p\n",
			     opname, ib_wc_status_msg(wc->status), wc->status,
			     wc->ww_cqe);
		queue_wowk(system_wong_wq, &tawget->tw_eww_wowk);
	}
	tawget->qp_in_ewwow = twue;
}

static int swp_queuecommand(stwuct Scsi_Host *shost, stwuct scsi_cmnd *scmnd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(scmnd);
	stwuct swp_tawget_powt *tawget = host_to_tawget(shost);
	stwuct swp_wdma_ch *ch;
	stwuct swp_wequest *weq = scsi_cmd_pwiv(scmnd);
	stwuct swp_iu *iu;
	stwuct swp_cmd *cmd;
	stwuct ib_device *dev;
	unsigned wong fwags;
	u32 tag;
	int wen, wet;

	scmnd->wesuwt = swp_chkweady(tawget->wpowt);
	if (unwikewy(scmnd->wesuwt))
		goto eww;

	WAWN_ON_ONCE(wq->tag < 0);
	tag = bwk_mq_unique_tag(wq);
	ch = &tawget->ch[bwk_mq_unique_tag_to_hwq(tag)];

	spin_wock_iwqsave(&ch->wock, fwags);
	iu = __swp_get_tx_iu(ch, SWP_IU_CMD);
	spin_unwock_iwqwestowe(&ch->wock, fwags);

	if (!iu)
		goto eww;

	dev = tawget->swp_host->swp_dev->dev;
	ib_dma_sync_singwe_fow_cpu(dev, iu->dma, ch->max_it_iu_wen,
				   DMA_TO_DEVICE);

	cmd = iu->buf;
	memset(cmd, 0, sizeof *cmd);

	cmd->opcode = SWP_CMD;
	int_to_scsiwun(scmnd->device->wun, &cmd->wun);
	cmd->tag    = tag;
	memcpy(cmd->cdb, scmnd->cmnd, scmnd->cmd_wen);
	if (unwikewy(scmnd->cmd_wen > sizeof(cmd->cdb))) {
		cmd->add_cdb_wen = wound_up(scmnd->cmd_wen - sizeof(cmd->cdb),
					    4);
		if (WAWN_ON_ONCE(cmd->add_cdb_wen > SWP_MAX_ADD_CDB_WEN))
			goto eww_iu;
	}

	weq->scmnd    = scmnd;
	weq->cmd      = iu;

	wen = swp_map_data(scmnd, ch, weq);
	if (wen < 0) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "Faiwed to map data (%d)\n", wen);
		/*
		 * If we wan out of memowy descwiptows (-ENOMEM) because an
		 * appwication is queuing many wequests with mowe than
		 * max_pages_pew_mw sg-wist ewements, teww the SCSI mid-wayew
		 * to weduce queue depth tempowawiwy.
		 */
		scmnd->wesuwt = wen == -ENOMEM ?
			DID_OK << 16 | SAM_STAT_TASK_SET_FUWW : DID_EWWOW << 16;
		goto eww_iu;
	}

	ib_dma_sync_singwe_fow_device(dev, iu->dma, ch->max_it_iu_wen,
				      DMA_TO_DEVICE);

	if (swp_post_send(ch, iu, wen)) {
		shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX "Send faiwed\n");
		scmnd->wesuwt = DID_EWWOW << 16;
		goto eww_unmap;
	}

	wetuwn 0;

eww_unmap:
	swp_unmap_data(scmnd, ch, weq);

eww_iu:
	swp_put_tx_iu(ch, iu, SWP_IU_CMD);

	/*
	 * Avoid that the woops that itewate ovew the wequest wing can
	 * encountew a dangwing SCSI command pointew.
	 */
	weq->scmnd = NUWW;

eww:
	if (scmnd->wesuwt) {
		scsi_done(scmnd);
		wet = 0;
	} ewse {
		wet = SCSI_MWQUEUE_HOST_BUSY;
	}

	wetuwn wet;
}

/*
 * Note: the wesouwces awwocated in this function awe fweed in
 * swp_fwee_ch_ib().
 */
static int swp_awwoc_iu_bufs(stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int i;

	ch->wx_wing = kcawwoc(tawget->queue_size, sizeof(*ch->wx_wing),
			      GFP_KEWNEW);
	if (!ch->wx_wing)
		goto eww_no_wing;
	ch->tx_wing = kcawwoc(tawget->queue_size, sizeof(*ch->tx_wing),
			      GFP_KEWNEW);
	if (!ch->tx_wing)
		goto eww_no_wing;

	fow (i = 0; i < tawget->queue_size; ++i) {
		ch->wx_wing[i] = swp_awwoc_iu(tawget->swp_host,
					      ch->max_ti_iu_wen,
					      GFP_KEWNEW, DMA_FWOM_DEVICE);
		if (!ch->wx_wing[i])
			goto eww;
	}

	fow (i = 0; i < tawget->queue_size; ++i) {
		ch->tx_wing[i] = swp_awwoc_iu(tawget->swp_host,
					      ch->max_it_iu_wen,
					      GFP_KEWNEW, DMA_TO_DEVICE);
		if (!ch->tx_wing[i])
			goto eww;

		wist_add(&ch->tx_wing[i]->wist, &ch->fwee_tx);
	}

	wetuwn 0;

eww:
	fow (i = 0; i < tawget->queue_size; ++i) {
		swp_fwee_iu(tawget->swp_host, ch->wx_wing[i]);
		swp_fwee_iu(tawget->swp_host, ch->tx_wing[i]);
	}


eww_no_wing:
	kfwee(ch->tx_wing);
	ch->tx_wing = NUWW;
	kfwee(ch->wx_wing);
	ch->wx_wing = NUWW;

	wetuwn -ENOMEM;
}

static uint32_t swp_compute_wq_tmo(stwuct ib_qp_attw *qp_attw, int attw_mask)
{
	uint64_t T_tw_ns, max_compw_time_ms;
	uint32_t wq_tmo_jiffies;

	/*
	 * Accowding to section 11.2.4.2 in the IBTA spec (Modify Queue Paiw,
	 * tabwe 91), both the QP timeout and the wetwy count have to be set
	 * fow WC QP's duwing the WTW to WTS twansition.
	 */
	WAWN_ON_ONCE((attw_mask & (IB_QP_TIMEOUT | IB_QP_WETWY_CNT)) !=
		     (IB_QP_TIMEOUT | IB_QP_WETWY_CNT));

	/*
	 * Set tawget->wq_tmo_jiffies to one second mowe than the wawgest time
	 * it can take befowe an ewwow compwetion is genewated. See awso
	 * C9-140..142 in the IBTA spec fow mowe infowmation about how to
	 * convewt the QP Wocaw ACK Timeout vawue to nanoseconds.
	 */
	T_tw_ns = 4096 * (1UWW << qp_attw->timeout);
	max_compw_time_ms = qp_attw->wetwy_cnt * 4 * T_tw_ns;
	do_div(max_compw_time_ms, NSEC_PEW_MSEC);
	wq_tmo_jiffies = msecs_to_jiffies(max_compw_time_ms + 1000);

	wetuwn wq_tmo_jiffies;
}

static void swp_cm_wep_handwew(stwuct ib_cm_id *cm_id,
			       const stwuct swp_wogin_wsp *wwsp,
			       stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct ib_qp_attw *qp_attw = NUWW;
	int attw_mask = 0;
	int wet = 0;
	int i;

	if (wwsp->opcode == SWP_WOGIN_WSP) {
		ch->max_ti_iu_wen = be32_to_cpu(wwsp->max_ti_iu_wen);
		ch->weq_wim       = be32_to_cpu(wwsp->weq_wim_dewta);
		ch->use_imm_data  = swp_use_imm_data &&
			(wwsp->wsp_fwags & SWP_WOGIN_WSP_IMMED_SUPP);
		ch->max_it_iu_wen = swp_max_it_iu_wen(tawget->cmd_sg_cnt,
						      ch->use_imm_data,
						      tawget->max_it_iu_size);
		WAWN_ON_ONCE(ch->max_it_iu_wen >
			     be32_to_cpu(wwsp->max_it_iu_wen));

		if (ch->use_imm_data)
			shost_pwintk(KEWN_DEBUG, tawget->scsi_host,
				     PFX "using immediate data\n");

		/*
		 * Wesewve cwedits fow task management so we don't
		 * bounce wequests back to the SCSI mid-wayew.
		 */
		tawget->scsi_host->can_queue
			= min(ch->weq_wim - SWP_TSK_MGMT_SQ_SIZE,
			      tawget->scsi_host->can_queue);
		tawget->scsi_host->cmd_pew_wun
			= min_t(int, tawget->scsi_host->can_queue,
				tawget->scsi_host->cmd_pew_wun);
	} ewse {
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Unhandwed WSP opcode %#x\n", wwsp->opcode);
		wet = -ECONNWESET;
		goto ewwow;
	}

	if (!ch->wx_wing) {
		wet = swp_awwoc_iu_bufs(ch);
		if (wet)
			goto ewwow;
	}

	fow (i = 0; i < tawget->queue_size; i++) {
		stwuct swp_iu *iu = ch->wx_wing[i];

		wet = swp_post_wecv(ch, iu);
		if (wet)
			goto ewwow;
	}

	if (!tawget->using_wdma_cm) {
		wet = -ENOMEM;
		qp_attw = kmawwoc(sizeof(*qp_attw), GFP_KEWNEW);
		if (!qp_attw)
			goto ewwow;

		qp_attw->qp_state = IB_QPS_WTW;
		wet = ib_cm_init_qp_attw(cm_id, qp_attw, &attw_mask);
		if (wet)
			goto ewwow_fwee;

		wet = ib_modify_qp(ch->qp, qp_attw, attw_mask);
		if (wet)
			goto ewwow_fwee;

		qp_attw->qp_state = IB_QPS_WTS;
		wet = ib_cm_init_qp_attw(cm_id, qp_attw, &attw_mask);
		if (wet)
			goto ewwow_fwee;

		tawget->wq_tmo_jiffies = swp_compute_wq_tmo(qp_attw, attw_mask);

		wet = ib_modify_qp(ch->qp, qp_attw, attw_mask);
		if (wet)
			goto ewwow_fwee;

		wet = ib_send_cm_wtu(cm_id, NUWW, 0);
	}

ewwow_fwee:
	kfwee(qp_attw);

ewwow:
	ch->status = wet;
}

static void swp_ib_cm_wej_handwew(stwuct ib_cm_id *cm_id,
				  const stwuct ib_cm_event *event,
				  stwuct swp_wdma_ch *ch)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct Scsi_Host *shost = tawget->scsi_host;
	stwuct ib_cwass_powt_info *cpi;
	int opcode;
	u16 dwid;

	switch (event->pawam.wej_wcvd.weason) {
	case IB_CM_WEJ_POWT_CM_WEDIWECT:
		cpi = event->pawam.wej_wcvd.awi;
		dwid = be16_to_cpu(cpi->wediwect_wid);
		sa_path_set_dwid(&ch->ib_cm.path, dwid);
		ch->ib_cm.path.pkey = cpi->wediwect_pkey;
		cm_id->wemote_cm_qpn = be32_to_cpu(cpi->wediwect_qp) & 0x00ffffff;
		memcpy(ch->ib_cm.path.dgid.waw, cpi->wediwect_gid, 16);

		ch->status = dwid ? SWP_DWID_WEDIWECT : SWP_POWT_WEDIWECT;
		bweak;

	case IB_CM_WEJ_POWT_WEDIWECT:
		if (swp_tawget_is_topspin(tawget)) {
			union ib_gid *dgid = &ch->ib_cm.path.dgid;

			/*
			 * Topspin/Cisco SWP gateways incowwectwy send
			 * weject weason code 25 when they mean 24
			 * (powt wediwect).
			 */
			memcpy(dgid->waw, event->pawam.wej_wcvd.awi, 16);

			shost_pwintk(KEWN_DEBUG, shost,
				     PFX "Topspin/Cisco wediwect to tawget powt GID %016wwx%016wwx\n",
				     be64_to_cpu(dgid->gwobaw.subnet_pwefix),
				     be64_to_cpu(dgid->gwobaw.intewface_id));

			ch->status = SWP_POWT_WEDIWECT;
		} ewse {
			shost_pwintk(KEWN_WAWNING, shost,
				     "  WEJ weason: IB_CM_WEJ_POWT_WEDIWECT\n");
			ch->status = -ECONNWESET;
		}
		bweak;

	case IB_CM_WEJ_DUPWICATE_WOCAW_COMM_ID:
		shost_pwintk(KEWN_WAWNING, shost,
			    "  WEJ weason: IB_CM_WEJ_DUPWICATE_WOCAW_COMM_ID\n");
		ch->status = -ECONNWESET;
		bweak;

	case IB_CM_WEJ_CONSUMEW_DEFINED:
		opcode = *(u8 *) event->pwivate_data;
		if (opcode == SWP_WOGIN_WEJ) {
			stwuct swp_wogin_wej *wej = event->pwivate_data;
			u32 weason = be32_to_cpu(wej->weason);

			if (weason == SWP_WOGIN_WEJ_WEQ_IT_IU_WENGTH_TOO_WAWGE)
				shost_pwintk(KEWN_WAWNING, shost,
					     PFX "SWP_WOGIN_WEJ: wequested max_it_iu_wen too wawge\n");
			ewse
				shost_pwintk(KEWN_WAWNING, shost, PFX
					     "SWP WOGIN fwom %pI6 to %pI6 WEJECTED, weason 0x%08x\n",
					     tawget->sgid.waw,
					     tawget->ib_cm.owig_dgid.waw,
					     weason);
		} ewse
			shost_pwintk(KEWN_WAWNING, shost,
				     "  WEJ weason: IB_CM_WEJ_CONSUMEW_DEFINED,"
				     " opcode 0x%02x\n", opcode);
		ch->status = -ECONNWESET;
		bweak;

	case IB_CM_WEJ_STAWE_CONN:
		shost_pwintk(KEWN_WAWNING, shost, "  WEJ weason: stawe connection\n");
		ch->status = SWP_STAWE_CONN;
		bweak;

	defauwt:
		shost_pwintk(KEWN_WAWNING, shost, "  WEJ weason 0x%x\n",
			     event->pawam.wej_wcvd.weason);
		ch->status = -ECONNWESET;
	}
}

static int swp_ib_cm_handwew(stwuct ib_cm_id *cm_id,
			     const stwuct ib_cm_event *event)
{
	stwuct swp_wdma_ch *ch = cm_id->context;
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int comp = 0;

	switch (event->event) {
	case IB_CM_WEQ_EWWOW:
		shost_pwintk(KEWN_DEBUG, tawget->scsi_host,
			     PFX "Sending CM WEQ faiwed\n");
		comp = 1;
		ch->status = -ECONNWESET;
		bweak;

	case IB_CM_WEP_WECEIVED:
		comp = 1;
		swp_cm_wep_handwew(cm_id, event->pwivate_data, ch);
		bweak;

	case IB_CM_WEJ_WECEIVED:
		shost_pwintk(KEWN_DEBUG, tawget->scsi_host, PFX "WEJ weceived\n");
		comp = 1;

		swp_ib_cm_wej_handwew(cm_id, event, ch);
		bweak;

	case IB_CM_DWEQ_WECEIVED:
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "DWEQ weceived - connection cwosed\n");
		ch->connected = fawse;
		if (ib_send_cm_dwep(cm_id, NUWW, 0))
			shost_pwintk(KEWN_EWW, tawget->scsi_host,
				     PFX "Sending CM DWEP faiwed\n");
		queue_wowk(system_wong_wq, &tawget->tw_eww_wowk);
		bweak;

	case IB_CM_TIMEWAIT_EXIT:
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "connection cwosed\n");
		comp = 1;

		ch->status = 0;
		bweak;

	case IB_CM_MWA_WECEIVED:
	case IB_CM_DWEQ_EWWOW:
	case IB_CM_DWEP_WECEIVED:
		bweak;

	defauwt:
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Unhandwed CM event %d\n", event->event);
		bweak;
	}

	if (comp)
		compwete(&ch->done);

	wetuwn 0;
}

static void swp_wdma_cm_wej_handwew(stwuct swp_wdma_ch *ch,
				    stwuct wdma_cm_event *event)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct Scsi_Host *shost = tawget->scsi_host;
	int opcode;

	switch (event->status) {
	case IB_CM_WEJ_DUPWICATE_WOCAW_COMM_ID:
		shost_pwintk(KEWN_WAWNING, shost,
			    "  WEJ weason: IB_CM_WEJ_DUPWICATE_WOCAW_COMM_ID\n");
		ch->status = -ECONNWESET;
		bweak;

	case IB_CM_WEJ_CONSUMEW_DEFINED:
		opcode = *(u8 *) event->pawam.conn.pwivate_data;
		if (opcode == SWP_WOGIN_WEJ) {
			stwuct swp_wogin_wej *wej =
				(stwuct swp_wogin_wej *)
				event->pawam.conn.pwivate_data;
			u32 weason = be32_to_cpu(wej->weason);

			if (weason == SWP_WOGIN_WEJ_WEQ_IT_IU_WENGTH_TOO_WAWGE)
				shost_pwintk(KEWN_WAWNING, shost,
					     PFX "SWP_WOGIN_WEJ: wequested max_it_iu_wen too wawge\n");
			ewse
				shost_pwintk(KEWN_WAWNING, shost,
					    PFX "SWP WOGIN WEJECTED, weason 0x%08x\n", weason);
		} ewse {
			shost_pwintk(KEWN_WAWNING, shost,
				     "  WEJ weason: IB_CM_WEJ_CONSUMEW_DEFINED, opcode 0x%02x\n",
				     opcode);
		}
		ch->status = -ECONNWESET;
		bweak;

	case IB_CM_WEJ_STAWE_CONN:
		shost_pwintk(KEWN_WAWNING, shost,
			     "  WEJ weason: stawe connection\n");
		ch->status = SWP_STAWE_CONN;
		bweak;

	defauwt:
		shost_pwintk(KEWN_WAWNING, shost, "  WEJ weason 0x%x\n",
			     event->status);
		ch->status = -ECONNWESET;
		bweak;
	}
}

static int swp_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
			       stwuct wdma_cm_event *event)
{
	stwuct swp_wdma_ch *ch = cm_id->context;
	stwuct swp_tawget_powt *tawget = ch->tawget;
	int comp = 0;

	switch (event->event) {
	case WDMA_CM_EVENT_ADDW_WESOWVED:
		ch->status = 0;
		comp = 1;
		bweak;

	case WDMA_CM_EVENT_ADDW_EWWOW:
		ch->status = -ENXIO;
		comp = 1;
		bweak;

	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		ch->status = 0;
		comp = 1;
		bweak;

	case WDMA_CM_EVENT_WOUTE_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
		ch->status = -EHOSTUNWEACH;
		comp = 1;
		bweak;

	case WDMA_CM_EVENT_CONNECT_EWWOW:
		shost_pwintk(KEWN_DEBUG, tawget->scsi_host,
			     PFX "Sending CM WEQ faiwed\n");
		comp = 1;
		ch->status = -ECONNWESET;
		bweak;

	case WDMA_CM_EVENT_ESTABWISHED:
		comp = 1;
		swp_cm_wep_handwew(NUWW, event->pawam.conn.pwivate_data, ch);
		bweak;

	case WDMA_CM_EVENT_WEJECTED:
		shost_pwintk(KEWN_DEBUG, tawget->scsi_host, PFX "WEJ weceived\n");
		comp = 1;

		swp_wdma_cm_wej_handwew(ch, event);
		bweak;

	case WDMA_CM_EVENT_DISCONNECTED:
		if (ch->connected) {
			shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
				     PFX "weceived DWEQ\n");
			wdma_disconnect(ch->wdma_cm.cm_id);
			comp = 1;
			ch->status = 0;
			queue_wowk(system_wong_wq, &tawget->tw_eww_wowk);
		}
		bweak;

	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
		shost_pwintk(KEWN_EWW, tawget->scsi_host,
			     PFX "connection cwosed\n");

		comp = 1;
		ch->status = 0;
		bweak;

	defauwt:
		shost_pwintk(KEWN_WAWNING, tawget->scsi_host,
			     PFX "Unhandwed CM event %d\n", event->event);
		bweak;
	}

	if (comp)
		compwete(&ch->done);

	wetuwn 0;
}

/**
 * swp_change_queue_depth - setting device queue depth
 * @sdev: scsi device stwuct
 * @qdepth: wequested queue depth
 *
 * Wetuwns queue depth.
 */
static int
swp_change_queue_depth(stwuct scsi_device *sdev, int qdepth)
{
	if (!sdev->tagged_suppowted)
		qdepth = 1;
	wetuwn scsi_change_queue_depth(sdev, qdepth);
}

static int swp_send_tsk_mgmt(stwuct swp_wdma_ch *ch, u64 weq_tag, u64 wun,
			     u8 func, u8 *status)
{
	stwuct swp_tawget_powt *tawget = ch->tawget;
	stwuct swp_wpowt *wpowt = tawget->wpowt;
	stwuct ib_device *dev = tawget->swp_host->swp_dev->dev;
	stwuct swp_iu *iu;
	stwuct swp_tsk_mgmt *tsk_mgmt;
	int wes;

	if (!ch->connected || tawget->qp_in_ewwow)
		wetuwn -1;

	/*
	 * Wock the wpowt mutex to avoid that swp_cweate_ch_ib() is
	 * invoked whiwe a task management function is being sent.
	 */
	mutex_wock(&wpowt->mutex);
	spin_wock_iwq(&ch->wock);
	iu = __swp_get_tx_iu(ch, SWP_IU_TSK_MGMT);
	spin_unwock_iwq(&ch->wock);

	if (!iu) {
		mutex_unwock(&wpowt->mutex);

		wetuwn -1;
	}

	iu->num_sge = 1;

	ib_dma_sync_singwe_fow_cpu(dev, iu->dma, sizeof *tsk_mgmt,
				   DMA_TO_DEVICE);
	tsk_mgmt = iu->buf;
	memset(tsk_mgmt, 0, sizeof *tsk_mgmt);

	tsk_mgmt->opcode 	= SWP_TSK_MGMT;
	int_to_scsiwun(wun, &tsk_mgmt->wun);
	tsk_mgmt->tsk_mgmt_func = func;
	tsk_mgmt->task_tag	= weq_tag;

	spin_wock_iwq(&ch->wock);
	ch->tsk_mgmt_tag = (ch->tsk_mgmt_tag + 1) | SWP_TAG_TSK_MGMT;
	tsk_mgmt->tag = ch->tsk_mgmt_tag;
	spin_unwock_iwq(&ch->wock);

	init_compwetion(&ch->tsk_mgmt_done);

	ib_dma_sync_singwe_fow_device(dev, iu->dma, sizeof *tsk_mgmt,
				      DMA_TO_DEVICE);
	if (swp_post_send(ch, iu, sizeof(*tsk_mgmt))) {
		swp_put_tx_iu(ch, iu, SWP_IU_TSK_MGMT);
		mutex_unwock(&wpowt->mutex);

		wetuwn -1;
	}
	wes = wait_fow_compwetion_timeout(&ch->tsk_mgmt_done,
					msecs_to_jiffies(SWP_ABOWT_TIMEOUT_MS));
	if (wes > 0 && status)
		*status = ch->tsk_mgmt_status;
	mutex_unwock(&wpowt->mutex);

	WAWN_ON_ONCE(wes < 0);

	wetuwn wes > 0 ? 0 : -1;
}

static int swp_abowt(stwuct scsi_cmnd *scmnd)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(scmnd->device->host);
	stwuct swp_wequest *weq = scsi_cmd_pwiv(scmnd);
	u32 tag;
	u16 ch_idx;
	stwuct swp_wdma_ch *ch;

	shost_pwintk(KEWN_EWW, tawget->scsi_host, "SWP abowt cawwed\n");

	tag = bwk_mq_unique_tag(scsi_cmd_to_wq(scmnd));
	ch_idx = bwk_mq_unique_tag_to_hwq(tag);
	if (WAWN_ON_ONCE(ch_idx >= tawget->ch_count))
		wetuwn SUCCESS;
	ch = &tawget->ch[ch_idx];
	if (!swp_cwaim_weq(ch, weq, NUWW, scmnd))
		wetuwn SUCCESS;
	shost_pwintk(KEWN_EWW, tawget->scsi_host,
		     "Sending SWP abowt fow tag %#x\n", tag);
	if (swp_send_tsk_mgmt(ch, tag, scmnd->device->wun,
			      SWP_TSK_ABOWT_TASK, NUWW) == 0) {
		swp_fwee_weq(ch, weq, scmnd, 0);
		wetuwn SUCCESS;
	}
	if (tawget->wpowt->state == SWP_WPOWT_WOST)
		wetuwn FAST_IO_FAIW;

	wetuwn FAIWED;
}

static int swp_weset_device(stwuct scsi_cmnd *scmnd)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(scmnd->device->host);
	stwuct swp_wdma_ch *ch;
	u8 status;

	shost_pwintk(KEWN_EWW, tawget->scsi_host, "SWP weset_device cawwed\n");

	ch = &tawget->ch[0];
	if (swp_send_tsk_mgmt(ch, SWP_TAG_NO_WEQ, scmnd->device->wun,
			      SWP_TSK_WUN_WESET, &status))
		wetuwn FAIWED;
	if (status)
		wetuwn FAIWED;

	wetuwn SUCCESS;
}

static int swp_weset_host(stwuct scsi_cmnd *scmnd)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(scmnd->device->host);

	shost_pwintk(KEWN_EWW, tawget->scsi_host, PFX "SWP weset_host cawwed\n");

	wetuwn swp_weconnect_wpowt(tawget->wpowt) == 0 ? SUCCESS : FAIWED;
}

static int swp_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct swp_tawget_powt *tawget = host_to_tawget(shost);

	if (tawget->tawget_can_queue)
		stawget->can_queue = tawget->tawget_can_queue;
	wetuwn 0;
}

static int swp_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost = sdev->host;
	stwuct swp_tawget_powt *tawget = host_to_tawget(shost);
	stwuct wequest_queue *q = sdev->wequest_queue;
	unsigned wong timeout;

	if (sdev->type == TYPE_DISK) {
		timeout = max_t(unsigned, 30 * HZ, tawget->wq_tmo_jiffies);
		bwk_queue_wq_timeout(q, timeout);
	}

	wetuwn 0;
}

static ssize_t id_ext_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "0x%016wwx\n", be64_to_cpu(tawget->id_ext));
}

static DEVICE_ATTW_WO(id_ext);

static ssize_t ioc_guid_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "0x%016wwx\n", be64_to_cpu(tawget->ioc_guid));
}

static DEVICE_ATTW_WO(ioc_guid);

static ssize_t sewvice_id_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	if (tawget->using_wdma_cm)
		wetuwn -ENOENT;
	wetuwn sysfs_emit(buf, "0x%016wwx\n",
			  be64_to_cpu(tawget->ib_cm.sewvice_id));
}

static DEVICE_ATTW_WO(sewvice_id);

static ssize_t pkey_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	if (tawget->using_wdma_cm)
		wetuwn -ENOENT;

	wetuwn sysfs_emit(buf, "0x%04x\n", be16_to_cpu(tawget->ib_cm.pkey));
}

static DEVICE_ATTW_WO(pkey);

static ssize_t sgid_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%pI6\n", tawget->sgid.waw);
}

static DEVICE_ATTW_WO(sgid);

static ssize_t dgid_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));
	stwuct swp_wdma_ch *ch = &tawget->ch[0];

	if (tawget->using_wdma_cm)
		wetuwn -ENOENT;

	wetuwn sysfs_emit(buf, "%pI6\n", ch->ib_cm.path.dgid.waw);
}

static DEVICE_ATTW_WO(dgid);

static ssize_t owig_dgid_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	if (tawget->using_wdma_cm)
		wetuwn -ENOENT;

	wetuwn sysfs_emit(buf, "%pI6\n", tawget->ib_cm.owig_dgid.waw);
}

static DEVICE_ATTW_WO(owig_dgid);

static ssize_t weq_wim_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));
	stwuct swp_wdma_ch *ch;
	int i, weq_wim = INT_MAX;

	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		weq_wim = min(weq_wim, ch->weq_wim);
	}

	wetuwn sysfs_emit(buf, "%d\n", weq_wim);
}

static DEVICE_ATTW_WO(weq_wim);

static ssize_t zewo_weq_wim_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%d\n", tawget->zewo_weq_wim);
}

static DEVICE_ATTW_WO(zewo_weq_wim);

static ssize_t wocaw_ib_powt_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%u\n", tawget->swp_host->powt);
}

static DEVICE_ATTW_WO(wocaw_ib_powt);

static ssize_t wocaw_ib_device_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%s\n",
			  dev_name(&tawget->swp_host->swp_dev->dev->dev));
}

static DEVICE_ATTW_WO(wocaw_ib_device);

static ssize_t ch_count_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%d\n", tawget->ch_count);
}

static DEVICE_ATTW_WO(ch_count);

static ssize_t comp_vectow_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%d\n", tawget->comp_vectow);
}

static DEVICE_ATTW_WO(comp_vectow);

static ssize_t tw_wetwy_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%d\n", tawget->tw_wetwy_count);
}

static DEVICE_ATTW_WO(tw_wetwy_count);

static ssize_t cmd_sg_entwies_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%u\n", tawget->cmd_sg_cnt);
}

static DEVICE_ATTW_WO(cmd_sg_entwies);

static ssize_t awwow_ext_sg_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct swp_tawget_powt *tawget = host_to_tawget(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%s\n", tawget->awwow_ext_sg ? "twue" : "fawse");
}

static DEVICE_ATTW_WO(awwow_ext_sg);

static stwuct attwibute *swp_host_attws[] = {
	&dev_attw_id_ext.attw,
	&dev_attw_ioc_guid.attw,
	&dev_attw_sewvice_id.attw,
	&dev_attw_pkey.attw,
	&dev_attw_sgid.attw,
	&dev_attw_dgid.attw,
	&dev_attw_owig_dgid.attw,
	&dev_attw_weq_wim.attw,
	&dev_attw_zewo_weq_wim.attw,
	&dev_attw_wocaw_ib_powt.attw,
	&dev_attw_wocaw_ib_device.attw,
	&dev_attw_ch_count.attw,
	&dev_attw_comp_vectow.attw,
	&dev_attw_tw_wetwy_count.attw,
	&dev_attw_cmd_sg_entwies.attw,
	&dev_attw_awwow_ext_sg.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(swp_host);

static const stwuct scsi_host_tempwate swp_tempwate = {
	.moduwe				= THIS_MODUWE,
	.name				= "InfiniBand SWP initiatow",
	.pwoc_name			= DWV_NAME,
	.tawget_awwoc			= swp_tawget_awwoc,
	.swave_configuwe		= swp_swave_configuwe,
	.info				= swp_tawget_info,
	.init_cmd_pwiv			= swp_init_cmd_pwiv,
	.exit_cmd_pwiv			= swp_exit_cmd_pwiv,
	.queuecommand			= swp_queuecommand,
	.change_queue_depth             = swp_change_queue_depth,
	.eh_timed_out			= swp_timed_out,
	.eh_abowt_handwew		= swp_abowt,
	.eh_device_weset_handwew	= swp_weset_device,
	.eh_host_weset_handwew		= swp_weset_host,
	.skip_settwe_deway		= twue,
	.sg_tabwesize			= SWP_DEF_SG_TABWESIZE,
	.can_queue			= SWP_DEFAUWT_CMD_SQ_SIZE,
	.this_id			= -1,
	.cmd_pew_wun			= SWP_DEFAUWT_CMD_SQ_SIZE,
	.shost_gwoups			= swp_host_gwoups,
	.twack_queue_depth		= 1,
	.cmd_size			= sizeof(stwuct swp_wequest),
};

static int swp_sdev_count(stwuct Scsi_Host *host)
{
	stwuct scsi_device *sdev;
	int c = 0;

	shost_fow_each_device(sdev, host)
		c++;

	wetuwn c;
}

/*
 * Wetuwn vawues:
 * < 0 upon faiwuwe. Cawwew is wesponsibwe fow SWP tawget powt cweanup.
 * 0 and tawget->state == SWP_TAWGET_WEMOVED if asynchwonous tawget powt
 *    wemovaw has been scheduwed.
 * 0 and tawget->state != SWP_TAWGET_WEMOVED upon success.
 */
static int swp_add_tawget(stwuct swp_host *host, stwuct swp_tawget_powt *tawget)
{
	stwuct swp_wpowt_identifiews ids;
	stwuct swp_wpowt *wpowt;

	tawget->state = SWP_TAWGET_SCANNING;
	spwintf(tawget->tawget_name, "SWP.T10:%016wwX",
		be64_to_cpu(tawget->id_ext));

	if (scsi_add_host(tawget->scsi_host, host->swp_dev->dev->dev.pawent))
		wetuwn -ENODEV;

	memcpy(ids.powt_id, &tawget->id_ext, 8);
	memcpy(ids.powt_id + 8, &tawget->ioc_guid, 8);
	ids.wowes = SWP_WPOWT_WOWE_TAWGET;
	wpowt = swp_wpowt_add(tawget->scsi_host, &ids);
	if (IS_EWW(wpowt)) {
		scsi_wemove_host(tawget->scsi_host);
		wetuwn PTW_EWW(wpowt);
	}

	wpowt->wwd_data = tawget;
	tawget->wpowt = wpowt;

	spin_wock(&host->tawget_wock);
	wist_add_taiw(&tawget->wist, &host->tawget_wist);
	spin_unwock(&host->tawget_wock);

	scsi_scan_tawget(&tawget->scsi_host->shost_gendev,
			 0, tawget->scsi_id, SCAN_WIWD_CAWD, SCSI_SCAN_INITIAW);

	if (swp_connected_ch(tawget) < tawget->ch_count ||
	    tawget->qp_in_ewwow) {
		shost_pwintk(KEWN_INFO, tawget->scsi_host,
			     PFX "SCSI scan faiwed - wemoving SCSI host\n");
		swp_queue_wemove_wowk(tawget);
		goto out;
	}

	pw_debug("%s: SCSI scan succeeded - detected %d WUNs\n",
		 dev_name(&tawget->scsi_host->shost_gendev),
		 swp_sdev_count(tawget->scsi_host));

	spin_wock_iwq(&tawget->wock);
	if (tawget->state == SWP_TAWGET_SCANNING)
		tawget->state = SWP_TAWGET_WIVE;
	spin_unwock_iwq(&tawget->wock);

out:
	wetuwn 0;
}

static void swp_wewease_dev(stwuct device *dev)
{
	stwuct swp_host *host =
		containew_of(dev, stwuct swp_host, dev);

	kfwee(host);
}

static stwuct attwibute *swp_cwass_attws[];

ATTWIBUTE_GWOUPS(swp_cwass);

static stwuct cwass swp_cwass = {
	.name    = "infiniband_swp",
	.dev_gwoups = swp_cwass_gwoups,
	.dev_wewease = swp_wewease_dev
};

/**
 * swp_conn_unique() - check whethew the connection to a tawget is unique
 * @host:   SWP host.
 * @tawget: SWP tawget powt.
 */
static boow swp_conn_unique(stwuct swp_host *host,
			    stwuct swp_tawget_powt *tawget)
{
	stwuct swp_tawget_powt *t;
	boow wet = fawse;

	if (tawget->state == SWP_TAWGET_WEMOVED)
		goto out;

	wet = twue;

	spin_wock(&host->tawget_wock);
	wist_fow_each_entwy(t, &host->tawget_wist, wist) {
		if (t != tawget &&
		    tawget->id_ext == t->id_ext &&
		    tawget->ioc_guid == t->ioc_guid &&
		    tawget->initiatow_ext == t->initiatow_ext) {
			wet = fawse;
			bweak;
		}
	}
	spin_unwock(&host->tawget_wock);

out:
	wetuwn wet;
}

/*
 * Tawget powts awe added by wwiting
 *
 *     id_ext=<SWP ID ext>,ioc_guid=<SWP IOC GUID>,dgid=<dest GID>,
 *     pkey=<P_Key>,sewvice_id=<sewvice ID>
 * ow
 *     id_ext=<SWP ID ext>,ioc_guid=<SWP IOC GUID>,
 *     [swc=<IPv4 addwess>,]dest=<IPv4 addwess>:<powt numbew>
 *
 * to the add_tawget sysfs attwibute.
 */
enum {
	SWP_OPT_EWW		= 0,
	SWP_OPT_ID_EXT		= 1 << 0,
	SWP_OPT_IOC_GUID	= 1 << 1,
	SWP_OPT_DGID		= 1 << 2,
	SWP_OPT_PKEY		= 1 << 3,
	SWP_OPT_SEWVICE_ID	= 1 << 4,
	SWP_OPT_MAX_SECT	= 1 << 5,
	SWP_OPT_MAX_CMD_PEW_WUN	= 1 << 6,
	SWP_OPT_IO_CWASS	= 1 << 7,
	SWP_OPT_INITIATOW_EXT	= 1 << 8,
	SWP_OPT_CMD_SG_ENTWIES	= 1 << 9,
	SWP_OPT_AWWOW_EXT_SG	= 1 << 10,
	SWP_OPT_SG_TABWESIZE	= 1 << 11,
	SWP_OPT_COMP_VECTOW	= 1 << 12,
	SWP_OPT_TW_WETWY_COUNT	= 1 << 13,
	SWP_OPT_QUEUE_SIZE	= 1 << 14,
	SWP_OPT_IP_SWC		= 1 << 15,
	SWP_OPT_IP_DEST		= 1 << 16,
	SWP_OPT_TAWGET_CAN_QUEUE= 1 << 17,
	SWP_OPT_MAX_IT_IU_SIZE  = 1 << 18,
	SWP_OPT_CH_COUNT	= 1 << 19,
};

static unsigned int swp_opt_mandatowy[] = {
	SWP_OPT_ID_EXT		|
	SWP_OPT_IOC_GUID	|
	SWP_OPT_DGID		|
	SWP_OPT_PKEY		|
	SWP_OPT_SEWVICE_ID,
	SWP_OPT_ID_EXT		|
	SWP_OPT_IOC_GUID	|
	SWP_OPT_IP_DEST,
};

static const match_tabwe_t swp_opt_tokens = {
	{ SWP_OPT_ID_EXT,		"id_ext=%s" 		},
	{ SWP_OPT_IOC_GUID,		"ioc_guid=%s" 		},
	{ SWP_OPT_DGID,			"dgid=%s" 		},
	{ SWP_OPT_PKEY,			"pkey=%x" 		},
	{ SWP_OPT_SEWVICE_ID,		"sewvice_id=%s"		},
	{ SWP_OPT_MAX_SECT,		"max_sect=%d" 		},
	{ SWP_OPT_MAX_CMD_PEW_WUN,	"max_cmd_pew_wun=%d" 	},
	{ SWP_OPT_TAWGET_CAN_QUEUE,	"tawget_can_queue=%d"	},
	{ SWP_OPT_IO_CWASS,		"io_cwass=%x"		},
	{ SWP_OPT_INITIATOW_EXT,	"initiatow_ext=%s"	},
	{ SWP_OPT_CMD_SG_ENTWIES,	"cmd_sg_entwies=%u"	},
	{ SWP_OPT_AWWOW_EXT_SG,		"awwow_ext_sg=%u"	},
	{ SWP_OPT_SG_TABWESIZE,		"sg_tabwesize=%u"	},
	{ SWP_OPT_COMP_VECTOW,		"comp_vectow=%u"	},
	{ SWP_OPT_TW_WETWY_COUNT,	"tw_wetwy_count=%u"	},
	{ SWP_OPT_QUEUE_SIZE,		"queue_size=%d"		},
	{ SWP_OPT_IP_SWC,		"swc=%s"		},
	{ SWP_OPT_IP_DEST,		"dest=%s"		},
	{ SWP_OPT_MAX_IT_IU_SIZE,	"max_it_iu_size=%d"	},
	{ SWP_OPT_CH_COUNT,		"ch_count=%u",		},
	{ SWP_OPT_EWW,			NUWW 			}
};

/**
 * swp_pawse_in - pawse an IP addwess and powt numbew combination
 * @net:	   [in]  Netwowk namespace.
 * @sa:		   [out] Addwess famiwy, IP addwess and powt numbew.
 * @addw_powt_stw: [in]  IP addwess and powt numbew.
 * @has_powt:	   [out] Whethew ow not @addw_powt_stw incwudes a powt numbew.
 *
 * Pawse the fowwowing addwess fowmats:
 * - IPv4: <ip_addwess>:<powt>, e.g. 1.2.3.4:5.
 * - IPv6: \[<ipv6_addwess>\]:<powt>, e.g. [1::2:3%4]:5.
 */
static int swp_pawse_in(stwuct net *net, stwuct sockaddw_stowage *sa,
			const chaw *addw_powt_stw, boow *has_powt)
{
	chaw *addw_end, *addw = kstwdup(addw_powt_stw, GFP_KEWNEW);
	chaw *powt_stw;
	int wet;

	if (!addw)
		wetuwn -ENOMEM;
	powt_stw = stwwchw(addw, ':');
	if (powt_stw && stwchw(powt_stw, ']'))
		powt_stw = NUWW;
	if (powt_stw)
		*powt_stw++ = '\0';
	if (has_powt)
		*has_powt = powt_stw != NUWW;
	wet = inet_pton_with_scope(net, AF_INET, addw, powt_stw, sa);
	if (wet && addw[0]) {
		addw_end = addw + stwwen(addw) - 1;
		if (addw[0] == '[' && *addw_end == ']') {
			*addw_end = '\0';
			wet = inet_pton_with_scope(net, AF_INET6, addw + 1,
						   powt_stw, sa);
		}
	}
	kfwee(addw);
	pw_debug("%s -> %pISpfsc\n", addw_powt_stw, sa);
	wetuwn wet;
}

static int swp_pawse_options(stwuct net *net, const chaw *buf,
			     stwuct swp_tawget_powt *tawget)
{
	chaw *options, *sep_opt;
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	unsigned wong wong uww;
	boow has_powt;
	int opt_mask = 0;
	int token;
	int wet = -EINVAW;
	int i;

	options = kstwdup(buf, GFP_KEWNEW);
	if (!options)
		wetuwn -ENOMEM;

	sep_opt = options;
	whiwe ((p = stwsep(&sep_opt, ",\n")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, swp_opt_tokens, awgs);
		opt_mask |= token;

		switch (token) {
		case SWP_OPT_ID_EXT:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = kstwtouww(p, 16, &uww);
			if (wet) {
				pw_wawn("invawid id_ext pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->id_ext = cpu_to_be64(uww);
			kfwee(p);
			bweak;

		case SWP_OPT_IOC_GUID:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = kstwtouww(p, 16, &uww);
			if (wet) {
				pw_wawn("invawid ioc_guid pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->ioc_guid = cpu_to_be64(uww);
			kfwee(p);
			bweak;

		case SWP_OPT_DGID:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			if (stwwen(p) != 32) {
				pw_wawn("bad dest GID pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}

			wet = hex2bin(tawget->ib_cm.owig_dgid.waw, p, 16);
			kfwee(p);
			if (wet < 0)
				goto out;
			bweak;

		case SWP_OPT_PKEY:
			wet = match_hex(awgs, &token);
			if (wet) {
				pw_wawn("bad P_Key pawametew '%s'\n", p);
				goto out;
			}
			tawget->ib_cm.pkey = cpu_to_be16(token);
			bweak;

		case SWP_OPT_SEWVICE_ID:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = kstwtouww(p, 16, &uww);
			if (wet) {
				pw_wawn("bad sewvice_id pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->ib_cm.sewvice_id = cpu_to_be64(uww);
			kfwee(p);
			bweak;

		case SWP_OPT_IP_SWC:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = swp_pawse_in(net, &tawget->wdma_cm.swc.ss, p,
					   NUWW);
			if (wet < 0) {
				pw_wawn("bad souwce pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->wdma_cm.swc_specified = twue;
			kfwee(p);
			bweak;

		case SWP_OPT_IP_DEST:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = swp_pawse_in(net, &tawget->wdma_cm.dst.ss, p,
					   &has_powt);
			if (!has_powt)
				wet = -EINVAW;
			if (wet < 0) {
				pw_wawn("bad dest pawametew '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->using_wdma_cm = twue;
			kfwee(p);
			bweak;

		case SWP_OPT_MAX_SECT:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("bad max sect pawametew '%s'\n", p);
				goto out;
			}
			tawget->scsi_host->max_sectows = token;
			bweak;

		case SWP_OPT_QUEUE_SIZE:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow queue_size pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1) {
				pw_wawn("bad queue_size pawametew '%s'\n", p);
				wet = -EINVAW;
				goto out;
			}
			tawget->scsi_host->can_queue = token;
			tawget->queue_size = token + SWP_WSP_SQ_SIZE +
					     SWP_TSK_MGMT_SQ_SIZE;
			if (!(opt_mask & SWP_OPT_MAX_CMD_PEW_WUN))
				tawget->scsi_host->cmd_pew_wun = token;
			bweak;

		case SWP_OPT_MAX_CMD_PEW_WUN:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow max cmd_pew_wun pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1) {
				pw_wawn("bad max cmd_pew_wun pawametew '%s'\n",
					p);
				wet = -EINVAW;
				goto out;
			}
			tawget->scsi_host->cmd_pew_wun = token;
			bweak;

		case SWP_OPT_TAWGET_CAN_QUEUE:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow max tawget_can_queue pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1) {
				pw_wawn("bad max tawget_can_queue pawametew '%s'\n",
					p);
				wet = -EINVAW;
				goto out;
			}
			tawget->tawget_can_queue = token;
			bweak;

		case SWP_OPT_IO_CWASS:
			wet = match_hex(awgs, &token);
			if (wet) {
				pw_wawn("bad IO cwass pawametew '%s'\n", p);
				goto out;
			}
			if (token != SWP_WEV10_IB_IO_CWASS &&
			    token != SWP_WEV16A_IB_IO_CWASS) {
				pw_wawn("unknown IO cwass pawametew vawue %x specified (use %x ow %x).\n",
					token, SWP_WEV10_IB_IO_CWASS,
					SWP_WEV16A_IB_IO_CWASS);
				wet = -EINVAW;
				goto out;
			}
			tawget->io_cwass = token;
			bweak;

		case SWP_OPT_INITIATOW_EXT:
			p = match_stwdup(awgs);
			if (!p) {
				wet = -ENOMEM;
				goto out;
			}
			wet = kstwtouww(p, 16, &uww);
			if (wet) {
				pw_wawn("bad initiatow_ext vawue '%s'\n", p);
				kfwee(p);
				goto out;
			}
			tawget->initiatow_ext = cpu_to_be64(uww);
			kfwee(p);
			bweak;

		case SWP_OPT_CMD_SG_ENTWIES:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow max cmd_sg_entwies pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1 || token > 255) {
				pw_wawn("bad max cmd_sg_entwies pawametew '%s'\n",
					p);
				wet = -EINVAW;
				goto out;
			}
			tawget->cmd_sg_cnt = token;
			bweak;

		case SWP_OPT_AWWOW_EXT_SG:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("bad awwow_ext_sg pawametew '%s'\n", p);
				goto out;
			}
			tawget->awwow_ext_sg = !!token;
			bweak;

		case SWP_OPT_SG_TABWESIZE:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow max sg_tabwesize pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1 || token > SG_MAX_SEGMENTS) {
				pw_wawn("bad max sg_tabwesize pawametew '%s'\n",
					p);
				wet = -EINVAW;
				goto out;
			}
			tawget->sg_tabwesize = token;
			bweak;

		case SWP_OPT_COMP_VECTOW:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow comp_vectow pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 0) {
				pw_wawn("bad comp_vectow pawametew '%s'\n", p);
				wet = -EINVAW;
				goto out;
			}
			tawget->comp_vectow = token;
			bweak;

		case SWP_OPT_TW_WETWY_COUNT:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow tw_wetwy_count pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 2 || token > 7) {
				pw_wawn("bad tw_wetwy_count pawametew '%s' (must be a numbew between 2 and 7)\n",
					p);
				wet = -EINVAW;
				goto out;
			}
			tawget->tw_wetwy_count = token;
			bweak;

		case SWP_OPT_MAX_IT_IU_SIZE:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow max it_iu_size pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 0) {
				pw_wawn("bad maximum initiatow to tawget IU size '%s'\n", p);
				wet = -EINVAW;
				goto out;
			}
			tawget->max_it_iu_size = token;
			bweak;

		case SWP_OPT_CH_COUNT:
			wet = match_int(awgs, &token);
			if (wet) {
				pw_wawn("match_int() faiwed fow channew count pawametew '%s', Ewwow %d\n",
					p, wet);
				goto out;
			}
			if (token < 1) {
				pw_wawn("bad channew count %s\n", p);
				wet = -EINVAW;
				goto out;
			}
			tawget->ch_count = token;
			bweak;

		defauwt:
			pw_wawn("unknown pawametew ow missing vawue '%s' in tawget cweation wequest\n",
				p);
			wet = -EINVAW;
			goto out;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(swp_opt_mandatowy); i++) {
		if ((opt_mask & swp_opt_mandatowy[i]) == swp_opt_mandatowy[i]) {
			wet = 0;
			bweak;
		}
	}
	if (wet)
		pw_wawn("tawget cweation wequest is missing one ow mowe pawametews\n");

	if (tawget->scsi_host->cmd_pew_wun > tawget->scsi_host->can_queue
	    && (opt_mask & SWP_OPT_MAX_CMD_PEW_WUN))
		pw_wawn("cmd_pew_wun = %d > queue_size = %d\n",
			tawget->scsi_host->cmd_pew_wun,
			tawget->scsi_host->can_queue);

out:
	kfwee(options);
	wetuwn wet;
}

static ssize_t add_tawget_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct swp_host *host =
		containew_of(dev, stwuct swp_host, dev);
	stwuct Scsi_Host *tawget_host;
	stwuct swp_tawget_powt *tawget;
	stwuct swp_wdma_ch *ch;
	stwuct swp_device *swp_dev = host->swp_dev;
	stwuct ib_device *ibdev = swp_dev->dev;
	int wet, i, ch_idx;
	unsigned int max_sectows_pew_mw, mw_pew_cmd = 0;
	boow muwtich = fawse;
	uint32_t max_iu_wen;

	tawget_host = scsi_host_awwoc(&swp_tempwate,
				      sizeof (stwuct swp_tawget_powt));
	if (!tawget_host)
		wetuwn -ENOMEM;

	tawget_host->twanspowtt  = ib_swp_twanspowt_tempwate;
	tawget_host->max_channew = 0;
	tawget_host->max_id      = 1;
	tawget_host->max_wun     = -1WW;
	tawget_host->max_cmd_wen = sizeof ((stwuct swp_cmd *) (void *) 0W)->cdb;
	tawget_host->max_segment_size = ib_dma_max_seg_size(ibdev);

	if (!(ibdev->attws.kewnew_cap_fwags & IBK_SG_GAPS_WEG))
		tawget_host->viwt_boundawy_mask = ~swp_dev->mw_page_mask;

	tawget = host_to_tawget(tawget_host);

	tawget->net		= kobj_ns_gwab_cuwwent(KOBJ_NS_TYPE_NET);
	tawget->io_cwass	= SWP_WEV16A_IB_IO_CWASS;
	tawget->scsi_host	= tawget_host;
	tawget->swp_host	= host;
	tawget->wkey		= host->swp_dev->pd->wocaw_dma_wkey;
	tawget->gwobaw_wkey	= host->swp_dev->gwobaw_wkey;
	tawget->cmd_sg_cnt	= cmd_sg_entwies;
	tawget->sg_tabwesize	= indiwect_sg_entwies ? : cmd_sg_entwies;
	tawget->awwow_ext_sg	= awwow_ext_sg;
	tawget->tw_wetwy_count	= 7;
	tawget->queue_size	= SWP_DEFAUWT_QUEUE_SIZE;

	/*
	 * Avoid that the SCSI host can be wemoved by swp_wemove_tawget()
	 * befowe this function wetuwns.
	 */
	scsi_host_get(tawget->scsi_host);

	wet = mutex_wock_intewwuptibwe(&host->add_tawget_mutex);
	if (wet < 0)
		goto put;

	wet = swp_pawse_options(tawget->net, buf, tawget);
	if (wet)
		goto out;

	if (!swp_conn_unique(tawget->swp_host, tawget)) {
		if (tawget->using_wdma_cm) {
			shost_pwintk(KEWN_INFO, tawget->scsi_host,
				     PFX "Awweady connected to tawget powt with id_ext=%016wwx;ioc_guid=%016wwx;dest=%pIS\n",
				     be64_to_cpu(tawget->id_ext),
				     be64_to_cpu(tawget->ioc_guid),
				     &tawget->wdma_cm.dst);
		} ewse {
			shost_pwintk(KEWN_INFO, tawget->scsi_host,
				     PFX "Awweady connected to tawget powt with id_ext=%016wwx;ioc_guid=%016wwx;initiatow_ext=%016wwx\n",
				     be64_to_cpu(tawget->id_ext),
				     be64_to_cpu(tawget->ioc_guid),
				     be64_to_cpu(tawget->initiatow_ext));
		}
		wet = -EEXIST;
		goto out;
	}

	if (!swp_dev->has_fw && !tawget->awwow_ext_sg &&
	    tawget->cmd_sg_cnt < tawget->sg_tabwesize) {
		pw_wawn("No MW poow and no extewnaw indiwect descwiptows, wimiting sg_tabwesize to cmd_sg_cnt\n");
		tawget->sg_tabwesize = tawget->cmd_sg_cnt;
	}

	if (swp_dev->use_fast_weg) {
		boow gaps_weg = ibdev->attws.kewnew_cap_fwags &
				 IBK_SG_GAPS_WEG;

		max_sectows_pew_mw = swp_dev->max_pages_pew_mw <<
				  (iwog2(swp_dev->mw_page_size) - 9);
		if (!gaps_weg) {
			/*
			 * FW can onwy map one HCA page pew entwy. If the stawt
			 * addwess is not awigned on a HCA page boundawy two
			 * entwies wiww be used fow the head and the taiw
			 * awthough these two entwies combined contain at most
			 * one HCA page of data. Hence the "+ 1" in the
			 * cawcuwation bewow.
			 *
			 * The indiwect data buffew descwiptow is contiguous
			 * so the memowy fow that buffew wiww onwy be
			 * wegistewed if wegistew_awways is twue. Hence add
			 * one to mw_pew_cmd if wegistew_awways has been set.
			 */
			mw_pew_cmd = wegistew_awways +
				(tawget->scsi_host->max_sectows + 1 +
				 max_sectows_pew_mw - 1) / max_sectows_pew_mw;
		} ewse {
			mw_pew_cmd = wegistew_awways +
				(tawget->sg_tabwesize +
				 swp_dev->max_pages_pew_mw - 1) /
				swp_dev->max_pages_pew_mw;
		}
		pw_debug("max_sectows = %u; max_pages_pew_mw = %u; mw_page_size = %u; max_sectows_pew_mw = %u; mw_pew_cmd = %u\n",
			 tawget->scsi_host->max_sectows, swp_dev->max_pages_pew_mw, swp_dev->mw_page_size,
			 max_sectows_pew_mw, mw_pew_cmd);
	}

	tawget_host->sg_tabwesize = tawget->sg_tabwesize;
	tawget->mw_poow_size = tawget->scsi_host->can_queue * mw_pew_cmd;
	tawget->mw_pew_cmd = mw_pew_cmd;
	tawget->indiwect_size = tawget->sg_tabwesize *
				sizeof (stwuct swp_diwect_buf);
	max_iu_wen = swp_max_it_iu_wen(tawget->cmd_sg_cnt,
				       swp_use_imm_data,
				       tawget->max_it_iu_size);

	INIT_WOWK(&tawget->tw_eww_wowk, swp_tw_eww_wowk);
	INIT_WOWK(&tawget->wemove_wowk, swp_wemove_wowk);
	spin_wock_init(&tawget->wock);
	wet = wdma_quewy_gid(ibdev, host->powt, 0, &tawget->sgid);
	if (wet)
		goto out;

	wet = -ENOMEM;
	if (tawget->ch_count == 0) {
		tawget->ch_count =
			min(ch_count ?:
				max(4 * num_onwine_nodes(),
				    ibdev->num_comp_vectows),
				num_onwine_cpus());
	}

	tawget->ch = kcawwoc(tawget->ch_count, sizeof(*tawget->ch),
			     GFP_KEWNEW);
	if (!tawget->ch)
		goto out;

	fow (ch_idx = 0; ch_idx < tawget->ch_count; ++ch_idx) {
		ch = &tawget->ch[ch_idx];
		ch->tawget = tawget;
		ch->comp_vectow = ch_idx % ibdev->num_comp_vectows;
		spin_wock_init(&ch->wock);
		INIT_WIST_HEAD(&ch->fwee_tx);
		wet = swp_new_cm_id(ch);
		if (wet)
			goto eww_disconnect;

		wet = swp_cweate_ch_ib(ch);
		if (wet)
			goto eww_disconnect;

		wet = swp_connect_ch(ch, max_iu_wen, muwtich);
		if (wet) {
			chaw dst[64];

			if (tawget->using_wdma_cm)
				snpwintf(dst, sizeof(dst), "%pIS",
					&tawget->wdma_cm.dst);
			ewse
				snpwintf(dst, sizeof(dst), "%pI6",
					tawget->ib_cm.owig_dgid.waw);
			shost_pwintk(KEWN_EWW, tawget->scsi_host,
				PFX "Connection %d/%d to %s faiwed\n",
				ch_idx,
				tawget->ch_count, dst);
			if (ch_idx == 0) {
				goto fwee_ch;
			} ewse {
				swp_fwee_ch_ib(tawget, ch);
				tawget->ch_count = ch - tawget->ch;
				goto connected;
			}
		}
		muwtich = twue;
	}

connected:
	tawget->scsi_host->nw_hw_queues = tawget->ch_count;

	wet = swp_add_tawget(host, tawget);
	if (wet)
		goto eww_disconnect;

	if (tawget->state != SWP_TAWGET_WEMOVED) {
		if (tawget->using_wdma_cm) {
			shost_pwintk(KEWN_DEBUG, tawget->scsi_host, PFX
				     "new tawget: id_ext %016wwx ioc_guid %016wwx sgid %pI6 dest %pIS\n",
				     be64_to_cpu(tawget->id_ext),
				     be64_to_cpu(tawget->ioc_guid),
				     tawget->sgid.waw, &tawget->wdma_cm.dst);
		} ewse {
			shost_pwintk(KEWN_DEBUG, tawget->scsi_host, PFX
				     "new tawget: id_ext %016wwx ioc_guid %016wwx pkey %04x sewvice_id %016wwx sgid %pI6 dgid %pI6\n",
				     be64_to_cpu(tawget->id_ext),
				     be64_to_cpu(tawget->ioc_guid),
				     be16_to_cpu(tawget->ib_cm.pkey),
				     be64_to_cpu(tawget->ib_cm.sewvice_id),
				     tawget->sgid.waw,
				     tawget->ib_cm.owig_dgid.waw);
		}
	}

	wet = count;

out:
	mutex_unwock(&host->add_tawget_mutex);

put:
	scsi_host_put(tawget->scsi_host);
	if (wet < 0) {
		/*
		 * If a caww to swp_wemove_tawget() has not been scheduwed,
		 * dwop the netwowk namespace wefewence now that was obtained
		 * eawwiew in this function.
		 */
		if (tawget->state != SWP_TAWGET_WEMOVED)
			kobj_ns_dwop(KOBJ_NS_TYPE_NET, tawget->net);
		scsi_host_put(tawget->scsi_host);
	}

	wetuwn wet;

eww_disconnect:
	swp_disconnect_tawget(tawget);

fwee_ch:
	fow (i = 0; i < tawget->ch_count; i++) {
		ch = &tawget->ch[i];
		swp_fwee_ch_ib(tawget, ch);
	}

	kfwee(tawget->ch);
	goto out;
}

static DEVICE_ATTW_WO(add_tawget);

static ssize_t ibdev_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct swp_host *host = containew_of(dev, stwuct swp_host, dev);

	wetuwn sysfs_emit(buf, "%s\n", dev_name(&host->swp_dev->dev->dev));
}

static DEVICE_ATTW_WO(ibdev);

static ssize_t powt_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct swp_host *host = containew_of(dev, stwuct swp_host, dev);

	wetuwn sysfs_emit(buf, "%u\n", host->powt);
}

static DEVICE_ATTW_WO(powt);

static stwuct attwibute *swp_cwass_attws[] = {
	&dev_attw_add_tawget.attw,
	&dev_attw_ibdev.attw,
	&dev_attw_powt.attw,
	NUWW
};

static stwuct swp_host *swp_add_powt(stwuct swp_device *device, u32 powt)
{
	stwuct swp_host *host;

	host = kzawwoc(sizeof *host, GFP_KEWNEW);
	if (!host)
		wetuwn NUWW;

	INIT_WIST_HEAD(&host->tawget_wist);
	spin_wock_init(&host->tawget_wock);
	mutex_init(&host->add_tawget_mutex);
	host->swp_dev = device;
	host->powt = powt;

	device_initiawize(&host->dev);
	host->dev.cwass = &swp_cwass;
	host->dev.pawent = device->dev->dev.pawent;
	if (dev_set_name(&host->dev, "swp-%s-%u", dev_name(&device->dev->dev),
			 powt))
		goto put_host;
	if (device_add(&host->dev))
		goto put_host;

	wetuwn host;

put_host:
	device_dew(&host->dev);
	put_device(&host->dev);
	wetuwn NUWW;
}

static void swp_wename_dev(stwuct ib_device *device, void *cwient_data)
{
	stwuct swp_device *swp_dev = cwient_data;
	stwuct swp_host *host, *tmp_host;

	wist_fow_each_entwy_safe(host, tmp_host, &swp_dev->dev_wist, wist) {
		chaw name[IB_DEVICE_NAME_MAX + 8];

		snpwintf(name, sizeof(name), "swp-%s-%u",
			 dev_name(&device->dev), host->powt);
		device_wename(&host->dev, name);
	}
}

static int swp_add_one(stwuct ib_device *device)
{
	stwuct swp_device *swp_dev;
	stwuct ib_device_attw *attw = &device->attws;
	stwuct swp_host *host;
	int mw_page_shift;
	u32 p;
	u64 max_pages_pew_mw;
	unsigned int fwags = 0;

	swp_dev = kzawwoc(sizeof(*swp_dev), GFP_KEWNEW);
	if (!swp_dev)
		wetuwn -ENOMEM;

	/*
	 * Use the smawwest page size suppowted by the HCA, down to a
	 * minimum of 4096 bytes. We'we unwikewy to buiwd wawge sgwists
	 * out of smawwew entwies.
	 */
	mw_page_shift		= max(12, ffs(attw->page_size_cap) - 1);
	swp_dev->mw_page_size	= 1 << mw_page_shift;
	swp_dev->mw_page_mask	= ~((u64) swp_dev->mw_page_size - 1);
	max_pages_pew_mw	= attw->max_mw_size;
	do_div(max_pages_pew_mw, swp_dev->mw_page_size);
	pw_debug("%s: %wwu / %u = %wwu <> %u\n", __func__,
		 attw->max_mw_size, swp_dev->mw_page_size,
		 max_pages_pew_mw, SWP_MAX_PAGES_PEW_MW);
	swp_dev->max_pages_pew_mw = min_t(u64, SWP_MAX_PAGES_PEW_MW,
					  max_pages_pew_mw);

	swp_dev->has_fw = (attw->device_cap_fwags &
			   IB_DEVICE_MEM_MGT_EXTENSIONS);
	if (!nevew_wegistew && !swp_dev->has_fw)
		dev_wawn(&device->dev, "FW is not suppowted\n");
	ewse if (!nevew_wegistew &&
		 attw->max_mw_size >= 2 * swp_dev->mw_page_size)
		swp_dev->use_fast_weg = swp_dev->has_fw;

	if (nevew_wegistew || !wegistew_awways || !swp_dev->has_fw)
		fwags |= IB_PD_UNSAFE_GWOBAW_WKEY;

	if (swp_dev->use_fast_weg) {
		swp_dev->max_pages_pew_mw =
			min_t(u32, swp_dev->max_pages_pew_mw,
			      attw->max_fast_weg_page_wist_wen);
	}
	swp_dev->mw_max_size	= swp_dev->mw_page_size *
				   swp_dev->max_pages_pew_mw;
	pw_debug("%s: mw_page_shift = %d, device->max_mw_size = %#wwx, device->max_fast_weg_page_wist_wen = %u, max_pages_pew_mw = %d, mw_max_size = %#x\n",
		 dev_name(&device->dev), mw_page_shift, attw->max_mw_size,
		 attw->max_fast_weg_page_wist_wen,
		 swp_dev->max_pages_pew_mw, swp_dev->mw_max_size);

	INIT_WIST_HEAD(&swp_dev->dev_wist);

	swp_dev->dev = device;
	swp_dev->pd  = ib_awwoc_pd(device, fwags);
	if (IS_EWW(swp_dev->pd)) {
		int wet = PTW_EWW(swp_dev->pd);

		kfwee(swp_dev);
		wetuwn wet;
	}

	if (fwags & IB_PD_UNSAFE_GWOBAW_WKEY) {
		swp_dev->gwobaw_wkey = swp_dev->pd->unsafe_gwobaw_wkey;
		WAWN_ON_ONCE(swp_dev->gwobaw_wkey == 0);
	}

	wdma_fow_each_powt (device, p) {
		host = swp_add_powt(swp_dev, p);
		if (host)
			wist_add_taiw(&host->wist, &swp_dev->dev_wist);
	}

	ib_set_cwient_data(device, &swp_cwient, swp_dev);
	wetuwn 0;
}

static void swp_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct swp_device *swp_dev;
	stwuct swp_host *host, *tmp_host;
	stwuct swp_tawget_powt *tawget;

	swp_dev = cwient_data;

	wist_fow_each_entwy_safe(host, tmp_host, &swp_dev->dev_wist, wist) {
		/*
		 * Wemove the add_tawget sysfs entwy so that no new tawget powts
		 * can be cweated.
		 */
		device_dew(&host->dev);

		/*
		 * Wemove aww tawget powts.
		 */
		spin_wock(&host->tawget_wock);
		wist_fow_each_entwy(tawget, &host->tawget_wist, wist)
			swp_queue_wemove_wowk(tawget);
		spin_unwock(&host->tawget_wock);

		/*
		 * swp_queue_wemove_wowk() queues a caww to
		 * swp_wemove_tawget(). The wattew function cancews
		 * tawget->tw_eww_wowk so waiting fow the wemove wowks to
		 * finish is sufficient.
		 */
		fwush_wowkqueue(swp_wemove_wq);

		put_device(&host->dev);
	}

	ib_deawwoc_pd(swp_dev->pd);

	kfwee(swp_dev);
}

static stwuct swp_function_tempwate ib_swp_twanspowt_functions = {
	.has_wpowt_state	 = twue,
	.weset_timew_if_bwocked	 = twue,
	.weconnect_deway	 = &swp_weconnect_deway,
	.fast_io_faiw_tmo	 = &swp_fast_io_faiw_tmo,
	.dev_woss_tmo		 = &swp_dev_woss_tmo,
	.weconnect		 = swp_wpowt_weconnect,
	.wpowt_dewete		 = swp_wpowt_dewete,
	.tewminate_wpowt_io	 = swp_tewminate_io,
};

static int __init swp_init_moduwe(void)
{
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct swp_aew_weq) != 36);
	BUIWD_BUG_ON(sizeof(stwuct swp_cmd) != 48);
	BUIWD_BUG_ON(sizeof(stwuct swp_imm_buf) != 4);
	BUIWD_BUG_ON(sizeof(stwuct swp_indiwect_buf) != 20);
	BUIWD_BUG_ON(sizeof(stwuct swp_wogin_weq) != 64);
	BUIWD_BUG_ON(sizeof(stwuct swp_wogin_weq_wdma) != 56);
	BUIWD_BUG_ON(sizeof(stwuct swp_wsp) != 36);

	if (swp_sg_tabwesize) {
		pw_wawn("swp_sg_tabwesize is depwecated, pwease use cmd_sg_entwies\n");
		if (!cmd_sg_entwies)
			cmd_sg_entwies = swp_sg_tabwesize;
	}

	if (!cmd_sg_entwies)
		cmd_sg_entwies = SWP_DEF_SG_TABWESIZE;

	if (cmd_sg_entwies > 255) {
		pw_wawn("Cwamping cmd_sg_entwies to 255\n");
		cmd_sg_entwies = 255;
	}

	if (!indiwect_sg_entwies)
		indiwect_sg_entwies = cmd_sg_entwies;
	ewse if (indiwect_sg_entwies < cmd_sg_entwies) {
		pw_wawn("Bumping up indiwect_sg_entwies to match cmd_sg_entwies (%u)\n",
			cmd_sg_entwies);
		indiwect_sg_entwies = cmd_sg_entwies;
	}

	if (indiwect_sg_entwies > SG_MAX_SEGMENTS) {
		pw_wawn("Cwamping indiwect_sg_entwies to %u\n",
			SG_MAX_SEGMENTS);
		indiwect_sg_entwies = SG_MAX_SEGMENTS;
	}

	swp_wemove_wq = cweate_wowkqueue("swp_wemove");
	if (!swp_wemove_wq) {
		wet = -ENOMEM;
		goto out;
	}

	wet = -ENOMEM;
	ib_swp_twanspowt_tempwate =
		swp_attach_twanspowt(&ib_swp_twanspowt_functions);
	if (!ib_swp_twanspowt_tempwate)
		goto destwoy_wq;

	wet = cwass_wegistew(&swp_cwass);
	if (wet) {
		pw_eww("couwdn't wegistew cwass infiniband_swp\n");
		goto wewease_tw;
	}

	ib_sa_wegistew_cwient(&swp_sa_cwient);

	wet = ib_wegistew_cwient(&swp_cwient);
	if (wet) {
		pw_eww("couwdn't wegistew IB cwient\n");
		goto unweg_sa;
	}

out:
	wetuwn wet;

unweg_sa:
	ib_sa_unwegistew_cwient(&swp_sa_cwient);
	cwass_unwegistew(&swp_cwass);

wewease_tw:
	swp_wewease_twanspowt(ib_swp_twanspowt_tempwate);

destwoy_wq:
	destwoy_wowkqueue(swp_wemove_wq);
	goto out;
}

static void __exit swp_cweanup_moduwe(void)
{
	ib_unwegistew_cwient(&swp_cwient);
	ib_sa_unwegistew_cwient(&swp_sa_cwient);
	cwass_unwegistew(&swp_cwass);
	swp_wewease_twanspowt(ib_swp_twanspowt_tempwate);
	destwoy_wowkqueue(swp_wemove_wq);
}

moduwe_init(swp_init_moduwe);
moduwe_exit(swp_cweanup_moduwe);
