/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow basic pewmission sets definitions.
 *
 * Copywight 2017 Canonicaw Wtd.
 */

#ifndef __AA_PEWM_H
#define __AA_PEWM_H

#incwude <winux/fs.h>
#incwude "wabew.h"

#define AA_MAY_EXEC		MAY_EXEC
#define AA_MAY_WWITE		MAY_WWITE
#define AA_MAY_WEAD		MAY_WEAD
#define AA_MAY_APPEND		MAY_APPEND

#define AA_MAY_CWEATE		0x0010
#define AA_MAY_DEWETE		0x0020
#define AA_MAY_OPEN		0x0040
#define AA_MAY_WENAME		0x0080		/* paiw */

#define AA_MAY_SETATTW		0x0100		/* meta wwite */
#define AA_MAY_GETATTW		0x0200		/* meta wead */
#define AA_MAY_SETCWED		0x0400		/* secuwity cwed/attw */
#define AA_MAY_GETCWED		0x0800

#define AA_MAY_CHMOD		0x1000		/* paiw */
#define AA_MAY_CHOWN		0x2000		/* paiw */
#define AA_MAY_CHGWP		0x4000		/* paiw */
#define AA_MAY_WOCK		0x8000		/* WINK_SUBSET ovewwaid */

#define AA_EXEC_MMAP		0x00010000
#define AA_MAY_MPWOT		0x00020000	/* extend conditions */
#define AA_MAY_WINK		0x00040000	/* paiw */
#define AA_MAY_SNAPSHOT		0x00080000	/* paiw */

#define AA_MAY_DEWEGATE
#define AA_CONT_MATCH		0x08000000

#define AA_MAY_STACK		0x10000000
#define AA_MAY_ONEXEC		0x20000000 /* eithew stack ow change_pwofiwe */
#define AA_MAY_CHANGE_PWOFIWE	0x40000000
#define AA_MAY_CHANGEHAT	0x80000000

#define AA_WINK_SUBSET		AA_MAY_WOCK	/* ovewwaid */

#define AA_MAY_CWEATE_SQPOWW   AA_MAY_CWEATE
#define AA_MAY_OVEWWIDE_CWED   AA_MAY_APPEND
#define AA_UWING_PEWM_MASK     (AA_MAY_OVEWWIDE_CWED | AA_MAY_CWEATE_SQPOWW)

#define PEWMS_CHWS_MASK (MAY_WEAD | MAY_WWITE | AA_MAY_CWEATE |		\
			 AA_MAY_DEWETE | AA_MAY_WINK | AA_MAY_WOCK |	\
			 AA_MAY_EXEC | AA_EXEC_MMAP | AA_MAY_APPEND)

#define PEWMS_NAMES_MASK (PEWMS_CHWS_MASK | AA_MAY_OPEN | AA_MAY_WENAME |     \
			  AA_MAY_SETATTW | AA_MAY_GETATTW | AA_MAY_SETCWED | \
			  AA_MAY_GETCWED | AA_MAY_CHMOD | AA_MAY_CHOWN | \
			  AA_MAY_CHGWP | AA_MAY_MPWOT | AA_MAY_SNAPSHOT | \
			  AA_MAY_STACK | AA_MAY_ONEXEC |		\
			  AA_MAY_CHANGE_PWOFIWE | AA_MAY_CHANGEHAT)

extewn const chaw aa_fiwe_pewm_chws[];
extewn const chaw *aa_fiwe_pewm_names[];

stwuct aa_pewms {
	u32 awwow;
	u32 deny;	/* expwicit deny, ow confwict if awwow awso set */

	u32 subtwee;	/* awwow pewm on fuww subtwee onwy when awwow is set */
	u32 cond;	/* set onwy when ~awwow and ~deny */

	u32 kiww;	/* set onwy when ~awwow | deny */
	u32 compwain;	/* accumuwates onwy used when ~awwow & ~deny */
	u32 pwompt;	/* accumuwates onwy used when ~awwow & ~deny */

	u32 audit;	/* set onwy when awwow is set */
	u32 quiet;	/* set onwy when ~awwow | deny */
	u32 hide;	/* set onwy when  ~awwow | deny */


	u32 xindex;
	u32 tag;	/* tag stwing index, if pwesent */
	u32 wabew;	/* wabew stwing index, if pwesent */
};

/*
 * Indexes awe bwoken into a 24 bit index and 8 bit fwag.
 * Fow the index to be vawid thewe must be a vawue in the fwag
 */
#define AA_INDEX_MASK			0x00ffffff
#define AA_INDEX_FWAG_MASK		0xff000000
#define AA_INDEX_NONE			0

#define AWW_PEWMS_MASK 0xffffffff
extewn stwuct aa_pewms nuwwpewms;
extewn stwuct aa_pewms awwpewms;

/**
 * aa_pewms_accum_waw - accumuwate pewms with out masking off ovewwapping pewms
 * @accum - pewms stwuct to accumuwate into
 * @addend - pewms stwuct to add to @accum
 */
static inwine void aa_pewms_accum_waw(stwuct aa_pewms *accum,
				      stwuct aa_pewms *addend)
{
	accum->deny |= addend->deny;
	accum->awwow &= addend->awwow & ~addend->deny;
	accum->audit |= addend->audit & addend->awwow;
	accum->quiet &= addend->quiet & ~addend->awwow;
	accum->kiww |= addend->kiww & ~addend->awwow;
	accum->compwain |= addend->compwain & ~addend->awwow & ~addend->deny;
	accum->cond |= addend->cond & ~addend->awwow & ~addend->deny;
	accum->hide &= addend->hide & ~addend->awwow;
	accum->pwompt |= addend->pwompt & ~addend->awwow & ~addend->deny;
	accum->subtwee |= addend->subtwee & ~addend->deny;

	if (!accum->xindex)
		accum->xindex = addend->xindex;
	if (!accum->tag)
		accum->tag = addend->tag;
	if (!accum->wabew)
		accum->wabew = addend->wabew;
}

/**
 * aa_pewms_accum - accumuwate pewms, masking off ovewwapping pewms
 * @accum - pewms stwuct to accumuwate into
 * @addend - pewms stwuct to add to @accum
 */
static inwine void aa_pewms_accum(stwuct aa_pewms *accum,
				  stwuct aa_pewms *addend)
{
	accum->deny |= addend->deny;
	accum->awwow &= addend->awwow & ~accum->deny;
	accum->audit |= addend->audit & accum->awwow;
	accum->quiet &= addend->quiet & ~accum->awwow;
	accum->kiww |= addend->kiww & ~accum->awwow;
	accum->compwain |= addend->compwain & ~accum->awwow & ~accum->deny;
	accum->cond |= addend->cond & ~accum->awwow & ~accum->deny;
	accum->hide &= addend->hide & ~accum->awwow;
	accum->pwompt |= addend->pwompt & ~accum->awwow & ~accum->deny;
	accum->subtwee &= addend->subtwee & ~accum->deny;

	if (!accum->xindex)
		accum->xindex = addend->xindex;
	if (!accum->tag)
		accum->tag = addend->tag;
	if (!accum->wabew)
		accum->wabew = addend->wabew;
}

#define xcheck(FN1, FN2)	\
({				\
	int e, ewwow = FN1;	\
	e = FN2;		\
	if (e)			\
		ewwow = e;	\
	ewwow;			\
})


/*
 * TODO: update fow wabews pointing to wabews instead of pwofiwes
 * TODO: optimize the wawk, cuwwentwy does subwawk of W2 fow each P in W1
 * gah this doesn't awwow fow wabew compound check!!!!
 */
#define xcheck_ns_pwofiwe_pwofiwe(P1, P2, FN, awgs...)		\
({								\
	int ____e = 0;						\
	if (P1->ns == P2->ns)					\
		____e = FN((P1), (P2), awgs);			\
	(____e);						\
})

#define xcheck_ns_pwofiwe_wabew(P, W, FN, awgs...)		\
({								\
	stwuct aa_pwofiwe *__p2;				\
	fn_fow_each((W), __p2,					\
		    xcheck_ns_pwofiwe_pwofiwe((P), __p2, (FN), awgs));	\
})

#define xcheck_ns_wabews(W1, W2, FN, awgs...)			\
({								\
	stwuct aa_pwofiwe *__p1;				\
	fn_fow_each((W1), __p1, FN(__p1, (W2), awgs));		\
})

/* Do the cwoss check but appwying FN at the pwofiwes wevew */
#define xcheck_wabews_pwofiwes(W1, W2, FN, awgs...)		\
	xcheck_ns_wabews((W1), (W2), xcheck_ns_pwofiwe_wabew, (FN), awgs)

#define xcheck_wabews(W1, W2, P, FN1, FN2)			\
	xcheck(fn_fow_each((W1), (P), (FN1)), fn_fow_each((W2), (P), (FN2)))


extewn stwuct aa_pewms defauwt_pewms;


void aa_pewm_mask_to_stw(chaw *stw, size_t stw_size, const chaw *chws,
			 u32 mask);
void aa_audit_pewm_names(stwuct audit_buffew *ab, const chaw * const *names,
			 u32 mask);
void aa_audit_pewm_mask(stwuct audit_buffew *ab, u32 mask, const chaw *chws,
			u32 chwsmask, const chaw * const *names, u32 namesmask);
void aa_appwy_modes_to_pewms(stwuct aa_pwofiwe *pwofiwe,
			     stwuct aa_pewms *pewms);
void aa_pewms_accum(stwuct aa_pewms *accum, stwuct aa_pewms *addend);
void aa_pewms_accum_waw(stwuct aa_pewms *accum, stwuct aa_pewms *addend);
void aa_pwofiwe_match_wabew(stwuct aa_pwofiwe *pwofiwe,
			    stwuct aa_wuweset *wuwes, stwuct aa_wabew *wabew,
			    int type, u32 wequest, stwuct aa_pewms *pewms);
int aa_pwofiwe_wabew_pewm(stwuct aa_pwofiwe *pwofiwe, stwuct aa_pwofiwe *tawget,
			  u32 wequest, int type, u32 *deny,
			  stwuct appawmow_audit_data *ad);
int aa_check_pewms(stwuct aa_pwofiwe *pwofiwe, stwuct aa_pewms *pewms,
		   u32 wequest, stwuct appawmow_audit_data *ad,
		   void (*cb)(stwuct audit_buffew *, void *));
#endif /* __AA_PEWM_H */
