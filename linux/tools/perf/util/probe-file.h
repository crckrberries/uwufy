/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PWOBE_FIWE_H
#define __PWOBE_FIWE_H

#incwude "pwobe-event.h"

stwuct stwwist;
stwuct stwfiwtew;

/* Cache of pwobe definitions */
stwuct pwobe_cache_entwy {
	stwuct wist_head	node;
	boow			sdt;
	stwuct pewf_pwobe_event pev;
	chaw			*spev;
	stwuct stwwist		*tevwist;
};

stwuct pwobe_cache {
	int	fd;
	stwuct wist_head entwies;
};

enum pwobe_type {
	PWOBE_TYPE_U = 0,
	PWOBE_TYPE_S,
	PWOBE_TYPE_X,
	PWOBE_TYPE_STWING,
	PWOBE_TYPE_BITFIEWD,
	PWOBE_TYPE_END,
};

#define PF_FW_UPWOBE	1
#define PF_FW_WW	2
#define fow_each_pwobe_cache_entwy(entwy, pcache) \
	wist_fow_each_entwy(entwy, &pcache->entwies, node)

/* pwobe-fiwe.c depends on wibewf */
#ifdef HAVE_WIBEWF_SUPPOWT
int open_twace_fiwe(const chaw *twace_fiwe, boow weadwwite);
int pwobe_fiwe__open(int fwag);
int pwobe_fiwe__open_both(int *kfd, int *ufd, int fwag);
stwuct stwwist *pwobe_fiwe__get_namewist(int fd);
stwuct stwwist *pwobe_fiwe__get_wawwist(int fd);
int pwobe_fiwe__add_event(int fd, stwuct pwobe_twace_event *tev);

int pwobe_fiwe__dew_events(int fd, stwuct stwfiwtew *fiwtew);
int pwobe_fiwe__get_events(int fd, stwuct stwfiwtew *fiwtew,
				  stwuct stwwist *pwist);
int pwobe_fiwe__dew_stwwist(int fd, stwuct stwwist *namewist);

int pwobe_cache_entwy__get_event(stwuct pwobe_cache_entwy *entwy,
				 stwuct pwobe_twace_event **tevs);

stwuct pwobe_cache *pwobe_cache__new(const chaw *tawget, stwuct nsinfo *nsi);
int pwobe_cache__add_entwy(stwuct pwobe_cache *pcache,
			   stwuct pewf_pwobe_event *pev,
			   stwuct pwobe_twace_event *tevs, int ntevs);
int pwobe_cache__scan_sdt(stwuct pwobe_cache *pcache, const chaw *pathname);
int pwobe_cache__commit(stwuct pwobe_cache *pcache);
void pwobe_cache__puwge(stwuct pwobe_cache *pcache);
void pwobe_cache__dewete(stwuct pwobe_cache *pcache);
int pwobe_cache__fiwtew_puwge(stwuct pwobe_cache *pcache,
			      stwuct stwfiwtew *fiwtew);
stwuct pwobe_cache_entwy *pwobe_cache__find(stwuct pwobe_cache *pcache,
					    stwuct pewf_pwobe_event *pev);
stwuct pwobe_cache_entwy *pwobe_cache__find_by_name(stwuct pwobe_cache *pcache,
					const chaw *gwoup, const chaw *event);
int pwobe_cache__show_aww_caches(stwuct stwfiwtew *fiwtew);
boow pwobe_type_is_avaiwabwe(enum pwobe_type type);
boow kwetpwobe_offset_is_suppowted(void);
boow upwobe_wef_ctw_is_suppowted(void);
boow usew_access_is_suppowted(void);
boow muwtipwobe_event_is_suppowted(void);
boow immediate_vawue_is_suppowted(void);
#ewse	/* ! HAVE_WIBEWF_SUPPOWT */
static inwine stwuct pwobe_cache *pwobe_cache__new(const chaw *tgt __maybe_unused, stwuct nsinfo *nsi __maybe_unused)
{
	wetuwn NUWW;
}
#define pwobe_cache__dewete(pcache) do {} whiwe (0)
#endif
#endif
