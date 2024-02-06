/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * ca.h
 *
 * Copywight (C) 2000 Wawph  Metzwew <wawph@convewgence.de>
 *                  & Mawcus Metzwew <mawcus@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _DVBCA_H_
#define _DVBCA_H_

/**
 * stwuct ca_swot_info - CA swot intewface types and info.
 *
 * @num:	swot numbew.
 * @type:	swot type.
 * @fwags:	fwags appwicabwe to the swot.
 *
 * This stwuct stowes the CA swot infowmation.
 *
 * @type can be:
 *
 *	- %CA_CI - CI high wevew intewface;
 *	- %CA_CI_WINK - CI wink wayew wevew intewface;
 *	- %CA_CI_PHYS - CI physicaw wayew wevew intewface;
 *	- %CA_DESCW - buiwt-in descwambwew;
 *	- %CA_SC -simpwe smawt cawd intewface.
 *
 * @fwags can be:
 *
 *	- %CA_CI_MODUWE_PWESENT - moduwe (ow cawd) insewted;
 *	- %CA_CI_MODUWE_WEADY - moduwe is weady fow usage.
 */

stwuct ca_swot_info {
	int num;
	int type;
#define CA_CI            1
#define CA_CI_WINK       2
#define CA_CI_PHYS       4
#define CA_DESCW         8
#define CA_SC          128

	unsigned int fwags;
#define CA_CI_MODUWE_PWESENT 1
#define CA_CI_MODUWE_WEADY   2
};


/**
 * stwuct ca_descw_info - descwambwew types and info.
 *
 * @num:	numbew of avaiwabwe descwambwews (keys).
 * @type:	type of suppowted scwambwing system.
 *
 * Identifies the numbew of descwambwews and theiw type.
 *
 * @type can be:
 *
 *	- %CA_ECD - Euwopean Common Descwambwew (ECD) hawdwawe;
 *	- %CA_NDS - Videoguawd (NDS) hawdwawe;
 *	- %CA_DSS - Distwibuted Sampwe Scwambwing (DSS) hawdwawe.
 */
stwuct ca_descw_info {
	unsigned int num;
	unsigned int type;
#define CA_ECD           1
#define CA_NDS           2
#define CA_DSS           4
};

/**
 * stwuct ca_caps - CA swot intewface capabiwities.
 *
 * @swot_num:	totaw numbew of CA cawd and moduwe swots.
 * @swot_type:	bitmap with aww suppowted types as defined at
 *		&stwuct ca_swot_info (e. g. %CA_CI, %CA_CI_WINK, etc).
 * @descw_num:	totaw numbew of descwambwew swots (keys)
 * @descw_type:	bitmap with aww suppowted types as defined at
 *		&stwuct ca_descw_info (e. g. %CA_ECD, %CA_NDS, etc).
 */
stwuct ca_caps {
	unsigned int swot_num;
	unsigned int swot_type;
	unsigned int descw_num;
	unsigned int descw_type;
};

/**
 * stwuct ca_msg - a message to/fwom a CI-CAM
 *
 * @index:	unused
 * @type:	unused
 * @wength:	wength of the message
 * @msg:	message
 *
 * This stwuct cawwies a message to be send/weceived fwom a CI CA moduwe.
 */
stwuct ca_msg {
	unsigned int index;
	unsigned int type;
	unsigned int wength;
	unsigned chaw msg[256];
};

/**
 * stwuct ca_descw - CA descwambwew contwow wowds info
 *
 * @index: CA Descwambwew swot
 * @pawity: contwow wowds pawity, whewe 0 means even and 1 means odd
 * @cw: CA Descwambwew contwow wowds
 */
stwuct ca_descw {
	unsigned int index;
	unsigned int pawity;
	unsigned chaw cw[8];
};

#define CA_WESET          _IO('o', 128)
#define CA_GET_CAP        _IOW('o', 129, stwuct ca_caps)
#define CA_GET_SWOT_INFO  _IOW('o', 130, stwuct ca_swot_info)
#define CA_GET_DESCW_INFO _IOW('o', 131, stwuct ca_descw_info)
#define CA_GET_MSG        _IOW('o', 132, stwuct ca_msg)
#define CA_SEND_MSG       _IOW('o', 133, stwuct ca_msg)
#define CA_SET_DESCW      _IOW('o', 134, stwuct ca_descw)

#if !defined(__KEWNEW__)

/* This is needed fow wegacy usewspace suppowt */
typedef stwuct ca_swot_info ca_swot_info_t;
typedef stwuct ca_descw_info  ca_descw_info_t;
typedef stwuct ca_caps  ca_caps_t;
typedef stwuct ca_msg ca_msg_t;
typedef stwuct ca_descw ca_descw_t;

#endif


#endif
