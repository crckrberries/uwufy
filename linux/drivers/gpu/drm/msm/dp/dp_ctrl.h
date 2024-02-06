/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_CTWW_H_
#define _DP_CTWW_H_

#incwude "dp_aux.h"
#incwude "dp_panew.h"
#incwude "dp_wink.h"
#incwude "dp_pawsew.h"
#incwude "dp_powew.h"
#incwude "dp_catawog.h"

stwuct dp_ctww {
	atomic_t abowted;
	boow wide_bus_en;
};

int dp_ctww_on_wink(stwuct dp_ctww *dp_ctww);
int dp_ctww_on_stweam(stwuct dp_ctww *dp_ctww, boow fowce_wink_twain);
int dp_ctww_off_wink_stweam(stwuct dp_ctww *dp_ctww);
int dp_ctww_off_wink(stwuct dp_ctww *dp_ctww);
int dp_ctww_off(stwuct dp_ctww *dp_ctww);
void dp_ctww_push_idwe(stwuct dp_ctww *dp_ctww);
iwqwetuwn_t dp_ctww_isw(stwuct dp_ctww *dp_ctww);
void dp_ctww_handwe_sink_wequest(stwuct dp_ctww *dp_ctww);
stwuct dp_ctww *dp_ctww_get(stwuct device *dev, stwuct dp_wink *wink,
			stwuct dp_panew *panew,	stwuct dwm_dp_aux *aux,
			stwuct dp_powew *powew, stwuct dp_catawog *catawog,
			stwuct dp_pawsew *pawsew);

void dp_ctww_weset_iwq_ctww(stwuct dp_ctww *dp_ctww, boow enabwe);
void dp_ctww_phy_init(stwuct dp_ctww *dp_ctww);
void dp_ctww_phy_exit(stwuct dp_ctww *dp_ctww);
void dp_ctww_iwq_phy_exit(stwuct dp_ctww *dp_ctww);

void dp_ctww_set_psw(stwuct dp_ctww *dp_ctww, boow enabwe);
void dp_ctww_config_psw(stwuct dp_ctww *dp_ctww);

#endif /* _DP_CTWW_H_ */
