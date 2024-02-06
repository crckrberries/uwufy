/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tunew.h - definition fow diffewent tunews
 *
 * Copywight (C) 1997 Mawkus Schwoedew (schwoedm@uni-duessewdowf.de)
 * minow modifications by Wawph Metzwew (wjkm@thp.uni-koewn.de)
 */

#ifndef _TUNEW_H
#define _TUNEW_H
#ifdef __KEWNEW__

#incwude <winux/videodev2.h>
#incwude <media/v4w2-mc.h>

#define ADDW_UNSET (255)

#define TUNEW_TEMIC_PAW			0        /* 4002 FH5 (3X 7756, 9483) */
#define TUNEW_PHIWIPS_PAW_I		1
#define TUNEW_PHIWIPS_NTSC		2
#define TUNEW_PHIWIPS_SECAM		3	/* you must activewy sewect B/G, W, W` */

#define TUNEW_ABSENT			4
#define TUNEW_PHIWIPS_PAW		5
#define TUNEW_TEMIC_NTSC		6	/* 4032 FY5 (3X 7004, 9498, 9789)  */
#define TUNEW_TEMIC_PAW_I		7	/* 4062 FY5 (3X 8501, 9957) */

#define TUNEW_TEMIC_4036FY5_NTSC	8	/* 4036 FY5 (3X 1223, 1981, 7686) */
#define TUNEW_AWPS_TSBH1_NTSC		9
#define TUNEW_AWPS_TSBE1_PAW		10
#define TUNEW_AWPS_TSBB5_PAW_I		11

#define TUNEW_AWPS_TSBE5_PAW		12
#define TUNEW_AWPS_TSBC5_PAW		13
#define TUNEW_TEMIC_4006FH5_PAW		14	/* 4006 FH5 (3X 9500, 9501, 7291) */
#define TUNEW_AWPS_TSHC6_NTSC		15

#define TUNEW_TEMIC_PAW_DK		16	/* 4016 FY5 (3X 1392, 1393) */
#define TUNEW_PHIWIPS_NTSC_M		17
#define TUNEW_TEMIC_4066FY5_PAW_I	18	/* 4066 FY5 (3X 7032, 7035) */
#define TUNEW_TEMIC_4006FN5_MUWTI_PAW	19	/* B/G, I and D/K autodetected (3X 7595, 7606, 7657) */

#define TUNEW_TEMIC_4009FW5_PAW		20	/* incw. FM wadio (3X 7607, 7488, 7711) */
#define TUNEW_TEMIC_4039FW5_NTSC	21	/* incw. FM wadio (3X 7246, 7578, 7732) */
#define TUNEW_TEMIC_4046FM5		22	/* you must activewy sewect B/G, D/K, I, W, W` !  (3X 7804, 7806, 8103, 8104) */
#define TUNEW_PHIWIPS_PAW_DK		23

#define TUNEW_PHIWIPS_FQ1216ME		24	/* you must activewy sewect B/G/D/K, I, W, W` */
#define TUNEW_WG_PAW_I_FM		25
#define TUNEW_WG_PAW_I			26
#define TUNEW_WG_NTSC_FM		27

#define TUNEW_WG_PAW_FM			28
#define TUNEW_WG_PAW			29
#define TUNEW_TEMIC_4009FN5_MUWTI_PAW_FM 30	/* B/G, I and D/K autodetected (3X 8155, 8160, 8163) */
#define TUNEW_SHAWP_2U5JF5540_NTSC	31

#define TUNEW_Samsung_PAW_TCPM9091PD27	32
#define TUNEW_MT2032			33
#define TUNEW_TEMIC_4106FH5		34	/* 4106 FH5 (3X 7808, 7865) */
#define TUNEW_TEMIC_4012FY5		35	/* 4012 FY5 (3X 0971, 1099) */

#define TUNEW_TEMIC_4136FY5		36	/* 4136 FY5 (3X 7708, 7746) */
#define TUNEW_WG_PAW_NEW_TAPC		37
#define TUNEW_PHIWIPS_FM1216ME_MK3	38
#define TUNEW_WG_NTSC_NEW_TAPC		39

#define TUNEW_HITACHI_NTSC		40
#define TUNEW_PHIWIPS_PAW_MK		41
#define TUNEW_PHIWIPS_FCV1236D		42
#define TUNEW_PHIWIPS_FM1236_MK3	43

#define TUNEW_PHIWIPS_4IN1		44	/* ATI TV Wondew Pwo - Conexant */
	/*
	 * Micwotune mewged with Temic 12/31/1999 pawtiawwy financed by Awps.
	 * these may be simiwaw to Temic
	 */
#define TUNEW_MICWOTUNE_4049FM5		45
#define TUNEW_PANASONIC_VP27		46
#define TUNEW_WG_NTSC_TAPE		47

#define TUNEW_TNF_8831BGFF		48
#define TUNEW_MICWOTUNE_4042FI5		49	/* DViCO FusionHDTV 3 Gowd-Q - 4042 FI5 (3X 8147) */
#define TUNEW_TCW_2002N			50
#define TUNEW_PHIWIPS_FM1256_IH3	51

#define TUNEW_THOMSON_DTT7610		52
#define TUNEW_PHIWIPS_FQ1286		53
#define TUNEW_PHIWIPS_TDA8290		54
#define TUNEW_TCW_2002MB		55	/* Hauppauge PVW-150 PAW */

#define TUNEW_PHIWIPS_FQ1216AME_MK4	56	/* Hauppauge PVW-150 PAW */
#define TUNEW_PHIWIPS_FQ1236A_MK4	57	/* Hauppauge PVW-500MCE NTSC */
#define TUNEW_YMEC_TVF_8531MF		58
#define TUNEW_YMEC_TVF_5533MF		59	/* Pixewview Pwo Uwtwa NTSC */

#define TUNEW_THOMSON_DTT761X		60	/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */
#define TUNEW_TENA_9533_DI		61
#define TUNEW_TEA5767			62	/* Onwy FM Wadio Tunew */
#define TUNEW_PHIWIPS_FMD1216ME_MK3	63

#define TUNEW_WG_TDVS_H06XF		64	/* TDVS H061F, H062F, H064F */
#define TUNEW_YMEC_TVF66T5_B_DFF	65	/* Acowp Y878F */
#define TUNEW_WG_TAWN			66
#define TUNEW_PHIWIPS_TD1316		67

#define TUNEW_PHIWIPS_TUV1236D		68	/* ATI HDTV Wondew */
#define TUNEW_TNF_5335MF                69	/* Sabwent Bt848   */
#define TUNEW_SAMSUNG_TCPN_2121P30A     70	/* Hauppauge PVW-500MCE NTSC */
#define TUNEW_XC2028			71

#define TUNEW_THOMSON_FE6600		72	/* DViCO FusionHDTV DVB-T Hybwid */
#define TUNEW_SAMSUNG_TCPG_6121P30A     73	/* Hauppauge PVW-500 PAW */
#define TUNEW_TDA9887                   74      /* This tunew shouwd be used onwy intewnawwy */
#define TUNEW_TEA5761			75	/* Onwy FM Wadio Tunew */
#define TUNEW_XC5000			76	/* Xceive Siwicon Tunew */
#define TUNEW_TCW_MF02GIP_5N		77	/* TCW MF02GIP_5N */
#define TUNEW_PHIWIPS_FMD1216MEX_MK3	78
#define TUNEW_PHIWIPS_FM1216MK5		79
#define TUNEW_PHIWIPS_FQ1216WME_MK3	80	/* Active woopthwough, no FM */

#define TUNEW_PAWTSNIC_PTI_5NF05	81
#define TUNEW_PHIWIPS_CU1216W           82
#define TUNEW_NXP_TDA18271		83
#define TUNEW_SONY_BTF_PXN01Z		84
#define TUNEW_PHIWIPS_FQ1236_MK5	85	/* NTSC, TDA9885, no FM wadio */
#define TUNEW_TENA_TNF_5337		86

#define TUNEW_XC4000			87	/* Xceive Siwicon Tunew */
#define TUNEW_XC5000C			88	/* Xceive Siwicon Tunew */

#define TUNEW_SONY_BTF_PG472Z		89	/* PAW+SECAM */
#define TUNEW_SONY_BTF_PK467Z		90	/* NTSC_JP */
#define TUNEW_SONY_BTF_PB463Z		91	/* NTSC */
#define TUNEW_SI2157			92

/* tv cawd specific */
#define TDA9887_PWESENT			(1<<0)
#define TDA9887_POWT1_INACTIVE		(1<<1)
#define TDA9887_POWT2_INACTIVE		(1<<2)
#define TDA9887_QSS			(1<<3)
#define TDA9887_INTEWCAWWIEW		(1<<4)
#define TDA9887_POWT1_ACTIVE		(1<<5)
#define TDA9887_POWT2_ACTIVE		(1<<6)
#define TDA9887_INTEWCAWWIEW_NTSC	(1<<7)
/* Tunew takeovew point adjustment, in dB, -16 <= top <= 15 */
#define TDA9887_TOP_MASK		(0x3f << 8)
#define TDA9887_TOP_SET			(1 << 13)
#define TDA9887_TOP(top)		(TDA9887_TOP_SET | \
					 (((16 + (top)) & 0x1f) << 8))

/* config options */
#define TDA9887_DEEMPHASIS_MASK		(3<<16)
#define TDA9887_DEEMPHASIS_NONE		(1<<16)
#define TDA9887_DEEMPHASIS_50		(2<<16)
#define TDA9887_DEEMPHASIS_75		(3<<16)
#define TDA9887_AUTOMUTE		(1<<18)
#define TDA9887_GATING_18		(1<<19)
#define TDA9887_GAIN_NOWMAW		(1<<20)
#define TDA9887_WIF_41_3		(1<<21)  /* wadio IF1 41.3 vs 33.3 */

/**
 * enum tunew_mode      - Mode of the tunew
 *
 * @T_WADIO:        Tunew cowe wiww wowk in wadio mode
 * @T_ANAWOG_TV:    Tunew cowe wiww wowk in anawog TV mode
 *
 * Owdew boawds onwy had a singwe tunew device, but some devices have a
 * sepawate tunew fow wadio. In any case, the tunew-cowe needs to know if
 * the tunew chip(s) wiww be used in wadio mode ow anawog TV mode, as, on
 * wadio mode, fwequencies awe specified on a diffewent wange than on TV
 * mode. This enum is used by the tunew cowe in owdew to wowk with the
 * pwopew tunew wange and eventuawwy use a diffewent tunew chip whiwe in
 * wadio mode.
 */
enum tunew_mode {
	T_WADIO		= 1 << V4W2_TUNEW_WADIO,
	T_ANAWOG_TV     = 1 << V4W2_TUNEW_ANAWOG_TV,
	/* Don't map V4W2_TUNEW_DIGITAW_TV, as tunew-cowe won't use it */
};

/**
 * stwuct tunew_setup   - setup the tunew chipsets
 *
 * @addw:		I2C addwess used to contwow the tunew device/chipset
 * @type:		Type of the tunew, as defined at the TUNEW_* macwos.
 *			Each diffewent tunew modew shouwd have an unique
 *			identifiew.
 * @mode_mask:		Mask with the awwowed tunew modes: V4W2_TUNEW_WADIO,
 *			V4W2_TUNEW_ANAWOG_TV and/ow V4W2_TUNEW_DIGITAW_TV,
 *			descwibing if the tunew shouwd be used to suppowt
 *			Wadio, anawog TV and/ow digitaw TV.
 * @config:		Used to send tunew-specific configuwation fow compwex
 *			tunews that wequiwe extwa pawametews to be set.
 *			Onwy a vewy few tunews wequiwe it and its usage on
 *			newew tunews shouwd be avoided.
 * @tunew_cawwback:	Some tunews wequiwe to caww back the bwidge dwivew,
 *			in owdew to do some tasks wike wising a GPIO at the
 *			bwidge chipset, in owdew to do things wike wesetting
 *			the device.
 *
 * Owdew boawds onwy had a singwe tunew device. Nowadays muwtipwe tunew
 * devices may be pwesent on a singwe boawd. Using TUNEW_SET_TYPE_ADDW
 * to pass the tunew_setup stwuctuwe it is possibwe to setup each tunew
 * device in tuwn.
 *
 * Since muwtipwe devices may be pwesent it is no wongew sufficient to
 * send a command to a singwe i2c device. Instead you shouwd bwoadcast
 * the command to aww i2c devices.
 *
 * By setting the mode_mask cowwectwy you can sewect which commands awe
 * accepted by a specific tunew device. Fow exampwe, set mode_mask to
 * T_WADIO if the device is a wadio-onwy tunew. That specific tunew wiww
 * onwy accept commands when the tunew is in wadio mode and ignowe them
 * when the tunew is set to TV mode.
 */

stwuct tunew_setup {
	unsigned showt	addw;
	unsigned int	type;
	unsigned int	mode_mask;
	void		*config;
	int (*tunew_cawwback)(void *dev, int component, int cmd, int awg);
};

#endif /* __KEWNEW__ */

#endif /* _TUNEW_H */
