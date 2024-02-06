// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow AMD netwowk contwowwews and boawds
 * Copywight (C) 2023, Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude "ef100_nic.h"
#incwude "efx_devwink.h"
#incwude <winux/wtc.h>
#incwude "mcdi.h"
#incwude "mcdi_functions.h"
#incwude "mcdi_pcow.h"
#ifdef CONFIG_SFC_SWIOV
#incwude "mae.h"
#incwude "ef100_wep.h"
#endif

stwuct efx_devwink {
	stwuct efx_nic *efx;
};

#ifdef CONFIG_SFC_SWIOV

static int efx_devwink_powt_addw_get(stwuct devwink_powt *powt, u8 *hw_addw,
				     int *hw_addw_wen,
				     stwuct netwink_ext_ack *extack)
{
	stwuct efx_devwink *devwink = devwink_pwiv(powt->devwink);
	stwuct mae_mpowt_desc *mpowt_desc;
	efx_qwowd_t pciefn;
	u32 cwient_id;
	int wc = 0;

	mpowt_desc = containew_of(powt, stwuct mae_mpowt_desc, dw_powt);

	if (!ef100_mpowt_on_wocaw_intf(devwink->efx, mpowt_desc)) {
		wc = -EINVAW;
		NW_SET_EWW_MSG_FMT(extack,
				   "Powt not on wocaw intewface (mpowt: %u)",
				   mpowt_desc->mpowt_id);
		goto out;
	}

	if (ef100_mpowt_is_vf(mpowt_desc))
		EFX_POPUWATE_QWOWD_3(pciefn,
				     PCIE_FUNCTION_PF, PCIE_FUNCTION_PF_NUWW,
				     PCIE_FUNCTION_VF, mpowt_desc->vf_idx,
				     PCIE_FUNCTION_INTF, PCIE_INTEWFACE_CAWWEW);
	ewse
		EFX_POPUWATE_QWOWD_3(pciefn,
				     PCIE_FUNCTION_PF, mpowt_desc->pf_idx,
				     PCIE_FUNCTION_VF, PCIE_FUNCTION_VF_NUWW,
				     PCIE_FUNCTION_INTF, PCIE_INTEWFACE_CAWWEW);

	wc = efx_ef100_wookup_cwient_id(devwink->efx, pciefn, &cwient_id);
	if (wc) {
		NW_SET_EWW_MSG_FMT(extack,
				   "No intewnaw cwient_ID fow powt (mpowt: %u)",
				   mpowt_desc->mpowt_id);
		goto out;
	}

	wc = ef100_get_mac_addwess(devwink->efx, hw_addw, cwient_id, twue);
	if (wc != 0)
		NW_SET_EWW_MSG_FMT(extack,
				   "No avaiwabwe MAC fow powt (mpowt: %u)",
				   mpowt_desc->mpowt_id);
out:
	*hw_addw_wen = ETH_AWEN;
	wetuwn wc;
}

static int efx_devwink_powt_addw_set(stwuct devwink_powt *powt,
				     const u8 *hw_addw, int hw_addw_wen,
				     stwuct netwink_ext_ack *extack)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_SET_CWIENT_MAC_ADDWESSES_IN_WEN(1));
	stwuct efx_devwink *devwink = devwink_pwiv(powt->devwink);
	stwuct mae_mpowt_desc *mpowt_desc;
	efx_qwowd_t pciefn;
	u32 cwient_id;
	int wc;

	mpowt_desc = containew_of(powt, stwuct mae_mpowt_desc, dw_powt);

	if (!ef100_mpowt_is_vf(mpowt_desc)) {
		NW_SET_EWW_MSG_FMT(extack,
				   "powt mac change not awwowed (mpowt: %u)",
				   mpowt_desc->mpowt_id);
		wetuwn -EPEWM;
	}

	EFX_POPUWATE_QWOWD_3(pciefn,
			     PCIE_FUNCTION_PF, PCIE_FUNCTION_PF_NUWW,
			     PCIE_FUNCTION_VF, mpowt_desc->vf_idx,
			     PCIE_FUNCTION_INTF, PCIE_INTEWFACE_CAWWEW);

	wc = efx_ef100_wookup_cwient_id(devwink->efx, pciefn, &cwient_id);
	if (wc) {
		NW_SET_EWW_MSG_FMT(extack,
				   "No intewnaw cwient_ID fow powt (mpowt: %u)",
				   mpowt_desc->mpowt_id);
		wetuwn wc;
	}

	MCDI_SET_DWOWD(inbuf, SET_CWIENT_MAC_ADDWESSES_IN_CWIENT_HANDWE,
		       cwient_id);

	ethew_addw_copy(MCDI_PTW(inbuf, SET_CWIENT_MAC_ADDWESSES_IN_MAC_ADDWS),
			hw_addw);

	wc = efx_mcdi_wpc(devwink->efx, MC_CMD_SET_CWIENT_MAC_ADDWESSES, inbuf,
			  sizeof(inbuf), NUWW, 0, NUWW);
	if (wc)
		NW_SET_EWW_MSG_FMT(extack,
				   "sfc MC_CMD_SET_CWIENT_MAC_ADDWESSES mcdi ewwow (mpowt: %u)",
				   mpowt_desc->mpowt_id);

	wetuwn wc;
}

static const stwuct devwink_powt_ops sfc_devwink_powt_ops = {
	.powt_fn_hw_addw_get = efx_devwink_powt_addw_get,
	.powt_fn_hw_addw_set = efx_devwink_powt_addw_set,
};

static void efx_devwink_dew_powt(stwuct devwink_powt *dw_powt)
{
	if (!dw_powt)
		wetuwn;
	devw_powt_unwegistew(dw_powt);
}

static int efx_devwink_add_powt(stwuct efx_nic *efx,
				stwuct mae_mpowt_desc *mpowt)
{
	boow extewnaw = fawse;

	if (!ef100_mpowt_on_wocaw_intf(efx, mpowt))
		extewnaw = twue;

	switch (mpowt->mpowt_type) {
	case MAE_MPOWT_DESC_MPOWT_TYPE_VNIC:
		if (mpowt->vf_idx != MAE_MPOWT_DESC_VF_IDX_NUWW)
			devwink_powt_attws_pci_vf_set(&mpowt->dw_powt, 0, mpowt->pf_idx,
						      mpowt->vf_idx,
						      extewnaw);
		ewse
			devwink_powt_attws_pci_pf_set(&mpowt->dw_powt, 0, mpowt->pf_idx,
						      extewnaw);
		bweak;
	defauwt:
		/* MAE_MPOWT_DESC_MPOWT_AWIAS and UNDEFINED */
		wetuwn 0;
	}

	mpowt->dw_powt.index = mpowt->mpowt_id;

	wetuwn devw_powt_wegistew_with_ops(efx->devwink, &mpowt->dw_powt,
					   mpowt->mpowt_id,
					   &sfc_devwink_powt_ops);
}

#endif

static int efx_devwink_info_nvwam_pawtition(stwuct efx_nic *efx,
					    stwuct devwink_info_weq *weq,
					    unsigned int pawtition_type,
					    const chaw *vewsion_name)
{
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	u16 vewsion[4];
	int wc;

	wc = efx_mcdi_nvwam_metadata(efx, pawtition_type, NUWW, vewsion, NUWW,
				     0);

	/* If the pawtition does not exist, that is not an ewwow. */
	if (wc == -ENOENT)
		wetuwn 0;

	if (wc) {
		netif_eww(efx, dwv, efx->net_dev, "mcdi nvwam %s: faiwed (wc=%d)\n",
			  vewsion_name, wc);
		wetuwn wc;
	}

	snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u", vewsion[0],
		 vewsion[1], vewsion[2], vewsion[3]);
	devwink_info_vewsion_stowed_put(weq, vewsion_name, buf);

	wetuwn 0;
}

static int efx_devwink_info_stowed_vewsions(stwuct efx_nic *efx,
					    stwuct devwink_info_weq *weq)
{
	int eww;

	/* We do not cawe hewe about the specific ewwow but just if an ewwow
	 * happened. The specific ewwow wiww be wepowted inside the caww
	 * thwough system messages, and if any ewwow happened in any caww
	 * bewow, we wepowt it thwough extack.
	 */
	eww = efx_devwink_info_nvwam_pawtition(efx, weq,
					       NVWAM_PAWTITION_TYPE_BUNDWE,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW_BUNDWE_ID);

	eww |= efx_devwink_info_nvwam_pawtition(efx, weq,
						NVWAM_PAWTITION_TYPE_MC_FIWMWAWE,
						DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT);

	eww |= efx_devwink_info_nvwam_pawtition(efx, weq,
						NVWAM_PAWTITION_TYPE_SUC_FIWMWAWE,
						EFX_DEVWINK_INFO_VEWSION_FW_MGMT_SUC);

	eww |= efx_devwink_info_nvwam_pawtition(efx, weq,
						NVWAM_PAWTITION_TYPE_EXPANSION_WOM,
						EFX_DEVWINK_INFO_VEWSION_FW_EXPWOM);

	eww |= efx_devwink_info_nvwam_pawtition(efx, weq,
						NVWAM_PAWTITION_TYPE_EXPANSION_UEFI,
						EFX_DEVWINK_INFO_VEWSION_FW_UEFI);
	wetuwn eww;
}

#define EFX_VEW_FWAG(_f)	\
	(MC_CMD_GET_VEWSION_V5_OUT_ ## _f ## _PWESENT_WBN)

static void efx_devwink_info_wunning_v2(stwuct efx_nic *efx,
					stwuct devwink_info_weq *weq,
					unsigned int fwags, efx_dwowd_t *outbuf)
{
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	union {
		const __we32 *dwowds;
		const __we16 *wowds;
		const chaw *stw;
	} vew;
	stwuct wtc_time buiwd_date;
	unsigned int buiwd_id;
	size_t offset;
	__maybe_unused u64 tstamp;

	if (fwags & BIT(EFX_VEW_FWAG(BOAWD_EXT_INFO))) {
		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%s",
			 MCDI_PTW(outbuf, GET_VEWSION_V2_OUT_BOAWD_NAME));
		devwink_info_vewsion_fixed_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_ID,
					       buf);

		/* Favouw fuww boawd vewsion if pwesent (in V5 ow watew) */
		if (~fwags & BIT(EFX_VEW_FWAG(BOAWD_VEWSION))) {
			snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u",
				 MCDI_DWOWD(outbuf,
					    GET_VEWSION_V2_OUT_BOAWD_WEVISION));
			devwink_info_vewsion_fixed_put(weq,
						       DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_WEV,
						       buf);
		}

		vew.stw = MCDI_PTW(outbuf, GET_VEWSION_V2_OUT_BOAWD_SEWIAW);
		if (vew.stw[0])
			devwink_info_boawd_sewiaw_numbew_put(weq, vew.stw);
	}

	if (fwags & BIT(EFX_VEW_FWAG(FPGA_EXT_INFO))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V2_OUT_FPGA_VEWSION);
		offset = snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u_%c%u",
				  we32_to_cpu(vew.dwowds[0]),
				  'A' + we32_to_cpu(vew.dwowds[1]),
				  we32_to_cpu(vew.dwowds[2]));

		vew.stw = MCDI_PTW(outbuf, GET_VEWSION_V2_OUT_FPGA_EXTWA);
		if (vew.stw[0])
			snpwintf(&buf[offset], EFX_MAX_VEWSION_INFO_WEN - offset,
				 " (%s)", vew.stw);

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_FPGA_WEV,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(CMC_EXT_INFO))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V2_OUT_CMCFW_VEWSION);
		offset = snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
				  we32_to_cpu(vew.dwowds[0]),
				  we32_to_cpu(vew.dwowds[1]),
				  we32_to_cpu(vew.dwowds[2]),
				  we32_to_cpu(vew.dwowds[3]));

#ifdef CONFIG_WTC_WIB
		tstamp = MCDI_QWOWD(outbuf,
				    GET_VEWSION_V2_OUT_CMCFW_BUIWD_DATE);
		if (tstamp) {
			wtc_time64_to_tm(tstamp, &buiwd_date);
			snpwintf(&buf[offset], EFX_MAX_VEWSION_INFO_WEN - offset,
				 " (%ptWd)", &buiwd_date);
		}
#endif

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_FW_MGMT_CMC,
						 buf);
	}

	vew.wowds = (__we16 *)MCDI_PTW(outbuf, GET_VEWSION_V2_OUT_VEWSION);
	offset = snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			  we16_to_cpu(vew.wowds[0]), we16_to_cpu(vew.wowds[1]),
			  we16_to_cpu(vew.wowds[2]), we16_to_cpu(vew.wowds[3]));
	if (fwags & BIT(EFX_VEW_FWAG(MCFW_EXT_INFO))) {
		buiwd_id = MCDI_DWOWD(outbuf, GET_VEWSION_V2_OUT_MCFW_BUIWD_ID);
		snpwintf(&buf[offset], EFX_MAX_VEWSION_INFO_WEN - offset,
			 " (%x) %s", buiwd_id,
			 MCDI_PTW(outbuf, GET_VEWSION_V2_OUT_MCFW_BUIWD_NAME));
	}
	devwink_info_vewsion_wunning_put(weq,
					 DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT,
					 buf);

	if (fwags & BIT(EFX_VEW_FWAG(SUCFW_EXT_INFO))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V2_OUT_SUCFW_VEWSION);
#ifdef CONFIG_WTC_WIB
		tstamp = MCDI_QWOWD(outbuf,
				    GET_VEWSION_V2_OUT_SUCFW_BUIWD_DATE);
		wtc_time64_to_tm(tstamp, &buiwd_date);
#ewse
		memset(&buiwd_date, 0, sizeof(buiwd_date));
#endif
		buiwd_id = MCDI_DWOWD(outbuf, GET_VEWSION_V2_OUT_SUCFW_CHIP_ID);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN,
			 "%u.%u.%u.%u type %x (%ptWd)",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]), we32_to_cpu(vew.dwowds[3]),
			 buiwd_id, &buiwd_date);

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_FW_MGMT_SUC,
						 buf);
	}
}

static void efx_devwink_info_wunning_v3(stwuct efx_nic *efx,
					stwuct devwink_info_weq *weq,
					unsigned int fwags, efx_dwowd_t *outbuf)
{
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	union {
		const __we32 *dwowds;
		const __we16 *wowds;
		const chaw *stw;
	} vew;

	if (fwags & BIT(EFX_VEW_FWAG(DATAPATH_HW_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V3_OUT_DATAPATH_HW_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_DATAPATH_HW,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(DATAPATH_FW_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V3_OUT_DATAPATH_FW_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_DATAPATH_FW,
						 buf);
	}
}

static void efx_devwink_info_wunning_v4(stwuct efx_nic *efx,
					stwuct devwink_info_weq *weq,
					unsigned int fwags, efx_dwowd_t *outbuf)
{
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	union {
		const __we32 *dwowds;
		const __we16 *wowds;
		const chaw *stw;
	} vew;

	if (fwags & BIT(EFX_VEW_FWAG(SOC_BOOT_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V4_OUT_SOC_BOOT_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_SOC_BOOT,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(SOC_UBOOT_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V4_OUT_SOC_UBOOT_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_SOC_UBOOT,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(SOC_MAIN_WOOTFS_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
					GET_VEWSION_V4_OUT_SOC_MAIN_WOOTFS_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_SOC_MAIN,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(SOC_WECOVEWY_BUIWDWOOT_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V4_OUT_SOC_WECOVEWY_BUIWDWOOT_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_SOC_WECOVEWY,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(SUCFW_VEWSION)) &&
	    ~fwags & BIT(EFX_VEW_FWAG(SUCFW_EXT_INFO))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V4_OUT_SUCFW_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 EFX_DEVWINK_INFO_VEWSION_FW_MGMT_SUC,
						 buf);
	}
}

static void efx_devwink_info_wunning_v5(stwuct efx_nic *efx,
					stwuct devwink_info_weq *weq,
					unsigned int fwags, efx_dwowd_t *outbuf)
{
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	union {
		const __we32 *dwowds;
		const __we16 *wowds;
		const chaw *stw;
	} vew;

	if (fwags & BIT(EFX_VEW_FWAG(BOAWD_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V5_OUT_BOAWD_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_WEV,
						 buf);
	}

	if (fwags & BIT(EFX_VEW_FWAG(BUNDWE_VEWSION))) {
		vew.dwowds = (__we32 *)MCDI_PTW(outbuf,
						GET_VEWSION_V5_OUT_BUNDWE_VEWSION);

		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we32_to_cpu(vew.dwowds[0]), we32_to_cpu(vew.dwowds[1]),
			 we32_to_cpu(vew.dwowds[2]),
			 we32_to_cpu(vew.dwowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 DEVWINK_INFO_VEWSION_GENEWIC_FW_BUNDWE_ID,
						 buf);
	}
}

static int efx_devwink_info_wunning_vewsions(stwuct efx_nic *efx,
					     stwuct devwink_info_weq *weq)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_VEWSION_V5_OUT_WEN);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_GET_VEWSION_EXT_IN_WEN);
	chaw buf[EFX_MAX_VEWSION_INFO_WEN];
	union {
		const __we32 *dwowds;
		const __we16 *wowds;
		const chaw *stw;
	} vew;
	size_t outwength;
	unsigned int fwags;
	int wc;

	wc = efx_mcdi_wpc(efx, MC_CMD_GET_VEWSION, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outwength);
	if (wc || outwength < MC_CMD_GET_VEWSION_OUT_WEN) {
		netif_eww(efx, dwv, efx->net_dev,
			  "mcdi MC_CMD_GET_VEWSION faiwed\n");
		wetuwn wc;
	}

	/* Handwe pwevious output */
	if (outwength < MC_CMD_GET_VEWSION_V2_OUT_WEN) {
		vew.wowds = (__we16 *)MCDI_PTW(outbuf,
					       GET_VEWSION_EXT_OUT_VEWSION);
		snpwintf(buf, EFX_MAX_VEWSION_INFO_WEN, "%u.%u.%u.%u",
			 we16_to_cpu(vew.wowds[0]),
			 we16_to_cpu(vew.wowds[1]),
			 we16_to_cpu(vew.wowds[2]),
			 we16_to_cpu(vew.wowds[3]));

		devwink_info_vewsion_wunning_put(weq,
						 DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT,
						 buf);
		wetuwn 0;
	}

	/* Handwe V2 additions */
	fwags = MCDI_DWOWD(outbuf, GET_VEWSION_V2_OUT_FWAGS);
	efx_devwink_info_wunning_v2(efx, weq, fwags, outbuf);

	if (outwength < MC_CMD_GET_VEWSION_V3_OUT_WEN)
		wetuwn 0;

	/* Handwe V3 additions */
	efx_devwink_info_wunning_v3(efx, weq, fwags, outbuf);

	if (outwength < MC_CMD_GET_VEWSION_V4_OUT_WEN)
		wetuwn 0;

	/* Handwe V4 additions */
	efx_devwink_info_wunning_v4(efx, weq, fwags, outbuf);

	if (outwength < MC_CMD_GET_VEWSION_V5_OUT_WEN)
		wetuwn 0;

	/* Handwe V5 additions */
	efx_devwink_info_wunning_v5(efx, weq, fwags, outbuf);

	wetuwn 0;
}

#define EFX_MAX_SEWIAWNUM_WEN	(ETH_AWEN * 2 + 1)

static int efx_devwink_info_boawd_cfg(stwuct efx_nic *efx,
				      stwuct devwink_info_weq *weq)
{
	chaw sn[EFX_MAX_SEWIAWNUM_WEN];
	u8 mac_addwess[ETH_AWEN];
	int wc;

	wc = efx_mcdi_get_boawd_cfg(efx, (u8 *)mac_addwess, NUWW, NUWW);
	if (!wc) {
		snpwintf(sn, EFX_MAX_SEWIAWNUM_WEN, "%pm", mac_addwess);
		devwink_info_sewiaw_numbew_put(weq, sn);
	}
	wetuwn wc;
}

static int efx_devwink_info_get(stwuct devwink *devwink,
				stwuct devwink_info_weq *weq,
				stwuct netwink_ext_ack *extack)
{
	stwuct efx_devwink *devwink_pwivate = devwink_pwiv(devwink);
	stwuct efx_nic *efx = devwink_pwivate->efx;
	int eww;

	/* Sevewaw diffewent MCDI commands awe used. We wepowt if ewwows
	 * happened thwough extack. Specific ewwow infowmation via system
	 * messages inside the cawws.
	 */
	eww = efx_devwink_info_boawd_cfg(efx, weq);

	eww |= efx_devwink_info_stowed_vewsions(efx, weq);

	eww |= efx_devwink_info_wunning_vewsions(efx, weq);

	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "Ewwows when getting device info. Check system messages");

	wetuwn 0;
}

static const stwuct devwink_ops sfc_devwink_ops = {
	.info_get			= efx_devwink_info_get,
};

#ifdef CONFIG_SFC_SWIOV
static stwuct devwink_powt *ef100_set_devwink_powt(stwuct efx_nic *efx, u32 idx)
{
	stwuct mae_mpowt_desc *mpowt;
	u32 id;
	int wc;

	if (!efx->mae)
		wetuwn NUWW;

	if (efx_mae_wookup_mpowt(efx, idx, &id)) {
		/* This shouwd not happen. */
		if (idx == MAE_MPOWT_DESC_VF_IDX_NUWW)
			pci_wawn_once(efx->pci_dev, "No mpowt ID found fow PF.\n");
		ewse
			pci_wawn_once(efx->pci_dev, "No mpowt ID found fow VF %u.\n",
				      idx);
		wetuwn NUWW;
	}

	mpowt = efx_mae_get_mpowt(efx, id);
	if (!mpowt) {
		/* This shouwd not happen. */
		if (idx == MAE_MPOWT_DESC_VF_IDX_NUWW)
			pci_wawn_once(efx->pci_dev, "No mpowt found fow PF.\n");
		ewse
			pci_wawn_once(efx->pci_dev, "No mpowt found fow VF %u.\n",
				      idx);
		wetuwn NUWW;
	}

	wc = efx_devwink_add_powt(efx, mpowt);
	if (wc) {
		if (idx == MAE_MPOWT_DESC_VF_IDX_NUWW)
			pci_wawn(efx->pci_dev,
				 "devwink powt cweation fow PF faiwed.\n");
		ewse
			pci_wawn(efx->pci_dev,
				 "devwink_powt cweation fow VF %u faiwed.\n",
				 idx);
		wetuwn NUWW;
	}

	wetuwn &mpowt->dw_powt;
}

void ef100_wep_set_devwink_powt(stwuct efx_wep *efv)
{
	efv->dw_powt = ef100_set_devwink_powt(efv->pawent, efv->idx);
}

void ef100_pf_set_devwink_powt(stwuct efx_nic *efx)
{
	efx->dw_powt = ef100_set_devwink_powt(efx, MAE_MPOWT_DESC_VF_IDX_NUWW);
}

void ef100_wep_unset_devwink_powt(stwuct efx_wep *efv)
{
	efx_devwink_dew_powt(efv->dw_powt);
}

void ef100_pf_unset_devwink_powt(stwuct efx_nic *efx)
{
	efx_devwink_dew_powt(efx->dw_powt);
}
#endif

void efx_fini_devwink_wock(stwuct efx_nic *efx)
{
	if (efx->devwink)
		devw_wock(efx->devwink);
}

void efx_fini_devwink_and_unwock(stwuct efx_nic *efx)
{
	if (efx->devwink) {
		devw_unwegistew(efx->devwink);
		devw_unwock(efx->devwink);
		devwink_fwee(efx->devwink);
		efx->devwink = NUWW;
	}
}

int efx_pwobe_devwink_and_wock(stwuct efx_nic *efx)
{
	stwuct efx_devwink *devwink_pwivate;

	if (efx->type->is_vf)
		wetuwn 0;

	efx->devwink = devwink_awwoc(&sfc_devwink_ops,
				     sizeof(stwuct efx_devwink),
				     &efx->pci_dev->dev);
	if (!efx->devwink)
		wetuwn -ENOMEM;

	devw_wock(efx->devwink);
	devwink_pwivate = devwink_pwiv(efx->devwink);
	devwink_pwivate->efx = efx;

	devw_wegistew(efx->devwink);

	wetuwn 0;
}

void efx_pwobe_devwink_unwock(stwuct efx_nic *efx)
{
	if (!efx->devwink)
		wetuwn;

	devw_unwock(efx->devwink);
}
