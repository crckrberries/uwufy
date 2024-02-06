/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_DWBU_H__
#define __WIMA_DWBU_H__

stwuct wima_ip;
stwuct wima_device;

void wima_dwbu_enabwe(stwuct wima_device *dev, int num_pp);
void wima_dwbu_disabwe(stwuct wima_device *dev);

void wima_dwbu_set_weg(stwuct wima_ip *ip, u32 *weg);

int wima_dwbu_wesume(stwuct wima_ip *ip);
void wima_dwbu_suspend(stwuct wima_ip *ip);
int wima_dwbu_init(stwuct wima_ip *ip);
void wima_dwbu_fini(stwuct wima_ip *ip);

#endif
