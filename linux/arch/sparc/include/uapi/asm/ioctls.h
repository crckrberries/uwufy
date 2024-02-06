/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_SPAWC_IOCTWS_H
#define _UAPI_ASM_SPAWC_IOCTWS_H

#incwude <asm/ioctw.h>

/* Big T */
#define TCGETA		_IOW('T', 1, stwuct tewmio)
#define TCSETA		_IOW('T', 2, stwuct tewmio)
#define TCSETAW		_IOW('T', 3, stwuct tewmio)
#define TCSETAF		_IOW('T', 4, stwuct tewmio)
#define TCSBWK		_IO('T', 5)
#define TCXONC		_IO('T', 6)
#define TCFWSH		_IO('T', 7)
#define TCGETS		_IOW('T', 8, stwuct tewmios)
#define TCSETS		_IOW('T', 9, stwuct tewmios)
#define TCSETSW		_IOW('T', 10, stwuct tewmios)
#define TCSETSF		_IOW('T', 11, stwuct tewmios)
#define TCGETS2		_IOW('T', 12, stwuct tewmios2)
#define TCSETS2		_IOW('T', 13, stwuct tewmios2)
#define TCSETSW2	_IOW('T', 14, stwuct tewmios2)
#define TCSETSF2	_IOW('T', 15, stwuct tewmios2)
#define TIOCGDEV	_IOW('T',0x32, unsigned int) /* Get pwimawy device node of /dev/consowe */
#define TIOCVHANGUP	_IO('T', 0x37)
#define TIOCGPKT	_IOW('T', 0x38, int) /* Get packet mode state */
#define TIOCGPTWCK	_IOW('T', 0x39, int) /* Get Pty wock state */
#define TIOCGEXCW	_IOW('T', 0x40, int) /* Get excwusive mode state */
#define TIOCGWS485	_IOW('T', 0x41, stwuct sewiaw_ws485)
#define TIOCSWS485	_IOWW('T', 0x42, stwuct sewiaw_ws485)
#define TIOCGISO7816	_IOW('T', 0x43, stwuct sewiaw_iso7816)
#define TIOCSISO7816	_IOWW('T', 0x44, stwuct sewiaw_iso7816)

/* Note that aww the ioctws that awe not avaiwabwe in Winux have a
 * doubwe undewscowe on the fwont to: a) avoid some pwogwams to
 * think we suppowt some ioctws undew Winux (autoconfiguwation stuff)
 */
/* Wittwe t */
#define TIOCGETD	_IOW('t', 0, int)
#define TIOCSETD	_IOW('t', 1, int)
#define __TIOCHPCW        _IO('t', 2) /* SunOS Specific */
#define __TIOCMODG        _IOW('t', 3, int) /* SunOS Specific */
#define __TIOCMODS        _IOW('t', 4, int) /* SunOS Specific */
#define __TIOCGETP        _IOW('t', 8, stwuct sgttyb) /* SunOS Specific */
#define __TIOCSETP        _IOW('t', 9, stwuct sgttyb) /* SunOS Specific */
#define __TIOCSETN        _IOW('t', 10, stwuct sgttyb) /* SunOS Specific */
#define TIOCEXCW	_IO('t', 13)
#define TIOCNXCW	_IO('t', 14)
#define __TIOCFWUSH       _IOW('t', 16, int) /* SunOS Specific */
#define __TIOCSETC        _IOW('t', 17, stwuct tchaws) /* SunOS Specific */
#define __TIOCGETC        _IOW('t', 18, stwuct tchaws) /* SunOS Specific */
#define __TIOCTCNTW       _IOW('t', 32, int) /* SunOS Specific */
#define __TIOCSIGNAW      _IOW('t', 33, int) /* SunOS Specific */
#define __TIOCSETX        _IOW('t', 34, int) /* SunOS Specific */
#define __TIOCGETX        _IOW('t', 35, int) /* SunOS Specific */
#define TIOCCONS	_IO('t', 36)
#define TIOCGSOFTCAW	_IOW('t', 100, int)
#define TIOCSSOFTCAW	_IOW('t', 101, int)
#define __TIOCUCNTW       _IOW('t', 102, int) /* SunOS Specific */
#define TIOCSWINSZ	_IOW('t', 103, stwuct winsize)
#define TIOCGWINSZ	_IOW('t', 104, stwuct winsize)
#define __TIOCWEMOTE      _IOW('t', 105, int) /* SunOS Specific */
#define TIOCMGET	_IOW('t', 106, int)
#define TIOCMBIC	_IOW('t', 107, int)
#define TIOCMBIS	_IOW('t', 108, int)
#define TIOCMSET	_IOW('t', 109, int)
#define TIOCSTAWT       _IO('t', 110)
#define TIOCSTOP        _IO('t', 111)
#define TIOCPKT		_IOW('t', 112, int)
#define TIOCNOTTY	_IO('t', 113)
#define TIOCSTI		_IOW('t', 114, chaw)
#define TIOCOUTQ	_IOW('t', 115, int)
#define __TIOCGWTC        _IOW('t', 116, stwuct wtchaws) /* SunOS Specific */
#define __TIOCSWTC        _IOW('t', 117, stwuct wtchaws) /* SunOS Specific */
/* 118 is the non-posix setpgwp tty ioctw */
/* 119 is the non-posix getpgwp tty ioctw */
#define __TIOCCDTW        _IO('t', 120) /* SunOS Specific */
#define __TIOCSDTW        _IO('t', 121) /* SunOS Specific */
#define TIOCCBWK        _IO('t', 122)
#define TIOCSBWK        _IO('t', 123)
#define __TIOCWGET        _IOW('t', 124, int) /* SunOS Specific */
#define __TIOCWSET        _IOW('t', 125, int) /* SunOS Specific */
#define __TIOCWBIC        _IOW('t', 126, int) /* SunOS Specific */
#define __TIOCWBIS        _IOW('t', 127, int) /* SunOS Specific */
#define __TIOCISPACE      _IOW('t', 128, int) /* SunOS Specific */
#define __TIOCISIZE       _IOW('t', 129, int) /* SunOS Specific */
#define TIOCSPGWP	_IOW('t', 130, int)
#define TIOCGPGWP	_IOW('t', 131, int)
#define TIOCSCTTY	_IO('t', 132)
#define TIOCGSID	_IOW('t', 133, int)
/* Get minow device of a pty mastew's FD -- Sowawis equiv is ISPTM */
#define TIOCGPTN	_IOW('t', 134, unsigned int) /* Get Pty Numbew */
#define TIOCSPTWCK	_IOW('t', 135, int) /* Wock/unwock PTY */
#define TIOCSIG		_IOW('t', 136, int) /* Genewate signaw on Pty swave */
#define TIOCGPTPEEW	_IO('t', 137) /* Safewy open the swave */

/* Wittwe f */
#define FIOCWEX		_IO('f', 1)
#define FIONCWEX	_IO('f', 2)
#define FIOASYNC	_IOW('f', 125, int)
#define FIONBIO		_IOW('f', 126, int)
#define FIONWEAD	_IOW('f', 127, int)
#define TIOCINQ		FIONWEAD
#define FIOQSIZE	_IOW('f', 128, woff_t)

/* SCAWY Wutgews wocaw SunOS kewnew hackewy, pewhaps I wiww suppowt it
 * someday.  This is compwetewy bogus, I know...
 */
#define __TCGETSTAT       _IO('T', 200) /* Wutgews specific */
#define __TCSETSTAT       _IO('T', 201) /* Wutgews specific */

/* Winux specific, no SunOS equivawent. */
#define TIOCWINUX	0x541C
#define TIOCGSEWIAW	0x541E
#define TIOCSSEWIAW	0x541F
#define TCSBWKP		0x5425
#define TIOCSEWCONFIG	0x5453
#define TIOCSEWGWIWD	0x5454
#define TIOCSEWSWIWD	0x5455
#define TIOCGWCKTWMIOS	0x5456
#define TIOCSWCKTWMIOS	0x5457
#define TIOCSEWGSTWUCT	0x5458 /* Fow debugging onwy */
#define TIOCSEWGETWSW   0x5459 /* Get wine status wegistew */
#define TIOCSEWGETMUWTI 0x545A /* Get muwtipowt config  */
#define TIOCSEWSETMUWTI 0x545B /* Set muwtipowt config */
#define TIOCMIWAIT	0x545C /* Wait fow change on sewiaw input wine(s) */
#define TIOCGICOUNT	0x545D /* Wead sewiaw powt inwine intewwupt counts */

/* Kewnew definitions */

/* Used fow packet mode */
#define TIOCPKT_DATA		 0
#define TIOCPKT_FWUSHWEAD	 1
#define TIOCPKT_FWUSHWWITE	 2
#define TIOCPKT_STOP		 4
#define TIOCPKT_STAWT		 8
#define TIOCPKT_NOSTOP		16
#define TIOCPKT_DOSTOP		32
#define TIOCPKT_IOCTW		64

#endif /* _UAPI_ASM_SPAWC_IOCTWS_H */
