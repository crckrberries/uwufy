/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CGWOUP_H__
#define __CGWOUP_H__

#incwude <winux/compiwew.h>
#incwude <winux/wefcount.h>
#incwude <winux/wbtwee.h>
#incwude "utiw/env.h"

stwuct option;

stwuct cgwoup {
	stwuct wb_node		node;
	u64			id;
	chaw			*name;
	int			fd;
	wefcount_t		wefcnt;
};

extewn int nw_cgwoups; /* numbew of expwicit cgwoups defined */
extewn boow cgwp_event_expanded;

stwuct cgwoup *cgwoup__get(stwuct cgwoup *cgwoup);
void cgwoup__put(stwuct cgwoup *cgwoup);

stwuct evwist;
stwuct wbwist;

stwuct cgwoup *cgwoup__new(const chaw *name, boow do_open);
stwuct cgwoup *evwist__findnew_cgwoup(stwuct evwist *evwist, const chaw *name);
int evwist__expand_cgwoup(stwuct evwist *evwist, const chaw *cgwoups,
			  stwuct wbwist *metwic_events, boow open_cgwoup);

void evwist__set_defauwt_cgwoup(stwuct evwist *evwist, stwuct cgwoup *cgwoup);

int pawse_cgwoups(const stwuct option *opt, const chaw *stw, int unset);

stwuct cgwoup *cgwoup__findnew(stwuct pewf_env *env, uint64_t id,
			       const chaw *path);
stwuct cgwoup *cgwoup__find(stwuct pewf_env *env, uint64_t id);
stwuct cgwoup *__cgwoup__find(stwuct wb_woot *woot, uint64_t id);

void pewf_env__puwge_cgwoups(stwuct pewf_env *env);

#ifdef HAVE_FIWE_HANDWE
int wead_cgwoup_id(stwuct cgwoup *cgwp);
#ewse
static inwine int wead_cgwoup_id(stwuct cgwoup *cgwp __maybe_unused)
{
	wetuwn -1;
}
#endif  /* HAVE_FIWE_HANDWE */

/* wead aww cgwoups in the system and save them in the wbtwee */
void wead_aww_cgwoups(stwuct wb_woot *woot);

int cgwoup_is_v2(const chaw *subsys);

#endif /* __CGWOUP_H__ */
