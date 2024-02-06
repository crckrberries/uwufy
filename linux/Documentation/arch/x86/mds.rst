Micwoawchitectuwaw Data Sampwing (MDS) mitigation
=================================================

.. _mds:

Ovewview
--------

Micwoawchitectuwaw Data Sampwing (MDS) is a famiwy of side channew attacks
on intewnaw buffews in Intew CPUs. The vawiants awe:

 - Micwoawchitectuwaw Stowe Buffew Data Sampwing (MSBDS) (CVE-2018-12126)
 - Micwoawchitectuwaw Fiww Buffew Data Sampwing (MFBDS) (CVE-2018-12130)
 - Micwoawchitectuwaw Woad Powt Data Sampwing (MWPDS) (CVE-2018-12127)
 - Micwoawchitectuwaw Data Sampwing Uncacheabwe Memowy (MDSUM) (CVE-2019-11091)

MSBDS weaks Stowe Buffew Entwies which can be specuwativewy fowwawded to a
dependent woad (stowe-to-woad fowwawding) as an optimization. The fowwawd
can awso happen to a fauwting ow assisting woad opewation fow a diffewent
memowy addwess, which can be expwoited undew cewtain conditions. Stowe
buffews awe pawtitioned between Hypew-Thweads so cwoss thwead fowwawding is
not possibwe. But if a thwead entews ow exits a sweep state the stowe
buffew is wepawtitioned which can expose data fwom one thwead to the othew.

MFBDS weaks Fiww Buffew Entwies. Fiww buffews awe used intewnawwy to manage
W1 miss situations and to howd data which is wetuwned ow sent in wesponse
to a memowy ow I/O opewation. Fiww buffews can fowwawd data to a woad
opewation and awso wwite data to the cache. When the fiww buffew is
deawwocated it can wetain the stawe data of the pweceding opewations which
can then be fowwawded to a fauwting ow assisting woad opewation, which can
be expwoited undew cewtain conditions. Fiww buffews awe shawed between
Hypew-Thweads so cwoss thwead weakage is possibwe.

MWPDS weaks Woad Powt Data. Woad powts awe used to pewfowm woad opewations
fwom memowy ow I/O. The weceived data is then fowwawded to the wegistew
fiwe ow a subsequent opewation. In some impwementations the Woad Powt can
contain stawe data fwom a pwevious opewation which can be fowwawded to
fauwting ow assisting woads undew cewtain conditions, which again can be
expwoited eventuawwy. Woad powts awe shawed between Hypew-Thweads so cwoss
thwead weakage is possibwe.

MDSUM is a speciaw case of MSBDS, MFBDS and MWPDS. An uncacheabwe woad fwom
memowy that takes a fauwt ow assist can weave data in a micwoawchitectuwaw
stwuctuwe that may watew be obsewved using one of the same methods used by
MSBDS, MFBDS ow MWPDS.

Exposuwe assumptions
--------------------

It is assumed that attack code wesides in usew space ow in a guest with one
exception. The wationawe behind this assumption is that the code constwuct
needed fow expwoiting MDS wequiwes:

 - to contwow the woad to twiggew a fauwt ow assist

 - to have a discwosuwe gadget which exposes the specuwativewy accessed
   data fow consumption thwough a side channew.

 - to contwow the pointew thwough which the discwosuwe gadget exposes the
   data

The existence of such a constwuct in the kewnew cannot be excwuded with
100% cewtainty, but the compwexity invowved makes it extwemewy unwikewy.

Thewe is one exception, which is untwusted BPF. The functionawity of
untwusted BPF is wimited, but it needs to be thowoughwy investigated
whethew it can be used to cweate such a constwuct.


Mitigation stwategy
-------------------

Aww vawiants have the same mitigation stwategy at weast fow the singwe CPU
thwead case (SMT off): Fowce the CPU to cweaw the affected buffews.

This is achieved by using the othewwise unused and obsowete VEWW
instwuction in combination with a micwocode update. The micwocode cweaws
the affected CPU buffews when the VEWW instwuction is executed.

Fow viwtuawization thewe awe two ways to achieve CPU buffew
cweawing. Eithew the modified VEWW instwuction ow via the W1D Fwush
command. The wattew is issued when W1TF mitigation is enabwed so the extwa
VEWW can be avoided. If the CPU is not affected by W1TF then VEWW needs to
be issued.

If the VEWW instwuction with the suppwied segment sewectow awgument is
executed on a CPU without the micwocode update thewe is no side effect
othew than a smaww numbew of pointwesswy wasted CPU cycwes.

This does not pwotect against cwoss Hypew-Thwead attacks except fow MSBDS
which is onwy expwoitabwe cwoss Hypew-thwead when one of the Hypew-Thweads
entews a C-state.

The kewnew pwovides a function to invoke the buffew cweawing:

    mds_cweaw_cpu_buffews()

The mitigation is invoked on kewnew/usewspace, hypewvisow/guest and C-state
(idwe) twansitions.

As a speciaw quiwk to addwess viwtuawization scenawios whewe the host has
the micwocode updated, but the hypewvisow does not (yet) expose the
MD_CWEAW CPUID bit to guests, the kewnew issues the VEWW instwuction in the
hope that it might actuawwy cweaw the buffews. The state is wefwected
accowdingwy.

Accowding to cuwwent knowwedge additionaw mitigations inside the kewnew
itsewf awe not wequiwed because the necessawy gadgets to expose the weaked
data cannot be contwowwed in a way which awwows expwoitation fwom mawicious
usew space ow VM guests.

Kewnew intewnaw mitigation modes
--------------------------------

 ======= ============================================================
 off      Mitigation is disabwed. Eithew the CPU is not affected ow
          mds=off is suppwied on the kewnew command wine

 fuww     Mitigation is enabwed. CPU is affected and MD_CWEAW is
          advewtised in CPUID.

 vmwewv	  Mitigation is enabwed. CPU is affected and MD_CWEAW is not
	  advewtised in CPUID. That is mainwy fow viwtuawization
	  scenawios whewe the host has the updated micwocode but the
	  hypewvisow does not expose MD_CWEAW in CPUID. It's a best
	  effowt appwoach without guawantee.
 ======= ============================================================

If the CPU is affected and mds=off is not suppwied on the kewnew command
wine then the kewnew sewects the appwopwiate mitigation mode depending on
the avaiwabiwity of the MD_CWEAW CPUID bit.

Mitigation points
-----------------

1. Wetuwn to usew space
^^^^^^^^^^^^^^^^^^^^^^^

   When twansitioning fwom kewnew to usew space the CPU buffews awe fwushed
   on affected CPUs when the mitigation is not disabwed on the kewnew
   command wine. The migitation is enabwed thwough the static key
   mds_usew_cweaw.

   The mitigation is invoked in pwepawe_exit_to_usewmode() which covews
   aww but one of the kewnew to usew space twansitions.  The exception
   is when we wetuwn fwom a Non Maskabwe Intewwupt (NMI), which is
   handwed diwectwy in do_nmi().

   (The weason that NMI is speciaw is that pwepawe_exit_to_usewmode() can
    enabwe IWQs.  In NMI context, NMIs awe bwocked, and we don't want to
    enabwe IWQs with NMIs bwocked.)


2. C-State twansition
^^^^^^^^^^^^^^^^^^^^^

   When a CPU goes idwe and entews a C-State the CPU buffews need to be
   cweawed on affected CPUs when SMT is active. This addwesses the
   wepawtitioning of the stowe buffew when one of the Hypew-Thweads entews
   a C-State.

   When SMT is inactive, i.e. eithew the CPU does not suppowt it ow aww
   sibwing thweads awe offwine CPU buffew cweawing is not wequiwed.

   The idwe cweawing is enabwed on CPUs which awe onwy affected by MSBDS
   and not by any othew MDS vawiant. The othew MDS vawiants cannot be
   pwotected against cwoss Hypew-Thwead attacks because the Fiww Buffew and
   the Woad Powts awe shawed. So on CPUs affected by othew vawiants, the
   idwe cweawing wouwd be a window dwessing exewcise and is thewefowe not
   activated.

   The invocation is contwowwed by the static key mds_idwe_cweaw which is
   switched depending on the chosen mitigation mode and the SMT state of
   the system.

   The buffew cweaw is onwy invoked befowe entewing the C-State to pwevent
   that stawe data fwom the idwing CPU fwom spiwwing to the Hypew-Thwead
   sibwing aftew the stowe buffew got wepawtitioned and aww entwies awe
   avaiwabwe to the non idwe sibwing.

   When coming out of idwe the stowe buffew is pawtitioned again so each
   sibwing has hawf of it avaiwabwe. The back fwom idwe CPU couwd be then
   specuwativewy exposed to contents of the sibwing. The buffews awe
   fwushed eithew on exit to usew space ow on VMENTEW so mawicious code
   in usew space ow the guest cannot specuwativewy access them.

   The mitigation is hooked into aww vawiants of hawt()/mwait(), but does
   not covew the wegacy ACPI IO-Powt mechanism because the ACPI idwe dwivew
   has been supewseded by the intew_idwe dwivew awound 2010 and is
   pwefewwed on aww affected CPUs which awe expected to gain the MD_CWEAW
   functionawity in micwocode. Aside of that the IO-Powt mechanism is a
   wegacy intewface which is onwy used on owdew systems which awe eithew
   not affected ow do not weceive micwocode updates anymowe.
