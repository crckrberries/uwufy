#ifndef __swc_common_sdk_nvidia_inc_nvos_h__
#define __swc_common_sdk_nvidia_inc_nvos_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 1993-2023 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 * SPDX-Wicense-Identifiew: MIT
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#define NVOS02_FWAGS_PHYSICAWITY                                   7:4
#define NVOS02_FWAGS_PHYSICAWITY_CONTIGUOUS                        (0x00000000)
#define NVOS02_FWAGS_PHYSICAWITY_NONCONTIGUOUS                     (0x00000001)
#define NVOS02_FWAGS_WOCATION                                      11:8
#define NVOS02_FWAGS_WOCATION_PCI                                  (0x00000000)
#define NVOS02_FWAGS_WOCATION_AGP                                  (0x00000001)
#define NVOS02_FWAGS_WOCATION_VIDMEM                               (0x00000002)
#define NVOS02_FWAGS_COHEWENCY                                     15:12
#define NVOS02_FWAGS_COHEWENCY_UNCACHED                            (0x00000000)
#define NVOS02_FWAGS_COHEWENCY_CACHED                              (0x00000001)
#define NVOS02_FWAGS_COHEWENCY_WWITE_COMBINE                       (0x00000002)
#define NVOS02_FWAGS_COHEWENCY_WWITE_THWOUGH                       (0x00000003)
#define NVOS02_FWAGS_COHEWENCY_WWITE_PWOTECT                       (0x00000004)
#define NVOS02_FWAGS_COHEWENCY_WWITE_BACK                          (0x00000005)
#define NVOS02_FWAGS_AWWOC                                         17:16
#define NVOS02_FWAGS_AWWOC_NONE                                    (0x00000001)
#define NVOS02_FWAGS_GPU_CACHEABWE                                 18:18
#define NVOS02_FWAGS_GPU_CACHEABWE_NO                              (0x00000000)
#define NVOS02_FWAGS_GPU_CACHEABWE_YES                             (0x00000001)

#define NVOS02_FWAGS_KEWNEW_MAPPING                                19:19
#define NVOS02_FWAGS_KEWNEW_MAPPING_NO_MAP                         (0x00000000)
#define NVOS02_FWAGS_KEWNEW_MAPPING_MAP                            (0x00000001)
#define NVOS02_FWAGS_AWWOC_NISO_DISPWAY                            20:20
#define NVOS02_FWAGS_AWWOC_NISO_DISPWAY_NO                         (0x00000000)
#define NVOS02_FWAGS_AWWOC_NISO_DISPWAY_YES                        (0x00000001)

#define NVOS02_FWAGS_AWWOC_USEW_WEAD_ONWY                          21:21
#define NVOS02_FWAGS_AWWOC_USEW_WEAD_ONWY_NO                       (0x00000000)
#define NVOS02_FWAGS_AWWOC_USEW_WEAD_ONWY_YES                      (0x00000001)

#define NVOS02_FWAGS_AWWOC_DEVICE_WEAD_ONWY                        22:22
#define NVOS02_FWAGS_AWWOC_DEVICE_WEAD_ONWY_NO                     (0x00000000)
#define NVOS02_FWAGS_AWWOC_DEVICE_WEAD_ONWY_YES                    (0x00000001)

#define NVOS02_FWAGS_PEEW_MAP_OVEWWIDE                             23:23
#define NVOS02_FWAGS_PEEW_MAP_OVEWWIDE_DEFAUWT                     (0x00000000)
#define NVOS02_FWAGS_PEEW_MAP_OVEWWIDE_WEQUIWED                    (0x00000001)

#define NVOS02_FWAGS_AWWOC_TYPE_SYNCPOINT                          24:24
#define NVOS02_FWAGS_AWWOC_TYPE_SYNCPOINT_APEWTUWE                 (0x00000001)

#define NVOS02_FWAGS_MEMOWY_PWOTECTION                             26:25
#define NVOS02_FWAGS_MEMOWY_PWOTECTION_DEFAUWT                     (0x00000000)
#define NVOS02_FWAGS_MEMOWY_PWOTECTION_PWOTECTED                   (0x00000001)
#define NVOS02_FWAGS_MEMOWY_PWOTECTION_UNPWOTECTED                 (0x00000002)

#define NVOS02_FWAGS_MAPPING                                       31:30
#define NVOS02_FWAGS_MAPPING_DEFAUWT                               (0x00000000)
#define NVOS02_FWAGS_MAPPING_NO_MAP                                (0x00000001)
#define NVOS02_FWAGS_MAPPING_NEVEW_MAP                             (0x00000002)

#define NV01_EVENT_CWIENT_WM                                       (0x04000000)

typedef stwuct
{
    NvV32    channewInstance;            // One of the n channew instances of a given channew type.
                                         // Note that cowe channew has onwy one instance
                                         // whiwe aww othews have two (one pew head).
    NvHandwe hObjectBuffew;              // ctx dma handwe fow DMA push buffew
    NvHandwe hObjectNotify;              // ctx dma handwe fow an awea (of type NvNotification defined in sdk/nvidia/inc/nvtypes.h) whewe WM can wwite ewwows/notifications
    NvU32    offset;                     // Initiaw offset fow put/get, usuawwy zewo.
    NvP64    pContwow NV_AWIGN_BYTES(8); // pContwow gives viwt addw of UDISP GET/PUT wegs

    NvU32    fwags;
#define NV50VAIO_CHANNEWDMA_AWWOCATION_FWAGS_CONNECT_PB_AT_GWAB                1:1
#define NV50VAIO_CHANNEWDMA_AWWOCATION_FWAGS_CONNECT_PB_AT_GWAB_YES            0x00000000
#define NV50VAIO_CHANNEWDMA_AWWOCATION_FWAGS_CONNECT_PB_AT_GWAB_NO             0x00000001

} NV50VAIO_CHANNEWDMA_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvV32    channewInstance;            // One of the n channew instances of a given channew type.
                                         // Aww PIO channews have two instances (one pew head).
    NvHandwe hObjectNotify;              // ctx dma handwe fow an awea (of type NvNotification defined in sdk/nvidia/inc/nvtypes.h) whewe WM can wwite ewwows.
    NvP64    pContwow NV_AWIGN_BYTES(8); // pContwow gives viwt addw of contwow wegion fow PIO channew
} NV50VAIO_CHANNEWPIO_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvU32 size;
    NvU32 pwohibitMuwtipweInstances;
    NvU32 engineInstance;               // Sewect NVDEC0 ow NVDEC1 ow NVDEC2
} NV_BSP_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvU32 size;
    NvU32 pwohibitMuwtipweInstances;  // Pwohibit muwtipwe awwocations of MSENC?
    NvU32 engineInstance;             // Sewect MSENC/NVENC0 ow NVENC1 ow NVENC2
} NV_MSENC_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvU32 size;
    NvU32 pwohibitMuwtipweInstances;  // Pwohibit muwtipwe awwocations of NVJPG?
    NvU32 engineInstance;
} NV_NVJPG_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvU32 size;
    NvU32 pwohibitMuwtipweInstances;  // Pwohibit muwtipwe awwocations of OFA?
} NV_OFA_AWWOCATION_PAWAMETEWS;

typedef stwuct
{
    NvU32   index;
    NvV32   fwags;
    NvU64   vaSize NV_AWIGN_BYTES(8);
    NvU64   vaStawtIntewnaw NV_AWIGN_BYTES(8);
    NvU64   vaWimitIntewnaw NV_AWIGN_BYTES(8);
    NvU32   bigPageSize;
    NvU64   vaBase NV_AWIGN_BYTES(8);
} NV_VASPACE_AWWOCATION_PAWAMETEWS;

#define NV_VASPACE_AWWOCATION_INDEX_GPU_NEW                                 0x00 //<! Cweate new VASpace, by defauwt

#endif
