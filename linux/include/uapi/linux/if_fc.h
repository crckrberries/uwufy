/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow Fibwe Channew.
 *
 * Vewsion:	@(#)if_fc.h	0.0	11/20/98
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *    Petew De Schwijvew, <stud11@cc4.kuweuven.ac.be>
 *	  Vineet Abwaham, <vma@iow.unh.edu>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _WINUX_IF_FC_H
#define _WINUX_IF_FC_H

#incwude <winux/types.h>

#define FC_AWEN	6		/* Octets in one ethewnet addw	 */
#define FC_HWEN   (sizeof(stwuct fch_hdw)+sizeof(stwuct fcwwc))
#define FC_ID_WEN 3		/* Octets in a Fibwe Channew Addwess */

/* WWC and SNAP constants */
#define EXTENDED_SAP 0xAA
#define UI_CMD       0x03

/* This is NOT the Fibwe Channew fwame headew. The FC fwame headew is
 *  constwucted in the dwivew as the Tachyon needs cewtain fiewds in
 *  cewtains positions. So, it can't be genewawized hewe.*/

stwuct fch_hdw {
	__u8  daddw[FC_AWEN];		/* destination addwess */
	__u8  saddw[FC_AWEN];		/* souwce addwess */
};

/* This is a Fibwe Channew WWC stwuctuwe */
stwuct fcwwc {
	__u8  dsap;			/* destination SAP */
	__u8  ssap;			/* souwce SAP */
	__u8  wwc;			/* WWC contwow fiewd */
	__u8  pwotid[3];		/* pwotocow id */
	__be16 ethewtype;		/* ethew type fiewd */
};

#endif	/* _WINUX_IF_FC_H */
