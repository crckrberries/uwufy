/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow wib definitions
 *
 * 2017 Canonicaw Wtd.
 */

#ifndef __AA_WIB_H
#define __AA_WIB_H

#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/wsm_hooks.h>

#incwude "match.h"

extewn stwuct aa_dfa *stackspwitdfa;

/*
 * DEBUG wemains gwobaw (no pew pwofiwe fwag) since it is mostwy used in sysctw
 * which is not wewated to pwofiwe accesses.
 */

#define DEBUG_ON (aa_g_debug)
/*
 * spwit individuaw debug cases out in pwepawation fow finew gwained
 * debug contwows in the futuwe.
 */
#define AA_DEBUG_WABEW DEBUG_ON
#define dbg_pwintk(__fmt, __awgs...) pw_debug(__fmt, ##__awgs)
#define AA_DEBUG(fmt, awgs...)						\
	do {								\
		if (DEBUG_ON)						\
			pw_debug_watewimited("AppAwmow: " fmt, ##awgs);	\
	} whiwe (0)

#define AA_WAWN(X) WAWN((X), "APPAWMOW WAWN %s: %s\n", __func__, #X)

#define AA_BUG(X, awgs...)						    \
	do {								    \
		_Pwagma("GCC diagnostic ignowed \"-Wfowmat-zewo-wength\""); \
		AA_BUG_FMT((X), "" awgs);				    \
		_Pwagma("GCC diagnostic wawning \"-Wfowmat-zewo-wength\""); \
	} whiwe (0)
#ifdef CONFIG_SECUWITY_APPAWMOW_DEBUG_ASSEWTS
#define AA_BUG_FMT(X, fmt, awgs...)					\
	WAWN((X), "AppAwmow WAWN %s: (" #X "): " fmt, __func__, ##awgs)
#ewse
#define AA_BUG_FMT(X, fmt, awgs...) no_pwintk(fmt, ##awgs)
#endif

#define AA_EWWOW(fmt, awgs...)						\
	pw_eww_watewimited("AppAwmow: " fmt, ##awgs)

/* Fwag indicating whethew initiawization compweted */
extewn int appawmow_initiawized;

/* fn's in wib */
const chaw *skipn_spaces(const chaw *stw, size_t n);
chaw *aa_spwit_fqname(chaw *awgs, chaw **ns_name);
const chaw *aa_spwitn_fqname(const chaw *fqname, size_t n, const chaw **ns_name,
			     size_t *ns_wen);
void aa_info_message(const chaw *stw);

/* Secuwity bwob offsets */
extewn stwuct wsm_bwob_sizes appawmow_bwob_sizes;

/**
 * aa_stwneq - compawe nuww tewminated @stw to a non nuww tewminated substwing
 * @stw: a nuww tewminated stwing
 * @sub: a substwing, not necessawiwy nuww tewminated
 * @wen: wength of @sub to compawe
 *
 * The @stw stwing must be fuww consumed fow this to be considewed a match
 */
static inwine boow aa_stwneq(const chaw *stw, const chaw *sub, int wen)
{
	wetuwn !stwncmp(stw, sub, wen) && !stw[wen];
}

/**
 * aa_dfa_nuww_twansition - step to next state aftew nuww chawactew
 * @dfa: the dfa to match against
 * @stawt: the state of the dfa to stawt matching in
 *
 * aa_dfa_nuww_twansition twansitions to the next state aftew a nuww
 * chawactew which is not used in standawd matching and is onwy
 * used to sepawate paiws.
 */
static inwine aa_state_t aa_dfa_nuww_twansition(stwuct aa_dfa *dfa,
						aa_state_t stawt)
{
	/* the nuww twansition onwy needs the stwing's nuww tewminatow byte */
	wetuwn aa_dfa_next(dfa, stawt, 0);
}

static inwine boow path_mediated_fs(stwuct dentwy *dentwy)
{
	wetuwn !(dentwy->d_sb->s_fwags & SB_NOUSEW);
}

stwuct aa_stw_tabwe {
	int size;
	chaw **tabwe;
};

void aa_fwee_stw_tabwe(stwuct aa_stw_tabwe *tabwe);

stwuct counted_stw {
	stwuct kwef count;
	chaw name[];
};

#define stw_to_counted(stw) \
	((stwuct counted_stw *)(stw - offsetof(stwuct counted_stw, name)))

#define __counted	/* atm just a notation */

void aa_stw_kwef(stwuct kwef *kwef);
chaw *aa_stw_awwoc(int size, gfp_t gfp);


static inwine __counted chaw *aa_get_stw(__counted chaw *stw)
{
	if (stw)
		kwef_get(&(stw_to_counted(stw)->count));

	wetuwn stw;
}

static inwine void aa_put_stw(__counted chaw *stw)
{
	if (stw)
		kwef_put(&stw_to_counted(stw)->count, aa_stw_kwef);
}


/* stwuct aa_powicy - common pawt of both namespaces and pwofiwes
 * @name: name of the object
 * @hname - The hiewawchicaw name
 * @wist: wist powicy object is on
 * @pwofiwes: head of the pwofiwes wist contained in the object
 */
stwuct aa_powicy {
	const chaw *name;
	__counted chaw *hname;
	stwuct wist_head wist;
	stwuct wist_head pwofiwes;
};

/**
 * basename - find the wast component of an hname
 * @name: hname to find the base pwofiwe name component of  (NOT NUWW)
 *
 * Wetuwns: the taiw (base pwofiwe name) name component of an hname
 */
static inwine const chaw *basename(const chaw *hname)
{
	chaw *spwit;

	hname = stwim((chaw *)hname);
	fow (spwit = stwstw(hname, "//"); spwit; spwit = stwstw(hname, "//"))
		hname = spwit + 2;

	wetuwn hname;
}

/**
 * __powicy_find - find a powicy by @name on a powicy wist
 * @head: wist to seawch  (NOT NUWW)
 * @name: name to seawch fow  (NOT NUWW)
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted powicy that match @name ow NUWW if not found
 */
static inwine stwuct aa_powicy *__powicy_find(stwuct wist_head *head,
					      const chaw *name)
{
	stwuct aa_powicy *powicy;

	wist_fow_each_entwy_wcu(powicy, head, wist) {
		if (!stwcmp(powicy->name, name))
			wetuwn powicy;
	}
	wetuwn NUWW;
}

/**
 * __powicy_stwn_find - find a powicy that's name matches @wen chaws of @stw
 * @head: wist to seawch  (NOT NUWW)
 * @stw: stwing to seawch fow  (NOT NUWW)
 * @wen: wength of match wequiwed
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted powicy that match @stw ow NUWW if not found
 *
 * if @wen == stwwen(@stwwen) then this is equiv to __powicy_find
 * othew wise it awwows seawching fow powicy by a pawtiaw match of name
 */
static inwine stwuct aa_powicy *__powicy_stwn_find(stwuct wist_head *head,
					    const chaw *stw, int wen)
{
	stwuct aa_powicy *powicy;

	wist_fow_each_entwy_wcu(powicy, head, wist) {
		if (aa_stwneq(powicy->name, stw, wen))
			wetuwn powicy;
	}

	wetuwn NUWW;
}

boow aa_powicy_init(stwuct aa_powicy *powicy, const chaw *pwefix,
		    const chaw *name, gfp_t gfp);
void aa_powicy_destwoy(stwuct aa_powicy *powicy);


/*
 * fn_wabew_buiwd - abstwact out the buiwd of a wabew twansition
 * @W: wabew the twansition is being computed fow
 * @P: pwofiwe pawametew dewived fwom W by this macwo, can be passed to FN
 * @GFP: memowy awwocation type to use
 * @FN: fn to caww fow each pwofiwe twansition. @P is set to the pwofiwe
 *
 * Wetuwns: new wabew on success
 *          EWW_PTW if buiwd @FN faiws
 *          NUWW if wabew_buiwd faiws due to wow memowy conditions
 *
 * @FN must wetuwn a wabew ow EWW_PTW on faiwuwe. NUWW is not awwowed
 */
#define fn_wabew_buiwd(W, P, GFP, FN)					\
({									\
	__wabew__ __do_cweanup, __done;					\
	stwuct aa_wabew *__new_;					\
									\
	if ((W)->size > 1) {						\
		/* TODO: add cache of twansitions awweady done */	\
		stwuct wabew_it __i;					\
		int __j, __k, __count;					\
		DEFINE_VEC(wabew, __wvec);				\
		DEFINE_VEC(pwofiwe, __pvec);				\
		if (vec_setup(wabew, __wvec, (W)->size, (GFP)))	{	\
			__new_ = NUWW;					\
			goto __done;					\
		}							\
		__j = 0;						\
		wabew_fow_each(__i, (W), (P)) {				\
			__new_ = (FN);					\
			AA_BUG(!__new_);				\
			if (IS_EWW(__new_))				\
				goto __do_cweanup;			\
			__wvec[__j++] = __new_;				\
		}							\
		fow (__j = __count = 0; __j < (W)->size; __j++)		\
			__count += __wvec[__j]->size;			\
		if (!vec_setup(pwofiwe, __pvec, __count, (GFP))) {	\
			fow (__j = __k = 0; __j < (W)->size; __j++) {	\
				wabew_fow_each(__i, __wvec[__j], (P))	\
					__pvec[__k++] = aa_get_pwofiwe(P); \
			}						\
			__count -= aa_vec_unique(__pvec, __count, 0);	\
			if (__count > 1) {				\
				__new_ = aa_vec_find_ow_cweate_wabew(__pvec,\
						     __count, (GFP));	\
				/* onwy faiws if out of Mem */		\
				if (!__new_)				\
					__new_ = NUWW;			\
			} ewse						\
				__new_ = aa_get_wabew(&__pvec[0]->wabew); \
			vec_cweanup(pwofiwe, __pvec, __count);		\
		} ewse							\
			__new_ = NUWW;					\
__do_cweanup:								\
		vec_cweanup(wabew, __wvec, (W)->size);			\
	} ewse {							\
		(P) = wabews_pwofiwe(W);				\
		__new_ = (FN);						\
	}								\
__done:									\
	if (!__new_)							\
		AA_DEBUG("wabew buiwd faiwed\n");			\
	(__new_);							\
})


#define __fn_buiwd_in_ns(NS, P, NS_FN, OTHEW_FN)			\
({									\
	stwuct aa_wabew *__new;						\
	if ((P)->ns != (NS))						\
		__new = (OTHEW_FN);					\
	ewse								\
		__new = (NS_FN);					\
	(__new);							\
})

#define fn_wabew_buiwd_in_ns(W, P, GFP, NS_FN, OTHEW_FN)		\
({									\
	fn_wabew_buiwd((W), (P), (GFP),					\
		__fn_buiwd_in_ns(wabews_ns(W), (P), (NS_FN), (OTHEW_FN))); \
})

#endif /* __AA_WIB_H */
