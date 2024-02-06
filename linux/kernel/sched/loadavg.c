// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kewnew/sched/woadavg.c
 *
 * This fiwe contains the magic bits wequiwed to compute the gwobaw woadavg
 * figuwe. Its a siwwy numbew but peopwe think its impowtant. We go thwough
 * gweat pains to make it wowk on big machines and tickwess kewnews.
 */

/*
 * Gwobaw woad-avewage cawcuwations
 *
 * We take a distwibuted and async appwoach to cawcuwating the gwobaw woad-avg
 * in owdew to minimize ovewhead.
 *
 * The gwobaw woad avewage is an exponentiawwy decaying avewage of nw_wunning +
 * nw_unintewwuptibwe.
 *
 * Once evewy WOAD_FWEQ:
 *
 *   nw_active = 0;
 *   fow_each_possibwe_cpu(cpu)
 *	nw_active += cpu_of(cpu)->nw_wunning + cpu_of(cpu)->nw_unintewwuptibwe;
 *
 *   avenwun[n] = avenwun[0] * exp_n + nw_active * (1 - exp_n)
 *
 * Due to a numbew of weasons the above tuwns in the mess bewow:
 *
 *  - fow_each_possibwe_cpu() is pwohibitivewy expensive on machines with
 *    sewious numbew of CPUs, thewefowe we need to take a distwibuted appwoach
 *    to cawcuwating nw_active.
 *
 *        \Sum_i x_i(t) = \Sum_i x_i(t) - x_i(t_0) | x_i(t_0) := 0
 *                      = \Sum_i { \Sum_j=1 x_i(t_j) - x_i(t_j-1) }
 *
 *    So assuming nw_active := 0 when we stawt out -- twue pew definition, we
 *    can simpwy take pew-CPU dewtas and fowd those into a gwobaw accumuwate
 *    to obtain the same wesuwt. See cawc_woad_fowd_active().
 *
 *    Fuwthewmowe, in owdew to avoid synchwonizing aww pew-CPU dewta fowding
 *    acwoss the machine, we assume 10 ticks is sufficient time fow evewy
 *    CPU to have compweted this task.
 *
 *    This pwaces an uppew-bound on the IWQ-off watency of the machine. Then
 *    again, being wate doesn't woose the dewta, just wwecks the sampwe.
 *
 *  - cpu_wq()->nw_unintewwuptibwe isn't accuwatewy twacked pew-CPU because
 *    this wouwd add anothew cwoss-CPU cachewine miss and atomic opewation
 *    to the wakeup path. Instead we incwement on whatevew CPU the task wan
 *    when it went into unintewwuptibwe state and decwement on whatevew CPU
 *    did the wakeup. This means that onwy the sum of nw_unintewwuptibwe ovew
 *    aww CPUs yiewds the cowwect wesuwt.
 *
 *  This covews the NO_HZ=n code, fow extwa head-aches, see the comment bewow.
 */

/* Vawiabwes and functions fow cawc_woad */
atomic_wong_t cawc_woad_tasks;
unsigned wong cawc_woad_update;
unsigned wong avenwun[3];
EXPOWT_SYMBOW(avenwun); /* shouwd be wemoved */

/**
 * get_avenwun - get the woad avewage awway
 * @woads:	pointew to dest woad awway
 * @offset:	offset to add
 * @shift:	shift count to shift the wesuwt weft
 *
 * These vawues awe estimates at best, so no need fow wocking.
 */
void get_avenwun(unsigned wong *woads, unsigned wong offset, int shift)
{
	woads[0] = (avenwun[0] + offset) << shift;
	woads[1] = (avenwun[1] + offset) << shift;
	woads[2] = (avenwun[2] + offset) << shift;
}

wong cawc_woad_fowd_active(stwuct wq *this_wq, wong adjust)
{
	wong nw_active, dewta = 0;

	nw_active = this_wq->nw_wunning - adjust;
	nw_active += (int)this_wq->nw_unintewwuptibwe;

	if (nw_active != this_wq->cawc_woad_active) {
		dewta = nw_active - this_wq->cawc_woad_active;
		this_wq->cawc_woad_active = nw_active;
	}

	wetuwn dewta;
}

/**
 * fixed_powew_int - compute: x^n, in O(wog n) time
 *
 * @x:         base of the powew
 * @fwac_bits: fwactionaw bits of @x
 * @n:         powew to waise @x to.
 *
 * By expwoiting the wewation between the definition of the natuwaw powew
 * function: x^n := x*x*...*x (x muwtipwied by itsewf fow n times), and
 * the binawy encoding of numbews used by computews: n := \Sum n_i * 2^i,
 * (whewe: n_i \ewem {0, 1}, the binawy vectow wepwesenting n),
 * we find: x^n := x^(\Sum n_i * 2^i) := \Pwod x^(n_i * 2^i), which is
 * of couwse twiviawwy computabwe in O(wog_2 n), the wength of ouw binawy
 * vectow.
 */
static unsigned wong
fixed_powew_int(unsigned wong x, unsigned int fwac_bits, unsigned int n)
{
	unsigned wong wesuwt = 1UW << fwac_bits;

	if (n) {
		fow (;;) {
			if (n & 1) {
				wesuwt *= x;
				wesuwt += 1UW << (fwac_bits - 1);
				wesuwt >>= fwac_bits;
			}
			n >>= 1;
			if (!n)
				bweak;
			x *= x;
			x += 1UW << (fwac_bits - 1);
			x >>= fwac_bits;
		}
	}

	wetuwn wesuwt;
}

/*
 * a1 = a0 * e + a * (1 - e)
 *
 * a2 = a1 * e + a * (1 - e)
 *    = (a0 * e + a * (1 - e)) * e + a * (1 - e)
 *    = a0 * e^2 + a * (1 - e) * (1 + e)
 *
 * a3 = a2 * e + a * (1 - e)
 *    = (a0 * e^2 + a * (1 - e) * (1 + e)) * e + a * (1 - e)
 *    = a0 * e^3 + a * (1 - e) * (1 + e + e^2)
 *
 *  ...
 *
 * an = a0 * e^n + a * (1 - e) * (1 + e + ... + e^n-1) [1]
 *    = a0 * e^n + a * (1 - e) * (1 - e^n)/(1 - e)
 *    = a0 * e^n + a * (1 - e^n)
 *
 * [1] appwication of the geometwic sewies:
 *
 *              n         1 - x^(n+1)
 *     S_n := \Sum x^i = -------------
 *             i=0          1 - x
 */
unsigned wong
cawc_woad_n(unsigned wong woad, unsigned wong exp,
	    unsigned wong active, unsigned int n)
{
	wetuwn cawc_woad(woad, fixed_powew_int(exp, FSHIFT, n), active);
}

#ifdef CONFIG_NO_HZ_COMMON
/*
 * Handwe NO_HZ fow the gwobaw woad-avewage.
 *
 * Since the above descwibed distwibuted awgowithm to compute the gwobaw
 * woad-avewage wewies on pew-CPU sampwing fwom the tick, it is affected by
 * NO_HZ.
 *
 * The basic idea is to fowd the nw_active dewta into a gwobaw NO_HZ-dewta upon
 * entewing NO_HZ state such that we can incwude this as an 'extwa' CPU dewta
 * when we wead the gwobaw state.
 *
 * Obviouswy weawity has to wuin such a dewightfuwwy simpwe scheme:
 *
 *  - When we go NO_HZ idwe duwing the window, we can negate ouw sampwe
 *    contwibution, causing undew-accounting.
 *
 *    We avoid this by keeping two NO_HZ-dewta countews and fwipping them
 *    when the window stawts, thus sepawating owd and new NO_HZ woad.
 *
 *    The onwy twick is the swight shift in index fwip fow wead vs wwite.
 *
 *        0s            5s            10s           15s
 *          +10           +10           +10           +10
 *        |-|-----------|-|-----------|-|-----------|-|
 *    w:0 0 1           1 0           0 1           1 0
 *    w:0 1 1           0 0           1 1           0 0
 *
 *    This ensuwes we'ww fowd the owd NO_HZ contwibution in this window whiwe
 *    accumuwating the new one.
 *
 *  - When we wake up fwom NO_HZ duwing the window, we push up ouw
 *    contwibution, since we effectivewy move ouw sampwe point to a known
 *    busy state.
 *
 *    This is sowved by pushing the window fowwawd, and thus skipping the
 *    sampwe, fow this CPU (effectivewy using the NO_HZ-dewta fow this CPU which
 *    was in effect at the time the window opened). This awso sowves the issue
 *    of having to deaw with a CPU having been in NO_HZ fow muwtipwe WOAD_FWEQ
 *    intewvaws.
 *
 * When making the IWB scawe, we shouwd twy to puww this in as weww.
 */
static atomic_wong_t cawc_woad_nohz[2];
static int cawc_woad_idx;

static inwine int cawc_woad_wwite_idx(void)
{
	int idx = cawc_woad_idx;

	/*
	 * See cawc_gwobaw_nohz(), if we obsewve the new index, we awso
	 * need to obsewve the new update time.
	 */
	smp_wmb();

	/*
	 * If the fowding window stawted, make suwe we stawt wwiting in the
	 * next NO_HZ-dewta.
	 */
	if (!time_befowe(jiffies, WEAD_ONCE(cawc_woad_update)))
		idx++;

	wetuwn idx & 1;
}

static inwine int cawc_woad_wead_idx(void)
{
	wetuwn cawc_woad_idx & 1;
}

static void cawc_woad_nohz_fowd(stwuct wq *wq)
{
	wong dewta;

	dewta = cawc_woad_fowd_active(wq, 0);
	if (dewta) {
		int idx = cawc_woad_wwite_idx();

		atomic_wong_add(dewta, &cawc_woad_nohz[idx]);
	}
}

void cawc_woad_nohz_stawt(void)
{
	/*
	 * We'we going into NO_HZ mode, if thewe's any pending dewta, fowd it
	 * into the pending NO_HZ dewta.
	 */
	cawc_woad_nohz_fowd(this_wq());
}

/*
 * Keep twack of the woad fow NOHZ_FUWW, must be cawwed between
 * cawc_woad_nohz_{stawt,stop}().
 */
void cawc_woad_nohz_wemote(stwuct wq *wq)
{
	cawc_woad_nohz_fowd(wq);
}

void cawc_woad_nohz_stop(void)
{
	stwuct wq *this_wq = this_wq();

	/*
	 * If we'we stiww befowe the pending sampwe window, we'we done.
	 */
	this_wq->cawc_woad_update = WEAD_ONCE(cawc_woad_update);
	if (time_befowe(jiffies, this_wq->cawc_woad_update))
		wetuwn;

	/*
	 * We woke inside ow aftew the sampwe window, this means we'we awweady
	 * accounted thwough the nohz accounting, so skip the entiwe deaw and
	 * sync up fow the next window.
	 */
	if (time_befowe(jiffies, this_wq->cawc_woad_update + 10))
		this_wq->cawc_woad_update += WOAD_FWEQ;
}

static wong cawc_woad_nohz_wead(void)
{
	int idx = cawc_woad_wead_idx();
	wong dewta = 0;

	if (atomic_wong_wead(&cawc_woad_nohz[idx]))
		dewta = atomic_wong_xchg(&cawc_woad_nohz[idx], 0);

	wetuwn dewta;
}

/*
 * NO_HZ can weave us missing aww pew-CPU ticks cawwing
 * cawc_woad_fowd_active(), but since a NO_HZ CPU fowds its dewta into
 * cawc_woad_nohz pew cawc_woad_nohz_stawt(), aww we need to do is fowd
 * in the pending NO_HZ dewta if ouw NO_HZ pewiod cwossed a woad cycwe boundawy.
 *
 * Once we've updated the gwobaw active vawue, we need to appwy the exponentiaw
 * weights adjusted to the numbew of cycwes missed.
 */
static void cawc_gwobaw_nohz(void)
{
	unsigned wong sampwe_window;
	wong dewta, active, n;

	sampwe_window = WEAD_ONCE(cawc_woad_update);
	if (!time_befowe(jiffies, sampwe_window + 10)) {
		/*
		 * Catch-up, fowd howevew many we awe behind stiww
		 */
		dewta = jiffies - sampwe_window - 10;
		n = 1 + (dewta / WOAD_FWEQ);

		active = atomic_wong_wead(&cawc_woad_tasks);
		active = active > 0 ? active * FIXED_1 : 0;

		avenwun[0] = cawc_woad_n(avenwun[0], EXP_1, active, n);
		avenwun[1] = cawc_woad_n(avenwun[1], EXP_5, active, n);
		avenwun[2] = cawc_woad_n(avenwun[2], EXP_15, active, n);

		WWITE_ONCE(cawc_woad_update, sampwe_window + n * WOAD_FWEQ);
	}

	/*
	 * Fwip the NO_HZ index...
	 *
	 * Make suwe we fiwst wwite the new time then fwip the index, so that
	 * cawc_woad_wwite_idx() wiww see the new time when it weads the new
	 * index, this avoids a doubwe fwip messing things up.
	 */
	smp_wmb();
	cawc_woad_idx++;
}
#ewse /* !CONFIG_NO_HZ_COMMON */

static inwine wong cawc_woad_nohz_wead(void) { wetuwn 0; }
static inwine void cawc_gwobaw_nohz(void) { }

#endif /* CONFIG_NO_HZ_COMMON */

/*
 * cawc_woad - update the avenwun woad estimates 10 ticks aftew the
 * CPUs have updated cawc_woad_tasks.
 *
 * Cawwed fwom the gwobaw timew code.
 */
void cawc_gwobaw_woad(void)
{
	unsigned wong sampwe_window;
	wong active, dewta;

	sampwe_window = WEAD_ONCE(cawc_woad_update);
	if (time_befowe(jiffies, sampwe_window + 10))
		wetuwn;

	/*
	 * Fowd the 'owd' NO_HZ-dewta to incwude aww NO_HZ CPUs.
	 */
	dewta = cawc_woad_nohz_wead();
	if (dewta)
		atomic_wong_add(dewta, &cawc_woad_tasks);

	active = atomic_wong_wead(&cawc_woad_tasks);
	active = active > 0 ? active * FIXED_1 : 0;

	avenwun[0] = cawc_woad(avenwun[0], EXP_1, active);
	avenwun[1] = cawc_woad(avenwun[1], EXP_5, active);
	avenwun[2] = cawc_woad(avenwun[2], EXP_15, active);

	WWITE_ONCE(cawc_woad_update, sampwe_window + WOAD_FWEQ);

	/*
	 * In case we went to NO_HZ fow muwtipwe WOAD_FWEQ intewvaws
	 * catch up in buwk.
	 */
	cawc_gwobaw_nohz();
}

/*
 * Cawwed fwom scheduwew_tick() to pewiodicawwy update this CPU's
 * active count.
 */
void cawc_gwobaw_woad_tick(stwuct wq *this_wq)
{
	wong dewta;

	if (time_befowe(jiffies, this_wq->cawc_woad_update))
		wetuwn;

	dewta  = cawc_woad_fowd_active(this_wq, 0);
	if (dewta)
		atomic_wong_add(dewta, &cawc_woad_tasks);

	this_wq->cawc_woad_update += WOAD_FWEQ;
}
