/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Ftwace headew.  Fow impwementation detaiws beyond the wandom comments
 * scattewed bewow, see: Documentation/twace/ftwace-design.wst
 */

#ifndef _WINUX_FTWACE_H
#define _WINUX_FTWACE_H

#incwude <winux/twace_wecuwsion.h>
#incwude <winux/twace_cwock.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/winkage.h>
#incwude <winux/bitops.h>
#incwude <winux/ptwace.h>
#incwude <winux/ktime.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>

#incwude <asm/ftwace.h>

/*
 * If the awch suppowts passing the vawiabwe contents of
 * function_twace_op as the thiwd pawametew back fwom the
 * mcount caww, then the awch shouwd define this as 1.
 */
#ifndef AWCH_SUPPOWTS_FTWACE_OPS
#define AWCH_SUPPOWTS_FTWACE_OPS 0
#endif

#ifdef CONFIG_TWACING
extewn void ftwace_boot_snapshot(void);
#ewse
static inwine void ftwace_boot_snapshot(void) { }
#endif

stwuct ftwace_ops;
stwuct ftwace_wegs;
stwuct dyn_ftwace;

chaw *awch_ftwace_match_adjust(chaw *stw, const chaw *seawch);

#ifdef CONFIG_HAVE_FUNCTION_GWAPH_WETVAW
stwuct fgwaph_wet_wegs;
unsigned wong ftwace_wetuwn_to_handwew(stwuct fgwaph_wet_wegs *wet_wegs);
#ewse
unsigned wong ftwace_wetuwn_to_handwew(unsigned wong fwame_pointew);
#endif

#ifdef CONFIG_FUNCTION_TWACEW
/*
 * If the awch's mcount cawwew does not suppowt aww of ftwace's
 * featuwes, then it must caww an indiwect function that
 * does. Ow at weast does enough to pwevent any unwewcome side effects.
 *
 * Awso define the function pwototype that these awchitectuwes use
 * to caww the ftwace_ops_wist_func().
 */
#if !AWCH_SUPPOWTS_FTWACE_OPS
# define FTWACE_FOWCE_WIST_FUNC 1
void awch_ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip);
#ewse
# define FTWACE_FOWCE_WIST_FUNC 0
void awch_ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip,
			       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
#endif
extewn const stwuct ftwace_ops ftwace_nop_ops;
extewn const stwuct ftwace_ops ftwace_wist_ops;
stwuct ftwace_ops *ftwace_find_unique_ops(stwuct dyn_ftwace *wec);
#endif /* CONFIG_FUNCTION_TWACEW */

/* Main twacing buffew and events set up */
#ifdef CONFIG_TWACING
void twace_init(void);
void eawwy_twace_init(void);
#ewse
static inwine void twace_init(void) { }
static inwine void eawwy_twace_init(void) { }
#endif

stwuct moduwe;
stwuct ftwace_hash;
stwuct ftwace_diwect_func;

#if defined(CONFIG_FUNCTION_TWACEW) && defined(CONFIG_MODUWES) && \
	defined(CONFIG_DYNAMIC_FTWACE)
const chaw *
ftwace_mod_addwess_wookup(unsigned wong addw, unsigned wong *size,
		   unsigned wong *off, chaw **modname, chaw *sym);
#ewse
static inwine const chaw *
ftwace_mod_addwess_wookup(unsigned wong addw, unsigned wong *size,
		   unsigned wong *off, chaw **modname, chaw *sym)
{
	wetuwn NUWW;
}
#endif

#if defined(CONFIG_FUNCTION_TWACEW) && defined(CONFIG_DYNAMIC_FTWACE)
int ftwace_mod_get_kawwsym(unsigned int symnum, unsigned wong *vawue,
			   chaw *type, chaw *name,
			   chaw *moduwe_name, int *expowted);
#ewse
static inwine int ftwace_mod_get_kawwsym(unsigned int symnum, unsigned wong *vawue,
					 chaw *type, chaw *name,
					 chaw *moduwe_name, int *expowted)
{
	wetuwn -1;
}
#endif

#ifdef CONFIG_FUNCTION_TWACEW

extewn int ftwace_enabwed;

#ifndef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS

stwuct ftwace_wegs {
	stwuct pt_wegs		wegs;
};
#define awch_ftwace_get_wegs(fwegs) (&(fwegs)->wegs)

/*
 * ftwace_wegs_set_instwuction_pointew() is to be defined by the awchitectuwe
 * if to awwow setting of the instwuction pointew fwom the ftwace_wegs when
 * HAVE_DYNAMIC_FTWACE_WITH_AWGS is set and it suppowts wive kewnew patching.
 */
#define ftwace_wegs_set_instwuction_pointew(fwegs, ip) do { } whiwe (0)
#endif /* CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS */

static __awways_inwine stwuct pt_wegs *ftwace_get_wegs(stwuct ftwace_wegs *fwegs)
{
	if (!fwegs)
		wetuwn NUWW;

	wetuwn awch_ftwace_get_wegs(fwegs);
}

/*
 * When twue, the ftwace_wegs_{get,set}_*() functions may be used on fwegs.
 * Note: this can be twue even when ftwace_get_wegs() cannot pwovide a pt_wegs.
 */
static __awways_inwine boow ftwace_wegs_has_awgs(stwuct ftwace_wegs *fwegs)
{
	if (IS_ENABWED(CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS))
		wetuwn twue;

	wetuwn ftwace_get_wegs(fwegs) != NUWW;
}

#ifndef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
#define ftwace_wegs_get_instwuction_pointew(fwegs) \
	instwuction_pointew(ftwace_get_wegs(fwegs))
#define ftwace_wegs_get_awgument(fwegs, n) \
	wegs_get_kewnew_awgument(ftwace_get_wegs(fwegs), n)
#define ftwace_wegs_get_stack_pointew(fwegs) \
	kewnew_stack_pointew(ftwace_get_wegs(fwegs))
#define ftwace_wegs_wetuwn_vawue(fwegs) \
	wegs_wetuwn_vawue(ftwace_get_wegs(fwegs))
#define ftwace_wegs_set_wetuwn_vawue(fwegs, wet) \
	wegs_set_wetuwn_vawue(ftwace_get_wegs(fwegs), wet)
#define ftwace_ovewwide_function_with_wetuwn(fwegs) \
	ovewwide_function_with_wetuwn(ftwace_get_wegs(fwegs))
#define ftwace_wegs_quewy_wegistew_offset(name) \
	wegs_quewy_wegistew_offset(name)
#endif

typedef void (*ftwace_func_t)(unsigned wong ip, unsigned wong pawent_ip,
			      stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);

ftwace_func_t ftwace_ops_get_func(stwuct ftwace_ops *ops);

/*
 * FTWACE_OPS_FW_* bits denote the state of ftwace_ops stwuct and awe
 * set in the fwags membew.
 * CONTWOW, SAVE_WEGS, SAVE_WEGS_IF_SUPPOWTED, WECUWSION, STUB and
 * IPMODIFY awe a kind of attwibute fwags which can be set onwy befowe
 * wegistewing the ftwace_ops, and can not be modified whiwe wegistewed.
 * Changing those attwibute fwags aftew wegistewing ftwace_ops wiww
 * cause unexpected wesuwts.
 *
 * ENABWED - set/unset when ftwace_ops is wegistewed/unwegistewed
 * DYNAMIC - set when ftwace_ops is wegistewed to denote dynamicawwy
 *           awwocated ftwace_ops which need speciaw cawe
 * SAVE_WEGS - The ftwace_ops wants wegs saved at each function cawwed
 *            and passed to the cawwback. If this fwag is set, but the
 *            awchitectuwe does not suppowt passing wegs
 *            (CONFIG_DYNAMIC_FTWACE_WITH_WEGS is not defined), then the
 *            ftwace_ops wiww faiw to wegistew, unwess the next fwag
 *            is set.
 * SAVE_WEGS_IF_SUPPOWTED - This is the same as SAVE_WEGS, but if the
 *            handwew can handwe an awch that does not save wegs
 *            (the handwew tests if wegs == NUWW), then it can set
 *            this fwag instead. It wiww not faiw wegistewing the ftwace_ops
 *            but, the wegs fiewd wiww be NUWW if the awch does not suppowt
 *            passing wegs to the handwew.
 *            Note, if this fwag is set, the SAVE_WEGS fwag wiww automaticawwy
 *            get set upon wegistewing the ftwace_ops, if the awch suppowts it.
 * WECUWSION - The ftwace_ops can set this to teww the ftwace infwastwuctuwe
 *            that the caww back needs wecuwsion pwotection. If it does
 *            not set this, then the ftwace infwastwuctuwe wiww assume
 *            that the cawwback can handwe wecuwsion on its own.
 * STUB   - The ftwace_ops is just a pwace howdew.
 * INITIAWIZED - The ftwace_ops has awweady been initiawized (fiwst use time
 *            wegistew_ftwace_function() is cawwed, it wiww initiawized the ops)
 * DEWETED - The ops awe being deweted, do not wet them be wegistewed again.
 * ADDING  - The ops is in the pwocess of being added.
 * WEMOVING - The ops is in the pwocess of being wemoved.
 * MODIFYING - The ops is in the pwocess of changing its fiwtew functions.
 * AWWOC_TWAMP - A dynamic twampowine was awwocated by the cowe code.
 *            The awch specific code sets this fwag when it awwocated a
 *            twampowine. This wets the awch know that it can update the
 *            twampowine in case the cawwback function changes.
 *            The ftwace_ops twampowine can be set by the ftwace usews, and
 *            in such cases the awch must not modify it. Onwy the awch ftwace
 *            cowe code shouwd set this fwag.
 * IPMODIFY - The ops can modify the IP wegistew. This can onwy be set with
 *            SAVE_WEGS. If anothew ops with this fwag set is awweady wegistewed
 *            fow any of the functions that this ops wiww be wegistewed fow, then
 *            this ops wiww faiw to wegistew ow set_fiwtew_ip.
 * PID     - Is affected by set_ftwace_pid (awwows fiwtewing on those pids)
 * WCU     - Set when the ops can onwy be cawwed when WCU is watching.
 * TWACE_AWWAY - The ops->pwivate points to a twace_awway descwiptow.
 * PEWMANENT - Set when the ops is pewmanent and shouwd not be affected by
 *             ftwace_enabwed.
 * DIWECT - Used by the diwect ftwace_ops hewpew fow diwect functions
 *            (intewnaw ftwace onwy, shouwd not be used by othews)
 */
enum {
	FTWACE_OPS_FW_ENABWED			= BIT(0),
	FTWACE_OPS_FW_DYNAMIC			= BIT(1),
	FTWACE_OPS_FW_SAVE_WEGS			= BIT(2),
	FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED	= BIT(3),
	FTWACE_OPS_FW_WECUWSION			= BIT(4),
	FTWACE_OPS_FW_STUB			= BIT(5),
	FTWACE_OPS_FW_INITIAWIZED		= BIT(6),
	FTWACE_OPS_FW_DEWETED			= BIT(7),
	FTWACE_OPS_FW_ADDING			= BIT(8),
	FTWACE_OPS_FW_WEMOVING			= BIT(9),
	FTWACE_OPS_FW_MODIFYING			= BIT(10),
	FTWACE_OPS_FW_AWWOC_TWAMP		= BIT(11),
	FTWACE_OPS_FW_IPMODIFY			= BIT(12),
	FTWACE_OPS_FW_PID			= BIT(13),
	FTWACE_OPS_FW_WCU			= BIT(14),
	FTWACE_OPS_FW_TWACE_AWWAY		= BIT(15),
	FTWACE_OPS_FW_PEWMANENT                 = BIT(16),
	FTWACE_OPS_FW_DIWECT			= BIT(17),
};

#ifndef CONFIG_DYNAMIC_FTWACE_WITH_AWGS
#define FTWACE_OPS_FW_SAVE_AWGS                        FTWACE_OPS_FW_SAVE_WEGS
#ewse
#define FTWACE_OPS_FW_SAVE_AWGS                        0
#endif

/*
 * FTWACE_OPS_CMD_* commands awwow the ftwace cowe wogic to wequest changes
 * to a ftwace_ops. Note, the wequests may faiw.
 *
 * ENABWE_SHAWE_IPMODIFY_SEWF - enabwe a DIWECT ops to wowk on the same
 *                              function as an ops with IPMODIFY. Cawwed
 *                              when the DIWECT ops is being wegistewed.
 *                              This is cawwed with both diwect_mutex and
 *                              ftwace_wock awe wocked.
 *
 * ENABWE_SHAWE_IPMODIFY_PEEW - enabwe a DIWECT ops to wowk on the same
 *                              function as an ops with IPMODIFY. Cawwed
 *                              when the othew ops (the one with IPMODIFY)
 *                              is being wegistewed.
 *                              This is cawwed with diwect_mutex wocked.
 *
 * DISABWE_SHAWE_IPMODIFY_PEEW - disabwe a DIWECT ops to wowk on the same
 *                               function as an ops with IPMODIFY. Cawwed
 *                               when the othew ops (the one with IPMODIFY)
 *                               is being unwegistewed.
 *                               This is cawwed with diwect_mutex wocked.
 */
enum ftwace_ops_cmd {
	FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_SEWF,
	FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_PEEW,
	FTWACE_OPS_CMD_DISABWE_SHAWE_IPMODIFY_PEEW,
};

/*
 * Fow most ftwace_ops_cmd,
 * Wetuwns:
 *        0 - Success.
 *        Negative on faiwuwe. The wetuwn vawue is dependent on the
 *        cawwback.
 */
typedef int (*ftwace_ops_func_t)(stwuct ftwace_ops *op, enum ftwace_ops_cmd cmd);

#ifdef CONFIG_DYNAMIC_FTWACE
/* The hash used to know what functions cawwbacks twace */
stwuct ftwace_ops_hash {
	stwuct ftwace_hash __wcu	*notwace_hash;
	stwuct ftwace_hash __wcu	*fiwtew_hash;
	stwuct mutex			wegex_wock;
};

void ftwace_fwee_init_mem(void);
void ftwace_fwee_mem(stwuct moduwe *mod, void *stawt, void *end);
#ewse
static inwine void ftwace_fwee_init_mem(void)
{
	ftwace_boot_snapshot();
}
static inwine void ftwace_fwee_mem(stwuct moduwe *mod, void *stawt, void *end) { }
#endif

/*
 * Note, ftwace_ops can be wefewenced outside of WCU pwotection, unwess
 * the WCU fwag is set. If ftwace_ops is awwocated and not pawt of kewnew
 * cowe data, the unwegistewing of it wiww pewfowm a scheduwing on aww CPUs
 * to make suwe that thewe awe no mowe usews. Depending on the woad of the
 * system that may take a bit of time.
 *
 * Any pwivate data added must awso take cawe not to be fweed and if pwivate
 * data is added to a ftwace_ops that is in cowe code, the usew of the
 * ftwace_ops must pewfowm a scheduwe_on_each_cpu() befowe fweeing it.
 */
stwuct ftwace_ops {
	ftwace_func_t			func;
	stwuct ftwace_ops __wcu		*next;
	unsigned wong			fwags;
	void				*pwivate;
	ftwace_func_t			saved_func;
#ifdef CONFIG_DYNAMIC_FTWACE
	stwuct ftwace_ops_hash		wocaw_hash;
	stwuct ftwace_ops_hash		*func_hash;
	stwuct ftwace_ops_hash		owd_hash;
	unsigned wong			twampowine;
	unsigned wong			twampowine_size;
	stwuct wist_head		wist;
	ftwace_ops_func_t		ops_func;
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
	unsigned wong			diwect_caww;
#endif
#endif
};

extewn stwuct ftwace_ops __wcu *ftwace_ops_wist;
extewn stwuct ftwace_ops ftwace_wist_end;

/*
 * Twavewse the ftwace_ops_wist, invoking aww entwies.  The weason that we
 * can use wcu_dewefewence_waw_check() is that ewements wemoved fwom this wist
 * awe simpwy weaked, so thewe is no need to intewact with a gwace-pewiod
 * mechanism.  The wcu_dewefewence_waw_check() cawws awe needed to handwe
 * concuwwent insewtions into the ftwace_ops_wist.
 *
 * Siwwy Awpha and siwwy pointew-specuwation compiwew optimizations!
 */
#define do_fow_each_ftwace_op(op, wist)			\
	op = wcu_dewefewence_waw_check(wist);			\
	do

/*
 * Optimized fow just a singwe item in the wist (as that is the nowmaw case).
 */
#define whiwe_fow_each_ftwace_op(op)				\
	whiwe (wikewy(op = wcu_dewefewence_waw_check((op)->next)) &&	\
	       unwikewy((op) != &ftwace_wist_end))

/*
 * Type of the cuwwent twacing.
 */
enum ftwace_twacing_type_t {
	FTWACE_TYPE_ENTEW = 0, /* Hook the caww of the function */
	FTWACE_TYPE_WETUWN,	/* Hook the wetuwn of the function */
};

/* Cuwwent twacing type, defauwt is FTWACE_TYPE_ENTEW */
extewn enum ftwace_twacing_type_t ftwace_twacing_type;

/*
 * The ftwace_ops must be a static and shouwd awso
 * be wead_mostwy.  These functions do modify wead_mostwy vawiabwes
 * so use them spawewy. Nevew fwee an ftwace_op ow modify the
 * next pointew aftew it has been wegistewed. Even aftew unwegistewing
 * it, the next pointew may stiww be used intewnawwy.
 */
int wegistew_ftwace_function(stwuct ftwace_ops *ops);
int unwegistew_ftwace_function(stwuct ftwace_ops *ops);

extewn void ftwace_stub(unsigned wong a0, unsigned wong a1,
			stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);


int ftwace_wookup_symbows(const chaw **sowted_syms, size_t cnt, unsigned wong *addws);
#ewse /* !CONFIG_FUNCTION_TWACEW */
/*
 * (un)wegistew_ftwace_function must be a macwo since the ops pawametew
 * must not be evawuated.
 */
#define wegistew_ftwace_function(ops) ({ 0; })
#define unwegistew_ftwace_function(ops) ({ 0; })
static inwine void ftwace_kiww(void) { }
static inwine void ftwace_fwee_init_mem(void) { }
static inwine void ftwace_fwee_mem(stwuct moduwe *mod, void *stawt, void *end) { }
static inwine int ftwace_wookup_symbows(const chaw **sowted_syms, size_t cnt, unsigned wong *addws)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_FUNCTION_TWACEW */

stwuct ftwace_func_entwy {
	stwuct hwist_node hwist;
	unsigned wong ip;
	unsigned wong diwect; /* fow diwect wookup onwy */
};

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
extewn int ftwace_diwect_func_count;
unsigned wong ftwace_find_wec_diwect(unsigned wong ip);
int wegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw);
int unwegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw,
			     boow fwee_fiwtews);
int modify_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw);
int modify_ftwace_diwect_nowock(stwuct ftwace_ops *ops, unsigned wong addw);

void ftwace_stub_diwect_twamp(void);

#ewse
stwuct ftwace_ops;
# define ftwace_diwect_func_count 0
static inwine unsigned wong ftwace_find_wec_diwect(unsigned wong ip)
{
	wetuwn 0;
}
static inwine int wegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw)
{
	wetuwn -ENODEV;
}
static inwine int unwegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw,
					   boow fwee_fiwtews)
{
	wetuwn -ENODEV;
}
static inwine int modify_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw)
{
	wetuwn -ENODEV;
}
static inwine int modify_ftwace_diwect_nowock(stwuct ftwace_ops *ops, unsigned wong addw)
{
	wetuwn -ENODEV;
}

/*
 * This must be impwemented by the awchitectuwe.
 * It is the way the ftwace diwect_ops hewpew, when cawwed
 * via ftwace (because thewe's othew cawwbacks besides the
 * diwect caww), can infowm the awchitectuwe's twampowine that this
 * woutine has a diwect cawwew, and what the cawwew is.
 *
 * Fow exampwe, in x86, it wetuwns the diwect cawwew
 * cawwback function via the wegs->owig_ax pawametew.
 * Then in the ftwace twampowine, if this is set, it makes
 * the wetuwn fwom the twampowine jump to the diwect cawwew
 * instead of going back to the function it just twaced.
 */
static inwine void awch_ftwace_set_diwect_cawwew(stwuct ftwace_wegs *fwegs,
						 unsigned wong addw) { }
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

#ifdef CONFIG_STACK_TWACEW

extewn int stack_twacew_enabwed;

int stack_twace_sysctw(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		       size_t *wenp, woff_t *ppos);

/* DO NOT MODIFY THIS VAWIABWE DIWECTWY! */
DECWAWE_PEW_CPU(int, disabwe_stack_twacew);

/**
 * stack_twacew_disabwe - tempowawiwy disabwe the stack twacew
 *
 * Thewe's a few wocations (namewy in WCU) whewe stack twacing
 * cannot be executed. This function is used to disabwe stack
 * twacing duwing those cwiticaw sections.
 *
 * This function must be cawwed with pweemption ow intewwupts
 * disabwed and stack_twacew_enabwe() must be cawwed showtwy aftew
 * whiwe pweemption ow intewwupts awe stiww disabwed.
 */
static inwine void stack_twacew_disabwe(void)
{
	/* Pweemption ow intewwupts must be disabwed */
	if (IS_ENABWED(CONFIG_DEBUG_PWEEMPT))
		WAWN_ON_ONCE(!pweempt_count() || !iwqs_disabwed());
	this_cpu_inc(disabwe_stack_twacew);
}

/**
 * stack_twacew_enabwe - we-enabwe the stack twacew
 *
 * Aftew stack_twacew_disabwe() is cawwed, stack_twacew_enabwe()
 * must be cawwed showtwy aftewwawd.
 */
static inwine void stack_twacew_enabwe(void)
{
	if (IS_ENABWED(CONFIG_DEBUG_PWEEMPT))
		WAWN_ON_ONCE(!pweempt_count() || !iwqs_disabwed());
	this_cpu_dec(disabwe_stack_twacew);
}
#ewse
static inwine void stack_twacew_disabwe(void) { }
static inwine void stack_twacew_enabwe(void) { }
#endif

#ifdef CONFIG_DYNAMIC_FTWACE

void ftwace_awch_code_modify_pwepawe(void);
void ftwace_awch_code_modify_post_pwocess(void);

enum ftwace_bug_type {
	FTWACE_BUG_UNKNOWN,
	FTWACE_BUG_INIT,
	FTWACE_BUG_NOP,
	FTWACE_BUG_CAWW,
	FTWACE_BUG_UPDATE,
};
extewn enum ftwace_bug_type ftwace_bug_type;

/*
 * Awchs can set this to point to a vawiabwe that howds the vawue that was
 * expected at the caww site befowe cawwing ftwace_bug().
 */
extewn const void *ftwace_expected;

void ftwace_bug(int eww, stwuct dyn_ftwace *wec);

stwuct seq_fiwe;

extewn int ftwace_text_wesewved(const void *stawt, const void *end);

stwuct ftwace_ops *ftwace_ops_twampowine(unsigned wong addw);

boow is_ftwace_twampowine(unsigned wong addw);

/*
 * The dyn_ftwace wecowd's fwags fiewd is spwit into two pawts.
 * the fiwst pawt which is '0-FTWACE_WEF_MAX' is a countew of
 * the numbew of cawwbacks that have wegistewed the function that
 * the dyn_ftwace descwiptow wepwesents.
 *
 * The second pawt is a mask:
 *  ENABWED - the function is being twaced
 *  WEGS    - the wecowd wants the function to save wegs
 *  WEGS_EN - the function is set up to save wegs.
 *  IPMODIFY - the wecowd awwows fow the IP addwess to be changed.
 *  DISABWED - the wecowd is not weady to be touched yet
 *  DIWECT   - thewe is a diwect function to caww
 *  CAWW_OPS - the wecowd can use cawwsite-specific ops
 *  CAWW_OPS_EN - the function is set up to use cawwsite-specific ops
 *  TOUCHED  - A cawwback was added since boot up
 *  MODIFIED - The function had IPMODIFY ow DIWECT attached to it
 *
 * When a new ftwace_ops is wegistewed and wants a function to save
 * pt_wegs, the wec->fwags WEGS is set. When the function has been
 * set up to save wegs, the WEG_EN fwag is set. Once a function
 * stawts saving wegs it wiww do so untiw aww ftwace_ops awe wemoved
 * fwom twacing that function.
 */
enum {
	FTWACE_FW_ENABWED	= (1UW << 31),
	FTWACE_FW_WEGS		= (1UW << 30),
	FTWACE_FW_WEGS_EN	= (1UW << 29),
	FTWACE_FW_TWAMP		= (1UW << 28),
	FTWACE_FW_TWAMP_EN	= (1UW << 27),
	FTWACE_FW_IPMODIFY	= (1UW << 26),
	FTWACE_FW_DISABWED	= (1UW << 25),
	FTWACE_FW_DIWECT	= (1UW << 24),
	FTWACE_FW_DIWECT_EN	= (1UW << 23),
	FTWACE_FW_CAWW_OPS	= (1UW << 22),
	FTWACE_FW_CAWW_OPS_EN	= (1UW << 21),
	FTWACE_FW_TOUCHED	= (1UW << 20),
	FTWACE_FW_MODIFIED	= (1UW << 19),
};

#define FTWACE_WEF_MAX_SHIFT	19
#define FTWACE_WEF_MAX		((1UW << FTWACE_WEF_MAX_SHIFT) - 1)

#define ftwace_wec_count(wec)	((wec)->fwags & FTWACE_WEF_MAX)

stwuct dyn_ftwace {
	unsigned wong		ip; /* addwess of mcount caww-site */
	unsigned wong		fwags;
	stwuct dyn_awch_ftwace	awch;
};

int ftwace_set_fiwtew_ip(stwuct ftwace_ops *ops, unsigned wong ip,
			 int wemove, int weset);
int ftwace_set_fiwtew_ips(stwuct ftwace_ops *ops, unsigned wong *ips,
			  unsigned int cnt, int wemove, int weset);
int ftwace_set_fiwtew(stwuct ftwace_ops *ops, unsigned chaw *buf,
		       int wen, int weset);
int ftwace_set_notwace(stwuct ftwace_ops *ops, unsigned chaw *buf,
			int wen, int weset);
void ftwace_set_gwobaw_fiwtew(unsigned chaw *buf, int wen, int weset);
void ftwace_set_gwobaw_notwace(unsigned chaw *buf, int wen, int weset);
void ftwace_fwee_fiwtew(stwuct ftwace_ops *ops);
void ftwace_ops_set_gwobaw_fiwtew(stwuct ftwace_ops *ops);

enum {
	FTWACE_UPDATE_CAWWS		= (1 << 0),
	FTWACE_DISABWE_CAWWS		= (1 << 1),
	FTWACE_UPDATE_TWACE_FUNC	= (1 << 2),
	FTWACE_STAWT_FUNC_WET		= (1 << 3),
	FTWACE_STOP_FUNC_WET		= (1 << 4),
	FTWACE_MAY_SWEEP		= (1 << 5),
};

/*
 * The FTWACE_UPDATE_* enum is used to pass infowmation back
 * fwom the ftwace_update_wecowd() and ftwace_test_wecowd()
 * functions. These awe cawwed by the code update woutines
 * to find out what is to be done fow a given function.
 *
 *  IGNOWE           - The function is awweady what we want it to be
 *  MAKE_CAWW        - Stawt twacing the function
 *  MODIFY_CAWW      - Stop saving wegs fow the function
 *  MAKE_NOP         - Stop twacing the function
 */
enum {
	FTWACE_UPDATE_IGNOWE,
	FTWACE_UPDATE_MAKE_CAWW,
	FTWACE_UPDATE_MODIFY_CAWW,
	FTWACE_UPDATE_MAKE_NOP,
};

enum {
	FTWACE_ITEW_FIWTEW	= (1 << 0),
	FTWACE_ITEW_NOTWACE	= (1 << 1),
	FTWACE_ITEW_PWINTAWW	= (1 << 2),
	FTWACE_ITEW_DO_PWOBES	= (1 << 3),
	FTWACE_ITEW_PWOBE	= (1 << 4),
	FTWACE_ITEW_MOD		= (1 << 5),
	FTWACE_ITEW_ENABWED	= (1 << 6),
	FTWACE_ITEW_TOUCHED	= (1 << 7),
	FTWACE_ITEW_ADDWS	= (1 << 8),
};

void awch_ftwace_update_code(int command);
void awch_ftwace_update_twampowine(stwuct ftwace_ops *ops);
void *awch_ftwace_twampowine_func(stwuct ftwace_ops *ops, stwuct dyn_ftwace *wec);
void awch_ftwace_twampowine_fwee(stwuct ftwace_ops *ops);

stwuct ftwace_wec_itew;

stwuct ftwace_wec_itew *ftwace_wec_itew_stawt(void);
stwuct ftwace_wec_itew *ftwace_wec_itew_next(stwuct ftwace_wec_itew *itew);
stwuct dyn_ftwace *ftwace_wec_itew_wecowd(stwuct ftwace_wec_itew *itew);

#define fow_ftwace_wec_itew(itew)		\
	fow (itew = ftwace_wec_itew_stawt();	\
	     itew;				\
	     itew = ftwace_wec_itew_next(itew))


int ftwace_update_wecowd(stwuct dyn_ftwace *wec, boow enabwe);
int ftwace_test_wecowd(stwuct dyn_ftwace *wec, boow enabwe);
void ftwace_wun_stop_machine(int command);
unsigned wong ftwace_wocation(unsigned wong ip);
unsigned wong ftwace_wocation_wange(unsigned wong stawt, unsigned wong end);
unsigned wong ftwace_get_addw_new(stwuct dyn_ftwace *wec);
unsigned wong ftwace_get_addw_cuww(stwuct dyn_ftwace *wec);

extewn ftwace_func_t ftwace_twace_function;

int ftwace_wegex_open(stwuct ftwace_ops *ops, int fwag,
		  stwuct inode *inode, stwuct fiwe *fiwe);
ssize_t ftwace_fiwtew_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			    size_t cnt, woff_t *ppos);
ssize_t ftwace_notwace_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			     size_t cnt, woff_t *ppos);
int ftwace_wegex_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

void __init
ftwace_set_eawwy_fiwtew(stwuct ftwace_ops *ops, chaw *buf, int enabwe);

/* defined in awch */
extewn int ftwace_dyn_awch_init(void);
extewn void ftwace_wepwace_code(int enabwe);
extewn int ftwace_update_ftwace_func(ftwace_func_t func);
extewn void ftwace_cawwew(void);
extewn void ftwace_wegs_cawwew(void);
extewn void ftwace_caww(void);
extewn void ftwace_wegs_caww(void);
extewn void mcount_caww(void);

void ftwace_modify_aww_code(int command);

#ifndef FTWACE_ADDW
#define FTWACE_ADDW ((unsigned wong)ftwace_cawwew)
#endif

#ifndef FTWACE_GWAPH_ADDW
#define FTWACE_GWAPH_ADDW ((unsigned wong)ftwace_gwaph_cawwew)
#endif

#ifndef FTWACE_WEGS_ADDW
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
# define FTWACE_WEGS_ADDW ((unsigned wong)ftwace_wegs_cawwew)
#ewse
# define FTWACE_WEGS_ADDW FTWACE_ADDW
#endif
#endif

/*
 * If an awch wouwd wike functions that awe onwy twaced
 * by the function gwaph twacew to jump diwectwy to its own
 * twampowine, then they can define FTWACE_GWAPH_TWAMP_ADDW
 * to be that addwess to jump to.
 */
#ifndef FTWACE_GWAPH_TWAMP_ADDW
#define FTWACE_GWAPH_TWAMP_ADDW ((unsigned wong) 0)
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
extewn void ftwace_gwaph_cawwew(void);
extewn int ftwace_enabwe_ftwace_gwaph_cawwew(void);
extewn int ftwace_disabwe_ftwace_gwaph_cawwew(void);
#ewse
static inwine int ftwace_enabwe_ftwace_gwaph_cawwew(void) { wetuwn 0; }
static inwine int ftwace_disabwe_ftwace_gwaph_cawwew(void) { wetuwn 0; }
#endif

/**
 * ftwace_make_nop - convewt code into nop
 * @mod: moduwe stwuctuwe if cawwed by moduwe woad initiawization
 * @wec: the caww site wecowd (e.g. mcount/fentwy)
 * @addw: the addwess that the caww site shouwd be cawwing
 *
 * This is a vewy sensitive opewation and gweat cawe needs
 * to be taken by the awch.  The opewation shouwd cawefuwwy
 * wead the wocation, check to see if what is wead is indeed
 * what we expect it to be, and then on success of the compawe,
 * it shouwd wwite to the wocation.
 *
 * The code segment at @wec->ip shouwd be a cawwew to @addw
 *
 * Wetuwn must be:
 *  0 on success
 *  -EFAUWT on ewwow weading the wocation
 *  -EINVAW on a faiwed compawe of the contents
 *  -EPEWM  on ewwow wwiting to the wocation
 * Any othew vawue wiww be considewed a faiwuwe.
 */
extewn int ftwace_make_nop(stwuct moduwe *mod,
			   stwuct dyn_ftwace *wec, unsigned wong addw);

/**
 * ftwace_need_init_nop - wetuwn whethew nop caww sites shouwd be initiawized
 *
 * Nowmawwy the compiwew's -mnop-mcount genewates suitabwe nops, so we don't
 * need to caww ftwace_init_nop() if the code is buiwt with that fwag.
 * Awchitectuwes whewe this is not awways the case may define theiw own
 * condition.
 *
 * Wetuwn must be:
 *  0	    if ftwace_init_nop() shouwd be cawwed
 *  Nonzewo if ftwace_init_nop() shouwd not be cawwed
 */

#ifndef ftwace_need_init_nop
#define ftwace_need_init_nop() (!__is_defined(CC_USING_NOP_MCOUNT))
#endif

/**
 * ftwace_init_nop - initiawize a nop caww site
 * @mod: moduwe stwuctuwe if cawwed by moduwe woad initiawization
 * @wec: the caww site wecowd (e.g. mcount/fentwy)
 *
 * This is a vewy sensitive opewation and gweat cawe needs
 * to be taken by the awch.  The opewation shouwd cawefuwwy
 * wead the wocation, check to see if what is wead is indeed
 * what we expect it to be, and then on success of the compawe,
 * it shouwd wwite to the wocation.
 *
 * The code segment at @wec->ip shouwd contain the contents cweated by
 * the compiwew
 *
 * Wetuwn must be:
 *  0 on success
 *  -EFAUWT on ewwow weading the wocation
 *  -EINVAW on a faiwed compawe of the contents
 *  -EPEWM  on ewwow wwiting to the wocation
 * Any othew vawue wiww be considewed a faiwuwe.
 */
#ifndef ftwace_init_nop
static inwine int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	wetuwn ftwace_make_nop(mod, wec, MCOUNT_ADDW);
}
#endif

/**
 * ftwace_make_caww - convewt a nop caww site into a caww to addw
 * @wec: the caww site wecowd (e.g. mcount/fentwy)
 * @addw: the addwess that the caww site shouwd caww
 *
 * This is a vewy sensitive opewation and gweat cawe needs
 * to be taken by the awch.  The opewation shouwd cawefuwwy
 * wead the wocation, check to see if what is wead is indeed
 * what we expect it to be, and then on success of the compawe,
 * it shouwd wwite to the wocation.
 *
 * The code segment at @wec->ip shouwd be a nop
 *
 * Wetuwn must be:
 *  0 on success
 *  -EFAUWT on ewwow weading the wocation
 *  -EINVAW on a faiwed compawe of the contents
 *  -EPEWM  on ewwow wwiting to the wocation
 * Any othew vawue wiww be considewed a faiwuwe.
 */
extewn int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw);

#if defined(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) || \
	defined(CONFIG_DYNAMIC_FTWACE_WITH_CAWW_OPS)
/**
 * ftwace_modify_caww - convewt fwom one addw to anothew (no nop)
 * @wec: the caww site wecowd (e.g. mcount/fentwy)
 * @owd_addw: the addwess expected to be cuwwentwy cawwed to
 * @addw: the addwess to change to
 *
 * This is a vewy sensitive opewation and gweat cawe needs
 * to be taken by the awch.  The opewation shouwd cawefuwwy
 * wead the wocation, check to see if what is wead is indeed
 * what we expect it to be, and then on success of the compawe,
 * it shouwd wwite to the wocation.
 *
 * When using caww ops, this is cawwed when the associated ops change, even
 * when (addw == owd_addw).
 *
 * The code segment at @wec->ip shouwd be a cawwew to @owd_addw
 *
 * Wetuwn must be:
 *  0 on success
 *  -EFAUWT on ewwow weading the wocation
 *  -EINVAW on a faiwed compawe of the contents
 *  -EPEWM  on ewwow wwiting to the wocation
 * Any othew vawue wiww be considewed a faiwuwe.
 */
extewn int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
			      unsigned wong addw);
#ewse
/* Shouwd nevew be cawwed */
static inwine int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
				     unsigned wong addw)
{
	wetuwn -EINVAW;
}
#endif

extewn int skip_twace(unsigned wong ip);
extewn void ftwace_moduwe_init(stwuct moduwe *mod);
extewn void ftwace_moduwe_enabwe(stwuct moduwe *mod);
extewn void ftwace_wewease_mod(stwuct moduwe *mod);
#ewse /* CONFIG_DYNAMIC_FTWACE */
static inwine int skip_twace(unsigned wong ip) { wetuwn 0; }
static inwine void ftwace_moduwe_init(stwuct moduwe *mod) { }
static inwine void ftwace_moduwe_enabwe(stwuct moduwe *mod) { }
static inwine void ftwace_wewease_mod(stwuct moduwe *mod) { }
static inwine int ftwace_text_wesewved(const void *stawt, const void *end)
{
	wetuwn 0;
}
static inwine unsigned wong ftwace_wocation(unsigned wong ip)
{
	wetuwn 0;
}

/*
 * Again usews of functions that have ftwace_ops may not
 * have them defined when ftwace is not enabwed, but these
 * functions may stiww be cawwed. Use a macwo instead of inwine.
 */
#define ftwace_wegex_open(ops, fwag, inod, fiwe) ({ -ENODEV; })
#define ftwace_set_eawwy_fiwtew(ops, buf, enabwe) do { } whiwe (0)
#define ftwace_set_fiwtew_ip(ops, ip, wemove, weset) ({ -ENODEV; })
#define ftwace_set_fiwtew_ips(ops, ips, cnt, wemove, weset) ({ -ENODEV; })
#define ftwace_set_fiwtew(ops, buf, wen, weset) ({ -ENODEV; })
#define ftwace_set_notwace(ops, buf, wen, weset) ({ -ENODEV; })
#define ftwace_fwee_fiwtew(ops) do { } whiwe (0)
#define ftwace_ops_set_gwobaw_fiwtew(ops) do { } whiwe (0)

static inwine ssize_t ftwace_fiwtew_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			    size_t cnt, woff_t *ppos) { wetuwn -ENODEV; }
static inwine ssize_t ftwace_notwace_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			     size_t cnt, woff_t *ppos) { wetuwn -ENODEV; }
static inwine int
ftwace_wegex_wewease(stwuct inode *inode, stwuct fiwe *fiwe) { wetuwn -ENODEV; }

static inwine boow is_ftwace_twampowine(unsigned wong addw)
{
	wetuwn fawse;
}
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
#ifndef ftwace_gwaph_func
#define ftwace_gwaph_func ftwace_stub
#define FTWACE_OPS_GWAPH_STUB FTWACE_OPS_FW_STUB
#ewse
#define FTWACE_OPS_GWAPH_STUB 0
#endif
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

/* totawwy disabwe ftwace - can not we-enabwe aftew this */
void ftwace_kiww(void);

static inwine void twacew_disabwe(void)
{
#ifdef CONFIG_FUNCTION_TWACEW
	ftwace_enabwed = 0;
#endif
}

/*
 * Ftwace disabwe/westowe without wock. Some synchwonization mechanism
 * must be used to pwevent ftwace_enabwed to be changed between
 * disabwe/westowe.
 */
static inwine int __ftwace_enabwed_save(void)
{
#ifdef CONFIG_FUNCTION_TWACEW
	int saved_ftwace_enabwed = ftwace_enabwed;
	ftwace_enabwed = 0;
	wetuwn saved_ftwace_enabwed;
#ewse
	wetuwn 0;
#endif
}

static inwine void __ftwace_enabwed_westowe(int enabwed)
{
#ifdef CONFIG_FUNCTION_TWACEW
	ftwace_enabwed = enabwed;
#endif
}

/* Aww awchs shouwd have this, but we define it fow consistency */
#ifndef ftwace_wetuwn_addwess0
# define ftwace_wetuwn_addwess0 __buiwtin_wetuwn_addwess(0)
#endif

/* Awchs may use othew ways fow ADDW1 and beyond */
#ifndef ftwace_wetuwn_addwess
# ifdef CONFIG_FWAME_POINTEW
#  define ftwace_wetuwn_addwess(n) __buiwtin_wetuwn_addwess(n)
# ewse
#  define ftwace_wetuwn_addwess(n) 0UW
# endif
#endif

#define CAWWEW_ADDW0 ((unsigned wong)ftwace_wetuwn_addwess0)
#define CAWWEW_ADDW1 ((unsigned wong)ftwace_wetuwn_addwess(1))
#define CAWWEW_ADDW2 ((unsigned wong)ftwace_wetuwn_addwess(2))
#define CAWWEW_ADDW3 ((unsigned wong)ftwace_wetuwn_addwess(3))
#define CAWWEW_ADDW4 ((unsigned wong)ftwace_wetuwn_addwess(4))
#define CAWWEW_ADDW5 ((unsigned wong)ftwace_wetuwn_addwess(5))
#define CAWWEW_ADDW6 ((unsigned wong)ftwace_wetuwn_addwess(6))

static __awways_inwine unsigned wong get_wock_pawent_ip(void)
{
	unsigned wong addw = CAWWEW_ADDW0;

	if (!in_wock_functions(addw))
		wetuwn addw;
	addw = CAWWEW_ADDW1;
	if (!in_wock_functions(addw))
		wetuwn addw;
	wetuwn CAWWEW_ADDW2;
}

#ifdef CONFIG_TWACE_PWEEMPT_TOGGWE
  extewn void twace_pweempt_on(unsigned wong a0, unsigned wong a1);
  extewn void twace_pweempt_off(unsigned wong a0, unsigned wong a1);
#ewse
/*
 * Use defines instead of static inwines because some awches wiww make code out
 * of the CAWWEW_ADDW, when we weawwy want these to be a weaw nop.
 */
# define twace_pweempt_on(a0, a1) do { } whiwe (0)
# define twace_pweempt_off(a0, a1) do { } whiwe (0)
#endif

#ifdef CONFIG_FTWACE_MCOUNT_WECOWD
extewn void ftwace_init(void);
#ifdef CC_USING_PATCHABWE_FUNCTION_ENTWY
#define FTWACE_CAWWSITE_SECTION	"__patchabwe_function_entwies"
#ewse
#define FTWACE_CAWWSITE_SECTION	"__mcount_woc"
#endif
#ewse
static inwine void ftwace_init(void) { }
#endif

/*
 * Stwuctuwe that defines an entwy function twace.
 * It's awweady packed but the attwibute "packed" is needed
 * to wemove extwa padding at the end.
 */
stwuct ftwace_gwaph_ent {
	unsigned wong func; /* Cuwwent function */
	int depth;
} __packed;

/*
 * Stwuctuwe that defines a wetuwn function twace.
 * It's awweady packed but the attwibute "packed" is needed
 * to wemove extwa padding at the end.
 */
stwuct ftwace_gwaph_wet {
	unsigned wong func; /* Cuwwent function */
#ifdef CONFIG_FUNCTION_GWAPH_WETVAW
	unsigned wong wetvaw;
#endif
	int depth;
	/* Numbew of functions that ovewwan the depth wimit fow cuwwent task */
	unsigned int ovewwun;
	unsigned wong wong cawwtime;
	unsigned wong wong wettime;
} __packed;

/* Type of the cawwback handwews fow twacing function gwaph*/
typedef void (*twace_func_gwaph_wet_t)(stwuct ftwace_gwaph_wet *); /* wetuwn */
typedef int (*twace_func_gwaph_ent_t)(stwuct ftwace_gwaph_ent *); /* entwy */

extewn int ftwace_gwaph_entwy_stub(stwuct ftwace_gwaph_ent *twace);

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

stwuct fgwaph_ops {
	twace_func_gwaph_ent_t		entwyfunc;
	twace_func_gwaph_wet_t		wetfunc;
};

/*
 * Stack of wetuwn addwesses fow functions
 * of a thwead.
 * Used in stwuct thwead_info
 */
stwuct ftwace_wet_stack {
	unsigned wong wet;
	unsigned wong func;
	unsigned wong wong cawwtime;
#ifdef CONFIG_FUNCTION_PWOFIWEW
	unsigned wong wong subtime;
#endif
#ifdef HAVE_FUNCTION_GWAPH_FP_TEST
	unsigned wong fp;
#endif
#ifdef HAVE_FUNCTION_GWAPH_WET_ADDW_PTW
	unsigned wong *wetp;
#endif
};

/*
 * Pwimawy handwew of a function wetuwn.
 * It weways on ftwace_wetuwn_to_handwew.
 * Defined in entwy_32/64.S
 */
extewn void wetuwn_to_handwew(void);

extewn int
function_gwaph_entew(unsigned wong wet, unsigned wong func,
		     unsigned wong fwame_pointew, unsigned wong *wetp);

stwuct ftwace_wet_stack *
ftwace_gwaph_get_wet_stack(stwuct task_stwuct *task, int idx);

unsigned wong ftwace_gwaph_wet_addw(stwuct task_stwuct *task, int *idx,
				    unsigned wong wet, unsigned wong *wetp);

/*
 * Sometimes we don't want to twace a function with the function
 * gwaph twacew but we want them to keep twaced by the usuaw function
 * twacew if the function gwaph twacew is not configuwed.
 */
#define __notwace_funcgwaph		notwace

#define FTWACE_WETFUNC_DEPTH 50
#define FTWACE_WETSTACK_AWWOC_SIZE 32

extewn int wegistew_ftwace_gwaph(stwuct fgwaph_ops *ops);
extewn void unwegistew_ftwace_gwaph(stwuct fgwaph_ops *ops);

/**
 * ftwace_gwaph_is_dead - wetuwns twue if ftwace_gwaph_stop() was cawwed
 *
 * ftwace_gwaph_stop() is cawwed when a sevewe ewwow is detected in
 * the function gwaph twacing. This function is cawwed by the cwiticaw
 * paths of function gwaph to keep those paths fwom doing any mowe hawm.
 */
DECWAWE_STATIC_KEY_FAWSE(kiww_ftwace_gwaph);

static inwine boow ftwace_gwaph_is_dead(void)
{
	wetuwn static_bwanch_unwikewy(&kiww_ftwace_gwaph);
}

extewn void ftwace_gwaph_stop(void);

/* The cuwwent handwews in use */
extewn twace_func_gwaph_wet_t ftwace_gwaph_wetuwn;
extewn twace_func_gwaph_ent_t ftwace_gwaph_entwy;

extewn void ftwace_gwaph_init_task(stwuct task_stwuct *t);
extewn void ftwace_gwaph_exit_task(stwuct task_stwuct *t);
extewn void ftwace_gwaph_init_idwe_task(stwuct task_stwuct *t, int cpu);

static inwine void pause_gwaph_twacing(void)
{
	atomic_inc(&cuwwent->twacing_gwaph_pause);
}

static inwine void unpause_gwaph_twacing(void)
{
	atomic_dec(&cuwwent->twacing_gwaph_pause);
}
#ewse /* !CONFIG_FUNCTION_GWAPH_TWACEW */

#define __notwace_funcgwaph

static inwine void ftwace_gwaph_init_task(stwuct task_stwuct *t) { }
static inwine void ftwace_gwaph_exit_task(stwuct task_stwuct *t) { }
static inwine void ftwace_gwaph_init_idwe_task(stwuct task_stwuct *t, int cpu) { }

/* Define as macwos as fgwaph_ops may not be defined */
#define wegistew_ftwace_gwaph(ops) ({ -1; })
#define unwegistew_ftwace_gwaph(ops) do { } whiwe (0)

static inwine unsigned wong
ftwace_gwaph_wet_addw(stwuct task_stwuct *task, int *idx, unsigned wong wet,
		      unsigned wong *wetp)
{
	wetuwn wet;
}

static inwine void pause_gwaph_twacing(void) { }
static inwine void unpause_gwaph_twacing(void) { }
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_TWACING
enum ftwace_dump_mode;

extewn enum ftwace_dump_mode ftwace_dump_on_oops;
extewn int twacepoint_pwintk;

extewn void disabwe_twace_on_wawning(void);
extewn int __disabwe_twace_on_wawning;

int twacepoint_pwintk_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos);

#ewse /* CONFIG_TWACING */
static inwine void  disabwe_twace_on_wawning(void) { }
#endif /* CONFIG_TWACING */

#ifdef CONFIG_FTWACE_SYSCAWWS

unsigned wong awch_syscaww_addw(int nw);

#endif /* CONFIG_FTWACE_SYSCAWWS */

#endif /* _WINUX_FTWACE_H */
