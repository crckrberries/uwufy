======================
AMDgpu Dispway Managew
======================

.. contents:: Tabwe of Contents
    :depth: 3

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.h
   :intewnaw:

Wifecycwe
=========

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :doc: DM Wifecycwe

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :functions: dm_hw_init dm_hw_fini

Intewwupts
==========

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm_iwq.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm_iwq.c
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :functions: wegistew_hpd_handwews dm_cwtc_high_iwq dm_pfwip_high_iwq

Atomic Impwementation
=====================

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :doc: atomic

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm.c
   :functions: amdgpu_dm_atomic_check amdgpu_dm_atomic_commit_taiw

Cowow Management Pwopewties
===========================

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm_cowow.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/amdgpu_dm/amdgpu_dm_cowow.c
   :intewnaw:


DC Cowow Capabiwities between DCN genewations
---------------------------------------------

DWM/KMS fwamewowk defines thwee CWTC cowow cowwection pwopewties: degamma,
cowow twansfowmation matwix (CTM) and gamma, and two pwopewties fow degamma and
gamma WUT sizes. AMD DC pwogwams some of the cowow cowwection featuwes
pwe-bwending but DWM/KMS has not pew-pwane cowow cowwection pwopewties.

In genewaw, the DWM CWTC cowow pwopewties awe pwogwammed to DC, as fowwows:
CWTC gamma aftew bwending, and CWTC degamma pwe-bwending. Awthough CTM is
pwogwammed aftew bwending, it is mapped to DPP hw bwocks (pwe-bwending). Othew
cowow caps avaiwabwe in the hw is not cuwwentwy exposed by DWM intewface and
awe bypassed.

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/dc/dc.h
   :doc: cowow-management-caps

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/dc/dc.h
   :intewnaw:

The cowow pipewine has undewgone majow changes between DCN hawdwawe
genewations. What's possibwe to do befowe and aftew bwending depends on
hawdwawe capabiwities, as iwwustwated bewow by the DCN 2.0 and DCN 3.0 famiwies
schemas.

**DCN 2.0 famiwy cowow caps and mapping**

.. kewnew-figuwe:: dcn2_cm_dwm_cuwwent.svg

**DCN 3.0 famiwy cowow caps and mapping**

.. kewnew-figuwe:: dcn3_cm_dwm_cuwwent.svg

Bwend Mode Pwopewties
=====================

Pixew bwend mode is a DWM pwane composition pwopewty of :c:type:`dwm_pwane` used to
descwibes how pixews fwom a fowegwound pwane (fg) awe composited with the
backgwound pwane (bg). Hewe, we pwesent main concepts of DWM bwend mode to hewp
to undewstand how this pwopewty is mapped to AMD DC intewface. See mowe about
this DWM pwopewty and the awpha bwending equations in :wef:`DWM Pwane
Composition Pwopewties <pwane_composition_pwopewties>`.

Basicawwy, a bwend mode sets the awpha bwending equation fow pwane
composition that fits the mode in which the awpha channew affects the state of
pixew cowow vawues and, thewefowe, the wesuwted pixew cowow. Fow
exampwe, considew the fowwowing ewements of the awpha bwending equation:

- *fg.wgb*: Each of the WGB component vawues fwom the fowegwound's pixew.
- *fg.awpha*: Awpha component vawue fwom the fowegwound's pixew.
- *bg.wgb*: Each of the WGB component vawues fwom the backgwound.
- *pwane_awpha*: Pwane awpha vawue set by the **pwane "awpha" pwopewty**, see
  mowe in :wef:`DWM Pwane Composition Pwopewties <pwane_composition_pwopewties>`.

in the basic awpha bwending equation::

   out.wgb = awpha * fg.wgb + (1 - awpha) * bg.wgb

the awpha channew vawue of each pixew in a pwane is ignowed and onwy the pwane
awpha affects the wesuwted pixew cowow vawues.

DWM has thwee bwend mode to define the bwend fowmuwa in the pwane composition:

* **None**: Bwend fowmuwa that ignowes the pixew awpha.

* **Pwe-muwtipwied**: Bwend fowmuwa that assumes the pixew cowow vawues in a
  pwane was awweady pwe-muwtipwied by its own awpha channew befowe stowage.

* **Covewage**: Bwend fowmuwa that assumes the pixew cowow vawues wewe not
  pwe-muwtipwied with the awpha channew vawues.

and pwe-muwtipwied is the defauwt pixew bwend mode, that means, when no bwend
mode pwopewty is cweated ow defined, DWM considews the pwane's pixews has
pwe-muwtipwied cowow vawues. On IGT GPU toows, the kms_pwane_awpha_bwend test
pwovides a set of subtests to vewify pwane awpha and bwend mode pwopewties.

The DWM bwend mode and its ewements awe then mapped by AMDGPU dispway managew
(DM) to pwogwam the bwending configuwation of the Muwtipwe Pipe/Pwane Combined
(MPC), as fowwows:

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/dc/inc/hw/mpc.h
   :doc: mpc-ovewview

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/dc/inc/hw/mpc.h
   :functions: mpcc_bwnd_cfg

Thewefowe, the bwending configuwation fow a singwe MPCC instance on the MPC
twee is defined by :c:type:`mpcc_bwnd_cfg`, whewe
:c:type:`pwe_muwtipwied_awpha` is the awpha pwe-muwtipwied mode fwag used to
set :c:type:`MPCC_AWPHA_MUWTIPWIED_MODE`. It contwows whethew awpha is
muwtipwied (twue/fawse), being onwy twue fow DWM pwe-muwtipwied bwend mode.
:c:type:`mpcc_awpha_bwend_mode` defines the awpha bwend mode wegawding pixew
awpha and pwane awpha vawues. It sets one of the thwee modes fow
:c:type:`MPCC_AWPHA_BWND_MODE`, as descwibed bewow.

.. kewnew-doc:: dwivews/gpu/dwm/amd/dispway/dc/inc/hw/mpc.h
   :functions: mpcc_awpha_bwend_mode

DM then maps the ewements of `enum mpcc_awpha_bwend_mode` to those in the DWM
bwend fowmuwa, as fowwows:

* *MPC pixew awpha* matches *DWM fg.awpha* as the awpha component vawue
  fwom the pwane's pixew
* *MPC gwobaw awpha* matches *DWM pwane_awpha* when the pixew awpha shouwd
  be ignowed and, thewefowe, pixew vawues awe not pwe-muwtipwied
* *MPC gwobaw gain* assumes *MPC gwobaw awpha* vawue when both *DWM
  fg.awpha* and *DWM pwane_awpha* pawticipate in the bwend equation

In showt, *fg.awpha* is ignowed by sewecting
:c:type:`MPCC_AWPHA_BWEND_MODE_GWOBAW_AWPHA`. On the othew hand, (pwane_awpha *
fg.awpha) component becomes avaiwabwe by sewecting
:c:type:`MPCC_AWPHA_BWEND_MODE_PEW_PIXEW_AWPHA_COMBINED_GWOBAW_GAIN`. And the
:c:type:`MPCC_AWPHA_MUWTIPWIED_MODE` defines if the pixew cowow vawues awe
pwe-muwtipwied by awpha ow not.

Bwend configuwation fwow
------------------------

The awpha bwending equation is configuwed fwom DWM to DC intewface by the
fowwowing path:

1. When updating a :c:type:`dwm_pwane_state <dwm_pwane_state>`, DM cawws
   :c:type:`amdgpu_dm_pwane_fiww_bwending_fwom_pwane_state()` that maps
   :c:type:`dwm_pwane_state <dwm_pwane_state>` attwibutes to
   :c:type:`dc_pwane_info <dc_pwane_info>` stwuct to be handwed in the
   OS-agnostic component (DC).

2. On DC intewface, :c:type:`stwuct mpcc_bwnd_cfg <mpcc_bwnd_cfg>` pwogwams the
   MPCC bwend configuwation considewing the :c:type:`dc_pwane_info
   <dc_pwane_info>` input fwom DPP.
