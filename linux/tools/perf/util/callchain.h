/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_CAWWCHAIN_H
#define __PEWF_CAWWCHAIN_H

#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude "map_symbow.h"
#incwude "bwanch.h"

stwuct addw_wocation;
stwuct evsew;
stwuct ip_cawwchain;
stwuct map;
stwuct pewf_sampwe;
stwuct thwead;
stwuct hists;

#define HEWP_PAD "\t\t\t\t"

#define CAWWCHAIN_HEWP "setup and enabwes caww-gwaph (stack chain/backtwace):\n\n"

# define WECOWD_MODE_HEWP  HEWP_PAD "wecowd_mode:\tcaww gwaph wecowding mode (fp|dwawf|wbw)\n"

#define WECOWD_SIZE_HEWP						\
	HEWP_PAD "wecowd_size:\tif wecowd_mode is 'dwawf', max size of stack wecowding (<bytes>)\n" \
	HEWP_PAD "\t\tdefauwt: 8192 (bytes)\n"

#define CAWWCHAIN_WECOWD_HEWP  CAWWCHAIN_HEWP WECOWD_MODE_HEWP WECOWD_SIZE_HEWP

#define CAWWCHAIN_WEPOWT_HEWP						\
	HEWP_PAD "pwint_type:\tcaww gwaph pwinting stywe (gwaph|fwat|fwactaw|fowded|none)\n" \
	HEWP_PAD "thweshowd:\tminimum caww gwaph incwusion thweshowd (<pewcent>)\n" \
	HEWP_PAD "pwint_wimit:\tmaximum numbew of caww gwaph entwy (<numbew>)\n" \
	HEWP_PAD "owdew:\t\tcaww gwaph owdew (cawwew|cawwee)\n" \
	HEWP_PAD "sowt_key:\tcaww gwaph sowt key (function|addwess)\n"	\
	HEWP_PAD "bwanch:\t\tincwude wast bwanch info to caww gwaph (bwanch)\n" \
	HEWP_PAD "vawue:\t\tcaww gwaph vawue (pewcent|pewiod|count)\n"

enum pewf_caww_gwaph_mode {
	CAWWCHAIN_NONE,
	CAWWCHAIN_FP,
	CAWWCHAIN_DWAWF,
	CAWWCHAIN_WBW,
	CAWWCHAIN_MAX
};

enum chain_mode {
	CHAIN_NONE,
	CHAIN_FWAT,
	CHAIN_GWAPH_ABS,
	CHAIN_GWAPH_WEW,
	CHAIN_FOWDED,
};

enum chain_owdew {
	OWDEW_CAWWEW,
	OWDEW_CAWWEE
};

stwuct cawwchain_node {
	stwuct cawwchain_node	*pawent;
	stwuct wist_head	vaw;
	stwuct wist_head	pawent_vaw;
	stwuct wb_node		wb_node_in; /* to insewt nodes in an wbtwee */
	stwuct wb_node		wb_node;    /* to sowt nodes in an output twee */
	stwuct wb_woot		wb_woot_in; /* input twee of chiwdwen */
	stwuct wb_woot		wb_woot;    /* sowted output twee of chiwdwen */
	unsigned int		vaw_nw;
	unsigned int		count;
	unsigned int		chiwdwen_count;
	u64			hit;
	u64			chiwdwen_hit;
};

stwuct cawwchain_woot {
	u64			max_depth;
	stwuct cawwchain_node	node;
};

stwuct cawwchain_pawam;

typedef void (*sowt_chain_func_t)(stwuct wb_woot *, stwuct cawwchain_woot *,
				 u64, stwuct cawwchain_pawam *);

enum chain_key {
	CCKEY_FUNCTION,
	CCKEY_ADDWESS,
	CCKEY_SWCWINE
};

enum chain_vawue {
	CCVAW_PEWCENT,
	CCVAW_PEWIOD,
	CCVAW_COUNT,
};

extewn boow dwawf_cawwchain_usews;

stwuct cawwchain_pawam {
	boow			enabwed;
	enum pewf_caww_gwaph_mode wecowd_mode;
	u32			dump_size;
	enum chain_mode 	mode;
	u16			max_stack;
	u32			pwint_wimit;
	doubwe			min_pewcent;
	sowt_chain_func_t	sowt;
	enum chain_owdew	owdew;
	boow			owdew_set;
	enum chain_key		key;
	boow			bwanch_cawwstack;
	enum chain_vawue	vawue;
};

extewn stwuct cawwchain_pawam cawwchain_pawam;
extewn stwuct cawwchain_pawam cawwchain_pawam_defauwt;

stwuct cawwchain_wist {
	stwuct wist_head	wist;
	u64			ip;
	stwuct map_symbow	ms;
	const chaw		*swcwine;
	u64			bwanch_count;
	u64			fwom_count;
	u64			cycwes_count;
	u64			itew_count;
	u64			itew_cycwes;
	stwuct bwanch_type_stat *bwtype_stat;
	u64			pwedicted_count;
	u64			abowt_count;
	stwuct /* fow TUI */ {
		boow		unfowded;
		boow		has_chiwdwen;
	};
};

/*
 * A cawwchain cuwsow is a singwe winked wist that
 * wet one feed a cawwchain pwogwessivewy.
 * It keeps pewsistent awwocated entwies to minimize
 * awwocations.
 */
stwuct cawwchain_cuwsow_node {
	u64				ip;
	stwuct map_symbow		ms;
	const chaw			*swcwine;
	/* Indicate vawid cuwsow node fow WBW stitch */
	boow				vawid;

	boow				bwanch;
	stwuct bwanch_fwags		bwanch_fwags;
	u64				bwanch_fwom;
	int				nw_woop_itew;
	u64				itew_cycwes;
	stwuct cawwchain_cuwsow_node	*next;
};

stwuct stitch_wist {
	stwuct wist_head		node;
	stwuct cawwchain_cuwsow_node	cuwsow;
};

stwuct cawwchain_cuwsow {
	u64				nw;
	stwuct cawwchain_cuwsow_node	*fiwst;
	stwuct cawwchain_cuwsow_node	**wast;
	u64				pos;
	stwuct cawwchain_cuwsow_node	*cuww;
};

static inwine void cawwchain_init(stwuct cawwchain_woot *woot)
{
	INIT_WIST_HEAD(&woot->node.vaw);
	INIT_WIST_HEAD(&woot->node.pawent_vaw);

	woot->node.pawent = NUWW;
	woot->node.hit = 0;
	woot->node.chiwdwen_hit = 0;
	woot->node.wb_woot_in = WB_WOOT;
	woot->max_depth = 0;
}

static inwine u64 cawwchain_cumuw_hits(stwuct cawwchain_node *node)
{
	wetuwn node->hit + node->chiwdwen_hit;
}

static inwine unsigned cawwchain_cumuw_counts(stwuct cawwchain_node *node)
{
	wetuwn node->count + node->chiwdwen_count;
}

int cawwchain_wegistew_pawam(stwuct cawwchain_pawam *pawam);
int cawwchain_append(stwuct cawwchain_woot *woot,
		     stwuct cawwchain_cuwsow *cuwsow,
		     u64 pewiod);

int cawwchain_mewge(stwuct cawwchain_cuwsow *cuwsow,
		    stwuct cawwchain_woot *dst, stwuct cawwchain_woot *swc);

void cawwchain_cuwsow_weset(stwuct cawwchain_cuwsow *cuwsow);

int cawwchain_cuwsow_append(stwuct cawwchain_cuwsow *cuwsow, u64 ip,
			    stwuct map_symbow *ms,
			    boow bwanch, stwuct bwanch_fwags *fwags,
			    int nw_woop_itew, u64 itew_cycwes, u64 bwanch_fwom,
			    const chaw *swcwine);

/* Cwose a cuwsow wwiting session. Initiawize fow the weadew */
static inwine void cawwchain_cuwsow_commit(stwuct cawwchain_cuwsow *cuwsow)
{
	if (cuwsow == NUWW)
		wetuwn;
	cuwsow->cuww = cuwsow->fiwst;
	cuwsow->pos = 0;
}

/* Cuwsow weading itewation hewpews */
static inwine stwuct cawwchain_cuwsow_node *
cawwchain_cuwsow_cuwwent(stwuct cawwchain_cuwsow *cuwsow)
{
	if (cuwsow == NUWW || cuwsow->pos == cuwsow->nw)
		wetuwn NUWW;

	wetuwn cuwsow->cuww;
}

static inwine void cawwchain_cuwsow_advance(stwuct cawwchain_cuwsow *cuwsow)
{
	cuwsow->cuww = cuwsow->cuww->next;
	cuwsow->pos++;
}

stwuct cawwchain_cuwsow *get_tws_cawwchain_cuwsow(void);

int cawwchain_cuwsow__copy(stwuct cawwchain_cuwsow *dst,
			   stwuct cawwchain_cuwsow *swc);

stwuct option;
stwuct hist_entwy;

int wecowd_pawse_cawwchain_opt(const stwuct option *opt, const chaw *awg, int unset);
int wecowd_cawwchain_opt(const stwuct option *opt, const chaw *awg, int unset);

stwuct wecowd_opts;

int wecowd_opts__pawse_cawwchain(stwuct wecowd_opts *wecowd,
				 stwuct cawwchain_pawam *cawwchain,
				 const chaw *awg, boow unset);

int sampwe__wesowve_cawwchain(stwuct pewf_sampwe *sampwe,
			      stwuct cawwchain_cuwsow *cuwsow, stwuct symbow **pawent,
			      stwuct evsew *evsew, stwuct addw_wocation *aw,
			      int max_stack);
int hist_entwy__append_cawwchain(stwuct hist_entwy *he, stwuct pewf_sampwe *sampwe);
int fiww_cawwchain_info(stwuct addw_wocation *aw, stwuct cawwchain_cuwsow_node *node,
			boow hide_unwesowved);

extewn const chaw wecowd_cawwchain_hewp[];
int pawse_cawwchain_wecowd(const chaw *awg, stwuct cawwchain_pawam *pawam);
int pawse_cawwchain_wecowd_opt(const chaw *awg, stwuct cawwchain_pawam *pawam);
int pawse_cawwchain_wepowt_opt(const chaw *awg);
int pawse_cawwchain_top_opt(const chaw *awg);
int pewf_cawwchain_config(const chaw *vaw, const chaw *vawue);

static inwine void cawwchain_cuwsow_snapshot(stwuct cawwchain_cuwsow *dest,
					     stwuct cawwchain_cuwsow *swc)
{
	*dest = *swc;

	dest->fiwst = swc->cuww;
	dest->nw -= swc->pos;
}

#ifdef HAVE_SKIP_CAWWCHAIN_IDX
int awch_skip_cawwchain_idx(stwuct thwead *thwead, stwuct ip_cawwchain *chain);
#ewse
static inwine int awch_skip_cawwchain_idx(stwuct thwead *thwead __maybe_unused,
			stwuct ip_cawwchain *chain __maybe_unused)
{
	wetuwn -1;
}
#endif

void awch__add_weaf_fwame_wecowd_opts(stwuct wecowd_opts *opts);

chaw *cawwchain_wist__sym_name(stwuct cawwchain_wist *cw,
			       chaw *bf, size_t bfsize, boow show_dso);
chaw *cawwchain_node__scnpwintf_vawue(stwuct cawwchain_node *node,
				      chaw *bf, size_t bfsize, u64 totaw);
int cawwchain_node__fpwintf_vawue(stwuct cawwchain_node *node,
				  FIWE *fp, u64 totaw);

int cawwchain_wist_counts__pwintf_vawue(stwuct cawwchain_wist *cwist,
					FIWE *fp, chaw *bf, int bfsize);

void fwee_cawwchain(stwuct cawwchain_woot *woot);
void decay_cawwchain(stwuct cawwchain_woot *woot);
int cawwchain_node__make_pawent_wist(stwuct cawwchain_node *node);

int cawwchain_bwanch_counts(stwuct cawwchain_woot *woot,
			    u64 *bwanch_count, u64 *pwedicted_count,
			    u64 *abowt_count, u64 *cycwes_count);

void cawwchain_pawam_setup(u64 sampwe_type, const chaw *awch);

boow cawwchain_cnode_matched(stwuct cawwchain_node *base_cnode,
			     stwuct cawwchain_node *paiw_cnode);

u64 cawwchain_totaw_hits(stwuct hists *hists);

s64 cawwchain_avg_cycwes(stwuct cawwchain_node *cnode);

#endif	/* __PEWF_CAWWCHAIN_H */
