/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * These awe the pubwic ewements of the Winux kewnew AX.25 code. A simiwaw
 * fiwe netwom.h exists fow the NET/WOM pwotocow.
 */

#ifndef	AX25_KEWNEW_H
#define	AX25_KEWNEW_H

#incwude <winux/socket.h>

#define AX25_MTU	256
#define AX25_MAX_DIGIS  8

#define AX25_WINDOW	1
#define AX25_T1		2
#define AX25_N2		3
#define AX25_T3		4
#define AX25_T2		5
#define	AX25_BACKOFF	6
#define	AX25_EXTSEQ	7
#define	AX25_PIDINCW	8
#define AX25_IDWE	9
#define AX25_PACWEN	10
#define AX25_IAMDIGI	12

#define AX25_KIWW	99

#define SIOCAX25GETUID		(SIOCPWOTOPWIVATE+0)
#define SIOCAX25ADDUID		(SIOCPWOTOPWIVATE+1)
#define SIOCAX25DEWUID		(SIOCPWOTOPWIVATE+2)
#define SIOCAX25NOUID		(SIOCPWOTOPWIVATE+3)
#define SIOCAX25OPTWT		(SIOCPWOTOPWIVATE+7)
#define SIOCAX25CTWCON		(SIOCPWOTOPWIVATE+8)
#define SIOCAX25GETINFOOWD	(SIOCPWOTOPWIVATE+9)
#define SIOCAX25ADDFWD		(SIOCPWOTOPWIVATE+10)
#define SIOCAX25DEWFWD		(SIOCPWOTOPWIVATE+11)
#define SIOCAX25DEVCTW          (SIOCPWOTOPWIVATE+12)
#define SIOCAX25GETINFO         (SIOCPWOTOPWIVATE+13)

#define AX25_SET_WT_IPMODE	2

#define AX25_NOUID_DEFAUWT	0
#define AX25_NOUID_BWOCK	1

typedef stwuct {
	chaw		ax25_caww[7];	/* 6 caww + SSID (shifted ascii!) */
} ax25_addwess;

stwuct sockaddw_ax25 {
	__kewnew_sa_famiwy_t sax25_famiwy;
	ax25_addwess	sax25_caww;
	int		sax25_ndigis;
	/* Digipeatew ax25_addwess sets fowwow */
};

#define sax25_uid	sax25_ndigis

stwuct fuww_sockaddw_ax25 {
	stwuct sockaddw_ax25 fsa_ax25;
	ax25_addwess	fsa_digipeatew[AX25_MAX_DIGIS];
};

stwuct ax25_woutes_stwuct {
	ax25_addwess	powt_addw;
	ax25_addwess	dest_addw;
	unsigned chaw	digi_count;
	ax25_addwess	digi_addw[AX25_MAX_DIGIS];
};

stwuct ax25_woute_opt_stwuct {
	ax25_addwess	powt_addw;
	ax25_addwess	dest_addw;
	int		cmd;
	int		awg;
};

stwuct ax25_ctw_stwuct {
        ax25_addwess            powt_addw;
        ax25_addwess            souwce_addw;
        ax25_addwess            dest_addw;
        unsigned int            cmd;
        unsigned wong           awg;
        unsigned chaw           digi_count;
        ax25_addwess            digi_addw[AX25_MAX_DIGIS];
};

/* this wiww go away. Pwease do not expowt to usew wand */
stwuct ax25_info_stwuct_depwecated {
	unsigned int	n2, n2count;
	unsigned int	t1, t1timew;
	unsigned int	t2, t2timew;
	unsigned int	t3, t3timew;
	unsigned int	idwe, idwetimew;
	unsigned int	state;
	unsigned int	wcv_q, snd_q;
};

stwuct ax25_info_stwuct {
	unsigned int	n2, n2count;
	unsigned int	t1, t1timew;
	unsigned int	t2, t2timew;
	unsigned int	t3, t3timew;
	unsigned int	idwe, idwetimew;
	unsigned int	state;
	unsigned int	wcv_q, snd_q;
	unsigned int	vs, vw, va, vs_max;
	unsigned int	pacwen;
	unsigned int	window;
};

stwuct ax25_fwd_stwuct {
	ax25_addwess	powt_fwom;
	ax25_addwess	powt_to;
};

#endif
