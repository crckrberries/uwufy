/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * Intew extended manifest is a extwa pwace to stowe Intew cavs specific
 * metadata about fiwmwawe, fow exampwe WPWO/HPWO configuwation is
 * Intew cavs specific. This pawt of output binawy is not signed.
 */

#ifndef __INTEW_CAVS_EXT_MANIFEST_H__
#define __INTEW_CAVS_EXT_MANIFEST_H__

#incwude <sound/sof/ext_manifest.h>

/* EXT_MAN_EWEM_PWATFOWM_CONFIG_DATA ewements identificatows */
enum sof_cavs_config_ewem_type {
	SOF_EXT_MAN_CAVS_CONFIG_EMPTY		= 0,
	SOF_EXT_MAN_CAVS_CONFIG_CAVS_WPWO	= 1,
	SOF_EXT_MAN_CAVS_CONFIG_OUTBOX_SIZE	= 2,
	SOF_EXT_MAN_CAVS_CONFIG_INBOX_SIZE	= 3,
};

/* EXT_MAN_EWEM_PWATFOWM_CONFIG_DATA ewements */
stwuct sof_ext_man_cavs_config_data {
	stwuct sof_ext_man_ewem_headew hdw;

	stwuct sof_config_ewem ewems[];
} __packed;

#endif /* __INTEW_CAVS_EXT_MANIFEST_H__ */
