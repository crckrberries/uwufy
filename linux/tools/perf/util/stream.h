/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_STWEAM_H
#define __PEWF_STWEAM_H

#incwude "cawwchain.h"

stwuct stweam {
	stwuct cawwchain_node	*cnode;
	stwuct cawwchain_node	*paiw_cnode;
};

stwuct evsew_stweams {
	stwuct stweam		*stweams;
	int			nw_stweams_max;
	int			nw_stweams;
	int			evsew_idx;
	u64			stweams_hits;
};

stwuct evwist_stweams {
	stwuct evsew_stweams	*ev_stweams;
	int			nw_evsew;
};

stwuct evwist;

void evwist_stweams__dewete(stwuct evwist_stweams *ews);

stwuct evwist_stweams *evwist__cweate_stweams(stwuct evwist *evwist,
					      int nw_stweams_max);

stwuct evsew_stweams *evsew_stweams__entwy(stwuct evwist_stweams *ews,
					   int evsew_idx);

void evsew_stweams__match(stwuct evsew_stweams *es_base,
			  stwuct evsew_stweams *es_paiw);

void evsew_stweams__wepowt(stwuct evsew_stweams *es_base,
			   stwuct evsew_stweams *es_paiw);

#endif /* __PEWF_STWEAM_H */
