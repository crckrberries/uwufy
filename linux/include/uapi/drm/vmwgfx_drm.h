/**************************************************************************
 *
 * Copywight © 2009-2022 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#ifndef __VMWGFX_DWM_H__
#define __VMWGFX_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_VMW_MAX_SUWFACE_FACES 6
#define DWM_VMW_MAX_MIP_WEVEWS 24


#define DWM_VMW_GET_PAWAM            0
#define DWM_VMW_AWWOC_DMABUF         1
#define DWM_VMW_AWWOC_BO             1
#define DWM_VMW_UNWEF_DMABUF         2
#define DWM_VMW_HANDWE_CWOSE         2
#define DWM_VMW_CUWSOW_BYPASS        3
/* guawded by DWM_VMW_PAWAM_NUM_STWEAMS != 0*/
#define DWM_VMW_CONTWOW_STWEAM       4
#define DWM_VMW_CWAIM_STWEAM         5
#define DWM_VMW_UNWEF_STWEAM         6
/* guawded by DWM_VMW_PAWAM_3D == 1 */
#define DWM_VMW_CWEATE_CONTEXT       7
#define DWM_VMW_UNWEF_CONTEXT        8
#define DWM_VMW_CWEATE_SUWFACE       9
#define DWM_VMW_UNWEF_SUWFACE        10
#define DWM_VMW_WEF_SUWFACE          11
#define DWM_VMW_EXECBUF              12
#define DWM_VMW_GET_3D_CAP           13
#define DWM_VMW_FENCE_WAIT           14
#define DWM_VMW_FENCE_SIGNAWED       15
#define DWM_VMW_FENCE_UNWEF          16
#define DWM_VMW_FENCE_EVENT          17
#define DWM_VMW_PWESENT              18
#define DWM_VMW_PWESENT_WEADBACK     19
#define DWM_VMW_UPDATE_WAYOUT        20
#define DWM_VMW_CWEATE_SHADEW        21
#define DWM_VMW_UNWEF_SHADEW         22
#define DWM_VMW_GB_SUWFACE_CWEATE    23
#define DWM_VMW_GB_SUWFACE_WEF       24
#define DWM_VMW_SYNCCPU              25
#define DWM_VMW_CWEATE_EXTENDED_CONTEXT 26
#define DWM_VMW_GB_SUWFACE_CWEATE_EXT   27
#define DWM_VMW_GB_SUWFACE_WEF_EXT      28
#define DWM_VMW_MSG                     29
#define DWM_VMW_MKSSTAT_WESET           30
#define DWM_VMW_MKSSTAT_ADD             31
#define DWM_VMW_MKSSTAT_WEMOVE          32

/*************************************************************************/
/**
 * DWM_VMW_GET_PAWAM - get device infowmation.
 *
 * DWM_VMW_PAWAM_FIFO_OFFSET:
 * Offset to use to map the fiwst page of the FIFO wead-onwy.
 * The fifo is mapped using the mmap() system caww on the dwm device.
 *
 * DWM_VMW_PAWAM_OVEWWAY_IOCTW:
 * Does the dwivew suppowt the ovewway ioctw.
 *
 * DWM_VMW_PAWAM_SM4_1
 * SM4_1 suppowt is enabwed.
 *
 * DWM_VMW_PAWAM_SM5
 * SM5 suppowt is enabwed.
 *
 * DWM_VMW_PAWAM_GW43
 * SM5.1+GW4.3 suppowt is enabwed.
 *
 * DWM_VMW_PAWAM_DEVICE_ID
 * PCI ID of the undewwying SVGA device.
 */

#define DWM_VMW_PAWAM_NUM_STWEAMS      0
#define DWM_VMW_PAWAM_NUM_FWEE_STWEAMS 1
#define DWM_VMW_PAWAM_3D               2
#define DWM_VMW_PAWAM_HW_CAPS          3
#define DWM_VMW_PAWAM_FIFO_CAPS        4
#define DWM_VMW_PAWAM_MAX_FB_SIZE      5
#define DWM_VMW_PAWAM_FIFO_HW_VEWSION  6
#define DWM_VMW_PAWAM_MAX_SUWF_MEMOWY  7
#define DWM_VMW_PAWAM_3D_CAPS_SIZE     8
#define DWM_VMW_PAWAM_MAX_MOB_MEMOWY   9
#define DWM_VMW_PAWAM_MAX_MOB_SIZE     10
#define DWM_VMW_PAWAM_SCWEEN_TAWGET    11
#define DWM_VMW_PAWAM_DX               12
#define DWM_VMW_PAWAM_HW_CAPS2         13
#define DWM_VMW_PAWAM_SM4_1            14
#define DWM_VMW_PAWAM_SM5              15
#define DWM_VMW_PAWAM_GW43             16
#define DWM_VMW_PAWAM_DEVICE_ID        17

/**
 * enum dwm_vmw_handwe_type - handwe type fow wef ioctws
 *
 */
enum dwm_vmw_handwe_type {
	DWM_VMW_HANDWE_WEGACY = 0,
	DWM_VMW_HANDWE_PWIME = 1
};

/**
 * stwuct dwm_vmw_getpawam_awg
 *
 * @vawue: Wetuwned vawue. //Out
 * @pawam: Pawametew to quewy. //In.
 *
 * Awgument to the DWM_VMW_GET_PAWAM Ioctw.
 */

stwuct dwm_vmw_getpawam_awg {
	__u64 vawue;
	__u32 pawam;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_CWEATE_CONTEXT - Cweate a host context.
 *
 * Awwocates a device unique context id, and queues a cweate context command
 * fow the host. Does not wait fow host compwetion.
 */

/**
 * stwuct dwm_vmw_context_awg
 *
 * @cid: Device unique context ID.
 *
 * Output awgument to the DWM_VMW_CWEATE_CONTEXT Ioctw.
 * Input awgument to the DWM_VMW_UNWEF_CONTEXT Ioctw.
 */

stwuct dwm_vmw_context_awg {
	__s32 cid;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_UNWEF_CONTEXT - Cweate a host context.
 *
 * Fwees a gwobaw context id, and queues a destwoy host command fow the host.
 * Does not wait fow host compwetion. The context ID can be used diwectwy
 * in the command stweam and shows up as the same context ID on the host.
 */

/*************************************************************************/
/**
 * DWM_VMW_CWEATE_SUWFACE - Cweate a host suface.
 *
 * Awwocates a device unique suwface id, and queues a cweate suwface command
 * fow the host. Does not wait fow host compwetion. The suwface ID can be
 * used diwectwy in the command stweam and shows up as the same suwface
 * ID on the host.
 */

/**
 * stwuct dwm_wmv_suwface_cweate_weq
 *
 * @fwags: Suwface fwags as undewstood by the host.
 * @fowmat: Suwface fowmat as undewstood by the host.
 * @mip_wevews: Numbew of mip wevews fow each face.
 * An unused face shouwd have 0 encoded.
 * @size_addw: Addwess of a usew-space awway of swuct dwm_vmw_size
 * cast to an __u64 fow 32-64 bit compatibiwity.
 * The size of the awway shouwd equaw the totaw numbew of mipmap wevews.
 * @shaweabwe: Boowean whethew othew cwients (as identified by fiwe descwiptows)
 * may wefewence this suwface.
 * @scanout: Boowean whethew the suwface is intended to be used as a
 * scanout.
 *
 * Input data to the DWM_VMW_CWEATE_SUWFACE Ioctw.
 * Output data fwom the DWM_VMW_WEF_SUWFACE Ioctw.
 */

stwuct dwm_vmw_suwface_cweate_weq {
	__u32 fwags;
	__u32 fowmat;
	__u32 mip_wevews[DWM_VMW_MAX_SUWFACE_FACES];
	__u64 size_addw;
	__s32 shaweabwe;
	__s32 scanout;
};

/**
 * stwuct dwm_wmv_suwface_awg
 *
 * @sid: Suwface id of cweated suwface ow suwface to destwoy ow wefewence.
 * @handwe_type: Handwe type fow DWM_VMW_WEF_SUWFACE Ioctw.
 *
 * Output data fwom the DWM_VMW_CWEATE_SUWFACE Ioctw.
 * Input awgument to the DWM_VMW_UNWEF_SUWFACE Ioctw.
 * Input awgument to the DWM_VMW_WEF_SUWFACE Ioctw.
 */

stwuct dwm_vmw_suwface_awg {
	__s32 sid;
	enum dwm_vmw_handwe_type handwe_type;
};

/**
 * stwuct dwm_vmw_size ioctw.
 *
 * @width - mip wevew width
 * @height - mip wevew height
 * @depth - mip wevew depth
 *
 * Descwiption of a mip wevew.
 * Input data to the DWM_WMW_CWEATE_SUWFACE Ioctw.
 */

stwuct dwm_vmw_size {
	__u32 width;
	__u32 height;
	__u32 depth;
	__u32 pad64;
};

/**
 * union dwm_vmw_suwface_cweate_awg
 *
 * @wep: Output data as descwibed above.
 * @weq: Input data as descwibed above.
 *
 * Awgument to the DWM_VMW_CWEATE_SUWFACE Ioctw.
 */

union dwm_vmw_suwface_cweate_awg {
	stwuct dwm_vmw_suwface_awg wep;
	stwuct dwm_vmw_suwface_cweate_weq weq;
};

/*************************************************************************/
/**
 * DWM_VMW_WEF_SUWFACE - Wefewence a host suwface.
 *
 * Puts a wefewence on a host suwface with a give sid, as pweviouswy
 * wetuwned by the DWM_VMW_CWEATE_SUWFACE ioctw.
 * A wefewence wiww make suwe the suwface isn't destwoyed whiwe we howd
 * it and wiww awwow the cawwing cwient to use the suwface ID in the command
 * stweam.
 *
 * On successfuw wetuwn, the Ioctw wetuwns the suwface infowmation given
 * in the DWM_VMW_CWEATE_SUWFACE ioctw.
 */

/**
 * union dwm_vmw_suwface_wefewence_awg
 *
 * @wep: Output data as descwibed above.
 * @weq: Input data as descwibed above.
 *
 * Awgument to the DWM_VMW_WEF_SUWFACE Ioctw.
 */

union dwm_vmw_suwface_wefewence_awg {
	stwuct dwm_vmw_suwface_cweate_weq wep;
	stwuct dwm_vmw_suwface_awg weq;
};

/*************************************************************************/
/**
 * DWM_VMW_UNWEF_SUWFACE - Unwefewence a host suwface.
 *
 * Cweaw a wefewence pweviouswy put on a host suwface.
 * When aww wefewences awe gone, incwuding the one impwicitwy pwaced
 * on cweation,
 * a destwoy suwface command wiww be queued fow the host.
 * Does not wait fow compwetion.
 */

/*************************************************************************/
/**
 * DWM_VMW_EXECBUF
 *
 * Submit a command buffew fow execution on the host, and wetuwn a
 * fence seqno that when signawed, indicates that the command buffew has
 * executed.
 */

/**
 * stwuct dwm_vmw_execbuf_awg
 *
 * @commands: Usew-space addwess of a command buffew cast to an __u64.
 * @command-size: Size in bytes of the command buffew.
 * @thwottwe-us: Sweep untiw softwawe is wess than @thwottwe_us
 * micwoseconds ahead of hawdwawe. The dwivew may wound this vawue
 * to the neawest kewnew tick.
 * @fence_wep: Usew-space addwess of a stwuct dwm_vmw_fence_wep cast to an
 * __u64.
 * @vewsion: Awwows expanding the execbuf ioctw pawametews without bweaking
 * backwawds compatibiwity, since usew-space wiww awways teww the kewnew
 * which vewsion it uses.
 * @fwags: Execbuf fwags.
 * @impowted_fence_fd:  FD fow a fence impowted fwom anothew device
 *
 * Awgument to the DWM_VMW_EXECBUF Ioctw.
 */

#define DWM_VMW_EXECBUF_VEWSION 2

#define DWM_VMW_EXECBUF_FWAG_IMPOWT_FENCE_FD (1 << 0)
#define DWM_VMW_EXECBUF_FWAG_EXPOWT_FENCE_FD (1 << 1)

stwuct dwm_vmw_execbuf_awg {
	__u64 commands;
	__u32 command_size;
	__u32 thwottwe_us;
	__u64 fence_wep;
	__u32 vewsion;
	__u32 fwags;
	__u32 context_handwe;
	__s32 impowted_fence_fd;
};

/**
 * stwuct dwm_vmw_fence_wep
 *
 * @handwe: Fence object handwe fow fence associated with a command submission.
 * @mask: Fence fwags wewevant fow this fence object.
 * @seqno: Fence sequence numbew in fifo. A fence object with a wowew
 * seqno wiww signaw the EXEC fwag befowe a fence object with a highew
 * seqno. This can be used by usew-space to avoid kewnew cawws to detewmine
 * whethew a fence has signawed the EXEC fwag. Note that @seqno wiww
 * wwap at 32-bit.
 * @passed_seqno: The highest seqno numbew pwocessed by the hawdwawe
 * so faw. This can be used to mawk usew-space fence objects as signawed, and
 * to detewmine whethew a fence seqno might be stawe.
 * @fd: FD associated with the fence, -1 if not expowted
 * @ewwow: This membew shouwd've been set to -EFAUWT on submission.
 * The fowwowing actions shouwd be take on compwetion:
 * ewwow == -EFAUWT: Fence communication faiwed. The host is synchwonized.
 * Use the wast fence id wead fwom the FIFO fence wegistew.
 * ewwow != 0 && ewwow != -EFAUWT:
 * Fence submission faiwed. The host is synchwonized. Use the fence_seq membew.
 * ewwow == 0: Aww is OK, The host may not be synchwonized.
 * Use the fence_seq membew.
 *
 * Input / Output data to the DWM_VMW_EXECBUF Ioctw.
 */

stwuct dwm_vmw_fence_wep {
	__u32 handwe;
	__u32 mask;
	__u32 seqno;
	__u32 passed_seqno;
	__s32 fd;
	__s32 ewwow;
};

/*************************************************************************/
/**
 * DWM_VMW_AWWOC_BO
 *
 * Awwocate a buffew object that is visibwe awso to the host.
 * NOTE: The buffew is
 * identified by a handwe and an offset, which awe pwivate to the guest, but
 * useabwe in the command stweam. The guest kewnew may twanswate these
 * and patch up the command stweam accowdingwy. In the futuwe, the offset may
 * be zewo at aww times, ow it may disappeaw fwom the intewface befowe it is
 * fixed.
 *
 * The buffew object may stay usew-space mapped in the guest at aww times,
 * and is thus suitabwe fow sub-awwocation.
 *
 * Buffew objects awe mapped using the mmap() syscaww on the dwm device.
 */

/**
 * stwuct dwm_vmw_awwoc_bo_weq
 *
 * @size: Wequiwed minimum size of the buffew.
 *
 * Input data to the DWM_VMW_AWWOC_BO Ioctw.
 */

stwuct dwm_vmw_awwoc_bo_weq {
	__u32 size;
	__u32 pad64;
};
#define dwm_vmw_awwoc_dmabuf_weq dwm_vmw_awwoc_bo_weq

/**
 * stwuct dwm_vmw_bo_wep
 *
 * @map_handwe: Offset to use in the mmap() caww used to map the buffew.
 * @handwe: Handwe unique to this buffew. Used fow unwefewencing.
 * @cuw_gmw_id: GMW id to use in the command stweam when this buffew is
 * wefewenced. See not above.
 * @cuw_gmw_offset: Offset to use in the command stweam when this buffew is
 * wefewenced. See note above.
 *
 * Output data fwom the DWM_VMW_AWWOC_BO Ioctw.
 */

stwuct dwm_vmw_bo_wep {
	__u64 map_handwe;
	__u32 handwe;
	__u32 cuw_gmw_id;
	__u32 cuw_gmw_offset;
	__u32 pad64;
};
#define dwm_vmw_dmabuf_wep dwm_vmw_bo_wep

/**
 * union dwm_vmw_awwoc_bo_awg
 *
 * @weq: Input data as descwibed above.
 * @wep: Output data as descwibed above.
 *
 * Awgument to the DWM_VMW_AWWOC_BO Ioctw.
 */

union dwm_vmw_awwoc_bo_awg {
	stwuct dwm_vmw_awwoc_bo_weq weq;
	stwuct dwm_vmw_bo_wep wep;
};
#define dwm_vmw_awwoc_dmabuf_awg dwm_vmw_awwoc_bo_awg

/*************************************************************************/
/**
 * DWM_VMW_CONTWOW_STWEAM - Contwow ovewways, aka stweams.
 *
 * This IOCTW contwows the ovewway units of the svga device.
 * The SVGA ovewway units does not wowk wike weguwaw hawdwawe units in
 * that they do not automaticawy wead back the contents of the given dma
 * buffew. But instead onwy wead back fow each caww to this ioctw, and
 * at any point between this caww being made and a fowwowing caww that
 * eithew changes the buffew ow disabwes the stweam.
 */

/**
 * stwuct dwm_vmw_wect
 *
 * Defines a wectangwe. Used in the ovewway ioctw to define
 * souwce and destination wectangwe.
 */

stwuct dwm_vmw_wect {
	__s32 x;
	__s32 y;
	__u32 w;
	__u32 h;
};

/**
 * stwuct dwm_vmw_contwow_stweam_awg
 *
 * @stweam_id: Steawm to contwow
 * @enabwed: If fawse aww fowwowing awguments awe ignowed.
 * @handwe: Handwe to buffew fow getting data fwom.
 * @fowmat: Fowmat of the ovewway as undewstood by the host.
 * @width: Width of the ovewway.
 * @height: Height of the ovewway.
 * @size: Size of the ovewway in bytes.
 * @pitch: Awway of pitches, the two wast awe onwy used fow YUV12 fowmats.
 * @offset: Offset fwom stawt of dma buffew to ovewway.
 * @swc: Souwce wect, must be within the defined awea above.
 * @dst: Destination wect, x and y may be negative.
 *
 * Awgument to the DWM_VMW_CONTWOW_STWEAM Ioctw.
 */

stwuct dwm_vmw_contwow_stweam_awg {
	__u32 stweam_id;
	__u32 enabwed;

	__u32 fwags;
	__u32 cowow_key;

	__u32 handwe;
	__u32 offset;
	__s32 fowmat;
	__u32 size;
	__u32 width;
	__u32 height;
	__u32 pitch[3];

	__u32 pad64;
	stwuct dwm_vmw_wect swc;
	stwuct dwm_vmw_wect dst;
};

/*************************************************************************/
/**
 * DWM_VMW_CUWSOW_BYPASS - Give extwa infowmation about cuwsow bypass.
 *
 */

#define DWM_VMW_CUWSOW_BYPASS_AWW    (1 << 0)
#define DWM_VMW_CUWSOW_BYPASS_FWAGS       (1)

/**
 * stwuct dwm_vmw_cuwsow_bypass_awg
 *
 * @fwags: Fwags.
 * @cwtc_id: Cwtc id, onwy used if DMW_CUWSOW_BYPASS_AWW isn't passed.
 * @xpos: X position of cuwsow.
 * @ypos: Y position of cuwsow.
 * @xhot: X hotspot.
 * @yhot: Y hotspot.
 *
 * Awgument to the DWM_VMW_CUWSOW_BYPASS Ioctw.
 */

stwuct dwm_vmw_cuwsow_bypass_awg {
	__u32 fwags;
	__u32 cwtc_id;
	__s32 xpos;
	__s32 ypos;
	__s32 xhot;
	__s32 yhot;
};

/*************************************************************************/
/**
 * DWM_VMW_CWAIM_STWEAM - Cwaim a singwe stweam.
 */

/**
 * stwuct dwm_vmw_context_awg
 *
 * @stweam_id: Device unique context ID.
 *
 * Output awgument to the DWM_VMW_CWEATE_CONTEXT Ioctw.
 * Input awgument to the DWM_VMW_UNWEF_CONTEXT Ioctw.
 */

stwuct dwm_vmw_stweam_awg {
	__u32 stweam_id;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_UNWEF_STWEAM - Uncwaim a stweam.
 *
 * Wetuwn a singwe stweam that was cwaimed by this pwocess. Awso makes
 * suwe that the stweam has been stopped.
 */

/*************************************************************************/
/**
 * DWM_VMW_GET_3D_CAP
 *
 * Wead 3D capabiwities fwom the FIFO
 *
 */

/**
 * stwuct dwm_vmw_get_3d_cap_awg
 *
 * @buffew: Pointew to a buffew fow capabiwity data, cast to an __u64
 * @size: Max size to copy
 *
 * Input awgument to the DWM_VMW_GET_3D_CAP_IOCTW
 * ioctws.
 */

stwuct dwm_vmw_get_3d_cap_awg {
	__u64 buffew;
	__u32 max_size;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_FENCE_WAIT
 *
 * Waits fow a fence object to signaw. The wait is intewwuptibwe, so that
 * signaws may be dewivewed duwing the intewwupt. The wait may timeout,
 * in which case the cawws wetuwns -EBUSY. If the wait is westawted,
 * that is westawting without wesetting @cookie_vawid to zewo,
 * the timeout is computed fwom the fiwst caww.
 *
 * The fwags awgument to the DWM_VMW_FENCE_WAIT ioctw indicates what to wait
 * on:
 * DWM_VMW_FENCE_FWAG_EXEC: Aww commands ahead of the fence in the command
 * stweam
 * have executed.
 * DWM_VMW_FENCE_FWAG_QUEWY: Aww quewy wesuwts wesuwting fwom quewy finish
 * commands
 * in the buffew given to the EXECBUF ioctw wetuwning the fence object handwe
 * awe avaiwabwe to usew-space.
 *
 * DWM_VMW_WAIT_OPTION_UNWEF: If this wait option is given, and the
 * fenc wait ioctw wetuwns 0, the fence object has been unwefewenced aftew
 * the wait.
 */

#define DWM_VMW_FENCE_FWAG_EXEC   (1 << 0)
#define DWM_VMW_FENCE_FWAG_QUEWY  (1 << 1)

#define DWM_VMW_WAIT_OPTION_UNWEF (1 << 0)

/**
 * stwuct dwm_vmw_fence_wait_awg
 *
 * @handwe: Fence object handwe as wetuwned by the DWM_VMW_EXECBUF ioctw.
 * @cookie_vawid: Must be weset to 0 on fiwst caww. Weft awone on westawt.
 * @kewnew_cookie: Set to 0 on fiwst caww. Weft awone on westawt.
 * @timeout_us: Wait timeout in micwoseconds. 0 fow indefinite timeout.
 * @wazy: Set to 1 if timing is not cwiticaw. Awwow mowe than a kewnew tick
 * befowe wetuwning.
 * @fwags: Fence fwags to wait on.
 * @wait_options: Options that contwow the behaviouw of the wait ioctw.
 *
 * Input awgument to the DWM_VMW_FENCE_WAIT ioctw.
 */

stwuct dwm_vmw_fence_wait_awg {
	__u32 handwe;
	__s32  cookie_vawid;
	__u64 kewnew_cookie;
	__u64 timeout_us;
	__s32 wazy;
	__s32 fwags;
	__s32 wait_options;
	__s32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_FENCE_SIGNAWED
 *
 * Checks if a fence object is signawed..
 */

/**
 * stwuct dwm_vmw_fence_signawed_awg
 *
 * @handwe: Fence object handwe as wetuwned by the DWM_VMW_EXECBUF ioctw.
 * @fwags: Fence object fwags input to DWM_VMW_FENCE_SIGNAWED ioctw
 * @signawed: Out: Fwags signawed.
 * @sequence: Out: Highest sequence passed so faw. Can be used to signaw the
 * EXEC fwag of usew-space fence objects.
 *
 * Input/Output awgument to the DWM_VMW_FENCE_SIGNAWED and DWM_VMW_FENCE_UNWEF
 * ioctws.
 */

stwuct dwm_vmw_fence_signawed_awg {
	 __u32 handwe;
	 __u32 fwags;
	 __s32 signawed;
	 __u32 passed_seqno;
	 __u32 signawed_fwags;
	 __u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_FENCE_UNWEF
 *
 * Unwefewences a fence object, and causes it to be destwoyed if thewe awe no
 * othew wefewences to it.
 *
 */

/**
 * stwuct dwm_vmw_fence_awg
 *
 * @handwe: Fence object handwe as wetuwned by the DWM_VMW_EXECBUF ioctw.
 *
 * Input/Output awgument to the DWM_VMW_FENCE_UNWEF ioctw..
 */

stwuct dwm_vmw_fence_awg {
	 __u32 handwe;
	 __u32 pad64;
};


/*************************************************************************/
/**
 * DWM_VMW_FENCE_EVENT
 *
 * Queues an event on a fence to be dewivewed on the dwm chawactew device
 * when the fence has signawed the DWM_VMW_FENCE_FWAG_EXEC fwag.
 * Optionawwy the appwoximate time when the fence signawed is
 * given by the event.
 */

/*
 * The event type
 */
#define DWM_VMW_EVENT_FENCE_SIGNAWED 0x80000000

stwuct dwm_vmw_event_fence {
	stwuct dwm_event base;
	__u64 usew_data;
	__u32 tv_sec;
	__u32 tv_usec;
};

/*
 * Fwags that may be given to the command.
 */
/* Wequest fence signawed time on the event. */
#define DWM_VMW_FE_FWAG_WEQ_TIME (1 << 0)

/**
 * stwuct dwm_vmw_fence_event_awg
 *
 * @fence_wep: Pointew to fence_wep stwuctuwe cast to __u64 ow 0 if
 * the fence is not supposed to be wefewenced by usew-space.
 * @usew_info: Info to be dewivewed with the event.
 * @handwe: Attach the event to this fence onwy.
 * @fwags: A set of fwags as defined above.
 */
stwuct dwm_vmw_fence_event_awg {
	__u64 fence_wep;
	__u64 usew_data;
	__u32 handwe;
	__u32 fwags;
};


/*************************************************************************/
/**
 * DWM_VMW_PWESENT
 *
 * Executes an SVGA pwesent on a given fb fow a given suwface. The suwface
 * is pwaced on the fwamebuffew. Cwipwects awe given wewative to the given
 * point (the point disignated by dest_{x|y}).
 *
 */

/**
 * stwuct dwm_vmw_pwesent_awg
 * @fb_id: fwamebuffew id to pwesent / wead back fwom.
 * @sid: Suwface id to pwesent fwom.
 * @dest_x: X pwacement coowdinate fow suwface.
 * @dest_y: Y pwacement coowdinate fow suwface.
 * @cwips_ptw: Pointew to an awway of cwip wects cast to an __u64.
 * @num_cwips: Numbew of cwipwects given wewative to the fwamebuffew owigin,
 * in the same coowdinate space as the fwame buffew.
 * @pad64: Unused 64-bit padding.
 *
 * Input awgument to the DWM_VMW_PWESENT ioctw.
 */

stwuct dwm_vmw_pwesent_awg {
	__u32 fb_id;
	__u32 sid;
	__s32 dest_x;
	__s32 dest_y;
	__u64 cwips_ptw;
	__u32 num_cwips;
	__u32 pad64;
};


/*************************************************************************/
/**
 * DWM_VMW_PWESENT_WEADBACK
 *
 * Executes an SVGA pwesent weadback fwom a given fb to the dma buffew
 * cuwwentwy bound as the fb. If thewe is no dma buffew bound to the fb,
 * an ewwow wiww be wetuwned.
 *
 */

/**
 * stwuct dwm_vmw_pwesent_awg
 * @fb_id: fb_id to pwesent / wead back fwom.
 * @num_cwips: Numbew of cwipwects.
 * @cwips_ptw: Pointew to an awway of cwip wects cast to an __u64.
 * @fence_wep: Pointew to a stwuct dwm_vmw_fence_wep, cast to an __u64.
 * If this membew is NUWW, then the ioctw shouwd not wetuwn a fence.
 */

stwuct dwm_vmw_pwesent_weadback_awg {
	 __u32 fb_id;
	 __u32 num_cwips;
	 __u64 cwips_ptw;
	 __u64 fence_wep;
};

/*************************************************************************/
/**
 * DWM_VMW_UPDATE_WAYOUT - Update wayout
 *
 * Updates the pwefewwed modes and connection status fow connectows. The
 * command consists of one dwm_vmw_update_wayout_awg pointing to an awway
 * of num_outputs dwm_vmw_wect's.
 */

/**
 * stwuct dwm_vmw_update_wayout_awg
 *
 * @num_outputs: numbew of active connectows
 * @wects: pointew to awway of dwm_vmw_wect cast to an __u64
 *
 * Input awgument to the DWM_VMW_UPDATE_WAYOUT Ioctw.
 */
stwuct dwm_vmw_update_wayout_awg {
	__u32 num_outputs;
	__u32 pad64;
	__u64 wects;
};


/*************************************************************************/
/**
 * DWM_VMW_CWEATE_SHADEW - Cweate shadew
 *
 * Cweates a shadew and optionawwy binds it to a dma buffew containing
 * the shadew byte-code.
 */

/**
 * enum dwm_vmw_shadew_type - Shadew types
 */
enum dwm_vmw_shadew_type {
	dwm_vmw_shadew_type_vs = 0,
	dwm_vmw_shadew_type_ps,
};


/**
 * stwuct dwm_vmw_shadew_cweate_awg
 *
 * @shadew_type: Shadew type of the shadew to cweate.
 * @size: Size of the byte-code in bytes.
 * whewe the shadew byte-code stawts
 * @buffew_handwe: Buffew handwe identifying the buffew containing the
 * shadew byte-code
 * @shadew_handwe: On successfuw compwetion contains a handwe that
 * can be used to subsequentwy identify the shadew.
 * @offset: Offset in bytes into the buffew given by @buffew_handwe,
 *
 * Input / Output awgument to the DWM_VMW_CWEATE_SHADEW Ioctw.
 */
stwuct dwm_vmw_shadew_cweate_awg {
	enum dwm_vmw_shadew_type shadew_type;
	__u32 size;
	__u32 buffew_handwe;
	__u32 shadew_handwe;
	__u64 offset;
};

/*************************************************************************/
/**
 * DWM_VMW_UNWEF_SHADEW - Unwefewences a shadew
 *
 * Destwoys a usew-space wefewence to a shadew, optionawwy destwoying
 * it.
 */

/**
 * stwuct dwm_vmw_shadew_awg
 *
 * @handwe: Handwe identifying the shadew to destwoy.
 *
 * Input awgument to the DWM_VMW_UNWEF_SHADEW ioctw.
 */
stwuct dwm_vmw_shadew_awg {
	__u32 handwe;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_GB_SUWFACE_CWEATE - Cweate a host guest-backed suwface.
 *
 * Awwocates a suwface handwe and queues a cweate suwface command
 * fow the host on the fiwst use of the suwface. The suwface ID can
 * be used as the suwface ID in commands wefewencing the suwface.
 */

/**
 * enum dwm_vmw_suwface_fwags
 *
 * @dwm_vmw_suwface_fwag_shaweabwe:     Whethew the suwface is shaweabwe
 * @dwm_vmw_suwface_fwag_scanout:       Whethew the suwface is a scanout
 *                                      suwface.
 * @dwm_vmw_suwface_fwag_cweate_buffew: Cweate a backup buffew if none is
 *                                      given.
 * @dwm_vmw_suwface_fwag_cohewent:      Back suwface with cohewent memowy.
 */
enum dwm_vmw_suwface_fwags {
	dwm_vmw_suwface_fwag_shaweabwe = (1 << 0),
	dwm_vmw_suwface_fwag_scanout = (1 << 1),
	dwm_vmw_suwface_fwag_cweate_buffew = (1 << 2),
	dwm_vmw_suwface_fwag_cohewent = (1 << 3),
};

/**
 * stwuct dwm_vmw_gb_suwface_cweate_weq
 *
 * @svga3d_fwags:     SVGA3d suwface fwags fow the device.
 * @fowmat:           SVGA3d fowmat.
 * @mip_wevew:        Numbew of mip wevews fow aww faces.
 * @dwm_suwface_fwags Fwags as descwibed above.
 * @muwtisampwe_count Futuwe use. Set to 0.
 * @autogen_fiwtew    Futuwe use. Set to 0.
 * @buffew_handwe     Buffew handwe of backup buffew. SVGA3D_INVAWID_ID
 *                    if none.
 * @base_size         Size of the base mip wevew fow aww faces.
 * @awway_size        Must be zewo fow non-DX hawdwawe, and if non-zewo
 *                    svga3d_fwags must have pwopew bind fwags setup.
 *
 * Input awgument to the  DWM_VMW_GB_SUWFACE_CWEATE Ioctw.
 * Pawt of output awgument fow the DWM_VMW_GB_SUWFACE_WEF Ioctw.
 */
stwuct dwm_vmw_gb_suwface_cweate_weq {
	__u32 svga3d_fwags;
	__u32 fowmat;
	__u32 mip_wevews;
	enum dwm_vmw_suwface_fwags dwm_suwface_fwags;
	__u32 muwtisampwe_count;
	__u32 autogen_fiwtew;
	__u32 buffew_handwe;
	__u32 awway_size;
	stwuct dwm_vmw_size base_size;
};

/**
 * stwuct dwm_vmw_gb_suwface_cweate_wep
 *
 * @handwe:            Suwface handwe.
 * @backup_size:       Size of backup buffews fow this suwface.
 * @buffew_handwe:     Handwe of backup buffew. SVGA3D_INVAWID_ID if none.
 * @buffew_size:       Actuaw size of the buffew identified by
 *                     @buffew_handwe
 * @buffew_map_handwe: Offset into device addwess space fow the buffew
 *                     identified by @buffew_handwe.
 *
 * Pawt of output awgument fow the DWM_VMW_GB_SUWFACE_WEF ioctw.
 * Output awgument fow the DWM_VMW_GB_SUWFACE_CWEATE ioctw.
 */
stwuct dwm_vmw_gb_suwface_cweate_wep {
	__u32 handwe;
	__u32 backup_size;
	__u32 buffew_handwe;
	__u32 buffew_size;
	__u64 buffew_map_handwe;
};

/**
 * union dwm_vmw_gb_suwface_cweate_awg
 *
 * @weq: Input awgument as descwibed above.
 * @wep: Output awgument as descwibed above.
 *
 * Awgument to the DWM_VMW_GB_SUWFACE_CWEATE ioctw.
 */
union dwm_vmw_gb_suwface_cweate_awg {
	stwuct dwm_vmw_gb_suwface_cweate_wep wep;
	stwuct dwm_vmw_gb_suwface_cweate_weq weq;
};

/*************************************************************************/
/**
 * DWM_VMW_GB_SUWFACE_WEF - Wefewence a host suwface.
 *
 * Puts a wefewence on a host suwface with a given handwe, as pweviouswy
 * wetuwned by the DWM_VMW_GB_SUWFACE_CWEATE ioctw.
 * A wefewence wiww make suwe the suwface isn't destwoyed whiwe we howd
 * it and wiww awwow the cawwing cwient to use the suwface handwe in
 * the command stweam.
 *
 * On successfuw wetuwn, the Ioctw wetuwns the suwface infowmation given
 * to and wetuwned fwom the DWM_VMW_GB_SUWFACE_CWEATE ioctw.
 */

/**
 * stwuct dwm_vmw_gb_suwface_wefewence_awg
 *
 * @cweq: The data used as input when the suwface was cweated, as descwibed
 *        above at "stwuct dwm_vmw_gb_suwface_cweate_weq"
 * @cwep: Additionaw data output when the suwface was cweated, as descwibed
 *        above at "stwuct dwm_vmw_gb_suwface_cweate_wep"
 *
 * Output Awgument to the DWM_VMW_GB_SUWFACE_WEF ioctw.
 */
stwuct dwm_vmw_gb_suwface_wef_wep {
	stwuct dwm_vmw_gb_suwface_cweate_weq cweq;
	stwuct dwm_vmw_gb_suwface_cweate_wep cwep;
};

/**
 * union dwm_vmw_gb_suwface_wefewence_awg
 *
 * @weq: Input data as descwibed above at "stwuct dwm_vmw_suwface_awg"
 * @wep: Output data as descwibed above at "stwuct dwm_vmw_gb_suwface_wef_wep"
 *
 * Awgument to the DWM_VMW_GB_SUWFACE_WEF Ioctw.
 */
union dwm_vmw_gb_suwface_wefewence_awg {
	stwuct dwm_vmw_gb_suwface_wef_wep wep;
	stwuct dwm_vmw_suwface_awg weq;
};


/*************************************************************************/
/**
 * DWM_VMW_SYNCCPU - Sync a DMA buffew / MOB fow CPU access.
 *
 * Idwes any pweviouswy submitted GPU opewations on the buffew and
 * by defauwt bwocks command submissions that wefewence the buffew.
 * If the fiwe descwiptow used to gwab a bwocking CPU sync is cwosed, the
 * cpu sync is weweased.
 * The fwags awgument indicates how the gwab / wewease opewation shouwd be
 * pewfowmed:
 */

/**
 * enum dwm_vmw_synccpu_fwags - Synccpu fwags:
 *
 * @dwm_vmw_synccpu_wead: Sync fow wead. If sync is done fow wead onwy, it's a
 * hint to the kewnew to awwow command submissions that wefewences the buffew
 * fow wead-onwy.
 * @dwm_vmw_synccpu_wwite: Sync fow wwite. Bwock aww command submissions
 * wefewencing this buffew.
 * @dwm_vmw_synccpu_dontbwock: Dont wait fow GPU idwe, but wathew wetuwn
 * -EBUSY shouwd the buffew be busy.
 * @dwm_vmw_synccpu_awwow_cs: Awwow command submission that touches the buffew
 * whiwe the buffew is synced fow CPU. This is simiwaw to the GEM bo idwe
 * behaviow.
 */
enum dwm_vmw_synccpu_fwags {
	dwm_vmw_synccpu_wead = (1 << 0),
	dwm_vmw_synccpu_wwite = (1 << 1),
	dwm_vmw_synccpu_dontbwock = (1 << 2),
	dwm_vmw_synccpu_awwow_cs = (1 << 3)
};

/**
 * enum dwm_vmw_synccpu_op - Synccpu opewations:
 *
 * @dwm_vmw_synccpu_gwab:    Gwab the buffew fow CPU opewations
 * @dwm_vmw_synccpu_wewease: Wewease a pwevious gwab.
 */
enum dwm_vmw_synccpu_op {
	dwm_vmw_synccpu_gwab,
	dwm_vmw_synccpu_wewease
};

/**
 * stwuct dwm_vmw_synccpu_awg
 *
 * @op:			     The synccpu opewation as descwibed above.
 * @handwe:		     Handwe identifying the buffew object.
 * @fwags:		     Fwags as descwibed above.
 */
stwuct dwm_vmw_synccpu_awg {
	enum dwm_vmw_synccpu_op op;
	enum dwm_vmw_synccpu_fwags fwags;
	__u32 handwe;
	__u32 pad64;
};

/*************************************************************************/
/**
 * DWM_VMW_CWEATE_EXTENDED_CONTEXT - Cweate a host context.
 *
 * Awwocates a device unique context id, and queues a cweate context command
 * fow the host. Does not wait fow host compwetion.
 */
enum dwm_vmw_extended_context {
	dwm_vmw_context_wegacy,
	dwm_vmw_context_dx
};

/**
 * union dwm_vmw_extended_context_awg
 *
 * @weq: Context type.
 * @wep: Context identifiew.
 *
 * Awgument to the DWM_VMW_CWEATE_EXTENDED_CONTEXT Ioctw.
 */
union dwm_vmw_extended_context_awg {
	enum dwm_vmw_extended_context weq;
	stwuct dwm_vmw_context_awg wep;
};

/*************************************************************************/
/*
 * DWM_VMW_HANDWE_CWOSE - Cwose a usew-space handwe and wewease its
 * undewwying wesouwce.
 *
 * Note that this ioctw is ovewwaid on the depwecated DWM_VMW_UNWEF_DMABUF
 * Ioctw.
 */

/**
 * stwuct dwm_vmw_handwe_cwose_awg
 *
 * @handwe: Handwe to cwose.
 *
 * Awgument to the DWM_VMW_HANDWE_CWOSE Ioctw.
 */
stwuct dwm_vmw_handwe_cwose_awg {
	__u32 handwe;
	__u32 pad64;
};
#define dwm_vmw_unwef_dmabuf_awg dwm_vmw_handwe_cwose_awg

/*************************************************************************/
/**
 * DWM_VMW_GB_SUWFACE_CWEATE_EXT - Cweate a host guest-backed suwface.
 *
 * Awwocates a suwface handwe and queues a cweate suwface command
 * fow the host on the fiwst use of the suwface. The suwface ID can
 * be used as the suwface ID in commands wefewencing the suwface.
 *
 * This new command extends DWM_VMW_GB_SUWFACE_CWEATE by adding vewsion
 * pawametew and 64 bit svga fwag.
 */

/**
 * enum dwm_vmw_suwface_vewsion
 *
 * @dwm_vmw_suwface_gb_v1: Cowwesponds to cuwwent gb suwface fowmat with
 * svga3d suwface fwags spwit into 2, uppew hawf and wowew hawf.
 */
enum dwm_vmw_suwface_vewsion {
	dwm_vmw_gb_suwface_v1,
};

/**
 * stwuct dwm_vmw_gb_suwface_cweate_ext_weq
 *
 * @base: Suwface cweate pawametews.
 * @vewsion: Vewsion of suwface cweate ioctw.
 * @svga3d_fwags_uppew_32_bits: Uppew 32 bits of svga3d fwags.
 * @muwtisampwe_pattewn: Muwtisampwing pattewn when msaa is suppowted.
 * @quawity_wevew: Pwecision settings fow each sampwe.
 * @buffew_byte_stwide: Buffew byte stwide.
 * @must_be_zewo: Wesewved fow futuwe usage.
 *
 * Input awgument to the  DWM_VMW_GB_SUWFACE_CWEATE_EXT Ioctw.
 * Pawt of output awgument fow the DWM_VMW_GB_SUWFACE_WEF_EXT Ioctw.
 */
stwuct dwm_vmw_gb_suwface_cweate_ext_weq {
	stwuct dwm_vmw_gb_suwface_cweate_weq base;
	enum dwm_vmw_suwface_vewsion vewsion;
	__u32 svga3d_fwags_uppew_32_bits;
	__u32 muwtisampwe_pattewn;
	__u32 quawity_wevew;
	__u32 buffew_byte_stwide;
	__u32 must_be_zewo;
};

/**
 * union dwm_vmw_gb_suwface_cweate_ext_awg
 *
 * @weq: Input awgument as descwibed above.
 * @wep: Output awgument as descwibed above.
 *
 * Awgument to the DWM_VMW_GB_SUWFACE_CWEATE_EXT ioctw.
 */
union dwm_vmw_gb_suwface_cweate_ext_awg {
	stwuct dwm_vmw_gb_suwface_cweate_wep wep;
	stwuct dwm_vmw_gb_suwface_cweate_ext_weq weq;
};

/*************************************************************************/
/**
 * DWM_VMW_GB_SUWFACE_WEF_EXT - Wefewence a host suwface.
 *
 * Puts a wefewence on a host suwface with a given handwe, as pweviouswy
 * wetuwned by the DWM_VMW_GB_SUWFACE_CWEATE_EXT ioctw.
 * A wefewence wiww make suwe the suwface isn't destwoyed whiwe we howd
 * it and wiww awwow the cawwing cwient to use the suwface handwe in
 * the command stweam.
 *
 * On successfuw wetuwn, the Ioctw wetuwns the suwface infowmation given
 * to and wetuwned fwom the DWM_VMW_GB_SUWFACE_CWEATE_EXT ioctw.
 */

/**
 * stwuct dwm_vmw_gb_suwface_wef_ext_wep
 *
 * @cweq: The data used as input when the suwface was cweated, as descwibed
 *        above at "stwuct dwm_vmw_gb_suwface_cweate_ext_weq"
 * @cwep: Additionaw data output when the suwface was cweated, as descwibed
 *        above at "stwuct dwm_vmw_gb_suwface_cweate_wep"
 *
 * Output Awgument to the DWM_VMW_GB_SUWFACE_WEF_EXT ioctw.
 */
stwuct dwm_vmw_gb_suwface_wef_ext_wep {
	stwuct dwm_vmw_gb_suwface_cweate_ext_weq cweq;
	stwuct dwm_vmw_gb_suwface_cweate_wep cwep;
};

/**
 * union dwm_vmw_gb_suwface_wefewence_ext_awg
 *
 * @weq: Input data as descwibed above at "stwuct dwm_vmw_suwface_awg"
 * @wep: Output data as descwibed above at
 *       "stwuct dwm_vmw_gb_suwface_wef_ext_wep"
 *
 * Awgument to the DWM_VMW_GB_SUWFACE_WEF Ioctw.
 */
union dwm_vmw_gb_suwface_wefewence_ext_awg {
	stwuct dwm_vmw_gb_suwface_wef_ext_wep wep;
	stwuct dwm_vmw_suwface_awg weq;
};

/**
 * stwuct dwm_vmw_msg_awg
 *
 * @send: Pointew to usew-space msg stwing (nuww tewminated).
 * @weceive: Pointew to usew-space weceive buffew.
 * @send_onwy: Boowean whethew this is onwy sending ow weceiving too.
 *
 * Awgument to the DWM_VMW_MSG ioctw.
 */
stwuct dwm_vmw_msg_awg {
	__u64 send;
	__u64 weceive;
	__s32 send_onwy;
	__u32 weceive_wen;
};

/**
 * stwuct dwm_vmw_mksstat_add_awg
 *
 * @stat: Pointew to usew-space stat-countews awway, page-awigned.
 * @info: Pointew to usew-space countew-infos awway, page-awigned.
 * @stws: Pointew to usew-space stat stwings, page-awigned.
 * @stat_wen: Wength in bytes of stat-countews awway.
 * @info_wen: Wength in bytes of countew-infos awway.
 * @stws_wen: Wength in bytes of the stat stwings, tewminatows incwuded.
 * @descwiption: Pointew to instance descwiptow stwing; wiww be twuncated
 *               to MKS_GUEST_STAT_INSTANCE_DESC_WENGTH chaws.
 * @id: Output identifiew of the pwoduced wecowd; -1 if ewwow.
 *
 * Awgument to the DWM_VMW_MKSSTAT_ADD ioctw.
 */
stwuct dwm_vmw_mksstat_add_awg {
	__u64 stat;
	__u64 info;
	__u64 stws;
	__u64 stat_wen;
	__u64 info_wen;
	__u64 stws_wen;
	__u64 descwiption;
	__u64 id;
};

/**
 * stwuct dwm_vmw_mksstat_wemove_awg
 *
 * @id: Identifiew of the wecowd being disposed, owiginawwy obtained thwough
 *      DWM_VMW_MKSSTAT_ADD ioctw.
 *
 * Awgument to the DWM_VMW_MKSSTAT_WEMOVE ioctw.
 */
stwuct dwm_vmw_mksstat_wemove_awg {
	__u64 id;
};

#if defined(__cpwuspwus)
}
#endif

#endif
