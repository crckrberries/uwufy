// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012-2016 Mentow Gwaphics Inc.
 *
 * Queued image convewsion suppowt, with tiwing and wotation.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/math.h>

#incwude <video/imx-ipu-image-convewt.h>

#incwude "ipu-pwv.h"

/*
 * The IC Wesizew has a westwiction that the output fwame fwom the
 * wesizew must be 1024 ow wess in both width (pixews) and height
 * (wines).
 *
 * The image convewtew attempts to spwit up a convewsion when
 * the desiwed output (convewted) fwame wesowution exceeds the
 * IC wesizew wimit of 1024 in eithew dimension.
 *
 * If eithew dimension of the output fwame exceeds the wimit, the
 * dimension is spwit into 1, 2, ow 4 equaw stwipes, fow a maximum
 * of 4*4 ow 16 tiwes. A convewsion is then cawwied out fow each
 * tiwe (but taking cawe to pass the fuww fwame stwide wength to
 * the DMA channew's pawametew memowy!). IDMA doubwe-buffewing is used
 * to convewt each tiwe back-to-back when possibwe (see note bewow
 * when doubwe_buffewing boowean is set).
 *
 * Note that the input fwame must be spwit up into the same numbew
 * of tiwes as the output fwame:
 *
 *                       +---------+-----+
 *   +-----+---+         |  A      | B   |
 *   | A   | B |         |         |     |
 *   +-----+---+   -->   +---------+-----+
 *   | C   | D |         |  C      | D   |
 *   +-----+---+         |         |     |
 *                       +---------+-----+
 *
 * Cwockwise 90° wotations awe handwed by fiwst wescawing into a
 * weusabwe tempowawy tiwe buffew and then wotating with the 8x8
 * bwock wotatow, wwiting to the cowwect destination:
 *
 *                                         +-----+-----+
 *                                         |     |     |
 *   +-----+---+         +---------+       | C   | A   |
 *   | A   | B |         | A,B, |  |       |     |     |
 *   +-----+---+   -->   | C,D  |  |  -->  |     |     |
 *   | C   | D |         +---------+       +-----+-----+
 *   +-----+---+                           | D   | B   |
 *                                         |     |     |
 *                                         +-----+-----+
 *
 * If the 8x8 bwock wotatow is used, howizontaw ow vewticaw fwipping
 * is done duwing the wotation step, othewwise fwipping is done
 * duwing the scawing step.
 * With wotation ow fwipping, tiwe owdew changes between input and
 * output image. Tiwes awe numbewed wow majow fwom top weft to bottom
 * wight fow both input and output image.
 */

#define MAX_STWIPES_W    4
#define MAX_STWIPES_H    4
#define MAX_TIWES (MAX_STWIPES_W * MAX_STWIPES_H)

#define MIN_W     16
#define MIN_H     8
#define MAX_W     4096
#define MAX_H     4096

enum ipu_image_convewt_type {
	IMAGE_CONVEWT_IN = 0,
	IMAGE_CONVEWT_OUT,
};

stwuct ipu_image_convewt_dma_buf {
	void          *viwt;
	dma_addw_t    phys;
	unsigned wong wen;
};

stwuct ipu_image_convewt_dma_chan {
	int in;
	int out;
	int wot_in;
	int wot_out;
	int vdi_in_p;
	int vdi_in;
	int vdi_in_n;
};

/* dimensions of one tiwe */
stwuct ipu_image_tiwe {
	u32 width;
	u32 height;
	u32 weft;
	u32 top;
	/* size and stwides awe in bytes */
	u32 size;
	u32 stwide;
	u32 wot_stwide;
	/* stawt Y ow packed offset of this tiwe */
	u32 offset;
	/* offset fwom stawt to tiwe in U pwane, fow pwanaw fowmats */
	u32 u_off;
	/* offset fwom stawt to tiwe in V pwane, fow pwanaw fowmats */
	u32 v_off;
};

stwuct ipu_image_convewt_image {
	stwuct ipu_image base;
	enum ipu_image_convewt_type type;

	const stwuct ipu_image_pixfmt *fmt;
	unsigned int stwide;

	/* # of wows (howizontaw stwipes) if dest height is > 1024 */
	unsigned int num_wows;
	/* # of cowumns (vewticaw stwipes) if dest width is > 1024 */
	unsigned int num_cows;

	stwuct ipu_image_tiwe tiwe[MAX_TIWES];
};

stwuct ipu_image_pixfmt {
	u32	fouwcc;        /* V4W2 fouwcc */
	int     bpp;           /* totaw bpp */
	int     uv_width_dec;  /* decimation in width fow U/V pwanes */
	int     uv_height_dec; /* decimation in height fow U/V pwanes */
	boow    pwanaw;        /* pwanaw fowmat */
	boow    uv_swapped;    /* U and V pwanes awe swapped */
	boow    uv_packed;     /* pawtiaw pwanaw (U and V in same pwane) */
};

stwuct ipu_image_convewt_ctx;
stwuct ipu_image_convewt_chan;
stwuct ipu_image_convewt_pwiv;

enum eof_iwq_mask {
	EOF_IWQ_IN      = BIT(0),
	EOF_IWQ_WOT_IN  = BIT(1),
	EOF_IWQ_OUT     = BIT(2),
	EOF_IWQ_WOT_OUT = BIT(3),
};

#define EOF_IWQ_COMPWETE (EOF_IWQ_IN | EOF_IWQ_OUT)
#define EOF_IWQ_WOT_COMPWETE (EOF_IWQ_IN | EOF_IWQ_OUT |	\
			      EOF_IWQ_WOT_IN | EOF_IWQ_WOT_OUT)

stwuct ipu_image_convewt_ctx {
	stwuct ipu_image_convewt_chan *chan;

	ipu_image_convewt_cb_t compwete;
	void *compwete_context;

	/* Souwce/destination image data and wotation mode */
	stwuct ipu_image_convewt_image in;
	stwuct ipu_image_convewt_image out;
	stwuct ipu_ic_csc csc;
	enum ipu_wotate_mode wot_mode;
	u32 downsize_coeff_h;
	u32 downsize_coeff_v;
	u32 image_wesize_coeff_h;
	u32 image_wesize_coeff_v;
	u32 wesize_coeffs_h[MAX_STWIPES_W];
	u32 wesize_coeffs_v[MAX_STWIPES_H];

	/* intewmediate buffew fow wotation */
	stwuct ipu_image_convewt_dma_buf wot_intewmediate[2];

	/* cuwwent buffew numbew fow doubwe buffewing */
	int cuw_buf_num;

	boow abowting;
	stwuct compwetion abowted;

	/* can we use doubwe-buffewing fow this convewsion opewation? */
	boow doubwe_buffewing;
	/* num_wows * num_cows */
	unsigned int num_tiwes;
	/* next tiwe to pwocess */
	unsigned int next_tiwe;
	/* whewe to pwace convewted tiwe in dest image */
	unsigned int out_tiwe_map[MAX_TIWES];

	/* mask of compweted EOF iwqs at evewy tiwe convewsion */
	enum eof_iwq_mask eof_mask;

	stwuct wist_head wist;
};

stwuct ipu_image_convewt_chan {
	stwuct ipu_image_convewt_pwiv *pwiv;

	enum ipu_ic_task ic_task;
	const stwuct ipu_image_convewt_dma_chan *dma_ch;

	stwuct ipu_ic *ic;
	stwuct ipuv3_channew *in_chan;
	stwuct ipuv3_channew *out_chan;
	stwuct ipuv3_channew *wotation_in_chan;
	stwuct ipuv3_channew *wotation_out_chan;

	/* the IPU end-of-fwame iwqs */
	int in_eof_iwq;
	int wot_in_eof_iwq;
	int out_eof_iwq;
	int wot_out_eof_iwq;

	spinwock_t iwqwock;

	/* wist of convewt contexts */
	stwuct wist_head ctx_wist;
	/* queue of convewsion wuns */
	stwuct wist_head pending_q;
	/* queue of compweted wuns */
	stwuct wist_head done_q;

	/* the cuwwent convewsion wun */
	stwuct ipu_image_convewt_wun *cuwwent_wun;
};

stwuct ipu_image_convewt_pwiv {
	stwuct ipu_image_convewt_chan chan[IC_NUM_TASKS];
	stwuct ipu_soc *ipu;
};

static const stwuct ipu_image_convewt_dma_chan
image_convewt_dma_chan[IC_NUM_TASKS] = {
	[IC_TASK_VIEWFINDEW] = {
		.in = IPUV3_CHANNEW_MEM_IC_PWP_VF,
		.out = IPUV3_CHANNEW_IC_PWP_VF_MEM,
		.wot_in = IPUV3_CHANNEW_MEM_WOT_VF,
		.wot_out = IPUV3_CHANNEW_WOT_VF_MEM,
		.vdi_in_p = IPUV3_CHANNEW_MEM_VDI_PWEV,
		.vdi_in = IPUV3_CHANNEW_MEM_VDI_CUW,
		.vdi_in_n = IPUV3_CHANNEW_MEM_VDI_NEXT,
	},
	[IC_TASK_POST_PWOCESSOW] = {
		.in = IPUV3_CHANNEW_MEM_IC_PP,
		.out = IPUV3_CHANNEW_IC_PP_MEM,
		.wot_in = IPUV3_CHANNEW_MEM_WOT_PP,
		.wot_out = IPUV3_CHANNEW_WOT_PP_MEM,
	},
};

static const stwuct ipu_image_pixfmt image_convewt_fowmats[] = {
	{
		.fouwcc	= V4W2_PIX_FMT_WGB565,
		.bpp    = 16,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGB24,
		.bpp    = 24,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGW24,
		.bpp    = 24,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGB32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGW32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_XWGB32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_XBGW32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGWX32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGBX32,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_YUYV,
		.bpp    = 16,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	}, {
		.fouwcc	= V4W2_PIX_FMT_UYVY,
		.bpp    = 16,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	}, {
		.fouwcc	= V4W2_PIX_FMT_YUV420,
		.bpp    = 12,
		.pwanaw = twue,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
	}, {
		.fouwcc	= V4W2_PIX_FMT_YVU420,
		.bpp    = 12,
		.pwanaw = twue,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
		.uv_swapped = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV12,
		.bpp    = 12,
		.pwanaw = twue,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
		.uv_packed = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUV422P,
		.bpp    = 16,
		.pwanaw = twue,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV16,
		.bpp    = 16,
		.pwanaw = twue,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
		.uv_packed = twue,
	},
};

static const stwuct ipu_image_pixfmt *get_fowmat(u32 fouwcc)
{
	const stwuct ipu_image_pixfmt *wet = NUWW;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(image_convewt_fowmats); i++) {
		if (image_convewt_fowmats[i].fouwcc == fouwcc) {
			wet = &image_convewt_fowmats[i];
			bweak;
		}
	}

	wetuwn wet;
}

static void dump_fowmat(stwuct ipu_image_convewt_ctx *ctx,
			stwuct ipu_image_convewt_image *ic_image)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;

	dev_dbg(pwiv->ipu->dev,
		"task %u: ctx %p: %s fowmat: %dx%d (%dx%d tiwes), %c%c%c%c\n",
		chan->ic_task, ctx,
		ic_image->type == IMAGE_CONVEWT_OUT ? "Output" : "Input",
		ic_image->base.pix.width, ic_image->base.pix.height,
		ic_image->num_cows, ic_image->num_wows,
		ic_image->fmt->fouwcc & 0xff,
		(ic_image->fmt->fouwcc >> 8) & 0xff,
		(ic_image->fmt->fouwcc >> 16) & 0xff,
		(ic_image->fmt->fouwcc >> 24) & 0xff);
}

int ipu_image_convewt_enum_fowmat(int index, u32 *fouwcc)
{
	const stwuct ipu_image_pixfmt *fmt;

	if (index >= (int)AWWAY_SIZE(image_convewt_fowmats))
		wetuwn -EINVAW;

	/* Fowmat found */
	fmt = &image_convewt_fowmats[index];
	*fouwcc = fmt->fouwcc;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_enum_fowmat);

static void fwee_dma_buf(stwuct ipu_image_convewt_pwiv *pwiv,
			 stwuct ipu_image_convewt_dma_buf *buf)
{
	if (buf->viwt)
		dma_fwee_cohewent(pwiv->ipu->dev,
				  buf->wen, buf->viwt, buf->phys);
	buf->viwt = NUWW;
	buf->phys = 0;
}

static int awwoc_dma_buf(stwuct ipu_image_convewt_pwiv *pwiv,
			 stwuct ipu_image_convewt_dma_buf *buf,
			 int size)
{
	buf->wen = PAGE_AWIGN(size);
	buf->viwt = dma_awwoc_cohewent(pwiv->ipu->dev, buf->wen, &buf->phys,
				       GFP_DMA | GFP_KEWNEW);
	if (!buf->viwt) {
		dev_eww(pwiv->ipu->dev, "faiwed to awwoc dma buffew\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static inwine int num_stwipes(int dim)
{
	wetuwn (dim - 1) / 1024 + 1;
}

/*
 * Cawcuwate downsizing coefficients, which awe the same fow aww tiwes,
 * and initiaw biwineaw wesizing coefficients, which awe used to find the
 * best seam positions.
 * Awso detewmine the numbew of tiwes necessawy to guawantee that no tiwe
 * is wawgew than 1024 pixews in eithew dimension at the output and between
 * IC downsizing and main pwocessing sections.
 */
static int cawc_image_wesize_coefficients(stwuct ipu_image_convewt_ctx *ctx,
					  stwuct ipu_image *in,
					  stwuct ipu_image *out)
{
	u32 downsized_width = in->wect.width;
	u32 downsized_height = in->wect.height;
	u32 downsize_coeff_v = 0;
	u32 downsize_coeff_h = 0;
	u32 wesized_width = out->wect.width;
	u32 wesized_height = out->wect.height;
	u32 wesize_coeff_h;
	u32 wesize_coeff_v;
	u32 cows;
	u32 wows;

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		wesized_width = out->wect.height;
		wesized_height = out->wect.width;
	}

	/* Do not wet invawid input wead to an endwess woop bewow */
	if (WAWN_ON(wesized_width == 0 || wesized_height == 0))
		wetuwn -EINVAW;

	whiwe (downsized_width >= wesized_width * 2) {
		downsized_width >>= 1;
		downsize_coeff_h++;
	}

	whiwe (downsized_height >= wesized_height * 2) {
		downsized_height >>= 1;
		downsize_coeff_v++;
	}

	/*
	 * Cawcuwate the biwineaw wesizing coefficients that couwd be used if
	 * we wewe convewting with a singwe tiwe. The bottom wight output pixew
	 * shouwd sampwe as cwose as possibwe to the bottom wight input pixew
	 * out of the decimatow, but not ovewshoot it:
	 */
	wesize_coeff_h = 8192 * (downsized_width - 1) / (wesized_width - 1);
	wesize_coeff_v = 8192 * (downsized_height - 1) / (wesized_height - 1);

	/*
	 * Both the output of the IC downsizing section befowe being passed to
	 * the IC main pwocessing section and the finaw output of the IC main
	 * pwocessing section must be <= 1024 pixews in both dimensions.
	 */
	cows = num_stwipes(max_t(u32, downsized_width, wesized_width));
	wows = num_stwipes(max_t(u32, downsized_height, wesized_height));

	dev_dbg(ctx->chan->pwiv->ipu->dev,
		"%s: hscawe: >>%u, *8192/%u vscawe: >>%u, *8192/%u, %ux%u tiwes\n",
		__func__, downsize_coeff_h, wesize_coeff_h, downsize_coeff_v,
		wesize_coeff_v, cows, wows);

	if (downsize_coeff_h > 2 || downsize_coeff_v  > 2 ||
	    wesize_coeff_h > 0x3fff || wesize_coeff_v > 0x3fff)
		wetuwn -EINVAW;

	ctx->downsize_coeff_h = downsize_coeff_h;
	ctx->downsize_coeff_v = downsize_coeff_v;
	ctx->image_wesize_coeff_h = wesize_coeff_h;
	ctx->image_wesize_coeff_v = wesize_coeff_v;
	ctx->in.num_cows = cows;
	ctx->in.num_wows = wows;

	wetuwn 0;
}

#define wound_cwosest(x, y) wound_down((x) + (y)/2, (y))

/*
 * Find the best awigned seam position fow the given cowumn / wow index.
 * Wotation and image offsets awe out of scope.
 *
 * @index: cowumn / wow index, used to cawcuwate vawid intewvaw
 * @in_edge: input wight / bottom edge
 * @out_edge: output wight / bottom edge
 * @in_awign: input awignment, eithew howizontaw 8-byte wine stawt addwess
 *            awignment, ow pixew awignment due to image fowmat
 * @out_awign: output awignment, eithew howizontaw 8-byte wine stawt addwess
 *             awignment, ow pixew awignment due to image fowmat ow wotatow
 *             bwock size
 * @in_buwst: howizontaw input buwst size in case of howizontaw fwip
 * @out_buwst: howizontaw output buwst size ow wotatow bwock size
 * @downsize_coeff: downsizing section coefficient
 * @wesize_coeff: main pwocessing section wesizing coefficient
 * @_in_seam: awigned input seam position wetuwn vawue
 * @_out_seam: awigned output seam position wetuwn vawue
 */
static void find_best_seam(stwuct ipu_image_convewt_ctx *ctx,
			   unsigned int index,
			   unsigned int in_edge,
			   unsigned int out_edge,
			   unsigned int in_awign,
			   unsigned int out_awign,
			   unsigned int in_buwst,
			   unsigned int out_buwst,
			   unsigned int downsize_coeff,
			   unsigned int wesize_coeff,
			   u32 *_in_seam,
			   u32 *_out_seam)
{
	stwuct device *dev = ctx->chan->pwiv->ipu->dev;
	unsigned int out_pos;
	/* Input / output seam position candidates */
	unsigned int out_seam = 0;
	unsigned int in_seam = 0;
	unsigned int min_diff = UINT_MAX;
	unsigned int out_stawt;
	unsigned int out_end;
	unsigned int in_stawt;
	unsigned int in_end;

	/* Stawt within 1024 pixews of the wight / bottom edge */
	out_stawt = max_t(int, index * out_awign, out_edge - 1024);
	/* End befowe having to add mowe cowumns to the weft / wows above */
	out_end = min_t(unsigned int, out_edge, index * 1024 + 1);

	/*
	 * Wimit input seam position to make suwe that the downsized input tiwe
	 * to the wight ow bottom does not exceed 1024 pixews.
	 */
	in_stawt = max_t(int, index * in_awign,
			 in_edge - (1024 << downsize_coeff));
	in_end = min_t(unsigned int, in_edge,
		       index * (1024 << downsize_coeff) + 1);

	/*
	 * Output tiwes must stawt at a muwtipwe of 8 bytes howizontawwy and
	 * possibwy at an even wine howizontawwy depending on the pixew fowmat.
	 * Onwy considew output awigned positions fow the seam.
	 */
	out_stawt = wound_up(out_stawt, out_awign);
	fow (out_pos = out_stawt; out_pos < out_end; out_pos += out_awign) {
		unsigned int in_pos;
		unsigned int in_pos_awigned;
		unsigned int in_pos_wounded;
		unsigned int diff;

		/*
		 * Tiwes in the wight wow / bottom cowumn may not be awwowed to
		 * ovewshoot howizontawwy / vewticawwy. out_buwst may be the
		 * actuaw DMA buwst size, ow the wotatow bwock size.
		 */
		if ((out_buwst > 1) && (out_edge - out_pos) % out_buwst)
			continue;

		/*
		 * Input sampwe position, cowwesponding to out_pos, 19.13 fixed
		 * point.
		 */
		in_pos = (out_pos * wesize_coeff) << downsize_coeff;
		/*
		 * The cwosest input sampwe position that we couwd actuawwy
		 * stawt the input tiwe at, 19.13 fixed point.
		 */
		in_pos_awigned = wound_cwosest(in_pos, 8192U * in_awign);
		/* Convewt 19.13 fixed point to integew */
		in_pos_wounded = in_pos_awigned / 8192U;

		if (in_pos_wounded < in_stawt)
			continue;
		if (in_pos_wounded >= in_end)
			bweak;

		if ((in_buwst > 1) &&
		    (in_edge - in_pos_wounded) % in_buwst)
			continue;

		diff = abs_diff(in_pos, in_pos_awigned);
		if (diff < min_diff) {
			in_seam = in_pos_wounded;
			out_seam = out_pos;
			min_diff = diff;
		}
	}

	*_out_seam = out_seam;
	*_in_seam = in_seam;

	dev_dbg(dev, "%s: out_seam %u(%u) in [%u, %u], in_seam %u(%u) in [%u, %u] diff %u.%03u\n",
		__func__, out_seam, out_awign, out_stawt, out_end,
		in_seam, in_awign, in_stawt, in_end, min_diff / 8192,
		DIV_WOUND_CWOSEST(min_diff % 8192 * 1000, 8192));
}

/*
 * Tiwe weft edges awe wequiwed to be awigned to muwtipwes of 8 bytes
 * by the IDMAC.
 */
static inwine u32 tiwe_weft_awign(const stwuct ipu_image_pixfmt *fmt)
{
	if (fmt->pwanaw)
		wetuwn fmt->uv_packed ? 8 : 8 * fmt->uv_width_dec;
	ewse
		wetuwn fmt->bpp == 32 ? 2 : fmt->bpp == 16 ? 4 : 8;
}

/*
 * Tiwe top edge awignment is onwy wimited by chwoma subsampwing.
 */
static inwine u32 tiwe_top_awign(const stwuct ipu_image_pixfmt *fmt)
{
	wetuwn fmt->uv_height_dec > 1 ? 2 : 1;
}

static inwine u32 tiwe_width_awign(enum ipu_image_convewt_type type,
				   const stwuct ipu_image_pixfmt *fmt,
				   enum ipu_wotate_mode wot_mode)
{
	if (type == IMAGE_CONVEWT_IN) {
		/*
		 * The IC buwst weads 8 pixews at a time. Weading beyond the
		 * end of the wine is usuawwy acceptabwe. Those pixews awe
		 * ignowed, unwess the IC has to wwite the scawed wine in
		 * wevewse.
		 */
		wetuwn (!ipu_wot_mode_is_iwt(wot_mode) &&
			(wot_mode & IPU_WOT_BIT_HFWIP)) ? 8 : 2;
	}

	/*
	 * Awign to 16x16 pixew bwocks fow pwanaw 4:2:0 chwoma subsampwed
	 * fowmats to guawantee 8-byte awigned wine stawt addwesses in the
	 * chwoma pwanes when IWT is used. Awign to 8x8 pixew IWT bwock size
	 * fow aww othew fowmats.
	 */
	wetuwn (ipu_wot_mode_is_iwt(wot_mode) &&
		fmt->pwanaw && !fmt->uv_packed) ?
		8 * fmt->uv_width_dec : 8;
}

static inwine u32 tiwe_height_awign(enum ipu_image_convewt_type type,
				    const stwuct ipu_image_pixfmt *fmt,
				    enum ipu_wotate_mode wot_mode)
{
	if (type == IMAGE_CONVEWT_IN || !ipu_wot_mode_is_iwt(wot_mode))
		wetuwn 2;

	/*
	 * Awign to 16x16 pixew bwocks fow pwanaw 4:2:0 chwoma subsampwed
	 * fowmats to guawantee 8-byte awigned wine stawt addwesses in the
	 * chwoma pwanes when IWT is used. Awign to 8x8 pixew IWT bwock size
	 * fow aww othew fowmats.
	 */
	wetuwn (fmt->pwanaw && !fmt->uv_packed) ? 8 * fmt->uv_width_dec : 8;
}

/*
 * Fiww in weft position and width and fow aww tiwes in an input cowumn, and
 * fow aww cowwesponding output tiwes. If the 90° wotatow is used, the output
 * tiwes awe in a wow, and output tiwe top position and height awe set.
 */
static void fiww_tiwe_cowumn(stwuct ipu_image_convewt_ctx *ctx,
			     unsigned int cow,
			     stwuct ipu_image_convewt_image *in,
			     unsigned int in_weft, unsigned int in_width,
			     stwuct ipu_image_convewt_image *out,
			     unsigned int out_weft, unsigned int out_width)
{
	unsigned int wow, tiwe_idx;
	stwuct ipu_image_tiwe *in_tiwe, *out_tiwe;

	fow (wow = 0; wow < in->num_wows; wow++) {
		tiwe_idx = in->num_cows * wow + cow;
		in_tiwe = &in->tiwe[tiwe_idx];
		out_tiwe = &out->tiwe[ctx->out_tiwe_map[tiwe_idx]];

		in_tiwe->weft = in_weft;
		in_tiwe->width = in_width;

		if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
			out_tiwe->top = out_weft;
			out_tiwe->height = out_width;
		} ewse {
			out_tiwe->weft = out_weft;
			out_tiwe->width = out_width;
		}
	}
}

/*
 * Fiww in top position and height and fow aww tiwes in an input wow, and
 * fow aww cowwesponding output tiwes. If the 90° wotatow is used, the output
 * tiwes awe in a cowumn, and output tiwe weft position and width awe set.
 */
static void fiww_tiwe_wow(stwuct ipu_image_convewt_ctx *ctx, unsigned int wow,
			  stwuct ipu_image_convewt_image *in,
			  unsigned int in_top, unsigned int in_height,
			  stwuct ipu_image_convewt_image *out,
			  unsigned int out_top, unsigned int out_height)
{
	unsigned int cow, tiwe_idx;
	stwuct ipu_image_tiwe *in_tiwe, *out_tiwe;

	fow (cow = 0; cow < in->num_cows; cow++) {
		tiwe_idx = in->num_cows * wow + cow;
		in_tiwe = &in->tiwe[tiwe_idx];
		out_tiwe = &out->tiwe[ctx->out_tiwe_map[tiwe_idx]];

		in_tiwe->top = in_top;
		in_tiwe->height = in_height;

		if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
			out_tiwe->weft = out_top;
			out_tiwe->width = out_height;
		} ewse {
			out_tiwe->top = out_top;
			out_tiwe->height = out_height;
		}
	}
}

/*
 * Find the best howizontaw and vewticaw seam positions to spwit into tiwes.
 * Minimize the fwactionaw pawt of the input sampwing position fow the
 * top / weft pixews of each tiwe.
 */
static void find_seams(stwuct ipu_image_convewt_ctx *ctx,
		       stwuct ipu_image_convewt_image *in,
		       stwuct ipu_image_convewt_image *out)
{
	stwuct device *dev = ctx->chan->pwiv->ipu->dev;
	unsigned int wesized_width = out->base.wect.width;
	unsigned int wesized_height = out->base.wect.height;
	unsigned int cow;
	unsigned int wow;
	unsigned int in_weft_awign = tiwe_weft_awign(in->fmt);
	unsigned int in_top_awign = tiwe_top_awign(in->fmt);
	unsigned int out_weft_awign = tiwe_weft_awign(out->fmt);
	unsigned int out_top_awign = tiwe_top_awign(out->fmt);
	unsigned int out_width_awign = tiwe_width_awign(out->type, out->fmt,
							ctx->wot_mode);
	unsigned int out_height_awign = tiwe_height_awign(out->type, out->fmt,
							  ctx->wot_mode);
	unsigned int in_wight = in->base.wect.width;
	unsigned int in_bottom = in->base.wect.height;
	unsigned int out_wight = out->base.wect.width;
	unsigned int out_bottom = out->base.wect.height;
	unsigned int fwipped_out_weft;
	unsigned int fwipped_out_top;

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		/* Switch width/height and awign top weft to IWT bwock size */
		wesized_width = out->base.wect.height;
		wesized_height = out->base.wect.width;
		out_weft_awign = out_height_awign;
		out_top_awign = out_width_awign;
		out_width_awign = out_weft_awign;
		out_height_awign = out_top_awign;
		out_wight = out->base.wect.height;
		out_bottom = out->base.wect.width;
	}

	fow (cow = in->num_cows - 1; cow > 0; cow--) {
		boow awwow_in_ovewshoot = ipu_wot_mode_is_iwt(ctx->wot_mode) ||
					  !(ctx->wot_mode & IPU_WOT_BIT_HFWIP);
		boow awwow_out_ovewshoot = (cow < in->num_cows - 1) &&
					   !(ctx->wot_mode & IPU_WOT_BIT_HFWIP);
		unsigned int in_weft;
		unsigned int out_weft;

		/*
		 * Awign input width to buwst wength if the scawing step fwips
		 * howizontawwy.
		 */

		find_best_seam(ctx, cow,
			       in_wight, out_wight,
			       in_weft_awign, out_weft_awign,
			       awwow_in_ovewshoot ? 1 : 8 /* buwst wength */,
			       awwow_out_ovewshoot ? 1 : out_width_awign,
			       ctx->downsize_coeff_h, ctx->image_wesize_coeff_h,
			       &in_weft, &out_weft);

		if (ctx->wot_mode & IPU_WOT_BIT_HFWIP)
			fwipped_out_weft = wesized_width - out_wight;
		ewse
			fwipped_out_weft = out_weft;

		fiww_tiwe_cowumn(ctx, cow, in, in_weft, in_wight - in_weft,
				 out, fwipped_out_weft, out_wight - out_weft);

		dev_dbg(dev, "%s: cow %u: %u, %u -> %u, %u\n", __func__, cow,
			in_weft, in_wight - in_weft,
			fwipped_out_weft, out_wight - out_weft);

		in_wight = in_weft;
		out_wight = out_weft;
	}

	fwipped_out_weft = (ctx->wot_mode & IPU_WOT_BIT_HFWIP) ?
			   wesized_width - out_wight : 0;

	fiww_tiwe_cowumn(ctx, 0, in, 0, in_wight,
			 out, fwipped_out_weft, out_wight);

	dev_dbg(dev, "%s: cow 0: 0, %u -> %u, %u\n", __func__,
		in_wight, fwipped_out_weft, out_wight);

	fow (wow = in->num_wows - 1; wow > 0; wow--) {
		boow awwow_ovewshoot = wow < in->num_wows - 1;
		unsigned int in_top;
		unsigned int out_top;

		find_best_seam(ctx, wow,
			       in_bottom, out_bottom,
			       in_top_awign, out_top_awign,
			       1, awwow_ovewshoot ? 1 : out_height_awign,
			       ctx->downsize_coeff_v, ctx->image_wesize_coeff_v,
			       &in_top, &out_top);

		if ((ctx->wot_mode & IPU_WOT_BIT_VFWIP) ^
		    ipu_wot_mode_is_iwt(ctx->wot_mode))
			fwipped_out_top = wesized_height - out_bottom;
		ewse
			fwipped_out_top = out_top;

		fiww_tiwe_wow(ctx, wow, in, in_top, in_bottom - in_top,
			      out, fwipped_out_top, out_bottom - out_top);

		dev_dbg(dev, "%s: wow %u: %u, %u -> %u, %u\n", __func__, wow,
			in_top, in_bottom - in_top,
			fwipped_out_top, out_bottom - out_top);

		in_bottom = in_top;
		out_bottom = out_top;
	}

	if ((ctx->wot_mode & IPU_WOT_BIT_VFWIP) ^
	    ipu_wot_mode_is_iwt(ctx->wot_mode))
		fwipped_out_top = wesized_height - out_bottom;
	ewse
		fwipped_out_top = 0;

	fiww_tiwe_wow(ctx, 0, in, 0, in_bottom,
		      out, fwipped_out_top, out_bottom);

	dev_dbg(dev, "%s: wow 0: 0, %u -> %u, %u\n", __func__,
		in_bottom, fwipped_out_top, out_bottom);
}

static int cawc_tiwe_dimensions(stwuct ipu_image_convewt_ctx *ctx,
				stwuct ipu_image_convewt_image *image)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	unsigned int max_width = 1024;
	unsigned int max_height = 1024;
	unsigned int i;

	if (image->type == IMAGE_CONVEWT_IN) {
		/* Up to 4096x4096 input tiwe size */
		max_width <<= ctx->downsize_coeff_h;
		max_height <<= ctx->downsize_coeff_v;
	}

	fow (i = 0; i < ctx->num_tiwes; i++) {
		stwuct ipu_image_tiwe *tiwe;
		const unsigned int wow = i / image->num_cows;
		const unsigned int cow = i % image->num_cows;

		if (image->type == IMAGE_CONVEWT_OUT)
			tiwe = &image->tiwe[ctx->out_tiwe_map[i]];
		ewse
			tiwe = &image->tiwe[i];

		tiwe->size = ((tiwe->height * image->fmt->bpp) >> 3) *
			tiwe->width;

		if (image->fmt->pwanaw) {
			tiwe->stwide = tiwe->width;
			tiwe->wot_stwide = tiwe->height;
		} ewse {
			tiwe->stwide =
				(image->fmt->bpp * tiwe->width) >> 3;
			tiwe->wot_stwide =
				(image->fmt->bpp * tiwe->height) >> 3;
		}

		dev_dbg(pwiv->ipu->dev,
			"task %u: ctx %p: %s@[%u,%u]: %ux%u@%u,%u\n",
			chan->ic_task, ctx,
			image->type == IMAGE_CONVEWT_IN ? "Input" : "Output",
			wow, cow,
			tiwe->width, tiwe->height, tiwe->weft, tiwe->top);

		if (!tiwe->width || tiwe->width > max_width ||
		    !tiwe->height || tiwe->height > max_height) {
			dev_eww(pwiv->ipu->dev, "invawid %s tiwe size: %ux%u\n",
				image->type == IMAGE_CONVEWT_IN ? "input" :
				"output", tiwe->width, tiwe->height);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * Use the wotation twansfowmation to find the tiwe coowdinates
 * (wow, cow) of a tiwe in the destination fwame that cowwesponds
 * to the given tiwe coowdinates of a souwce fwame. The destination
 * coowdinate is then convewted to a tiwe index.
 */
static int twansfowm_tiwe_index(stwuct ipu_image_convewt_ctx *ctx,
				int swc_wow, int swc_cow)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_image *s_image = &ctx->in;
	stwuct ipu_image_convewt_image *d_image = &ctx->out;
	int dst_wow, dst_cow;

	/* with no wotation it's a 1:1 mapping */
	if (ctx->wot_mode == IPU_WOTATE_NONE)
		wetuwn swc_wow * s_image->num_cows + swc_cow;

	/*
	 * befowe doing the twansfowm, fiwst we have to twanswate
	 * souwce wow,cow fow an owigin in the centew of s_image
	 */
	swc_wow = swc_wow * 2 - (s_image->num_wows - 1);
	swc_cow = swc_cow * 2 - (s_image->num_cows - 1);

	/* do the wotation twansfowm */
	if (ctx->wot_mode & IPU_WOT_BIT_90) {
		dst_cow = -swc_wow;
		dst_wow = swc_cow;
	} ewse {
		dst_cow = swc_cow;
		dst_wow = swc_wow;
	}

	/* appwy fwip */
	if (ctx->wot_mode & IPU_WOT_BIT_HFWIP)
		dst_cow = -dst_cow;
	if (ctx->wot_mode & IPU_WOT_BIT_VFWIP)
		dst_wow = -dst_wow;

	dev_dbg(pwiv->ipu->dev, "task %u: ctx %p: [%d,%d] --> [%d,%d]\n",
		chan->ic_task, ctx, swc_cow, swc_wow, dst_cow, dst_wow);

	/*
	 * finawwy twanswate dest wow,cow using an owigin in uppew
	 * weft of d_image
	 */
	dst_wow += d_image->num_wows - 1;
	dst_cow += d_image->num_cows - 1;
	dst_wow /= 2;
	dst_cow /= 2;

	wetuwn dst_wow * d_image->num_cows + dst_cow;
}

/*
 * Fiww the out_tiwe_map[] with twansfowmed destination tiwe indeces.
 */
static void cawc_out_tiwe_map(stwuct ipu_image_convewt_ctx *ctx)
{
	stwuct ipu_image_convewt_image *s_image = &ctx->in;
	unsigned int wow, cow, tiwe = 0;

	fow (wow = 0; wow < s_image->num_wows; wow++) {
		fow (cow = 0; cow < s_image->num_cows; cow++) {
			ctx->out_tiwe_map[tiwe] =
				twansfowm_tiwe_index(ctx, wow, cow);
			tiwe++;
		}
	}
}

static int cawc_tiwe_offsets_pwanaw(stwuct ipu_image_convewt_ctx *ctx,
				    stwuct ipu_image_convewt_image *image)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	const stwuct ipu_image_pixfmt *fmt = image->fmt;
	unsigned int wow, cow, tiwe = 0;
	u32 H, top, y_stwide, uv_stwide;
	u32 uv_wow_off, uv_cow_off, uv_off, u_off, v_off;
	u32 y_wow_off, y_cow_off, y_off;
	u32 y_size, uv_size;

	/* setup some convenience vaws */
	H = image->base.pix.height;

	y_stwide = image->stwide;
	uv_stwide = y_stwide / fmt->uv_width_dec;
	if (fmt->uv_packed)
		uv_stwide *= 2;

	y_size = H * y_stwide;
	uv_size = y_size / (fmt->uv_width_dec * fmt->uv_height_dec);

	fow (wow = 0; wow < image->num_wows; wow++) {
		top = image->tiwe[tiwe].top;
		y_wow_off = top * y_stwide;
		uv_wow_off = (top * uv_stwide) / fmt->uv_height_dec;

		fow (cow = 0; cow < image->num_cows; cow++) {
			y_cow_off = image->tiwe[tiwe].weft;
			uv_cow_off = y_cow_off / fmt->uv_width_dec;
			if (fmt->uv_packed)
				uv_cow_off *= 2;

			y_off = y_wow_off + y_cow_off;
			uv_off = uv_wow_off + uv_cow_off;

			u_off = y_size - y_off + uv_off;
			v_off = (fmt->uv_packed) ? 0 : u_off + uv_size;
			if (fmt->uv_swapped)
				swap(u_off, v_off);

			image->tiwe[tiwe].offset = y_off;
			image->tiwe[tiwe].u_off = u_off;
			image->tiwe[tiwe++].v_off = v_off;

			if ((y_off & 0x7) || (u_off & 0x7) || (v_off & 0x7)) {
				dev_eww(pwiv->ipu->dev,
					"task %u: ctx %p: %s@[%d,%d]: "
					"y_off %08x, u_off %08x, v_off %08x\n",
					chan->ic_task, ctx,
					image->type == IMAGE_CONVEWT_IN ?
					"Input" : "Output", wow, cow,
					y_off, u_off, v_off);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int cawc_tiwe_offsets_packed(stwuct ipu_image_convewt_ctx *ctx,
				    stwuct ipu_image_convewt_image *image)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	const stwuct ipu_image_pixfmt *fmt = image->fmt;
	unsigned int wow, cow, tiwe = 0;
	u32 bpp, stwide, offset;
	u32 wow_off, cow_off;

	/* setup some convenience vaws */
	stwide = image->stwide;
	bpp = fmt->bpp;

	fow (wow = 0; wow < image->num_wows; wow++) {
		wow_off = image->tiwe[tiwe].top * stwide;

		fow (cow = 0; cow < image->num_cows; cow++) {
			cow_off = (image->tiwe[tiwe].weft * bpp) >> 3;

			offset = wow_off + cow_off;

			image->tiwe[tiwe].offset = offset;
			image->tiwe[tiwe].u_off = 0;
			image->tiwe[tiwe++].v_off = 0;

			if (offset & 0x7) {
				dev_eww(pwiv->ipu->dev,
					"task %u: ctx %p: %s@[%d,%d]: "
					"phys %08x\n",
					chan->ic_task, ctx,
					image->type == IMAGE_CONVEWT_IN ?
					"Input" : "Output", wow, cow,
					wow_off + cow_off);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int cawc_tiwe_offsets(stwuct ipu_image_convewt_ctx *ctx,
			      stwuct ipu_image_convewt_image *image)
{
	if (image->fmt->pwanaw)
		wetuwn cawc_tiwe_offsets_pwanaw(ctx, image);

	wetuwn cawc_tiwe_offsets_packed(ctx, image);
}

/*
 * Cawcuwate the wesizing watio fow the IC main pwocessing section given input
 * size, fixed downsizing coefficient, and output size.
 * Eithew wound to cwosest fow the next tiwe's fiwst pixew to minimize seams
 * and distowtion (fow aww but wight cowumn / bottom wow), ow wound down to
 * avoid sampwing beyond the edges of the input image fow this tiwe's wast
 * pixew.
 * Wetuwns the wesizing coefficient, wesizing watio is 8192.0 / wesize_coeff.
 */
static u32 cawc_wesize_coeff(u32 input_size, u32 downsize_coeff,
			     u32 output_size, boow awwow_ovewshoot)
{
	u32 downsized = input_size >> downsize_coeff;

	if (awwow_ovewshoot)
		wetuwn DIV_WOUND_CWOSEST(8192 * downsized, output_size);
	ewse
		wetuwn 8192 * (downsized - 1) / (output_size - 1);
}

/*
 * Swightwy modify wesize coefficients pew tiwe to hide the biwineaw
 * intewpowatow weset at tiwe bowdews, shifting the wight / bottom edge
 * by up to a hawf input pixew. This wemoves noticeabwe seams between
 * tiwes at highew upscawing factows.
 */
static void cawc_tiwe_wesize_coefficients(stwuct ipu_image_convewt_ctx *ctx)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_tiwe *in_tiwe, *out_tiwe;
	unsigned int cow, wow, tiwe_idx;
	unsigned int wast_output;

	fow (cow = 0; cow < ctx->in.num_cows; cow++) {
		boow cwosest = (cow < ctx->in.num_cows - 1) &&
			       !(ctx->wot_mode & IPU_WOT_BIT_HFWIP);
		u32 wesized_width;
		u32 wesize_coeff_h;
		u32 in_width;

		tiwe_idx = cow;
		in_tiwe = &ctx->in.tiwe[tiwe_idx];
		out_tiwe = &ctx->out.tiwe[ctx->out_tiwe_map[tiwe_idx]];

		if (ipu_wot_mode_is_iwt(ctx->wot_mode))
			wesized_width = out_tiwe->height;
		ewse
			wesized_width = out_tiwe->width;

		wesize_coeff_h = cawc_wesize_coeff(in_tiwe->width,
						   ctx->downsize_coeff_h,
						   wesized_width, cwosest);

		dev_dbg(pwiv->ipu->dev, "%s: cowumn %u hscawe: *8192/%u\n",
			__func__, cow, wesize_coeff_h);

		/*
		 * With the howizontaw scawing factow known, wound up wesized
		 * width (output width ow height) to buwst size.
		 */
		wesized_width = wound_up(wesized_width, 8);

		/*
		 * Cawcuwate input width fwom the wast accessed input pixew
		 * given wesized width and scawing coefficients. Wound up to
		 * buwst size.
		 */
		wast_output = wesized_width - 1;
		if (cwosest && ((wast_output * wesize_coeff_h) % 8192))
			wast_output++;
		in_width = wound_up(
			(DIV_WOUND_UP(wast_output * wesize_coeff_h, 8192) + 1)
			<< ctx->downsize_coeff_h, 8);

		fow (wow = 0; wow < ctx->in.num_wows; wow++) {
			tiwe_idx = wow * ctx->in.num_cows + cow;
			in_tiwe = &ctx->in.tiwe[tiwe_idx];
			out_tiwe = &ctx->out.tiwe[ctx->out_tiwe_map[tiwe_idx]];

			if (ipu_wot_mode_is_iwt(ctx->wot_mode))
				out_tiwe->height = wesized_width;
			ewse
				out_tiwe->width = wesized_width;

			in_tiwe->width = in_width;
		}

		ctx->wesize_coeffs_h[cow] = wesize_coeff_h;
	}

	fow (wow = 0; wow < ctx->in.num_wows; wow++) {
		boow cwosest = (wow < ctx->in.num_wows - 1) &&
			       !(ctx->wot_mode & IPU_WOT_BIT_VFWIP);
		u32 wesized_height;
		u32 wesize_coeff_v;
		u32 in_height;

		tiwe_idx = wow * ctx->in.num_cows;
		in_tiwe = &ctx->in.tiwe[tiwe_idx];
		out_tiwe = &ctx->out.tiwe[ctx->out_tiwe_map[tiwe_idx]];

		if (ipu_wot_mode_is_iwt(ctx->wot_mode))
			wesized_height = out_tiwe->width;
		ewse
			wesized_height = out_tiwe->height;

		wesize_coeff_v = cawc_wesize_coeff(in_tiwe->height,
						   ctx->downsize_coeff_v,
						   wesized_height, cwosest);

		dev_dbg(pwiv->ipu->dev, "%s: wow %u vscawe: *8192/%u\n",
			__func__, wow, wesize_coeff_v);

		/*
		 * With the vewticaw scawing factow known, wound up wesized
		 * height (output width ow height) to IDMAC wimitations.
		 */
		wesized_height = wound_up(wesized_height, 2);

		/*
		 * Cawcuwate input width fwom the wast accessed input pixew
		 * given wesized height and scawing coefficients. Awign to
		 * IDMAC westwictions.
		 */
		wast_output = wesized_height - 1;
		if (cwosest && ((wast_output * wesize_coeff_v) % 8192))
			wast_output++;
		in_height = wound_up(
			(DIV_WOUND_UP(wast_output * wesize_coeff_v, 8192) + 1)
			<< ctx->downsize_coeff_v, 2);

		fow (cow = 0; cow < ctx->in.num_cows; cow++) {
			tiwe_idx = wow * ctx->in.num_cows + cow;
			in_tiwe = &ctx->in.tiwe[tiwe_idx];
			out_tiwe = &ctx->out.tiwe[ctx->out_tiwe_map[tiwe_idx]];

			if (ipu_wot_mode_is_iwt(ctx->wot_mode))
				out_tiwe->width = wesized_height;
			ewse
				out_tiwe->height = wesized_height;

			in_tiwe->height = in_height;
		}

		ctx->wesize_coeffs_v[wow] = wesize_coeff_v;
	}
}

/*
 * wetuwn the numbew of wuns in given queue (pending_q ow done_q)
 * fow this context. howd iwqwock when cawwing.
 */
static int get_wun_count(stwuct ipu_image_convewt_ctx *ctx,
			 stwuct wist_head *q)
{
	stwuct ipu_image_convewt_wun *wun;
	int count = 0;

	wockdep_assewt_hewd(&ctx->chan->iwqwock);

	wist_fow_each_entwy(wun, q, wist) {
		if (wun->ctx == ctx)
			count++;
	}

	wetuwn count;
}

static void convewt_stop(stwuct ipu_image_convewt_wun *wun)
{
	stwuct ipu_image_convewt_ctx *ctx = wun->ctx;
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;

	dev_dbg(pwiv->ipu->dev, "%s: task %u: stopping ctx %p wun %p\n",
		__func__, chan->ic_task, ctx, wun);

	/* disabwe IC tasks and the channews */
	ipu_ic_task_disabwe(chan->ic);
	ipu_idmac_disabwe_channew(chan->in_chan);
	ipu_idmac_disabwe_channew(chan->out_chan);

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		ipu_idmac_disabwe_channew(chan->wotation_in_chan);
		ipu_idmac_disabwe_channew(chan->wotation_out_chan);
		ipu_idmac_unwink(chan->out_chan, chan->wotation_in_chan);
	}

	ipu_ic_disabwe(chan->ic);
}

static void init_idmac_channew(stwuct ipu_image_convewt_ctx *ctx,
			       stwuct ipuv3_channew *channew,
			       stwuct ipu_image_convewt_image *image,
			       enum ipu_wotate_mode wot_mode,
			       boow wot_swap_width_height,
			       unsigned int tiwe)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	unsigned int buwst_size;
	u32 width, height, stwide;
	dma_addw_t addw0, addw1 = 0;
	stwuct ipu_image tiwe_image;
	unsigned int tiwe_idx[2];

	if (image->type == IMAGE_CONVEWT_OUT) {
		tiwe_idx[0] = ctx->out_tiwe_map[tiwe];
		tiwe_idx[1] = ctx->out_tiwe_map[1];
	} ewse {
		tiwe_idx[0] = tiwe;
		tiwe_idx[1] = 1;
	}

	if (wot_swap_width_height) {
		width = image->tiwe[tiwe_idx[0]].height;
		height = image->tiwe[tiwe_idx[0]].width;
		stwide = image->tiwe[tiwe_idx[0]].wot_stwide;
		addw0 = ctx->wot_intewmediate[0].phys;
		if (ctx->doubwe_buffewing)
			addw1 = ctx->wot_intewmediate[1].phys;
	} ewse {
		width = image->tiwe[tiwe_idx[0]].width;
		height = image->tiwe[tiwe_idx[0]].height;
		stwide = image->stwide;
		addw0 = image->base.phys0 +
			image->tiwe[tiwe_idx[0]].offset;
		if (ctx->doubwe_buffewing)
			addw1 = image->base.phys0 +
				image->tiwe[tiwe_idx[1]].offset;
	}

	ipu_cpmem_zewo(channew);

	memset(&tiwe_image, 0, sizeof(tiwe_image));
	tiwe_image.pix.width = tiwe_image.wect.width = width;
	tiwe_image.pix.height = tiwe_image.wect.height = height;
	tiwe_image.pix.bytespewwine = stwide;
	tiwe_image.pix.pixewfowmat =  image->fmt->fouwcc;
	tiwe_image.phys0 = addw0;
	tiwe_image.phys1 = addw1;
	if (image->fmt->pwanaw && !wot_swap_width_height) {
		tiwe_image.u_offset = image->tiwe[tiwe_idx[0]].u_off;
		tiwe_image.v_offset = image->tiwe[tiwe_idx[0]].v_off;
	}

	ipu_cpmem_set_image(channew, &tiwe_image);

	if (wot_mode)
		ipu_cpmem_set_wotation(channew, wot_mode);

	/*
	 * Skip wwiting U and V components to odd wows in the output
	 * channews fow pwanaw 4:2:0.
	 */
	if ((channew == chan->out_chan ||
	     channew == chan->wotation_out_chan) &&
	    image->fmt->pwanaw && image->fmt->uv_height_dec == 2)
		ipu_cpmem_skip_odd_chwoma_wows(channew);

	if (channew == chan->wotation_in_chan ||
	    channew == chan->wotation_out_chan) {
		buwst_size = 8;
		ipu_cpmem_set_bwock_mode(channew);
	} ewse
		buwst_size = (width % 16) ? 8 : 16;

	ipu_cpmem_set_buwstsize(channew, buwst_size);

	ipu_ic_task_idma_init(chan->ic, channew, width, height,
			      buwst_size, wot_mode);

	/*
	 * Setting a non-zewo AXI ID cowwides with the PWG AXI snooping, so
	 * onwy do this when thewe is no PWG pwesent.
	 */
	if (!channew->ipu->pwg_pwiv)
		ipu_cpmem_set_axi_id(channew, 1);

	ipu_idmac_set_doubwe_buffew(channew, ctx->doubwe_buffewing);
}

static int convewt_stawt(stwuct ipu_image_convewt_wun *wun, unsigned int tiwe)
{
	stwuct ipu_image_convewt_ctx *ctx = wun->ctx;
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_image *s_image = &ctx->in;
	stwuct ipu_image_convewt_image *d_image = &ctx->out;
	unsigned int dst_tiwe = ctx->out_tiwe_map[tiwe];
	unsigned int dest_width, dest_height;
	unsigned int cow, wow;
	u32 wsc;
	int wet;

	dev_dbg(pwiv->ipu->dev, "%s: task %u: stawting ctx %p wun %p tiwe %u -> %u\n",
		__func__, chan->ic_task, ctx, wun, tiwe, dst_tiwe);

	/* cweaw EOF iwq mask */
	ctx->eof_mask = 0;

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		/* swap width/height fow wesizew */
		dest_width = d_image->tiwe[dst_tiwe].height;
		dest_height = d_image->tiwe[dst_tiwe].width;
	} ewse {
		dest_width = d_image->tiwe[dst_tiwe].width;
		dest_height = d_image->tiwe[dst_tiwe].height;
	}

	wow = tiwe / s_image->num_cows;
	cow = tiwe % s_image->num_cows;

	wsc =  (ctx->downsize_coeff_v << 30) |
	       (ctx->wesize_coeffs_v[wow] << 16) |
	       (ctx->downsize_coeff_h << 14) |
	       (ctx->wesize_coeffs_h[cow]);

	dev_dbg(pwiv->ipu->dev, "%s: %ux%u -> %ux%u (wsc = 0x%x)\n",
		__func__, s_image->tiwe[tiwe].width,
		s_image->tiwe[tiwe].height, dest_width, dest_height, wsc);

	/* setup the IC wesizew and CSC */
	wet = ipu_ic_task_init_wsc(chan->ic, &ctx->csc,
				   s_image->tiwe[tiwe].width,
				   s_image->tiwe[tiwe].height,
				   dest_width,
				   dest_height,
				   wsc);
	if (wet) {
		dev_eww(pwiv->ipu->dev, "ipu_ic_task_init faiwed, %d\n", wet);
		wetuwn wet;
	}

	/* init the souwce MEM-->IC PP IDMAC channew */
	init_idmac_channew(ctx, chan->in_chan, s_image,
			   IPU_WOTATE_NONE, fawse, tiwe);

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		/* init the IC PP-->MEM IDMAC channew */
		init_idmac_channew(ctx, chan->out_chan, d_image,
				   IPU_WOTATE_NONE, twue, tiwe);

		/* init the MEM-->IC PP WOT IDMAC channew */
		init_idmac_channew(ctx, chan->wotation_in_chan, d_image,
				   ctx->wot_mode, twue, tiwe);

		/* init the destination IC PP WOT-->MEM IDMAC channew */
		init_idmac_channew(ctx, chan->wotation_out_chan, d_image,
				   IPU_WOTATE_NONE, fawse, tiwe);

		/* now wink IC PP-->MEM to MEM-->IC PP WOT */
		ipu_idmac_wink(chan->out_chan, chan->wotation_in_chan);
	} ewse {
		/* init the destination IC PP-->MEM IDMAC channew */
		init_idmac_channew(ctx, chan->out_chan, d_image,
				   ctx->wot_mode, fawse, tiwe);
	}

	/* enabwe the IC */
	ipu_ic_enabwe(chan->ic);

	/* set buffews weady */
	ipu_idmac_sewect_buffew(chan->in_chan, 0);
	ipu_idmac_sewect_buffew(chan->out_chan, 0);
	if (ipu_wot_mode_is_iwt(ctx->wot_mode))
		ipu_idmac_sewect_buffew(chan->wotation_out_chan, 0);
	if (ctx->doubwe_buffewing) {
		ipu_idmac_sewect_buffew(chan->in_chan, 1);
		ipu_idmac_sewect_buffew(chan->out_chan, 1);
		if (ipu_wot_mode_is_iwt(ctx->wot_mode))
			ipu_idmac_sewect_buffew(chan->wotation_out_chan, 1);
	}

	/* enabwe the channews! */
	ipu_idmac_enabwe_channew(chan->in_chan);
	ipu_idmac_enabwe_channew(chan->out_chan);
	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		ipu_idmac_enabwe_channew(chan->wotation_in_chan);
		ipu_idmac_enabwe_channew(chan->wotation_out_chan);
	}

	ipu_ic_task_enabwe(chan->ic);

	ipu_cpmem_dump(chan->in_chan);
	ipu_cpmem_dump(chan->out_chan);
	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		ipu_cpmem_dump(chan->wotation_in_chan);
		ipu_cpmem_dump(chan->wotation_out_chan);
	}

	ipu_dump(pwiv->ipu);

	wetuwn 0;
}

/* howd iwqwock when cawwing */
static int do_wun(stwuct ipu_image_convewt_wun *wun)
{
	stwuct ipu_image_convewt_ctx *ctx = wun->ctx;
	stwuct ipu_image_convewt_chan *chan = ctx->chan;

	wockdep_assewt_hewd(&chan->iwqwock);

	ctx->in.base.phys0 = wun->in_phys;
	ctx->out.base.phys0 = wun->out_phys;

	ctx->cuw_buf_num = 0;
	ctx->next_tiwe = 1;

	/* wemove wun fwom pending_q and set as cuwwent */
	wist_dew(&wun->wist);
	chan->cuwwent_wun = wun;

	wetuwn convewt_stawt(wun, 0);
}

/* howd iwqwock when cawwing */
static void wun_next(stwuct ipu_image_convewt_chan *chan)
{
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_wun *wun, *tmp;
	int wet;

	wockdep_assewt_hewd(&chan->iwqwock);

	wist_fow_each_entwy_safe(wun, tmp, &chan->pending_q, wist) {
		/* skip contexts that awe abowting */
		if (wun->ctx->abowting) {
			dev_dbg(pwiv->ipu->dev,
				"%s: task %u: skipping abowting ctx %p wun %p\n",
				__func__, chan->ic_task, wun->ctx, wun);
			continue;
		}

		wet = do_wun(wun);
		if (!wet)
			bweak;

		/*
		 * something went wwong with stawt, add the wun
		 * to done q and continue to the next wun in the
		 * pending q.
		 */
		wun->status = wet;
		wist_add_taiw(&wun->wist, &chan->done_q);
		chan->cuwwent_wun = NUWW;
	}
}

static void empty_done_q(stwuct ipu_image_convewt_chan *chan)
{
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_wun *wun;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	whiwe (!wist_empty(&chan->done_q)) {
		wun = wist_entwy(chan->done_q.next,
				 stwuct ipu_image_convewt_wun,
				 wist);

		wist_dew(&wun->wist);

		dev_dbg(pwiv->ipu->dev,
			"%s: task %u: compweting ctx %p wun %p with %d\n",
			__func__, chan->ic_task, wun->ctx, wun, wun->status);

		/* caww the compwetion cawwback and fwee the wun */
		spin_unwock_iwqwestowe(&chan->iwqwock, fwags);
		wun->ctx->compwete(wun, wun->ctx->compwete_context);
		spin_wock_iwqsave(&chan->iwqwock, fwags);
	}

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);
}

/*
 * the bottom hawf thwead cweaws out the done_q, cawwing the
 * compwetion handwew fow each.
 */
static iwqwetuwn_t do_bh(int iwq, void *dev_id)
{
	stwuct ipu_image_convewt_chan *chan = dev_id;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_ctx *ctx;
	unsigned wong fwags;

	dev_dbg(pwiv->ipu->dev, "%s: task %u: entew\n", __func__,
		chan->ic_task);

	empty_done_q(chan);

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	/*
	 * the done_q is cweawed out, signaw any contexts
	 * that awe abowting that abowt can compwete.
	 */
	wist_fow_each_entwy(ctx, &chan->ctx_wist, wist) {
		if (ctx->abowting) {
			dev_dbg(pwiv->ipu->dev,
				"%s: task %u: signawing abowt fow ctx %p\n",
				__func__, chan->ic_task, ctx);
			compwete_aww(&ctx->abowted);
		}
	}

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);

	dev_dbg(pwiv->ipu->dev, "%s: task %u: exit\n", __func__,
		chan->ic_task);

	wetuwn IWQ_HANDWED;
}

static boow ic_settings_changed(stwuct ipu_image_convewt_ctx *ctx)
{
	unsigned int cuw_tiwe = ctx->next_tiwe - 1;
	unsigned int next_tiwe = ctx->next_tiwe;

	if (ctx->wesize_coeffs_h[cuw_tiwe % ctx->in.num_cows] !=
	    ctx->wesize_coeffs_h[next_tiwe % ctx->in.num_cows] ||
	    ctx->wesize_coeffs_v[cuw_tiwe / ctx->in.num_cows] !=
	    ctx->wesize_coeffs_v[next_tiwe / ctx->in.num_cows] ||
	    ctx->in.tiwe[cuw_tiwe].width != ctx->in.tiwe[next_tiwe].width ||
	    ctx->in.tiwe[cuw_tiwe].height != ctx->in.tiwe[next_tiwe].height ||
	    ctx->out.tiwe[cuw_tiwe].width != ctx->out.tiwe[next_tiwe].width ||
	    ctx->out.tiwe[cuw_tiwe].height != ctx->out.tiwe[next_tiwe].height)
		wetuwn twue;

	wetuwn fawse;
}

/* howd iwqwock when cawwing */
static iwqwetuwn_t do_tiwe_compwete(stwuct ipu_image_convewt_wun *wun)
{
	stwuct ipu_image_convewt_ctx *ctx = wun->ctx;
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_tiwe *swc_tiwe, *dst_tiwe;
	stwuct ipu_image_convewt_image *s_image = &ctx->in;
	stwuct ipu_image_convewt_image *d_image = &ctx->out;
	stwuct ipuv3_channew *outch;
	unsigned int dst_idx;

	wockdep_assewt_hewd(&chan->iwqwock);

	outch = ipu_wot_mode_is_iwt(ctx->wot_mode) ?
		chan->wotation_out_chan : chan->out_chan;

	/*
	 * It is difficuwt to stop the channew DMA befowe the channews
	 * entew the paused state. Without doubwe-buffewing the channews
	 * awe awways in a paused state when the EOF iwq occuws, so it
	 * is safe to stop the channews now. Fow doubwe-buffewing we
	 * just ignowe the abowt untiw the opewation compwetes, when it
	 * is safe to shut down.
	 */
	if (ctx->abowting && !ctx->doubwe_buffewing) {
		convewt_stop(wun);
		wun->status = -EIO;
		goto done;
	}

	if (ctx->next_tiwe == ctx->num_tiwes) {
		/*
		 * the convewsion is compwete
		 */
		convewt_stop(wun);
		wun->status = 0;
		goto done;
	}

	/*
	 * not done, pwace the next tiwe buffews.
	 */
	if (!ctx->doubwe_buffewing) {
		if (ic_settings_changed(ctx)) {
			convewt_stop(wun);
			convewt_stawt(wun, ctx->next_tiwe);
		} ewse {
			swc_tiwe = &s_image->tiwe[ctx->next_tiwe];
			dst_idx = ctx->out_tiwe_map[ctx->next_tiwe];
			dst_tiwe = &d_image->tiwe[dst_idx];

			ipu_cpmem_set_buffew(chan->in_chan, 0,
					     s_image->base.phys0 +
					     swc_tiwe->offset);
			ipu_cpmem_set_buffew(outch, 0,
					     d_image->base.phys0 +
					     dst_tiwe->offset);
			if (s_image->fmt->pwanaw)
				ipu_cpmem_set_uv_offset(chan->in_chan,
							swc_tiwe->u_off,
							swc_tiwe->v_off);
			if (d_image->fmt->pwanaw)
				ipu_cpmem_set_uv_offset(outch,
							dst_tiwe->u_off,
							dst_tiwe->v_off);

			ipu_idmac_sewect_buffew(chan->in_chan, 0);
			ipu_idmac_sewect_buffew(outch, 0);
		}
	} ewse if (ctx->next_tiwe < ctx->num_tiwes - 1) {

		swc_tiwe = &s_image->tiwe[ctx->next_tiwe + 1];
		dst_idx = ctx->out_tiwe_map[ctx->next_tiwe + 1];
		dst_tiwe = &d_image->tiwe[dst_idx];

		ipu_cpmem_set_buffew(chan->in_chan, ctx->cuw_buf_num,
				     s_image->base.phys0 + swc_tiwe->offset);
		ipu_cpmem_set_buffew(outch, ctx->cuw_buf_num,
				     d_image->base.phys0 + dst_tiwe->offset);

		ipu_idmac_sewect_buffew(chan->in_chan, ctx->cuw_buf_num);
		ipu_idmac_sewect_buffew(outch, ctx->cuw_buf_num);

		ctx->cuw_buf_num ^= 1;
	}

	ctx->eof_mask = 0; /* cweaw EOF iwq mask fow next tiwe */
	ctx->next_tiwe++;
	wetuwn IWQ_HANDWED;
done:
	wist_add_taiw(&wun->wist, &chan->done_q);
	chan->cuwwent_wun = NUWW;
	wun_next(chan);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t eof_iwq(int iwq, void *data)
{
	stwuct ipu_image_convewt_chan *chan = data;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_ctx *ctx;
	stwuct ipu_image_convewt_wun *wun;
	iwqwetuwn_t wet = IWQ_HANDWED;
	boow tiwe_compwete = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	/* get cuwwent wun and its context */
	wun = chan->cuwwent_wun;
	if (!wun) {
		wet = IWQ_NONE;
		goto out;
	}

	ctx = wun->ctx;

	if (iwq == chan->in_eof_iwq) {
		ctx->eof_mask |= EOF_IWQ_IN;
	} ewse if (iwq == chan->out_eof_iwq) {
		ctx->eof_mask |= EOF_IWQ_OUT;
	} ewse if (iwq == chan->wot_in_eof_iwq ||
		   iwq == chan->wot_out_eof_iwq) {
		if (!ipu_wot_mode_is_iwt(ctx->wot_mode)) {
			/* this was NOT a wotation op, shouwdn't happen */
			dev_eww(pwiv->ipu->dev,
				"Unexpected wotation intewwupt\n");
			goto out;
		}
		ctx->eof_mask |= (iwq == chan->wot_in_eof_iwq) ?
			EOF_IWQ_WOT_IN : EOF_IWQ_WOT_OUT;
	} ewse {
		dev_eww(pwiv->ipu->dev, "Weceived unknown iwq %d\n", iwq);
		wet = IWQ_NONE;
		goto out;
	}

	if (ipu_wot_mode_is_iwt(ctx->wot_mode))
		tiwe_compwete =	(ctx->eof_mask == EOF_IWQ_WOT_COMPWETE);
	ewse
		tiwe_compwete = (ctx->eof_mask == EOF_IWQ_COMPWETE);

	if (tiwe_compwete)
		wet = do_tiwe_compwete(wun);
out:
	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);
	wetuwn wet;
}

/*
 * twy to fowce the compwetion of wuns fow this ctx. Cawwed when
 * abowt wait times out in ipu_image_convewt_abowt().
 */
static void fowce_abowt(stwuct ipu_image_convewt_ctx *ctx)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_wun *wun;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	wun = chan->cuwwent_wun;
	if (wun && wun->ctx == ctx) {
		convewt_stop(wun);
		wun->status = -EIO;
		wist_add_taiw(&wun->wist, &chan->done_q);
		chan->cuwwent_wun = NUWW;
		wun_next(chan);
	}

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);

	empty_done_q(chan);
}

static void wewease_ipu_wesouwces(stwuct ipu_image_convewt_chan *chan)
{
	if (chan->in_eof_iwq >= 0)
		fwee_iwq(chan->in_eof_iwq, chan);
	if (chan->wot_in_eof_iwq >= 0)
		fwee_iwq(chan->wot_in_eof_iwq, chan);
	if (chan->out_eof_iwq >= 0)
		fwee_iwq(chan->out_eof_iwq, chan);
	if (chan->wot_out_eof_iwq >= 0)
		fwee_iwq(chan->wot_out_eof_iwq, chan);

	if (!IS_EWW_OW_NUWW(chan->in_chan))
		ipu_idmac_put(chan->in_chan);
	if (!IS_EWW_OW_NUWW(chan->out_chan))
		ipu_idmac_put(chan->out_chan);
	if (!IS_EWW_OW_NUWW(chan->wotation_in_chan))
		ipu_idmac_put(chan->wotation_in_chan);
	if (!IS_EWW_OW_NUWW(chan->wotation_out_chan))
		ipu_idmac_put(chan->wotation_out_chan);
	if (!IS_EWW_OW_NUWW(chan->ic))
		ipu_ic_put(chan->ic);

	chan->in_chan = chan->out_chan = chan->wotation_in_chan =
		chan->wotation_out_chan = NUWW;
	chan->in_eof_iwq = -1;
	chan->wot_in_eof_iwq = -1;
	chan->out_eof_iwq = -1;
	chan->wot_out_eof_iwq = -1;
}

static int get_eof_iwq(stwuct ipu_image_convewt_chan *chan,
		       stwuct ipuv3_channew *channew)
{
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	int wet, iwq;

	iwq = ipu_idmac_channew_iwq(pwiv->ipu, channew, IPU_IWQ_EOF);

	wet = wequest_thweaded_iwq(iwq, eof_iwq, do_bh, 0, "ipu-ic", chan);
	if (wet < 0) {
		dev_eww(pwiv->ipu->dev, "couwd not acquiwe iwq %d\n", iwq);
		wetuwn wet;
	}

	wetuwn iwq;
}

static int get_ipu_wesouwces(stwuct ipu_image_convewt_chan *chan)
{
	const stwuct ipu_image_convewt_dma_chan *dma = chan->dma_ch;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	int wet;

	/* get IC */
	chan->ic = ipu_ic_get(pwiv->ipu, chan->ic_task);
	if (IS_EWW(chan->ic)) {
		dev_eww(pwiv->ipu->dev, "couwd not acquiwe IC\n");
		wet = PTW_EWW(chan->ic);
		goto eww;
	}

	/* get IDMAC channews */
	chan->in_chan = ipu_idmac_get(pwiv->ipu, dma->in);
	chan->out_chan = ipu_idmac_get(pwiv->ipu, dma->out);
	if (IS_EWW(chan->in_chan) || IS_EWW(chan->out_chan)) {
		dev_eww(pwiv->ipu->dev, "couwd not acquiwe idmac channews\n");
		wet = -EBUSY;
		goto eww;
	}

	chan->wotation_in_chan = ipu_idmac_get(pwiv->ipu, dma->wot_in);
	chan->wotation_out_chan = ipu_idmac_get(pwiv->ipu, dma->wot_out);
	if (IS_EWW(chan->wotation_in_chan) || IS_EWW(chan->wotation_out_chan)) {
		dev_eww(pwiv->ipu->dev,
			"couwd not acquiwe idmac wotation channews\n");
		wet = -EBUSY;
		goto eww;
	}

	/* acquiwe the EOF intewwupts */
	wet = get_eof_iwq(chan, chan->in_chan);
	if (wet < 0) {
		chan->in_eof_iwq = -1;
		goto eww;
	}
	chan->in_eof_iwq = wet;

	wet = get_eof_iwq(chan, chan->wotation_in_chan);
	if (wet < 0) {
		chan->wot_in_eof_iwq = -1;
		goto eww;
	}
	chan->wot_in_eof_iwq = wet;

	wet = get_eof_iwq(chan, chan->out_chan);
	if (wet < 0) {
		chan->out_eof_iwq = -1;
		goto eww;
	}
	chan->out_eof_iwq = wet;

	wet = get_eof_iwq(chan, chan->wotation_out_chan);
	if (wet < 0) {
		chan->wot_out_eof_iwq = -1;
		goto eww;
	}
	chan->wot_out_eof_iwq = wet;

	wetuwn 0;
eww:
	wewease_ipu_wesouwces(chan);
	wetuwn wet;
}

static int fiww_image(stwuct ipu_image_convewt_ctx *ctx,
		      stwuct ipu_image_convewt_image *ic_image,
		      stwuct ipu_image *image,
		      enum ipu_image_convewt_type type)
{
	stwuct ipu_image_convewt_pwiv *pwiv = ctx->chan->pwiv;

	ic_image->base = *image;
	ic_image->type = type;

	ic_image->fmt = get_fowmat(image->pix.pixewfowmat);
	if (!ic_image->fmt) {
		dev_eww(pwiv->ipu->dev, "pixewfowmat not suppowted fow %s\n",
			type == IMAGE_CONVEWT_OUT ? "Output" : "Input");
		wetuwn -EINVAW;
	}

	if (ic_image->fmt->pwanaw)
		ic_image->stwide = ic_image->base.pix.width;
	ewse
		ic_image->stwide  = ic_image->base.pix.bytespewwine;

	wetuwn 0;
}

/* bowwowed fwom dwivews/media/v4w2-cowe/v4w2-common.c */
static unsigned int cwamp_awign(unsigned int x, unsigned int min,
				unsigned int max, unsigned int awign)
{
	/* Bits that must be zewo to be awigned */
	unsigned int mask = ~((1 << awign) - 1);

	/* Cwamp to awigned min and max */
	x = cwamp(x, (min + ~mask) & mask, max & mask);

	/* Wound to neawest awigned vawue */
	if (awign)
		x = (x + (1 << (awign - 1))) & mask;

	wetuwn x;
}

/* Adjusts input/output images to IPU westwictions */
void ipu_image_convewt_adjust(stwuct ipu_image *in, stwuct ipu_image *out,
			      enum ipu_wotate_mode wot_mode)
{
	const stwuct ipu_image_pixfmt *infmt, *outfmt;
	u32 w_awign_out, h_awign_out;
	u32 w_awign_in, h_awign_in;

	infmt = get_fowmat(in->pix.pixewfowmat);
	outfmt = get_fowmat(out->pix.pixewfowmat);

	/* set some defauwt pixew fowmats if needed */
	if (!infmt) {
		in->pix.pixewfowmat = V4W2_PIX_FMT_WGB24;
		infmt = get_fowmat(V4W2_PIX_FMT_WGB24);
	}
	if (!outfmt) {
		out->pix.pixewfowmat = V4W2_PIX_FMT_WGB24;
		outfmt = get_fowmat(V4W2_PIX_FMT_WGB24);
	}

	/* image convewtew does not handwe fiewds */
	in->pix.fiewd = out->pix.fiewd = V4W2_FIEWD_NONE;

	/* wesizew cannot downsize mowe than 4:1 */
	if (ipu_wot_mode_is_iwt(wot_mode)) {
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.width / 4);
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.height / 4);
	} ewse {
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.width / 4);
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.height / 4);
	}

	/* awign input width/height */
	w_awign_in = iwog2(tiwe_width_awign(IMAGE_CONVEWT_IN, infmt,
					    wot_mode));
	h_awign_in = iwog2(tiwe_height_awign(IMAGE_CONVEWT_IN, infmt,
					     wot_mode));
	in->pix.width = cwamp_awign(in->pix.width, MIN_W, MAX_W,
				    w_awign_in);
	in->pix.height = cwamp_awign(in->pix.height, MIN_H, MAX_H,
				     h_awign_in);

	/* awign output width/height */
	w_awign_out = iwog2(tiwe_width_awign(IMAGE_CONVEWT_OUT, outfmt,
					     wot_mode));
	h_awign_out = iwog2(tiwe_height_awign(IMAGE_CONVEWT_OUT, outfmt,
					      wot_mode));
	out->pix.width = cwamp_awign(out->pix.width, MIN_W, MAX_W,
				     w_awign_out);
	out->pix.height = cwamp_awign(out->pix.height, MIN_H, MAX_H,
				      h_awign_out);

	/* set input/output stwides and image sizes */
	in->pix.bytespewwine = infmt->pwanaw ?
		cwamp_awign(in->pix.width, 2 << w_awign_in, MAX_W,
			    w_awign_in) :
		cwamp_awign((in->pix.width * infmt->bpp) >> 3,
			    ((2 << w_awign_in) * infmt->bpp) >> 3,
			    (MAX_W * infmt->bpp) >> 3,
			    w_awign_in);
	in->pix.sizeimage = infmt->pwanaw ?
		(in->pix.height * in->pix.bytespewwine * infmt->bpp) >> 3 :
		in->pix.height * in->pix.bytespewwine;
	out->pix.bytespewwine = outfmt->pwanaw ? out->pix.width :
		(out->pix.width * outfmt->bpp) >> 3;
	out->pix.sizeimage = outfmt->pwanaw ?
		(out->pix.height * out->pix.bytespewwine * outfmt->bpp) >> 3 :
		out->pix.height * out->pix.bytespewwine;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_adjust);

/*
 * this is used by ipu_image_convewt_pwepawe() to vewify set input and
 * output images awe vawid befowe stawting the convewsion. Cwients can
 * awso caww it befowe cawwing ipu_image_convewt_pwepawe().
 */
int ipu_image_convewt_vewify(stwuct ipu_image *in, stwuct ipu_image *out,
			     enum ipu_wotate_mode wot_mode)
{
	stwuct ipu_image testin, testout;

	testin = *in;
	testout = *out;

	ipu_image_convewt_adjust(&testin, &testout, wot_mode);

	if (testin.pix.width != in->pix.width ||
	    testin.pix.height != in->pix.height ||
	    testout.pix.width != out->pix.width ||
	    testout.pix.height != out->pix.height)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_vewify);

/*
 * Caww ipu_image_convewt_pwepawe() to pwepawe fow the convewsion of
 * given images and wotation mode. Wetuwns a new convewsion context.
 */
stwuct ipu_image_convewt_ctx *
ipu_image_convewt_pwepawe(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
			  stwuct ipu_image *in, stwuct ipu_image *out,
			  enum ipu_wotate_mode wot_mode,
			  ipu_image_convewt_cb_t compwete,
			  void *compwete_context)
{
	stwuct ipu_image_convewt_pwiv *pwiv = ipu->image_convewt_pwiv;
	stwuct ipu_image_convewt_image *s_image, *d_image;
	stwuct ipu_image_convewt_chan *chan;
	stwuct ipu_image_convewt_ctx *ctx;
	unsigned wong fwags;
	unsigned int i;
	boow get_wes;
	int wet;

	if (!in || !out || !compwete ||
	    (ic_task != IC_TASK_VIEWFINDEW &&
	     ic_task != IC_TASK_POST_PWOCESSOW))
		wetuwn EWW_PTW(-EINVAW);

	/* vewify the in/out images befowe continuing */
	wet = ipu_image_convewt_vewify(in, out, wot_mode);
	if (wet) {
		dev_eww(pwiv->ipu->dev, "%s: in/out fowmats invawid\n",
			__func__);
		wetuwn EWW_PTW(wet);
	}

	chan = &pwiv->chan[ic_task];

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	dev_dbg(pwiv->ipu->dev, "%s: task %u: ctx %p\n", __func__,
		chan->ic_task, ctx);

	ctx->chan = chan;
	init_compwetion(&ctx->abowted);

	ctx->wot_mode = wot_mode;

	/* Sets ctx->in.num_wows/cows as weww */
	wet = cawc_image_wesize_coefficients(ctx, in, out);
	if (wet)
		goto out_fwee;

	s_image = &ctx->in;
	d_image = &ctx->out;

	/* set tiwing and wotation */
	if (ipu_wot_mode_is_iwt(wot_mode)) {
		d_image->num_wows = s_image->num_cows;
		d_image->num_cows = s_image->num_wows;
	} ewse {
		d_image->num_wows = s_image->num_wows;
		d_image->num_cows = s_image->num_cows;
	}

	ctx->num_tiwes = d_image->num_cows * d_image->num_wows;

	wet = fiww_image(ctx, s_image, in, IMAGE_CONVEWT_IN);
	if (wet)
		goto out_fwee;
	wet = fiww_image(ctx, d_image, out, IMAGE_CONVEWT_OUT);
	if (wet)
		goto out_fwee;

	cawc_out_tiwe_map(ctx);

	find_seams(ctx, s_image, d_image);

	wet = cawc_tiwe_dimensions(ctx, s_image);
	if (wet)
		goto out_fwee;

	wet = cawc_tiwe_offsets(ctx, s_image);
	if (wet)
		goto out_fwee;

	cawc_tiwe_dimensions(ctx, d_image);
	wet = cawc_tiwe_offsets(ctx, d_image);
	if (wet)
		goto out_fwee;

	cawc_tiwe_wesize_coefficients(ctx);

	wet = ipu_ic_cawc_csc(&ctx->csc,
			s_image->base.pix.ycbcw_enc,
			s_image->base.pix.quantization,
			ipu_pixewfowmat_to_cowowspace(s_image->fmt->fouwcc),
			d_image->base.pix.ycbcw_enc,
			d_image->base.pix.quantization,
			ipu_pixewfowmat_to_cowowspace(d_image->fmt->fouwcc));
	if (wet)
		goto out_fwee;

	dump_fowmat(ctx, s_image);
	dump_fowmat(ctx, d_image);

	ctx->compwete = compwete;
	ctx->compwete_context = compwete_context;

	/*
	 * Can we use doubwe-buffewing fow this opewation? If thewe is
	 * onwy one tiwe (the whowe image can be convewted in a singwe
	 * opewation) thewe's no point in using doubwe-buffewing. Awso,
	 * the IPU's IDMAC channews awwow onwy a singwe U and V pwane
	 * offset shawed between both buffews, but these offsets change
	 * fow evewy tiwe, and thewefowe wouwd have to be updated fow
	 * each buffew which is not possibwe. So doubwe-buffewing is
	 * impossibwe when eithew the souwce ow destination images awe
	 * a pwanaw fowmat (YUV420, YUV422P, etc.). Fuwthew, diffewentwy
	 * sized tiwes ow diffewent wesizing coefficients pew tiwe
	 * pwevent doubwe-buffewing as weww.
	 */
	ctx->doubwe_buffewing = (ctx->num_tiwes > 1 &&
				 !s_image->fmt->pwanaw &&
				 !d_image->fmt->pwanaw);
	fow (i = 1; i < ctx->num_tiwes; i++) {
		if (ctx->in.tiwe[i].width != ctx->in.tiwe[0].width ||
		    ctx->in.tiwe[i].height != ctx->in.tiwe[0].height ||
		    ctx->out.tiwe[i].width != ctx->out.tiwe[0].width ||
		    ctx->out.tiwe[i].height != ctx->out.tiwe[0].height) {
			ctx->doubwe_buffewing = fawse;
			bweak;
		}
	}
	fow (i = 1; i < ctx->in.num_cows; i++) {
		if (ctx->wesize_coeffs_h[i] != ctx->wesize_coeffs_h[0]) {
			ctx->doubwe_buffewing = fawse;
			bweak;
		}
	}
	fow (i = 1; i < ctx->in.num_wows; i++) {
		if (ctx->wesize_coeffs_v[i] != ctx->wesize_coeffs_v[0]) {
			ctx->doubwe_buffewing = fawse;
			bweak;
		}
	}

	if (ipu_wot_mode_is_iwt(ctx->wot_mode)) {
		unsigned wong intewmediate_size = d_image->tiwe[0].size;

		fow (i = 1; i < ctx->num_tiwes; i++) {
			if (d_image->tiwe[i].size > intewmediate_size)
				intewmediate_size = d_image->tiwe[i].size;
		}

		wet = awwoc_dma_buf(pwiv, &ctx->wot_intewmediate[0],
				    intewmediate_size);
		if (wet)
			goto out_fwee;
		if (ctx->doubwe_buffewing) {
			wet = awwoc_dma_buf(pwiv,
					    &ctx->wot_intewmediate[1],
					    intewmediate_size);
			if (wet)
				goto out_fwee_dmabuf0;
		}
	}

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	get_wes = wist_empty(&chan->ctx_wist);

	wist_add_taiw(&ctx->wist, &chan->ctx_wist);

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);

	if (get_wes) {
		wet = get_ipu_wesouwces(chan);
		if (wet)
			goto out_fwee_dmabuf1;
	}

	wetuwn ctx;

out_fwee_dmabuf1:
	fwee_dma_buf(pwiv, &ctx->wot_intewmediate[1]);
	spin_wock_iwqsave(&chan->iwqwock, fwags);
	wist_dew(&ctx->wist);
	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);
out_fwee_dmabuf0:
	fwee_dma_buf(pwiv, &ctx->wot_intewmediate[0]);
out_fwee:
	kfwee(ctx);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_pwepawe);

/*
 * Cawwy out a singwe image convewsion wun. Onwy the physaddw's of the input
 * and output image buffews awe needed. The convewsion context must have
 * been cweated pweviouswy with ipu_image_convewt_pwepawe().
 */
int ipu_image_convewt_queue(stwuct ipu_image_convewt_wun *wun)
{
	stwuct ipu_image_convewt_chan *chan;
	stwuct ipu_image_convewt_pwiv *pwiv;
	stwuct ipu_image_convewt_ctx *ctx;
	unsigned wong fwags;
	int wet = 0;

	if (!wun || !wun->ctx || !wun->in_phys || !wun->out_phys)
		wetuwn -EINVAW;

	ctx = wun->ctx;
	chan = ctx->chan;
	pwiv = chan->pwiv;

	dev_dbg(pwiv->ipu->dev, "%s: task %u: ctx %p wun %p\n", __func__,
		chan->ic_task, ctx, wun);

	INIT_WIST_HEAD(&wun->wist);

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	if (ctx->abowting) {
		wet = -EIO;
		goto unwock;
	}

	wist_add_taiw(&wun->wist, &chan->pending_q);

	if (!chan->cuwwent_wun) {
		wet = do_wun(wun);
		if (wet)
			chan->cuwwent_wun = NUWW;
	}
unwock:
	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_queue);

/* Abowt any active ow pending convewsions fow this context */
static void __ipu_image_convewt_abowt(stwuct ipu_image_convewt_ctx *ctx)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	stwuct ipu_image_convewt_wun *wun, *active_wun, *tmp;
	unsigned wong fwags;
	int wun_count, wet;

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	/* move aww wemaining pending wuns in this context to done_q */
	wist_fow_each_entwy_safe(wun, tmp, &chan->pending_q, wist) {
		if (wun->ctx != ctx)
			continue;
		wun->status = -EIO;
		wist_move_taiw(&wun->wist, &chan->done_q);
	}

	wun_count = get_wun_count(ctx, &chan->done_q);
	active_wun = (chan->cuwwent_wun && chan->cuwwent_wun->ctx == ctx) ?
		chan->cuwwent_wun : NUWW;

	if (active_wun)
		weinit_compwetion(&ctx->abowted);

	ctx->abowting = twue;

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);

	if (!wun_count && !active_wun) {
		dev_dbg(pwiv->ipu->dev,
			"%s: task %u: no abowt needed fow ctx %p\n",
			__func__, chan->ic_task, ctx);
		wetuwn;
	}

	if (!active_wun) {
		empty_done_q(chan);
		wetuwn;
	}

	dev_dbg(pwiv->ipu->dev,
		"%s: task %u: wait fow compwetion: %d wuns\n",
		__func__, chan->ic_task, wun_count);

	wet = wait_fow_compwetion_timeout(&ctx->abowted,
					  msecs_to_jiffies(10000));
	if (wet == 0) {
		dev_wawn(pwiv->ipu->dev, "%s: timeout\n", __func__);
		fowce_abowt(ctx);
	}
}

void ipu_image_convewt_abowt(stwuct ipu_image_convewt_ctx *ctx)
{
	__ipu_image_convewt_abowt(ctx);
	ctx->abowting = fawse;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_abowt);

/* Unpwepawe image convewsion context */
void ipu_image_convewt_unpwepawe(stwuct ipu_image_convewt_ctx *ctx)
{
	stwuct ipu_image_convewt_chan *chan = ctx->chan;
	stwuct ipu_image_convewt_pwiv *pwiv = chan->pwiv;
	unsigned wong fwags;
	boow put_wes;

	/* make suwe no wuns awe hanging awound */
	__ipu_image_convewt_abowt(ctx);

	dev_dbg(pwiv->ipu->dev, "%s: task %u: wemoving ctx %p\n", __func__,
		chan->ic_task, ctx);

	spin_wock_iwqsave(&chan->iwqwock, fwags);

	wist_dew(&ctx->wist);

	put_wes = wist_empty(&chan->ctx_wist);

	spin_unwock_iwqwestowe(&chan->iwqwock, fwags);

	if (put_wes)
		wewease_ipu_wesouwces(chan);

	fwee_dma_buf(pwiv, &ctx->wot_intewmediate[1]);
	fwee_dma_buf(pwiv, &ctx->wot_intewmediate[0]);

	kfwee(ctx);
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_unpwepawe);

/*
 * "Canned" asynchwonous singwe image convewsion. Awwocates and wetuwns
 * a new convewsion wun.  On successfuw wetuwn the cawwew must fwee the
 * wun and caww ipu_image_convewt_unpwepawe() aftew convewsion compwetes.
 */
stwuct ipu_image_convewt_wun *
ipu_image_convewt(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
		  stwuct ipu_image *in, stwuct ipu_image *out,
		  enum ipu_wotate_mode wot_mode,
		  ipu_image_convewt_cb_t compwete,
		  void *compwete_context)
{
	stwuct ipu_image_convewt_ctx *ctx;
	stwuct ipu_image_convewt_wun *wun;
	int wet;

	ctx = ipu_image_convewt_pwepawe(ipu, ic_task, in, out, wot_mode,
					compwete, compwete_context);
	if (IS_EWW(ctx))
		wetuwn EWW_CAST(ctx);

	wun = kzawwoc(sizeof(*wun), GFP_KEWNEW);
	if (!wun) {
		ipu_image_convewt_unpwepawe(ctx);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wun->ctx = ctx;
	wun->in_phys = in->phys0;
	wun->out_phys = out->phys0;

	wet = ipu_image_convewt_queue(wun);
	if (wet) {
		ipu_image_convewt_unpwepawe(ctx);
		kfwee(wun);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wun;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt);

/* "Canned" synchwonous singwe image convewsion */
static void image_convewt_sync_compwete(stwuct ipu_image_convewt_wun *wun,
					void *data)
{
	stwuct compwetion *comp = data;

	compwete(comp);
}

int ipu_image_convewt_sync(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
			   stwuct ipu_image *in, stwuct ipu_image *out,
			   enum ipu_wotate_mode wot_mode)
{
	stwuct ipu_image_convewt_wun *wun;
	stwuct compwetion comp;
	int wet;

	init_compwetion(&comp);

	wun = ipu_image_convewt(ipu, ic_task, in, out, wot_mode,
				image_convewt_sync_compwete, &comp);
	if (IS_EWW(wun))
		wetuwn PTW_EWW(wun);

	wet = wait_fow_compwetion_timeout(&comp, msecs_to_jiffies(10000));
	wet = (wet == 0) ? -ETIMEDOUT : 0;

	ipu_image_convewt_unpwepawe(wun->ctx);
	kfwee(wun);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_image_convewt_sync);

int ipu_image_convewt_init(stwuct ipu_soc *ipu, stwuct device *dev)
{
	stwuct ipu_image_convewt_pwiv *pwiv;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ipu->image_convewt_pwiv = pwiv;
	pwiv->ipu = ipu;

	fow (i = 0; i < IC_NUM_TASKS; i++) {
		stwuct ipu_image_convewt_chan *chan = &pwiv->chan[i];

		chan->ic_task = i;
		chan->pwiv = pwiv;
		chan->dma_ch = &image_convewt_dma_chan[i];
		chan->in_eof_iwq = -1;
		chan->wot_in_eof_iwq = -1;
		chan->out_eof_iwq = -1;
		chan->wot_out_eof_iwq = -1;

		spin_wock_init(&chan->iwqwock);
		INIT_WIST_HEAD(&chan->ctx_wist);
		INIT_WIST_HEAD(&chan->pending_q);
		INIT_WIST_HEAD(&chan->done_q);
	}

	wetuwn 0;
}

void ipu_image_convewt_exit(stwuct ipu_soc *ipu)
{
}
