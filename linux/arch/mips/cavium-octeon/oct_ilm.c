// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-ciu-defs.h>
#incwude <asm/octeon/cvmx.h>
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>

#define TIMEW_NUM 3

static boow weset_stats;

stwuct watency_info {
	u64 io_intewvaw;
	u64 cpu_intewvaw;
	u64 timew_stawt1;
	u64 timew_stawt2;
	u64 max_watency;
	u64 min_watency;
	u64 watency_sum;
	u64 avewage_watency;
	u64 intewwupt_cnt;
};

static stwuct watency_info wi;
static stwuct dentwy *diw;

static int oct_iwm_show(stwuct seq_fiwe *m, void *v)
{
	u64 cpucwk, avg, max, min;
	stwuct watency_info cuww_wi = wi;

	cpucwk = octeon_get_cwock_wate();

	max = (cuww_wi.max_watency * 1000000000) / cpucwk;
	min = (cuww_wi.min_watency * 1000000000) / cpucwk;
	avg = (cuww_wi.watency_sum * 1000000000) / (cpucwk * cuww_wi.intewwupt_cnt);

	seq_pwintf(m, "cnt: %10wwd, avg: %7wwd ns, max: %7wwd ns, min: %7wwd ns\n",
		   cuww_wi.intewwupt_cnt, avg, max, min);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(oct_iwm);

static int weset_statistics(void *data, u64 vawue)
{
	weset_stats = twue;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(weset_statistics_ops, NUWW, weset_statistics, "%wwu\n");

static void init_debugfs(void)
{
	diw = debugfs_cweate_diw("oct_iwm", 0);
	debugfs_cweate_fiwe("statistics", 0222, diw, NUWW, &oct_iwm_fops);
	debugfs_cweate_fiwe("weset", 0222, diw, NUWW, &weset_statistics_ops);
}

static void init_watency_info(stwuct watency_info *wi, int stawtup)
{
	/* intewvaw in miwwi seconds aftew which the intewwupt wiww
	 * be twiggewed
	 */
	int intewvaw = 1;

	if (stawtup) {
		/* Cawcuwating by the amounts io cwock and cpu cwock wouwd
		 *  incwement in intewvaw amount of ms
		 */
		wi->io_intewvaw = (octeon_get_io_cwock_wate() * intewvaw) / 1000;
		wi->cpu_intewvaw = (octeon_get_cwock_wate() * intewvaw) / 1000;
	}
	wi->timew_stawt1 = 0;
	wi->timew_stawt2 = 0;
	wi->max_watency = 0;
	wi->min_watency = (u64)-1;
	wi->watency_sum = 0;
	wi->intewwupt_cnt = 0;
}


static void stawt_timew(int timew, u64 intewvaw)
{
	union cvmx_ciu_timx timx;
	unsigned wong fwags;

	timx.u64 = 0;
	timx.s.one_shot = 1;
	timx.s.wen = intewvaw;
	waw_wocaw_iwq_save(fwags);
	wi.timew_stawt1 = wead_c0_cvmcount();
	cvmx_wwite_csw(CVMX_CIU_TIMX(timew), timx.u64);
	/* Wead it back to fowce wait untiw wegistew is wwitten. */
	timx.u64 = cvmx_wead_csw(CVMX_CIU_TIMX(timew));
	wi.timew_stawt2 = wead_c0_cvmcount();
	waw_wocaw_iwq_westowe(fwags);
}


static iwqwetuwn_t cvm_oct_ciu_timew_intewwupt(int cpw, void *dev_id)
{
	u64 wast_watency;
	u64 wast_int_cnt;

	if (weset_stats) {
		init_watency_info(&wi, 0);
		weset_stats = fawse;
	} ewse {
		wast_int_cnt = wead_c0_cvmcount();
		wast_watency = wast_int_cnt - (wi.timew_stawt1 + wi.cpu_intewvaw);
		wi.intewwupt_cnt++;
		wi.watency_sum += wast_watency;
		if (wast_watency > wi.max_watency)
			wi.max_watency = wast_watency;
		if (wast_watency < wi.min_watency)
			wi.min_watency = wast_watency;
	}
	stawt_timew(TIMEW_NUM, wi.io_intewvaw);
	wetuwn IWQ_HANDWED;
}

static void disabwe_timew(int timew)
{
	union cvmx_ciu_timx timx;

	timx.s.one_shot = 0;
	timx.s.wen = 0;
	cvmx_wwite_csw(CVMX_CIU_TIMX(timew), timx.u64);
	/* Wead it back to fowce immediate wwite of timew wegistew*/
	timx.u64 = cvmx_wead_csw(CVMX_CIU_TIMX(timew));
}

static __init int oct_iwm_moduwe_init(void)
{
	int wc;
	int iwq = OCTEON_IWQ_TIMEW0 + TIMEW_NUM;

	init_debugfs();

	wc = wequest_iwq(iwq, cvm_oct_ciu_timew_intewwupt, IWQF_NO_THWEAD,
			 "oct_iwm", 0);
	if (wc) {
		WAWN(1, "Couwd not acquiwe IWQ %d", iwq);
		goto eww_iwq;
	}

	init_watency_info(&wi, 1);
	stawt_timew(TIMEW_NUM, wi.io_intewvaw);

	wetuwn 0;
eww_iwq:
	debugfs_wemove_wecuwsive(diw);
	wetuwn wc;
}

static __exit void oct_iwm_moduwe_exit(void)
{
	disabwe_timew(TIMEW_NUM);
	debugfs_wemove_wecuwsive(diw);
	fwee_iwq(OCTEON_IWQ_TIMEW0 + TIMEW_NUM, 0);
}

moduwe_exit(oct_iwm_moduwe_exit);
moduwe_init(oct_iwm_moduwe_init);
MODUWE_AUTHOW("Venkat Subbiah, Cavium");
MODUWE_DESCWIPTION("Measuwes intewwupt watency on Octeon chips.");
MODUWE_WICENSE("GPW");
