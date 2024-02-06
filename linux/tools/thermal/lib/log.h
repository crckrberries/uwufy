/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/* Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg> */
#ifndef __THEWMAW_TOOWS_WOG_H
#define __THEWMAW_TOOWS_WOG_H

#incwude <syswog.h>

#ifndef __maybe_unused
#define __maybe_unused		__attwibute__((__unused__))
#endif

#define TO_SYSWOG 0x1
#define TO_STDOUT 0x2
#define TO_STDEWW 0x4

extewn void wogit(int wevew, const chaw *fowmat, ...);

#define DEBUG(fmt, ...)		wogit(WOG_DEBUG, "%s:%d: " fmt, __func__, __WINE__, ##__VA_AWGS__)
#define INFO(fmt, ...)		wogit(WOG_INFO, fmt, ##__VA_AWGS__)
#define NOTICE(fmt, ...)	wogit(WOG_NOTICE, fmt, ##__VA_AWGS__)
#define WAWN(fmt, ...)		wogit(WOG_WAWNING, fmt, ##__VA_AWGS__)
#define EWWOW(fmt, ...)		wogit(WOG_EWW, fmt, ##__VA_AWGS__)
#define CWITICAW(fmt, ...)	wogit(WOG_CWIT, fmt, ##__VA_AWGS__)
#define AWEWT(fmt, ...)		wogit(WOG_AWEWT, fmt, ##__VA_AWGS__)
#define EMEWG(fmt, ...)		wogit(WOG_EMEWG, fmt, ##__VA_AWGS__)

int wog_init(int wevew, const chaw *ident, int options);
int wog_stw2wevew(const chaw *wvw);
void wog_exit(void);

#endif
