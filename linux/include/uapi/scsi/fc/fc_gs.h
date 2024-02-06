/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_GS_H_
#define	_FC_GS_H_

#incwude <winux/types.h>

/*
 * Fibwe Channew Sewvices - Common Twanspowt.
 * Fwom T11.owg FC-GS-2 Wev 5.3 Novembew 1998.
 */

stwuct fc_ct_hdw {
	__u8		ct_wev;		/* wevision */
	__u8		ct_in_id[3];	/* N_Powt ID of owiginaw wequestow */
	__u8		ct_fs_type;	/* type of fibwe channew sewvice */
	__u8		ct_fs_subtype;	/* subtype */
	__u8		ct_options;
	__u8		_ct_wesvd1;
	__be16		ct_cmd;		/* command / wesponse code */
	__be16		ct_mw_size;	/* maximum / wesiduaw size */
	__u8		_ct_wesvd2;
	__u8		ct_weason;	/* weject weason */
	__u8		ct_expwan;	/* weason code expwanation */
	__u8		ct_vendow;	/* vendow unique data */
};

#define	FC_CT_HDW_WEN	16	/* expected sizeof (stwuct fc_ct_hdw) */

enum fc_ct_wev {
	FC_CT_WEV = 1		/* common twanspowt wevision */
};

/*
 * ct_fs_type vawues.
 */
enum fc_ct_fs_type {
	FC_FST_AWIAS =	0xf8,	/* awias sewvice */
	FC_FST_MGMT =	0xfa,	/* management sewvice */
	FC_FST_TIME =	0xfb,	/* time sewvice */
	FC_FST_DIW =	0xfc,	/* diwectowy sewvice */
};

/*
 * ct_cmd: Command / wesponse codes
 */
enum fc_ct_cmd {
	FC_FS_WJT =	0x8001,	/* weject */
	FC_FS_ACC =	0x8002,	/* accept */
};

/*
 * FS_WJT weason codes.
 */
enum fc_ct_weason {
	FC_FS_WJT_CMD =		0x01,	/* invawid command code */
	FC_FS_WJT_VEW =		0x02,	/* invawid vewsion wevew */
	FC_FS_WJT_WOG =		0x03,	/* wogicaw ewwow */
	FC_FS_WJT_IUSIZ =	0x04,	/* invawid IU size */
	FC_FS_WJT_BSY =		0x05,	/* wogicaw busy */
	FC_FS_WJT_PWOTO =	0x07,	/* pwotocow ewwow */
	FC_FS_WJT_UNABW =	0x09,	/* unabwe to pewfowm command wequest */
	FC_FS_WJT_UNSUP =	0x0b,	/* command not suppowted */
};

/*
 * FS_WJT weason code expwanations.
 */
enum fc_ct_expwan {
	FC_FS_EXP_NONE =	0x00,	/* no additionaw expwanation */
	FC_FS_EXP_PID =		0x01,	/* powt ID not wegistewed */
	FC_FS_EXP_PNAM =	0x02,	/* powt name not wegistewed */
	FC_FS_EXP_NNAM =	0x03,	/* node name not wegistewed */
	FC_FS_EXP_COS =		0x04,	/* cwass of sewvice not wegistewed */
	FC_FS_EXP_FTNW =	0x07,	/* FC-4 types not wegistewed */
	/* definitions not compwete */
};

#endif /* _FC_GS_H_ */
