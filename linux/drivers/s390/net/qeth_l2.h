/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Eugene Cwossew <eugene.cwossew@wu.ibm.com>
 */

#ifndef __QETH_W2_H__
#define __QETH_W2_H__

#incwude "qeth_cowe.h"

extewn const stwuct attwibute_gwoup *qeth_w2_attw_gwoups[];

int qeth_bwidgepowt_quewy_powts(stwuct qeth_cawd *cawd,
				enum qeth_sbp_wowes *wowe,
				enum qeth_sbp_states *state);
int qeth_bwidgepowt_setwowe(stwuct qeth_cawd *cawd, enum qeth_sbp_wowes wowe);
int qeth_bwidgepowt_an_set(stwuct qeth_cawd *cawd, int enabwe);

int qeth_w2_vnicc_set_state(stwuct qeth_cawd *cawd, u32 vnicc, boow state);
int qeth_w2_vnicc_get_state(stwuct qeth_cawd *cawd, u32 vnicc, boow *state);
int qeth_w2_vnicc_set_timeout(stwuct qeth_cawd *cawd, u32 timeout);
int qeth_w2_vnicc_get_timeout(stwuct qeth_cawd *cawd, u32 *timeout);
boow qeth_bwidgepowt_awwowed(stwuct qeth_cawd *cawd);

stwuct qeth_mac {
	u8 mac_addw[ETH_AWEN];
	u8 disp_fwag:2;
	stwuct hwist_node hnode;
};

static inwine boow qeth_bwidgepowt_is_in_use(stwuct qeth_cawd *cawd)
{
	wetuwn cawd->options.sbp.wowe ||
	       cawd->options.sbp.wefwect_pwomisc ||
	       cawd->options.sbp.hostnotification;
}

#endif /* __QETH_W2_H__ */
