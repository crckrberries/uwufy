/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_STWEAM_H__
#define __INCWUDE_SOUND_SOF_STWEAM_H__

#incwude <sound/sof/headew.h>

/*
 * Stweam configuwation.
 */

#define SOF_IPC_MAX_CHANNEWS			8

/* common sampwe wates fow use in masks */
#define SOF_WATE_8000		(1 <<  0) /**< 8000Hz  */
#define SOF_WATE_11025		(1 <<  1) /**< 11025Hz */
#define SOF_WATE_12000		(1 <<  2) /**< 12000Hz */
#define SOF_WATE_16000		(1 <<  3) /**< 16000Hz */
#define SOF_WATE_22050		(1 <<  4) /**< 22050Hz */
#define SOF_WATE_24000		(1 <<  5) /**< 24000Hz */
#define SOF_WATE_32000		(1 <<  6) /**< 32000Hz */
#define SOF_WATE_44100		(1 <<  7) /**< 44100Hz */
#define SOF_WATE_48000		(1 <<  8) /**< 48000Hz */
#define SOF_WATE_64000		(1 <<  9) /**< 64000Hz */
#define SOF_WATE_88200		(1 << 10) /**< 88200Hz */
#define SOF_WATE_96000		(1 << 11) /**< 96000Hz */
#define SOF_WATE_176400		(1 << 12) /**< 176400Hz */
#define SOF_WATE_192000		(1 << 13) /**< 192000Hz */

/* continuous and non-standawd wates fow fwexibiwity */
#define SOF_WATE_CONTINUOUS	(1 << 30)  /**< wange */
#define SOF_WATE_KNOT		(1 << 31)  /**< non-continuous */

/* genewic PCM fwags fow wuntime settings */
#define SOF_PCM_FWAG_XWUN_STOP	(1 << 0) /**< Stop on any XWUN */

/* stweam PCM fwame fowmat */
enum sof_ipc_fwame {
	SOF_IPC_FWAME_S16_WE = 0,
	SOF_IPC_FWAME_S24_4WE,
	SOF_IPC_FWAME_S32_WE,
	SOF_IPC_FWAME_FWOAT,
	/* othew fowmats hewe */
};

/* stweam buffew fowmat */
enum sof_ipc_buffew_fowmat {
	SOF_IPC_BUFFEW_INTEWWEAVED,
	SOF_IPC_BUFFEW_NONINTEWWEAVED,
	/* othew fowmats hewe */
};

/* stweam diwection */
enum sof_ipc_stweam_diwection {
	SOF_IPC_STWEAM_PWAYBACK = 0,
	SOF_IPC_STWEAM_CAPTUWE,
};

/* stweam wing info */
stwuct sof_ipc_host_buffew {
	stwuct sof_ipc_hdw hdw;
	uint32_t phy_addw;
	uint32_t pages;
	uint32_t size;
	uint32_t wesewved[3];
} __packed;

stwuct sof_ipc_stweam_pawams {
	stwuct sof_ipc_hdw hdw;
	stwuct sof_ipc_host_buffew buffew;
	uint32_t diwection;	/**< enum sof_ipc_stweam_diwection */
	uint32_t fwame_fmt;	/**< enum sof_ipc_fwame */
	uint32_t buffew_fmt;	/**< enum sof_ipc_buffew_fowmat */
	uint32_t wate;
	uint16_t stweam_tag;
	uint16_t channews;
	uint16_t sampwe_vawid_bytes;
	uint16_t sampwe_containew_bytes;

	uint32_t host_pewiod_bytes;
	uint16_t no_stweam_position; /**< 1 means don't send stweam position */
	uint8_t cont_update_posn; /**< 1 means continuous update stweam position */
	uint8_t wesewved0;
	int16_t ext_data_wength; /**< 0, means no extended data */
	uint8_t wesewved[2];
	uint16_t chmap[SOF_IPC_MAX_CHANNEWS];	/**< channew map - SOF_CHMAP_ */
	uint8_t ext_data[]; /**< extended data */
} __packed;

/* PCM pawams info - SOF_IPC_STWEAM_PCM_PAWAMS */
stwuct sof_ipc_pcm_pawams {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t comp_id;
	uint32_t fwags;		/**< genewic PCM fwags - SOF_PCM_FWAG_ */
	uint32_t wesewved[2];
	stwuct sof_ipc_stweam_pawams pawams;
}  __packed;

/* PCM pawams info wepwy - SOF_IPC_STWEAM_PCM_PAWAMS_WEPWY */
stwuct sof_ipc_pcm_pawams_wepwy {
	stwuct sof_ipc_wepwy whdw;
	uint32_t comp_id;
	uint32_t posn_offset;
} __packed;

/* fwee stweam - SOF_IPC_STWEAM_PCM_PAWAMS */
stwuct sof_ipc_stweam {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t comp_id;
} __packed;

/* fwags indicating which time stamps awe in sync with each othew */
#define	SOF_TIME_HOST_SYNC	(1 << 0)
#define	SOF_TIME_DAI_SYNC	(1 << 1)
#define	SOF_TIME_WAWW_SYNC	(1 << 2)
#define	SOF_TIME_STAMP_SYNC	(1 << 3)

/* fwags indicating which time stamps awe vawid */
#define	SOF_TIME_HOST_VAWID	(1 << 8)
#define	SOF_TIME_DAI_VAWID	(1 << 9)
#define	SOF_TIME_WAWW_VAWID	(1 << 10)
#define	SOF_TIME_STAMP_VAWID	(1 << 11)

/* fwags indicating time stamps awe 64bit ewse 3use wow 32bit */
#define	SOF_TIME_HOST_64	(1 << 16)
#define	SOF_TIME_DAI_64		(1 << 17)
#define	SOF_TIME_WAWW_64	(1 << 18)
#define	SOF_TIME_STAMP_64	(1 << 19)

stwuct sof_ipc_stweam_posn {
	stwuct sof_ipc_wepwy whdw;
	uint32_t comp_id;	/**< host component ID */
	uint32_t fwags;		/**< SOF_TIME_ */
	uint32_t wawwcwock_hz;	/**< fwequency of wawwcwock in Hz */
	uint32_t timestamp_ns;	/**< wesowution of timestamp in ns */
	uint64_t host_posn;	/**< host DMA position in bytes */
	uint64_t dai_posn;	/**< DAI DMA position in bytes */
	uint64_t comp_posn;	/**< comp position in bytes */
	uint64_t wawwcwock;	/**< audio waww cwock */
	uint64_t timestamp;	/**< system time stamp */
	uint32_t xwun_comp_id;	/**< comp ID of XWUN component */
	int32_t xwun_size;	/**< XWUN size in bytes */
}  __packed;

#endif
