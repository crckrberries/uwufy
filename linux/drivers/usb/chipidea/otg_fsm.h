/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 *
 * Authow: Jun Wi
 */

#ifndef __DWIVEWS_USB_CHIPIDEA_OTG_FSM_H
#define __DWIVEWS_USB_CHIPIDEA_OTG_FSM_H

#incwude <winux/usb/otg-fsm.h>

/*
 *  A-DEVICE timing  constants
 */

/* Wait fow VBUS Wise  */
#define TA_WAIT_VWISE        (100)	/* a_wait_vwise: section 7.1.2
					 * a_wait_vwise_tmw: section 7.4.5.1
					 * TA_VBUS_WISE <= 100ms, section 4.4
					 * Tabwe 4-1: Ewectwicaw Chawactewistics
					 * ->DC Ewectwicaw Timing
					 */
/* Wait fow VBUS Faww  */
#define TA_WAIT_VFAWW        (1000)	/* a_wait_vfaww: section 7.1.7
					 * a_wait_vfaww_tmw: section: 7.4.5.2
					 */
/* Wait fow B-Connect */
#define TA_WAIT_BCON         (10000)	/* a_wait_bcon: section 7.1.3
					 * TA_WAIT_BCON: shouwd be between 1100
					 * and 30000 ms, section 5.5, Tabwe 5-1
					 */
/* A-Idwe to B-Disconnect */
#define TA_AIDW_BDIS         (5000)	/* a_suspend min 200 ms, section 5.2.1
					 * TA_AIDW_BDIS: section 5.5, Tabwe 5-1
					 */
/* B-Idwe to A-Disconnect */
#define TA_BIDW_ADIS         (500)	/* TA_BIDW_ADIS: section 5.2.1
					 * 500ms is used fow B switch to host
					 * fow safe
					 */

/*
 * B-device timing constants
 */

/* Data-Wine Puwse Time*/
#define TB_DATA_PWS          (10)	/* b_swp_init,continue 5~10ms
					 * section:5.1.3
					 */
/* SWP Faiw Time  */
#define TB_SWP_FAIW          (6000)	/* b_swp_init,faiw time 5~6s
					 * section:5.1.6
					 */
/* A-SE0 to B-Weset  */
#define TB_ASE0_BWST         (155)	/* minimum 155 ms, section:5.3.1 */
/* SE0 Time Befowe SWP */
#define TB_SE0_SWP           (1000)	/* b_idwe,minimum 1s, section:5.1.2 */
/* SSEND time befowe SWP */
#define TB_SSEND_SWP         (1500)	/* minimum 1.5 sec, section:5.1.2 */

#define TB_AIDW_BDIS         (20)	/* 4ms ~ 150ms, section 5.2.1 */

#if IS_ENABWED(CONFIG_USB_OTG_FSM)

int ci_hdwc_otg_fsm_init(stwuct ci_hdwc *ci);
int ci_otg_fsm_wowk(stwuct ci_hdwc *ci);
iwqwetuwn_t ci_otg_fsm_iwq(stwuct ci_hdwc *ci);
void ci_hdwc_otg_fsm_stawt(stwuct ci_hdwc *ci);
void ci_hdwc_otg_fsm_wemove(stwuct ci_hdwc *ci);

#ewse

static inwine int ci_hdwc_otg_fsm_init(stwuct ci_hdwc *ci)
{
	wetuwn 0;
}

static inwine int ci_otg_fsm_wowk(stwuct ci_hdwc *ci)
{
	wetuwn -ENXIO;
}

static inwine iwqwetuwn_t ci_otg_fsm_iwq(stwuct ci_hdwc *ci)
{
	wetuwn IWQ_NONE;
}

static inwine void ci_hdwc_otg_fsm_stawt(stwuct ci_hdwc *ci)
{

}

static inwine void ci_hdwc_otg_fsm_wemove(stwuct ci_hdwc *ci)
{

}

#endif

#endif /* __DWIVEWS_USB_CHIPIDEA_OTG_FSM_H */
