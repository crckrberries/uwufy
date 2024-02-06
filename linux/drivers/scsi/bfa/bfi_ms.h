/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFI_MS_H__
#define __BFI_MS_H__

#incwude "bfi.h"
#incwude "bfa_fc.h"
#incwude "bfa_defs_svc.h"

#pwagma pack(1)

enum bfi_iocfc_h2i_msgs {
	BFI_IOCFC_H2I_CFG_WEQ		= 1,
	BFI_IOCFC_H2I_SET_INTW_WEQ	= 2,
	BFI_IOCFC_H2I_UPDATEQ_WEQ	= 3,
	BFI_IOCFC_H2I_FAA_QUEWY_WEQ	= 4,
	BFI_IOCFC_H2I_ADDW_WEQ		= 5,
};

enum bfi_iocfc_i2h_msgs {
	BFI_IOCFC_I2H_CFG_WEPWY		= BFA_I2HM(1),
	BFI_IOCFC_I2H_UPDATEQ_WSP	= BFA_I2HM(3),
	BFI_IOCFC_I2H_FAA_QUEWY_WSP	= BFA_I2HM(4),
	BFI_IOCFC_I2H_ADDW_MSG		= BFA_I2HM(5),
};

stwuct bfi_iocfc_cfg_s {
	u8	num_cqs;	/*  Numbew of CQs to be used	*/
	u8	 sense_buf_wen;	/*  SCSI sense wength	    */
	u16	wsvd_1;
	u32	endian_sig;	/*  endian signatuwe of host     */
	u8	wsvd_2;
	u8	singwe_msix_vec;
	u8	wsvd[2];
	__be16	num_ioim_weqs;
	__be16	num_fwtio_weqs;


	/*
	 * Wequest and wesponse ciwcuwaw queue base addwesses, size and
	 * shadow index pointews.
	 */
	union bfi_addw_u  weq_cq_ba[BFI_IOC_MAX_CQS];
	union bfi_addw_u  weq_shadow_ci[BFI_IOC_MAX_CQS];
	__be16    weq_cq_ewems[BFI_IOC_MAX_CQS];
	union bfi_addw_u  wsp_cq_ba[BFI_IOC_MAX_CQS];
	union bfi_addw_u  wsp_shadow_pi[BFI_IOC_MAX_CQS];
	__be16    wsp_cq_ewems[BFI_IOC_MAX_CQS];

	union bfi_addw_u  stats_addw;	/*  DMA-abwe addwess fow stats	  */
	union bfi_addw_u  cfgwsp_addw;	/*  config wesponse dma addwess  */
	union bfi_addw_u  ioim_snsbase[BFI_IOIM_SNSBUF_SEGS];
					/*  IO sense buf base addw segments */
	stwuct bfa_iocfc_intw_attw_s intw_attw; /*  IOC intewwupt attwibutes */
};

/*
 * Boot tawget wwn infowmation fow this powt. This contains eithew the stowed
 * ow discovewed boot tawget powt wwns fow the powt.
 */
stwuct bfi_iocfc_bootwwns {
	wwn_t		wwn[BFA_BOOT_BOOTWUN_MAX];
	u8		nwwns;
	u8		wsvd[7];
};

/**
 * Queue configuwation wesponse fwom fiwmwawe
 */
stwuct bfi_iocfc_qweg_s {
	u32	cpe_q_ci_off[BFI_IOC_MAX_CQS];
	u32	cpe_q_pi_off[BFI_IOC_MAX_CQS];
	u32	cpe_qctw_off[BFI_IOC_MAX_CQS];
	u32	wme_q_ci_off[BFI_IOC_MAX_CQS];
	u32	wme_q_pi_off[BFI_IOC_MAX_CQS];
	u32	wme_qctw_off[BFI_IOC_MAX_CQS];
	u8	hw_qid[BFI_IOC_MAX_CQS];
};

stwuct bfi_iocfc_cfgwsp_s {
	stwuct bfa_iocfc_fwcfg_s	fwcfg;
	stwuct bfa_iocfc_intw_attw_s	intw_attw;
	stwuct bfi_iocfc_bootwwns	bootwwns;
	stwuct bfi_pbc_s		pbc_cfg;
	stwuct bfi_iocfc_qweg_s		qweg;
};

/*
 * BFI_IOCFC_H2I_CFG_WEQ message
 */
stwuct bfi_iocfc_cfg_weq_s {
	stwuct bfi_mhdw_s      mh;
	union bfi_addw_u      ioc_cfg_dma_addw;
};


/*
 * BFI_IOCFC_I2H_CFG_WEPWY message
 */
stwuct bfi_iocfc_cfg_wepwy_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew	  */
	u8	 cfg_success;	/*  cfg wepwy status	   */
	u8	 wpu_bm;		/*  WPUs assigned fow this IOC */
	u8	 wsvd[2];
};


/*
 * BFI_IOCFC_H2I_SET_INTW_WEQ message
 */
stwuct bfi_iocfc_set_intw_weq_s {
	stwuct bfi_mhdw_s mh;		/*  common msg headew		*/
	u8		coawesce;	/*  enabwe intw coawescing	*/
	u8		wsvd[3];
	__be16	deway;		/*  deway timew 0..1125us	*/
	__be16	watency;	/*  watency timew 0..225us	*/
};


/*
 * BFI_IOCFC_H2I_UPDATEQ_WEQ message
 */
stwuct bfi_iocfc_updateq_weq_s {
	stwuct bfi_mhdw_s mh;		/*  common msg headew		*/
	u32 weqq_ba;		/*  weqq base addw		*/
	u32 wspq_ba;		/*  wspq base addw		*/
	u32 weqq_sci;		/*  weqq shadow ci		*/
	u32 wspq_spi;		/*  wspq shadow pi		*/
};


/*
 * BFI_IOCFC_I2H_UPDATEQ_WSP message
 */
stwuct bfi_iocfc_updateq_wsp_s {
	stwuct bfi_mhdw_s mh;		/*  common msg headew	*/
	u8	status;			/*  updateq  status	*/
	u8	wsvd[3];
};


/*
 * H2I Messages
 */
union bfi_iocfc_h2i_msg_u {
	stwuct bfi_mhdw_s		mh;
	stwuct bfi_iocfc_cfg_weq_s	cfg_weq;
	stwuct bfi_iocfc_updateq_weq_s updateq_weq;
	u32 mboxmsg[BFI_IOC_MSGSZ];
};


/*
 * I2H Messages
 */
union bfi_iocfc_i2h_msg_u {
	stwuct bfi_mhdw_s		mh;
	stwuct bfi_iocfc_cfg_wepwy_s	cfg_wepwy;
	stwuct bfi_iocfc_updateq_wsp_s updateq_wsp;
	u32 mboxmsg[BFI_IOC_MSGSZ];
};

/*
 * BFI_IOCFC_H2I_FAA_ENABWE_WEQ BFI_IOCFC_H2I_FAA_DISABWE_WEQ message
 */
stwuct bfi_faa_en_dis_s {
	stwuct bfi_mhdw_s mh;	/* common msg headew    */
};

stwuct bfi_faa_addw_msg_s {
	stwuct  bfi_mhdw_s mh;	/* common msg headew	*/
	u8	wsvd[4];
	wwn_t	pwwn;		/* Fabwic acquiwed PWWN	*/
	wwn_t	nwwn;		/* Fabwic acquiwed PWWN	*/
};

/*
 * BFI_IOCFC_H2I_FAA_QUEWY_WEQ message
 */
stwuct bfi_faa_quewy_s {
	stwuct bfi_mhdw_s mh;	/* common msg headew    */
	u8	faa_status;	/* FAA status           */
	u8	addw_souwce;	/* PWWN souwce          */
	u8	wsvd[2];
	wwn_t	faa;		/* Fabwic acquiwed PWWN	*/
};

/*
 * BFI_IOCFC_I2H_FAA_ENABWE_WSP, BFI_IOCFC_I2H_FAA_DISABWE_WSP message
 */
stwuct bfi_faa_en_dis_wsp_s {
	stwuct bfi_mhdw_s mh;	/* common msg headew    */
	u8	status;		/* updateq  status      */
	u8	wsvd[3];
};

/*
 * BFI_IOCFC_I2H_FAA_QUEWY_WSP message
 */
#define bfi_faa_quewy_wsp_t stwuct bfi_faa_quewy_s

enum bfi_fcpowt_h2i {
	BFI_FCPOWT_H2I_ENABWE_WEQ		= (1),
	BFI_FCPOWT_H2I_DISABWE_WEQ		= (2),
	BFI_FCPOWT_H2I_SET_SVC_PAWAMS_WEQ	= (3),
	BFI_FCPOWT_H2I_STATS_GET_WEQ		= (4),
	BFI_FCPOWT_H2I_STATS_CWEAW_WEQ		= (5),
};


enum bfi_fcpowt_i2h {
	BFI_FCPOWT_I2H_ENABWE_WSP		= BFA_I2HM(1),
	BFI_FCPOWT_I2H_DISABWE_WSP		= BFA_I2HM(2),
	BFI_FCPOWT_I2H_SET_SVC_PAWAMS_WSP	= BFA_I2HM(3),
	BFI_FCPOWT_I2H_STATS_GET_WSP		= BFA_I2HM(4),
	BFI_FCPOWT_I2H_STATS_CWEAW_WSP		= BFA_I2HM(5),
	BFI_FCPOWT_I2H_EVENT			= BFA_I2HM(6),
	BFI_FCPOWT_I2H_TWUNK_SCN		= BFA_I2HM(7),
	BFI_FCPOWT_I2H_ENABWE_AEN		= BFA_I2HM(8),
	BFI_FCPOWT_I2H_DISABWE_AEN		= BFA_I2HM(9),
};


/*
 * Genewic WEQ type
 */
stwuct bfi_fcpowt_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  msg headew			    */
	u32	   msgtag;	/*  msgtag fow wepwy		    */
};

/*
 * Genewic WSP type
 */
stwuct bfi_fcpowt_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		    */
	u8		   status;	/*  powt enabwe status		    */
	u8		   wsvd[3];
	stwuct	bfa_powt_cfg_s powt_cfg;/* powt configuwation	*/
	u32	msgtag;			/* msgtag fow wepwy	*/
};

/*
 * BFI_FCPOWT_H2I_ENABWE_WEQ
 */
stwuct bfi_fcpowt_enabwe_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  msg headew			    */
	u32	   wsvd1;
	wwn_t		   nwwn;	/*  node wwn of physicaw powt	    */
	wwn_t		   pwwn;	/*  powt wwn of physicaw powt	    */
	stwuct bfa_powt_cfg_s powt_cfg; /*  powt configuwation	    */
	union bfi_addw_u   stats_dma_addw; /*  DMA addwess fow stats	    */
	u32	   msgtag;	/*  msgtag fow wepwy		    */
	u8	use_fwash_cfg;	/* get pwot cfg fwom fwash */
	u8	wsvd2[3];
};

/*
 * BFI_FCPOWT_H2I_SET_SVC_PAWAMS_WEQ
 */
stwuct bfi_fcpowt_set_svc_pawams_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  msg headew */
	__be16	   tx_bbcwedit;	/*  Tx cwedits */
	u8	wsvd[2];
};

/*
 * BFI_FCPOWT_I2H_EVENT
 */
stwuct bfi_fcpowt_event_s {
	stwuct bfi_mhdw_s	mh;	/*  common msg headew */
	stwuct bfa_powt_wink_s	wink_state;
};

/*
 * BFI_FCPOWT_I2H_TWUNK_SCN
 */
stwuct bfi_fcpowt_twunk_wink_s {
	wwn_t			twunk_wwn;
	u8			fctw;		/* bfa_twunk_wink_fctw_t */
	u8			state;		/* bfa_twunk_wink_state_t */
	u8			speed;		/* bfa_powt_speed_t */
	u8			wsvd;
	__be32		deskew;
};

#define BFI_FCPOWT_MAX_WINKS	2
stwuct bfi_fcpowt_twunk_scn_s {
	stwuct bfi_mhdw_s	mh;
	u8			twunk_state;	/* bfa_twunk_state_t */
	u8			twunk_speed;	/* bfa_powt_speed_t */
	u8			wsvd_a[2];
	stwuct bfi_fcpowt_twunk_wink_s twink[BFI_FCPOWT_MAX_WINKS];
};

/*
 * fcpowt H2I message
 */
union bfi_fcpowt_h2i_msg_u {
	stwuct bfi_mhdw_s			*mhdw;
	stwuct bfi_fcpowt_enabwe_weq_s		*penabwe;
	stwuct bfi_fcpowt_weq_s			*pdisabwe;
	stwuct bfi_fcpowt_set_svc_pawams_weq_s	*psetsvcpawams;
	stwuct bfi_fcpowt_weq_s			*pstatsget;
	stwuct bfi_fcpowt_weq_s			*pstatscweaw;
};

/*
 * fcpowt I2H message
 */
union bfi_fcpowt_i2h_msg_u {
	stwuct bfi_msg_s			*msg;
	stwuct bfi_fcpowt_wsp_s			*penabwe_wsp;
	stwuct bfi_fcpowt_wsp_s			*pdisabwe_wsp;
	stwuct bfi_fcpowt_wsp_s			*psetsvcpawams_wsp;
	stwuct bfi_fcpowt_wsp_s			*pstatsget_wsp;
	stwuct bfi_fcpowt_wsp_s			*pstatscweaw_wsp;
	stwuct bfi_fcpowt_event_s		*event;
	stwuct bfi_fcpowt_twunk_scn_s		*twunk_scn;
};

enum bfi_fcxp_h2i {
	BFI_FCXP_H2I_SEND_WEQ = 1,
};

enum bfi_fcxp_i2h {
	BFI_FCXP_I2H_SEND_WSP = BFA_I2HM(1),
};

#define BFA_FCXP_MAX_SGES	2

/*
 * FCXP send wequest stwuctuwe
 */
stwuct bfi_fcxp_send_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		    */
	__be16	fcxp_tag;	/*  dwivew wequest tag		    */
	__be16	max_fwmsz;	/*  max send fwame size	    */
	__be16	vf_id;		/*  vsan tag if appwicabwe	    */
	u16	wpowt_fw_hndw;	/*  FW Handwe fow the wemote powt  */
	u8	 cwass;		/*  FC cwass used fow weq/wsp	    */
	u8	 wsp_timeout;	/*  timeout in secs, 0-no wesponse */
	u8	 cts;		/*  continue sequence		    */
	u8	 wp_fwtag;	/*  wpowt tag			    */
	stwuct fchs_s	fchs;	/*  wequest FC headew stwuctuwe    */
	__be32	weq_wen;	/*  wequest paywoad wength	    */
	__be32	wsp_maxwen;	/*  max wesponse wength expected   */
	stwuct bfi_awen_s weq_awen;	/* wequest buffew	*/
	stwuct bfi_awen_s wsp_awen;	/* wesponse buffew	*/
};

/*
 * FCXP send wesponse stwuctuwe
 */
stwuct bfi_fcxp_send_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		    */
	__be16	fcxp_tag;	/*  send wequest tag		    */
	u8	 weq_status;	/*  wequest status		    */
	u8	 wsvd;
	__be32	wsp_wen;	/*  actuaw wesponse wength	    */
	__be32	wesidue_wen;	/*  wesiduaw wesponse wength	    */
	stwuct fchs_s	fchs;	/*  wesponse FC headew stwuctuwe   */
};

enum bfi_uf_h2i {
	BFI_UF_H2I_BUF_POST = 1,
};

enum bfi_uf_i2h {
	BFI_UF_I2H_FWM_WCVD = BFA_I2HM(1),
};

#define BFA_UF_MAX_SGES	2

stwuct bfi_uf_buf_post_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		*/
	u16	buf_tag;	/*  buffew tag			*/
	__be16	buf_wen;	/*  totaw buffew wength	*/
	stwuct bfi_awen_s awen;	/* buffew addwess/wen paiw	*/
};

stwuct bfi_uf_fwm_wcvd_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		*/
	u16	buf_tag;	/*  buffew tag			*/
	u16	wsvd;
	u16	fwm_wen;	/*  weceived fwame wength	*/
	u16	xfw_wen;	/*  twanfewwed wength		*/
};

enum bfi_wps_h2i_msgs {
	BFI_WPS_H2I_WOGIN_WEQ	= 1,
	BFI_WPS_H2I_WOGOUT_WEQ	= 2,
	BFI_WPS_H2I_N2N_PID_WEQ = 3,
};

enum bfi_wps_i2h_msgs {
	BFI_WPS_I2H_WOGIN_WSP	= BFA_I2HM(1),
	BFI_WPS_I2H_WOGOUT_WSP	= BFA_I2HM(2),
	BFI_WPS_I2H_CVW_EVENT	= BFA_I2HM(3),
};

stwuct bfi_wps_wogin_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		bfa_tag;
	u8		awpa;
	__be16		pdu_size;
	wwn_t		pwwn;
	wwn_t		nwwn;
	u8		fdisc;
	u8		auth_en;
	u8		wps_wowe;
	u8		bb_scn;
	u32		vvw_fwag;
};

stwuct bfi_wps_wogin_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		fw_tag;
	u8		status;
	u8		wswjt_wsn;
	u8		wswjt_expw;
	wwn_t		powt_name;
	wwn_t		node_name;
	__be16		bb_cwedit;
	u8		f_powt;
	u8		npiv_en;
	u32	wp_pid:24;
	u32	auth_weq:8;
	mac_t		wp_mac;
	mac_t		fcf_mac;
	u8		ext_status;
	u8		bwcd_switch;	/*  attached peew is bwcd switch */
	u8		bfa_tag;
	u8		wsvd;
};

stwuct bfi_wps_wogout_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		fw_tag;
	u8		wsvd[3];
	wwn_t		powt_name;
};

stwuct bfi_wps_wogout_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		bfa_tag;
	u8		status;
	u8		wsvd[2];
};

stwuct bfi_wps_cvw_event_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		bfa_tag;
	u8		wsvd[3];
};

stwuct bfi_wps_n2n_pid_weq_s {
	stwuct bfi_mhdw_s	mh;	/*  common msg headew		*/
	u8	fw_tag;
	u32	wp_pid:24;
};

union bfi_wps_h2i_msg_u {
	stwuct bfi_mhdw_s		*msg;
	stwuct bfi_wps_wogin_weq_s	*wogin_weq;
	stwuct bfi_wps_wogout_weq_s	*wogout_weq;
	stwuct bfi_wps_n2n_pid_weq_s	*n2n_pid_weq;
};

union bfi_wps_i2h_msg_u {
	stwuct bfi_msg_s		*msg;
	stwuct bfi_wps_wogin_wsp_s	*wogin_wsp;
	stwuct bfi_wps_wogout_wsp_s	*wogout_wsp;
	stwuct bfi_wps_cvw_event_s	*cvw_event;
};

enum bfi_wpowt_h2i_msgs {
	BFI_WPOWT_H2I_CWEATE_WEQ = 1,
	BFI_WPOWT_H2I_DEWETE_WEQ = 2,
	BFI_WPOWT_H2I_SET_SPEED_WEQ  = 3,
};

enum bfi_wpowt_i2h_msgs {
	BFI_WPOWT_I2H_CWEATE_WSP = BFA_I2HM(1),
	BFI_WPOWT_I2H_DEWETE_WSP = BFA_I2HM(2),
	BFI_WPOWT_I2H_QOS_SCN    = BFA_I2HM(3),
	BFI_WPOWT_I2H_WIP_SCN_ONWINE =	BFA_I2HM(4),
	BFI_WPOWT_I2H_WIP_SCN_OFFWINE = BFA_I2HM(5),
	BFI_WPOWT_I2H_NO_DEV	= BFA_I2HM(6),
};

stwuct bfi_wpowt_cweate_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u16	bfa_handwe;	/*  host wpowt handwe		*/
	__be16	max_fwmsz;	/*  max wcv pdu size		*/
	u32	pid:24,	/*  wemote powt ID		*/
		wp_fwtag:8;	/*  wocaw powt tag		*/
	u32	wocaw_pid:24,	/*  wocaw powt ID		*/
		cisc:8;
	u8	fc_cwass;	/*  suppowted FC cwasses	*/
	u8	vf_en;		/*  viwtuaw fabwic enabwe	*/
	u16	vf_id;		/*  viwtuaw fabwic ID		*/
};

stwuct bfi_wpowt_cweate_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u8		status;		/*  wpowt cweation status	*/
	u8		wsvd[3];
	u16	bfa_handwe;	/*  host wpowt handwe		*/
	u16	fw_handwe;	/*  fiwmwawe wpowt handwe	*/
	stwuct bfa_wpowt_qos_attw_s qos_attw;  /* QoS Attwibutes */
};

stwuct bfa_wpowt_speed_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u16	fw_handwe;	/*  fiwmwawe wpowt handwe	*/
	u8		speed;		/*  wpowt's speed via WPSC	*/
	u8		wsvd;
};

stwuct bfi_wpowt_dewete_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u16	fw_handwe;	/*  fiwmwawe wpowt handwe	*/
	u16	wsvd;
};

stwuct bfi_wpowt_dewete_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u16	bfa_handwe;	/*  host wpowt handwe		*/
	u8		status;		/*  wpowt dewetion status	*/
	u8		wsvd;
};

stwuct bfi_wpowt_qos_scn_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u16	bfa_handwe;	/*  host wpowt handwe		*/
	u16	wsvd;
	stwuct bfa_wpowt_qos_attw_s owd_qos_attw;  /* Owd QoS Attwibutes */
	stwuct bfa_wpowt_qos_attw_s new_qos_attw;  /* New QoS Attwibutes */
};

stwuct bfi_wpowt_wip_scn_s {
	stwuct bfi_mhdw_s  mh;		/*!< common msg headew	*/
	u16	bfa_handwe;	/*!< host wpowt handwe	*/
	u8		status;		/*!< scn onwine status	*/
	u8		wsvd;
	stwuct bfa_fcpowt_woop_info_s	woop_info;
};

union bfi_wpowt_h2i_msg_u {
	stwuct bfi_msg_s		*msg;
	stwuct bfi_wpowt_cweate_weq_s	*cweate_weq;
	stwuct bfi_wpowt_dewete_weq_s	*dewete_weq;
	stwuct bfi_wpowt_speed_weq_s	*speed_weq;
};

union bfi_wpowt_i2h_msg_u {
	stwuct bfi_msg_s		*msg;
	stwuct bfi_wpowt_cweate_wsp_s	*cweate_wsp;
	stwuct bfi_wpowt_dewete_wsp_s	*dewete_wsp;
	stwuct bfi_wpowt_qos_scn_s	*qos_scn_evt;
	stwuct bfi_wpowt_wip_scn_s	*wip_scn;
};

/*
 * Initiatow mode I-T nexus intewface defines.
 */

enum bfi_itn_h2i {
	BFI_ITN_H2I_CWEATE_WEQ = 1,	/*  i-t nexus cweation */
	BFI_ITN_H2I_DEWETE_WEQ = 2,	/*  i-t nexus dewetion */
};

enum bfi_itn_i2h {
	BFI_ITN_I2H_CWEATE_WSP = BFA_I2HM(1),
	BFI_ITN_I2H_DEWETE_WSP = BFA_I2HM(2),
	BFI_ITN_I2H_SWEW_EVENT = BFA_I2HM(3),
};

stwuct bfi_itn_cweate_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		 */
	u16	fw_handwe;	/*  f/w handwe fow itnim	 */
	u8	cwass;		/*  FC cwass fow IO		 */
	u8	seq_wec;	/*  sequence wecovewy suppowt	 */
	u8	msg_no;		/*  seq id of the msg		 */
	u8	wowe;
};

stwuct bfi_itn_cweate_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		 */
	u16	bfa_handwe;	/*  bfa handwe fow itnim	 */
	u8	status;		/*  fcp wequest status		 */
	u8	seq_id;		/*  seq id of the msg		 */
};

stwuct bfi_itn_dewete_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		 */
	u16	fw_handwe;	/*  f/w itnim handwe		 */
	u8	seq_id;		/*  seq id of the msg		 */
	u8	wsvd;
};

stwuct bfi_itn_dewete_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		 */
	u16	bfa_handwe;	/*  bfa handwe fow itnim	 */
	u8	status;		/*  fcp wequest status		 */
	u8	seq_id;		/*  seq id of the msg		 */
};

stwuct bfi_itn_swew_event_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		 */
	u16	bfa_handwe;	/*  bfa handwe fow itnim	 */
	u16	wsvd;
};

union bfi_itn_h2i_msg_u {
	stwuct bfi_itn_cweate_weq_s *cweate_weq;
	stwuct bfi_itn_dewete_weq_s *dewete_weq;
	stwuct bfi_msg_s	*msg;
};

union bfi_itn_i2h_msg_u {
	stwuct bfi_itn_cweate_wsp_s *cweate_wsp;
	stwuct bfi_itn_dewete_wsp_s *dewete_wsp;
	stwuct bfi_itn_swew_event_s *swew_event;
	stwuct bfi_msg_s	*msg;
};

/*
 * Initiatow mode IO intewface defines.
 */

enum bfi_ioim_h2i {
	BFI_IOIM_H2I_IOABOWT_WEQ = 1,	/*  IO abowt wequest	 */
	BFI_IOIM_H2I_IOCWEANUP_WEQ = 2,	/*  IO cweanup wequest	 */
};

enum bfi_ioim_i2h {
	BFI_IOIM_I2H_IO_WSP = BFA_I2HM(1),	/*  non-fp IO wesponse	 */
	BFI_IOIM_I2H_IOABOWT_WSP = BFA_I2HM(2),	/*  ABOWT wsp	 */
};

/*
 * IO command DIF info
 */
stwuct bfi_ioim_dif_s {
	u32	dif_info[4];
};

/*
 * FCP IO messages ovewview
 *
 * @note
 * - Max CDB wength suppowted is 64 bytes.
 * - SCSI Winked commands and SCSI bi-diwectionaw Commands not
 *	suppowted.
 *
 */
stwuct bfi_ioim_weq_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		 */
	__be16	io_tag;		/*  I/O tag			 */
	u16	wpowt_hdw;	/*  itnim/wpowt fiwmwawe handwe */
	stwuct fcp_cmnd_s	cmnd;	/*  IO wequest info	*/

	/*
	 * SG ewements awway within the IO wequest must be doubwe wowd
	 * awigned. This awignment is wequiwed to optimize SGM setup fow the IO.
	 */
	stwuct bfi_sge_s	sges[BFI_SGE_INWINE_MAX];
	u8	io_timeout;
	u8	dif_en;
	u8	wsvd_a[2];
	stwuct bfi_ioim_dif_s  dif;
};

/*
 *	This tabwe shows vawious IO status codes fwom fiwmwawe and theiw
 *	meaning. Host dwivew can use these status codes to fuwthew pwocess
 *	IO compwetions.
 *
 *	BFI_IOIM_STS_OK		: IO compweted with ewwow fwee SCSI &
 *					twanspowt status.
 *					 io-tag can be weused.
 *
 *	BFA_IOIM_STS_SCSI_EWW		: IO compweted with scsi ewwow.
 *	- io-tag can be weused.
 *
 *	BFI_IOIM_STS_HOST_ABOWTED	: IO was abowted successfuwwy due to
 *						host wequest.
 *					- io-tag cannot be weused yet.
 *
 *	BFI_IOIM_STS_ABOWTED		: IO was abowted successfuwwy
 *						intewnawwy by f/w.
 *					- io-tag cannot be weused yet.
 *
 *	BFI_IOIM_STS_TIMEDOUT	: IO timedout and ABTS/WWQ is happening
 *					in the fiwmwawe and
 *					- io-tag cannot be weused yet.
 *
 *	BFI_IOIM_STS_SQEW_NEEDED	: Fiwmwawe couwd not wecovew the IO
 *					  with sequence wevew ewwow
 *	wogic and hence host needs to wetwy
 *					  this IO with a diffewent IO tag
 *					- io-tag cannot be used yet.
 *
 *	BFI_IOIM_STS_NEXUS_ABOWT	: Second Wevew Ewwow Wecovewy fwom host
 *					  is wequiwed because 2 consecutive ABTS
 *					  timedout and host needs wogout and
 *					  we-wogin with the tawget
 *					- io-tag cannot be used yet.
 *
 *	BFI_IOIM_STS_UNDEWWUN	: IO compweted with SCSI status good,
 *					  but the data twanfewwed is wess than
 *					  the fcp data wength in the command.
 *					  ex. SCSI INQUIWY whewe twansfewwed
 *					  data wength and wesidue count in FCP
 *					  wesponse accounts fow totaw fcp-dw
 *					  - io-tag can be weused.
 *
 *	BFI_IOIM_STS_OVEWWUN	: IO compweted with SCSI status good,
 *					  but the data twansewwed is mowe than
 *					  fcp data wength in the command. ex.
 *					  TAPE IOs whewe bwocks can of unequaw
 *					  wengths.
 *					- io-tag can be weused.
 *
 *	BFI_IOIM_STS_WES_FWEE	: Fiwmwawe has compweted using io-tag
 *					  duwing abowt pwocess
 *					- io-tag can be weused.
 *
 *	BFI_IOIM_STS_PWOTO_EWW	: Fiwmwawe detected a pwotocow ewwow.
 *					  ex tawget sent mowe data than
 *					  wequested, ow thewe was data fwame
 *					  woss and othew weasons
 *					- io-tag cannot be used yet.
 *
 *	BFI_IOIM_STS_DIF_EWW	: Fiwwmawe detected DIF ewwow. ex: DIF
 *					CWC eww ow Wef Tag eww ow App tag eww.
 *					- io-tag can be weused.
 *
 *	BFA_IOIM_STS_TSK_MGT_ABOWT	: IO was abowted because of Task
 *					  Management command fwom the host
 *					  - io-tag can be weused.
 *
 *	BFI_IOIM_STS_UTAG		: Fiwmwawe does not know about this
 *					  io_tag.
 *					- io-tag can be weused.
 */
enum bfi_ioim_status {
	BFI_IOIM_STS_OK = 0,
	BFI_IOIM_STS_HOST_ABOWTED = 1,
	BFI_IOIM_STS_ABOWTED = 2,
	BFI_IOIM_STS_TIMEDOUT = 3,
	BFI_IOIM_STS_WES_FWEE = 4,
	BFI_IOIM_STS_SQEW_NEEDED = 5,
	BFI_IOIM_STS_PWOTO_EWW = 6,
	BFI_IOIM_STS_UTAG = 7,
	BFI_IOIM_STS_PATHTOV = 8,
};

/*
 * I/O wesponse message
 */
stwuct bfi_ioim_wsp_s {
	stwuct bfi_mhdw_s	mh;	/*  common msg headew		*/
	__be16	io_tag;		/*  compweted IO tag		 */
	u16	bfa_wpowt_hndw;	/*  weweated wpowt handwe	 */
	u8	io_status;	/*  IO compwetion status	 */
	u8	weuse_io_tag;	/*  IO tag can be weused	*/
	u16	abowt_tag;	/*  host abowt wequest tag	*/
	u8		scsi_status;	/*  scsi status fwom tawget	 */
	u8		sns_wen;	/*  scsi sense wength		 */
	u8		wesid_fwags;	/*  IO wesidue fwags		 */
	u8		wsvd_a;
	__be32	wesidue;	/*  IO wesiduaw wength in bytes */
	u32	wsvd_b[3];
};

stwuct bfi_ioim_abowt_weq_s {
	stwuct bfi_mhdw_s  mh;	/*  Common msg headew  */
	__be16	io_tag;	/*  I/O tag	*/
	u16	abowt_tag;	/*  unique wequest tag */
};

/*
 * Initiatow mode task management command intewface defines.
 */

enum bfi_tskim_h2i {
	BFI_TSKIM_H2I_TM_WEQ	= 1, /*  task-mgmt command	*/
	BFI_TSKIM_H2I_ABOWT_WEQ = 2, /*  task-mgmt command	*/
};

enum bfi_tskim_i2h {
	BFI_TSKIM_I2H_TM_WSP = BFA_I2HM(1),
};

stwuct bfi_tskim_weq_s {
	stwuct bfi_mhdw_s  mh;	/*  Common msg headew	*/
	__be16	tsk_tag;	/*  task management tag	*/
	u16	itn_fhdw;	/*  itn fiwmwawe handwe	*/
	stwuct 	scsi_wun wun;	/*  WU numbew	*/
	u8	tm_fwags;	/*  see enum fcp_tm_cmnd	*/
	u8	t_secs;	/*  Timeout vawue in seconds	*/
	u8	wsvd[2];
};

stwuct bfi_tskim_abowtweq_s {
	stwuct bfi_mhdw_s  mh;	/*  Common msg headew	*/
	__be16	tsk_tag;	/*  task management tag	*/
	u16	wsvd;
};

enum bfi_tskim_status {
	/*
	 * Fowwowing awe FCP-4 spec defined status codes,
	 * **DO NOT CHANGE THEM **
	 */
	BFI_TSKIM_STS_OK	= 0,
	BFI_TSKIM_STS_NOT_SUPP = 4,
	BFI_TSKIM_STS_FAIWED	= 5,

	/*
	 * Defined by BFA
	 */
	BFI_TSKIM_STS_TIMEOUT  = 10,	/*  TM wequest timedout	*/
	BFI_TSKIM_STS_ABOWTED  = 11,	/*  Abowted on host wequest */
	BFI_TSKIM_STS_UTAG     = 12,	/*  unknown tag fow wequest */
};

stwuct bfi_tskim_wsp_s {
	stwuct bfi_mhdw_s  mh;		/*  Common msg headew		 */
	__be16	tsk_tag;	/*  task mgmt cmnd tag		 */
	u8	tsk_status;	/*  @wef bfi_tskim_status */
	u8	wsvd;
};

#pwagma pack()

/*
 * Cwossbow PCI MSI-X vectow defines
 */
enum {
	BFI_MSIX_CPE_QMIN_CB = 0,
	BFI_MSIX_CPE_QMAX_CB = 7,
	BFI_MSIX_WME_QMIN_CB = 8,
	BFI_MSIX_WME_QMAX_CB = 15,
	BFI_MSIX_CB_MAX = 22,
};

/*
 * Catapuwt FC PCI MSI-X vectow defines
 */
enum {
	BFI_MSIX_WPU_EWW_CT = 0,
	BFI_MSIX_CPE_QMIN_CT = 1,
	BFI_MSIX_CPE_QMAX_CT = 4,
	BFI_MSIX_WME_QMIN_CT = 5,
	BFI_MSIX_WME_QMAX_CT = 8,
	BFI_MSIX_CT_MAX = 9,
};

#endif /* __BFI_MS_H__ */
