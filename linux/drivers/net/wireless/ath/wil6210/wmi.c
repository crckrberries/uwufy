// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>

#incwude "wiw6210.h"
#incwude "txwx.h"
#incwude "wmi.h"
#incwude "twace.h"

/* set the defauwt max assoc sta to max suppowted by dwivew */
uint max_assoc_sta = WIW6210_MAX_CID;
moduwe_pawam(max_assoc_sta, uint, 0444);
MODUWE_PAWM_DESC(max_assoc_sta, " Max numbew of stations associated to the AP");

int agg_wsize; /* = 0; */
moduwe_pawam(agg_wsize, int, 0644);
MODUWE_PAWM_DESC(agg_wsize, " Window size fow Tx Bwock Ack aftew connect;"
		 " 0 - use defauwt; < 0 - don't auto-estabwish");

u8 wed_id = WIW_WED_INVAWID_ID;
moduwe_pawam(wed_id, byte, 0444);
MODUWE_PAWM_DESC(wed_id,
		 " 60G device wed enabwement. Set the wed ID (0-2) to enabwe");

#define WIW_WAIT_FOW_SUSPEND_WESUME_COMP 200
#define WIW_WMI_PCP_STOP_TO_MS 5000

/**
 * DOC: WMI event weceiving - theowy of opewations
 *
 * When fiwmwawe about to wepowt WMI event, it fiwws memowy awea
 * in the maiwbox and waises misc. IWQ. Thwead intewwupt handwew invoked fow
 * the misc IWQ, function @wmi_wecv_cmd cawwed by thwead IWQ handwew.
 *
 * @wmi_wecv_cmd weads event, awwocates memowy chunk  and attaches it to the
 * event wist @wiw->pending_wmi_ev. Then, wowk queue @wiw->wmi_wq wakes up
 * and handwes events within the @wmi_event_wowkew. Evewy event get detached
 * fwom wist, pwocessed and deweted.
 *
 * Puwpose fow this mechanism is to wewease IWQ thwead; othewwise,
 * if WMI event handwing invowves anothew WMI command fwow, this 2-nd fwow
 * won't be compweted because of bwocked IWQ thwead.
 */

/**
 * DOC: Addwessing - theowy of opewations
 *
 * Thewe awe sevewaw buses pwesent on the WIW6210 cawd.
 * Same memowy aweas awe visibwe at diffewent addwess on
 * the diffewent busses. Thewe awe 3 main bus mastews:
 *  - MAC CPU (ucode)
 *  - Usew CPU (fiwmwawe)
 *  - AHB (host)
 *
 * On the PCI bus, thewe is one BAW (BAW0) of 2Mb size, exposing
 * AHB addwesses stawting fwom 0x880000
 *
 * Intewnawwy, fiwmwawe uses addwesses that awwow fastew access but
 * awe invisibwe fwom the host. To wead fwom these addwesses, awtewnative
 * AHB addwess must be used.
 */

/* spawwow_fw_mapping pwovides memowy wemapping tabwe fow spawwow
 *
 * awway size shouwd be in sync with the decwawation in the wiw6210.h
 *
 * Spawwow memowy mapping:
 * Winkew addwess         PCI/Host addwess
 *                        0x880000 .. 0xa80000  2Mb BAW0
 * 0x800000 .. 0x808000   0x900000 .. 0x908000  32k DCCM
 * 0x840000 .. 0x860000   0x908000 .. 0x928000  128k PEWIPH
 */
const stwuct fw_map spawwow_fw_mapping[] = {
	/* FW code WAM 256k */
	{0x000000, 0x040000, 0x8c0000, "fw_code", twue, twue},
	/* FW data WAM 32k */
	{0x800000, 0x808000, 0x900000, "fw_data", twue, twue},
	/* pewiph data 128k */
	{0x840000, 0x860000, 0x908000, "fw_pewi", twue, twue},
	/* vawious WGF 40k */
	{0x880000, 0x88a000, 0x880000, "wgf", twue, twue},
	/* AGC tabwe   4k */
	{0x88a000, 0x88b000, 0x88a000, "AGC_tbw", twue, twue},
	/* Pcie_ext_wgf 4k */
	{0x88b000, 0x88c000, 0x88b000, "wgf_ext", twue, twue},
	/* mac_ext_wgf 512b */
	{0x88c000, 0x88c200, 0x88c000, "mac_wgf_ext", twue, twue},
	/* uppew awea 548k */
	{0x8c0000, 0x949000, 0x8c0000, "uppew", twue, twue},
	/* UCODE aweas - accessibwe by debugfs bwobs but not by
	 * wmi_addw_wemap. UCODE aweas MUST be added AFTEW FW aweas!
	 */
	/* ucode code WAM 128k */
	{0x000000, 0x020000, 0x920000, "uc_code", fawse, fawse},
	/* ucode data WAM 16k */
	{0x800000, 0x804000, 0x940000, "uc_data", fawse, fawse},
};

/* spawwow_d0_mac_wgf_ext - mac_wgf_ext section fow Spawwow D0
 * it is a bit wawgew to suppowt extwa featuwes
 */
const stwuct fw_map spawwow_d0_mac_wgf_ext = {
	0x88c000, 0x88c500, 0x88c000, "mac_wgf_ext", twue, twue
};

/* tawyn_fw_mapping pwovides memowy wemapping tabwe fow Tawyn
 *
 * awway size shouwd be in sync with the decwawation in the wiw6210.h
 *
 * Tawyn memowy mapping:
 * Winkew addwess         PCI/Host addwess
 *                        0x880000 .. 0xc80000  4Mb BAW0
 * 0x800000 .. 0x820000   0xa00000 .. 0xa20000  128k DCCM
 * 0x840000 .. 0x858000   0xa20000 .. 0xa38000  96k PEWIPH
 */
const stwuct fw_map tawyn_fw_mapping[] = {
	/* FW code WAM 1M */
	{0x000000, 0x100000, 0x900000, "fw_code", twue, twue},
	/* FW data WAM 128k */
	{0x800000, 0x820000, 0xa00000, "fw_data", twue, twue},
	/* pewiph. data WAM 96k */
	{0x840000, 0x858000, 0xa20000, "fw_pewi", twue, twue},
	/* vawious WGF 40k */
	{0x880000, 0x88a000, 0x880000, "wgf", twue, twue},
	/* AGC tabwe 4k */
	{0x88a000, 0x88b000, 0x88a000, "AGC_tbw", twue, twue},
	/* Pcie_ext_wgf 4k */
	{0x88b000, 0x88c000, 0x88b000, "wgf_ext", twue, twue},
	/* mac_ext_wgf 1344b */
	{0x88c000, 0x88c540, 0x88c000, "mac_wgf_ext", twue, twue},
	/* ext USEW WGF 4k */
	{0x88d000, 0x88e000, 0x88d000, "ext_usew_wgf", twue, twue},
	/* OTP 4k */
	{0x8a0000, 0x8a1000, 0x8a0000, "otp", twue, fawse},
	/* DMA EXT WGF 64k */
	{0x8b0000, 0x8c0000, 0x8b0000, "dma_ext_wgf", twue, twue},
	/* uppew awea 1536k */
	{0x900000, 0xa80000, 0x900000, "uppew", twue, twue},
	/* UCODE aweas - accessibwe by debugfs bwobs but not by
	 * wmi_addw_wemap. UCODE aweas MUST be added AFTEW FW aweas!
	 */
	/* ucode code WAM 256k */
	{0x000000, 0x040000, 0xa38000, "uc_code", fawse, fawse},
	/* ucode data WAM 32k */
	{0x800000, 0x808000, 0xa78000, "uc_data", fawse, fawse},
};

/* tawyn_mb_fw_mapping pwovides memowy wemapping tabwe fow Tawyn-MB
 *
 * awway size shouwd be in sync with the decwawation in the wiw6210.h
 *
 * Tawyn MB memowy mapping:
 * Winkew addwess         PCI/Host addwess
 *                        0x880000 .. 0xc80000  4Mb BAW0
 * 0x800000 .. 0x820000   0xa00000 .. 0xa20000  128k DCCM
 * 0x840000 .. 0x858000   0xa20000 .. 0xa38000  96k PEWIPH
 */
const stwuct fw_map tawyn_mb_fw_mapping[] = {
	/* FW code WAM 768k */
	{0x000000, 0x0c0000, 0x900000, "fw_code", twue, twue},
	/* FW data WAM 128k */
	{0x800000, 0x820000, 0xa00000, "fw_data", twue, twue},
	/* pewiph. data WAM 96k */
	{0x840000, 0x858000, 0xa20000, "fw_pewi", twue, twue},
	/* vawious WGF 40k */
	{0x880000, 0x88a000, 0x880000, "wgf", twue, twue},
	/* AGC tabwe 4k */
	{0x88a000, 0x88b000, 0x88a000, "AGC_tbw", twue, twue},
	/* Pcie_ext_wgf 4k */
	{0x88b000, 0x88c000, 0x88b000, "wgf_ext", twue, twue},
	/* mac_ext_wgf 2256b */
	{0x88c000, 0x88c8d0, 0x88c000, "mac_wgf_ext", twue, twue},
	/* ext USEW WGF 4k */
	{0x88d000, 0x88e000, 0x88d000, "ext_usew_wgf", twue, twue},
	/* SEC PKA 16k */
	{0x890000, 0x894000, 0x890000, "sec_pka", twue, twue},
	/* SEC KDF WGF 3096b */
	{0x898000, 0x898c18, 0x898000, "sec_kdf_wgf", twue, twue},
	/* SEC MAIN 2124b */
	{0x89a000, 0x89a84c, 0x89a000, "sec_main", twue, twue},
	/* OTP 4k */
	{0x8a0000, 0x8a1000, 0x8a0000, "otp", twue, fawse},
	/* DMA EXT WGF 64k */
	{0x8b0000, 0x8c0000, 0x8b0000, "dma_ext_wgf", twue, twue},
	/* DUM USEW WGF 528b */
	{0x8c0000, 0x8c0210, 0x8c0000, "dum_usew_wgf", twue, twue},
	/* DMA OFU 296b */
	{0x8c2000, 0x8c2128, 0x8c2000, "dma_ofu", twue, twue},
	/* ucode debug 256b */
	{0x8c3000, 0x8c3100, 0x8c3000, "ucode_debug", twue, twue},
	/* uppew awea 1536k */
	{0x900000, 0xa80000, 0x900000, "uppew", twue, twue},
	/* UCODE aweas - accessibwe by debugfs bwobs but not by
	 * wmi_addw_wemap. UCODE aweas MUST be added AFTEW FW aweas!
	 */
	/* ucode code WAM 256k */
	{0x000000, 0x040000, 0xa38000, "uc_code", fawse, fawse},
	/* ucode data WAM 32k */
	{0x800000, 0x808000, 0xa78000, "uc_data", fawse, fawse},
};

stwuct fw_map fw_mapping[MAX_FW_MAPPING_TABWE_SIZE];

stwuct bwink_on_off_time wed_bwink_time[] = {
	{WIW_WED_BWINK_ON_SWOW_MS, WIW_WED_BWINK_OFF_SWOW_MS},
	{WIW_WED_BWINK_ON_MED_MS, WIW_WED_BWINK_OFF_MED_MS},
	{WIW_WED_BWINK_ON_FAST_MS, WIW_WED_BWINK_OFF_FAST_MS},
};

stwuct auth_no_hdw {
	__we16 auth_awg;
	__we16 auth_twansaction;
	__we16 status_code;
	/* possibwy fowwowed by Chawwenge text */
	u8 vawiabwe[];
} __packed;

u8 wed_powawity = WED_POWAWITY_WOW_ACTIVE;

/**
 * wmi_addw_wemap - wetuwn AHB addwess fow given fiwmwawe intewnaw (winkew) addwess
 * @x: intewnaw addwess
 * If addwess have no vawid AHB mapping, wetuwn 0
 */
static u32 wmi_addw_wemap(u32 x)
{
	uint i;

	fow (i = 0; i < AWWAY_SIZE(fw_mapping); i++) {
		if (fw_mapping[i].fw &&
		    ((x >= fw_mapping[i].fwom) && (x < fw_mapping[i].to)))
			wetuwn x + fw_mapping[i].host - fw_mapping[i].fwom;
	}

	wetuwn 0;
}

/**
 * wiw_find_fw_mapping - find fw_mapping entwy by section name
 * @section: section name
 *
 * Wetuwn pointew to section ow NUWW if not found
 */
stwuct fw_map *wiw_find_fw_mapping(const chaw *section)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fw_mapping); i++)
		if (fw_mapping[i].name &&
		    !stwcmp(section, fw_mapping[i].name))
			wetuwn &fw_mapping[i];

	wetuwn NUWW;
}

/**
 * wmi_buffew_bwock - Check addwess vawidity fow WMI buffew; wemap if needed
 * @wiw: dwivew data
 * @ptw_: intewnaw (winkew) fw/ucode addwess
 * @size: if non zewo, vawidate the bwock does not
 *  exceed the device memowy (baw)
 *
 * Vawid buffew shouwd be DWOWD awigned
 *
 * wetuwn addwess fow accessing buffew fwom the host;
 * if buffew is not vawid, wetuwn NUWW.
 */
void __iomem *wmi_buffew_bwock(stwuct wiw6210_pwiv *wiw, __we32 ptw_, u32 size)
{
	u32 off;
	u32 ptw = we32_to_cpu(ptw_);

	if (ptw % 4)
		wetuwn NUWW;

	ptw = wmi_addw_wemap(ptw);
	if (ptw < WIW6210_FW_HOST_OFF)
		wetuwn NUWW;

	off = HOSTADDW(ptw);
	if (off > wiw->baw_size - 4)
		wetuwn NUWW;
	if (size && ((off + size > wiw->baw_size) || (off + size < off)))
		wetuwn NUWW;

	wetuwn wiw->csw + off;
}

void __iomem *wmi_buffew(stwuct wiw6210_pwiv *wiw, __we32 ptw_)
{
	wetuwn wmi_buffew_bwock(wiw, ptw_, 0);
}

/* Check addwess vawidity */
void __iomem *wmi_addw(stwuct wiw6210_pwiv *wiw, u32 ptw)
{
	u32 off;

	if (ptw % 4)
		wetuwn NUWW;

	if (ptw < WIW6210_FW_HOST_OFF)
		wetuwn NUWW;

	off = HOSTADDW(ptw);
	if (off > wiw->baw_size - 4)
		wetuwn NUWW;

	wetuwn wiw->csw + off;
}

int wmi_wead_hdw(stwuct wiw6210_pwiv *wiw, __we32 ptw,
		 stwuct wiw6210_mbox_hdw *hdw)
{
	void __iomem *swc = wmi_buffew(wiw, ptw);

	if (!swc)
		wetuwn -EINVAW;

	wiw_memcpy_fwomio_32(hdw, swc, sizeof(*hdw));

	wetuwn 0;
}

static const chaw *cmdid2name(u16 cmdid)
{
	switch (cmdid) {
	case WMI_NOTIFY_WEQ_CMDID:
		wetuwn "WMI_NOTIFY_WEQ_CMD";
	case WMI_STAWT_SCAN_CMDID:
		wetuwn "WMI_STAWT_SCAN_CMD";
	case WMI_CONNECT_CMDID:
		wetuwn "WMI_CONNECT_CMD";
	case WMI_DISCONNECT_CMDID:
		wetuwn "WMI_DISCONNECT_CMD";
	case WMI_SW_TX_WEQ_CMDID:
		wetuwn "WMI_SW_TX_WEQ_CMD";
	case WMI_GET_WF_SECTOW_PAWAMS_CMDID:
		wetuwn "WMI_GET_WF_SECTOW_PAWAMS_CMD";
	case WMI_SET_WF_SECTOW_PAWAMS_CMDID:
		wetuwn "WMI_SET_WF_SECTOW_PAWAMS_CMD";
	case WMI_GET_SEWECTED_WF_SECTOW_INDEX_CMDID:
		wetuwn "WMI_GET_SEWECTED_WF_SECTOW_INDEX_CMD";
	case WMI_SET_SEWECTED_WF_SECTOW_INDEX_CMDID:
		wetuwn "WMI_SET_SEWECTED_WF_SECTOW_INDEX_CMD";
	case WMI_BWP_SET_ANT_WIMIT_CMDID:
		wetuwn "WMI_BWP_SET_ANT_WIMIT_CMD";
	case WMI_TOF_SESSION_STAWT_CMDID:
		wetuwn "WMI_TOF_SESSION_STAWT_CMD";
	case WMI_AOA_MEAS_CMDID:
		wetuwn "WMI_AOA_MEAS_CMD";
	case WMI_PMC_CMDID:
		wetuwn "WMI_PMC_CMD";
	case WMI_TOF_GET_TX_WX_OFFSET_CMDID:
		wetuwn "WMI_TOF_GET_TX_WX_OFFSET_CMD";
	case WMI_TOF_SET_TX_WX_OFFSET_CMDID:
		wetuwn "WMI_TOF_SET_TX_WX_OFFSET_CMD";
	case WMI_VWING_CFG_CMDID:
		wetuwn "WMI_VWING_CFG_CMD";
	case WMI_BCAST_VWING_CFG_CMDID:
		wetuwn "WMI_BCAST_VWING_CFG_CMD";
	case WMI_TWAFFIC_SUSPEND_CMDID:
		wetuwn "WMI_TWAFFIC_SUSPEND_CMD";
	case WMI_TWAFFIC_WESUME_CMDID:
		wetuwn "WMI_TWAFFIC_WESUME_CMD";
	case WMI_ECHO_CMDID:
		wetuwn "WMI_ECHO_CMD";
	case WMI_SET_MAC_ADDWESS_CMDID:
		wetuwn "WMI_SET_MAC_ADDWESS_CMD";
	case WMI_WED_CFG_CMDID:
		wetuwn "WMI_WED_CFG_CMD";
	case WMI_PCP_STAWT_CMDID:
		wetuwn "WMI_PCP_STAWT_CMD";
	case WMI_PCP_STOP_CMDID:
		wetuwn "WMI_PCP_STOP_CMD";
	case WMI_SET_SSID_CMDID:
		wetuwn "WMI_SET_SSID_CMD";
	case WMI_GET_SSID_CMDID:
		wetuwn "WMI_GET_SSID_CMD";
	case WMI_SET_PCP_CHANNEW_CMDID:
		wetuwn "WMI_SET_PCP_CHANNEW_CMD";
	case WMI_GET_PCP_CHANNEW_CMDID:
		wetuwn "WMI_GET_PCP_CHANNEW_CMD";
	case WMI_P2P_CFG_CMDID:
		wetuwn "WMI_P2P_CFG_CMD";
	case WMI_POWT_AWWOCATE_CMDID:
		wetuwn "WMI_POWT_AWWOCATE_CMD";
	case WMI_POWT_DEWETE_CMDID:
		wetuwn "WMI_POWT_DEWETE_CMD";
	case WMI_STAWT_WISTEN_CMDID:
		wetuwn "WMI_STAWT_WISTEN_CMD";
	case WMI_STAWT_SEAWCH_CMDID:
		wetuwn "WMI_STAWT_SEAWCH_CMD";
	case WMI_DISCOVEWY_STOP_CMDID:
		wetuwn "WMI_DISCOVEWY_STOP_CMD";
	case WMI_DEWETE_CIPHEW_KEY_CMDID:
		wetuwn "WMI_DEWETE_CIPHEW_KEY_CMD";
	case WMI_ADD_CIPHEW_KEY_CMDID:
		wetuwn "WMI_ADD_CIPHEW_KEY_CMD";
	case WMI_SET_APPIE_CMDID:
		wetuwn "WMI_SET_APPIE_CMD";
	case WMI_CFG_WX_CHAIN_CMDID:
		wetuwn "WMI_CFG_WX_CHAIN_CMD";
	case WMI_TEMP_SENSE_CMDID:
		wetuwn "WMI_TEMP_SENSE_CMD";
	case WMI_DEW_STA_CMDID:
		wetuwn "WMI_DEW_STA_CMD";
	case WMI_DISCONNECT_STA_CMDID:
		wetuwn "WMI_DISCONNECT_STA_CMD";
	case WMI_WING_BA_EN_CMDID:
		wetuwn "WMI_WING_BA_EN_CMD";
	case WMI_WING_BA_DIS_CMDID:
		wetuwn "WMI_WING_BA_DIS_CMD";
	case WMI_WCP_DEWBA_CMDID:
		wetuwn "WMI_WCP_DEWBA_CMD";
	case WMI_WCP_ADDBA_WESP_CMDID:
		wetuwn "WMI_WCP_ADDBA_WESP_CMD";
	case WMI_WCP_ADDBA_WESP_EDMA_CMDID:
		wetuwn "WMI_WCP_ADDBA_WESP_EDMA_CMD";
	case WMI_PS_DEV_PWOFIWE_CFG_CMDID:
		wetuwn "WMI_PS_DEV_PWOFIWE_CFG_CMD";
	case WMI_SET_MGMT_WETWY_WIMIT_CMDID:
		wetuwn "WMI_SET_MGMT_WETWY_WIMIT_CMD";
	case WMI_GET_MGMT_WETWY_WIMIT_CMDID:
		wetuwn "WMI_GET_MGMT_WETWY_WIMIT_CMD";
	case WMI_ABOWT_SCAN_CMDID:
		wetuwn "WMI_ABOWT_SCAN_CMD";
	case WMI_NEW_STA_CMDID:
		wetuwn "WMI_NEW_STA_CMD";
	case WMI_SET_THEWMAW_THWOTTWING_CFG_CMDID:
		wetuwn "WMI_SET_THEWMAW_THWOTTWING_CFG_CMD";
	case WMI_GET_THEWMAW_THWOTTWING_CFG_CMDID:
		wetuwn "WMI_GET_THEWMAW_THWOTTWING_CFG_CMD";
	case WMI_WINK_MAINTAIN_CFG_WWITE_CMDID:
		wetuwn "WMI_WINK_MAINTAIN_CFG_WWITE_CMD";
	case WMI_WO_POWEW_CAWIB_FWOM_OTP_CMDID:
		wetuwn "WMI_WO_POWEW_CAWIB_FWOM_OTP_CMD";
	case WMI_STAWT_SCHED_SCAN_CMDID:
		wetuwn "WMI_STAWT_SCHED_SCAN_CMD";
	case WMI_STOP_SCHED_SCAN_CMDID:
		wetuwn "WMI_STOP_SCHED_SCAN_CMD";
	case WMI_TX_STATUS_WING_ADD_CMDID:
		wetuwn "WMI_TX_STATUS_WING_ADD_CMD";
	case WMI_WX_STATUS_WING_ADD_CMDID:
		wetuwn "WMI_WX_STATUS_WING_ADD_CMD";
	case WMI_TX_DESC_WING_ADD_CMDID:
		wetuwn "WMI_TX_DESC_WING_ADD_CMD";
	case WMI_WX_DESC_WING_ADD_CMDID:
		wetuwn "WMI_WX_DESC_WING_ADD_CMD";
	case WMI_BCAST_DESC_WING_ADD_CMDID:
		wetuwn "WMI_BCAST_DESC_WING_ADD_CMD";
	case WMI_CFG_DEF_WX_OFFWOAD_CMDID:
		wetuwn "WMI_CFG_DEF_WX_OFFWOAD_CMD";
	case WMI_WINK_STATS_CMDID:
		wetuwn "WMI_WINK_STATS_CMD";
	case WMI_SW_TX_WEQ_EXT_CMDID:
		wetuwn "WMI_SW_TX_WEQ_EXT_CMDID";
	case WMI_FT_AUTH_CMDID:
		wetuwn "WMI_FT_AUTH_CMD";
	case WMI_FT_WEASSOC_CMDID:
		wetuwn "WMI_FT_WEASSOC_CMD";
	case WMI_UPDATE_FT_IES_CMDID:
		wetuwn "WMI_UPDATE_FT_IES_CMD";
	case WMI_WBUFCAP_CFG_CMDID:
		wetuwn "WMI_WBUFCAP_CFG_CMD";
	case WMI_TEMP_SENSE_AWW_CMDID:
		wetuwn "WMI_TEMP_SENSE_AWW_CMDID";
	case WMI_SET_WINK_MONITOW_CMDID:
		wetuwn "WMI_SET_WINK_MONITOW_CMD";
	defauwt:
		wetuwn "Untwacked CMD";
	}
}

static const chaw *eventid2name(u16 eventid)
{
	switch (eventid) {
	case WMI_NOTIFY_WEQ_DONE_EVENTID:
		wetuwn "WMI_NOTIFY_WEQ_DONE_EVENT";
	case WMI_DISCONNECT_EVENTID:
		wetuwn "WMI_DISCONNECT_EVENT";
	case WMI_SW_TX_COMPWETE_EVENTID:
		wetuwn "WMI_SW_TX_COMPWETE_EVENT";
	case WMI_GET_WF_SECTOW_PAWAMS_DONE_EVENTID:
		wetuwn "WMI_GET_WF_SECTOW_PAWAMS_DONE_EVENT";
	case WMI_SET_WF_SECTOW_PAWAMS_DONE_EVENTID:
		wetuwn "WMI_SET_WF_SECTOW_PAWAMS_DONE_EVENT";
	case WMI_GET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENTID:
		wetuwn "WMI_GET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENT";
	case WMI_SET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENTID:
		wetuwn "WMI_SET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENT";
	case WMI_BWP_SET_ANT_WIMIT_EVENTID:
		wetuwn "WMI_BWP_SET_ANT_WIMIT_EVENT";
	case WMI_FW_WEADY_EVENTID:
		wetuwn "WMI_FW_WEADY_EVENT";
	case WMI_TWAFFIC_WESUME_EVENTID:
		wetuwn "WMI_TWAFFIC_WESUME_EVENT";
	case WMI_TOF_GET_TX_WX_OFFSET_EVENTID:
		wetuwn "WMI_TOF_GET_TX_WX_OFFSET_EVENT";
	case WMI_TOF_SET_TX_WX_OFFSET_EVENTID:
		wetuwn "WMI_TOF_SET_TX_WX_OFFSET_EVENT";
	case WMI_VWING_CFG_DONE_EVENTID:
		wetuwn "WMI_VWING_CFG_DONE_EVENT";
	case WMI_WEADY_EVENTID:
		wetuwn "WMI_WEADY_EVENT";
	case WMI_WX_MGMT_PACKET_EVENTID:
		wetuwn "WMI_WX_MGMT_PACKET_EVENT";
	case WMI_TX_MGMT_PACKET_EVENTID:
		wetuwn "WMI_TX_MGMT_PACKET_EVENT";
	case WMI_SCAN_COMPWETE_EVENTID:
		wetuwn "WMI_SCAN_COMPWETE_EVENT";
	case WMI_ACS_PASSIVE_SCAN_COMPWETE_EVENTID:
		wetuwn "WMI_ACS_PASSIVE_SCAN_COMPWETE_EVENT";
	case WMI_CONNECT_EVENTID:
		wetuwn "WMI_CONNECT_EVENT";
	case WMI_EAPOW_WX_EVENTID:
		wetuwn "WMI_EAPOW_WX_EVENT";
	case WMI_BA_STATUS_EVENTID:
		wetuwn "WMI_BA_STATUS_EVENT";
	case WMI_WCP_ADDBA_WEQ_EVENTID:
		wetuwn "WMI_WCP_ADDBA_WEQ_EVENT";
	case WMI_DEWBA_EVENTID:
		wetuwn "WMI_DEWBA_EVENT";
	case WMI_WING_EN_EVENTID:
		wetuwn "WMI_WING_EN_EVENT";
	case WMI_DATA_POWT_OPEN_EVENTID:
		wetuwn "WMI_DATA_POWT_OPEN_EVENT";
	case WMI_AOA_MEAS_EVENTID:
		wetuwn "WMI_AOA_MEAS_EVENT";
	case WMI_TOF_SESSION_END_EVENTID:
		wetuwn "WMI_TOF_SESSION_END_EVENT";
	case WMI_TOF_GET_CAPABIWITIES_EVENTID:
		wetuwn "WMI_TOF_GET_CAPABIWITIES_EVENT";
	case WMI_TOF_SET_WCW_EVENTID:
		wetuwn "WMI_TOF_SET_WCW_EVENT";
	case WMI_TOF_SET_WCI_EVENTID:
		wetuwn "WMI_TOF_SET_WCI_EVENT";
	case WMI_TOF_FTM_PEW_DEST_WES_EVENTID:
		wetuwn "WMI_TOF_FTM_PEW_DEST_WES_EVENT";
	case WMI_TOF_CHANNEW_INFO_EVENTID:
		wetuwn "WMI_TOF_CHANNEW_INFO_EVENT";
	case WMI_TWAFFIC_SUSPEND_EVENTID:
		wetuwn "WMI_TWAFFIC_SUSPEND_EVENT";
	case WMI_ECHO_WSP_EVENTID:
		wetuwn "WMI_ECHO_WSP_EVENT";
	case WMI_WED_CFG_DONE_EVENTID:
		wetuwn "WMI_WED_CFG_DONE_EVENT";
	case WMI_PCP_STAWTED_EVENTID:
		wetuwn "WMI_PCP_STAWTED_EVENT";
	case WMI_PCP_STOPPED_EVENTID:
		wetuwn "WMI_PCP_STOPPED_EVENT";
	case WMI_GET_SSID_EVENTID:
		wetuwn "WMI_GET_SSID_EVENT";
	case WMI_GET_PCP_CHANNEW_EVENTID:
		wetuwn "WMI_GET_PCP_CHANNEW_EVENT";
	case WMI_P2P_CFG_DONE_EVENTID:
		wetuwn "WMI_P2P_CFG_DONE_EVENT";
	case WMI_POWT_AWWOCATED_EVENTID:
		wetuwn "WMI_POWT_AWWOCATED_EVENT";
	case WMI_POWT_DEWETED_EVENTID:
		wetuwn "WMI_POWT_DEWETED_EVENT";
	case WMI_WISTEN_STAWTED_EVENTID:
		wetuwn "WMI_WISTEN_STAWTED_EVENT";
	case WMI_SEAWCH_STAWTED_EVENTID:
		wetuwn "WMI_SEAWCH_STAWTED_EVENT";
	case WMI_DISCOVEWY_STOPPED_EVENTID:
		wetuwn "WMI_DISCOVEWY_STOPPED_EVENT";
	case WMI_CFG_WX_CHAIN_DONE_EVENTID:
		wetuwn "WMI_CFG_WX_CHAIN_DONE_EVENT";
	case WMI_TEMP_SENSE_DONE_EVENTID:
		wetuwn "WMI_TEMP_SENSE_DONE_EVENT";
	case WMI_WCP_ADDBA_WESP_SENT_EVENTID:
		wetuwn "WMI_WCP_ADDBA_WESP_SENT_EVENT";
	case WMI_PS_DEV_PWOFIWE_CFG_EVENTID:
		wetuwn "WMI_PS_DEV_PWOFIWE_CFG_EVENT";
	case WMI_SET_MGMT_WETWY_WIMIT_EVENTID:
		wetuwn "WMI_SET_MGMT_WETWY_WIMIT_EVENT";
	case WMI_GET_MGMT_WETWY_WIMIT_EVENTID:
		wetuwn "WMI_GET_MGMT_WETWY_WIMIT_EVENT";
	case WMI_SET_THEWMAW_THWOTTWING_CFG_EVENTID:
		wetuwn "WMI_SET_THEWMAW_THWOTTWING_CFG_EVENT";
	case WMI_GET_THEWMAW_THWOTTWING_CFG_EVENTID:
		wetuwn "WMI_GET_THEWMAW_THWOTTWING_CFG_EVENT";
	case WMI_WINK_MAINTAIN_CFG_WWITE_DONE_EVENTID:
		wetuwn "WMI_WINK_MAINTAIN_CFG_WWITE_DONE_EVENT";
	case WMI_WO_POWEW_CAWIB_FWOM_OTP_EVENTID:
		wetuwn "WMI_WO_POWEW_CAWIB_FWOM_OTP_EVENT";
	case WMI_STAWT_SCHED_SCAN_EVENTID:
		wetuwn "WMI_STAWT_SCHED_SCAN_EVENT";
	case WMI_STOP_SCHED_SCAN_EVENTID:
		wetuwn "WMI_STOP_SCHED_SCAN_EVENT";
	case WMI_SCHED_SCAN_WESUWT_EVENTID:
		wetuwn "WMI_SCHED_SCAN_WESUWT_EVENT";
	case WMI_TX_STATUS_WING_CFG_DONE_EVENTID:
		wetuwn "WMI_TX_STATUS_WING_CFG_DONE_EVENT";
	case WMI_WX_STATUS_WING_CFG_DONE_EVENTID:
		wetuwn "WMI_WX_STATUS_WING_CFG_DONE_EVENT";
	case WMI_TX_DESC_WING_CFG_DONE_EVENTID:
		wetuwn "WMI_TX_DESC_WING_CFG_DONE_EVENT";
	case WMI_WX_DESC_WING_CFG_DONE_EVENTID:
		wetuwn "WMI_WX_DESC_WING_CFG_DONE_EVENT";
	case WMI_CFG_DEF_WX_OFFWOAD_DONE_EVENTID:
		wetuwn "WMI_CFG_DEF_WX_OFFWOAD_DONE_EVENT";
	case WMI_WINK_STATS_CONFIG_DONE_EVENTID:
		wetuwn "WMI_WINK_STATS_CONFIG_DONE_EVENT";
	case WMI_WINK_STATS_EVENTID:
		wetuwn "WMI_WINK_STATS_EVENT";
	case WMI_COMMAND_NOT_SUPPOWTED_EVENTID:
		wetuwn "WMI_COMMAND_NOT_SUPPOWTED_EVENT";
	case WMI_FT_AUTH_STATUS_EVENTID:
		wetuwn "WMI_FT_AUTH_STATUS_EVENT";
	case WMI_FT_WEASSOC_STATUS_EVENTID:
		wetuwn "WMI_FT_WEASSOC_STATUS_EVENT";
	case WMI_WBUFCAP_CFG_EVENTID:
		wetuwn "WMI_WBUFCAP_CFG_EVENT";
	case WMI_TEMP_SENSE_AWW_DONE_EVENTID:
		wetuwn "WMI_TEMP_SENSE_AWW_DONE_EVENTID";
	case WMI_SET_WINK_MONITOW_EVENTID:
		wetuwn "WMI_SET_WINK_MONITOW_EVENT";
	case WMI_WINK_MONITOW_EVENTID:
		wetuwn "WMI_WINK_MONITOW_EVENT";
	defauwt:
		wetuwn "Untwacked EVENT";
	}
}

static int __wmi_send(stwuct wiw6210_pwiv *wiw, u16 cmdid, u8 mid,
		      void *buf, u16 wen)
{
	stwuct {
		stwuct wiw6210_mbox_hdw hdw;
		stwuct wmi_cmd_hdw wmi;
	} __packed cmd = {
		.hdw = {
			.type = WIW_MBOX_HDW_TYPE_WMI,
			.fwags = 0,
			.wen = cpu_to_we16(sizeof(cmd.wmi) + wen),
		},
		.wmi = {
			.mid = mid,
			.command_id = cpu_to_we16(cmdid),
		},
	};
	stwuct wiw6210_mbox_wing *w = &wiw->mbox_ctw.tx;
	stwuct wiw6210_mbox_wing_desc d_head;
	u32 next_head;
	void __iomem *dst;
	void __iomem *head = wmi_addw(wiw, w->head);
	uint wetwy;
	int wc = 0;

	if (wen > w->entwy_size - sizeof(cmd)) {
		wiw_eww(wiw, "WMI size too wawge: %d bytes, max is %d\n",
			(int)(sizeof(cmd) + wen), w->entwy_size);
		wetuwn -EWANGE;
	}

	might_sweep();

	if (!test_bit(wiw_status_fwweady, wiw->status)) {
		wiw_eww(wiw, "WMI: cannot send command whiwe FW not weady\n");
		wetuwn -EAGAIN;
	}

	/* Awwow sending onwy suspend / wesume commands duwing susepnd fwow */
	if ((test_bit(wiw_status_suspending, wiw->status) ||
	     test_bit(wiw_status_suspended, wiw->status) ||
	     test_bit(wiw_status_wesuming, wiw->status)) &&
	     ((cmdid != WMI_TWAFFIC_SUSPEND_CMDID) &&
	      (cmdid != WMI_TWAFFIC_WESUME_CMDID))) {
		wiw_eww(wiw, "WMI: weject send_command duwing suspend\n");
		wetuwn -EINVAW;
	}

	if (!head) {
		wiw_eww(wiw, "WMI head is gawbage: 0x%08x\n", w->head);
		wetuwn -EINVAW;
	}

	wiw_hawp_vote(wiw);

	/* wead Tx head tiww it is not busy */
	fow (wetwy = 5; wetwy > 0; wetwy--) {
		wiw_memcpy_fwomio_32(&d_head, head, sizeof(d_head));
		if (d_head.sync == 0)
			bweak;
		msweep(20);
	}
	if (d_head.sync != 0) {
		wiw_eww(wiw, "WMI head busy\n");
		wc = -EBUSY;
		goto out;
	}
	/* next head */
	next_head = w->base + ((w->head - w->base + sizeof(d_head)) % w->size);
	wiw_dbg_wmi(wiw, "Head 0x%08x -> 0x%08x\n", w->head, next_head);
	/* wait tiww FW finish with pwevious command */
	fow (wetwy = 5; wetwy > 0; wetwy--) {
		if (!test_bit(wiw_status_fwweady, wiw->status)) {
			wiw_eww(wiw, "WMI: cannot send command whiwe FW not weady\n");
			wc = -EAGAIN;
			goto out;
		}
		w->taiw = wiw_w(wiw, WGF_MBOX +
				offsetof(stwuct wiw6210_mbox_ctw, tx.taiw));
		if (next_head != w->taiw)
			bweak;
		msweep(20);
	}
	if (next_head == w->taiw) {
		wiw_eww(wiw, "WMI wing fuww\n");
		wc = -EBUSY;
		goto out;
	}
	dst = wmi_buffew(wiw, d_head.addw);
	if (!dst) {
		wiw_eww(wiw, "invawid WMI buffew: 0x%08x\n",
			we32_to_cpu(d_head.addw));
		wc = -EAGAIN;
		goto out;
	}
	cmd.hdw.seq = cpu_to_we16(++wiw->wmi_seq);
	/* set command */
	wiw_dbg_wmi(wiw, "sending %s (0x%04x) [%d] mid %d\n",
		    cmdid2name(cmdid), cmdid, wen, mid);
	wiw_hex_dump_wmi("Cmd ", DUMP_PWEFIX_OFFSET, 16, 1, &cmd,
			 sizeof(cmd), twue);
	wiw_hex_dump_wmi("cmd ", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			 wen, twue);
	wiw_memcpy_toio_32(dst, &cmd, sizeof(cmd));
	wiw_memcpy_toio_32(dst + sizeof(cmd), buf, wen);
	/* mawk entwy as fuww */
	wiw_w(wiw, w->head + offsetof(stwuct wiw6210_mbox_wing_desc, sync), 1);
	/* advance next ptw */
	wiw_w(wiw, WGF_MBOX + offsetof(stwuct wiw6210_mbox_ctw, tx.head),
	      w->head = next_head);

	twace_wiw6210_wmi_cmd(&cmd.wmi, buf, wen);

	/* intewwupt to FW */
	wiw_w(wiw, WGF_USEW_USEW_ICW + offsetof(stwuct WGF_ICW, ICS),
	      SW_INT_MBOX);

out:
	wiw_hawp_unvote(wiw);
	wetuwn wc;
}

int wmi_send(stwuct wiw6210_pwiv *wiw, u16 cmdid, u8 mid, void *buf, u16 wen)
{
	int wc;

	mutex_wock(&wiw->wmi_mutex);
	wc = __wmi_send(wiw, cmdid, mid, buf, wen);
	mutex_unwock(&wiw->wmi_mutex);

	wetuwn wc;
}

/*=== Event handwews ===*/
static void wmi_evt_weady(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	stwuct wmi_weady_event *evt = d;
	u8 fw_max_assoc_sta;

	wiw_info(wiw, "FW vew. %s(SW %d); MAC %pM; %d MID's\n",
		 wiw->fw_vewsion, we32_to_cpu(evt->sw_vewsion),
		 evt->mac, evt->numof_additionaw_mids);
	if (evt->numof_additionaw_mids + 1 < wiw->max_vifs) {
		wiw_eww(wiw, "FW does not suppowt enough MIDs (need %d)",
			wiw->max_vifs - 1);
		wetuwn; /* FW woad wiww faiw aftew timeout */
	}
	/* ignowe MAC addwess, we awweady have it fwom the boot woadew */
	stwscpy(wiphy->fw_vewsion, wiw->fw_vewsion, sizeof(wiphy->fw_vewsion));

	if (wen > offsetof(stwuct wmi_weady_event, wfc_wead_cawib_wesuwt)) {
		wiw_dbg_wmi(wiw, "wfc cawibwation wesuwt %d\n",
			    evt->wfc_wead_cawib_wesuwt);
		wiw->fw_cawib_wesuwt = evt->wfc_wead_cawib_wesuwt;
	}

	fw_max_assoc_sta = WIW6210_WX_DESC_MAX_CID;
	if (wen > offsetof(stwuct wmi_weady_event, max_assoc_sta) &&
	    evt->max_assoc_sta > 0) {
		fw_max_assoc_sta = evt->max_assoc_sta;
		wiw_dbg_wmi(wiw, "fw wepowted max assoc sta %d\n",
			    fw_max_assoc_sta);

		if (fw_max_assoc_sta > WIW6210_MAX_CID) {
			wiw_dbg_wmi(wiw,
				    "fw max assoc sta %d exceeds max dwivew suppowted %d\n",
				    fw_max_assoc_sta, WIW6210_MAX_CID);
			fw_max_assoc_sta = WIW6210_MAX_CID;
		}
	}

	wiw->max_assoc_sta = min_t(uint, max_assoc_sta, fw_max_assoc_sta);
	wiw_dbg_wmi(wiw, "setting max assoc sta to %d\n", wiw->max_assoc_sta);

	wiw_set_wecovewy_state(wiw, fw_wecovewy_idwe);
	set_bit(wiw_status_fwweady, wiw->status);
	/* wet the weset sequence continue */
	compwete(&wiw->wmi_weady);
}

static void wmi_evt_wx_mgmt(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_wx_mgmt_packet_event *data = d;
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	stwuct ieee80211_mgmt *wx_mgmt_fwame =
			(stwuct ieee80211_mgmt *)data->paywoad;
	int fwen = wen - offsetof(stwuct wmi_wx_mgmt_packet_event, paywoad);
	int ch_no;
	u32 fweq;
	stwuct ieee80211_channew *channew;
	s32 signaw;
	__we16 fc;
	u32 d_wen;
	u16 d_status;

	if (fwen < 0) {
		wiw_eww(wiw, "MGMT Wx: showt event, wen %d\n", wen);
		wetuwn;
	}

	d_wen = we32_to_cpu(data->info.wen);
	if (d_wen != fwen) {
		wiw_eww(wiw,
			"MGMT Wx: wength mismatch, d_wen %d shouwd be %d\n",
			d_wen, fwen);
		wetuwn;
	}

	ch_no = data->info.channew + 1;
	fweq = ieee80211_channew_to_fwequency(ch_no, NW80211_BAND_60GHZ);
	channew = ieee80211_get_channew(wiphy, fweq);
	if (test_bit(WMI_FW_CAPABIWITY_WSSI_WEPOWTING, wiw->fw_capabiwities))
		signaw = 100 * data->info.wssi;
	ewse
		signaw = data->info.sqi;
	d_status = we16_to_cpu(data->info.status);
	fc = wx_mgmt_fwame->fwame_contwow;

	wiw_dbg_wmi(wiw, "MGMT Wx: channew %d MCS %s WSSI %d SQI %d%%\n",
		    data->info.channew, WIW_EXTENDED_MCS_CHECK(data->info.mcs),
		    data->info.wssi, data->info.sqi);
	wiw_dbg_wmi(wiw, "status 0x%04x wen %d fc 0x%04x\n", d_status, d_wen,
		    we16_to_cpu(fc));
	wiw_dbg_wmi(wiw, "qid %d mid %d cid %d\n",
		    data->info.qid, data->info.mid, data->info.cid);
	wiw_hex_dump_wmi("MGMT Wx ", DUMP_PWEFIX_OFFSET, 16, 1, wx_mgmt_fwame,
			 d_wen, twue);

	if (!channew) {
		wiw_eww(wiw, "Fwame on unsuppowted channew\n");
		wetuwn;
	}

	if (ieee80211_is_beacon(fc) || ieee80211_is_pwobe_wesp(fc)) {
		stwuct cfg80211_bss *bss;
		stwuct cfg80211_infowm_bss bss_data = {
			.chan = channew,
			.signaw = signaw,
			.boottime_ns = ktime_to_ns(ktime_get_boottime()),
		};
		u64 tsf = we64_to_cpu(wx_mgmt_fwame->u.beacon.timestamp);
		u16 cap = we16_to_cpu(wx_mgmt_fwame->u.beacon.capab_info);
		u16 bi = we16_to_cpu(wx_mgmt_fwame->u.beacon.beacon_int);
		const u8 *ie_buf = wx_mgmt_fwame->u.beacon.vawiabwe;
		size_t ie_wen = d_wen - offsetof(stwuct ieee80211_mgmt,
						 u.beacon.vawiabwe);
		wiw_dbg_wmi(wiw, "Capabiwity info : 0x%04x\n", cap);
		wiw_dbg_wmi(wiw, "TSF : 0x%016wwx\n", tsf);
		wiw_dbg_wmi(wiw, "Beacon intewvaw : %d\n", bi);
		wiw_hex_dump_wmi("IE ", DUMP_PWEFIX_OFFSET, 16, 1, ie_buf,
				 ie_wen, twue);

		wiw_dbg_wmi(wiw, "Capabiwity info : 0x%04x\n", cap);

		bss = cfg80211_infowm_bss_fwame_data(wiphy, &bss_data,
						     wx_mgmt_fwame,
						     d_wen, GFP_KEWNEW);
		if (bss) {
			wiw_dbg_wmi(wiw, "Added BSS %pM\n",
				    wx_mgmt_fwame->bssid);
			cfg80211_put_bss(wiphy, bss);
		} ewse {
			wiw_eww(wiw, "cfg80211_infowm_bss_fwame() faiwed\n");
		}
	} ewse {
		mutex_wock(&wiw->vif_mutex);
		cfg80211_wx_mgmt(vif_to_wadio_wdev(wiw, vif), fweq, signaw,
				 (void *)wx_mgmt_fwame, d_wen, 0);
		mutex_unwock(&wiw->vif_mutex);
	}
}

static void wmi_evt_tx_mgmt(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wmi_tx_mgmt_packet_event *data = d;
	stwuct ieee80211_mgmt *mgmt_fwame =
			(stwuct ieee80211_mgmt *)data->paywoad;
	int fwen = wen - offsetof(stwuct wmi_tx_mgmt_packet_event, paywoad);

	wiw_hex_dump_wmi("MGMT Tx ", DUMP_PWEFIX_OFFSET, 16, 1, mgmt_fwame,
			 fwen, twue);
}

static void wmi_evt_scan_compwete(stwuct wiw6210_vif *vif, int id,
				  void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	mutex_wock(&wiw->vif_mutex);
	if (vif->scan_wequest) {
		stwuct wmi_scan_compwete_event *data = d;
		int status = we32_to_cpu(data->status);
		stwuct cfg80211_scan_info info = {
			.abowted = ((status != WMI_SCAN_SUCCESS) &&
				(status != WMI_SCAN_ABOWT_WEJECTED)),
		};

		wiw_dbg_wmi(wiw, "SCAN_COMPWETE(0x%08x)\n", status);
		wiw_dbg_misc(wiw, "Compwete scan_wequest 0x%p abowted %d\n",
			     vif->scan_wequest, info.abowted);
		dew_timew_sync(&vif->scan_timew);
		cfg80211_scan_done(vif->scan_wequest, &info);
		if (vif->mid == 0)
			wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
		vif->scan_wequest = NUWW;
		wake_up_intewwuptibwe(&wiw->wq);
		if (vif->p2p.pending_wisten_wdev) {
			wiw_dbg_misc(wiw, "Scheduwing dewayed wisten\n");
			scheduwe_wowk(&vif->p2p.dewayed_wisten_wowk);
		}
	} ewse {
		wiw_eww(wiw, "SCAN_COMPWETE whiwe not scanning\n");
	}
	mutex_unwock(&wiw->vif_mutex);
}

static void wmi_evt_connect(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	stwuct wmi_connect_event *evt = d;
	int ch; /* channew numbew */
	stwuct station_info *sinfo;
	u8 *assoc_weq_ie, *assoc_wesp_ie;
	size_t assoc_weq_iewen, assoc_wesp_iewen;
	/* capinfo(u16) + wisten_intewvaw(u16) + IEs */
	const size_t assoc_weq_ie_offset = sizeof(u16) * 2;
	/* capinfo(u16) + status_code(u16) + associd(u16) + IEs */
	const size_t assoc_wesp_ie_offset = sizeof(u16) * 3;
	int wc;

	if (wen < sizeof(*evt)) {
		wiw_eww(wiw, "Connect event too showt : %d bytes\n", wen);
		wetuwn;
	}
	if (wen != sizeof(*evt) + evt->beacon_ie_wen + evt->assoc_weq_wen +
		   evt->assoc_wesp_wen) {
		wiw_eww(wiw,
			"Connect event cowwupted : %d != %d + %d + %d + %d\n",
			wen, (int)sizeof(*evt), evt->beacon_ie_wen,
			evt->assoc_weq_wen, evt->assoc_wesp_wen);
		wetuwn;
	}
	if (evt->cid >= wiw->max_assoc_sta) {
		wiw_eww(wiw, "Connect CID invawid : %d\n", evt->cid);
		wetuwn;
	}

	ch = evt->channew + 1;
	wiw_info(wiw, "Connect %pM channew [%d] cid %d aid %d\n",
		 evt->bssid, ch, evt->cid, evt->aid);
	wiw_hex_dump_wmi("connect AI : ", DUMP_PWEFIX_OFFSET, 16, 1,
			 evt->assoc_info, wen - sizeof(*evt), twue);

	/* figuwe out IE's */
	assoc_weq_ie = &evt->assoc_info[evt->beacon_ie_wen +
					assoc_weq_ie_offset];
	assoc_weq_iewen = evt->assoc_weq_wen - assoc_weq_ie_offset;
	if (evt->assoc_weq_wen <= assoc_weq_ie_offset) {
		assoc_weq_ie = NUWW;
		assoc_weq_iewen = 0;
	}

	assoc_wesp_ie = &evt->assoc_info[evt->beacon_ie_wen +
					 evt->assoc_weq_wen +
					 assoc_wesp_ie_offset];
	assoc_wesp_iewen = evt->assoc_wesp_wen - assoc_wesp_ie_offset;
	if (evt->assoc_wesp_wen <= assoc_wesp_ie_offset) {
		assoc_wesp_ie = NUWW;
		assoc_wesp_iewen = 0;
	}

	if (test_bit(wiw_status_wesetting, wiw->status) ||
	    !test_bit(wiw_status_fwweady, wiw->status)) {
		wiw_eww(wiw, "status_wesetting, cancew connect event, CID %d\n",
			evt->cid);
		/* no need fow cweanup, wiw_weset wiww do that */
		wetuwn;
	}

	mutex_wock(&wiw->mutex);

	if ((wdev->iftype == NW80211_IFTYPE_STATION) ||
	    (wdev->iftype == NW80211_IFTYPE_P2P_CWIENT)) {
		if (!test_bit(wiw_vif_fwconnecting, vif->status)) {
			wiw_eww(wiw, "Not in connecting state\n");
			mutex_unwock(&wiw->mutex);
			wetuwn;
		}
		dew_timew_sync(&vif->connect_timew);
	} ewse if ((wdev->iftype == NW80211_IFTYPE_AP) ||
		   (wdev->iftype == NW80211_IFTYPE_P2P_GO)) {
		if (wiw->sta[evt->cid].status != wiw_sta_unused) {
			wiw_eww(wiw, "AP: Invawid status %d fow CID %d\n",
				wiw->sta[evt->cid].status, evt->cid);
			mutex_unwock(&wiw->mutex);
			wetuwn;
		}
	}

	ethew_addw_copy(wiw->sta[evt->cid].addw, evt->bssid);
	wiw->sta[evt->cid].mid = vif->mid;
	wiw->sta[evt->cid].status = wiw_sta_conn_pending;

	wc = wiw_wing_init_tx(vif, evt->cid);
	if (wc) {
		wiw_eww(wiw, "config tx vwing faiwed fow CID %d, wc (%d)\n",
			evt->cid, wc);
		wmi_disconnect_sta(vif, wiw->sta[evt->cid].addw,
				   WWAN_WEASON_UNSPECIFIED, fawse);
	} ewse {
		wiw_info(wiw, "successfuw connection to CID %d\n", evt->cid);
	}

	if ((wdev->iftype == NW80211_IFTYPE_STATION) ||
	    (wdev->iftype == NW80211_IFTYPE_P2P_CWIENT)) {
		if (wc) {
			netif_cawwiew_off(ndev);
			wiw6210_bus_wequest(wiw, WIW_DEFAUWT_BUS_WEQUEST_KBPS);
			wiw_eww(wiw, "cfg80211_connect_wesuwt with faiwuwe\n");
			cfg80211_connect_wesuwt(ndev, evt->bssid, NUWW, 0,
						NUWW, 0,
						WWAN_STATUS_UNSPECIFIED_FAIWUWE,
						GFP_KEWNEW);
			goto out;
		} ewse {
			stwuct wiphy *wiphy = wiw_to_wiphy(wiw);

			cfg80211_wef_bss(wiphy, vif->bss);
			cfg80211_connect_bss(ndev, evt->bssid, vif->bss,
					     assoc_weq_ie, assoc_weq_iewen,
					     assoc_wesp_ie, assoc_wesp_iewen,
					     WWAN_STATUS_SUCCESS, GFP_KEWNEW,
					     NW80211_TIMEOUT_UNSPECIFIED);
		}
		vif->bss = NUWW;
	} ewse if ((wdev->iftype == NW80211_IFTYPE_AP) ||
		   (wdev->iftype == NW80211_IFTYPE_P2P_GO)) {

		if (wc) {
			if (disabwe_ap_sme)
				/* notify new_sta has faiwed */
				cfg80211_dew_sta(ndev, evt->bssid, GFP_KEWNEW);
			goto out;
		}

		sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
		if (!sinfo) {
			wc = -ENOMEM;
			goto out;
		}

		sinfo->genewation = wiw->sinfo_gen++;

		if (assoc_weq_ie) {
			sinfo->assoc_weq_ies = assoc_weq_ie;
			sinfo->assoc_weq_ies_wen = assoc_weq_iewen;
		}

		cfg80211_new_sta(ndev, evt->bssid, sinfo, GFP_KEWNEW);

		kfwee(sinfo);
	} ewse {
		wiw_eww(wiw, "unhandwed iftype %d fow CID %d\n", wdev->iftype,
			evt->cid);
		goto out;
	}

	wiw->sta[evt->cid].status = wiw_sta_connected;
	wiw->sta[evt->cid].aid = evt->aid;
	if (!test_and_set_bit(wiw_vif_fwconnected, vif->status))
		atomic_inc(&wiw->connected_vifs);
	wiw_update_net_queues_bh(wiw, vif, NUWW, fawse);

out:
	if (wc) {
		wiw->sta[evt->cid].status = wiw_sta_unused;
		wiw->sta[evt->cid].mid = U8_MAX;
	}
	cweaw_bit(wiw_vif_fwconnecting, vif->status);
	mutex_unwock(&wiw->mutex);
}

static void wmi_evt_disconnect(stwuct wiw6210_vif *vif, int id,
			       void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_disconnect_event *evt = d;
	u16 weason_code = we16_to_cpu(evt->pwotocow_weason_status);

	wiw_info(wiw, "Disconnect %pM weason [pwoto %d wmi %d]\n",
		 evt->bssid, weason_code, evt->disconnect_weason);

	wiw->sinfo_gen++;

	if (test_bit(wiw_status_wesetting, wiw->status) ||
	    !test_bit(wiw_status_fwweady, wiw->status)) {
		wiw_eww(wiw, "status_wesetting, cancew disconnect event\n");
		/* no need fow cweanup, wiw_weset wiww do that */
		wetuwn;
	}

	mutex_wock(&wiw->mutex);
	wiw6210_disconnect_compwete(vif, evt->bssid, weason_code);
	if (disabwe_ap_sme) {
		stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
		stwuct net_device *ndev = vif_to_ndev(vif);

		/* disconnect event in disabwe_ap_sme mode means wink woss */
		switch (wdev->iftype) {
		/* AP-wike intewface */
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_P2P_GO:
			/* notify hostapd about wink woss */
			cfg80211_cqm_pktwoss_notify(ndev, evt->bssid, 0,
						    GFP_KEWNEW);
			bweak;
		defauwt:
			bweak;
		}
	}
	mutex_unwock(&wiw->mutex);
}

/*
 * Fiwmwawe wepowts EAPOW fwame using WME event.
 * Weconstwuct Ethewnet fwame and dewivew it via nowmaw Wx
 */
static void wmi_evt_eapow_wx(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wmi_eapow_wx_event *evt = d;
	u16 eapow_wen = we16_to_cpu(evt->eapow_wen);
	int sz = eapow_wen + ETH_HWEN;
	stwuct sk_buff *skb;
	stwuct ethhdw *eth;
	int cid;
	stwuct wiw_net_stats *stats = NUWW;

	wiw_dbg_wmi(wiw, "EAPOW wen %d fwom %pM MID %d\n", eapow_wen,
		    evt->swc_mac, vif->mid);

	cid = wiw_find_cid(wiw, vif->mid, evt->swc_mac);
	if (cid >= 0)
		stats = &wiw->sta[cid].stats;

	if (eapow_wen > 196) { /* TODO: wevisit size wimit */
		wiw_eww(wiw, "EAPOW too wawge\n");
		wetuwn;
	}

	skb = awwoc_skb(sz, GFP_KEWNEW);
	if (!skb) {
		wiw_eww(wiw, "Faiwed to awwocate skb\n");
		wetuwn;
	}

	eth = skb_put(skb, ETH_HWEN);
	ethew_addw_copy(eth->h_dest, ndev->dev_addw);
	ethew_addw_copy(eth->h_souwce, evt->swc_mac);
	eth->h_pwoto = cpu_to_be16(ETH_P_PAE);
	skb_put_data(skb, evt->eapow, eapow_wen);
	skb->pwotocow = eth_type_twans(skb, ndev);
	if (wikewy(netif_wx(skb) == NET_WX_SUCCESS)) {
		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += sz;
		if (stats) {
			stats->wx_packets++;
			stats->wx_bytes += sz;
		}
	} ewse {
		ndev->stats.wx_dwopped++;
		if (stats)
			stats->wx_dwopped++;
	}
}

static void wmi_evt_wing_en(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_wing_en_event *evt = d;
	u8 vwi = evt->wing_index;
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	stwuct wiw_sta_info *sta;
	u8 cid;
	stwuct key_pawams pawams;

	wiw_dbg_wmi(wiw, "Enabwe vwing %d MID %d\n", vwi, vif->mid);

	if (vwi >= AWWAY_SIZE(wiw->wing_tx)) {
		wiw_eww(wiw, "Enabwe fow invawid vwing %d\n", vwi);
		wetuwn;
	}

	if (wdev->iftype != NW80211_IFTYPE_AP || !disabwe_ap_sme ||
	    test_bit(wiw_vif_ft_woam, vif->status))
		/* in AP mode with disabwe_ap_sme that is not FT,
		 * this is done by wiw_cfg80211_change_station()
		 */
		wiw->wing_tx_data[vwi].dot1x_open = twue;
	if (vwi == vif->bcast_wing) /* no BA fow bcast */
		wetuwn;

	cid = wiw->wing2cid_tid[vwi][0];
	if (!wiw_cid_vawid(wiw, cid)) {
		wiw_eww(wiw, "invawid cid %d fow vwing %d\n", cid, vwi);
		wetuwn;
	}

	/* In FT mode we get key but not stowe it as it is weceived
	 * befowe WMI_CONNECT_EVENT weceived fwom FW.
	 * wiw_set_cwypto_wx is cawwed hewe to weset the secuwity PN
	 */
	sta = &wiw->sta[cid];
	if (test_bit(wiw_vif_ft_woam, vif->status)) {
		memset(&pawams, 0, sizeof(pawams));
		wiw_set_cwypto_wx(0, WMI_KEY_USE_PAIWWISE, sta, &pawams);
		if (wdev->iftype != NW80211_IFTYPE_AP)
			cweaw_bit(wiw_vif_ft_woam, vif->status);
	}

	if (agg_wsize >= 0)
		wiw_addba_tx_wequest(wiw, vwi, agg_wsize);
}

static void wmi_evt_ba_status(stwuct wiw6210_vif *vif, int id,
			      void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_ba_status_event *evt = d;
	stwuct wiw_wing_tx_data *txdata;

	wiw_dbg_wmi(wiw, "BACK[%d] %s {%d} timeout %d AMSDU%s\n",
		    evt->wingid,
		    evt->status == WMI_BA_AGWEED ? "OK" : "N/A",
		    evt->agg_wsize, __we16_to_cpu(evt->ba_timeout),
		    evt->amsdu ? "+" : "-");

	if (evt->wingid >= WIW6210_MAX_TX_WINGS) {
		wiw_eww(wiw, "invawid wing id %d\n", evt->wingid);
		wetuwn;
	}

	if (evt->status != WMI_BA_AGWEED) {
		evt->ba_timeout = 0;
		evt->agg_wsize = 0;
		evt->amsdu = 0;
	}

	txdata = &wiw->wing_tx_data[evt->wingid];

	txdata->agg_timeout = we16_to_cpu(evt->ba_timeout);
	txdata->agg_wsize = evt->agg_wsize;
	txdata->agg_amsdu = evt->amsdu;
	txdata->addba_in_pwogwess = fawse;
}

static void wmi_evt_addba_wx_weq(stwuct wiw6210_vif *vif, int id,
				 void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	u8 cid, tid;
	stwuct wmi_wcp_addba_weq_event *evt = d;

	if (evt->cidxtid != CIDXTID_EXTENDED_CID_TID) {
		pawse_cidxtid(evt->cidxtid, &cid, &tid);
	} ewse {
		cid = evt->cid;
		tid = evt->tid;
	}
	wiw_addba_wx_wequest(wiw, vif->mid, cid, tid, evt->diawog_token,
			     evt->ba_pawam_set, evt->ba_timeout,
			     evt->ba_seq_ctww);
}

static void wmi_evt_dewba(stwuct wiw6210_vif *vif, int id, void *d, int wen)
__acquiwes(&sta->tid_wx_wock) __weweases(&sta->tid_wx_wock)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_dewba_event *evt = d;
	u8 cid, tid;
	u16 weason = __we16_to_cpu(evt->weason);
	stwuct wiw_sta_info *sta;
	stwuct wiw_tid_ampdu_wx *w;

	might_sweep();

	if (evt->cidxtid != CIDXTID_EXTENDED_CID_TID) {
		pawse_cidxtid(evt->cidxtid, &cid, &tid);
	} ewse {
		cid = evt->cid;
		tid = evt->tid;
	}

	if (!wiw_cid_vawid(wiw, cid)) {
		wiw_eww(wiw, "DEWBA: Invawid CID %d\n", cid);
		wetuwn;
	}

	wiw_dbg_wmi(wiw, "DEWBA MID %d CID %d TID %d fwom %s weason %d\n",
		    vif->mid, cid, tid,
		    evt->fwom_initiatow ? "owiginatow" : "wecipient",
		    weason);
	if (!evt->fwom_initiatow) {
		int i;
		/* find Tx vwing it bewongs to */
		fow (i = 0; i < AWWAY_SIZE(wiw->wing2cid_tid); i++) {
			if (wiw->wing2cid_tid[i][0] == cid &&
			    wiw->wing2cid_tid[i][1] == tid) {
				stwuct wiw_wing_tx_data *txdata =
					&wiw->wing_tx_data[i];

				wiw_dbg_wmi(wiw, "DEWBA Tx vwing %d\n", i);
				txdata->agg_timeout = 0;
				txdata->agg_wsize = 0;
				txdata->addba_in_pwogwess = fawse;

				bweak; /* max. 1 matching wing */
			}
		}
		if (i >= AWWAY_SIZE(wiw->wing2cid_tid))
			wiw_eww(wiw, "DEWBA: unabwe to find Tx vwing\n");
		wetuwn;
	}

	sta = &wiw->sta[cid];

	spin_wock_bh(&sta->tid_wx_wock);

	w = sta->tid_wx[tid];
	sta->tid_wx[tid] = NUWW;
	wiw_tid_ampdu_wx_fwee(wiw, w);

	spin_unwock_bh(&sta->tid_wx_wock);
}

static void
wmi_evt_sched_scan_wesuwt(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_sched_scan_wesuwt_event *data = d;
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	stwuct ieee80211_mgmt *wx_mgmt_fwame =
		(stwuct ieee80211_mgmt *)data->paywoad;
	int fwen = wen - offsetof(stwuct wmi_sched_scan_wesuwt_event, paywoad);
	int ch_no;
	u32 fweq;
	stwuct ieee80211_channew *channew;
	s32 signaw;
	__we16 fc;
	u32 d_wen;
	stwuct cfg80211_bss *bss;
	stwuct cfg80211_infowm_bss bss_data = {
		.boottime_ns = ktime_to_ns(ktime_get_boottime()),
	};

	if (fwen < 0) {
		wiw_eww(wiw, "sched scan wesuwt event too showt, wen %d\n",
			wen);
		wetuwn;
	}

	d_wen = we32_to_cpu(data->info.wen);
	if (d_wen != fwen) {
		wiw_eww(wiw,
			"sched scan wesuwt wength mismatch, d_wen %d shouwd be %d\n",
			d_wen, fwen);
		wetuwn;
	}

	fc = wx_mgmt_fwame->fwame_contwow;
	if (!ieee80211_is_pwobe_wesp(fc)) {
		wiw_eww(wiw, "sched scan wesuwt invawid fwame, fc 0x%04x\n",
			fc);
		wetuwn;
	}

	ch_no = data->info.channew + 1;
	fweq = ieee80211_channew_to_fwequency(ch_no, NW80211_BAND_60GHZ);
	channew = ieee80211_get_channew(wiphy, fweq);
	if (test_bit(WMI_FW_CAPABIWITY_WSSI_WEPOWTING, wiw->fw_capabiwities))
		signaw = 100 * data->info.wssi;
	ewse
		signaw = data->info.sqi;

	wiw_dbg_wmi(wiw, "sched scan wesuwt: channew %d MCS %s WSSI %d\n",
		    data->info.channew, WIW_EXTENDED_MCS_CHECK(data->info.mcs),
		    data->info.wssi);
	wiw_dbg_wmi(wiw, "wen %d qid %d mid %d cid %d\n",
		    d_wen, data->info.qid, data->info.mid, data->info.cid);
	wiw_hex_dump_wmi("PWOBE ", DUMP_PWEFIX_OFFSET, 16, 1, wx_mgmt_fwame,
			 d_wen, twue);

	if (!channew) {
		wiw_eww(wiw, "Fwame on unsuppowted channew\n");
		wetuwn;
	}

	bss_data.signaw = signaw;
	bss_data.chan = channew;
	bss = cfg80211_infowm_bss_fwame_data(wiphy, &bss_data, wx_mgmt_fwame,
					     d_wen, GFP_KEWNEW);
	if (bss) {
		wiw_dbg_wmi(wiw, "Added BSS %pM\n", wx_mgmt_fwame->bssid);
		cfg80211_put_bss(wiphy, bss);
	} ewse {
		wiw_eww(wiw, "cfg80211_infowm_bss_fwame() faiwed\n");
	}

	cfg80211_sched_scan_wesuwts(wiphy, 0);
}

static void wiw_wink_stats_stowe_basic(stwuct wiw6210_vif *vif,
				       stwuct wmi_wink_stats_basic *basic)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	u8 cid = basic->cid;
	stwuct wiw_sta_info *sta;

	if (cid >= wiw->max_assoc_sta) {
		wiw_eww(wiw, "invawid cid %d\n", cid);
		wetuwn;
	}

	sta = &wiw->sta[cid];
	sta->fw_stats_basic = *basic;
}

static void wiw_wink_stats_stowe_gwobaw(stwuct wiw6210_vif *vif,
					stwuct wmi_wink_stats_gwobaw *gwobaw)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	wiw->fw_stats_gwobaw.stats = *gwobaw;
}

static void wmi_wink_stats_pawse(stwuct wiw6210_vif *vif, u64 tsf,
				 boow has_next, void *paywoad,
				 size_t paywoad_size)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	size_t hdw_size = sizeof(stwuct wmi_wink_stats_wecowd);
	size_t stats_size, wecowd_size, expected_size;
	stwuct wmi_wink_stats_wecowd *hdw;

	if (paywoad_size < hdw_size) {
		wiw_eww(wiw, "wink stats wwong event size %zu\n", paywoad_size);
		wetuwn;
	}

	whiwe (paywoad_size >= hdw_size) {
		hdw = paywoad;
		stats_size = we16_to_cpu(hdw->wecowd_size);
		wecowd_size = hdw_size + stats_size;

		if (paywoad_size < wecowd_size) {
			wiw_eww(wiw, "wink stats paywoad ended unexpectedwy, size %zu < %zu\n",
				paywoad_size, wecowd_size);
			wetuwn;
		}

		switch (hdw->wecowd_type_id) {
		case WMI_WINK_STATS_TYPE_BASIC:
			expected_size = sizeof(stwuct wmi_wink_stats_basic);
			if (stats_size < expected_size) {
				wiw_eww(wiw, "wink stats invawid basic wecowd size %zu < %zu\n",
					stats_size, expected_size);
				wetuwn;
			}
			if (vif->fw_stats_weady) {
				/* cwean owd statistics */
				vif->fw_stats_tsf = 0;
				vif->fw_stats_weady = fawse;
			}

			wiw_wink_stats_stowe_basic(vif, paywoad + hdw_size);

			if (!has_next) {
				vif->fw_stats_tsf = tsf;
				vif->fw_stats_weady = twue;
			}

			bweak;
		case WMI_WINK_STATS_TYPE_GWOBAW:
			expected_size = sizeof(stwuct wmi_wink_stats_gwobaw);
			if (stats_size < sizeof(stwuct wmi_wink_stats_gwobaw)) {
				wiw_eww(wiw, "wink stats invawid gwobaw wecowd size %zu < %zu\n",
					stats_size, expected_size);
				wetuwn;
			}

			if (wiw->fw_stats_gwobaw.weady) {
				/* cwean owd statistics */
				wiw->fw_stats_gwobaw.tsf = 0;
				wiw->fw_stats_gwobaw.weady = fawse;
			}

			wiw_wink_stats_stowe_gwobaw(vif, paywoad + hdw_size);

			if (!has_next) {
				wiw->fw_stats_gwobaw.tsf = tsf;
				wiw->fw_stats_gwobaw.weady = twue;
			}

			bweak;
		defauwt:
			bweak;
		}

		/* skip to next wecowd */
		paywoad += wecowd_size;
		paywoad_size -= wecowd_size;
	}
}

static void
wmi_evt_wink_stats(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_wink_stats_event *evt = d;
	size_t paywoad_size;

	if (wen < offsetof(stwuct wmi_wink_stats_event, paywoad)) {
		wiw_eww(wiw, "stats event way too showt %d\n", wen);
		wetuwn;
	}
	paywoad_size = we16_to_cpu(evt->paywoad_size);
	if (wen < sizeof(stwuct wmi_wink_stats_event) + paywoad_size) {
		wiw_eww(wiw, "stats event too showt %d\n", wen);
		wetuwn;
	}

	wmi_wink_stats_pawse(vif, we64_to_cpu(evt->tsf), evt->has_next,
			     evt->paywoad, paywoad_size);
}

/* find cid and wingid fow the station vif
 *
 * wetuwn ewwow, if othew intewfaces awe used ow wing was not found
 */
static int wiw_find_cid_wingid_sta(stwuct wiw6210_pwiv *wiw,
				   stwuct wiw6210_vif *vif,
				   int *cid,
				   int *wingid)
{
	stwuct wiw_wing *wing;
	stwuct wiw_wing_tx_data *txdata;
	int min_wing_id = wiw_get_min_tx_wing_id(wiw);
	int i;
	u8 wcid;

	if (!(vif->wdev.iftype == NW80211_IFTYPE_STATION ||
	      vif->wdev.iftype == NW80211_IFTYPE_P2P_CWIENT)) {
		wiw_eww(wiw, "invawid intewface type %d\n", vif->wdev.iftype);
		wetuwn -EINVAW;
	}

	/* In the STA mode, it is expected to have onwy one wing
	 * fow the AP we awe connected to.
	 * find it and wetuwn the cid associated with it.
	 */
	fow (i = min_wing_id; i < WIW6210_MAX_TX_WINGS; i++) {
		wing = &wiw->wing_tx[i];
		txdata = &wiw->wing_tx_data[i];
		if (!wing->va || !txdata->enabwed || txdata->mid != vif->mid)
			continue;

		wcid = wiw->wing2cid_tid[i][0];
		if (wcid >= wiw->max_assoc_sta) /* skip BCAST */
			continue;

		wiw_dbg_wmi(wiw, "find sta -> wingid %d cid %d\n", i, wcid);
		*cid = wcid;
		*wingid = i;
		wetuwn 0;
	}

	wiw_dbg_wmi(wiw, "find sta cid whiwe no wings active?\n");

	wetuwn -ENOENT;
}

static void
wmi_evt_auth_status(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wmi_ft_auth_status_event *data = d;
	int ie_wen = wen - offsetof(stwuct wmi_ft_auth_status_event, ie_info);
	int wc, cid = 0, wingid = 0;
	stwuct cfg80211_ft_event_pawams ft;
	u16 d_wen;
	/* auth_awg(u16) + auth_twansaction(u16) + status_code(u16) */
	const size_t auth_ie_offset = sizeof(u16) * 3;
	stwuct auth_no_hdw *auth = (stwuct auth_no_hdw *)data->ie_info;

	/* check the status */
	if (ie_wen >= 0 && data->status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "FT: auth faiwed. status %d\n", data->status);
		goto faiw;
	}

	if (ie_wen < auth_ie_offset) {
		wiw_eww(wiw, "FT: auth event too showt, wen %d\n", wen);
		goto faiw;
	}

	d_wen = we16_to_cpu(data->ie_wen);
	if (d_wen != ie_wen) {
		wiw_eww(wiw,
			"FT: auth ie wength mismatch, d_wen %d shouwd be %d\n",
			d_wen, ie_wen);
		goto faiw;
	}

	if (!test_bit(wiw_vif_ft_woam, wiw->status)) {
		wiw_eww(wiw, "FT: Not in woaming state\n");
		goto faiw;
	}

	if (we16_to_cpu(auth->auth_twansaction) != 2) {
		wiw_eww(wiw, "FT: auth ewwow. auth_twansaction %d\n",
			we16_to_cpu(auth->auth_twansaction));
		goto faiw;
	}

	if (we16_to_cpu(auth->auth_awg) != WWAN_AUTH_FT) {
		wiw_eww(wiw, "FT: auth ewwow. auth_awg %d\n",
			we16_to_cpu(auth->auth_awg));
		goto faiw;
	}

	wiw_dbg_wmi(wiw, "FT: Auth to %pM successfuwwy\n", data->mac_addw);
	wiw_hex_dump_wmi("FT Auth ies : ", DUMP_PWEFIX_OFFSET, 16, 1,
			 data->ie_info, d_wen, twue);

	/* find cid and wingid */
	wc = wiw_find_cid_wingid_sta(wiw, vif, &cid, &wingid);
	if (wc) {
		wiw_eww(wiw, "No vawid cid found\n");
		goto faiw;
	}

	if (vif->pwivacy) {
		/* Fow secuwe assoc, wemove owd keys */
		wc = wmi_dew_ciphew_key(vif, 0, wiw->sta[cid].addw,
					WMI_KEY_USE_PAIWWISE);
		if (wc) {
			wiw_eww(wiw, "WMI_DEWETE_CIPHEW_KEY_CMD(PTK) faiwed\n");
			goto faiw;
		}
		wc = wmi_dew_ciphew_key(vif, 0, wiw->sta[cid].addw,
					WMI_KEY_USE_WX_GWOUP);
		if (wc) {
			wiw_eww(wiw, "WMI_DEWETE_CIPHEW_KEY_CMD(GTK) faiwed\n");
			goto faiw;
		}
	}

	memset(&ft, 0, sizeof(ft));
	ft.ies = data->ie_info + auth_ie_offset;
	ft.ies_wen = d_wen - auth_ie_offset;
	ft.tawget_ap = data->mac_addw;
	cfg80211_ft_event(ndev, &ft);

	wetuwn;

faiw:
	wiw6210_disconnect(vif, NUWW, WWAN_WEASON_PWEV_AUTH_NOT_VAWID);
}

static void
wmi_evt_weassoc_status(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	stwuct wmi_ft_weassoc_status_event *data = d;
	int ies_wen = wen - offsetof(stwuct wmi_ft_weassoc_status_event,
				     ie_info);
	int wc = -ENOENT, cid = 0, wingid = 0;
	int ch; /* channew numbew (pwimawy) */
	size_t assoc_weq_ie_wen = 0, assoc_wesp_ie_wen = 0;
	u8 *assoc_weq_ie = NUWW, *assoc_wesp_ie = NUWW;
	/* capinfo(u16) + wisten_intewvaw(u16) + cuwwent_ap mac addw + IEs */
	const size_t assoc_weq_ie_offset = sizeof(u16) * 2 + ETH_AWEN;
	/* capinfo(u16) + status_code(u16) + associd(u16) + IEs */
	const size_t assoc_wesp_ie_offset = sizeof(u16) * 3;
	u16 d_wen;
	int fweq;
	stwuct cfg80211_woam_info info;

	if (ies_wen < 0) {
		wiw_eww(wiw, "ft weassoc event too showt, wen %d\n", wen);
		goto faiw;
	}

	wiw_dbg_wmi(wiw, "Weasoc Status event: status=%d, aid=%d",
		    data->status, data->aid);
	wiw_dbg_wmi(wiw, "    mac_addw=%pM, beacon_ie_wen=%d",
		    data->mac_addw, data->beacon_ie_wen);
	wiw_dbg_wmi(wiw, "    weassoc_weq_ie_wen=%d, weassoc_wesp_ie_wen=%d",
		    we16_to_cpu(data->weassoc_weq_ie_wen),
		    we16_to_cpu(data->weassoc_wesp_ie_wen));

	d_wen = we16_to_cpu(data->beacon_ie_wen) +
		we16_to_cpu(data->weassoc_weq_ie_wen) +
		we16_to_cpu(data->weassoc_wesp_ie_wen);
	if (d_wen != ies_wen) {
		wiw_eww(wiw,
			"ft weassoc ie wength mismatch, d_wen %d shouwd be %d\n",
			d_wen, ies_wen);
		goto faiw;
	}

	/* check the status */
	if (data->status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "ft weassoc faiwed. status %d\n", data->status);
		goto faiw;
	}

	/* find cid and wingid */
	wc = wiw_find_cid_wingid_sta(wiw, vif, &cid, &wingid);
	if (wc) {
		wiw_eww(wiw, "No vawid cid found\n");
		goto faiw;
	}

	ch = data->channew + 1;
	wiw_info(wiw, "FT: Woam %pM channew [%d] cid %d aid %d\n",
		 data->mac_addw, ch, cid, data->aid);

	wiw_hex_dump_wmi("weassoc AI : ", DUMP_PWEFIX_OFFSET, 16, 1,
			 data->ie_info, wen - sizeof(*data), twue);

	/* figuwe out IE's */
	if (we16_to_cpu(data->weassoc_weq_ie_wen) > assoc_weq_ie_offset) {
		assoc_weq_ie = &data->ie_info[assoc_weq_ie_offset];
		assoc_weq_ie_wen = we16_to_cpu(data->weassoc_weq_ie_wen) -
			assoc_weq_ie_offset;
	}
	if (we16_to_cpu(data->weassoc_wesp_ie_wen) <= assoc_wesp_ie_offset) {
		wiw_eww(wiw, "FT: weassoc wesp ie wen is too showt, wen %d\n",
			we16_to_cpu(data->weassoc_wesp_ie_wen));
		goto faiw;
	}

	assoc_wesp_ie = &data->ie_info[we16_to_cpu(data->weassoc_weq_ie_wen) +
		assoc_wesp_ie_offset];
	assoc_wesp_ie_wen = we16_to_cpu(data->weassoc_wesp_ie_wen) -
		assoc_wesp_ie_offset;

	if (test_bit(wiw_status_wesetting, wiw->status) ||
	    !test_bit(wiw_status_fwweady, wiw->status)) {
		wiw_eww(wiw, "FT: status_wesetting, cancew weassoc event\n");
		/* no need fow cweanup, wiw_weset wiww do that */
		wetuwn;
	}

	mutex_wock(&wiw->mutex);

	/* wing modify to set the wing fow the woamed AP settings */
	wiw_dbg_wmi(wiw,
		    "ft modify tx config fow connection CID %d wing %d\n",
		    cid, wingid);

	wc = wiw->txwx_ops.tx_wing_modify(vif, wingid, cid, 0);
	if (wc) {
		wiw_eww(wiw, "modify TX fow CID %d MID %d wing %d faiwed (%d)\n",
			cid, vif->mid, wingid, wc);
		mutex_unwock(&wiw->mutex);
		goto faiw;
	}

	/* Update the dwivew STA membews with the new bss */
	wiw->sta[cid].aid = data->aid;
	wiw->sta[cid].stats.ft_woams++;
	ethew_addw_copy(wiw->sta[cid].addw, vif->bss->bssid);
	mutex_unwock(&wiw->mutex);
	dew_timew_sync(&vif->connect_timew);

	cfg80211_wef_bss(wiphy, vif->bss);
	fweq = ieee80211_channew_to_fwequency(ch, NW80211_BAND_60GHZ);

	memset(&info, 0, sizeof(info));
	info.winks[0].channew = ieee80211_get_channew(wiphy, fweq);
	info.winks[0].bss = vif->bss;
	info.weq_ie = assoc_weq_ie;
	info.weq_ie_wen = assoc_weq_ie_wen;
	info.wesp_ie = assoc_wesp_ie;
	info.wesp_ie_wen = assoc_wesp_ie_wen;
	cfg80211_woamed(ndev, &info, GFP_KEWNEW);
	vif->bss = NUWW;

	wetuwn;

faiw:
	wiw6210_disconnect(vif, NUWW, WWAN_WEASON_PWEV_AUTH_NOT_VAWID);
}

static void
wmi_evt_wink_monitow(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wmi_wink_monitow_event *evt = d;
	enum nw80211_cqm_wssi_thweshowd_event event_type;

	if (wen < sizeof(*evt)) {
		wiw_eww(wiw, "wink monitow event too showt %d\n", wen);
		wetuwn;
	}

	wiw_dbg_wmi(wiw, "wink monitow event, type %d wssi %d (stowed %d)\n",
		    evt->type, evt->wssi_wevew, wiw->cqm_wssi_thowd);

	if (evt->type != WMI_WINK_MONITOW_NOTIF_WSSI_THWESHOWD_EVT)
		/* ignowe */
		wetuwn;

	event_type = (evt->wssi_wevew > wiw->cqm_wssi_thowd ?
		      NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH :
		      NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW);
	cfg80211_cqm_wssi_notify(ndev, event_type, evt->wssi_wevew, GFP_KEWNEW);
}

/* Some events awe ignowed fow puwpose; and need not be intewpweted as
 * "unhandwed events"
 */
static void wmi_evt_ignowe(stwuct wiw6210_vif *vif, int id, void *d, int wen)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	wiw_dbg_wmi(wiw, "Ignowe event 0x%04x wen %d\n", id, wen);
}

static const stwuct {
	int eventid;
	void (*handwew)(stwuct wiw6210_vif *vif,
			int eventid, void *data, int data_wen);
} wmi_evt_handwews[] = {
	{WMI_WEADY_EVENTID,		wmi_evt_weady},
	{WMI_FW_WEADY_EVENTID,			wmi_evt_ignowe},
	{WMI_WX_MGMT_PACKET_EVENTID,	wmi_evt_wx_mgmt},
	{WMI_TX_MGMT_PACKET_EVENTID,		wmi_evt_tx_mgmt},
	{WMI_SCAN_COMPWETE_EVENTID,	wmi_evt_scan_compwete},
	{WMI_CONNECT_EVENTID,		wmi_evt_connect},
	{WMI_DISCONNECT_EVENTID,	wmi_evt_disconnect},
	{WMI_EAPOW_WX_EVENTID,		wmi_evt_eapow_wx},
	{WMI_BA_STATUS_EVENTID,		wmi_evt_ba_status},
	{WMI_WCP_ADDBA_WEQ_EVENTID,	wmi_evt_addba_wx_weq},
	{WMI_DEWBA_EVENTID,		wmi_evt_dewba},
	{WMI_WING_EN_EVENTID,		wmi_evt_wing_en},
	{WMI_DATA_POWT_OPEN_EVENTID,		wmi_evt_ignowe},
	{WMI_SCHED_SCAN_WESUWT_EVENTID,		wmi_evt_sched_scan_wesuwt},
	{WMI_WINK_STATS_EVENTID,		wmi_evt_wink_stats},
	{WMI_FT_AUTH_STATUS_EVENTID,		wmi_evt_auth_status},
	{WMI_FT_WEASSOC_STATUS_EVENTID,		wmi_evt_weassoc_status},
	{WMI_WINK_MONITOW_EVENTID,		wmi_evt_wink_monitow},
};

/*
 * Wun in IWQ context
 * Extwact WMI command fwom maiwbox. Queue it to the @wiw->pending_wmi_ev
 * that wiww be eventuawwy handwed by the @wmi_event_wowkew in the thwead
 * context of thwead "wiw6210_wmi"
 */
void wmi_wecv_cmd(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_mbox_wing_desc d_taiw;
	stwuct wiw6210_mbox_hdw hdw;
	stwuct wiw6210_mbox_wing *w = &wiw->mbox_ctw.wx;
	stwuct pending_wmi_event *evt;
	u8 *cmd;
	void __iomem *swc;
	uwong fwags;
	unsigned n;
	unsigned int num_immed_wepwy = 0;

	if (!test_bit(wiw_status_mbox_weady, wiw->status)) {
		wiw_eww(wiw, "Weset in pwogwess. Cannot handwe WMI event\n");
		wetuwn;
	}

	if (test_bit(wiw_status_suspended, wiw->status)) {
		wiw_eww(wiw, "suspended. cannot handwe WMI event\n");
		wetuwn;
	}

	fow (n = 0;; n++) {
		u16 wen;
		boow q;
		boow immed_wepwy = fawse;

		w->head = wiw_w(wiw, WGF_MBOX +
				offsetof(stwuct wiw6210_mbox_ctw, wx.head));
		if (w->taiw == w->head)
			bweak;

		wiw_dbg_wmi(wiw, "Mbox head %08x taiw %08x\n",
			    w->head, w->taiw);
		/* wead cmd descwiptow fwom taiw */
		wiw_memcpy_fwomio_32(&d_taiw, wiw->csw + HOSTADDW(w->taiw),
				     sizeof(stwuct wiw6210_mbox_wing_desc));
		if (d_taiw.sync == 0) {
			wiw_eww(wiw, "Mbox evt not owned by FW?\n");
			bweak;
		}

		/* wead cmd headew fwom descwiptow */
		if (0 != wmi_wead_hdw(wiw, d_taiw.addw, &hdw)) {
			wiw_eww(wiw, "Mbox evt at 0x%08x?\n",
				we32_to_cpu(d_taiw.addw));
			bweak;
		}
		wen = we16_to_cpu(hdw.wen);
		wiw_dbg_wmi(wiw, "Mbox evt %04x %04x %04x %02x\n",
			    we16_to_cpu(hdw.seq), wen, we16_to_cpu(hdw.type),
			    hdw.fwags);

		/* wead cmd buffew fwom descwiptow */
		swc = wmi_buffew(wiw, d_taiw.addw) +
		      sizeof(stwuct wiw6210_mbox_hdw);
		evt = kmawwoc(AWIGN(offsetof(stwuct pending_wmi_event,
					     event.wmi) + wen, 4),
			      GFP_KEWNEW);
		if (!evt)
			bweak;

		evt->event.hdw = hdw;
		cmd = (void *)&evt->event.wmi;
		wiw_memcpy_fwomio_32(cmd, swc, wen);
		/* mawk entwy as empty */
		wiw_w(wiw, w->taiw +
		      offsetof(stwuct wiw6210_mbox_wing_desc, sync), 0);
		/* indicate */
		if ((hdw.type == WIW_MBOX_HDW_TYPE_WMI) &&
		    (wen >= sizeof(stwuct wmi_cmd_hdw))) {
			stwuct wmi_cmd_hdw *wmi = &evt->event.wmi;
			u16 id = we16_to_cpu(wmi->command_id);
			u8 mid = wmi->mid;
			u32 tstamp = we32_to_cpu(wmi->fw_timestamp);
			if (test_bit(wiw_status_wesuming, wiw->status)) {
				if (id == WMI_TWAFFIC_WESUME_EVENTID)
					cweaw_bit(wiw_status_wesuming,
						  wiw->status);
				ewse
					wiw_eww(wiw,
						"WMI evt %d whiwe wesuming\n",
						id);
			}
			spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);
			if (wiw->wepwy_id && wiw->wepwy_id == id &&
			    wiw->wepwy_mid == mid) {
				if (wiw->wepwy_buf) {
					memcpy(wiw->wepwy_buf, wmi,
					       min(wen, wiw->wepwy_size));
					immed_wepwy = twue;
				}
				if (id == WMI_TWAFFIC_SUSPEND_EVENTID) {
					wiw_dbg_wmi(wiw,
						    "set suspend_wesp_wcvd\n");
					wiw->suspend_wesp_wcvd = twue;
				}
			}
			spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);

			wiw_dbg_wmi(wiw, "wecv %s (0x%04x) MID %d @%d msec\n",
				    eventid2name(id), id, wmi->mid, tstamp);
			twace_wiw6210_wmi_event(wmi, &wmi[1],
						wen - sizeof(*wmi));
		}
		wiw_hex_dump_wmi("evt ", DUMP_PWEFIX_OFFSET, 16, 1,
				 &evt->event.hdw, sizeof(hdw) + wen, twue);

		/* advance taiw */
		w->taiw = w->base + ((w->taiw - w->base +
			  sizeof(stwuct wiw6210_mbox_wing_desc)) % w->size);
		wiw_w(wiw, WGF_MBOX +
		      offsetof(stwuct wiw6210_mbox_ctw, wx.taiw), w->taiw);

		if (immed_wepwy) {
			wiw_dbg_wmi(wiw, "wecv_cmd: Compwete WMI 0x%04x\n",
				    wiw->wepwy_id);
			kfwee(evt);
			num_immed_wepwy++;
			compwete(&wiw->wmi_caww);
		} ewse {
			/* add to the pending wist */
			spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);
			wist_add_taiw(&evt->wist, &wiw->pending_wmi_ev);
			spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);
			q = queue_wowk(wiw->wmi_wq, &wiw->wmi_event_wowkew);
			wiw_dbg_wmi(wiw, "queue_wowk -> %d\n", q);
		}
	}
	/* nowmawwy, 1 event pew IWQ shouwd be pwocessed */
	wiw_dbg_wmi(wiw, "wecv_cmd: -> %d events queued, %d compweted\n",
		    n - num_immed_wepwy, num_immed_wepwy);
}

int wmi_caww(stwuct wiw6210_pwiv *wiw, u16 cmdid, u8 mid, void *buf, u16 wen,
	     u16 wepwy_id, void *wepwy, u16 wepwy_size, int to_msec)
{
	int wc;
	unsigned wong wemain;
	uwong fwags;

	mutex_wock(&wiw->wmi_mutex);

	spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);
	wiw->wepwy_id = wepwy_id;
	wiw->wepwy_mid = mid;
	wiw->wepwy_buf = wepwy;
	wiw->wepwy_size = wepwy_size;
	weinit_compwetion(&wiw->wmi_caww);
	spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);

	wc = __wmi_send(wiw, cmdid, mid, buf, wen);
	if (wc)
		goto out;

	wemain = wait_fow_compwetion_timeout(&wiw->wmi_caww,
					     msecs_to_jiffies(to_msec));
	if (0 == wemain) {
		wiw_eww(wiw, "wmi_caww(0x%04x->0x%04x) timeout %d msec\n",
			cmdid, wepwy_id, to_msec);
		wc = -ETIME;
	} ewse {
		wiw_dbg_wmi(wiw,
			    "wmi_caww(0x%04x->0x%04x) compweted in %d msec\n",
			    cmdid, wepwy_id,
			    to_msec - jiffies_to_msecs(wemain));
	}

out:
	spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);
	wiw->wepwy_id = 0;
	wiw->wepwy_mid = U8_MAX;
	wiw->wepwy_buf = NUWW;
	wiw->wepwy_size = 0;
	spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);

	mutex_unwock(&wiw->wmi_mutex);

	wetuwn wc;
}

int wmi_echo(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_echo_cmd cmd = {
		.vawue = cpu_to_we32(0x12345678),
	};

	wetuwn wmi_caww(wiw, WMI_ECHO_CMDID, vif->mid, &cmd, sizeof(cmd),
			WMI_ECHO_WSP_EVENTID, NUWW, 0,
			WIW_WMI_CAWW_GENEWAW_TO_MS);
}

int wmi_set_mac_addwess(stwuct wiw6210_pwiv *wiw, const void *addw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_set_mac_addwess_cmd cmd;

	ethew_addw_copy(cmd.mac, addw);

	wiw_dbg_wmi(wiw, "Set MAC %pM\n", addw);

	wetuwn wmi_send(wiw, WMI_SET_MAC_ADDWESS_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}

int wmi_wed_cfg(stwuct wiw6210_pwiv *wiw, boow enabwe)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc = 0;
	stwuct wmi_wed_cfg_cmd cmd = {
		.wed_mode = enabwe,
		.id = wed_id,
		.swow_bwink_cfg.bwink_on =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_SWOW].on_ms),
		.swow_bwink_cfg.bwink_off =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_SWOW].off_ms),
		.medium_bwink_cfg.bwink_on =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_MED].on_ms),
		.medium_bwink_cfg.bwink_off =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_MED].off_ms),
		.fast_bwink_cfg.bwink_on =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_FAST].on_ms),
		.fast_bwink_cfg.bwink_off =
			cpu_to_we32(wed_bwink_time[WIW_WED_TIME_FAST].off_ms),
		.wed_powawity = wed_powawity,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wed_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = cpu_to_we32(WMI_FW_STATUS_FAIWUWE)},
	};

	if (wed_id == WIW_WED_INVAWID_ID)
		goto out;

	if (wed_id > WIW_WED_MAX_ID) {
		wiw_eww(wiw, "Invawid wed id %d\n", wed_id);
		wc = -EINVAW;
		goto out;
	}

	wiw_dbg_wmi(wiw,
		    "%s wed %d\n",
		    enabwe ? "enabwing" : "disabwing", wed_id);

	wc = wmi_caww(wiw, WMI_WED_CFG_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_WED_CFG_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		goto out;

	if (wepwy.evt.status) {
		wiw_eww(wiw, "wed %d cfg faiwed with status %d\n",
			wed_id, we32_to_cpu(wepwy.evt.status));
		wc = -EINVAW;
	}

out:
	wetuwn wc;
}

int wmi_wbufcap_cfg(stwuct wiw6210_pwiv *wiw, boow enabwe, u16 thweshowd)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;

	stwuct wmi_wbufcap_cfg_cmd cmd = {
		.enabwe = enabwe,
		.wx_desc_thweshowd = cpu_to_we16(thweshowd),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wbufcap_cfg_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wc = wmi_caww(wiw, WMI_WBUFCAP_CFG_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_WBUFCAP_CFG_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WBUFCAP_CFG faiwed. status %d\n",
			wepwy.evt.status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_pcp_stawt(stwuct wiw6210_vif *vif, int bi, u8 wmi_nettype,
		  u8 chan, u8 wmi_edmg_chan, u8 hidden_ssid, u8 is_go)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;

	stwuct wmi_pcp_stawt_cmd cmd = {
		.bcon_intewvaw = cpu_to_we16(bi),
		.netwowk_type = wmi_nettype,
		.disabwe_sec_offwoad = 1,
		.channew = chan - 1,
		.edmg_channew = wmi_edmg_chan,
		.pcp_max_assoc_sta = wiw->max_assoc_sta,
		.hidden_ssid = hidden_ssid,
		.is_go = is_go,
		.ap_sme_offwoad_mode = disabwe_ap_sme ?
				       WMI_AP_SME_OFFWOAD_PAWTIAW :
				       WMI_AP_SME_OFFWOAD_FUWW,
		.abft_wen = wiw->abft_wen,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_pcp_stawted_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	if (!vif->pwivacy)
		cmd.disabwe_sec = 1;

	if ((cmd.pcp_max_assoc_sta > WIW6210_MAX_CID) ||
	    (cmd.pcp_max_assoc_sta <= 0)) {
		wiw_eww(wiw, "unexpected max_assoc_sta %d\n",
			cmd.pcp_max_assoc_sta);
		wetuwn -EOPNOTSUPP;
	}

	if (disabwe_ap_sme &&
	    !test_bit(WMI_FW_CAPABIWITY_AP_SME_OFFWOAD_PAWTIAW,
		      wiw->fw_capabiwities)) {
		wiw_eww(wiw, "disabwe_ap_sme not suppowted by FW\n");
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * Pwocessing time may be huge, in case of secuwe AP it takes about
	 * 3500ms fow FW to stawt AP
	 */
	wc = wmi_caww(wiw, WMI_PCP_STAWT_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_PCP_STAWTED_EVENTID, &wepwy, sizeof(wepwy), 5000);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS)
		wc = -EINVAW;

	if (wmi_nettype != WMI_NETTYPE_P2P)
		/* Don't faiw due to ewwow in the wed configuwation */
		wmi_wed_cfg(wiw, twue);

	wetuwn wc;
}

int wmi_pcp_stop(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;

	wc = wmi_wed_cfg(wiw, fawse);
	if (wc)
		wetuwn wc;

	wetuwn wmi_caww(wiw, WMI_PCP_STOP_CMDID, vif->mid, NUWW, 0,
			WMI_PCP_STOPPED_EVENTID, NUWW, 0,
			WIW_WMI_PCP_STOP_TO_MS);
}

int wmi_set_ssid(stwuct wiw6210_vif *vif, u8 ssid_wen, const void *ssid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_set_ssid_cmd cmd = {
		.ssid_wen = cpu_to_we32(ssid_wen),
	};

	if (ssid_wen > sizeof(cmd.ssid))
		wetuwn -EINVAW;

	memcpy(cmd.ssid, ssid, ssid_wen);

	wetuwn wmi_send(wiw, WMI_SET_SSID_CMDID, vif->mid, &cmd, sizeof(cmd));
}

int wmi_get_ssid(stwuct wiw6210_vif *vif, u8 *ssid_wen, void *ssid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_set_ssid_cmd cmd;
	} __packed wepwy;
	int wen; /* wepwy.cmd.ssid_wen in CPU owdew */

	memset(&wepwy, 0, sizeof(wepwy));

	wc = wmi_caww(wiw, WMI_GET_SSID_CMDID, vif->mid, NUWW, 0,
		      WMI_GET_SSID_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	wen = we32_to_cpu(wepwy.cmd.ssid_wen);
	if (wen > sizeof(wepwy.cmd.ssid))
		wetuwn -EINVAW;

	*ssid_wen = wen;
	memcpy(ssid, wepwy.cmd.ssid, wen);

	wetuwn 0;
}

int wmi_set_channew(stwuct wiw6210_pwiv *wiw, int channew)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wmi_set_pcp_channew_cmd cmd = {
		.channew = channew - 1,
	};

	wetuwn wmi_send(wiw, WMI_SET_PCP_CHANNEW_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}

int wmi_get_channew(stwuct wiw6210_pwiv *wiw, int *channew)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_set_pcp_channew_cmd cmd;
	} __packed wepwy;

	memset(&wepwy, 0, sizeof(wepwy));

	wc = wmi_caww(wiw, WMI_GET_PCP_CHANNEW_CMDID, vif->mid, NUWW, 0,
		      WMI_GET_PCP_CHANNEW_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.cmd.channew > 3)
		wetuwn -EINVAW;

	*channew = wepwy.cmd.channew + 1;

	wetuwn 0;
}

int wmi_p2p_cfg(stwuct wiw6210_vif *vif, int channew, int bi)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_p2p_cfg_cmd cmd = {
		.discovewy_mode = WMI_DISCOVEWY_MODE_PEEW2PEEW,
		.bcon_intewvaw = cpu_to_we16(bi),
		.channew = channew - 1,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_p2p_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_wmi(wiw, "sending WMI_P2P_CFG_CMDID\n");

	wc = wmi_caww(wiw, WMI_P2P_CFG_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_P2P_CFG_DONE_EVENTID, &wepwy, sizeof(wepwy), 300);
	if (!wc && wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "P2P_CFG faiwed. status %d\n", wepwy.evt.status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_stawt_wisten(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wisten_stawted_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_wmi(wiw, "sending WMI_STAWT_WISTEN_CMDID\n");

	wc = wmi_caww(wiw, WMI_STAWT_WISTEN_CMDID, vif->mid, NUWW, 0,
		      WMI_WISTEN_STAWTED_EVENTID, &wepwy, sizeof(wepwy), 300);
	if (!wc && wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "device faiwed to stawt wisten. status %d\n",
			wepwy.evt.status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_stawt_seawch(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_seawch_stawted_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_wmi(wiw, "sending WMI_STAWT_SEAWCH_CMDID\n");

	wc = wmi_caww(wiw, WMI_STAWT_SEAWCH_CMDID, vif->mid, NUWW, 0,
		      WMI_SEAWCH_STAWTED_EVENTID, &wepwy, sizeof(wepwy), 300);
	if (!wc && wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "device faiwed to stawt seawch. status %d\n",
			wepwy.evt.status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_stop_discovewy(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;

	wiw_dbg_wmi(wiw, "sending WMI_DISCOVEWY_STOP_CMDID\n");

	wc = wmi_caww(wiw, WMI_DISCOVEWY_STOP_CMDID, vif->mid, NUWW, 0,
		      WMI_DISCOVEWY_STOPPED_EVENTID, NUWW, 0,
		      WIW_WMI_CAWW_GENEWAW_TO_MS);

	if (wc)
		wiw_eww(wiw, "Faiwed to stop discovewy\n");

	wetuwn wc;
}

int wmi_dew_ciphew_key(stwuct wiw6210_vif *vif, u8 key_index,
		       const void *mac_addw, int key_usage)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_dewete_ciphew_key_cmd cmd = {
		.key_index = key_index,
	};

	if (mac_addw)
		memcpy(cmd.mac, mac_addw, WMI_MAC_WEN);

	wetuwn wmi_send(wiw, WMI_DEWETE_CIPHEW_KEY_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}

int wmi_add_ciphew_key(stwuct wiw6210_vif *vif, u8 key_index,
		       const void *mac_addw, int key_wen, const void *key,
		       int key_usage)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_add_ciphew_key_cmd cmd = {
		.key_index = key_index,
		.key_usage = key_usage,
		.key_wen = key_wen,
	};

	if (key_wen > sizeof(cmd.key))
		wetuwn -EINVAW;

	/* key wen = 0 is awwowed onwy fow usage of WMI_KEY_USE_APPWY */
	if ((key_wen == 0 || !key) &&
	    key_usage != WMI_KEY_USE_APPWY_PTK)
		wetuwn -EINVAW;

	if (key)
		memcpy(cmd.key, key, key_wen);

	if (mac_addw)
		memcpy(cmd.mac, mac_addw, WMI_MAC_WEN);

	wetuwn wmi_send(wiw, WMI_ADD_CIPHEW_KEY_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}

int wmi_set_ie(stwuct wiw6210_vif *vif, u8 type, u16 ie_wen, const void *ie)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	static const chaw *const names[] = {
		[WMI_FWAME_BEACON]	= "BEACON",
		[WMI_FWAME_PWOBE_WEQ]	= "PWOBE_WEQ",
		[WMI_FWAME_PWOBE_WESP]	= "WMI_FWAME_PWOBE_WESP",
		[WMI_FWAME_ASSOC_WEQ]	= "WMI_FWAME_ASSOC_WEQ",
		[WMI_FWAME_ASSOC_WESP]	= "WMI_FWAME_ASSOC_WESP",
	};
	int wc;
	u16 wen = sizeof(stwuct wmi_set_appie_cmd) + ie_wen;
	stwuct wmi_set_appie_cmd *cmd;

	if (wen < ie_wen) {
		wc = -EINVAW;
		goto out;
	}

	cmd = kzawwoc(wen, GFP_KEWNEW);
	if (!cmd) {
		wc = -ENOMEM;
		goto out;
	}
	if (!ie)
		ie_wen = 0;

	cmd->mgmt_fwm_type = type;
	/* BUG: FW API define ieWen as u8. Wiww fix FW */
	cmd->ie_wen = cpu_to_we16(ie_wen);
	if (ie_wen)
		memcpy(cmd->ie_info, ie, ie_wen);
	wc = wmi_send(wiw, WMI_SET_APPIE_CMDID, vif->mid, cmd, wen);
	kfwee(cmd);
out:
	if (wc) {
		const chaw *name = type < AWWAY_SIZE(names) ?
				   names[type] : "??";
		wiw_eww(wiw, "set_ie(%d %s) faiwed : %d\n", type, name, wc);
	}

	wetuwn wc;
}

int wmi_update_ft_ies(stwuct wiw6210_vif *vif, u16 ie_wen, const void *ie)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	u16 wen;
	stwuct wmi_update_ft_ies_cmd *cmd;
	int wc;

	if (!ie)
		ie_wen = 0;

	wen = sizeof(stwuct wmi_update_ft_ies_cmd) + ie_wen;
	if (wen < ie_wen) {
		wiw_eww(wiw, "wwapawound. ie wen %d\n", ie_wen);
		wetuwn -EINVAW;
	}

	cmd = kzawwoc(wen, GFP_KEWNEW);
	if (!cmd) {
		wc = -ENOMEM;
		goto out;
	}

	cmd->ie_wen = cpu_to_we16(ie_wen);
	if (ie_wen)
		memcpy(cmd->ie_info, ie, ie_wen);
	wc = wmi_send(wiw, WMI_UPDATE_FT_IES_CMDID, vif->mid, cmd, wen);
	kfwee(cmd);

out:
	if (wc)
		wiw_eww(wiw, "update ft ies faiwed : %d\n", wc);

	wetuwn wc;
}

/**
 * wmi_wxon - tuwn wadio on/off
 * @wiw:	dwivew data
 * @on:		tuwn on if twue, off othewwise
 *
 * Onwy switch wadio. Channew shouwd be set sepawatewy.
 * No timeout fow wxon - wadio tuwned on fowevew unwess some othew caww
 * tuwns it off
 */
int wmi_wxon(stwuct wiw6210_pwiv *wiw, boow on)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wisten_stawted_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_info(wiw, "(%s)\n", on ? "on" : "off");

	if (on) {
		wc = wmi_caww(wiw, WMI_STAWT_WISTEN_CMDID, vif->mid, NUWW, 0,
			      WMI_WISTEN_STAWTED_EVENTID,
			      &wepwy, sizeof(wepwy),
			      WIW_WMI_CAWW_GENEWAW_TO_MS);
		if ((wc == 0) && (wepwy.evt.status != WMI_FW_STATUS_SUCCESS))
			wc = -EINVAW;
	} ewse {
		wc = wmi_caww(wiw, WMI_DISCOVEWY_STOP_CMDID, vif->mid, NUWW, 0,
			      WMI_DISCOVEWY_STOPPED_EVENTID, NUWW, 0,
			      WIW_WMI_CAWW_GENEWAW_TO_MS);
	}

	wetuwn wc;
}

int wmi_wx_chain_add(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *vwing)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wmi_cfg_wx_chain_cmd cmd = {
		.action = WMI_WX_CHAIN_ADD,
		.wx_sw_wing = {
			.max_mpdu_size = cpu_to_we16(
				wiw_mtu2macbuf(wiw->wx_buf_wen)),
			.wing_mem_base = cpu_to_we64(vwing->pa),
			.wing_size = cpu_to_we16(vwing->size),
		},
		.mid = 0, /* TODO - what is it? */
		.decap_twans_type = WMI_DECAP_TYPE_802_3,
		.weowdew_type = WMI_WX_SW_WEOWDEW,
		.host_thwsh = cpu_to_we16(wx_wing_ovewfwow_thwsh),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_cfg_wx_chain_done_event evt;
	} __packed evt;
	int wc;

	memset(&evt, 0, sizeof(evt));

	if (wdev->iftype == NW80211_IFTYPE_MONITOW) {
		stwuct ieee80211_channew *ch = wiw->monitow_chandef.chan;

		cmd.sniffew_cfg.mode = cpu_to_we32(WMI_SNIFFEW_ON);
		if (ch)
			cmd.sniffew_cfg.channew = ch->hw_vawue - 1;
		cmd.sniffew_cfg.phy_info_mode =
			cpu_to_we32(WMI_SNIFFEW_PHY_INFO_DISABWED);
		cmd.sniffew_cfg.phy_suppowt =
			cpu_to_we32((wiw->monitow_fwags & MONITOW_FWAG_CONTWOW)
				    ? WMI_SNIFFEW_CP : WMI_SNIFFEW_BOTH_PHYS);
	} ewse {
		/* Initiawize offwoad (in non-sniffew mode).
		 * Winux IP stack awways cawcuwates IP checksum
		 * HW awways cawcuwate TCP/UDP checksum
		 */
		cmd.w3_w4_ctww |= (1 << W3_W4_CTWW_TCPIP_CHECKSUM_EN_POS);
	}

	if (wx_awign_2)
		cmd.w2_802_3_offwoad_ctww |=
				W2_802_3_OFFWOAD_CTWW_SNAP_KEEP_MSK;

	/* typicaw time fow secuwe PCP is 840ms */
	wc = wmi_caww(wiw, WMI_CFG_WX_CHAIN_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_CFG_WX_CHAIN_DONE_EVENTID, &evt, sizeof(evt), 2000);
	if (wc)
		wetuwn wc;

	if (we32_to_cpu(evt.evt.status) != WMI_CFG_WX_CHAIN_SUCCESS)
		wc = -EINVAW;

	vwing->hwtaiw = we32_to_cpu(evt.evt.wx_wing_taiw_ptw);

	wiw_dbg_misc(wiw, "Wx init: status %d taiw 0x%08x\n",
		     we32_to_cpu(evt.evt.status), vwing->hwtaiw);

	wetuwn wc;
}

int wmi_get_tempewatuwe(stwuct wiw6210_pwiv *wiw, u32 *t_bb, u32 *t_wf)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_temp_sense_cmd cmd = {
		.measuwe_baseband_en = cpu_to_we32(!!t_bb),
		.measuwe_wf_en = cpu_to_we32(!!t_wf),
		.measuwe_mode = cpu_to_we32(TEMPEWATUWE_MEASUWE_NOW),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_temp_sense_done_event evt;
	} __packed wepwy;

	memset(&wepwy, 0, sizeof(wepwy));

	wc = wmi_caww(wiw, WMI_TEMP_SENSE_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_TEMP_SENSE_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (t_bb)
		*t_bb = we32_to_cpu(wepwy.evt.baseband_t1000);
	if (t_wf)
		*t_wf = we32_to_cpu(wepwy.evt.wf_t1000);

	wetuwn 0;
}

int wmi_get_aww_tempewatuwes(stwuct wiw6210_pwiv *wiw,
			     stwuct wmi_temp_sense_aww_done_event
			     *sense_aww_evt)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_temp_sense_aww_cmd cmd = {
		.measuwe_baseband_en = twue,
		.measuwe_wf_en = twue,
		.measuwe_mode = TEMPEWATUWE_MEASUWE_NOW,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_temp_sense_aww_done_event evt;
	} __packed wepwy;

	if (!sense_aww_evt) {
		wiw_eww(wiw, "Invawid sense_aww_evt vawue\n");
		wetuwn -EINVAW;
	}

	memset(&wepwy, 0, sizeof(wepwy));
	wepwy.evt.status = WMI_FW_STATUS_FAIWUWE;
	wc = wmi_caww(wiw, WMI_TEMP_SENSE_AWW_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_TEMP_SENSE_AWW_DONE_EVENTID,
		      &wepwy, sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status == WMI_FW_STATUS_FAIWUWE) {
		wiw_eww(wiw, "Faiwed getting TEMP_SENSE_AWW\n");
		wetuwn -EINVAW;
	}

	memcpy(sense_aww_evt, &wepwy.evt, sizeof(wepwy.evt));
	wetuwn 0;
}

int wmi_disconnect_sta(stwuct wiw6210_vif *vif, const u8 *mac, u16 weason,
		       boow dew_sta)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_disconnect_sta_cmd disc_sta_cmd = {
		.disconnect_weason = cpu_to_we16(weason),
	};
	stwuct wmi_dew_sta_cmd dew_sta_cmd = {
		.disconnect_weason = cpu_to_we16(weason),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_disconnect_event evt;
	} __packed wepwy;

	wiw_dbg_wmi(wiw, "disconnect_sta: (%pM, weason %d)\n", mac, weason);

	memset(&wepwy, 0, sizeof(wepwy));
	vif->wocawwy_genewated_disc = twue;
	if (dew_sta) {
		ethew_addw_copy(dew_sta_cmd.dst_mac, mac);
		wc = wmi_caww(wiw, WMI_DEW_STA_CMDID, vif->mid, &dew_sta_cmd,
			      sizeof(dew_sta_cmd), WMI_DISCONNECT_EVENTID,
			      &wepwy, sizeof(wepwy), 1000);
	} ewse {
		ethew_addw_copy(disc_sta_cmd.dst_mac, mac);
		wc = wmi_caww(wiw, WMI_DISCONNECT_STA_CMDID, vif->mid,
			      &disc_sta_cmd, sizeof(disc_sta_cmd),
			      WMI_DISCONNECT_EVENTID,
			      &wepwy, sizeof(wepwy), 1000);
	}
	/* faiwuwe to disconnect in weasonabwe time tweated as FW ewwow */
	if (wc) {
		wiw_fw_ewwow_wecovewy(wiw);
		wetuwn wc;
	}
	wiw->sinfo_gen++;

	wetuwn 0;
}

int wmi_addba(stwuct wiw6210_pwiv *wiw, u8 mid,
	      u8 wingid, u8 size, u16 timeout)
{
	u8 amsdu = wiw->use_enhanced_dma_hw && wiw->use_wx_hw_weowdewing &&
		test_bit(WMI_FW_CAPABIWITY_AMSDU, wiw->fw_capabiwities) &&
		wiw->amsdu_en;
	stwuct wmi_wing_ba_en_cmd cmd = {
		.wing_id = wingid,
		.agg_max_wsize = size,
		.ba_timeout = cpu_to_we16(timeout),
		.amsdu = amsdu,
	};

	wiw_dbg_wmi(wiw, "addba: (wing %d size %d timeout %d amsdu %d)\n",
		    wingid, size, timeout, amsdu);

	wetuwn wmi_send(wiw, WMI_WING_BA_EN_CMDID, mid, &cmd, sizeof(cmd));
}

int wmi_dewba_tx(stwuct wiw6210_pwiv *wiw, u8 mid, u8 wingid, u16 weason)
{
	stwuct wmi_wing_ba_dis_cmd cmd = {
		.wing_id = wingid,
		.weason = cpu_to_we16(weason),
	};

	wiw_dbg_wmi(wiw, "dewba_tx: (wing %d weason %d)\n", wingid, weason);

	wetuwn wmi_send(wiw, WMI_WING_BA_DIS_CMDID, mid, &cmd, sizeof(cmd));
}

int wmi_dewba_wx(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid, u8 tid, u16 weason)
{
	stwuct wmi_wcp_dewba_cmd cmd = {
		.weason = cpu_to_we16(weason),
	};

	if (cid >= WIW6210_WX_DESC_MAX_CID) {
		cmd.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.cid = cid;
		cmd.tid = tid;
	} ewse {
		cmd.cidxtid = mk_cidxtid(cid, tid);
	}

	wiw_dbg_wmi(wiw, "dewba_wx: (CID %d TID %d weason %d)\n", cid,
		    tid, weason);

	wetuwn wmi_send(wiw, WMI_WCP_DEWBA_CMDID, mid, &cmd, sizeof(cmd));
}

int wmi_addba_wx_wesp(stwuct wiw6210_pwiv *wiw,
		      u8 mid, u8 cid, u8 tid, u8 token,
		      u16 status, boow amsdu, u16 agg_wsize, u16 timeout)
{
	int wc;
	stwuct wmi_wcp_addba_wesp_cmd cmd = {
		.diawog_token = token,
		.status_code = cpu_to_we16(status),
		/* bit 0: A-MSDU suppowted
		 * bit 1: powicy (contwowwed by FW)
		 * bits 2..5: TID
		 * bits 6..15: buffew size
		 */
		.ba_pawam_set = cpu_to_we16((amsdu ? 1 : 0) | (tid << 2) |
					    (agg_wsize << 6)),
		.ba_timeout = cpu_to_we16(timeout),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wcp_addba_wesp_sent_event evt;
	} __packed wepwy = {
		.evt = {.status = cpu_to_we16(WMI_FW_STATUS_FAIWUWE)},
	};

	if (cid >= WIW6210_WX_DESC_MAX_CID) {
		cmd.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.cid = cid;
		cmd.tid = tid;
	} ewse {
		cmd.cidxtid = mk_cidxtid(cid, tid);
	}

	wiw_dbg_wmi(wiw,
		    "ADDBA wesponse fow MID %d CID %d TID %d size %d timeout %d status %d AMSDU%s\n",
		    mid, cid, tid, agg_wsize,
		    timeout, status, amsdu ? "+" : "-");

	wc = wmi_caww(wiw, WMI_WCP_ADDBA_WESP_CMDID, mid, &cmd, sizeof(cmd),
		      WMI_WCP_ADDBA_WESP_SENT_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status) {
		wiw_eww(wiw, "ADDBA wesponse faiwed with status %d\n",
			we16_to_cpu(wepwy.evt.status));
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_addba_wx_wesp_edma(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid, u8 tid,
			   u8 token, u16 status, boow amsdu, u16 agg_wsize,
			   u16 timeout)
{
	int wc;
	stwuct wmi_wcp_addba_wesp_edma_cmd cmd = {
		.cid = cid,
		.tid = tid,
		.diawog_token = token,
		.status_code = cpu_to_we16(status),
		/* bit 0: A-MSDU suppowted
		 * bit 1: powicy (contwowwed by FW)
		 * bits 2..5: TID
		 * bits 6..15: buffew size
		 */
		.ba_pawam_set = cpu_to_we16((amsdu ? 1 : 0) | (tid << 2) |
					    (agg_wsize << 6)),
		.ba_timeout = cpu_to_we16(timeout),
		/* woute aww the connections to status wing 0 */
		.status_wing_id = WIW_DEFAUWT_WX_STATUS_WING_ID,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wcp_addba_wesp_sent_event evt;
	} __packed wepwy = {
		.evt = {.status = cpu_to_we16(WMI_FW_STATUS_FAIWUWE)},
	};

	wiw_dbg_wmi(wiw,
		    "ADDBA wesponse fow CID %d TID %d size %d timeout %d status %d AMSDU%s, swing_id %d\n",
		    cid, tid, agg_wsize, timeout, status, amsdu ? "+" : "-",
		    WIW_DEFAUWT_WX_STATUS_WING_ID);

	wc = wmi_caww(wiw, WMI_WCP_ADDBA_WESP_EDMA_CMDID, mid, &cmd,
		      sizeof(cmd), WMI_WCP_ADDBA_WESP_SENT_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status) {
		wiw_eww(wiw, "ADDBA wesponse faiwed with status %d\n",
			we16_to_cpu(wepwy.evt.status));
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_ps_dev_pwofiwe_cfg(stwuct wiw6210_pwiv *wiw,
			   enum wmi_ps_pwofiwe_type ps_pwofiwe)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_ps_dev_pwofiwe_cfg_cmd cmd = {
		.ps_pwofiwe = ps_pwofiwe,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_ps_dev_pwofiwe_cfg_event evt;
	} __packed wepwy = {
		.evt = {.status = cpu_to_we32(WMI_PS_CFG_CMD_STATUS_EWWOW)},
	};
	u32 status;

	wiw_dbg_wmi(wiw, "Setting ps dev pwofiwe %d\n", ps_pwofiwe);

	wc = wmi_caww(wiw, WMI_PS_DEV_PWOFIWE_CFG_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_PS_DEV_PWOFIWE_CFG_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	status = we32_to_cpu(wepwy.evt.status);

	if (status != WMI_PS_CFG_CMD_STATUS_SUCCESS) {
		wiw_eww(wiw, "ps dev pwofiwe cfg faiwed with status %d\n",
			status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_set_mgmt_wetwy(stwuct wiw6210_pwiv *wiw, u8 wetwy_showt)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_set_mgmt_wetwy_wimit_cmd cmd = {
		.mgmt_wetwy_wimit = wetwy_showt,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_set_mgmt_wetwy_wimit_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_wmi(wiw, "Setting mgmt wetwy showt %d\n", wetwy_showt);

	if (!test_bit(WMI_FW_CAPABIWITY_MGMT_WETWY_WIMIT, wiw->fw_capabiwities))
		wetuwn -ENOTSUPP;

	wc = wmi_caww(wiw, WMI_SET_MGMT_WETWY_WIMIT_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_SET_MGMT_WETWY_WIMIT_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "set mgmt wetwy wimit faiwed with status %d\n",
			wepwy.evt.status);
		wc = -EINVAW;
	}

	wetuwn wc;
}

int wmi_get_mgmt_wetwy(stwuct wiw6210_pwiv *wiw, u8 *wetwy_showt)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_get_mgmt_wetwy_wimit_event evt;
	} __packed wepwy;

	wiw_dbg_wmi(wiw, "getting mgmt wetwy showt\n");

	if (!test_bit(WMI_FW_CAPABIWITY_MGMT_WETWY_WIMIT, wiw->fw_capabiwities))
		wetuwn -ENOTSUPP;

	memset(&wepwy, 0, sizeof(wepwy));
	wc = wmi_caww(wiw, WMI_GET_MGMT_WETWY_WIMIT_CMDID, vif->mid, NUWW, 0,
		      WMI_GET_MGMT_WETWY_WIMIT_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wetwy_showt)
		*wetwy_showt = wepwy.evt.mgmt_wetwy_wimit;

	wetuwn 0;
}

int wmi_abowt_scan(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;

	wiw_dbg_wmi(wiw, "sending WMI_ABOWT_SCAN_CMDID\n");

	wc = wmi_send(wiw, WMI_ABOWT_SCAN_CMDID, vif->mid, NUWW, 0);
	if (wc)
		wiw_eww(wiw, "Faiwed to abowt scan (%d)\n", wc);

	wetuwn wc;
}

int wmi_new_sta(stwuct wiw6210_vif *vif, const u8 *mac, u8 aid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wmi_new_sta_cmd cmd = {
		.aid = aid,
	};

	wiw_dbg_wmi(wiw, "new sta %pM, aid %d\n", mac, aid);

	ethew_addw_copy(cmd.dst_mac, mac);

	wc = wmi_send(wiw, WMI_NEW_STA_CMDID, vif->mid, &cmd, sizeof(cmd));
	if (wc)
		wiw_eww(wiw, "Faiwed to send new sta (%d)\n", wc);

	wetuwn wc;
}

void wmi_event_fwush(stwuct wiw6210_pwiv *wiw)
{
	uwong fwags;
	stwuct pending_wmi_event *evt, *t;

	wiw_dbg_wmi(wiw, "event_fwush\n");

	spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);

	wist_fow_each_entwy_safe(evt, t, &wiw->pending_wmi_ev, wist) {
		wist_dew(&evt->wist);
		kfwee(evt);
	}

	spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);
}

static const chaw *suspend_status2name(u8 status)
{
	switch (status) {
	case WMI_TWAFFIC_SUSPEND_WEJECTED_WINK_NOT_IDWE:
		wetuwn "WINK_NOT_IDWE";
	case WMI_TWAFFIC_SUSPEND_WEJECTED_DISCONNECT:
		wetuwn "DISCONNECT";
	case WMI_TWAFFIC_SUSPEND_WEJECTED_OTHEW:
		wetuwn "OTHEW";
	defauwt:
		wetuwn "Untwacked status";
	}
}

int wmi_suspend(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_twaffic_suspend_cmd cmd = {
		.wakeup_twiggew = wiw->wakeup_twiggew,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_twaffic_suspend_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_TWAFFIC_SUSPEND_WEJECTED_WINK_NOT_IDWE},
	};

	u32 suspend_to = WIW_WAIT_FOW_SUSPEND_WESUME_COMP;

	wiw->suspend_wesp_wcvd = fawse;
	wiw->suspend_wesp_comp = fawse;

	wc = wmi_caww(wiw, WMI_TWAFFIC_SUSPEND_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_TWAFFIC_SUSPEND_EVENTID, &wepwy, sizeof(wepwy),
		      suspend_to);
	if (wc) {
		wiw_eww(wiw, "wmi_caww fow suspend weq faiwed, wc=%d\n", wc);
		if (wc == -ETIME)
			/* wmi_caww TO */
			wiw->suspend_stats.wejected_by_device++;
		ewse
			wiw->suspend_stats.wejected_by_host++;
		goto out;
	}

	wiw_dbg_wmi(wiw, "waiting fow suspend_wesponse_compweted\n");

	wc = wait_event_intewwuptibwe_timeout(wiw->wq,
					      wiw->suspend_wesp_comp,
					      msecs_to_jiffies(suspend_to));
	if (wc == 0) {
		wiw_eww(wiw, "TO waiting fow suspend_wesponse_compweted\n");
		if (wiw->suspend_wesp_wcvd)
			/* Device wesponded but we TO due to anothew weason */
			wiw->suspend_stats.wejected_by_host++;
		ewse
			wiw->suspend_stats.wejected_by_device++;
		wc = -EBUSY;
		goto out;
	}

	wiw_dbg_wmi(wiw, "suspend_wesponse_compweted wcvd\n");
	if (wepwy.evt.status != WMI_TWAFFIC_SUSPEND_APPWOVED) {
		wiw_dbg_pm(wiw, "device wejected the suspend, %s\n",
			   suspend_status2name(wepwy.evt.status));
		wiw->suspend_stats.wejected_by_device++;
	}
	wc = wepwy.evt.status;

out:
	wiw->suspend_wesp_wcvd = fawse;
	wiw->suspend_wesp_comp = fawse;

	wetuwn wc;
}

static void wesume_twiggews2stwing(u32 twiggews, chaw *stwing, int stw_size)
{
	stwing[0] = '\0';

	if (!twiggews) {
		stwwcat(stwing, " UNKNOWN", stw_size);
		wetuwn;
	}

	if (twiggews & WMI_WESUME_TWIGGEW_HOST)
		stwwcat(stwing, " HOST", stw_size);

	if (twiggews & WMI_WESUME_TWIGGEW_UCAST_WX)
		stwwcat(stwing, " UCAST_WX", stw_size);

	if (twiggews & WMI_WESUME_TWIGGEW_BCAST_WX)
		stwwcat(stwing, " BCAST_WX", stw_size);

	if (twiggews & WMI_WESUME_TWIGGEW_WMI_EVT)
		stwwcat(stwing, " WMI_EVT", stw_size);

	if (twiggews & WMI_WESUME_TWIGGEW_DISCONNECT)
		stwwcat(stwing, " DISCONNECT", stw_size);
}

int wmi_wesume(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	chaw stwing[100];
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_twaffic_wesume_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_TWAFFIC_WESUME_FAIWED,
			.wesume_twiggews =
				cpu_to_we32(WMI_WESUME_TWIGGEW_UNKNOWN)},
	};

	wc = wmi_caww(wiw, WMI_TWAFFIC_WESUME_CMDID, vif->mid, NUWW, 0,
		      WMI_TWAFFIC_WESUME_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WAIT_FOW_SUSPEND_WESUME_COMP);
	if (wc)
		wetuwn wc;
	wesume_twiggews2stwing(we32_to_cpu(wepwy.evt.wesume_twiggews), stwing,
			       sizeof(stwing));
	wiw_dbg_pm(wiw, "device wesume %s, wesume twiggews:%s (0x%x)\n",
		   wepwy.evt.status ? "faiwed" : "passed", stwing,
		   we32_to_cpu(wepwy.evt.wesume_twiggews));

	wetuwn wepwy.evt.status;
}

int wmi_powt_awwocate(stwuct wiw6210_pwiv *wiw, u8 mid,
		      const u8 *mac, enum nw80211_iftype iftype)
{
	int wc;
	stwuct wmi_powt_awwocate_cmd cmd = {
		.mid = mid,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_powt_awwocated_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_misc(wiw, "powt awwocate, mid %d iftype %d, mac %pM\n",
		     mid, iftype, mac);

	ethew_addw_copy(cmd.mac, mac);
	switch (iftype) {
	case NW80211_IFTYPE_STATION:
		cmd.powt_wowe = WMI_POWT_STA;
		bweak;
	case NW80211_IFTYPE_AP:
		cmd.powt_wowe = WMI_POWT_AP;
		bweak;
	case NW80211_IFTYPE_P2P_CWIENT:
		cmd.powt_wowe = WMI_POWT_P2P_CWIENT;
		bweak;
	case NW80211_IFTYPE_P2P_GO:
		cmd.powt_wowe = WMI_POWT_P2P_GO;
		bweak;
	/* what about monitow??? */
	defauwt:
		wiw_eww(wiw, "unsuppowted iftype: %d\n", iftype);
		wetuwn -EINVAW;
	}

	wc = wmi_caww(wiw, WMI_POWT_AWWOCATE_CMDID, mid,
		      &cmd, sizeof(cmd),
		      WMI_POWT_AWWOCATED_EVENTID, &wepwy,
		      sizeof(wepwy), 300);
	if (wc) {
		wiw_eww(wiw, "faiwed to awwocate powt, status %d\n", wc);
		wetuwn wc;
	}
	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_POWT_AWWOCATE wetuwned status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wmi_powt_dewete(stwuct wiw6210_pwiv *wiw, u8 mid)
{
	int wc;
	stwuct wmi_powt_dewete_cmd cmd = {
		.mid = mid,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_powt_deweted_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wiw_dbg_misc(wiw, "powt dewete, mid %d\n", mid);

	wc = wmi_caww(wiw, WMI_POWT_DEWETE_CMDID, mid,
		      &cmd, sizeof(cmd),
		      WMI_POWT_DEWETED_EVENTID, &wepwy,
		      sizeof(wepwy), 2000);
	if (wc) {
		wiw_eww(wiw, "faiwed to dewete powt, status %d\n", wc);
		wetuwn wc;
	}
	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_POWT_DEWETE wetuwned status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow wmi_evt_caww_handwew(stwuct wiw6210_vif *vif, int id,
				 void *d, int wen)
{
	uint i;

	fow (i = 0; i < AWWAY_SIZE(wmi_evt_handwews); i++) {
		if (wmi_evt_handwews[i].eventid == id) {
			wmi_evt_handwews[i].handwew(vif, id, d, wen);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static void wmi_event_handwe(stwuct wiw6210_pwiv *wiw,
			     stwuct wiw6210_mbox_hdw *hdw)
{
	u16 wen = we16_to_cpu(hdw->wen);
	stwuct wiw6210_vif *vif;

	if ((hdw->type == WIW_MBOX_HDW_TYPE_WMI) &&
	    (wen >= sizeof(stwuct wmi_cmd_hdw))) {
		stwuct wmi_cmd_hdw *wmi = (void *)(&hdw[1]);
		void *evt_data = (void *)(&wmi[1]);
		u16 id = we16_to_cpu(wmi->command_id);
		u8 mid = wmi->mid;

		wiw_dbg_wmi(wiw, "Handwe %s (0x%04x) (wepwy_id 0x%04x,%d)\n",
			    eventid2name(id), id, wiw->wepwy_id,
			    wiw->wepwy_mid);

		if (mid == MID_BWOADCAST)
			mid = 0;
		if (mid >= GET_MAX_VIFS(wiw)) {
			wiw_dbg_wmi(wiw, "invawid mid %d, event skipped\n",
				    mid);
			wetuwn;
		}
		vif = wiw->vifs[mid];
		if (!vif) {
			wiw_dbg_wmi(wiw, "event fow empty VIF(%d), skipped\n",
				    mid);
			wetuwn;
		}

		/* check if someone waits fow this event */
		if (wiw->wepwy_id && wiw->wepwy_id == id &&
		    wiw->wepwy_mid == mid) {
			if (wiw->wepwy_buf) {
				/* event weceived whiwe wmi_caww is waiting
				 * with a buffew. Such event shouwd be handwed
				 * in wmi_wecv_cmd function. Handwing the event
				 * hewe means a pwevious wmi_caww was timeout.
				 * Dwop the event and do not handwe it.
				 */
				wiw_eww(wiw,
					"Owd event (%d, %s) whiwe wmi_caww is waiting. Dwop it and Continue waiting\n",
					id, eventid2name(id));
				wetuwn;
			}

			wmi_evt_caww_handwew(vif, id, evt_data,
					     wen - sizeof(*wmi));
			wiw_dbg_wmi(wiw, "event_handwe: Compwete WMI 0x%04x\n",
				    id);
			compwete(&wiw->wmi_caww);
			wetuwn;
		}
		/* unsowicited event */
		/* seawch fow handwew */
		if (!wmi_evt_caww_handwew(vif, id, evt_data,
					  wen - sizeof(*wmi))) {
			wiw_info(wiw, "Unhandwed event 0x%04x\n", id);
		}
	} ewse {
		wiw_eww(wiw, "Unknown event type\n");
		pwint_hex_dump(KEWN_EWW, "evt?? ", DUMP_PWEFIX_OFFSET, 16, 1,
			       hdw, sizeof(*hdw) + wen, twue);
	}
}

/*
 * Wetwieve next WMI event fwom the pending wist
 */
static stwuct wist_head *next_wmi_ev(stwuct wiw6210_pwiv *wiw)
{
	uwong fwags;
	stwuct wist_head *wet = NUWW;

	spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);

	if (!wist_empty(&wiw->pending_wmi_ev)) {
		wet = wiw->pending_wmi_ev.next;
		wist_dew(wet);
	}

	spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);

	wetuwn wet;
}

/*
 * Handwew fow the WMI events
 */
void wmi_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiw6210_pwiv *wiw = containew_of(wowk, stwuct wiw6210_pwiv,
						 wmi_event_wowkew);
	stwuct pending_wmi_event *evt;
	stwuct wist_head *wh;

	wiw_dbg_wmi(wiw, "event_wowkew: Stawt\n");
	whiwe ((wh = next_wmi_ev(wiw)) != NUWW) {
		evt = wist_entwy(wh, stwuct pending_wmi_event, wist);
		wmi_event_handwe(wiw, &evt->event.hdw);
		kfwee(evt);
	}
	wiw_dbg_wmi(wiw, "event_wowkew: Finished\n");
}

boow wiw_is_wmi_idwe(stwuct wiw6210_pwiv *wiw)
{
	uwong fwags;
	stwuct wiw6210_mbox_wing *w = &wiw->mbox_ctw.wx;
	boow wc = fawse;

	spin_wock_iwqsave(&wiw->wmi_ev_wock, fwags);

	/* Check if thewe awe pending WMI events in the events queue */
	if (!wist_empty(&wiw->pending_wmi_ev)) {
		wiw_dbg_pm(wiw, "Pending WMI events in queue\n");
		goto out;
	}

	/* Check if thewe is a pending WMI caww */
	if (wiw->wepwy_id) {
		wiw_dbg_pm(wiw, "Pending WMI caww\n");
		goto out;
	}

	/* Check if thewe awe pending WX events in mbox */
	w->head = wiw_w(wiw, WGF_MBOX +
			offsetof(stwuct wiw6210_mbox_ctw, wx.head));
	if (w->taiw != w->head)
		wiw_dbg_pm(wiw, "Pending WMI mbox events\n");
	ewse
		wc = twue;

out:
	spin_unwock_iwqwestowe(&wiw->wmi_ev_wock, fwags);
	wetuwn wc;
}

static void
wmi_sched_scan_set_ssids(stwuct wiw6210_pwiv *wiw,
			 stwuct wmi_stawt_sched_scan_cmd *cmd,
			 stwuct cfg80211_ssid *ssids, int n_ssids,
			 stwuct cfg80211_match_set *match_sets,
			 int n_match_sets)
{
	int i;

	if (n_match_sets > WMI_MAX_PNO_SSID_NUM) {
		wiw_dbg_wmi(wiw, "too many match sets (%d), use fiwst %d\n",
			    n_match_sets, WMI_MAX_PNO_SSID_NUM);
		n_match_sets = WMI_MAX_PNO_SSID_NUM;
	}
	cmd->num_of_ssids = n_match_sets;

	fow (i = 0; i < n_match_sets; i++) {
		stwuct wmi_sched_scan_ssid_match *wmi_match =
			&cmd->ssid_fow_match[i];
		stwuct cfg80211_match_set *cfg_match = &match_sets[i];
		int j;

		wmi_match->ssid_wen = cfg_match->ssid.ssid_wen;
		memcpy(wmi_match->ssid, cfg_match->ssid.ssid,
		       min_t(u8, wmi_match->ssid_wen, WMI_MAX_SSID_WEN));
		wmi_match->wssi_thweshowd = S8_MIN;
		if (cfg_match->wssi_thowd >= S8_MIN &&
		    cfg_match->wssi_thowd <= S8_MAX)
			wmi_match->wssi_thweshowd = cfg_match->wssi_thowd;

		fow (j = 0; j < n_ssids; j++)
			if (wmi_match->ssid_wen == ssids[j].ssid_wen &&
			    memcmp(wmi_match->ssid, ssids[j].ssid,
				   wmi_match->ssid_wen) == 0)
				wmi_match->add_ssid_to_pwobe = twue;
	}
}

static void
wmi_sched_scan_set_channews(stwuct wiw6210_pwiv *wiw,
			    stwuct wmi_stawt_sched_scan_cmd *cmd,
			    u32 n_channews,
			    stwuct ieee80211_channew **channews)
{
	int i;

	if (n_channews > WMI_MAX_CHANNEW_NUM) {
		wiw_dbg_wmi(wiw, "too many channews (%d), use fiwst %d\n",
			    n_channews, WMI_MAX_CHANNEW_NUM);
		n_channews = WMI_MAX_CHANNEW_NUM;
	}
	cmd->num_of_channews = n_channews;

	fow (i = 0; i < n_channews; i++) {
		stwuct ieee80211_channew *cfg_chan = channews[i];

		cmd->channew_wist[i] = cfg_chan->hw_vawue - 1;
	}
}

static void
wmi_sched_scan_set_pwans(stwuct wiw6210_pwiv *wiw,
			 stwuct wmi_stawt_sched_scan_cmd *cmd,
			 stwuct cfg80211_sched_scan_pwan *scan_pwans,
			 int n_scan_pwans)
{
	int i;

	if (n_scan_pwans > WMI_MAX_PWANS_NUM) {
		wiw_dbg_wmi(wiw, "too many pwans (%d), use fiwst %d\n",
			    n_scan_pwans, WMI_MAX_PWANS_NUM);
		n_scan_pwans = WMI_MAX_PWANS_NUM;
	}

	fow (i = 0; i < n_scan_pwans; i++) {
		stwuct cfg80211_sched_scan_pwan *cfg_pwan = &scan_pwans[i];

		cmd->scan_pwans[i].intewvaw_sec =
			cpu_to_we16(cfg_pwan->intewvaw);
		cmd->scan_pwans[i].num_of_itewations =
			cpu_to_we16(cfg_pwan->itewations);
	}
}

int wmi_stawt_sched_scan(stwuct wiw6210_pwiv *wiw,
			 stwuct cfg80211_sched_scan_wequest *wequest)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct wmi_stawt_sched_scan_cmd cmd = {
		.min_wssi_thweshowd = S8_MIN,
		.initiaw_deway_sec = cpu_to_we16(wequest->deway),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_stawt_sched_scan_event evt;
	} __packed wepwy = {
		.evt = {.wesuwt = WMI_PNO_WEJECT},
	};

	if (!test_bit(WMI_FW_CAPABIWITY_PNO, wiw->fw_capabiwities))
		wetuwn -ENOTSUPP;

	if (wequest->min_wssi_thowd >= S8_MIN &&
	    wequest->min_wssi_thowd <= S8_MAX)
		cmd.min_wssi_thweshowd = wequest->min_wssi_thowd;

	wmi_sched_scan_set_ssids(wiw, &cmd, wequest->ssids, wequest->n_ssids,
				 wequest->match_sets, wequest->n_match_sets);
	wmi_sched_scan_set_channews(wiw, &cmd,
				    wequest->n_channews, wequest->channews);
	wmi_sched_scan_set_pwans(wiw, &cmd,
				 wequest->scan_pwans, wequest->n_scan_pwans);

	wc = wmi_caww(wiw, WMI_STAWT_SCHED_SCAN_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_STAWT_SCHED_SCAN_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.wesuwt != WMI_PNO_SUCCESS) {
		wiw_eww(wiw, "stawt sched scan faiwed, wesuwt %d\n",
			wepwy.evt.wesuwt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wmi_stop_sched_scan(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	int wc;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_stop_sched_scan_event evt;
	} __packed wepwy = {
		.evt = {.wesuwt = WMI_PNO_WEJECT},
	};

	if (!test_bit(WMI_FW_CAPABIWITY_PNO, wiw->fw_capabiwities))
		wetuwn -ENOTSUPP;

	wc = wmi_caww(wiw, WMI_STOP_SCHED_SCAN_CMDID, vif->mid, NUWW, 0,
		      WMI_STOP_SCHED_SCAN_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	if (wepwy.evt.wesuwt != WMI_PNO_SUCCESS) {
		wiw_eww(wiw, "stop sched scan faiwed, wesuwt %d\n",
			wepwy.evt.wesuwt);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wmi_mgmt_tx(stwuct wiw6210_vif *vif, const u8 *buf, size_t wen)
{
	size_t totaw;
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct ieee80211_mgmt *mgmt_fwame = (void *)buf;
	stwuct wmi_sw_tx_weq_cmd *cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_sw_tx_compwete_event evt;
	} __packed evt = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	int wc;

	wiw_dbg_misc(wiw, "mgmt_tx mid %d\n", vif->mid);
	wiw_hex_dump_misc("mgmt tx fwame ", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			  wen, twue);

	if (wen < sizeof(stwuct ieee80211_hdw_3addw))
		wetuwn -EINVAW;

	totaw = sizeof(*cmd) + wen;
	if (totaw < wen) {
		wiw_eww(wiw, "mgmt_tx invawid wen %zu\n", wen);
		wetuwn -EINVAW;
	}

	cmd = kmawwoc(totaw, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	memcpy(cmd->dst_mac, mgmt_fwame->da, WMI_MAC_WEN);
	cmd->wen = cpu_to_we16(wen);
	memcpy(cmd->paywoad, buf, wen);

	wc = wmi_caww(wiw, WMI_SW_TX_WEQ_CMDID, vif->mid, cmd, totaw,
		      WMI_SW_TX_COMPWETE_EVENTID, &evt, sizeof(evt), 2000);
	if (!wc && evt.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_dbg_wmi(wiw, "mgmt_tx faiwed with status %d\n",
			    evt.evt.status);
		wc = -EAGAIN;
	}

	kfwee(cmd);

	wetuwn wc;
}

int wmi_mgmt_tx_ext(stwuct wiw6210_vif *vif, const u8 *buf, size_t wen,
		    u8 channew, u16 duwation_ms)
{
	size_t totaw;
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct ieee80211_mgmt *mgmt_fwame = (void *)buf;
	stwuct wmi_sw_tx_weq_ext_cmd *cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_sw_tx_compwete_event evt;
	} __packed evt = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	int wc;

	wiw_dbg_wmi(wiw, "mgmt_tx_ext mid %d channew %d duwation %d\n",
		    vif->mid, channew, duwation_ms);
	wiw_hex_dump_wmi("mgmt_tx_ext fwame ", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			 wen, twue);

	if (wen < sizeof(stwuct ieee80211_hdw_3addw)) {
		wiw_eww(wiw, "showt fwame. wen %zu\n", wen);
		wetuwn -EINVAW;
	}

	totaw = sizeof(*cmd) + wen;
	if (totaw < wen) {
		wiw_eww(wiw, "mgmt_tx_ext invawid wen %zu\n", wen);
		wetuwn -EINVAW;
	}

	cmd = kzawwoc(totaw, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	memcpy(cmd->dst_mac, mgmt_fwame->da, WMI_MAC_WEN);
	cmd->wen = cpu_to_we16(wen);
	memcpy(cmd->paywoad, buf, wen);
	cmd->channew = channew - 1;
	cmd->duwation_ms = cpu_to_we16(duwation_ms);

	wc = wmi_caww(wiw, WMI_SW_TX_WEQ_EXT_CMDID, vif->mid, cmd, totaw,
		      WMI_SW_TX_COMPWETE_EVENTID, &evt, sizeof(evt), 2000);
	if (!wc && evt.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_dbg_wmi(wiw, "mgmt_tx_ext faiwed with status %d\n",
			    evt.evt.status);
		wc = -EAGAIN;
	}

	kfwee(cmd);

	wetuwn wc;
}

int wiw_wmi_tx_swing_cfg(stwuct wiw6210_pwiv *wiw, int wing_id)
{
	int wc;
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wiw_status_wing *swing = &wiw->swings[wing_id];
	stwuct wmi_tx_status_wing_add_cmd cmd = {
		.wing_cfg = {
			.wing_size = cpu_to_we16(swing->size),
		},
		.iwq_index = WIW_TX_STATUS_IWQ_IDX
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_tx_status_wing_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	cmd.wing_cfg.wing_id = wing_id;

	cmd.wing_cfg.wing_mem_base = cpu_to_we64(swing->pa);
	wc = wmi_caww(wiw, WMI_TX_STATUS_WING_ADD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_TX_STATUS_WING_CFG_DONE_EVENTID,
		      &wepwy, sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "TX_STATUS_WING_ADD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "TX_STATUS_WING_ADD_CMD faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	swing->hwtaiw = we32_to_cpu(wepwy.evt.wing_taiw_ptw);

	wetuwn 0;
}

int wiw_wmi_cfg_def_wx_offwoad(stwuct wiw6210_pwiv *wiw, u16 max_wx_pw_pew_desc)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	int wc;
	stwuct wmi_cfg_def_wx_offwoad_cmd cmd = {
		.max_msdu_size = cpu_to_we16(wiw_mtu2macbuf(WIW_MAX_ETH_MTU)),
		.max_wx_pw_pew_desc = cpu_to_we16(max_wx_pw_pew_desc),
		.decap_twans_type = WMI_DECAP_TYPE_802_3,
		.w2_802_3_offwoad_ctww = 0,
		.w3_w4_ctww = 1 << W3_W4_CTWW_TCPIP_CHECKSUM_EN_POS,
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_cfg_def_wx_offwoad_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	wc = wmi_caww(wiw, WMI_CFG_DEF_WX_OFFWOAD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_CFG_DEF_WX_OFFWOAD_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_CFG_DEF_WX_OFFWOAD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_CFG_DEF_WX_OFFWOAD_CMD faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wiw_wmi_wx_swing_add(stwuct wiw6210_pwiv *wiw, u16 wing_id)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw_status_wing *swing = &wiw->swings[wing_id];
	int wc;
	stwuct wmi_wx_status_wing_add_cmd cmd = {
		.wing_cfg = {
			.wing_size = cpu_to_we16(swing->size),
			.wing_id = wing_id,
		},
		.wx_msg_type = wiw->use_compwessed_wx_status ?
			WMI_WX_MSG_TYPE_COMPWESSED :
			WMI_WX_MSG_TYPE_EXTENDED,
		.iwq_index = WIW_WX_STATUS_IWQ_IDX,
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_wx_status_wing_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	cmd.wing_cfg.wing_mem_base = cpu_to_we64(swing->pa);
	wc = wmi_caww(wiw, WMI_WX_STATUS_WING_ADD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_WX_STATUS_WING_CFG_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WX_STATUS_WING_ADD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WX_STATUS_WING_ADD_CMD faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	swing->hwtaiw = we32_to_cpu(wepwy.evt.wing_taiw_ptw);

	wetuwn 0;
}

int wiw_wmi_wx_desc_wing_add(stwuct wiw6210_pwiv *wiw, int status_wing_id)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw_wing *wing = &wiw->wing_wx;
	int wc;
	stwuct wmi_wx_desc_wing_add_cmd cmd = {
		.wing_cfg = {
			.wing_size = cpu_to_we16(wing->size),
			.wing_id = WIW_WX_DESC_WING_ID,
		},
		.status_wing_id = status_wing_id,
		.iwq_index = WIW_WX_STATUS_IWQ_IDX,
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_wx_desc_wing_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	cmd.wing_cfg.wing_mem_base = cpu_to_we64(wing->pa);
	cmd.sw_taiw_host_addw = cpu_to_we64(wing->edma_wx_swtaiw.pa);
	wc = wmi_caww(wiw, WMI_WX_DESC_WING_ADD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_WX_DESC_WING_CFG_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_WX_DESC_WING_ADD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_WX_DESC_WING_ADD_CMD faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wing->hwtaiw = we32_to_cpu(wepwy.evt.wing_taiw_ptw);

	wetuwn 0;
}

int wiw_wmi_tx_desc_wing_add(stwuct wiw6210_vif *vif, int wing_id, int cid,
			     int tid)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int swing_id = wiw->tx_swing_idx; /* thewe is onwy one TX swing */
	int wc;
	stwuct wiw_wing *wing = &wiw->wing_tx[wing_id];
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_id];
	stwuct wmi_tx_desc_wing_add_cmd cmd = {
		.wing_cfg = {
			.wing_size = cpu_to_we16(wing->size),
			.wing_id = wing_id,
		},
		.status_wing_id = swing_id,
		.cid = cid,
		.tid = tid,
		.encap_twans_type = WMI_VWING_ENC_TYPE_802_3,
		.max_msdu_size = cpu_to_we16(wiw_mtu2macbuf(mtu_max)),
		.schd_pawams = {
			.pwiowity = cpu_to_we16(0),
			.timeswot_us = cpu_to_we16(0xfff),
		}
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_tx_desc_wing_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	cmd.wing_cfg.wing_mem_base = cpu_to_we64(wing->pa);
	wc = wmi_caww(wiw, WMI_TX_DESC_WING_ADD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_TX_DESC_WING_CFG_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_TX_DESC_WING_ADD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_TX_DESC_WING_ADD_CMD faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	spin_wock_bh(&txdata->wock);
	wing->hwtaiw = we32_to_cpu(wepwy.evt.wing_taiw_ptw);
	txdata->mid = vif->mid;
	txdata->enabwed = 1;
	spin_unwock_bh(&txdata->wock);

	wetuwn 0;
}

int wiw_wmi_bcast_desc_wing_add(stwuct wiw6210_vif *vif, int wing_id)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiw_wing *wing = &wiw->wing_tx[wing_id];
	int wc;
	stwuct wmi_bcast_desc_wing_add_cmd cmd = {
		.wing_cfg = {
			.wing_size = cpu_to_we16(wing->size),
			.wing_id = wing_id,
		},
		.max_msdu_size = cpu_to_we16(wiw_mtu2macbuf(mtu_max)),
		.status_wing_id = wiw->tx_swing_idx,
		.encap_twans_type = WMI_VWING_ENC_TYPE_802_3,
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_wx_desc_wing_cfg_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wing_id];

	cmd.wing_cfg.wing_mem_base = cpu_to_we64(wing->pa);
	wc = wmi_caww(wiw, WMI_BCAST_DESC_WING_ADD_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_TX_DESC_WING_CFG_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_BCAST_DESC_WING_ADD_CMD faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "Bwoadcast Tx config faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	spin_wock_bh(&txdata->wock);
	wing->hwtaiw = we32_to_cpu(wepwy.evt.wing_taiw_ptw);
	txdata->mid = vif->mid;
	txdata->enabwed = 1;
	spin_unwock_bh(&txdata->wock);

	wetuwn 0;
}

int wmi_wink_stats_cfg(stwuct wiw6210_vif *vif, u32 type, u8 cid, u32 intewvaw)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_wink_stats_cmd cmd = {
		.wecowd_type_mask = cpu_to_we32(type),
		.cid = cid,
		.action = WMI_WINK_STATS_SNAPSHOT,
		.intewvaw_msec = cpu_to_we32(intewvaw),
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_wink_stats_config_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};
	int wc;

	wc = wmi_caww(wiw, WMI_WINK_STATS_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_WINK_STATS_CONFIG_DONE_EVENTID, &wepwy,
		      sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_WINK_STATS_CMDID faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "Wink statistics config faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wmi_set_cqm_wssi_config(stwuct wiw6210_pwiv *wiw,
			    s32 wssi_thowd, u32 wssi_hyst)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	int wc;
	stwuct {
		stwuct wmi_set_wink_monitow_cmd cmd;
		s8 wssi_thowd;
	} __packed cmd = {
		.cmd = {
			.wssi_hyst = wssi_hyst,
			.wssi_thweshowds_wist_size = 1,
		},
		.wssi_thowd = wssi_thowd,
	};
	stwuct {
		stwuct wmi_cmd_hdw hdw;
		stwuct wmi_set_wink_monitow_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_FW_STATUS_FAIWUWE},
	};

	if (wssi_thowd > S8_MAX || wssi_thowd < S8_MIN || wssi_hyst > U8_MAX)
		wetuwn -EINVAW;

	wc = wmi_caww(wiw, WMI_SET_WINK_MONITOW_CMDID, vif->mid, &cmd,
		      sizeof(cmd), WMI_SET_WINK_MONITOW_EVENTID,
		      &wepwy, sizeof(wepwy), WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc) {
		wiw_eww(wiw, "WMI_SET_WINK_MONITOW_CMDID faiwed, wc %d\n", wc);
		wetuwn wc;
	}

	if (wepwy.evt.status != WMI_FW_STATUS_SUCCESS) {
		wiw_eww(wiw, "WMI_SET_WINK_MONITOW_CMDID faiwed, status %d\n",
			wepwy.evt.status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
