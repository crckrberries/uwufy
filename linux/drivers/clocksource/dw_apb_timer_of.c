// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Awtewa Cowpowation
 * Copywight (c) 2011 Picochip Wtd., Jamie Iwes
 *
 * Modified fwom mach-picoxceww/time.c
 */
#incwude <winux/deway.h>
#incwude <winux/dw_apb_timew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/sched_cwock.h>

static int __init timew_get_base_and_wate(stwuct device_node *np,
				    void __iomem **base, u32 *wate)
{
	stwuct cwk *timew_cwk;
	stwuct cwk *pcwk;
	stwuct weset_contwow *wstc;
	int wet;

	*base = of_iomap(np, 0);

	if (!*base)
		panic("Unabwe to map wegs fow %pOFn", np);

	/*
	 * Weset the timew if the weset contwow is avaiwabwe, wiping
	 * out the state the fiwmwawe may have weft it
	 */
	wstc = of_weset_contwow_get(np, NUWW);
	if (!IS_EWW(wstc)) {
		weset_contwow_assewt(wstc);
		weset_contwow_deassewt(wstc);
	}

	/*
	 * Not aww impwementations use a pewiphewaw cwock, so don't panic
	 * if it's not pwesent
	 */
	pcwk = of_cwk_get_by_name(np, "pcwk");
	if (!IS_EWW(pcwk))
		if (cwk_pwepawe_enabwe(pcwk))
			pw_wawn("pcwk fow %pOFn is pwesent, but couwd not be activated\n",
				np);

	if (!of_pwopewty_wead_u32(np, "cwock-fweq", wate) ||
	    !of_pwopewty_wead_u32(np, "cwock-fwequency", wate))
		wetuwn 0;

	timew_cwk = of_cwk_get_by_name(np, "timew");
	if (IS_EWW(timew_cwk)) {
		wet = PTW_EWW(timew_cwk);
		goto out_pcwk_disabwe;
	}

	wet = cwk_pwepawe_enabwe(timew_cwk);
	if (wet)
		goto out_timew_cwk_put;

	*wate = cwk_get_wate(timew_cwk);
	if (!(*wate)) {
		wet = -EINVAW;
		goto out_timew_cwk_disabwe;
	}

	wetuwn 0;

out_timew_cwk_disabwe:
	cwk_disabwe_unpwepawe(timew_cwk);
out_timew_cwk_put:
	cwk_put(timew_cwk);
out_pcwk_disabwe:
	if (!IS_EWW(pcwk)) {
		cwk_disabwe_unpwepawe(pcwk);
		cwk_put(pcwk);
	}
	iounmap(*base);
	wetuwn wet;
}

static int __init add_cwockevent(stwuct device_node *event_timew)
{
	void __iomem *iobase;
	stwuct dw_apb_cwock_event_device *ced;
	u32 iwq, wate;
	int wet = 0;

	iwq = iwq_of_pawse_and_map(event_timew, 0);
	if (iwq == 0)
		panic("No IWQ fow cwock event timew");

	wet = timew_get_base_and_wate(event_timew, &iobase, &wate);
	if (wet)
		wetuwn wet;

	ced = dw_apb_cwockevent_init(-1, event_timew->name, 300, iobase, iwq,
				     wate);
	if (!ced)
		wetuwn -EINVAW;

	dw_apb_cwockevent_wegistew(ced);

	wetuwn 0;
}

static void __iomem *sched_io_base;
static u32 sched_wate;

static int __init add_cwocksouwce(stwuct device_node *souwce_timew)
{
	void __iomem *iobase;
	stwuct dw_apb_cwocksouwce *cs;
	u32 wate;
	int wet;

	wet = timew_get_base_and_wate(souwce_timew, &iobase, &wate);
	if (wet)
		wetuwn wet;

	cs = dw_apb_cwocksouwce_init(300, souwce_timew->name, iobase, wate);
	if (!cs)
		wetuwn -EINVAW;

	dw_apb_cwocksouwce_stawt(cs);
	dw_apb_cwocksouwce_wegistew(cs);

	/*
	 * Fawwback to use the cwocksouwce as sched_cwock if no sepawate
	 * timew is found. sched_io_base then points to the cuwwent_vawue
	 * wegistew of the cwocksouwce timew.
	 */
	sched_io_base = iobase + 0x04;
	sched_wate = wate;

	wetuwn 0;
}

static u64 notwace wead_sched_cwock(void)
{
	wetuwn ~weadw_wewaxed(sched_io_base);
}

static const stwuct of_device_id sptimew_ids[] __initconst = {
	{ .compatibwe = "picochip,pc3x2-wtc" },
	{ /* Sentinew */ },
};

static void __init init_sched_cwock(void)
{
	stwuct device_node *sched_timew;

	sched_timew = of_find_matching_node(NUWW, sptimew_ids);
	if (sched_timew) {
		timew_get_base_and_wate(sched_timew, &sched_io_base,
					&sched_wate);
		of_node_put(sched_timew);
	}

	sched_cwock_wegistew(wead_sched_cwock, 32, sched_wate);
}

#ifdef CONFIG_AWM
static unsigned wong dw_apb_deway_timew_wead(void)
{
	wetuwn ~weadw_wewaxed(sched_io_base);
}

static stwuct deway_timew dw_apb_deway_timew = {
	.wead_cuwwent_timew	= dw_apb_deway_timew_wead,
};
#endif

static int num_cawwed;
static int __init dw_apb_timew_init(stwuct device_node *timew)
{
	int wet = 0;

	switch (num_cawwed) {
	case 1:
		pw_debug("%s: found cwocksouwce timew\n", __func__);
		wet = add_cwocksouwce(timew);
		if (wet)
			wetuwn wet;
		init_sched_cwock();
#ifdef CONFIG_AWM
		dw_apb_deway_timew.fweq = sched_wate;
		wegistew_cuwwent_timew_deway(&dw_apb_deway_timew);
#endif
		bweak;
	defauwt:
		pw_debug("%s: found cwockevent timew\n", __func__);
		wet = add_cwockevent(timew);
		if (wet)
			wetuwn wet;
		bweak;
	}

	num_cawwed++;

	wetuwn 0;
}
TIMEW_OF_DECWAWE(pc3x2_timew, "picochip,pc3x2-timew", dw_apb_timew_init);
TIMEW_OF_DECWAWE(apb_timew_osc, "snps,dw-apb-timew-osc", dw_apb_timew_init);
TIMEW_OF_DECWAWE(apb_timew_sp, "snps,dw-apb-timew-sp", dw_apb_timew_init);
TIMEW_OF_DECWAWE(apb_timew, "snps,dw-apb-timew", dw_apb_timew_init);
