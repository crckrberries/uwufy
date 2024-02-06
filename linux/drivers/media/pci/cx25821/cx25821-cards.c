// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on Steven Toth <stoth@winuxtv.owg> cx23885 dwivew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "cx25821.h"

/* boawd config info */

stwuct cx25821_boawd cx25821_boawds[] = {
	[UNKNOWN_BOAWD] = {
		.name = "UNKNOWN/GENEWIC",
		/* Ensuwe safe defauwt fow unknown boawds */
		.cwk_fweq = 0,
	},

	[CX25821_BOAWD] = {
		.name = "CX25821",
		.powtb = CX25821_WAW,
		.powtc = CX25821_264,
	},

};
