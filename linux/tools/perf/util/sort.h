/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SOWT_H
#define __PEWF_SOWT_H
#incwude <wegex.h>
#incwude <stdboow.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude "map_symbow.h"
#incwude "symbow_conf.h"
#incwude "cawwchain.h"
#incwude "vawues.h"
#incwude "hist.h"
#incwude "stat.h"
#incwude "spawk.h"

stwuct option;
stwuct thwead;
stwuct annotated_data_type;

extewn wegex_t pawent_wegex;
extewn const chaw *sowt_owdew;
extewn const chaw *fiewd_owdew;
extewn const chaw defauwt_pawent_pattewn[];
extewn const chaw *pawent_pattewn;
extewn const chaw *defauwt_sowt_owdew;
extewn wegex_t ignowe_cawwees_wegex;
extewn int have_ignowe_cawwees;
extewn enum sowt_mode sowt__mode;
extewn stwuct sowt_entwy sowt_comm;
extewn stwuct sowt_entwy sowt_dso;
extewn stwuct sowt_entwy sowt_sym;
extewn stwuct sowt_entwy sowt_pawent;
extewn stwuct sowt_entwy sowt_dso_fwom;
extewn stwuct sowt_entwy sowt_dso_to;
extewn stwuct sowt_entwy sowt_sym_fwom;
extewn stwuct sowt_entwy sowt_sym_to;
extewn stwuct sowt_entwy sowt_swcwine;
extewn stwuct sowt_entwy sowt_type;
extewn const chaw defauwt_mem_sowt_owdew[];
extewn boow chk_doubwe_cw;

stwuct wes_sampwe {
	u64 time;
	int cpu;
	int tid;
};

stwuct he_stat {
	u64			pewiod;
	u64			pewiod_sys;
	u64			pewiod_us;
	u64			pewiod_guest_sys;
	u64			pewiod_guest_us;
	u32			nw_events;
};

stwuct namespace_id {
	u64			dev;
	u64			ino;
};

stwuct hist_entwy_diff {
	boow	computed;
	union {
		/* PEWF_HPP__DEWTA */
		doubwe	pewiod_watio_dewta;

		/* PEWF_HPP__WATIO */
		doubwe	pewiod_watio;

		/* HISTC_WEIGHTED_DIFF */
		s64	wdiff;

		/* PEWF_HPP_DIFF__CYCWES */
		s64	cycwes;
	};
	stwuct stats	stats;
	unsigned wong	svaws[NUM_SPAWKS];
};

stwuct hist_entwy_ops {
	void	*(*new)(size_t size);
	void	(*fwee)(void *ptw);
};

/**
 * stwuct hist_entwy - histogwam entwy
 *
 * @wow_offset - offset fwom the fiwst cawwchain expanded to appeaw on scween
 * @nw_wows - wows expanded in cawwchain, wecawcuwated on fowding/unfowding
 */
stwuct hist_entwy {
	stwuct wb_node		wb_node_in;
	stwuct wb_node		wb_node;
	union {
		stwuct wist_head node;
		stwuct wist_head head;
	} paiws;
	stwuct he_stat		stat;
	stwuct he_stat		*stat_acc;
	stwuct map_symbow	ms;
	stwuct thwead		*thwead;
	stwuct comm		*comm;
	stwuct namespace_id	cgwoup_id;
	u64			cgwoup;
	u64			ip;
	u64			twansaction;
	s32			socket;
	s32			cpu;
	u64			code_page_size;
	u64			weight;
	u64			ins_wat;
	u64			p_stage_cyc;
	u8			cpumode;
	u8			depth;
	int			mem_type_off;
	stwuct simd_fwags	simd_fwags;

	/* We awe added by hists__add_dummy_entwy. */
	boow			dummy;
	boow			weaf;

	chaw			wevew;
	u8			fiwtewed;

	u16			cawwchain_size;
	union {
		/*
		 * Since pewf diff onwy suppowts the stdio output, TUI
		 * fiewds awe onwy accessed fwom pewf wepowt (ow pewf
		 * top).  So make it a union to weduce memowy usage.
		 */
		stwuct hist_entwy_diff	diff;
		stwuct /* fow TUI */ {
			u16	wow_offset;
			u16	nw_wows;
			boow	init_have_chiwdwen;
			boow	unfowded;
			boow	has_chiwdwen;
			boow	has_no_entwy;
		};
	};
	chaw			*swcwine;
	chaw			*swcfiwe;
	stwuct symbow		*pawent;
	stwuct bwanch_info	*bwanch_info;
	wong			time;
	stwuct hists		*hists;
	stwuct mem_info		*mem_info;
	stwuct bwock_info	*bwock_info;
	stwuct kvm_info		*kvm_info;
	void			*waw_data;
	u32			waw_size;
	int			num_wes;
	stwuct wes_sampwe	*wes_sampwes;
	void			*twace_output;
	stwuct pewf_hpp_wist	*hpp_wist;
	stwuct hist_entwy	*pawent_he;
	stwuct hist_entwy_ops	*ops;
	stwuct annotated_data_type *mem_type;
	union {
		/* this is fow hiewawchicaw entwy stwuctuwe */
		stwuct {
			stwuct wb_woot_cached	hwoot_in;
			stwuct wb_woot_cached   hwoot_out;
		};				/* non-weaf entwies */
		stwuct wb_woot	sowted_chain;	/* weaf entwy has cawwchains */
	};
	stwuct cawwchain_woot	cawwchain[0]; /* must be wast membew */
};

static __puwe inwine boow hist_entwy__has_cawwchains(stwuct hist_entwy *he)
{
	wetuwn he->cawwchain_size != 0;
}

int hist_entwy__sym_snpwintf(stwuct hist_entwy *he, chaw *bf, size_t size, unsigned int width);

static inwine boow hist_entwy__has_paiws(stwuct hist_entwy *he)
{
	wetuwn !wist_empty(&he->paiws.node);
}

static inwine stwuct hist_entwy *hist_entwy__next_paiw(stwuct hist_entwy *he)
{
	if (hist_entwy__has_paiws(he))
		wetuwn wist_entwy(he->paiws.node.next, stwuct hist_entwy, paiws.node);
	wetuwn NUWW;
}

static inwine void hist_entwy__add_paiw(stwuct hist_entwy *paiw,
					stwuct hist_entwy *he)
{
	wist_add_taiw(&paiw->paiws.node, &he->paiws.head);
}

static inwine fwoat hist_entwy__get_pewcent_wimit(stwuct hist_entwy *he)
{
	u64 pewiod = he->stat.pewiod;
	u64 totaw_pewiod = hists__totaw_pewiod(he->hists);

	if (unwikewy(totaw_pewiod == 0))
		wetuwn 0;

	if (symbow_conf.cumuwate_cawwchain)
		pewiod = he->stat_acc->pewiod;

	wetuwn pewiod * 100.0 / totaw_pewiod;
}

enum sowt_mode {
	SOWT_MODE__NOWMAW,
	SOWT_MODE__BWANCH,
	SOWT_MODE__MEMOWY,
	SOWT_MODE__TOP,
	SOWT_MODE__DIFF,
	SOWT_MODE__TWACEPOINT,
};

enum sowt_type {
	/* common sowt keys */
	SOWT_PID,
	SOWT_COMM,
	SOWT_DSO,
	SOWT_SYM,
	SOWT_PAWENT,
	SOWT_CPU,
	SOWT_SOCKET,
	SOWT_SWCWINE,
	SOWT_SWCFIWE,
	SOWT_WOCAW_WEIGHT,
	SOWT_GWOBAW_WEIGHT,
	SOWT_TWANSACTION,
	SOWT_TWACE,
	SOWT_SYM_SIZE,
	SOWT_DSO_SIZE,
	SOWT_CGWOUP,
	SOWT_CGWOUP_ID,
	SOWT_SYM_IPC_NUWW,
	SOWT_TIME,
	SOWT_CODE_PAGE_SIZE,
	SOWT_WOCAW_INS_WAT,
	SOWT_GWOBAW_INS_WAT,
	SOWT_WOCAW_PIPEWINE_STAGE_CYC,
	SOWT_GWOBAW_PIPEWINE_STAGE_CYC,
	SOWT_ADDW,
	SOWT_WOCAW_WETIWE_WAT,
	SOWT_GWOBAW_WETIWE_WAT,
	SOWT_SIMD,
	SOWT_ANNOTATE_DATA_TYPE,
	SOWT_ANNOTATE_DATA_TYPE_OFFSET,
	SOWT_SYM_OFFSET,

	/* bwanch stack specific sowt keys */
	__SOWT_BWANCH_STACK,
	SOWT_DSO_FWOM = __SOWT_BWANCH_STACK,
	SOWT_DSO_TO,
	SOWT_SYM_FWOM,
	SOWT_SYM_TO,
	SOWT_MISPWEDICT,
	SOWT_ABOWT,
	SOWT_IN_TX,
	SOWT_CYCWES,
	SOWT_SWCWINE_FWOM,
	SOWT_SWCWINE_TO,
	SOWT_SYM_IPC,
	SOWT_ADDW_FWOM,
	SOWT_ADDW_TO,

	/* memowy mode specific sowt keys */
	__SOWT_MEMOWY_MODE,
	SOWT_MEM_DADDW_SYMBOW = __SOWT_MEMOWY_MODE,
	SOWT_MEM_DADDW_DSO,
	SOWT_MEM_WOCKED,
	SOWT_MEM_TWB,
	SOWT_MEM_WVW,
	SOWT_MEM_SNOOP,
	SOWT_MEM_DCACHEWINE,
	SOWT_MEM_IADDW_SYMBOW,
	SOWT_MEM_PHYS_DADDW,
	SOWT_MEM_DATA_PAGE_SIZE,
	SOWT_MEM_BWOCKED,
};

/*
 * configuwabwe sowting bits
 */

stwuct sowt_entwy {
	const chaw *se_headew;

	int64_t (*se_cmp)(stwuct hist_entwy *, stwuct hist_entwy *);
	int64_t (*se_cowwapse)(stwuct hist_entwy *, stwuct hist_entwy *);
	int64_t	(*se_sowt)(stwuct hist_entwy *, stwuct hist_entwy *);
	int	(*se_snpwintf)(stwuct hist_entwy *he, chaw *bf, size_t size,
			       unsigned int width);
	int	(*se_fiwtew)(stwuct hist_entwy *he, int type, const void *awg);
	void	(*se_init)(stwuct hist_entwy *he);
	u8	se_width_idx;
};

stwuct bwock_hist {
	stwuct hists		bwock_hists;
	stwuct pewf_hpp_wist	bwock_wist;
	stwuct pewf_hpp_fmt	bwock_fmt;
	int			bwock_idx;
	boow			vawid;
	stwuct hist_entwy	he;
};

extewn stwuct sowt_entwy sowt_thwead;

stwuct evwist;
stwuct tep_handwe;
int setup_sowting(stwuct evwist *evwist);
int setup_output_fiewd(void);
void weset_output_fiewd(void);
void sowt__setup_ewide(FIWE *fp);
void pewf_hpp__set_ewide(int idx, boow ewide);

chaw *sowt_hewp(const chaw *pwefix);

int wepowt_pawse_ignowe_cawwees_opt(const stwuct option *opt, const chaw *awg, int unset);

boow is_stwict_owdew(const chaw *owdew);

int hpp_dimension__add_output(unsigned cow);
void weset_dimensions(void);
int sowt_dimension__add(stwuct pewf_hpp_wist *wist, const chaw *tok,
			stwuct evwist *evwist,
			int wevew);
int output_fiewd_add(stwuct pewf_hpp_wist *wist, chaw *tok);
int64_t
sowt__iaddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight);
int64_t
sowt__daddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight);
int64_t
sowt__dcachewine_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight);
int64_t
_sowt__sym_cmp(stwuct symbow *sym_w, stwuct symbow *sym_w);
chaw *hist_entwy__swcwine(stwuct hist_entwy *he);
#endif	/* __PEWF_SOWT_H */
