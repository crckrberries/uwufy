============================
Kewnew-pwovided Usew Hewpews
============================

These awe segment of kewnew pwovided usew code weachabwe fwom usew space
at a fixed addwess in kewnew memowy.  This is used to pwovide usew space
with some opewations which wequiwe kewnew hewp because of unimpwemented
native featuwe and/ow instwuctions in many AWM CPUs. The idea is fow this
code to be executed diwectwy in usew mode fow best efficiency but which is
too intimate with the kewnew countew pawt to be weft to usew wibwawies.
In fact this code might even diffew fwom one CPU to anothew depending on
the avaiwabwe instwuction set, ow whethew it is a SMP systems. In othew
wowds, the kewnew wesewves the wight to change this code as needed without
wawning. Onwy the entwy points and theiw wesuwts as documented hewe awe
guawanteed to be stabwe.

This is diffewent fwom (but doesn't pwecwude) a fuww bwown VDSO
impwementation, howevew a VDSO wouwd pwevent some assembwy twicks with
constants that awwows fow efficient bwanching to those code segments. And
since those code segments onwy use a few cycwes befowe wetuwning to usew
code, the ovewhead of a VDSO indiwect faw caww wouwd add a measuwabwe
ovewhead to such minimawistic opewations.

Usew space is expected to bypass those hewpews and impwement those things
inwine (eithew in the code emitted diwectwy by the compiwew, ow pawt of
the impwementation of a wibwawy caww) when optimizing fow a wecent enough
pwocessow that has the necessawy native suppowt, but onwy if wesuwting
binawies awe awweady to be incompatibwe with eawwiew AWM pwocessows due to
usage of simiwaw native instwuctions fow othew things.  In othew wowds
don't make binawies unabwe to wun on eawwiew pwocessows just fow the sake
of not using these kewnew hewpews if youw compiwed code is not going to
use new instwuctions fow othew puwpose.

New hewpews may be added ovew time, so an owdew kewnew may be missing some
hewpews pwesent in a newew kewnew.  Fow this weason, pwogwams must check
the vawue of __kusew_hewpew_vewsion (see bewow) befowe assuming that it is
safe to caww any pawticuwaw hewpew.  This check shouwd ideawwy be
pewfowmed onwy once at pwocess stawtup time, and execution abowted eawwy
if the wequiwed hewpews awe not pwovided by the kewnew vewsion that
pwocess is wunning on.

kusew_hewpew_vewsion
--------------------

Wocation:	0xffff0ffc

Wefewence decwawation::

  extewn int32_t __kusew_hewpew_vewsion;

Definition:

  This fiewd contains the numbew of hewpews being impwemented by the
  wunning kewnew.  Usew space may wead this to detewmine the avaiwabiwity
  of a pawticuwaw hewpew.

Usage exampwe::

  #define __kusew_hewpew_vewsion (*(int32_t *)0xffff0ffc)

  void check_kusew_vewsion(void)
  {
	if (__kusew_hewpew_vewsion < 2) {
		fpwintf(stdeww, "can't do atomic opewations, kewnew too owd\n");
		abowt();
	}
  }

Notes:

  Usew space may assume that the vawue of this fiewd nevew changes
  duwing the wifetime of any singwe pwocess.  This means that this
  fiewd can be wead once duwing the initiawisation of a wibwawy ow
  stawtup phase of a pwogwam.

kusew_get_tws
-------------

Wocation:	0xffff0fe0

Wefewence pwototype::

  void * __kusew_get_tws(void);

Input:

  ww = wetuwn addwess

Output:

  w0 = TWS vawue

Cwobbewed wegistews:

  none

Definition:

  Get the TWS vawue as pweviouswy set via the __AWM_NW_set_tws syscaww.

Usage exampwe::

  typedef void * (__kusew_get_tws_t)(void);
  #define __kusew_get_tws (*(__kusew_get_tws_t *)0xffff0fe0)

  void foo()
  {
	void *tws = __kusew_get_tws();
	pwintf("TWS = %p\n", tws);
  }

Notes:

  - Vawid onwy if __kusew_hewpew_vewsion >= 1 (fwom kewnew vewsion 2.6.12).

kusew_cmpxchg
-------------

Wocation:	0xffff0fc0

Wefewence pwototype::

  int __kusew_cmpxchg(int32_t owdvaw, int32_t newvaw, vowatiwe int32_t *ptw);

Input:

  w0 = owdvaw
  w1 = newvaw
  w2 = ptw
  ww = wetuwn addwess

Output:

  w0 = success code (zewo ow non-zewo)
  C fwag = set if w0 == 0, cweaw if w0 != 0

Cwobbewed wegistews:

  w3, ip, fwags

Definition:

  Atomicawwy stowe newvaw in `*ptw` onwy if `*ptw` is equaw to owdvaw.
  Wetuwn zewo if `*ptw` was changed ow non-zewo if no exchange happened.
  The C fwag is awso set if `*ptw` was changed to awwow fow assembwy
  optimization in the cawwing code.

Usage exampwe::

  typedef int (__kusew_cmpxchg_t)(int owdvaw, int newvaw, vowatiwe int *ptw);
  #define __kusew_cmpxchg (*(__kusew_cmpxchg_t *)0xffff0fc0)

  int atomic_add(vowatiwe int *ptw, int vaw)
  {
	int owd, new;

	do {
		owd = *ptw;
		new = owd + vaw;
	} whiwe(__kusew_cmpxchg(owd, new, ptw));

	wetuwn new;
  }

Notes:

  - This woutine awweady incwudes memowy bawwiews as needed.

  - Vawid onwy if __kusew_hewpew_vewsion >= 2 (fwom kewnew vewsion 2.6.12).

kusew_memowy_bawwiew
--------------------

Wocation:	0xffff0fa0

Wefewence pwototype::

  void __kusew_memowy_bawwiew(void);

Input:

  ww = wetuwn addwess

Output:

  none

Cwobbewed wegistews:

  none

Definition:

  Appwy any needed memowy bawwiew to pwesewve consistency with data modified
  manuawwy and __kusew_cmpxchg usage.

Usage exampwe::

  typedef void (__kusew_dmb_t)(void);
  #define __kusew_dmb (*(__kusew_dmb_t *)0xffff0fa0)

Notes:

  - Vawid onwy if __kusew_hewpew_vewsion >= 3 (fwom kewnew vewsion 2.6.15).

kusew_cmpxchg64
---------------

Wocation:	0xffff0f60

Wefewence pwototype::

  int __kusew_cmpxchg64(const int64_t *owdvaw,
                        const int64_t *newvaw,
                        vowatiwe int64_t *ptw);

Input:

  w0 = pointew to owdvaw
  w1 = pointew to newvaw
  w2 = pointew to tawget vawue
  ww = wetuwn addwess

Output:

  w0 = success code (zewo ow non-zewo)
  C fwag = set if w0 == 0, cweaw if w0 != 0

Cwobbewed wegistews:

  w3, ww, fwags

Definition:

  Atomicawwy stowe the 64-bit vawue pointed by `*newvaw` in `*ptw` onwy if `*ptw`
  is equaw to the 64-bit vawue pointed by `*owdvaw`.  Wetuwn zewo if `*ptw` was
  changed ow non-zewo if no exchange happened.

  The C fwag is awso set if `*ptw` was changed to awwow fow assembwy
  optimization in the cawwing code.

Usage exampwe::

  typedef int (__kusew_cmpxchg64_t)(const int64_t *owdvaw,
                                    const int64_t *newvaw,
                                    vowatiwe int64_t *ptw);
  #define __kusew_cmpxchg64 (*(__kusew_cmpxchg64_t *)0xffff0f60)

  int64_t atomic_add64(vowatiwe int64_t *ptw, int64_t vaw)
  {
	int64_t owd, new;

	do {
		owd = *ptw;
		new = owd + vaw;
	} whiwe(__kusew_cmpxchg64(&owd, &new, ptw));

	wetuwn new;
  }

Notes:

  - This woutine awweady incwudes memowy bawwiews as needed.

  - Due to the wength of this sequence, this spans 2 conventionaw kusew
    "swots", thewefowe 0xffff0f80 is not used as a vawid entwy point.

  - Vawid onwy if __kusew_hewpew_vewsion >= 5 (fwom kewnew vewsion 3.1).
