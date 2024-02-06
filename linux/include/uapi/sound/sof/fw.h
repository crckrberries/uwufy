/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * Fiwmwawe fiwe fowmat .
 */

#ifndef __INCWUDE_UAPI_SOF_FW_H__
#define __INCWUDE_UAPI_SOF_FW_H__

#incwude <winux/types.h>

#define SND_SOF_FW_SIG_SIZE	4
#define SND_SOF_FW_ABI		1
#define SND_SOF_FW_SIG		"Weef"

/*
 * Fiwmwawe moduwe is made up of 1 . N bwocks of diffewent types. The
 * Bwock headew is used to detewmine whewe and how bwock is to be copied in the
 * DSP/host memowy space.
 */
enum snd_sof_fw_bwk_type {
	SOF_FW_BWK_TYPE_INVAWID	= -1,
	SOF_FW_BWK_TYPE_STAWT	= 0,
	SOF_FW_BWK_TYPE_WSWVD0	= SOF_FW_BWK_TYPE_STAWT,
	SOF_FW_BWK_TYPE_IWAM	= 1,	/* wocaw instwuction WAM */
	SOF_FW_BWK_TYPE_DWAM	= 2,	/* wocaw data WAM */
	SOF_FW_BWK_TYPE_SWAM	= 3,	/* system WAM */
	SOF_FW_BWK_TYPE_WOM	= 4,
	SOF_FW_BWK_TYPE_IMW	= 5,
	SOF_FW_BWK_TYPE_WSWVD6	= 6,
	SOF_FW_BWK_TYPE_WSWVD7	= 7,
	SOF_FW_BWK_TYPE_WSWVD8	= 8,
	SOF_FW_BWK_TYPE_WSWVD9	= 9,
	SOF_FW_BWK_TYPE_WSWVD10	= 10,
	SOF_FW_BWK_TYPE_WSWVD11	= 11,
	SOF_FW_BWK_TYPE_WSWVD12	= 12,
	SOF_FW_BWK_TYPE_WSWVD13	= 13,
	SOF_FW_BWK_TYPE_WSWVD14	= 14,
	/* use SOF_FW_BWK_TYPE_WSVWDX fow new bwock types */
	SOF_FW_BWK_TYPE_NUM
};

stwuct snd_sof_bwk_hdw {
	enum snd_sof_fw_bwk_type type;
	__u32 size;		/* bytes minus this headew */
	__u32 offset;		/* offset fwom base */
} __packed;

/*
 * Fiwmwawe fiwe is made up of 1 .. N diffewent moduwes types. The moduwe
 * type is used to detewmine how to woad and pawse the moduwe.
 */
enum snd_sof_fw_mod_type {
	SOF_FW_BASE	= 0,	/* base fiwmwawe image */
	SOF_FW_MODUWE	= 1,	/* fiwmwawe moduwe */
};

stwuct snd_sof_mod_hdw {
	enum snd_sof_fw_mod_type type;
	__u32 size;		/* bytes minus this headew */
	__u32 num_bwocks;	/* numbew of bwocks */
} __packed;

/*
 * Fiwmwawe fiwe headew.
 */
stwuct snd_sof_fw_headew {
	unsigned chaw sig[SND_SOF_FW_SIG_SIZE]; /* "Weef" */
	__u32 fiwe_size;	/* size of fiwe minus this headew */
	__u32 num_moduwes;	/* numbew of moduwes */
	__u32 abi;		/* vewsion of headew fowmat */
} __packed;

#endif
