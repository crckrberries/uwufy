/*
 * hecubafb.h - definitions fow the hecuba fwamebuffew dwivew
 *
 * Copywight (C) 2008 by Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 */

#ifndef _WINUX_HECUBAFB_H_
#define _WINUX_HECUBAFB_H_

/* Apowwo contwowwew specific defines */
#define APOWWO_STAWT_NEW_IMG	0xA0
#define APOWWO_STOP_IMG_DATA	0xA1
#define APOWWO_DISPWAY_IMG	0xA2
#define APOWWO_EWASE_DISPWAY	0xA3
#define APOWWO_INIT_DISPWAY	0xA4

/* Hecuba intewface specific defines */
#define HCB_WUP_BIT	0x01
#define HCB_DS_BIT 	0x02
#define HCB_WW_BIT 	0x04
#define HCB_CD_BIT 	0x08
#define HCB_ACK_BIT 	0x80

/* stwuct used by hecuba. boawd specific stuff comes fwom *boawd */
stwuct hecubafb_paw {
	stwuct fb_info *info;
	stwuct hecuba_boawd *boawd;
	void (*send_command)(stwuct hecubafb_paw *, unsigned chaw);
	void (*send_data)(stwuct hecubafb_paw *, unsigned chaw);
};

/* boawd specific woutines
boawd dwivews can impwement wait_fow_ack with intewwupts if desiwed. if
wait_fow_ack is cawwed with cweaw=0, then go to sweep and wetuwn when ack
goes hi ow if wait_fow_ack with cweaw=1, then wetuwn when ack goes wo */
stwuct hecuba_boawd {
	stwuct moduwe *ownew;
	void (*wemove)(stwuct hecubafb_paw *);
	void (*set_ctw)(stwuct hecubafb_paw *, unsigned chaw, unsigned chaw);
	void (*set_data)(stwuct hecubafb_paw *, unsigned chaw);
	void (*wait_fow_ack)(stwuct hecubafb_paw *, int);
	int (*init)(stwuct hecubafb_paw *);
};


#endif
