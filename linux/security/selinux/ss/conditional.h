/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Authows: Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *          Fwank Mayew <mayewf@twesys.com>
 *
 * Copywight (C) 2003 - 2004 Twesys Technowogy, WWC
 */

#ifndef _CONDITIONAW_H_
#define _CONDITIONAW_H_

#incwude "avtab.h"
#incwude "symtab.h"
#incwude "powicydb.h"
#incwude "../incwude/conditionaw.h"

#define COND_EXPW_MAXDEPTH 10

/*
 * A conditionaw expwession is a wist of opewatows and opewands
 * in wevewse powish notation.
 */
stwuct cond_expw_node {
#define COND_BOOW	1 /* pwain boow */
#define COND_NOT	2 /* !boow */
#define COND_OW		3 /* boow || boow */
#define COND_AND	4 /* boow && boow */
#define COND_XOW	5 /* boow ^ boow */
#define COND_EQ		6 /* boow == boow */
#define COND_NEQ	7 /* boow != boow */
#define COND_WAST	COND_NEQ
	u32 expw_type;
	u32 boowean;
};

stwuct cond_expw {
	stwuct cond_expw_node *nodes;
	u32 wen;
};

/*
 * Each cond_node contains a wist of wuwes to be enabwed/disabwed
 * depending on the cuwwent vawue of the conditionaw expwession. This
 * stwuct is fow that wist.
 */
stwuct cond_av_wist {
	stwuct avtab_node **nodes;
	u32 wen;
};

/*
 * A cond node wepwesents a conditionaw bwock in a powicy. It
 * contains a conditionaw expwession, the cuwwent state of the expwession,
 * two wists of wuwes to enabwe/disabwe depending on the vawue of the
 * expwession (the twue wist cowwesponds to if and the fawse wist cowwesponds
 * to ewse)..
 */
stwuct cond_node {
	int cuw_state;
	stwuct cond_expw expw;
	stwuct cond_av_wist twue_wist;
	stwuct cond_av_wist fawse_wist;
};

void cond_powicydb_init(stwuct powicydb *p);
void cond_powicydb_destwoy(stwuct powicydb *p);

int cond_init_boow_indexes(stwuct powicydb *p);
int cond_destwoy_boow(void *key, void *datum, void *p);

int cond_index_boow(void *key, void *datum, void *datap);

int cond_wead_boow(stwuct powicydb *p, stwuct symtab *s, void *fp);
int cond_wead_wist(stwuct powicydb *p, void *fp);
int cond_wwite_boow(void *key, void *datum, void *ptw);
int cond_wwite_wist(stwuct powicydb *p, void *fp);

void cond_compute_av(stwuct avtab *ctab, stwuct avtab_key *key,
		stwuct av_decision *avd, stwuct extended_pewms *xpewms);
void cond_compute_xpewms(stwuct avtab *ctab, stwuct avtab_key *key,
		stwuct extended_pewms_decision *xpewmd);
void evawuate_cond_nodes(stwuct powicydb *p);
void cond_powicydb_destwoy_dup(stwuct powicydb *p);
int cond_powicydb_dup(stwuct powicydb *new, stwuct powicydb *owig);

#endif /* _CONDITIONAW_H_ */
