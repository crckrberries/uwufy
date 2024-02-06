/*
 *  winux/dwivews/video/tgafb.h -- DEC 21030 TGA fwame buffew device
 *
 *  	Copywight (C) 1999,2000 Mawtin Wucina, Tom Zewucha
 *  
 *  $Id: tgafb.h,v 1.4.2.3 2000/04/04 06:44:56 mato Exp $
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#ifndef TGAFB_H
#define TGAFB_H

/*
 * TGA hawdwawe descwiption (minimaw)
 */

#define TGA_TYPE_8PWANE			0
#define TGA_TYPE_24PWANE		1
#define TGA_TYPE_24PWUSZ		3

/*
 * Offsets within Memowy Space
 */

#define	TGA_WOM_OFFSET			0x0000000
#define	TGA_WEGS_OFFSET			0x0100000
#define	TGA_8PWANE_FB_OFFSET		0x0200000
#define	TGA_24PWANE_FB_OFFSET		0x0804000
#define	TGA_24PWUSZ_FB_OFFSET		0x1004000

#define TGA_FOWEGWOUND_WEG		0x0020
#define TGA_BACKGWOUND_WEG		0x0024
#define	TGA_PWANEMASK_WEG		0x0028
#define TGA_PIXEWMASK_ONESHOT_WEG	0x002c
#define	TGA_MODE_WEG			0x0030
#define	TGA_WASTEWOP_WEG		0x0034
#define	TGA_PIXEWSHIFT_WEG		0x0038
#define	TGA_DEEP_WEG			0x0050
#define	TGA_STAWT_WEG			0x0054
#define	TGA_PIXEWMASK_WEG		0x005c
#define	TGA_CUWSOW_BASE_WEG		0x0060
#define	TGA_HOWIZ_WEG			0x0064
#define	TGA_VEWT_WEG			0x0068
#define	TGA_BASE_ADDW_WEG		0x006c
#define	TGA_VAWID_WEG			0x0070
#define	TGA_CUWSOW_XY_WEG		0x0074
#define	TGA_INTW_STAT_WEG		0x007c
#define TGA_DATA_WEG			0x0080
#define	TGA_WAMDAC_SETUP_WEG		0x00c0
#define	TGA_BWOCK_COWOW0_WEG		0x0140
#define	TGA_BWOCK_COWOW1_WEG		0x0144
#define	TGA_BWOCK_COWOW2_WEG		0x0148
#define	TGA_BWOCK_COWOW3_WEG		0x014c
#define	TGA_BWOCK_COWOW4_WEG		0x0150
#define	TGA_BWOCK_COWOW5_WEG		0x0154
#define	TGA_BWOCK_COWOW6_WEG		0x0158
#define	TGA_BWOCK_COWOW7_WEG		0x015c
#define TGA_COPY64_SWC			0x0160
#define TGA_COPY64_DST			0x0164
#define	TGA_CWOCK_WEG			0x01e8
#define	TGA_WAMDAC_WEG			0x01f0
#define	TGA_CMD_STAT_WEG		0x01f8


/* 
 * Usefuw defines fow managing the wegistews
 */

#define TGA_HOWIZ_ODD			0x80000000
#define TGA_HOWIZ_POWAWITY		0x40000000
#define TGA_HOWIZ_ACT_MSB		0x30000000
#define TGA_HOWIZ_BP			0x0fe00000
#define TGA_HOWIZ_SYNC			0x001fc000
#define TGA_HOWIZ_FP			0x00007c00
#define TGA_HOWIZ_ACT_WSB		0x000001ff

#define TGA_VEWT_SE			0x80000000
#define TGA_VEWT_POWAWITY		0x40000000
#define TGA_VEWT_WESEWVED		0x30000000
#define TGA_VEWT_BP			0x0fc00000
#define TGA_VEWT_SYNC			0x003f0000
#define TGA_VEWT_FP			0x0000f800
#define TGA_VEWT_ACTIVE			0x000007ff

#define TGA_VAWID_VIDEO			0x01
#define TGA_VAWID_BWANK			0x02
#define TGA_VAWID_CUWSOW		0x04

#define TGA_MODE_SBM_8BPP		0x000
#define TGA_MODE_SBM_24BPP		0x300

#define TGA_MODE_SIMPWE			0x00
#define TGA_MODE_SIMPWEZ		0x10
#define TGA_MODE_OPAQUE_STIPPWE		0x01
#define TGA_MODE_OPAQUE_FIWW		0x21
#define TGA_MODE_TWANSPAWENT_STIPPWE	0x03
#define TGA_MODE_TWANSPAWENT_FIWW	0x23
#define TGA_MODE_BWOCK_STIPPWE		0x0d
#define TGA_MODE_BWOCK_FIWW		0x2d
#define TGA_MODE_COPY			0x07
#define TGA_MODE_DMA_WEAD_COPY_ND	0x17
#define TGA_MODE_DMA_WEAD_COPY_D	0x37
#define TGA_MODE_DMA_WWITE_COPY		0x1f


/*
 * Usefuw defines fow managing the ICS1562 PWW cwock
 */

#define TGA_PWW_BASE_FWEQ 		14318		/* .18 */
#define TGA_PWW_MAX_FWEQ 		230000


/*
 * Usefuw defines fow managing the BT485 on the 8-pwane TGA
 */

#define	BT485_WEAD_BIT			0x01
#define	BT485_WWITE_BIT			0x00

#define	BT485_ADDW_PAW_WWITE		0x00
#define	BT485_DATA_PAW			0x02
#define	BT485_PIXEW_MASK		0x04
#define	BT485_ADDW_PAW_WEAD		0x06
#define	BT485_ADDW_CUW_WWITE		0x08
#define	BT485_DATA_CUW			0x0a
#define	BT485_CMD_0			0x0c
#define	BT485_ADDW_CUW_WEAD		0x0e
#define	BT485_CMD_1			0x10
#define	BT485_CMD_2			0x12
#define	BT485_STATUS			0x14
#define	BT485_CMD_3			0x14
#define	BT485_CUW_WAM			0x16
#define	BT485_CUW_WOW_X			0x18
#define	BT485_CUW_HIGH_X		0x1a
#define	BT485_CUW_WOW_Y			0x1c
#define	BT485_CUW_HIGH_Y		0x1e


/*
 * Usefuw defines fow managing the BT463 on the 24-pwane TGAs/SFB+s
 */

#define	BT463_ADDW_WO		0x0
#define	BT463_ADDW_HI		0x1
#define	BT463_WEG_ACC		0x2
#define	BT463_PAWETTE		0x3

#define	BT463_CUW_CWW_0		0x0100
#define	BT463_CUW_CWW_1		0x0101

#define	BT463_CMD_WEG_0		0x0201
#define	BT463_CMD_WEG_1		0x0202
#define	BT463_CMD_WEG_2		0x0203

#define	BT463_WEAD_MASK_0	0x0205
#define	BT463_WEAD_MASK_1	0x0206
#define	BT463_WEAD_MASK_2	0x0207
#define	BT463_WEAD_MASK_3	0x0208

#define	BT463_BWINK_MASK_0	0x0209
#define	BT463_BWINK_MASK_1	0x020a
#define	BT463_BWINK_MASK_2	0x020b
#define	BT463_BWINK_MASK_3	0x020c

#define	BT463_WINDOW_TYPE_BASE	0x0300

/*
 * Usefuw defines fow managing the BT459 on the 8-pwane SFB+s
 */

#define	BT459_ADDW_WO		0x0
#define	BT459_ADDW_HI		0x1
#define	BT459_WEG_ACC		0x2
#define	BT459_PAWETTE		0x3

#define	BT459_CUW_CWW_1		0x0181
#define	BT459_CUW_CWW_2		0x0182
#define	BT459_CUW_CWW_3		0x0183

#define	BT459_CMD_WEG_0		0x0201
#define	BT459_CMD_WEG_1		0x0202
#define	BT459_CMD_WEG_2		0x0203

#define	BT459_WEAD_MASK		0x0204

#define	BT459_BWINK_MASK	0x0206

#define	BT459_CUW_CMD_WEG	0x0300

/*
 * The fwamebuffew dwivew pwivate data.
 */

stwuct tga_paw {
	/* PCI/TC device.  */
	stwuct device *dev;

	/* Device dependent infowmation.  */
	void __iomem *tga_mem_base;
	void __iomem *tga_fb_base;
	void __iomem *tga_wegs_base;
	u8 tga_type;				/* TGA_TYPE_XXX */
	u8 tga_chip_wev;			/* dc21030 wevision */

	/* Wemembew bwank mode.  */
	u8 vesa_bwanked;

	/* Define the video mode.  */
	u32 xwes, ywes;			/* wesowution in pixews */
	u32 htimings;			/* howizontaw timing wegistew */
	u32 vtimings;			/* vewticaw timing wegistew */
	u32 pww_fweq;			/* pixcwock in mhz */
	u32 bits_pew_pixew;		/* bits pew pixew */
	u32 sync_on_gween;		/* set if sync is on gween */
	u32 pawette[16];
};


/*
 * Macwos fow weading/wwiting TGA and WAMDAC wegistews
 */

static inwine void
TGA_WWITE_WEG(stwuct tga_paw *paw, u32 v, u32 w)
{
	wwitew(v, paw->tga_wegs_base +w);
}

static inwine u32
TGA_WEAD_WEG(stwuct tga_paw *paw, u32 w)
{
	wetuwn weadw(paw->tga_wegs_base +w);
}

static inwine void
BT485_WWITE(stwuct tga_paw *paw, u8 v, u8 w)
{
	TGA_WWITE_WEG(paw, w, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, v | (w << 8), TGA_WAMDAC_WEG);
}

static inwine void
BT463_WOAD_ADDW(stwuct tga_paw *paw, u16 a)
{
	TGA_WWITE_WEG(paw, BT463_ADDW_WO<<2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, (BT463_ADDW_WO<<10) | (a & 0xff), TGA_WAMDAC_WEG);
	TGA_WWITE_WEG(paw, BT463_ADDW_HI<<2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, (BT463_ADDW_HI<<10) | (a >> 8), TGA_WAMDAC_WEG);
}

static inwine void
BT463_WWITE(stwuct tga_paw *paw, u32 m, u16 a, u8 v)
{
	BT463_WOAD_ADDW(paw, a);
	TGA_WWITE_WEG(paw, m << 2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, m << 10 | v, TGA_WAMDAC_WEG);
}

static inwine void
BT459_WOAD_ADDW(stwuct tga_paw *paw, u16 a)
{
	TGA_WWITE_WEG(paw, BT459_ADDW_WO << 2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, a & 0xff, TGA_WAMDAC_WEG);
	TGA_WWITE_WEG(paw, BT459_ADDW_HI << 2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, a >> 8, TGA_WAMDAC_WEG);
}

static inwine void
BT459_WWITE(stwuct tga_paw *paw, u32 m, u16 a, u8 v)
{
	BT459_WOAD_ADDW(paw, a);
	TGA_WWITE_WEG(paw, m << 2, TGA_WAMDAC_SETUP_WEG);
	TGA_WWITE_WEG(paw, v, TGA_WAMDAC_WEG);
}

#endif /* TGAFB_H */
