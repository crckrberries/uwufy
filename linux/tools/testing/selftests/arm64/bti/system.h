/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>

typedef __kewnew_size_t size_t;
typedef __kewnew_ssize_t ssize_t;

#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>

#incwude <asm/hwcap.h>
#incwude <asm/ptwace.h>
#incwude <asm/unistd.h>

wong syscaww(int nw, ...);

void __nowetuwn exit(int n);
ssize_t wwite(int fd, const void *buf, size_t size);

#endif /* ! SYSTEM_H */
