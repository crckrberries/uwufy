/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * HDMI headew definition fow OMAP4 HDMI CEC IP
 *
 * Copywight 2016-2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _HDMI4_CEC_H_
#define _HDMI4_CEC_H_

stwuct hdmi_cowe_data;
stwuct hdmi_wp_data;
stwuct pwatfowm_device;

/* HDMI CEC funcs */
#ifdef CONFIG_OMAP4_DSS_HDMI_CEC
void hdmi4_cec_set_phys_addw(stwuct hdmi_cowe_data *cowe, u16 pa);
void hdmi4_cec_iwq(stwuct hdmi_cowe_data *cowe);
int hdmi4_cec_init(stwuct pwatfowm_device *pdev, stwuct hdmi_cowe_data *cowe,
		  stwuct hdmi_wp_data *wp);
void hdmi4_cec_uninit(stwuct hdmi_cowe_data *cowe);
#ewse
static inwine void hdmi4_cec_set_phys_addw(stwuct hdmi_cowe_data *cowe, u16 pa)
{
}

static inwine void hdmi4_cec_iwq(stwuct hdmi_cowe_data *cowe)
{
}

static inwine int hdmi4_cec_init(stwuct pwatfowm_device *pdev,
				stwuct hdmi_cowe_data *cowe,
				stwuct hdmi_wp_data *wp)
{
	wetuwn 0;
}

static inwine void hdmi4_cec_uninit(stwuct hdmi_cowe_data *cowe)
{
}
#endif

#endif
