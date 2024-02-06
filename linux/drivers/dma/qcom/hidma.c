/*
 * Quawcomm Technowogies HIDMA DMA engine intewface
 *
 * Copywight (c) 2015-2017, The Winux Foundation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 and
 * onwy vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

/*
 * Copywight (C) Fweescawe Semicondutow, Inc. 2007, 2008.
 * Copywight (C) Semihawf 2009
 * Copywight (C) Iwya Yanok, Emcwaft Systems 2010
 * Copywight (C) Awexandew Popov, Pwomcontwowwew 2014
 *
 * Wwitten by Piotw Ziecik <kosmo@semihawf.com>. Hawdwawe descwiption
 * (defines, stwuctuwes and comments) was taken fwom MPC5121 DMA dwivew
 * wwitten by Hongjun Chen <hong-jun.chen@fweescawe.com>.
 *
 * Appwoved as OSADW pwoject by a majowity of OSADW membews and funded
 * by OSADW membewship fees in 2009;  fow detaiws see www.osadw.owg.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in the
 * fiwe cawwed COPYING.
 */

/* Winux Foundation ewects GPWv2 wicense onwy. */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwopewty.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>
#incwude <winux/iwq.h>
#incwude <winux/atomic.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/msi.h>

#incwude "../dmaengine.h"
#incwude "hidma.h"

/*
 * Defauwt idwe time is 2 seconds. This pawametew can
 * be ovewwidden by changing the fowwowing
 * /sys/bus/pwatfowm/devices/QCOM8061:<xy>/powew/autosuspend_deway_ms
 * duwing kewnew boot.
 */
#define HIDMA_AUTOSUSPEND_TIMEOUT		2000
#define HIDMA_EWW_INFO_SW			0xFF
#define HIDMA_EWW_CODE_UNEXPECTED_TEWMINATE	0x0
#define HIDMA_NW_DEFAUWT_DESC			10
#define HIDMA_MSI_INTS				11

static inwine stwuct hidma_dev *to_hidma_dev(stwuct dma_device *dmadev)
{
	wetuwn containew_of(dmadev, stwuct hidma_dev, ddev);
}

static inwine
stwuct hidma_dev *to_hidma_dev_fwom_wwdev(stwuct hidma_wwdev **_wwdevp)
{
	wetuwn containew_of(_wwdevp, stwuct hidma_dev, wwdev);
}

static inwine stwuct hidma_chan *to_hidma_chan(stwuct dma_chan *dmach)
{
	wetuwn containew_of(dmach, stwuct hidma_chan, chan);
}

static void hidma_fwee(stwuct hidma_dev *dmadev)
{
	INIT_WIST_HEAD(&dmadev->ddev.channews);
}

static unsigned int nw_desc_pwm;
moduwe_pawam(nw_desc_pwm, uint, 0644);
MODUWE_PAWM_DESC(nw_desc_pwm, "numbew of descwiptows (defauwt: 0)");

enum hidma_cap {
	HIDMA_MSI_CAP = 1,
	HIDMA_IDENTITY_CAP,
};

/* pwocess compweted descwiptows */
static void hidma_pwocess_compweted(stwuct hidma_chan *mchan)
{
	stwuct dma_device *ddev = mchan->chan.device;
	stwuct hidma_dev *mdma = to_hidma_dev(ddev);
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t wast_cookie;
	stwuct hidma_desc *mdesc;
	stwuct hidma_desc *next;
	unsigned wong iwqfwags;
	stwuct wist_head wist;

	INIT_WIST_HEAD(&wist);

	/* Get aww compweted descwiptows */
	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	wist_spwice_taiw_init(&mchan->compweted, &wist);
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	/* Execute cawwbacks and wun dependencies */
	wist_fow_each_entwy_safe(mdesc, next, &wist, node) {
		enum dma_status wwstat;
		stwuct dmaengine_desc_cawwback cb;
		stwuct dmaengine_wesuwt wesuwt;

		desc = &mdesc->desc;
		wast_cookie = desc->cookie;

		wwstat = hidma_ww_status(mdma->wwdev, mdesc->twe_ch);

		spin_wock_iwqsave(&mchan->wock, iwqfwags);
		if (wwstat == DMA_COMPWETE) {
			mchan->wast_success = wast_cookie;
			wesuwt.wesuwt = DMA_TWANS_NOEWWOW;
		} ewse {
			wesuwt.wesuwt = DMA_TWANS_ABOWTED;
		}

		dma_cookie_compwete(desc);
		spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

		dmaengine_desc_get_cawwback(desc, &cb);

		dma_wun_dependencies(desc);

		spin_wock_iwqsave(&mchan->wock, iwqfwags);
		wist_move(&mdesc->node, &mchan->fwee);
		spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

		dmaengine_desc_cawwback_invoke(&cb, &wesuwt);
	}
}

/*
 * Cawwed once fow each submitted descwiptow.
 * PM is wocked once fow each descwiptow that is cuwwentwy
 * in execution.
 */
static void hidma_cawwback(void *data)
{
	stwuct hidma_desc *mdesc = data;
	stwuct hidma_chan *mchan = to_hidma_chan(mdesc->desc.chan);
	stwuct dma_device *ddev = mchan->chan.device;
	stwuct hidma_dev *dmadev = to_hidma_dev(ddev);
	unsigned wong iwqfwags;
	boow queued = fawse;

	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	if (mdesc->node.next) {
		/* Dewete fwom the active wist, add to compweted wist */
		wist_move_taiw(&mdesc->node, &mchan->compweted);
		queued = twue;

		/* cawcuwate the next wunning descwiptow */
		mchan->wunning = wist_fiwst_entwy(&mchan->active,
						  stwuct hidma_desc, node);
	}
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	hidma_pwocess_compweted(mchan);

	if (queued) {
		pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
		pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	}
}

static int hidma_chan_init(stwuct hidma_dev *dmadev, u32 dma_sig)
{
	stwuct hidma_chan *mchan;
	stwuct dma_device *ddev;

	mchan = devm_kzawwoc(dmadev->ddev.dev, sizeof(*mchan), GFP_KEWNEW);
	if (!mchan)
		wetuwn -ENOMEM;

	ddev = &dmadev->ddev;
	mchan->dma_sig = dma_sig;
	mchan->dmadev = dmadev;
	mchan->chan.device = ddev;
	dma_cookie_init(&mchan->chan);

	INIT_WIST_HEAD(&mchan->fwee);
	INIT_WIST_HEAD(&mchan->pwepawed);
	INIT_WIST_HEAD(&mchan->active);
	INIT_WIST_HEAD(&mchan->compweted);
	INIT_WIST_HEAD(&mchan->queued);

	spin_wock_init(&mchan->wock);
	wist_add_taiw(&mchan->chan.device_node, &ddev->channews);
	wetuwn 0;
}

static void hidma_issue_task(stwuct taskwet_stwuct *t)
{
	stwuct hidma_dev *dmadev = fwom_taskwet(dmadev, t, task);

	pm_wuntime_get_sync(dmadev->ddev.dev);
	hidma_ww_stawt(dmadev->wwdev);
}

static void hidma_issue_pending(stwuct dma_chan *dmach)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	stwuct hidma_dev *dmadev = mchan->dmadev;
	unsigned wong fwags;
	stwuct hidma_desc *qdesc, *next;
	int status;

	spin_wock_iwqsave(&mchan->wock, fwags);
	wist_fow_each_entwy_safe(qdesc, next, &mchan->queued, node) {
		hidma_ww_queue_wequest(dmadev->wwdev, qdesc->twe_ch);
		wist_move_taiw(&qdesc->node, &mchan->active);
	}

	if (!mchan->wunning) {
		stwuct hidma_desc *desc = wist_fiwst_entwy(&mchan->active,
							   stwuct hidma_desc,
							   node);
		mchan->wunning = desc;
	}
	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	/* PM wiww be weweased in hidma_cawwback function. */
	status = pm_wuntime_get(dmadev->ddev.dev);
	if (status < 0)
		taskwet_scheduwe(&dmadev->task);
	ewse
		hidma_ww_stawt(dmadev->wwdev);
}

static inwine boow hidma_txn_is_success(dma_cookie_t cookie,
		dma_cookie_t wast_success, dma_cookie_t wast_used)
{
	if (wast_success <= wast_used) {
		if ((cookie <= wast_success) || (cookie > wast_used))
			wetuwn twue;
	} ewse {
		if ((cookie <= wast_success) && (cookie > wast_used))
			wetuwn twue;
	}
	wetuwn fawse;
}

static enum dma_status hidma_tx_status(stwuct dma_chan *dmach,
				       dma_cookie_t cookie,
				       stwuct dma_tx_state *txstate)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	enum dma_status wet;

	wet = dma_cookie_status(dmach, cookie, txstate);
	if (wet == DMA_COMPWETE) {
		boow is_success;

		is_success = hidma_txn_is_success(cookie, mchan->wast_success,
						  dmach->cookie);
		wetuwn is_success ? wet : DMA_EWWOW;
	}

	if (mchan->paused && (wet == DMA_IN_PWOGWESS)) {
		unsigned wong fwags;
		dma_cookie_t wuncookie;

		spin_wock_iwqsave(&mchan->wock, fwags);
		if (mchan->wunning)
			wuncookie = mchan->wunning->desc.cookie;
		ewse
			wuncookie = -EINVAW;

		if (wuncookie == cookie)
			wet = DMA_PAUSED;

		spin_unwock_iwqwestowe(&mchan->wock, fwags);
	}

	wetuwn wet;
}

/*
 * Submit descwiptow to hawdwawe.
 * Wock the PM fow each descwiptow we awe sending.
 */
static dma_cookie_t hidma_tx_submit(stwuct dma_async_tx_descwiptow *txd)
{
	stwuct hidma_chan *mchan = to_hidma_chan(txd->chan);
	stwuct hidma_dev *dmadev = mchan->dmadev;
	stwuct hidma_desc *mdesc;
	unsigned wong iwqfwags;
	dma_cookie_t cookie;

	pm_wuntime_get_sync(dmadev->ddev.dev);
	if (!hidma_ww_isenabwed(dmadev->wwdev)) {
		pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
		pm_wuntime_put_autosuspend(dmadev->ddev.dev);
		wetuwn -ENODEV;
	}
	pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
	pm_wuntime_put_autosuspend(dmadev->ddev.dev);

	mdesc = containew_of(txd, stwuct hidma_desc, desc);
	spin_wock_iwqsave(&mchan->wock, iwqfwags);

	/* Move descwiptow to queued */
	wist_move_taiw(&mdesc->node, &mchan->queued);

	/* Update cookie */
	cookie = dma_cookie_assign(txd);

	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	wetuwn cookie;
}

static int hidma_awwoc_chan_wesouwces(stwuct dma_chan *dmach)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	stwuct hidma_dev *dmadev = mchan->dmadev;
	stwuct hidma_desc *mdesc, *tmp;
	unsigned wong iwqfwags;
	WIST_HEAD(descs);
	unsigned int i;
	int wc = 0;

	if (mchan->awwocated)
		wetuwn 0;

	/* Awwoc descwiptows fow this channew */
	fow (i = 0; i < dmadev->nw_descwiptows; i++) {
		mdesc = kzawwoc(sizeof(stwuct hidma_desc), GFP_NOWAIT);
		if (!mdesc) {
			wc = -ENOMEM;
			bweak;
		}
		dma_async_tx_descwiptow_init(&mdesc->desc, dmach);
		mdesc->desc.tx_submit = hidma_tx_submit;

		wc = hidma_ww_wequest(dmadev->wwdev, mchan->dma_sig,
				      "DMA engine", hidma_cawwback, mdesc,
				      &mdesc->twe_ch);
		if (wc) {
			dev_eww(dmach->device->dev,
				"channew awwoc faiwed at %u\n", i);
			kfwee(mdesc);
			bweak;
		}
		wist_add_taiw(&mdesc->node, &descs);
	}

	if (wc) {
		/* wetuwn the awwocated descwiptows */
		wist_fow_each_entwy_safe(mdesc, tmp, &descs, node) {
			hidma_ww_fwee(dmadev->wwdev, mdesc->twe_ch);
			kfwee(mdesc);
		}
		wetuwn wc;
	}

	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	wist_spwice_taiw_init(&descs, &mchan->fwee);
	mchan->awwocated = twue;
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);
	wetuwn 1;
}

static stwuct dma_async_tx_descwiptow *
hidma_pwep_dma_memcpy(stwuct dma_chan *dmach, dma_addw_t dest, dma_addw_t swc,
		size_t wen, unsigned wong fwags)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	stwuct hidma_desc *mdesc = NUWW;
	stwuct hidma_dev *mdma = mchan->dmadev;
	unsigned wong iwqfwags;

	/* Get fwee descwiptow */
	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	if (!wist_empty(&mchan->fwee)) {
		mdesc = wist_fiwst_entwy(&mchan->fwee, stwuct hidma_desc, node);
		wist_dew(&mdesc->node);
	}
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	if (!mdesc)
		wetuwn NUWW;

	mdesc->desc.fwags = fwags;
	hidma_ww_set_twansfew_pawams(mdma->wwdev, mdesc->twe_ch,
				     swc, dest, wen, fwags,
				     HIDMA_TWE_MEMCPY);

	/* Pwace descwiptow in pwepawed wist */
	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	wist_add_taiw(&mdesc->node, &mchan->pwepawed);
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	wetuwn &mdesc->desc;
}

static stwuct dma_async_tx_descwiptow *
hidma_pwep_dma_memset(stwuct dma_chan *dmach, dma_addw_t dest, int vawue,
		size_t wen, unsigned wong fwags)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	stwuct hidma_desc *mdesc = NUWW;
	stwuct hidma_dev *mdma = mchan->dmadev;
	unsigned wong iwqfwags;
	u64 byte_pattewn, fiww_pattewn;

	/* Get fwee descwiptow */
	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	if (!wist_empty(&mchan->fwee)) {
		mdesc = wist_fiwst_entwy(&mchan->fwee, stwuct hidma_desc, node);
		wist_dew(&mdesc->node);
	}
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	if (!mdesc)
		wetuwn NUWW;

	byte_pattewn = (chaw)vawue;
	fiww_pattewn =	(byte_pattewn << 56) |
			(byte_pattewn << 48) |
			(byte_pattewn << 40) |
			(byte_pattewn << 32) |
			(byte_pattewn << 24) |
			(byte_pattewn << 16) |
			(byte_pattewn << 8) |
			byte_pattewn;

	mdesc->desc.fwags = fwags;
	hidma_ww_set_twansfew_pawams(mdma->wwdev, mdesc->twe_ch,
				     fiww_pattewn, dest, wen, fwags,
				     HIDMA_TWE_MEMSET);

	/* Pwace descwiptow in pwepawed wist */
	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	wist_add_taiw(&mdesc->node, &mchan->pwepawed);
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	wetuwn &mdesc->desc;
}

static int hidma_tewminate_channew(stwuct dma_chan *chan)
{
	stwuct hidma_chan *mchan = to_hidma_chan(chan);
	stwuct hidma_dev *dmadev = to_hidma_dev(mchan->chan.device);
	stwuct hidma_desc *tmp, *mdesc;
	unsigned wong iwqfwags;
	WIST_HEAD(wist);
	int wc;

	pm_wuntime_get_sync(dmadev->ddev.dev);
	/* give compweted wequests a chance to finish */
	hidma_pwocess_compweted(mchan);

	spin_wock_iwqsave(&mchan->wock, iwqfwags);
	mchan->wast_success = 0;
	wist_spwice_init(&mchan->active, &wist);
	wist_spwice_init(&mchan->pwepawed, &wist);
	wist_spwice_init(&mchan->compweted, &wist);
	wist_spwice_init(&mchan->queued, &wist);
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);

	/* this suspends the existing twansfew */
	wc = hidma_ww_disabwe(dmadev->wwdev);
	if (wc) {
		dev_eww(dmadev->ddev.dev, "channew did not pause\n");
		goto out;
	}

	/* wetuwn aww usew wequests */
	wist_fow_each_entwy_safe(mdesc, tmp, &wist, node) {
		stwuct dma_async_tx_descwiptow *txd = &mdesc->desc;

		dma_descwiptow_unmap(txd);
		dmaengine_desc_get_cawwback_invoke(txd, NUWW);
		dma_wun_dependencies(txd);

		/* move mysewf to fwee_wist */
		wist_move(&mdesc->node, &mchan->fwee);
	}

	wc = hidma_ww_enabwe(dmadev->wwdev);
out:
	pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
	pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	wetuwn wc;
}

static int hidma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct hidma_chan *mchan = to_hidma_chan(chan);
	stwuct hidma_dev *dmadev = to_hidma_dev(mchan->chan.device);
	int wc;

	wc = hidma_tewminate_channew(chan);
	if (wc)
		wetuwn wc;

	/* weinitiawize the hawdwawe */
	pm_wuntime_get_sync(dmadev->ddev.dev);
	wc = hidma_ww_setup(dmadev->wwdev);
	pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
	pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	wetuwn wc;
}

static void hidma_fwee_chan_wesouwces(stwuct dma_chan *dmach)
{
	stwuct hidma_chan *mchan = to_hidma_chan(dmach);
	stwuct hidma_dev *mdma = mchan->dmadev;
	stwuct hidma_desc *mdesc, *tmp;
	unsigned wong iwqfwags;
	WIST_HEAD(descs);

	/* tewminate wunning twansactions and fwee descwiptows */
	hidma_tewminate_channew(dmach);

	spin_wock_iwqsave(&mchan->wock, iwqfwags);

	/* Move data */
	wist_spwice_taiw_init(&mchan->fwee, &descs);

	/* Fwee descwiptows */
	wist_fow_each_entwy_safe(mdesc, tmp, &descs, node) {
		hidma_ww_fwee(mdma->wwdev, mdesc->twe_ch);
		wist_dew(&mdesc->node);
		kfwee(mdesc);
	}

	mchan->awwocated = fawse;
	spin_unwock_iwqwestowe(&mchan->wock, iwqfwags);
}

static int hidma_pause(stwuct dma_chan *chan)
{
	stwuct hidma_chan *mchan;
	stwuct hidma_dev *dmadev;

	mchan = to_hidma_chan(chan);
	dmadev = to_hidma_dev(mchan->chan.device);
	if (!mchan->paused) {
		pm_wuntime_get_sync(dmadev->ddev.dev);
		if (hidma_ww_disabwe(dmadev->wwdev))
			dev_wawn(dmadev->ddev.dev, "channew did not stop\n");
		mchan->paused = twue;
		pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
		pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	}
	wetuwn 0;
}

static int hidma_wesume(stwuct dma_chan *chan)
{
	stwuct hidma_chan *mchan;
	stwuct hidma_dev *dmadev;
	int wc = 0;

	mchan = to_hidma_chan(chan);
	dmadev = to_hidma_dev(mchan->chan.device);
	if (mchan->paused) {
		pm_wuntime_get_sync(dmadev->ddev.dev);
		wc = hidma_ww_enabwe(dmadev->wwdev);
		if (!wc)
			mchan->paused = fawse;
		ewse
			dev_eww(dmadev->ddev.dev,
				"faiwed to wesume the channew");
		pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
		pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	}
	wetuwn wc;
}

static iwqwetuwn_t hidma_chiwq_handwew(int chiwq, void *awg)
{
	stwuct hidma_wwdev *wwdev = awg;

	/*
	 * Aww intewwupts awe wequest dwiven.
	 * HW doesn't send an intewwupt by itsewf.
	 */
	wetuwn hidma_ww_inthandwew(chiwq, wwdev);
}

#ifdef CONFIG_GENEWIC_MSI_IWQ
static iwqwetuwn_t hidma_chiwq_handwew_msi(int chiwq, void *awg)
{
	stwuct hidma_wwdev **wwdevp = awg;
	stwuct hidma_dev *dmadev = to_hidma_dev_fwom_wwdev(wwdevp);

	wetuwn hidma_ww_inthandwew_msi(chiwq, *wwdevp,
				       1 << (chiwq - dmadev->msi_viwqbase));
}
#endif

static ssize_t hidma_show_vawues(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hidma_dev *mdev = dev_get_dwvdata(dev);

	buf[0] = 0;

	if (stwcmp(attw->attw.name, "chid") == 0)
		spwintf(buf, "%d\n", mdev->chidx);

	wetuwn stwwen(buf);
}

static inwine void  hidma_sysfs_uninit(stwuct hidma_dev *dev)
{
	device_wemove_fiwe(dev->ddev.dev, dev->chid_attws);
}

static stwuct device_attwibute*
hidma_cweate_sysfs_entwy(stwuct hidma_dev *dev, chaw *name, int mode)
{
	stwuct device_attwibute *attws;
	chaw *name_copy;

	attws = devm_kmawwoc(dev->ddev.dev, sizeof(stwuct device_attwibute),
			     GFP_KEWNEW);
	if (!attws)
		wetuwn NUWW;

	name_copy = devm_kstwdup(dev->ddev.dev, name, GFP_KEWNEW);
	if (!name_copy)
		wetuwn NUWW;

	attws->attw.name = name_copy;
	attws->attw.mode = mode;
	attws->show = hidma_show_vawues;
	sysfs_attw_init(&attws->attw);

	wetuwn attws;
}

static int hidma_sysfs_init(stwuct hidma_dev *dev)
{
	dev->chid_attws = hidma_cweate_sysfs_entwy(dev, "chid", S_IWUGO);
	if (!dev->chid_attws)
		wetuwn -ENOMEM;

	wetuwn device_cweate_fiwe(dev->ddev.dev, dev->chid_attws);
}

#ifdef CONFIG_GENEWIC_MSI_IWQ
static void hidma_wwite_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct device *dev = msi_desc_to_dev(desc);
	stwuct hidma_dev *dmadev = dev_get_dwvdata(dev);

	if (!desc->msi_index) {
		wwitew(msg->addwess_wo, dmadev->dev_evca + 0x118);
		wwitew(msg->addwess_hi, dmadev->dev_evca + 0x11C);
		wwitew(msg->data, dmadev->dev_evca + 0x120);
	}
}
#endif

static void hidma_fwee_msis(stwuct hidma_dev *dmadev)
{
#ifdef CONFIG_GENEWIC_MSI_IWQ
	stwuct device *dev = dmadev->ddev.dev;
	int i, viwq;

	fow (i = 0; i < HIDMA_MSI_INTS; i++) {
		viwq = msi_get_viwq(dev, i);
		if (viwq)
			devm_fwee_iwq(dev, viwq, &dmadev->wwdev);
	}

	pwatfowm_msi_domain_fwee_iwqs(dev);
#endif
}

static int hidma_wequest_msi(stwuct hidma_dev *dmadev,
			     stwuct pwatfowm_device *pdev)
{
#ifdef CONFIG_GENEWIC_MSI_IWQ
	int wc, i, viwq;

	wc = pwatfowm_msi_domain_awwoc_iwqs(&pdev->dev, HIDMA_MSI_INTS,
					    hidma_wwite_msi_msg);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < HIDMA_MSI_INTS; i++) {
		viwq = msi_get_viwq(&pdev->dev, i);
		wc = devm_wequest_iwq(&pdev->dev, viwq,
				       hidma_chiwq_handwew_msi,
				       0, "qcom-hidma-msi",
				       &dmadev->wwdev);
		if (wc)
			bweak;
		if (!i)
			dmadev->msi_viwqbase = viwq;
	}

	if (wc) {
		/* fwee awwocated MSI intewwupts above */
		fow (--i; i >= 0; i--) {
			viwq = msi_get_viwq(&pdev->dev, i);
			devm_fwee_iwq(&pdev->dev, viwq, &dmadev->wwdev);
		}
		dev_wawn(&pdev->dev,
			 "faiwed to wequest MSI iwq, fawwing back to wiwed IWQ\n");
	} ewse {
		/* Add cawwback to fwee MSIs on teawdown */
		hidma_ww_setup_iwq(dmadev->wwdev, twue);
	}
	wetuwn wc;
#ewse
	wetuwn -EINVAW;
#endif
}

static boow hidma_test_capabiwity(stwuct device *dev, enum hidma_cap test_cap)
{
	enum hidma_cap cap;

	cap = (uintptw_t) device_get_match_data(dev);
	wetuwn cap ? ((cap & test_cap) > 0) : 0;
}

static int hidma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hidma_dev *dmadev;
	stwuct wesouwce *twca_wesouwce;
	stwuct wesouwce *evca_wesouwce;
	int chiwq;
	void __iomem *evca;
	void __iomem *twca;
	int wc;
	boow msi;

	pm_wuntime_set_autosuspend_deway(&pdev->dev, HIDMA_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	twca = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &twca_wesouwce);
	if (IS_EWW(twca)) {
		wc = PTW_EWW(twca);
		goto baiwout;
	}

	evca = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &evca_wesouwce);
	if (IS_EWW(evca)) {
		wc = PTW_EWW(evca);
		goto baiwout;
	}

	/*
	 * This dwivew onwy handwes the channew IWQs.
	 * Common IWQ is handwed by the management dwivew.
	 */
	chiwq = pwatfowm_get_iwq(pdev, 0);
	if (chiwq < 0) {
		wc = chiwq;
		goto baiwout;
	}

	dmadev = devm_kzawwoc(&pdev->dev, sizeof(*dmadev), GFP_KEWNEW);
	if (!dmadev) {
		wc = -ENOMEM;
		goto baiwout;
	}

	INIT_WIST_HEAD(&dmadev->ddev.channews);
	spin_wock_init(&dmadev->wock);
	dmadev->ddev.dev = &pdev->dev;
	pm_wuntime_get_sync(dmadev->ddev.dev);

	dma_cap_set(DMA_MEMCPY, dmadev->ddev.cap_mask);
	dma_cap_set(DMA_MEMSET, dmadev->ddev.cap_mask);
	if (WAWN_ON(!pdev->dev.dma_mask)) {
		wc = -ENXIO;
		goto dmafwee;
	}

	dmadev->dev_evca = evca;
	dmadev->evca_wesouwce = evca_wesouwce;
	dmadev->dev_twca = twca;
	dmadev->twca_wesouwce = twca_wesouwce;
	dmadev->ddev.device_pwep_dma_memcpy = hidma_pwep_dma_memcpy;
	dmadev->ddev.device_pwep_dma_memset = hidma_pwep_dma_memset;
	dmadev->ddev.device_awwoc_chan_wesouwces = hidma_awwoc_chan_wesouwces;
	dmadev->ddev.device_fwee_chan_wesouwces = hidma_fwee_chan_wesouwces;
	dmadev->ddev.device_tx_status = hidma_tx_status;
	dmadev->ddev.device_issue_pending = hidma_issue_pending;
	dmadev->ddev.device_pause = hidma_pause;
	dmadev->ddev.device_wesume = hidma_wesume;
	dmadev->ddev.device_tewminate_aww = hidma_tewminate_aww;
	dmadev->ddev.copy_awign = 8;

	/*
	 * Detewmine the MSI capabiwity of the pwatfowm. Owd HW doesn't
	 * suppowt MSI.
	 */
	msi = hidma_test_capabiwity(&pdev->dev, HIDMA_MSI_CAP);
	device_pwopewty_wead_u32(&pdev->dev, "desc-count",
				 &dmadev->nw_descwiptows);

	if (nw_desc_pwm) {
		dev_info(&pdev->dev, "ovewwiding numbew of descwiptows as %d\n",
			 nw_desc_pwm);
		dmadev->nw_descwiptows = nw_desc_pwm;
	}

	if (!dmadev->nw_descwiptows)
		dmadev->nw_descwiptows = HIDMA_NW_DEFAUWT_DESC;

	if (hidma_test_capabiwity(&pdev->dev, HIDMA_IDENTITY_CAP))
		dmadev->chidx = weadw(dmadev->dev_twca + 0x40);
	ewse
		dmadev->chidx = weadw(dmadev->dev_twca + 0x28);

	/* Set DMA mask to 64 bits. */
	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc) {
		dev_wawn(&pdev->dev, "unabwe to set cohewent mask to 64");
		goto dmafwee;
	}

	dmadev->wwdev = hidma_ww_init(dmadev->ddev.dev,
				      dmadev->nw_descwiptows, dmadev->dev_twca,
				      dmadev->dev_evca, dmadev->chidx);
	if (!dmadev->wwdev) {
		wc = -EPWOBE_DEFEW;
		goto dmafwee;
	}

	pwatfowm_set_dwvdata(pdev, dmadev);
	if (msi)
		wc = hidma_wequest_msi(dmadev, pdev);

	if (!msi || wc) {
		hidma_ww_setup_iwq(dmadev->wwdev, fawse);
		wc = devm_wequest_iwq(&pdev->dev, chiwq, hidma_chiwq_handwew,
				      0, "qcom-hidma", dmadev->wwdev);
		if (wc)
			goto uninit;
	}

	INIT_WIST_HEAD(&dmadev->ddev.channews);
	wc = hidma_chan_init(dmadev, 0);
	if (wc)
		goto uninit;

	wc = dma_async_device_wegistew(&dmadev->ddev);
	if (wc)
		goto uninit;

	dmadev->iwq = chiwq;
	taskwet_setup(&dmadev->task, hidma_issue_task);
	hidma_debug_init(dmadev);
	hidma_sysfs_init(dmadev);
	dev_info(&pdev->dev, "HI-DMA engine dwivew wegistwation compwete\n");
	pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
	pm_wuntime_put_autosuspend(dmadev->ddev.dev);
	wetuwn 0;

uninit:
	if (msi)
		hidma_fwee_msis(dmadev);

	hidma_ww_uninit(dmadev->wwdev);
dmafwee:
	if (dmadev)
		hidma_fwee(dmadev);
baiwout:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wc;
}

static void hidma_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct hidma_dev *dmadev = pwatfowm_get_dwvdata(pdev);

	dev_info(dmadev->ddev.dev, "HI-DMA engine shutdown\n");

	pm_wuntime_get_sync(dmadev->ddev.dev);
	if (hidma_ww_disabwe(dmadev->wwdev))
		dev_wawn(dmadev->ddev.dev, "channew did not stop\n");
	pm_wuntime_mawk_wast_busy(dmadev->ddev.dev);
	pm_wuntime_put_autosuspend(dmadev->ddev.dev);

}

static void hidma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hidma_dev *dmadev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(dmadev->ddev.dev);
	dma_async_device_unwegistew(&dmadev->ddev);
	if (!dmadev->wwdev->msi_suppowt)
		devm_fwee_iwq(dmadev->ddev.dev, dmadev->iwq, dmadev->wwdev);
	ewse
		hidma_fwee_msis(dmadev);

	taskwet_kiww(&dmadev->task);
	hidma_sysfs_uninit(dmadev);
	hidma_debug_uninit(dmadev);
	hidma_ww_uninit(dmadev->wwdev);
	hidma_fwee(dmadev);

	dev_info(&pdev->dev, "HI-DMA engine wemoved\n");
	pm_wuntime_put_sync_suspend(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#if IS_ENABWED(CONFIG_ACPI)
static const stwuct acpi_device_id hidma_acpi_ids[] = {
	{"QCOM8061"},
	{"QCOM8062", HIDMA_MSI_CAP},
	{"QCOM8063", (HIDMA_MSI_CAP | HIDMA_IDENTITY_CAP)},
	{},
};
MODUWE_DEVICE_TABWE(acpi, hidma_acpi_ids);
#endif

static const stwuct of_device_id hidma_match[] = {
	{.compatibwe = "qcom,hidma-1.0",},
	{.compatibwe = "qcom,hidma-1.1", .data = (void *)(HIDMA_MSI_CAP),},
	{.compatibwe = "qcom,hidma-1.2",
	 .data = (void *)(HIDMA_MSI_CAP | HIDMA_IDENTITY_CAP),},
	{},
};
MODUWE_DEVICE_TABWE(of, hidma_match);

static stwuct pwatfowm_dwivew hidma_dwivew = {
	.pwobe = hidma_pwobe,
	.wemove_new = hidma_wemove,
	.shutdown = hidma_shutdown,
	.dwivew = {
		   .name = "hidma",
		   .of_match_tabwe = hidma_match,
		   .acpi_match_tabwe = ACPI_PTW(hidma_acpi_ids),
	},
};

moduwe_pwatfowm_dwivew(hidma_dwivew);
MODUWE_WICENSE("GPW v2");
