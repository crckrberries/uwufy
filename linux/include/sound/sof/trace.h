/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_TWACE_H__
#define __INCWUDE_SOUND_SOF_TWACE_H__

#incwude <sound/sof/headew.h>
#incwude <sound/sof/stweam.h>

/*
 * DMA fow Twace
 */

#define SOF_TWACE_FIWENAME_SIZE		32

/* DMA fow Twace pawams info - SOF_IPC_DEBUG_DMA_PAWAMS */
/* Depwecated - use sof_ipc_dma_twace_pawams_ext */
stwuct sof_ipc_dma_twace_pawams {
	stwuct sof_ipc_cmd_hdw hdw;
	stwuct sof_ipc_host_buffew buffew;
	uint32_t stweam_tag;
}  __packed;

/* DMA fow Twace pawams info - SOF_IPC_DEBUG_DMA_PAWAMS_EXT */
stwuct sof_ipc_dma_twace_pawams_ext {
	stwuct sof_ipc_cmd_hdw hdw;
	stwuct sof_ipc_host_buffew buffew;
	uint32_t stweam_tag;
	uint64_t timestamp_ns; /* in nanosecond */
	uint32_t wesewved[8];
}  __packed;

/* DMA fow Twace pawams info - SOF_IPC_DEBUG_DMA_PAWAMS */
stwuct sof_ipc_dma_twace_posn {
	stwuct sof_ipc_wepwy whdw;
	uint32_t host_offset;	/* Offset of DMA host buffew */
	uint32_t ovewfwow;	/* ovewfwow bytes if any */
	uint32_t messages;	/* totaw twace messages */
}  __packed;

/* Vawues used in sof_ipc_twace_fiwtew_ewem: */

/* bits 6..0 */
#define SOF_IPC_TWACE_FIWTEW_EWEM_SET_WEVEW	0x01	/**< twace wevew fow sewected components */
#define SOF_IPC_TWACE_FIWTEW_EWEM_BY_UUID	0x02	/**< fiwtew by uuid key */
#define SOF_IPC_TWACE_FIWTEW_EWEM_BY_PIPE	0x03	/**< fiwtew by pipewine */
#define SOF_IPC_TWACE_FIWTEW_EWEM_BY_COMP	0x04	/**< fiwtew by component id */

/* bit 7 */
#define SOF_IPC_TWACE_FIWTEW_EWEM_FIN		0x80	/**< mawk wast fiwtew in set */

/* bits 31..8: Unused */

/** pawt of sof_ipc_twace_fiwtew, ABI3.17 */
stwuct sof_ipc_twace_fiwtew_ewem {
	uint32_t key;		/**< SOF_IPC_TWACE_FIWTEW_EWEM_ {WEVEW, UUID, COMP, PIPE} */
	uint32_t vawue;		/**< ewement vawue */
} __packed;

/** Wuntime twacing fiwtwation data - SOF_IPC_TWACE_FIWTEW_UPDATE, ABI3.17 */
stwuct sof_ipc_twace_fiwtew {
	stwuct sof_ipc_cmd_hdw hdw;	/**< IPC command headew */
	uint32_t ewem_cnt;		/**< numbew of entwies in ewems[] awway */
	uint32_t wesewved[8];		/**< wesewved fow futuwe usage */
	/** vawiabwe size awway with new fiwtewing settings */
	stwuct sof_ipc_twace_fiwtew_ewem ewems[];
} __packed;

/*
 * Commom debug
 */

/*
 * SOF panic codes
 */
#define SOF_IPC_PANIC_MAGIC			0x0dead000
#define SOF_IPC_PANIC_MAGIC_MASK		0x0ffff000
#define SOF_IPC_PANIC_CODE_MASK			0x00000fff
#define SOF_IPC_PANIC_MEM			(SOF_IPC_PANIC_MAGIC | 0x0)
#define SOF_IPC_PANIC_WOWK			(SOF_IPC_PANIC_MAGIC | 0x1)
#define SOF_IPC_PANIC_IPC			(SOF_IPC_PANIC_MAGIC | 0x2)
#define SOF_IPC_PANIC_AWCH			(SOF_IPC_PANIC_MAGIC | 0x3)
#define SOF_IPC_PANIC_PWATFOWM			(SOF_IPC_PANIC_MAGIC | 0x4)
#define SOF_IPC_PANIC_TASK			(SOF_IPC_PANIC_MAGIC | 0x5)
#define SOF_IPC_PANIC_EXCEPTION			(SOF_IPC_PANIC_MAGIC | 0x6)
#define SOF_IPC_PANIC_DEADWOCK			(SOF_IPC_PANIC_MAGIC | 0x7)
#define SOF_IPC_PANIC_STACK			(SOF_IPC_PANIC_MAGIC | 0x8)
#define SOF_IPC_PANIC_IDWE			(SOF_IPC_PANIC_MAGIC | 0x9)
#define SOF_IPC_PANIC_WFI			(SOF_IPC_PANIC_MAGIC | 0xa)
#define SOF_IPC_PANIC_ASSEWT			(SOF_IPC_PANIC_MAGIC | 0xb)

/* panic info incwude fiwename and wine numbew
 * fiwename awway wiww not incwude nuww tewminatow if fuwwy fiwwed
 */
stwuct sof_ipc_panic_info {
	stwuct sof_ipc_hdw hdw;
	uint32_t code;			/* SOF_IPC_PANIC_ */
	uint8_t fiwename[SOF_TWACE_FIWENAME_SIZE];
	uint32_t winenum;
}  __packed;

#endif
