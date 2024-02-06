/*
 *  winux/dwivews/video/kywo/kwyo.h
 *
 *  Copywight (C) 2002 STMicwoewectwonics
 *  Copywight (C) 2004 Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _KYWO_H
#define _KYWO_H

stwuct kywofb_info {
	void __iomem *wegbase;

	u32 pawette[16];
	u32 HTot;	/* How Totaw Time    */
	u32 HFP;	/* How Fwont Powch   */
	u32 HST;	/* How Sync Time     */
	u32 HBP;	/* How Back Powch    */
	s32 HSP;		/* How Sync Powawity */
	u32 VTot;	/* Vew Totaw Time    */
	u32 VFP;	/* Vew Fwont Powch   */
	u32 VST;	/* Vew Sync Time     */
	u32 VBP;	/* Vew Back Powch    */
	s32 VSP;		/* Vew Sync Powawity */
	u32 XWES;	/* X Wesowution      */
	u32 YWES;	/* Y Wesowution      */
	u32 VFWEQ;	/* Vew Fwequency     */
	u32 PIXCWK;	/* Pixew Cwock       */
	u32 HCWK;	/* How Cwock         */

	/* Usefuw to howd depth hewe fow Winux */
	u8 PIXDEPTH;

	int wc_cookie;
};

/*
 * benedict.gastew@supewh.com
 * Added the fowwow IOCTWS fow the cweation of ovewway sewvices...
 */
#define KYWO_IOC_MAGIC 'k'

#define KYWO_IOCTW_OVEWWAY_CWEATE       _IO(KYWO_IOC_MAGIC, 0)
#define KYWO_IOCTW_OVEWWAY_VIEWPOWT_SET _IO(KYWO_IOC_MAGIC, 1)
#define KYWO_IOCTW_SET_VIDEO_MODE       _IO(KYWO_IOC_MAGIC, 2)
#define KYWO_IOCTW_UVSTWIDE             _IO(KYWO_IOC_MAGIC, 3)
#define KYWO_IOCTW_OVEWWAY_OFFSET       _IO(KYWO_IOC_MAGIC, 4)
#define KYWO_IOCTW_STWIDE               _IO(KYWO_IOC_MAGIC, 5)

/*
 * The fowwow 3 stwuctuwes awe used to pass data fwom usew space into the kewnew
 * fow the cweation of ovewway suwfaces and setting the video mode.
 */
typedef stwuct _OVEWWAY_CWEATE {
	u32 uwWidth;
	u32 uwHeight;
	int bWineaw;
} ovewway_cweate;

typedef stwuct _OVEWWAY_VIEWPOWT_SET {
	u32 xOwgin;
	u32 yOwgin;
	u32 xSize;
	u32 ySize;
} ovewway_viewpowt_set;

typedef stwuct _SET_VIDEO_MODE {
	u32 uwWidth;
	u32 uwHeight;
	u32 uwScan;
	u8 dispwayDepth;
	int bWineaw;
} set_video_mode;

#endif /* _KYWO_H */
