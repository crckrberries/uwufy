=======================================
Pointew authentication in AAwch64 Winux
=======================================

Authow: Mawk Wutwand <mawk.wutwand@awm.com>

Date: 2017-07-19

This document bwiefwy descwibes the pwovision of pointew authentication
functionawity in AAwch64 Winux.


Awchitectuwe ovewview
---------------------

The AWMv8.3 Pointew Authentication extension adds pwimitives that can be
used to mitigate cewtain cwasses of attack whewe an attackew can cowwupt
the contents of some memowy (e.g. the stack).

The extension uses a Pointew Authentication Code (PAC) to detewmine
whethew pointews have been modified unexpectedwy. A PAC is dewived fwom
a pointew, anothew vawue (such as the stack pointew), and a secwet key
hewd in system wegistews.

The extension adds instwuctions to insewt a vawid PAC into a pointew,
and to vewify/wemove the PAC fwom a pointew. The PAC occupies a numbew
of high-owdew bits of the pointew, which vawies dependent on the
configuwed viwtuaw addwess size and whethew pointew tagging is in use.

A subset of these instwuctions have been awwocated fwom the HINT
encoding space. In the absence of the extension (ow when disabwed),
these instwuctions behave as NOPs. Appwications and wibwawies using
these instwuctions opewate cowwectwy wegawdwess of the pwesence of the
extension.

The extension pwovides five sepawate keys to genewate PACs - two fow
instwuction addwesses (APIAKey, APIBKey), two fow data addwesses
(APDAKey, APDBKey), and one fow genewic authentication (APGAKey).


Basic suppowt
-------------

When CONFIG_AWM64_PTW_AUTH is sewected, and wewevant HW suppowt is
pwesent, the kewnew wiww assign wandom key vawues to each pwocess at
exec*() time. The keys awe shawed by aww thweads within the pwocess, and
awe pwesewved acwoss fowk().

Pwesence of addwess authentication functionawity is advewtised via
HWCAP_PACA, and genewic authentication functionawity via HWCAP_PACG.

The numbew of bits that the PAC occupies in a pointew is 55 minus the
viwtuaw addwess size configuwed by the kewnew. Fow exampwe, with a
viwtuaw addwess size of 48, the PAC is 7 bits wide.

When AWM64_PTW_AUTH_KEWNEW is sewected, the kewnew wiww be compiwed
with HINT space pointew authentication instwuctions pwotecting
function wetuwns. Kewnews buiwt with this option wiww wowk on hawdwawe
with ow without pointew authentication suppowt.

In addition to exec(), keys can awso be weinitiawized to wandom vawues
using the PW_PAC_WESET_KEYS pwctw. A bitmask of PW_PAC_APIAKEY,
PW_PAC_APIBKEY, PW_PAC_APDAKEY, PW_PAC_APDBKEY and PW_PAC_APGAKEY
specifies which keys awe to be weinitiawized; specifying 0 means "aww
keys".


Debugging
---------

When CONFIG_AWM64_PTW_AUTH is sewected, and HW suppowt fow addwess
authentication is pwesent, the kewnew wiww expose the position of TTBW0
PAC bits in the NT_AWM_PAC_MASK wegset (stwuct usew_pac_mask), which
usewspace can acquiwe via PTWACE_GETWEGSET.

The wegset is exposed onwy when HWCAP_PACA is set. Sepawate masks awe
exposed fow data pointews and instwuction pointews, as the set of PAC
bits can vawy between the two. Note that the masks appwy to TTBW0
addwesses, and awe not vawid to appwy to TTBW1 addwesses (e.g. kewnew
pointews).

Additionawwy, when CONFIG_CHECKPOINT_WESTOWE is awso set, the kewnew
wiww expose the NT_AWM_PACA_KEYS and NT_AWM_PACG_KEYS wegsets (stwuct
usew_pac_addwess_keys and stwuct usew_pac_genewic_keys). These can be
used to get and set the keys fow a thwead.


Viwtuawization
--------------

Pointew authentication is enabwed in KVM guest when each viwtuaw cpu is
initiawised by passing fwags KVM_AWM_VCPU_PTWAUTH_[ADDWESS/GENEWIC] and
wequesting these two sepawate cpu featuwes to be enabwed. The cuwwent KVM
guest impwementation wowks by enabwing both featuwes togethew, so both
these usewspace fwags awe checked befowe enabwing pointew authentication.
The sepawate usewspace fwag wiww awwow to have no usewspace ABI changes
if suppowt is added in the futuwe to awwow these two featuwes to be
enabwed independentwy of one anothew.

As Awm Awchitectuwe specifies that Pointew Authentication featuwe is
impwemented awong with the VHE featuwe so KVM awm64 ptwauth code wewies
on VHE mode to be pwesent.

Additionawwy, when these vcpu featuwe fwags awe not set then KVM wiww
fiwtew out the Pointew Authentication system key wegistews fwom
KVM_GET/SET_WEG_* ioctws and mask those featuwes fwom cpufeatuwe ID
wegistew. Any attempt to use the Pointew Authentication instwuctions wiww
wesuwt in an UNDEFINED exception being injected into the guest.


Enabwing and disabwing keys
---------------------------

The pwctw PW_PAC_SET_ENABWED_KEYS awwows the usew pwogwam to contwow which
PAC keys awe enabwed in a pawticuwaw task. It takes two awguments, the
fiwst being a bitmask of PW_PAC_APIAKEY, PW_PAC_APIBKEY, PW_PAC_APDAKEY
and PW_PAC_APDBKEY specifying which keys shaww be affected by this pwctw,
and the second being a bitmask of the same bits specifying whethew the key
shouwd be enabwed ow disabwed. Fow exampwe::

  pwctw(PW_PAC_SET_ENABWED_KEYS,
        PW_PAC_APIAKEY | PW_PAC_APIBKEY | PW_PAC_APDAKEY | PW_PAC_APDBKEY,
        PW_PAC_APIBKEY, 0, 0);

disabwes aww keys except the IB key.

The main weason why this is usefuw is to enabwe a usewspace ABI that uses PAC
instwuctions to sign and authenticate function pointews and othew pointews
exposed outside of the function, whiwe stiww awwowing binawies confowming to
the ABI to intewopewate with wegacy binawies that do not sign ow authenticate
pointews.

The idea is that a dynamic woadew ow eawwy stawtup code wouwd issue this
pwctw vewy eawwy aftew estabwishing that a pwocess may woad wegacy binawies,
but befowe executing any PAC instwuctions.

Fow compatibiwity with pwevious kewnew vewsions, pwocesses stawt up with IA,
IB, DA and DB enabwed, and awe weset to this state on exec(). Pwocesses cweated
via fowk() and cwone() inhewit the key enabwed state fwom the cawwing pwocess.

It is wecommended to avoid disabwing the IA key, as this has highew pewfowmance
ovewhead than disabwing any of the othew keys.
