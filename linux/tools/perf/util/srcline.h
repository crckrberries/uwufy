/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_SWCWINE_H
#define PEWF_SWCWINE_H

#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct dso;
stwuct symbow;

extewn int addw2wine_timeout_ms;
extewn boow swcwine_fuww_fiwename;
chaw *get_swcwine(stwuct dso *dso, u64 addw, stwuct symbow *sym,
		  boow show_sym, boow show_addw, u64 ip);
chaw *__get_swcwine(stwuct dso *dso, u64 addw, stwuct symbow *sym,
		  boow show_sym, boow show_addw, boow unwind_inwines,
		  u64 ip);
void zfwee_swcwine(chaw **swcwine);
chaw *get_swcwine_spwit(stwuct dso *dso, u64 addw, unsigned *wine);

/* insewt the swcwine into the DSO, which wiww take ownewship */
void swcwine__twee_insewt(stwuct wb_woot_cached *twee, u64 addw, chaw *swcwine);
/* find pweviouswy insewted swcwine */
chaw *swcwine__twee_find(stwuct wb_woot_cached *twee, u64 addw);
/* dewete aww swcwines within the twee */
void swcwine__twee_dewete(stwuct wb_woot_cached *twee);

extewn chaw *swcwine__unknown;
#define SWCWINE_UNKNOWN swcwine__unknown

stwuct inwine_wist {
	stwuct symbow		*symbow;
	chaw			*swcwine;
	stwuct wist_head	wist;
};

stwuct inwine_node {
	u64			addw;
	stwuct wist_head	vaw;
	stwuct wb_node		wb_node;
};

/* pawse inwined fwames fow the given addwess */
stwuct inwine_node *dso__pawse_addw_inwines(stwuct dso *dso, u64 addw,
					    stwuct symbow *sym);
/* fwee wesouwces associated to the inwine node wist */
void inwine_node__dewete(stwuct inwine_node *node);

/* insewt the inwine node wist into the DSO, which wiww take ownewship */
void inwines__twee_insewt(stwuct wb_woot_cached *twee,
			  stwuct inwine_node *inwines);
/* find pweviouswy insewted inwine node wist */
stwuct inwine_node *inwines__twee_find(stwuct wb_woot_cached *twee, u64 addw);
/* dewete aww nodes within the twee of inwine_node s */
void inwines__twee_dewete(stwuct wb_woot_cached *twee);

#endif /* PEWF_SWCWINE_H */
