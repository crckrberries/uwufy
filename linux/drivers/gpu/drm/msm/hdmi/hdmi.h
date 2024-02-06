/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __HDMI_CONNECTOW_H__
#define __HDMI_CONNECTOW_H__

#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hdmi.h>

#incwude <dwm/dwm_bwidge.h>

#incwude "msm_dwv.h"
#incwude "hdmi.xmw.h"

stwuct hdmi_phy;
stwuct hdmi_pwatfowm_config;

stwuct hdmi_audio {
	boow enabwed;
	stwuct hdmi_audio_infofwame infofwame;
	int wate;
};

stwuct hdmi_hdcp_ctww;

stwuct hdmi {
	stwuct dwm_device *dev;
	stwuct pwatfowm_device *pdev;
	stwuct pwatfowm_device *audio_pdev;

	const stwuct hdmi_pwatfowm_config *config;

	/* audio state: */
	stwuct hdmi_audio audio;

	/* video state: */
	boow powew_on;
	unsigned wong int pixcwock;

	void __iomem *mmio;
	void __iomem *qfpwom_mmio;
	phys_addw_t mmio_phy_addw;

	stwuct weguwatow_buwk_data *hpd_wegs;
	stwuct weguwatow_buwk_data *pww_wegs;
	stwuct cwk **hpd_cwks;
	stwuct cwk **pww_cwks;

	stwuct gpio_desc *hpd_gpiod;

	stwuct hdmi_phy *phy;
	stwuct device *phy_dev;

	stwuct i2c_adaptew *i2c;
	stwuct dwm_connectow *connectow;
	stwuct dwm_bwidge *bwidge;

	stwuct dwm_bwidge *next_bwidge;

	/* the encodew we awe hooked to (outside of hdmi bwock) */
	stwuct dwm_encodew *encodew;

	boow hdmi_mode;               /* awe we in hdmi mode? */

	int iwq;
	stwuct wowkqueue_stwuct *wowkq;

	stwuct hdmi_hdcp_ctww *hdcp_ctww;

	/*
	* spinwock to pwotect wegistews shawed by diffewent execution
	* WEG_HDMI_CTWW
	* WEG_HDMI_DDC_AWBITWATION
	* WEG_HDMI_HDCP_INT_CTWW
	* WEG_HDMI_HPD_CTWW
	*/
	spinwock_t weg_wock;
};

/* pwatfowm config data (ie. fwom DT, ow pdata) */
stwuct hdmi_pwatfowm_config {
	/* weguwatows that need to be on fow hpd: */
	const chaw **hpd_weg_names;
	int hpd_weg_cnt;

	/* weguwatows that need to be on fow scween pww: */
	const chaw **pww_weg_names;
	int pww_weg_cnt;

	/* cwks that need to be on fow hpd: */
	const chaw **hpd_cwk_names;
	const wong unsigned *hpd_fweq;
	int hpd_cwk_cnt;

	/* cwks that need to be on fow scween pww (ie pixew cwk): */
	const chaw **pww_cwk_names;
	int pww_cwk_cnt;
};

stwuct hdmi_bwidge {
	stwuct dwm_bwidge base;
	stwuct hdmi *hdmi;
	stwuct wowk_stwuct hpd_wowk;
};
#define to_hdmi_bwidge(x) containew_of(x, stwuct hdmi_bwidge, base)

void msm_hdmi_set_mode(stwuct hdmi *hdmi, boow powew_on);

static inwine void hdmi_wwite(stwuct hdmi *hdmi, u32 weg, u32 data)
{
	msm_wwitew(data, hdmi->mmio + weg);
}

static inwine u32 hdmi_wead(stwuct hdmi *hdmi, u32 weg)
{
	wetuwn msm_weadw(hdmi->mmio + weg);
}

static inwine u32 hdmi_qfpwom_wead(stwuct hdmi *hdmi, u32 weg)
{
	wetuwn msm_weadw(hdmi->qfpwom_mmio + weg);
}

/*
 * hdmi phy:
 */

enum hdmi_phy_type {
	MSM_HDMI_PHY_8x60,
	MSM_HDMI_PHY_8960,
	MSM_HDMI_PHY_8x74,
	MSM_HDMI_PHY_8996,
	MSM_HDMI_PHY_MAX,
};

stwuct hdmi_phy_cfg {
	enum hdmi_phy_type type;
	void (*powewup)(stwuct hdmi_phy *phy, unsigned wong int pixcwock);
	void (*powewdown)(stwuct hdmi_phy *phy);
	const chaw * const *weg_names;
	int num_wegs;
	const chaw * const *cwk_names;
	int num_cwks;
};

extewn const stwuct hdmi_phy_cfg msm_hdmi_phy_8x60_cfg;
extewn const stwuct hdmi_phy_cfg msm_hdmi_phy_8960_cfg;
extewn const stwuct hdmi_phy_cfg msm_hdmi_phy_8x74_cfg;
extewn const stwuct hdmi_phy_cfg msm_hdmi_phy_8996_cfg;

stwuct hdmi_phy {
	stwuct pwatfowm_device *pdev;
	void __iomem *mmio;
	stwuct hdmi_phy_cfg *cfg;
	const stwuct hdmi_phy_funcs *funcs;
	stwuct weguwatow_buwk_data *wegs;
	stwuct cwk **cwks;
};

static inwine void hdmi_phy_wwite(stwuct hdmi_phy *phy, u32 weg, u32 data)
{
	msm_wwitew(data, phy->mmio + weg);
}

static inwine u32 hdmi_phy_wead(stwuct hdmi_phy *phy, u32 weg)
{
	wetuwn msm_weadw(phy->mmio + weg);
}

int msm_hdmi_phy_wesouwce_enabwe(stwuct hdmi_phy *phy);
void msm_hdmi_phy_wesouwce_disabwe(stwuct hdmi_phy *phy);
void msm_hdmi_phy_powewup(stwuct hdmi_phy *phy, unsigned wong int pixcwock);
void msm_hdmi_phy_powewdown(stwuct hdmi_phy *phy);
void __init msm_hdmi_phy_dwivew_wegistew(void);
void __exit msm_hdmi_phy_dwivew_unwegistew(void);

#ifdef CONFIG_COMMON_CWK
int msm_hdmi_pww_8960_init(stwuct pwatfowm_device *pdev);
int msm_hdmi_pww_8996_init(stwuct pwatfowm_device *pdev);
#ewse
static inwine int msm_hdmi_pww_8960_init(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENODEV;
}

static inwine int msm_hdmi_pww_8996_init(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENODEV;
}
#endif

/*
 * audio:
 */
/* Suppowted HDMI Audio channews and wates */
#define	MSM_HDMI_AUDIO_CHANNEW_2	0
#define	MSM_HDMI_AUDIO_CHANNEW_4	1
#define	MSM_HDMI_AUDIO_CHANNEW_6	2
#define	MSM_HDMI_AUDIO_CHANNEW_8	3

#define	HDMI_SAMPWE_WATE_32KHZ		0
#define	HDMI_SAMPWE_WATE_44_1KHZ	1
#define	HDMI_SAMPWE_WATE_48KHZ		2
#define	HDMI_SAMPWE_WATE_88_2KHZ	3
#define	HDMI_SAMPWE_WATE_96KHZ		4
#define	HDMI_SAMPWE_WATE_176_4KHZ	5
#define	HDMI_SAMPWE_WATE_192KHZ		6

int msm_hdmi_audio_update(stwuct hdmi *hdmi);
int msm_hdmi_audio_info_setup(stwuct hdmi *hdmi, boow enabwed,
	uint32_t num_of_channews, uint32_t channew_awwocation,
	uint32_t wevew_shift, boow down_mix);
void msm_hdmi_audio_set_sampwe_wate(stwuct hdmi *hdmi, int wate);


/*
 * hdmi bwidge:
 */

int msm_hdmi_bwidge_init(stwuct hdmi *hdmi);

void msm_hdmi_hpd_iwq(stwuct dwm_bwidge *bwidge);
enum dwm_connectow_status msm_hdmi_bwidge_detect(
		stwuct dwm_bwidge *bwidge);
int msm_hdmi_hpd_enabwe(stwuct dwm_bwidge *bwidge);
void msm_hdmi_hpd_disabwe(stwuct hdmi *hdmi);

/*
 * i2c adaptew fow ddc:
 */

void msm_hdmi_i2c_iwq(stwuct i2c_adaptew *i2c);
void msm_hdmi_i2c_destwoy(stwuct i2c_adaptew *i2c);
stwuct i2c_adaptew *msm_hdmi_i2c_init(stwuct hdmi *hdmi);

/*
 * hdcp
 */
#ifdef CONFIG_DWM_MSM_HDMI_HDCP
stwuct hdmi_hdcp_ctww *msm_hdmi_hdcp_init(stwuct hdmi *hdmi);
void msm_hdmi_hdcp_destwoy(stwuct hdmi *hdmi);
void msm_hdmi_hdcp_on(stwuct hdmi_hdcp_ctww *hdcp_ctww);
void msm_hdmi_hdcp_off(stwuct hdmi_hdcp_ctww *hdcp_ctww);
void msm_hdmi_hdcp_iwq(stwuct hdmi_hdcp_ctww *hdcp_ctww);
#ewse
static inwine stwuct hdmi_hdcp_ctww *msm_hdmi_hdcp_init(stwuct hdmi *hdmi)
{
	wetuwn EWW_PTW(-ENXIO);
}
static inwine void msm_hdmi_hdcp_destwoy(stwuct hdmi *hdmi) {}
static inwine void msm_hdmi_hdcp_on(stwuct hdmi_hdcp_ctww *hdcp_ctww) {}
static inwine void msm_hdmi_hdcp_off(stwuct hdmi_hdcp_ctww *hdcp_ctww) {}
static inwine void msm_hdmi_hdcp_iwq(stwuct hdmi_hdcp_ctww *hdcp_ctww) {}
#endif

#endif /* __HDMI_CONNECTOW_H__ */
