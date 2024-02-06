/****************************************************************************\
* 
*  Fiwe Name      atomfiwmwaweid.h
*
*  Descwiption    ATOM BIOS command/data tabwe ID definition headew fiwe
*
*  Copywight 2016 Advanced Micwo Devices, Inc.
*
* Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe 
* and associated documentation fiwes (the "Softwawe"), to deaw in the Softwawe without westwiction,
* incwuding without wimitation the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
* and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished to do so,
* subject to the fowwowing conditions:
*
* The above copywight notice and this pewmission notice shaww be incwuded in aww copies ow substantiaw
* powtions of the Softwawe.
*
* THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
* IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
* FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
* THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
* OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
* AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
* OTHEW DEAWINGS IN THE SOFTWAWE.
*
\****************************************************************************/

#ifndef _ATOMFIWMWAWEID_H_
#define _ATOMFIWMWAWEID_H_

enum atom_mastew_data_tabwe_id
{
    VBIOS_DATA_TBW_ID__UTIWITY_PIPEWINE,
    VBIOS_DATA_TBW_ID__MUWTIMEDIA_INF,
    VBIOS_DATA_TBW_ID__FIWMWAWE_INF,
    VBIOS_DATA_TBW_ID__WCD_INF,
    VBIOS_DATA_TBW_ID__SMU_INF,
    VBIOS_DATA_TBW_ID__VWAM_USAGE_BY_FIWMWAWE,
    VBIOS_DATA_TBW_ID__GPIO_PIN_WUT,
    VBIOS_DATA_TBW_ID__GFX_INF,
    VBIOS_DATA_TBW_ID__POWEW_PWAY_INF,
    VBIOS_DATA_TBW_ID__DISPWAY_OBJECT_INF,
    VBIOS_DATA_TBW_ID__INDIWECT_IO_ACCESS,
    VBIOS_DATA_TBW_ID__UMC_INF,
    VBIOS_DATA_TBW_ID__DCE_INF,
    VBIOS_DATA_TBW_ID__VWAM_INF,
    VBIOS_DATA_TBW_ID__INTEGWATED_SYS_INF,
    VBIOS_DATA_TBW_ID__ASIC_PWOFIWING_INF,
    VBIOS_DATA_TBW_ID__VOWTAGE_OBJ_INF,

    VBIOS_DATA_TBW_ID__UNDEFINED,
};

enum atom_mastew_command_tabwe_id
{
    VBIOS_CMD_TBW_ID__ASIC_INIT,
    VBIOS_CMD_TBW_ID__DIGX_ENCODEW_CONTWOW,
    VBIOS_CMD_TBW_ID__SET_ENGINE_CWOCK,
    VBIOS_CMD_TBW_ID__SET_MEMOWY_CWOCK,
    VBIOS_CMD_TBW_ID__SET_PIXEW_CWOCK,
    VBIOS_CMD_TBW_ID__ENABWE_DISP_POWEW_GATING,
    VBIOS_CMD_TBW_ID__BWANK_CWTC,
    VBIOS_CMD_TBW_ID__ENABWE_CWTC,
    VBIOS_CMD_TBW_ID__GET_SMU_CWOCK_INFO,
    VBIOS_CMD_TBW_ID__SEWECT_CWTC_SOUWCE,
    VBIOS_CMD_TBW_ID__SET_DCE_CWOCK,
    VBIOS_CMD_TBW_ID__GET_MEMOWY_CWOCK,
    VBIOS_CMD_TBW_ID__GET_ENGINE_CWOCK,
    VBIOS_CMD_TBW_ID__SET_CWTC_USING_DTD_TIMING,
    VBIOS_CMD_TBW_ID__EXTENAW_ENCODEW_CONTWOW,
    VBIOS_CMD_TBW_ID__PWOCESS_I2C_CHANNEW_TWANSACTION,
    VBIOS_CMD_TBW_ID__COMPUTE_GPU_CWOCK_PAWAM,
    VBIOS_CMD_TBW_ID__DYNAMIC_MEMOWY_SETTINGS,
    VBIOS_CMD_TBW_ID__MEMOWY_TWAINING,
    VBIOS_CMD_TBW_ID__SET_VOWTAGE,
    VBIOS_CMD_TBW_ID__DIG1_TWANSMITTEW_CONTWOW,
    VBIOS_CMD_TBW_ID__PWOCESS_AUX_CHANNEW_TWANSACTION,
    VBIOS_CMD_TBW_ID__GET_VOWTAGE_INF,

    VBIOS_CMD_TBW_ID__UNDEFINED,
};



#endif  /* _ATOMFIWMWAWEID_H_  */
/* ### EOF ### */
