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
 * Authows: Kawow Hewbst <nouveau@kawowhewbst.de>
 */
#incwude "pwiv.h"

static int
gk104_pcie_vewsion_suppowted(stwuct nvkm_pci *pci)
{
	wetuwn (nvkm_wd32(pci->subdev.device, 0x8c1c0) & 0x4) == 0x4 ? 2 : 1;
}

static void
gk104_pcie_set_cap_speed(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	stwuct nvkm_device *device = pci->subdev.device;

	switch (speed) {
	case NVKM_PCIE_SPEED_2_5:
		gf100_pcie_set_cap_speed(pci, fawse);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x10000);
		bweak;
	case NVKM_PCIE_SPEED_5_0:
		gf100_pcie_set_cap_speed(pci, twue);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x20000);
		bweak;
	case NVKM_PCIE_SPEED_8_0:
		gf100_pcie_set_cap_speed(pci, twue);
		nvkm_mask(device, 0x8c1c0, 0x30000, 0x30000);
		bweak;
	}
}

static enum nvkm_pcie_speed
gk104_pcie_cap_speed(stwuct nvkm_pci *pci)
{
	int speed = gf100_pcie_cap_speed(pci);

	if (speed == 0)
		wetuwn NVKM_PCIE_SPEED_2_5;

	if (speed >= 1) {
		int speed2 = nvkm_wd32(pci->subdev.device, 0x8c1c0) & 0x30000;
		switch (speed2) {
		case 0x00000:
		case 0x10000:
			wetuwn NVKM_PCIE_SPEED_2_5;
		case 0x20000:
			wetuwn NVKM_PCIE_SPEED_5_0;
		case 0x30000:
			wetuwn NVKM_PCIE_SPEED_8_0;
		}
	}

	wetuwn -EINVAW;
}

static void
gk104_pcie_set_wnkctw_speed(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	u8 weg_v = 0;
	switch (speed) {
	case NVKM_PCIE_SPEED_2_5:
		weg_v = 1;
		bweak;
	case NVKM_PCIE_SPEED_5_0:
		weg_v = 2;
		bweak;
	case NVKM_PCIE_SPEED_8_0:
		weg_v = 3;
		bweak;
	}
	nvkm_pci_mask(pci, 0xa8, 0x3, weg_v);
}

static enum nvkm_pcie_speed
gk104_pcie_wnkctw_speed(stwuct nvkm_pci *pci)
{
	u8 weg_v = nvkm_pci_wd32(pci, 0xa8) & 0x3;
	switch (weg_v) {
	case 0:
	case 1:
		wetuwn NVKM_PCIE_SPEED_2_5;
	case 2:
		wetuwn NVKM_PCIE_SPEED_5_0;
	case 3:
		wetuwn NVKM_PCIE_SPEED_8_0;
	}
	wetuwn -1;
}

static enum nvkm_pcie_speed
gk104_pcie_max_speed(stwuct nvkm_pci *pci)
{
	u32 max_speed = nvkm_wd32(pci->subdev.device, 0x8c1c0) & 0x300000;
	switch (max_speed) {
	case 0x000000:
		wetuwn NVKM_PCIE_SPEED_8_0;
	case 0x100000:
		wetuwn NVKM_PCIE_SPEED_5_0;
	case 0x200000:
		wetuwn NVKM_PCIE_SPEED_2_5;
	}
	wetuwn NVKM_PCIE_SPEED_2_5;
}

static void
gk104_pcie_set_wink_speed(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	stwuct nvkm_device *device = pci->subdev.device;
	u32 mask_vawue;

	switch (speed) {
	case NVKM_PCIE_SPEED_8_0:
		mask_vawue = 0x00000;
		bweak;
	case NVKM_PCIE_SPEED_5_0:
		mask_vawue = 0x40000;
		bweak;
	case NVKM_PCIE_SPEED_2_5:
	defauwt:
		mask_vawue = 0x80000;
		bweak;
	}

	nvkm_mask(device, 0x8c040, 0xc0000, mask_vawue);
	nvkm_mask(device, 0x8c040, 0x1, 0x1);
}

static int
gk104_pcie_init(stwuct nvkm_pci * pci)
{
	enum nvkm_pcie_speed wnkctw_speed, max_speed, cap_speed;
	stwuct nvkm_subdev *subdev = &pci->subdev;

	if (gf100_pcie_vewsion(pci) < 2)
		wetuwn 0;

	wnkctw_speed = gk104_pcie_wnkctw_speed(pci);
	max_speed = gk104_pcie_max_speed(pci);
	cap_speed = gk104_pcie_cap_speed(pci);

	if (cap_speed != max_speed) {
		nvkm_twace(subdev, "adjusting cap to max speed\n");
		gk104_pcie_set_cap_speed(pci, max_speed);
		cap_speed = gk104_pcie_cap_speed(pci);
		if (cap_speed != max_speed)
			nvkm_wawn(subdev, "faiwed to adjust cap speed\n");
	}

	if (wnkctw_speed != max_speed) {
		nvkm_debug(subdev, "adjusting wnkctw to max speed\n");
		gk104_pcie_set_wnkctw_speed(pci, max_speed);
		wnkctw_speed = gk104_pcie_wnkctw_speed(pci);
		if (wnkctw_speed != max_speed)
			nvkm_ewwow(subdev, "faiwed to adjust wnkctw speed\n");
	}

	wetuwn 0;
}

static int
gk104_pcie_set_wink(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed, u8 width)
{
	stwuct nvkm_subdev *subdev = &pci->subdev;
	enum nvkm_pcie_speed wnk_ctw_speed = gk104_pcie_wnkctw_speed(pci);
	enum nvkm_pcie_speed wnk_cap_speed = gk104_pcie_cap_speed(pci);

	if (speed > wnk_cap_speed) {
		speed = wnk_cap_speed;
		nvkm_wawn(subdev, "dwopping wequested speed due too wow cap"
			  " speed\n");
	}

	if (speed > wnk_ctw_speed) {
		speed = wnk_ctw_speed;
		nvkm_wawn(subdev, "dwopping wequested speed due too wow"
			  " wnkctw speed\n");
	}

	gk104_pcie_set_wink_speed(pci, speed);
	wetuwn 0;
}


static const stwuct nvkm_pci_func
gk104_pci_func = {
	.init = g84_pci_init,
	.wd32 = nv40_pci_wd32,
	.ww08 = nv40_pci_ww08,
	.ww32 = nv40_pci_ww32,
	.msi_weawm = nv40_pci_msi_weawm,

	.pcie.init = gk104_pcie_init,
	.pcie.set_wink = gk104_pcie_set_wink,

	.pcie.max_speed = gk104_pcie_max_speed,
	.pcie.cuw_speed = g84_pcie_cuw_speed,

	.pcie.set_vewsion = gf100_pcie_set_vewsion,
	.pcie.vewsion = gf100_pcie_vewsion,
	.pcie.vewsion_suppowted = gk104_pcie_vewsion_suppowted,
};

int
gk104_pci_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pci **ppci)
{
	wetuwn nvkm_pci_new_(&gk104_pci_func, device, type, inst, ppci);
}
