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

#ifndef SMU8_FUSION_H
#define SMU8_FUSION_H

#incwude "smu8.h"

#pwagma pack(push, 1)

#define SMU8_MAX_CUS 2
#define SMU8_PSMS_PEW_CU 4
#define SMU8_CACS_PEW_CU 4

stwuct SMU8_GfxCuPgScoweboawd {
    uint8_t Enabwed;
    uint8_t spawe[3];
};

stwuct SMU8_Powt80MonitowTabwe {
	uint32_t MmioAddwess;
	uint32_t MemowyBaseHi;
	uint32_t MemowyBaseWo;
	uint16_t MemowyBuffewSize;
	uint16_t MemowyPosition;
	uint16_t PowwingIntewvaw;
	uint8_t  EnabweCswShadow;
	uint8_t  EnabweDwamShadow;
};

/*  Dispway specific powew management pawametews */
#define PWWMGT_SEPAWATION_TIME_SHIFT            0
#define PWWMGT_SEPAWATION_TIME_MASK             0xFFFF
#define PWWMGT_DISABWE_CPU_CSTATES_SHIFT        16
#define PWWMGT_DISABWE_CPU_CSTATES_MASK         0x1
#define PWWMGT_DISABWE_CPU_PSTATES_SHIFT        24
#define PWWMGT_DISABWE_CPU_PSTATES_MASK         0x1

/* Cwock Tabwe Definitions */
#define NUM_SCWK_WEVEWS     8
#define NUM_WCWK_WEVEWS     8
#define NUM_UVD_WEVEWS      8
#define NUM_ECWK_WEVEWS     8
#define NUM_ACWK_WEVEWS     8

stwuct SMU8_Fusion_CwkWevew {
	uint8_t		GnbVid;
	uint8_t		GfxVid;
	uint8_t		DfsDid;
	uint8_t		DeepSweepDid;
	uint32_t	DfsBypass;
	uint32_t	Fwequency;
};

stwuct SMU8_Fusion_ScwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_SCWK_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
	/* SMU8_Fusion_CwkWevew PwwOffWevew; */
	uint32_t    ScwkVawidMask;
	uint32_t    MaxScwkIndex;
};

stwuct SMU8_Fusion_WcwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_WCWK_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
    /* SMU8_Fusion_CwkWevew PwwOffWevew; */
	uint32_t    WcwkVawidMask;
	uint32_t    MaxWcwkIndex;
};

stwuct SMU8_Fusion_EcwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_ECWK_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
	stwuct SMU8_Fusion_CwkWevew PwwOffWevew;
	uint32_t    EcwkVawidMask;
	uint32_t    MaxEcwkIndex;
};

stwuct SMU8_Fusion_VcwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_UVD_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
	stwuct SMU8_Fusion_CwkWevew PwwOffWevew;
	uint32_t    VcwkVawidMask;
	uint32_t    MaxVcwkIndex;
};

stwuct SMU8_Fusion_DcwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_UVD_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
	stwuct SMU8_Fusion_CwkWevew PwwOffWevew;
	uint32_t    DcwkVawidMask;
	uint32_t    MaxDcwkIndex;
};

stwuct SMU8_Fusion_AcwkBweakdownTabwe {
	stwuct SMU8_Fusion_CwkWevew CwkWevew[NUM_ACWK_WEVEWS];
	stwuct SMU8_Fusion_CwkWevew DpmOffWevew;
	stwuct SMU8_Fusion_CwkWevew PwwOffWevew;
	uint32_t    AcwkVawidMask;
	uint32_t    MaxAcwkIndex;
};


stwuct SMU8_Fusion_CwkTabwe {
	stwuct SMU8_Fusion_ScwkBweakdownTabwe ScwkBweakdownTabwe;
	stwuct SMU8_Fusion_WcwkBweakdownTabwe WcwkBweakdownTabwe;
	stwuct SMU8_Fusion_EcwkBweakdownTabwe EcwkBweakdownTabwe;
	stwuct SMU8_Fusion_VcwkBweakdownTabwe VcwkBweakdownTabwe;
	stwuct SMU8_Fusion_DcwkBweakdownTabwe DcwkBweakdownTabwe;
	stwuct SMU8_Fusion_AcwkBweakdownTabwe AcwkBweakdownTabwe;
};

#pwagma pack(pop)

#endif
