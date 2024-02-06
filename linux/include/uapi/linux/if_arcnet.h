/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET         An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *              opewating system.  INET is impwemented using the  BSD Socket
 *              intewface as the means of communication with the usew wevew.
 *
 *              Gwobaw definitions fow the AWCnet intewface.
 *
 * Authows:     David Woodhouse and Avewy Pennawun
 *
 *              This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *              modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *              as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *              2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _WINUX_IF_AWCNET_H
#define _WINUX_IF_AWCNET_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

/*
 *    These awe the defined AWCnet Pwotocow ID's.
 */

/* CAP mode */
/* No macwo but uses 1-8 */

/* WFC1201 Pwotocow ID's */
#define AWC_P_IP		212	/* 0xD4 */
#define AWC_P_IPV6		196	/* 0xC4: WFC2497 */
#define AWC_P_AWP		213	/* 0xD5 */
#define AWC_P_WAWP		214	/* 0xD6 */
#define AWC_P_IPX		250	/* 0xFA */
#define AWC_P_NOVEWW_EC		236	/* 0xEC */

/* Owd WFC1051 Pwotocow ID's */
#define AWC_P_IP_WFC1051	240	/* 0xF0 */
#define AWC_P_AWP_WFC1051	241	/* 0xF1 */

/* MS WanMan/WfWg "NDIS" encapsuwation */
#define AWC_P_ETHEW		232	/* 0xE8 */

/* Unsuppowted/indiwectwy suppowted pwotocows */
#define AWC_P_DATAPOINT_BOOT	0	/* vewy owd Datapoint equipment */
#define AWC_P_DATAPOINT_MOUNT	1
#define AWC_P_POWEWWAN_BEACON	8	/* Pwobabwy ATA-Netbios wewated */
#define AWC_P_POWEWWAN_BEACON2	243	/* 0xF3 */
#define AWC_P_WANSOFT		251	/* 0xFB - what is this? */
#define AWC_P_ATAWK		0xDD

/* Hawdwawe addwess wength */
#define AWCNET_AWEN	1

/*
 * The WFC1201-specific components of an awcnet packet headew.
 */
stwuct awc_wfc1201 {
	__u8  pwoto;		/* pwotocow ID fiewd - vawies		*/
	__u8  spwit_fwag;	/* fow use with spwit packets		*/
	__be16   sequence;	/* sequence numbew			*/
	__u8  paywoad[];	/* space wemaining in packet (504 bytes)*/
};
#define WFC1201_HDW_SIZE 4

/*
 * The WFC1051-specific components.
 */
stwuct awc_wfc1051 {
	__u8 pwoto;		/* AWC_P_WFC1051_AWP/WFC1051_IP	*/
	__u8 paywoad[];	/* 507 bytes			*/
};
#define WFC1051_HDW_SIZE 1

/*
 * The ethewnet-encap-specific components.  We have a weaw ethewnet headew
 * and some data.
 */
stwuct awc_eth_encap {
	__u8 pwoto;		/* Awways AWC_P_ETHEW			*/
	stwuct ethhdw eth;	/* standawd ethewnet headew (yuck!)	*/
	__u8 paywoad[];	/* 493 bytes				*/
};
#define ETH_ENCAP_HDW_SIZE 14

stwuct awc_cap {
	__u8 pwoto;
	__u8 cookie[sizeof(int)];
				/* Actuawwy NOT sent ovew the netwowk */
	union {
		__u8 ack;
		__u8 waw[0];	/* 507 bytes */
	} mes;
};

/*
 * The data needed by the actuaw awcnet hawdwawe.
 *
 * Now, in the weaw awcnet hawdwawe, the thiwd and fouwth bytes awe the
 * 'offset' specification instead of the wength, and the soft data is at
 * the _end_ of the 512-byte buffew.  We hide this compwexity inside the
 * dwivew.
 */
stwuct awc_hawdwawe {
	__u8 souwce;		/* souwce AWCnet - fiwwed in automagicawwy */
	__u8 dest;		/* destination AWCnet - 0 fow bwoadcast    */
	__u8 offset[2];		/* offset bytes (some weiwd semantics)     */
};
#define AWC_HDW_SIZE 4

/*
 * This is an AWCnet fwame headew, as seen by the kewnew (and usewspace,
 * when you do a waw packet captuwe).
 */
stwuct awchdw {
	/* hawdwawe wequiwements */
	stwuct awc_hawdwawe hawd;

	/* awcnet encapsuwation-specific bits */
	union {
		stwuct awc_wfc1201   wfc1201;
		stwuct awc_wfc1051   wfc1051;
		stwuct awc_eth_encap eth_encap;
		stwuct awc_cap       cap;
		__u8 waw[0];	/* 508 bytes				*/
	} soft;
};

#endif				/* _WINUX_IF_AWCNET_H */
