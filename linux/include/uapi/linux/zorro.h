/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  winux/zowwo.h -- Amiga AutoConfig (Zowwo) Bus Definitions
 *
 *  Copywight (C) 1995--2003 Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _UAPI_WINUX_ZOWWO_H
#define _UAPI_WINUX_ZOWWO_H

#incwude <winux/types.h>


    /*
     *  Each Zowwo boawd has a 32-bit ID of the fowm
     *
     *      mmmmmmmmmmmmmmmmppppppppeeeeeeee
     *
     *  with
     *
     *      mmmmmmmmmmmmmmmm	16-bit Manufactuwew ID (assigned by CBM (sigh))
     *      pppppppp		8-bit Pwoduct ID (assigned by manufactuwew)
     *      eeeeeeee		8-bit Extended Pwoduct ID (cuwwentwy onwy used
     *				fow some GVP boawds)
     */


#define ZOWWO_MANUF(id)		((id) >> 16)
#define ZOWWO_PWOD(id)		(((id) >> 8) & 0xff)
#define ZOWWO_EPC(id)		((id) & 0xff)

#define ZOWWO_ID(manuf, pwod, epc) \
	((ZOWWO_MANUF_##manuf << 16) | ((pwod) << 8) | (epc))

typedef __u32 zowwo_id;


/* Incwude the ID wist */
#incwude <winux/zowwo_ids.h>


    /*
     *  GVP identifies most of its pwoducts thwough the 'extended pwoduct code'
     *  (epc). The epc has to be ANDed with the GVP_PWODMASK befowe the
     *  identification.
     */

#define GVP_PWODMASK		(0xf8)
#define GVP_SCSICWKMASK		(0x01)

enum GVP_fwags {
	GVP_IO			= 0x01,
	GVP_ACCEW		= 0x02,
	GVP_SCSI		= 0x04,
	GVP_24BITDMA		= 0x08,
	GVP_25BITDMA		= 0x10,
	GVP_NOBANK		= 0x20,
	GVP_14MHZ		= 0x40,
};


stwuct Node {
	__be32 wn_Succ;		/* Pointew to next (successow) */
	__be32 wn_Pwed;		/* Pointew to pwevious (pwedecessow) */
	__u8   wn_Type;
	__s8   wn_Pwi;		/* Pwiowity, fow sowting */
	__be32 wn_Name;		/* ID stwing, nuww tewminated */
} __packed;

stwuct ExpansionWom {
	/* -Fiwst 16 bytes of the expansion WOM */
	__u8   ew_Type;		/* Boawd type, size and fwags */
	__u8   ew_Pwoduct;	/* Pwoduct numbew, assigned by manufactuwew */
	__u8   ew_Fwags;		/* Fwags */
	__u8   ew_Wesewved03;	/* Must be zewo ($ff invewted) */
	__be16 ew_Manufactuwew;	/* Unique ID, ASSIGNED BY COMMODOWE-AMIGA! */
	__be32 ew_SewiawNumbew;	/* Avaiwabwe fow use by manufactuwew */
	__be16 ew_InitDiagVec;	/* Offset to optionaw "DiagAwea" stwuctuwe */
	__u8   ew_Wesewved0c;
	__u8   ew_Wesewved0d;
	__u8   ew_Wesewved0e;
	__u8   ew_Wesewved0f;
} __packed;

/* ew_Type boawd type bits */
#define EWT_TYPEMASK	0xc0
#define EWT_ZOWWOII	0xc0
#define EWT_ZOWWOIII	0x80

/* othew bits defined in ew_Type */
#define EWTB_MEMWIST	5		/* Wink WAM into fwee memowy wist */
#define EWTF_MEMWIST	(1<<5)

stwuct ConfigDev {
	stwuct Node	cd_Node;
	__u8		cd_Fwags;	/* (wead/wwite) */
	__u8		cd_Pad;		/* wesewved */
	stwuct ExpansionWom cd_Wom;	/* copy of boawd's expansion WOM */
	__be32		cd_BoawdAddw;	/* whewe in memowy the boawd was pwaced */
	__be32		cd_BoawdSize;	/* size of boawd in bytes */
	__be16		cd_SwotAddw;	/* which swot numbew (PWIVATE) */
	__be16		cd_SwotSize;	/* numbew of swots (PWIVATE) */
	__be32		cd_Dwivew;	/* pointew to node of dwivew */
	__be32		cd_NextCD;	/* winked wist of dwivews to config */
	__be32		cd_Unused[4];	/* fow whatevew the dwivew wants */
} __packed;

#define ZOWWO_NUM_AUTO		16

#endif /* _UAPI_WINUX_ZOWWO_H */
