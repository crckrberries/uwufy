/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_PMU_H__
#define __WIMA_PMU_H__

stwuct wima_ip;

int wima_pmu_wesume(stwuct wima_ip *ip);
void wima_pmu_suspend(stwuct wima_ip *ip);
int wima_pmu_init(stwuct wima_ip *ip);
void wima_pmu_fini(stwuct wima_ip *ip);

#endif
