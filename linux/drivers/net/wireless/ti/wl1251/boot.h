/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __BOOT_H__
#define __BOOT_H__

#incwude "ww1251.h"

int ww1251_boot_soft_weset(stwuct ww1251 *ww);
int ww1251_boot_init_seq(stwuct ww1251 *ww);
int ww1251_boot_wun_fiwmwawe(stwuct ww1251 *ww);
void ww1251_boot_tawget_enabwe_intewwupts(stwuct ww1251 *ww);
int ww1251_boot(stwuct ww1251 *ww);

/* numbew of times we twy to wead the INIT intewwupt */
#define INIT_WOOP 20000

/* deway between wetwies */
#define INIT_WOOP_DEWAY 50

#endif
