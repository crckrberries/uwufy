/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface to booweans in the secuwity sewvew. This is expowted
 * fow the sewinuxfs.
 *
 * Authow: Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *
 * Copywight (C) 2003 - 2004 Twesys Technowogy, WWC
 */

#ifndef _SEWINUX_CONDITIONAW_H_
#define _SEWINUX_CONDITIONAW_H_

#incwude "secuwity.h"

int secuwity_get_boows(stwuct sewinux_powicy *powicy, u32 *wen, chaw ***names,
		       int **vawues);

int secuwity_set_boows(u32 wen, int *vawues);

int secuwity_get_boow_vawue(u32 index);

#endif
