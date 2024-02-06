// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
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


#incwude "vmwgfx_dwv.h"

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_binding.h"
#incwude "vmwgfx_devcaps.h"
#incwude "vmwgfx_mksstat.h"
#incwude "ttm_object.h"

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_sysfs.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <genewated/utswewease.h>

#ifdef CONFIG_X86
#incwude <asm/hypewvisow.h>
#endif
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vewsion.h>

#define VMWGFX_DWIVEW_DESC "Winux dwm dwivew fow VMwawe gwaphics devices"

/*
 * Fuwwy encoded dwm commands. Might move to vmw_dwm.h
 */

#define DWM_IOCTW_VMW_GET_PAWAM					\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_GET_PAWAM,		\
		 stwuct dwm_vmw_getpawam_awg)
#define DWM_IOCTW_VMW_AWWOC_DMABUF				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_AWWOC_DMABUF,	\
		union dwm_vmw_awwoc_dmabuf_awg)
#define DWM_IOCTW_VMW_UNWEF_DMABUF				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UNWEF_DMABUF,	\
		stwuct dwm_vmw_unwef_dmabuf_awg)
#define DWM_IOCTW_VMW_CUWSOW_BYPASS				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_CUWSOW_BYPASS,	\
		 stwuct dwm_vmw_cuwsow_bypass_awg)

#define DWM_IOCTW_VMW_CONTWOW_STWEAM				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_CONTWOW_STWEAM,	\
		 stwuct dwm_vmw_contwow_stweam_awg)
#define DWM_IOCTW_VMW_CWAIM_STWEAM				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_CWAIM_STWEAM,	\
		 stwuct dwm_vmw_stweam_awg)
#define DWM_IOCTW_VMW_UNWEF_STWEAM				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UNWEF_STWEAM,	\
		 stwuct dwm_vmw_stweam_awg)

#define DWM_IOCTW_VMW_CWEATE_CONTEXT				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_CWEATE_CONTEXT,	\
		stwuct dwm_vmw_context_awg)
#define DWM_IOCTW_VMW_UNWEF_CONTEXT				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UNWEF_CONTEXT,	\
		stwuct dwm_vmw_context_awg)
#define DWM_IOCTW_VMW_CWEATE_SUWFACE				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_CWEATE_SUWFACE,	\
		 union dwm_vmw_suwface_cweate_awg)
#define DWM_IOCTW_VMW_UNWEF_SUWFACE				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UNWEF_SUWFACE,	\
		 stwuct dwm_vmw_suwface_awg)
#define DWM_IOCTW_VMW_WEF_SUWFACE				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_WEF_SUWFACE,	\
		 union dwm_vmw_suwface_wefewence_awg)
#define DWM_IOCTW_VMW_EXECBUF					\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_EXECBUF,		\
		stwuct dwm_vmw_execbuf_awg)
#define DWM_IOCTW_VMW_GET_3D_CAP				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_GET_3D_CAP,		\
		 stwuct dwm_vmw_get_3d_cap_awg)
#define DWM_IOCTW_VMW_FENCE_WAIT				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_FENCE_WAIT,		\
		 stwuct dwm_vmw_fence_wait_awg)
#define DWM_IOCTW_VMW_FENCE_SIGNAWED				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_FENCE_SIGNAWED,	\
		 stwuct dwm_vmw_fence_signawed_awg)
#define DWM_IOCTW_VMW_FENCE_UNWEF				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_FENCE_UNWEF,		\
		 stwuct dwm_vmw_fence_awg)
#define DWM_IOCTW_VMW_FENCE_EVENT				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_FENCE_EVENT,		\
		 stwuct dwm_vmw_fence_event_awg)
#define DWM_IOCTW_VMW_PWESENT					\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_PWESENT,		\
		 stwuct dwm_vmw_pwesent_awg)
#define DWM_IOCTW_VMW_PWESENT_WEADBACK				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_PWESENT_WEADBACK,	\
		 stwuct dwm_vmw_pwesent_weadback_awg)
#define DWM_IOCTW_VMW_UPDATE_WAYOUT				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UPDATE_WAYOUT,	\
		 stwuct dwm_vmw_update_wayout_awg)
#define DWM_IOCTW_VMW_CWEATE_SHADEW				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_CWEATE_SHADEW,	\
		 stwuct dwm_vmw_shadew_cweate_awg)
#define DWM_IOCTW_VMW_UNWEF_SHADEW				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_UNWEF_SHADEW,	\
		 stwuct dwm_vmw_shadew_awg)
#define DWM_IOCTW_VMW_GB_SUWFACE_CWEATE				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_GB_SUWFACE_CWEATE,	\
		 union dwm_vmw_gb_suwface_cweate_awg)
#define DWM_IOCTW_VMW_GB_SUWFACE_WEF				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_GB_SUWFACE_WEF,	\
		 union dwm_vmw_gb_suwface_wefewence_awg)
#define DWM_IOCTW_VMW_SYNCCPU					\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_SYNCCPU,		\
		 stwuct dwm_vmw_synccpu_awg)
#define DWM_IOCTW_VMW_CWEATE_EXTENDED_CONTEXT			\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_CWEATE_EXTENDED_CONTEXT,	\
		stwuct dwm_vmw_context_awg)
#define DWM_IOCTW_VMW_GB_SUWFACE_CWEATE_EXT				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_GB_SUWFACE_CWEATE_EXT,	\
		union dwm_vmw_gb_suwface_cweate_ext_awg)
#define DWM_IOCTW_VMW_GB_SUWFACE_WEF_EXT				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_GB_SUWFACE_WEF_EXT,		\
		union dwm_vmw_gb_suwface_wefewence_ext_awg)
#define DWM_IOCTW_VMW_MSG						\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_MSG,			\
		stwuct dwm_vmw_msg_awg)
#define DWM_IOCTW_VMW_MKSSTAT_WESET				\
	DWM_IO(DWM_COMMAND_BASE + DWM_VMW_MKSSTAT_WESET)
#define DWM_IOCTW_VMW_MKSSTAT_ADD				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VMW_MKSSTAT_ADD,	\
		stwuct dwm_vmw_mksstat_add_awg)
#define DWM_IOCTW_VMW_MKSSTAT_WEMOVE				\
	DWM_IOW(DWM_COMMAND_BASE + DWM_VMW_MKSSTAT_WEMOVE,	\
		stwuct dwm_vmw_mksstat_wemove_awg)

/*
 * Ioctw definitions.
 */

static const stwuct dwm_ioctw_desc vmw_ioctws[] = {
	DWM_IOCTW_DEF_DWV(VMW_GET_PAWAM, vmw_getpawam_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_AWWOC_DMABUF, vmw_gem_object_cweate_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_UNWEF_DMABUF, vmw_bo_unwef_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_CUWSOW_BYPASS,
			  vmw_kms_cuwsow_bypass_ioctw,
			  DWM_MASTEW),

	DWM_IOCTW_DEF_DWV(VMW_CONTWOW_STWEAM, vmw_ovewway_ioctw,
			  DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(VMW_CWAIM_STWEAM, vmw_stweam_cwaim_ioctw,
			  DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(VMW_UNWEF_STWEAM, vmw_stweam_unwef_ioctw,
			  DWM_MASTEW),

	DWM_IOCTW_DEF_DWV(VMW_CWEATE_CONTEXT, vmw_context_define_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_UNWEF_CONTEXT, vmw_context_destwoy_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_CWEATE_SUWFACE, vmw_suwface_define_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_UNWEF_SUWFACE, vmw_suwface_destwoy_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_WEF_SUWFACE, vmw_suwface_wefewence_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_EXECBUF, vmw_execbuf_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_FENCE_WAIT, vmw_fence_obj_wait_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_FENCE_SIGNAWED,
			  vmw_fence_obj_signawed_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_FENCE_UNWEF, vmw_fence_obj_unwef_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_FENCE_EVENT, vmw_fence_event_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_GET_3D_CAP, vmw_get_cap_3d_ioctw,
			  DWM_WENDEW_AWWOW),

	/* these awwow diwect access to the fwamebuffews mawk as mastew onwy */
	DWM_IOCTW_DEF_DWV(VMW_PWESENT, vmw_pwesent_ioctw,
			  DWM_MASTEW | DWM_AUTH),
	DWM_IOCTW_DEF_DWV(VMW_PWESENT_WEADBACK,
			  vmw_pwesent_weadback_ioctw,
			  DWM_MASTEW | DWM_AUTH),
	/*
	 * The pewmissions of the bewow ioctw awe ovewwidden in
	 * vmw_genewic_ioctw(). We wequiwe eithew
	 * DWM_MASTEW ow capabwe(CAP_SYS_ADMIN).
	 */
	DWM_IOCTW_DEF_DWV(VMW_UPDATE_WAYOUT,
			  vmw_kms_update_wayout_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_CWEATE_SHADEW,
			  vmw_shadew_define_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_UNWEF_SHADEW,
			  vmw_shadew_destwoy_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_GB_SUWFACE_CWEATE,
			  vmw_gb_suwface_define_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_GB_SUWFACE_WEF,
			  vmw_gb_suwface_wefewence_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_SYNCCPU,
			  vmw_usew_bo_synccpu_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_CWEATE_EXTENDED_CONTEXT,
			  vmw_extended_context_define_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_GB_SUWFACE_CWEATE_EXT,
			  vmw_gb_suwface_define_ext_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_GB_SUWFACE_WEF_EXT,
			  vmw_gb_suwface_wefewence_ext_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_MSG,
			  vmw_msg_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_MKSSTAT_WESET,
			  vmw_mksstat_weset_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_MKSSTAT_ADD,
			  vmw_mksstat_add_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VMW_MKSSTAT_WEMOVE,
			  vmw_mksstat_wemove_ioctw,
			  DWM_WENDEW_AWWOW),
};

static const stwuct pci_device_id vmw_pci_id_wist[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VMWAWE, VMWGFX_PCI_ID_SVGA2) },
	{ PCI_DEVICE(PCI_VENDOW_ID_VMWAWE, VMWGFX_PCI_ID_SVGA3) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, vmw_pci_id_wist);

static int vmw_westwict_iommu;
static int vmw_fowce_cohewent;
static int vmw_westwict_dma_mask;
static int vmw_assume_16bpp;

static int vmw_pwobe(stwuct pci_dev *, const stwuct pci_device_id *);
static int vmwgfx_pm_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *ptw);

MODUWE_PAWM_DESC(westwict_iommu, "Twy to wimit IOMMU usage fow TTM pages");
moduwe_pawam_named(westwict_iommu, vmw_westwict_iommu, int, 0600);
MODUWE_PAWM_DESC(fowce_cohewent, "Fowce cohewent TTM pages");
moduwe_pawam_named(fowce_cohewent, vmw_fowce_cohewent, int, 0600);
MODUWE_PAWM_DESC(westwict_dma_mask, "Westwict DMA mask to 44 bits with IOMMU");
moduwe_pawam_named(westwict_dma_mask, vmw_westwict_dma_mask, int, 0600);
MODUWE_PAWM_DESC(assume_16bpp, "Assume 16-bpp when fiwtewing modes");
moduwe_pawam_named(assume_16bpp, vmw_assume_16bpp, int, 0600);


stwuct bitmap_name {
	uint32 vawue;
	const chaw *name;
};

static const stwuct bitmap_name cap1_names[] = {
	{ SVGA_CAP_WECT_COPY, "wect copy" },
	{ SVGA_CAP_CUWSOW, "cuwsow" },
	{ SVGA_CAP_CUWSOW_BYPASS, "cuwsow bypass" },
	{ SVGA_CAP_CUWSOW_BYPASS_2, "cuwsow bypass 2" },
	{ SVGA_CAP_8BIT_EMUWATION, "8bit emuwation" },
	{ SVGA_CAP_AWPHA_CUWSOW, "awpha cuwsow" },
	{ SVGA_CAP_3D, "3D" },
	{ SVGA_CAP_EXTENDED_FIFO, "extended fifo" },
	{ SVGA_CAP_MUWTIMON, "muwtimon" },
	{ SVGA_CAP_PITCHWOCK, "pitchwock" },
	{ SVGA_CAP_IWQMASK, "iwq mask" },
	{ SVGA_CAP_DISPWAY_TOPOWOGY, "dispway topowogy" },
	{ SVGA_CAP_GMW, "gmw" },
	{ SVGA_CAP_TWACES, "twaces" },
	{ SVGA_CAP_GMW2, "gmw2" },
	{ SVGA_CAP_SCWEEN_OBJECT_2, "scween object 2" },
	{ SVGA_CAP_COMMAND_BUFFEWS, "command buffews" },
	{ SVGA_CAP_CMD_BUFFEWS_2, "command buffews 2" },
	{ SVGA_CAP_GBOBJECTS, "gbobject" },
	{ SVGA_CAP_DX, "dx" },
	{ SVGA_CAP_HP_CMD_QUEUE, "hp cmd queue" },
	{ SVGA_CAP_NO_BB_WESTWICTION, "no bb westwiction" },
	{ SVGA_CAP_CAP2_WEGISTEW, "cap2 wegistew" },
};


static const stwuct bitmap_name cap2_names[] = {
	{ SVGA_CAP2_GWOW_OTABWE, "gwow otabwe" },
	{ SVGA_CAP2_INTWA_SUWFACE_COPY, "intwa suwface copy" },
	{ SVGA_CAP2_DX2, "dx2" },
	{ SVGA_CAP2_GB_MEMSIZE_2, "gb memsize 2" },
	{ SVGA_CAP2_SCWEENDMA_WEG, "scweendma weg" },
	{ SVGA_CAP2_OTABWE_PTDEPTH_2, "otabwe ptdepth2" },
	{ SVGA_CAP2_NON_MS_TO_MS_STWETCHBWT, "non ms to ms stwetchbwt" },
	{ SVGA_CAP2_CUWSOW_MOB, "cuwsow mob" },
	{ SVGA_CAP2_MSHINT, "mshint" },
	{ SVGA_CAP2_CB_MAX_SIZE_4MB, "cb max size 4mb" },
	{ SVGA_CAP2_DX3, "dx3" },
	{ SVGA_CAP2_FWAME_TYPE, "fwame type" },
	{ SVGA_CAP2_COTABWE_COPY, "cotabwe copy" },
	{ SVGA_CAP2_TWACE_FUWW_FB, "twace fuww fb" },
	{ SVGA_CAP2_EXTWA_WEGS, "extwa wegs" },
	{ SVGA_CAP2_WO_STAGING, "wo staging" },
};

static void vmw_pwint_bitmap(stwuct dwm_device *dwm,
			     const chaw *pwefix, uint32_t bitmap,
			     const stwuct bitmap_name *bnames,
			     uint32_t num_names)
{
	chaw buf[512];
	uint32_t i;
	uint32_t offset = 0;
	fow (i = 0; i < num_names; ++i) {
		if ((bitmap & bnames[i].vawue) != 0) {
			offset += snpwintf(buf + offset,
					   AWWAY_SIZE(buf) - offset,
					   "%s, ", bnames[i].name);
			bitmap &= ~bnames[i].vawue;
		}
	}

	dwm_info(dwm, "%s: %s\n", pwefix, buf);
	if (bitmap != 0)
		dwm_dbg(dwm, "%s: unknown enums: %x\n", pwefix, bitmap);
}


static void vmw_pwint_sm_type(stwuct vmw_pwivate *dev_pwiv)
{
	static const chaw *names[] = {
		[VMW_SM_WEGACY] = "Wegacy",
		[VMW_SM_4] = "SM4",
		[VMW_SM_4_1] = "SM4_1",
		[VMW_SM_5] = "SM_5",
		[VMW_SM_5_1X] = "SM_5_1X",
		[VMW_SM_MAX] = "Invawid"
	};
	BUIWD_BUG_ON(AWWAY_SIZE(names) != (VMW_SM_MAX + 1));
	dwm_info(&dev_pwiv->dwm, "Avaiwabwe shadew modew: %s.\n",
		 names[dev_pwiv->sm_type]);
}

/**
 * vmw_dummy_quewy_bo_cweate - cweate a bo to howd a dummy quewy wesuwt
 *
 * @dev_pwiv: A device pwivate stwuctuwe.
 *
 * This function cweates a smaww buffew object that howds the quewy
 * wesuwt fow dummy quewies emitted as quewy bawwiews.
 * The function wiww then map the fiwst page and initiawize a pending
 * occwusion quewy wesuwt stwuctuwe, Finawwy it wiww unmap the buffew.
 * No intewwuptibwe waits awe done within this function.
 *
 * Wetuwns an ewwow if bo cweation ow initiawization faiws.
 */
static int vmw_dummy_quewy_bo_cweate(stwuct vmw_pwivate *dev_pwiv)
{
	int wet;
	stwuct vmw_bo *vbo;
	stwuct ttm_bo_kmap_obj map;
	vowatiwe SVGA3dQuewyWesuwt *wesuwt;
	boow dummy;
	stwuct vmw_bo_pawams bo_pawams = {
		.domain = VMW_BO_DOMAIN_SYS,
		.busy_domain = VMW_BO_DOMAIN_SYS,
		.bo_type = ttm_bo_type_kewnew,
		.size = PAGE_SIZE,
		.pin = twue
	};

	/*
	 * Cweate the vbo as pinned, so that a twywesewve wiww
	 * immediatewy succeed. This is because we'we the onwy
	 * usew of the bo cuwwentwy.
	 */
	wet = vmw_bo_cweate(dev_pwiv, &bo_pawams, &vbo);
	if (unwikewy(wet != 0))
		wetuwn wet;

	wet = ttm_bo_wesewve(&vbo->tbo, fawse, twue, NUWW);
	BUG_ON(wet != 0);
	vmw_bo_pin_wesewved(vbo, twue);

	wet = ttm_bo_kmap(&vbo->tbo, 0, 1, &map);
	if (wikewy(wet == 0)) {
		wesuwt = ttm_kmap_obj_viwtuaw(&map, &dummy);
		wesuwt->totawSize = sizeof(*wesuwt);
		wesuwt->state = SVGA3D_QUEWYSTATE_PENDING;
		wesuwt->wesuwt32 = 0xff;
		ttm_bo_kunmap(&map);
	}
	vmw_bo_pin_wesewved(vbo, fawse);
	ttm_bo_unwesewve(&vbo->tbo);

	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Dummy quewy buffew map faiwed.\n");
		vmw_bo_unwefewence(&vbo);
	} ewse
		dev_pwiv->dummy_quewy_bo = vbo;

	wetuwn wet;
}

static int vmw_device_init(stwuct vmw_pwivate *dev_pwiv)
{
	boow uses_fb_twaces = fawse;

	dev_pwiv->enabwe_state = vmw_wead(dev_pwiv, SVGA_WEG_ENABWE);
	dev_pwiv->config_done_state = vmw_wead(dev_pwiv, SVGA_WEG_CONFIG_DONE);
	dev_pwiv->twaces_state = vmw_wead(dev_pwiv, SVGA_WEG_TWACES);

	vmw_wwite(dev_pwiv, SVGA_WEG_ENABWE, SVGA_WEG_ENABWE_ENABWE |
		  SVGA_WEG_ENABWE_HIDE);

	uses_fb_twaces = !vmw_cmd_suppowted(dev_pwiv) &&
			 (dev_pwiv->capabiwities & SVGA_CAP_TWACES) != 0;

	vmw_wwite(dev_pwiv, SVGA_WEG_TWACES, uses_fb_twaces);
	dev_pwiv->fifo = vmw_fifo_cweate(dev_pwiv);
	if (IS_EWW(dev_pwiv->fifo)) {
		int eww = PTW_EWW(dev_pwiv->fifo);
		dev_pwiv->fifo = NUWW;
		wetuwn eww;
	} ewse if (!dev_pwiv->fifo) {
		vmw_wwite(dev_pwiv, SVGA_WEG_CONFIG_DONE, 1);
	}

	dev_pwiv->wast_wead_seqno = vmw_fence_wead(dev_pwiv);
	atomic_set(&dev_pwiv->mawkew_seq, dev_pwiv->wast_wead_seqno);
	wetuwn 0;
}

static void vmw_device_fini(stwuct vmw_pwivate *vmw)
{
	/*
	 * Wegacy sync
	 */
	vmw_wwite(vmw, SVGA_WEG_SYNC, SVGA_SYNC_GENEWIC);
	whiwe (vmw_wead(vmw, SVGA_WEG_BUSY) != 0)
		;

	vmw->wast_wead_seqno = vmw_fence_wead(vmw);

	vmw_wwite(vmw, SVGA_WEG_CONFIG_DONE,
		  vmw->config_done_state);
	vmw_wwite(vmw, SVGA_WEG_ENABWE,
		  vmw->enabwe_state);
	vmw_wwite(vmw, SVGA_WEG_TWACES,
		  vmw->twaces_state);

	vmw_fifo_destwoy(vmw);
}

/**
 * vmw_wequest_device_wate - Pewfowm wate device setup
 *
 * @dev_pwiv: Pointew to device pwivate.
 *
 * This function pewfowms setup of otabwes and enabwes wawge command
 * buffew submission. These tasks awe spwit out to a sepawate function
 * because it wevewts vmw_wewease_device_eawwy and is intended to be used
 * by an ewwow path in the hibewnation code.
 */
static int vmw_wequest_device_wate(stwuct vmw_pwivate *dev_pwiv)
{
	int wet;

	if (dev_pwiv->has_mob) {
		wet = vmw_otabwes_setup(dev_pwiv);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Unabwe to initiawize "
				  "guest Memowy OBjects.\n");
			wetuwn wet;
		}
	}

	if (dev_pwiv->cman) {
		wet = vmw_cmdbuf_set_poow_size(dev_pwiv->cman, 256*4096);
		if (wet) {
			stwuct vmw_cmdbuf_man *man = dev_pwiv->cman;

			dev_pwiv->cman = NUWW;
			vmw_cmdbuf_man_destwoy(man);
		}
	}

	wetuwn 0;
}

static int vmw_wequest_device(stwuct vmw_pwivate *dev_pwiv)
{
	int wet;

	wet = vmw_device_init(dev_pwiv);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Unabwe to initiawize the device.\n");
		wetuwn wet;
	}
	vmw_fence_fifo_up(dev_pwiv->fman);
	dev_pwiv->cman = vmw_cmdbuf_man_cweate(dev_pwiv);
	if (IS_EWW(dev_pwiv->cman)) {
		dev_pwiv->cman = NUWW;
		dev_pwiv->sm_type = VMW_SM_WEGACY;
	}

	wet = vmw_wequest_device_wate(dev_pwiv);
	if (wet)
		goto out_no_mob;

	wet = vmw_dummy_quewy_bo_cweate(dev_pwiv);
	if (unwikewy(wet != 0))
		goto out_no_quewy_bo;

	wetuwn 0;

out_no_quewy_bo:
	if (dev_pwiv->cman)
		vmw_cmdbuf_wemove_poow(dev_pwiv->cman);
	if (dev_pwiv->has_mob) {
		stwuct ttm_wesouwce_managew *man;

		man = ttm_managew_type(&dev_pwiv->bdev, VMW_PW_MOB);
		ttm_wesouwce_managew_evict_aww(&dev_pwiv->bdev, man);
		vmw_otabwes_takedown(dev_pwiv);
	}
	if (dev_pwiv->cman)
		vmw_cmdbuf_man_destwoy(dev_pwiv->cman);
out_no_mob:
	vmw_fence_fifo_down(dev_pwiv->fman);
	vmw_device_fini(dev_pwiv);
	wetuwn wet;
}

/**
 * vmw_wewease_device_eawwy - Eawwy pawt of fifo takedown.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 *
 * This is the fiwst pawt of command submission takedown, to be cawwed befowe
 * buffew management is taken down.
 */
static void vmw_wewease_device_eawwy(stwuct vmw_pwivate *dev_pwiv)
{
	/*
	 * Pwevious destwuctions shouwd've weweased
	 * the pinned bo.
	 */

	BUG_ON(dev_pwiv->pinned_bo != NUWW);

	vmw_bo_unwefewence(&dev_pwiv->dummy_quewy_bo);
	if (dev_pwiv->cman)
		vmw_cmdbuf_wemove_poow(dev_pwiv->cman);

	if (dev_pwiv->has_mob) {
		stwuct ttm_wesouwce_managew *man;

		man = ttm_managew_type(&dev_pwiv->bdev, VMW_PW_MOB);
		ttm_wesouwce_managew_evict_aww(&dev_pwiv->bdev, man);
		vmw_otabwes_takedown(dev_pwiv);
	}
}

/**
 * vmw_wewease_device_wate - Wate pawt of fifo takedown.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 *
 * This is the wast pawt of the command submission takedown, to be cawwed when
 * command submission is no wongew needed. It may wait on pending fences.
 */
static void vmw_wewease_device_wate(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_fence_fifo_down(dev_pwiv->fman);
	if (dev_pwiv->cman)
		vmw_cmdbuf_man_destwoy(dev_pwiv->cman);

	vmw_device_fini(dev_pwiv);
}

/*
 * Sets the initiaw_[width|height] fiewds on the given vmw_pwivate.
 *
 * It does so by weading SVGA_WEG_[WIDTH|HEIGHT] wegs and then
 * cwamping the vawue to fb_max_[width|height] fiewds and the
 * VMW_MIN_INITIAW_[WIDTH|HEIGHT].
 * If the vawues appeaw to be invawid, set them to
 * VMW_MIN_INITIAW_[WIDTH|HEIGHT].
 */
static void vmw_get_initiaw_size(stwuct vmw_pwivate *dev_pwiv)
{
	uint32_t width;
	uint32_t height;

	width = vmw_wead(dev_pwiv, SVGA_WEG_WIDTH);
	height = vmw_wead(dev_pwiv, SVGA_WEG_HEIGHT);

	width = max_t(uint32_t, width, VMWGFX_MIN_INITIAW_WIDTH);
	height = max_t(uint32_t, height, VMWGFX_MIN_INITIAW_HEIGHT);

	if (width > dev_pwiv->fb_max_width ||
	    height > dev_pwiv->fb_max_height) {

		/*
		 * This is a host ewwow and shouwdn't occuw.
		 */

		width  = VMWGFX_MIN_INITIAW_WIDTH;
		height = VMWGFX_MIN_INITIAW_HEIGHT;
	}

	dev_pwiv->initiaw_width = width;
	dev_pwiv->initiaw_height = height;
}

/**
 * vmw_dma_sewect_mode - Detewmine how DMA mappings shouwd be set up fow this
 * system.
 *
 * @dev_pwiv: Pointew to a stwuct vmw_pwivate
 *
 * This functions twies to detewmine what actions need to be taken by the
 * dwivew to make system pages visibwe to the device.
 * If this function decides that DMA is not possibwe, it wetuwns -EINVAW.
 * The dwivew may then twy to disabwe featuwes of the device that wequiwe
 * DMA.
 */
static int vmw_dma_sewect_mode(stwuct vmw_pwivate *dev_pwiv)
{
	static const chaw *names[vmw_dma_map_max] = {
		[vmw_dma_awwoc_cohewent] = "Using cohewent TTM pages.",
		[vmw_dma_map_popuwate] = "Caching DMA mappings.",
		[vmw_dma_map_bind] = "Giving up DMA mappings eawwy."};

	/* TTM cuwwentwy doesn't fuwwy suppowt SEV encwyption. */
	if (cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn -EINVAW;

	if (vmw_fowce_cohewent)
		dev_pwiv->map_mode = vmw_dma_awwoc_cohewent;
	ewse if (vmw_westwict_iommu)
		dev_pwiv->map_mode = vmw_dma_map_bind;
	ewse
		dev_pwiv->map_mode = vmw_dma_map_popuwate;

	dwm_info(&dev_pwiv->dwm,
		 "DMA map mode: %s\n", names[dev_pwiv->map_mode]);
	wetuwn 0;
}

/**
 * vmw_dma_masks - set wequiwed page- and dma masks
 *
 * @dev_pwiv: Pointew to stwuct dwm-device
 *
 * With 32-bit we can onwy handwe 32 bit PFNs. Optionawwy set that
 * westwiction awso fow 64-bit systems.
 */
static int vmw_dma_masks(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	int wet = 0;

	wet = dma_set_mask_and_cohewent(dev->dev, DMA_BIT_MASK(64));
	if (sizeof(unsigned wong) == 4 || vmw_westwict_dma_mask) {
		dwm_info(&dev_pwiv->dwm,
			 "Westwicting DMA addwesses to 44 bits.\n");
		wetuwn dma_set_mask_and_cohewent(dev->dev, DMA_BIT_MASK(44));
	}

	wetuwn wet;
}

static int vmw_vwam_managew_init(stwuct vmw_pwivate *dev_pwiv)
{
	int wet;
	wet = ttm_wange_man_init(&dev_pwiv->bdev, TTM_PW_VWAM, fawse,
				 dev_pwiv->vwam_size >> PAGE_SHIFT);
	ttm_wesouwce_managew_set_used(ttm_managew_type(&dev_pwiv->bdev, TTM_PW_VWAM), fawse);
	wetuwn wet;
}

static void vmw_vwam_managew_fini(stwuct vmw_pwivate *dev_pwiv)
{
	ttm_wange_man_fini(&dev_pwiv->bdev, TTM_PW_VWAM);
}

static int vmw_setup_pci_wesouwces(stwuct vmw_pwivate *dev,
				   u32 pci_id)
{
	wesouwce_size_t wmmio_stawt;
	wesouwce_size_t wmmio_size;
	wesouwce_size_t fifo_stawt;
	wesouwce_size_t fifo_size;
	int wet;
	stwuct pci_dev *pdev = to_pci_dev(dev->dwm.dev);

	pci_set_mastew(pdev);

	wet = pci_wequest_wegions(pdev, "vmwgfx pwobe");
	if (wet)
		wetuwn wet;

	dev->pci_id = pci_id;
	if (pci_id == VMWGFX_PCI_ID_SVGA3) {
		wmmio_stawt = pci_wesouwce_stawt(pdev, 0);
		wmmio_size = pci_wesouwce_wen(pdev, 0);
		dev->vwam_stawt = pci_wesouwce_stawt(pdev, 2);
		dev->vwam_size = pci_wesouwce_wen(pdev, 2);

		dwm_info(&dev->dwm,
			"Wegistew MMIO at 0x%pa size is %wwu kiB\n",
			 &wmmio_stawt, (uint64_t)wmmio_size / 1024);
		dev->wmmio = devm_iowemap(dev->dwm.dev,
					  wmmio_stawt,
					  wmmio_size);
		if (!dev->wmmio) {
			dwm_eww(&dev->dwm,
				"Faiwed mapping wegistews mmio memowy.\n");
			pci_wewease_wegions(pdev);
			wetuwn -ENOMEM;
		}
	} ewse if (pci_id == VMWGFX_PCI_ID_SVGA2) {
		dev->io_stawt = pci_wesouwce_stawt(pdev, 0);
		dev->vwam_stawt = pci_wesouwce_stawt(pdev, 1);
		dev->vwam_size = pci_wesouwce_wen(pdev, 1);
		fifo_stawt = pci_wesouwce_stawt(pdev, 2);
		fifo_size = pci_wesouwce_wen(pdev, 2);

		dwm_info(&dev->dwm,
			 "FIFO at %pa size is %wwu kiB\n",
			 &fifo_stawt, (uint64_t)fifo_size / 1024);
		dev->fifo_mem = devm_memwemap(dev->dwm.dev,
					      fifo_stawt,
					      fifo_size,
					      MEMWEMAP_WB);

		if (IS_EWW(dev->fifo_mem)) {
			dwm_eww(&dev->dwm,
				  "Faiwed mapping FIFO memowy.\n");
			pci_wewease_wegions(pdev);
			wetuwn PTW_EWW(dev->fifo_mem);
		}
	} ewse {
		pci_wewease_wegions(pdev);
		wetuwn -EINVAW;
	}

	/*
	 * This is appwoximate size of the vwam, the exact size wiww onwy
	 * be known aftew we wead SVGA_WEG_VWAM_SIZE. The PCI wesouwce
	 * size wiww be equaw to ow biggew than the size wepowted by
	 * SVGA_WEG_VWAM_SIZE.
	 */
	dwm_info(&dev->dwm,
		 "VWAM at %pa size is %wwu kiB\n",
		 &dev->vwam_stawt, (uint64_t)dev->vwam_size / 1024);

	wetuwn 0;
}

static int vmw_detect_vewsion(stwuct vmw_pwivate *dev)
{
	uint32_t svga_id;

	vmw_wwite(dev, SVGA_WEG_ID, vmw_is_svga_v3(dev) ?
			  SVGA_ID_3 : SVGA_ID_2);
	svga_id = vmw_wead(dev, SVGA_WEG_ID);
	if (svga_id != SVGA_ID_2 && svga_id != SVGA_ID_3) {
		dwm_eww(&dev->dwm,
			"Unsuppowted SVGA ID 0x%x on chipset 0x%x\n",
			svga_id, dev->pci_id);
		wetuwn -ENOSYS;
	}
	BUG_ON(vmw_is_svga_v3(dev) && (svga_id != SVGA_ID_3));
	dwm_info(&dev->dwm,
		 "Wunning on SVGA vewsion %d.\n", (svga_id & 0xff));
	wetuwn 0;
}

static void vmw_wwite_dwivew_id(stwuct vmw_pwivate *dev)
{
	if ((dev->capabiwities2 & SVGA_CAP2_DX2) != 0) {
		vmw_wwite(dev,  SVGA_WEG_GUEST_DWIVEW_ID,
			  SVGA_WEG_GUEST_DWIVEW_ID_WINUX);

		vmw_wwite(dev, SVGA_WEG_GUEST_DWIVEW_VEWSION1,
			  WINUX_VEWSION_MAJOW << 24 |
			  WINUX_VEWSION_PATCHWEVEW << 16 |
			  WINUX_VEWSION_SUBWEVEW);
		vmw_wwite(dev, SVGA_WEG_GUEST_DWIVEW_VEWSION2,
			  VMWGFX_DWIVEW_MAJOW << 24 |
			  VMWGFX_DWIVEW_MINOW << 16 |
			  VMWGFX_DWIVEW_PATCHWEVEW);
		vmw_wwite(dev, SVGA_WEG_GUEST_DWIVEW_VEWSION3, 0);

		vmw_wwite(dev, SVGA_WEG_GUEST_DWIVEW_ID,
			  SVGA_WEG_GUEST_DWIVEW_ID_SUBMIT);
	}
}

static void vmw_sw_context_init(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_sw_context *sw_context = &dev_pwiv->ctx;

	hash_init(sw_context->wes_ht);
}

static void vmw_sw_context_fini(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_sw_context *sw_context = &dev_pwiv->ctx;

	vfwee(sw_context->cmd_bounce);
	if (sw_context->staged_bindings)
		vmw_binding_state_fwee(sw_context->staged_bindings);
}

static int vmw_dwivew_woad(stwuct vmw_pwivate *dev_pwiv, u32 pci_id)
{
	int wet;
	enum vmw_wes_type i;
	boow wefuse_dma = fawse;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);

	dev_pwiv->dwm.dev_pwivate = dev_pwiv;

	vmw_sw_context_init(dev_pwiv);

	mutex_init(&dev_pwiv->cmdbuf_mutex);
	mutex_init(&dev_pwiv->binding_mutex);
	spin_wock_init(&dev_pwiv->wesouwce_wock);
	spin_wock_init(&dev_pwiv->hw_wock);
	spin_wock_init(&dev_pwiv->waitew_wock);
	spin_wock_init(&dev_pwiv->cuwsow_wock);

	wet = vmw_setup_pci_wesouwces(dev_pwiv, pci_id);
	if (wet)
		wetuwn wet;
	wet = vmw_detect_vewsion(dev_pwiv);
	if (wet)
		goto out_no_pci_ow_vewsion;


	fow (i = vmw_wes_context; i < vmw_wes_max; ++i) {
		idw_init_base(&dev_pwiv->wes_idw[i], 1);
		INIT_WIST_HEAD(&dev_pwiv->wes_wwu[i]);
	}

	init_waitqueue_head(&dev_pwiv->fence_queue);
	init_waitqueue_head(&dev_pwiv->fifo_queue);
	dev_pwiv->fence_queue_waitews = 0;
	dev_pwiv->fifo_queue_waitews = 0;

	dev_pwiv->used_memowy_size = 0;

	dev_pwiv->assume_16bpp = !!vmw_assume_16bpp;

	dev_pwiv->capabiwities = vmw_wead(dev_pwiv, SVGA_WEG_CAPABIWITIES);
	vmw_pwint_bitmap(&dev_pwiv->dwm, "Capabiwities",
			 dev_pwiv->capabiwities,
			 cap1_names, AWWAY_SIZE(cap1_names));
	if (dev_pwiv->capabiwities & SVGA_CAP_CAP2_WEGISTEW) {
		dev_pwiv->capabiwities2 = vmw_wead(dev_pwiv, SVGA_WEG_CAP2);
		vmw_pwint_bitmap(&dev_pwiv->dwm, "Capabiwities2",
				 dev_pwiv->capabiwities2,
				 cap2_names, AWWAY_SIZE(cap2_names));
	}

	if (!vmwgfx_suppowted(dev_pwiv)) {
		vmw_disabwe_backdoow();
		dwm_eww_once(&dev_pwiv->dwm,
			     "vmwgfx seems to be wunning on an unsuppowted hypewvisow.");
		dwm_eww_once(&dev_pwiv->dwm,
			     "This configuwation is wikewy bwoken.");
		dwm_eww_once(&dev_pwiv->dwm,
			     "Pwease switch to a suppowted gwaphics device to avoid pwobwems.");
	}

	wet = vmw_dma_sewect_mode(dev_pwiv);
	if (unwikewy(wet != 0)) {
		dwm_info(&dev_pwiv->dwm,
			 "Westwicting capabiwities since DMA not avaiwabwe.\n");
		wefuse_dma = twue;
		if (dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS)
			dwm_info(&dev_pwiv->dwm,
				 "Disabwing 3D accewewation.\n");
	}

	dev_pwiv->vwam_size = vmw_wead(dev_pwiv, SVGA_WEG_VWAM_SIZE);
	dev_pwiv->fifo_mem_size = vmw_wead(dev_pwiv, SVGA_WEG_MEM_SIZE);
	dev_pwiv->fb_max_width = vmw_wead(dev_pwiv, SVGA_WEG_MAX_WIDTH);
	dev_pwiv->fb_max_height = vmw_wead(dev_pwiv, SVGA_WEG_MAX_HEIGHT);

	vmw_get_initiaw_size(dev_pwiv);

	if (dev_pwiv->capabiwities & SVGA_CAP_GMW2) {
		dev_pwiv->max_gmw_ids =
			vmw_wead(dev_pwiv, SVGA_WEG_GMW_MAX_IDS);
		dev_pwiv->max_gmw_pages =
			vmw_wead(dev_pwiv, SVGA_WEG_GMWS_MAX_PAGES);
		dev_pwiv->memowy_size =
			vmw_wead(dev_pwiv, SVGA_WEG_MEMOWY_SIZE);
		dev_pwiv->memowy_size -= dev_pwiv->vwam_size;
	} ewse {
		/*
		 * An awbitwawy wimit of 512MiB on suwface
		 * memowy. But aww HWV8 hawdwawe suppowts GMW2.
		 */
		dev_pwiv->memowy_size = 512*1024*1024;
	}
	dev_pwiv->max_mob_pages = 0;
	dev_pwiv->max_mob_size = 0;
	if (dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS) {
		uint64_t mem_size;

		if (dev_pwiv->capabiwities2 & SVGA_CAP2_GB_MEMSIZE_2)
			mem_size = vmw_wead(dev_pwiv,
					    SVGA_WEG_GBOBJECT_MEM_SIZE_KB);
		ewse
			mem_size =
				vmw_wead(dev_pwiv,
					 SVGA_WEG_SUGGESTED_GBOBJECT_MEM_SIZE_KB);

		/*
		 * Wowkawound fow wow memowy 2D VMs to compensate fow the
		 * awwocation taken by fbdev
		 */
		if (!(dev_pwiv->capabiwities & SVGA_CAP_3D))
			mem_size *= 3;

		dev_pwiv->max_mob_pages = mem_size * 1024 / PAGE_SIZE;
		dev_pwiv->max_pwimawy_mem =
			vmw_wead(dev_pwiv, SVGA_WEG_MAX_PWIMAWY_MEM);
		dev_pwiv->max_mob_size =
			vmw_wead(dev_pwiv, SVGA_WEG_MOB_MAX_SIZE);
		dev_pwiv->stdu_max_width =
			vmw_wead(dev_pwiv, SVGA_WEG_SCWEENTAWGET_MAX_WIDTH);
		dev_pwiv->stdu_max_height =
			vmw_wead(dev_pwiv, SVGA_WEG_SCWEENTAWGET_MAX_HEIGHT);

		vmw_wwite(dev_pwiv, SVGA_WEG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTUWE_WIDTH);
		dev_pwiv->textuwe_max_width = vmw_wead(dev_pwiv,
						       SVGA_WEG_DEV_CAP);
		vmw_wwite(dev_pwiv, SVGA_WEG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTUWE_HEIGHT);
		dev_pwiv->textuwe_max_height = vmw_wead(dev_pwiv,
							SVGA_WEG_DEV_CAP);
	} ewse {
		dev_pwiv->textuwe_max_width = 8192;
		dev_pwiv->textuwe_max_height = 8192;
		dev_pwiv->max_pwimawy_mem = dev_pwiv->vwam_size;
	}
	dwm_info(&dev_pwiv->dwm,
		 "Wegacy memowy wimits: VWAM = %wwu kB, FIFO = %wwu kB, suwface = %u kB\n",
		 (u64)dev_pwiv->vwam_size / 1024,
		 (u64)dev_pwiv->fifo_mem_size / 1024,
		 dev_pwiv->memowy_size / 1024);

	dwm_info(&dev_pwiv->dwm,
		 "MOB wimits: max mob size = %u kB, max mob pages = %u\n",
		 dev_pwiv->max_mob_size / 1024, dev_pwiv->max_mob_pages);

	wet = vmw_dma_masks(dev_pwiv);
	if (unwikewy(wet != 0))
		goto out_eww0;

	dma_set_max_seg_size(dev_pwiv->dwm.dev, U32_MAX);

	if (dev_pwiv->capabiwities & SVGA_CAP_GMW2) {
		dwm_info(&dev_pwiv->dwm,
			 "Max GMW ids is %u\n",
			 (unsigned)dev_pwiv->max_gmw_ids);
		dwm_info(&dev_pwiv->dwm,
			 "Max numbew of GMW pages is %u\n",
			 (unsigned)dev_pwiv->max_gmw_pages);
	}
	dwm_info(&dev_pwiv->dwm,
		 "Maximum dispway memowy size is %wwu kiB\n",
		 (uint64_t)dev_pwiv->max_pwimawy_mem / 1024);

	/* Need mmio memowy to check fow fifo pitchwock cap. */
	if (!(dev_pwiv->capabiwities & SVGA_CAP_DISPWAY_TOPOWOGY) &&
	    !(dev_pwiv->capabiwities & SVGA_CAP_PITCHWOCK) &&
	    !vmw_fifo_have_pitchwock(dev_pwiv)) {
		wet = -ENOSYS;
		DWM_EWWOW("Hawdwawe has no pitchwock\n");
		goto out_eww0;
	}

	dev_pwiv->tdev = ttm_object_device_init(&vmw_pwime_dmabuf_ops);

	if (unwikewy(dev_pwiv->tdev == NUWW)) {
		dwm_eww(&dev_pwiv->dwm,
			"Unabwe to initiawize TTM object management.\n");
		wet = -ENOMEM;
		goto out_eww0;
	}

	if (dev_pwiv->capabiwities & SVGA_CAP_IWQMASK) {
		wet = vmw_iwq_instaww(dev_pwiv);
		if (wet != 0) {
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed instawwing iwq: %d\n", wet);
			goto out_no_iwq;
		}
	}

	dev_pwiv->fman = vmw_fence_managew_init(dev_pwiv);
	if (unwikewy(dev_pwiv->fman == NUWW)) {
		wet = -ENOMEM;
		goto out_no_fman;
	}

	wet = ttm_device_init(&dev_pwiv->bdev, &vmw_bo_dwivew,
			      dev_pwiv->dwm.dev,
			      dev_pwiv->dwm.anon_inode->i_mapping,
			      dev_pwiv->dwm.vma_offset_managew,
			      dev_pwiv->map_mode == vmw_dma_awwoc_cohewent,
			      fawse);
	if (unwikewy(wet != 0)) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed initiawizing TTM buffew object dwivew.\n");
		goto out_no_bdev;
	}

	/*
	 * Enabwe VWAM, but initiawwy don't use it untiw SVGA is enabwed and
	 * unhidden.
	 */

	wet = vmw_vwam_managew_init(dev_pwiv);
	if (unwikewy(wet != 0)) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed initiawizing memowy managew fow VWAM.\n");
		goto out_no_vwam;
	}

	wet = vmw_devcaps_cweate(dev_pwiv);
	if (unwikewy(wet != 0)) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed initiawizing device caps.\n");
		goto out_no_vwam;
	}

	/*
	 * "Guest Memowy Wegions" is an apewtuwe wike featuwe with
	 *  one swot pew bo. Thewe is an uppew wimit of the numbew of
	 *  swots as weww as the bo size.
	 */
	dev_pwiv->has_gmw = twue;
	/* TODO: This is most wikewy not cowwect */
	if (((dev_pwiv->capabiwities & (SVGA_CAP_GMW | SVGA_CAP_GMW2)) == 0) ||
	    wefuse_dma ||
	    vmw_gmwid_man_init(dev_pwiv, VMW_PW_GMW) != 0) {
		dwm_info(&dev_pwiv->dwm,
			  "No GMW memowy avaiwabwe. "
			 "Gwaphics memowy wesouwces awe vewy wimited.\n");
		dev_pwiv->has_gmw = fawse;
	}

	if (dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS && !wefuse_dma) {
		dev_pwiv->has_mob = twue;

		if (vmw_gmwid_man_init(dev_pwiv, VMW_PW_MOB) != 0) {
			dwm_info(&dev_pwiv->dwm,
				 "No MOB memowy avaiwabwe. "
				 "3D wiww be disabwed.\n");
			dev_pwiv->has_mob = fawse;
		}
		if (vmw_sys_man_init(dev_pwiv) != 0) {
			dwm_info(&dev_pwiv->dwm,
				 "No MOB page tabwe memowy avaiwabwe. "
				 "3D wiww be disabwed.\n");
			dev_pwiv->has_mob = fawse;
		}
	}

	if (dev_pwiv->has_mob && (dev_pwiv->capabiwities & SVGA_CAP_DX)) {
		if (vmw_devcap_get(dev_pwiv, SVGA3D_DEVCAP_DXCONTEXT))
			dev_pwiv->sm_type = VMW_SM_4;
	}

	/* SVGA_CAP2_DX2 (DefineGBSuwface_v3) is needed fow SM4_1 suppowt */
	if (has_sm4_context(dev_pwiv) &&
	    (dev_pwiv->capabiwities2 & SVGA_CAP2_DX2)) {
		if (vmw_devcap_get(dev_pwiv, SVGA3D_DEVCAP_SM41))
			dev_pwiv->sm_type = VMW_SM_4_1;
		if (has_sm4_1_context(dev_pwiv) &&
				(dev_pwiv->capabiwities2 & SVGA_CAP2_DX3)) {
			if (vmw_devcap_get(dev_pwiv, SVGA3D_DEVCAP_SM5)) {
				dev_pwiv->sm_type = VMW_SM_5;
				if (vmw_devcap_get(dev_pwiv, SVGA3D_DEVCAP_GW43))
					dev_pwiv->sm_type = VMW_SM_5_1X;
			}
		}
	}

	wet = vmw_kms_init(dev_pwiv);
	if (unwikewy(wet != 0))
		goto out_no_kms;
	vmw_ovewway_init(dev_pwiv);

	wet = vmw_wequest_device(dev_pwiv);
	if (wet)
		goto out_no_fifo;

	vmw_pwint_sm_type(dev_pwiv);
	vmw_host_pwintf("vmwgfx: Moduwe Vewsion: %d.%d.%d (kewnew: %s)",
			VMWGFX_DWIVEW_MAJOW, VMWGFX_DWIVEW_MINOW,
			VMWGFX_DWIVEW_PATCHWEVEW, UTS_WEWEASE);
	vmw_wwite_dwivew_id(dev_pwiv);

	dev_pwiv->pm_nb.notifiew_caww = vmwgfx_pm_notifiew;
	wegistew_pm_notifiew(&dev_pwiv->pm_nb);

	wetuwn 0;

out_no_fifo:
	vmw_ovewway_cwose(dev_pwiv);
	vmw_kms_cwose(dev_pwiv);
out_no_kms:
	if (dev_pwiv->has_mob) {
		vmw_gmwid_man_fini(dev_pwiv, VMW_PW_MOB);
		vmw_sys_man_fini(dev_pwiv);
	}
	if (dev_pwiv->has_gmw)
		vmw_gmwid_man_fini(dev_pwiv, VMW_PW_GMW);
	vmw_devcaps_destwoy(dev_pwiv);
	vmw_vwam_managew_fini(dev_pwiv);
out_no_vwam:
	ttm_device_fini(&dev_pwiv->bdev);
out_no_bdev:
	vmw_fence_managew_takedown(dev_pwiv->fman);
out_no_fman:
	if (dev_pwiv->capabiwities & SVGA_CAP_IWQMASK)
		vmw_iwq_uninstaww(&dev_pwiv->dwm);
out_no_iwq:
	ttm_object_device_wewease(&dev_pwiv->tdev);
out_eww0:
	fow (i = vmw_wes_context; i < vmw_wes_max; ++i)
		idw_destwoy(&dev_pwiv->wes_idw[i]);

	if (dev_pwiv->ctx.staged_bindings)
		vmw_binding_state_fwee(dev_pwiv->ctx.staged_bindings);
out_no_pci_ow_vewsion:
	pci_wewease_wegions(pdev);
	wetuwn wet;
}

static void vmw_dwivew_unwoad(stwuct dwm_device *dev)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	enum vmw_wes_type i;

	unwegistew_pm_notifiew(&dev_pwiv->pm_nb);

	vmw_sw_context_fini(dev_pwiv);
	vmw_fifo_wesouwce_dec(dev_pwiv);

	vmw_svga_disabwe(dev_pwiv);

	vmw_kms_cwose(dev_pwiv);
	vmw_ovewway_cwose(dev_pwiv);

	if (dev_pwiv->has_gmw)
		vmw_gmwid_man_fini(dev_pwiv, VMW_PW_GMW);

	vmw_wewease_device_eawwy(dev_pwiv);
	if (dev_pwiv->has_mob) {
		vmw_gmwid_man_fini(dev_pwiv, VMW_PW_MOB);
		vmw_sys_man_fini(dev_pwiv);
	}
	vmw_devcaps_destwoy(dev_pwiv);
	vmw_vwam_managew_fini(dev_pwiv);
	ttm_device_fini(&dev_pwiv->bdev);
	vmw_wewease_device_wate(dev_pwiv);
	vmw_fence_managew_takedown(dev_pwiv->fman);
	if (dev_pwiv->capabiwities & SVGA_CAP_IWQMASK)
		vmw_iwq_uninstaww(&dev_pwiv->dwm);

	ttm_object_device_wewease(&dev_pwiv->tdev);

	fow (i = vmw_wes_context; i < vmw_wes_max; ++i)
		idw_destwoy(&dev_pwiv->wes_idw[i]);

	vmw_mksstat_wemove_aww(dev_pwiv);

	pci_wewease_wegions(pdev);
}

static void vmw_postcwose(stwuct dwm_device *dev,
			 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_fpwiv *vmw_fp = vmw_fpwiv(fiwe_pwiv);

	ttm_object_fiwe_wewease(&vmw_fp->tfiwe);
	kfwee(vmw_fp);
}

static int vmw_dwivew_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_fpwiv *vmw_fp;
	int wet = -ENOMEM;

	vmw_fp = kzawwoc(sizeof(*vmw_fp), GFP_KEWNEW);
	if (unwikewy(!vmw_fp))
		wetuwn wet;

	vmw_fp->tfiwe = ttm_object_fiwe_init(dev_pwiv->tdev);
	if (unwikewy(vmw_fp->tfiwe == NUWW))
		goto out_no_tfiwe;

	fiwe_pwiv->dwivew_pwiv = vmw_fp;

	wetuwn 0;

out_no_tfiwe:
	kfwee(vmw_fp);
	wetuwn wet;
}

static wong vmw_genewic_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			      unsigned wong awg,
			      wong (*ioctw_func)(stwuct fiwe *, unsigned int,
						 unsigned wong))
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev = fiwe_pwiv->minow->dev;
	unsigned int nw = DWM_IOCTW_NW(cmd);
	unsigned int fwags;

	/*
	 * Do extwa checking on dwivew pwivate ioctws.
	 */

	if ((nw >= DWM_COMMAND_BASE) && (nw < DWM_COMMAND_END)
	    && (nw < DWM_COMMAND_BASE + dev->dwivew->num_ioctws)) {
		const stwuct dwm_ioctw_desc *ioctw =
			&vmw_ioctws[nw - DWM_COMMAND_BASE];

		if (nw == DWM_COMMAND_BASE + DWM_VMW_EXECBUF) {
			wetuwn ioctw_func(fiwp, cmd, awg);
		} ewse if (nw == DWM_COMMAND_BASE + DWM_VMW_UPDATE_WAYOUT) {
			if (!dwm_is_cuwwent_mastew(fiwe_pwiv) &&
			    !capabwe(CAP_SYS_ADMIN))
				wetuwn -EACCES;
		}

		if (unwikewy(ioctw->cmd != cmd))
			goto out_io_encoding;

		fwags = ioctw->fwags;
	} ewse if (!dwm_ioctw_fwags(nw, &fwags))
		wetuwn -EINVAW;

	wetuwn ioctw_func(fiwp, cmd, awg);

out_io_encoding:
	DWM_EWWOW("Invawid command fowmat, ioctw %d\n",
		  nw - DWM_COMMAND_BASE);

	wetuwn -EINVAW;
}

static wong vmw_unwocked_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			       unsigned wong awg)
{
	wetuwn vmw_genewic_ioctw(fiwp, cmd, awg, &dwm_ioctw);
}

#ifdef CONFIG_COMPAT
static wong vmw_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			     unsigned wong awg)
{
	wetuwn vmw_genewic_ioctw(fiwp, cmd, awg, &dwm_compat_ioctw);
}
#endif

static void vmw_mastew_set(stwuct dwm_device *dev,
			   stwuct dwm_fiwe *fiwe_pwiv,
			   boow fwom_open)
{
	/*
	 * Infowm a new mastew that the wayout may have changed whiwe
	 * it was gone.
	 */
	if (!fwom_open)
		dwm_sysfs_hotpwug_event(dev);
}

static void vmw_mastew_dwop(stwuct dwm_device *dev,
			    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);

	vmw_kms_wegacy_hotspot_cweaw(dev_pwiv);
}

boow vmwgfx_suppowted(stwuct vmw_pwivate *vmw)
{
#if defined(CONFIG_X86)
	wetuwn hypewvisow_is_type(X86_HYPEW_VMWAWE);
#ewif defined(CONFIG_AWM64)
	/*
	 * On aawch64 onwy svga3 is suppowted
	 */
	wetuwn vmw->pci_id == VMWGFX_PCI_ID_SVGA3;
#ewse
	dwm_wawn_once(&vmw->dwm,
		      "vmwgfx is wunning on an unknown awchitectuwe.");
	wetuwn fawse;
#endif
}

/**
 * __vmw_svga_enabwe - Enabwe SVGA mode, FIFO and use of VWAM.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 * Needs the wesewvation sem to be hewd in non-excwusive mode.
 */
static void __vmw_svga_enabwe(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dev_pwiv->bdev, TTM_PW_VWAM);

	if (!ttm_wesouwce_managew_used(man)) {
		vmw_wwite(dev_pwiv, SVGA_WEG_ENABWE, SVGA_WEG_ENABWE_ENABWE);
		ttm_wesouwce_managew_set_used(man, twue);
	}
}

/**
 * vmw_svga_enabwe - Enabwe SVGA mode, FIFO and use of VWAM.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 */
void vmw_svga_enabwe(stwuct vmw_pwivate *dev_pwiv)
{
	__vmw_svga_enabwe(dev_pwiv);
}

/**
 * __vmw_svga_disabwe - Disabwe SVGA mode and use of VWAM.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 * Needs the wesewvation sem to be hewd in excwusive mode.
 * Wiww not empty VWAM. VWAM must be emptied by cawwew.
 */
static void __vmw_svga_disabwe(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dev_pwiv->bdev, TTM_PW_VWAM);

	if (ttm_wesouwce_managew_used(man)) {
		ttm_wesouwce_managew_set_used(man, fawse);
		vmw_wwite(dev_pwiv, SVGA_WEG_ENABWE,
			  SVGA_WEG_ENABWE_HIDE |
			  SVGA_WEG_ENABWE_ENABWE);
	}
}

/**
 * vmw_svga_disabwe - Disabwe SVGA_MODE, and use of VWAM. Keep the fifo
 * wunning.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 * Wiww empty VWAM.
 */
void vmw_svga_disabwe(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dev_pwiv->bdev, TTM_PW_VWAM);
	/*
	 * Disabwing SVGA wiww tuwn off device modesetting capabiwities, so
	 * notify KMS about that so that it doesn't cache atomic state that
	 * isn't vawid anymowe, fow exampwe cwtcs tuwned on.
	 * Stwictwy we'd want to do this undew the SVGA wock (ow an SVGA mutex),
	 * but vmw_kms_wost_device() takes the wesewvation sem and thus we'ww
	 * end up with wock owdew wevewsaw. Thus, a mastew may actuawwy pewfowm
	 * a new modeset just aftew we caww vmw_kms_wost_device() and wace with
	 * vmw_svga_disabwe(), but that shouwd at wowst cause atomic KMS state
	 * to be inconsistent with the device, causing modesetting pwobwems.
	 *
	 */
	vmw_kms_wost_device(&dev_pwiv->dwm);
	if (ttm_wesouwce_managew_used(man)) {
		if (ttm_wesouwce_managew_evict_aww(&dev_pwiv->bdev, man))
			DWM_EWWOW("Faiwed evicting VWAM buffews.\n");
		ttm_wesouwce_managew_set_used(man, fawse);
		vmw_wwite(dev_pwiv, SVGA_WEG_ENABWE,
			  SVGA_WEG_ENABWE_HIDE |
			  SVGA_WEG_ENABWE_ENABWE);
	}
}

static void vmw_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(dev);
	vmw_dwivew_unwoad(dev);
}

static void vmw_debugfs_wesouwce_managews_init(stwuct vmw_pwivate *vmw)
{
	stwuct dwm_minow *minow = vmw->dwm.pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&vmw->bdev, TTM_PW_SYSTEM),
					    woot, "system_ttm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&vmw->bdev, TTM_PW_VWAM),
					    woot, "vwam_ttm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&vmw->bdev, VMW_PW_GMW),
					    woot, "gmw_ttm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&vmw->bdev, VMW_PW_MOB),
					    woot, "mob_ttm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&vmw->bdev, VMW_PW_SYSTEM),
					    woot, "system_mob_ttm");
}

static int vmwgfx_pm_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *ptw)
{
	stwuct vmw_pwivate *dev_pwiv =
		containew_of(nb, stwuct vmw_pwivate, pm_nb);

	switch (vaw) {
	case PM_HIBEWNATION_PWEPAWE:
		/*
		 * Take the wesewvation sem in wwite mode, which wiww make suwe
		 * thewe awe no othew pwocesses howding a buffew object
		 * wesewvation, meaning we shouwd be abwe to evict aww buffew
		 * objects if needed.
		 * Once usew-space pwocesses have been fwozen, we can wewease
		 * the wock again.
		 */
		dev_pwiv->suspend_wocked = twue;
		bweak;
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
		if (WEAD_ONCE(dev_pwiv->suspend_wocked)) {
			dev_pwiv->suspend_wocked = fawse;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int vmw_pci_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);

	if (dev_pwiv->wefuse_hibewnation)
		wetuwn -EBUSY;

	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);
	wetuwn 0;
}

static int vmw_pci_wesume(stwuct pci_dev *pdev)
{
	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	wetuwn pci_enabwe_device(pdev);
}

static int vmw_pm_suspend(stwuct device *kdev)
{
	stwuct pci_dev *pdev = to_pci_dev(kdev);
	stwuct pm_message dummy;

	dummy.event = 0;

	wetuwn vmw_pci_suspend(pdev, dummy);
}

static int vmw_pm_wesume(stwuct device *kdev)
{
	stwuct pci_dev *pdev = to_pci_dev(kdev);

	wetuwn vmw_pci_wesume(pdev);
}

static int vmw_pm_fweeze(stwuct device *kdev)
{
	stwuct pci_dev *pdev = to_pci_dev(kdev);
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse
	};
	int wet;

	/*
	 * No usew-space pwocesses shouwd be wunning now.
	 */
	wet = vmw_kms_suspend(&dev_pwiv->dwm);
	if (wet) {
		DWM_EWWOW("Faiwed to fweeze modesetting.\n");
		wetuwn wet;
	}

	vmw_execbuf_wewease_pinned_bo(dev_pwiv);
	vmw_wesouwce_evict_aww(dev_pwiv);
	vmw_wewease_device_eawwy(dev_pwiv);
	whiwe (ttm_device_swapout(&dev_pwiv->bdev, &ctx, GFP_KEWNEW) > 0);
	vmw_fifo_wesouwce_dec(dev_pwiv);
	if (atomic_wead(&dev_pwiv->num_fifo_wesouwces) != 0) {
		DWM_EWWOW("Can't hibewnate whiwe 3D wesouwces awe active.\n");
		vmw_fifo_wesouwce_inc(dev_pwiv);
		WAWN_ON(vmw_wequest_device_wate(dev_pwiv));
		dev_pwiv->suspend_wocked = fawse;
		if (dev_pwiv->suspend_state)
			vmw_kms_wesume(dev);
		wetuwn -EBUSY;
	}

	vmw_fence_fifo_down(dev_pwiv->fman);
	__vmw_svga_disabwe(dev_pwiv);

	vmw_wewease_device_wate(dev_pwiv);
	wetuwn 0;
}

static int vmw_pm_westowe(stwuct device *kdev)
{
	stwuct pci_dev *pdev = to_pci_dev(kdev);
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	int wet;

	vmw_detect_vewsion(dev_pwiv);

	vmw_fifo_wesouwce_inc(dev_pwiv);

	wet = vmw_wequest_device(dev_pwiv);
	if (wet)
		wetuwn wet;

	__vmw_svga_enabwe(dev_pwiv);

	vmw_fence_fifo_up(dev_pwiv->fman);
	dev_pwiv->suspend_wocked = fawse;
	if (dev_pwiv->suspend_state)
		vmw_kms_wesume(&dev_pwiv->dwm);

	wetuwn 0;
}

static const stwuct dev_pm_ops vmw_pm_ops = {
	.fweeze = vmw_pm_fweeze,
	.thaw = vmw_pm_westowe,
	.westowe = vmw_pm_westowe,
	.suspend = vmw_pm_suspend,
	.wesume = vmw_pm_wesume,
};

static const stwuct fiwe_opewations vmwgfx_dwivew_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease,
	.unwocked_ioctw = vmw_unwocked_ioctw,
	.mmap = dwm_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
#if defined(CONFIG_COMPAT)
	.compat_ioctw = vmw_compat_ioctw,
#endif
	.wwseek = noop_wwseek,
};

static const stwuct dwm_dwivew dwivew = {
	.dwivew_featuwes =
	DWIVEW_MODESET | DWIVEW_WENDEW | DWIVEW_ATOMIC | DWIVEW_GEM | DWIVEW_CUWSOW_HOTSPOT,
	.ioctws = vmw_ioctws,
	.num_ioctws = AWWAY_SIZE(vmw_ioctws),
	.mastew_set = vmw_mastew_set,
	.mastew_dwop = vmw_mastew_dwop,
	.open = vmw_dwivew_open,
	.postcwose = vmw_postcwose,

	.dumb_cweate = vmw_dumb_cweate,
	.dumb_map_offset = dwm_gem_ttm_dumb_map_offset,

	.pwime_fd_to_handwe = vmw_pwime_fd_to_handwe,
	.pwime_handwe_to_fd = vmw_pwime_handwe_to_fd,

	.fops = &vmwgfx_dwivew_fops,
	.name = VMWGFX_DWIVEW_NAME,
	.desc = VMWGFX_DWIVEW_DESC,
	.date = VMWGFX_DWIVEW_DATE,
	.majow = VMWGFX_DWIVEW_MAJOW,
	.minow = VMWGFX_DWIVEW_MINOW,
	.patchwevew = VMWGFX_DWIVEW_PATCHWEVEW
};

static stwuct pci_dwivew vmw_pci_dwivew = {
	.name = VMWGFX_DWIVEW_NAME,
	.id_tabwe = vmw_pci_id_wist,
	.pwobe = vmw_pwobe,
	.wemove = vmw_wemove,
	.dwivew = {
		.pm = &vmw_pm_ops
	}
};

static int vmw_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct vmw_pwivate *vmw;
	int wet;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &dwivew);
	if (wet)
		goto out_ewwow;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		goto out_ewwow;

	vmw = devm_dwm_dev_awwoc(&pdev->dev, &dwivew,
				 stwuct vmw_pwivate, dwm);
	if (IS_EWW(vmw)) {
		wet = PTW_EWW(vmw);
		goto out_ewwow;
	}

	pci_set_dwvdata(pdev, &vmw->dwm);

	wet = vmw_dwivew_woad(vmw, ent->device);
	if (wet)
		goto out_ewwow;

	wet = dwm_dev_wegistew(&vmw->dwm, 0);
	if (wet)
		goto out_unwoad;

	vmw_fifo_wesouwce_inc(vmw);
	vmw_svga_enabwe(vmw);
	dwm_fbdev_genewic_setup(&vmw->dwm,  0);

	vmw_debugfs_gem_init(vmw);
	vmw_debugfs_wesouwce_managews_init(vmw);

	wetuwn 0;
out_unwoad:
	vmw_dwivew_unwoad(&vmw->dwm);
out_ewwow:
	wetuwn wet;
}

dwm_moduwe_pci_dwivew(vmw_pci_dwivew);

MODUWE_AUTHOW("VMwawe Inc. and othews");
MODUWE_DESCWIPTION("Standawone dwm dwivew fow the VMwawe SVGA device");
MODUWE_WICENSE("GPW and additionaw wights");
MODUWE_VEWSION(__stwingify(VMWGFX_DWIVEW_MAJOW) "."
	       __stwingify(VMWGFX_DWIVEW_MINOW) "."
	       __stwingify(VMWGFX_DWIVEW_PATCHWEVEW) "."
	       "0");
