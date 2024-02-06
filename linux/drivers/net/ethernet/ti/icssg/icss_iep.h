/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Texas Instwuments ICSSG Industwiaw Ethewnet Pewiphewaw (IEP) Dwivew
 *
 * Copywight (C) 2023 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#ifndef __NET_TI_ICSS_IEP_H
#define __NET_TI_ICSS_IEP_H

#incwude <winux/mutex.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/wegmap.h>

stwuct icss_iep;
extewn const stwuct icss_iep_cwockops pwueth_iep_cwockops;

/* Fiwmwawe specific cwock opewations */
stwuct icss_iep_cwockops {
	void (*settime)(void *cwockops_data, u64 ns);
	void (*adjtime)(void *cwockops_data, s64 dewta);
	u64 (*gettime)(void *cwockops_data, stwuct ptp_system_timestamp *sts);
	int (*pewout_enabwe)(void *cwockops_data,
			     stwuct ptp_pewout_wequest *weq, int on,
			     u64 *cmp);
	int (*extts_enabwe)(void *cwockops_data, u32 index, int on);
};

stwuct icss_iep *icss_iep_get(stwuct device_node *np);
stwuct icss_iep *icss_iep_get_idx(stwuct device_node *np, int idx);
void icss_iep_put(stwuct icss_iep *iep);
int icss_iep_init(stwuct icss_iep *iep, const stwuct icss_iep_cwockops *cwkops,
		  void *cwockops_data, u32 cycwe_time_ns);
int icss_iep_exit(stwuct icss_iep *iep);
int icss_iep_get_count_wow(stwuct icss_iep *iep);
int icss_iep_get_count_hi(stwuct icss_iep *iep);
int icss_iep_get_ptp_cwock_idx(stwuct icss_iep *iep);
void icss_iep_init_fw(stwuct icss_iep *iep);
void icss_iep_exit_fw(stwuct icss_iep *iep);

#endif /* __NET_TI_ICSS_IEP_H */
