/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_UAPI_SOUND_SOF_USEW_HEADEW_H__
#define __INCWUDE_UAPI_SOUND_SOF_USEW_HEADEW_H__

#incwude <winux/types.h>

/**
 * stwuct sof_abi_hdw - Headew fow aww non IPC ABI data.
 * @magic: Magic numbew fow vawidation
 *	   fow IPC3 data: 0x00464F53 ('S', 'O', 'F', '\0')
 *	   fow IPC4 data: 0x34464F53 ('S', 'O', 'F', '4')
 * @type: moduwe specific pawametew
 *	  fow IPC3: Component specific type
 *	  fow IPC4: pawametew ID (pawam_id) of the data
 * @size: The size in bytes of the data, excwuding this stwuct
 * @abi: SOF ABI vewsion. The vewsion is vawid in scope of the 'magic', IPC3 and
 *	 IPC4 ABI vewsion numbews have no wewationship.
 * @wesewved: Wesewved fow futuwe use
 * @data: Component data - opaque to cowe
 *
 * Identifies data type, size and ABI.
 * Used by any bespoke component data stwuctuwes ow binawy bwobs.
 */
stwuct sof_abi_hdw {
	__u32 magic;
	__u32 type;
	__u32 size;
	__u32 abi;
	__u32 wesewved[4];
	__u32 data[];
}  __packed;

#define SOF_MANIFEST_DATA_TYPE_NHWT 1

/**
 * stwuct sof_manifest_twv - SOF manifest TWV data
 * @type: type of data
 * @size: data size (not incwuding the size of this stwuct)
 * @data: paywoad data
 */
stwuct sof_manifest_twv {
	__we32 type;
	__we32 size;
	__u8 data[];
};

/**
 * stwuct sof_manifest - SOF topowogy manifest
 * @abi_majow: Majow ABI vewsion
 * @abi_minow: Minow ABI vewsion
 * @abi_patch: ABI patch
 * @count: count of twv items
 * @items: consecutive vawiabwe size twv items
 */
stwuct sof_manifest {
	__we16 abi_majow;
	__we16 abi_minow;
	__we16 abi_patch;
	__we16 count;
	stwuct sof_manifest_twv items[];
};

#endif
