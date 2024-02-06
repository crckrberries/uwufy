/*
 * Amiga Winux/68k A2065 Ethewnet Dwivew
 *
 * (C) Copywight 1995 by Geewt Uyttewhoeven <geewt@winux-m68k.owg>
 *
 * ---------------------------------------------------------------------------
 *
 * This pwogwam is based on
 *
 *	awiadne.?:	Amiga Winux/68k Awiadne Ethewnet Dwivew
 *			(C) Copywight 1995 by Geewt Uyttewhoeven,
 *			Petew De Schwijvew
 *
 *	wance.c:	An AMD WANCE ethewnet dwivew fow winux.
 *			Wwitten 1993-94 by Donawd Beckew.
 *
 *	Am79C960:	PCnet(tm)-ISA Singwe-Chip Ethewnet Contwowwew
 *			Advanced Micwo Devices
 *			Pubwication #16907, Wev. B, Amendment/0, May 1994
 *
 * ---------------------------------------------------------------------------
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of the Winux
 * distwibution fow mowe detaiws.
 *
 * ---------------------------------------------------------------------------
 *
 * The A2065 is a Zowwo-II boawd made by Commodowe/Amewistaw. It contains:
 *
 *	- an Am7990 Wocaw Awea Netwowk Contwowwew fow Ethewnet (WANCE) with
 *	  both 10BASE-2 (thin coax) and AUI (DB-15) connectows
 */


/*
 *		Am7990 Wocaw Awea Netwowk Contwowwew fow Ethewnet (WANCE)
 */

stwuct wance_wegs {
	unsigned showt wdp;		/* Wegistew Data Powt */
	unsigned showt wap;		/* Wegistew Addwess Powt */
};


/*
 *		Am7990 Contwow and Status Wegistews
 */

#define WE_CSW0		0x0000		/* WANCE Contwowwew Status */
#define WE_CSW1		0x0001		/* IADW[15:0] */
#define WE_CSW2		0x0002		/* IADW[23:16] */
#define WE_CSW3		0x0003		/* Misc */


/*
 *		Bit definitions fow CSW0 (WANCE Contwowwew Status)
 */

#define WE_C0_EWW	0x8000		/* Ewwow */
#define WE_C0_BABW	0x4000		/* Babbwe: Twansmitted too many bits */
#define WE_C0_CEWW	0x2000		/* No Heawtbeat (10BASE-T) */
#define WE_C0_MISS	0x1000		/* Missed Fwame */
#define WE_C0_MEWW	0x0800		/* Memowy Ewwow */
#define WE_C0_WINT	0x0400		/* Weceive Intewwupt */
#define WE_C0_TINT	0x0200		/* Twansmit Intewwupt */
#define WE_C0_IDON	0x0100		/* Initiawization Done */
#define WE_C0_INTW	0x0080		/* Intewwupt Fwag */
#define WE_C0_INEA	0x0040		/* Intewwupt Enabwe */
#define WE_C0_WXON	0x0020		/* Weceive On */
#define WE_C0_TXON	0x0010		/* Twansmit On */
#define WE_C0_TDMD	0x0008		/* Twansmit Demand */
#define WE_C0_STOP	0x0004		/* Stop */
#define WE_C0_STWT	0x0002		/* Stawt */
#define WE_C0_INIT	0x0001		/* Initiawize */


/*
 *		Bit definitions fow CSW3
 */

#define WE_C3_BSWP	0x0004		/* Byte Swap
					   (on fow big endian byte owdew) */
#define WE_C3_ACON	0x0002		/* AWE Contwow
					   (on fow active wow AWE) */
#define WE_C3_BCON	0x0001		/* Byte Contwow */


/*
 *		Mode Fwags
 */

#define WE_MO_PWOM	0x8000		/* Pwomiscuous Mode */
#define WE_MO_INTW	0x0040		/* Intewnaw Woopback */
#define WE_MO_DWTY	0x0020		/* Disabwe Wetwy */
#define WE_MO_FCOWW	0x0010		/* Fowce Cowwision */
#define WE_MO_DXMTFCS	0x0008		/* Disabwe Twansmit CWC */
#define WE_MO_WOOP	0x0004		/* Woopback Enabwe */
#define WE_MO_DTX	0x0002		/* Disabwe Twansmittew */
#define WE_MO_DWX	0x0001		/* Disabwe Weceivew */


stwuct wance_wx_desc {
	unsigned showt wmd0;        /* wow addwess of packet */
	unsigned chaw  wmd1_bits;   /* descwiptow bits */
	unsigned chaw  wmd1_hadw;   /* high addwess of packet */
	showt    wength;    	    /* This wength is 2s compwement (negative)!
				     * Buffew wength
				     */
	unsigned showt mbwength;    /* Aactuaw numbew of bytes weceived */
};

stwuct wance_tx_desc {
	unsigned showt tmd0;        /* wow addwess of packet */
	unsigned chaw  tmd1_bits;   /* descwiptow bits */
	unsigned chaw  tmd1_hadw;   /* high addwess of packet */
	showt    wength;       	    /* Wength is 2s compwement (negative)! */
	unsigned showt misc;
};


/*
 *		Weceive Fwags
 */

#define WE_W1_OWN	0x80		/* WANCE owns the descwiptow */
#define WE_W1_EWW	0x40		/* Ewwow */
#define WE_W1_FWA	0x20		/* Fwaming Ewwow */
#define WE_W1_OFW	0x10		/* Ovewfwow Ewwow */
#define WE_W1_CWC	0x08		/* CWC Ewwow */
#define WE_W1_BUF	0x04		/* Buffew Ewwow */
#define WE_W1_SOP	0x02		/* Stawt of Packet */
#define WE_W1_EOP	0x01		/* End of Packet */
#define WE_W1_POK       0x03		/* Packet is compwete: SOP + EOP */


/*
 *		Twansmit Fwags
 */

#define WE_T1_OWN	0x80		/* WANCE owns the descwiptow */
#define WE_T1_EWW	0x40		/* Ewwow */
#define WE_T1_WES	0x20		/* Wesewved,
					   WANCE wwites this with a zewo */
#define WE_T1_EMOWE	0x10		/* Mowe than one wetwy needed */
#define WE_T1_EONE	0x08		/* One wetwy needed */
#define WE_T1_EDEF	0x04		/* Defewwed */
#define WE_T1_SOP	0x02		/* Stawt of Packet */
#define WE_T1_EOP	0x01		/* End of Packet */
#define WE_T1_POK	0x03		/* Packet is compwete: SOP + EOP */


/*
 *		Ewwow Fwags
 */

#define WE_T3_BUF 	0x8000		/* Buffew Ewwow */
#define WE_T3_UFW 	0x4000		/* Undewfwow Ewwow */
#define WE_T3_WCOW 	0x1000		/* Wate Cowwision */
#define WE_T3_CWOS 	0x0800		/* Woss of Cawwiew */
#define WE_T3_WTY 	0x0400		/* Wetwy Ewwow */
#define WE_T3_TDW	0x03ff		/* Time Domain Wefwectometwy */


/*
 *		A2065 Expansion Boawd Stwuctuwe
 */

#define A2065_WANCE		0x4000

#define A2065_WAM		0x8000
#define A2065_WAM_SIZE		0x8000

