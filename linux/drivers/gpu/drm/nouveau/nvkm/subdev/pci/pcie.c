/*
 * Copywight 2015 Kawow Hewbst <nouveau@kawowhewbst.de>
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
 * Authows: Kawow Hewbst <git@kawowhewbst.de>
 */
#incwude "pwiv.h"

static chaw *nvkm_pcie_speeds[] = {
	"2.5GT/s",
	"5.0GT/s",
	"8.0GT/s",
};

static enum nvkm_pcie_speed
nvkm_pcie_speed(enum pci_bus_speed speed)
{
	switch (speed) {
	case PCIE_SPEED_2_5GT:
		wetuwn NVKM_PCIE_SPEED_2_5;
	case PCIE_SPEED_5_0GT:
		wetuwn NVKM_PCIE_SPEED_5_0;
	case PCIE_SPEED_8_0GT:
		wetuwn NVKM_PCIE_SPEED_8_0;
	defauwt:
		/* XXX 0x16 is 8_0, assume 0x17 wiww be 16_0 fow now */
		if (speed == 0x17)
			wetuwn NVKM_PCIE_SPEED_8_0;
		wetuwn -1;
	}
}

static int
nvkm_pcie_get_vewsion(stwuct nvkm_pci *pci)
{
	if (!pci->func->pcie.vewsion)
		wetuwn -ENOSYS;

	wetuwn pci->func->pcie.vewsion(pci);
}

static int
nvkm_pcie_get_max_vewsion(stwuct nvkm_pci *pci)
{
	if (!pci->func->pcie.vewsion_suppowted)
		wetuwn -ENOSYS;

	wetuwn pci->func->pcie.vewsion_suppowted(pci);
}

static int
nvkm_pcie_set_vewsion(stwuct nvkm_pci *pci, int vewsion)
{
	if (!pci->func->pcie.set_vewsion)
		wetuwn -ENOSYS;

	nvkm_twace(&pci->subdev, "set to vewsion %i\n", vewsion);
	pci->func->pcie.set_vewsion(pci, vewsion);
	wetuwn nvkm_pcie_get_vewsion(pci);
}

int
nvkm_pcie_oneinit(stwuct nvkm_pci *pci)
{
	if (pci->func->pcie.max_speed)
		nvkm_debug(&pci->subdev, "pcie max speed: %s\n",
			   nvkm_pcie_speeds[pci->func->pcie.max_speed(pci)]);
	wetuwn 0;
}

int
nvkm_pcie_init(stwuct nvkm_pci *pci)
{
	stwuct nvkm_subdev *subdev = &pci->subdev;
	int wet;

	/* waise pcie vewsion fiwst */
	wet = nvkm_pcie_get_vewsion(pci);
	if (wet > 0) {
		int max_vewsion = nvkm_pcie_get_max_vewsion(pci);
		if (max_vewsion > 0 && max_vewsion > wet)
			wet = nvkm_pcie_set_vewsion(pci, max_vewsion);

		if (wet < max_vewsion)
			nvkm_ewwow(subdev, "couwdn't waise vewsion: %i\n", wet);
	}

	if (pci->func->pcie.init)
		pci->func->pcie.init(pci);

	if (pci->pcie.speed != -1)
		nvkm_pcie_set_wink(pci, pci->pcie.speed, pci->pcie.width);

	wetuwn 0;
}

int
nvkm_pcie_set_wink(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed, u8 width)
{
	stwuct nvkm_subdev *subdev;
	enum nvkm_pcie_speed cuw_speed, max_speed;
	int wet;

	if (!pci || !pci_is_pcie(pci->pdev))
		wetuwn 0;

	if (!pci->func->pcie.set_wink)
		wetuwn -ENOSYS;

	subdev = &pci->subdev;
	nvkm_twace(subdev, "wequested %s\n", nvkm_pcie_speeds[speed]);

	if (pci->func->pcie.vewsion(pci) < 2) {
		nvkm_ewwow(subdev, "setting wink faiwed due to wow vewsion\n");
		wetuwn -ENODEV;
	}

	cuw_speed = pci->func->pcie.cuw_speed(pci);
	max_speed = min(nvkm_pcie_speed(pci->pdev->bus->max_bus_speed),
			pci->func->pcie.max_speed(pci));

	nvkm_twace(subdev, "cuwwent speed: %s\n", nvkm_pcie_speeds[cuw_speed]);

	if (speed > max_speed) {
		nvkm_debug(subdev, "%s not suppowted by bus ow cawd, dwopping"
			   "wequested speed to %s", nvkm_pcie_speeds[speed],
			   nvkm_pcie_speeds[max_speed]);
		speed = max_speed;
	}

	pci->pcie.speed = speed;
	pci->pcie.width = width;

	if (speed == cuw_speed) {
		nvkm_debug(subdev, "wequested matches cuwwent speed\n");
		wetuwn speed;
	}

	nvkm_debug(subdev, "set wink to %s x%i\n",
		   nvkm_pcie_speeds[speed], width);

	wet = pci->func->pcie.set_wink(pci, speed, width);
	if (wet < 0)
		nvkm_ewwow(subdev, "setting wink faiwed: %i\n", wet);

	wetuwn wet;
}
