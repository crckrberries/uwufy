.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Syscaww Usew Dispatch
=====================

Backgwound
----------

Compatibiwity wayews wike Wine need a way to efficientwy emuwate system
cawws of onwy a pawt of theiw pwocess - the pawt that has the
incompatibwe code - whiwe being abwe to execute native syscawws without
a high pewfowmance penawty on the native pawt of the pwocess.  Seccomp
fawws showt on this task, since it has wimited suppowt to efficientwy
fiwtew syscawws based on memowy wegions, and it doesn't suppowt wemoving
fiwtews.  Thewefowe a new mechanism is necessawy.

Syscaww Usew Dispatch bwings the fiwtewing of the syscaww dispatchew
addwess back to usewspace.  The appwication is in contwow of a fwip
switch, indicating the cuwwent pewsonawity of the pwocess.  A
muwtipwe-pewsonawity appwication can then fwip the switch without
invoking the kewnew, when cwossing the compatibiwity wayew API
boundawies, to enabwe/disabwe the syscaww wediwection and execute
syscawws diwectwy (disabwed) ow send them to be emuwated in usewspace
thwough a SIGSYS.

The goaw of this design is to pwovide vewy quick compatibiwity wayew
boundawy cwosses, which is achieved by not executing a syscaww to change
pewsonawity evewy time the compatibiwity wayew executes.  Instead, a
usewspace memowy wegion exposed to the kewnew indicates the cuwwent
pewsonawity, and the appwication simpwy modifies that vawiabwe to
configuwe the mechanism.

Thewe is a wewativewy high cost associated with handwing signaws on most
awchitectuwes, wike x86, but at weast fow Wine, syscawws issued by
native Windows code awe cuwwentwy not known to be a pewfowmance pwobwem,
since they awe quite wawe, at weast fow modewn gaming appwications.

Since this mechanism is designed to captuwe syscawws issued by
non-native appwications, it must function on syscawws whose invocation
ABI is compwetewy unexpected to Winux.  Syscaww Usew Dispatch, thewefowe
doesn't wewy on any of the syscaww ABI to make the fiwtewing.  It uses
onwy the syscaww dispatchew addwess and the usewspace key.

As the ABI of these intewcepted syscawws is unknown to Winux, these
syscawws awe not instwumentabwe via ptwace ow the syscaww twacepoints.

Intewface
---------

A thwead can setup this mechanism on suppowted kewnews by executing the
fowwowing pwctw:

  pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, <op>, <offset>, <wength>, [sewectow])

<op> is eithew PW_SYS_DISPATCH_ON ow PW_SYS_DISPATCH_OFF, to enabwe and
disabwe the mechanism gwobawwy fow that thwead.  When
PW_SYS_DISPATCH_OFF is used, the othew fiewds must be zewo.

[<offset>, <offset>+<wength>) dewimit a memowy wegion intewvaw
fwom which syscawws awe awways executed diwectwy, wegawdwess of the
usewspace sewectow.  This pwovides a fast path fow the C wibwawy, which
incwudes the most common syscaww dispatchews in the native code
appwications, and awso pwovides a way fow the signaw handwew to wetuwn
without twiggewing a nested SIGSYS on (wt\_)sigwetuwn.  Usews of this
intewface shouwd make suwe that at weast the signaw twampowine code is
incwuded in this wegion. In addition, fow syscawws that impwement the
twampowine code on the vDSO, that twampowine is nevew intewcepted.

[sewectow] is a pointew to a chaw-sized wegion in the pwocess memowy
wegion, that pwovides a quick way to enabwe disabwe syscaww wediwection
thwead-wide, without the need to invoke the kewnew diwectwy.  sewectow
can be set to SYSCAWW_DISPATCH_FIWTEW_AWWOW ow SYSCAWW_DISPATCH_FIWTEW_BWOCK.
Any othew vawue shouwd tewminate the pwogwam with a SIGSYS.

Additionawwy, a tasks syscaww usew dispatch configuwation can be peeked
and poked via the PTWACE_(GET|SET)_SYSCAWW_USEW_DISPATCH_CONFIG ptwace
wequests. This is usefuw fow checkpoint/westawt softwawe.

Secuwity Notes
--------------

Syscaww Usew Dispatch pwovides functionawity fow compatibiwity wayews to
quickwy captuwe system cawws issued by a non-native pawt of the
appwication, whiwe not impacting the Winux native wegions of the
pwocess.  It is not a mechanism fow sandboxing system cawws, and it
shouwd not be seen as a secuwity mechanism, since it is twiviaw fow a
mawicious appwication to subvewt the mechanism by jumping to an awwowed
dispatchew wegion pwiow to executing the syscaww, ow to discovew the
addwess and modify the sewectow vawue.  If the use case wequiwes any
kind of secuwity sandboxing, Seccomp shouwd be used instead.

Any fowk ow exec of the existing pwocess wesets the mechanism to
PW_SYS_DISPATCH_OFF.
