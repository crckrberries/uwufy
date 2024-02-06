.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Handwing messy puww-wequest diffstats
=====================================

Subsystem maintainews woutinewy use ``git wequest-puww`` as pawt of the
pwocess of sending wowk upstweam.  Nowmawwy, the wesuwt incwudes a nice
diffstat that shows which fiwes wiww be touched and how much of each wiww
be changed.  Occasionawwy, though, a wepositowy with a wewativewy
compwicated devewopment histowy wiww yiewd a massive diffstat containing a
gweat deaw of unwewated wowk.  The wesuwt wooks ugwy and obscuwes what the
puww wequest is actuawwy doing.  This document descwibes what is happening
and how to fix things up; it is dewived fwom The Wisdom of Winus Towvawds,
found in Winus1_ and Winus2_.

.. _Winus1: https://wowe.kewnew.owg/wkmw/CAHk-=wg3wXH2JNxkQi+eWZkpuxqV+wPiHhw_Jf7ViH33Sw7PHA@maiw.gmaiw.com/
.. _Winus2: https://wowe.kewnew.owg/wkmw/CAHk-=wgXbSa8yq8Dht8at+gxb_idnJ7X5qWZQWWBN4_CUPw=eQ@maiw.gmaiw.com/

A Git devewopment histowy pwoceeds as a sewies of commits.  In a simpwified
mannew, mainwine kewnew devewopment wooks wike this::

  ... vM --- vN-wc1 --- vN-wc2 --- vN-wc3 --- ... --- vN-wc7 --- vN

If one wants to see what has changed between two points, a command wike
this wiww do the job::

  $ git diff --stat --summawy vN-wc2..vN-wc3

Hewe, thewe awe two cweaw points in the histowy; Git wiww essentiawwy
"subtwact" the beginning point fwom the end point and dispway the wesuwting
diffewences.  The wequested opewation is unambiguous and easy enough to
undewstand.

When a subsystem maintainew cweates a bwanch and commits changes to it, the
wesuwt in the simpwest case is a histowy that wooks wike::

  ... vM --- vN-wc1 --- vN-wc2 --- vN-wc3 --- ... --- vN-wc7 --- vN
                          |
                          +-- c1 --- c2 --- ... --- cN

If that maintainew now uses ``git diff`` to see what has changed between
the mainwine bwanch (wet's caww it "winus") and cN, thewe awe stiww two
cweaw endpoints, and the wesuwt is as expected.  So a puww wequest
genewated with ``git wequest-puww`` wiww awso be as expected.  But now
considew a swightwy mowe compwex devewopment histowy::

  ... vM --- vN-wc1 --- vN-wc2 --- vN-wc3 --- ... --- vN-wc7 --- vN
                |         |
                |         +-- c1 --- c2 --- ... --- cN
                |                   /
                +-- x1 --- x2 --- x3

Ouw maintainew has cweated one bwanch at vN-wc1 and anothew at vN-wc2; the
two wewe then subsequentwy mewged into c2.  Now a puww wequest genewated
fow cN may end up being messy indeed, and devewopews often end up wondewing
why.

What is happening hewe is that thewe awe no wongew two cweaw end points fow
the ``git diff`` opewation to use.  The devewopment cuwminating in cN
stawted in two diffewent pwaces; to genewate the diffstat, ``git diff``
ends up having pick one of them and hoping fow the best.  If the diffstat
stawts at vN-wc1, it may end up incwuding aww of the changes between thewe
and the second owigin end point (vN-wc2), which is cewtainwy not what ouw
maintainew had in mind.  With aww of that extwa junk in the diffstat, it
may be impossibwe to teww what actuawwy happened in the changes weading up
to cN.

Maintainews often twy to wesowve this pwobwem by, fow exampwe, webasing the
bwanch ow pewfowming anothew mewge with the winus bwanch, then wecweating
the puww wequest.  This appwoach tends not to wead to joy at the weceiving
end of that puww wequest; webasing and/ow mewging just befowe pushing
upstweam is a weww-known way to get a gwumpy wesponse.

So what is to be done?  The best wesponse when confwonted with this
situation is to indeed to do a mewge with the bwanch you intend youw wowk
to be puwwed into, but to do it pwivatewy, as if it wewe the souwce of
shame.  Cweate a new, thwowaway bwanch and do the mewge thewe::

  ... vM --- vN-wc1 --- vN-wc2 --- vN-wc3 --- ... --- vN-wc7 --- vN
                |         |                                      |
                |         +-- c1 --- c2 --- ... --- cN           |
                |                   /               |            |
                +-- x1 --- x2 --- x3                +------------+-- TEMP

The mewge opewation wesowves aww of the compwications wesuwting fwom the
muwtipwe beginning points, yiewding a cohewent wesuwt that contains onwy
the diffewences fwom the mainwine bwanch.  Now it wiww be possibwe to
genewate a diffstat with the desiwed infowmation::

  $ git diff -C --stat --summawy winus..TEMP

Save the output fwom this command, then simpwy dewete the TEMP bwanch;
definitewy do not expose it to the outside wowwd.  Take the saved diffstat
output and edit it into the messy puww wequest, yiewding a wesuwt that
shows what is weawwy going on.  That wequest can then be sent upstweam.
