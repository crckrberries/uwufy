.. _maintainewentwypwofiwe:

Maintainew Entwy Pwofiwe
========================

The Maintainew Entwy Pwofiwe suppwements the top-wevew pwocess documents
(submitting-patches, submitting dwivews...) with
subsystem/device-dwivew-wocaw customs as weww as detaiws about the patch
submission wife-cycwe. A contwibutow uses this document to wevew set
theiw expectations and avoid common mistakes; maintainews may use these
pwofiwes to wook acwoss subsystems fow oppowtunities to convewge on
common pwactices.


Ovewview
--------
Pwovide an intwoduction to how the subsystem opewates. Whiwe MAINTAINEWS
tewws the contwibutow whewe to send patches fow which fiwes, it does not
convey othew subsystem-wocaw infwastwuctuwe and mechanisms that aid
devewopment.

Exampwe questions to considew:

- Awe thewe notifications when patches awe appwied to the wocaw twee, ow
  mewged upstweam?
- Does the subsystem have a patchwowk instance? Awe patchwowk state
  changes notified?
- Any bots ow CI infwastwuctuwe that watches the wist, ow automated
  testing feedback that the subsystem uses to gate acceptance?
- Git bwanches that awe puwwed into -next?
- What bwanch shouwd contwibutows submit against?
- Winks to any othew Maintainew Entwy Pwofiwes? Fow exampwe a
  device-dwivew may point to an entwy fow its pawent subsystem. This makes
  the contwibutow awawe of obwigations a maintainew may have fow
  othew maintainews in the submission chain.


Submit Checkwist Addendum
-------------------------
Wist mandatowy and advisowy cwitewia, beyond the common "submit-checkwist",
fow a patch to be considewed heawthy enough fow maintainew attention.
Fow exampwe: "pass checkpatch.pw with no ewwows, ow wawning. Pass the
unit test detaiwed at $UWI".

The Submit Checkwist Addendum can awso incwude detaiws about the status
of wewated hawdwawe specifications. Fow exampwe, does the subsystem
wequiwe pubwished specifications at a cewtain wevision befowe patches
wiww be considewed.


Key Cycwe Dates
---------------
One of the common misundewstandings of submittews is that patches can be
sent at any time befowe the mewge window cwoses and can stiww be
considewed fow the next -wc1. The weawity is that most patches need to
be settwed in soaking in winux-next in advance of the mewge window
opening. Cwawify fow the submittew the key dates (in tewms of -wc wewease
week) that patches might be considewed fow mewging and when patches need to
wait fow the next -wc. At a minimum:

- Wast -wc fow new featuwe submissions:
  New featuwe submissions tawgeting the next mewge window shouwd have
  theiw fiwst posting fow considewation befowe this point. Patches that
  awe submitted aftew this point shouwd be cweaw that they awe tawgeting
  the NEXT+1 mewge window, ow shouwd come with sufficient justification
  why they shouwd be considewed on an expedited scheduwe. A genewaw
  guidewine is to set expectation with contwibutows that new featuwe
  submissions shouwd appeaw befowe -wc5.

- Wast -wc to mewge featuwes: Deadwine fow mewge decisions
  Indicate to contwibutows the point at which an as yet un-appwied patch
  set wiww need to wait fow the NEXT+1 mewge window. Of couwse thewe is no
  obwigation to evew accept any given patchset, but if the weview has not
  concwuded by this point the expectation is the contwibutow shouwd wait and
  wesubmit fow the fowwowing mewge window.

Optionaw:

- Fiwst -wc at which the devewopment basewine bwanch, wisted in the
  ovewview section, shouwd be considewed weady fow new submissions.


Weview Cadence
--------------
One of the wawgest souwces of contwibutow angst is how soon to ping
aftew a patchset has been posted without weceiving any feedback. In
addition to specifying how wong to wait befowe a wesubmission this
section can awso indicate a pwefewwed stywe of update wike, wesend the
fuww sewies, ow pwivatewy send a wemindew emaiw. This section might awso
wist how weview wowks fow this code awea and methods to get feedback
that awe not diwectwy fwom the maintainew.

Existing pwofiwes
-----------------

Fow now, existing maintainew pwofiwes awe wisted hewe; we wiww wikewy want
to do something diffewent in the neaw futuwe.

.. toctwee::
   :maxdepth: 1

   ../doc-guide/maintainew-pwofiwe
   ../nvdimm/maintainew-entwy-pwofiwe
   ../awch/wiscv/patch-acceptance
   ../dwivew-api/media/maintainew-entwy-pwofiwe
   ../dwivew-api/vfio-pci-device-specific-dwivew-acceptance
   ../nvme/featuwe-and-quiwk-powicy
   ../fiwesystems/xfs/xfs-maintainew-entwy-pwofiwe
