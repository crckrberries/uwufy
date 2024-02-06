// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_ioctw_wtw.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define  _WTW871X_IOCTW_WTW_C_

#incwude <winux/wndis.h>
#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wwan_bssdef.h"
#incwude "wifi.h"
#incwude "wtw871x_ioctw.h"
#incwude "wtw871x_ioctw_set.h"
#incwude "wtw871x_ioctw_wtw.h"
#incwude "mp_custom_oid.h"
#incwude "wtw871x_mp.h"
#incwude "wtw871x_mp_ioctw.h"

uint oid_wt_get_signaw_quawity_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_smaww_packet_cwc_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >=  sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
				padaptew->wecvpwiv.wx_smawwpacket_cwceww;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_middwe_packet_cwc_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >=  sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
				padaptew->wecvpwiv.wx_middwepacket_cwceww;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_wawge_packet_cwc_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >=  sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
				 padaptew->wecvpwiv.wx_wawgepacket_cwceww;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_tx_wetwy_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_wx_wetwy_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_wx_totaw_packet_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >=  sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
					 padaptew->wecvpwiv.wx_pkts +
					 padaptew->wecvpwiv.wx_dwop;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_tx_beacon_ok_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_tx_beacon_eww_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_wx_icv_eww_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		*(uint *)poid_paw_pwiv->infowmation_buf =
					 padaptew->wecvpwiv.wx_icv_eww;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_set_encwyption_awgowithm_hdw(stwuct oid_paw_pwiv
						*poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_pweambwe_mode_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	u32 pweambwemode = 0;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		if (padaptew->wegistwypwiv.pweambwe == PWEAMBWE_WONG)
			pweambwemode = 0;
		ewse if (padaptew->wegistwypwiv.pweambwe == PWEAMBWE_AUTO)
			pweambwemode = 1;
		ewse if (padaptew->wegistwypwiv.pweambwe == PWEAMBWE_SHOWT)
			pweambwemode = 2;
		*(u32 *)poid_paw_pwiv->infowmation_buf = pweambwemode;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_ap_ip_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_channewpwan_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	stwuct eepwom_pwiv *peepwompwiv = &padaptew->eepwompwiv;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	*(u16 *)poid_paw_pwiv->infowmation_buf = peepwompwiv->channew_pwan;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_set_channewpwan_hdw(stwuct oid_paw_pwiv
				       *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	stwuct eepwom_pwiv *peepwompwiv = &padaptew->eepwompwiv;

	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	peepwompwiv->channew_pwan = *(u16 *)poid_paw_pwiv->infowmation_buf;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_set_pweambwe_mode_hdw(stwuct oid_paw_pwiv
					 *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	u32 pweambwemode = 0;

	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		pweambwemode = *(u32 *)poid_paw_pwiv->infowmation_buf;
		if (pweambwemode == 0)
			padaptew->wegistwypwiv.pweambwe = PWEAMBWE_WONG;
		ewse if (pweambwemode == 1)
			padaptew->wegistwypwiv.pweambwe = PWEAMBWE_AUTO;
		ewse if (pweambwemode == 2)
			padaptew->wegistwypwiv.pweambwe = PWEAMBWE_SHOWT;
		*(u32 *)poid_paw_pwiv->infowmation_buf = pweambwemode;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_set_bcn_intvw_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_dedicate_pwobe_hdw(stwuct oid_paw_pwiv
				      *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_totaw_tx_bytes_hdw(stwuct oid_paw_pwiv
					  *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
						 padaptew->xmitpwiv.tx_bytes;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_totaw_wx_bytes_hdw(stwuct oid_paw_pwiv
					  *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		*(u32 *)poid_paw_pwiv->infowmation_buf =
					   padaptew->wecvpwiv.wx_bytes;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_cuwwent_tx_powew_wevew_hdw(stwuct oid_paw_pwiv
					      *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_enc_key_mismatch_count_hdw(stwuct oid_paw_pwiv
						  *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_enc_key_match_count_hdw(stwuct oid_paw_pwiv
					       *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_channew_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	stwuct	mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct NDIS_802_11_CONFIGUWATION *pnic_Config;
	u32   channewnum;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (check_fwstate(pmwmepwiv, _FW_WINKED) ||
	    check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE))
		pnic_Config = &pmwmepwiv->cuw_netwowk.netwowk.Configuwation;
	ewse
		pnic_Config = &padaptew->wegistwypwiv.dev_netwowk.Configuwation;
	channewnum = pnic_Config->DSConfig;
	*(u32 *)poid_paw_pwiv->infowmation_buf = channewnum;
	*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_hawdwawe_wadio_off_hdw(stwuct oid_paw_pwiv
			 *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_key_mismatch_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_suppowted_wiwewess_mode_hdw(stwuct oid_paw_pwiv
					       *poid_paw_pwiv)
{
	u32 uwInfo = 0;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen >= sizeof(u32)) {
		uwInfo |= 0x0100; /* WIWEWESS_MODE_B */
		uwInfo |= 0x0200; /* WIWEWESS_MODE_G */
		uwInfo |= 0x0400; /* WIWEWESS_MODE_A */
		*(u32 *) poid_paw_pwiv->infowmation_buf = uwInfo;
		*poid_paw_pwiv->bytes_ww = poid_paw_pwiv->infowmation_buf_wen;
	} ewse {
		wetuwn WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_channew_wist_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_scan_in_pwogwess_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_fowced_data_wate_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_wiwewess_mode_fow_scan_wist_hdw(stwuct oid_paw_pwiv
						   *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_get_bss_wiwewess_mode_hdw(stwuct oid_paw_pwiv
					     *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_scan_with_magic_packet_hdw(stwuct oid_paw_pwiv
					      *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_ap_get_associated_station_wist_hdw(stwuct oid_paw_pwiv
						      *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_ap_switch_into_ap_mode_hdw(stwuct oid_paw_pwiv*
					      poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_ap_suppowted_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_ap_set_passphwase_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_pwo_wf_wwite_wegistwy_hdw(stwuct oid_paw_pwiv*
					     poid_paw_pwiv)
{
	uint status = WNDIS_STATUS_SUCCESS;
	stwuct _adaptew *Adaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != SET_OID) /* QUEWY_OID */
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen ==
	   (sizeof(unsigned wong) * 3)) {
		if (w8712_setwfweg_cmd(Adaptew,
			*(unsigned chaw *)poid_paw_pwiv->infowmation_buf,
			(unsigned wong)(*((unsigned wong *)
					poid_paw_pwiv->infowmation_buf + 2))))
			status = WNDIS_STATUS_NOT_ACCEPTED;
	} ewse {
		status = WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn status;
}

uint oid_wt_pwo_wf_wead_wegistwy_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	uint status = WNDIS_STATUS_SUCCESS;
	stwuct _adaptew *Adaptew = poid_paw_pwiv->adaptew_context;

	if (poid_paw_pwiv->type_of_oid != SET_OID) /* QUEWY_OID */
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	if (poid_paw_pwiv->infowmation_buf_wen == (sizeof(unsigned wong) *
						   3)) {
		if (Adaptew->mppwiv.act_in_pwogwess) {
			status = WNDIS_STATUS_NOT_ACCEPTED;
		} ewse {
			/* init wowkpawam */
			Adaptew->mppwiv.act_in_pwogwess = twue;
			Adaptew->mppwiv.wowkpawam.bcompweted = fawse;
			Adaptew->mppwiv.wowkpawam.act_type = MPT_WEAD_WF;
			Adaptew->mppwiv.wowkpawam.io_offset = *(unsigned wong *)
						poid_paw_pwiv->infowmation_buf;
			Adaptew->mppwiv.wowkpawam.io_vawue = 0xcccccccc;

		/* WegOffsetVawue	- The offset of WF wegistew to wead.
		 * WegDataWidth	- The data width of WF wegistew to wead.
		 * WegDataVawue	- The vawue to wead.
		 * WegOffsetVawue = *((unsigned wong *)InfowmationBuffew);
		 * WegDataWidth = *((unsigned wong *)InfowmationBuffew+1);
		 * WegDataVawue =  *((unsigned wong *)InfowmationBuffew+2);
		 */
			if (w8712_getwfweg_cmd(Adaptew,
			    *(unsigned chaw *)poid_paw_pwiv->infowmation_buf,
			    (unsigned chaw *)&Adaptew->mppwiv.wowkpawam.io_vawue
			    ))
				status = WNDIS_STATUS_NOT_ACCEPTED;
		}
	} ewse {
		status = WNDIS_STATUS_INVAWID_WENGTH;
	}
	wetuwn status;
}

enum _CONNECT_STATE_ {
	CHECKINGSTATUS,
	ASSOCIATED,
	ADHOCMODE,
	NOTASSOCIATED
};

uint oid_wt_get_connect_state_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	stwuct _adaptew *padaptew = poid_paw_pwiv->adaptew_context;
	stwuct mwme_pwiv *pmwmepwiv = &(padaptew->mwmepwiv);
	u32 uwInfo;

	if (poid_paw_pwiv->type_of_oid != QUEWY_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	/* nStatus==0	CheckingStatus
	 * nStatus==1	Associated
	 * nStatus==2	AdHocMode
	 * nStatus==3	NotAssociated
	 */
	if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING))
		uwInfo = CHECKINGSTATUS;
	ewse if (check_fwstate(pmwmepwiv, _FW_WINKED))
		uwInfo = ASSOCIATED;
	ewse if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE))
		uwInfo = ADHOCMODE;
	ewse
		uwInfo = NOTASSOCIATED;
	*(u32 *)poid_paw_pwiv->infowmation_buf = uwInfo;
	*poid_paw_pwiv->bytes_ww =  poid_paw_pwiv->infowmation_buf_wen;
	wetuwn WNDIS_STATUS_SUCCESS;
}

uint oid_wt_set_defauwt_key_id_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv)
{
	if (poid_paw_pwiv->type_of_oid != SET_OID)
		wetuwn WNDIS_STATUS_NOT_ACCEPTED;
	wetuwn WNDIS_STATUS_SUCCESS;
}
