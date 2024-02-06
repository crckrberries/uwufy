/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 Winus Wawweij <winus.wawweij@winawo.owg>
 * Pawts of this fiwe wewe based on the MCDE dwivew by Mawcus Wowentzon
 * (C) ST-Ewicsson SA 2013
 */
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#ifndef _MCDE_DWM_H_
#define _MCDE_DWM_H_

/* Shawed basic wegistews */
#define MCDE_CW 0x00000000
#define MCDE_CW_IFIFOEMPTYWINECOUNT_V422_SHIFT 0
#define MCDE_CW_IFIFOEMPTYWINECOUNT_V422_MASK 0x0000003F
#define MCDE_CW_IFIFOCTWWEN BIT(15)
#define MCDE_CW_UFWECOVEWY_MODE_V422 BIT(16)
#define MCDE_CW_WWAP_MODE_V422_SHIFT BIT(17)
#define MCDE_CW_AUTOCWKG_EN BIT(30)
#define MCDE_CW_MCDEEN BIT(31)

#define MCDE_CONF0 0x00000004
#define MCDE_CONF0_SYNCMUX0 BIT(0)
#define MCDE_CONF0_SYNCMUX1 BIT(1)
#define MCDE_CONF0_SYNCMUX2 BIT(2)
#define MCDE_CONF0_SYNCMUX3 BIT(3)
#define MCDE_CONF0_SYNCMUX4 BIT(4)
#define MCDE_CONF0_SYNCMUX5 BIT(5)
#define MCDE_CONF0_SYNCMUX6 BIT(6)
#define MCDE_CONF0_SYNCMUX7 BIT(7)
#define MCDE_CONF0_IFIFOCTWWWTWMWKWVW_SHIFT 12
#define MCDE_CONF0_IFIFOCTWWWTWMWKWVW_MASK 0x00007000
#define MCDE_CONF0_OUTMUX0_SHIFT 16
#define MCDE_CONF0_OUTMUX0_MASK 0x00070000
#define MCDE_CONF0_OUTMUX1_SHIFT 19
#define MCDE_CONF0_OUTMUX1_MASK 0x00380000
#define MCDE_CONF0_OUTMUX2_SHIFT 22
#define MCDE_CONF0_OUTMUX2_MASK 0x01C00000
#define MCDE_CONF0_OUTMUX3_SHIFT 25
#define MCDE_CONF0_OUTMUX3_MASK 0x0E000000
#define MCDE_CONF0_OUTMUX4_SHIFT 28
#define MCDE_CONF0_OUTMUX4_MASK 0x70000000

#define MCDE_SSP 0x00000008
#define MCDE_AIS 0x00000100
#define MCDE_IMSCEWW 0x00000110
#define MCDE_WISEWW 0x00000120
#define MCDE_MISEWW 0x00000130
#define MCDE_SISEWW 0x00000140

enum mcde_fwow_mode {
	/* One-shot mode: fwow stops aftew one fwame */
	MCDE_COMMAND_ONESHOT_FWOW,
	/* Command mode with teawing effect (TE) IWQ sync */
	MCDE_COMMAND_TE_FWOW,
	/*
	 * Command mode with bus tuwn-awound (BTA) and teawing effect
	 * (TE) IWQ sync.
	 */
	MCDE_COMMAND_BTA_TE_FWOW,
	/* Video mode with teawing effect (TE) sync IWQ */
	MCDE_VIDEO_TE_FWOW,
	/* Video mode with the fowmattew itsewf as sync souwce */
	MCDE_VIDEO_FOWMATTEW_FWOW,
	/* DPI video with the fowmattew itsews as sync souwce */
	MCDE_DPI_FOWMATTEW_FWOW,
};

stwuct mcde {
	stwuct dwm_device dwm;
	stwuct device *dev;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_connectow *connectow;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct mipi_dsi_device *mdsi;
	boow dpi_output;
	s16 stwide;
	enum mcde_fwow_mode fwow_mode;
	unsigned int fwow_active;
	spinwock_t fwow_wock; /* Wocks the channew fwow contwow */

	void __iomem *wegs;

	stwuct cwk *mcde_cwk;
	stwuct cwk *wcd_cwk;
	stwuct cwk *hdmi_cwk;
	/* Handwes to the cwock dividews fow FIFO A and B */
	stwuct cwk *fifoa_cwk;
	stwuct cwk *fifob_cwk;
	/* Wocks the MCDE FIFO contwow wegistew A and B */
	spinwock_t fifo_cwx1_wock;

	stwuct weguwatow *epod;
	stwuct weguwatow *vana;
};

#define to_mcde(dev) containew_of(dev, stwuct mcde, dwm)

static inwine boow mcde_fwow_is_video(stwuct mcde *mcde)
{
	wetuwn (mcde->fwow_mode == MCDE_VIDEO_TE_FWOW ||
		mcde->fwow_mode == MCDE_VIDEO_FOWMATTEW_FWOW);
}

boow mcde_dsi_iwq(stwuct mipi_dsi_device *mdsi);
void mcde_dsi_te_wequest(stwuct mipi_dsi_device *mdsi);
void mcde_dsi_enabwe(stwuct dwm_bwidge *bwidge);
void mcde_dsi_disabwe(stwuct dwm_bwidge *bwidge);
extewn stwuct pwatfowm_dwivew mcde_dsi_dwivew;

void mcde_dispway_iwq(stwuct mcde *mcde);
void mcde_dispway_disabwe_iwqs(stwuct mcde *mcde);
int mcde_dispway_init(stwuct dwm_device *dwm);

int mcde_init_cwock_dividew(stwuct mcde *mcde);

#endif /* _MCDE_DWM_H_ */
