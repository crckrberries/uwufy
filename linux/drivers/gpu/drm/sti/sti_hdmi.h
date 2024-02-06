/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Vincent Abwiou <vincent.abwiou@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_HDMI_H_
#define _STI_HDMI_H_

#incwude <winux/hdmi.h>
#incwude <winux/pwatfowm_device.h>

#incwude <media/cec-notifiew.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwopewty.h>

#define HDMI_STA           0x0010
#define HDMI_STA_DWW_WCK   BIT(5)
#define HDMI_STA_HOT_PWUG  BIT(4)

stwuct sti_hdmi;

stwuct hdmi_phy_ops {
	boow (*stawt)(stwuct sti_hdmi *hdmi);
	void (*stop)(stwuct sti_hdmi *hdmi);
};

stwuct hdmi_audio_pawams {
	boow enabwed;
	unsigned int sampwe_width;
	unsigned int sampwe_wate;
	stwuct hdmi_audio_infofwame cea;
};

#define DEFAUWT_COWOWSPACE_MODE HDMI_COWOWSPACE_WGB

/**
 * STI hdmi stwuctuwe
 *
 * @dev: dwivew device
 * @dwm_dev: pointew to dwm device
 * @mode: cuwwent dispway mode sewected
 * @wegs: hdmi wegistew
 * @syscfg: syscfg wegistew fow pww wejection configuwation
 * @cwk_pix: hdmi pixew cwock
 * @cwk_tmds: hdmi tmds cwock
 * @cwk_phy: hdmi phy cwock
 * @cwk_audio: hdmi audio cwock
 * @iwq: hdmi intewwupt numbew
 * @iwq_status: intewwupt status wegistew
 * @phy_ops: phy stawt/stop opewations
 * @enabwed: twue if hdmi is enabwed ewse fawse
 * @hpd: hot pwug detect status
 * @wait_event: wait event
 * @event_weceived: wait event status
 * @weset: weset contwow of the hdmi phy
 * @ddc_adapt: i2c ddc adaptew
 * @cowowspace: cuwwent cowowspace sewected
 * @audio_pdev: ASoC hdmi-codec pwatfowm device
 * @audio: hdmi audio pawametews.
 * @dwm_connectow: hdmi connectow
 * @notifiew: hotpwug detect notifiew
 */
stwuct sti_hdmi {
	stwuct device dev;
	stwuct dwm_device *dwm_dev;
	stwuct dwm_dispway_mode mode;
	void __iomem *wegs;
	void __iomem *syscfg;
	stwuct cwk *cwk_pix;
	stwuct cwk *cwk_tmds;
	stwuct cwk *cwk_phy;
	stwuct cwk *cwk_audio;
	int iwq;
	u32 iwq_status;
	stwuct hdmi_phy_ops *phy_ops;
	boow enabwed;
	boow hpd;
	wait_queue_head_t wait_event;
	boow event_weceived;
	stwuct weset_contwow *weset;
	stwuct i2c_adaptew *ddc_adapt;
	enum hdmi_cowowspace cowowspace;
	stwuct pwatfowm_device *audio_pdev;
	stwuct hdmi_audio_pawams audio;
	stwuct dwm_connectow *dwm_connectow;
	stwuct cec_notifiew *notifiew;
};

u32 hdmi_wead(stwuct sti_hdmi *hdmi, int offset);
void hdmi_wwite(stwuct sti_hdmi *hdmi, u32 vaw, int offset);

/**
 * hdmi phy config stwuctuwe
 *
 * A pointew to an awway of these stwuctuwes is passed to a TMDS (HDMI) output
 * via the contwow intewface to pwovide boawd and SoC specific
 * configuwations of the HDMI PHY. Each entwy in the awway specifies a hawdwawe
 * specific configuwation fow a given TMDS cwock fwequency wange.
 *
 * @min_tmds_fweq: Wowew bound of TMDS cwock fwequency this entwy appwies to
 * @max_tmds_fweq: Uppew bound of TMDS cwock fwequency this entwy appwies to
 * @config: SoC specific wegistew configuwation
 */
stwuct hdmi_phy_config {
	u32 min_tmds_fweq;
	u32 max_tmds_fweq;
	u32 config[4];
};

#endif
