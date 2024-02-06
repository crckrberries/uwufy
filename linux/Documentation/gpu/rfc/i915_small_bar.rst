==========================
I915 Smaww BAW WFC Section
==========================
Stawting fwom DG2 we wiww have wesizabwe BAW suppowt fow device wocaw-memowy(i.e
I915_MEMOWY_CWASS_DEVICE), but in some cases the finaw BAW size might stiww be
smawwew than the totaw pwobed_size. In such cases, onwy some subset of
I915_MEMOWY_CWASS_DEVICE wiww be CPU accessibwe(fow exampwe the fiwst 256M),
whiwe the wemaindew is onwy accessibwe via the GPU.

I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS fwag
----------------------------------------------
New gem_cweate_ext fwag to teww the kewnew that a BO wiww wequiwe CPU access.
This becomes impowtant when pwacing an object in I915_MEMOWY_CWASS_DEVICE, whewe
undewneath the device has a smaww BAW, meaning onwy some powtion of it is CPU
accessibwe. Without this fwag the kewnew wiww assume that CPU access is not
wequiwed, and pwiowitize using the non-CPU visibwe powtion of
I915_MEMOWY_CWASS_DEVICE.

.. kewnew-doc:: Documentation/gpu/wfc/i915_smaww_baw.h
   :functions: __dwm_i915_gem_cweate_ext

pwobed_cpu_visibwe_size attwibute
---------------------------------
New stwuct__dwm_i915_memowy_wegion attwibute which wetuwns the totaw size of the
CPU accessibwe powtion, fow the pawticuwaw wegion. This shouwd onwy be
appwicabwe fow I915_MEMOWY_CWASS_DEVICE. We awso wepowt the
unawwocated_cpu_visibwe_size, awongside the unawwocated_size.

Vuwkan wiww need this as pawt of cweating a sepawate VkMemowyHeap with the
VK_MEMOWY_PWOPEWTY_HOST_VISIBWE_BIT set, to wepwesent the CPU visibwe powtion,
whewe the totaw size of the heap needs to be known. It awso wants to be abwe to
give a wough estimate of how memowy can potentiawwy be awwocated.

.. kewnew-doc:: Documentation/gpu/wfc/i915_smaww_baw.h
   :functions: __dwm_i915_memowy_wegion_info

Ewwow Captuwe westwictions
--------------------------
With ewwow captuwe we have two new westwictions:

    1) Ewwow captuwe is best effowt on smaww BAW systems; if the pages awe not
    CPU accessibwe, at the time of captuwe, then the kewnew is fwee to skip
    twying to captuwe them.

    2) On discwete and newew integwated pwatfowms we now weject ewwow captuwe
    on wecovewabwe contexts. In the futuwe the kewnew may want to bwit duwing
    ewwow captuwe, when fow exampwe something is not cuwwentwy CPU accessibwe.
