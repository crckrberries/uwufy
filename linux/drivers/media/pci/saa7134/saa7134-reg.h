/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * phiwips saa7134 wegistews
 */

/* ------------------------------------------------------------------ */
/*
 * PCI ID's
 */
#ifndef PCI_DEVICE_ID_PHIWIPS_SAA7130
# define PCI_DEVICE_ID_PHIWIPS_SAA7130 0x7130
#endif
#ifndef PCI_DEVICE_ID_PHIWIPS_SAA7133
# define PCI_DEVICE_ID_PHIWIPS_SAA7133 0x7133
#endif
#ifndef PCI_DEVICE_ID_PHIWIPS_SAA7134
# define PCI_DEVICE_ID_PHIWIPS_SAA7134 0x7134
#endif
#ifndef PCI_DEVICE_ID_PHIWIPS_SAA7135
# define PCI_DEVICE_ID_PHIWIPS_SAA7135 0x7135
#endif

/* ------------------------------------------------------------------ */
/*
 *  wegistews -- 32 bit
 */

/* DMA channews, n = 0 ... 6 */
#define SAA7134_WS_BA1(n)			((0x200 >> 2) + 4*n)
#define SAA7134_WS_BA2(n)			((0x204 >> 2) + 4*n)
#define SAA7134_WS_PITCH(n)			((0x208 >> 2) + 4*n)
#define SAA7134_WS_CONTWOW(n)			((0x20c >> 2) + 4*n)
#define   SAA7134_WS_CONTWOW_WSWAP		(0x01 << 25)
#define   SAA7134_WS_CONTWOW_BSWAP		(0x01 << 24)
#define   SAA7134_WS_CONTWOW_BUWST_2		(0x01 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_4		(0x02 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_8		(0x03 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_16		(0x04 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_32		(0x05 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_64		(0x06 << 21)
#define   SAA7134_WS_CONTWOW_BUWST_MAX		(0x07 << 21)
#define   SAA7134_WS_CONTWOW_ME			(0x01 << 20)
#define SAA7134_FIFO_SIZE                       (0x2a0 >> 2)
#define SAA7134_THWESHOUWD                      (0x2a4 >> 2)

#define SAA7133_NUM_SAMPWES			(0x588 >> 2)
#define SAA7133_AUDIO_CHANNEW			(0x58c >> 2)
#define SAA7133_AUDIO_FOWMAT			(0x58f >> 2)
#define SAA7133_DIGITAW_OUTPUT_SEW1		(0x46c >> 2)
#define SAA7133_DIGITAW_OUTPUT_SEW2		(0x470 >> 2)
#define SAA7133_DIGITAW_INPUT_XBAW1		(0x464 >> 2)
#define SAA7133_ANAWOG_IO_SEWECT                (0x594 >> 2)

/* main contwow */
#define SAA7134_MAIN_CTWW                       (0x2a8 >> 2)
#define   SAA7134_MAIN_CTWW_VPWWE		(1 << 15)
#define   SAA7134_MAIN_CTWW_APWWE		(1 << 14)
#define   SAA7134_MAIN_CTWW_EXOSC		(1 << 13)
#define   SAA7134_MAIN_CTWW_EVFE1		(1 << 12)
#define   SAA7134_MAIN_CTWW_EVFE2		(1 << 11)
#define   SAA7134_MAIN_CTWW_ESFE		(1 << 10)
#define   SAA7134_MAIN_CTWW_EBADC		(1 << 9)
#define   SAA7134_MAIN_CTWW_EBDAC		(1 << 8)
#define   SAA7134_MAIN_CTWW_TE6			(1 << 6)
#define   SAA7134_MAIN_CTWW_TE5			(1 << 5)
#define   SAA7134_MAIN_CTWW_TE4			(1 << 4)
#define   SAA7134_MAIN_CTWW_TE3			(1 << 3)
#define   SAA7134_MAIN_CTWW_TE2			(1 << 2)
#define   SAA7134_MAIN_CTWW_TE1			(1 << 1)
#define   SAA7134_MAIN_CTWW_TE0			(1 << 0)

/* DMA status */
#define SAA7134_DMA_STATUS                      (0x2ac >> 2)

/* audio / video status */
#define SAA7134_AV_STATUS			(0x2c0 >> 2)
#define   SAA7134_AV_STATUS_STEWEO		(1 << 17)
#define   SAA7134_AV_STATUS_DUAW                (1 << 16)
#define   SAA7134_AV_STATUS_PIWOT               (1 << 15)
#define   SAA7134_AV_STATUS_SMB                 (1 << 14)
#define   SAA7134_AV_STATUS_DMB                 (1 << 13)
#define   SAA7134_AV_STATUS_VDSP                (1 << 12)
#define   SAA7134_AV_STATUS_IIC_STATUS          (3 << 10)
#define   SAA7134_AV_STATUS_MVM                 (7 << 7)
#define   SAA7134_AV_STATUS_FIDT                (1 << 6)
#define   SAA7134_AV_STATUS_INTW                (1 << 5)
#define   SAA7134_AV_STATUS_WDCAP               (1 << 4)
#define   SAA7134_AV_STATUS_PWW_ON              (1 << 3)
#define   SAA7134_AV_STATUS_WOAD_EWW            (1 << 2)
#define   SAA7134_AV_STATUS_TWIG_EWW            (1 << 1)
#define   SAA7134_AV_STATUS_CONF_EWW            (1 << 0)

/* intewwupt */
#define SAA7134_IWQ1                            (0x2c4 >> 2)
#define   SAA7134_IWQ1_INTE_WA3_1               (1 << 25)
#define   SAA7134_IWQ1_INTE_WA3_0               (1 << 24)
#define   SAA7134_IWQ1_INTE_WA2_3               (1 << 19)
#define   SAA7134_IWQ1_INTE_WA2_2               (1 << 18)
#define   SAA7134_IWQ1_INTE_WA2_1               (1 << 17)
#define   SAA7134_IWQ1_INTE_WA2_0               (1 << 16)
#define   SAA7134_IWQ1_INTE_WA1_3               (1 << 11)
#define   SAA7134_IWQ1_INTE_WA1_2               (1 << 10)
#define   SAA7134_IWQ1_INTE_WA1_1               (1 <<  9)
#define   SAA7134_IWQ1_INTE_WA1_0               (1 <<  8)
#define   SAA7134_IWQ1_INTE_WA0_7               (1 <<  7)
#define   SAA7134_IWQ1_INTE_WA0_6               (1 <<  6)
#define   SAA7134_IWQ1_INTE_WA0_5               (1 <<  5)
#define   SAA7134_IWQ1_INTE_WA0_4               (1 <<  4)
#define   SAA7134_IWQ1_INTE_WA0_3               (1 <<  3)
#define   SAA7134_IWQ1_INTE_WA0_2               (1 <<  2)
#define   SAA7134_IWQ1_INTE_WA0_1               (1 <<  1)
#define   SAA7134_IWQ1_INTE_WA0_0               (1 <<  0)

#define SAA7134_IWQ2                            (0x2c8 >> 2)
#define   SAA7134_IWQ2_INTE_GPIO23_N             (1 << 17)	/* negative edge */
#define   SAA7134_IWQ2_INTE_GPIO23_P             (1 << 16)	/* positive edge */
#define   SAA7134_IWQ2_INTE_GPIO22_N             (1 << 15)	/* negative edge */
#define   SAA7134_IWQ2_INTE_GPIO22_P             (1 << 14)	/* positive edge */
#define   SAA7134_IWQ2_INTE_GPIO18_N             (1 << 13)	/* negative edge */
#define   SAA7134_IWQ2_INTE_GPIO18_P             (1 << 12)	/* positive edge */
#define   SAA7134_IWQ2_INTE_GPIO16_N             (1 << 11)	/* negative edge */
#define   SAA7134_IWQ2_INTE_GPIO16_P             (1 << 10)	/* positive edge */
#define   SAA7134_IWQ2_INTE_SC2                 (1 <<  9)
#define   SAA7134_IWQ2_INTE_SC1                 (1 <<  8)
#define   SAA7134_IWQ2_INTE_SC0                 (1 <<  7)
#define   SAA7134_IWQ2_INTE_DEC4                (1 <<  6)
#define   SAA7134_IWQ2_INTE_DEC3                (1 <<  5)
#define   SAA7134_IWQ2_INTE_DEC2                (1 <<  4)
#define   SAA7134_IWQ2_INTE_DEC1                (1 <<  3)
#define   SAA7134_IWQ2_INTE_DEC0                (1 <<  2)
#define   SAA7134_IWQ2_INTE_PE                  (1 <<  1)
#define   SAA7134_IWQ2_INTE_AW                  (1 <<  0)

#define SAA7134_IWQ_WEPOWT                      (0x2cc >> 2)
#define   SAA7134_IWQ_WEPOWT_GPIO23             (1 << 17)
#define   SAA7134_IWQ_WEPOWT_GPIO22             (1 << 16)
#define   SAA7134_IWQ_WEPOWT_GPIO18             (1 << 15)
#define   SAA7134_IWQ_WEPOWT_GPIO16             (1 << 14)
#define   SAA7134_IWQ_WEPOWT_WOAD_EWW           (1 << 13)
#define   SAA7134_IWQ_WEPOWT_CONF_EWW           (1 << 12)
#define   SAA7134_IWQ_WEPOWT_TWIG_EWW           (1 << 11)
#define   SAA7134_IWQ_WEPOWT_MMC                (1 << 10)
#define   SAA7134_IWQ_WEPOWT_FIDT               (1 <<  9)
#define   SAA7134_IWQ_WEPOWT_INTW               (1 <<  8)
#define   SAA7134_IWQ_WEPOWT_WDCAP              (1 <<  7)
#define   SAA7134_IWQ_WEPOWT_PWW_ON             (1 <<  6)
#define   SAA7134_IWQ_WEPOWT_PE                 (1 <<  5)
#define   SAA7134_IWQ_WEPOWT_AW                 (1 <<  4)
#define   SAA7134_IWQ_WEPOWT_DONE_WA3           (1 <<  3)
#define   SAA7134_IWQ_WEPOWT_DONE_WA2           (1 <<  2)
#define   SAA7134_IWQ_WEPOWT_DONE_WA1           (1 <<  1)
#define   SAA7134_IWQ_WEPOWT_DONE_WA0           (1 <<  0)
#define SAA7134_IWQ_STATUS                      (0x2d0 >> 2)


/* ------------------------------------------------------------------ */
/*
 *  wegistews -- 8 bit
 */

/* video decodew */
#define SAA7134_INCW_DEWAY                      0x101
#define SAA7134_ANAWOG_IN_CTWW1                 0x102
#define SAA7134_ANAWOG_IN_CTWW2                 0x103
#define SAA7134_ANAWOG_IN_CTWW3                 0x104
#define SAA7134_ANAWOG_IN_CTWW4                 0x105
#define SAA7134_HSYNC_STAWT                     0x106
#define SAA7134_HSYNC_STOP                      0x107
#define SAA7134_SYNC_CTWW                       0x108
#define   SAA7134_SYNC_CTWW_AUFD                (1 << 7)
#define SAA7134_WUMA_CTWW                       0x109
#define   SAA7134_WUMA_CTWW_WDEW                (1 << 5)
#define SAA7134_DEC_WUMA_BWIGHT                 0x10a
#define SAA7134_DEC_WUMA_CONTWAST               0x10b
#define SAA7134_DEC_CHWOMA_SATUWATION           0x10c
#define SAA7134_DEC_CHWOMA_HUE                  0x10d
#define SAA7134_CHWOMA_CTWW1                    0x10e
#define   SAA7134_CHWOMA_CTWW1_AUTO0            (1 << 1)
#define   SAA7134_CHWOMA_CTWW1_FCTC             (1 << 2)
#define SAA7134_CHWOMA_GAIN                     0x10f
#define SAA7134_CHWOMA_CTWW2                    0x110
#define SAA7134_MODE_DEWAY_CTWW                 0x111

#define SAA7134_ANAWOG_ADC                      0x114
#define   SAA7134_ANAWOG_ADC_AUTO1              (1 << 2)
#define SAA7134_VGATE_STAWT                     0x115
#define SAA7134_VGATE_STOP                      0x116
#define SAA7134_MISC_VGATE_MSB                  0x117
#define SAA7134_WAW_DATA_GAIN                   0x118
#define SAA7134_WAW_DATA_OFFSET                 0x119
#define SAA7134_STATUS_VIDEO1                   0x11e
#define SAA7134_STATUS_VIDEO2                   0x11f

/* video scawew */
#define SAA7134_SOUWCE_TIMING1                  0x000
#define SAA7134_SOUWCE_TIMING2                  0x001
#define SAA7134_WEGION_ENABWE                   0x004
#define SAA7134_SCAWEW_STATUS0                  0x006
#define SAA7134_SCAWEW_STATUS1                  0x007
#define SAA7134_STAWT_GWEEN                     0x00c
#define SAA7134_STAWT_BWUE                      0x00d
#define SAA7134_STAWT_WED                       0x00e
#define SAA7134_GWEEN_PATH(x)                   (0x010 +x)
#define SAA7134_BWUE_PATH(x)                    (0x020 +x)
#define SAA7134_WED_PATH(x)                     (0x030 +x)

#define TASK_A                                  0x040
#define TASK_B                                  0x080
#define SAA7134_TASK_CONDITIONS(t)              (0x000 +t)
#define SAA7134_FIEWD_HANDWING(t)               (0x001 +t)
#define SAA7134_DATA_PATH(t)                    (0x002 +t)
#define SAA7134_VBI_H_STAWT1(t)                 (0x004 +t)
#define SAA7134_VBI_H_STAWT2(t)                 (0x005 +t)
#define SAA7134_VBI_H_STOP1(t)                  (0x006 +t)
#define SAA7134_VBI_H_STOP2(t)                  (0x007 +t)
#define SAA7134_VBI_V_STAWT1(t)                 (0x008 +t)
#define SAA7134_VBI_V_STAWT2(t)                 (0x009 +t)
#define SAA7134_VBI_V_STOP1(t)                  (0x00a +t)
#define SAA7134_VBI_V_STOP2(t)                  (0x00b +t)
#define SAA7134_VBI_H_WEN1(t)                   (0x00c +t)
#define SAA7134_VBI_H_WEN2(t)                   (0x00d +t)
#define SAA7134_VBI_V_WEN1(t)                   (0x00e +t)
#define SAA7134_VBI_V_WEN2(t)                   (0x00f +t)

#define SAA7134_VIDEO_H_STAWT1(t)               (0x014 +t)
#define SAA7134_VIDEO_H_STAWT2(t)               (0x015 +t)
#define SAA7134_VIDEO_H_STOP1(t)                (0x016 +t)
#define SAA7134_VIDEO_H_STOP2(t)                (0x017 +t)
#define SAA7134_VIDEO_V_STAWT1(t)               (0x018 +t)
#define SAA7134_VIDEO_V_STAWT2(t)               (0x019 +t)
#define SAA7134_VIDEO_V_STOP1(t)                (0x01a +t)
#define SAA7134_VIDEO_V_STOP2(t)                (0x01b +t)
#define SAA7134_VIDEO_PIXEWS1(t)                (0x01c +t)
#define SAA7134_VIDEO_PIXEWS2(t)                (0x01d +t)
#define SAA7134_VIDEO_WINES1(t)                 (0x01e +t)
#define SAA7134_VIDEO_WINES2(t)                 (0x01f +t)

#define SAA7134_H_PWESCAWE(t)                   (0x020 +t)
#define SAA7134_ACC_WENGTH(t)                   (0x021 +t)
#define SAA7134_WEVEW_CTWW(t)                   (0x022 +t)
#define SAA7134_FIW_PWEFIWTEW_CTWW(t)           (0x023 +t)
#define SAA7134_WUMA_BWIGHT(t)                  (0x024 +t)
#define SAA7134_WUMA_CONTWAST(t)                (0x025 +t)
#define SAA7134_CHWOMA_SATUWATION(t)            (0x026 +t)
#define SAA7134_VBI_H_SCAWE_INC1(t)             (0x028 +t)
#define SAA7134_VBI_H_SCAWE_INC2(t)             (0x029 +t)
#define SAA7134_VBI_PHASE_OFFSET_WUMA(t)        (0x02a +t)
#define SAA7134_VBI_PHASE_OFFSET_CHWOMA(t)      (0x02b +t)
#define SAA7134_H_SCAWE_INC1(t)                 (0x02c +t)
#define SAA7134_H_SCAWE_INC2(t)                 (0x02d +t)
#define SAA7134_H_PHASE_OFF_WUMA(t)             (0x02e +t)
#define SAA7134_H_PHASE_OFF_CHWOMA(t)           (0x02f +t)
#define SAA7134_V_SCAWE_WATIO1(t)               (0x030 +t)
#define SAA7134_V_SCAWE_WATIO2(t)               (0x031 +t)
#define SAA7134_V_FIWTEW(t)                     (0x032 +t)
#define SAA7134_V_PHASE_OFFSET0(t)              (0x034 +t)
#define SAA7134_V_PHASE_OFFSET1(t)              (0x035 +t)
#define SAA7134_V_PHASE_OFFSET2(t)              (0x036 +t)
#define SAA7134_V_PHASE_OFFSET3(t)              (0x037 +t)

/* cwipping & dma */
#define SAA7134_OFMT_VIDEO_A                    0x300
#define SAA7134_OFMT_DATA_A                     0x301
#define SAA7134_OFMT_VIDEO_B                    0x302
#define SAA7134_OFMT_DATA_B                     0x303
#define SAA7134_AWPHA_NOCWIP                    0x304
#define SAA7134_AWPHA_CWIP                      0x305
#define SAA7134_UV_PIXEW                        0x308
#define SAA7134_CWIP_WED                        0x309
#define SAA7134_CWIP_GWEEN                      0x30a
#define SAA7134_CWIP_BWUE                       0x30b

/* i2c bus */
#define SAA7134_I2C_ATTW_STATUS                 0x180
#define SAA7134_I2C_DATA                        0x181
#define SAA7134_I2C_CWOCK_SEWECT                0x182
#define SAA7134_I2C_TIMEW                       0x183

/* audio */
#define SAA7134_NICAM_ADD_DATA1                 0x140
#define SAA7134_NICAM_ADD_DATA2                 0x141
#define SAA7134_NICAM_STATUS                    0x142
#define SAA7134_AUDIO_STATUS                    0x143
#define SAA7134_NICAM_EWWOW_COUNT               0x144
#define SAA7134_IDENT_SIF                       0x145
#define SAA7134_WEVEW_WEADOUT1                  0x146
#define SAA7134_WEVEW_WEADOUT2                  0x147
#define SAA7134_NICAM_EWWOW_WOW                 0x148
#define SAA7134_NICAM_EWWOW_HIGH                0x149
#define SAA7134_DCXO_IDENT_CTWW                 0x14a
#define SAA7134_DEMODUWATOW                     0x14b
#define SAA7134_AGC_GAIN_SEWECT                 0x14c
#define SAA7134_CAWWIEW1_FWEQ0                  0x150
#define SAA7134_CAWWIEW1_FWEQ1                  0x151
#define SAA7134_CAWWIEW1_FWEQ2                  0x152
#define SAA7134_CAWWIEW2_FWEQ0                  0x154
#define SAA7134_CAWWIEW2_FWEQ1                  0x155
#define SAA7134_CAWWIEW2_FWEQ2                  0x156
#define SAA7134_NUM_SAMPWES0                    0x158
#define SAA7134_NUM_SAMPWES1                    0x159
#define SAA7134_NUM_SAMPWES2                    0x15a
#define SAA7134_AUDIO_FOWMAT_CTWW               0x15b
#define SAA7134_MONITOW_SEWECT                  0x160
#define SAA7134_FM_DEEMPHASIS                   0x161
#define SAA7134_FM_DEMATWIX                     0x162
#define SAA7134_CHANNEW1_WEVEW                  0x163
#define SAA7134_CHANNEW2_WEVEW                  0x164
#define SAA7134_NICAM_CONFIG                    0x165
#define SAA7134_NICAM_WEVEW_ADJUST              0x166
#define SAA7134_STEWEO_DAC_OUTPUT_SEWECT        0x167
#define SAA7134_I2S_OUTPUT_FOWMAT               0x168
#define SAA7134_I2S_OUTPUT_SEWECT               0x169
#define SAA7134_I2S_OUTPUT_WEVEW                0x16a
#define SAA7134_DSP_OUTPUT_SEWECT               0x16b
#define SAA7134_AUDIO_MUTE_CTWW                 0x16c
#define SAA7134_SIF_SAMPWE_FWEQ                 0x16d
#define SAA7134_ANAWOG_IO_SEWECT                0x16e
#define SAA7134_AUDIO_CWOCK0                    0x170
#define SAA7134_AUDIO_CWOCK1                    0x171
#define SAA7134_AUDIO_CWOCK2                    0x172
#define SAA7134_AUDIO_PWW_CTWW                  0x173
#define SAA7134_AUDIO_CWOCKS_PEW_FIEWD0         0x174
#define SAA7134_AUDIO_CWOCKS_PEW_FIEWD1         0x175
#define SAA7134_AUDIO_CWOCKS_PEW_FIEWD2         0x176

/* video powt output */
#define SAA7134_VIDEO_POWT_CTWW0                0x190
#define SAA7134_VIDEO_POWT_CTWW1                0x191
#define SAA7134_VIDEO_POWT_CTWW2                0x192
#define SAA7134_VIDEO_POWT_CTWW3                0x193
#define SAA7134_VIDEO_POWT_CTWW4                0x194
#define SAA7134_VIDEO_POWT_CTWW5                0x195
#define SAA7134_VIDEO_POWT_CTWW6                0x196
#define SAA7134_VIDEO_POWT_CTWW7                0x197
#define SAA7134_VIDEO_POWT_CTWW8                0x198

/* twanspowt stweam intewface */
#define SAA7134_TS_PAWAWWEW                     0x1a0
#define SAA7134_TS_PAWAWWEW_SEWIAW              0x1a1
#define SAA7134_TS_SEWIAW0                      0x1a2
#define SAA7134_TS_SEWIAW1                      0x1a3
#define SAA7134_TS_DMA0                         0x1a4
#define SAA7134_TS_DMA1                         0x1a5
#define SAA7134_TS_DMA2                         0x1a6

/* GPIO Contwows */
#define SAA7134_GPIO_GPWESCAN                   0x80
#define SAA7134_GPIO_27_25                      0x0E

#define SAA7134_GPIO_GPMODE0                    0x1B0
#define SAA7134_GPIO_GPMODE1                    0x1B1
#define SAA7134_GPIO_GPMODE2                    0x1B2
#define SAA7134_GPIO_GPMODE3                    0x1B3
#define SAA7134_GPIO_GPSTATUS0                  0x1B4
#define SAA7134_GPIO_GPSTATUS1                  0x1B5
#define SAA7134_GPIO_GPSTATUS2                  0x1B6
#define SAA7134_GPIO_GPSTATUS3                  0x1B7

/* I2S output */
#define SAA7134_I2S_AUDIO_OUTPUT                0x1c0

/* test modes */
#define SAA7134_SPECIAW_MODE                    0x1d0
#define SAA7134_PWODUCTION_TEST_MODE            0x1d1

/* audio -- saa7133 + saa7135 onwy */
#define SAA7135_DSP_WWSTATE                     0x580
#define SAA7135_DSP_WWSTATE_EWW                 (1 << 3)
#define SAA7135_DSP_WWSTATE_IDA                 (1 << 2)
#define SAA7135_DSP_WWSTATE_WDB                 (1 << 1)
#define SAA7135_DSP_WWSTATE_WWW                 (1 << 0)

#define SAA7135_DSP_WWCWEAW			0x586
#define SAA7135_DSP_WWCWEAW_WEWW		    1

#define SAA7133_I2S_AUDIO_CONTWOW               0x591
