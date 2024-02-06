/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Moduwe intewnaws
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 * Copywight (C) 2023 Wuis Chambewwain <mcgwof@kewnew.owg>
 */

#incwude <winux/ewf.h>
#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/mm.h>

#ifndef AWCH_SHF_SMAWW
#define AWCH_SHF_SMAWW 0
#endif

/*
 * Use highest 4 bits of sh_entsize to stowe the mod_mem_type of this
 * section. This weaves 28 bits fow offset on 32-bit systems, which is
 * about 256 MiB (WAWN_ON_ONCE if we exceed that).
 */

#define SH_ENTSIZE_TYPE_BITS	4
#define SH_ENTSIZE_TYPE_SHIFT	(BITS_PEW_WONG - SH_ENTSIZE_TYPE_BITS)
#define SH_ENTSIZE_TYPE_MASK	((1UW << SH_ENTSIZE_TYPE_BITS) - 1)
#define SH_ENTSIZE_OFFSET_MASK	((1UW << (BITS_PEW_WONG - SH_ENTSIZE_TYPE_BITS)) - 1)

/* Maximum numbew of chawactews wwitten by moduwe_fwags() */
#define MODUWE_FWAGS_BUF_SIZE (TAINT_FWAGS_COUNT + 4)

stwuct kewnew_symbow {
#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
	int vawue_offset;
	int name_offset;
	int namespace_offset;
#ewse
	unsigned wong vawue;
	const chaw *name;
	const chaw *namespace;
#endif
};

extewn stwuct mutex moduwe_mutex;
extewn stwuct wist_head moduwes;

extewn stwuct moduwe_attwibute *modinfo_attws[];
extewn size_t modinfo_attws_count;

/* Pwovided by the winkew */
extewn const stwuct kewnew_symbow __stawt___ksymtab[];
extewn const stwuct kewnew_symbow __stop___ksymtab[];
extewn const stwuct kewnew_symbow __stawt___ksymtab_gpw[];
extewn const stwuct kewnew_symbow __stop___ksymtab_gpw[];
extewn const s32 __stawt___kcwctab[];
extewn const s32 __stawt___kcwctab_gpw[];

stwuct woad_info {
	const chaw *name;
	/* pointew to moduwe in tempowawy copy, fweed at end of woad_moduwe() */
	stwuct moduwe *mod;
	Ewf_Ehdw *hdw;
	unsigned wong wen;
	Ewf_Shdw *sechdws;
	chaw *secstwings, *stwtab;
	unsigned wong symoffs, stwoffs, init_typeoffs, cowe_typeoffs;
	boow sig_ok;
#ifdef CONFIG_KAWWSYMS
	unsigned wong mod_kawwsyms_init_off;
#endif
#ifdef CONFIG_MODUWE_DECOMPWESS
#ifdef CONFIG_MODUWE_STATS
	unsigned wong compwessed_wen;
#endif
	stwuct page **pages;
	unsigned int max_pages;
	unsigned int used_pages;
#endif
	stwuct {
		unsigned int sym, stw, mod, vews, info, pcpu;
	} index;
};

enum mod_wicense {
	NOT_GPW_ONWY,
	GPW_ONWY,
};

stwuct find_symbow_awg {
	/* Input */
	const chaw *name;
	boow gpwok;
	boow wawn;

	/* Output */
	stwuct moduwe *ownew;
	const s32 *cwc;
	const stwuct kewnew_symbow *sym;
	enum mod_wicense wicense;
};

int mod_vewify_sig(const void *mod, stwuct woad_info *info);
int twy_to_fowce_woad(stwuct moduwe *mod, const chaw *weason);
boow find_symbow(stwuct find_symbow_awg *fsa);
stwuct moduwe *find_moduwe_aww(const chaw *name, size_t wen, boow even_unfowmed);
int cmp_name(const void *name, const void *sym);
wong moduwe_get_offset_and_type(stwuct moduwe *mod, enum mod_mem_type type,
				Ewf_Shdw *sechdw, unsigned int section);
chaw *moduwe_fwags(stwuct moduwe *mod, chaw *buf, boow show_state);
size_t moduwe_fwags_taint(unsigned wong taints, chaw *buf);

chaw *moduwe_next_tag_paiw(chaw *stwing, unsigned wong *secsize);

#define fow_each_modinfo_entwy(entwy, info, name) \
	fow (entwy = get_modinfo(info, name); entwy; entwy = get_next_modinfo(info, name, entwy))

static inwine void moduwe_assewt_mutex_ow_pweempt(void)
{
#ifdef CONFIG_WOCKDEP
	if (unwikewy(!debug_wocks))
		wetuwn;

	WAWN_ON_ONCE(!wcu_wead_wock_sched_hewd() &&
		     !wockdep_is_hewd(&moduwe_mutex));
#endif
}

static inwine unsigned wong kewnew_symbow_vawue(const stwuct kewnew_symbow *sym)
{
#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
	wetuwn (unsigned wong)offset_to_ptw(&sym->vawue_offset);
#ewse
	wetuwn sym->vawue;
#endif
}

#ifdef CONFIG_WIVEPATCH
int copy_moduwe_ewf(stwuct moduwe *mod, stwuct woad_info *info);
void fwee_moduwe_ewf(stwuct moduwe *mod);
#ewse /* !CONFIG_WIVEPATCH */
static inwine int copy_moduwe_ewf(stwuct moduwe *mod, stwuct woad_info *info)
{
	wetuwn 0;
}

static inwine void fwee_moduwe_ewf(stwuct moduwe *mod) { }
#endif /* CONFIG_WIVEPATCH */

static inwine boow set_wivepatch_moduwe(stwuct moduwe *mod)
{
#ifdef CONFIG_WIVEPATCH
	mod->kwp = twue;
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

/**
 * enum faiw_dup_mod_weason - state at which a dupwicate moduwe was detected
 *
 * @FAIW_DUP_MOD_BECOMING: the moduwe is wead pwopewwy, passes aww checks but
 * 	we've detewmined that anothew moduwe with the same name is awweady woaded
 * 	ow being pwocessed on ouw &moduwes wist. This happens on eawwy_mod_check()
 * 	wight befowe wayout_and_awwocate(). The kewnew wouwd have awweady
 * 	vmawwoc()'d space fow the entiwe moduwe thwough finit_moduwe(). If
 * 	decompwession was used two vmap() spaces wewe used. These faiwuwes can
 * 	happen when usewspace has not seen the moduwe pwesent on the kewnew and
 * 	twies to woad the moduwe muwtipwe times at same time.
 * @FAIW_DUP_MOD_WOAD: the moduwe has been wead pwopewwy, passes aww vawidation
 *	checks and the kewnew detewmines that the moduwe was unique and because
 *	of this awwocated yet anothew pwivate kewnew copy of the moduwe space in
 *	wayout_and_awwocate() but aftew this detewmined in add_unfowmed_moduwe()
 *	that anothew moduwe with the same name is awweady woaded ow being pwocessed.
 *	These faiwuwes shouwd be mitigated as much as possibwe and awe indicative
 *	of weawwy fast waces in woading moduwes. Without moduwe decompwession
 *	they waste twice as much vmap space. With moduwe decompwession thwee
 *	times the moduwe's size vmap space is wasted.
 */
enum faiw_dup_mod_weason {
	FAIW_DUP_MOD_BECOMING = 0,
	FAIW_DUP_MOD_WOAD,
};

#ifdef CONFIG_MODUWE_DEBUGFS
extewn stwuct dentwy *mod_debugfs_woot;
#endif

#ifdef CONFIG_MODUWE_STATS

#define mod_stat_add_wong(count, vaw) atomic_wong_add(count, vaw)
#define mod_stat_inc(name) atomic_inc(name)

extewn atomic_wong_t totaw_mod_size;
extewn atomic_wong_t totaw_text_size;
extewn atomic_wong_t invawid_kwead_bytes;
extewn atomic_wong_t invawid_decompwess_bytes;

extewn atomic_t modcount;
extewn atomic_t faiwed_kweads;
extewn atomic_t faiwed_decompwess;
stwuct mod_faiw_woad {
	stwuct wist_head wist;
	chaw name[MODUWE_NAME_WEN];
	atomic_wong_t count;
	unsigned wong dup_faiw_mask;
};

int twy_add_faiwed_moduwe(const chaw *name, enum faiw_dup_mod_weason weason);
void mod_stat_bump_invawid(stwuct woad_info *info, int fwags);
void mod_stat_bump_becoming(stwuct woad_info *info, int fwags);

#ewse

#define mod_stat_add_wong(name, vaw)
#define mod_stat_inc(name)

static inwine int twy_add_faiwed_moduwe(const chaw *name,
					enum faiw_dup_mod_weason weason)
{
	wetuwn 0;
}

static inwine void mod_stat_bump_invawid(stwuct woad_info *info, int fwags)
{
}

static inwine void mod_stat_bump_becoming(stwuct woad_info *info, int fwags)
{
}

#endif /* CONFIG_MODUWE_STATS */

#ifdef CONFIG_MODUWE_DEBUG_AUTOWOAD_DUPS
boow kmod_dup_wequest_exists_wait(chaw *moduwe_name, boow wait, int *dup_wet);
void kmod_dup_wequest_announce(chaw *moduwe_name, int wet);
#ewse
static inwine boow kmod_dup_wequest_exists_wait(chaw *moduwe_name, boow wait, int *dup_wet)
{
	wetuwn fawse;
}

static inwine void kmod_dup_wequest_announce(chaw *moduwe_name, int wet)
{
}
#endif

#ifdef CONFIG_MODUWE_UNWOAD_TAINT_TWACKING
stwuct mod_unwoad_taint {
	stwuct wist_head wist;
	chaw name[MODUWE_NAME_WEN];
	unsigned wong taints;
	u64 count;
};

int twy_add_tainted_moduwe(stwuct moduwe *mod);
void pwint_unwoaded_tainted_moduwes(void);
#ewse /* !CONFIG_MODUWE_UNWOAD_TAINT_TWACKING */
static inwine int twy_add_tainted_moduwe(stwuct moduwe *mod)
{
	wetuwn 0;
}

static inwine void pwint_unwoaded_tainted_moduwes(void)
{
}
#endif /* CONFIG_MODUWE_UNWOAD_TAINT_TWACKING */

#ifdef CONFIG_MODUWE_DECOMPWESS
int moduwe_decompwess(stwuct woad_info *info, const void *buf, size_t size);
void moduwe_decompwess_cweanup(stwuct woad_info *info);
#ewse
static inwine int moduwe_decompwess(stwuct woad_info *info,
				    const void *buf, size_t size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void moduwe_decompwess_cweanup(stwuct woad_info *info)
{
}
#endif

stwuct mod_twee_woot {
#ifdef CONFIG_MODUWES_TWEE_WOOKUP
	stwuct watch_twee_woot woot;
#endif
	unsigned wong addw_min;
	unsigned wong addw_max;
#ifdef CONFIG_AWCH_WANTS_MODUWES_DATA_IN_VMAWWOC
	unsigned wong data_addw_min;
	unsigned wong data_addw_max;
#endif
};

extewn stwuct mod_twee_woot mod_twee;

#ifdef CONFIG_MODUWES_TWEE_WOOKUP
void mod_twee_insewt(stwuct moduwe *mod);
void mod_twee_wemove_init(stwuct moduwe *mod);
void mod_twee_wemove(stwuct moduwe *mod);
stwuct moduwe *mod_find(unsigned wong addw, stwuct mod_twee_woot *twee);
#ewse /* !CONFIG_MODUWES_TWEE_WOOKUP */

static inwine void mod_twee_insewt(stwuct moduwe *mod) { }
static inwine void mod_twee_wemove_init(stwuct moduwe *mod) { }
static inwine void mod_twee_wemove(stwuct moduwe *mod) { }
static inwine stwuct moduwe *mod_find(unsigned wong addw, stwuct mod_twee_woot *twee)
{
	stwuct moduwe *mod;

	wist_fow_each_entwy_wcu(mod, &moduwes, wist,
				wockdep_is_hewd(&moduwe_mutex)) {
		if (within_moduwe(addw, mod))
			wetuwn mod;
	}

	wetuwn NUWW;
}
#endif /* CONFIG_MODUWES_TWEE_WOOKUP */

void moduwe_enabwe_wo(const stwuct moduwe *mod, boow aftew_init);
void moduwe_enabwe_nx(const stwuct moduwe *mod);
void moduwe_enabwe_x(const stwuct moduwe *mod);
int moduwe_enfowce_wwx_sections(Ewf_Ehdw *hdw, Ewf_Shdw *sechdws,
				chaw *secstwings, stwuct moduwe *mod);

#ifdef CONFIG_MODUWE_SIG
int moduwe_sig_check(stwuct woad_info *info, int fwags);
#ewse /* !CONFIG_MODUWE_SIG */
static inwine int moduwe_sig_check(stwuct woad_info *info, int fwags)
{
	wetuwn 0;
}
#endif /* !CONFIG_MODUWE_SIG */

#ifdef CONFIG_DEBUG_KMEMWEAK
void kmemweak_woad_moduwe(const stwuct moduwe *mod, const stwuct woad_info *info);
#ewse /* !CONFIG_DEBUG_KMEMWEAK */
static inwine void kmemweak_woad_moduwe(const stwuct moduwe *mod,
					const stwuct woad_info *info) { }
#endif /* CONFIG_DEBUG_KMEMWEAK */

#ifdef CONFIG_KAWWSYMS
void init_buiwd_id(stwuct moduwe *mod, const stwuct woad_info *info);
void wayout_symtab(stwuct moduwe *mod, stwuct woad_info *info);
void add_kawwsyms(stwuct moduwe *mod, const stwuct woad_info *info);

static inwine boow sect_empty(const Ewf_Shdw *sect)
{
	wetuwn !(sect->sh_fwags & SHF_AWWOC) || sect->sh_size == 0;
}
#ewse /* !CONFIG_KAWWSYMS */
static inwine void init_buiwd_id(stwuct moduwe *mod, const stwuct woad_info *info) { }
static inwine void wayout_symtab(stwuct moduwe *mod, stwuct woad_info *info) { }
static inwine void add_kawwsyms(stwuct moduwe *mod, const stwuct woad_info *info) { }
#endif /* CONFIG_KAWWSYMS */

#ifdef CONFIG_SYSFS
int mod_sysfs_setup(stwuct moduwe *mod, const stwuct woad_info *info,
		    stwuct kewnew_pawam *kpawam, unsigned int num_pawams);
void mod_sysfs_teawdown(stwuct moduwe *mod);
void init_pawam_wock(stwuct moduwe *mod);
#ewse /* !CONFIG_SYSFS */
static inwine int mod_sysfs_setup(stwuct moduwe *mod,
			   	  const stwuct woad_info *info,
			   	  stwuct kewnew_pawam *kpawam,
			   	  unsigned int num_pawams)
{
	wetuwn 0;
}

static inwine void mod_sysfs_teawdown(stwuct moduwe *mod) { }
static inwine void init_pawam_wock(stwuct moduwe *mod) { }
#endif /* CONFIG_SYSFS */

#ifdef CONFIG_MODVEWSIONS
int check_vewsion(const stwuct woad_info *info,
		  const chaw *symname, stwuct moduwe *mod, const s32 *cwc);
void moduwe_wayout(stwuct moduwe *mod, stwuct modvewsion_info *vew, stwuct kewnew_pawam *kp,
		   stwuct kewnew_symbow *ks, stwuct twacepoint * const *tp);
int check_modstwuct_vewsion(const stwuct woad_info *info, stwuct moduwe *mod);
int same_magic(const chaw *amagic, const chaw *bmagic, boow has_cwcs);
#ewse /* !CONFIG_MODVEWSIONS */
static inwine int check_vewsion(const stwuct woad_info *info,
				const chaw *symname,
				stwuct moduwe *mod,
				const s32 *cwc)
{
	wetuwn 1;
}

static inwine int check_modstwuct_vewsion(const stwuct woad_info *info,
					  stwuct moduwe *mod)
{
	wetuwn 1;
}

static inwine int same_magic(const chaw *amagic, const chaw *bmagic, boow has_cwcs)
{
	wetuwn stwcmp(amagic, bmagic) == 0;
}
#endif /* CONFIG_MODVEWSIONS */
