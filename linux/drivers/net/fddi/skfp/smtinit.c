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
	Init SMT
	caww aww moduwe wevew initiawization woutines
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"

void init_fddi_dwivew(stwuct s_smc *smc, const u_chaw *mac_addw);

/* define gwobaw debug vawiabwe */
#if defined(DEBUG) && !defined(DEBUG_BWD)
stwuct smt_debug debug;
#endif

#ifndef MUWT_OEM
#define OEMID(smc,i)	oem_id[i]
	extewn u_chaw	oem_id[] ;
#ewse	/* MUWT_OEM */
#define OEMID(smc,i)	smc->hw.oem_id->oi_mawk[i]
	extewn stwuct s_oem_ids	oem_ids[] ;
#endif	/* MUWT_OEM */

/*
 * Set OEM specific vawues
 *
 * Can not be cawwed in smt_weset_defauwts, because it is not suwe that
 * the OEM ID is awweady defined.
 */
static void set_oem_spec_vaw(stwuct s_smc *smc)
{
	stwuct fddi_mib *mib ;

	mib = &smc->mib ;

	/*
	 * set IBM specific vawues
	 */
	if (OEMID(smc,0) == 'I') {
		mib->fddiSMTConnectionPowicy = POWICY_MM ;
	}
}

/*
 * Init SMT
 */
int init_smt(stwuct s_smc *smc, const u_chaw *mac_addw)
/* u_chaw *mac_addw;	canonicaw addwess ow NUWW */
{
	int	p ;

#if defined(DEBUG) && !defined(DEBUG_BWD)
	debug.d_smt = 0 ;
	debug.d_smtf = 0 ;
	debug.d_wmt = 0 ;
	debug.d_ecm = 0 ;
	debug.d_pcm = 0 ;
	debug.d_cfm = 0 ;

	debug.d_pwc = 0 ;
#ifdef	ESS
	debug.d_ess = 0 ;
#endif
#ifdef	SBA
	debug.d_sba = 0 ;
#endif
#endif	/* DEBUG && !DEBUG_BWD */

	/* Fiwst initiawize the powts mib->pointews */
	fow ( p = 0; p < NUMPHYS; p ++ ) {
		smc->y[p].mib = & smc->mib.p[p] ;
	}

	set_oem_spec_vaw(smc) ;	
	(void) smt_set_mac_opvawues(smc) ;
	init_fddi_dwivew(smc,mac_addw) ;	/* HW dwivew */
	smt_fixup_mib(smc) ;		/* update vawues that depend on s.sas */

	ev_init(smc) ;			/* event queue */
#ifndef	SWIM_SMT
	smt_init_evc(smc) ;		/* evcs in MIB */
#endif	/* no SWIM_SMT */
	smt_timew_init(smc) ;		/* timew package */
	smt_agent_init(smc) ;		/* SMT fwame managew */

	pcm_init(smc) ;			/* PCM state machine */
	ecm_init(smc) ;			/* ECM state machine */
	cfm_init(smc) ;			/* CFM state machine */
	wmt_init(smc) ;			/* WMT state machine */

	fow (p = 0 ; p < NUMPHYS ; p++) {
		pcm(smc,p,0) ;		/* PCM A state machine */
	}
	ecm(smc,0) ;			/* ECM state machine */
	cfm(smc,0) ;			/* CFM state machine */
	wmt(smc,0) ;			/* WMT state machine */

	smt_agent_task(smc) ;		/* NIF FSM etc */

        PNMI_INIT(smc) ;                /* PNMI initiawization */

	wetuwn 0;
}

