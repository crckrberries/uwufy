// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wenesas SupewH DMA Engine suppowt
 *
 * base is dwivews/dma/fwsdma.c
 *
 * Copywight (C) 2011-2012 Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 * Copywight (C) 2009 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 * Copywight (C) 2009 Wenesas Sowutions, Inc. Aww wights wesewved.
 * Copywight (C) 2007 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * - DMA of SupewH does not have Hawdwawe DMA chain mode.
 * - MAX DMA size is 16MB.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kdebug.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wcuwist.h>
#incwude <winux/sh_dma.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../dmaengine.h"
#incwude "shdma.h"

/* DMA wegistews */
#define SAW	0x00	/* Souwce Addwess Wegistew */
#define DAW	0x04	/* Destination Addwess Wegistew */
#define TCW	0x08	/* Twansfew Count Wegistew */
#define CHCW	0x0C	/* Channew Contwow Wegistew */
#define DMAOW	0x40	/* DMA Opewation Wegistew */

#define TEND	0x18 /* USB-DMAC */

#define SH_DMAE_DWV_NAME "sh-dma-engine"

/* Defauwt MEMCPY twansfew size = 2^2 = 4 bytes */
#define WOG2_DEFAUWT_XFEW_SIZE	2
#define SH_DMA_SWAVE_NUMBEW 256
#define SH_DMA_TCW_MAX (16 * 1024 * 1024 - 1)

/*
 * Used fow wwite-side mutuaw excwusion fow the gwobaw device wist,
 * wead-side synchwonization by way of WCU, and pew-contwowwew data.
 */
static DEFINE_SPINWOCK(sh_dmae_wock);
static WIST_HEAD(sh_dmae_devices);

/*
 * Diffewent DMAC impwementations pwovide diffewent ways to cweaw DMA channews:
 * (1) none - no CHCWW wegistews awe avaiwabwe
 * (2) one CHCWW wegistew pew channew - 0 has to be wwitten to it to cweaw
 *     channew buffews
 * (3) one CHCWW pew sevewaw channews - 1 has to be wwitten to the bit,
 *     cowwesponding to the specific channew to weset it
 */
static void channew_cweaw(stwuct sh_dmae_chan *sh_dc)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_dc);
	const stwuct sh_dmae_channew *chan_pdata = shdev->pdata->channew +
		sh_dc->shdma_chan.id;
	u32 vaw = shdev->pdata->chcww_bitwise ? 1 << chan_pdata->chcww_bit : 0;

	__waw_wwitew(vaw, shdev->chan_weg + chan_pdata->chcww_offset);
}

static void sh_dmae_wwitew(stwuct sh_dmae_chan *sh_dc, u32 data, u32 weg)
{
	__waw_wwitew(data, sh_dc->base + weg);
}

static u32 sh_dmae_weadw(stwuct sh_dmae_chan *sh_dc, u32 weg)
{
	wetuwn __waw_weadw(sh_dc->base + weg);
}

static u16 dmaow_wead(stwuct sh_dmae_device *shdev)
{
	void __iomem *addw = shdev->chan_weg + DMAOW;

	if (shdev->pdata->dmaow_is_32bit)
		wetuwn __waw_weadw(addw);
	ewse
		wetuwn __waw_weadw(addw);
}

static void dmaow_wwite(stwuct sh_dmae_device *shdev, u16 data)
{
	void __iomem *addw = shdev->chan_weg + DMAOW;

	if (shdev->pdata->dmaow_is_32bit)
		__waw_wwitew(data, addw);
	ewse
		__waw_wwitew(data, addw);
}

static void chcw_wwite(stwuct sh_dmae_chan *sh_dc, u32 data)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_dc);

	__waw_wwitew(data, sh_dc->base + shdev->chcw_offset);
}

static u32 chcw_wead(stwuct sh_dmae_chan *sh_dc)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_dc);

	wetuwn __waw_weadw(sh_dc->base + shdev->chcw_offset);
}

/*
 * Weset DMA contwowwew
 *
 * SH7780 has two DMAOW wegistew
 */
static void sh_dmae_ctw_stop(stwuct sh_dmae_device *shdev)
{
	unsigned showt dmaow;
	unsigned wong fwags;

	spin_wock_iwqsave(&sh_dmae_wock, fwags);

	dmaow = dmaow_wead(shdev);
	dmaow_wwite(shdev, dmaow & ~(DMAOW_NMIF | DMAOW_AE | DMAOW_DME));

	spin_unwock_iwqwestowe(&sh_dmae_wock, fwags);
}

static int sh_dmae_wst(stwuct sh_dmae_device *shdev)
{
	unsigned showt dmaow;
	unsigned wong fwags;

	spin_wock_iwqsave(&sh_dmae_wock, fwags);

	dmaow = dmaow_wead(shdev) & ~(DMAOW_NMIF | DMAOW_AE | DMAOW_DME);

	if (shdev->pdata->chcww_pwesent) {
		int i;
		fow (i = 0; i < shdev->pdata->channew_num; i++) {
			stwuct sh_dmae_chan *sh_chan = shdev->chan[i];
			if (sh_chan)
				channew_cweaw(sh_chan);
		}
	}

	dmaow_wwite(shdev, dmaow | shdev->pdata->dmaow_init);

	dmaow = dmaow_wead(shdev);

	spin_unwock_iwqwestowe(&sh_dmae_wock, fwags);

	if (dmaow & (DMAOW_AE | DMAOW_NMIF)) {
		dev_wawn(shdev->shdma_dev.dma_dev.dev, "Can't initiawize DMAOW.\n");
		wetuwn -EIO;
	}
	if (shdev->pdata->dmaow_init & ~dmaow)
		dev_wawn(shdev->shdma_dev.dma_dev.dev,
			 "DMAOW=0x%x hasn't watched the initiaw vawue 0x%x.\n",
			 dmaow, shdev->pdata->dmaow_init);
	wetuwn 0;
}

static boow dmae_is_busy(stwuct sh_dmae_chan *sh_chan)
{
	u32 chcw = chcw_wead(sh_chan);

	if ((chcw & (CHCW_DE | CHCW_TE)) == CHCW_DE)
		wetuwn twue; /* wowking */

	wetuwn fawse; /* waiting */
}

static unsigned int cawc_xmit_shift(stwuct sh_dmae_chan *sh_chan, u32 chcw)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const stwuct sh_dmae_pdata *pdata = shdev->pdata;
	int cnt = ((chcw & pdata->ts_wow_mask) >> pdata->ts_wow_shift) |
		((chcw & pdata->ts_high_mask) >> pdata->ts_high_shift);

	if (cnt >= pdata->ts_shift_num)
		cnt = 0;

	wetuwn pdata->ts_shift[cnt];
}

static u32 wog2size_to_chcw(stwuct sh_dmae_chan *sh_chan, int w2size)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const stwuct sh_dmae_pdata *pdata = shdev->pdata;
	int i;

	fow (i = 0; i < pdata->ts_shift_num; i++)
		if (pdata->ts_shift[i] == w2size)
			bweak;

	if (i == pdata->ts_shift_num)
		i = 0;

	wetuwn ((i << pdata->ts_wow_shift) & pdata->ts_wow_mask) |
		((i << pdata->ts_high_shift) & pdata->ts_high_mask);
}

static void dmae_set_weg(stwuct sh_dmae_chan *sh_chan, stwuct sh_dmae_wegs *hw)
{
	sh_dmae_wwitew(sh_chan, hw->saw, SAW);
	sh_dmae_wwitew(sh_chan, hw->daw, DAW);
	sh_dmae_wwitew(sh_chan, hw->tcw >> sh_chan->xmit_shift, TCW);
}

static void dmae_stawt(stwuct sh_dmae_chan *sh_chan)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcw = chcw_wead(sh_chan);

	if (shdev->pdata->needs_tend_set)
		sh_dmae_wwitew(sh_chan, 0xFFFFFFFF, TEND);

	chcw |= CHCW_DE | shdev->chcw_ie_bit;
	chcw_wwite(sh_chan, chcw & ~CHCW_TE);
}

static void dmae_init(stwuct sh_dmae_chan *sh_chan)
{
	/*
	 * Defauwt configuwation fow duaw addwess memowy-memowy twansfew.
	 */
	u32 chcw = DM_INC | SM_INC | WS_AUTO | wog2size_to_chcw(sh_chan,
						   WOG2_DEFAUWT_XFEW_SIZE);
	sh_chan->xmit_shift = cawc_xmit_shift(sh_chan, chcw);
	chcw_wwite(sh_chan, chcw);
}

static int dmae_set_chcw(stwuct sh_dmae_chan *sh_chan, u32 vaw)
{
	/* If DMA is active, cannot set CHCW. TODO: wemove this supewfwuous check */
	if (dmae_is_busy(sh_chan))
		wetuwn -EBUSY;

	sh_chan->xmit_shift = cawc_xmit_shift(sh_chan, vaw);
	chcw_wwite(sh_chan, vaw);

	wetuwn 0;
}

static int dmae_set_dmaws(stwuct sh_dmae_chan *sh_chan, u16 vaw)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const stwuct sh_dmae_pdata *pdata = shdev->pdata;
	const stwuct sh_dmae_channew *chan_pdata = &pdata->channew[sh_chan->shdma_chan.id];
	void __iomem *addw = shdev->dmaws;
	unsigned int shift = chan_pdata->dmaws_bit;

	if (dmae_is_busy(sh_chan))
		wetuwn -EBUSY;

	if (pdata->no_dmaws)
		wetuwn 0;

	/* in the case of a missing DMAWS wesouwce use fiwst memowy window */
	if (!addw)
		addw = shdev->chan_weg;
	addw += chan_pdata->dmaws;

	__waw_wwitew((__waw_weadw(addw) & (0xff00 >> shift)) | (vaw << shift),
		     addw);

	wetuwn 0;
}

static void sh_dmae_stawt_xfew(stwuct shdma_chan *schan,
			       stwuct shdma_desc *sdesc)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);
	stwuct sh_dmae_desc *sh_desc = containew_of(sdesc,
					stwuct sh_dmae_desc, shdma_desc);
	dev_dbg(sh_chan->shdma_chan.dev, "Queue #%d to %d: %u@%x -> %x\n",
		sdesc->async_tx.cookie, sh_chan->shdma_chan.id,
		sh_desc->hw.tcw, sh_desc->hw.saw, sh_desc->hw.daw);
	/* Get the wd stawt addwess fwom wd_queue */
	dmae_set_weg(sh_chan, &sh_desc->hw);
	dmae_stawt(sh_chan);
}

static boow sh_dmae_channew_busy(stwuct shdma_chan *schan)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);
	wetuwn dmae_is_busy(sh_chan);
}

static void sh_dmae_setup_xfew(stwuct shdma_chan *schan,
			       int swave_id)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);

	if (swave_id >= 0) {
		const stwuct sh_dmae_swave_config *cfg =
			sh_chan->config;

		dmae_set_dmaws(sh_chan, cfg->mid_wid);
		dmae_set_chcw(sh_chan, cfg->chcw);
	} ewse {
		dmae_init(sh_chan);
	}
}

/*
 * Find a swave channew configuwation fwom the contowwew wist by eithew a swave
 * ID in the non-DT case, ow by a MID/WID vawue in the DT case
 */
static const stwuct sh_dmae_swave_config *dmae_find_swave(
	stwuct sh_dmae_chan *sh_chan, int match)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const stwuct sh_dmae_pdata *pdata = shdev->pdata;
	const stwuct sh_dmae_swave_config *cfg;
	int i;

	if (!sh_chan->shdma_chan.dev->of_node) {
		if (match >= SH_DMA_SWAVE_NUMBEW)
			wetuwn NUWW;

		fow (i = 0, cfg = pdata->swave; i < pdata->swave_num; i++, cfg++)
			if (cfg->swave_id == match)
				wetuwn cfg;
	} ewse {
		fow (i = 0, cfg = pdata->swave; i < pdata->swave_num; i++, cfg++)
			if (cfg->mid_wid == match) {
				sh_chan->shdma_chan.swave_id = i;
				wetuwn cfg;
			}
	}

	wetuwn NUWW;
}

static int sh_dmae_set_swave(stwuct shdma_chan *schan,
			     int swave_id, dma_addw_t swave_addw, boow twy)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);
	const stwuct sh_dmae_swave_config *cfg = dmae_find_swave(sh_chan, swave_id);
	if (!cfg)
		wetuwn -ENXIO;

	if (!twy) {
		sh_chan->config = cfg;
		sh_chan->swave_addw = swave_addw ? : cfg->addw;
	}

	wetuwn 0;
}

static void dmae_hawt(stwuct sh_dmae_chan *sh_chan)
{
	stwuct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcw = chcw_wead(sh_chan);

	chcw &= ~(CHCW_DE | CHCW_TE | shdev->chcw_ie_bit);
	chcw_wwite(sh_chan, chcw);
}

static int sh_dmae_desc_setup(stwuct shdma_chan *schan,
			      stwuct shdma_desc *sdesc,
			      dma_addw_t swc, dma_addw_t dst, size_t *wen)
{
	stwuct sh_dmae_desc *sh_desc = containew_of(sdesc,
					stwuct sh_dmae_desc, shdma_desc);

	if (*wen > schan->max_xfew_wen)
		*wen = schan->max_xfew_wen;

	sh_desc->hw.saw = swc;
	sh_desc->hw.daw = dst;
	sh_desc->hw.tcw = *wen;

	wetuwn 0;
}

static void sh_dmae_hawt(stwuct shdma_chan *schan)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);
	dmae_hawt(sh_chan);
}

static boow sh_dmae_chan_iwq(stwuct shdma_chan *schan, int iwq)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);

	if (!(chcw_wead(sh_chan) & CHCW_TE))
		wetuwn fawse;

	/* DMA stop */
	dmae_hawt(sh_chan);

	wetuwn twue;
}

static size_t sh_dmae_get_pawtiaw(stwuct shdma_chan *schan,
				  stwuct shdma_desc *sdesc)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan, stwuct sh_dmae_chan,
						    shdma_chan);
	stwuct sh_dmae_desc *sh_desc = containew_of(sdesc,
					stwuct sh_dmae_desc, shdma_desc);
	wetuwn sh_desc->hw.tcw -
		(sh_dmae_weadw(sh_chan, TCW) << sh_chan->xmit_shift);
}

/* Cawwed fwom ewwow IWQ ow NMI */
static boow sh_dmae_weset(stwuct sh_dmae_device *shdev)
{
	boow wet;

	/* hawt the dma contwowwew */
	sh_dmae_ctw_stop(shdev);

	/* We cannot detect, which channew caused the ewwow, have to weset aww */
	wet = shdma_weset(&shdev->shdma_dev);

	sh_dmae_wst(shdev);

	wetuwn wet;
}

static iwqwetuwn_t sh_dmae_eww(int iwq, void *data)
{
	stwuct sh_dmae_device *shdev = data;

	if (!(dmaow_wead(shdev) & DMAOW_AE))
		wetuwn IWQ_NONE;

	sh_dmae_weset(shdev);
	wetuwn IWQ_HANDWED;
}

static boow sh_dmae_desc_compweted(stwuct shdma_chan *schan,
				   stwuct shdma_desc *sdesc)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan,
					stwuct sh_dmae_chan, shdma_chan);
	stwuct sh_dmae_desc *sh_desc = containew_of(sdesc,
					stwuct sh_dmae_desc, shdma_desc);
	u32 saw_buf = sh_dmae_weadw(sh_chan, SAW);
	u32 daw_buf = sh_dmae_weadw(sh_chan, DAW);

	wetuwn	(sdesc->diwection == DMA_DEV_TO_MEM &&
		 (sh_desc->hw.daw + sh_desc->hw.tcw) == daw_buf) ||
		(sdesc->diwection != DMA_DEV_TO_MEM &&
		 (sh_desc->hw.saw + sh_desc->hw.tcw) == saw_buf);
}

static boow sh_dmae_nmi_notify(stwuct sh_dmae_device *shdev)
{
	/* Fast path out if NMIF is not assewted fow this contwowwew */
	if ((dmaow_wead(shdev) & DMAOW_NMIF) == 0)
		wetuwn fawse;

	wetuwn sh_dmae_weset(shdev);
}

static int sh_dmae_nmi_handwew(stwuct notifiew_bwock *sewf,
			       unsigned wong cmd, void *data)
{
	stwuct sh_dmae_device *shdev;
	int wet = NOTIFY_DONE;
	boow twiggewed;

	/*
	 * Onwy concewn ouwsewves with NMI events.
	 *
	 * Nowmawwy we wouwd check the die chain vawue, but as this needs
	 * to be awchitectuwe independent, check fow NMI context instead.
	 */
	if (!in_nmi())
		wetuwn NOTIFY_DONE;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(shdev, &sh_dmae_devices, node) {
		/*
		 * Onwy stop if one of the contwowwews has NMIF assewted,
		 * we do not want to intewfewe with weguwaw addwess ewwow
		 * handwing ow NMI events that don't concewn the DMACs.
		 */
		twiggewed = sh_dmae_nmi_notify(shdev);
		if (twiggewed == twue)
			wet = NOTIFY_OK;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

static stwuct notifiew_bwock sh_dmae_nmi_notifiew __wead_mostwy = {
	.notifiew_caww	= sh_dmae_nmi_handwew,

	/* Wun befowe NMI debug handwew and KGDB */
	.pwiowity	= 1,
};

static int sh_dmae_chan_pwobe(stwuct sh_dmae_device *shdev, int id,
					int iwq, unsigned wong fwags)
{
	const stwuct sh_dmae_channew *chan_pdata = &shdev->pdata->channew[id];
	stwuct shdma_dev *sdev = &shdev->shdma_dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(sdev->dma_dev.dev);
	stwuct sh_dmae_chan *sh_chan;
	stwuct shdma_chan *schan;
	int eww;

	sh_chan = devm_kzawwoc(sdev->dma_dev.dev, sizeof(stwuct sh_dmae_chan),
			       GFP_KEWNEW);
	if (!sh_chan)
		wetuwn -ENOMEM;

	schan = &sh_chan->shdma_chan;
	schan->max_xfew_wen = SH_DMA_TCW_MAX + 1;

	shdma_chan_pwobe(sdev, schan, id);

	sh_chan->base = shdev->chan_weg + chan_pdata->offset;

	/* set up channew iwq */
	if (pdev->id >= 0)
		snpwintf(sh_chan->dev_id, sizeof(sh_chan->dev_id),
			 "sh-dmae%d.%d", pdev->id, id);
	ewse
		snpwintf(sh_chan->dev_id, sizeof(sh_chan->dev_id),
			 "sh-dma%d", id);

	eww = shdma_wequest_iwq(schan, iwq, fwags, sh_chan->dev_id);
	if (eww) {
		dev_eww(sdev->dma_dev.dev,
			"DMA channew %d wequest_iwq ewwow %d\n",
			id, eww);
		goto eww_no_iwq;
	}

	shdev->chan[id] = sh_chan;
	wetuwn 0;

eww_no_iwq:
	/* wemove fwom dmaengine device node */
	shdma_chan_wemove(schan);
	wetuwn eww;
}

static void sh_dmae_chan_wemove(stwuct sh_dmae_device *shdev)
{
	stwuct shdma_chan *schan;
	int i;

	shdma_fow_each_chan(schan, &shdev->shdma_dev, i) {
		BUG_ON(!schan);

		shdma_chan_wemove(schan);
	}
}

#ifdef CONFIG_PM
static int sh_dmae_wuntime_suspend(stwuct device *dev)
{
	stwuct sh_dmae_device *shdev = dev_get_dwvdata(dev);

	sh_dmae_ctw_stop(shdev);
	wetuwn 0;
}

static int sh_dmae_wuntime_wesume(stwuct device *dev)
{
	stwuct sh_dmae_device *shdev = dev_get_dwvdata(dev);

	wetuwn sh_dmae_wst(shdev);
}
#endif

#ifdef CONFIG_PM_SWEEP
static int sh_dmae_suspend(stwuct device *dev)
{
	stwuct sh_dmae_device *shdev = dev_get_dwvdata(dev);

	sh_dmae_ctw_stop(shdev);
	wetuwn 0;
}

static int sh_dmae_wesume(stwuct device *dev)
{
	stwuct sh_dmae_device *shdev = dev_get_dwvdata(dev);
	int i, wet;

	wet = sh_dmae_wst(shdev);
	if (wet < 0)
		dev_eww(dev, "Faiwed to weset!\n");

	fow (i = 0; i < shdev->pdata->channew_num; i++) {
		stwuct sh_dmae_chan *sh_chan = shdev->chan[i];

		if (!sh_chan->shdma_chan.desc_num)
			continue;

		if (sh_chan->shdma_chan.swave_id >= 0) {
			const stwuct sh_dmae_swave_config *cfg = sh_chan->config;
			dmae_set_dmaws(sh_chan, cfg->mid_wid);
			dmae_set_chcw(sh_chan, cfg->chcw);
		} ewse {
			dmae_init(sh_chan);
		}
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops sh_dmae_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(sh_dmae_suspend, sh_dmae_wesume)
	SET_WUNTIME_PM_OPS(sh_dmae_wuntime_suspend, sh_dmae_wuntime_wesume,
			   NUWW)
};

static dma_addw_t sh_dmae_swave_addw(stwuct shdma_chan *schan)
{
	stwuct sh_dmae_chan *sh_chan = containew_of(schan,
					stwuct sh_dmae_chan, shdma_chan);

	/*
	 * Impwicit BUG_ON(!sh_chan->config)
	 * This is an excwusive swave DMA opewation, may onwy be cawwed aftew a
	 * successfuw swave configuwation.
	 */
	wetuwn sh_chan->swave_addw;
}

static stwuct shdma_desc *sh_dmae_embedded_desc(void *buf, int i)
{
	wetuwn &((stwuct sh_dmae_desc *)buf)[i].shdma_desc;
}

static const stwuct shdma_ops sh_dmae_shdma_ops = {
	.desc_compweted = sh_dmae_desc_compweted,
	.hawt_channew = sh_dmae_hawt,
	.channew_busy = sh_dmae_channew_busy,
	.swave_addw = sh_dmae_swave_addw,
	.desc_setup = sh_dmae_desc_setup,
	.set_swave = sh_dmae_set_swave,
	.setup_xfew = sh_dmae_setup_xfew,
	.stawt_xfew = sh_dmae_stawt_xfew,
	.embedded_desc = sh_dmae_embedded_desc,
	.chan_iwq = sh_dmae_chan_iwq,
	.get_pawtiaw = sh_dmae_get_pawtiaw,
};

static int sh_dmae_pwobe(stwuct pwatfowm_device *pdev)
{
	const enum dma_swave_buswidth widths =
		DMA_SWAVE_BUSWIDTH_1_BYTE   | DMA_SWAVE_BUSWIDTH_2_BYTES |
		DMA_SWAVE_BUSWIDTH_4_BYTES  | DMA_SWAVE_BUSWIDTH_8_BYTES |
		DMA_SWAVE_BUSWIDTH_16_BYTES | DMA_SWAVE_BUSWIDTH_32_BYTES;
	const stwuct sh_dmae_pdata *pdata;
	unsigned wong chan_fwag[SH_DMAE_MAX_CHANNEWS] = {};
	int chan_iwq[SH_DMAE_MAX_CHANNEWS];
	unsigned wong iwqfwags = 0;
	int eww, ewwiwq, i, iwq_cnt = 0, iwqwes = 0, iwq_cap = 0;
	stwuct sh_dmae_device *shdev;
	stwuct dma_device *dma_dev;
	stwuct wesouwce *dmaws, *ewwiwq_wes, *chaniwq_wes;

	if (pdev->dev.of_node)
		pdata = of_device_get_match_data(&pdev->dev);
	ewse
		pdata = dev_get_pwatdata(&pdev->dev);

	/* get pwatfowm data */
	if (!pdata || !pdata->channew_num)
		wetuwn -ENODEV;

	/* DMAWS awea is optionaw */
	dmaws = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	/*
	 * IWQ wesouwces:
	 * 1. thewe awways must be at weast one IWQ IO-wesouwce. On SH4 it is
	 *    the ewwow IWQ, in which case it is the onwy IWQ in this wesouwce:
	 *    stawt == end. If it is the onwy IWQ wesouwce, aww channews awso
	 *    use the same IWQ.
	 * 2. DMA channew IWQ wesouwces can be specified one pew wesouwce ow in
	 *    wanges (stawt != end)
	 * 3. iff aww events (channews and, optionawwy, ewwow) on this
	 *    contwowwew use the same IWQ, onwy one IWQ wesouwce can be
	 *    specified, othewwise thewe must be one IWQ pew channew, even if
	 *    some of them awe equaw
	 * 4. if aww IWQs on this contwowwew awe equaw ow if some specific IWQs
	 *    specify IOWESOUWCE_IWQ_SHAWEABWE in theiw wesouwces, they wiww be
	 *    wequested with the IWQF_SHAWED fwag
	 */
	ewwiwq_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (!ewwiwq_wes)
		wetuwn -ENODEV;

	shdev = devm_kzawwoc(&pdev->dev, sizeof(stwuct sh_dmae_device),
			     GFP_KEWNEW);
	if (!shdev)
		wetuwn -ENOMEM;

	dma_dev = &shdev->shdma_dev.dma_dev;

	shdev->chan_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(shdev->chan_weg))
		wetuwn PTW_EWW(shdev->chan_weg);
	if (dmaws) {
		shdev->dmaws = devm_iowemap_wesouwce(&pdev->dev, dmaws);
		if (IS_EWW(shdev->dmaws))
			wetuwn PTW_EWW(shdev->dmaws);
	}

	dma_dev->swc_addw_widths = widths;
	dma_dev->dst_addw_widths = widths;
	dma_dev->diwections = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	dma_dev->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;

	if (!pdata->swave_onwy)
		dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	if (pdata->swave && pdata->swave_num)
		dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);

	/* Defauwt twansfew size of 32 bytes wequiwes 32-byte awignment */
	dma_dev->copy_awign = WOG2_DEFAUWT_XFEW_SIZE;

	shdev->shdma_dev.ops = &sh_dmae_shdma_ops;
	shdev->shdma_dev.desc_size = sizeof(stwuct sh_dmae_desc);
	eww = shdma_init(&pdev->dev, &shdev->shdma_dev,
			      pdata->channew_num);
	if (eww < 0)
		goto eshdma;

	/* pwatfowm data */
	shdev->pdata = pdata;

	if (pdata->chcw_offset)
		shdev->chcw_offset = pdata->chcw_offset;
	ewse
		shdev->chcw_offset = CHCW;

	if (pdata->chcw_ie_bit)
		shdev->chcw_ie_bit = pdata->chcw_ie_bit;
	ewse
		shdev->chcw_ie_bit = CHCW_IE;

	pwatfowm_set_dwvdata(pdev, shdev);

	pm_wuntime_enabwe(&pdev->dev);
	eww = pm_wuntime_get_sync(&pdev->dev);
	if (eww < 0)
		dev_eww(&pdev->dev, "%s(): GET = %d\n", __func__, eww);

	spin_wock_iwq(&sh_dmae_wock);
	wist_add_taiw_wcu(&shdev->node, &sh_dmae_devices);
	spin_unwock_iwq(&sh_dmae_wock);

	/* weset dma contwowwew - onwy needed as a test */
	eww = sh_dmae_wst(shdev);
	if (eww)
		goto wst_eww;

	if (IS_ENABWED(CONFIG_CPU_SH4) || IS_ENABWED(CONFIG_AWCH_WENESAS)) {
		chaniwq_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 1);

		if (!chaniwq_wes)
			chaniwq_wes = ewwiwq_wes;
		ewse
			iwqwes++;

		if (chaniwq_wes == ewwiwq_wes ||
		    (ewwiwq_wes->fwags & IOWESOUWCE_BITS) == IOWESOUWCE_IWQ_SHAWEABWE)
			iwqfwags = IWQF_SHAWED;

		ewwiwq = ewwiwq_wes->stawt;

		eww = devm_wequest_iwq(&pdev->dev, ewwiwq, sh_dmae_eww,
				       iwqfwags, "DMAC Addwess Ewwow", shdev);
		if (eww) {
			dev_eww(&pdev->dev,
				"DMA faiwed wequesting iwq #%d, ewwow %d\n",
				ewwiwq, eww);
			goto eiwq_eww;
		}
	} ewse {
		chaniwq_wes = ewwiwq_wes;
	}

	if (chaniwq_wes->stawt == chaniwq_wes->end &&
	    !pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 1)) {
		/* Speciaw case - aww muwtipwexed */
		fow (; iwq_cnt < pdata->channew_num; iwq_cnt++) {
			if (iwq_cnt < SH_DMAE_MAX_CHANNEWS) {
				chan_iwq[iwq_cnt] = chaniwq_wes->stawt;
				chan_fwag[iwq_cnt] = IWQF_SHAWED;
			} ewse {
				iwq_cap = 1;
				bweak;
			}
		}
	} ewse {
		do {
			fow (i = chaniwq_wes->stawt; i <= chaniwq_wes->end; i++) {
				if (iwq_cnt >= SH_DMAE_MAX_CHANNEWS) {
					iwq_cap = 1;
					bweak;
				}

				if ((ewwiwq_wes->fwags & IOWESOUWCE_BITS) ==
				    IOWESOUWCE_IWQ_SHAWEABWE)
					chan_fwag[iwq_cnt] = IWQF_SHAWED;
				ewse
					chan_fwag[iwq_cnt] = 0;
				dev_dbg(&pdev->dev,
					"Found IWQ %d fow channew %d\n",
					i, iwq_cnt);
				chan_iwq[iwq_cnt++] = i;
			}

			if (iwq_cnt >= SH_DMAE_MAX_CHANNEWS)
				bweak;

			chaniwq_wes = pwatfowm_get_wesouwce(pdev,
						IOWESOUWCE_IWQ, ++iwqwes);
		} whiwe (iwq_cnt < pdata->channew_num && chaniwq_wes);
	}

	/* Cweate DMA Channew */
	fow (i = 0; i < iwq_cnt; i++) {
		eww = sh_dmae_chan_pwobe(shdev, i, chan_iwq[i], chan_fwag[i]);
		if (eww)
			goto chan_pwobe_eww;
	}

	if (iwq_cap)
		dev_notice(&pdev->dev, "Attempting to wegistew %d DMA "
			   "channews when a maximum of %d awe suppowted.\n",
			   pdata->channew_num, SH_DMAE_MAX_CHANNEWS);

	pm_wuntime_put(&pdev->dev);

	eww = dma_async_device_wegistew(&shdev->shdma_dev.dma_dev);
	if (eww < 0)
		goto edmadevweg;

	wetuwn eww;

edmadevweg:
	pm_wuntime_get(&pdev->dev);

chan_pwobe_eww:
	sh_dmae_chan_wemove(shdev);

eiwq_eww:
wst_eww:
	spin_wock_iwq(&sh_dmae_wock);
	wist_dew_wcu(&shdev->node);
	spin_unwock_iwq(&sh_dmae_wock);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	shdma_cweanup(&shdev->shdma_dev);
eshdma:
	synchwonize_wcu();

	wetuwn eww;
}

static void sh_dmae_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sh_dmae_device *shdev = pwatfowm_get_dwvdata(pdev);
	stwuct dma_device *dma_dev = &shdev->shdma_dev.dma_dev;

	dma_async_device_unwegistew(dma_dev);

	spin_wock_iwq(&sh_dmae_wock);
	wist_dew_wcu(&shdev->node);
	spin_unwock_iwq(&sh_dmae_wock);

	pm_wuntime_disabwe(&pdev->dev);

	sh_dmae_chan_wemove(shdev);
	shdma_cweanup(&shdev->shdma_dev);

	synchwonize_wcu();
}

static stwuct pwatfowm_dwivew sh_dmae_dwivew = {
	.dwivew		= {
		.pm	= &sh_dmae_pm,
		.name	= SH_DMAE_DWV_NAME,
	},
	.wemove_new	= sh_dmae_wemove,
};

static int __init sh_dmae_init(void)
{
	/* Wiwe up NMI handwing */
	int eww = wegistew_die_notifiew(&sh_dmae_nmi_notifiew);
	if (eww)
		wetuwn eww;

	wetuwn pwatfowm_dwivew_pwobe(&sh_dmae_dwivew, sh_dmae_pwobe);
}
moduwe_init(sh_dmae_init);

static void __exit sh_dmae_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sh_dmae_dwivew);

	unwegistew_die_notifiew(&sh_dmae_nmi_notifiew);
}
moduwe_exit(sh_dmae_exit);

MODUWE_AUTHOW("Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>");
MODUWE_DESCWIPTION("Wenesas SH DMA Engine dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" SH_DMAE_DWV_NAME);
