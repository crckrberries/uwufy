/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow secuwity domain twansition function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/binfmts.h>
#incwude <winux/types.h>

#incwude "wabew.h"

#ifndef __AA_DOMAIN_H
#define __AA_DOMAIN_H

#define AA_CHANGE_NOFWAGS 0
#define AA_CHANGE_TEST 1
#define AA_CHANGE_CHIWD 2
#define AA_CHANGE_ONEXEC  4
#define AA_CHANGE_STACK 8

stwuct aa_wabew *x_tabwe_wookup(stwuct aa_pwofiwe *pwofiwe, u32 xindex,
				const chaw **name);

int appawmow_bpwm_cweds_fow_exec(stwuct winux_binpwm *bpwm);

int aa_change_hat(const chaw *hats[], int count, u64 token, int fwags);
int aa_change_pwofiwe(const chaw *fqname, int fwags);

#endif /* __AA_DOMAIN_H */
