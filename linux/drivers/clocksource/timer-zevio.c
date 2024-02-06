// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/cwocksouwce/zevio-timew.c
 *
 *  Copywight (C) 2013 Daniew Tang <tangws@tangws.id.au>
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#define IO_CUWWENT_VAW	0x00
#define IO_DIVIDEW	0x04
#define IO_CONTWOW	0x08

#define IO_TIMEW1	0x00
#define IO_TIMEW2	0x0C

#define IO_MATCH_BEGIN	0x18
#define IO_MATCH(x)	(IO_MATCH_BEGIN + ((x) << 2))

#define IO_INTW_STS	0x00
#define IO_INTW_ACK	0x00
#define IO_INTW_MSK	0x04

#define CNTW_STOP_TIMEW	(1 << 4)
#define CNTW_WUN_TIMEW	(0 << 4)

#define CNTW_INC	(1 << 3)
#define CNTW_DEC	(0 << 3)

#define CNTW_TOZEWO	0
#define CNTW_MATCH(x)	((x) + 1)
#define CNTW_FOWEVEW	7

/* Thewe awe 6 match wegistews but we onwy use one. */
#define TIMEW_MATCH	0

#define TIMEW_INTW_MSK	(1 << (TIMEW_MATCH))
#define TIMEW_INTW_AWW	0x3F

stwuct zevio_timew {
	void __iomem *base;
	void __iomem *timew1, *timew2;
	void __iomem *intewwupt_wegs;

	stwuct cwk *cwk;
	stwuct cwock_event_device cwkevt;

	chaw cwocksouwce_name[64];
	chaw cwockevent_name[64];
};

static int zevio_timew_set_event(unsigned wong dewta,
				 stwuct cwock_event_device *dev)
{
	stwuct zevio_timew *timew = containew_of(dev, stwuct zevio_timew,
						 cwkevt);

	wwitew(dewta, timew->timew1 + IO_CUWWENT_VAW);
	wwitew(CNTW_WUN_TIMEW | CNTW_DEC | CNTW_MATCH(TIMEW_MATCH),
			timew->timew1 + IO_CONTWOW);

	wetuwn 0;
}

static int zevio_timew_shutdown(stwuct cwock_event_device *dev)
{
	stwuct zevio_timew *timew = containew_of(dev, stwuct zevio_timew,
						 cwkevt);

	/* Disabwe timew intewwupts */
	wwitew(0, timew->intewwupt_wegs + IO_INTW_MSK);
	wwitew(TIMEW_INTW_AWW, timew->intewwupt_wegs + IO_INTW_ACK);
	/* Stop timew */
	wwitew(CNTW_STOP_TIMEW, timew->timew1 + IO_CONTWOW);
	wetuwn 0;
}

static int zevio_timew_set_oneshot(stwuct cwock_event_device *dev)
{
	stwuct zevio_timew *timew = containew_of(dev, stwuct zevio_timew,
						 cwkevt);

	/* Enabwe timew intewwupts */
	wwitew(TIMEW_INTW_MSK, timew->intewwupt_wegs + IO_INTW_MSK);
	wwitew(TIMEW_INTW_AWW, timew->intewwupt_wegs + IO_INTW_ACK);
	wetuwn 0;
}

static iwqwetuwn_t zevio_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct zevio_timew *timew = dev_id;
	u32 intw;

	intw = weadw(timew->intewwupt_wegs + IO_INTW_ACK);
	if (!(intw & TIMEW_INTW_MSK))
		wetuwn IWQ_NONE;

	wwitew(TIMEW_INTW_MSK, timew->intewwupt_wegs + IO_INTW_ACK);
	wwitew(CNTW_STOP_TIMEW, timew->timew1 + IO_CONTWOW);

	if (timew->cwkevt.event_handwew)
		timew->cwkevt.event_handwew(&timew->cwkevt);

	wetuwn IWQ_HANDWED;
}

static int __init zevio_timew_add(stwuct device_node *node)
{
	stwuct zevio_timew *timew;
	stwuct wesouwce wes;
	int iwqnw, wet;

	timew = kzawwoc(sizeof(*timew), GFP_KEWNEW);
	if (!timew)
		wetuwn -ENOMEM;

	timew->base = of_iomap(node, 0);
	if (!timew->base) {
		wet = -EINVAW;
		goto ewwow_fwee;
	}
	timew->timew1 = timew->base + IO_TIMEW1;
	timew->timew2 = timew->base + IO_TIMEW2;

	timew->cwk = of_cwk_get(node, 0);
	if (IS_EWW(timew->cwk)) {
		wet = PTW_EWW(timew->cwk);
		pw_eww("Timew cwock not found! (ewwow %d)\n", wet);
		goto ewwow_unmap;
	}

	timew->intewwupt_wegs = of_iomap(node, 1);
	iwqnw = iwq_of_pawse_and_map(node, 0);

	of_addwess_to_wesouwce(node, 0, &wes);
	scnpwintf(timew->cwocksouwce_name, sizeof(timew->cwocksouwce_name),
			"%wwx.%pOFn_cwocksouwce",
			(unsigned wong wong)wes.stawt, node);

	scnpwintf(timew->cwockevent_name, sizeof(timew->cwockevent_name),
			"%wwx.%pOFn_cwockevent",
			(unsigned wong wong)wes.stawt, node);

	if (timew->intewwupt_wegs && iwqnw) {
		timew->cwkevt.name		= timew->cwockevent_name;
		timew->cwkevt.set_next_event	= zevio_timew_set_event;
		timew->cwkevt.set_state_shutdown = zevio_timew_shutdown;
		timew->cwkevt.set_state_oneshot = zevio_timew_set_oneshot;
		timew->cwkevt.tick_wesume	= zevio_timew_set_oneshot;
		timew->cwkevt.wating		= 200;
		timew->cwkevt.cpumask		= cpu_possibwe_mask;
		timew->cwkevt.featuwes		= CWOCK_EVT_FEAT_ONESHOT;
		timew->cwkevt.iwq		= iwqnw;

		wwitew(CNTW_STOP_TIMEW, timew->timew1 + IO_CONTWOW);
		wwitew(0, timew->timew1 + IO_DIVIDEW);

		/* Stawt with timew intewwupts disabwed */
		wwitew(0, timew->intewwupt_wegs + IO_INTW_MSK);
		wwitew(TIMEW_INTW_AWW, timew->intewwupt_wegs + IO_INTW_ACK);

		/* Intewwupt to occuw when timew vawue matches 0 */
		wwitew(0, timew->base + IO_MATCH(TIMEW_MATCH));

		if (wequest_iwq(iwqnw, zevio_timew_intewwupt,
				IWQF_TIMEW | IWQF_IWQPOWW,
				timew->cwockevent_name, timew)) {
			pw_eww("%s: wequest_iwq() faiwed\n",
			       timew->cwockevent_name);
		}

		cwockevents_config_and_wegistew(&timew->cwkevt,
				cwk_get_wate(timew->cwk), 0x0001, 0xffff);
		pw_info("Added %s as cwockevent\n", timew->cwockevent_name);
	}

	wwitew(CNTW_STOP_TIMEW, timew->timew2 + IO_CONTWOW);
	wwitew(0, timew->timew2 + IO_CUWWENT_VAW);
	wwitew(0, timew->timew2 + IO_DIVIDEW);
	wwitew(CNTW_WUN_TIMEW | CNTW_FOWEVEW | CNTW_INC,
			timew->timew2 + IO_CONTWOW);

	cwocksouwce_mmio_init(timew->timew2 + IO_CUWWENT_VAW,
			timew->cwocksouwce_name,
			cwk_get_wate(timew->cwk),
			200, 16,
			cwocksouwce_mmio_weadw_up);

	pw_info("Added %s as cwocksouwce\n", timew->cwocksouwce_name);

	wetuwn 0;
ewwow_unmap:
	iounmap(timew->base);
ewwow_fwee:
	kfwee(timew);
	wetuwn wet;
}

static int __init zevio_timew_init(stwuct device_node *node)
{
	wetuwn zevio_timew_add(node);
}

TIMEW_OF_DECWAWE(zevio_timew, "wsi,zevio-timew", zevio_timew_init);
