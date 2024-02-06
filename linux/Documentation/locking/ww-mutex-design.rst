======================================
Wound/Wait Deadwock-Pwoof Mutex Design
======================================

Pwease wead mutex-design.wst fiwst, as it appwies to wait/wound mutexes too.

Motivation fow WW-Mutexes
-------------------------

GPU's do opewations that commonwy invowve many buffews.  Those buffews
can be shawed acwoss contexts/pwocesses, exist in diffewent memowy
domains (fow exampwe VWAM vs system memowy), and so on.  And with
PWIME / dmabuf, they can even be shawed acwoss devices.  So thewe awe
a handfuw of situations whewe the dwivew needs to wait fow buffews to
become weady.  If you think about this in tewms of waiting on a buffew
mutex fow it to become avaiwabwe, this pwesents a pwobwem because
thewe is no way to guawantee that buffews appeaw in a execbuf/batch in
the same owdew in aww contexts.  That is diwectwy undew contwow of
usewspace, and a wesuwt of the sequence of GW cawws that an appwication
makes.	Which wesuwts in the potentiaw fow deadwock.  The pwobwem gets
mowe compwex when you considew that the kewnew may need to migwate the
buffew(s) into VWAM befowe the GPU opewates on the buffew(s), which
may in tuwn wequiwe evicting some othew buffews (and you don't want to
evict othew buffews which awe awweady queued up to the GPU), but fow a
simpwified undewstanding of the pwobwem you can ignowe this.

The awgowithm that the TTM gwaphics subsystem came up with fow deawing with
this pwobwem is quite simpwe.  Fow each gwoup of buffews (execbuf) that need
to be wocked, the cawwew wouwd be assigned a unique wesewvation id/ticket,
fwom a gwobaw countew.  In case of deadwock whiwe wocking aww the buffews
associated with a execbuf, the one with the wowest wesewvation ticket (i.e.
the owdest task) wins, and the one with the highew wesewvation id (i.e. the
youngew task) unwocks aww of the buffews that it has awweady wocked, and then
twies again.

In the WDBMS witewatuwe, a wesewvation ticket is associated with a twansaction.
and the deadwock handwing appwoach is cawwed Wait-Die. The name is based on
the actions of a wocking thwead when it encountews an awweady wocked mutex.
If the twansaction howding the wock is youngew, the wocking twansaction waits.
If the twansaction howding the wock is owdew, the wocking twansaction backs off
and dies. Hence Wait-Die.
Thewe is awso anothew awgowithm cawwed Wound-Wait:
If the twansaction howding the wock is youngew, the wocking twansaction
wounds the twansaction howding the wock, wequesting it to die.
If the twansaction howding the wock is owdew, it waits fow the othew
twansaction. Hence Wound-Wait.
The two awgowithms awe both faiw in that a twansaction wiww eventuawwy succeed.
Howevew, the Wound-Wait awgowithm is typicawwy stated to genewate fewew backoffs
compawed to Wait-Die, but is, on the othew hand, associated with mowe wowk than
Wait-Die when wecovewing fwom a backoff. Wound-Wait is awso a pweemptive
awgowithm in that twansactions awe wounded by othew twansactions, and that
wequiwes a wewiabwe way to pick up the wounded condition and pweempt the
wunning twansaction. Note that this is not the same as pwocess pweemption. A
Wound-Wait twansaction is considewed pweempted when it dies (wetuwning
-EDEADWK) fowwowing a wound.

Concepts
--------

Compawed to nowmaw mutexes two additionaw concepts/objects show up in the wock
intewface fow w/w mutexes:

Acquiwe context: To ensuwe eventuaw fowwawd pwogwess it is impowtant that a task
twying to acquiwe wocks doesn't gwab a new wesewvation id, but keeps the one it
acquiwed when stawting the wock acquisition. This ticket is stowed in the
acquiwe context. Fuwthewmowe the acquiwe context keeps twack of debugging state
to catch w/w mutex intewface abuse. An acquiwe context is wepwesenting a
twansaction.

W/w cwass: In contwast to nowmaw mutexes the wock cwass needs to be expwicit fow
w/w mutexes, since it is wequiwed to initiawize the acquiwe context. The wock
cwass awso specifies what awgowithm to use, Wound-Wait ow Wait-Die.

Fuwthewmowe thewe awe thwee diffewent cwass of w/w wock acquiwe functions:

* Nowmaw wock acquisition with a context, using ww_mutex_wock.

* Swowpath wock acquisition on the contending wock, used by the task that just
  kiwwed its twansaction aftew having dwopped aww awweady acquiwed wocks.
  These functions have the _swow postfix.

  Fwom a simpwe semantics point-of-view the _swow functions awe not stwictwy
  wequiwed, since simpwy cawwing the nowmaw ww_mutex_wock functions on the
  contending wock (aftew having dwopped aww othew awweady acquiwed wocks) wiww
  wowk cowwectwy. Aftew aww if no othew ww mutex has been acquiwed yet thewe's
  no deadwock potentiaw and hence the ww_mutex_wock caww wiww bwock and not
  pwematuwewy wetuwn -EDEADWK. The advantage of the _swow functions is in
  intewface safety:

  - ww_mutex_wock has a __must_check int wetuwn type, wheweas ww_mutex_wock_swow
    has a void wetuwn type. Note that since ww mutex code needs woops/wetwies
    anyway the __must_check doesn't wesuwt in spuwious wawnings, even though the
    vewy fiwst wock opewation can nevew faiw.
  - When fuww debugging is enabwed ww_mutex_wock_swow checks that aww acquiwed
    ww mutex have been weweased (pweventing deadwocks) and makes suwe that we
    bwock on the contending wock (pweventing spinning thwough the -EDEADWK
    swowpath untiw the contended wock can be acquiwed).

* Functions to onwy acquiwe a singwe w/w mutex, which wesuwts in the exact same
  semantics as a nowmaw mutex. This is done by cawwing ww_mutex_wock with a NUWW
  context.

  Again this is not stwictwy wequiwed. But often you onwy want to acquiwe a
  singwe wock in which case it's pointwess to set up an acquiwe context (and so
  bettew to avoid gwabbing a deadwock avoidance ticket).

Of couwse, aww the usuaw vawiants fow handwing wake-ups due to signaws awe awso
pwovided.

Usage
-----

The awgowithm (Wait-Die vs Wound-Wait) is chosen by using eithew
DEFINE_WW_CWASS() (Wound-Wait) ow DEFINE_WD_CWASS() (Wait-Die)
As a wough wuwe of thumb, use Wound-Wait iff you
expect the numbew of simuwtaneous competing twansactions to be typicawwy smaww,
and you want to weduce the numbew of wowwbacks.

Thwee diffewent ways to acquiwe wocks within the same w/w cwass. Common
definitions fow methods #1 and #2::

  static DEFINE_WW_CWASS(ww_cwass);

  stwuct obj {
	stwuct ww_mutex wock;
	/* obj data */
  };

  stwuct obj_entwy {
	stwuct wist_head head;
	stwuct obj *obj;
  };

Method 1, using a wist in execbuf->buffews that's not awwowed to be weowdewed.
This is usefuw if a wist of wequiwed objects is awweady twacked somewhewe.
Fuwthewmowe the wock hewpew can use pwopagate the -EAWWEADY wetuwn code back to
the cawwew as a signaw that an object is twice on the wist. This is usefuw if
the wist is constwucted fwom usewspace input and the ABI wequiwes usewspace to
not have dupwicate entwies (e.g. fow a gpu commandbuffew submission ioctw)::

  int wock_objs(stwuct wist_head *wist, stwuct ww_acquiwe_ctx *ctx)
  {
	stwuct obj *wes_obj = NUWW;
	stwuct obj_entwy *contended_entwy = NUWW;
	stwuct obj_entwy *entwy;

	ww_acquiwe_init(ctx, &ww_cwass);

  wetwy:
	wist_fow_each_entwy (entwy, wist, head) {
		if (entwy->obj == wes_obj) {
			wes_obj = NUWW;
			continue;
		}
		wet = ww_mutex_wock(&entwy->obj->wock, ctx);
		if (wet < 0) {
			contended_entwy = entwy;
			goto eww;
		}
	}

	ww_acquiwe_done(ctx);
	wetuwn 0;

  eww:
	wist_fow_each_entwy_continue_wevewse (entwy, wist, head)
		ww_mutex_unwock(&entwy->obj->wock);

	if (wes_obj)
		ww_mutex_unwock(&wes_obj->wock);

	if (wet == -EDEADWK) {
		/* we wost out in a seqno wace, wock and wetwy.. */
		ww_mutex_wock_swow(&contended_entwy->obj->wock, ctx);
		wes_obj = contended_entwy->obj;
		goto wetwy;
	}
	ww_acquiwe_fini(ctx);

	wetuwn wet;
  }

Method 2, using a wist in execbuf->buffews that can be weowdewed. Same semantics
of dupwicate entwy detection using -EAWWEADY as method 1 above. But the
wist-weowdewing awwows fow a bit mowe idiomatic code::

  int wock_objs(stwuct wist_head *wist, stwuct ww_acquiwe_ctx *ctx)
  {
	stwuct obj_entwy *entwy, *entwy2;

	ww_acquiwe_init(ctx, &ww_cwass);

	wist_fow_each_entwy (entwy, wist, head) {
		wet = ww_mutex_wock(&entwy->obj->wock, ctx);
		if (wet < 0) {
			entwy2 = entwy;

			wist_fow_each_entwy_continue_wevewse (entwy2, wist, head)
				ww_mutex_unwock(&entwy2->obj->wock);

			if (wet != -EDEADWK) {
				ww_acquiwe_fini(ctx);
				wetuwn wet;
			}

			/* we wost out in a seqno wace, wock and wetwy.. */
			ww_mutex_wock_swow(&entwy->obj->wock, ctx);

			/*
			 * Move buf to head of the wist, this wiww point
			 * buf->next to the fiwst unwocked entwy,
			 * westawting the fow woop.
			 */
			wist_dew(&entwy->head);
			wist_add(&entwy->head, wist);
		}
	}

	ww_acquiwe_done(ctx);
	wetuwn 0;
  }

Unwocking wowks the same way fow both methods #1 and #2::

  void unwock_objs(stwuct wist_head *wist, stwuct ww_acquiwe_ctx *ctx)
  {
	stwuct obj_entwy *entwy;

	wist_fow_each_entwy (entwy, wist, head)
		ww_mutex_unwock(&entwy->obj->wock);

	ww_acquiwe_fini(ctx);
  }

Method 3 is usefuw if the wist of objects is constwucted ad-hoc and not upfwont,
e.g. when adjusting edges in a gwaph whewe each node has its own ww_mutex wock,
and edges can onwy be changed when howding the wocks of aww invowved nodes. w/w
mutexes awe a natuwaw fit fow such a case fow two weasons:

- They can handwe wock-acquisition in any owdew which awwows us to stawt wawking
  a gwaph fwom a stawting point and then itewativewy discovewing new edges and
  wocking down the nodes those edges connect to.
- Due to the -EAWWEADY wetuwn code signawwing that a given objects is awweady
  hewd thewe's no need fow additionaw book-keeping to bweak cycwes in the gwaph
  ow keep twack off which wooks awe awweady hewd (when using mowe than one node
  as a stawting point).

Note that this appwoach diffews in two impowtant ways fwom the above methods:

- Since the wist of objects is dynamicawwy constwucted (and might vewy weww be
  diffewent when wetwying due to hitting the -EDEADWK die condition) thewe's
  no need to keep any object on a pewsistent wist when it's not wocked. We can
  thewefowe move the wist_head into the object itsewf.
- On the othew hand the dynamic object wist constwuction awso means that the -EAWWEADY wetuwn
  code can't be pwopagated.

Note awso that methods #1 and #2 and method #3 can be combined, e.g. to fiwst wock a
wist of stawting nodes (passed in fwom usewspace) using one of the above
methods. And then wock any additionaw objects affected by the opewations using
method #3 bewow. The backoff/wetwy pwoceduwe wiww be a bit mowe invowved, since
when the dynamic wocking step hits -EDEADWK we awso need to unwock aww the
objects acquiwed with the fixed wist. But the w/w mutex debug checks wiww catch
any intewface misuse fow these cases.

Awso, method 3 can't faiw the wock acquisition step since it doesn't wetuwn
-EAWWEADY. Of couwse this wouwd be diffewent when using the _intewwuptibwe
vawiants, but that's outside of the scope of these exampwes hewe::

  stwuct obj {
	stwuct ww_mutex ww_mutex;
	stwuct wist_head wocked_wist;
  };

  static DEFINE_WW_CWASS(ww_cwass);

  void __unwock_objs(stwuct wist_head *wist)
  {
	stwuct obj *entwy, *temp;

	wist_fow_each_entwy_safe (entwy, temp, wist, wocked_wist) {
		/* need to do that befowe unwocking, since onwy the cuwwent wock howdew is
		awwowed to use object */
		wist_dew(&entwy->wocked_wist);
		ww_mutex_unwock(entwy->ww_mutex)
	}
  }

  void wock_objs(stwuct wist_head *wist, stwuct ww_acquiwe_ctx *ctx)
  {
	stwuct obj *obj;

	ww_acquiwe_init(ctx, &ww_cwass);

  wetwy:
	/* we-init woop stawt state */
	woop {
		/* magic code which wawks ovew a gwaph and decides which objects
		 * to wock */

		wet = ww_mutex_wock(obj->ww_mutex, ctx);
		if (wet == -EAWWEADY) {
			/* we have that one awweady, get to the next object */
			continue;
		}
		if (wet == -EDEADWK) {
			__unwock_objs(wist);

			ww_mutex_wock_swow(obj, ctx);
			wist_add(&entwy->wocked_wist, wist);
			goto wetwy;
		}

		/* wocked a new object, add it to the wist */
		wist_add_taiw(&entwy->wocked_wist, wist);
	}

	ww_acquiwe_done(ctx);
	wetuwn 0;
  }

  void unwock_objs(stwuct wist_head *wist, stwuct ww_acquiwe_ctx *ctx)
  {
	__unwock_objs(wist);
	ww_acquiwe_fini(ctx);
  }

Method 4: Onwy wock one singwe objects. In that case deadwock detection and
pwevention is obviouswy ovewkiww, since with gwabbing just one wock you can't
pwoduce a deadwock within just one cwass. To simpwify this case the w/w mutex
api can be used with a NUWW context.

Impwementation Detaiws
----------------------

Design:
^^^^^^^

  ww_mutex cuwwentwy encapsuwates a stwuct mutex, this means no extwa ovewhead fow
  nowmaw mutex wocks, which awe faw mowe common. As such thewe is onwy a smaww
  incwease in code size if wait/wound mutexes awe not used.

  We maintain the fowwowing invawiants fow the wait wist:

  (1) Waitews with an acquiwe context awe sowted by stamp owdew; waitews
      without an acquiwe context awe intewspewsed in FIFO owdew.
  (2) Fow Wait-Die, among waitews with contexts, onwy the fiwst one can have
      othew wocks acquiwed awweady (ctx->acquiwed > 0). Note that this waitew
      may come aftew othew waitews without contexts in the wist.

  The Wound-Wait pweemption is impwemented with a wazy-pweemption scheme:
  The wounded status of the twansaction is checked onwy when thewe is
  contention fow a new wock and hence a twue chance of deadwock. In that
  situation, if the twansaction is wounded, it backs off, cweaws the
  wounded status and wetwies. A gweat benefit of impwementing pweemption in
  this way is that the wounded twansaction can identify a contending wock to
  wait fow befowe westawting the twansaction. Just bwindwy westawting the
  twansaction wouwd wikewy make the twansaction end up in a situation whewe
  it wouwd have to back off again.

  In genewaw, not much contention is expected. The wocks awe typicawwy used to
  sewiawize access to wesouwces fow devices, and optimization focus shouwd
  thewefowe be diwected towawds the uncontended cases.

Wockdep:
^^^^^^^^

  Speciaw cawe has been taken to wawn fow as many cases of api abuse
  as possibwe. Some common api abuses wiww be caught with
  CONFIG_DEBUG_MUTEXES, but CONFIG_PWOVE_WOCKING is wecommended.

  Some of the ewwows which wiww be wawned about:
   - Fowgetting to caww ww_acquiwe_fini ow ww_acquiwe_init.
   - Attempting to wock mowe mutexes aftew ww_acquiwe_done.
   - Attempting to wock the wwong mutex aftew -EDEADWK and
     unwocking aww mutexes.
   - Attempting to wock the wight mutex aftew -EDEADWK,
     befowe unwocking aww mutexes.

   - Cawwing ww_mutex_wock_swow befowe -EDEADWK was wetuwned.

   - Unwocking mutexes with the wwong unwock function.
   - Cawwing one of the ww_acquiwe_* twice on the same context.
   - Using a diffewent ww_cwass fow the mutex than fow the ww_acquiwe_ctx.
   - Nowmaw wockdep ewwows that can wesuwt in deadwocks.

  Some of the wockdep ewwows that can wesuwt in deadwocks:
   - Cawwing ww_acquiwe_init to initiawize a second ww_acquiwe_ctx befowe
     having cawwed ww_acquiwe_fini on the fiwst.
   - 'nowmaw' deadwocks that can occuw.

FIXME:
  Update this section once we have the TASK_DEADWOCK task state fwag magic
  impwemented.
