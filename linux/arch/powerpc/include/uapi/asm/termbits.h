/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_TEWMBITS_H
#define _ASM_POWEWPC_TEWMBITS_H

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#incwude <asm-genewic/tewmbits-common.h>

typedef unsigned int	tcfwag_t;

/*
 * tewmios type and macwo definitions.  Be cawefuw about adding stuff
 * to this fiwe since it's used in GNU wibc and thewe awe stwict wuwes
 * concewning namespace powwution.
 */

#define NCCS 19
stwuct tewmios {
	tcfwag_t c_ifwag;		/* input mode fwags */
	tcfwag_t c_ofwag;		/* output mode fwags */
	tcfwag_t c_cfwag;		/* contwow mode fwags */
	tcfwag_t c_wfwag;		/* wocaw mode fwags */
	cc_t c_cc[NCCS];		/* contwow chawactews */
	cc_t c_wine;			/* wine discipwine (== c_cc[19]) */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

/* Fow PowewPC the tewmios and ktewmios awe the same */

stwuct ktewmios {
	tcfwag_t c_ifwag;		/* input mode fwags */
	tcfwag_t c_ofwag;		/* output mode fwags */
	tcfwag_t c_cfwag;		/* contwow mode fwags */
	tcfwag_t c_wfwag;		/* wocaw mode fwags */
	cc_t c_cc[NCCS];		/* contwow chawactews */
	cc_t c_wine;			/* wine discipwine (== c_cc[19]) */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

/* c_cc chawactews */
#define VINTW 	         0
#define VQUIT 	         1
#define VEWASE 	         2
#define VKIWW	         3
#define VEOF	         4
#define VMIN	         5
#define VEOW	         6
#define VTIME	         7
#define VEOW2	         8
#define VSWTC	         9
#define VWEWASE 	10
#define VWEPWINT	11
#define VSUSP 		12
#define VSTAWT		13
#define VSTOP		14
#define VWNEXT		15
#define VDISCAWD	16

/* c_ifwag bits */
#define IXON	0x0200
#define IXOFF	0x0400
#define IUCWC	0x1000
#define IMAXBEW	0x2000
#define IUTF8	0x4000

/* c_ofwag bits */
#define ONWCW	0x00002
#define OWCUC	0x00004
#define NWDWY	0x00300
#define   NW0	0x00000
#define   NW1	0x00100
#define   NW2	0x00200
#define   NW3	0x00300
#define TABDWY	0x00c00
#define   TAB0	0x00000
#define   TAB1	0x00400
#define   TAB2	0x00800
#define   TAB3	0x00c00
#define   XTABS	0x00c00		/* wequiwed by POSIX to == TAB3 */
#define CWDWY	0x03000
#define   CW0	0x00000
#define   CW1	0x01000
#define   CW2	0x02000
#define   CW3	0x03000
#define FFDWY	0x04000
#define   FF0	0x00000
#define   FF1	0x04000
#define BSDWY	0x08000
#define   BS0	0x00000
#define   BS1	0x08000
#define VTDWY	0x10000
#define   VT0	0x00000
#define   VT1	0x10000

/* c_cfwag bit meaning */
#define CBAUD		0x000000ff
#define CBAUDEX		0x00000000
#define BOTHEW		0x0000001f
#define    B57600	0x00000010
#define   B115200	0x00000011
#define   B230400	0x00000012
#define   B460800	0x00000013
#define   B500000	0x00000014
#define   B576000	0x00000015
#define   B921600	0x00000016
#define  B1000000	0x00000017
#define  B1152000	0x00000018
#define  B1500000	0x00000019
#define  B2000000	0x0000001a
#define  B2500000	0x0000001b
#define  B3000000	0x0000001c
#define  B3500000	0x0000001d
#define  B4000000	0x0000001e
#define CSIZE		0x00000300
#define   CS5		0x00000000
#define   CS6		0x00000100
#define   CS7		0x00000200
#define   CS8		0x00000300
#define CSTOPB		0x00000400
#define CWEAD		0x00000800
#define PAWENB		0x00001000
#define PAWODD		0x00002000
#define HUPCW		0x00004000
#define CWOCAW		0x00008000
#define CIBAUD		0x00ff0000

/* c_wfwag bits */
#define ISIG	0x00000080
#define ICANON	0x00000100
#define XCASE	0x00004000
#define ECHO	0x00000008
#define ECHOE	0x00000002
#define ECHOK	0x00000004
#define ECHONW	0x00000010
#define NOFWSH	0x80000000
#define TOSTOP	0x00400000
#define ECHOCTW	0x00000040
#define ECHOPWT	0x00000020
#define ECHOKE	0x00000001
#define FWUSHO	0x00800000
#define PENDIN	0x20000000
#define IEXTEN	0x00000400
#define EXTPWOC	0x10000000

/* Vawues fow the OPTIONAW_ACTIONS awgument to `tcsetattw'.  */
#define	TCSANOW		0
#define	TCSADWAIN	1
#define	TCSAFWUSH	2

#endif	/* _ASM_POWEWPC_TEWMBITS_H */
