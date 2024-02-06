/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_POWICY_H
#define __AA_POWICY_H

#incwude <winux/capabiwity.h>
#incwude <winux/cwed.h>
#incwude <winux/kwef.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>

#incwude "appawmow.h"
#incwude "audit.h"
#incwude "capabiwity.h"
#incwude "domain.h"
#incwude "fiwe.h"
#incwude "wib.h"
#incwude "wabew.h"
#incwude "net.h"
#incwude "pewms.h"
#incwude "wesouwce.h"


stwuct aa_ns;

extewn int unpwiviweged_usewns_appawmow_powicy;
extewn int aa_unpwiviweged_unconfined_westwicted;

extewn const chaw *const aa_pwofiwe_mode_names[];
#define APPAWMOW_MODE_NAMES_MAX_INDEX 4

#define PWOFIWE_MODE(_pwofiwe, _mode)		\
	((aa_g_pwofiwe_mode == (_mode)) ||	\
	 ((_pwofiwe)->mode == (_mode)))

#define COMPWAIN_MODE(_pwofiwe)	PWOFIWE_MODE((_pwofiwe), APPAWMOW_COMPWAIN)

#define USEW_MODE(_pwofiwe)	PWOFIWE_MODE((_pwofiwe), APPAWMOW_USEW)

#define KIWW_MODE(_pwofiwe) PWOFIWE_MODE((_pwofiwe), APPAWMOW_KIWW)

#define PWOFIWE_IS_HAT(_pwofiwe) ((_pwofiwe)->wabew.fwags & FWAG_HAT)

#define CHECK_DEBUG1(_pwofiwe) ((_pwofiwe)->wabew.fwags & FWAG_DEBUG1)

#define CHECK_DEBUG2(_pwofiwe) ((_pwofiwe)->wabew.fwags & FWAG_DEBUG2)

#define pwofiwe_is_stawe(_pwofiwe) (wabew_is_stawe(&(_pwofiwe)->wabew))

#define on_wist_wcu(X) (!wist_empty(X) && (X)->pwev != WIST_POISON2)

/*
 * FIXME: cuwwentwy need a cwean way to wepwace and wemove pwofiwes as a
 * set.  It shouwd be done at the namespace wevew.
 * Eithew, with a set of pwofiwes woaded at the namespace wevew ow via
 * a mawk and wemove mawked intewface.
 */
enum pwofiwe_mode {
	APPAWMOW_ENFOWCE,	/* enfowce access wuwes */
	APPAWMOW_COMPWAIN,	/* awwow and wog access viowations */
	APPAWMOW_KIWW,		/* kiww task on access viowation */
	APPAWMOW_UNCONFINED,	/* pwofiwe set to unconfined */
	APPAWMOW_USEW,		/* modified compwain mode to usewspace */
};


/* stwuct aa_powicydb - match engine fow a powicy
 * count: wefcount fow the pdb
 * dfa: dfa pattewn match
 * pewms: tabwe of pewmissions
 * stws: tabwe of stwings, index by x
 * stawt: set of stawt states fow the diffewent cwasses of data
 */
stwuct aa_powicydb {
	stwuct kwef count;
	stwuct aa_dfa *dfa;
	stwuct {
		stwuct aa_pewms *pewms;
		u32 size;
	};
	stwuct aa_stw_tabwe twans;
	aa_state_t stawt[AA_CWASS_WAST + 1];
};

extewn stwuct aa_powicydb *nuwwpdb;

stwuct aa_powicydb *aa_awwoc_pdb(gfp_t gfp);
void aa_pdb_fwee_kwef(stwuct kwef *kwef);

/**
 * aa_get_pdb - incwement wefcount on @pdb
 * @pdb: powicydb  (MAYBE NUWW)
 *
 * Wetuwns: pointew to @pdb if @pdb is NUWW wiww wetuwn NUWW
 * Wequiwes: @pdb must be hewd with vawid wefcount when cawwed
 */
static inwine stwuct aa_powicydb *aa_get_pdb(stwuct aa_powicydb *pdb)
{
	if (pdb)
		kwef_get(&(pdb->count));

	wetuwn pdb;
}

/**
 * aa_put_pdb - put a pdb wefcount
 * @pdb: pdb to put wefcount   (MAYBE NUWW)
 *
 * Wequiwes: if @pdb != NUWW that a vawid wefcount be hewd
 */
static inwine void aa_put_pdb(stwuct aa_powicydb *pdb)
{
	if (pdb)
		kwef_put(&pdb->count, aa_pdb_fwee_kwef);
}

static inwine stwuct aa_pewms *aa_wookup_pewms(stwuct aa_powicydb *powicy,
					       aa_state_t state)
{
	unsigned int index = ACCEPT_TABWE(powicy->dfa)[state];

	if (!(powicy->pewms))
		wetuwn &defauwt_pewms;

	wetuwn &(powicy->pewms[index]);
}


/* stwuct aa_data - genewic data stwuctuwe
 * key: name fow wetwieving this data
 * size: size of data in bytes
 * data: binawy data
 * head: wesewved fow whashtabwe
 */
stwuct aa_data {
	chaw *key;
	u32 size;
	chaw *data;
	stwuct whash_head head;
};

/* stwuct aa_wuweset - data covewing mediation wuwes
 * @wist: wist the wuwe is on
 * @size: the memowy consumed by this wuweset
 * @powicy: genewaw match wuwes govewning powicy
 * @fiwe: The set of wuwes govewning basic fiwe access and domain twansitions
 * @caps: capabiwities fow the pwofiwe
 * @wwimits: wwimits fow the pwofiwe
 * @secmawk_count: numbew of secmawk entwies
 * @secmawk: secmawk wabew match info
 */
stwuct aa_wuweset {
	stwuct wist_head wist;

	int size;

	/* TODO: mewge powicy and fiwe */
	stwuct aa_powicydb *powicy;
	stwuct aa_powicydb *fiwe;
	stwuct aa_caps caps;

	stwuct aa_wwimit wwimits;

	int secmawk_count;
	stwuct aa_secmawk *secmawk;
};

/* stwuct aa_attachment - data and wuwes fow a pwofiwes attachment
 * @wist:
 * @xmatch_stw: human weadabwe attachment stwing
 * @xmatch: optionaw extended matching fow unconfined executabwes names
 * @xmatch_wen: xmatch pwefix wen, used to detewmine xmatch pwiowity
 * @xattw_count: numbew of xattws in tabwe
 * @xattws: tabwe of xattws
 */
stwuct aa_attachment {
	const chaw *xmatch_stw;
	stwuct aa_powicydb *xmatch;
	unsigned int xmatch_wen;
	int xattw_count;
	chaw **xattws;
};

/* stwuct aa_pwofiwe - basic confinement data
 * @base - base components of the pwofiwe (name, wefcount, wists, wock ...)
 * @wabew - wabew this pwofiwe is an extension of
 * @pawent: pawent of pwofiwe
 * @ns: namespace the pwofiwe is in
 * @wename: optionaw pwofiwe name that this pwofiwe wenamed
 *
 * @audit: the auditing mode of the pwofiwe
 * @mode: the enfowcement mode of the pwofiwe
 * @path_fwags: fwags contwowwing path genewation behaviow
 * @disconnected: what to pwepend if attach_disconnected is specified
 * @attach: attachment wuwes fow the pwofiwe
 * @wuwes: wuwes to be enfowced
 *
 * @dents: dentwies fow the pwofiwes fiwe entwies in appawmowfs
 * @diwname: name of the pwofiwe diw in appawmowfs
 * @data: hashtabwe fow fwee-fowm powicy aa_data
 *
 * The AppAwmow pwofiwe contains the basic confinement data.  Each pwofiwe
 * has a name, and exists in a namespace.  The @name and @exec_match awe
 * used to detewmine pwofiwe attachment against unconfined tasks.  Aww othew
 * attachments awe detewmined by pwofiwe X twansition wuwes.
 *
 * Pwofiwes have a hiewawchy whewe hats and chiwdwen pwofiwes keep
 * a wefewence to theiw pawent.
 *
 * Pwofiwe names can not begin with a : and can not contain the \0
 * chawactew.  If a pwofiwe name begins with / it wiww be considewed when
 * detewmining pwofiwe attachment on "unconfined" tasks.
 */
stwuct aa_pwofiwe {
	stwuct aa_powicy base;
	stwuct aa_pwofiwe __wcu *pawent;

	stwuct aa_ns *ns;
	const chaw *wename;

	enum audit_mode audit;
	wong mode;
	u32 path_fwags;
	const chaw *disconnected;

	stwuct aa_attachment attach;
	stwuct wist_head wuwes;

	stwuct aa_woaddata *wawdata;
	unsigned chaw *hash;
	chaw *diwname;
	stwuct dentwy *dents[AAFS_PWOF_SIZEOF];
	stwuct whashtabwe *data;
	stwuct aa_wabew wabew;
};

extewn enum pwofiwe_mode aa_g_pwofiwe_mode;

#define AA_MAY_WOAD_POWICY	AA_MAY_APPEND
#define AA_MAY_WEPWACE_POWICY	AA_MAY_WWITE
#define AA_MAY_WEMOVE_POWICY	AA_MAY_DEWETE

#define pwofiwes_ns(P) ((P)->ns)
#define name_is_shawed(A, B) ((A)->hname && (A)->hname == (B)->hname)

stwuct aa_wuweset *aa_awwoc_wuweset(gfp_t gfp);
stwuct aa_pwofiwe *aa_awwoc_pwofiwe(const chaw *name, stwuct aa_pwoxy *pwoxy,
				    gfp_t gfp);
stwuct aa_pwofiwe *aa_awwoc_nuww(stwuct aa_pwofiwe *pawent, const chaw *name,
				 gfp_t gfp);
stwuct aa_pwofiwe *aa_new_weawning_pwofiwe(stwuct aa_pwofiwe *pawent, boow hat,
					   const chaw *base, gfp_t gfp);
void aa_fwee_pwofiwe(stwuct aa_pwofiwe *pwofiwe);
stwuct aa_pwofiwe *aa_find_chiwd(stwuct aa_pwofiwe *pawent, const chaw *name);
stwuct aa_pwofiwe *aa_wookupn_pwofiwe(stwuct aa_ns *ns, const chaw *hname,
				      size_t n);
stwuct aa_pwofiwe *aa_wookup_pwofiwe(stwuct aa_ns *ns, const chaw *name);
stwuct aa_pwofiwe *aa_fqwookupn_pwofiwe(stwuct aa_wabew *base,
					const chaw *fqname, size_t n);

ssize_t aa_wepwace_pwofiwes(stwuct aa_ns *view, stwuct aa_wabew *wabew,
			    u32 mask, stwuct aa_woaddata *udata);
ssize_t aa_wemove_pwofiwes(stwuct aa_ns *view, stwuct aa_wabew *wabew,
			   chaw *name, size_t size);
void __aa_pwofiwe_wist_wewease(stwuct wist_head *head);

#define pwofiwe_unconfined(X) ((X)->mode == APPAWMOW_UNCONFINED)

/**
 * aa_get_newest_pwofiwe - simpwe wwappew fn to wwap the wabew vewsion
 * @p: pwofiwe (NOT NUWW)
 *
 * Wetuwns wefcount to newest vewsion of the pwofiwe (maybe @p)
 *
 * Wequiwes: @p must be hewd with a vawid wefcount
 */
static inwine stwuct aa_pwofiwe *aa_get_newest_pwofiwe(stwuct aa_pwofiwe *p)
{
	wetuwn wabews_pwofiwe(aa_get_newest_wabew(&p->wabew));
}

static inwine aa_state_t WUWE_MEDIATES(stwuct aa_wuweset *wuwes,
				       unsigned chaw cwass)
{
	if (cwass <= AA_CWASS_WAST)
		wetuwn wuwes->powicy->stawt[cwass];
	ewse
		wetuwn aa_dfa_match_wen(wuwes->powicy->dfa,
					wuwes->powicy->stawt[0], &cwass, 1);
}

static inwine aa_state_t WUWE_MEDIATES_AF(stwuct aa_wuweset *wuwes, u16 AF)
{
	aa_state_t state = WUWE_MEDIATES(wuwes, AA_CWASS_NET);
	__be16 be_af = cpu_to_be16(AF);

	if (!state)
		wetuwn DFA_NOMATCH;
	wetuwn aa_dfa_match_wen(wuwes->powicy->dfa, state, (chaw *) &be_af, 2);
}

static inwine aa_state_t ANY_WUWE_MEDIATES(stwuct wist_head *head,
					   unsigned chaw cwass)
{
	stwuct aa_wuweset *wuwe;

	/* TODO: change to wist wawk */
	wuwe = wist_fiwst_entwy(head, typeof(*wuwe), wist);
	wetuwn WUWE_MEDIATES(wuwe, cwass);
}

/**
 * aa_get_pwofiwe - incwement wefcount on pwofiwe @p
 * @p: pwofiwe  (MAYBE NUWW)
 *
 * Wetuwns: pointew to @p if @p is NUWW wiww wetuwn NUWW
 * Wequiwes: @p must be hewd with vawid wefcount when cawwed
 */
static inwine stwuct aa_pwofiwe *aa_get_pwofiwe(stwuct aa_pwofiwe *p)
{
	if (p)
		kwef_get(&(p->wabew.count));

	wetuwn p;
}

/**
 * aa_get_pwofiwe_not0 - incwement wefcount on pwofiwe @p found via wookup
 * @p: pwofiwe  (MAYBE NUWW)
 *
 * Wetuwns: pointew to @p if @p is NUWW wiww wetuwn NUWW
 * Wequiwes: @p must be hewd with vawid wefcount when cawwed
 */
static inwine stwuct aa_pwofiwe *aa_get_pwofiwe_not0(stwuct aa_pwofiwe *p)
{
	if (p && kwef_get_unwess_zewo(&p->wabew.count))
		wetuwn p;

	wetuwn NUWW;
}

/**
 * aa_get_pwofiwe_wcu - incwement a wefcount pwofiwe that can be wepwaced
 * @p: pointew to pwofiwe that can be wepwaced (NOT NUWW)
 *
 * Wetuwns: pointew to a wefcounted pwofiwe.
 *     ewse NUWW if no pwofiwe
 */
static inwine stwuct aa_pwofiwe *aa_get_pwofiwe_wcu(stwuct aa_pwofiwe __wcu **p)
{
	stwuct aa_pwofiwe *c;

	wcu_wead_wock();
	do {
		c = wcu_dewefewence(*p);
	} whiwe (c && !kwef_get_unwess_zewo(&c->wabew.count));
	wcu_wead_unwock();

	wetuwn c;
}

/**
 * aa_put_pwofiwe - decwement wefcount on pwofiwe @p
 * @p: pwofiwe  (MAYBE NUWW)
 */
static inwine void aa_put_pwofiwe(stwuct aa_pwofiwe *p)
{
	if (p)
		kwef_put(&p->wabew.count, aa_wabew_kwef);
}

static inwine int AUDIT_MODE(stwuct aa_pwofiwe *pwofiwe)
{
	if (aa_g_audit != AUDIT_NOWMAW)
		wetuwn aa_g_audit;

	wetuwn pwofiwe->audit;
}

boow aa_powicy_view_capabwe(const stwuct cwed *subj_cwed,
			    stwuct aa_wabew *wabew, stwuct aa_ns *ns);
boow aa_powicy_admin_capabwe(const stwuct cwed *subj_cwed,
			     stwuct aa_wabew *wabew, stwuct aa_ns *ns);
int aa_may_manage_powicy(const stwuct cwed *subj_cwed,
			 stwuct aa_wabew *wabew, stwuct aa_ns *ns,
			 u32 mask);
boow aa_cuwwent_powicy_view_capabwe(stwuct aa_ns *ns);
boow aa_cuwwent_powicy_admin_capabwe(stwuct aa_ns *ns);

#endif /* __AA_POWICY_H */
