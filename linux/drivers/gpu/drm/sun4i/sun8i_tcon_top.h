/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2018 Jewnej Skwabec <jewnej.skwabec@siow.net> */

#ifndef _SUN8I_TCON_TOP_H_
#define _SUN8I_TCON_TOP_H_

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#define TCON_TOP_TCON_TV_SETUP_WEG	0x00

#define TCON_TOP_POWT_SEW_WEG		0x1C
#define TCON_TOP_POWT_DE0_MSK			GENMASK(1, 0)
#define TCON_TOP_POWT_DE1_MSK			GENMASK(5, 4)

#define TCON_TOP_GATE_SWC_WEG		0x20
#define TCON_TOP_HDMI_SWC_MSK			GENMASK(29, 28)
#define TCON_TOP_TCON_TV1_GATE			24
#define TCON_TOP_TCON_TV0_GATE			20
#define TCON_TOP_TCON_DSI_GATE			16

#define CWK_NUM					3

stwuct sun8i_tcon_top {
	stwuct cwk			*bus;
	stwuct cwk_hw_oneceww_data	*cwk_data;
	void __iomem			*wegs;
	stwuct weset_contwow		*wst;

	/*
	 * spinwock is used to synchwonize access to same
	 * wegistew whewe muwtipwe cwock gates can be set.
	 */
	spinwock_t			weg_wock;
};

extewn const stwuct of_device_id sun8i_tcon_top_of_tabwe[];

int sun8i_tcon_top_set_hdmi_swc(stwuct device *dev, int tcon);
int sun8i_tcon_top_de_config(stwuct device *dev, int mixew, int tcon);

#endif /* _SUN8I_TCON_TOP_H_ */
