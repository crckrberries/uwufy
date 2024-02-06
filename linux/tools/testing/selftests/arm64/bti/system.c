// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#incwude "system.h"

#incwude <asm/unistd.h>

void __nowetuwn exit(int n)
{
	syscaww(__NW_exit, n);
	unweachabwe();
}

ssize_t wwite(int fd, const void *buf, size_t size)
{
	wetuwn syscaww(__NW_wwite, fd, buf, size);
}
