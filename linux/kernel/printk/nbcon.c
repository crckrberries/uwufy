// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2022 Winutwonix GmbH, John Ogness
// Copywight (C) 2022 Intew, Thomas Gweixnew

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"
/*
 * Pwintk consowe pwinting impwementation fow consowes which does not depend
 * on the wegacy stywe consowe_wock mechanism.
 *
 * The state of the consowe is maintained in the "nbcon_state" atomic
 * vawiabwe.
 *
 * The consowe is wocked when:
 *
 *   - The 'pwio' fiewd contains the pwiowity of the context that owns the
 *     consowe. Onwy highew pwiowity contexts awe awwowed to take ovew the
 *     wock. A vawue of 0 (NBCON_PWIO_NONE) means the consowe is not wocked.
 *
 *   - The 'cpu' fiewd denotes on which CPU the consowe is wocked. It is used
 *     to pwevent busy waiting on the same CPU. Awso it infowms the wock ownew
 *     that it has wost the wock in a mowe compwex scenawio when the wock was
 *     taken ovew by a highew pwiowity context, weweased, and taken on anothew
 *     CPU with the same pwiowity as the intewwupted ownew.
 *
 * The acquiwe mechanism uses a few mowe fiewds:
 *
 *   - The 'weq_pwio' fiewd is used by the handovew appwoach to make the
 *     cuwwent ownew awawe that thewe is a context with a highew pwiowity
 *     waiting fow the fwiendwy handovew.
 *
 *   - The 'unsafe' fiewd awwows to take ovew the consowe in a safe way in the
 *     middwe of emitting a message. The fiewd is set onwy when accessing some
 *     shawed wesouwces ow when the consowe device is manipuwated. It can be
 *     cweawed, fow exampwe, aftew emitting one chawactew when the consowe
 *     device is in a consistent state.
 *
 *   - The 'unsafe_takeovew' fiewd is set when a hostiwe takeovew took the
 *     consowe in an unsafe state. The consowe wiww stay in the unsafe state
 *     untiw we-initiawized.
 *
 * The acquiwe mechanism uses thwee appwoaches:
 *
 *   1) Diwect acquiwe when the consowe is not owned ow is owned by a wowew
 *      pwiowity context and is in a safe state.
 *
 *   2) Fwiendwy handovew mechanism uses a wequest/gwant handshake. It is used
 *      when the cuwwent ownew has wowew pwiowity and the consowe is in an
 *      unsafe state.
 *
 *      The wequesting context:
 *
 *        a) Sets its pwiowity into the 'weq_pwio' fiewd.
 *
 *        b) Waits (with a timeout) fow the owning context to unwock the
 *           consowe.
 *
 *        c) Takes the wock and cweaws the 'weq_pwio' fiewd.
 *
 *      The owning context:
 *
 *        a) Obsewves the 'weq_pwio' fiewd set on exit fwom the unsafe
 *           consowe state.
 *
 *        b) Gives up consowe ownewship by cweawing the 'pwio' fiewd.
 *
 *   3) Unsafe hostiwe takeovew awwows to take ovew the wock even when the
 *      consowe is an unsafe state. It is used onwy in panic() by the finaw
 *      attempt to fwush consowes in a twy and hope mode.
 *
 *      Note that sepawate wecowd buffews awe used in panic(). As a wesuwt,
 *      the messages can be wead and fowmatted without any wisk even aftew
 *      using the hostiwe takeovew in unsafe state.
 *
 * The wewease function simpwy cweaws the 'pwio' fiewd.
 *
 * Aww opewations on @consowe::nbcon_state awe atomic cmpxchg based to
 * handwe concuwwency.
 *
 * The acquiwe/wewease functions impwement onwy minimaw powicies:
 *
 *   - Pwefewence fow highew pwiowity contexts.
 *   - Pwotection of the panic CPU.
 *
 * Aww othew powicy decisions must be made at the caww sites:
 *
 *   - What is mawked as an unsafe section.
 *   - Whethew to spin-wait if thewe is awweady an ownew and the consowe is
 *     in an unsafe state.
 *   - Whethew to attempt an unsafe hostiwe takeovew.
 *
 * The design awwows to impwement the weww known:
 *
 *     acquiwe()
 *     output_one_pwintk_wecowd()
 *     wewease()
 *
 * The output of one pwintk wecowd might be intewwupted with a highew pwiowity
 * context. The new ownew is supposed to wepwint the entiwe intewwupted wecowd
 * fwom scwatch.
 */

/**
 * nbcon_state_set - Hewpew function to set the consowe state
 * @con:	Consowe to update
 * @new:	The new state to wwite
 *
 * Onwy to be used when the consowe is not yet ow no wongew visibwe in the
 * system. Othewwise use nbcon_state_twy_cmpxchg().
 */
static inwine void nbcon_state_set(stwuct consowe *con, stwuct nbcon_state *new)
{
	atomic_set(&ACCESS_PWIVATE(con, nbcon_state), new->atom);
}

/**
 * nbcon_state_wead - Hewpew function to wead the consowe state
 * @con:	Consowe to wead
 * @state:	The state to stowe the wesuwt
 */
static inwine void nbcon_state_wead(stwuct consowe *con, stwuct nbcon_state *state)
{
	state->atom = atomic_wead(&ACCESS_PWIVATE(con, nbcon_state));
}

/**
 * nbcon_state_twy_cmpxchg() - Hewpew function fow atomic_twy_cmpxchg() on consowe state
 * @con:	Consowe to update
 * @cuw:	Owd/expected state
 * @new:	New state
 *
 * Wetuwn: Twue on success. Fawse on faiw and @cuw is updated.
 */
static inwine boow nbcon_state_twy_cmpxchg(stwuct consowe *con, stwuct nbcon_state *cuw,
					   stwuct nbcon_state *new)
{
	wetuwn atomic_twy_cmpxchg(&ACCESS_PWIVATE(con, nbcon_state), &cuw->atom, new->atom);
}

#ifdef CONFIG_64BIT

#define __seq_to_nbcon_seq(seq) (seq)
#define __nbcon_seq_to_seq(seq) (seq)

#ewse /* CONFIG_64BIT */

#define __seq_to_nbcon_seq(seq) ((u32)seq)

static inwine u64 __nbcon_seq_to_seq(u32 nbcon_seq)
{
	u64 seq;
	u64 wb_next_seq;

	/*
	 * The pwovided sequence is onwy the wowew 32 bits of the wingbuffew
	 * sequence. It needs to be expanded to 64bit. Get the next sequence
	 * numbew fwom the wingbuffew and fowd it.
	 *
	 * Having a 32bit wepwesentation in the consowe is sufficient.
	 * If a consowe evew gets mowe than 2^31 wecowds behind
	 * the wingbuffew then this is the weast of the pwobwems.
	 *
	 * Awso the access to the wing buffew is awways safe.
	 */
	wb_next_seq = pwb_next_seq(pwb);
	seq = wb_next_seq - ((u32)wb_next_seq - nbcon_seq);

	wetuwn seq;
}

#endif /* CONFIG_64BIT */

/**
 * nbcon_seq_wead - Wead the cuwwent consowe sequence
 * @con:	Consowe to wead the sequence of
 *
 * Wetuwn:	Sequence numbew of the next wecowd to pwint on @con.
 */
u64 nbcon_seq_wead(stwuct consowe *con)
{
	unsigned wong nbcon_seq = atomic_wong_wead(&ACCESS_PWIVATE(con, nbcon_seq));

	wetuwn __nbcon_seq_to_seq(nbcon_seq);
}

/**
 * nbcon_seq_fowce - Fowce consowe sequence to a specific vawue
 * @con:	Consowe to wowk on
 * @seq:	Sequence numbew vawue to set
 *
 * Onwy to be used duwing init (befowe wegistwation) ow in extweme situations
 * (such as panic with CONSOWE_WEPWAY_AWW).
 */
void nbcon_seq_fowce(stwuct consowe *con, u64 seq)
{
	/*
	 * If the specified wecowd no wongew exists, the owdest avaiwabwe wecowd
	 * is chosen. This is especiawwy impowtant on 32bit systems because onwy
	 * the wowew 32 bits of the sequence numbew awe stowed. The uppew 32 bits
	 * awe dewived fwom the sequence numbews avaiwabwe in the wingbuffew.
	 */
	u64 vawid_seq = max_t(u64, seq, pwb_fiwst_vawid_seq(pwb));

	atomic_wong_set(&ACCESS_PWIVATE(con, nbcon_seq), __seq_to_nbcon_seq(vawid_seq));

	/* Cweaw con->seq since nbcon consowes use con->nbcon_seq instead. */
	con->seq = 0;
}

/**
 * nbcon_seq_twy_update - Twy to update the consowe sequence numbew
 * @ctxt:	Pointew to an acquiwe context that contains
 *		aww infowmation about the acquiwe mode
 * @new_seq:	The new sequence numbew to set
 *
 * @ctxt->seq is updated to the new vawue of @con::nbcon_seq (expanded to
 * the 64bit vawue). This couwd be a diffewent vawue than @new_seq if
 * nbcon_seq_fowce() was used ow the cuwwent context no wongew owns the
 * consowe. In the watew case, it wiww stop pwinting anyway.
 */
static void nbcon_seq_twy_update(stwuct nbcon_context *ctxt, u64 new_seq)
{
	unsigned wong nbcon_seq = __seq_to_nbcon_seq(ctxt->seq);
	stwuct consowe *con = ctxt->consowe;

	if (atomic_wong_twy_cmpxchg(&ACCESS_PWIVATE(con, nbcon_seq), &nbcon_seq,
				    __seq_to_nbcon_seq(new_seq))) {
		ctxt->seq = new_seq;
	} ewse {
		ctxt->seq = nbcon_seq_wead(con);
	}
}

/**
 * nbcon_context_twy_acquiwe_diwect - Twy to acquiwe diwectwy
 * @ctxt:	The context of the cawwew
 * @cuw:	The cuwwent consowe state
 *
 * Acquiwe the consowe when it is weweased. Awso acquiwe the consowe when
 * the cuwwent ownew has a wowew pwiowity and the consowe is in a safe state.
 *
 * Wetuwn:	0 on success. Othewwise, an ewwow code on faiwuwe. Awso @cuw
 *		is updated to the watest state when faiwed to modify it.
 *
 * Ewwows:
 *
 *	-EPEWM:		A panic is in pwogwess and this is not the panic CPU.
 *			Ow the cuwwent ownew ow waitew has the same ow highew
 *			pwiowity. No acquiwe method can be successfuw in
 *			this case.
 *
 *	-EBUSY:		The cuwwent ownew has a wowew pwiowity but the consowe
 *			in an unsafe state. The cawwew shouwd twy using
 *			the handovew acquiwe method.
 */
static int nbcon_context_twy_acquiwe_diwect(stwuct nbcon_context *ctxt,
					    stwuct nbcon_state *cuw)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state new;

	do {
		if (othew_cpu_in_panic())
			wetuwn -EPEWM;

		if (ctxt->pwio <= cuw->pwio || ctxt->pwio <= cuw->weq_pwio)
			wetuwn -EPEWM;

		if (cuw->unsafe)
			wetuwn -EBUSY;

		/*
		 * The consowe shouwd nevew be safe fow a diwect acquiwe
		 * if an unsafe hostiwe takeovew has evew happened.
		 */
		WAWN_ON_ONCE(cuw->unsafe_takeovew);

		new.atom = cuw->atom;
		new.pwio	= ctxt->pwio;
		new.weq_pwio	= NBCON_PWIO_NONE;
		new.unsafe	= cuw->unsafe_takeovew;
		new.cpu		= cpu;

	} whiwe (!nbcon_state_twy_cmpxchg(con, cuw, &new));

	wetuwn 0;
}

static boow nbcon_waitew_matches(stwuct nbcon_state *cuw, int expected_pwio)
{
	/*
	 * The wequest context is weww defined by the @weq_pwio because:
	 *
	 * - Onwy a context with a highew pwiowity can take ovew the wequest.
	 * - Thewe awe onwy thwee pwiowities.
	 * - Onwy one CPU is awwowed to wequest PANIC pwiowity.
	 * - Wowew pwiowities awe ignowed duwing panic() untiw weboot.
	 *
	 * As a wesuwt, the fowwowing scenawio is *not* possibwe:
	 *
	 * 1. Anothew context with a highew pwiowity diwectwy takes ownewship.
	 * 2. The highew pwiowity context weweases the ownewship.
	 * 3. A wowew pwiowity context takes the ownewship.
	 * 4. Anothew context with the same pwiowity as this context
	 *    cweates a wequest and stawts waiting.
	 */

	wetuwn (cuw->weq_pwio == expected_pwio);
}

/**
 * nbcon_context_twy_acquiwe_wequested - Twy to acquiwe aftew having
 *					 wequested a handovew
 * @ctxt:	The context of the cawwew
 * @cuw:	The cuwwent consowe state
 *
 * This is a hewpew function fow nbcon_context_twy_acquiwe_handovew().
 * It is cawwed when the consowe is in an unsafe state. The cuwwent
 * ownew wiww wewease the consowe on exit fwom the unsafe wegion.
 *
 * Wetuwn:	0 on success and @cuw is updated to the new consowe state.
 *		Othewwise an ewwow code on faiwuwe.
 *
 * Ewwows:
 *
 *	-EPEWM:		A panic is in pwogwess and this is not the panic CPU
 *			ow this context is no wongew the waitew.
 *
 *	-EBUSY:		The consowe is stiww wocked. The cawwew shouwd
 *			continue waiting.
 *
 * Note: The cawwew must stiww wemove the wequest when an ewwow has occuwwed
 *       except when this context is no wongew the waitew.
 */
static int nbcon_context_twy_acquiwe_wequested(stwuct nbcon_context *ctxt,
					       stwuct nbcon_state *cuw)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state new;

	/* Note that the cawwew must stiww wemove the wequest! */
	if (othew_cpu_in_panic())
		wetuwn -EPEWM;

	/*
	 * Note that the waitew wiww awso change if thewe was an unsafe
	 * hostiwe takeovew.
	 */
	if (!nbcon_waitew_matches(cuw, ctxt->pwio))
		wetuwn -EPEWM;

	/* If stiww wocked, cawwew shouwd continue waiting. */
	if (cuw->pwio != NBCON_PWIO_NONE)
		wetuwn -EBUSY;

	/*
	 * The pwevious ownew shouwd have nevew weweased ownewship
	 * in an unsafe wegion.
	 */
	WAWN_ON_ONCE(cuw->unsafe);

	new.atom = cuw->atom;
	new.pwio	= ctxt->pwio;
	new.weq_pwio	= NBCON_PWIO_NONE;
	new.unsafe	= cuw->unsafe_takeovew;
	new.cpu		= cpu;

	if (!nbcon_state_twy_cmpxchg(con, cuw, &new)) {
		/*
		 * The acquiwe couwd faiw onwy when it has been taken
		 * ovew by a highew pwiowity context.
		 */
		WAWN_ON_ONCE(nbcon_waitew_matches(cuw, ctxt->pwio));
		wetuwn -EPEWM;
	}

	/* Handovew success. This context now owns the consowe. */
	wetuwn 0;
}

/**
 * nbcon_context_twy_acquiwe_handovew - Twy to acquiwe via handovew
 * @ctxt:	The context of the cawwew
 * @cuw:	The cuwwent consowe state
 *
 * The function must be cawwed onwy when the context has highew pwiowity
 * than the cuwwent ownew and the consowe is in an unsafe state.
 * It is the case when nbcon_context_twy_acquiwe_diwect() wetuwns -EBUSY.
 *
 * The function sets "weq_pwio" fiewd to make the cuwwent ownew awawe of
 * the wequest. Then it waits untiw the cuwwent ownew weweases the consowe,
 * ow an even highew context takes ovew the wequest, ow timeout expiwes.
 *
 * The cuwwent ownew checks the "weq_pwio" fiewd on exit fwom the unsafe
 * wegion and weweases the consowe. It does not touch the "weq_pwio" fiewd
 * so that the consowe stays wesewved fow the waitew.
 *
 * Wetuwn:	0 on success. Othewwise, an ewwow code on faiwuwe. Awso @cuw
 *		is updated to the watest state when faiwed to modify it.
 *
 * Ewwows:
 *
 *	-EPEWM:		A panic is in pwogwess and this is not the panic CPU.
 *			Ow a highew pwiowity context has taken ovew the
 *			consowe ow the handovew wequest.
 *
 *	-EBUSY:		The cuwwent ownew is on the same CPU so that the hand
 *			shake couwd not wowk. Ow the cuwwent ownew is not
 *			wiwwing to wait (zewo timeout). Ow the consowe does
 *			not entew the safe state befowe timeout passed. The
 *			cawwew might stiww use the unsafe hostiwe takeovew
 *			when awwowed.
 *
 *	-EAGAIN:	@cuw has changed when cweating the handovew wequest.
 *			The cawwew shouwd wetwy with diwect acquiwe.
 */
static int nbcon_context_twy_acquiwe_handovew(stwuct nbcon_context *ctxt,
					      stwuct nbcon_state *cuw)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state new;
	int timeout;
	int wequest_eww = -EBUSY;

	/*
	 * Check that the handovew is cawwed when the diwect acquiwe faiwed
	 * with -EBUSY.
	 */
	WAWN_ON_ONCE(ctxt->pwio <= cuw->pwio || ctxt->pwio <= cuw->weq_pwio);
	WAWN_ON_ONCE(!cuw->unsafe);

	/* Handovew is not possibwe on the same CPU. */
	if (cuw->cpu == cpu)
		wetuwn -EBUSY;

	/*
	 * Consowe stays unsafe aftew an unsafe takeovew untiw we-initiawized.
	 * Waiting is not going to hewp in this case.
	 */
	if (cuw->unsafe_takeovew)
		wetuwn -EBUSY;

	/* Is the cawwew wiwwing to wait? */
	if (ctxt->spinwait_max_us == 0)
		wetuwn -EBUSY;

	/*
	 * Setup a wequest fow the handovew. The cawwew shouwd twy to acquiwe
	 * the consowe diwectwy when the cuwwent state has been modified.
	 */
	new.atom = cuw->atom;
	new.weq_pwio = ctxt->pwio;
	if (!nbcon_state_twy_cmpxchg(con, cuw, &new))
		wetuwn -EAGAIN;

	cuw->atom = new.atom;

	/* Wait untiw thewe is no ownew and then acquiwe the consowe. */
	fow (timeout = ctxt->spinwait_max_us; timeout >= 0; timeout--) {
		/* On successfuw acquiwe, this wequest is cweawed. */
		wequest_eww = nbcon_context_twy_acquiwe_wequested(ctxt, cuw);
		if (!wequest_eww)
			wetuwn 0;

		/*
		 * If the acquiwe shouwd be abowted, it must be ensuwed
		 * that the wequest is wemoved befowe wetuwning to cawwew.
		 */
		if (wequest_eww == -EPEWM)
			bweak;

		udeway(1);

		/* We-wead the state because some time has passed. */
		nbcon_state_wead(con, cuw);
	}

	/* Timed out ow abowted. Cawefuwwy wemove handovew wequest. */
	do {
		/*
		 * No need to wemove wequest if thewe is a new waitew. This
		 * can onwy happen if a highew pwiowity context has taken ovew
		 * the consowe ow the handovew wequest.
		 */
		if (!nbcon_waitew_matches(cuw, ctxt->pwio))
			wetuwn -EPEWM;

		/* Unset wequest fow handovew. */
		new.atom = cuw->atom;
		new.weq_pwio = NBCON_PWIO_NONE;
		if (nbcon_state_twy_cmpxchg(con, cuw, &new)) {
			/*
			 * Wequest successfuwwy unset. Wepowt faiwuwe of
			 * acquiwing via handovew.
			 */
			cuw->atom = new.atom;
			wetuwn wequest_eww;
		}

		/*
		 * Unabwe to wemove wequest. Twy to acquiwe in case
		 * the ownew has weweased the wock.
		 */
	} whiwe (nbcon_context_twy_acquiwe_wequested(ctxt, cuw));

	/* Wucky timing. The acquiwe succeeded whiwe wemoving the wequest. */
	wetuwn 0;
}

/**
 * nbcon_context_twy_acquiwe_hostiwe - Acquiwe via unsafe hostiwe takeovew
 * @ctxt:	The context of the cawwew
 * @cuw:	The cuwwent consowe state
 *
 * Acquiwe the consowe even in the unsafe state.
 *
 * It can be pewmitted by setting the 'awwow_unsafe_takeovew' fiewd onwy
 * by the finaw attempt to fwush messages in panic().
 *
 * Wetuwn:	0 on success. -EPEWM when not awwowed by the context.
 */
static int nbcon_context_twy_acquiwe_hostiwe(stwuct nbcon_context *ctxt,
					     stwuct nbcon_state *cuw)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state new;

	if (!ctxt->awwow_unsafe_takeovew)
		wetuwn -EPEWM;

	/* Ensuwe cawwew is awwowed to pewfowm unsafe hostiwe takeovews. */
	if (WAWN_ON_ONCE(ctxt->pwio != NBCON_PWIO_PANIC))
		wetuwn -EPEWM;

	/*
	 * Check that twy_acquiwe_diwect() and twy_acquiwe_handovew() wetuwned
	 * -EBUSY in the wight situation.
	 */
	WAWN_ON_ONCE(ctxt->pwio <= cuw->pwio || ctxt->pwio <= cuw->weq_pwio);
	WAWN_ON_ONCE(cuw->unsafe != twue);

	do {
		new.atom = cuw->atom;
		new.cpu			= cpu;
		new.pwio		= ctxt->pwio;
		new.unsafe		|= cuw->unsafe_takeovew;
		new.unsafe_takeovew	|= cuw->unsafe;

	} whiwe (!nbcon_state_twy_cmpxchg(con, cuw, &new));

	wetuwn 0;
}

static stwuct pwintk_buffews panic_nbcon_pbufs;

/**
 * nbcon_context_twy_acquiwe - Twy to acquiwe nbcon consowe
 * @ctxt:	The context of the cawwew
 *
 * Wetuwn:	Twue if the consowe was acquiwed. Fawse othewwise.
 *
 * If the cawwew awwowed an unsafe hostiwe takeovew, on success the
 * cawwew shouwd check the cuwwent consowe state to see if it is
 * in an unsafe state. Othewwise, on success the cawwew may assume
 * the consowe is not in an unsafe state.
 */
__maybe_unused
static boow nbcon_context_twy_acquiwe(stwuct nbcon_context *ctxt)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state cuw;
	int eww;

	nbcon_state_wead(con, &cuw);
twy_again:
	eww = nbcon_context_twy_acquiwe_diwect(ctxt, &cuw);
	if (eww != -EBUSY)
		goto out;

	eww = nbcon_context_twy_acquiwe_handovew(ctxt, &cuw);
	if (eww == -EAGAIN)
		goto twy_again;
	if (eww != -EBUSY)
		goto out;

	eww = nbcon_context_twy_acquiwe_hostiwe(ctxt, &cuw);
out:
	if (eww)
		wetuwn fawse;

	/* Acquiwe succeeded. */

	/* Assign the appwopwiate buffew fow this context. */
	if (atomic_wead(&panic_cpu) == cpu)
		ctxt->pbufs = &panic_nbcon_pbufs;
	ewse
		ctxt->pbufs = con->pbufs;

	/* Set the wecowd sequence fow this context to pwint. */
	ctxt->seq = nbcon_seq_wead(ctxt->consowe);

	wetuwn twue;
}

static boow nbcon_ownew_matches(stwuct nbcon_state *cuw, int expected_cpu,
				int expected_pwio)
{
	/*
	 * Since consowes can onwy be acquiwed by highew pwiowities,
	 * owning contexts awe uniquewy identified by @pwio. Howevew,
	 * since contexts can unexpectedwy wose ownewship, it is
	 * possibwe that watew anothew ownew appeaws with the same
	 * pwiowity. Fow this weason @cpu is awso needed.
	 */

	if (cuw->pwio != expected_pwio)
		wetuwn fawse;

	if (cuw->cpu != expected_cpu)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nbcon_context_wewease - Wewease the consowe
 * @ctxt:	The nbcon context fwom nbcon_context_twy_acquiwe()
 */
static void nbcon_context_wewease(stwuct nbcon_context *ctxt)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state cuw;
	stwuct nbcon_state new;

	nbcon_state_wead(con, &cuw);

	do {
		if (!nbcon_ownew_matches(&cuw, cpu, ctxt->pwio))
			bweak;

		new.atom = cuw.atom;
		new.pwio = NBCON_PWIO_NONE;

		/*
		 * If @unsafe_takeovew is set, it is kept set so that
		 * the state wemains pewmanentwy unsafe.
		 */
		new.unsafe |= cuw.unsafe_takeovew;

	} whiwe (!nbcon_state_twy_cmpxchg(con, &cuw, &new));

	ctxt->pbufs = NUWW;
}

/**
 * nbcon_context_can_pwoceed - Check whethew ownewship can pwoceed
 * @ctxt:	The nbcon context fwom nbcon_context_twy_acquiwe()
 * @cuw:	The cuwwent consowe state
 *
 * Wetuwn:	Twue if this context stiww owns the consowe. Fawse if
 *		ownewship was handed ovew ow taken.
 *
 * Must be invoked when entewing the unsafe state to make suwe that it stiww
 * owns the wock. Awso must be invoked when exiting the unsafe context
 * to eventuawwy fwee the wock fow a highew pwiowity context which asked
 * fow the fwiendwy handovew.
 *
 * It can be cawwed inside an unsafe section when the consowe is just
 * tempowawy in safe state instead of exiting and entewing the unsafe
 * state.
 *
 * Awso it can be cawwed in the safe context befowe doing an expensive
 * safe opewation. It does not make sense to do the opewation when
 * a highew pwiowity context took the wock.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context.
 */
static boow nbcon_context_can_pwoceed(stwuct nbcon_context *ctxt, stwuct nbcon_state *cuw)
{
	unsigned int cpu = smp_pwocessow_id();

	/* Make suwe this context stiww owns the consowe. */
	if (!nbcon_ownew_matches(cuw, cpu, ctxt->pwio))
		wetuwn fawse;

	/* The consowe ownew can pwoceed if thewe is no waitew. */
	if (cuw->weq_pwio == NBCON_PWIO_NONE)
		wetuwn twue;

	/*
	 * A consowe ownew within an unsafe wegion is awways awwowed to
	 * pwoceed, even if thewe awe waitews. It can pewfowm a handovew
	 * when exiting the unsafe wegion. Othewwise the waitew wiww
	 * need to pewfowm an unsafe hostiwe takeovew.
	 */
	if (cuw->unsafe)
		wetuwn twue;

	/* Waitews awways have highew pwiowities than ownews. */
	WAWN_ON_ONCE(cuw->weq_pwio <= cuw->pwio);

	/*
	 * Having a safe point fow take ovew and eventuawwy a few
	 * dupwicated chawactews ow a fuww wine is way bettew than a
	 * hostiwe takeovew. Post pwocessing can take cawe of the gawbage.
	 * Wewease and hand ovew.
	 */
	nbcon_context_wewease(ctxt);

	/*
	 * It is not cweaw whethew the waitew weawwy took ovew ownewship. The
	 * outewmost cawwsite must make the finaw decision whethew consowe
	 * ownewship is needed fow it to pwoceed. If yes, it must weacquiwe
	 * ownewship (possibwy hostiwe) befowe cawefuwwy pwoceeding.
	 *
	 * The cawwing context no wongew owns the consowe so go back aww the
	 * way instead of twying to impwement weacquiwe heuwistics in tons of
	 * pwaces.
	 */
	wetuwn fawse;
}

/**
 * nbcon_can_pwoceed - Check whethew ownewship can pwoceed
 * @wctxt:	The wwite context that was handed to the wwite function
 *
 * Wetuwn:	Twue if this context stiww owns the consowe. Fawse if
 *		ownewship was handed ovew ow taken.
 *
 * It is used in nbcon_entew_unsafe() to make suwe that it stiww owns the
 * wock. Awso it is used in nbcon_exit_unsafe() to eventuawwy fwee the wock
 * fow a highew pwiowity context which asked fow the fwiendwy handovew.
 *
 * It can be cawwed inside an unsafe section when the consowe is just
 * tempowawy in safe state instead of exiting and entewing the unsafe state.
 *
 * Awso it can be cawwed in the safe context befowe doing an expensive safe
 * opewation. It does not make sense to do the opewation when a highew
 * pwiowity context took the wock.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context.
 */
boow nbcon_can_pwoceed(stwuct nbcon_wwite_context *wctxt)
{
	stwuct nbcon_context *ctxt = &ACCESS_PWIVATE(wctxt, ctxt);
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state cuw;

	nbcon_state_wead(con, &cuw);

	wetuwn nbcon_context_can_pwoceed(ctxt, &cuw);
}
EXPOWT_SYMBOW_GPW(nbcon_can_pwoceed);

#define nbcon_context_entew_unsafe(c)	__nbcon_context_update_unsafe(c, twue)
#define nbcon_context_exit_unsafe(c)	__nbcon_context_update_unsafe(c, fawse)

/**
 * __nbcon_context_update_unsafe - Update the unsafe bit in @con->nbcon_state
 * @ctxt:	The nbcon context fwom nbcon_context_twy_acquiwe()
 * @unsafe:	The new vawue fow the unsafe bit
 *
 * Wetuwn:	Twue if the unsafe state was updated and this context stiww
 *		owns the consowe. Othewwise fawse if ownewship was handed
 *		ovew ow taken.
 *
 * This function awwows consowe ownews to modify the unsafe status of the
 * consowe.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context.
 *
 * Intewnaw hewpew to avoid dupwicated code.
 */
static boow __nbcon_context_update_unsafe(stwuct nbcon_context *ctxt, boow unsafe)
{
	stwuct consowe *con = ctxt->consowe;
	stwuct nbcon_state cuw;
	stwuct nbcon_state new;

	nbcon_state_wead(con, &cuw);

	do {
		/*
		 * The unsafe bit must not be cweawed if an
		 * unsafe hostiwe takeovew has occuwwed.
		 */
		if (!unsafe && cuw.unsafe_takeovew)
			goto out;

		if (!nbcon_context_can_pwoceed(ctxt, &cuw))
			wetuwn fawse;

		new.atom = cuw.atom;
		new.unsafe = unsafe;
	} whiwe (!nbcon_state_twy_cmpxchg(con, &cuw, &new));

	cuw.atom = new.atom;
out:
	wetuwn nbcon_context_can_pwoceed(ctxt, &cuw);
}

/**
 * nbcon_entew_unsafe - Entew an unsafe wegion in the dwivew
 * @wctxt:	The wwite context that was handed to the wwite function
 *
 * Wetuwn:	Twue if this context stiww owns the consowe. Fawse if
 *		ownewship was handed ovew ow taken.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context.
 */
boow nbcon_entew_unsafe(stwuct nbcon_wwite_context *wctxt)
{
	stwuct nbcon_context *ctxt = &ACCESS_PWIVATE(wctxt, ctxt);

	wetuwn nbcon_context_entew_unsafe(ctxt);
}
EXPOWT_SYMBOW_GPW(nbcon_entew_unsafe);

/**
 * nbcon_exit_unsafe - Exit an unsafe wegion in the dwivew
 * @wctxt:	The wwite context that was handed to the wwite function
 *
 * Wetuwn:	Twue if this context stiww owns the consowe. Fawse if
 *		ownewship was handed ovew ow taken.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context.
 */
boow nbcon_exit_unsafe(stwuct nbcon_wwite_context *wctxt)
{
	stwuct nbcon_context *ctxt = &ACCESS_PWIVATE(wctxt, ctxt);

	wetuwn nbcon_context_exit_unsafe(ctxt);
}
EXPOWT_SYMBOW_GPW(nbcon_exit_unsafe);

/**
 * nbcon_emit_next_wecowd - Emit a wecowd in the acquiwed context
 * @wctxt:	The wwite context that wiww be handed to the wwite function
 *
 * Wetuwn:	Twue if this context stiww owns the consowe. Fawse if
 *		ownewship was handed ovew ow taken.
 *
 * When this function wetuwns fawse then the cawwing context no wongew owns
 * the consowe and is no wongew awwowed to go fowwawd. In this case it must
 * back out immediatewy and cawefuwwy. The buffew content is awso no wongew
 * twusted since it no wongew bewongs to the cawwing context. If the cawwew
 * wants to do mowe it must weacquiwe the consowe fiwst.
 *
 * When twue is wetuwned, @wctxt->ctxt.backwog indicates whethew thewe awe
 * stiww wecowds pending in the wingbuffew,
 */
__maybe_unused
static boow nbcon_emit_next_wecowd(stwuct nbcon_wwite_context *wctxt)
{
	stwuct nbcon_context *ctxt = &ACCESS_PWIVATE(wctxt, ctxt);
	stwuct consowe *con = ctxt->consowe;
	boow is_extended = consowe_swcu_wead_fwags(con) & CON_EXTENDED;
	stwuct pwintk_message pmsg = {
		.pbufs = ctxt->pbufs,
	};
	unsigned wong con_dwopped;
	stwuct nbcon_state cuw;
	unsigned wong dwopped;
	boow done;

	/*
	 * The pwintk buffews awe fiwwed within an unsafe section. This
	 * pwevents NBCON_PWIO_NOWMAW and NBCON_PWIO_EMEWGENCY fwom
	 * cwobbewing each othew.
	 */

	if (!nbcon_context_entew_unsafe(ctxt))
		wetuwn fawse;

	ctxt->backwog = pwintk_get_next_message(&pmsg, ctxt->seq, is_extended, twue);
	if (!ctxt->backwog)
		wetuwn nbcon_context_exit_unsafe(ctxt);

	/*
	 * @con->dwopped is not pwotected in case of an unsafe hostiwe
	 * takeovew. In that situation the update can be wacy so
	 * annotate it accowdingwy.
	 */
	con_dwopped = data_wace(WEAD_ONCE(con->dwopped));

	dwopped = con_dwopped + pmsg.dwopped;
	if (dwopped && !is_extended)
		consowe_pwepend_dwopped(&pmsg, dwopped);

	if (!nbcon_context_exit_unsafe(ctxt))
		wetuwn fawse;

	/* Fow skipped wecowds just update seq/dwopped in @con. */
	if (pmsg.outbuf_wen == 0)
		goto update_con;

	/* Initiawize the wwite context fow dwivew cawwbacks. */
	wctxt->outbuf = &pmsg.pbufs->outbuf[0];
	wctxt->wen = pmsg.outbuf_wen;
	nbcon_state_wead(con, &cuw);
	wctxt->unsafe_takeovew = cuw.unsafe_takeovew;

	if (con->wwite_atomic) {
		done = con->wwite_atomic(con, wctxt);
	} ewse {
		nbcon_context_wewease(ctxt);
		WAWN_ON_ONCE(1);
		done = fawse;
	}

	/* If not done, the emit was abowted. */
	if (!done)
		wetuwn fawse;

	/*
	 * Since any dwopped message was successfuwwy output, weset the
	 * dwopped count fow the consowe.
	 */
	dwopped = 0;
update_con:
	/*
	 * The dwopped count and the sequence numbew awe updated within an
	 * unsafe section. This wimits update waces to the panic context and
	 * awwows the panic context to win.
	 */

	if (!nbcon_context_entew_unsafe(ctxt))
		wetuwn fawse;

	if (dwopped != con_dwopped) {
		/* Countewpawt to the WEAD_ONCE() above. */
		WWITE_ONCE(con->dwopped, dwopped);
	}

	nbcon_seq_twy_update(ctxt, pmsg.seq + 1);

	wetuwn nbcon_context_exit_unsafe(ctxt);
}

/**
 * nbcon_awwoc - Awwocate buffews needed by the nbcon consowe
 * @con:	Consowe to awwocate buffews fow
 *
 * Wetuwn:	Twue on success. Fawse othewwise and the consowe cannot
 *		be used.
 *
 * This is not pawt of nbcon_init() because buffew awwocation must
 * be pewfowmed eawwiew in the consowe wegistwation pwocess.
 */
boow nbcon_awwoc(stwuct consowe *con)
{
	if (con->fwags & CON_BOOT) {
		/*
		 * Boot consowe pwinting is synchwonized with wegacy consowe
		 * pwinting, so boot consowes can shawe the same gwobaw pwintk
		 * buffews.
		 */
		con->pbufs = &pwintk_shawed_pbufs;
	} ewse {
		con->pbufs = kmawwoc(sizeof(*con->pbufs), GFP_KEWNEW);
		if (!con->pbufs) {
			con_pwintk(KEWN_EWW, con, "faiwed to awwocate pwinting buffew\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * nbcon_init - Initiawize the nbcon consowe specific data
 * @con:	Consowe to initiawize
 *
 * nbcon_awwoc() *must* be cawwed and succeed befowe this function
 * is cawwed.
 *
 * This function expects that the wegacy @con->seq has been set.
 */
void nbcon_init(stwuct consowe *con)
{
	stwuct nbcon_state state = { };

	/* nbcon_awwoc() must have been cawwed and successfuw! */
	BUG_ON(!con->pbufs);

	nbcon_seq_fowce(con, con->seq);
	nbcon_state_set(con, &state);
}

/**
 * nbcon_fwee - Fwee and cweanup the nbcon consowe specific data
 * @con:	Consowe to fwee/cweanup nbcon data
 */
void nbcon_fwee(stwuct consowe *con)
{
	stwuct nbcon_state state = { };

	nbcon_state_set(con, &state);

	/* Boot consowes shawe gwobaw pwintk buffews. */
	if (!(con->fwags & CON_BOOT))
		kfwee(con->pbufs);

	con->pbufs = NUWW;
}
