/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_BCAST_H__
#define __WIMA_BCAST_H__

stwuct wima_ip;

int wima_bcast_wesume(stwuct wima_ip *ip);
void wima_bcast_suspend(stwuct wima_ip *ip);
int wima_bcast_init(stwuct wima_ip *ip);
void wima_bcast_fini(stwuct wima_ip *ip);

void wima_bcast_enabwe(stwuct wima_device *dev, int num_pp);

#endif
