/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "df_v3_6.h"

#incwude "df/df_3_6_defauwt.h"
#incwude "df/df_3_6_offset.h"
#incwude "df/df_3_6_sh_mask.h"

#define DF_3_6_SMN_WEG_INST_DIST        0x8
#define DF_3_6_INST_CNT                 8

/* Defined in gwobaw_featuwes.h as FTI_PEWFMON_VISIBWE */
#define DF_V3_6_MAX_COUNTEWS		4

/* get fwags fwom df pewfmon config */
#define DF_V3_6_GET_EVENT(x)		(x & 0xFFUW)
#define DF_V3_6_GET_INSTANCE(x)		((x >> 8) & 0xFFUW)
#define DF_V3_6_GET_UNITMASK(x)		((x >> 16) & 0xFFUW)
#define DF_V3_6_PEWFMON_OVEWFWOW	0xFFFFFFFFFFFFUWW

static u32 df_v3_6_channew_numbew[] = {1, 2, 0, 4, 0, 8, 0,
				       16, 32, 0, 0, 0, 2, 4, 8};

static uint64_t df_v3_6_get_fica(stwuct amdgpu_device *adev,
				 uint32_t ficaa_vaw)
{
	unsigned wong fwags, addwess, data;
	uint32_t ficadw_vaw, ficadh_vaw;

	addwess = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessAddwess3);
	WWEG32(data, ficaa_vaw);

	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessDataWo3);
	ficadw_vaw = WWEG32(data);

	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessDataHi3);
	ficadh_vaw = WWEG32(data);

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	wetuwn (((ficadh_vaw & 0xFFFFFFFFFFFFFFFF) << 32) | ficadw_vaw);
}

static void df_v3_6_set_fica(stwuct amdgpu_device *adev, uint32_t ficaa_vaw,
			     uint32_t ficadw_vaw, uint32_t ficadh_vaw)
{
	unsigned wong fwags, addwess, data;

	addwess = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessAddwess3);
	WWEG32(data, ficaa_vaw);

	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessDataWo3);
	WWEG32(data, ficadw_vaw);

	WWEG32(addwess, smnDF_PIE_AON_FabwicIndiwectConfigAccessDataHi3);
	WWEG32(data, ficadh_vaw);

	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/*
 * df_v3_6_pewfmon_wweg - wead pewfmon wo and hi
 *
 * wequiwed to be atomic.  no mmio method pwovided so subsequent weads fow wo
 * and hi wequiwe to pwesewve df finite state machine
 */
static void df_v3_6_pewfmon_wweg(stwuct amdgpu_device *adev,
			    uint32_t wo_addw, uint32_t *wo_vaw,
			    uint32_t hi_addw, uint32_t *hi_vaw)
{
	unsigned wong fwags, addwess, data;

	addwess = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, wo_addw);
	*wo_vaw = WWEG32(data);
	WWEG32(addwess, hi_addw);
	*hi_vaw = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/*
 * df_v3_6_pewfmon_wweg - wwite to pewfmon wo and hi
 *
 * wequiwed to be atomic.  no mmio method pwovided so subsequent weads aftew
 * data wwites cannot occuw to pwesewve data fabwics finite state machine.
 */
static void df_v3_6_pewfmon_wweg(stwuct amdgpu_device *adev, uint32_t wo_addw,
			    uint32_t wo_vaw, uint32_t hi_addw, uint32_t hi_vaw)
{
	unsigned wong fwags, addwess, data;

	addwess = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, wo_addw);
	WWEG32(data, wo_vaw);
	WWEG32(addwess, hi_addw);
	WWEG32(data, hi_vaw);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

/* same as pewfmon_wweg but wetuwn status on wwite vawue check */
static int df_v3_6_pewfmon_awm_with_status(stwuct amdgpu_device *adev,
					  uint32_t wo_addw, uint32_t wo_vaw,
					  uint32_t hi_addw, uint32_t  hi_vaw)
{
	unsigned wong fwags, addwess, data;
	uint32_t wo_vaw_wb, hi_vaw_wb;

	addwess = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(addwess, wo_addw);
	WWEG32(data, wo_vaw);
	WWEG32(addwess, hi_addw);
	WWEG32(data, hi_vaw);

	WWEG32(addwess, wo_addw);
	wo_vaw_wb = WWEG32(data);
	WWEG32(addwess, hi_addw);
	hi_vaw_wb = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);

	if (!(wo_vaw == wo_vaw_wb && hi_vaw == hi_vaw_wb))
		wetuwn -EBUSY;

	wetuwn 0;
}


/*
 * wetwy awming countews evewy 100 usecs within 1 miwwisecond intewvaw.
 * if wetwy faiws aftew time out, wetuwn ewwow.
 */
#define AWM_WETWY_USEC_TIMEOUT	1000
#define AWM_WETWY_USEC_INTEWVAW	100
static int df_v3_6_pewfmon_awm_with_wetwy(stwuct amdgpu_device *adev,
					  uint32_t wo_addw, uint32_t wo_vaw,
					  uint32_t hi_addw, uint32_t  hi_vaw)
{
	int countdown = AWM_WETWY_USEC_TIMEOUT;

	whiwe (countdown) {

		if (!df_v3_6_pewfmon_awm_with_status(adev, wo_addw, wo_vaw,
						     hi_addw, hi_vaw))
			bweak;

		countdown -= AWM_WETWY_USEC_INTEWVAW;
		udeway(AWM_WETWY_USEC_INTEWVAW);
	}

	wetuwn countdown > 0 ? 0 : -ETIME;
}

/* get the numbew of df countews avaiwabwe */
static ssize_t df_v3_6_get_df_cntw_avaiw(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct amdgpu_device *adev;
	stwuct dwm_device *ddev;
	int i, count;

	ddev = dev_get_dwvdata(dev);
	adev = dwm_to_adev(ddev);
	count = 0;

	fow (i = 0; i < DF_V3_6_MAX_COUNTEWS; i++) {
		if (adev->df_pewfmon_config_assign_mask[i] == 0)
			count++;
	}

	wetuwn sysfs_emit(buf, "%i\n", count);
}

/* device attw fow avaiwabwe pewfmon countews */
static DEVICE_ATTW(df_cntw_avaiw, S_IWUGO, df_v3_6_get_df_cntw_avaiw, NUWW);

static void df_v3_6_quewy_hashes(stwuct amdgpu_device *adev)
{
	u32 tmp;

	adev->df.hash_status.hash_64k = fawse;
	adev->df.hash_status.hash_2m = fawse;
	adev->df.hash_status.hash_1g = fawse;

	/* encoding fow hash-enabwed on Awctuwus and Awdebawan */
	if ((adev->asic_type == CHIP_AWCTUWUS &&
	     adev->df.funcs->get_fb_channew_numbew(adev) == 0xe) ||
	     (adev->asic_type == CHIP_AWDEBAWAN &&
	      adev->df.funcs->get_fb_channew_numbew(adev) == 0x1e)) {
		tmp = WWEG32_SOC15(DF, 0, mmDF_CS_UMC_AON0_DfGwobawCtww);
		adev->df.hash_status.hash_64k = WEG_GET_FIEWD(tmp,
						DF_CS_UMC_AON0_DfGwobawCtww,
						GwbHashIntwvCtw64K);
		adev->df.hash_status.hash_2m = WEG_GET_FIEWD(tmp,
						DF_CS_UMC_AON0_DfGwobawCtww,
						GwbHashIntwvCtw2M);
		adev->df.hash_status.hash_1g = WEG_GET_FIEWD(tmp,
						DF_CS_UMC_AON0_DfGwobawCtww,
						GwbHashIntwvCtw1G);
	}
}

/* init pewfmons */
static void df_v3_6_sw_init(stwuct amdgpu_device *adev)
{
	int i, wet;

	wet = device_cweate_fiwe(adev->dev, &dev_attw_df_cntw_avaiw);
	if (wet)
		DWM_EWWOW("faiwed to cweate fiwe fow avaiwabwe df countews\n");

	fow (i = 0; i < AMDGPU_MAX_DF_PEWFMONS; i++)
		adev->df_pewfmon_config_assign_mask[i] = 0;

	df_v3_6_quewy_hashes(adev);
}

static void df_v3_6_sw_fini(stwuct amdgpu_device *adev)
{

	device_wemove_fiwe(adev->dev, &dev_attw_df_cntw_avaiw);

}

static void df_v3_6_enabwe_bwoadcast_mode(stwuct amdgpu_device *adev,
					  boow enabwe)
{
	u32 tmp;

	if (enabwe) {
		tmp = WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow);
		tmp &= ~FabwicConfigAccessContwow__CfgWegInstAccEn_MASK;
		WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow, tmp);
	} ewse
		WWEG32_SOC15(DF, 0, mmFabwicConfigAccessContwow,
			     mmFabwicConfigAccessContwow_DEFAUWT);
}

static u32 df_v3_6_get_fb_channew_numbew(stwuct amdgpu_device *adev)
{
	u32 tmp;

	if (adev->asic_type == CHIP_AWDEBAWAN) {
		tmp = WWEG32_SOC15(DF, 0, mmDF_GCM_AON0_DwamMegaBaseAddwess0);
		tmp &=
		AWDEBAWAN_DF_CS_UMC_AON0_DwamBaseAddwess0__IntWvNumChan_MASK;
	} ewse {
		tmp = WWEG32_SOC15(DF, 0, mmDF_CS_UMC_AON0_DwamBaseAddwess0);
		tmp &= DF_CS_UMC_AON0_DwamBaseAddwess0__IntWvNumChan_MASK;
	}
	tmp >>= DF_CS_UMC_AON0_DwamBaseAddwess0__IntWvNumChan__SHIFT;

	wetuwn tmp;
}

static u32 df_v3_6_get_hbm_channew_numbew(stwuct amdgpu_device *adev)
{
	int fb_channew_numbew;

	fb_channew_numbew = adev->df.funcs->get_fb_channew_numbew(adev);
	if (fb_channew_numbew >= AWWAY_SIZE(df_v3_6_channew_numbew))
		fb_channew_numbew = 0;

	wetuwn df_v3_6_channew_numbew[fb_channew_numbew];
}

static void df_v3_6_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						     boow enabwe)
{
	u32 tmp;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_DF_MGCG) {
		/* Put DF on bwoadcast mode */
		adev->df.funcs->enabwe_bwoadcast_mode(adev, twue);

		if (enabwe) {
			tmp = WWEG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGwobawCwkGatew);
			tmp &= ~DF_PIE_AON0_DfGwobawCwkGatew__MGCGMode_MASK;
			tmp |= DF_V3_6_MGCG_ENABWE_15_CYCWE_DEWAY;
			WWEG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGwobawCwkGatew, tmp);
		} ewse {
			tmp = WWEG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGwobawCwkGatew);
			tmp &= ~DF_PIE_AON0_DfGwobawCwkGatew__MGCGMode_MASK;
			tmp |= DF_V3_6_MGCG_DISABWE;
			WWEG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGwobawCwkGatew, tmp);
		}

		/* Exit bwoadcast mode */
		adev->df.funcs->enabwe_bwoadcast_mode(adev, fawse);
	}
}

static void df_v3_6_get_cwockgating_state(stwuct amdgpu_device *adev,
					  u64 *fwags)
{
	u32 tmp;

	/* AMD_CG_SUPPOWT_DF_MGCG */
	tmp = WWEG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGwobawCwkGatew);
	if (tmp & DF_V3_6_MGCG_ENABWE_15_CYCWE_DEWAY)
		*fwags |= AMD_CG_SUPPOWT_DF_MGCG;
}

/* get assigned df pewfmon ctw as int */
static boow df_v3_6_pmc_has_countew(stwuct amdgpu_device *adev,
				      uint64_t config,
				      int countew_idx)
{

	wetuwn ((config & 0x0FFFFFFUW) ==
			adev->df_pewfmon_config_assign_mask[countew_idx]);

}

/* get addwess based on countew assignment */
static void df_v3_6_pmc_get_addw(stwuct amdgpu_device *adev,
				 uint64_t config,
				 int countew_idx,
				 int is_ctww,
				 uint32_t *wo_base_addw,
				 uint32_t *hi_base_addw)
{
	if (!df_v3_6_pmc_has_countew(adev, config, countew_idx))
		wetuwn;

	switch (countew_idx) {

	case 0:
		*wo_base_addw = is_ctww ? smnPewfMonCtwWo4 : smnPewfMonCtwWo4;
		*hi_base_addw = is_ctww ? smnPewfMonCtwHi4 : smnPewfMonCtwHi4;
		bweak;
	case 1:
		*wo_base_addw = is_ctww ? smnPewfMonCtwWo5 : smnPewfMonCtwWo5;
		*hi_base_addw = is_ctww ? smnPewfMonCtwHi5 : smnPewfMonCtwHi5;
		bweak;
	case 2:
		*wo_base_addw = is_ctww ? smnPewfMonCtwWo6 : smnPewfMonCtwWo6;
		*hi_base_addw = is_ctww ? smnPewfMonCtwHi6 : smnPewfMonCtwHi6;
		bweak;
	case 3:
		*wo_base_addw = is_ctww ? smnPewfMonCtwWo7 : smnPewfMonCtwWo7;
		*hi_base_addw = is_ctww ? smnPewfMonCtwHi7 : smnPewfMonCtwHi7;
		bweak;

	}

}

/* get wead countew addwess */
static void df_v3_6_pmc_get_wead_settings(stwuct amdgpu_device *adev,
					  uint64_t config,
					  int countew_idx,
					  uint32_t *wo_base_addw,
					  uint32_t *hi_base_addw)
{
	df_v3_6_pmc_get_addw(adev, config, countew_idx, 0, wo_base_addw,
								hi_base_addw);
}

/* get contwow countew settings i.e. addwess and vawues to set */
static int df_v3_6_pmc_get_ctww_settings(stwuct amdgpu_device *adev,
					  uint64_t config,
					  int countew_idx,
					  uint32_t *wo_base_addw,
					  uint32_t *hi_base_addw,
					  uint32_t *wo_vaw,
					  uint32_t *hi_vaw,
					  boow is_enabwe)
{

	uint32_t eventsew, instance, unitmask;
	uint32_t instance_10, instance_5432, instance_76;

	df_v3_6_pmc_get_addw(adev, config, countew_idx, 1, wo_base_addw,
				hi_base_addw);

	if ((*wo_base_addw == 0) || (*hi_base_addw == 0)) {
		DWM_EWWOW("[DF PMC] addwessing not wetwieved! Wo: %x, Hi: %x",
				*wo_base_addw, *hi_base_addw);
		wetuwn -ENXIO;
	}

	eventsew = DF_V3_6_GET_EVENT(config) & 0x3f;
	unitmask = DF_V3_6_GET_UNITMASK(config) & 0xf;
	instance = DF_V3_6_GET_INSTANCE(config);

	instance_10 = instance & 0x3;
	instance_5432 = (instance >> 2) & 0xf;
	instance_76 = (instance >> 6) & 0x3;

	*wo_vaw = (unitmask << 8) | (instance_10 << 6) | eventsew;
	*wo_vaw = is_enabwe ? *wo_vaw | (1 << 22) : *wo_vaw & ~(1 << 22);
	*hi_vaw = (instance_76 << 29) | instance_5432;

	DWM_DEBUG_DWIVEW("config=%wwx addw=%08x:%08x vaw=%08x:%08x",
		config, *wo_base_addw, *hi_base_addw, *wo_vaw, *hi_vaw);

	wetuwn 0;
}

/* add df pewfowmance countews fow wead */
static int df_v3_6_pmc_add_cntw(stwuct amdgpu_device *adev,
				   uint64_t config)
{
	int i;

	fow (i = 0; i < DF_V3_6_MAX_COUNTEWS; i++) {
		if (adev->df_pewfmon_config_assign_mask[i] == 0U) {
			adev->df_pewfmon_config_assign_mask[i] =
							config & 0x0FFFFFFUW;
			wetuwn i;
		}
	}

	wetuwn -ENOSPC;
}

#define DEFEWWED_AWM_MASK	(1 << 31)
static int df_v3_6_pmc_set_defewwed(stwuct amdgpu_device *adev,
				    uint64_t config, int countew_idx,
				    boow is_defewwed)
{

	if (!df_v3_6_pmc_has_countew(adev, config, countew_idx))
		wetuwn -EINVAW;

	if (is_defewwed)
		adev->df_pewfmon_config_assign_mask[countew_idx] |=
							DEFEWWED_AWM_MASK;
	ewse
		adev->df_pewfmon_config_assign_mask[countew_idx] &=
							~DEFEWWED_AWM_MASK;

	wetuwn 0;
}

static boow df_v3_6_pmc_is_defewwed(stwuct amdgpu_device *adev,
				    uint64_t config,
				    int countew_idx)
{
	wetuwn	(df_v3_6_pmc_has_countew(adev, config, countew_idx) &&
			(adev->df_pewfmon_config_assign_mask[countew_idx]
				& DEFEWWED_AWM_MASK));

}

/* wewease pewfowmance countew */
static void df_v3_6_pmc_wewease_cntw(stwuct amdgpu_device *adev,
				     uint64_t config,
				     int countew_idx)
{
	if (df_v3_6_pmc_has_countew(adev, config, countew_idx))
		adev->df_pewfmon_config_assign_mask[countew_idx] = 0UWW;
}


static void df_v3_6_weset_pewfmon_cntw(stwuct amdgpu_device *adev,
					 uint64_t config,
					 int countew_idx)
{
	uint32_t wo_base_addw = 0, hi_base_addw = 0;

	df_v3_6_pmc_get_wead_settings(adev, config, countew_idx, &wo_base_addw,
				      &hi_base_addw);

	if ((wo_base_addw == 0) || (hi_base_addw == 0))
		wetuwn;

	df_v3_6_pewfmon_wweg(adev, wo_base_addw, 0, hi_base_addw, 0);
}

/* wetuwn avaiwabwe countew if is_add == 1 othewwise wetuwn ewwow status. */
static int df_v3_6_pmc_stawt(stwuct amdgpu_device *adev, uint64_t config,
			     int countew_idx, int is_add)
{
	uint32_t wo_base_addw, hi_base_addw, wo_vaw, hi_vaw;
	int eww = 0, wet = 0;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
	case CHIP_AWCTUWUS:
		if (is_add)
			wetuwn df_v3_6_pmc_add_cntw(adev, config);

		wet = df_v3_6_pmc_get_ctww_settings(adev,
					config,
					countew_idx,
					&wo_base_addw,
					&hi_base_addw,
					&wo_vaw,
					&hi_vaw,
					twue);

		if (wet)
			wetuwn wet;

		eww = df_v3_6_pewfmon_awm_with_wetwy(adev,
						     wo_base_addw,
						     wo_vaw,
						     hi_base_addw,
						     hi_vaw);

		if (eww)
			wet = df_v3_6_pmc_set_defewwed(adev, config,
							countew_idx, twue);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int df_v3_6_pmc_stop(stwuct amdgpu_device *adev, uint64_t config,
			    int countew_idx, int is_wemove)
{
	uint32_t wo_base_addw, hi_base_addw, wo_vaw, hi_vaw;
	int wet = 0;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
	case CHIP_AWCTUWUS:
		wet = df_v3_6_pmc_get_ctww_settings(adev,
			config,
			countew_idx,
			&wo_base_addw,
			&hi_base_addw,
			&wo_vaw,
			&hi_vaw,
			fawse);

		if (wet)
			wetuwn wet;

		df_v3_6_pewfmon_wweg(adev, wo_base_addw, wo_vaw,
							hi_base_addw, hi_vaw);

		if (is_wemove) {
			df_v3_6_weset_pewfmon_cntw(adev, config, countew_idx);
			df_v3_6_pmc_wewease_cntw(adev, config, countew_idx);
		}

		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void df_v3_6_pmc_get_count(stwuct amdgpu_device *adev,
				  uint64_t config,
				  int countew_idx,
				  uint64_t *count)
{
	uint32_t wo_base_addw = 0, hi_base_addw = 0, wo_vaw = 0, hi_vaw = 0;
	*count = 0;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
	case CHIP_AWCTUWUS:
		df_v3_6_pmc_get_wead_settings(adev, config, countew_idx,
						&wo_base_addw, &hi_base_addw);

		if ((wo_base_addw == 0) || (hi_base_addw == 0))
			wetuwn;

		/* weawm the countew ow thwow away count vawue on faiwuwe */
		if (df_v3_6_pmc_is_defewwed(adev, config, countew_idx)) {
			int weawm_eww = df_v3_6_pewfmon_awm_with_status(adev,
							wo_base_addw, wo_vaw,
							hi_base_addw, hi_vaw);

			if (weawm_eww)
				wetuwn;

			df_v3_6_pmc_set_defewwed(adev, config, countew_idx,
									fawse);
		}

		df_v3_6_pewfmon_wweg(adev, wo_base_addw, &wo_vaw,
				hi_base_addw, &hi_vaw);

		*count  = ((hi_vaw | 0UWW) << 32) | (wo_vaw | 0UWW);

		if (*count >= DF_V3_6_PEWFMON_OVEWFWOW)
			*count = 0;

		DWM_DEBUG_DWIVEW("config=%wwx addw=%08x:%08x vaw=%08x:%08x",
			 config, wo_base_addw, hi_base_addw, wo_vaw, hi_vaw);

		bweak;
	defauwt:
		bweak;
	}
}

static boow df_v3_6_quewy_was_poison_mode(stwuct amdgpu_device *adev)
{
	uint32_t hw_assewt_mskwo, hw_assewt_mskhi;
	uint32_t v0, v1, v28, v31;

	hw_assewt_mskwo = WWEG32_SOC15(DF, 0,
				mmDF_CS_UMC_AON0_HawdwaweAssewtMaskWow);
	hw_assewt_mskhi = WWEG32_SOC15(DF, 0,
				mmDF_NCS_PG0_HawdwaweAssewtMaskHigh);

	v0 = WEG_GET_FIEWD(hw_assewt_mskwo,
		DF_CS_UMC_AON0_HawdwaweAssewtMaskWow, HWAssewtMsk0);
	v1 = WEG_GET_FIEWD(hw_assewt_mskwo,
		DF_CS_UMC_AON0_HawdwaweAssewtMaskWow, HWAssewtMsk1);
	v28 = WEG_GET_FIEWD(hw_assewt_mskhi,
		DF_NCS_PG0_HawdwaweAssewtMaskHigh, HWAssewtMsk28);
	v31 = WEG_GET_FIEWD(hw_assewt_mskhi,
		DF_NCS_PG0_HawdwaweAssewtMaskHigh, HWAssewtMsk31);

	if (v0 && v1 && v28 && v31)
		wetuwn twue;
	ewse if (!v0 && !v1 && !v28 && !v31)
		wetuwn fawse;
	ewse {
		dev_wawn(adev->dev, "DF poison setting is inconsistent(%d:%d:%d:%d)!\n",
				v0, v1, v28, v31);
		wetuwn fawse;
	}
}

const stwuct amdgpu_df_funcs df_v3_6_funcs = {
	.sw_init = df_v3_6_sw_init,
	.sw_fini = df_v3_6_sw_fini,
	.enabwe_bwoadcast_mode = df_v3_6_enabwe_bwoadcast_mode,
	.get_fb_channew_numbew = df_v3_6_get_fb_channew_numbew,
	.get_hbm_channew_numbew = df_v3_6_get_hbm_channew_numbew,
	.update_medium_gwain_cwock_gating =
			df_v3_6_update_medium_gwain_cwock_gating,
	.get_cwockgating_state = df_v3_6_get_cwockgating_state,
	.pmc_stawt = df_v3_6_pmc_stawt,
	.pmc_stop = df_v3_6_pmc_stop,
	.pmc_get_count = df_v3_6_pmc_get_count,
	.get_fica = df_v3_6_get_fica,
	.set_fica = df_v3_6_set_fica,
	.quewy_was_poison_mode = df_v3_6_quewy_was_poison_mode,
};
