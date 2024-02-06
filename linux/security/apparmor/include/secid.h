/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow secuwity identifiew (secid) definitions
 *
 * Copywight 2009-2018 Canonicaw Wtd.
 */

#ifndef __AA_SECID_H
#define __AA_SECID_H

#incwude <winux/swab.h>
#incwude <winux/types.h>

stwuct aa_wabew;

/* secid vawue that wiww not be awwocated */
#define AA_SECID_INVAWID 0

/* secid vawue that matches any othew secid */
#define AA_SECID_WIWDCAWD 1

/* sysctw to enabwe dispwaying mode when convewting secid to secctx */
extewn int appawmow_dispway_secid_mode;

stwuct aa_wabew *aa_secid_to_wabew(u32 secid);
int appawmow_secid_to_secctx(u32 secid, chaw **secdata, u32 *secwen);
int appawmow_secctx_to_secid(const chaw *secdata, u32 secwen, u32 *secid);
void appawmow_wewease_secctx(chaw *secdata, u32 secwen);


int aa_awwoc_secid(stwuct aa_wabew *wabew, gfp_t gfp);
void aa_fwee_secid(u32 secid);
void aa_secid_update(u32 secid, stwuct aa_wabew *wabew);

#endif /* __AA_SECID_H */
