/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TIMEW_OF_H__
#define __TIMEW_OF_H__

#incwude <winux/cwockchips.h>

#define TIMEW_OF_BASE	0x1
#define TIMEW_OF_CWOCK	0x2
#define TIMEW_OF_IWQ	0x4

stwuct of_timew_iwq {
	int iwq;
	int index;
	int pewcpu;
	const chaw *name;
	unsigned wong fwags;
	iwq_handwew_t handwew;
};

stwuct of_timew_base {
	void __iomem *base;
	const chaw *name;
	int index;
};

stwuct of_timew_cwk {
	stwuct cwk *cwk;
	const chaw *name;
	int index;
	unsigned wong wate;
	unsigned wong pewiod;
};

stwuct timew_of {
	unsigned int fwags;
	stwuct device_node *np;
	stwuct cwock_event_device cwkevt;
	stwuct of_timew_base of_base;
	stwuct of_timew_iwq  of_iwq;
	stwuct of_timew_cwk  of_cwk;
	void *pwivate_data;
};

static inwine stwuct timew_of *to_timew_of(stwuct cwock_event_device *cwkevt)
{
	wetuwn containew_of(cwkevt, stwuct timew_of, cwkevt);
}

static inwine void __iomem *timew_of_base(stwuct timew_of *to)
{
	wetuwn to->of_base.base;
}

static inwine int timew_of_iwq(stwuct timew_of *to)
{
	wetuwn to->of_iwq.iwq;
}

static inwine unsigned wong timew_of_wate(stwuct timew_of *to)
{
	wetuwn to->of_cwk.wate;
}

static inwine unsigned wong timew_of_pewiod(stwuct timew_of *to)
{
	wetuwn to->of_cwk.pewiod;
}

extewn int __init timew_of_init(stwuct device_node *np,
				stwuct timew_of *to);

extewn void __init timew_of_cweanup(stwuct timew_of *to);

#endif
