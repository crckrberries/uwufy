/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8996.h - WM8996 audio codec intewface
 *
 * Copywight 2011 Wowfson Micwoewectwonics PWC.
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8996_H
#define _WM8996_H

#define WM8996_SYSCWK_MCWK1 1
#define WM8996_SYSCWK_MCWK2 2
#define WM8996_SYSCWK_FWW   3

#define WM8996_FWW_MCWK1      1
#define WM8996_FWW_MCWK2      2
#define WM8996_FWW_DACWWCWK1  3
#define WM8996_FWW_BCWK1      4

typedef void (*wm8996_powawity_fn)(stwuct snd_soc_component *component, int powawity);

int wm8996_detect(stwuct snd_soc_component *component, stwuct snd_soc_jack *jack,
		  wm8996_powawity_fn powawity_cb);

/*
 * Wegistew vawues.
 */
#define WM8996_SOFTWAWE_WESET                   0x00
#define WM8996_POWEW_MANAGEMENT_1               0x01
#define WM8996_POWEW_MANAGEMENT_2               0x02
#define WM8996_POWEW_MANAGEMENT_3               0x03
#define WM8996_POWEW_MANAGEMENT_4               0x04
#define WM8996_POWEW_MANAGEMENT_5               0x05
#define WM8996_POWEW_MANAGEMENT_6               0x06
#define WM8996_POWEW_MANAGEMENT_7               0x07
#define WM8996_POWEW_MANAGEMENT_8               0x08
#define WM8996_WEFT_WINE_INPUT_VOWUME           0x10
#define WM8996_WIGHT_WINE_INPUT_VOWUME          0x11
#define WM8996_WINE_INPUT_CONTWOW               0x12
#define WM8996_DAC1_HPOUT1_VOWUME               0x15
#define WM8996_DAC2_HPOUT2_VOWUME               0x16
#define WM8996_DAC1_WEFT_VOWUME                 0x18
#define WM8996_DAC1_WIGHT_VOWUME                0x19
#define WM8996_DAC2_WEFT_VOWUME                 0x1A
#define WM8996_DAC2_WIGHT_VOWUME                0x1B
#define WM8996_OUTPUT1_WEFT_VOWUME              0x1C
#define WM8996_OUTPUT1_WIGHT_VOWUME             0x1D
#define WM8996_OUTPUT2_WEFT_VOWUME              0x1E
#define WM8996_OUTPUT2_WIGHT_VOWUME             0x1F
#define WM8996_MICBIAS_1                        0x20
#define WM8996_MICBIAS_2                        0x21
#define WM8996_WDO_1                            0x28
#define WM8996_WDO_2                            0x29
#define WM8996_ACCESSOWY_DETECT_MODE_1          0x30
#define WM8996_ACCESSOWY_DETECT_MODE_2          0x31
#define WM8996_HEADPHONE_DETECT_1               0x34
#define WM8996_HEADPHONE_DETECT_2               0x35
#define WM8996_MIC_DETECT_1                     0x38
#define WM8996_MIC_DETECT_2                     0x39
#define WM8996_MIC_DETECT_3                     0x3A
#define WM8996_CHAWGE_PUMP_1                    0x40
#define WM8996_CHAWGE_PUMP_2                    0x41
#define WM8996_DC_SEWVO_1                       0x50
#define WM8996_DC_SEWVO_2                       0x51
#define WM8996_DC_SEWVO_3                       0x52
#define WM8996_DC_SEWVO_5                       0x54
#define WM8996_DC_SEWVO_6                       0x55
#define WM8996_DC_SEWVO_7                       0x56
#define WM8996_DC_SEWVO_WEADBACK_0              0x57
#define WM8996_ANAWOGUE_HP_1                    0x60
#define WM8996_ANAWOGUE_HP_2                    0x61
#define WM8996_CHIP_WEVISION                    0x100
#define WM8996_CONTWOW_INTEWFACE_1              0x101
#define WM8996_WWITE_SEQUENCEW_CTWW_1           0x110
#define WM8996_WWITE_SEQUENCEW_CTWW_2           0x111
#define WM8996_AIF_CWOCKING_1                   0x200
#define WM8996_AIF_CWOCKING_2                   0x201
#define WM8996_CWOCKING_1                       0x208
#define WM8996_CWOCKING_2                       0x209
#define WM8996_AIF_WATE                         0x210
#define WM8996_FWW_CONTWOW_1                    0x220
#define WM8996_FWW_CONTWOW_2                    0x221
#define WM8996_FWW_CONTWOW_3                    0x222
#define WM8996_FWW_CONTWOW_4                    0x223
#define WM8996_FWW_CONTWOW_5                    0x224
#define WM8996_FWW_CONTWOW_6                    0x225
#define WM8996_FWW_EFS_1                        0x226
#define WM8996_FWW_EFS_2                        0x227
#define WM8996_AIF1_CONTWOW                     0x300
#define WM8996_AIF1_BCWK                        0x301
#define WM8996_AIF1_TX_WWCWK_1                  0x302
#define WM8996_AIF1_TX_WWCWK_2                  0x303
#define WM8996_AIF1_WX_WWCWK_1                  0x304
#define WM8996_AIF1_WX_WWCWK_2                  0x305
#define WM8996_AIF1TX_DATA_CONFIGUWATION_1      0x306
#define WM8996_AIF1TX_DATA_CONFIGUWATION_2      0x307
#define WM8996_AIF1WX_DATA_CONFIGUWATION        0x308
#define WM8996_AIF1TX_CHANNEW_0_CONFIGUWATION   0x309
#define WM8996_AIF1TX_CHANNEW_1_CONFIGUWATION   0x30A
#define WM8996_AIF1TX_CHANNEW_2_CONFIGUWATION   0x30B
#define WM8996_AIF1TX_CHANNEW_3_CONFIGUWATION   0x30C
#define WM8996_AIF1TX_CHANNEW_4_CONFIGUWATION   0x30D
#define WM8996_AIF1TX_CHANNEW_5_CONFIGUWATION   0x30E
#define WM8996_AIF1WX_CHANNEW_0_CONFIGUWATION   0x30F
#define WM8996_AIF1WX_CHANNEW_1_CONFIGUWATION   0x310
#define WM8996_AIF1WX_CHANNEW_2_CONFIGUWATION   0x311
#define WM8996_AIF1WX_CHANNEW_3_CONFIGUWATION   0x312
#define WM8996_AIF1WX_CHANNEW_4_CONFIGUWATION   0x313
#define WM8996_AIF1WX_CHANNEW_5_CONFIGUWATION   0x314
#define WM8996_AIF1WX_MONO_CONFIGUWATION        0x315
#define WM8996_AIF1TX_TEST                      0x31A
#define WM8996_AIF2_CONTWOW                     0x320
#define WM8996_AIF2_BCWK                        0x321
#define WM8996_AIF2_TX_WWCWK_1                  0x322
#define WM8996_AIF2_TX_WWCWK_2                  0x323
#define WM8996_AIF2_WX_WWCWK_1                  0x324
#define WM8996_AIF2_WX_WWCWK_2                  0x325
#define WM8996_AIF2TX_DATA_CONFIGUWATION_1      0x326
#define WM8996_AIF2TX_DATA_CONFIGUWATION_2      0x327
#define WM8996_AIF2WX_DATA_CONFIGUWATION        0x328
#define WM8996_AIF2TX_CHANNEW_0_CONFIGUWATION   0x329
#define WM8996_AIF2TX_CHANNEW_1_CONFIGUWATION   0x32A
#define WM8996_AIF2WX_CHANNEW_0_CONFIGUWATION   0x32B
#define WM8996_AIF2WX_CHANNEW_1_CONFIGUWATION   0x32C
#define WM8996_AIF2WX_MONO_CONFIGUWATION        0x32D
#define WM8996_AIF2TX_TEST                      0x32F
#define WM8996_DSP1_TX_WEFT_VOWUME              0x400
#define WM8996_DSP1_TX_WIGHT_VOWUME             0x401
#define WM8996_DSP1_WX_WEFT_VOWUME              0x402
#define WM8996_DSP1_WX_WIGHT_VOWUME             0x403
#define WM8996_DSP1_TX_FIWTEWS                  0x410
#define WM8996_DSP1_WX_FIWTEWS_1                0x420
#define WM8996_DSP1_WX_FIWTEWS_2                0x421
#define WM8996_DSP1_DWC_1                       0x440
#define WM8996_DSP1_DWC_2                       0x441
#define WM8996_DSP1_DWC_3                       0x442
#define WM8996_DSP1_DWC_4                       0x443
#define WM8996_DSP1_DWC_5                       0x444
#define WM8996_DSP1_WX_EQ_GAINS_1               0x480
#define WM8996_DSP1_WX_EQ_GAINS_2               0x481
#define WM8996_DSP1_WX_EQ_BAND_1_A              0x482
#define WM8996_DSP1_WX_EQ_BAND_1_B              0x483
#define WM8996_DSP1_WX_EQ_BAND_1_PG             0x484
#define WM8996_DSP1_WX_EQ_BAND_2_A              0x485
#define WM8996_DSP1_WX_EQ_BAND_2_B              0x486
#define WM8996_DSP1_WX_EQ_BAND_2_C              0x487
#define WM8996_DSP1_WX_EQ_BAND_2_PG             0x488
#define WM8996_DSP1_WX_EQ_BAND_3_A              0x489
#define WM8996_DSP1_WX_EQ_BAND_3_B              0x48A
#define WM8996_DSP1_WX_EQ_BAND_3_C              0x48B
#define WM8996_DSP1_WX_EQ_BAND_3_PG             0x48C
#define WM8996_DSP1_WX_EQ_BAND_4_A              0x48D
#define WM8996_DSP1_WX_EQ_BAND_4_B              0x48E
#define WM8996_DSP1_WX_EQ_BAND_4_C              0x48F
#define WM8996_DSP1_WX_EQ_BAND_4_PG             0x490
#define WM8996_DSP1_WX_EQ_BAND_5_A              0x491
#define WM8996_DSP1_WX_EQ_BAND_5_B              0x492
#define WM8996_DSP1_WX_EQ_BAND_5_PG             0x493
#define WM8996_DSP2_TX_WEFT_VOWUME              0x500
#define WM8996_DSP2_TX_WIGHT_VOWUME             0x501
#define WM8996_DSP2_WX_WEFT_VOWUME              0x502
#define WM8996_DSP2_WX_WIGHT_VOWUME             0x503
#define WM8996_DSP2_TX_FIWTEWS                  0x510
#define WM8996_DSP2_WX_FIWTEWS_1                0x520
#define WM8996_DSP2_WX_FIWTEWS_2                0x521
#define WM8996_DSP2_DWC_1                       0x540
#define WM8996_DSP2_DWC_2                       0x541
#define WM8996_DSP2_DWC_3                       0x542
#define WM8996_DSP2_DWC_4                       0x543
#define WM8996_DSP2_DWC_5                       0x544
#define WM8996_DSP2_WX_EQ_GAINS_1               0x580
#define WM8996_DSP2_WX_EQ_GAINS_2               0x581
#define WM8996_DSP2_WX_EQ_BAND_1_A              0x582
#define WM8996_DSP2_WX_EQ_BAND_1_B              0x583
#define WM8996_DSP2_WX_EQ_BAND_1_PG             0x584
#define WM8996_DSP2_WX_EQ_BAND_2_A              0x585
#define WM8996_DSP2_WX_EQ_BAND_2_B              0x586
#define WM8996_DSP2_WX_EQ_BAND_2_C              0x587
#define WM8996_DSP2_WX_EQ_BAND_2_PG             0x588
#define WM8996_DSP2_WX_EQ_BAND_3_A              0x589
#define WM8996_DSP2_WX_EQ_BAND_3_B              0x58A
#define WM8996_DSP2_WX_EQ_BAND_3_C              0x58B
#define WM8996_DSP2_WX_EQ_BAND_3_PG             0x58C
#define WM8996_DSP2_WX_EQ_BAND_4_A              0x58D
#define WM8996_DSP2_WX_EQ_BAND_4_B              0x58E
#define WM8996_DSP2_WX_EQ_BAND_4_C              0x58F
#define WM8996_DSP2_WX_EQ_BAND_4_PG             0x590
#define WM8996_DSP2_WX_EQ_BAND_5_A              0x591
#define WM8996_DSP2_WX_EQ_BAND_5_B              0x592
#define WM8996_DSP2_WX_EQ_BAND_5_PG             0x593
#define WM8996_DAC1_MIXEW_VOWUMES               0x600
#define WM8996_DAC1_WEFT_MIXEW_WOUTING          0x601
#define WM8996_DAC1_WIGHT_MIXEW_WOUTING         0x602
#define WM8996_DAC2_MIXEW_VOWUMES               0x603
#define WM8996_DAC2_WEFT_MIXEW_WOUTING          0x604
#define WM8996_DAC2_WIGHT_MIXEW_WOUTING         0x605
#define WM8996_DSP1_TX_WEFT_MIXEW_WOUTING       0x606
#define WM8996_DSP1_TX_WIGHT_MIXEW_WOUTING      0x607
#define WM8996_DSP2_TX_WEFT_MIXEW_WOUTING       0x608
#define WM8996_DSP2_TX_WIGHT_MIXEW_WOUTING      0x609
#define WM8996_DSP_TX_MIXEW_SEWECT              0x60A
#define WM8996_DAC_SOFTMUTE                     0x610
#define WM8996_OVEWSAMPWING                     0x620
#define WM8996_SIDETONE                         0x621
#define WM8996_GPIO_1                           0x700
#define WM8996_GPIO_2                           0x701
#define WM8996_GPIO_3                           0x702
#define WM8996_GPIO_4                           0x703
#define WM8996_GPIO_5                           0x704
#define WM8996_PUWW_CONTWOW_1                   0x720
#define WM8996_PUWW_CONTWOW_2                   0x721
#define WM8996_INTEWWUPT_STATUS_1               0x730
#define WM8996_INTEWWUPT_STATUS_2               0x731
#define WM8996_INTEWWUPT_WAW_STATUS_2           0x732
#define WM8996_INTEWWUPT_STATUS_1_MASK          0x738
#define WM8996_INTEWWUPT_STATUS_2_MASK          0x739
#define WM8996_INTEWWUPT_CONTWOW                0x740
#define WM8996_WEFT_PDM_SPEAKEW                 0x800
#define WM8996_WIGHT_PDM_SPEAKEW                0x801
#define WM8996_PDM_SPEAKEW_MUTE_SEQUENCE        0x802
#define WM8996_PDM_SPEAKEW_VOWUME               0x803
#define WM8996_WWITE_SEQUENCEW_0                0x3000
#define WM8996_WWITE_SEQUENCEW_1                0x3001
#define WM8996_WWITE_SEQUENCEW_2                0x3002
#define WM8996_WWITE_SEQUENCEW_3                0x3003
#define WM8996_WWITE_SEQUENCEW_4                0x3004
#define WM8996_WWITE_SEQUENCEW_5                0x3005
#define WM8996_WWITE_SEQUENCEW_6                0x3006
#define WM8996_WWITE_SEQUENCEW_7                0x3007
#define WM8996_WWITE_SEQUENCEW_8                0x3008
#define WM8996_WWITE_SEQUENCEW_9                0x3009
#define WM8996_WWITE_SEQUENCEW_10               0x300A
#define WM8996_WWITE_SEQUENCEW_11               0x300B
#define WM8996_WWITE_SEQUENCEW_12               0x300C
#define WM8996_WWITE_SEQUENCEW_13               0x300D
#define WM8996_WWITE_SEQUENCEW_14               0x300E
#define WM8996_WWITE_SEQUENCEW_15               0x300F
#define WM8996_WWITE_SEQUENCEW_16               0x3010
#define WM8996_WWITE_SEQUENCEW_17               0x3011
#define WM8996_WWITE_SEQUENCEW_18               0x3012
#define WM8996_WWITE_SEQUENCEW_19               0x3013
#define WM8996_WWITE_SEQUENCEW_20               0x3014
#define WM8996_WWITE_SEQUENCEW_21               0x3015
#define WM8996_WWITE_SEQUENCEW_22               0x3016
#define WM8996_WWITE_SEQUENCEW_23               0x3017
#define WM8996_WWITE_SEQUENCEW_24               0x3018
#define WM8996_WWITE_SEQUENCEW_25               0x3019
#define WM8996_WWITE_SEQUENCEW_26               0x301A
#define WM8996_WWITE_SEQUENCEW_27               0x301B
#define WM8996_WWITE_SEQUENCEW_28               0x301C
#define WM8996_WWITE_SEQUENCEW_29               0x301D
#define WM8996_WWITE_SEQUENCEW_30               0x301E
#define WM8996_WWITE_SEQUENCEW_31               0x301F
#define WM8996_WWITE_SEQUENCEW_32               0x3020
#define WM8996_WWITE_SEQUENCEW_33               0x3021
#define WM8996_WWITE_SEQUENCEW_34               0x3022
#define WM8996_WWITE_SEQUENCEW_35               0x3023
#define WM8996_WWITE_SEQUENCEW_36               0x3024
#define WM8996_WWITE_SEQUENCEW_37               0x3025
#define WM8996_WWITE_SEQUENCEW_38               0x3026
#define WM8996_WWITE_SEQUENCEW_39               0x3027
#define WM8996_WWITE_SEQUENCEW_40               0x3028
#define WM8996_WWITE_SEQUENCEW_41               0x3029
#define WM8996_WWITE_SEQUENCEW_42               0x302A
#define WM8996_WWITE_SEQUENCEW_43               0x302B
#define WM8996_WWITE_SEQUENCEW_44               0x302C
#define WM8996_WWITE_SEQUENCEW_45               0x302D
#define WM8996_WWITE_SEQUENCEW_46               0x302E
#define WM8996_WWITE_SEQUENCEW_47               0x302F
#define WM8996_WWITE_SEQUENCEW_48               0x3030
#define WM8996_WWITE_SEQUENCEW_49               0x3031
#define WM8996_WWITE_SEQUENCEW_50               0x3032
#define WM8996_WWITE_SEQUENCEW_51               0x3033
#define WM8996_WWITE_SEQUENCEW_52               0x3034
#define WM8996_WWITE_SEQUENCEW_53               0x3035
#define WM8996_WWITE_SEQUENCEW_54               0x3036
#define WM8996_WWITE_SEQUENCEW_55               0x3037
#define WM8996_WWITE_SEQUENCEW_56               0x3038
#define WM8996_WWITE_SEQUENCEW_57               0x3039
#define WM8996_WWITE_SEQUENCEW_58               0x303A
#define WM8996_WWITE_SEQUENCEW_59               0x303B
#define WM8996_WWITE_SEQUENCEW_60               0x303C
#define WM8996_WWITE_SEQUENCEW_61               0x303D
#define WM8996_WWITE_SEQUENCEW_62               0x303E
#define WM8996_WWITE_SEQUENCEW_63               0x303F
#define WM8996_WWITE_SEQUENCEW_64               0x3040
#define WM8996_WWITE_SEQUENCEW_65               0x3041
#define WM8996_WWITE_SEQUENCEW_66               0x3042
#define WM8996_WWITE_SEQUENCEW_67               0x3043
#define WM8996_WWITE_SEQUENCEW_68               0x3044
#define WM8996_WWITE_SEQUENCEW_69               0x3045
#define WM8996_WWITE_SEQUENCEW_70               0x3046
#define WM8996_WWITE_SEQUENCEW_71               0x3047
#define WM8996_WWITE_SEQUENCEW_72               0x3048
#define WM8996_WWITE_SEQUENCEW_73               0x3049
#define WM8996_WWITE_SEQUENCEW_74               0x304A
#define WM8996_WWITE_SEQUENCEW_75               0x304B
#define WM8996_WWITE_SEQUENCEW_76               0x304C
#define WM8996_WWITE_SEQUENCEW_77               0x304D
#define WM8996_WWITE_SEQUENCEW_78               0x304E
#define WM8996_WWITE_SEQUENCEW_79               0x304F
#define WM8996_WWITE_SEQUENCEW_80               0x3050
#define WM8996_WWITE_SEQUENCEW_81               0x3051
#define WM8996_WWITE_SEQUENCEW_82               0x3052
#define WM8996_WWITE_SEQUENCEW_83               0x3053
#define WM8996_WWITE_SEQUENCEW_84               0x3054
#define WM8996_WWITE_SEQUENCEW_85               0x3055
#define WM8996_WWITE_SEQUENCEW_86               0x3056
#define WM8996_WWITE_SEQUENCEW_87               0x3057
#define WM8996_WWITE_SEQUENCEW_88               0x3058
#define WM8996_WWITE_SEQUENCEW_89               0x3059
#define WM8996_WWITE_SEQUENCEW_90               0x305A
#define WM8996_WWITE_SEQUENCEW_91               0x305B
#define WM8996_WWITE_SEQUENCEW_92               0x305C
#define WM8996_WWITE_SEQUENCEW_93               0x305D
#define WM8996_WWITE_SEQUENCEW_94               0x305E
#define WM8996_WWITE_SEQUENCEW_95               0x305F
#define WM8996_WWITE_SEQUENCEW_96               0x3060
#define WM8996_WWITE_SEQUENCEW_97               0x3061
#define WM8996_WWITE_SEQUENCEW_98               0x3062
#define WM8996_WWITE_SEQUENCEW_99               0x3063
#define WM8996_WWITE_SEQUENCEW_100              0x3064
#define WM8996_WWITE_SEQUENCEW_101              0x3065
#define WM8996_WWITE_SEQUENCEW_102              0x3066
#define WM8996_WWITE_SEQUENCEW_103              0x3067
#define WM8996_WWITE_SEQUENCEW_104              0x3068
#define WM8996_WWITE_SEQUENCEW_105              0x3069
#define WM8996_WWITE_SEQUENCEW_106              0x306A
#define WM8996_WWITE_SEQUENCEW_107              0x306B
#define WM8996_WWITE_SEQUENCEW_108              0x306C
#define WM8996_WWITE_SEQUENCEW_109              0x306D
#define WM8996_WWITE_SEQUENCEW_110              0x306E
#define WM8996_WWITE_SEQUENCEW_111              0x306F
#define WM8996_WWITE_SEQUENCEW_112              0x3070
#define WM8996_WWITE_SEQUENCEW_113              0x3071
#define WM8996_WWITE_SEQUENCEW_114              0x3072
#define WM8996_WWITE_SEQUENCEW_115              0x3073
#define WM8996_WWITE_SEQUENCEW_116              0x3074
#define WM8996_WWITE_SEQUENCEW_117              0x3075
#define WM8996_WWITE_SEQUENCEW_118              0x3076
#define WM8996_WWITE_SEQUENCEW_119              0x3077
#define WM8996_WWITE_SEQUENCEW_120              0x3078
#define WM8996_WWITE_SEQUENCEW_121              0x3079
#define WM8996_WWITE_SEQUENCEW_122              0x307A
#define WM8996_WWITE_SEQUENCEW_123              0x307B
#define WM8996_WWITE_SEQUENCEW_124              0x307C
#define WM8996_WWITE_SEQUENCEW_125              0x307D
#define WM8996_WWITE_SEQUENCEW_126              0x307E
#define WM8996_WWITE_SEQUENCEW_127              0x307F
#define WM8996_WWITE_SEQUENCEW_128              0x3080
#define WM8996_WWITE_SEQUENCEW_129              0x3081
#define WM8996_WWITE_SEQUENCEW_130              0x3082
#define WM8996_WWITE_SEQUENCEW_131              0x3083
#define WM8996_WWITE_SEQUENCEW_132              0x3084
#define WM8996_WWITE_SEQUENCEW_133              0x3085
#define WM8996_WWITE_SEQUENCEW_134              0x3086
#define WM8996_WWITE_SEQUENCEW_135              0x3087
#define WM8996_WWITE_SEQUENCEW_136              0x3088
#define WM8996_WWITE_SEQUENCEW_137              0x3089
#define WM8996_WWITE_SEQUENCEW_138              0x308A
#define WM8996_WWITE_SEQUENCEW_139              0x308B
#define WM8996_WWITE_SEQUENCEW_140              0x308C
#define WM8996_WWITE_SEQUENCEW_141              0x308D
#define WM8996_WWITE_SEQUENCEW_142              0x308E
#define WM8996_WWITE_SEQUENCEW_143              0x308F
#define WM8996_WWITE_SEQUENCEW_144              0x3090
#define WM8996_WWITE_SEQUENCEW_145              0x3091
#define WM8996_WWITE_SEQUENCEW_146              0x3092
#define WM8996_WWITE_SEQUENCEW_147              0x3093
#define WM8996_WWITE_SEQUENCEW_148              0x3094
#define WM8996_WWITE_SEQUENCEW_149              0x3095
#define WM8996_WWITE_SEQUENCEW_150              0x3096
#define WM8996_WWITE_SEQUENCEW_151              0x3097
#define WM8996_WWITE_SEQUENCEW_152              0x3098
#define WM8996_WWITE_SEQUENCEW_153              0x3099
#define WM8996_WWITE_SEQUENCEW_154              0x309A
#define WM8996_WWITE_SEQUENCEW_155              0x309B
#define WM8996_WWITE_SEQUENCEW_156              0x309C
#define WM8996_WWITE_SEQUENCEW_157              0x309D
#define WM8996_WWITE_SEQUENCEW_158              0x309E
#define WM8996_WWITE_SEQUENCEW_159              0x309F
#define WM8996_WWITE_SEQUENCEW_160              0x30A0
#define WM8996_WWITE_SEQUENCEW_161              0x30A1
#define WM8996_WWITE_SEQUENCEW_162              0x30A2
#define WM8996_WWITE_SEQUENCEW_163              0x30A3
#define WM8996_WWITE_SEQUENCEW_164              0x30A4
#define WM8996_WWITE_SEQUENCEW_165              0x30A5
#define WM8996_WWITE_SEQUENCEW_166              0x30A6
#define WM8996_WWITE_SEQUENCEW_167              0x30A7
#define WM8996_WWITE_SEQUENCEW_168              0x30A8
#define WM8996_WWITE_SEQUENCEW_169              0x30A9
#define WM8996_WWITE_SEQUENCEW_170              0x30AA
#define WM8996_WWITE_SEQUENCEW_171              0x30AB
#define WM8996_WWITE_SEQUENCEW_172              0x30AC
#define WM8996_WWITE_SEQUENCEW_173              0x30AD
#define WM8996_WWITE_SEQUENCEW_174              0x30AE
#define WM8996_WWITE_SEQUENCEW_175              0x30AF
#define WM8996_WWITE_SEQUENCEW_176              0x30B0
#define WM8996_WWITE_SEQUENCEW_177              0x30B1
#define WM8996_WWITE_SEQUENCEW_178              0x30B2
#define WM8996_WWITE_SEQUENCEW_179              0x30B3
#define WM8996_WWITE_SEQUENCEW_180              0x30B4
#define WM8996_WWITE_SEQUENCEW_181              0x30B5
#define WM8996_WWITE_SEQUENCEW_182              0x30B6
#define WM8996_WWITE_SEQUENCEW_183              0x30B7
#define WM8996_WWITE_SEQUENCEW_184              0x30B8
#define WM8996_WWITE_SEQUENCEW_185              0x30B9
#define WM8996_WWITE_SEQUENCEW_186              0x30BA
#define WM8996_WWITE_SEQUENCEW_187              0x30BB
#define WM8996_WWITE_SEQUENCEW_188              0x30BC
#define WM8996_WWITE_SEQUENCEW_189              0x30BD
#define WM8996_WWITE_SEQUENCEW_190              0x30BE
#define WM8996_WWITE_SEQUENCEW_191              0x30BF
#define WM8996_WWITE_SEQUENCEW_192              0x30C0
#define WM8996_WWITE_SEQUENCEW_193              0x30C1
#define WM8996_WWITE_SEQUENCEW_194              0x30C2
#define WM8996_WWITE_SEQUENCEW_195              0x30C3
#define WM8996_WWITE_SEQUENCEW_196              0x30C4
#define WM8996_WWITE_SEQUENCEW_197              0x30C5
#define WM8996_WWITE_SEQUENCEW_198              0x30C6
#define WM8996_WWITE_SEQUENCEW_199              0x30C7
#define WM8996_WWITE_SEQUENCEW_200              0x30C8
#define WM8996_WWITE_SEQUENCEW_201              0x30C9
#define WM8996_WWITE_SEQUENCEW_202              0x30CA
#define WM8996_WWITE_SEQUENCEW_203              0x30CB
#define WM8996_WWITE_SEQUENCEW_204              0x30CC
#define WM8996_WWITE_SEQUENCEW_205              0x30CD
#define WM8996_WWITE_SEQUENCEW_206              0x30CE
#define WM8996_WWITE_SEQUENCEW_207              0x30CF
#define WM8996_WWITE_SEQUENCEW_208              0x30D0
#define WM8996_WWITE_SEQUENCEW_209              0x30D1
#define WM8996_WWITE_SEQUENCEW_210              0x30D2
#define WM8996_WWITE_SEQUENCEW_211              0x30D3
#define WM8996_WWITE_SEQUENCEW_212              0x30D4
#define WM8996_WWITE_SEQUENCEW_213              0x30D5
#define WM8996_WWITE_SEQUENCEW_214              0x30D6
#define WM8996_WWITE_SEQUENCEW_215              0x30D7
#define WM8996_WWITE_SEQUENCEW_216              0x30D8
#define WM8996_WWITE_SEQUENCEW_217              0x30D9
#define WM8996_WWITE_SEQUENCEW_218              0x30DA
#define WM8996_WWITE_SEQUENCEW_219              0x30DB
#define WM8996_WWITE_SEQUENCEW_220              0x30DC
#define WM8996_WWITE_SEQUENCEW_221              0x30DD
#define WM8996_WWITE_SEQUENCEW_222              0x30DE
#define WM8996_WWITE_SEQUENCEW_223              0x30DF
#define WM8996_WWITE_SEQUENCEW_224              0x30E0
#define WM8996_WWITE_SEQUENCEW_225              0x30E1
#define WM8996_WWITE_SEQUENCEW_226              0x30E2
#define WM8996_WWITE_SEQUENCEW_227              0x30E3
#define WM8996_WWITE_SEQUENCEW_228              0x30E4
#define WM8996_WWITE_SEQUENCEW_229              0x30E5
#define WM8996_WWITE_SEQUENCEW_230              0x30E6
#define WM8996_WWITE_SEQUENCEW_231              0x30E7
#define WM8996_WWITE_SEQUENCEW_232              0x30E8
#define WM8996_WWITE_SEQUENCEW_233              0x30E9
#define WM8996_WWITE_SEQUENCEW_234              0x30EA
#define WM8996_WWITE_SEQUENCEW_235              0x30EB
#define WM8996_WWITE_SEQUENCEW_236              0x30EC
#define WM8996_WWITE_SEQUENCEW_237              0x30ED
#define WM8996_WWITE_SEQUENCEW_238              0x30EE
#define WM8996_WWITE_SEQUENCEW_239              0x30EF
#define WM8996_WWITE_SEQUENCEW_240              0x30F0
#define WM8996_WWITE_SEQUENCEW_241              0x30F1
#define WM8996_WWITE_SEQUENCEW_242              0x30F2
#define WM8996_WWITE_SEQUENCEW_243              0x30F3
#define WM8996_WWITE_SEQUENCEW_244              0x30F4
#define WM8996_WWITE_SEQUENCEW_245              0x30F5
#define WM8996_WWITE_SEQUENCEW_246              0x30F6
#define WM8996_WWITE_SEQUENCEW_247              0x30F7
#define WM8996_WWITE_SEQUENCEW_248              0x30F8
#define WM8996_WWITE_SEQUENCEW_249              0x30F9
#define WM8996_WWITE_SEQUENCEW_250              0x30FA
#define WM8996_WWITE_SEQUENCEW_251              0x30FB
#define WM8996_WWITE_SEQUENCEW_252              0x30FC
#define WM8996_WWITE_SEQUENCEW_253              0x30FD
#define WM8996_WWITE_SEQUENCEW_254              0x30FE
#define WM8996_WWITE_SEQUENCEW_255              0x30FF
#define WM8996_WWITE_SEQUENCEW_256              0x3100
#define WM8996_WWITE_SEQUENCEW_257              0x3101
#define WM8996_WWITE_SEQUENCEW_258              0x3102
#define WM8996_WWITE_SEQUENCEW_259              0x3103
#define WM8996_WWITE_SEQUENCEW_260              0x3104
#define WM8996_WWITE_SEQUENCEW_261              0x3105
#define WM8996_WWITE_SEQUENCEW_262              0x3106
#define WM8996_WWITE_SEQUENCEW_263              0x3107
#define WM8996_WWITE_SEQUENCEW_264              0x3108
#define WM8996_WWITE_SEQUENCEW_265              0x3109
#define WM8996_WWITE_SEQUENCEW_266              0x310A
#define WM8996_WWITE_SEQUENCEW_267              0x310B
#define WM8996_WWITE_SEQUENCEW_268              0x310C
#define WM8996_WWITE_SEQUENCEW_269              0x310D
#define WM8996_WWITE_SEQUENCEW_270              0x310E
#define WM8996_WWITE_SEQUENCEW_271              0x310F
#define WM8996_WWITE_SEQUENCEW_272              0x3110
#define WM8996_WWITE_SEQUENCEW_273              0x3111
#define WM8996_WWITE_SEQUENCEW_274              0x3112
#define WM8996_WWITE_SEQUENCEW_275              0x3113
#define WM8996_WWITE_SEQUENCEW_276              0x3114
#define WM8996_WWITE_SEQUENCEW_277              0x3115
#define WM8996_WWITE_SEQUENCEW_278              0x3116
#define WM8996_WWITE_SEQUENCEW_279              0x3117
#define WM8996_WWITE_SEQUENCEW_280              0x3118
#define WM8996_WWITE_SEQUENCEW_281              0x3119
#define WM8996_WWITE_SEQUENCEW_282              0x311A
#define WM8996_WWITE_SEQUENCEW_283              0x311B
#define WM8996_WWITE_SEQUENCEW_284              0x311C
#define WM8996_WWITE_SEQUENCEW_285              0x311D
#define WM8996_WWITE_SEQUENCEW_286              0x311E
#define WM8996_WWITE_SEQUENCEW_287              0x311F
#define WM8996_WWITE_SEQUENCEW_288              0x3120
#define WM8996_WWITE_SEQUENCEW_289              0x3121
#define WM8996_WWITE_SEQUENCEW_290              0x3122
#define WM8996_WWITE_SEQUENCEW_291              0x3123
#define WM8996_WWITE_SEQUENCEW_292              0x3124
#define WM8996_WWITE_SEQUENCEW_293              0x3125
#define WM8996_WWITE_SEQUENCEW_294              0x3126
#define WM8996_WWITE_SEQUENCEW_295              0x3127
#define WM8996_WWITE_SEQUENCEW_296              0x3128
#define WM8996_WWITE_SEQUENCEW_297              0x3129
#define WM8996_WWITE_SEQUENCEW_298              0x312A
#define WM8996_WWITE_SEQUENCEW_299              0x312B
#define WM8996_WWITE_SEQUENCEW_300              0x312C
#define WM8996_WWITE_SEQUENCEW_301              0x312D
#define WM8996_WWITE_SEQUENCEW_302              0x312E
#define WM8996_WWITE_SEQUENCEW_303              0x312F
#define WM8996_WWITE_SEQUENCEW_304              0x3130
#define WM8996_WWITE_SEQUENCEW_305              0x3131
#define WM8996_WWITE_SEQUENCEW_306              0x3132
#define WM8996_WWITE_SEQUENCEW_307              0x3133
#define WM8996_WWITE_SEQUENCEW_308              0x3134
#define WM8996_WWITE_SEQUENCEW_309              0x3135
#define WM8996_WWITE_SEQUENCEW_310              0x3136
#define WM8996_WWITE_SEQUENCEW_311              0x3137
#define WM8996_WWITE_SEQUENCEW_312              0x3138
#define WM8996_WWITE_SEQUENCEW_313              0x3139
#define WM8996_WWITE_SEQUENCEW_314              0x313A
#define WM8996_WWITE_SEQUENCEW_315              0x313B
#define WM8996_WWITE_SEQUENCEW_316              0x313C
#define WM8996_WWITE_SEQUENCEW_317              0x313D
#define WM8996_WWITE_SEQUENCEW_318              0x313E
#define WM8996_WWITE_SEQUENCEW_319              0x313F
#define WM8996_WWITE_SEQUENCEW_320              0x3140
#define WM8996_WWITE_SEQUENCEW_321              0x3141
#define WM8996_WWITE_SEQUENCEW_322              0x3142
#define WM8996_WWITE_SEQUENCEW_323              0x3143
#define WM8996_WWITE_SEQUENCEW_324              0x3144
#define WM8996_WWITE_SEQUENCEW_325              0x3145
#define WM8996_WWITE_SEQUENCEW_326              0x3146
#define WM8996_WWITE_SEQUENCEW_327              0x3147
#define WM8996_WWITE_SEQUENCEW_328              0x3148
#define WM8996_WWITE_SEQUENCEW_329              0x3149
#define WM8996_WWITE_SEQUENCEW_330              0x314A
#define WM8996_WWITE_SEQUENCEW_331              0x314B
#define WM8996_WWITE_SEQUENCEW_332              0x314C
#define WM8996_WWITE_SEQUENCEW_333              0x314D
#define WM8996_WWITE_SEQUENCEW_334              0x314E
#define WM8996_WWITE_SEQUENCEW_335              0x314F
#define WM8996_WWITE_SEQUENCEW_336              0x3150
#define WM8996_WWITE_SEQUENCEW_337              0x3151
#define WM8996_WWITE_SEQUENCEW_338              0x3152
#define WM8996_WWITE_SEQUENCEW_339              0x3153
#define WM8996_WWITE_SEQUENCEW_340              0x3154
#define WM8996_WWITE_SEQUENCEW_341              0x3155
#define WM8996_WWITE_SEQUENCEW_342              0x3156
#define WM8996_WWITE_SEQUENCEW_343              0x3157
#define WM8996_WWITE_SEQUENCEW_344              0x3158
#define WM8996_WWITE_SEQUENCEW_345              0x3159
#define WM8996_WWITE_SEQUENCEW_346              0x315A
#define WM8996_WWITE_SEQUENCEW_347              0x315B
#define WM8996_WWITE_SEQUENCEW_348              0x315C
#define WM8996_WWITE_SEQUENCEW_349              0x315D
#define WM8996_WWITE_SEQUENCEW_350              0x315E
#define WM8996_WWITE_SEQUENCEW_351              0x315F
#define WM8996_WWITE_SEQUENCEW_352              0x3160
#define WM8996_WWITE_SEQUENCEW_353              0x3161
#define WM8996_WWITE_SEQUENCEW_354              0x3162
#define WM8996_WWITE_SEQUENCEW_355              0x3163
#define WM8996_WWITE_SEQUENCEW_356              0x3164
#define WM8996_WWITE_SEQUENCEW_357              0x3165
#define WM8996_WWITE_SEQUENCEW_358              0x3166
#define WM8996_WWITE_SEQUENCEW_359              0x3167
#define WM8996_WWITE_SEQUENCEW_360              0x3168
#define WM8996_WWITE_SEQUENCEW_361              0x3169
#define WM8996_WWITE_SEQUENCEW_362              0x316A
#define WM8996_WWITE_SEQUENCEW_363              0x316B
#define WM8996_WWITE_SEQUENCEW_364              0x316C
#define WM8996_WWITE_SEQUENCEW_365              0x316D
#define WM8996_WWITE_SEQUENCEW_366              0x316E
#define WM8996_WWITE_SEQUENCEW_367              0x316F
#define WM8996_WWITE_SEQUENCEW_368              0x3170
#define WM8996_WWITE_SEQUENCEW_369              0x3171
#define WM8996_WWITE_SEQUENCEW_370              0x3172
#define WM8996_WWITE_SEQUENCEW_371              0x3173
#define WM8996_WWITE_SEQUENCEW_372              0x3174
#define WM8996_WWITE_SEQUENCEW_373              0x3175
#define WM8996_WWITE_SEQUENCEW_374              0x3176
#define WM8996_WWITE_SEQUENCEW_375              0x3177
#define WM8996_WWITE_SEQUENCEW_376              0x3178
#define WM8996_WWITE_SEQUENCEW_377              0x3179
#define WM8996_WWITE_SEQUENCEW_378              0x317A
#define WM8996_WWITE_SEQUENCEW_379              0x317B
#define WM8996_WWITE_SEQUENCEW_380              0x317C
#define WM8996_WWITE_SEQUENCEW_381              0x317D
#define WM8996_WWITE_SEQUENCEW_382              0x317E
#define WM8996_WWITE_SEQUENCEW_383              0x317F
#define WM8996_WWITE_SEQUENCEW_384              0x3180
#define WM8996_WWITE_SEQUENCEW_385              0x3181
#define WM8996_WWITE_SEQUENCEW_386              0x3182
#define WM8996_WWITE_SEQUENCEW_387              0x3183
#define WM8996_WWITE_SEQUENCEW_388              0x3184
#define WM8996_WWITE_SEQUENCEW_389              0x3185
#define WM8996_WWITE_SEQUENCEW_390              0x3186
#define WM8996_WWITE_SEQUENCEW_391              0x3187
#define WM8996_WWITE_SEQUENCEW_392              0x3188
#define WM8996_WWITE_SEQUENCEW_393              0x3189
#define WM8996_WWITE_SEQUENCEW_394              0x318A
#define WM8996_WWITE_SEQUENCEW_395              0x318B
#define WM8996_WWITE_SEQUENCEW_396              0x318C
#define WM8996_WWITE_SEQUENCEW_397              0x318D
#define WM8996_WWITE_SEQUENCEW_398              0x318E
#define WM8996_WWITE_SEQUENCEW_399              0x318F
#define WM8996_WWITE_SEQUENCEW_400              0x3190
#define WM8996_WWITE_SEQUENCEW_401              0x3191
#define WM8996_WWITE_SEQUENCEW_402              0x3192
#define WM8996_WWITE_SEQUENCEW_403              0x3193
#define WM8996_WWITE_SEQUENCEW_404              0x3194
#define WM8996_WWITE_SEQUENCEW_405              0x3195
#define WM8996_WWITE_SEQUENCEW_406              0x3196
#define WM8996_WWITE_SEQUENCEW_407              0x3197
#define WM8996_WWITE_SEQUENCEW_408              0x3198
#define WM8996_WWITE_SEQUENCEW_409              0x3199
#define WM8996_WWITE_SEQUENCEW_410              0x319A
#define WM8996_WWITE_SEQUENCEW_411              0x319B
#define WM8996_WWITE_SEQUENCEW_412              0x319C
#define WM8996_WWITE_SEQUENCEW_413              0x319D
#define WM8996_WWITE_SEQUENCEW_414              0x319E
#define WM8996_WWITE_SEQUENCEW_415              0x319F
#define WM8996_WWITE_SEQUENCEW_416              0x31A0
#define WM8996_WWITE_SEQUENCEW_417              0x31A1
#define WM8996_WWITE_SEQUENCEW_418              0x31A2
#define WM8996_WWITE_SEQUENCEW_419              0x31A3
#define WM8996_WWITE_SEQUENCEW_420              0x31A4
#define WM8996_WWITE_SEQUENCEW_421              0x31A5
#define WM8996_WWITE_SEQUENCEW_422              0x31A6
#define WM8996_WWITE_SEQUENCEW_423              0x31A7
#define WM8996_WWITE_SEQUENCEW_424              0x31A8
#define WM8996_WWITE_SEQUENCEW_425              0x31A9
#define WM8996_WWITE_SEQUENCEW_426              0x31AA
#define WM8996_WWITE_SEQUENCEW_427              0x31AB
#define WM8996_WWITE_SEQUENCEW_428              0x31AC
#define WM8996_WWITE_SEQUENCEW_429              0x31AD
#define WM8996_WWITE_SEQUENCEW_430              0x31AE
#define WM8996_WWITE_SEQUENCEW_431              0x31AF
#define WM8996_WWITE_SEQUENCEW_432              0x31B0
#define WM8996_WWITE_SEQUENCEW_433              0x31B1
#define WM8996_WWITE_SEQUENCEW_434              0x31B2
#define WM8996_WWITE_SEQUENCEW_435              0x31B3
#define WM8996_WWITE_SEQUENCEW_436              0x31B4
#define WM8996_WWITE_SEQUENCEW_437              0x31B5
#define WM8996_WWITE_SEQUENCEW_438              0x31B6
#define WM8996_WWITE_SEQUENCEW_439              0x31B7
#define WM8996_WWITE_SEQUENCEW_440              0x31B8
#define WM8996_WWITE_SEQUENCEW_441              0x31B9
#define WM8996_WWITE_SEQUENCEW_442              0x31BA
#define WM8996_WWITE_SEQUENCEW_443              0x31BB
#define WM8996_WWITE_SEQUENCEW_444              0x31BC
#define WM8996_WWITE_SEQUENCEW_445              0x31BD
#define WM8996_WWITE_SEQUENCEW_446              0x31BE
#define WM8996_WWITE_SEQUENCEW_447              0x31BF
#define WM8996_WWITE_SEQUENCEW_448              0x31C0
#define WM8996_WWITE_SEQUENCEW_449              0x31C1
#define WM8996_WWITE_SEQUENCEW_450              0x31C2
#define WM8996_WWITE_SEQUENCEW_451              0x31C3
#define WM8996_WWITE_SEQUENCEW_452              0x31C4
#define WM8996_WWITE_SEQUENCEW_453              0x31C5
#define WM8996_WWITE_SEQUENCEW_454              0x31C6
#define WM8996_WWITE_SEQUENCEW_455              0x31C7
#define WM8996_WWITE_SEQUENCEW_456              0x31C8
#define WM8996_WWITE_SEQUENCEW_457              0x31C9
#define WM8996_WWITE_SEQUENCEW_458              0x31CA
#define WM8996_WWITE_SEQUENCEW_459              0x31CB
#define WM8996_WWITE_SEQUENCEW_460              0x31CC
#define WM8996_WWITE_SEQUENCEW_461              0x31CD
#define WM8996_WWITE_SEQUENCEW_462              0x31CE
#define WM8996_WWITE_SEQUENCEW_463              0x31CF
#define WM8996_WWITE_SEQUENCEW_464              0x31D0
#define WM8996_WWITE_SEQUENCEW_465              0x31D1
#define WM8996_WWITE_SEQUENCEW_466              0x31D2
#define WM8996_WWITE_SEQUENCEW_467              0x31D3
#define WM8996_WWITE_SEQUENCEW_468              0x31D4
#define WM8996_WWITE_SEQUENCEW_469              0x31D5
#define WM8996_WWITE_SEQUENCEW_470              0x31D6
#define WM8996_WWITE_SEQUENCEW_471              0x31D7
#define WM8996_WWITE_SEQUENCEW_472              0x31D8
#define WM8996_WWITE_SEQUENCEW_473              0x31D9
#define WM8996_WWITE_SEQUENCEW_474              0x31DA
#define WM8996_WWITE_SEQUENCEW_475              0x31DB
#define WM8996_WWITE_SEQUENCEW_476              0x31DC
#define WM8996_WWITE_SEQUENCEW_477              0x31DD
#define WM8996_WWITE_SEQUENCEW_478              0x31DE
#define WM8996_WWITE_SEQUENCEW_479              0x31DF
#define WM8996_WWITE_SEQUENCEW_480              0x31E0
#define WM8996_WWITE_SEQUENCEW_481              0x31E1
#define WM8996_WWITE_SEQUENCEW_482              0x31E2
#define WM8996_WWITE_SEQUENCEW_483              0x31E3
#define WM8996_WWITE_SEQUENCEW_484              0x31E4
#define WM8996_WWITE_SEQUENCEW_485              0x31E5
#define WM8996_WWITE_SEQUENCEW_486              0x31E6
#define WM8996_WWITE_SEQUENCEW_487              0x31E7
#define WM8996_WWITE_SEQUENCEW_488              0x31E8
#define WM8996_WWITE_SEQUENCEW_489              0x31E9
#define WM8996_WWITE_SEQUENCEW_490              0x31EA
#define WM8996_WWITE_SEQUENCEW_491              0x31EB
#define WM8996_WWITE_SEQUENCEW_492              0x31EC
#define WM8996_WWITE_SEQUENCEW_493              0x31ED
#define WM8996_WWITE_SEQUENCEW_494              0x31EE
#define WM8996_WWITE_SEQUENCEW_495              0x31EF
#define WM8996_WWITE_SEQUENCEW_496              0x31F0
#define WM8996_WWITE_SEQUENCEW_497              0x31F1
#define WM8996_WWITE_SEQUENCEW_498              0x31F2
#define WM8996_WWITE_SEQUENCEW_499              0x31F3
#define WM8996_WWITE_SEQUENCEW_500              0x31F4
#define WM8996_WWITE_SEQUENCEW_501              0x31F5
#define WM8996_WWITE_SEQUENCEW_502              0x31F6
#define WM8996_WWITE_SEQUENCEW_503              0x31F7
#define WM8996_WWITE_SEQUENCEW_504              0x31F8
#define WM8996_WWITE_SEQUENCEW_505              0x31F9
#define WM8996_WWITE_SEQUENCEW_506              0x31FA
#define WM8996_WWITE_SEQUENCEW_507              0x31FB
#define WM8996_WWITE_SEQUENCEW_508              0x31FC
#define WM8996_WWITE_SEQUENCEW_509              0x31FD
#define WM8996_WWITE_SEQUENCEW_510              0x31FE
#define WM8996_WWITE_SEQUENCEW_511              0x31FF

#define WM8996_WEGISTEW_COUNT                   706
#define WM8996_MAX_WEGISTEW                     0x31FF

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Softwawe Weset
 */
#define WM8996_SW_WESET_MASK                    0xFFFF  /* SW_WESET - [15:0] */
#define WM8996_SW_WESET_SHIFT                        0  /* SW_WESET - [15:0] */
#define WM8996_SW_WESET_WIDTH                       16  /* SW_WESET - [15:0] */

/*
 * W1 (0x01) - Powew Management (1)
 */
#define WM8996_MICB2_ENA                        0x0200  /* MICB2_ENA */
#define WM8996_MICB2_ENA_MASK                   0x0200  /* MICB2_ENA */
#define WM8996_MICB2_ENA_SHIFT                       9  /* MICB2_ENA */
#define WM8996_MICB2_ENA_WIDTH                       1  /* MICB2_ENA */
#define WM8996_MICB1_ENA                        0x0100  /* MICB1_ENA */
#define WM8996_MICB1_ENA_MASK                   0x0100  /* MICB1_ENA */
#define WM8996_MICB1_ENA_SHIFT                       8  /* MICB1_ENA */
#define WM8996_MICB1_ENA_WIDTH                       1  /* MICB1_ENA */
#define WM8996_HPOUT2W_ENA                      0x0080  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_MASK                 0x0080  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_SHIFT                     7  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_WIDTH                     1  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA                      0x0040  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_MASK                 0x0040  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_SHIFT                     6  /* HPOUT2W_ENA */
#define WM8996_HPOUT2W_ENA_WIDTH                     1  /* HPOUT2W_ENA */
#define WM8996_HPOUT1W_ENA                      0x0020  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_MASK                 0x0020  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_SHIFT                     5  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_WIDTH                     1  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA                      0x0010  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_MASK                 0x0010  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_SHIFT                     4  /* HPOUT1W_ENA */
#define WM8996_HPOUT1W_ENA_WIDTH                     1  /* HPOUT1W_ENA */
#define WM8996_BG_ENA                           0x0001  /* BG_ENA */
#define WM8996_BG_ENA_MASK                      0x0001  /* BG_ENA */
#define WM8996_BG_ENA_SHIFT                          0  /* BG_ENA */
#define WM8996_BG_ENA_WIDTH                          1  /* BG_ENA */

/*
 * W2 (0x02) - Powew Management (2)
 */
#define WM8996_OPCWK_ENA                        0x0800  /* OPCWK_ENA */
#define WM8996_OPCWK_ENA_MASK                   0x0800  /* OPCWK_ENA */
#define WM8996_OPCWK_ENA_SHIFT                      11  /* OPCWK_ENA */
#define WM8996_OPCWK_ENA_WIDTH                       1  /* OPCWK_ENA */
#define WM8996_INW_ENA                          0x0020  /* INW_ENA */
#define WM8996_INW_ENA_MASK                     0x0020  /* INW_ENA */
#define WM8996_INW_ENA_SHIFT                         5  /* INW_ENA */
#define WM8996_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8996_INW_ENA                          0x0010  /* INW_ENA */
#define WM8996_INW_ENA_MASK                     0x0010  /* INW_ENA */
#define WM8996_INW_ENA_SHIFT                         4  /* INW_ENA */
#define WM8996_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8996_WDO2_ENA                         0x0002  /* WDO2_ENA */
#define WM8996_WDO2_ENA_MASK                    0x0002  /* WDO2_ENA */
#define WM8996_WDO2_ENA_SHIFT                        1  /* WDO2_ENA */
#define WM8996_WDO2_ENA_WIDTH                        1  /* WDO2_ENA */

/*
 * W3 (0x03) - Powew Management (3)
 */
#define WM8996_DSP2WXW_ENA                      0x0800  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_MASK                 0x0800  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_SHIFT                    11  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_WIDTH                     1  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA                      0x0400  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_MASK                 0x0400  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_SHIFT                    10  /* DSP2WXW_ENA */
#define WM8996_DSP2WXW_ENA_WIDTH                     1  /* DSP2WXW_ENA */
#define WM8996_DSP1WXW_ENA                      0x0200  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_MASK                 0x0200  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_SHIFT                     9  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_WIDTH                     1  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA                      0x0100  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_MASK                 0x0100  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_SHIFT                     8  /* DSP1WXW_ENA */
#define WM8996_DSP1WXW_ENA_WIDTH                     1  /* DSP1WXW_ENA */
#define WM8996_DMIC2W_ENA                       0x0020  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_MASK                  0x0020  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_SHIFT                      5  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_WIDTH                      1  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA                       0x0010  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_MASK                  0x0010  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_SHIFT                      4  /* DMIC2W_ENA */
#define WM8996_DMIC2W_ENA_WIDTH                      1  /* DMIC2W_ENA */
#define WM8996_DMIC1W_ENA                       0x0008  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_MASK                  0x0008  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_SHIFT                      3  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_WIDTH                      1  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA                       0x0004  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_MASK                  0x0004  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_SHIFT                      2  /* DMIC1W_ENA */
#define WM8996_DMIC1W_ENA_WIDTH                      1  /* DMIC1W_ENA */
#define WM8996_ADCW_ENA                         0x0002  /* ADCW_ENA */
#define WM8996_ADCW_ENA_MASK                    0x0002  /* ADCW_ENA */
#define WM8996_ADCW_ENA_SHIFT                        1  /* ADCW_ENA */
#define WM8996_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8996_ADCW_ENA                         0x0001  /* ADCW_ENA */
#define WM8996_ADCW_ENA_MASK                    0x0001  /* ADCW_ENA */
#define WM8996_ADCW_ENA_SHIFT                        0  /* ADCW_ENA */
#define WM8996_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */

/*
 * W4 (0x04) - Powew Management (4)
 */
#define WM8996_AIF2WX_CHAN1_ENA                 0x0200  /* AIF2WX_CHAN1_ENA */
#define WM8996_AIF2WX_CHAN1_ENA_MASK            0x0200  /* AIF2WX_CHAN1_ENA */
#define WM8996_AIF2WX_CHAN1_ENA_SHIFT                9  /* AIF2WX_CHAN1_ENA */
#define WM8996_AIF2WX_CHAN1_ENA_WIDTH                1  /* AIF2WX_CHAN1_ENA */
#define WM8996_AIF2WX_CHAN0_ENA                 0x0100  /* AIF2WX_CHAN0_ENA */
#define WM8996_AIF2WX_CHAN0_ENA_MASK            0x0100  /* AIF2WX_CHAN0_ENA */
#define WM8996_AIF2WX_CHAN0_ENA_SHIFT                8  /* AIF2WX_CHAN0_ENA */
#define WM8996_AIF2WX_CHAN0_ENA_WIDTH                1  /* AIF2WX_CHAN0_ENA */
#define WM8996_AIF1WX_CHAN5_ENA                 0x0020  /* AIF1WX_CHAN5_ENA */
#define WM8996_AIF1WX_CHAN5_ENA_MASK            0x0020  /* AIF1WX_CHAN5_ENA */
#define WM8996_AIF1WX_CHAN5_ENA_SHIFT                5  /* AIF1WX_CHAN5_ENA */
#define WM8996_AIF1WX_CHAN5_ENA_WIDTH                1  /* AIF1WX_CHAN5_ENA */
#define WM8996_AIF1WX_CHAN4_ENA                 0x0010  /* AIF1WX_CHAN4_ENA */
#define WM8996_AIF1WX_CHAN4_ENA_MASK            0x0010  /* AIF1WX_CHAN4_ENA */
#define WM8996_AIF1WX_CHAN4_ENA_SHIFT                4  /* AIF1WX_CHAN4_ENA */
#define WM8996_AIF1WX_CHAN4_ENA_WIDTH                1  /* AIF1WX_CHAN4_ENA */
#define WM8996_AIF1WX_CHAN3_ENA                 0x0008  /* AIF1WX_CHAN3_ENA */
#define WM8996_AIF1WX_CHAN3_ENA_MASK            0x0008  /* AIF1WX_CHAN3_ENA */
#define WM8996_AIF1WX_CHAN3_ENA_SHIFT                3  /* AIF1WX_CHAN3_ENA */
#define WM8996_AIF1WX_CHAN3_ENA_WIDTH                1  /* AIF1WX_CHAN3_ENA */
#define WM8996_AIF1WX_CHAN2_ENA                 0x0004  /* AIF1WX_CHAN2_ENA */
#define WM8996_AIF1WX_CHAN2_ENA_MASK            0x0004  /* AIF1WX_CHAN2_ENA */
#define WM8996_AIF1WX_CHAN2_ENA_SHIFT                2  /* AIF1WX_CHAN2_ENA */
#define WM8996_AIF1WX_CHAN2_ENA_WIDTH                1  /* AIF1WX_CHAN2_ENA */
#define WM8996_AIF1WX_CHAN1_ENA                 0x0002  /* AIF1WX_CHAN1_ENA */
#define WM8996_AIF1WX_CHAN1_ENA_MASK            0x0002  /* AIF1WX_CHAN1_ENA */
#define WM8996_AIF1WX_CHAN1_ENA_SHIFT                1  /* AIF1WX_CHAN1_ENA */
#define WM8996_AIF1WX_CHAN1_ENA_WIDTH                1  /* AIF1WX_CHAN1_ENA */
#define WM8996_AIF1WX_CHAN0_ENA                 0x0001  /* AIF1WX_CHAN0_ENA */
#define WM8996_AIF1WX_CHAN0_ENA_MASK            0x0001  /* AIF1WX_CHAN0_ENA */
#define WM8996_AIF1WX_CHAN0_ENA_SHIFT                0  /* AIF1WX_CHAN0_ENA */
#define WM8996_AIF1WX_CHAN0_ENA_WIDTH                1  /* AIF1WX_CHAN0_ENA */

/*
 * W5 (0x05) - Powew Management (5)
 */
#define WM8996_DSP2TXW_ENA                      0x0800  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_MASK                 0x0800  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_SHIFT                    11  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_WIDTH                     1  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA                      0x0400  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_MASK                 0x0400  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_SHIFT                    10  /* DSP2TXW_ENA */
#define WM8996_DSP2TXW_ENA_WIDTH                     1  /* DSP2TXW_ENA */
#define WM8996_DSP1TXW_ENA                      0x0200  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_MASK                 0x0200  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_SHIFT                     9  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_WIDTH                     1  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA                      0x0100  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_MASK                 0x0100  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_SHIFT                     8  /* DSP1TXW_ENA */
#define WM8996_DSP1TXW_ENA_WIDTH                     1  /* DSP1TXW_ENA */
#define WM8996_DAC2W_ENA                        0x0008  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_MASK                   0x0008  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_SHIFT                       3  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_WIDTH                       1  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA                        0x0004  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_MASK                   0x0004  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_SHIFT                       2  /* DAC2W_ENA */
#define WM8996_DAC2W_ENA_WIDTH                       1  /* DAC2W_ENA */
#define WM8996_DAC1W_ENA                        0x0002  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_MASK                   0x0002  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_SHIFT                       1  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_WIDTH                       1  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA                        0x0001  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_MASK                   0x0001  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_SHIFT                       0  /* DAC1W_ENA */
#define WM8996_DAC1W_ENA_WIDTH                       1  /* DAC1W_ENA */

/*
 * W6 (0x06) - Powew Management (6)
 */
#define WM8996_AIF2TX_CHAN1_ENA                 0x0200  /* AIF2TX_CHAN1_ENA */
#define WM8996_AIF2TX_CHAN1_ENA_MASK            0x0200  /* AIF2TX_CHAN1_ENA */
#define WM8996_AIF2TX_CHAN1_ENA_SHIFT                9  /* AIF2TX_CHAN1_ENA */
#define WM8996_AIF2TX_CHAN1_ENA_WIDTH                1  /* AIF2TX_CHAN1_ENA */
#define WM8996_AIF2TX_CHAN0_ENA                 0x0100  /* AIF2TX_CHAN0_ENA */
#define WM8996_AIF2TX_CHAN0_ENA_MASK            0x0100  /* AIF2TX_CHAN0_ENA */
#define WM8996_AIF2TX_CHAN0_ENA_SHIFT                8  /* AIF2TX_CHAN0_ENA */
#define WM8996_AIF2TX_CHAN0_ENA_WIDTH                1  /* AIF2TX_CHAN0_ENA */
#define WM8996_AIF1TX_CHAN5_ENA                 0x0020  /* AIF1TX_CHAN5_ENA */
#define WM8996_AIF1TX_CHAN5_ENA_MASK            0x0020  /* AIF1TX_CHAN5_ENA */
#define WM8996_AIF1TX_CHAN5_ENA_SHIFT                5  /* AIF1TX_CHAN5_ENA */
#define WM8996_AIF1TX_CHAN5_ENA_WIDTH                1  /* AIF1TX_CHAN5_ENA */
#define WM8996_AIF1TX_CHAN4_ENA                 0x0010  /* AIF1TX_CHAN4_ENA */
#define WM8996_AIF1TX_CHAN4_ENA_MASK            0x0010  /* AIF1TX_CHAN4_ENA */
#define WM8996_AIF1TX_CHAN4_ENA_SHIFT                4  /* AIF1TX_CHAN4_ENA */
#define WM8996_AIF1TX_CHAN4_ENA_WIDTH                1  /* AIF1TX_CHAN4_ENA */
#define WM8996_AIF1TX_CHAN3_ENA                 0x0008  /* AIF1TX_CHAN3_ENA */
#define WM8996_AIF1TX_CHAN3_ENA_MASK            0x0008  /* AIF1TX_CHAN3_ENA */
#define WM8996_AIF1TX_CHAN3_ENA_SHIFT                3  /* AIF1TX_CHAN3_ENA */
#define WM8996_AIF1TX_CHAN3_ENA_WIDTH                1  /* AIF1TX_CHAN3_ENA */
#define WM8996_AIF1TX_CHAN2_ENA                 0x0004  /* AIF1TX_CHAN2_ENA */
#define WM8996_AIF1TX_CHAN2_ENA_MASK            0x0004  /* AIF1TX_CHAN2_ENA */
#define WM8996_AIF1TX_CHAN2_ENA_SHIFT                2  /* AIF1TX_CHAN2_ENA */
#define WM8996_AIF1TX_CHAN2_ENA_WIDTH                1  /* AIF1TX_CHAN2_ENA */
#define WM8996_AIF1TX_CHAN1_ENA                 0x0002  /* AIF1TX_CHAN1_ENA */
#define WM8996_AIF1TX_CHAN1_ENA_MASK            0x0002  /* AIF1TX_CHAN1_ENA */
#define WM8996_AIF1TX_CHAN1_ENA_SHIFT                1  /* AIF1TX_CHAN1_ENA */
#define WM8996_AIF1TX_CHAN1_ENA_WIDTH                1  /* AIF1TX_CHAN1_ENA */
#define WM8996_AIF1TX_CHAN0_ENA                 0x0001  /* AIF1TX_CHAN0_ENA */
#define WM8996_AIF1TX_CHAN0_ENA_MASK            0x0001  /* AIF1TX_CHAN0_ENA */
#define WM8996_AIF1TX_CHAN0_ENA_SHIFT                0  /* AIF1TX_CHAN0_ENA */
#define WM8996_AIF1TX_CHAN0_ENA_WIDTH                1  /* AIF1TX_CHAN0_ENA */

/*
 * W7 (0x07) - Powew Management (7)
 */
#define WM8996_DMIC2_FN                         0x0200  /* DMIC2_FN */
#define WM8996_DMIC2_FN_MASK                    0x0200  /* DMIC2_FN */
#define WM8996_DMIC2_FN_SHIFT                        9  /* DMIC2_FN */
#define WM8996_DMIC2_FN_WIDTH                        1  /* DMIC2_FN */
#define WM8996_DMIC1_FN                         0x0100  /* DMIC1_FN */
#define WM8996_DMIC1_FN_MASK                    0x0100  /* DMIC1_FN */
#define WM8996_DMIC1_FN_SHIFT                        8  /* DMIC1_FN */
#define WM8996_DMIC1_FN_WIDTH                        1  /* DMIC1_FN */
#define WM8996_ADC_DMIC_DSP2W_ENA               0x0080  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_MASK          0x0080  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_SHIFT              7  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_WIDTH              1  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA               0x0040  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_MASK          0x0040  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_SHIFT              6  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_DSP2W_ENA_WIDTH              1  /* ADC_DMIC_DSP2W_ENA */
#define WM8996_ADC_DMIC_SWC2_MASK               0x0030  /* ADC_DMIC_SWC2 - [5:4] */
#define WM8996_ADC_DMIC_SWC2_SHIFT                   4  /* ADC_DMIC_SWC2 - [5:4] */
#define WM8996_ADC_DMIC_SWC2_WIDTH                   2  /* ADC_DMIC_SWC2 - [5:4] */
#define WM8996_ADC_DMIC_DSP1W_ENA               0x0008  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_MASK          0x0008  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_SHIFT              3  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_WIDTH              1  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA               0x0004  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_MASK          0x0004  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_SHIFT              2  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_DSP1W_ENA_WIDTH              1  /* ADC_DMIC_DSP1W_ENA */
#define WM8996_ADC_DMIC_SWC1_MASK               0x0003  /* ADC_DMIC_SWC1 - [1:0] */
#define WM8996_ADC_DMIC_SWC1_SHIFT                   0  /* ADC_DMIC_SWC1 - [1:0] */
#define WM8996_ADC_DMIC_SWC1_WIDTH                   2  /* ADC_DMIC_SWC1 - [1:0] */

/*
 * W8 (0x08) - Powew Management (8)
 */
#define WM8996_AIF2TX_SWC_MASK                  0x00C0  /* AIF2TX_SWC - [7:6] */
#define WM8996_AIF2TX_SWC_SHIFT                      6  /* AIF2TX_SWC - [7:6] */
#define WM8996_AIF2TX_SWC_WIDTH                      2  /* AIF2TX_SWC - [7:6] */
#define WM8996_DSP2WX_SWC                       0x0010  /* DSP2WX_SWC */
#define WM8996_DSP2WX_SWC_MASK                  0x0010  /* DSP2WX_SWC */
#define WM8996_DSP2WX_SWC_SHIFT                      4  /* DSP2WX_SWC */
#define WM8996_DSP2WX_SWC_WIDTH                      1  /* DSP2WX_SWC */
#define WM8996_DSP1WX_SWC                       0x0001  /* DSP1WX_SWC */
#define WM8996_DSP1WX_SWC_MASK                  0x0001  /* DSP1WX_SWC */
#define WM8996_DSP1WX_SWC_SHIFT                      0  /* DSP1WX_SWC */
#define WM8996_DSP1WX_SWC_WIDTH                      1  /* DSP1WX_SWC */

/*
 * W16 (0x10) - Weft Wine Input Vowume
 */
#define WM8996_IN1_VU                           0x0080  /* IN1_VU */
#define WM8996_IN1_VU_MASK                      0x0080  /* IN1_VU */
#define WM8996_IN1_VU_SHIFT                          7  /* IN1_VU */
#define WM8996_IN1_VU_WIDTH                          1  /* IN1_VU */
#define WM8996_IN1W_ZC                          0x0020  /* IN1W_ZC */
#define WM8996_IN1W_ZC_MASK                     0x0020  /* IN1W_ZC */
#define WM8996_IN1W_ZC_SHIFT                         5  /* IN1W_ZC */
#define WM8996_IN1W_ZC_WIDTH                         1  /* IN1W_ZC */
#define WM8996_IN1W_VOW_MASK                    0x001F  /* IN1W_VOW - [4:0] */
#define WM8996_IN1W_VOW_SHIFT                        0  /* IN1W_VOW - [4:0] */
#define WM8996_IN1W_VOW_WIDTH                        5  /* IN1W_VOW - [4:0] */

/*
 * W17 (0x11) - Wight Wine Input Vowume
 */
#define WM8996_IN1_VU                           0x0080  /* IN1_VU */
#define WM8996_IN1_VU_MASK                      0x0080  /* IN1_VU */
#define WM8996_IN1_VU_SHIFT                          7  /* IN1_VU */
#define WM8996_IN1_VU_WIDTH                          1  /* IN1_VU */
#define WM8996_IN1W_ZC                          0x0020  /* IN1W_ZC */
#define WM8996_IN1W_ZC_MASK                     0x0020  /* IN1W_ZC */
#define WM8996_IN1W_ZC_SHIFT                         5  /* IN1W_ZC */
#define WM8996_IN1W_ZC_WIDTH                         1  /* IN1W_ZC */
#define WM8996_IN1W_VOW_MASK                    0x001F  /* IN1W_VOW - [4:0] */
#define WM8996_IN1W_VOW_SHIFT                        0  /* IN1W_VOW - [4:0] */
#define WM8996_IN1W_VOW_WIDTH                        5  /* IN1W_VOW - [4:0] */

/*
 * W18 (0x12) - Wine Input Contwow
 */
#define WM8996_INW_MODE_MASK                    0x000C  /* INW_MODE - [3:2] */
#define WM8996_INW_MODE_SHIFT                        2  /* INW_MODE - [3:2] */
#define WM8996_INW_MODE_WIDTH                        2  /* INW_MODE - [3:2] */
#define WM8996_INW_MODE_MASK                    0x0003  /* INW_MODE - [1:0] */
#define WM8996_INW_MODE_SHIFT                        0  /* INW_MODE - [1:0] */
#define WM8996_INW_MODE_WIDTH                        2  /* INW_MODE - [1:0] */

/*
 * W21 (0x15) - DAC1 HPOUT1 Vowume
 */
#define WM8996_DAC1W_HPOUT1W_VOW_MASK           0x00F0  /* DAC1W_HPOUT1W_VOW - [7:4] */
#define WM8996_DAC1W_HPOUT1W_VOW_SHIFT               4  /* DAC1W_HPOUT1W_VOW - [7:4] */
#define WM8996_DAC1W_HPOUT1W_VOW_WIDTH               4  /* DAC1W_HPOUT1W_VOW - [7:4] */
#define WM8996_DAC1W_HPOUT1W_VOW_MASK           0x000F  /* DAC1W_HPOUT1W_VOW - [3:0] */
#define WM8996_DAC1W_HPOUT1W_VOW_SHIFT               0  /* DAC1W_HPOUT1W_VOW - [3:0] */
#define WM8996_DAC1W_HPOUT1W_VOW_WIDTH               4  /* DAC1W_HPOUT1W_VOW - [3:0] */

/*
 * W22 (0x16) - DAC2 HPOUT2 Vowume
 */
#define WM8996_DAC2W_HPOUT2W_VOW_MASK           0x00F0  /* DAC2W_HPOUT2W_VOW - [7:4] */
#define WM8996_DAC2W_HPOUT2W_VOW_SHIFT               4  /* DAC2W_HPOUT2W_VOW - [7:4] */
#define WM8996_DAC2W_HPOUT2W_VOW_WIDTH               4  /* DAC2W_HPOUT2W_VOW - [7:4] */
#define WM8996_DAC2W_HPOUT2W_VOW_MASK           0x000F  /* DAC2W_HPOUT2W_VOW - [3:0] */
#define WM8996_DAC2W_HPOUT2W_VOW_SHIFT               0  /* DAC2W_HPOUT2W_VOW - [3:0] */
#define WM8996_DAC2W_HPOUT2W_VOW_WIDTH               4  /* DAC2W_HPOUT2W_VOW - [3:0] */

/*
 * W24 (0x18) - DAC1 Weft Vowume
 */
#define WM8996_DAC1W_MUTE                       0x0200  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_MASK                  0x0200  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_SHIFT                      9  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_WIDTH                      1  /* DAC1W_MUTE */
#define WM8996_DAC1_VU                          0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_MASK                     0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_SHIFT                         8  /* DAC1_VU */
#define WM8996_DAC1_VU_WIDTH                         1  /* DAC1_VU */
#define WM8996_DAC1W_VOW_MASK                   0x00FF  /* DAC1W_VOW - [7:0] */
#define WM8996_DAC1W_VOW_SHIFT                       0  /* DAC1W_VOW - [7:0] */
#define WM8996_DAC1W_VOW_WIDTH                       8  /* DAC1W_VOW - [7:0] */

/*
 * W25 (0x19) - DAC1 Wight Vowume
 */
#define WM8996_DAC1W_MUTE                       0x0200  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_MASK                  0x0200  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_SHIFT                      9  /* DAC1W_MUTE */
#define WM8996_DAC1W_MUTE_WIDTH                      1  /* DAC1W_MUTE */
#define WM8996_DAC1_VU                          0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_MASK                     0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_SHIFT                         8  /* DAC1_VU */
#define WM8996_DAC1_VU_WIDTH                         1  /* DAC1_VU */
#define WM8996_DAC1W_VOW_MASK                   0x00FF  /* DAC1W_VOW - [7:0] */
#define WM8996_DAC1W_VOW_SHIFT                       0  /* DAC1W_VOW - [7:0] */
#define WM8996_DAC1W_VOW_WIDTH                       8  /* DAC1W_VOW - [7:0] */

/*
 * W26 (0x1A) - DAC2 Weft Vowume
 */
#define WM8996_DAC2W_MUTE                       0x0200  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_MASK                  0x0200  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_SHIFT                      9  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_WIDTH                      1  /* DAC2W_MUTE */
#define WM8996_DAC2_VU                          0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_MASK                     0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_SHIFT                         8  /* DAC2_VU */
#define WM8996_DAC2_VU_WIDTH                         1  /* DAC2_VU */
#define WM8996_DAC2W_VOW_MASK                   0x00FF  /* DAC2W_VOW - [7:0] */
#define WM8996_DAC2W_VOW_SHIFT                       0  /* DAC2W_VOW - [7:0] */
#define WM8996_DAC2W_VOW_WIDTH                       8  /* DAC2W_VOW - [7:0] */

/*
 * W27 (0x1B) - DAC2 Wight Vowume
 */
#define WM8996_DAC2W_MUTE                       0x0200  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_MASK                  0x0200  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_SHIFT                      9  /* DAC2W_MUTE */
#define WM8996_DAC2W_MUTE_WIDTH                      1  /* DAC2W_MUTE */
#define WM8996_DAC2_VU                          0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_MASK                     0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_SHIFT                         8  /* DAC2_VU */
#define WM8996_DAC2_VU_WIDTH                         1  /* DAC2_VU */
#define WM8996_DAC2W_VOW_MASK                   0x00FF  /* DAC2W_VOW - [7:0] */
#define WM8996_DAC2W_VOW_SHIFT                       0  /* DAC2W_VOW - [7:0] */
#define WM8996_DAC2W_VOW_WIDTH                       8  /* DAC2W_VOW - [7:0] */

/*
 * W28 (0x1C) - Output1 Weft Vowume
 */
#define WM8996_DAC1_VU                          0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_MASK                     0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_SHIFT                         8  /* DAC1_VU */
#define WM8996_DAC1_VU_WIDTH                         1  /* DAC1_VU */
#define WM8996_HPOUT1W_ZC                       0x0080  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_MASK                  0x0080  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_SHIFT                      7  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_WIDTH                      1  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_VOW_MASK                 0x000F  /* HPOUT1W_VOW - [3:0] */
#define WM8996_HPOUT1W_VOW_SHIFT                     0  /* HPOUT1W_VOW - [3:0] */
#define WM8996_HPOUT1W_VOW_WIDTH                     4  /* HPOUT1W_VOW - [3:0] */

/*
 * W29 (0x1D) - Output1 Wight Vowume
 */
#define WM8996_DAC1_VU                          0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_MASK                     0x0100  /* DAC1_VU */
#define WM8996_DAC1_VU_SHIFT                         8  /* DAC1_VU */
#define WM8996_DAC1_VU_WIDTH                         1  /* DAC1_VU */
#define WM8996_HPOUT1W_ZC                       0x0080  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_MASK                  0x0080  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_SHIFT                      7  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_ZC_WIDTH                      1  /* HPOUT1W_ZC */
#define WM8996_HPOUT1W_VOW_MASK                 0x000F  /* HPOUT1W_VOW - [3:0] */
#define WM8996_HPOUT1W_VOW_SHIFT                     0  /* HPOUT1W_VOW - [3:0] */
#define WM8996_HPOUT1W_VOW_WIDTH                     4  /* HPOUT1W_VOW - [3:0] */

/*
 * W30 (0x1E) - Output2 Weft Vowume
 */
#define WM8996_DAC2_VU                          0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_MASK                     0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_SHIFT                         8  /* DAC2_VU */
#define WM8996_DAC2_VU_WIDTH                         1  /* DAC2_VU */
#define WM8996_HPOUT2W_ZC                       0x0080  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_MASK                  0x0080  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_SHIFT                      7  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_WIDTH                      1  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_VOW_MASK                 0x000F  /* HPOUT2W_VOW - [3:0] */
#define WM8996_HPOUT2W_VOW_SHIFT                     0  /* HPOUT2W_VOW - [3:0] */
#define WM8996_HPOUT2W_VOW_WIDTH                     4  /* HPOUT2W_VOW - [3:0] */

/*
 * W31 (0x1F) - Output2 Wight Vowume
 */
#define WM8996_DAC2_VU                          0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_MASK                     0x0100  /* DAC2_VU */
#define WM8996_DAC2_VU_SHIFT                         8  /* DAC2_VU */
#define WM8996_DAC2_VU_WIDTH                         1  /* DAC2_VU */
#define WM8996_HPOUT2W_ZC                       0x0080  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_MASK                  0x0080  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_SHIFT                      7  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_ZC_WIDTH                      1  /* HPOUT2W_ZC */
#define WM8996_HPOUT2W_VOW_MASK                 0x000F  /* HPOUT2W_VOW - [3:0] */
#define WM8996_HPOUT2W_VOW_SHIFT                     0  /* HPOUT2W_VOW - [3:0] */
#define WM8996_HPOUT2W_VOW_WIDTH                     4  /* HPOUT2W_VOW - [3:0] */

/*
 * W32 (0x20) - MICBIAS (1)
 */
#define WM8996_MICB1_WATE                       0x0020  /* MICB1_WATE */
#define WM8996_MICB1_WATE_MASK                  0x0020  /* MICB1_WATE */
#define WM8996_MICB1_WATE_SHIFT                      5  /* MICB1_WATE */
#define WM8996_MICB1_WATE_WIDTH                      1  /* MICB1_WATE */
#define WM8996_MICB1_MODE                       0x0010  /* MICB1_MODE */
#define WM8996_MICB1_MODE_MASK                  0x0010  /* MICB1_MODE */
#define WM8996_MICB1_MODE_SHIFT                      4  /* MICB1_MODE */
#define WM8996_MICB1_MODE_WIDTH                      1  /* MICB1_MODE */
#define WM8996_MICB1_WVW_MASK                   0x000E  /* MICB1_WVW - [3:1] */
#define WM8996_MICB1_WVW_SHIFT                       1  /* MICB1_WVW - [3:1] */
#define WM8996_MICB1_WVW_WIDTH                       3  /* MICB1_WVW - [3:1] */
#define WM8996_MICB1_DISCH                      0x0001  /* MICB1_DISCH */
#define WM8996_MICB1_DISCH_MASK                 0x0001  /* MICB1_DISCH */
#define WM8996_MICB1_DISCH_SHIFT                     0  /* MICB1_DISCH */
#define WM8996_MICB1_DISCH_WIDTH                     1  /* MICB1_DISCH */

/*
 * W33 (0x21) - MICBIAS (2)
 */
#define WM8996_MICB2_WATE                       0x0020  /* MICB2_WATE */
#define WM8996_MICB2_WATE_MASK                  0x0020  /* MICB2_WATE */
#define WM8996_MICB2_WATE_SHIFT                      5  /* MICB2_WATE */
#define WM8996_MICB2_WATE_WIDTH                      1  /* MICB2_WATE */
#define WM8996_MICB2_MODE                       0x0010  /* MICB2_MODE */
#define WM8996_MICB2_MODE_MASK                  0x0010  /* MICB2_MODE */
#define WM8996_MICB2_MODE_SHIFT                      4  /* MICB2_MODE */
#define WM8996_MICB2_MODE_WIDTH                      1  /* MICB2_MODE */
#define WM8996_MICB2_WVW_MASK                   0x000E  /* MICB2_WVW - [3:1] */
#define WM8996_MICB2_WVW_SHIFT                       1  /* MICB2_WVW - [3:1] */
#define WM8996_MICB2_WVW_WIDTH                       3  /* MICB2_WVW - [3:1] */
#define WM8996_MICB2_DISCH                      0x0001  /* MICB2_DISCH */
#define WM8996_MICB2_DISCH_MASK                 0x0001  /* MICB2_DISCH */
#define WM8996_MICB2_DISCH_SHIFT                     0  /* MICB2_DISCH */
#define WM8996_MICB2_DISCH_WIDTH                     1  /* MICB2_DISCH */

/*
 * W40 (0x28) - WDO 1
 */
#define WM8996_WDO1_MODE                        0x0020  /* WDO1_MODE */
#define WM8996_WDO1_MODE_MASK                   0x0020  /* WDO1_MODE */
#define WM8996_WDO1_MODE_SHIFT                       5  /* WDO1_MODE */
#define WM8996_WDO1_MODE_WIDTH                       1  /* WDO1_MODE */
#define WM8996_WDO1_VSEW_MASK                   0x0006  /* WDO1_VSEW - [2:1] */
#define WM8996_WDO1_VSEW_SHIFT                       1  /* WDO1_VSEW - [2:1] */
#define WM8996_WDO1_VSEW_WIDTH                       2  /* WDO1_VSEW - [2:1] */
#define WM8996_WDO1_DISCH                       0x0001  /* WDO1_DISCH */
#define WM8996_WDO1_DISCH_MASK                  0x0001  /* WDO1_DISCH */
#define WM8996_WDO1_DISCH_SHIFT                      0  /* WDO1_DISCH */
#define WM8996_WDO1_DISCH_WIDTH                      1  /* WDO1_DISCH */

/*
 * W41 (0x29) - WDO 2
 */
#define WM8996_WDO2_MODE                        0x0020  /* WDO2_MODE */
#define WM8996_WDO2_MODE_MASK                   0x0020  /* WDO2_MODE */
#define WM8996_WDO2_MODE_SHIFT                       5  /* WDO2_MODE */
#define WM8996_WDO2_MODE_WIDTH                       1  /* WDO2_MODE */
#define WM8996_WDO2_VSEW_MASK                   0x001E  /* WDO2_VSEW - [4:1] */
#define WM8996_WDO2_VSEW_SHIFT                       1  /* WDO2_VSEW - [4:1] */
#define WM8996_WDO2_VSEW_WIDTH                       4  /* WDO2_VSEW - [4:1] */
#define WM8996_WDO2_DISCH                       0x0001  /* WDO2_DISCH */
#define WM8996_WDO2_DISCH_MASK                  0x0001  /* WDO2_DISCH */
#define WM8996_WDO2_DISCH_SHIFT                      0  /* WDO2_DISCH */
#define WM8996_WDO2_DISCH_WIDTH                      1  /* WDO2_DISCH */

/*
 * W48 (0x30) - Accessowy Detect Mode 1
 */
#define WM8996_JD_MODE_MASK                     0x0003  /* JD_MODE - [1:0] */
#define WM8996_JD_MODE_SHIFT                         0  /* JD_MODE - [1:0] */
#define WM8996_JD_MODE_WIDTH                         2  /* JD_MODE - [1:0] */

/*
 * W49 (0x31) - Accessowy Detect Mode 2
 */
#define WM8996_HPOUT1FB_SWC                     0x0004  /* HPOUT1FB_SWC */
#define WM8996_HPOUT1FB_SWC_MASK                0x0004  /* HPOUT1FB_SWC */
#define WM8996_HPOUT1FB_SWC_SHIFT                    2  /* HPOUT1FB_SWC */
#define WM8996_HPOUT1FB_SWC_WIDTH                    1  /* HPOUT1FB_SWC */
#define WM8996_MICD_SWC                         0x0002  /* MICD_SWC */
#define WM8996_MICD_SWC_MASK                    0x0002  /* MICD_SWC */
#define WM8996_MICD_SWC_SHIFT                        1  /* MICD_SWC */
#define WM8996_MICD_SWC_WIDTH                        1  /* MICD_SWC */
#define WM8996_MICD_BIAS_SWC                    0x0001  /* MICD_BIAS_SWC */
#define WM8996_MICD_BIAS_SWC_MASK               0x0001  /* MICD_BIAS_SWC */
#define WM8996_MICD_BIAS_SWC_SHIFT                   0  /* MICD_BIAS_SWC */
#define WM8996_MICD_BIAS_SWC_WIDTH                   1  /* MICD_BIAS_SWC */

/*
 * W52 (0x34) - Headphone Detect 1
 */
#define WM8996_HP_HOWDTIME_MASK                 0x00E0  /* HP_HOWDTIME - [7:5] */
#define WM8996_HP_HOWDTIME_SHIFT                     5  /* HP_HOWDTIME - [7:5] */
#define WM8996_HP_HOWDTIME_WIDTH                     3  /* HP_HOWDTIME - [7:5] */
#define WM8996_HP_CWK_DIV_MASK                  0x0018  /* HP_CWK_DIV - [4:3] */
#define WM8996_HP_CWK_DIV_SHIFT                      3  /* HP_CWK_DIV - [4:3] */
#define WM8996_HP_CWK_DIV_WIDTH                      2  /* HP_CWK_DIV - [4:3] */
#define WM8996_HP_STEP_SIZE                     0x0002  /* HP_STEP_SIZE */
#define WM8996_HP_STEP_SIZE_MASK                0x0002  /* HP_STEP_SIZE */
#define WM8996_HP_STEP_SIZE_SHIFT                    1  /* HP_STEP_SIZE */
#define WM8996_HP_STEP_SIZE_WIDTH                    1  /* HP_STEP_SIZE */
#define WM8996_HP_POWW                          0x0001  /* HP_POWW */
#define WM8996_HP_POWW_MASK                     0x0001  /* HP_POWW */
#define WM8996_HP_POWW_SHIFT                         0  /* HP_POWW */
#define WM8996_HP_POWW_WIDTH                         1  /* HP_POWW */

/*
 * W53 (0x35) - Headphone Detect 2
 */
#define WM8996_HP_DONE                          0x0080  /* HP_DONE */
#define WM8996_HP_DONE_MASK                     0x0080  /* HP_DONE */
#define WM8996_HP_DONE_SHIFT                         7  /* HP_DONE */
#define WM8996_HP_DONE_WIDTH                         1  /* HP_DONE */
#define WM8996_HP_WVW_MASK                      0x007F  /* HP_WVW - [6:0] */
#define WM8996_HP_WVW_SHIFT                          0  /* HP_WVW - [6:0] */
#define WM8996_HP_WVW_WIDTH                          7  /* HP_WVW - [6:0] */

/*
 * W56 (0x38) - Mic Detect 1
 */
#define WM8996_MICD_BIAS_STAWTTIME_MASK         0xF000  /* MICD_BIAS_STAWTTIME - [15:12] */
#define WM8996_MICD_BIAS_STAWTTIME_SHIFT            12  /* MICD_BIAS_STAWTTIME - [15:12] */
#define WM8996_MICD_BIAS_STAWTTIME_WIDTH             4  /* MICD_BIAS_STAWTTIME - [15:12] */
#define WM8996_MICD_WATE_MASK                   0x0F00  /* MICD_WATE - [11:8] */
#define WM8996_MICD_WATE_SHIFT                       8  /* MICD_WATE - [11:8] */
#define WM8996_MICD_WATE_WIDTH                       4  /* MICD_WATE - [11:8] */
#define WM8996_MICD_DBTIME                      0x0002  /* MICD_DBTIME */
#define WM8996_MICD_DBTIME_MASK                 0x0002  /* MICD_DBTIME */
#define WM8996_MICD_DBTIME_SHIFT                     1  /* MICD_DBTIME */
#define WM8996_MICD_DBTIME_WIDTH                     1  /* MICD_DBTIME */
#define WM8996_MICD_ENA                         0x0001  /* MICD_ENA */
#define WM8996_MICD_ENA_MASK                    0x0001  /* MICD_ENA */
#define WM8996_MICD_ENA_SHIFT                        0  /* MICD_ENA */
#define WM8996_MICD_ENA_WIDTH                        1  /* MICD_ENA */

/*
 * W57 (0x39) - Mic Detect 2
 */
#define WM8996_MICD_WVW_SEW_MASK                0x00FF  /* MICD_WVW_SEW - [7:0] */
#define WM8996_MICD_WVW_SEW_SHIFT                    0  /* MICD_WVW_SEW - [7:0] */
#define WM8996_MICD_WVW_SEW_WIDTH                    8  /* MICD_WVW_SEW - [7:0] */

/*
 * W58 (0x3A) - Mic Detect 3
 */
#define WM8996_MICD_WVW_MASK                    0x07FC  /* MICD_WVW - [10:2] */
#define WM8996_MICD_WVW_SHIFT                        2  /* MICD_WVW - [10:2] */
#define WM8996_MICD_WVW_WIDTH                        9  /* MICD_WVW - [10:2] */
#define WM8996_MICD_VAWID                       0x0002  /* MICD_VAWID */
#define WM8996_MICD_VAWID_MASK                  0x0002  /* MICD_VAWID */
#define WM8996_MICD_VAWID_SHIFT                      1  /* MICD_VAWID */
#define WM8996_MICD_VAWID_WIDTH                      1  /* MICD_VAWID */
#define WM8996_MICD_STS                         0x0001  /* MICD_STS */
#define WM8996_MICD_STS_MASK                    0x0001  /* MICD_STS */
#define WM8996_MICD_STS_SHIFT                        0  /* MICD_STS */
#define WM8996_MICD_STS_WIDTH                        1  /* MICD_STS */

/*
 * W64 (0x40) - Chawge Pump (1)
 */
#define WM8996_CP_ENA                           0x8000  /* CP_ENA */
#define WM8996_CP_ENA_MASK                      0x8000  /* CP_ENA */
#define WM8996_CP_ENA_SHIFT                         15  /* CP_ENA */
#define WM8996_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W65 (0x41) - Chawge Pump (2)
 */
#define WM8996_CP_DISCH                         0x8000  /* CP_DISCH */
#define WM8996_CP_DISCH_MASK                    0x8000  /* CP_DISCH */
#define WM8996_CP_DISCH_SHIFT                       15  /* CP_DISCH */
#define WM8996_CP_DISCH_WIDTH                        1  /* CP_DISCH */

/*
 * W80 (0x50) - DC Sewvo (1)
 */
#define WM8996_DCS_ENA_CHAN_3                   0x0008  /* DCS_ENA_CHAN_3 */
#define WM8996_DCS_ENA_CHAN_3_MASK              0x0008  /* DCS_ENA_CHAN_3 */
#define WM8996_DCS_ENA_CHAN_3_SHIFT                  3  /* DCS_ENA_CHAN_3 */
#define WM8996_DCS_ENA_CHAN_3_WIDTH                  1  /* DCS_ENA_CHAN_3 */
#define WM8996_DCS_ENA_CHAN_2                   0x0004  /* DCS_ENA_CHAN_2 */
#define WM8996_DCS_ENA_CHAN_2_MASK              0x0004  /* DCS_ENA_CHAN_2 */
#define WM8996_DCS_ENA_CHAN_2_SHIFT                  2  /* DCS_ENA_CHAN_2 */
#define WM8996_DCS_ENA_CHAN_2_WIDTH                  1  /* DCS_ENA_CHAN_2 */
#define WM8996_DCS_ENA_CHAN_1                   0x0002  /* DCS_ENA_CHAN_1 */
#define WM8996_DCS_ENA_CHAN_1_MASK              0x0002  /* DCS_ENA_CHAN_1 */
#define WM8996_DCS_ENA_CHAN_1_SHIFT                  1  /* DCS_ENA_CHAN_1 */
#define WM8996_DCS_ENA_CHAN_1_WIDTH                  1  /* DCS_ENA_CHAN_1 */
#define WM8996_DCS_ENA_CHAN_0                   0x0001  /* DCS_ENA_CHAN_0 */
#define WM8996_DCS_ENA_CHAN_0_MASK              0x0001  /* DCS_ENA_CHAN_0 */
#define WM8996_DCS_ENA_CHAN_0_SHIFT                  0  /* DCS_ENA_CHAN_0 */
#define WM8996_DCS_ENA_CHAN_0_WIDTH                  1  /* DCS_ENA_CHAN_0 */

/*
 * W81 (0x51) - DC Sewvo (2)
 */
#define WM8996_DCS_TWIG_SINGWE_3                0x8000  /* DCS_TWIG_SINGWE_3 */
#define WM8996_DCS_TWIG_SINGWE_3_MASK           0x8000  /* DCS_TWIG_SINGWE_3 */
#define WM8996_DCS_TWIG_SINGWE_3_SHIFT              15  /* DCS_TWIG_SINGWE_3 */
#define WM8996_DCS_TWIG_SINGWE_3_WIDTH               1  /* DCS_TWIG_SINGWE_3 */
#define WM8996_DCS_TWIG_SINGWE_2                0x4000  /* DCS_TWIG_SINGWE_2 */
#define WM8996_DCS_TWIG_SINGWE_2_MASK           0x4000  /* DCS_TWIG_SINGWE_2 */
#define WM8996_DCS_TWIG_SINGWE_2_SHIFT              14  /* DCS_TWIG_SINGWE_2 */
#define WM8996_DCS_TWIG_SINGWE_2_WIDTH               1  /* DCS_TWIG_SINGWE_2 */
#define WM8996_DCS_TWIG_SINGWE_1                0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM8996_DCS_TWIG_SINGWE_1_MASK           0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM8996_DCS_TWIG_SINGWE_1_SHIFT              13  /* DCS_TWIG_SINGWE_1 */
#define WM8996_DCS_TWIG_SINGWE_1_WIDTH               1  /* DCS_TWIG_SINGWE_1 */
#define WM8996_DCS_TWIG_SINGWE_0                0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM8996_DCS_TWIG_SINGWE_0_MASK           0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM8996_DCS_TWIG_SINGWE_0_SHIFT              12  /* DCS_TWIG_SINGWE_0 */
#define WM8996_DCS_TWIG_SINGWE_0_WIDTH               1  /* DCS_TWIG_SINGWE_0 */
#define WM8996_DCS_TWIG_SEWIES_3                0x0800  /* DCS_TWIG_SEWIES_3 */
#define WM8996_DCS_TWIG_SEWIES_3_MASK           0x0800  /* DCS_TWIG_SEWIES_3 */
#define WM8996_DCS_TWIG_SEWIES_3_SHIFT              11  /* DCS_TWIG_SEWIES_3 */
#define WM8996_DCS_TWIG_SEWIES_3_WIDTH               1  /* DCS_TWIG_SEWIES_3 */
#define WM8996_DCS_TWIG_SEWIES_2                0x0400  /* DCS_TWIG_SEWIES_2 */
#define WM8996_DCS_TWIG_SEWIES_2_MASK           0x0400  /* DCS_TWIG_SEWIES_2 */
#define WM8996_DCS_TWIG_SEWIES_2_SHIFT              10  /* DCS_TWIG_SEWIES_2 */
#define WM8996_DCS_TWIG_SEWIES_2_WIDTH               1  /* DCS_TWIG_SEWIES_2 */
#define WM8996_DCS_TWIG_SEWIES_1                0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM8996_DCS_TWIG_SEWIES_1_MASK           0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM8996_DCS_TWIG_SEWIES_1_SHIFT               9  /* DCS_TWIG_SEWIES_1 */
#define WM8996_DCS_TWIG_SEWIES_1_WIDTH               1  /* DCS_TWIG_SEWIES_1 */
#define WM8996_DCS_TWIG_SEWIES_0                0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM8996_DCS_TWIG_SEWIES_0_MASK           0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM8996_DCS_TWIG_SEWIES_0_SHIFT               8  /* DCS_TWIG_SEWIES_0 */
#define WM8996_DCS_TWIG_SEWIES_0_WIDTH               1  /* DCS_TWIG_SEWIES_0 */
#define WM8996_DCS_TWIG_STAWTUP_3               0x0080  /* DCS_TWIG_STAWTUP_3 */
#define WM8996_DCS_TWIG_STAWTUP_3_MASK          0x0080  /* DCS_TWIG_STAWTUP_3 */
#define WM8996_DCS_TWIG_STAWTUP_3_SHIFT              7  /* DCS_TWIG_STAWTUP_3 */
#define WM8996_DCS_TWIG_STAWTUP_3_WIDTH              1  /* DCS_TWIG_STAWTUP_3 */
#define WM8996_DCS_TWIG_STAWTUP_2               0x0040  /* DCS_TWIG_STAWTUP_2 */
#define WM8996_DCS_TWIG_STAWTUP_2_MASK          0x0040  /* DCS_TWIG_STAWTUP_2 */
#define WM8996_DCS_TWIG_STAWTUP_2_SHIFT              6  /* DCS_TWIG_STAWTUP_2 */
#define WM8996_DCS_TWIG_STAWTUP_2_WIDTH              1  /* DCS_TWIG_STAWTUP_2 */
#define WM8996_DCS_TWIG_STAWTUP_1               0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM8996_DCS_TWIG_STAWTUP_1_MASK          0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM8996_DCS_TWIG_STAWTUP_1_SHIFT              5  /* DCS_TWIG_STAWTUP_1 */
#define WM8996_DCS_TWIG_STAWTUP_1_WIDTH              1  /* DCS_TWIG_STAWTUP_1 */
#define WM8996_DCS_TWIG_STAWTUP_0               0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM8996_DCS_TWIG_STAWTUP_0_MASK          0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM8996_DCS_TWIG_STAWTUP_0_SHIFT              4  /* DCS_TWIG_STAWTUP_0 */
#define WM8996_DCS_TWIG_STAWTUP_0_WIDTH              1  /* DCS_TWIG_STAWTUP_0 */
#define WM8996_DCS_TWIG_DAC_WW_3                0x0008  /* DCS_TWIG_DAC_WW_3 */
#define WM8996_DCS_TWIG_DAC_WW_3_MASK           0x0008  /* DCS_TWIG_DAC_WW_3 */
#define WM8996_DCS_TWIG_DAC_WW_3_SHIFT               3  /* DCS_TWIG_DAC_WW_3 */
#define WM8996_DCS_TWIG_DAC_WW_3_WIDTH               1  /* DCS_TWIG_DAC_WW_3 */
#define WM8996_DCS_TWIG_DAC_WW_2                0x0004  /* DCS_TWIG_DAC_WW_2 */
#define WM8996_DCS_TWIG_DAC_WW_2_MASK           0x0004  /* DCS_TWIG_DAC_WW_2 */
#define WM8996_DCS_TWIG_DAC_WW_2_SHIFT               2  /* DCS_TWIG_DAC_WW_2 */
#define WM8996_DCS_TWIG_DAC_WW_2_WIDTH               1  /* DCS_TWIG_DAC_WW_2 */
#define WM8996_DCS_TWIG_DAC_WW_1                0x0002  /* DCS_TWIG_DAC_WW_1 */
#define WM8996_DCS_TWIG_DAC_WW_1_MASK           0x0002  /* DCS_TWIG_DAC_WW_1 */
#define WM8996_DCS_TWIG_DAC_WW_1_SHIFT               1  /* DCS_TWIG_DAC_WW_1 */
#define WM8996_DCS_TWIG_DAC_WW_1_WIDTH               1  /* DCS_TWIG_DAC_WW_1 */
#define WM8996_DCS_TWIG_DAC_WW_0                0x0001  /* DCS_TWIG_DAC_WW_0 */
#define WM8996_DCS_TWIG_DAC_WW_0_MASK           0x0001  /* DCS_TWIG_DAC_WW_0 */
#define WM8996_DCS_TWIG_DAC_WW_0_SHIFT               0  /* DCS_TWIG_DAC_WW_0 */
#define WM8996_DCS_TWIG_DAC_WW_0_WIDTH               1  /* DCS_TWIG_DAC_WW_0 */

/*
 * W82 (0x52) - DC Sewvo (3)
 */
#define WM8996_DCS_TIMEW_PEWIOD_23_MASK         0x0F00  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8996_DCS_TIMEW_PEWIOD_23_SHIFT             8  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8996_DCS_TIMEW_PEWIOD_23_WIDTH             4  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8996_DCS_TIMEW_PEWIOD_01_MASK         0x000F  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM8996_DCS_TIMEW_PEWIOD_01_SHIFT             0  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM8996_DCS_TIMEW_PEWIOD_01_WIDTH             4  /* DCS_TIMEW_PEWIOD_01 - [3:0] */

/*
 * W84 (0x54) - DC Sewvo (5)
 */
#define WM8996_DCS_SEWIES_NO_23_MASK            0x7F00  /* DCS_SEWIES_NO_23 - [14:8] */
#define WM8996_DCS_SEWIES_NO_23_SHIFT                8  /* DCS_SEWIES_NO_23 - [14:8] */
#define WM8996_DCS_SEWIES_NO_23_WIDTH                7  /* DCS_SEWIES_NO_23 - [14:8] */
#define WM8996_DCS_SEWIES_NO_01_MASK            0x007F  /* DCS_SEWIES_NO_01 - [6:0] */
#define WM8996_DCS_SEWIES_NO_01_SHIFT                0  /* DCS_SEWIES_NO_01 - [6:0] */
#define WM8996_DCS_SEWIES_NO_01_WIDTH                7  /* DCS_SEWIES_NO_01 - [6:0] */

/*
 * W85 (0x55) - DC Sewvo (6)
 */
#define WM8996_DCS_DAC_WW_VAW_3_MASK            0xFF00  /* DCS_DAC_WW_VAW_3 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_3_SHIFT                8  /* DCS_DAC_WW_VAW_3 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_3_WIDTH                8  /* DCS_DAC_WW_VAW_3 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_2_MASK            0x00FF  /* DCS_DAC_WW_VAW_2 - [7:0] */
#define WM8996_DCS_DAC_WW_VAW_2_SHIFT                0  /* DCS_DAC_WW_VAW_2 - [7:0] */
#define WM8996_DCS_DAC_WW_VAW_2_WIDTH                8  /* DCS_DAC_WW_VAW_2 - [7:0] */

/*
 * W86 (0x56) - DC Sewvo (7)
 */
#define WM8996_DCS_DAC_WW_VAW_1_MASK            0xFF00  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_1_SHIFT                8  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_1_WIDTH                8  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM8996_DCS_DAC_WW_VAW_0_MASK            0x00FF  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM8996_DCS_DAC_WW_VAW_0_SHIFT                0  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM8996_DCS_DAC_WW_VAW_0_WIDTH                8  /* DCS_DAC_WW_VAW_0 - [7:0] */

/*
 * W87 (0x57) - DC Sewvo Weadback 0
 */
#define WM8996_DCS_CAW_COMPWETE_MASK            0x0F00  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8996_DCS_CAW_COMPWETE_SHIFT                8  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8996_DCS_CAW_COMPWETE_WIDTH                4  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8996_DCS_DAC_WW_COMPWETE_MASK         0x00F0  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8996_DCS_DAC_WW_COMPWETE_SHIFT             4  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8996_DCS_DAC_WW_COMPWETE_WIDTH             4  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8996_DCS_STAWTUP_COMPWETE_MASK        0x000F  /* DCS_STAWTUP_COMPWETE - [3:0] */
#define WM8996_DCS_STAWTUP_COMPWETE_SHIFT            0  /* DCS_STAWTUP_COMPWETE - [3:0] */
#define WM8996_DCS_STAWTUP_COMPWETE_WIDTH            4  /* DCS_STAWTUP_COMPWETE - [3:0] */

/*
 * W96 (0x60) - Anawogue HP (1)
 */
#define WM8996_HPOUT1W_WMV_SHOWT                0x0080  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_MASK           0x0080  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_SHIFT               7  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_WIDTH               1  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_OUTP                     0x0040  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_MASK                0x0040  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_SHIFT                    6  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_WIDTH                    1  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_DWY                      0x0020  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_MASK                 0x0020  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_SHIFT                     5  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_WIDTH                     1  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_WMV_SHOWT                0x0008  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_MASK           0x0008  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_SHIFT               3  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_WMV_SHOWT_WIDTH               1  /* HPOUT1W_WMV_SHOWT */
#define WM8996_HPOUT1W_OUTP                     0x0004  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_MASK                0x0004  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_SHIFT                    2  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_OUTP_WIDTH                    1  /* HPOUT1W_OUTP */
#define WM8996_HPOUT1W_DWY                      0x0002  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_MASK                 0x0002  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_SHIFT                     1  /* HPOUT1W_DWY */
#define WM8996_HPOUT1W_DWY_WIDTH                     1  /* HPOUT1W_DWY */

/*
 * W97 (0x61) - Anawogue HP (2)
 */
#define WM8996_HPOUT2W_WMV_SHOWT                0x0080  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_MASK           0x0080  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_SHIFT               7  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_WIDTH               1  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_OUTP                     0x0040  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_MASK                0x0040  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_SHIFT                    6  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_WIDTH                    1  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_DWY                      0x0020  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_MASK                 0x0020  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_SHIFT                     5  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_WIDTH                     1  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_WMV_SHOWT                0x0008  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_MASK           0x0008  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_SHIFT               3  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_WMV_SHOWT_WIDTH               1  /* HPOUT2W_WMV_SHOWT */
#define WM8996_HPOUT2W_OUTP                     0x0004  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_MASK                0x0004  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_SHIFT                    2  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_OUTP_WIDTH                    1  /* HPOUT2W_OUTP */
#define WM8996_HPOUT2W_DWY                      0x0002  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_MASK                 0x0002  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_SHIFT                     1  /* HPOUT2W_DWY */
#define WM8996_HPOUT2W_DWY_WIDTH                     1  /* HPOUT2W_DWY */

/*
 * W256 (0x100) - Chip Wevision
 */
#define WM8996_CHIP_WEV_MASK                    0x000F  /* CHIP_WEV - [3:0] */
#define WM8996_CHIP_WEV_SHIFT                        0  /* CHIP_WEV - [3:0] */
#define WM8996_CHIP_WEV_WIDTH                        4  /* CHIP_WEV - [3:0] */

/*
 * W257 (0x101) - Contwow Intewface (1)
 */
#define WM8996_WEG_SYNC                         0x8000  /* WEG_SYNC */
#define WM8996_WEG_SYNC_MASK                    0x8000  /* WEG_SYNC */
#define WM8996_WEG_SYNC_SHIFT                       15  /* WEG_SYNC */
#define WM8996_WEG_SYNC_WIDTH                        1  /* WEG_SYNC */
#define WM8996_AUTO_INC                         0x0004  /* AUTO_INC */
#define WM8996_AUTO_INC_MASK                    0x0004  /* AUTO_INC */
#define WM8996_AUTO_INC_SHIFT                        2  /* AUTO_INC */
#define WM8996_AUTO_INC_WIDTH                        1  /* AUTO_INC */

/*
 * W272 (0x110) - Wwite Sequencew Ctww (1)
 */
#define WM8996_WSEQ_ENA                         0x8000  /* WSEQ_ENA */
#define WM8996_WSEQ_ENA_MASK                    0x8000  /* WSEQ_ENA */
#define WM8996_WSEQ_ENA_SHIFT                       15  /* WSEQ_ENA */
#define WM8996_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM8996_WSEQ_ABOWT                       0x0200  /* WSEQ_ABOWT */
#define WM8996_WSEQ_ABOWT_MASK                  0x0200  /* WSEQ_ABOWT */
#define WM8996_WSEQ_ABOWT_SHIFT                      9  /* WSEQ_ABOWT */
#define WM8996_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM8996_WSEQ_STAWT                       0x0100  /* WSEQ_STAWT */
#define WM8996_WSEQ_STAWT_MASK                  0x0100  /* WSEQ_STAWT */
#define WM8996_WSEQ_STAWT_SHIFT                      8  /* WSEQ_STAWT */
#define WM8996_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM8996_WSEQ_STAWT_INDEX_MASK            0x007F  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM8996_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM8996_WSEQ_STAWT_INDEX_WIDTH                7  /* WSEQ_STAWT_INDEX - [6:0] */

/*
 * W273 (0x111) - Wwite Sequencew Ctww (2)
 */
#define WM8996_WSEQ_BUSY                        0x0100  /* WSEQ_BUSY */
#define WM8996_WSEQ_BUSY_MASK                   0x0100  /* WSEQ_BUSY */
#define WM8996_WSEQ_BUSY_SHIFT                       8  /* WSEQ_BUSY */
#define WM8996_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */
#define WM8996_WSEQ_CUWWENT_INDEX_MASK          0x007F  /* WSEQ_CUWWENT_INDEX - [6:0] */
#define WM8996_WSEQ_CUWWENT_INDEX_SHIFT              0  /* WSEQ_CUWWENT_INDEX - [6:0] */
#define WM8996_WSEQ_CUWWENT_INDEX_WIDTH              7  /* WSEQ_CUWWENT_INDEX - [6:0] */

/*
 * W512 (0x200) - AIF Cwocking (1)
 */
#define WM8996_SYSCWK_SWC_MASK                  0x0018  /* SYSCWK_SWC - [4:3] */
#define WM8996_SYSCWK_SWC_SHIFT                      3  /* SYSCWK_SWC - [4:3] */
#define WM8996_SYSCWK_SWC_WIDTH                      2  /* SYSCWK_SWC - [4:3] */
#define WM8996_SYSCWK_INV                       0x0004  /* SYSCWK_INV */
#define WM8996_SYSCWK_INV_MASK                  0x0004  /* SYSCWK_INV */
#define WM8996_SYSCWK_INV_SHIFT                      2  /* SYSCWK_INV */
#define WM8996_SYSCWK_INV_WIDTH                      1  /* SYSCWK_INV */
#define WM8996_SYSCWK_DIV                       0x0002  /* SYSCWK_DIV */
#define WM8996_SYSCWK_DIV_MASK                  0x0002  /* SYSCWK_DIV */
#define WM8996_SYSCWK_DIV_SHIFT                      1  /* SYSCWK_DIV */
#define WM8996_SYSCWK_DIV_WIDTH                      1  /* SYSCWK_DIV */
#define WM8996_SYSCWK_ENA                       0x0001  /* SYSCWK_ENA */
#define WM8996_SYSCWK_ENA_MASK                  0x0001  /* SYSCWK_ENA */
#define WM8996_SYSCWK_ENA_SHIFT                      0  /* SYSCWK_ENA */
#define WM8996_SYSCWK_ENA_WIDTH                      1  /* SYSCWK_ENA */

/*
 * W513 (0x201) - AIF Cwocking (2)
 */
#define WM8996_DSP2_DIV_MASK                    0x0018  /* DSP2_DIV - [4:3] */
#define WM8996_DSP2_DIV_SHIFT                        3  /* DSP2_DIV - [4:3] */
#define WM8996_DSP2_DIV_WIDTH                        2  /* DSP2_DIV - [4:3] */
#define WM8996_DSP1_DIV_MASK                    0x0003  /* DSP1_DIV - [1:0] */
#define WM8996_DSP1_DIV_SHIFT                        0  /* DSP1_DIV - [1:0] */
#define WM8996_DSP1_DIV_WIDTH                        2  /* DSP1_DIV - [1:0] */

/*
 * W520 (0x208) - Cwocking (1)
 */
#define WM8996_WFCWK_ENA                        0x0020  /* WFCWK_ENA */
#define WM8996_WFCWK_ENA_MASK                   0x0020  /* WFCWK_ENA */
#define WM8996_WFCWK_ENA_SHIFT                       5  /* WFCWK_ENA */
#define WM8996_WFCWK_ENA_WIDTH                       1  /* WFCWK_ENA */
#define WM8996_TOCWK_ENA                        0x0010  /* TOCWK_ENA */
#define WM8996_TOCWK_ENA_MASK                   0x0010  /* TOCWK_ENA */
#define WM8996_TOCWK_ENA_SHIFT                       4  /* TOCWK_ENA */
#define WM8996_TOCWK_ENA_WIDTH                       1  /* TOCWK_ENA */
#define WM8996_AIFCWK_ENA                       0x0004  /* AIFCWK_ENA */
#define WM8996_AIFCWK_ENA_MASK                  0x0004  /* AIFCWK_ENA */
#define WM8996_AIFCWK_ENA_SHIFT                      2  /* AIFCWK_ENA */
#define WM8996_AIFCWK_ENA_WIDTH                      1  /* AIFCWK_ENA */
#define WM8996_SYSDSPCWK_ENA                    0x0002  /* SYSDSPCWK_ENA */
#define WM8996_SYSDSPCWK_ENA_MASK               0x0002  /* SYSDSPCWK_ENA */
#define WM8996_SYSDSPCWK_ENA_SHIFT                   1  /* SYSDSPCWK_ENA */
#define WM8996_SYSDSPCWK_ENA_WIDTH                   1  /* SYSDSPCWK_ENA */

/*
 * W521 (0x209) - Cwocking (2)
 */
#define WM8996_TOCWK_DIV_MASK                   0x0700  /* TOCWK_DIV - [10:8] */
#define WM8996_TOCWK_DIV_SHIFT                       8  /* TOCWK_DIV - [10:8] */
#define WM8996_TOCWK_DIV_WIDTH                       3  /* TOCWK_DIV - [10:8] */
#define WM8996_DBCWK_DIV_MASK                   0x00F0  /* DBCWK_DIV - [7:4] */
#define WM8996_DBCWK_DIV_SHIFT                       4  /* DBCWK_DIV - [7:4] */
#define WM8996_DBCWK_DIV_WIDTH                       4  /* DBCWK_DIV - [7:4] */
#define WM8996_OPCWK_DIV_MASK                   0x0007  /* OPCWK_DIV - [2:0] */
#define WM8996_OPCWK_DIV_SHIFT                       0  /* OPCWK_DIV - [2:0] */
#define WM8996_OPCWK_DIV_WIDTH                       3  /* OPCWK_DIV - [2:0] */

/*
 * W528 (0x210) - AIF Wate
 */
#define WM8996_SYSCWK_WATE                      0x0001  /* SYSCWK_WATE */
#define WM8996_SYSCWK_WATE_MASK                 0x0001  /* SYSCWK_WATE */
#define WM8996_SYSCWK_WATE_SHIFT                     0  /* SYSCWK_WATE */
#define WM8996_SYSCWK_WATE_WIDTH                     1  /* SYSCWK_WATE */

/*
 * W544 (0x220) - FWW Contwow (1)
 */
#define WM8996_FWW_OSC_ENA                      0x0002  /* FWW_OSC_ENA */
#define WM8996_FWW_OSC_ENA_MASK                 0x0002  /* FWW_OSC_ENA */
#define WM8996_FWW_OSC_ENA_SHIFT                     1  /* FWW_OSC_ENA */
#define WM8996_FWW_OSC_ENA_WIDTH                     1  /* FWW_OSC_ENA */
#define WM8996_FWW_ENA                          0x0001  /* FWW_ENA */
#define WM8996_FWW_ENA_MASK                     0x0001  /* FWW_ENA */
#define WM8996_FWW_ENA_SHIFT                         0  /* FWW_ENA */
#define WM8996_FWW_ENA_WIDTH                         1  /* FWW_ENA */

/*
 * W545 (0x221) - FWW Contwow (2)
 */
#define WM8996_FWW_OUTDIV_MASK                  0x3F00  /* FWW_OUTDIV - [13:8] */
#define WM8996_FWW_OUTDIV_SHIFT                      8  /* FWW_OUTDIV - [13:8] */
#define WM8996_FWW_OUTDIV_WIDTH                      6  /* FWW_OUTDIV - [13:8] */
#define WM8996_FWW_FWATIO_MASK                  0x0007  /* FWW_FWATIO - [2:0] */
#define WM8996_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [2:0] */
#define WM8996_FWW_FWATIO_WIDTH                      3  /* FWW_FWATIO - [2:0] */

/*
 * W546 (0x222) - FWW Contwow (3)
 */
#define WM8996_FWW_THETA_MASK                   0xFFFF  /* FWW_THETA - [15:0] */
#define WM8996_FWW_THETA_SHIFT                       0  /* FWW_THETA - [15:0] */
#define WM8996_FWW_THETA_WIDTH                      16  /* FWW_THETA - [15:0] */

/*
 * W547 (0x223) - FWW Contwow (4)
 */
#define WM8996_FWW_N_MASK                       0x7FE0  /* FWW_N - [14:5] */
#define WM8996_FWW_N_SHIFT                           5  /* FWW_N - [14:5] */
#define WM8996_FWW_N_WIDTH                          10  /* FWW_N - [14:5] */
#define WM8996_FWW_WOOP_GAIN_MASK               0x000F  /* FWW_WOOP_GAIN - [3:0] */
#define WM8996_FWW_WOOP_GAIN_SHIFT                   0  /* FWW_WOOP_GAIN - [3:0] */
#define WM8996_FWW_WOOP_GAIN_WIDTH                   4  /* FWW_WOOP_GAIN - [3:0] */

/*
 * W548 (0x224) - FWW Contwow (5)
 */
#define WM8996_FWW_FWC_NCO_VAW_MASK             0x1F80  /* FWW_FWC_NCO_VAW - [12:7] */
#define WM8996_FWW_FWC_NCO_VAW_SHIFT                 7  /* FWW_FWC_NCO_VAW - [12:7] */
#define WM8996_FWW_FWC_NCO_VAW_WIDTH                 6  /* FWW_FWC_NCO_VAW - [12:7] */
#define WM8996_FWW_FWC_NCO                      0x0040  /* FWW_FWC_NCO */
#define WM8996_FWW_FWC_NCO_MASK                 0x0040  /* FWW_FWC_NCO */
#define WM8996_FWW_FWC_NCO_SHIFT                     6  /* FWW_FWC_NCO */
#define WM8996_FWW_FWC_NCO_WIDTH                     1  /* FWW_FWC_NCO */
#define WM8996_FWW_WEFCWK_DIV_MASK              0x0018  /* FWW_WEFCWK_DIV - [4:3] */
#define WM8996_FWW_WEFCWK_DIV_SHIFT                  3  /* FWW_WEFCWK_DIV - [4:3] */
#define WM8996_FWW_WEFCWK_DIV_WIDTH                  2  /* FWW_WEFCWK_DIV - [4:3] */
#define WM8996_FWW_WEF_FWEQ                     0x0004  /* FWW_WEF_FWEQ */
#define WM8996_FWW_WEF_FWEQ_MASK                0x0004  /* FWW_WEF_FWEQ */
#define WM8996_FWW_WEF_FWEQ_SHIFT                    2  /* FWW_WEF_FWEQ */
#define WM8996_FWW_WEF_FWEQ_WIDTH                    1  /* FWW_WEF_FWEQ */
#define WM8996_FWW_WEFCWK_SWC_MASK              0x0003  /* FWW_WEFCWK_SWC - [1:0] */
#define WM8996_FWW_WEFCWK_SWC_SHIFT                  0  /* FWW_WEFCWK_SWC - [1:0] */
#define WM8996_FWW_WEFCWK_SWC_WIDTH                  2  /* FWW_WEFCWK_SWC - [1:0] */

/*
 * W549 (0x225) - FWW Contwow (6)
 */
#define WM8996_FWW_WEFCWK_SWC_STS_MASK          0x000C  /* FWW_WEFCWK_SWC_STS - [3:2] */
#define WM8996_FWW_WEFCWK_SWC_STS_SHIFT              2  /* FWW_WEFCWK_SWC_STS - [3:2] */
#define WM8996_FWW_WEFCWK_SWC_STS_WIDTH              2  /* FWW_WEFCWK_SWC_STS - [3:2] */
#define WM8996_FWW_SWITCH_CWK                   0x0001  /* FWW_SWITCH_CWK */
#define WM8996_FWW_SWITCH_CWK_MASK              0x0001  /* FWW_SWITCH_CWK */
#define WM8996_FWW_SWITCH_CWK_SHIFT                  0  /* FWW_SWITCH_CWK */
#define WM8996_FWW_SWITCH_CWK_WIDTH                  1  /* FWW_SWITCH_CWK */

/*
 * W550 (0x226) - FWW EFS 1
 */
#define WM8996_FWW_WAMBDA_MASK                  0xFFFF  /* FWW_WAMBDA - [15:0] */
#define WM8996_FWW_WAMBDA_SHIFT                      0  /* FWW_WAMBDA - [15:0] */
#define WM8996_FWW_WAMBDA_WIDTH                     16  /* FWW_WAMBDA - [15:0] */

/*
 * W551 (0x227) - FWW EFS 2
 */
#define WM8996_FWW_WFSW_SEW_MASK                0x0006  /* FWW_WFSW_SEW - [2:1] */
#define WM8996_FWW_WFSW_SEW_SHIFT                    1  /* FWW_WFSW_SEW - [2:1] */
#define WM8996_FWW_WFSW_SEW_WIDTH                    2  /* FWW_WFSW_SEW - [2:1] */
#define WM8996_FWW_EFS_ENA                      0x0001  /* FWW_EFS_ENA */
#define WM8996_FWW_EFS_ENA_MASK                 0x0001  /* FWW_EFS_ENA */
#define WM8996_FWW_EFS_ENA_SHIFT                     0  /* FWW_EFS_ENA */
#define WM8996_FWW_EFS_ENA_WIDTH                     1  /* FWW_EFS_ENA */

/*
 * W768 (0x300) - AIF1 Contwow
 */
#define WM8996_AIF1_TWI                         0x0004  /* AIF1_TWI */
#define WM8996_AIF1_TWI_MASK                    0x0004  /* AIF1_TWI */
#define WM8996_AIF1_TWI_SHIFT                        2  /* AIF1_TWI */
#define WM8996_AIF1_TWI_WIDTH                        1  /* AIF1_TWI */
#define WM8996_AIF1_FMT_MASK                    0x0003  /* AIF1_FMT - [1:0] */
#define WM8996_AIF1_FMT_SHIFT                        0  /* AIF1_FMT - [1:0] */
#define WM8996_AIF1_FMT_WIDTH                        2  /* AIF1_FMT - [1:0] */

/*
 * W769 (0x301) - AIF1 BCWK
 */
#define WM8996_AIF1_BCWK_INV                    0x0400  /* AIF1_BCWK_INV */
#define WM8996_AIF1_BCWK_INV_MASK               0x0400  /* AIF1_BCWK_INV */
#define WM8996_AIF1_BCWK_INV_SHIFT                  10  /* AIF1_BCWK_INV */
#define WM8996_AIF1_BCWK_INV_WIDTH                   1  /* AIF1_BCWK_INV */
#define WM8996_AIF1_BCWK_FWC                    0x0200  /* AIF1_BCWK_FWC */
#define WM8996_AIF1_BCWK_FWC_MASK               0x0200  /* AIF1_BCWK_FWC */
#define WM8996_AIF1_BCWK_FWC_SHIFT                   9  /* AIF1_BCWK_FWC */
#define WM8996_AIF1_BCWK_FWC_WIDTH                   1  /* AIF1_BCWK_FWC */
#define WM8996_AIF1_BCWK_MSTW                   0x0100  /* AIF1_BCWK_MSTW */
#define WM8996_AIF1_BCWK_MSTW_MASK              0x0100  /* AIF1_BCWK_MSTW */
#define WM8996_AIF1_BCWK_MSTW_SHIFT                  8  /* AIF1_BCWK_MSTW */
#define WM8996_AIF1_BCWK_MSTW_WIDTH                  1  /* AIF1_BCWK_MSTW */
#define WM8996_AIF1_BCWK_DIV_MASK               0x000F  /* AIF1_BCWK_DIV - [3:0] */
#define WM8996_AIF1_BCWK_DIV_SHIFT                   0  /* AIF1_BCWK_DIV - [3:0] */
#define WM8996_AIF1_BCWK_DIV_WIDTH                   4  /* AIF1_BCWK_DIV - [3:0] */

/*
 * W770 (0x302) - AIF1 TX WWCWK(1)
 */
#define WM8996_AIF1TX_WATE_MASK                 0x07FF  /* AIF1TX_WATE - [10:0] */
#define WM8996_AIF1TX_WATE_SHIFT                     0  /* AIF1TX_WATE - [10:0] */
#define WM8996_AIF1TX_WATE_WIDTH                    11  /* AIF1TX_WATE - [10:0] */

/*
 * W771 (0x303) - AIF1 TX WWCWK(2)
 */
#define WM8996_AIF1TX_WWCWK_MODE                0x0008  /* AIF1TX_WWCWK_MODE */
#define WM8996_AIF1TX_WWCWK_MODE_MASK           0x0008  /* AIF1TX_WWCWK_MODE */
#define WM8996_AIF1TX_WWCWK_MODE_SHIFT               3  /* AIF1TX_WWCWK_MODE */
#define WM8996_AIF1TX_WWCWK_MODE_WIDTH               1  /* AIF1TX_WWCWK_MODE */
#define WM8996_AIF1TX_WWCWK_INV                 0x0004  /* AIF1TX_WWCWK_INV */
#define WM8996_AIF1TX_WWCWK_INV_MASK            0x0004  /* AIF1TX_WWCWK_INV */
#define WM8996_AIF1TX_WWCWK_INV_SHIFT                2  /* AIF1TX_WWCWK_INV */
#define WM8996_AIF1TX_WWCWK_INV_WIDTH                1  /* AIF1TX_WWCWK_INV */
#define WM8996_AIF1TX_WWCWK_FWC                 0x0002  /* AIF1TX_WWCWK_FWC */
#define WM8996_AIF1TX_WWCWK_FWC_MASK            0x0002  /* AIF1TX_WWCWK_FWC */
#define WM8996_AIF1TX_WWCWK_FWC_SHIFT                1  /* AIF1TX_WWCWK_FWC */
#define WM8996_AIF1TX_WWCWK_FWC_WIDTH                1  /* AIF1TX_WWCWK_FWC */
#define WM8996_AIF1TX_WWCWK_MSTW                0x0001  /* AIF1TX_WWCWK_MSTW */
#define WM8996_AIF1TX_WWCWK_MSTW_MASK           0x0001  /* AIF1TX_WWCWK_MSTW */
#define WM8996_AIF1TX_WWCWK_MSTW_SHIFT               0  /* AIF1TX_WWCWK_MSTW */
#define WM8996_AIF1TX_WWCWK_MSTW_WIDTH               1  /* AIF1TX_WWCWK_MSTW */

/*
 * W772 (0x304) - AIF1 WX WWCWK(1)
 */
#define WM8996_AIF1WX_WATE_MASK                 0x07FF  /* AIF1WX_WATE - [10:0] */
#define WM8996_AIF1WX_WATE_SHIFT                     0  /* AIF1WX_WATE - [10:0] */
#define WM8996_AIF1WX_WATE_WIDTH                    11  /* AIF1WX_WATE - [10:0] */

/*
 * W773 (0x305) - AIF1 WX WWCWK(2)
 */
#define WM8996_AIF1WX_WWCWK_INV                 0x0004  /* AIF1WX_WWCWK_INV */
#define WM8996_AIF1WX_WWCWK_INV_MASK            0x0004  /* AIF1WX_WWCWK_INV */
#define WM8996_AIF1WX_WWCWK_INV_SHIFT                2  /* AIF1WX_WWCWK_INV */
#define WM8996_AIF1WX_WWCWK_INV_WIDTH                1  /* AIF1WX_WWCWK_INV */
#define WM8996_AIF1WX_WWCWK_FWC                 0x0002  /* AIF1WX_WWCWK_FWC */
#define WM8996_AIF1WX_WWCWK_FWC_MASK            0x0002  /* AIF1WX_WWCWK_FWC */
#define WM8996_AIF1WX_WWCWK_FWC_SHIFT                1  /* AIF1WX_WWCWK_FWC */
#define WM8996_AIF1WX_WWCWK_FWC_WIDTH                1  /* AIF1WX_WWCWK_FWC */
#define WM8996_AIF1WX_WWCWK_MSTW                0x0001  /* AIF1WX_WWCWK_MSTW */
#define WM8996_AIF1WX_WWCWK_MSTW_MASK           0x0001  /* AIF1WX_WWCWK_MSTW */
#define WM8996_AIF1WX_WWCWK_MSTW_SHIFT               0  /* AIF1WX_WWCWK_MSTW */
#define WM8996_AIF1WX_WWCWK_MSTW_WIDTH               1  /* AIF1WX_WWCWK_MSTW */

/*
 * W774 (0x306) - AIF1TX Data Configuwation (1)
 */
#define WM8996_AIF1TX_WW_MASK                   0xFF00  /* AIF1TX_WW - [15:8] */
#define WM8996_AIF1TX_WW_SHIFT                       8  /* AIF1TX_WW - [15:8] */
#define WM8996_AIF1TX_WW_WIDTH                       8  /* AIF1TX_WW - [15:8] */
#define WM8996_AIF1TX_SWOT_WEN_MASK             0x00FF  /* AIF1TX_SWOT_WEN - [7:0] */
#define WM8996_AIF1TX_SWOT_WEN_SHIFT                 0  /* AIF1TX_SWOT_WEN - [7:0] */
#define WM8996_AIF1TX_SWOT_WEN_WIDTH                 8  /* AIF1TX_SWOT_WEN - [7:0] */

/*
 * W775 (0x307) - AIF1TX Data Configuwation (2)
 */
#define WM8996_AIF1TX_DAT_TWI                   0x0001  /* AIF1TX_DAT_TWI */
#define WM8996_AIF1TX_DAT_TWI_MASK              0x0001  /* AIF1TX_DAT_TWI */
#define WM8996_AIF1TX_DAT_TWI_SHIFT                  0  /* AIF1TX_DAT_TWI */
#define WM8996_AIF1TX_DAT_TWI_WIDTH                  1  /* AIF1TX_DAT_TWI */

/*
 * W776 (0x308) - AIF1WX Data Configuwation
 */
#define WM8996_AIF1WX_WW_MASK                   0xFF00  /* AIF1WX_WW - [15:8] */
#define WM8996_AIF1WX_WW_SHIFT                       8  /* AIF1WX_WW - [15:8] */
#define WM8996_AIF1WX_WW_WIDTH                       8  /* AIF1WX_WW - [15:8] */
#define WM8996_AIF1WX_SWOT_WEN_MASK             0x00FF  /* AIF1WX_SWOT_WEN - [7:0] */
#define WM8996_AIF1WX_SWOT_WEN_SHIFT                 0  /* AIF1WX_SWOT_WEN - [7:0] */
#define WM8996_AIF1WX_SWOT_WEN_WIDTH                 8  /* AIF1WX_SWOT_WEN - [7:0] */

/*
 * W777 (0x309) - AIF1TX Channew 0 Configuwation
 */
#define WM8996_AIF1TX_CHAN0_DAT_INV             0x8000  /* AIF1TX_CHAN0_DAT_INV */
#define WM8996_AIF1TX_CHAN0_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN0_DAT_INV */
#define WM8996_AIF1TX_CHAN0_DAT_INV_SHIFT           15  /* AIF1TX_CHAN0_DAT_INV */
#define WM8996_AIF1TX_CHAN0_DAT_INV_WIDTH            1  /* AIF1TX_CHAN0_DAT_INV */
#define WM8996_AIF1TX_CHAN0_SPACING_MASK        0x7E00  /* AIF1TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN0_SPACING_SHIFT            9  /* AIF1TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN0_SPACING_WIDTH            6  /* AIF1TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN0_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN0_SWOTS_SHIFT              6  /* AIF1TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN0_SWOTS_WIDTH              3  /* AIF1TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN0_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN0_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN0_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN0_STAWT_SWOT - [5:0] */

/*
 * W778 (0x30A) - AIF1TX Channew 1 Configuwation
 */
#define WM8996_AIF1TX_CHAN1_DAT_INV             0x8000  /* AIF1TX_CHAN1_DAT_INV */
#define WM8996_AIF1TX_CHAN1_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN1_DAT_INV */
#define WM8996_AIF1TX_CHAN1_DAT_INV_SHIFT           15  /* AIF1TX_CHAN1_DAT_INV */
#define WM8996_AIF1TX_CHAN1_DAT_INV_WIDTH            1  /* AIF1TX_CHAN1_DAT_INV */
#define WM8996_AIF1TX_CHAN1_SPACING_MASK        0x7E00  /* AIF1TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN1_SPACING_SHIFT            9  /* AIF1TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN1_SPACING_WIDTH            6  /* AIF1TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN1_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN1_SWOTS_SHIFT              6  /* AIF1TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN1_SWOTS_WIDTH              3  /* AIF1TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN1_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN1_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN1_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN1_STAWT_SWOT - [5:0] */

/*
 * W779 (0x30B) - AIF1TX Channew 2 Configuwation
 */
#define WM8996_AIF1TX_CHAN2_DAT_INV             0x8000  /* AIF1TX_CHAN2_DAT_INV */
#define WM8996_AIF1TX_CHAN2_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN2_DAT_INV */
#define WM8996_AIF1TX_CHAN2_DAT_INV_SHIFT           15  /* AIF1TX_CHAN2_DAT_INV */
#define WM8996_AIF1TX_CHAN2_DAT_INV_WIDTH            1  /* AIF1TX_CHAN2_DAT_INV */
#define WM8996_AIF1TX_CHAN2_SPACING_MASK        0x7E00  /* AIF1TX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN2_SPACING_SHIFT            9  /* AIF1TX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN2_SPACING_WIDTH            6  /* AIF1TX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN2_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN2_SWOTS_SHIFT              6  /* AIF1TX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN2_SWOTS_WIDTH              3  /* AIF1TX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN2_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN2_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN2_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN2_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN2_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN2_STAWT_SWOT - [5:0] */

/*
 * W780 (0x30C) - AIF1TX Channew 3 Configuwation
 */
#define WM8996_AIF1TX_CHAN3_DAT_INV             0x8000  /* AIF1TX_CHAN3_DAT_INV */
#define WM8996_AIF1TX_CHAN3_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN3_DAT_INV */
#define WM8996_AIF1TX_CHAN3_DAT_INV_SHIFT           15  /* AIF1TX_CHAN3_DAT_INV */
#define WM8996_AIF1TX_CHAN3_DAT_INV_WIDTH            1  /* AIF1TX_CHAN3_DAT_INV */
#define WM8996_AIF1TX_CHAN3_SPACING_MASK        0x7E00  /* AIF1TX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN3_SPACING_SHIFT            9  /* AIF1TX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN3_SPACING_WIDTH            6  /* AIF1TX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN3_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN3_SWOTS_SHIFT              6  /* AIF1TX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN3_SWOTS_WIDTH              3  /* AIF1TX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN3_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN3_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN3_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN3_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN3_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN3_STAWT_SWOT - [5:0] */

/*
 * W781 (0x30D) - AIF1TX Channew 4 Configuwation
 */
#define WM8996_AIF1TX_CHAN4_DAT_INV             0x8000  /* AIF1TX_CHAN4_DAT_INV */
#define WM8996_AIF1TX_CHAN4_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN4_DAT_INV */
#define WM8996_AIF1TX_CHAN4_DAT_INV_SHIFT           15  /* AIF1TX_CHAN4_DAT_INV */
#define WM8996_AIF1TX_CHAN4_DAT_INV_WIDTH            1  /* AIF1TX_CHAN4_DAT_INV */
#define WM8996_AIF1TX_CHAN4_SPACING_MASK        0x7E00  /* AIF1TX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN4_SPACING_SHIFT            9  /* AIF1TX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN4_SPACING_WIDTH            6  /* AIF1TX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN4_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN4_SWOTS_SHIFT              6  /* AIF1TX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN4_SWOTS_WIDTH              3  /* AIF1TX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN4_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN4_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN4_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN4_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN4_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN4_STAWT_SWOT - [5:0] */

/*
 * W782 (0x30E) - AIF1TX Channew 5 Configuwation
 */
#define WM8996_AIF1TX_CHAN5_DAT_INV             0x8000  /* AIF1TX_CHAN5_DAT_INV */
#define WM8996_AIF1TX_CHAN5_DAT_INV_MASK        0x8000  /* AIF1TX_CHAN5_DAT_INV */
#define WM8996_AIF1TX_CHAN5_DAT_INV_SHIFT           15  /* AIF1TX_CHAN5_DAT_INV */
#define WM8996_AIF1TX_CHAN5_DAT_INV_WIDTH            1  /* AIF1TX_CHAN5_DAT_INV */
#define WM8996_AIF1TX_CHAN5_SPACING_MASK        0x7E00  /* AIF1TX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN5_SPACING_SHIFT            9  /* AIF1TX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN5_SPACING_WIDTH            6  /* AIF1TX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1TX_CHAN5_SWOTS_MASK          0x01C0  /* AIF1TX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN5_SWOTS_SHIFT              6  /* AIF1TX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN5_SWOTS_WIDTH              3  /* AIF1TX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1TX_CHAN5_STAWT_SWOT_MASK     0x003F  /* AIF1TX_CHAN5_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN5_STAWT_SWOT_SHIFT         0  /* AIF1TX_CHAN5_STAWT_SWOT - [5:0] */
#define WM8996_AIF1TX_CHAN5_STAWT_SWOT_WIDTH         6  /* AIF1TX_CHAN5_STAWT_SWOT - [5:0] */

/*
 * W783 (0x30F) - AIF1WX Channew 0 Configuwation
 */
#define WM8996_AIF1WX_CHAN0_DAT_INV             0x8000  /* AIF1WX_CHAN0_DAT_INV */
#define WM8996_AIF1WX_CHAN0_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN0_DAT_INV */
#define WM8996_AIF1WX_CHAN0_DAT_INV_SHIFT           15  /* AIF1WX_CHAN0_DAT_INV */
#define WM8996_AIF1WX_CHAN0_DAT_INV_WIDTH            1  /* AIF1WX_CHAN0_DAT_INV */
#define WM8996_AIF1WX_CHAN0_SPACING_MASK        0x7E00  /* AIF1WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN0_SPACING_SHIFT            9  /* AIF1WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN0_SPACING_WIDTH            6  /* AIF1WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN0_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN0_SWOTS_SHIFT              6  /* AIF1WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN0_SWOTS_WIDTH              3  /* AIF1WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN0_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN0_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN0_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN0_STAWT_SWOT - [5:0] */

/*
 * W784 (0x310) - AIF1WX Channew 1 Configuwation
 */
#define WM8996_AIF1WX_CHAN1_DAT_INV             0x8000  /* AIF1WX_CHAN1_DAT_INV */
#define WM8996_AIF1WX_CHAN1_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN1_DAT_INV */
#define WM8996_AIF1WX_CHAN1_DAT_INV_SHIFT           15  /* AIF1WX_CHAN1_DAT_INV */
#define WM8996_AIF1WX_CHAN1_DAT_INV_WIDTH            1  /* AIF1WX_CHAN1_DAT_INV */
#define WM8996_AIF1WX_CHAN1_SPACING_MASK        0x7E00  /* AIF1WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN1_SPACING_SHIFT            9  /* AIF1WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN1_SPACING_WIDTH            6  /* AIF1WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN1_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN1_SWOTS_SHIFT              6  /* AIF1WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN1_SWOTS_WIDTH              3  /* AIF1WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN1_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN1_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN1_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN1_STAWT_SWOT - [5:0] */

/*
 * W785 (0x311) - AIF1WX Channew 2 Configuwation
 */
#define WM8996_AIF1WX_CHAN2_DAT_INV             0x8000  /* AIF1WX_CHAN2_DAT_INV */
#define WM8996_AIF1WX_CHAN2_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN2_DAT_INV */
#define WM8996_AIF1WX_CHAN2_DAT_INV_SHIFT           15  /* AIF1WX_CHAN2_DAT_INV */
#define WM8996_AIF1WX_CHAN2_DAT_INV_WIDTH            1  /* AIF1WX_CHAN2_DAT_INV */
#define WM8996_AIF1WX_CHAN2_SPACING_MASK        0x7E00  /* AIF1WX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN2_SPACING_SHIFT            9  /* AIF1WX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN2_SPACING_WIDTH            6  /* AIF1WX_CHAN2_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN2_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN2_SWOTS_SHIFT              6  /* AIF1WX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN2_SWOTS_WIDTH              3  /* AIF1WX_CHAN2_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN2_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN2_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN2_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN2_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN2_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN2_STAWT_SWOT - [5:0] */

/*
 * W786 (0x312) - AIF1WX Channew 3 Configuwation
 */
#define WM8996_AIF1WX_CHAN3_DAT_INV             0x8000  /* AIF1WX_CHAN3_DAT_INV */
#define WM8996_AIF1WX_CHAN3_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN3_DAT_INV */
#define WM8996_AIF1WX_CHAN3_DAT_INV_SHIFT           15  /* AIF1WX_CHAN3_DAT_INV */
#define WM8996_AIF1WX_CHAN3_DAT_INV_WIDTH            1  /* AIF1WX_CHAN3_DAT_INV */
#define WM8996_AIF1WX_CHAN3_SPACING_MASK        0x7E00  /* AIF1WX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN3_SPACING_SHIFT            9  /* AIF1WX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN3_SPACING_WIDTH            6  /* AIF1WX_CHAN3_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN3_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN3_SWOTS_SHIFT              6  /* AIF1WX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN3_SWOTS_WIDTH              3  /* AIF1WX_CHAN3_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN3_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN3_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN3_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN3_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN3_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN3_STAWT_SWOT - [5:0] */

/*
 * W787 (0x313) - AIF1WX Channew 4 Configuwation
 */
#define WM8996_AIF1WX_CHAN4_DAT_INV             0x8000  /* AIF1WX_CHAN4_DAT_INV */
#define WM8996_AIF1WX_CHAN4_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN4_DAT_INV */
#define WM8996_AIF1WX_CHAN4_DAT_INV_SHIFT           15  /* AIF1WX_CHAN4_DAT_INV */
#define WM8996_AIF1WX_CHAN4_DAT_INV_WIDTH            1  /* AIF1WX_CHAN4_DAT_INV */
#define WM8996_AIF1WX_CHAN4_SPACING_MASK        0x7E00  /* AIF1WX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN4_SPACING_SHIFT            9  /* AIF1WX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN4_SPACING_WIDTH            6  /* AIF1WX_CHAN4_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN4_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN4_SWOTS_SHIFT              6  /* AIF1WX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN4_SWOTS_WIDTH              3  /* AIF1WX_CHAN4_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN4_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN4_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN4_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN4_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN4_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN4_STAWT_SWOT - [5:0] */

/*
 * W788 (0x314) - AIF1WX Channew 5 Configuwation
 */
#define WM8996_AIF1WX_CHAN5_DAT_INV             0x8000  /* AIF1WX_CHAN5_DAT_INV */
#define WM8996_AIF1WX_CHAN5_DAT_INV_MASK        0x8000  /* AIF1WX_CHAN5_DAT_INV */
#define WM8996_AIF1WX_CHAN5_DAT_INV_SHIFT           15  /* AIF1WX_CHAN5_DAT_INV */
#define WM8996_AIF1WX_CHAN5_DAT_INV_WIDTH            1  /* AIF1WX_CHAN5_DAT_INV */
#define WM8996_AIF1WX_CHAN5_SPACING_MASK        0x7E00  /* AIF1WX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN5_SPACING_SHIFT            9  /* AIF1WX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN5_SPACING_WIDTH            6  /* AIF1WX_CHAN5_SPACING - [14:9] */
#define WM8996_AIF1WX_CHAN5_SWOTS_MASK          0x01C0  /* AIF1WX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN5_SWOTS_SHIFT              6  /* AIF1WX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN5_SWOTS_WIDTH              3  /* AIF1WX_CHAN5_SWOTS - [8:6] */
#define WM8996_AIF1WX_CHAN5_STAWT_SWOT_MASK     0x003F  /* AIF1WX_CHAN5_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN5_STAWT_SWOT_SHIFT         0  /* AIF1WX_CHAN5_STAWT_SWOT - [5:0] */
#define WM8996_AIF1WX_CHAN5_STAWT_SWOT_WIDTH         6  /* AIF1WX_CHAN5_STAWT_SWOT - [5:0] */

/*
 * W789 (0x315) - AIF1WX Mono Configuwation
 */
#define WM8996_AIF1WX_CHAN4_MONO_MODE           0x0004  /* AIF1WX_CHAN4_MONO_MODE */
#define WM8996_AIF1WX_CHAN4_MONO_MODE_MASK      0x0004  /* AIF1WX_CHAN4_MONO_MODE */
#define WM8996_AIF1WX_CHAN4_MONO_MODE_SHIFT          2  /* AIF1WX_CHAN4_MONO_MODE */
#define WM8996_AIF1WX_CHAN4_MONO_MODE_WIDTH          1  /* AIF1WX_CHAN4_MONO_MODE */
#define WM8996_AIF1WX_CHAN2_MONO_MODE           0x0002  /* AIF1WX_CHAN2_MONO_MODE */
#define WM8996_AIF1WX_CHAN2_MONO_MODE_MASK      0x0002  /* AIF1WX_CHAN2_MONO_MODE */
#define WM8996_AIF1WX_CHAN2_MONO_MODE_SHIFT          1  /* AIF1WX_CHAN2_MONO_MODE */
#define WM8996_AIF1WX_CHAN2_MONO_MODE_WIDTH          1  /* AIF1WX_CHAN2_MONO_MODE */
#define WM8996_AIF1WX_CHAN0_MONO_MODE           0x0001  /* AIF1WX_CHAN0_MONO_MODE */
#define WM8996_AIF1WX_CHAN0_MONO_MODE_MASK      0x0001  /* AIF1WX_CHAN0_MONO_MODE */
#define WM8996_AIF1WX_CHAN0_MONO_MODE_SHIFT          0  /* AIF1WX_CHAN0_MONO_MODE */
#define WM8996_AIF1WX_CHAN0_MONO_MODE_WIDTH          1  /* AIF1WX_CHAN0_MONO_MODE */

/*
 * W794 (0x31A) - AIF1TX Test
 */
#define WM8996_AIF1TX45_DITHEW_ENA              0x0004  /* AIF1TX45_DITHEW_ENA */
#define WM8996_AIF1TX45_DITHEW_ENA_MASK         0x0004  /* AIF1TX45_DITHEW_ENA */
#define WM8996_AIF1TX45_DITHEW_ENA_SHIFT             2  /* AIF1TX45_DITHEW_ENA */
#define WM8996_AIF1TX45_DITHEW_ENA_WIDTH             1  /* AIF1TX45_DITHEW_ENA */
#define WM8996_AIF1TX23_DITHEW_ENA              0x0002  /* AIF1TX23_DITHEW_ENA */
#define WM8996_AIF1TX23_DITHEW_ENA_MASK         0x0002  /* AIF1TX23_DITHEW_ENA */
#define WM8996_AIF1TX23_DITHEW_ENA_SHIFT             1  /* AIF1TX23_DITHEW_ENA */
#define WM8996_AIF1TX23_DITHEW_ENA_WIDTH             1  /* AIF1TX23_DITHEW_ENA */
#define WM8996_AIF1TX01_DITHEW_ENA              0x0001  /* AIF1TX01_DITHEW_ENA */
#define WM8996_AIF1TX01_DITHEW_ENA_MASK         0x0001  /* AIF1TX01_DITHEW_ENA */
#define WM8996_AIF1TX01_DITHEW_ENA_SHIFT             0  /* AIF1TX01_DITHEW_ENA */
#define WM8996_AIF1TX01_DITHEW_ENA_WIDTH             1  /* AIF1TX01_DITHEW_ENA */

/*
 * W800 (0x320) - AIF2 Contwow
 */
#define WM8996_AIF2_TWI                         0x0004  /* AIF2_TWI */
#define WM8996_AIF2_TWI_MASK                    0x0004  /* AIF2_TWI */
#define WM8996_AIF2_TWI_SHIFT                        2  /* AIF2_TWI */
#define WM8996_AIF2_TWI_WIDTH                        1  /* AIF2_TWI */
#define WM8996_AIF2_FMT_MASK                    0x0003  /* AIF2_FMT - [1:0] */
#define WM8996_AIF2_FMT_SHIFT                        0  /* AIF2_FMT - [1:0] */
#define WM8996_AIF2_FMT_WIDTH                        2  /* AIF2_FMT - [1:0] */

/*
 * W801 (0x321) - AIF2 BCWK
 */
#define WM8996_AIF2_BCWK_INV                    0x0400  /* AIF2_BCWK_INV */
#define WM8996_AIF2_BCWK_INV_MASK               0x0400  /* AIF2_BCWK_INV */
#define WM8996_AIF2_BCWK_INV_SHIFT                  10  /* AIF2_BCWK_INV */
#define WM8996_AIF2_BCWK_INV_WIDTH                   1  /* AIF2_BCWK_INV */
#define WM8996_AIF2_BCWK_FWC                    0x0200  /* AIF2_BCWK_FWC */
#define WM8996_AIF2_BCWK_FWC_MASK               0x0200  /* AIF2_BCWK_FWC */
#define WM8996_AIF2_BCWK_FWC_SHIFT                   9  /* AIF2_BCWK_FWC */
#define WM8996_AIF2_BCWK_FWC_WIDTH                   1  /* AIF2_BCWK_FWC */
#define WM8996_AIF2_BCWK_MSTW                   0x0100  /* AIF2_BCWK_MSTW */
#define WM8996_AIF2_BCWK_MSTW_MASK              0x0100  /* AIF2_BCWK_MSTW */
#define WM8996_AIF2_BCWK_MSTW_SHIFT                  8  /* AIF2_BCWK_MSTW */
#define WM8996_AIF2_BCWK_MSTW_WIDTH                  1  /* AIF2_BCWK_MSTW */
#define WM8996_AIF2_BCWK_DIV_MASK               0x000F  /* AIF2_BCWK_DIV - [3:0] */
#define WM8996_AIF2_BCWK_DIV_SHIFT                   0  /* AIF2_BCWK_DIV - [3:0] */
#define WM8996_AIF2_BCWK_DIV_WIDTH                   4  /* AIF2_BCWK_DIV - [3:0] */

/*
 * W802 (0x322) - AIF2 TX WWCWK(1)
 */
#define WM8996_AIF2TX_WATE_MASK                 0x07FF  /* AIF2TX_WATE - [10:0] */
#define WM8996_AIF2TX_WATE_SHIFT                     0  /* AIF2TX_WATE - [10:0] */
#define WM8996_AIF2TX_WATE_WIDTH                    11  /* AIF2TX_WATE - [10:0] */

/*
 * W803 (0x323) - AIF2 TX WWCWK(2)
 */
#define WM8996_AIF2TX_WWCWK_MODE                0x0008  /* AIF2TX_WWCWK_MODE */
#define WM8996_AIF2TX_WWCWK_MODE_MASK           0x0008  /* AIF2TX_WWCWK_MODE */
#define WM8996_AIF2TX_WWCWK_MODE_SHIFT               3  /* AIF2TX_WWCWK_MODE */
#define WM8996_AIF2TX_WWCWK_MODE_WIDTH               1  /* AIF2TX_WWCWK_MODE */
#define WM8996_AIF2TX_WWCWK_INV                 0x0004  /* AIF2TX_WWCWK_INV */
#define WM8996_AIF2TX_WWCWK_INV_MASK            0x0004  /* AIF2TX_WWCWK_INV */
#define WM8996_AIF2TX_WWCWK_INV_SHIFT                2  /* AIF2TX_WWCWK_INV */
#define WM8996_AIF2TX_WWCWK_INV_WIDTH                1  /* AIF2TX_WWCWK_INV */
#define WM8996_AIF2TX_WWCWK_FWC                 0x0002  /* AIF2TX_WWCWK_FWC */
#define WM8996_AIF2TX_WWCWK_FWC_MASK            0x0002  /* AIF2TX_WWCWK_FWC */
#define WM8996_AIF2TX_WWCWK_FWC_SHIFT                1  /* AIF2TX_WWCWK_FWC */
#define WM8996_AIF2TX_WWCWK_FWC_WIDTH                1  /* AIF2TX_WWCWK_FWC */
#define WM8996_AIF2TX_WWCWK_MSTW                0x0001  /* AIF2TX_WWCWK_MSTW */
#define WM8996_AIF2TX_WWCWK_MSTW_MASK           0x0001  /* AIF2TX_WWCWK_MSTW */
#define WM8996_AIF2TX_WWCWK_MSTW_SHIFT               0  /* AIF2TX_WWCWK_MSTW */
#define WM8996_AIF2TX_WWCWK_MSTW_WIDTH               1  /* AIF2TX_WWCWK_MSTW */

/*
 * W804 (0x324) - AIF2 WX WWCWK(1)
 */
#define WM8996_AIF2WX_WATE_MASK                 0x07FF  /* AIF2WX_WATE - [10:0] */
#define WM8996_AIF2WX_WATE_SHIFT                     0  /* AIF2WX_WATE - [10:0] */
#define WM8996_AIF2WX_WATE_WIDTH                    11  /* AIF2WX_WATE - [10:0] */

/*
 * W805 (0x325) - AIF2 WX WWCWK(2)
 */
#define WM8996_AIF2WX_WWCWK_INV                 0x0004  /* AIF2WX_WWCWK_INV */
#define WM8996_AIF2WX_WWCWK_INV_MASK            0x0004  /* AIF2WX_WWCWK_INV */
#define WM8996_AIF2WX_WWCWK_INV_SHIFT                2  /* AIF2WX_WWCWK_INV */
#define WM8996_AIF2WX_WWCWK_INV_WIDTH                1  /* AIF2WX_WWCWK_INV */
#define WM8996_AIF2WX_WWCWK_FWC                 0x0002  /* AIF2WX_WWCWK_FWC */
#define WM8996_AIF2WX_WWCWK_FWC_MASK            0x0002  /* AIF2WX_WWCWK_FWC */
#define WM8996_AIF2WX_WWCWK_FWC_SHIFT                1  /* AIF2WX_WWCWK_FWC */
#define WM8996_AIF2WX_WWCWK_FWC_WIDTH                1  /* AIF2WX_WWCWK_FWC */
#define WM8996_AIF2WX_WWCWK_MSTW                0x0001  /* AIF2WX_WWCWK_MSTW */
#define WM8996_AIF2WX_WWCWK_MSTW_MASK           0x0001  /* AIF2WX_WWCWK_MSTW */
#define WM8996_AIF2WX_WWCWK_MSTW_SHIFT               0  /* AIF2WX_WWCWK_MSTW */
#define WM8996_AIF2WX_WWCWK_MSTW_WIDTH               1  /* AIF2WX_WWCWK_MSTW */

/*
 * W806 (0x326) - AIF2TX Data Configuwation (1)
 */
#define WM8996_AIF2TX_WW_MASK                   0xFF00  /* AIF2TX_WW - [15:8] */
#define WM8996_AIF2TX_WW_SHIFT                       8  /* AIF2TX_WW - [15:8] */
#define WM8996_AIF2TX_WW_WIDTH                       8  /* AIF2TX_WW - [15:8] */
#define WM8996_AIF2TX_SWOT_WEN_MASK             0x00FF  /* AIF2TX_SWOT_WEN - [7:0] */
#define WM8996_AIF2TX_SWOT_WEN_SHIFT                 0  /* AIF2TX_SWOT_WEN - [7:0] */
#define WM8996_AIF2TX_SWOT_WEN_WIDTH                 8  /* AIF2TX_SWOT_WEN - [7:0] */

/*
 * W807 (0x327) - AIF2TX Data Configuwation (2)
 */
#define WM8996_AIF2TX_DAT_TWI                   0x0001  /* AIF2TX_DAT_TWI */
#define WM8996_AIF2TX_DAT_TWI_MASK              0x0001  /* AIF2TX_DAT_TWI */
#define WM8996_AIF2TX_DAT_TWI_SHIFT                  0  /* AIF2TX_DAT_TWI */
#define WM8996_AIF2TX_DAT_TWI_WIDTH                  1  /* AIF2TX_DAT_TWI */

/*
 * W808 (0x328) - AIF2WX Data Configuwation
 */
#define WM8996_AIF2WX_WW_MASK                   0xFF00  /* AIF2WX_WW - [15:8] */
#define WM8996_AIF2WX_WW_SHIFT                       8  /* AIF2WX_WW - [15:8] */
#define WM8996_AIF2WX_WW_WIDTH                       8  /* AIF2WX_WW - [15:8] */
#define WM8996_AIF2WX_SWOT_WEN_MASK             0x00FF  /* AIF2WX_SWOT_WEN - [7:0] */
#define WM8996_AIF2WX_SWOT_WEN_SHIFT                 0  /* AIF2WX_SWOT_WEN - [7:0] */
#define WM8996_AIF2WX_SWOT_WEN_WIDTH                 8  /* AIF2WX_SWOT_WEN - [7:0] */

/*
 * W809 (0x329) - AIF2TX Channew 0 Configuwation
 */
#define WM8996_AIF2TX_CHAN0_DAT_INV             0x8000  /* AIF2TX_CHAN0_DAT_INV */
#define WM8996_AIF2TX_CHAN0_DAT_INV_MASK        0x8000  /* AIF2TX_CHAN0_DAT_INV */
#define WM8996_AIF2TX_CHAN0_DAT_INV_SHIFT           15  /* AIF2TX_CHAN0_DAT_INV */
#define WM8996_AIF2TX_CHAN0_DAT_INV_WIDTH            1  /* AIF2TX_CHAN0_DAT_INV */
#define WM8996_AIF2TX_CHAN0_SPACING_MASK        0x7E00  /* AIF2TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN0_SPACING_SHIFT            9  /* AIF2TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN0_SPACING_WIDTH            6  /* AIF2TX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN0_SWOTS_MASK          0x01C0  /* AIF2TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN0_SWOTS_SHIFT              6  /* AIF2TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN0_SWOTS_WIDTH              3  /* AIF2TX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN0_STAWT_SWOT_MASK     0x003F  /* AIF2TX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF2TX_CHAN0_STAWT_SWOT_SHIFT         0  /* AIF2TX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF2TX_CHAN0_STAWT_SWOT_WIDTH         6  /* AIF2TX_CHAN0_STAWT_SWOT - [5:0] */

/*
 * W810 (0x32A) - AIF2TX Channew 1 Configuwation
 */
#define WM8996_AIF2TX_CHAN1_DAT_INV             0x8000  /* AIF2TX_CHAN1_DAT_INV */
#define WM8996_AIF2TX_CHAN1_DAT_INV_MASK        0x8000  /* AIF2TX_CHAN1_DAT_INV */
#define WM8996_AIF2TX_CHAN1_DAT_INV_SHIFT           15  /* AIF2TX_CHAN1_DAT_INV */
#define WM8996_AIF2TX_CHAN1_DAT_INV_WIDTH            1  /* AIF2TX_CHAN1_DAT_INV */
#define WM8996_AIF2TX_CHAN1_SPACING_MASK        0x7E00  /* AIF2TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN1_SPACING_SHIFT            9  /* AIF2TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN1_SPACING_WIDTH            6  /* AIF2TX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2TX_CHAN1_SWOTS_MASK          0x01C0  /* AIF2TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN1_SWOTS_SHIFT              6  /* AIF2TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN1_SWOTS_WIDTH              3  /* AIF2TX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2TX_CHAN1_STAWT_SWOT_MASK     0x003F  /* AIF2TX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF2TX_CHAN1_STAWT_SWOT_SHIFT         0  /* AIF2TX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF2TX_CHAN1_STAWT_SWOT_WIDTH         6  /* AIF2TX_CHAN1_STAWT_SWOT - [5:0] */

/*
 * W811 (0x32B) - AIF2WX Channew 0 Configuwation
 */
#define WM8996_AIF2WX_CHAN0_DAT_INV             0x8000  /* AIF2WX_CHAN0_DAT_INV */
#define WM8996_AIF2WX_CHAN0_DAT_INV_MASK        0x8000  /* AIF2WX_CHAN0_DAT_INV */
#define WM8996_AIF2WX_CHAN0_DAT_INV_SHIFT           15  /* AIF2WX_CHAN0_DAT_INV */
#define WM8996_AIF2WX_CHAN0_DAT_INV_WIDTH            1  /* AIF2WX_CHAN0_DAT_INV */
#define WM8996_AIF2WX_CHAN0_SPACING_MASK        0x7E00  /* AIF2WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN0_SPACING_SHIFT            9  /* AIF2WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN0_SPACING_WIDTH            6  /* AIF2WX_CHAN0_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN0_SWOTS_MASK          0x01C0  /* AIF2WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN0_SWOTS_SHIFT              6  /* AIF2WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN0_SWOTS_WIDTH              3  /* AIF2WX_CHAN0_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN0_STAWT_SWOT_MASK     0x003F  /* AIF2WX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF2WX_CHAN0_STAWT_SWOT_SHIFT         0  /* AIF2WX_CHAN0_STAWT_SWOT - [5:0] */
#define WM8996_AIF2WX_CHAN0_STAWT_SWOT_WIDTH         6  /* AIF2WX_CHAN0_STAWT_SWOT - [5:0] */

/*
 * W812 (0x32C) - AIF2WX Channew 1 Configuwation
 */
#define WM8996_AIF2WX_CHAN1_DAT_INV             0x8000  /* AIF2WX_CHAN1_DAT_INV */
#define WM8996_AIF2WX_CHAN1_DAT_INV_MASK        0x8000  /* AIF2WX_CHAN1_DAT_INV */
#define WM8996_AIF2WX_CHAN1_DAT_INV_SHIFT           15  /* AIF2WX_CHAN1_DAT_INV */
#define WM8996_AIF2WX_CHAN1_DAT_INV_WIDTH            1  /* AIF2WX_CHAN1_DAT_INV */
#define WM8996_AIF2WX_CHAN1_SPACING_MASK        0x7E00  /* AIF2WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN1_SPACING_SHIFT            9  /* AIF2WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN1_SPACING_WIDTH            6  /* AIF2WX_CHAN1_SPACING - [14:9] */
#define WM8996_AIF2WX_CHAN1_SWOTS_MASK          0x01C0  /* AIF2WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN1_SWOTS_SHIFT              6  /* AIF2WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN1_SWOTS_WIDTH              3  /* AIF2WX_CHAN1_SWOTS - [8:6] */
#define WM8996_AIF2WX_CHAN1_STAWT_SWOT_MASK     0x003F  /* AIF2WX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF2WX_CHAN1_STAWT_SWOT_SHIFT         0  /* AIF2WX_CHAN1_STAWT_SWOT - [5:0] */
#define WM8996_AIF2WX_CHAN1_STAWT_SWOT_WIDTH         6  /* AIF2WX_CHAN1_STAWT_SWOT - [5:0] */

/*
 * W813 (0x32D) - AIF2WX Mono Configuwation
 */
#define WM8996_AIF2WX_CHAN0_MONO_MODE           0x0001  /* AIF2WX_CHAN0_MONO_MODE */
#define WM8996_AIF2WX_CHAN0_MONO_MODE_MASK      0x0001  /* AIF2WX_CHAN0_MONO_MODE */
#define WM8996_AIF2WX_CHAN0_MONO_MODE_SHIFT          0  /* AIF2WX_CHAN0_MONO_MODE */
#define WM8996_AIF2WX_CHAN0_MONO_MODE_WIDTH          1  /* AIF2WX_CHAN0_MONO_MODE */

/*
 * W815 (0x32F) - AIF2TX Test
 */
#define WM8996_AIF2TX_DITHEW_ENA                0x0001  /* AIF2TX_DITHEW_ENA */
#define WM8996_AIF2TX_DITHEW_ENA_MASK           0x0001  /* AIF2TX_DITHEW_ENA */
#define WM8996_AIF2TX_DITHEW_ENA_SHIFT               0  /* AIF2TX_DITHEW_ENA */
#define WM8996_AIF2TX_DITHEW_ENA_WIDTH               1  /* AIF2TX_DITHEW_ENA */

/*
 * W1024 (0x400) - DSP1 TX Weft Vowume
 */
#define WM8996_DSP1TX_VU                        0x0100  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_MASK                   0x0100  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_SHIFT                       8  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_WIDTH                       1  /* DSP1TX_VU */
#define WM8996_DSP1TXW_VOW_MASK                 0x00FF  /* DSP1TXW_VOW - [7:0] */
#define WM8996_DSP1TXW_VOW_SHIFT                     0  /* DSP1TXW_VOW - [7:0] */
#define WM8996_DSP1TXW_VOW_WIDTH                     8  /* DSP1TXW_VOW - [7:0] */

/*
 * W1025 (0x401) - DSP1 TX Wight Vowume
 */
#define WM8996_DSP1TX_VU                        0x0100  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_MASK                   0x0100  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_SHIFT                       8  /* DSP1TX_VU */
#define WM8996_DSP1TX_VU_WIDTH                       1  /* DSP1TX_VU */
#define WM8996_DSP1TXW_VOW_MASK                 0x00FF  /* DSP1TXW_VOW - [7:0] */
#define WM8996_DSP1TXW_VOW_SHIFT                     0  /* DSP1TXW_VOW - [7:0] */
#define WM8996_DSP1TXW_VOW_WIDTH                     8  /* DSP1TXW_VOW - [7:0] */

/*
 * W1026 (0x402) - DSP1 WX Weft Vowume
 */
#define WM8996_DSP1WX_VU                        0x0100  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_MASK                   0x0100  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_SHIFT                       8  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_WIDTH                       1  /* DSP1WX_VU */
#define WM8996_DSP1WXW_VOW_MASK                 0x00FF  /* DSP1WXW_VOW - [7:0] */
#define WM8996_DSP1WXW_VOW_SHIFT                     0  /* DSP1WXW_VOW - [7:0] */
#define WM8996_DSP1WXW_VOW_WIDTH                     8  /* DSP1WXW_VOW - [7:0] */

/*
 * W1027 (0x403) - DSP1 WX Wight Vowume
 */
#define WM8996_DSP1WX_VU                        0x0100  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_MASK                   0x0100  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_SHIFT                       8  /* DSP1WX_VU */
#define WM8996_DSP1WX_VU_WIDTH                       1  /* DSP1WX_VU */
#define WM8996_DSP1WXW_VOW_MASK                 0x00FF  /* DSP1WXW_VOW - [7:0] */
#define WM8996_DSP1WXW_VOW_SHIFT                     0  /* DSP1WXW_VOW - [7:0] */
#define WM8996_DSP1WXW_VOW_WIDTH                     8  /* DSP1WXW_VOW - [7:0] */

/*
 * W1040 (0x410) - DSP1 TX Fiwtews
 */
#define WM8996_DSP1TX_NF                        0x2000  /* DSP1TX_NF */
#define WM8996_DSP1TX_NF_MASK                   0x2000  /* DSP1TX_NF */
#define WM8996_DSP1TX_NF_SHIFT                      13  /* DSP1TX_NF */
#define WM8996_DSP1TX_NF_WIDTH                       1  /* DSP1TX_NF */
#define WM8996_DSP1TXW_HPF                      0x1000  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_MASK                 0x1000  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_SHIFT                    12  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_WIDTH                     1  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF                      0x0800  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_MASK                 0x0800  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_SHIFT                    11  /* DSP1TXW_HPF */
#define WM8996_DSP1TXW_HPF_WIDTH                     1  /* DSP1TXW_HPF */
#define WM8996_DSP1TX_HPF_MODE_MASK             0x0018  /* DSP1TX_HPF_MODE - [4:3] */
#define WM8996_DSP1TX_HPF_MODE_SHIFT                 3  /* DSP1TX_HPF_MODE - [4:3] */
#define WM8996_DSP1TX_HPF_MODE_WIDTH                 2  /* DSP1TX_HPF_MODE - [4:3] */
#define WM8996_DSP1TX_HPF_CUT_MASK              0x0007  /* DSP1TX_HPF_CUT - [2:0] */
#define WM8996_DSP1TX_HPF_CUT_SHIFT                  0  /* DSP1TX_HPF_CUT - [2:0] */
#define WM8996_DSP1TX_HPF_CUT_WIDTH                  3  /* DSP1TX_HPF_CUT - [2:0] */

/*
 * W1056 (0x420) - DSP1 WX Fiwtews (1)
 */
#define WM8996_DSP1WX_MUTE                      0x0200  /* DSP1WX_MUTE */
#define WM8996_DSP1WX_MUTE_MASK                 0x0200  /* DSP1WX_MUTE */
#define WM8996_DSP1WX_MUTE_SHIFT                     9  /* DSP1WX_MUTE */
#define WM8996_DSP1WX_MUTE_WIDTH                     1  /* DSP1WX_MUTE */
#define WM8996_DSP1WX_MONO                      0x0080  /* DSP1WX_MONO */
#define WM8996_DSP1WX_MONO_MASK                 0x0080  /* DSP1WX_MONO */
#define WM8996_DSP1WX_MONO_SHIFT                     7  /* DSP1WX_MONO */
#define WM8996_DSP1WX_MONO_WIDTH                     1  /* DSP1WX_MONO */
#define WM8996_DSP1WX_MUTEWATE                  0x0020  /* DSP1WX_MUTEWATE */
#define WM8996_DSP1WX_MUTEWATE_MASK             0x0020  /* DSP1WX_MUTEWATE */
#define WM8996_DSP1WX_MUTEWATE_SHIFT                 5  /* DSP1WX_MUTEWATE */
#define WM8996_DSP1WX_MUTEWATE_WIDTH                 1  /* DSP1WX_MUTEWATE */
#define WM8996_DSP1WX_UNMUTE_WAMP               0x0010  /* DSP1WX_UNMUTE_WAMP */
#define WM8996_DSP1WX_UNMUTE_WAMP_MASK          0x0010  /* DSP1WX_UNMUTE_WAMP */
#define WM8996_DSP1WX_UNMUTE_WAMP_SHIFT              4  /* DSP1WX_UNMUTE_WAMP */
#define WM8996_DSP1WX_UNMUTE_WAMP_WIDTH              1  /* DSP1WX_UNMUTE_WAMP */

/*
 * W1057 (0x421) - DSP1 WX Fiwtews (2)
 */
#define WM8996_DSP1WX_3D_GAIN_MASK              0x3E00  /* DSP1WX_3D_GAIN - [13:9] */
#define WM8996_DSP1WX_3D_GAIN_SHIFT                  9  /* DSP1WX_3D_GAIN - [13:9] */
#define WM8996_DSP1WX_3D_GAIN_WIDTH                  5  /* DSP1WX_3D_GAIN - [13:9] */
#define WM8996_DSP1WX_3D_ENA                    0x0100  /* DSP1WX_3D_ENA */
#define WM8996_DSP1WX_3D_ENA_MASK               0x0100  /* DSP1WX_3D_ENA */
#define WM8996_DSP1WX_3D_ENA_SHIFT                   8  /* DSP1WX_3D_ENA */
#define WM8996_DSP1WX_3D_ENA_WIDTH                   1  /* DSP1WX_3D_ENA */

/*
 * W1088 (0x440) - DSP1 DWC (1)
 */
#define WM8996_DSP1DWC_SIG_DET_WMS_MASK         0xF800  /* DSP1DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP1DWC_SIG_DET_WMS_SHIFT            11  /* DSP1DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP1DWC_SIG_DET_WMS_WIDTH             5  /* DSP1DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP1DWC_SIG_DET_PK_MASK          0x0600  /* DSP1DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP1DWC_SIG_DET_PK_SHIFT              9  /* DSP1DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP1DWC_SIG_DET_PK_WIDTH              2  /* DSP1DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP1DWC_NG_ENA                   0x0100  /* DSP1DWC_NG_ENA */
#define WM8996_DSP1DWC_NG_ENA_MASK              0x0100  /* DSP1DWC_NG_ENA */
#define WM8996_DSP1DWC_NG_ENA_SHIFT                  8  /* DSP1DWC_NG_ENA */
#define WM8996_DSP1DWC_NG_ENA_WIDTH                  1  /* DSP1DWC_NG_ENA */
#define WM8996_DSP1DWC_SIG_DET_MODE             0x0080  /* DSP1DWC_SIG_DET_MODE */
#define WM8996_DSP1DWC_SIG_DET_MODE_MASK        0x0080  /* DSP1DWC_SIG_DET_MODE */
#define WM8996_DSP1DWC_SIG_DET_MODE_SHIFT            7  /* DSP1DWC_SIG_DET_MODE */
#define WM8996_DSP1DWC_SIG_DET_MODE_WIDTH            1  /* DSP1DWC_SIG_DET_MODE */
#define WM8996_DSP1DWC_SIG_DET                  0x0040  /* DSP1DWC_SIG_DET */
#define WM8996_DSP1DWC_SIG_DET_MASK             0x0040  /* DSP1DWC_SIG_DET */
#define WM8996_DSP1DWC_SIG_DET_SHIFT                 6  /* DSP1DWC_SIG_DET */
#define WM8996_DSP1DWC_SIG_DET_WIDTH                 1  /* DSP1DWC_SIG_DET */
#define WM8996_DSP1DWC_KNEE2_OP_ENA             0x0020  /* DSP1DWC_KNEE2_OP_ENA */
#define WM8996_DSP1DWC_KNEE2_OP_ENA_MASK        0x0020  /* DSP1DWC_KNEE2_OP_ENA */
#define WM8996_DSP1DWC_KNEE2_OP_ENA_SHIFT            5  /* DSP1DWC_KNEE2_OP_ENA */
#define WM8996_DSP1DWC_KNEE2_OP_ENA_WIDTH            1  /* DSP1DWC_KNEE2_OP_ENA */
#define WM8996_DSP1DWC_QW                       0x0010  /* DSP1DWC_QW */
#define WM8996_DSP1DWC_QW_MASK                  0x0010  /* DSP1DWC_QW */
#define WM8996_DSP1DWC_QW_SHIFT                      4  /* DSP1DWC_QW */
#define WM8996_DSP1DWC_QW_WIDTH                      1  /* DSP1DWC_QW */
#define WM8996_DSP1DWC_ANTICWIP                 0x0008  /* DSP1DWC_ANTICWIP */
#define WM8996_DSP1DWC_ANTICWIP_MASK            0x0008  /* DSP1DWC_ANTICWIP */
#define WM8996_DSP1DWC_ANTICWIP_SHIFT                3  /* DSP1DWC_ANTICWIP */
#define WM8996_DSP1DWC_ANTICWIP_WIDTH                1  /* DSP1DWC_ANTICWIP */
#define WM8996_DSP1WX_DWC_ENA                   0x0004  /* DSP1WX_DWC_ENA */
#define WM8996_DSP1WX_DWC_ENA_MASK              0x0004  /* DSP1WX_DWC_ENA */
#define WM8996_DSP1WX_DWC_ENA_SHIFT                  2  /* DSP1WX_DWC_ENA */
#define WM8996_DSP1WX_DWC_ENA_WIDTH                  1  /* DSP1WX_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA                  0x0002  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_MASK             0x0002  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_SHIFT                 1  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_WIDTH                 1  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA                  0x0001  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_MASK             0x0001  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_SHIFT                 0  /* DSP1TXW_DWC_ENA */
#define WM8996_DSP1TXW_DWC_ENA_WIDTH                 1  /* DSP1TXW_DWC_ENA */

/*
 * W1089 (0x441) - DSP1 DWC (2)
 */
#define WM8996_DSP1DWC_ATK_MASK                 0x1E00  /* DSP1DWC_ATK - [12:9] */
#define WM8996_DSP1DWC_ATK_SHIFT                     9  /* DSP1DWC_ATK - [12:9] */
#define WM8996_DSP1DWC_ATK_WIDTH                     4  /* DSP1DWC_ATK - [12:9] */
#define WM8996_DSP1DWC_DCY_MASK                 0x01E0  /* DSP1DWC_DCY - [8:5] */
#define WM8996_DSP1DWC_DCY_SHIFT                     5  /* DSP1DWC_DCY - [8:5] */
#define WM8996_DSP1DWC_DCY_WIDTH                     4  /* DSP1DWC_DCY - [8:5] */
#define WM8996_DSP1DWC_MINGAIN_MASK             0x001C  /* DSP1DWC_MINGAIN - [4:2] */
#define WM8996_DSP1DWC_MINGAIN_SHIFT                 2  /* DSP1DWC_MINGAIN - [4:2] */
#define WM8996_DSP1DWC_MINGAIN_WIDTH                 3  /* DSP1DWC_MINGAIN - [4:2] */
#define WM8996_DSP1DWC_MAXGAIN_MASK             0x0003  /* DSP1DWC_MAXGAIN - [1:0] */
#define WM8996_DSP1DWC_MAXGAIN_SHIFT                 0  /* DSP1DWC_MAXGAIN - [1:0] */
#define WM8996_DSP1DWC_MAXGAIN_WIDTH                 2  /* DSP1DWC_MAXGAIN - [1:0] */

/*
 * W1090 (0x442) - DSP1 DWC (3)
 */
#define WM8996_DSP1DWC_NG_MINGAIN_MASK          0xF000  /* DSP1DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP1DWC_NG_MINGAIN_SHIFT             12  /* DSP1DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP1DWC_NG_MINGAIN_WIDTH              4  /* DSP1DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP1DWC_NG_EXP_MASK              0x0C00  /* DSP1DWC_NG_EXP - [11:10] */
#define WM8996_DSP1DWC_NG_EXP_SHIFT                 10  /* DSP1DWC_NG_EXP - [11:10] */
#define WM8996_DSP1DWC_NG_EXP_WIDTH                  2  /* DSP1DWC_NG_EXP - [11:10] */
#define WM8996_DSP1DWC_QW_THW_MASK              0x0300  /* DSP1DWC_QW_THW - [9:8] */
#define WM8996_DSP1DWC_QW_THW_SHIFT                  8  /* DSP1DWC_QW_THW - [9:8] */
#define WM8996_DSP1DWC_QW_THW_WIDTH                  2  /* DSP1DWC_QW_THW - [9:8] */
#define WM8996_DSP1DWC_QW_DCY_MASK              0x00C0  /* DSP1DWC_QW_DCY - [7:6] */
#define WM8996_DSP1DWC_QW_DCY_SHIFT                  6  /* DSP1DWC_QW_DCY - [7:6] */
#define WM8996_DSP1DWC_QW_DCY_WIDTH                  2  /* DSP1DWC_QW_DCY - [7:6] */
#define WM8996_DSP1DWC_HI_COMP_MASK             0x0038  /* DSP1DWC_HI_COMP - [5:3] */
#define WM8996_DSP1DWC_HI_COMP_SHIFT                 3  /* DSP1DWC_HI_COMP - [5:3] */
#define WM8996_DSP1DWC_HI_COMP_WIDTH                 3  /* DSP1DWC_HI_COMP - [5:3] */
#define WM8996_DSP1DWC_WO_COMP_MASK             0x0007  /* DSP1DWC_WO_COMP - [2:0] */
#define WM8996_DSP1DWC_WO_COMP_SHIFT                 0  /* DSP1DWC_WO_COMP - [2:0] */
#define WM8996_DSP1DWC_WO_COMP_WIDTH                 3  /* DSP1DWC_WO_COMP - [2:0] */

/*
 * W1091 (0x443) - DSP1 DWC (4)
 */
#define WM8996_DSP1DWC_KNEE_IP_MASK             0x07E0  /* DSP1DWC_KNEE_IP - [10:5] */
#define WM8996_DSP1DWC_KNEE_IP_SHIFT                 5  /* DSP1DWC_KNEE_IP - [10:5] */
#define WM8996_DSP1DWC_KNEE_IP_WIDTH                 6  /* DSP1DWC_KNEE_IP - [10:5] */
#define WM8996_DSP1DWC_KNEE_OP_MASK             0x001F  /* DSP1DWC_KNEE_OP - [4:0] */
#define WM8996_DSP1DWC_KNEE_OP_SHIFT                 0  /* DSP1DWC_KNEE_OP - [4:0] */
#define WM8996_DSP1DWC_KNEE_OP_WIDTH                 5  /* DSP1DWC_KNEE_OP - [4:0] */

/*
 * W1092 (0x444) - DSP1 DWC (5)
 */
#define WM8996_DSP1DWC_KNEE2_IP_MASK            0x03E0  /* DSP1DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP1DWC_KNEE2_IP_SHIFT                5  /* DSP1DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP1DWC_KNEE2_IP_WIDTH                5  /* DSP1DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP1DWC_KNEE2_OP_MASK            0x001F  /* DSP1DWC_KNEE2_OP - [4:0] */
#define WM8996_DSP1DWC_KNEE2_OP_SHIFT                0  /* DSP1DWC_KNEE2_OP - [4:0] */
#define WM8996_DSP1DWC_KNEE2_OP_WIDTH                5  /* DSP1DWC_KNEE2_OP - [4:0] */

/*
 * W1152 (0x480) - DSP1 WX EQ Gains (1)
 */
#define WM8996_DSP1WX_EQ_B1_GAIN_MASK           0xF800  /* DSP1WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B1_GAIN_SHIFT              11  /* DSP1WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B1_GAIN_WIDTH               5  /* DSP1WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B2_GAIN_MASK           0x07C0  /* DSP1WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP1WX_EQ_B2_GAIN_SHIFT               6  /* DSP1WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP1WX_EQ_B2_GAIN_WIDTH               5  /* DSP1WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP1WX_EQ_B3_GAIN_MASK           0x003E  /* DSP1WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP1WX_EQ_B3_GAIN_SHIFT               1  /* DSP1WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP1WX_EQ_B3_GAIN_WIDTH               5  /* DSP1WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP1WX_EQ_ENA                    0x0001  /* DSP1WX_EQ_ENA */
#define WM8996_DSP1WX_EQ_ENA_MASK               0x0001  /* DSP1WX_EQ_ENA */
#define WM8996_DSP1WX_EQ_ENA_SHIFT                   0  /* DSP1WX_EQ_ENA */
#define WM8996_DSP1WX_EQ_ENA_WIDTH                   1  /* DSP1WX_EQ_ENA */

/*
 * W1153 (0x481) - DSP1 WX EQ Gains (2)
 */
#define WM8996_DSP1WX_EQ_B4_GAIN_MASK           0xF800  /* DSP1WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B4_GAIN_SHIFT              11  /* DSP1WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B4_GAIN_WIDTH               5  /* DSP1WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP1WX_EQ_B5_GAIN_MASK           0x07C0  /* DSP1WX_EQ_B5_GAIN - [10:6] */
#define WM8996_DSP1WX_EQ_B5_GAIN_SHIFT               6  /* DSP1WX_EQ_B5_GAIN - [10:6] */
#define WM8996_DSP1WX_EQ_B5_GAIN_WIDTH               5  /* DSP1WX_EQ_B5_GAIN - [10:6] */

/*
 * W1154 (0x482) - DSP1 WX EQ Band 1 A
 */
#define WM8996_DSP1WX_EQ_B1_A_MASK              0xFFFF  /* DSP1WX_EQ_B1_A - [15:0] */
#define WM8996_DSP1WX_EQ_B1_A_SHIFT                  0  /* DSP1WX_EQ_B1_A - [15:0] */
#define WM8996_DSP1WX_EQ_B1_A_WIDTH                 16  /* DSP1WX_EQ_B1_A - [15:0] */

/*
 * W1155 (0x483) - DSP1 WX EQ Band 1 B
 */
#define WM8996_DSP1WX_EQ_B1_B_MASK              0xFFFF  /* DSP1WX_EQ_B1_B - [15:0] */
#define WM8996_DSP1WX_EQ_B1_B_SHIFT                  0  /* DSP1WX_EQ_B1_B - [15:0] */
#define WM8996_DSP1WX_EQ_B1_B_WIDTH                 16  /* DSP1WX_EQ_B1_B - [15:0] */

/*
 * W1156 (0x484) - DSP1 WX EQ Band 1 PG
 */
#define WM8996_DSP1WX_EQ_B1_PG_MASK             0xFFFF  /* DSP1WX_EQ_B1_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B1_PG_SHIFT                 0  /* DSP1WX_EQ_B1_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B1_PG_WIDTH                16  /* DSP1WX_EQ_B1_PG - [15:0] */

/*
 * W1157 (0x485) - DSP1 WX EQ Band 2 A
 */
#define WM8996_DSP1WX_EQ_B2_A_MASK              0xFFFF  /* DSP1WX_EQ_B2_A - [15:0] */
#define WM8996_DSP1WX_EQ_B2_A_SHIFT                  0  /* DSP1WX_EQ_B2_A - [15:0] */
#define WM8996_DSP1WX_EQ_B2_A_WIDTH                 16  /* DSP1WX_EQ_B2_A - [15:0] */

/*
 * W1158 (0x486) - DSP1 WX EQ Band 2 B
 */
#define WM8996_DSP1WX_EQ_B2_B_MASK              0xFFFF  /* DSP1WX_EQ_B2_B - [15:0] */
#define WM8996_DSP1WX_EQ_B2_B_SHIFT                  0  /* DSP1WX_EQ_B2_B - [15:0] */
#define WM8996_DSP1WX_EQ_B2_B_WIDTH                 16  /* DSP1WX_EQ_B2_B - [15:0] */

/*
 * W1159 (0x487) - DSP1 WX EQ Band 2 C
 */
#define WM8996_DSP1WX_EQ_B2_C_MASK              0xFFFF  /* DSP1WX_EQ_B2_C - [15:0] */
#define WM8996_DSP1WX_EQ_B2_C_SHIFT                  0  /* DSP1WX_EQ_B2_C - [15:0] */
#define WM8996_DSP1WX_EQ_B2_C_WIDTH                 16  /* DSP1WX_EQ_B2_C - [15:0] */

/*
 * W1160 (0x488) - DSP1 WX EQ Band 2 PG
 */
#define WM8996_DSP1WX_EQ_B2_PG_MASK             0xFFFF  /* DSP1WX_EQ_B2_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B2_PG_SHIFT                 0  /* DSP1WX_EQ_B2_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B2_PG_WIDTH                16  /* DSP1WX_EQ_B2_PG - [15:0] */

/*
 * W1161 (0x489) - DSP1 WX EQ Band 3 A
 */
#define WM8996_DSP1WX_EQ_B3_A_MASK              0xFFFF  /* DSP1WX_EQ_B3_A - [15:0] */
#define WM8996_DSP1WX_EQ_B3_A_SHIFT                  0  /* DSP1WX_EQ_B3_A - [15:0] */
#define WM8996_DSP1WX_EQ_B3_A_WIDTH                 16  /* DSP1WX_EQ_B3_A - [15:0] */

/*
 * W1162 (0x48A) - DSP1 WX EQ Band 3 B
 */
#define WM8996_DSP1WX_EQ_B3_B_MASK              0xFFFF  /* DSP1WX_EQ_B3_B - [15:0] */
#define WM8996_DSP1WX_EQ_B3_B_SHIFT                  0  /* DSP1WX_EQ_B3_B - [15:0] */
#define WM8996_DSP1WX_EQ_B3_B_WIDTH                 16  /* DSP1WX_EQ_B3_B - [15:0] */

/*
 * W1163 (0x48B) - DSP1 WX EQ Band 3 C
 */
#define WM8996_DSP1WX_EQ_B3_C_MASK              0xFFFF  /* DSP1WX_EQ_B3_C - [15:0] */
#define WM8996_DSP1WX_EQ_B3_C_SHIFT                  0  /* DSP1WX_EQ_B3_C - [15:0] */
#define WM8996_DSP1WX_EQ_B3_C_WIDTH                 16  /* DSP1WX_EQ_B3_C - [15:0] */

/*
 * W1164 (0x48C) - DSP1 WX EQ Band 3 PG
 */
#define WM8996_DSP1WX_EQ_B3_PG_MASK             0xFFFF  /* DSP1WX_EQ_B3_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B3_PG_SHIFT                 0  /* DSP1WX_EQ_B3_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B3_PG_WIDTH                16  /* DSP1WX_EQ_B3_PG - [15:0] */

/*
 * W1165 (0x48D) - DSP1 WX EQ Band 4 A
 */
#define WM8996_DSP1WX_EQ_B4_A_MASK              0xFFFF  /* DSP1WX_EQ_B4_A - [15:0] */
#define WM8996_DSP1WX_EQ_B4_A_SHIFT                  0  /* DSP1WX_EQ_B4_A - [15:0] */
#define WM8996_DSP1WX_EQ_B4_A_WIDTH                 16  /* DSP1WX_EQ_B4_A - [15:0] */

/*
 * W1166 (0x48E) - DSP1 WX EQ Band 4 B
 */
#define WM8996_DSP1WX_EQ_B4_B_MASK              0xFFFF  /* DSP1WX_EQ_B4_B - [15:0] */
#define WM8996_DSP1WX_EQ_B4_B_SHIFT                  0  /* DSP1WX_EQ_B4_B - [15:0] */
#define WM8996_DSP1WX_EQ_B4_B_WIDTH                 16  /* DSP1WX_EQ_B4_B - [15:0] */

/*
 * W1167 (0x48F) - DSP1 WX EQ Band 4 C
 */
#define WM8996_DSP1WX_EQ_B4_C_MASK              0xFFFF  /* DSP1WX_EQ_B4_C - [15:0] */
#define WM8996_DSP1WX_EQ_B4_C_SHIFT                  0  /* DSP1WX_EQ_B4_C - [15:0] */
#define WM8996_DSP1WX_EQ_B4_C_WIDTH                 16  /* DSP1WX_EQ_B4_C - [15:0] */

/*
 * W1168 (0x490) - DSP1 WX EQ Band 4 PG
 */
#define WM8996_DSP1WX_EQ_B4_PG_MASK             0xFFFF  /* DSP1WX_EQ_B4_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B4_PG_SHIFT                 0  /* DSP1WX_EQ_B4_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B4_PG_WIDTH                16  /* DSP1WX_EQ_B4_PG - [15:0] */

/*
 * W1169 (0x491) - DSP1 WX EQ Band 5 A
 */
#define WM8996_DSP1WX_EQ_B5_A_MASK              0xFFFF  /* DSP1WX_EQ_B5_A - [15:0] */
#define WM8996_DSP1WX_EQ_B5_A_SHIFT                  0  /* DSP1WX_EQ_B5_A - [15:0] */
#define WM8996_DSP1WX_EQ_B5_A_WIDTH                 16  /* DSP1WX_EQ_B5_A - [15:0] */

/*
 * W1170 (0x492) - DSP1 WX EQ Band 5 B
 */
#define WM8996_DSP1WX_EQ_B5_B_MASK              0xFFFF  /* DSP1WX_EQ_B5_B - [15:0] */
#define WM8996_DSP1WX_EQ_B5_B_SHIFT                  0  /* DSP1WX_EQ_B5_B - [15:0] */
#define WM8996_DSP1WX_EQ_B5_B_WIDTH                 16  /* DSP1WX_EQ_B5_B - [15:0] */

/*
 * W1171 (0x493) - DSP1 WX EQ Band 5 PG
 */
#define WM8996_DSP1WX_EQ_B5_PG_MASK             0xFFFF  /* DSP1WX_EQ_B5_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B5_PG_SHIFT                 0  /* DSP1WX_EQ_B5_PG - [15:0] */
#define WM8996_DSP1WX_EQ_B5_PG_WIDTH                16  /* DSP1WX_EQ_B5_PG - [15:0] */

/*
 * W1280 (0x500) - DSP2 TX Weft Vowume
 */
#define WM8996_DSP2TX_VU                        0x0100  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_MASK                   0x0100  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_SHIFT                       8  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_WIDTH                       1  /* DSP2TX_VU */
#define WM8996_DSP2TXW_VOW_MASK                 0x00FF  /* DSP2TXW_VOW - [7:0] */
#define WM8996_DSP2TXW_VOW_SHIFT                     0  /* DSP2TXW_VOW - [7:0] */
#define WM8996_DSP2TXW_VOW_WIDTH                     8  /* DSP2TXW_VOW - [7:0] */

/*
 * W1281 (0x501) - DSP2 TX Wight Vowume
 */
#define WM8996_DSP2TX_VU                        0x0100  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_MASK                   0x0100  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_SHIFT                       8  /* DSP2TX_VU */
#define WM8996_DSP2TX_VU_WIDTH                       1  /* DSP2TX_VU */
#define WM8996_DSP2TXW_VOW_MASK                 0x00FF  /* DSP2TXW_VOW - [7:0] */
#define WM8996_DSP2TXW_VOW_SHIFT                     0  /* DSP2TXW_VOW - [7:0] */
#define WM8996_DSP2TXW_VOW_WIDTH                     8  /* DSP2TXW_VOW - [7:0] */

/*
 * W1282 (0x502) - DSP2 WX Weft Vowume
 */
#define WM8996_DSP2WX_VU                        0x0100  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_MASK                   0x0100  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_SHIFT                       8  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_WIDTH                       1  /* DSP2WX_VU */
#define WM8996_DSP2WXW_VOW_MASK                 0x00FF  /* DSP2WXW_VOW - [7:0] */
#define WM8996_DSP2WXW_VOW_SHIFT                     0  /* DSP2WXW_VOW - [7:0] */
#define WM8996_DSP2WXW_VOW_WIDTH                     8  /* DSP2WXW_VOW - [7:0] */

/*
 * W1283 (0x503) - DSP2 WX Wight Vowume
 */
#define WM8996_DSP2WX_VU                        0x0100  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_MASK                   0x0100  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_SHIFT                       8  /* DSP2WX_VU */
#define WM8996_DSP2WX_VU_WIDTH                       1  /* DSP2WX_VU */
#define WM8996_DSP2WXW_VOW_MASK                 0x00FF  /* DSP2WXW_VOW - [7:0] */
#define WM8996_DSP2WXW_VOW_SHIFT                     0  /* DSP2WXW_VOW - [7:0] */
#define WM8996_DSP2WXW_VOW_WIDTH                     8  /* DSP2WXW_VOW - [7:0] */

/*
 * W1296 (0x510) - DSP2 TX Fiwtews
 */
#define WM8996_DSP2TX_NF                        0x2000  /* DSP2TX_NF */
#define WM8996_DSP2TX_NF_MASK                   0x2000  /* DSP2TX_NF */
#define WM8996_DSP2TX_NF_SHIFT                      13  /* DSP2TX_NF */
#define WM8996_DSP2TX_NF_WIDTH                       1  /* DSP2TX_NF */
#define WM8996_DSP2TXW_HPF                      0x1000  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_MASK                 0x1000  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_SHIFT                    12  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_WIDTH                     1  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF                      0x0800  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_MASK                 0x0800  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_SHIFT                    11  /* DSP2TXW_HPF */
#define WM8996_DSP2TXW_HPF_WIDTH                     1  /* DSP2TXW_HPF */
#define WM8996_DSP2TX_HPF_MODE_MASK             0x0018  /* DSP2TX_HPF_MODE - [4:3] */
#define WM8996_DSP2TX_HPF_MODE_SHIFT                 3  /* DSP2TX_HPF_MODE - [4:3] */
#define WM8996_DSP2TX_HPF_MODE_WIDTH                 2  /* DSP2TX_HPF_MODE - [4:3] */
#define WM8996_DSP2TX_HPF_CUT_MASK              0x0007  /* DSP2TX_HPF_CUT - [2:0] */
#define WM8996_DSP2TX_HPF_CUT_SHIFT                  0  /* DSP2TX_HPF_CUT - [2:0] */
#define WM8996_DSP2TX_HPF_CUT_WIDTH                  3  /* DSP2TX_HPF_CUT - [2:0] */

/*
 * W1312 (0x520) - DSP2 WX Fiwtews (1)
 */
#define WM8996_DSP2WX_MUTE                      0x0200  /* DSP2WX_MUTE */
#define WM8996_DSP2WX_MUTE_MASK                 0x0200  /* DSP2WX_MUTE */
#define WM8996_DSP2WX_MUTE_SHIFT                     9  /* DSP2WX_MUTE */
#define WM8996_DSP2WX_MUTE_WIDTH                     1  /* DSP2WX_MUTE */
#define WM8996_DSP2WX_MONO                      0x0080  /* DSP2WX_MONO */
#define WM8996_DSP2WX_MONO_MASK                 0x0080  /* DSP2WX_MONO */
#define WM8996_DSP2WX_MONO_SHIFT                     7  /* DSP2WX_MONO */
#define WM8996_DSP2WX_MONO_WIDTH                     1  /* DSP2WX_MONO */
#define WM8996_DSP2WX_MUTEWATE                  0x0020  /* DSP2WX_MUTEWATE */
#define WM8996_DSP2WX_MUTEWATE_MASK             0x0020  /* DSP2WX_MUTEWATE */
#define WM8996_DSP2WX_MUTEWATE_SHIFT                 5  /* DSP2WX_MUTEWATE */
#define WM8996_DSP2WX_MUTEWATE_WIDTH                 1  /* DSP2WX_MUTEWATE */
#define WM8996_DSP2WX_UNMUTE_WAMP               0x0010  /* DSP2WX_UNMUTE_WAMP */
#define WM8996_DSP2WX_UNMUTE_WAMP_MASK          0x0010  /* DSP2WX_UNMUTE_WAMP */
#define WM8996_DSP2WX_UNMUTE_WAMP_SHIFT              4  /* DSP2WX_UNMUTE_WAMP */
#define WM8996_DSP2WX_UNMUTE_WAMP_WIDTH              1  /* DSP2WX_UNMUTE_WAMP */

/*
 * W1313 (0x521) - DSP2 WX Fiwtews (2)
 */
#define WM8996_DSP2WX_3D_GAIN_MASK              0x3E00  /* DSP2WX_3D_GAIN - [13:9] */
#define WM8996_DSP2WX_3D_GAIN_SHIFT                  9  /* DSP2WX_3D_GAIN - [13:9] */
#define WM8996_DSP2WX_3D_GAIN_WIDTH                  5  /* DSP2WX_3D_GAIN - [13:9] */
#define WM8996_DSP2WX_3D_ENA                    0x0100  /* DSP2WX_3D_ENA */
#define WM8996_DSP2WX_3D_ENA_MASK               0x0100  /* DSP2WX_3D_ENA */
#define WM8996_DSP2WX_3D_ENA_SHIFT                   8  /* DSP2WX_3D_ENA */
#define WM8996_DSP2WX_3D_ENA_WIDTH                   1  /* DSP2WX_3D_ENA */

/*
 * W1344 (0x540) - DSP2 DWC (1)
 */
#define WM8996_DSP2DWC_SIG_DET_WMS_MASK         0xF800  /* DSP2DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP2DWC_SIG_DET_WMS_SHIFT            11  /* DSP2DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP2DWC_SIG_DET_WMS_WIDTH             5  /* DSP2DWC_SIG_DET_WMS - [15:11] */
#define WM8996_DSP2DWC_SIG_DET_PK_MASK          0x0600  /* DSP2DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP2DWC_SIG_DET_PK_SHIFT              9  /* DSP2DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP2DWC_SIG_DET_PK_WIDTH              2  /* DSP2DWC_SIG_DET_PK - [10:9] */
#define WM8996_DSP2DWC_NG_ENA                   0x0100  /* DSP2DWC_NG_ENA */
#define WM8996_DSP2DWC_NG_ENA_MASK              0x0100  /* DSP2DWC_NG_ENA */
#define WM8996_DSP2DWC_NG_ENA_SHIFT                  8  /* DSP2DWC_NG_ENA */
#define WM8996_DSP2DWC_NG_ENA_WIDTH                  1  /* DSP2DWC_NG_ENA */
#define WM8996_DSP2DWC_SIG_DET_MODE             0x0080  /* DSP2DWC_SIG_DET_MODE */
#define WM8996_DSP2DWC_SIG_DET_MODE_MASK        0x0080  /* DSP2DWC_SIG_DET_MODE */
#define WM8996_DSP2DWC_SIG_DET_MODE_SHIFT            7  /* DSP2DWC_SIG_DET_MODE */
#define WM8996_DSP2DWC_SIG_DET_MODE_WIDTH            1  /* DSP2DWC_SIG_DET_MODE */
#define WM8996_DSP2DWC_SIG_DET                  0x0040  /* DSP2DWC_SIG_DET */
#define WM8996_DSP2DWC_SIG_DET_MASK             0x0040  /* DSP2DWC_SIG_DET */
#define WM8996_DSP2DWC_SIG_DET_SHIFT                 6  /* DSP2DWC_SIG_DET */
#define WM8996_DSP2DWC_SIG_DET_WIDTH                 1  /* DSP2DWC_SIG_DET */
#define WM8996_DSP2DWC_KNEE2_OP_ENA             0x0020  /* DSP2DWC_KNEE2_OP_ENA */
#define WM8996_DSP2DWC_KNEE2_OP_ENA_MASK        0x0020  /* DSP2DWC_KNEE2_OP_ENA */
#define WM8996_DSP2DWC_KNEE2_OP_ENA_SHIFT            5  /* DSP2DWC_KNEE2_OP_ENA */
#define WM8996_DSP2DWC_KNEE2_OP_ENA_WIDTH            1  /* DSP2DWC_KNEE2_OP_ENA */
#define WM8996_DSP2DWC_QW                       0x0010  /* DSP2DWC_QW */
#define WM8996_DSP2DWC_QW_MASK                  0x0010  /* DSP2DWC_QW */
#define WM8996_DSP2DWC_QW_SHIFT                      4  /* DSP2DWC_QW */
#define WM8996_DSP2DWC_QW_WIDTH                      1  /* DSP2DWC_QW */
#define WM8996_DSP2DWC_ANTICWIP                 0x0008  /* DSP2DWC_ANTICWIP */
#define WM8996_DSP2DWC_ANTICWIP_MASK            0x0008  /* DSP2DWC_ANTICWIP */
#define WM8996_DSP2DWC_ANTICWIP_SHIFT                3  /* DSP2DWC_ANTICWIP */
#define WM8996_DSP2DWC_ANTICWIP_WIDTH                1  /* DSP2DWC_ANTICWIP */
#define WM8996_DSP2WX_DWC_ENA                   0x0004  /* DSP2WX_DWC_ENA */
#define WM8996_DSP2WX_DWC_ENA_MASK              0x0004  /* DSP2WX_DWC_ENA */
#define WM8996_DSP2WX_DWC_ENA_SHIFT                  2  /* DSP2WX_DWC_ENA */
#define WM8996_DSP2WX_DWC_ENA_WIDTH                  1  /* DSP2WX_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA                  0x0002  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_MASK             0x0002  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_SHIFT                 1  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_WIDTH                 1  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA                  0x0001  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_MASK             0x0001  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_SHIFT                 0  /* DSP2TXW_DWC_ENA */
#define WM8996_DSP2TXW_DWC_ENA_WIDTH                 1  /* DSP2TXW_DWC_ENA */

/*
 * W1345 (0x541) - DSP2 DWC (2)
 */
#define WM8996_DSP2DWC_ATK_MASK                 0x1E00  /* DSP2DWC_ATK - [12:9] */
#define WM8996_DSP2DWC_ATK_SHIFT                     9  /* DSP2DWC_ATK - [12:9] */
#define WM8996_DSP2DWC_ATK_WIDTH                     4  /* DSP2DWC_ATK - [12:9] */
#define WM8996_DSP2DWC_DCY_MASK                 0x01E0  /* DSP2DWC_DCY - [8:5] */
#define WM8996_DSP2DWC_DCY_SHIFT                     5  /* DSP2DWC_DCY - [8:5] */
#define WM8996_DSP2DWC_DCY_WIDTH                     4  /* DSP2DWC_DCY - [8:5] */
#define WM8996_DSP2DWC_MINGAIN_MASK             0x001C  /* DSP2DWC_MINGAIN - [4:2] */
#define WM8996_DSP2DWC_MINGAIN_SHIFT                 2  /* DSP2DWC_MINGAIN - [4:2] */
#define WM8996_DSP2DWC_MINGAIN_WIDTH                 3  /* DSP2DWC_MINGAIN - [4:2] */
#define WM8996_DSP2DWC_MAXGAIN_MASK             0x0003  /* DSP2DWC_MAXGAIN - [1:0] */
#define WM8996_DSP2DWC_MAXGAIN_SHIFT                 0  /* DSP2DWC_MAXGAIN - [1:0] */
#define WM8996_DSP2DWC_MAXGAIN_WIDTH                 2  /* DSP2DWC_MAXGAIN - [1:0] */

/*
 * W1346 (0x542) - DSP2 DWC (3)
 */
#define WM8996_DSP2DWC_NG_MINGAIN_MASK          0xF000  /* DSP2DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP2DWC_NG_MINGAIN_SHIFT             12  /* DSP2DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP2DWC_NG_MINGAIN_WIDTH              4  /* DSP2DWC_NG_MINGAIN - [15:12] */
#define WM8996_DSP2DWC_NG_EXP_MASK              0x0C00  /* DSP2DWC_NG_EXP - [11:10] */
#define WM8996_DSP2DWC_NG_EXP_SHIFT                 10  /* DSP2DWC_NG_EXP - [11:10] */
#define WM8996_DSP2DWC_NG_EXP_WIDTH                  2  /* DSP2DWC_NG_EXP - [11:10] */
#define WM8996_DSP2DWC_QW_THW_MASK              0x0300  /* DSP2DWC_QW_THW - [9:8] */
#define WM8996_DSP2DWC_QW_THW_SHIFT                  8  /* DSP2DWC_QW_THW - [9:8] */
#define WM8996_DSP2DWC_QW_THW_WIDTH                  2  /* DSP2DWC_QW_THW - [9:8] */
#define WM8996_DSP2DWC_QW_DCY_MASK              0x00C0  /* DSP2DWC_QW_DCY - [7:6] */
#define WM8996_DSP2DWC_QW_DCY_SHIFT                  6  /* DSP2DWC_QW_DCY - [7:6] */
#define WM8996_DSP2DWC_QW_DCY_WIDTH                  2  /* DSP2DWC_QW_DCY - [7:6] */
#define WM8996_DSP2DWC_HI_COMP_MASK             0x0038  /* DSP2DWC_HI_COMP - [5:3] */
#define WM8996_DSP2DWC_HI_COMP_SHIFT                 3  /* DSP2DWC_HI_COMP - [5:3] */
#define WM8996_DSP2DWC_HI_COMP_WIDTH                 3  /* DSP2DWC_HI_COMP - [5:3] */
#define WM8996_DSP2DWC_WO_COMP_MASK             0x0007  /* DSP2DWC_WO_COMP - [2:0] */
#define WM8996_DSP2DWC_WO_COMP_SHIFT                 0  /* DSP2DWC_WO_COMP - [2:0] */
#define WM8996_DSP2DWC_WO_COMP_WIDTH                 3  /* DSP2DWC_WO_COMP - [2:0] */

/*
 * W1347 (0x543) - DSP2 DWC (4)
 */
#define WM8996_DSP2DWC_KNEE_IP_MASK             0x07E0  /* DSP2DWC_KNEE_IP - [10:5] */
#define WM8996_DSP2DWC_KNEE_IP_SHIFT                 5  /* DSP2DWC_KNEE_IP - [10:5] */
#define WM8996_DSP2DWC_KNEE_IP_WIDTH                 6  /* DSP2DWC_KNEE_IP - [10:5] */
#define WM8996_DSP2DWC_KNEE_OP_MASK             0x001F  /* DSP2DWC_KNEE_OP - [4:0] */
#define WM8996_DSP2DWC_KNEE_OP_SHIFT                 0  /* DSP2DWC_KNEE_OP - [4:0] */
#define WM8996_DSP2DWC_KNEE_OP_WIDTH                 5  /* DSP2DWC_KNEE_OP - [4:0] */

/*
 * W1348 (0x544) - DSP2 DWC (5)
 */
#define WM8996_DSP2DWC_KNEE2_IP_MASK            0x03E0  /* DSP2DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP2DWC_KNEE2_IP_SHIFT                5  /* DSP2DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP2DWC_KNEE2_IP_WIDTH                5  /* DSP2DWC_KNEE2_IP - [9:5] */
#define WM8996_DSP2DWC_KNEE2_OP_MASK            0x001F  /* DSP2DWC_KNEE2_OP - [4:0] */
#define WM8996_DSP2DWC_KNEE2_OP_SHIFT                0  /* DSP2DWC_KNEE2_OP - [4:0] */
#define WM8996_DSP2DWC_KNEE2_OP_WIDTH                5  /* DSP2DWC_KNEE2_OP - [4:0] */

/*
 * W1408 (0x580) - DSP2 WX EQ Gains (1)
 */
#define WM8996_DSP2WX_EQ_B1_GAIN_MASK           0xF800  /* DSP2WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B1_GAIN_SHIFT              11  /* DSP2WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B1_GAIN_WIDTH               5  /* DSP2WX_EQ_B1_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B2_GAIN_MASK           0x07C0  /* DSP2WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP2WX_EQ_B2_GAIN_SHIFT               6  /* DSP2WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP2WX_EQ_B2_GAIN_WIDTH               5  /* DSP2WX_EQ_B2_GAIN - [10:6] */
#define WM8996_DSP2WX_EQ_B3_GAIN_MASK           0x003E  /* DSP2WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP2WX_EQ_B3_GAIN_SHIFT               1  /* DSP2WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP2WX_EQ_B3_GAIN_WIDTH               5  /* DSP2WX_EQ_B3_GAIN - [5:1] */
#define WM8996_DSP2WX_EQ_ENA                    0x0001  /* DSP2WX_EQ_ENA */
#define WM8996_DSP2WX_EQ_ENA_MASK               0x0001  /* DSP2WX_EQ_ENA */
#define WM8996_DSP2WX_EQ_ENA_SHIFT                   0  /* DSP2WX_EQ_ENA */
#define WM8996_DSP2WX_EQ_ENA_WIDTH                   1  /* DSP2WX_EQ_ENA */

/*
 * W1409 (0x581) - DSP2 WX EQ Gains (2)
 */
#define WM8996_DSP2WX_EQ_B4_GAIN_MASK           0xF800  /* DSP2WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B4_GAIN_SHIFT              11  /* DSP2WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B4_GAIN_WIDTH               5  /* DSP2WX_EQ_B4_GAIN - [15:11] */
#define WM8996_DSP2WX_EQ_B5_GAIN_MASK           0x07C0  /* DSP2WX_EQ_B5_GAIN - [10:6] */
#define WM8996_DSP2WX_EQ_B5_GAIN_SHIFT               6  /* DSP2WX_EQ_B5_GAIN - [10:6] */
#define WM8996_DSP2WX_EQ_B5_GAIN_WIDTH               5  /* DSP2WX_EQ_B5_GAIN - [10:6] */

/*
 * W1410 (0x582) - DSP2 WX EQ Band 1 A
 */
#define WM8996_DSP2WX_EQ_B1_A_MASK              0xFFFF  /* DSP2WX_EQ_B1_A - [15:0] */
#define WM8996_DSP2WX_EQ_B1_A_SHIFT                  0  /* DSP2WX_EQ_B1_A - [15:0] */
#define WM8996_DSP2WX_EQ_B1_A_WIDTH                 16  /* DSP2WX_EQ_B1_A - [15:0] */

/*
 * W1411 (0x583) - DSP2 WX EQ Band 1 B
 */
#define WM8996_DSP2WX_EQ_B1_B_MASK              0xFFFF  /* DSP2WX_EQ_B1_B - [15:0] */
#define WM8996_DSP2WX_EQ_B1_B_SHIFT                  0  /* DSP2WX_EQ_B1_B - [15:0] */
#define WM8996_DSP2WX_EQ_B1_B_WIDTH                 16  /* DSP2WX_EQ_B1_B - [15:0] */

/*
 * W1412 (0x584) - DSP2 WX EQ Band 1 PG
 */
#define WM8996_DSP2WX_EQ_B1_PG_MASK             0xFFFF  /* DSP2WX_EQ_B1_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B1_PG_SHIFT                 0  /* DSP2WX_EQ_B1_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B1_PG_WIDTH                16  /* DSP2WX_EQ_B1_PG - [15:0] */

/*
 * W1413 (0x585) - DSP2 WX EQ Band 2 A
 */
#define WM8996_DSP2WX_EQ_B2_A_MASK              0xFFFF  /* DSP2WX_EQ_B2_A - [15:0] */
#define WM8996_DSP2WX_EQ_B2_A_SHIFT                  0  /* DSP2WX_EQ_B2_A - [15:0] */
#define WM8996_DSP2WX_EQ_B2_A_WIDTH                 16  /* DSP2WX_EQ_B2_A - [15:0] */

/*
 * W1414 (0x586) - DSP2 WX EQ Band 2 B
 */
#define WM8996_DSP2WX_EQ_B2_B_MASK              0xFFFF  /* DSP2WX_EQ_B2_B - [15:0] */
#define WM8996_DSP2WX_EQ_B2_B_SHIFT                  0  /* DSP2WX_EQ_B2_B - [15:0] */
#define WM8996_DSP2WX_EQ_B2_B_WIDTH                 16  /* DSP2WX_EQ_B2_B - [15:0] */

/*
 * W1415 (0x587) - DSP2 WX EQ Band 2 C
 */
#define WM8996_DSP2WX_EQ_B2_C_MASK              0xFFFF  /* DSP2WX_EQ_B2_C - [15:0] */
#define WM8996_DSP2WX_EQ_B2_C_SHIFT                  0  /* DSP2WX_EQ_B2_C - [15:0] */
#define WM8996_DSP2WX_EQ_B2_C_WIDTH                 16  /* DSP2WX_EQ_B2_C - [15:0] */

/*
 * W1416 (0x588) - DSP2 WX EQ Band 2 PG
 */
#define WM8996_DSP2WX_EQ_B2_PG_MASK             0xFFFF  /* DSP2WX_EQ_B2_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B2_PG_SHIFT                 0  /* DSP2WX_EQ_B2_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B2_PG_WIDTH                16  /* DSP2WX_EQ_B2_PG - [15:0] */

/*
 * W1417 (0x589) - DSP2 WX EQ Band 3 A
 */
#define WM8996_DSP2WX_EQ_B3_A_MASK              0xFFFF  /* DSP2WX_EQ_B3_A - [15:0] */
#define WM8996_DSP2WX_EQ_B3_A_SHIFT                  0  /* DSP2WX_EQ_B3_A - [15:0] */
#define WM8996_DSP2WX_EQ_B3_A_WIDTH                 16  /* DSP2WX_EQ_B3_A - [15:0] */

/*
 * W1418 (0x58A) - DSP2 WX EQ Band 3 B
 */
#define WM8996_DSP2WX_EQ_B3_B_MASK              0xFFFF  /* DSP2WX_EQ_B3_B - [15:0] */
#define WM8996_DSP2WX_EQ_B3_B_SHIFT                  0  /* DSP2WX_EQ_B3_B - [15:0] */
#define WM8996_DSP2WX_EQ_B3_B_WIDTH                 16  /* DSP2WX_EQ_B3_B - [15:0] */

/*
 * W1419 (0x58B) - DSP2 WX EQ Band 3 C
 */
#define WM8996_DSP2WX_EQ_B3_C_MASK              0xFFFF  /* DSP2WX_EQ_B3_C - [15:0] */
#define WM8996_DSP2WX_EQ_B3_C_SHIFT                  0  /* DSP2WX_EQ_B3_C - [15:0] */
#define WM8996_DSP2WX_EQ_B3_C_WIDTH                 16  /* DSP2WX_EQ_B3_C - [15:0] */

/*
 * W1420 (0x58C) - DSP2 WX EQ Band 3 PG
 */
#define WM8996_DSP2WX_EQ_B3_PG_MASK             0xFFFF  /* DSP2WX_EQ_B3_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B3_PG_SHIFT                 0  /* DSP2WX_EQ_B3_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B3_PG_WIDTH                16  /* DSP2WX_EQ_B3_PG - [15:0] */

/*
 * W1421 (0x58D) - DSP2 WX EQ Band 4 A
 */
#define WM8996_DSP2WX_EQ_B4_A_MASK              0xFFFF  /* DSP2WX_EQ_B4_A - [15:0] */
#define WM8996_DSP2WX_EQ_B4_A_SHIFT                  0  /* DSP2WX_EQ_B4_A - [15:0] */
#define WM8996_DSP2WX_EQ_B4_A_WIDTH                 16  /* DSP2WX_EQ_B4_A - [15:0] */

/*
 * W1422 (0x58E) - DSP2 WX EQ Band 4 B
 */
#define WM8996_DSP2WX_EQ_B4_B_MASK              0xFFFF  /* DSP2WX_EQ_B4_B - [15:0] */
#define WM8996_DSP2WX_EQ_B4_B_SHIFT                  0  /* DSP2WX_EQ_B4_B - [15:0] */
#define WM8996_DSP2WX_EQ_B4_B_WIDTH                 16  /* DSP2WX_EQ_B4_B - [15:0] */

/*
 * W1423 (0x58F) - DSP2 WX EQ Band 4 C
 */
#define WM8996_DSP2WX_EQ_B4_C_MASK              0xFFFF  /* DSP2WX_EQ_B4_C - [15:0] */
#define WM8996_DSP2WX_EQ_B4_C_SHIFT                  0  /* DSP2WX_EQ_B4_C - [15:0] */
#define WM8996_DSP2WX_EQ_B4_C_WIDTH                 16  /* DSP2WX_EQ_B4_C - [15:0] */

/*
 * W1424 (0x590) - DSP2 WX EQ Band 4 PG
 */
#define WM8996_DSP2WX_EQ_B4_PG_MASK             0xFFFF  /* DSP2WX_EQ_B4_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B4_PG_SHIFT                 0  /* DSP2WX_EQ_B4_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B4_PG_WIDTH                16  /* DSP2WX_EQ_B4_PG - [15:0] */

/*
 * W1425 (0x591) - DSP2 WX EQ Band 5 A
 */
#define WM8996_DSP2WX_EQ_B5_A_MASK              0xFFFF  /* DSP2WX_EQ_B5_A - [15:0] */
#define WM8996_DSP2WX_EQ_B5_A_SHIFT                  0  /* DSP2WX_EQ_B5_A - [15:0] */
#define WM8996_DSP2WX_EQ_B5_A_WIDTH                 16  /* DSP2WX_EQ_B5_A - [15:0] */

/*
 * W1426 (0x592) - DSP2 WX EQ Band 5 B
 */
#define WM8996_DSP2WX_EQ_B5_B_MASK              0xFFFF  /* DSP2WX_EQ_B5_B - [15:0] */
#define WM8996_DSP2WX_EQ_B5_B_SHIFT                  0  /* DSP2WX_EQ_B5_B - [15:0] */
#define WM8996_DSP2WX_EQ_B5_B_WIDTH                 16  /* DSP2WX_EQ_B5_B - [15:0] */

/*
 * W1427 (0x593) - DSP2 WX EQ Band 5 PG
 */
#define WM8996_DSP2WX_EQ_B5_PG_MASK             0xFFFF  /* DSP2WX_EQ_B5_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B5_PG_SHIFT                 0  /* DSP2WX_EQ_B5_PG - [15:0] */
#define WM8996_DSP2WX_EQ_B5_PG_WIDTH                16  /* DSP2WX_EQ_B5_PG - [15:0] */

/*
 * W1536 (0x600) - DAC1 Mixew Vowumes
 */
#define WM8996_ADCW_DAC1_VOW_MASK               0x03E0  /* ADCW_DAC1_VOW - [9:5] */
#define WM8996_ADCW_DAC1_VOW_SHIFT                   5  /* ADCW_DAC1_VOW - [9:5] */
#define WM8996_ADCW_DAC1_VOW_WIDTH                   5  /* ADCW_DAC1_VOW - [9:5] */
#define WM8996_ADCW_DAC1_VOW_MASK               0x001F  /* ADCW_DAC1_VOW - [4:0] */
#define WM8996_ADCW_DAC1_VOW_SHIFT                   0  /* ADCW_DAC1_VOW - [4:0] */
#define WM8996_ADCW_DAC1_VOW_WIDTH                   5  /* ADCW_DAC1_VOW - [4:0] */

/*
 * W1537 (0x601) - DAC1 Weft Mixew Wouting
 */
#define WM8996_ADCW_TO_DAC1W                    0x0020  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_MASK               0x0020  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_SHIFT                   5  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_WIDTH                   1  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W                    0x0010  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_MASK               0x0010  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_SHIFT                   4  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_WIDTH                   1  /* ADCW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W                 0x0002  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_MASK            0x0002  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_SHIFT                1  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_WIDTH                1  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W                 0x0001  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_MASK            0x0001  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_SHIFT                0  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_WIDTH                1  /* DSP1WXW_TO_DAC1W */

/*
 * W1538 (0x602) - DAC1 Wight Mixew Wouting
 */
#define WM8996_ADCW_TO_DAC1W                    0x0020  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_MASK               0x0020  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_SHIFT                   5  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_WIDTH                   1  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W                    0x0010  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_MASK               0x0010  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_SHIFT                   4  /* ADCW_TO_DAC1W */
#define WM8996_ADCW_TO_DAC1W_WIDTH                   1  /* ADCW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W                 0x0002  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_MASK            0x0002  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_SHIFT                1  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP2WXW_TO_DAC1W_WIDTH                1  /* DSP2WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W                 0x0001  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_MASK            0x0001  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_SHIFT                0  /* DSP1WXW_TO_DAC1W */
#define WM8996_DSP1WXW_TO_DAC1W_WIDTH                1  /* DSP1WXW_TO_DAC1W */

/*
 * W1539 (0x603) - DAC2 Mixew Vowumes
 */
#define WM8996_ADCW_DAC2_VOW_MASK               0x03E0  /* ADCW_DAC2_VOW - [9:5] */
#define WM8996_ADCW_DAC2_VOW_SHIFT                   5  /* ADCW_DAC2_VOW - [9:5] */
#define WM8996_ADCW_DAC2_VOW_WIDTH                   5  /* ADCW_DAC2_VOW - [9:5] */
#define WM8996_ADCW_DAC2_VOW_MASK               0x001F  /* ADCW_DAC2_VOW - [4:0] */
#define WM8996_ADCW_DAC2_VOW_SHIFT                   0  /* ADCW_DAC2_VOW - [4:0] */
#define WM8996_ADCW_DAC2_VOW_WIDTH                   5  /* ADCW_DAC2_VOW - [4:0] */

/*
 * W1540 (0x604) - DAC2 Weft Mixew Wouting
 */
#define WM8996_ADCW_TO_DAC2W                    0x0020  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_MASK               0x0020  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_SHIFT                   5  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_WIDTH                   1  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W                    0x0010  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_MASK               0x0010  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_SHIFT                   4  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_WIDTH                   1  /* ADCW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W                 0x0002  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_MASK            0x0002  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_SHIFT                1  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_WIDTH                1  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W                 0x0001  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_MASK            0x0001  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_SHIFT                0  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_WIDTH                1  /* DSP1WXW_TO_DAC2W */

/*
 * W1541 (0x605) - DAC2 Wight Mixew Wouting
 */
#define WM8996_ADCW_TO_DAC2W                    0x0020  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_MASK               0x0020  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_SHIFT                   5  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_WIDTH                   1  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W                    0x0010  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_MASK               0x0010  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_SHIFT                   4  /* ADCW_TO_DAC2W */
#define WM8996_ADCW_TO_DAC2W_WIDTH                   1  /* ADCW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W                 0x0002  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_MASK            0x0002  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_SHIFT                1  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP2WXW_TO_DAC2W_WIDTH                1  /* DSP2WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W                 0x0001  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_MASK            0x0001  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_SHIFT                0  /* DSP1WXW_TO_DAC2W */
#define WM8996_DSP1WXW_TO_DAC2W_WIDTH                1  /* DSP1WXW_TO_DAC2W */

/*
 * W1542 (0x606) - DSP1 TX Weft Mixew Wouting
 */
#define WM8996_ADC1W_TO_DSP1TXW                 0x0002  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_MASK            0x0002  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_SHIFT                1  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_WIDTH                1  /* ADC1W_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW                  0x0001  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_MASK             0x0001  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_SHIFT                 0  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_WIDTH                 1  /* DACW_TO_DSP1TXW */

/*
 * W1543 (0x607) - DSP1 TX Wight Mixew Wouting
 */
#define WM8996_ADC1W_TO_DSP1TXW                 0x0002  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_MASK            0x0002  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_SHIFT                1  /* ADC1W_TO_DSP1TXW */
#define WM8996_ADC1W_TO_DSP1TXW_WIDTH                1  /* ADC1W_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW                  0x0001  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_MASK             0x0001  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_SHIFT                 0  /* DACW_TO_DSP1TXW */
#define WM8996_DACW_TO_DSP1TXW_WIDTH                 1  /* DACW_TO_DSP1TXW */

/*
 * W1544 (0x608) - DSP2 TX Weft Mixew Wouting
 */
#define WM8996_ADC2W_TO_DSP2TXW                 0x0002  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_MASK            0x0002  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_SHIFT                1  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_WIDTH                1  /* ADC2W_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW                  0x0001  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_MASK             0x0001  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_SHIFT                 0  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_WIDTH                 1  /* DACW_TO_DSP2TXW */

/*
 * W1545 (0x609) - DSP2 TX Wight Mixew Wouting
 */
#define WM8996_ADC2W_TO_DSP2TXW                 0x0002  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_MASK            0x0002  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_SHIFT                1  /* ADC2W_TO_DSP2TXW */
#define WM8996_ADC2W_TO_DSP2TXW_WIDTH                1  /* ADC2W_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW                  0x0001  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_MASK             0x0001  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_SHIFT                 0  /* DACW_TO_DSP2TXW */
#define WM8996_DACW_TO_DSP2TXW_WIDTH                 1  /* DACW_TO_DSP2TXW */

/*
 * W1546 (0x60A) - DSP TX Mixew Sewect
 */
#define WM8996_DAC_TO_DSPTX_SWC                 0x0001  /* DAC_TO_DSPTX_SWC */
#define WM8996_DAC_TO_DSPTX_SWC_MASK            0x0001  /* DAC_TO_DSPTX_SWC */
#define WM8996_DAC_TO_DSPTX_SWC_SHIFT                0  /* DAC_TO_DSPTX_SWC */
#define WM8996_DAC_TO_DSPTX_SWC_WIDTH                1  /* DAC_TO_DSPTX_SWC */

/*
 * W1552 (0x610) - DAC Softmute
 */
#define WM8996_DAC_SOFTMUTEMODE                 0x0002  /* DAC_SOFTMUTEMODE */
#define WM8996_DAC_SOFTMUTEMODE_MASK            0x0002  /* DAC_SOFTMUTEMODE */
#define WM8996_DAC_SOFTMUTEMODE_SHIFT                1  /* DAC_SOFTMUTEMODE */
#define WM8996_DAC_SOFTMUTEMODE_WIDTH                1  /* DAC_SOFTMUTEMODE */
#define WM8996_DAC_MUTEWATE                     0x0001  /* DAC_MUTEWATE */
#define WM8996_DAC_MUTEWATE_MASK                0x0001  /* DAC_MUTEWATE */
#define WM8996_DAC_MUTEWATE_SHIFT                    0  /* DAC_MUTEWATE */
#define WM8996_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */

/*
 * W1568 (0x620) - Ovewsampwing
 */
#define WM8996_SPK_OSW128                       0x0008  /* SPK_OSW128 */
#define WM8996_SPK_OSW128_MASK                  0x0008  /* SPK_OSW128 */
#define WM8996_SPK_OSW128_SHIFT                      3  /* SPK_OSW128 */
#define WM8996_SPK_OSW128_WIDTH                      1  /* SPK_OSW128 */
#define WM8996_DMIC_OSW64                       0x0004  /* DMIC_OSW64 */
#define WM8996_DMIC_OSW64_MASK                  0x0004  /* DMIC_OSW64 */
#define WM8996_DMIC_OSW64_SHIFT                      2  /* DMIC_OSW64 */
#define WM8996_DMIC_OSW64_WIDTH                      1  /* DMIC_OSW64 */
#define WM8996_ADC_OSW128                       0x0002  /* ADC_OSW128 */
#define WM8996_ADC_OSW128_MASK                  0x0002  /* ADC_OSW128 */
#define WM8996_ADC_OSW128_SHIFT                      1  /* ADC_OSW128 */
#define WM8996_ADC_OSW128_WIDTH                      1  /* ADC_OSW128 */
#define WM8996_DAC_OSW128                       0x0001  /* DAC_OSW128 */
#define WM8996_DAC_OSW128_MASK                  0x0001  /* DAC_OSW128 */
#define WM8996_DAC_OSW128_SHIFT                      0  /* DAC_OSW128 */
#define WM8996_DAC_OSW128_WIDTH                      1  /* DAC_OSW128 */

/*
 * W1569 (0x621) - Sidetone
 */
#define WM8996_ST_WPF                           0x1000  /* ST_WPF */
#define WM8996_ST_WPF_MASK                      0x1000  /* ST_WPF */
#define WM8996_ST_WPF_SHIFT                         12  /* ST_WPF */
#define WM8996_ST_WPF_WIDTH                          1  /* ST_WPF */
#define WM8996_ST_HPF_CUT_MASK                  0x0380  /* ST_HPF_CUT - [9:7] */
#define WM8996_ST_HPF_CUT_SHIFT                      7  /* ST_HPF_CUT - [9:7] */
#define WM8996_ST_HPF_CUT_WIDTH                      3  /* ST_HPF_CUT - [9:7] */
#define WM8996_ST_HPF                           0x0040  /* ST_HPF */
#define WM8996_ST_HPF_MASK                      0x0040  /* ST_HPF */
#define WM8996_ST_HPF_SHIFT                          6  /* ST_HPF */
#define WM8996_ST_HPF_WIDTH                          1  /* ST_HPF */
#define WM8996_STW_SEW                          0x0002  /* STW_SEW */
#define WM8996_STW_SEW_MASK                     0x0002  /* STW_SEW */
#define WM8996_STW_SEW_SHIFT                         1  /* STW_SEW */
#define WM8996_STW_SEW_WIDTH                         1  /* STW_SEW */
#define WM8996_STW_SEW                          0x0001  /* STW_SEW */
#define WM8996_STW_SEW_MASK                     0x0001  /* STW_SEW */
#define WM8996_STW_SEW_SHIFT                         0  /* STW_SEW */
#define WM8996_STW_SEW_WIDTH                         1  /* STW_SEW */

/*
 * W1792 (0x700) - GPIO 1
 */
#define WM8996_GP1_DIW                          0x8000  /* GP1_DIW */
#define WM8996_GP1_DIW_MASK                     0x8000  /* GP1_DIW */
#define WM8996_GP1_DIW_SHIFT                        15  /* GP1_DIW */
#define WM8996_GP1_DIW_WIDTH                         1  /* GP1_DIW */
#define WM8996_GP1_PU                           0x4000  /* GP1_PU */
#define WM8996_GP1_PU_MASK                      0x4000  /* GP1_PU */
#define WM8996_GP1_PU_SHIFT                         14  /* GP1_PU */
#define WM8996_GP1_PU_WIDTH                          1  /* GP1_PU */
#define WM8996_GP1_PD                           0x2000  /* GP1_PD */
#define WM8996_GP1_PD_MASK                      0x2000  /* GP1_PD */
#define WM8996_GP1_PD_SHIFT                         13  /* GP1_PD */
#define WM8996_GP1_PD_WIDTH                          1  /* GP1_PD */
#define WM8996_GP1_POW                          0x0400  /* GP1_POW */
#define WM8996_GP1_POW_MASK                     0x0400  /* GP1_POW */
#define WM8996_GP1_POW_SHIFT                        10  /* GP1_POW */
#define WM8996_GP1_POW_WIDTH                         1  /* GP1_POW */
#define WM8996_GP1_OP_CFG                       0x0200  /* GP1_OP_CFG */
#define WM8996_GP1_OP_CFG_MASK                  0x0200  /* GP1_OP_CFG */
#define WM8996_GP1_OP_CFG_SHIFT                      9  /* GP1_OP_CFG */
#define WM8996_GP1_OP_CFG_WIDTH                      1  /* GP1_OP_CFG */
#define WM8996_GP1_DB                           0x0100  /* GP1_DB */
#define WM8996_GP1_DB_MASK                      0x0100  /* GP1_DB */
#define WM8996_GP1_DB_SHIFT                          8  /* GP1_DB */
#define WM8996_GP1_DB_WIDTH                          1  /* GP1_DB */
#define WM8996_GP1_WVW                          0x0040  /* GP1_WVW */
#define WM8996_GP1_WVW_MASK                     0x0040  /* GP1_WVW */
#define WM8996_GP1_WVW_SHIFT                         6  /* GP1_WVW */
#define WM8996_GP1_WVW_WIDTH                         1  /* GP1_WVW */
#define WM8996_GP1_FN_MASK                      0x000F  /* GP1_FN - [3:0] */
#define WM8996_GP1_FN_SHIFT                          0  /* GP1_FN - [3:0] */
#define WM8996_GP1_FN_WIDTH                          4  /* GP1_FN - [3:0] */

/*
 * W1793 (0x701) - GPIO 2
 */
#define WM8996_GP2_DIW                          0x8000  /* GP2_DIW */
#define WM8996_GP2_DIW_MASK                     0x8000  /* GP2_DIW */
#define WM8996_GP2_DIW_SHIFT                        15  /* GP2_DIW */
#define WM8996_GP2_DIW_WIDTH                         1  /* GP2_DIW */
#define WM8996_GP2_PU                           0x4000  /* GP2_PU */
#define WM8996_GP2_PU_MASK                      0x4000  /* GP2_PU */
#define WM8996_GP2_PU_SHIFT                         14  /* GP2_PU */
#define WM8996_GP2_PU_WIDTH                          1  /* GP2_PU */
#define WM8996_GP2_PD                           0x2000  /* GP2_PD */
#define WM8996_GP2_PD_MASK                      0x2000  /* GP2_PD */
#define WM8996_GP2_PD_SHIFT                         13  /* GP2_PD */
#define WM8996_GP2_PD_WIDTH                          1  /* GP2_PD */
#define WM8996_GP2_POW                          0x0400  /* GP2_POW */
#define WM8996_GP2_POW_MASK                     0x0400  /* GP2_POW */
#define WM8996_GP2_POW_SHIFT                        10  /* GP2_POW */
#define WM8996_GP2_POW_WIDTH                         1  /* GP2_POW */
#define WM8996_GP2_OP_CFG                       0x0200  /* GP2_OP_CFG */
#define WM8996_GP2_OP_CFG_MASK                  0x0200  /* GP2_OP_CFG */
#define WM8996_GP2_OP_CFG_SHIFT                      9  /* GP2_OP_CFG */
#define WM8996_GP2_OP_CFG_WIDTH                      1  /* GP2_OP_CFG */
#define WM8996_GP2_DB                           0x0100  /* GP2_DB */
#define WM8996_GP2_DB_MASK                      0x0100  /* GP2_DB */
#define WM8996_GP2_DB_SHIFT                          8  /* GP2_DB */
#define WM8996_GP2_DB_WIDTH                          1  /* GP2_DB */
#define WM8996_GP2_WVW                          0x0040  /* GP2_WVW */
#define WM8996_GP2_WVW_MASK                     0x0040  /* GP2_WVW */
#define WM8996_GP2_WVW_SHIFT                         6  /* GP2_WVW */
#define WM8996_GP2_WVW_WIDTH                         1  /* GP2_WVW */
#define WM8996_GP2_FN_MASK                      0x000F  /* GP2_FN - [3:0] */
#define WM8996_GP2_FN_SHIFT                          0  /* GP2_FN - [3:0] */
#define WM8996_GP2_FN_WIDTH                          4  /* GP2_FN - [3:0] */

/*
 * W1794 (0x702) - GPIO 3
 */
#define WM8996_GP3_DIW                          0x8000  /* GP3_DIW */
#define WM8996_GP3_DIW_MASK                     0x8000  /* GP3_DIW */
#define WM8996_GP3_DIW_SHIFT                        15  /* GP3_DIW */
#define WM8996_GP3_DIW_WIDTH                         1  /* GP3_DIW */
#define WM8996_GP3_PU                           0x4000  /* GP3_PU */
#define WM8996_GP3_PU_MASK                      0x4000  /* GP3_PU */
#define WM8996_GP3_PU_SHIFT                         14  /* GP3_PU */
#define WM8996_GP3_PU_WIDTH                          1  /* GP3_PU */
#define WM8996_GP3_PD                           0x2000  /* GP3_PD */
#define WM8996_GP3_PD_MASK                      0x2000  /* GP3_PD */
#define WM8996_GP3_PD_SHIFT                         13  /* GP3_PD */
#define WM8996_GP3_PD_WIDTH                          1  /* GP3_PD */
#define WM8996_GP3_POW                          0x0400  /* GP3_POW */
#define WM8996_GP3_POW_MASK                     0x0400  /* GP3_POW */
#define WM8996_GP3_POW_SHIFT                        10  /* GP3_POW */
#define WM8996_GP3_POW_WIDTH                         1  /* GP3_POW */
#define WM8996_GP3_OP_CFG                       0x0200  /* GP3_OP_CFG */
#define WM8996_GP3_OP_CFG_MASK                  0x0200  /* GP3_OP_CFG */
#define WM8996_GP3_OP_CFG_SHIFT                      9  /* GP3_OP_CFG */
#define WM8996_GP3_OP_CFG_WIDTH                      1  /* GP3_OP_CFG */
#define WM8996_GP3_DB                           0x0100  /* GP3_DB */
#define WM8996_GP3_DB_MASK                      0x0100  /* GP3_DB */
#define WM8996_GP3_DB_SHIFT                          8  /* GP3_DB */
#define WM8996_GP3_DB_WIDTH                          1  /* GP3_DB */
#define WM8996_GP3_WVW                          0x0040  /* GP3_WVW */
#define WM8996_GP3_WVW_MASK                     0x0040  /* GP3_WVW */
#define WM8996_GP3_WVW_SHIFT                         6  /* GP3_WVW */
#define WM8996_GP3_WVW_WIDTH                         1  /* GP3_WVW */
#define WM8996_GP3_FN_MASK                      0x000F  /* GP3_FN - [3:0] */
#define WM8996_GP3_FN_SHIFT                          0  /* GP3_FN - [3:0] */
#define WM8996_GP3_FN_WIDTH                          4  /* GP3_FN - [3:0] */

/*
 * W1795 (0x703) - GPIO 4
 */
#define WM8996_GP4_DIW                          0x8000  /* GP4_DIW */
#define WM8996_GP4_DIW_MASK                     0x8000  /* GP4_DIW */
#define WM8996_GP4_DIW_SHIFT                        15  /* GP4_DIW */
#define WM8996_GP4_DIW_WIDTH                         1  /* GP4_DIW */
#define WM8996_GP4_PU                           0x4000  /* GP4_PU */
#define WM8996_GP4_PU_MASK                      0x4000  /* GP4_PU */
#define WM8996_GP4_PU_SHIFT                         14  /* GP4_PU */
#define WM8996_GP4_PU_WIDTH                          1  /* GP4_PU */
#define WM8996_GP4_PD                           0x2000  /* GP4_PD */
#define WM8996_GP4_PD_MASK                      0x2000  /* GP4_PD */
#define WM8996_GP4_PD_SHIFT                         13  /* GP4_PD */
#define WM8996_GP4_PD_WIDTH                          1  /* GP4_PD */
#define WM8996_GP4_POW                          0x0400  /* GP4_POW */
#define WM8996_GP4_POW_MASK                     0x0400  /* GP4_POW */
#define WM8996_GP4_POW_SHIFT                        10  /* GP4_POW */
#define WM8996_GP4_POW_WIDTH                         1  /* GP4_POW */
#define WM8996_GP4_OP_CFG                       0x0200  /* GP4_OP_CFG */
#define WM8996_GP4_OP_CFG_MASK                  0x0200  /* GP4_OP_CFG */
#define WM8996_GP4_OP_CFG_SHIFT                      9  /* GP4_OP_CFG */
#define WM8996_GP4_OP_CFG_WIDTH                      1  /* GP4_OP_CFG */
#define WM8996_GP4_DB                           0x0100  /* GP4_DB */
#define WM8996_GP4_DB_MASK                      0x0100  /* GP4_DB */
#define WM8996_GP4_DB_SHIFT                          8  /* GP4_DB */
#define WM8996_GP4_DB_WIDTH                          1  /* GP4_DB */
#define WM8996_GP4_WVW                          0x0040  /* GP4_WVW */
#define WM8996_GP4_WVW_MASK                     0x0040  /* GP4_WVW */
#define WM8996_GP4_WVW_SHIFT                         6  /* GP4_WVW */
#define WM8996_GP4_WVW_WIDTH                         1  /* GP4_WVW */
#define WM8996_GP4_FN_MASK                      0x000F  /* GP4_FN - [3:0] */
#define WM8996_GP4_FN_SHIFT                          0  /* GP4_FN - [3:0] */
#define WM8996_GP4_FN_WIDTH                          4  /* GP4_FN - [3:0] */

/*
 * W1796 (0x704) - GPIO 5
 */
#define WM8996_GP5_DIW                          0x8000  /* GP5_DIW */
#define WM8996_GP5_DIW_MASK                     0x8000  /* GP5_DIW */
#define WM8996_GP5_DIW_SHIFT                        15  /* GP5_DIW */
#define WM8996_GP5_DIW_WIDTH                         1  /* GP5_DIW */
#define WM8996_GP5_PU                           0x4000  /* GP5_PU */
#define WM8996_GP5_PU_MASK                      0x4000  /* GP5_PU */
#define WM8996_GP5_PU_SHIFT                         14  /* GP5_PU */
#define WM8996_GP5_PU_WIDTH                          1  /* GP5_PU */
#define WM8996_GP5_PD                           0x2000  /* GP5_PD */
#define WM8996_GP5_PD_MASK                      0x2000  /* GP5_PD */
#define WM8996_GP5_PD_SHIFT                         13  /* GP5_PD */
#define WM8996_GP5_PD_WIDTH                          1  /* GP5_PD */
#define WM8996_GP5_POW                          0x0400  /* GP5_POW */
#define WM8996_GP5_POW_MASK                     0x0400  /* GP5_POW */
#define WM8996_GP5_POW_SHIFT                        10  /* GP5_POW */
#define WM8996_GP5_POW_WIDTH                         1  /* GP5_POW */
#define WM8996_GP5_OP_CFG                       0x0200  /* GP5_OP_CFG */
#define WM8996_GP5_OP_CFG_MASK                  0x0200  /* GP5_OP_CFG */
#define WM8996_GP5_OP_CFG_SHIFT                      9  /* GP5_OP_CFG */
#define WM8996_GP5_OP_CFG_WIDTH                      1  /* GP5_OP_CFG */
#define WM8996_GP5_DB                           0x0100  /* GP5_DB */
#define WM8996_GP5_DB_MASK                      0x0100  /* GP5_DB */
#define WM8996_GP5_DB_SHIFT                          8  /* GP5_DB */
#define WM8996_GP5_DB_WIDTH                          1  /* GP5_DB */
#define WM8996_GP5_WVW                          0x0040  /* GP5_WVW */
#define WM8996_GP5_WVW_MASK                     0x0040  /* GP5_WVW */
#define WM8996_GP5_WVW_SHIFT                         6  /* GP5_WVW */
#define WM8996_GP5_WVW_WIDTH                         1  /* GP5_WVW */
#define WM8996_GP5_FN_MASK                      0x000F  /* GP5_FN - [3:0] */
#define WM8996_GP5_FN_SHIFT                          0  /* GP5_FN - [3:0] */
#define WM8996_GP5_FN_WIDTH                          4  /* GP5_FN - [3:0] */

/*
 * W1824 (0x720) - Puww Contwow (1)
 */
#define WM8996_DMICDAT2_PD                      0x1000  /* DMICDAT2_PD */
#define WM8996_DMICDAT2_PD_MASK                 0x1000  /* DMICDAT2_PD */
#define WM8996_DMICDAT2_PD_SHIFT                    12  /* DMICDAT2_PD */
#define WM8996_DMICDAT2_PD_WIDTH                     1  /* DMICDAT2_PD */
#define WM8996_DMICDAT1_PD                      0x0400  /* DMICDAT1_PD */
#define WM8996_DMICDAT1_PD_MASK                 0x0400  /* DMICDAT1_PD */
#define WM8996_DMICDAT1_PD_SHIFT                    10  /* DMICDAT1_PD */
#define WM8996_DMICDAT1_PD_WIDTH                     1  /* DMICDAT1_PD */
#define WM8996_MCWK2_PU                         0x0200  /* MCWK2_PU */
#define WM8996_MCWK2_PU_MASK                    0x0200  /* MCWK2_PU */
#define WM8996_MCWK2_PU_SHIFT                        9  /* MCWK2_PU */
#define WM8996_MCWK2_PU_WIDTH                        1  /* MCWK2_PU */
#define WM8996_MCWK2_PD                         0x0100  /* MCWK2_PD */
#define WM8996_MCWK2_PD_MASK                    0x0100  /* MCWK2_PD */
#define WM8996_MCWK2_PD_SHIFT                        8  /* MCWK2_PD */
#define WM8996_MCWK2_PD_WIDTH                        1  /* MCWK2_PD */
#define WM8996_MCWK1_PU                         0x0080  /* MCWK1_PU */
#define WM8996_MCWK1_PU_MASK                    0x0080  /* MCWK1_PU */
#define WM8996_MCWK1_PU_SHIFT                        7  /* MCWK1_PU */
#define WM8996_MCWK1_PU_WIDTH                        1  /* MCWK1_PU */
#define WM8996_MCWK1_PD                         0x0040  /* MCWK1_PD */
#define WM8996_MCWK1_PD_MASK                    0x0040  /* MCWK1_PD */
#define WM8996_MCWK1_PD_SHIFT                        6  /* MCWK1_PD */
#define WM8996_MCWK1_PD_WIDTH                        1  /* MCWK1_PD */
#define WM8996_DACDAT1_PU                       0x0020  /* DACDAT1_PU */
#define WM8996_DACDAT1_PU_MASK                  0x0020  /* DACDAT1_PU */
#define WM8996_DACDAT1_PU_SHIFT                      5  /* DACDAT1_PU */
#define WM8996_DACDAT1_PU_WIDTH                      1  /* DACDAT1_PU */
#define WM8996_DACDAT1_PD                       0x0010  /* DACDAT1_PD */
#define WM8996_DACDAT1_PD_MASK                  0x0010  /* DACDAT1_PD */
#define WM8996_DACDAT1_PD_SHIFT                      4  /* DACDAT1_PD */
#define WM8996_DACDAT1_PD_WIDTH                      1  /* DACDAT1_PD */
#define WM8996_DACWWCWK1_PU                     0x0008  /* DACWWCWK1_PU */
#define WM8996_DACWWCWK1_PU_MASK                0x0008  /* DACWWCWK1_PU */
#define WM8996_DACWWCWK1_PU_SHIFT                    3  /* DACWWCWK1_PU */
#define WM8996_DACWWCWK1_PU_WIDTH                    1  /* DACWWCWK1_PU */
#define WM8996_DACWWCWK1_PD                     0x0004  /* DACWWCWK1_PD */
#define WM8996_DACWWCWK1_PD_MASK                0x0004  /* DACWWCWK1_PD */
#define WM8996_DACWWCWK1_PD_SHIFT                    2  /* DACWWCWK1_PD */
#define WM8996_DACWWCWK1_PD_WIDTH                    1  /* DACWWCWK1_PD */
#define WM8996_BCWK1_PU                         0x0002  /* BCWK1_PU */
#define WM8996_BCWK1_PU_MASK                    0x0002  /* BCWK1_PU */
#define WM8996_BCWK1_PU_SHIFT                        1  /* BCWK1_PU */
#define WM8996_BCWK1_PU_WIDTH                        1  /* BCWK1_PU */
#define WM8996_BCWK1_PD                         0x0001  /* BCWK1_PD */
#define WM8996_BCWK1_PD_MASK                    0x0001  /* BCWK1_PD */
#define WM8996_BCWK1_PD_SHIFT                        0  /* BCWK1_PD */
#define WM8996_BCWK1_PD_WIDTH                        1  /* BCWK1_PD */

/*
 * W1825 (0x721) - Puww Contwow (2)
 */
#define WM8996_WDO1ENA_PD                       0x0100  /* WDO1ENA_PD */
#define WM8996_WDO1ENA_PD_MASK                  0x0100  /* WDO1ENA_PD */
#define WM8996_WDO1ENA_PD_SHIFT                      8  /* WDO1ENA_PD */
#define WM8996_WDO1ENA_PD_WIDTH                      1  /* WDO1ENA_PD */
#define WM8996_ADDW_PD                          0x0040  /* ADDW_PD */
#define WM8996_ADDW_PD_MASK                     0x0040  /* ADDW_PD */
#define WM8996_ADDW_PD_SHIFT                         6  /* ADDW_PD */
#define WM8996_ADDW_PD_WIDTH                         1  /* ADDW_PD */
#define WM8996_DACDAT2_PU                       0x0020  /* DACDAT2_PU */
#define WM8996_DACDAT2_PU_MASK                  0x0020  /* DACDAT2_PU */
#define WM8996_DACDAT2_PU_SHIFT                      5  /* DACDAT2_PU */
#define WM8996_DACDAT2_PU_WIDTH                      1  /* DACDAT2_PU */
#define WM8996_DACDAT2_PD                       0x0010  /* DACDAT2_PD */
#define WM8996_DACDAT2_PD_MASK                  0x0010  /* DACDAT2_PD */
#define WM8996_DACDAT2_PD_SHIFT                      4  /* DACDAT2_PD */
#define WM8996_DACDAT2_PD_WIDTH                      1  /* DACDAT2_PD */
#define WM8996_DACWWCWK2_PU                     0x0008  /* DACWWCWK2_PU */
#define WM8996_DACWWCWK2_PU_MASK                0x0008  /* DACWWCWK2_PU */
#define WM8996_DACWWCWK2_PU_SHIFT                    3  /* DACWWCWK2_PU */
#define WM8996_DACWWCWK2_PU_WIDTH                    1  /* DACWWCWK2_PU */
#define WM8996_DACWWCWK2_PD                     0x0004  /* DACWWCWK2_PD */
#define WM8996_DACWWCWK2_PD_MASK                0x0004  /* DACWWCWK2_PD */
#define WM8996_DACWWCWK2_PD_SHIFT                    2  /* DACWWCWK2_PD */
#define WM8996_DACWWCWK2_PD_WIDTH                    1  /* DACWWCWK2_PD */
#define WM8996_BCWK2_PU                         0x0002  /* BCWK2_PU */
#define WM8996_BCWK2_PU_MASK                    0x0002  /* BCWK2_PU */
#define WM8996_BCWK2_PU_SHIFT                        1  /* BCWK2_PU */
#define WM8996_BCWK2_PU_WIDTH                        1  /* BCWK2_PU */
#define WM8996_BCWK2_PD                         0x0001  /* BCWK2_PD */
#define WM8996_BCWK2_PD_MASK                    0x0001  /* BCWK2_PD */
#define WM8996_BCWK2_PD_SHIFT                        0  /* BCWK2_PD */
#define WM8996_BCWK2_PD_WIDTH                        1  /* BCWK2_PD */

/*
 * W1840 (0x730) - Intewwupt Status 1
 */
#define WM8996_GP5_EINT                         0x0010  /* GP5_EINT */
#define WM8996_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#define WM8996_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#define WM8996_GP5_EINT_WIDTH                        1  /* GP5_EINT */
#define WM8996_GP4_EINT                         0x0008  /* GP4_EINT */
#define WM8996_GP4_EINT_MASK                    0x0008  /* GP4_EINT */
#define WM8996_GP4_EINT_SHIFT                        3  /* GP4_EINT */
#define WM8996_GP4_EINT_WIDTH                        1  /* GP4_EINT */
#define WM8996_GP3_EINT                         0x0004  /* GP3_EINT */
#define WM8996_GP3_EINT_MASK                    0x0004  /* GP3_EINT */
#define WM8996_GP3_EINT_SHIFT                        2  /* GP3_EINT */
#define WM8996_GP3_EINT_WIDTH                        1  /* GP3_EINT */
#define WM8996_GP2_EINT                         0x0002  /* GP2_EINT */
#define WM8996_GP2_EINT_MASK                    0x0002  /* GP2_EINT */
#define WM8996_GP2_EINT_SHIFT                        1  /* GP2_EINT */
#define WM8996_GP2_EINT_WIDTH                        1  /* GP2_EINT */
#define WM8996_GP1_EINT                         0x0001  /* GP1_EINT */
#define WM8996_GP1_EINT_MASK                    0x0001  /* GP1_EINT */
#define WM8996_GP1_EINT_SHIFT                        0  /* GP1_EINT */
#define WM8996_GP1_EINT_WIDTH                        1  /* GP1_EINT */

/*
 * W1841 (0x731) - Intewwupt Status 2
 */
#define WM8996_DCS_DONE_23_EINT                 0x1000  /* DCS_DONE_23_EINT */
#define WM8996_DCS_DONE_23_EINT_MASK            0x1000  /* DCS_DONE_23_EINT */
#define WM8996_DCS_DONE_23_EINT_SHIFT               12  /* DCS_DONE_23_EINT */
#define WM8996_DCS_DONE_23_EINT_WIDTH                1  /* DCS_DONE_23_EINT */
#define WM8996_DCS_DONE_01_EINT                 0x0800  /* DCS_DONE_01_EINT */
#define WM8996_DCS_DONE_01_EINT_MASK            0x0800  /* DCS_DONE_01_EINT */
#define WM8996_DCS_DONE_01_EINT_SHIFT               11  /* DCS_DONE_01_EINT */
#define WM8996_DCS_DONE_01_EINT_WIDTH                1  /* DCS_DONE_01_EINT */
#define WM8996_WSEQ_DONE_EINT                   0x0400  /* WSEQ_DONE_EINT */
#define WM8996_WSEQ_DONE_EINT_MASK              0x0400  /* WSEQ_DONE_EINT */
#define WM8996_WSEQ_DONE_EINT_SHIFT                 10  /* WSEQ_DONE_EINT */
#define WM8996_WSEQ_DONE_EINT_WIDTH                  1  /* WSEQ_DONE_EINT */
#define WM8996_FIFOS_EWW_EINT                   0x0200  /* FIFOS_EWW_EINT */
#define WM8996_FIFOS_EWW_EINT_MASK              0x0200  /* FIFOS_EWW_EINT */
#define WM8996_FIFOS_EWW_EINT_SHIFT                  9  /* FIFOS_EWW_EINT */
#define WM8996_FIFOS_EWW_EINT_WIDTH                  1  /* FIFOS_EWW_EINT */
#define WM8996_DSP2DWC_SIG_DET_EINT             0x0080  /* DSP2DWC_SIG_DET_EINT */
#define WM8996_DSP2DWC_SIG_DET_EINT_MASK        0x0080  /* DSP2DWC_SIG_DET_EINT */
#define WM8996_DSP2DWC_SIG_DET_EINT_SHIFT            7  /* DSP2DWC_SIG_DET_EINT */
#define WM8996_DSP2DWC_SIG_DET_EINT_WIDTH            1  /* DSP2DWC_SIG_DET_EINT */
#define WM8996_DSP1DWC_SIG_DET_EINT             0x0040  /* DSP1DWC_SIG_DET_EINT */
#define WM8996_DSP1DWC_SIG_DET_EINT_MASK        0x0040  /* DSP1DWC_SIG_DET_EINT */
#define WM8996_DSP1DWC_SIG_DET_EINT_SHIFT            6  /* DSP1DWC_SIG_DET_EINT */
#define WM8996_DSP1DWC_SIG_DET_EINT_WIDTH            1  /* DSP1DWC_SIG_DET_EINT */
#define WM8996_FWW_SW_CWK_DONE_EINT             0x0008  /* FWW_SW_CWK_DONE_EINT */
#define WM8996_FWW_SW_CWK_DONE_EINT_MASK        0x0008  /* FWW_SW_CWK_DONE_EINT */
#define WM8996_FWW_SW_CWK_DONE_EINT_SHIFT            3  /* FWW_SW_CWK_DONE_EINT */
#define WM8996_FWW_SW_CWK_DONE_EINT_WIDTH            1  /* FWW_SW_CWK_DONE_EINT */
#define WM8996_FWW_WOCK_EINT                    0x0004  /* FWW_WOCK_EINT */
#define WM8996_FWW_WOCK_EINT_MASK               0x0004  /* FWW_WOCK_EINT */
#define WM8996_FWW_WOCK_EINT_SHIFT                   2  /* FWW_WOCK_EINT */
#define WM8996_FWW_WOCK_EINT_WIDTH                   1  /* FWW_WOCK_EINT */
#define WM8996_HP_DONE_EINT                     0x0002  /* HP_DONE_EINT */
#define WM8996_HP_DONE_EINT_MASK                0x0002  /* HP_DONE_EINT */
#define WM8996_HP_DONE_EINT_SHIFT                    1  /* HP_DONE_EINT */
#define WM8996_HP_DONE_EINT_WIDTH                    1  /* HP_DONE_EINT */
#define WM8996_MICD_EINT                        0x0001  /* MICD_EINT */
#define WM8996_MICD_EINT_MASK                   0x0001  /* MICD_EINT */
#define WM8996_MICD_EINT_SHIFT                       0  /* MICD_EINT */
#define WM8996_MICD_EINT_WIDTH                       1  /* MICD_EINT */

/*
 * W1842 (0x732) - Intewwupt Waw Status 2
 */
#define WM8996_DCS_DONE_23_STS                  0x1000  /* DCS_DONE_23_STS */
#define WM8996_DCS_DONE_23_STS_MASK             0x1000  /* DCS_DONE_23_STS */
#define WM8996_DCS_DONE_23_STS_SHIFT                12  /* DCS_DONE_23_STS */
#define WM8996_DCS_DONE_23_STS_WIDTH                 1  /* DCS_DONE_23_STS */
#define WM8996_DCS_DONE_01_STS                  0x0800  /* DCS_DONE_01_STS */
#define WM8996_DCS_DONE_01_STS_MASK             0x0800  /* DCS_DONE_01_STS */
#define WM8996_DCS_DONE_01_STS_SHIFT                11  /* DCS_DONE_01_STS */
#define WM8996_DCS_DONE_01_STS_WIDTH                 1  /* DCS_DONE_01_STS */
#define WM8996_WSEQ_DONE_STS                    0x0400  /* WSEQ_DONE_STS */
#define WM8996_WSEQ_DONE_STS_MASK               0x0400  /* WSEQ_DONE_STS */
#define WM8996_WSEQ_DONE_STS_SHIFT                  10  /* WSEQ_DONE_STS */
#define WM8996_WSEQ_DONE_STS_WIDTH                   1  /* WSEQ_DONE_STS */
#define WM8996_FIFOS_EWW_STS                    0x0200  /* FIFOS_EWW_STS */
#define WM8996_FIFOS_EWW_STS_MASK               0x0200  /* FIFOS_EWW_STS */
#define WM8996_FIFOS_EWW_STS_SHIFT                   9  /* FIFOS_EWW_STS */
#define WM8996_FIFOS_EWW_STS_WIDTH                   1  /* FIFOS_EWW_STS */
#define WM8996_DSP2DWC_SIG_DET_STS              0x0080  /* DSP2DWC_SIG_DET_STS */
#define WM8996_DSP2DWC_SIG_DET_STS_MASK         0x0080  /* DSP2DWC_SIG_DET_STS */
#define WM8996_DSP2DWC_SIG_DET_STS_SHIFT             7  /* DSP2DWC_SIG_DET_STS */
#define WM8996_DSP2DWC_SIG_DET_STS_WIDTH             1  /* DSP2DWC_SIG_DET_STS */
#define WM8996_DSP1DWC_SIG_DET_STS              0x0040  /* DSP1DWC_SIG_DET_STS */
#define WM8996_DSP1DWC_SIG_DET_STS_MASK         0x0040  /* DSP1DWC_SIG_DET_STS */
#define WM8996_DSP1DWC_SIG_DET_STS_SHIFT             6  /* DSP1DWC_SIG_DET_STS */
#define WM8996_DSP1DWC_SIG_DET_STS_WIDTH             1  /* DSP1DWC_SIG_DET_STS */
#define WM8996_FWW_WOCK_STS                     0x0004  /* FWW_WOCK_STS */
#define WM8996_FWW_WOCK_STS_MASK                0x0004  /* FWW_WOCK_STS */
#define WM8996_FWW_WOCK_STS_SHIFT                    2  /* FWW_WOCK_STS */
#define WM8996_FWW_WOCK_STS_WIDTH                    1  /* FWW_WOCK_STS */

/*
 * W1848 (0x738) - Intewwupt Status 1 Mask
 */
#define WM8996_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#define WM8996_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#define WM8996_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#define WM8996_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */
#define WM8996_IM_GP4_EINT                      0x0008  /* IM_GP4_EINT */
#define WM8996_IM_GP4_EINT_MASK                 0x0008  /* IM_GP4_EINT */
#define WM8996_IM_GP4_EINT_SHIFT                     3  /* IM_GP4_EINT */
#define WM8996_IM_GP4_EINT_WIDTH                     1  /* IM_GP4_EINT */
#define WM8996_IM_GP3_EINT                      0x0004  /* IM_GP3_EINT */
#define WM8996_IM_GP3_EINT_MASK                 0x0004  /* IM_GP3_EINT */
#define WM8996_IM_GP3_EINT_SHIFT                     2  /* IM_GP3_EINT */
#define WM8996_IM_GP3_EINT_WIDTH                     1  /* IM_GP3_EINT */
#define WM8996_IM_GP2_EINT                      0x0002  /* IM_GP2_EINT */
#define WM8996_IM_GP2_EINT_MASK                 0x0002  /* IM_GP2_EINT */
#define WM8996_IM_GP2_EINT_SHIFT                     1  /* IM_GP2_EINT */
#define WM8996_IM_GP2_EINT_WIDTH                     1  /* IM_GP2_EINT */
#define WM8996_IM_GP1_EINT                      0x0001  /* IM_GP1_EINT */
#define WM8996_IM_GP1_EINT_MASK                 0x0001  /* IM_GP1_EINT */
#define WM8996_IM_GP1_EINT_SHIFT                     0  /* IM_GP1_EINT */
#define WM8996_IM_GP1_EINT_WIDTH                     1  /* IM_GP1_EINT */

/*
 * W1849 (0x739) - Intewwupt Status 2 Mask
 */
#define WM8996_IM_DCS_DONE_23_EINT              0x1000  /* IM_DCS_DONE_23_EINT */
#define WM8996_IM_DCS_DONE_23_EINT_MASK         0x1000  /* IM_DCS_DONE_23_EINT */
#define WM8996_IM_DCS_DONE_23_EINT_SHIFT            12  /* IM_DCS_DONE_23_EINT */
#define WM8996_IM_DCS_DONE_23_EINT_WIDTH             1  /* IM_DCS_DONE_23_EINT */
#define WM8996_IM_DCS_DONE_01_EINT              0x0800  /* IM_DCS_DONE_01_EINT */
#define WM8996_IM_DCS_DONE_01_EINT_MASK         0x0800  /* IM_DCS_DONE_01_EINT */
#define WM8996_IM_DCS_DONE_01_EINT_SHIFT            11  /* IM_DCS_DONE_01_EINT */
#define WM8996_IM_DCS_DONE_01_EINT_WIDTH             1  /* IM_DCS_DONE_01_EINT */
#define WM8996_IM_WSEQ_DONE_EINT                0x0400  /* IM_WSEQ_DONE_EINT */
#define WM8996_IM_WSEQ_DONE_EINT_MASK           0x0400  /* IM_WSEQ_DONE_EINT */
#define WM8996_IM_WSEQ_DONE_EINT_SHIFT              10  /* IM_WSEQ_DONE_EINT */
#define WM8996_IM_WSEQ_DONE_EINT_WIDTH               1  /* IM_WSEQ_DONE_EINT */
#define WM8996_IM_FIFOS_EWW_EINT                0x0200  /* IM_FIFOS_EWW_EINT */
#define WM8996_IM_FIFOS_EWW_EINT_MASK           0x0200  /* IM_FIFOS_EWW_EINT */
#define WM8996_IM_FIFOS_EWW_EINT_SHIFT               9  /* IM_FIFOS_EWW_EINT */
#define WM8996_IM_FIFOS_EWW_EINT_WIDTH               1  /* IM_FIFOS_EWW_EINT */
#define WM8996_IM_DSP2DWC_SIG_DET_EINT          0x0080  /* IM_DSP2DWC_SIG_DET_EINT */
#define WM8996_IM_DSP2DWC_SIG_DET_EINT_MASK     0x0080  /* IM_DSP2DWC_SIG_DET_EINT */
#define WM8996_IM_DSP2DWC_SIG_DET_EINT_SHIFT         7  /* IM_DSP2DWC_SIG_DET_EINT */
#define WM8996_IM_DSP2DWC_SIG_DET_EINT_WIDTH         1  /* IM_DSP2DWC_SIG_DET_EINT */
#define WM8996_IM_DSP1DWC_SIG_DET_EINT          0x0040  /* IM_DSP1DWC_SIG_DET_EINT */
#define WM8996_IM_DSP1DWC_SIG_DET_EINT_MASK     0x0040  /* IM_DSP1DWC_SIG_DET_EINT */
#define WM8996_IM_DSP1DWC_SIG_DET_EINT_SHIFT         6  /* IM_DSP1DWC_SIG_DET_EINT */
#define WM8996_IM_DSP1DWC_SIG_DET_EINT_WIDTH         1  /* IM_DSP1DWC_SIG_DET_EINT */
#define WM8996_IM_FWW_SW_CWK_DONE_EINT          0x0008  /* IM_FWW_SW_CWK_DONE_EINT */
#define WM8996_IM_FWW_SW_CWK_DONE_EINT_MASK     0x0008  /* IM_FWW_SW_CWK_DONE_EINT */
#define WM8996_IM_FWW_SW_CWK_DONE_EINT_SHIFT         3  /* IM_FWW_SW_CWK_DONE_EINT */
#define WM8996_IM_FWW_SW_CWK_DONE_EINT_WIDTH         1  /* IM_FWW_SW_CWK_DONE_EINT */
#define WM8996_IM_FWW_WOCK_EINT                 0x0004  /* IM_FWW_WOCK_EINT */
#define WM8996_IM_FWW_WOCK_EINT_MASK            0x0004  /* IM_FWW_WOCK_EINT */
#define WM8996_IM_FWW_WOCK_EINT_SHIFT                2  /* IM_FWW_WOCK_EINT */
#define WM8996_IM_FWW_WOCK_EINT_WIDTH                1  /* IM_FWW_WOCK_EINT */
#define WM8996_IM_HP_DONE_EINT                  0x0002  /* IM_HP_DONE_EINT */
#define WM8996_IM_HP_DONE_EINT_MASK             0x0002  /* IM_HP_DONE_EINT */
#define WM8996_IM_HP_DONE_EINT_SHIFT                 1  /* IM_HP_DONE_EINT */
#define WM8996_IM_HP_DONE_EINT_WIDTH                 1  /* IM_HP_DONE_EINT */
#define WM8996_IM_MICD_EINT                     0x0001  /* IM_MICD_EINT */
#define WM8996_IM_MICD_EINT_MASK                0x0001  /* IM_MICD_EINT */
#define WM8996_IM_MICD_EINT_SHIFT                    0  /* IM_MICD_EINT */
#define WM8996_IM_MICD_EINT_WIDTH                    1  /* IM_MICD_EINT */

/*
 * W1856 (0x740) - Intewwupt Contwow
 */
#define WM8996_IM_IWQ                           0x0001  /* IM_IWQ */
#define WM8996_IM_IWQ_MASK                      0x0001  /* IM_IWQ */
#define WM8996_IM_IWQ_SHIFT                          0  /* IM_IWQ */
#define WM8996_IM_IWQ_WIDTH                          1  /* IM_IWQ */

/*
 * W2048 (0x800) - Weft PDM Speakew
 */
#define WM8996_SPKW_ENA                         0x0010  /* SPKW_ENA */
#define WM8996_SPKW_ENA_MASK                    0x0010  /* SPKW_ENA */
#define WM8996_SPKW_ENA_SHIFT                        4  /* SPKW_ENA */
#define WM8996_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */
#define WM8996_SPKW_MUTE                        0x0008  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_MASK                   0x0008  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_SHIFT                       3  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_WIDTH                       1  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_ZC                     0x0004  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_MASK                0x0004  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_SHIFT                    2  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_WIDTH                    1  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_SWC_MASK                    0x0003  /* SPKW_SWC - [1:0] */
#define WM8996_SPKW_SWC_SHIFT                        0  /* SPKW_SWC - [1:0] */
#define WM8996_SPKW_SWC_WIDTH                        2  /* SPKW_SWC - [1:0] */

/*
 * W2049 (0x801) - Wight PDM Speakew
 */
#define WM8996_SPKW_ENA                         0x0010  /* SPKW_ENA */
#define WM8996_SPKW_ENA_MASK                    0x0010  /* SPKW_ENA */
#define WM8996_SPKW_ENA_SHIFT                        4  /* SPKW_ENA */
#define WM8996_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */
#define WM8996_SPKW_MUTE                        0x0008  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_MASK                   0x0008  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_SHIFT                       3  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_WIDTH                       1  /* SPKW_MUTE */
#define WM8996_SPKW_MUTE_ZC                     0x0004  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_MASK                0x0004  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_SHIFT                    2  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_MUTE_ZC_WIDTH                    1  /* SPKW_MUTE_ZC */
#define WM8996_SPKW_SWC_MASK                    0x0003  /* SPKW_SWC - [1:0] */
#define WM8996_SPKW_SWC_SHIFT                        0  /* SPKW_SWC - [1:0] */
#define WM8996_SPKW_SWC_WIDTH                        2  /* SPKW_SWC - [1:0] */

/*
 * W2050 (0x802) - PDM Speakew Mute Sequence
 */
#define WM8996_SPK_MUTE_ENDIAN                  0x0100  /* SPK_MUTE_ENDIAN */
#define WM8996_SPK_MUTE_ENDIAN_MASK             0x0100  /* SPK_MUTE_ENDIAN */
#define WM8996_SPK_MUTE_ENDIAN_SHIFT                 8  /* SPK_MUTE_ENDIAN */
#define WM8996_SPK_MUTE_ENDIAN_WIDTH                 1  /* SPK_MUTE_ENDIAN */
#define WM8996_SPK_MUTE_SEQ1_MASK               0x00FF  /* SPK_MUTE_SEQ1 - [7:0] */
#define WM8996_SPK_MUTE_SEQ1_SHIFT                   0  /* SPK_MUTE_SEQ1 - [7:0] */
#define WM8996_SPK_MUTE_SEQ1_WIDTH                   8  /* SPK_MUTE_SEQ1 - [7:0] */

/*
 * W2051 (0x803) - PDM Speakew Vowume
 */
#define WM8996_SPKW_VOW_MASK                    0x00F0  /* SPKW_VOW - [7:4] */
#define WM8996_SPKW_VOW_SHIFT                        4  /* SPKW_VOW - [7:4] */
#define WM8996_SPKW_VOW_WIDTH                        4  /* SPKW_VOW - [7:4] */
#define WM8996_SPKW_VOW_MASK                    0x000F  /* SPKW_VOW - [3:0] */
#define WM8996_SPKW_VOW_SHIFT                        0  /* SPKW_VOW - [3:0] */
#define WM8996_SPKW_VOW_WIDTH                        4  /* SPKW_VOW - [3:0] */

#endif
