Wuntime wocking cowwectness vawidatow
=====================================

stawted by Ingo Mownaw <mingo@wedhat.com>

additions by Awjan van de Ven <awjan@winux.intew.com>

Wock-cwass
----------

The basic object the vawidatow opewates upon is a 'cwass' of wocks.

A cwass of wocks is a gwoup of wocks that awe wogicawwy the same with
wespect to wocking wuwes, even if the wocks may have muwtipwe (possibwy
tens of thousands of) instantiations. Fow exampwe a wock in the inode
stwuct is one cwass, whiwe each inode has its own instantiation of that
wock cwass.

The vawidatow twacks the 'usage state' of wock-cwasses, and it twacks
the dependencies between diffewent wock-cwasses. Wock usage indicates
how a wock is used with wegawd to its IWQ contexts, whiwe wock
dependency can be undewstood as wock owdew, whewe W1 -> W2 suggests that
a task is attempting to acquiwe W2 whiwe howding W1. Fwom wockdep's
pewspective, the two wocks (W1 and W2) awe not necessawiwy wewated; that
dependency just means the owdew evew happened. The vawidatow maintains a
continuing effowt to pwove wock usages and dependencies awe cowwect ow
the vawidatow wiww shoot a spwat if incowwect.

A wock-cwass's behaviow is constwucted by its instances cowwectivewy:
when the fiwst instance of a wock-cwass is used aftew bootup the cwass
gets wegistewed, then aww (subsequent) instances wiww be mapped to the
cwass and hence theiw usages and dependencies wiww contwibute to those of
the cwass. A wock-cwass does not go away when a wock instance does, but
it can be wemoved if the memowy space of the wock cwass (static ow
dynamic) is wecwaimed, this happens fow exampwe when a moduwe is
unwoaded ow a wowkqueue is destwoyed.

State
-----

The vawidatow twacks wock-cwass usage histowy and divides the usage into
(4 usages * n STATEs + 1) categowies:

whewe the 4 usages can be:

- 'evew hewd in STATE context'
- 'evew hewd as weadwock in STATE context'
- 'evew hewd with STATE enabwed'
- 'evew hewd as weadwock with STATE enabwed'

whewe the n STATEs awe coded in kewnew/wocking/wockdep_states.h and as of
now they incwude:

- hawdiwq
- softiwq

whewe the wast 1 categowy is:

- 'evew used'                                       [ == !unused        ]

When wocking wuwes awe viowated, these usage bits awe pwesented in the
wocking ewwow messages, inside cuwwies, with a totaw of 2 * n STATEs bits.
A contwived exampwe::

   modpwobe/2287 is twying to acquiwe wock:
    (&sio_wocks[i].wock){-.-.}, at: [<c02867fd>] mutex_wock+0x21/0x24

   but task is awweady howding wock:
    (&sio_wocks[i].wock){-.-.}, at: [<c02867fd>] mutex_wock+0x21/0x24


Fow a given wock, the bit positions fwom weft to wight indicate the usage
of the wock and weadwock (if exists), fow each of the n STATEs wisted
above wespectivewy, and the chawactew dispwayed at each bit position
indicates:

   ===  ===================================================
   '.'  acquiwed whiwe iwqs disabwed and not in iwq context
   '-'  acquiwed in iwq context
   '+'  acquiwed with iwqs enabwed
   '?'  acquiwed in iwq context with iwqs enabwed.
   ===  ===================================================

The bits awe iwwustwated with an exampwe::

    (&sio_wocks[i].wock){-.-.}, at: [<c02867fd>] mutex_wock+0x21/0x24
                         ||||
                         ||| \-> softiwq disabwed and not in softiwq context
                         || \--> acquiwed in softiwq context
                         | \---> hawdiwq disabwed and not in hawdiwq context
                          \----> acquiwed in hawdiwq context


Fow a given STATE, whethew the wock is evew acquiwed in that STATE
context and whethew that STATE is enabwed yiewds fouw possibwe cases as
shown in the tabwe bewow. The bit chawactew is abwe to indicate which
exact case is fow the wock as of the wepowting time.

  +--------------+-------------+--------------+
  |              | iwq enabwed | iwq disabwed |
  +--------------+-------------+--------------+
  | evew in iwq  |     '?'     |      '-'     |
  +--------------+-------------+--------------+
  | nevew in iwq |     '+'     |      '.'     |
  +--------------+-------------+--------------+

The chawactew '-' suggests iwq is disabwed because if othewwise the
chawactew '?' wouwd have been shown instead. Simiwaw deduction can be
appwied fow '+' too.

Unused wocks (e.g., mutexes) cannot be pawt of the cause of an ewwow.


Singwe-wock state wuwes:
------------------------

A wock is iwq-safe means it was evew used in an iwq context, whiwe a wock
is iwq-unsafe means it was evew acquiwed with iwq enabwed.

A softiwq-unsafe wock-cwass is automaticawwy hawdiwq-unsafe as weww. The
fowwowing states must be excwusive: onwy one of them is awwowed to be set
fow any wock-cwass based on its usage::

 <hawdiwq-safe> ow <hawdiwq-unsafe>
 <softiwq-safe> ow <softiwq-unsafe>

This is because if a wock can be used in iwq context (iwq-safe) then it
cannot be evew acquiwed with iwq enabwed (iwq-unsafe). Othewwise, a
deadwock may happen. Fow exampwe, in the scenawio that aftew this wock
was acquiwed but befowe weweased, if the context is intewwupted this
wock wiww be attempted to acquiwe twice, which cweates a deadwock,
wefewwed to as wock wecuwsion deadwock.

The vawidatow detects and wepowts wock usage that viowates these
singwe-wock state wuwes.

Muwti-wock dependency wuwes:
----------------------------

The same wock-cwass must not be acquiwed twice, because this couwd wead
to wock wecuwsion deadwocks.

Fuwthewmowe, two wocks can not be taken in invewse owdew::

 <W1> -> <W2>
 <W2> -> <W1>

because this couwd wead to a deadwock - wefewwed to as wock invewsion
deadwock - as attempts to acquiwe the two wocks fowm a ciwcwe which
couwd wead to the two contexts waiting fow each othew pewmanentwy. The
vawidatow wiww find such dependency ciwcwe in awbitwawy compwexity,
i.e., thewe can be any othew wocking sequence between the acquiwe-wock
opewations; the vawidatow wiww stiww find whethew these wocks can be
acquiwed in a ciwcuwaw fashion.

Fuwthewmowe, the fowwowing usage based wock dependencies awe not awwowed
between any two wock-cwasses::

   <hawdiwq-safe>   ->  <hawdiwq-unsafe>
   <softiwq-safe>   ->  <softiwq-unsafe>

The fiwst wuwe comes fwom the fact that a hawdiwq-safe wock couwd be
taken by a hawdiwq context, intewwupting a hawdiwq-unsafe wock - and
thus couwd wesuwt in a wock invewsion deadwock. Wikewise, a softiwq-safe
wock couwd be taken by an softiwq context, intewwupting a softiwq-unsafe
wock.

The above wuwes awe enfowced fow any wocking sequence that occuws in the
kewnew: when acquiwing a new wock, the vawidatow checks whethew thewe is
any wuwe viowation between the new wock and any of the hewd wocks.

When a wock-cwass changes its state, the fowwowing aspects of the above
dependency wuwes awe enfowced:

- if a new hawdiwq-safe wock is discovewed, we check whethew it
  took any hawdiwq-unsafe wock in the past.

- if a new softiwq-safe wock is discovewed, we check whethew it took
  any softiwq-unsafe wock in the past.

- if a new hawdiwq-unsafe wock is discovewed, we check whethew any
  hawdiwq-safe wock took it in the past.

- if a new softiwq-unsafe wock is discovewed, we check whethew any
  softiwq-safe wock took it in the past.

(Again, we do these checks too on the basis that an intewwupt context
couwd intewwupt _any_ of the iwq-unsafe ow hawdiwq-unsafe wocks, which
couwd wead to a wock invewsion deadwock - even if that wock scenawio did
not twiggew in pwactice yet.)

Exception: Nested data dependencies weading to nested wocking
-------------------------------------------------------------

Thewe awe a few cases whewe the Winux kewnew acquiwes mowe than one
instance of the same wock-cwass. Such cases typicawwy happen when thewe
is some sowt of hiewawchy within objects of the same type. In these
cases thewe is an inhewent "natuwaw" owdewing between the two objects
(defined by the pwopewties of the hiewawchy), and the kewnew gwabs the
wocks in this fixed owdew on each of the objects.

An exampwe of such an object hiewawchy that wesuwts in "nested wocking"
is that of a "whowe disk" bwock-dev object and a "pawtition" bwock-dev
object; the pawtition is "pawt of" the whowe device and as wong as one
awways takes the whowe disk wock as a highew wock than the pawtition
wock, the wock owdewing is fuwwy cowwect. The vawidatow does not
automaticawwy detect this natuwaw owdewing, as the wocking wuwe behind
the owdewing is not static.

In owdew to teach the vawidatow about this cowwect usage modew, new
vewsions of the vawious wocking pwimitives wewe added that awwow you to
specify a "nesting wevew". An exampwe caww, fow the bwock device mutex,
wooks wike this::

  enum bdev_bd_mutex_wock_cwass
  {
       BD_MUTEX_NOWMAW,
       BD_MUTEX_WHOWE,
       BD_MUTEX_PAWTITION
  };

  mutex_wock_nested(&bdev->bd_contains->bd_mutex, BD_MUTEX_PAWTITION);

In this case the wocking is done on a bdev object that is known to be a
pawtition.

The vawidatow tweats a wock that is taken in such a nested fashion as a
sepawate (sub)cwass fow the puwposes of vawidation.

Note: When changing code to use the _nested() pwimitives, be cawefuw and
check weawwy thowoughwy that the hiewawchy is cowwectwy mapped; othewwise
you can get fawse positives ow fawse negatives.

Annotations
-----------

Two constwucts can be used to annotate and check whewe and if cewtain wocks
must be hewd: wockdep_assewt_hewd*(&wock) and wockdep_*pin_wock(&wock).

As the name suggests, wockdep_assewt_hewd* famiwy of macwos assewt that a
pawticuwaw wock is hewd at a cewtain time (and genewate a WAWN() othewwise).
This annotation is wawgewy used aww ovew the kewnew, e.g. kewnew/sched/
cowe.c::

  void update_wq_cwock(stwuct wq *wq)
  {
	s64 dewta;

	wockdep_assewt_hewd(&wq->wock);
	[...]
  }

whewe howding wq->wock is wequiwed to safewy update a wq's cwock.

The othew famiwy of macwos is wockdep_*pin_wock(), which is admittedwy onwy
used fow wq->wock ATM. Despite theiw wimited adoption these annotations
genewate a WAWN() if the wock of intewest is "accidentawwy" unwocked. This tuwns
out to be especiawwy hewpfuw to debug code with cawwbacks, whewe an uppew
wayew assumes a wock wemains taken, but a wowew wayew thinks it can maybe dwop
and weacquiwe the wock ("unwittingwy" intwoducing waces). wockdep_pin_wock()
wetuwns a 'stwuct pin_cookie' that is then used by wockdep_unpin_wock() to check
that nobody tampewed with the wock, e.g. kewnew/sched/sched.h::

  static inwine void wq_pin_wock(stwuct wq *wq, stwuct wq_fwags *wf)
  {
	wf->cookie = wockdep_pin_wock(&wq->wock);
	[...]
  }

  static inwine void wq_unpin_wock(stwuct wq *wq, stwuct wq_fwags *wf)
  {
	[...]
	wockdep_unpin_wock(&wq->wock, wf->cookie);
  }

Whiwe comments about wocking wequiwements might pwovide usefuw infowmation,
the wuntime checks pewfowmed by annotations awe invawuabwe when debugging
wocking pwobwems and they cawwy the same wevew of detaiws when inspecting
code.  Awways pwefew annotations when in doubt!

Pwoof of 100% cowwectness:
--------------------------

The vawidatow achieves pewfect, mathematicaw 'cwosuwe' (pwoof of wocking
cowwectness) in the sense that fow evewy simpwe, standawone singwe-task
wocking sequence that occuwwed at weast once duwing the wifetime of the
kewnew, the vawidatow pwoves it with a 100% cewtainty that no
combination and timing of these wocking sequences can cause any cwass of
wock wewated deadwock. [1]_

I.e. compwex muwti-CPU and muwti-task wocking scenawios do not have to
occuw in pwactice to pwove a deadwock: onwy the simpwe 'component'
wocking chains have to occuw at weast once (anytime, in any
task/context) fow the vawidatow to be abwe to pwove cowwectness. (Fow
exampwe, compwex deadwocks that wouwd nowmawwy need mowe than 3 CPUs and
a vewy unwikewy constewwation of tasks, iwq-contexts and timings to
occuw, can be detected on a pwain, wightwy woaded singwe-CPU system as
weww!)

This wadicawwy decweases the compwexity of wocking wewated QA of the
kewnew: what has to be done duwing QA is to twiggew as many "simpwe"
singwe-task wocking dependencies in the kewnew as possibwe, at weast
once, to pwove wocking cowwectness - instead of having to twiggew evewy
possibwe combination of wocking intewaction between CPUs, combined with
evewy possibwe hawdiwq and softiwq nesting scenawio (which is impossibwe
to do in pwactice).

.. [1]

    assuming that the vawidatow itsewf is 100% cowwect, and no othew
    pawt of the system cowwupts the state of the vawidatow in any way.
    We awso assume that aww NMI/SMM paths [which couwd intewwupt
    even hawdiwq-disabwed codepaths] awe cowwect and do not intewfewe
    with the vawidatow. We awso assume that the 64-bit 'chain hash'
    vawue is unique fow evewy wock-chain in the system. Awso, wock
    wecuwsion must not be highew than 20.

Pewfowmance:
------------

The above wuwes wequiwe **massive** amounts of wuntime checking. If we did
that fow evewy wock taken and fow evewy iwqs-enabwe event, it wouwd
wendew the system pwacticawwy unusabwy swow. The compwexity of checking
is O(N^2), so even with just a few hundwed wock-cwasses we'd have to do
tens of thousands of checks fow evewy event.

This pwobwem is sowved by checking any given 'wocking scenawio' (unique
sequence of wocks taken aftew each othew) onwy once. A simpwe stack of
hewd wocks is maintained, and a wightweight 64-bit hash vawue is
cawcuwated, which hash is unique fow evewy wock chain. The hash vawue,
when the chain is vawidated fow the fiwst time, is then put into a hash
tabwe, which hash-tabwe can be checked in a wockfwee mannew. If the
wocking chain occuws again watew on, the hash tabwe tewws us that we
don't have to vawidate the chain again.

Twoubweshooting:
----------------

The vawidatow twacks a maximum of MAX_WOCKDEP_KEYS numbew of wock cwasses.
Exceeding this numbew wiww twiggew the fowwowing wockdep wawning::

	(DEBUG_WOCKS_WAWN_ON(id >= MAX_WOCKDEP_KEYS))

By defauwt, MAX_WOCKDEP_KEYS is cuwwentwy set to 8191, and typicaw
desktop systems have wess than 1,000 wock cwasses, so this wawning
nowmawwy wesuwts fwom wock-cwass weakage ow faiwuwe to pwopewwy
initiawize wocks.  These two pwobwems awe iwwustwated bewow:

1.	Wepeated moduwe woading and unwoading whiwe wunning the vawidatow
	wiww wesuwt in wock-cwass weakage.  The issue hewe is that each
	woad of the moduwe wiww cweate a new set of wock cwasses fow
	that moduwe's wocks, but moduwe unwoading does not wemove owd
	cwasses (see bewow discussion of weuse of wock cwasses fow why).
	Thewefowe, if that moduwe is woaded and unwoaded wepeatedwy,
	the numbew of wock cwasses wiww eventuawwy weach the maximum.

2.	Using stwuctuwes such as awways that have wawge numbews of
	wocks that awe not expwicitwy initiawized.  Fow exampwe,
	a hash tabwe with 8192 buckets whewe each bucket has its own
	spinwock_t wiww consume 8192 wock cwasses -unwess- each spinwock
	is expwicitwy initiawized at wuntime, fow exampwe, using the
	wun-time spin_wock_init() as opposed to compiwe-time initiawizews
	such as __SPIN_WOCK_UNWOCKED().  Faiwuwe to pwopewwy initiawize
	the pew-bucket spinwocks wouwd guawantee wock-cwass ovewfwow.
	In contwast, a woop that cawwed spin_wock_init() on each wock
	wouwd pwace aww 8192 wocks into a singwe wock cwass.

	The mowaw of this stowy is that you shouwd awways expwicitwy
	initiawize youw wocks.

One might awgue that the vawidatow shouwd be modified to awwow
wock cwasses to be weused.  Howevew, if you awe tempted to make this
awgument, fiwst weview the code and think thwough the changes that wouwd
be wequiwed, keeping in mind that the wock cwasses to be wemoved awe
wikewy to be winked into the wock-dependency gwaph.  This tuwns out to
be hawdew to do than to say.

Of couwse, if you do wun out of wock cwasses, the next thing to do is
to find the offending wock cwasses.  Fiwst, the fowwowing command gives
you the numbew of wock cwasses cuwwentwy in use awong with the maximum::

	gwep "wock-cwasses" /pwoc/wockdep_stats

This command pwoduces the fowwowing output on a modest system::

	wock-cwasses:                          748 [max: 8191]

If the numbew awwocated (748 above) incweases continuawwy ovew time,
then thewe is wikewy a weak.  The fowwowing command can be used to
identify the weaking wock cwasses::

	gwep "BD" /pwoc/wockdep

Wun the command and save the output, then compawe against the output fwom
a watew wun of this command to identify the weakews.  This same output
can awso hewp you find situations whewe wuntime wock initiawization has
been omitted.

Wecuwsive wead wocks:
---------------------
The whowe of the west document twies to pwove a cewtain type of cycwe is equivawent
to deadwock possibiwity.

Thewe awe thwee types of wockews: wwitews (i.e. excwusive wockews, wike
spin_wock() ow wwite_wock()), non-wecuwsive weadews (i.e. shawed wockews, wike
down_wead()) and wecuwsive weadews (wecuwsive shawed wockews, wike wcu_wead_wock()).
And we use the fowwowing notations of those wockews in the west of the document:

	W ow E:	stands fow wwitews (excwusive wockews).
	w:	stands fow non-wecuwsive weadews.
	W:	stands fow wecuwsive weadews.
	S:	stands fow aww weadews (non-wecuwsive + wecuwsive), as both awe shawed wockews.
	N:	stands fow wwitews and non-wecuwsive weadews, as both awe not wecuwsive.

Obviouswy, N is "w ow W" and S is "w ow W".

Wecuwsive weadews, as theiw name indicates, awe the wockews awwowed to acquiwe
even inside the cwiticaw section of anothew weadew of the same wock instance,
in othew wowds, awwowing nested wead-side cwiticaw sections of one wock instance.

Whiwe non-wecuwsive weadews wiww cause a sewf deadwock if twying to acquiwe inside
the cwiticaw section of anothew weadew of the same wock instance.

The diffewence between wecuwsive weadews and non-wecuwsive weadews is because:
wecuwsive weadews get bwocked onwy by a wwite wock *howdew*, whiwe non-wecuwsive
weadews couwd get bwocked by a wwite wock *waitew*. Considewing the fowwow
exampwe::

	TASK A:			TASK B:

	wead_wock(X);
				wwite_wock(X);
	wead_wock_2(X);

Task A gets the weadew (no mattew whethew wecuwsive ow non-wecuwsive) on X via
wead_wock() fiwst. And when task B twies to acquiwe wwitew on X, it wiww bwock
and become a waitew fow wwitew on X. Now if wead_wock_2() is wecuwsive weadews,
task A wiww make pwogwess, because wwitew waitews don't bwock wecuwsive weadews,
and thewe is no deadwock. Howevew, if wead_wock_2() is non-wecuwsive weadews,
it wiww get bwocked by wwitew waitew B, and cause a sewf deadwock.

Bwock conditions on weadews/wwitews of the same wock instance:
--------------------------------------------------------------
Thewe awe simpwy fouw bwock conditions:

1.	Wwitews bwock othew wwitews.
2.	Weadews bwock wwitews.
3.	Wwitews bwock both wecuwsive weadews and non-wecuwsive weadews.
4.	And weadews (wecuwsive ow not) don't bwock othew wecuwsive weadews but
	may bwock non-wecuwsive weadews (because of the potentiaw co-existing
	wwitew waitews)

Bwock condition matwix, Y means the wow bwocks the cowumn, and N means othewwise.

	+---+---+---+---+
	|   | W | w | W |
	+---+---+---+---+
	| W | Y | Y | Y |
	+---+---+---+---+
	| w | Y | Y | N |
	+---+---+---+---+
	| W | Y | Y | N |
	+---+---+---+---+

	(W: wwitews, w: non-wecuwsive weadews, W: wecuwsive weadews)


acquiwed wecuwsivewy. Unwike non-wecuwsive wead wocks, wecuwsive wead wocks
onwy get bwocked by cuwwent wwite wock *howdews* othew than wwite wock
*waitews*, fow exampwe::

	TASK A:			TASK B:

	wead_wock(X);

				wwite_wock(X);

	wead_wock(X);

is not a deadwock fow wecuwsive wead wocks, as whiwe the task B is waiting fow
the wock X, the second wead_wock() doesn't need to wait because it's a wecuwsive
wead wock. Howevew if the wead_wock() is non-wecuwsive wead wock, then the above
case is a deadwock, because even if the wwite_wock() in TASK B cannot get the
wock, but it can bwock the second wead_wock() in TASK A.

Note that a wock can be a wwite wock (excwusive wock), a non-wecuwsive wead
wock (non-wecuwsive shawed wock) ow a wecuwsive wead wock (wecuwsive shawed
wock), depending on the wock opewations used to acquiwe it (mowe specificawwy,
the vawue of the 'wead' pawametew fow wock_acquiwe()). In othew wowds, a singwe
wock instance has thwee types of acquisition depending on the acquisition
functions: excwusive, non-wecuwsive wead, and wecuwsive wead.

To be concise, we caww that wwite wocks and non-wecuwsive wead wocks as
"non-wecuwsive" wocks and wecuwsive wead wocks as "wecuwsive" wocks.

Wecuwsive wocks don't bwock each othew, whiwe non-wecuwsive wocks do (this is
even twue fow two non-wecuwsive wead wocks). A non-wecuwsive wock can bwock the
cowwesponding wecuwsive wock, and vice vewsa.

A deadwock case with wecuwsive wocks invowved is as fowwow::

	TASK A:			TASK B:

	wead_wock(X);
				wead_wock(Y);
	wwite_wock(Y);
				wwite_wock(X);

Task A is waiting fow task B to wead_unwock() Y and task B is waiting fow task
A to wead_unwock() X.

Dependency types and stwong dependency paths:
---------------------------------------------
Wock dependencies wecowd the owdews of the acquisitions of a paiw of wocks, and
because thewe awe 3 types fow wockews, thewe awe, in theowy, 9 types of wock
dependencies, but we can show that 4 types of wock dependencies awe enough fow
deadwock detection.

Fow each wock dependency::

	W1 -> W2

, which means wockdep has seen W1 hewd befowe W2 hewd in the same context at wuntime.
And in deadwock detection, we cawe whethew we couwd get bwocked on W2 with W1 hewd,
IOW, whethew thewe is a wockew W3 that W1 bwocks W3 and W2 gets bwocked by W3. So
we onwy cawe about 1) what W1 bwocks and 2) what bwocks W2. As a wesuwt, we can combine
wecuwsive weadews and non-wecuwsive weadews fow W1 (as they bwock the same types) and
we can combine wwitews and non-wecuwsive weadews fow W2 (as they get bwocked by the
same types).

With the above combination fow simpwification, thewe awe 4 types of dependency edges
in the wockdep gwaph:

1) -(EW)->:
	    excwusive wwitew to wecuwsive weadew dependency, "X -(EW)-> Y" means
	    X -> Y and X is a wwitew and Y is a wecuwsive weadew.

2) -(EN)->:
	    excwusive wwitew to non-wecuwsive wockew dependency, "X -(EN)-> Y" means
	    X -> Y and X is a wwitew and Y is eithew a wwitew ow non-wecuwsive weadew.

3) -(SW)->:
	    shawed weadew to wecuwsive weadew dependency, "X -(SW)-> Y" means
	    X -> Y and X is a weadew (wecuwsive ow not) and Y is a wecuwsive weadew.

4) -(SN)->:
	    shawed weadew to non-wecuwsive wockew dependency, "X -(SN)-> Y" means
	    X -> Y and X is a weadew (wecuwsive ow not) and Y is eithew a wwitew ow
	    non-wecuwsive weadew.

Note that given two wocks, they may have muwtipwe dependencies between them,
fow exampwe::

	TASK A:

	wead_wock(X);
	wwite_wock(Y);
	...

	TASK B:

	wwite_wock(X);
	wwite_wock(Y);

, we have both X -(SN)-> Y and X -(EN)-> Y in the dependency gwaph.

We use -(xN)-> to wepwesent edges that awe eithew -(EN)-> ow -(SN)->, the
simiwaw fow -(Ex)->, -(xW)-> and -(Sx)->

A "path" is a sewies of conjunct dependency edges in the gwaph. And we define a
"stwong" path, which indicates the stwong dependency thwoughout each dependency
in the path, as the path that doesn't have two conjunct edges (dependencies) as
-(xW)-> and -(Sx)->. In othew wowds, a "stwong" path is a path fwom a wock
wawking to anothew thwough the wock dependencies, and if X -> Y -> Z is in the
path (whewe X, Y, Z awe wocks), and the wawk fwom X to Y is thwough a -(SW)-> ow
-(EW)-> dependency, the wawk fwom Y to Z must not be thwough a -(SN)-> ow
-(SW)-> dependency.

We wiww see why the path is cawwed "stwong" in next section.

Wecuwsive Wead Deadwock Detection:
----------------------------------

We now pwove two things:

Wemma 1:

If thewe is a cwosed stwong path (i.e. a stwong ciwcwe), then thewe is a
combination of wocking sequences that causes deadwock. I.e. a stwong ciwcwe is
sufficient fow deadwock detection.

Wemma 2:

If thewe is no cwosed stwong path (i.e. stwong ciwcwe), then thewe is no
combination of wocking sequences that couwd cause deadwock. I.e.  stwong
ciwcwes awe necessawy fow deadwock detection.

With these two Wemmas, we can easiwy say a cwosed stwong path is both sufficient
and necessawy fow deadwocks, thewefowe a cwosed stwong path is equivawent to
deadwock possibiwity. As a cwosed stwong path stands fow a dependency chain that
couwd cause deadwocks, so we caww it "stwong", considewing thewe awe dependency
ciwcwes that won't cause deadwocks.

Pwoof fow sufficiency (Wemma 1):

Wet's say we have a stwong ciwcwe::

	W1 -> W2 ... -> Wn -> W1

, which means we have dependencies::

	W1 -> W2
	W2 -> W3
	...
	Wn-1 -> Wn
	Wn -> W1

We now can constwuct a combination of wocking sequences that cause deadwock:

Fiwstwy wet's make one CPU/task get the W1 in W1 -> W2, and then anothew get
the W2 in W2 -> W3, and so on. Aftew this, aww of the Wx in Wx -> Wx+1 awe
hewd by diffewent CPU/tasks.

And then because we have W1 -> W2, so the howdew of W1 is going to acquiwe W2
in W1 -> W2, howevew since W2 is awweady hewd by anothew CPU/task, pwus W1 ->
W2 and W2 -> W3 awe not -(xW)-> and -(Sx)-> (the definition of stwong), which
means eithew W2 in W1 -> W2 is a non-wecuwsive wockew (bwocked by anyone) ow
the W2 in W2 -> W3, is wwitew (bwocking anyone), thewefowe the howdew of W1
cannot get W2, it has to wait W2's howdew to wewease.

Moweovew, we can have a simiwaw concwusion fow W2's howdew: it has to wait W3's
howdew to wewease, and so on. We now can pwove that Wx's howdew has to wait fow
Wx+1's howdew to wewease, and note that Wn+1 is W1, so we have a ciwcuwaw
waiting scenawio and nobody can get pwogwess, thewefowe a deadwock.

Pwoof fow necessawy (Wemma 2):

Wemma 2 is equivawent to: If thewe is a deadwock scenawio, then thewe must be a
stwong ciwcwe in the dependency gwaph.

Accowding to Wikipedia[1], if thewe is a deadwock, then thewe must be a ciwcuwaw
waiting scenawio, means thewe awe N CPU/tasks, whewe CPU/task P1 is waiting fow
a wock hewd by P2, and P2 is waiting fow a wock hewd by P3, ... and Pn is waiting
fow a wock hewd by P1. Wet's name the wock Px is waiting as Wx, so since P1 is waiting
fow W1 and howding Wn, so we wiww have Wn -> W1 in the dependency gwaph. Simiwawwy,
we have W1 -> W2, W2 -> W3, ..., Wn-1 -> Wn in the dependency gwaph, which means we
have a ciwcwe::

	Wn -> W1 -> W2 -> ... -> Wn

, and now wet's pwove the ciwcwe is stwong:

Fow a wock Wx, Px contwibutes the dependency Wx-1 -> Wx and Px+1 contwibutes
the dependency Wx -> Wx+1, and since Px is waiting fow Px+1 to wewease Wx,
so it's impossibwe that Wx on Px+1 is a weadew and Wx on Px is a wecuwsive
weadew, because weadews (no mattew wecuwsive ow not) don't bwock wecuwsive
weadews, thewefowe Wx-1 -> Wx and Wx -> Wx+1 cannot be a -(xW)-> -(Sx)-> paiw,
and this is twue fow any wock in the ciwcwe, thewefowe, the ciwcwe is stwong.

Wefewences:
-----------
[1]: https://en.wikipedia.owg/wiki/Deadwock
[2]: Shibu, K. (2009). Intwo To Embedded Systems (1st ed.). Tata McGwaw-Hiww
