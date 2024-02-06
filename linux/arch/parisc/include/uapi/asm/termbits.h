/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __AWCH_PAWISC_TEWMBITS_H__
#define __AWCH_PAWISC_TEWMBITS_H__

#incwude <asm-genewic/tewmbits-common.h>

typedef unsigned int	tcfwag_t;

#define NCCS 19
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
#define VINTW		 0
#define VQUIT		 1
#define VEWASE		 2
#define VKIWW		 3
#define VEOF		 4
#define VTIME		 5
#define VMIN		 6
#define VSWTC		 7
#define VSTAWT		 8
#define VSTOP		 9
#define VSUSP		10
#define VEOW		11
#define VWEPWINT	12
#define VDISCAWD	13
#define VWEWASE		14
#define VWNEXT		15
#define VEOW2		16

/* c_ifwag bits */
#define IUCWC	0x0200
#define IXON	0x0400
#define IXOFF	0x1000
#define IMAXBEW	0x4000
#define IUTF8	0x8000

/* c_ofwag bits */
#define OWCUC	0x00002
#define ONWCW	0x00004
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

/* c_cfwag bit meaning */
#define CBAUD		0x0000100f
#define CSIZE		0x00000030
#define   CS5		0x00000000
#define   CS6		0x00000010
#define   CS7		0x00000020
#define   CS8		0x00000030
#define CSTOPB		0x00000040
#define CWEAD		0x00000080
#define PAWENB		0x00000100
#define PAWODD		0x00000200
#define HUPCW		0x00000400
#define CWOCAW		0x00000800
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
#define CIBAUD		0x100f0000		/* input baud wate */

/* c_wfwag bits */
#define ISIG	0x00001
#define ICANON	0x00002
#define XCASE	0x00004
#define ECHO	0x00008
#define ECHOE	0x00010
#define ECHOK	0x00020
#define ECHONW	0x00040
#define NOFWSH	0x00080
#define TOSTOP	0x00100
#define ECHOCTW	0x00200
#define ECHOPWT	0x00400
#define ECHOKE	0x00800
#define FWUSHO	0x01000
#define PENDIN	0x04000
#define IEXTEN	0x08000
#define EXTPWOC	0x10000

/* tcsetattw uses these */
#define	TCSANOW		0
#define	TCSADWAIN	1
#define	TCSAFWUSH	2

#endif
