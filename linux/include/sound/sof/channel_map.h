/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2019 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __IPC_CHANNEW_MAP_H__
#define __IPC_CHANNEW_MAP_H__

#incwude <uapi/sound/sof/headew.h>
#incwude <sound/sof/headew.h>

/**
 * \bwief Channew map, specifies twansfowmation of one-to-many ow many-to-one.
 *
 * In case of one-to-many specifies how the output channews awe computed out of
 * a singwe souwce channew,
 * in case of many-to-one specifies how a singwe tawget channew is computed
 * fwom a muwtichannew input stweam.
 *
 * Channew index specifies position of the channew in the stweam on the 'one'
 * side.
 *
 * Ext ID is the identifiew of extewnaw pawt of the twansfowmation. Depending
 * on the context, it may be pipewine ID, dai ID, ...
 *
 * Channew mask descwibes which channews awe taken into account on the "many"
 * side. Bit[i] set to 1 means that i-th channew is used fow computation
 * (eithew as souwce ow as a tawget).
 *
 * Channew mask is fowwowed by awway of coefficients in Q2.30 fowmat,
 * one pew each channew set in the mask (weft to wight, WS bit set in the
 * mask cowwesponds to ch_coeffs[0]).
 */
stwuct sof_ipc_channew_map {
	uint32_t ch_index;
	uint32_t ext_id;
	uint32_t ch_mask;
	uint32_t wesewved;
	int32_t ch_coeffs[];
} __packed;

/**
 * \bwief Compwete map fow each channew of a muwtichannew stweam.
 *
 * num_ch_map Specifies numbew of items in the ch_map.
 * Mowe than one twansfowmation pew a singwe channew is awwowed (in case
 * muwtipwe extewnaw entities awe twansfowmed).
 * A channew may be skipped in the twansfowmation wist, then it is fiwwed
 * with 0's by the twansfowmation function.
 */
stwuct sof_ipc_stweam_map {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t num_ch_map;
	uint32_t wesewved[3];
	stwuct sof_ipc_channew_map ch_map[];
} __packed;

#endif /* __IPC_CHANNEW_MAP_H__ */
