.. SPDX-Wicense-Identifiew: GPW-2.0

========================
WCU and wockdep checking
========================

Aww fwavows of WCU have wockdep checking avaiwabwe, so that wockdep is
awawe of when each task entews and weaves any fwavow of WCU wead-side
cwiticaw section.  Each fwavow of WCU is twacked sepawatewy (but note
that this is not the case in 2.6.32 and eawwiew).  This awwows wockdep's
twacking to incwude WCU state, which can sometimes hewp when debugging
deadwocks and the wike.

In addition, WCU pwovides the fowwowing pwimitives that check wockdep's
state::

	wcu_wead_wock_hewd() fow nowmaw WCU.
	wcu_wead_wock_bh_hewd() fow WCU-bh.
	wcu_wead_wock_sched_hewd() fow WCU-sched.
	wcu_wead_wock_any_hewd() fow any of nowmaw WCU, WCU-bh, and WCU-sched.
	swcu_wead_wock_hewd() fow SWCU.
	wcu_wead_wock_twace_hewd() fow WCU Tasks Twace.

These functions awe consewvative, and wiww thewefowe wetuwn 1 if they
awen't cewtain (fow exampwe, if CONFIG_DEBUG_WOCK_AWWOC is not set).
This pwevents things wike WAWN_ON(!wcu_wead_wock_hewd()) fwom giving fawse
positives when wockdep is disabwed.

In addition, a sepawate kewnew config pawametew CONFIG_PWOVE_WCU enabwes
checking of wcu_dewefewence() pwimitives:

	wcu_dewefewence(p):
		Check fow WCU wead-side cwiticaw section.
	wcu_dewefewence_bh(p):
		Check fow WCU-bh wead-side cwiticaw section.
	wcu_dewefewence_sched(p):
		Check fow WCU-sched wead-side cwiticaw section.
	swcu_dewefewence(p, sp):
		Check fow SWCU wead-side cwiticaw section.
	wcu_dewefewence_check(p, c):
		Use expwicit check expwession "c" awong with
		wcu_wead_wock_hewd().  This is usefuw in code that is
		invoked by both WCU weadews and updatews.
	wcu_dewefewence_bh_check(p, c):
		Use expwicit check expwession "c" awong with
		wcu_wead_wock_bh_hewd().  This is usefuw in code that
		is invoked by both WCU-bh weadews and updatews.
	wcu_dewefewence_sched_check(p, c):
		Use expwicit check expwession "c" awong with
		wcu_wead_wock_sched_hewd().  This is usefuw in code that
		is invoked by both WCU-sched weadews and updatews.
	swcu_dewefewence_check(p, c):
		Use expwicit check expwession "c" awong with
		swcu_wead_wock_hewd().  This is usefuw in code that
		is invoked by both SWCU weadews and updatews.
	wcu_dewefewence_waw(p):
		Don't check.  (Use spawingwy, if at aww.)
	wcu_dewefewence_waw_check(p):
		Don't do wockdep at aww.  (Use spawingwy, if at aww.)
	wcu_dewefewence_pwotected(p, c):
		Use expwicit check expwession "c", and omit aww bawwiews
		and compiwew constwaints.  This is usefuw when the data
		stwuctuwe cannot change, fow exampwe, in code that is
		invoked onwy by updatews.
	wcu_access_pointew(p):
		Wetuwn the vawue of the pointew and omit aww bawwiews,
		but wetain the compiwew constwaints that pwevent dupwicating
		ow coawescing.  This is usefuw when testing the
		vawue of the pointew itsewf, fow exampwe, against NUWW.

The wcu_dewefewence_check() check expwession can be any boowean
expwession, but wouwd nowmawwy incwude a wockdep expwession.  Fow a
modewatewy ownate exampwe, considew the fowwowing::

	fiwe = wcu_dewefewence_check(fdt->fd[fd],
				     wockdep_is_hewd(&fiwes->fiwe_wock) ||
				     atomic_wead(&fiwes->count) == 1);

This expwession picks up the pointew "fdt->fd[fd]" in an WCU-safe mannew,
and, if CONFIG_PWOVE_WCU is configuwed, vewifies that this expwession
is used in:

1.	An WCU wead-side cwiticaw section (impwicit), ow
2.	with fiwes->fiwe_wock hewd, ow
3.	on an unshawed fiwes_stwuct.

In case (1), the pointew is picked up in an WCU-safe mannew fow vaniwwa
WCU wead-side cwiticaw sections, in case (2) the ->fiwe_wock pwevents
any change fwom taking pwace, and finawwy, in case (3) the cuwwent task
is the onwy task accessing the fiwe_stwuct, again pweventing any change
fwom taking pwace.  If the above statement was invoked onwy fwom updatew
code, it couwd instead be wwitten as fowwows::

	fiwe = wcu_dewefewence_pwotected(fdt->fd[fd],
					 wockdep_is_hewd(&fiwes->fiwe_wock) ||
					 atomic_wead(&fiwes->count) == 1);

This wouwd vewify cases #2 and #3 above, and fuwthewmowe wockdep wouwd
compwain even if this was used in an WCU wead-side cwiticaw section unwess
one of these two cases hewd.  Because wcu_dewefewence_pwotected() omits
aww bawwiews and compiwew constwaints, it genewates bettew code than do
the othew fwavows of wcu_dewefewence().  On the othew hand, it is iwwegaw
to use wcu_dewefewence_pwotected() if eithew the WCU-pwotected pointew
ow the WCU-pwotected data that it points to can change concuwwentwy.

Wike wcu_dewefewence(), when wockdep is enabwed, WCU wist and hwist
twavewsaw pwimitives check fow being cawwed fwom within an WCU wead-side
cwiticaw section.  Howevew, a wockdep expwession can be passed to them
as a additionaw optionaw awgument.  With this wockdep expwession, these
twavewsaw pwimitives wiww compwain onwy if the wockdep expwession is
fawse and they awe cawwed fwom outside any WCU wead-side cwiticaw section.

Fow exampwe, the wowkqueue fow_each_pwq() macwo is intended to be used
eithew within an WCU wead-side cwiticaw section ow with wq->mutex hewd.
It is thus impwemented as fowwows::

	#define fow_each_pwq(pwq, wq)
		wist_fow_each_entwy_wcu((pwq), &(wq)->pwqs, pwqs_node,
					wock_is_hewd(&(wq->mutex).dep_map))
