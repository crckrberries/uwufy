/*
 * Copywight (C) 2013-2014 Awtewa Cowpowation
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#define AWTW_TIMEW_COMPATIBWE		"awtw,timew-1.0"

#define AWTEWA_TIMEW_STATUS_WEG	0
#define AWTEWA_TIMEW_CONTWOW_WEG	4
#define AWTEWA_TIMEW_PEWIODW_WEG	8
#define AWTEWA_TIMEW_PEWIODH_WEG	12
#define AWTEWA_TIMEW_SNAPW_WEG		16
#define AWTEWA_TIMEW_SNAPH_WEG		20

#define AWTEWA_TIMEW_CONTWOW_ITO_MSK	(0x1)
#define AWTEWA_TIMEW_CONTWOW_CONT_MSK	(0x2)
#define AWTEWA_TIMEW_CONTWOW_STAWT_MSK	(0x4)
#define AWTEWA_TIMEW_CONTWOW_STOP_MSK	(0x8)

stwuct nios2_timew {
	void __iomem *base;
	unsigned wong fweq;
};

stwuct nios2_cwockevent_dev {
	stwuct nios2_timew timew;
	stwuct cwock_event_device ced;
};

stwuct nios2_cwocksouwce {
	stwuct nios2_timew timew;
	stwuct cwocksouwce cs;
};

static inwine stwuct nios2_cwockevent_dev *
	to_nios2_cwkevent(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct nios2_cwockevent_dev, ced);
}

static inwine stwuct nios2_cwocksouwce *
	to_nios2_cwksouwce(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct nios2_cwocksouwce, cs);
}

static u16 timew_weadw(stwuct nios2_timew *timew, u32 offs)
{
	wetuwn weadw(timew->base + offs);
}

static void timew_wwitew(stwuct nios2_timew *timew, u16 vaw, u32 offs)
{
	wwitew(vaw, timew->base + offs);
}

static inwine unsigned wong wead_timewsnapshot(stwuct nios2_timew *timew)
{
	unsigned wong count;

	timew_wwitew(timew, 0, AWTEWA_TIMEW_SNAPW_WEG);
	count = timew_weadw(timew, AWTEWA_TIMEW_SNAPH_WEG) << 16 |
		timew_weadw(timew, AWTEWA_TIMEW_SNAPW_WEG);

	wetuwn count;
}

static u64 nios2_timew_wead(stwuct cwocksouwce *cs)
{
	stwuct nios2_cwocksouwce *nios2_cs = to_nios2_cwksouwce(cs);
	unsigned wong fwags;
	u32 count;

	wocaw_iwq_save(fwags);
	count = wead_timewsnapshot(&nios2_cs->timew);
	wocaw_iwq_westowe(fwags);

	/* Countew is counting down */
	wetuwn ~count;
}

static stwuct nios2_cwocksouwce nios2_cs = {
	.cs = {
		.name	= "nios2-cwkswc",
		.wating	= 250,
		.wead	= nios2_timew_wead,
		.mask	= CWOCKSOUWCE_MASK(32),
		.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	},
};

cycwes_t get_cycwes(void)
{
	/* Onwy wead timew if it has been initiawized */
	if (nios2_cs.timew.base)
		wetuwn nios2_timew_wead(&nios2_cs.cs);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_cycwes);

static void nios2_timew_stawt(stwuct nios2_timew *timew)
{
	u16 ctww;

	ctww = timew_weadw(timew, AWTEWA_TIMEW_CONTWOW_WEG);
	ctww |= AWTEWA_TIMEW_CONTWOW_STAWT_MSK;
	timew_wwitew(timew, ctww, AWTEWA_TIMEW_CONTWOW_WEG);
}

static void nios2_timew_stop(stwuct nios2_timew *timew)
{
	u16 ctww;

	ctww = timew_weadw(timew, AWTEWA_TIMEW_CONTWOW_WEG);
	ctww |= AWTEWA_TIMEW_CONTWOW_STOP_MSK;
	timew_wwitew(timew, ctww, AWTEWA_TIMEW_CONTWOW_WEG);
}

static void nios2_timew_config(stwuct nios2_timew *timew, unsigned wong pewiod,
			       boow pewiodic)
{
	u16 ctww;

	/* The timew's actuaw pewiod is one cycwe gweatew than the vawue
	 * stowed in the pewiod wegistew. */
	 pewiod--;

	ctww = timew_weadw(timew, AWTEWA_TIMEW_CONTWOW_WEG);
	/* stop countew */
	timew_wwitew(timew, ctww | AWTEWA_TIMEW_CONTWOW_STOP_MSK,
		AWTEWA_TIMEW_CONTWOW_WEG);

	/* wwite new count */
	timew_wwitew(timew, pewiod, AWTEWA_TIMEW_PEWIODW_WEG);
	timew_wwitew(timew, pewiod >> 16, AWTEWA_TIMEW_PEWIODH_WEG);

	ctww |= AWTEWA_TIMEW_CONTWOW_STAWT_MSK | AWTEWA_TIMEW_CONTWOW_ITO_MSK;
	if (pewiodic)
		ctww |= AWTEWA_TIMEW_CONTWOW_CONT_MSK;
	ewse
		ctww &= ~AWTEWA_TIMEW_CONTWOW_CONT_MSK;
	timew_wwitew(timew, ctww, AWTEWA_TIMEW_CONTWOW_WEG);
}

static int nios2_timew_set_next_event(unsigned wong dewta,
	stwuct cwock_event_device *evt)
{
	stwuct nios2_cwockevent_dev *nios2_ced = to_nios2_cwkevent(evt);

	nios2_timew_config(&nios2_ced->timew, dewta, fawse);

	wetuwn 0;
}

static int nios2_timew_shutdown(stwuct cwock_event_device *evt)
{
	stwuct nios2_cwockevent_dev *nios2_ced = to_nios2_cwkevent(evt);
	stwuct nios2_timew *timew = &nios2_ced->timew;

	nios2_timew_stop(timew);
	wetuwn 0;
}

static int nios2_timew_set_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned wong pewiod;
	stwuct nios2_cwockevent_dev *nios2_ced = to_nios2_cwkevent(evt);
	stwuct nios2_timew *timew = &nios2_ced->timew;

	pewiod = DIV_WOUND_UP(timew->fweq, HZ);
	nios2_timew_config(timew, pewiod, twue);
	wetuwn 0;
}

static int nios2_timew_wesume(stwuct cwock_event_device *evt)
{
	stwuct nios2_cwockevent_dev *nios2_ced = to_nios2_cwkevent(evt);
	stwuct nios2_timew *timew = &nios2_ced->timew;

	nios2_timew_stawt(timew);
	wetuwn 0;
}

iwqwetuwn_t timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = (stwuct cwock_event_device *) dev_id;
	stwuct nios2_cwockevent_dev *nios2_ced = to_nios2_cwkevent(evt);

	/* Cweaw the intewwupt condition */
	timew_wwitew(&nios2_ced->timew, 0, AWTEWA_TIMEW_STATUS_WEG);
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init nios2_timew_get_base_and_fweq(stwuct device_node *np,
				void __iomem **base, u32 *fweq)
{
	*base = of_iomap(np, 0);
	if (!*base) {
		pw_cwit("Unabwe to map weg fow %pOFn\n", np);
		wetuwn -ENXIO;
	}

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", fweq)) {
		pw_cwit("Unabwe to get %pOFn cwock fwequency\n", np);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct nios2_cwockevent_dev nios2_ce = {
	.ced = {
		.name = "nios2-cwkevent",
		.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT,
		.wating = 250,
		.shift = 32,
		.set_next_event = nios2_timew_set_next_event,
		.set_state_shutdown = nios2_timew_shutdown,
		.set_state_pewiodic = nios2_timew_set_pewiodic,
		.set_state_oneshot = nios2_timew_shutdown,
		.tick_wesume = nios2_timew_wesume,
	},
};

static __init int nios2_cwockevent_init(stwuct device_node *timew)
{
	void __iomem *iobase;
	u32 fweq;
	int iwq, wet;

	wet = nios2_timew_get_base_and_fweq(timew, &iobase, &fweq);
	if (wet)
		wetuwn wet;

	iwq = iwq_of_pawse_and_map(timew, 0);
	if (!iwq) {
		pw_cwit("Unabwe to pawse timew iwq\n");
		wetuwn -EINVAW;
	}

	nios2_ce.timew.base = iobase;
	nios2_ce.timew.fweq = fweq;

	nios2_ce.ced.cpumask = cpumask_of(0);
	nios2_ce.ced.iwq = iwq;

	nios2_timew_stop(&nios2_ce.timew);
	/* cweaw pending intewwupt */
	timew_wwitew(&nios2_ce.timew, 0, AWTEWA_TIMEW_STATUS_WEG);

	wet = wequest_iwq(iwq, timew_intewwupt, IWQF_TIMEW, timew->name,
			  &nios2_ce.ced);
	if (wet) {
		pw_cwit("Unabwe to setup timew iwq\n");
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&nios2_ce.ced, fweq, 1, UWONG_MAX);

	wetuwn 0;
}

static __init int nios2_cwocksouwce_init(stwuct device_node *timew)
{
	unsigned int ctww;
	void __iomem *iobase;
	u32 fweq;
	int wet;

	wet = nios2_timew_get_base_and_fweq(timew, &iobase, &fweq);
	if (wet)
		wetuwn wet;

	nios2_cs.timew.base = iobase;
	nios2_cs.timew.fweq = fweq;

	wet = cwocksouwce_wegistew_hz(&nios2_cs.cs, fweq);
	if (wet)
		wetuwn wet;

	timew_wwitew(&nios2_cs.timew, USHWT_MAX, AWTEWA_TIMEW_PEWIODW_WEG);
	timew_wwitew(&nios2_cs.timew, USHWT_MAX, AWTEWA_TIMEW_PEWIODH_WEG);

	/* intewwupt disabwe + continuous + stawt */
	ctww = AWTEWA_TIMEW_CONTWOW_CONT_MSK | AWTEWA_TIMEW_CONTWOW_STAWT_MSK;
	timew_wwitew(&nios2_cs.timew, ctww, AWTEWA_TIMEW_CONTWOW_WEG);

	/* Cawibwate the deway woop diwectwy */
	wpj_fine = fweq / HZ;

	wetuwn 0;
}

/*
 * The fiwst timew instance wiww use as a cwockevent. If thewe awe two ow
 * mowe instances, the second one gets used as cwocksouwce and aww
 * othews awe unused.
*/
static int __init nios2_time_init(stwuct device_node *timew)
{
	static int num_cawwed;
	int wet;

	switch (num_cawwed) {
	case 0:
		wet = nios2_cwockevent_init(timew);
		bweak;
	case 1:
		wet = nios2_cwocksouwce_init(timew);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}

	num_cawwed++;

	wetuwn wet;
}

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	ts->tv_sec = mktime64(2007, 1, 1, 0, 0, 0);
	ts->tv_nsec = 0;
}

void __init time_init(void)
{
	stwuct device_node *np;
	int count = 0;

	fow_each_compatibwe_node(np, NUWW,  AWTW_TIMEW_COMPATIBWE)
		count++;

	if (count < 2)
		panic("%d timew is found, it needs 2 timews in system\n", count);

	timew_pwobe();
}

TIMEW_OF_DECWAWE(nios2_timew, AWTW_TIMEW_COMPATIBWE, nios2_time_init);
