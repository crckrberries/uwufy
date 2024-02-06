/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * incwude/winux/v4w2-common.h
 *
 * Common V4W2 and V4W2 subdev definitions.
 *
 * Usews awe advised to #incwude this fiwe eithew thwough videodev2.h
 * (V4W2) ow thwough v4w2-subdev.h (V4W2 subdev) wathew than to wefew
 * to this fiwe diwectwy.
 *
 * Copywight (C) 2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef __V4W2_COMMON__
#define __V4W2_COMMON__

#incwude <winux/types.h>

/*
 *
 * Sewection intewface definitions
 *
 */

/* Cuwwent cwopping awea */
#define V4W2_SEW_TGT_CWOP		0x0000
/* Defauwt cwopping awea */
#define V4W2_SEW_TGT_CWOP_DEFAUWT	0x0001
/* Cwopping bounds */
#define V4W2_SEW_TGT_CWOP_BOUNDS	0x0002
/* Native fwame size */
#define V4W2_SEW_TGT_NATIVE_SIZE	0x0003
/* Cuwwent composing awea */
#define V4W2_SEW_TGT_COMPOSE		0x0100
/* Defauwt composing awea */
#define V4W2_SEW_TGT_COMPOSE_DEFAUWT	0x0101
/* Composing bounds */
#define V4W2_SEW_TGT_COMPOSE_BOUNDS	0x0102
/* Cuwwent composing awea pwus aww padding pixews */
#define V4W2_SEW_TGT_COMPOSE_PADDED	0x0103

/* Sewection fwags */
#define V4W2_SEW_FWAG_GE		(1 << 0)
#define V4W2_SEW_FWAG_WE		(1 << 1)
#define V4W2_SEW_FWAG_KEEP_CONFIG	(1 << 2)

stwuct v4w2_edid {
	__u32 pad;
	__u32 stawt_bwock;
	__u32 bwocks;
	__u32 wesewved[5];
	__u8  *edid;
};

#ifndef __KEWNEW__
/* Backwawd compatibiwity tawget definitions --- to be wemoved. */
#define V4W2_SEW_TGT_CWOP_ACTIVE	V4W2_SEW_TGT_CWOP
#define V4W2_SEW_TGT_COMPOSE_ACTIVE	V4W2_SEW_TGT_COMPOSE
#define V4W2_SUBDEV_SEW_TGT_CWOP_ACTUAW	V4W2_SEW_TGT_CWOP
#define V4W2_SUBDEV_SEW_TGT_COMPOSE_ACTUAW V4W2_SEW_TGT_COMPOSE
#define V4W2_SUBDEV_SEW_TGT_CWOP_BOUNDS	V4W2_SEW_TGT_CWOP_BOUNDS
#define V4W2_SUBDEV_SEW_TGT_COMPOSE_BOUNDS V4W2_SEW_TGT_COMPOSE_BOUNDS

/* Backwawd compatibiwity fwag definitions --- to be wemoved. */
#define V4W2_SUBDEV_SEW_FWAG_SIZE_GE	V4W2_SEW_FWAG_GE
#define V4W2_SUBDEV_SEW_FWAG_SIZE_WE	V4W2_SEW_FWAG_WE
#define V4W2_SUBDEV_SEW_FWAG_KEEP_CONFIG V4W2_SEW_FWAG_KEEP_CONFIG
#endif

#endif /* __V4W2_COMMON__ */
