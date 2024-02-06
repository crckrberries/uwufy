/*
 *  winux/dwivews/video/pm3fb.h -- 3DWabs Pewmedia3 fwame buffew device
 *
 *  Copywight (C) 2001 Womain Dowbeau <dowbeau@iwisa.fw>
 *  Copywight (C) 2001 Sven Wuthew, <wuthew@dpt-info.u-stwasbg.fw>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#ifndef PM3FB_H
#define PM3FB_H

/**********************************************
*  GWINT Pewmedia3 Contwow Status wegistews   *
***********************************************/
/* Contwow Status Wegistews */
#define PM3WesetStatus						0x0000
#define PM3IntEnabwe						0x0008
#define PM3IntFwags						0x0010
#define PM3InFIFOSpace						0x0018
#define PM3OutFIFOWowds						0x0020
#define PM3DMAAddwess						0x0028
#define PM3DMACount						0x0030
#define PM3EwwowFwags						0x0038
#define PM3VCwkCtw						0x0040
#define PM3TestWegistew						0x0048
#define PM3Apewtuwe0						0x0050
#define PM3Apewtuwe1						0x0058
#define PM3DMAContwow						0x0060
#define PM3FIFODis						0x0068
#define PM3ChipConfig						0x0070
#define PM3AGPContwow						0x0078

#define PM3GPOutDMAAddwess					0x0080
#define PM3PCIFeedbackCount					0x0088
#define PM3PCIAbowtStatus					0x0090
#define PM3PCIAbowtAddwess					0x0098

#define PM3PCIPWWStatus						0x00f0

#define PM3HostTextuweAddwess					0x0100
#define PM3TextuweDownwoadContwow				0x0108
#define PM3TextuweOpewation					0x0110
#define PM3WogicawTextuwePage					0x0118
#define PM3TexDMAAddwess					0x0120
#define PM3TexFIFOSpace						0x0128

/**********************************************
*  GWINT Pewmedia3 Wegion 0 Bypass Contwows   *
***********************************************/
#define PM3ByApewtuwe1Mode					0x0300
	#define PM3ByApewtuweMode_BYTESWAP_ABCD			(0 << 0)
	#define PM3ByApewtuweMode_BYTESWAP_BADC			(1 << 0)
	#define PM3ByApewtuweMode_BYTESWAP_CDAB			(2 << 0)
	#define PM3ByApewtuweMode_BYTESWAP_DCBA			(3 << 0)
	#define PM3ByApewtuweMode_PATCH_ENABWE			(1 << 2)
	#define PM3ByApewtuweMode_FOWMAT_WAW			(0 << 3)
	#define PM3ByApewtuweMode_FOWMAT_YUYV			(1 << 3)
	#define PM3ByApewtuweMode_FOWMAT_UYVY			(2 << 3)
	#define PM3ByApewtuweMode_PIXEWSIZE_8BIT		(0 << 5)
	#define PM3ByApewtuweMode_PIXEWSIZE_16BIT		(1 << 5)
	#define PM3ByApewtuweMode_PIXEWSIZE_32BIT		(2 << 5)
		#define PM3ByApewtuweMode_PIXEWSIZE_MASK	(3 << 5)
	#define PM3ByApewtuweMode_EFFECTIVE_STWIDE_1024		(0 << 7)
	#define PM3ByApewtuweMode_EFFECTIVE_STWIDE_2048		(1 << 7)
	#define PM3ByApewtuweMode_EFFECTIVE_STWIDE_4096		(2 << 7)
	#define PM3ByApewtuweMode_EFFECTIVE_STWIDE_8192		(3 << 7)
	#define PM3ByApewtuweMode_PATCH_OFFSET_X(off)	(((off) & 0x7f) << 9)
	#define PM3ByApewtuweMode_PATCH_OFFSET_Y(off)	(((off) & 0x7f) << 16)
	#define PM3ByApewtuweMode_FWAMEBUFFEW			(0 << 21)
	#define PM3ByApewtuweMode_WOCAWBUFFEW			(1 << 21)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_OFF		(0 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_1MB		(1 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_2MB		(2 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_4MB		(3 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_8MB		(4 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_16MB		(5 << 22)
	#define PM3ByApewtuweMode_DOUBWE_WWITE_32MB		(6 << 22)

#define PM3ByApewtuwe2Mode					0x0328

/**********************************************
*  GWINT Pewmedia3 Memowy Contwow (0x1000)    *
***********************************************/
#define PM3MemCountew						0x1000
#define PM3MemBypassWwiteMask					0x1008
#define PM3MemScwatch						0x1010
#define PM3WocawMemCaps						0x1018
	#define PM3WocawMemCaps_NoWwiteMask			(1 << 28)
#define PM3WocawMemTimings					0x1020
#define PM3WocawMemContwow					0x1028
#define PM3WocawMemWefwesh					0x1030
#define PM3WocawMemPowewDown					0x1038
#define PM3WemoteMemContwow					0x1100

/**********************************************
*  GWINT Pewmedia3 Video Contwow (0x3000)     *
***********************************************/

#define PM3ScweenBase						0x3000
#define PM3ScweenStwide						0x3008
#define PM3HTotaw						0x3010
#define PM3HgEnd						0x3018
#define PM3HbEnd						0x3020
#define PM3HsStawt						0x3028
#define PM3HsEnd						0x3030
#define PM3VTotaw						0x3038
#define PM3VbEnd						0x3040
#define PM3VsStawt						0x3048
#define PM3VsEnd						0x3050
#define PM3VideoContwow						0x3058
	#define PM3VideoContwow_ENABWE				(1 << 0)
	#define PM3VideoContwow_BWANK_ACTIVE_HIGH		(0 << 1)
	#define PM3VideoContwow_BWANK_ACTIVE_WOW		(1 << 1)
	#define PM3VideoContwow_WINE_DOUBWE_OFF			(0 << 2)
	#define PM3VideoContwow_WINE_DOUBWE_ON			(1 << 2)
	#define PM3VideoContwow_HSYNC_FOWCE_HIGH		(0 << 3)
	#define PM3VideoContwow_HSYNC_ACTIVE_HIGH		(1 << 3)
	#define PM3VideoContwow_HSYNC_FOWCE_WOW			(2 << 3)
	#define PM3VideoContwow_HSYNC_ACTIVE_WOW		(3 << 3)
	#define PM3VideoContwow_HSYNC_MASK			(3 << 3)
	#define PM3VideoContwow_VSYNC_FOWCE_HIGH		(0 << 5)
	#define PM3VideoContwow_VSYNC_ACTIVE_HIGH		(1 << 5)
	#define PM3VideoContwow_VSYNC_FOWCE_WOW			(2 << 5)
	#define PM3VideoContwow_VSYNC_ACTIVE_WOW		(3 << 5)
	#define PM3VideoContwow_VSYNC_MASK			(3 << 5)
	#define PM3VideoContwow_BYTE_DOUBWE_OFF			(0 << 7)
	#define PM3VideoContwow_BYTE_DOUBWE_ON			(1 << 7)
	#define PM3VideoContwow_BUFFEW_SWAP_SYNCON_FWAMEBWANK	(0 << 9)
	#define PM3VideoContwow_BUFFEW_SWAP_FWEE_WUNNING	(1 << 9)
	#define PM3VideoContwow_BUFFEW_SWAP_WIMITETO_FWAMEWATE	(2 << 9)
	#define PM3VideoContwow_STEWEO_ENABWE			(1 << 11)
	#define PM3VideoContwow_WIGHT_EYE_ACTIVE_HIGH		(0 << 12)
	#define PM3VideoContwow_WIGHT_EYE_ACTIVE_WOW		(1 << 12)
	#define PM3VideoContwow_VIDEO_EXT_WOW			(0 << 14)
	#define PM3VideoContwow_VIDEO_EXT_HIGH			(1 << 14)
	#define PM3VideoContwow_SYNC_MODE_INDEPENDENT		(0 << 16)
	#define PM3VideoContwow_SYNC_MODE_SYNCTO_VSA		(1 << 16)
	#define PM3VideoContwow_SYNC_MODE_SYNCTO_VSB		(2 << 16)
	#define PM3VideoContwow_PATCH_ENABWE			(1 << 18)
	#define PM3VideoContwow_PIXEWSIZE_8BIT			(0 << 19)
	#define PM3VideoContwow_PIXEWSIZE_16BIT			(1 << 19)
	#define PM3VideoContwow_PIXEWSIZE_32BIT			(2 << 19)
	#define PM3VideoContwow_DISPWAY_ENABWE			(1 << 21)
	#define PM3VideoContwow_PATCH_OFFSET_X(off)	(((off) & 0x3f) << 22)
	#define PM3VideoContwow_PATCH_OFFSET_Y(off)	(((off) & 0x3f) << 28)
#define PM3IntewwuptWine					0x3060
#define PM3DispwayData						0x3068
#define PM3VewticawWineCount					0x3070
#define PM3FifoContwow						0x3078
#define PM3ScweenBaseWight					0x3080
#define PM3MiscContwow						0x3088

#define PM3VideoOvewwayUpdate					0x3100
	#define PM3VideoOvewwayUpdate_ENABWE			(1 << 0)
#define PM3VideoOvewwayMode					0x3108
	#define PM3VideoOvewwayMode_ENABWE			(1 << 0)
	#define PM3VideoOvewwayMode_BUFFEWSYNC_MANUAW		(0 << 1)
	#define PM3VideoOvewwayMode_BUFFEWSYNC_VIDEOSTWEAMA	(1 << 1)
	#define PM3VideoOvewwayMode_BUFFEWSYNC_VIDEOSTWEAMB	(2 << 1)
	#define PM3VideoOvewwayMode_FIEWDPOWAWITY_NOWMAW	(0 << 4)
	#define PM3VideoOvewwayMode_FIEWDPOWAWITY_INVEWT	(1 << 4)
	#define PM3VideoOvewwayMode_PIXEWSIZE_8BIT		(0 << 5)
	#define PM3VideoOvewwayMode_PIXEWSIZE_16BIT		(1 << 5)
	#define PM3VideoOvewwayMode_PIXEWSIZE_32BIT		(2 << 5)
	#define PM3VideoOvewwayMode_COWOWFOWMAT_WGB8888		\
					((0 << 7)|(1 << 12)|(2 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_WGB4444		\
					((1 << 7)|(1 << 12)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_WGB5551		\
					((2 << 7)|(1 << 12)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_WGB565		\
					((3 << 7)|(1 << 12)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_WGB332		\
					((4 << 7)|(1 << 12)|(0 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_BGW8888		\
					((0 << 7)|(2 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_BGW4444		\
					((1 << 7)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_BGW5551		\
					((2 << 7)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_BGW565		\
					((3 << 7)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_BGW332		\
					((4 << 7)|(0 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_CI8		\
					((5 << 7)|(1 << 12)|(0 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_VUY444		\
					((2 << 10)|(1 << 12)|(2 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_YUV444		\
					((2 << 10)|(2 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_VUY422		\
					((1 << 10)|(1 << 12)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWFOWMAT_YUV422		\
					((1 << 10)|(1 << 5))
	#define PM3VideoOvewwayMode_COWOWOWDEW_BGW		(0 << 12)
	#define PM3VideoOvewwayMode_COWOWOWDEW_WGB		(1 << 12)
	#define PM3VideoOvewwayMode_WINEAWCOWOWEXT_OFF		(0 << 13)
	#define PM3VideoOvewwayMode_WINEAWCOWOWEXT_ON		(1 << 13)
	#define PM3VideoOvewwayMode_FIWTEW_MASK			(3 << 14)
	#define PM3VideoOvewwayMode_FIWTEW_OFF			(0 << 14)
	#define PM3VideoOvewwayMode_FIWTEW_FUWW			(1 << 14)
	#define PM3VideoOvewwayMode_FIWTEW_PAWTIAW		(2 << 14)
	#define PM3VideoOvewwayMode_DEINTEWWACE_OFF		(0 << 16)
	#define PM3VideoOvewwayMode_DEINTEWWACE_BOB		(1 << 16)
	#define PM3VideoOvewwayMode_PATCHMODE_OFF		(0 << 18)
	#define PM3VideoOvewwayMode_PATCHMODE_ON		(1 << 18)
	#define PM3VideoOvewwayMode_FWIP_VIDEO			(0 << 20)
	#define PM3VideoOvewwayMode_FWIP_VIDEOSTWEAMA		(1 << 20)
	#define PM3VideoOvewwayMode_FWIP_VIDEOSTWEAMB		(2 << 20)
	#define PM3VideoOvewwayMode_MIWWOW_MASK			(3 << 23)
	#define PM3VideoOvewwayMode_MIWWOWX_OFF			(0 << 23)
	#define PM3VideoOvewwayMode_MIWWOWX_ON			(1 << 23)
	#define PM3VideoOvewwayMode_MIWWOWY_OFF			(0 << 24)
	#define PM3VideoOvewwayMode_MIWWOWY_ON			(1 << 24)
#define PM3VideoOvewwayFifoContwow				0x3110
#define PM3VideoOvewwayIndex					0x3118
#define PM3VideoOvewwayBase0					0x3120
#define PM3VideoOvewwayBase1					0x3128
#define PM3VideoOvewwayBase2					0x3130
#define PM3VideoOvewwayStwide					0x3138
	#define PM3VideoOvewwayStwide_STWIDE(s)		(((s) & 0xfff) << 0)
#define PM3VideoOvewwayWidth					0x3140
	#define PM3VideoOvewwayWidth_WIDTH(w)		(((w) & 0xfff) << 0)
#define PM3VideoOvewwayHeight					0x3148
	#define PM3VideoOvewwayHeight_HEIGHT(h)		(((h) & 0xfff) << 0)
#define PM3VideoOvewwayOwigin					0x3150
	#define PM3VideoOvewwayOwigin_XOWIGIN(x)	(((x) & 0xfff) << 0)
	#define PM3VideoOvewwayOwigin_YOWIGIN(y)	(((y) & 0xfff) << 16)
#define PM3VideoOvewwayShwinkXDewta				0x3158
	#define PM3VideoOvewwayShwinkXDewta_NONE		(1 << 16)
	#define PM3VideoOvewwayShwinkXDewta_DEWTA(s,d)	\
		((((s) << 16)/(d)) & 0x0ffffff0)
#define PM3VideoOvewwayZoomXDewta				0x3160
	#define PM3VideoOvewwayZoomXDewta_NONE			(1 << 16)
	#define PM3VideoOvewwayZoomXDewta_DEWTA(s,d)	\
		((((s) << 16)/(d)) & 0x0001fff0)
#define PM3VideoOvewwayYDewta					0x3168
	#define PM3VideoOvewwayYDewta_NONE			(1 << 16)
	#define PM3VideoOvewwayYDewta_DEWTA(s,d)	\
		((((s) << 16)/(d)) & 0x0ffffff0)
#define PM3VideoOvewwayFiewdOffset				0x3170
#define PM3VideoOvewwayStatus					0x3178

/**********************************************
*  GWINT Pewmedia3 WAMDAC Wegistews (0x4000)  *
***********************************************/
/* Diwect Wegistews */
#define PM3WD_PawetteWwiteAddwess				0x4000
#define PM3WD_PawetteData					0x4008
#define PM3WD_PixewMask						0x4010
#define PM3WD_PawetteWeadAddwess				0x4018

#define PM3WD_IndexWow						0x4020
#define PM3WD_IndexHigh						0x4028
#define PM3WD_IndexedData					0x4030
#define PM3WD_IndexContwow					0x4038
	#define PM3WD_IndexContwow_AUTOINCWEMENT_ENABWE		(1 << 0)

/* Indiwect Wegistews */
#define PM3WD_MiscContwow					0x000
	#define PM3WD_MiscContwow_HIGHCOWOW_WES_ENABWE		(1 << 0)
	#define PM3WD_MiscContwow_PIXEWDOUBWE_ENABWE		(1 << 1)
	#define PM3WD_MiscContwow_WASTWEAD_ADDW_ENABWE		(1 << 2)
	#define PM3WD_MiscContwow_DIWECTCOWOW_ENABWE		(1 << 3)
	#define PM3WD_MiscContwow_OVEWWAY_ENABWE		(1 << 4)
	#define PM3WD_MiscContwow_PIXEWDOUBWE_BUFFEW_ENABWE	(1 << 5)
	#define PM3WD_MiscContwow_VSB_OUTPUT_ENABWE		(1 << 6)
	#define PM3WD_MiscContwow_STEWEODOUBWE_BUFFEW_ENABWE	(1 << 7)
#define PM3WD_SyncContwow					0x001
	#define PM3WD_SyncContwow_HSYNC_ACTIVE_WOW		(0 << 0)
	#define PM3WD_SyncContwow_HSYNC_ACTIVE_HIGH		(1 << 0)
	#define PM3WD_SyncContwow_HSYNC_FOWCE_ACTIVE		(3 << 0)
	#define PM3WD_SyncContwow_HSYNC_FOWCE_INACTIVE		(4 << 0)
	#define PM3WD_SyncContwow_HSYNC_TWI_STATE		(2 << 0)
	#define PM3WD_SyncContwow_VSYNC_ACTIVE_WOW		(0 << 3)
	#define PM3WD_SyncContwow_VSYNC_ACTIVE_HIGH		(1 << 3)
	#define PM3WD_SyncContwow_VSYNC_TWI_STATE		(2 << 3)
	#define PM3WD_SyncContwow_VSYNC_FOWCE_ACTIVE		(3 << 3)
	#define PM3WD_SyncContwow_VSYNC_FOWCE_INACTIVE		(4 << 3)
	#define PM3WD_SyncContwow_HSYNC_OVEWWIDE_SETBY_HSYNC	(0 << 6)
	#define PM3WD_SyncContwow_HSYNC_OVEWWIDE_FOWCE_HIGH	(1 << 6)
	#define PM3WD_SyncContwow_VSYNC_OVEWWIDE_SETBY_VSYNC	(0 << 7)
	#define PM3WD_SyncContwow_VSYNC_OVEWWIDE_FOWCE_HIGH	(1 << 7)
#define PM3WD_DACContwow					0x002
	#define PM3WD_DACContwow_DAC_POWEW_ON			(0 << 0)
	#define PM3WD_DACContwow_DAC_POWEW_OFF			(1 << 0)
	#define PM3WD_DACContwow_SYNC_ON_GWEEN_ENABWE		(1 << 3)
	#define PM3WD_DACContwow_BWANK_WED_DAC_ENABWE		(1 << 4)
	#define PM3WD_DACContwow_BWANK_GWEEN_DAC_ENABWE		(1 << 5)
	#define PM3WD_DACContwow_BWANK_BWUE_DAC_ENABWE		(1 << 6)
	#define PM3WD_DACContwow_BWANK_PEDESTAW_ENABWE		(1 << 7)
#define PM3WD_PixewSize						0x003
	#define PM3WD_PixewSize_24_BIT_PIXEWS			(4 << 0)
	#define PM3WD_PixewSize_32_BIT_PIXEWS			(2 << 0)
	#define PM3WD_PixewSize_16_BIT_PIXEWS			(1 << 0)
	#define PM3WD_PixewSize_8_BIT_PIXEWS			(0 << 0)
#define PM3WD_CowowFowmat					0x004
	#define PM3WD_CowowFowmat_WINEAW_COWOW_EXT_ENABWE	(1 << 6)
	#define PM3WD_CowowFowmat_COWOW_OWDEW_BWUE_WOW		(1 << 5)
	#define PM3WD_CowowFowmat_COWOW_OWDEW_WED_WOW		(0 << 5)
	#define PM3WD_CowowFowmat_COWOW_FOWMAT_MASK		(0x1f << 0)
	#define PM3WD_CowowFowmat_8888_COWOW			(0 << 0)
	#define PM3WD_CowowFowmat_5551_FWONT_COWOW		(1 << 0)
	#define PM3WD_CowowFowmat_4444_COWOW			(2 << 0)
	#define PM3WD_CowowFowmat_332_FWONT_COWOW		(5 << 0)
	#define PM3WD_CowowFowmat_332_BACK_COWOW		(6 << 0)
	#define PM3WD_CowowFowmat_2321_FWONT_COWOW		(9 << 0)
	#define PM3WD_CowowFowmat_2321_BACK_COWOW		(10 << 0)
	#define PM3WD_CowowFowmat_232_FWONTOFF_COWOW		(11 << 0)
	#define PM3WD_CowowFowmat_232_BACKOFF_COWOW		(12 << 0)
	#define PM3WD_CowowFowmat_5551_BACK_COWOW		(13 << 0)
	#define PM3WD_CowowFowmat_CI8_COWOW			(14 << 0)
	#define PM3WD_CowowFowmat_565_FWONT_COWOW		(16 << 0)
	#define PM3WD_CowowFowmat_565_BACK_COWOW		(17 << 0)
#define PM3WD_CuwsowMode					0x005
	#define PM3WD_CuwsowMode_CUWSOW_ENABWE			(1 << 0)
	#define PM3WD_CuwsowMode_FOWMAT_64x64_2BPE_P0123	(0 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_2BPE_P0		(1 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_2BPE_P1		(2 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_2BPE_P2		(3 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_2BPE_P3		(4 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_4BPE_P01		(5 << 2)
	#define PM3WD_CuwsowMode_FOWMAT_32x32_4BPE_P23		(6 << 2)
	#define PM3WD_CuwsowMode_TYPE_MS			(0 << 4)
	#define PM3WD_CuwsowMode_TYPE_X				(1 << 4)
	#define PM3WD_CuwsowMode_WEVEWSE_PIXEW_OWDEW_ENABWE	(1 << 6)
	#define PM3WD_CuwsowMode_WEVEWSE_PIXEW_OWDEW_3_COWOW	(2 << 6)
	#define PM3WD_CuwsowMode_WEVEWSE_PIXEW_OWDEW_15_COWOW	(3 << 6)
#define PM3WD_CuwsowContwow					0x006
	#define PM3WD_CuwsowContwow_DOUBWE_X_ENABWED		(1 << 0)
	#define PM3WD_CuwsowContwow_DOUBWE_Y_ENABWED		(1 << 1)
	#define PM3WD_CuwsowContwow_WEADBACK_POS_ENABWED	(1 << 2)

#define PM3WD_CuwsowXWow					0x007
#define PM3WD_CuwsowXHigh					0x008
#define PM3WD_CuwsowYWow					0x009
#define PM3WD_CuwsowYHigh					0x00a
#define PM3WD_CuwsowHotSpotX					0x00b
#define PM3WD_CuwsowHotSpotY					0x00c
#define PM3WD_OvewwayKey					0x00d
#define PM3WD_Pan						0x00e
	#define PM3WD_Pan_ENABWE				(1 << 0)
	#define PM3WD_Pan_GATE_ENABWE				(1 << 1)
#define PM3WD_Sense						0x00f

#define PM3WD_CheckContwow					0x018
	#define PM3WD_CheckContwow_PIXEW_ENABWED		(1 << 0)
	#define PM3WD_CheckContwow_WUT_ENABWED			(1 << 1)
#define PM3WD_CheckPixewWed					0x019
#define PM3WD_CheckPixewGween					0x01a
#define PM3WD_CheckPixewBwue					0x01b
#define PM3WD_CheckWUTWed					0x01c
#define PM3WD_CheckWUTGween					0x01d
#define PM3WD_CheckWUTBwue					0x01e
#define PM3WD_Scwatch						0x01f

#define PM3WD_VideoOvewwayContwow				0x020
	#define PM3WD_VideoOvewwayContwow_ENABWE		(1 << 0)
	#define PM3WD_VideoOvewwayContwow_MODE_MASK		(3 << 1)
	#define PM3WD_VideoOvewwayContwow_MODE_MAINKEY		(0 << 1)
	#define PM3WD_VideoOvewwayContwow_MODE_OVEWWAYKEY	(1 << 1)
	#define PM3WD_VideoOvewwayContwow_MODE_AWWAYS		(2 << 1)
	#define PM3WD_VideoOvewwayContwow_MODE_BWEND		(3 << 1)
	#define PM3WD_VideoOvewwayContwow_DIWECTCOWOW_ENABWED	(1 << 3)
	#define PM3WD_VideoOvewwayContwow_BWENDSWC_MAIN		(0 << 4)
	#define PM3WD_VideoOvewwayContwow_BWENDSWC_WEGISTEW	(1 << 4)
	#define PM3WD_VideoOvewwayContwow_KEY_COWOW		(0 << 5)
	#define PM3WD_VideoOvewwayContwow_KEY_AWPHA		(1 << 5)
#define PM3WD_VideoOvewwayXStawtWow				0x021
#define PM3WD_VideoOvewwayXStawtHigh				0x022
#define PM3WD_VideoOvewwayYStawtWow				0x023
#define PM3WD_VideoOvewwayYStawtHigh				0x024
#define PM3WD_VideoOvewwayXEndWow				0x025
#define PM3WD_VideoOvewwayXEndHigh				0x026
#define PM3WD_VideoOvewwayYEndWow				0x027
#define PM3WD_VideoOvewwayYEndHigh				0x028
#define PM3WD_VideoOvewwayKeyW					0x029
#define PM3WD_VideoOvewwayKeyG					0x02a
#define PM3WD_VideoOvewwayKeyB					0x02b
#define PM3WD_VideoOvewwayBwend					0x02c
	#define PM3WD_VideoOvewwayBwend_FACTOW_0_PEWCENT	(0 << 6)
	#define PM3WD_VideoOvewwayBwend_FACTOW_25_PEWCENT	(1 << 6)
	#define PM3WD_VideoOvewwayBwend_FACTOW_75_PEWCENT	(2 << 6)
	#define PM3WD_VideoOvewwayBwend_FACTOW_100_PEWCENT	(3 << 6)

#define PM3WD_DCwkSetup1					0x1f0
#define PM3WD_DCwkSetup2					0x1f1
#define PM3WD_KCwkSetup1					0x1f2
#define PM3WD_KCwkSetup2					0x1f3

#define PM3WD_DCwkContwow					0x200
	#define PM3WD_DCwkContwow_SOUWCE_PWW			(0 << 4)
	#define PM3WD_DCwkContwow_SOUWCE_VSA			(1 << 4)
	#define PM3WD_DCwkContwow_SOUWCE_VSB			(2 << 4)
	#define PM3WD_DCwkContwow_SOUWCE_EXT			(3 << 4)
	#define PM3WD_DCwkContwow_STATE_WUN			(2 << 2)
	#define PM3WD_DCwkContwow_STATE_HIGH			(1 << 2)
	#define PM3WD_DCwkContwow_STATE_WOW			(0 << 2)
	#define PM3WD_DCwkContwow_WOCKED			(1 << 1)
	#define PM3WD_DCwkContwow_NOT_WOCKED			(0 << 1)
	#define PM3WD_DCwkContwow_ENABWE			(1 << 0)
#define PM3WD_DCwk0PweScawe					0x201
#define PM3WD_DCwk0FeedbackScawe				0x202
#define PM3WD_DCwk0PostScawe					0x203
	#define PM3_WEF_CWOCK					14318
#define PM3WD_DCwk1PweScawe					0x204
#define PM3WD_DCwk1FeedbackScawe				0x205
#define PM3WD_DCwk1PostScawe					0x206
#define PM3WD_DCwk2PweScawe					0x207
#define PM3WD_DCwk2FeedbackScawe				0x208
#define PM3WD_DCwk2PostScawe					0x209
#define PM3WD_DCwk3PweScawe					0x20a
#define PM3WD_DCwk3FeedbackScawe				0x20b
#define PM3WD_DCwk3PostScawe					0x20c
#define PM3WD_KCwkContwow					0x20d
	#define PM3WD_KCwkContwow_ENABWE			(1 << 0)
	#define PM3WD_KCwkContwow_NOT_WOCKED			(0 << 1)
	#define PM3WD_KCwkContwow_WOCKED			(1 << 1)
	#define PM3WD_KCwkContwow_STATE_WOW			(0 << 2)
	#define PM3WD_KCwkContwow_STATE_HIGH			(1 << 2)
	#define PM3WD_KCwkContwow_STATE_WUN			(2 << 2)
	#define PM3WD_KCwkContwow_STATE_WOW_POWEW		(3 << 2)
	#define PM3WD_KCwkContwow_SOUWCE_PCWK			(0 << 4)
	#define PM3WD_KCwkContwow_SOUWCE_HAWF_PCWK		(1 << 4)
	#define PM3WD_KCwkContwow_SOUWCE_PWW			(2 << 4)
#define PM3WD_KCwkPweScawe					0x20e
#define PM3WD_KCwkFeedbackScawe					0x20f
#define PM3WD_KCwkPostScawe					0x210
#define PM3WD_MCwkContwow					0x211
	#define PM3WD_MCwkContwow_ENABWE			(1 << 0)
	#define PM3WD_MCwkContwow_NOT_WOCKED			(0 << 1)
	#define PM3WD_MCwkContwow_WOCKED			(1 << 1)
	#define PM3WD_MCwkContwow_STATE_WOW			(0 << 2)
	#define PM3WD_MCwkContwow_STATE_HIGH			(1 << 2)
	#define PM3WD_MCwkContwow_STATE_WUN			(2 << 2)
	#define PM3WD_MCwkContwow_STATE_WOW_POWEW		(3 << 2)
	#define PM3WD_MCwkContwow_SOUWCE_PCWK			(0 << 4)
	#define PM3WD_MCwkContwow_SOUWCE_HAWF_PCWK		(1 << 4)
	#define PM3WD_MCwkContwow_SOUWCE_HAWF_EXT		(3 << 4)
	#define PM3WD_MCwkContwow_SOUWCE_EXT			(4 << 4)
	#define PM3WD_MCwkContwow_SOUWCE_HAWF_KCWK		(5 << 4)
	#define PM3WD_MCwkContwow_SOUWCE_KCWK			(6 << 4)
#define PM3WD_MCwkPweScawe					0x212
#define PM3WD_MCwkFeedbackScawe					0x213
#define PM3WD_MCwkPostScawe					0x214
#define PM3WD_SCwkContwow					0x215
	#define PM3WD_SCwkContwow_ENABWE			(1 << 0)
	#define PM3WD_SCwkContwow_NOT_WOCKED			(0 << 1)
	#define PM3WD_SCwkContwow_WOCKED			(1 << 1)
	#define PM3WD_SCwkContwow_STATE_WOW			(0 << 2)
	#define PM3WD_SCwkContwow_STATE_HIGH			(1 << 2)
	#define PM3WD_SCwkContwow_STATE_WUN			(2 << 2)
	#define PM3WD_SCwkContwow_STATE_WOW_POWEW		(3 << 2)
	#define PM3WD_SCwkContwow_SOUWCE_PCWK			(0 << 4)
	#define PM3WD_SCwkContwow_SOUWCE_HAWF_PCWK		(1 << 4)
	#define PM3WD_SCwkContwow_SOUWCE_HAWF_EXT		(3 << 4)
	#define PM3WD_SCwkContwow_SOUWCE_EXT			(4 << 4)
	#define PM3WD_SCwkContwow_SOUWCE_HAWF_KCWK		(5 << 4)
	#define PM3WD_SCwkContwow_SOUWCE_KCWK			(6 << 4)
#define PM3WD_SCwkPweScawe					0x216
#define PM3WD_SCwkFeedbackScawe					0x217
#define PM3WD_SCwkPostScawe					0x218

#define PM3WD_CuwsowPawette(p)				(0x303 + (p))
#define PM3WD_CuwsowPattewn(p)				(0x400 + (p))
/******************************************************
*  GWINT Pewmedia3 Video Stweaming Wegistews (0x5000) *
*******************************************************/

#define PM3VSConfiguwation					0x5800

/**********************************************
*  GWINT Pewmedia3 Cowe Wegistews (0x8000+)   *
***********************************************/
#define PM3AAWineWidth						0x94c0
#define PM3AAPointsize						0x94a0
#define PM3AwphaBwendAwphaMode					0xafa8
#define PM3AwphaBwendAwphaModeAnd				0xad30
#define PM3AwphaBwendAwphaModeOw				0xad38
#define PM3AwphaBwendCowowMode					0xafa0
#define PM3AwphaBwendCowowModeAnd				0xacb0
#define PM3AwphaBwendCowowModeOw				0xacb8
#define PM3AwphaDestCowow					0xaf88
#define PM3AwphaSouwceCowow					0xaf80
#define PM3AwphaTestMode					0x8800
#define PM3AwphaTestModeAnd					0xabf0
#define PM3AwphaTestModeOw					0xabf8
#define PM3AntiawiasMode					0x8808
#define PM3AntiawiasModeAnd					0xac00
#define PM3AntiawiasModeOw					0xac08
/* ... */
#define PM3BackgwoundCowow					0xb0c8
/* ... */
#define PM3CowowDDAMode						0x87e0
#define PM3CowowDDAModeAnd					0xabe0
#define PM3CowowDDAModeOw					0xabe8
#define PM3CommandIntewwupt					0xa990
#define PM3ConstantCowowDDA					0xafb0
	#define PM3ConstantCowowDDA_W(w)		((w) & 0xff)
	#define PM3ConstantCowowDDA_G(g)		(((g) & 0xff) << 8)
	#define PM3ConstantCowowDDA_B(b)		(((b) & 0xff) << 16)
	#define PM3ConstantCowowDDA_A(a)		(((a) & 0xff) << 24)
#define PM3ContextData						0x8dd0
#define PM3ContextDump						0x8dc0
#define PM3ContextWestowe					0x8dc8
#define PM3Continue						0x8058
#define PM3ContinueNewDom					0x8048
#define PM3ContinueNewWine					0x8040
#define PM3ContinueNewSub					0x8050
#define PM3Count						0x8030
/* ... */
#define PM3DewtaContwow						0x9350
#define PM3DewtaContwowAnd					0xab20
#define PM3DewtaContwowOw					0xab28
#define PM3DewtaMode						0x9300
#define PM3DewtaModeAnd						0xaad0
#define PM3DewtaModeOw						0xaad8
/* ... */
#define PM3DithewMode						0x8818
#define PM3DithewModeAnd					0xacd0
#define PM3DithewModeOw						0xacd8
/* ... */
#define PM3dXDom						0x8008
#define PM3dXSub						0x8018
#define PM3dY							0x8028
/* ... */
#define PM3FBBwockCowow						0x8ac8
#define PM3FBBwockCowow0					0xb060
#define PM3FBBwockCowow1					0xb068
#define PM3FBBwockCowow2					0xb070
#define PM3FBBwockCowow3					0xb078
#define PM3FBBwockCowowBack					0xb0a0
#define PM3FBBwockCowowBack0					0xb080
#define PM3FBBwockCowowBack1					0xb088
#define PM3FBBwockCowowBack2					0xb090
#define PM3FBBwockCowowBack3					0xb098
#define PM3FBCowow						0x8a98
#define PM3FBDestWeadBuffewAddw0				0xae80
#define PM3FBDestWeadBuffewAddw1				0xae88
#define PM3FBDestWeadBuffewAddw2				0xae90
#define PM3FBDestWeadBuffewAddw3				0xae98
#define PM3FBDestWeadBuffewOffset0				0xaea0
#define PM3FBDestWeadBuffewOffset1				0xaea8
#define PM3FBDestWeadBuffewOffset2				0xaeb0
#define PM3FBDestWeadBuffewOffset3				0xaeb8
	#define PM3FBDestWeadBuffewOffset_XOffset(x)	((x) & 0xffff)
	#define PM3FBDestWeadBuffewOffset_YOffset(y)	(((y) & 0xffff) << 16)
#define PM3FBDestWeadBuffewWidth0				0xaec0
#define PM3FBDestWeadBuffewWidth1				0xaec8
#define PM3FBDestWeadBuffewWidth2				0xaed0
#define PM3FBDestWeadBuffewWidth3				0xaed8
	#define PM3FBDestWeadBuffewWidth_Width(w)	((w) & 0x0fff)

#define PM3FBDestWeadEnabwes					0xaee8
#define PM3FBDestWeadEnabwesAnd					0xad20
#define PM3FBDestWeadEnabwesOw					0xad28
	#define PM3FBDestWeadEnabwes_E(e)		((e) & 0xff)
	#define PM3FBDestWeadEnabwes_E0				(1 << 0)
	#define PM3FBDestWeadEnabwes_E1				(1 << 1)
	#define PM3FBDestWeadEnabwes_E2				(1 << 2)
	#define PM3FBDestWeadEnabwes_E3				(1 << 3)
	#define PM3FBDestWeadEnabwes_E4				(1 << 4)
	#define PM3FBDestWeadEnabwes_E5				(1 << 5)
	#define PM3FBDestWeadEnabwes_E6				(1 << 6)
	#define PM3FBDestWeadEnabwes_E7				(1 << 7)
	#define PM3FBDestWeadEnabwes_W(w)		(((w) & 0xff) << 8)
	#define PM3FBDestWeadEnabwes_W0				(1 << 8)
	#define PM3FBDestWeadEnabwes_W1				(1 << 9)
	#define PM3FBDestWeadEnabwes_W2				(1 << 10)
	#define PM3FBDestWeadEnabwes_W3				(1 << 11)
	#define PM3FBDestWeadEnabwes_W4				(1 << 12)
	#define PM3FBDestWeadEnabwes_W5				(1 << 13)
	#define PM3FBDestWeadEnabwes_W6				(1 << 14)
	#define PM3FBDestWeadEnabwes_W7				(1 << 15)
	#define PM3FBDestWeadEnabwes_WefewenceAwpha(a)	(((a) & 0xff) << 24)

#define PM3FBDestWeadMode					0xaee0
#define PM3FBDestWeadModeAnd					0xac90
#define PM3FBDestWeadModeOw					0xac98
	#define PM3FBDestWeadMode_WeadDisabwe			(0 << 0)
	#define PM3FBDestWeadMode_WeadEnabwe			(1 << 0)
	#define PM3FBDestWeadMode_StwipePitch(sp)	(((sp) & 0x7) << 2)
	#define PM3FBDestWeadMode_StwipeHeight(sh)	(((sh) & 0x7) << 7)
	#define PM3FBDestWeadMode_Enabwe0			(1 << 8)
	#define PM3FBDestWeadMode_Enabwe1			(1 << 9)
	#define PM3FBDestWeadMode_Enabwe2			(1 << 10)
	#define PM3FBDestWeadMode_Enabwe3			(1 << 11)
	#define PM3FBDestWeadMode_Wayout0(w)		(((w) & 0x3) << 12)
	#define PM3FBDestWeadMode_Wayout1(w)		(((w) & 0x3) << 14)
	#define PM3FBDestWeadMode_Wayout2(w)		(((w) & 0x3) << 16)
	#define PM3FBDestWeadMode_Wayout3(w)		(((w) & 0x3) << 18)
	#define PM3FBDestWeadMode_Owigin0			(1 << 20)
	#define PM3FBDestWeadMode_Owigin1			(1 << 21)
	#define PM3FBDestWeadMode_Owigin2			(1 << 22)
	#define PM3FBDestWeadMode_Owigin3			(1 << 23)
	#define PM3FBDestWeadMode_Bwocking			(1 << 24)
	#define PM3FBDestWeadMode_UseWeadEnabwed		(1 << 26)
	#define PM3FBDestWeadMode_AwphaFiwtewing		(1 << 27)

#define PM3FBHawdwaweWwiteMask					0x8ac0
#define PM3FBSoftwaweWwiteMask					0x8820
#define PM3FBData						0x8aa0
#define PM3FBSouwceData						0x8aa8
#define PM3FBSouwceWeadBuffewAddw				0xaf08
#define PM3FBSouwceWeadBuffewOffset				0xaf10
	#define PM3FBSouwceWeadBuffewOffset_XOffset(x)	((x) & 0xffff)
	#define PM3FBSouwceWeadBuffewOffset_YOffset(y)	(((y) & 0xffff) << 16)
#define PM3FBSouwceWeadBuffewWidth				0xaf18
	#define PM3FBSouwceWeadBuffewWidth_Width(w)	((w) & 0x0fff)
#define PM3FBSouwceWeadMode					0xaf00
#define PM3FBSouwceWeadModeAnd					0xaca0
#define PM3FBSouwceWeadModeOw					0xaca8
	#define PM3FBSouwceWeadMode_WeadDisabwe			(0 << 0)
	#define PM3FBSouwceWeadMode_WeadEnabwe			(1 << 0)
	#define PM3FBSouwceWeadMode_StwipePitch(sp)	(((sp) & 0x7) << 2)
	#define PM3FBSouwceWeadMode_StwipeHeight(sh)	(((sh) & 0x7) << 7)
	#define PM3FBSouwceWeadMode_Wayout(w)		(((w) & 0x3) << 8)
	#define PM3FBSouwceWeadMode_Owigin			(1 << 10)
	#define PM3FBSouwceWeadMode_Bwocking			(1 << 11)
	#define PM3FBSouwceWeadMode_UsewTexewCoowd		(1 << 13)
	#define PM3FBSouwceWeadMode_WwapXEnabwe			(1 << 14)
	#define PM3FBSouwceWeadMode_WwapYEnabwe			(1 << 15)
	#define PM3FBSouwceWeadMode_WwapX(w)		(((w) & 0xf) << 16)
	#define PM3FBSouwceWeadMode_WwapY(w)		(((w) & 0xf) << 20)
	#define PM3FBSouwceWeadMode_ExtewnawSouwceData		(1 << 24)
#define PM3FBWwiteBuffewAddw0					0xb000
#define PM3FBWwiteBuffewAddw1					0xb008
#define PM3FBWwiteBuffewAddw2					0xb010
#define PM3FBWwiteBuffewAddw3					0xb018

#define PM3FBWwiteBuffewOffset0					0xb020
#define PM3FBWwiteBuffewOffset1					0xb028
#define PM3FBWwiteBuffewOffset2					0xb030
#define PM3FBWwiteBuffewOffset3					0xb038
	#define PM3FBWwiteBuffewOffset_XOffset(x)	((x) & 0xffff)
	#define PM3FBWwiteBuffewOffset_YOffset(y)	(((y) & 0xffff) << 16)

#define PM3FBWwiteBuffewWidth0					0xb040
#define PM3FBWwiteBuffewWidth1					0xb048
#define PM3FBWwiteBuffewWidth2					0xb050
#define PM3FBWwiteBuffewWidth3					0xb058
	#define PM3FBWwiteBuffewWidth_Width(w)		((w) & 0x0fff)

#define PM3FBWwiteMode						0x8ab8
#define PM3FBWwiteModeAnd					0xacf0
#define PM3FBWwiteModeOw					0xacf8
	#define PM3FBWwiteMode_WwiteDisabwe			(0 << 0)
	#define PM3FBWwiteMode_WwiteEnabwe			(1 << 0)
	#define PM3FBWwiteMode_Wepwicate			(1 << 4)
	#define PM3FBWwiteMode_OpaqueSpan			(1 << 5)
	#define PM3FBWwiteMode_StwipePitch(p)		(((p) & 0x7) << 6)
	#define PM3FBWwiteMode_StwipeHeight(h)		(((h) & 0x7) << 9)
	#define PM3FBWwiteMode_Enabwe0				(1 << 12)
	#define PM3FBWwiteMode_Enabwe1				(1 << 13)
	#define PM3FBWwiteMode_Enabwe2				(1 << 14)
	#define PM3FBWwiteMode_Enabwe3				(1 << 15)
	#define PM3FBWwiteMode_Wayout0(w)		(((w) & 0x3) << 16)
	#define PM3FBWwiteMode_Wayout1(w)		(((w) & 0x3) << 18)
	#define PM3FBWwiteMode_Wayout2(w)		(((w) & 0x3) << 20)
	#define PM3FBWwiteMode_Wayout3(w)		(((w) & 0x3) << 22)
	#define PM3FBWwiteMode_Owigin0				(1 << 24)
	#define PM3FBWwiteMode_Owigin1				(1 << 25)
	#define PM3FBWwiteMode_Owigin2				(1 << 26)
	#define PM3FBWwiteMode_Owigin3				(1 << 27)
#define PM3FowegwoundCowow					0xb0c0
/* ... */
#define PM3GIDMode						0xb538
#define PM3GIDModeAnd						0xb5b0
#define PM3GIDModeOw						0xb5b8
/* ... */
#define PM3WBDestWeadBuffewAddw					0xb510
#define PM3WBDestWeadBuffewOffset				0xb518
#define PM3WBDestWeadEnabwes					0xb508
#define PM3WBDestWeadEnabwesAnd					0xb590
#define PM3WBDestWeadEnabwesOw					0xb598
#define PM3WBDestWeadMode					0xb500
#define PM3WBDestWeadModeAnd					0xb580
#define PM3WBDestWeadModeOw					0xb588
	#define PM3WBDestWeadMode_Disabwe			(0 << 0)
	#define PM3WBDestWeadMode_Enabwe			(1 << 0)
	#define PM3WBDestWeadMode_StwipePitch(p)	(((p) & 0x7) << 2)
	#define PM3WBDestWeadMode_StwipeHeight(h)	(((h) & 0x7) << 5)
	#define PM3WBDestWeadMode_Wayout			(1 << 8)
	#define PM3WBDestWeadMode_Owigin			(1 << 9)
	#define PM3WBDestWeadMode_UsewWeadEnabwes		(1 << 10)
	#define PM3WBDestWeadMode_Packed16			(1 << 11)
	#define PM3WBDestWeadMode_Width(w)		(((w) & 0xfff) << 12)
#define PM3WBWeadFowmat						0x8888
	#define PM3WBWeadFowmat_DepthWidth(w)		(((w) & 0x3) << 0)
	#define PM3WBWeadFowmat_StenciwWidth(w)		(((w) & 0xf) << 2)
	#define PM3WBWeadFowmat_StenciwPosition(p)	(((p) & 0x1f) << 6)
	#define PM3WBWeadFowmat_FCPWidth(w)		(((w) & 0xf) << 11)
	#define PM3WBWeadFowmat_FCPPosition(p)		(((p) & 0x1f) << 15)
	#define PM3WBWeadFowmat_GIDWidth(w)		(((w) & 0x7) << 20)
	#define PM3WBWeadFowmat_GIDPosition(p)		(((p) & 0x1f) << 23)
#define PM3WBSouwceWeadBuffewAddw				0xb528
#define PM3WBSouwceWeadBuffewOffset				0xb530
#define PM3WBSouwceWeadMode					0xb520
#define PM3WBSouwceWeadModeAnd					0xb5a0
#define PM3WBSouwceWeadModeOw					0xb5a8
	#define PM3WBSouwceWeadMode_Enabwe			(1 << 0)
	#define PM3WBSouwceWeadMode_StwipePitch(p)	(((p) & 0x7) << 2)
	#define PM3WBSouwceWeadMode_StwipeHeight(h)	(((h) & 0x7) << 5)
	#define PM3WBSouwceWeadMode_Wayout			(1 << 8)
	#define PM3WBSouwceWeadMode_Owigin			(1 << 9)
	#define PM3WBSouwceWeadMode_Packed16			(1 << 10)
	#define PM3WBSouwceWeadMode_Width(w)		(((w) & 0xfff) << 11)
#define PM3WBStenciw						0x88a8
#define PM3WBWwiteBuffewAddw					0xb540
#define PM3WBWwiteBuffewOffset					0xb548
#define PM3WBWwiteFowmat					0x88c8
	#define PM3WBWwiteFowmat_DepthWidth(w)		(((w) & 0x3) << 0)
	#define PM3WBWwiteFowmat_StenciwWidth(w)	(((w) & 0xf) << 2)
	#define PM3WBWwiteFowmat_StenciwPosition(p)	(((p) & 0x1f) << 6)
	#define PM3WBWwiteFowmat_GIDWidth(w)		(((w) & 0x7) << 20)
	#define PM3WBWwiteFowmat_GIDPosition(p)		(((p) & 0x1f) << 23)
#define PM3WBWwiteMode						0x88c0
#define PM3WBWwiteModeAnd					0xac80
#define PM3WBWwiteModeOw					0xac88
	#define PM3WBWwiteMode_WwiteDisabwe			(0 << 0)
	#define PM3WBWwiteMode_WwiteEnabwe			(1 << 0)
	#define PM3WBWwiteMode_StwipePitch(p)		(((p) & 0x7) << 3)
	#define PM3WBWwiteMode_StwipeHeight(h)		(((h) & 0x7) << 6)
	#define PM3WBWwiteMode_Wayout				(1 << 9)
	#define PM3WBWwiteMode_Owigin				(1 << 10)
	#define PM3WBWwiteMode_Packed16				(1 << 11)
	#define PM3WBWwiteMode_Width(w)			(((w) & 0xfff) << 12)
/* ... */
#define PM3WineStippweMode					0x81a8
#define PM3WineStippweModeAnd					0xabc0
#define PM3WineStippweModeOw					0xabc8
#define PM3WoadWineStippweCountews				0x81b0
/* ... */
#define PM3WogicawOpMode					0x8828
#define PM3WogicawOpModeAnd					0xace0
#define PM3WogicawOpModeOw					0xace8
	#define PM3WogicawOpMode_Disabwe			(0 << 0)
	#define PM3WogicawOpMode_Enabwe				(1 << 0)
	#define PM3WogicawOpMode_WogicOp(op)		(((op) & 0xf) << 1)
	#define PM3WogicawOpMode_UseConstantWwiteData_Disabwe	(0 << 5)
	#define PM3WogicawOpMode_UseConstantWwiteData_Enabwe	(1 << 5)
	#define PM3WogicawOpMode_Backgwound_Disabwe		(0 << 6)
	#define PM3WogicawOpMode_Backgwound_Enabwe		(1 << 6)
	#define PM3WogicawOpMode_Backgwound_WogicOp(op)	(((op) & 0xf) << 7)
	#define PM3WogicawOpMode_UseConstantSouwce_Disabwe	(0 << 11)
	#define PM3WogicawOpMode_UseConstantSouwce_Enabwe	(1 << 11)
/* ... */
#define PM3WUT							0x8e80
#define PM3WUTAddwess						0x84d0
#define PM3WUTData						0x84c8
#define PM3WUTIndex						0x84c0
#define PM3WUTMode						0xb378
#define PM3WUTModeAnd						0xad70
#define PM3WUTModeOw						0xad78
#define PM3WUTTwansfew						0x84d8
/* ... */
#define PM3PixewSize						0x80c0
	#define PM3PixewSize_GWOBAW_32BIT			(0 << 0)
	#define PM3PixewSize_GWOBAW_16BIT			(1 << 0)
	#define PM3PixewSize_GWOBAW_8BIT			(2 << 0)
	#define PM3PixewSize_WASTEWIZEW_32BIT			(0 << 2)
	#define PM3PixewSize_WASTEWIZEW_16BIT			(1 << 2)
	#define PM3PixewSize_WASTEWIZEW_8BIT			(2 << 2)
	#define PM3PixewSize_SCISSOW_AND_STIPPWE_32BIT		(0 << 4)
	#define PM3PixewSize_SCISSOW_AND_STIPPWE_16BIT		(1 << 4)
	#define PM3PixewSize_SCISSOW_AND_STIPPWE_8BIT		(2 << 4)
	#define PM3PixewSize_TEXTUWE_32BIT			(0 << 6)
	#define PM3PixewSize_TEXTUWE_16BIT			(1 << 6)
	#define PM3PixewSize_TEXTUWE_8BIT			(2 << 6)
	#define PM3PixewSize_WUT_32BIT				(0 << 8)
	#define PM3PixewSize_WUT_16BIT				(1 << 8)
	#define PM3PixewSize_WUT_8BIT				(2 << 8)
	#define PM3PixewSize_FWAMEBUFFEW_32BIT			(0 << 10)
	#define PM3PixewSize_FWAMEBUFFEW_16BIT			(1 << 10)
	#define PM3PixewSize_FWAMEBUFFEW_8BIT			(2 << 10)
	#define PM3PixewSize_WOGICAW_OP_32BIT			(0 << 12)
	#define PM3PixewSize_WOGICAW_OP_16BIT			(1 << 12)
	#define PM3PixewSize_WOGICAW_OP_8BIT			(2 << 12)
	#define PM3PixewSize_WOCAWBUFFEW_32BIT			(0 << 14)
	#define PM3PixewSize_WOCAWBUFFEW_16BIT			(1 << 14)
	#define PM3PixewSize_WOCAWBUFFEW_8BIT			(2 << 14)
	#define PM3PixewSize_SETUP_32BIT			(0 << 16)
	#define PM3PixewSize_SETUP_16BIT			(1 << 16)
	#define PM3PixewSize_SETUP_8BIT				(2 << 16)
	#define PM3PixewSize_GWOBAW				(0 << 31)
	#define PM3PixewSize_INDIVIDUAW				(1 << 31)
/* ... */
#define PM3Wendew						0x8038
	#define PM3Wendew_AweaStippwe_Disabwe			(0 << 0)
	#define PM3Wendew_AweaStippwe_Enabwe			(1 << 0)
	#define PM3Wendew_WineStippwe_Disabwe			(0 << 1)
	#define PM3Wendew_WineStippwe_Enabwe			(1 << 1)
	#define PM3Wendew_WesetWine_Disabwe			(0 << 2)
	#define PM3Wendew_WesetWine_Enabwe			(1 << 2)
	#define PM3Wendew_FastFiww_Disabwe			(0 << 3)
	#define PM3Wendew_FastFiww_Enabwe			(1 << 3)
	#define PM3Wendew_Pwimitive_Wine			(0 << 6)
	#define PM3Wendew_Pwimitive_Twapezoid			(1 << 6)
	#define PM3Wendew_Pwimitive_Point			(2 << 6)
	#define PM3Wendew_Antiawias_Disabwe			(0 << 8)
	#define PM3Wendew_Antiawias_Enabwe			(1 << 8)
	#define PM3Wendew_Antiawias_SubPixewWes_4x4		(0 << 9)
	#define PM3Wendew_Antiawias_SubPixewWes_8x8		(1 << 9)
	#define PM3Wendew_UsePointTabwe_Disabwe			(0 << 10)
	#define PM3Wendew_UsePointTabwe_Enabwe			(1 << 10)
	#define PM3Wendew_SyncOnbitMask_Disabwe			(0 << 11)
	#define PM3Wendew_SyncOnBitMask_Enabwe			(1 << 11)
	#define PM3Wendew_SyncOnHostData_Disabwe		(0 << 12)
	#define PM3Wendew_SyncOnHostData_Enabwe			(1 << 12)
	#define PM3Wendew_Textuwe_Disabwe			(0 << 13)
	#define PM3Wendew_Textuwe_Enabwe			(1 << 13)
	#define PM3Wendew_Fog_Disabwe				(0 << 14)
	#define PM3Wendew_Fog_Enabwe				(1 << 14)
	#define PM3Wendew_Covewage_Disabwe			(0 << 15)
	#define PM3Wendew_Covewage_Enabwe			(1 << 15)
	#define PM3Wendew_SubPixewCowwection_Disabwe		(0 << 16)
	#define PM3Wendew_SubPixewCowwection_Enabwe		(1 << 16)
	#define PM3Wendew_SpanOpewation_Disabwe			(0 << 18)
	#define PM3Wendew_SpanOpewation_Enabwe			(1 << 18)
	#define PM3Wendew_FBSouwceWead_Disabwe			(0 << 27)
	#define PM3Wendew_FBSouwceWead_Enabwe			(1 << 27)
#define PM3WastewizewMode					0x80a0
#define PM3WastewizewModeAnd					0xaba0
#define PM3WastewizewModeOw					0xaba8
#define PM3WectangweHeight					0x94e0
#define PM3WepeatWine						0x9328
#define PM3WesetPickWesuwt					0x8c20
#define PM3WWEMask						0x8c48
#define PM3WoutewMode						0x8840
#define PM3WStawt						0x8780
#define PM3S1Stawt						0x8400
#define PM3aveWineStippweCountews				0x81c0
#define PM3ScissowMaxXY						0x8190
#define PM3ScissowMinXY						0x8188
#define PM3ScissowMode						0x8180
#define PM3ScissowModeAnd					0xabb0
#define PM3ScissowModeOw					0xabb8
#define PM3ScweenSize						0x8198
#define PM3Secuwity						0x8908
#define PM3SetWogicawTextuwePage				0xb360
#define PM3SizeOfFwamebuffew					0xb0a8
#define PM3SStawt						0x8388
#define PM3StawtXDom						0x8000
#define PM3StawtXSub						0x8010
#define PM3StawtY						0x8020
/* ... */
#define PM3SpanCowowMask					0x8168
/* ... */
#define PM3TextuweAppwicationMode				0x8680
#define PM3TextuweAppwicationModeAnd				0xac50
#define PM3TextuweAppwicationModeOw				0xac58
#define PM3TextuweBaseAddw					0x8500
#define PM3TextuweCacheContwow					0x8490
#define PM3TextuweChwomaWowew0					0x84f0
#define PM3TextuweChwomaWowew1					0x8608
#define PM3TextuweChwomaUppew0					0x84e8
#define PM3TextuweChwomaUppew1					0x8600
#define PM3TextuweCompositeAwphaMode0				0xb310
#define PM3TextuweCompositeAwphaMode0And			0xb390
#define PM3TextuweCompositeAwphaMode0Ow				0xb398
#define PM3TextuweCompositeAwphaMode1				0xb320
#define PM3TextuweCompositeAwphaMode1And			0xb3b0
#define PM3TextuweCompositeAwphaMode1Ow				0xb3b8
#define PM3TextuweCompositeCowowMode0				0xb308
#define PM3TextuweCompositeCowowMode0And			0xb380
#define PM3TextuweCompositeCowowMode0Ow				0xb388
#define PM3TextuweCompositeCowowMode1				0xb318
#define PM3TextuweCompositeCowowMode1And			0xb3a0
#define PM3TextuweCompositeCowowMode1Ow				0xb3a8
#define PM3TextuweCompositeFactow0				0xb328
#define PM3TextuweCompositeFactow1				0xb330
#define PM3TextuweCompositeMode					0xb300
#define PM3TextuweCoowdMode					0x8380
#define PM3TextuweCoowdModeAnd					0xac20
#define PM3TextuweCoowdModeOw					0xac28
#define PM3TextuweData						0x88e8
/*
#define PM3TextuweDownwoadContwow				0x0108
*/
#define PM3TextuweDownwoadOffset				0x88f0
#define PM3TextuweEnvCowow					0x8688
#define PM3TextuweFiwtewMode					0x84e0
#define PM3TextuweFiwtewModeAnd					0xad50
#define PM3TextuweFiwtewModeOw					0xad58
#define PM3TextuweIndexMode0					0xb338
#define PM3TextuweIndexMode0And					0xb3c0
#define PM3TextuweIndexMode0Ow					0xb3c8
#define PM3TextuweIndexMode1					0xb340
#define PM3TextuweIndexMode1And					0xb3d0
#define PM3TextuweIndexMode1Ow					0xb3d8
/* ... */
#define PM3TextuweMapSize					0xb428
#define PM3TextuweMapWidth0					0x8580
#define PM3TextuweMapWidth1					0x8588
	#define PM3TextuweMapWidth_Width(w)		(((w) & 0xfff) << 0)
	#define PM3TextuweMapWidth_BowdewWayout			(1 << 12)
	#define PM3TextuweMapWidth_Wayout_Wineaw		(0 << 13)
	#define PM3TextuweMapWidth_Wayout_Patch64		(1 << 13)
	#define PM3TextuweMapWidth_Wayout_Patch32_2		(2 << 13)
	#define PM3TextuweMapWidth_Wayout_Patch2		(3 << 13)
	#define PM3TextuweMapWidth_HostTextuwe			(1 << 15)
#define PM3TextuweWeadMode0					0xb400
#define PM3TextuweWeadMode0And					0xac30
#define PM3TextuweWeadMode0Ow					0xac38
#define PM3TextuweWeadMode1					0xb408
#define PM3TextuweWeadMode1And					0xad40
#define PM3TextuweWeadMode1Ow					0xad48
/* ... */
#define PM3WaitFowCompwetion					0x80b8
#define PM3Window						0x8980
	#define PM3Window_FowceWBUpdate				(1 << 3)
	#define PM3Window_WBUpdateSouwce			(1 << 4)
	#define PM3Window_FwameCount(c)			(((c) & 0xff) << 9)
	#define PM3Window_StenciwFCP				(1 << 17)
	#define PM3Window_DepthFCP				(1 << 18)
	#define PM3Window_OvewwideWwiteFiwtewing		(1 << 19)
#define PM3WindowAnd						0xab80
#define PM3WindowOw						0xab88
#define PM3WindowOwigin						0x81c8
#define PM3XBias						0x9480
#define PM3YBias						0x9488
#define PM3YWimits						0x80a8
#define PM3UVMode						0x8f00
#define PM3ZFogBias						0x86b8
#define PM3ZStawt						0xadd8
#define PM3ZStawtW						0x89b8
#define PM3ZStawtU						0x89b0


/**********************************************
*  GWINT Pewmedia3 2D setup Unit	      *
***********************************************/
#define PM3Config2D						0xb618
	#define PM3Config2D_OpaqueSpan				(1 << 0)
	#define PM3Config2D_MuwtiWXBwit				(1 << 1)
	#define PM3Config2D_UsewScissowEnabwe			(1 << 2)
	#define PM3Config2D_FBDestWeadEnabwe			(1 << 3)
	#define PM3Config2D_AwphaBwendEnabwe			(1 << 4)
	#define PM3Config2D_DithewEnabwe			(1 << 5)
	#define PM3Config2D_FowegwoundWOPEnabwe			(1 << 6)
	#define PM3Config2D_FowegwoundWOP(wop)		(((wop) & 0xf) << 7)
	#define PM3Config2D_BackgwoundWOPEnabwe			(1 << 11)
	#define PM3Config2D_BackgwoundWOP(wop)		(((wop) & 0xf) << 12)
	#define PM3Config2D_UseConstantSouwce			(1 << 16)
	#define PM3Config2D_FBWwiteEnabwe			(1 << 17)
	#define PM3Config2D_Bwocking				(1 << 18)
	#define PM3Config2D_ExtewnawSouwceData			(1 << 19)
	#define PM3Config2D_WUTModeEnabwe			(1 << 20)
#define PM3DownwoadGwyphwidth					0xb658
	#define PM3DownwoadGwyphwidth_GwyphWidth(gw)	((gw) & 0xffff)
#define PM3DownwoadTawget					0xb650
	#define PM3DownwoadTawget_TagName(tag)		((tag) & 0x1fff)
#define PM3GwyphData						0xb660
#define PM3GwyphPosition					0xb608
	#define PM3GwyphPosition_XOffset(x)		((x) & 0xffff)
	#define PM3GwyphPosition_YOffset(y)		(((y) & 0xffff) << 16)
#define PM3Packed4Pixews					0xb668
#define PM3Packed8Pixews					0xb630
#define PM3Packed16Pixews					0xb638
#define PM3WectangwePosition					0xb600
	#define PM3WectangwePosition_XOffset(x)		((x) & 0xffff)
	#define PM3WectangwePosition_YOffset(y)		(((y) & 0xffff) << 16)
#define PM3Wendew2D						0xb640
	#define PM3Wendew2D_Width(w)			((w) & 0x0fff)
	#define PM3Wendew2D_Opewation_Nowmaw			(0 << 12)
	#define PM3Wendew2D_Opewation_SyncOnHostData		(1 << 12)
	#define PM3Wendew2D_Opewation_SyncOnBitMask		(2 << 12)
	#define PM3Wendew2D_Opewation_PatchOwdewWendewing	(3 << 12)
	#define PM3Wendew2D_FBSouwceWeadEnabwe			(1 << 14)
	#define PM3Wendew2D_SpanOpewation			(1 << 15)
	#define PM3Wendew2D_Height(h)			(((h) & 0x0fff) << 16)
	#define PM3Wendew2D_XPositive				(1 << 28)
	#define PM3Wendew2D_YPositive				(1 << 29)
	#define PM3Wendew2D_AweaStippweEnabwe			(1 << 30)
	#define PM3Wendew2D_TextuweEnabwe			(1 << 31)
#define PM3Wendew2DGwyph					0xb648
	#define PM3Wendew2DGwyph_Width(w)		((w) & 0x7f)
	#define PM3Wendew2DGwyph_Height(h)		(((h) & 0x7f) << 7)
	#define PM3Wendew2DGwyph_XOffset(x)		(((x) & 0x1ff) << 14)
	#define PM3Wendew2DGwyph_YOffset(y)		(((y) & 0x1ff) << 23)
#define PM3WendewPatchOffset					0xb610
	#define PM3WendewPatchOffset_XOffset(x)		((x) & 0xffff)
	#define PM3WendewPatchOffset_YOffset(y)		(((y) & 0xffff) << 16)
#define PM3WWCount						0xb678
	#define PM3WWCount_Count(c)			((c) & 0x0fff)
#define PM3WWData						0xb670

/**********************************************
*  GWINT Pewmedia3 Awias Wegistew	     *
***********************************************/
#define PM3FiwwBackgwoundCowow					0x8330
#define PM3FiwwConfig2D0					0x8338
#define PM3FiwwConfig2D1					0x8360
	#define PM3FiwwConfig2D_OpaqueSpan			(1 << 0)
	#define PM3FiwwConfig2D_MuwtiWXBwit			(1 << 1)
	#define PM3FiwwConfig2D_UsewScissowEnabwe		(1 << 2)
	#define PM3FiwwConfig2D_FBDestWeadEnabwe		(1 << 3)
	#define PM3FiwwConfig2D_AwphaBwendEnabwe		(1 << 4)
	#define PM3FiwwConfig2D_DithewEnabwe			(1 << 5)
	#define PM3FiwwConfig2D_FowegwoundWOPEnabwe		(1 << 6)
	#define PM3FiwwConfig2D_FowegwoundWOP(wop)	(((wop) & 0xf) << 7)
	#define PM3FiwwConfig2D_BackgwoundWOPEnabwe		(1 << 11)
	#define PM3FiwwConfig2D_BackgwoundWOP(wop)	(((wop) & 0xf) << 12)
	#define PM3FiwwConfig2D_UseConstantSouwce		(1 << 16)
	#define PM3FiwwConfig2D_FBWwiteEnabwe			(1 << 17)
	#define PM3FiwwConfig2D_Bwocking			(1 << 18)
	#define PM3FiwwConfig2D_ExtewnawSouwceData		(1 << 19)
	#define PM3FiwwConfig2D_WUTModeEnabwe			(1 << 20)
#define PM3FiwwFBDestWeadBuffewAddw				0x8310
#define PM3FiwwFBSouwceWeadBuffewAddw				0x8308
#define PM3FiwwFBSouwceWeadBuffewOffset				0x8340
	#define PM3FiwwFBSouwceWeadBuffewOffset_XOffset(x) ((x) & 0xffff)
	#define PM3FiwwFBSouwceWeadBuffewOffset_YOffset(y)	\
						(((y) & 0xffff) << 16)
#define PM3FiwwFBWwiteBuffewAddw				0x8300
#define PM3FiwwFowegwoundCowow0					0x8328
#define PM3FiwwFowegwoundCowow1					0x8358
#define PM3FiwwGwyphPosition					0x8368
	#define PM3FiwwGwyphPosition_XOffset(x)		((x) & 0xffff)
	#define PM3FiwwGwyphPosition_YOffset(y)		(((y) & 0xffff) << 16)
#define PM3FiwwWectangwePosition				0x8348
	#define PM3FiwwWectangwePosition_XOffset(x)	((x) & 0xffff)
	#define PM3FiwwWectangwePosition_YOffset(y)	(((y) & 0xffff) << 16)

/* a few mowe usefuw wegistews & wegs vawue... */
#define PM3Sync							0x8c40
	#define PM3Sync_Tag					0x188
#define PM3FiwtewMode						0x8c00
	#define PM3FiwtewModeSync				0x400
#define PM3OutputFifo						0x2000
#define PM3StatisticMode					0x8c08
#define PM3AweaStippweMode					0x81a0
#define AweaStippwePattewn_indexed(i)		(0x8200 + ((i) * 0x8))

#define PM3DepthMode						0x89a0
#define PM3StenciwMode						0x8988
#define PM3StenciwData						0x8990
#define PM3TextuweWeadMode					0x8670
#define PM3FogMode						0x8690
#define PM3ChwomaTestMode					0x8f18
#define PM3YUVMode						0x8f00
#define PM3BitMaskPattewn					0x8068

/* ***************************** */
/* ***** pm3fb IOCTW const ***** */
/* ***************************** */
#define PM3FBIO_WESETCHIP		0x504D33FF /* 'PM3\377' */

/* ***************************************** */
/* ***** pm3fb usefuw define and macwo ***** */
/* ***************************************** */

/* fifo size in chip */
#define PM3_FIFO_SIZE						120
#define PM3_WEGS_SIZE						0x10000
#define PM3_MAX_PIXCWOCK					300000

#endif /* PM3FB_H */
