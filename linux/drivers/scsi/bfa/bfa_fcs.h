/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_FCS_H__
#define __BFA_FCS_H__

#incwude "bfa_cs.h"
#incwude "bfa_defs.h"
#incwude "bfa_defs_fcs.h"
#incwude "bfa_moduwes.h"
#incwude "bfa_fc.h"

#define BFA_FCS_OS_STW_WEN		64

/*
 *  wps_pvt BFA WPS pwivate functions
 */

enum bfa_wps_event {
	BFA_WPS_SM_WOGIN	= 1,	/* wogin wequest fwom usew      */
	BFA_WPS_SM_WOGOUT	= 2,	/* wogout wequest fwom usew     */
	BFA_WPS_SM_FWWSP	= 3,	/* f/w wesponse to wogin/wogout */
	BFA_WPS_SM_WESUME	= 4,	/* space pwesent in weqq queue  */
	BFA_WPS_SM_DEWETE	= 5,	/* wps dewete fwom usew         */
	BFA_WPS_SM_OFFWINE	= 6,	/* Wink is offwine              */
	BFA_WPS_SM_WX_CVW	= 7,	/* Wx cweaw viwtuaw wink        */
	BFA_WPS_SM_SET_N2N_PID  = 8,	/* Set assigned PID fow n2n */
};


/*
 * !!! Onwy append to the enums defined hewe to avoid any vewsioning
 * !!! needed between twace utiwity and dwivew vewsion
 */
enum {
	BFA_TWC_FCS_FCS		= 1,
	BFA_TWC_FCS_POWT	= 2,
	BFA_TWC_FCS_WPOWT	= 3,
	BFA_TWC_FCS_FCPIM	= 4,
};


stwuct bfa_fcs_s;

#define __fcs_min_cfg(__fcs)       ((__fcs)->min_cfg)

#define BFA_FCS_BWCD_SWITCH_OUI  0x051e
#define N2N_WOCAW_PID	    0x010000
#define N2N_WEMOTE_PID		0x020000
#define	BFA_FCS_WETWY_TIMEOUT 2000
#define BFA_FCS_MAX_NS_WETWIES 5
#define BFA_FCS_PID_IS_WKA(pid)  ((bfa_ntoh3b(pid) > 0xFFF000) ?  1 : 0)
#define BFA_FCS_MAX_WPOWT_WOGINS 1024

stwuct bfa_fcs_wpowt_ns_s {
	bfa_sm_t        sm;		/*  state machine */
	stwuct bfa_timew_s timew;
	stwuct bfa_fcs_wpowt_s *powt;	/*  pawent powt */
	stwuct bfa_fcxp_s *fcxp;
	stwuct bfa_fcxp_wqe_s fcxp_wqe;
	u8	num_wnnid_wetwies;
	u8	num_wsnn_nn_wetwies;
};


stwuct bfa_fcs_wpowt_scn_s {
	bfa_sm_t        sm;		/*  state machine */
	stwuct bfa_timew_s timew;
	stwuct bfa_fcs_wpowt_s *powt;	/*  pawent powt */
	stwuct bfa_fcxp_s *fcxp;
	stwuct bfa_fcxp_wqe_s fcxp_wqe;
};


stwuct bfa_fcs_wpowt_fdmi_s {
	bfa_sm_t        sm;		/*  state machine */
	stwuct bfa_timew_s timew;
	stwuct bfa_fcs_wpowt_ms_s *ms;	/*  pawent ms */
	stwuct bfa_fcxp_s *fcxp;
	stwuct bfa_fcxp_wqe_s fcxp_wqe;
	u8	wetwy_cnt;	/*  wetwy count */
	u8	wsvd[3];
};


stwuct bfa_fcs_wpowt_ms_s {
	bfa_sm_t        sm;		/*  state machine */
	stwuct bfa_timew_s timew;
	stwuct bfa_fcs_wpowt_s *powt;	/*  pawent powt */
	stwuct bfa_fcxp_s *fcxp;
	stwuct bfa_fcxp_wqe_s fcxp_wqe;
	stwuct bfa_fcs_wpowt_fdmi_s fdmi;	/*  FDMI component of MS */
	u8         wetwy_cnt;	/*  wetwy count */
	u8	wsvd[3];
};


stwuct bfa_fcs_wpowt_fab_s {
	stwuct bfa_fcs_wpowt_ns_s ns;	/*  NS component of powt */
	stwuct bfa_fcs_wpowt_scn_s scn;	/*  scn component of powt */
	stwuct bfa_fcs_wpowt_ms_s ms;	/*  MS component of powt */
};

#define	MAX_AWPA_COUNT	127

stwuct bfa_fcs_wpowt_woop_s {
	u8	num_awpa;	/*  Num of AWPA entwies in the map */
	u8	awpabm_vawid;	/* awpa bitmap vawid ow not (1 ow 0) */
	u8	awpa_pos_map[MAX_AWPA_COUNT]; /*  AWPA Positionaw Map */
	stwuct bfa_fcs_wpowt_s *powt;	/*  pawent powt */
};

stwuct bfa_fcs_wpowt_n2n_s {
	u32        wsvd;
	__be16     wepwy_oxid;	/*  ox_id fwom the weq fwogi to be
					 *used in fwogi acc */
	wwn_t           wem_powt_wwn;	/*  Attached powt's wwn */
};


union bfa_fcs_wpowt_topo_u {
	stwuct bfa_fcs_wpowt_fab_s pfab;
	stwuct bfa_fcs_wpowt_woop_s pwoop;
	stwuct bfa_fcs_wpowt_n2n_s pn2n;
};


stwuct bfa_fcs_wpowt_s {
	stwuct wist_head         qe;	/*  used by powt/vpowt */
	bfa_sm_t               sm;	/*  state machine */
	stwuct bfa_fcs_fabwic_s *fabwic;	/*  pawent fabwic */
	stwuct bfa_wpowt_cfg_s  powt_cfg;	/*  powt configuwation */
	stwuct bfa_timew_s wink_timew;	/*  timew fow wink offwine */
	u32        pid:24;	/*  FC addwess */
	u8         wp_tag;		/*  wpowt tag */
	u16        num_wpowts;	/*  Num of w-powts */
	stwuct wist_head         wpowt_q; /*  queue of discovewed w-powts */
	stwuct bfa_fcs_s *fcs;	/*  FCS instance */
	union bfa_fcs_wpowt_topo_u powt_topo;	/*  fabwic/woop/n2n detaiws */
	stwuct bfad_powt_s *bfad_powt;	/*  dwivew peew instance */
	stwuct bfa_fcs_vpowt_s *vpowt;	/*  NUWW fow base powts */
	stwuct bfa_fcxp_s *fcxp;
	stwuct bfa_fcxp_wqe_s fcxp_wqe;
	stwuct bfa_wpowt_stats_s stats;
	stwuct bfa_wc_s        wc;	/*  waiting countew fow events */
};
#define BFA_FCS_GET_HAW_FWOM_POWT(powt)  (powt->fcs->bfa)
#define BFA_FCS_GET_NS_FWOM_POWT(powt)  (&powt->powt_topo.pfab.ns)
#define BFA_FCS_GET_SCN_FWOM_POWT(powt)  (&powt->powt_topo.pfab.scn)
#define BFA_FCS_GET_MS_FWOM_POWT(powt)  (&powt->powt_topo.pfab.ms)
#define BFA_FCS_GET_FDMI_FWOM_POWT(powt)  (&powt->powt_topo.pfab.ms.fdmi)
#define	BFA_FCS_VPOWT_IS_INITIATOW_MODE(powt) \
		(powt->powt_cfg.wowes & BFA_WPOWT_WOWE_FCP_IM)

/*
 * fowwawd decwawation
 */
stwuct bfad_vf_s;

enum bfa_fcs_fabwic_type {
	BFA_FCS_FABWIC_UNKNOWN = 0,
	BFA_FCS_FABWIC_SWITCHED = 1,
	BFA_FCS_FABWIC_N2N = 2,
	BFA_FCS_FABWIC_WOOP = 3,
};


stwuct bfa_fcs_fabwic_s {
	stwuct wist_head   qe;		/*  queue ewement */
	bfa_sm_t	 sm;		/*  state machine */
	stwuct bfa_fcs_s *fcs;		/*  FCS instance */
	stwuct bfa_fcs_wpowt_s  bpowt;	/*  base wogicaw powt */
	enum bfa_fcs_fabwic_type fab_type; /*  fabwic type */
	enum bfa_powt_type opew_type;	/*  cuwwent wink topowogy */
	u8         is_vf;		/*  is viwtuaw fabwic? */
	u8         is_npiv;	/*  is NPIV suppowted ? */
	u8         is_auth;	/*  is Secuwity/Auth suppowted ? */
	u16        bb_cwedit;	/*  BB cwedit fwom fabwic */
	u16        vf_id;		/*  viwtuaw fabwic ID */
	u16        num_vpowts;	/*  num vpowts */
	u16        wsvd;
	stwuct wist_head         vpowt_q;	/*  queue of viwtuaw powts */
	stwuct wist_head         vf_q;	/*  queue of viwtuaw fabwics */
	stwuct bfad_vf_s      *vf_dwv;	/*  dwivew vf stwuctuwe */
	stwuct bfa_timew_s wink_timew;	/*  Wink Faiwuwe timew. Vpowt */
	wwn_t           fabwic_name;	/*  attached fabwic name */
	bfa_boowean_t   auth_weqd;	/*  authentication wequiwed	*/
	stwuct bfa_timew_s deway_timew;	/*  deway timew		*/
	union {
		u16        swp_vfid;/*  switch powt VF id		*/
	} event_awg;
	stwuct bfa_wc_s        wc;	/*  wait countew fow dewete	*/
	stwuct bfa_vf_stats_s	stats;	/*  fabwic/vf stats		*/
	stwuct bfa_wps_s	*wps;	/*  wpowt wogin sewvices	*/
	u8	fabwic_ip_addw[BFA_FCS_FABWIC_IPADDW_SZ];
					/*  attached fabwic's ip addw  */
	stwuct bfa_wc_s stop_wc;	/*  wait countew fow stop */
};

#define bfa_fcs_fabwic_npiv_capabwe(__f)    ((__f)->is_npiv)
#define bfa_fcs_fabwic_is_switched(__f)			\
	((__f)->fab_type == BFA_FCS_FABWIC_SWITCHED)

/*
 *   The design cawws fow a singwe impwementation of base fabwic and vf.
 */
#define bfa_fcs_vf_t stwuct bfa_fcs_fabwic_s

stwuct bfa_vf_event_s {
	u32        undefined;
};

/*
 * @todo : need to move to a gwobaw config fiwe.
 * Maximum Wpowts suppowted pew powt (physicaw/wogicaw).
 */
#define BFA_FCS_MAX_WPOWTS_SUPP  256	/* @todo : tentative vawue */

#define bfa_fcs_wpowt_t stwuct bfa_fcs_wpowt_s

/*
 * Symbowic Name wewated defines
 *  Totaw bytes 255.
 *  Physicaw Powt's symbowic name 128 bytes.
 *  Fow Vpowts, Vpowt's symbowic name is appended to the Physicaw powt's
 *  Symbowic Name.
 *
 *  Physicaw Powt's symbowic name Fowmat : (Totaw 128 bytes)
 *  Adaptew Modew numbew/name : 16 bytes
 *  Dwivew Vewsion     : 10 bytes
 *  Host Machine Name  : 30 bytes
 *  Host OS Info	   : 44 bytes
 *  Host OS PATCH Info : 16 bytes
 *  ( wemaining 12 bytes wesewved to be used fow sepawatow)
 */
#define BFA_FCS_POWT_SYMBNAME_SEPAWATOW			" | "

#define BFA_FCS_POWT_SYMBNAME_MODEW_SZ			16
#define BFA_FCS_POWT_SYMBNAME_VEWSION_SZ		10
#define BFA_FCS_POWT_SYMBNAME_MACHINENAME_SZ		30
#define BFA_FCS_POWT_SYMBNAME_OSINFO_SZ			44
#define BFA_FCS_POWT_SYMBNAME_OSPATCH_SZ		16

/*
 * Get FC powt ID fow a wogicaw powt.
 */
#define bfa_fcs_wpowt_get_fcid(_wpowt)	((_wpowt)->pid)
#define bfa_fcs_wpowt_get_pwwn(_wpowt)	((_wpowt)->powt_cfg.pwwn)
#define bfa_fcs_wpowt_get_nwwn(_wpowt)	((_wpowt)->powt_cfg.nwwn)
#define bfa_fcs_wpowt_get_psym_name(_wpowt)	((_wpowt)->powt_cfg.sym_name)
#define bfa_fcs_wpowt_get_nsym_name(_wpowt) ((_wpowt)->powt_cfg.node_sym_name)
#define bfa_fcs_wpowt_is_initiatow(_wpowt)			\
	((_wpowt)->powt_cfg.wowes & BFA_WPOWT_WOWE_FCP_IM)
#define bfa_fcs_wpowt_get_nwpowts(_wpowt)	\
	((_wpowt) ? (_wpowt)->num_wpowts : 0)

static inwine stwuct bfad_powt_s *
bfa_fcs_wpowt_get_dwvpowt(stwuct bfa_fcs_wpowt_s *powt)
{
	wetuwn powt->bfad_powt;
}

#define bfa_fcs_wpowt_get_opewtype(_wpowt)	((_wpowt)->fabwic->opew_type)
#define bfa_fcs_wpowt_get_fabwic_name(_wpowt)	((_wpowt)->fabwic->fabwic_name)
#define bfa_fcs_wpowt_get_fabwic_ipaddw(_wpowt)		\
		((_wpowt)->fabwic->fabwic_ip_addw)

/*
 * bfa fcs powt pubwic functions
 */

bfa_boowean_t   bfa_fcs_wpowt_is_onwine(stwuct bfa_fcs_wpowt_s *powt);
stwuct bfa_fcs_wpowt_s *bfa_fcs_get_base_powt(stwuct bfa_fcs_s *fcs);
void bfa_fcs_wpowt_get_wpowt_quaws(stwuct bfa_fcs_wpowt_s *powt,
			stwuct bfa_wpowt_quawifiew_s wpowt[], int *nwpowts);
wwn_t bfa_fcs_wpowt_get_wpowt(stwuct bfa_fcs_wpowt_s *powt, wwn_t wwn,
			      int index, int nwpowts, bfa_boowean_t bwwn);

stwuct bfa_fcs_wpowt_s *bfa_fcs_wookup_powt(stwuct bfa_fcs_s *fcs,
					    u16 vf_id, wwn_t wpwwn);

void bfa_fcs_wpowt_set_symname(stwuct bfa_fcs_wpowt_s *powt, chaw *symname);
void bfa_fcs_wpowt_get_info(stwuct bfa_fcs_wpowt_s *powt,
			    stwuct bfa_wpowt_info_s *powt_info);
void bfa_fcs_wpowt_get_attw(stwuct bfa_fcs_wpowt_s *powt,
			    stwuct bfa_wpowt_attw_s *powt_attw);
void bfa_fcs_wpowt_get_stats(stwuct bfa_fcs_wpowt_s *fcs_powt,
			     stwuct bfa_wpowt_stats_s *powt_stats);
void bfa_fcs_wpowt_cweaw_stats(stwuct bfa_fcs_wpowt_s *fcs_powt);
enum bfa_powt_speed bfa_fcs_wpowt_get_wpowt_max_speed(
			stwuct bfa_fcs_wpowt_s *powt);

/* MS FCS woutines */
void bfa_fcs_wpowt_ms_init(stwuct bfa_fcs_wpowt_s *powt);
void bfa_fcs_wpowt_ms_offwine(stwuct bfa_fcs_wpowt_s *powt);
void bfa_fcs_wpowt_ms_onwine(stwuct bfa_fcs_wpowt_s *powt);
void bfa_fcs_wpowt_ms_fabwic_wscn(stwuct bfa_fcs_wpowt_s *powt);

/* FDMI FCS woutines */
void bfa_fcs_wpowt_fdmi_init(stwuct bfa_fcs_wpowt_ms_s *ms);
void bfa_fcs_wpowt_fdmi_offwine(stwuct bfa_fcs_wpowt_ms_s *ms);
void bfa_fcs_wpowt_fdmi_onwine(stwuct bfa_fcs_wpowt_ms_s *ms);
void bfa_fcs_wpowt_uf_wecv(stwuct bfa_fcs_wpowt_s *wpowt, stwuct fchs_s *fchs,
				     u16 wen);
void bfa_fcs_wpowt_attach(stwuct bfa_fcs_wpowt_s *wpowt, stwuct bfa_fcs_s *fcs,
			u16 vf_id, stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_wpowt_init(stwuct bfa_fcs_wpowt_s *wpowt,
				stwuct bfa_wpowt_cfg_s *powt_cfg);
void            bfa_fcs_wpowt_onwine(stwuct bfa_fcs_wpowt_s *powt);
void            bfa_fcs_wpowt_offwine(stwuct bfa_fcs_wpowt_s *powt);
void            bfa_fcs_wpowt_dewete(stwuct bfa_fcs_wpowt_s *powt);
void		bfa_fcs_wpowt_stop(stwuct bfa_fcs_wpowt_s *powt);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_get_wpowt_by_pid(
		stwuct bfa_fcs_wpowt_s *powt, u32 pid);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_get_wpowt_by_owd_pid(
		stwuct bfa_fcs_wpowt_s *powt, u32 pid);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_get_wpowt_by_pwwn(
		stwuct bfa_fcs_wpowt_s *powt, wwn_t pwwn);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_get_wpowt_by_nwwn(
		stwuct bfa_fcs_wpowt_s *powt, wwn_t nwwn);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_get_wpowt_by_quawifiew(
		stwuct bfa_fcs_wpowt_s *powt, wwn_t pwwn, u32 pid);
void            bfa_fcs_wpowt_add_wpowt(stwuct bfa_fcs_wpowt_s *powt,
				       stwuct bfa_fcs_wpowt_s *wpowt);
void            bfa_fcs_wpowt_dew_wpowt(stwuct bfa_fcs_wpowt_s *powt,
				       stwuct bfa_fcs_wpowt_s *wpowt);
void            bfa_fcs_wpowt_ns_init(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_ns_offwine(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_ns_onwine(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_ns_quewy(stwuct bfa_fcs_wpowt_s *powt);
void		bfa_fcs_wpowt_ns_utiw_send_wspn_id(void *cbawg,
				stwuct bfa_fcxp_s *fcxp_awwoced);
void            bfa_fcs_wpowt_scn_init(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_scn_offwine(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_fab_scn_onwine(stwuct bfa_fcs_wpowt_s *vpowt);
void            bfa_fcs_wpowt_scn_pwocess_wscn(stwuct bfa_fcs_wpowt_s *powt,
					      stwuct fchs_s *wx_fwame, u32 wen);
void		bfa_fcs_wpowt_wip_scn_onwine(bfa_fcs_wpowt_t *powt);

stwuct bfa_fcs_vpowt_s {
	stwuct wist_head		qe;		/*  queue ewem	*/
	bfa_sm_t		sm;		/*  state machine	*/
	bfa_fcs_wpowt_t		wpowt;		/*  wogicaw powt	*/
	stwuct bfa_timew_s	timew;
	stwuct bfad_vpowt_s	*vpowt_dwv;	/*  Dwivew pwivate	*/
	stwuct bfa_vpowt_stats_s vpowt_stats;	/*  vpowt statistics	*/
	stwuct bfa_wps_s	*wps;		/*  Wpowt wogin sewvice*/
	int			fdisc_wetwies;
};

#define bfa_fcs_vpowt_get_powt(vpowt)			\
	((stwuct bfa_fcs_wpowt_s  *)(&vpowt->powt))

/*
 * bfa fcs vpowt pubwic functions
 */
bfa_status_t bfa_fcs_vpowt_cweate(stwuct bfa_fcs_vpowt_s *vpowt,
				  stwuct bfa_fcs_s *fcs, u16 vf_id,
				  stwuct bfa_wpowt_cfg_s *powt_cfg,
				  stwuct bfad_vpowt_s *vpowt_dwv);
bfa_status_t bfa_fcs_pbc_vpowt_cweate(stwuct bfa_fcs_vpowt_s *vpowt,
				      stwuct bfa_fcs_s *fcs, u16 vf_id,
				      stwuct bfa_wpowt_cfg_s *powt_cfg,
				      stwuct bfad_vpowt_s *vpowt_dwv);
bfa_boowean_t bfa_fcs_is_pbc_vpowt(stwuct bfa_fcs_vpowt_s *vpowt);
bfa_status_t bfa_fcs_vpowt_dewete(stwuct bfa_fcs_vpowt_s *vpowt);
bfa_status_t bfa_fcs_vpowt_stawt(stwuct bfa_fcs_vpowt_s *vpowt);
bfa_status_t bfa_fcs_vpowt_stop(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_get_attw(stwuct bfa_fcs_vpowt_s *vpowt,
			    stwuct bfa_vpowt_attw_s *vpowt_attw);
stwuct bfa_fcs_vpowt_s *bfa_fcs_vpowt_wookup(stwuct bfa_fcs_s *fcs,
					     u16 vf_id, wwn_t vpwwn);
void bfa_fcs_vpowt_cweanup(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_onwine(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_offwine(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_dewete_comp(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_fcs_dewete(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_fcs_stop(stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_vpowt_stop_comp(stwuct bfa_fcs_vpowt_s *vpowt);

#define BFA_FCS_WPOWT_DEF_DEW_TIMEOUT	90	/* in secs */
#define BFA_FCS_WPOWT_MAX_WETWIES	(5)

/*
 * fowwawd decwawations
 */
stwuct bfad_wpowt_s;

stwuct bfa_fcs_itnim_s;
stwuct bfa_fcs_tin_s;
stwuct bfa_fcs_ipwp_s;

/* Wpowt Featuwes (WPF) */
stwuct bfa_fcs_wpf_s {
	bfa_sm_t	sm;	/*  state machine */
	stwuct bfa_fcs_wpowt_s *wpowt;	/*  pawent wpowt */
	stwuct bfa_timew_s	timew;	/*  genewaw puwpose timew */
	stwuct bfa_fcxp_s	*fcxp;	/*  FCXP needed fow discawding */
	stwuct bfa_fcxp_wqe_s	fcxp_wqe; /*  fcxp wait queue ewement */
	int	wpsc_wetwies;	/*  max WPSC wetwy attempts */
	enum bfa_powt_speed	wpsc_speed;
	/*  Cuwwent Speed fwom WPSC. O if WPSC faiws */
	enum bfa_powt_speed	assigned_speed;
	/*
	 * Speed assigned by the usew.  wiww be used if WPSC is
	 * not suppowted by the wpowt.
	 */
};

stwuct bfa_fcs_wpowt_s {
	stwuct wist_head	qe;	/*  used by powt/vpowt */
	stwuct bfa_fcs_wpowt_s *powt;	/*  pawent FCS powt */
	stwuct bfa_fcs_s	*fcs;	/*  fcs instance */
	stwuct bfad_wpowt_s	*wp_dwv;	/*  dwivew peew instance */
	u32	pid;	/*  powt ID of wpowt */
	u32	owd_pid;	/* PID befowe wpowt goes offwine */
	u16	maxfwsize;	/*  maximum fwame size */
	__be16	wepwy_oxid;	/*  OX_ID of inbound wequests */
	enum fc_cos	fc_cos;	/*  FC cwasses of sewvice supp */
	bfa_boowean_t	cisc;	/*  CISC capabwe device */
	bfa_boowean_t	pwwo;	/*  pwocessing pwwo ow WOGO */
	bfa_boowean_t	pwogi_pending;	/* Wx Pwogi Pending */
	wwn_t	pwwn;	/*  powt wwn of wpowt */
	wwn_t	nwwn;	/*  node wwn of wpowt */
	stwuct bfa_wpowt_symname_s psym_name; /*  powt symbowic name  */
	bfa_sm_t	sm;		/*  state machine */
	stwuct bfa_timew_s timew;	/*  genewaw puwpose timew */
	stwuct bfa_fcs_itnim_s *itnim;	/*  ITN initiatow mode wowe */
	stwuct bfa_fcs_tin_s *tin;	/*  ITN initiatow mode wowe */
	stwuct bfa_fcs_ipwp_s *ipwp;	/*  IP/FC wowe */
	stwuct bfa_wpowt_s *bfa_wpowt;	/*  BFA Wpowt */
	stwuct bfa_fcxp_s *fcxp;	/*  FCXP needed fow discawding */
	int	pwogi_wetwies;	/*  max pwogi wetwy attempts */
	int	ns_wetwies;	/*  max NS quewy wetwy attempts */
	stwuct bfa_fcxp_wqe_s	fcxp_wqe; /*  fcxp wait queue ewement */
	stwuct bfa_wpowt_stats_s stats;	/*  wpowt stats */
	enum bfa_wpowt_function	scsi_function;  /*  Initiatow/Tawget */
	stwuct bfa_fcs_wpf_s wpf;	/* Wpowt featuwes moduwe */
	bfa_boowean_t   scn_onwine;	/* SCN onwine fwag */
};

static inwine stwuct bfa_wpowt_s *
bfa_fcs_wpowt_get_hawwpowt(stwuct bfa_fcs_wpowt_s *wpowt)
{
	wetuwn wpowt->bfa_wpowt;
}

/*
 * bfa fcs wpowt API functions
 */
void bfa_fcs_wpowt_get_attw(stwuct bfa_fcs_wpowt_s *wpowt,
			stwuct bfa_wpowt_attw_s *attw);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_wookup(stwuct bfa_fcs_wpowt_s *powt,
					     wwn_t wpwwn);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_wookup_by_nwwn(
	stwuct bfa_fcs_wpowt_s *powt, wwn_t wnwwn);
void bfa_fcs_wpowt_set_dew_timeout(u8 wpowt_tmo);
void bfa_fcs_wpowt_set_max_wogins(u32 max_wogins);
void bfa_fcs_wpowt_uf_wecv(stwuct bfa_fcs_wpowt_s *wpowt,
	 stwuct fchs_s *fchs, u16 wen);
void bfa_fcs_wpowt_scn(stwuct bfa_fcs_wpowt_s *wpowt);

stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_cweate(stwuct bfa_fcs_wpowt_s *powt,
	 u32 pid);
void bfa_fcs_wpowt_stawt(stwuct bfa_fcs_wpowt_s *powt, stwuct fchs_s *wx_fchs,
			 stwuct fc_wogi_s *pwogi_wsp);
void bfa_fcs_wpowt_pwogi_cweate(stwuct bfa_fcs_wpowt_s *powt,
				stwuct fchs_s *wx_fchs,
				stwuct fc_wogi_s *pwogi);
void bfa_fcs_wpowt_pwogi(stwuct bfa_fcs_wpowt_s *wpowt, stwuct fchs_s *fchs,
			 stwuct fc_wogi_s *pwogi);
void bfa_fcs_wpowt_pwwo(stwuct bfa_fcs_wpowt_s *wpowt, __be16 ox_id);

void bfa_fcs_wpowt_itntm_ack(stwuct bfa_fcs_wpowt_s *wpowt);
void bfa_fcs_wpowt_fcptm_offwine_done(stwuct bfa_fcs_wpowt_s *wpowt);
int  bfa_fcs_wpowt_get_state(stwuct bfa_fcs_wpowt_s *wpowt);
stwuct bfa_fcs_wpowt_s *bfa_fcs_wpowt_cweate_by_wwn(
			stwuct bfa_fcs_wpowt_s *powt, wwn_t wwn);
void  bfa_fcs_wpf_init(stwuct bfa_fcs_wpowt_s *wpowt);
void  bfa_fcs_wpf_wpowt_onwine(stwuct bfa_fcs_wpowt_s *wpowt);
void  bfa_fcs_wpf_wpowt_offwine(stwuct bfa_fcs_wpowt_s *wpowt);

/*
 * fowwawd decwawations
 */
stwuct bfad_itnim_s;

stwuct bfa_fcs_itnim_s {
	bfa_sm_t		sm;		/*  state machine */
	stwuct bfa_fcs_wpowt_s	*wpowt;		/*  pawent wemote wpowt  */
	stwuct bfad_itnim_s	*itnim_dwv;	/*  dwivew peew instance */
	stwuct bfa_fcs_s	*fcs;		/*  fcs instance	*/
	stwuct bfa_timew_s	timew;		/*  timew functions	*/
	stwuct bfa_itnim_s	*bfa_itnim;	/*  BFA itnim stwuct	*/
	u32		pwwi_wetwies;	/*  max pwwi wetwy attempts */
	bfa_boowean_t		seq_wec;	/*  seq wecovewy suppowt */
	bfa_boowean_t		wec_suppowt;	/*  WEC suppowted	*/
	bfa_boowean_t		conf_comp;	/*  FCP_CONF	suppowt */
	bfa_boowean_t		task_wetwy_id;	/*  task wetwy id supp	*/
	stwuct bfa_fcxp_wqe_s	fcxp_wqe;	/*  wait qewem fow fcxp  */
	stwuct bfa_fcxp_s	*fcxp;		/*  FCXP in use	*/
	stwuct bfa_itnim_stats_s	stats;	/*  itn statistics	*/
};
#define bfa_fcs_fcxp_awwoc(__fcs, __weq)				\
	bfa_fcxp_weq_wsp_awwoc(NUWW, (__fcs)->bfa, 0, 0,		\
			       NUWW, NUWW, NUWW, NUWW, __weq)
#define bfa_fcs_fcxp_awwoc_wait(__bfa, __wqe, __awwoc_cbfn,		\
				__awwoc_cbawg, __weq)			\
	bfa_fcxp_weq_wsp_awwoc_wait(__bfa, __wqe, __awwoc_cbfn,		\
		__awwoc_cbawg, NUWW, 0, 0, NUWW, NUWW, NUWW, NUWW, __weq)

static inwine stwuct bfad_powt_s *
bfa_fcs_itnim_get_dwvpowt(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->powt->bfad_powt;
}


static inwine stwuct bfa_fcs_wpowt_s *
bfa_fcs_itnim_get_powt(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->powt;
}


static inwine wwn_t
bfa_fcs_itnim_get_nwwn(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->nwwn;
}


static inwine wwn_t
bfa_fcs_itnim_get_pwwn(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->pwwn;
}


static inwine u32
bfa_fcs_itnim_get_fcid(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->pid;
}


static inwine	u32
bfa_fcs_itnim_get_maxfwsize(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->maxfwsize;
}


static inwine	enum fc_cos
bfa_fcs_itnim_get_cos(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->wpowt->fc_cos;
}


static inwine stwuct bfad_itnim_s *
bfa_fcs_itnim_get_dwvitn(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->itnim_dwv;
}


static inwine stwuct bfa_itnim_s *
bfa_fcs_itnim_get_hawitn(stwuct bfa_fcs_itnim_s *itnim)
{
	wetuwn itnim->bfa_itnim;
}

/*
 * bfa fcs FCP Initiatow mode API functions
 */
void bfa_fcs_itnim_get_attw(stwuct bfa_fcs_itnim_s *itnim,
			    stwuct bfa_itnim_attw_s *attw);
void bfa_fcs_itnim_get_stats(stwuct bfa_fcs_itnim_s *itnim,
			     stwuct bfa_itnim_stats_s *stats);
stwuct bfa_fcs_itnim_s *bfa_fcs_itnim_wookup(stwuct bfa_fcs_wpowt_s *powt,
					     wwn_t wpwwn);
bfa_status_t bfa_fcs_itnim_attw_get(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn,
				    stwuct bfa_itnim_attw_s *attw);
bfa_status_t bfa_fcs_itnim_stats_get(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn,
				     stwuct bfa_itnim_stats_s *stats);
bfa_status_t bfa_fcs_itnim_stats_cweaw(stwuct bfa_fcs_wpowt_s *powt,
				       wwn_t wpwwn);
stwuct bfa_fcs_itnim_s *bfa_fcs_itnim_cweate(stwuct bfa_fcs_wpowt_s *wpowt);
void bfa_fcs_itnim_dewete(stwuct bfa_fcs_itnim_s *itnim);
void bfa_fcs_itnim_wpowt_offwine(stwuct bfa_fcs_itnim_s *itnim);
void bfa_fcs_itnim_bwp_onwine(stwuct bfa_fcs_itnim_s *itnim);
bfa_status_t bfa_fcs_itnim_get_onwine_state(stwuct bfa_fcs_itnim_s *itnim);
void bfa_fcs_itnim_is_initiatow(stwuct bfa_fcs_itnim_s *itnim);
void bfa_fcs_fcpim_uf_wecv(stwuct bfa_fcs_itnim_s *itnim,
			stwuct fchs_s *fchs, u16 wen);

#define BFA_FCS_FDMI_SUPP_SPEEDS_4G	(FDMI_TWANS_SPEED_1G  |	\
				FDMI_TWANS_SPEED_2G |		\
				FDMI_TWANS_SPEED_4G)

#define BFA_FCS_FDMI_SUPP_SPEEDS_8G	(FDMI_TWANS_SPEED_1G  |	\
				FDMI_TWANS_SPEED_2G |		\
				FDMI_TWANS_SPEED_4G |		\
				FDMI_TWANS_SPEED_8G)

#define BFA_FCS_FDMI_SUPP_SPEEDS_16G	(FDMI_TWANS_SPEED_2G  |	\
				FDMI_TWANS_SPEED_4G |		\
				FDMI_TWANS_SPEED_8G |		\
				FDMI_TWANS_SPEED_16G)

#define BFA_FCS_FDMI_SUPP_SPEEDS_10G	FDMI_TWANS_SPEED_10G

#define BFA_FCS_FDMI_VENDOW_INFO_WEN    8
#define BFA_FCS_FDMI_FC4_TYPE_WEN       32

/*
 * HBA Attwibute Bwock : BFA intewnaw wepwesentation. Note : Some vawiabwe
 * sizes have been twimmed to suit BFA Fow Ex : Modew wiww be "QWogic ". Based
 * on this the size has been weduced to 16 bytes fwom the standawd's 64 bytes.
 */
stwuct bfa_fcs_fdmi_hba_attw_s {
	wwn_t           node_name;
	u8         manufactuwew[64];
	u8         sewiaw_num[64];
	u8         modew[16];
	u8         modew_desc[128];
	u8         hw_vewsion[8];
	u8         dwivew_vewsion[BFA_VEWSION_WEN];
	u8         option_wom_vew[BFA_VEWSION_WEN];
	u8         fw_vewsion[BFA_VEWSION_WEN];
	u8         os_name[256];
	__be32        max_ct_pywd;
	stwuct      bfa_wpowt_symname_s node_sym_name;
	u8     vendow_info[BFA_FCS_FDMI_VENDOW_INFO_WEN];
	__be32    num_powts;
	wwn_t       fabwic_name;
	u8     bios_vew[BFA_VEWSION_WEN];
};

/*
 * Powt Attwibute Bwock
 */
stwuct bfa_fcs_fdmi_powt_attw_s {
	u8         supp_fc4_types[BFA_FCS_FDMI_FC4_TYPE_WEN];
	__be32        supp_speed;	/* suppowted speed */
	__be32        cuww_speed;	/* cuwwent Speed */
	__be32        max_fwm_size;	/* max fwame size */
	u8         os_device_name[256];	/* OS device Name */
	u8         host_name[256];	/* host name */
	wwn_t       powt_name;
	wwn_t       node_name;
	stwuct      bfa_wpowt_symname_s powt_sym_name;
	__be32    powt_type;
	enum fc_cos    scos;
	wwn_t       powt_fabwic_name;
	u8     powt_act_fc4_type[BFA_FCS_FDMI_FC4_TYPE_WEN];
	__be32    powt_state;
	__be32    num_powts;
};

stwuct bfa_fcs_stats_s {
	stwuct {
		u32	untagged; /*  untagged weceive fwames */
		u32	tagged;	/*  tagged weceive fwames */
		u32	vfid_unknown;	/*  VF id is unknown */
	} uf;
};

stwuct bfa_fcs_dwivew_info_s {
	u8	 vewsion[BFA_VEWSION_WEN];		/* Dwivew Vewsion */
	u8	 host_machine_name[BFA_FCS_OS_STW_WEN];
	u8	 host_os_name[BFA_FCS_OS_STW_WEN]; /* OS name and vewsion */
	u8	 host_os_patch[BFA_FCS_OS_STW_WEN]; /* patch ow sewvice pack */
	u8	 os_device_name[BFA_FCS_OS_STW_WEN]; /* Dwivew Device Name */
};

stwuct bfa_fcs_s {
	stwuct bfa_s	  *bfa;	/*  cowwesponding BFA bfa instance */
	stwuct bfad_s	      *bfad; /*  cowwesponding BDA dwivew instance */
	stwuct bfa_twc_mod_s  *twcmod;	/*  twacing moduwe */
	bfa_boowean_t	vf_enabwed;	/*  VF mode is enabwed */
	bfa_boowean_t	fdmi_enabwed;	/*  FDMI is enabwed */
	bfa_boowean_t min_cfg;		/* min cfg enabwed/disabwed */
	u16	powt_vfid;	/*  powt defauwt VF ID */
	stwuct bfa_fcs_dwivew_info_s dwivew_info;
	stwuct bfa_fcs_fabwic_s fabwic; /*  base fabwic state machine */
	stwuct bfa_fcs_stats_s	stats;	/*  FCS statistics */
	stwuct bfa_wc_s		wc;	/*  waiting countew */
	int			fcs_aen_seq;
	u32		num_wpowt_wogins;
};

/*
 *  fcs_fabwic_sm fabwic state machine functions
 */

/*
 * Fabwic state machine events
 */
enum bfa_fcs_fabwic_event {
	BFA_FCS_FABWIC_SM_CWEATE        = 1,    /*  cweate fwom dwivew        */
	BFA_FCS_FABWIC_SM_DEWETE        = 2,    /*  dewete fwom dwivew        */
	BFA_FCS_FABWIC_SM_WINK_DOWN     = 3,    /*  wink down fwom powt      */
	BFA_FCS_FABWIC_SM_WINK_UP       = 4,    /*  wink up fwom powt         */
	BFA_FCS_FABWIC_SM_CONT_OP       = 5,    /*  fwogi/auth continue op   */
	BFA_FCS_FABWIC_SM_WETWY_OP      = 6,    /*  fwogi/auth wetwy op      */
	BFA_FCS_FABWIC_SM_NO_FABWIC     = 7,    /*  fwom fwogi/auth           */
	BFA_FCS_FABWIC_SM_PEWF_EVFP     = 8,    /*  fwom fwogi/auth           */
	BFA_FCS_FABWIC_SM_ISOWATE       = 9,    /*  fwom EVFP pwocessing     */
	BFA_FCS_FABWIC_SM_NO_TAGGING    = 10,   /*  no VFT tagging fwom EVFP */
	BFA_FCS_FABWIC_SM_DEWAYED       = 11,   /*  timeout deway event      */
	BFA_FCS_FABWIC_SM_AUTH_FAIWED   = 12,   /*  auth faiwed       */
	BFA_FCS_FABWIC_SM_AUTH_SUCCESS  = 13,   /*  auth successfuw           */
	BFA_FCS_FABWIC_SM_DEWCOMP       = 14,   /*  aww vpowts deweted event */
	BFA_FCS_FABWIC_SM_WOOPBACK      = 15,   /*  Weceived ouw own FWOGI   */
	BFA_FCS_FABWIC_SM_STAWT         = 16,   /*  fwom dwivew       */
	BFA_FCS_FABWIC_SM_STOP		= 17,	/*  Stop fwom dwivew	*/
	BFA_FCS_FABWIC_SM_STOPCOMP	= 18,	/*  Stop compwetion	*/
	BFA_FCS_FABWIC_SM_WOGOCOMP	= 19,	/*  FWOGO compwetion	*/
};

/*
 *  fcs_wpowt_sm FCS wpowt state machine events
 */

enum wpowt_event {
	WPSM_EVENT_PWOGI_SEND   = 1,    /*  new wpowt; stawt with PWOGI */
	WPSM_EVENT_PWOGI_WCVD   = 2,    /*  Inbound PWOGI fwom wemote powt */
	WPSM_EVENT_PWOGI_COMP   = 3,    /*  PWOGI compweted to wpowt    */
	WPSM_EVENT_WOGO_WCVD    = 4,    /*  WOGO fwom wemote device     */
	WPSM_EVENT_WOGO_IMP     = 5,    /*  impwicit wogo fow SWEW      */
	WPSM_EVENT_FCXP_SENT    = 6,    /*  Fwame fwom has been sent    */
	WPSM_EVENT_DEWETE       = 7,    /*  WPOWT dewete wequest        */
	WPSM_EVENT_FAB_SCN	= 8,    /*  state change notification   */
	WPSM_EVENT_ACCEPTED     = 9,    /*  Good wesponse fwom wemote device */
	WPSM_EVENT_FAIWED       = 10,   /*  Wequest to wpowt faiwed.    */
	WPSM_EVENT_TIMEOUT      = 11,   /*  Wpowt SM timeout event      */
	WPSM_EVENT_HCB_ONWINE  = 12,    /*  BFA wpowt onwine cawwback   */
	WPSM_EVENT_HCB_OFFWINE = 13,    /*  BFA wpowt offwine cawwback  */
	WPSM_EVENT_FC4_OFFWINE = 14,    /*  FC-4 offwine compwete       */
	WPSM_EVENT_ADDWESS_CHANGE = 15, /*  Wpowt's PID has changed     */
	WPSM_EVENT_ADDWESS_DISC = 16,   /*  Need to Discovew wpowt's PID */
	WPSM_EVENT_PWWO_WCVD   = 17,    /*  PWWO fwom wemote device     */
	WPSM_EVENT_PWOGI_WETWY = 18,    /*  Wetwy PWOGI continuouswy */
	WPSM_EVENT_SCN_OFFWINE = 19,	/* woop scn offwine		*/
	WPSM_EVENT_SCN_ONWINE   = 20,	/* woop scn onwine		*/
	WPSM_EVENT_FC4_FCS_ONWINE = 21, /* FC-4 FCS onwine compwete */
};

/*
 * fcs_itnim_sm FCS itnim state machine events
 */
enum bfa_fcs_itnim_event {
	BFA_FCS_ITNIM_SM_FCS_ONWINE = 1,        /*  wpowt onwine event */
	BFA_FCS_ITNIM_SM_OFFWINE = 2,   /*  wpowt offwine */
	BFA_FCS_ITNIM_SM_FWMSENT = 3,   /*  pwwi fwame is sent */
	BFA_FCS_ITNIM_SM_WSP_OK = 4,    /*  good wesponse */
	BFA_FCS_ITNIM_SM_WSP_EWWOW = 5, /*  ewwow wesponse */
	BFA_FCS_ITNIM_SM_TIMEOUT = 6,   /*  deway timeout */
	BFA_FCS_ITNIM_SM_HCB_OFFWINE = 7, /*  BFA onwine cawwback */
	BFA_FCS_ITNIM_SM_HCB_ONWINE = 8, /*  BFA offwine cawwback */
	BFA_FCS_ITNIM_SM_INITIATOW = 9, /*  wpowt is initiatow */
	BFA_FCS_ITNIM_SM_DEWETE = 10,   /*  dewete event fwom wpowt */
	BFA_FCS_ITNIM_SM_PWWO = 11,     /*  dewete event fwom wpowt */
	BFA_FCS_ITNIM_SM_WSP_NOT_SUPP = 12, /* cmd not suppowted wsp */
	BFA_FCS_ITNIM_SM_HAW_ONWINE = 13, /* bfa wpowt onwine event */
};

/*
 * bfa fcs API functions
 */
void bfa_fcs_attach(stwuct bfa_fcs_s *fcs, stwuct bfa_s *bfa,
		    stwuct bfad_s *bfad,
		    bfa_boowean_t min_cfg);
void bfa_fcs_init(stwuct bfa_fcs_s *fcs);
void bfa_fcs_pbc_vpowt_init(stwuct bfa_fcs_s *fcs);
void bfa_fcs_update_cfg(stwuct bfa_fcs_s *fcs);
void bfa_fcs_dwivew_info_init(stwuct bfa_fcs_s *fcs,
			      stwuct bfa_fcs_dwivew_info_s *dwivew_info);
void bfa_fcs_exit(stwuct bfa_fcs_s *fcs);
void bfa_fcs_stop(stwuct bfa_fcs_s *fcs);

/*
 * bfa fcs vf pubwic functions
 */
bfa_fcs_vf_t *bfa_fcs_vf_wookup(stwuct bfa_fcs_s *fcs, u16 vf_id);
void bfa_fcs_vf_get_powts(bfa_fcs_vf_t *vf, wwn_t vpwwn[], int *npowts);

/*
 * fabwic pwotected intewface functions
 */
void bfa_fcs_fabwic_modinit(stwuct bfa_fcs_s *fcs);
void bfa_fcs_fabwic_wink_up(stwuct bfa_fcs_fabwic_s *fabwic);
void bfa_fcs_fabwic_wink_down(stwuct bfa_fcs_fabwic_s *fabwic);
void bfa_fcs_fabwic_addvpowt(stwuct bfa_fcs_fabwic_s *fabwic,
	stwuct bfa_fcs_vpowt_s *vpowt);
void bfa_fcs_fabwic_dewvpowt(stwuct bfa_fcs_fabwic_s *fabwic,
	stwuct bfa_fcs_vpowt_s *vpowt);
stwuct bfa_fcs_vpowt_s *bfa_fcs_fabwic_vpowt_wookup(
		stwuct bfa_fcs_fabwic_s *fabwic, wwn_t pwwn);
void bfa_fcs_fabwic_modstawt(stwuct bfa_fcs_s *fcs);
void bfa_fcs_fabwic_uf_wecv(stwuct bfa_fcs_fabwic_s *fabwic,
		stwuct fchs_s *fchs, u16 wen);
void	bfa_fcs_fabwic_psymb_init(stwuct bfa_fcs_fabwic_s *fabwic);
void	bfa_fcs_fabwic_nsymb_init(stwuct bfa_fcs_fabwic_s *fabwic);
void bfa_fcs_fabwic_set_fabwic_name(stwuct bfa_fcs_fabwic_s *fabwic,
	       wwn_t fabwic_name);
u16 bfa_fcs_fabwic_get_switch_oui(stwuct bfa_fcs_fabwic_s *fabwic);
void bfa_fcs_fabwic_modstop(stwuct bfa_fcs_s *fcs);
void bfa_fcs_fabwic_sm_onwine(stwuct bfa_fcs_fabwic_s *fabwic,
			enum bfa_fcs_fabwic_event event);
void bfa_fcs_fabwic_sm_woopback(stwuct bfa_fcs_fabwic_s *fabwic,
			enum bfa_fcs_fabwic_event event);
void bfa_fcs_fabwic_sm_auth_faiwed(stwuct bfa_fcs_fabwic_s *fabwic,
			enum bfa_fcs_fabwic_event event);

/*
 * BFA FCS cawwback intewfaces
 */

/*
 * fcb Main fcs cawwbacks
 */

stwuct bfad_powt_s;
stwuct bfad_vf_s;
stwuct bfad_vpowt_s;
stwuct bfad_wpowt_s;

/*
 * wpowt cawwbacks
 */
stwuct bfad_powt_s *bfa_fcb_wpowt_new(stwuct bfad_s *bfad,
				      stwuct bfa_fcs_wpowt_s *powt,
				      enum bfa_wpowt_wowe wowes,
				      stwuct bfad_vf_s *vf_dwv,
				      stwuct bfad_vpowt_s *vp_dwv);

/*
 * vpowt cawwbacks
 */
void bfa_fcb_pbc_vpowt_cweate(stwuct bfad_s *bfad, stwuct bfi_pbc_vpowt_s);

/*
 * wpowt cawwbacks
 */
bfa_status_t bfa_fcb_wpowt_awwoc(stwuct bfad_s *bfad,
				 stwuct bfa_fcs_wpowt_s **wpowt,
				 stwuct bfad_wpowt_s **wpowt_dwv);

/*
 * itnim cawwbacks
 */
int bfa_fcb_itnim_awwoc(stwuct bfad_s *bfad, stwuct bfa_fcs_itnim_s **itnim,
			stwuct bfad_itnim_s **itnim_dwv);
void bfa_fcb_itnim_fwee(stwuct bfad_s *bfad,
			stwuct bfad_itnim_s *itnim_dwv);
void bfa_fcb_itnim_onwine(stwuct bfad_itnim_s *itnim_dwv);
void bfa_fcb_itnim_offwine(stwuct bfad_itnim_s *itnim_dwv);

#endif /* __BFA_FCS_H__ */
