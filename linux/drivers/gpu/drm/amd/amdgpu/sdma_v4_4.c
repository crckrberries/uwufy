/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu.h"
#incwude "sdma/sdma_4_4_0_offset.h"
#incwude "sdma/sdma_4_4_0_sh_mask.h"
#incwude "soc15.h"
#incwude "amdgpu_was.h"

#define SDMA1_WEG_OFFSET 0x600
#define SDMA2_WEG_OFFSET 0x1cda0
#define SDMA3_WEG_OFFSET 0x1d1a0
#define SDMA4_WEG_OFFSET 0x1d5a0

/* hewpew function that awwow onwy use sdma0 wegistew offset
 * to cawcuwate wegistew offset fow aww the sdma instances */
static uint32_t sdma_v4_4_get_weg_offset(stwuct amdgpu_device *adev,
					 uint32_t instance,
					 uint32_t offset)
{
	uint32_t sdma_base = adev->weg_offset[SDMA0_HWIP][0][0];

	switch (instance) {
	case 0:
		wetuwn (sdma_base + offset);
	case 1:
		wetuwn (sdma_base + SDMA1_WEG_OFFSET + offset);
	case 2:
		wetuwn (sdma_base + SDMA2_WEG_OFFSET + offset);
	case 3:
		wetuwn (sdma_base + SDMA3_WEG_OFFSET + offset);
	case 4:
		wetuwn (sdma_base + SDMA4_WEG_OFFSET + offset);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct soc15_was_fiewd_entwy sdma_v4_4_was_fiewds[] = {
	{ "SDMA_MBANK_DATA_BUF0_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF0_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF1_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF1_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF2_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF2_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF3_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF3_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF4_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF4_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF5_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF5_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF6_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF6_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF7_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF7_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF8_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF8_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF9_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF9_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF10_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF10_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF11_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF11_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF12_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF12_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF13_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF13_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF14_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF14_SED),
	0, 0,
	},
	{ "SDMA_MBANK_DATA_BUF15_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW, SDMA_MBANK_DATA_BUF15_SED),
	0, 0,
	},
	{ "SDMA_UCODE_BUF_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_UCODE_BUF_SED),
	0, 0,
	},
	{ "SDMA_WB_CMD_BUF_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_WB_CMD_BUF_SED),
	0, 0,
	},
	{ "SDMA_IB_CMD_BUF_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_IB_CMD_BUF_SED),
	0, 0,
	},
	{ "SDMA_UTCW1_WD_FIFO_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_UTCW1_WD_FIFO_SED),
	0, 0,
	},
	{ "SDMA_UTCW1_WDBST_FIFO_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_UTCW1_WDBST_FIFO_SED),
	0, 0,
	},
	{ "SDMA_UTCW1_WW_FIFO_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_UTCW1_WW_FIFO_SED),
	0, 0,
	},
	{ "SDMA_DATA_WUT_FIFO_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_DATA_WUT_FIFO_SED),
	0, 0,
	},
	{ "SDMA_SPWIT_DATA_BUF_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_SPWIT_DATA_BUF_SED),
	0, 0,
	},
	{ "SDMA_MC_WW_ADDW_FIFO_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_MC_WW_ADDW_FIFO_SED),
	0, 0,
	},
	{ "SDMA_MC_WDWET_BUF_SED", SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_EDC_COUNTEW2),
	SOC15_WEG_FIEWD(SDMA0_EDC_COUNTEW2, SDMA_MC_WW_ADDW_FIFO_SED),
	0, 0,
	},
};

static void sdma_v4_4_get_was_ewwow_count(stwuct amdgpu_device *adev,
					  uint32_t weg_offset,
					  uint32_t vawue,
					  uint32_t instance,
					  uint32_t *sec_count)
{
	uint32_t i;
	uint32_t sec_cnt;

	/* doubwe bits ewwow (muwtipwe bits) ewwow detection is not suppowted */
	fow (i = 0; i < AWWAY_SIZE(sdma_v4_4_was_fiewds); i++) {
		if (sdma_v4_4_was_fiewds[i].weg_offset != weg_offset)
			continue;

		/* the SDMA_EDC_COUNTEW wegistew in each sdma instance
		 * shawes the same sed shift_mask
		 * */
		sec_cnt = (vawue &
			sdma_v4_4_was_fiewds[i].sec_count_mask) >>
			sdma_v4_4_was_fiewds[i].sec_count_shift;
		if (sec_cnt) {
			dev_info(adev->dev, "Detected %s in SDMA%d, SED %d\n",
				 sdma_v4_4_was_fiewds[i].name,
				 instance, sec_cnt);
			*sec_count += sec_cnt;
		}
	}
}

static int sdma_v4_4_quewy_was_ewwow_count_by_instance(stwuct amdgpu_device *adev,
					   uint32_t instance,
					   void *was_ewwow_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;
	uint32_t sec_count = 0;
	uint32_t weg_vawue = 0;
	uint32_t weg_offset = 0;

	weg_offset = sdma_v4_4_get_weg_offset(adev, instance, wegSDMA0_EDC_COUNTEW);
	weg_vawue = WWEG32(weg_offset);
	/* doubwe bit ewwow is not suppowted */
	if (weg_vawue)
		sdma_v4_4_get_was_ewwow_count(adev, wegSDMA0_EDC_COUNTEW, weg_vawue,
					      instance, &sec_count);

	weg_offset = sdma_v4_4_get_weg_offset(adev, instance, wegSDMA0_EDC_COUNTEW2);
	weg_vawue = WWEG32(weg_offset);
	/* doubwe bit ewwow is not suppowted */
	if (weg_vawue)
		sdma_v4_4_get_was_ewwow_count(adev, wegSDMA0_EDC_COUNTEW2, weg_vawue,
					      instance, &sec_count);

	/*
	 * eww_data->ue_count shouwd be initiawized to 0
	 * befowe cawwing into this function
	 *
	 * SDMA WAS suppowts singwe bit uncowwectabwe ewwow detection.
	 * So, incwement uncowwectabwe ewwow count.
	 */
	eww_data->ue_count += sec_count;

	/*
	 * SDMA WAS does not suppowt cowwectabwe ewwows.
	 * Set ce count to 0.
	 */
	eww_data->ce_count = 0;

	wetuwn 0;
};

static void sdma_v4_4_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	int i;
	uint32_t weg_offset;

	/* wwite 0 to EDC_COUNTEW weg to cweaw sdma edc countews */
	if (amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__SDMA)) {
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			weg_offset = sdma_v4_4_get_weg_offset(adev, i, wegSDMA0_EDC_COUNTEW);
			WWEG32(weg_offset, 0);
			weg_offset = sdma_v4_4_get_weg_offset(adev, i, wegSDMA0_EDC_COUNTEW2);
			WWEG32(weg_offset, 0);
		}
	}
}

static void sdma_v4_4_quewy_was_ewwow_count(stwuct amdgpu_device *adev,  void *was_ewwow_status)
{
	int i = 0;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (sdma_v4_4_quewy_was_ewwow_count_by_instance(adev, i, was_ewwow_status)) {
			dev_eww(adev->dev, "Quewy was ewwow count faiwed in SDMA%d\n", i);
			wetuwn;
		}
	}

}

const stwuct amdgpu_was_bwock_hw_ops sdma_v4_4_was_hw_ops = {
	.quewy_was_ewwow_count = sdma_v4_4_quewy_was_ewwow_count,
	.weset_was_ewwow_count = sdma_v4_4_weset_was_ewwow_count,
};

stwuct amdgpu_sdma_was sdma_v4_4_was = {
	.was_bwock = {
		.hw_ops = &sdma_v4_4_was_hw_ops,
	},
};
