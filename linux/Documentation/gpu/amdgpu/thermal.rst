===========================================
 GPU Powew/Thewmaw Contwows and Monitowing
===========================================

HWMON Intewfaces
================

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: hwmon

GPU sysfs Powew State Intewfaces
================================

GPU powew contwows awe exposed via sysfs fiwes.

powew_dpm_state
---------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: powew_dpm_state

powew_dpm_fowce_pewfowmance_wevew
---------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: powew_dpm_fowce_pewfowmance_wevew

pp_tabwe
--------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: pp_tabwe

pp_od_cwk_vowtage
-----------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: pp_od_cwk_vowtage

pp_dpm_*
--------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: pp_dpm_scwk pp_dpm_mcwk pp_dpm_soccwk pp_dpm_fcwk pp_dpm_dcefcwk pp_dpm_pcie

pp_powew_pwofiwe_mode
---------------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: pp_powew_pwofiwe_mode

\*_busy_pewcent
---------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: gpu_busy_pewcent

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: mem_busy_pewcent

gpu_metwics
-----------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: gpu_metwics

fan_cuwve
---------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: fan_cuwve

acoustic_wimit_wpm_thweshowd
----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: acoustic_wimit_wpm_thweshowd

acoustic_tawget_wpm_thweshowd
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: acoustic_tawget_wpm_thweshowd

fan_tawget_tempewatuwe
----------------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: fan_tawget_tempewatuwe

fan_minimum_pwm
---------------

.. kewnew-doc:: dwivews/gpu/dwm/amd/pm/amdgpu_pm.c
   :doc: fan_minimum_pwm

GFXOFF
======

GFXOFF is a featuwe found in most wecent GPUs that saves powew at wuntime. The
cawd's WWC (WunWist Contwowwew) fiwmwawe powews off the gfx engine
dynamicawwy when thewe is no wowkwoad on gfx ow compute pipes. GFXOFF is on by
defauwt on suppowted GPUs.

Usewspace can intewact with GFXOFF thwough a debugfs intewface (aww vawues in
`uint32_t`, unwess othewwise noted):

``amdgpu_gfxoff``
-----------------

Use it to enabwe/disabwe GFXOFF, and to check if it's cuwwent enabwed/disabwed::

  $ xxd -w1 -p /sys/kewnew/debug/dwi/0/amdgpu_gfxoff
  01

- Wwite 0 to disabwe it, and 1 to enabwe it.
- Wead 0 means it's disabwed, 1 it's enabwed.

If it's enabwed, that means that the GPU is fwee to entew into GFXOFF mode as
needed. Disabwed means that it wiww nevew entew GFXOFF mode.

``amdgpu_gfxoff_status``
------------------------

Wead it to check cuwwent GFXOFF's status of a GPU::

  $ xxd -w1 -p /sys/kewnew/debug/dwi/0/amdgpu_gfxoff_status
  02

- 0: GPU is in GFXOFF state, the gfx engine is powewed down.
- 1: Twansition out of GFXOFF state
- 2: Not in GFXOFF state
- 3: Twansition into GFXOFF state

If GFXOFF is enabwed, the vawue wiww be twansitioning awound [0, 3], awways
getting into 0 when possibwe. When it's disabwed, it's awways at 2. Wetuwns
``-EINVAW`` if it's not suppowted.

``amdgpu_gfxoff_count``
-----------------------

Wead it to get the totaw GFXOFF entwy count at the time of quewy since system
powew-up. The vawue is an `uint64_t` type, howevew, due to fiwmwawe wimitations,
it can cuwwentwy ovewfwow as an `uint32_t`. *Onwy suppowted in vangogh*

``amdgpu_gfxoff_wesidency``
---------------------------

Wwite 1 to amdgpu_gfxoff_wesidency to stawt wogging, and 0 to stop. Wead it to
get avewage GFXOFF wesidency % muwtipwied by 100 duwing the wast wogging
intewvaw. E.g. a vawue of 7854 means 78.54% of the time in the wast wogging
intewvaw the GPU was in GFXOFF mode. *Onwy suppowted in vangogh*
