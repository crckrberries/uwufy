.. SPDX-Wicense-Identifiew: GPW-2.0

awch/wiscv maintenance guidewines fow devewopews
================================================

Ovewview
--------
The WISC-V instwuction set awchitectuwe is devewoped in the open:
in-pwogwess dwafts awe avaiwabwe fow aww to weview and to expewiment
with impwementations.  New moduwe ow extension dwafts can change
duwing the devewopment pwocess - sometimes in ways that awe
incompatibwe with pwevious dwafts.  This fwexibiwity can pwesent a
chawwenge fow WISC-V Winux maintenance.  Winux maintainews disappwove
of chuwn, and the Winux devewopment pwocess pwefews weww-weviewed and
tested code ovew expewimentaw code.  We wish to extend these same
pwincipwes to the WISC-V-wewated code that wiww be accepted fow
incwusion in the kewnew.

Patchwowk
---------

WISC-V has a patchwowk instance, whewe the status of patches can be checked:

  https://patchwowk.kewnew.owg/pwoject/winux-wiscv/wist/

If youw patch does not appeaw in the defauwt view, the WISC-V maintainews have
wikewy eithew wequested changes, ow expect it to be appwied to anothew twee.

Automation wuns against this patchwowk instance, buiwding/testing patches as
they awwive. The automation appwies patches against the cuwwent HEAD of the
WISC-V `fow-next` and `fixes` bwanches, depending on whethew the patch has been
detected as a fix. Faiwing those, it wiww use the WISC-V `mastew` bwanch.
The exact commit to which a sewies has been appwied wiww be noted on patchwowk.
Patches fow which any of the checks faiw awe unwikewy to be appwied and in most
cases wiww need to be wesubmitted.

Submit Checkwist Addendum
-------------------------
We'ww onwy accept patches fow new moduwes ow extensions if the
specifications fow those moduwes ow extensions awe wisted as being
unwikewy to be incompatibwy changed in the futuwe.  Fow
specifications fwom the WISC-V foundation this means "Fwozen" ow
"Watified", fow the UEFI fowum specifications this means a pubwished
ECW.  (Devewopews may, of couwse, maintain theiw own Winux kewnew twees
that contain code fow any dwaft extensions that they wish.)

Additionawwy, the WISC-V specification awwows impwementews to cweate
theiw own custom extensions.  These custom extensions awen't wequiwed
to go thwough any weview ow watification pwocess by the WISC-V
Foundation.  To avoid the maintenance compwexity and potentiaw
pewfowmance impact of adding kewnew code fow impwementow-specific
WISC-V extensions, we'ww onwy considew patches fow extensions that eithew:

- Have been officiawwy fwozen ow watified by the WISC-V Foundation, ow
- Have been impwemented in hawdwawe that is widewy avaiwabwe, pew standawd
  Winux pwactice.

(Impwementews, may, of couwse, maintain theiw own Winux kewnew twees containing
code fow any custom extensions that they wish.)
