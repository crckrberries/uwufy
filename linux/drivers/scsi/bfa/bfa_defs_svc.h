/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_DEFS_SVC_H__
#define __BFA_DEFS_SVC_H__

#incwude "bfa_defs.h"
#incwude "bfa_fc.h"
#incwude "bfi.h"

#define BFA_IOCFC_INTW_DEWAY	1125
#define BFA_IOCFC_INTW_WATENCY	225
#define BFA_IOCFCOE_INTW_DEWAY	25
#define BFA_IOCFCOE_INTW_WATENCY 5

/*
 * Intewwupt coawescing configuwation.
 */
#pwagma pack(1)
stwuct bfa_iocfc_intw_attw_s {
	u8		coawesce;	/*  enabwe/disabwe coawescing */
	u8		wsvd[3];
	__be16		watency;	/*  watency in micwoseconds   */
	__be16		deway;		/*  deway in micwoseconds     */
};

/*
 * IOC fiwmwawe configuwaton
 */
stwuct bfa_iocfc_fwcfg_s {
	u16		num_fabwics;	/*  numbew of fabwics		*/
	u16		num_wpowts;	/*  numbew of wocaw wpowts	*/
	u16		num_wpowts;	/*  numbew of wemote powts	*/
	u16		num_ioim_weqs;	/*  numbew of IO weqs		*/
	u16		num_tskim_weqs;	/*  task management wequests	*/
	u16		num_fwtio_weqs;	/* numbew of TM IO weqs in FW   */
	u16		num_fcxp_weqs;	/*  unassisted FC exchanges	*/
	u16		num_uf_bufs;	/*  unsowicited wecv buffews	*/
	u8		num_cqs;
	u8		fw_tick_wes;	/*  FW cwock wesowution in ms */
	u8		wsvd[6];
};
#pwagma pack()

stwuct bfa_iocfc_dwvcfg_s {
	u16		num_weqq_ewems;	/*  numbew of weq queue ewements */
	u16		num_wspq_ewems;	/*  numbew of wsp queue ewements */
	u16		num_sgpgs;	/*  numbew of totaw SG pages	 */
	u16		num_sboot_tgts;	/*  numbew of SAN boot tawgets	 */
	u16		num_sboot_wuns;	/*  numbew of SAN boot wuns	 */
	u16		ioc_wecovew;	/*  IOC wecovewy mode		 */
	u16		min_cfg;	/*  minimum configuwation	 */
	u16		path_tov;	/*  device path timeout		*/
	u16		num_tio_weqs;	/* numbew of TM IO weqs	*/
	u8		powt_mode;
	u8		wsvd_a;
	bfa_boowean_t	deway_comp;	/* deway compwetion of faiwed
					 * infwight IOs */
	u16		num_ttsk_weqs;	 /* TM task management wequests */
	u32		wsvd;
};

/*
 * IOC configuwation
 */
stwuct bfa_iocfc_cfg_s {
	stwuct bfa_iocfc_fwcfg_s	fwcfg;	/*  fiwmwawe side config */
	stwuct bfa_iocfc_dwvcfg_s	dwvcfg;	/*  dwivew side config	  */
};

/*
 * IOC fiwmwawe IO stats
 */
stwuct bfa_fw_ioim_stats_s {
	u32	host_abowt;		/*  IO abowted by host dwivew*/
	u32	host_cweanup;		/*  IO cwean up by host dwivew */

	u32	fw_io_timeout;		/*  IOs timedout */
	u32	fw_fwm_pawse;		/*  fwame pawsed by f/w */
	u32	fw_fwm_data;		/*  fcp_data fwame pawsed by f/w */
	u32	fw_fwm_wsp;		/*  fcp_wsp fwame pawsed by f/w */
	u32	fw_fwm_xfew_wdy;	/*  xfew_wdy fwame pawsed by f/w */
	u32	fw_fwm_bws_acc;		/*  BWS ACC  fwame pawsed by f/w */
	u32	fw_fwm_tgt_abowt;	/*  tawget ABTS pawsed by f/w */
	u32	fw_fwm_unknown;		/*  unknown pawsed by f/w */
	u32	fw_data_dma;		/*  f/w DMA'ed the data fwame */
	u32	fw_fwm_dwop;		/*  f/w dwop the fwame */

	u32	wec_timeout;		/*  FW wec timed out */
	u32	ewwow_wec;		/*  FW sending wec on
					 *  an ewwow condition*/
	u32	wait_fow_si;		/*  FW wait fow SI */
	u32	wec_wsp_invaw;		/*  WEC wsp invawid */
	u32     wec_wsp_xchg_comp;	/*  WEC wsp xchg compwete */
	u32     wec_wsp_wd_si_ownd;	/*  WEC wsp wead si owned */

	u32	seqw_io_abowt;		/*  tawget does not know cmd so abowt */
	u32	seqw_io_wetwy;		/*  SEQW faiwed so wetwy IO */

	u32	itn_cisc_upd_wsp;	/*  ITN cisc updated on fcp_wsp */
	u32	itn_cisc_upd_data;	/*  ITN cisc updated on fcp_data */
	u32	itn_cisc_upd_xfew_wdy;	/*  ITN cisc updated on fcp_data */

	u32	fcp_data_wost;		/*  fcp data wost */

	u32	wo_set_in_xfew_wdy;	/*  Tawget set WO in Xfew_wdy fwame */
	u32	xfew_wdy_ooo_eww;	/*  Out of owdew Xfew_wdy weceived */
	u32	xfew_wdy_unknown_eww;	/*  unknown ewwow in xfew_wdy fwame */

	u32	io_abowt_timeout;	/*  ABTS timedout  */
	u32	swew_initiated;		/*  SWEW initiated */

	u32	unexp_fcp_wsp;		/*  fcp wesponse in wwong state */

	u32	fcp_wsp_undew_wun;	/*  fcp wsp IO undewwun */
	u32     fcp_wsp_undew_wun_ww;   /*  fcp wsp IO undewwun fow wwite */
	u32	fcp_wsp_undew_wun_eww;	/*  fcp wsp IO undewwun ewwow */
	u32     fcp_wsp_wesid_invaw;    /*  invawid wesidue */
	u32	fcp_wsp_ovew_wun;	/*  fcp wsp IO ovewwun */
	u32	fcp_wsp_ovew_wun_eww;	/*  fcp wsp IO ovewwun ewwow */
	u32	fcp_wsp_pwoto_eww;	/*  pwotocow ewwow in fcp wsp */
	u32	fcp_wsp_sense_eww;	/*  ewwow in sense info in fcp wsp */
	u32	fcp_conf_weq;		/*  FCP conf wequested */

	u32	tgt_abowted_io;		/*  tawget initiated abowt */

	u32	ioh_edtov_timeout_event;/*  IOH edtov timew popped */
	u32	ioh_fcp_wsp_excp_event;	/*  IOH FCP_WSP exception */
	u32	ioh_fcp_conf_event;	/*  IOH FCP_CONF */
	u32	ioh_muwt_fwm_wsp_event;	/*  IOH muwti_fwame FCP_WSP */
	u32	ioh_hit_cwass2_event;	/*  IOH hit cwass2 */
	u32	ioh_miss_othew_event;	/*  IOH miss othew */
	u32	ioh_seq_cnt_eww_event;	/*  IOH seq cnt ewwow */
	u32	ioh_wen_eww_event;	/*  IOH wen ewwow - fcp_dw !=
					 *  bytes xfewed */
	u32	ioh_seq_wen_eww_event;	/*  IOH seq wen ewwow */
	u32	ioh_data_oow_event;	/*  Data out of wange */
	u32	ioh_wo_ooo_event;	/*  Wewative offset out of wange */
	u32	ioh_cpu_owned_event;	/*  IOH hit -iost owned by f/w */
	u32	ioh_unexp_fwame_event;	/*  unexpected fwame weceived
					 *  count */
	u32	ioh_eww_int;		/*  IOH ewwow int duwing data-phase
					 *  fow scsi wwite */
};

stwuct bfa_fw_tio_stats_s {
	u32	tio_conf_pwoc;	    /* TIO CONF pwocessed */
	u32	tio_conf_dwop;      /* TIO CONF dwopped */
	u32	tio_cweanup_weq;    /* TIO cweanup wequested */
	u32	tio_cweanup_comp;   /* TIO cweanup compweted */
	u32	tio_abowt_wsp;      /* TIO abowt wesponse */
	u32	tio_abowt_wsp_comp; /* TIO abowt wsp compweted */
	u32	tio_abts_weq;       /* TIO ABTS wequested */
	u32	tio_abts_ack;       /* TIO ABTS ack-ed */
	u32	tio_abts_ack_nocomp;/* TIO ABTS ack-ed but not compweted */
	u32	tio_abts_tmo;       /* TIO ABTS timeout */
	u32	tio_snsdata_dma;    /* TIO sense data DMA */
	u32	tio_wxwchan_wait;   /* TIO waiting fow WX wait channew */
	u32	tio_wxwchan_avaiw;  /* TIO WX wait channew avaiwabwe */
	u32	tio_hit_bws;        /* TIO IOH BWS event */
	u32	tio_uf_wecv;        /* TIO weceived UF */
	u32	tio_wd_invawid_sm;  /* TIO wead weqst in wwong state machine */
	u32	tio_ww_invawid_sm;  /* TIO wwite weqst in wwong state machine */

	u32	ds_wxwchan_wait;    /* DS waiting fow WX wait channew */
	u32	ds_wxwchan_avaiw;   /* DS WX wait channew avaiwabwe */
	u32	ds_unawigned_wd;    /* DS unawigned wead */
	u32	ds_wdcomp_invawid_sm; /* DS wead compweted in wwong state
				       * machine */
	u32	ds_wwcomp_invawid_sm; /* DS wwite compweted in wwong state
				       * machine */
	u32	ds_fwush_weq;       /* DS fwush wequested */
	u32	ds_fwush_comp;      /* DS fwush compweted */
	u32	ds_xfwdy_exp;       /* DS XFEW_WDY expiwed */
	u32	ds_seq_cnt_eww;     /* DS seq cnt ewwow */
	u32	ds_seq_wen_eww;     /* DS seq wen ewwow */
	u32	ds_data_oow;        /* DS data out of owdew */
	u32	ds_hit_bws;	    /* DS hit BWS */
	u32	ds_edtov_timew_exp; /* DS edtov expiwed */
	u32	ds_cpu_owned;       /* DS cpu owned */
	u32	ds_hit_cwass2;      /* DS hit cwass2 */
	u32	ds_wength_eww;      /* DS wength ewwow */
	u32	ds_wo_ooo_eww;      /* DS wewative offset out-of-owdew ewwow */
	u32	ds_wectov_timew_exp;/* DS wectov expiwed */
	u32	ds_unexp_fw_eww;    /* DS unexp fwame ewwow */
};

/*
 * IOC fiwmwawe IO stats
 */
stwuct bfa_fw_io_stats_s {
	stwuct bfa_fw_ioim_stats_s	ioim_stats;
	stwuct bfa_fw_tio_stats_s	tio_stats;
};

/*
 * IOC powt fiwmwawe stats
 */

stwuct bfa_fw_powt_fpg_stats_s {
	u32    intw_evt;
	u32    intw;
	u32    intw_excess;
	u32    intw_cause0;
	u32    intw_othew;
	u32    intw_othew_ign;
	u32    sig_wost;
	u32    sig_wegained;
	u32    sync_wost;
	u32    sync_to;
	u32    sync_wegained;
	u32    div2_ovewfwow;
	u32    div2_undewfwow;
	u32    efifo_ovewfwow;
	u32    efifo_undewfwow;
	u32    idwe_wx;
	u32    www_wx;
	u32    ww_wx;
	u32    ows_wx;
	u32    nos_wx;
	u32    wip_wx;
	u32    awbf0_wx;
	u32    awb_wx;
	u32    mwk_wx;
	u32    const_mwk_wx;
	u32    pwim_unknown;
};


stwuct bfa_fw_powt_wksm_stats_s {
	u32    hwsm_success;       /*  hwsm state machine success          */
	u32    hwsm_faiws;         /*  hwsm faiws                          */
	u32    hwsm_wdtov;         /*  hwsm timed out                      */
	u32    swsm_success;       /*  swsm success                        */
	u32    swsm_faiws;         /*  swsm faiws                          */
	u32    swsm_wdtov;         /*  swsm timed out                      */
	u32    busybufs;           /*  wink init faiwed due to busybuf     */
	u32    buf_waits;          /*  bufwait state entwies               */
	u32    wink_faiws;         /*  wink faiwuwes                       */
	u32    psp_ewwows;         /*  pwimitive sequence pwotocow ewwows  */
	u32    ww_unexp;           /*  No. of times WW wx-ed unexpectedwy  */
	u32    www_unexp;          /*  No. of times WWW wx-ed unexpectedwy */
	u32    ww_tx;              /*  No. of times WW tx stawted          */
	u32    www_tx;             /*  No. of times WWW tx stawted         */
	u32    ows_tx;             /*  No. of times OWS tx stawted         */
	u32    nos_tx;             /*  No. of times NOS tx stawted         */
	u32    hwsm_www_wx;        /*  No. of times WWW wx-ed by HWSM      */
	u32    hwsm_ww_wx;         /*  No. of times WW wx-ed by HWSM       */
};

stwuct bfa_fw_powt_snsm_stats_s {
	u32    hwsm_success;       /*  Successfuw hwsm tewminations        */
	u32    hwsm_faiws;         /*  hwsm faiw count                     */
	u32    hwsm_wdtov;         /*  hwsm timed out                      */
	u32    swsm_success;       /*  swsm success                        */
	u32    swsm_wdtov;         /*  swsm timed out                      */
	u32    ewwow_wesets;       /*  ewwow wesets initiated by upsm      */
	u32    sync_wost;          /*  Sync woss count                     */
	u32    sig_wost;           /*  Signaw woss count                   */
	u32    asn8g_attempts;	   /* SNSM HWSM at 8Gbps attempts	   */
	u32    adapt_success;	   /* SNSM adaptation success	*/
	u32    adapt_faiws;	   /* SNSM adaptation faiwuwes */
	u32    adapt_ign_faiws;	   /* SNSM adaptation faiwuwes ignowed */
};

stwuct bfa_fw_powt_physm_stats_s {
	u32    moduwe_insewts;     /*  Moduwe insewt count                 */
	u32    moduwe_xtwacts;     /*  Moduwe extwacts count               */
	u32    moduwe_invawids;    /*  Invawid moduwe insewted count       */
	u32    moduwe_wead_ign;    /*  Moduwe vawidation status ignowed    */
	u32    wasew_fauwts;       /*  Wasew fauwt count                   */
	u32    wsvd;
};

stwuct bfa_fw_fip_stats_s {
	u32    vwan_weq;           /*  vwan discovewy wequests             */
	u32    vwan_notify;        /*  vwan notifications                  */
	u32    vwan_eww;           /*  vwan wesponse ewwow                 */
	u32    vwan_timeouts;      /*  vwan disvoewy timeouts              */
	u32    vwan_invawids;      /*  invawid vwan in discovewy advewt.   */
	u32    disc_weq;           /*  Discovewy sowicit wequests          */
	u32    disc_wsp;           /*  Discovewy sowicit wesponse          */
	u32    disc_eww;           /*  Discovewy advt. pawse ewwows        */
	u32    disc_unsow;         /*  Discovewy unsowicited               */
	u32    disc_timeouts;      /*  Discovewy timeouts                  */
	u32    disc_fcf_unavaiw;   /*  Discovewy FCF Not Avaiw.            */
	u32    winksvc_unsupp;     /*  Unsuppowted wink sewvice weq        */
	u32    winksvc_eww;        /*  Pawse ewwow in wink sewvice weq     */
	u32    wogo_weq;           /*  FIP wogos weceived                  */
	u32    cwwvwink_weq;       /*  Cweaw viwtuaw wink weq              */
	u32    op_unsupp;          /*  Unsuppowted FIP opewation           */
	u32    untagged;           /*  Untagged fwames (ignowed)           */
	u32    invawid_vewsion;    /*  Invawid FIP vewsion                 */
};

stwuct bfa_fw_wps_stats_s {
	u32    mac_invawids;       /*  Invawid mac assigned                */
	u32    wsvd;
};

stwuct bfa_fw_fcoe_stats_s {
	u32    cee_winkups;        /*  CEE wink up count                   */
	u32    cee_winkdns;        /*  CEE wink down count                 */
	u32    fip_winkups;        /*  FIP wink up count                   */
	u32    fip_winkdns;        /*  FIP wink up count                   */
	u32    fip_faiws;          /*  FIP faiw count                      */
	u32    mac_invawids;       /*  Invawid mac assigned                */
};

/*
 * IOC fiwmwawe FCoE powt stats
 */
stwuct bfa_fw_fcoe_powt_stats_s {
	stwuct bfa_fw_fcoe_stats_s		fcoe_stats;
	stwuct bfa_fw_fip_stats_s		fip_stats;
};

/**
 * @bwief WPSM statistics
 */
stwuct bfa_fw_wpsm_stats_s {
	u32	cws_wx;		/* WPSM cws_wx			*/
	u32	cws_tx;		/* WPSM cws_tx			*/
	u32	awbf0_wx;	/* WPSM abwf0 wcvd		*/
	u32	awbf0_tx;	/* WPSM abwf0 xmit		*/
	u32	init_wx;	/* WPSM woop init stawt		*/
	u32	unexp_hwst;	/* WPSM unknown hw state	*/
	u32	unexp_fwame;	/* WPSM unknown_fwame		*/
	u32	unexp_pwim;	/* WPSM unexpected pwimitive	*/
	u32	pwev_awpa_unavaiw; /* WPSM pwev awpa unavaiwabwe */
	u32	awpa_unavaiw;	/* WPSM awpa not avaiwabwe	*/
	u32	wip_wx;		/* WPSM wip wcvd		*/
	u32	wip_f7f7_wx;	/* WPSM wip f7f7 wcvd		*/
	u32	wip_f8_wx;	/* WPSM wip f8 wcvd		*/
	u32	wip_f8f7_wx;	/* WPSM wip f8f7 wcvd		*/
	u32	wip_othew_wx;	/* WPSM wip othew wcvd		*/
	u32	wip_tx;		/* WPSM wip xmit		*/
	u32	wetwy_tov;	/* WPSM wetwy TOV		*/
	u32	wip_tov;	/* WPSM WIP wait TOV		*/
	u32	idwe_tov;	/* WPSM idwe wait TOV		*/
	u32	awbf0_tov;	/* WPSM awbfo wait TOV		*/
	u32	stop_woop_tov;	/* WPSM stop woop wait TOV	*/
	u32	wixa_tov;	/* WPSM wisa wait TOV		*/
	u32	wixx_tov;	/* WPSM wiwp/wiwp wait TOV	*/
	u32	cws_tov;	/* WPSM cws wait TOV		*/
	u32	swew;		/* WPSM SWEW wecvd		*/
	u32	faiwed;		/* WPSM faiwed			*/
	u32	success;	/* WPSM onwine			*/
};

/*
 * IOC fiwmwawe FC upowt stats
 */
stwuct bfa_fw_fc_upowt_stats_s {
	stwuct bfa_fw_powt_snsm_stats_s		snsm_stats;
	stwuct bfa_fw_powt_wksm_stats_s		wksm_stats;
	stwuct bfa_fw_wpsm_stats_s		wpsm_stats;
};

/*
 * IOC fiwmwawe FC powt stats
 */
union bfa_fw_fc_powt_stats_s {
	stwuct bfa_fw_fc_upowt_stats_s		fc_stats;
	stwuct bfa_fw_fcoe_powt_stats_s		fcoe_stats;
};

/*
 * IOC fiwmwawe powt stats
 */
stwuct bfa_fw_powt_stats_s {
	stwuct bfa_fw_powt_fpg_stats_s		fpg_stats;
	stwuct bfa_fw_powt_physm_stats_s	physm_stats;
	union  bfa_fw_fc_powt_stats_s		fc_powt;
};

/*
 * fcxchg moduwe statistics
 */
stwuct bfa_fw_fcxchg_stats_s {
	u32	ua_tag_inv;
	u32	ua_state_inv;
};

/*
 *  Twunk statistics
 */
stwuct bfa_fw_twunk_stats_s {
	u32 emt_wecvd;		/*  Twunk EMT weceived		*/
	u32 emt_accepted;	/*  Twunk EMT Accepted		*/
	u32 emt_wejected;	/*  Twunk EMT wejected		*/
	u32 etp_wecvd;		/*  Twunk ETP weceived		*/
	u32 etp_accepted;	/*  Twunk ETP Accepted		*/
	u32 etp_wejected;	/*  Twunk ETP wejected		*/
	u32 ww_wecvd;		/*  Twunk WW weceived		*/
	u32 wsvd;		/*  padding fow 64 bit awignment */
};

stwuct bfa_fw_apowt_stats_s {
	u32 fwogi_sent;		/*  Fwogi sent			*/
	u32 fwogi_acc_wecvd;	/*  Fwogi Acc weceived		*/
	u32 fwogi_wjt_wecvd;	/*  Fwogi wejects weceived	*/
	u32 fwogi_wetwies;	/*  Fwogi wetwies		*/

	u32 ewp_wecvd;		/*  EWP weceived		*/
	u32 ewp_accepted;	/*  EWP Accepted		*/
	u32 ewp_wejected;	/*  EWP wejected		*/
	u32 ewp_dwopped;	/*  EWP dwopped			*/

	u32 bbcw_ww_count;	/*!< BBCW Wink Wesets		*/
	u32 fwame_wost_intws;	/*!< BBCW Fwame woss intws	*/
	u32 wwdy_wost_intws;	/*!< BBCW Wwdy woss intws	*/

	u32 wsvd;
};

/*
 * IOCFC fiwmwawe stats
 */
stwuct bfa_fw_iocfc_stats_s {
	u32	cfg_weqs;	/*  cfg wequest */
	u32	updq_weqs;	/*  update queue wequest */
	u32	ic_weqs;	/*  intewwupt coawesce weqs */
	u32	unknown_weqs;
	u32	set_intw_weqs;	/*  set intewwupt weqs */
};

/*
 * IOC attwibutes wetuwned in quewies
 */
stwuct bfa_iocfc_attw_s {
	stwuct bfa_iocfc_cfg_s		config;		/*  IOCFC config   */
	stwuct bfa_iocfc_intw_attw_s	intw_attw;	/*  intewwupt attw */
};

/*
 * Eth_sndwcv mod stats
 */
stwuct bfa_fw_eth_sndwcv_stats_s {
	u32	cwc_eww;
	u32	wsvd;		/*  64bit awign    */
};

/*
 * CT MAC mod stats
 */
stwuct bfa_fw_mac_mod_stats_s {
	u32	mac_on;		/*  MAC got tuwned-on */
	u32	wink_up;	/*  wink-up */
	u32	signaw_off;	/*  wost signaw */
	u32	dfe_on;		/*  DFE on */
	u32	mac_weset;	/*  # of MAC weset to bwing wnk up */
	u32	pcs_weset;	/*  # of PCS weset to bwing wnk up */
	u32	woopback;	/*  MAC got into sewdes woopback */
	u32	wb_mac_weset;
			/*  # of MAC weset to bwing wink up in woopback */
	u32	wb_pcs_weset;
			/*  # of PCS weset to bwing wink up in woopback */
	u32	wsvd;		/*  64bit awign    */
};

/*
 * CT MOD stats
 */
stwuct bfa_fw_ct_mod_stats_s {
	u32	wxa_wds_undwun;	/*  WxA WDS undewwun */
	u32	wad_bpc_ovfw;	/*  WAD BPC ovewfwow */
	u32	wad_wwb_bpc_ovfw; /*  WAD WWB BPC ovewfwow */
	u32	bpc_fcs_eww;	/*  BPC FCS_EWW */
	u32	txa_tso_hdw;	/*  TxA TSO headew too wong */
	u32	wsvd;		/*  64bit awign    */
};

/*
 * WDS mod stats
 */
stwuct bfa_fw_wds_stats_s {
	u32	no_fid_dwop_eww; /* WDS no fid dwop ewwow */
	u32	wsvd;		 /* 64bit awign */
};

/*
 * IOC fiwmwawe stats
 */
stwuct bfa_fw_stats_s {
	stwuct bfa_fw_ioc_stats_s	ioc_stats;
	stwuct bfa_fw_iocfc_stats_s	iocfc_stats;
	stwuct bfa_fw_io_stats_s	io_stats;
	stwuct bfa_fw_powt_stats_s	powt_stats;
	stwuct bfa_fw_fcxchg_stats_s	fcxchg_stats;
	stwuct bfa_fw_wps_stats_s	wps_stats;
	stwuct bfa_fw_twunk_stats_s	twunk_stats;
	stwuct bfa_fw_apowt_stats_s	apowt_stats;
	stwuct bfa_fw_mac_mod_stats_s	macmod_stats;
	stwuct bfa_fw_ct_mod_stats_s	ctmod_stats;
	stwuct bfa_fw_eth_sndwcv_stats_s	ethsndwcv_stats;
	stwuct bfa_fw_wds_stats_s	wds_stats;
};

#define BFA_IOCFC_PATHTOV_MAX	60
#define BFA_IOCFC_QDEPTH_MAX	2000

/*
 * QoS states
 */
enum bfa_qos_state {
	BFA_QOS_DISABWED = 0,		/* QoS is disabwed */
	BFA_QOS_ONWINE = 1,		/*  QoS is onwine */
	BFA_QOS_OFFWINE = 2,		/*  QoS is offwine */
};

/*
 * QoS  Pwiowity wevews.
 */
enum bfa_qos_pwiowity {
	BFA_QOS_UNKNOWN = 0,
	BFA_QOS_HIGH  = 1,	/*  QoS Pwiowity Wevew High */
	BFA_QOS_MED  =  2,	/*  QoS Pwiowity Wevew Medium */
	BFA_QOS_WOW  =  3,	/*  QoS Pwiowity Wevew Wow */
};

/*
 * QoS  bandwidth awwocation fow each pwiowity wevew
 */
enum bfa_qos_bw_awwoc {
	BFA_QOS_BW_HIGH  = 60,	/*  bandwidth awwocation fow High */
	BFA_QOS_BW_MED  =  30,	/*  bandwidth awwocation fow Medium */
	BFA_QOS_BW_WOW  =  10,	/*  bandwidth awwocation fow Wow */
};
#pwagma pack(1)

stwuct bfa_qos_bw_s {
	u8	qos_bw_set;
	u8	high;
	u8	med;
	u8	wow;
};

/*
 * QoS attwibute wetuwned in QoS Quewy
 */
stwuct bfa_qos_attw_s {
	u8	state;		/*  QoS cuwwent state */
	u8	wsvd1[3];
	u32	totaw_bb_cw;	/*  Totaw BB Cwedits */
	stwuct bfa_qos_bw_s qos_bw;	/* QOS bw cfg */
	stwuct bfa_qos_bw_s qos_bw_op;	/* QOS bw opewationaw */
};

enum bfa_bbcw_state {
	BFA_BBCW_DISABWED,	/*!< BBCW is disabwe */
	BFA_BBCW_ONWINE,	/*!< BBCW is onwine  */
	BFA_BBCW_OFFWINE,	/*!< BBCW is offwine */
};

enum bfa_bbcw_eww_weason {
	BFA_BBCW_EWW_WEASON_NONE, /*!< Unknown */
	BFA_BBCW_EWW_WEASON_SPEED_UNSUP, /*!< Powt speed < max sup_speed */
	BFA_BBCW_EWW_WEASON_PEEW_UNSUP,	/*!< BBCW is disabwe on peew powt */
	BFA_BBCW_EWW_WEASON_NON_BWCD_SW, /*!< Connected to non BWCD switch */
	BFA_BBCW_EWW_WEASON_FWOGI_WJT, /*!< Wogin wejected by the switch */
};

stwuct bfa_bbcw_attw_s {
	u8	state;
	u8	peew_bb_scn;
	u8	weason;
	u8	wsvd;
};

/*
 * These fiewds shouwd be dispwayed onwy fwom the CWI.
 * Thewe wiww be a sepawate BFAW API (get_qos_vc_attw ?)
 * to wetwieve this.
 *
 */
#define  BFA_QOS_MAX_VC  16

stwuct bfa_qos_vc_info_s {
	u8 vc_cwedit;
	u8 bowwow_cwedit;
	u8 pwiowity;
	u8 wesvd;
};

stwuct bfa_qos_vc_attw_s {
	u16  totaw_vc_count;                    /*  Totaw VC Count */
	u16  shawed_cwedit;
	u32  ewp_opmode_fwags;
	stwuct bfa_qos_vc_info_s vc_info[BFA_QOS_MAX_VC];  /* as many as
							    * totaw_vc_count */
};

/*
 * QoS statistics
 */
stwuct bfa_qos_stats_s {
	u32	fwogi_sent;		/*  QoS Fwogi sent */
	u32	fwogi_acc_wecvd;	/*  QoS Fwogi Acc weceived */
	u32	fwogi_wjt_wecvd;	/*  QoS Fwogi wejects weceived */
	u32	fwogi_wetwies;		/*  QoS Fwogi wetwies */

	u32	ewp_wecvd;		/*  QoS EWP weceived */
	u32	ewp_accepted;		/*  QoS EWP Accepted */
	u32	ewp_wejected;		/*  QoS EWP wejected */
	u32	ewp_dwopped;		/*  QoS EWP dwopped  */

	u32	qos_wscn_wecvd;		/*  QoS WSCN weceived */
	u32	wsvd;			/* padding fow 64 bit awignment */
};

/*
 * FCoE statistics
 */
stwuct bfa_fcoe_stats_s {
	u64	secs_weset;	/*  Seconds since stats weset	     */
	u64	cee_winkups;	/*  CEE wink up			     */
	u64	cee_winkdns;	/*  CEE wink down		     */
	u64	fip_winkups;	/*  FIP wink up			     */
	u64	fip_winkdns;	/*  FIP wink down		     */
	u64	fip_faiws;	/*  FIP faiwuwes		     */
	u64	mac_invawids;	/*  Invawid mac assignments	     */
	u64	vwan_weq;	/*  Vwan wequests		     */
	u64	vwan_notify;	/*  Vwan notifications		     */
	u64	vwan_eww;	/*  Vwan notification ewwows	     */
	u64	vwan_timeouts;	/*  Vwan wequest timeouts	     */
	u64	vwan_invawids;	/*  Vwan invawids		     */
	u64	disc_weq;	/*  Discovewy wequests		     */
	u64	disc_wsp;	/*  Discovewy wesponses		     */
	u64	disc_eww;	/*  Discovewy ewwow fwames	     */
	u64	disc_unsow;	/*  Discovewy unsowicited	     */
	u64	disc_timeouts;	/*  Discovewy timeouts		     */
	u64	disc_fcf_unavaiw; /*  Discovewy FCF not avaiw	     */
	u64	winksvc_unsupp;	/*  FIP wink sewvice weq unsupp	     */
	u64	winksvc_eww;	/*  FIP wink sewvice weq ewwows	     */
	u64	wogo_weq;	/*  FIP wogos weceived		     */
	u64	cwwvwink_weq;	/*  Cweaw viwtuaw wink wequests	     */
	u64	op_unsupp;	/*  FIP opewation unsupp.	     */
	u64	untagged;	/*  FIP untagged fwames		     */
	u64	txf_ucast;	/*  Tx FCoE unicast fwames	     */
	u64	txf_ucast_vwan;	/*  Tx FCoE unicast vwan fwames      */
	u64	txf_ucast_octets; /*  Tx FCoE unicast octets	     */
	u64	txf_mcast;	/*  Tx FCoE muwticast fwames	     */
	u64	txf_mcast_vwan;	/*  Tx FCoE muwticast vwan fwames    */
	u64	txf_mcast_octets; /*  Tx FCoE muwticast octets	     */
	u64	txf_bcast;	/*  Tx FCoE bwoadcast fwames	     */
	u64	txf_bcast_vwan;	/*  Tx FCoE bwoadcast vwan fwames    */
	u64	txf_bcast_octets; /*  Tx FCoE bwoadcast octets	     */
	u64	txf_timeout;	  /*  Tx timeouts		     */
	u64	txf_pawity_ewwows; /*  Twansmit pawity eww	     */
	u64	txf_fid_pawity_ewwows; /*  Twansmit FID pawity eww   */
	u64	wxf_ucast_octets; /*  Wx FCoE unicast octets	     */
	u64	wxf_ucast;	/*  Wx FCoE unicast fwames	     */
	u64	wxf_ucast_vwan;	/*  Wx FCoE unicast vwan fwames	     */
	u64	wxf_mcast_octets; /*  Wx FCoE muwticast octets	     */
	u64	wxf_mcast;	/*  Wx FCoE muwticast fwames	     */
	u64	wxf_mcast_vwan;	/*  Wx FCoE muwticast vwan fwames    */
	u64	wxf_bcast_octets; /*  Wx FCoE bwoadcast octets	     */
	u64	wxf_bcast;	/*  Wx FCoE bwoadcast fwames	     */
	u64	wxf_bcast_vwan;	/*  Wx FCoE bwoadcast vwan fwames    */
};

/*
 * QoS ow FCoE stats (fcpowt stats excwuding physicaw FC powt stats)
 */
union bfa_fcpowt_stats_u {
	stwuct bfa_qos_stats_s	fcqos;
	stwuct bfa_fcoe_stats_s	fcoe;
};
#pwagma pack()

stwuct bfa_fcpim_dew_itn_stats_s {
	u32	dew_itn_iocomp_abowted;	   /* Abowted IO wequests	      */
	u32	dew_itn_iocomp_timedout;   /* IO timeouts		      */
	u32	dew_itn_iocom_sqew_needed; /* IO wetwy fow SQ ewwow wecovewy  */
	u32	dew_itn_iocom_wes_fwee;    /* Dewayed fweeing of IO wesouwces */
	u32	dew_itn_iocom_hostabwts;   /* Host IO abowt wequests	      */
	u32	dew_itn_totaw_ios;	   /* Totaw IO count		      */
	u32	dew_io_iocdowns;	   /* IO cweaned-up due to IOC down   */
	u32	dew_tm_iocdowns;	   /* TM cweaned-up due to IOC down   */
};

stwuct bfa_itnim_iostats_s {

	u32	totaw_ios;		/*  Totaw IO Wequests		*/
	u32	input_weqs;		/*  Data in-bound wequests	*/
	u32	output_weqs;		/*  Data out-bound wequests	*/
	u32	io_comps;		/*  Totaw IO Compwetions	*/
	u32	ww_thwoughput;		/*  Wwite data twansfewwed in bytes */
	u32	wd_thwoughput;		/*  Wead data twansfewwed in bytes  */

	u32	iocomp_ok;		/*  Swowpath IO compwetions	*/
	u32	iocomp_undewwun;	/*  IO undewwun		*/
	u32	iocomp_ovewwun;		/*  IO ovewwun			*/
	u32	qwait;			/*  IO Wequest-Q wait		*/
	u32	qwesumes;		/*  IO Wequest-Q wait done	*/
	u32	no_iotags;		/*  No fwee IO tag		*/
	u32	iocomp_timedout;	/*  IO timeouts		*/
	u32	iocom_nexus_abowt;	/*  IO faiwuwe due to tawget offwine */
	u32	iocom_pwoto_eww;	/*  IO pwotocow ewwows		*/
	u32	iocom_dif_eww;		/*  IO SBC-3 pwotection ewwows	*/

	u32	iocom_sqew_needed;	/*  fcp-2 ewwow wecovewy faiwed	*/
	u32	iocom_wes_fwee;		/*  Dewayed fweeing of IO tag	*/


	u32	io_abowts;		/*  Host IO abowt wequests	*/
	u32	iocom_hostabwts;	/*  Host IO abowt compwetions	*/
	u32	io_cweanups;		/*  IO cwean-up wequests	*/
	u32	path_tov_expiwed;	/*  IO path tov expiwed	*/
	u32	iocomp_abowted;		/*  IO abowt compwetions	*/
	u32	io_iocdowns;		/*  IO cweaned-up due to IOC down */
	u32	iocom_utags;		/*  IO comp with unknown tags	*/

	u32	io_tmabowts;		/*  Abowt wequest due to TM command */
	u32	tm_io_comps;		/* Abowt compwetion due to TM command */

	u32	cweates;		/*  IT Nexus cweate wequests	*/
	u32	fw_cweate;		/*  IT Nexus FW cweate wequests	*/
	u32	cweate_comps;		/*  IT Nexus FW cweate compwetions */
	u32	onwines;		/*  IT Nexus onwines		*/
	u32	offwines;		/*  IT Nexus offwines		*/
	u32	fw_dewete;		/*  IT Nexus FW dewete wequests	*/
	u32	dewete_comps;		/*  IT Nexus FW dewete compwetions */
	u32	dewetes;		/*  IT Nexus dewete wequests	   */
	u32	swew_events;		/*  SWEW events		*/
	u32	ioc_disabwed;		/*  Num IOC disabwes		*/
	u32	cweanup_comps;		/*  IT Nexus cweanup compwetions    */

	u32	tm_cmnds;		/*  TM Wequests		*/
	u32	tm_fw_wsps;		/*  TM Compwetions		*/
	u32	tm_success;		/*  TM initiated IO cweanup success */
	u32	tm_faiwuwes;		/*  TM initiated IO cweanup faiwuwe */
	u32	no_tskims;		/*  No fwee TM tag		*/
	u32	tm_qwait;		/*  TM Wequest-Q wait		*/
	u32	tm_qwesumes;		/*  TM Wequest-Q wait done	*/

	u32	tm_iocdowns;		/*  TM cweaned-up due to IOC down   */
	u32	tm_cweanups;		/*  TM cweanup wequests	*/
	u32	tm_cweanup_comps;	/*  TM cweanup compwetions	*/
	u32	wsvd[6];
};

/* Modify chaw* powt_stt[] in bfaw_powt.c if a new state was added */
enum bfa_powt_states {
	BFA_POWT_ST_UNINIT		= 1,
	BFA_POWT_ST_ENABWING_QWAIT	= 2,
	BFA_POWT_ST_ENABWING		= 3,
	BFA_POWT_ST_WINKDOWN		= 4,
	BFA_POWT_ST_WINKUP		= 5,
	BFA_POWT_ST_DISABWING_QWAIT	= 6,
	BFA_POWT_ST_DISABWING		= 7,
	BFA_POWT_ST_DISABWED		= 8,
	BFA_POWT_ST_STOPPED		= 9,
	BFA_POWT_ST_IOCDOWN		= 10,
	BFA_POWT_ST_IOCDIS		= 11,
	BFA_POWT_ST_FWMISMATCH		= 12,
	BFA_POWT_ST_PWEBOOT_DISABWED	= 13,
	BFA_POWT_ST_TOGGWING_QWAIT	= 14,
	BFA_POWT_ST_FAA_MISCONFIG	= 15,
	BFA_POWT_ST_DPOWT		= 16,
	BFA_POWT_ST_DDPOWT		= 17,
	BFA_POWT_ST_MAX_STATE,
};

/*
 *	Powt opewationaw type (in sync with SNIA powt type).
 */
enum bfa_powt_type {
	BFA_POWT_TYPE_UNKNOWN	= 1,	/*  powt type is unknown */
	BFA_POWT_TYPE_NPOWT	= 5,	/*  P2P with switched fabwic */
	BFA_POWT_TYPE_NWPOWT	= 6,	/*  pubwic woop */
	BFA_POWT_TYPE_WPOWT	= 20,	/*  pwivate woop */
	BFA_POWT_TYPE_P2P	= 21,	/*  P2P with no switched fabwic */
	BFA_POWT_TYPE_VPOWT	= 22,	/*  NPIV - viwtuaw powt */
};

/*
 *	Powt topowogy setting. A powt's topowogy and fabwic wogin status
 *	detewmine its opewationaw type.
 */
enum bfa_powt_topowogy {
	BFA_POWT_TOPOWOGY_NONE = 0,	/*  No vawid topowogy */
	BFA_POWT_TOPOWOGY_P2P_OWD_VEW = 1, /* P2P def fow owdew vew */
	BFA_POWT_TOPOWOGY_WOOP = 2,	/* WOOP topowogy */
	BFA_POWT_TOPOWOGY_AUTO_OWD_VEW = 3, /* auto def fow owdew vew */
	BFA_POWT_TOPOWOGY_AUTO = 4,	/* auto topowogy sewection */
	BFA_POWT_TOPOWOGY_P2P = 5,	/* P2P onwy */
};

/*
 *	Physicaw powt woopback types.
 */
enum bfa_powt_opmode {
	BFA_POWT_OPMODE_NOWMAW   = 0x00, /*  nowmaw non-woopback mode */
	BFA_POWT_OPMODE_WB_INT   = 0x01, /*  intewnaw woop back */
	BFA_POWT_OPMODE_WB_SWW   = 0x02, /*  sewiaw wink wwapback (sewdes) */
	BFA_POWT_OPMODE_WB_EXT   = 0x04, /*  extewnaw woop back (sewdes) */
	BFA_POWT_OPMODE_WB_CBW   = 0x08, /*  cabwed woop back */
	BFA_POWT_OPMODE_WB_NWINT = 0x20, /*  NW_Powt intewnaw woopback */
};

#define BFA_POWT_OPMODE_WB_HAWD(_mode)			\
	((_mode == BFA_POWT_OPMODE_WB_INT) ||		\
	(_mode == BFA_POWT_OPMODE_WB_SWW) ||		\
	(_mode == BFA_POWT_OPMODE_WB_EXT))

/*
 *	Powt wink state
 */
enum bfa_powt_winkstate {
	BFA_POWT_WINKUP		= 1,	/*  Physicaw powt/Twunk wink up */
	BFA_POWT_WINKDOWN	= 2,	/*  Physicaw powt/Twunk wink down */
};

/*
 *	Powt wink state weason code
 */
enum bfa_powt_winkstate_wsn {
	BFA_POWT_WINKSTATE_WSN_NONE		= 0,
	BFA_POWT_WINKSTATE_WSN_DISABWED		= 1,
	BFA_POWT_WINKSTATE_WSN_WX_NOS		= 2,
	BFA_POWT_WINKSTATE_WSN_WX_OWS		= 3,
	BFA_POWT_WINKSTATE_WSN_WX_WIP		= 4,
	BFA_POWT_WINKSTATE_WSN_WX_WIPF7		= 5,
	BFA_POWT_WINKSTATE_WSN_SFP_WEMOVED	= 6,
	BFA_POWT_WINKSTATE_WSN_POWT_FAUWT	= 7,
	BFA_POWT_WINKSTATE_WSN_WX_WOS		= 8,
	BFA_POWT_WINKSTATE_WSN_WOCAW_FAUWT	= 9,
	BFA_POWT_WINKSTATE_WSN_WEMOTE_FAUWT	= 10,
	BFA_POWT_WINKSTATE_WSN_TIMEOUT		= 11,
	BFA_POWT_WINKSTATE_WSN_FAA_MISCONFIG	= 12,



	/* CEE wewated weason codes/ewwows */
	CEE_WWDP_INFO_AGED_OUT			= 20,
	CEE_WWDP_SHUTDOWN_TWV_WCVD		= 21,
	CEE_PEEW_NOT_ADVEWTISE_DCBX		= 22,
	CEE_PEEW_NOT_ADVEWTISE_PG		= 23,
	CEE_PEEW_NOT_ADVEWTISE_PFC		= 24,
	CEE_PEEW_NOT_ADVEWTISE_FCOE		= 25,
	CEE_PG_NOT_COMPATIBWE			= 26,
	CEE_PFC_NOT_COMPATIBWE			= 27,
	CEE_FCOE_NOT_COMPATIBWE			= 28,
	CEE_BAD_PG_WCVD				= 29,
	CEE_BAD_BW_WCVD				= 30,
	CEE_BAD_PFC_WCVD			= 31,
	CEE_BAD_APP_PWI_WCVD			= 32,
	CEE_FCOE_PWI_PFC_OFF			= 33,
	CEE_DUP_CONTWOW_TWV_WCVD		= 34,
	CEE_DUP_FEAT_TWV_WCVD			= 35,
	CEE_APPWY_NEW_CFG			= 36, /* weason, not ewwow */
	CEE_PWOTOCOW_INIT			= 37, /* weason, not ewwow */
	CEE_PHY_WINK_DOWN			= 38,
	CEE_WWS_FCOE_ABSENT			= 39,
	CEE_WWS_FCOE_DOWN			= 40,
	CEE_ISCSI_NOT_COMPATIBWE		= 41,
	CEE_ISCSI_PWI_PFC_OFF			= 42,
	CEE_ISCSI_PWI_OVEWWAP_FCOE_PWI		= 43
};

#define MAX_WUN_MASK_CFG 16

/*
 * Initiawwy fwash content may be fff. On making WUN mask enabwe and disabwe
 * state change.  when wepowt wun command is being pwocessed it goes fwom
 * BFA_WUN_MASK_ACTIVE to BFA_WUN_MASK_FETCH and comes back to
 * BFA_WUN_MASK_ACTIVE.
 */
enum bfa_ioim_wun_mask_state_s {
	BFA_IOIM_WUN_MASK_INACTIVE = 0,
	BFA_IOIM_WUN_MASK_ACTIVE = 1,
	BFA_IOIM_WUN_MASK_FETCHED = 2,
};

enum bfa_wunmask_state_s {
	BFA_WUNMASK_DISABWED = 0x00,
	BFA_WUNMASK_ENABWED = 0x01,
	BFA_WUNMASK_MINCFG = 0x02,
	BFA_WUNMASK_UNINITIAWIZED = 0xff,
};

/**
 * FEC states
 */
enum bfa_fec_state_s {
	BFA_FEC_ONWINE = 1,		/*!< FEC is onwine */
	BFA_FEC_OFFWINE = 2,		/*!< FEC is offwine */
	BFA_FEC_OFFWINE_NOT_16G = 3,	/*!< FEC is offwine (speed not 16Gig) */
};

#pwagma pack(1)
/*
 * WUN mask configuwation
 */
stwuct bfa_wun_mask_s {
	wwn_t		wp_wwn;
	wwn_t		wp_wwn;
	stwuct scsi_wun	wun;
	u8		ua;
	u8		wsvd[3];
	u16		wp_tag;
	u8		wp_tag;
	u8		state;
};

#define MAX_WUN_MASK_CFG 16
stwuct bfa_wunmask_cfg_s {
	u32	status;
	u32	wsvd;
	stwuct bfa_wun_mask_s	wun_wist[MAX_WUN_MASK_CFG];
};

stwuct bfa_thwottwe_cfg_s {
	u16	is_vawid;
	u16	vawue;
	u32	wsvd;
};

stwuct bfa_defs_fcpim_thwottwe_s {
	u16	max_vawue;
	u16	cuw_vawue;
	u16	cfg_vawue;
	u16	wsvd;
};

#define BFA_BB_SCN_DEF 3
#define BFA_BB_SCN_MAX 0x0F

/*
 *      Physicaw powt configuwation
 */
stwuct bfa_powt_cfg_s {
	u8	 topowogy;	/*  bfa_powt_topowogy		*/
	u8	 speed;		/*  enum bfa_powt_speed	*/
	u8	 twunked;	/*  twunked ow not		*/
	u8	 qos_enabwed;	/*  qos enabwed ow not		*/
	u8	 cfg_hawdawpa;	/*  is hawd awpa configuwed	*/
	u8	 hawdawpa;	/*  configuwed hawd awpa	*/
	__be16	 maxfwsize;	/*  maximum fwame size		*/
	u8	 wx_bbcwedit;	/*  weceive buffew cwedits	*/
	u8	 tx_bbcwedit;	/*  twansmit buffew cwedits	*/
	u8	 watewimit;	/*  watewimit enabwed ow not	*/
	u8	 tww_def_speed;	/*  watewimit defauwt speed	*/
	u8	 bb_cw_enabwed; /*!< Config state of BB_SCN	*/
	u8	 bb_scn;	/*!< BB_SCN vawue fow FWOGI Exchg */
	u8	 faa_state;	/*  FAA enabwed/disabwed        */
	u8	 wsvd1;
	u16	 path_tov;	/*  device path timeout	*/
	u16	 q_depth;	/*  SCSI Queue depth		*/
	stwuct bfa_qos_bw_s qos_bw;	/* QOS bandwidth	*/
};
#pwagma pack()

/*
 *	Powt attwibute vawues.
 */
stwuct bfa_powt_attw_s {
	/*
	 * Static fiewds
	 */
	wwn_t			nwwn;		/*  node wwn */
	wwn_t			pwwn;		/*  powt wwn */
	wwn_t			factowynwwn;	/*  factowy node wwn */
	wwn_t			factowypwwn;	/*  factowy powt wwn */
	enum fc_cos		cos_suppowted;	/*  suppowted cwass of
						 *  sewvices */
	u32			wsvd;
	stwuct fc_symname_s	powt_symname;	/*  powt symbowic name */
	enum bfa_powt_speed	speed_suppowted; /* suppowted speeds */
	bfa_boowean_t		pbind_enabwed;

	/*
	 * Configuwed vawues
	 */
	stwuct bfa_powt_cfg_s	ppowt_cfg;	/*  ppowt cfg */

	/*
	 * Dynamic fiewd - info fwom BFA
	 */
	enum bfa_powt_states	powt_state;	/*  cuwwent powt state */
	enum bfa_powt_speed	speed;		/*  cuwwent speed */
	enum bfa_powt_topowogy	topowogy;	/*  cuwwent topowogy */
	bfa_boowean_t		beacon;		/*  cuwwent beacon status */
	bfa_boowean_t		wink_e2e_beacon; /* wink beacon is on */
	bfa_boowean_t		bbsc_op_status;	/* fc cwedit wecovewy opew
						 * state */
	enum bfa_fec_state_s	fec_state;	/*!< cuwwent FEC state */

	/*
	 * Dynamic fiewd - info fwom FCS
	 */
	u32			pid;		/*  powt ID */
	enum bfa_powt_type	powt_type;	/*  cuwwent topowogy */
	u32			woopback;	/*  extewnaw woopback */
	u32			authfaiw;	/*  auth faiw state */

	/* FCoE specific  */
	u16			fcoe_vwan;
	u8			wsvd1[2];
};

/*
 *	      Powt FCP mappings.
 */
stwuct bfa_powt_fcpmap_s {
	chaw	osdevname[256];
	u32	bus;
	u32	tawget;
	u32	oswun;
	u32	fcid;
	wwn_t	nwwn;
	wwn_t	pwwn;
	u64	fcpwun;
	chaw	wuid[256];
};

/*
 *	      Powt WNID info.
 */
stwuct bfa_powt_wnid_s {
	wwn_t	  wwn;
	u32	  unittype;
	u32	  powtid;
	u32	  attached_nodes_num;
	u16	  ip_vewsion;
	u16	  udp_powt;
	u8	  ipaddw[16];
	u16	  wsvd;
	u16	  topowogydiscovewyfwags;
};

#pwagma pack(1)
stwuct bfa_fcpowt_fcf_s {
	wwn_t	name;		/*  FCF name		   */
	wwn_t	fabwic_name;    /*  Fabwic Name		   */
	u8	fipenabwed;	/*  FIP enabwed ow not	   */
	u8	fipfaiwed;	/*  FIP faiwed ow not	   */
	u8	wesv[2];
	u8	pwi;		/*  FCF pwiowity	   */
	u8	vewsion;	/*  FIP vewsion used	   */
	u8	avaiwabwe;      /*  Avaiwabwe fow wogin    */
	u8	fka_disabwed;   /*  FKA is disabwed	   */
	u8	maxsz_vewified; /*  FCoE max size vewified */
	u8	fc_map[3];      /*  FC map		   */
	__be16	vwan;		/*  FCoE vwan tag/pwiowity */
	u32	fka_adv_pew;    /*  FIP  ka advewt. pewiod */
	mac_t	mac;		/*  FCF mac		   */
};

/*
 *	Twunk states fow BCU/BFAW
 */
enum bfa_twunk_state {
	BFA_TWUNK_DISABWED	= 0,	/*  Twunk is not configuwed	*/
	BFA_TWUNK_ONWINE	= 1,	/*  Twunk is onwine		*/
	BFA_TWUNK_OFFWINE	= 2,	/*  Twunk is offwine		*/
};

/*
 *	VC attwibutes fow twunked wink
 */
stwuct bfa_twunk_vc_attw_s {
	u32 bb_cwedit;
	u32 ewp_opmode_fwags;
	u32 weq_cwedit;
	u16 vc_cwedits[8];
};

stwuct bfa_fcpowt_woop_info_s {
	u8	myawpa;		/* awpa cwaimed */
	u8	awpabm_vaw;	/* awpa bitmap vawid ow not (1 ow 0) */
	u8	wesvd[6];
	stwuct fc_awpabm_s awpabm;	/* awpa bitmap */
};

/*
 *	Wink state infowmation
 */
stwuct bfa_powt_wink_s {
	u8	 winkstate;	/*  Wink state bfa_powt_winkstate */
	u8	 winkstate_wsn;	/*  bfa_powt_winkstate_wsn_t */
	u8	 topowogy;	/*  P2P/WOOP bfa_powt_topowogy */
	u8	 speed;		/*  Wink speed (1/2/4/8 G) */
	u32	 winkstate_opt; /*  Winkstate optionaw data (debug) */
	u8	 twunked;	/*  Twunked ow not (1 ow 0) */
	u8	 fec_state;	/*!< State of FEC */
	u8	 wesvd[6];
	stwuct bfa_qos_attw_s  qos_attw;   /* QoS Attwibutes */
	union {
		stwuct bfa_fcpowt_woop_info_s woop_info;
		stwuct bfa_bbcw_attw_s bbcw_attw;
		union {
			stwuct bfa_qos_vc_attw_s qos_vc_attw;
					/*  VC info fwom EWP */
			stwuct bfa_twunk_vc_attw_s twunk_vc_attw;
			stwuct bfa_fcpowt_fcf_s fcf;
					/*  FCF infowmation (fow FCoE) */
		} vc_fcf;
	} attw;
};
#pwagma pack()

enum bfa_twunk_wink_fctw {
	BFA_TWUNK_WINK_FCTW_NOWMAW,
	BFA_TWUNK_WINK_FCTW_VC,
	BFA_TWUNK_WINK_FCTW_VC_QOS,
};

enum bfa_twunk_wink_state {
	BFA_TWUNK_WINK_STATE_UP = 1,		/* wink pawt of twunk */
	BFA_TWUNK_WINK_STATE_DN_WINKDN = 2,	/* physicaw wink down */
	BFA_TWUNK_WINK_STATE_DN_GWP_MIS = 3,	/* twunk gwoup diffewent */
	BFA_TWUNK_WINK_STATE_DN_SPD_MIS = 4,	/* speed mismatch */
	BFA_TWUNK_WINK_STATE_DN_MODE_MIS = 5,	/* wemote powt not twunked */
};

#define BFA_TWUNK_MAX_POWTS	2
stwuct bfa_twunk_wink_attw_s {
	wwn_t    twunk_wwn;
	enum bfa_twunk_wink_fctw fctw;
	enum bfa_twunk_wink_state wink_state;
	enum bfa_powt_speed	speed;
	u32 deskew;
};

stwuct bfa_twunk_attw_s {
	enum bfa_twunk_state	state;
	enum bfa_powt_speed	speed;
	u32		powt_id;
	u32		wsvd;
	stwuct bfa_twunk_wink_attw_s wink_attw[BFA_TWUNK_MAX_POWTS];
};

stwuct bfa_wpowt_haw_stats_s {
	u32        sm_un_cw;	    /*  uninit: cweate events      */
	u32        sm_un_unexp;	    /*  uninit: exception events   */
	u32        sm_cw_on;	    /*  cweated: onwine events     */
	u32        sm_cw_dew;	    /*  cweated: dewete events     */
	u32        sm_cw_hwf;	    /*  cweated: IOC down          */
	u32        sm_cw_unexp;	    /*  cweated: exception events  */
	u32        sm_fwc_wsp;	    /*  fw cweate: f/w wesponses   */
	u32        sm_fwc_dew;	    /*  fw cweate: dewete events   */
	u32        sm_fwc_off;	    /*  fw cweate: offwine events  */
	u32        sm_fwc_hwf;	    /*  fw cweate: IOC down        */
	u32        sm_fwc_unexp;    /*  fw cweate: exception events*/
	u32        sm_on_off;	    /*  onwine: offwine events     */
	u32        sm_on_dew;	    /*  onwine: dewete events      */
	u32        sm_on_hwf;	    /*  onwine: IOC down events    */
	u32        sm_on_unexp;	    /*  onwine: exception events   */
	u32        sm_fwd_wsp;	    /*  fw dewete: fw wesponses    */
	u32        sm_fwd_dew;	    /*  fw dewete: dewete events   */
	u32        sm_fwd_hwf;	    /*  fw dewete: IOC down events */
	u32        sm_fwd_unexp;    /*  fw dewete: exception events*/
	u32        sm_off_dew;	    /*  offwine: dewete events     */
	u32        sm_off_on;	    /*  offwine: onwine events     */
	u32        sm_off_hwf;	    /*  offwine: IOC down events   */
	u32        sm_off_unexp;    /*  offwine: exception events  */
	u32        sm_dew_fwwsp;    /*  dewete: fw wesponses       */
	u32        sm_dew_hwf;	    /*  dewete: IOC down events    */
	u32        sm_dew_unexp;    /*  dewete: exception events   */
	u32        sm_dewp_fwwsp;   /*  dewete pend: fw wesponses  */
	u32        sm_dewp_hwf;	    /*  dewete pend: IOC downs     */
	u32        sm_dewp_unexp;   /*  dewete pend: exceptions    */
	u32        sm_offp_fwwsp;   /*  off-pending: fw wesponses  */
	u32        sm_offp_dew;	    /*  off-pending: dewetes       */
	u32        sm_offp_hwf;	    /*  off-pending: IOC downs     */
	u32        sm_offp_unexp;   /*  off-pending: exceptions    */
	u32        sm_iocd_off;	    /*  IOC down: offwine events   */
	u32        sm_iocd_dew;	    /*  IOC down: dewete events    */
	u32        sm_iocd_on;	    /*  IOC down: onwine events    */
	u32        sm_iocd_unexp;   /*  IOC down: exceptions       */
	u32        wsvd;
};
#pwagma pack(1)
/*
 *  Wpowt's QoS attwibutes
 */
stwuct bfa_wpowt_qos_attw_s {
	u8		qos_pwiowity;	/*  wpowt's QoS pwiowity   */
	u8		wsvd[3];
	u32		qos_fwow_id;	/*  QoS fwow Id	 */
};
#pwagma pack()

#define BFA_IOBUCKET_MAX 14

stwuct bfa_itnim_watency_s {
	u32 min[BFA_IOBUCKET_MAX];
	u32 max[BFA_IOBUCKET_MAX];
	u32 count[BFA_IOBUCKET_MAX];
	u32 avg[BFA_IOBUCKET_MAX];
};

stwuct bfa_itnim_iopwofiwe_s {
	u32 cwock_wes_muw;
	u32 cwock_wes_div;
	u32 index;
	u32 io_pwofiwe_stawt_time;	/*  IO pwofiwe stawt time	*/
	u32 iocomps[BFA_IOBUCKET_MAX];	/*  IO compweted	*/
	stwuct bfa_itnim_watency_s io_watency;
};

/*
 *	vHBA powt attwibute vawues.
 */
stwuct bfa_vhba_attw_s {
	wwn_t	nwwn;       /* node wwn */
	wwn_t	pwwn;       /* powt wwn */
	u32	pid;        /* powt ID */
	bfa_boowean_t       io_pwofiwe; /* get it fwom fcpim mod */
	bfa_boowean_t       pwog_enabwed;   /* powtwog is enabwed */
	u16	path_tov;
	u8	wsvd[2];
};

/*
 * FC physicaw powt statistics.
 */
stwuct bfa_powt_fc_stats_s {
	u64     secs_weset;     /*  Seconds since stats is weset */
	u64     tx_fwames;      /*  Tx fwames                   */
	u64     tx_wowds;       /*  Tx wowds                    */
	u64     tx_wip;         /*  Tx WIP                      */
	u64	tx_wip_f7f7;	/*  Tx WIP_F7F7		*/
	u64	tx_wip_f8f7;	/*  Tx WIP_F8F7		*/
	u64	tx_awbf0;	/*  Tx AWB F0			*/
	u64     tx_nos;         /*  Tx NOS                      */
	u64     tx_ows;         /*  Tx OWS                      */
	u64     tx_ww;          /*  Tx WW                       */
	u64     tx_www;         /*  Tx WWW                      */
	u64     wx_fwames;      /*  Wx fwames                   */
	u64     wx_wowds;       /*  Wx wowds                    */
	u64     wip_count;      /*  Wx WIP                      */
	u64	wx_wip_f7f7;	/*  Wx WIP_F7F7		*/
	u64	wx_wip_f8f7;	/*  Wx WIP_F8F7		*/
	u64	wx_awbf0;	/*  Wx AWB F0			*/
	u64     nos_count;      /*  Wx NOS                      */
	u64     ows_count;      /*  Wx OWS                      */
	u64     ww_count;       /*  Wx WW                       */
	u64     www_count;      /*  Wx WWW                      */
	u64     invawid_cwcs;   /*  Wx CWC eww fwames           */
	u64     invawid_cwc_gd_eof; /*  Wx CWC eww good EOF fwames */
	u64     undewsized_fwm; /*  Wx undewsized fwames        */
	u64     ovewsized_fwm;  /*  Wx ovewsized fwames */
	u64     bad_eof_fwm;    /*  Wx fwames with bad EOF      */
	u64     ewwow_fwames;   /*  Ewwowed fwames              */
	u64     dwopped_fwames; /*  Dwopped fwames              */
	u64     wink_faiwuwes;  /*  Wink Faiwuwe (WF) count     */
	u64     woss_of_syncs;  /*  Woss of sync count          */
	u64     woss_of_signaws; /*  Woss of signaw count       */
	u64     pwimseq_ewws;   /*  Pwimitive sequence pwotocow eww. */
	u64     bad_os_count;   /*  Invawid owdewed sets        */
	u64     eww_enc_out;    /*  Encoding eww nonfwame_8b10b */
	u64     eww_enc;        /*  Encoding eww fwame_8b10b    */
	u64	bbcw_fwames_wost; /*!< BBCW Fwames Wost */
	u64	bbcw_wwdys_wost; /*!< BBCW WWDYs Wost */
	u64	bbcw_wink_wesets; /*!< BBCW Wink Wesets */
	u64	bbcw_fwame_wost_intws; /*!< BBCW Fwame woss intws */
	u64	bbcw_wwdy_wost_intws; /*!< BBCW Wwdy woss intws */
	u64	woop_timeouts;	/*  Woop timeouts		*/
};

/*
 * Eth Physicaw Powt statistics.
 */
stwuct bfa_powt_eth_stats_s {
	u64     secs_weset;     /*  Seconds since stats is weset */
	u64     fwame_64;       /*  Fwames 64 bytes             */
	u64     fwame_65_127;   /*  Fwames 65-127 bytes */
	u64     fwame_128_255;  /*  Fwames 128-255 bytes        */
	u64     fwame_256_511;  /*  Fwames 256-511 bytes        */
	u64     fwame_512_1023; /*  Fwames 512-1023 bytes       */
	u64     fwame_1024_1518; /*  Fwames 1024-1518 bytes     */
	u64     fwame_1519_1522; /*  Fwames 1519-1522 bytes     */
	u64     tx_bytes;       /*  Tx bytes                    */
	u64     tx_packets;      /*  Tx packets         */
	u64     tx_mcast_packets; /*  Tx muwticast packets      */
	u64     tx_bcast_packets; /*  Tx bwoadcast packets      */
	u64     tx_contwow_fwame; /*  Tx contwow fwame          */
	u64     tx_dwop;        /*  Tx dwops                    */
	u64     tx_jabbew;      /*  Tx jabbew                   */
	u64     tx_fcs_ewwow;   /*  Tx FCS ewwows               */
	u64     tx_fwagments;   /*  Tx fwagments                */
	u64     wx_bytes;       /*  Wx bytes                    */
	u64     wx_packets;     /*  Wx packets                  */
	u64     wx_mcast_packets; /*  Wx muwticast packets      */
	u64     wx_bcast_packets; /*  Wx bwoadcast packets      */
	u64     wx_contwow_fwames; /*  Wx contwow fwames        */
	u64     wx_unknown_opcode; /*  Wx unknown opcode        */
	u64     wx_dwop;        /*  Wx dwops                    */
	u64     wx_jabbew;      /*  Wx jabbew                   */
	u64     wx_fcs_ewwow;   /*  Wx FCS ewwows               */
	u64     wx_awignment_ewwow; /*  Wx awignment ewwows     */
	u64     wx_fwame_wength_ewwow; /*  Wx fwame wen ewwows  */
	u64     wx_code_ewwow;  /*  Wx code ewwows              */
	u64     wx_fwagments;   /*  Wx fwagments                */
	u64     wx_pause;       /*  Wx pause                    */
	u64     wx_zewo_pause;  /*  Wx zewo pause               */
	u64     tx_pause;       /*  Tx pause                    */
	u64     tx_zewo_pause;  /*  Tx zewo pause               */
	u64     wx_fcoe_pause;  /*  Wx FCoE pause               */
	u64     wx_fcoe_zewo_pause; /*  Wx FCoE zewo pause      */
	u64     tx_fcoe_pause;  /*  Tx FCoE pause               */
	u64     tx_fcoe_zewo_pause; /*  Tx FCoE zewo pause      */
	u64     wx_iscsi_pause; /*  Wx iSCSI pause              */
	u64     wx_iscsi_zewo_pause; /*  Wx iSCSI zewo pause    */
	u64     tx_iscsi_pause; /*  Tx iSCSI pause              */
	u64     tx_iscsi_zewo_pause; /*  Tx iSCSI zewo pause    */
};

/*
 *              Powt statistics.
 */
union bfa_powt_stats_u {
	stwuct bfa_powt_fc_stats_s      fc;
	stwuct bfa_powt_eth_stats_s     eth;
};

stwuct bfa_powt_cfg_mode_s {
	u16		max_pf;
	u16		max_vf;
	enum bfa_mode_s	mode;
};

#pwagma pack(1)

#define BFA_CEE_WWDP_MAX_STWING_WEN	(128)
#define BFA_CEE_DCBX_MAX_PWIOWITY	(8)
#define BFA_CEE_DCBX_MAX_PGID		(8)

stwuct bfa_cee_wwdp_stw_s {
	u8	sub_type;
	u8	wen;
	u8	wsvd[2];
	u8	vawue[BFA_CEE_WWDP_MAX_STWING_WEN];
};

stwuct bfa_cee_wwdp_cfg_s {
	stwuct bfa_cee_wwdp_stw_s chassis_id;
	stwuct bfa_cee_wwdp_stw_s powt_id;
	stwuct bfa_cee_wwdp_stw_s powt_desc;
	stwuct bfa_cee_wwdp_stw_s sys_name;
	stwuct bfa_cee_wwdp_stw_s sys_desc;
	stwuct bfa_cee_wwdp_stw_s mgmt_addw;
	u16	time_to_wive;
	u16	enabwed_system_cap;
};

/* CEE/DCBX pawametews */
stwuct bfa_cee_dcbx_cfg_s {
	u8	pgid[BFA_CEE_DCBX_MAX_PWIOWITY];
	u8	pg_pewcentage[BFA_CEE_DCBX_MAX_PGID];
	u8	pfc_pwimap; /* bitmap of pwiowties with PFC enabwed */
	u8	fcoe_pwimap; /* bitmap of pwiowities used fow FcoE twaffic */
	u8	iscsi_pwimap; /* bitmap of pwiowities used fow iSCSI twaffic */
	u8	dcbx_vewsion; /* opewating vewsion:CEE ow pweCEE */
	u8	wws_fcoe; /* FCoE Wogicaw Wink Status */
	u8	wws_wan; /* WAN Wogicaw Wink Status */
	u8	wsvd[2];
};

/* CEE Quewy */
stwuct bfa_cee_attw_s {
	u8	cee_status;
	u8	ewwow_weason;
	stwuct bfa_cee_wwdp_cfg_s wwdp_wemote;
	stwuct bfa_cee_dcbx_cfg_s dcbx_wemote;
	mac_t swc_mac;
	u8	wink_speed;
	u8	nw_pwiowity;
	u8	fiwwew[2];
};

/* WWDP/DCBX/CEE Statistics */
stwuct bfa_cee_stats_s {
	u32		wwdp_tx_fwames;		/* WWDP Tx Fwames */
	u32		wwdp_wx_fwames;		/* WWDP Wx Fwames */
	u32		wwdp_wx_fwames_invawid; /* WWDP Wx Fwames invawid */
	u32		wwdp_wx_fwames_new;     /* WWDP Wx Fwames new */
	u32		wwdp_twvs_unwecognized; /* WWDP Wx unwecog. TWVs */
	u32		wwdp_wx_shutdown_twvs;  /* WWDP Wx shutdown TWVs */
	u32		wwdp_info_aged_out;     /* WWDP wemote info aged */
	u32		dcbx_phywink_ups;       /* DCBX phy wink ups */
	u32		dcbx_phywink_downs;     /* DCBX phy wink downs */
	u32		dcbx_wx_twvs;           /* DCBX Wx TWVs */
	u32		dcbx_wx_twvs_invawid;   /* DCBX Wx TWVs invawid */
	u32		dcbx_contwow_twv_ewwow; /* DCBX contwow TWV ewwows */
	u32		dcbx_featuwe_twv_ewwow; /* DCBX featuwe TWV ewwows */
	u32		dcbx_cee_cfg_new;       /* DCBX new CEE cfg wcvd */
	u32		cee_status_down;        /* DCB status down */
	u32		cee_status_up;          /* DCB status up */
	u32		cee_hw_cfg_changed;     /* DCB hw cfg changed */
	u32		cee_wx_invawid_cfg;     /* DCB invawid cfg */
};

#pwagma pack()

/*
 *			AEN wewated definitions
 */
#define BFAD_NW_VENDOW_ID (((u64)0x01 << SCSI_NW_VID_TYPE_SHIFT) \
			   | BFA_PCI_VENDOW_ID_BWOCADE)

/* BFA wemote powt events */
enum bfa_wpowt_aen_event {
	BFA_WPOWT_AEN_ONWINE     = 1,   /* WPowt onwine event */
	BFA_WPOWT_AEN_OFFWINE    = 2,   /* WPowt offwine event */
	BFA_WPOWT_AEN_DISCONNECT = 3,   /* WPowt disconnect event */
	BFA_WPOWT_AEN_QOS_PWIO   = 4,   /* QOS pwiowity change event */
	BFA_WPOWT_AEN_QOS_FWOWID = 5,   /* QOS fwow Id change event */
};

stwuct bfa_wpowt_aen_data_s {
	u16             vf_id;  /* vf_id of this wogicaw powt */
	u16             wsvd[3];
	wwn_t           ppwwn;  /* WWN of its physicaw powt */
	wwn_t           wpwwn;  /* WWN of this wogicaw powt */
	wwn_t           wpwwn;  /* WWN of this wemote powt */
	union {
		stwuct bfa_wpowt_qos_attw_s qos;
	} pwiv;
};

union bfa_aen_data_u {
	stwuct bfa_adaptew_aen_data_s	adaptew;
	stwuct bfa_powt_aen_data_s	powt;
	stwuct bfa_wpowt_aen_data_s	wpowt;
	stwuct bfa_wpowt_aen_data_s	wpowt;
	stwuct bfa_itnim_aen_data_s	itnim;
	stwuct bfa_audit_aen_data_s	audit;
	stwuct bfa_ioc_aen_data_s	ioc;
};

#define BFA_AEN_MAX_ENTWY	512

stwuct bfa_aen_entwy_s {
	stwuct wist_head	qe;
	enum bfa_aen_categowy   aen_categowy;
	int                     aen_type;
	union bfa_aen_data_u    aen_data;
	u64			aen_tv_sec;
	u64			aen_tv_usec;
	u32                     seq_num;
	u32                     bfad_num;
};

#endif /* __BFA_DEFS_SVC_H__ */
