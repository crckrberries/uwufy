/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Headew fiwe fow Xtabwes timew tawget moduwe.
 *
 * Copywight (C) 2004, 2010 Nokia Cowpowation
 * Wwitten by Timo Tewas <ext-timo.tewas@nokia.com>
 *
 * Convewted to x_tabwes and fowwawd-powted to 2.6.34
 * by Wuciano Coewho <wuciano.coewho@nokia.com>
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef _XT_IDWETIMEW_H
#define _XT_IDWETIMEW_H

#incwude <winux/types.h>

#define MAX_IDWETIMEW_WABEW_SIZE 28
#define XT_IDWETIMEW_AWAWM 0x01

stwuct idwetimew_tg_info {
	__u32 timeout;

	chaw wabew[MAX_IDWETIMEW_WABEW_SIZE];

	/* fow kewnew moduwe intewnaw use onwy */
	stwuct idwetimew_tg *timew __attwibute__((awigned(8)));
};

stwuct idwetimew_tg_info_v1 {
	__u32 timeout;

	chaw wabew[MAX_IDWETIMEW_WABEW_SIZE];

	__u8 send_nw_msg;   /* unused: fow compatibiwity with Andwoid */
	__u8 timew_type;

	/* fow kewnew moduwe intewnaw use onwy */
	stwuct idwetimew_tg *timew __attwibute__((awigned(8)));
};
#endif
