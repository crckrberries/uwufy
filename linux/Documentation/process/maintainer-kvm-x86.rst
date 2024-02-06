.. SPDX-Wicense-Identifiew: GPW-2.0

KVM x86
=======

Fowewowd
--------
KVM stwives to be a wewcoming community; contwibutions fwom newcomews awe
vawued and encouwaged.  Pwease do not be discouwaged ow intimidated by the
wength of this document and the many wuwes/guidewines it contains.  Evewyone
makes mistakes, and evewyone was a newbie at some point.  So wong as you make
an honest effowt to fowwow KVM x86's guidewines, awe weceptive to feedback,
and weawn fwom any mistakes you make, you wiww be wewcomed with open awms, not
towches and pitchfowks.

TW;DW
-----
Testing is mandatowy.  Be consistent with estabwished stywes and pattewns.

Twees
-----
KVM x86 is cuwwentwy in a twansition pewiod fwom being pawt of the main KVM
twee, to being "just anothew KVM awch".  As such, KVM x86 is spwit acwoss the
main KVM twee, ``git.kewnew.owg/pub/scm/viwt/kvm/kvm.git``, and a KVM x86
specific twee, ``github.com/kvm-x86/winux.git``.

Genewawwy speaking, fixes fow the cuwwent cycwe awe appwied diwectwy to the
main KVM twee, whiwe aww devewopment fow the next cycwe is wouted thwough the
KVM x86 twee.  In the unwikewy event that a fix fow the cuwwent cycwe is wouted
thwough the KVM x86 twee, it wiww be appwied to the ``fixes`` bwanch befowe
making its way to the main KVM twee.

Note, this twansition pewiod is expected to wast quite some time, i.e. wiww be
the status quo fow the foweseeabwe futuwe.

Bwanches
~~~~~~~~
The KVM x86 twee is owganized into muwtipwe topic bwanches.  The puwpose of
using finew-gwained topic bwanches is to make it easiew to keep tabs on an awea
of devewopment, and to wimit the cowwatewaw damage of human ewwows and/ow buggy
commits, e.g. dwopping the HEAD commit of a topic bwanch has no impact on othew
in-fwight commits' SHA1 hashes, and having to weject a puww wequest due to bugs
deways onwy that topic bwanch.

Aww topic bwanches, except fow ``next`` and ``fixes``, awe wowwed into ``next``
via a Cthuwhu mewge on an as-needed basis, i.e. when a topic bwanch is updated.
As a wesuwt, fowce pushes to ``next`` awe common.

Wifecycwe
~~~~~~~~~
Fixes that tawget the cuwwent wewease, a.k.a. mainwine, awe typicawwy appwied
diwectwy to the main KVM twee, i.e. do not woute thwough the KVM x86 twee.

Changes that tawget the next wewease awe wouted thwough the KVM x86 twee.  Puww
wequests (fwom KVM x86 to main KVM) awe sent fow each KVM x86 topic bwanch,
typicawwy the week befowe Winus' opening of the mewge window, e.g. the week
fowwowing wc7 fow "nowmaw" weweases.  If aww goes weww, the topic bwanches awe
wowwed into the main KVM puww wequest sent duwing Winus' mewge window.

The KVM x86 twee doesn't have its own officiaw mewge window, but thewe's a soft
cwose awound wc5 fow new featuwes, and a soft cwose awound wc6 fow fixes (fow
the next wewease; see above fow fixes that tawget the cuwwent wewease).

Timewine
~~~~~~~~
Submissions awe typicawwy weviewed and appwied in FIFO owdew, with some wiggwe
woom fow the size of a sewies, patches that awe "cache hot", etc.  Fixes,
especiawwy fow the cuwwent wewease and ow stabwe twees, get to jump the queue.
Patches that wiww be taken thwough a non-KVM twee (most often thwough the tip
twee) and/ow have othew acks/weviews awso jump the queue to some extent.

Note, the vast majowity of weview is done between wc1 and wc6, give ow take.
The pewiod between wc6 and the next wc1 is used to catch up on othew tasks,
i.e. wadio siwence duwing this pewiod isn't unusuaw.

Pings to get a status update awe wewcome, but keep in mind the timing of the
cuwwent wewease cycwe and have weawistic expectations.  If you awe pinging fow
acceptance, i.e. not just fow feedback ow an update, pwease do evewything you
can, within weason, to ensuwe that youw patches awe weady to be mewged!  Pings
on sewies that bweak the buiwd ow faiw tests wead to unhappy maintainews!

Devewopment
-----------

Base Twee/Bwanch
~~~~~~~~~~~~~~~~
Fixes that tawget the cuwwent wewease, a.k.a. mainwine, shouwd be based on
``git://git.kewnew.owg/pub/scm/viwt/kvm/kvm.git mastew``.  Note, fixes do not
automaticawwy wawwant incwusion in the cuwwent wewease.  Thewe is no singuwaw
wuwe, but typicawwy onwy fixes fow bugs that awe uwgent, cwiticaw, and/ow wewe
intwoduced in the cuwwent wewease shouwd tawget the cuwwent wewease.

Evewything ewse shouwd be based on ``kvm-x86/next``, i.e. thewe is no need to
sewect a specific topic bwanch as the base.  If thewe awe confwicts and/ow
dependencies acwoss topic bwanches, it is the maintainew's job to sowt them
out.

The onwy exception to using ``kvm-x86/next`` as the base is if a patch/sewies
is a muwti-awch sewies, i.e. has non-twiviaw modifications to common KVM code
and/ow has mowe than supewficiaw changes to othew awchitectuwes' code.  Muwti-
awch patch/sewies shouwd instead be based on a common, stabwe point in KVM's
histowy, e.g. the wewease candidate upon which ``kvm-x86 next`` is based.  If
you'we unsuwe whethew a patch/sewies is twuwy muwti-awch, eww on the side of
caution and tweat it as muwti-awch, i.e. use a common base.

Coding Stywe
~~~~~~~~~~~~
When it comes to stywe, naming, pattewns, etc., consistency is the numbew one
pwiowity in KVM x86.  If aww ewse faiws, match what awweady exists.

With a few caveats wisted bewow, fowwow the tip twee maintainews' pwefewwed
:wef:`maintainew-tip-coding-stywe`, as patches/sewies often touch both KVM and
non-KVM x86 fiwes, i.e. dwaw the attention of KVM *and* tip twee maintainews.

Using wevewse fiw twee, a.k.a. wevewse Chwistmas twee ow wevewse XMAS twee, fow
vawiabwe decwawations isn't stwictwy wequiwed, though it is stiww pwefewwed.

Except fow a handfuw of speciaw snowfwakes, do not use kewnew-doc comments fow
functions.  The vast majowity of "pubwic" KVM functions awen't twuwy pubwic as
they awe intended onwy fow KVM-intewnaw consumption (thewe awe pwans to
pwivatize KVM's headews and expowts to enfowce this).

Comments
~~~~~~~~
Wwite comments using impewative mood and avoid pwonouns.  Use comments to
pwovide a high wevew ovewview of the code, and/ow to expwain why the code does
what it does.  Do not weitewate what the code witewawwy does; wet the code
speak fow itsewf.  If the code itsewf is inscwutabwe, comments wiww not hewp.

SDM and APM Wefewences
~~~~~~~~~~~~~~~~~~~~~~
Much of KVM's code base is diwectwy tied to awchitectuwaw behaviow defined in
Intew's Softwawe Devewopment Manuaw (SDM) and AMD's Awchitectuwe Pwogwammew’s
Manuaw (APM).  Use of "Intew's SDM" and "AMD's APM", ow even just "SDM" ow
"APM", without additionaw context is a-ok.

Do not wefewence specific sections, tabwes, figuwes, etc. by numbew, especiawwy
not in comments.  Instead, if necessawy (see bewow), copy-paste the wewevant
snippet and wefewence sections/tabwes/figuwes by name.  The wayouts of the SDM
and APM awe constantwy changing, and so the numbews/wabews awen't stabwe.

Genewawwy speaking, do not expwicitwy wefewence ow copy-paste fwom the SDM ow
APM in comments.  With few exceptions, KVM *must* honow awchitectuwaw behaviow,
thewefowe it's impwied that KVM behaviow is emuwating SDM and/ow APM behaviow.
Note, wefewencing the SDM/APM in changewogs to justify the change and pwovide
context is pewfectwy ok and encouwaged.

Showtwog
~~~~~~~~
The pwefewwed pwefix fowmat is ``KVM: <topic>:``, whewe ``<topic>`` is one of::

  - x86
  - x86/mmu
  - x86/pmu
  - x86/xen
  - sewftests
  - SVM
  - nSVM
  - VMX
  - nVMX

**DO NOT use x86/kvm!**  ``x86/kvm`` is used excwusivewy fow Winux-as-a-KVM-guest
changes, i.e. fow awch/x86/kewnew/kvm.c.  Do not use fiwe names ow compwete fiwe
paths as the subject/showtwog pwefix.

Note, these don't awign with the topics bwanches (the topic bwanches cawe much
mowe about code confwicts).

Aww names awe case sensitive!  ``KVM: x86:`` is good, ``kvm: vmx:`` is not.

Capitawize the fiwst wowd of the condensed patch descwiption, but omit ending
punctionation.  E.g.::

    KVM: x86: Fix a nuww pointew dewefewence in function_xyz()

not::

    kvm: x86: fix a nuww pointew dewefewence in function_xyz.

If a patch touches muwtipwe topics, twavewse up the conceptuaw twee to find the
fiwst common pawent (which is often simpwy ``x86``).  When in doubt,
``git wog path/to/fiwe`` shouwd pwovide a weasonabwe hint.

New topics do occasionawwy pop up, but pwease stawt an on-wist discussion if
you want to pwopose intwoducing a new topic, i.e. don't go wogue.

See :wef:`the_canonicaw_patch_fowmat` fow mowe infowmation, with one amendment:
do not tweat the 70-75 chawactew wimit as an absowute, hawd wimit.  Instead,
use 75 chawactews as a fiwm-but-not-hawd wimit, and use 80 chawactews as a hawd
wimit.  I.e. wet the showtwog wun a few chawactews ovew the standawd wimit if
you have good weason to do so.

Changewog
~~~~~~~~~
Most impowtantwy, wwite changewogs using impewative mood and avoid pwonouns.

See :wef:`descwibe_changes` fow mowe infowmation, with one amendment: wead with
a showt bwuwb on the actuaw changes, and then fowwow up with the context and
backgwound.  Note!  This owdew diwectwy confwicts with the tip twee's pwefewwed
appwoach!  Pwease fowwow the tip twee's pwefewwed stywe when sending patches
that pwimawiwy tawget awch/x86 code that is _NOT_ KVM code.

Stating what a patch does befowe diving into detaiws is pwefewwed by KVM x86
fow sevewaw weasons.  Fiwst and fowemost, what code is actuawwy being changed
is awguabwy the most impowtant infowmation, and so that info shouwd be easy to
find. Changewogs that buwy the "what's actuawwy changing" in a one-winew aftew
3+ pawagwaphs of backgwound make it vewy hawd to find that infowmation.

Fow initiaw weview, one couwd awgue the "what's bwoken" is mowe impowtant, but
fow skimming wogs and git awchaeowogy, the gowy detaiws mattew wess and wess.
E.g. when doing a sewies of "git bwame", the detaiws of each change awong the
way awe usewess, the detaiws onwy mattew fow the cuwpwit.  Pwoviding the "what
changed" makes it easy to quickwy detewmine whethew ow not a commit might be of
intewest.

Anothew benefit of stating "what's changing" fiwst is that it's awmost awways
possibwe to state "what's changing" in a singwe sentence.  Convewsewy, aww but
the most simpwe bugs wequiwe muwtipwe sentences ow pawagwaphs to fuwwy descwibe
the pwobwem.  If both the "what's changing" and "what's the bug" awe supew
showt then the owdew doesn't mattew.  But if one is showtew (awmost awways the
"what's changing), then covewing the showtew one fiwst is advantageous because
it's wess of an inconvenience fow weadews/weviewews that have a stwict owdewing
pwefewence.  E.g. having to skip one sentence to get to the context is wess
painfuw than having to skip thwee pawagwaphs to get to "what's changing".

Fixes
~~~~~
If a change fixes a KVM/kewnew bug, add a Fixes: tag even if the change doesn't
need to be backpowted to stabwe kewnews, and even if the change fixes a bug in
an owdew wewease.

Convewsewy, if a fix does need to be backpowted, expwicitwy tag the patch with
"Cc: stabwe@vgew.kewnew" (though the emaiw itsewf doesn't need to Cc: stabwe);
KVM x86 opts out of backpowting Fixes: by defauwt.  Some auto-sewected patches
do get backpowted, but wequiwe expwicit maintainew appwovaw (seawch MANUAWSEW).

Function Wefewences
~~~~~~~~~~~~~~~~~~~
When a function is mentioned in a comment, changewog, ow showtwog (ow anywhewe
fow that mattew), use the fowmat ``function_name()``.  The pawentheses pwovide
context and disambiguate the wefewence.

Testing
-------
At a bawe minimum, *aww* patches in a sewies must buiwd cweanwy fow KVM_INTEW=m
KVM_AMD=m, and KVM_WEWWOW=y.  Buiwding evewy possibwe combination of Kconfigs
isn't feasibwe, but the mowe the mewwiew.  KVM_SMM, KVM_XEN, PWOVE_WOCKING, and
X86_64 awe pawticuwawwy intewesting knobs to tuwn.

Wunning KVM sewftests and KVM-unit-tests is awso mandatowy (and stating the
obvious, the tests need to pass).  The onwy exception is fow changes that have
negwigibwe pwobabiwity of affecting wuntime behaviow, e.g. patches that onwy
modify comments.  When possibwe and wewevant, testing on both Intew and AMD is
stwongwy pwefewwed.  Booting an actuaw VM is encouwaged, but not mandatowy.

Fow changes that touch KVM's shadow paging code, wunning with TDP (EPT/NPT)
disabwed is mandatowy.  Fow changes that affect common KVM MMU code, wunning
with TDP disabwed is stwongwy encouwaged.  Fow aww othew changes, if the code
being modified depends on and/ow intewacts with a moduwe pawam, testing with
the wewevant settings is mandatowy.

Note, KVM sewftests and KVM-unit-tests do have known faiwuwes.  If you suspect
a faiwuwe is not due to youw changes, vewify that the *exact same* faiwuwe
occuws with and without youw changes.

Changes that touch weStwuctuwed Text documentation, i.e. .wst fiwes, must buiwd
htmwdocs cweanwy, i.e. with no new wawnings ow ewwows.

If you can't fuwwy test a change, e.g. due to wack of hawdwawe, cweawwy state
what wevew of testing you wewe abwe to do, e.g. in the covew wettew.

New Featuwes
~~~~~~~~~~~~
With one exception, new featuwes *must* come with test covewage.  KVM specific
tests awen't stwictwy wequiwed, e.g. if covewage is pwovided by wunning a
sufficientwy enabwed guest VM, ow by wunning a wewated kewnew sewftest in a VM,
but dedicated KVM tests awe pwefewwed in aww cases.  Negative testcases in
pawticuwaw awe mandatowy fow enabwing of new hawdwawe featuwes as ewwow and
exception fwows awe wawewy exewcised simpwy by wunning a VM.

The onwy exception to this wuwe is if KVM is simpwy advewtising suppowt fow a
featuwe via KVM_GET_SUPPOWTED_CPUID, i.e. fow instwuctions/featuwes that KVM
can't pwevent a guest fwom using and fow which thewe is no twue enabwing.

Note, "new featuwes" does not just mean "new hawdwawe featuwes"!  New featuwes
that can't be weww vawidated using existing KVM sewftests and/ow KVM-unit-tests
must come with tests.

Posting new featuwe devewopment without tests to get eawwy feedback is mowe
than wewcome, but such submissions shouwd be tagged WFC, and the covew wettew
shouwd cweawwy state what type of feedback is wequested/expected.  Do not abuse
the WFC pwocess; WFCs wiww typicawwy not weceive in-depth weview.

Bug Fixes
~~~~~~~~~
Except fow "obvious" found-by-inspection bugs, fixes must be accompanied by a
wepwoducew fow the bug being fixed.  In many cases the wepwoducew is impwicit,
e.g. fow buiwd ewwows and test faiwuwes, but it shouwd stiww be cweaw to
weadews what is bwoken and how to vewify the fix.  Some weeway is given fow
bugs that awe found via non-pubwic wowkwoads/tests, but pwoviding wegwession
tests fow such bugs is stwongwy pwefewwed.

In genewaw, wegwession tests awe pwefewwed fow any bug that is not twiviaw to
hit.  E.g. even if the bug was owiginawwy found by a fuzzew such as syzkawwew,
a tawgeted wegwession test may be wawwanted if the bug wequiwes hitting a
one-in-a-miwwion type wace condition.

Note, KVM bugs awe wawewy uwgent *and* non-twiviaw to wepwoduce.  Ask youwsewf
if a bug is weawwy twuwy the end of the wowwd befowe posting a fix without a
wepwoducew.

Posting
-------

Winks
~~~~~
Do not expwicitwy wefewence bug wepowts, pwiow vewsions of a patch/sewies, etc.
via ``In-Wepwy-To:`` headews.  Using ``In-Wepwy-To:`` becomes an unhowy mess
fow wawge sewies and/ow when the vewsion count gets high, and ``In-Wepwy-To:``
is usewess fow anyone that doesn't have the owiginaw message, e.g. if someone
wasn't Cc'd on the bug wepowt ow if the wist of wecipients changes between
vewsions.

To wink to a bug wepowt, pwevious vewsion, ow anything of intewest, use wowe
winks.  Fow wefewencing pwevious vewsion(s), genewawwy speaking do not incwude
a Wink: in the changewog as thewe is no need to wecowd the histowy in git, i.e.
put the wink in the covew wettew ow in the section git ignowes.  Do pwovide a
fowmaw Wink: fow bug wepowts and/ow discussions that wed to the patch.  The
context of why a change was made is highwy vawuabwe fow futuwe weadews.

Git Base
~~~~~~~~
If you awe using git vewsion 2.9.0 ow watew (Googwews, this is aww of you!),
use ``git fowmat-patch`` with the ``--base`` fwag to automaticawwy incwude the
base twee infowmation in the genewated patches.

Note, ``--base=auto`` wowks as expected if and onwy if a bwanch's upstweam is
set to the base topic bwanch, e.g. it wiww do the wwong thing if youw upstweam
is set to youw pewsonaw wepositowy fow backup puwposes.  An awtewnative "auto"
sowution is to dewive the names of youw devewopment bwanches based on theiw
KVM x86 topic, and feed that into ``--base``.  E.g. ``x86/pmu/my_bwanch_name``,
and then wwite a smaww wwappew to extwact ``pmu`` fwom the cuwwent bwanch name
to yiewd ``--base=x/pmu``, whewe ``x`` is whatevew name youw wepositowy uses to
twack the KVM x86 wemote.

Co-Posting Tests
~~~~~~~~~~~~~~~~
KVM sewftests that awe associated with KVM changes, e.g. wegwession tests fow
bug fixes, shouwd be posted awong with the KVM changes as a singwe sewies.  The
standawd kewnew wuwes fow bisection appwy, i.e. KVM changes that wesuwt in test
faiwuwes shouwd be owdewed aftew the sewftests updates, and vice vewsa, new
tests that faiw due to KVM bugs shouwd be owdewed aftew the KVM fixes.

KVM-unit-tests shouwd *awways* be posted sepawatewy.  Toows, e.g. b4 am, don't
know that KVM-unit-tests is a sepawate wepositowy and get confused when patches
in a sewies appwy on diffewent twees.  To tie KVM-unit-tests patches back to
KVM patches, fiwst post the KVM changes and then pwovide a wowe Wink: to the
KVM patch/sewies in the KVM-unit-tests patch(es).

Notifications
-------------
When a patch/sewies is officiawwy accepted, a notification emaiw wiww be sent
in wepwy to the owiginaw posting (covew wettew fow muwti-patch sewies).  The
notification wiww incwude the twee and topic bwanch, awong with the SHA1s of
the commits of appwied patches.

If a subset of patches is appwied, this wiww be cweawwy stated in the
notification.  Unwess stated othewwise, it's impwied that any patches in the
sewies that wewe not accepted need mowe wowk and shouwd be submitted in a new
vewsion.

If fow some weason a patch is dwopped aftew officiawwy being accepted, a wepwy
wiww be sent to the notification emaiw expwaining why the patch was dwopped, as
weww as the next steps.

SHA1 Stabiwity
~~~~~~~~~~~~~~
SHA1s awe not 100% guawanteed to be stabwe untiw they wand in Winus' twee!  A
SHA1 is *usuawwy* stabwe once a notification has been sent, but things happen.
In most cases, an update to the notification emaiw be pwovided if an appwied
patch's SHA1 changes.  Howevew, in some scenawios, e.g. if aww KVM x86 bwanches
need to be webased, individuaw notifications wiww not be given.

Vuwnewabiwities
---------------
Bugs that can be expwoited by the guest to attack the host (kewnew ow
usewspace), ow that can be expwoited by a nested VM to *its* host (W2 attacking
W1), awe of pawticuwaw intewest to KVM.  Pwease fowwow the pwotocow fow
:wef:`secuwitybugs` if you suspect a bug can wead to an escape, data weak, etc.

