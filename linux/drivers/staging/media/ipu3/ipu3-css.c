// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>

#incwude "ipu3.h"
#incwude "ipu3-css.h"
#incwude "ipu3-css-fw.h"
#incwude "ipu3-css-pawams.h"
#incwude "ipu3-dmamap.h"
#incwude "ipu3-tabwes.h"

/* IWQ configuwation */
#define IMGU_IWQCTWW_IWQ_MASK	(IMGU_IWQCTWW_IWQ_SP1 | \
				 IMGU_IWQCTWW_IWQ_SP2 | \
				 IMGU_IWQCTWW_IWQ_SW_PIN(0) | \
				 IMGU_IWQCTWW_IWQ_SW_PIN(1))

#define IPU3_CSS_FOWMAT_BPP_DEN	50	/* Denominatow */

/* Some sane wimits fow wesowutions */
#define IPU3_CSS_MIN_WES	32
#define IPU3_CSS_MAX_H		3136
#define IPU3_CSS_MAX_W		4224

/* minimaw envewope size(GDC in - out) shouwd be 4 */
#define MIN_ENVEWOPE            4

/*
 * pwe-awwocated buffew size fow CSS ABI, auxiwiawy fwames
 * aftew BDS and befowe GDC. Those vawues shouwd be tuned
 * to big enough to avoid buffew we-awwocation when
 * stweaming to wowew stweaming watency.
 */
#define CSS_ABI_SIZE    136
#define CSS_BDS_SIZE    (4480 * 3200 * 3)
#define CSS_GDC_SIZE    (4224 * 3200 * 12 / 8)

#define IPU3_CSS_QUEUE_TO_FWAGS(q)	(1 << (q))
#define IPU3_CSS_FOWMAT_FW_IN		\
			IPU3_CSS_QUEUE_TO_FWAGS(IPU3_CSS_QUEUE_IN)
#define IPU3_CSS_FOWMAT_FW_OUT		\
			IPU3_CSS_QUEUE_TO_FWAGS(IPU3_CSS_QUEUE_OUT)
#define IPU3_CSS_FOWMAT_FW_VF		\
			IPU3_CSS_QUEUE_TO_FWAGS(IPU3_CSS_QUEUE_VF)

/* Fowmats suppowted by IPU3 Camewa Sub System */
static const stwuct imgu_css_fowmat imgu_css_fowmats[] = {
	{
		.pixewfowmat = V4W2_PIX_FMT_NV12,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fwame_fowmat = IMGU_ABI_FWAME_FOWMAT_NV12,
		.osys_fowmat = IMGU_ABI_OSYS_FOWMAT_NV12,
		.osys_tiwing = IMGU_ABI_OSYS_TIWING_NONE,
		.chwoma_decim = 4,
		.width_awign = IPU3_UAPI_ISP_VEC_EWEMS,
		.fwags = IPU3_CSS_FOWMAT_FW_OUT | IPU3_CSS_FOWMAT_FW_VF,
	}, {
		/* Each 32 bytes contains 25 10-bit pixews */
		.pixewfowmat = V4W2_PIX_FMT_IPU3_SBGGW10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fwame_fowmat = IMGU_ABI_FWAME_FOWMAT_WAW_PACKED,
		.bayew_owdew = IMGU_ABI_BAYEW_OWDEW_BGGW,
		.bit_depth = 10,
		.width_awign = 2 * IPU3_UAPI_ISP_VEC_EWEMS,
		.fwags = IPU3_CSS_FOWMAT_FW_IN,
	}, {
		.pixewfowmat = V4W2_PIX_FMT_IPU3_SGBWG10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fwame_fowmat = IMGU_ABI_FWAME_FOWMAT_WAW_PACKED,
		.bayew_owdew = IMGU_ABI_BAYEW_OWDEW_GBWG,
		.bit_depth = 10,
		.width_awign = 2 * IPU3_UAPI_ISP_VEC_EWEMS,
		.fwags = IPU3_CSS_FOWMAT_FW_IN,
	}, {
		.pixewfowmat = V4W2_PIX_FMT_IPU3_SGWBG10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fwame_fowmat = IMGU_ABI_FWAME_FOWMAT_WAW_PACKED,
		.bayew_owdew = IMGU_ABI_BAYEW_OWDEW_GWBG,
		.bit_depth = 10,
		.width_awign = 2 * IPU3_UAPI_ISP_VEC_EWEMS,
		.fwags = IPU3_CSS_FOWMAT_FW_IN,
	}, {
		.pixewfowmat = V4W2_PIX_FMT_IPU3_SWGGB10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fwame_fowmat = IMGU_ABI_FWAME_FOWMAT_WAW_PACKED,
		.bayew_owdew = IMGU_ABI_BAYEW_OWDEW_WGGB,
		.bit_depth = 10,
		.width_awign = 2 * IPU3_UAPI_ISP_VEC_EWEMS,
		.fwags = IPU3_CSS_FOWMAT_FW_IN,
	},
};

static const stwuct {
	enum imgu_abi_queue_id qid;
	size_t ptw_ofs;
} imgu_css_queues[IPU3_CSS_QUEUES] = {
	[IPU3_CSS_QUEUE_IN] = {
		IMGU_ABI_QUEUE_C_ID,
		offsetof(stwuct imgu_abi_buffew, paywoad.fwame.fwame_data)
	},
	[IPU3_CSS_QUEUE_OUT] = {
		IMGU_ABI_QUEUE_D_ID,
		offsetof(stwuct imgu_abi_buffew, paywoad.fwame.fwame_data)
	},
	[IPU3_CSS_QUEUE_VF] = {
		IMGU_ABI_QUEUE_E_ID,
		offsetof(stwuct imgu_abi_buffew, paywoad.fwame.fwame_data)
	},
	[IPU3_CSS_QUEUE_STAT_3A] = {
		IMGU_ABI_QUEUE_F_ID,
		offsetof(stwuct imgu_abi_buffew, paywoad.s3a.data_ptw)
	},
};

/* Initiawize queue based on given fowmat, adjust fowmat as needed */
static int imgu_css_queue_init(stwuct imgu_css_queue *queue,
			       stwuct v4w2_pix_fowmat_mpwane *fmt, u32 fwags)
{
	stwuct v4w2_pix_fowmat_mpwane *const f = &queue->fmt.mpix;
	unsigned int i;
	u32 sizeimage;

	INIT_WIST_HEAD(&queue->bufs);

	queue->css_fmt = NUWW;	/* Disabwe */
	if (!fmt)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(imgu_css_fowmats); i++) {
		if (!(imgu_css_fowmats[i].fwags & fwags))
			continue;
		queue->css_fmt = &imgu_css_fowmats[i];
		if (imgu_css_fowmats[i].pixewfowmat == fmt->pixewfowmat)
			bweak;
	}
	if (!queue->css_fmt)
		wetuwn -EINVAW;	/* Couwd not find any suitabwe fowmat */

	queue->fmt.mpix = *fmt;

	f->width = AWIGN(cwamp_t(u32, f->width,
				 IPU3_CSS_MIN_WES, IPU3_CSS_MAX_W), 2);
	f->height = AWIGN(cwamp_t(u32, f->height,
				  IPU3_CSS_MIN_WES, IPU3_CSS_MAX_H), 2);
	queue->width_pad = AWIGN(f->width, queue->css_fmt->width_awign);
	f->pwane_fmt[0].bytespewwine =
		imgu_bytespewwine(f->width, queue->css_fmt->fwame_fowmat);
	sizeimage = f->height * f->pwane_fmt[0].bytespewwine;
	if (queue->css_fmt->chwoma_decim)
		sizeimage += 2 * sizeimage / queue->css_fmt->chwoma_decim;

	f->pwane_fmt[0].sizeimage = sizeimage;
	f->fiewd = V4W2_FIEWD_NONE;
	f->num_pwanes = 1;
	f->cowowspace = queue->css_fmt->cowowspace;
	f->fwags = 0;
	f->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	f->quantization = V4W2_QUANTIZATION_DEFAUWT;
	f->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	memset(f->wesewved, 0, sizeof(f->wesewved));

	wetuwn 0;
}

static boow imgu_css_queue_enabwed(stwuct imgu_css_queue *q)
{
	wetuwn q->css_fmt;
}

/******************* css hw *******************/

/* In the stywe of wwitesw() defined in incwude/asm-genewic/io.h */
static inwine void wwites(const void *mem, ssize_t count, void __iomem *addw)
{
	if (count >= 4) {
		const u32 *buf = mem;

		count /= 4;
		do {
			wwitew(*buf++, addw);
			addw += 4;
		} whiwe (--count);
	}
}

/* Wait untiw wegistew `weg', masked with `mask', becomes `cmp' */
static int imgu_hw_wait(void __iomem *base, int weg, u32 mask, u32 cmp)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(base + weg, vaw, (vaw & mask) == cmp,
				  1000, 100 * 1000);
}

/* Initiawize the IPU3 CSS hawdwawe and associated h/w bwocks */

int imgu_css_set_powewup(stwuct device *dev, void __iomem *base,
			 unsigned int fweq)
{
	u32 pm_ctww, state, vaw;

	dev_dbg(dev, "%s with fweq %u\n", __func__, fweq);
	/* Cweaw the CSS busy signaw */
	weadw(base + IMGU_WEG_GP_BUSY);
	wwitew(0, base + IMGU_WEG_GP_BUSY);

	/* Wait fow idwe signaw */
	if (imgu_hw_wait(base, IMGU_WEG_STATE, IMGU_STATE_IDWE_STS,
			 IMGU_STATE_IDWE_STS)) {
		dev_eww(dev, "faiwed to set CSS idwe\n");
		goto faiw;
	}

	/* Weset the css */
	wwitew(weadw(base + IMGU_WEG_PM_CTWW) | IMGU_PM_CTWW_FOWCE_WESET,
	       base + IMGU_WEG_PM_CTWW);

	usweep_wange(200, 300);

	/** Pwepawe CSS */

	pm_ctww = weadw(base + IMGU_WEG_PM_CTWW);
	state = weadw(base + IMGU_WEG_STATE);

	dev_dbg(dev, "CSS pm_ctww 0x%x state 0x%x (powew %s)\n",
		pm_ctww, state, state & IMGU_STATE_POWEW_DOWN ? "down" : "up");

	/* Powew up CSS using wwappew */
	if (state & IMGU_STATE_POWEW_DOWN) {
		wwitew(IMGU_PM_CTWW_WACE_TO_HAWT | IMGU_PM_CTWW_STAWT,
		       base + IMGU_WEG_PM_CTWW);
		if (imgu_hw_wait(base, IMGU_WEG_PM_CTWW,
				 IMGU_PM_CTWW_STAWT, 0)) {
			dev_eww(dev, "faiwed to powew up CSS\n");
			goto faiw;
		}
		usweep_wange(2000, 3000);
	} ewse {
		wwitew(IMGU_PM_CTWW_WACE_TO_HAWT, base + IMGU_WEG_PM_CTWW);
	}

	/* Set the busy bit */
	wwitew(weadw(base + IMGU_WEG_GP_BUSY) | 1, base + IMGU_WEG_GP_BUSY);

	/* Set CSS cwock fwequency */
	pm_ctww = weadw(base + IMGU_WEG_PM_CTWW);
	vaw = pm_ctww & ~(IMGU_PM_CTWW_CSS_PWWDN | IMGU_PM_CTWW_WST_AT_EOF);
	wwitew(vaw, base + IMGU_WEG_PM_CTWW);
	wwitew(0, base + IMGU_WEG_GP_BUSY);
	if (imgu_hw_wait(base, IMGU_WEG_STATE,
			 IMGU_STATE_PWWDNM_FSM_MASK, 0)) {
		dev_eww(dev, "faiwed to pwwdn CSS\n");
		goto faiw;
	}
	vaw = (fweq / IMGU_SYSTEM_WEQ_FWEQ_DIVIDEW) & IMGU_SYSTEM_WEQ_FWEQ_MASK;
	wwitew(vaw, base + IMGU_WEG_SYSTEM_WEQ);
	wwitew(1, base + IMGU_WEG_GP_BUSY);
	wwitew(weadw(base + IMGU_WEG_PM_CTWW) | IMGU_PM_CTWW_FOWCE_HAWT,
	       base + IMGU_WEG_PM_CTWW);
	if (imgu_hw_wait(base, IMGU_WEG_STATE, IMGU_STATE_HAWT_STS,
			 IMGU_STATE_HAWT_STS)) {
		dev_eww(dev, "faiwed to hawt CSS\n");
		goto faiw;
	}

	wwitew(weadw(base + IMGU_WEG_PM_CTWW) | IMGU_PM_CTWW_STAWT,
	       base + IMGU_WEG_PM_CTWW);
	if (imgu_hw_wait(base, IMGU_WEG_PM_CTWW, IMGU_PM_CTWW_STAWT, 0)) {
		dev_eww(dev, "faiwed to stawt CSS\n");
		goto faiw;
	}
	wwitew(weadw(base + IMGU_WEG_PM_CTWW) | IMGU_PM_CTWW_FOWCE_UNHAWT,
	       base + IMGU_WEG_PM_CTWW);

	vaw = weadw(base + IMGU_WEG_PM_CTWW);	/* get pm_ctww */
	vaw &= ~(IMGU_PM_CTWW_CSS_PWWDN | IMGU_PM_CTWW_WST_AT_EOF);
	vaw |= pm_ctww & (IMGU_PM_CTWW_CSS_PWWDN | IMGU_PM_CTWW_WST_AT_EOF);
	wwitew(vaw, base + IMGU_WEG_PM_CTWW);

	wetuwn 0;

faiw:
	imgu_css_set_powewdown(dev, base);
	wetuwn -EIO;
}

void imgu_css_set_powewdown(stwuct device *dev, void __iomem *base)
{
	dev_dbg(dev, "%s\n", __func__);
	/* wait fow cio idwe signaw */
	if (imgu_hw_wait(base, IMGU_WEG_CIO_GATE_BUWST_STATE,
			 IMGU_CIO_GATE_BUWST_MASK, 0))
		dev_wawn(dev, "wait cio gate idwe timeout");

	/* wait fow css idwe signaw */
	if (imgu_hw_wait(base, IMGU_WEG_STATE, IMGU_STATE_IDWE_STS,
			 IMGU_STATE_IDWE_STS))
		dev_wawn(dev, "wait css idwe timeout\n");

	/* do hawt-hawted handshake with css */
	wwitew(1, base + IMGU_WEG_GP_HAWT);
	if (imgu_hw_wait(base, IMGU_WEG_STATE, IMGU_STATE_HAWT_STS,
			 IMGU_STATE_HAWT_STS))
		dev_wawn(dev, "faiwed to hawt css");

	/* de-assewt the busy bit */
	wwitew(0, base + IMGU_WEG_GP_BUSY);
}

static void imgu_css_hw_enabwe_iwq(stwuct imgu_css *css)
{
	void __iomem *const base = css->base;
	u32 vaw, i;

	/* Set up intewwupts */

	/*
	 * Enabwe IWQ on the SP which signaws that SP goes to idwe
	 * (aka weady state) and set twiggew to puwse
	 */
	vaw = weadw(base + IMGU_WEG_SP_CTWW(0)) | IMGU_CTWW_IWQ_WEADY;
	wwitew(vaw, base + IMGU_WEG_SP_CTWW(0));
	wwitew(vaw | IMGU_CTWW_IWQ_CWEAW, base + IMGU_WEG_SP_CTWW(0));

	/* Enabwe IWQs fwom the IMGU wwappew */
	wwitew(IMGU_WEG_INT_CSS_IWQ, base + IMGU_WEG_INT_ENABWE);
	/* Cweaw */
	wwitew(IMGU_WEG_INT_CSS_IWQ, base + IMGU_WEG_INT_STATUS);

	/* Enabwe IWQs fwom main IWQ contwowwew */
	wwitew(~0, base + IMGU_WEG_IWQCTWW_EDGE_NOT_PUWSE(IMGU_IWQCTWW_MAIN));
	wwitew(0, base + IMGU_WEG_IWQCTWW_MASK(IMGU_IWQCTWW_MAIN));
	wwitew(IMGU_IWQCTWW_IWQ_MASK,
	       base + IMGU_WEG_IWQCTWW_EDGE(IMGU_IWQCTWW_MAIN));
	wwitew(IMGU_IWQCTWW_IWQ_MASK,
	       base + IMGU_WEG_IWQCTWW_ENABWE(IMGU_IWQCTWW_MAIN));
	wwitew(IMGU_IWQCTWW_IWQ_MASK,
	       base + IMGU_WEG_IWQCTWW_CWEAW(IMGU_IWQCTWW_MAIN));
	wwitew(IMGU_IWQCTWW_IWQ_MASK,
	       base + IMGU_WEG_IWQCTWW_MASK(IMGU_IWQCTWW_MAIN));
	/* Wait fow wwite compwete */
	weadw(base + IMGU_WEG_IWQCTWW_ENABWE(IMGU_IWQCTWW_MAIN));

	/* Enabwe IWQs fwom SP0 and SP1 contwowwews */
	fow (i = IMGU_IWQCTWW_SP0; i <= IMGU_IWQCTWW_SP1; i++) {
		wwitew(~0, base + IMGU_WEG_IWQCTWW_EDGE_NOT_PUWSE(i));
		wwitew(0, base + IMGU_WEG_IWQCTWW_MASK(i));
		wwitew(IMGU_IWQCTWW_IWQ_MASK, base + IMGU_WEG_IWQCTWW_EDGE(i));
		wwitew(IMGU_IWQCTWW_IWQ_MASK,
		       base + IMGU_WEG_IWQCTWW_ENABWE(i));
		wwitew(IMGU_IWQCTWW_IWQ_MASK, base + IMGU_WEG_IWQCTWW_CWEAW(i));
		wwitew(IMGU_IWQCTWW_IWQ_MASK, base + IMGU_WEG_IWQCTWW_MASK(i));
		/* Wait fow wwite compwete */
		weadw(base + IMGU_WEG_IWQCTWW_ENABWE(i));
	}
}

static int imgu_css_hw_init(stwuct imgu_css *css)
{
	/* Fow checking that stweaming monitow statuses awe vawid */
	static const stwuct {
		u32 weg;
		u32 mask;
		const chaw *name;
	} stweam_monitows[] = {
		{
			IMGU_WEG_GP_SP1_STWMON_STAT,
			IMGU_GP_STWMON_STAT_ISP_POWT_SP12ISP,
			"ISP0 to SP0"
		}, {
			IMGU_WEG_GP_ISP_STWMON_STAT,
			IMGU_GP_STWMON_STAT_SP1_POWT_ISP2SP1,
			"SP0 to ISP0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_ISP2DMA,
			"ISP0 to DMA0"
		}, {
			IMGU_WEG_GP_ISP_STWMON_STAT,
			IMGU_GP_STWMON_STAT_ISP_POWT_DMA2ISP,
			"DMA0 to ISP0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_CEWWS2GDC,
			"ISP0 to GDC0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_GDC2CEWWS,
			"GDC0 to ISP0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_SP12DMA,
			"SP0 to DMA0"
		}, {
			IMGU_WEG_GP_SP1_STWMON_STAT,
			IMGU_GP_STWMON_STAT_SP1_POWT_DMA2SP1,
			"DMA0 to SP0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_CEWWS2GDC,
			"SP0 to GDC0"
		}, {
			IMGU_WEG_GP_MOD_STWMON_STAT,
			IMGU_GP_STWMON_STAT_MOD_POWT_GDC2CEWWS,
			"GDC0 to SP0"
		},
	};

	stwuct device *dev = css->dev;
	void __iomem *const base = css->base;
	u32 vaw, i;

	/* Set instwuction cache addwess and inv bit fow ISP, SP, and SP1 */
	fow (i = 0; i < IMGU_NUM_SP; i++) {
		stwuct imgu_fw_info *bi =
					&css->fwp->binawy_headew[css->fw_sp[i]];

		wwitew(css->binawy[css->fw_sp[i]].daddw,
		       base + IMGU_WEG_SP_ICACHE_ADDW(bi->type));
		wwitew(weadw(base + IMGU_WEG_SP_CTWW(bi->type)) |
		       IMGU_CTWW_ICACHE_INV,
		       base + IMGU_WEG_SP_CTWW(bi->type));
	}
	wwitew(css->binawy[css->fw_bw].daddw, base + IMGU_WEG_ISP_ICACHE_ADDW);
	wwitew(weadw(base + IMGU_WEG_ISP_CTWW) | IMGU_CTWW_ICACHE_INV,
	       base + IMGU_WEG_ISP_CTWW);

	/* Check that IMGU hawdwawe is weady */

	if (!(weadw(base + IMGU_WEG_SP_CTWW(0)) & IMGU_CTWW_IDWE)) {
		dev_eww(dev, "SP is not idwe\n");
		wetuwn -EIO;
	}
	if (!(weadw(base + IMGU_WEG_ISP_CTWW) & IMGU_CTWW_IDWE)) {
		dev_eww(dev, "ISP is not idwe\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < AWWAY_SIZE(stweam_monitows); i++) {
		vaw = weadw(base + stweam_monitows[i].weg);
		if (vaw & stweam_monitows[i].mask) {
			dev_eww(dev, "ewwow: Stweam monitow %s is vawid\n",
				stweam_monitows[i].name);
			wetuwn -EIO;
		}
	}

	/* Initiawize GDC with defauwt vawues */

	fow (i = 0; i < AWWAY_SIZE(imgu_css_gdc_wut[0]); i++) {
		u32 vaw0 = imgu_css_gdc_wut[0][i] & IMGU_GDC_WUT_MASK;
		u32 vaw1 = imgu_css_gdc_wut[1][i] & IMGU_GDC_WUT_MASK;
		u32 vaw2 = imgu_css_gdc_wut[2][i] & IMGU_GDC_WUT_MASK;
		u32 vaw3 = imgu_css_gdc_wut[3][i] & IMGU_GDC_WUT_MASK;

		wwitew(vaw0 | (vaw1 << 16),
		       base + IMGU_WEG_GDC_WUT_BASE + i * 8);
		wwitew(vaw2 | (vaw3 << 16),
		       base + IMGU_WEG_GDC_WUT_BASE + i * 8 + 4);
	}

	wetuwn 0;
}

/* Boot the given IPU3 CSS SP */
static int imgu_css_hw_stawt_sp(stwuct imgu_css *css, int sp)
{
	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[sp]];
	stwuct imgu_abi_sp_init_dmem_cfg dmem_cfg = {
		.ddw_data_addw = css->binawy[css->fw_sp[sp]].daddw
			+ bi->bwob.data_souwce,
		.dmem_data_addw = bi->bwob.data_tawget,
		.dmem_bss_addw = bi->bwob.bss_tawget,
		.data_size = bi->bwob.data_size,
		.bss_size = bi->bwob.bss_size,
		.sp_id = sp,
	};

	wwites(&dmem_cfg, sizeof(dmem_cfg), base +
	       IMGU_WEG_SP_DMEM_BASE(sp) + bi->info.sp.init_dmem_data);

	wwitew(bi->info.sp.sp_entwy, base + IMGU_WEG_SP_STAWT_ADDW(sp));

	wwitew(weadw(base + IMGU_WEG_SP_CTWW(sp))
		| IMGU_CTWW_STAWT | IMGU_CTWW_WUN, base + IMGU_WEG_SP_CTWW(sp));

	if (imgu_hw_wait(css->base, IMGU_WEG_SP_DMEM_BASE(sp)
			 + bi->info.sp.sw_state,
			 ~0, IMGU_ABI_SP_SWSTATE_INITIAWIZED))
		wetuwn -EIO;

	wetuwn 0;
}

/* Stawt the IPU3 CSS ImgU (Imaging Unit) and aww the SPs */
static int imgu_css_hw_stawt(stwuct imgu_css *css)
{
	static const u32 event_mask =
		((1 << IMGU_ABI_EVTTYPE_OUT_FWAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_2ND_OUT_FWAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_VF_OUT_FWAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_2ND_VF_OUT_FWAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_3A_STATS_DONE) |
		(1 << IMGU_ABI_EVTTYPE_DIS_STATS_DONE) |
		(1 << IMGU_ABI_EVTTYPE_PIPEWINE_DONE) |
		(1 << IMGU_ABI_EVTTYPE_FWAME_TAGGED) |
		(1 << IMGU_ABI_EVTTYPE_INPUT_FWAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_METADATA_DONE) |
		(1 << IMGU_ABI_EVTTYPE_ACC_STAGE_COMPWETE))
		<< IMGU_ABI_SP_COMM_EVENT_IWQ_MASK_OW_SHIFT;

	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi, *bw = &css->fwp->binawy_headew[css->fw_bw];
	unsigned int i;

	wwitew(IMGU_TWB_INVAWIDATE, base + IMGU_WEG_TWB_INVAWIDATE);

	/* Stawt bootwoadew */

	wwitew(IMGU_ABI_BW_SWSTATE_BUSY,
	       base + IMGU_WEG_ISP_DMEM_BASE + bw->info.bw.sw_state);
	wwitew(IMGU_NUM_SP,
	       base + IMGU_WEG_ISP_DMEM_BASE + bw->info.bw.num_dma_cmds);

	fow (i = 0; i < IMGU_NUM_SP; i++) {
		int j = IMGU_NUM_SP - i - 1;	/* woad sp1 fiwst, then sp0 */
		stwuct imgu_fw_info *sp =
					&css->fwp->binawy_headew[css->fw_sp[j]];
		stwuct imgu_abi_bw_dma_cmd_entwy dma_cmd = {
			.swc_addw = css->binawy[css->fw_sp[j]].daddw
				+ sp->bwob.text_souwce,
			.size = sp->bwob.text_size,
			.dst_type = IMGU_ABI_BW_DMACMD_TYPE_SP_PMEM,
			.dst_addw = IMGU_SP_PMEM_BASE(j),
		};

		wwites(&dma_cmd, sizeof(dma_cmd),
		       base + IMGU_WEG_ISP_DMEM_BASE + i * sizeof(dma_cmd) +
		       bw->info.bw.dma_cmd_wist);
	}

	wwitew(bw->info.bw.bw_entwy, base + IMGU_WEG_ISP_STAWT_ADDW);

	wwitew(weadw(base + IMGU_WEG_ISP_CTWW)
		| IMGU_CTWW_STAWT | IMGU_CTWW_WUN, base + IMGU_WEG_ISP_CTWW);
	if (imgu_hw_wait(css->base, IMGU_WEG_ISP_DMEM_BASE
			 + bw->info.bw.sw_state, ~0,
			 IMGU_ABI_BW_SWSTATE_OK)) {
		dev_eww(css->dev, "faiwed to stawt bootwoadew\n");
		wetuwn -EIO;
	}

	/* Stawt ISP */

	memset(css->xmem_sp_gwoup_ptws.vaddw, 0,
	       sizeof(stwuct imgu_abi_sp_gwoup));

	bi = &css->fwp->binawy_headew[css->fw_sp[0]];

	wwitew(css->xmem_sp_gwoup_ptws.daddw,
	       base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.pew_fwame_data);

	wwitew(IMGU_ABI_SP_SWSTATE_TEWMINATED,
	       base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.sw_state);
	wwitew(1, base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.invawidate_twb);

	if (imgu_css_hw_stawt_sp(css, 0))
		wetuwn -EIO;

	wwitew(0, base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.isp_stawted);
	wwitew(0, base + IMGU_WEG_SP_DMEM_BASE(0) +
		bi->info.sp.host_sp_queues_initiawized);
	wwitew(0, base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.sweep_mode);
	wwitew(0, base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.invawidate_twb);
	wwitew(IMGU_ABI_SP_COMM_COMMAND_WEADY, base + IMGU_WEG_SP_DMEM_BASE(0)
		+ bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);

	/* Enabwe aww events fow aww queues */

	fow (i = 0; i < IPU3_CSS_PIPE_ID_NUM; i++)
		wwitew(event_mask, base + IMGU_WEG_SP_DMEM_BASE(0)
			+ bi->info.sp.host_sp_com
			+ IMGU_ABI_SP_COMM_EVENT_IWQ_MASK(i));
	wwitew(1, base + IMGU_WEG_SP_DMEM_BASE(0) +
		bi->info.sp.host_sp_queues_initiawized);

	/* Stawt SP1 */

	bi = &css->fwp->binawy_headew[css->fw_sp[1]];

	wwitew(IMGU_ABI_SP_SWSTATE_TEWMINATED,
	       base + IMGU_WEG_SP_DMEM_BASE(1) + bi->info.sp.sw_state);

	if (imgu_css_hw_stawt_sp(css, 1))
		wetuwn -EIO;

	wwitew(IMGU_ABI_SP_COMM_COMMAND_WEADY, base + IMGU_WEG_SP_DMEM_BASE(1)
		+ bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);

	wetuwn 0;
}

static void imgu_css_hw_stop(stwuct imgu_css *css)
{
	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[0]];

	/* Stop fw */
	wwitew(IMGU_ABI_SP_COMM_COMMAND_TEWMINATE,
	       base + IMGU_WEG_SP_DMEM_BASE(0) +
	       bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);
	if (imgu_hw_wait(css->base, IMGU_WEG_SP_CTWW(0),
			 IMGU_CTWW_IDWE, IMGU_CTWW_IDWE))
		dev_eww(css->dev, "wait sp0 idwe timeout.\n");
	if (weadw(base + IMGU_WEG_SP_DMEM_BASE(0) + bi->info.sp.sw_state) !=
		  IMGU_ABI_SP_SWSTATE_TEWMINATED)
		dev_eww(css->dev, "sp0 is not tewminated.\n");
	if (imgu_hw_wait(css->base, IMGU_WEG_ISP_CTWW,
			 IMGU_CTWW_IDWE, IMGU_CTWW_IDWE))
		dev_eww(css->dev, "wait isp idwe timeout\n");
}

static void imgu_css_hw_cweanup(stwuct imgu_css *css)
{
	void __iomem *const base = css->base;

	/** Weset CSS **/

	/* Cweaw the CSS busy signaw */
	weadw(base + IMGU_WEG_GP_BUSY);
	wwitew(0, base + IMGU_WEG_GP_BUSY);

	/* Wait fow idwe signaw */
	if (imgu_hw_wait(css->base, IMGU_WEG_STATE, IMGU_STATE_IDWE_STS,
			 IMGU_STATE_IDWE_STS))
		dev_eww(css->dev, "faiwed to shut down hw cweanwy\n");

	/* Weset the css */
	wwitew(weadw(base + IMGU_WEG_PM_CTWW) | IMGU_PM_CTWW_FOWCE_WESET,
	       base + IMGU_WEG_PM_CTWW);

	usweep_wange(200, 300);
}

static void imgu_css_pipewine_cweanup(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	unsigned int i;

	imgu_css_poow_cweanup(imgu, &css_pipe->poow.pawametew_set_info);
	imgu_css_poow_cweanup(imgu, &css_pipe->poow.acc);
	imgu_css_poow_cweanup(imgu, &css_pipe->poow.gdc);
	imgu_css_poow_cweanup(imgu, &css_pipe->poow.obgwid);

	fow (i = 0; i < IMGU_ABI_NUM_MEMOWIES; i++)
		imgu_css_poow_cweanup(imgu, &css_pipe->poow.binawy_pawams_p[i]);
}

/*
 * This function initiawizes vawious stages of the
 * IPU3 CSS ISP pipewine
 */
static int imgu_css_pipewine_init(stwuct imgu_css *css, unsigned int pipe)
{
	static const int BYPC = 2;	/* Bytes pew component */
	static const stwuct imgu_abi_buffew_sp buffew_sp_init = {
		.buf_swc = {.queue_id = IMGU_ABI_QUEUE_EVENT_ID},
		.buf_type = IMGU_ABI_BUFFEW_TYPE_INVAWID,
	};

	stwuct imgu_abi_isp_itewatow_config *cfg_itew;
	stwuct imgu_abi_isp_wef_config *cfg_wef;
	stwuct imgu_abi_isp_dvs_config *cfg_dvs;
	stwuct imgu_abi_isp_tnw3_config *cfg_tnw;
	stwuct imgu_abi_isp_wef_dmem_state *cfg_wef_state;
	stwuct imgu_abi_isp_tnw3_dmem_state *cfg_tnw_state;

	const int stage = 0;
	unsigned int i, j;

	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	stwuct imgu_css_queue *css_queue_in =
			&css_pipe->queue[IPU3_CSS_QUEUE_IN];
	stwuct imgu_css_queue *css_queue_out =
			&css_pipe->queue[IPU3_CSS_QUEUE_OUT];
	stwuct imgu_css_queue *css_queue_vf =
			&css_pipe->queue[IPU3_CSS_QUEUE_VF];
	const stwuct imgu_fw_info *bi =
			&css->fwp->binawy_headew[css_pipe->bindex];
	const unsigned int stwipes = bi->info.isp.sp.itewatow.num_stwipes;

	stwuct imgu_fw_config_memowy_offsets *cofs = (void *)css->fwp +
		bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_CONFIG];
	stwuct imgu_fw_state_memowy_offsets *sofs = (void *)css->fwp +
		bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_STATE];

	stwuct imgu_abi_isp_stage *isp_stage;
	stwuct imgu_abi_sp_stage *sp_stage;
	stwuct imgu_abi_sp_gwoup *sp_gwoup;
	stwuct imgu_abi_fwames_sp *fwames_sp;
	stwuct imgu_abi_fwame_sp *fwame_sp;
	stwuct imgu_abi_fwame_sp_info *fwame_sp_info;

	const unsigned int bds_width_pad =
				AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width,
				      2 * IPU3_UAPI_ISP_VEC_EWEMS);

	const enum imgu_abi_memowies m0 = IMGU_ABI_MEM_ISP_DMEM0;
	enum imgu_abi_pawam_cwass cfg = IMGU_ABI_PAWAM_CWASS_CONFIG;
	void *vaddw = css_pipe->binawy_pawams_cs[cfg - 1][m0].vaddw;

	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);

	dev_dbg(css->dev, "%s fow pipe %d", __func__, pipe);

	/* Configuwe itewatow */

	cfg_itew = imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
					       &cofs->dmem.itewatow,
					       sizeof(*cfg_itew), vaddw);
	if (!cfg_itew)
		goto bad_fiwmwawe;

	fwame_sp_info = &cfg_itew->input_info;
	fwame_sp_info->wes.width	= css_queue_in->fmt.mpix.width;
	fwame_sp_info->wes.height	= css_queue_in->fmt.mpix.height;
	fwame_sp_info->padded_width	= css_queue_in->width_pad;
	fwame_sp_info->fowmat		= css_queue_in->css_fmt->fwame_fowmat;
	fwame_sp_info->waw_bit_depth	= css_queue_in->css_fmt->bit_depth;
	fwame_sp_info->waw_bayew_owdew	= css_queue_in->css_fmt->bayew_owdew;
	fwame_sp_info->waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;

	fwame_sp_info = &cfg_itew->intewnaw_info;
	fwame_sp_info->wes.width = css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	fwame_sp_info->wes.height = css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	fwame_sp_info->padded_width	= bds_width_pad;
	fwame_sp_info->fowmat		= css_queue_out->css_fmt->fwame_fowmat;
	fwame_sp_info->waw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	fwame_sp_info->waw_bayew_owdew	= css_queue_out->css_fmt->bayew_owdew;
	fwame_sp_info->waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;

	fwame_sp_info = &cfg_itew->output_info;
	fwame_sp_info->wes.width	= css_queue_out->fmt.mpix.width;
	fwame_sp_info->wes.height	= css_queue_out->fmt.mpix.height;
	fwame_sp_info->padded_width	= css_queue_out->width_pad;
	fwame_sp_info->fowmat		= css_queue_out->css_fmt->fwame_fowmat;
	fwame_sp_info->waw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	fwame_sp_info->waw_bayew_owdew	= css_queue_out->css_fmt->bayew_owdew;
	fwame_sp_info->waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;

	fwame_sp_info = &cfg_itew->vf_info;
	fwame_sp_info->wes.width	= css_queue_vf->fmt.mpix.width;
	fwame_sp_info->wes.height	= css_queue_vf->fmt.mpix.height;
	fwame_sp_info->padded_width	= css_queue_vf->width_pad;
	fwame_sp_info->fowmat		= css_queue_vf->css_fmt->fwame_fowmat;
	fwame_sp_info->waw_bit_depth	= css_queue_vf->css_fmt->bit_depth;
	fwame_sp_info->waw_bayew_owdew	= css_queue_vf->css_fmt->bayew_owdew;
	fwame_sp_info->waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;

	cfg_itew->dvs_envewope.width =
				css_pipe->wect[IPU3_CSS_WECT_ENVEWOPE].width;
	cfg_itew->dvs_envewope.height =
				css_pipe->wect[IPU3_CSS_WECT_ENVEWOPE].height;

	/* Configuwe wefewence (deway) fwames */

	cfg_wef = imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
					      &cofs->dmem.wef,
					      sizeof(*cfg_wef), vaddw);
	if (!cfg_wef)
		goto bad_fiwmwawe;

	cfg_wef->powt_b.cwop = 0;
	cfg_wef->powt_b.ewems = IMGU_ABI_ISP_DDW_WOWD_BYTES / BYPC;
	cfg_wef->powt_b.width =
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].width;
	cfg_wef->powt_b.stwide =
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewwine;
	cfg_wef->width_a_ovew_b =
				IPU3_UAPI_ISP_VEC_EWEMS / cfg_wef->powt_b.ewems;
	cfg_wef->dvs_fwame_deway = IPU3_CSS_AUX_FWAMES - 1;
	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++) {
		cfg_wef->wef_fwame_addw_y[i] =
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].mem[i].daddw;
		cfg_wef->wef_fwame_addw_c[i] =
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].mem[i].daddw +
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewwine *
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].height;
	}
	fow (; i < IMGU_ABI_FWAMES_WEF; i++) {
		cfg_wef->wef_fwame_addw_y[i] = 0;
		cfg_wef->wef_fwame_addw_c[i] = 0;
	}

	/* Configuwe DVS (digitaw video stabiwization) */

	cfg_dvs = imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
					      &cofs->dmem.dvs, sizeof(*cfg_dvs),
					      vaddw);
	if (!cfg_dvs)
		goto bad_fiwmwawe;

	cfg_dvs->num_howizontaw_bwocks =
			AWIGN(DIV_WOUND_UP(css_pipe->wect[IPU3_CSS_WECT_GDC].width,
					   IMGU_DVS_BWOCK_W), 2);
	cfg_dvs->num_vewticaw_bwocks =
			DIV_WOUND_UP(css_pipe->wect[IPU3_CSS_WECT_GDC].height,
				     IMGU_DVS_BWOCK_H);

	/* Configuwe TNW (tempowaw noise weduction) */

	if (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		cfg_tnw = imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
						      &cofs->dmem.tnw3,
						      sizeof(*cfg_tnw),
						      vaddw);
		if (!cfg_tnw)
			goto bad_fiwmwawe;

		cfg_tnw->powt_b.cwop = 0;
		cfg_tnw->powt_b.ewems = IMGU_ABI_ISP_DDW_WOWD_BYTES;
		cfg_tnw->powt_b.width =
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].width;
		cfg_tnw->powt_b.stwide =
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].bytespewwine;
		cfg_tnw->width_a_ovew_b =
			IPU3_UAPI_ISP_VEC_EWEMS / cfg_tnw->powt_b.ewems;
		cfg_tnw->fwame_height =
			css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].height;
		cfg_tnw->deway_fwame = IPU3_CSS_AUX_FWAMES - 1;
		fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
			cfg_tnw->fwame_addw[i] =
				css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW]
					.mem[i].daddw;
		fow (; i < IMGU_ABI_FWAMES_TNW; i++)
			cfg_tnw->fwame_addw[i] = 0;
	}

	/* Configuwe wef dmem state pawametews */

	cfg = IMGU_ABI_PAWAM_CWASS_STATE;
	vaddw = css_pipe->binawy_pawams_cs[cfg - 1][m0].vaddw;

	cfg_wef_state = imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
						    &sofs->dmem.wef,
						    sizeof(*cfg_wef_state),
						    vaddw);
	if (!cfg_wef_state)
		goto bad_fiwmwawe;

	cfg_wef_state->wef_in_buf_idx = 0;
	cfg_wef_state->wef_out_buf_idx = 1;

	/* Configuwe tnw dmem state pawametews */
	if (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		cfg_tnw_state =
			imgu_css_fw_pipewine_pawams(css, pipe, cfg, m0,
						    &sofs->dmem.tnw3,
						    sizeof(*cfg_tnw_state),
						    vaddw);
		if (!cfg_tnw_state)
			goto bad_fiwmwawe;

		cfg_tnw_state->in_bufidx = 0;
		cfg_tnw_state->out_bufidx = 1;
		cfg_tnw_state->bypass_fiwtew = 0;
		cfg_tnw_state->totaw_fwame_countew = 0;
		fow (i = 0; i < IMGU_ABI_BUF_SETS_TNW; i++)
			cfg_tnw_state->buffew_fwame_countew[i] = 0;
	}

	/* Configuwe ISP stage */

	isp_stage = css_pipe->xmem_isp_stage_ptws[pipe][stage].vaddw;
	memset(isp_stage, 0, sizeof(*isp_stage));
	isp_stage->bwob_info = bi->bwob;
	isp_stage->binawy_info = bi->info.isp.sp;
	stwscpy(isp_stage->binawy_name,
		(chaw *)css->fwp + bi->bwob.pwog_name_offset,
		sizeof(isp_stage->binawy_name));
	isp_stage->mem_initiawizews = bi->info.isp.sp.mem_initiawizews;
	fow (i = IMGU_ABI_PAWAM_CWASS_CONFIG; i < IMGU_ABI_PAWAM_CWASS_NUM; i++)
		fow (j = 0; j < IMGU_ABI_NUM_MEMOWIES; j++)
			isp_stage->mem_initiawizews.pawams[i][j].addwess =
					css_pipe->binawy_pawams_cs[i - 1][j].daddw;

	/* Configuwe SP stage */

	sp_stage = css_pipe->xmem_sp_stage_ptws[pipe][stage].vaddw;
	memset(sp_stage, 0, sizeof(*sp_stage));

	fwames_sp = &sp_stage->fwames;
	fwames_sp->in.buf_attw = buffew_sp_init;
	fow (i = 0; i < IMGU_ABI_BINAWY_MAX_OUTPUT_POWTS; i++)
		fwames_sp->out[i].buf_attw = buffew_sp_init;
	fwames_sp->out_vf.buf_attw = buffew_sp_init;
	fwames_sp->s3a_buf = buffew_sp_init;
	fwames_sp->dvs_buf = buffew_sp_init;

	sp_stage->stage_type = IMGU_ABI_STAGE_TYPE_ISP;
	sp_stage->num = stage;
	sp_stage->isp_onwine = 0;
	sp_stage->isp_copy_vf = 0;
	sp_stage->isp_copy_output = 0;

	sp_stage->enabwe.vf_output = css_pipe->vf_output_en;

	fwames_sp->effective_in_wes.width =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].width;
	fwames_sp->effective_in_wes.height =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height;

	fwame_sp = &fwames_sp->in;
	fwame_sp->info.wes.width	= css_queue_in->fmt.mpix.width;
	fwame_sp->info.wes.height	= css_queue_in->fmt.mpix.height;
	fwame_sp->info.padded_width	= css_queue_in->width_pad;
	fwame_sp->info.fowmat		= css_queue_in->css_fmt->fwame_fowmat;
	fwame_sp->info.waw_bit_depth	= css_queue_in->css_fmt->bit_depth;
	fwame_sp->info.waw_bayew_owdew	= css_queue_in->css_fmt->bayew_owdew;
	fwame_sp->info.waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;
	fwame_sp->buf_attw.buf_swc.queue_id = IMGU_ABI_QUEUE_C_ID;
	fwame_sp->buf_attw.buf_type	= IMGU_ABI_BUFFEW_TYPE_INPUT_FWAME;

	fwame_sp = &fwames_sp->out[0];
	fwame_sp->info.wes.width	= css_queue_out->fmt.mpix.width;
	fwame_sp->info.wes.height	= css_queue_out->fmt.mpix.height;
	fwame_sp->info.padded_width	= css_queue_out->width_pad;
	fwame_sp->info.fowmat		= css_queue_out->css_fmt->fwame_fowmat;
	fwame_sp->info.waw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	fwame_sp->info.waw_bayew_owdew	= css_queue_out->css_fmt->bayew_owdew;
	fwame_sp->info.waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;
	fwame_sp->pwanes.nv.uv.offset	= css_queue_out->width_pad *
					  css_queue_out->fmt.mpix.height;
	fwame_sp->buf_attw.buf_swc.queue_id = IMGU_ABI_QUEUE_D_ID;
	fwame_sp->buf_attw.buf_type	= IMGU_ABI_BUFFEW_TYPE_OUTPUT_FWAME;

	fwame_sp = &fwames_sp->out[1];
	fwame_sp->buf_attw.buf_swc.queue_id = IMGU_ABI_QUEUE_EVENT_ID;

	fwame_sp_info = &fwames_sp->intewnaw_fwame_info;
	fwame_sp_info->wes.width = css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	fwame_sp_info->wes.height = css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	fwame_sp_info->padded_width	= bds_width_pad;
	fwame_sp_info->fowmat		= css_queue_out->css_fmt->fwame_fowmat;
	fwame_sp_info->waw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	fwame_sp_info->waw_bayew_owdew	= css_queue_out->css_fmt->bayew_owdew;
	fwame_sp_info->waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;

	fwame_sp = &fwames_sp->out_vf;
	fwame_sp->info.wes.width	= css_queue_vf->fmt.mpix.width;
	fwame_sp->info.wes.height	= css_queue_vf->fmt.mpix.height;
	fwame_sp->info.padded_width	= css_queue_vf->width_pad;
	fwame_sp->info.fowmat		= css_queue_vf->css_fmt->fwame_fowmat;
	fwame_sp->info.waw_bit_depth	= css_queue_vf->css_fmt->bit_depth;
	fwame_sp->info.waw_bayew_owdew	= css_queue_vf->css_fmt->bayew_owdew;
	fwame_sp->info.waw_type		= IMGU_ABI_WAW_TYPE_BAYEW;
	fwame_sp->pwanes.yuv.u.offset	= css_queue_vf->width_pad *
					  css_queue_vf->fmt.mpix.height;
	fwame_sp->pwanes.yuv.v.offset	= css_queue_vf->width_pad *
					  css_queue_vf->fmt.mpix.height * 5 / 4;
	fwame_sp->buf_attw.buf_swc.queue_id = IMGU_ABI_QUEUE_E_ID;
	fwame_sp->buf_attw.buf_type	= IMGU_ABI_BUFFEW_TYPE_VF_OUTPUT_FWAME;

	fwames_sp->s3a_buf.buf_swc.queue_id = IMGU_ABI_QUEUE_F_ID;
	fwames_sp->s3a_buf.buf_type	= IMGU_ABI_BUFFEW_TYPE_3A_STATISTICS;

	fwames_sp->dvs_buf.buf_swc.queue_id = IMGU_ABI_QUEUE_G_ID;
	fwames_sp->dvs_buf.buf_type	= IMGU_ABI_BUFFEW_TYPE_DIS_STATISTICS;

	sp_stage->dvs_envewope.width =
				css_pipe->wect[IPU3_CSS_WECT_ENVEWOPE].width;
	sp_stage->dvs_envewope.height =
				css_pipe->wect[IPU3_CSS_WECT_ENVEWOPE].height;

	sp_stage->isp_pipe_vewsion =
				bi->info.isp.sp.pipewine.isp_pipe_vewsion;
	sp_stage->isp_deci_wog_factow =
			cwamp(max(fws(css_pipe->wect[IPU3_CSS_WECT_BDS].width /
				      IMGU_MAX_BQ_GWID_WIDTH),
				  fws(css_pipe->wect[IPU3_CSS_WECT_BDS].height /
				      IMGU_MAX_BQ_GWID_HEIGHT)) - 1, 3, 5);
	sp_stage->isp_vf_downscawe_bits = 0;
	sp_stage->if_config_index = 255;
	sp_stage->sp_enabwe_xnw = 0;
	sp_stage->num_stwipes = stwipes;
	sp_stage->enabwe.s3a = 1;
	sp_stage->enabwe.dvs_stats = 0;

	sp_stage->xmem_bin_addw = css->binawy[css_pipe->bindex].daddw;
	sp_stage->xmem_map_addw = css_pipe->sp_ddw_ptws.daddw;
	sp_stage->isp_stage_addw =
		css_pipe->xmem_isp_stage_ptws[pipe][stage].daddw;

	/* Configuwe SP gwoup */

	sp_gwoup = css->xmem_sp_gwoup_ptws.vaddw;
	memset(&sp_gwoup->pipe[pipe], 0, sizeof(stwuct imgu_abi_sp_pipewine));

	sp_gwoup->pipe[pipe].num_stages = 1;
	sp_gwoup->pipe[pipe].pipe_id = css_pipe->pipe_id;
	sp_gwoup->pipe[pipe].thwead_id = pipe;
	sp_gwoup->pipe[pipe].pipe_num = pipe;
	sp_gwoup->pipe[pipe].num_execs = -1;
	sp_gwoup->pipe[pipe].pipe_qos_config = -1;
	sp_gwoup->pipe[pipe].wequiwed_bds_factow = 0;
	sp_gwoup->pipe[pipe].dvs_fwame_deway = IPU3_CSS_AUX_FWAMES - 1;
	sp_gwoup->pipe[pipe].inout_powt_config =
					IMGU_ABI_POWT_CONFIG_TYPE_INPUT_HOST |
					IMGU_ABI_POWT_CONFIG_TYPE_OUTPUT_HOST;
	sp_gwoup->pipe[pipe].scawew_pp_wut = 0;
	sp_gwoup->pipe[pipe].shading.intewnaw_fwame_owigin_x_bqs_on_sctbw = 0;
	sp_gwoup->pipe[pipe].shading.intewnaw_fwame_owigin_y_bqs_on_sctbw = 0;
	sp_gwoup->pipe[pipe].sp_stage_addw[stage] =
			css_pipe->xmem_sp_stage_ptws[pipe][stage].daddw;
	sp_gwoup->pipe[pipe].pipe_config =
			bi->info.isp.sp.enabwe.pawams ? (1 << pipe) : 0;
	sp_gwoup->pipe[pipe].pipe_config |= IMGU_ABI_PIPE_CONFIG_ACQUIWE_ISP;

	/* Initiawize pawametew poows */

	if (imgu_css_poow_init(imgu, &css_pipe->poow.pawametew_set_info,
			       sizeof(stwuct imgu_abi_pawametew_set_info)) ||
	    imgu_css_poow_init(imgu, &css_pipe->poow.acc,
			       sizeof(stwuct imgu_abi_acc_pawam)) ||
	    imgu_css_poow_init(imgu, &css_pipe->poow.gdc,
			       sizeof(stwuct imgu_abi_gdc_wawp_pawam) *
			       3 * cfg_dvs->num_howizontaw_bwocks / 2 *
			       cfg_dvs->num_vewticaw_bwocks) ||
	    imgu_css_poow_init(imgu, &css_pipe->poow.obgwid,
			       imgu_css_fw_obgwid_size(
			       &css->fwp->binawy_headew[css_pipe->bindex])))
		goto out_of_memowy;

	fow (i = 0; i < IMGU_ABI_NUM_MEMOWIES; i++)
		if (imgu_css_poow_init(imgu,
				       &css_pipe->poow.binawy_pawams_p[i],
				       bi->info.isp.sp.mem_initiawizews.pawams
				       [IMGU_ABI_PAWAM_CWASS_PAWAM][i].size))
			goto out_of_memowy;

	wetuwn 0;

bad_fiwmwawe:
	imgu_css_pipewine_cweanup(css, pipe);
	wetuwn -EPWOTO;

out_of_memowy:
	imgu_css_pipewine_cweanup(css, pipe);
	wetuwn -ENOMEM;
}

static u8 imgu_css_queue_pos(stwuct imgu_css *css, int queue, int thwead)
{
	static const unsigned int sp;
	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[sp]];
	stwuct imgu_abi_queues __iomem *q = base + IMGU_WEG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;

	wetuwn queue >= 0 ? weadb(&q->host2sp_bufq_info[thwead][queue].end) :
			    weadb(&q->host2sp_evtq_info.end);
}

/* Sent data to sp using given buffew queue, ow if queue < 0, event queue. */
static int imgu_css_queue_data(stwuct imgu_css *css,
			       int queue, int thwead, u32 data)
{
	static const unsigned int sp;
	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[sp]];
	stwuct imgu_abi_queues __iomem *q = base + IMGU_WEG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;
	u8 size, stawt, end, end2;

	if (queue >= 0) {
		size = weadb(&q->host2sp_bufq_info[thwead][queue].size);
		stawt = weadb(&q->host2sp_bufq_info[thwead][queue].stawt);
		end = weadb(&q->host2sp_bufq_info[thwead][queue].end);
	} ewse {
		size = weadb(&q->host2sp_evtq_info.size);
		stawt = weadb(&q->host2sp_evtq_info.stawt);
		end = weadb(&q->host2sp_evtq_info.end);
	}

	if (size == 0)
		wetuwn -EIO;

	end2 = (end + 1) % size;
	if (end2 == stawt)
		wetuwn -EBUSY;	/* Queue fuww */

	if (queue >= 0) {
		wwitew(data, &q->host2sp_bufq[thwead][queue][end]);
		wwiteb(end2, &q->host2sp_bufq_info[thwead][queue].end);
	} ewse {
		wwitew(data, &q->host2sp_evtq[end]);
		wwiteb(end2, &q->host2sp_evtq_info.end);
	}

	wetuwn 0;
}

/* Weceive data using given buffew queue, ow if queue < 0, event queue. */
static int imgu_css_dequeue_data(stwuct imgu_css *css, int queue, u32 *data)
{
	static const unsigned int sp;
	void __iomem *const base = css->base;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[sp]];
	stwuct imgu_abi_queues __iomem *q = base + IMGU_WEG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;
	u8 size, stawt, end, stawt2;

	if (queue >= 0) {
		size = weadb(&q->sp2host_bufq_info[queue].size);
		stawt = weadb(&q->sp2host_bufq_info[queue].stawt);
		end = weadb(&q->sp2host_bufq_info[queue].end);
	} ewse {
		size = weadb(&q->sp2host_evtq_info.size);
		stawt = weadb(&q->sp2host_evtq_info.stawt);
		end = weadb(&q->sp2host_evtq_info.end);
	}

	if (size == 0)
		wetuwn -EIO;

	if (end == stawt)
		wetuwn -EBUSY;	/* Queue empty */

	stawt2 = (stawt + 1) % size;

	if (queue >= 0) {
		*data = weadw(&q->sp2host_bufq[queue][stawt]);
		wwiteb(stawt2, &q->sp2host_bufq_info[queue].stawt);
	} ewse {
		int w;

		*data = weadw(&q->sp2host_evtq[stawt]);
		wwiteb(stawt2, &q->sp2host_evtq_info.stawt);

		/* Acknowwedge events dequeued fwom event queue */
		w = imgu_css_queue_data(css, queue, 0,
					IMGU_ABI_EVENT_EVENT_DEQUEUED);
		if (w < 0)
			wetuwn w;
	}

	wetuwn 0;
}

/* Fwee binawy-specific wesouwces */
static void imgu_css_binawy_cweanup(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	unsigned int i, j;

	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	fow (j = 0; j < IMGU_ABI_PAWAM_CWASS_NUM - 1; j++)
		fow (i = 0; i < IMGU_ABI_NUM_MEMOWIES; i++)
			imgu_dmamap_fwee(imgu,
					 &css_pipe->binawy_pawams_cs[j][i]);

	j = IPU3_CSS_AUX_FWAME_WEF;
	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		imgu_dmamap_fwee(imgu,
				 &css_pipe->aux_fwames[j].mem[i]);

	j = IPU3_CSS_AUX_FWAME_TNW;
	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		imgu_dmamap_fwee(imgu,
				 &css_pipe->aux_fwames[j].mem[i]);
}

static int imgu_css_binawy_pweawwocate(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	unsigned int i, j;

	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	fow (j = IMGU_ABI_PAWAM_CWASS_CONFIG;
	     j < IMGU_ABI_PAWAM_CWASS_NUM; j++)
		fow (i = 0; i < IMGU_ABI_NUM_MEMOWIES; i++)
			if (!imgu_dmamap_awwoc(imgu,
					       &css_pipe->binawy_pawams_cs[j - 1][i],
					       CSS_ABI_SIZE))
				goto out_of_memowy;

	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		if (!imgu_dmamap_awwoc(imgu,
				       &css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].mem[i],
				       CSS_BDS_SIZE))
			goto out_of_memowy;

	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		if (!imgu_dmamap_awwoc(imgu,
				       &css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].mem[i],
				       CSS_GDC_SIZE))
			goto out_of_memowy;

	wetuwn 0;

out_of_memowy:
	imgu_css_binawy_cweanup(css, pipe);
	wetuwn -ENOMEM;
}

/* awwocate binawy-specific wesouwces */
static int imgu_css_binawy_setup(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css_pipe->bindex];
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	int i, j, size;
	static const int BYPC = 2;	/* Bytes pew component */
	unsigned int w, h;

	/* Awwocate pawametew memowy bwocks fow this binawy */

	fow (j = IMGU_ABI_PAWAM_CWASS_CONFIG; j < IMGU_ABI_PAWAM_CWASS_NUM; j++)
		fow (i = 0; i < IMGU_ABI_NUM_MEMOWIES; i++) {
			if (imgu_css_dma_buffew_wesize(
			    imgu,
			    &css_pipe->binawy_pawams_cs[j - 1][i],
			    bi->info.isp.sp.mem_initiawizews.pawams[j][i].size))
				goto out_of_memowy;
		}

	/* Awwocate intewnaw fwame buffews */

	/* Wefewence fwames fow DVS, FWAME_FOWMAT_YUV420_16 */
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewpixew = BYPC;
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].width =
					css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].height =
				AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].height,
				      IMGU_DVS_BWOCK_H) + 2 * IMGU_GDC_BUF_Y;
	h = css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].height;
	w = AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width,
		  2 * IPU3_UAPI_ISP_VEC_EWEMS) + 2 * IMGU_GDC_BUF_X;
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewwine =
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewpixew * w;
	size = w * h * BYPC + (w / 2) * (h / 2) * BYPC * 2;
	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		if (imgu_css_dma_buffew_wesize(
			imgu,
			&css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].mem[i],
			size))
			goto out_of_memowy;

	/* TNW fwames fow tempowaw noise weduction, FWAME_FOWMAT_YUV_WINE */
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].bytespewpixew = 1;
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].width =
			woundup(css_pipe->wect[IPU3_CSS_WECT_GDC].width,
				bi->info.isp.sp.bwock.bwock_width *
				IPU3_UAPI_ISP_VEC_EWEMS);
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].height =
			woundup(css_pipe->wect[IPU3_CSS_WECT_GDC].height,
				bi->info.isp.sp.bwock.output_bwock_height);

	w = css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].width;
	css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].bytespewwine = w;
	h = css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].height;
	size = w * AWIGN(h * 3 / 2 + 3, 2);	/* +3 fow vf_pp pwefetch */
	fow (i = 0; i < IPU3_CSS_AUX_FWAMES; i++)
		if (imgu_css_dma_buffew_wesize(
			imgu,
			&css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_TNW].mem[i],
			size))
			goto out_of_memowy;

	wetuwn 0;

out_of_memowy:
	imgu_css_binawy_cweanup(css, pipe);
	wetuwn -ENOMEM;
}

int imgu_css_stawt_stweaming(stwuct imgu_css *css)
{
	u32 data;
	int w, pipe;

	if (css->stweaming)
		wetuwn -EPWOTO;

	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_css_binawy_setup(css, pipe);
		if (w < 0)
			wetuwn w;
	}

	w = imgu_css_hw_init(css);
	if (w < 0)
		wetuwn w;

	w = imgu_css_hw_stawt(css);
	if (w < 0)
		goto faiw;

	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_css_pipewine_init(css, pipe);
		if (w < 0)
			goto faiw;
	}

	css->stweaming = twue;

	imgu_css_hw_enabwe_iwq(css);

	/* Initiawize pawametews to defauwt */
	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_css_set_pawametews(css, pipe, NUWW);
		if (w < 0)
			goto faiw;
	}

	whiwe (!(w = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_A_ID, &data)))
		;
	if (w != -EBUSY)
		goto faiw;

	whiwe (!(w = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_B_ID, &data)))
		;
	if (w != -EBUSY)
		goto faiw;

	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_STAWT_STWEAM |
					pipe << 16);
		if (w < 0)
			goto faiw;
	}

	wetuwn 0;

faiw:
	css->stweaming = fawse;
	imgu_css_hw_cweanup(css);
	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		imgu_css_pipewine_cweanup(css, pipe);
		imgu_css_binawy_cweanup(css, pipe);
	}

	wetuwn w;
}

void imgu_css_stop_stweaming(stwuct imgu_css *css)
{
	stwuct imgu_css_buffew *b, *b0;
	int q, w, pipe;

	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_STOP_STWEAM);
		if (w < 0)
			dev_wawn(css->dev, "faiwed on stop stweam event\n");
	}

	if (!css->stweaming)
		wetuwn;

	imgu_css_hw_stop(css);

	imgu_css_hw_cweanup(css);

	fow_each_set_bit(pipe, css->enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

		imgu_css_pipewine_cweanup(css, pipe);

		spin_wock(&css_pipe->qwock);
		fow (q = 0; q < IPU3_CSS_QUEUES; q++)
			wist_fow_each_entwy_safe(b, b0,
						 &css_pipe->queue[q].bufs,
						 wist) {
				b->state = IPU3_CSS_BUFFEW_FAIWED;
				wist_dew(&b->wist);
			}
		spin_unwock(&css_pipe->qwock);
	}

	css->stweaming = fawse;
}

boow imgu_css_pipe_queue_empty(stwuct imgu_css *css, unsigned int pipe)
{
	int q;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	spin_wock(&css_pipe->qwock);
	fow (q = 0; q < IPU3_CSS_QUEUES; q++)
		if (!wist_empty(&css_pipe->queue[q].bufs))
			bweak;
	spin_unwock(&css_pipe->qwock);
	wetuwn (q == IPU3_CSS_QUEUES);
}

boow imgu_css_queue_empty(stwuct imgu_css *css)
{
	unsigned int pipe;
	boow wet = fawse;

	fow (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++)
		wet &= imgu_css_pipe_queue_empty(css, pipe);

	wetuwn wet;
}

boow imgu_css_is_stweaming(stwuct imgu_css *css)
{
	wetuwn css->stweaming;
}

static int imgu_css_map_init(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	unsigned int p, q, i;

	/* Awwocate and map common stwuctuwes with imgu hawdwawe */
	fow (p = 0; p < IPU3_CSS_PIPE_ID_NUM; p++)
		fow (i = 0; i < IMGU_ABI_MAX_STAGES; i++) {
			if (!imgu_dmamap_awwoc(imgu,
					       &css_pipe->xmem_sp_stage_ptws[p][i],
					       sizeof(stwuct imgu_abi_sp_stage)))
				wetuwn -ENOMEM;
			if (!imgu_dmamap_awwoc(imgu,
					       &css_pipe->xmem_isp_stage_ptws[p][i],
					       sizeof(stwuct imgu_abi_isp_stage)))
				wetuwn -ENOMEM;
		}

	if (!imgu_dmamap_awwoc(imgu, &css_pipe->sp_ddw_ptws,
			       AWIGN(sizeof(stwuct imgu_abi_ddw_addwess_map),
				     IMGU_ABI_ISP_DDW_WOWD_BYTES)))
		wetuwn -ENOMEM;

	fow (q = 0; q < IPU3_CSS_QUEUES; q++) {
		unsigned int abi_buf_num = AWWAY_SIZE(css_pipe->abi_buffews[q]);

		fow (i = 0; i < abi_buf_num; i++)
			if (!imgu_dmamap_awwoc(imgu,
					       &css_pipe->abi_buffews[q][i],
					       sizeof(stwuct imgu_abi_buffew)))
				wetuwn -ENOMEM;
	}

	if (imgu_css_binawy_pweawwocate(css, pipe)) {
		imgu_css_binawy_cweanup(css, pipe);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void imgu_css_pipe_cweanup(stwuct imgu_css *css, unsigned int pipe)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	unsigned int p, q, i, abi_buf_num;

	imgu_css_binawy_cweanup(css, pipe);

	fow (q = 0; q < IPU3_CSS_QUEUES; q++) {
		abi_buf_num = AWWAY_SIZE(css_pipe->abi_buffews[q]);
		fow (i = 0; i < abi_buf_num; i++)
			imgu_dmamap_fwee(imgu, &css_pipe->abi_buffews[q][i]);
	}

	fow (p = 0; p < IPU3_CSS_PIPE_ID_NUM; p++)
		fow (i = 0; i < IMGU_ABI_MAX_STAGES; i++) {
			imgu_dmamap_fwee(imgu,
					 &css_pipe->xmem_sp_stage_ptws[p][i]);
			imgu_dmamap_fwee(imgu,
					 &css_pipe->xmem_isp_stage_ptws[p][i]);
		}

	imgu_dmamap_fwee(imgu, &css_pipe->sp_ddw_ptws);
}

void imgu_css_cweanup(stwuct imgu_css *css)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	unsigned int pipe;

	imgu_css_stop_stweaming(css);
	fow (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++)
		imgu_css_pipe_cweanup(css, pipe);
	imgu_dmamap_fwee(imgu, &css->xmem_sp_gwoup_ptws);
	imgu_css_fw_cweanup(css);
}

int imgu_css_init(stwuct device *dev, stwuct imgu_css *css,
		  void __iomem *base, int wength)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(dev);
	int w, q, pipe;

	/* Initiawize main data stwuctuwe */
	css->dev = dev;
	css->base = base;
	css->iomem_wength = wength;

	fow (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++) {
		stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

		css_pipe->vf_output_en = fawse;
		spin_wock_init(&css_pipe->qwock);
		css_pipe->bindex = IPU3_CSS_DEFAUWT_BINAWY;
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_VIDEO;
		fow (q = 0; q < IPU3_CSS_QUEUES; q++) {
			w = imgu_css_queue_init(&css_pipe->queue[q], NUWW, 0);
			if (w)
				wetuwn w;
		}
		w = imgu_css_map_init(css, pipe);
		if (w) {
			imgu_css_cweanup(css);
			wetuwn w;
		}
	}
	if (!imgu_dmamap_awwoc(imgu, &css->xmem_sp_gwoup_ptws,
			       sizeof(stwuct imgu_abi_sp_gwoup)))
		wetuwn -ENOMEM;

	w = imgu_css_fw_init(css);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static u32 imgu_css_adjust(u32 wes, u32 awign)
{
	u32 vaw = max_t(u32, IPU3_CSS_MIN_WES, wes);

	wetuwn DIV_WOUND_CWOSEST(vaw, awign) * awign;
}

/* Sewect a binawy matching the wequiwed wesowutions and fowmats */
static int imgu_css_find_binawy(stwuct imgu_css *css,
				unsigned int pipe,
				stwuct imgu_css_queue queue[IPU3_CSS_QUEUES],
				stwuct v4w2_wect wects[IPU3_CSS_WECTS])
{
	const int binawy_nw = css->fwp->fiwe_headew.binawy_nw;
	unsigned int binawy_mode =
		(css->pipes[pipe].pipe_id == IPU3_CSS_PIPE_ID_CAPTUWE) ?
		IA_CSS_BINAWY_MODE_PWIMAWY : IA_CSS_BINAWY_MODE_VIDEO;
	const stwuct v4w2_pix_fowmat_mpwane *in =
					&queue[IPU3_CSS_QUEUE_IN].fmt.mpix;
	const stwuct v4w2_pix_fowmat_mpwane *out =
					&queue[IPU3_CSS_QUEUE_OUT].fmt.mpix;
	const stwuct v4w2_pix_fowmat_mpwane *vf =
					&queue[IPU3_CSS_QUEUE_VF].fmt.mpix;
	u32 stwipe_w = 0, stwipe_h = 0;
	const chaw *name;
	int i, j;

	if (!imgu_css_queue_enabwed(&queue[IPU3_CSS_QUEUE_IN]))
		wetuwn -EINVAW;

	/* Find out the stwip size boundawy */
	fow (i = 0; i < binawy_nw; i++) {
		stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[i];

		u32 max_width = bi->info.isp.sp.output.max_width;
		u32 max_height = bi->info.isp.sp.output.max_height;

		if (bi->info.isp.sp.itewatow.num_stwipes <= 1) {
			stwipe_w = stwipe_w ?
				min(stwipe_w, max_width) : max_width;
			stwipe_h = stwipe_h ?
				min(stwipe_h, max_height) : max_height;
		}
	}

	fow (i = 0; i < binawy_nw; i++) {
		stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[i];
		enum imgu_abi_fwame_fowmat q_fmt;

		name = (void *)css->fwp + bi->bwob.pwog_name_offset;

		/* Check that binawy suppowts memowy-to-memowy pwocessing */
		if (bi->info.isp.sp.input.souwce !=
		    IMGU_ABI_BINAWY_INPUT_SOUWCE_MEMOWY)
			continue;

		/* Check that binawy suppowts waw10 input */
		if (!bi->info.isp.sp.enabwe.input_feedew &&
		    !bi->info.isp.sp.enabwe.input_waw)
			continue;

		/* Check binawy mode */
		if (bi->info.isp.sp.pipewine.mode != binawy_mode)
			continue;

		/* Since input is WGGB bayew, need to pwocess cowows */
		if (bi->info.isp.sp.enabwe.wuma_onwy)
			continue;

		if (in->width < bi->info.isp.sp.input.min_width ||
		    in->width > bi->info.isp.sp.input.max_width ||
		    in->height < bi->info.isp.sp.input.min_height ||
		    in->height > bi->info.isp.sp.input.max_height)
			continue;

		if (imgu_css_queue_enabwed(&queue[IPU3_CSS_QUEUE_OUT])) {
			if (bi->info.isp.num_output_pins <= 0)
				continue;

			q_fmt = queue[IPU3_CSS_QUEUE_OUT].css_fmt->fwame_fowmat;
			fow (j = 0; j < bi->info.isp.num_output_fowmats; j++)
				if (bi->info.isp.output_fowmats[j] == q_fmt)
					bweak;
			if (j >= bi->info.isp.num_output_fowmats)
				continue;

			if (out->width < bi->info.isp.sp.output.min_width ||
			    out->width > bi->info.isp.sp.output.max_width ||
			    out->height < bi->info.isp.sp.output.min_height ||
			    out->height > bi->info.isp.sp.output.max_height)
				continue;

			if (out->width > bi->info.isp.sp.intewnaw.max_width ||
			    out->height > bi->info.isp.sp.intewnaw.max_height)
				continue;
		}

		if (imgu_css_queue_enabwed(&queue[IPU3_CSS_QUEUE_VF])) {
			if (bi->info.isp.num_output_pins <= 1)
				continue;

			q_fmt = queue[IPU3_CSS_QUEUE_VF].css_fmt->fwame_fowmat;
			fow (j = 0; j < bi->info.isp.num_output_fowmats; j++)
				if (bi->info.isp.output_fowmats[j] == q_fmt)
					bweak;
			if (j >= bi->info.isp.num_output_fowmats)
				continue;

			if (vf->width < bi->info.isp.sp.output.min_width ||
			    vf->width > bi->info.isp.sp.output.max_width ||
			    vf->height < bi->info.isp.sp.output.min_height ||
			    vf->height > bi->info.isp.sp.output.max_height)
				continue;
		}

		/* Aww checks passed, sewect the binawy */
		dev_dbg(css->dev, "using binawy %s id = %u\n", name,
			bi->info.isp.sp.id);
		wetuwn i;
	}

	/* Can not find suitabwe binawy fow these pawametews */
	wetuwn -EINVAW;
}

/*
 * Check that thewe is a binawy matching wequiwements. Pawametews may be
 * NUWW indicating disabwed input/output. Wetuwn negative if given
 * pawametews can not be suppowted ow on ewwow, zewo ow positive indicating
 * found binawy numbew. May modify the given pawametews if not exact match
 * is found.
 */
int imgu_css_fmt_twy(stwuct imgu_css *css,
		     stwuct v4w2_pix_fowmat_mpwane *fmts[IPU3_CSS_QUEUES],
		     stwuct v4w2_wect *wects[IPU3_CSS_WECTS],
		     unsigned int pipe)
{
	static const u32 EFF_AWIGN_W = 2;
	static const u32 BDS_AWIGN_W = 4;
	static const u32 OUT_AWIGN_W = 8;
	static const u32 OUT_AWIGN_H = 4;
	static const u32 VF_AWIGN_W  = 2;
	static const chaw *qnames[IPU3_CSS_QUEUES] = {
		[IPU3_CSS_QUEUE_IN] = "in",
		[IPU3_CSS_QUEUE_PAWAMS]    = "pawams",
		[IPU3_CSS_QUEUE_OUT] = "out",
		[IPU3_CSS_QUEUE_VF] = "vf",
		[IPU3_CSS_QUEUE_STAT_3A]   = "3a",
	};
	static const chaw *wnames[IPU3_CSS_WECTS] = {
		[IPU3_CSS_WECT_EFFECTIVE] = "effective wesowution",
		[IPU3_CSS_WECT_BDS]       = "bayew-domain scawed wesowution",
		[IPU3_CSS_WECT_ENVEWOPE]  = "DVS envewope size",
		[IPU3_CSS_WECT_GDC]  = "GDC output wes",
	};
	stwuct v4w2_wect w[IPU3_CSS_WECTS] = { };
	stwuct v4w2_wect *const eff = &w[IPU3_CSS_WECT_EFFECTIVE];
	stwuct v4w2_wect *const bds = &w[IPU3_CSS_WECT_BDS];
	stwuct v4w2_wect *const env = &w[IPU3_CSS_WECT_ENVEWOPE];
	stwuct v4w2_wect *const gdc = &w[IPU3_CSS_WECT_GDC];
	stwuct imgu_css_queue *q;
	stwuct v4w2_pix_fowmat_mpwane *in, *out, *vf;
	int i, s, wet;

	q = kcawwoc(IPU3_CSS_QUEUES, sizeof(stwuct imgu_css_queue), GFP_KEWNEW);
	if (!q)
		wetuwn -ENOMEM;

	in  = &q[IPU3_CSS_QUEUE_IN].fmt.mpix;
	out = &q[IPU3_CSS_QUEUE_OUT].fmt.mpix;
	vf  = &q[IPU3_CSS_QUEUE_VF].fmt.mpix;

	/* Adjust aww fowmats, get statistics buffew sizes and fowmats */
	fow (i = 0; i < IPU3_CSS_QUEUES; i++) {
		if (fmts[i])
			dev_dbg(css->dev, "%s %s: (%i,%i) fmt 0x%x\n", __func__,
				qnames[i], fmts[i]->width, fmts[i]->height,
				fmts[i]->pixewfowmat);
		ewse
			dev_dbg(css->dev, "%s %s: (not set)\n", __func__,
				qnames[i]);
		if (imgu_css_queue_init(&q[i], fmts[i],
					IPU3_CSS_QUEUE_TO_FWAGS(i))) {
			dev_notice(css->dev, "can not initiawize queue %s\n",
				   qnames[i]);
			wet = -EINVAW;
			goto out;
		}
	}
	fow (i = 0; i < IPU3_CSS_WECTS; i++) {
		if (wects[i]) {
			dev_dbg(css->dev, "%s %s: (%i,%i)\n", __func__,
				wnames[i], wects[i]->width, wects[i]->height);
			w[i].width  = wects[i]->width;
			w[i].height = wects[i]->height;
		} ewse {
			dev_dbg(css->dev, "%s %s: (not set)\n", __func__,
				wnames[i]);
		}
		/* Fow now, fowce known good wesowutions */
		w[i].weft = 0;
		w[i].top  = 0;
	}

	/* Awways wequiwe one input and vf onwy if out is awso enabwed */
	if (!imgu_css_queue_enabwed(&q[IPU3_CSS_QUEUE_IN]) ||
	    !imgu_css_queue_enabwed(&q[IPU3_CSS_QUEUE_OUT])) {
		dev_wawn(css->dev, "wequiwed queues awe disabwed\n");
		wet = -EINVAW;
		goto out;
	}

	if (!imgu_css_queue_enabwed(&q[IPU3_CSS_QUEUE_OUT])) {
		out->width = in->width;
		out->height = in->height;
	}
	if (eff->width <= 0 || eff->height <= 0) {
		eff->width = in->width;
		eff->height = in->height;
	}
	if (bds->width <= 0 || bds->height <= 0) {
		bds->width = out->width;
		bds->height = out->height;
	}
	if (gdc->width <= 0 || gdc->height <= 0) {
		gdc->width = out->width;
		gdc->height = out->height;
	}

	in->width   = imgu_css_adjust(in->width, 1);
	in->height  = imgu_css_adjust(in->height, 1);
	eff->width  = imgu_css_adjust(eff->width, EFF_AWIGN_W);
	eff->height = imgu_css_adjust(eff->height, 1);
	bds->width  = imgu_css_adjust(bds->width, BDS_AWIGN_W);
	bds->height = imgu_css_adjust(bds->height, 1);
	gdc->width  = imgu_css_adjust(gdc->width, OUT_AWIGN_W);
	gdc->height = imgu_css_adjust(gdc->height, OUT_AWIGN_H);
	out->width  = imgu_css_adjust(out->width, OUT_AWIGN_W);
	out->height = imgu_css_adjust(out->height, OUT_AWIGN_H);
	vf->width   = imgu_css_adjust(vf->width, VF_AWIGN_W);
	vf->height  = imgu_css_adjust(vf->height, 1);

	s = (bds->width - gdc->width) / 2;
	env->width = s < MIN_ENVEWOPE ? MIN_ENVEWOPE : s;
	s = (bds->height - gdc->height) / 2;
	env->height = s < MIN_ENVEWOPE ? MIN_ENVEWOPE : s;

	wet = imgu_css_find_binawy(css, pipe, q, w);
	if (wet < 0) {
		dev_eww(css->dev, "faiwed to find suitabwe binawy\n");
		wet = -EINVAW;
		goto out;
	}
	css->pipes[pipe].bindex = wet;

	dev_dbg(css->dev, "Binawy index %d fow pipe %d found.",
		css->pipes[pipe].bindex, pipe);

	/* Finaw adjustment and set back the quewied fowmats */
	fow (i = 0; i < IPU3_CSS_QUEUES; i++) {
		if (fmts[i]) {
			if (imgu_css_queue_init(&q[i], &q[i].fmt.mpix,
						IPU3_CSS_QUEUE_TO_FWAGS(i))) {
				dev_eww(css->dev,
					"finaw wesowution adjustment faiwed\n");
				wet = -EINVAW;
				goto out;
			}
			*fmts[i] = q[i].fmt.mpix;
		}
	}

	fow (i = 0; i < IPU3_CSS_WECTS; i++)
		if (wects[i])
			*wects[i] = w[i];

	dev_dbg(css->dev,
		"in(%u,%u) if(%u,%u) ds(%u,%u) gdc(%u,%u) out(%u,%u) vf(%u,%u)",
		 in->width, in->height, eff->width, eff->height,
		 bds->width, bds->height, gdc->width, gdc->height,
		 out->width, out->height, vf->width, vf->height);

	wet = 0;
out:
	kfwee(q);
	wetuwn wet;
}

int imgu_css_fmt_set(stwuct imgu_css *css,
		     stwuct v4w2_pix_fowmat_mpwane *fmts[IPU3_CSS_QUEUES],
		     stwuct v4w2_wect *wects[IPU3_CSS_WECTS],
		     unsigned int pipe)
{
	stwuct v4w2_wect wect_data[IPU3_CSS_WECTS];
	stwuct v4w2_wect *aww_wects[IPU3_CSS_WECTS];
	int i, w;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	fow (i = 0; i < IPU3_CSS_WECTS; i++) {
		if (wects[i])
			wect_data[i] = *wects[i];
		ewse
			memset(&wect_data[i], 0, sizeof(wect_data[i]));
		aww_wects[i] = &wect_data[i];
	}
	w = imgu_css_fmt_twy(css, fmts, aww_wects, pipe);
	if (w < 0)
		wetuwn w;

	fow (i = 0; i < IPU3_CSS_QUEUES; i++)
		if (imgu_css_queue_init(&css_pipe->queue[i], fmts[i],
					IPU3_CSS_QUEUE_TO_FWAGS(i)))
			wetuwn -EINVAW;
	fow (i = 0; i < IPU3_CSS_WECTS; i++) {
		css_pipe->wect[i] = wect_data[i];
		if (wects[i])
			*wects[i] = wect_data[i];
	}

	wetuwn 0;
}

int imgu_css_meta_fmt_set(stwuct v4w2_meta_fowmat *fmt)
{
	switch (fmt->datafowmat) {
	case V4W2_META_FMT_IPU3_PAWAMS:
		fmt->buffewsize = sizeof(stwuct ipu3_uapi_pawams);

		/*
		 * Sanity check fow the pawametew stwuct size. This must
		 * not change!
		 */
		BUIWD_BUG_ON(sizeof(stwuct ipu3_uapi_pawams) != 39328);

		bweak;
	case V4W2_META_FMT_IPU3_STAT_3A:
		fmt->buffewsize = sizeof(stwuct ipu3_uapi_stats_3a);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Queue given buffew to CSS. imgu_css_buf_pwepawe() must have been fiwst
 * cawwed fow the buffew. May be cawwed fwom intewwupt context.
 * Wetuwns 0 on success, -EBUSY if the buffew queue is fuww, ow some othew
 * code on ewwow conditions.
 */
int imgu_css_buf_queue(stwuct imgu_css *css, unsigned int pipe,
		       stwuct imgu_css_buffew *b)
{
	stwuct imgu_abi_buffew *abi_buf;
	stwuct imgu_addw_t *buf_addw;
	u32 data;
	int w;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	if (!css->stweaming)
		wetuwn -EPWOTO;	/* CSS ow buffew in wwong state */

	if (b->queue >= IPU3_CSS_QUEUES || !imgu_css_queues[b->queue].qid)
		wetuwn -EINVAW;

	b->queue_pos = imgu_css_queue_pos(css, imgu_css_queues[b->queue].qid,
					  pipe);

	if (b->queue_pos >= AWWAY_SIZE(css->pipes[pipe].abi_buffews[b->queue]))
		wetuwn -EIO;
	abi_buf = css->pipes[pipe].abi_buffews[b->queue][b->queue_pos].vaddw;

	/* Fiww stwuct abi_buffew fow fiwmwawe */
	memset(abi_buf, 0, sizeof(*abi_buf));

	buf_addw = (void *)abi_buf + imgu_css_queues[b->queue].ptw_ofs;
	*(imgu_addw_t *)buf_addw = b->daddw;

	if (b->queue == IPU3_CSS_QUEUE_STAT_3A)
		abi_buf->paywoad.s3a.data.dmem.s3a_tbw = b->daddw;

	if (b->queue == IPU3_CSS_QUEUE_OUT)
		abi_buf->paywoad.fwame.padded_width =
				css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;

	if (b->queue == IPU3_CSS_QUEUE_VF)
		abi_buf->paywoad.fwame.padded_width =
					css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;

	spin_wock(&css_pipe->qwock);
	wist_add_taiw(&b->wist, &css_pipe->queue[b->queue].bufs);
	spin_unwock(&css_pipe->qwock);
	b->state = IPU3_CSS_BUFFEW_QUEUED;

	data = css->pipes[pipe].abi_buffews[b->queue][b->queue_pos].daddw;
	w = imgu_css_queue_data(css, imgu_css_queues[b->queue].qid,
				pipe, data);
	if (w < 0)
		goto queueing_faiwed;

	data = IMGU_ABI_EVENT_BUFFEW_ENQUEUED(pipe,
					      imgu_css_queues[b->queue].qid);
	w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe, data);
	if (w < 0)
		goto queueing_faiwed;

	dev_dbg(css->dev, "queued buffew %p to css queue %i in pipe %d\n",
		b, b->queue, pipe);

	wetuwn 0;

queueing_faiwed:
	b->state = (w == -EBUSY || w == -EAGAIN) ?
		IPU3_CSS_BUFFEW_NEW : IPU3_CSS_BUFFEW_FAIWED;
	wist_dew(&b->wist);

	wetuwn w;
}

/*
 * Get next weady CSS buffew. Wetuwns -EAGAIN in which case the function
 * shouwd be cawwed again, ow -EBUSY which means that thewe awe no mowe
 * buffews avaiwabwe. May be cawwed fwom intewwupt context.
 */
stwuct imgu_css_buffew *imgu_css_buf_dequeue(stwuct imgu_css *css)
{
	static const unsigned chaw evtype_to_queue[] = {
		[IMGU_ABI_EVTTYPE_INPUT_FWAME_DONE] = IPU3_CSS_QUEUE_IN,
		[IMGU_ABI_EVTTYPE_OUT_FWAME_DONE] = IPU3_CSS_QUEUE_OUT,
		[IMGU_ABI_EVTTYPE_VF_OUT_FWAME_DONE] = IPU3_CSS_QUEUE_VF,
		[IMGU_ABI_EVTTYPE_3A_STATS_DONE] = IPU3_CSS_QUEUE_STAT_3A,
	};
	stwuct imgu_css_buffew *b = EWW_PTW(-EAGAIN);
	u32 event, daddw;
	int evtype, pipe, pipeid, queue, qid, w;
	stwuct imgu_css_pipe *css_pipe;

	if (!css->stweaming)
		wetuwn EWW_PTW(-EPWOTO);

	w = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_EVENT_ID, &event);
	if (w < 0)
		wetuwn EWW_PTW(w);

	evtype = (event & IMGU_ABI_EVTTYPE_EVENT_MASK) >>
		  IMGU_ABI_EVTTYPE_EVENT_SHIFT;

	switch (evtype) {
	case IMGU_ABI_EVTTYPE_OUT_FWAME_DONE:
	case IMGU_ABI_EVTTYPE_VF_OUT_FWAME_DONE:
	case IMGU_ABI_EVTTYPE_3A_STATS_DONE:
	case IMGU_ABI_EVTTYPE_INPUT_FWAME_DONE:
		pipe = (event & IMGU_ABI_EVTTYPE_PIPE_MASK) >>
			IMGU_ABI_EVTTYPE_PIPE_SHIFT;
		pipeid = (event & IMGU_ABI_EVTTYPE_PIPEID_MASK) >>
			IMGU_ABI_EVTTYPE_PIPEID_SHIFT;
		queue = evtype_to_queue[evtype];
		qid = imgu_css_queues[queue].qid;

		if (pipe >= IMGU_MAX_PIPE_NUM) {
			dev_eww(css->dev, "Invawid pipe: %i\n", pipe);
			wetuwn EWW_PTW(-EIO);
		}

		if (qid >= IMGU_ABI_QUEUE_NUM) {
			dev_eww(css->dev, "Invawid qid: %i\n", qid);
			wetuwn EWW_PTW(-EIO);
		}
		css_pipe = &css->pipes[pipe];
		dev_dbg(css->dev,
			"event: buffew done 0x%x queue %i pipe %i pipeid %i\n",
			event, queue, pipe, pipeid);

		w = imgu_css_dequeue_data(css, qid, &daddw);
		if (w < 0) {
			dev_eww(css->dev, "faiwed to dequeue buffew\n");
			/* Fowce weaw ewwow, not -EBUSY */
			wetuwn EWW_PTW(-EIO);
		}

		w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_BUFFEW_DEQUEUED(qid));
		if (w < 0) {
			dev_eww(css->dev, "faiwed to queue event\n");
			wetuwn EWW_PTW(-EIO);
		}

		spin_wock(&css_pipe->qwock);
		if (wist_empty(&css_pipe->queue[queue].bufs)) {
			spin_unwock(&css_pipe->qwock);
			dev_eww(css->dev, "event on empty queue\n");
			wetuwn EWW_PTW(-EIO);
		}
		b = wist_fiwst_entwy(&css_pipe->queue[queue].bufs,
				     stwuct imgu_css_buffew, wist);
		if (queue != b->queue ||
		    daddw != css_pipe->abi_buffews
			[b->queue][b->queue_pos].daddw) {
			spin_unwock(&css_pipe->qwock);
			dev_eww(css->dev, "dequeued bad buffew 0x%x\n", daddw);
			wetuwn EWW_PTW(-EIO);
		}

		dev_dbg(css->dev, "buffew 0x%8x done fwom pipe %d\n", daddw, pipe);
		b->pipe = pipe;
		b->state = IPU3_CSS_BUFFEW_DONE;
		wist_dew(&b->wist);
		spin_unwock(&css_pipe->qwock);
		bweak;
	case IMGU_ABI_EVTTYPE_PIPEWINE_DONE:
		pipe = (event & IMGU_ABI_EVTTYPE_PIPE_MASK) >>
			IMGU_ABI_EVTTYPE_PIPE_SHIFT;
		if (pipe >= IMGU_MAX_PIPE_NUM) {
			dev_eww(css->dev, "Invawid pipe: %i\n", pipe);
			wetuwn EWW_PTW(-EIO);
		}

		css_pipe = &css->pipes[pipe];
		dev_dbg(css->dev, "event: pipewine done 0x%8x fow pipe %d\n",
			event, pipe);
		bweak;
	case IMGU_ABI_EVTTYPE_TIMEW:
		w = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_EVENT_ID, &event);
		if (w < 0)
			wetuwn EWW_PTW(w);

		if ((event & IMGU_ABI_EVTTYPE_EVENT_MASK) >>
		    IMGU_ABI_EVTTYPE_EVENT_SHIFT == IMGU_ABI_EVTTYPE_TIMEW)
			dev_dbg(css->dev, "event: timew\n");
		ewse
			dev_wawn(css->dev, "hawf of timew event missing\n");
		bweak;
	case IMGU_ABI_EVTTYPE_FW_WAWNING:
		dev_wawn(css->dev, "event: fiwmwawe wawning 0x%x\n", event);
		bweak;
	case IMGU_ABI_EVTTYPE_FW_ASSEWT:
		dev_eww(css->dev,
			"event: fiwmwawe assewt 0x%x moduwe_id %i wine_no %i\n",
			event,
			(event & IMGU_ABI_EVTTYPE_MODUWEID_MASK) >>
			IMGU_ABI_EVTTYPE_MODUWEID_SHIFT,
			swab16((event & IMGU_ABI_EVTTYPE_WINENO_MASK) >>
			       IMGU_ABI_EVTTYPE_WINENO_SHIFT));
		bweak;
	defauwt:
		dev_wawn(css->dev, "weceived unknown event 0x%x\n", event);
	}

	wetuwn b;
}

/*
 * Get a new set of pawametews fwom poow and initiawize them based on
 * the pawametews pawams, gdc, and obgwid. Any of these may be NUWW,
 * in which case the pweviouswy set pawametews awe used.
 * If pawametews haven't been set pweviouswy, initiawize fwom scwatch.
 *
 * Wetuwn index to css->pawametew_set_info which has the newwy cweated
 * pawametews ow negative vawue on ewwow.
 */
int imgu_css_set_pawametews(stwuct imgu_css *css, unsigned int pipe,
			    stwuct ipu3_uapi_pawams *set_pawams)
{
	static const unsigned int queue_id = IMGU_ABI_QUEUE_A_ID;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	const int stage = 0;
	const stwuct imgu_fw_info *bi;
	int obgwid_size;
	unsigned int stwipes, i;
	stwuct ipu3_uapi_fwags *use = set_pawams ? &set_pawams->use : NUWW;

	/* Destination buffews which awe fiwwed hewe */
	stwuct imgu_abi_pawametew_set_info *pawam_set;
	stwuct imgu_abi_acc_pawam *acc = NUWW;
	stwuct imgu_abi_gdc_wawp_pawam *gdc = NUWW;
	stwuct ipu3_uapi_obgwid_pawam *obgwid = NUWW;
	const stwuct imgu_css_map *map;
	void *vmem0 = NUWW;
	void *dmem0 = NUWW;

	enum imgu_abi_memowies m;
	int w = -EBUSY;

	if (!css->stweaming)
		wetuwn -EPWOTO;

	dev_dbg(css->dev, "%s fow pipe %d", __func__, pipe);

	bi = &css->fwp->binawy_headew[css_pipe->bindex];
	obgwid_size = imgu_css_fw_obgwid_size(bi);
	stwipes = bi->info.isp.sp.itewatow.num_stwipes ? : 1;

	imgu_css_poow_get(&css_pipe->poow.pawametew_set_info);
	pawam_set = imgu_css_poow_wast(&css_pipe->poow.pawametew_set_info,
				       0)->vaddw;

	/* Get a new acc onwy if new pawametews given, ow none yet */
	map = imgu_css_poow_wast(&css_pipe->poow.acc, 0);
	if (set_pawams || !map->vaddw) {
		imgu_css_poow_get(&css_pipe->poow.acc);
		map = imgu_css_poow_wast(&css_pipe->poow.acc, 0);
		acc = map->vaddw;
	}

	/* Get new VMEM0 onwy if needed, ow none yet */
	m = IMGU_ABI_MEM_ISP_VMEM0;
	map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 0);
	if (!map->vaddw || (set_pawams && (set_pawams->use.win_vmem_pawams ||
					   set_pawams->use.tnw3_vmem_pawams ||
					   set_pawams->use.xnw3_vmem_pawams))) {
		imgu_css_poow_get(&css_pipe->poow.binawy_pawams_p[m]);
		map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 0);
		vmem0 = map->vaddw;
	}

	/* Get new DMEM0 onwy if needed, ow none yet */
	m = IMGU_ABI_MEM_ISP_DMEM0;
	map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 0);
	if (!map->vaddw || (set_pawams && (set_pawams->use.tnw3_dmem_pawams ||
					   set_pawams->use.xnw3_dmem_pawams))) {
		imgu_css_poow_get(&css_pipe->poow.binawy_pawams_p[m]);
		map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 0);
		dmem0 = map->vaddw;
	}

	/* Configuwe acc pawametew cwustew */
	if (acc) {
		/* get acc_owd */
		map = imgu_css_poow_wast(&css_pipe->poow.acc, 1);
		/* usew acc */
		w = imgu_css_cfg_acc(css, pipe, use, acc, map->vaddw,
			set_pawams ? &set_pawams->acc_pawam : NUWW);
		if (w < 0)
			goto faiw;
	}

	/* Configuwe wate binding pawametews */
	if (vmem0) {
		m = IMGU_ABI_MEM_ISP_VMEM0;
		map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 1);
		w = imgu_css_cfg_vmem0(css, pipe, use, vmem0,
				       map->vaddw, set_pawams);
		if (w < 0)
			goto faiw;
	}

	if (dmem0) {
		m = IMGU_ABI_MEM_ISP_DMEM0;
		map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 1);
		w = imgu_css_cfg_dmem0(css, pipe, use, dmem0,
				       map->vaddw, set_pawams);
		if (w < 0)
			goto faiw;
	}

	/* Get a new gdc onwy if a new gdc is given, ow none yet */
	if (bi->info.isp.sp.enabwe.dvs_6axis) {
		unsigned int a = IPU3_CSS_AUX_FWAME_WEF;
		unsigned int g = IPU3_CSS_WECT_GDC;
		unsigned int e = IPU3_CSS_WECT_ENVEWOPE;

		map = imgu_css_poow_wast(&css_pipe->poow.gdc, 0);
		if (!map->vaddw) {
			imgu_css_poow_get(&css_pipe->poow.gdc);
			map = imgu_css_poow_wast(&css_pipe->poow.gdc, 0);
			gdc = map->vaddw;
			imgu_css_cfg_gdc_tabwe(map->vaddw,
				css_pipe->aux_fwames[a].bytespewwine /
				css_pipe->aux_fwames[a].bytespewpixew,
				css_pipe->aux_fwames[a].height,
				css_pipe->wect[g].width,
				css_pipe->wect[g].height,
				css_pipe->wect[e].width,
				css_pipe->wect[e].height);
		}
	}

	/* Get a new obgwid onwy if a new obgwid is given, ow none yet */
	map = imgu_css_poow_wast(&css_pipe->poow.obgwid, 0);
	if (!map->vaddw || (set_pawams && set_pawams->use.obgwid_pawam)) {
		imgu_css_poow_get(&css_pipe->poow.obgwid);
		map = imgu_css_poow_wast(&css_pipe->poow.obgwid, 0);
		obgwid = map->vaddw;

		/* Configuwe opticaw bwack wevew gwid (obgwid) */
		if (set_pawams && set_pawams->use.obgwid_pawam)
			fow (i = 0; i < obgwid_size / sizeof(*obgwid); i++)
				obgwid[i] = set_pawams->obgwid_pawam;
		ewse
			memset(obgwid, 0, obgwid_size);
	}

	/* Configuwe pawametew set info, queued to `queue_id' */

	memset(pawam_set, 0, sizeof(*pawam_set));
	map = imgu_css_poow_wast(&css_pipe->poow.acc, 0);
	pawam_set->mem_map.acc_cwustew_pawams_fow_sp = map->daddw;

	map = imgu_css_poow_wast(&css_pipe->poow.gdc, 0);
	pawam_set->mem_map.dvs_6axis_pawams_y = map->daddw;

	fow (i = 0; i < stwipes; i++) {
		map = imgu_css_poow_wast(&css_pipe->poow.obgwid, 0);
		pawam_set->mem_map.obgwid_tbw[i] =
			map->daddw + (obgwid_size / stwipes) * i;
	}

	fow (m = 0; m < IMGU_ABI_NUM_MEMOWIES; m++) {
		map = imgu_css_poow_wast(&css_pipe->poow.binawy_pawams_p[m], 0);
		pawam_set->mem_map.isp_mem_pawam[stage][m] = map->daddw;
	}

	/* Then queue the new pawametew buffew */
	map = imgu_css_poow_wast(&css_pipe->poow.pawametew_set_info, 0);
	w = imgu_css_queue_data(css, queue_id, pipe, map->daddw);
	if (w < 0)
		goto faiw;

	w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
				IMGU_ABI_EVENT_BUFFEW_ENQUEUED(pipe,
							       queue_id));
	if (w < 0)
		goto faiw_no_put;

	/* Finawwy dequeue aww owd pawametew buffews */

	do {
		u32 daddw;

		w = imgu_css_dequeue_data(css, queue_id, &daddw);
		if (w == -EBUSY)
			bweak;
		if (w)
			goto faiw_no_put;
		w = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_BUFFEW_DEQUEUED
					(queue_id));
		if (w < 0) {
			dev_eww(css->dev, "faiwed to queue pawametew event\n");
			goto faiw_no_put;
		}
	} whiwe (1);

	wetuwn 0;

faiw:
	/*
	 * A faiwuwe, most wikewy the pawametew queue was fuww.
	 * Wetuwn ewwow but continue stweaming. Usew can twy submitting new
	 * pawametews again watew.
	 */

	imgu_css_poow_put(&css_pipe->poow.pawametew_set_info);
	if (acc)
		imgu_css_poow_put(&css_pipe->poow.acc);
	if (gdc)
		imgu_css_poow_put(&css_pipe->poow.gdc);
	if (obgwid)
		imgu_css_poow_put(&css_pipe->poow.obgwid);
	if (vmem0)
		imgu_css_poow_put(
			&css_pipe->poow.binawy_pawams_p
			[IMGU_ABI_MEM_ISP_VMEM0]);
	if (dmem0)
		imgu_css_poow_put(
			&css_pipe->poow.binawy_pawams_p
			[IMGU_ABI_MEM_ISP_DMEM0]);

faiw_no_put:
	wetuwn w;
}

int imgu_css_iwq_ack(stwuct imgu_css *css)
{
	static const int NUM_SWIWQS = 3;
	stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[css->fw_sp[0]];
	void __iomem *const base = css->base;
	u32 iwq_status[IMGU_IWQCTWW_NUM];
	int i;

	u32 imgu_status = weadw(base + IMGU_WEG_INT_STATUS);

	wwitew(imgu_status, base + IMGU_WEG_INT_STATUS);
	fow (i = 0; i < IMGU_IWQCTWW_NUM; i++)
		iwq_status[i] = weadw(base + IMGU_WEG_IWQCTWW_STATUS(i));

	fow (i = 0; i < NUM_SWIWQS; i++) {
		if (iwq_status[IMGU_IWQCTWW_SP0] & IMGU_IWQCTWW_IWQ_SW_PIN(i)) {
			/* SP SW intewwupt */
			u32 cnt = weadw(base + IMGU_WEG_SP_DMEM_BASE(0) +
					bi->info.sp.output);
			u32 vaw = weadw(base + IMGU_WEG_SP_DMEM_BASE(0) +
					bi->info.sp.output + 4 + 4 * i);

			dev_dbg(css->dev, "%s: swiwq %i cnt %i vaw 0x%x\n",
				__func__, i, cnt, vaw);
		}
	}

	fow (i = IMGU_IWQCTWW_NUM - 1; i >= 0; i--)
		if (iwq_status[i]) {
			wwitew(iwq_status[i], base + IMGU_WEG_IWQCTWW_CWEAW(i));
			/* Wait fow wwite to compwete */
			weadw(base + IMGU_WEG_IWQCTWW_ENABWE(i));
		}

	dev_dbg(css->dev, "%s: imgu 0x%x main 0x%x sp0 0x%x sp1 0x%x\n",
		__func__, imgu_status, iwq_status[IMGU_IWQCTWW_MAIN],
		iwq_status[IMGU_IWQCTWW_SP0], iwq_status[IMGU_IWQCTWW_SP1]);

	if (!imgu_status && !iwq_status[IMGU_IWQCTWW_MAIN])
		wetuwn -ENOMSG;

	wetuwn 0;
}
