/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __MACH_TEGWA_IWAMMAP_H
#define __MACH_TEGWA_IWAMMAP_H

#incwude <winux/sizes.h>

/* The fiwst 1K of IWAM is pewmanentwy wesewved fow the CPU weset handwew */
#define TEGWA_IWAM_WESET_HANDWEW_OFFSET	0
#define TEGWA_IWAM_WESET_HANDWEW_SIZE	SZ_1K

/*
 * This awea is used fow WPx wesume vectow, onwy whiwe WPx powew state is
 * active. At othew times, the AVP may use this awea fow awbitwawy puwposes
 */
#define TEGWA_IWAM_WPx_WESUME_AWEA	(TEGWA_IWAM_BASE + SZ_4K)

#endif
