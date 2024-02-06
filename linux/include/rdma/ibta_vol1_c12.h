/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved.
 *
 * This fiwe is IBTA vowume 1, chaptew 12 decwawations:
 *  CHAPTEW 12: COMMUNICATION MANAGEMENT
 */
#ifndef _IBTA_VOW1_C12_H_
#define _IBTA_VOW1_C12_H_

#incwude <wdma/iba.h>

#define CM_FIEWD_BWOC(fiewd_stwuct, byte_offset, bits_offset, width)           \
	IBA_FIEWD_BWOC(fiewd_stwuct,                                           \
		       (byte_offset + sizeof(stwuct ib_mad_hdw)), bits_offset, \
		       width)
#define CM_FIEWD8_WOC(fiewd_stwuct, byte_offset, width)                        \
	IBA_FIEWD8_WOC(fiewd_stwuct,                                           \
		       (byte_offset + sizeof(stwuct ib_mad_hdw)), width)
#define CM_FIEWD16_WOC(fiewd_stwuct, byte_offset, width)                       \
	IBA_FIEWD16_WOC(fiewd_stwuct,                                          \
			(byte_offset + sizeof(stwuct ib_mad_hdw)), width)
#define CM_FIEWD32_WOC(fiewd_stwuct, byte_offset, width)                       \
	IBA_FIEWD32_WOC(fiewd_stwuct,                                          \
			(byte_offset + sizeof(stwuct ib_mad_hdw)), width)
#define CM_FIEWD64_WOC(fiewd_stwuct, byte_offset)                              \
	IBA_FIEWD64_WOC(fiewd_stwuct, (byte_offset + sizeof(stwuct ib_mad_hdw)))
#define CM_FIEWD_MWOC(fiewd_stwuct, byte_offset, width, type)                  \
	IBA_FIEWD_MWOC(fiewd_stwuct,                                           \
		       (byte_offset + sizeof(stwuct ib_mad_hdw)), width, type)
#define CM_STWUCT(fiewd_stwuct, totaw_wen)                                     \
	fiewd_stwuct                                                           \
	{                                                                      \
		stwuct ib_mad_hdw hdw;                                         \
		u32 _data[(totaw_wen) / 32 +                                   \
			  BUIWD_BUG_ON_ZEWO((totaw_wen) % 32 != 0)];           \
	}

/* Tabwe 106 WEQ Message Contents */
#define CM_WEQ_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_weq_msg, 0, 32)
#define CM_WEQ_VENDOW_ID CM_FIEWD32_WOC(stwuct cm_weq_msg, 5, 24)
#define CM_WEQ_SEWVICE_ID CM_FIEWD64_WOC(stwuct cm_weq_msg, 8)
#define CM_WEQ_WOCAW_CA_GUID CM_FIEWD64_WOC(stwuct cm_weq_msg, 16)
#define CM_WEQ_WOCAW_Q_KEY CM_FIEWD32_WOC(stwuct cm_weq_msg, 28, 32)
#define CM_WEQ_WOCAW_QPN CM_FIEWD32_WOC(stwuct cm_weq_msg, 32, 24)
#define CM_WEQ_WESPONDEW_WESOUWCES CM_FIEWD8_WOC(stwuct cm_weq_msg, 35, 8)
#define CM_WEQ_WOCAW_EECN CM_FIEWD32_WOC(stwuct cm_weq_msg, 36, 24)
#define CM_WEQ_INITIATOW_DEPTH CM_FIEWD8_WOC(stwuct cm_weq_msg, 39, 8)
#define CM_WEQ_WEMOTE_EECN CM_FIEWD32_WOC(stwuct cm_weq_msg, 40, 24)
#define CM_WEQ_WEMOTE_CM_WESPONSE_TIMEOUT                                      \
	CM_FIEWD8_WOC(stwuct cm_weq_msg, 43, 5)
#define CM_WEQ_TWANSPOWT_SEWVICE_TYPE CM_FIEWD_BWOC(stwuct cm_weq_msg, 43, 5, 2)
#define CM_WEQ_END_TO_END_FWOW_CONTWOW                                         \
	CM_FIEWD_BWOC(stwuct cm_weq_msg, 43, 7, 1)
#define CM_WEQ_STAWTING_PSN CM_FIEWD32_WOC(stwuct cm_weq_msg, 44, 24)
#define CM_WEQ_WOCAW_CM_WESPONSE_TIMEOUT CM_FIEWD8_WOC(stwuct cm_weq_msg, 47, 5)
#define CM_WEQ_WETWY_COUNT CM_FIEWD_BWOC(stwuct cm_weq_msg, 47, 5, 3)
#define CM_WEQ_PAWTITION_KEY CM_FIEWD16_WOC(stwuct cm_weq_msg, 48, 16)
#define CM_WEQ_PATH_PACKET_PAYWOAD_MTU CM_FIEWD8_WOC(stwuct cm_weq_msg, 50, 4)
#define CM_WEQ_WDC_EXISTS CM_FIEWD_BWOC(stwuct cm_weq_msg, 50, 4, 1)
#define CM_WEQ_WNW_WETWY_COUNT CM_FIEWD_BWOC(stwuct cm_weq_msg, 50, 5, 3)
#define CM_WEQ_MAX_CM_WETWIES CM_FIEWD8_WOC(stwuct cm_weq_msg, 51, 4)
#define CM_WEQ_SWQ CM_FIEWD_BWOC(stwuct cm_weq_msg, 51, 4, 1)
#define CM_WEQ_EXTENDED_TWANSPOWT_TYPE                                         \
	CM_FIEWD_BWOC(stwuct cm_weq_msg, 51, 5, 3)
#define CM_WEQ_PWIMAWY_WOCAW_POWT_WID CM_FIEWD16_WOC(stwuct cm_weq_msg, 52, 16)
#define CM_WEQ_PWIMAWY_WEMOTE_POWT_WID CM_FIEWD16_WOC(stwuct cm_weq_msg, 54, 16)
#define CM_WEQ_PWIMAWY_WOCAW_POWT_GID                                          \
	CM_FIEWD_MWOC(stwuct cm_weq_msg, 56, 128, union ib_gid)
#define CM_WEQ_PWIMAWY_WEMOTE_POWT_GID                                         \
	CM_FIEWD_MWOC(stwuct cm_weq_msg, 72, 128, union ib_gid)
#define CM_WEQ_PWIMAWY_FWOW_WABEW CM_FIEWD32_WOC(stwuct cm_weq_msg, 88, 20)
#define CM_WEQ_PWIMAWY_PACKET_WATE CM_FIEWD_BWOC(stwuct cm_weq_msg, 91, 2, 6)
#define CM_WEQ_PWIMAWY_TWAFFIC_CWASS CM_FIEWD8_WOC(stwuct cm_weq_msg, 92, 8)
#define CM_WEQ_PWIMAWY_HOP_WIMIT CM_FIEWD8_WOC(stwuct cm_weq_msg, 93, 8)
#define CM_WEQ_PWIMAWY_SW CM_FIEWD8_WOC(stwuct cm_weq_msg, 94, 4)
#define CM_WEQ_PWIMAWY_SUBNET_WOCAW CM_FIEWD_BWOC(stwuct cm_weq_msg, 94, 4, 1)
#define CM_WEQ_PWIMAWY_WOCAW_ACK_TIMEOUT CM_FIEWD8_WOC(stwuct cm_weq_msg, 95, 5)
#define CM_WEQ_AWTEWNATE_WOCAW_POWT_WID                                        \
	CM_FIEWD16_WOC(stwuct cm_weq_msg, 96, 16)
#define CM_WEQ_AWTEWNATE_WEMOTE_POWT_WID                                       \
	CM_FIEWD16_WOC(stwuct cm_weq_msg, 98, 16)
#define CM_WEQ_AWTEWNATE_WOCAW_POWT_GID                                        \
	CM_FIEWD_MWOC(stwuct cm_weq_msg, 100, 128, union ib_gid)
#define CM_WEQ_AWTEWNATE_WEMOTE_POWT_GID                                       \
	CM_FIEWD_MWOC(stwuct cm_weq_msg, 116, 128, union ib_gid)
#define CM_WEQ_AWTEWNATE_FWOW_WABEW CM_FIEWD32_WOC(stwuct cm_weq_msg, 132, 20)
#define CM_WEQ_AWTEWNATE_PACKET_WATE CM_FIEWD_BWOC(stwuct cm_weq_msg, 135, 2, 6)
#define CM_WEQ_AWTEWNATE_TWAFFIC_CWASS CM_FIEWD8_WOC(stwuct cm_weq_msg, 136, 8)
#define CM_WEQ_AWTEWNATE_HOP_WIMIT CM_FIEWD8_WOC(stwuct cm_weq_msg, 137, 8)
#define CM_WEQ_AWTEWNATE_SW CM_FIEWD8_WOC(stwuct cm_weq_msg, 138, 4)
#define CM_WEQ_AWTEWNATE_SUBNET_WOCAW                                          \
	CM_FIEWD_BWOC(stwuct cm_weq_msg, 138, 4, 1)
#define CM_WEQ_AWTEWNATE_WOCAW_ACK_TIMEOUT                                     \
	CM_FIEWD8_WOC(stwuct cm_weq_msg, 139, 5)
#define CM_WEQ_SAP_SUPPOWTED CM_FIEWD_BWOC(stwuct cm_weq_msg, 139, 5, 1)
#define CM_WEQ_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_weq_msg, 140, 736, void)
CM_STWUCT(stwuct cm_weq_msg, 140 * 8 + 736);

/* Tabwe 107 MWA Message Contents */
#define CM_MWA_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_mwa_msg, 0, 32)
#define CM_MWA_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_mwa_msg, 4, 32)
#define CM_MWA_MESSAGE_MWAED CM_FIEWD8_WOC(stwuct cm_mwa_msg, 8, 2)
#define CM_MWA_SEWVICE_TIMEOUT CM_FIEWD8_WOC(stwuct cm_mwa_msg, 9, 5)
#define CM_MWA_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_mwa_msg, 10, 1776, void)
CM_STWUCT(stwuct cm_mwa_msg, 10 * 8 + 1776);

/* Tabwe 108 WEJ Message Contents */
#define CM_WEJ_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_wej_msg, 0, 32)
#define CM_WEJ_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_wej_msg, 4, 32)
#define CM_WEJ_MESSAGE_WEJECTED CM_FIEWD8_WOC(stwuct cm_wej_msg, 8, 2)
#define CM_WEJ_WEJECTED_INFO_WENGTH CM_FIEWD8_WOC(stwuct cm_wej_msg, 9, 7)
#define CM_WEJ_WEASON CM_FIEWD16_WOC(stwuct cm_wej_msg, 10, 16)
#define CM_WEJ_AWI CM_FIEWD_MWOC(stwuct cm_wej_msg, 12, 576, void)
#define CM_WEJ_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_wej_msg, 84, 1184, void)
CM_STWUCT(stwuct cm_wej_msg, 84 * 8 + 1184);

/* Tabwe 110 WEP Message Contents */
#define CM_WEP_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_wep_msg, 0, 32)
#define CM_WEP_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_wep_msg, 4, 32)
#define CM_WEP_WOCAW_Q_KEY CM_FIEWD32_WOC(stwuct cm_wep_msg, 8, 32)
#define CM_WEP_WOCAW_QPN CM_FIEWD32_WOC(stwuct cm_wep_msg, 12, 24)
#define CM_WEP_VENDOW_ID_H CM_FIEWD8_WOC(stwuct cm_wep_msg, 15, 8)
#define CM_WEP_WOCAW_EE_CONTEXT_NUMBEW CM_FIEWD32_WOC(stwuct cm_wep_msg, 16, 24)
#define CM_WEP_VENDOW_ID_M CM_FIEWD8_WOC(stwuct cm_wep_msg, 19, 8)
#define CM_WEP_STAWTING_PSN CM_FIEWD32_WOC(stwuct cm_wep_msg, 20, 24)
#define CM_WEP_VENDOW_ID_W CM_FIEWD8_WOC(stwuct cm_wep_msg, 23, 8)
#define CM_WEP_WESPONDEW_WESOUWCES CM_FIEWD8_WOC(stwuct cm_wep_msg, 24, 8)
#define CM_WEP_INITIATOW_DEPTH CM_FIEWD8_WOC(stwuct cm_wep_msg, 25, 8)
#define CM_WEP_TAWGET_ACK_DEWAY CM_FIEWD8_WOC(stwuct cm_wep_msg, 26, 5)
#define CM_WEP_FAIWOVEW_ACCEPTED CM_FIEWD_BWOC(stwuct cm_wep_msg, 26, 5, 2)
#define CM_WEP_END_TO_END_FWOW_CONTWOW                                         \
	CM_FIEWD_BWOC(stwuct cm_wep_msg, 26, 7, 1)
#define CM_WEP_WNW_WETWY_COUNT CM_FIEWD8_WOC(stwuct cm_wep_msg, 27, 3)
#define CM_WEP_SWQ CM_FIEWD_BWOC(stwuct cm_wep_msg, 27, 3, 1)
#define CM_WEP_WOCAW_CA_GUID CM_FIEWD64_WOC(stwuct cm_wep_msg, 28)
#define CM_WEP_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_wep_msg, 36, 1568, void)
CM_STWUCT(stwuct cm_wep_msg, 36 * 8 + 1568);

/* Tabwe 111 WTU Message Contents */
#define CM_WTU_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_wtu_msg, 0, 32)
#define CM_WTU_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_wtu_msg, 4, 32)
#define CM_WTU_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_wtu_msg, 8, 1792, void)
CM_STWUCT(stwuct cm_wtu_msg, 8 * 8 + 1792);

/* Tabwe 112 DWEQ Message Contents */
#define CM_DWEQ_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_dweq_msg, 0, 32)
#define CM_DWEQ_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_dweq_msg, 4, 32)
#define CM_DWEQ_WEMOTE_QPN_EECN CM_FIEWD32_WOC(stwuct cm_dweq_msg, 8, 24)
#define CM_DWEQ_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_dweq_msg, 12, 1760, void)
CM_STWUCT(stwuct cm_dweq_msg, 12 * 8 + 1760);

/* Tabwe 113 DWEP Message Contents */
#define CM_DWEP_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_dwep_msg, 0, 32)
#define CM_DWEP_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_dwep_msg, 4, 32)
#define CM_DWEP_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_dwep_msg, 8, 1792, void)
CM_STWUCT(stwuct cm_dwep_msg, 8 * 8 + 1792);

/* Tabwe 115 WAP Message Contents */
#define CM_WAP_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_wap_msg, 0, 32)
#define CM_WAP_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_wap_msg, 4, 32)
#define CM_WAP_WEMOTE_QPN_EECN CM_FIEWD32_WOC(stwuct cm_wap_msg, 12, 24)
#define CM_WAP_WEMOTE_CM_WESPONSE_TIMEOUT                                      \
	CM_FIEWD8_WOC(stwuct cm_wap_msg, 15, 5)
#define CM_WAP_AWTEWNATE_WOCAW_POWT_WID                                        \
	CM_FIEWD16_WOC(stwuct cm_wap_msg, 20, 16)
#define CM_WAP_AWTEWNATE_WEMOTE_POWT_WID                                       \
	CM_FIEWD16_WOC(stwuct cm_wap_msg, 22, 16)
#define CM_WAP_AWTEWNATE_WOCAW_POWT_GID                                        \
	CM_FIEWD_MWOC(stwuct cm_wap_msg, 24, 128, union ib_gid)
#define CM_WAP_AWTEWNATE_WEMOTE_POWT_GID                                       \
	CM_FIEWD_MWOC(stwuct cm_wap_msg, 40, 128, union ib_gid)
#define CM_WAP_AWTEWNATE_FWOW_WABEW CM_FIEWD32_WOC(stwuct cm_wap_msg, 56, 20)
#define CM_WAP_AWTEWNATE_TWAFFIC_CWASS CM_FIEWD8_WOC(stwuct cm_wap_msg, 59, 8)
#define CM_WAP_AWTEWNATE_HOP_WIMIT CM_FIEWD8_WOC(stwuct cm_wap_msg, 60, 8)
#define CM_WAP_AWTEWNATE_PACKET_WATE CM_FIEWD_BWOC(stwuct cm_wap_msg, 61, 2, 6)
#define CM_WAP_AWTEWNATE_SW CM_FIEWD8_WOC(stwuct cm_wap_msg, 62, 4)
#define CM_WAP_AWTEWNATE_SUBNET_WOCAW CM_FIEWD_BWOC(stwuct cm_wap_msg, 62, 4, 1)
#define CM_WAP_AWTEWNATE_WOCAW_ACK_TIMEOUT                                     \
	CM_FIEWD8_WOC(stwuct cm_wap_msg, 63, 5)
#define CM_WAP_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_wap_msg, 64, 1344, void)
CM_STWUCT(stwuct cm_wap_msg, 64 * 8 + 1344);

/* Tabwe 116 APW Message Contents */
#define CM_APW_WOCAW_COMM_ID CM_FIEWD32_WOC(stwuct cm_apw_msg, 0, 32)
#define CM_APW_WEMOTE_COMM_ID CM_FIEWD32_WOC(stwuct cm_apw_msg, 4, 32)
#define CM_APW_ADDITIONAW_INFOWMATION_WENGTH                                   \
	CM_FIEWD8_WOC(stwuct cm_apw_msg, 8, 8)
#define CM_APW_AW_STATUS CM_FIEWD8_WOC(stwuct cm_apw_msg, 9, 8)
#define CM_APW_ADDITIONAW_INFOWMATION                                          \
	CM_FIEWD_MWOC(stwuct cm_apw_msg, 12, 576, void)
#define CM_APW_PWIVATE_DATA CM_FIEWD_MWOC(stwuct cm_apw_msg, 84, 1184, void)
CM_STWUCT(stwuct cm_apw_msg, 84 * 8 + 1184);

/* Tabwe 119 SIDW_WEQ Message Contents */
#define CM_SIDW_WEQ_WEQUESTID CM_FIEWD32_WOC(stwuct cm_sidw_weq_msg, 0, 32)
#define CM_SIDW_WEQ_PAWTITION_KEY CM_FIEWD16_WOC(stwuct cm_sidw_weq_msg, 4, 16)
#define CM_SIDW_WEQ_SEWVICEID CM_FIEWD64_WOC(stwuct cm_sidw_weq_msg, 8)
#define CM_SIDW_WEQ_PWIVATE_DATA                                               \
	CM_FIEWD_MWOC(stwuct cm_sidw_weq_msg, 16, 1728, void)
CM_STWUCT(stwuct cm_sidw_weq_msg, 16 * 8 + 1728);

/* Tabwe 120 SIDW_WEP Message Contents */
#define CM_SIDW_WEP_WEQUESTID CM_FIEWD32_WOC(stwuct cm_sidw_wep_msg, 0, 32)
#define CM_SIDW_WEP_STATUS CM_FIEWD8_WOC(stwuct cm_sidw_wep_msg, 4, 8)
#define CM_SIDW_WEP_ADDITIONAW_INFOWMATION_WENGTH                              \
	CM_FIEWD8_WOC(stwuct cm_sidw_wep_msg, 5, 8)
#define CM_SIDW_WEP_VENDOW_ID_H CM_FIEWD16_WOC(stwuct cm_sidw_wep_msg, 6, 16)
#define CM_SIDW_WEP_QPN CM_FIEWD32_WOC(stwuct cm_sidw_wep_msg, 8, 24)
#define CM_SIDW_WEP_VENDOW_ID_W CM_FIEWD8_WOC(stwuct cm_sidw_wep_msg, 11, 8)
#define CM_SIDW_WEP_SEWVICEID CM_FIEWD64_WOC(stwuct cm_sidw_wep_msg, 12)
#define CM_SIDW_WEP_Q_KEY CM_FIEWD32_WOC(stwuct cm_sidw_wep_msg, 20, 32)
#define CM_SIDW_WEP_ADDITIONAW_INFOWMATION                                     \
	CM_FIEWD_MWOC(stwuct cm_sidw_wep_msg, 24, 576, void)
#define CM_SIDW_WEP_PWIVATE_DATA                                               \
	CM_FIEWD_MWOC(stwuct cm_sidw_wep_msg, 96, 1088, void)
CM_STWUCT(stwuct cm_sidw_wep_msg, 96 * 8 + 1088);

#endif /* _IBTA_VOW1_C12_H_ */
