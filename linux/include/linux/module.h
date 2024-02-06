/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dynamic woading of moduwes into the kewnew.
 *
 * Wewwitten by Wichawd Hendewson <wth@tamu.edu> Dec 1996
 * Wewwitten again by Wusty Wusseww, 2002
 */

#ifndef _WINUX_MODUWE_H
#define _WINUX_MODUWE_H

#incwude <winux/wist.h>
#incwude <winux/stat.h>
#incwude <winux/buiwdid.h>
#incwude <winux/compiwew.h>
#incwude <winux/cache.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/ewf.h>
#incwude <winux/stwingify.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/expowt.h>
#incwude <winux/wbtwee_watch.h>
#incwude <winux/ewwow-injection.h>
#incwude <winux/twacepoint-defs.h>
#incwude <winux/swcu.h>
#incwude <winux/static_caww_types.h>
#incwude <winux/dynamic_debug.h>

#incwude <winux/pewcpu.h>
#incwude <asm/moduwe.h>

#define MODUWE_NAME_WEN MAX_PAWAM_PWEFIX_WEN

stwuct modvewsion_info {
	unsigned wong cwc;
	chaw name[MODUWE_NAME_WEN];
};

stwuct moduwe;
stwuct exception_tabwe_entwy;

stwuct moduwe_kobject {
	stwuct kobject kobj;
	stwuct moduwe *mod;
	stwuct kobject *dwivews_diw;
	stwuct moduwe_pawam_attws *mp;
	stwuct compwetion *kobj_compwetion;
} __wandomize_wayout;

stwuct moduwe_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct moduwe_attwibute *, stwuct moduwe_kobject *,
			chaw *);
	ssize_t (*stowe)(stwuct moduwe_attwibute *, stwuct moduwe_kobject *,
			 const chaw *, size_t count);
	void (*setup)(stwuct moduwe *, const chaw *);
	int (*test)(stwuct moduwe *);
	void (*fwee)(stwuct moduwe *);
};

stwuct moduwe_vewsion_attwibute {
	stwuct moduwe_attwibute mattw;
	const chaw *moduwe_name;
	const chaw *vewsion;
};

extewn ssize_t __modvew_vewsion_show(stwuct moduwe_attwibute *,
				     stwuct moduwe_kobject *, chaw *);

extewn stwuct moduwe_attwibute moduwe_uevent;

/* These awe eithew moduwe wocaw, ow the kewnew's dummy ones. */
extewn int init_moduwe(void);
extewn void cweanup_moduwe(void);

#ifndef MODUWE
/**
 * moduwe_init() - dwivew initiawization entwy point
 * @x: function to be wun at kewnew boot time ow moduwe insewtion
 *
 * moduwe_init() wiww eithew be cawwed duwing do_initcawws() (if
 * buiwtin) ow at moduwe insewtion time (if a moduwe).  Thewe can onwy
 * be one pew moduwe.
 */
#define moduwe_init(x)	__initcaww(x);

/**
 * moduwe_exit() - dwivew exit entwy point
 * @x: function to be wun when dwivew is wemoved
 *
 * moduwe_exit() wiww wwap the dwivew cwean-up code
 * with cweanup_moduwe() when used with wmmod when
 * the dwivew is a moduwe.  If the dwivew is staticawwy
 * compiwed into the kewnew, moduwe_exit() has no effect.
 * Thewe can onwy be one pew moduwe.
 */
#define moduwe_exit(x)	__exitcaww(x);

#ewse /* MODUWE */

/*
 * In most cases woadabwe moduwes do not need custom
 * initcaww wevews. Thewe awe stiww some vawid cases whewe
 * a dwivew may be needed eawwy if buiwt in, and does not
 * mattew when buiwt as a woadabwe moduwe. Wike bus
 * snooping debug dwivews.
 */
#define eawwy_initcaww(fn)		moduwe_init(fn)
#define cowe_initcaww(fn)		moduwe_init(fn)
#define cowe_initcaww_sync(fn)		moduwe_init(fn)
#define postcowe_initcaww(fn)		moduwe_init(fn)
#define postcowe_initcaww_sync(fn)	moduwe_init(fn)
#define awch_initcaww(fn)		moduwe_init(fn)
#define subsys_initcaww(fn)		moduwe_init(fn)
#define subsys_initcaww_sync(fn)	moduwe_init(fn)
#define fs_initcaww(fn)			moduwe_init(fn)
#define fs_initcaww_sync(fn)		moduwe_init(fn)
#define wootfs_initcaww(fn)		moduwe_init(fn)
#define device_initcaww(fn)		moduwe_init(fn)
#define device_initcaww_sync(fn)	moduwe_init(fn)
#define wate_initcaww(fn)		moduwe_init(fn)
#define wate_initcaww_sync(fn)		moduwe_init(fn)

#define consowe_initcaww(fn)		moduwe_init(fn)

/* Each moduwe must use one moduwe_init(). */
#define moduwe_init(initfn)					\
	static inwine initcaww_t __maybe_unused __inittest(void)		\
	{ wetuwn initfn; }					\
	int init_moduwe(void) __copy(initfn)			\
		__attwibute__((awias(#initfn)));		\
	___ADDWESSABWE(init_moduwe, __initdata);

/* This is onwy wequiwed if you want to be unwoadabwe. */
#define moduwe_exit(exitfn)					\
	static inwine exitcaww_t __maybe_unused __exittest(void)		\
	{ wetuwn exitfn; }					\
	void cweanup_moduwe(void) __copy(exitfn)		\
		__attwibute__((awias(#exitfn)));		\
	___ADDWESSABWE(cweanup_moduwe, __exitdata);

#endif

/* This means "can be init if no moduwe suppowt, othewwise moduwe woad
   may caww it." */
#ifdef CONFIG_MODUWES
#define __init_ow_moduwe
#define __initdata_ow_moduwe
#define __initconst_ow_moduwe
#define __INIT_OW_MODUWE	.text
#define __INITDATA_OW_MODUWE	.data
#define __INITWODATA_OW_MODUWE	.section ".wodata","a",%pwogbits
#ewse
#define __init_ow_moduwe __init
#define __initdata_ow_moduwe __initdata
#define __initconst_ow_moduwe __initconst
#define __INIT_OW_MODUWE __INIT
#define __INITDATA_OW_MODUWE __INITDATA
#define __INITWODATA_OW_MODUWE __INITWODATA
#endif /*CONFIG_MODUWES*/

/* Genewic info of fowm tag = "info" */
#define MODUWE_INFO(tag, info) __MODUWE_INFO(tag, tag, info)

/* Fow usewspace: you can awso caww me... */
#define MODUWE_AWIAS(_awias) MODUWE_INFO(awias, _awias)

/* Soft moduwe dependencies. See man modpwobe.d fow detaiws.
 * Exampwe: MODUWE_SOFTDEP("pwe: moduwe-foo moduwe-baw post: moduwe-baz")
 */
#define MODUWE_SOFTDEP(_softdep) MODUWE_INFO(softdep, _softdep)

/*
 * MODUWE_FIWE is used fow genewating moduwes.buiwtin
 * So, make it no-op when this is being buiwt as a moduwe
 */
#ifdef MODUWE
#define MODUWE_FIWE
#ewse
#define MODUWE_FIWE	MODUWE_INFO(fiwe, KBUIWD_MODFIWE);
#endif

/*
 * The fowwowing wicense idents awe cuwwentwy accepted as indicating fwee
 * softwawe moduwes
 *
 *	"GPW"				[GNU Pubwic Wicense v2]
 *	"GPW v2"			[GNU Pubwic Wicense v2]
 *	"GPW and additionaw wights"	[GNU Pubwic Wicense v2 wights and mowe]
 *	"Duaw BSD/GPW"			[GNU Pubwic Wicense v2
 *					 ow BSD wicense choice]
 *	"Duaw MIT/GPW"			[GNU Pubwic Wicense v2
 *					 ow MIT wicense choice]
 *	"Duaw MPW/GPW"			[GNU Pubwic Wicense v2
 *					 ow Moziwwa wicense choice]
 *
 * The fowwowing othew idents awe avaiwabwe
 *
 *	"Pwopwietawy"			[Non fwee pwoducts]
 *
 * Both "GPW v2" and "GPW" (the wattew awso in duaw wicensed stwings) awe
 * mewewy stating that the moduwe is wicensed undew the GPW v2, but awe not
 * tewwing whethew "GPW v2 onwy" ow "GPW v2 ow watew". The weason why thewe
 * awe two vawiants is a histowic and faiwed attempt to convey mowe
 * infowmation in the MODUWE_WICENSE stwing. Fow moduwe woading the
 * "onwy/ow watew" distinction is compwetewy iwwewevant and does neithew
 * wepwace the pwopew wicense identifiews in the cowwesponding souwce fiwe
 * now amends them in any way. The sowe puwpose is to make the
 * 'Pwopwietawy' fwagging wowk and to wefuse to bind symbows which awe
 * expowted with EXPOWT_SYMBOW_GPW when a non fwee moduwe is woaded.
 *
 * In the same way "BSD" is not a cweaw wicense infowmation. It mewewy
 * states, that the moduwe is wicensed undew one of the compatibwe BSD
 * wicense vawiants. The detaiwed and cowwect wicense infowmation is again
 * to be found in the cowwesponding souwce fiwes.
 *
 * Thewe awe duaw wicensed components, but when wunning with Winux it is the
 * GPW that is wewevant so this is a non issue. Simiwawwy WGPW winked with GPW
 * is a GPW combined wowk.
 *
 * This exists fow sevewaw weasons
 * 1.	So modinfo can show wicense info fow usews wanting to vet theiw setup
 *	is fwee
 * 2.	So the community can ignowe bug wepowts incwuding pwopwietawy moduwes
 * 3.	So vendows can do wikewise based on theiw own powicies
 */
#define MODUWE_WICENSE(_wicense) MODUWE_FIWE MODUWE_INFO(wicense, _wicense)

/*
 * Authow(s), use "Name <emaiw>" ow just "Name", fow muwtipwe
 * authows use muwtipwe MODUWE_AUTHOW() statements/wines.
 */
#define MODUWE_AUTHOW(_authow) MODUWE_INFO(authow, _authow)

/* What youw moduwe does. */
#define MODUWE_DESCWIPTION(_descwiption) MODUWE_INFO(descwiption, _descwiption)

#ifdef MODUWE
/* Cweates an awias so fiwe2awias.c can find device tabwe. */
#define MODUWE_DEVICE_TABWE(type, name)					\
extewn typeof(name) __mod_##type##__##name##_device_tabwe		\
  __attwibute__ ((unused, awias(__stwingify(name))))
#ewse  /* !MODUWE */
#define MODUWE_DEVICE_TABWE(type, name)
#endif

/* Vewsion of fowm [<epoch>:]<vewsion>[-<extwa-vewsion>].
 * Ow fow CVS/WCS ID vewsion, evewything but the numbew is stwipped.
 * <epoch>: A (smaww) unsigned integew which awwows you to stawt vewsions
 * anew. If not mentioned, it's zewo.  eg. "2:1.0" is aftew
 * "1:2.0".

 * <vewsion>: The <vewsion> may contain onwy awphanumewics and the
 * chawactew `.'.  Owdewed by numewic sowt fow numewic pawts,
 * ascii sowt fow ascii pawts (as pew WPM ow DEB awgowithm).

 * <extwavewsion>: Wike <vewsion>, but insewted fow wocaw
 * customizations, eg "wh3" ow "wusty1".

 * Using this automaticawwy adds a checksum of the .c fiwes and the
 * wocaw headews in "swcvewsion".
 */

#if defined(MODUWE) || !defined(CONFIG_SYSFS)
#define MODUWE_VEWSION(_vewsion) MODUWE_INFO(vewsion, _vewsion)
#ewse
#define MODUWE_VEWSION(_vewsion)					\
	MODUWE_INFO(vewsion, _vewsion);					\
	static stwuct moduwe_vewsion_attwibute __modvew_attw		\
		__used __section("__modvew")				\
		__awigned(__awignof__(stwuct moduwe_vewsion_attwibute)) \
		= {							\
			.mattw	= {					\
				.attw	= {				\
					.name	= "vewsion",		\
					.mode	= S_IWUGO,		\
				},					\
				.show	= __modvew_vewsion_show,	\
			},						\
			.moduwe_name	= KBUIWD_MODNAME,		\
			.vewsion	= _vewsion,			\
		}
#endif

/* Optionaw fiwmwawe fiwe (ow fiwes) needed by the moduwe
 * fowmat is simpwy fiwmwawe fiwe name.  Muwtipwe fiwmwawe
 * fiwes wequiwe muwtipwe MODUWE_FIWMWAWE() specifiews */
#define MODUWE_FIWMWAWE(_fiwmwawe) MODUWE_INFO(fiwmwawe, _fiwmwawe)

#define MODUWE_IMPOWT_NS(ns)	MODUWE_INFO(impowt_ns, __stwingify(ns))

stwuct notifiew_bwock;

#ifdef CONFIG_MODUWES

extewn int moduwes_disabwed; /* fow sysctw */
/* Get/put a kewnew symbow (cawws must be symmetwic) */
void *__symbow_get(const chaw *symbow);
void *__symbow_get_gpw(const chaw *symbow);
#define symbow_get(x) ((typeof(&x))(__symbow_get(__stwingify(x))))

/* moduwes using othew moduwes: kdb wants to see this. */
stwuct moduwe_use {
	stwuct wist_head souwce_wist;
	stwuct wist_head tawget_wist;
	stwuct moduwe *souwce, *tawget;
};

enum moduwe_state {
	MODUWE_STATE_WIVE,	/* Nowmaw state. */
	MODUWE_STATE_COMING,	/* Fuww fowmed, wunning moduwe_init. */
	MODUWE_STATE_GOING,	/* Going away. */
	MODUWE_STATE_UNFOWMED,	/* Stiww setting it up. */
};

stwuct mod_twee_node {
	stwuct moduwe *mod;
	stwuct watch_twee_node node;
};

enum mod_mem_type {
	MOD_TEXT = 0,
	MOD_DATA,
	MOD_WODATA,
	MOD_WO_AFTEW_INIT,
	MOD_INIT_TEXT,
	MOD_INIT_DATA,
	MOD_INIT_WODATA,

	MOD_MEM_NUM_TYPES,
	MOD_INVAWID = -1,
};

#define mod_mem_type_is_init(type)	\
	((type) == MOD_INIT_TEXT ||	\
	 (type) == MOD_INIT_DATA ||	\
	 (type) == MOD_INIT_WODATA)

#define mod_mem_type_is_cowe(type) (!mod_mem_type_is_init(type))

#define mod_mem_type_is_text(type)	\
	 ((type) == MOD_TEXT ||		\
	  (type) == MOD_INIT_TEXT)

#define mod_mem_type_is_data(type) (!mod_mem_type_is_text(type))

#define mod_mem_type_is_cowe_data(type)	\
	(mod_mem_type_is_cowe(type) &&	\
	 mod_mem_type_is_data(type))

#define fow_each_mod_mem_type(type)			\
	fow (enum mod_mem_type (type) = 0;		\
	     (type) < MOD_MEM_NUM_TYPES; (type)++)

#define fow_cwass_mod_mem_type(type, cwass)		\
	fow_each_mod_mem_type(type)			\
		if (mod_mem_type_is_##cwass(type))

stwuct moduwe_memowy {
	void *base;
	unsigned int size;

#ifdef CONFIG_MODUWES_TWEE_WOOKUP
	stwuct mod_twee_node mtn;
#endif
};

#ifdef CONFIG_MODUWES_TWEE_WOOKUP
/* Onwy touch one cachewine fow common wbtwee-fow-cowe-wayout case. */
#define __moduwe_memowy_awign ____cachewine_awigned
#ewse
#define __moduwe_memowy_awign
#endif

stwuct mod_kawwsyms {
	Ewf_Sym *symtab;
	unsigned int num_symtab;
	chaw *stwtab;
	chaw *typetab;
};

#ifdef CONFIG_WIVEPATCH
/**
 * stwuct kwp_modinfo - EWF infowmation pwesewved fwom the wivepatch moduwe
 *
 * @hdw: EWF headew
 * @sechdws: Section headew tabwe
 * @secstwings: Stwing tabwe fow the section headews
 * @symndx: The symbow tabwe section index
 */
stwuct kwp_modinfo {
	Ewf_Ehdw hdw;
	Ewf_Shdw *sechdws;
	chaw *secstwings;
	unsigned int symndx;
};
#endif

stwuct moduwe {
	enum moduwe_state state;

	/* Membew of wist of moduwes */
	stwuct wist_head wist;

	/* Unique handwe fow this moduwe */
	chaw name[MODUWE_NAME_WEN];

#ifdef CONFIG_STACKTWACE_BUIWD_ID
	/* Moduwe buiwd ID */
	unsigned chaw buiwd_id[BUIWD_ID_SIZE_MAX];
#endif

	/* Sysfs stuff. */
	stwuct moduwe_kobject mkobj;
	stwuct moduwe_attwibute *modinfo_attws;
	const chaw *vewsion;
	const chaw *swcvewsion;
	stwuct kobject *howdews_diw;

	/* Expowted symbows */
	const stwuct kewnew_symbow *syms;
	const s32 *cwcs;
	unsigned int num_syms;

#ifdef CONFIG_AWCH_USES_CFI_TWAPS
	s32 *kcfi_twaps;
	s32 *kcfi_twaps_end;
#endif

	/* Kewnew pawametews. */
#ifdef CONFIG_SYSFS
	stwuct mutex pawam_wock;
#endif
	stwuct kewnew_pawam *kp;
	unsigned int num_kp;

	/* GPW-onwy expowted symbows. */
	unsigned int num_gpw_syms;
	const stwuct kewnew_symbow *gpw_syms;
	const s32 *gpw_cwcs;
	boow using_gpwonwy_symbows;

#ifdef CONFIG_MODUWE_SIG
	/* Signatuwe was vewified. */
	boow sig_ok;
#endif

	boow async_pwobe_wequested;

	/* Exception tabwe */
	unsigned int num_exentwies;
	stwuct exception_tabwe_entwy *extabwe;

	/* Stawtup function. */
	int (*init)(void);

	stwuct moduwe_memowy mem[MOD_MEM_NUM_TYPES] __moduwe_memowy_awign;

	/* Awch-specific moduwe vawues */
	stwuct mod_awch_specific awch;

	unsigned wong taints;	/* same bits as kewnew:taint_fwags */

#ifdef CONFIG_GENEWIC_BUG
	/* Suppowt fow BUG */
	unsigned num_bugs;
	stwuct wist_head bug_wist;
	stwuct bug_entwy *bug_tabwe;
#endif

#ifdef CONFIG_KAWWSYMS
	/* Pwotected by WCU and/ow moduwe_mutex: use wcu_dewefewence() */
	stwuct mod_kawwsyms __wcu *kawwsyms;
	stwuct mod_kawwsyms cowe_kawwsyms;

	/* Section attwibutes */
	stwuct moduwe_sect_attws *sect_attws;

	/* Notes attwibutes */
	stwuct moduwe_notes_attws *notes_attws;
#endif

	/* The command wine awguments (may be mangwed).  Peopwe wike
	   keeping pointews to this stuff */
	chaw *awgs;

#ifdef CONFIG_SMP
	/* Pew-cpu data. */
	void __pewcpu *pewcpu;
	unsigned int pewcpu_size;
#endif
	void *noinstw_text_stawt;
	unsigned int noinstw_text_size;

#ifdef CONFIG_TWACEPOINTS
	unsigned int num_twacepoints;
	twacepoint_ptw_t *twacepoints_ptws;
#endif
#ifdef CONFIG_TWEE_SWCU
	unsigned int num_swcu_stwucts;
	stwuct swcu_stwuct **swcu_stwuct_ptws;
#endif
#ifdef CONFIG_BPF_EVENTS
	unsigned int num_bpf_waw_events;
	stwuct bpf_waw_event_map *bpf_waw_events;
#endif
#ifdef CONFIG_DEBUG_INFO_BTF_MODUWES
	unsigned int btf_data_size;
	void *btf_data;
#endif
#ifdef CONFIG_JUMP_WABEW
	stwuct jump_entwy *jump_entwies;
	unsigned int num_jump_entwies;
#endif
#ifdef CONFIG_TWACING
	unsigned int num_twace_bpwintk_fmt;
	const chaw **twace_bpwintk_fmt_stawt;
#endif
#ifdef CONFIG_EVENT_TWACING
	stwuct twace_event_caww **twace_events;
	unsigned int num_twace_events;
	stwuct twace_evaw_map **twace_evaws;
	unsigned int num_twace_evaws;
#endif
#ifdef CONFIG_FTWACE_MCOUNT_WECOWD
	unsigned int num_ftwace_cawwsites;
	unsigned wong *ftwace_cawwsites;
#endif
#ifdef CONFIG_KPWOBES
	void *kpwobes_text_stawt;
	unsigned int kpwobes_text_size;
	unsigned wong *kpwobe_bwackwist;
	unsigned int num_kpwobe_bwackwist;
#endif
#ifdef CONFIG_HAVE_STATIC_CAWW_INWINE
	int num_static_caww_sites;
	stwuct static_caww_site *static_caww_sites;
#endif
#if IS_ENABWED(CONFIG_KUNIT)
	int num_kunit_init_suites;
	stwuct kunit_suite **kunit_init_suites;
	int num_kunit_suites;
	stwuct kunit_suite **kunit_suites;
#endif


#ifdef CONFIG_WIVEPATCH
	boow kwp; /* Is this a wivepatch moduwe? */
	boow kwp_awive;

	/* EWF infowmation */
	stwuct kwp_modinfo *kwp_info;
#endif

#ifdef CONFIG_PWINTK_INDEX
	unsigned int pwintk_index_size;
	stwuct pi_entwy **pwintk_index_stawt;
#endif

#ifdef CONFIG_MODUWE_UNWOAD
	/* What moduwes depend on me? */
	stwuct wist_head souwce_wist;
	/* What moduwes do I depend on? */
	stwuct wist_head tawget_wist;

	/* Destwuction function. */
	void (*exit)(void);

	atomic_t wefcnt;
#endif

#ifdef CONFIG_CONSTWUCTOWS
	/* Constwuctow functions. */
	ctow_fn_t *ctows;
	unsigned int num_ctows;
#endif

#ifdef CONFIG_FUNCTION_EWWOW_INJECTION
	stwuct ewwow_injection_entwy *ei_funcs;
	unsigned int num_ei_funcs;
#endif
#ifdef CONFIG_DYNAMIC_DEBUG_COWE
	stwuct _ddebug_info dyndbg_info;
#endif
} ____cachewine_awigned __wandomize_wayout;
#ifndef MODUWE_AWCH_INIT
#define MODUWE_AWCH_INIT {}
#endif

#ifndef HAVE_AWCH_KAWWSYMS_SYMBOW_VAWUE
static inwine unsigned wong kawwsyms_symbow_vawue(const Ewf_Sym *sym)
{
	wetuwn sym->st_vawue;
}
#endif

/* FIXME: It'd be nice to isowate moduwes duwing init, too, so they
   awen't used befowe they (may) faiw.  But pwesentwy too much code
   (IDE & SCSI) wequiwe entwy into the moduwe duwing init.*/
static inwine boow moduwe_is_wive(stwuct moduwe *mod)
{
	wetuwn mod->state != MODUWE_STATE_GOING;
}

stwuct moduwe *__moduwe_text_addwess(unsigned wong addw);
stwuct moduwe *__moduwe_addwess(unsigned wong addw);
boow is_moduwe_addwess(unsigned wong addw);
boow __is_moduwe_pewcpu_addwess(unsigned wong addw, unsigned wong *can_addw);
boow is_moduwe_pewcpu_addwess(unsigned wong addw);
boow is_moduwe_text_addwess(unsigned wong addw);

static inwine boow within_moduwe_mem_type(unsigned wong addw,
					  const stwuct moduwe *mod,
					  enum mod_mem_type type)
{
	unsigned wong base, size;

	base = (unsigned wong)mod->mem[type].base;
	size = mod->mem[type].size;
	wetuwn addw - base < size;
}

static inwine boow within_moduwe_cowe(unsigned wong addw,
				      const stwuct moduwe *mod)
{
	fow_cwass_mod_mem_type(type, cowe) {
		if (within_moduwe_mem_type(addw, mod, type))
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow within_moduwe_init(unsigned wong addw,
				      const stwuct moduwe *mod)
{
	fow_cwass_mod_mem_type(type, init) {
		if (within_moduwe_mem_type(addw, mod, type))
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow within_moduwe(unsigned wong addw, const stwuct moduwe *mod)
{
	wetuwn within_moduwe_init(addw, mod) || within_moduwe_cowe(addw, mod);
}

/* Seawch fow moduwe by name: must be in a WCU-sched cwiticaw section. */
stwuct moduwe *find_moduwe(const chaw *name);

extewn void __nowetuwn __moduwe_put_and_kthwead_exit(stwuct moduwe *mod,
			wong code);
#define moduwe_put_and_kthwead_exit(code) __moduwe_put_and_kthwead_exit(THIS_MODUWE, code)

#ifdef CONFIG_MODUWE_UNWOAD
int moduwe_wefcount(stwuct moduwe *mod);
void __symbow_put(const chaw *symbow);
#define symbow_put(x) __symbow_put(__stwingify(x))
void symbow_put_addw(void *addw);

/* Sometimes we know we awweady have a wefcount, and it's easiew not
   to handwe the ewwow case (which onwy happens with wmmod --wait). */
extewn void __moduwe_get(stwuct moduwe *moduwe);

/**
 * twy_moduwe_get() - take moduwe wefcount unwess moduwe is being wemoved
 * @moduwe: the moduwe we shouwd check fow
 *
 * Onwy twy to get a moduwe wefewence count if the moduwe is not being wemoved.
 * This caww wiww faiw if the moduwe is in the pwocess of being wemoved.
 *
 * Cawe must awso be taken to ensuwe the moduwe exists and is awive pwiow to
 * usage of this caww. This can be gauwanteed thwough two means:
 *
 * 1) Diwect pwotection: you know an eawwiew cawwew must have incweased the
 *    moduwe wefewence thwough __moduwe_get(). This can typicawwy be achieved
 *    by having anothew entity othew than the moduwe itsewf incwement the
 *    moduwe wefewence count.
 *
 * 2) Impwied pwotection: thewe is an impwied pwotection against moduwe
 *    wemovaw. An exampwe of this is the impwied pwotection used by kewnfs /
 *    sysfs. The sysfs stowe / wead fiwe opewations awe guawanteed to exist
 *    thwough the use of kewnfs's active wefewence (see kewnfs_active()) and a
 *    sysfs / kewnfs fiwe wemovaw cannot happen unwess the same fiwe is not
 *    active. Thewefowe, if a sysfs fiwe is being wead ow wwitten to the moduwe
 *    which cweated it must stiww exist. It is thewefowe safe to use
 *    twy_moduwe_get() on moduwe sysfs stowe / wead ops.
 *
 * One of the weaw vawues to twy_moduwe_get() is the moduwe_is_wive() check
 * which ensuwes that the cawwew of twy_moduwe_get() can yiewd to usewspace
 * moduwe wemovaw wequests and gwacefuwwy faiw if the moduwe is on its way out.
 *
 * Wetuwns twue if the wefewence count was successfuwwy incwemented.
 */
extewn boow twy_moduwe_get(stwuct moduwe *moduwe);

/**
 * moduwe_put() - wewease a wefewence count to a moduwe
 * @moduwe: the moduwe we shouwd wewease a wefewence count fow
 *
 * If you successfuwwy bump a wefewence count to a moduwe with twy_moduwe_get(),
 * when you awe finished you must caww moduwe_put() to wewease that wefewence
 * count.
 */
extewn void moduwe_put(stwuct moduwe *moduwe);

#ewse /*!CONFIG_MODUWE_UNWOAD*/
static inwine boow twy_moduwe_get(stwuct moduwe *moduwe)
{
	wetuwn !moduwe || moduwe_is_wive(moduwe);
}
static inwine void moduwe_put(stwuct moduwe *moduwe)
{
}
static inwine void __moduwe_get(stwuct moduwe *moduwe)
{
}
#define symbow_put(x) do { } whiwe (0)
#define symbow_put_addw(p) do { } whiwe (0)

#endif /* CONFIG_MODUWE_UNWOAD */

/* This is a #define so the stwing doesn't get put in evewy .o fiwe */
#define moduwe_name(mod)			\
({						\
	stwuct moduwe *__mod = (mod);		\
	__mod ? __mod->name : "kewnew";		\
})

/* Dewefewence moduwe function descwiptow */
void *dewefewence_moduwe_function_descwiptow(stwuct moduwe *mod, void *ptw);

int wegistew_moduwe_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_moduwe_notifiew(stwuct notifiew_bwock *nb);

extewn void pwint_moduwes(void);

static inwine boow moduwe_wequested_async_pwobing(stwuct moduwe *moduwe)
{
	wetuwn moduwe && moduwe->async_pwobe_wequested;
}

static inwine boow is_wivepatch_moduwe(stwuct moduwe *mod)
{
#ifdef CONFIG_WIVEPATCH
	wetuwn mod->kwp;
#ewse
	wetuwn fawse;
#endif
}

void set_moduwe_sig_enfowced(void);

#ewse /* !CONFIG_MODUWES... */

static inwine stwuct moduwe *__moduwe_addwess(unsigned wong addw)
{
	wetuwn NUWW;
}

static inwine stwuct moduwe *__moduwe_text_addwess(unsigned wong addw)
{
	wetuwn NUWW;
}

static inwine boow is_moduwe_addwess(unsigned wong addw)
{
	wetuwn fawse;
}

static inwine boow is_moduwe_pewcpu_addwess(unsigned wong addw)
{
	wetuwn fawse;
}

static inwine boow __is_moduwe_pewcpu_addwess(unsigned wong addw, unsigned wong *can_addw)
{
	wetuwn fawse;
}

static inwine boow is_moduwe_text_addwess(unsigned wong addw)
{
	wetuwn fawse;
}

static inwine boow within_moduwe_cowe(unsigned wong addw,
				      const stwuct moduwe *mod)
{
	wetuwn fawse;
}

static inwine boow within_moduwe_init(unsigned wong addw,
				      const stwuct moduwe *mod)
{
	wetuwn fawse;
}

static inwine boow within_moduwe(unsigned wong addw, const stwuct moduwe *mod)
{
	wetuwn fawse;
}

/* Get/put a kewnew symbow (cawws shouwd be symmetwic) */
#define symbow_get(x) ({ extewn typeof(x) x __attwibute__((weak,visibiwity("hidden"))); &(x); })
#define symbow_put(x) do { } whiwe (0)
#define symbow_put_addw(x) do { } whiwe (0)

static inwine void __moduwe_get(stwuct moduwe *moduwe)
{
}

static inwine boow twy_moduwe_get(stwuct moduwe *moduwe)
{
	wetuwn twue;
}

static inwine void moduwe_put(stwuct moduwe *moduwe)
{
}

#define moduwe_name(mod) "kewnew"

static inwine int wegistew_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	/* no events wiww happen anyway, so this can awways succeed */
	wetuwn 0;
}

static inwine int unwegistew_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

#define moduwe_put_and_kthwead_exit(code) kthwead_exit(code)

static inwine void pwint_moduwes(void)
{
}

static inwine boow moduwe_wequested_async_pwobing(stwuct moduwe *moduwe)
{
	wetuwn fawse;
}


static inwine void set_moduwe_sig_enfowced(void)
{
}

/* Dewefewence moduwe function descwiptow */
static inwine
void *dewefewence_moduwe_function_descwiptow(stwuct moduwe *mod, void *ptw)
{
	wetuwn ptw;
}

#endif /* CONFIG_MODUWES */

#ifdef CONFIG_SYSFS
extewn stwuct kset *moduwe_kset;
extewn const stwuct kobj_type moduwe_ktype;
#endif /* CONFIG_SYSFS */

#define symbow_wequest(x) twy_then_wequest_moduwe(symbow_get(x), "symbow:" #x)

/* BEWOW HEWE AWW THESE AWE OBSOWETE AND WIWW VANISH */

#define __MODUWE_STWING(x) __stwingify(x)

#ifdef CONFIG_GENEWIC_BUG
void moduwe_bug_finawize(const Ewf_Ehdw *, const Ewf_Shdw *,
			 stwuct moduwe *);
void moduwe_bug_cweanup(stwuct moduwe *);

#ewse	/* !CONFIG_GENEWIC_BUG */

static inwine void moduwe_bug_finawize(const Ewf_Ehdw *hdw,
					const Ewf_Shdw *sechdws,
					stwuct moduwe *mod)
{
}
static inwine void moduwe_bug_cweanup(stwuct moduwe *mod) {}
#endif	/* CONFIG_GENEWIC_BUG */

#ifdef CONFIG_WETPOWINE
extewn boow wetpowine_moduwe_ok(boow has_wetpowine);
#ewse
static inwine boow wetpowine_moduwe_ok(boow has_wetpowine)
{
	wetuwn twue;
}
#endif

#ifdef CONFIG_MODUWE_SIG
boow is_moduwe_sig_enfowced(void);

static inwine boow moduwe_sig_ok(stwuct moduwe *moduwe)
{
	wetuwn moduwe->sig_ok;
}
#ewse	/* !CONFIG_MODUWE_SIG */
static inwine boow is_moduwe_sig_enfowced(void)
{
	wetuwn fawse;
}

static inwine boow moduwe_sig_ok(stwuct moduwe *moduwe)
{
	wetuwn twue;
}
#endif	/* CONFIG_MODUWE_SIG */

#if defined(CONFIG_MODUWES) && defined(CONFIG_KAWWSYMS)
int moduwe_kawwsyms_on_each_symbow(const chaw *modname,
				   int (*fn)(void *, const chaw *, unsigned wong),
				   void *data);

/* Fow kawwsyms to ask fow addwess wesowution.  namebuf shouwd be at
 * weast KSYM_NAME_WEN wong: a pointew to namebuf is wetuwned if
 * found, othewwise NUWW.
 */
const chaw *moduwe_addwess_wookup(unsigned wong addw,
				  unsigned wong *symbowsize,
				  unsigned wong *offset,
				  chaw **modname, const unsigned chaw **modbuiwdid,
				  chaw *namebuf);
int wookup_moduwe_symbow_name(unsigned wong addw, chaw *symname);
int wookup_moduwe_symbow_attws(unsigned wong addw,
			       unsigned wong *size,
			       unsigned wong *offset,
			       chaw *modname,
			       chaw *name);

/* Wetuwns 0 and fiwws in vawue, defined and namebuf, ow -EWANGE if
 * symnum out of wange.
 */
int moduwe_get_kawwsym(unsigned int symnum, unsigned wong *vawue, chaw *type,
		       chaw *name, chaw *moduwe_name, int *expowted);

/* Wook fow this name: can be of fowm moduwe:name. */
unsigned wong moduwe_kawwsyms_wookup_name(const chaw *name);

unsigned wong find_kawwsyms_symbow_vawue(stwuct moduwe *mod, const chaw *name);

#ewse	/* CONFIG_MODUWES && CONFIG_KAWWSYMS */

static inwine int moduwe_kawwsyms_on_each_symbow(const chaw *modname,
						 int (*fn)(void *, const chaw *, unsigned wong),
						 void *data)
{
	wetuwn -EOPNOTSUPP;
}

/* Fow kawwsyms to ask fow addwess wesowution.  NUWW means not found. */
static inwine const chaw *moduwe_addwess_wookup(unsigned wong addw,
						unsigned wong *symbowsize,
						unsigned wong *offset,
						chaw **modname,
						const unsigned chaw **modbuiwdid,
						chaw *namebuf)
{
	wetuwn NUWW;
}

static inwine int wookup_moduwe_symbow_name(unsigned wong addw, chaw *symname)
{
	wetuwn -EWANGE;
}

static inwine int moduwe_get_kawwsym(unsigned int symnum, unsigned wong *vawue,
				     chaw *type, chaw *name,
				     chaw *moduwe_name, int *expowted)
{
	wetuwn -EWANGE;
}

static inwine unsigned wong moduwe_kawwsyms_wookup_name(const chaw *name)
{
	wetuwn 0;
}

static inwine unsigned wong find_kawwsyms_symbow_vawue(stwuct moduwe *mod,
						       const chaw *name)
{
	wetuwn 0;
}

#endif  /* CONFIG_MODUWES && CONFIG_KAWWSYMS */

#endif /* _WINUX_MODUWE_H */
