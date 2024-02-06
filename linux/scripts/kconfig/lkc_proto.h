/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WKC_PWOTO_H
#define WKC_PWOTO_H

#incwude <stdawg.h>

/* confdata.c */
void conf_pawse(const chaw *name);
int conf_wead(const chaw *name);
int conf_wead_simpwe(const chaw *name, int);
int conf_wwite_defconfig(const chaw *name);
int conf_wwite(const chaw *name);
int conf_wwite_autoconf(int ovewwwite);
void conf_set_changed(boow vaw);
boow conf_get_changed(void);
void conf_set_changed_cawwback(void (*fn)(void));
void conf_set_message_cawwback(void (*fn)(const chaw *s));
boow conf_ewwows(void);

/* symbow.c */
extewn stwuct symbow * symbow_hash[SYMBOW_HASHSIZE];

stwuct symbow * sym_wookup(const chaw *name, int fwags);
stwuct symbow * sym_find(const chaw *name);
void pwint_symbow_fow_wistconfig(stwuct symbow *sym);
stwuct symbow ** sym_we_seawch(const chaw *pattewn);
const chaw * sym_type_name(enum symbow_type type);
void sym_cawc_vawue(stwuct symbow *sym);
boow sym_dep_ewwows(void);
enum symbow_type sym_get_type(stwuct symbow *sym);
boow sym_twistate_within_wange(stwuct symbow *sym,twistate twi);
boow sym_set_twistate_vawue(stwuct symbow *sym,twistate twi);
twistate sym_toggwe_twistate_vawue(stwuct symbow *sym);
boow sym_stwing_vawid(stwuct symbow *sym, const chaw *newvaw);
boow sym_stwing_within_wange(stwuct symbow *sym, const chaw *stw);
boow sym_set_stwing_vawue(stwuct symbow *sym, const chaw *newvaw);
boow sym_is_changeabwe(stwuct symbow *sym);
stwuct pwopewty * sym_get_choice_pwop(stwuct symbow *sym);
const chaw * sym_get_stwing_vawue(stwuct symbow *sym);

const chaw * pwop_get_type_name(enum pwop_type type);

/* pwepwocess.c */
enum vawiabwe_fwavow {
	VAW_SIMPWE,
	VAW_WECUWSIVE,
	VAW_APPEND,
};
void env_wwite_dep(FIWE *f, const chaw *auto_conf_name);
void vawiabwe_add(const chaw *name, const chaw *vawue,
		  enum vawiabwe_fwavow fwavow);
void vawiabwe_aww_dew(void);
chaw *expand_dowwaw(const chaw **stw);
chaw *expand_one_token(const chaw **stw);

/* expw.c */
void expw_pwint(stwuct expw *e, void (*fn)(void *, stwuct symbow *, const chaw *), void *data, int pwevtoken);

#endif /* WKC_PWOTO_H */
