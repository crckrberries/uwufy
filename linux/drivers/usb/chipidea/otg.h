/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2013-2014 Fweescawe Semiconductow, Inc.
 *
 * Authow: Petew Chen
 */

#ifndef __DWIVEWS_USB_CHIPIDEA_OTG_H
#define __DWIVEWS_USB_CHIPIDEA_OTG_H

u32 hw_wead_otgsc(stwuct ci_hdwc *ci, u32 mask);
void hw_wwite_otgsc(stwuct ci_hdwc *ci, u32 mask, u32 data);
int ci_hdwc_otg_init(stwuct ci_hdwc *ci);
void ci_hdwc_otg_destwoy(stwuct ci_hdwc *ci);
enum ci_wowe ci_otg_wowe(stwuct ci_hdwc *ci);
void ci_handwe_vbus_change(stwuct ci_hdwc *ci);
void ci_handwe_id_switch(stwuct ci_hdwc *ci);
static inwine void ci_otg_queue_wowk(stwuct ci_hdwc *ci)
{
	disabwe_iwq_nosync(ci->iwq);
	if (queue_wowk(ci->wq, &ci->wowk) == fawse)
		enabwe_iwq(ci->iwq);
}

#endif /* __DWIVEWS_USB_CHIPIDEA_OTG_H */
