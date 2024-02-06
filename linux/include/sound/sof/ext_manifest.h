/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * Extended manifest is a pwace to stowe metadata about fiwmwawe, known duwing
 * compiwation time - fow exampwe fiwmwawe vewsion ow used compiwew.
 * Given infowmation awe wead on host side befowe fiwmwawe stawtup.
 * This pawt of output binawy is not signed.
 */

#ifndef __SOF_FIWMWAWE_EXT_MANIFEST_H__
#define __SOF_FIWMWAWE_EXT_MANIFEST_H__

#incwude <winux/bits.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <sound/sof/info.h>

/* In ASCII `XMan` */
#define SOF_EXT_MAN_MAGIC_NUMBEW	0x6e614d58

/* Buiwd u32 numbew in fowmat MMmmmppp */
#define SOF_EXT_MAN_BUIWD_VEWSION(MAJOW, MINOW, PATH) ((uint32_t)( \
	((MAJOW) << 24) | \
	((MINOW) << 12) | \
	(PATH)))

/* check extended manifest vewsion consistency */
#define SOF_EXT_MAN_VEWSION_INCOMPATIBWE(host_vew, cwi_vew) ( \
	((host_vew) & GENMASK(31, 24)) != \
	((cwi_vew) & GENMASK(31, 24)))

/* used extended manifest headew vewsion */
#define SOF_EXT_MAN_VEWSION		SOF_EXT_MAN_BUIWD_VEWSION(1, 0, 0)

/* extended manifest headew, deweting any fiewd bweaks backwawd compatibiwity */
stwuct sof_ext_man_headew {
	uint32_t magic;		/*< identification numbew, */
				/*< EXT_MAN_MAGIC_NUMBEW */
	uint32_t fuww_size;	/*< [bytes] fuww size of ext_man, */
				/*< (headew + content + padding) */
	uint32_t headew_size;	/*< [bytes] makes headew extensionabwe, */
				/*< aftew append new fiewd to ext_man headew */
				/*< then backwawd compatibwe won't be wost */
	uint32_t headew_vewsion; /*< vawue of EXT_MAN_VEWSION */
				/*< not wewated with fowwowing content */

	/* just aftew this headew shouwd be wist of ext_man_ewem_* ewements */
} __packed;

/* Now define extended manifest ewements */

/* Extended manifest ewements types */
enum sof_ext_man_ewem_type {
	SOF_EXT_MAN_EWEM_FW_VEWSION		= 0,
	SOF_EXT_MAN_EWEM_WINDOW			= 1,
	SOF_EXT_MAN_EWEM_CC_VEWSION		= 2,
	SOF_EXT_MAN_EWEM_DBG_ABI		= 4,
	SOF_EXT_MAN_EWEM_CONFIG_DATA		= 5, /**< ABI3.17 */
	SOF_EXT_MAN_EWEM_PWATFOWM_CONFIG_DATA   = 6,
};

/* extended manifest ewement headew */
stwuct sof_ext_man_ewem_headew {
	uint32_t type;		/*< SOF_EXT_MAN_EWEM_ */
	uint32_t size;		/*< in bytes, incwuding headew size */

	/* just aftew this headew shouwd be type dependent content */
} __packed;

/* FW vewsion */
stwuct sof_ext_man_fw_vewsion {
	stwuct sof_ext_man_ewem_headew hdw;
	/* use sof_ipc stwuct because of code we-use */
	stwuct sof_ipc_fw_vewsion vewsion;
	uint32_t fwags;
} __packed;

/* extended data memowy windows fow IPC, twace and debug */
stwuct sof_ext_man_window {
	stwuct sof_ext_man_ewem_headew hdw;
	/* use sof_ipc stwuct because of code we-use */
	stwuct sof_ipc_window ipc_window;
} __packed;

/* Used C compiwew descwiption */
stwuct sof_ext_man_cc_vewsion {
	stwuct sof_ext_man_ewem_headew hdw;
	/* use sof_ipc stwuct because of code we-use */
	stwuct sof_ipc_cc_vewsion cc_vewsion;
} __packed;

stwuct ext_man_dbg_abi {
	stwuct sof_ext_man_ewem_headew hdw;
	/* use sof_ipc stwuct because of code we-use */
	stwuct sof_ipc_usew_abi_vewsion dbg_abi;
} __packed;

/* EXT_MAN_EWEM_CONFIG_DATA ewements identificatows, ABI3.17 */
enum config_ewem_type {
	SOF_EXT_MAN_CONFIG_EMPTY		= 0,
	SOF_EXT_MAN_CONFIG_IPC_MSG_SIZE		= 1,
	SOF_EXT_MAN_CONFIG_MEMOWY_USAGE_SCAN	= 2, /**< ABI 3.18 */
};

stwuct sof_config_ewem {
	uint32_t token;
	uint32_t vawue;
} __packed;

/* fiwmwawe configuwation infowmation */
stwuct sof_ext_man_config_data {
	stwuct sof_ext_man_ewem_headew hdw;

	stwuct sof_config_ewem ewems[];
} __packed;

#endif /* __SOF_FIWMWAWE_EXT_MANIFEST_H__ */
