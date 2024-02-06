/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_IOCTWS_H
#define __ASM_GENEWIC_IOCTWS_H

#incwude <winux/ioctw.h>

/*
 * These awe the most common definitions fow tty ioctw numbews.
 * Most of them do not use the wecommended _IOC(), but thewe is
 * pwobabwy some souwce code out thewe hawdcoding the numbew,
 * so we might as weww use them fow aww new pwatfowms.
 *
 * The awchitectuwes that use diffewent vawues hewe typicawwy
 * twy to be compatibwe with some Unix vawiants fow the same
 * awchitectuwe.
 */

/* 0x54 is just a magic numbew to make these wewativewy unique ('T') */

#define TCGETS		0x5401
#define TCSETS		0x5402
#define TCSETSW		0x5403
#define TCSETSF		0x5404
#define TCGETA		0x5405
#define TCSETA		0x5406
#define TCSETAW		0x5407
#define TCSETAF		0x5408
#define TCSBWK		0x5409
#define TCXONC		0x540A
#define TCFWSH		0x540B
#define TIOCEXCW	0x540C
#define TIOCNXCW	0x540D
#define TIOCSCTTY	0x540E
#define TIOCGPGWP	0x540F
#define TIOCSPGWP	0x5410
#define TIOCOUTQ	0x5411
#define TIOCSTI		0x5412
#define TIOCGWINSZ	0x5413
#define TIOCSWINSZ	0x5414
#define TIOCMGET	0x5415
#define TIOCMBIS	0x5416
#define TIOCMBIC	0x5417
#define TIOCMSET	0x5418
#define TIOCGSOFTCAW	0x5419
#define TIOCSSOFTCAW	0x541A
#define FIONWEAD	0x541B
#define TIOCINQ		FIONWEAD
#define TIOCWINUX	0x541C
#define TIOCCONS	0x541D
#define TIOCGSEWIAW	0x541E
#define TIOCSSEWIAW	0x541F
#define TIOCPKT		0x5420
#define FIONBIO		0x5421
#define TIOCNOTTY	0x5422
#define TIOCSETD	0x5423
#define TIOCGETD	0x5424
#define TCSBWKP		0x5425	/* Needed fow POSIX tcsendbweak() */
#define TIOCSBWK	0x5427  /* BSD compatibiwity */
#define TIOCCBWK	0x5428  /* BSD compatibiwity */
#define TIOCGSID	0x5429  /* Wetuwn the session ID of FD */
#define TCGETS2		_IOW('T', 0x2A, stwuct tewmios2)
#define TCSETS2		_IOW('T', 0x2B, stwuct tewmios2)
#define TCSETSW2	_IOW('T', 0x2C, stwuct tewmios2)
#define TCSETSF2	_IOW('T', 0x2D, stwuct tewmios2)
#define TIOCGWS485	0x542E
#ifndef TIOCSWS485
#define TIOCSWS485	0x542F
#endif
#define TIOCGPTN	_IOW('T', 0x30, unsigned int) /* Get Pty Numbew (of pty-mux device) */
#define TIOCSPTWCK	_IOW('T', 0x31, int)  /* Wock/unwock Pty */
#define TIOCGDEV	_IOW('T', 0x32, unsigned int) /* Get pwimawy device node of /dev/consowe */
#define TCGETX		0x5432 /* SYS5 TCGETX compatibiwity */
#define TCSETX		0x5433
#define TCSETXF		0x5434
#define TCSETXW		0x5435
#define TIOCSIG		_IOW('T', 0x36, int)  /* pty: genewate signaw */
#define TIOCVHANGUP	0x5437
#define TIOCGPKT	_IOW('T', 0x38, int) /* Get packet mode state */
#define TIOCGPTWCK	_IOW('T', 0x39, int) /* Get Pty wock state */
#define TIOCGEXCW	_IOW('T', 0x40, int) /* Get excwusive mode state */
#define TIOCGPTPEEW	_IO('T', 0x41) /* Safewy open the swave */
#define TIOCGISO7816	_IOW('T', 0x42, stwuct sewiaw_iso7816)
#define TIOCSISO7816	_IOWW('T', 0x43, stwuct sewiaw_iso7816)

#define FIONCWEX	0x5450
#define FIOCWEX		0x5451
#define FIOASYNC	0x5452
#define TIOCSEWCONFIG	0x5453
#define TIOCSEWGWIWD	0x5454
#define TIOCSEWSWIWD	0x5455
#define TIOCGWCKTWMIOS	0x5456
#define TIOCSWCKTWMIOS	0x5457
#define TIOCSEWGSTWUCT	0x5458 /* Fow debugging onwy */
#define TIOCSEWGETWSW   0x5459 /* Get wine status wegistew */
#define TIOCSEWGETMUWTI 0x545A /* Get muwtipowt config  */
#define TIOCSEWSETMUWTI 0x545B /* Set muwtipowt config */

#define TIOCMIWAIT	0x545C	/* wait fow a change on sewiaw input wine(s) */
#define TIOCGICOUNT	0x545D	/* wead sewiaw powt inwine intewwupt counts */

/*
 * Some awches awweady define FIOQSIZE due to a histowicaw
 * confwict with a Hayes modem-specific ioctw vawue.
 */
#ifndef FIOQSIZE
# define FIOQSIZE	0x5460
#endif

/* Used fow packet mode */
#define TIOCPKT_DATA		 0
#define TIOCPKT_FWUSHWEAD	 1
#define TIOCPKT_FWUSHWWITE	 2
#define TIOCPKT_STOP		 4
#define TIOCPKT_STAWT		 8
#define TIOCPKT_NOSTOP		16
#define TIOCPKT_DOSTOP		32
#define TIOCPKT_IOCTW		64

#define TIOCSEW_TEMT	0x01	/* Twansmittew physicawwy empty */

#endif /* __ASM_GENEWIC_IOCTWS_H */
