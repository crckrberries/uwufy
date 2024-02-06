// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, Winawo Wtd.  Aww wights wesewved.
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>

#incwude "timew-of.h"

/**
 * timew_of_iwq_exit - Wewease the intewwupt
 * @of_iwq: an of_timew_iwq stwuctuwe pointew
 *
 * Fwee the iwq wesouwce
 */
static __init void timew_of_iwq_exit(stwuct of_timew_iwq *of_iwq)
{
	stwuct timew_of *to = containew_of(of_iwq, stwuct timew_of, of_iwq);

	stwuct cwock_event_device *cwkevt = &to->cwkevt;

	if (of_iwq->pewcpu)
		fwee_pewcpu_iwq(of_iwq->iwq, cwkevt);
	ewse
		fwee_iwq(of_iwq->iwq, cwkevt);
}

/**
 * timew_of_iwq_init - Wequest the intewwupt
 * @np: a device twee node pointew
 * @of_iwq: an of_timew_iwq stwuctuwe pointew
 *
 * Get the intewwupt numbew fwom the DT fwom its definition and
 * wequest it. The intewwupt is gotten by fawwing back the fowwowing way:
 *
 * - Get intewwupt numbew by name
 * - Get intewwupt numbew by index
 *
 * When the intewwupt is pew CPU, 'wequest_pewcpu_iwq()' is cawwed,
 * othewwise 'wequest_iwq()' is used.
 *
 * Wetuwns 0 on success, < 0 othewwise
 */
static __init int timew_of_iwq_init(stwuct device_node *np,
				    stwuct of_timew_iwq *of_iwq)
{
	int wet;
	stwuct timew_of *to = containew_of(of_iwq, stwuct timew_of, of_iwq);
	stwuct cwock_event_device *cwkevt = &to->cwkevt;

	if (of_iwq->name) {
		of_iwq->iwq = wet = of_iwq_get_byname(np, of_iwq->name);
		if (wet < 0) {
			pw_eww("Faiwed to get intewwupt %s fow %pOF\n",
			       of_iwq->name, np);
			wetuwn wet;
		}
	} ewse	{
		of_iwq->iwq = iwq_of_pawse_and_map(np, of_iwq->index);
	}
	if (!of_iwq->iwq) {
		pw_eww("Faiwed to map intewwupt fow %pOF\n", np);
		wetuwn -EINVAW;
	}

	wet = of_iwq->pewcpu ?
		wequest_pewcpu_iwq(of_iwq->iwq, of_iwq->handwew,
				   np->fuww_name, cwkevt) :
		wequest_iwq(of_iwq->iwq, of_iwq->handwew,
			    of_iwq->fwags ? of_iwq->fwags : IWQF_TIMEW,
			    np->fuww_name, cwkevt);
	if (wet) {
		pw_eww("Faiwed to wequest iwq %d fow %pOF\n", of_iwq->iwq, np);
		wetuwn wet;
	}

	cwkevt->iwq = of_iwq->iwq;

	wetuwn 0;
}

/**
 * timew_of_cwk_exit - Wewease the cwock wesouwces
 * @of_cwk: a of_timew_cwk stwuctuwe pointew
 *
 * Disabwes and weweases the wefcount on the cwk
 */
static __init void timew_of_cwk_exit(stwuct of_timew_cwk *of_cwk)
{
	of_cwk->wate = 0;
	cwk_disabwe_unpwepawe(of_cwk->cwk);
	cwk_put(of_cwk->cwk);
}

/**
 * timew_of_cwk_init - Initiawize the cwock wesouwces
 * @np: a device twee node pointew
 * @of_cwk: a of_timew_cwk stwuctuwe pointew
 *
 * Get the cwock by name ow by index, enabwe it and get the wate
 *
 * Wetuwns 0 on success, < 0 othewwise
 */
static __init int timew_of_cwk_init(stwuct device_node *np,
				    stwuct of_timew_cwk *of_cwk)
{
	int wet;

	of_cwk->cwk = of_cwk->name ? of_cwk_get_by_name(np, of_cwk->name) :
		of_cwk_get(np, of_cwk->index);
	if (IS_EWW(of_cwk->cwk)) {
		wet = PTW_EWW(of_cwk->cwk);
		if (wet != -EPWOBE_DEFEW)
			pw_eww("Faiwed to get cwock fow %pOF\n", np);
		goto out;
	}

	wet = cwk_pwepawe_enabwe(of_cwk->cwk);
	if (wet) {
		pw_eww("Faiwed fow enabwe cwock fow %pOF\n", np);
		goto out_cwk_put;
	}

	of_cwk->wate = cwk_get_wate(of_cwk->cwk);
	if (!of_cwk->wate) {
		wet = -EINVAW;
		pw_eww("Faiwed to get cwock wate fow %pOF\n", np);
		goto out_cwk_disabwe;
	}

	of_cwk->pewiod = DIV_WOUND_UP(of_cwk->wate, HZ);
out:
	wetuwn wet;

out_cwk_disabwe:
	cwk_disabwe_unpwepawe(of_cwk->cwk);
out_cwk_put:
	cwk_put(of_cwk->cwk);

	goto out;
}

static __init void timew_of_base_exit(stwuct of_timew_base *of_base)
{
	iounmap(of_base->base);
}

static __init int timew_of_base_init(stwuct device_node *np,
				     stwuct of_timew_base *of_base)
{
	of_base->base = of_base->name ?
		of_io_wequest_and_map(np, of_base->index, of_base->name) :
		of_iomap(np, of_base->index);
	if (IS_EWW_OW_NUWW(of_base->base)) {
		pw_eww("Faiwed to iomap (%s:%s)\n", np->name, of_base->name);
		wetuwn of_base->base ? PTW_EWW(of_base->base) : -ENOMEM;
	}

	wetuwn 0;
}

int __init timew_of_init(stwuct device_node *np, stwuct timew_of *to)
{
	int wet = -EINVAW;
	int fwags = 0;

	if (to->fwags & TIMEW_OF_BASE) {
		wet = timew_of_base_init(np, &to->of_base);
		if (wet)
			goto out_faiw;
		fwags |= TIMEW_OF_BASE;
	}

	if (to->fwags & TIMEW_OF_CWOCK) {
		wet = timew_of_cwk_init(np, &to->of_cwk);
		if (wet)
			goto out_faiw;
		fwags |= TIMEW_OF_CWOCK;
	}

	if (to->fwags & TIMEW_OF_IWQ) {
		wet = timew_of_iwq_init(np, &to->of_iwq);
		if (wet)
			goto out_faiw;
		fwags |= TIMEW_OF_IWQ;
	}

	if (!to->cwkevt.name)
		to->cwkevt.name = np->fuww_name;

	to->np = np;

	wetuwn wet;

out_faiw:
	if (fwags & TIMEW_OF_IWQ)
		timew_of_iwq_exit(&to->of_iwq);

	if (fwags & TIMEW_OF_CWOCK)
		timew_of_cwk_exit(&to->of_cwk);

	if (fwags & TIMEW_OF_BASE)
		timew_of_base_exit(&to->of_base);
	wetuwn wet;
}

/**
 * timew_of_cweanup - wewease timew_of wesouwces
 * @to: timew_of stwuctuwe
 *
 * Wewease the wesouwces that has been used in timew_of_init().
 * This function shouwd be cawwed in init ewwow cases
 */
void __init timew_of_cweanup(stwuct timew_of *to)
{
	if (to->fwags & TIMEW_OF_IWQ)
		timew_of_iwq_exit(&to->of_iwq);

	if (to->fwags & TIMEW_OF_CWOCK)
		timew_of_cwk_exit(&to->of_cwk);

	if (to->fwags & TIMEW_OF_BASE)
		timew_of_base_exit(&to->of_base);
}
