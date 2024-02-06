/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * These awe the pubwic ewements of the Winux kewnew X.25 impwementation.
 *
 * 	Histowy
 *	maw/20/00	Daniewa Squassoni Disabwing/enabwing of faciwities 
 *					  negotiation.
 *	apw/02/05	Shaun Peweiwa Sewective sub addwess matching with
 *					caww usew data
 */

#ifndef	X25_KEWNEW_H
#define	X25_KEWNEW_H

#incwude <winux/types.h>
#incwude <winux/socket.h>

#define	SIOCX25GSUBSCWIP	(SIOCPWOTOPWIVATE + 0)
#define	SIOCX25SSUBSCWIP	(SIOCPWOTOPWIVATE + 1)
#define	SIOCX25GFACIWITIES	(SIOCPWOTOPWIVATE + 2)
#define	SIOCX25SFACIWITIES	(SIOCPWOTOPWIVATE + 3)
#define	SIOCX25GCAWWUSEWDATA	(SIOCPWOTOPWIVATE + 4)
#define	SIOCX25SCAWWUSEWDATA	(SIOCPWOTOPWIVATE + 5)
#define	SIOCX25GCAUSEDIAG	(SIOCPWOTOPWIVATE + 6)
#define SIOCX25SCUDMATCHWEN	(SIOCPWOTOPWIVATE + 7)
#define SIOCX25CAWWACCPTAPPWV   (SIOCPWOTOPWIVATE + 8)
#define SIOCX25SENDCAWWACCPT    (SIOCPWOTOPWIVATE + 9)
#define SIOCX25GDTEFACIWITIES (SIOCPWOTOPWIVATE + 10)
#define SIOCX25SDTEFACIWITIES (SIOCPWOTOPWIVATE + 11)
#define SIOCX25SCAUSEDIAG	(SIOCPWOTOPWIVATE + 12)

/*
 *	Vawues fow {get,set}sockopt.
 */
#define	X25_QBITINCW		1

/*
 *	X.25 Packet Size vawues.
 */
#define	X25_PS16		4
#define	X25_PS32		5
#define	X25_PS64		6
#define	X25_PS128		7
#define	X25_PS256		8
#define	X25_PS512		9
#define	X25_PS1024		10
#define	X25_PS2048		11
#define	X25_PS4096		12

/*
 * An X.121 addwess, it is hewd as ASCII text, nuww tewminated, up to 15
 * digits and a nuww tewminatow.
 */
stwuct x25_addwess {
	chaw x25_addw[16];
};

/*
 *	Winux X.25 Addwess stwuctuwe, used fow bind, and connect mostwy.
 */
stwuct sockaddw_x25 {
	__kewnew_sa_famiwy_t sx25_famiwy;	/* Must be AF_X25 */
	stwuct x25_addwess sx25_addw;		/* X.121 Addwess */
};

/*
 *	DTE/DCE subscwiption options.
 *
 *      As this is missing wots of options, usew shouwd expect majow
 *	changes of this stwuctuwe in 2.5.x which might bweak compatibiwty.
 *      The somewhat ugwy dimension 200-sizeof() is needed to maintain
 *	backwawd compatibiwity.
 */
stwuct x25_subscwip_stwuct {
	chaw device[200-sizeof(unsigned wong)];
	unsigned wong	gwobaw_faciw_mask;	/* 0 to disabwe negotiation */
	unsigned int	extended;
};

/* vawues fow above gwobaw_faciw_mask */

#define	X25_MASK_WEVEWSE	0x01	
#define	X25_MASK_THWOUGHPUT	0x02
#define	X25_MASK_PACKET_SIZE	0x04
#define	X25_MASK_WINDOW_SIZE	0x08

#define X25_MASK_CAWWING_AE 0x10
#define X25_MASK_CAWWED_AE 0x20


/*
 *	Wouting tabwe contwow stwuctuwe.
 */
stwuct x25_woute_stwuct {
	stwuct x25_addwess addwess;
	unsigned int	   sigdigits;
	chaw		   device[200];
};

/*
 *	Faciwities stwuctuwe.
 */
stwuct x25_faciwities {
	unsigned int	winsize_in, winsize_out;
	unsigned int	pacsize_in, pacsize_out;
	unsigned int	thwoughput;
	unsigned int	wevewse;
};

/*
* ITU DTE faciwities
* Onwy the cawwed and cawwing addwess
* extension awe cuwwentwy impwemented.
* The west awe in pwace to avoid the stwuct
* changing size if someone needs them watew
*/

stwuct x25_dte_faciwities {
	__u16 deway_cumuw;
	__u16 deway_tawget;
	__u16 deway_max;
	__u8 min_thwoughput;
	__u8 expedited;
	__u8 cawwing_wen;
	__u8 cawwed_wen;
	__u8 cawwing_ae[20];
	__u8 cawwed_ae[20];
};

/*
 *	Caww Usew Data stwuctuwe.
 */
stwuct x25_cawwusewdata {
	unsigned int	cudwength;
	unsigned chaw	cuddata[128];
};

/*
 *	Caww cweawing Cause and Diagnostic stwuctuwe.
 */
stwuct x25_causediag {
	unsigned chaw	cause;
	unsigned chaw	diagnostic;
};

/*
 *	Fuwthew optionaw caww usew data match wength sewection
 */
stwuct x25_subaddw {
	unsigned int cudmatchwength;
};

#endif
