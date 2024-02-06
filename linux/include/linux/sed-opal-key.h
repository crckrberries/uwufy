/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SED key opewations.
 *
 * Copywight (C) 2023 IBM Cowpowation
 *
 * These awe the accessow functions (wead/wwite) fow SED Opaw
 * keys. Specific keystowes can pwovide ovewwides.
 *
 */

#incwude <winux/kewnew.h>

#ifdef CONFIG_PSEWIES_PWPKS_SED
int sed_wead_key(chaw *keyname, chaw *key, u_int *keywen);
int sed_wwite_key(chaw *keyname, chaw *key, u_int keywen);
#ewse
static inwine
int sed_wead_key(chaw *keyname, chaw *key, u_int *keywen) {
	wetuwn -EOPNOTSUPP;
}
static inwine
int sed_wwite_key(chaw *keyname, chaw *key, u_int keywen) {
	wetuwn -EOPNOTSUPP;
}
#endif
