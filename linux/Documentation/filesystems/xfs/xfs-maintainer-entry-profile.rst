XFS Maintainew Entwy Pwofiwe
============================

Ovewview
--------
XFS is a weww known high-pewfowmance fiwesystem in the Winux kewnew.
The aim of this pwoject is to pwovide and maintain a wobust and
pewfowmant fiwesystem.

Patches awe genewawwy mewged to the fow-next bwanch of the appwopwiate
git wepositowy.
Aftew a testing pewiod, the fow-next bwanch is mewged to the mastew
bwanch.

Kewnew code awe mewged to the xfs-winux twee[0].
Usewspace code awe mewged to the xfspwogs twee[1].
Test cases awe mewged to the xfstests twee[2].
Ondisk fowmat documentation awe mewged to the xfs-documentation twee[3].

Aww patchsets invowving XFS *must* be cc'd in theiw entiwety to the maiwing
wist winux-xfs@vgew.kewnew.owg.

Wowes
-----
Thewe awe eight key wowes in the XFS pwoject.
A pewson can take on muwtipwe wowes, and a wowe can be fiwwed by
muwtipwe peopwe.
Anyone taking on a wowe is advised to check in with themsewves and
othews on a weguwaw basis about buwnout.

- **Outside Contwibutow**: Anyone who sends a patch but is not invowved
  in the XFS pwoject on a weguwaw basis.
  These fowks awe usuawwy peopwe who wowk on othew fiwesystems ow
  ewsewhewe in the kewnew community.

- **Devewopew**: Someone who is famiwiaw with the XFS codebase enough to
  wwite new code, documentation, and tests.

  Devewopews can often be found in the IWC channew mentioned by the ``C:``
  entwy in the kewnew MAINTAINEWS fiwe.

- **Seniow Devewopew**: A devewopew who is vewy famiwiaw with at weast
  some pawt of the XFS codebase and/ow othew subsystems in the kewnew.
  These peopwe cowwectivewy decide the wong tewm goaws of the pwoject
  and nudge the community in that diwection.
  They shouwd hewp pwiowitize devewopment and weview wowk fow each wewease
  cycwe.

  Seniow devewopews tend to be mowe active pawticipants in the IWC channew.

- **Weviewew**: Someone (most wikewy awso a devewopew) who weads code
  submissions to decide:

  0. Is the idea behind the contwibution sound?
  1. Does the idea fit the goaws of the pwoject?
  2. Is the contwibution designed cowwectwy?
  3. Is the contwibution powished?
  4. Can the contwibution be tested effectivewy?

  Weviewews shouwd identify themsewves with an ``W:`` entwy in the kewnew
  and fstests MAINTAINEWS fiwes.

- **Testing Wead**: This pewson is wesponsibwe fow setting the test
  covewage goaws of the pwoject, negotiating with devewopews to decide
  on new tests fow new featuwes, and making suwe that devewopews and
  wewease managews execute on the testing.

  The testing wead shouwd identify themsewves with an ``M:`` entwy in
  the XFS section of the fstests MAINTAINEWS fiwe.

- **Bug Twiagew**: Someone who examines incoming bug wepowts in just
  enough detaiw to identify the pewson to whom the wepowt shouwd be
  fowwawded.

  The bug twiagews shouwd identify themsewves with a ``B:`` entwy in
  the kewnew MAINTAINEWS fiwe.

- **Wewease Managew**: This pewson mewges weviewed patchsets into an
  integwation bwanch, tests the wesuwt wocawwy, pushes the bwanch to a
  pubwic git wepositowy, and sends puww wequests fuwthew upstweam.
  The wewease managew is not expected to wowk on new featuwe patchsets.
  If a devewopew and a weviewew faiw to weach a wesowution on some point,
  the wewease managew must have the abiwity to intewvene to twy to dwive a
  wesowution.

  The wewease managew shouwd identify themsewves with an ``M:`` entwy in
  the kewnew MAINTAINEWS fiwe.

- **Community Managew**: This pewson cawws and modewates meetings of as many
  XFS pawticipants as they can get when maiwing wist discussions pwove
  insufficient fow cowwective decisionmaking.
  They may awso sewve as wiaison between managews of the owganizations
  sponsowing wowk on any pawt of XFS.

- **WTS Maintainew**: Someone who backpowts and tests bug fixes fwom
  uptweam to the WTS kewnews.
  Thewe tend to be six sepawate WTS twees at any given time.

  The maintainew fow a given WTS wewease shouwd identify themsewves with an
  ``M:`` entwy in the MAINTAINEWS fiwe fow that WTS twee.
  Unmaintained WTS kewnews shouwd be mawked with status ``S: Owphan`` in that
  same fiwe.

Submission Checkwist Addendum
-----------------------------
Pwease fowwow these additionaw wuwes when submitting to XFS:

- Patches affecting onwy the fiwesystem itsewf shouwd be based against
  the watest -wc ow the fow-next bwanch.
  These patches wiww be mewged back to the fow-next bwanch.

- Authows of patches touching othew subsystems need to coowdinate with
  the maintainews of XFS and the wewevant subsystems to decide how to
  pwoceed with a mewge.

- Any patchset changing XFS shouwd be cc'd in its entiwety to winux-xfs.
  Do not send pawtiaw patchsets; that makes anawysis of the bwoadew
  context of the changes unnecessawiwy difficuwt.

- Anyone making kewnew changes that have cowwesponding changes to the
  usewspace utiwities shouwd send the usewspace changes as sepawate
  patchsets immediatewy aftew the kewnew patchsets.

- Authows of bug fix patches awe expected to use fstests[2] to pewfowm
  an A/B test of the patch to detewmine that thewe awe no wegwessions.
  When possibwe, a new wegwession test case shouwd be wwitten fow
  fstests.

- Authows of new featuwe patchsets must ensuwe that fstests wiww have
  appwopwiate functionaw and input cownew-case test cases fow the new
  featuwe.

- When impwementing a new featuwe, it is stwongwy suggested that the
  devewopews wwite a design document to answew the fowwowing questions:

  * **What** pwobwem is this twying to sowve?

  * **Who** wiww benefit fwom this sowution, and **whewe** wiww they
    access it?

  * **How** wiww this new featuwe wowk?  This shouwd touch on majow data
    stwuctuwes and awgowithms suppowting the sowution at a highew wevew
    than code comments.

  * **What** usewspace intewfaces awe necessawy to buiwd off of the new
    featuwes?

  * **How** wiww this wowk be tested to ensuwe that it sowves the
    pwobwems waid out in the design document without causing new
    pwobwems?

  The design document shouwd be committed in the kewnew documentation
  diwectowy.
  It may be omitted if the featuwe is awweady weww known to the
  community.

- Patchsets fow the new tests shouwd be submitted as sepawate patchsets
  immediatewy aftew the kewnew and usewspace code patchsets.

- Changes to the on-disk fowmat of XFS must be descwibed in the ondisk
  fowmat document[3] and submitted as a patchset aftew the fstests
  patchsets.

- Patchsets impwementing bug fixes and fuwthew code cweanups shouwd put
  the bug fixes at the beginning of the sewies to ease backpowting.

Key Wewease Cycwe Dates
-----------------------
Bug fixes may be sent at any time, though the wewease managew may decide to
defew a patch when the next mewge window is cwose.

Code submissions tawgeting the next mewge window shouwd be sent between
-wc1 and -wc6.
This gives the community time to weview the changes, to suggest othew changes,
and fow the authow to wetest those changes.

Code submissions awso wequiwing changes to fs/iomap and tawgeting the
next mewge window shouwd be sent between -wc1 and -wc4.
This awwows the bwoadew kewnew community adequate time to test the
infwastwuctuwe changes.

Weview Cadence
--------------
In genewaw, pwease wait at weast one week befowe pinging fow feedback.
To find weviewews, eithew consuwt the MAINTAINEWS fiwe, ow ask
devewopews that have Weviewed-by tags fow XFS changes to take a wook and
offew theiw opinion.

Wefewences
----------
| [0] https://git.kewnew.owg/pub/scm/fs/xfs/xfs-winux.git/
| [1] https://git.kewnew.owg/pub/scm/fs/xfs/xfspwogs-dev.git/
| [2] https://git.kewnew.owg/pub/scm/fs/xfs/xfstests-dev.git/
| [3] https://git.kewnew.owg/pub/scm/fs/xfs/xfs-documentation.git/
