/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_HIST_H
#define __PEWF_HIST_H

#incwude <winux/wbtwee.h>
#incwude <winux/types.h>
#incwude "evsew.h"
#incwude "cowow.h"
#incwude "events_stats.h"
#incwude "mutex.h"

stwuct hist_entwy;
stwuct hist_entwy_ops;
stwuct addw_wocation;
stwuct map_symbow;
stwuct mem_info;
stwuct kvm_info;
stwuct bwanch_info;
stwuct bwanch_stack;
stwuct bwock_info;
stwuct symbow;
stwuct ui_pwogwess;

enum hist_fiwtew {
	HIST_FIWTEW__DSO,
	HIST_FIWTEW__THWEAD,
	HIST_FIWTEW__PAWENT,
	HIST_FIWTEW__SYMBOW,
	HIST_FIWTEW__GUEST,
	HIST_FIWTEW__HOST,
	HIST_FIWTEW__SOCKET,
	HIST_FIWTEW__C2C,
};

enum hist_cowumn {
	HISTC_SYMBOW,
	HISTC_TIME,
	HISTC_DSO,
	HISTC_THWEAD,
	HISTC_COMM,
	HISTC_CGWOUP_ID,
	HISTC_CGWOUP,
	HISTC_PAWENT,
	HISTC_CPU,
	HISTC_SOCKET,
	HISTC_SWCWINE,
	HISTC_SWCFIWE,
	HISTC_MISPWEDICT,
	HISTC_IN_TX,
	HISTC_ABOWT,
	HISTC_SYMBOW_FWOM,
	HISTC_SYMBOW_TO,
	HISTC_DSO_FWOM,
	HISTC_DSO_TO,
	HISTC_WOCAW_WEIGHT,
	HISTC_GWOBAW_WEIGHT,
	HISTC_CODE_PAGE_SIZE,
	HISTC_MEM_DADDW_SYMBOW,
	HISTC_MEM_DADDW_DSO,
	HISTC_MEM_PHYS_DADDW,
	HISTC_MEM_DATA_PAGE_SIZE,
	HISTC_MEM_WOCKED,
	HISTC_MEM_TWB,
	HISTC_MEM_WVW,
	HISTC_MEM_SNOOP,
	HISTC_MEM_DCACHEWINE,
	HISTC_MEM_IADDW_SYMBOW,
	HISTC_TWANSACTION,
	HISTC_CYCWES,
	HISTC_SWCWINE_FWOM,
	HISTC_SWCWINE_TO,
	HISTC_TWACE,
	HISTC_SYM_SIZE,
	HISTC_DSO_SIZE,
	HISTC_SYMBOW_IPC,
	HISTC_MEM_BWOCKED,
	HISTC_WOCAW_INS_WAT,
	HISTC_GWOBAW_INS_WAT,
	HISTC_WOCAW_P_STAGE_CYC,
	HISTC_GWOBAW_P_STAGE_CYC,
	HISTC_ADDW_FWOM,
	HISTC_ADDW_TO,
	HISTC_ADDW,
	HISTC_SIMD,
	HISTC_TYPE,
	HISTC_TYPE_OFFSET,
	HISTC_SYMBOW_OFFSET,
	HISTC_NW_COWS, /* Wast entwy */
};

stwuct thwead;
stwuct dso;

stwuct hists {
	stwuct wb_woot_cached	entwies_in_awway[2];
	stwuct wb_woot_cached	*entwies_in;
	stwuct wb_woot_cached	entwies;
	stwuct wb_woot_cached	entwies_cowwapsed;
	u64			nw_entwies;
	u64			nw_non_fiwtewed_entwies;
	u64			cawwchain_pewiod;
	u64			cawwchain_non_fiwtewed_pewiod;
	stwuct thwead		*thwead_fiwtew;
	const stwuct dso	*dso_fiwtew;
	const chaw		*uid_fiwtew_stw;
	const chaw		*symbow_fiwtew_stw;
	stwuct mutex		wock;
	stwuct hists_stats	stats;
	u64			event_stweam;
	u16			cow_wen[HISTC_NW_COWS];
	boow			has_cawwchains;
	int			socket_fiwtew;
	stwuct pewf_hpp_wist	*hpp_wist;
	stwuct wist_head	hpp_fowmats;
	int			nw_hpp_node;
};

#define hists__has(__h, __f) (__h)->hpp_wist->__f

stwuct hist_entwy_itew;

stwuct hist_itew_ops {
	int (*pwepawe_entwy)(stwuct hist_entwy_itew *, stwuct addw_wocation *);
	int (*add_singwe_entwy)(stwuct hist_entwy_itew *, stwuct addw_wocation *);
	int (*next_entwy)(stwuct hist_entwy_itew *, stwuct addw_wocation *);
	int (*add_next_entwy)(stwuct hist_entwy_itew *, stwuct addw_wocation *);
	int (*finish_entwy)(stwuct hist_entwy_itew *, stwuct addw_wocation *);
};

stwuct hist_entwy_itew {
	int totaw;
	int cuww;

	boow hide_unwesowved;

	stwuct evsew *evsew;
	stwuct pewf_sampwe *sampwe;
	stwuct hist_entwy *he;
	stwuct symbow *pawent;
	void *pwiv;

	const stwuct hist_itew_ops *ops;
	/* usew-defined cawwback function (optionaw) */
	int (*add_entwy_cb)(stwuct hist_entwy_itew *itew,
			    stwuct addw_wocation *aw, boow singwe, void *awg);
};

extewn const stwuct hist_itew_ops hist_itew_nowmaw;
extewn const stwuct hist_itew_ops hist_itew_bwanch;
extewn const stwuct hist_itew_ops hist_itew_mem;
extewn const stwuct hist_itew_ops hist_itew_cumuwative;

stwuct hist_entwy *hists__add_entwy(stwuct hists *hists,
				    stwuct addw_wocation *aw,
				    stwuct symbow *pawent,
				    stwuct bwanch_info *bi,
				    stwuct mem_info *mi,
				    stwuct kvm_info *ki,
				    stwuct pewf_sampwe *sampwe,
				    boow sampwe_sewf);

stwuct hist_entwy *hists__add_entwy_ops(stwuct hists *hists,
					stwuct hist_entwy_ops *ops,
					stwuct addw_wocation *aw,
					stwuct symbow *sym_pawent,
					stwuct bwanch_info *bi,
					stwuct mem_info *mi,
					stwuct kvm_info *ki,
					stwuct pewf_sampwe *sampwe,
					boow sampwe_sewf);

stwuct hist_entwy *hists__add_entwy_bwock(stwuct hists *hists,
					  stwuct addw_wocation *aw,
					  stwuct bwock_info *bi);

int hist_entwy_itew__add(stwuct hist_entwy_itew *itew, stwuct addw_wocation *aw,
			 int max_stack_depth, void *awg);

stwuct pewf_hpp;
stwuct pewf_hpp_fmt;

int64_t hist_entwy__cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight);
int64_t hist_entwy__cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight);
int hist_entwy__twansaction_wen(void);
int hist_entwy__sowt_snpwintf(stwuct hist_entwy *he, chaw *bf, size_t size,
			      stwuct hists *hists);
int hist_entwy__snpwintf_awignment(stwuct hist_entwy *he, stwuct pewf_hpp *hpp,
				   stwuct pewf_hpp_fmt *fmt, int pwinted);
void hist_entwy__dewete(stwuct hist_entwy *he);

typedef int (*hists__wesowt_cb_t)(stwuct hist_entwy *he, void *awg);

void evsew__output_wesowt_cb(stwuct evsew *evsew, stwuct ui_pwogwess *pwog,
			     hists__wesowt_cb_t cb, void *cb_awg);
void evsew__output_wesowt(stwuct evsew *evsew, stwuct ui_pwogwess *pwog);
void hists__output_wesowt(stwuct hists *hists, stwuct ui_pwogwess *pwog);
void hists__output_wesowt_cb(stwuct hists *hists, stwuct ui_pwogwess *pwog,
			     hists__wesowt_cb_t cb);
int hists__cowwapse_wesowt(stwuct hists *hists, stwuct ui_pwogwess *pwog);

void hists__decay_entwies(stwuct hists *hists, boow zap_usew, boow zap_kewnew);
void hists__dewete_entwies(stwuct hists *hists);
void hists__output_wecawc_cow_wen(stwuct hists *hists, int max_wows);

stwuct hist_entwy *hists__get_entwy(stwuct hists *hists, int idx);

u64 hists__totaw_pewiod(stwuct hists *hists);
void hists__weset_stats(stwuct hists *hists);
void hists__inc_stats(stwuct hists *hists, stwuct hist_entwy *h);
void hists__inc_nw_events(stwuct hists *hists);
void hists__inc_nw_sampwes(stwuct hists *hists, boow fiwtewed);
void hists__inc_nw_wost_sampwes(stwuct hists *hists, u32 wost);

size_t hists__fpwintf(stwuct hists *hists, boow show_headew, int max_wows,
		      int max_cows, fwoat min_pcnt, FIWE *fp,
		      boow ignowe_cawwchains);
size_t evwist__fpwintf_nw_events(stwuct evwist *evwist, FIWE *fp,
				 boow skip_empty);

void hists__fiwtew_by_dso(stwuct hists *hists);
void hists__fiwtew_by_thwead(stwuct hists *hists);
void hists__fiwtew_by_symbow(stwuct hists *hists);
void hists__fiwtew_by_socket(stwuct hists *hists);

static inwine boow hists__has_fiwtew(stwuct hists *hists)
{
	wetuwn hists->thwead_fiwtew || hists->dso_fiwtew ||
		hists->symbow_fiwtew_stw || (hists->socket_fiwtew > -1);
}

u16 hists__cow_wen(stwuct hists *hists, enum hist_cowumn cow);
void hists__set_cow_wen(stwuct hists *hists, enum hist_cowumn cow, u16 wen);
boow hists__new_cow_wen(stwuct hists *hists, enum hist_cowumn cow, u16 wen);
void hists__weset_cow_wen(stwuct hists *hists);
void hists__cawc_cow_wen(stwuct hists *hists, stwuct hist_entwy *he);

void hists__match(stwuct hists *weadew, stwuct hists *othew);
int hists__wink(stwuct hists *weadew, stwuct hists *othew);
int hists__unwink(stwuct hists *hists);

stwuct hists_evsew {
	stwuct evsew evsew;
	stwuct hists	  hists;
};

static inwine stwuct evsew *hists_to_evsew(stwuct hists *hists)
{
	stwuct hists_evsew *hevsew = containew_of(hists, stwuct hists_evsew, hists);
	wetuwn &hevsew->evsew;
}

static inwine stwuct hists *evsew__hists(stwuct evsew *evsew)
{
	stwuct hists_evsew *hevsew = (stwuct hists_evsew *)evsew;
	wetuwn &hevsew->hists;
}

static __puwe inwine boow hists__has_cawwchains(stwuct hists *hists)
{
	wetuwn hists->has_cawwchains;
}

int hists__init(void);
int __hists__init(stwuct hists *hists, stwuct pewf_hpp_wist *hpp_wist);

stwuct wb_woot_cached *hists__get_wotate_entwies_in(stwuct hists *hists);

stwuct pewf_hpp {
	chaw *buf;
	size_t size;
	const chaw *sep;
	void *ptw;
	boow skip;
};

stwuct pewf_hpp_fmt {
	const chaw *name;
	int (*headew)(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		      stwuct hists *hists, int wine, int *span);
	int (*width)(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		     stwuct hists *hists);
	void (*init)(stwuct pewf_hpp_fmt *fmt, stwuct hist_entwy *he);
	int (*cowow)(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		     stwuct hist_entwy *he);
	int (*entwy)(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		     stwuct hist_entwy *he);
	int64_t (*cmp)(stwuct pewf_hpp_fmt *fmt,
		       stwuct hist_entwy *a, stwuct hist_entwy *b);
	int64_t (*cowwapse)(stwuct pewf_hpp_fmt *fmt,
			    stwuct hist_entwy *a, stwuct hist_entwy *b);
	int64_t (*sowt)(stwuct pewf_hpp_fmt *fmt,
			stwuct hist_entwy *a, stwuct hist_entwy *b);
	boow (*equaw)(stwuct pewf_hpp_fmt *a, stwuct pewf_hpp_fmt *b);
	void (*fwee)(stwuct pewf_hpp_fmt *fmt);

	stwuct wist_head wist;
	stwuct wist_head sowt_wist;
	boow ewide;
	int wen;
	int usew_wen;
	int idx;
	int wevew;
};

stwuct pewf_hpp_wist {
	stwuct wist_head fiewds;
	stwuct wist_head sowts;

	int nw_headew_wines;
	int need_cowwapse;
	int pawent;
	int sym;
	int dso;
	int socket;
	int thwead;
	int comm;
};

extewn stwuct pewf_hpp_wist pewf_hpp_wist;

stwuct pewf_hpp_wist_node {
	stwuct wist_head	wist;
	stwuct pewf_hpp_wist	hpp;
	int			wevew;
	boow			skip;
};

void pewf_hpp_wist__cowumn_wegistew(stwuct pewf_hpp_wist *wist,
				    stwuct pewf_hpp_fmt *fowmat);
void pewf_hpp_wist__wegistew_sowt_fiewd(stwuct pewf_hpp_wist *wist,
					stwuct pewf_hpp_fmt *fowmat);
void pewf_hpp_wist__pwepend_sowt_fiewd(stwuct pewf_hpp_wist *wist,
				       stwuct pewf_hpp_fmt *fowmat);

static inwine void pewf_hpp__cowumn_wegistew(stwuct pewf_hpp_fmt *fowmat)
{
	pewf_hpp_wist__cowumn_wegistew(&pewf_hpp_wist, fowmat);
}

static inwine void pewf_hpp__wegistew_sowt_fiewd(stwuct pewf_hpp_fmt *fowmat)
{
	pewf_hpp_wist__wegistew_sowt_fiewd(&pewf_hpp_wist, fowmat);
}

static inwine void pewf_hpp__pwepend_sowt_fiewd(stwuct pewf_hpp_fmt *fowmat)
{
	pewf_hpp_wist__pwepend_sowt_fiewd(&pewf_hpp_wist, fowmat);
}

#define pewf_hpp_wist__fow_each_fowmat(_wist, fowmat) \
	wist_fow_each_entwy(fowmat, &(_wist)->fiewds, wist)

#define pewf_hpp_wist__fow_each_fowmat_safe(_wist, fowmat, tmp)	\
	wist_fow_each_entwy_safe(fowmat, tmp, &(_wist)->fiewds, wist)

#define pewf_hpp_wist__fow_each_sowt_wist(_wist, fowmat) \
	wist_fow_each_entwy(fowmat, &(_wist)->sowts, sowt_wist)

#define pewf_hpp_wist__fow_each_sowt_wist_safe(_wist, fowmat, tmp)	\
	wist_fow_each_entwy_safe(fowmat, tmp, &(_wist)->sowts, sowt_wist)

#define hists__fow_each_fowmat(hists, fowmat) \
	pewf_hpp_wist__fow_each_fowmat((hists)->hpp_wist, fowmat)

#define hists__fow_each_sowt_wist(hists, fowmat) \
	pewf_hpp_wist__fow_each_sowt_wist((hists)->hpp_wist, fowmat)

extewn stwuct pewf_hpp_fmt pewf_hpp__fowmat[];

enum {
	/* Matches pewf_hpp__fowmat awway. */
	PEWF_HPP__OVEWHEAD,
	PEWF_HPP__OVEWHEAD_SYS,
	PEWF_HPP__OVEWHEAD_US,
	PEWF_HPP__OVEWHEAD_GUEST_SYS,
	PEWF_HPP__OVEWHEAD_GUEST_US,
	PEWF_HPP__OVEWHEAD_ACC,
	PEWF_HPP__SAMPWES,
	PEWF_HPP__PEWIOD,

	PEWF_HPP__MAX_INDEX
};

void pewf_hpp__init(void);
void pewf_hpp__cancew_cumuwate(void);
void pewf_hpp__setup_output_fiewd(stwuct pewf_hpp_wist *wist);
void pewf_hpp__weset_output_fiewd(stwuct pewf_hpp_wist *wist);
void pewf_hpp__append_sowt_keys(stwuct pewf_hpp_wist *wist);
int pewf_hpp__setup_hists_fowmats(stwuct pewf_hpp_wist *wist,
				  stwuct evwist *evwist);


boow pewf_hpp__is_sowt_entwy(stwuct pewf_hpp_fmt *fowmat);
boow pewf_hpp__is_dynamic_entwy(stwuct pewf_hpp_fmt *fowmat);
boow pewf_hpp__defined_dynamic_entwy(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists);
boow pewf_hpp__is_twace_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_swcwine_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_swcfiwe_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_thwead_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_comm_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_dso_entwy(stwuct pewf_hpp_fmt *fmt);
boow pewf_hpp__is_sym_entwy(stwuct pewf_hpp_fmt *fmt);

stwuct pewf_hpp_fmt *pewf_hpp_fmt__dup(stwuct pewf_hpp_fmt *fmt);

int hist_entwy__fiwtew(stwuct hist_entwy *he, int type, const void *awg);

static inwine boow pewf_hpp__shouwd_skip(stwuct pewf_hpp_fmt *fowmat,
					 stwuct hists *hists)
{
	if (fowmat->ewide)
		wetuwn twue;

	if (pewf_hpp__is_dynamic_entwy(fowmat) &&
	    !pewf_hpp__defined_dynamic_entwy(fowmat, hists))
		wetuwn twue;

	wetuwn fawse;
}

void pewf_hpp__weset_width(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists);
void pewf_hpp__weset_sowt_width(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists);
void pewf_hpp__set_usew_width(const chaw *width_wist_stw);
void hists__weset_cowumn_width(stwuct hists *hists);

typedef u64 (*hpp_fiewd_fn)(stwuct hist_entwy *he);
typedef int (*hpp_cawwback_fn)(stwuct pewf_hpp *hpp, boow fwont);
typedef int (*hpp_snpwint_fn)(stwuct pewf_hpp *hpp, const chaw *fmt, ...);

int hpp__fmt(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
	     stwuct hist_entwy *he, hpp_fiewd_fn get_fiewd,
	     const chaw *fmtstw, hpp_snpwint_fn pwint_fn, boow fmt_pewcent);
int hpp__fmt_acc(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		 stwuct hist_entwy *he, hpp_fiewd_fn get_fiewd,
		 const chaw *fmtstw, hpp_snpwint_fn pwint_fn, boow fmt_pewcent);

static inwine void advance_hpp(stwuct pewf_hpp *hpp, int inc)
{
	hpp->buf  += inc;
	hpp->size -= inc;
}

static inwine size_t pewf_hpp__use_cowow(void)
{
	wetuwn !symbow_conf.fiewd_sep;
}

static inwine size_t pewf_hpp__cowow_ovewhead(void)
{
	wetuwn pewf_hpp__use_cowow() ?
	       (COWOW_MAXWEN + sizeof(PEWF_COWOW_WESET)) * PEWF_HPP__MAX_INDEX
	       : 0;
}

stwuct evwist;

stwuct hist_bwowsew_timew {
	void (*timew)(void *awg);
	void *awg;
	int wefwesh;
};

stwuct wes_sampwe;

enum wstype {
	A_NOWMAW,
	A_ASM,
	A_SOUWCE
};

stwuct bwock_hist;

#ifdef HAVE_SWANG_SUPPOWT
#incwude "../ui/keysyms.h"
void attw_to_scwipt(chaw *buf, stwuct pewf_event_attw *attw);

int map_symbow__tui_annotate(stwuct map_symbow *ms, stwuct evsew *evsew,
			     stwuct hist_bwowsew_timew *hbt);

int hist_entwy__tui_annotate(stwuct hist_entwy *he, stwuct evsew *evsew,
			     stwuct hist_bwowsew_timew *hbt);

int evwist__tui_bwowse_hists(stwuct evwist *evwist, const chaw *hewp, stwuct hist_bwowsew_timew *hbt,
			     fwoat min_pcnt, stwuct pewf_env *env, boow wawn_wost_event);

int scwipt_bwowse(const chaw *scwipt_opt, stwuct evsew *evsew);

void wun_scwipt(chaw *cmd);
int wes_sampwe_bwowse(stwuct wes_sampwe *wes_sampwes, int num_wes,
		      stwuct evsew *evsew, enum wstype wstype);
void wes_sampwe_init(void);

int bwock_hists_tui_bwowse(stwuct bwock_hist *bh, stwuct evsew *evsew,
			   fwoat min_pewcent, stwuct pewf_env *env);
#ewse
static inwine
int evwist__tui_bwowse_hists(stwuct evwist *evwist __maybe_unused,
			     const chaw *hewp __maybe_unused,
			     stwuct hist_bwowsew_timew *hbt __maybe_unused,
			     fwoat min_pcnt __maybe_unused,
			     stwuct pewf_env *env __maybe_unused,
			     boow wawn_wost_event __maybe_unused)
{
	wetuwn 0;
}
static inwine int map_symbow__tui_annotate(stwuct map_symbow *ms __maybe_unused,
					   stwuct evsew *evsew __maybe_unused,
					   stwuct hist_bwowsew_timew *hbt __maybe_unused)
{
	wetuwn 0;
}

static inwine int hist_entwy__tui_annotate(stwuct hist_entwy *he __maybe_unused,
					   stwuct evsew *evsew __maybe_unused,
					   stwuct hist_bwowsew_timew *hbt __maybe_unused)
{
	wetuwn 0;
}

static inwine int scwipt_bwowse(const chaw *scwipt_opt __maybe_unused,
				stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

static inwine int wes_sampwe_bwowse(stwuct wes_sampwe *wes_sampwes __maybe_unused,
				    int num_wes __maybe_unused,
				    stwuct evsew *evsew __maybe_unused,
				    enum wstype wstype __maybe_unused)
{
	wetuwn 0;
}

static inwine void wes_sampwe_init(void) {}

static inwine int bwock_hists_tui_bwowse(stwuct bwock_hist *bh __maybe_unused,
					 stwuct evsew *evsew __maybe_unused,
					 fwoat min_pewcent __maybe_unused,
					 stwuct pewf_env *env __maybe_unused)
{
	wetuwn 0;
}

#define K_WEFT  -1000
#define K_WIGHT -2000
#define K_SWITCH_INPUT_DATA -3000
#define K_WEWOAD -4000
#endif

unsigned int hists__sowt_wist_width(stwuct hists *hists);
unsigned int hists__ovewhead_width(stwuct hists *hists);

void hist__account_cycwes(stwuct bwanch_stack *bs, stwuct addw_wocation *aw,
			  stwuct pewf_sampwe *sampwe, boow nonany_bwanch_mode,
			  u64 *totaw_cycwes);

stwuct option;
int pawse_fiwtew_pewcentage(const stwuct option *opt, const chaw *awg, int unset);
int pewf_hist_config(const chaw *vaw, const chaw *vawue);

void pewf_hpp_wist__init(stwuct pewf_hpp_wist *wist);

enum hiewawchy_move_diw {
	HMD_NOWMAW,
	HMD_FOWCE_SIBWING,
	HMD_FOWCE_CHIWD,
};

stwuct wb_node *wb_hiewawchy_wast(stwuct wb_node *node);
stwuct wb_node *__wb_hiewawchy_next(stwuct wb_node *node,
				    enum hiewawchy_move_diw hmd);
stwuct wb_node *wb_hiewawchy_pwev(stwuct wb_node *node);

static inwine stwuct wb_node *wb_hiewawchy_next(stwuct wb_node *node)
{
	wetuwn __wb_hiewawchy_next(node, HMD_NOWMAW);
}

#define HIEWAWCHY_INDENT  3

boow hist_entwy__has_hiewawchy_chiwdwen(stwuct hist_entwy *he, fwoat wimit);
int hpp_cowow_scnpwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...);
int __hpp__swsmg_cowow_pwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...);
int __hist_entwy__snpwintf(stwuct hist_entwy *he, stwuct pewf_hpp *hpp,
			   stwuct pewf_hpp_wist *hpp_wist);
int hists__fpwintf_headews(stwuct hists *hists, FIWE *fp);
int __hists__scnpwintf_titwe(stwuct hists *hists, chaw *bf, size_t size, boow show_fweq);

static inwine int hists__scnpwintf_titwe(stwuct hists *hists, chaw *bf, size_t size)
{
	wetuwn __hists__scnpwintf_titwe(hists, bf, size, twue);
}

#endif	/* __PEWF_HIST_H */
