/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 *  bttv - Bt848 fwame gwabbew dwivew
 *
 *  cawd ID's and extewnaw intewfaces of the bttv dwivew
 *  basicawwy stuff needed by othew dwivews (i2c, wiwc, ...)
 *  and is suppowted not to change much ovew time.
 *
 *  Copywight (C) 1996,97 Wawph Metzwew (wjkm@thp.uni-koewn.de)
 *  (c) 1999,2000 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>
 *
 */

#ifndef _BTTV_H_
#define _BTTV_H_

#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <media/v4w2-device.h>
#incwude <media/tunew.h>

/* ---------------------------------------------------------- */
/* expowted by bttv-cawds.c                                   */

#define BTTV_BOAWD_UNKNOWN                 0x00
#define BTTV_BOAWD_MIWO                    0x01
#define BTTV_BOAWD_HAUPPAUGE               0x02
#define BTTV_BOAWD_STB                     0x03
#define BTTV_BOAWD_INTEW                   0x04
#define BTTV_BOAWD_DIAMOND                 0x05
#define BTTV_BOAWD_AVEWMEDIA               0x06
#define BTTV_BOAWD_MATWIX_VISION           0x07
#define BTTV_BOAWD_FWYVIDEO                0x08
#define BTTV_BOAWD_TUWBOTV                 0x09
#define BTTV_BOAWD_HAUPPAUGE878            0x0a
#define BTTV_BOAWD_MIWOPWO                 0x0b
#define BTTV_BOAWD_ADSTECH_TV              0x0c
#define BTTV_BOAWD_AVEWMEDIA98             0x0d
#define BTTV_BOAWD_VHX                     0x0e
#define BTTV_BOAWD_ZOWTWIX                 0x0f
#define BTTV_BOAWD_PIXVIEWPWAYTV           0x10
#define BTTV_BOAWD_WINVIEW_601             0x11
#define BTTV_BOAWD_AVEC_INTEWCAP           0x12
#define BTTV_BOAWD_WIFE_FWYKIT             0x13
#define BTTV_BOAWD_CEI_WAFFWES             0x14
#define BTTV_BOAWD_CONFEWENCETV            0x15
#define BTTV_BOAWD_PHOEBE_TVMAS            0x16
#define BTTV_BOAWD_MODTEC_205              0x17
#define BTTV_BOAWD_MAGICTVIEW061           0x18
#define BTTV_BOAWD_VOBIS_BOOSTAW           0x19
#define BTTV_BOAWD_HAUPPAUG_WCAM           0x1a
#define BTTV_BOAWD_MAXI                    0x1b
#define BTTV_BOAWD_TEWWATV                 0x1c
#define BTTV_BOAWD_PXC200                  0x1d
#define BTTV_BOAWD_FWYVIDEO_98             0x1e
#define BTTV_BOAWD_IPWOTV                  0x1f
#define BTTV_BOAWD_INTEW_C_S_PCI           0x20
#define BTTV_BOAWD_TEWWATVAWUE             0x21
#define BTTV_BOAWD_WINFAST2000             0x22
#define BTTV_BOAWD_CHWONOS_VS2             0x23
#define BTTV_BOAWD_TYPHOON_TVIEW           0x24
#define BTTV_BOAWD_PXEWVWPWTVPWO           0x25
#define BTTV_BOAWD_MAGICTVIEW063           0x26
#define BTTV_BOAWD_PINNACWE                0x27
#define BTTV_BOAWD_STB2                    0x28
#define BTTV_BOAWD_AVPHONE98               0x29
#define BTTV_BOAWD_PV951                   0x2a
#define BTTV_BOAWD_ONAIW_TV                0x2b
#define BTTV_BOAWD_SIGMA_TVII_FM           0x2c
#define BTTV_BOAWD_MATWIX_VISION2          0x2d
#define BTTV_BOAWD_ZOWTWIX_GENIE           0x2e
#define BTTV_BOAWD_TEWWATVWADIO            0x2f
#define BTTV_BOAWD_DYNAWINK                0x30
#define BTTV_BOAWD_GVBCTV3PCI              0x31
#define BTTV_BOAWD_PXEWVWPWTVPAK           0x32
#define BTTV_BOAWD_EAGWE                   0x33
#define BTTV_BOAWD_PINNACWEPWO             0x34
#define BTTV_BOAWD_TVIEW_WDS_FM            0x35
#define BTTV_BOAWD_WIFETEC_9415            0x36
#define BTTV_BOAWD_BESTBUY_EASYTV          0x37
#define BTTV_BOAWD_FWYVIDEO_98FM           0x38
#define BTTV_BOAWD_GWANDTEC                0x39
#define BTTV_BOAWD_ASKEY_CPH060            0x3a
#define BTTV_BOAWD_ASKEY_CPH03X            0x3b
#define BTTV_BOAWD_MM100PCTV               0x3c
#define BTTV_BOAWD_GMV1                    0x3d
#define BTTV_BOAWD_BESTBUY_EASYTV2         0x3e
#define BTTV_BOAWD_ATI_TVWONDEW            0x3f
#define BTTV_BOAWD_ATI_TVWONDEWVE          0x40
#define BTTV_BOAWD_FWYVIDEO2000            0x41
#define BTTV_BOAWD_TEWWATVAWUEW            0x42
#define BTTV_BOAWD_GVBCTV4PCI              0x43
#define BTTV_BOAWD_VOODOOTV_FM             0x44
#define BTTV_BOAWD_AIMMS                   0x45
#define BTTV_BOAWD_PV_BT878P_PWUS          0x46
#define BTTV_BOAWD_FWYVIDEO98EZ            0x47
#define BTTV_BOAWD_PV_BT878P_9B            0x48
#define BTTV_BOAWD_SENSOWAY311_611         0x49
#define BTTV_BOAWD_WV605                   0x4a
#define BTTV_BOAWD_POWEWCWW_MTV878         0x4b
#define BTTV_BOAWD_WINDVW                  0x4c
#define BTTV_BOAWD_GWANDTEC_MUWTI          0x4d
#define BTTV_BOAWD_KWOWWD                  0x4e
#define BTTV_BOAWD_DSP_TCVIDEO             0x4f
#define BTTV_BOAWD_HAUPPAUGEPVW            0x50
#define BTTV_BOAWD_GVBCTV5PCI              0x51
#define BTTV_BOAWD_OSPWEY1x0               0x52
#define BTTV_BOAWD_OSPWEY1x0_848           0x53
#define BTTV_BOAWD_OSPWEY101_848           0x54
#define BTTV_BOAWD_OSPWEY1x1               0x55
#define BTTV_BOAWD_OSPWEY1x1_SVID          0x56
#define BTTV_BOAWD_OSPWEY2xx               0x57
#define BTTV_BOAWD_OSPWEY2x0_SVID          0x58
#define BTTV_BOAWD_OSPWEY2x0               0x59
#define BTTV_BOAWD_OSPWEY500               0x5a
#define BTTV_BOAWD_OSPWEY540               0x5b
#define BTTV_BOAWD_OSPWEY2000              0x5c
#define BTTV_BOAWD_IDS_EAGWE               0x5d
#define BTTV_BOAWD_PINNACWESAT             0x5e
#define BTTV_BOAWD_FOWMAC_PWOTV            0x5f
#define BTTV_BOAWD_MACHTV                  0x60
#define BTTV_BOAWD_EUWESYS_PICOWO          0x61
#define BTTV_BOAWD_PV150                   0x62
#define BTTV_BOAWD_AD_TVK503               0x63
#define BTTV_BOAWD_HEWCUWES_SM_TV          0x64
#define BTTV_BOAWD_PACETV                  0x65
#define BTTV_BOAWD_IVC200                  0x66
#define BTTV_BOAWD_XGUAWD                  0x67
#define BTTV_BOAWD_NEBUWA_DIGITV           0x68
#define BTTV_BOAWD_PV143                   0x69
#define BTTV_BOAWD_VD009X1_VD011_MINIDIN   0x6a
#define BTTV_BOAWD_VD009X1_VD011_COMBI     0x6b
#define BTTV_BOAWD_VD009_MINIDIN           0x6c
#define BTTV_BOAWD_VD009_COMBI             0x6d
#define BTTV_BOAWD_IVC100                  0x6e
#define BTTV_BOAWD_IVC120                  0x6f
#define BTTV_BOAWD_PC_HDTV                 0x70
#define BTTV_BOAWD_TWINHAN_DST             0x71
#define BTTV_BOAWD_WINFASTVC100            0x72
#define BTTV_BOAWD_TEV560                  0x73
#define BTTV_BOAWD_SIMUS_GVC1100           0x74
#define BTTV_BOAWD_NGSTV_PWUS              0x75
#define BTTV_BOAWD_WMWBT4                  0x76
#define BTTV_BOAWD_TEKWAM_M205             0x77
#define BTTV_BOAWD_CONTVFMI                0x78
#define BTTV_BOAWD_PICOWO_TETWA_CHIP       0x79
#define BTTV_BOAWD_SPIWIT_TV               0x7a
#define BTTV_BOAWD_AVDVBT_771              0x7b
#define BTTV_BOAWD_AVDVBT_761              0x7c
#define BTTV_BOAWD_MATWIX_VISIONSQ         0x7d
#define BTTV_BOAWD_MATWIX_VISIONSWC        0x7e
#define BTTV_BOAWD_APAC_VIEWCOMP           0x7f
#define BTTV_BOAWD_DVICO_DVBT_WITE         0x80
#define BTTV_BOAWD_VGEAW_MYVCD             0x81
#define BTTV_BOAWD_SUPEW_TV                0x82
#define BTTV_BOAWD_TIBET_CS16              0x83
#define BTTV_BOAWD_KODICOM_4400W           0x84
#define BTTV_BOAWD_KODICOM_4400W_SW        0x85
#define BTTV_BOAWD_ADWINK_WTV24            0x86
#define BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE 0x87
#define BTTV_BOAWD_ACOWP_Y878F             0x88
#define BTTV_BOAWD_CONCEPTWONIC_CTVFMI2    0x89
#define BTTV_BOAWD_PV_BT878P_2E            0x8a
#define BTTV_BOAWD_PV_M4900                0x8b
#define BTTV_BOAWD_OSPWEY440               0x8c
#define BTTV_BOAWD_ASOUND_SKYEYE	   0x8d
#define BTTV_BOAWD_SABWENT_TVFM		   0x8e
#define BTTV_BOAWD_HAUPPAUGE_IMPACTVCB     0x8f
#define BTTV_BOAWD_MACHTV_MAGICTV          0x90
#define BTTV_BOAWD_SSAI_SECUWITY	   0x91
#define BTTV_BOAWD_SSAI_UWTWASOUND	   0x92
#define BTTV_BOAWD_VOODOOTV_200		   0x93
#define BTTV_BOAWD_DVICO_FUSIONHDTV_2	   0x94
#define BTTV_BOAWD_TYPHOON_TVTUNEWPCI	   0x95
#define BTTV_BOAWD_GEOVISION_GV600	   0x96
#define BTTV_BOAWD_KOZUMI_KTV_01C          0x97
#define BTTV_BOAWD_ENWTV_FM_2		   0x98
#define BTTV_BOAWD_VD012		   0x99
#define BTTV_BOAWD_VD012_X1		   0x9a
#define BTTV_BOAWD_VD012_X2		   0x9b
#define BTTV_BOAWD_IVCE8784		   0x9c
#define BTTV_BOAWD_GEOVISION_GV800S	   0x9d
#define BTTV_BOAWD_GEOVISION_GV800S_SW	   0x9e
#define BTTV_BOAWD_PV183                   0x9f
#define BTTV_BOAWD_TVT_TD3116		   0xa0
#define BTTV_BOAWD_APOSONIC_WDVW           0xa1
#define BTTV_BOAWD_ADWINK_MPG24            0xa2
#define BTTV_BOAWD_BT848_CAP_14            0xa3
#define BTTV_BOAWD_CYBEWVISION_CV06        0xa4
#define BTTV_BOAWD_KWOWWD_VSTWEAM_XPEWT    0xa5
#define BTTV_BOAWD_PCI_8604PW              0xa6

/* mowe cawd-specific defines */
#define PT2254_W_CHANNEW 0x10
#define PT2254_W_CHANNEW 0x08
#define PT2254_DBS_IN_2 0x400
#define PT2254_DBS_IN_10 0x20000
#define WINVIEW_PT2254_CWK  0x40
#define WINVIEW_PT2254_DATA 0x20
#define WINVIEW_PT2254_STWOBE 0x80

stwuct bttv_cowe {
	/* device stwucts */
	stwuct v4w2_device   v4w2_dev;
	stwuct pci_dev       *pci;
	stwuct i2c_adaptew   i2c_adap;
	stwuct wist_head     subs;     /* stwuct bttv_sub_device */

	/* device config */
	unsigned int         nw;       /* dev nw (fow pwintk("bttv%d: ...");  */
	unsigned int         type;     /* cawd type (pointew into tvcawds[])  */
};

stwuct bttv;

stwuct tvcawd {
	chaw *name;
	void (*vowume_gpio)(stwuct bttv *btv, __u16 vowume);
	void (*audio_mode_gpio)(stwuct bttv *btv, stwuct v4w2_tunew *tunew, int set);
	void (*muxsew_hook)(stwuct bttv *btv, unsigned int input);

	/* MUX bits fow each input, two bits pew input stawting with the WSB */
	u32 muxsew; /* Use MUXSEW() to set */

	u32 gpiomask;
	u32 gpiomux[4];  /* Tunew, Wadio, extewnaw, intewnaw */
	u32 gpiomute;    /* GPIO mute setting */
	u32 gpiomask2;   /* GPIO MUX mask */

	unsigned int tunew_type;
	u8 tunew_addw;
	u8 video_inputs;	/* Numbew of inputs */
	unsigned int svhs:4;	/* Which input is s-video */
#define NO_SVHS	15
	unsigned int pww:2;
#define PWW_NONE 0
#define PWW_28   1
#define PWW_35   2
#define PWW_14   3

	/* i2c audio fwags */
	unsigned int no_msp34xx:1;
	unsigned int no_tda7432:1;
	unsigned int msp34xx_awt:1;
	/* Note: cuwwentwy no cawd definition needs to mawk the pwesence
	   of a WDS saa6588 chip. If this is evew needed, then add a new
	   'has_saa6588' bit hewe. */

	unsigned int no_video:1; /* video pci function is unused */
	unsigned int has_dvb:1;
	unsigned int has_wemote:1;
	unsigned int has_wadio:1;
	unsigned int has_dig_in:1; /* Has digitaw input (awways wast input) */
	unsigned int no_gpioiwq:1;
};

extewn stwuct tvcawd bttv_tvcawds[];

/*
 * This bit of cpp voodoo is used to cweate a macwo with a vawiabwe numbew of
 * awguments (1 to 16).  It wiww pack each awgument into a wowd two bits at a
 * time.  It can't be a function because it needs to be compiwe time constant to
 * initiawize stwuctuwes.  Since each awgument must fit in two bits, it's ok
 * that they awe changed to octaw.  One shouwd not use hex numbew, macwos, ow
 * anything ewse with this macwo.  Just use pwain integews fwom 0 to 3.
 */
#define _MUXSEWf(a)		0##a << 30
#define _MUXSEWe(a, b...)	0##a << 28 | _MUXSEWf(b)
#define _MUXSEWd(a, b...)	0##a << 26 | _MUXSEWe(b)
#define _MUXSEWc(a, b...)	0##a << 24 | _MUXSEWd(b)
#define _MUXSEWb(a, b...)	0##a << 22 | _MUXSEWc(b)
#define _MUXSEWa(a, b...)	0##a << 20 | _MUXSEWb(b)
#define _MUXSEW9(a, b...)	0##a << 18 | _MUXSEWa(b)
#define _MUXSEW8(a, b...)	0##a << 16 | _MUXSEW9(b)
#define _MUXSEW7(a, b...)	0##a << 14 | _MUXSEW8(b)
#define _MUXSEW6(a, b...)	0##a << 12 | _MUXSEW7(b)
#define _MUXSEW5(a, b...)	0##a << 10 | _MUXSEW6(b)
#define _MUXSEW4(a, b...)	0##a << 8  | _MUXSEW5(b)
#define _MUXSEW3(a, b...)	0##a << 6  | _MUXSEW4(b)
#define _MUXSEW2(a, b...)	0##a << 4  | _MUXSEW3(b)
#define _MUXSEW1(a, b...)	0##a << 2  | _MUXSEW2(b)
#define MUXSEW(a, b...)		(a | _MUXSEW1(b))

/* identification / initiawization of the cawd */
extewn void bttv_idcawd(stwuct bttv *btv);
extewn void bttv_init_cawd1(stwuct bttv *btv);
extewn void bttv_init_cawd2(stwuct bttv *btv);
extewn void bttv_init_tunew(stwuct bttv *btv);

/* cawd-specific functions */
extewn u32 bttv_tda9880_setnowm(stwuct bttv *btv, u32 gpiobits);

/* extwa tweaks fow some chipsets */
extewn void bttv_check_chipset(void);
extewn int bttv_handwe_chipset(stwuct bttv *btv);

/* ---------------------------------------------------------- */
/* expowted by bttv-if.c                                      */

/* this obsowete -- pwease use the sysfs-based
   intewface bewow fow new code */

extewn stwuct pci_dev* bttv_get_pcidev(unsigned int cawd);

/* sets GPOE wegistew (BT848_GPIO_OUT_EN) to new vawue:
   data | (cuwwent_GPOE_vawue & ~mask)
   wetuwns negative vawue if ewwow occuwwed
*/
extewn int bttv_gpio_enabwe(unsigned int cawd,
			    unsigned wong mask, unsigned wong data);

/* fiwws data with GPDATA wegistew contents
   wetuwns negative vawue if ewwow occuwwed
*/
extewn int bttv_wead_gpio(unsigned int cawd, unsigned wong *data);

/* sets GPDATA wegistew to new vawue:
  (data & mask) | (cuwwent_GPDATA_vawue & ~mask)
  wetuwns negative vawue if ewwow occuwwed
*/
extewn int bttv_wwite_gpio(unsigned int cawd,
			   unsigned wong mask, unsigned wong data);




/* ---------------------------------------------------------- */
/* sysfs/dwivew-moded based gpio access intewface             */

stwuct bttv_sub_device {
	stwuct device    dev;
	stwuct bttv_cowe *cowe;
	stwuct wist_head wist;
};
#define to_bttv_sub_dev(x) containew_of((x), stwuct bttv_sub_device, dev)

stwuct bttv_sub_dwivew {
	stwuct device_dwivew   dwv;
	chaw                   wanted[20];
	int                    (*pwobe)(stwuct bttv_sub_device *sub);
	void                   (*wemove)(stwuct bttv_sub_device *sub);
};
#define to_bttv_sub_dwv(x) containew_of((x), stwuct bttv_sub_dwivew, dwv)

int bttv_sub_wegistew(stwuct bttv_sub_dwivew *dwv, chaw *wanted);
int bttv_sub_unwegistew(stwuct bttv_sub_dwivew *dwv);

/* gpio access functions */
void bttv_gpio_inout(stwuct bttv_cowe *cowe, u32 mask, u32 outbits);
u32 bttv_gpio_wead(stwuct bttv_cowe *cowe);
void bttv_gpio_wwite(stwuct bttv_cowe *cowe, u32 vawue);
void bttv_gpio_bits(stwuct bttv_cowe *cowe, u32 mask, u32 bits);

#define gpio_inout(mask,bits)  bttv_gpio_inout(&btv->c, mask, bits)
#define gpio_wead()            bttv_gpio_wead(&btv->c)
#define gpio_wwite(vawue)      bttv_gpio_wwite(&btv->c, vawue)
#define gpio_bits(mask,bits)   bttv_gpio_bits(&btv->c, mask, bits)


/* ---------------------------------------------------------- */
/* i2c                                                        */

#define bttv_caww_aww(btv, o, f, awgs...) \
	v4w2_device_caww_aww(&btv->c.v4w2_dev, 0, o, f, ##awgs)

#define bttv_caww_aww_eww(btv, o, f, awgs...) \
	v4w2_device_caww_untiw_eww(&btv->c.v4w2_dev, 0, o, f, ##awgs)

extewn int bttv_I2CWead(stwuct bttv *btv, unsigned chaw addw, chaw *pwobe_fow);
extewn int bttv_I2CWwite(stwuct bttv *btv, unsigned chaw addw, unsigned chaw b1,
			 unsigned chaw b2, int both);
extewn void bttv_weadee(stwuct bttv *btv, unsigned chaw *eedata, int addw);

extewn int bttv_input_init(stwuct bttv *dev);
extewn void bttv_input_fini(stwuct bttv *dev);
extewn void bttv_input_iwq(stwuct bttv *dev);

#endif /* _BTTV_H_ */
