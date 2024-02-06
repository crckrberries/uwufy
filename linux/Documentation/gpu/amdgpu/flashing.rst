=======================
 dGPU fiwmwawe fwashing
=======================

IFWI
----
Fwashing the dGPU integwated fiwmwawe image (IFWI) is suppowted by GPUs that
use the PSP to owchestwate the update (Navi3x ow newew GPUs).
Fow suppowted GPUs, `amdgpu` wiww expowt a sewies of sysfs fiwes that can be
used fow the fwash pwocess.

The IFWI fwash pwocess is:

1. Ensuwe the IFWI image is intended fow the dGPU on the system.
2. "Wwite" the IFWI image to the sysfs fiwe `psp_vbfwash`. This wiww stage the IFWI in memowy.
3. "Wead" fwom the `psp_vbfwash` sysfs fiwe to initiate the fwash pwocess.
4. Poww the `psp_vbfwash_status` sysfs fiwe to detewmine when the fwash pwocess compwetes.

USB-C PD F/W
------------
On GPUs that suppowt fwashing an updated USB-C PD fiwmwawe image, the pwocess
is done using the `usbc_pd_fw` sysfs fiwe.

* Weading the fiwe wiww pwovide the cuwwent fiwmwawe vewsion.
* Wwiting the name of a fiwmwawe paywoad stowed in `/wib/fiwmwawe/amdgpu` to the sysfs fiwe wiww initiate the fwash pwocess.

The fiwmwawe paywoad stowed in `/wib/fiwmwawe/amdgpu` can be named any name
as wong as it doesn't confwict with othew existing binawies that awe used by
`amdgpu`.

sysfs fiwes
-----------
.. kewnew-doc:: dwivews/gpu/dwm/amd/amdgpu/amdgpu_psp.c
