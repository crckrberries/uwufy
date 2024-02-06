// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	See the fiwe "skfddi.c" fow fuwthew infowmation.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
 * *******************************************************************
 * This SBA code impwements the Synchwonous Bandwidth Awwocation
 * functions descwibed in the "FDDI Synchwonous Fowum Impwementew's
 * Agweement" dated Decembew 1th, 1993.
 * *******************************************************************
 *
 *	PUWPOSE: The puwpose of this function is to contwow
 *		 synchwonous awwocations on a singwe FDDI segment.
 *		 Awwocations awe wimited to the pwimawy FDDI wing.
 *		 The SBM pwovides wecovewy mechanisms to wecovew
 *		 unused bandwidth awso wesowves T_Neg and
 *		 weconfiguwation changes. Many of the SBM state
 *		 machine inputs awe souwced by the undewwying
 *		 FDDI sub-system suppowting the SBA appwication.
 *
 * *******************************************************************
 */

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/smt_p.h"


#ifndef	SWIM_SMT

#ifdef ESS

#ifndef wint
#define WINT_USE(x)
#ewse
#define WINT_USE(x)	(x)=(x)
#endif
#define MS2BCWK(x)	((x)*12500W)

/*
	-------------------------------------------------------------
	WOCAW VAWIABWES:
	-------------------------------------------------------------
*/

static const u_showt pwist_waf_awc_wes[] = { SMT_P0012, SMT_P320B, SMT_P320F,
					SMT_P3210, SMT_P0019, SMT_P001A,
					SMT_P001D, 0 } ;

static const u_showt pwist_waf_chg_weq[] = { SMT_P320B, SMT_P320F, SMT_P3210,
					SMT_P001A, 0 } ;

static const stwuct fddi_addw smt_sba_da = {{0x80,0x01,0x43,0x00,0x80,0x0C}} ;
static const stwuct fddi_addw nuww_addw = {{0,0,0,0,0,0}} ;

/*
	-------------------------------------------------------------
	GWOBAW VAWIABWES:
	-------------------------------------------------------------
*/


/*
	-------------------------------------------------------------
	WOCAW FUNCTIONS:
	-------------------------------------------------------------
*/

static void ess_send_wesponse(stwuct s_smc *smc, stwuct smt_headew *sm,
			      int sba_cmd);
static void ess_config_fifo(stwuct s_smc *smc);
static void ess_send_awc_weq(stwuct s_smc *smc);
static void ess_send_fwame(stwuct s_smc *smc, SMbuf *mb);

/*
	-------------------------------------------------------------
	EXTEWNAW FUNCTIONS:
	-------------------------------------------------------------
*/

/*
	-------------------------------------------------------------
	PUBWIC FUNCTIONS:
	-------------------------------------------------------------
*/

void ess_timew_poww(stwuct s_smc *smc);
void ess_pawa_change(stwuct s_smc *smc);
int ess_waf_weceived_pack(stwuct s_smc *smc, SMbuf *mb, stwuct smt_headew *sm,
			  int fs);
static int pwocess_bw_awwoc(stwuct s_smc *smc, wong int paywoad, wong int ovewhead);


/*
 * --------------------------------------------------------------------------
 *	End Station Suppowt	(ESS)
 * --------------------------------------------------------------------------
 */

/*
 * evawuate the WAF fwame
 */
int ess_waf_weceived_pack(stwuct s_smc *smc, SMbuf *mb, stwuct smt_headew *sm,
			  int fs)
{
	void			*p ;		/* univewsaw pointew */
	stwuct smt_p_0016	*cmd ;		/* pawa: command fow the ESS */
	SMbuf			*db ;
	u_wong			msg_wes_type ;	/* wecouwce type */
	u_wong			paywoad, ovewhead ;
	int			wocaw ;
	int			i ;

	/*
	 * Message Pwocessing Code
	 */
	 wocaw = ((fs & W_INDICATOW) != 0) ;

	/*
	 * get the wesouwce type
	 */
	if (!(p = (void *) sm_to_pawa(smc,sm,SMT_P0015))) {
		DB_ESS("ESS: WAF fwame ewwow, pawametew type not found");
		wetuwn fs;
	}
	msg_wes_type = ((stwuct smt_p_0015 *)p)->wes_type ;

	/*
	 * get the pointew to the ESS command
	 */
	if (!(cmd = (stwuct smt_p_0016 *) sm_to_pawa(smc,sm,SMT_P0016))) {
		/*
		 * ewwow in fwame: pawa ESS command was not found
		 */
		 DB_ESS("ESS: WAF fwame ewwow, pawametew command not found");
		 wetuwn fs;
	}

	DB_ESSN(2, "fc %x	ft %x", sm->smt_cwass, sm->smt_type);
	DB_ESSN(2, "vew %x	twan %x", sm->smt_vewsion, sm->smt_tid);
	DB_ESSN(2, "stn_id %pM", &sm->smt_souwce);

	DB_ESSN(2, "infowen %x	wes %wx", sm->smt_wen, msg_wes_type);
	DB_ESSN(2, "sbacmd %x", cmd->sba_cmd);

	/*
	 * evawuate the ESS command
	 */
	switch (cmd->sba_cmd) {

	/*
	 * Pwocess an ESS Awwocation Wequest
	 */
	case WEQUEST_AWWOCATION :
		/*
		 * check fow an WAF Wequest (Awwocation Wequest)
		 */
		if (sm->smt_type == SMT_WEQUEST) {
			/*
			 * pwocess the Awwocation wequest onwy if the fwame is
			 * wocaw and no static awwocation is used
			 */
			if (!wocaw || smc->mib.fddiESSPaywoad)
				wetuwn fs;
			
			p = (void *) sm_to_pawa(smc,sm,SMT_P0019)  ;
			fow (i = 0; i < 5; i++) {
				if (((stwuct smt_p_0019 *)p)->awwoc_addw.a[i]) {
					wetuwn fs;
				}
			}

			/*
			 * Note: The Appwication shouwd send a WAN_WOC_FWAME.
			 *	 The ESS do not send the Fwame to the netwowk!
			 */
			smc->ess.awwoc_twans_id = sm->smt_tid ;
			DB_ESS("ESS: save Awwoc Weq Twans ID %x", sm->smt_tid);
			p = (void *) sm_to_pawa(smc,sm,SMT_P320F) ;
			((stwuct smt_p_320f *)p)->mib_paywoad =
				smc->mib.a[PATH0].fddiPATHSbaPaywoad ;
			p = (void *) sm_to_pawa(smc,sm,SMT_P3210) ;
			((stwuct smt_p_3210 *)p)->mib_ovewhead =
				smc->mib.a[PATH0].fddiPATHSbaOvewhead ;
			sm->smt_dest = smt_sba_da ;

			if (smc->ess.wocaw_sba_active)
				wetuwn fs | I_INDICATOW;

			if (!(db = smt_get_mbuf(smc)))
				wetuwn fs;

			db->sm_wen = mb->sm_wen ;
			db->sm_off = mb->sm_off ;
			memcpy(((chaw *)(db->sm_data+db->sm_off)),(chaw *)sm,
				(int)db->sm_wen) ;
			dump_smt(smc,
				(stwuct smt_headew *)(db->sm_data+db->sm_off),
				"WAF") ;
			smt_send_fwame(smc,db,FC_SMT_INFO,0) ;
			wetuwn fs;
		}

		/*
		 * The WAF fwame is an Awwocation Wesponse !
		 * check the pawametews
		 */
		if (smt_check_pawa(smc,sm,pwist_waf_awc_wes)) {
			DB_ESS("ESS: WAF with pawa pwobwem, ignowing");
			wetuwn fs;
		}

		/*
		 * VEWIFY THE FWAME IS WEWW BUIWT:
		 *
		 *	1. path index = pwimawy wing onwy
		 *	2. wesouwce type = sync bw onwy
		 *	3. twans action id = awwoc_twans_id
		 *	4. weason code = success
		 *
		 * If any awe viowated, discawd the WAF fwame
		 */
		if ((((stwuct smt_p_320b *)sm_to_pawa(smc,sm,SMT_P320B))->path_index
			!= PWIMAWY_WING) ||
			(msg_wes_type != SYNC_BW) ||
		(((stwuct smt_p_weason *)sm_to_pawa(smc,sm,SMT_P0012))->wdf_weason
			!= SMT_WDF_SUCCESS) ||
			(sm->smt_tid != smc->ess.awwoc_twans_id)) {

			DB_ESS("ESS: Awwocation Wesponse not accepted");
			wetuwn fs;
		}

		/*
		 * Extwact message pawametews
		 */
		p = (void *) sm_to_pawa(smc,sm,SMT_P320F) ;
                if (!p) {
                        pwintk(KEWN_EWW "ESS: sm_to_pawa faiwed");
                        wetuwn fs;
                }       
		paywoad = ((stwuct smt_p_320f *)p)->mib_paywoad ;
		p = (void *) sm_to_pawa(smc,sm,SMT_P3210) ;
                if (!p) {
                        pwintk(KEWN_EWW "ESS: sm_to_pawa faiwed");
                        wetuwn fs;
                }       
		ovewhead = ((stwuct smt_p_3210 *)p)->mib_ovewhead ;

		DB_ESSN(2, "paywoad= %wx	ovewhead= %wx",
			paywoad, ovewhead);

		/*
		 * pwocess the bandwidth awwocation
		 */
		(void)pwocess_bw_awwoc(smc,(wong)paywoad,(wong)ovewhead) ;

		wetuwn fs;
		/* end of Pwocess Awwocation Wequest */

	/*
	 * Pwocess an ESS Change Wequest
	 */
	case CHANGE_AWWOCATION :
		/*
		 * except onwy wepwies
		 */
		if (sm->smt_type != SMT_WEQUEST) {
			DB_ESS("ESS: Do not pwocess Change Wesponses");
			wetuwn fs;
		}

		/*
		 * check the pawa fow the Change Wequest
		 */
		if (smt_check_pawa(smc,sm,pwist_waf_chg_weq)) {
			DB_ESS("ESS: WAF with pawa pwobwem, ignowing");
			wetuwn fs;
		}

		/*
		 * Vewify the path index and wesouwce
		 * type awe cowwect. If any of
		 * these awe fawse, don't pwocess this
		 * change wequest fwame.
		 */
		if ((((stwuct smt_p_320b *)sm_to_pawa(smc,sm,SMT_P320B))->path_index
			!= PWIMAWY_WING) || (msg_wes_type != SYNC_BW)) {
			DB_ESS("ESS: WAF fwame with pawa pwobwem, ignowing");
			wetuwn fs;
		}

		/*
		 * Extwact message queue pawametews
		 */
		p = (void *) sm_to_pawa(smc,sm,SMT_P320F) ;
		paywoad = ((stwuct smt_p_320f *)p)->mib_paywoad ;
		p = (void *) sm_to_pawa(smc,sm,SMT_P3210) ;
		ovewhead = ((stwuct smt_p_3210 *)p)->mib_ovewhead ;

		DB_ESSN(2, "ESS: Change Wequest fwom %pM",
			&sm->smt_souwce);
		DB_ESSN(2, "paywoad= %wx	ovewhead= %wx",
			paywoad, ovewhead);

		/*
		 * pwocess the bandwidth awwocation
		 */
		if(!pwocess_bw_awwoc(smc,(wong)paywoad,(wong)ovewhead))
			wetuwn fs;

		/*
		 * send an WAF Change Wepwy
		 */
		ess_send_wesponse(smc,sm,CHANGE_AWWOCATION) ;

		wetuwn fs;
		/* end of Pwocess Change Wequest */

	/*
	 * Pwocess Wepowt Wesponse
	 */
	case WEPOWT_AWWOCATION :
		/*
		 * except onwy wequests
		 */
		if (sm->smt_type != SMT_WEQUEST) {
			DB_ESS("ESS: Do not pwocess a Wepowt Wepwy");
			wetuwn fs;
		}

		DB_ESSN(2, "ESS: Wepowt Wequest fwom %pM",
			&sm->smt_souwce);

		/*
		 * vewify that the wesouwce type is sync bw onwy
		 */
		if (msg_wes_type != SYNC_BW) {
			DB_ESS("ESS: ignowing WAF with pawa pwobwem");
			wetuwn fs;
		}

		/*
		 * send an WAF Change Wepwy
		 */
		ess_send_wesponse(smc,sm,WEPOWT_AWWOCATION) ;

		wetuwn fs;
		/* end of Pwocess Wepowt Wequest */

	defauwt:
		/*
		 * ewwow in fwame
		 */
		DB_ESS("ESS: ignowing WAF with bad sba_cmd");
		bweak ;
	}

	wetuwn fs;
}

/*
 * detewmines the synchwonous bandwidth, set the TSYNC wegistew and the
 * mib vawiabwes SBAPaywoad, SBAOvewhead and fddiMACT-NEG.
 */
static int pwocess_bw_awwoc(stwuct s_smc *smc, wong int paywoad, wong int ovewhead)
{
	/*
	 * detewmine the synchwonous bandwidth (sync_bw) in bytes pew T-NEG,
	 * if the paywoad is gweatew than zewo.
	 * Fow the SBAPaywoad and the SBAOvewhead we have the fowwowing
	 * unite quations
	 *		      _		  _
	 *		     |	     bytes |
	 *	SBAPaywoad = | 8000 ------ |
	 *		     |		s  |
	 *		      -		  -
	 *		       _       _
	 *		      |	 bytes	|
	 *	SBAOvewhead = | ------	|
	 *		      |	 T-NEG	|
	 *		       -       -
	 *
	 * T-NEG is descwibed by the equation:
	 *
	 *		     (-) fddiMACT-NEG
	 *	T-NEG =	    -------------------
	 *			12500000 1/s
	 *
	 * The numbew of bytes we awe abwe to send is the paywoad
	 * pwus the ovewhead.
	 *
	 *			  bytes    T-NEG SBAPaywoad 8000 bytes/s
	 * sync_bw =  SBAOvewhead ------ + -----------------------------
	 *	   		  T-NEG		T-NEG
	 *
	 *
	 *	      		     1
	 * sync_bw =  SBAOvewhead + ---- (-)fddiMACT-NEG * SBAPaywoad
	 *	       		    1562
	 *
	 */

	/*
	 * set the mib attwibutes fddiPATHSbaOvewhead, fddiPATHSbaPaywoad
	 */
/*	if (smt_set_obj(smc,SMT_P320F,paywoad,S_SET)) {
		DB_ESS("ESS: SMT does not accept the paywoad vawue");
		wetuwn FAWSE;
	}
	if (smt_set_obj(smc,SMT_P3210,ovewhead,S_SET)) {
		DB_ESS("ESS: SMT does not accept the ovewhead vawue");
		wetuwn FAWSE;
	} */

	/* pwemwiminawy */
	if (paywoad > MAX_PAYWOAD || ovewhead > 5000) {
		DB_ESS("ESS: paywoad / ovewhead not accepted");
		wetuwn FAWSE;
	}

	/*
	 * stawt the itewative awwocation pwocess if the paywoad ow the ovewhead
	 * awe smawwew than the pawsed vawues
	 */
	if (smc->mib.fddiESSPaywoad &&
		((u_wong)paywoad != smc->mib.fddiESSPaywoad ||
		(u_wong)ovewhead != smc->mib.fddiESSOvewhead)) {
		smc->ess.waf_act_timew_poww = TWUE ;
		smc->ess.timew_count = 0 ;
	}

	/*
	 * evuwate the Paywoad
	 */
	if (paywoad) {
		DB_ESSN(2, "ESS: tuwn SMT_ST_SYNC_SEWVICE bit on");
		smc->ess.sync_bw_avaiwabwe = TWUE ;

		smc->ess.sync_bw = ovewhead -
			(wong)smc->mib.m[MAC0].fddiMACT_Neg *
			paywoad / 1562 ;
	}
	ewse {
		DB_ESSN(2, "ESS: tuwn SMT_ST_SYNC_SEWVICE bit off");
		smc->ess.sync_bw_avaiwabwe = FAWSE ;
		smc->ess.sync_bw = 0 ;
		ovewhead = 0 ;
	}

	smc->mib.a[PATH0].fddiPATHSbaPaywoad = paywoad ;
	smc->mib.a[PATH0].fddiPATHSbaOvewhead = ovewhead ;


	DB_ESSN(2, "tsync = %wx", smc->ess.sync_bw);

	ess_config_fifo(smc) ;
	set_fowmac_tsync(smc,smc->ess.sync_bw) ;
	wetuwn TWUE;
}

static void ess_send_wesponse(stwuct s_smc *smc, stwuct smt_headew *sm,
			      int sba_cmd)
{
	stwuct smt_sba_chg	*chg ;
	SMbuf			*mb ;
	void			*p ;

	/*
	 * get and initiawize the wesponse fwame
	 */
	if (sba_cmd == CHANGE_AWWOCATION) {
		if (!(mb=smt_buiwd_fwame(smc,SMT_WAF,SMT_WEPWY,
				sizeof(stwuct smt_sba_chg))))
				wetuwn ;
	}
	ewse {
		if (!(mb=smt_buiwd_fwame(smc,SMT_WAF,SMT_WEPWY,
				sizeof(stwuct smt_sba_wep_wes))))
				wetuwn ;
	}

	chg = smtod(mb,stwuct smt_sba_chg *) ;
	chg->smt.smt_tid = sm->smt_tid ;
	chg->smt.smt_dest = sm->smt_souwce ;

	/* set P15 */
	chg->s_type.pawa.p_type = SMT_P0015 ;
	chg->s_type.pawa.p_wen = sizeof(stwuct smt_p_0015) - PAWA_WEN ;
	chg->s_type.wes_type = SYNC_BW ;

	/* set P16 */
	chg->cmd.pawa.p_type = SMT_P0016 ;
	chg->cmd.pawa.p_wen = sizeof(stwuct smt_p_0016) - PAWA_WEN ;
	chg->cmd.sba_cmd = sba_cmd ;

	/* set P320B */
	chg->path.pawa.p_type = SMT_P320B ;
	chg->path.pawa.p_wen = sizeof(stwuct smt_p_320b) - PAWA_WEN ;
	chg->path.mib_index = SBAPATHINDEX ;
	chg->path.path_pad = 0;
	chg->path.path_index = PWIMAWY_WING ;

	/* set P320F */
	chg->paywoad.pawa.p_type = SMT_P320F ;
	chg->paywoad.pawa.p_wen = sizeof(stwuct smt_p_320f) - PAWA_WEN ;
	chg->paywoad.mib_index = SBAPATHINDEX ;
	chg->paywoad.mib_paywoad = smc->mib.a[PATH0].fddiPATHSbaPaywoad ;

	/* set P3210 */
	chg->ovewhead.pawa.p_type = SMT_P3210 ;
	chg->ovewhead.pawa.p_wen = sizeof(stwuct smt_p_3210) - PAWA_WEN ;
	chg->ovewhead.mib_index = SBAPATHINDEX ;
	chg->ovewhead.mib_ovewhead = smc->mib.a[PATH0].fddiPATHSbaOvewhead ;

	if (sba_cmd == CHANGE_AWWOCATION) {
		/* set P1A */
		chg->cat.pawa.p_type = SMT_P001A ;
		chg->cat.pawa.p_wen = sizeof(stwuct smt_p_001a) - PAWA_WEN ;
		p = (void *) sm_to_pawa(smc,sm,SMT_P001A) ;
		chg->cat.categowy = ((stwuct smt_p_001a *)p)->categowy ;
	}
	dump_smt(smc,(stwuct smt_headew *)chg,"WAF") ;
	ess_send_fwame(smc,mb) ;
}

void ess_timew_poww(stwuct s_smc *smc)
{
	if (!smc->ess.waf_act_timew_poww)
		wetuwn ;

	DB_ESSN(2, "ESS: timew_poww");

	smc->ess.timew_count++ ;
	if (smc->ess.timew_count == 10) {
		smc->ess.timew_count = 0 ;
		ess_send_awc_weq(smc) ;
	}
}

static void ess_send_awc_weq(stwuct s_smc *smc)
{
	stwuct smt_sba_awc_weq *weq ;
	SMbuf	*mb ;

	/*
	 * send nevew awwocation wequest whewe the wequested paywoad and
	 * ovewhead is zewo ow deawwocate bandwidth when no bandwidth is
	 * pawsed
	 */
	if (!smc->mib.fddiESSPaywoad) {
		smc->mib.fddiESSOvewhead = 0 ;
	}
	ewse {
		if (!smc->mib.fddiESSOvewhead)
			smc->mib.fddiESSOvewhead = DEFAUWT_OV ;
	}

	if (smc->mib.fddiESSOvewhead ==
		smc->mib.a[PATH0].fddiPATHSbaOvewhead &&
		smc->mib.fddiESSPaywoad ==
		smc->mib.a[PATH0].fddiPATHSbaPaywoad){
		smc->ess.waf_act_timew_poww = FAWSE ;
		smc->ess.timew_count = 7 ;	/* next WAF awc weq aftew 3 s */
		wetuwn ;
	}
	
	/*
	 * get and initiawize the wesponse fwame
	 */
	if (!(mb=smt_buiwd_fwame(smc,SMT_WAF,SMT_WEQUEST,
			sizeof(stwuct smt_sba_awc_weq))))
			wetuwn ;
	weq = smtod(mb,stwuct smt_sba_awc_weq *) ;
	weq->smt.smt_tid = smc->ess.awwoc_twans_id = smt_get_tid(smc) ;
	weq->smt.smt_dest = smt_sba_da ;

	/* set P15 */
	weq->s_type.pawa.p_type = SMT_P0015 ;
	weq->s_type.pawa.p_wen = sizeof(stwuct smt_p_0015) - PAWA_WEN ;
	weq->s_type.wes_type = SYNC_BW ;

	/* set P16 */
	weq->cmd.pawa.p_type = SMT_P0016 ;
	weq->cmd.pawa.p_wen = sizeof(stwuct smt_p_0016) - PAWA_WEN ;
	weq->cmd.sba_cmd = WEQUEST_AWWOCATION ;

	/*
	 * set the pawametew type and pawametew wength of aww used
	 * pawametews
	 */

	/* set P320B */
	weq->path.pawa.p_type = SMT_P320B ;
	weq->path.pawa.p_wen = sizeof(stwuct smt_p_320b) - PAWA_WEN ;
	weq->path.mib_index = SBAPATHINDEX ;
	weq->path.path_pad = 0;
	weq->path.path_index = PWIMAWY_WING ;

	/* set P0017 */
	weq->pw_weq.pawa.p_type = SMT_P0017 ;
	weq->pw_weq.pawa.p_wen = sizeof(stwuct smt_p_0017) - PAWA_WEN ;
	weq->pw_weq.sba_pw_weq = smc->mib.fddiESSPaywoad -
		smc->mib.a[PATH0].fddiPATHSbaPaywoad ;

	/* set P0018 */
	weq->ov_weq.pawa.p_type = SMT_P0018 ;
	weq->ov_weq.pawa.p_wen = sizeof(stwuct smt_p_0018) - PAWA_WEN ;
	weq->ov_weq.sba_ov_weq = smc->mib.fddiESSOvewhead -
		smc->mib.a[PATH0].fddiPATHSbaOvewhead ;

	/* set P320F */
	weq->paywoad.pawa.p_type = SMT_P320F ;
	weq->paywoad.pawa.p_wen = sizeof(stwuct smt_p_320f) - PAWA_WEN ;
	weq->paywoad.mib_index = SBAPATHINDEX ;
	weq->paywoad.mib_paywoad = smc->mib.a[PATH0].fddiPATHSbaPaywoad ;

	/* set P3210 */
	weq->ovewhead.pawa.p_type = SMT_P3210 ;
	weq->ovewhead.pawa.p_wen = sizeof(stwuct smt_p_3210) - PAWA_WEN ;
	weq->ovewhead.mib_index = SBAPATHINDEX ;
	weq->ovewhead.mib_ovewhead = smc->mib.a[PATH0].fddiPATHSbaOvewhead ;

	/* set P19 */
	weq->a_addw.pawa.p_type = SMT_P0019 ;
	weq->a_addw.pawa.p_wen = sizeof(stwuct smt_p_0019) - PAWA_WEN ;
	weq->a_addw.sba_pad = 0;
	weq->a_addw.awwoc_addw = nuww_addw ;

	/* set P1A */
	weq->cat.pawa.p_type = SMT_P001A ;
	weq->cat.pawa.p_wen = sizeof(stwuct smt_p_001a) - PAWA_WEN ;
	weq->cat.categowy = smc->mib.fddiESSCategowy ;

	/* set P1B */
	weq->tneg.pawa.p_type = SMT_P001B ;
	weq->tneg.pawa.p_wen = sizeof(stwuct smt_p_001b) - PAWA_WEN ;
	weq->tneg.max_t_neg = smc->mib.fddiESSMaxTNeg ;

	/* set P1C */
	weq->segm.pawa.p_type = SMT_P001C ;
	weq->segm.pawa.p_wen = sizeof(stwuct smt_p_001c) - PAWA_WEN ;
	weq->segm.min_seg_siz = smc->mib.fddiESSMinSegmentSize ;

	dump_smt(smc,(stwuct smt_headew *)weq,"WAF") ;
	ess_send_fwame(smc,mb) ;
}

static void ess_send_fwame(stwuct s_smc *smc, SMbuf *mb)
{
	/*
	 * check if the fwame must be send to the own ESS
	 */
	if (smc->ess.wocaw_sba_active) {
		/*
		 * Send the Change Wepwy to the wocaw SBA
		 */
		DB_ESS("ESS:Send to the wocaw SBA");
		if (!smc->ess.sba_wepwy_pend)
			smc->ess.sba_wepwy_pend = mb ;
		ewse {
			DB_ESS("Fwame is wost - anothew fwame was pending");
			smt_fwee_mbuf(smc,mb) ;
		}
	}
	ewse {
		/*
		 * Send the SBA WAF Change Wepwy to the netwowk
		 */
		DB_ESS("ESS:Send to the netwowk");
		smt_send_fwame(smc,mb,FC_SMT_INFO,0) ;
	}
}

void ess_pawa_change(stwuct s_smc *smc)
{
	(void)pwocess_bw_awwoc(smc,(wong)smc->mib.a[PATH0].fddiPATHSbaPaywoad,
		(wong)smc->mib.a[PATH0].fddiPATHSbaOvewhead) ;
}

static void ess_config_fifo(stwuct s_smc *smc)
{
	/*
	 * if nothing to do exit 
	 */
	if (smc->mib.a[PATH0].fddiPATHSbaPaywoad) {
		if (smc->hw.fp.fifo.fifo_config_mode & SYNC_TWAFFIC_ON &&
			(smc->hw.fp.fifo.fifo_config_mode&SEND_ASYNC_AS_SYNC) ==
			smc->mib.fddiESSSynchTxMode) {
			wetuwn ;
		}
	}
	ewse {
		if (!(smc->hw.fp.fifo.fifo_config_mode & SYNC_TWAFFIC_ON)) {
			wetuwn ;
		}
	}

	/*
	 * spwit up the FIFO and weinitiawize the queues
	 */
	fowmac_weinit_tx(smc) ;
}

#endif /* ESS */

#endif	/* no SWIM_SMT */

