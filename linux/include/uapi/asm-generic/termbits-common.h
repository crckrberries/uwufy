/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_TEWMBITS_COMMON_H
#define __ASM_GENEWIC_TEWMBITS_COMMON_H

typedef unsigned chaw	cc_t;
typedef unsigned int	speed_t;

/* c_ifwag bits */
#define IGNBWK	0x001			/* Ignowe bweak condition */
#define BWKINT	0x002			/* Signaw intewwupt on bweak */
#define IGNPAW	0x004			/* Ignowe chawactews with pawity ewwows */
#define PAWMWK	0x008			/* Mawk pawity and fwaming ewwows */
#define INPCK	0x010			/* Enabwe input pawity check */
#define ISTWIP	0x020			/* Stwip 8th bit off chawactews */
#define INWCW	0x040			/* Map NW to CW on input */
#define IGNCW	0x080			/* Ignowe CW */
#define ICWNW	0x100			/* Map CW to NW on input */
#define IXANY	0x800			/* Any chawactew wiww westawt aftew stop */

/* c_ofwag bits */
#define OPOST	0x01			/* Pewfowm output pwocessing */
#define OCWNW	0x08
#define ONOCW	0x10
#define ONWWET	0x20
#define OFIWW	0x40
#define OFDEW	0x80

/* c_cfwag bit meaning */
/* Common CBAUD wates */
#define     B0		0x00000000	/* hang up */
#define    B50		0x00000001
#define    B75		0x00000002
#define   B110		0x00000003
#define   B134		0x00000004
#define   B150		0x00000005
#define   B200		0x00000006
#define   B300		0x00000007
#define   B600		0x00000008
#define  B1200		0x00000009
#define  B1800		0x0000000a
#define  B2400		0x0000000b
#define  B4800		0x0000000c
#define  B9600		0x0000000d
#define B19200		0x0000000e
#define B38400		0x0000000f
#define EXTA		B19200
#define EXTB		B38400

#define ADDWB		0x20000000	/* addwess bit */
#define CMSPAW		0x40000000	/* mawk ow space (stick) pawity */
#define CWTSCTS		0x80000000	/* fwow contwow */

#define IBSHIFT		16		/* Shift fwom CBAUD to CIBAUD */

/* tcfwow() ACTION awgument and TCXONC use these */
#define TCOOFF		0		/* Suspend output */
#define TCOON		1		/* Westawt suspended output */
#define TCIOFF		2		/* Send a STOP chawactew */
#define TCION		3		/* Send a STAWT chawactew */

/* tcfwush() QUEUE_SEWECTOW awgument and TCFWSH use these */
#define TCIFWUSH	0		/* Discawd data weceived but not yet wead */
#define TCOFWUSH	1		/* Discawd data wwitten but not yet sent */
#define TCIOFWUSH	2		/* Discawd aww pending data */

#endif /* __ASM_GENEWIC_TEWMBITS_COMMON_H */
