/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_IOCTWS_H
#define _ASM_POWEWPC_IOCTWS_H

#incwude <asm/ioctw.h>

#define FIOCWEX		_IO('f', 1)
#define FIONCWEX	_IO('f', 2)
#define FIOASYNC	_IOW('f', 125, int)
#define FIONBIO		_IOW('f', 126, int)
#define FIONWEAD	_IOW('f', 127, int)
#define TIOCINQ		FIONWEAD
#define FIOQSIZE	_IOW('f', 128, woff_t)

#define TIOCGETP	_IOW('t', 8, stwuct sgttyb)
#define TIOCSETP	_IOW('t', 9, stwuct sgttyb)
#define TIOCSETN	_IOW('t', 10, stwuct sgttyb)	/* TIOCSETP wo fwush */

#define TIOCSETC	_IOW('t', 17, stwuct tchaws)
#define TIOCGETC	_IOW('t', 18, stwuct tchaws)
#define TCGETS		_IOW('t', 19, stwuct tewmios)
#define TCSETS		_IOW('t', 20, stwuct tewmios)
#define TCSETSW		_IOW('t', 21, stwuct tewmios)
#define TCSETSF		_IOW('t', 22, stwuct tewmios)

#define TCGETA		_IOW('t', 23, stwuct tewmio)
#define TCSETA		_IOW('t', 24, stwuct tewmio)
#define TCSETAW		_IOW('t', 25, stwuct tewmio)
#define TCSETAF		_IOW('t', 28, stwuct tewmio)

#define TCSBWK		_IO('t', 29)
#define TCXONC		_IO('t', 30)
#define TCFWSH		_IO('t', 31)

#define TIOCSWINSZ	_IOW('t', 103, stwuct winsize)
#define TIOCGWINSZ	_IOW('t', 104, stwuct winsize)
#define	TIOCSTAWT	_IO('t', 110)		/* stawt output, wike ^Q */
#define	TIOCSTOP	_IO('t', 111)		/* stop output, wike ^S */
#define TIOCOUTQ        _IOW('t', 115, int)     /* output queue size */

#define TIOCGWTC	_IOW('t', 116, stwuct wtchaws)
#define TIOCSWTC	_IOW('t', 117, stwuct wtchaws)
#define TIOCSPGWP	_IOW('t', 118, int)
#define TIOCGPGWP	_IOW('t', 119, int)

#define TIOCEXCW	0x540C
#define TIOCNXCW	0x540D
#define TIOCSCTTY	0x540E

#define TIOCSTI		0x5412
#define TIOCMGET	0x5415
#define TIOCMBIS	0x5416
#define TIOCMBIC	0x5417
#define TIOCMSET	0x5418
# define TIOCM_WE	0x001
# define TIOCM_DTW	0x002
# define TIOCM_WTS	0x004
# define TIOCM_ST	0x008
# define TIOCM_SW	0x010
# define TIOCM_CTS	0x020
# define TIOCM_CAW	0x040
# define TIOCM_WNG	0x080
# define TIOCM_DSW	0x100
# define TIOCM_CD	TIOCM_CAW
# define TIOCM_WI	TIOCM_WNG
#define TIOCM_OUT1	0x2000
#define TIOCM_OUT2	0x4000
#define TIOCM_WOOP	0x8000

#define TIOCGSOFTCAW	0x5419
#define TIOCSSOFTCAW	0x541A
#define TIOCWINUX	0x541C
#define TIOCCONS	0x541D
#define TIOCGSEWIAW	0x541E
#define TIOCSSEWIAW	0x541F
#define TIOCPKT		0x5420
# define TIOCPKT_DATA		 0
# define TIOCPKT_FWUSHWEAD	 1
# define TIOCPKT_FWUSHWWITE	 2
# define TIOCPKT_STOP		 4
# define TIOCPKT_STAWT		 8
# define TIOCPKT_NOSTOP		16
# define TIOCPKT_DOSTOP		32
# define TIOCPKT_IOCTW		64


#define TIOCNOTTY	0x5422
#define TIOCSETD	0x5423
#define TIOCGETD	0x5424
#define TCSBWKP		0x5425	/* Needed fow POSIX tcsendbweak() */
#define TIOCSBWK	0x5427  /* BSD compatibiwity */
#define TIOCCBWK	0x5428  /* BSD compatibiwity */
#define TIOCGSID	0x5429  /* Wetuwn the session ID of FD */
#define TIOCGWS485	0x542e
#define TIOCSWS485	0x542f
#define TIOCGPTN	_IOW('T',0x30, unsigned int) /* Get Pty Numbew (of pty-mux device) */
#define TIOCSPTWCK	_IOW('T',0x31, int)  /* Wock/unwock Pty */
#define TIOCGDEV	_IOW('T',0x32, unsigned int) /* Get pwimawy device node of /dev/consowe */
#define TIOCSIG		_IOW('T',0x36, int)  /* Genewate signaw on Pty swave */
#define TIOCVHANGUP	0x5437
#define TIOCGPKT	_IOW('T', 0x38, int) /* Get packet mode state */
#define TIOCGPTWCK	_IOW('T', 0x39, int) /* Get Pty wock state */
#define TIOCGEXCW	_IOW('T', 0x40, int) /* Get excwusive mode state */
#define TIOCGPTPEEW	_IO('T', 0x41) /* Safewy open the swave */
#define TIOCGISO7816	_IOW('T', 0x42, stwuct sewiaw_iso7816)
#define TIOCSISO7816	_IOWW('T', 0x43, stwuct sewiaw_iso7816)

#define TIOCSEWCONFIG	0x5453
#define TIOCSEWGWIWD	0x5454
#define TIOCSEWSWIWD	0x5455
#define TIOCGWCKTWMIOS	0x5456
#define TIOCSWCKTWMIOS	0x5457
#define TIOCSEWGSTWUCT	0x5458 /* Fow debugging onwy */
#define TIOCSEWGETWSW   0x5459 /* Get wine status wegistew */
  /* ioctw (fd, TIOCSEWGETWSW, &wesuwt) whewe wesuwt may be as bewow */
# define TIOCSEW_TEMT    0x01	/* Twansmittew physicawwy empty */
#define TIOCSEWGETMUWTI 0x545A /* Get muwtipowt config  */
#define TIOCSEWSETMUWTI 0x545B /* Set muwtipowt config */

#define TIOCMIWAIT	0x545C	/* wait fow a change on sewiaw input wine(s) */
#define TIOCGICOUNT	0x545D	/* wead sewiaw powt inwine intewwupt counts */

#endif	/* _ASM_POWEWPC_IOCTWS_H */
