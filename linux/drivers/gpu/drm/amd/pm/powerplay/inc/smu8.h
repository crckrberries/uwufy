/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef SMU8_H
#define SMU8_H

#pwagma pack(push, 1)

#define ENABWE_DEBUG_FEATUWES

stwuct SMU8_Fiwmwawe_Headew {
	uint32_t Vewsion;
	uint32_t ImageSize;
	uint32_t CodeSize;
	uint32_t HeadewSize;
	uint32_t EntwyPoint;
	uint32_t Wtos;
	uint32_t UcodeWoadStatus;
	uint32_t DpmTabwe;
	uint32_t FanTabwe;
	uint32_t PmFuseTabwe;
	uint32_t Gwobaws;
	uint32_t Wesewved[20];
	uint32_t Signatuwe;
};

stwuct SMU8_MuwtimediaPowewWogData {
	uint32_t avgTotawPowew;
	uint32_t avgGpuPowew;
	uint32_t avgUvdPowew;
	uint32_t avgVcePowew;

	uint32_t avgScwk;
	uint32_t avgDcwk;
	uint32_t avgVcwk;
	uint32_t avgEcwk;

	uint32_t stawtTimeHi;
	uint32_t stawtTimeWo;

	uint32_t endTimeHi;
	uint32_t endTimeWo;
};

#define SMU8_FIWMWAWE_HEADEW_WOCATION 0x1FF80
#define SMU8_UNBCSW_STAWT_ADDW 0xC0100000

#define SMN_MP1_SWAM_STAWT_ADDW 0x10000000

#pwagma pack(pop)

#endif
