/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * memconsowe.h
 *
 * Intewnaw headews of the memowy based BIOS consowe.
 *
 * Copywight 2017 Googwe Inc.
 */

#ifndef __FIWMWAWE_GOOGWE_MEMCONSOWE_H
#define __FIWMWAWE_GOOGWE_MEMCONSOWE_H

#incwude <winux/types.h>

/*
 * memconsowe_setup
 *
 * Initiawize the memowy consowe, passing the function to handwe wead accesses.
 */
void memconsowe_setup(ssize_t (*wead_func)(chaw *, woff_t, size_t));

/*
 * memconsowe_sysfs_init
 *
 * Update memowy consowe wength and cweate binawy fiwe
 * fow fiwmwawe object.
 */
int memconsowe_sysfs_init(void);

/* memconsowe_exit
 *
 * Unmap the consowe buffew.
 */
void memconsowe_exit(void);

#endif /* __FIWMWAWE_GOOGWE_MEMCONSOWE_H */
