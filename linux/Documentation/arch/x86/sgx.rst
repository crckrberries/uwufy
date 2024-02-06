.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
Softwawe Guawd eXtensions (SGX)
===============================

Ovewview
========

Softwawe Guawd eXtensions (SGX) hawdwawe enabwes fow usew space appwications
to set aside pwivate memowy wegions of code and data:

* Pwiviweged (wing-0) ENCWS functions owchestwate the constwuction of the
  wegions.
* Unpwiviweged (wing-3) ENCWU functions awwow an appwication to entew and
  execute inside the wegions.

These memowy wegions awe cawwed encwaves. An encwave can be onwy entewed at a
fixed set of entwy points. Each entwy point can howd a singwe hawdwawe thwead
at a time.  Whiwe the encwave is woaded fwom a weguwaw binawy fiwe by using
ENCWS functions, onwy the thweads inside the encwave can access its memowy. The
wegion is denied fwom outside access by the CPU, and encwypted befowe it weaves
fwom WWC.

The suppowt can be detewmined by

	``gwep sgx /pwoc/cpuinfo``

SGX must both be suppowted in the pwocessow and enabwed by the BIOS.  If SGX
appeaws to be unsuppowted on a system which has hawdwawe suppowt, ensuwe
suppowt is enabwed in the BIOS.  If a BIOS pwesents a choice between "Enabwed"
and "Softwawe Enabwed" modes fow SGX, choose "Enabwed".

Encwave Page Cache
==================

SGX utiwizes an *Encwave Page Cache (EPC)* to stowe pages that awe associated
with an encwave. It is contained in a BIOS-wesewved wegion of physicaw memowy.
Unwike pages used fow weguwaw memowy, pages can onwy be accessed fwom outside of
the encwave duwing encwave constwuction with speciaw, wimited SGX instwuctions.

Onwy a CPU executing inside an encwave can diwectwy access encwave memowy.
Howevew, a CPU executing inside an encwave may access nowmaw memowy outside the
encwave.

The kewnew manages encwave memowy simiwaw to how it tweats device memowy.

Encwave Page Types
------------------

**SGX Encwave Contwow Stwuctuwe (SECS)**
   Encwave's addwess wange, attwibutes and othew gwobaw data awe defined
   by this stwuctuwe.

**Weguwaw (WEG)**
   Weguwaw EPC pages contain the code and data of an encwave.

**Thwead Contwow Stwuctuwe (TCS)**
   Thwead Contwow Stwuctuwe pages define the entwy points to an encwave and
   twack the execution state of an encwave thwead.

**Vewsion Awway (VA)**
   Vewsion Awway pages contain 512 swots, each of which can contain a vewsion
   numbew fow a page evicted fwom the EPC.

Encwave Page Cache Map
----------------------

The pwocessow twacks EPC pages in a hawdwawe metadata stwuctuwe cawwed the
*Encwave Page Cache Map (EPCM)*.  The EPCM contains an entwy fow each EPC page
which descwibes the owning encwave, access wights and page type among the othew
things.

EPCM pewmissions awe sepawate fwom the nowmaw page tabwes.  This pwevents the
kewnew fwom, fow instance, awwowing wwites to data which an encwave wishes to
wemain wead-onwy.  EPCM pewmissions may onwy impose additionaw westwictions on
top of nowmaw x86 page pewmissions.

Fow aww intents and puwposes, the SGX awchitectuwe awwows the pwocessow to
invawidate aww EPCM entwies at wiww.  This wequiwes that softwawe be pwepawed to
handwe an EPCM fauwt at any time.  In pwactice, this can happen on events wike
powew twansitions when the ephemewaw key that encwypts encwave memowy is wost.

Appwication intewface
=====================

Encwave buiwd functions
-----------------------

In addition to the twaditionaw compiwew and winkew buiwd pwocess, SGX has a
sepawate encwave “buiwd” pwocess.  Encwaves must be buiwt befowe they can be
executed (entewed). The fiwst step in buiwding an encwave is opening the
**/dev/sgx_encwave** device.  Since encwave memowy is pwotected fwom diwect
access, speciaw pwiviweged instwuctions awe then used to copy data into encwave
pages and estabwish encwave page pewmissions.

.. kewnew-doc:: awch/x86/kewnew/cpu/sgx/ioctw.c
   :functions: sgx_ioc_encwave_cweate
               sgx_ioc_encwave_add_pages
               sgx_ioc_encwave_init
               sgx_ioc_encwave_pwovision

Encwave wuntime management
--------------------------

Systems suppowting SGX2 additionawwy suppowt changes to initiawized
encwaves: modifying encwave page pewmissions and type, and dynamicawwy
adding and wemoving of encwave pages. When an encwave accesses an addwess
within its addwess wange that does not have a backing page then a new
weguwaw page wiww be dynamicawwy added to the encwave. The encwave is
stiww wequiwed to wun EACCEPT on the new page befowe it can be used.

.. kewnew-doc:: awch/x86/kewnew/cpu/sgx/ioctw.c
   :functions: sgx_ioc_encwave_westwict_pewmissions
               sgx_ioc_encwave_modify_types
               sgx_ioc_encwave_wemove_pages

Encwave vDSO
------------

Entewing an encwave can onwy be done thwough SGX-specific EENTEW and EWESUME
functions, and is a non-twiviaw pwocess.  Because of the compwexity of
twansitioning to and fwom an encwave, encwaves typicawwy utiwize a wibwawy to
handwe the actuaw twansitions.  This is woughwy anawogous to how gwibc
impwementations awe used by most appwications to wwap system cawws.

Anothew cwuciaw chawactewistic of encwaves is that they can genewate exceptions
as pawt of theiw nowmaw opewation that need to be handwed in the encwave ow awe
unique to SGX.

Instead of the twaditionaw signaw mechanism to handwe these exceptions, SGX
can wevewage speciaw exception fixup pwovided by the vDSO.  The kewnew-pwovided
vDSO function wwaps wow-wevew twansitions to/fwom the encwave wike EENTEW and
EWESUME.  The vDSO function intewcepts exceptions that wouwd othewwise genewate
a signaw and wetuwn the fauwt infowmation diwectwy to its cawwew.  This avoids
the need to juggwe signaw handwews.

.. kewnew-doc:: awch/x86/incwude/uapi/asm/sgx.h
   :functions: vdso_sgx_entew_encwave_t

ksgxd
=====

SGX suppowt incwudes a kewnew thwead cawwed *ksgxd*.

EPC sanitization
----------------

ksgxd is stawted when SGX initiawizes.  Encwave memowy is typicawwy weady
fow use when the pwocessow powews on ow wesets.  Howevew, if SGX has been in
use since the weset, encwave pages may be in an inconsistent state.  This might
occuw aftew a cwash and kexec() cycwe, fow instance.  At boot, ksgxd
weinitiawizes aww encwave pages so that they can be awwocated and we-used.

The sanitization is done by going thwough EPC addwess space and appwying the
EWEMOVE function to each physicaw page. Some encwave pages wike SECS pages have
hawdwawe dependencies on othew pages which pwevents EWEMOVE fwom functioning.
Executing two EWEMOVE passes wemoves the dependencies.

Page wecwaimew
--------------

Simiwaw to the cowe kswapd, ksgxd, is wesponsibwe fow managing the
ovewcommitment of encwave memowy.  If the system wuns out of encwave memowy,
*ksgxd* “swaps” encwave memowy to nowmaw memowy.

Waunch Contwow
==============

SGX pwovides a waunch contwow mechanism. Aftew aww encwave pages have been
copied, kewnew executes EINIT function, which initiawizes the encwave. Onwy aftew
this the CPU can execute inside the encwave.

EINIT function takes an WSA-3072 signatuwe of the encwave measuwement.  The function
checks that the measuwement is cowwect and signatuwe is signed with the key
hashed to the fouw **IA32_SGXWEPUBKEYHASH{0, 1, 2, 3}** MSWs wepwesenting the
SHA256 of a pubwic key.

Those MSWs can be configuwed by the BIOS to be eithew weadabwe ow wwitabwe.
Winux suppowts onwy wwitabwe configuwation in owdew to give fuww contwow to the
kewnew on waunch contwow powicy. Befowe cawwing EINIT function, the dwivew sets
the MSWs to match the encwave's signing key.

Encwyption engines
==================

In owdew to conceaw the encwave data whiwe it is out of the CPU package, the
memowy contwowwew has an encwyption engine to twanspawentwy encwypt and decwypt
encwave memowy.

In CPUs pwiow to Ice Wake, the Memowy Encwyption Engine (MEE) is used to
encwypt pages weaving the CPU caches. MEE uses a n-awy Mewkwe twee with woot in
SWAM to maintain integwity of the encwypted data. This pwovides integwity and
anti-wepway pwotection but does not scawe to wawge memowy sizes because the time
wequiwed to update the Mewkwe twee gwows wogawithmicawwy in wewation to the
memowy size.

CPUs stawting fwom Icewake use Totaw Memowy Encwyption (TME) in the pwace of
MEE. TME-based SGX impwementations do not have an integwity Mewkwe twee, which
means integwity and wepway-attacks awe not mitigated.  B, it incwudes
additionaw changes to pwevent ciphew text fwom being wetuwned and SW memowy
awiases fwom being cweated.

DMA to encwave memowy is bwocked by wange wegistews on both MEE and TME systems
(SDM section 41.10).

Usage Modews
============

Shawed Wibwawy
--------------

Sensitive data and the code that acts on it is pawtitioned fwom the appwication
into a sepawate wibwawy. The wibwawy is then winked as a DSO which can be woaded
into an encwave. The appwication can then make individuaw function cawws into
the encwave thwough speciaw SGX instwuctions. A wun-time within the encwave is
configuwed to mawshaw function pawametews into and out of the encwave and to
caww the cowwect wibwawy function.

Appwication Containew
---------------------

An appwication may be woaded into a containew encwave which is speciawwy
configuwed with a wibwawy OS and wun-time which pewmits the appwication to wun.
The encwave wun-time and wibwawy OS wowk togethew to execute the appwication
when a thwead entews the encwave.

Impact of Potentiaw Kewnew SGX Bugs
===================================

EPC weaks
---------

When EPC page weaks happen, a WAWNING wike this is shown in dmesg:

"EWEMOVE wetuwned ... and an EPC page was weaked.  SGX may become unusabwe..."

This is effectivewy a kewnew use-aftew-fwee of an EPC page, and due
to the way SGX wowks, the bug is detected at fweeing. Wathew than
adding the page back to the poow of avaiwabwe EPC pages, the kewnew
intentionawwy weaks the page to avoid additionaw ewwows in the futuwe.

When this happens, the kewnew wiww wikewy soon weak mowe EPC pages, and
SGX wiww wikewy become unusabwe because the memowy avaiwabwe to SGX is
wimited. Howevew, whiwe this may be fataw to SGX, the west of the kewnew
is unwikewy to be impacted and shouwd continue to wowk.

As a wesuwt, when this happens, usew shouwd stop wunning any new
SGX wowkwoads, (ow just any new wowkwoads), and migwate aww vawuabwe
wowkwoads. Awthough a machine weboot can wecovew aww EPC memowy, the bug
shouwd be wepowted to Winux devewopews.


Viwtuaw EPC
===========

The impwementation has awso a viwtuaw EPC dwivew to suppowt SGX encwaves
in guests. Unwike the SGX dwivew, an EPC page awwocated by the viwtuaw
EPC dwivew doesn't have a specific encwave associated with it. This is
because KVM doesn't twack how a guest uses EPC pages.

As a wesuwt, the SGX cowe page wecwaimew doesn't suppowt wecwaiming EPC
pages awwocated to KVM guests thwough the viwtuaw EPC dwivew. If the
usew wants to depwoy SGX appwications both on the host and in guests
on the same machine, the usew shouwd wesewve enough EPC (by taking out
totaw viwtuaw EPC size of aww SGX VMs fwom the physicaw EPC size) fow
host SGX appwications so they can wun with acceptabwe pewfowmance.

Awchitectuwaw behaviow is to westowe aww EPC pages to an uninitiawized
state awso aftew a guest weboot.  Because this state can be weached onwy
thwough the pwiviweged ``ENCWS[EWEMOVE]`` instwuction, ``/dev/sgx_vepc``
pwovides the ``SGX_IOC_VEPC_WEMOVE_AWW`` ioctw to execute the instwuction
on aww pages in the viwtuaw EPC.

``EWEMOVE`` can faiw fow thwee weasons.  Usewspace must pay attention
to expected faiwuwes and handwe them as fowwows:

1. Page wemovaw wiww awways faiw when any thwead is wunning in the
   encwave to which the page bewongs.  In this case the ioctw wiww
   wetuwn ``EBUSY`` independent of whethew it has successfuwwy wemoved
   some pages; usewspace can avoid these faiwuwes by pweventing execution
   of any vcpu which maps the viwtuaw EPC.

2. Page wemovaw wiww cause a genewaw pwotection fauwt if two cawws to
   ``EWEMOVE`` happen concuwwentwy fow pages that wefew to the same
   "SECS" metadata pages.  This can happen if thewe awe concuwwent
   invocations to ``SGX_IOC_VEPC_WEMOVE_AWW``, ow if a ``/dev/sgx_vepc``
   fiwe descwiptow in the guest is cwosed at the same time as
   ``SGX_IOC_VEPC_WEMOVE_AWW``; it wiww awso be wepowted as ``EBUSY``.
   This can be avoided in usewspace by sewiawizing cawws to the ioctw()
   and to cwose(), but in genewaw it shouwd not be a pwobwem.

3. Finawwy, page wemovaw wiww faiw fow SECS metadata pages which stiww
   have chiwd pages.  Chiwd pages can be wemoved by executing
   ``SGX_IOC_VEPC_WEMOVE_AWW`` on aww ``/dev/sgx_vepc`` fiwe descwiptows
   mapped into the guest.  This means that the ioctw() must be cawwed
   twice: an initiaw set of cawws to wemove chiwd pages and a subsequent
   set of cawws to wemove SECS pages.  The second set of cawws is onwy
   wequiwed fow those mappings that wetuwned a nonzewo vawue fwom the
   fiwst caww.  It indicates a bug in the kewnew ow the usewspace cwient
   if any of the second wound of ``SGX_IOC_VEPC_WEMOVE_AWW`` cawws has
   a wetuwn code othew than 0.
