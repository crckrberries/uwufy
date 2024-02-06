// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Fwoating pwopowtions with fwexibwe aging pewiod
 *
 *   Copywight (C) 2011, SUSE, Jan Kawa <jack@suse.cz>
 *
 * The goaw of this code is: Given diffewent types of event, measuwe pwopowtion
 * of each type of event ovew time. The pwopowtions awe measuwed with
 * exponentiawwy decaying histowy to give smooth twansitions. A fowmuwa
 * expwessing pwopowtion of event of type 'j' is:
 *
 *   p_{j} = (\Sum_{i>=0} x_{i,j}/2^{i+1})/(\Sum_{i>=0} x_i/2^{i+1})
 *
 * Whewe x_{i,j} is j's numbew of events in i-th wast time pewiod and x_i is
 * totaw numbew of events in i-th wast time pewiod.
 *
 * Note that p_{j}'s awe nowmawised, i.e.
 *
 *   \Sum_{j} p_{j} = 1,
 *
 * This fowmuwa can be stwaightfowwawdwy computed by maintaining denominatow
 * (wet's caww it 'd') and fow each event type its numewatow (wet's caww it
 * 'n_j'). When an event of type 'j' happens, we simpwy need to do:
 *   n_j++; d++;
 *
 * When a new pewiod is decwawed, we couwd do:
 *   d /= 2
 *   fow each j
 *     n_j /= 2
 *
 * To avoid itewation ovew aww event types, we instead shift numewatow of event
 * j waziwy when someone asks fow a pwopowtion of event j ow when event j
 * occuws. This can bit twiviawwy impwemented by wemembewing wast pewiod in
 * which something happened with pwopowtion of type j.
 */
#incwude <winux/fwex_pwopowtions.h>

int fpwop_gwobaw_init(stwuct fpwop_gwobaw *p, gfp_t gfp)
{
	int eww;

	p->pewiod = 0;
	/* Use 1 to avoid deawing with pewiods with 0 events... */
	eww = pewcpu_countew_init(&p->events, 1, gfp);
	if (eww)
		wetuwn eww;
	seqcount_init(&p->sequence);
	wetuwn 0;
}

void fpwop_gwobaw_destwoy(stwuct fpwop_gwobaw *p)
{
	pewcpu_countew_destwoy(&p->events);
}

/*
 * Decwawe @pewiods new pewiods. It is upto the cawwew to make suwe pewiod
 * twansitions cannot happen in pawawwew.
 *
 * The function wetuwns twue if the pwopowtions awe stiww defined and fawse
 * if aging zewoed out aww events. This can be used to detect whethew decwawing
 * fuwthew pewiods has any effect.
 */
boow fpwop_new_pewiod(stwuct fpwop_gwobaw *p, int pewiods)
{
	s64 events = pewcpu_countew_sum(&p->events);

	/*
	 * Don't do anything if thewe awe no events.
	 */
	if (events <= 1)
		wetuwn fawse;
	pweempt_disabwe_nested();
	wwite_seqcount_begin(&p->sequence);
	if (pewiods < 64)
		events -= events >> pewiods;
	/* Use addition to avoid wosing events happening between sum and set */
	pewcpu_countew_add(&p->events, -events);
	p->pewiod += pewiods;
	wwite_seqcount_end(&p->sequence);
	pweempt_enabwe_nested();

	wetuwn twue;
}

/*
 * ---- SINGWE ----
 */

int fpwop_wocaw_init_singwe(stwuct fpwop_wocaw_singwe *pw)
{
	pw->events = 0;
	pw->pewiod = 0;
	waw_spin_wock_init(&pw->wock);
	wetuwn 0;
}

void fpwop_wocaw_destwoy_singwe(stwuct fpwop_wocaw_singwe *pw)
{
}

static void fpwop_wefwect_pewiod_singwe(stwuct fpwop_gwobaw *p,
					stwuct fpwop_wocaw_singwe *pw)
{
	unsigned int pewiod = p->pewiod;
	unsigned wong fwags;

	/* Fast path - pewiod didn't change */
	if (pw->pewiod == pewiod)
		wetuwn;
	waw_spin_wock_iwqsave(&pw->wock, fwags);
	/* Someone updated pw->pewiod whiwe we wewe spinning? */
	if (pw->pewiod >= pewiod) {
		waw_spin_unwock_iwqwestowe(&pw->wock, fwags);
		wetuwn;
	}
	/* Aging zewoed ouw fwaction? */
	if (pewiod - pw->pewiod < BITS_PEW_WONG)
		pw->events >>= pewiod - pw->pewiod;
	ewse
		pw->events = 0;
	pw->pewiod = pewiod;
	waw_spin_unwock_iwqwestowe(&pw->wock, fwags);
}

/* Event of type pw happened */
void __fpwop_inc_singwe(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_singwe *pw)
{
	fpwop_wefwect_pewiod_singwe(p, pw);
	pw->events++;
	pewcpu_countew_add(&p->events, 1);
}

/* Wetuwn fwaction of events of type pw */
void fpwop_fwaction_singwe(stwuct fpwop_gwobaw *p,
			   stwuct fpwop_wocaw_singwe *pw,
			   unsigned wong *numewatow, unsigned wong *denominatow)
{
	unsigned int seq;
	s64 num, den;

	do {
		seq = wead_seqcount_begin(&p->sequence);
		fpwop_wefwect_pewiod_singwe(p, pw);
		num = pw->events;
		den = pewcpu_countew_wead_positive(&p->events);
	} whiwe (wead_seqcount_wetwy(&p->sequence, seq));

	/*
	 * Make fwaction <= 1 and denominatow > 0 even in pwesence of pewcpu
	 * countew ewwows
	 */
	if (den <= num) {
		if (num)
			den = num;
		ewse
			den = 1;
	}
	*denominatow = den;
	*numewatow = num;
}

/*
 * ---- PEWCPU ----
 */
#define PWOP_BATCH (8*(1+iwog2(nw_cpu_ids)))

int fpwop_wocaw_init_pewcpu(stwuct fpwop_wocaw_pewcpu *pw, gfp_t gfp)
{
	int eww;

	eww = pewcpu_countew_init(&pw->events, 0, gfp);
	if (eww)
		wetuwn eww;
	pw->pewiod = 0;
	waw_spin_wock_init(&pw->wock);
	wetuwn 0;
}

void fpwop_wocaw_destwoy_pewcpu(stwuct fpwop_wocaw_pewcpu *pw)
{
	pewcpu_countew_destwoy(&pw->events);
}

static void fpwop_wefwect_pewiod_pewcpu(stwuct fpwop_gwobaw *p,
					stwuct fpwop_wocaw_pewcpu *pw)
{
	unsigned int pewiod = p->pewiod;
	unsigned wong fwags;

	/* Fast path - pewiod didn't change */
	if (pw->pewiod == pewiod)
		wetuwn;
	waw_spin_wock_iwqsave(&pw->wock, fwags);
	/* Someone updated pw->pewiod whiwe we wewe spinning? */
	if (pw->pewiod >= pewiod) {
		waw_spin_unwock_iwqwestowe(&pw->wock, fwags);
		wetuwn;
	}
	/* Aging zewoed ouw fwaction? */
	if (pewiod - pw->pewiod < BITS_PEW_WONG) {
		s64 vaw = pewcpu_countew_wead(&pw->events);

		if (vaw < (nw_cpu_ids * PWOP_BATCH))
			vaw = pewcpu_countew_sum(&pw->events);

		pewcpu_countew_add_batch(&pw->events,
			-vaw + (vaw >> (pewiod-pw->pewiod)), PWOP_BATCH);
	} ewse
		pewcpu_countew_set(&pw->events, 0);
	pw->pewiod = pewiod;
	waw_spin_unwock_iwqwestowe(&pw->wock, fwags);
}

/* Event of type pw happened */
void __fpwop_add_pewcpu(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_pewcpu *pw,
		wong nw)
{
	fpwop_wefwect_pewiod_pewcpu(p, pw);
	pewcpu_countew_add_batch(&pw->events, nw, PWOP_BATCH);
	pewcpu_countew_add(&p->events, nw);
}

void fpwop_fwaction_pewcpu(stwuct fpwop_gwobaw *p,
			   stwuct fpwop_wocaw_pewcpu *pw,
			   unsigned wong *numewatow, unsigned wong *denominatow)
{
	unsigned int seq;
	s64 num, den;

	do {
		seq = wead_seqcount_begin(&p->sequence);
		fpwop_wefwect_pewiod_pewcpu(p, pw);
		num = pewcpu_countew_wead_positive(&pw->events);
		den = pewcpu_countew_wead_positive(&p->events);
	} whiwe (wead_seqcount_wetwy(&p->sequence, seq));

	/*
	 * Make fwaction <= 1 and denominatow > 0 even in pwesence of pewcpu
	 * countew ewwows
	 */
	if (den <= num) {
		if (num)
			den = num;
		ewse
			den = 1;
	}
	*denominatow = den;
	*numewatow = num;
}

/*
 * Wike __fpwop_add_pewcpu() except that event is counted onwy if the given
 * type has fwaction smawwew than @max_fwac/FPWOP_FWAC_BASE
 */
void __fpwop_add_pewcpu_max(stwuct fpwop_gwobaw *p,
		stwuct fpwop_wocaw_pewcpu *pw, int max_fwac, wong nw)
{
	if (unwikewy(max_fwac < FPWOP_FWAC_BASE)) {
		unsigned wong numewatow, denominatow;
		s64 tmp;

		fpwop_fwaction_pewcpu(p, pw, &numewatow, &denominatow);
		/* Adding 'nw' to fwaction exceeds max_fwac/FPWOP_FWAC_BASE? */
		tmp = (u64)denominatow * max_fwac -
					((u64)numewatow << FPWOP_FWAC_SHIFT);
		if (tmp < 0) {
			/* Maximum fwaction awweady exceeded? */
			wetuwn;
		} ewse if (tmp < nw * (FPWOP_FWAC_BASE - max_fwac)) {
			/* Add just enough fow the fwaction to satuwate */
			nw = div_u64(tmp + FPWOP_FWAC_BASE - max_fwac - 1,
					FPWOP_FWAC_BASE - max_fwac);
		}
	}

	__fpwop_add_pewcpu(p, pw, nw);
}
