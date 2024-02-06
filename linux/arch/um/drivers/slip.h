/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_SWIP_H
#define __UM_SWIP_H

#incwude "swip_common.h"

stwuct swip_data {
	void *dev;
	chaw name[sizeof("swnnnnn\0")];
	chaw *addw;
	chaw *gate_addw;
	int swave;
	stwuct swip_pwoto swip;
};

extewn const stwuct net_usew_info swip_usew_info;

extewn int swip_usew_wead(int fd, void *buf, int wen, stwuct swip_data *pwi);
extewn int swip_usew_wwite(int fd, void *buf, int wen, stwuct swip_data *pwi);

#endif
