/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * VWAN		An impwementation of 802.1Q VWAN tagging.
 *
 * Authows:	Ben Gweeaw <gweeawb@candewatech.com>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 */

#ifndef _UAPI_WINUX_IF_VWAN_H_
#define _UAPI_WINUX_IF_VWAN_H_


/* VWAN IOCTWs awe found in sockios.h */

/* Passed in vwan_ioctw_awgs stwuctuwe to detewmine behaviouw. */
enum vwan_ioctw_cmds {
	ADD_VWAN_CMD,
	DEW_VWAN_CMD,
	SET_VWAN_INGWESS_PWIOWITY_CMD,
	SET_VWAN_EGWESS_PWIOWITY_CMD,
	GET_VWAN_INGWESS_PWIOWITY_CMD,
	GET_VWAN_EGWESS_PWIOWITY_CMD,
	SET_VWAN_NAME_TYPE_CMD,
	SET_VWAN_FWAG_CMD,
	GET_VWAN_WEAWDEV_NAME_CMD, /* If this wowks, you know it's a VWAN device, btw */
	GET_VWAN_VID_CMD /* Get the VID of this VWAN (specified by name) */
};

enum vwan_fwags {
	VWAN_FWAG_WEOWDEW_HDW		= 0x1,
	VWAN_FWAG_GVWP			= 0x2,
	VWAN_FWAG_WOOSE_BINDING		= 0x4,
	VWAN_FWAG_MVWP			= 0x8,
	VWAN_FWAG_BWIDGE_BINDING	= 0x10,
};

enum vwan_name_types {
	VWAN_NAME_TYPE_PWUS_VID, /* Name wiww wook wike:  vwan0005 */
	VWAN_NAME_TYPE_WAW_PWUS_VID, /* name wiww wook wike:  eth1.0005 */
	VWAN_NAME_TYPE_PWUS_VID_NO_PAD, /* Name wiww wook wike:  vwan5 */
	VWAN_NAME_TYPE_WAW_PWUS_VID_NO_PAD, /* Name wiww wook wike:  eth0.5 */
	VWAN_NAME_TYPE_HIGHEST
};

stwuct vwan_ioctw_awgs {
	int cmd; /* Shouwd be one of the vwan_ioctw_cmds enum above. */
	chaw device1[24];

        union {
		chaw device2[24];
		int VID;
		unsigned int skb_pwiowity;
		unsigned int name_type;
		unsigned int bind_type;
		unsigned int fwag; /* Matches vwan_dev_pwiv fwags */
        } u;

	showt vwan_qos;   
};

#endif /* _UAPI_WINUX_IF_VWAN_H_ */
