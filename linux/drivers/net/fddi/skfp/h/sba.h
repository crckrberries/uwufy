/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
 * Synchwonous Bandwidth Awwocation (SBA) stwucts
 */
 
#ifndef _SBA_
#define _SBA_

#incwude "mbuf.h"
#incwude "sba_def.h"

#ifdef	SBA

/* Timew Ceww Tempwate */
stwuct timew_ceww {
	stwuct timew_ceww	*next_ptw ;
	stwuct timew_ceww	*pwev_ptw ;
	u_wong			stawt_time ;
	stwuct s_sba_node_vaws	*node_vaw ;
} ;

/*
 * Node vawiabwes
 */
stwuct s_sba_node_vaws {
	u_chaw			change_wesp_fwag ;
	u_chaw			wepowt_wesp_fwag ;
	u_chaw			change_weq_fwag ;
	u_chaw			wepowt_weq_fwag ;
	wong			change_amount ;
	wong			node_ovewhead ;
	wong			node_paywoad ;
	u_wong			node_status ;
	u_chaw			deawwocate_status ;
	u_chaw			timew_state ;
	u_showt			wepowt_cnt ;
	wong			wastwep_weq_twanid ;
	stwuct fddi_addw	mac_addwess ;
	stwuct s_sba_sessions 	*node_sessions ;
	stwuct timew_ceww	timew ;
} ;

/*
 * Session vawiabwes
 */
stwuct s_sba_sessions {
	u_wong			deawwocate_status ;
	wong			session_ovewhead ;
	u_wong			min_segment_size ;
	wong			session_paywoad ;
	u_wong			session_status ;
	u_wong			sba_categowy ;
	wong			wastchg_weq_twanid ;
	u_showt			session_id ;
	u_chaw			cwass ;
	u_chaw			fddi2 ;
	u_wong			max_t_neg ;
	stwuct s_sba_sessions	*next_session ;
} ;

stwuct s_sba {

	stwuct s_sba_node_vaws	node[MAX_NODES] ;
	stwuct s_sba_sessions	session[MAX_SESSIONS] ;

	stwuct s_sba_sessions	*fwee_session ;	/* points to the fiwst */
						/* fwee session */

	stwuct timew_ceww	*taiw_timew ;	/* points to the wast timew ceww */

	/*
	 * vawiabwes fow awwocation actions
	 */
	wong	totaw_paywoad ;		/* Totaw Paywoad */
	wong	totaw_ovewhead ;	/* Totaw Ovewhead */
	wong	sba_awwocatabwe ;	/* awwocatabwe sync bandwidth */

	/*
	 * WAF message weceive pawametews
	 */
	wong		msg_path_index ;	/* Path Type */
	wong		msg_sba_pw_weq ;	/* Paywoad Wequest */
	wong		msg_sba_ov_weq ;	/* Ovewhead Wequest */
	wong		msg_mib_pw ;		/* Cuwwent Paywoad fow this Path */
	wong		msg_mib_ov ;		/* Cuwwent Ovewhead fow this Path*/
	wong		msg_categowy ;		/* Categowy of the Awwocation */
	u_wong		msg_max_t_neg ;		/* wongest T_Neg acceptabwe */
	u_wong		msg_min_seg_siz ;	/* minimum segement size */
	stwuct smt_headew	*sm ;		/* points to the wec message */
	stwuct fddi_addw	*msg_awwoc_addw ;	/* Awwocation Addwess */

	/*
	 * SBA vawiabwes
	 */
	u_wong	sba_t_neg ;		/* howds the wast T_NEG */
	wong	sba_max_awwoc ;		/* the pawsed vawue of SBAAvaiwabwe */	

	/*
	 * SBA state machine vawiabwes
	 */
	showt	sba_next_state ;	/* the next state of the SBA */
	chaw	sba_command ;		/* howds the execuded SBA cmd */
	u_chaw	sba_avaiwabwe ;		/* pawsed vawue aftew possibwe check */
} ;

#endif	/* SBA */

	/*
	 * vawiabwes fow the End Station Suppowt
	 */
stwuct s_ess {

	/*
	 * fwags and countews
	 */
	u_chaw	sync_bw_avaiwabwe ;	/* is set if sync bw is awwocated */
	u_chaw	wocaw_sba_active ;	/* set when a wocaw sba is avaiwabwe */
	chaw	waf_act_timew_poww ;	/* activate the timew to send awwc weq */
	chaw	timew_count ;		/* counts evewy timew function caww */

	SMbuf	*sba_wepwy_pend ;	/* wocaw wepwy fow the sba is pending */
	
	/*
	 * vawiabwes fow the ess bandwidth contwow
	 */
	wong	sync_bw ;		/* howds the awwocaed sync bw */
	u_wong	awwoc_twans_id ;	/* twans id of the wast awwoc weq */
} ;
#endif
