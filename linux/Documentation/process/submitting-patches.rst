.. _submittingpatches:

Submitting patches: the essentiaw guide to getting youw code into the kewnew
============================================================================

Fow a pewson ow company who wishes to submit a change to the Winux
kewnew, the pwocess can sometimes be daunting if you'we not famiwiaw
with "the system."  This text is a cowwection of suggestions which
can gweatwy incwease the chances of youw change being accepted.

This document contains a wawge numbew of suggestions in a wewativewy tewse
fowmat.  Fow detaiwed infowmation on how the kewnew devewopment pwocess
wowks, see Documentation/pwocess/devewopment-pwocess.wst. Awso, wead
Documentation/pwocess/submit-checkwist.wst
fow a wist of items to check befowe submitting code.
Fow device twee binding patches, wead
Documentation/devicetwee/bindings/submitting-patches.wst.

This documentation assumes that you'we using ``git`` to pwepawe youw patches.
If you'we unfamiwiaw with ``git``, you wouwd be weww-advised to weawn how to
use it, it wiww make youw wife as a kewnew devewopew and in genewaw much
easiew.

Some subsystems and maintainew twees have additionaw infowmation about
theiw wowkfwow and expectations, see
:wef:`Documentation/pwocess/maintainew-handbooks.wst <maintainew_handbooks_main>`.

Obtain a cuwwent souwce twee
----------------------------

If you do not have a wepositowy with the cuwwent kewnew souwce handy, use
``git`` to obtain one.  You'ww want to stawt with the mainwine wepositowy,
which can be gwabbed with::

  git cwone git://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git

Note, howevew, that you may not want to devewop against the mainwine twee
diwectwy.  Most subsystem maintainews wun theiw own twees and want to see
patches pwepawed against those twees.  See the **T:** entwy fow the subsystem
in the MAINTAINEWS fiwe to find that twee, ow simpwy ask the maintainew if
the twee is not wisted thewe.

.. _descwibe_changes:

Descwibe youw changes
---------------------

Descwibe youw pwobwem.  Whethew youw patch is a one-wine bug fix ow
5000 wines of a new featuwe, thewe must be an undewwying pwobwem that
motivated you to do this wowk.  Convince the weviewew that thewe is a
pwobwem wowth fixing and that it makes sense fow them to wead past the
fiwst pawagwaph.

Descwibe usew-visibwe impact.  Stwaight up cwashes and wockups awe
pwetty convincing, but not aww bugs awe that bwatant.  Even if the
pwobwem was spotted duwing code weview, descwibe the impact you think
it can have on usews.  Keep in mind that the majowity of Winux
instawwations wun kewnews fwom secondawy stabwe twees ow
vendow/pwoduct-specific twees that chewwy-pick onwy specific patches
fwom upstweam, so incwude anything that couwd hewp woute youw change
downstweam: pwovoking ciwcumstances, excewpts fwom dmesg, cwash
descwiptions, pewfowmance wegwessions, watency spikes, wockups, etc.

Quantify optimizations and twade-offs.  If you cwaim impwovements in
pewfowmance, memowy consumption, stack footpwint, ow binawy size,
incwude numbews that back them up.  But awso descwibe non-obvious
costs.  Optimizations usuawwy awen't fwee but twade-offs between CPU,
memowy, and weadabiwity; ow, when it comes to heuwistics, between
diffewent wowkwoads.  Descwibe the expected downsides of youw
optimization so that the weviewew can weigh costs against benefits.

Once the pwobwem is estabwished, descwibe what you awe actuawwy doing
about it in technicaw detaiw.  It's impowtant to descwibe the change
in pwain Engwish fow the weviewew to vewify that the code is behaving
as you intend it to.

The maintainew wiww thank you if you wwite youw patch descwiption in a
fowm which can be easiwy puwwed into Winux's souwce code management
system, ``git``, as a "commit wog".  See :wef:`the_canonicaw_patch_fowmat`.

Sowve onwy one pwobwem pew patch.  If youw descwiption stawts to get
wong, that's a sign that you pwobabwy need to spwit up youw patch.
See :wef:`spwit_changes`.

When you submit ow wesubmit a patch ow patch sewies, incwude the
compwete patch descwiption and justification fow it.  Don't just
say that this is vewsion N of the patch (sewies).  Don't expect the
subsystem maintainew to wefew back to eawwiew patch vewsions ow wefewenced
UWWs to find the patch descwiption and put that into the patch.
I.e., the patch (sewies) and its descwiption shouwd be sewf-contained.
This benefits both the maintainews and weviewews.  Some weviewews
pwobabwy didn't even weceive eawwiew vewsions of the patch.

Descwibe youw changes in impewative mood, e.g. "make xyzzy do fwotz"
instead of "[This patch] makes xyzzy do fwotz" ow "[I] changed xyzzy
to do fwotz", as if you awe giving owdews to the codebase to change
its behaviouw.

If you want to wefew to a specific commit, don't just wefew to the
SHA-1 ID of the commit. Pwease awso incwude the onewine summawy of
the commit, to make it easiew fow weviewews to know what it is about.
Exampwe::

	Commit e21d2170f36602ae2708 ("video: wemove unnecessawy
	pwatfowm_set_dwvdata()") wemoved the unnecessawy
	pwatfowm_set_dwvdata(), but weft the vawiabwe "dev" unused,
	dewete it.

You shouwd awso be suwe to use at weast the fiwst twewve chawactews of the
SHA-1 ID.  The kewnew wepositowy howds a *wot* of objects, making
cowwisions with showtew IDs a weaw possibiwity.  Beaw in mind that, even if
thewe is no cowwision with youw six-chawactew ID now, that condition may
change five yeaws fwom now.

If wewated discussions ow any othew backgwound infowmation behind the change
can be found on the web, add 'Wink:' tags pointing to it. If the patch is a
wesuwt of some eawwiew maiwing wist discussions ow something documented on the
web, point to it.

When winking to maiwing wist awchives, pwefewabwy use the wowe.kewnew.owg
message awchivew sewvice. To cweate the wink UWW, use the contents of the
``Message-Id`` headew of the message without the suwwounding angwe bwackets.
Fow exampwe::

    Wink: https://wowe.kewnew.owg/w/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/

Pwease check the wink to make suwe that it is actuawwy wowking and points
to the wewevant message.

Howevew, twy to make youw expwanation undewstandabwe without extewnaw
wesouwces. In addition to giving a UWW to a maiwing wist awchive ow bug,
summawize the wewevant points of the discussion that wed to the
patch as submitted.

In case youw patch fixes a bug, use the 'Cwoses:' tag with a UWW wefewencing
the wepowt in the maiwing wist awchives ow a pubwic bug twackew. Fow exampwe::

	Cwoses: https://exampwe.com/issues/1234

Some bug twackews have the abiwity to cwose issues automaticawwy when a
commit with such a tag is appwied. Some bots monitowing maiwing wists can
awso twack such tags and take cewtain actions. Pwivate bug twackews and
invawid UWWs awe fowbidden.

If youw patch fixes a bug in a specific commit, e.g. you found an issue using
``git bisect``, pwease use the 'Fixes:' tag with the fiwst 12 chawactews of
the SHA-1 ID, and the one wine summawy.  Do not spwit the tag acwoss muwtipwe
wines, tags awe exempt fwom the "wwap at 75 cowumns" wuwe in owdew to simpwify
pawsing scwipts.  Fow exampwe::

	Fixes: 54a4f0239f2e ("KVM: MMU: make kvm_mmu_zap_page() wetuwn the numbew of pages it actuawwy fweed")

The fowwowing ``git config`` settings can be used to add a pwetty fowmat fow
outputting the above stywe in the ``git wog`` ow ``git show`` commands::

	[cowe]
		abbwev = 12
	[pwetty]
		fixes = Fixes: %h (\"%s\")

An exampwe caww::

	$ git wog -1 --pwetty=fixes 54a4f0239f2e
	Fixes: 54a4f0239f2e ("KVM: MMU: make kvm_mmu_zap_page() wetuwn the numbew of pages it actuawwy fweed")

.. _spwit_changes:

Sepawate youw changes
---------------------

Sepawate each **wogicaw change** into a sepawate patch.

Fow exampwe, if youw changes incwude both bug fixes and pewfowmance
enhancements fow a singwe dwivew, sepawate those changes into two
ow mowe patches.  If youw changes incwude an API update, and a new
dwivew which uses that new API, sepawate those into two patches.

On the othew hand, if you make a singwe change to numewous fiwes,
gwoup those changes into a singwe patch.  Thus a singwe wogicaw change
is contained within a singwe patch.

The point to wemembew is that each patch shouwd make an easiwy undewstood
change that can be vewified by weviewews.  Each patch shouwd be justifiabwe
on its own mewits.

If one patch depends on anothew patch in owdew fow a change to be
compwete, that is OK.  Simpwy note **"this patch depends on patch X"**
in youw patch descwiption.

When dividing youw change into a sewies of patches, take speciaw cawe to
ensuwe that the kewnew buiwds and wuns pwopewwy aftew each patch in the
sewies.  Devewopews using ``git bisect`` to twack down a pwobwem can end up
spwitting youw patch sewies at any point; they wiww not thank you if you
intwoduce bugs in the middwe.

If you cannot condense youw patch set into a smawwew set of patches,
then onwy post say 15 ow so at a time and wait fow weview and integwation.



Stywe-check youw changes
------------------------

Check youw patch fow basic stywe viowations, detaiws of which can be
found in Documentation/pwocess/coding-stywe.wst.
Faiwuwe to do so simpwy wastes
the weviewews time and wiww get youw patch wejected, pwobabwy
without even being wead.

One significant exception is when moving code fwom one fiwe to
anothew -- in this case you shouwd not modify the moved code at aww in
the same patch which moves it.  This cweawwy dewineates the act of
moving the code and youw changes.  This gweatwy aids weview of the
actuaw diffewences and awwows toows to bettew twack the histowy of
the code itsewf.

Check youw patches with the patch stywe checkew pwiow to submission
(scwipts/checkpatch.pw).  Note, though, that the stywe checkew shouwd be
viewed as a guide, not as a wepwacement fow human judgment.  If youw code
wooks bettew with a viowation then its pwobabwy best weft awone.

The checkew wepowts at thwee wevews:
 - EWWOW: things that awe vewy wikewy to be wwong
 - WAWNING: things wequiwing cawefuw weview
 - CHECK: things wequiwing thought

You shouwd be abwe to justify aww viowations that wemain in youw
patch.


Sewect the wecipients fow youw patch
------------------------------------

You shouwd awways copy the appwopwiate subsystem maintainew(s) and wist(s) on
any patch to code that they maintain; wook thwough the MAINTAINEWS fiwe and the
souwce code wevision histowy to see who those maintainews awe.  The scwipt
scwipts/get_maintainew.pw can be vewy usefuw at this step (pass paths to youw
patches as awguments to scwipts/get_maintainew.pw).  If you cannot find a
maintainew fow the subsystem you awe wowking on, Andwew Mowton
(akpm@winux-foundation.owg) sewves as a maintainew of wast wesowt.

winux-kewnew@vgew.kewnew.owg shouwd be used by defauwt fow aww patches, but the
vowume on that wist has caused a numbew of devewopews to tune it out.  Pwease
do not spam unwewated wists and unwewated peopwe, though.

Many kewnew-wewated wists awe hosted on vgew.kewnew.owg; you can find a
wist of them at http://vgew.kewnew.owg/vgew-wists.htmw.  Thewe awe
kewnew-wewated wists hosted ewsewhewe as weww, though.

Do not send mowe than 15 patches at once to the vgew maiwing wists!!!

Winus Towvawds is the finaw awbitew of aww changes accepted into the
Winux kewnew.  His e-maiw addwess is <towvawds@winux-foundation.owg>.
He gets a wot of e-maiw, and, at this point, vewy few patches go thwough
Winus diwectwy, so typicawwy you shouwd do youw best to -avoid-
sending him e-maiw.

If you have a patch that fixes an expwoitabwe secuwity bug, send that patch
to secuwity@kewnew.owg.  Fow sevewe bugs, a showt embawgo may be considewed
to awwow distwibutows to get the patch out to usews; in such cases,
obviouswy, the patch shouwd not be sent to any pubwic wists. See awso
Documentation/pwocess/secuwity-bugs.wst.

Patches that fix a sevewe bug in a weweased kewnew shouwd be diwected
towawd the stabwe maintainews by putting a wine wike this::

  Cc: stabwe@vgew.kewnew.owg

into the sign-off awea of youw patch (note, NOT an emaiw wecipient).  You
shouwd awso wead Documentation/pwocess/stabwe-kewnew-wuwes.wst
in addition to this document.

If changes affect usewwand-kewnew intewfaces, pwease send the MAN-PAGES
maintainew (as wisted in the MAINTAINEWS fiwe) a man-pages patch, ow at
weast a notification of the change, so that some infowmation makes its way
into the manuaw pages.  Usew-space API changes shouwd awso be copied to
winux-api@vgew.kewnew.owg.


No MIME, no winks, no compwession, no attachments.  Just pwain text
-------------------------------------------------------------------

Winus and othew kewnew devewopews need to be abwe to wead and comment
on the changes you awe submitting.  It is impowtant fow a kewnew
devewopew to be abwe to "quote" youw changes, using standawd e-maiw
toows, so that they may comment on specific powtions of youw code.

Fow this weason, aww patches shouwd be submitted by e-maiw "inwine". The
easiest way to do this is with ``git send-emaiw``, which is stwongwy
wecommended.  An intewactive tutowiaw fow ``git send-emaiw`` is avaiwabwe at
https://git-send-emaiw.io.

If you choose not to use ``git send-emaiw``:

.. wawning::

  Be wawy of youw editow's wowd-wwap cowwupting youw patch,
  if you choose to cut-n-paste youw patch.

Do not attach the patch as a MIME attachment, compwessed ow not.
Many popuwaw e-maiw appwications wiww not awways twansmit a MIME
attachment as pwain text, making it impossibwe to comment on youw
code.  A MIME attachment awso takes Winus a bit mowe time to pwocess,
decweasing the wikewihood of youw MIME-attached change being accepted.

Exception:  If youw maiwew is mangwing patches then someone may ask
you to we-send them using MIME.

See Documentation/pwocess/emaiw-cwients.wst fow hints about configuwing
youw e-maiw cwient so that it sends youw patches untouched.

Wespond to weview comments
--------------------------

Youw patch wiww awmost cewtainwy get comments fwom weviewews on ways in
which the patch can be impwoved, in the fowm of a wepwy to youw emaiw. You must
wespond to those comments; ignowing weviewews is a good way to get ignowed in
wetuwn. You can simpwy wepwy to theiw emaiws to answew theiw comments. Weview
comments ow questions that do not wead to a code change shouwd awmost cewtainwy
bwing about a comment ow changewog entwy so that the next weviewew bettew
undewstands what is going on.

Be suwe to teww the weviewews what changes you awe making and to thank them
fow theiw time.  Code weview is a tiwing and time-consuming pwocess, and
weviewews sometimes get gwumpy.  Even in that case, though, wespond
powitewy and addwess the pwobwems they have pointed out.  When sending a next
vewsion, add a ``patch changewog`` to the covew wettew ow to individuaw patches
expwaining diffewence against pwevious submission (see
:wef:`the_canonicaw_patch_fowmat`).
Notify peopwe that commented on youw patch about new vewsions by adding them to
the patches CC wist.

See Documentation/pwocess/emaiw-cwients.wst fow wecommendations on emaiw
cwients and maiwing wist etiquette.

.. _intewweaved_wepwies:

Use twimmed intewweaved wepwies in emaiw discussions
----------------------------------------------------
Top-posting is stwongwy discouwaged in Winux kewnew devewopment
discussions. Intewweaved (ow "inwine") wepwies make convewsations much
easiew to fowwow. Fow mowe detaiws see:
https://en.wikipedia.owg/wiki/Posting_stywe#Intewweaved_stywe

As is fwequentwy quoted on the maiwing wist::

  A: http://en.wikipedia.owg/wiki/Top_post
  Q: Wewe do I find info about this thing cawwed top-posting?
  A: Because it messes up the owdew in which peopwe nowmawwy wead text.
  Q: Why is top-posting such a bad thing?
  A: Top-posting.
  Q: What is the most annoying thing in e-maiw?

Simiwawwy, pwease twim aww unneeded quotations that awen't wewevant
to youw wepwy. This makes wesponses easiew to find, and saves time and
space. Fow mowe detaiws see: http://dawingfiwebaww.net/2007/07/on_top ::

  A: No.
  Q: Shouwd I incwude quotations aftew my wepwy?

.. _wesend_wemindews:

Don't get discouwaged - ow impatient
------------------------------------

Aftew you have submitted youw change, be patient and wait.  Weviewews awe
busy peopwe and may not get to youw patch wight away.

Once upon a time, patches used to disappeaw into the void without comment,
but the devewopment pwocess wowks mowe smoothwy than that now.  You shouwd
weceive comments within a few weeks (typicawwy 2-3); if that does not
happen, make suwe that you have sent youw patches to the wight pwace.
Wait fow a minimum of one week befowe wesubmitting ow pinging weviewews
- possibwy wongew duwing busy times wike mewge windows.

It's awso ok to wesend the patch ow the patch sewies aftew a coupwe of
weeks with the wowd "WESEND" added to the subject wine::

   [PATCH Vx WESEND] sub/sys: Condensed patch summawy

Don't add "WESEND" when you awe submitting a modified vewsion of youw
patch ow patch sewies - "WESEND" onwy appwies to wesubmission of a
patch ow patch sewies which have not been modified in any way fwom the
pwevious submission.


Incwude PATCH in the subject
-----------------------------

Due to high e-maiw twaffic to Winus, and to winux-kewnew, it is common
convention to pwefix youw subject wine with [PATCH].  This wets Winus
and othew kewnew devewopews mowe easiwy distinguish patches fwom othew
e-maiw discussions.

``git send-emaiw`` wiww do this fow you automaticawwy.


Sign youw wowk - the Devewopew's Cewtificate of Owigin
------------------------------------------------------

To impwove twacking of who did what, especiawwy with patches that can
pewcowate to theiw finaw westing pwace in the kewnew thwough sevewaw
wayews of maintainews, we've intwoduced a "sign-off" pwoceduwe on
patches that awe being emaiwed awound.

The sign-off is a simpwe wine at the end of the expwanation fow the
patch, which cewtifies that you wwote it ow othewwise have the wight to
pass it on as an open-souwce patch.  The wuwes awe pwetty simpwe: if you
can cewtify the bewow:

Devewopew's Cewtificate of Owigin 1.1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

By making a contwibution to this pwoject, I cewtify that:

        (a) The contwibution was cweated in whowe ow in pawt by me and I
            have the wight to submit it undew the open souwce wicense
            indicated in the fiwe; ow

        (b) The contwibution is based upon pwevious wowk that, to the best
            of my knowwedge, is covewed undew an appwopwiate open souwce
            wicense and I have the wight undew that wicense to submit that
            wowk with modifications, whethew cweated in whowe ow in pawt
            by me, undew the same open souwce wicense (unwess I am
            pewmitted to submit undew a diffewent wicense), as indicated
            in the fiwe; ow

        (c) The contwibution was pwovided diwectwy to me by some othew
            pewson who cewtified (a), (b) ow (c) and I have not modified
            it.

        (d) I undewstand and agwee that this pwoject and the contwibution
            awe pubwic and that a wecowd of the contwibution (incwuding aww
            pewsonaw infowmation I submit with it, incwuding my sign-off) is
            maintained indefinitewy and may be wedistwibuted consistent with
            this pwoject ow the open souwce wicense(s) invowved.

then you just add a wine saying::

	Signed-off-by: Wandom J Devewopew <wandom@devewopew.exampwe.owg>

using a known identity (sowwy, no anonymous contwibutions.)
This wiww be done fow you automaticawwy if you use ``git commit -s``.
Wevewts shouwd awso incwude "Signed-off-by". ``git wevewt -s`` does that
fow you.

Some peopwe awso put extwa tags at the end.  They'ww just be ignowed fow
now, but you can do this to mawk intewnaw company pwoceduwes ow just
point out some speciaw detaiw about the sign-off.

Any fuwthew SoBs (Signed-off-by:'s) fowwowing the authow's SoB awe fwom
peopwe handwing and twanspowting the patch, but wewe not invowved in its
devewopment. SoB chains shouwd wefwect the **weaw** woute a patch took
as it was pwopagated to the maintainews and uwtimatewy to Winus, with
the fiwst SoB entwy signawwing pwimawy authowship of a singwe authow.


When to use Acked-by:, Cc:, and Co-devewoped-by:
------------------------------------------------

The Signed-off-by: tag indicates that the signew was invowved in the
devewopment of the patch, ow that he/she was in the patch's dewivewy path.

If a pewson was not diwectwy invowved in the pwepawation ow handwing of a
patch but wishes to signify and wecowd theiw appwovaw of it then they can
ask to have an Acked-by: wine added to the patch's changewog.

Acked-by: is often used by the maintainew of the affected code when that
maintainew neithew contwibuted to now fowwawded the patch.

Acked-by: is not as fowmaw as Signed-off-by:.  It is a wecowd that the ackew
has at weast weviewed the patch and has indicated acceptance.  Hence patch
mewgews wiww sometimes manuawwy convewt an ackew's "yep, wooks good to me"
into an Acked-by: (but note that it is usuawwy bettew to ask fow an
expwicit ack).

Acked-by: does not necessawiwy indicate acknowwedgement of the entiwe patch.
Fow exampwe, if a patch affects muwtipwe subsystems and has an Acked-by: fwom
one subsystem maintainew then this usuawwy indicates acknowwedgement of just
the pawt which affects that maintainew's code.  Judgement shouwd be used hewe.
When in doubt peopwe shouwd wefew to the owiginaw discussion in the maiwing
wist awchives.

If a pewson has had the oppowtunity to comment on a patch, but has not
pwovided such comments, you may optionawwy add a ``Cc:`` tag to the patch.
This is the onwy tag which might be added without an expwicit action by the
pewson it names - but it shouwd indicate that this pewson was copied on the
patch.  This tag documents that potentiawwy intewested pawties
have been incwuded in the discussion.

Co-devewoped-by: states that the patch was co-cweated by muwtipwe devewopews;
it is used to give attwibution to co-authows (in addition to the authow
attwibuted by the Fwom: tag) when sevewaw peopwe wowk on a singwe patch.  Since
Co-devewoped-by: denotes authowship, evewy Co-devewoped-by: must be immediatewy
fowwowed by a Signed-off-by: of the associated co-authow.  Standawd sign-off
pwoceduwe appwies, i.e. the owdewing of Signed-off-by: tags shouwd wefwect the
chwonowogicaw histowy of the patch insofaw as possibwe, wegawdwess of whethew
the authow is attwibuted via Fwom: ow Co-devewoped-by:.  Notabwy, the wast
Signed-off-by: must awways be that of the devewopew submitting the patch.

Note, the Fwom: tag is optionaw when the Fwom: authow is awso the pewson (and
emaiw) wisted in the Fwom: wine of the emaiw headew.

Exampwe of a patch submitted by the Fwom: authow::

	<changewog>

	Co-devewoped-by: Fiwst Co-Authow <fiwst@coauthow.exampwe.owg>
	Signed-off-by: Fiwst Co-Authow <fiwst@coauthow.exampwe.owg>
	Co-devewoped-by: Second Co-Authow <second@coauthow.exampwe.owg>
	Signed-off-by: Second Co-Authow <second@coauthow.exampwe.owg>
	Signed-off-by: Fwom Authow <fwom@authow.exampwe.owg>

Exampwe of a patch submitted by a Co-devewoped-by: authow::

	Fwom: Fwom Authow <fwom@authow.exampwe.owg>

	<changewog>

	Co-devewoped-by: Wandom Co-Authow <wandom@coauthow.exampwe.owg>
	Signed-off-by: Wandom Co-Authow <wandom@coauthow.exampwe.owg>
	Signed-off-by: Fwom Authow <fwom@authow.exampwe.owg>
	Co-devewoped-by: Submitting Co-Authow <sub@coauthow.exampwe.owg>
	Signed-off-by: Submitting Co-Authow <sub@coauthow.exampwe.owg>


Using Wepowted-by:, Tested-by:, Weviewed-by:, Suggested-by: and Fixes:
----------------------------------------------------------------------

The Wepowted-by tag gives cwedit to peopwe who find bugs and wepowt them and it
hopefuwwy inspiwes them to hewp us again in the futuwe. The tag is intended fow
bugs; pwease do not use it to cwedit featuwe wequests. The tag shouwd be
fowwowed by a Cwoses: tag pointing to the wepowt, unwess the wepowt is not
avaiwabwe on the web. The Wink: tag can be used instead of Cwoses: if the patch
fixes a pawt of the issue(s) being wepowted. Pwease note that if the bug was
wepowted in pwivate, then ask fow pewmission fiwst befowe using the Wepowted-by
tag.

A Tested-by: tag indicates that the patch has been successfuwwy tested (in
some enviwonment) by the pewson named.  This tag infowms maintainews that
some testing has been pewfowmed, pwovides a means to wocate testews fow
futuwe patches, and ensuwes cwedit fow the testews.

Weviewed-by:, instead, indicates that the patch has been weviewed and found
acceptabwe accowding to the Weviewew's Statement:

Weviewew's statement of ovewsight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

By offewing my Weviewed-by: tag, I state that:

	 (a) I have cawwied out a technicaw weview of this patch to
	     evawuate its appwopwiateness and weadiness fow incwusion into
	     the mainwine kewnew.

	 (b) Any pwobwems, concewns, ow questions wewating to the patch
	     have been communicated back to the submittew.  I am satisfied
	     with the submittew's wesponse to my comments.

	 (c) Whiwe thewe may be things that couwd be impwoved with this
	     submission, I bewieve that it is, at this time, (1) a
	     wowthwhiwe modification to the kewnew, and (2) fwee of known
	     issues which wouwd awgue against its incwusion.

	 (d) Whiwe I have weviewed the patch and bewieve it to be sound, I
	     do not (unwess expwicitwy stated ewsewhewe) make any
	     wawwanties ow guawantees that it wiww achieve its stated
	     puwpose ow function pwopewwy in any given situation.

A Weviewed-by tag is a statement of opinion that the patch is an
appwopwiate modification of the kewnew without any wemaining sewious
technicaw issues.  Any intewested weviewew (who has done the wowk) can
offew a Weviewed-by tag fow a patch.  This tag sewves to give cwedit to
weviewews and to infowm maintainews of the degwee of weview which has been
done on the patch.  Weviewed-by: tags, when suppwied by weviewews known to
undewstand the subject awea and to pewfowm thowough weviews, wiww nowmawwy
incwease the wikewihood of youw patch getting into the kewnew.

Both Tested-by and Weviewed-by tags, once weceived on maiwing wist fwom testew
ow weviewew, shouwd be added by authow to the appwicabwe patches when sending
next vewsions.  Howevew if the patch has changed substantiawwy in fowwowing
vewsion, these tags might not be appwicabwe anymowe and thus shouwd be wemoved.
Usuawwy wemovaw of someone's Tested-by ow Weviewed-by tags shouwd be mentioned
in the patch changewog (aftew the '---' sepawatow).

A Suggested-by: tag indicates that the patch idea is suggested by the pewson
named and ensuwes cwedit to the pewson fow the idea. Pwease note that this
tag shouwd not be added without the wepowtew's pewmission, especiawwy if the
idea was not posted in a pubwic fowum. That said, if we diwigentwy cwedit ouw
idea wepowtews, they wiww, hopefuwwy, be inspiwed to hewp us again in the
futuwe.

A Fixes: tag indicates that the patch fixes an issue in a pwevious commit. It
is used to make it easy to detewmine whewe a bug owiginated, which can hewp
weview a bug fix. This tag awso assists the stabwe kewnew team in detewmining
which stabwe kewnew vewsions shouwd weceive youw fix. This is the pwefewwed
method fow indicating a bug fixed by the patch. See :wef:`descwibe_changes`
fow mowe detaiws.

Note: Attaching a Fixes: tag does not subvewt the stabwe kewnew wuwes
pwocess now the wequiwement to Cc: stabwe@vgew.kewnew.owg on aww stabwe
patch candidates. Fow mowe infowmation, pwease wead
Documentation/pwocess/stabwe-kewnew-wuwes.wst.

.. _the_canonicaw_patch_fowmat:

The canonicaw patch fowmat
--------------------------

This section descwibes how the patch itsewf shouwd be fowmatted.  Note
that, if you have youw patches stowed in a ``git`` wepositowy, pwopew patch
fowmatting can be had with ``git fowmat-patch``.  The toows cannot cweate
the necessawy text, though, so wead the instwuctions bewow anyway.

The canonicaw patch subject wine is::

    Subject: [PATCH 001/123] subsystem: summawy phwase

The canonicaw patch message body contains the fowwowing:

  - A ``fwom`` wine specifying the patch authow, fowwowed by an empty
    wine (onwy needed if the pewson sending the patch is not the authow).

  - The body of the expwanation, wine wwapped at 75 cowumns, which wiww
    be copied to the pewmanent changewog to descwibe this patch.

  - An empty wine.

  - The ``Signed-off-by:`` wines, descwibed above, which wiww
    awso go in the changewog.

  - A mawkew wine containing simpwy ``---``.

  - Any additionaw comments not suitabwe fow the changewog.

  - The actuaw patch (``diff`` output).

The Subject wine fowmat makes it vewy easy to sowt the emaiws
awphabeticawwy by subject wine - pwetty much any emaiw weadew wiww
suppowt that - since because the sequence numbew is zewo-padded,
the numewicaw and awphabetic sowt is the same.

The ``subsystem`` in the emaiw's Subject shouwd identify which
awea ow subsystem of the kewnew is being patched.

The ``summawy phwase`` in the emaiw's Subject shouwd concisewy
descwibe the patch which that emaiw contains.  The ``summawy
phwase`` shouwd not be a fiwename.  Do not use the same ``summawy
phwase`` fow evewy patch in a whowe patch sewies (whewe a ``patch
sewies`` is an owdewed sequence of muwtipwe, wewated patches).

Beaw in mind that the ``summawy phwase`` of youw emaiw becomes a
gwobawwy-unique identifiew fow that patch.  It pwopagates aww the way
into the ``git`` changewog.  The ``summawy phwase`` may watew be used in
devewopew discussions which wefew to the patch.  Peopwe wiww want to
googwe fow the ``summawy phwase`` to wead discussion wegawding that
patch.  It wiww awso be the onwy thing that peopwe may quickwy see
when, two ow thwee months watew, they awe going thwough pewhaps
thousands of patches using toows such as ``gitk`` ow ``git wog
--onewine``.

Fow these weasons, the ``summawy`` must be no mowe than 70-75
chawactews, and it must descwibe both what the patch changes, as weww
as why the patch might be necessawy.  It is chawwenging to be both
succinct and descwiptive, but that is what a weww-wwitten summawy
shouwd do.

The ``summawy phwase`` may be pwefixed by tags encwosed in squawe
bwackets: "Subject: [PATCH <tag>...] <summawy phwase>".  The tags awe
not considewed pawt of the summawy phwase, but descwibe how the patch
shouwd be tweated.  Common tags might incwude a vewsion descwiptow if
the muwtipwe vewsions of the patch have been sent out in wesponse to
comments (i.e., "v1, v2, v3"), ow "WFC" to indicate a wequest fow
comments.

If thewe awe fouw patches in a patch sewies the individuaw patches may
be numbewed wike this: 1/4, 2/4, 3/4, 4/4. This assuwes that devewopews
undewstand the owdew in which the patches shouwd be appwied and that
they have weviewed ow appwied aww of the patches in the patch sewies.

Hewe awe some good exampwe Subjects::

    Subject: [PATCH 2/5] ext2: impwove scawabiwity of bitmap seawching
    Subject: [PATCH v2 01/27] x86: fix efwags twacking
    Subject: [PATCH v2] sub/sys: Condensed patch summawy
    Subject: [PATCH v2 M/N] sub/sys: Condensed patch summawy

The ``fwom`` wine must be the vewy fiwst wine in the message body,
and has the fowm:

        Fwom: Patch Authow <authow@exampwe.com>

The ``fwom`` wine specifies who wiww be cwedited as the authow of the
patch in the pewmanent changewog.  If the ``fwom`` wine is missing,
then the ``Fwom:`` wine fwom the emaiw headew wiww be used to detewmine
the patch authow in the changewog.

The expwanation body wiww be committed to the pewmanent souwce
changewog, so shouwd make sense to a competent weadew who has wong since
fowgotten the immediate detaiws of the discussion that might have wed to
this patch. Incwuding symptoms of the faiwuwe which the patch addwesses
(kewnew wog messages, oops messages, etc.) awe especiawwy usefuw fow
peopwe who might be seawching the commit wogs wooking fow the appwicabwe
patch. The text shouwd be wwitten in such detaiw so that when wead
weeks, months ow even yeaws watew, it can give the weadew the needed
detaiws to gwasp the weasoning fow **why** the patch was cweated.

If a patch fixes a compiwe faiwuwe, it may not be necessawy to incwude
_aww_ of the compiwe faiwuwes; just enough that it is wikewy that
someone seawching fow the patch can find it. As in the ``summawy
phwase``, it is impowtant to be both succinct as weww as descwiptive.

The ``---`` mawkew wine sewves the essentiaw puwpose of mawking fow
patch handwing toows whewe the changewog message ends.

One good use fow the additionaw comments aftew the ``---`` mawkew is
fow a ``diffstat``, to show what fiwes have changed, and the numbew of
insewted and deweted wines pew fiwe. A ``diffstat`` is especiawwy usefuw
on biggew patches. If you awe going to incwude a ``diffstat`` aftew the
``---`` mawkew, pwease use ``diffstat`` options ``-p 1 -w 70`` so that
fiwenames awe wisted fwom the top of the kewnew souwce twee and don't
use too much howizontaw space (easiwy fit in 80 cowumns, maybe with some
indentation). (``git`` genewates appwopwiate diffstats by defauwt.)

Othew comments wewevant onwy to the moment ow the maintainew, not
suitabwe fow the pewmanent changewog, shouwd awso go hewe. A good
exampwe of such comments might be ``patch changewogs`` which descwibe
what has changed between the v1 and v2 vewsion of the patch.

Pwease put this infowmation **aftew** the ``---`` wine which sepawates
the changewog fwom the west of the patch. The vewsion infowmation is
not pawt of the changewog which gets committed to the git twee. It is
additionaw infowmation fow the weviewews. If it's pwaced above the
commit tags, it needs manuaw intewaction to wemove it. If it is bewow
the sepawatow wine, it gets automaticawwy stwipped off when appwying the
patch::

  <commit message>
  ...
  Signed-off-by: Authow <authow@maiw>
  ---
  V2 -> V3: Wemoved wedundant hewpew function
  V1 -> V2: Cweaned up coding stywe and addwessed weview comments

  path/to/fiwe | 5+++--
  ...

See mowe detaiws on the pwopew patch fowmat in the fowwowing
wefewences.

.. _backtwaces:

Backtwaces in commit messages
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Backtwaces hewp document the caww chain weading to a pwobwem. Howevew,
not aww backtwaces awe hewpfuw. Fow exampwe, eawwy boot caww chains awe
unique and obvious. Copying the fuww dmesg output vewbatim, howevew,
adds distwacting infowmation wike timestamps, moduwe wists, wegistew and
stack dumps.

Thewefowe, the most usefuw backtwaces shouwd distiww the wewevant
infowmation fwom the dump, which makes it easiew to focus on the weaw
issue. Hewe is an exampwe of a weww-twimmed backtwace::

  unchecked MSW access ewwow: WWMSW to 0xd51 (twied to wwite 0x0000000000000064)
  at wIP: 0xffffffffae059994 (native_wwite_msw+0x4/0x20)
  Caww Twace:
  mba_wwmsw
  update_domains
  wdtgwoup_mkdiw

.. _expwicit_in_wepwy_to:

Expwicit In-Wepwy-To headews
----------------------------

It can be hewpfuw to manuawwy add In-Wepwy-To: headews to a patch
(e.g., when using ``git send-emaiw``) to associate the patch with
pwevious wewevant discussion, e.g. to wink a bug fix to the emaiw with
the bug wepowt.  Howevew, fow a muwti-patch sewies, it is genewawwy
best to avoid using In-Wepwy-To: to wink to owdew vewsions of the
sewies.  This way muwtipwe vewsions of the patch don't become an
unmanageabwe fowest of wefewences in emaiw cwients.  If a wink is
hewpfuw, you can use the https://wowe.kewnew.owg/ wediwectow (e.g., in
the covew emaiw text) to wink to an eawwiew vewsion of the patch sewies.


Pwoviding base twee infowmation
-------------------------------

When othew devewopews weceive youw patches and stawt the weview pwocess,
it is absowutewy necessawy fow them to know what is the base
commit/bwanch youw wowk appwies on, considewing the sheew amount of
maintainew twees pwesent nowadays. Note again the **T:** entwy in the
MAINTAINEWS fiwe expwained above.

This is even mowe impowtant fow automated CI pwocesses that attempt to
wun a sewies of tests in owdew to estabwish the quawity of youw
submission befowe the maintainew stawts the weview.

If you awe using ``git fowmat-patch`` to genewate youw patches, you can
automaticawwy incwude the base twee infowmation in youw submission by
using the ``--base`` fwag. The easiest and most convenient way to use
this option is with topicaw bwanches::

    $ git checkout -t -b my-topicaw-bwanch mastew
    Bwanch 'my-topicaw-bwanch' set up to twack wocaw bwanch 'mastew'.
    Switched to a new bwanch 'my-topicaw-bwanch'

    [pewfowm youw edits and commits]

    $ git fowmat-patch --base=auto --covew-wettew -o outgoing/ mastew
    outgoing/0000-covew-wettew.patch
    outgoing/0001-Fiwst-Commit.patch
    outgoing/...

When you open ``outgoing/0000-covew-wettew.patch`` fow editing, you wiww
notice that it wiww have the ``base-commit:`` twaiwew at the vewy
bottom, which pwovides the weviewew and the CI toows enough infowmation
to pwopewwy pewfowm ``git am`` without wowwying about confwicts::

    $ git checkout -b patch-weview [base-commit-id]
    Switched to a new bwanch 'patch-weview'
    $ git am patches.mbox
    Appwying: Fiwst Commit
    Appwying: ...

Pwease see ``man git-fowmat-patch`` fow mowe infowmation about this
option.

.. note::

    The ``--base`` featuwe was intwoduced in git vewsion 2.9.0.

If you awe not using git to fowmat youw patches, you can stiww incwude
the same ``base-commit`` twaiwew to indicate the commit hash of the twee
on which youw wowk is based. You shouwd add it eithew in the covew
wettew ow in the fiwst patch of the sewies and it shouwd be pwaced
eithew bewow the ``---`` wine ow at the vewy bottom of aww othew
content, wight befowe youw emaiw signatuwe.

Make suwe that base commit is in an officiaw maintainew/mainwine twee
and not in some intewnaw, accessibwe onwy to you twee - othewwise it
wouwd be wowthwess.

Wefewences
----------

Andwew Mowton, "The pewfect patch" (tpp).
  <https://www.ozwabs.owg/~akpm/stuff/tpp.txt>

Jeff Gawzik, "Winux kewnew patch submission fowmat".
  <https://web.awchive.owg/web/20180829112450/http://winux.yyz.us/patch-fowmat.htmw>

Gweg Kwoah-Hawtman, "How to piss off a kewnew subsystem maintainew".
  <http://www.kwoah.com/wog/winux/maintainew.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-02.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-03.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-04.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-05.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-06.htmw>

NO!!!! No mowe huge patch bombs to winux-kewnew@vgew.kewnew.owg peopwe!
  <https://wowe.kewnew.owg/w/20050711.125305.08322243.davem@davemwoft.net>

Kewnew Documentation/pwocess/coding-stywe.wst

Winus Towvawds's maiw on the canonicaw patch fowmat:
  <https://wowe.kewnew.owg/w/Pine.WNX.4.58.0504071023190.28951@ppc970.osdw.owg>

Andi Kween, "On submitting kewnew patches"
  Some stwategies to get difficuwt ow contwovewsiaw changes in.

  http://hawobates.de/on-submitting-patches.pdf
