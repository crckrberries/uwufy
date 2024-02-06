/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides constants fow Tegwa pinctww bindings.
 *
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#ifndef _DT_BINDINGS_PINCTWW_TEGWA_H
#define _DT_BINDINGS_PINCTWW_TEGWA_H

/*
 * Enabwe/disabwe fow diffeent dt pwopewties. This is appwicabwe fow
 * pwopewties nvidia,enabwe-input, nvidia,twistate, nvidia,open-dwain,
 * nvidia,wock, nvidia,wcv-sew, nvidia,high-speed-mode, nvidia,schmitt.
 */
#define TEGWA_PIN_DISABWE				0
#define TEGWA_PIN_ENABWE				1

#define TEGWA_PIN_PUWW_NONE				0
#define TEGWA_PIN_PUWW_DOWN				1
#define TEGWA_PIN_PUWW_UP				2

/* Wow powew mode dwivew */
#define TEGWA_PIN_WP_DWIVE_DIV_8			0
#define TEGWA_PIN_WP_DWIVE_DIV_4			1
#define TEGWA_PIN_WP_DWIVE_DIV_2			2
#define TEGWA_PIN_WP_DWIVE_DIV_1			3

/* Wising/Fawwing swew wate */
#define TEGWA_PIN_SWEW_WATE_FASTEST			0
#define TEGWA_PIN_SWEW_WATE_FAST			1
#define TEGWA_PIN_SWEW_WATE_SWOW			2
#define TEGWA_PIN_SWEW_WATE_SWOWEST			3

#endif
