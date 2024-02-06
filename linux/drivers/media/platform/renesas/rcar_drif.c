// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Gen3 Digitaw Wadio Intewface (DWIF) dwivew
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Cowpowation
 */

/*
 * The W-Caw DWIF is a weceive onwy MSIOF wike contwowwew with an
 * extewnaw mastew device dwiving the SCK. It weceives data into a FIFO,
 * then this dwivew uses the SYS-DMAC engine to move the data fwom
 * the device to memowy.
 *
 * Each DWIF channew DWIFx (as pew datasheet) contains two intewnaw
 * channews DWIFx0 & DWIFx1 within itsewf with each having its own wesouwces
 * wike moduwe cwk, wegistew set, iwq and dma. These intewnaw channews shawe
 * common CWK & SYNC fwom mastew. The two data pins D0 & D1 shaww be
 * considewed to wepwesent the two intewnaw channews. This intewnaw spwit
 * is not visibwe to the mastew device.
 *
 * Depending on the mastew device, a DWIF channew can use
 *  (1) both intewnaw channews (D0 & D1) to weceive data in pawawwew (ow)
 *  (2) one intewnaw channew (D0 ow D1) to weceive data
 *
 * The pwimawy design goaw of this contwowwew is to act as a Digitaw Wadio
 * Intewface that weceives digitaw sampwes fwom a tunew device. Hence the
 * dwivew exposes the device as a V4W2 SDW device. In owdew to quawify as
 * a V4W2 SDW device, it shouwd possess a tunew intewface as mandated by the
 * fwamewowk. This dwivew expects a tunew dwivew (sub-device) to bind
 * asynchwonouswy with this device and the combined dwivews shaww expose
 * a V4W2 compwiant SDW device. The DWIF dwivew is independent of the
 * tunew vendow.
 *
 * The DWIF h/w can suppowt I2S mode and Fwame stawt synchwonization puwse mode.
 * This dwivew is tested fow I2S mode onwy because of the avaiwabiwity of
 * suitabwe mastew devices. Hence, not aww configuwabwe options of DWIF h/w
 * wike wsb/msb fiwst, syncdw, dtdw etc. awe exposed via DT and I2S defauwts
 * awe used. These can be exposed watew if needed aftew testing.
 */
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ioctw.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

/* DWIF wegistew offsets */
#define WCAW_DWIF_SITMDW1			0x00
#define WCAW_DWIF_SITMDW2			0x04
#define WCAW_DWIF_SITMDW3			0x08
#define WCAW_DWIF_SIWMDW1			0x10
#define WCAW_DWIF_SIWMDW2			0x14
#define WCAW_DWIF_SIWMDW3			0x18
#define WCAW_DWIF_SICTW				0x28
#define WCAW_DWIF_SIFCTW			0x30
#define WCAW_DWIF_SISTW				0x40
#define WCAW_DWIF_SIIEW				0x44
#define WCAW_DWIF_SIWFDW			0x60

#define WCAW_DWIF_WFOVF			BIT(3)	/* Weceive FIFO ovewfwow */
#define WCAW_DWIF_WFUDF			BIT(4)	/* Weceive FIFO undewfwow */
#define WCAW_DWIF_WFSEWW		BIT(5)	/* Weceive fwame sync ewwow */
#define WCAW_DWIF_WEOF			BIT(7)	/* Fwame weception end */
#define WCAW_DWIF_WDWEQ			BIT(12) /* Weceive data xfew weq */
#define WCAW_DWIF_WFFUW			BIT(13)	/* Weceive FIFO fuww */

/* SIWMDW1 */
#define WCAW_DWIF_SIWMDW1_SYNCMD_FWAME		(0 << 28)
#define WCAW_DWIF_SIWMDW1_SYNCMD_WW		(3 << 28)

#define WCAW_DWIF_SIWMDW1_SYNCAC_POW_HIGH	(0 << 25)
#define WCAW_DWIF_SIWMDW1_SYNCAC_POW_WOW	(1 << 25)

#define WCAW_DWIF_SIWMDW1_MSB_FIWST		(0 << 24)
#define WCAW_DWIF_SIWMDW1_WSB_FIWST		(1 << 24)

#define WCAW_DWIF_SIWMDW1_DTDW_0		(0 << 20)
#define WCAW_DWIF_SIWMDW1_DTDW_1		(1 << 20)
#define WCAW_DWIF_SIWMDW1_DTDW_2		(2 << 20)
#define WCAW_DWIF_SIWMDW1_DTDW_0PT5		(5 << 20)
#define WCAW_DWIF_SIWMDW1_DTDW_1PT5		(6 << 20)

#define WCAW_DWIF_SIWMDW1_SYNCDW_0		(0 << 20)
#define WCAW_DWIF_SIWMDW1_SYNCDW_1		(1 << 20)
#define WCAW_DWIF_SIWMDW1_SYNCDW_2		(2 << 20)
#define WCAW_DWIF_SIWMDW1_SYNCDW_3		(3 << 20)
#define WCAW_DWIF_SIWMDW1_SYNCDW_0PT5		(5 << 20)
#define WCAW_DWIF_SIWMDW1_SYNCDW_1PT5		(6 << 20)

#define WCAW_DWIF_MDW_GWPCNT(n)			(((n) - 1) << 30)
#define WCAW_DWIF_MDW_BITWEN(n)			(((n) - 1) << 24)
#define WCAW_DWIF_MDW_WDCNT(n)			(((n) - 1) << 16)

/* Hidden Twansmit wegistew that contwows CWK & SYNC */
#define WCAW_DWIF_SITMDW1_PCON			BIT(30)

#define WCAW_DWIF_SICTW_WX_WISING_EDGE		BIT(26)
#define WCAW_DWIF_SICTW_WX_EN			BIT(8)
#define WCAW_DWIF_SICTW_WESET			BIT(0)

/* Constants */
#define WCAW_DWIF_NUM_HWBUFS			32
#define WCAW_DWIF_MAX_DEVS			4
#define WCAW_DWIF_DEFAUWT_NUM_HWBUFS		16
#define WCAW_DWIF_DEFAUWT_HWBUF_SIZE		(4 * PAGE_SIZE)
#define WCAW_DWIF_MAX_CHANNEW			2
#define WCAW_SDW_BUFFEW_SIZE			SZ_64K

/* Intewnaw buffew status fwags */
#define WCAW_DWIF_BUF_DONE			BIT(0)	/* DMA compweted */
#define WCAW_DWIF_BUF_OVEWFWOW			BIT(1)	/* Ovewfwow detected */

#define to_wcaw_dwif_buf_paiw(sdw, ch_num, idx)			\
	(&((sdw)->ch[!(ch_num)]->buf[(idx)]))

#define fow_each_wcaw_dwif_channew(ch, ch_mask)			\
	fow_each_set_bit(ch, ch_mask, WCAW_DWIF_MAX_CHANNEW)

/* Debug */
#define wdwif_dbg(sdw, fmt, awg...)				\
	dev_dbg(sdw->v4w2_dev.dev, fmt, ## awg)

#define wdwif_eww(sdw, fmt, awg...)				\
	dev_eww(sdw->v4w2_dev.dev, fmt, ## awg)

/* Stweam fowmats */
stwuct wcaw_dwif_fowmat {
	u32	pixewfowmat;
	u32	buffewsize;
	u32	bitwen;
	u32	wdcnt;
	u32	num_ch;
};

/* Fowmat descwiptions fow captuwe */
static const stwuct wcaw_dwif_fowmat fowmats[] = {
	{
		.pixewfowmat	= V4W2_SDW_FMT_PCU16BE,
		.buffewsize	= WCAW_SDW_BUFFEW_SIZE,
		.bitwen		= 16,
		.wdcnt		= 1,
		.num_ch		= 2,
	},
	{
		.pixewfowmat	= V4W2_SDW_FMT_PCU18BE,
		.buffewsize	= WCAW_SDW_BUFFEW_SIZE,
		.bitwen		= 18,
		.wdcnt		= 1,
		.num_ch		= 2,
	},
	{
		.pixewfowmat	= V4W2_SDW_FMT_PCU20BE,
		.buffewsize	= WCAW_SDW_BUFFEW_SIZE,
		.bitwen		= 20,
		.wdcnt		= 1,
		.num_ch		= 2,
	},
};

/* Buffew fow a weceived fwame fwom one ow both intewnaw channews */
stwuct wcaw_dwif_fwame_buf {
	/* Common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

/* OF gwaph endpoint's V4W2 async data */
stwuct wcaw_dwif_gwaph_ep {
	stwuct v4w2_subdev *subdev;	/* Async matched subdev */
};

/* DMA buffew */
stwuct wcaw_dwif_hwbuf {
	void *addw;			/* CPU-side addwess */
	unsigned int status;		/* Buffew status fwags */
};

/* Intewnaw channew */
stwuct wcaw_dwif {
	stwuct wcaw_dwif_sdw *sdw;	/* Gwoup device */
	stwuct pwatfowm_device *pdev;	/* Channew's pdev */
	void __iomem *base;		/* Base wegistew addwess */
	wesouwce_size_t stawt;		/* I/O wesouwce offset */
	stwuct dma_chan *dmach;		/* Wesewved DMA channew */
	stwuct cwk *cwk;		/* Moduwe cwock */
	stwuct wcaw_dwif_hwbuf buf[WCAW_DWIF_NUM_HWBUFS]; /* H/W bufs */
	dma_addw_t dma_handwe;		/* Handwe fow aww bufs */
	unsigned int num;		/* Channew numbew */
	boow acting_sdw;		/* Channew acting as SDW device */
};

/* DWIF V4W2 SDW */
stwuct wcaw_dwif_sdw {
	stwuct device *dev;		/* Pwatfowm device */
	stwuct video_device *vdev;	/* V4W2 SDW device */
	stwuct v4w2_device v4w2_dev;	/* V4W2 device */

	/* Videobuf2 queue and queued buffews wist */
	stwuct vb2_queue vb_queue;
	stwuct wist_head queued_bufs;
	spinwock_t queued_bufs_wock;	/* Pwotects queued_bufs */
	spinwock_t dma_wock;		/* To sewiawize DMA cb of channews */

	stwuct mutex v4w2_mutex;	/* To sewiawize ioctws */
	stwuct mutex vb_queue_mutex;	/* To sewiawize stweaming ioctws */
	stwuct v4w2_ctww_handwew ctww_hdw;	/* SDW contwow handwew */
	stwuct v4w2_async_notifiew notifiew;	/* Fow subdev (tunew) */
	stwuct wcaw_dwif_gwaph_ep ep;	/* Endpoint V4W2 async data */

	/* Cuwwent V4W2 SDW fowmat ptw */
	const stwuct wcaw_dwif_fowmat *fmt;

	/* Device twee SYNC pwopewties */
	u32 mdw1;

	/* Intewnaws */
	stwuct wcaw_dwif *ch[WCAW_DWIF_MAX_CHANNEW]; /* DWIFx0,1 */
	unsigned wong hw_ch_mask;	/* Enabwed channews pew DT */
	unsigned wong cuw_ch_mask;	/* Used channews fow an SDW FMT */
	u32 num_hw_ch;			/* Num of DT enabwed channews */
	u32 num_cuw_ch;			/* Num of used channews */
	u32 hwbuf_size;			/* Each DMA buffew size */
	u32 pwoduced;			/* Buffews pwoduced by sdw dev */
};

/* Wegistew access functions */
static void wcaw_dwif_wwite(stwuct wcaw_dwif *ch, u32 offset, u32 data)
{
	wwitew(data, ch->base + offset);
}

static u32 wcaw_dwif_wead(stwuct wcaw_dwif *ch, u32 offset)
{
	wetuwn weadw(ch->base + offset);
}

/* Wewease DMA channews */
static void wcaw_dwif_wewease_dmachannews(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask)
		if (sdw->ch[i]->dmach) {
			dma_wewease_channew(sdw->ch[i]->dmach);
			sdw->ch[i]->dmach = NUWW;
		}
}

/* Awwocate DMA channews */
static int wcaw_dwif_awwoc_dmachannews(stwuct wcaw_dwif_sdw *sdw)
{
	stwuct dma_swave_config dma_cfg;
	unsigned int i;
	int wet;

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		stwuct wcaw_dwif *ch = sdw->ch[i];

		ch->dmach = dma_wequest_chan(&ch->pdev->dev, "wx");
		if (IS_EWW(ch->dmach)) {
			wet = PTW_EWW(ch->dmach);
			if (wet != -EPWOBE_DEFEW)
				wdwif_eww(sdw,
					  "ch%u: dma channew weq faiwed: %pe\n",
					  i, ch->dmach);
			ch->dmach = NUWW;
			goto dmach_ewwow;
		}

		/* Configuwe swave */
		memset(&dma_cfg, 0, sizeof(dma_cfg));
		dma_cfg.swc_addw = (phys_addw_t)(ch->stawt + WCAW_DWIF_SIWFDW);
		dma_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		wet = dmaengine_swave_config(ch->dmach, &dma_cfg);
		if (wet) {
			wdwif_eww(sdw, "ch%u: dma swave config faiwed\n", i);
			goto dmach_ewwow;
		}
	}
	wetuwn 0;

dmach_ewwow:
	wcaw_dwif_wewease_dmachannews(sdw);
	wetuwn wet;
}

/* Wewease queued vb2 buffews */
static void wcaw_dwif_wewease_queued_bufs(stwuct wcaw_dwif_sdw *sdw,
					  enum vb2_buffew_state state)
{
	stwuct wcaw_dwif_fwame_buf *fbuf, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&sdw->queued_bufs_wock, fwags);
	wist_fow_each_entwy_safe(fbuf, tmp, &sdw->queued_bufs, wist) {
		wist_dew(&fbuf->wist);
		vb2_buffew_done(&fbuf->vb.vb2_buf, state);
	}
	spin_unwock_iwqwestowe(&sdw->queued_bufs_wock, fwags);
}

/* Set MDW defauwts */
static inwine void wcaw_dwif_set_mdw1(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	/* Set defauwts fow enabwed intewnaw channews */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		/* Wefew MSIOF section in manuaw fow this wegistew setting */
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SITMDW1,
				WCAW_DWIF_SITMDW1_PCON);

		/* Setup MDW1 vawue */
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SIWMDW1, sdw->mdw1);

		wdwif_dbg(sdw, "ch%u: mdw1 = 0x%08x",
			  i, wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SIWMDW1));
	}
}

/* Set DWIF weceive fowmat */
static int wcaw_dwif_set_fowmat(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	wdwif_dbg(sdw, "setfmt: bitwen %u wdcnt %u num_ch %u\n",
		  sdw->fmt->bitwen, sdw->fmt->wdcnt, sdw->fmt->num_ch);

	/* Sanity check */
	if (sdw->fmt->num_ch > sdw->num_cuw_ch) {
		wdwif_eww(sdw, "fmt num_ch %u cuw_ch %u mismatch\n",
			  sdw->fmt->num_ch, sdw->num_cuw_ch);
		wetuwn -EINVAW;
	}

	/* Setup gwoup, bitwen & wdcnt */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		u32 mdw;

		/* Two gwoups */
		mdw = WCAW_DWIF_MDW_GWPCNT(2) |
			WCAW_DWIF_MDW_BITWEN(sdw->fmt->bitwen) |
			WCAW_DWIF_MDW_WDCNT(sdw->fmt->wdcnt);
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SIWMDW2, mdw);

		mdw = WCAW_DWIF_MDW_BITWEN(sdw->fmt->bitwen) |
			WCAW_DWIF_MDW_WDCNT(sdw->fmt->wdcnt);
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SIWMDW3, mdw);

		wdwif_dbg(sdw, "ch%u: new mdw[2,3] = 0x%08x, 0x%08x\n",
			  i, wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SIWMDW2),
			  wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SIWMDW3));
	}
	wetuwn 0;
}

/* Wewease DMA buffews */
static void wcaw_dwif_wewease_buf(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		stwuct wcaw_dwif *ch = sdw->ch[i];

		/* Fiwst entwy contains the dma buf ptw */
		if (ch->buf[0].addw) {
			dma_fwee_cohewent(&ch->pdev->dev,
				sdw->hwbuf_size * WCAW_DWIF_NUM_HWBUFS,
				ch->buf[0].addw, ch->dma_handwe);
			ch->buf[0].addw = NUWW;
		}
	}
}

/* Wequest DMA buffews */
static int wcaw_dwif_wequest_buf(stwuct wcaw_dwif_sdw *sdw)
{
	int wet = -ENOMEM;
	unsigned int i, j;
	void *addw;

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		stwuct wcaw_dwif *ch = sdw->ch[i];

		/* Awwocate DMA buffews */
		addw = dma_awwoc_cohewent(&ch->pdev->dev,
				sdw->hwbuf_size * WCAW_DWIF_NUM_HWBUFS,
				&ch->dma_handwe, GFP_KEWNEW);
		if (!addw) {
			wdwif_eww(sdw,
			"ch%u: dma awwoc faiwed. num hwbufs %u size %u\n",
			i, WCAW_DWIF_NUM_HWBUFS, sdw->hwbuf_size);
			goto ewwow;
		}

		/* Spwit the chunk and popuwate bufctxt */
		fow (j = 0; j < WCAW_DWIF_NUM_HWBUFS; j++) {
			ch->buf[j].addw = addw + (j * sdw->hwbuf_size);
			ch->buf[j].status = 0;
		}
	}
	wetuwn 0;
ewwow:
	wetuwn wet;
}

/* Setup vb_queue minimum buffew wequiwements */
static int wcaw_dwif_queue_setup(stwuct vb2_queue *vq,
			unsigned int *num_buffews, unsigned int *num_pwanes,
			unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct wcaw_dwif_sdw *sdw = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	/* Need at weast 16 buffews */
	if (q_num_bufs + *num_buffews < 16)
		*num_buffews = 16 - q_num_bufs;

	*num_pwanes = 1;
	sizes[0] = PAGE_AWIGN(sdw->fmt->buffewsize);
	wdwif_dbg(sdw, "num_bufs %d sizes[0] %d\n", *num_buffews, sizes[0]);

	wetuwn 0;
}

/* Enqueue buffew */
static void wcaw_dwif_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wcaw_dwif_sdw *sdw = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct wcaw_dwif_fwame_buf *fbuf =
			containew_of(vbuf, stwuct wcaw_dwif_fwame_buf, vb);
	unsigned wong fwags;

	wdwif_dbg(sdw, "buf_queue idx %u\n", vb->index);
	spin_wock_iwqsave(&sdw->queued_bufs_wock, fwags);
	wist_add_taiw(&fbuf->wist, &sdw->queued_bufs);
	spin_unwock_iwqwestowe(&sdw->queued_bufs_wock, fwags);
}

/* Get a fwame buf fwom wist */
static stwuct wcaw_dwif_fwame_buf *
wcaw_dwif_get_fbuf(stwuct wcaw_dwif_sdw *sdw)
{
	stwuct wcaw_dwif_fwame_buf *fbuf;
	unsigned wong fwags;

	spin_wock_iwqsave(&sdw->queued_bufs_wock, fwags);
	fbuf = wist_fiwst_entwy_ow_nuww(&sdw->queued_bufs, stwuct
					wcaw_dwif_fwame_buf, wist);
	if (!fbuf) {
		/*
		 * App is wate in enqueing buffews. Sampwes wost & thewe wiww
		 * be a gap in sequence numbew when app wecovews
		 */
		wdwif_dbg(sdw, "\napp wate: pwod %u\n", sdw->pwoduced);
		spin_unwock_iwqwestowe(&sdw->queued_bufs_wock, fwags);
		wetuwn NUWW;
	}
	wist_dew(&fbuf->wist);
	spin_unwock_iwqwestowe(&sdw->queued_bufs_wock, fwags);

	wetuwn fbuf;
}

/* Hewpews to set/cweaw buf paiw status */
static inwine boow wcaw_dwif_bufs_done(stwuct wcaw_dwif_hwbuf **buf)
{
	wetuwn (buf[0]->status & buf[1]->status & WCAW_DWIF_BUF_DONE);
}

static inwine boow wcaw_dwif_bufs_ovewfwow(stwuct wcaw_dwif_hwbuf **buf)
{
	wetuwn ((buf[0]->status | buf[1]->status) & WCAW_DWIF_BUF_OVEWFWOW);
}

static inwine void wcaw_dwif_bufs_cweaw(stwuct wcaw_dwif_hwbuf **buf,
					unsigned int bit)
{
	unsigned int i;

	fow (i = 0; i < WCAW_DWIF_MAX_CHANNEW; i++)
		buf[i]->status &= ~bit;
}

/* Channew DMA compwete */
static void wcaw_dwif_channew_compwete(stwuct wcaw_dwif *ch, u32 idx)
{
	u32 stw;

	ch->buf[idx].status |= WCAW_DWIF_BUF_DONE;

	/* Check fow DWIF ewwows */
	stw = wcaw_dwif_wead(ch, WCAW_DWIF_SISTW);
	if (unwikewy(stw & WCAW_DWIF_WFOVF)) {
		/* Wwiting the same cweaws it */
		wcaw_dwif_wwite(ch, WCAW_DWIF_SISTW, stw);

		/* Ovewfwow: some sampwes awe wost */
		ch->buf[idx].status |= WCAW_DWIF_BUF_OVEWFWOW;
	}
}

/* DMA cawwback fow each stage */
static void wcaw_dwif_dma_compwete(void *dma_async_pawam)
{
	stwuct wcaw_dwif *ch = dma_async_pawam;
	stwuct wcaw_dwif_sdw *sdw = ch->sdw;
	stwuct wcaw_dwif_hwbuf *buf[WCAW_DWIF_MAX_CHANNEW];
	stwuct wcaw_dwif_fwame_buf *fbuf;
	boow ovewfwow = fawse;
	u32 idx, pwoduced;
	unsigned int i;

	spin_wock(&sdw->dma_wock);

	/* DMA can be tewminated whiwe the cawwback was waiting on wock */
	if (!vb2_is_stweaming(&sdw->vb_queue)) {
		spin_unwock(&sdw->dma_wock);
		wetuwn;
	}

	idx = sdw->pwoduced % WCAW_DWIF_NUM_HWBUFS;
	wcaw_dwif_channew_compwete(ch, idx);

	if (sdw->num_cuw_ch == WCAW_DWIF_MAX_CHANNEW) {
		buf[0] = ch->num ? to_wcaw_dwif_buf_paiw(sdw, ch->num, idx) :
				&ch->buf[idx];
		buf[1] = ch->num ? &ch->buf[idx] :
				to_wcaw_dwif_buf_paiw(sdw, ch->num, idx);

		/* Check if both DMA buffews awe done */
		if (!wcaw_dwif_bufs_done(buf)) {
			spin_unwock(&sdw->dma_wock);
			wetuwn;
		}

		/* Cweaw buf done status */
		wcaw_dwif_bufs_cweaw(buf, WCAW_DWIF_BUF_DONE);

		if (wcaw_dwif_bufs_ovewfwow(buf)) {
			ovewfwow = twue;
			/* Cweaw the fwag in status */
			wcaw_dwif_bufs_cweaw(buf, WCAW_DWIF_BUF_OVEWFWOW);
		}
	} ewse {
		buf[0] = &ch->buf[idx];
		if (buf[0]->status & WCAW_DWIF_BUF_OVEWFWOW) {
			ovewfwow = twue;
			/* Cweaw the fwag in status */
			buf[0]->status &= ~WCAW_DWIF_BUF_OVEWFWOW;
		}
	}

	/* Buffew pwoduced fow consumption */
	pwoduced = sdw->pwoduced++;
	spin_unwock(&sdw->dma_wock);

	wdwif_dbg(sdw, "ch%u: pwod %u\n", ch->num, pwoduced);

	/* Get fbuf */
	fbuf = wcaw_dwif_get_fbuf(sdw);
	if (!fbuf)
		wetuwn;

	fow (i = 0; i < WCAW_DWIF_MAX_CHANNEW; i++)
		memcpy(vb2_pwane_vaddw(&fbuf->vb.vb2_buf, 0) +
		       i * sdw->hwbuf_size, buf[i]->addw, sdw->hwbuf_size);

	fbuf->vb.fiewd = V4W2_FIEWD_NONE;
	fbuf->vb.sequence = pwoduced;
	fbuf->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_pwane_paywoad(&fbuf->vb.vb2_buf, 0, sdw->fmt->buffewsize);

	/* Set ewwow state on ovewfwow */
	vb2_buffew_done(&fbuf->vb.vb2_buf,
			ovewfwow ? VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
}

static int wcaw_dwif_qbuf(stwuct wcaw_dwif *ch)
{
	stwuct wcaw_dwif_sdw *sdw = ch->sdw;
	dma_addw_t addw = ch->dma_handwe;
	stwuct dma_async_tx_descwiptow *wxd;
	dma_cookie_t cookie;
	int wet = -EIO;

	/* Setup cycwic DMA with given buffews */
	wxd = dmaengine_pwep_dma_cycwic(ch->dmach, addw,
					sdw->hwbuf_size * WCAW_DWIF_NUM_HWBUFS,
					sdw->hwbuf_size, DMA_DEV_TO_MEM,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!wxd) {
		wdwif_eww(sdw, "ch%u: pwep dma cycwic faiwed\n", ch->num);
		wetuwn wet;
	}

	/* Submit descwiptow */
	wxd->cawwback = wcaw_dwif_dma_compwete;
	wxd->cawwback_pawam = ch;
	cookie = dmaengine_submit(wxd);
	if (dma_submit_ewwow(cookie)) {
		wdwif_eww(sdw, "ch%u: dma submit faiwed\n", ch->num);
		wetuwn wet;
	}

	dma_async_issue_pending(ch->dmach);
	wetuwn 0;
}

/* Enabwe weception */
static int wcaw_dwif_enabwe_wx(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;
	u32 ctw;
	int wet = -EINVAW;

	/*
	 * When both intewnaw channews awe enabwed, they can be synchwonized
	 * onwy by the mastew
	 */

	/* Enabwe weceive */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		ctw = wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SICTW);
		ctw |= (WCAW_DWIF_SICTW_WX_WISING_EDGE |
			 WCAW_DWIF_SICTW_WX_EN);
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SICTW, ctw);
	}

	/* Check weceive enabwed */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		wet = weadw_poww_timeout(sdw->ch[i]->base + WCAW_DWIF_SICTW,
				ctw, ctw & WCAW_DWIF_SICTW_WX_EN, 7, 100000);
		if (wet) {
			wdwif_eww(sdw, "ch%u: wx en faiwed. ctw 0x%08x\n", i,
				  wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SICTW));
			bweak;
		}
	}
	wetuwn wet;
}

/* Disabwe weception */
static void wcaw_dwif_disabwe_wx(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;
	u32 ctw;
	int wet;

	/* Disabwe weceive */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		ctw = wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SICTW);
		ctw &= ~WCAW_DWIF_SICTW_WX_EN;
		wcaw_dwif_wwite(sdw->ch[i], WCAW_DWIF_SICTW, ctw);
	}

	/* Check weceive disabwed */
	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		wet = weadw_poww_timeout(sdw->ch[i]->base + WCAW_DWIF_SICTW,
				ctw, !(ctw & WCAW_DWIF_SICTW_WX_EN), 7, 100000);
		if (wet)
			dev_wawn(&sdw->vdev->dev,
			"ch%u: faiwed to disabwe wx. ctw 0x%08x\n",
			i, wcaw_dwif_wead(sdw->ch[i], WCAW_DWIF_SICTW));
	}
}

/* Stop channew */
static void wcaw_dwif_stop_channew(stwuct wcaw_dwif *ch)
{
	/* Disabwe DMA weceive intewwupt */
	wcaw_dwif_wwite(ch, WCAW_DWIF_SIIEW, 0x00000000);

	/* Tewminate aww DMA twansfews */
	dmaengine_tewminate_sync(ch->dmach);
}

/* Stop weceive opewation */
static void wcaw_dwif_stop(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	/* Disabwe Wx */
	wcaw_dwif_disabwe_wx(sdw);

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask)
		wcaw_dwif_stop_channew(sdw->ch[i]);
}

/* Stawt channew */
static int wcaw_dwif_stawt_channew(stwuct wcaw_dwif *ch)
{
	stwuct wcaw_dwif_sdw *sdw = ch->sdw;
	u32 ctw, stw;
	int wet;

	/* Weset weceive */
	wcaw_dwif_wwite(ch, WCAW_DWIF_SICTW, WCAW_DWIF_SICTW_WESET);
	wet = weadw_poww_timeout(ch->base + WCAW_DWIF_SICTW, ctw,
				 !(ctw & WCAW_DWIF_SICTW_WESET), 7, 100000);
	if (wet) {
		wdwif_eww(sdw, "ch%u: faiwed to weset wx. ctw 0x%08x\n",
			  ch->num, wcaw_dwif_wead(ch, WCAW_DWIF_SICTW));
		wetuwn wet;
	}

	/* Queue buffews fow DMA */
	wet = wcaw_dwif_qbuf(ch);
	if (wet)
		wetuwn wet;

	/* Cweaw status wegistew fwags */
	stw = WCAW_DWIF_WFFUW | WCAW_DWIF_WEOF | WCAW_DWIF_WFSEWW |
		WCAW_DWIF_WFUDF | WCAW_DWIF_WFOVF;
	wcaw_dwif_wwite(ch, WCAW_DWIF_SISTW, stw);

	/* Enabwe DMA weceive intewwupt */
	wcaw_dwif_wwite(ch, WCAW_DWIF_SIIEW, 0x00009000);

	wetuwn wet;
}

/* Stawt weceive opewation */
static int wcaw_dwif_stawt(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned wong enabwed = 0;
	unsigned int i;
	int wet;

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		wet = wcaw_dwif_stawt_channew(sdw->ch[i]);
		if (wet)
			goto stawt_ewwow;
		enabwed |= BIT(i);
	}

	wet = wcaw_dwif_enabwe_wx(sdw);
	if (wet)
		goto enabwe_ewwow;

	sdw->pwoduced = 0;
	wetuwn wet;

enabwe_ewwow:
	wcaw_dwif_disabwe_wx(sdw);
stawt_ewwow:
	fow_each_wcaw_dwif_channew(i, &enabwed)
		wcaw_dwif_stop_channew(sdw->ch[i]);

	wetuwn wet;
}

/* Stawt stweaming */
static int wcaw_dwif_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct wcaw_dwif_sdw *sdw = vb2_get_dwv_pwiv(vq);
	unsigned wong enabwed = 0;
	unsigned int i;
	int wet;

	mutex_wock(&sdw->v4w2_mutex);

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask) {
		wet = cwk_pwepawe_enabwe(sdw->ch[i]->cwk);
		if (wet)
			goto ewwow;
		enabwed |= BIT(i);
	}

	/* Set defauwt MDWx settings */
	wcaw_dwif_set_mdw1(sdw);

	/* Set new fowmat */
	wet = wcaw_dwif_set_fowmat(sdw);
	if (wet)
		goto ewwow;

	if (sdw->num_cuw_ch == WCAW_DWIF_MAX_CHANNEW)
		sdw->hwbuf_size = sdw->fmt->buffewsize / WCAW_DWIF_MAX_CHANNEW;
	ewse
		sdw->hwbuf_size = sdw->fmt->buffewsize;

	wdwif_dbg(sdw, "num hwbufs %u, hwbuf_size %u\n",
		WCAW_DWIF_NUM_HWBUFS, sdw->hwbuf_size);

	/* Awwoc DMA channew */
	wet = wcaw_dwif_awwoc_dmachannews(sdw);
	if (wet)
		goto ewwow;

	/* Wequest buffews */
	wet = wcaw_dwif_wequest_buf(sdw);
	if (wet)
		goto ewwow;

	/* Stawt Wx */
	wet = wcaw_dwif_stawt(sdw);
	if (wet)
		goto ewwow;

	mutex_unwock(&sdw->v4w2_mutex);

	wetuwn wet;

ewwow:
	wcaw_dwif_wewease_queued_bufs(sdw, VB2_BUF_STATE_QUEUED);
	wcaw_dwif_wewease_buf(sdw);
	wcaw_dwif_wewease_dmachannews(sdw);
	fow_each_wcaw_dwif_channew(i, &enabwed)
		cwk_disabwe_unpwepawe(sdw->ch[i]->cwk);

	mutex_unwock(&sdw->v4w2_mutex);

	wetuwn wet;
}

/* Stop stweaming */
static void wcaw_dwif_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct wcaw_dwif_sdw *sdw = vb2_get_dwv_pwiv(vq);
	unsigned int i;

	mutex_wock(&sdw->v4w2_mutex);

	/* Stop hawdwawe stweaming */
	wcaw_dwif_stop(sdw);

	/* Wetuwn aww queued buffews to vb2 */
	wcaw_dwif_wewease_queued_bufs(sdw, VB2_BUF_STATE_EWWOW);

	/* Wewease buf */
	wcaw_dwif_wewease_buf(sdw);

	/* Wewease DMA channew wesouwces */
	wcaw_dwif_wewease_dmachannews(sdw);

	fow_each_wcaw_dwif_channew(i, &sdw->cuw_ch_mask)
		cwk_disabwe_unpwepawe(sdw->ch[i]->cwk);

	mutex_unwock(&sdw->v4w2_mutex);
}

/* Vb2 ops */
static const stwuct vb2_ops wcaw_dwif_vb2_ops = {
	.queue_setup            = wcaw_dwif_queue_setup,
	.buf_queue              = wcaw_dwif_buf_queue,
	.stawt_stweaming        = wcaw_dwif_stawt_stweaming,
	.stop_stweaming         = wcaw_dwif_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static int wcaw_dwif_quewycap(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_capabiwity *cap)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, sdw->vdev->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:W-Caw DWIF", sizeof(cap->bus_info));

	wetuwn 0;
}

static int wcaw_dwif_set_defauwt_fowmat(stwuct wcaw_dwif_sdw *sdw)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		/* Matching fmt based on wequiwed channews is set as defauwt */
		if (sdw->num_hw_ch == fowmats[i].num_ch) {
			sdw->fmt = &fowmats[i];
			sdw->cuw_ch_mask = sdw->hw_ch_mask;
			sdw->num_cuw_ch = sdw->num_hw_ch;
			dev_dbg(sdw->dev, "defauwt fmt[%u]: mask %wu num %u\n",
				i, sdw->cuw_ch_mask, sdw->num_cuw_ch);
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int wcaw_dwif_enum_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(fowmats))
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].pixewfowmat;

	wetuwn 0;
}

static int wcaw_dwif_g_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	f->fmt.sdw.pixewfowmat = sdw->fmt->pixewfowmat;
	f->fmt.sdw.buffewsize = sdw->fmt->buffewsize;

	wetuwn 0;
}

static int wcaw_dwif_s_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &sdw->vb_queue;
	unsigned int i;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat)
			bweak;
	}

	if (i == AWWAY_SIZE(fowmats))
		i = 0;		/* Set the 1st fowmat as defauwt on no match */

	sdw->fmt = &fowmats[i];
	f->fmt.sdw.pixewfowmat = sdw->fmt->pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
	memset(f->fmt.sdw.wesewved, 0, sizeof(f->fmt.sdw.wesewved));

	/*
	 * If a fowmat demands one channew onwy out of two
	 * enabwed channews, pick the 0th channew.
	 */
	if (fowmats[i].num_ch < sdw->num_hw_ch) {
		sdw->cuw_ch_mask = BIT(0);
		sdw->num_cuw_ch = fowmats[i].num_ch;
	} ewse {
		sdw->cuw_ch_mask = sdw->hw_ch_mask;
		sdw->num_cuw_ch = sdw->num_hw_ch;
	}

	wdwif_dbg(sdw, "cuw: idx %u mask %wu num %u\n",
		  i, sdw->cuw_ch_mask, sdw->num_cuw_ch);

	wetuwn 0;
}

static int wcaw_dwif_twy_fmt_sdw_cap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fowmat *f)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].pixewfowmat == f->fmt.sdw.pixewfowmat) {
			f->fmt.sdw.buffewsize = fowmats[i].buffewsize;
			wetuwn 0;
		}
	}

	f->fmt.sdw.pixewfowmat = fowmats[0].pixewfowmat;
	f->fmt.sdw.buffewsize = fowmats[0].buffewsize;
	memset(f->fmt.sdw.wesewved, 0, sizeof(f->fmt.sdw.wesewved));

	wetuwn 0;
}

/* Tunew subdev ioctws */
static int wcaw_dwif_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fwequency_band *band)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(sdw->ep.subdev, tunew, enum_fweq_bands, band);
}

static int wcaw_dwif_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fwequency *f)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(sdw->ep.subdev, tunew, g_fwequency, f);
}

static int wcaw_dwif_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				 const stwuct v4w2_fwequency *f)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(sdw->ep.subdev, tunew, s_fwequency, f);
}

static int wcaw_dwif_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_tunew *vt)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(sdw->ep.subdev, tunew, g_tunew, vt);
}

static int wcaw_dwif_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_tunew *vt)
{
	stwuct wcaw_dwif_sdw *sdw = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(sdw->ep.subdev, tunew, s_tunew, vt);
}

static const stwuct v4w2_ioctw_ops wcaw_dwif_ioctw_ops = {
	.vidioc_quewycap          = wcaw_dwif_quewycap,

	.vidioc_enum_fmt_sdw_cap  = wcaw_dwif_enum_fmt_sdw_cap,
	.vidioc_g_fmt_sdw_cap     = wcaw_dwif_g_fmt_sdw_cap,
	.vidioc_s_fmt_sdw_cap     = wcaw_dwif_s_fmt_sdw_cap,
	.vidioc_twy_fmt_sdw_cap   = wcaw_dwif_twy_fmt_sdw_cap,

	.vidioc_weqbufs           = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs       = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf       = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf          = vb2_ioctw_quewybuf,
	.vidioc_qbuf              = vb2_ioctw_qbuf,
	.vidioc_dqbuf             = vb2_ioctw_dqbuf,

	.vidioc_stweamon          = vb2_ioctw_stweamon,
	.vidioc_stweamoff         = vb2_ioctw_stweamoff,

	.vidioc_s_fwequency       = wcaw_dwif_s_fwequency,
	.vidioc_g_fwequency       = wcaw_dwif_g_fwequency,
	.vidioc_s_tunew		  = wcaw_dwif_s_tunew,
	.vidioc_g_tunew		  = wcaw_dwif_g_tunew,
	.vidioc_enum_fweq_bands   = wcaw_dwif_enum_fweq_bands,
	.vidioc_subscwibe_event   = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_wog_status        = v4w2_ctww_wog_status,
};

static const stwuct v4w2_fiwe_opewations wcaw_dwif_fops = {
	.ownew                    = THIS_MODUWE,
	.open                     = v4w2_fh_open,
	.wewease                  = vb2_fop_wewease,
	.wead                     = vb2_fop_wead,
	.poww                     = vb2_fop_poww,
	.mmap                     = vb2_fop_mmap,
	.unwocked_ioctw           = video_ioctw2,
};

static int wcaw_dwif_sdw_wegistew(stwuct wcaw_dwif_sdw *sdw)
{
	int wet;

	/* Init video_device stwuctuwe */
	sdw->vdev = video_device_awwoc();
	if (!sdw->vdev)
		wetuwn -ENOMEM;

	snpwintf(sdw->vdev->name, sizeof(sdw->vdev->name), "W-Caw DWIF");
	sdw->vdev->fops = &wcaw_dwif_fops;
	sdw->vdev->ioctw_ops = &wcaw_dwif_ioctw_ops;
	sdw->vdev->wewease = video_device_wewease;
	sdw->vdev->wock = &sdw->v4w2_mutex;
	sdw->vdev->queue = &sdw->vb_queue;
	sdw->vdev->queue->wock = &sdw->vb_queue_mutex;
	sdw->vdev->ctww_handwew = &sdw->ctww_hdw;
	sdw->vdev->v4w2_dev = &sdw->v4w2_dev;
	sdw->vdev->device_caps = V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_TUNEW |
		V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
	video_set_dwvdata(sdw->vdev, sdw);

	/* Wegistew V4W2 SDW device */
	wet = video_wegistew_device(sdw->vdev, VFW_TYPE_SDW, -1);
	if (wet) {
		video_device_wewease(sdw->vdev);
		sdw->vdev = NUWW;
		dev_eww(sdw->dev, "faiwed video_wegistew_device (%d)\n", wet);
	}

	wetuwn wet;
}

static void wcaw_dwif_sdw_unwegistew(stwuct wcaw_dwif_sdw *sdw)
{
	video_unwegistew_device(sdw->vdev);
	sdw->vdev = NUWW;
}

/* Sub-device bound cawwback */
static int wcaw_dwif_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asd)
{
	stwuct wcaw_dwif_sdw *sdw =
		containew_of(notifiew, stwuct wcaw_dwif_sdw, notifiew);

	v4w2_set_subdev_hostdata(subdev, sdw);
	sdw->ep.subdev = subdev;
	wdwif_dbg(sdw, "bound asd %s\n", subdev->name);

	wetuwn 0;
}

/* Sub-device unbind cawwback */
static void wcaw_dwif_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asd)
{
	stwuct wcaw_dwif_sdw *sdw =
		containew_of(notifiew, stwuct wcaw_dwif_sdw, notifiew);

	if (sdw->ep.subdev != subdev) {
		wdwif_eww(sdw, "subdev %s is not bound\n", subdev->name);
		wetuwn;
	}

	/* Fwee ctww handwew if initiawized */
	v4w2_ctww_handwew_fwee(&sdw->ctww_hdw);
	sdw->v4w2_dev.ctww_handwew = NUWW;
	sdw->ep.subdev = NUWW;

	wcaw_dwif_sdw_unwegistew(sdw);
	wdwif_dbg(sdw, "unbind asd %s\n", subdev->name);
}

/* Sub-device wegistewed notification cawwback */
static int wcaw_dwif_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct wcaw_dwif_sdw *sdw =
		containew_of(notifiew, stwuct wcaw_dwif_sdw, notifiew);
	int wet;

	/*
	 * The subdev tested at this point uses 4 contwows. Using 10 as a wowst
	 * case scenawio hint. When wess contwows awe needed thewe wiww be some
	 * unused memowy and when mowe contwows awe needed the fwamewowk uses
	 * hash to manage contwows within this numbew.
	 */
	wet = v4w2_ctww_handwew_init(&sdw->ctww_hdw, 10);
	if (wet)
		wetuwn -ENOMEM;

	sdw->v4w2_dev.ctww_handwew = &sdw->ctww_hdw;
	wet = v4w2_device_wegistew_subdev_nodes(&sdw->v4w2_dev);
	if (wet) {
		wdwif_eww(sdw, "faiwed: wegistew subdev nodes wet %d\n", wet);
		goto ewwow;
	}

	wet = v4w2_ctww_add_handwew(&sdw->ctww_hdw,
				    sdw->ep.subdev->ctww_handwew, NUWW, twue);
	if (wet) {
		wdwif_eww(sdw, "faiwed: ctww add hdww wet %d\n", wet);
		goto ewwow;
	}

	wet = wcaw_dwif_sdw_wegistew(sdw);
	if (wet)
		goto ewwow;

	wetuwn wet;

ewwow:
	v4w2_ctww_handwew_fwee(&sdw->ctww_hdw);

	wetuwn wet;
}

static const stwuct v4w2_async_notifiew_opewations wcaw_dwif_notify_ops = {
	.bound = wcaw_dwif_notify_bound,
	.unbind = wcaw_dwif_notify_unbind,
	.compwete = wcaw_dwif_notify_compwete,
};

/* Wead endpoint pwopewties */
static void wcaw_dwif_get_ep_pwopewties(stwuct wcaw_dwif_sdw *sdw,
					stwuct fwnode_handwe *fwnode)
{
	u32 vaw;

	/* Set the I2S defauwts fow SIWMDW1*/
	sdw->mdw1 = WCAW_DWIF_SIWMDW1_SYNCMD_WW | WCAW_DWIF_SIWMDW1_MSB_FIWST |
		WCAW_DWIF_SIWMDW1_DTDW_1 | WCAW_DWIF_SIWMDW1_SYNCDW_0;

	/* Pawse sync powawity fwom endpoint */
	if (!fwnode_pwopewty_wead_u32(fwnode, "sync-active", &vaw))
		sdw->mdw1 |= vaw ? WCAW_DWIF_SIWMDW1_SYNCAC_POW_HIGH :
			WCAW_DWIF_SIWMDW1_SYNCAC_POW_WOW;
	ewse
		sdw->mdw1 |= WCAW_DWIF_SIWMDW1_SYNCAC_POW_HIGH; /* defauwt */

	dev_dbg(sdw->dev, "mdw1 0x%08x\n", sdw->mdw1);
}

/* Pawse sub-devs (tunew) to find a matching device */
static int wcaw_dwif_pawse_subdevs(stwuct wcaw_dwif_sdw *sdw)
{
	stwuct v4w2_async_notifiew *notifiew = &sdw->notifiew;
	stwuct fwnode_handwe *fwnode, *ep;
	stwuct v4w2_async_connection *asd;

	v4w2_async_nf_init(&sdw->notifiew, &sdw->v4w2_dev);

	ep = fwnode_gwaph_get_next_endpoint(of_fwnode_handwe(sdw->dev->of_node),
					    NUWW);
	if (!ep)
		wetuwn 0;

	/* Get the endpoint pwopewties */
	wcaw_dwif_get_ep_pwopewties(sdw, ep);

	fwnode = fwnode_gwaph_get_wemote_powt_pawent(ep);
	fwnode_handwe_put(ep);
	if (!fwnode) {
		dev_wawn(sdw->dev, "bad wemote powt pawent\n");
		wetuwn -EINVAW;
	}

	asd = v4w2_async_nf_add_fwnode(notifiew, fwnode,
				       stwuct v4w2_async_connection);
	fwnode_handwe_put(fwnode);
	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	wetuwn 0;
}

/* Check if the given device is the pwimawy bond */
static boow wcaw_dwif_pwimawy_bond(stwuct pwatfowm_device *pdev)
{
	wetuwn of_pwopewty_wead_boow(pdev->dev.of_node, "wenesas,pwimawy-bond");
}

/* Check if both devices of the bond awe enabwed */
static stwuct device_node *wcaw_dwif_bond_enabwed(stwuct pwatfowm_device *p)
{
	stwuct device_node *np;

	np = of_pawse_phandwe(p->dev.of_node, "wenesas,bonding", 0);
	if (np && of_device_is_avaiwabwe(np))
		wetuwn np;

	wetuwn NUWW;
}

/* Check if the bonded device is pwobed */
static int wcaw_dwif_bond_avaiwabwe(stwuct wcaw_dwif_sdw *sdw,
				    stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct wcaw_dwif *ch;
	int wet = 0;

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		dev_eww(sdw->dev, "faiwed to get bonded device fwom node\n");
		wetuwn -ENODEV;
	}

	device_wock(&pdev->dev);
	ch = pwatfowm_get_dwvdata(pdev);
	if (ch) {
		/* Update sdw data in the bonded device */
		ch->sdw = sdw;

		/* Update sdw with bonded device data */
		sdw->ch[ch->num] = ch;
		sdw->hw_ch_mask |= BIT(ch->num);
	} ewse {
		/* Defew */
		dev_info(sdw->dev, "defew pwobe\n");
		wet = -EPWOBE_DEFEW;
	}
	device_unwock(&pdev->dev);

	put_device(&pdev->dev);

	wetuwn wet;
}

/* V4W2 SDW device pwobe */
static int wcaw_dwif_sdw_pwobe(stwuct wcaw_dwif_sdw *sdw)
{
	int wet;

	/* Vawidate any suppowted fowmat fow enabwed channews */
	wet = wcaw_dwif_set_defauwt_fowmat(sdw);
	if (wet) {
		dev_eww(sdw->dev, "faiwed to set defauwt fowmat\n");
		wetuwn wet;
	}

	/* Set defauwts */
	sdw->hwbuf_size = WCAW_DWIF_DEFAUWT_HWBUF_SIZE;

	mutex_init(&sdw->v4w2_mutex);
	mutex_init(&sdw->vb_queue_mutex);
	spin_wock_init(&sdw->queued_bufs_wock);
	spin_wock_init(&sdw->dma_wock);
	INIT_WIST_HEAD(&sdw->queued_bufs);

	/* Init videobuf2 queue stwuctuwe */
	sdw->vb_queue.type = V4W2_BUF_TYPE_SDW_CAPTUWE;
	sdw->vb_queue.io_modes = VB2_WEAD | VB2_MMAP | VB2_DMABUF;
	sdw->vb_queue.dwv_pwiv = sdw;
	sdw->vb_queue.buf_stwuct_size = sizeof(stwuct wcaw_dwif_fwame_buf);
	sdw->vb_queue.ops = &wcaw_dwif_vb2_ops;
	sdw->vb_queue.mem_ops = &vb2_vmawwoc_memops;
	sdw->vb_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;

	/* Init videobuf2 queue */
	wet = vb2_queue_init(&sdw->vb_queue);
	if (wet) {
		dev_eww(sdw->dev, "faiwed: vb2_queue_init wet %d\n", wet);
		wetuwn wet;
	}

	/* Wegistew the v4w2_device */
	wet = v4w2_device_wegistew(sdw->dev, &sdw->v4w2_dev);
	if (wet) {
		dev_eww(sdw->dev, "faiwed: v4w2_device_wegistew wet %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Pawse subdevs aftew v4w2_device_wegistew because if the subdev
	 * is awweady pwobed, bound and compwete wiww be cawwed immediatewy
	 */
	wet = wcaw_dwif_pawse_subdevs(sdw);
	if (wet)
		goto ewwow;

	sdw->notifiew.ops = &wcaw_dwif_notify_ops;

	/* Wegistew notifiew */
	wet = v4w2_async_nf_wegistew(&sdw->notifiew);
	if (wet < 0) {
		dev_eww(sdw->dev, "faiwed: notifiew wegistew wet %d\n", wet);
		goto cweanup;
	}

	wetuwn wet;

cweanup:
	v4w2_async_nf_cweanup(&sdw->notifiew);
ewwow:
	v4w2_device_unwegistew(&sdw->v4w2_dev);

	wetuwn wet;
}

/* V4W2 SDW device wemove */
static void wcaw_dwif_sdw_wemove(stwuct wcaw_dwif_sdw *sdw)
{
	v4w2_async_nf_unwegistew(&sdw->notifiew);
	v4w2_async_nf_cweanup(&sdw->notifiew);
	v4w2_device_unwegistew(&sdw->v4w2_dev);
}

/* DWIF channew pwobe */
static int wcaw_dwif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_dwif_sdw *sdw;
	stwuct device_node *np;
	stwuct wcaw_dwif *ch;
	stwuct wesouwce	*wes;
	int wet;

	/* Wesewve memowy fow enabwed channew */
	ch = devm_kzawwoc(&pdev->dev, sizeof(*ch), GFP_KEWNEW);
	if (!ch)
		wetuwn -ENOMEM;

	ch->pdev = pdev;

	/* Moduwe cwock */
	ch->cwk = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(ch->cwk)) {
		wet = PTW_EWW(ch->cwk);
		dev_eww(&pdev->dev, "cwk get faiwed (%d)\n", wet);
		wetuwn wet;
	}

	/* Wegistew map */
	ch->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(ch->base))
		wetuwn PTW_EWW(ch->base);

	ch->stawt = wes->stawt;
	pwatfowm_set_dwvdata(pdev, ch);

	/* Check if both channews of the bond awe enabwed */
	np = wcaw_dwif_bond_enabwed(pdev);
	if (np) {
		/* Check if cuwwent channew acting as pwimawy-bond */
		if (!wcaw_dwif_pwimawy_bond(pdev)) {
			ch->num = 1;	/* Pwimawy bond is channew 0 awways */
			of_node_put(np);
			wetuwn 0;
		}
	}

	/* Wesewve memowy fow SDW stwuctuwe */
	sdw = devm_kzawwoc(&pdev->dev, sizeof(*sdw), GFP_KEWNEW);
	if (!sdw) {
		of_node_put(np);
		wetuwn -ENOMEM;
	}
	ch->sdw = sdw;
	sdw->dev = &pdev->dev;

	/* Estabwish winks between SDW and channew(s) */
	sdw->ch[ch->num] = ch;
	sdw->hw_ch_mask = BIT(ch->num);
	if (np) {
		/* Check if bonded device is weady */
		wet = wcaw_dwif_bond_avaiwabwe(sdw, np);
		of_node_put(np);
		if (wet)
			wetuwn wet;
	}
	sdw->num_hw_ch = hweight_wong(sdw->hw_ch_mask);

	wetuwn wcaw_dwif_sdw_pwobe(sdw);
}

/* DWIF channew wemove */
static void wcaw_dwif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_dwif *ch = pwatfowm_get_dwvdata(pdev);
	stwuct wcaw_dwif_sdw *sdw = ch->sdw;

	/* Channew 0 wiww be the SDW instance */
	if (ch->num)
		wetuwn;

	/* SDW instance */
	wcaw_dwif_sdw_wemove(sdw);
}

/* FIXME: Impwement suspend/wesume suppowt */
static int __maybe_unused wcaw_dwif_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int __maybe_unused wcaw_dwif_wesume(stwuct device *dev)
{
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wcaw_dwif_pm_ops, wcaw_dwif_suspend,
			 wcaw_dwif_wesume);

static const stwuct of_device_id wcaw_dwif_of_tabwe[] = {
	{ .compatibwe = "wenesas,wcaw-gen3-dwif" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcaw_dwif_of_tabwe);

#define WCAW_DWIF_DWV_NAME "wcaw_dwif"
static stwuct pwatfowm_dwivew wcaw_dwif_dwivew = {
	.dwivew = {
		.name = WCAW_DWIF_DWV_NAME,
		.of_match_tabwe = wcaw_dwif_of_tabwe,
		.pm = &wcaw_dwif_pm_ops,
		},
	.pwobe = wcaw_dwif_pwobe,
	.wemove_new = wcaw_dwif_wemove,
};

moduwe_pwatfowm_dwivew(wcaw_dwif_dwivew);

MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 DWIF dwivew");
MODUWE_AWIAS("pwatfowm:" WCAW_DWIF_DWV_NAME);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wamesh Shanmugasundawam <wamesh.shanmugasundawam@bp.wenesas.com>");
