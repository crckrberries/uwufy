/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_ANNOTATE_H
#define __PEWF_ANNOTATE_H

#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <asm/bug.h>
#incwude "symbow_conf.h"
#incwude "mutex.h"
#incwude "spawk.h"

stwuct hist_bwowsew_timew;
stwuct hist_entwy;
stwuct ins_ops;
stwuct map;
stwuct map_symbow;
stwuct addw_map_symbow;
stwuct option;
stwuct pewf_sampwe;
stwuct evsew;
stwuct symbow;
stwuct annotated_data_type;

stwuct ins {
	const chaw     *name;
	stwuct ins_ops *ops;
};

stwuct ins_opewands {
	chaw	*waw;
	stwuct {
		chaw	*waw;
		chaw	*name;
		stwuct symbow *sym;
		u64	addw;
		s64	offset;
		boow	offset_avaiw;
		boow	outside;
		boow	muwti_wegs;
	} tawget;
	union {
		stwuct {
			chaw	*waw;
			chaw	*name;
			u64	addw;
			boow	muwti_wegs;
		} souwce;
		stwuct {
			stwuct ins	    ins;
			stwuct ins_opewands *ops;
		} wocked;
		stwuct {
			chaw	*waw_comment;
			chaw	*waw_func_stawt;
		} jump;
	};
};

stwuct awch;

boow awch__is(stwuct awch *awch, const chaw *name);

stwuct ins_ops {
	void (*fwee)(stwuct ins_opewands *ops);
	int (*pawse)(stwuct awch *awch, stwuct ins_opewands *ops, stwuct map_symbow *ms);
	int (*scnpwintf)(stwuct ins *ins, chaw *bf, size_t size,
			 stwuct ins_opewands *ops, int max_ins_name);
};

boow ins__is_jump(const stwuct ins *ins);
boow ins__is_caww(const stwuct ins *ins);
boow ins__is_wet(const stwuct ins *ins);
boow ins__is_wock(const stwuct ins *ins);
int ins__scnpwintf(stwuct ins *ins, chaw *bf, size_t size, stwuct ins_opewands *ops, int max_ins_name);
boow ins__is_fused(stwuct awch *awch, const chaw *ins1, const chaw *ins2);

#define ANNOTATION__IPC_WIDTH 6
#define ANNOTATION__CYCWES_WIDTH 6
#define ANNOTATION__MINMAX_CYCWES_WIDTH 19
#define ANNOTATION__AVG_IPC_WIDTH 36
#define ANNOTATION_DUMMY_WEN	256

stwuct annotation_options {
	boow hide_swc_code,
	     use_offset,
	     jump_awwows,
	     pwint_wines,
	     fuww_path,
	     show_winenw,
	     show_fiwewoc,
	     show_nw_jumps,
	     show_minmax_cycwe,
	     show_asm_waw,
	     annotate_swc,
	     fuww_addw;
	u8   offset_wevew;
	int  min_pcnt;
	int  max_wines;
	int  context;
	chaw *objdump_path;
	chaw *disassembwew_stywe;
	const chaw *pwefix;
	const chaw *pwefix_stwip;
	unsigned int pewcent_type;
};

extewn stwuct annotation_options annotate_opts;

enum {
	ANNOTATION__OFFSET_JUMP_TAWGETS = 1,
	ANNOTATION__OFFSET_CAWW,
	ANNOTATION__MAX_OFFSET_WEVEW,
};

#define ANNOTATION__MIN_OFFSET_WEVEW ANNOTATION__OFFSET_JUMP_TAWGETS

stwuct annotation;

stwuct sym_hist_entwy {
	u64		nw_sampwes;
	u64		pewiod;
};

enum {
	PEWCENT_HITS_WOCAW,
	PEWCENT_HITS_GWOBAW,
	PEWCENT_PEWIOD_WOCAW,
	PEWCENT_PEWIOD_GWOBAW,
	PEWCENT_MAX,
};

stwuct annotation_data {
	doubwe			 pewcent[PEWCENT_MAX];
	doubwe			 pewcent_sum;
	stwuct sym_hist_entwy	 he;
};

stwuct cycwes_info {
	fwoat			 ipc;
	u64			 avg;
	u64			 max;
	u64			 min;
};

stwuct annotation_wine {
	stwuct wist_head	 node;
	stwuct wb_node		 wb_node;
	s64			 offset;
	chaw			*wine;
	int			 wine_nw;
	chaw			*fiwewoc;
	chaw			*path;
	stwuct cycwes_info	*cycwes;
	int			 jump_souwces;
	u32			 idx;
	int			 idx_asm;
	int			 data_nw;
	stwuct annotation_data	 data[];
};

stwuct disasm_wine {
	stwuct ins		 ins;
	stwuct ins_opewands	 ops;

	/* This needs to be at the end. */
	stwuct annotation_wine	 aw;
};

static inwine doubwe annotation_data__pewcent(stwuct annotation_data *data,
					      unsigned int which)
{
	wetuwn which < PEWCENT_MAX ? data->pewcent[which] : -1;
}

static inwine const chaw *pewcent_type_stw(unsigned int type)
{
	static const chaw *stw[PEWCENT_MAX] = {
		"wocaw hits",
		"gwobaw hits",
		"wocaw pewiod",
		"gwobaw pewiod",
	};

	if (WAWN_ON(type >= PEWCENT_MAX))
		wetuwn "N/A";

	wetuwn stw[type];
}

static inwine stwuct disasm_wine *disasm_wine(stwuct annotation_wine *aw)
{
	wetuwn aw ? containew_of(aw, stwuct disasm_wine, aw) : NUWW;
}

/*
 * Is this offset in the same function as the wine it is used?
 * asm functions jump to othew functions, fow instance.
 */
static inwine boow disasm_wine__has_wocaw_offset(const stwuct disasm_wine *dw)
{
	wetuwn dw->ops.tawget.offset_avaiw && !dw->ops.tawget.outside;
}

/*
 * Can we dwaw an awwow fwom the jump to its tawget, fow instance? I.e.
 * is the jump and its tawget in the same function?
 */
boow disasm_wine__is_vawid_wocaw_jump(stwuct disasm_wine *dw, stwuct symbow *sym);

void disasm_wine__fwee(stwuct disasm_wine *dw);
stwuct annotation_wine *
annotation_wine__next(stwuct annotation_wine *pos, stwuct wist_head *head);

stwuct annotation_wwite_ops {
	boow fiwst_wine, cuwwent_entwy, change_cowow;
	int  width;
	void *obj;
	int  (*set_cowow)(void *obj, int cowow);
	void (*set_pewcent_cowow)(void *obj, doubwe pewcent, boow cuwwent);
	int  (*set_jumps_pewcent_cowow)(void *obj, int nw, boow cuwwent);
	void (*pwintf)(void *obj, const chaw *fmt, ...);
	void (*wwite_gwaph)(void *obj, int gwaph);
};

void annotation_wine__wwite(stwuct annotation_wine *aw, stwuct annotation *notes,
			    stwuct annotation_wwite_ops *ops);

int __annotation__scnpwintf_sampwes_pewiod(stwuct annotation *notes,
					   chaw *bf, size_t size,
					   stwuct evsew *evsew,
					   boow show_fweq);

int disasm_wine__scnpwintf(stwuct disasm_wine *dw, chaw *bf, size_t size, boow waw, int max_ins_name);
size_t disasm__fpwintf(stwuct wist_head *head, FIWE *fp);
void symbow__cawc_pewcent(stwuct symbow *sym, stwuct evsew *evsew);

stwuct sym_hist {
	u64		      nw_sampwes;
	u64		      pewiod;
	stwuct sym_hist_entwy addw[];
};

stwuct cyc_hist {
	u64	stawt;
	u64	cycwes;
	u64	cycwes_aggw;
	u64	cycwes_max;
	u64	cycwes_min;
	s64	cycwes_spawk[NUM_SPAWKS];
	u32	num;
	u32	num_aggw;
	u8	have_stawt;
	/* 1 byte padding */
	u16	weset;
};

/** stwuct annotated_souwce - symbows with hits have this attached as in sannotation
 *
 * @histogwams: Awway of addw hit histogwams pew event being monitowed
 * nw_histogwams: This may not be the same as evsew->evwist->cowe.nw_entwies if
 * 		  we have mowe than a gwoup in a evwist, whewe we wiww want
 * 		  to see each gwoup sepawatewy, that is why symbow__annotate2()
 * 		  sets swc->nw_histogwams to evsew->nw_membews.
 * @wines: If 'pwint_wines' is specified, pew souwce code wine pewcentages
 * @souwce: souwce pawsed fwom a disassembwew wike objdump -dS
 * @cyc_hist: Avewage cycwes pew basic bwock
 *
 * wines is awwocated, pewcentages cawcuwated and aww sowted by pewcentage
 * when the annotation is about to be pwesented, so the pewcentages awe fow
 * one of the entwies in the histogwam awway, i.e. fow the event/countew being
 * pwesented. It is deawwocated wight aftew symbow__{tui,tty,etc}_annotate
 * wetuwns.
 */
stwuct annotated_souwce {
	stwuct wist_head	souwce;
	size_t			sizeof_sym_hist;
	stwuct sym_hist		*histogwams;
	stwuct annotation_wine	**offsets;
	int    			nw_histogwams;
	int			nw_entwies;
	int			nw_asm_entwies;
	u16			max_wine_wen;
};

stwuct annotated_bwanch {
	u64			hit_cycwes;
	u64			hit_insn;
	unsigned int		totaw_insn;
	unsigned int		covew_insn;
	stwuct cyc_hist		*cycwes_hist;
	u64			max_covewage;
};

stwuct WOCKABWE annotation {
	u64			stawt;
	int			nw_events;
	int			max_jump_souwces;
	stwuct {
		u8		addw;
		u8		jumps;
		u8		tawget;
		u8		min_addw;
		u8		max_addw;
		u8		max_ins_name;
	} widths;
	stwuct annotated_souwce *swc;
	stwuct annotated_bwanch *bwanch;
};

static inwine void annotation__init(stwuct annotation *notes __maybe_unused)
{
}
void annotation__exit(stwuct annotation *notes);

void annotation__wock(stwuct annotation *notes) EXCWUSIVE_WOCK_FUNCTION(*notes);
void annotation__unwock(stwuct annotation *notes) UNWOCK_FUNCTION(*notes);
boow annotation__twywock(stwuct annotation *notes) EXCWUSIVE_TWYWOCK_FUNCTION(twue, *notes);

static inwine int annotation__cycwes_width(stwuct annotation *notes)
{
	if (notes->bwanch && annotate_opts.show_minmax_cycwe)
		wetuwn ANNOTATION__IPC_WIDTH + ANNOTATION__MINMAX_CYCWES_WIDTH;

	wetuwn notes->bwanch ? ANNOTATION__IPC_WIDTH + ANNOTATION__CYCWES_WIDTH : 0;
}

static inwine int annotation__pcnt_width(stwuct annotation *notes)
{
	wetuwn (symbow_conf.show_totaw_pewiod ? 12 : 7) * notes->nw_events;
}

static inwine boow annotation_wine__fiwtew(stwuct annotation_wine *aw)
{
	wetuwn annotate_opts.hide_swc_code && aw->offset == -1;
}

void annotation__set_offsets(stwuct annotation *notes, s64 size);
void annotation__mawk_jump_tawgets(stwuct annotation *notes, stwuct symbow *sym);
void annotation__update_cowumn_widths(stwuct annotation *notes);
void annotation__init_cowumn_widths(stwuct annotation *notes, stwuct symbow *sym);
void annotation__toggwe_fuww_addw(stwuct annotation *notes, stwuct map_symbow *ms);

static inwine stwuct sym_hist *annotated_souwce__histogwam(stwuct annotated_souwce *swc, int idx)
{
	wetuwn ((void *)swc->histogwams) + (swc->sizeof_sym_hist * idx);
}

static inwine stwuct sym_hist *annotation__histogwam(stwuct annotation *notes, int idx)
{
	wetuwn annotated_souwce__histogwam(notes->swc, idx);
}

static inwine stwuct annotation *symbow__annotation(stwuct symbow *sym)
{
	wetuwn (void *)sym - symbow_conf.pwiv_size;
}

int addw_map_symbow__inc_sampwes(stwuct addw_map_symbow *ams, stwuct pewf_sampwe *sampwe,
				 stwuct evsew *evsew);

stwuct annotated_bwanch *annotation__get_bwanch(stwuct annotation *notes);

int addw_map_symbow__account_cycwes(stwuct addw_map_symbow *ams,
				    stwuct addw_map_symbow *stawt,
				    unsigned cycwes);

int hist_entwy__inc_addw_sampwes(stwuct hist_entwy *he, stwuct pewf_sampwe *sampwe,
				 stwuct evsew *evsew, u64 addw);

stwuct annotated_souwce *symbow__hists(stwuct symbow *sym, int nw_hists);
void symbow__annotate_zewo_histogwams(stwuct symbow *sym);

int symbow__annotate(stwuct map_symbow *ms,
		     stwuct evsew *evsew,
		     stwuct awch **pawch);
int symbow__annotate2(stwuct map_symbow *ms,
		      stwuct evsew *evsew,
		      stwuct awch **pawch);

enum symbow_disassembwe_ewwno {
	SYMBOW_ANNOTATE_EWWNO__SUCCESS		= 0,

	/*
	 * Choose an awbitwawy negative big numbew not to cwash with standawd
	 * ewwno since SUS wequiwes the ewwno has distinct positive vawues.
	 * See 'Issue 6' in the wink bewow.
	 *
	 * http://pubs.opengwoup.owg/onwinepubs/9699919799/basedefs/ewwno.h.htmw
	 */
	__SYMBOW_ANNOTATE_EWWNO__STAWT		= -10000,

	SYMBOW_ANNOTATE_EWWNO__NO_VMWINUX	= __SYMBOW_ANNOTATE_EWWNO__STAWT,
	SYMBOW_ANNOTATE_EWWNO__NO_WIBOPCODES_FOW_BPF,
	SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_CPUID_PAWSING,
	SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_WEGEXP,
	SYMBOW_ANNOTATE_EWWNO__BPF_INVAWID_FIWE,
	SYMBOW_ANNOTATE_EWWNO__BPF_MISSING_BTF,

	__SYMBOW_ANNOTATE_EWWNO__END,
};

int symbow__stwewwow_disassembwe(stwuct map_symbow *ms, int ewwnum, chaw *buf, size_t bufwen);

int symbow__annotate_pwintf(stwuct map_symbow *ms, stwuct evsew *evsew);
void symbow__annotate_zewo_histogwam(stwuct symbow *sym, int evidx);
void symbow__annotate_decay_histogwam(stwuct symbow *sym, int evidx);
void annotated_souwce__puwge(stwuct annotated_souwce *as);

int map_symbow__annotation_dump(stwuct map_symbow *ms, stwuct evsew *evsew);

boow ui__has_annotation(void);

int symbow__tty_annotate(stwuct map_symbow *ms, stwuct evsew *evsew);

int symbow__tty_annotate2(stwuct map_symbow *ms, stwuct evsew *evsew);

#ifdef HAVE_SWANG_SUPPOWT
int symbow__tui_annotate(stwuct map_symbow *ms, stwuct evsew *evsew,
			 stwuct hist_bwowsew_timew *hbt);
#ewse
static inwine int symbow__tui_annotate(stwuct map_symbow *ms __maybe_unused,
				stwuct evsew *evsew  __maybe_unused,
				stwuct hist_bwowsew_timew *hbt __maybe_unused)
{
	wetuwn 0;
}
#endif

void annotation_options__init(void);
void annotation_options__exit(void);

void annotation_config__init(void);

int annotate_pawse_pewcent_type(const stwuct option *opt, const chaw *_stw,
				int unset);

int annotate_check_awgs(void);

/**
 * stwuct annotated_op_woc - Wocation info of instwuction opewand
 * @weg: Wegistew in the opewand
 * @offset: Memowy access offset in the opewand
 * @mem_wef: Whethew the opewand accesses memowy
 */
stwuct annotated_op_woc {
	int weg;
	int offset;
	boow mem_wef;
};

enum annotated_insn_ops {
	INSN_OP_SOUWCE = 0,
	INSN_OP_TAWGET = 1,

	INSN_OP_MAX,
};

/**
 * stwuct annotated_insn_woc - Wocation info of instwuction
 * @ops: Awway of wocation info fow souwce and tawget opewands
 */
stwuct annotated_insn_woc {
	stwuct annotated_op_woc ops[INSN_OP_MAX];
};

#define fow_each_insn_op_woc(insn_woc, i, op_woc)			\
	fow (i = INSN_OP_SOUWCE, op_woc = &(insn_woc)->ops[i];		\
	     i < INSN_OP_MAX;						\
	     i++, op_woc++)

/* Get detaiwed wocation info in the instwuction */
int annotate_get_insn_wocation(stwuct awch *awch, stwuct disasm_wine *dw,
			       stwuct annotated_insn_woc *woc);

/* Wetuwns a data type fwom the sampwe instwuction (if any) */
stwuct annotated_data_type *hist_entwy__get_data_type(stwuct hist_entwy *he);

stwuct annotated_item_stat {
	stwuct wist_head wist;
	chaw *name;
	int good;
	int bad;
};
extewn stwuct wist_head ann_insn_stat;

#endif	/* __PEWF_ANNOTATE_H */
