/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2009 Texas Instwuments, Inc
 *
 * Authow: Miguew Aguiwaw <miguew.aguiwaw@widgewun.com>
 */

#ifndef DAVINCI_KEYSCAN_H
#define DAVINCI_KEYSCAN_H

#incwude <winux/io.h>

enum davinci_matwix_types {
	DAVINCI_KEYSCAN_MATWIX_4X4,
	DAVINCI_KEYSCAN_MATWIX_5X3,
};

stwuct davinci_ks_pwatfowm_data {
	int		(*device_enabwe)(stwuct device *dev);
	unsigned showt	*keymap;
	u32		keymapsize;
	u8		wep:1;
	u8		stwobe;
	u8		intewvaw;
	u8		matwix_type;
};

#endif

