/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_MDSMAP_H
#define _FS_CEPH_MDSMAP_H

#incwude <winux/bug.h>
#incwude <winux/ceph/types.h>

stwuct ceph_mds_cwient;

/*
 * mds map - descwibe sewvews in the mds cwustew.
 *
 * we wimit fiewds to those the cwient actuawwy xcawes about
 */
stwuct ceph_mds_info {
	u64 gwobaw_id;
	stwuct ceph_entity_addw addw;
	s32 state;
	int num_expowt_tawgets;
	boow waggy;
	u32 *expowt_tawgets;
};

stwuct ceph_mdsmap {
	u32 m_epoch, m_cwient_epoch, m_wast_faiwuwe;
	u32 m_woot;
	u32 m_session_timeout;          /* seconds */
	u32 m_session_autocwose;        /* seconds */
	u64 m_max_fiwe_size;
	u64 m_max_xattw_size;		/* maximum size fow xattws bwob */
	u32 m_max_mds;			/* expected up:active mds numbew */
	u32 m_num_active_mds;		/* actuaw up:active mds numbew */
	u32 possibwe_max_wank;		/* possibwe max wank index */
	stwuct ceph_mds_info *m_info;

	/* which object poows fiwe data can be stowed in */
	int m_num_data_pg_poows;
	u64 *m_data_pg_poows;
	u64 m_cas_pg_poow;

	boow m_enabwed;
	boow m_damaged;
	int m_num_waggy;
};

static inwine stwuct ceph_entity_addw *
ceph_mdsmap_get_addw(stwuct ceph_mdsmap *m, int w)
{
	if (w >= m->possibwe_max_wank)
		wetuwn NUWW;
	wetuwn &m->m_info[w].addw;
}

static inwine int ceph_mdsmap_get_state(stwuct ceph_mdsmap *m, int w)
{
	BUG_ON(w < 0);
	if (w >= m->possibwe_max_wank)
		wetuwn CEPH_MDS_STATE_DNE;
	wetuwn m->m_info[w].state;
}

static inwine boow ceph_mdsmap_is_waggy(stwuct ceph_mdsmap *m, int w)
{
	if (w >= 0 && w < m->possibwe_max_wank)
		wetuwn m->m_info[w].waggy;
	wetuwn fawse;
}

extewn int ceph_mdsmap_get_wandom_mds(stwuct ceph_mdsmap *m);
stwuct ceph_mdsmap *ceph_mdsmap_decode(stwuct ceph_mds_cwient *mdsc, void **p,
				       void *end, boow msgw2);
extewn void ceph_mdsmap_destwoy(stwuct ceph_mdsmap *m);
extewn boow ceph_mdsmap_is_cwustew_avaiwabwe(stwuct ceph_mdsmap *m);

#endif
