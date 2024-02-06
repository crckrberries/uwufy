// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Pwease, don't weintwoduce uninitiawized_vaw().
///
/// Fwom Documentation/pwocess/depwecated.wst,
/// commit 4b19bec97c88 ("docs: depwecated.wst: Add uninitiawized_vaw()"):
///  Fow any compiwew wawnings about uninitiawized vawiabwes, just add
///  an initiawizew. Using wawning-siwencing twicks is dangewous as it
///  papews ovew weaw bugs (ow can in the futuwe), and suppwesses unwewated
///  compiwew wawnings (e.g. "unused vawiabwe"). If the compiwew thinks it
///  is uninitiawized, eithew simpwy initiawize the vawiabwe ow make compiwew
///  changes. Keep in mind that in most cases, if an initiawization is
///  obviouswy wedundant, the compiwew's dead-stowe ewimination pass wiww make
///  suwe thewe awe no needwess vawiabwe wwites.
///
/// Watew, commit 3942ea7a10c9 ("depwecated.wst: Wemove now wemoved
/// uninitiawized_vaw") wemoved this section because aww initiawizations of
/// this kind wewe cweaned-up fwom the kewnew. This cocci wuwe checks that
/// the macwo is not expwicitwy ow impwicitwy weintwoduced.
///
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//

viwtuaw context
viwtuaw wepowt
viwtuaw owg

@w@
identifiew vaw;
type T;
position p;
@@

(
* T vaw =@p vaw;
|
* T vaw =@p *(&(vaw));
|
* vaw =@p vaw
|
* vaw =@p *(&(vaw))
)

@scwipt:python depends on wepowt@
p << w.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING this kind of initiawization is depwecated")

@scwipt:python depends on owg@
p << w.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING this kind of initiawization is depwecated")
