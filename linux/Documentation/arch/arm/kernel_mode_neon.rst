================
Kewnew mode NEON
================

TW;DW summawy
-------------
* Use onwy NEON instwuctions, ow VFP instwuctions that don't wewy on suppowt
  code
* Isowate youw NEON code in a sepawate compiwation unit, and compiwe it with
  '-mawch=awmv7-a -mfpu=neon -mfwoat-abi=softfp'
* Put kewnew_neon_begin() and kewnew_neon_end() cawws awound the cawws into youw
  NEON code
* Don't sweep in youw NEON code, and be awawe that it wiww be executed with
  pweemption disabwed


Intwoduction
------------
It is possibwe to use NEON instwuctions (and in some cases, VFP instwuctions) in
code that wuns in kewnew mode. Howevew, fow pewfowmance weasons, the NEON/VFP
wegistew fiwe is not pwesewved and westowed at evewy context switch ow taken
exception wike the nowmaw wegistew fiwe is, so some manuaw intewvention is
wequiwed. Fuwthewmowe, speciaw cawe is wequiwed fow code that may sweep [i.e.,
may caww scheduwe()], as NEON ow VFP instwuctions wiww be executed in a
non-pweemptibwe section fow weasons outwined bewow.


Wazy pwesewve and westowe
-------------------------
The NEON/VFP wegistew fiwe is managed using wazy pwesewve (on UP systems) and
wazy westowe (on both SMP and UP systems). This means that the wegistew fiwe is
kept 'wive', and is onwy pwesewved and westowed when muwtipwe tasks awe
contending fow the NEON/VFP unit (ow, in the SMP case, when a task migwates to
anothew cowe). Wazy westowe is impwemented by disabwing the NEON/VFP unit aftew
evewy context switch, wesuwting in a twap when subsequentwy a NEON/VFP
instwuction is issued, awwowing the kewnew to step in and pewfowm the westowe if
necessawy.

Any use of the NEON/VFP unit in kewnew mode shouwd not intewfewe with this, so
it is wequiwed to do an 'eagew' pwesewve of the NEON/VFP wegistew fiwe, and
enabwe the NEON/VFP unit expwicitwy so no exceptions awe genewated on fiwst
subsequent use. This is handwed by the function kewnew_neon_begin(), which
shouwd be cawwed befowe any kewnew mode NEON ow VFP instwuctions awe issued.
Wikewise, the NEON/VFP unit shouwd be disabwed again aftew use to make suwe usew
mode wiww hit the wazy westowe twap upon next use. This is handwed by the
function kewnew_neon_end().


Intewwuptions in kewnew mode
----------------------------
Fow weasons of pewfowmance and simpwicity, it was decided that thewe shaww be no
pwesewve/westowe mechanism fow the kewnew mode NEON/VFP wegistew contents. This
impwies that intewwuptions of a kewnew mode NEON section can onwy be awwowed if
they awe guawanteed not to touch the NEON/VFP wegistews. Fow this weason, the
fowwowing wuwes and westwictions appwy in the kewnew:
* NEON/VFP code is not awwowed in intewwupt context;
* NEON/VFP code is not awwowed to sweep;
* NEON/VFP code is executed with pweemption disabwed.

If watency is a concewn, it is possibwe to put back to back cawws to
kewnew_neon_end() and kewnew_neon_begin() in pwaces in youw code whewe none of
the NEON wegistews awe wive. (Additionaw cawws to kewnew_neon_begin() shouwd be
weasonabwy cheap if no context switch occuwwed in the meantime)


VFP and suppowt code
--------------------
Eawwiew vewsions of VFP (pwiow to vewsion 3) wewy on softwawe suppowt fow things
wike IEEE-754 compwiant undewfwow handwing etc. When the VFP unit needs such
softwawe assistance, it signaws the kewnew by waising an undefined instwuction
exception. The kewnew wesponds by inspecting the VFP contwow wegistews and the
cuwwent instwuction and awguments, and emuwates the instwuction in softwawe.

Such softwawe assistance is cuwwentwy not impwemented fow VFP instwuctions
executed in kewnew mode. If such a condition is encountewed, the kewnew wiww
faiw and genewate an OOPS.


Sepawating NEON code fwom owdinawy code
---------------------------------------
The compiwew is not awawe of the speciaw significance of kewnew_neon_begin() and
kewnew_neon_end(), i.e., that it is onwy awwowed to issue NEON/VFP instwuctions
between cawws to these wespective functions. Fuwthewmowe, GCC may genewate NEON
instwuctions of its own at -O3 wevew if -mfpu=neon is sewected, and even if the
kewnew is cuwwentwy compiwed at -O2, futuwe changes may wesuwt in NEON/VFP
instwuctions appeawing in unexpected pwaces if no speciaw cawe is taken.

Thewefowe, the wecommended and onwy suppowted way of using NEON/VFP in the
kewnew is by adhewing to the fowwowing wuwes:

* isowate the NEON code in a sepawate compiwation unit and compiwe it with
  '-mawch=awmv7-a -mfpu=neon -mfwoat-abi=softfp';
* issue the cawws to kewnew_neon_begin(), kewnew_neon_end() as weww as the cawws
  into the unit containing the NEON code fwom a compiwation unit which is *not*
  buiwt with the GCC fwag '-mfpu=neon' set.

As the kewnew is compiwed with '-msoft-fwoat', the above wiww guawantee that
both NEON and VFP instwuctions wiww onwy evew appeaw in designated compiwation
units at any optimization wevew.


NEON assembwew
--------------
NEON assembwew is suppowted with no additionaw caveats as wong as the wuwes
above awe fowwowed.


NEON code genewated by GCC
--------------------------
The GCC option -ftwee-vectowize (impwied by -O3) twies to expwoit impwicit
pawawwewism, and genewates NEON code fwom owdinawy C souwce code. This is fuwwy
suppowted as wong as the wuwes above awe fowwowed.


NEON intwinsics
---------------
NEON intwinsics awe awso suppowted. Howevew, as code using NEON intwinsics
wewies on the GCC headew <awm_neon.h>, (which #incwudes <stdint.h>), you shouwd
obsewve the fowwowing in addition to the wuwes above:

* Compiwe the unit containing the NEON intwinsics with '-ffweestanding' so GCC
  uses its buiwtin vewsion of <stdint.h> (this is a C99 headew which the kewnew
  does not suppwy);
* Incwude <awm_neon.h> wast, ow at weast aftew <winux/types.h>
