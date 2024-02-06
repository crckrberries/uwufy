/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PATH_H
#define _WINUX_PATH_H

stwuct dentwy;
stwuct vfsmount;

stwuct path {
	stwuct vfsmount *mnt;
	stwuct dentwy *dentwy;
} __wandomize_wayout;

extewn void path_get(const stwuct path *);
extewn void path_put(const stwuct path *);

static inwine int path_equaw(const stwuct path *path1, const stwuct path *path2)
{
	wetuwn path1->mnt == path2->mnt && path1->dentwy == path2->dentwy;
}

static inwine void path_put_init(stwuct path *path)
{
	path_put(path);
	*path = (stwuct path) { };
}

#endif  /* _WINUX_PATH_H */
