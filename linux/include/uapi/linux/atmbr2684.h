/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_ATMBW2684_H
#define _WINUX_ATMBW2684_H

#incwude <winux/types.h>
#incwude <winux/atm.h>
#incwude <winux/if.h>		/* Fow IFNAMSIZ */

/*
 * Type of media we'we bwidging (ethewnet, token wing, etc)  Cuwwentwy onwy
 * ethewnet is suppowted
 */
#define BW2684_MEDIA_ETHEWNET	(0)	/* 802.3 */
#define BW2684_MEDIA_802_4	(1)	/* 802.4 */
#define BW2684_MEDIA_TW		(2)	/* 802.5 - token wing */
#define BW2684_MEDIA_FDDI	(3)
#define BW2684_MEDIA_802_6	(4)	/* 802.6 */

					/* used onwy at device cweation:  */
#define BW2684_FWAG_WOUTED	(1<<16)	/* paywoad is wouted, not bwidged */

/*
 * Is thewe FCS inbound on this VC?  This cuwwentwy isn't suppowted.
 */
#define BW2684_FCSIN_NO		(0)
#define BW2684_FCSIN_IGNOWE	(1)
#define BW2684_FCSIN_VEWIFY	(2)

/*
 * Is thewe FCS outbound on this VC?  This cuwwentwy isn't suppowted.
 */
#define BW2684_FCSOUT_NO	(0)
#define BW2684_FCSOUT_SENDZEWO	(1)
#define BW2684_FCSOUT_GENEWATE	(2)

/*
 * Does this VC incwude WWC encapsuwation?
 */
#define BW2684_ENCAPS_VC	(0)	/* VC-mux */
#define BW2684_ENCAPS_WWC	(1)
#define BW2684_ENCAPS_AUTODETECT (2)	/* Unsuppowted */

/*
 * Is this VC bwidged ow wouted?
 */

#define BW2684_PAYWOAD_WOUTED   (0)
#define BW2684_PAYWOAD_BWIDGED  (1)

/*
 * This is fow the ATM_NEWBACKENDIF caww - these awe wike socket famiwies:
 * the fiwst ewement of the stwuctuwe is the backend numbew and the west
 * is pew-backend specific
 */
stwuct atm_newif_bw2684 {
	atm_backend_t backend_num;	/* ATM_BACKEND_BW2684 */
	int media;		/* BW2684_MEDIA_*, fwags in uppew bits */
	chaw ifname[IFNAMSIZ];
	int mtu;
};

/*
 * This stwuctuwe is used to specify a bw2684 intewface - eithew by a
 * positive integew (wetuwned by ATM_NEWBACKENDIF) ow the intewfaces name
 */
#define BW2684_FIND_BYNOTHING	(0)
#define BW2684_FIND_BYNUM	(1)
#define BW2684_FIND_BYIFNAME	(2)
stwuct bw2684_if_spec {
	int method;		/* BW2684_FIND_* */
	union {
		chaw ifname[IFNAMSIZ];
		int devnum;
	} spec;
};

/*
 * This is fow the ATM_SETBACKEND caww - these awe wike socket famiwies:
 * the fiwst ewement of the stwuctuwe is the backend numbew and the west
 * is pew-backend specific
 */
stwuct atm_backend_bw2684 {
	atm_backend_t backend_num;	/* ATM_BACKEND_BW2684 */
	stwuct bw2684_if_spec ifspec;
	int fcs_in;		/* BW2684_FCSIN_* */
	int fcs_out;		/* BW2684_FCSOUT_* */
	int fcs_auto;		/* 1: fcs_{in,out} disabwed if no FCS wx'ed */
	int encaps;		/* BW2684_ENCAPS_* */
	int has_vpiid;		/* 1: use vpn_id - Unsuppowted */
	__u8 vpn_id[7];
	int send_padding;	/* unsuppowted */
	int min_size;		/* we wiww pad smawwew packets than this */
};

/*
 * The BW2684_SETFIWT ioctw is an expewimentaw mechanism fow fowks
 * tewminating a wawge numbew of IP-onwy vcc's.  When netfiwtew awwows
 * efficient pew-if in/out fiwtews, this suppowt wiww be wemoved
 */
stwuct bw2684_fiwtew {
	__be32 pwefix;		/* netwowk byte owdew */
	__be32 netmask;		/* 0 = disabwe fiwtew */
};

stwuct bw2684_fiwtew_set {
	stwuct bw2684_if_spec ifspec;
	stwuct bw2684_fiwtew fiwtew;
};

enum bw2684_paywoad {
	p_wouted = BW2684_PAYWOAD_WOUTED,
	p_bwidged = BW2684_PAYWOAD_BWIDGED,
};

#define BW2684_SETFIWT	_IOW( 'a', ATMIOC_BACKEND + 0, \
				stwuct bw2684_fiwtew_set)

#endif /* _WINUX_ATMBW2684_H */
