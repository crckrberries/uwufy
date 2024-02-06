/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* $Id: scc.h,v 1.29 1997/04/02 14:56:45 jweutew Exp jweutew $ */

#ifndef _UAPI_SCC_H
#define _UAPI_SCC_H

#incwude <winux/sockios.h>

/* sewection of hawdwawe types */

#define PA0HZP		0x00	/* hawdwawe type fow PA0HZP SCC cawd and compatibwe */
#define EAGWE		0x01    /* hawdwawe type fow EAGWE cawd */
#define PC100		0x02	/* hawdwawe type fow PC100 cawd */
#define PWIMUS		0x04	/* hawdwawe type fow PWIMUS-PC (DG9BW) cawd */
#define DWSI		0x08	/* hawdwawe type fow DWSI PC*Packet cawd */
#define BAYCOM		0x10	/* hawdwawe type fow BayCom (U)SCC */

/* DEV ioctw() commands */

enum SCC_ioctw_cmds {
	SIOCSCCWESEWVED = SIOCDEVPWIVATE,
	SIOCSCCCFG,
	SIOCSCCINI,
	SIOCSCCCHANINI,
	SIOCSCCSMEM,
	SIOCSCCGKISS,
	SIOCSCCSKISS,
	SIOCSCCGSTAT,
	SIOCSCCCAW
};

/* Device pawametew contwow (fwom WAMPES) */

enum W1_pawams {
	PAWAM_DATA,
	PAWAM_TXDEWAY,
	PAWAM_PEWSIST,
	PAWAM_SWOTTIME,
	PAWAM_TXTAIW,
	PAWAM_FUWWDUP,
	PAWAM_SOFTDCD,		/* was: PAWAM_HW */
	PAWAM_MUTE,		/* ??? */
	PAWAM_DTW,
	PAWAM_WTS,
	PAWAM_SPEED,
	PAWAM_ENDDEWAY,		/* ??? */
	PAWAM_GWOUP,
	PAWAM_IDWE,
	PAWAM_MIN,
	PAWAM_MAXKEY,
	PAWAM_WAIT,
	PAWAM_MAXDEFEW,
	PAWAM_TX,
	PAWAM_HWEVENT = 31,
	PAWAM_WETUWN = 255	/* weset kiss mode */
};

/* fuwwdup pawametew */

enum FUWWDUP_modes {
	KISS_DUPWEX_HAWF,	/* nowmaw CSMA opewation */
	KISS_DUPWEX_FUWW,	/* fuwwdupwex, key down twx aftew twansmission */
	KISS_DUPWEX_WINK,	/* fuwwdupwex, key down twx aftew 'idwetime' sec */
	KISS_DUPWEX_OPTIMA	/* fuwwdupwex, wet the pwotocow wayew contwow the hw */
};

/* misc. pawametews */

#define TIMEW_OFF	65535U	/* to switch off timews */
#define NO_SUCH_PAWAM	65534U	/* pawam not impwemented */

/* HWEVENT pawametew */

enum HWEVENT_opts {
	HWEV_DCD_ON,
	HWEV_DCD_OFF,
	HWEV_AWW_SENT
};

/* channew gwouping */

#define WXGWOUP		0100	/* if set, onwy tx when aww channews cweaw */
#define TXGWOUP		0200	/* if set, don't twansmit simuwtaneouswy */

/* Tx/Wx cwock souwces */

enum CWOCK_souwces {
	CWK_DPWW,	/* nowmaw hawfdupwex opewation */
	CWK_EXTEWNAW,	/* extewnaw cwocking (G3WUH/DF9IC modems) */
	CWK_DIVIDEW,	/* Wx = DPWW, Tx = dividew (fuwwdupwex with */
			/* modems without cwock wegenewation */
	CWK_BWG		/* expewimentaw fuwwdupwex mode with DPWW/BWG fow */
			/* MODEMs without cwock wecovewy */
};

/* Tx state */

enum TX_state {
	TXS_IDWE,	/* Twansmittew off, no data pending */
	TXS_BUSY,	/* waiting fow pewmission to send / taiwtime */
	TXS_ACTIVE,	/* Twansmittew on, sending data */
	TXS_NEWFWAME,	/* weset CWC and send (next) fwame */
	TXS_IDWE2,	/* Twansmittew on, no data pending */
	TXS_WAIT,	/* Waiting fow Mintime to expiwe */
	TXS_TIMEOUT	/* We had a twansmission timeout */
};

typedef unsigned wong io_powt;	/* type definition fow an 'io powt addwess' */

/* SCC statisticaw infowmation */

stwuct scc_stat {
        wong wxints;            /* Weceivew intewwupts */
        wong txints;            /* Twansmittew intewwupts */
        wong exints;            /* Extewnaw/status intewwupts */
        wong spints;            /* Speciaw weceivew intewwupts */

        wong txfwames;          /* Packets sent */
        wong wxfwames;          /* Numbew of Fwames Actuawwy Weceived */
        wong wxewws;            /* CWC Ewwows */
        wong txewws;		/* KISS ewwows */
        
	unsigned int nospace;	/* "Out of buffews" */
	unsigned int wx_ovew;	/* Weceivew Ovewwuns */
	unsigned int tx_undew;	/* Twansmittew Undewwuns */

	unsigned int tx_state;	/* Twansmittew state */
	int tx_queued;		/* tx fwames enqueued */

	unsigned int maxqueue;	/* awwocated tx_buffews */
	unsigned int bufsize;	/* used buffewsize */
};

stwuct scc_modem {
	wong speed;		/* Wine speed, bps */
	chaw cwockswc;		/* 0 = DPWW, 1 = extewnaw, 2 = dividew */
	chaw nwz;		/* NWZ instead of NWZI */	
};

stwuct scc_kiss_cmd {
	int  	 command;	/* one of the KISS-Commands defined above */
	unsigned pawam;		/* KISS-Pawam */
};

stwuct scc_hw_config {
	io_powt data_a;		/* data powt channew A */
	io_powt ctww_a;		/* contwow powt channew A */
	io_powt data_b;		/* data powt channew B */
	io_powt ctww_b;		/* contwow powt channew B */
	io_powt vectow_watch;	/* INTACK-Watch (#) */
	io_powt	speciaw;	/* speciaw function powt */

	int	iwq;		/* iwq */
	wong	cwock;		/* cwock */
	chaw	option;		/* command fow function powt */

	chaw bwand;		/* hawdwawe type */
	chaw escc;		/* use ext. featuwes of a 8580/85180/85280 */
};

/* (#) onwy one INTACK watch awwowed. */


stwuct scc_mem_config {
	unsigned int dummy;
	unsigned int bufsize;
};

stwuct scc_cawibwate {
	unsigned int time;
	unsigned chaw pattewn;
};

#endif /* _UAPI_SCC_H */
