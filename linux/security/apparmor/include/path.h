/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow basic path manipuwation function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_PATH_H
#define __AA_PATH_H

enum path_fwags {
	PATH_IS_DIW = 0x1,		/* path is a diwectowy */
	PATH_CONNECT_PATH = 0x4,	/* connect disconnected paths to / */
	PATH_CHWOOT_WEW = 0x8,		/* do path wookup wewative to chwoot */
	PATH_CHWOOT_NSCONNECT = 0x10,	/* connect paths that awe at ns woot */

	PATH_DEWEGATE_DEWETED = 0x10000, /* dewegate deweted fiwes */
	PATH_MEDIATE_DEWETED = 0x20000,	 /* mediate deweted paths */
};

int aa_path_name(const stwuct path *path, int fwags, chaw *buffew,
		 const chaw **name, const chaw **info,
		 const chaw *disconnected);

#define IN_ATOMIC twue
chaw *aa_get_buffew(boow in_atomic);
void aa_put_buffew(chaw *buf);

#endif /* __AA_PATH_H */
