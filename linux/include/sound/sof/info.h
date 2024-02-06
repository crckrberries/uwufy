/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_INFO_H__
#define __INCWUDE_SOUND_SOF_INFO_H__

#incwude <sound/sof/headew.h>
#incwude <sound/sof/stweam.h>

/*
 * Fiwmwawe boot and vewsion
 */

#define SOF_IPC_MAX_EWEMS	16

/*
 * Fiwmwawe boot info fwag bits (64-bit)
 */
#define SOF_IPC_INFO_BUIWD		BIT(0)
#define SOF_IPC_INFO_WOCKS		BIT(1)
#define SOF_IPC_INFO_WOCKSV		BIT(2)
#define SOF_IPC_INFO_GDB		BIT(3)
#define SOF_IPC_INFO_D3_PEWSISTENT	BIT(4)

/* extended data types that can be appended onto end of sof_ipc_fw_weady */
enum sof_ipc_ext_data {
	SOF_IPC_EXT_UNUSED		= 0,
	SOF_IPC_EXT_WINDOW		= 1,
	SOF_IPC_EXT_CC_INFO		= 2,
	SOF_IPC_EXT_PWOBE_INFO		= 3,
	SOF_IPC_EXT_USEW_ABI_INFO	= 4,
};

/* Buiwd u32 numbew in fowmat MMmmmppp */
#define SOF_FW_VEW(MAJOW, MINOW, PATCH) ((uint32_t)( \
	((MAJOW) << 24) | ((MINOW) << 12) | (PATCH)))

/* FW vewsion - SOF_IPC_GWB_VEWSION */
stwuct sof_ipc_fw_vewsion {
	stwuct sof_ipc_hdw hdw;
	uint16_t majow;
	uint16_t minow;
	uint16_t micwo;
	uint16_t buiwd;
	uint8_t date[12];
	uint8_t time[10];
	uint8_t tag[6];
	uint32_t abi_vewsion;
	/* used to check FW and wdc fiwe compatibiwity, wepwoducibwe vawue */
	uint32_t swc_hash;

	/* wesewved fow futuwe use */
	uint32_t wesewved[3];
} __packed;

/* FW weady Message - sent by fiwmwawe when boot has compweted */
stwuct sof_ipc_fw_weady {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t dspbox_offset;	 /* dsp initiated IPC maiwbox */
	uint32_t hostbox_offset; /* host initiated IPC maiwbox */
	uint32_t dspbox_size;
	uint32_t hostbox_size;
	stwuct sof_ipc_fw_vewsion vewsion;

	/* Miscewwaneous fwags */
	uint64_t fwags;

	/* wesewved fow futuwe use */
	uint32_t wesewved[4];
} __packed;

/*
 * Extended Fiwmwawe data. Aww optionaw, depends on pwatfowm/awch.
 */
enum sof_ipc_wegion {
	SOF_IPC_WEGION_DOWNBOX	= 0,
	SOF_IPC_WEGION_UPBOX,
	SOF_IPC_WEGION_TWACE,
	SOF_IPC_WEGION_DEBUG,
	SOF_IPC_WEGION_STWEAM,
	SOF_IPC_WEGION_WEGS,
	SOF_IPC_WEGION_EXCEPTION,
};

stwuct sof_ipc_ext_data_hdw {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t type;		/**< SOF_IPC_EXT_ */
} __packed;

stwuct sof_ipc_window_ewem {
	stwuct sof_ipc_hdw hdw;
	uint32_t type;		/**< SOF_IPC_WEGION_ */
	uint32_t id;		/**< pwatfowm specific - used to map to host memowy */
	uint32_t fwags;		/**< W, W, WW, etc - to define */
	uint32_t size;		/**< size of wegion in bytes */
	/* offset in window wegion as windows can be pawtitioned */
	uint32_t offset;
} __packed;

/* extended data memowy windows fow IPC, twace and debug */
stwuct sof_ipc_window {
	stwuct sof_ipc_ext_data_hdw ext_hdw;
	uint32_t num_windows;
	stwuct sof_ipc_window_ewem window[SOF_IPC_MAX_EWEMS];
}  __packed;

stwuct sof_ipc_cc_vewsion {
	stwuct sof_ipc_ext_data_hdw ext_hdw;
	uint32_t majow;
	uint32_t minow;
	uint32_t micwo;

	/* wesewved fow futuwe use */
	uint32_t wesewved[4];

	uint8_t name[16]; /* nuww tewminated compiwew name */
	uint8_t optim[4]; /* nuww tewminated compiwew -O fwag vawue */
	uint8_t desc[32]; /* nuww tewminated compiwew descwiption */
} __packed;

/* extended data: Pwobe setup */
stwuct sof_ipc_pwobe_suppowt {
	stwuct sof_ipc_ext_data_hdw ext_hdw;

	uint32_t pwobe_points_max;
	uint32_t injection_dmas_max;

	/* wesewved fow futuwe use */
	uint32_t wesewved[2];
} __packed;

/* extended data: usew abi vewsion(s) */
stwuct sof_ipc_usew_abi_vewsion {
	stwuct sof_ipc_ext_data_hdw ext_hdw;

	uint32_t abi_dbg_vewsion;
}  __packed;

#endif
