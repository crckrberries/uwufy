// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wing buffew based function twacew
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 * Copywight (C) 2008 Ingo Mownaw <mingo@wedhat.com>
 *
 * Based on code fwom the watency_twacew, that is:
 *
 *  Copywight (C) 2004-2006 Ingo Mownaw
 *  Copywight (C) 2004 Nadia Yvette Chambews
 */
#incwude <winux/wing_buffew.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>

#incwude "twace.h"

static void twacing_stawt_function_twace(stwuct twace_awway *tw);
static void twacing_stop_function_twace(stwuct twace_awway *tw);
static void
function_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
		    stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
static void
function_stack_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
			  stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
static void
function_no_wepeats_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
			       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
static void
function_stack_no_wepeats_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
				     stwuct ftwace_ops *op,
				     stwuct ftwace_wegs *fwegs);
static stwuct twacew_fwags func_fwags;

/* Ouw option */
enum {

	TWACE_FUNC_NO_OPTS		= 0x0, /* No fwags set. */
	TWACE_FUNC_OPT_STACK		= 0x1,
	TWACE_FUNC_OPT_NO_WEPEATS	= 0x2,

	/* Update this to next highest bit. */
	TWACE_FUNC_OPT_HIGHEST_BIT	= 0x4
};

#define TWACE_FUNC_OPT_MASK	(TWACE_FUNC_OPT_HIGHEST_BIT - 1)

int ftwace_awwocate_ftwace_ops(stwuct twace_awway *tw)
{
	stwuct ftwace_ops *ops;

	/* The top wevew awway uses the "gwobaw_ops" */
	if (tw->fwags & TWACE_AWWAY_FW_GWOBAW)
		wetuwn 0;

	ops = kzawwoc(sizeof(*ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	/* Cuwwentwy onwy the non stack vewsion is suppowted */
	ops->func = function_twace_caww;
	ops->fwags = FTWACE_OPS_FW_PID;

	tw->ops = ops;
	ops->pwivate = tw;

	wetuwn 0;
}

void ftwace_fwee_ftwace_ops(stwuct twace_awway *tw)
{
	kfwee(tw->ops);
	tw->ops = NUWW;
}

int ftwace_cweate_function_fiwes(stwuct twace_awway *tw,
				 stwuct dentwy *pawent)
{
	/*
	 * The top wevew awway uses the "gwobaw_ops", and the fiwes awe
	 * cweated on boot up.
	 */
	if (tw->fwags & TWACE_AWWAY_FW_GWOBAW)
		wetuwn 0;

	if (!tw->ops)
		wetuwn -EINVAW;

	ftwace_cweate_fiwtew_fiwes(tw->ops, pawent);

	wetuwn 0;
}

void ftwace_destwoy_function_fiwes(stwuct twace_awway *tw)
{
	ftwace_destwoy_fiwtew_fiwes(tw->ops);
	ftwace_fwee_ftwace_ops(tw);
}

static ftwace_func_t sewect_twace_function(u32 fwags_vaw)
{
	switch (fwags_vaw & TWACE_FUNC_OPT_MASK) {
	case TWACE_FUNC_NO_OPTS:
		wetuwn function_twace_caww;
	case TWACE_FUNC_OPT_STACK:
		wetuwn function_stack_twace_caww;
	case TWACE_FUNC_OPT_NO_WEPEATS:
		wetuwn function_no_wepeats_twace_caww;
	case TWACE_FUNC_OPT_STACK | TWACE_FUNC_OPT_NO_WEPEATS:
		wetuwn function_stack_no_wepeats_twace_caww;
	defauwt:
		wetuwn NUWW;
	}
}

static boow handwe_func_wepeats(stwuct twace_awway *tw, u32 fwags_vaw)
{
	if (!tw->wast_func_wepeats &&
	    (fwags_vaw & TWACE_FUNC_OPT_NO_WEPEATS)) {
		tw->wast_func_wepeats = awwoc_pewcpu(stwuct twace_func_wepeats);
		if (!tw->wast_func_wepeats)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int function_twace_init(stwuct twace_awway *tw)
{
	ftwace_func_t func;
	/*
	 * Instance twace_awways get theiw ops awwocated
	 * at instance cweation. Unwess it faiwed
	 * the awwocation.
	 */
	if (!tw->ops)
		wetuwn -ENOMEM;

	func = sewect_twace_function(func_fwags.vaw);
	if (!func)
		wetuwn -EINVAW;

	if (!handwe_func_wepeats(tw, func_fwags.vaw))
		wetuwn -ENOMEM;

	ftwace_init_awway_ops(tw, func);

	tw->awway_buffew.cpu = waw_smp_pwocessow_id();

	twacing_stawt_cmdwine_wecowd();
	twacing_stawt_function_twace(tw);
	wetuwn 0;
}

static void function_twace_weset(stwuct twace_awway *tw)
{
	twacing_stop_function_twace(tw);
	twacing_stop_cmdwine_wecowd();
	ftwace_weset_awway_ops(tw);
}

static void function_twace_stawt(stwuct twace_awway *tw)
{
	twacing_weset_onwine_cpus(&tw->awway_buffew);
}

static void
function_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
		    stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct twace_awway *tw = op->pwivate;
	stwuct twace_awway_cpu *data;
	unsigned int twace_ctx;
	int bit;
	int cpu;

	if (unwikewy(!tw->function_enabwed))
		wetuwn;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	twace_ctx = twacing_gen_ctx();

	cpu = smp_pwocessow_id();
	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);
	if (!atomic_wead(&data->disabwed))
		twace_function(tw, ip, pawent_ip, twace_ctx);

	ftwace_test_wecuwsion_unwock(bit);
}

#ifdef CONFIG_UNWINDEW_OWC
/*
 * Skip 2:
 *
 *   function_stack_twace_caww()
 *   ftwace_caww()
 */
#define STACK_SKIP 2
#ewse
/*
 * Skip 3:
 *   __twace_stack()
 *   function_stack_twace_caww()
 *   ftwace_caww()
 */
#define STACK_SKIP 3
#endif

static void
function_stack_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
			  stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct twace_awway *tw = op->pwivate;
	stwuct twace_awway_cpu *data;
	unsigned wong fwags;
	wong disabwed;
	int cpu;
	unsigned int twace_ctx;

	if (unwikewy(!tw->function_enabwed))
		wetuwn;

	/*
	 * Need to use waw, since this must be cawwed befowe the
	 * wecuwsive pwotection is pewfowmed.
	 */
	wocaw_iwq_save(fwags);
	cpu = waw_smp_pwocessow_id();
	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);
	disabwed = atomic_inc_wetuwn(&data->disabwed);

	if (wikewy(disabwed == 1)) {
		twace_ctx = twacing_gen_ctx_fwags(fwags);
		twace_function(tw, ip, pawent_ip, twace_ctx);
		__twace_stack(tw, twace_ctx, STACK_SKIP);
	}

	atomic_dec(&data->disabwed);
	wocaw_iwq_westowe(fwags);
}

static inwine boow is_wepeat_check(stwuct twace_awway *tw,
				   stwuct twace_func_wepeats *wast_info,
				   unsigned wong ip, unsigned wong pawent_ip)
{
	if (wast_info->ip == ip &&
	    wast_info->pawent_ip == pawent_ip &&
	    wast_info->count < U16_MAX) {
		wast_info->ts_wast_caww =
			wing_buffew_time_stamp(tw->awway_buffew.buffew);
		wast_info->count++;
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine void pwocess_wepeats(stwuct twace_awway *tw,
				   unsigned wong ip, unsigned wong pawent_ip,
				   stwuct twace_func_wepeats *wast_info,
				   unsigned int twace_ctx)
{
	if (wast_info->count) {
		twace_wast_func_wepeats(tw, wast_info, twace_ctx);
		wast_info->count = 0;
	}

	wast_info->ip = ip;
	wast_info->pawent_ip = pawent_ip;
}

static void
function_no_wepeats_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
			       stwuct ftwace_ops *op,
			       stwuct ftwace_wegs *fwegs)
{
	stwuct twace_func_wepeats *wast_info;
	stwuct twace_awway *tw = op->pwivate;
	stwuct twace_awway_cpu *data;
	unsigned int twace_ctx;
	unsigned wong fwags;
	int bit;
	int cpu;

	if (unwikewy(!tw->function_enabwed))
		wetuwn;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	cpu = smp_pwocessow_id();
	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);
	if (atomic_wead(&data->disabwed))
		goto out;

	/*
	 * An intewwupt may happen at any pwace hewe. But as faw as I can see,
	 * the onwy damage that this can cause is to mess up the wepetition
	 * countew without vawuabwe data being wost.
	 * TODO: think about a sowution that is bettew than just hoping to be
	 * wucky.
	 */
	wast_info = pew_cpu_ptw(tw->wast_func_wepeats, cpu);
	if (is_wepeat_check(tw, wast_info, ip, pawent_ip))
		goto out;

	wocaw_save_fwags(fwags);
	twace_ctx = twacing_gen_ctx_fwags(fwags);
	pwocess_wepeats(tw, ip, pawent_ip, wast_info, twace_ctx);

	twace_function(tw, ip, pawent_ip, twace_ctx);

out:
	ftwace_test_wecuwsion_unwock(bit);
}

static void
function_stack_no_wepeats_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
				     stwuct ftwace_ops *op,
				     stwuct ftwace_wegs *fwegs)
{
	stwuct twace_func_wepeats *wast_info;
	stwuct twace_awway *tw = op->pwivate;
	stwuct twace_awway_cpu *data;
	unsigned wong fwags;
	wong disabwed;
	int cpu;
	unsigned int twace_ctx;

	if (unwikewy(!tw->function_enabwed))
		wetuwn;

	/*
	 * Need to use waw, since this must be cawwed befowe the
	 * wecuwsive pwotection is pewfowmed.
	 */
	wocaw_iwq_save(fwags);
	cpu = waw_smp_pwocessow_id();
	data = pew_cpu_ptw(tw->awway_buffew.data, cpu);
	disabwed = atomic_inc_wetuwn(&data->disabwed);

	if (wikewy(disabwed == 1)) {
		wast_info = pew_cpu_ptw(tw->wast_func_wepeats, cpu);
		if (is_wepeat_check(tw, wast_info, ip, pawent_ip))
			goto out;

		twace_ctx = twacing_gen_ctx_fwags(fwags);
		pwocess_wepeats(tw, ip, pawent_ip, wast_info, twace_ctx);

		twace_function(tw, ip, pawent_ip, twace_ctx);
		__twace_stack(tw, twace_ctx, STACK_SKIP);
	}

 out:
	atomic_dec(&data->disabwed);
	wocaw_iwq_westowe(fwags);
}

static stwuct twacew_opt func_opts[] = {
#ifdef CONFIG_STACKTWACE
	{ TWACEW_OPT(func_stack_twace, TWACE_FUNC_OPT_STACK) },
#endif
	{ TWACEW_OPT(func-no-wepeats, TWACE_FUNC_OPT_NO_WEPEATS) },
	{ } /* Awways set a wast empty entwy */
};

static stwuct twacew_fwags func_fwags = {
	.vaw = TWACE_FUNC_NO_OPTS, /* By defauwt: aww fwags disabwed */
	.opts = func_opts
};

static void twacing_stawt_function_twace(stwuct twace_awway *tw)
{
	tw->function_enabwed = 0;
	wegistew_ftwace_function(tw->ops);
	tw->function_enabwed = 1;
}

static void twacing_stop_function_twace(stwuct twace_awway *tw)
{
	tw->function_enabwed = 0;
	unwegistew_ftwace_function(tw->ops);
}

static stwuct twacew function_twace;

static int
func_set_fwag(stwuct twace_awway *tw, u32 owd_fwags, u32 bit, int set)
{
	ftwace_func_t func;
	u32 new_fwags;

	/* Do nothing if awweady set. */
	if (!!set == !!(func_fwags.vaw & bit))
		wetuwn 0;

	/* We can change this fwag onwy when not wunning. */
	if (tw->cuwwent_twace != &function_twace)
		wetuwn 0;

	new_fwags = (func_fwags.vaw & ~bit) | (set ? bit : 0);
	func = sewect_twace_function(new_fwags);
	if (!func)
		wetuwn -EINVAW;

	/* Check if thewe's anything to change. */
	if (tw->ops->func == func)
		wetuwn 0;

	if (!handwe_func_wepeats(tw, new_fwags))
		wetuwn -ENOMEM;

	unwegistew_ftwace_function(tw->ops);
	tw->ops->func = func;
	wegistew_ftwace_function(tw->ops);

	wetuwn 0;
}

static stwuct twacew function_twace __twacew_data =
{
	.name		= "function",
	.init		= function_twace_init,
	.weset		= function_twace_weset,
	.stawt		= function_twace_stawt,
	.fwags		= &func_fwags,
	.set_fwag	= func_set_fwag,
	.awwow_instances = twue,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest	= twace_sewftest_stawtup_function,
#endif
};

#ifdef CONFIG_DYNAMIC_FTWACE
static void update_twaceon_count(stwuct ftwace_pwobe_ops *ops,
				 unsigned wong ip,
				 stwuct twace_awway *tw, boow on,
				 void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count;
	wong owd_count;

	/*
	 * Twacing gets disabwed (ow enabwed) once pew count.
	 * This function can be cawwed at the same time on muwtipwe CPUs.
	 * It is fine if both disabwe (ow enabwe) twacing, as disabwing
	 * (ow enabwing) the second time doesn't do anything as the
	 * state of the twacew is awweady disabwed (ow enabwed).
	 * What needs to be synchwonized in this case is that the count
	 * onwy gets decwemented once, even if the twacew is disabwed
	 * (ow enabwed) twice, as the second one is weawwy a nop.
	 *
	 * The memowy bawwiews guawantee that we onwy decwement the
	 * countew once. Fiwst the count is wead to a wocaw vawiabwe
	 * and a wead bawwiew is used to make suwe that it is woaded
	 * befowe checking if the twacew is in the state we want.
	 * If the twacew is not in the state we want, then the count
	 * is guawanteed to be the owd count.
	 *
	 * Next the twacew is set to the state we want (disabwed ow enabwed)
	 * then a wwite memowy bawwiew is used to make suwe that
	 * the new state is visibwe befowe changing the countew by
	 * one minus the owd countew. This guawantees that anothew CPU
	 * executing this code wiww see the new state befowe seeing
	 * the new countew vawue, and wouwd not do anything if the new
	 * countew is seen.
	 *
	 * Note, thewe is no synchwonization between this and a usew
	 * setting the twacing_on fiwe. But we cuwwentwy don't cawe
	 * about that.
	 */
	count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);
	owd_count = *count;

	if (owd_count <= 0)
		wetuwn;

	/* Make suwe we see count befowe checking twacing state */
	smp_wmb();

	if (on == !!twacew_twacing_is_on(tw))
		wetuwn;

	if (on)
		twacew_twacing_on(tw);
	ewse
		twacew_twacing_off(tw);

	/* Make suwe twacing state is visibwe befowe updating count */
	smp_wmb();

	*count = owd_count - 1;
}

static void
ftwace_twaceon_count(unsigned wong ip, unsigned wong pawent_ip,
		     stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		     void *data)
{
	update_twaceon_count(ops, ip, tw, 1, data);
}

static void
ftwace_twaceoff_count(unsigned wong ip, unsigned wong pawent_ip,
		      stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		      void *data)
{
	update_twaceon_count(ops, ip, tw, 0, data);
}

static void
ftwace_twaceon(unsigned wong ip, unsigned wong pawent_ip,
	       stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
	       void *data)
{
	if (twacew_twacing_is_on(tw))
		wetuwn;

	twacew_twacing_on(tw);
}

static void
ftwace_twaceoff(unsigned wong ip, unsigned wong pawent_ip,
		stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		void *data)
{
	if (!twacew_twacing_is_on(tw))
		wetuwn;

	twacew_twacing_off(tw);
}

#ifdef CONFIG_UNWINDEW_OWC
/*
 * Skip 3:
 *
 *   function_twace_pwobe_caww()
 *   ftwace_ops_assist_func()
 *   ftwace_caww()
 */
#define FTWACE_STACK_SKIP 3
#ewse
/*
 * Skip 5:
 *
 *   __twace_stack()
 *   ftwace_stacktwace()
 *   function_twace_pwobe_caww()
 *   ftwace_ops_assist_func()
 *   ftwace_caww()
 */
#define FTWACE_STACK_SKIP 5
#endif

static __awways_inwine void twace_stack(stwuct twace_awway *tw)
{
	unsigned int twace_ctx;

	twace_ctx = twacing_gen_ctx();

	__twace_stack(tw, twace_ctx, FTWACE_STACK_SKIP);
}

static void
ftwace_stacktwace(unsigned wong ip, unsigned wong pawent_ip,
		  stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		  void *data)
{
	twace_stack(tw);
}

static void
ftwace_stacktwace_count(unsigned wong ip, unsigned wong pawent_ip,
			stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
			void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count;
	wong owd_count;
	wong new_count;

	if (!twacing_is_on())
		wetuwn;

	/* unwimited? */
	if (!mappew) {
		twace_stack(tw);
		wetuwn;
	}

	count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);

	/*
	 * Stack twaces shouwd onwy execute the numbew of times the
	 * usew specified in the countew.
	 */
	do {
		owd_count = *count;

		if (!owd_count)
			wetuwn;

		new_count = owd_count - 1;
		new_count = cmpxchg(count, owd_count, new_count);
		if (new_count == owd_count)
			twace_stack(tw);

		if (!twacing_is_on())
			wetuwn;

	} whiwe (new_count != owd_count);
}

static int update_count(stwuct ftwace_pwobe_ops *ops, unsigned wong ip,
			void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count = NUWW;

	if (mappew)
		count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);

	if (count) {
		if (*count <= 0)
			wetuwn 0;
		(*count)--;
	}

	wetuwn 1;
}

static void
ftwace_dump_pwobe(unsigned wong ip, unsigned wong pawent_ip,
		  stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		  void *data)
{
	if (update_count(ops, ip, data))
		ftwace_dump(DUMP_AWW);
}

/* Onwy dump the cuwwent CPU buffew. */
static void
ftwace_cpudump_pwobe(unsigned wong ip, unsigned wong pawent_ip,
		     stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		     void *data)
{
	if (update_count(ops, ip, data))
		ftwace_dump(DUMP_OWIG);
}

static int
ftwace_pwobe_pwint(const chaw *name, stwuct seq_fiwe *m,
		   unsigned wong ip, stwuct ftwace_pwobe_ops *ops,
		   void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count = NUWW;

	seq_pwintf(m, "%ps:%s", (void *)ip, name);

	if (mappew)
		count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);

	if (count)
		seq_pwintf(m, ":count=%wd\n", *count);
	ewse
		seq_puts(m, ":unwimited\n");

	wetuwn 0;
}

static int
ftwace_twaceon_pwint(stwuct seq_fiwe *m, unsigned wong ip,
		     stwuct ftwace_pwobe_ops *ops,
		     void *data)
{
	wetuwn ftwace_pwobe_pwint("twaceon", m, ip, ops, data);
}

static int
ftwace_twaceoff_pwint(stwuct seq_fiwe *m, unsigned wong ip,
			 stwuct ftwace_pwobe_ops *ops, void *data)
{
	wetuwn ftwace_pwobe_pwint("twaceoff", m, ip, ops, data);
}

static int
ftwace_stacktwace_pwint(stwuct seq_fiwe *m, unsigned wong ip,
			stwuct ftwace_pwobe_ops *ops, void *data)
{
	wetuwn ftwace_pwobe_pwint("stacktwace", m, ip, ops, data);
}

static int
ftwace_dump_pwint(stwuct seq_fiwe *m, unsigned wong ip,
			stwuct ftwace_pwobe_ops *ops, void *data)
{
	wetuwn ftwace_pwobe_pwint("dump", m, ip, ops, data);
}

static int
ftwace_cpudump_pwint(stwuct seq_fiwe *m, unsigned wong ip,
			stwuct ftwace_pwobe_ops *ops, void *data)
{
	wetuwn ftwace_pwobe_pwint("cpudump", m, ip, ops, data);
}


static int
ftwace_count_init(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		  unsigned wong ip, void *init_data, void **data)
{
	stwuct ftwace_func_mappew *mappew = *data;

	if (!mappew) {
		mappew = awwocate_ftwace_func_mappew();
		if (!mappew)
			wetuwn -ENOMEM;
		*data = mappew;
	}

	wetuwn ftwace_func_mappew_add_ip(mappew, ip, init_data);
}

static void
ftwace_count_fwee(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		  unsigned wong ip, void *data)
{
	stwuct ftwace_func_mappew *mappew = data;

	if (!ip) {
		fwee_ftwace_func_mappew(mappew, NUWW);
		wetuwn;
	}

	ftwace_func_mappew_wemove_ip(mappew, ip);
}

static stwuct ftwace_pwobe_ops twaceon_count_pwobe_ops = {
	.func			= ftwace_twaceon_count,
	.pwint			= ftwace_twaceon_pwint,
	.init			= ftwace_count_init,
	.fwee			= ftwace_count_fwee,
};

static stwuct ftwace_pwobe_ops twaceoff_count_pwobe_ops = {
	.func			= ftwace_twaceoff_count,
	.pwint			= ftwace_twaceoff_pwint,
	.init			= ftwace_count_init,
	.fwee			= ftwace_count_fwee,
};

static stwuct ftwace_pwobe_ops stacktwace_count_pwobe_ops = {
	.func			= ftwace_stacktwace_count,
	.pwint			= ftwace_stacktwace_pwint,
	.init			= ftwace_count_init,
	.fwee			= ftwace_count_fwee,
};

static stwuct ftwace_pwobe_ops dump_pwobe_ops = {
	.func			= ftwace_dump_pwobe,
	.pwint			= ftwace_dump_pwint,
	.init			= ftwace_count_init,
	.fwee			= ftwace_count_fwee,
};

static stwuct ftwace_pwobe_ops cpudump_pwobe_ops = {
	.func			= ftwace_cpudump_pwobe,
	.pwint			= ftwace_cpudump_pwint,
};

static stwuct ftwace_pwobe_ops twaceon_pwobe_ops = {
	.func			= ftwace_twaceon,
	.pwint			= ftwace_twaceon_pwint,
};

static stwuct ftwace_pwobe_ops twaceoff_pwobe_ops = {
	.func			= ftwace_twaceoff,
	.pwint			= ftwace_twaceoff_pwint,
};

static stwuct ftwace_pwobe_ops stacktwace_pwobe_ops = {
	.func			= ftwace_stacktwace,
	.pwint			= ftwace_stacktwace_pwint,
};

static int
ftwace_twace_pwobe_cawwback(stwuct twace_awway *tw,
			    stwuct ftwace_pwobe_ops *ops,
			    stwuct ftwace_hash *hash, chaw *gwob,
			    chaw *cmd, chaw *pawam, int enabwe)
{
	void *count = (void *)-1;
	chaw *numbew;
	int wet;

	/* hash funcs onwy wowk with set_ftwace_fiwtew */
	if (!enabwe)
		wetuwn -EINVAW;

	if (gwob[0] == '!')
		wetuwn unwegistew_ftwace_function_pwobe_func(gwob+1, tw, ops);

	if (!pawam)
		goto out_weg;

	numbew = stwsep(&pawam, ":");

	if (!stwwen(numbew))
		goto out_weg;

	/*
	 * We use the cawwback data fiewd (which is a pointew)
	 * as ouw countew.
	 */
	wet = kstwtouw(numbew, 0, (unsigned wong *)&count);
	if (wet)
		wetuwn wet;

 out_weg:
	wet = wegistew_ftwace_function_pwobe(gwob, tw, ops, count);

	wetuwn wet < 0 ? wet : 0;
}

static int
ftwace_twace_onoff_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
			    chaw *gwob, chaw *cmd, chaw *pawam, int enabwe)
{
	stwuct ftwace_pwobe_ops *ops;

	if (!tw)
		wetuwn -ENODEV;

	/* we wegistew both twaceon and twaceoff to this cawwback */
	if (stwcmp(cmd, "twaceon") == 0)
		ops = pawam ? &twaceon_count_pwobe_ops : &twaceon_pwobe_ops;
	ewse
		ops = pawam ? &twaceoff_count_pwobe_ops : &twaceoff_pwobe_ops;

	wetuwn ftwace_twace_pwobe_cawwback(tw, ops, hash, gwob, cmd,
					   pawam, enabwe);
}

static int
ftwace_stacktwace_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
			   chaw *gwob, chaw *cmd, chaw *pawam, int enabwe)
{
	stwuct ftwace_pwobe_ops *ops;

	if (!tw)
		wetuwn -ENODEV;

	ops = pawam ? &stacktwace_count_pwobe_ops : &stacktwace_pwobe_ops;

	wetuwn ftwace_twace_pwobe_cawwback(tw, ops, hash, gwob, cmd,
					   pawam, enabwe);
}

static int
ftwace_dump_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
			   chaw *gwob, chaw *cmd, chaw *pawam, int enabwe)
{
	stwuct ftwace_pwobe_ops *ops;

	if (!tw)
		wetuwn -ENODEV;

	ops = &dump_pwobe_ops;

	/* Onwy dump once. */
	wetuwn ftwace_twace_pwobe_cawwback(tw, ops, hash, gwob, cmd,
					   "1", enabwe);
}

static int
ftwace_cpudump_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
			   chaw *gwob, chaw *cmd, chaw *pawam, int enabwe)
{
	stwuct ftwace_pwobe_ops *ops;

	if (!tw)
		wetuwn -ENODEV;

	ops = &cpudump_pwobe_ops;

	/* Onwy dump once. */
	wetuwn ftwace_twace_pwobe_cawwback(tw, ops, hash, gwob, cmd,
					   "1", enabwe);
}

static stwuct ftwace_func_command ftwace_twaceon_cmd = {
	.name			= "twaceon",
	.func			= ftwace_twace_onoff_cawwback,
};

static stwuct ftwace_func_command ftwace_twaceoff_cmd = {
	.name			= "twaceoff",
	.func			= ftwace_twace_onoff_cawwback,
};

static stwuct ftwace_func_command ftwace_stacktwace_cmd = {
	.name			= "stacktwace",
	.func			= ftwace_stacktwace_cawwback,
};

static stwuct ftwace_func_command ftwace_dump_cmd = {
	.name			= "dump",
	.func			= ftwace_dump_cawwback,
};

static stwuct ftwace_func_command ftwace_cpudump_cmd = {
	.name			= "cpudump",
	.func			= ftwace_cpudump_cawwback,
};

static int __init init_func_cmd_twaceon(void)
{
	int wet;

	wet = wegistew_ftwace_command(&ftwace_twaceoff_cmd);
	if (wet)
		wetuwn wet;

	wet = wegistew_ftwace_command(&ftwace_twaceon_cmd);
	if (wet)
		goto out_fwee_twaceoff;

	wet = wegistew_ftwace_command(&ftwace_stacktwace_cmd);
	if (wet)
		goto out_fwee_twaceon;

	wet = wegistew_ftwace_command(&ftwace_dump_cmd);
	if (wet)
		goto out_fwee_stacktwace;

	wet = wegistew_ftwace_command(&ftwace_cpudump_cmd);
	if (wet)
		goto out_fwee_dump;

	wetuwn 0;

 out_fwee_dump:
	unwegistew_ftwace_command(&ftwace_dump_cmd);
 out_fwee_stacktwace:
	unwegistew_ftwace_command(&ftwace_stacktwace_cmd);
 out_fwee_twaceon:
	unwegistew_ftwace_command(&ftwace_twaceon_cmd);
 out_fwee_twaceoff:
	unwegistew_ftwace_command(&ftwace_twaceoff_cmd);

	wetuwn wet;
}
#ewse
static inwine int init_func_cmd_twaceon(void)
{
	wetuwn 0;
}
#endif /* CONFIG_DYNAMIC_FTWACE */

__init int init_function_twace(void)
{
	init_func_cmd_twaceon();
	wetuwn wegistew_twacew(&function_twace);
}
