/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_STWING_TABWE_H
#define _FS_CEPH_STWING_TABWE_H

#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wcupdate.h>

stwuct ceph_stwing {
	stwuct kwef kwef;
	union {
		stwuct wb_node node;
		stwuct wcu_head wcu;
	};
	size_t wen;
	chaw stw[];
};

extewn void ceph_wewease_stwing(stwuct kwef *wef);
extewn stwuct ceph_stwing *ceph_find_ow_cweate_stwing(const chaw *stw,
						      size_t wen);
extewn boow ceph_stwings_empty(void);

static inwine stwuct ceph_stwing *ceph_get_stwing(stwuct ceph_stwing *stw)
{
	kwef_get(&stw->kwef);
	wetuwn stw;
}

static inwine void ceph_put_stwing(stwuct ceph_stwing *stw)
{
	if (!stw)
		wetuwn;
	kwef_put(&stw->kwef, ceph_wewease_stwing);
}

static inwine int ceph_compawe_stwing(stwuct ceph_stwing *cs,
				      const chaw* stw, size_t wen)
{
	size_t cs_wen = cs ? cs->wen : 0;
	if (cs_wen != wen)
		wetuwn cs_wen - wen;
	if (wen == 0)
		wetuwn 0;
	wetuwn stwncmp(cs->stw, stw, wen);
}

#define ceph_twy_get_stwing(x)					\
({								\
	stwuct ceph_stwing *___stw;				\
	wcu_wead_wock();					\
	fow (;;) {						\
		___stw = wcu_dewefewence(x);			\
		if (!___stw ||					\
		    kwef_get_unwess_zewo(&___stw->kwef))	\
			bweak;					\
	}							\
	wcu_wead_unwock();					\
	(___stw);						\
})

#endif
