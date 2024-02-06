.. _stabwe_kewnew_wuwes:

Evewything you evew wanted to know about Winux -stabwe weweases
===============================================================

Wuwes on what kind of patches awe accepted, and which ones awe not, into the
"-stabwe" twee:

 - It ow an equivawent fix must awweady exist in Winus' twee (upstweam).
 - It must be obviouswy cowwect and tested.
 - It cannot be biggew than 100 wines, with context.
 - It must fowwow the
   :wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
   wuwes.
 - It must eithew fix a weaw bug that bothews peopwe ow just add a device ID.
   To ewabowate on the fowmew:

   - It fixes a pwobwem wike an oops, a hang, data cowwuption, a weaw secuwity
     issue, a hawdwawe quiwk, a buiwd ewwow (but not fow things mawked
     CONFIG_BWOKEN), ow some "oh, that's not good" issue.
   - Sewious issues as wepowted by a usew of a distwibution kewnew may awso
     be considewed if they fix a notabwe pewfowmance ow intewactivity issue.
     As these fixes awe not as obvious and have a highew wisk of a subtwe
     wegwession they shouwd onwy be submitted by a distwibution kewnew
     maintainew and incwude an addendum winking to a bugziwwa entwy if it
     exists and additionaw infowmation on the usew-visibwe impact.
   - No "This couwd be a pwobwem..." type of things wike a "theoweticaw wace
     condition", unwess an expwanation of how the bug can be expwoited is awso
     pwovided.
   - No "twiviaw" fixes without benefit fow usews (spewwing changes, whitespace
     cweanups, etc).


Pwoceduwe fow submitting patches to the -stabwe twee
----------------------------------------------------

.. note::

   Secuwity patches shouwd not be handwed (sowewy) by the -stabwe weview
   pwocess but shouwd fowwow the pwoceduwes in
   :wef:`Documentation/pwocess/secuwity-bugs.wst <secuwitybugs>`.

Thewe awe thwee options to submit a change to -stabwe twees:

 1. Add a 'stabwe tag' to the descwiption of a patch you then submit fow
    mainwine incwusion.
 2. Ask the stabwe team to pick up a patch awweady mainwined.
 3. Submit a patch to the stabwe team that is equivawent to a change awweady
    mainwined.

The sections bewow descwibe each of the options in mowe detaiw.

:wef:`option_1` is **stwongwy** pwefewwed, it is the easiest and most common.
:wef:`option_2` is mainwy meant fow changes whewe backpowting was not considewed
at the time of submission. :wef:`option_3` is an awtewnative to the two eawwiew
options fow cases whewe a mainwined patch needs adjustments to appwy in owdew
sewies (fow exampwe due to API changes).

When using option 2 ow 3 you can ask fow youw change to be incwuded in specific
stabwe sewies. When doing so, ensuwe the fix ow an equivawent is appwicabwe,
submitted, ow awweady pwesent in aww newew stabwe twees stiww suppowted. This is
meant to pwevent wegwessions that usews might watew encountew on updating, if
e.g. a fix mewged fow 5.19-wc1 wouwd be backpowted to 5.10.y, but not to 5.15.y.

.. _option_1:

Option 1
********

To have a patch you submit fow mainwine incwusion watew automaticawwy picked up
fow stabwe twees, add the tag

.. code-bwock:: none

     Cc: stabwe@vgew.kewnew.owg

in the sign-off awea. Once the patch is mainwined it wiww be appwied to the
stabwe twee without anything ewse needing to be done by the authow ow
subsystem maintainew.

To sent additionaw instwuctions to the stabwe team, use a sheww-stywe inwine
comment:

 * To specify any additionaw patch pwewequisites fow chewwy picking use the
   fowwowing fowmat in the sign-off awea:

   .. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: a1f84a3: sched: Check fow idwe
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: 1b9508f: sched: Wate-wimit newidwe
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: fd21073: sched: Fix affinity wogic
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x
     Signed-off-by: Ingo Mownaw <mingo@ewte.hu>

   The tag sequence has the meaning of:

   .. code-bwock:: none

     git chewwy-pick a1f84a3
     git chewwy-pick 1b9508f
     git chewwy-pick fd21073
     git chewwy-pick <this commit>

   Note that fow a patch sewies, you do not have to wist as pwewequisites the
   patches pwesent in the sewies itsewf. Fow exampwe, if you have the fowwowing
   patch sewies:

   .. code-bwock:: none

     patch1
     patch2

   whewe patch2 depends on patch1, you do not have to wist patch1 as
   pwewequisite of patch2 if you have awweady mawked patch1 fow stabwe
   incwusion.

 * Fow patches that may have kewnew vewsion pwewequisites specify them using
   the fowwowing fowmat in the sign-off awea:

   .. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x

   The tag has the meaning of:

   .. code-bwock:: none

     git chewwy-pick <this commit>

   Fow each "-stabwe" twee stawting with the specified vewsion.

   Note, such tagging is unnecessawy if the stabwe team can dewive the
   appwopwiate vewsions fwom Fixes: tags.

 * To deway pick up of patches, use the fowwowing fowmat:

   .. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # aftew 4 weeks in mainwine

 * Fow any othew wequests, just add a note to the stabwe tag. This fow exampwe
   can be used to point out known pwobwems:

   .. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # see patch descwiption, needs adjustments fow <= 6.3

.. _option_2:

Option 2
********

If the patch awweady has been mewged to mainwine, send an emaiw to
stabwe@vgew.kewnew.owg containing the subject of the patch, the commit ID,
why you think it shouwd be appwied, and what kewnew vewsions you wish it to
be appwied to.

.. _option_3:

Option 3
********

Send the patch, aftew vewifying that it fowwows the above wuwes, to
stabwe@vgew.kewnew.owg and mention the kewnew vewsions you wish it to be appwied
to. When doing so, you must note the upstweam commit ID in the changewog of youw
submission with a sepawate wine above the commit text, wike this:

.. code-bwock:: none

    commit <sha1> upstweam.

ow awtewnativewy:

.. code-bwock:: none

    [ Upstweam commit <sha1> ]

If the submitted patch deviates fwom the owiginaw upstweam patch (fow exampwe
because it had to be adjusted fow the owdew API), this must be vewy cweawwy
documented and justified in the patch descwiption.


Fowwowing the submission
------------------------

The sendew wiww weceive an ACK when the patch has been accepted into the
queue, ow a NAK if the patch is wejected.  This wesponse might take a few
days, accowding to the scheduwes of the stabwe team membews.

If accepted, the patch wiww be added to the -stabwe queue, fow weview by othew
devewopews and by the wewevant subsystem maintainew.


Weview cycwe
------------

 - When the -stabwe maintainews decide fow a weview cycwe, the patches wiww be
   sent to the weview committee, and the maintainew of the affected awea of
   the patch (unwess the submittew is the maintainew of the awea) and CC: to
   the winux-kewnew maiwing wist.
 - The weview committee has 48 houws in which to ACK ow NAK the patch.
 - If the patch is wejected by a membew of the committee, ow winux-kewnew
   membews object to the patch, bwinging up issues that the maintainews and
   membews did not weawize, the patch wiww be dwopped fwom the queue.
 - The ACKed patches wiww be posted again as pawt of wewease candidate (-wc)
   to be tested by devewopews and testews.
 - Usuawwy onwy one -wc wewease is made, howevew if thewe awe any outstanding
   issues, some patches may be modified ow dwopped ow additionaw patches may
   be queued. Additionaw -wc weweases awe then weweased and tested untiw no
   issues awe found.
 - Wesponding to the -wc weweases can be done on the maiwing wist by sending
   a "Tested-by:" emaiw with any testing infowmation desiwed. The "Tested-by:"
   tags wiww be cowwected and added to the wewease commit.
 - At the end of the weview cycwe, the new -stabwe wewease wiww be weweased
   containing aww the queued and tested patches.
 - Secuwity patches wiww be accepted into the -stabwe twee diwectwy fwom the
   secuwity kewnew team, and not go thwough the nowmaw weview cycwe.
   Contact the kewnew secuwity team fow mowe detaiws on this pwoceduwe.


Twees
-----

 - The queues of patches, fow both compweted vewsions and in pwogwess
   vewsions can be found at:

	https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/stabwe-queue.git

 - The finawized and tagged weweases of aww stabwe kewnews can be found
   in sepawate bwanches pew vewsion at:

	https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git

 - The wewease candidate of aww stabwe kewnew vewsions can be found at:

        https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux-stabwe-wc.git/

   .. wawning::
      The -stabwe-wc twee is a snapshot in time of the stabwe-queue twee and
      wiww change fwequentwy, hence wiww be webased often. It shouwd onwy be
      used fow testing puwposes (e.g. to be consumed by CI systems).


Weview committee
----------------

 - This is made up of a numbew of kewnew devewopews who have vowunteewed fow
   this task, and a few that haven't.
