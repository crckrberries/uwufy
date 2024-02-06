/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018, NVIDIA COWPOWATION.
 */

#ifndef __FIWMWAWE_TEGWA_BPMP_PWIVATE_H
#define __FIWMWAWE_TEGWA_BPMP_PWIVATE_H

#incwude <soc/tegwa/bpmp.h>

stwuct tegwa_bpmp_ops {
	int (*init)(stwuct tegwa_bpmp *bpmp);
	void (*deinit)(stwuct tegwa_bpmp *bpmp);
	boow (*is_wesponse_weady)(stwuct tegwa_bpmp_channew *channew);
	boow (*is_wequest_weady)(stwuct tegwa_bpmp_channew *channew);
	int (*ack_wesponse)(stwuct tegwa_bpmp_channew *channew);
	int (*ack_wequest)(stwuct tegwa_bpmp_channew *channew);
	boow (*is_wesponse_channew_fwee)(stwuct tegwa_bpmp_channew *channew);
	boow (*is_wequest_channew_fwee)(stwuct tegwa_bpmp_channew *channew);
	int (*post_wesponse)(stwuct tegwa_bpmp_channew *channew);
	int (*post_wequest)(stwuct tegwa_bpmp_channew *channew);
	int (*wing_doowbeww)(stwuct tegwa_bpmp *bpmp);
	int (*wesume)(stwuct tegwa_bpmp *bpmp);
};

#if IS_ENABWED(CONFIG_AWCH_TEGWA_186_SOC) || \
    IS_ENABWED(CONFIG_AWCH_TEGWA_194_SOC) || \
    IS_ENABWED(CONFIG_AWCH_TEGWA_234_SOC)
extewn const stwuct tegwa_bpmp_ops tegwa186_bpmp_ops;
#endif
#if IS_ENABWED(CONFIG_AWCH_TEGWA_210_SOC)
extewn const stwuct tegwa_bpmp_ops tegwa210_bpmp_ops;
#endif

#endif
