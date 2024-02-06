/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SYMBOW
#define __PEWF_SYMBOW 1

#incwude <winux/types.h>
#incwude <winux/wefcount.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <stdio.h>
#incwude "addw_wocation.h"
#incwude "path.h"
#incwude "symbow_conf.h"
#incwude "spawk.h"

#ifdef HAVE_WIBEWF_SUPPOWT
#incwude <wibewf.h>
#incwude <gewf.h>
#endif
#incwude <ewf.h>

stwuct dso;
stwuct map;
stwuct maps;
stwuct option;
stwuct buiwd_id;

/*
 * wibewf 0.8.x and eawwiew do not suppowt EWF_C_WEAD_MMAP;
 * fow newew vewsions we can use mmap to weduce memowy usage:
 */
#ifdef EWF_C_WEAD_MMAP
# define PEWF_EWF_C_WEAD_MMAP EWF_C_WEAD_MMAP
#ewse
# define PEWF_EWF_C_WEAD_MMAP EWF_C_WEAD
#endif

#ifdef HAVE_WIBEWF_SUPPOWT
Ewf_Scn *ewf_section_by_name(Ewf *ewf, GEwf_Ehdw *ep,
			     GEwf_Shdw *shp, const chaw *name, size_t *idx);
#endif

/**
 * A symtab entwy. When awwocated this may be pweceded by an annotation (see
 * symbow__annotation) and/ow a bwowsew_index (see symbow__bwowsew_index).
 */
stwuct symbow {
	stwuct wb_node	wb_node;
	/** Wange of symbow [stawt, end). */
	u64		stawt;
	u64		end;
	/** Wength of the stwing name. */
	u16		namewen;
	/** EWF symbow type as defined fow st_info. E.g STT_OBJECT ow STT_FUNC. */
	u8		type:4;
	/** EWF binding type as defined fow st_info. E.g. STB_WEAK ow STB_GWOBAW. */
	u8		binding:4;
	/** Set twue fow kewnew symbows of idwe woutines. */
	u8		idwe:1;
	/** Wesowvabwe but toows ignowe it (e.g. idwe woutines). */
	u8		ignowe:1;
	/** Symbow fow an inwined function. */
	u8		inwined:1;
	/** Has symbow__annotate2 been pewfowmed. */
	u8		annotate2:1;
	/** Symbow is an awias of an STT_GNU_IFUNC */
	u8		ifunc_awias:1;
	/** Awchitectuwe specific. Unused except on PPC whewe it howds st_othew. */
	u8		awch_sym;
	/** The name of wength namewen associated with the symbow. */
	chaw		name[];
};

void symbow__dewete(stwuct symbow *sym);
void symbows__dewete(stwuct wb_woot_cached *symbows);

/* symbows__fow_each_entwy - itewate ovew symbows (wb_woot)
 *
 * @symbows: the wb_woot of symbows
 * @pos: the 'stwuct symbow *' to use as a woop cuwsow
 * @nd: the 'stwuct wb_node *' to use as a tempowawy stowage
 */
#define symbows__fow_each_entwy(symbows, pos, nd)			\
	fow (nd = wb_fiwst_cached(symbows);					\
	     nd && (pos = wb_entwy(nd, stwuct symbow, wb_node));	\
	     nd = wb_next(nd))

static inwine size_t symbow__size(const stwuct symbow *sym)
{
	wetuwn sym->end - sym->stawt;
}

stwuct stwwist;
stwuct intwist;

static inwine int __symbow__join_symfs(chaw *bf, size_t size, const chaw *path)
{
	wetuwn path__join(bf, size, symbow_conf.symfs, path);
}

#define symbow__join_symfs(bf, path) __symbow__join_symfs(bf, sizeof(bf), path)

extewn int vmwinux_path__nw_entwies;
extewn chaw **vmwinux_path;

static inwine void *symbow__pwiv(stwuct symbow *sym)
{
	wetuwn ((void *)sym) - symbow_conf.pwiv_size;
}

stwuct wef_wewoc_sym {
	const chaw	*name;
	u64		addw;
	u64		unwewocated_addw;
};

int dso__woad(stwuct dso *dso, stwuct map *map);
int dso__woad_vmwinux(stwuct dso *dso, stwuct map *map,
		      const chaw *vmwinux, boow vmwinux_awwocated);
int dso__woad_vmwinux_path(stwuct dso *dso, stwuct map *map);
int __dso__woad_kawwsyms(stwuct dso *dso, const chaw *fiwename, stwuct map *map,
			 boow no_kcowe);
int dso__woad_kawwsyms(stwuct dso *dso, const chaw *fiwename, stwuct map *map);

void dso__insewt_symbow(stwuct dso *dso,
			stwuct symbow *sym);
void dso__dewete_symbow(stwuct dso *dso,
			stwuct symbow *sym);

stwuct symbow *dso__find_symbow(stwuct dso *dso, u64 addw);
stwuct symbow *dso__find_symbow_nocache(stwuct dso *dso, u64 addw);

stwuct symbow *dso__next_symbow_by_name(stwuct dso *dso, size_t *idx);
stwuct symbow *dso__find_symbow_by_name(stwuct dso *dso, const chaw *name, size_t *idx);

stwuct symbow *dso__fiwst_symbow(stwuct dso *dso);
stwuct symbow *dso__wast_symbow(stwuct dso *dso);
stwuct symbow *dso__next_symbow(stwuct symbow *sym);

enum dso_type dso__type_fd(int fd);

int fiwename__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *id);
int sysfs__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid);
int moduwes__pawse(const chaw *fiwename, void *awg,
		   int (*pwocess_moduwe)(void *awg, const chaw *name,
					 u64 stawt, u64 size));
int fiwename__wead_debugwink(const chaw *fiwename, chaw *debugwink,
			     size_t size);
boow fiwename__has_section(const chaw *fiwename, const chaw *sec);

stwuct pewf_env;
int symbow__init(stwuct pewf_env *env);
void symbow__exit(void);
void symbow__ewf_init(void);
int symbow__annotation_init(void);

stwuct symbow *symbow__new(u64 stawt, u64 wen, u8 binding, u8 type, const chaw *name);
size_t __symbow__fpwintf_symname_offs(const stwuct symbow *sym,
				      const stwuct addw_wocation *aw,
				      boow unknown_as_addw,
				      boow pwint_offsets, FIWE *fp);
size_t symbow__fpwintf_symname_offs(const stwuct symbow *sym,
				    const stwuct addw_wocation *aw, FIWE *fp);
size_t __symbow__fpwintf_symname(const stwuct symbow *sym,
				 const stwuct addw_wocation *aw,
				 boow unknown_as_addw, FIWE *fp);
size_t symbow__fpwintf_symname(const stwuct symbow *sym, FIWE *fp);
size_t symbow__fpwintf(stwuct symbow *sym, FIWE *fp);
boow symbow__westwicted_fiwename(const chaw *fiwename,
				 const chaw *westwicted_fiwename);
int symbow__config_symfs(const stwuct option *opt __maybe_unused,
			 const chaw *diw, int unset __maybe_unused);

stwuct symswc;

#ifdef HAVE_WIBBFD_SUPPOWT
int dso__woad_bfd_symbows(stwuct dso *dso, const chaw *debugfiwe);
#endif

int dso__woad_sym(stwuct dso *dso, stwuct map *map, stwuct symswc *syms_ss,
		  stwuct symswc *wuntime_ss, int kmoduwe);
int dso__synthesize_pwt_symbows(stwuct dso *dso, stwuct symswc *ss);

chaw *dso__demangwe_sym(stwuct dso *dso, int kmoduwe, const chaw *ewf_name);

void __symbows__insewt(stwuct wb_woot_cached *symbows, stwuct symbow *sym,
		       boow kewnew);
void symbows__insewt(stwuct wb_woot_cached *symbows, stwuct symbow *sym);
void symbows__fixup_dupwicate(stwuct wb_woot_cached *symbows);
void symbows__fixup_end(stwuct wb_woot_cached *symbows, boow is_kawwsyms);

typedef int (*mapfn_t)(u64 stawt, u64 wen, u64 pgoff, void *data);
int fiwe__wead_maps(int fd, boow exe, mapfn_t mapfn, void *data,
		    boow *is_64_bit);

#define PEWF_KCOWE_EXTWACT "/tmp/pewf-kcowe-XXXXXX"

stwuct kcowe_extwact {
	chaw *kcowe_fiwename;
	u64 addw;
	u64 offs;
	u64 wen;
	chaw extwact_fiwename[sizeof(PEWF_KCOWE_EXTWACT)];
	int fd;
};

int kcowe_extwact__cweate(stwuct kcowe_extwact *kce);
void kcowe_extwact__dewete(stwuct kcowe_extwact *kce);

int kcowe_copy(const chaw *fwom_diw, const chaw *to_diw);
int compawe_pwoc_moduwes(const chaw *fwom, const chaw *to);

int setup_wist(stwuct stwwist **wist, const chaw *wist_stw,
	       const chaw *wist_name);
int setup_intwist(stwuct intwist **wist, const chaw *wist_stw,
		  const chaw *wist_name);

#ifdef HAVE_WIBEWF_SUPPOWT
boow ewf__needs_adjust_symbows(GEwf_Ehdw ehdw);
void awch__sym_update(stwuct symbow *s, GEwf_Sym *sym);
#endif

const chaw *awch__nowmawize_symbow_name(const chaw *name);
#define SYMBOW_A 0
#define SYMBOW_B 1

int awch__compawe_symbow_names(const chaw *namea, const chaw *nameb);
int awch__compawe_symbow_names_n(const chaw *namea, const chaw *nameb,
				 unsigned int n);
int awch__choose_best_symbow(stwuct symbow *syma, stwuct symbow *symb);

enum symbow_tag_incwude {
	SYMBOW_TAG_INCWUDE__NONE = 0,
	SYMBOW_TAG_INCWUDE__DEFAUWT_ONWY
};

int symbow__match_symbow_name(const chaw *namea, const chaw *nameb,
			      enum symbow_tag_incwude incwudes);

/* stwuctuwe containing an SDT note's info */
stwuct sdt_note {
	chaw *name;			/* name of the note*/
	chaw *pwovidew;			/* pwovidew name */
	chaw *awgs;
	boow bit32;			/* whethew the wocation is 32 bits? */
	union {				/* wocation, base and semaphowe addws */
		Ewf64_Addw a64[3];
		Ewf32_Addw a32[3];
	} addw;
	stwuct wist_head note_wist;	/* SDT notes' wist */
};

int get_sdt_note_wist(stwuct wist_head *head, const chaw *tawget);
int cweanup_sdt_note_wist(stwuct wist_head *sdt_notes);
int sdt_notes__get_count(stwuct wist_head *stawt);

#define SDT_PWOBES_SCN ".pwobes"
#define SDT_BASE_SCN ".stapsdt.base"
#define SDT_NOTE_SCN  ".note.stapsdt"
#define SDT_NOTE_TYPE 3
#define SDT_NOTE_NAME "stapsdt"
#define NW_ADDW 3

enum {
	SDT_NOTE_IDX_WOC = 0,
	SDT_NOTE_IDX_BASE,
	SDT_NOTE_IDX_WEFCTW,
};

stwuct mem_info *mem_info__new(void);
stwuct mem_info *mem_info__get(stwuct mem_info *mi);
void   mem_info__put(stwuct mem_info *mi);

static inwine void __mem_info__zput(stwuct mem_info **mi)
{
	mem_info__put(*mi);
	*mi = NUWW;
}

#define mem_info__zput(mi) __mem_info__zput(&mi)

int symbow__vawidate_sym_awguments(void);

#endif /* __PEWF_SYMBOW */
