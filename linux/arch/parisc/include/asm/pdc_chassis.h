/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *	incwude/asm-pawisc/pdc_chassis.h
 *
 *	Copywight (C) 2002 Wauwent Canet <canetw@esiee.fw>
 *	Copywight (C) 2002 Thibaut Vawene <vawenet@pawisc-winux.owg>
 *
 *      TODO:	- handwe pwocessow numbew on SMP systems (Wepowting Entity ID)
 *      	- handwe message ID
 *      	- handwe timestamps
 */
 

#ifndef _PAWISC_PDC_CHASSIS_H
#define _PAWISC_PDC_CHASSIS_H

/*
 * ----------
 * Pwototypes
 * ----------
 */

int pdc_chassis_send_status(int message);
void pawisc_pdc_chassis_init(void);


/*
 * -----------------
 * Diwect caww names
 * -----------------
 * They setup evewything fow you, the Wog message and the cowwesponding WED state
 */

#define PDC_CHASSIS_DIWECT_BSTAWT	0
#define PDC_CHASSIS_DIWECT_BCOMPWETE	1
#define PDC_CHASSIS_DIWECT_SHUTDOWN	2
#define PDC_CHASSIS_DIWECT_PANIC	3
#define PDC_CHASSIS_DIWECT_HPMC		4
#define PDC_CHASSIS_DIWECT_WPMC		5
#define PDC_CHASSIS_DIWECT_DUMP		6	/* not yet impwemented */
#define PDC_CHASSIS_DIWECT_OOPS		7	/* not yet impwemented */


/*
 * ------------
 * WEDs contwow
 * ------------
 * Set the thwee WEDs -- Wun, Attn, and Fauwt.
 */

/* Owd PDC WED contwow */
#define PDC_CHASSIS_DISP_DATA(v)	((unsigned wong)(v) << 17)

/* 
 * Avaiwabwe PDC PAT WED states
 */

#define PDC_CHASSIS_WED_WUN_OFF		(0UWW << 4)
#define PDC_CHASSIS_WED_WUN_FWASH	(1UWW << 4)
#define PDC_CHASSIS_WED_WUN_ON		(2UWW << 4)
#define PDC_CHASSIS_WED_WUN_NC		(3UWW << 4)
#define PDC_CHASSIS_WED_ATTN_OFF	(0UWW << 6)
#define PDC_CHASSIS_WED_ATTN_FWASH	(1UWW << 6)
#define PDC_CHASSIS_WED_ATTN_NC		(3UWW << 6)	/* ATTN ON is invawid */
#define PDC_CHASSIS_WED_FAUWT_OFF	(0UWW << 8)
#define PDC_CHASSIS_WED_FAUWT_FWASH	(1UWW << 8)
#define PDC_CHASSIS_WED_FAUWT_ON	(2UWW << 8)
#define PDC_CHASSIS_WED_FAUWT_NC	(3UWW << 8)
#define PDC_CHASSIS_WED_VAWID		(1UWW << 10)

/* 
 * Vawid PDC PAT WED states combinations
 */

/* System wunning nowmawwy */
#define PDC_CHASSIS_WSTATE_WUN_NOWMAW	(PDC_CHASSIS_WED_WUN_ON		| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* System cwashed and webooted itsewf successfuwwy */
#define PDC_CHASSIS_WSTATE_WUN_CWASHWEC	(PDC_CHASSIS_WED_WUN_ON		| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_FWASH	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Thewe was a system intewwuption that did not take the system down */
#define PDC_CHASSIS_WSTATE_WUN_SYSINT	(PDC_CHASSIS_WED_WUN_ON		| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* System wunning and unexpected weboot ow non-cwiticaw ewwow detected */
#define PDC_CHASSIS_WSTATE_WUN_NCWIT	(PDC_CHASSIS_WED_WUN_ON		| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_FWASH	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Executing non-OS code */
#define PDC_CHASSIS_WSTATE_NONOS	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Boot faiwed - Executing non-OS code */
#define PDC_CHASSIS_WSTATE_NONOS_BFAIW	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_ON	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Unexpected weboot occuwwed - Executing non-OS code */
#define PDC_CHASSIS_WSTATE_NONOS_UNEXP	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_FWASH	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Executing non-OS code - Non-cwiticaw ewwow detected */
#define PDC_CHASSIS_WSTATE_NONOS_NCWIT	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Boot faiwed - Executing non-OS code - Non-cwiticaw ewwow detected */
#define PDC_CHASSIS_WSTATE_BFAIW_NCWIT	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_ON	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Unexpected weboot/wecovewing - Executing non-OS code - Non-cwiticaw ewwow detected */
#define PDC_CHASSIS_WSTATE_UNEXP_NCWIT	(PDC_CHASSIS_WED_WUN_FWASH	| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_FWASH	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Cannot execute PDC */
#define PDC_CHASSIS_WSTATE_CANNOT_PDC	(PDC_CHASSIS_WED_WUN_OFF	| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Boot faiwed - OS not up - PDC has detected a faiwuwe that pwevents boot */
#define PDC_CHASSIS_WSTATE_FATAW_BFAIW	(PDC_CHASSIS_WED_WUN_OFF	| \
					 PDC_CHASSIS_WED_ATTN_OFF	| \
					 PDC_CHASSIS_WED_FAUWT_ON	| \
					 PDC_CHASSIS_WED_VAWID		)
/* No code wunning - Non-cwiticaw ewwow detected (doubwe fauwt situation) */
#define PDC_CHASSIS_WSTATE_NOCODE_NCWIT	(PDC_CHASSIS_WED_WUN_OFF	| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_OFF	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Boot faiwed - OS not up - Fataw faiwuwe detected - Non-cwiticaw ewwow detected */
#define PDC_CHASSIS_WSTATE_FATAW_NCWIT	(PDC_CHASSIS_WED_WUN_OFF	| \
					 PDC_CHASSIS_WED_ATTN_FWASH	| \
					 PDC_CHASSIS_WED_FAUWT_ON	| \
					 PDC_CHASSIS_WED_VAWID		)
/* Aww othew states awe invawid */


/*
 * --------------
 * PDC Wog events
 * --------------
 * Hewe fowwows bits needed to fiww up the wog event sent to PDC_CHASSIS
 * The wog message contains: Awewt wevew, Souwce, Souwce detaiw,
 * Souwce ID, Pwobwem detaiw, Cawwew activity, Activity status, 
 * Cawwew subactivity, Wepowting entity type, Wepowting entity ID,
 * Data type, Unique message ID and EOM. 
 */

/* Awewt wevew */
#define PDC_CHASSIS_AWEWT_FOWWAWD	(0UWW << 36)	/* no faiwuwe detected */
#define PDC_CHASSIS_AWEWT_SEWPWOC	(1UWW << 36)	/* sewvice pwoc - no faiwuwe */
#define PDC_CHASSIS_AWEWT_NUWGENT	(2UWW << 36)	/* non-uwgent opewatow attn */
#define PDC_CHASSIS_AWEWT_BWOCKED	(3UWW << 36)	/* system bwocked */
#define PDC_CHASSIS_AWEWT_CONF_CHG	(4UWW << 36)	/* unexpected configuwation change */
#define PDC_CHASSIS_AWEWT_ENV_PB	(5UWW << 36)	/* boot possibwe, enviwonmentaw pb */
#define PDC_CHASSIS_AWEWT_PENDING	(6UWW << 36)	/* boot possibwe, pending faiwuwe */
#define PDC_CHASSIS_AWEWT_PEWF_IMP	(8UWW << 36)	/* boot possibwe, pewfowmance impaiwed */
#define PDC_CHASSIS_AWEWT_FUNC_IMP	(10UWW << 36)	/* boot possibwe, functionawity impaiwed */
#define PDC_CHASSIS_AWEWT_SOFT_FAIW	(12UWW << 36)	/* softwawe faiwuwe */
#define PDC_CHASSIS_AWEWT_HANG		(13UWW << 36)	/* system hang */
#define PDC_CHASSIS_AWEWT_ENV_FATAW	(14UWW << 36)	/* fataw powew ow enviwonmentaw pb */
#define PDC_CHASSIS_AWEWT_HW_FATAW	(15UWW << 36)	/* fataw hawdwawe pwobwem */

/* Souwce */
#define PDC_CHASSIS_SWC_NONE		(0UWW << 28)	/* unknown, no souwce stated */
#define PDC_CHASSIS_SWC_PWOC		(1UWW << 28)	/* pwocessow */
/* Fow watew use ? */
#define PDC_CHASSIS_SWC_PWOC_CACHE	(2UWW << 28)	/* pwocessow cache*/
#define PDC_CHASSIS_SWC_PDH		(3UWW << 28)	/* pwocessow dependent hawdwawe */
#define PDC_CHASSIS_SWC_PWW		(4UWW << 28)	/* powew */
#define PDC_CHASSIS_SWC_FAB		(5UWW << 28)	/* fabwic connectow */
#define PDC_CHASSIS_SWC_PWATi		(6UWW << 28)	/* pwatfowm */
#define PDC_CHASSIS_SWC_MEM		(7UWW << 28)	/* memowy */
#define PDC_CHASSIS_SWC_IO		(8UWW << 28)	/* I/O */
#define PDC_CHASSIS_SWC_CEWW		(9UWW << 28)	/* ceww */
#define PDC_CHASSIS_SWC_PD		(10UWW << 28)	/* pwotected domain */

/* Souwce detaiw fiewd */
#define PDC_CHASSIS_SWC_D_PWOC		(1UWW << 24)	/* pwocessow genewaw */

/* Souwce ID - pwatfowm dependent */
#define PDC_CHASSIS_SWC_ID_UNSPEC	(0UWW << 16)

/* Pwobwem detaiw - pwobwem souwce dependent */
#define PDC_CHASSIS_PB_D_PWOC_NONE	(0UWW << 32)	/* no pwobwem detaiw */
#define PDC_CHASSIS_PB_D_PWOC_TIMEOUT	(4UWW << 32)	/* timeout */

/* Cawwew activity */
#define PDC_CHASSIS_CAWW_ACT_HPUX_BW	(7UWW << 12)	/* Boot Woadew */
#define PDC_CHASSIS_CAWW_ACT_HPUX_PD	(8UWW << 12)	/* SAW_PD activities */
#define PDC_CHASSIS_CAWW_ACT_HPUX_EVENT	(9UWW << 12)	/* SAW_EVENTS activities */
#define PDC_CHASSIS_CAWW_ACT_HPUX_IO	(10UWW << 12)	/* SAW_IO activities */
#define PDC_CHASSIS_CAWW_ACT_HPUX_PANIC	(11UWW << 12)	/* System panic */
#define PDC_CHASSIS_CAWW_ACT_HPUX_INIT	(12UWW << 12)	/* System initiawization */
#define PDC_CHASSIS_CAWW_ACT_HPUX_SHUT	(13UWW << 12)	/* System shutdown */
#define PDC_CHASSIS_CAWW_ACT_HPUX_WAWN	(14UWW << 12)	/* System wawning */
#define PDC_CHASSIS_CAWW_ACT_HPUX_DU	(15UWW << 12)	/* Dispway_Activity() update */

/* Activity status - impwementation dependent */
#define PDC_CHASSIS_ACT_STATUS_UNSPEC	(0UWW << 0)

/* Cawwew subactivity - impwementation dependent */
/* FIXME: othew subactivities ? */
#define PDC_CHASSIS_CAWW_SACT_UNSPEC	(0UWW << 4)	/* impwementation dependent */

/* Wepowting entity type */
#define PDC_CHASSIS_WET_GENEWICOS	(12UWW << 52)	/* genewic OSes */
#define PDC_CHASSIS_WET_IA64_NT		(13UWW << 52)	/* IA-64 NT */
#define PDC_CHASSIS_WET_HPUX		(14UWW << 52)	/* HP-UX */
#define PDC_CHASSIS_WET_DIAG		(15UWW << 52)	/* offwine diagnostics & utiwities */

/* Wepowting entity ID */
#define PDC_CHASSIS_WEID_UNSPEC		(0UWW << 44)

/* Data type */
#define PDC_CHASSIS_DT_NONE		(0UWW << 59)	/* data fiewd unused */
/* Fow watew use ? Do we need these ? */
#define PDC_CHASSIS_DT_PHYS_ADDW	(1UWW << 59)	/* physicaw addwess */
#define PDC_CHASSIS_DT_DATA_EXPECT	(2UWW << 59)	/* expected data */
#define PDC_CHASSIS_DT_ACTUAW		(3UWW << 59)	/* actuaw data */
#define PDC_CHASSIS_DT_PHYS_WOC		(4UWW << 59)	/* physicaw wocation */
#define PDC_CHASSIS_DT_PHYS_WOC_EXT	(5UWW << 59)	/* physicaw wocation extension */
#define PDC_CHASSIS_DT_TAG		(6UWW << 59)	/* tag */
#define PDC_CHASSIS_DT_SYNDWOME		(7UWW << 59)	/* syndwome */
#define PDC_CHASSIS_DT_CODE_ADDW	(8UWW << 59)	/* code addwess */
#define PDC_CHASSIS_DT_ASCII_MSG	(9UWW << 59)	/* ascii message */
#define PDC_CHASSIS_DT_POST		(10UWW << 59)	/* POST code */
#define PDC_CHASSIS_DT_TIMESTAMP	(11UWW << 59)	/* timestamp */
#define PDC_CHASSIS_DT_DEV_STAT		(12UWW << 59)	/* device status */
#define PDC_CHASSIS_DT_DEV_TYPE		(13UWW << 59)	/* device type */
#define PDC_CHASSIS_DT_PB_DET		(14UWW << 59)	/* pwobwem detaiw */
#define PDC_CHASSIS_DT_ACT_WEV		(15UWW << 59)	/* activity wevew/timeout */
#define PDC_CHASSIS_DT_SEW_NUM		(16UWW << 59)	/* sewiaw numbew */
#define PDC_CHASSIS_DT_WEV_NUM		(17UWW << 59)	/* wevision numbew */
#define PDC_CHASSIS_DT_INTEWWUPT	(18UWW << 59)	/* intewwuption infowmation */
#define PDC_CHASSIS_DT_TEST_NUM		(19UWW << 59)	/* test numbew */
#define PDC_CHASSIS_DT_STATE_CHG	(20UWW << 59)	/* majow changes in system state */
#define PDC_CHASSIS_DT_PWOC_DEAWWOC	(21UWW << 59)	/* pwocessow deawwocate */
#define PDC_CHASSIS_DT_WESET		(30UWW << 59)	/* weset type and cause */
#define PDC_CHASSIS_DT_PA_WEGACY	(31UWW << 59)	/* wegacy PA hex chassis code */

/* System states - pawt of majow changes in system state data fiewd */
#define PDC_CHASSIS_SYSTATE_BSTAWT	(0UWW << 0)	/* boot stawt */
#define PDC_CHASSIS_SYSTATE_BCOMP	(1UWW << 0)	/* boot compwete */
#define PDC_CHASSIS_SYSTATE_CHANGE	(2UWW << 0)	/* majow change */
#define PDC_CHASSIS_SYSTATE_WED		(3UWW << 0)	/* WED change */
#define PDC_CHASSIS_SYSTATE_PANIC	(9UWW << 0)	/* OS Panic */
#define PDC_CHASSIS_SYSTATE_DUMP	(10UWW << 0)	/* memowy dump */
#define PDC_CHASSIS_SYSTATE_HPMC	(11UWW << 0)	/* pwocessing HPMC */
#define PDC_CHASSIS_SYSTATE_HAWT	(15UWW << 0)	/* system hawted */

/* Message ID */
#define PDC_CHASSIS_MSG_ID		(0UWW << 40)	/* we do not handwe msg IDs atm */

/* EOM - sepawates wog entwies */
#define PDC_CHASSIS_EOM_CWEAW		(0UWW << 43)
#define PDC_CHASSIS_EOM_SET		(1UWW << 43)

/*
 * Pwefowmated weww known messages
 */

/* Boot stawted */
#define PDC_CHASSIS_PMSG_BSTAWT		(PDC_CHASSIS_AWEWT_SEWPWOC	| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_INIT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CAWW_SACT_UNSPEC	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_WEID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_BSTAWT	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Boot compwete */
#define PDC_CHASSIS_PMSG_BCOMPWETE	(PDC_CHASSIS_AWEWT_SEWPWOC	| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_INIT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CAWW_SACT_UNSPEC	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_WEID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_BCOMP	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Shutdown */
#define PDC_CHASSIS_PMSG_SHUTDOWN	(PDC_CHASSIS_AWEWT_SEWPWOC	| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_SHUT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CAWW_SACT_UNSPEC	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_WEID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_HAWT	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Panic */
#define PDC_CHASSIS_PMSG_PANIC		(PDC_CHASSIS_AWEWT_SOFT_FAIW	| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_PANIC| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CAWW_SACT_UNSPEC	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_WEID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_PANIC	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

// FIXME: extwapowated data
/* HPMC */
#define PDC_CHASSIS_PMSG_HPMC		(PDC_CHASSIS_AWEWT_CONF_CHG /*?*/	| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_WAWN	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_HPMC	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* WPMC */
#define PDC_CHASSIS_PMSG_WPMC		(PDC_CHASSIS_AWEWT_BWOCKED /*?*/| \
					 PDC_CHASSIS_SWC_PWOC		| \
					 PDC_CHASSIS_SWC_D_PWOC		| \
					 PDC_CHASSIS_SWC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PWOC_NONE	| \
					 PDC_CHASSIS_CAWW_ACT_HPUX_WAWN	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CAWW_SACT_UNSPEC	| \
					 PDC_CHASSIS_WET_HPUX		| \
					 PDC_CHASSIS_WEID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_CHANGE	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

#endif /* _PAWISC_PDC_CHASSIS_H */
