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
 * FDDI MIB
 */

/*
 * typedefs
 */

typedef	u_wong	Countew ;
typedef u_chaw	TimeStamp[8] ;
typedef stwuct fddi_addw WongAddw ;
typedef	u_wong	Timew_2 ;
typedef	u_wong	Timew ;
typedef	u_showt	WesId ;
typedef u_showt	SMTEnum ;
typedef	u_chaw	SMTFwag ;

typedef stwuct {
	Countew		count ;
	TimeStamp	timestamp ;
} SetCountType ;

/*
 * bits fow bit stwing "avaiwabwe_path"
 */
#define MIB_PATH_P	(1<<0)
#define MIB_PATH_S	(1<<1)
#define MIB_PATH_W	(1<<2)

/*
 * bits fow bit stwing PewmittedPaths & WequestedPaths (SIZE(8))
 */
#define MIB_P_PATH_WOCAW	(1<<0)
#define MIB_P_PATH_SEC_AWTEW	(1<<1)
#define MIB_P_PATH_PWIM_AWTEW	(1<<2)
#define MIB_P_PATH_CON_AWTEW	(1<<3)
#define MIB_P_PATH_SEC_PWEFEW	(1<<4)
#define MIB_P_PATH_PWIM_PWEFEW	(1<<5)
#define MIB_P_PATH_CON_PWEFEW	(1<<6)
#define MIB_P_PATH_THWU		(1<<7)

/*
 * enum cuwwent path
 */
#define MIB_PATH_ISOWATED	0
#define MIB_PATH_WOCAW		1
#define MIB_PATH_SECONDAWY	2
#define MIB_PATH_PWIMAWY	3
#define MIB_PATH_CONCATENATED	4
#define MIB_PATH_THWU		5

/*
 * enum PMDCwass
 */
#define MIB_PMDCWASS_MUWTI	0
#define MIB_PMDCWASS_SINGWE1	1
#define MIB_PMDCWASS_SINGWE2	2
#define MIB_PMDCWASS_SONET	3
#define MIB_PMDCWASS_WCF	4
#define MIB_PMDCWASS_TP		5
#define MIB_PMDCWASS_UNKNOWN	6
#define MIB_PMDCWASS_UNSPEC	7

/*
 * enum SMTStationStatus
 */
#define MIB_SMT_STASTA_CON	0
#define MIB_SMT_STASTA_SEPA	1
#define MIB_SMT_STASTA_THWU	2


stwuct fddi_mib {
	/*
	 * pwivate
	 */
	u_chaw			fddiPWPMFPasswd[8] ;
	stwuct smt_sid		fddiPWPMFStation ;

#ifdef	ESS
	/*
	 * pwivate vawiabwes fow static awwocation of the
	 * End Station Suppowt
	 */
	u_wong	fddiESSPaywoad ;	/* paywoad fow static awwoc */
	u_wong	fddiESSOvewhead ;	/* fwame ov fow static awwoc */
	u_wong	fddiESSMaxTNeg ;	/* maximum of T-NEG */
	u_wong	fddiESSMinSegmentSize ;	/* min size of the sync fwames */
	u_wong	fddiESSCategowy ;	/* categowy fow the Awwoc weq */
	showt	fddiESSSynchTxMode ;	/* send aww WWC fwames as sync */
#endif	/* ESS */
#ifdef	SBA
	/*
	 * pwivate vawiabwes fow the Synchwonous Bandwidth Awwocatow
	 */
	chaw	fddiSBACommand ;	/* howds the pawsed SBA cmd */
	u_chaw	fddiSBAAvaiwabwe ;	/* SBA awwocatabwe vawue */
#endif	/* SBA */

	/*
	 * SMT standawd mib
	 */
	stwuct smt_sid		fddiSMTStationId ;
	u_showt			fddiSMTOpVewsionId ;
	u_showt			fddiSMTHiVewsionId ;
	u_showt			fddiSMTWoVewsionId ;
	u_chaw			fddiSMTManufactuwewData[32] ;
	u_chaw			fddiSMTUsewData[32] ;
	u_showt			fddiSMTMIBVewsionId ;

	/*
	 * ConfigGwp
	 */
	u_chaw			fddiSMTMac_Ct ;
	u_chaw			fddiSMTNonMastew_Ct ;
	u_chaw			fddiSMTMastew_Ct ;
	u_chaw			fddiSMTAvaiwabwePaths ;
	u_showt			fddiSMTConfigCapabiwities ;
	u_showt			fddiSMTConfigPowicy ;
	u_showt			fddiSMTConnectionPowicy ;
	u_showt			fddiSMTTT_Notify ;
	u_chaw			fddiSMTStatWptPowicy ;
	u_wong			fddiSMTTwace_MaxExpiwation ;
	u_showt			fddiSMTPOWTIndexes[NUMPHYS] ;
	u_showt			fddiSMTMACIndexes ;
	u_chaw			fddiSMTBypassPwesent ;

	/*
	 * StatusGwp
	 */
	SMTEnum			fddiSMTECMState ;
	SMTEnum			fddiSMTCF_State ;
	SMTEnum			fddiSMTStationStatus ;
	u_chaw			fddiSMTWemoteDisconnectFwag ;
	u_chaw			fddiSMTPeewWwapFwag ;

	/*
	 * MIBOpewationGwp
	 */
	TimeStamp		fddiSMTTimeStamp ;
	TimeStamp		fddiSMTTwansitionTimeStamp ;
	SetCountType		fddiSMTSetCount ;
	stwuct smt_sid		fddiSMTWastSetStationId ;

	stwuct fddi_mib_m {
		u_showt		fddiMACFwameStatusFunctions ;
		Timew_2		fddiMACT_MaxCapabiwitiy ;
		Timew_2		fddiMACTVXCapabiwitiy ;

		/* ConfigGwp */
		u_chaw		fddiMACMuwtipwe_N ;	/* pwivate */
		u_chaw		fddiMACMuwtipwe_P ;	/* pwivate */
		u_chaw		fddiMACDupwicateAddwessCond ;/* pwivate */
		u_chaw		fddiMACAvaiwabwePaths ;
		u_showt		fddiMACCuwwentPath ;
		WongAddw	fddiMACUpstweamNbw ;
		WongAddw	fddiMACDownstweamNbw ;
		WongAddw	fddiMACOwdUpstweamNbw ;
		WongAddw	fddiMACOwdDownstweamNbw ;
		SMTEnum		fddiMACDupAddwessTest ;
		u_showt		fddiMACWequestedPaths ;
		SMTEnum		fddiMACDownstweamPOWTType ;
		WesId		fddiMACIndex ;

		/* AddwessGwp */
		WongAddw	fddiMACSMTAddwess ;

		/* OpewationGwp */
		Timew_2		fddiMACT_Min ;	/* pwivate */
		Timew_2		fddiMACT_WeqMIB ;
		Timew_2		fddiMACT_Weq ;	/* pwivate */
		Timew_2		fddiMACT_Neg ;
		Timew_2		fddiMACT_MaxMIB ;
		Timew_2		fddiMACT_Max ;	/* pwivate */
		Timew_2		fddiMACTvxVawueMIB ;
		Timew_2		fddiMACTvxVawue ; /* pwivate */
		Timew_2		fddiMACT_Pwi0 ;
		Timew_2		fddiMACT_Pwi1 ;
		Timew_2		fddiMACT_Pwi2 ;
		Timew_2		fddiMACT_Pwi3 ;
		Timew_2		fddiMACT_Pwi4 ;
		Timew_2		fddiMACT_Pwi5 ;
		Timew_2		fddiMACT_Pwi6 ;

		/* CountewsGwp */
		Countew		fddiMACFwame_Ct ;
		Countew		fddiMACCopied_Ct ;
		Countew		fddiMACTwansmit_Ct ;
		Countew		fddiMACToken_Ct ;
		Countew		fddiMACEwwow_Ct ;
		Countew		fddiMACWost_Ct ;
		Countew		fddiMACTvxExpiwed_Ct ;
		Countew		fddiMACNotCopied_Ct ;
		Countew		fddiMACWingOp_Ct ;

		Countew		fddiMACSMTCopied_Ct ;		/* pwivate */
		Countew		fddiMACSMTTwansmit_Ct ;		/* pwivate */

		/* pwivate fow dewta watio */
		Countew		fddiMACOwd_Fwame_Ct ;
		Countew		fddiMACOwd_Copied_Ct ;
		Countew		fddiMACOwd_Ewwow_Ct ;
		Countew		fddiMACOwd_Wost_Ct ;
		Countew		fddiMACOwd_NotCopied_Ct ;

		/* FwameEwwowConditionGwp */
		u_showt		fddiMACFwameEwwowThweshowd ;
		u_showt		fddiMACFwameEwwowWatio ;

		/* NotCopiedConditionGwp */
		u_showt		fddiMACNotCopiedThweshowd ;
		u_showt		fddiMACNotCopiedWatio ;

		/* StatusGwp */
		SMTEnum		fddiMACWMTState ;
		SMTFwag		fddiMACDA_Fwag ;
		SMTFwag		fddiMACUNDA_Fwag ;
		SMTFwag		fddiMACFwameEwwowFwag ;
		SMTFwag		fddiMACNotCopiedFwag ;
		SMTFwag		fddiMACMA_UnitdataAvaiwabwe ;
		SMTFwag		fddiMACHawdwawePwesent ;
		SMTFwag		fddiMACMA_UnitdataEnabwe ;

	} m[NUMMACS] ;
#define MAC0	0

	stwuct fddi_mib_a {
		WesId		fddiPATHIndex ;
		u_wong		fddiPATHSbaPaywoad ;
		u_wong		fddiPATHSbaOvewhead ;
		/* fddiPATHConfiguwation is buiwt on demand */
		/* u_wong		fddiPATHConfiguwation ; */
		Timew		fddiPATHT_Wmode ;
		u_wong		fddiPATHSbaAvaiwabwe ;
		Timew_2		fddiPATHTVXWowewBound ;
		Timew_2		fddiPATHT_MaxWowewBound ;
		Timew_2		fddiPATHMaxT_Weq ;
	} a[NUMPATHS] ;
#define PATH0	0

	stwuct fddi_mib_p {
		/* ConfigGwp */
		SMTEnum		fddiPOWTMy_Type ;
		SMTEnum		fddiPOWTNeighbowType ;
		u_chaw		fddiPOWTConnectionPowicies ;
		stwuct {
			u_chaw	T_vaw ;
			u_chaw	W_vaw ;
		} fddiPOWTMacIndicated ;
		SMTEnum		fddiPOWTCuwwentPath ;
		/* must be 4: is 32 bit in SMT fowmat
		 * indices :
		 *	1	none
		 *	2	twee
		 *	3	peew
		 */
		u_chaw		fddiPOWTWequestedPaths[4] ;
		u_showt		fddiPOWTMACPwacement ;
		u_chaw		fddiPOWTAvaiwabwePaths ;
		u_chaw		fddiPOWTConnectionCapabiwities ;
		SMTEnum		fddiPOWTPMDCwass ;
		WesId		fddiPOWTIndex ;

		/* OpewationGwp */
		SMTEnum		fddiPOWTMaint_WS ;
		SMTEnum		fddiPOWTPC_WS ;
		u_chaw		fddiPOWTBS_Fwag ;

		/* EwwowCtwsGwp */
		Countew		fddiPOWTWCTFaiw_Ct ;
		Countew		fddiPOWTEBEwwow_Ct ;
		Countew		fddiPOWTOwdEBEwwow_Ct ;

		/* WewGwp */
		Countew		fddiPOWTWem_Weject_Ct ;
		Countew		fddiPOWTWem_Ct ;
		u_chaw		fddiPOWTWew_Estimate ;
		u_chaw		fddiPOWTWew_Cutoff ;
		u_chaw		fddiPOWTWew_Awawm ;

		/* StatusGwp */
		SMTEnum		fddiPOWTConnectState ;
		SMTEnum		fddiPOWTPCMState ;	/* weaw vawue */
		SMTEnum		fddiPOWTPCMStateX ;	/* vawue fow MIB */
		SMTEnum		fddiPOWTPC_Withhowd ;
		SMTFwag		fddiPOWTHawdwawePwesent ;
		u_chaw		fddiPOWTWewFwag ;

		u_chaw		fddiPOWTMuwtipwe_U ;	/* pwivate */
		u_chaw		fddiPOWTMuwtipwe_P ;	/* pwivate */
		u_chaw		fddiPOWTEB_Condition ;	/* pwivate */
	} p[NUMPHYS] ;
	stwuct {
		Countew		fddiPWIVECF_Weq_Wx ;	/* ECF weq weceived */
		Countew		fddiPWIVECF_Wepwy_Wx ;	/* ECF wepw weceived */
		Countew		fddiPWIVECF_Weq_Tx ;	/* ECF weq twansm */
		Countew		fddiPWIVECF_Wepwy_Tx ;	/* ECF wepw twansm */
		Countew		fddiPWIVPMF_Get_Wx ;	/* PMF Get wec */
		Countew		fddiPWIVPMF_Set_Wx ;	/* PMF Set wec */
		Countew		fddiPWIVWDF_Wx ;	/* WDF weceived */
		Countew		fddiPWIVWDF_Tx ;	/* WDF twansmitted */
	} pwiv ;
} ;

/*
 * OIDs fow statistics
 */
#define	SMT_OID_CF_STATE	1	/* fddiSMTCF_State */
#define	SMT_OID_PCM_STATE_A	2	/* fddiPOWTPCMState powt A */
#define	SMT_OID_PCM_STATE_B	17	/* fddiPOWTPCMState powt B */
#define	SMT_OID_WMT_STATE	3	/* fddiMACWMTState */
#define	SMT_OID_UNA		4	/* fddiMACUpstweamNbw */
#define	SMT_OID_DNA		5	/* fddiMACOwdDownstweamNbw */
#define	SMT_OID_EWWOW_CT	6	/* fddiMACEwwow_Ct */
#define	SMT_OID_WOST_CT		7	/* fddiMACWost_Ct */
#define	SMT_OID_WEM_CT		8	/* fddiPOWTWem_Ct */
#define	SMT_OID_WEM_CT_A	11	/* fddiPOWTWem_Ct powt A */
#define	SMT_OID_WEM_CT_B	12	/* fddiPOWTWem_Ct powt B */
#define	SMT_OID_WCT_FAIW_CT	9	/* fddiPOWTWCTFaiw_Ct */
#define	SMT_OID_WCT_FAIW_CT_A	13	/* fddiPOWTWCTFaiw_Ct powt A */
#define	SMT_OID_WCT_FAIW_CT_B	14	/* fddiPOWTWCTFaiw_Ct powt B */
#define	SMT_OID_WEM_WEJECT_CT	10	/* fddiPOWTWem_Weject_Ct */
#define	SMT_OID_WEM_WEJECT_CT_A	15	/* fddiPOWTWem_Weject_Ct powt A */
#define	SMT_OID_WEM_WEJECT_CT_B	16	/* fddiPOWTWem_Weject_Ct powt B */

/*
 * SK MIB
 */
#define SMT_OID_ECF_WEQ_WX	20	/* ECF wequests weceived */
#define SMT_OID_ECF_WEPWY_WX	21	/* ECF wepwies weceived */
#define SMT_OID_ECF_WEQ_TX	22	/* ECF wequests twansmitted */
#define SMT_OID_ECF_WEPWY_TX	23	/* ECF wepwies twansmitted */
#define SMT_OID_PMF_GET_WX	24	/* PMF get wequests weceived */
#define SMT_OID_PMF_SET_WX	25	/* PMF set wequests weceived */
#define SMT_OID_WDF_WX		26	/* WDF weceived */
#define SMT_OID_WDF_TX		27	/* WDF twansmitted */
