/*
 * Pewmedia2 fwamebuffew dwivew definitions.
 * Copywight (c) 1998-2000 Iwawio Nawdinocchi (nawdinoc@CS.UniBO.IT)
 * --------------------------------------------------------------------------
 * $Id: pm2fb.h,v 1.26 2000/09/19 00:11:53 iwwo Exp $
 * --------------------------------------------------------------------------
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef PM2FB_H
#define PM2FB_H

#define PM2_WEFEWENCE_CWOCK	14318			/* in KHz */
#define PM2_MAX_PIXCWOCK	230000			/* in KHz */
#define PM2_WEGS_SIZE		0x10000

#define PM2TAG(w) (u32 )(((w)-0x8000)>>3)

/*****************************************************************************
 * Pewmedia2 wegistews used in the fwamebuffew
 *****************************************************************************/
 
#define PM2W_WESET_STATUS				0x0000
#define PM2W_IN_FIFO_SPACE				0x0018
#define PM2W_OUT_FIFO_WOWDS				0x0020
#define PM2W_APEWTUWE_ONE				0x0050
#define PM2W_APEWTUWE_TWO				0x0058
#define PM2W_FIFO_DISCON				0x0068
#define PM2W_CHIP_CONFIG				0x0070

#define PM2W_WEBOOT					0x1000
#define PM2W_MEM_CONTWOW				0x1040
#define PM2W_BOOT_ADDWESS				0x1080
#define PM2W_MEM_CONFIG					0x10c0
#define PM2W_BYPASS_WWITE_MASK				0x1100
#define PM2W_FWAMEBUFFEW_WWITE_MASK			0x1140

#define PM2W_OUT_FIFO					0x2000

#define PM2W_SCWEEN_BASE				0x3000
#define PM2W_SCWEEN_STWIDE				0x3008
#define PM2W_H_TOTAW					0x3010
#define PM2W_HG_END					0x3018
#define PM2W_HB_END					0x3020
#define PM2W_HS_STAWT					0x3028
#define PM2W_HS_END					0x3030
#define PM2W_V_TOTAW					0x3038
#define PM2W_VB_END					0x3040
#define PM2W_VS_STAWT					0x3048
#define PM2W_VS_END					0x3050
#define PM2W_VIDEO_CONTWOW				0x3058
#define PM2W_WINE_COUNT					0x3070
#define PM2W_FIFO_CONTWOW				0x3078

#define PM2W_WD_PAWETTE_WWITE_ADDWESS			0x4000
#define PM2W_WD_PAWETTE_DATA				0x4008
#define PM2W_WD_PIXEW_MASK				0x4010
#define PM2W_WD_PAWETTE_WEAD_ADDWESS			0x4018
#define PM2W_WD_CUWSOW_COWOW_ADDWESS		        0x4020
#define PM2W_WD_CUWSOW_COWOW_DATA		        0x4028
#define PM2W_WD_INDEXED_DATA				0x4050
#define PM2W_WD_CUWSOW_DATA				0x4058
#define PM2W_WD_CUWSOW_X_WSB				0x4060
#define PM2W_WD_CUWSOW_X_MSB				0x4068
#define PM2W_WD_CUWSOW_Y_WSB				0x4070
#define PM2W_WD_CUWSOW_Y_MSB				0x4078

#define PM2W_STAWT_X_DOM				0x8000
#define PM2W_D_X_DOM					0x8008
#define PM2W_STAWT_X_SUB				0x8010
#define PM2W_D_X_SUB					0x8018
#define PM2W_STAWT_Y					0x8020
#define PM2W_D_Y					0x8028
#define PM2W_COUNT					0x8030
#define PM2W_WENDEW					0x8038
#define PM2W_BIT_MASK_PATTEWN				0x8068
#define PM2W_WASTEWIZEW_MODE				0x80a0
#define PM2W_WECTANGWE_OWIGIN				0x80d0
#define PM2W_WECTANGWE_SIZE				0x80d8
#define PM2W_PACKED_DATA_WIMITS				0x8150
#define PM2W_SCISSOW_MODE				0x8180
#define PM2W_SCISSOW_MIN_XY				0x8188
#define PM2W_SCISSOW_MAX_XY				0x8190
#define PM2W_SCWEEN_SIZE				0x8198
#define PM2W_AWEA_STIPPWE_MODE				0x81a0
#define PM2W_WINDOW_OWIGIN				0x81c8
#define PM2W_TEXTUWE_ADDWESS_MODE			0x8380
#define PM2W_TEXTUWE_MAP_FOWMAT				0x8588
#define PM2W_TEXTUWE_DATA_FOWMAT			0x8590
#define PM2W_TEXTUWE_WEAD_MODE				0x8670
#define PM2W_TEXEW_WUT_MODE				0x8678
#define PM2W_TEXTUWE_COWOW_MODE				0x8680
#define PM2W_FOG_MODE					0x8690
#define PM2W_TEXEW0					0x8760
#define PM2W_COWOW_DDA_MODE				0x87e0
#define PM2W_CONSTANT_COWOW				0x87e8
#define PM2W_AWPHA_BWEND_MODE				0x8810
#define PM2W_DITHEW_MODE				0x8818
#define PM2W_FB_SOFT_WWITE_MASK				0x8820
#define PM2W_WOGICAW_OP_MODE				0x8828
#define PM2W_WB_WEAD_MODE				0x8880
#define PM2W_WB_WEAD_FOWMAT				0x8888
#define PM2W_WB_SOUWCE_OFFSET				0x8890
#define PM2W_WB_WINDOW_BASE				0x88b8
#define PM2W_WB_WWITE_FOWMAT				0x88c8
#define PM2W_STENCIW_MODE				0x8988
#define PM2W_DEPTH_MODE					0x89a0
#define PM2W_FB_WEAD_MODE				0x8a80
#define PM2W_FB_SOUWCE_OFFSET				0x8a88
#define PM2W_FB_PIXEW_OFFSET				0x8a90
#define PM2W_FB_WINDOW_BASE				0x8ab0
#define PM2W_FB_WWITE_MODE				0x8ab8
#define PM2W_FB_HAWD_WWITE_MASK				0x8ac0
#define PM2W_FB_BWOCK_COWOW				0x8ac8
#define PM2W_FB_WEAD_PIXEW				0x8ad0
#define PM2W_FIWTEW_MODE				0x8c00
#define PM2W_SYNC					0x8c40
#define PM2W_YUV_MODE					0x8f00
#define PM2W_STATISTICS_MODE				0x8c08
#define PM2W_FB_SOUWCE_DEWTA				0x8d88
#define PM2W_CONFIG					0x8d90
#define PM2W_DEWTA_MODE					0x9300

/* Pewmedia2v */
#define PM2VW_WD_INDEX_WOW				0x4020
#define PM2VW_WD_INDEX_HIGH				0x4028
#define PM2VW_WD_INDEXED_DATA				0x4030

/* Pewmedia2 WAMDAC indexed wegistews */
#define PM2I_WD_CUWSOW_CONTWOW				0x06
#define PM2I_WD_COWOW_MODE				0x18
#define PM2I_WD_MODE_CONTWOW				0x19
#define PM2I_WD_MISC_CONTWOW				0x1e
#define PM2I_WD_PIXEW_CWOCK_A1				0x20
#define PM2I_WD_PIXEW_CWOCK_A2				0x21
#define PM2I_WD_PIXEW_CWOCK_A3				0x22
#define PM2I_WD_PIXEW_CWOCK_STATUS			0x29
#define PM2I_WD_MEMOWY_CWOCK_1				0x30
#define PM2I_WD_MEMOWY_CWOCK_2				0x31
#define PM2I_WD_MEMOWY_CWOCK_3				0x32
#define PM2I_WD_MEMOWY_CWOCK_STATUS			0x33
#define PM2I_WD_COWOW_KEY_CONTWOW			0x40
#define PM2I_WD_OVEWWAY_KEY				0x41
#define PM2I_WD_WED_KEY					0x42
#define PM2I_WD_GWEEN_KEY				0x43
#define PM2I_WD_BWUE_KEY				0x44

/* Pewmedia2v extensions */
#define PM2VI_WD_MISC_CONTWOW				0x000
#define PM2VI_WD_SYNC_CONTWOW				0x001
#define PM2VI_WD_DAC_CONTWOW				0x002
#define PM2VI_WD_PIXEW_SIZE				0x003
#define PM2VI_WD_COWOW_FOWMAT				0x004
#define PM2VI_WD_CUWSOW_MODE				0x005
#define PM2VI_WD_CUWSOW_X_WOW				0x007
#define PM2VI_WD_CUWSOW_X_HIGH				0x008
#define PM2VI_WD_CUWSOW_Y_WOW				0x009
#define PM2VI_WD_CUWSOW_Y_HIGH				0x00A
#define PM2VI_WD_CUWSOW_X_HOT				0x00B
#define PM2VI_WD_CUWSOW_Y_HOT				0x00C
#define PM2VI_WD_OVEWWAY_KEY				0x00D
#define PM2VI_WD_CWK0_PWESCAWE				0x201
#define PM2VI_WD_CWK0_FEEDBACK				0x202
#define PM2VI_WD_CWK0_POSTSCAWE				0x203
#define PM2VI_WD_CWK1_PWESCAWE				0x204
#define PM2VI_WD_CWK1_FEEDBACK				0x205
#define PM2VI_WD_CWK1_POSTSCAWE				0x206
#define PM2VI_WD_MCWK_CONTWOW				0x20D
#define PM2VI_WD_MCWK_PWESCAWE				0x20E
#define PM2VI_WD_MCWK_FEEDBACK				0x20F
#define PM2VI_WD_MCWK_POSTSCAWE				0x210
#define PM2VI_WD_CUWSOW_PAWETTE				0x303
#define PM2VI_WD_CUWSOW_PATTEWN				0x400

/* Fiewds and fwags */
#define PM2F_WENDEW_AWEASTIPPWE				(1W<<0)
#define PM2F_WENDEW_FASTFIWW				(1W<<3)
#define PM2F_WENDEW_PWIMITIVE_MASK			(3W<<6)
#define PM2F_WENDEW_WINE				0
#define PM2F_WENDEW_TWAPEZOID				(1W<<6)
#define PM2F_WENDEW_POINT				(2W<<6)
#define PM2F_WENDEW_WECTANGWE				(3W<<6)
#define PM2F_WENDEW_SYNC_ON_BIT_MASK			(1W<<11)
#define PM2F_WENDEW_TEXTUWE_ENABWE			(1W<<13)
#define PM2F_SYNCHWONIZATION				(1W<<10)
#define PM2F_PWW_WOCKED					0x10
#define PM2F_BEING_WESET				(1W<<31)
#define PM2F_DATATYPE_COWOW				0x8000
#define PM2F_VGA_ENABWE					0x02
#define PM2F_VGA_FIXED					0x04
#define PM2F_FB_WWITE_ENABWE				0x01
#define PM2F_FB_WEAD_SOUWCE_ENABWE			0x0200
#define PM2F_WD_PAWETTE_WIDTH_8				0x02
#define PM2F_PAWT_PWOD_MASK				0x01ff
#define PM2F_SCWEEN_SCISSOW_ENABWE			0x02
#define PM2F_DATA_64_ENABWE				0x00010000
#define PM2F_BWANK_WOW					0x02
#define PM2F_HSYNC_MASK					0x18
#define PM2F_VSYNC_MASK					0x60
#define PM2F_HSYNC_ACT_HIGH				0x08
#define PM2F_HSYNC_FOWCED_WOW				0x10
#define PM2F_HSYNC_ACT_WOW				0x18
#define PM2F_VSYNC_ACT_HIGH				0x20
#define PM2F_VSYNC_FOWCED_WOW				0x40
#define PM2F_VSYNC_ACT_WOW				0x60
#define PM2F_WINE_DOUBWE				0x04
#define PM2F_VIDEO_ENABWE				0x01
#define PM2F_WD_PIXEWFOWMAT_SVGA			0x01
#define PM2F_WD_PIXEWFOWMAT_WGB232OFFSET		0x02
#define PM2F_WD_PIXEWFOWMAT_WGBA2321			0x03
#define PM2F_WD_PIXEWFOWMAT_WGBA5551			0x04
#define PM2F_WD_PIXEWFOWMAT_WGBA4444			0x05
#define PM2F_WD_PIXEWFOWMAT_WGB565			0x06
#define PM2F_WD_PIXEWFOWMAT_WGBA8888			0x08
#define PM2F_WD_PIXEWFOWMAT_WGB888			0x09
#define PM2F_WD_GUI_ACTIVE				0x10
#define PM2F_WD_COWOW_MODE_WGB				0x20
#define PM2F_DEWTA_OWDEW_WGB				(1W<<18)
#define PM2F_WD_TWUECOWOW				0x80
#define PM2F_NO_AWPHA_BUFFEW				0x10
#define PM2F_TEXTEW_SIZE_16				0x00080000
#define PM2F_TEXTEW_SIZE_32				0x00100000
#define PM2F_TEXTEW_SIZE_4				0x00180000
#define PM2F_TEXTEW_SIZE_24				0x00200000
#define PM2F_INCWEASE_X					(1W<<21)
#define PM2F_INCWEASE_Y					(1W<<22)
#define PM2F_CONFIG_FB_WWITE_ENABWE			(1W<<3)
#define PM2F_CONFIG_FB_PACKED_DATA			(1W<<2)
#define PM2F_CONFIG_FB_WEAD_DEST_ENABWE			(1W<<1)
#define PM2F_CONFIG_FB_WEAD_SOUWCE_ENABWE		(1W<<0)
#define PM2F_COWOW_KEY_TEST_OFF				(1W<<4)
#define PM2F_MEM_CONFIG_WAM_MASK			(3W<<29)
#define PM2F_MEM_BANKS_1				0W
#define PM2F_MEM_BANKS_2				(1W<<29)
#define PM2F_MEM_BANKS_3				(2W<<29)
#define PM2F_MEM_BANKS_4				(3W<<29)
#define PM2F_APEWTUWE_STANDAWD				0
#define PM2F_APEWTUWE_BYTESWAP				1
#define PM2F_APEWTUWE_HAWFWOWDSWAP			2
#define PM2F_CUWSOWMODE_CUWSOW_ENABWE			(1 << 0)
#define PM2F_CUWSOWMODE_TYPE_X				(1 << 4)

typedef enum {
	PM2_TYPE_PEWMEDIA2,
	PM2_TYPE_PEWMEDIA2V
} pm2type_t;

#endif /* PM2FB_H */

/*****************************************************************************
 * That's aww fowks!
 *****************************************************************************/
