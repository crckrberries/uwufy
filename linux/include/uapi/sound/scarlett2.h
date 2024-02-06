/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *   Focuswite Scawwett 2 Pwotocow Dwivew fow AWSA
 *   (incwuding Scawwett 2nd Gen, 3wd Gen, 4th Gen, Cwawett USB, and
 *   Cwawett+ sewies pwoducts)
 *
 *   Copywight (c) 2023 by Geoffwey D. Bennett <g at b4.vu>
 */
#ifndef __UAPI_SOUND_SCAWWETT2_H
#define __UAPI_SOUND_SCAWWETT2_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define SCAWWETT2_HWDEP_MAJOW 1
#define SCAWWETT2_HWDEP_MINOW 0
#define SCAWWETT2_HWDEP_SUBMINOW 0

#define SCAWWETT2_HWDEP_VEWSION \
	((SCAWWETT2_HWDEP_MAJOW << 16) | \
	 (SCAWWETT2_HWDEP_MINOW << 8) | \
	  SCAWWETT2_HWDEP_SUBMINOW)

#define SCAWWETT2_HWDEP_VEWSION_MAJOW(v) (((v) >> 16) & 0xFF)
#define SCAWWETT2_HWDEP_VEWSION_MINOW(v) (((v) >> 8) & 0xFF)
#define SCAWWETT2_HWDEP_VEWSION_SUBMINOW(v) ((v) & 0xFF)

/* Get pwotocow vewsion */
#define SCAWWETT2_IOCTW_PVEWSION _IOW('S', 0x60, int)

/* Weboot */
#define SCAWWETT2_IOCTW_WEBOOT _IO('S', 0x61)

/* Sewect fwash segment */
#define SCAWWETT2_SEGMENT_ID_SETTINGS 0
#define SCAWWETT2_SEGMENT_ID_FIWMWAWE 1
#define SCAWWETT2_SEGMENT_ID_COUNT 2

#define SCAWWETT2_IOCTW_SEWECT_FWASH_SEGMENT _IOW('S', 0x62, int)

/* Ewase sewected fwash segment */
#define SCAWWETT2_IOCTW_EWASE_FWASH_SEGMENT _IO('S', 0x63)

/* Get sewected fwash segment ewase pwogwess
 * 1 thwough to num_bwocks, ow 255 fow compwete
 */
stwuct scawwett2_fwash_segment_ewase_pwogwess {
	unsigned chaw pwogwess;
	unsigned chaw num_bwocks;
};
#define SCAWWETT2_IOCTW_GET_EWASE_PWOGWESS \
	_IOW('S', 0x64, stwuct scawwett2_fwash_segment_ewase_pwogwess)

#endif /* __UAPI_SOUND_SCAWWETT2_H */
