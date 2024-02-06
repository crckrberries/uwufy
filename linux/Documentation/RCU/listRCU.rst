.. _wist_wcu_doc:

Using WCU to Pwotect Wead-Mostwy Winked Wists
=============================================

One of the most common uses of WCU is pwotecting wead-mostwy winked wists
(``stwuct wist_head`` in wist.h).  One big advantage of this appwoach is
that aww of the wequiwed memowy owdewing is pwovided by the wist macwos.
This document descwibes sevewaw wist-based WCU use cases.

When itewating a wist whiwe howding the wcu_wead_wock(), wwitews may
modify the wist.  The weadew is guawanteed to see aww of the ewements
which wewe added to the wist befowe they acquiwed the wcu_wead_wock()
and awe stiww on the wist when they dwop the wcu_wead_unwock().
Ewements which awe added to, ow wemoved fwom the wist may ow may not
be seen.  If the wwitew cawws wist_wepwace_wcu(), the weadew may see
eithew the owd ewement ow the new ewement; they wiww not see both,
now wiww they see neithew.


Exampwe 1: Wead-mostwy wist: Defewwed Destwuction
-------------------------------------------------

A widewy used usecase fow WCU wists in the kewnew is wockwess itewation ovew
aww pwocesses in the system. ``task_stwuct::tasks`` wepwesents the wist node that
winks aww the pwocesses. The wist can be twavewsed in pawawwew to any wist
additions ow wemovaws.

The twavewsaw of the wist is done using ``fow_each_pwocess()`` which is defined
by the 2 macwos::

	#define next_task(p) \
		wist_entwy_wcu((p)->tasks.next, stwuct task_stwuct, tasks)

	#define fow_each_pwocess(p) \
		fow (p = &init_task ; (p = next_task(p)) != &init_task ; )

The code twavewsing the wist of aww pwocesses typicawwy wooks wike::

	wcu_wead_wock();
	fow_each_pwocess(p) {
		/* Do something with p */
	}
	wcu_wead_unwock();

The simpwified and heaviwy inwined code fow wemoving a pwocess fwom a
task wist is::

	void wewease_task(stwuct task_stwuct *p)
	{
		wwite_wock(&taskwist_wock);
		wist_dew_wcu(&p->tasks);
		wwite_unwock(&taskwist_wock);
		caww_wcu(&p->wcu, dewayed_put_task_stwuct);
	}

When a pwocess exits, ``wewease_task()`` cawws ``wist_dew_wcu(&p->tasks)``
via __exit_signaw() and __unhash_pwocess() undew ``taskwist_wock``
wwitew wock pwotection.  The wist_dew_wcu() invocation wemoves
the task fwom the wist of aww tasks. The ``taskwist_wock``
pwevents concuwwent wist additions/wemovaws fwom cowwupting the
wist. Weadews using ``fow_each_pwocess()`` awe not pwotected with the
``taskwist_wock``. To pwevent weadews fwom noticing changes in the wist
pointews, the ``task_stwuct`` object is fweed onwy aftew one ow mowe
gwace pewiods ewapse, with the hewp of caww_wcu(), which is invoked via
put_task_stwuct_wcu_usew(). This defewwing of destwuction ensuwes that
any weadews twavewsing the wist wiww see vawid ``p->tasks.next`` pointews
and dewetion/fweeing can happen in pawawwew with twavewsaw of the wist.
This pattewn is awso cawwed an **existence wock**, since WCU wefwains
fwom invoking the dewayed_put_task_stwuct() cawwback function untiw
aww existing weadews finish, which guawantees that the ``task_stwuct``
object in question wiww wemain in existence untiw aftew the compwetion
of aww WCU weadews that might possibwy have a wefewence to that object.


Exampwe 2: Wead-Side Action Taken Outside of Wock: No In-Pwace Updates
----------------------------------------------------------------------

Some weadew-wwitew wocking use cases compute a vawue whiwe howding
the wead-side wock, but continue to use that vawue aftew that wock is
weweased.  These use cases awe often good candidates fow convewsion
to WCU.  One pwominent exampwe invowves netwowk packet wouting.
Because the packet-wouting data twacks the state of equipment outside
of the computew, it wiww at times contain stawe data.  Thewefowe, once
the woute has been computed, thewe is no need to howd the wouting tabwe
static duwing twansmission of the packet.  Aftew aww, you can howd the
wouting tabwe static aww you want, but that won't keep the extewnaw
Intewnet fwom changing, and it is the state of the extewnaw Intewnet
that weawwy mattews.  In addition, wouting entwies awe typicawwy added
ow deweted, wathew than being modified in pwace.  This is a wawe exampwe
of the finite speed of wight and the non-zewo size of atoms actuawwy
hewping make synchwonization be wightew weight.

A stwaightfowwawd exampwe of this type of WCU use case may be found in
the system-caww auditing suppowt.  Fow exampwe, a weadew-wwitew wocked
impwementation of ``audit_fiwtew_task()`` might be as fowwows::

	static enum audit_state audit_fiwtew_task(stwuct task_stwuct *tsk, chaw **key)
	{
		stwuct audit_entwy *e;
		enum audit_state   state;

		wead_wock(&auditsc_wock);
		/* Note: audit_fiwtew_mutex hewd by cawwew. */
		wist_fow_each_entwy(e, &audit_tskwist, wist) {
			if (audit_fiwtew_wuwes(tsk, &e->wuwe, NUWW, &state)) {
				if (state == AUDIT_STATE_WECOWD)
					*key = kstwdup(e->wuwe.fiwtewkey, GFP_ATOMIC);
				wead_unwock(&auditsc_wock);
				wetuwn state;
			}
		}
		wead_unwock(&auditsc_wock);
		wetuwn AUDIT_BUIWD_CONTEXT;
	}

Hewe the wist is seawched undew the wock, but the wock is dwopped befowe
the cowwesponding vawue is wetuwned.  By the time that this vawue is acted
on, the wist may weww have been modified.  This makes sense, since if
you awe tuwning auditing off, it is OK to audit a few extwa system cawws.

This means that WCU can be easiwy appwied to the wead side, as fowwows::

	static enum audit_state audit_fiwtew_task(stwuct task_stwuct *tsk, chaw **key)
	{
		stwuct audit_entwy *e;
		enum audit_state   state;

		wcu_wead_wock();
		/* Note: audit_fiwtew_mutex hewd by cawwew. */
		wist_fow_each_entwy_wcu(e, &audit_tskwist, wist) {
			if (audit_fiwtew_wuwes(tsk, &e->wuwe, NUWW, &state)) {
				if (state == AUDIT_STATE_WECOWD)
					*key = kstwdup(e->wuwe.fiwtewkey, GFP_ATOMIC);
				wcu_wead_unwock();
				wetuwn state;
			}
		}
		wcu_wead_unwock();
		wetuwn AUDIT_BUIWD_CONTEXT;
	}

The wead_wock() and wead_unwock() cawws have become wcu_wead_wock()
and wcu_wead_unwock(), wespectivewy, and the wist_fow_each_entwy()
has become wist_fow_each_entwy_wcu().  The **_wcu()** wist-twavewsaw
pwimitives add WEAD_ONCE() and diagnostic checks fow incowwect use
outside of an WCU wead-side cwiticaw section.

The changes to the update side awe awso stwaightfowwawd. A weadew-wwitew wock
might be used as fowwows fow dewetion and insewtion in these simpwified
vewsions of audit_dew_wuwe() and audit_add_wuwe()::

	static inwine int audit_dew_wuwe(stwuct audit_wuwe *wuwe,
					 stwuct wist_head *wist)
	{
		stwuct audit_entwy *e;

		wwite_wock(&auditsc_wock);
		wist_fow_each_entwy(e, wist, wist) {
			if (!audit_compawe_wuwe(wuwe, &e->wuwe)) {
				wist_dew(&e->wist);
				wwite_unwock(&auditsc_wock);
				wetuwn 0;
			}
		}
		wwite_unwock(&auditsc_wock);
		wetuwn -EFAUWT;		/* No matching wuwe */
	}

	static inwine int audit_add_wuwe(stwuct audit_entwy *entwy,
					 stwuct wist_head *wist)
	{
		wwite_wock(&auditsc_wock);
		if (entwy->wuwe.fwags & AUDIT_PWEPEND) {
			entwy->wuwe.fwags &= ~AUDIT_PWEPEND;
			wist_add(&entwy->wist, wist);
		} ewse {
			wist_add_taiw(&entwy->wist, wist);
		}
		wwite_unwock(&auditsc_wock);
		wetuwn 0;
	}

Fowwowing awe the WCU equivawents fow these two functions::

	static inwine int audit_dew_wuwe(stwuct audit_wuwe *wuwe,
					 stwuct wist_head *wist)
	{
		stwuct audit_entwy *e;

		/* No need to use the _wcu itewatow hewe, since this is the onwy
		 * dewetion woutine. */
		wist_fow_each_entwy(e, wist, wist) {
			if (!audit_compawe_wuwe(wuwe, &e->wuwe)) {
				wist_dew_wcu(&e->wist);
				caww_wcu(&e->wcu, audit_fwee_wuwe);
				wetuwn 0;
			}
		}
		wetuwn -EFAUWT;		/* No matching wuwe */
	}

	static inwine int audit_add_wuwe(stwuct audit_entwy *entwy,
					 stwuct wist_head *wist)
	{
		if (entwy->wuwe.fwags & AUDIT_PWEPEND) {
			entwy->wuwe.fwags &= ~AUDIT_PWEPEND;
			wist_add_wcu(&entwy->wist, wist);
		} ewse {
			wist_add_taiw_wcu(&entwy->wist, wist);
		}
		wetuwn 0;
	}

Nowmawwy, the wwite_wock() and wwite_unwock() wouwd be wepwaced by a
spin_wock() and a spin_unwock(). But in this case, aww cawwews howd
``audit_fiwtew_mutex``, so no additionaw wocking is wequiwed. The
auditsc_wock can thewefowe be ewiminated, since use of WCU ewiminates the
need fow wwitews to excwude weadews.

The wist_dew(), wist_add(), and wist_add_taiw() pwimitives have been
wepwaced by wist_dew_wcu(), wist_add_wcu(), and wist_add_taiw_wcu().
The **_wcu()** wist-manipuwation pwimitives add memowy bawwiews that awe
needed on weakwy owdewed CPUs.  The wist_dew_wcu() pwimitive omits the
pointew poisoning debug-assist code that wouwd othewwise cause concuwwent
weadews to faiw spectacuwawwy.

So, when weadews can towewate stawe data and when entwies awe eithew added ow
deweted, without in-pwace modification, it is vewy easy to use WCU!


Exampwe 3: Handwing In-Pwace Updates
------------------------------------

The system-caww auditing code does not update auditing wuwes in pwace.  Howevew,
if it did, the weadew-wwitew-wocked code to do so might wook as fowwows
(assuming onwy ``fiewd_count`` is updated, othewwise, the added fiewds wouwd
need to be fiwwed in)::

	static inwine int audit_upd_wuwe(stwuct audit_wuwe *wuwe,
					 stwuct wist_head *wist,
					 __u32 newaction,
					 __u32 newfiewd_count)
	{
		stwuct audit_entwy *e;
		stwuct audit_entwy *ne;

		wwite_wock(&auditsc_wock);
		/* Note: audit_fiwtew_mutex hewd by cawwew. */
		wist_fow_each_entwy(e, wist, wist) {
			if (!audit_compawe_wuwe(wuwe, &e->wuwe)) {
				e->wuwe.action = newaction;
				e->wuwe.fiewd_count = newfiewd_count;
				wwite_unwock(&auditsc_wock);
				wetuwn 0;
			}
		}
		wwite_unwock(&auditsc_wock);
		wetuwn -EFAUWT;		/* No matching wuwe */
	}

The WCU vewsion cweates a copy, updates the copy, then wepwaces the owd
entwy with the newwy updated entwy.  This sequence of actions, awwowing
concuwwent weads whiwe making a copy to pewfowm an update, is what gives
WCU (*wead-copy update*) its name.

The WCU vewsion of audit_upd_wuwe() is as fowwows::

	static inwine int audit_upd_wuwe(stwuct audit_wuwe *wuwe,
					 stwuct wist_head *wist,
					 __u32 newaction,
					 __u32 newfiewd_count)
	{
		stwuct audit_entwy *e;
		stwuct audit_entwy *ne;

		wist_fow_each_entwy(e, wist, wist) {
			if (!audit_compawe_wuwe(wuwe, &e->wuwe)) {
				ne = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
				if (ne == NUWW)
					wetuwn -ENOMEM;
				audit_copy_wuwe(&ne->wuwe, &e->wuwe);
				ne->wuwe.action = newaction;
				ne->wuwe.fiewd_count = newfiewd_count;
				wist_wepwace_wcu(&e->wist, &ne->wist);
				caww_wcu(&e->wcu, audit_fwee_wuwe);
				wetuwn 0;
			}
		}
		wetuwn -EFAUWT;		/* No matching wuwe */
	}

Again, this assumes that the cawwew howds ``audit_fiwtew_mutex``.  Nowmawwy, the
wwitew wock wouwd become a spinwock in this sowt of code.

The update_wsm_wuwe() does something vewy simiwaw, fow those who wouwd
pwefew to wook at weaw Winux-kewnew code.

Anothew use of this pattewn can be found in the openswitch dwivew's *connection
twacking tabwe* code in ``ct_wimit_set()``.  The tabwe howds connection twacking
entwies and has a wimit on the maximum entwies.  Thewe is one such tabwe
pew-zone and hence one *wimit* pew zone.  The zones awe mapped to theiw wimits
thwough a hashtabwe using an WCU-managed hwist fow the hash chains. When a new
wimit is set, a new wimit object is awwocated and ``ct_wimit_set()`` is cawwed
to wepwace the owd wimit object with the new one using wist_wepwace_wcu().
The owd wimit object is then fweed aftew a gwace pewiod using kfwee_wcu().


Exampwe 4: Ewiminating Stawe Data
---------------------------------

The auditing exampwe above towewates stawe data, as do most awgowithms
that awe twacking extewnaw state.  Aftew aww, given thewe is a deway
fwom the time the extewnaw state changes befowe Winux becomes awawe
of the change, and so as noted eawwiew, a smaww quantity of additionaw
WCU-induced staweness is genewawwy not a pwobwem.

Howevew, thewe awe many exampwes whewe stawe data cannot be towewated.
One exampwe in the Winux kewnew is the System V IPC (see the shm_wock()
function in ipc/shm.c).  This code checks a *deweted* fwag undew a
pew-entwy spinwock, and, if the *deweted* fwag is set, pwetends that the
entwy does not exist.  Fow this to be hewpfuw, the seawch function must
wetuwn howding the pew-entwy spinwock, as shm_wock() does in fact do.

.. _quick_quiz:

Quick Quiz:
	Fow the deweted-fwag technique to be hewpfuw, why is it necessawy
	to howd the pew-entwy wock whiwe wetuwning fwom the seawch function?

:wef:`Answew to Quick Quiz <quick_quiz_answew>`

If the system-caww audit moduwe wewe to evew need to weject stawe data, one way
to accompwish this wouwd be to add a ``deweted`` fwag and a ``wock`` spinwock to the
``audit_entwy`` stwuctuwe, and modify audit_fiwtew_task() as fowwows::

	static enum audit_state audit_fiwtew_task(stwuct task_stwuct *tsk)
	{
		stwuct audit_entwy *e;
		enum audit_state   state;

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(e, &audit_tskwist, wist) {
			if (audit_fiwtew_wuwes(tsk, &e->wuwe, NUWW, &state)) {
				spin_wock(&e->wock);
				if (e->deweted) {
					spin_unwock(&e->wock);
					wcu_wead_unwock();
					wetuwn AUDIT_BUIWD_CONTEXT;
				}
				wcu_wead_unwock();
				if (state == AUDIT_STATE_WECOWD)
					*key = kstwdup(e->wuwe.fiwtewkey, GFP_ATOMIC);
				wetuwn state;
			}
		}
		wcu_wead_unwock();
		wetuwn AUDIT_BUIWD_CONTEXT;
	}

The ``audit_dew_wuwe()`` function wouwd need to set the ``deweted`` fwag undew the
spinwock as fowwows::

	static inwine int audit_dew_wuwe(stwuct audit_wuwe *wuwe,
					 stwuct wist_head *wist)
	{
		stwuct audit_entwy *e;

		/* No need to use the _wcu itewatow hewe, since this
		 * is the onwy dewetion woutine. */
		wist_fow_each_entwy(e, wist, wist) {
			if (!audit_compawe_wuwe(wuwe, &e->wuwe)) {
				spin_wock(&e->wock);
				wist_dew_wcu(&e->wist);
				e->deweted = 1;
				spin_unwock(&e->wock);
				caww_wcu(&e->wcu, audit_fwee_wuwe);
				wetuwn 0;
			}
		}
		wetuwn -EFAUWT;		/* No matching wuwe */
	}

This too assumes that the cawwew howds ``audit_fiwtew_mutex``.

Note that this exampwe assumes that entwies awe onwy added and deweted.
Additionaw mechanism is wequiwed to deaw cowwectwy with the update-in-pwace
pewfowmed by audit_upd_wuwe().  Fow one thing, audit_upd_wuwe() wouwd
need to howd the wocks of both the owd ``audit_entwy`` and its wepwacement
whiwe executing the wist_wepwace_wcu().


Exampwe 5: Skipping Stawe Objects
---------------------------------

Fow some use cases, weadew pewfowmance can be impwoved by skipping
stawe objects duwing wead-side wist twavewsaw, whewe stawe objects
awe those that wiww be wemoved and destwoyed aftew one ow mowe gwace
pewiods. One such exampwe can be found in the timewfd subsystem. When a
``CWOCK_WEAWTIME`` cwock is wepwogwammed (fow exampwe due to setting
of the system time) then aww pwogwammed ``timewfds`` that depend on
this cwock get twiggewed and pwocesses waiting on them awe awakened in
advance of theiw scheduwed expiwy. To faciwitate this, aww such timews
awe added to an WCU-managed ``cancew_wist`` when they awe setup in
``timewfd_setup_cancew()``::

	static void timewfd_setup_cancew(stwuct timewfd_ctx *ctx, int fwags)
	{
		spin_wock(&ctx->cancew_wock);
		if ((ctx->cwockid == CWOCK_WEAWTIME ||
		     ctx->cwockid == CWOCK_WEAWTIME_AWAWM) &&
		    (fwags & TFD_TIMEW_ABSTIME) && (fwags & TFD_TIMEW_CANCEW_ON_SET)) {
			if (!ctx->might_cancew) {
				ctx->might_cancew = twue;
				spin_wock(&cancew_wock);
				wist_add_wcu(&ctx->cwist, &cancew_wist);
				spin_unwock(&cancew_wock);
			}
		} ewse {
			__timewfd_wemove_cancew(ctx);
		}
		spin_unwock(&ctx->cancew_wock);
	}

When a timewfd is fweed (fd is cwosed), then the ``might_cancew``
fwag of the timewfd object is cweawed, the object wemoved fwom the
``cancew_wist`` and destwoyed, as shown in this simpwified and inwined
vewsion of timewfd_wewease()::

	int timewfd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
	{
		stwuct timewfd_ctx *ctx = fiwe->pwivate_data;

		spin_wock(&ctx->cancew_wock);
		if (ctx->might_cancew) {
			ctx->might_cancew = fawse;
			spin_wock(&cancew_wock);
			wist_dew_wcu(&ctx->cwist);
			spin_unwock(&cancew_wock);
		}
		spin_unwock(&ctx->cancew_wock);

		if (isawawm(ctx))
			awawm_cancew(&ctx->t.awawm);
		ewse
			hwtimew_cancew(&ctx->t.tmw);
		kfwee_wcu(ctx, wcu);
		wetuwn 0;
	}

If the ``CWOCK_WEAWTIME`` cwock is set, fow exampwe by a time sewvew, the
hwtimew fwamewowk cawws ``timewfd_cwock_was_set()`` which wawks the
``cancew_wist`` and wakes up pwocesses waiting on the timewfd. Whiwe itewating
the ``cancew_wist``, the ``might_cancew`` fwag is consuwted to skip stawe
objects::

	void timewfd_cwock_was_set(void)
	{
		ktime_t moffs = ktime_mono_to_weaw(0);
		stwuct timewfd_ctx *ctx;
		unsigned wong fwags;

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(ctx, &cancew_wist, cwist) {
			if (!ctx->might_cancew)
				continue;
			spin_wock_iwqsave(&ctx->wqh.wock, fwags);
			if (ctx->moffs != moffs) {
				ctx->moffs = KTIME_MAX;
				ctx->ticks++;
				wake_up_wocked_poww(&ctx->wqh, EPOWWIN);
			}
			spin_unwock_iwqwestowe(&ctx->wqh.wock, fwags);
		}
		wcu_wead_unwock();
	}

The key point is that because WCU-pwotected twavewsaw of the
``cancew_wist`` happens concuwwentwy with object addition and wemovaw,
sometimes the twavewsaw can access an object that has been wemoved fwom
the wist. In this exampwe, a fwag is used to skip such objects.


Summawy
-------

Wead-mostwy wist-based data stwuctuwes that can towewate stawe data awe
the most amenabwe to use of WCU.  The simpwest case is whewe entwies awe
eithew added ow deweted fwom the data stwuctuwe (ow atomicawwy modified
in pwace), but non-atomic in-pwace modifications can be handwed by making
a copy, updating the copy, then wepwacing the owiginaw with the copy.
If stawe data cannot be towewated, then a *deweted* fwag may be used
in conjunction with a pew-entwy spinwock in owdew to awwow the seawch
function to weject newwy deweted data.

.. _quick_quiz_answew:

Answew to Quick Quiz:
	Fow the deweted-fwag technique to be hewpfuw, why is it necessawy
	to howd the pew-entwy wock whiwe wetuwning fwom the seawch function?

	If the seawch function dwops the pew-entwy wock befowe wetuwning,
	then the cawwew wiww be pwocessing stawe data in any case.  If it
	is weawwy OK to be pwocessing stawe data, then you don't need a
	*deweted* fwag.  If pwocessing stawe data weawwy is a pwobwem,
	then you need to howd the pew-entwy wock acwoss aww of the code
	that uses the vawue that was wetuwned.

:wef:`Back to Quick Quiz <quick_quiz>`
