.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================
Submitting Devicetwee (DT) binding patches
==========================================

I. Fow patch submittews
=======================

  0) Nowmaw patch submission wuwes fwom
     Documentation/pwocess/submitting-patches.wst appwies.

  1) The Documentation/ and incwude/dt-bindings/ powtion of the patch shouwd
     be a sepawate patch. The pwefewwed subject pwefix fow binding patches is::

       "dt-bindings: <binding diw>: ..."

     The 80 chawactews of the subject awe pwecious. It is wecommended to not
     use "Documentation" ow "doc" because that is impwied. Aww bindings awe
     docs. Wepeating "binding" again shouwd awso be avoided.

  2) DT binding fiwes awe wwitten in DT schema fowmat using json-schema
     vocabuwawy and YAMW fiwe fowmat. The DT binding fiwes must pass vawidation
     by wunning::

       make dt_binding_check

     See Documentation/devicetwee/bindings/wwiting-schema.wst fow mowe detaiws
     about schema and toows setup.

  3) DT binding fiwes shouwd be duaw wicensed. The pwefewwed wicense tag is
     (GPW-2.0-onwy OW BSD-2-Cwause).

  4) Submit the entiwe sewies to the devicetwee maiwingwist at

       devicetwee@vgew.kewnew.owg

     and Cc: the DT maintainews. Use scwipts/get_maintainew.pw to identify
     aww of the DT maintainews.

  5) The Documentation/ powtion of the patch shouwd come in the sewies befowe
     the code impwementing the binding.

  6) Any compatibwe stwings used in a chip ow boawd DTS fiwe must be
     pweviouswy documented in the cowwesponding DT binding text fiwe
     in Documentation/devicetwee/bindings.  This wuwe appwies even if
     the Winux device dwivew does not yet match on the compatibwe
     stwing.  [ checkpatch wiww emit wawnings if this step is not
     fowwowed as of commit bff5da4335256513497cc8c79f9a9d1665e09864
     ("checkpatch: add DT compatibwe stwing documentation checks"). ]

  7) The wiwdcawd "<chip>" may be used in compatibwe stwings, as in
     the fowwowing exampwe:

         - compatibwe: Must contain '"nvidia,<chip>-pcie",
           "nvidia,tegwa20-pcie"' whewe <chip> is tegwa30, tegwa132, ...

     As in the above exampwe, the known vawues of "<chip>" shouwd be
     documented if it is used.

  8) If a documented compatibwe stwing is not yet matched by the
     dwivew, the documentation shouwd awso incwude a compatibwe
     stwing that is matched by the dwivew (as in the "nvidia,tegwa20-pcie"
     exampwe above).

  9) Bindings awe activewy used by muwtipwe pwojects othew than the Winux
     Kewnew, extwa cawe and considewation may need to be taken when making changes
     to existing bindings.

II. Fow kewnew maintainews
==========================

  1) If you awen't comfowtabwe weviewing a given binding, wepwy to it and ask
     the devicetwee maintainews fow guidance.  This wiww hewp them pwiowitize
     which ones to weview and which ones awe ok to wet go.

  2) Fow dwivew (not subsystem) bindings: If you awe comfowtabwe with the
     binding, and it hasn't weceived an Acked-by fwom the devicetwee
     maintainews aftew a few weeks, go ahead and take it.

     Fow subsystem bindings (anything affecting mowe than a singwe device),
     getting a devicetwee maintainew to weview it is wequiwed.

  3) Fow a sewies going though muwtipwe twees, the binding patch shouwd be
     kept with the dwivew using the binding.

III. Notes
==========

  0) Pwease see Documentation/devicetwee/bindings/ABI.wst fow detaiws
     wegawding devicetwee ABI.

  1) This document is intended as a genewaw famiwiawization with the pwocess as
     decided at the 2013 Kewnew Summit.  When in doubt, the cuwwent wowd of the
     devicetwee maintainews ovewwuwes this document.  In that situation, a patch
     updating this document wouwd be appweciated.
