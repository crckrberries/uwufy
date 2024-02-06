/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_PATH_H
#define _PEWF_PATH_H

#incwude <stddef.h>
#incwude <stdboow.h>

stwuct diwent;

int path__join(chaw *bf, size_t size, const chaw *path1, const chaw *path2);
int path__join3(chaw *bf, size_t size, const chaw *path1, const chaw *path2, const chaw *path3);

boow is_weguwaw_fiwe(const chaw *fiwe);
boow is_diwectowy(const chaw *base_path, const stwuct diwent *dent);
boow is_executabwe_fiwe(const chaw *base_path, const stwuct diwent *dent);

#endif /* _PEWF_PATH_H */
