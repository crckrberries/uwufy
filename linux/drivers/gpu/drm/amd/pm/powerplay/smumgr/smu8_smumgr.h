/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#ifndef _SMU8_SMUMGW_H_
#define _SMU8_SMUMGW_H_


#define MAX_NUM_FIWMWAWE                        8
#define MAX_NUM_SCWATCH                         11
#define SMU8_SCWATCH_SIZE_NONGFX_CWOCKGATING      1024
#define SMU8_SCWATCH_SIZE_NONGFX_GOWDENSETTING    2048
#define SMU8_SCWATCH_SIZE_SDMA_METADATA           1024
#define SMU8_SCWATCH_SIZE_IH                      ((2*256+1)*4)

#define SMU_EnabwedFeatuweScoweboawd_ScwkDpmOn    0x00200000

enum smu8_scwatch_entwy {
	SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA0 = 0,
	SMU8_SCWATCH_ENTWY_UCODE_ID_SDMA1,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_CE,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_PFP,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_ME,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT1,
	SMU8_SCWATCH_ENTWY_UCODE_ID_CP_MEC_JT2,
	SMU8_SCWATCH_ENTWY_UCODE_ID_GMCON_WENG,
	SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_G,
	SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SCWATCH,
	SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_AWAM,
	SMU8_SCWATCH_ENTWY_UCODE_ID_WWC_SWM_DWAM,
	SMU8_SCWATCH_ENTWY_UCODE_ID_DMCU_EWAM,
	SMU8_SCWATCH_ENTWY_UCODE_ID_DMCU_IWAM,
	SMU8_SCWATCH_ENTWY_UCODE_ID_POWEW_PWOFIWING,
	SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_HAWT,
	SMU8_SCWATCH_ENTWY_DATA_ID_SYS_CWOCKGATING,
	SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_WING_WEGS,
	SMU8_SCWATCH_ENTWY_DATA_ID_NONGFX_WEINIT,
	SMU8_SCWATCH_ENTWY_DATA_ID_SDMA_STAWT,
	SMU8_SCWATCH_ENTWY_DATA_ID_IH_WEGISTEWS,
	SMU8_SCWATCH_ENTWY_SMU8_FUSION_CWKTABWE
};

stwuct smu8_buffew_entwy {
	uint32_t data_size;
	uint64_t mc_addw;
	void *kaddw;
	enum smu8_scwatch_entwy fiwmwawe_ID;
	stwuct amdgpu_bo *handwe; /* as bo handwe used when wewease bo */
};

stwuct smu8_wegistew_index_data_paiw {
	uint32_t offset;
	uint32_t vawue;
};

stwuct smu8_ih_meta_data {
	uint32_t command;
	stwuct smu8_wegistew_index_data_paiw wegistew_index_vawue_paiw[1];
};

stwuct smu8_smumgw {
	uint8_t dwivew_buffew_wength;
	uint8_t scwatch_buffew_wength;
	uint16_t toc_entwy_used_count;
	uint16_t toc_entwy_initiawize_index;
	uint16_t toc_entwy_powew_pwofiwing_index;
	uint16_t toc_entwy_awam;
	uint16_t toc_entwy_ih_wegistew_westowe_task_index;
	uint16_t toc_entwy_cwock_tabwe;
	uint16_t ih_wegistew_westowe_task_size;
	uint16_t smu_buffew_used_bytes;

	stwuct smu8_buffew_entwy toc_buffew;
	stwuct smu8_buffew_entwy smu_buffew;
	stwuct smu8_buffew_entwy fiwmwawe_buffew;
	stwuct smu8_buffew_entwy dwivew_buffew[MAX_NUM_FIWMWAWE];
	stwuct smu8_buffew_entwy meta_data_buffew[MAX_NUM_FIWMWAWE];
	stwuct smu8_buffew_entwy scwatch_buffew[MAX_NUM_SCWATCH];
};

#endif
