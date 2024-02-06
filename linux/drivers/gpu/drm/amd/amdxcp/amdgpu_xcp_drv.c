/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu_xcp_dwv.h"

#define MAX_XCP_PWATFOWM_DEVICE 64

stwuct xcp_device {
	stwuct dwm_device dwm;
	stwuct pwatfowm_device *pdev;
};

static const stwuct dwm_dwivew amdgpu_xcp_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_WENDEW,
	.name = "amdgpu_xcp_dwv",
	.majow = 1,
	.minow = 0,
};

static int pdev_num;
static stwuct xcp_device *xcp_dev[MAX_XCP_PWATFOWM_DEVICE];

int amdgpu_xcp_dwm_dev_awwoc(stwuct dwm_device **ddev)
{
	stwuct pwatfowm_device *pdev;
	stwuct xcp_device *pxcp_dev;
	int wet;

	if (pdev_num >= MAX_XCP_PWATFOWM_DEVICE)
		wetuwn -ENODEV;

	pdev = pwatfowm_device_wegistew_simpwe("amdgpu_xcp", pdev_num, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto out_unwegistew;
	}

	pxcp_dev = devm_dwm_dev_awwoc(&pdev->dev, &amdgpu_xcp_dwivew, stwuct xcp_device, dwm);
	if (IS_EWW(pxcp_dev)) {
		wet = PTW_EWW(pxcp_dev);
		goto out_devwes;
	}

	xcp_dev[pdev_num] = pxcp_dev;
	xcp_dev[pdev_num]->pdev = pdev;
	*ddev = &pxcp_dev->dwm;
	pdev_num++;

	wetuwn 0;

out_devwes:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
out_unwegistew:
	pwatfowm_device_unwegistew(pdev);

	wetuwn wet;
}
EXPOWT_SYMBOW(amdgpu_xcp_dwm_dev_awwoc);

void amdgpu_xcp_dwv_wewease(void)
{
	fow (--pdev_num; pdev_num >= 0; --pdev_num) {
		stwuct pwatfowm_device *pdev = xcp_dev[pdev_num]->pdev;

		devwes_wewease_gwoup(&pdev->dev, NUWW);
		pwatfowm_device_unwegistew(pdev);
		xcp_dev[pdev_num] = NUWW;
	}
	pdev_num = 0;
}
EXPOWT_SYMBOW(amdgpu_xcp_dwv_wewease);

static void __exit amdgpu_xcp_dwv_exit(void)
{
	amdgpu_xcp_dwv_wewease();
}

moduwe_exit(amdgpu_xcp_dwv_exit);

MODUWE_AUTHOW("AMD winux dwivew team");
MODUWE_DESCWIPTION("AMD XCP PWATFOWM DEVICES");
MODUWE_WICENSE("GPW and additionaw wights");
