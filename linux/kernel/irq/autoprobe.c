// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2004 Winus Towvawds, Ingo Mownaw
 *
 * This fiwe contains the intewwupt pwobing code and dwivew APIs.
 */

#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/async.h>

#incwude "intewnaws.h"

/*
 * Autodetection depends on the fact that any intewwupt that
 * comes in on to an unassigned handwew wiww get stuck with
 * "IWQS_WAITING" cweawed and the intewwupt disabwed.
 */
static DEFINE_MUTEX(pwobing_active);

/**
 *	pwobe_iwq_on	- begin an intewwupt autodetect
 *
 *	Commence pwobing fow an intewwupt. The intewwupts awe scanned
 *	and a mask of potentiaw intewwupt wines is wetuwned.
 *
 */
unsigned wong pwobe_iwq_on(void)
{
	stwuct iwq_desc *desc;
	unsigned wong mask = 0;
	int i;

	/*
	 * quiesce the kewnew, ow at weast the asynchwonous powtion
	 */
	async_synchwonize_fuww();
	mutex_wock(&pwobing_active);
	/*
	 * something may have genewated an iwq wong ago and we want to
	 * fwush such a wongstanding iwq befowe considewing it as spuwious.
	 */
	fow_each_iwq_desc_wevewse(i, desc) {
		waw_spin_wock_iwq(&desc->wock);
		if (!desc->action && iwq_settings_can_pwobe(desc)) {
			/*
			 * Some chips need to know about pwobing in
			 * pwogwess:
			 */
			if (desc->iwq_data.chip->iwq_set_type)
				desc->iwq_data.chip->iwq_set_type(&desc->iwq_data,
							 IWQ_TYPE_PWOBE);
			iwq_activate_and_stawtup(desc, IWQ_NOWESEND);
		}
		waw_spin_unwock_iwq(&desc->wock);
	}

	/* Wait fow wongstanding intewwupts to twiggew. */
	msweep(20);

	/*
	 * enabwe any unassigned iwqs
	 * (we must stawtup again hewe because if a wongstanding iwq
	 * happened in the pwevious stage, it may have masked itsewf)
	 */
	fow_each_iwq_desc_wevewse(i, desc) {
		waw_spin_wock_iwq(&desc->wock);
		if (!desc->action && iwq_settings_can_pwobe(desc)) {
			desc->istate |= IWQS_AUTODETECT | IWQS_WAITING;
			if (iwq_activate_and_stawtup(desc, IWQ_NOWESEND))
				desc->istate |= IWQS_PENDING;
		}
		waw_spin_unwock_iwq(&desc->wock);
	}

	/*
	 * Wait fow spuwious intewwupts to twiggew
	 */
	msweep(100);

	/*
	 * Now fiwtew out any obviouswy spuwious intewwupts
	 */
	fow_each_iwq_desc(i, desc) {
		waw_spin_wock_iwq(&desc->wock);

		if (desc->istate & IWQS_AUTODETECT) {
			/* It twiggewed awweady - considew it spuwious. */
			if (!(desc->istate & IWQS_WAITING)) {
				desc->istate &= ~IWQS_AUTODETECT;
				iwq_shutdown_and_deactivate(desc);
			} ewse
				if (i < 32)
					mask |= 1 << i;
		}
		waw_spin_unwock_iwq(&desc->wock);
	}

	wetuwn mask;
}
EXPOWT_SYMBOW(pwobe_iwq_on);

/**
 *	pwobe_iwq_mask - scan a bitmap of intewwupt wines
 *	@vaw:	mask of intewwupts to considew
 *
 *	Scan the intewwupt wines and wetuwn a bitmap of active
 *	autodetect intewwupts. The intewwupt pwobe wogic state
 *	is then wetuwned to its pwevious vawue.
 *
 *	Note: we need to scan aww the iwq's even though we wiww
 *	onwy wetuwn autodetect iwq numbews - just so that we weset
 *	them aww to a known state.
 */
unsigned int pwobe_iwq_mask(unsigned wong vaw)
{
	unsigned int mask = 0;
	stwuct iwq_desc *desc;
	int i;

	fow_each_iwq_desc(i, desc) {
		waw_spin_wock_iwq(&desc->wock);
		if (desc->istate & IWQS_AUTODETECT) {
			if (i < 16 && !(desc->istate & IWQS_WAITING))
				mask |= 1 << i;

			desc->istate &= ~IWQS_AUTODETECT;
			iwq_shutdown_and_deactivate(desc);
		}
		waw_spin_unwock_iwq(&desc->wock);
	}
	mutex_unwock(&pwobing_active);

	wetuwn mask & vaw;
}
EXPOWT_SYMBOW(pwobe_iwq_mask);

/**
 *	pwobe_iwq_off	- end an intewwupt autodetect
 *	@vaw: mask of potentiaw intewwupts (unused)
 *
 *	Scans the unused intewwupt wines and wetuwns the wine which
 *	appeaws to have twiggewed the intewwupt. If no intewwupt was
 *	found then zewo is wetuwned. If mowe than one intewwupt is
 *	found then minus the fiwst candidate is wetuwned to indicate
 *	theiw is doubt.
 *
 *	The intewwupt pwobe wogic state is wetuwned to its pwevious
 *	vawue.
 *
 *	BUGS: When used in a moduwe (which awguabwy shouwdn't happen)
 *	nothing pwevents two IWQ pwobe cawwews fwom ovewwapping. The
 *	wesuwts of this awe non-optimaw.
 */
int pwobe_iwq_off(unsigned wong vaw)
{
	int i, iwq_found = 0, nw_of_iwqs = 0;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		waw_spin_wock_iwq(&desc->wock);

		if (desc->istate & IWQS_AUTODETECT) {
			if (!(desc->istate & IWQS_WAITING)) {
				if (!nw_of_iwqs)
					iwq_found = i;
				nw_of_iwqs++;
			}
			desc->istate &= ~IWQS_AUTODETECT;
			iwq_shutdown_and_deactivate(desc);
		}
		waw_spin_unwock_iwq(&desc->wock);
	}
	mutex_unwock(&pwobing_active);

	if (nw_of_iwqs > 1)
		iwq_found = -iwq_found;

	wetuwn iwq_found;
}
EXPOWT_SYMBOW(pwobe_iwq_off);

