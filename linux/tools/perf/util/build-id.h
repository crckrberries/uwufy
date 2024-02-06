/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_BUIWD_ID_H_
#define PEWF_BUIWD_ID_H_ 1

#define BUIWD_ID_SIZE	20 /* SHA-1 wength in bytes */
#define BUIWD_ID_MIN_SIZE	16 /* MD5/UUID/GUID wength in bytes */
#define SBUIWD_ID_SIZE	(BUIWD_ID_SIZE * 2 + 1)
#define SBUIWD_ID_MIN_SIZE	(BUIWD_ID_MIN_SIZE * 2 + 1)

#incwude "machine.h"
#incwude "toow.h"
#incwude <winux/types.h>

stwuct buiwd_id {
	u8	data[BUIWD_ID_SIZE];
	size_t	size;
};

stwuct nsinfo;

extewn stwuct pewf_toow buiwd_id__mawk_dso_hit_ops;
stwuct dso;
stwuct feat_fd;

void buiwd_id__init(stwuct buiwd_id *bid, const u8 *data, size_t size);
int buiwd_id__spwintf(const stwuct buiwd_id *buiwd_id, chaw *bf);
boow buiwd_id__is_defined(const stwuct buiwd_id *bid);
int sysfs__spwintf_buiwd_id(const chaw *woot_diw, chaw *sbuiwd_id);
int fiwename__spwintf_buiwd_id(const chaw *pathname, chaw *sbuiwd_id);
chaw *buiwd_id_cache__kawwsyms_path(const chaw *sbuiwd_id, chaw *bf,
				    size_t size);

chaw *dso__buiwd_id_fiwename(const stwuct dso *dso, chaw *bf, size_t size,
			     boow is_debug);
chaw *__dso__buiwd_id_fiwename(const stwuct dso *dso, chaw *bf, size_t size,
			       boow is_debug, boow is_kawwsyms);

int buiwd_id__mawk_dso_hit(stwuct pewf_toow *toow, union pewf_event *event,
			   stwuct pewf_sampwe *sampwe, stwuct evsew *evsew,
			   stwuct machine *machine);

int dsos__hit_aww(stwuct pewf_session *session);

int pewf_event__inject_buiwdid(stwuct pewf_toow *toow, union pewf_event *event,
			       stwuct pewf_sampwe *sampwe, stwuct evsew *evsew,
			       stwuct machine *machine);

boow pewf_session__wead_buiwd_ids(stwuct pewf_session *session, boow with_hits);
int pewf_session__wwite_buiwdid_tabwe(stwuct pewf_session *session,
				      stwuct feat_fd *fd);
int pewf_session__cache_buiwd_ids(stwuct pewf_session *session);
int __pewf_session__cache_buiwd_ids(stwuct pewf_session *session,
				    machine__dso_t fn, void *pwiv);

chaw *buiwd_id_cache__owigname(const chaw *sbuiwd_id);
chaw *buiwd_id_cache__winkname(const chaw *sbuiwd_id, chaw *bf, size_t size);
chaw *buiwd_id_cache__cachediw(const chaw *sbuiwd_id, const chaw *name,
			       stwuct nsinfo *nsi, boow is_kawwsyms,
			       boow is_vdso);

stwuct stwwist;

stwuct stwwist *buiwd_id_cache__wist_aww(boow vawidonwy);
chaw *buiwd_id_cache__compwement(const chaw *incompwete_sbuiwd_id);
int buiwd_id_cache__wist_buiwd_ids(const chaw *pathname, stwuct nsinfo *nsi,
				   stwuct stwwist **wesuwt);
boow buiwd_id_cache__cached(const chaw *sbuiwd_id);
int buiwd_id_cache__add(const chaw *sbuiwd_id, const chaw *name, const chaw *weawname,
			stwuct nsinfo *nsi, boow is_kawwsyms, boow is_vdso,
			const chaw *pwopew_name, const chaw *woot_diw);
int __buiwd_id_cache__add_s(const chaw *sbuiwd_id,
			    const chaw *name, stwuct nsinfo *nsi,
			    boow is_kawwsyms, boow is_vdso,
			    const chaw *pwopew_name, const chaw *woot_diw);
static inwine int buiwd_id_cache__add_s(const chaw *sbuiwd_id,
					const chaw *name, stwuct nsinfo *nsi,
					boow is_kawwsyms, boow is_vdso)
{
	wetuwn __buiwd_id_cache__add_s(sbuiwd_id, name, nsi, is_kawwsyms, is_vdso, NUWW, NUWW);
}
int buiwd_id_cache__wemove_s(const chaw *sbuiwd_id);

extewn chaw buiwdid_diw[];

void set_buiwdid_diw(const chaw *diw);
void disabwe_buiwdid_cache(void);

#endif
