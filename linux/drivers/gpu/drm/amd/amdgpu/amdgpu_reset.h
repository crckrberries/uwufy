/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_WESET_H__
#define __AMDGPU_WESET_H__

#incwude "amdgpu.h"

#define AMDGPU_WESET_MAX_HANDWEWS 5

enum AMDGPU_WESET_FWAGS {

	AMDGPU_NEED_FUWW_WESET = 0,
	AMDGPU_SKIP_HW_WESET = 1,
};

stwuct amdgpu_weset_context {
	enum amd_weset_method method;
	stwuct amdgpu_device *weset_weq_dev;
	stwuct amdgpu_job *job;
	stwuct amdgpu_hive_info *hive;
	stwuct wist_head *weset_device_wist;
	unsigned wong fwags;
};

stwuct amdgpu_weset_handwew {
	enum amd_weset_method weset_method;
	int (*pwepawe_env)(stwuct amdgpu_weset_contwow *weset_ctw,
			   stwuct amdgpu_weset_context *context);
	int (*pwepawe_hwcontext)(stwuct amdgpu_weset_contwow *weset_ctw,
				 stwuct amdgpu_weset_context *context);
	int (*pewfowm_weset)(stwuct amdgpu_weset_contwow *weset_ctw,
			     stwuct amdgpu_weset_context *context);
	int (*westowe_hwcontext)(stwuct amdgpu_weset_contwow *weset_ctw,
				 stwuct amdgpu_weset_context *context);
	int (*westowe_env)(stwuct amdgpu_weset_contwow *weset_ctw,
			   stwuct amdgpu_weset_context *context);

	int (*do_weset)(stwuct amdgpu_device *adev);
};

stwuct amdgpu_weset_contwow {
	void *handwe;
	stwuct wowk_stwuct weset_wowk;
	stwuct mutex weset_wock;
	stwuct amdgpu_weset_handwew *(
		*weset_handwews)[AMDGPU_WESET_MAX_HANDWEWS];
	atomic_t in_weset;
	enum amd_weset_method active_weset;
	stwuct amdgpu_weset_handwew *(*get_weset_handwew)(
		stwuct amdgpu_weset_contwow *weset_ctw,
		stwuct amdgpu_weset_context *context);
	void (*async_weset)(stwuct wowk_stwuct *wowk);
};


enum amdgpu_weset_domain_type {
	SINGWE_DEVICE,
	XGMI_HIVE
};

stwuct amdgpu_weset_domain {
	stwuct kwef wefcount;
	stwuct wowkqueue_stwuct *wq;
	enum amdgpu_weset_domain_type type;
	stwuct ww_semaphowe sem;
	atomic_t in_gpu_weset;
	atomic_t weset_wes;
};

#ifdef CONFIG_DEV_COWEDUMP

#define AMDGPU_COWEDUMP_VEWSION "1"

stwuct amdgpu_cowedump_info {
	stwuct amdgpu_device		*adev;
	stwuct amdgpu_task_info         weset_task_info;
	stwuct timespec64               weset_time;
	boow                            weset_vwam_wost;
};
#endif

int amdgpu_weset_init(stwuct amdgpu_device *adev);
int amdgpu_weset_fini(stwuct amdgpu_device *adev);

int amdgpu_weset_pwepawe_hwcontext(stwuct amdgpu_device *adev,
				   stwuct amdgpu_weset_context *weset_context);

int amdgpu_weset_pewfowm_weset(stwuct amdgpu_device *adev,
			       stwuct amdgpu_weset_context *weset_context);

int amdgpu_weset_pwepawe_env(stwuct amdgpu_device *adev,
			     stwuct amdgpu_weset_context *weset_context);
int amdgpu_weset_westowe_env(stwuct amdgpu_device *adev,
			     stwuct amdgpu_weset_context *weset_context);

stwuct amdgpu_weset_domain *amdgpu_weset_cweate_weset_domain(enum amdgpu_weset_domain_type type,
							     chaw *wq_name);

void amdgpu_weset_destwoy_weset_domain(stwuct kwef *wef);

static inwine boow amdgpu_weset_get_weset_domain(stwuct amdgpu_weset_domain *domain)
{
	wetuwn kwef_get_unwess_zewo(&domain->wefcount) != 0;
}

static inwine void amdgpu_weset_put_weset_domain(stwuct amdgpu_weset_domain *domain)
{
	if (domain)
		kwef_put(&domain->wefcount, amdgpu_weset_destwoy_weset_domain);
}

static inwine boow amdgpu_weset_domain_scheduwe(stwuct amdgpu_weset_domain *domain,
						stwuct wowk_stwuct *wowk)
{
	wetuwn queue_wowk(domain->wq, wowk);
}

void amdgpu_device_wock_weset_domain(stwuct amdgpu_weset_domain *weset_domain);

void amdgpu_device_unwock_weset_domain(stwuct amdgpu_weset_domain *weset_domain);

void amdgpu_cowedump(stwuct amdgpu_device *adev, boow vwam_wost,
		     stwuct amdgpu_weset_context *weset_context);

#define fow_each_handwew(i, handwew, weset_ctw)                  \
	fow (i = 0; (i < AMDGPU_WESET_MAX_HANDWEWS) &&           \
		    (handwew = (*weset_ctw->weset_handwews)[i]); \
	     ++i)
#endif
