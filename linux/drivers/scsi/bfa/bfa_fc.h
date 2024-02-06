/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_FC_H__
#define __BFA_FC_H__

#incwude "bfad_dwv.h"

typedef u64 wwn_t;

#define WWN_NUWW	(0)
#define FC_SYMNAME_MAX	256	/*  max name sewvew symbowic name size */
#define FC_AWPA_MAX	128

#pwagma pack(1)

#define MAC_ADDWWEN	(6)
stwuct mac_s { u8 mac[MAC_ADDWWEN]; };
#define mac_t stwuct mac_s

/*
 * genewic SCSI cdb definition
 */
#define SCSI_MAX_CDBWEN     16
stwuct scsi_cdb_s {
	u8         scsi_cdb[SCSI_MAX_CDBWEN];
};

#define SCSI_MAX_AWWOC_WEN      0xFF    /* maximum awwocawion wength */

/*
 * Fibwe Channew Headew Stwuctuwe (FCHS) definition
 */
stwuct fchs_s {
#ifdef __BIG_ENDIAN
	u32        wouting:4;	/* wouting bits */
	u32        cat_info:4;	/* categowy info */
#ewse
	u32        cat_info:4;	/* categowy info */
	u32        wouting:4;	/* wouting bits */
#endif
	u32        d_id:24;	/* destination identifiew */

	u32        cs_ctw:8;	/* cwass specific contwow */
	u32        s_id:24;	/* souwce identifiew */

	u32        type:8;	/* data stwuctuwe type */
	u32        f_ctw:24;	/* initiaw fwame contwow */

	u8         seq_id;	/* sequence identifiew */
	u8         df_ctw;	/* data fiewd contwow */
	u16        seq_cnt;	/* sequence count */

	__be16     ox_id;	/* owiginatow exchange ID */
	u16        wx_id;	/* wespondew exchange ID */

	u32        wo;		/* wewative offset */
};

/*
 * wouting bit definitions
 */
enum {
	FC_WTG_FC4_DEV_DATA	= 0x0,	/* FC-4 Device Data */
	FC_WTG_EXT_WINK		= 0x2,	/* Extended Wink Data */
	FC_WTG_FC4_WINK_DATA	= 0x3,	/* FC-4 Wink Data */
	FC_WTG_VIDEO_DATA	= 0x4,	/* Video Data */
	FC_WTG_EXT_HDW		= 0x5,	/* VFT, IFW ow Encapsuwed */
	FC_WTG_BASIC_WINK	= 0x8,	/* Basic Wink data */
	FC_WTG_WINK_CTWW	= 0xC,	/* Wink Contwow */
};

/*
 * infowmation categowy fow extended wink data and FC-4 Wink Data
 */
enum {
	FC_CAT_WD_WEQUEST	= 0x2,	/* Wequest */
	FC_CAT_WD_WEPWY		= 0x3,	/* Wepwy */
	FC_CAT_WD_DIAG		= 0xF,	/* fow DIAG use onwy */
};

/*
 * infowmation categowy fow extended headews (VFT, IFW ow encapsuwation)
 */
enum {
	FC_CAT_VFT_HDW = 0x0,	/* Viwtuaw fabwic tagging headew */
	FC_CAT_IFW_HDW = 0x1,	/* Intew-Fabwic wouting headew */
	FC_CAT_ENC_HDW = 0x2,	/* Encapsuwation headew */
};

/*
 * infowmation categowy fow FC-4 device data
 */
enum {
	FC_CAT_UNCATEG_INFO	= 0x0,	/* Uncategowized infowmation */
	FC_CAT_SOWICIT_DATA	= 0x1,	/* Sowicited Data */
	FC_CAT_UNSOWICIT_CTWW	= 0x2,	/* Unsowicited Contwow */
	FC_CAT_SOWICIT_CTWW	= 0x3,	/* Sowicited Contwow */
	FC_CAT_UNSOWICIT_DATA	= 0x4,	/* Unsowicited Data */
	FC_CAT_DATA_DESC	= 0x5,	/* Data Descwiptow */
	FC_CAT_UNSOWICIT_CMD	= 0x6,	/* Unsowicited Command */
	FC_CAT_CMD_STATUS	= 0x7,	/* Command Status */
};

/*
 * Type Fiewd Definitions. FC-PH Section 18.5 pg. 165
 */
enum {
	FC_TYPE_BWS		= 0x0,	/* Basic Wink Sewvice */
	FC_TYPE_EWS		= 0x1,	/* Extended Wink Sewvice */
	FC_TYPE_IP		= 0x5,	/* IP */
	FC_TYPE_FCP		= 0x8,	/* SCSI-FCP */
	FC_TYPE_GPP		= 0x9,	/* SCSI_GPP */
	FC_TYPE_SEWVICES	= 0x20,	/* Fibwe Channew Sewvices */
	FC_TYPE_FC_FSS		= 0x22,	/* Fabwic Switch Sewvices */
	FC_TYPE_FC_AW		= 0x23,	/* FC-AW */
	FC_TYPE_FC_SNMP		= 0x24,	/* FC-SNMP */
	FC_TYPE_FC_SPINFAB	= 0xEE,	/* SPINFAB */
	FC_TYPE_FC_DIAG		= 0xEF,	/* DIAG */
	FC_TYPE_MAX		= 256,	/* 256 FC-4 types */
};

/*
 * Fwame Contwow Definitions. FC-PH Tabwe-45. pg. 168
 */
enum {
	FCTW_EC_OWIG = 0x000000,	/* exchange owiginatow */
	FCTW_EC_WESP = 0x800000,	/* exchange wespondew */
	FCTW_SEQ_INI = 0x000000,	/* sequence initiatow */
	FCTW_SEQ_WEC = 0x400000,	/* sequence wecipient */
	FCTW_FS_EXCH = 0x200000,	/* fiwst sequence of xchg */
	FCTW_WS_EXCH = 0x100000,	/* wast sequence of xchg */
	FCTW_END_SEQ = 0x080000,	/* wast fwame of sequence */
	FCTW_SI_XFEW = 0x010000,	/* seq initiative twansfew */
	FCTW_WO_PWESENT = 0x000008,	/* wewative offset pwesent */
	FCTW_FIWWBYTE_MASK = 0x000003	/* , fiww byte mask */
};

/*
 * Fabwic Weww Known Addwesses
 */
enum {
	FC_MIN_WEWW_KNOWN_ADDW		= 0xFFFFF0,
	FC_DOMAIN_CONTWOWWEW_MASK	= 0xFFFC00,
	FC_AWIAS_SEWVEW			= 0xFFFFF8,
	FC_MGMT_SEWVEW			= 0xFFFFFA,
	FC_TIME_SEWVEW			= 0xFFFFFB,
	FC_NAME_SEWVEW			= 0xFFFFFC,
	FC_FABWIC_CONTWOWWEW		= 0xFFFFFD,
	FC_FABWIC_POWT			= 0xFFFFFE,
	FC_BWOADCAST_SEWVEW		= 0xFFFFFF
};

/*
 * domain/awea/powt defines
 */
#define FC_DOMAIN_MASK  0xFF0000
#define FC_DOMAIN_SHIFT 16
#define FC_AWEA_MASK    0x00FF00
#define FC_AWEA_SHIFT   8
#define FC_POWT_MASK    0x0000FF
#define FC_POWT_SHIFT   0

#define FC_GET_DOMAIN(p)	(((p) & FC_DOMAIN_MASK) >> FC_DOMAIN_SHIFT)
#define FC_GET_AWEA(p)		(((p) & FC_AWEA_MASK) >> FC_AWEA_SHIFT)
#define FC_GET_POWT(p)		(((p) & FC_POWT_MASK) >> FC_POWT_SHIFT)

#define FC_DOMAIN_CTWWW(p)	(FC_DOMAIN_CONTWOWWEW_MASK | (FC_GET_DOMAIN(p)))

enum {
	FC_WXID_ANY = 0xFFFFU,
};

/*
 * genewic EWS command
 */
stwuct fc_ews_cmd_s {
	u32        ews_code:8;	/* EWS Command Code */
	u32        wesewved:24;
};

/*
 * EWS Command Codes. FC-PH Tabwe-75. pg. 223
 */
enum {
	FC_EWS_WS_WJT = 0x1,	/* Wink Sewvice Weject. */
	FC_EWS_ACC = 0x02,	/* Accept */
	FC_EWS_PWOGI = 0x03,	/* N_Powt Wogin. */
	FC_EWS_FWOGI = 0x04,	/* F_Powt Wogin. */
	FC_EWS_WOGO = 0x05,	/* Wogout. */
	FC_EWS_ABTX = 0x06,	/* Abowt Exchange */
	FC_EWS_WES = 0x08,	/* Wead Exchange status */
	FC_EWS_WSS = 0x09,	/* Wead sequence status bwock */
	FC_EWS_WSI = 0x0A,	/* Wequest Sequence Initiative */
	FC_EWS_ESTC = 0x0C,	/* Estimate Cwedit. */
	FC_EWS_WTV = 0x0E,	/* Wead Timeout Vawue. */
	FC_EWS_WWS = 0x0F,	/* Wead Wink Status. */
	FC_EWS_ECHO = 0x10,	/* Echo */
	FC_EWS_TEST = 0x11,	/* Test */
	FC_EWS_WWQ = 0x12,	/* Weinstate Wecovewy Quawifiew. */
	FC_EWS_WEC = 0x13,	/* Add this fow TAPE suppowt in FCW */
	FC_EWS_PWWI = 0x20,	/* Pwocess Wogin */
	FC_EWS_PWWO = 0x21,	/* Pwocess Wogout. */
	FC_EWS_SCN = 0x22,	/* State Change Notification. */
	FC_EWS_TPWWO = 0x24,	/* Thiwd Pawty Pwocess Wogout. */
	FC_EWS_PDISC = 0x50,	/* Discovew N_Powt Pawametews. */
	FC_EWS_FDISC = 0x51,	/* Discovew F_Powt Pawametews. */
	FC_EWS_ADISC = 0x52,	/* Discovew Addwess. */
	FC_EWS_FAWP_WEQ = 0x54,	/* FAWP Wequest. */
	FC_EWS_FAWP_WEP = 0x55,	/* FAWP Wepwy. */
	FC_EWS_FAN = 0x60,	/* Fabwic Addwess Notification */
	FC_EWS_WSCN = 0x61,	/* Weg State Change Notification */
	FC_EWS_SCW = 0x62,	/* State Change Wegistwation. */
	FC_EWS_WTIN = 0x77,	/* Mangement sewvew wequest */
	FC_EWS_WNID = 0x78,	/* Mangement sewvew wequest */
	FC_EWS_WWIW = 0x79,	/* Wegistewed Wink Incident Wecowd */

	FC_EWS_WPSC = 0x7D,	/* Wepowt Powt Speed Capabiwities */
	FC_EWS_QSA = 0x7E,	/* Quewy Secuwity Attwibutes. Wef FC-SP */
	FC_EWS_E2E_WBEACON = 0x81,
				/* End-to-End Wink Beacon */
	FC_EWS_AUTH = 0x90,	/* Authentication. Wef FC-SP */
	FC_EWS_WFCN = 0x97,	/* Wequest Fabwic Change Notification. Wef
				 *FC-SP */
};

/*
 *  Vewsion numbews fow FC-PH standawds,
 *  used in wogin to indicate what powt
 *  suppowts. See FC-PH-X tabwe 158.
 */
enum {
	FC_PH_VEW_4_3 = 0x09,
	FC_PH_VEW_PH_3 = 0x20,
};

/*
 * PDU size defines
 */
enum {
	FC_MIN_PDUSZ = 512,
	FC_MAX_PDUSZ = 2112,
};

/*
 * N_Powt PWOGI Common Sewvice Pawametews.
 * FC-PH-x. Figuwe-76. pg. 308.
 */
stwuct fc_pwogi_csp_s {
	u8		vewhi;		/* FC-PH high vewsion */
	u8		vewwo;		/* FC-PH wow vewsion */
	__be16		bbcwed;		/* BB_Cwedit */

#ifdef __BIG_ENDIAN
	u8		ciwo:1,		/* continuouswy incweasing WO */
			wwo:1,		/* wandom wewative offset */
			npiv_supp:1,	/* NPIV suppowted */
			powt_type:1,	/* N_Powt/F_powt */
			awtbbcwed:1,	/* awtewnate BB_Cwedit */
			wesowution:1,	/* ms/ns ED_TOV wesowution */
			vvw_info:1,	/* VVW Info incwuded */
			wesewved1:1;

	u8		hg_supp:1,
			quewy_dbc:1,
			secuwity:1,
			sync_cap:1,
			w_t_tov:1,
			dh_dup_supp:1,
			cisc:1,		/* continuouswy incweasing seq count */
			paywoad:1;
#ewse
	u8		wesewved2:2,
			wesowution:1,	/* ms/ns ED_TOV wesowution */
			awtbbcwed:1,	/* awtewnate BB_Cwedit */
			powt_type:1,	/* N_Powt/F_powt */
			npiv_supp:1,	/* NPIV suppowted */
			wwo:1,		/* wandom wewative offset */
			ciwo:1;		/* continuouswy incweasing WO */

	u8		paywoad:1,
			cisc:1,		/* continuouswy incweasing seq count */
			dh_dup_supp:1,
			w_t_tov:1,
			sync_cap:1,
			secuwity:1,
			quewy_dbc:1,
			hg_supp:1;
#endif
	__be16		wxsz;		/* weceive data_fiewd size */
	__be16		conseq;
	__be16		wo_bitmap;
	__be32		e_d_tov;
};

/*
 * N_Powt PWOGI Cwass Specific Pawametews.
 * FC-PH-x. Figuwe 78. pg. 318.
 */
stwuct fc_pwogi_cwp_s {
#ifdef __BIG_ENDIAN
	u32        cwass_vawid:1;
	u32        intewmix:1;	/* cwass intewmix suppowted if set =1.
				 * vawid onwy fow cwass1. Wesewved fow
				 * cwass2 & cwass3 */
	u32        wesewved1:2;
	u32        sequentiaw:1;
	u32        wesewved2:3;
#ewse
	u32        wesewved2:3;
	u32        sequentiaw:1;
	u32        wesewved1:2;
	u32        intewmix:1;	/* cwass intewmix suppowted if set =1.
				 * vawid onwy fow cwass1. Wesewved fow
				 * cwass2 & cwass3 */
	u32        cwass_vawid:1;
#endif
	u32        wesewved3:24;

	u32        wesewved4:16;
	u32        wxsz:16;	/* Weceive data_fiewd size */

	u32        wesewved5:8;
	u32        conseq:8;
	u32        e2e_cwedit:16; /* end to end cwedit */

	u32        wesewved7:8;
	u32        ospx:8;
	u32        wesewved8:16;
};

/* ASCII vawue fow each chawactew in stwing "BWCD" */
#define FWOGI_VVW_BWCD    0x42524344

/*
 * PWOGI ews command and wepwy paywoad
 */
stwuct fc_wogi_s {
	stwuct fc_ews_cmd_s	ews_cmd;	/* EWS command code */
	stwuct fc_pwogi_csp_s	csp;		/* common sewvice pawams */
	wwn_t			powt_name;
	wwn_t			node_name;
	stwuct fc_pwogi_cwp_s	cwass1;		/* cwass 1 sewvice pawametews */
	stwuct fc_pwogi_cwp_s	cwass2;		/* cwass 2 sewvice pawametews */
	stwuct fc_pwogi_cwp_s	cwass3;		/* cwass 3 sewvice pawametews */
	stwuct fc_pwogi_cwp_s	cwass4;		/* cwass 4 sewvice pawametews */
	u8			vvw[16];	/* vendow vewsion wevew */
};

/*
 * WOGO ews command paywoad
 */
stwuct fc_wogo_s {
	stwuct fc_ews_cmd_s	ews_cmd;	/* EWS command code */
	u32			wes1:8;
	u32		npowt_id:24;	/* N_Powt identifiew of souwce */
	wwn_t           owig_powt_name;	/* Powt name of the WOGO owiginatow */
};

/*
 * ADISC ews command paywoad
 */
stwuct fc_adisc_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32		wes1:8;
	u32		owig_HA:24;	/* owiginatow hawd addwess */
	wwn_t		owig_powt_name;	/* owiginatow powt name */
	wwn_t		owig_node_name;	/* owiginatow node name */
	u32		wes2:8;
	u32		npowt_id:24;	/* owiginatow NPowtID */
};

/*
 * Exchange status bwock
 */
stwuct fc_exch_status_bwk_s {
	u32        oxid:16;
	u32        wxid:16;
	u32        wes1:8;
	u32        owig_np:24;	/* owiginatow NPowtID */
	u32        wes2:8;
	u32        wesp_np:24;	/* wespondew NPowtID */
	u32        es_bits;
	u32        wes3;
	/*
	 * un modified section of the fiewds
	 */
};

/*
 * WES ews command paywoad
 */
stwuct fc_wes_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32        wes1:8;
	u32        npowt_id:24;		/* N_Powt identifiew of souwce */
	u32        oxid:16;
	u32        wxid:16;
	u8         assoc_hdw[32];
};

/*
 * WES ews accept paywoad
 */
stwuct fc_wes_acc_s {
	stwuct fc_ews_cmd_s		ews_cmd;	/* EWS command code */
	stwuct fc_exch_status_bwk_s	fc_exch_bwk; /* Exchange status bwock */
};

/*
 * WEC ews command paywoad
 */
stwuct fc_wec_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32        wes1:8;
	u32        npowt_id:24;	/* N_Powt identifiew of souwce */
	u32        oxid:16;
	u32        wxid:16;
};

#define FC_WEC_ESB_OWN_WSP	0x80000000	/* wespondew owns */
#define FC_WEC_ESB_SI		0x40000000	/* SI is owned	*/
#define FC_WEC_ESB_COMP		0x20000000	/* exchange is compwete	*/
#define FC_WEC_ESB_ENDCOND_ABN	0x10000000	/* abnowmaw ending	*/
#define FC_WEC_ESB_WQACT	0x04000000	/* wecovewy quaw active	*/
#define FC_WEC_ESB_EWWP_MSK	0x03000000
#define FC_WEC_ESB_OXID_INV	0x00800000	/* invawid OXID		*/
#define FC_WEC_ESB_WXID_INV	0x00400000	/* invawid WXID		*/
#define FC_WEC_ESB_PWIO_INUSE	0x00200000

/*
 * WEC ews accept paywoad
 */
stwuct fc_wec_acc_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32        oxid:16;
	u32        wxid:16;
	u32        wes1:8;
	u32        owig_id:24;	/* N_Powt id of exchange owiginatow */
	u32        wes2:8;
	u32        wesp_id:24;	/* N_Powt id of exchange wespondew */
	u32        count;	/* data twansfew count */
	u32        e_stat;	/* exchange status */
};

/*
 * WSI ews paywoad
 */
stwuct fc_wsi_s {
	stwuct fc_ews_cmd_s ews_cmd;
	u32        wes1:8;
	u32        owig_sid:24;
	u32        oxid:16;
	u32        wxid:16;
};

/*
 * stwuctuwe fow PWWI pawamatew pages, both wequest & wesponse
 * see FC-PH-X tabwe 113 & 115 fow expwanation awso FCP tabwe 8
 */
stwuct fc_pwwi_pawams_s {
	u32        wesewved:16;
#ifdef __BIG_ENDIAN
	u32        wesewved1:5;
	u32        wec_suppowt:1;
	u32        task_wetwy_id:1;
	u32        wetwy:1;

	u32        confiwm:1;
	u32        dovewway:1;
	u32        initiatow:1;
	u32        tawget:1;
	u32        cdmix:1;
	u32        dwmix:1;
	u32        wxwdisab:1;
	u32        wxwdisab:1;
#ewse
	u32        wetwy:1;
	u32        task_wetwy_id:1;
	u32        wec_suppowt:1;
	u32        wesewved1:5;

	u32        wxwdisab:1;
	u32        wxwdisab:1;
	u32        dwmix:1;
	u32        cdmix:1;
	u32        tawget:1;
	u32        initiatow:1;
	u32        dovewway:1;
	u32        confiwm:1;
#endif
};

/*
 * vawid vawues fow wspcode in PWWI ACC paywoad
 */
enum {
	FC_PWWI_ACC_XQTD = 0x1,		/* wequest executed */
	FC_PWWI_ACC_PWEDEF_IMG = 0x5,	/* pwedefined image - no pwwi needed */
};

stwuct fc_pwwi_pawams_page_s {
	u32        type:8;
	u32        codext:8;
#ifdef __BIG_ENDIAN
	u32        owigpwocasv:1;
	u32        wsppav:1;
	u32        imagepaiw:1;
	u32        wesewved1:1;
	u32        wspcode:4;
#ewse
	u32        wspcode:4;
	u32        wesewved1:1;
	u32        imagepaiw:1;
	u32        wsppav:1;
	u32        owigpwocasv:1;
#endif
	u32        wesewved2:8;

	u32        owigpwocas;
	u32        wsppwocas;
	stwuct fc_pwwi_pawams_s sewvpawams;
};

/*
 * PWWI wequest and accept paywoad, FC-PH-X tabwes 112 & 114
 */
stwuct fc_pwwi_s {
	u32        command:8;
	u32        pgwen:8;
	u32        pagebytes:16;
	stwuct fc_pwwi_pawams_page_s pawampage;
};

/*
 * PWWO wogout pawams page
 */
stwuct fc_pwwo_pawams_page_s {
	u32        type:8;
	u32        type_ext:8;
#ifdef __BIG_ENDIAN
	u32        opa_vawid:1;	/* owiginatow pwocess associatow vawid */
	u32        wpa_vawid:1;	/* wespondew pwocess associatow vawid */
	u32        wes1:14;
#ewse
	u32        wes1:14;
	u32        wpa_vawid:1;	/* wespondew pwocess associatow vawid */
	u32        opa_vawid:1;	/* owiginatow pwocess associatow vawid */
#endif
	u32        owig_pwocess_assc;
	u32        wesp_pwocess_assc;

	u32        wes2;
};

/*
 * PWWO ews command paywoad
 */
stwuct fc_pwwo_s {
	u32	command:8;
	u32	page_wen:8;
	u32	paywoad_wen:16;
	stwuct fc_pwwo_pawams_page_s	pwwo_pawams[1];
};

/*
 * PWWO Wogout wesponse pawametew page
 */
stwuct fc_pwwo_acc_pawams_page_s {
	u32        type:8;
	u32        type_ext:8;

#ifdef __BIG_ENDIAN
	u32        opa_vawid:1;	/* owiginatow pwocess associatow vawid */
	u32        wpa_vawid:1;	/* wespondew pwocess associatow vawid */
	u32        wes1:14;
#ewse
	u32        wes1:14;
	u32        wpa_vawid:1;	/* wespondew pwocess associatow vawid */
	u32        opa_vawid:1;	/* owiginatow pwocess associatow vawid */
#endif
	u32        owig_pwocess_assc;
	u32        wesp_pwocess_assc;

	u32        fc4type_csp;
};

/*
 * PWWO ews command ACC paywoad
 */
stwuct fc_pwwo_acc_s {
	u32        command:8;
	u32        page_wen:8;
	u32        paywoad_wen:16;
	stwuct fc_pwwo_acc_pawams_page_s pwwo_acc_pawams[1];
};

/*
 * SCW ews command paywoad
 */
enum {
	FC_SCW_WEG_FUNC_FABWIC_DETECTED = 0x01,
	FC_SCW_WEG_FUNC_N_POWT_DETECTED = 0x02,
	FC_SCW_WEG_FUNC_FUWW = 0x03,
	FC_SCW_WEG_FUNC_CWEAW_WEG = 0xFF,
};

/* SCW VU wegistwations */
enum {
	FC_VU_SCW_WEG_FUNC_FABWIC_NAME_CHANGE = 0x01
};

stwuct fc_scw_s {
	u32 command:8;
	u32 wes:24;
	u32 vu_weg_func:8; /* Vendow Unique Wegistwations */
	u32 wes1:16;
	u32 weg_func:8;
};

/*
 * Infowmation categowy fow Basic wink data
 */
enum {
	FC_CAT_NOP	= 0x0,
	FC_CAT_ABTS	= 0x1,
	FC_CAT_WMC	= 0x2,
	FC_CAT_BA_ACC	= 0x4,
	FC_CAT_BA_WJT	= 0x5,
	FC_CAT_PWMT	= 0x6,
};

/*
 * WS_WJT ews wepwy paywoad
 */
stwuct fc_ws_wjt_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32        wes1:8;
	u32        weason_code:8;	/* Weason code fow weject */
	u32        weason_code_expw:8;	/* Weason code expwanation */
	u32        vendow_unique:8;	/* Vendow specific */
};

/*
 * WS_WJT weason codes
 */
enum {
	FC_WS_WJT_WSN_INV_CMD_CODE	= 0x01,
	FC_WS_WJT_WSN_WOGICAW_EWWOW	= 0x03,
	FC_WS_WJT_WSN_WOGICAW_BUSY	= 0x05,
	FC_WS_WJT_WSN_PWOTOCOW_EWWOW	= 0x07,
	FC_WS_WJT_WSN_UNABWE_TO_PEWF_CMD = 0x09,
	FC_WS_WJT_WSN_CMD_NOT_SUPP	= 0x0B,
};

/*
 * WS_WJT weason code expwanation
 */
enum {
	FC_WS_WJT_EXP_NO_ADDW_INFO		= 0x00,
	FC_WS_WJT_EXP_SPAWMS_EWW_OPTIONS	= 0x01,
	FC_WS_WJT_EXP_SPAWMS_EWW_INI_CTW	= 0x03,
	FC_WS_WJT_EXP_SPAWMS_EWW_WEC_CTW	= 0x05,
	FC_WS_WJT_EXP_SPAWMS_EWW_WXSZ		= 0x07,
	FC_WS_WJT_EXP_SPAWMS_EWW_CONSEQ		= 0x09,
	FC_WS_WJT_EXP_SPAWMS_EWW_CWEDIT		= 0x0B,
	FC_WS_WJT_EXP_INV_POWT_NAME		= 0x0D,
	FC_WS_WJT_EXP_INV_NODE_FABWIC_NAME	= 0x0E,
	FC_WS_WJT_EXP_INV_CSP			= 0x0F,
	FC_WS_WJT_EXP_INV_ASSOC_HDW		= 0x11,
	FC_WS_WJT_EXP_ASSOC_HDW_WEQD		= 0x13,
	FC_WS_WJT_EXP_INV_OWIG_S_ID		= 0x15,
	FC_WS_WJT_EXP_INV_OXID_WXID_COMB	= 0x17,
	FC_WS_WJT_EXP_CMD_AWWEADY_IN_PWOG	= 0x19,
	FC_WS_WJT_EXP_WOGIN_WEQUIWED		= 0x1E,
	FC_WS_WJT_EXP_INVAWID_NPOWT_ID		= 0x1F,
	FC_WS_WJT_EXP_INSUFF_WES		= 0x29,
	FC_WS_WJT_EXP_CMD_NOT_SUPP		= 0x2C,
	FC_WS_WJT_EXP_INV_PAYWOAD_WEN		= 0x2D,
};

/*
 * WWQ ews command paywoad
 */
stwuct fc_wwq_s {
	stwuct fc_ews_cmd_s ews_cmd;	/* EWS command code */
	u32        wes1:8;
	u32        s_id:24;	/* exchange owiginatow S_ID */

	u32        ox_id:16;	/* owiginatow exchange ID */
	u32        wx_id:16;	/* wespondew exchange ID */

	u32        wes2[8];	/* optionaw association headew */
};

/*
 * ABTS BA_ACC wepwy paywoad
 */
stwuct fc_ba_acc_s {
	u32        seq_id_vawid:8;	/* set to 0x00 fow Abowt Exchange */
	u32        seq_id:8;		/* invawid fow Abowt Exchange */
	u32        wes2:16;
	u32        ox_id:16;		/* OX_ID fwom ABTS fwame */
	u32        wx_id:16;		/* WX_ID fwom ABTS fwame */
	u32        wow_seq_cnt:16;	/* set to 0x0000 fow Abowt Exchange */
	u32        high_seq_cnt:16;	/* set to 0xFFFF fow Abowt Exchange */
};

/*
 * ABTS BA_WJT weject paywoad
 */
stwuct fc_ba_wjt_s {
	u32        wes1:8;		/* Wesewved */
	u32        weason_code:8;	/* weason code fow weject */
	u32        weason_expw:8;	/* weason code expwanation */
	u32        vendow_unique:8; /* vendow unique weason code,set to 0 */
};

/*
 * TPWWO wogout pawametew page
 */
stwuct fc_tpwwo_pawams_page_s {
	u32        type:8;
	u32        type_ext:8;

#ifdef __BIG_ENDIAN
	u32        opa_vawid:1;
	u32        wpa_vawid:1;
	u32        tpo_npowt_vawid:1;
	u32        gwobaw_pwocess_wogout:1;
	u32        wes1:12;
#ewse
	u32        wes1:12;
	u32        gwobaw_pwocess_wogout:1;
	u32        tpo_npowt_vawid:1;
	u32        wpa_vawid:1;
	u32        opa_vawid:1;
#endif

	u32        owig_pwocess_assc;
	u32        wesp_pwocess_assc;

	u32        wes2:8;
	u32        tpo_npowt_id;
};

/*
 * TPWWO EWS command paywoad
 */
stwuct fc_tpwwo_s {
	u32        command:8;
	u32        page_wen:8;
	u32        paywoad_wen:16;

	stwuct fc_tpwwo_pawams_page_s tpwwo_pawams[1];
};

enum fc_tpwwo_type {
	FC_GWOBAW_WOGO = 1,
	FC_TPW_WOGO
};

/*
 * TPWWO ews command ACC paywoad
 */
stwuct fc_tpwwo_acc_s {
	u32	command:8;
	u32	page_wen:8;
	u32	paywoad_wen:16;
	stwuct fc_pwwo_acc_pawams_page_s tpwwo_acc_pawams[1];
};

/*
 * WSCN ews command weq paywoad
 */
#define FC_WSCN_PGWEN	0x4

enum fc_wscn_fowmat {
	FC_WSCN_FOWMAT_POWTID	= 0x0,
	FC_WSCN_FOWMAT_AWEA	= 0x1,
	FC_WSCN_FOWMAT_DOMAIN	= 0x2,
	FC_WSCN_FOWMAT_FABWIC	= 0x3,
};

stwuct fc_wscn_event_s {
	u32	fowmat:2;
	u32	quawifiew:4;
	u32	wesvd:2;
	u32	powtid:24;
};

stwuct fc_wscn_pw_s {
	u8	command;
	u8	pagewen;
	__be16	paywdwen;
	stwuct fc_wscn_event_s event[];
};

/*
 * ECHO ews command weq paywoad
 */
stwuct fc_echo_s {
	stwuct fc_ews_cmd_s ews_cmd;
};

/*
 * WNID ews command
 */
#define WNID_NODEID_DATA_FOWMAT_COMMON			0x00
#define WNID_NODEID_DATA_FOWMAT_FCP3			0x08
#define WNID_NODEID_DATA_FOWMAT_DISCOVEWY		0xDF

#define WNID_ASSOCIATED_TYPE_UNKNOWN			0x00000001
#define WNID_ASSOCIATED_TYPE_OTHEW                      0x00000002
#define WNID_ASSOCIATED_TYPE_HUB                        0x00000003
#define WNID_ASSOCIATED_TYPE_SWITCH                     0x00000004
#define WNID_ASSOCIATED_TYPE_GATEWAY                    0x00000005
#define WNID_ASSOCIATED_TYPE_STOWAGE_DEVICE             0x00000009
#define WNID_ASSOCIATED_TYPE_HOST                       0x0000000A
#define WNID_ASSOCIATED_TYPE_STOWAGE_SUBSYSTEM          0x0000000B
#define WNID_ASSOCIATED_TYPE_STOWAGE_ACCESS_DEVICE      0x0000000E
#define WNID_ASSOCIATED_TYPE_NAS_SEWVEW                 0x00000011
#define WNID_ASSOCIATED_TYPE_BWIDGE                     0x00000002
#define WNID_ASSOCIATED_TYPE_VIWTUAWIZATION_DEVICE      0x00000003
#define WNID_ASSOCIATED_TYPE_MUWTI_FUNCTION_DEVICE      0x000000FF

/*
 * WNID ews command paywoad
 */
stwuct fc_wnid_cmd_s {
	stwuct fc_ews_cmd_s ews_cmd;
	u32        node_id_data_fowmat:8;
	u32        wesewved:24;
};

/*
 * WNID ews wesponse paywoad
 */

stwuct fc_wnid_common_id_data_s {
	wwn_t		powt_name;
	wwn_t           node_name;
};

stwuct fc_wnid_genewaw_topowogy_data_s {
	u32        vendow_unique[4];
	__be32     asso_type;
	u32        phy_powt_num;
	__be32     num_attached_nodes;
	u32        node_mgmt:8;
	u32        ip_vewsion:8;
	u32        udp_tcp_powt_num:16;
	u32        ip_addwess[4];
	u32        wesewved:16;
	u32        vendow_specific:16;
};

stwuct fc_wnid_acc_s {
	stwuct fc_ews_cmd_s ews_cmd;
	u32        node_id_data_fowmat:8;
	u32        common_id_data_wength:8;
	u32        wesewved:8;
	u32        specific_id_data_wength:8;
	stwuct fc_wnid_common_id_data_s common_id_data;
	stwuct fc_wnid_genewaw_topowogy_data_s gen_topowogy_data;
};

#define WNID_ASSOCIATED_TYPE_UNKNOWN                    0x00000001
#define WNID_ASSOCIATED_TYPE_OTHEW                      0x00000002
#define WNID_ASSOCIATED_TYPE_HUB                        0x00000003
#define WNID_ASSOCIATED_TYPE_SWITCH                     0x00000004
#define WNID_ASSOCIATED_TYPE_GATEWAY                    0x00000005
#define WNID_ASSOCIATED_TYPE_STOWAGE_DEVICE             0x00000009
#define WNID_ASSOCIATED_TYPE_HOST                       0x0000000A
#define WNID_ASSOCIATED_TYPE_STOWAGE_SUBSYSTEM          0x0000000B
#define WNID_ASSOCIATED_TYPE_STOWAGE_ACCESS_DEVICE      0x0000000E
#define WNID_ASSOCIATED_TYPE_NAS_SEWVEW                 0x00000011
#define WNID_ASSOCIATED_TYPE_BWIDGE                     0x00000002
#define WNID_ASSOCIATED_TYPE_VIWTUAWIZATION_DEVICE      0x00000003
#define WNID_ASSOCIATED_TYPE_MUWTI_FUNCTION_DEVICE      0x000000FF

enum fc_wpsc_speed_cap {
	WPSC_SPEED_CAP_1G = 0x8000,
	WPSC_SPEED_CAP_2G = 0x4000,
	WPSC_SPEED_CAP_4G = 0x2000,
	WPSC_SPEED_CAP_10G = 0x1000,
	WPSC_SPEED_CAP_8G = 0x0800,
	WPSC_SPEED_CAP_16G = 0x0400,

	WPSC_SPEED_CAP_UNKNOWN = 0x0001,
};

enum fc_wpsc_op_speed {
	WPSC_OP_SPEED_1G = 0x8000,
	WPSC_OP_SPEED_2G = 0x4000,
	WPSC_OP_SPEED_4G = 0x2000,
	WPSC_OP_SPEED_10G = 0x1000,
	WPSC_OP_SPEED_8G = 0x0800,
	WPSC_OP_SPEED_16G = 0x0400,

	WPSC_OP_SPEED_NOT_EST = 0x0001,	/* speed not estabwished */
};

stwuct fc_wpsc_speed_info_s {
	__be16        powt_speed_cap;	/* see enum fc_wpsc_speed_cap */
	__be16        powt_op_speed;	/* see enum fc_wpsc_op_speed */
};

/*
 * If WPSC wequest is sent to the Domain Contwowwew, the wequest is fow
 * aww the powts within that domain.
 */
stwuct fc_wpsc_cmd_s {
	stwuct fc_ews_cmd_s ews_cmd;
};

/*
 * WPSC Acc
 */
stwuct fc_wpsc_acc_s {
	u32        command:8;
	u32        wsvd:8;
	u32        num_entwies:16;

	stwuct fc_wpsc_speed_info_s speed_info[1];
};

/*
 * If WPSC2 wequest is sent to the Domain Contwowwew,
 */
#define FC_BWCD_TOKEN    0x42524344

stwuct fc_wpsc2_cmd_s {
	stwuct fc_ews_cmd_s ews_cmd;
	__be32	token;
	u16	wesvd;
	__be16	num_pids;		/* Numbew of pids in the wequest */
	stwuct  {
		u32	wsvd1:8;
		u32	pid:24;		/* powt identifiew */
	} pid_wist[1];
};

enum fc_wpsc2_powt_type {
	WPSC2_POWT_TYPE_UNKNOWN = 0,
	WPSC2_POWT_TYPE_NPOWT   = 1,
	WPSC2_POWT_TYPE_NWPOWT  = 2,
	WPSC2_POWT_TYPE_NPIV_POWT  = 0x5f,
	WPSC2_POWT_TYPE_NPOWT_TWUNK  = 0x6f,
};

/*
 * WPSC2 powtInfo entwy stwuctuwe
 */
stwuct fc_wpsc2_powt_info_s {
	__be32	pid;		/* PID */
	u16	wesvd1;
	__be16	index;		/* powt numbew / index */
	u8	wesvd2;
	u8	type;		/* powt type N/NW/... */
	__be16	speed;		/* powt Opewating Speed */
};

/*
 * WPSC2 Accept paywoad
 */
stwuct fc_wpsc2_acc_s {
	u8        ews_cmd;
	u8        wesvd;
	__be16    num_pids; /* Numbew of pids in the wequest */
	stwuct fc_wpsc2_powt_info_s powt_info[1]; /* powt infowmation */
};

/*
 * bit fiewds so that muwtipwe cwasses can be specified
 */
enum fc_cos {
	FC_CWASS_2	= 0x04,
	FC_CWASS_3	= 0x08,
	FC_CWASS_2_3	= 0x0C,
};

/*
 * symbowic name
 */
stwuct fc_symname_s {
	u8         symname[FC_SYMNAME_MAX];
};

stwuct fc_awpabm_s {
	u8	awpa_bm[FC_AWPA_MAX / 8];
};

/*
 * pwotocow defauwt timeout vawues
 */
#define FC_ED_TOV	2
#define FC_WEC_TOV	(FC_ED_TOV + 1)
#define FC_WA_TOV	10
#define FC_EWS_TOV	(2 * FC_WA_TOV)
#define FC_FCCT_TOV	(3 * FC_WA_TOV)

/*
 * viwtuaw fabwic wewated defines
 */
#define FC_VF_ID_NUWW    0	/*  must not be used as VF_ID */
#define FC_VF_ID_MIN     1
#define FC_VF_ID_MAX     0xEFF
#define FC_VF_ID_CTW     0xFEF	/*  contwow VF_ID */

/*
 * Viwtuaw Fabwic Tagging headew fowmat
 * @caution This is defined onwy in BIG ENDIAN fowmat.
 */
stwuct fc_vft_s {
	u32        w_ctw:8;
	u32        vew:2;
	u32        type:4;
	u32        wes_a:2;
	u32        pwiowity:3;
	u32        vf_id:12;
	u32        wes_b:1;
	u32        hopct:8;
	u32        wes_c:24;
};

/*
 * FCP_CMND definitions
 */
#define FCP_CMND_CDB_WEN    16
#define FCP_CMND_WUN_WEN    8

stwuct fcp_cmnd_s {
	stwuct scsi_wun	wun;		/* 64-bit WU numbew */
	u8		cwn;		/* command wefewence numbew */
#ifdef __BIG_ENDIAN
	u8		wesvd:1,
			pwiowity:4,	/* FCP-3: SAM-3 pwiowity */
			taskattw:3;	/* scsi task attwibute */
#ewse
	u8		taskattw:3,	/* scsi task attwibute */
			pwiowity:4,	/* FCP-3: SAM-3 pwiowity */
			wesvd:1;
#endif
	u8		tm_fwags;	/* task management fwags */
#ifdef __BIG_ENDIAN
	u8		addw_cdb_wen:6,	/* additionaw CDB wength wowds */
			iodiw:2;	/* wead/wwite FCP_DATA IUs */
#ewse
	u8		iodiw:2,	/* wead/wwite FCP_DATA IUs */
			addw_cdb_wen:6;	/* additionaw CDB wength */
#endif
	stwuct scsi_cdb_s      cdb;

	__be32        fcp_dw;	/* bytes to be twansfewwed */
};

#define fcp_cmnd_cdb_wen(_cmnd) ((_cmnd)->addw_cdb_wen * 4 + FCP_CMND_CDB_WEN)
#define fcp_cmnd_fcpdw(_cmnd)	((&(_cmnd)->fcp_dw)[(_cmnd)->addw_cdb_wen])

/*
 * stwuct fcp_cmnd_s .iodiw fiewd vawues
 */
enum fcp_iodiw {
	FCP_IODIW_NONE  = 0,
	FCP_IODIW_WWITE = 1,
	FCP_IODIW_WEAD  = 2,
	FCP_IODIW_WW    = 3,
};

/*
 * Task management fwags fiewd - onwy one bit shaww be set
 */
enum fcp_tm_cmnd {
	FCP_TM_ABOWT_TASK_SET	= BIT(1),
	FCP_TM_CWEAW_TASK_SET	= BIT(2),
	FCP_TM_WUN_WESET	= BIT(4),
	FCP_TM_TAWGET_WESET	= BIT(5),	/* obsowete in FCP-3 */
	FCP_TM_CWEAW_ACA	= BIT(6),
};

/*
 * FCP_WSP wesidue fwags
 */
enum fcp_wesidue {
	FCP_NO_WESIDUE = 0,     /* no wesidue */
	FCP_WESID_OVEW = 1,     /* mowe data weft that was not sent */
	FCP_WESID_UNDEW = 2,    /* wess data than wequested */
};

stwuct fcp_wspinfo_s {
	u32        wes0:24;
	u32        wsp_code:8;		/* wesponse code (as above) */
	u32        wes1;
};

stwuct fcp_wesp_s {
	u32        wesewved[2];		/* 2 wowds wesewved */
	u16        wesewved2;
#ifdef __BIG_ENDIAN
	u8         wesewved3:3;
	u8         fcp_conf_weq:1;	/* FCP_CONF is wequested */
	u8         wesid_fwags:2;	/* undewfwow/ovewfwow */
	u8         sns_wen_vawid:1;	/* sense wen is vawid */
	u8         wsp_wen_vawid:1;	/* wesponse wen is vawid */
#ewse
	u8         wsp_wen_vawid:1;	/* wesponse wen is vawid */
	u8         sns_wen_vawid:1;	/* sense wen is vawid */
	u8         wesid_fwags:2;	/* undewfwow/ovewfwow */
	u8         fcp_conf_weq:1;	/* FCP_CONF is wequested */
	u8         wesewved3:3;
#endif
	u8         scsi_status;		/* one byte SCSI status */
	u32        wesidue;		/* wesiduaw data bytes */
	u32        sns_wen;		/* wength od sense info */
	u32        wsp_wen;		/* wength of wesponse info */
};

#define fcp_snswen(__fcpwsp)	((__fcpwsp)->sns_wen_vawid ?		\
					(__fcpwsp)->sns_wen : 0)
#define fcp_wspwen(__fcpwsp)	((__fcpwsp)->wsp_wen_vawid ?		\
					(__fcpwsp)->wsp_wen : 0)
#define fcp_wspinfo(__fcpwsp)	((stwuct fcp_wspinfo_s *)((__fcpwsp) + 1))
#define fcp_snsinfo(__fcpwsp)	(((u8 *)fcp_wspinfo(__fcpwsp)) +	\
						fcp_wspwen(__fcpwsp))
/*
 * CT
 */
stwuct ct_hdw_s {
	u32	wev_id:8;	/* Wevision of the CT */
	u32	in_id:24;	/* Initiatow Id */
	u32	gs_type:8;	/* Genewic sewvice Type */
	u32	gs_sub_type:8;	/* Genewic sewvice sub type */
	u32	options:8;	/* options */
	u32	wsvwd:8;	/* wesewved */
	u32	cmd_wsp_code:16;/* ct command/wesponse code */
	u32	max_wes_size:16;/* maximum/wesiduaw size */
	u32	fwag_id:8;	/* fwagment ID */
	u32	weason_code:8;	/* weason code */
	u32	exp_code:8;	/* expwanation code */
	u32	vendow_unq:8;	/* vendow unique */
};

/*
 * defines fow the Wevision
 */
enum {
	CT_GS3_WEVISION = 0x01,
};

/*
 * defines fow gs_type
 */
enum {
	CT_GSTYPE_KEYSEWVICE	= 0xF7,
	CT_GSTYPE_AWIASSEWVICE	= 0xF8,
	CT_GSTYPE_MGMTSEWVICE	= 0xFA,
	CT_GSTYPE_TIMESEWVICE	= 0xFB,
	CT_GSTYPE_DIWSEWVICE	= 0xFC,
};

/*
 * defines fow gs_sub_type fow gs type diwectowy sewvice
 */
enum {
	CT_GSSUBTYPE_NAMESEWVEW = 0x02,
};

/*
 * defines fow gs_sub_type fow gs type management sewvice
 */
enum {
	CT_GSSUBTYPE_CFGSEWVEW	= 0x01,
	CT_GSSUBTYPE_UNZONED_NS = 0x02,
	CT_GSSUBTYPE_ZONESEWVEW = 0x03,
	CT_GSSUBTYPE_WOCKSEWVEW = 0x04,
	CT_GSSUBTYPE_HBA_MGMTSEWVEW = 0x10,	/* fow FDMI */
};

/*
 * defines fow CT wesponse code fiewd
 */
enum {
	CT_WSP_WEJECT = 0x8001,
	CT_WSP_ACCEPT = 0x8002,
};

/*
 * definitions fow CT weason code
 */
enum {
	CT_WSN_INV_CMD		= 0x01,
	CT_WSN_INV_VEW		= 0x02,
	CT_WSN_WOGIC_EWW	= 0x03,
	CT_WSN_INV_SIZE		= 0x04,
	CT_WSN_WOGICAW_BUSY	= 0x05,
	CT_WSN_PWOTO_EWW	= 0x07,
	CT_WSN_UNABWE_TO_PEWF	= 0x09,
	CT_WSN_NOT_SUPP		= 0x0B,
	CT_WSN_SEWVEW_NOT_AVBW  = 0x0D,
	CT_WSN_SESSION_COUWD_NOT_BE_ESTBD = 0x0E,
	CT_WSN_VENDOW_SPECIFIC  = 0xFF,

};

/*
 * definitions fow expwanations code fow Name sewvew
 */
enum {
	CT_NS_EXP_NOADDITIONAW	= 0x00,
	CT_NS_EXP_ID_NOT_WEG	= 0x01,
	CT_NS_EXP_PN_NOT_WEG	= 0x02,
	CT_NS_EXP_NN_NOT_WEG	= 0x03,
	CT_NS_EXP_CS_NOT_WEG	= 0x04,
	CT_NS_EXP_IPN_NOT_WEG	= 0x05,
	CT_NS_EXP_IPA_NOT_WEG	= 0x06,
	CT_NS_EXP_FT_NOT_WEG	= 0x07,
	CT_NS_EXP_SPN_NOT_WEG	= 0x08,
	CT_NS_EXP_SNN_NOT_WEG	= 0x09,
	CT_NS_EXP_PT_NOT_WEG	= 0x0A,
	CT_NS_EXP_IPP_NOT_WEG	= 0x0B,
	CT_NS_EXP_FPN_NOT_WEG	= 0x0C,
	CT_NS_EXP_HA_NOT_WEG	= 0x0D,
	CT_NS_EXP_FD_NOT_WEG	= 0x0E,
	CT_NS_EXP_FF_NOT_WEG	= 0x0F,
	CT_NS_EXP_ACCESSDENIED	= 0x10,
	CT_NS_EXP_UNACCEPTABWE_ID = 0x11,
	CT_NS_EXP_DATABASEEMPTY		= 0x12,
	CT_NS_EXP_NOT_WEG_IN_SCOPE	= 0x13,
	CT_NS_EXP_DOM_ID_NOT_PWESENT	= 0x14,
	CT_NS_EXP_POWT_NUM_NOT_PWESENT	= 0x15,
	CT_NS_EXP_NO_DEVICE_ATTACHED	= 0x16
};

/*
 * definitions fow the expwanation code fow aww sewvews
 */
enum {
	CT_EXP_AUTH_EXCEPTION		= 0xF1,
	CT_EXP_DB_FUWW			= 0xF2,
	CT_EXP_DB_EMPTY			= 0xF3,
	CT_EXP_PWOCESSING_WEQ		= 0xF4,
	CT_EXP_UNABWE_TO_VEWIFY_CONN	= 0xF5,
	CT_EXP_DEVICES_NOT_IN_CMN_ZONE  = 0xF6
};

/*
 * Command codes fow Name sewvew
 */
enum {
	GS_GID_PN	= 0x0121,	/* Get Id on powt name */
	GS_GPN_ID	= 0x0112,	/* Get powt name on ID */
	GS_GNN_ID	= 0x0113,	/* Get node name on ID */
	GS_GID_FT	= 0x0171,	/* Get Id on FC4 type */
	GS_GSPN_ID	= 0x0118,	/* Get symbowic PN on ID */
	GS_WFT_ID	= 0x0217,	/* Wegistew fc4type on ID */
	GS_WSPN_ID	= 0x0218,	/* Wegistew symbowic PN on ID */
	GS_WSNN_NN	= 0x0239,	/* Wegistew symbowic NN on NN */
	GS_WPN_ID	= 0x0212,	/* Wegistew powt name */
	GS_WNN_ID	= 0x0213,	/* Wegistew node name */
	GS_WCS_ID	= 0x0214,	/* Wegistew cwass of sewvice */
	GS_WPT_ID	= 0x021A,	/* Wegistew powt type */
	GS_GA_NXT	= 0x0100,	/* Get aww next */
	GS_WFF_ID	= 0x021F,	/* Wegistew FC4 Featuwe		*/
};

stwuct fcgs_id_weq_s {
	u32 wsvd:8;
	u32 dap:24; /* powt identifiew */
};
#define fcgs_gpnid_weq_t stwuct fcgs_id_weq_s
#define fcgs_gnnid_weq_t stwuct fcgs_id_weq_s
#define fcgs_gspnid_weq_t stwuct fcgs_id_weq_s

stwuct fcgs_gidpn_weq_s {
	wwn_t	powt_name;	/* powt wwn */
};

stwuct fcgs_gidpn_wesp_s {
	u32	wsvd:8;
	u32	dap:24;		/* powt identifiew */
};

/*
 * WFT_ID
 */
stwuct fcgs_wftid_weq_s {
	u32	wsvd:8;
	u32	dap:24;		/* powt identifiew */
	__be32	fc4_type[8];	/* fc4 types */
};

/*
 * WFF_ID : Wegistew FC4 featuwes.
 */
#define FC_GS_FCP_FC4_FEATUWE_INITIATOW  0x02
#define FC_GS_FCP_FC4_FEATUWE_TAWGET	 0x01

stwuct fcgs_wffid_weq_s {
	u32	wsvd:8;
	u32	dap:24;		/* powt identifiew */
	u32	wsvd1:16;
	u32	fc4ftw_bits:8;	/* fc4 featuwe bits */
	u32	fc4_type:8;		/* cowwesponding FC4 Type */
};

/*
 * GID_FT Wequest
 */
stwuct fcgs_gidft_weq_s {
	u8	wesewved;
	u8	domain_id;	/* domain, 0 - aww fabwic */
	u8	awea_id;	/* awea, 0 - whowe domain */
	u8	fc4_type;	/* FC_TYPE_FCP fow SCSI devices */
};

/*
 * GID_FT Wesponse
 */
stwuct fcgs_gidft_wesp_s {
	u8	wast:1;		/* wast powt identifiew fwag */
	u8	wesewved:7;
	u32	pid:24;		/* powt identifiew */
};

/*
 * WSPN_ID
 */
stwuct fcgs_wspnid_weq_s {
	u32	wsvd:8;
	u32	dap:24;		/* powt identifiew */
	u8	spn_wen;	/* symbowic powt name wength */
	u8	spn[256];	/* symbowic powt name */
};

/*
 * WSNN_NN
 */
stwuct fcgs_wsnn_nn_weq_s {
	wwn_t	node_name;	/* Node name */
	u8	snn_wen;	/* symbowic node name wength */
	u8	snn[256];	/* symbowic node name */
};

/*
 * WPN_ID
 */
stwuct fcgs_wpnid_weq_s {
	u32	wsvd:8;
	u32	powt_id:24;
	wwn_t	powt_name;
};

/*
 * WNN_ID
 */
stwuct fcgs_wnnid_weq_s {
	u32	wsvd:8;
	u32	powt_id:24;
	wwn_t	node_name;
};

/*
 * WCS_ID
 */
stwuct fcgs_wcsid_weq_s {
	u32	wsvd:8;
	u32	powt_id:24;
	u32	cos;
};

/*
 * WPT_ID
 */
stwuct fcgs_wptid_weq_s {
	u32	wsvd:8;
	u32	powt_id:24;
	u32	powt_type:8;
	u32	wsvd1:24;
};

/*
 * GA_NXT Wequest
 */
stwuct fcgs_ganxt_weq_s {
	u32	wsvd:8;
	u32	powt_id:24;
};

/*
 * GA_NXT Wesponse
 */
stwuct fcgs_ganxt_wsp_s {
	u32		powt_type:8;	/* Powt Type */
	u32		powt_id:24;	/* Powt Identifiew */
	wwn_t		powt_name;	/* Powt Name */
	u8		spn_wen;	/* Wength of Symbowic Powt Name */
	chaw		spn[255];	/* Symbowic Powt Name */
	wwn_t		node_name;	/* Node Name */
	u8		snn_wen;	/* Wength of Symbowic Node Name */
	chaw		snn[255];	/* Symbowic Node Name */
	u8		ipa[8];		/* Initiaw Pwocess Associatow */
	u8		ip[16];		/* IP Addwess */
	u32		cos;		/* Cwass of Sewvice */
	u32		fc4types[8];	/* FC-4 TYPEs */
	wwn_t		fabwic_powt_name; /* Fabwic Powt Name */
	u32		wsvd:8;		/* Wesewved */
	u32		hawd_addw:24;	/* Hawd Addwess */
};

/*
 * Command codes fow Fabwic Configuwation Sewvew
 */
enum {
	GS_FC_GFN_CMD	= 0x0114,	/* GS FC Get Fabwic Name  */
	GS_FC_GMAW_CMD	= 0x0116,	/* GS FC GMAW  */
	GS_FC_TWACE_CMD	= 0x0400,	/* GS FC Twace Woute */
	GS_FC_PING_CMD	= 0x0401,	/* GS FC Ping */
};

/*
 * GMAW Command ( Get ( intewconnect Ewement) Management Addwess Wist)
 * To wetwieve the IP Addwess of a Switch.
 */
#define CT_GMAW_WESP_PWEFIX_TEWNET	 "tewnet://"
#define CT_GMAW_WESP_PWEFIX_HTTP	 "http://"

/*  GMAW/GFN wequest */
stwuct fcgs_weq_s {
	wwn_t    wwn;   /* PWWN/NWWN */
};

#define fcgs_gmaw_weq_t stwuct fcgs_weq_s
#define fcgs_gfn_weq_t stwuct fcgs_weq_s

/* Accept Wesponse to GMAW */
stwuct fcgs_gmaw_wesp_s {
	__be32	ms_wen;   /* Num of entwies */
	u8	ms_ma[256];
};

stwuct fcgs_gmaw_entwy_s {
	u8  wen;
	u8  pwefix[7]; /* wike "http://" */
	u8  ip_addw[248];
};

/*
 * FDMI Command Codes
 */
#define	FDMI_GWHW		0x0100
#define	FDMI_GHAT		0x0101
#define	FDMI_GWPW		0x0102
#define	FDMI_GPAT		0x0110
#define	FDMI_WHBA		0x0200
#define	FDMI_WHAT		0x0201
#define	FDMI_WPWT		0x0210
#define	FDMI_WPA		0x0211
#define	FDMI_DHBA		0x0300
#define	FDMI_DPWT		0x0310

/*
 * FDMI weason codes
 */
#define	FDMI_NO_ADDITIONAW_EXP		0x00
#define	FDMI_HBA_AWWEADY_WEG		0x10
#define	FDMI_HBA_ATTWIB_NOT_WEG		0x11
#define	FDMI_HBA_ATTWIB_MUWTIPWE	0x12
#define	FDMI_HBA_ATTWIB_WENGTH_INVAWID	0x13
#define	FDMI_HBA_ATTWIB_NOT_PWESENT	0x14
#define	FDMI_POWT_OWIG_NOT_IN_WIST	0x15
#define	FDMI_POWT_HBA_NOT_IN_WIST	0x16
#define	FDMI_POWT_ATTWIB_NOT_WEG	0x20
#define	FDMI_POWT_NOT_WEG		0x21
#define	FDMI_POWT_ATTWIB_MUWTIPWE	0x22
#define	FDMI_POWT_ATTWIB_WENGTH_INVAWID	0x23
#define	FDMI_POWT_AWWEADY_WEGISTEWEED	0x24

/*
 * FDMI Twansmission Speed Mask vawues
 */
#define	FDMI_TWANS_SPEED_1G		0x00000001
#define	FDMI_TWANS_SPEED_2G		0x00000002
#define	FDMI_TWANS_SPEED_10G		0x00000004
#define	FDMI_TWANS_SPEED_4G		0x00000008
#define	FDMI_TWANS_SPEED_8G		0x00000010
#define	FDMI_TWANS_SPEED_16G		0x00000020
#define	FDMI_TWANS_SPEED_UNKNOWN	0x00008000

/*
 * FDMI HBA attwibute types
 */
enum fdmi_hba_attwibute_type {
	FDMI_HBA_ATTWIB_NODENAME = 1,	/* 0x0001 */
	FDMI_HBA_ATTWIB_MANUFACTUWEW,	/* 0x0002 */
	FDMI_HBA_ATTWIB_SEWIAWNUM,	/* 0x0003 */
	FDMI_HBA_ATTWIB_MODEW,		/* 0x0004 */
	FDMI_HBA_ATTWIB_MODEW_DESC,	/* 0x0005 */
	FDMI_HBA_ATTWIB_HW_VEWSION,	/* 0x0006 */
	FDMI_HBA_ATTWIB_DWIVEW_VEWSION,	/* 0x0007 */
	FDMI_HBA_ATTWIB_WOM_VEWSION,	/* 0x0008 */
	FDMI_HBA_ATTWIB_FW_VEWSION,	/* 0x0009 */
	FDMI_HBA_ATTWIB_OS_NAME,	/* 0x000A */
	FDMI_HBA_ATTWIB_MAX_CT,		/* 0x000B */
	FDMI_HBA_ATTWIB_NODE_SYM_NAME,  /* 0x000C */
	FDMI_HBA_ATTWIB_VENDOW_INFO,    /* 0x000D */
	FDMI_HBA_ATTWIB_NUM_POWTS,  /* 0x000E */
	FDMI_HBA_ATTWIB_FABWIC_NAME,    /* 0x000F */
	FDMI_HBA_ATTWIB_BIOS_VEW,   /* 0x0010 */
	FDMI_HBA_ATTWIB_VENDOW_ID = 0x00E0,

	FDMI_HBA_ATTWIB_MAX_TYPE
};

/*
 * FDMI Powt attwibute types
 */
enum fdmi_powt_attwibute_type {
	FDMI_POWT_ATTWIB_FC4_TYPES = 1,	/* 0x0001 */
	FDMI_POWT_ATTWIB_SUPP_SPEED,	/* 0x0002 */
	FDMI_POWT_ATTWIB_POWT_SPEED,	/* 0x0003 */
	FDMI_POWT_ATTWIB_FWAME_SIZE,	/* 0x0004 */
	FDMI_POWT_ATTWIB_DEV_NAME,	/* 0x0005 */
	FDMI_POWT_ATTWIB_HOST_NAME,	/* 0x0006 */
	FDMI_POWT_ATTWIB_NODE_NAME,     /* 0x0007 */
	FDMI_POWT_ATTWIB_POWT_NAME,     /* 0x0008 */
	FDMI_POWT_ATTWIB_POWT_SYM_NAME, /* 0x0009 */
	FDMI_POWT_ATTWIB_POWT_TYPE,     /* 0x000A */
	FDMI_POWT_ATTWIB_SUPP_COS,      /* 0x000B */
	FDMI_POWT_ATTWIB_POWT_FAB_NAME, /* 0x000C */
	FDMI_POWT_ATTWIB_POWT_FC4_TYPE, /* 0x000D */
	FDMI_POWT_ATTWIB_POWT_STATE = 0x101,    /* 0x0101 */
	FDMI_POWT_ATTWIB_POWT_NUM_WPWT = 0x102, /* 0x0102 */

	FDMI_POWT_ATTW_MAX_TYPE
};

/*
 * FDMI attwibute
 */
stwuct fdmi_attw_s {
	__be16        type;
	__be16        wen;
	u8         vawue[];
};

/*
 * HBA Attwibute Bwock
 */
stwuct fdmi_hba_attw_s {
	__be32        attw_count;	/* # of attwibutes */
	stwuct fdmi_attw_s hba_attw;	/* n attwibutes */
};

/*
 * Wegistewed Powt Wist
 */
stwuct fdmi_powt_wist_s {
	__be32		num_powts;	/* numbew Of Powt Entwies */
	wwn_t		powt_entwy;	/* one ow mowe */
};

/*
 * Powt Attwibute Bwock
 */
stwuct fdmi_powt_attw_s {
	__be32        attw_count;	/* # of attwibutes */
	stwuct fdmi_attw_s powt_attw;	/* n attwibutes */
};

/*
 * FDMI Wegistew HBA Attwibutes
 */
stwuct fdmi_whba_s {
	wwn_t			hba_id;		/* HBA Identifiew */
	stwuct fdmi_powt_wist_s powt_wist;	/* Wegistewed Powt Wist */
	stwuct fdmi_hba_attw_s hba_attw_bwk;	/* HBA attwibute bwock */
};

/*
 * FDMI Wegistew Powt
 */
stwuct fdmi_wpwt_s {
	wwn_t			hba_id;		/* HBA Identifiew */
	wwn_t			powt_name;	/* Powt wwn */
	stwuct fdmi_powt_attw_s powt_attw_bwk;	/* Powt Attw Bwock */
};

/*
 * FDMI Wegistew Powt Attwibutes
 */
stwuct fdmi_wpa_s {
	wwn_t			powt_name;	/* powt wwn */
	stwuct fdmi_powt_attw_s powt_attw_bwk;	/* Powt Attw Bwock */
};

#pwagma pack()

#endif	/* __BFA_FC_H__ */
