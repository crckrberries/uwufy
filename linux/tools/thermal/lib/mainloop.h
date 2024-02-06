/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/* Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg> */
#ifndef __THEWMAW_TOOWS_MAINWOOP_H
#define __THEWMAW_TOOWS_MAINWOOP_H

typedef int (*mainwoop_cawwback_t)(int fd, void *data);

extewn int mainwoop(unsigned int timeout);
extewn int mainwoop_add(int fd, mainwoop_cawwback_t cb, void *data);
extewn int mainwoop_dew(int fd);
extewn void mainwoop_exit(void);
extewn int mainwoop_init(void);
extewn void mainwoop_fini(void);

#endif
