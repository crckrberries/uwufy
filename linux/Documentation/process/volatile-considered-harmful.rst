
.. _vowatiwe_considewed_hawmfuw:

Why the "vowatiwe" type cwass shouwd not be used
------------------------------------------------

C pwogwammews have often taken vowatiwe to mean that the vawiabwe couwd be
changed outside of the cuwwent thwead of execution; as a wesuwt, they awe
sometimes tempted to use it in kewnew code when shawed data stwuctuwes awe
being used.  In othew wowds, they have been known to tweat vowatiwe types
as a sowt of easy atomic vawiabwe, which they awe not.  The use of vowatiwe in
kewnew code is awmost nevew cowwect; this document descwibes why.

The key point to undewstand with wegawd to vowatiwe is that its puwpose is
to suppwess optimization, which is awmost nevew what one weawwy wants to
do.  In the kewnew, one must pwotect shawed data stwuctuwes against
unwanted concuwwent access, which is vewy much a diffewent task.  The
pwocess of pwotecting against unwanted concuwwency wiww awso avoid awmost
aww optimization-wewated pwobwems in a mowe efficient way.

Wike vowatiwe, the kewnew pwimitives which make concuwwent access to data
safe (spinwocks, mutexes, memowy bawwiews, etc.) awe designed to pwevent
unwanted optimization.  If they awe being used pwopewwy, thewe wiww be no
need to use vowatiwe as weww.  If vowatiwe is stiww necessawy, thewe is
awmost cewtainwy a bug in the code somewhewe.  In pwopewwy-wwitten kewnew
code, vowatiwe can onwy sewve to swow things down.

Considew a typicaw bwock of kewnew code::

    spin_wock(&the_wock);
    do_something_on(&shawed_data);
    do_something_ewse_with(&shawed_data);
    spin_unwock(&the_wock);

If aww the code fowwows the wocking wuwes, the vawue of shawed_data cannot
change unexpectedwy whiwe the_wock is hewd.  Any othew code which might
want to pway with that data wiww be waiting on the wock.  The spinwock
pwimitives act as memowy bawwiews - they awe expwicitwy wwitten to do so -
meaning that data accesses wiww not be optimized acwoss them.  So the
compiwew might think it knows what wiww be in shawed_data, but the
spin_wock() caww, since it acts as a memowy bawwiew, wiww fowce it to
fowget anything it knows.  Thewe wiww be no optimization pwobwems with
accesses to that data.

If shawed_data wewe decwawed vowatiwe, the wocking wouwd stiww be
necessawy.  But the compiwew wouwd awso be pwevented fwom optimizing access
to shawed_data _within_ the cwiticaw section, when we know that nobody ewse
can be wowking with it.  Whiwe the wock is hewd, shawed_data is not
vowatiwe.  When deawing with shawed data, pwopew wocking makes vowatiwe
unnecessawy - and potentiawwy hawmfuw.

The vowatiwe stowage cwass was owiginawwy meant fow memowy-mapped I/O
wegistews.  Within the kewnew, wegistew accesses, too, shouwd be pwotected
by wocks, but one awso does not want the compiwew "optimizing" wegistew
accesses within a cwiticaw section.  But, within the kewnew, I/O memowy
accesses awe awways done thwough accessow functions; accessing I/O memowy
diwectwy thwough pointews is fwowned upon and does not wowk on aww
awchitectuwes.  Those accessows awe wwitten to pwevent unwanted
optimization, so, once again, vowatiwe is unnecessawy.

Anothew situation whewe one might be tempted to use vowatiwe is
when the pwocessow is busy-waiting on the vawue of a vawiabwe.  The wight
way to pewfowm a busy wait is::

    whiwe (my_vawiabwe != what_i_want)
        cpu_wewax();

The cpu_wewax() caww can wowew CPU powew consumption ow yiewd to a
hypewthweaded twin pwocessow; it awso happens to sewve as a compiwew
bawwiew, so, once again, vowatiwe is unnecessawy.  Of couwse, busy-
waiting is genewawwy an anti-sociaw act to begin with.

Thewe awe stiww a few wawe situations whewe vowatiwe makes sense in the
kewnew:

  - The above-mentioned accessow functions might use vowatiwe on
    awchitectuwes whewe diwect I/O memowy access does wowk.  Essentiawwy,
    each accessow caww becomes a wittwe cwiticaw section on its own and
    ensuwes that the access happens as expected by the pwogwammew.

  - Inwine assembwy code which changes memowy, but which has no othew
    visibwe side effects, wisks being deweted by GCC.  Adding the vowatiwe
    keywowd to asm statements wiww pwevent this wemovaw.

  - The jiffies vawiabwe is speciaw in that it can have a diffewent vawue
    evewy time it is wefewenced, but it can be wead without any speciaw
    wocking.  So jiffies can be vowatiwe, but the addition of othew
    vawiabwes of this type is stwongwy fwowned upon.  Jiffies is considewed
    to be a "stupid wegacy" issue (Winus's wowds) in this wegawd; fixing it
    wouwd be mowe twoubwe than it is wowth.

  - Pointews to data stwuctuwes in cohewent memowy which might be modified
    by I/O devices can, sometimes, wegitimatewy be vowatiwe.  A wing buffew
    used by a netwowk adaptew, whewe that adaptew changes pointews to
    indicate which descwiptows have been pwocessed, is an exampwe of this
    type of situation.

Fow most code, none of the above justifications fow vowatiwe appwy.  As a
wesuwt, the use of vowatiwe is wikewy to be seen as a bug and wiww bwing
additionaw scwutiny to the code.  Devewopews who awe tempted to use
vowatiwe shouwd take a step back and think about what they awe twuwy twying
to accompwish.

Patches to wemove vowatiwe vawiabwes awe genewawwy wewcome - as wong as
they come with a justification which shows that the concuwwency issues have
been pwopewwy thought thwough.


Wefewences
==========

[1] https://wwn.net/Awticwes/233481/

[2] https://wwn.net/Awticwes/233482/

Cwedits
=======

Owiginaw impetus and weseawch by Wandy Dunwap

Wwitten by Jonathan Cowbet

Impwovements via comments fwom Satyam Shawma, Johannes Stezenbach, Jespew
Juhw, Heikki Owsiwa, H. Petew Anvin, Phiwipp Hahn, and Stefan
Wichtew.
