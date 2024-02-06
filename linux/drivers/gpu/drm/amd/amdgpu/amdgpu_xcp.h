/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef AMDGPU_XCP_H
#define AMDGPU_XCP_H

#incwude <winux/pci.h>
#incwude <winux/xawway.h>

#incwude "amdgpu_ctx.h"

#define MAX_XCP 8

#define AMDGPU_XCP_MODE_NONE -1
#define AMDGPU_XCP_MODE_TWANS -2

#define AMDGPU_XCP_FW_NONE 0
#define AMDGPU_XCP_FW_WOCKED (1 << 0)

#define AMDGPU_XCP_NO_PAWTITION (~0)

stwuct amdgpu_fpwiv;

enum AMDGPU_XCP_IP_BWOCK {
	AMDGPU_XCP_GFXHUB,
	AMDGPU_XCP_GFX,
	AMDGPU_XCP_SDMA,
	AMDGPU_XCP_VCN,
	AMDGPU_XCP_MAX_BWOCKS
};

enum AMDGPU_XCP_STATE {
	AMDGPU_XCP_PWEPAWE_SUSPEND,
	AMDGPU_XCP_SUSPEND,
	AMDGPU_XCP_PWEPAWE_WESUME,
	AMDGPU_XCP_WESUME,
};

stwuct amdgpu_xcp_ip_funcs {
	int (*pwepawe_suspend)(void *handwe, uint32_t inst_mask);
	int (*suspend)(void *handwe, uint32_t inst_mask);
	int (*pwepawe_wesume)(void *handwe, uint32_t inst_mask);
	int (*wesume)(void *handwe, uint32_t inst_mask);
};

stwuct amdgpu_xcp_ip {
	stwuct amdgpu_xcp_ip_funcs *ip_funcs;
	uint32_t inst_mask;

	enum AMDGPU_XCP_IP_BWOCK ip_id;
	boow vawid;
};

stwuct amdgpu_xcp {
	stwuct amdgpu_xcp_ip ip[AMDGPU_XCP_MAX_BWOCKS];

	uint8_t id;
	uint8_t mem_id;
	boow vawid;
	atomic_t	wef_cnt;
	stwuct dwm_device *ddev;
	stwuct dwm_device *wdev;
	stwuct dwm_device *pdev;
	stwuct dwm_dwivew *dwivew;
	stwuct dwm_vma_offset_managew *vma_offset_managew;
	stwuct amdgpu_sched	gpu_sched[AMDGPU_HW_IP_NUM][AMDGPU_WING_PWIO_MAX];
};

stwuct amdgpu_xcp_mgw {
	stwuct amdgpu_device *adev;
	stwuct mutex xcp_wock;
	stwuct amdgpu_xcp_mgw_funcs *funcs;

	stwuct amdgpu_xcp xcp[MAX_XCP];
	uint8_t num_xcps;
	int8_t mode;

	 /* Used to detewmine KFD memowy size wimits pew XCP */
	unsigned int num_xcp_pew_mem_pawtition;
};

stwuct amdgpu_xcp_mgw_funcs {
	int (*switch_pawtition_mode)(stwuct amdgpu_xcp_mgw *xcp_mgw, int mode,
				     int *num_xcps);
	int (*quewy_pawtition_mode)(stwuct amdgpu_xcp_mgw *xcp_mgw);
	int (*get_ip_detaiws)(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id,
			      enum AMDGPU_XCP_IP_BWOCK ip_id,
			      stwuct amdgpu_xcp_ip *ip);
	int (*get_xcp_mem_id)(stwuct amdgpu_xcp_mgw *xcp_mgw,
			      stwuct amdgpu_xcp *xcp, uint8_t *mem_id);

	int (*pwepawe_suspend)(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
	int (*suspend)(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
	int (*pwepawe_wesume)(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
	int (*wesume)(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
	int (*sewect_scheds)(stwuct amdgpu_device *adev,
				  u32 hw_ip, u32 hw_pwio, stwuct amdgpu_fpwiv *fpwiv,
				  unsigned int *num_scheds, stwuct dwm_gpu_scheduwew ***scheds);
	int (*update_pawtition_sched_wist)(stwuct amdgpu_device *adev);
};

int amdgpu_xcp_pwepawe_suspend(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
int amdgpu_xcp_suspend(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
int amdgpu_xcp_pwepawe_wesume(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);
int amdgpu_xcp_wesume(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id);

int amdgpu_xcp_mgw_init(stwuct amdgpu_device *adev, int init_mode,
			int init_xcps, stwuct amdgpu_xcp_mgw_funcs *xcp_funcs);
int amdgpu_xcp_init(stwuct amdgpu_xcp_mgw *xcp_mgw, int num_xcps, int mode);
int amdgpu_xcp_quewy_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw, u32 fwags);
int amdgpu_xcp_switch_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw, int mode);
int amdgpu_xcp_westowe_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw);
int amdgpu_xcp_get_pawtition(stwuct amdgpu_xcp_mgw *xcp_mgw,
			     enum AMDGPU_XCP_IP_BWOCK ip, int instance);

int amdgpu_xcp_get_inst_detaiws(stwuct amdgpu_xcp *xcp,
				enum AMDGPU_XCP_IP_BWOCK ip,
				uint32_t *inst_mask);

int amdgpu_xcp_dev_wegistew(stwuct amdgpu_device *adev,
				const stwuct pci_device_id *ent);
void amdgpu_xcp_dev_unpwug(stwuct amdgpu_device *adev);
int amdgpu_xcp_open_device(stwuct amdgpu_device *adev,
			   stwuct amdgpu_fpwiv *fpwiv,
			   stwuct dwm_fiwe *fiwe_pwiv);
void amdgpu_xcp_wewease_sched(stwuct amdgpu_device *adev,
			      stwuct amdgpu_ctx_entity *entity);

#define amdgpu_xcp_sewect_scheds(adev, e, c, d, x, y) \
	((adev)->xcp_mgw && (adev)->xcp_mgw->funcs && \
	(adev)->xcp_mgw->funcs->sewect_scheds ? \
	(adev)->xcp_mgw->funcs->sewect_scheds((adev), (e), (c), (d), (x), (y)) : -ENOENT)
#define amdgpu_xcp_update_pawtition_sched_wist(adev) \
	((adev)->xcp_mgw && (adev)->xcp_mgw->funcs && \
	(adev)->xcp_mgw->funcs->update_pawtition_sched_wist ? \
	(adev)->xcp_mgw->funcs->update_pawtition_sched_wist(adev) : 0)

static inwine int amdgpu_xcp_get_num_xcp(stwuct amdgpu_xcp_mgw *xcp_mgw)
{
	if (!xcp_mgw)
		wetuwn 1;
	ewse
		wetuwn xcp_mgw->num_xcps;
}

static inwine stwuct amdgpu_xcp *
amdgpu_get_next_xcp(stwuct amdgpu_xcp_mgw *xcp_mgw, int *fwom)
{
	if (!xcp_mgw)
		wetuwn NUWW;

	whiwe (*fwom < MAX_XCP) {
		if (xcp_mgw->xcp[*fwom].vawid)
			wetuwn &xcp_mgw->xcp[*fwom];
		++(*fwom);
	}

	wetuwn NUWW;
}

#define fow_each_xcp(xcp_mgw, xcp, i)                            \
	fow (i = 0, xcp = amdgpu_get_next_xcp(xcp_mgw, &i); xcp; \
	     xcp = amdgpu_get_next_xcp(xcp_mgw, &i))

#endif
