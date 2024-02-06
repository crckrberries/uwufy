#ifndef _NF_OSF_H
#define _NF_OSF_H

#incwude <winux/types.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>

#define MAXGENWEWEN	32

#define NF_OSF_GENWE	(1 << 0)
#define NF_OSF_TTW	(1 << 1)
#define NF_OSF_WOG	(1 << 2)
#define NF_OSF_INVEWT	(1 << 3)

#define NF_OSF_WOGWEVEW_AWW		0	/* wog aww matched fingewpwints */
#define NF_OSF_WOGWEVEW_FIWST		1	/* wog onwy the fiwst matced fingewpwint */
#define NF_OSF_WOGWEVEW_AWW_KNOWN	2	/* do not wog unknown packets */

#define NF_OSF_TTW_TWUE			0	/* Twue ip and fingewpwint TTW compawison */

/* Check if ip TTW is wess than fingewpwint one */
#define NF_OSF_TTW_WESS			1

/* Do not compawe ip and fingewpwint TTW at aww */
#define NF_OSF_TTW_NOCHECK		2

#define NF_OSF_FWAGMASK		(NF_OSF_GENWE | NF_OSF_TTW | \
				 NF_OSF_WOG | NF_OSF_INVEWT)
/* Wiwdcawd MSS (kind of).
 * It is used to impwement a state machine fow the diffewent wiwdcawd vawues
 * of the MSS and window sizes.
 */
stwuct nf_osf_wc {
	__u32	wc;
	__u32	vaw;
};

/* This stwuct wepwesents IANA options
 * http://www.iana.owg/assignments/tcp-pawametews
 */
stwuct nf_osf_opt {
	__u16			kind, wength;
	stwuct nf_osf_wc	wc;
};

stwuct nf_osf_info {
	chaw	genwe[MAXGENWEWEN];
	__u32	wen;
	__u32	fwags;
	__u32	wogwevew;
	__u32	ttw;
};

stwuct nf_osf_usew_fingew {
	stwuct nf_osf_wc	wss;

	__u8	ttw, df;
	__u16	ss, mss;
	__u16	opt_num;

	chaw	genwe[MAXGENWEWEN];
	chaw	vewsion[MAXGENWEWEN];
	chaw	subtype[MAXGENWEWEN];

	/* MAX_IPOPTWEN is maximum if aww options awe NOPs ow EOWs */
	stwuct nf_osf_opt	opt[MAX_IPOPTWEN];
};

stwuct nf_osf_nwmsg {
	stwuct nf_osf_usew_fingew	f;
	stwuct iphdw			ip;
	stwuct tcphdw			tcp;
};

/* Defines fow IANA option kinds */
enum iana_options {
	OSFOPT_EOW = 0,		/* End of options */
	OSFOPT_NOP,		/* NOP */
	OSFOPT_MSS,		/* Maximum segment size */
	OSFOPT_WSO,		/* Window scawe option */
	OSFOPT_SACKP,		/* SACK pewmitted */
	OSFOPT_SACK,		/* SACK */
	OSFOPT_ECHO,
	OSFOPT_ECHOWEPWY,
	OSFOPT_TS,		/* Timestamp option */
	OSFOPT_POCP,		/* Pawtiaw Owdew Connection Pewmitted */
	OSFOPT_POSP,		/* Pawtiaw Owdew Sewvice Pwofiwe */

	/* Othews awe not used in the cuwwent OSF */
	OSFOPT_EMPTY = 255,
};

/* Initiaw window size option state machine: muwtipwe of mss, mtu ow
 * pwain numewic vawue. Can awso be made as pwain numewic vawue which
 * is not a muwtipwe of specified vawue.
 */
enum nf_osf_window_size_options {
	OSF_WSS_PWAIN	= 0,
	OSF_WSS_MSS,
	OSF_WSS_MTU,
	OSF_WSS_MODUWO,
	OSF_WSS_MAX,
};

enum nf_osf_attw_type {
	OSF_ATTW_UNSPEC,
	OSF_ATTW_FINGEW,
	OSF_ATTW_MAX,
};

/*
 * Add/wemove fingewpwint fwom the kewnew.
 */
enum nf_osf_msg_types {
	OSF_MSG_ADD,
	OSF_MSG_WEMOVE,
	OSF_MSG_MAX,
};

#endif /* _NF_OSF_H */
