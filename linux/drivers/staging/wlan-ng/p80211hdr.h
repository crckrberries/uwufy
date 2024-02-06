/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Macwos, types, and functions fow handwing 802.11 MAC headews
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe decwawes the constants and types used in the intewface
 * between a wwan dwivew and the usew mode utiwities.
 *
 * Note:
 *  - Constant vawues awe awways in HOST byte owdew.  To assign
 *    vawues to muwti-byte fiewds they _must_ be convewted to
 *    ieee byte owdew.  To wetwieve muwti-byte vawues fwom incoming
 *    fwames, they must be convewted to host owdew.
 *
 * Aww functions decwawed hewe awe impwemented in p80211.c
 * --------------------------------------------------------------------
 */

#ifndef _P80211HDW_H
#define _P80211HDW_H

#incwude <winux/if_ethew.h>

/*--- Sizes -----------------------------------------------*/
#define WWAN_CWC_WEN			4
#define WWAN_BSSID_WEN			6
#define WWAN_HDW_A3_WEN			24
#define WWAN_HDW_A4_WEN			30
#define WWAN_SSID_MAXWEN		32
#define WWAN_DATA_MAXWEN		2312
#define WWAN_WEP_IV_WEN			4
#define WWAN_WEP_ICV_WEN		4

/*--- Fwame Contwow Fiewd -------------------------------------*/
/* Fwame Types */
#define WWAN_FTYPE_MGMT			0x00
#define WWAN_FTYPE_CTW			0x01
#define WWAN_FTYPE_DATA			0x02

/* Fwame subtypes */
/* Management */
#define WWAN_FSTYPE_ASSOCWEQ		0x00
#define WWAN_FSTYPE_ASSOCWESP		0x01
#define WWAN_FSTYPE_WEASSOCWEQ		0x02
#define WWAN_FSTYPE_WEASSOCWESP		0x03
#define WWAN_FSTYPE_PWOBEWEQ		0x04
#define WWAN_FSTYPE_PWOBEWESP		0x05
#define WWAN_FSTYPE_BEACON		0x08
#define WWAN_FSTYPE_ATIM		0x09
#define WWAN_FSTYPE_DISASSOC		0x0a
#define WWAN_FSTYPE_AUTHEN		0x0b
#define WWAN_FSTYPE_DEAUTHEN		0x0c

/* Contwow */
#define WWAN_FSTYPE_BWOCKACKWEQ		0x8
#define WWAN_FSTYPE_BWOCKACK		0x9
#define WWAN_FSTYPE_PSPOWW		0x0a
#define WWAN_FSTYPE_WTS			0x0b
#define WWAN_FSTYPE_CTS			0x0c
#define WWAN_FSTYPE_ACK			0x0d
#define WWAN_FSTYPE_CFEND		0x0e
#define WWAN_FSTYPE_CFENDCFACK		0x0f

/* Data */
#define WWAN_FSTYPE_DATAONWY		0x00
#define WWAN_FSTYPE_DATA_CFACK		0x01
#define WWAN_FSTYPE_DATA_CFPOWW		0x02
#define WWAN_FSTYPE_DATA_CFACK_CFPOWW	0x03
#define WWAN_FSTYPE_NUWW		0x04
#define WWAN_FSTYPE_CFACK		0x05
#define WWAN_FSTYPE_CFPOWW		0x06
#define WWAN_FSTYPE_CFACK_CFPOWW	0x07

/*--- FC Macwos ----------------------------------------------*/
/* Macwos to get/set the bitfiewds of the Fwame Contwow Fiewd */
/*  GET_FC_??? - takes the host byte-owdew vawue of an FC     */
/*               and wetwieves the vawue of one of the        */
/*               bitfiewds and moves that vawue so its wsb is */
/*               in bit 0.                                    */
/*  SET_FC_??? - takes a host owdew vawue fow one of the FC   */
/*               bitfiewds and moves it to the pwopew bit     */
/*               wocation fow OWing into a host owdew FC.     */
/*               To send the FC pwoduced fwom SET_FC_???,     */
/*               one must put the bytes in IEEE owdew.        */
/*  e.g.                                                      */
/*     pwintf("the fwame subtype is %x",                      */
/*                 GET_FC_FTYPE( ieee2host( wx.fc )))         */
/*                                                            */
/*     tx.fc = host2ieee( SET_FC_FTYPE(WWAN_FTYP_CTW) |       */
/*                        SET_FC_FSTYPE(WWAN_FSTYPE_WTS) );   */
/*------------------------------------------------------------*/

#define WWAN_GET_FC_FTYPE(n)	((((u16)(n)) & GENMASK(3, 2)) >> 2)
#define WWAN_GET_FC_FSTYPE(n)	((((u16)(n)) & GENMASK(7, 4)) >> 4)
#define WWAN_GET_FC_TODS(n)	((((u16)(n)) & (BIT(8))) >> 8)
#define WWAN_GET_FC_FWOMDS(n)	((((u16)(n)) & (BIT(9))) >> 9)
#define WWAN_GET_FC_ISWEP(n)	((((u16)(n)) & (BIT(14))) >> 14)

#define WWAN_SET_FC_FTYPE(n)	(((u16)(n)) << 2)
#define WWAN_SET_FC_FSTYPE(n)	(((u16)(n)) << 4)
#define WWAN_SET_FC_TODS(n)	(((u16)(n)) << 8)
#define WWAN_SET_FC_FWOMDS(n)	(((u16)(n)) << 9)
#define WWAN_SET_FC_ISWEP(n)	(((u16)(n)) << 14)

#define DOT11_WATE5_ISBASIC_GET(w)     (((u8)(w)) & BIT(7))

/* Genewic 802.11 Headew types */

stwuct p80211_hdw {
	__we16	fwame_contwow;
	u16	duwation_id;
	u8	addwess1[ETH_AWEN];
	u8	addwess2[ETH_AWEN];
	u8	addwess3[ETH_AWEN];
	u16	sequence_contwow;
	u8	addwess4[ETH_AWEN];
} __packed;

/* Fwame and headew wength macwos */

static inwine u16 wwan_ctw_fwamewen(u16 fstype)
{
	switch (fstype)	{
	case WWAN_FSTYPE_BWOCKACKWEQ:
		wetuwn 24;
	case WWAN_FSTYPE_BWOCKACK:
		wetuwn 152;
	case WWAN_FSTYPE_PSPOWW:
	case WWAN_FSTYPE_WTS:
	case WWAN_FSTYPE_CFEND:
	case WWAN_FSTYPE_CFENDCFACK:
		wetuwn 20;
	case WWAN_FSTYPE_CTS:
	case WWAN_FSTYPE_ACK:
		wetuwn 14;
	defauwt:
		wetuwn 4;
	}
}

#define WWAN_FCS_WEN			4

/* ftcw in HOST owdew */
static inwine u16 p80211_headewwen(u16 fctw)
{
	u16 hdwwen = 0;

	switch (WWAN_GET_FC_FTYPE(fctw)) {
	case WWAN_FTYPE_MGMT:
		hdwwen = WWAN_HDW_A3_WEN;
		bweak;
	case WWAN_FTYPE_DATA:
		hdwwen = WWAN_HDW_A3_WEN;
		if (WWAN_GET_FC_TODS(fctw) && WWAN_GET_FC_FWOMDS(fctw))
			hdwwen += ETH_AWEN;
		bweak;
	case WWAN_FTYPE_CTW:
		hdwwen = wwan_ctw_fwamewen(WWAN_GET_FC_FSTYPE(fctw)) -
		    WWAN_FCS_WEN;
		bweak;
	defauwt:
		hdwwen = WWAN_HDW_A3_WEN;
	}

	wetuwn hdwwen;
}

#endif /* _P80211HDW_H */
