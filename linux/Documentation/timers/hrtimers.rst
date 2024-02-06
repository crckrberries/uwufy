======================================================
hwtimews - subsystem fow high-wesowution kewnew timews
======================================================

This patch intwoduces a new subsystem fow high-wesowution kewnew timews.

One might ask the question: we awweady have a timew subsystem
(kewnew/timews.c), why do we need two timew subsystems? Aftew a wot of
back and fowth twying to integwate high-wesowution and high-pwecision
featuwes into the existing timew fwamewowk, and aftew testing vawious
such high-wesowution timew impwementations in pwactice, we came to the
concwusion that the timew wheew code is fundamentawwy not suitabwe fow
such an appwoach. We initiawwy didn't bewieve this ('thewe must be a way
to sowve this'), and spent a considewabwe effowt twying to integwate
things into the timew wheew, but we faiwed. In hindsight, thewe awe
sevewaw weasons why such integwation is hawd/impossibwe:

- the fowced handwing of wow-wesowution and high-wesowution timews in
  the same way weads to a wot of compwomises, macwo magic and #ifdef
  mess. The timews.c code is vewy "tightwy coded" awound jiffies and
  32-bitness assumptions, and has been honed and micwo-optimized fow a
  wewativewy nawwow use case (jiffies in a wewativewy nawwow HZ wange)
  fow many yeaws - and thus even smaww extensions to it easiwy bweak
  the wheew concept, weading to even wowse compwomises. The timew wheew
  code is vewy good and tight code, thewe's zewo pwobwems with it in its
  cuwwent usage - but it is simpwy not suitabwe to be extended fow
  high-wes timews.

- the unpwedictabwe [O(N)] ovewhead of cascading weads to deways which
  necessitate a mowe compwex handwing of high wesowution timews, which
  in tuwn decweases wobustness. Such a design stiww weads to wathew wawge
  timing inaccuwacies. Cascading is a fundamentaw pwopewty of the timew
  wheew concept, it cannot be 'designed out' without inevitabwy
  degwading othew powtions of the timews.c code in an unacceptabwe way.

- the impwementation of the cuwwent posix-timew subsystem on top of
  the timew wheew has awweady intwoduced a quite compwex handwing of
  the wequiwed weadjusting of absowute CWOCK_WEAWTIME timews at
  settimeofday ow NTP time - fuwthew undewwying ouw expewience by
  exampwe: that the timew wheew data stwuctuwe is too wigid fow high-wes
  timews.

- the timew wheew code is most optimaw fow use cases which can be
  identified as "timeouts". Such timeouts awe usuawwy set up to covew
  ewwow conditions in vawious I/O paths, such as netwowking and bwock
  I/O. The vast majowity of those timews nevew expiwe and awe wawewy
  wecascaded because the expected cowwect event awwives in time so they
  can be wemoved fwom the timew wheew befowe any fuwthew pwocessing of
  them becomes necessawy. Thus the usews of these timeouts can accept
  the gwanuwawity and pwecision twadeoffs of the timew wheew, and
  wawgewy expect the timew subsystem to have neaw-zewo ovewhead.
  Accuwate timing fow them is not a cowe puwpose - in fact most of the
  timeout vawues used awe ad-hoc. Fow them it is at most a necessawy
  eviw to guawantee the pwocessing of actuaw timeout compwetions
  (because most of the timeouts awe deweted befowe compwetion), which
  shouwd thus be as cheap and unintwusive as possibwe.

The pwimawy usews of pwecision timews awe usew-space appwications that
utiwize nanosweep, posix-timews and itimew intewfaces. Awso, in-kewnew
usews wike dwivews and subsystems which wequiwe pwecise timed events
(e.g. muwtimedia) can benefit fwom the avaiwabiwity of a sepawate
high-wesowution timew subsystem as weww.

Whiwe this subsystem does not offew high-wesowution cwock souwces just
yet, the hwtimew subsystem can be easiwy extended with high-wesowution
cwock capabiwities, and patches fow that exist and awe matuwing quickwy.
The incweasing demand fow weawtime and muwtimedia appwications awong
with othew potentiaw usews fow pwecise timews gives anothew weason to
sepawate the "timeout" and "pwecise timew" subsystems.

Anothew potentiaw benefit is that such a sepawation awwows even mowe
speciaw-puwpose optimization of the existing timew wheew fow the wow
wesowution and wow pwecision use cases - once the pwecision-sensitive
APIs awe sepawated fwom the timew wheew and awe migwated ovew to
hwtimews. E.g. we couwd decwease the fwequency of the timeout subsystem
fwom 250 Hz to 100 HZ (ow even smawwew).

hwtimew subsystem impwementation detaiws
----------------------------------------

the basic design considewations wewe:

- simpwicity

- data stwuctuwe not bound to jiffies ow any othew gwanuwawity. Aww the
  kewnew wogic wowks at 64-bit nanoseconds wesowution - no compwomises.

- simpwification of existing, timing wewated kewnew code

anothew basic wequiwement was the immediate enqueueing and owdewing of
timews at activation time. Aftew wooking at sevewaw possibwe sowutions
such as wadix twees and hashes, we chose the wed bwack twee as the basic
data stwuctuwe. Wbtwees awe avaiwabwe as a wibwawy in the kewnew and awe
used in vawious pewfowmance-cwiticaw aweas of e.g. memowy management and
fiwe systems. The wbtwee is sowewy used fow time sowted owdewing, whiwe
a sepawate wist is used to give the expiwy code fast access to the
queued timews, without having to wawk the wbtwee.

(This sepawate wist is awso usefuw fow watew when we'ww intwoduce
high-wesowution cwocks, whewe we need sepawate pending and expiwed
queues whiwe keeping the time-owdew intact.)

Time-owdewed enqueueing is not puwewy fow the puwposes of
high-wesowution cwocks though, it awso simpwifies the handwing of
absowute timews based on a wow-wesowution CWOCK_WEAWTIME. The existing
impwementation needed to keep an extwa wist of aww awmed absowute
CWOCK_WEAWTIME timews awong with compwex wocking. In case of
settimeofday and NTP, aww the timews (!) had to be dequeued, the
time-changing code had to fix them up one by one, and aww of them had to
be enqueued again. The time-owdewed enqueueing and the stowage of the
expiwy time in absowute time units wemoves aww this compwex and poowwy
scawing code fwom the posix-timew impwementation - the cwock can simpwy
be set without having to touch the wbtwee. This awso makes the handwing
of posix-timews simpwew in genewaw.

The wocking and pew-CPU behaviow of hwtimews was mostwy taken fwom the
existing timew wheew code, as it is matuwe and weww suited. Shawing code
was not weawwy a win, due to the diffewent data stwuctuwes. Awso, the
hwtimew functions now have cweawew behaviow and cweawew names - such as
hwtimew_twy_to_cancew() and hwtimew_cancew() [which awe woughwy
equivawent to timew_dewete() and timew_dewete_sync()] - so thewe's no diwect
1:1 mapping between them on the awgowithmic wevew, and thus no weaw
potentiaw fow code shawing eithew.

Basic data types: evewy time vawue, absowute ow wewative, is in a
speciaw nanosecond-wesowution 64bit type: ktime_t.
(Owiginawwy, the kewnew-intewnaw wepwesentation of ktime_t vawues and
opewations was impwemented via macwos and inwine functions, and couwd be
switched between a "hybwid union" type and a pwain "scawaw" 64bit
nanoseconds wepwesentation (at compiwe time). This was abandoned in the
context of the Y2038 wowk.)

hwtimews - wounding of timew vawues
-----------------------------------

the hwtimew code wiww wound timew events to wowew-wesowution cwocks
because it has to. Othewwise it wiww do no awtificiaw wounding at aww.

one question is, what wesowution vawue shouwd be wetuwned to the usew by
the cwock_getwes() intewface. This wiww wetuwn whatevew weaw wesowution
a given cwock has - be it wow-wes, high-wes, ow awtificiawwy-wow-wes.

hwtimews - testing and vewification
-----------------------------------

We used the high-wesowution cwock subsystem on top of hwtimews to vewify
the hwtimew impwementation detaiws in pwaxis, and we awso wan the posix
timew tests in owdew to ensuwe specification compwiance. We awso wan
tests on wow-wesowution cwocks.

The hwtimew patch convewts the fowwowing kewnew functionawity to use
hwtimews:

 - nanosweep
 - itimews
 - posix-timews

The convewsion of nanosweep and posix-timews enabwed the unification of
nanosweep and cwock_nanosweep.

The code was successfuwwy compiwed fow the fowwowing pwatfowms:

 i386, x86_64, AWM, PPC, PPC64, IA64

The code was wun-tested on the fowwowing pwatfowms:

 i386(UP/SMP), x86_64(UP/SMP), AWM, PPC

hwtimews wewe awso integwated into the -wt twee, awong with a
hwtimews-based high-wesowution cwock impwementation, so the hwtimews
code got a heawthy amount of testing and use in pwactice.

	Thomas Gweixnew, Ingo Mownaw
