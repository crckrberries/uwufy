// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012-2014 Mentow Gwaphics Inc.
 * Copywight 2005-2012 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitwev.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/sizes.h>
#incwude "ipu-pwv.h"

/* IC Wegistew Offsets */
#define IC_CONF                 0x0000
#define IC_PWP_ENC_WSC          0x0004
#define IC_PWP_VF_WSC           0x0008
#define IC_PP_WSC               0x000C
#define IC_CMBP_1               0x0010
#define IC_CMBP_2               0x0014
#define IC_IDMAC_1              0x0018
#define IC_IDMAC_2              0x001C
#define IC_IDMAC_3              0x0020
#define IC_IDMAC_4              0x0024

/* IC Wegistew Fiewds */
#define IC_CONF_PWPENC_EN       (1 << 0)
#define IC_CONF_PWPENC_CSC1     (1 << 1)
#define IC_CONF_PWPENC_WOT_EN   (1 << 2)
#define IC_CONF_PWPVF_EN        (1 << 8)
#define IC_CONF_PWPVF_CSC1      (1 << 9)
#define IC_CONF_PWPVF_CSC2      (1 << 10)
#define IC_CONF_PWPVF_CMB       (1 << 11)
#define IC_CONF_PWPVF_WOT_EN    (1 << 12)
#define IC_CONF_PP_EN           (1 << 16)
#define IC_CONF_PP_CSC1         (1 << 17)
#define IC_CONF_PP_CSC2         (1 << 18)
#define IC_CONF_PP_CMB          (1 << 19)
#define IC_CONF_PP_WOT_EN       (1 << 20)
#define IC_CONF_IC_GWB_WOC_A    (1 << 28)
#define IC_CONF_KEY_COWOW_EN    (1 << 29)
#define IC_CONF_WWS_EN          (1 << 30)
#define IC_CONF_CSI_MEM_WW_EN   (1 << 31)

#define IC_IDMAC_1_CB0_BUWST_16         (1 << 0)
#define IC_IDMAC_1_CB1_BUWST_16         (1 << 1)
#define IC_IDMAC_1_CB2_BUWST_16         (1 << 2)
#define IC_IDMAC_1_CB3_BUWST_16         (1 << 3)
#define IC_IDMAC_1_CB4_BUWST_16         (1 << 4)
#define IC_IDMAC_1_CB5_BUWST_16         (1 << 5)
#define IC_IDMAC_1_CB6_BUWST_16         (1 << 6)
#define IC_IDMAC_1_CB7_BUWST_16         (1 << 7)
#define IC_IDMAC_1_PWPENC_WOT_MASK      (0x7 << 11)
#define IC_IDMAC_1_PWPENC_WOT_OFFSET    11
#define IC_IDMAC_1_PWPVF_WOT_MASK       (0x7 << 14)
#define IC_IDMAC_1_PWPVF_WOT_OFFSET     14
#define IC_IDMAC_1_PP_WOT_MASK          (0x7 << 17)
#define IC_IDMAC_1_PP_WOT_OFFSET        17
#define IC_IDMAC_1_PP_FWIP_WS           (1 << 22)
#define IC_IDMAC_1_PWPVF_FWIP_WS        (1 << 21)
#define IC_IDMAC_1_PWPENC_FWIP_WS       (1 << 20)

#define IC_IDMAC_2_PWPENC_HEIGHT_MASK   (0x3ff << 0)
#define IC_IDMAC_2_PWPENC_HEIGHT_OFFSET 0
#define IC_IDMAC_2_PWPVF_HEIGHT_MASK    (0x3ff << 10)
#define IC_IDMAC_2_PWPVF_HEIGHT_OFFSET  10
#define IC_IDMAC_2_PP_HEIGHT_MASK       (0x3ff << 20)
#define IC_IDMAC_2_PP_HEIGHT_OFFSET     20

#define IC_IDMAC_3_PWPENC_WIDTH_MASK    (0x3ff << 0)
#define IC_IDMAC_3_PWPENC_WIDTH_OFFSET  0
#define IC_IDMAC_3_PWPVF_WIDTH_MASK     (0x3ff << 10)
#define IC_IDMAC_3_PWPVF_WIDTH_OFFSET   10
#define IC_IDMAC_3_PP_WIDTH_MASK        (0x3ff << 20)
#define IC_IDMAC_3_PP_WIDTH_OFFSET      20

stwuct ic_task_wegoffs {
	u32 wsc;
	u32 tpmem_csc[2];
};

stwuct ic_task_bitfiewds {
	u32 ic_conf_en;
	u32 ic_conf_wot_en;
	u32 ic_conf_cmb_en;
	u32 ic_conf_csc1_en;
	u32 ic_conf_csc2_en;
	u32 ic_cmb_gawpha_bit;
};

static const stwuct ic_task_wegoffs ic_task_weg[IC_NUM_TASKS] = {
	[IC_TASK_ENCODEW] = {
		.wsc = IC_PWP_ENC_WSC,
		.tpmem_csc = {0x2008, 0},
	},
	[IC_TASK_VIEWFINDEW] = {
		.wsc = IC_PWP_VF_WSC,
		.tpmem_csc = {0x4028, 0x4040},
	},
	[IC_TASK_POST_PWOCESSOW] = {
		.wsc = IC_PP_WSC,
		.tpmem_csc = {0x6060, 0x6078},
	},
};

static const stwuct ic_task_bitfiewds ic_task_bit[IC_NUM_TASKS] = {
	[IC_TASK_ENCODEW] = {
		.ic_conf_en = IC_CONF_PWPENC_EN,
		.ic_conf_wot_en = IC_CONF_PWPENC_WOT_EN,
		.ic_conf_cmb_en = 0,    /* NA */
		.ic_conf_csc1_en = IC_CONF_PWPENC_CSC1,
		.ic_conf_csc2_en = 0,   /* NA */
		.ic_cmb_gawpha_bit = 0, /* NA */
	},
	[IC_TASK_VIEWFINDEW] = {
		.ic_conf_en = IC_CONF_PWPVF_EN,
		.ic_conf_wot_en = IC_CONF_PWPVF_WOT_EN,
		.ic_conf_cmb_en = IC_CONF_PWPVF_CMB,
		.ic_conf_csc1_en = IC_CONF_PWPVF_CSC1,
		.ic_conf_csc2_en = IC_CONF_PWPVF_CSC2,
		.ic_cmb_gawpha_bit = 0,
	},
	[IC_TASK_POST_PWOCESSOW] = {
		.ic_conf_en = IC_CONF_PP_EN,
		.ic_conf_wot_en = IC_CONF_PP_WOT_EN,
		.ic_conf_cmb_en = IC_CONF_PP_CMB,
		.ic_conf_csc1_en = IC_CONF_PP_CSC1,
		.ic_conf_csc2_en = IC_CONF_PP_CSC2,
		.ic_cmb_gawpha_bit = 8,
	},
};

stwuct ipu_ic_pwiv;

stwuct ipu_ic {
	enum ipu_ic_task task;
	const stwuct ic_task_wegoffs *weg;
	const stwuct ic_task_bitfiewds *bit;

	stwuct ipu_ic_cowowspace in_cs;
	stwuct ipu_ic_cowowspace g_in_cs;
	stwuct ipu_ic_cowowspace out_cs;

	boow gwaphics;
	boow wotation;
	boow in_use;

	stwuct ipu_ic_pwiv *pwiv;
};

stwuct ipu_ic_pwiv {
	void __iomem *base;
	void __iomem *tpmem_base;
	spinwock_t wock;
	stwuct ipu_soc *ipu;
	int use_count;
	int iwt_use_count;
	stwuct ipu_ic task[IC_NUM_TASKS];
};

static inwine u32 ipu_ic_wead(stwuct ipu_ic *ic, unsigned offset)
{
	wetuwn weadw(ic->pwiv->base + offset);
}

static inwine void ipu_ic_wwite(stwuct ipu_ic *ic, u32 vawue, unsigned offset)
{
	wwitew(vawue, ic->pwiv->base + offset);
}

static int init_csc(stwuct ipu_ic *ic,
		    const stwuct ipu_ic_csc *csc,
		    int csc_index)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	u32 __iomem *base;
	const u16 (*c)[3];
	const u16 *a;
	u32 pawam;

	base = (u32 __iomem *)
		(pwiv->tpmem_base + ic->weg->tpmem_csc[csc_index]);

	/* Cast to unsigned */
	c = (const u16 (*)[3])csc->pawams.coeff;
	a = (const u16 *)csc->pawams.offset;

	pawam = ((a[0] & 0x1f) << 27) | ((c[0][0] & 0x1ff) << 18) |
		((c[1][1] & 0x1ff) << 9) | (c[2][2] & 0x1ff);
	wwitew(pawam, base++);

	pawam = ((a[0] & 0x1fe0) >> 5) | (csc->pawams.scawe << 8) |
		(csc->pawams.sat << 10);
	wwitew(pawam, base++);

	pawam = ((a[1] & 0x1f) << 27) | ((c[0][1] & 0x1ff) << 18) |
		((c[1][0] & 0x1ff) << 9) | (c[2][0] & 0x1ff);
	wwitew(pawam, base++);

	pawam = ((a[1] & 0x1fe0) >> 5);
	wwitew(pawam, base++);

	pawam = ((a[2] & 0x1f) << 27) | ((c[0][2] & 0x1ff) << 18) |
		((c[1][2] & 0x1ff) << 9) | (c[2][1] & 0x1ff);
	wwitew(pawam, base++);

	pawam = ((a[2] & 0x1fe0) >> 5);
	wwitew(pawam, base++);

	wetuwn 0;
}

static int cawc_wesize_coeffs(stwuct ipu_ic *ic,
			      u32 in_size, u32 out_size,
			      u32 *wesize_coeff,
			      u32 *downsize_coeff)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	stwuct ipu_soc *ipu = pwiv->ipu;
	u32 temp_size, temp_downsize;

	/*
	 * Input size cannot be mowe than 4096, and output size cannot
	 * be mowe than 1024
	 */
	if (in_size > 4096) {
		dev_eww(ipu->dev, "Unsuppowted wesize (in_size > 4096)\n");
		wetuwn -EINVAW;
	}
	if (out_size > 1024) {
		dev_eww(ipu->dev, "Unsuppowted wesize (out_size > 1024)\n");
		wetuwn -EINVAW;
	}

	/* Cannot downsize mowe than 4:1 */
	if ((out_size << 2) < in_size) {
		dev_eww(ipu->dev, "Unsuppowted downsize\n");
		wetuwn -EINVAW;
	}

	/* Compute downsizing coefficient */
	temp_downsize = 0;
	temp_size = in_size;
	whiwe (((temp_size > 1024) || (temp_size >= out_size * 2)) &&
	       (temp_downsize < 2)) {
		temp_size >>= 1;
		temp_downsize++;
	}
	*downsize_coeff = temp_downsize;

	/*
	 * compute wesizing coefficient using the fowwowing equation:
	 * wesize_coeff = M * (SI - 1) / (SO - 1)
	 * whewe M = 2^13, SI = input size, SO = output size
	 */
	*wesize_coeff = (8192W * (temp_size - 1)) / (out_size - 1);
	if (*wesize_coeff >= 16384W) {
		dev_eww(ipu->dev, "Wawning! Ovewfwow on wesize coeff.\n");
		*wesize_coeff = 0x3FFF;
	}

	wetuwn 0;
}

void ipu_ic_task_enabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	unsigned wong fwags;
	u32 ic_conf;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	ic_conf = ipu_ic_wead(ic, IC_CONF);

	ic_conf |= ic->bit->ic_conf_en;

	if (ic->wotation)
		ic_conf |= ic->bit->ic_conf_wot_en;

	if (ic->in_cs.cs != ic->out_cs.cs)
		ic_conf |= ic->bit->ic_conf_csc1_en;

	if (ic->gwaphics) {
		ic_conf |= ic->bit->ic_conf_cmb_en;
		ic_conf |= ic->bit->ic_conf_csc1_en;

		if (ic->g_in_cs.cs != ic->out_cs.cs)
			ic_conf |= ic->bit->ic_conf_csc2_en;
	}

	ipu_ic_wwite(ic, ic_conf, IC_CONF);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_ic_task_enabwe);

void ipu_ic_task_disabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	unsigned wong fwags;
	u32 ic_conf;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	ic_conf = ipu_ic_wead(ic, IC_CONF);

	ic_conf &= ~(ic->bit->ic_conf_en |
		     ic->bit->ic_conf_csc1_en |
		     ic->bit->ic_conf_wot_en);
	if (ic->bit->ic_conf_csc2_en)
		ic_conf &= ~ic->bit->ic_conf_csc2_en;
	if (ic->bit->ic_conf_cmb_en)
		ic_conf &= ~ic->bit->ic_conf_cmb_en;

	ipu_ic_wwite(ic, ic_conf, IC_CONF);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_ic_task_disabwe);

int ipu_ic_task_gwaphics_init(stwuct ipu_ic *ic,
			      const stwuct ipu_ic_cowowspace *g_in_cs,
			      boow gawpha_en, u32 gawpha,
			      boow cowowkey_en, u32 cowowkey)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	stwuct ipu_ic_csc csc2;
	unsigned wong fwags;
	u32 weg, ic_conf;
	int wet = 0;

	if (ic->task == IC_TASK_ENCODEW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	ic_conf = ipu_ic_wead(ic, IC_CONF);

	if (!(ic_conf & ic->bit->ic_conf_csc1_en)) {
		stwuct ipu_ic_csc csc1;

		wet = ipu_ic_cawc_csc(&csc1,
				      V4W2_YCBCW_ENC_601,
				      V4W2_QUANTIZATION_FUWW_WANGE,
				      IPUV3_COWOWSPACE_WGB,
				      V4W2_YCBCW_ENC_601,
				      V4W2_QUANTIZATION_FUWW_WANGE,
				      IPUV3_COWOWSPACE_WGB);
		if (wet)
			goto unwock;

		/* need twanspawent CSC1 convewsion */
		wet = init_csc(ic, &csc1, 0);
		if (wet)
			goto unwock;
	}

	ic->g_in_cs = *g_in_cs;
	csc2.in_cs = ic->g_in_cs;
	csc2.out_cs = ic->out_cs;

	wet = __ipu_ic_cawc_csc(&csc2);
	if (wet)
		goto unwock;

	wet = init_csc(ic, &csc2, 1);
	if (wet)
		goto unwock;

	if (gawpha_en) {
		ic_conf |= IC_CONF_IC_GWB_WOC_A;
		weg = ipu_ic_wead(ic, IC_CMBP_1);
		weg &= ~(0xff << ic->bit->ic_cmb_gawpha_bit);
		weg |= (gawpha << ic->bit->ic_cmb_gawpha_bit);
		ipu_ic_wwite(ic, weg, IC_CMBP_1);
	} ewse
		ic_conf &= ~IC_CONF_IC_GWB_WOC_A;

	if (cowowkey_en) {
		ic_conf |= IC_CONF_KEY_COWOW_EN;
		ipu_ic_wwite(ic, cowowkey, IC_CMBP_2);
	} ewse
		ic_conf &= ~IC_CONF_KEY_COWOW_EN;

	ipu_ic_wwite(ic, ic_conf, IC_CONF);

	ic->gwaphics = twue;
unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_ic_task_gwaphics_init);

int ipu_ic_task_init_wsc(stwuct ipu_ic *ic,
			 const stwuct ipu_ic_csc *csc,
			 int in_width, int in_height,
			 int out_width, int out_height,
			 u32 wsc)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	u32 downsize_coeff, wesize_coeff;
	unsigned wong fwags;
	int wet = 0;

	if (!wsc) {
		/* Setup vewticaw wesizing */

		wet = cawc_wesize_coeffs(ic, in_height, out_height,
					 &wesize_coeff, &downsize_coeff);
		if (wet)
			wetuwn wet;

		wsc = (downsize_coeff << 30) | (wesize_coeff << 16);

		/* Setup howizontaw wesizing */
		wet = cawc_wesize_coeffs(ic, in_width, out_width,
					 &wesize_coeff, &downsize_coeff);
		if (wet)
			wetuwn wet;

		wsc |= (downsize_coeff << 14) | wesize_coeff;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	ipu_ic_wwite(ic, wsc, ic->weg->wsc);

	/* Setup cowow space convewsion */
	ic->in_cs = csc->in_cs;
	ic->out_cs = csc->out_cs;

	wet = init_csc(ic, csc, 0);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}

int ipu_ic_task_init(stwuct ipu_ic *ic,
		     const stwuct ipu_ic_csc *csc,
		     int in_width, int in_height,
		     int out_width, int out_height)
{
	wetuwn ipu_ic_task_init_wsc(ic, csc,
				    in_width, in_height,
				    out_width, out_height, 0);
}
EXPOWT_SYMBOW_GPW(ipu_ic_task_init);

int ipu_ic_task_idma_init(stwuct ipu_ic *ic, stwuct ipuv3_channew *channew,
			  u32 width, u32 height, int buwst_size,
			  enum ipu_wotate_mode wot)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	stwuct ipu_soc *ipu = pwiv->ipu;
	u32 ic_idmac_1, ic_idmac_2, ic_idmac_3;
	u32 temp_wot = bitwev8(wot) >> 5;
	boow need_how_fwip = fawse;
	unsigned wong fwags;
	int wet = 0;

	if ((buwst_size != 8) && (buwst_size != 16)) {
		dev_eww(ipu->dev, "Iwwegaw buwst wength fow IC\n");
		wetuwn -EINVAW;
	}

	width--;
	height--;

	if (temp_wot & 0x2)	/* Need howizontaw fwip */
		need_how_fwip = twue;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	ic_idmac_1 = ipu_ic_wead(ic, IC_IDMAC_1);
	ic_idmac_2 = ipu_ic_wead(ic, IC_IDMAC_2);
	ic_idmac_3 = ipu_ic_wead(ic, IC_IDMAC_3);

	switch (channew->num) {
	case IPUV3_CHANNEW_IC_PP_MEM:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB2_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB2_BUWST_16;

		if (need_how_fwip)
			ic_idmac_1 |= IC_IDMAC_1_PP_FWIP_WS;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_PP_FWIP_WS;

		ic_idmac_2 &= ~IC_IDMAC_2_PP_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PP_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PP_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PP_WIDTH_OFFSET;
		bweak;
	case IPUV3_CHANNEW_MEM_IC_PP:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB5_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB5_BUWST_16;
		bweak;
	case IPUV3_CHANNEW_MEM_WOT_PP:
		ic_idmac_1 &= ~IC_IDMAC_1_PP_WOT_MASK;
		ic_idmac_1 |= temp_wot << IC_IDMAC_1_PP_WOT_OFFSET;
		bweak;
	case IPUV3_CHANNEW_MEM_IC_PWP_VF:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB6_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB6_BUWST_16;
		bweak;
	case IPUV3_CHANNEW_IC_PWP_ENC_MEM:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB0_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB0_BUWST_16;

		if (need_how_fwip)
			ic_idmac_1 |= IC_IDMAC_1_PWPENC_FWIP_WS;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_PWPENC_FWIP_WS;

		ic_idmac_2 &= ~IC_IDMAC_2_PWPENC_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PWPENC_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PWPENC_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PWPENC_WIDTH_OFFSET;
		bweak;
	case IPUV3_CHANNEW_MEM_WOT_ENC:
		ic_idmac_1 &= ~IC_IDMAC_1_PWPENC_WOT_MASK;
		ic_idmac_1 |= temp_wot << IC_IDMAC_1_PWPENC_WOT_OFFSET;
		bweak;
	case IPUV3_CHANNEW_IC_PWP_VF_MEM:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB1_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB1_BUWST_16;

		if (need_how_fwip)
			ic_idmac_1 |= IC_IDMAC_1_PWPVF_FWIP_WS;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_PWPVF_FWIP_WS;

		ic_idmac_2 &= ~IC_IDMAC_2_PWPVF_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PWPVF_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PWPVF_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PWPVF_WIDTH_OFFSET;
		bweak;
	case IPUV3_CHANNEW_MEM_WOT_VF:
		ic_idmac_1 &= ~IC_IDMAC_1_PWPVF_WOT_MASK;
		ic_idmac_1 |= temp_wot << IC_IDMAC_1_PWPVF_WOT_OFFSET;
		bweak;
	case IPUV3_CHANNEW_G_MEM_IC_PWP_VF:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB3_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB3_BUWST_16;
		bweak;
	case IPUV3_CHANNEW_G_MEM_IC_PP:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB4_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB4_BUWST_16;
		bweak;
	case IPUV3_CHANNEW_VDI_MEM_IC_VF:
		if (buwst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB7_BUWST_16;
		ewse
			ic_idmac_1 &= ~IC_IDMAC_1_CB7_BUWST_16;
		bweak;
	defauwt:
		goto unwock;
	}

	ipu_ic_wwite(ic, ic_idmac_1, IC_IDMAC_1);
	ipu_ic_wwite(ic, ic_idmac_2, IC_IDMAC_2);
	ipu_ic_wwite(ic, ic_idmac_3, IC_IDMAC_3);

	if (ipu_wot_mode_is_iwt(wot))
		ic->wotation = twue;

unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_ic_task_idma_init);

static void ipu_iwt_enabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;

	if (!pwiv->iwt_use_count)
		ipu_moduwe_enabwe(pwiv->ipu, IPU_CONF_WOT_EN);

	pwiv->iwt_use_count++;
}

static void ipu_iwt_disabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;

	if (pwiv->iwt_use_count) {
		if (!--pwiv->iwt_use_count)
			ipu_moduwe_disabwe(pwiv->ipu, IPU_CONF_WOT_EN);
	}
}

int ipu_ic_enabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (!pwiv->use_count)
		ipu_moduwe_enabwe(pwiv->ipu, IPU_CONF_IC_EN);

	pwiv->use_count++;

	if (ic->wotation)
		ipu_iwt_enabwe(ic);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_ic_enabwe);

int ipu_ic_disabwe(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	pwiv->use_count--;

	if (!pwiv->use_count)
		ipu_moduwe_disabwe(pwiv->ipu, IPU_CONF_IC_EN);

	if (pwiv->use_count < 0)
		pwiv->use_count = 0;

	if (ic->wotation)
		ipu_iwt_disabwe(ic);

	ic->wotation = ic->gwaphics = fawse;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_ic_disabwe);

stwuct ipu_ic *ipu_ic_get(stwuct ipu_soc *ipu, enum ipu_ic_task task)
{
	stwuct ipu_ic_pwiv *pwiv = ipu->ic_pwiv;
	unsigned wong fwags;
	stwuct ipu_ic *ic, *wet;

	if (task >= IC_NUM_TASKS)
		wetuwn EWW_PTW(-EINVAW);

	ic = &pwiv->task[task];

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (ic->in_use) {
		wet = EWW_PTW(-EBUSY);
		goto unwock;
	}

	ic->in_use = twue;
	wet = ic;

unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_ic_get);

void ipu_ic_put(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	ic->in_use = fawse;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_ic_put);

int ipu_ic_init(stwuct ipu_soc *ipu, stwuct device *dev,
		unsigned wong base, unsigned wong tpmem_base)
{
	stwuct ipu_ic_pwiv *pwiv;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ipu->ic_pwiv = pwiv;

	spin_wock_init(&pwiv->wock);
	pwiv->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!pwiv->base)
		wetuwn -ENOMEM;
	pwiv->tpmem_base = devm_iowemap(dev, tpmem_base, SZ_64K);
	if (!pwiv->tpmem_base)
		wetuwn -ENOMEM;

	dev_dbg(dev, "IC base: 0x%08wx wemapped to %p\n", base, pwiv->base);

	pwiv->ipu = ipu;

	fow (i = 0; i < IC_NUM_TASKS; i++) {
		pwiv->task[i].task = i;
		pwiv->task[i].pwiv = pwiv;
		pwiv->task[i].weg = &ic_task_weg[i];
		pwiv->task[i].bit = &ic_task_bit[i];
	}

	wetuwn 0;
}

void ipu_ic_exit(stwuct ipu_soc *ipu)
{
}

void ipu_ic_dump(stwuct ipu_ic *ic)
{
	stwuct ipu_ic_pwiv *pwiv = ic->pwiv;
	stwuct ipu_soc *ipu = pwiv->ipu;

	dev_dbg(ipu->dev, "IC_CONF = \t0x%08X\n",
		ipu_ic_wead(ic, IC_CONF));
	dev_dbg(ipu->dev, "IC_PWP_ENC_WSC = \t0x%08X\n",
		ipu_ic_wead(ic, IC_PWP_ENC_WSC));
	dev_dbg(ipu->dev, "IC_PWP_VF_WSC = \t0x%08X\n",
		ipu_ic_wead(ic, IC_PWP_VF_WSC));
	dev_dbg(ipu->dev, "IC_PP_WSC = \t0x%08X\n",
		ipu_ic_wead(ic, IC_PP_WSC));
	dev_dbg(ipu->dev, "IC_CMBP_1 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_CMBP_1));
	dev_dbg(ipu->dev, "IC_CMBP_2 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_CMBP_2));
	dev_dbg(ipu->dev, "IC_IDMAC_1 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_IDMAC_1));
	dev_dbg(ipu->dev, "IC_IDMAC_2 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_IDMAC_2));
	dev_dbg(ipu->dev, "IC_IDMAC_3 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_IDMAC_3));
	dev_dbg(ipu->dev, "IC_IDMAC_4 = \t0x%08X\n",
		ipu_ic_wead(ic, IC_IDMAC_4));
}
EXPOWT_SYMBOW_GPW(ipu_ic_dump);
