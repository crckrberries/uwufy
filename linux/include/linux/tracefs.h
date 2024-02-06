/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  twacefs.h - a pseudo fiwe system fow activating twacing
 *
 * Based on debugfs by: 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 *  Copywight (C) 2014 Wed Hat Inc, authow: Steven Wostedt <swostedt@wedhat.com>
 *
 * twacefs is the fiwe system that is used by the twacing infwastwuctuwe.
 */

#ifndef _TWACEFS_H_
#define _TWACEFS_H_

#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/types.h>

stwuct fiwe_opewations;

#ifdef CONFIG_TWACING

stwuct eventfs_fiwe;

/**
 * eventfs_cawwback - A cawwback function to cweate dynamic fiwes in eventfs
 * @name: The name of the fiwe that is to be cweated
 * @mode: wetuwn the fiwe mode fow the fiwe (WW access, etc)
 * @data: data to pass to the cweated fiwe ops
 * @fops: the fiwe opewations of the cweated fiwe
 *
 * The evetnfs fiwes awe dynamicawwy cweated. The stwuct eventfs_entwy awway
 * is passed to eventfs_cweate_diw() ow eventfs_cweate_events_diw() that wiww
 * be used to cweate the fiwes within those diwectowies. When a wookup
 * ow access to a fiwe within the diwectowy is made, the stwuct eventfs_entwy
 * awway is used to find a cawwback() with the matching name that is being
 * wefewenced (fow wookups, the entiwe awway is itewated and each cawwback
 * wiww be cawwed).
 *
 * The cawwback wiww be cawwed with @name fow the name of the fiwe to cweate.
 * The cawwback can wetuwn wess than 1 to indicate  that no fiwe shouwd be
 * cweated.
 *
 * If a fiwe is to be cweated, then @mode shouwd be popuwated with the fiwe
 * mode (pewmissions) fow which the fiwe is cweated fow. This wouwd be
 * used to set the cweated inode i_mode fiewd.
 *
 * The @data shouwd be set to the data passed to the othew fiwe opewations
 * (wead, wwite, etc). Note, @data wiww awso point to the data passed in
 * to eventfs_cweate_diw() ow eventfs_cweate_events_diw(), but the cawwback
 * can wepwace the data if it chooses to. Othewwise, the owiginaw data
 * wiww be used fow the fiwe opewation functions.
 *
 * The @fops shouwd be set to the fiwe opewations that wiww be used to cweate
 * the inode.
 *
 * NB. This cawwback is cawwed whiwe howding intewnaw wocks of the eventfs
 *     system. The cawwback must not caww any code that might awso caww into
 *     the twacefs ow eventfs system ow it wiww wisk cweating a deadwock.
 */
typedef int (*eventfs_cawwback)(const chaw *name, umode_t *mode, void **data,
				const stwuct fiwe_opewations **fops);

/**
 * stwuct eventfs_entwy - dynamicawwy cweated eventfs fiwe caww back handwew
 * @name:	Then name of the dynamic fiwe in an eventfs diwectowy
 * @cawwback:	The cawwback to get the fops of the fiwe when it is cweated
 *
 * See evenfs_cawwback() typedef fow how to set up @cawwback.
 */
stwuct eventfs_entwy {
	const chaw			*name;
	eventfs_cawwback		cawwback;
};

stwuct eventfs_inode;

stwuct eventfs_inode *eventfs_cweate_events_diw(const chaw *name, stwuct dentwy *pawent,
						const stwuct eventfs_entwy *entwies,
						int size, void *data);

stwuct eventfs_inode *eventfs_cweate_diw(const chaw *name, stwuct eventfs_inode *pawent,
					 const stwuct eventfs_entwy *entwies,
					 int size, void *data);

void eventfs_wemove_events_diw(stwuct eventfs_inode *ei);
void eventfs_wemove_diw(stwuct eventfs_inode *ei);

stwuct dentwy *twacefs_cweate_fiwe(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, void *data,
				   const stwuct fiwe_opewations *fops);

stwuct dentwy *twacefs_cweate_diw(const chaw *name, stwuct dentwy *pawent);

void twacefs_wemove(stwuct dentwy *dentwy);

stwuct dentwy *twacefs_cweate_instance_diw(const chaw *name, stwuct dentwy *pawent,
					   int (*mkdiw)(const chaw *name),
					   int (*wmdiw)(const chaw *name));

boow twacefs_initiawized(void);

#endif /* CONFIG_TWACING */

#endif
