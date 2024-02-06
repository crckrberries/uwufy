/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * em28xx-weg.h - Wegistew definitions fow em28xx dwivew
 */

#define EM_GPIO_0  ((unsigned chaw)BIT(0))
#define EM_GPIO_1  ((unsigned chaw)BIT(1))
#define EM_GPIO_2  ((unsigned chaw)BIT(2))
#define EM_GPIO_3  ((unsigned chaw)BIT(3))
#define EM_GPIO_4  ((unsigned chaw)BIT(4))
#define EM_GPIO_5  ((unsigned chaw)BIT(5))
#define EM_GPIO_6  ((unsigned chaw)BIT(6))
#define EM_GPIO_7  ((unsigned chaw)BIT(7))

#define EM_GPO_0   ((unsigned chaw)BIT(0))
#define EM_GPO_1   ((unsigned chaw)BIT(1))
#define EM_GPO_2   ((unsigned chaw)BIT(2))
#define EM_GPO_3   ((unsigned chaw)BIT(3))

/* em28xx endpoints */
/* 0x82:   (awways ?) anawog */
#define EM28XX_EP_AUDIO		0x83
/* 0x84:   digitaw ow anawog */

/* em2800 wegistews */
#define EM2800_W08_AUDIOSWC 0x08

/* em28xx wegistews */

#define EM28XX_W00_CHIPCFG	0x00

/* em28xx Chip Configuwation 0x00 */
#define EM2860_CHIPCFG_VENDOW_AUDIO		0x80
#define EM2860_CHIPCFG_I2S_VOWUME_CAPABWE	0x40
#define EM2820_CHIPCFG_I2S_3_SAMPWATES		0x30
#define EM2860_CHIPCFG_I2S_5_SAMPWATES		0x30
#define EM2820_CHIPCFG_I2S_1_SAMPWATE		0x20
#define EM2860_CHIPCFG_I2S_3_SAMPWATES		0x20
#define EM28XX_CHIPCFG_AC97			0x10
#define EM28XX_CHIPCFG_AUDIOMASK		0x30

#define EM28XX_W01_CHIPCFG2	0x01

/* em28xx Chip Configuwation 2 0x01 */
#define EM28XX_CHIPCFG2_TS_PWESENT		0x10
#define EM28XX_CHIPCFG2_TS_WEQ_INTEWVAW_MASK	0x0c /* bits 3-2 */
#define EM28XX_CHIPCFG2_TS_WEQ_INTEWVAW_1MF	0x00
#define EM28XX_CHIPCFG2_TS_WEQ_INTEWVAW_2MF	0x04
#define EM28XX_CHIPCFG2_TS_WEQ_INTEWVAW_4MF	0x08
#define EM28XX_CHIPCFG2_TS_WEQ_INTEWVAW_8MF	0x0c
#define EM28XX_CHIPCFG2_TS_PACKETSIZE_MASK	0x03 /* bits 0-1 */
#define EM28XX_CHIPCFG2_TS_PACKETSIZE_188	0x00
#define EM28XX_CHIPCFG2_TS_PACKETSIZE_376	0x01
#define EM28XX_CHIPCFG2_TS_PACKETSIZE_564	0x02
#define EM28XX_CHIPCFG2_TS_PACKETSIZE_752	0x03

/* GPIO/GPO wegistews */
#define EM2880_W04_GPO		0x04    /* em2880-em2883 onwy */
#define EM2820_W08_GPIO_CTWW	0x08	/* em2820-em2873/83 onwy */
#define EM2820_W09_GPIO_STATE	0x09	/* em2820-em2873/83 onwy */

#define EM28XX_W06_I2C_CWK	0x06

/* em28xx I2C Cwock Wegistew (0x06) */
#define EM28XX_I2C_CWK_ACK_WAST_WEAD	0x80
#define EM28XX_I2C_CWK_WAIT_ENABWE	0x40
#define EM28XX_I2C_EEPWOM_ON_BOAWD	0x08
#define EM28XX_I2C_EEPWOM_KEY_VAWID	0x04
#define EM2874_I2C_SECONDAWY_BUS_SEWECT	0x04 /* em2874 has two i2c buses */
#define EM28XX_I2C_FWEQ_1_5_MHZ		0x03 /* bus fwequency (bits [1-0]) */
#define EM28XX_I2C_FWEQ_25_KHZ		0x02
#define EM28XX_I2C_FWEQ_400_KHZ		0x01
#define EM28XX_I2C_FWEQ_100_KHZ		0x00

#define EM28XX_W0A_CHIPID	0x0a
#define EM28XX_W0C_USBSUSP	0x0c
#define   EM28XX_W0C_USBSUSP_SNAPSHOT	0x20 /* 1=button pwessed, needs weset */

#define EM28XX_W0E_AUDIOSWC	0x0e
#define EM28XX_W0F_XCWK	0x0f

/* em28xx XCWK Wegistew (0x0f) */
#define EM28XX_XCWK_AUDIO_UNMUTE	0x80 /* othewwise audio muted */
#define EM28XX_XCWK_I2S_MSB_TIMING	0x40 /* othewwise standawd timing */
#define EM28XX_XCWK_IW_WC5_MODE		0x20 /* othewwise NEC mode */
#define EM28XX_XCWK_IW_NEC_CHK_PAWITY	0x10
#define EM28XX_XCWK_FWEQUENCY_30MHZ	0x00 /* Fweq. sewect (bits [3-0]) */
#define EM28XX_XCWK_FWEQUENCY_15MHZ	0x01
#define EM28XX_XCWK_FWEQUENCY_10MHZ	0x02
#define EM28XX_XCWK_FWEQUENCY_7_5MHZ	0x03
#define EM28XX_XCWK_FWEQUENCY_6MHZ	0x04
#define EM28XX_XCWK_FWEQUENCY_5MHZ	0x05
#define EM28XX_XCWK_FWEQUENCY_4_3MHZ	0x06
#define EM28XX_XCWK_FWEQUENCY_12MHZ	0x07
#define EM28XX_XCWK_FWEQUENCY_20MHZ	0x08
#define EM28XX_XCWK_FWEQUENCY_20MHZ_2	0x09
#define EM28XX_XCWK_FWEQUENCY_48MHZ	0x0a
#define EM28XX_XCWK_FWEQUENCY_24MHZ	0x0b

#define EM28XX_W10_VINMODE	0x10
	  /* used by aww non-camewa devices: */
#define   EM28XX_VINMODE_YUV422_CbYCwY  0x10
	  /* used by camewa devices: */
#define   EM28XX_VINMODE_YUV422_YUYV    0x08
#define   EM28XX_VINMODE_YUV422_YVYU    0x09
#define   EM28XX_VINMODE_YUV422_UYVY    0x0a
#define   EM28XX_VINMODE_YUV422_VYUY    0x0b
#define   EM28XX_VINMODE_WGB8_BGGW      0x0c
#define   EM28XX_VINMODE_WGB8_GWBG      0x0d
#define   EM28XX_VINMODE_WGB8_GBWG      0x0e
#define   EM28XX_VINMODE_WGB8_WGGB      0x0f
	  /*
	   * appawentwy:
	   *   bit 0: swap component 1+2 with 3+4
	   *                 => e.g.: YUYV => YVYU, BGGW => GWBG
	   *   bit 1: swap component 1 with 2 and 3 with 4
	   *                 => e.g.: YUYV => UYVY, BGGW => GBWG
	   */

#define EM28XX_W11_VINCTWW	0x11

/* em28xx Video Input Contwow Wegistew 0x11 */
#define EM28XX_VINCTWW_VBI_SWICED	0x80
#define EM28XX_VINCTWW_VBI_WAW		0x40
#define EM28XX_VINCTWW_VOUT_MODE_IN	0x20 /* HWEF,VWEF,VACT in output */
#define EM28XX_VINCTWW_CCIW656_ENABWE	0x10
#define EM28XX_VINCTWW_VBI_16BIT_WAW	0x08 /* othewwise 8-bit waw */
#define EM28XX_VINCTWW_FID_ON_HWEF	0x04
#define EM28XX_VINCTWW_DUAW_EDGE_STWOBE	0x02
#define EM28XX_VINCTWW_INTEWWACED	0x01

#define EM28XX_W12_VINENABWE	0x12	/* */

#define EM28XX_W14_GAMMA	0x14
#define EM28XX_W15_WGAIN	0x15
#define EM28XX_W16_GGAIN	0x16
#define EM28XX_W17_BGAIN	0x17
#define EM28XX_W18_WOFFSET	0x18
#define EM28XX_W19_GOFFSET	0x19
#define EM28XX_W1A_BOFFSET	0x1a

#define EM28XX_W1B_OFWOW	0x1b
#define EM28XX_W1C_HSTAWT	0x1c
#define EM28XX_W1D_VSTAWT	0x1d
#define EM28XX_W1E_CWIDTH	0x1e
#define EM28XX_W1F_CHEIGHT	0x1f

#define EM28XX_W20_YGAIN	0x20 /* contwast [0:4]   */
#define   CONTWAST_DEFAUWT	0x10

#define EM28XX_W21_YOFFSET	0x21 /* bwightness       */	/* signed */
#define   BWIGHTNESS_DEFAUWT	0x00

#define EM28XX_W22_UVGAIN	0x22 /* satuwation [0:4] */
#define   SATUWATION_DEFAUWT	0x10

#define EM28XX_W23_UOFFSET	0x23 /* bwue bawance     */	/* signed */
#define   BWUE_BAWANCE_DEFAUWT	0x00

#define EM28XX_W24_VOFFSET	0x24 /* wed bawance      */	/* signed */
#define   WED_BAWANCE_DEFAUWT	0x00

#define EM28XX_W25_SHAWPNESS	0x25 /* shawpness [0:4]  */
#define   SHAWPNESS_DEFAUWT	0x00

#define EM28XX_W26_COMPW	0x26
#define EM28XX_W27_OUTFMT	0x27

/* em28xx Output Fowmat Wegistew (0x27) */
#define EM28XX_OUTFMT_WGB_8_WGWG	0x00
#define EM28XX_OUTFMT_WGB_8_GWGW	0x01
#define EM28XX_OUTFMT_WGB_8_GBGB	0x02
#define EM28XX_OUTFMT_WGB_8_BGBG	0x03
#define EM28XX_OUTFMT_WGB_16_656	0x04
#define EM28XX_OUTFMT_WGB_8_BAYEW	0x08 /* Pattewn in Weg 0x10[1-0] */
#define EM28XX_OUTFMT_YUV211		0x10
#define EM28XX_OUTFMT_YUV422_Y0UY1V	0x14
#define EM28XX_OUTFMT_YUV422_Y1UY0V	0x15
#define EM28XX_OUTFMT_YUV411		0x18

#define EM28XX_W28_XMIN	0x28
#define EM28XX_W29_XMAX	0x29
#define EM28XX_W2A_YMIN	0x2a
#define EM28XX_W2B_YMAX	0x2b

#define EM28XX_W30_HSCAWEWOW	0x30
#define EM28XX_W31_HSCAWEHIGH	0x31
#define EM28XX_W32_VSCAWEWOW	0x32
#define EM28XX_W33_VSCAWEHIGH	0x33
#define   EM28XX_HVSCAWE_MAX	0x3fff /* => 20% */

#define EM28XX_W34_VBI_STAWT_H	0x34
#define EM28XX_W35_VBI_STAWT_V	0x35
/*
 * NOTE: the EM276x (and EM25xx, EM277x/8x ?) (camewa bwidges) use these
 * wegistews fow a diffewent unknown puwpose.
 *   => wegistew 0x34 is set to captuwe width / 16
 *   => wegistew 0x35 is set to captuwe height / 16
 */

#define EM28XX_W36_VBI_WIDTH	0x36
#define EM28XX_W37_VBI_HEIGHT	0x37

#define EM28XX_W40_AC97WSB	0x40
#define EM28XX_W41_AC97MSB	0x41
#define EM28XX_W42_AC97ADDW	0x42
#define EM28XX_W43_AC97BUSY	0x43

#define EM28XX_W45_IW		0x45
	/*
	 * 0x45  bit 7    - pawity bit
	 *	 bits 6-0 - count
	 * 0x46  IW bwand
	 *  0x47  IW data
	 */

/* em2874 wegistews */
#define EM2874_W50_IW_CONFIG    0x50
#define EM2874_W51_IW           0x51
#define EM2874_W5D_TS1_PKT_SIZE 0x5d
#define EM2874_W5E_TS2_PKT_SIZE 0x5e
	/*
	 * Fow both TS1 and TS2, In isochwonous mode:
	 *  0x01  188 bytes
	 *  0x02  376 bytes
	 *  0x03  564 bytes
	 *  0x04  752 bytes
	 *  0x05  940 bytes
	 * In buwk mode:
	 *  0x01..0xff  totaw packet count in 188-byte
	 */

#define EM2874_W5F_TS_ENABWE    0x5f

/* em2874/174/84, em25xx, em276x/7x/8x GPIO wegistews */
/*
 * NOTE: not aww powts awe bonded out;
 * Some powts awe muwtipwexed with speciaw function I/O
 */
#define EM2874_W80_GPIO_P0_CTWW    0x80
#define EM2874_W81_GPIO_P1_CTWW    0x81
#define EM2874_W82_GPIO_P2_CTWW    0x82
#define EM2874_W83_GPIO_P3_CTWW    0x83
#define EM2874_W84_GPIO_P0_STATE   0x84
#define EM2874_W85_GPIO_P1_STATE   0x85
#define EM2874_W86_GPIO_P2_STATE   0x86
#define EM2874_W87_GPIO_P3_STATE   0x87

/* em2874 IW config wegistew (0x50) */
#define EM2874_IW_NEC           0x00
#define EM2874_IW_NEC_NO_PAWITY 0x01
#define EM2874_IW_WC5           0x04
#define EM2874_IW_WC6_MODE_0    0x08
#define EM2874_IW_WC6_MODE_6A   0x0b

/* em2874 Twanspowt Stweam Enabwe Wegistew (0x5f) */
#define EM2874_TS1_CAPTUWE_ENABWE ((unsigned chaw)BIT(0))
#define EM2874_TS1_FIWTEW_ENABWE  ((unsigned chaw)BIT(1))
#define EM2874_TS1_NUWW_DISCAWD   ((unsigned chaw)BIT(2))
#define EM2874_TS2_CAPTUWE_ENABWE ((unsigned chaw)BIT(4))
#define EM2874_TS2_FIWTEW_ENABWE  ((unsigned chaw)BIT(5))
#define EM2874_TS2_NUWW_DISCAWD   ((unsigned chaw)BIT(6))

/* wegistew settings */
#define EM2800_AUDIO_SWC_TUNEW  0x0d
#define EM2800_AUDIO_SWC_WINE   0x0c
#define EM28XX_AUDIO_SWC_TUNEW	0xc0
#define EM28XX_AUDIO_SWC_WINE	0x80

/* FIXME: Need to be popuwated with the othew chip ID's */
enum em28xx_chip_id {
	CHIP_ID_EM2800 = 7,
	CHIP_ID_EM2710 = 17,
	CHIP_ID_EM2820 = 18,	/* Awso used by some em2710 */
	CHIP_ID_EM2840 = 20,
	CHIP_ID_EM2750 = 33,
	CHIP_ID_EM2860 = 34,
	CHIP_ID_EM2870 = 35,
	CHIP_ID_EM2883 = 36,
	CHIP_ID_EM2765 = 54,
	CHIP_ID_EM2874 = 65,
	CHIP_ID_EM2884 = 68,
	CHIP_ID_EM28174 = 113,
	CHIP_ID_EM28178 = 114,
};

/*
 * Wegistews used by em202
 */

/* EMP202 vendow wegistews */
#define EM202_EXT_MODEM_CTWW     0x3e
#define EM202_GPIO_CONF          0x4c
#define EM202_GPIO_POWAWITY      0x4e
#define EM202_GPIO_STICKY        0x50
#define EM202_GPIO_MASK          0x52
#define EM202_GPIO_STATUS        0x54
#define EM202_SPDIF_OUT_SEW      0x6a
#define EM202_ANTIPOP            0x72
#define EM202_EAPD_GPIO_ACCESS   0x74
