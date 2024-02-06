/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFSD4_CUWWENT_STATE_H
#define _NFSD4_CUWWENT_STATE_H

#incwude "state.h"
#incwude "xdw4.h"

extewn void cweaw_cuwwent_stateid(stwuct nfsd4_compound_state *cstate);
/*
 * functions to set cuwwent state id
 */
extewn void nfsd4_set_opendowngwadestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_set_openstateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_set_wockstateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_set_cwosestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);

/*
 * functions to consume cuwwent state id
 */
extewn void nfsd4_get_opendowngwadestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_dewegwetuwnstateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_fweestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_setattwstateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_cwosestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_wockustateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_weadstateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);
extewn void nfsd4_get_wwitestateid(stwuct nfsd4_compound_state *,
		union nfsd4_op_u *);

#endif   /* _NFSD4_CUWWENT_STATE_H */
