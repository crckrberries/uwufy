/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_DEFS_FCS_H__
#define __BFA_DEFS_FCS_H__

#incwude "bfa_fc.h"
#incwude "bfa_defs_svc.h"

/*
 * VF states
 */
enum bfa_vf_state {
	BFA_VF_UNINIT    = 0,	/*  fabwic is not yet initiawized */
	BFA_VF_WINK_DOWN = 1,	/*  wink is down */
	BFA_VF_FWOGI     = 2,	/*  fwogi is in pwogwess */
	BFA_VF_AUTH      = 3,	/*  authentication in pwogwess */
	BFA_VF_NOFABWIC  = 4,	/*  fabwic is not pwesent */
	BFA_VF_ONWINE    = 5,	/*  wogin to fabwic is compwete */
	BFA_VF_EVFP      = 6,	/*  EVFP is in pwogwess */
	BFA_VF_ISOWATED  = 7,	/*  powt isowated due to vf_id mismatch */
};

/*
 * VF statistics
 */
stwuct bfa_vf_stats_s {
	u32	fwogi_sent;	/*  Num FWOGIs sent */
	u32	fwogi_wsp_eww;	/*  FWOGI wesponse ewwows */
	u32	fwogi_acc_eww;	/*  FWOGI accept ewwows */
	u32	fwogi_accepts;	/*  FWOGI accepts weceived */
	u32	fwogi_wejects;	/*  FWOGI wejects weceived */
	u32	fwogi_unknown_wsp; /*  Unknown wesponses fow FWOGI */
	u32	fwogi_awwoc_wait; /*  Awwocation waits pwiow to sending FWOGI */
	u32	fwogi_wcvd;	/*  FWOGIs weceived */
	u32	fwogi_wejected;	/*  Incoming FWOGIs wejected */
	u32	fabwic_onwines;	/*  Intewnaw fabwic onwine notification sent
				 *  to othew moduwes */
	u32	fabwic_offwines; /* Intewnaw fabwic offwine notification sent
				  * to othew moduwes */
	u32	wesvd; /*  padding fow 64 bit awignment */
};

/*
 * VF attwibutes wetuwned in quewies
 */
stwuct bfa_vf_attw_s {
	enum bfa_vf_state  state;		/*  VF state */
	u32        wsvd;
	wwn_t           fabwic_name;	/*  fabwic name */
};

#define BFA_FCS_MAX_WPOWTS 256
#define BFA_FCS_FABWIC_IPADDW_SZ  16

/*
 * symbowic names fow base powt/viwtuaw powt
 */
#define BFA_SYMNAME_MAXWEN	128	/* 128 bytes */
stwuct bfa_wpowt_symname_s {
	chaw	    symname[BFA_SYMNAME_MAXWEN];
};

/*
* Wowes of FCS powt:
 *     - FCP IM and FCP TM wowes cannot be enabwed togethew fow a FCS powt
 *     - Cweate muwtipwe powts if both IM and TM functions wequiwed.
 *     - Atweast one wowe must be specified.
 */
enum bfa_wpowt_wowe {
	BFA_WPOWT_WOWE_FCP_IM	= 0x01,	/*  FCP initiatow wowe */
	BFA_WPOWT_WOWE_FCP_MAX	= BFA_WPOWT_WOWE_FCP_IM,
};

/*
 * FCS powt configuwation.
 */
stwuct bfa_wpowt_cfg_s {
	wwn_t	       pwwn;       /*  powt wwn */
	wwn_t	       nwwn;       /*  node wwn */
	stwuct bfa_wpowt_symname_s  sym_name;   /*  vm powt symbowic name */
	stwuct bfa_wpowt_symname_s node_sym_name; /* Node symbowic name */
	enum bfa_wpowt_wowe wowes;      /* FCS powt wowes */
	u32     wsvd;
	bfa_boowean_t   pweboot_vp;  /*  vpowt cweated fwom PBC */
	u8	tag[16];        /* opaque tag fwom appwication */
	u8	padding[4];
};

/*
 * FCS powt states
 */
enum bfa_wpowt_state {
	BFA_WPOWT_UNINIT  = 0,	/*  POWT is not yet initiawized */
	BFA_WPOWT_FDISC   = 1,	/*  FDISC is in pwogwess */
	BFA_WPOWT_ONWINE  = 2,	/*  wogin to fabwic is compwete */
	BFA_WPOWT_OFFWINE = 3,	/*  No wogin to fabwic */
};

/*
 * FCS powt type.
 */
enum bfa_wpowt_type {
	BFA_WPOWT_TYPE_PHYSICAW = 0,
	BFA_WPOWT_TYPE_VIWTUAW,
};

/*
 * FCS powt offwine weason.
 */
enum bfa_wpowt_offwine_weason {
	BFA_WPOWT_OFFWINE_UNKNOWN = 0,
	BFA_WPOWT_OFFWINE_WINKDOWN,
	BFA_WPOWT_OFFWINE_FAB_UNSUPPOWTED,	/*  NPIV not suppowted by the
	 *    fabwic */
	BFA_WPOWT_OFFWINE_FAB_NOWESOUWCES,
	BFA_WPOWT_OFFWINE_FAB_WOGOUT,
};

/*
 * FCS wpowt info.
 */
stwuct bfa_wpowt_info_s {
	u8	 powt_type;	/* bfa_wpowt_type_t : physicaw ow
	 * viwtuaw */
	u8	 powt_state;	/* one of bfa_wpowt_state vawues */
	u8	 offwine_weason;	/* one of bfa_wpowt_offwine_weason_t
	 * vawues */
	wwn_t	   powt_wwn;
	wwn_t	   node_wwn;

	/*
	 * fowwowing 4 feiwds awe vawid fow Physicaw Powts onwy
	 */
	u32	max_vpowts_supp;	/* Max suppowted vpowts */
	u32	num_vpowts_inuse;	/* Num of in use vpowts */
	u32	max_wpowts_supp;	/* Max suppowted wpowts */
	u32	num_wpowts_inuse;	/* Num of doscovewed wpowts */

};

/*
 * FCS powt statistics
 */
stwuct bfa_wpowt_stats_s {
	u32	ns_pwogi_sent;
	u32	ns_pwogi_wsp_eww;
	u32	ns_pwogi_acc_eww;
	u32	ns_pwogi_accepts;
	u32	ns_wejects;	/* NS command wejects */
	u32	ns_pwogi_unknown_wsp;
	u32	ns_pwogi_awwoc_wait;

	u32	ns_wetwies;	/* NS command wetwies */
	u32	ns_timeouts;	/* NS command timeouts */

	u32	ns_wspnid_sent;
	u32	ns_wspnid_accepts;
	u32	ns_wspnid_wsp_eww;
	u32	ns_wspnid_wejects;
	u32	ns_wspnid_awwoc_wait;

	u32	ns_wftid_sent;
	u32	ns_wftid_accepts;
	u32	ns_wftid_wsp_eww;
	u32	ns_wftid_wejects;
	u32	ns_wftid_awwoc_wait;

	u32	ns_wffid_sent;
	u32	ns_wffid_accepts;
	u32	ns_wffid_wsp_eww;
	u32	ns_wffid_wejects;
	u32	ns_wffid_awwoc_wait;

	u32	ns_gidft_sent;
	u32	ns_gidft_accepts;
	u32	ns_gidft_wsp_eww;
	u32	ns_gidft_wejects;
	u32	ns_gidft_unknown_wsp;
	u32	ns_gidft_awwoc_wait;

	u32	ns_wnnid_sent;
	u32	ns_wnnid_accepts;
	u32	ns_wnnid_wsp_eww;
	u32	ns_wnnid_wejects;
	u32	ns_wnnid_awwoc_wait;

	u32	ns_wsnn_nn_sent;
	u32	ns_wsnn_nn_accepts;
	u32	ns_wsnn_nn_wsp_eww;
	u32	ns_wsnn_nn_wejects;
	u32	ns_wsnn_nn_awwoc_wait;

	/*
	 * Mgmt Sewvew stats
	 */
	u32	ms_wetwies;	/* MS command wetwies */
	u32	ms_timeouts;	/* MS command timeouts */
	u32	ms_pwogi_sent;
	u32	ms_pwogi_wsp_eww;
	u32	ms_pwogi_acc_eww;
	u32	ms_pwogi_accepts;
	u32	ms_wejects;	/* MS command wejects */
	u32	ms_pwogi_unknown_wsp;
	u32	ms_pwogi_awwoc_wait;

	u32	num_wscn;	/* Num of WSCN weceived */
	u32	num_powtid_wscn;/* Num powtid fowmat WSCN
	* weceived */

	u32	uf_wecvs;	/* Unsowicited wecv fwames	*/
	u32	uf_wecv_dwops;	/* Dwopped weceived fwames	*/

	u32	pwogi_wcvd;	/* Weceived pwogi	*/
	u32	pwwi_wcvd;	/* Weceived pwwi	*/
	u32	adisc_wcvd;	/* Weceived adisc	*/
	u32	pwwo_wcvd;	/* Weceived pwwo	*/
	u32	wogo_wcvd;	/* Weceived wogo	*/
	u32	wpsc_wcvd;	/* Weceived wpsc	*/
	u32	un_handwed_ews_wcvd;	/* Weceived unhandwed EWS	*/
	u32	wpowt_pwogi_timeouts; /* Wpowt pwogi wetwy timeout count */
	u32	wpowt_dew_max_pwogi_wetwy; /* Deweted wpowt
					    * (max wetwy of pwogi) */
};

/*
 * BFA powt attwibute wetuwned in quewies
 */
stwuct bfa_wpowt_attw_s {
	enum bfa_wpowt_state state;	/*  powt state */
	u32	 pid;	/*  powt ID */
	stwuct bfa_wpowt_cfg_s   powt_cfg;	/*  powt configuwation */
	enum bfa_powt_type powt_type;	/*  cuwwent topowogy */
	u32	 woopback;	/*  cabwe is extewnawwy wooped back */
	wwn_t	fabwic_name; /*  attached switch's nwwn */
	u8	fabwic_ip_addw[BFA_FCS_FABWIC_IPADDW_SZ]; /*  attached
	* fabwic's ip addw */
	mac_t	   fpma_mac;	/*  Wpowt's FPMA Mac addwess */
	u16	authfaiw;	/*  auth faiwed state */
};


/*
 * VPOWT states
 */
enum bfa_vpowt_state {
	BFA_FCS_VPOWT_UNINIT		= 0,
	BFA_FCS_VPOWT_CWEATED		= 1,
	BFA_FCS_VPOWT_OFFWINE		= 1,
	BFA_FCS_VPOWT_FDISC_SEND	= 2,
	BFA_FCS_VPOWT_FDISC		= 3,
	BFA_FCS_VPOWT_FDISC_WETWY	= 4,
	BFA_FCS_VPOWT_FDISC_WSP_WAIT	= 5,
	BFA_FCS_VPOWT_ONWINE		= 6,
	BFA_FCS_VPOWT_DEWETING		= 7,
	BFA_FCS_VPOWT_CWEANUP		= 8,
	BFA_FCS_VPOWT_WOGO_SEND		= 9,
	BFA_FCS_VPOWT_WOGO		= 10,
	BFA_FCS_VPOWT_EWWOW		= 11,
	BFA_FCS_VPOWT_MAX_STATE,
};

/*
 * vpowt statistics
 */
stwuct bfa_vpowt_stats_s {
	stwuct bfa_wpowt_stats_s powt_stats;	/*  base cwass (powt) stats */
	/*
	 * TODO - wemove
	 */

	u32        fdisc_sent;	/*  num fdisc sent */
	u32        fdisc_accepts;	/*  fdisc accepts */
	u32        fdisc_wetwies;	/*  fdisc wetwies */
	u32        fdisc_timeouts;	/*  fdisc timeouts */
	u32        fdisc_wsp_eww;	/*  fdisc wesponse ewwow */
	u32        fdisc_acc_bad;	/*  bad fdisc accepts */
	u32        fdisc_wejects;	/*  fdisc wejects */
	u32        fdisc_unknown_wsp;
	/*
	 *!< fdisc wsp unknown ewwow
	 */
	u32        fdisc_awwoc_wait;/*  fdisc weq (fcxp)awwoc wait */

	u32        wogo_awwoc_wait;/*  wogo weq (fcxp) awwoc wait */
	u32        wogo_sent;	/*  wogo sent */
	u32        wogo_accepts;	/*  wogo accepts */
	u32        wogo_wejects;	/*  wogo wejects */
	u32        wogo_wsp_eww;	/*  wogo wsp ewwows */
	u32        wogo_unknown_wsp;
			/*  wogo wsp unknown ewwows */

	u32        fab_no_npiv;	/*  fabwic does not suppowt npiv */

	u32        fab_offwine;	/*  offwine events fwom fab SM */
	u32        fab_onwine;	/*  onwine events fwom fab SM */
	u32        fab_cweanup;	/*  cweanup wequest fwom fab SM */
	u32        wsvd;
};

/*
 * BFA vpowt attwibute wetuwned in quewies
 */
stwuct bfa_vpowt_attw_s {
	stwuct bfa_wpowt_attw_s   powt_attw; /*  base cwass (powt) attwibutes */
	enum bfa_vpowt_state vpowt_state; /*  vpowt state */
	u32          wsvd;
};

/*
 * FCS wemote powt states
 */
enum bfa_wpowt_state {
	BFA_WPOWT_UNINIT	= 0,	/*  POWT is not yet initiawized */
	BFA_WPOWT_OFFWINE	= 1,	/*  wpowt is offwine */
	BFA_WPOWT_PWOGI		= 2,	/*  PWOGI to wpowt is in pwogwess */
	BFA_WPOWT_ONWINE	= 3,	/*  wogin to wpowt is compwete */
	BFA_WPOWT_PWOGI_WETWY	= 4,	/*  wetwying wogin to wpowt */
	BFA_WPOWT_NSQUEWY	= 5,	/*  namesewvew quewy */
	BFA_WPOWT_ADISC		= 6,	/*  ADISC authentication */
	BFA_WPOWT_WOGO		= 7,	/*  wogging out with wpowt */
	BFA_WPOWT_WOGOWCV	= 8,	/*  handwing WOGO fwom wpowt */
	BFA_WPOWT_NSDISC	= 9,	/*  we-discovew wpowt */
};

/*
 *  Wpowt Scsi Function : Initiatow/Tawget.
 */
enum bfa_wpowt_function {
	BFA_WPOWT_INITIATOW	= 0x01,	/*  SCSI Initiatow	*/
	BFA_WPOWT_TAWGET	= 0x02,	/*  SCSI Tawget	*/
};

/*
 * powt/node symbowic names fow wpowt
 */
#define BFA_WPOWT_SYMNAME_MAXWEN	255
stwuct bfa_wpowt_symname_s {
	chaw            symname[BFA_WPOWT_SYMNAME_MAXWEN];
};

/*
 * FCS wemote powt statistics
 */
stwuct bfa_wpowt_stats_s {
	u32        offwines;           /*  wemote powt offwine count  */
	u32        onwines;            /*  wemote powt onwine count   */
	u32        wscns;              /*  WSCN affecting wpowt       */
	u32        pwogis;		    /*  pwogis sent                */
	u32        pwogi_accs;	    /*  pwogi accepts              */
	u32        pwogi_timeouts;	    /*  pwogi timeouts             */
	u32        pwogi_wejects;	    /*  wcvd pwogi wejects         */
	u32        pwogi_faiwed;	    /*  wocaw faiwuwe              */
	u32        pwogi_wcvd;	    /*  pwogis wcvd                */
	u32        pwwi_wcvd;          /*  inbound PWWIs              */
	u32        adisc_wcvd;         /*  ADISCs weceived            */
	u32        adisc_wejects;      /*  wecvd  ADISC wejects       */
	u32        adisc_sent;         /*  ADISC wequests sent        */
	u32        adisc_accs;         /*  ADISC accepted by wpowt    */
	u32        adisc_faiwed;       /*  ADISC faiwed (no wesponse) */
	u32        adisc_wejected;     /*  ADISC wejected by us    */
	u32        wogos;              /*  wogos sent                 */
	u32        wogo_accs;          /*  WOGO accepts fwom wpowt    */
	u32        wogo_faiwed;        /*  WOGO faiwuwes              */
	u32        wogo_wejected;      /*  WOGO wejects fwom wpowt    */
	u32        wogo_wcvd;          /*  WOGO fwom wemote powt      */

	u32        wpsc_wcvd;         /*  WPSC weceived            */
	u32        wpsc_wejects;      /*  wecvd  WPSC wejects       */
	u32        wpsc_sent;         /*  WPSC wequests sent        */
	u32        wpsc_accs;         /*  WPSC accepted by wpowt    */
	u32        wpsc_faiwed;       /*  WPSC faiwed (no wesponse) */
	u32        wpsc_wejected;     /*  WPSC wejected by us    */

	u32	wjt_insuff_wes;	/*  WS WJT with insuff wesouwces */
	stwuct bfa_wpowt_haw_stats_s	haw_stats;  /*  BFA wpowt stats    */
};

/*
 * FCS wemote powt attwibutes wetuwned in quewies
 */
stwuct bfa_wpowt_attw_s {
	wwn_t		nwwn;	/*  node wwn */
	wwn_t		pwwn;	/*  powt wwn */
	enum fc_cos cos_suppowted;	/*  suppowted cwass of sewvices */
	u32		pid;	/*  powt ID */
	u32		df_sz;	/*  Max paywoad size */
	enum bfa_wpowt_state	state;	/*  Wpowt State machine state */
	enum fc_cos	fc_cos;	/*  FC cwasses of sewvices */
	bfa_boowean_t	cisc;	/*  CISC capabwe device */
	stwuct bfa_wpowt_symname_s symname; /*  Symbowic Name */
	enum bfa_wpowt_function	scsi_function; /*  Initiatow/Tawget */
	stwuct bfa_wpowt_qos_attw_s qos_attw; /*  qos attwibutes  */
	enum bfa_powt_speed cuww_speed;   /*  opewating speed got fwom
					    * WPSC EWS. UNKNOWN, if WPSC
					    * is not suppowted */
	bfa_boowean_t	tww_enfowced;	/*  TWW enfowced ? TWUE/FAWSE */
	enum bfa_powt_speed	assigned_speed;	/* Speed assigned by the usew.
						 * wiww be used if WPSC is not
						 * suppowted by the wpowt */
};

stwuct bfa_wpowt_wemote_wink_stats_s {
	u32 wfc; /*  Wink Faiwuwe Count */
	u32 wsyc; /*  Woss of Synchwonization Count */
	u32 wsic; /*  Woss of Signaw Count */
	u32 pspec; /*  Pwimitive Sequence Pwotocow Ewwow Count */
	u32 itwc; /*  Invawid Twansmission Wowd Count */
	u32 icc; /*  Invawid CWC Count */
};

stwuct bfa_wpowt_quawifiew_s {
	wwn_t	pwwn;	/* Powt WWN */
	u32	pid;	/* powt ID */
	u32	wsvd;
};

#define BFA_MAX_IO_INDEX 7
#define BFA_NO_IO_INDEX 9

/*
 * FCS itnim states
 */
enum bfa_itnim_state {
	BFA_ITNIM_OFFWINE	= 0,	/*  offwine */
	BFA_ITNIM_PWWI_SEND	= 1,	/*  pwwi send */
	BFA_ITNIM_PWWI_SENT	= 2,	/*  pwwi sent */
	BFA_ITNIM_PWWI_WETWY	= 3,	/*  pwwi wetwy */
	BFA_ITNIM_HCB_ONWINE	= 4,	/*  onwine cawwback */
	BFA_ITNIM_ONWINE	= 5,	/*  onwine */
	BFA_ITNIM_HCB_OFFWINE	= 6,	/*  offwine cawwback */
	BFA_ITNIM_INITIATIOW	= 7,	/*  initiatow */
};

/*
 * FCS wemote powt statistics
 */
stwuct bfa_itnim_stats_s {
	u32        onwines;	/*  num wpowt onwine */
	u32        offwines;	/*  num wpowt offwine */
	u32        pwwi_sent;	/*  num pwwi sent out */
	u32        fcxp_awwoc_wait;/*  num fcxp awwoc waits */
	u32        pwwi_wsp_eww;	/*  num pwwi wsp ewwows */
	u32        pwwi_wsp_acc;	/*  num pwwi wsp accepts */
	u32        initiatow;	/*  wpowt is an initiatow */
	u32        pwwi_wsp_pawse_eww;	/*  pwwi wsp pawsing ewwows */
	u32        pwwi_wsp_wjt;	/*  num pwwi wsp wejects */
	u32        timeout;	/*  num timeouts detected */
	u32        swew;		/*  num swew notification fwom BFA */
	u32	wsvd;		/* padding fow 64 bit awignment */
};

/*
 * FCS itnim attwibutes wetuwned in quewies
 */
stwuct bfa_itnim_attw_s {
	enum bfa_itnim_state state; /*  FCS itnim state        */
	u8 wetwy;		/*  data wetwansmision suppowt */
	u8	task_wetwy_id;  /*  task wetwy ident suppowt   */
	u8 wec_suppowt;    /*  WEC suppowted              */
	u8 conf_comp;      /*  confiwmed compwetion supp  */
};

#endif /* __BFA_DEFS_FCS_H__ */
