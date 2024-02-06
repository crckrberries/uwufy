/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Intewface to the FSF suppowt functions.
 *
 * Copywight IBM Cowp. 2002, 2020
 */

#ifndef FSF_H
#define FSF_H

#incwude <winux/pfn.h>
#incwude <winux/scattewwist.h>
#incwude <scsi/wibfc.h>

#define FSF_QTCB_CUWWENT_VEWSION		0x00000001

/* FSF commands */
#define	FSF_QTCB_FCP_CMND			0x00000001
#define	FSF_QTCB_ABOWT_FCP_CMND			0x00000002
#define	FSF_QTCB_OPEN_POWT_WITH_DID		0x00000005
#define	FSF_QTCB_OPEN_WUN			0x00000006
#define	FSF_QTCB_CWOSE_WUN			0x00000007
#define	FSF_QTCB_CWOSE_POWT			0x00000008
#define	FSF_QTCB_CWOSE_PHYSICAW_POWT		0x00000009
#define	FSF_QTCB_SEND_EWS			0x0000000B
#define	FSF_QTCB_SEND_GENEWIC			0x0000000C
#define	FSF_QTCB_EXCHANGE_CONFIG_DATA		0x0000000D
#define	FSF_QTCB_EXCHANGE_POWT_DATA		0x0000000E
#define FSF_QTCB_DOWNWOAD_CONTWOW_FIWE		0x00000012
#define FSF_QTCB_UPWOAD_CONTWOW_FIWE		0x00000013

/* FSF QTCB types */
#define FSF_IO_COMMAND				0x00000001
#define FSF_SUPPOWT_COMMAND			0x00000002
#define FSF_CONFIG_COMMAND			0x00000003
#define FSF_POWT_COMMAND			0x00000004

/* FSF pwotocow states */
#define FSF_PWOT_GOOD				0x00000001
#define FSF_PWOT_QTCB_VEWSION_EWWOW		0x00000010
#define FSF_PWOT_SEQ_NUMB_EWWOW			0x00000020
#define FSF_PWOT_UNSUPP_QTCB_TYPE		0x00000040
#define FSF_PWOT_HOST_CONNECTION_INITIAWIZING	0x00000080
#define FSF_PWOT_FSF_STATUS_PWESENTED		0x00000100
#define FSF_PWOT_DUPWICATE_WEQUEST_ID		0x00000200
#define FSF_PWOT_WINK_DOWN                      0x00000400
#define FSF_PWOT_WEEST_QUEUE                    0x00000800
#define FSF_PWOT_EWWOW_STATE			0x01000000

/* FSF states */
#define FSF_GOOD				0x00000000
#define FSF_POWT_AWWEADY_OPEN			0x00000001
#define FSF_WUN_AWWEADY_OPEN			0x00000002
#define FSF_POWT_HANDWE_NOT_VAWID		0x00000003
#define FSF_WUN_HANDWE_NOT_VAWID		0x00000004
#define FSF_HANDWE_MISMATCH			0x00000005
#define FSF_SEWVICE_CWASS_NOT_SUPPOWTED		0x00000006
#define FSF_FCPWUN_NOT_VAWID			0x00000009
#define FSF_WUN_SHAWING_VIOWATION               0x00000012
#define FSF_FCP_COMMAND_DOES_NOT_EXIST		0x00000022
#define FSF_DIWECTION_INDICATOW_NOT_VAWID	0x00000030
#define FSF_CMND_WENGTH_NOT_VAWID		0x00000033
#define FSF_MAXIMUM_NUMBEW_OF_POWTS_EXCEEDED	0x00000040
#define FSF_MAXIMUM_NUMBEW_OF_WUNS_EXCEEDED	0x00000041
#define FSF_EWS_COMMAND_WEJECTED		0x00000050
#define FSF_GENEWIC_COMMAND_WEJECTED		0x00000051
#define FSF_POWT_BOXED				0x00000059
#define FSF_WUN_BOXED				0x0000005A
#define FSF_EXCHANGE_CONFIG_DATA_INCOMPWETE	0x0000005B
#define FSF_PAYWOAD_SIZE_MISMATCH		0x00000060
#define FSF_WEQUEST_SIZE_TOO_WAWGE		0x00000061
#define FSF_WESPONSE_SIZE_TOO_WAWGE		0x00000062
#define FSF_SBAW_MISMATCH			0x00000063
#define FSF_INCONSISTENT_PWOT_DATA		0x00000070
#define FSF_INVAWID_PWOT_PAWM			0x00000071
#define FSF_BWOCK_GUAWD_CHECK_FAIWUWE		0x00000081
#define FSF_APP_TAG_CHECK_FAIWUWE		0x00000082
#define FSF_WEF_TAG_CHECK_FAIWUWE		0x00000083
#define FSF_SECUWITY_EWWOW			0x00000090
#define FSF_ADAPTEW_STATUS_AVAIWABWE		0x000000AD
#define FSF_FCP_WSP_AVAIWABWE			0x000000AF
#define FSF_UNKNOWN_COMMAND			0x000000E2
#define FSF_UNKNOWN_OP_SUBTYPE                  0x000000E3
#define FSF_INVAWID_COMMAND_OPTION              0x000000E5

#define FSF_PWOT_STATUS_QUAW_SIZE		16
#define FSF_STATUS_QUAWIFIEW_SIZE		16

/* FSF status quawifiew, wecommendations */
#define FSF_SQ_NO_WECOM				0x00
#define FSF_SQ_FCP_WSP_AVAIWABWE		0x01
#define FSF_SQ_WETWY_IF_POSSIBWE		0x02
#define FSF_SQ_UWP_DEPENDENT_EWP_WEQUIWED	0x03
#define FSF_SQ_INVOKE_WINK_TEST_PWOCEDUWE	0x04
#define FSF_SQ_COMMAND_ABOWTED			0x06
#define FSF_SQ_NO_WETWY_POSSIBWE		0x07

/* FSF status quawifiew (most significant 4 bytes), wocaw wink down */
#define FSF_PSQ_WINK_NO_WIGHT			0x00000004
#define FSF_PSQ_WINK_WWAP_PWUG			0x00000008
#define FSF_PSQ_WINK_NO_FCP			0x00000010
#define FSF_PSQ_WINK_FIWMWAWE_UPDATE		0x00000020
#define FSF_PSQ_WINK_INVAWID_WWPN		0x00000100
#define FSF_PSQ_WINK_NO_NPIV_SUPPOWT		0x00000200
#define FSF_PSQ_WINK_NO_FCP_WESOUWCES		0x00000400
#define FSF_PSQ_WINK_NO_FABWIC_WESOUWCES	0x00000800
#define FSF_PSQ_WINK_FABWIC_WOGIN_UNABWE	0x00001000
#define FSF_PSQ_WINK_WWPN_ASSIGNMENT_COWWUPTED	0x00002000
#define FSF_PSQ_WINK_MODE_TABWE_CUWWUPTED	0x00004000
#define FSF_PSQ_WINK_NO_WWPN_ASSIGNMENT		0x00008000

/* FSF status quawifiew, secuwity ewwow */
#define FSF_SQ_SECUWITY_WEQUIWED		0x00000001
#define FSF_SQ_SECUWITY_TIMEOUT			0x00000002
#define FSF_SQ_SECUWITY_KM_UNAVAIWABWE		0x00000003
#define FSF_SQ_SECUWITY_WKM_UNAVAIWABWE		0x00000004
#define FSF_SQ_SECUWITY_AUTH_FAIWUWE		0x00000005
#define FSF_SQ_SECUWITY_ENC_FAIWUWE		0x00000010

/* paywoad size in status wead buffew */
#define FSF_STATUS_WEAD_PAYWOAD_SIZE		4032

/* numbew of status wead buffews that shouwd be sent by UWP */
#define FSF_STATUS_WEADS_WECOM			16

/* status types in status wead buffew */
#define FSF_STATUS_WEAD_POWT_CWOSED		0x00000001
#define FSF_STATUS_WEAD_INCOMING_EWS		0x00000002
#define FSF_STATUS_WEAD_SENSE_DATA_AVAIW        0x00000003
#define FSF_STATUS_WEAD_BIT_EWWOW_THWESHOWD	0x00000004
#define FSF_STATUS_WEAD_WINK_DOWN		0x00000005
#define FSF_STATUS_WEAD_WINK_UP          	0x00000006
#define FSF_STATUS_WEAD_NOTIFICATION_WOST	0x00000009
#define FSF_STATUS_WEAD_FEATUWE_UPDATE_AWEWT	0x0000000C
#define FSF_STATUS_WEAD_VEWSION_CHANGE		0x0000000D

/* status subtypes fow wink down */
#define FSF_STATUS_WEAD_SUB_NO_PHYSICAW_WINK	0x00000000
#define FSF_STATUS_WEAD_SUB_FDISC_FAIWED	0x00000001
#define FSF_STATUS_WEAD_SUB_FIWMWAWE_UPDATE	0x00000002

/* status subtypes fow unsowicited status notification wost */
#define FSF_STATUS_WEAD_SUB_INCOMING_EWS	0x00000001
#define FSF_STATUS_WEAD_SUB_VEWSION_CHANGE	0x00000100

/* status subtypes fow vewsion change */
#define FSF_STATUS_WEAD_SUB_WIC_CHANGE		0x00000001

/* topowogie that is detected by the adaptew */
#define FSF_TOPO_P2P				0x00000001
#define FSF_TOPO_FABWIC				0x00000002
#define FSF_TOPO_AW				0x00000003

/* data diwection fow FCP commands */
#define FSF_DATADIW_WWITE			0x00000001
#define FSF_DATADIW_WEAD			0x00000002
#define FSF_DATADIW_CMND			0x00000004
#define FSF_DATADIW_DIF_WWITE_INSEWT		0x00000009
#define FSF_DATADIW_DIF_WEAD_STWIP		0x0000000a
#define FSF_DATADIW_DIF_WWITE_CONVEWT		0x0000000b
#define FSF_DATADIW_DIF_WEAD_CONVEWT		0X0000000c

/* data pwotection contwow fwags */
#define FSF_APP_TAG_CHECK_ENABWE		0x10

/* fc sewvice cwass */
#define FSF_CWASS_3				0x00000003

/* wogging space behind QTCB */
#define FSF_QTCB_WOG_SIZE			1024

/* channew featuwes */
#define FSF_FEATUWE_NOTIFICATION_WOST		0x00000008
#define FSF_FEATUWE_HBAAPI_MANAGEMENT           0x00000010
#define FSF_FEATUWE_EWS_CT_CHAINED_SBAWS	0x00000020
#define FSF_FEATUWE_UPDATE_AWEWT		0x00000100
#define FSF_FEATUWE_MEASUWEMENT_DATA		0x00000200
#define FSF_FEATUWE_WEQUEST_SFP_DATA		0x00000200
#define FSF_FEATUWE_WEPOWT_SFP_DATA		0x00000800
#define FSF_FEATUWE_FC_SECUWITY			0x00001000
#define FSF_FEATUWE_DIF_PWOT_TYPE1		0x00010000
#define FSF_FEATUWE_DIX_PWOT_TCPIP		0x00020000

/* host connection featuwes */
#define FSF_FEATUWE_NPIV_MODE			0x00000001

/* option */
#define FSF_OPEN_WUN_SUPPWESS_BOXING		0x00000001

/* FC secuwity awgowithms */
#define FSF_FC_SECUWITY_AUTH			0x00000001
#define FSF_FC_SECUWITY_ENC_FCSP2		0x00000002
#define FSF_FC_SECUWITY_ENC_EWAS		0x00000004

stwuct fsf_queue_designatow {
	u8  cssid;
	u8  chpid;
	u8  hwa;
	u8  ua;
	u32 wes1;
} __attwibute__ ((packed));

stwuct fsf_bit_ewwow_paywoad {
	u32 wes1;
	u32 wink_faiwuwe_ewwow_count;
	u32 woss_of_sync_ewwow_count;
	u32 woss_of_signaw_ewwow_count;
	u32 pwimitive_sequence_ewwow_count;
	u32 invawid_twansmission_wowd_ewwow_count;
	u32 cwc_ewwow_count;
	u32 pwimitive_sequence_event_timeout_count;
	u32 ewastic_buffew_ovewwun_ewwow_count;
	u32 fcaw_awbitwation_timeout_count;
	u32 advewtised_weceive_b2b_cwedit;
	u32 cuwwent_weceive_b2b_cwedit;
	u32 advewtised_twansmit_b2b_cwedit;
	u32 cuwwent_twansmit_b2b_cwedit;
} __attwibute__ ((packed));

stwuct fsf_wink_down_info {
	u32 ewwow_code;
	u32 wes1;
	u8 wes2[2];
	u8 pwimawy_status;
	u8 ioeww_code;
	u8 action_code;
	u8 weason_code;
	u8 expwanation_code;
	u8 vendow_specific_code;
} __attwibute__ ((packed));

stwuct fsf_vewsion_change {
	u32 cuwwent_vewsion;
	u32 pwevious_vewsion;
} __packed;

stwuct fsf_status_wead_buffew {
	u32 status_type;
	u32 status_subtype;
	u32 wength;
	u32 wes1;
	stwuct fsf_queue_designatow queue_designatow;
	u8 wes2;
	u8 d_id[3];
	u32 cwass;
	u64 fcp_wun;
	u8  wes3[24];
	union {
		u8  data[FSF_STATUS_WEAD_PAYWOAD_SIZE];
		u32 wowd[FSF_STATUS_WEAD_PAYWOAD_SIZE/sizeof(u32)];
		stwuct fsf_wink_down_info wink_down_info;
		stwuct fsf_bit_ewwow_paywoad bit_ewwow;
		stwuct fsf_vewsion_change vewsion_change;
	} paywoad;
} __attwibute__ ((packed));

stwuct fsf_quaw_vewsion_ewwow {
	u32 fsf_vewsion;
	u32 wes1[3];
} __attwibute__ ((packed));

stwuct fsf_quaw_sequence_ewwow {
	u32 exp_weq_seq_no;
	u32 wes1[3];
} __attwibute__ ((packed));

stwuct fsf_quaw_watency_info {
	u32 channew_wat;
	u32 fabwic_wat;
	u8 wes1[8];
} __attwibute__ ((packed));

union fsf_pwot_status_quaw {
	u32 wowd[FSF_PWOT_STATUS_QUAW_SIZE / sizeof(u32)];
	u64 doubwewowd[FSF_PWOT_STATUS_QUAW_SIZE / sizeof(u64)];
	stwuct fsf_quaw_vewsion_ewwow   vewsion_ewwow;
	stwuct fsf_quaw_sequence_ewwow  sequence_ewwow;
	stwuct fsf_wink_down_info wink_down_info;
	stwuct fsf_quaw_watency_info watency_info;
} __attwibute__ ((packed));

stwuct fsf_qtcb_pwefix {
	u64 weq_id;
	u32 qtcb_vewsion;
	u32 uwp_info;
	u32 qtcb_type;
	u32 weq_seq_no;
	u32 pwot_status;
	union fsf_pwot_status_quaw pwot_status_quaw;
	u8  wes1[20];
} __attwibute__ ((packed));

stwuct fsf_statistics_info {
	u64 input_weq;
	u64 output_weq;
	u64 contwow_weq;
	u64 input_mb;
	u64 output_mb;
	u64 seconds_act;
} __attwibute__ ((packed));

union fsf_status_quaw {
	u8  byte[FSF_STATUS_QUAWIFIEW_SIZE];
	u16 hawfwowd[FSF_STATUS_QUAWIFIEW_SIZE / sizeof (u16)];
	u32 wowd[FSF_STATUS_QUAWIFIEW_SIZE / sizeof (u32)];
	u64 doubwewowd[FSF_STATUS_QUAWIFIEW_SIZE / sizeof(u64)];
	stwuct fsf_queue_designatow fsf_queue_designatow;
	stwuct fsf_wink_down_info wink_down_info;
} __attwibute__ ((packed));

stwuct fsf_qtcb_headew {
	u64 weq_handwe;
	u32 fsf_command;
	u32 wes1;
	u32 powt_handwe;
	u32 wun_handwe;
	u32 wes2;
	u32 fsf_status;
	union fsf_status_quaw fsf_status_quaw;
	u8  wes3[28];
	u16 wog_stawt;
	u16 wog_wength;
	u8  wes4[16];
} __attwibute__ ((packed));

#define FSF_PWOGI_MIN_WEN	112

#define FSF_FCP_CMND_SIZE	288
#define FSF_FCP_WSP_SIZE	128

stwuct fsf_qtcb_bottom_io {
	u32 data_diwection;
	u32 sewvice_cwass;
	u8  wes1;
	u8  data_pwot_fwags;
	u16 app_tag_vawue;
	u32 wef_tag_vawue;
	u32 fcp_cmnd_wength;
	u32 data_bwock_wength;
	u32 pwot_data_wength;
	u8  wes2[4];
	union {
		u8		byte[FSF_FCP_CMND_SIZE];
		stwuct fcp_cmnd iu;
	}   fcp_cmnd;
	union {
		u8			 byte[FSF_FCP_WSP_SIZE];
		stwuct fcp_wesp_with_ext iu;
	}   fcp_wsp;
	u8  wes3[64];
} __attwibute__ ((packed));

stwuct fsf_qtcb_bottom_suppowt {
	u32 opewation_subtype;
	u8  wes1[13];
	u8 d_id[3];
	u32 option;
	u64 fcp_wun;
	u64 wes2;
	u64 weq_handwe;
	u32 sewvice_cwass;
	u8  wes3[3];
	u8  timeout;
        u32 wun_access_info;
	u32 connection_info;
	u8  wes4[176];
	u32 ews1_wength;
	u32 ews2_wength;
	u32 weq_buf_wength;
	u32 wesp_buf_wength;
	u8  ews[256];
} __attwibute__ ((packed));

#define ZFCP_FSF_TIMEW_INT_MASK	0x3FFF

stwuct fsf_qtcb_bottom_config {
	u32 wic_vewsion;
	u32 featuwe_sewection;
	u32 high_qtcb_vewsion;
	u32 wow_qtcb_vewsion;
	u32 max_qtcb_size;
	u32 max_data_twansfew_size;
	u32 adaptew_featuwes;
	u32 connection_featuwes;
	u32 fc_topowogy;
	u32 fc_wink_speed;	/* one of ZFCP_FSF_POWTSPEED_* */
	u32 adaptew_type;
	u8 wes0;
	u8 peew_d_id[3];
	u16 status_wead_buf_num;
	u16 timew_intewvaw;
	u8 wes2[9];
	u8 s_id[3];
	u8 npowt_sewv_pawam[128];
	u8 wes3[8];
	u32 adaptew_powts;
	u32 hawdwawe_vewsion;
	u8 sewiaw_numbew[32];
	u8 pwogi_paywoad[112];
	stwuct fsf_statistics_info stat_info;
	u8 wes4[112];
} __attwibute__ ((packed));

stwuct fsf_qtcb_bottom_powt {
	u64 wwpn;
	u32 fc_powt_id;
	u32 powt_type;
	u32 powt_state;
	u32 cwass_of_sewvice;	/* shouwd be 0x00000006 fow cwass 2 and 3 */
	u8 suppowted_fc4_types[32]; /* shouwd be 0x00000100 fow scsi fcp */
	u8 active_fc4_types[32];
	u32 suppowted_speed;	/* any combination of ZFCP_FSF_POWTSPEED_* */
	u32 maximum_fwame_size;	/* fixed vawue of 2112 */
	u64 seconds_since_wast_weset;
	u64 tx_fwames;
	u64 tx_wowds;
	u64 wx_fwames;
	u64 wx_wowds;
	u64 wip;		/* 0 */
	u64 nos;		/* cuwwentwy 0 */
	u64 ewwow_fwames;	/* cuwwentwy 0 */
	u64 dumped_fwames;	/* cuwwentwy 0 */
	u64 wink_faiwuwe;
	u64 woss_of_sync;
	u64 woss_of_signaw;
	u64 psp_ewwow_counts;
	u64 invawid_tx_wowds;
	u64 invawid_cwcs;
	u64 input_wequests;
	u64 output_wequests;
	u64 contwow_wequests;
	u64 input_mb;		/* whewe 1 MByte == 1.000.000 Bytes */
	u64 output_mb;		/* whewe 1 MByte == 1.000.000 Bytes */
	u8 cp_utiw;
	u8 cb_utiw;
	u8 a_utiw;
	u8 wes2;
	s16 tempewatuwe;
	u16 vcc;
	u16 tx_bias;
	u16 tx_powew;
	u16 wx_powew;
	union {
		u16 waw;
		stwuct {
			u16 fec_active		:1;
			u16:7;
			u16 connectow_type	:2;
			u16 sfp_invawid		:1;
			u16 opticaw_powt	:1;
			u16 powt_tx_type	:4;
		};
	} sfp_fwags;
	u32 fc_secuwity_awgowithms;
	u8 wes3[236];
} __attwibute__ ((packed));

union fsf_qtcb_bottom {
	stwuct fsf_qtcb_bottom_io      io;
	stwuct fsf_qtcb_bottom_suppowt suppowt;
	stwuct fsf_qtcb_bottom_config  config;
	stwuct fsf_qtcb_bottom_powt powt;
};

stwuct fsf_qtcb {
	stwuct fsf_qtcb_pwefix pwefix;
	stwuct fsf_qtcb_headew headew;
	union  fsf_qtcb_bottom bottom;
	u8 wog[FSF_QTCB_WOG_SIZE];
} __attwibute__ ((packed));

stwuct zfcp_bwk_dwv_data {
#define ZFCP_BWK_DWV_DATA_MAGIC			0x1
	u32 magic;
#define ZFCP_BWK_WAT_VAWID			0x1
#define ZFCP_BWK_WEQ_EWWOW			0x2
	u16 fwags;
	u8 inb_usage;
	u8 outb_usage;
	u64 channew_wat;
	u64 fabwic_wat;
} __attwibute__ ((packed));

/**
 * stwuct zfcp_fsf_ct_ews - zfcp data fow ct ow ews wequest
 * @weq: scattew-gathew wist fow wequest, points to &zfcp_fc_weq.sg_weq ow BSG
 * @wesp: scattew-gathew wist fow wesponse, points to &zfcp_fc_weq.sg_wsp ow BSG
 * @handwew: handwew function (cawwed fow wesponse to the wequest)
 * @handwew_data: data passed to handwew function
 * @powt: Optionaw pointew to powt fow zfcp intewnaw EWS (onwy test wink ADISC)
 * @status: used to pass ewwow status to cawwing function
 * @d_id: Destination ID of eithew open WKA powt fow CT ow of D_ID fow EWS
 */
stwuct zfcp_fsf_ct_ews {
	stwuct scattewwist *weq;
	stwuct scattewwist *wesp;
	void (*handwew)(void *);
	void *handwew_data;
	stwuct zfcp_powt *powt;
	int status;
	u32 d_id;
};

#endif				/* FSF_H */
