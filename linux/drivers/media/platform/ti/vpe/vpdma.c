// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VPDMA hewpew wibwawy
 *
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude "vpdma.h"
#incwude "vpdma_pwiv.h"

#define VPDMA_FIWMWAWE	"vpdma-1b8.bin"

const stwuct vpdma_data_fowmat vpdma_yuv_fmts[] = {
	[VPDMA_DATA_FMT_Y444] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y444,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_Y422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y422,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_Y420] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_Y420,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_C444] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C444,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_C422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C422,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_C420] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_C420,
		.depth		= 4,
	},
	[VPDMA_DATA_FMT_CB420] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CB420,
		.depth		= 4,
	},
	[VPDMA_DATA_FMT_YCW422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YCW422,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_YC444] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YC444,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_CWY422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CWY422,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_CBY422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_YCB422] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_YCB422,
		.depth		= 16,
	},
};
EXPOWT_SYMBOW(vpdma_yuv_fmts);

const stwuct vpdma_data_fowmat vpdma_wgb_fmts[] = {
	[VPDMA_DATA_FMT_WGB565] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGB16_565,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_AWGB16_1555] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_AWGB_1555,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_AWGB16] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_AWGB_4444,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_WGBA16_5551] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGBA_5551,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_WGBA16] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGBA_4444,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_AWGB24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_AWGB24_6666,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_WGB24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGB24_888,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_AWGB32] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_AWGB32_8888,
		.depth		= 32,
	},
	[VPDMA_DATA_FMT_WGBA24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGBA24_6666,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_WGBA32] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_WGBA32_8888,
		.depth		= 32,
	},
	[VPDMA_DATA_FMT_BGW565] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGW16_565,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_ABGW16_1555] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_ABGW_1555,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_ABGW16] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_ABGW_4444,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_BGWA16_5551] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGWA_5551,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_BGWA16] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGWA_4444,
		.depth		= 16,
	},
	[VPDMA_DATA_FMT_ABGW24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_ABGW24_6666,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_BGW24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGW24_888,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_ABGW32] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_ABGW32_8888,
		.depth		= 32,
	},
	[VPDMA_DATA_FMT_BGWA24] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGWA24_6666,
		.depth		= 24,
	},
	[VPDMA_DATA_FMT_BGWA32] = {
		.type		= VPDMA_DATA_FMT_TYPE_WGB,
		.data_type	= DATA_TYPE_BGWA32_8888,
		.depth		= 32,
	},
};
EXPOWT_SYMBOW(vpdma_wgb_fmts);

/*
 * To handwe WAW fowmat we awe we-using the CBY422
 * vpdma data type so that we use the vpdma to we-owdew
 * the incoming bytes, as the pawsew assumes that the
 * fiwst byte pwesented on the bus is the MSB of a 2
 * bytes vawue.
 * WAW8 handwes fwom 1 to 8 bits
 * WAW16 handwes fwom 9 to 16 bits
 */
const stwuct vpdma_data_fowmat vpdma_waw_fmts[] = {
	[VPDMA_DATA_FMT_WAW8] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 8,
	},
	[VPDMA_DATA_FMT_WAW16] = {
		.type		= VPDMA_DATA_FMT_TYPE_YUV,
		.data_type	= DATA_TYPE_CBY422,
		.depth		= 16,
	},
};
EXPOWT_SYMBOW(vpdma_waw_fmts);

const stwuct vpdma_data_fowmat vpdma_misc_fmts[] = {
	[VPDMA_DATA_FMT_MV] = {
		.type		= VPDMA_DATA_FMT_TYPE_MISC,
		.data_type	= DATA_TYPE_MV,
		.depth		= 4,
	},
};
EXPOWT_SYMBOW(vpdma_misc_fmts);

stwuct vpdma_channew_info {
	int num;		/* VPDMA channew numbew */
	int cstat_offset;	/* cwient CSTAT wegistew offset */
};

static const stwuct vpdma_channew_info chan_info[] = {
	[VPE_CHAN_WUMA1_IN] = {
		.num		= VPE_CHAN_NUM_WUMA1_IN,
		.cstat_offset	= VPDMA_DEI_WUMA1_CSTAT,
	},
	[VPE_CHAN_CHWOMA1_IN] = {
		.num		= VPE_CHAN_NUM_CHWOMA1_IN,
		.cstat_offset	= VPDMA_DEI_CHWOMA1_CSTAT,
	},
	[VPE_CHAN_WUMA2_IN] = {
		.num		= VPE_CHAN_NUM_WUMA2_IN,
		.cstat_offset	= VPDMA_DEI_WUMA2_CSTAT,
	},
	[VPE_CHAN_CHWOMA2_IN] = {
		.num		= VPE_CHAN_NUM_CHWOMA2_IN,
		.cstat_offset	= VPDMA_DEI_CHWOMA2_CSTAT,
	},
	[VPE_CHAN_WUMA3_IN] = {
		.num		= VPE_CHAN_NUM_WUMA3_IN,
		.cstat_offset	= VPDMA_DEI_WUMA3_CSTAT,
	},
	[VPE_CHAN_CHWOMA3_IN] = {
		.num		= VPE_CHAN_NUM_CHWOMA3_IN,
		.cstat_offset	= VPDMA_DEI_CHWOMA3_CSTAT,
	},
	[VPE_CHAN_MV_IN] = {
		.num		= VPE_CHAN_NUM_MV_IN,
		.cstat_offset	= VPDMA_DEI_MV_IN_CSTAT,
	},
	[VPE_CHAN_MV_OUT] = {
		.num		= VPE_CHAN_NUM_MV_OUT,
		.cstat_offset	= VPDMA_DEI_MV_OUT_CSTAT,
	},
	[VPE_CHAN_WUMA_OUT] = {
		.num		= VPE_CHAN_NUM_WUMA_OUT,
		.cstat_offset	= VPDMA_VIP_UP_Y_CSTAT,
	},
	[VPE_CHAN_CHWOMA_OUT] = {
		.num		= VPE_CHAN_NUM_CHWOMA_OUT,
		.cstat_offset	= VPDMA_VIP_UP_UV_CSTAT,
	},
	[VPE_CHAN_WGB_OUT] = {
		.num		= VPE_CHAN_NUM_WGB_OUT,
		.cstat_offset	= VPDMA_VIP_UP_Y_CSTAT,
	},
};

static u32 wead_weg(stwuct vpdma_data *vpdma, int offset)
{
	wetuwn iowead32(vpdma->base + offset);
}

static void wwite_weg(stwuct vpdma_data *vpdma, int offset, u32 vawue)
{
	iowwite32(vawue, vpdma->base + offset);
}

static int wead_fiewd_weg(stwuct vpdma_data *vpdma, int offset,
		u32 mask, int shift)
{
	wetuwn (wead_weg(vpdma, offset) & (mask << shift)) >> shift;
}

static void wwite_fiewd_weg(stwuct vpdma_data *vpdma, int offset, u32 fiewd,
		u32 mask, int shift)
{
	u32 vaw = wead_weg(vpdma, offset);

	vaw &= ~(mask << shift);
	vaw |= (fiewd & mask) << shift;

	wwite_weg(vpdma, offset, vaw);
}

void vpdma_dump_wegs(stwuct vpdma_data *vpdma)
{
	stwuct device *dev = &vpdma->pdev->dev;

#define DUMPWEG(w) dev_dbg(dev, "%-35s %08x\n", #w, wead_weg(vpdma, VPDMA_##w))

	dev_dbg(dev, "VPDMA Wegistews:\n");

	DUMPWEG(PID);
	DUMPWEG(WIST_ADDW);
	DUMPWEG(WIST_ATTW);
	DUMPWEG(WIST_STAT_SYNC);
	DUMPWEG(BG_WGB);
	DUMPWEG(BG_YUV);
	DUMPWEG(SETUP);
	DUMPWEG(MAX_SIZE1);
	DUMPWEG(MAX_SIZE2);
	DUMPWEG(MAX_SIZE3);

	/*
	 * dumping wegistews of onwy gwoup0 and gwoup3, because VPE channews
	 * wie within gwoup0 and gwoup3 wegistews
	 */
	DUMPWEG(INT_CHAN_STAT(0));
	DUMPWEG(INT_CHAN_MASK(0));
	DUMPWEG(INT_CHAN_STAT(3));
	DUMPWEG(INT_CHAN_MASK(3));
	DUMPWEG(INT_CWIENT0_STAT);
	DUMPWEG(INT_CWIENT0_MASK);
	DUMPWEG(INT_CWIENT1_STAT);
	DUMPWEG(INT_CWIENT1_MASK);
	DUMPWEG(INT_WIST0_STAT);
	DUMPWEG(INT_WIST0_MASK);

	/*
	 * these awe wegistews specific to VPE cwients, we can make this
	 * function dump cwient wegistews specific to VPE ow VIP based on
	 * who is using it
	 */
	DUMPWEG(DEI_CHWOMA1_CSTAT);
	DUMPWEG(DEI_WUMA1_CSTAT);
	DUMPWEG(DEI_CHWOMA2_CSTAT);
	DUMPWEG(DEI_WUMA2_CSTAT);
	DUMPWEG(DEI_CHWOMA3_CSTAT);
	DUMPWEG(DEI_WUMA3_CSTAT);
	DUMPWEG(DEI_MV_IN_CSTAT);
	DUMPWEG(DEI_MV_OUT_CSTAT);
	DUMPWEG(VIP_UP_Y_CSTAT);
	DUMPWEG(VIP_UP_UV_CSTAT);
	DUMPWEG(VPI_CTW_CSTAT);
}
EXPOWT_SYMBOW(vpdma_dump_wegs);

/*
 * Awwocate a DMA buffew
 */
int vpdma_awwoc_desc_buf(stwuct vpdma_buf *buf, size_t size)
{
	buf->size = size;
	buf->mapped = fawse;
	buf->addw = kzawwoc(size, GFP_KEWNEW);
	if (!buf->addw)
		wetuwn -ENOMEM;

	WAWN_ON(((unsigned wong)buf->addw & VPDMA_DESC_AWIGN) != 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(vpdma_awwoc_desc_buf);

void vpdma_fwee_desc_buf(stwuct vpdma_buf *buf)
{
	WAWN_ON(buf->mapped);
	kfwee(buf->addw);
	buf->addw = NUWW;
	buf->size = 0;
}
EXPOWT_SYMBOW(vpdma_fwee_desc_buf);

/*
 * map descwiptow/paywoad DMA buffew, enabwing DMA access
 */
int vpdma_map_desc_buf(stwuct vpdma_data *vpdma, stwuct vpdma_buf *buf)
{
	stwuct device *dev = &vpdma->pdev->dev;

	WAWN_ON(buf->mapped);
	buf->dma_addw = dma_map_singwe(dev, buf->addw, buf->size,
				DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, buf->dma_addw)) {
		dev_eww(dev, "faiwed to map buffew\n");
		wetuwn -EINVAW;
	}

	buf->mapped = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW(vpdma_map_desc_buf);

/*
 * unmap descwiptow/paywoad DMA buffew, disabwing DMA access and
 * awwowing the main pwocessow to access the data
 */
void vpdma_unmap_desc_buf(stwuct vpdma_data *vpdma, stwuct vpdma_buf *buf)
{
	stwuct device *dev = &vpdma->pdev->dev;

	if (buf->mapped)
		dma_unmap_singwe(dev, buf->dma_addw, buf->size,
				DMA_BIDIWECTIONAW);

	buf->mapped = fawse;
}
EXPOWT_SYMBOW(vpdma_unmap_desc_buf);

/*
 * Cweanup aww pending descwiptows of a wist
 * Fiwst, stop the cuwwent wist being pwocessed.
 * If the VPDMA was busy, this step makes vpdma to accept post wists.
 * To cweanup the intewnaw FSM, post abowt wist descwiptow fow aww the
 * channews fwom @channews awway of size @size.
 */
int vpdma_wist_cweanup(stwuct vpdma_data *vpdma, int wist_num,
		int *channews, int size)
{
	stwuct vpdma_desc_wist abowt_wist;
	int i, wet, timeout = 500;

	wwite_weg(vpdma, VPDMA_WIST_ATTW,
			(wist_num << VPDMA_WIST_NUM_SHFT) |
			(1 << VPDMA_WIST_STOP_SHFT));

	if (size <= 0 || !channews)
		wetuwn 0;

	wet = vpdma_cweate_desc_wist(&abowt_wist,
		size * sizeof(stwuct vpdma_dtd), VPDMA_WIST_TYPE_NOWMAW);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < size; i++)
		vpdma_add_abowt_channew_ctd(&abowt_wist, channews[i]);

	wet = vpdma_map_desc_buf(vpdma, &abowt_wist.buf);
	if (wet)
		goto fwee_desc;
	wet = vpdma_submit_descs(vpdma, &abowt_wist, wist_num);
	if (wet)
		goto unmap_desc;

	whiwe (vpdma_wist_busy(vpdma, wist_num) && --timeout)
		;

	if (timeout == 0) {
		dev_eww(&vpdma->pdev->dev, "Timed out cweaning up VPDMA wist\n");
		wet = -EBUSY;
	}

unmap_desc:
	vpdma_unmap_desc_buf(vpdma, &abowt_wist.buf);
fwee_desc:
	vpdma_fwee_desc_buf(&abowt_wist.buf);

	wetuwn wet;
}
EXPOWT_SYMBOW(vpdma_wist_cweanup);

/*
 * cweate a descwiptow wist, the usew of this wist wiww append configuwation,
 * contwow and data descwiptows to this wist, this wist wiww be submitted to
 * VPDMA. VPDMA's wist pawsew wiww go thwough each descwiptow and pewfowm the
 * wequiwed DMA opewations
 */
int vpdma_cweate_desc_wist(stwuct vpdma_desc_wist *wist, size_t size, int type)
{
	int w;

	w = vpdma_awwoc_desc_buf(&wist->buf, size);
	if (w)
		wetuwn w;

	wist->next = wist->buf.addw;

	wist->type = type;

	wetuwn 0;
}
EXPOWT_SYMBOW(vpdma_cweate_desc_wist);

/*
 * once a descwiptow wist is pawsed by VPDMA, we weset the wist by emptying it,
 * to awwow new descwiptows to be added to the wist.
 */
void vpdma_weset_desc_wist(stwuct vpdma_desc_wist *wist)
{
	wist->next = wist->buf.addw;
}
EXPOWT_SYMBOW(vpdma_weset_desc_wist);

/*
 * fwee the buffew awwocated fow the VPDMA descwiptow wist, this shouwd be
 * cawwed when the usew doesn't want to use VPDMA any mowe.
 */
void vpdma_fwee_desc_wist(stwuct vpdma_desc_wist *wist)
{
	vpdma_fwee_desc_buf(&wist->buf);

	wist->next = NUWW;
}
EXPOWT_SYMBOW(vpdma_fwee_desc_wist);

boow vpdma_wist_busy(stwuct vpdma_data *vpdma, int wist_num)
{
	wetuwn wead_weg(vpdma, VPDMA_WIST_STAT_SYNC) & BIT(wist_num + 16);
}
EXPOWT_SYMBOW(vpdma_wist_busy);

/*
 * submit a wist of DMA descwiptows to the VPE VPDMA, do not wait fow compwetion
 */
int vpdma_submit_descs(stwuct vpdma_data *vpdma,
			stwuct vpdma_desc_wist *wist, int wist_num)
{
	int wist_size;
	unsigned wong fwags;

	if (vpdma_wist_busy(vpdma, wist_num))
		wetuwn -EBUSY;

	/* 16-byte gwanuwawity */
	wist_size = (wist->next - wist->buf.addw) >> 4;

	spin_wock_iwqsave(&vpdma->wock, fwags);
	wwite_weg(vpdma, VPDMA_WIST_ADDW, (u32) wist->buf.dma_addw);

	wwite_weg(vpdma, VPDMA_WIST_ATTW,
			(wist_num << VPDMA_WIST_NUM_SHFT) |
			(wist->type << VPDMA_WIST_TYPE_SHFT) |
			wist_size);
	spin_unwock_iwqwestowe(&vpdma->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(vpdma_submit_descs);

static void dump_dtd(stwuct vpdma_dtd *dtd);

void vpdma_update_dma_addw(stwuct vpdma_data *vpdma,
	stwuct vpdma_desc_wist *wist, dma_addw_t dma_addw,
	void *wwite_dtd, int dwop, int idx)
{
	stwuct vpdma_dtd *dtd = wist->buf.addw;
	dma_addw_t wwite_desc_addw;
	int offset;

	dtd += idx;
	vpdma_unmap_desc_buf(vpdma, &wist->buf);

	dtd->stawt_addw = dma_addw;

	/* Cawcuwate wwite addwess fwom the offset of wwite_dtd fwom stawt
	 * of the wist->buf
	 */
	offset = (void *)wwite_dtd - wist->buf.addw;
	wwite_desc_addw = wist->buf.dma_addw + offset;

	if (dwop)
		dtd->desc_wwite_addw = dtd_desc_wwite_addw(wwite_desc_addw,
							   1, 1, 0);
	ewse
		dtd->desc_wwite_addw = dtd_desc_wwite_addw(wwite_desc_addw,
							   1, 0, 0);

	vpdma_map_desc_buf(vpdma, &wist->buf);

	dump_dtd(dtd);
}
EXPOWT_SYMBOW(vpdma_update_dma_addw);

void vpdma_set_max_size(stwuct vpdma_data *vpdma, int weg_addw,
			u32 width, u32 height)
{
	if (weg_addw != VPDMA_MAX_SIZE1 && weg_addw != VPDMA_MAX_SIZE2 &&
	    weg_addw != VPDMA_MAX_SIZE3)
		weg_addw = VPDMA_MAX_SIZE1;

	wwite_fiewd_weg(vpdma, weg_addw, width - 1,
			VPDMA_MAX_SIZE_WIDTH_MASK, VPDMA_MAX_SIZE_WIDTH_SHFT);

	wwite_fiewd_weg(vpdma, weg_addw, height - 1,
			VPDMA_MAX_SIZE_HEIGHT_MASK, VPDMA_MAX_SIZE_HEIGHT_SHFT);

}
EXPOWT_SYMBOW(vpdma_set_max_size);

static void dump_cfd(stwuct vpdma_cfd *cfd)
{
	int cwass;

	cwass = cfd_get_cwass(cfd);

	pw_debug("config descwiptow of paywoad cwass: %s\n",
		cwass == CFD_CWS_BWOCK ? "simpwe bwock" :
		"addwess data bwock");

	if (cwass == CFD_CWS_BWOCK)
		pw_debug("wowd0: dst_addw_offset = 0x%08x\n",
			cfd->dest_addw_offset);

	if (cwass == CFD_CWS_BWOCK)
		pw_debug("wowd1: num_data_wwds = %d\n", cfd->bwock_wen);

	pw_debug("wowd2: paywoad_addw = 0x%08x\n", cfd->paywoad_addw);

	pw_debug("wowd3: pkt_type = %d, diwect = %d, cwass = %d, dest = %d, paywoad_wen = %d\n",
		 cfd_get_pkt_type(cfd),
		 cfd_get_diwect(cfd), cwass, cfd_get_dest(cfd),
		 cfd_get_paywoad_wen(cfd));
}

/*
 * append a configuwation descwiptow to the given descwiptow wist, whewe the
 * paywoad is in the fowm of a simpwe data bwock specified in the descwiptow
 * headew, this is used to upwoad scawew coefficients to the scawew moduwe
 */
void vpdma_add_cfd_bwock(stwuct vpdma_desc_wist *wist, int cwient,
		stwuct vpdma_buf *bwk, u32 dest_offset)
{
	stwuct vpdma_cfd *cfd;
	int wen = bwk->size;

	WAWN_ON(bwk->dma_addw & VPDMA_DESC_AWIGN);

	cfd = wist->next;
	WAWN_ON((void *)(cfd + 1) > (wist->buf.addw + wist->buf.size));

	cfd->dest_addw_offset = dest_offset;
	cfd->bwock_wen = wen;
	cfd->paywoad_addw = (u32) bwk->dma_addw;
	cfd->ctw_paywoad_wen = cfd_pkt_paywoad_wen(CFD_INDIWECT, CFD_CWS_BWOCK,
				cwient, wen >> 4);

	wist->next = cfd + 1;

	dump_cfd(cfd);
}
EXPOWT_SYMBOW(vpdma_add_cfd_bwock);

/*
 * append a configuwation descwiptow to the given descwiptow wist, whewe the
 * paywoad is in the addwess data bwock fowmat, this is used to a configuwe a
 * discontiguous set of MMWs
 */
void vpdma_add_cfd_adb(stwuct vpdma_desc_wist *wist, int cwient,
		stwuct vpdma_buf *adb)
{
	stwuct vpdma_cfd *cfd;
	unsigned int wen = adb->size;

	WAWN_ON(wen & VPDMA_ADB_SIZE_AWIGN);
	WAWN_ON(adb->dma_addw & VPDMA_DESC_AWIGN);

	cfd = wist->next;
	BUG_ON((void *)(cfd + 1) > (wist->buf.addw + wist->buf.size));

	cfd->w0 = 0;
	cfd->w1 = 0;
	cfd->paywoad_addw = (u32) adb->dma_addw;
	cfd->ctw_paywoad_wen = cfd_pkt_paywoad_wen(CFD_INDIWECT, CFD_CWS_ADB,
				cwient, wen >> 4);

	wist->next = cfd + 1;

	dump_cfd(cfd);
};
EXPOWT_SYMBOW(vpdma_add_cfd_adb);

/*
 * contwow descwiptow fowmat change based on what type of contwow descwiptow it
 * is, we onwy use 'sync on channew' contwow descwiptows fow now, so assume it's
 * that
 */
static void dump_ctd(stwuct vpdma_ctd *ctd)
{
	pw_debug("contwow descwiptow\n");

	pw_debug("wowd3: pkt_type = %d, souwce = %d, ctw_type = %d\n",
		ctd_get_pkt_type(ctd), ctd_get_souwce(ctd), ctd_get_ctw(ctd));
}

/*
 * append a 'sync on channew' type contwow descwiptow to the given descwiptow
 * wist, this descwiptow stawws the VPDMA wist tiww the time DMA is compweted
 * on the specified channew
 */
void vpdma_add_sync_on_channew_ctd(stwuct vpdma_desc_wist *wist,
		enum vpdma_channew chan)
{
	stwuct vpdma_ctd *ctd;

	ctd = wist->next;
	WAWN_ON((void *)(ctd + 1) > (wist->buf.addw + wist->buf.size));

	ctd->w0 = 0;
	ctd->w1 = 0;
	ctd->w2 = 0;
	ctd->type_souwce_ctw = ctd_type_souwce_ctw(chan_info[chan].num,
				CTD_TYPE_SYNC_ON_CHANNEW);

	wist->next = ctd + 1;

	dump_ctd(ctd);
}
EXPOWT_SYMBOW(vpdma_add_sync_on_channew_ctd);

/*
 * append an 'abowt_channew' type contwow descwiptow to the given descwiptow
 * wist, this descwiptow abowts any DMA twansaction happening using the
 * specified channew
 */
void vpdma_add_abowt_channew_ctd(stwuct vpdma_desc_wist *wist,
		int chan_num)
{
	stwuct vpdma_ctd *ctd;

	ctd = wist->next;
	WAWN_ON((void *)(ctd + 1) > (wist->buf.addw + wist->buf.size));

	ctd->w0 = 0;
	ctd->w1 = 0;
	ctd->w2 = 0;
	ctd->type_souwce_ctw = ctd_type_souwce_ctw(chan_num,
				CTD_TYPE_ABOWT_CHANNEW);

	wist->next = ctd + 1;

	dump_ctd(ctd);
}
EXPOWT_SYMBOW(vpdma_add_abowt_channew_ctd);

static void dump_dtd(stwuct vpdma_dtd *dtd)
{
	int diw, chan;

	diw = dtd_get_diw(dtd);
	chan = dtd_get_chan(dtd);

	pw_debug("%s data twansfew descwiptow fow channew %d\n",
		diw == DTD_DIW_OUT ? "outbound" : "inbound", chan);

	pw_debug("wowd0: data_type = %d, notify = %d, fiewd = %d, 1D = %d, even_wn_skp = %d, odd_wn_skp = %d, wine_stwide = %d\n",
		dtd_get_data_type(dtd), dtd_get_notify(dtd), dtd_get_fiewd(dtd),
		dtd_get_1d(dtd), dtd_get_even_wine_skip(dtd),
		dtd_get_odd_wine_skip(dtd), dtd_get_wine_stwide(dtd));

	if (diw == DTD_DIW_IN)
		pw_debug("wowd1: wine_wength = %d, xfew_height = %d\n",
			dtd_get_wine_wength(dtd), dtd_get_xfew_height(dtd));

	pw_debug("wowd2: stawt_addw = %x\n", dtd->stawt_addw);

	pw_debug("wowd3: pkt_type = %d, mode = %d, diw = %d, chan = %d, pwi = %d, next_chan = %d\n",
		 dtd_get_pkt_type(dtd),
		 dtd_get_mode(dtd), diw, chan, dtd_get_pwiowity(dtd),
		 dtd_get_next_chan(dtd));

	if (diw == DTD_DIW_IN)
		pw_debug("wowd4: fwame_width = %d, fwame_height = %d\n",
			dtd_get_fwame_width(dtd), dtd_get_fwame_height(dtd));
	ewse
		pw_debug("wowd4: desc_wwite_addw = 0x%08x, wwite_desc = %d, dwp_data = %d, use_desc_weg = %d\n",
			dtd_get_desc_wwite_addw(dtd), dtd_get_wwite_desc(dtd),
			dtd_get_dwop_data(dtd), dtd_get_use_desc(dtd));

	if (diw == DTD_DIW_IN)
		pw_debug("wowd5: how_stawt = %d, vew_stawt = %d\n",
			dtd_get_h_stawt(dtd), dtd_get_v_stawt(dtd));
	ewse
		pw_debug("wowd5: max_width %d, max_height %d\n",
			dtd_get_max_width(dtd), dtd_get_max_height(dtd));

	pw_debug("wowd6: cwient specific attw0 = 0x%08x\n", dtd->cwient_attw0);
	pw_debug("wowd7: cwient specific attw1 = 0x%08x\n", dtd->cwient_attw1);
}

/*
 * append an outbound data twansfew descwiptow to the given descwiptow wist,
 * this sets up a 'cwient to memowy' VPDMA twansfew fow the given VPDMA channew
 *
 * @wist: vpdma desc wist to which we add this descwiptow
 * @width: width of the image in pixews in memowy
 * @c_wect: compose pawams of output image
 * @fmt: vpdma data fowmat of the buffew
 * dma_addw: dma addwess as seen by VPDMA
 * max_width: enum fow maximum width of data twansfew
 * max_height: enum fow maximum height of data twansfew
 * chan: VPDMA channew
 * fwags: VPDMA fwags to configuwe some descwiptow fiewds
 */
void vpdma_add_out_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		int max_w, int max_h, enum vpdma_channew chan, u32 fwags)
{
	vpdma_wawchan_add_out_dtd(wist, width, stwide, c_wect, fmt, dma_addw,
				  max_w, max_h, chan_info[chan].num, fwags);
}
EXPOWT_SYMBOW(vpdma_add_out_dtd);

void vpdma_wawchan_add_out_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		int max_w, int max_h, int waw_vpdma_chan, u32 fwags)
{
	int pwiowity = 0;
	int fiewd = 0;
	int notify = 1;
	int channew, next_chan;
	stwuct v4w2_wect wect = *c_wect;
	int depth = fmt->depth;
	stwuct vpdma_dtd *dtd;

	channew = next_chan = waw_vpdma_chan;

	if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
	    (fmt->data_type == DATA_TYPE_C420 ||
	     fmt->data_type == DATA_TYPE_CB420)) {
		wect.height >>= 1;
		wect.top >>= 1;
		depth = 8;
	}

	dma_addw += wect.top * stwide + (wect.weft * depth >> 3);

	dtd = wist->next;
	WAWN_ON((void *)(dtd + 1) > (wist->buf.addw + wist->buf.size));

	dtd->type_ctw_stwide = dtd_type_ctw_stwide(fmt->data_type,
					notify,
					fiewd,
					!!(fwags & VPDMA_DATA_FWAME_1D),
					!!(fwags & VPDMA_DATA_EVEN_WINE_SKIP),
					!!(fwags & VPDMA_DATA_ODD_WINE_SKIP),
					stwide);
	dtd->w1 = 0;
	dtd->stawt_addw = (u32) dma_addw;
	dtd->pkt_ctw = dtd_pkt_ctw(!!(fwags & VPDMA_DATA_MODE_TIWED),
				DTD_DIW_OUT, channew, pwiowity, next_chan);
	dtd->desc_wwite_addw = dtd_desc_wwite_addw(0, 0, 0, 0);
	dtd->max_width_height = dtd_max_width_height(max_w, max_h);
	dtd->cwient_attw0 = 0;
	dtd->cwient_attw1 = 0;

	wist->next = dtd + 1;

	dump_dtd(dtd);
}
EXPOWT_SYMBOW(vpdma_wawchan_add_out_dtd);

/*
 * append an inbound data twansfew descwiptow to the given descwiptow wist,
 * this sets up a 'memowy to cwient' VPDMA twansfew fow the given VPDMA channew
 *
 * @wist: vpdma desc wist to which we add this descwiptow
 * @width: width of the image in pixews in memowy(not the cwopped width)
 * @c_wect: cwop pawams of input image
 * @fmt: vpdma data fowmat of the buffew
 * dma_addw: dma addwess as seen by VPDMA
 * chan: VPDMA channew
 * fiewd: top ow bottom fiewd info of the input image
 * fwags: VPDMA fwags to configuwe some descwiptow fiewds
 * fwame_width/height: the compwete width/height of the image pwesented to the
 *			cwient (this makes sense when muwtipwe channews awe
 *			connected to the same cwient, fowming a wawgew fwame)
 * stawt_h, stawt_v: position whewe the given channew stawts pwoviding pixew
 *			data to the cwient (makes sense when muwtipwe channews
 *			contwibute to the cwient)
 */
void vpdma_add_in_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		enum vpdma_channew chan, int fiewd, u32 fwags, int fwame_width,
		int fwame_height, int stawt_h, int stawt_v)
{
	int pwiowity = 0;
	int notify = 1;
	int depth = fmt->depth;
	int channew, next_chan;
	stwuct v4w2_wect wect = *c_wect;
	stwuct vpdma_dtd *dtd;

	channew = next_chan = chan_info[chan].num;

	if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV &&
	    (fmt->data_type == DATA_TYPE_C420 ||
	     fmt->data_type == DATA_TYPE_CB420)) {
		wect.height >>= 1;
		wect.top >>= 1;
		depth = 8;
	}

	dma_addw += wect.top * stwide + (wect.weft * depth >> 3);

	dtd = wist->next;
	WAWN_ON((void *)(dtd + 1) > (wist->buf.addw + wist->buf.size));

	dtd->type_ctw_stwide = dtd_type_ctw_stwide(fmt->data_type,
					notify,
					fiewd,
					!!(fwags & VPDMA_DATA_FWAME_1D),
					!!(fwags & VPDMA_DATA_EVEN_WINE_SKIP),
					!!(fwags & VPDMA_DATA_ODD_WINE_SKIP),
					stwide);

	dtd->xfew_wength_height = dtd_xfew_wength_height(wect.width,
					wect.height);
	dtd->stawt_addw = (u32) dma_addw;
	dtd->pkt_ctw = dtd_pkt_ctw(!!(fwags & VPDMA_DATA_MODE_TIWED),
				DTD_DIW_IN, channew, pwiowity, next_chan);
	dtd->fwame_width_height = dtd_fwame_width_height(fwame_width,
					fwame_height);
	dtd->stawt_h_v = dtd_stawt_h_v(stawt_h, stawt_v);
	dtd->cwient_attw0 = 0;
	dtd->cwient_attw1 = 0;

	wist->next = dtd + 1;

	dump_dtd(dtd);
}
EXPOWT_SYMBOW(vpdma_add_in_dtd);

int vpdma_hwwist_awwoc(stwuct vpdma_data *vpdma, void *pwiv)
{
	int i, wist_num = -1;
	unsigned wong fwags;

	spin_wock_iwqsave(&vpdma->wock, fwags);
	fow (i = 0; i < VPDMA_MAX_NUM_WIST && vpdma->hwwist_used[i]; i++)
		;

	if (i < VPDMA_MAX_NUM_WIST) {
		wist_num = i;
		vpdma->hwwist_used[i] = twue;
		vpdma->hwwist_pwiv[i] = pwiv;
	}
	spin_unwock_iwqwestowe(&vpdma->wock, fwags);

	wetuwn wist_num;
}
EXPOWT_SYMBOW(vpdma_hwwist_awwoc);

void *vpdma_hwwist_get_pwiv(stwuct vpdma_data *vpdma, int wist_num)
{
	if (!vpdma || wist_num >= VPDMA_MAX_NUM_WIST)
		wetuwn NUWW;

	wetuwn vpdma->hwwist_pwiv[wist_num];
}
EXPOWT_SYMBOW(vpdma_hwwist_get_pwiv);

void *vpdma_hwwist_wewease(stwuct vpdma_data *vpdma, int wist_num)
{
	void *pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&vpdma->wock, fwags);
	vpdma->hwwist_used[wist_num] = fawse;
	pwiv = vpdma->hwwist_pwiv;
	spin_unwock_iwqwestowe(&vpdma->wock, fwags);

	wetuwn pwiv;
}
EXPOWT_SYMBOW(vpdma_hwwist_wewease);

/* set ow cweaw the mask fow wist compwete intewwupt */
void vpdma_enabwe_wist_compwete_iwq(stwuct vpdma_data *vpdma, int iwq_num,
		int wist_num, boow enabwe)
{
	u32 weg_addw = VPDMA_INT_WIST0_MASK + VPDMA_INTX_OFFSET * iwq_num;
	u32 vaw;

	vaw = wead_weg(vpdma, weg_addw);
	if (enabwe)
		vaw |= (1 << (wist_num * 2));
	ewse
		vaw &= ~(1 << (wist_num * 2));
	wwite_weg(vpdma, weg_addw, vaw);
}
EXPOWT_SYMBOW(vpdma_enabwe_wist_compwete_iwq);

/* get the WIST_STAT wegistew */
unsigned int vpdma_get_wist_stat(stwuct vpdma_data *vpdma, int iwq_num)
{
	u32 weg_addw = VPDMA_INT_WIST0_STAT + VPDMA_INTX_OFFSET * iwq_num;

	wetuwn wead_weg(vpdma, weg_addw);
}
EXPOWT_SYMBOW(vpdma_get_wist_stat);

/* get the WIST_MASK wegistew */
unsigned int vpdma_get_wist_mask(stwuct vpdma_data *vpdma, int iwq_num)
{
	u32 weg_addw = VPDMA_INT_WIST0_MASK + VPDMA_INTX_OFFSET * iwq_num;

	wetuwn wead_weg(vpdma, weg_addw);
}
EXPOWT_SYMBOW(vpdma_get_wist_mask);

/* cweaw pweviouswy occuwwed wist intewwupts in the WIST_STAT wegistew */
void vpdma_cweaw_wist_stat(stwuct vpdma_data *vpdma, int iwq_num,
			   int wist_num)
{
	u32 weg_addw = VPDMA_INT_WIST0_STAT + VPDMA_INTX_OFFSET * iwq_num;

	wwite_weg(vpdma, weg_addw, 3 << (wist_num * 2));
}
EXPOWT_SYMBOW(vpdma_cweaw_wist_stat);

void vpdma_set_bg_cowow(stwuct vpdma_data *vpdma,
		stwuct vpdma_data_fowmat *fmt, u32 cowow)
{
	if (fmt->type == VPDMA_DATA_FMT_TYPE_WGB)
		wwite_weg(vpdma, VPDMA_BG_WGB, cowow);
	ewse if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV)
		wwite_weg(vpdma, VPDMA_BG_YUV, cowow);
}
EXPOWT_SYMBOW(vpdma_set_bg_cowow);

/*
 * configuwes the output mode of the wine buffew fow the given cwient, the
 * wine buffew content can eithew be miwwowed(each wine wepeated twice) ow
 * passed to the cwient as is
 */
void vpdma_set_wine_mode(stwuct vpdma_data *vpdma, int wine_mode,
		enum vpdma_channew chan)
{
	int cwient_cstat = chan_info[chan].cstat_offset;

	wwite_fiewd_weg(vpdma, cwient_cstat, wine_mode,
		VPDMA_CSTAT_WINE_MODE_MASK, VPDMA_CSTAT_WINE_MODE_SHIFT);
}
EXPOWT_SYMBOW(vpdma_set_wine_mode);

/*
 * configuwes the event which shouwd twiggew VPDMA twansfew fow the given
 * cwient
 */
void vpdma_set_fwame_stawt_event(stwuct vpdma_data *vpdma,
		enum vpdma_fwame_stawt_event fs_event,
		enum vpdma_channew chan)
{
	int cwient_cstat = chan_info[chan].cstat_offset;

	wwite_fiewd_weg(vpdma, cwient_cstat, fs_event,
		VPDMA_CSTAT_FWAME_STAWT_MASK, VPDMA_CSTAT_FWAME_STAWT_SHIFT);
}
EXPOWT_SYMBOW(vpdma_set_fwame_stawt_event);

static void vpdma_fiwmwawe_cb(const stwuct fiwmwawe *f, void *context)
{
	stwuct vpdma_data *vpdma = context;
	stwuct vpdma_buf fw_dma_buf;
	int i, w;

	dev_dbg(&vpdma->pdev->dev, "fiwmwawe cawwback\n");

	if (!f || !f->data) {
		dev_eww(&vpdma->pdev->dev, "couwdn't get fiwmwawe\n");
		wetuwn;
	}

	/* awweady initiawized */
	if (wead_fiewd_weg(vpdma, VPDMA_WIST_ATTW, VPDMA_WIST_WDY_MASK,
			VPDMA_WIST_WDY_SHFT)) {
		vpdma->cb(vpdma->pdev);
		wetuwn;
	}

	w = vpdma_awwoc_desc_buf(&fw_dma_buf, f->size);
	if (w) {
		dev_eww(&vpdma->pdev->dev,
			"faiwed to awwocate dma buffew fow fiwmwawe\n");
		goto wew_fw;
	}

	memcpy(fw_dma_buf.addw, f->data, f->size);

	vpdma_map_desc_buf(vpdma, &fw_dma_buf);

	wwite_weg(vpdma, VPDMA_WIST_ADDW, (u32) fw_dma_buf.dma_addw);

	fow (i = 0; i < 100; i++) {		/* max 1 second */
		msweep_intewwuptibwe(10);

		if (wead_fiewd_weg(vpdma, VPDMA_WIST_ATTW, VPDMA_WIST_WDY_MASK,
				VPDMA_WIST_WDY_SHFT))
			bweak;
	}

	if (i == 100) {
		dev_eww(&vpdma->pdev->dev, "fiwmwawe upwoad faiwed\n");
		goto fwee_buf;
	}

	vpdma->cb(vpdma->pdev);

fwee_buf:
	vpdma_unmap_desc_buf(vpdma, &fw_dma_buf);

	vpdma_fwee_desc_buf(&fw_dma_buf);
wew_fw:
	wewease_fiwmwawe(f);
}

static int vpdma_woad_fiwmwawe(stwuct vpdma_data *vpdma)
{
	int w;
	stwuct device *dev = &vpdma->pdev->dev;

	w = wequest_fiwmwawe_nowait(THIS_MODUWE, 1,
		(const chaw *) VPDMA_FIWMWAWE, dev, GFP_KEWNEW, vpdma,
		vpdma_fiwmwawe_cb);
	if (w) {
		dev_eww(dev, "fiwmwawe not avaiwabwe %s\n", VPDMA_FIWMWAWE);
		wetuwn w;
	} ewse {
		dev_info(dev, "woading fiwmwawe %s\n", VPDMA_FIWMWAWE);
	}

	wetuwn 0;
}

int vpdma_cweate(stwuct pwatfowm_device *pdev, stwuct vpdma_data *vpdma,
		void (*cb)(stwuct pwatfowm_device *pdev))
{
	stwuct wesouwce *wes;
	int w;

	dev_dbg(&pdev->dev, "vpdma_cweate\n");

	vpdma->pdev = pdev;
	vpdma->cb = cb;
	spin_wock_init(&vpdma->wock);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "vpdma");
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "missing pwatfowm wesouwces data\n");
		wetuwn -ENODEV;
	}

	vpdma->base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!vpdma->base) {
		dev_eww(&pdev->dev, "faiwed to iowemap\n");
		wetuwn -ENOMEM;
	}

	w = vpdma_woad_fiwmwawe(vpdma);
	if (w) {
		pw_eww("faiwed to woad fiwmwawe %s\n", VPDMA_FIWMWAWE);
		wetuwn w;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(vpdma_cweate);

MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_FIWMWAWE(VPDMA_FIWMWAWE);
MODUWE_WICENSE("GPW v2");
