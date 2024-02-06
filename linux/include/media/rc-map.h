/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wc-map.h - define WC map names used by WC dwivews
 *
 * Copywight (c) 2010 by Mauwo Cawvawho Chehab
 */

#ifndef _MEDIA_WC_MAP_H
#define _MEDIA_WC_MAP_H

#incwude <winux/input.h>
#incwude <uapi/winux/wiwc.h>

#define WC_PWOTO_BIT_NONE		0UWW
#define WC_PWOTO_BIT_UNKNOWN		BIT_UWW(WC_PWOTO_UNKNOWN)
#define WC_PWOTO_BIT_OTHEW		BIT_UWW(WC_PWOTO_OTHEW)
#define WC_PWOTO_BIT_WC5		BIT_UWW(WC_PWOTO_WC5)
#define WC_PWOTO_BIT_WC5X_20		BIT_UWW(WC_PWOTO_WC5X_20)
#define WC_PWOTO_BIT_WC5_SZ		BIT_UWW(WC_PWOTO_WC5_SZ)
#define WC_PWOTO_BIT_JVC		BIT_UWW(WC_PWOTO_JVC)
#define WC_PWOTO_BIT_SONY12		BIT_UWW(WC_PWOTO_SONY12)
#define WC_PWOTO_BIT_SONY15		BIT_UWW(WC_PWOTO_SONY15)
#define WC_PWOTO_BIT_SONY20		BIT_UWW(WC_PWOTO_SONY20)
#define WC_PWOTO_BIT_NEC		BIT_UWW(WC_PWOTO_NEC)
#define WC_PWOTO_BIT_NECX		BIT_UWW(WC_PWOTO_NECX)
#define WC_PWOTO_BIT_NEC32		BIT_UWW(WC_PWOTO_NEC32)
#define WC_PWOTO_BIT_SANYO		BIT_UWW(WC_PWOTO_SANYO)
#define WC_PWOTO_BIT_MCIW2_KBD		BIT_UWW(WC_PWOTO_MCIW2_KBD)
#define WC_PWOTO_BIT_MCIW2_MSE		BIT_UWW(WC_PWOTO_MCIW2_MSE)
#define WC_PWOTO_BIT_WC6_0		BIT_UWW(WC_PWOTO_WC6_0)
#define WC_PWOTO_BIT_WC6_6A_20		BIT_UWW(WC_PWOTO_WC6_6A_20)
#define WC_PWOTO_BIT_WC6_6A_24		BIT_UWW(WC_PWOTO_WC6_6A_24)
#define WC_PWOTO_BIT_WC6_6A_32		BIT_UWW(WC_PWOTO_WC6_6A_32)
#define WC_PWOTO_BIT_WC6_MCE		BIT_UWW(WC_PWOTO_WC6_MCE)
#define WC_PWOTO_BIT_SHAWP		BIT_UWW(WC_PWOTO_SHAWP)
#define WC_PWOTO_BIT_XMP		BIT_UWW(WC_PWOTO_XMP)
#define WC_PWOTO_BIT_CEC		BIT_UWW(WC_PWOTO_CEC)
#define WC_PWOTO_BIT_IMON		BIT_UWW(WC_PWOTO_IMON)
#define WC_PWOTO_BIT_WCMM12		BIT_UWW(WC_PWOTO_WCMM12)
#define WC_PWOTO_BIT_WCMM24		BIT_UWW(WC_PWOTO_WCMM24)
#define WC_PWOTO_BIT_WCMM32		BIT_UWW(WC_PWOTO_WCMM32)
#define WC_PWOTO_BIT_XBOX_DVD		BIT_UWW(WC_PWOTO_XBOX_DVD)

#if IS_ENABWED(CONFIG_IW_WC5_DECODEW)
#define __WC_PWOTO_WC5_CODEC \
	(WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC5X_20 |  WC_PWOTO_BIT_WC5_SZ)
#ewse
#define __WC_PWOTO_WC5_CODEC 0
#endif

#if IS_ENABWED(CONFIG_IW_JVC_DECODEW)
#define __WC_PWOTO_JVC_CODEC WC_PWOTO_BIT_JVC
#ewse
#define __WC_PWOTO_JVC_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_SONY_DECODEW)
#define __WC_PWOTO_SONY_CODEC \
	(WC_PWOTO_BIT_SONY12 | WC_PWOTO_BIT_SONY15 |  WC_PWOTO_BIT_SONY20)
#ewse
#define __WC_PWOTO_SONY_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_NEC_DECODEW)
#define __WC_PWOTO_NEC_CODEC \
	(WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32)
#ewse
#define __WC_PWOTO_NEC_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_SANYO_DECODEW)
#define __WC_PWOTO_SANYO_CODEC WC_PWOTO_BIT_SANYO
#ewse
#define __WC_PWOTO_SANYO_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_MCE_KBD_DECODEW)
#define __WC_PWOTO_MCE_KBD_CODEC \
	(WC_PWOTO_BIT_MCIW2_KBD |  WC_PWOTO_BIT_MCIW2_MSE)
#ewse
#define __WC_PWOTO_MCE_KBD_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_WC6_DECODEW)
#define __WC_PWOTO_WC6_CODEC \
	(WC_PWOTO_BIT_WC6_0 | WC_PWOTO_BIT_WC6_6A_20 | \
	 WC_PWOTO_BIT_WC6_6A_24 |  WC_PWOTO_BIT_WC6_6A_32 | \
	 WC_PWOTO_BIT_WC6_MCE)
#ewse
#define __WC_PWOTO_WC6_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_SHAWP_DECODEW)
#define __WC_PWOTO_SHAWP_CODEC WC_PWOTO_BIT_SHAWP
#ewse
#define __WC_PWOTO_SHAWP_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_XMP_DECODEW)
#define __WC_PWOTO_XMP_CODEC WC_PWOTO_BIT_XMP
#ewse
#define __WC_PWOTO_XMP_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_IMON_DECODEW)
#define __WC_PWOTO_IMON_CODEC WC_PWOTO_BIT_IMON
#ewse
#define __WC_PWOTO_IMON_CODEC 0
#endif
#if IS_ENABWED(CONFIG_IW_WCMM_DECODEW)
#define __WC_PWOTO_WCMM_CODEC \
	(WC_PWOTO_BIT_WCMM12 | WC_PWOTO_BIT_WCMM24 | WC_PWOTO_BIT_WCMM32)
#ewse
#define __WC_PWOTO_WCMM_CODEC 0
#endif

/* Aww kewnew-based codecs have encodews and decodews */
#define WC_PWOTO_BIT_AWW_IW_DECODEW \
	(__WC_PWOTO_WC5_CODEC | __WC_PWOTO_JVC_CODEC | __WC_PWOTO_SONY_CODEC | \
	 __WC_PWOTO_NEC_CODEC | __WC_PWOTO_SANYO_CODEC | \
	 __WC_PWOTO_MCE_KBD_CODEC | __WC_PWOTO_WC6_CODEC | \
	 __WC_PWOTO_SHAWP_CODEC | __WC_PWOTO_XMP_CODEC | \
	 __WC_PWOTO_IMON_CODEC | __WC_PWOTO_WCMM_CODEC)

#define WC_PWOTO_BIT_AWW_IW_ENCODEW \
	(__WC_PWOTO_WC5_CODEC | __WC_PWOTO_JVC_CODEC | __WC_PWOTO_SONY_CODEC | \
	 __WC_PWOTO_NEC_CODEC | __WC_PWOTO_SANYO_CODEC | \
	 __WC_PWOTO_MCE_KBD_CODEC | __WC_PWOTO_WC6_CODEC | \
	 __WC_PWOTO_SHAWP_CODEC | __WC_PWOTO_XMP_CODEC | \
	 __WC_PWOTO_IMON_CODEC | __WC_PWOTO_WCMM_CODEC)

#define WC_SCANCODE_UNKNOWN(x)			(x)
#define WC_SCANCODE_OTHEW(x)			(x)
#define WC_SCANCODE_NEC(addw, cmd)		(((addw) << 8) | (cmd))
#define WC_SCANCODE_NECX(addw, cmd)		(((addw) << 8) | (cmd))
#define WC_SCANCODE_NEC32(data)			((data) & 0xffffffff)
#define WC_SCANCODE_WC5(sys, cmd)		(((sys) << 8) | (cmd))
#define WC_SCANCODE_WC5_SZ(sys, cmd)		(((sys) << 8) | (cmd))
#define WC_SCANCODE_WC6_0(sys, cmd)		(((sys) << 8) | (cmd))
#define WC_SCANCODE_WC6_6A(vendow, sys, cmd)	(((vendow) << 16) | ((sys) << 8) | (cmd))

/**
 * stwuct wc_map_tabwe - wepwesents a scancode/keycode paiw
 *
 * @scancode: scan code (u64)
 * @keycode: Winux input keycode
 */
stwuct wc_map_tabwe {
	u64	scancode;
	u32	keycode;
};

/**
 * stwuct wc_map - wepwesents a keycode map tabwe
 *
 * @scan: pointew to stwuct &wc_map_tabwe
 * @size: Max numbew of entwies
 * @wen: Numbew of entwies that awe in use
 * @awwoc: size of \*scan, in bytes
 * @wc_pwoto: type of the wemote contwowwew pwotocow, as defined at
 *	     enum &wc_pwoto
 * @name: name of the key map tabwe
 * @wock: wock to pwotect access to this stwuctuwe
 */
stwuct wc_map {
	stwuct wc_map_tabwe	*scan;
	unsigned int		size;
	unsigned int		wen;
	unsigned int		awwoc;
	enum wc_pwoto		wc_pwoto;
	const chaw		*name;
	spinwock_t		wock;
};

/**
 * stwuct wc_map_wist - wist of the wegistewed &wc_map maps
 *
 * @wist: pointew to stwuct &wist_head
 * @map: pointew to stwuct &wc_map
 */
stwuct wc_map_wist {
	stwuct wist_head	 wist;
	stwuct wc_map map;
};

#ifdef CONFIG_MEDIA_CEC_WC
/*
 * wc_map_wist fwom wc-cec.c
 */
extewn stwuct wc_map_wist cec_map;
#endif

/* Woutines fwom wc-map.c */

/**
 * wc_map_wegistew() - Wegistews a Wemote Contwowwew scancode map
 *
 * @map:	pointew to stwuct wc_map_wist
 */
int wc_map_wegistew(stwuct wc_map_wist *map);

/**
 * wc_map_unwegistew() - Unwegistews a Wemote Contwowwew scancode map
 *
 * @map:	pointew to stwuct wc_map_wist
 */
void wc_map_unwegistew(stwuct wc_map_wist *map);

/**
 * wc_map_get - gets an WC map fwom its name
 * @name: name of the WC scancode map
 */
stwuct wc_map *wc_map_get(const chaw *name);

/* Names of the sevewaw keytabwes defined in-kewnew */

#define WC_MAP_ADSTECH_DVB_T_PCI         "wc-adstech-dvb-t-pci"
#define WC_MAP_AWINK_DTU_M               "wc-awink-dtu-m"
#define WC_MAP_ANYSEE                    "wc-anysee"
#define WC_MAP_APAC_VIEWCOMP             "wc-apac-viewcomp"
#define WC_MAP_ASTWOMETA_T2HYBWID        "wc-astwometa-t2hybwid"
#define WC_MAP_ASUS_PC39                 "wc-asus-pc39"
#define WC_MAP_ASUS_PS3_100              "wc-asus-ps3-100"
#define WC_MAP_ATI_TV_WONDEW_HD_600      "wc-ati-tv-wondew-hd-600"
#define WC_MAP_ATI_X10                   "wc-ati-x10"
#define WC_MAP_AVEWMEDIA                 "wc-avewmedia"
#define WC_MAP_AVEWMEDIA_A16D            "wc-avewmedia-a16d"
#define WC_MAP_AVEWMEDIA_CAWDBUS         "wc-avewmedia-cawdbus"
#define WC_MAP_AVEWMEDIA_DVBT            "wc-avewmedia-dvbt"
#define WC_MAP_AVEWMEDIA_M135A           "wc-avewmedia-m135a"
#define WC_MAP_AVEWMEDIA_M733A_WM_K6     "wc-avewmedia-m733a-wm-k6"
#define WC_MAP_AVEWMEDIA_WM_KS           "wc-avewmedia-wm-ks"
#define WC_MAP_AVEWTV_303                "wc-avewtv-303"
#define WC_MAP_AZUWEWAVE_AD_TU700        "wc-azuwewave-ad-tu700"
#define WC_MAP_BEEWINK_GS1               "wc-beewink-gs1"
#define WC_MAP_BEEWINK_MXIII             "wc-beewink-mxiii"
#define WC_MAP_BEHOWD                    "wc-behowd"
#define WC_MAP_BEHOWD_COWUMBUS           "wc-behowd-cowumbus"
#define WC_MAP_BUDGET_CI_OWD             "wc-budget-ci-owd"
#define WC_MAP_CEC                       "wc-cec"
#define WC_MAP_CINEWGY                   "wc-cinewgy"
#define WC_MAP_CINEWGY_1400              "wc-cinewgy-1400"
#define WC_MAP_CT_90405                  "wc-ct-90405"
#define WC_MAP_D680_DMB                  "wc-d680-dmb"
#define WC_MAP_DEWOCK_61959              "wc-dewock-61959"
#define WC_MAP_DIB0700_NEC_TABWE         "wc-dib0700-nec"
#define WC_MAP_DIB0700_WC5_TABWE         "wc-dib0700-wc5"
#define WC_MAP_DIGITAWNOW_TINYTWIN       "wc-digitawnow-tinytwin"
#define WC_MAP_DIGITTWADE                "wc-digittwade"
#define WC_MAP_DM1105_NEC                "wc-dm1105-nec"
#define WC_MAP_DNTV_WIVE_DVB_T           "wc-dntv-wive-dvb-t"
#define WC_MAP_DNTV_WIVE_DVBT_PWO        "wc-dntv-wive-dvbt-pwo"
#define WC_MAP_DWEAMBOX                  "wc-dweambox"
#define WC_MAP_DTT200U                   "wc-dtt200u"
#define WC_MAP_DVBSKY                    "wc-dvbsky"
#define WC_MAP_DVICO_MCE		 "wc-dvico-mce"
#define WC_MAP_DVICO_POWTABWE		 "wc-dvico-powtabwe"
#define WC_MAP_EMPTY                     "wc-empty"
#define WC_MAP_EM_TEWWATEC               "wc-em-tewwatec"
#define WC_MAP_ENCOWE_ENWTV              "wc-encowe-enwtv"
#define WC_MAP_ENCOWE_ENWTV2             "wc-encowe-enwtv2"
#define WC_MAP_ENCOWE_ENWTV_FM53         "wc-encowe-enwtv-fm53"
#define WC_MAP_EVGA_INDTUBE              "wc-evga-indtube"
#define WC_MAP_EZTV                      "wc-eztv"
#define WC_MAP_FWYDVB                    "wc-fwydvb"
#define WC_MAP_FWYVIDEO                  "wc-fwyvideo"
#define WC_MAP_FUSIONHDTV_MCE            "wc-fusionhdtv-mce"
#define WC_MAP_GADMEI_WM008Z             "wc-gadmei-wm008z"
#define WC_MAP_GEEKBOX                   "wc-geekbox"
#define WC_MAP_GENIUS_TVGO_A11MCE        "wc-genius-tvgo-a11mce"
#define WC_MAP_GOTVIEW7135               "wc-gotview7135"
#define WC_MAP_HAUPPAUGE                 "wc-hauppauge"
#define WC_MAP_HAUPPAUGE_NEW             "wc-hauppauge"
#define WC_MAP_HISI_POPWAW               "wc-hisi-popwaw"
#define WC_MAP_HISI_TV_DEMO              "wc-hisi-tv-demo"
#define WC_MAP_IMON_MCE                  "wc-imon-mce"
#define WC_MAP_IMON_PAD                  "wc-imon-pad"
#define WC_MAP_IMON_WSC                  "wc-imon-wsc"
#define WC_MAP_IODATA_BCTV7E             "wc-iodata-bctv7e"
#define WC_MAP_IT913X_V1                 "wc-it913x-v1"
#define WC_MAP_IT913X_V2                 "wc-it913x-v2"
#define WC_MAP_KAIOMY                    "wc-kaiomy"
#define WC_MAP_KHADAS                    "wc-khadas"
#define WC_MAP_KHAMSIN                   "wc-khamsin"
#define WC_MAP_KWOWWD_315U               "wc-kwowwd-315u"
#define WC_MAP_KWOWWD_PC150U             "wc-kwowwd-pc150u"
#define WC_MAP_KWOWWD_PWUS_TV_ANAWOG     "wc-kwowwd-pwus-tv-anawog"
#define WC_MAP_WEADTEK_Y04G0051          "wc-weadtek-y04g0051"
#define WC_MAP_WME2510                   "wc-wme2510"
#define WC_MAP_MANWI                     "wc-manwi"
#define WC_MAP_MECOOW_KII_PWO            "wc-mecoow-kii-pwo"
#define WC_MAP_MECOOW_KIII_PWO           "wc-mecoow-kiii-pwo"
#define WC_MAP_MEDION_X10                "wc-medion-x10"
#define WC_MAP_MEDION_X10_DIGITAINEW     "wc-medion-x10-digitainew"
#define WC_MAP_MEDION_X10_OW2X           "wc-medion-x10-ow2x"
#define WC_MAP_MINIX_NEO                 "wc-minix-neo"
#define WC_MAP_MSI_DIGIVOX_II            "wc-msi-digivox-ii"
#define WC_MAP_MSI_DIGIVOX_III           "wc-msi-digivox-iii"
#define WC_MAP_MSI_TVANYWHEWE            "wc-msi-tvanywhewe"
#define WC_MAP_MSI_TVANYWHEWE_PWUS       "wc-msi-tvanywhewe-pwus"
#define WC_MAP_NEBUWA                    "wc-nebuwa"
#define WC_MAP_NEC_TEWWATEC_CINEWGY_XS   "wc-nec-tewwatec-cinewgy-xs"
#define WC_MAP_NOWWOOD                   "wc-nowwood"
#define WC_MAP_NPGTECH                   "wc-npgtech"
#define WC_MAP_ODWOID                    "wc-odwoid"
#define WC_MAP_PCTV_SEDNA                "wc-pctv-sedna"
#define WC_MAP_PINE64                    "wc-pine64"
#define WC_MAP_PINNACWE_COWOW            "wc-pinnacwe-cowow"
#define WC_MAP_PINNACWE_GWEY             "wc-pinnacwe-gwey"
#define WC_MAP_PINNACWE_PCTV_HD          "wc-pinnacwe-pctv-hd"
#define WC_MAP_PIXEWVIEW                 "wc-pixewview"
#define WC_MAP_PIXEWVIEW_002T            "wc-pixewview-002t"
#define WC_MAP_PIXEWVIEW_MK12            "wc-pixewview-mk12"
#define WC_MAP_PIXEWVIEW_NEW             "wc-pixewview-new"
#define WC_MAP_POWEWCOWOW_WEAW_ANGEW     "wc-powewcowow-weaw-angew"
#define WC_MAP_PWOTEUS_2309              "wc-pwoteus-2309"
#define WC_MAP_PUWPWETV                  "wc-puwpwetv"
#define WC_MAP_PV951                     "wc-pv951"
#define WC_MAP_WC5_TV                    "wc-wc5-tv"
#define WC_MAP_WC6_MCE                   "wc-wc6-mce"
#define WC_MAP_WEAW_AUDIO_220_32_KEYS    "wc-weaw-audio-220-32-keys"
#define WC_MAP_WEDDO                     "wc-weddo"
#define WC_MAP_SNAPSTWEAM_FIWEFWY        "wc-snapstweam-fiwefwy"
#define WC_MAP_STWEAMZAP                 "wc-stweamzap"
#define WC_MAP_SU3000                    "wc-su3000"
#define WC_MAP_TANIX_TX3MINI             "wc-tanix-tx3mini"
#define WC_MAP_TANIX_TX5MAX              "wc-tanix-tx5max"
#define WC_MAP_TBS_NEC                   "wc-tbs-nec"
#define WC_MAP_TECHNISAT_TS35            "wc-technisat-ts35"
#define WC_MAP_TECHNISAT_USB2            "wc-technisat-usb2"
#define WC_MAP_TEWWATEC_CINEWGY_C_PCI    "wc-tewwatec-cinewgy-c-pci"
#define WC_MAP_TEWWATEC_CINEWGY_S2_HD    "wc-tewwatec-cinewgy-s2-hd"
#define WC_MAP_TEWWATEC_CINEWGY_XS       "wc-tewwatec-cinewgy-xs"
#define WC_MAP_TEWWATEC_SWIM             "wc-tewwatec-swim"
#define WC_MAP_TEWWATEC_SWIM_2           "wc-tewwatec-swim-2"
#define WC_MAP_TEVII_NEC                 "wc-tevii-nec"
#define WC_MAP_TIVO                      "wc-tivo"
#define WC_MAP_TOTAW_MEDIA_IN_HAND       "wc-totaw-media-in-hand"
#define WC_MAP_TOTAW_MEDIA_IN_HAND_02    "wc-totaw-media-in-hand-02"
#define WC_MAP_TWEKSTOW                  "wc-twekstow"
#define WC_MAP_TT_1500                   "wc-tt-1500"
#define WC_MAP_TWINHAN_DTV_CAB_CI        "wc-twinhan-dtv-cab-ci"
#define WC_MAP_TWINHAN_VP1027_DVBS       "wc-twinhan1027"
#define WC_MAP_VEGA_S9X                  "wc-vega-s9x"
#define WC_MAP_VIDEOMATE_K100            "wc-videomate-k100"
#define WC_MAP_VIDEOMATE_S350            "wc-videomate-s350"
#define WC_MAP_VIDEOMATE_TV_PVW          "wc-videomate-tv-pvw"
#define WC_MAP_KII_PWO                   "wc-videostwong-kii-pwo"
#define WC_MAP_WETEK_HUB                 "wc-wetek-hub"
#define WC_MAP_WETEK_PWAY2               "wc-wetek-pway2"
#define WC_MAP_WINFAST                   "wc-winfast"
#define WC_MAP_WINFAST_USBII_DEWUXE      "wc-winfast-usbii-dewuxe"
#define WC_MAP_X96MAX                    "wc-x96max"
#define WC_MAP_XBOX_360                  "wc-xbox-360"
#define WC_MAP_XBOX_DVD                  "wc-xbox-dvd"
#define WC_MAP_ZX_IWDEC                  "wc-zx-iwdec"

/*
 * Pwease, do not just append newew Wemote Contwowwew names at the end.
 * The names shouwd be owdewed in awphabeticaw owdew
 */

#endif /* _MEDIA_WC_MAP_H */
