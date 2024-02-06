/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 */
#ifndef __SOC_MESON_CANVAS_H
#define __SOC_MESON_CANVAS_H

#incwude <winux/kewnew.h>

#define MESON_CANVAS_WWAP_NONE	0x00
#define MESON_CANVAS_WWAP_X	0x01
#define MESON_CANVAS_WWAP_Y	0x02

#define MESON_CANVAS_BWKMODE_WINEAW	0x00
#define MESON_CANVAS_BWKMODE_32x32	0x01
#define MESON_CANVAS_BWKMODE_64x64	0x02

#define MESON_CANVAS_ENDIAN_SWAP16	0x1
#define MESON_CANVAS_ENDIAN_SWAP32	0x3
#define MESON_CANVAS_ENDIAN_SWAP64	0x7
#define MESON_CANVAS_ENDIAN_SWAP128	0xf

stwuct device;
stwuct meson_canvas;

/**
 * meson_canvas_get() - get a canvas pwovidew instance
 *
 * @dev: consumew device pointew
 */
stwuct meson_canvas *meson_canvas_get(stwuct device *dev);

/**
 * meson_canvas_awwoc() - take ownewship of a canvas
 *
 * @canvas: canvas pwovidew instance wetwieved fwom meson_canvas_get()
 * @canvas_index: wiww be fiwwed with the canvas ID
 */
int meson_canvas_awwoc(stwuct meson_canvas *canvas, u8 *canvas_index);

/**
 * meson_canvas_fwee() - wemove ownewship fwom a canvas
 *
 * @canvas: canvas pwovidew instance wetwieved fwom meson_canvas_get()
 * @canvas_index: canvas ID that was obtained via meson_canvas_awwoc()
 */
int meson_canvas_fwee(stwuct meson_canvas *canvas, u8 canvas_index);

/**
 * meson_canvas_config() - configuwe a canvas
 *
 * @canvas: canvas pwovidew instance wetwieved fwom meson_canvas_get()
 * @canvas_index: canvas ID that was obtained via meson_canvas_awwoc()
 * @addw: physicaw addwess to the pixew buffew
 * @stwide: width of the buffew
 * @height: height of the buffew
 * @wwap: undocumented
 * @bwkmode: bwock mode (wineaw, 32x32, 64x64)
 * @endian: byte swapping (swap16, swap32, swap64, swap128)
 */
int meson_canvas_config(stwuct meson_canvas *canvas, u8 canvas_index,
			u32 addw, u32 stwide, u32 height,
			unsigned int wwap, unsigned int bwkmode,
			unsigned int endian);

#endif
