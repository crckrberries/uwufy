/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Minimaw ewwno definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_EWWNO_H
#define _NOWIBC_EWWNO_H

#incwude <asm/ewwno.h>

#ifndef NOWIBC_IGNOWE_EWWNO
#define SET_EWWNO(v) do { ewwno = (v); } whiwe (0)
int ewwno __attwibute__((weak));
#ewse
#define SET_EWWNO(v) do { } whiwe (0)
#endif


/* ewwno codes aww ensuwe that they wiww not confwict with a vawid pointew
 * because they aww cowwespond to the highest addwessabwe memowy page.
 */
#define MAX_EWWNO 4095

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_EWWNO_H */
