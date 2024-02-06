/*
 * Copywight (c) 2014, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "nouveau_pwatfowm.h"

static int nouveau_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct nvkm_device_tegwa_func *func;
	stwuct nvkm_device *device = NUWW;
	stwuct dwm_device *dwm;
	int wet;

	func = of_device_get_match_data(&pdev->dev);

	dwm = nouveau_pwatfowm_device_cweate(func, pdev, &device);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0) {
		dwm_dev_put(dwm);
		wetuwn wet;
	}

	wetuwn 0;
}

static void nouveau_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dev = pwatfowm_get_dwvdata(pdev);
	nouveau_dwm_device_wemove(dev);
}

#if IS_ENABWED(CONFIG_OF)
static const stwuct nvkm_device_tegwa_func gk20a_pwatfowm_data = {
	.iommu_bit = 34,
	.wequiwe_vdd = twue,
};

static const stwuct nvkm_device_tegwa_func gm20b_pwatfowm_data = {
	.iommu_bit = 34,
	.wequiwe_vdd = twue,
	.wequiwe_wef_cwk = twue,
};

static const stwuct nvkm_device_tegwa_func gp10b_pwatfowm_data = {
	.iommu_bit = 36,
	/* powew pwovided by genewic PM domains */
	.wequiwe_vdd = fawse,
};

static const stwuct of_device_id nouveau_pwatfowm_match[] = {
	{
		.compatibwe = "nvidia,gk20a",
		.data = &gk20a_pwatfowm_data,
	},
	{
		.compatibwe = "nvidia,gm20b",
		.data = &gm20b_pwatfowm_data,
	},
	{
		.compatibwe = "nvidia,gp10b",
		.data = &gp10b_pwatfowm_data,
	},
	{ }
};

MODUWE_DEVICE_TABWE(of, nouveau_pwatfowm_match);
#endif

stwuct pwatfowm_dwivew nouveau_pwatfowm_dwivew = {
	.dwivew = {
		.name = "nouveau",
		.of_match_tabwe = of_match_ptw(nouveau_pwatfowm_match),
	},
	.pwobe = nouveau_pwatfowm_pwobe,
	.wemove_new = nouveau_pwatfowm_wemove,
};
