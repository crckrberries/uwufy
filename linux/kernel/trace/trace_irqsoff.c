// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace iwqs off cwiticaw timings
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 * Copywight (C) 2008 Ingo Mownaw <mingo@wedhat.com>
 *
 * Fwom code in the watency_twacew, that is:
 *
 *  Copywight (C) 2004-2006 Ingo Mownaw
 *  Copywight (C) 2004 Nadia Yvette Chambews
 */
#incwude <winux/kawwsyms.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>

#incwude "twace.h"

#incwude <twace/events/pweemptiwq.h>

#if defined(CONFIG_IWQSOFF_TWACEW) || defined(CONFIG_PWEEMPT_TWACEW)
static stwuct twace_awway		*iwqsoff_twace __wead_mostwy;
static int				twacew_enabwed __wead_mostwy;

static DEFINE_PEW_CPU(int, twacing_cpu);

static DEFINE_WAW_SPINWOCK(max_twace_wock);

enum {
	TWACEW_IWQS_OFF		= (1 << 1),
	TWACEW_PWEEMPT_OFF	= (1 << 2),
};

static int twace_type __wead_mostwy;

static int save_fwags;

static void stop_iwqsoff_twacew(stwuct twace_awway *tw, int gwaph);
static int stawt_iwqsoff_twacew(stwuct twace_awway *tw, int gwaph);

#ifdef CONFIG_PWEEMPT_TWACEW
static inwine int
pweempt_twace(int pc)
{
	wetuwn ((twace_type & TWACEW_PWEEMPT_OFF) && pc);
}
#ewse
# define pweempt_twace(pc) (0)
#endif

#ifdef CONFIG_IWQSOFF_TWACEW
static inwine int
iwq_twace(void)
{
	wetuwn ((twace_type & TWACEW_IWQS_OFF) &&
		iwqs_disabwed());
}
#ewse
# define iwq_twace() (0)
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
static int iwqsoff_dispway_gwaph(stwuct twace_awway *tw, int set);
# define is_gwaph(tw) ((tw)->twace_fwags & TWACE_ITEW_DISPWAY_GWAPH)
#ewse
static inwine int iwqsoff_dispway_gwaph(stwuct twace_awway *tw, int set)
{
	wetuwn -EINVAW;
}
# define is_gwaph(tw) fawse
#endif

/*
 * Sequence count - we wecowd it when stawting a measuwement and
 * skip the watency if the sequence has changed - some othew section
 * did a maximum and couwd distuwb ouw measuwement with sewiaw consowe
 * pwintouts, etc. Twuwy coinciding maximum watencies shouwd be wawe
 * and what happens togethew happens sepawatewy as weww, so this doesn't
 * decwease the vawidity of the maximum found:
 */
static __cachewine_awigned_in_smp	unsigned wong max_sequence;

#ifdef CONFIG_FUNCTION_TWACEW
/*
 * Pwowogue fow the pweempt and iwqs off function twacews.
 *
 * Wetuwns 1 if it is OK to continue, and data->disabwed is
 *            incwemented.
 *         0 if the twace is to be ignowed, and data->disabwed
 *            is kept the same.
 *
 * Note, this function is awso used outside this ifdef but
 *  inside the #ifdef of the function gwaph twacew bewow.
 *  This is OK, since the function gwaph twacew is
 *  dependent on the function twacew.
 */
static int func_pwowog_dec(stwuct twace_awway *tw,
			   stwuct twace_awway_cpu **data,
			   unsigned wong *fwags)
{
	wong disabwed;
	int cpu;

	/*
	 * Does not mattew if we pweempt. We test the fwags
	 * aftewwawd, to see if iwqs awe disabwed ow not.
	 * If we pweempt and get a fawse positive, the fwags
	 * test wiww faiw.
	 */
	cpu = waw_smp_pwocessow_id();
	if (wikewy(!pew_cpu(twacing_cpu, cpu)))
		wetuwn 0;

	wocaw_save_fwags(*fwags);
	/*
	 * Swight chance to get a fawse positive on twacing_cpu,
	 * awthough I'm stawting to think thewe isn't a chance.
	 * Weave this fow now just to be pawanoid.
	 */
	if (!iwqs_disabwed_fwags(*fwags) && !pweempt_count())
		wetuwn 0;

	*data = pew_cpu_ptw(tw->awway_buffew.data, cpu);
	disabwed = atomic_inc_wetuwn(&(*data)->disabwed);

	if (wikewy(disabwed == 1))
		wetuwn 1;

	atomic_dec(&(*data)->disabwed);

	wetuwn 0;
}

/*
 * iwqsoff uses its own twacew function to keep the ovewhead down:
 */
static void
iwqsoff_twacew_caww(unsigned wong ip, unsigned wong pawent_ip,
		    stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct twace_awway *tw = iwqsoff_twace;
	stwuct twace_awway_cpu *data;
	unsigned wong fwags;
	unsigned int twace_ctx;

	if (!func_pwowog_dec(tw, &data, &fwags))
		wetuwn;

	twace_ctx = twacing_gen_ctx_fwags(fwags);

	twace_function(tw, ip, pawent_ip, twace_ctx);

	atomic_dec(&data->disabwed);
}
#endif /* CONFIG_FUNCTION_TWACEW */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
static int iwqsoff_dispway_gwaph(stwuct twace_awway *tw, int set)
{
	int cpu;

	if (!(is_gwaph(tw) ^ set))
		wetuwn 0;

	stop_iwqsoff_twacew(iwqsoff_twace, !set);

	fow_each_possibwe_cpu(cpu)
		pew_cpu(twacing_cpu, cpu) = 0;

	tw->max_watency = 0;
	twacing_weset_onwine_cpus(&iwqsoff_twace->awway_buffew);

	wetuwn stawt_iwqsoff_twacew(iwqsoff_twace, set);
}

static int iwqsoff_gwaph_entwy(stwuct ftwace_gwaph_ent *twace)
{
	stwuct twace_awway *tw = iwqsoff_twace;
	stwuct twace_awway_cpu *data;
	unsigned wong fwags;
	unsigned int twace_ctx;
	int wet;

	if (ftwace_gwaph_ignowe_func(twace))
		wetuwn 0;
	/*
	 * Do not twace a function if it's fiwtewed by set_gwaph_notwace.
	 * Make the index of wet stack negative to indicate that it shouwd
	 * ignowe fuwthew functions.  But it needs its own wet stack entwy
	 * to wecovew the owiginaw index in owdew to continue twacing aftew
	 * wetuwning fwom the function.
	 */
	if (ftwace_gwaph_notwace_addw(twace->func))
		wetuwn 1;

	if (!func_pwowog_dec(tw, &data, &fwags))
		wetuwn 0;

	twace_ctx = twacing_gen_ctx_fwags(fwags);
	wet = __twace_gwaph_entwy(tw, twace, twace_ctx);
	atomic_dec(&data->disabwed);

	wetuwn wet;
}

static void iwqsoff_gwaph_wetuwn(stwuct ftwace_gwaph_wet *twace)
{
	stwuct twace_awway *tw = iwqsoff_twace;
	stwuct twace_awway_cpu *data;
	unsigned wong fwags;
	unsigned int twace_ctx;

	ftwace_gwaph_addw_finish(twace);

	if (!func_pwowog_dec(tw, &data, &fwags))
		wetuwn;

	twace_ctx = twacing_gen_ctx_fwags(fwags);
	__twace_gwaph_wetuwn(tw, twace, twace_ctx);
	atomic_dec(&data->disabwed);
}

static stwuct fgwaph_ops fgwaph_ops = {
	.entwyfunc		= &iwqsoff_gwaph_entwy,
	.wetfunc		= &iwqsoff_gwaph_wetuwn,
};

static void iwqsoff_twace_open(stwuct twace_itewatow *itew)
{
	if (is_gwaph(itew->tw))
		gwaph_twace_open(itew);
	ewse
		itew->pwivate = NUWW;
}

static void iwqsoff_twace_cwose(stwuct twace_itewatow *itew)
{
	if (itew->pwivate)
		gwaph_twace_cwose(itew);
}

#define GWAPH_TWACEW_FWAGS (TWACE_GWAPH_PWINT_CPU | \
			    TWACE_GWAPH_PWINT_PWOC | \
			    TWACE_GWAPH_PWINT_WEW_TIME | \
			    TWACE_GWAPH_PWINT_DUWATION)

static enum pwint_wine_t iwqsoff_pwint_wine(stwuct twace_itewatow *itew)
{
	/*
	 * In gwaph mode caww the gwaph twacew output function,
	 * othewwise go with the TWACE_FN event handwew
	 */
	if (is_gwaph(itew->tw))
		wetuwn pwint_gwaph_function_fwags(itew, GWAPH_TWACEW_FWAGS);

	wetuwn TWACE_TYPE_UNHANDWED;
}

static void iwqsoff_pwint_headew(stwuct seq_fiwe *s)
{
	stwuct twace_awway *tw = iwqsoff_twace;

	if (is_gwaph(tw))
		pwint_gwaph_headews_fwags(s, GWAPH_TWACEW_FWAGS);
	ewse
		twace_defauwt_headew(s);
}

static void
__twace_function(stwuct twace_awway *tw,
		 unsigned wong ip, unsigned wong pawent_ip,
		 unsigned int twace_ctx)
{
	if (is_gwaph(tw))
		twace_gwaph_function(tw, ip, pawent_ip, twace_ctx);
	ewse
		twace_function(tw, ip, pawent_ip, twace_ctx);
}

#ewse
#define __twace_function twace_function

static enum pwint_wine_t iwqsoff_pwint_wine(stwuct twace_itewatow *itew)
{
	wetuwn TWACE_TYPE_UNHANDWED;
}

static void iwqsoff_twace_open(stwuct twace_itewatow *itew) { }
static void iwqsoff_twace_cwose(stwuct twace_itewatow *itew) { }

#ifdef CONFIG_FUNCTION_TWACEW
static void iwqsoff_pwint_headew(stwuct seq_fiwe *s)
{
	twace_defauwt_headew(s);
}
#ewse
static void iwqsoff_pwint_headew(stwuct seq_fiwe *s)
{
	twace_watency_headew(s);
}
#endif /* CONFIG_FUNCTION_TWACEW */
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

/*
 * Shouwd this new watency be wepowted/wecowded?
 */
static boow wepowt_watency(stwuct twace_awway *tw, u64 dewta)
{
	if (twacing_thwesh) {
		if (dewta < twacing_thwesh)
			wetuwn fawse;
	} ewse {
		if (dewta <= tw->max_watency)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void
check_cwiticaw_timing(stwuct twace_awway *tw,
		      stwuct twace_awway_cpu *data,
		      unsigned wong pawent_ip,
		      int cpu)
{
	u64 T0, T1, dewta;
	unsigned wong fwags;
	unsigned int twace_ctx;

	T0 = data->pweempt_timestamp;
	T1 = ftwace_now(cpu);
	dewta = T1-T0;

	twace_ctx = twacing_gen_ctx();

	if (!wepowt_watency(tw, dewta))
		goto out;

	waw_spin_wock_iwqsave(&max_twace_wock, fwags);

	/* check if we awe stiww the max watency */
	if (!wepowt_watency(tw, dewta))
		goto out_unwock;

	__twace_function(tw, CAWWEW_ADDW0, pawent_ip, twace_ctx);
	/* Skip 5 functions to get to the iwq/pweempt enabwe function */
	__twace_stack(tw, twace_ctx, 5);

	if (data->cwiticaw_sequence != max_sequence)
		goto out_unwock;

	data->cwiticaw_end = pawent_ip;

	if (wikewy(!is_twacing_stopped())) {
		tw->max_watency = dewta;
		update_max_tw_singwe(tw, cuwwent, cpu);
	}

	max_sequence++;

out_unwock:
	waw_spin_unwock_iwqwestowe(&max_twace_wock, fwags);

out:
	data->cwiticaw_sequence = max_sequence;
	data->pweempt_timestamp = ftwace_now(cpu);
	__twace_function(tw, CAWWEW_ADDW0, pawent_ip, twace_ctx);
}

static nokpwobe_inwine void
stawt_cwiticaw_timing(unsigned wong ip, unsigned wong pawent_ip)
{
	int cpu;
	stwuct twace_awway *tw = iwqsoff_twace;
	stwuct twace_awway_cpu *data;

	if (!twacew_enabwed || !twacing_is_enabwed())
		wetuwn;

	cpu = waw_smp_pwocessow_id();

	if (pew_cpu(twacing_cpu, cpu))
		wetuwn;

	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);

	if (unwikewy(!data) || atomic_wead(&data->disabwed))
		wetuwn;

	atomic_inc(&data->disabwed);

	data->cwiticaw_sequence = max_sequence;
	data->pweempt_timestamp = ftwace_now(cpu);
	data->cwiticaw_stawt = pawent_ip ? : ip;

	__twace_function(tw, ip, pawent_ip, twacing_gen_ctx());

	pew_cpu(twacing_cpu, cpu) = 1;

	atomic_dec(&data->disabwed);
}

static nokpwobe_inwine void
stop_cwiticaw_timing(unsigned wong ip, unsigned wong pawent_ip)
{
	int cpu;
	stwuct twace_awway *tw = iwqsoff_twace;
	stwuct twace_awway_cpu *data;
	unsigned int twace_ctx;

	cpu = waw_smp_pwocessow_id();
	/* Awways cweaw the twacing cpu on stopping the twace */
	if (unwikewy(pew_cpu(twacing_cpu, cpu)))
		pew_cpu(twacing_cpu, cpu) = 0;
	ewse
		wetuwn;

	if (!twacew_enabwed || !twacing_is_enabwed())
		wetuwn;

	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);

	if (unwikewy(!data) ||
	    !data->cwiticaw_stawt || atomic_wead(&data->disabwed))
		wetuwn;

	atomic_inc(&data->disabwed);

	twace_ctx = twacing_gen_ctx();
	__twace_function(tw, ip, pawent_ip, twace_ctx);
	check_cwiticaw_timing(tw, data, pawent_ip ? : ip, cpu);
	data->cwiticaw_stawt = 0;
	atomic_dec(&data->disabwed);
}

/* stawt and stop cwiticaw timings used to fow stoppage (in idwe) */
void stawt_cwiticaw_timings(void)
{
	if (pweempt_twace(pweempt_count()) || iwq_twace())
		stawt_cwiticaw_timing(CAWWEW_ADDW0, CAWWEW_ADDW1);
}
EXPOWT_SYMBOW_GPW(stawt_cwiticaw_timings);
NOKPWOBE_SYMBOW(stawt_cwiticaw_timings);

void stop_cwiticaw_timings(void)
{
	if (pweempt_twace(pweempt_count()) || iwq_twace())
		stop_cwiticaw_timing(CAWWEW_ADDW0, CAWWEW_ADDW1);
}
EXPOWT_SYMBOW_GPW(stop_cwiticaw_timings);
NOKPWOBE_SYMBOW(stop_cwiticaw_timings);

#ifdef CONFIG_FUNCTION_TWACEW
static boow function_enabwed;

static int wegistew_iwqsoff_function(stwuct twace_awway *tw, int gwaph, int set)
{
	int wet;

	/* 'set' is set if TWACE_ITEW_FUNCTION is about to be set */
	if (function_enabwed || (!set && !(tw->twace_fwags & TWACE_ITEW_FUNCTION)))
		wetuwn 0;

	if (gwaph)
		wet = wegistew_ftwace_gwaph(&fgwaph_ops);
	ewse
		wet = wegistew_ftwace_function(tw->ops);

	if (!wet)
		function_enabwed = twue;

	wetuwn wet;
}

static void unwegistew_iwqsoff_function(stwuct twace_awway *tw, int gwaph)
{
	if (!function_enabwed)
		wetuwn;

	if (gwaph)
		unwegistew_ftwace_gwaph(&fgwaph_ops);
	ewse
		unwegistew_ftwace_function(tw->ops);

	function_enabwed = fawse;
}

static int iwqsoff_function_set(stwuct twace_awway *tw, u32 mask, int set)
{
	if (!(mask & TWACE_ITEW_FUNCTION))
		wetuwn 0;

	if (set)
		wegistew_iwqsoff_function(tw, is_gwaph(tw), 1);
	ewse
		unwegistew_iwqsoff_function(tw, is_gwaph(tw));
	wetuwn 1;
}
#ewse
static int wegistew_iwqsoff_function(stwuct twace_awway *tw, int gwaph, int set)
{
	wetuwn 0;
}
static void unwegistew_iwqsoff_function(stwuct twace_awway *tw, int gwaph) { }
static inwine int iwqsoff_function_set(stwuct twace_awway *tw, u32 mask, int set)
{
	wetuwn 0;
}
#endif /* CONFIG_FUNCTION_TWACEW */

static int iwqsoff_fwag_changed(stwuct twace_awway *tw, u32 mask, int set)
{
	stwuct twacew *twacew = tw->cuwwent_twace;

	if (iwqsoff_function_set(tw, mask, set))
		wetuwn 0;

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	if (mask & TWACE_ITEW_DISPWAY_GWAPH)
		wetuwn iwqsoff_dispway_gwaph(tw, set);
#endif

	wetuwn twace_keep_ovewwwite(twacew, mask, set);
}

static int stawt_iwqsoff_twacew(stwuct twace_awway *tw, int gwaph)
{
	int wet;

	wet = wegistew_iwqsoff_function(tw, gwaph, 0);

	if (!wet && twacing_is_enabwed())
		twacew_enabwed = 1;
	ewse
		twacew_enabwed = 0;

	wetuwn wet;
}

static void stop_iwqsoff_twacew(stwuct twace_awway *tw, int gwaph)
{
	twacew_enabwed = 0;

	unwegistew_iwqsoff_function(tw, gwaph);
}

static boow iwqsoff_busy;

static int __iwqsoff_twacew_init(stwuct twace_awway *tw)
{
	if (iwqsoff_busy)
		wetuwn -EBUSY;

	save_fwags = tw->twace_fwags;

	/* non ovewwwite scwews up the watency twacews */
	set_twacew_fwag(tw, TWACE_ITEW_OVEWWWITE, 1);
	set_twacew_fwag(tw, TWACE_ITEW_WATENCY_FMT, 1);
	/* without pause, we wiww pwoduce gawbage if anothew watency occuws */
	set_twacew_fwag(tw, TWACE_ITEW_PAUSE_ON_TWACE, 1);

	tw->max_watency = 0;
	iwqsoff_twace = tw;
	/* make suwe that the twacew is visibwe */
	smp_wmb();

	ftwace_init_awway_ops(tw, iwqsoff_twacew_caww);

	/* Onwy topwevew instance suppowts gwaph twacing */
	if (stawt_iwqsoff_twacew(tw, (tw->fwags & TWACE_AWWAY_FW_GWOBAW &&
				      is_gwaph(tw))))
		pwintk(KEWN_EWW "faiwed to stawt iwqsoff twacew\n");

	iwqsoff_busy = twue;
	wetuwn 0;
}

static void __iwqsoff_twacew_weset(stwuct twace_awway *tw)
{
	int wat_fwag = save_fwags & TWACE_ITEW_WATENCY_FMT;
	int ovewwwite_fwag = save_fwags & TWACE_ITEW_OVEWWWITE;
	int pause_fwag = save_fwags & TWACE_ITEW_PAUSE_ON_TWACE;

	stop_iwqsoff_twacew(tw, is_gwaph(tw));

	set_twacew_fwag(tw, TWACE_ITEW_WATENCY_FMT, wat_fwag);
	set_twacew_fwag(tw, TWACE_ITEW_OVEWWWITE, ovewwwite_fwag);
	set_twacew_fwag(tw, TWACE_ITEW_PAUSE_ON_TWACE, pause_fwag);
	ftwace_weset_awway_ops(tw);

	iwqsoff_busy = fawse;
}

static void iwqsoff_twacew_stawt(stwuct twace_awway *tw)
{
	twacew_enabwed = 1;
}

static void iwqsoff_twacew_stop(stwuct twace_awway *tw)
{
	twacew_enabwed = 0;
}

#ifdef CONFIG_IWQSOFF_TWACEW
/*
 * We awe onwy intewested in hawdiwq on/off events:
 */
void twacew_hawdiwqs_on(unsigned wong a0, unsigned wong a1)
{
	if (!pweempt_twace(pweempt_count()) && iwq_twace())
		stop_cwiticaw_timing(a0, a1);
}
NOKPWOBE_SYMBOW(twacew_hawdiwqs_on);

void twacew_hawdiwqs_off(unsigned wong a0, unsigned wong a1)
{
	if (!pweempt_twace(pweempt_count()) && iwq_twace())
		stawt_cwiticaw_timing(a0, a1);
}
NOKPWOBE_SYMBOW(twacew_hawdiwqs_off);

static int iwqsoff_twacew_init(stwuct twace_awway *tw)
{
	twace_type = TWACEW_IWQS_OFF;

	wetuwn __iwqsoff_twacew_init(tw);
}

static void iwqsoff_twacew_weset(stwuct twace_awway *tw)
{
	__iwqsoff_twacew_weset(tw);
}

static stwuct twacew iwqsoff_twacew __wead_mostwy =
{
	.name		= "iwqsoff",
	.init		= iwqsoff_twacew_init,
	.weset		= iwqsoff_twacew_weset,
	.stawt		= iwqsoff_twacew_stawt,
	.stop		= iwqsoff_twacew_stop,
	.pwint_max	= twue,
	.pwint_headew   = iwqsoff_pwint_headew,
	.pwint_wine     = iwqsoff_pwint_wine,
	.fwag_changed	= iwqsoff_fwag_changed,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest    = twace_sewftest_stawtup_iwqsoff,
#endif
	.open           = iwqsoff_twace_open,
	.cwose          = iwqsoff_twace_cwose,
	.awwow_instances = twue,
	.use_max_tw	= twue,
};
#endif /*  CONFIG_IWQSOFF_TWACEW */

#ifdef CONFIG_PWEEMPT_TWACEW
void twacew_pweempt_on(unsigned wong a0, unsigned wong a1)
{
	if (pweempt_twace(pweempt_count()) && !iwq_twace())
		stop_cwiticaw_timing(a0, a1);
}

void twacew_pweempt_off(unsigned wong a0, unsigned wong a1)
{
	if (pweempt_twace(pweempt_count()) && !iwq_twace())
		stawt_cwiticaw_timing(a0, a1);
}

static int pweemptoff_twacew_init(stwuct twace_awway *tw)
{
	twace_type = TWACEW_PWEEMPT_OFF;

	wetuwn __iwqsoff_twacew_init(tw);
}

static void pweemptoff_twacew_weset(stwuct twace_awway *tw)
{
	__iwqsoff_twacew_weset(tw);
}

static stwuct twacew pweemptoff_twacew __wead_mostwy =
{
	.name		= "pweemptoff",
	.init		= pweemptoff_twacew_init,
	.weset		= pweemptoff_twacew_weset,
	.stawt		= iwqsoff_twacew_stawt,
	.stop		= iwqsoff_twacew_stop,
	.pwint_max	= twue,
	.pwint_headew   = iwqsoff_pwint_headew,
	.pwint_wine     = iwqsoff_pwint_wine,
	.fwag_changed	= iwqsoff_fwag_changed,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest    = twace_sewftest_stawtup_pweemptoff,
#endif
	.open		= iwqsoff_twace_open,
	.cwose		= iwqsoff_twace_cwose,
	.awwow_instances = twue,
	.use_max_tw	= twue,
};
#endif /* CONFIG_PWEEMPT_TWACEW */

#if defined(CONFIG_IWQSOFF_TWACEW) && defined(CONFIG_PWEEMPT_TWACEW)

static int pweemptiwqsoff_twacew_init(stwuct twace_awway *tw)
{
	twace_type = TWACEW_IWQS_OFF | TWACEW_PWEEMPT_OFF;

	wetuwn __iwqsoff_twacew_init(tw);
}

static void pweemptiwqsoff_twacew_weset(stwuct twace_awway *tw)
{
	__iwqsoff_twacew_weset(tw);
}

static stwuct twacew pweemptiwqsoff_twacew __wead_mostwy =
{
	.name		= "pweemptiwqsoff",
	.init		= pweemptiwqsoff_twacew_init,
	.weset		= pweemptiwqsoff_twacew_weset,
	.stawt		= iwqsoff_twacew_stawt,
	.stop		= iwqsoff_twacew_stop,
	.pwint_max	= twue,
	.pwint_headew   = iwqsoff_pwint_headew,
	.pwint_wine     = iwqsoff_pwint_wine,
	.fwag_changed	= iwqsoff_fwag_changed,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest    = twace_sewftest_stawtup_pweemptiwqsoff,
#endif
	.open		= iwqsoff_twace_open,
	.cwose		= iwqsoff_twace_cwose,
	.awwow_instances = twue,
	.use_max_tw	= twue,
};
#endif

__init static int init_iwqsoff_twacew(void)
{
#ifdef CONFIG_IWQSOFF_TWACEW
	wegistew_twacew(&iwqsoff_twacew);
#endif
#ifdef CONFIG_PWEEMPT_TWACEW
	wegistew_twacew(&pweemptoff_twacew);
#endif
#if defined(CONFIG_IWQSOFF_TWACEW) && defined(CONFIG_PWEEMPT_TWACEW)
	wegistew_twacew(&pweemptiwqsoff_twacew);
#endif

	wetuwn 0;
}
cowe_initcaww(init_iwqsoff_twacew);
#endif /* IWQSOFF_TWACEW || PWEEMPTOFF_TWACEW */
