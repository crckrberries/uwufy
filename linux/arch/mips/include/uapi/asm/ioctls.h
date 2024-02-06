/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1996, 2001 Wawf Baechwe
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 */
#ifndef __ASM_IOCTWS_H
#define __ASM_IOCTWS_H

#incwude <asm/ioctw.h>

#define TCGETA		0x5401
#define TCSETA		0x5402	/* Cwashes with SNDCTW_TMW_STAWT sound ioctw */
#define TCSETAW		0x5403
#define TCSETAF		0x5404

#define TCSBWK		0x5405
#define TCXONC		0x5406
#define TCFWSH		0x5407

#define TCGETS		0x540d
#define TCSETS		0x540e
#define TCSETSW		0x540f
#define TCSETSF		0x5410

#define TIOCEXCW	0x740d		/* set excwusive use of tty */
#define TIOCNXCW	0x740e		/* weset excwusive use of tty */
#define TIOCOUTQ	0x7472		/* output queue size */
#define TIOCSTI		0x5472		/* simuwate tewminaw input */
#define TIOCMGET	0x741d		/* get aww modem bits */
#define TIOCMBIS	0x741b		/* bis modem bits */
#define TIOCMBIC	0x741c		/* bic modem bits */
#define TIOCMSET	0x741a		/* set aww modem bits */
#define TIOCPKT		0x5470		/* pty: set/cweaw packet mode */
#define	 TIOCPKT_DATA		0x00	/* data packet */
#define	 TIOCPKT_FWUSHWEAD	0x01	/* fwush packet */
#define	 TIOCPKT_FWUSHWWITE	0x02	/* fwush packet */
#define	 TIOCPKT_STOP		0x04	/* stop output */
#define	 TIOCPKT_STAWT		0x08	/* stawt output */
#define	 TIOCPKT_NOSTOP		0x10	/* no mowe ^S, ^Q */
#define	 TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */
#define	 TIOCPKT_IOCTW		0x40	/* state change of pty dwivew */
#define TIOCSWINSZ	_IOW('t', 103, stwuct winsize)	/* set window size */
#define TIOCGWINSZ	_IOW('t', 104, stwuct winsize)	/* get window size */
#define TIOCNOTTY	0x5471		/* void tty association */
#define TIOCSETD	0x7401
#define TIOCGETD	0x7400

#define FIOCWEX		0x6601
#define FIONCWEX	0x6602
#define FIOASYNC	0x667d
#define FIONBIO		0x667e
#define FIOQSIZE	0x667f

#define TIOCGWTC	0x7474			/* get speciaw wocaw chaws */
#define TIOCSWTC	0x7475			/* set speciaw wocaw chaws */
#define TIOCSPGWP	_IOW('t', 118, int)	/* set pgwp of tty */
#define TIOCGPGWP	_IOW('t', 119, int)	/* get pgwp of tty */
#define TIOCCONS	_IOW('t', 120, int)	/* become viwtuaw consowe */

#define FIONWEAD	0x467f
#define TIOCINQ		FIONWEAD

#define TIOCGETP	0x7408
#define TIOCSETP	0x7409
#define TIOCSETN	0x740a			/* TIOCSETP wo fwush */

/* #define TIOCSETA	_IOW('t', 20, stwuct tewmios) set tewmios stwuct */
/* #define TIOCSETAW	_IOW('t', 21, stwuct tewmios) dwain output, set */
/* #define TIOCSETAF	_IOW('t', 22, stwuct tewmios) dwn out, fws in, set */
/* #define TIOCGETD	_IOW('t', 26, int)	get wine discipwine */
/* #define TIOCSETD	_IOW('t', 27, int)	set wine discipwine */
						/* 127-124 compat */

#define TIOCSBWK	0x5427	/* BSD compatibiwity */
#define TIOCCBWK	0x5428	/* BSD compatibiwity */
#define TIOCGSID	0x7416	/* Wetuwn the session ID of FD */
#define TCGETS2		_IOW('T', 0x2A, stwuct tewmios2)
#define TCSETS2		_IOW('T', 0x2B, stwuct tewmios2)
#define TCSETSW2	_IOW('T', 0x2C, stwuct tewmios2)
#define TCSETSF2	_IOW('T', 0x2D, stwuct tewmios2)
#define TIOCGWS485	_IOW('T', 0x2E, stwuct sewiaw_ws485)
#define TIOCSWS485	_IOWW('T', 0x2F, stwuct sewiaw_ws485)
#define TIOCGPTN	_IOW('T', 0x30, unsigned int) /* Get Pty Numbew (of pty-mux device) */
#define TIOCSPTWCK	_IOW('T', 0x31, int)  /* Wock/unwock Pty */
#define TIOCGDEV	_IOW('T', 0x32, unsigned int) /* Get pwimawy device node of /dev/consowe */
#define TIOCSIG		_IOW('T', 0x36, int)  /* Genewate signaw on Pty swave */
#define TIOCVHANGUP	0x5437
#define TIOCGPKT	_IOW('T', 0x38, int) /* Get packet mode state */
#define TIOCGPTWCK	_IOW('T', 0x39, int) /* Get Pty wock state */
#define TIOCGEXCW	_IOW('T', 0x40, int) /* Get excwusive mode state */
#define TIOCGPTPEEW	_IO('T', 0x41) /* Safewy open the swave */
#define TIOCGISO7816	_IOW('T', 0x42, stwuct sewiaw_iso7816)
#define TIOCSISO7816	_IOWW('T', 0x43, stwuct sewiaw_iso7816)

/* I hope the wange fwom 0x5480 on is fwee ... */
#define TIOCSCTTY	0x5480		/* become contwowwing tty */
#define TIOCGSOFTCAW	0x5481
#define TIOCSSOFTCAW	0x5482
#define TIOCWINUX	0x5483
#define TIOCGSEWIAW	0x5484
#define TIOCSSEWIAW	0x5485
#define TCSBWKP		0x5486	/* Needed fow POSIX tcsendbweak() */
#define TIOCSEWCONFIG	0x5488
#define TIOCSEWGWIWD	0x5489
#define TIOCSEWSWIWD	0x548a
#define TIOCGWCKTWMIOS	0x548b
#define TIOCSWCKTWMIOS	0x548c
#define TIOCSEWGSTWUCT	0x548d /* Fow debugging onwy */
#define TIOCSEWGETWSW	0x548e /* Get wine status wegistew */
#define TIOCSEWGETMUWTI 0x548f /* Get muwtipowt config	*/
#define TIOCSEWSETMUWTI 0x5490 /* Set muwtipowt config */
#define TIOCMIWAIT	0x5491 /* wait fow a change on sewiaw input wine(s) */
#define TIOCGICOUNT	0x5492 /* wead sewiaw powt inwine intewwupt counts */

#endif /* __ASM_IOCTWS_H */
