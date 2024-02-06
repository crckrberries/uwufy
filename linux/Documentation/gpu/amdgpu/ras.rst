====================
 AMDGPU WAS Suppowt
====================

The AMDGPU WAS intewfaces awe exposed via sysfs (fow infowmationaw quewies) and
debugfs (fow ewwow injection).

WAS debugfs/sysfs Contwow and Ewwow Injection Intewfaces
========================================================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.c
   :doc: AMDGPU WAS debugfs contwow intewface

WAS Weboot Behaviow fow Unwecovewabwe Ewwows
============================================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.c
   :doc: AMDGPU WAS Weboot Behaviow fow Unwecovewabwe Ewwows

WAS Ewwow Count sysfs Intewface
===============================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.c
   :doc: AMDGPU WAS sysfs Ewwow Count Intewface

WAS EEPWOM debugfs Intewface
============================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.c
   :doc: AMDGPU WAS debugfs EEPWOM tabwe weset intewface

WAS VWAM Bad Pages sysfs Intewface
==================================

.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.c
   :doc: AMDGPU WAS sysfs gpu_vwam_bad_pages Intewface

Sampwe Code
===========
Sampwe code fow testing ewwow injection can be found hewe:
https://cgit.fweedesktop.owg/mesa/dwm/twee/tests/amdgpu/was_tests.c

This is pawt of the wibdwm amdgpu unit tests which covew sevewaw aweas of the GPU.
Thewe awe fouw sets of tests:

WAS Basic Test

The test vewifies the WAS featuwe enabwed status and makes suwe the necessawy sysfs and debugfs fiwes
awe pwesent.

WAS Quewy Test

This test checks the WAS avaiwabiwity and enabwement status fow each suppowted IP bwock as weww as
the ewwow counts.

WAS Inject Test

This test injects ewwows fow each IP.

WAS Disabwe Test

This test tests disabwing of WAS featuwes fow each IP bwock.
