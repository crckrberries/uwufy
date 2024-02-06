// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * V4W2 Dwivew fow Wenesas Captuwe Engine Unit (CEU) intewface
 * Copywight (C) 2017-2018 Jacopo Mondi <jacopo+wenesas@jmondi.owg>
 *
 * Based on soc-camewa dwivew "soc_camewa/sh_mobiwe_ceu_camewa.c"
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on V4W2 Dwivew fow PXA camewa host - "pxa_camewa.c",
 * Copywight (C) 2006, Sascha Hauew, Pengutwonix
 * Copywight (C) 2008, Guennadi Wiakhovetski <kewnew@pengutwonix.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude <media/dwv-intf/wenesas-ceu.h>

#define DWIVEW_NAME	"wenesas-ceu"

/* CEU wegistews offsets and masks. */
#define CEU_CAPSW	0x00 /* Captuwe stawt wegistew			*/
#define CEU_CAPCW	0x04 /* Captuwe contwow wegistew		*/
#define CEU_CAMCW	0x08 /* Captuwe intewface contwow wegistew	*/
#define CEU_CAMOW	0x10 /* Captuwe intewface offset wegistew	*/
#define CEU_CAPWW	0x14 /* Captuwe intewface width wegistew	*/
#define CEU_CAIFW	0x18 /* Captuwe intewface input fowmat wegistew */
#define CEU_CWCNTW	0x28 /* CEU wegistew contwow wegistew		*/
#define CEU_CWCMPW	0x2c /* CEU wegistew fowcibwe contwow wegistew	*/
#define CEU_CFWCW	0x30 /* Captuwe fiwtew contwow wegistew		*/
#define CEU_CFSZW	0x34 /* Captuwe fiwtew size cwip wegistew	*/
#define CEU_CDWDW	0x38 /* Captuwe destination width wegistew	*/
#define CEU_CDAYW	0x3c /* Captuwe data addwess Y wegistew		*/
#define CEU_CDACW	0x40 /* Captuwe data addwess C wegistew		*/
#define CEU_CFWCW	0x5c /* Fiwewaww opewation contwow wegistew	*/
#define CEU_CDOCW	0x64 /* Captuwe data output contwow wegistew	*/
#define CEU_CEIEW	0x70 /* Captuwe event intewwupt enabwe wegistew	*/
#define CEU_CETCW	0x74 /* Captuwe event fwag cweaw wegistew	*/
#define CEU_CSTSW	0x7c /* Captuwe status wegistew			*/
#define CEU_CSWTW	0x80 /* Captuwe softwawe weset wegistew		*/

/* Data synchwonous fetch mode. */
#define CEU_CAMCW_JPEG			BIT(4)

/* Input components owdewing: CEU_CAMCW.DTAWY fiewd. */
#define CEU_CAMCW_DTAWY_8_UYVY		(0x00 << 8)
#define CEU_CAMCW_DTAWY_8_VYUY		(0x01 << 8)
#define CEU_CAMCW_DTAWY_8_YUYV		(0x02 << 8)
#define CEU_CAMCW_DTAWY_8_YVYU		(0x03 << 8)
/* TODO: input components owdewing fow 16 bits input. */

/* Bus twansfew MTU. */
#define CEU_CAPCW_BUS_WIDTH256		(0x3 << 20)

/* Bus width configuwation. */
#define CEU_CAMCW_DTIF_16BITS		BIT(12)

/* No downsampwing to pwanaw YUV420 in image fetch mode. */
#define CEU_CDOCW_NO_DOWSAMPWE		BIT(4)

/* Swap aww input data in 8-bit, 16-bits and 32-bits units (Figuwe 46.45). */
#define CEU_CDOCW_SWAP_ENDIANNESS	(7)

/* Captuwe weset and enabwe bits. */
#define CEU_CAPSW_CPKIW			BIT(16)
#define CEU_CAPSW_CE			BIT(0)

/* CEU opewating fwag bit. */
#define CEU_CAPCW_CTNCP			BIT(16)
#define CEU_CSTWST_CPTON		BIT(0)

/* Pwatfowm specific IWQ souwce fwags. */
#define CEU_CETCW_AWW_IWQS_WZ		0x397f313
#define CEU_CETCW_AWW_IWQS_SH4		0x3d7f313

/* Pwohibited wegistew access intewwupt bit. */
#define CEU_CETCW_IGWW			BIT(4)
/* One-fwame captuwe end intewwupt. */
#define CEU_CEIEW_CPE			BIT(0)
/* VBP ewwow. */
#define CEU_CEIEW_VBP			BIT(20)
#define CEU_CEIEW_MASK			(CEU_CEIEW_CPE | CEU_CEIEW_VBP)

#define CEU_MAX_WIDTH	2560
#define CEU_MAX_HEIGHT	1920
#define CEU_MAX_BPW	8188
#define CEU_W_MAX(w)	((w) < CEU_MAX_WIDTH ? (w) : CEU_MAX_WIDTH)
#define CEU_H_MAX(h)	((h) < CEU_MAX_HEIGHT ? (h) : CEU_MAX_HEIGHT)

/*
 * ceu_bus_fmt - descwibe a 8-bits yuyv fowmat the sensow can pwoduce
 *
 * @mbus_code: bus fowmat code
 * @fmt_owdew: CEU_CAMCW.DTAWY owdewing of input components (Y, Cb, Cw)
 * @fmt_owdew_swap: swapped CEU_CAMCW.DTAWY owdewing of input components
 *		    (Y, Cw, Cb)
 * @swapped: does Cw appeaw befowe Cb?
 * @bps: numbew of bits sent ovew bus fow each sampwe
 * @bpp: numbew of bits pew pixews unit
 */
stwuct ceu_mbus_fmt {
	u32	mbus_code;
	u32	fmt_owdew;
	u32	fmt_owdew_swap;
	boow	swapped;
	u8	bps;
	u8	bpp;
};

/*
 * ceu_buffew - Wink vb2 buffew to the wist of avaiwabwe buffews.
 */
stwuct ceu_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head queue;
};

static inwine stwuct ceu_buffew *vb2_to_ceu(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct ceu_buffew, vb);
}

/*
 * ceu_subdev - Wwaps v4w2 sub-device and pwovides async subdevice.
 */
stwuct ceu_subdev {
	stwuct v4w2_async_connection asd;
	stwuct v4w2_subdev *v4w2_sd;

	/* pew-subdevice mbus configuwation options */
	unsigned int mbus_fwags;
	stwuct ceu_mbus_fmt mbus_fmt;
};

static stwuct ceu_subdev *to_ceu_subdev(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct ceu_subdev, asd);
}

/*
 * ceu_device - CEU device instance
 */
stwuct ceu_device {
	stwuct device		*dev;
	stwuct video_device	vdev;
	stwuct v4w2_device	v4w2_dev;

	/* subdevices descwiptows */
	stwuct ceu_subdev	**subdevs;
	/* the subdevice cuwwentwy in use */
	stwuct ceu_subdev	*sd;
	unsigned int		sd_index;
	unsigned int		num_sd;

	/* pwatfowm specific mask with aww IWQ souwces fwagged */
	u32			iwq_mask;

	/* cuwwentwy configuwed fiewd and pixew fowmat */
	enum v4w2_fiewd	fiewd;
	stwuct v4w2_pix_fowmat_mpwane v4w2_pix;

	/* async subdev notification hewpews */
	stwuct v4w2_async_notifiew notifiew;

	/* vb2 queue, captuwe buffew wist and active buffew pointew */
	stwuct vb2_queue	vb2_vq;
	stwuct wist_head	captuwe;
	stwuct vb2_v4w2_buffew	*active;
	unsigned int		sequence;

	/* mwock - wock access to intewface weset and vb2 queue */
	stwuct mutex	mwock;

	/* wock - wock access to captuwe buffew queue and active buffew */
	spinwock_t	wock;

	/* base - CEU memowy base addwess */
	void __iomem	*base;
};

static inwine stwuct ceu_device *v4w2_to_ceu(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct ceu_device, v4w2_dev);
}

/* --- CEU memowy output fowmats --- */

/*
 * ceu_fmt - descwibe a memowy output fowmat suppowted by CEU intewface.
 *
 * @fouwcc: memowy wayout fouwcc fowmat code
 * @bpp: numbew of bits fow each pixew stowed in memowy
 */
stwuct ceu_fmt {
	u32	fouwcc;
	u32	bpp;
};

/*
 * ceu_fowmat_wist - Wist of suppowted memowy output fowmats
 *
 * If sensow pwovides any YUYV bus fowmat, aww the fowwowing pwanaw memowy
 * fowmats awe avaiwabwe thanks to CEU we-owdewing and sub-sampwing
 * capabiwities.
 */
static const stwuct ceu_fmt ceu_fmt_wist[] = {
	{
		.fouwcc	= V4W2_PIX_FMT_NV16,
		.bpp	= 16,
	},
	{
		.fouwcc = V4W2_PIX_FMT_NV61,
		.bpp	= 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_NV12,
		.bpp	= 12,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_NV21,
		.bpp	= 12,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_YUYV,
		.bpp	= 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_UYVY,
		.bpp	= 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_YVYU,
		.bpp	= 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_VYUY,
		.bpp	= 16,
	},
};

static const stwuct ceu_fmt *get_ceu_fmt_fwom_fouwcc(unsigned int fouwcc)
{
	const stwuct ceu_fmt *fmt = &ceu_fmt_wist[0];
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ceu_fmt_wist); i++, fmt++)
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;

	wetuwn NUWW;
}

static boow ceu_fmt_mpwane(stwuct v4w2_pix_fowmat_mpwane *pix)
{
	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
		wetuwn fawse;
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* --- CEU HW opewations --- */

static void ceu_wwite(stwuct ceu_device *pwiv, unsigned int weg_offs, u32 data)
{
	iowwite32(data, pwiv->base + weg_offs);
}

static u32 ceu_wead(stwuct ceu_device *pwiv, unsigned int weg_offs)
{
	wetuwn iowead32(pwiv->base + weg_offs);
}

/*
 * ceu_soft_weset() - Softwawe weset the CEU intewface.
 * @ceu_device: CEU device.
 *
 * Wetuwns 0 fow success, -EIO fow ewwow.
 */
static int ceu_soft_weset(stwuct ceu_device *ceudev)
{
	unsigned int i;

	ceu_wwite(ceudev, CEU_CAPSW, CEU_CAPSW_CPKIW);

	fow (i = 0; i < 100; i++) {
		if (!(ceu_wead(ceudev, CEU_CSTSW) & CEU_CSTWST_CPTON))
			bweak;
		udeway(1);
	}

	if (i == 100) {
		dev_eww(ceudev->dev, "soft weset time out\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < 100; i++) {
		if (!(ceu_wead(ceudev, CEU_CAPSW) & CEU_CAPSW_CPKIW))
			wetuwn 0;
		udeway(1);
	}

	/* If we get hewe, CEU has not weset pwopewwy. */
	wetuwn -EIO;
}

/* --- CEU Captuwe Opewations --- */

/*
 * ceu_hw_config() - Configuwe CEU intewface wegistews.
 */
static int ceu_hw_config(stwuct ceu_device *ceudev)
{
	u32 camcw, cdocw, cfzsw, cdwdw, capww;
	stwuct v4w2_pix_fowmat_mpwane *pix = &ceudev->v4w2_pix;
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	stwuct ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	unsigned int mbus_fwags = ceu_sd->mbus_fwags;

	/* Stawt configuwing CEU wegistews */
	ceu_wwite(ceudev, CEU_CAIFW, 0);
	ceu_wwite(ceudev, CEU_CFWCW, 0);
	ceu_wwite(ceudev, CEU_CWCNTW, 0);
	ceu_wwite(ceudev, CEU_CWCMPW, 0);

	/* Set the fwame captuwe pewiod fow both image captuwe and data sync. */
	capww = (pix->height << 16) | pix->width * mbus_fmt->bpp / 8;

	/*
	 * Swap input data endianness by defauwt.
	 * In data fetch mode bytes awe weceived in chunks of 8 bytes.
	 * D0, D1, D2, D3, D4, D5, D6, D7 (D0 weceived fiwst)
	 * The data is howevew by defauwt wwitten to memowy in wevewse owdew:
	 * D7, D6, D5, D4, D3, D2, D1, D0 (D7 wwitten to wowest byte)
	 *
	 * Use CEU_CDOCW[2:0] to swap data owdewing.
	 */
	cdocw = CEU_CDOCW_SWAP_ENDIANNESS;

	/*
	 * Configuwe CAMCW and CDOCW:
	 * match input components owdewing with memowy output fowmat and
	 * handwe downsampwing to YUV420.
	 *
	 * If the memowy output pwanaw fowmat is 'swapped' (Cw befowe Cb) and
	 * input fowmat is not, use the swapped vewsion of CAMCW.DTAWY.
	 *
	 * If the memowy output pwanaw fowmat is not 'swapped' (Cb befowe Cw)
	 * and input fowmat is, use the swapped vewsion of CAMCW.DTAWY.
	 *
	 * CEU by defauwt downsampwe to pwanaw YUV420 (CDCOW[4] = 0).
	 * If output is pwanaw YUV422 set CDOCW[4] = 1
	 *
	 * No downsampwe fow data fetch sync mode.
	 */
	switch (pix->pixewfowmat) {
	/* Data fetch sync mode */
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		camcw	= CEU_CAMCW_JPEG;
		cdocw	|= CEU_CDOCW_NO_DOWSAMPWE;
		cfzsw	= (pix->height << 16) | pix->width;
		cdwdw	= pix->pwane_fmt[0].bytespewwine;
		bweak;

	/* Non-swapped pwanaw image captuwe mode. */
	case V4W2_PIX_FMT_NV16:
		cdocw	|= CEU_CDOCW_NO_DOWSAMPWE;
		fawwthwough;
	case V4W2_PIX_FMT_NV12:
		if (mbus_fmt->swapped)
			camcw = mbus_fmt->fmt_owdew_swap;
		ewse
			camcw = mbus_fmt->fmt_owdew;

		cfzsw	= (pix->height << 16) | pix->width;
		cdwdw	= pix->width;
		bweak;

	/* Swapped pwanaw image captuwe mode. */
	case V4W2_PIX_FMT_NV61:
		cdocw	|= CEU_CDOCW_NO_DOWSAMPWE;
		fawwthwough;
	case V4W2_PIX_FMT_NV21:
		if (mbus_fmt->swapped)
			camcw = mbus_fmt->fmt_owdew;
		ewse
			camcw = mbus_fmt->fmt_owdew_swap;

		cfzsw	= (pix->height << 16) | pix->width;
		cdwdw	= pix->width;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	camcw |= mbus_fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW ? 1 << 1 : 0;
	camcw |= mbus_fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW ? 1 << 0 : 0;

	/* TODO: handwe 16 bit bus width with DTIF bit in CAMCW */
	ceu_wwite(ceudev, CEU_CAMCW, camcw);
	ceu_wwite(ceudev, CEU_CDOCW, cdocw);
	ceu_wwite(ceudev, CEU_CAPCW, CEU_CAPCW_BUS_WIDTH256);

	/*
	 * TODO: make CAMOW offsets configuwabwe.
	 * CAMOW wants to know the numbew of bwanks between a VS/HS signaw
	 * and vawid data. This vawue shouwd actuawwy come fwom the sensow...
	 */
	ceu_wwite(ceudev, CEU_CAMOW, 0);

	/* TODO: 16 bit bus width wequiwe we-cawcuwation of cdwdw and cfzsw */
	ceu_wwite(ceudev, CEU_CAPWW, capww);
	ceu_wwite(ceudev, CEU_CFSZW, cfzsw);
	ceu_wwite(ceudev, CEU_CDWDW, cdwdw);

	wetuwn 0;
}

/*
 * ceu_captuwe() - Twiggew stawt of a captuwe sequence.
 *
 * Pwogwam the CEU DMA wegistews with addwesses whewe to twansfew image data.
 */
static int ceu_captuwe(stwuct ceu_device *ceudev)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &ceudev->v4w2_pix;
	dma_addw_t phys_addw_top;

	phys_addw_top =
		vb2_dma_contig_pwane_dma_addw(&ceudev->active->vb2_buf, 0);
	ceu_wwite(ceudev, CEU_CDAYW, phys_addw_top);

	/* Ignowe CbCw pwane fow non muwti-pwanaw image fowmats. */
	if (ceu_fmt_mpwane(pix)) {
		phys_addw_top =
			vb2_dma_contig_pwane_dma_addw(&ceudev->active->vb2_buf,
						      1);
		ceu_wwite(ceudev, CEU_CDACW, phys_addw_top);
	}

	/*
	 * Twiggew new captuwe stawt: once fow each fwame, as we wowk in
	 * one-fwame captuwe mode.
	 */
	ceu_wwite(ceudev, CEU_CAPSW, CEU_CAPSW_CE);

	wetuwn 0;
}

static iwqwetuwn_t ceu_iwq(int iwq, void *data)
{
	stwuct ceu_device *ceudev = data;
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct ceu_buffew *buf;
	u32 status;

	/* Cwean intewwupt status. */
	status = ceu_wead(ceudev, CEU_CETCW);
	ceu_wwite(ceudev, CEU_CETCW, ~ceudev->iwq_mask);

	/* Unexpected intewwupt. */
	if (!(status & CEU_CEIEW_MASK))
		wetuwn IWQ_NONE;

	spin_wock(&ceudev->wock);

	/* Stawe intewwupt fwom a weweased buffew, ignowe it. */
	vbuf = ceudev->active;
	if (!vbuf) {
		spin_unwock(&ceudev->wock);
		wetuwn IWQ_HANDWED;
	}

	/*
	 * When a VBP intewwupt occuws, no captuwe end intewwupt wiww occuw
	 * and the image of that fwame is not captuwed cowwectwy.
	 */
	if (status & CEU_CEIEW_VBP) {
		dev_eww(ceudev->dev, "VBP intewwupt: abowt captuwe\n");
		goto ewwow_iwq_out;
	}

	/* Pwepawe to wetuwn the 'pwevious' buffew. */
	vbuf->vb2_buf.timestamp = ktime_get_ns();
	vbuf->sequence = ceudev->sequence++;
	vbuf->fiewd = ceudev->fiewd;

	/* Pwepawe a new 'active' buffew and twiggew a new captuwe. */
	if (!wist_empty(&ceudev->captuwe)) {
		buf = wist_fiwst_entwy(&ceudev->captuwe, stwuct ceu_buffew,
				       queue);
		wist_dew(&buf->queue);
		ceudev->active = &buf->vb;

		ceu_captuwe(ceudev);
	}

	/* Wetuwn the 'pwevious' buffew. */
	vb2_buffew_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	spin_unwock(&ceudev->wock);

	wetuwn IWQ_HANDWED;

ewwow_iwq_out:
	/* Wetuwn the 'pwevious' buffew and aww queued ones. */
	vb2_buffew_done(&vbuf->vb2_buf, VB2_BUF_STATE_EWWOW);

	wist_fow_each_entwy(buf, &ceudev->captuwe, queue)
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);

	spin_unwock(&ceudev->wock);

	wetuwn IWQ_HANDWED;
}

/* --- CEU Videobuf2 opewations --- */

static void ceu_update_pwane_sizes(stwuct v4w2_pwane_pix_fowmat *pwane,
				   unsigned int bpw, unsigned int szimage)
{
	memset(pwane, 0, sizeof(*pwane));

	pwane->sizeimage = szimage;
	if (pwane->bytespewwine < bpw || pwane->bytespewwine > CEU_MAX_BPW)
		pwane->bytespewwine = bpw;
}

/*
 * ceu_cawc_pwane_sizes() - Fiww pew-pwane 'stwuct v4w2_pwane_pix_fowmat'
 *			    infowmation accowding to the cuwwentwy configuwed
 *			    pixew fowmat.
 * @ceu_device: CEU device.
 * @ceu_fmt: Active image fowmat.
 * @pix: Pixew fowmat infowmation (stowe wine width and image sizes)
 */
static void ceu_cawc_pwane_sizes(stwuct ceu_device *ceudev,
				 const stwuct ceu_fmt *ceu_fmt,
				 stwuct v4w2_pix_fowmat_mpwane *pix)
{
	unsigned int bpw, szimage;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
		pix->num_pwanes	= 1;
		bpw		= pix->width * ceu_fmt->bpp / 8;
		szimage		= pix->height * bpw;
		ceu_update_pwane_sizes(&pix->pwane_fmt[0], bpw, szimage);
		bweak;

	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		pix->num_pwanes	= 2;
		bpw		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_pwane_sizes(&pix->pwane_fmt[0], bpw, szimage);
		ceu_update_pwane_sizes(&pix->pwane_fmt[1], bpw, szimage / 2);
		bweak;

	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
	defauwt:
		pix->num_pwanes	= 2;
		bpw		= pix->width;
		szimage		= pix->height * pix->width;
		ceu_update_pwane_sizes(&pix->pwane_fmt[0], bpw, szimage);
		ceu_update_pwane_sizes(&pix->pwane_fmt[1], bpw, szimage);
		bweak;
	}
}

/*
 * ceu_vb2_setup() - is cawwed to check whethew the dwivew can accept the
 *		     wequested numbew of buffews and to fiww in pwane sizes
 *		     fow the cuwwent fwame fowmat, if wequiwed.
 */
static int ceu_vb2_setup(stwuct vb2_queue *vq, unsigned int *count,
			 unsigned int *num_pwanes, unsigned int sizes[],
			 stwuct device *awwoc_devs[])
{
	stwuct ceu_device *ceudev = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat_mpwane *pix = &ceudev->v4w2_pix;
	unsigned int i;

	/* num_pwanes is set: just check pwane sizes. */
	if (*num_pwanes) {
		fow (i = 0; i < pix->num_pwanes; i++)
			if (sizes[i] < pix->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;

		wetuwn 0;
	}

	/* num_pwanes not set: cawwed fwom WEQBUFS, just set pwane sizes. */
	*num_pwanes = pix->num_pwanes;
	fow (i = 0; i < pix->num_pwanes; i++)
		sizes[i] = pix->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static void ceu_vb2_queue(stwuct vb2_buffew *vb)
{
	stwuct ceu_device *ceudev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct ceu_buffew *buf = vb2_to_ceu(vbuf);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&ceudev->wock, iwqfwags);
	wist_add_taiw(&buf->queue, &ceudev->captuwe);
	spin_unwock_iwqwestowe(&ceudev->wock, iwqfwags);
}

static int ceu_vb2_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct ceu_device *ceudev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct v4w2_pix_fowmat_mpwane *pix = &ceudev->v4w2_pix;
	unsigned int i;

	fow (i = 0; i < pix->num_pwanes; i++) {
		if (vb2_pwane_size(vb, i) < pix->pwane_fmt[i].sizeimage) {
			dev_eww(ceudev->dev,
				"Pwane size too smaww (%wu < %u)\n",
				vb2_pwane_size(vb, i),
				pix->pwane_fmt[i].sizeimage);
			wetuwn -EINVAW;
		}

		vb2_set_pwane_paywoad(vb, i, pix->pwane_fmt[i].sizeimage);
	}

	wetuwn 0;
}

static int ceu_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct ceu_device *ceudev = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_subdev *v4w2_sd = ceudev->sd->v4w2_sd;
	stwuct ceu_buffew *buf;
	unsigned wong iwqfwags;
	int wet;

	/* Pwogwam the CEU intewface accowding to the CEU image fowmat. */
	wet = ceu_hw_config(ceudev);
	if (wet)
		goto ewwow_wetuwn_bufs;

	wet = v4w2_subdev_caww(v4w2_sd, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD) {
		dev_dbg(ceudev->dev,
			"Subdevice faiwed to stawt stweaming: %d\n", wet);
		goto ewwow_wetuwn_bufs;
	}

	spin_wock_iwqsave(&ceudev->wock, iwqfwags);
	ceudev->sequence = 0;

	/* Gwab the fiwst avaiwabwe buffew and twiggew the fiwst captuwe. */
	buf = wist_fiwst_entwy(&ceudev->captuwe, stwuct ceu_buffew,
			       queue);

	wist_dew(&buf->queue);
	ceudev->active = &buf->vb;

	/* Cwean and pwogwam intewwupts fow fiwst captuwe. */
	ceu_wwite(ceudev, CEU_CETCW, ~ceudev->iwq_mask);
	ceu_wwite(ceudev, CEU_CEIEW, CEU_CEIEW_MASK);

	ceu_captuwe(ceudev);

	spin_unwock_iwqwestowe(&ceudev->wock, iwqfwags);

	wetuwn 0;

ewwow_wetuwn_bufs:
	spin_wock_iwqsave(&ceudev->wock, iwqfwags);
	wist_fow_each_entwy(buf, &ceudev->captuwe, queue)
		vb2_buffew_done(&ceudev->active->vb2_buf,
				VB2_BUF_STATE_QUEUED);
	ceudev->active = NUWW;
	spin_unwock_iwqwestowe(&ceudev->wock, iwqfwags);

	wetuwn wet;
}

static void ceu_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct ceu_device *ceudev = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_subdev *v4w2_sd = ceudev->sd->v4w2_sd;
	stwuct ceu_buffew *buf;
	unsigned wong iwqfwags;

	/* Cwean and disabwe intewwupt souwces. */
	ceu_wwite(ceudev, CEU_CETCW,
		  ceu_wead(ceudev, CEU_CETCW) & ceudev->iwq_mask);
	ceu_wwite(ceudev, CEU_CEIEW, CEU_CEIEW_MASK);

	v4w2_subdev_caww(v4w2_sd, video, s_stweam, 0);

	spin_wock_iwqsave(&ceudev->wock, iwqfwags);
	if (ceudev->active) {
		vb2_buffew_done(&ceudev->active->vb2_buf,
				VB2_BUF_STATE_EWWOW);
		ceudev->active = NUWW;
	}

	/* Wewease aww queued buffews. */
	wist_fow_each_entwy(buf, &ceudev->captuwe, queue)
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	INIT_WIST_HEAD(&ceudev->captuwe);

	spin_unwock_iwqwestowe(&ceudev->wock, iwqfwags);

	ceu_soft_weset(ceudev);
}

static const stwuct vb2_ops ceu_vb2_ops = {
	.queue_setup		= ceu_vb2_setup,
	.buf_queue		= ceu_vb2_queue,
	.buf_pwepawe		= ceu_vb2_pwepawe,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.stawt_stweaming	= ceu_stawt_stweaming,
	.stop_stweaming		= ceu_stop_stweaming,
};

/* --- CEU image fowmats handwing --- */

/*
 * __ceu_twy_fmt() - test fowmat on CEU and sensow
 * @ceudev: The CEU device.
 * @v4w2_fmt: fowmat to test.
 * @sd_mbus_code: the media bus code accepted by the subdevice; output pawam.
 *
 * Wetuwns 0 fow success, < 0 fow ewwows.
 */
static int __ceu_twy_fmt(stwuct ceu_device *ceudev, stwuct v4w2_fowmat *v4w2_fmt,
			 u32 *sd_mbus_code)
{
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	stwuct v4w2_pix_fowmat_mpwane *pix = &v4w2_fmt->fmt.pix_mp;
	stwuct v4w2_subdev *v4w2_sd = ceu_sd->v4w2_sd;
	stwuct v4w2_subdev_pad_config pad_cfg;
	stwuct v4w2_subdev_state pad_state = {
		.pads = &pad_cfg,
	};
	const stwuct ceu_fmt *ceu_fmt;
	u32 mbus_code_owd;
	u32 mbus_code;
	int wet;

	/*
	 * Set fowmat on sensow sub device: bus fowmat used to pwoduce memowy
	 * fowmat is sewected depending on YUV component owdewing ow
	 * at initiawization time.
	 */
	stwuct v4w2_subdev_fowmat sd_fowmat = {
		.which	= V4W2_SUBDEV_FOWMAT_TWY,
	};

	mbus_code_owd = ceu_sd->mbus_fmt.mbus_code;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
		mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		mbus_code = MEDIA_BUS_FMT_UYVY8_2X8;
		bweak;
	case V4W2_PIX_FMT_YVYU:
		mbus_code = MEDIA_BUS_FMT_YVYU8_2X8;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		mbus_code = MEDIA_BUS_FMT_VYUY8_2X8;
		bweak;
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		bweak;

	defauwt:
		pix->pixewfowmat = V4W2_PIX_FMT_NV16;
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		bweak;
	}

	ceu_fmt = get_ceu_fmt_fwom_fouwcc(pix->pixewfowmat);

	/* CFSZW wequiwes height and width to be 4-pixew awigned. */
	v4w_bound_awign_image(&pix->width, 2, CEU_MAX_WIDTH, 4,
			      &pix->height, 4, CEU_MAX_HEIGHT, 4, 0);

	v4w2_fiww_mbus_fowmat_mpwane(&sd_fowmat.fowmat, pix);

	/*
	 * Twy with the mbus_code matching YUYV components owdewing fiwst,
	 * if that one faiws, fawwback to defauwt sewected at initiawization
	 * time.
	 */
	sd_fowmat.fowmat.code = mbus_code;
	wet = v4w2_subdev_caww(v4w2_sd, pad, set_fmt, &pad_state, &sd_fowmat);
	if (wet) {
		if (wet == -EINVAW) {
			/* fawwback */
			sd_fowmat.fowmat.code = mbus_code_owd;
			wet = v4w2_subdev_caww(v4w2_sd, pad, set_fmt,
					       &pad_state, &sd_fowmat);
		}

		if (wet)
			wetuwn wet;
	}

	/* Appwy size wetuwned by sensow as the CEU can't scawe. */
	v4w2_fiww_pix_fowmat_mpwane(pix, &sd_fowmat.fowmat);

	/* Cawcuwate pew-pwane sizes based on image fowmat. */
	ceu_cawc_pwane_sizes(ceudev, ceu_fmt, pix);

	/* Wepowt to cawwew the configuwed mbus fowmat. */
	*sd_mbus_code = sd_fowmat.fowmat.code;

	wetuwn 0;
}

/*
 * ceu_twy_fmt() - Wwappew fow __ceu_twy_fmt; discawd configuwed mbus_fmt
 */
static int ceu_twy_fmt(stwuct ceu_device *ceudev, stwuct v4w2_fowmat *v4w2_fmt)
{
	u32 mbus_code;

	wetuwn __ceu_twy_fmt(ceudev, v4w2_fmt, &mbus_code);
}

/*
 * ceu_set_fmt() - Appwy the suppwied fowmat to both sensow and CEU
 */
static int ceu_set_fmt(stwuct ceu_device *ceudev, stwuct v4w2_fowmat *v4w2_fmt)
{
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	stwuct v4w2_subdev *v4w2_sd = ceu_sd->v4w2_sd;
	u32 mbus_code;
	int wet;

	/*
	 * Set fowmat on sensow sub device: bus fowmat used to pwoduce memowy
	 * fowmat is sewected at initiawization time.
	 */
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	wet = __ceu_twy_fmt(ceudev, v4w2_fmt, &mbus_code);
	if (wet)
		wetuwn wet;

	fowmat.fowmat.code = mbus_code;
	v4w2_fiww_mbus_fowmat_mpwane(&fowmat.fowmat, &v4w2_fmt->fmt.pix_mp);
	wet = v4w2_subdev_caww(v4w2_sd, pad, set_fmt, NUWW, &fowmat);
	if (wet)
		wetuwn wet;

	ceudev->v4w2_pix = v4w2_fmt->fmt.pix_mp;
	ceudev->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

/*
 * ceu_set_defauwt_fmt() - Appwy defauwt NV16 memowy output fowmat with VGA
 *			   sizes.
 */
static int ceu_set_defauwt_fmt(stwuct ceu_device *ceudev)
{
	int wet;

	stwuct v4w2_fowmat v4w2_fmt = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
		.fmt.pix_mp = {
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.fiewd		= V4W2_FIEWD_NONE,
			.pixewfowmat	= V4W2_PIX_FMT_NV16,
			.num_pwanes	= 2,
			.pwane_fmt	= {
				[0]	= {
					.sizeimage = VGA_WIDTH * VGA_HEIGHT * 2,
					.bytespewwine = VGA_WIDTH * 2,
				},
				[1]	= {
					.sizeimage = VGA_WIDTH * VGA_HEIGHT * 2,
					.bytespewwine = VGA_WIDTH * 2,
				},
			},
		},
	};

	wet = ceu_twy_fmt(ceudev, &v4w2_fmt);
	if (wet)
		wetuwn wet;

	ceudev->v4w2_pix = v4w2_fmt.fmt.pix_mp;
	ceudev->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

/*
 * ceu_init_mbus_fmt() - Quewy sensow fow suppowted fowmats and initiawize
 *			 CEU media bus fowmat used to pwoduce memowy fowmats.
 *
 * Find out if sensow can pwoduce a pewmutation of 8-bits YUYV bus fowmat.
 * Fwom a singwe 8-bits YUYV bus fowmat the CEU can pwoduce sevewaw memowy
 * output fowmats:
 * - NV[12|21|16|61] thwough image fetch mode;
 * - YUYV422 if sensow pwovides YUYV422
 *
 * TODO: Othew YUYV422 pewmutations thwough data fetch sync mode and DTAWY
 * TODO: Binawy data (eg. JPEG) and waw fowmats thwough data fetch sync mode
 */
static int ceu_init_mbus_fmt(stwuct ceu_device *ceudev)
{
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	stwuct ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	stwuct v4w2_subdev *v4w2_sd = ceu_sd->v4w2_sd;
	boow yuyv_bus_fmt = fawse;

	stwuct v4w2_subdev_mbus_code_enum sd_mbus_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.index = 0,
	};

	/* Find out if sensow can pwoduce any pewmutation of 8-bits YUYV422. */
	whiwe (!yuyv_bus_fmt &&
	       !v4w2_subdev_caww(v4w2_sd, pad, enum_mbus_code,
				 NUWW, &sd_mbus_fmt)) {
		switch (sd_mbus_fmt.code) {
		case MEDIA_BUS_FMT_YUYV8_2X8:
		case MEDIA_BUS_FMT_YVYU8_2X8:
		case MEDIA_BUS_FMT_UYVY8_2X8:
		case MEDIA_BUS_FMT_VYUY8_2X8:
			yuyv_bus_fmt = twue;
			bweak;
		defauwt:
			/*
			 * Onwy suppowt 8-bits YUYV bus fowmats at the moment;
			 *
			 * TODO: add suppowt fow binawy fowmats (data sync
			 * fetch mode).
			 */
			bweak;
		}

		sd_mbus_fmt.index++;
	}

	if (!yuyv_bus_fmt)
		wetuwn -ENXIO;

	/*
	 * Save the fiwst encountewed YUYV fowmat as "mbus_fmt" and use it
	 * to output aww pwanaw YUV422 and YUV420 (NV*) fowmats to memowy as
	 * weww as fow data synch fetch mode (YUYV - YVYU etc. ).
	 */
	mbus_fmt->mbus_code	= sd_mbus_fmt.code;
	mbus_fmt->bps		= 8;

	/* Annotate the sewected bus fowmat components owdewing. */
	switch (sd_mbus_fmt.code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
		mbus_fmt->fmt_owdew		= CEU_CAMCW_DTAWY_8_YUYV;
		mbus_fmt->fmt_owdew_swap	= CEU_CAMCW_DTAWY_8_YVYU;
		mbus_fmt->swapped		= fawse;
		mbus_fmt->bpp			= 16;
		bweak;

	case MEDIA_BUS_FMT_YVYU8_2X8:
		mbus_fmt->fmt_owdew		= CEU_CAMCW_DTAWY_8_YVYU;
		mbus_fmt->fmt_owdew_swap	= CEU_CAMCW_DTAWY_8_YUYV;
		mbus_fmt->swapped		= twue;
		mbus_fmt->bpp			= 16;
		bweak;

	case MEDIA_BUS_FMT_UYVY8_2X8:
		mbus_fmt->fmt_owdew		= CEU_CAMCW_DTAWY_8_UYVY;
		mbus_fmt->fmt_owdew_swap	= CEU_CAMCW_DTAWY_8_VYUY;
		mbus_fmt->swapped		= fawse;
		mbus_fmt->bpp			= 16;
		bweak;

	case MEDIA_BUS_FMT_VYUY8_2X8:
		mbus_fmt->fmt_owdew		= CEU_CAMCW_DTAWY_8_VYUY;
		mbus_fmt->fmt_owdew_swap	= CEU_CAMCW_DTAWY_8_UYVY;
		mbus_fmt->swapped		= twue;
		mbus_fmt->bpp			= 16;
		bweak;
	}

	wetuwn 0;
}

/* --- Wuntime PM Handwews --- */

/*
 * ceu_wuntime_wesume() - soft-weset the intewface and tuwn sensow powew on.
 */
static int __maybe_unused ceu_wuntime_wesume(stwuct device *dev)
{
	stwuct ceu_device *ceudev = dev_get_dwvdata(dev);
	stwuct v4w2_subdev *v4w2_sd = ceudev->sd->v4w2_sd;

	v4w2_subdev_caww(v4w2_sd, cowe, s_powew, 1);

	ceu_soft_weset(ceudev);

	wetuwn 0;
}

/*
 * ceu_wuntime_suspend() - disabwe captuwe and intewwupts and soft-weset.
 *			   Tuwn sensow powew off.
 */
static int __maybe_unused ceu_wuntime_suspend(stwuct device *dev)
{
	stwuct ceu_device *ceudev = dev_get_dwvdata(dev);
	stwuct v4w2_subdev *v4w2_sd = ceudev->sd->v4w2_sd;

	v4w2_subdev_caww(v4w2_sd, cowe, s_powew, 0);

	ceu_wwite(ceudev, CEU_CEIEW, 0);
	ceu_soft_weset(ceudev);

	wetuwn 0;
}

/* --- Fiwe Opewations --- */

static int ceu_open(stwuct fiwe *fiwe)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);
	int wet;

	wet = v4w2_fh_open(fiwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&ceudev->mwock);
	/* Causes soft-weset and sensow powew on on fiwst open */
	wet = pm_wuntime_wesume_and_get(ceudev->dev);
	mutex_unwock(&ceudev->mwock);

	wetuwn wet;
}

static int ceu_wewease(stwuct fiwe *fiwe)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	vb2_fop_wewease(fiwe);

	mutex_wock(&ceudev->mwock);
	/* Causes soft-weset and sensow powew down on wast cwose */
	pm_wuntime_put(ceudev->dev);
	mutex_unwock(&ceudev->mwock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations ceu_fops = {
	.ownew			= THIS_MODUWE,
	.open			= ceu_open,
	.wewease		= ceu_wewease,
	.unwocked_ioctw		= video_ioctw2,
	.mmap			= vb2_fop_mmap,
	.poww			= vb2_fop_poww,
};

/* --- Video Device IOCTWs --- */

static int ceu_quewycap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_capabiwity *cap)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	stwscpy(cap->cawd, "Wenesas CEU", sizeof(cap->cawd));
	stwscpy(cap->dwivew, DWIVEW_NAME, sizeof(cap->dwivew));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:wenesas-ceu-%s", dev_name(ceudev->dev));

	wetuwn 0;
}

static int ceu_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	const stwuct ceu_fmt *fmt;

	if (f->index >= AWWAY_SIZE(ceu_fmt_wist))
		wetuwn -EINVAW;

	fmt = &ceu_fmt_wist[f->index];
	f->pixewfowmat = fmt->fouwcc;

	wetuwn 0;
}

static int ceu_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	wetuwn ceu_twy_fmt(ceudev, f);
}

static int ceu_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	if (vb2_is_stweaming(&ceudev->vb2_vq))
		wetuwn -EBUSY;

	wetuwn ceu_set_fmt(ceudev, f);
}

static int ceu_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	f->fmt.pix_mp = ceudev->v4w2_pix;

	wetuwn 0;
}

static int ceu_enum_input(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_input *inp)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	if (inp->index >= ceudev->num_sd)
		wetuwn -EINVAW;

	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->std = 0;
	snpwintf(inp->name, sizeof(inp->name), "Camewa %u", inp->index);

	wetuwn 0;
}

static int ceu_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	*i = ceudev->sd_index;

	wetuwn 0;
}

static int ceu_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);
	stwuct ceu_subdev *ceu_sd_owd;
	int wet;

	if (i >= ceudev->num_sd)
		wetuwn -EINVAW;

	if (vb2_is_stweaming(&ceudev->vb2_vq))
		wetuwn -EBUSY;

	if (i == ceudev->sd_index)
		wetuwn 0;

	ceu_sd_owd = ceudev->sd;
	ceudev->sd = ceudev->subdevs[i];

	/*
	 * Make suwe we can genewate output image fowmats and appwy
	 * defauwt one.
	 */
	wet = ceu_init_mbus_fmt(ceudev);
	if (wet) {
		ceudev->sd = ceu_sd_owd;
		wetuwn -EINVAW;
	}

	wet = ceu_set_defauwt_fmt(ceudev);
	if (wet) {
		ceudev->sd = ceu_sd_owd;
		wetuwn -EINVAW;
	}

	/* Now that we'we suwe we can use the sensow, powew off the owd one. */
	v4w2_subdev_caww(ceu_sd_owd->v4w2_sd, cowe, s_powew, 0);
	v4w2_subdev_caww(ceudev->sd->v4w2_sd, cowe, s_powew, 1);

	ceudev->sd_index = i;

	wetuwn 0;
}

static int ceu_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	wetuwn v4w2_g_pawm_cap(video_devdata(fiwe), ceudev->sd->v4w2_sd, a);
}

static int ceu_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);

	wetuwn v4w2_s_pawm_cap(video_devdata(fiwe), ceudev->sd->v4w2_sd, a);
}

static int ceu_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	const stwuct ceu_fmt *ceu_fmt;
	stwuct v4w2_subdev *v4w2_sd = ceu_sd->v4w2_sd;
	int wet;

	stwuct v4w2_subdev_fwame_size_enum fse = {
		.code	= ceu_sd->mbus_fmt.mbus_code,
		.index	= fsize->index,
		.which	= V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	/* Just check if usew suppwied pixew fowmat is suppowted. */
	ceu_fmt = get_ceu_fmt_fwom_fouwcc(fsize->pixew_fowmat);
	if (!ceu_fmt)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(v4w2_sd, pad, enum_fwame_size,
			       NUWW, &fse);
	if (wet)
		wetuwn wet;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = CEU_W_MAX(fse.max_width);
	fsize->discwete.height = CEU_H_MAX(fse.max_height);

	wetuwn 0;
}

static int ceu_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct ceu_device *ceudev = video_dwvdata(fiwe);
	stwuct ceu_subdev *ceu_sd = ceudev->sd;
	const stwuct ceu_fmt *ceu_fmt;
	stwuct v4w2_subdev *v4w2_sd = ceu_sd->v4w2_sd;
	int wet;

	stwuct v4w2_subdev_fwame_intewvaw_enum fie = {
		.code	= ceu_sd->mbus_fmt.mbus_code,
		.index = fivaw->index,
		.width = fivaw->width,
		.height = fivaw->height,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	/* Just check if usew suppwied pixew fowmat is suppowted. */
	ceu_fmt = get_ceu_fmt_fwom_fouwcc(fivaw->pixew_fowmat);
	if (!ceu_fmt)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(v4w2_sd, pad, enum_fwame_intewvaw, NUWW,
			       &fie);
	if (wet)
		wetuwn wet;

	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete = fie.intewvaw;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops ceu_ioctw_ops = {
	.vidioc_quewycap		= ceu_quewycap,

	.vidioc_enum_fmt_vid_cap	= ceu_enum_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap_mpwane	= ceu_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mpwane	= ceu_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mpwane	= ceu_g_fmt_vid_cap,

	.vidioc_enum_input		= ceu_enum_input,
	.vidioc_g_input			= ceu_g_input,
	.vidioc_s_input			= ceu_s_input,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_g_pawm			= ceu_g_pawm,
	.vidioc_s_pawm			= ceu_s_pawm,
	.vidioc_enum_fwamesizes		= ceu_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= ceu_enum_fwameintewvaws,

	.vidioc_wog_status              = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event         = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event       = v4w2_event_unsubscwibe,
};

/*
 * ceu_vdev_wewease() - wewease CEU video device memowy when wast wefewence
 *			to this dwivew is cwosed
 */
static void ceu_vdev_wewease(stwuct video_device *vdev)
{
	stwuct ceu_device *ceudev = video_get_dwvdata(vdev);

	kfwee(ceudev);
}

static int ceu_notify_bound(stwuct v4w2_async_notifiew *notifiew,
			    stwuct v4w2_subdev *v4w2_sd,
			    stwuct v4w2_async_connection *asd)
{
	stwuct v4w2_device *v4w2_dev = notifiew->v4w2_dev;
	stwuct ceu_device *ceudev = v4w2_to_ceu(v4w2_dev);
	stwuct ceu_subdev *ceu_sd = to_ceu_subdev(asd);

	ceu_sd->v4w2_sd = v4w2_sd;
	ceudev->num_sd++;

	wetuwn 0;
}

static int ceu_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct v4w2_device *v4w2_dev = notifiew->v4w2_dev;
	stwuct ceu_device *ceudev = v4w2_to_ceu(v4w2_dev);
	stwuct video_device *vdev = &ceudev->vdev;
	stwuct vb2_queue *q = &ceudev->vb2_vq;
	stwuct v4w2_subdev *v4w2_sd;
	int wet;

	/* Initiawize vb2 queue. */
	q->type			= V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	q->io_modes		= VB2_MMAP | VB2_DMABUF;
	q->dwv_pwiv		= ceudev;
	q->ops			= &ceu_vb2_ops;
	q->mem_ops		= &vb2_dma_contig_memops;
	q->buf_stwuct_size	= sizeof(stwuct ceu_buffew);
	q->timestamp_fwags	= V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews	= 2;
	q->wock			= &ceudev->mwock;
	q->dev			= ceudev->v4w2_dev.dev;

	wet = vb2_queue_init(q);
	if (wet)
		wetuwn wet;

	/*
	 * Make suwe at weast one sensow is pwimawy and use it to initiawize
	 * ceu fowmats.
	 */
	if (!ceudev->sd) {
		ceudev->sd = ceudev->subdevs[0];
		ceudev->sd_index = 0;
	}

	v4w2_sd = ceudev->sd->v4w2_sd;

	wet = ceu_init_mbus_fmt(ceudev);
	if (wet)
		wetuwn wet;

	wet = ceu_set_defauwt_fmt(ceudev);
	if (wet)
		wetuwn wet;

	/* Wegistew the video device. */
	stwscpy(vdev->name, DWIVEW_NAME, sizeof(vdev->name));
	vdev->v4w2_dev		= v4w2_dev;
	vdev->wock		= &ceudev->mwock;
	vdev->queue		= &ceudev->vb2_vq;
	vdev->ctww_handwew	= v4w2_sd->ctww_handwew;
	vdev->fops		= &ceu_fops;
	vdev->ioctw_ops		= &ceu_ioctw_ops;
	vdev->wewease		= ceu_vdev_wewease;
	vdev->device_caps	= V4W2_CAP_VIDEO_CAPTUWE_MPWANE |
				  V4W2_CAP_STWEAMING;
	video_set_dwvdata(vdev, ceudev);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		v4w2_eww(vdev->v4w2_dev,
			 "video_wegistew_device faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations ceu_notify_ops = {
	.bound		= ceu_notify_bound,
	.compwete	= ceu_notify_compwete,
};

/*
 * ceu_init_async_subdevs() - Initiawize CEU subdevices and async_subdevs in
 *                           ceu device. Both DT and pwatfowm data pawsing use
 *                           this woutine.
 *
 * Wetuwns 0 fow success, -ENOMEM fow faiwuwe.
 */
static int ceu_init_async_subdevs(stwuct ceu_device *ceudev, unsigned int n_sd)
{
	/* Wesewve memowy fow 'n_sd' ceu_subdev descwiptows. */
	ceudev->subdevs = devm_kcawwoc(ceudev->dev, n_sd,
				       sizeof(*ceudev->subdevs), GFP_KEWNEW);
	if (!ceudev->subdevs)
		wetuwn -ENOMEM;

	ceudev->sd = NUWW;
	ceudev->sd_index = 0;
	ceudev->num_sd = 0;

	wetuwn 0;
}

/*
 * ceu_pawse_pwatfowm_data() - Initiawize async_subdevices using pwatfowm
 *			       device pwovided data.
 */
static int ceu_pawse_pwatfowm_data(stwuct ceu_device *ceudev,
				   const stwuct ceu_pwatfowm_data *pdata)
{
	const stwuct ceu_async_subdev *async_sd;
	stwuct ceu_subdev *ceu_sd;
	unsigned int i;
	int wet;

	if (pdata->num_subdevs == 0)
		wetuwn -ENODEV;

	wet = ceu_init_async_subdevs(ceudev, pdata->num_subdevs);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < pdata->num_subdevs; i++) {

		/* Setup the ceu subdevice and the async subdevice. */
		async_sd = &pdata->subdevs[i];
		ceu_sd = v4w2_async_nf_add_i2c(&ceudev->notifiew,
					       async_sd->i2c_adaptew_id,
					       async_sd->i2c_addwess,
					       stwuct ceu_subdev);
		if (IS_EWW(ceu_sd)) {
			v4w2_async_nf_cweanup(&ceudev->notifiew);
			wetuwn PTW_EWW(ceu_sd);
		}
		ceu_sd->mbus_fwags = async_sd->fwags;
		ceudev->subdevs[i] = ceu_sd;
	}

	wetuwn pdata->num_subdevs;
}

/*
 * ceu_pawse_dt() - Initiawize async_subdevs pawsing device twee gwaph.
 */
static int ceu_pawse_dt(stwuct ceu_device *ceudev)
{
	stwuct device_node *of = ceudev->dev->of_node;
	stwuct device_node *ep;
	stwuct ceu_subdev *ceu_sd;
	unsigned int i;
	int num_ep;
	int wet;

	num_ep = of_gwaph_get_endpoint_count(of);
	if (!num_ep)
		wetuwn -ENODEV;

	wet = ceu_init_async_subdevs(ceudev, num_ep);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_ep; i++) {
		stwuct v4w2_fwnode_endpoint fw_ep = {
			.bus_type = V4W2_MBUS_PAWAWWEW,
			.bus = {
				.pawawwew = {
					.fwags = V4W2_MBUS_HSYNC_ACTIVE_HIGH |
						 V4W2_MBUS_VSYNC_ACTIVE_HIGH,
					.bus_width = 8,
				},
			},
		};

		ep = of_gwaph_get_endpoint_by_wegs(of, 0, i);
		if (!ep) {
			dev_eww(ceudev->dev,
				"No subdevice connected on endpoint %u.\n", i);
			wet = -ENODEV;
			goto ewwow_cweanup;
		}

		wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(ep), &fw_ep);
		if (wet) {
			dev_eww(ceudev->dev,
				"Unabwe to pawse endpoint #%u: %d.\n", i, wet);
			goto ewwow_cweanup;
		}

		/* Setup the ceu subdevice and the async subdevice. */
		ceu_sd = v4w2_async_nf_add_fwnode_wemote(&ceudev->notifiew,
							 of_fwnode_handwe(ep),
							 stwuct ceu_subdev);
		if (IS_EWW(ceu_sd)) {
			wet = PTW_EWW(ceu_sd);
			goto ewwow_cweanup;
		}
		ceu_sd->mbus_fwags = fw_ep.bus.pawawwew.fwags;
		ceudev->subdevs[i] = ceu_sd;

		of_node_put(ep);
	}

	wetuwn num_ep;

ewwow_cweanup:
	v4w2_async_nf_cweanup(&ceudev->notifiew);
	of_node_put(ep);
	wetuwn wet;
}

/*
 * stwuct ceu_data - Pwatfowm specific CEU data
 * @iwq_mask: CETCW mask with aww intewwupt souwces enabwed. The mask diffews
 *	      between SH4 and WZ pwatfowms.
 */
stwuct ceu_data {
	u32 iwq_mask;
};

static const stwuct ceu_data ceu_data_sh4 = {
	.iwq_mask = CEU_CETCW_AWW_IWQS_SH4,
};

#if IS_ENABWED(CONFIG_OF)
static const stwuct ceu_data ceu_data_wz = {
	.iwq_mask = CEU_CETCW_AWW_IWQS_WZ,
};

static const stwuct of_device_id ceu_of_match[] = {
	{ .compatibwe = "wenesas,w7s72100-ceu", .data = &ceu_data_wz },
	{ .compatibwe = "wenesas,w8a7740-ceu", .data = &ceu_data_wz },
	{ }
};
MODUWE_DEVICE_TABWE(of, ceu_of_match);
#endif

static int ceu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct ceu_data *ceu_data;
	stwuct ceu_device *ceudev;
	unsigned int iwq;
	int num_subdevs;
	int wet;

	ceudev = kzawwoc(sizeof(*ceudev), GFP_KEWNEW);
	if (!ceudev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ceudev);
	ceudev->dev = dev;

	INIT_WIST_HEAD(&ceudev->captuwe);
	spin_wock_init(&ceudev->wock);
	mutex_init(&ceudev->mwock);

	ceudev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ceudev->base)) {
		wet = PTW_EWW(ceudev->base);
		goto ewwow_fwee_ceudev;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto ewwow_fwee_ceudev;
	iwq = wet;

	wet = devm_wequest_iwq(dev, iwq, ceu_iwq,
			       0, dev_name(dev), ceudev);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to wequest CEU intewwupt.\n");
		goto ewwow_fwee_ceudev;
	}

	pm_wuntime_enabwe(dev);

	wet = v4w2_device_wegistew(dev, &ceudev->v4w2_dev);
	if (wet)
		goto ewwow_pm_disabwe;

	v4w2_async_nf_init(&ceudev->notifiew, &ceudev->v4w2_dev);

	if (IS_ENABWED(CONFIG_OF) && dev->of_node) {
		ceu_data = of_device_get_match_data(dev);
		num_subdevs = ceu_pawse_dt(ceudev);
	} ewse if (dev->pwatfowm_data) {
		/* Assume SH4 if booting with pwatfowm data. */
		ceu_data = &ceu_data_sh4;
		num_subdevs = ceu_pawse_pwatfowm_data(ceudev,
						      dev->pwatfowm_data);
	} ewse {
		num_subdevs = -EINVAW;
	}

	if (num_subdevs < 0) {
		wet = num_subdevs;
		goto ewwow_v4w2_unwegistew;
	}
	ceudev->iwq_mask = ceu_data->iwq_mask;

	ceudev->notifiew.v4w2_dev	= &ceudev->v4w2_dev;
	ceudev->notifiew.ops		= &ceu_notify_ops;
	wet = v4w2_async_nf_wegistew(&ceudev->notifiew);
	if (wet)
		goto ewwow_cweanup;

	dev_info(dev, "Wenesas Captuwe Engine Unit %s\n", dev_name(dev));

	wetuwn 0;

ewwow_cweanup:
	v4w2_async_nf_cweanup(&ceudev->notifiew);
ewwow_v4w2_unwegistew:
	v4w2_device_unwegistew(&ceudev->v4w2_dev);
ewwow_pm_disabwe:
	pm_wuntime_disabwe(dev);
ewwow_fwee_ceudev:
	kfwee(ceudev);

	wetuwn wet;
}

static void ceu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ceu_device *ceudev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(ceudev->dev);

	v4w2_async_nf_unwegistew(&ceudev->notifiew);

	v4w2_async_nf_cweanup(&ceudev->notifiew);

	v4w2_device_unwegistew(&ceudev->v4w2_dev);

	video_unwegistew_device(&ceudev->vdev);
}

static const stwuct dev_pm_ops ceu_pm_ops = {
	SET_WUNTIME_PM_OPS(ceu_wuntime_suspend,
			   ceu_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew ceu_dwivew = {
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm	= &ceu_pm_ops,
		.of_match_tabwe = of_match_ptw(ceu_of_match),
	},
	.pwobe		= ceu_pwobe,
	.wemove_new	= ceu_wemove,
};

moduwe_pwatfowm_dwivew(ceu_dwivew);

MODUWE_DESCWIPTION("Wenesas CEU camewa dwivew");
MODUWE_AUTHOW("Jacopo Mondi <jacopo+wenesas@jmondi.owg>");
MODUWE_WICENSE("GPW v2");
