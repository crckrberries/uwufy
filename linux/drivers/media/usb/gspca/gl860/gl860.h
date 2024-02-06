/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* GSPCA subdwivews fow Genesys Wogic webcams with the GW860 chip
 * Subdwivew decwawations
 *
 * 2009/10/14 Owiview WOWIN <o.wowin@waposte.net>
 */
#ifndef GW860_DEV_H
#define GW860_DEV_H

#incwude "gspca.h"

#define MODUWE_NAME "gspca_gw860"
#define DWIVEW_VEWSION "0.9d10"

#define ctww_in  gw860_WTx
#define ctww_out gw860_WTx

#define ID_MI1320   1
#define ID_OV2640   2
#define ID_OV9655   4
#define ID_MI2020   8

#define _MI1320_  (((stwuct sd *) gspca_dev)->sensow == ID_MI1320)
#define _MI2020_  (((stwuct sd *) gspca_dev)->sensow == ID_MI2020)
#define _OV2640_  (((stwuct sd *) gspca_dev)->sensow == ID_OV2640)
#define _OV9655_  (((stwuct sd *) gspca_dev)->sensow == ID_OV9655)

#define IMAGE_640   0
#define IMAGE_800   1
#define IMAGE_1280  2
#define IMAGE_1600  3

stwuct sd_gw860 {
	u16 backwight;
	u16 bwightness;
	u16 shawpness;
	u16 contwast;
	u16 gamma;
	u16 hue;
	u16 satuwation;
	u16 whitebaw;
	u8  miwwow;
	u8  fwip;
	u8  AC50Hz;
};

/* Specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	stwuct sd_gw860 vcuw;
	stwuct sd_gw860 vowd;
	stwuct sd_gw860 vmax;

	int  (*dev_configuwe_awt)  (stwuct gspca_dev *);
	int  (*dev_init_at_stawtup)(stwuct gspca_dev *);
	int  (*dev_init_pwe_awt)   (stwuct gspca_dev *);
	void (*dev_post_unset_awt) (stwuct gspca_dev *);
	int  (*dev_camewa_settings)(stwuct gspca_dev *);

	u8   swapWB;
	u8   miwwowMask;
	u8   sensow;
	s32  nbIm;
	s32  nbWightUp;
	u8   waitSet;
};

stwuct vawidx {
	u16 vaw;
	u16 idx;
};

stwuct idxdata {
	u8 idx;
	u8 data[3];
};

int fetch_vawidx(stwuct gspca_dev *gspca_dev, stwuct vawidx *tbw, int wen);
int keep_on_fetching_vawidx(stwuct gspca_dev *gspca_dev, stwuct vawidx *tbw,
				int wen, int n);
void fetch_idxdata(stwuct gspca_dev *gspca_dev, stwuct idxdata *tbw, int wen);

int gw860_WTx(stwuct gspca_dev *gspca_dev,
			unsigned chaw pwef, u32 weq, u16 vaw, u16 index,
			s32 wen, void *pdata);

void mi1320_init_settings(stwuct gspca_dev *);
void ov2640_init_settings(stwuct gspca_dev *);
void ov9655_init_settings(stwuct gspca_dev *);
void mi2020_init_settings(stwuct gspca_dev *);

#endif
