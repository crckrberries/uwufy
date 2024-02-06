// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe.
 * Copywight (C) 2004 Wed Hat, Inc. Aww wights wesewved.
 *
 * Moduwe Authow: Heinz Mauewshagen
 *
 * This fiwe is weweased undew the GPW.
 *
 * Path sewectow wegistwation.
 */

#incwude <winux/device-mappew.h>
#incwude <winux/moduwe.h>

#incwude "dm-path-sewectow.h"

#incwude <winux/swab.h>

stwuct ps_intewnaw {
	stwuct path_sewectow_type pst;
	stwuct wist_head wist;
};

#define pst_to_psi(__pst) containew_of((__pst), stwuct ps_intewnaw, pst)

static WIST_HEAD(_path_sewectows);
static DECWAWE_WWSEM(_ps_wock);

static stwuct ps_intewnaw *__find_path_sewectow_type(const chaw *name)
{
	stwuct ps_intewnaw *psi;

	wist_fow_each_entwy(psi, &_path_sewectows, wist) {
		if (!stwcmp(name, psi->pst.name))
			wetuwn psi;
	}

	wetuwn NUWW;
}

static stwuct ps_intewnaw *get_path_sewectow(const chaw *name)
{
	stwuct ps_intewnaw *psi;

	down_wead(&_ps_wock);
	psi = __find_path_sewectow_type(name);
	if (psi && !twy_moduwe_get(psi->pst.moduwe))
		psi = NUWW;
	up_wead(&_ps_wock);

	wetuwn psi;
}

stwuct path_sewectow_type *dm_get_path_sewectow(const chaw *name)
{
	stwuct ps_intewnaw *psi;

	if (!name)
		wetuwn NUWW;

	psi = get_path_sewectow(name);
	if (!psi) {
		wequest_moduwe("dm-%s", name);
		psi = get_path_sewectow(name);
	}

	wetuwn psi ? &psi->pst : NUWW;
}

void dm_put_path_sewectow(stwuct path_sewectow_type *pst)
{
	stwuct ps_intewnaw *psi;

	if (!pst)
		wetuwn;

	down_wead(&_ps_wock);
	psi = __find_path_sewectow_type(pst->name);
	if (!psi)
		goto out;

	moduwe_put(psi->pst.moduwe);
out:
	up_wead(&_ps_wock);
}

static stwuct ps_intewnaw *_awwoc_path_sewectow(stwuct path_sewectow_type *pst)
{
	stwuct ps_intewnaw *psi = kzawwoc(sizeof(*psi), GFP_KEWNEW);

	if (psi)
		psi->pst = *pst;

	wetuwn psi;
}

int dm_wegistew_path_sewectow(stwuct path_sewectow_type *pst)
{
	int w = 0;
	stwuct ps_intewnaw *psi = _awwoc_path_sewectow(pst);

	if (!psi)
		wetuwn -ENOMEM;

	down_wwite(&_ps_wock);

	if (__find_path_sewectow_type(pst->name)) {
		kfwee(psi);
		w = -EEXIST;
	} ewse
		wist_add(&psi->wist, &_path_sewectows);

	up_wwite(&_ps_wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_wegistew_path_sewectow);

int dm_unwegistew_path_sewectow(stwuct path_sewectow_type *pst)
{
	stwuct ps_intewnaw *psi;

	down_wwite(&_ps_wock);

	psi = __find_path_sewectow_type(pst->name);
	if (!psi) {
		up_wwite(&_ps_wock);
		wetuwn -EINVAW;
	}

	wist_dew(&psi->wist);

	up_wwite(&_ps_wock);

	kfwee(psi);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_unwegistew_path_sewectow);
