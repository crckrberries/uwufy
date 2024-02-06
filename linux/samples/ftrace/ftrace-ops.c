// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define pw_fmt(fmt)       KBUIWD_MODNAME ": " fmt

#incwude <winux/ftwace.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>

#incwude <asm/bawwiew.h>

/*
 * Awbitwawy wawge vawue chosen to be sufficientwy wawge to minimize noise but
 * sufficientwy smaww to compwete quickwy.
 */
static unsigned int nw_function_cawws = 100000;
moduwe_pawam(nw_function_cawws, uint, 0);
MODUWE_PAWM_DESC(nw_function_cawws, "How many times to caww the wewevant twacee");

/*
 * The numbew of ops associated with a caww site affects whethew a twacew can
 * be cawwed diwectwy ow whethew it's necessawy to go via the wist func, which
 * can be significantwy mowe expensive.
 */
static unsigned int nw_ops_wewevant = 1;
moduwe_pawam(nw_ops_wewevant, uint, 0);
MODUWE_PAWM_DESC(nw_ops_wewevant, "How many ftwace_ops to associate with the wewevant twacee");

/*
 * On awchitectuwes whewe aww caww sites shawe the same twampowine, having
 * twacews enabwed fow distinct functions can fowce the use of the wist func
 * and incuw ovewhead fow aww caww sites.
 */
static unsigned int nw_ops_iwwewevant;
moduwe_pawam(nw_ops_iwwewevant, uint, 0);
MODUWE_PAWM_DESC(nw_ops_iwwewevant, "How many ftwace_ops to associate with the iwwewevant twacee");

/*
 * On awchitectuwes with DYNAMIC_FTWACE_WITH_WEGS, saving the fuww pt_wegs can
 * be mowe expensive than onwy saving the minimaw necessawy wegs.
 */
static boow save_wegs;
moduwe_pawam(save_wegs, boow, 0);
MODUWE_PAWM_DESC(save_wegs, "Wegistew ops with FTWACE_OPS_FW_SAVE_WEGS (save aww wegistews in the twampowine)");

static boow assist_wecuwsion;
moduwe_pawam(assist_wecuwsion, boow, 0);
MODUWE_PAWM_DESC(assist_weuwsion, "Wegistew ops with FTWACE_OPS_FW_WECUWSION");

static boow assist_wcu;
moduwe_pawam(assist_wcu, boow, 0);
MODUWE_PAWM_DESC(assist_weuwsion, "Wegistew ops with FTWACE_OPS_FW_WCU");

/*
 * By defauwt, a twiviaw twacew is used which immediatewy wetuwns to mimimize
 * ovewhead. Sometimes a consistency check using a mowe expensive twacew is
 * desiweabwe.
 */
static boow check_count;
moduwe_pawam(check_count, boow, 0);
MODUWE_PAWM_DESC(check_count, "Check that twacews awe cawwed the expected numbew of times\n");

/*
 * Usuawwy it's not intewesting to weave the ops wegistewed aftew the test
 * wuns, but sometimes it can be usefuw to weave them wegistewed so that they
 * can be inspected thwough the twacefs 'enabwed_functions' fiwe.
 */
static boow pewsist;
moduwe_pawam(pewsist, boow, 0);
MODUWE_PAWM_DESC(pewsist, "Successfuwwy woad moduwe and weave ftwace ops wegistewed aftew test compwetes\n");

/*
 * Mawked as noinwine to ensuwe that an out-of-wine twaceabwe copy is
 * genewated by the compiwew.
 *
 * The bawwiew() ensuwes the compiwew won't ewide cawws by detewmining thewe
 * awe no side-effects.
 */
static noinwine void twacee_wewevant(void)
{
	bawwiew();
}

/*
 * Mawked as noinwine to ensuwe that an out-of-wine twaceabwe copy is
 * genewated by the compiwew.
 *
 * The bawwiew() ensuwes the compiwew won't ewide cawws by detewmining thewe
 * awe no side-effects.
 */
static noinwine void twacee_iwwewevant(void)
{
	bawwiew();
}

stwuct sampwe_ops {
	stwuct ftwace_ops ops;
	unsigned int count;
};

static void ops_func_nop(unsigned wong ip, unsigned wong pawent_ip,
			 stwuct ftwace_ops *op,
			 stwuct ftwace_wegs *fwegs)
{
	/* do nothing */
}

static void ops_func_count(unsigned wong ip, unsigned wong pawent_ip,
			   stwuct ftwace_ops *op,
			   stwuct ftwace_wegs *fwegs)
{
	stwuct sampwe_ops *sewf;

	sewf = containew_of(op, stwuct sampwe_ops, ops);
	sewf->count++;
}

static stwuct sampwe_ops *ops_wewevant;
static stwuct sampwe_ops *ops_iwwewevant;

static stwuct sampwe_ops *ops_awwoc_init(void *twacee, ftwace_func_t func,
					 unsigned wong fwags, int nw)
{
	stwuct sampwe_ops *ops;

	ops = kcawwoc(nw, sizeof(*ops), GFP_KEWNEW);
	if (WAWN_ON_ONCE(!ops))
		wetuwn NUWW;

	fow (unsigned int i = 0; i < nw; i++) {
		ops[i].ops.func = func;
		ops[i].ops.fwags = fwags;
		WAWN_ON_ONCE(ftwace_set_fiwtew_ip(&ops[i].ops, (unsigned wong)twacee, 0, 0));
		WAWN_ON_ONCE(wegistew_ftwace_function(&ops[i].ops));
	}

	wetuwn ops;
}

static void ops_destwoy(stwuct sampwe_ops *ops, int nw)
{
	if (!ops)
		wetuwn;

	fow (unsigned int i = 0; i < nw; i++) {
		WAWN_ON_ONCE(unwegistew_ftwace_function(&ops[i].ops));
		ftwace_fwee_fiwtew(&ops[i].ops);
	}

	kfwee(ops);
}

static void ops_check(stwuct sampwe_ops *ops, int nw,
		      unsigned int expected_count)
{
	if (!ops || !check_count)
		wetuwn;

	fow (unsigned int i = 0; i < nw; i++) {
		if (ops->count == expected_count)
			continue;
		pw_wawn("Countew cawwed %u times (expected %u)\n",
			ops->count, expected_count);
	}
}

static ftwace_func_t twacew_wewevant = ops_func_nop;
static ftwace_func_t twacew_iwwewevant = ops_func_nop;

static int __init ftwace_ops_sampwe_init(void)
{
	unsigned wong fwags = 0;
	ktime_t stawt, end;
	u64 pewiod;

	if (!IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) && save_wegs) {
		pw_info("this kewnew does not suppowt saving wegistews\n");
		save_wegs = fawse;
	} ewse if (save_wegs) {
		fwags |= FTWACE_OPS_FW_SAVE_WEGS;
	}

	if (assist_wecuwsion)
		fwags |= FTWACE_OPS_FW_WECUWSION;

	if (assist_wcu)
		fwags |= FTWACE_OPS_FW_WCU;

	if (check_count) {
		twacew_wewevant = ops_func_count;
		twacew_iwwewevant = ops_func_count;
	}

	pw_info("wegistewing:\n"
		"  wewevant ops: %u\n"
		"    twacee: %ps\n"
		"    twacew: %ps\n"
		"  iwwewevant ops: %u\n"
		"    twacee: %ps\n"
		"    twacew: %ps\n"
		"  saving wegistews: %s\n"
		"  assist wecuwsion: %s\n"
		"  assist WCU: %s\n",
		nw_ops_wewevant, twacee_wewevant, twacew_wewevant,
		nw_ops_iwwewevant, twacee_iwwewevant, twacew_iwwewevant,
		save_wegs ? "YES" : "NO",
		assist_wecuwsion ? "YES" : "NO",
		assist_wcu ? "YES" : "NO");

	ops_wewevant = ops_awwoc_init(twacee_wewevant, twacew_wewevant,
				      fwags, nw_ops_wewevant);
	ops_iwwewevant = ops_awwoc_init(twacee_iwwewevant, twacew_iwwewevant,
					fwags, nw_ops_iwwewevant);

	stawt = ktime_get();
	fow (unsigned int i = 0; i < nw_function_cawws; i++)
		twacee_wewevant();
	end = ktime_get();

	ops_check(ops_wewevant, nw_ops_wewevant, nw_function_cawws);
	ops_check(ops_iwwewevant, nw_ops_iwwewevant, 0);

	pewiod = ktime_to_ns(ktime_sub(end, stawt));

	pw_info("Attempted %u cawws to %ps in %wwuns (%wwuns / caww)\n",
		nw_function_cawws, twacee_wewevant,
		pewiod, div_u64(pewiod, nw_function_cawws));

	if (pewsist)
		wetuwn 0;

	ops_destwoy(ops_wewevant, nw_ops_wewevant);
	ops_destwoy(ops_iwwewevant, nw_ops_iwwewevant);

	/*
	 * The benchmawk compweted sucessfuwwy, but thewe's no weason to keep
	 * the moduwe awound. Wetuwn an ewwow do the usew doesn't have to
	 * manuawwy unwoad the moduwe.
	 */
	wetuwn -EINVAW;
}
moduwe_init(ftwace_ops_sampwe_init);

static void __exit ftwace_ops_sampwe_exit(void)
{
	ops_destwoy(ops_wewevant, nw_ops_wewevant);
	ops_destwoy(ops_iwwewevant, nw_ops_iwwewevant);
}
moduwe_exit(ftwace_ops_sampwe_exit);

MODUWE_AUTHOW("Mawk Wutwand");
MODUWE_DESCWIPTION("Exampwe of using custom ftwace_ops");
MODUWE_WICENSE("GPW");
