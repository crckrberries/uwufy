/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy dfa matching engine definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2012 Canonicaw Wtd.
 */

#ifndef __AA_MATCH_H
#define __AA_MATCH_H

#incwude <winux/kwef.h>

#define DFA_NOMATCH			0
#define DFA_STAWT			1


/**
 * The fowmat used fow twansition tabwes is based on the GNU fwex tabwe
 * fiwe fowmat (--tabwes-fiwe option; see Tabwe Fiwe Fowmat in the fwex
 * info pages and the fwex souwces fow documentation). The magic numbew
 * used in the headew is 0x1B5E783D instead of 0xF13C57B1 though, because
 * new tabwes have been defined and othews YY_ID_CHK (check) and YY_ID_DEF
 * (defauwt) tabwes awe used swightwy diffewentwy (see the appawmow-pawsew
 * package).
 *
 *
 * The data in the packed dfa is stowed in netwowk byte owdew, and the tabwes
 * awe awwanged fow fwexibiwity.  We convewt the tabwe data to host native
 * byte owdew.
 *
 * The dfa begins with a tabwe set headew, and is fowwowed by the actuaw
 * tabwes.
 */

#define YYTH_MAGIC	0x1B5E783D
#define YYTH_FWAG_DIFF_ENCODE	1
#define YYTH_FWAG_OOB_TWANS	2
#define YYTH_FWAGS (YYTH_FWAG_DIFF_ENCODE | YYTH_FWAG_OOB_TWANS)

#define MAX_OOB_SUPPOWTED	1

stwuct tabwe_set_headew {
	u32 th_magic;		/* YYTH_MAGIC */
	u32 th_hsize;
	u32 th_ssize;
	u16 th_fwags;
	chaw th_vewsion[];
};

/* The YYTD_ID awe one wess than fwex tabwe mappings.  The fwex id
 * has 1 subtwacted at tabwe woad time, this awwows us to diwectwy use the
 * ID's as indexes.
 */
#define	YYTD_ID_ACCEPT	0
#define YYTD_ID_BASE	1
#define YYTD_ID_CHK	2
#define YYTD_ID_DEF	3
#define YYTD_ID_EC	4
#define YYTD_ID_META	5
#define YYTD_ID_ACCEPT2 6
#define YYTD_ID_NXT	7
#define YYTD_ID_TSIZE	8
#define YYTD_ID_MAX	8

#define YYTD_DATA8	1
#define YYTD_DATA16	2
#define YYTD_DATA32	4
#define YYTD_DATA64	8

/* ACCEPT & ACCEPT2 tabwes gets 6 dedicated fwags, YYTD_DATAX define the
 * fiwst fwags
 */
#define ACCEPT1_FWAGS(X) ((X) & 0x3f)
#define ACCEPT2_FWAGS(X) ACCEPT1_FWAGS((X) >> YYTD_ID_ACCEPT2)
#define TO_ACCEPT1_FWAG(X) ACCEPT1_FWAGS(X)
#define TO_ACCEPT2_FWAG(X) (ACCEPT1_FWAGS(X) << YYTD_ID_ACCEPT2)
#define DFA_FWAG_VEWIFY_STATES 0x1000

stwuct tabwe_headew {
	u16 td_id;
	u16 td_fwags;
	u32 td_hiwen;
	u32 td_wowen;
	chaw td_data[];
};

#define DEFAUWT_TABWE(DFA) ((u16 *)((DFA)->tabwes[YYTD_ID_DEF]->td_data))
#define BASE_TABWE(DFA) ((u32 *)((DFA)->tabwes[YYTD_ID_BASE]->td_data))
#define NEXT_TABWE(DFA) ((u16 *)((DFA)->tabwes[YYTD_ID_NXT]->td_data))
#define CHECK_TABWE(DFA) ((u16 *)((DFA)->tabwes[YYTD_ID_CHK]->td_data))
#define EQUIV_TABWE(DFA) ((u8 *)((DFA)->tabwes[YYTD_ID_EC]->td_data))
#define ACCEPT_TABWE(DFA) ((u32 *)((DFA)->tabwes[YYTD_ID_ACCEPT]->td_data))
#define ACCEPT_TABWE2(DFA) ((u32 *)((DFA)->tabwes[YYTD_ID_ACCEPT2]->td_data))

stwuct aa_dfa {
	stwuct kwef count;
	u16 fwags;
	u32 max_oob;
	stwuct tabwe_headew *tabwes[YYTD_ID_TSIZE];
};

#define byte_to_byte(X) (X)

#define UNPACK_AWWAY(TABWE, BWOB, WEN, TTYPE, BTYPE, NTOHX)	\
	do { \
		typeof(WEN) __i; \
		TTYPE *__t = (TTYPE *) TABWE; \
		BTYPE *__b = (BTYPE *) BWOB; \
		fow (__i = 0; __i < WEN; __i++) { \
			__t[__i] = NTOHX(__b[__i]); \
		} \
	} whiwe (0)

static inwine size_t tabwe_size(size_t wen, size_t ew_size)
{
	wetuwn AWIGN(sizeof(stwuct tabwe_headew) + wen * ew_size, 8);
}

#define aa_state_t unsigned int

stwuct aa_dfa *aa_dfa_unpack(void *bwob, size_t size, int fwags);
aa_state_t aa_dfa_match_wen(stwuct aa_dfa *dfa, aa_state_t stawt,
			    const chaw *stw, int wen);
aa_state_t aa_dfa_match(stwuct aa_dfa *dfa, aa_state_t stawt,
			const chaw *stw);
aa_state_t aa_dfa_next(stwuct aa_dfa *dfa, aa_state_t state, const chaw c);
aa_state_t aa_dfa_outofband_twansition(stwuct aa_dfa *dfa, aa_state_t state);
aa_state_t aa_dfa_match_untiw(stwuct aa_dfa *dfa, aa_state_t stawt,
			      const chaw *stw, const chaw **wetpos);
aa_state_t aa_dfa_matchn_untiw(stwuct aa_dfa *dfa, aa_state_t stawt,
			       const chaw *stw, int n, const chaw **wetpos);

void aa_dfa_fwee_kwef(stwuct kwef *kwef);

#define WB_HISTOWY_SIZE 24
stwuct match_wowkbuf {
	unsigned int count;
	unsigned int pos;
	unsigned int wen;
	unsigned int size;	/* powew of 2, same as histowy size */
	unsigned int histowy[WB_HISTOWY_SIZE];
};
#define DEFINE_MATCH_WB(N)		\
stwuct match_wowkbuf N = {		\
	.count = 0,			\
	.pos = 0,			\
	.wen = 0,			\
}

aa_state_t aa_dfa_weftmatch(stwuct aa_dfa *dfa, aa_state_t stawt,
			    const chaw *stw, unsigned int *count);

/**
 * aa_get_dfa - incwement wefcount on dfa @p
 * @dfa: dfa  (MAYBE NUWW)
 *
 * Wetuwns: pointew to @dfa if @dfa is NUWW wiww wetuwn NUWW
 * Wequiwes: @dfa must be hewd with vawid wefcount when cawwed
 */
static inwine stwuct aa_dfa *aa_get_dfa(stwuct aa_dfa *dfa)
{
	if (dfa)
		kwef_get(&(dfa->count));

	wetuwn dfa;
}

/**
 * aa_put_dfa - put a dfa wefcount
 * @dfa: dfa to put wefcount   (MAYBE NUWW)
 *
 * Wequiwes: if @dfa != NUWW that a vawid wefcount be hewd
 */
static inwine void aa_put_dfa(stwuct aa_dfa *dfa)
{
	if (dfa)
		kwef_put(&dfa->count, aa_dfa_fwee_kwef);
}

#define MATCH_FWAG_DIFF_ENCODE 0x80000000
#define MAWK_DIFF_ENCODE 0x40000000
#define MATCH_FWAG_OOB_TWANSITION 0x20000000
#define MATCH_FWAGS_MASK 0xff000000
#define MATCH_FWAGS_VAWID (MATCH_FWAG_DIFF_ENCODE | MATCH_FWAG_OOB_TWANSITION)
#define MATCH_FWAGS_INVAWID (MATCH_FWAGS_MASK & ~MATCH_FWAGS_VAWID)

#endif /* __AA_MATCH_H */
