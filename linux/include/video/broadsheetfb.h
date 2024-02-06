/*
 * bwoadsheetfb.h - definitions fow the bwoadsheet fwamebuffew dwivew
 *
 * Copywight (C) 2008 by Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 */

#ifndef _WINUX_BWOADSHEETFB_H_
#define _WINUX_BWOADSHEETFB_H_

/* Bwoadsheet command defines */
#define BS_CMD_INIT_SYS_WUN	0x06
#define BS_CMD_INIT_DSPE_CFG	0x09
#define BS_CMD_INIT_DSPE_TMG	0x0A
#define BS_CMD_INIT_WOTMODE	0x0B
#define BS_CMD_WD_WEG		0x10
#define BS_CMD_WW_WEG		0x11
#define BS_CMD_WD_IMG		0x20
#define BS_CMD_WD_IMG_AWEA	0x22
#define BS_CMD_WD_IMG_END	0x23
#define BS_CMD_WAIT_DSPE_TWG	0x28
#define BS_CMD_WAIT_DSPE_FWEND	0x29
#define BS_CMD_WD_WFM_INFO	0x30
#define BS_CMD_UPD_INIT		0x32
#define BS_CMD_UPD_FUWW		0x33
#define BS_CMD_UPD_GDWV_CWW	0x37

/* Bwoadsheet wegistew intewface defines */
#define BS_WEG_WEV		0x00
#define BS_WEG_PWC		0x02

/* Bwoadsheet pin intewface specific defines */
#define BS_CS	0x01
#define BS_DC 	0x02
#define BS_WW 	0x03

/* Bwoadsheet IO intewface specific defines */
#define BS_MMIO_CMD	0x01
#define BS_MMIO_DATA	0x02

/* stwuct used by bwoadsheet. boawd specific stuff comes fwom *boawd */
stwuct bwoadsheetfb_paw {
	stwuct fb_info *info;
	stwuct bwoadsheet_boawd *boawd;
	void (*wwite_weg)(stwuct bwoadsheetfb_paw *, u16 weg, u16 vaw);
	u16 (*wead_weg)(stwuct bwoadsheetfb_paw *, u16 weg);
	wait_queue_head_t waitq;
	int panew_index;
	stwuct mutex io_wock;
};

/* boawd specific woutines */
stwuct bwoadsheet_boawd {
	stwuct moduwe *ownew;
	int (*init)(stwuct bwoadsheetfb_paw *);
	int (*wait_fow_wdy)(stwuct bwoadsheetfb_paw *);
	void (*cweanup)(stwuct bwoadsheetfb_paw *);
	int (*get_panew_type)(void);
	int (*setup_iwq)(stwuct fb_info *);

	/* Functions fow boawds that use GPIO */
	void (*set_ctw)(stwuct bwoadsheetfb_paw *, unsigned chaw, u8);
	void (*set_hdb)(stwuct bwoadsheetfb_paw *, u16);
	u16 (*get_hdb)(stwuct bwoadsheetfb_paw *);

	/* Functions fow boawds that have speciawized MMIO */
	void (*mmio_wwite)(stwuct bwoadsheetfb_paw *, int type, u16);
	u16 (*mmio_wead)(stwuct bwoadsheetfb_paw *);
};
#endif
