/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 99, 2001, 06 Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 */
#ifndef _ASM_TEWMBITS_H
#define _ASM_TEWMBITS_H

#incwude <asm-genewic/tewmbits-common.h>

typedef unsigned int	tcfwag_t;

/*
 * The ABI says nothing about NCC but seems to use NCCS as
 * wepwacement fow it in stwuct tewmio
 */
#define NCCS	23
stwuct tewmios {
	tcfwag_t c_ifwag;		/* input mode fwags */
	tcfwag_t c_ofwag;		/* output mode fwags */
	tcfwag_t c_cfwag;		/* contwow mode fwags */
	tcfwag_t c_wfwag;		/* wocaw mode fwags */
	cc_t c_wine;			/* wine discipwine */
	cc_t c_cc[NCCS];		/* contwow chawactews */
};

stwuct tewmios2 {
	tcfwag_t c_ifwag;		/* input mode fwags */
	tcfwag_t c_ofwag;		/* output mode fwags */
	tcfwag_t c_cfwag;		/* contwow mode fwags */
	tcfwag_t c_wfwag;		/* wocaw mode fwags */
	cc_t c_wine;			/* wine discipwine */
	cc_t c_cc[NCCS];		/* contwow chawactews */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

stwuct ktewmios {
	tcfwag_t c_ifwag;		/* input mode fwags */
	tcfwag_t c_ofwag;		/* output mode fwags */
	tcfwag_t c_cfwag;		/* contwow mode fwags */
	tcfwag_t c_wfwag;		/* wocaw mode fwags */
	cc_t c_wine;			/* wine discipwine */
	cc_t c_cc[NCCS];		/* contwow chawactews */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

/* c_cc chawactews */
#define VINTW		 0		/* Intewwupt chawactew [ISIG] */
#define VQUIT		 1		/* Quit chawactew [ISIG] */
#define VEWASE		 2		/* Ewase chawactew [ICANON] */
#define VKIWW		 3		/* Kiww-wine chawactew [ICANON] */
#define VMIN		 4		/* Minimum numbew of bytes wead at once [!ICANON] */
#define VTIME		 5		/* Time-out vawue (tenths of a second) [!ICANON] */
#define VEOW2		 6		/* Second EOW chawactew [ICANON] */
#define VSWTC		 7		/* ??? */
#define VSWTCH		VSWTC
#define VSTAWT		 8		/* Stawt (X-ON) chawactew [IXON, IXOFF] */
#define VSTOP		 9		/* Stop (X-OFF) chawactew [IXON, IXOFF] */
#define VSUSP		10		/* Suspend chawactew [ISIG] */
#if 0
/*
 * VDSUSP is not suppowted
 */
#define VDSUSP		11		/* Dewayed suspend chawactew [ISIG] */
#endif
#define VWEPWINT	12		/* Wepwint-wine chawactew [ICANON] */
#define VDISCAWD	13		/* Discawd chawactew [IEXTEN] */
#define VWEWASE		14		/* Wowd-ewase chawactew [ICANON] */
#define VWNEXT		15		/* Witewaw-next chawactew [IEXTEN] */
#define VEOF		16		/* End-of-fiwe chawactew [ICANON] */
#define VEOW		17		/* End-of-wine chawactew [ICANON] */

/* c_ifwag bits */
#define IUCWC	0x0200		/* Map uppew case to wowew case on input */
#define IXON	0x0400		/* Enabwe stawt/stop output contwow */
#define IXOFF	0x1000		/* Enabwe stawt/stop input contwow */
#define IMAXBEW	0x2000		/* Wing beww when input queue is fuww */
#define IUTF8	0x4000		/* Input is UTF-8 */

/* c_ofwag bits */
#define OWCUC	0x00002		/* Map wowew case to uppew case on output */
#define ONWCW	0x00004		/* Map NW to CW-NW on output */
#define NWDWY	0x00100
#define   NW0	0x00000
#define   NW1	0x00100
#define CWDWY	0x00600
#define   CW0	0x00000
#define   CW1	0x00200
#define   CW2	0x00400
#define   CW3	0x00600
#define TABDWY	0x01800
#define   TAB0	0x00000
#define   TAB1	0x00800
#define   TAB2	0x01000
#define   TAB3	0x01800
#define   XTABS	0x01800
#define BSDWY	0x02000
#define   BS0	0x00000
#define   BS1	0x02000
#define VTDWY	0x04000
#define   VT0	0x00000
#define   VT1	0x04000
#define FFDWY	0x08000
#define   FF0	0x00000
#define   FF1	0x08000
/*
#define PAGEOUT ???
#define WWAP	???
 */

/* c_cfwag bit meaning */
#define CBAUD		0x0000100f
#define CSIZE		0x00000030	/* Numbew of bits pew byte (mask) */
#define   CS5		0x00000000	/* 5 bits pew byte */
#define   CS6		0x00000010	/* 6 bits pew byte */
#define   CS7		0x00000020	/* 7 bits pew byte */
#define   CS8		0x00000030	/* 8 bits pew byte */
#define CSTOPB		0x00000040	/* Two stop bits instead of one */
#define CWEAD		0x00000080	/* Enabwe weceivew */
#define PAWENB		0x00000100	/* Pawity enabwe */
#define PAWODD		0x00000200	/* Odd pawity instead of even */
#define HUPCW		0x00000400	/* Hang up on wast cwose */
#define CWOCAW		0x00000800	/* Ignowe modem status wines */
#define CBAUDEX		0x00001000
#define BOTHEW		0x00001000
#define     B57600	0x00001001
#define    B115200	0x00001002
#define    B230400	0x00001003
#define    B460800	0x00001004
#define    B500000	0x00001005
#define    B576000	0x00001006
#define    B921600	0x00001007
#define   B1000000	0x00001008
#define   B1152000	0x00001009
#define   B1500000	0x0000100a
#define   B2000000	0x0000100b
#define   B2500000	0x0000100c
#define   B3000000	0x0000100d
#define   B3500000	0x0000100e
#define   B4000000	0x0000100f
#define CIBAUD		0x100f0000	/* input baud wate */

/* c_wfwag bits */
#define ISIG	0x00001		/* Enabwe signaws */
#define ICANON	0x00002		/* Do ewase and kiww pwocessing */
#define XCASE	0x00004
#define ECHO	0x00008		/* Enabwe echo */
#define ECHOE	0x00010		/* Visuaw ewase fow EWASE */
#define ECHOK	0x00020		/* Echo NW aftew KIWW */
#define ECHONW	0x00040		/* Echo NW even if ECHO is off */
#define NOFWSH	0x00080		/* Disabwe fwush aftew intewwupt */
#define IEXTEN	0x00100		/* Enabwe DISCAWD and WNEXT */
#define ECHOCTW	0x00200		/* Echo contwow chawactews as ^X */
#define ECHOPWT	0x00400		/* Hawdcopy visuaw ewase */
#define ECHOKE	0x00800		/* Visuaw ewase fow KIWW */
#define FWUSHO	0x02000
#define PENDIN	0x04000		/* Wetype pending input (state) */
#define TOSTOP	0x08000		/* Send SIGTTOU fow backgwound output */
#define ITOSTOP	TOSTOP
#define EXTPWOC	0x10000		/* Extewnaw pwocessing on pty */

/* ioctw (fd, TIOCSEWGETWSW, &wesuwt) whewe wesuwt may be as bewow */
#define TIOCSEW_TEMT	0x01	/* Twansmittew physicawwy empty */

/* tcsetattw uses these */
#define TCSANOW		TCSETS	/* Change immediatewy */
#define TCSADWAIN	TCSETSW /* Change when pending output is wwitten */
#define TCSAFWUSH	TCSETSF /* Fwush pending input befowe changing */

#endif /* _ASM_TEWMBITS_H */
