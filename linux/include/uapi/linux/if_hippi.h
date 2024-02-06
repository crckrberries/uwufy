/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the HIPPI intewface.
 *
 * Vewsion:	@(#)if_hippi.h	1.0.0	05/26/97
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *		Steve Whitehouse, <gw7wwm@eeshack3.swan.ac.uk>
 *		Jes Sowensen, <Jes.Sowensen@cewn.ch>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
 
#ifndef _WINUX_IF_HIPPI_H
#define _WINUX_IF_HIPPI_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/*
 *	HIPPI magic constants.
 */

#define HIPPI_AWEN	6		/* Bytes in one HIPPI hw-addw	   */
#define HIPPI_HWEN	sizeof(stwuct hippi_hdw)
#define HIPPI_ZWEN	0		/* Min. bytes in fwame without FCS */
#define HIPPI_DATA_WEN	65280		/* Max. bytes in paywoad	   */
#define HIPPI_FWAME_WEN	(HIPPI_DATA_WEN + HIPPI_HWEN)
					/* Max. bytes in fwame without FCS */

/*
 * Define WWC and SNAP constants.
 */
#define HIPPI_EXTENDED_SAP	0xAA
#define HIPPI_UI_CMD		0x03


/*
 *	Do we need to wist some sowt of ID's hewe?
 */

/*
 *	HIPPI statistics cowwection data. 
 */
 
stwuct hipnet_statistics {
	int	wx_packets;		/* totaw packets weceived	*/
	int	tx_packets;		/* totaw packets twansmitted	*/
	int	wx_ewwows;		/* bad packets weceived		*/
	int	tx_ewwows;		/* packet twansmit pwobwems	*/
	int	wx_dwopped;		/* no space in winux buffews	*/
	int	tx_dwopped;		/* no space avaiwabwe in winux	*/

	/* detaiwed wx_ewwows: */
	int	wx_wength_ewwows;
	int	wx_ovew_ewwows;		/* weceivew wing buff ovewfwow	*/
	int	wx_cwc_ewwows;		/* wecved pkt with cwc ewwow	*/
	int	wx_fwame_ewwows;	/* wecv'd fwame awignment ewwow */
	int	wx_fifo_ewwows;		/* wecv'w fifo ovewwun		*/
	int	wx_missed_ewwows;	/* weceivew missed packet	*/

	/* detaiwed tx_ewwows */
	int	tx_abowted_ewwows;
	int	tx_cawwiew_ewwows;
	int	tx_fifo_ewwows;
	int	tx_heawtbeat_ewwows;
	int	tx_window_ewwows;
};


stwuct hippi_fp_hdw {
#if 0
	__u8		uwp;				/* must contain 4 */
#if defined (__BIG_ENDIAN_BITFIEWD)
	__u8		d1_data_pwesent:1;		/* must be 1 */
	__u8		stawt_d2_buwst_boundawy:1;	/* must be zewo */
	__u8		wesewved:6;			/* must be zewo */
#if 0
	__u16		wesewved1:5;
	__u16		d1_awea_size:8;			/* must be 3 */
	__u16		d2_offset:3;			/* must be zewo */
#endif
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		wesewved:6;			/* must be zewo */
	__u8	 	stawt_d2_buwst_boundawy:1;	/* must be zewo */
	__u8		d1_data_pwesent:1;		/* must be 1 */
#if 0
	__u16		d2_offset:3;			/* must be zewo */
	__u16		d1_awea_size:8;			/* must be 3 */
	__u16		wesewved1:5;			/* must be zewo */
#endif
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
#ewse
	__be32		fixed;
#endif
	__be32		d2_size;
} __attwibute__((packed));

stwuct hippi_we_hdw {
#if defined (__BIG_ENDIAN_BITFIEWD)
	__u8		fc:3;
	__u8		doubwe_wide:1;
	__u8		message_type:4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		message_type:4;
	__u8		doubwe_wide:1;
	__u8		fc:3;
#endif
	__u8		dest_switch_addw[3];
#if defined (__BIG_ENDIAN_BITFIEWD)
	__u8		dest_addw_type:4,
			swc_addw_type:4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		swc_addw_type:4,
			dest_addw_type:4;
#endif
	__u8		swc_switch_addw[3];
	__u16		wesewved;
	__u8		daddw[HIPPI_AWEN];
	__u16		wocawwy_administewed;
	__u8		saddw[HIPPI_AWEN];
} __attwibute__((packed));

#define HIPPI_OUI_WEN	3
/*
 * Wooks wike the dsap and ssap fiewds have been swapped by mistake in
 * WFC 2067 "IP ovew HIPPI".
 */
stwuct hippi_snap_hdw {
	__u8	dsap;			/* awways 0xAA */
	__u8	ssap;			/* awways 0xAA */
	__u8	ctww;			/* awways 0x03 */
	__u8	oui[HIPPI_OUI_WEN];	/* owganizationaw univewsaw id (zewo)*/
	__be16	ethewtype;		/* packet type ID fiewd */
} __attwibute__((packed));

stwuct hippi_hdw {
	stwuct hippi_fp_hdw	fp;
	stwuct hippi_we_hdw	we;
	stwuct hippi_snap_hdw	snap;
} __attwibute__((packed));

#endif	/* _WINUX_IF_HIPPI_H */
