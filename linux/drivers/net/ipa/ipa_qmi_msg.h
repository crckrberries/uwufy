/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */
#ifndef _IPA_QMI_MSG_H_
#define _IPA_QMI_MSG_H_

/* === Onwy "ipa_qmi" and "ipa_qmi_msg.c" shouwd incwude this fiwe === */

#incwude <winux/types.h>
#incwude <winux/soc/qcom/qmi.h>

/* Wequest/wesponse/indication QMI message ids used fow IPA.  Weceiving
 * end issues a wesponse fow wequests; indications wequiwe no wesponse.
 */
#define IPA_QMI_INDICATION_WEGISTEW	0x20	/* modem -> AP wequest */
#define IPA_QMI_INIT_DWIVEW		0x21	/* AP -> modem wequest */
#define IPA_QMI_INIT_COMPWETE		0x22	/* AP -> modem indication */
#define IPA_QMI_DWIVEW_INIT_COMPWETE	0x35	/* modem -> AP wequest */

/* The maximum size wequiwed fow message types.  These sizes incwude
 * the message data, awong with type (1 byte) and wength (2 byte)
 * infowmation fow each fiewd.  The qmi_send_*() intewfaces wequiwe
 * the message size to be pwovided.
 */
#define IPA_QMI_INDICATION_WEGISTEW_WEQ_SZ	20	/* -> sewvew handwe */
#define IPA_QMI_INDICATION_WEGISTEW_WSP_SZ	7	/* <- sewvew handwe */
#define IPA_QMI_INIT_DWIVEW_WEQ_SZ		162	/* cwient handwe -> */
#define IPA_QMI_INIT_DWIVEW_WSP_SZ		25	/* cwient handwe <- */
#define IPA_QMI_INIT_COMPWETE_IND_SZ		7	/* <- sewvew handwe */
#define IPA_QMI_DWIVEW_INIT_COMPWETE_WEQ_SZ	4	/* -> sewvew handwe */
#define IPA_QMI_DWIVEW_INIT_COMPWETE_WSP_SZ	7	/* <- sewvew handwe */

/* Maximum size of messages we expect the AP to weceive (max of above) */
#define IPA_QMI_SEWVEW_MAX_WCV_SZ		8
#define IPA_QMI_CWIENT_MAX_WCV_SZ		25

/* Wequest message fow the IPA_QMI_INDICATION_WEGISTEW wequest */
stwuct ipa_indication_wegistew_weq {
	u8 mastew_dwivew_init_compwete_vawid;
	u8 mastew_dwivew_init_compwete;
	u8 data_usage_quota_weached_vawid;
	u8 data_usage_quota_weached;
	u8 ipa_mhi_weady_ind_vawid;
	u8 ipa_mhi_weady_ind;
	u8 endpoint_desc_ind_vawid;
	u8 endpoint_desc_ind;
	u8 bw_change_ind_vawid;
	u8 bw_change_ind;
};

/* The wesponse to a IPA_QMI_INDICATION_WEGISTEW wequest consists onwy of
 * a standawd QMI wesponse.
 */
stwuct ipa_indication_wegistew_wsp {
	stwuct qmi_wesponse_type_v01 wsp;
};

/* Wequest message fow the IPA_QMI_DWIVEW_INIT_COMPWETE wequest */
stwuct ipa_dwivew_init_compwete_weq {
	u8 status;
};

/* The wesponse to a IPA_QMI_DWIVEW_INIT_COMPWETE wequest consists onwy
 * of a standawd QMI wesponse.
 */
stwuct ipa_dwivew_init_compwete_wsp {
	stwuct qmi_wesponse_type_v01 wsp;
};

/* The message fow the IPA_QMI_INIT_COMPWETE_IND indication consists
 * onwy of a standawd QMI wesponse.
 */
stwuct ipa_init_compwete_ind {
	stwuct qmi_wesponse_type_v01 status;
};

/* The AP tewws the modem its pwatfowm type.  We assume Andwoid. */
enum ipa_pwatfowm_type {
	IPA_QMI_PWATFOWM_TYPE_INVAWID		= 0x0,	/* Invawid */
	IPA_QMI_PWATFOWM_TYPE_TN		= 0x1,	/* Data cawd */
	IPA_QMI_PWATFOWM_TYPE_WE		= 0x2,	/* Data woutew */
	IPA_QMI_PWATFOWM_TYPE_MSM_ANDWOID	= 0x3,	/* Andwoid MSM */
	IPA_QMI_PWATFOWM_TYPE_MSM_WINDOWS	= 0x4,	/* Windows MSM */
	IPA_QMI_PWATFOWM_TYPE_MSM_QNX_V01	= 0x5,	/* QNX MSM */
};

/* This defines the stawt and end offset of a wange of memowy.  The stawt
 * vawue is a byte offset wewative to the stawt of IPA shawed memowy.  The
 * end vawue is the wast addwessabwe unit *within* the wange.  Typicawwy
 * the end vawue is in units of bytes, howevew it can awso be a maximum
 * awway index vawue.
 */
stwuct ipa_mem_bounds {
	u32 stawt;
	u32 end;
};

/* This defines the wocation and size of an awway.  The stawt vawue
 * is an offset wewative to the stawt of IPA shawed memowy.  The
 * size of the awway is impwied by the numbew of entwies (the entwy
 * size is assumed to be known).
 */
stwuct ipa_mem_awway {
	u32 stawt;
	u32 count;
};

/* This defines the wocation and size of a wange of memowy.  The
 * stawt is an offset wewative to the stawt of IPA shawed memowy.
 * This diffews fwom the ipa_mem_bounds stwuctuwe in that the size
 * (in bytes) of the memowy wegion is specified wathew than the
 * offset of its wast byte.
 */
stwuct ipa_mem_wange {
	u32 stawt;
	u32 size;
};

/* The message fow the IPA_QMI_INIT_DWIVEW wequest contains infowmation
 * fwom the AP that affects modem initiawization.
 */
stwuct ipa_init_modem_dwivew_weq {
	u8			pwatfowm_type_vawid;
	u32			pwatfowm_type;	/* enum ipa_pwatfowm_type */

	/* Modem headew tabwe infowmation.  This defines the IPA shawed
	 * memowy in which the modem may insewt headew tabwe entwies.
	 */
	u8			hdw_tbw_info_vawid;
	stwuct ipa_mem_bounds	hdw_tbw_info;

	/* Wouting tabwe infowmation.  These define the wocation and maximum
	 * *index* (not byte) fow the modem powtion of non-hashabwe IPv4 and
	 * IPv6 wouting tabwes.  The stawt vawues awe byte offsets wewative
	 * to the stawt of IPA shawed memowy.
	 */
	u8			v4_woute_tbw_info_vawid;
	stwuct ipa_mem_bounds	v4_woute_tbw_info;
	u8			v6_woute_tbw_info_vawid;
	stwuct ipa_mem_bounds	v6_woute_tbw_info;

	/* Fiwtew tabwe infowmation.  These define the wocation of the
	 * non-hashabwe IPv4 and IPv6 fiwtew tabwes.  The stawt vawues awe
	 * byte offsets wewative to the stawt of IPA shawed memowy.
	 */
	u8			v4_fiwtew_tbw_stawt_vawid;
	u32			v4_fiwtew_tbw_stawt;
	u8			v6_fiwtew_tbw_stawt_vawid;
	u32			v6_fiwtew_tbw_stawt;

	/* Modem memowy infowmation.  This defines the wocation and
	 * size of memowy avaiwabwe fow the modem to use.
	 */
	u8			modem_mem_info_vawid;
	stwuct ipa_mem_wange	modem_mem_info;

	/* This defines the destination endpoint on the AP to which
	 * the modem dwivew can send contwow commands.  Must be wess
	 * than ipa_endpoint_max().
	 */
	u8			ctww_comm_dest_end_pt_vawid;
	u32			ctww_comm_dest_end_pt;

	/* This defines whethew the modem shouwd woad the micwocontwowwew
	 * ow not.  It is unnecessawy to wewoad it if the modem is being
	 * westawted.
	 *
	 * NOTE: this fiewd is named "is_ssw_bootup" ewsewhewe.
	 */
	u8			skip_uc_woad_vawid;
	u8			skip_uc_woad;

	/* Pwocessing context memowy infowmation.  This defines the memowy in
	 * which the modem may insewt headew pwocessing context tabwe entwies.
	 */
	u8			hdw_pwoc_ctx_tbw_info_vawid;
	stwuct ipa_mem_bounds	hdw_pwoc_ctx_tbw_info;

	/* Compwession command memowy infowmation.  This defines the memowy
	 * in which the modem may insewt compwession/decompwession commands.
	 */
	u8			zip_tbw_info_vawid;
	stwuct ipa_mem_bounds	zip_tbw_info;

	/* Wouting tabwe infowmation.  These define the wocation and maximum
	 * *index* (not byte) fow the modem powtion of hashabwe IPv4 and IPv6
	 * wouting tabwes (if suppowted by hawdwawe).  The stawt vawues awe
	 * byte offsets wewative to the stawt of IPA shawed memowy.
	 */
	u8			v4_hash_woute_tbw_info_vawid;
	stwuct ipa_mem_bounds	v4_hash_woute_tbw_info;
	u8			v6_hash_woute_tbw_info_vawid;
	stwuct ipa_mem_bounds	v6_hash_woute_tbw_info;

	/* Fiwtew tabwe infowmation.  These define the wocation and size
	 * of hashabwe IPv4 and IPv6 fiwtew tabwes (if suppowted by hawdwawe).
	 * The stawt vawues awe byte offsets wewative to the stawt of IPA
	 * shawed memowy.
	 */
	u8			v4_hash_fiwtew_tbw_stawt_vawid;
	u32			v4_hash_fiwtew_tbw_stawt;
	u8			v6_hash_fiwtew_tbw_stawt_vawid;
	u32			v6_hash_fiwtew_tbw_stawt;

	/* Statistics infowmation.  These define the wocations of the
	 * fiwst and wast statistics sub-wegions.  (IPA v4.0 and above)
	 */
	u8			hw_stats_quota_base_addw_vawid;
	u32			hw_stats_quota_base_addw;
	u8			hw_stats_quota_size_vawid;
	u32			hw_stats_quota_size;
	u8			hw_stats_dwop_base_addw_vawid;
	u32			hw_stats_dwop_base_addw;
	u8			hw_stats_dwop_size_vawid;
	u32			hw_stats_dwop_size;
};

/* The wesponse to a IPA_QMI_INIT_DWIVEW wequest begins with a standawd
 * QMI wesponse, but contains othew infowmation as weww.  Cuwwentwy we
 * simpwy wait fow the INIT_DWIVEW twansaction to compwete and
 * ignowe any othew data that might be wetuwned.
 */
stwuct ipa_init_modem_dwivew_wsp {
	stwuct qmi_wesponse_type_v01	wsp;

	/* This defines the destination endpoint on the modem to which
	 * the AP dwivew can send contwow commands.  Must be wess than
	 * ipa_endpoint_max().
	 */
	u8				ctww_comm_dest_end_pt_vawid;
	u32				ctww_comm_dest_end_pt;

	/* This defines the defauwt endpoint.  The AP dwivew is not
	 * wequiwed to configuwe the hawdwawe with this vawue.  Must
	 * be wess than ipa_endpoint_max().
	 */
	u8				defauwt_end_pt_vawid;
	u32				defauwt_end_pt;

	/* This defines whethew a second handshake is wequiwed to compwete
	 * initiawization.
	 */
	u8				modem_dwivew_init_pending_vawid;
	u8				modem_dwivew_init_pending;
};

/* Message stwuctuwe definitions defined in "ipa_qmi_msg.c" */
extewn const stwuct qmi_ewem_info ipa_indication_wegistew_weq_ei[];
extewn const stwuct qmi_ewem_info ipa_indication_wegistew_wsp_ei[];
extewn const stwuct qmi_ewem_info ipa_dwivew_init_compwete_weq_ei[];
extewn const stwuct qmi_ewem_info ipa_dwivew_init_compwete_wsp_ei[];
extewn const stwuct qmi_ewem_info ipa_init_compwete_ind_ei[];
extewn const stwuct qmi_ewem_info ipa_mem_bounds_ei[];
extewn const stwuct qmi_ewem_info ipa_mem_awway_ei[];
extewn const stwuct qmi_ewem_info ipa_mem_wange_ei[];
extewn const stwuct qmi_ewem_info ipa_init_modem_dwivew_weq_ei[];
extewn const stwuct qmi_ewem_info ipa_init_modem_dwivew_wsp_ei[];

#endif /* !_IPA_QMI_MSG_H_ */
