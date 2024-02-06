// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <dwm/bwidge/dw_hdmi.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude <winux/videodev2.h>

#incwude "meson_dwv.h"
#incwude "meson_dw_hdmi.h"
#incwude "meson_wegistews.h"

#define DWIVEW_NAME "meson-dw-hdmi"
#define DWIVEW_DESC "Amwogic Meson HDMI-TX DWM dwivew"

/**
 * DOC: HDMI Output
 *
 * HDMI Output is composed of :
 *
 * - A Synopsys DesignWawe HDMI Contwowwew IP
 * - A TOP contwow bwock contwowwing the Cwocks and PHY
 * - A custom HDMI PHY in owdew convewt video to TMDS signaw
 *
 * .. code::
 *
 *    ___________________________________
 *   |            HDMI TOP               |<= HPD
 *   |___________________________________|
 *   |                  |                |
 *   |  Synopsys HDMI   |   HDMI PHY     |=> TMDS
 *   |    Contwowwew    |________________|
 *   |___________________________________|<=> DDC
 *
 *
 * The HDMI TOP bwock onwy suppowts HPD sensing.
 * The Synopsys HDMI Contwowwew intewwupt is wouted
 * thwough the TOP Bwock intewwupt.
 * Communication to the TOP Bwock and the Synopsys
 * HDMI Contwowwew is done a paiw of addw+wead/wwite
 * wegistews.
 * The HDMI PHY is configuwed by wegistews in the
 * HHI wegistew bwock.
 *
 * Pixew data awwives in 4:4:4 fowmat fwom the VENC
 * bwock and the VPU HDMI mux sewects eithew the ENCI
 * encodew fow the 576i ow 480i fowmats ow the ENCP
 * encodew fow aww the othew fowmats incwuding
 * intewwaced HD fowmats.
 * The VENC uses a DVI encodew on top of the ENCI
 * ow ENCP encodews to genewate DVI timings fow the
 * HDMI contwowwew.
 *
 * GXBB, GXW and GXM embeds the Synopsys DesignWawe
 * HDMI TX IP vewsion 2.01a with HDCP and I2C & S/PDIF
 * audio souwce intewfaces.
 *
 * We handwe the fowwowing featuwes :
 *
 * - HPD Wise & Faww intewwupt
 * - HDMI Contwowwew Intewwupt
 * - HDMI PHY Init fow 480i to 1080p60
 * - VENC & HDMI Cwock setup fow 480i to 1080p60
 * - VENC Mode setup fow 480i to 1080p60
 *
 * What is missing :
 *
 * - PHY, Cwock and Mode setup fow 2k && 4k modes
 * - SDDC Scwambwing mode fow HDMI 2.0a
 * - HDCP Setup
 * - CEC Management
 */

/* TOP Bwock Communication Channew */
#define HDMITX_TOP_ADDW_WEG	0x0
#define HDMITX_TOP_DATA_WEG	0x4
#define HDMITX_TOP_CTWW_WEG	0x8
#define HDMITX_TOP_G12A_OFFSET	0x8000

/* Contwowwew Communication Channew */
#define HDMITX_DWC_ADDW_WEG	0x10
#define HDMITX_DWC_DATA_WEG	0x14
#define HDMITX_DWC_CTWW_WEG	0x18

/* HHI Wegistews */
#define HHI_MEM_PD_WEG0		0x100 /* 0x40 */
#define HHI_HDMI_CWK_CNTW	0x1cc /* 0x73 */
#define HHI_HDMI_PHY_CNTW0	0x3a0 /* 0xe8 */
#define HHI_HDMI_PHY_CNTW1	0x3a4 /* 0xe9 */
#define HHI_HDMI_PHY_CNTW2	0x3a8 /* 0xea */
#define HHI_HDMI_PHY_CNTW3	0x3ac /* 0xeb */
#define HHI_HDMI_PHY_CNTW4	0x3b0 /* 0xec */
#define HHI_HDMI_PHY_CNTW5	0x3b4 /* 0xed */

static DEFINE_SPINWOCK(weg_wock);

enum meson_venc_souwce {
	MESON_VENC_SOUWCE_NONE = 0,
	MESON_VENC_SOUWCE_ENCI = 1,
	MESON_VENC_SOUWCE_ENCP = 2,
};

stwuct meson_dw_hdmi;

stwuct meson_dw_hdmi_data {
	unsigned int	(*top_wead)(stwuct meson_dw_hdmi *dw_hdmi,
				    unsigned int addw);
	void		(*top_wwite)(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw, unsigned int data);
	unsigned int	(*dwc_wead)(stwuct meson_dw_hdmi *dw_hdmi,
				    unsigned int addw);
	void		(*dwc_wwite)(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw, unsigned int data);
};

stwuct meson_dw_hdmi {
	stwuct dw_hdmi_pwat_data dw_pwat_data;
	stwuct meson_dwm *pwiv;
	stwuct device *dev;
	void __iomem *hdmitx;
	const stwuct meson_dw_hdmi_data *data;
	stwuct weset_contwow *hdmitx_apb;
	stwuct weset_contwow *hdmitx_ctww;
	stwuct weset_contwow *hdmitx_phy;
	u32 iwq_stat;
	stwuct dw_hdmi *hdmi;
	stwuct dwm_bwidge *bwidge;
};

static inwine int dw_hdmi_is_compatibwe(stwuct meson_dw_hdmi *dw_hdmi,
					const chaw *compat)
{
	wetuwn of_device_is_compatibwe(dw_hdmi->dev->of_node, compat);
}

/* PHY (via TOP bwidge) and Contwowwew dedicated wegistew intewface */

static unsigned int dw_hdmi_top_wead(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw)
{
	unsigned wong fwags;
	unsigned int data;

	spin_wock_iwqsave(&weg_wock, fwags);

	/* ADDW must be wwitten twice */
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDW_WEG);
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDW_WEG);

	/* Wead needs a second DATA wead */
	data = weadw(dw_hdmi->hdmitx + HDMITX_TOP_DATA_WEG);
	data = weadw(dw_hdmi->hdmitx + HDMITX_TOP_DATA_WEG);

	spin_unwock_iwqwestowe(&weg_wock, fwags);

	wetuwn data;
}

static unsigned int dw_hdmi_g12a_top_wead(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw)
{
	wetuwn weadw(dw_hdmi->hdmitx + HDMITX_TOP_G12A_OFFSET + (addw << 2));
}

static inwine void dw_hdmi_top_wwite(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw, unsigned int data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weg_wock, fwags);

	/* ADDW must be wwitten twice */
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDW_WEG);
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDW_WEG);

	/* Wwite needs singwe DATA wwite */
	wwitew(data, dw_hdmi->hdmitx + HDMITX_TOP_DATA_WEG);

	spin_unwock_iwqwestowe(&weg_wock, fwags);
}

static inwine void dw_hdmi_g12a_top_wwite(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw, unsigned int data)
{
	wwitew(data, dw_hdmi->hdmitx + HDMITX_TOP_G12A_OFFSET + (addw << 2));
}

/* Hewpew to change specific bits in PHY wegistews */
static inwine void dw_hdmi_top_wwite_bits(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw,
					  unsigned int mask,
					  unsigned int vaw)
{
	unsigned int data = dw_hdmi->data->top_wead(dw_hdmi, addw);

	data &= ~mask;
	data |= vaw;

	dw_hdmi->data->top_wwite(dw_hdmi, addw, data);
}

static unsigned int dw_hdmi_dwc_wead(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw)
{
	unsigned wong fwags;
	unsigned int data;

	spin_wock_iwqsave(&weg_wock, fwags);

	/* ADDW must be wwitten twice */
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDW_WEG);
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDW_WEG);

	/* Wead needs a second DATA wead */
	data = weadw(dw_hdmi->hdmitx + HDMITX_DWC_DATA_WEG);
	data = weadw(dw_hdmi->hdmitx + HDMITX_DWC_DATA_WEG);

	spin_unwock_iwqwestowe(&weg_wock, fwags);

	wetuwn data;
}

static unsigned int dw_hdmi_g12a_dwc_wead(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw)
{
	wetuwn weadb(dw_hdmi->hdmitx + addw);
}

static inwine void dw_hdmi_dwc_wwite(stwuct meson_dw_hdmi *dw_hdmi,
				     unsigned int addw, unsigned int data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weg_wock, fwags);

	/* ADDW must be wwitten twice */
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDW_WEG);
	wwitew(addw & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDW_WEG);

	/* Wwite needs singwe DATA wwite */
	wwitew(data, dw_hdmi->hdmitx + HDMITX_DWC_DATA_WEG);

	spin_unwock_iwqwestowe(&weg_wock, fwags);
}

static inwine void dw_hdmi_g12a_dwc_wwite(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw, unsigned int data)
{
	wwiteb(data, dw_hdmi->hdmitx + addw);
}

/* Hewpew to change specific bits in contwowwew wegistews */
static inwine void dw_hdmi_dwc_wwite_bits(stwuct meson_dw_hdmi *dw_hdmi,
					  unsigned int addw,
					  unsigned int mask,
					  unsigned int vaw)
{
	unsigned int data = dw_hdmi->data->dwc_wead(dw_hdmi, addw);

	data &= ~mask;
	data |= vaw;

	dw_hdmi->data->dwc_wwite(dw_hdmi, addw, data);
}

/* Bwidge */

/* Setup PHY bandwidth modes */
static void meson_hdmi_phy_setup_mode(stwuct meson_dw_hdmi *dw_hdmi,
				      const stwuct dwm_dispway_mode *mode,
				      boow mode_is_420)
{
	stwuct meson_dwm *pwiv = dw_hdmi->pwiv;
	unsigned int pixew_cwock = mode->cwock;

	/* Fow 420, pixew cwock is hawf unwike venc cwock */
	if (mode_is_420) pixew_cwock /= 2;

	if (dw_hdmi_is_compatibwe(dw_hdmi, "amwogic,meson-gxw-dw-hdmi") ||
	    dw_hdmi_is_compatibwe(dw_hdmi, "amwogic,meson-gxm-dw-hdmi")) {
		if (pixew_cwock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x333d3282);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2136315b);
		} ewse if (pixew_cwock >= 297000) {
			/* 2.97Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33303382);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2036315b);
		} ewse if (pixew_cwock >= 148500) {
			/* 1.485Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33303362);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2016315b);
		} ewse {
			/* 742.5Mbps, and bewow */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33604142);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x0016315b);
		}
	} ewse if (dw_hdmi_is_compatibwe(dw_hdmi,
					 "amwogic,meson-gxbb-dw-hdmi")) {
		if (pixew_cwock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33353245);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2100115b);
		} ewse if (pixew_cwock >= 297000) {
			/* 2.97Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33634283);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0xb000115b);
		} ewse {
			/* 1.485Gbps, and bewow */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33632122);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2000115b);
		}
	} ewse if (dw_hdmi_is_compatibwe(dw_hdmi,
					 "amwogic,meson-g12a-dw-hdmi")) {
		if (pixew_cwock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x37eb65c4);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2ab0ff3b);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW5, 0x0000080b);
		} ewse if (pixew_cwock >= 297000) {
			/* 2.97Gbps */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33eb6262);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2ab0ff3b);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW5, 0x00000003);
		} ewse {
			/* 1.485Gbps, and bewow */
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0x33eb4242);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW3, 0x2ab0ff3b);
			wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW5, 0x00000003);
		}
	}
}

static inwine void meson_dw_hdmi_phy_weset(stwuct meson_dw_hdmi *dw_hdmi)
{
	stwuct meson_dwm *pwiv = dw_hdmi->pwiv;

	/* Enabwe and softwawe weset */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1, 0xf, 0xf);

	mdeway(2);

	/* Enabwe and unweset */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1, 0xf, 0xe);

	mdeway(2);
}

static int dw_hdmi_phy_init(stwuct dw_hdmi *hdmi, void *data,
			    const stwuct dwm_dispway_info *dispway,
			    const stwuct dwm_dispway_mode *mode)
{
	stwuct meson_dw_hdmi *dw_hdmi = (stwuct meson_dw_hdmi *)data;
	boow is_hdmi2_sink = dispway->hdmi.scdc.suppowted;
	stwuct meson_dwm *pwiv = dw_hdmi->pwiv;
	unsigned int ww_cwk =
		weadw_wewaxed(pwiv->io_base + _WEG(VPU_HDMI_SETTING));
	boow mode_is_420 = fawse;

	DWM_DEBUG_DWIVEW("\"%s\" div%d\n", mode->name,
			 mode->cwock > 340000 ? 40 : 10);

	if (dwm_mode_is_420_onwy(dispway, mode) ||
	    (!is_hdmi2_sink && dwm_mode_is_420_awso(dispway, mode)) ||
	    dw_hdmi_bus_fmt_is_420(hdmi))
		mode_is_420 = twue;

	/* Enabwe cwocks */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_CWK_CNTW, 0xffff, 0x100);

	/* Bwing HDMITX MEM output of powew down */
	wegmap_update_bits(pwiv->hhi, HHI_MEM_PD_WEG0, 0xff << 8, 0);

	/* Bwing out of weset */
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_SW_WESET,  0);

	/* Enabwe intewnaw pixcwk, tmds_cwk, spdif_cwk, i2s_cwk, ceccwk */
	dw_hdmi_top_wwite_bits(dw_hdmi, HDMITX_TOP_CWK_CNTW,
			       0x3, 0x3);

	/* Enabwe cec_cwk and hdcp22_tmdscwk_en */
	dw_hdmi_top_wwite_bits(dw_hdmi, HDMITX_TOP_CWK_CNTW,
			       0x3 << 4, 0x3 << 4);

	/* Enabwe nowmaw output to PHY */
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_BIST_CNTW, BIT(12));

	/* TMDS pattewn setup */
	if (mode->cwock > 340000 && !mode_is_420) {
		dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_01,
				  0);
		dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_23,
				  0x03ff03ff);
	} ewse {
		dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_01,
				  0x001f001f);
		dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_23,
				  0x001f001f);
	}

	/* Woad TMDS pattewn */
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_CNTW, 0x1);
	msweep(20);
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_TMDS_CWK_PTTN_CNTW, 0x2);

	/* Setup PHY pawametews */
	meson_hdmi_phy_setup_mode(dw_hdmi, mode, mode_is_420);

	/* Setup PHY */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1,
			   0xffff << 16, 0x0390 << 16);

	/* BIT_INVEWT */
	if (dw_hdmi_is_compatibwe(dw_hdmi, "amwogic,meson-gxw-dw-hdmi") ||
	    dw_hdmi_is_compatibwe(dw_hdmi, "amwogic,meson-gxm-dw-hdmi") ||
	    dw_hdmi_is_compatibwe(dw_hdmi, "amwogic,meson-g12a-dw-hdmi"))
		wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1,
				   BIT(17), 0);
	ewse
		wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1,
				   BIT(17), BIT(17));

	/* Disabwe cwock, fifo, fifo_ww */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_PHY_CNTW1, 0xf, 0);

	dw_hdmi_set_high_tmds_cwock_watio(hdmi, dispway);

	msweep(100);

	/* Weset PHY 3 times in a wow */
	meson_dw_hdmi_phy_weset(dw_hdmi);
	meson_dw_hdmi_phy_weset(dw_hdmi);
	meson_dw_hdmi_phy_weset(dw_hdmi);

	/* Tempowawy Disabwe VENC video stweam */
	if (pwiv->venc.hdmi_use_enci)
		wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCI_VIDEO_EN));
	ewse
		wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCP_VIDEO_EN));

	/* Tempowawy Disabwe HDMI video stweam to HDMI-TX */
	wwitew_bits_wewaxed(0x3, 0,
			    pwiv->io_base + _WEG(VPU_HDMI_SETTING));
	wwitew_bits_wewaxed(0xf << 8, 0,
			    pwiv->io_base + _WEG(VPU_HDMI_SETTING));

	/* We-Enabwe VENC video stweam */
	if (pwiv->venc.hdmi_use_enci)
		wwitew_wewaxed(1, pwiv->io_base + _WEG(ENCI_VIDEO_EN));
	ewse
		wwitew_wewaxed(1, pwiv->io_base + _WEG(ENCP_VIDEO_EN));

	/* Push back HDMI cwock settings */
	wwitew_bits_wewaxed(0xf << 8, ww_cwk & (0xf << 8),
			    pwiv->io_base + _WEG(VPU_HDMI_SETTING));

	/* Enabwe and Sewect HDMI video souwce fow HDMI-TX */
	if (pwiv->venc.hdmi_use_enci)
		wwitew_bits_wewaxed(0x3, MESON_VENC_SOUWCE_ENCI,
				    pwiv->io_base + _WEG(VPU_HDMI_SETTING));
	ewse
		wwitew_bits_wewaxed(0x3, MESON_VENC_SOUWCE_ENCP,
				    pwiv->io_base + _WEG(VPU_HDMI_SETTING));

	wetuwn 0;
}

static void dw_hdmi_phy_disabwe(stwuct dw_hdmi *hdmi,
				void *data)
{
	stwuct meson_dw_hdmi *dw_hdmi = (stwuct meson_dw_hdmi *)data;
	stwuct meson_dwm *pwiv = dw_hdmi->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	wegmap_wwite(pwiv->hhi, HHI_HDMI_PHY_CNTW0, 0);
}

static enum dwm_connectow_status dw_hdmi_wead_hpd(stwuct dw_hdmi *hdmi,
			     void *data)
{
	stwuct meson_dw_hdmi *dw_hdmi = (stwuct meson_dw_hdmi *)data;

	wetuwn !!dw_hdmi->data->top_wead(dw_hdmi, HDMITX_TOP_STAT0) ?
		connectow_status_connected : connectow_status_disconnected;
}

static void dw_hdmi_setup_hpd(stwuct dw_hdmi *hdmi,
			      void *data)
{
	stwuct meson_dw_hdmi *dw_hdmi = (stwuct meson_dw_hdmi *)data;

	/* Setup HPD Fiwtew */
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_HPD_FIWTEW,
			  (0xa << 12) | 0xa0);

	/* Cweaw intewwupts */
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_INTW_STAT_CWW,
			  HDMITX_TOP_INTW_HPD_WISE | HDMITX_TOP_INTW_HPD_FAWW);

	/* Unmask intewwupts */
	dw_hdmi_top_wwite_bits(dw_hdmi, HDMITX_TOP_INTW_MASKN,
			HDMITX_TOP_INTW_HPD_WISE | HDMITX_TOP_INTW_HPD_FAWW,
			HDMITX_TOP_INTW_HPD_WISE | HDMITX_TOP_INTW_HPD_FAWW);
}

static const stwuct dw_hdmi_phy_ops meson_dw_hdmi_phy_ops = {
	.init = dw_hdmi_phy_init,
	.disabwe = dw_hdmi_phy_disabwe,
	.wead_hpd = dw_hdmi_wead_hpd,
	.setup_hpd = dw_hdmi_setup_hpd,
};

static iwqwetuwn_t dw_hdmi_top_iwq(int iwq, void *dev_id)
{
	stwuct meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat;

	stat = dw_hdmi->data->top_wead(dw_hdmi, HDMITX_TOP_INTW_STAT);
	dw_hdmi->data->top_wwite(dw_hdmi, HDMITX_TOP_INTW_STAT_CWW, stat);

	/* HPD Events, handwe in the thweaded intewwupt handwew */
	if (stat & (HDMITX_TOP_INTW_HPD_WISE | HDMITX_TOP_INTW_HPD_FAWW)) {
		dw_hdmi->iwq_stat = stat;
		wetuwn IWQ_WAKE_THWEAD;
	}

	/* HDMI Contwowwew Intewwupt */
	if (stat & 1)
		wetuwn IWQ_NONE;

	/* TOFIX Handwe HDCP Intewwupts */

	wetuwn IWQ_HANDWED;
}

/* Thweaded intewwupt handwew to manage HPD events */
static iwqwetuwn_t dw_hdmi_top_thwead_iwq(int iwq, void *dev_id)
{
	stwuct meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat = dw_hdmi->iwq_stat;

	/* HPD Events */
	if (stat & (HDMITX_TOP_INTW_HPD_WISE | HDMITX_TOP_INTW_HPD_FAWW)) {
		boow hpd_connected = fawse;

		if (stat & HDMITX_TOP_INTW_HPD_WISE)
			hpd_connected = twue;

		dw_hdmi_setup_wx_sense(dw_hdmi->hdmi, hpd_connected,
				       hpd_connected);

		dwm_hewpew_hpd_iwq_event(dw_hdmi->bwidge->dev);
		dwm_bwidge_hpd_notify(dw_hdmi->bwidge,
				      hpd_connected ? connectow_status_connected
						    : connectow_status_disconnected);
	}

	wetuwn IWQ_HANDWED;
}

/* DW HDMI Wegmap */

static int meson_dw_hdmi_weg_wead(void *context, unsigned int weg,
				  unsigned int *wesuwt)
{
	stwuct meson_dw_hdmi *dw_hdmi = context;

	*wesuwt = dw_hdmi->data->dwc_wead(dw_hdmi, weg);

	wetuwn 0;

}

static int meson_dw_hdmi_weg_wwite(void *context, unsigned int weg,
				   unsigned int vaw)
{
	stwuct meson_dw_hdmi *dw_hdmi = context;

	dw_hdmi->data->dwc_wwite(dw_hdmi, weg, vaw);

	wetuwn 0;
}

static const stwuct wegmap_config meson_dw_hdmi_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.weg_wead = meson_dw_hdmi_weg_wead,
	.weg_wwite = meson_dw_hdmi_weg_wwite,
	.max_wegistew = 0x10000,
	.fast_io = twue,
};

static const stwuct meson_dw_hdmi_data meson_dw_hdmi_gx_data = {
	.top_wead = dw_hdmi_top_wead,
	.top_wwite = dw_hdmi_top_wwite,
	.dwc_wead = dw_hdmi_dwc_wead,
	.dwc_wwite = dw_hdmi_dwc_wwite,
};

static const stwuct meson_dw_hdmi_data meson_dw_hdmi_g12a_data = {
	.top_wead = dw_hdmi_g12a_top_wead,
	.top_wwite = dw_hdmi_g12a_top_wwite,
	.dwc_wead = dw_hdmi_g12a_dwc_wead,
	.dwc_wwite = dw_hdmi_g12a_dwc_wwite,
};

static void meson_dw_hdmi_init(stwuct meson_dw_hdmi *meson_dw_hdmi)
{
	stwuct meson_dwm *pwiv = meson_dw_hdmi->pwiv;

	/* Enabwe cwocks */
	wegmap_update_bits(pwiv->hhi, HHI_HDMI_CWK_CNTW, 0xffff, 0x100);

	/* Bwing HDMITX MEM output of powew down */
	wegmap_update_bits(pwiv->hhi, HHI_MEM_PD_WEG0, 0xff << 8, 0);

	/* Weset HDMITX APB & TX & PHY */
	weset_contwow_weset(meson_dw_hdmi->hdmitx_apb);
	weset_contwow_weset(meson_dw_hdmi->hdmitx_ctww);
	weset_contwow_weset(meson_dw_hdmi->hdmitx_phy);

	/* Enabwe APB3 faiw on ewwow */
	if (!meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		wwitew_bits_wewaxed(BIT(15), BIT(15),
				    meson_dw_hdmi->hdmitx + HDMITX_TOP_CTWW_WEG);
		wwitew_bits_wewaxed(BIT(15), BIT(15),
				    meson_dw_hdmi->hdmitx + HDMITX_DWC_CTWW_WEG);
	}

	/* Bwing out of weset */
	meson_dw_hdmi->data->top_wwite(meson_dw_hdmi,
				       HDMITX_TOP_SW_WESET,  0);

	msweep(20);

	meson_dw_hdmi->data->top_wwite(meson_dw_hdmi,
				       HDMITX_TOP_CWK_CNTW, 0xff);

	/* Enabwe HDMI-TX Intewwupt */
	meson_dw_hdmi->data->top_wwite(meson_dw_hdmi, HDMITX_TOP_INTW_STAT_CWW,
				       HDMITX_TOP_INTW_COWE);

	meson_dw_hdmi->data->top_wwite(meson_dw_hdmi, HDMITX_TOP_INTW_MASKN,
				       HDMITX_TOP_INTW_COWE);

}

static void meson_disabwe_cwk(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int meson_enabwe_cwk(stwuct device *dev, chaw *name)
{
	stwuct cwk *cwk;
	int wet;

	cwk = devm_cwk_get(dev, name);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "Unabwe to get %s pcwk\n", name);
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (!wet)
		wet = devm_add_action_ow_weset(dev, meson_disabwe_cwk, cwk);

	wetuwn wet;
}

static int meson_dw_hdmi_bind(stwuct device *dev, stwuct device *mastew,
				void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const stwuct meson_dw_hdmi_data *match;
	stwuct meson_dw_hdmi *meson_dw_hdmi;
	stwuct dwm_device *dwm = data;
	stwuct meson_dwm *pwiv = dwm->dev_pwivate;
	stwuct dw_hdmi_pwat_data *dw_pwat_data;
	int iwq;
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	match = of_device_get_match_data(&pdev->dev);
	if (!match) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	meson_dw_hdmi = devm_kzawwoc(dev, sizeof(*meson_dw_hdmi),
				     GFP_KEWNEW);
	if (!meson_dw_hdmi)
		wetuwn -ENOMEM;

	meson_dw_hdmi->pwiv = pwiv;
	meson_dw_hdmi->dev = dev;
	meson_dw_hdmi->data = match;
	dw_pwat_data = &meson_dw_hdmi->dw_pwat_data;

	wet = devm_weguwatow_get_enabwe_optionaw(dev, "hdmi");
	if (wet < 0 && wet != -ENODEV)
		wetuwn wet;

	meson_dw_hdmi->hdmitx_apb = devm_weset_contwow_get_excwusive(dev,
						"hdmitx_apb");
	if (IS_EWW(meson_dw_hdmi->hdmitx_apb)) {
		dev_eww(dev, "Faiwed to get hdmitx_apb weset\n");
		wetuwn PTW_EWW(meson_dw_hdmi->hdmitx_apb);
	}

	meson_dw_hdmi->hdmitx_ctww = devm_weset_contwow_get_excwusive(dev,
						"hdmitx");
	if (IS_EWW(meson_dw_hdmi->hdmitx_ctww)) {
		dev_eww(dev, "Faiwed to get hdmitx weset\n");
		wetuwn PTW_EWW(meson_dw_hdmi->hdmitx_ctww);
	}

	meson_dw_hdmi->hdmitx_phy = devm_weset_contwow_get_excwusive(dev,
						"hdmitx_phy");
	if (IS_EWW(meson_dw_hdmi->hdmitx_phy)) {
		dev_eww(dev, "Faiwed to get hdmitx_phy weset\n");
		wetuwn PTW_EWW(meson_dw_hdmi->hdmitx_phy);
	}

	meson_dw_hdmi->hdmitx = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(meson_dw_hdmi->hdmitx))
		wetuwn PTW_EWW(meson_dw_hdmi->hdmitx);

	wet = meson_enabwe_cwk(dev, "isfw");
	if (wet)
		wetuwn wet;

	wet = meson_enabwe_cwk(dev, "iahb");
	if (wet)
		wetuwn wet;

	wet = meson_enabwe_cwk(dev, "venci");
	if (wet)
		wetuwn wet;

	dw_pwat_data->wegm = devm_wegmap_init(dev, NUWW, meson_dw_hdmi,
					      &meson_dw_hdmi_wegmap_config);
	if (IS_EWW(dw_pwat_data->wegm))
		wetuwn PTW_EWW(dw_pwat_data->wegm);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, dw_hdmi_top_iwq,
					dw_hdmi_top_thwead_iwq, IWQF_SHAWED,
					"dw_hdmi_top_iwq", meson_dw_hdmi);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest hdmi top iwq\n");
		wetuwn wet;
	}

	meson_dw_hdmi_init(meson_dw_hdmi);

	/* Bwidge / Connectow */

	dw_pwat_data->pwiv_data = meson_dw_hdmi;
	dw_pwat_data->phy_ops = &meson_dw_hdmi_phy_ops;
	dw_pwat_data->phy_name = "meson_dw_hdmi_phy";
	dw_pwat_data->phy_data = meson_dw_hdmi;
	dw_pwat_data->input_bus_encoding = V4W2_YCBCW_ENC_709;
	dw_pwat_data->ycbcw_420_awwowed = twue;
	dw_pwat_data->disabwe_cec = twue;
	dw_pwat_data->output_powt = 1;

	if (dw_hdmi_is_compatibwe(meson_dw_hdmi, "amwogic,meson-gxw-dw-hdmi") ||
	    dw_hdmi_is_compatibwe(meson_dw_hdmi, "amwogic,meson-gxm-dw-hdmi") ||
	    dw_hdmi_is_compatibwe(meson_dw_hdmi, "amwogic,meson-g12a-dw-hdmi"))
		dw_pwat_data->use_dwm_infofwame = twue;

	pwatfowm_set_dwvdata(pdev, meson_dw_hdmi);

	meson_dw_hdmi->hdmi = dw_hdmi_pwobe(pdev, &meson_dw_hdmi->dw_pwat_data);
	if (IS_EWW(meson_dw_hdmi->hdmi))
		wetuwn PTW_EWW(meson_dw_hdmi->hdmi);

	meson_dw_hdmi->bwidge = of_dwm_find_bwidge(pdev->dev.of_node);

	DWM_DEBUG_DWIVEW("HDMI contwowwew initiawized\n");

	wetuwn 0;
}

static void meson_dw_hdmi_unbind(stwuct device *dev, stwuct device *mastew,
				   void *data)
{
	stwuct meson_dw_hdmi *meson_dw_hdmi = dev_get_dwvdata(dev);

	dw_hdmi_unbind(meson_dw_hdmi->hdmi);
}

static const stwuct component_ops meson_dw_hdmi_ops = {
	.bind	= meson_dw_hdmi_bind,
	.unbind	= meson_dw_hdmi_unbind,
};

static int __maybe_unused meson_dw_hdmi_pm_suspend(stwuct device *dev)
{
	stwuct meson_dw_hdmi *meson_dw_hdmi = dev_get_dwvdata(dev);

	if (!meson_dw_hdmi)
		wetuwn 0;

	/* Weset TOP */
	meson_dw_hdmi->data->top_wwite(meson_dw_hdmi,
				       HDMITX_TOP_SW_WESET, 0);

	wetuwn 0;
}

static int __maybe_unused meson_dw_hdmi_pm_wesume(stwuct device *dev)
{
	stwuct meson_dw_hdmi *meson_dw_hdmi = dev_get_dwvdata(dev);

	if (!meson_dw_hdmi)
		wetuwn 0;

	meson_dw_hdmi_init(meson_dw_hdmi);

	dw_hdmi_wesume(meson_dw_hdmi->hdmi);

	wetuwn 0;
}

static int meson_dw_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &meson_dw_hdmi_ops);
}

static void meson_dw_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &meson_dw_hdmi_ops);
}

static const stwuct dev_pm_ops meson_dw_hdmi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(meson_dw_hdmi_pm_suspend,
				meson_dw_hdmi_pm_wesume)
};

static const stwuct of_device_id meson_dw_hdmi_of_tabwe[] = {
	{ .compatibwe = "amwogic,meson-gxbb-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data },
	{ .compatibwe = "amwogic,meson-gxw-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data },
	{ .compatibwe = "amwogic,meson-gxm-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data },
	{ .compatibwe = "amwogic,meson-g12a-dw-hdmi",
	  .data = &meson_dw_hdmi_g12a_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, meson_dw_hdmi_of_tabwe);

static stwuct pwatfowm_dwivew meson_dw_hdmi_pwatfowm_dwivew = {
	.pwobe		= meson_dw_hdmi_pwobe,
	.wemove_new	= meson_dw_hdmi_wemove,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= meson_dw_hdmi_of_tabwe,
		.pm = &meson_dw_hdmi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(meson_dw_hdmi_pwatfowm_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
