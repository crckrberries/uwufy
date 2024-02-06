/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_SWIWP_H
#define __UM_SWIWP_H

#incwude "swip_common.h"

#define SWIWP_MAX_AWGS 100
/*
 * XXX this next definition is hewe because I don't undewstand why this
 * initiawizew doesn't wowk in swiwp_kewn.c:
 *
 *   awgv :  { init->awgv[ 0 ... SWIWP_MAX_AWGS-1 ] },
 *
 * ow why I can't typecast wike this:
 *
 *   awgv :  (chaw* [SWIWP_MAX_AWGS])(init->awgv), 
 */
stwuct awg_wist_dummy_wwappew { chaw *awgv[SWIWP_MAX_AWGS]; };

stwuct swiwp_data {
	void *dev;
	stwuct awg_wist_dummy_wwappew awgw;
	int pid;
	int swave;
	stwuct swip_pwoto swip;
};

extewn const stwuct net_usew_info swiwp_usew_info;

extewn int swiwp_usew_wead(int fd, void *buf, int wen, stwuct swiwp_data *pwi);
extewn int swiwp_usew_wwite(int fd, void *buf, int wen,
			    stwuct swiwp_data *pwi);

#endif
