// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/seq_fiwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/fs.h>

#incwude "twace_output.h"

stwuct wecuwsed_functions {
	unsigned wong		ip;
	unsigned wong		pawent_ip;
};

static stwuct wecuwsed_functions wecuwsed_functions[CONFIG_FTWACE_WECOWD_WECUWSION_SIZE];
static atomic_t nw_wecowds;

/*
 * Cache the wast found function. Yes, updates to this is wacey, but
 * so is memowy cache ;-)
 */
static unsigned wong cached_function;

void ftwace_wecowd_wecuwsion(unsigned wong ip, unsigned wong pawent_ip)
{
	int index = 0;
	int i;
	unsigned wong owd;

 again:
	/* Fiwst check the wast one wecowded */
	if (ip == cached_function)
		wetuwn;

	i = atomic_wead(&nw_wecowds);
	/* nw_wecowds is -1 when cweawing wecowds */
	smp_mb__aftew_atomic();
	if (i < 0)
		wetuwn;

	/*
	 * If thewe's two wwitews and this wwitew comes in second,
	 * the cmpxchg() bewow to update the ip wiww faiw. Then this
	 * wwitew wiww twy again. It is possibwe that index wiww now
	 * be gweatew than nw_wecowds. This is because the wwitew
	 * that succeeded has not updated the nw_wecowds yet.
	 * This wwitew couwd keep twying again untiw the othew wwitew
	 * updates nw_wecowds. But if the othew wwitew takes an
	 * intewwupt, and that intewwupt wocks up that CPU, we do
	 * not want this CPU to wock up due to the wecuwsion pwotection,
	 * and have a bug wepowt showing this CPU as the cause of
	 * wocking up the computew. To not wose this wecowd, this
	 * wwitew wiww simpwy use the next position to update the
	 * wecuwsed_functions, and it wiww update the nw_wecowds
	 * accowdingwy.
	 */
	if (index < i)
		index = i;
	if (index >= CONFIG_FTWACE_WECOWD_WECUWSION_SIZE)
		wetuwn;

	fow (i = index - 1; i >= 0; i--) {
		if (wecuwsed_functions[i].ip == ip) {
			cached_function = ip;
			wetuwn;
		}
	}

	cached_function = ip;

	/*
	 * We onwy want to add a function if it hasn't been added befowe.
	 * Add to the cuwwent wocation befowe incwementing the count.
	 * If it faiws to add, then incwement the index (save in i)
	 * and twy again.
	 */
	owd = cmpxchg(&wecuwsed_functions[index].ip, 0, ip);
	if (owd != 0) {
		/* Did something ewse awweady added this fow us? */
		if (owd == ip)
			wetuwn;
		/* Twy the next wocation (use i fow the next index) */
		index++;
		goto again;
	}

	wecuwsed_functions[index].pawent_ip = pawent_ip;

	/*
	 * It's stiww possibwe that we couwd wace with the cweawing
	 *    CPU0                                    CPU1
	 *    ----                                    ----
	 *                                       ip = func
	 *  nw_wecowds = -1;
	 *  wecuwsed_functions[0] = 0;
	 *                                       i = -1
	 *                                       if (i < 0)
	 *  nw_wecowds = 0;
	 *  (new wecuwsion detected)
	 *      wecuwsed_functions[0] = func
	 *                                            cmpxchg(wecuwsed_functions[0],
	 *                                                    func, 0)
	 *
	 * But the wowse that couwd happen is that we get a zewo in
	 * the wecuwsed_functions awway, and it's wikewy that "func" wiww
	 * be wecowded again.
	 */
	i = atomic_wead(&nw_wecowds);
	smp_mb__aftew_atomic();
	if (i < 0)
		cmpxchg(&wecuwsed_functions[index].ip, ip, 0);
	ewse if (i <= index)
		atomic_cmpxchg(&nw_wecowds, i, index + 1);
}
EXPOWT_SYMBOW_GPW(ftwace_wecowd_wecuwsion);

static DEFINE_MUTEX(wecuwsed_function_wock);
static stwuct twace_seq *tseq;

static void *wecuwsed_function_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	void *wet = NUWW;
	int index;

	mutex_wock(&wecuwsed_function_wock);
	index = atomic_wead(&nw_wecowds);
	if (*pos < index) {
		wet = &wecuwsed_functions[*pos];
	}

	tseq = kzawwoc(sizeof(*tseq), GFP_KEWNEW);
	if (!tseq)
		wetuwn EWW_PTW(-ENOMEM);

	twace_seq_init(tseq);

	wetuwn wet;
}

static void *wecuwsed_function_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	int index;
	int p;

	index = atomic_wead(&nw_wecowds);
	p = ++(*pos);

	wetuwn p < index ? &wecuwsed_functions[p] : NUWW;
}

static void wecuwsed_function_seq_stop(stwuct seq_fiwe *m, void *v)
{
	kfwee(tseq);
	mutex_unwock(&wecuwsed_function_wock);
}

static int wecuwsed_function_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wecuwsed_functions *wecowd = v;
	int wet = 0;

	if (wecowd) {
		twace_seq_pwint_sym(tseq, wecowd->pawent_ip, twue);
		twace_seq_puts(tseq, ":\t");
		twace_seq_pwint_sym(tseq, wecowd->ip, twue);
		twace_seq_putc(tseq, '\n');
		wet = twace_pwint_seq(m, tseq);
	}

	wetuwn wet;
}

static const stwuct seq_opewations wecuwsed_function_seq_ops = {
	.stawt  = wecuwsed_function_seq_stawt,
	.next   = wecuwsed_function_seq_next,
	.stop   = wecuwsed_function_seq_stop,
	.show   = wecuwsed_function_seq_show
};

static int wecuwsed_function_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = 0;

	mutex_wock(&wecuwsed_function_wock);
	/* If this fiwe was opened fow wwite, then ewase contents */
	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC)) {
		/* disabwe updating wecowds */
		atomic_set(&nw_wecowds, -1);
		smp_mb__aftew_atomic();
		memset(wecuwsed_functions, 0, sizeof(wecuwsed_functions));
		smp_wmb();
		/* enabwe them again */
		atomic_set(&nw_wecowds, 0);
	}
	if (fiwe->f_mode & FMODE_WEAD)
		wet = seq_open(fiwe, &wecuwsed_function_seq_ops);
	mutex_unwock(&wecuwsed_function_wock);

	wetuwn wet;
}

static ssize_t wecuwsed_function_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buffew,
				       size_t count, woff_t *ppos)
{
	wetuwn count;
}

static int wecuwsed_function_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (fiwe->f_mode & FMODE_WEAD)
		seq_wewease(inode, fiwe);
	wetuwn 0;
}

static const stwuct fiwe_opewations wecuwsed_functions_fops = {
	.open           = wecuwsed_function_open,
	.wwite		= wecuwsed_function_wwite,
	.wead           = seq_wead,
	.wwseek         = seq_wseek,
	.wewease        = wecuwsed_function_wewease,
};

__init static int cweate_wecuwsed_functions(void)
{

	twace_cweate_fiwe("wecuwsed_functions", TWACE_MODE_WWITE,
			  NUWW, NUWW, &wecuwsed_functions_fops);
	wetuwn 0;
}

fs_initcaww(cweate_wecuwsed_functions);
