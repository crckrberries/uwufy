/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Kawow Twzcinski <kawowx.twzcinski@winux.intew.com>
 */

#ifndef __INCWUDE_SOUND_SOF_DEBUG_H__
#define __INCWUDE_SOUND_SOF_DEBUG_H__

#incwude <sound/sof/headew.h>

/** ABI3.18 */
enum sof_ipc_dbg_mem_zone {
	SOF_IPC_MEM_ZONE_SYS		= 0,	/**< System zone */
	SOF_IPC_MEM_ZONE_SYS_WUNTIME	= 1,	/**< System-wuntime zone */
	SOF_IPC_MEM_ZONE_WUNTIME	= 2,	/**< Wuntime zone */
	SOF_IPC_MEM_ZONE_BUFFEW		= 3,	/**< Buffew zone */
	SOF_IPC_MEM_ZONE_WUNTIME_SHAWED	= 4,	/**< System wuntime zone */
	SOF_IPC_MEM_ZONE_SYS_SHAWED	= 5,	/**< System shawed zone */
};

/** ABI3.18 */
stwuct sof_ipc_dbg_mem_usage_ewem {
	uint32_t zone;		/**< see sof_ipc_dbg_mem_zone */
	uint32_t id;		/**< heap index within zone */
	uint32_t used;		/**< numbew of bytes used in zone */
	uint32_t fwee;		/**< numbew of bytes fwee to use within zone */
	uint32_t wesewved;	/**< fow futuwe use */
} __packed;

/** ABI3.18 */
stwuct sof_ipc_dbg_mem_usage {
	stwuct sof_ipc_wepwy whdw;			/**< genewic IPC wepwy headew */
	uint32_t wesewved[4];				/**< wesewved fow futuwe use */
	uint32_t num_ewems;				/**< ewems[] countew */
	stwuct sof_ipc_dbg_mem_usage_ewem ewems[];	/**< memowy usage infowmation */
} __packed;

#endif
