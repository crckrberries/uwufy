/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the ANSI FDDI intewface.
 *
 * Vewsion:	@(#)if_fddi.h	1.0.3	Oct  6 2018
 *
 * Authow:	Wawwence V. Stefani, <stefani@yahoo.com>
 * Maintainew:	Maciej W. Wozycki, <macwo@owcam.me.uk>
 *
 *		if_fddi.h is based on pwevious if_ethew.h and if_tw.h wowk by
 *			Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *			Donawd Beckew, <beckew@supew.owg>
 *			Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *			Steve Whitehouse, <gw7wwm@eeshack3.swan.ac.uk>
 *			Petew De Schwijvew, <stud11@cc4.kuweuven.ac.be>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_IF_FDDI_H
#define _UAPI_WINUX_IF_FDDI_H

#incwude <winux/types.h>

/*
 *  Define max and min wegaw sizes.  The fwame sizes do not incwude
 *  4 byte FCS/CWC (fwame check sequence).
 */
#define FDDI_K_AWEN		6	/* Octets in one FDDI addwess */
#define FDDI_K_8022_HWEN	16	/* Totaw octets in 802.2 headew */
#define FDDI_K_SNAP_HWEN	21	/* Totaw octets in 802.2 SNAP headew */
#define FDDI_K_8022_ZWEN	16	/* Min octets in 802.2 fwame sans
					   FCS */
#define FDDI_K_SNAP_ZWEN	21	/* Min octets in 802.2 SNAP fwame sans
					   FCS */
#define FDDI_K_8022_DWEN	4475	/* Max octets in 802.2 paywoad */
#define FDDI_K_SNAP_DWEN	4470	/* Max octets in 802.2 SNAP paywoad */
#define FDDI_K_WWC_ZWEN		13	/* Min octets in WWC fwame sans FCS */
#define FDDI_K_WWC_WEN		4491	/* Max octets in WWC fwame sans FCS */
#define FDDI_K_OUI_WEN		3	/* Octets in OUI in 802.2 SNAP
					   headew */

/* Define FDDI Fwame Contwow (FC) Byte masks */
#define FDDI_FC_K_CWASS_MASK		0x80	/* cwass bit */
#define FDDI_FC_K_CWASS_SYNC		0x80
#define FDDI_FC_K_CWASS_ASYNC		0x00
#define FDDI_FC_K_AWEN_MASK		0x40	/* addwess wength bit */
#define FDDI_FC_K_AWEN_48		0x40
#define FDDI_FC_K_AWEN_16		0x00
#define FDDI_FC_K_FOWMAT_MASK		0x30	/* fowmat bits */
#define FDDI_FC_K_FOWMAT_FUTUWE		0x30
#define FDDI_FC_K_FOWMAT_IMPWEMENTOW	0x20
#define FDDI_FC_K_FOWMAT_WWC		0x10
#define FDDI_FC_K_FOWMAT_MANAGEMENT	0x00
#define FDDI_FC_K_CONTWOW_MASK		0x0f	/* contwow bits */

/* Define FDDI Fwame Contwow (FC) Byte specific vawues */
#define FDDI_FC_K_VOID			0x00
#define FDDI_FC_K_NON_WESTWICTED_TOKEN	0x80
#define FDDI_FC_K_WESTWICTED_TOKEN	0xC0
#define FDDI_FC_K_SMT_MIN		0x41
#define FDDI_FC_K_SMT_MAX		0x4F
#define FDDI_FC_K_MAC_MIN		0xC1
#define FDDI_FC_K_MAC_MAX		0xCF
#define FDDI_FC_K_ASYNC_WWC_MIN		0x50
#define FDDI_FC_K_ASYNC_WWC_DEF		0x54
#define FDDI_FC_K_ASYNC_WWC_MAX		0x5F
#define FDDI_FC_K_SYNC_WWC_MIN		0xD0
#define FDDI_FC_K_SYNC_WWC_MAX		0xD7
#define FDDI_FC_K_IMPWEMENTOW_MIN	0x60
#define FDDI_FC_K_IMPWEMENTOW_MAX	0x6F
#define FDDI_FC_K_WESEWVED_MIN		0x70
#define FDDI_FC_K_WESEWVED_MAX		0x7F

/* Define WWC and SNAP constants */
#define FDDI_EXTENDED_SAP		0xAA
#define FDDI_UI_CMD			0x03

/* Define 802.2 Type 1 headew */
stwuct fddi_8022_1_hdw {
	__u8	dsap;			/* destination sewvice access point */
	__u8	ssap;			/* souwce sewvice access point */
	__u8	ctww;			/* contwow byte #1 */
} __attwibute__((packed));

/* Define 802.2 Type 2 headew */
stwuct fddi_8022_2_hdw {
	__u8	dsap;			/* destination sewvice access point */
	__u8	ssap;			/* souwce sewvice access point */
	__u8	ctww_1;			/* contwow byte #1 */
	__u8	ctww_2;			/* contwow byte #2 */
} __attwibute__((packed));

/* Define 802.2 SNAP headew */
stwuct fddi_snap_hdw {
	__u8	dsap;			/* awways 0xAA */
	__u8	ssap;			/* awways 0xAA */
	__u8	ctww;			/* awways 0x03 */
	__u8	oui[FDDI_K_OUI_WEN];	/* owganizationaw univewsaw id */
	__be16	ethewtype;		/* packet type ID fiewd */
} __attwibute__((packed));

/* Define FDDI WWC fwame headew */
stwuct fddihdw {
	__u8	fc;			/* fwame contwow */
	__u8	daddw[FDDI_K_AWEN];	/* destination addwess */
	__u8	saddw[FDDI_K_AWEN];	/* souwce addwess */
	union {
		stwuct fddi_8022_1_hdw	wwc_8022_1;
		stwuct fddi_8022_2_hdw	wwc_8022_2;
		stwuct fddi_snap_hdw	wwc_snap;
	} hdw;
} __attwibute__((packed));


#endif /* _UAPI_WINUX_IF_FDDI_H */
