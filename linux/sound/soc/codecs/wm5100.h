/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm5100.h  --  WM5100 AWSA SoC Audio dwivew
 *
 * Copywight 2011 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef WM5100_ASOC_H
#define WM5100_ASOC_H

#incwude <sound/soc.h>
#incwude <winux/wegmap.h>

int wm5100_detect(stwuct snd_soc_component *component, stwuct snd_soc_jack *jack);

#define WM5100_CWK_AIF1     1
#define WM5100_CWK_AIF2     2
#define WM5100_CWK_AIF3     3
#define WM5100_CWK_SYSCWK   4
#define WM5100_CWK_ASYNCCWK 5
#define WM5100_CWK_32KHZ    6
#define WM5100_CWK_OPCWK    7

#define WM5100_CWKSWC_MCWK1    0
#define WM5100_CWKSWC_MCWK2    1
#define WM5100_CWKSWC_SYSCWK   2
#define WM5100_CWKSWC_FWW1     4
#define WM5100_CWKSWC_FWW2     5
#define WM5100_CWKSWC_AIF1BCWK 8
#define WM5100_CWKSWC_AIF2BCWK 9
#define WM5100_CWKSWC_AIF3BCWK 10
#define WM5100_CWKSWC_ASYNCCWK 0x100

#define WM5100_FWW1 1
#define WM5100_FWW2 2

#define WM5100_FWW_SWC_MCWK1    0x0
#define WM5100_FWW_SWC_MCWK2    0x1
#define WM5100_FWW_SWC_FWW1     0x4
#define WM5100_FWW_SWC_FWW2     0x5
#define WM5100_FWW_SWC_AIF1BCWK 0x8
#define WM5100_FWW_SWC_AIF2BCWK 0x9
#define WM5100_FWW_SWC_AIF3BCWK 0xa

/*
 * Wegistew vawues.
 */
#define WM5100_SOFTWAWE_WESET                   0x00
#define WM5100_DEVICE_WEVISION                  0x01
#define WM5100_CTWW_IF_1                        0x10
#define WM5100_TONE_GENEWATOW_1                 0x20
#define WM5100_PWM_DWIVE_1                      0x30
#define WM5100_PWM_DWIVE_2                      0x31
#define WM5100_PWM_DWIVE_3                      0x32
#define WM5100_CWOCKING_1                       0x100
#define WM5100_CWOCKING_3                       0x101
#define WM5100_CWOCKING_4                       0x102
#define WM5100_CWOCKING_5                       0x103
#define WM5100_CWOCKING_6                       0x104
#define WM5100_CWOCKING_7                       0x107
#define WM5100_CWOCKING_8                       0x108
#define WM5100_ASWC_ENABWE                      0x120
#define WM5100_ASWC_STATUS                      0x121
#define WM5100_ASWC_WATE1                       0x122
#define WM5100_ISWC_1_CTWW_1                    0x141
#define WM5100_ISWC_1_CTWW_2                    0x142
#define WM5100_ISWC_2_CTWW1                     0x143
#define WM5100_ISWC_2_CTWW_2                    0x144
#define WM5100_FWW1_CONTWOW_1                   0x182
#define WM5100_FWW1_CONTWOW_2                   0x183
#define WM5100_FWW1_CONTWOW_3                   0x184
#define WM5100_FWW1_CONTWOW_5                   0x186
#define WM5100_FWW1_CONTWOW_6                   0x187
#define WM5100_FWW1_EFS_1                       0x188
#define WM5100_FWW2_CONTWOW_1                   0x1A2
#define WM5100_FWW2_CONTWOW_2                   0x1A3
#define WM5100_FWW2_CONTWOW_3                   0x1A4
#define WM5100_FWW2_CONTWOW_5                   0x1A6
#define WM5100_FWW2_CONTWOW_6                   0x1A7
#define WM5100_FWW2_EFS_1                       0x1A8
#define WM5100_MIC_CHAWGE_PUMP_1                0x200
#define WM5100_MIC_CHAWGE_PUMP_2                0x201
#define WM5100_HP_CHAWGE_PUMP_1                 0x202
#define WM5100_WDO1_CONTWOW                     0x211
#define WM5100_MIC_BIAS_CTWW_1                  0x215
#define WM5100_MIC_BIAS_CTWW_2                  0x216
#define WM5100_MIC_BIAS_CTWW_3                  0x217
#define WM5100_ACCESSOWY_DETECT_MODE_1          0x280
#define WM5100_HEADPHONE_DETECT_1               0x288
#define WM5100_HEADPHONE_DETECT_2               0x289
#define WM5100_MIC_DETECT_1                     0x290
#define WM5100_MIC_DETECT_2                     0x291
#define WM5100_MIC_DETECT_3                     0x292
#define WM5100_MISC_CONTWOW                     0x2BB
#define WM5100_INPUT_ENABWES                    0x301
#define WM5100_INPUT_ENABWES_STATUS             0x302
#define WM5100_IN1W_CONTWOW                     0x310
#define WM5100_IN1W_CONTWOW                     0x311
#define WM5100_IN2W_CONTWOW                     0x312
#define WM5100_IN2W_CONTWOW                     0x313
#define WM5100_IN3W_CONTWOW                     0x314
#define WM5100_IN3W_CONTWOW                     0x315
#define WM5100_IN4W_CONTWOW                     0x316
#define WM5100_IN4W_CONTWOW                     0x317
#define WM5100_WXANC_SWC                        0x318
#define WM5100_INPUT_VOWUME_WAMP                0x319
#define WM5100_ADC_DIGITAW_VOWUME_1W            0x320
#define WM5100_ADC_DIGITAW_VOWUME_1W            0x321
#define WM5100_ADC_DIGITAW_VOWUME_2W            0x322
#define WM5100_ADC_DIGITAW_VOWUME_2W            0x323
#define WM5100_ADC_DIGITAW_VOWUME_3W            0x324
#define WM5100_ADC_DIGITAW_VOWUME_3W            0x325
#define WM5100_ADC_DIGITAW_VOWUME_4W            0x326
#define WM5100_ADC_DIGITAW_VOWUME_4W            0x327
#define WM5100_OUTPUT_ENABWES_2                 0x401
#define WM5100_OUTPUT_STATUS_1                  0x402
#define WM5100_OUTPUT_STATUS_2                  0x403
#define WM5100_CHANNEW_ENABWES_1                0x408
#define WM5100_OUT_VOWUME_1W                    0x410
#define WM5100_OUT_VOWUME_1W                    0x411
#define WM5100_DAC_VOWUME_WIMIT_1W              0x412
#define WM5100_DAC_VOWUME_WIMIT_1W              0x413
#define WM5100_OUT_VOWUME_2W                    0x414
#define WM5100_OUT_VOWUME_2W                    0x415
#define WM5100_DAC_VOWUME_WIMIT_2W              0x416
#define WM5100_DAC_VOWUME_WIMIT_2W              0x417
#define WM5100_OUT_VOWUME_3W                    0x418
#define WM5100_OUT_VOWUME_3W                    0x419
#define WM5100_DAC_VOWUME_WIMIT_3W              0x41A
#define WM5100_DAC_VOWUME_WIMIT_3W              0x41B
#define WM5100_OUT_VOWUME_4W                    0x41C
#define WM5100_OUT_VOWUME_4W                    0x41D
#define WM5100_DAC_VOWUME_WIMIT_5W              0x41E
#define WM5100_DAC_VOWUME_WIMIT_5W              0x41F
#define WM5100_DAC_VOWUME_WIMIT_6W              0x420
#define WM5100_DAC_VOWUME_WIMIT_6W              0x421
#define WM5100_DAC_AEC_CONTWOW_1                0x440
#define WM5100_OUTPUT_VOWUME_WAMP               0x441
#define WM5100_DAC_DIGITAW_VOWUME_1W            0x480
#define WM5100_DAC_DIGITAW_VOWUME_1W            0x481
#define WM5100_DAC_DIGITAW_VOWUME_2W            0x482
#define WM5100_DAC_DIGITAW_VOWUME_2W            0x483
#define WM5100_DAC_DIGITAW_VOWUME_3W            0x484
#define WM5100_DAC_DIGITAW_VOWUME_3W            0x485
#define WM5100_DAC_DIGITAW_VOWUME_4W            0x486
#define WM5100_DAC_DIGITAW_VOWUME_4W            0x487
#define WM5100_DAC_DIGITAW_VOWUME_5W            0x488
#define WM5100_DAC_DIGITAW_VOWUME_5W            0x489
#define WM5100_DAC_DIGITAW_VOWUME_6W            0x48A
#define WM5100_DAC_DIGITAW_VOWUME_6W            0x48B
#define WM5100_PDM_SPK1_CTWW_1                  0x4C0
#define WM5100_PDM_SPK1_CTWW_2                  0x4C1
#define WM5100_PDM_SPK2_CTWW_1                  0x4C2
#define WM5100_PDM_SPK2_CTWW_2                  0x4C3
#define WM5100_AUDIO_IF_1_1                     0x500
#define WM5100_AUDIO_IF_1_2                     0x501
#define WM5100_AUDIO_IF_1_3                     0x502
#define WM5100_AUDIO_IF_1_4                     0x503
#define WM5100_AUDIO_IF_1_5                     0x504
#define WM5100_AUDIO_IF_1_6                     0x505
#define WM5100_AUDIO_IF_1_7                     0x506
#define WM5100_AUDIO_IF_1_8                     0x507
#define WM5100_AUDIO_IF_1_9                     0x508
#define WM5100_AUDIO_IF_1_10                    0x509
#define WM5100_AUDIO_IF_1_11                    0x50A
#define WM5100_AUDIO_IF_1_12                    0x50B
#define WM5100_AUDIO_IF_1_13                    0x50C
#define WM5100_AUDIO_IF_1_14                    0x50D
#define WM5100_AUDIO_IF_1_15                    0x50E
#define WM5100_AUDIO_IF_1_16                    0x50F
#define WM5100_AUDIO_IF_1_17                    0x510
#define WM5100_AUDIO_IF_1_18                    0x511
#define WM5100_AUDIO_IF_1_19                    0x512
#define WM5100_AUDIO_IF_1_20                    0x513
#define WM5100_AUDIO_IF_1_21                    0x514
#define WM5100_AUDIO_IF_1_22                    0x515
#define WM5100_AUDIO_IF_1_23                    0x516
#define WM5100_AUDIO_IF_1_24                    0x517
#define WM5100_AUDIO_IF_1_25                    0x518
#define WM5100_AUDIO_IF_1_26                    0x519
#define WM5100_AUDIO_IF_1_27                    0x51A
#define WM5100_AUDIO_IF_2_1                     0x540
#define WM5100_AUDIO_IF_2_2                     0x541
#define WM5100_AUDIO_IF_2_3                     0x542
#define WM5100_AUDIO_IF_2_4                     0x543
#define WM5100_AUDIO_IF_2_5                     0x544
#define WM5100_AUDIO_IF_2_6                     0x545
#define WM5100_AUDIO_IF_2_7                     0x546
#define WM5100_AUDIO_IF_2_8                     0x547
#define WM5100_AUDIO_IF_2_9                     0x548
#define WM5100_AUDIO_IF_2_10                    0x549
#define WM5100_AUDIO_IF_2_11                    0x54A
#define WM5100_AUDIO_IF_2_18                    0x551
#define WM5100_AUDIO_IF_2_19                    0x552
#define WM5100_AUDIO_IF_2_26                    0x559
#define WM5100_AUDIO_IF_2_27                    0x55A
#define WM5100_AUDIO_IF_3_1                     0x580
#define WM5100_AUDIO_IF_3_2                     0x581
#define WM5100_AUDIO_IF_3_3                     0x582
#define WM5100_AUDIO_IF_3_4                     0x583
#define WM5100_AUDIO_IF_3_5                     0x584
#define WM5100_AUDIO_IF_3_6                     0x585
#define WM5100_AUDIO_IF_3_7                     0x586
#define WM5100_AUDIO_IF_3_8                     0x587
#define WM5100_AUDIO_IF_3_9                     0x588
#define WM5100_AUDIO_IF_3_10                    0x589
#define WM5100_AUDIO_IF_3_11                    0x58A
#define WM5100_AUDIO_IF_3_18                    0x591
#define WM5100_AUDIO_IF_3_19                    0x592
#define WM5100_AUDIO_IF_3_26                    0x599
#define WM5100_AUDIO_IF_3_27                    0x59A
#define WM5100_PWM1MIX_INPUT_1_SOUWCE           0x640
#define WM5100_PWM1MIX_INPUT_1_VOWUME           0x641
#define WM5100_PWM1MIX_INPUT_2_SOUWCE           0x642
#define WM5100_PWM1MIX_INPUT_2_VOWUME           0x643
#define WM5100_PWM1MIX_INPUT_3_SOUWCE           0x644
#define WM5100_PWM1MIX_INPUT_3_VOWUME           0x645
#define WM5100_PWM1MIX_INPUT_4_SOUWCE           0x646
#define WM5100_PWM1MIX_INPUT_4_VOWUME           0x647
#define WM5100_PWM2MIX_INPUT_1_SOUWCE           0x648
#define WM5100_PWM2MIX_INPUT_1_VOWUME           0x649
#define WM5100_PWM2MIX_INPUT_2_SOUWCE           0x64A
#define WM5100_PWM2MIX_INPUT_2_VOWUME           0x64B
#define WM5100_PWM2MIX_INPUT_3_SOUWCE           0x64C
#define WM5100_PWM2MIX_INPUT_3_VOWUME           0x64D
#define WM5100_PWM2MIX_INPUT_4_SOUWCE           0x64E
#define WM5100_PWM2MIX_INPUT_4_VOWUME           0x64F
#define WM5100_OUT1WMIX_INPUT_1_SOUWCE          0x680
#define WM5100_OUT1WMIX_INPUT_1_VOWUME          0x681
#define WM5100_OUT1WMIX_INPUT_2_SOUWCE          0x682
#define WM5100_OUT1WMIX_INPUT_2_VOWUME          0x683
#define WM5100_OUT1WMIX_INPUT_3_SOUWCE          0x684
#define WM5100_OUT1WMIX_INPUT_3_VOWUME          0x685
#define WM5100_OUT1WMIX_INPUT_4_SOUWCE          0x686
#define WM5100_OUT1WMIX_INPUT_4_VOWUME          0x687
#define WM5100_OUT1WMIX_INPUT_1_SOUWCE          0x688
#define WM5100_OUT1WMIX_INPUT_1_VOWUME          0x689
#define WM5100_OUT1WMIX_INPUT_2_SOUWCE          0x68A
#define WM5100_OUT1WMIX_INPUT_2_VOWUME          0x68B
#define WM5100_OUT1WMIX_INPUT_3_SOUWCE          0x68C
#define WM5100_OUT1WMIX_INPUT_3_VOWUME          0x68D
#define WM5100_OUT1WMIX_INPUT_4_SOUWCE          0x68E
#define WM5100_OUT1WMIX_INPUT_4_VOWUME          0x68F
#define WM5100_OUT2WMIX_INPUT_1_SOUWCE          0x690
#define WM5100_OUT2WMIX_INPUT_1_VOWUME          0x691
#define WM5100_OUT2WMIX_INPUT_2_SOUWCE          0x692
#define WM5100_OUT2WMIX_INPUT_2_VOWUME          0x693
#define WM5100_OUT2WMIX_INPUT_3_SOUWCE          0x694
#define WM5100_OUT2WMIX_INPUT_3_VOWUME          0x695
#define WM5100_OUT2WMIX_INPUT_4_SOUWCE          0x696
#define WM5100_OUT2WMIX_INPUT_4_VOWUME          0x697
#define WM5100_OUT2WMIX_INPUT_1_SOUWCE          0x698
#define WM5100_OUT2WMIX_INPUT_1_VOWUME          0x699
#define WM5100_OUT2WMIX_INPUT_2_SOUWCE          0x69A
#define WM5100_OUT2WMIX_INPUT_2_VOWUME          0x69B
#define WM5100_OUT2WMIX_INPUT_3_SOUWCE          0x69C
#define WM5100_OUT2WMIX_INPUT_3_VOWUME          0x69D
#define WM5100_OUT2WMIX_INPUT_4_SOUWCE          0x69E
#define WM5100_OUT2WMIX_INPUT_4_VOWUME          0x69F
#define WM5100_OUT3WMIX_INPUT_1_SOUWCE          0x6A0
#define WM5100_OUT3WMIX_INPUT_1_VOWUME          0x6A1
#define WM5100_OUT3WMIX_INPUT_2_SOUWCE          0x6A2
#define WM5100_OUT3WMIX_INPUT_2_VOWUME          0x6A3
#define WM5100_OUT3WMIX_INPUT_3_SOUWCE          0x6A4
#define WM5100_OUT3WMIX_INPUT_3_VOWUME          0x6A5
#define WM5100_OUT3WMIX_INPUT_4_SOUWCE          0x6A6
#define WM5100_OUT3WMIX_INPUT_4_VOWUME          0x6A7
#define WM5100_OUT3WMIX_INPUT_1_SOUWCE          0x6A8
#define WM5100_OUT3WMIX_INPUT_1_VOWUME          0x6A9
#define WM5100_OUT3WMIX_INPUT_2_SOUWCE          0x6AA
#define WM5100_OUT3WMIX_INPUT_2_VOWUME          0x6AB
#define WM5100_OUT3WMIX_INPUT_3_SOUWCE          0x6AC
#define WM5100_OUT3WMIX_INPUT_3_VOWUME          0x6AD
#define WM5100_OUT3WMIX_INPUT_4_SOUWCE          0x6AE
#define WM5100_OUT3WMIX_INPUT_4_VOWUME          0x6AF
#define WM5100_OUT4WMIX_INPUT_1_SOUWCE          0x6B0
#define WM5100_OUT4WMIX_INPUT_1_VOWUME          0x6B1
#define WM5100_OUT4WMIX_INPUT_2_SOUWCE          0x6B2
#define WM5100_OUT4WMIX_INPUT_2_VOWUME          0x6B3
#define WM5100_OUT4WMIX_INPUT_3_SOUWCE          0x6B4
#define WM5100_OUT4WMIX_INPUT_3_VOWUME          0x6B5
#define WM5100_OUT4WMIX_INPUT_4_SOUWCE          0x6B6
#define WM5100_OUT4WMIX_INPUT_4_VOWUME          0x6B7
#define WM5100_OUT4WMIX_INPUT_1_SOUWCE          0x6B8
#define WM5100_OUT4WMIX_INPUT_1_VOWUME          0x6B9
#define WM5100_OUT4WMIX_INPUT_2_SOUWCE          0x6BA
#define WM5100_OUT4WMIX_INPUT_2_VOWUME          0x6BB
#define WM5100_OUT4WMIX_INPUT_3_SOUWCE          0x6BC
#define WM5100_OUT4WMIX_INPUT_3_VOWUME          0x6BD
#define WM5100_OUT4WMIX_INPUT_4_SOUWCE          0x6BE
#define WM5100_OUT4WMIX_INPUT_4_VOWUME          0x6BF
#define WM5100_OUT5WMIX_INPUT_1_SOUWCE          0x6C0
#define WM5100_OUT5WMIX_INPUT_1_VOWUME          0x6C1
#define WM5100_OUT5WMIX_INPUT_2_SOUWCE          0x6C2
#define WM5100_OUT5WMIX_INPUT_2_VOWUME          0x6C3
#define WM5100_OUT5WMIX_INPUT_3_SOUWCE          0x6C4
#define WM5100_OUT5WMIX_INPUT_3_VOWUME          0x6C5
#define WM5100_OUT5WMIX_INPUT_4_SOUWCE          0x6C6
#define WM5100_OUT5WMIX_INPUT_4_VOWUME          0x6C7
#define WM5100_OUT5WMIX_INPUT_1_SOUWCE          0x6C8
#define WM5100_OUT5WMIX_INPUT_1_VOWUME          0x6C9
#define WM5100_OUT5WMIX_INPUT_2_SOUWCE          0x6CA
#define WM5100_OUT5WMIX_INPUT_2_VOWUME          0x6CB
#define WM5100_OUT5WMIX_INPUT_3_SOUWCE          0x6CC
#define WM5100_OUT5WMIX_INPUT_3_VOWUME          0x6CD
#define WM5100_OUT5WMIX_INPUT_4_SOUWCE          0x6CE
#define WM5100_OUT5WMIX_INPUT_4_VOWUME          0x6CF
#define WM5100_OUT6WMIX_INPUT_1_SOUWCE          0x6D0
#define WM5100_OUT6WMIX_INPUT_1_VOWUME          0x6D1
#define WM5100_OUT6WMIX_INPUT_2_SOUWCE          0x6D2
#define WM5100_OUT6WMIX_INPUT_2_VOWUME          0x6D3
#define WM5100_OUT6WMIX_INPUT_3_SOUWCE          0x6D4
#define WM5100_OUT6WMIX_INPUT_3_VOWUME          0x6D5
#define WM5100_OUT6WMIX_INPUT_4_SOUWCE          0x6D6
#define WM5100_OUT6WMIX_INPUT_4_VOWUME          0x6D7
#define WM5100_OUT6WMIX_INPUT_1_SOUWCE          0x6D8
#define WM5100_OUT6WMIX_INPUT_1_VOWUME          0x6D9
#define WM5100_OUT6WMIX_INPUT_2_SOUWCE          0x6DA
#define WM5100_OUT6WMIX_INPUT_2_VOWUME          0x6DB
#define WM5100_OUT6WMIX_INPUT_3_SOUWCE          0x6DC
#define WM5100_OUT6WMIX_INPUT_3_VOWUME          0x6DD
#define WM5100_OUT6WMIX_INPUT_4_SOUWCE          0x6DE
#define WM5100_OUT6WMIX_INPUT_4_VOWUME          0x6DF
#define WM5100_AIF1TX1MIX_INPUT_1_SOUWCE        0x700
#define WM5100_AIF1TX1MIX_INPUT_1_VOWUME        0x701
#define WM5100_AIF1TX1MIX_INPUT_2_SOUWCE        0x702
#define WM5100_AIF1TX1MIX_INPUT_2_VOWUME        0x703
#define WM5100_AIF1TX1MIX_INPUT_3_SOUWCE        0x704
#define WM5100_AIF1TX1MIX_INPUT_3_VOWUME        0x705
#define WM5100_AIF1TX1MIX_INPUT_4_SOUWCE        0x706
#define WM5100_AIF1TX1MIX_INPUT_4_VOWUME        0x707
#define WM5100_AIF1TX2MIX_INPUT_1_SOUWCE        0x708
#define WM5100_AIF1TX2MIX_INPUT_1_VOWUME        0x709
#define WM5100_AIF1TX2MIX_INPUT_2_SOUWCE        0x70A
#define WM5100_AIF1TX2MIX_INPUT_2_VOWUME        0x70B
#define WM5100_AIF1TX2MIX_INPUT_3_SOUWCE        0x70C
#define WM5100_AIF1TX2MIX_INPUT_3_VOWUME        0x70D
#define WM5100_AIF1TX2MIX_INPUT_4_SOUWCE        0x70E
#define WM5100_AIF1TX2MIX_INPUT_4_VOWUME        0x70F
#define WM5100_AIF1TX3MIX_INPUT_1_SOUWCE        0x710
#define WM5100_AIF1TX3MIX_INPUT_1_VOWUME        0x711
#define WM5100_AIF1TX3MIX_INPUT_2_SOUWCE        0x712
#define WM5100_AIF1TX3MIX_INPUT_2_VOWUME        0x713
#define WM5100_AIF1TX3MIX_INPUT_3_SOUWCE        0x714
#define WM5100_AIF1TX3MIX_INPUT_3_VOWUME        0x715
#define WM5100_AIF1TX3MIX_INPUT_4_SOUWCE        0x716
#define WM5100_AIF1TX3MIX_INPUT_4_VOWUME        0x717
#define WM5100_AIF1TX4MIX_INPUT_1_SOUWCE        0x718
#define WM5100_AIF1TX4MIX_INPUT_1_VOWUME        0x719
#define WM5100_AIF1TX4MIX_INPUT_2_SOUWCE        0x71A
#define WM5100_AIF1TX4MIX_INPUT_2_VOWUME        0x71B
#define WM5100_AIF1TX4MIX_INPUT_3_SOUWCE        0x71C
#define WM5100_AIF1TX4MIX_INPUT_3_VOWUME        0x71D
#define WM5100_AIF1TX4MIX_INPUT_4_SOUWCE        0x71E
#define WM5100_AIF1TX4MIX_INPUT_4_VOWUME        0x71F
#define WM5100_AIF1TX5MIX_INPUT_1_SOUWCE        0x720
#define WM5100_AIF1TX5MIX_INPUT_1_VOWUME        0x721
#define WM5100_AIF1TX5MIX_INPUT_2_SOUWCE        0x722
#define WM5100_AIF1TX5MIX_INPUT_2_VOWUME        0x723
#define WM5100_AIF1TX5MIX_INPUT_3_SOUWCE        0x724
#define WM5100_AIF1TX5MIX_INPUT_3_VOWUME        0x725
#define WM5100_AIF1TX5MIX_INPUT_4_SOUWCE        0x726
#define WM5100_AIF1TX5MIX_INPUT_4_VOWUME        0x727
#define WM5100_AIF1TX6MIX_INPUT_1_SOUWCE        0x728
#define WM5100_AIF1TX6MIX_INPUT_1_VOWUME        0x729
#define WM5100_AIF1TX6MIX_INPUT_2_SOUWCE        0x72A
#define WM5100_AIF1TX6MIX_INPUT_2_VOWUME        0x72B
#define WM5100_AIF1TX6MIX_INPUT_3_SOUWCE        0x72C
#define WM5100_AIF1TX6MIX_INPUT_3_VOWUME        0x72D
#define WM5100_AIF1TX6MIX_INPUT_4_SOUWCE        0x72E
#define WM5100_AIF1TX6MIX_INPUT_4_VOWUME        0x72F
#define WM5100_AIF1TX7MIX_INPUT_1_SOUWCE        0x730
#define WM5100_AIF1TX7MIX_INPUT_1_VOWUME        0x731
#define WM5100_AIF1TX7MIX_INPUT_2_SOUWCE        0x732
#define WM5100_AIF1TX7MIX_INPUT_2_VOWUME        0x733
#define WM5100_AIF1TX7MIX_INPUT_3_SOUWCE        0x734
#define WM5100_AIF1TX7MIX_INPUT_3_VOWUME        0x735
#define WM5100_AIF1TX7MIX_INPUT_4_SOUWCE        0x736
#define WM5100_AIF1TX7MIX_INPUT_4_VOWUME        0x737
#define WM5100_AIF1TX8MIX_INPUT_1_SOUWCE        0x738
#define WM5100_AIF1TX8MIX_INPUT_1_VOWUME        0x739
#define WM5100_AIF1TX8MIX_INPUT_2_SOUWCE        0x73A
#define WM5100_AIF1TX8MIX_INPUT_2_VOWUME        0x73B
#define WM5100_AIF1TX8MIX_INPUT_3_SOUWCE        0x73C
#define WM5100_AIF1TX8MIX_INPUT_3_VOWUME        0x73D
#define WM5100_AIF1TX8MIX_INPUT_4_SOUWCE        0x73E
#define WM5100_AIF1TX8MIX_INPUT_4_VOWUME        0x73F
#define WM5100_AIF2TX1MIX_INPUT_1_SOUWCE        0x740
#define WM5100_AIF2TX1MIX_INPUT_1_VOWUME        0x741
#define WM5100_AIF2TX1MIX_INPUT_2_SOUWCE        0x742
#define WM5100_AIF2TX1MIX_INPUT_2_VOWUME        0x743
#define WM5100_AIF2TX1MIX_INPUT_3_SOUWCE        0x744
#define WM5100_AIF2TX1MIX_INPUT_3_VOWUME        0x745
#define WM5100_AIF2TX1MIX_INPUT_4_SOUWCE        0x746
#define WM5100_AIF2TX1MIX_INPUT_4_VOWUME        0x747
#define WM5100_AIF2TX2MIX_INPUT_1_SOUWCE        0x748
#define WM5100_AIF2TX2MIX_INPUT_1_VOWUME        0x749
#define WM5100_AIF2TX2MIX_INPUT_2_SOUWCE        0x74A
#define WM5100_AIF2TX2MIX_INPUT_2_VOWUME        0x74B
#define WM5100_AIF2TX2MIX_INPUT_3_SOUWCE        0x74C
#define WM5100_AIF2TX2MIX_INPUT_3_VOWUME        0x74D
#define WM5100_AIF2TX2MIX_INPUT_4_SOUWCE        0x74E
#define WM5100_AIF2TX2MIX_INPUT_4_VOWUME        0x74F
#define WM5100_AIF3TX1MIX_INPUT_1_SOUWCE        0x780
#define WM5100_AIF3TX1MIX_INPUT_1_VOWUME        0x781
#define WM5100_AIF3TX1MIX_INPUT_2_SOUWCE        0x782
#define WM5100_AIF3TX1MIX_INPUT_2_VOWUME        0x783
#define WM5100_AIF3TX1MIX_INPUT_3_SOUWCE        0x784
#define WM5100_AIF3TX1MIX_INPUT_3_VOWUME        0x785
#define WM5100_AIF3TX1MIX_INPUT_4_SOUWCE        0x786
#define WM5100_AIF3TX1MIX_INPUT_4_VOWUME        0x787
#define WM5100_AIF3TX2MIX_INPUT_1_SOUWCE        0x788
#define WM5100_AIF3TX2MIX_INPUT_1_VOWUME        0x789
#define WM5100_AIF3TX2MIX_INPUT_2_SOUWCE        0x78A
#define WM5100_AIF3TX2MIX_INPUT_2_VOWUME        0x78B
#define WM5100_AIF3TX2MIX_INPUT_3_SOUWCE        0x78C
#define WM5100_AIF3TX2MIX_INPUT_3_VOWUME        0x78D
#define WM5100_AIF3TX2MIX_INPUT_4_SOUWCE        0x78E
#define WM5100_AIF3TX2MIX_INPUT_4_VOWUME        0x78F
#define WM5100_EQ1MIX_INPUT_1_SOUWCE            0x880
#define WM5100_EQ1MIX_INPUT_1_VOWUME            0x881
#define WM5100_EQ1MIX_INPUT_2_SOUWCE            0x882
#define WM5100_EQ1MIX_INPUT_2_VOWUME            0x883
#define WM5100_EQ1MIX_INPUT_3_SOUWCE            0x884
#define WM5100_EQ1MIX_INPUT_3_VOWUME            0x885
#define WM5100_EQ1MIX_INPUT_4_SOUWCE            0x886
#define WM5100_EQ1MIX_INPUT_4_VOWUME            0x887
#define WM5100_EQ2MIX_INPUT_1_SOUWCE            0x888
#define WM5100_EQ2MIX_INPUT_1_VOWUME            0x889
#define WM5100_EQ2MIX_INPUT_2_SOUWCE            0x88A
#define WM5100_EQ2MIX_INPUT_2_VOWUME            0x88B
#define WM5100_EQ2MIX_INPUT_3_SOUWCE            0x88C
#define WM5100_EQ2MIX_INPUT_3_VOWUME            0x88D
#define WM5100_EQ2MIX_INPUT_4_SOUWCE            0x88E
#define WM5100_EQ2MIX_INPUT_4_VOWUME            0x88F
#define WM5100_EQ3MIX_INPUT_1_SOUWCE            0x890
#define WM5100_EQ3MIX_INPUT_1_VOWUME            0x891
#define WM5100_EQ3MIX_INPUT_2_SOUWCE            0x892
#define WM5100_EQ3MIX_INPUT_2_VOWUME            0x893
#define WM5100_EQ3MIX_INPUT_3_SOUWCE            0x894
#define WM5100_EQ3MIX_INPUT_3_VOWUME            0x895
#define WM5100_EQ3MIX_INPUT_4_SOUWCE            0x896
#define WM5100_EQ3MIX_INPUT_4_VOWUME            0x897
#define WM5100_EQ4MIX_INPUT_1_SOUWCE            0x898
#define WM5100_EQ4MIX_INPUT_1_VOWUME            0x899
#define WM5100_EQ4MIX_INPUT_2_SOUWCE            0x89A
#define WM5100_EQ4MIX_INPUT_2_VOWUME            0x89B
#define WM5100_EQ4MIX_INPUT_3_SOUWCE            0x89C
#define WM5100_EQ4MIX_INPUT_3_VOWUME            0x89D
#define WM5100_EQ4MIX_INPUT_4_SOUWCE            0x89E
#define WM5100_EQ4MIX_INPUT_4_VOWUME            0x89F
#define WM5100_DWC1WMIX_INPUT_1_SOUWCE          0x8C0
#define WM5100_DWC1WMIX_INPUT_1_VOWUME          0x8C1
#define WM5100_DWC1WMIX_INPUT_2_SOUWCE          0x8C2
#define WM5100_DWC1WMIX_INPUT_2_VOWUME          0x8C3
#define WM5100_DWC1WMIX_INPUT_3_SOUWCE          0x8C4
#define WM5100_DWC1WMIX_INPUT_3_VOWUME          0x8C5
#define WM5100_DWC1WMIX_INPUT_4_SOUWCE          0x8C6
#define WM5100_DWC1WMIX_INPUT_4_VOWUME          0x8C7
#define WM5100_DWC1WMIX_INPUT_1_SOUWCE          0x8C8
#define WM5100_DWC1WMIX_INPUT_1_VOWUME          0x8C9
#define WM5100_DWC1WMIX_INPUT_2_SOUWCE          0x8CA
#define WM5100_DWC1WMIX_INPUT_2_VOWUME          0x8CB
#define WM5100_DWC1WMIX_INPUT_3_SOUWCE          0x8CC
#define WM5100_DWC1WMIX_INPUT_3_VOWUME          0x8CD
#define WM5100_DWC1WMIX_INPUT_4_SOUWCE          0x8CE
#define WM5100_DWC1WMIX_INPUT_4_VOWUME          0x8CF
#define WM5100_HPWP1MIX_INPUT_1_SOUWCE          0x900
#define WM5100_HPWP1MIX_INPUT_1_VOWUME          0x901
#define WM5100_HPWP1MIX_INPUT_2_SOUWCE          0x902
#define WM5100_HPWP1MIX_INPUT_2_VOWUME          0x903
#define WM5100_HPWP1MIX_INPUT_3_SOUWCE          0x904
#define WM5100_HPWP1MIX_INPUT_3_VOWUME          0x905
#define WM5100_HPWP1MIX_INPUT_4_SOUWCE          0x906
#define WM5100_HPWP1MIX_INPUT_4_VOWUME          0x907
#define WM5100_HPWP2MIX_INPUT_1_SOUWCE          0x908
#define WM5100_HPWP2MIX_INPUT_1_VOWUME          0x909
#define WM5100_HPWP2MIX_INPUT_2_SOUWCE          0x90A
#define WM5100_HPWP2MIX_INPUT_2_VOWUME          0x90B
#define WM5100_HPWP2MIX_INPUT_3_SOUWCE          0x90C
#define WM5100_HPWP2MIX_INPUT_3_VOWUME          0x90D
#define WM5100_HPWP2MIX_INPUT_4_SOUWCE          0x90E
#define WM5100_HPWP2MIX_INPUT_4_VOWUME          0x90F
#define WM5100_HPWP3MIX_INPUT_1_SOUWCE          0x910
#define WM5100_HPWP3MIX_INPUT_1_VOWUME          0x911
#define WM5100_HPWP3MIX_INPUT_2_SOUWCE          0x912
#define WM5100_HPWP3MIX_INPUT_2_VOWUME          0x913
#define WM5100_HPWP3MIX_INPUT_3_SOUWCE          0x914
#define WM5100_HPWP3MIX_INPUT_3_VOWUME          0x915
#define WM5100_HPWP3MIX_INPUT_4_SOUWCE          0x916
#define WM5100_HPWP3MIX_INPUT_4_VOWUME          0x917
#define WM5100_HPWP4MIX_INPUT_1_SOUWCE          0x918
#define WM5100_HPWP4MIX_INPUT_1_VOWUME          0x919
#define WM5100_HPWP4MIX_INPUT_2_SOUWCE          0x91A
#define WM5100_HPWP4MIX_INPUT_2_VOWUME          0x91B
#define WM5100_HPWP4MIX_INPUT_3_SOUWCE          0x91C
#define WM5100_HPWP4MIX_INPUT_3_VOWUME          0x91D
#define WM5100_HPWP4MIX_INPUT_4_SOUWCE          0x91E
#define WM5100_HPWP4MIX_INPUT_4_VOWUME          0x91F
#define WM5100_DSP1WMIX_INPUT_1_SOUWCE          0x940
#define WM5100_DSP1WMIX_INPUT_1_VOWUME          0x941
#define WM5100_DSP1WMIX_INPUT_2_SOUWCE          0x942
#define WM5100_DSP1WMIX_INPUT_2_VOWUME          0x943
#define WM5100_DSP1WMIX_INPUT_3_SOUWCE          0x944
#define WM5100_DSP1WMIX_INPUT_3_VOWUME          0x945
#define WM5100_DSP1WMIX_INPUT_4_SOUWCE          0x946
#define WM5100_DSP1WMIX_INPUT_4_VOWUME          0x947
#define WM5100_DSP1WMIX_INPUT_1_SOUWCE          0x948
#define WM5100_DSP1WMIX_INPUT_1_VOWUME          0x949
#define WM5100_DSP1WMIX_INPUT_2_SOUWCE          0x94A
#define WM5100_DSP1WMIX_INPUT_2_VOWUME          0x94B
#define WM5100_DSP1WMIX_INPUT_3_SOUWCE          0x94C
#define WM5100_DSP1WMIX_INPUT_3_VOWUME          0x94D
#define WM5100_DSP1WMIX_INPUT_4_SOUWCE          0x94E
#define WM5100_DSP1WMIX_INPUT_4_VOWUME          0x94F
#define WM5100_DSP1AUX1MIX_INPUT_1_SOUWCE       0x950
#define WM5100_DSP1AUX2MIX_INPUT_1_SOUWCE       0x958
#define WM5100_DSP1AUX3MIX_INPUT_1_SOUWCE       0x960
#define WM5100_DSP1AUX4MIX_INPUT_1_SOUWCE       0x968
#define WM5100_DSP1AUX5MIX_INPUT_1_SOUWCE       0x970
#define WM5100_DSP1AUX6MIX_INPUT_1_SOUWCE       0x978
#define WM5100_DSP2WMIX_INPUT_1_SOUWCE          0x980
#define WM5100_DSP2WMIX_INPUT_1_VOWUME          0x981
#define WM5100_DSP2WMIX_INPUT_2_SOUWCE          0x982
#define WM5100_DSP2WMIX_INPUT_2_VOWUME          0x983
#define WM5100_DSP2WMIX_INPUT_3_SOUWCE          0x984
#define WM5100_DSP2WMIX_INPUT_3_VOWUME          0x985
#define WM5100_DSP2WMIX_INPUT_4_SOUWCE          0x986
#define WM5100_DSP2WMIX_INPUT_4_VOWUME          0x987
#define WM5100_DSP2WMIX_INPUT_1_SOUWCE          0x988
#define WM5100_DSP2WMIX_INPUT_1_VOWUME          0x989
#define WM5100_DSP2WMIX_INPUT_2_SOUWCE          0x98A
#define WM5100_DSP2WMIX_INPUT_2_VOWUME          0x98B
#define WM5100_DSP2WMIX_INPUT_3_SOUWCE          0x98C
#define WM5100_DSP2WMIX_INPUT_3_VOWUME          0x98D
#define WM5100_DSP2WMIX_INPUT_4_SOUWCE          0x98E
#define WM5100_DSP2WMIX_INPUT_4_VOWUME          0x98F
#define WM5100_DSP2AUX1MIX_INPUT_1_SOUWCE       0x990
#define WM5100_DSP2AUX2MIX_INPUT_1_SOUWCE       0x998
#define WM5100_DSP2AUX3MIX_INPUT_1_SOUWCE       0x9A0
#define WM5100_DSP2AUX4MIX_INPUT_1_SOUWCE       0x9A8
#define WM5100_DSP2AUX5MIX_INPUT_1_SOUWCE       0x9B0
#define WM5100_DSP2AUX6MIX_INPUT_1_SOUWCE       0x9B8
#define WM5100_DSP3WMIX_INPUT_1_SOUWCE          0x9C0
#define WM5100_DSP3WMIX_INPUT_1_VOWUME          0x9C1
#define WM5100_DSP3WMIX_INPUT_2_SOUWCE          0x9C2
#define WM5100_DSP3WMIX_INPUT_2_VOWUME          0x9C3
#define WM5100_DSP3WMIX_INPUT_3_SOUWCE          0x9C4
#define WM5100_DSP3WMIX_INPUT_3_VOWUME          0x9C5
#define WM5100_DSP3WMIX_INPUT_4_SOUWCE          0x9C6
#define WM5100_DSP3WMIX_INPUT_4_VOWUME          0x9C7
#define WM5100_DSP3WMIX_INPUT_1_SOUWCE          0x9C8
#define WM5100_DSP3WMIX_INPUT_1_VOWUME          0x9C9
#define WM5100_DSP3WMIX_INPUT_2_SOUWCE          0x9CA
#define WM5100_DSP3WMIX_INPUT_2_VOWUME          0x9CB
#define WM5100_DSP3WMIX_INPUT_3_SOUWCE          0x9CC
#define WM5100_DSP3WMIX_INPUT_3_VOWUME          0x9CD
#define WM5100_DSP3WMIX_INPUT_4_SOUWCE          0x9CE
#define WM5100_DSP3WMIX_INPUT_4_VOWUME          0x9CF
#define WM5100_DSP3AUX1MIX_INPUT_1_SOUWCE       0x9D0
#define WM5100_DSP3AUX2MIX_INPUT_1_SOUWCE       0x9D8
#define WM5100_DSP3AUX3MIX_INPUT_1_SOUWCE       0x9E0
#define WM5100_DSP3AUX4MIX_INPUT_1_SOUWCE       0x9E8
#define WM5100_DSP3AUX5MIX_INPUT_1_SOUWCE       0x9F0
#define WM5100_DSP3AUX6MIX_INPUT_1_SOUWCE       0x9F8
#define WM5100_ASWC1WMIX_INPUT_1_SOUWCE         0xA80
#define WM5100_ASWC1WMIX_INPUT_1_SOUWCE         0xA88
#define WM5100_ASWC2WMIX_INPUT_1_SOUWCE         0xA90
#define WM5100_ASWC2WMIX_INPUT_1_SOUWCE         0xA98
#define WM5100_ISWC1DEC1MIX_INPUT_1_SOUWCE      0xB00
#define WM5100_ISWC1DEC2MIX_INPUT_1_SOUWCE      0xB08
#define WM5100_ISWC1DEC3MIX_INPUT_1_SOUWCE      0xB10
#define WM5100_ISWC1DEC4MIX_INPUT_1_SOUWCE      0xB18
#define WM5100_ISWC1INT1MIX_INPUT_1_SOUWCE      0xB20
#define WM5100_ISWC1INT2MIX_INPUT_1_SOUWCE      0xB28
#define WM5100_ISWC1INT3MIX_INPUT_1_SOUWCE      0xB30
#define WM5100_ISWC1INT4MIX_INPUT_1_SOUWCE      0xB38
#define WM5100_ISWC2DEC1MIX_INPUT_1_SOUWCE      0xB40
#define WM5100_ISWC2DEC2MIX_INPUT_1_SOUWCE      0xB48
#define WM5100_ISWC2DEC3MIX_INPUT_1_SOUWCE      0xB50
#define WM5100_ISWC2DEC4MIX_INPUT_1_SOUWCE      0xB58
#define WM5100_ISWC2INT1MIX_INPUT_1_SOUWCE      0xB60
#define WM5100_ISWC2INT2MIX_INPUT_1_SOUWCE      0xB68
#define WM5100_ISWC2INT3MIX_INPUT_1_SOUWCE      0xB70
#define WM5100_ISWC2INT4MIX_INPUT_1_SOUWCE      0xB78
#define WM5100_GPIO_CTWW_1                      0xC00
#define WM5100_GPIO_CTWW_2                      0xC01
#define WM5100_GPIO_CTWW_3                      0xC02
#define WM5100_GPIO_CTWW_4                      0xC03
#define WM5100_GPIO_CTWW_5                      0xC04
#define WM5100_GPIO_CTWW_6                      0xC05
#define WM5100_MISC_PAD_CTWW_1                  0xC23
#define WM5100_MISC_PAD_CTWW_2                  0xC24
#define WM5100_MISC_PAD_CTWW_3                  0xC25
#define WM5100_MISC_PAD_CTWW_4                  0xC26
#define WM5100_MISC_PAD_CTWW_5                  0xC27
#define WM5100_MISC_GPIO_1                      0xC28
#define WM5100_INTEWWUPT_STATUS_1               0xD00
#define WM5100_INTEWWUPT_STATUS_2               0xD01
#define WM5100_INTEWWUPT_STATUS_3               0xD02
#define WM5100_INTEWWUPT_STATUS_4               0xD03
#define WM5100_INTEWWUPT_WAW_STATUS_2           0xD04
#define WM5100_INTEWWUPT_WAW_STATUS_3           0xD05
#define WM5100_INTEWWUPT_WAW_STATUS_4           0xD06
#define WM5100_INTEWWUPT_STATUS_1_MASK          0xD07
#define WM5100_INTEWWUPT_STATUS_2_MASK          0xD08
#define WM5100_INTEWWUPT_STATUS_3_MASK          0xD09
#define WM5100_INTEWWUPT_STATUS_4_MASK          0xD0A
#define WM5100_INTEWWUPT_CONTWOW                0xD1F
#define WM5100_IWQ_DEBOUNCE_1                   0xD20
#define WM5100_IWQ_DEBOUNCE_2                   0xD21
#define WM5100_FX_CTWW                          0xE00
#define WM5100_EQ1_1                            0xE10
#define WM5100_EQ1_2                            0xE11
#define WM5100_EQ1_3                            0xE12
#define WM5100_EQ1_4                            0xE13
#define WM5100_EQ1_5                            0xE14
#define WM5100_EQ1_6                            0xE15
#define WM5100_EQ1_7                            0xE16
#define WM5100_EQ1_8                            0xE17
#define WM5100_EQ1_9                            0xE18
#define WM5100_EQ1_10                           0xE19
#define WM5100_EQ1_11                           0xE1A
#define WM5100_EQ1_12                           0xE1B
#define WM5100_EQ1_13                           0xE1C
#define WM5100_EQ1_14                           0xE1D
#define WM5100_EQ1_15                           0xE1E
#define WM5100_EQ1_16                           0xE1F
#define WM5100_EQ1_17                           0xE20
#define WM5100_EQ1_18                           0xE21
#define WM5100_EQ1_19                           0xE22
#define WM5100_EQ1_20                           0xE23
#define WM5100_EQ2_1                            0xE26
#define WM5100_EQ2_2                            0xE27
#define WM5100_EQ2_3                            0xE28
#define WM5100_EQ2_4                            0xE29
#define WM5100_EQ2_5                            0xE2A
#define WM5100_EQ2_6                            0xE2B
#define WM5100_EQ2_7                            0xE2C
#define WM5100_EQ2_8                            0xE2D
#define WM5100_EQ2_9                            0xE2E
#define WM5100_EQ2_10                           0xE2F
#define WM5100_EQ2_11                           0xE30
#define WM5100_EQ2_12                           0xE31
#define WM5100_EQ2_13                           0xE32
#define WM5100_EQ2_14                           0xE33
#define WM5100_EQ2_15                           0xE34
#define WM5100_EQ2_16                           0xE35
#define WM5100_EQ2_17                           0xE36
#define WM5100_EQ2_18                           0xE37
#define WM5100_EQ2_19                           0xE38
#define WM5100_EQ2_20                           0xE39
#define WM5100_EQ3_1                            0xE3C
#define WM5100_EQ3_2                            0xE3D
#define WM5100_EQ3_3                            0xE3E
#define WM5100_EQ3_4                            0xE3F
#define WM5100_EQ3_5                            0xE40
#define WM5100_EQ3_6                            0xE41
#define WM5100_EQ3_7                            0xE42
#define WM5100_EQ3_8                            0xE43
#define WM5100_EQ3_9                            0xE44
#define WM5100_EQ3_10                           0xE45
#define WM5100_EQ3_11                           0xE46
#define WM5100_EQ3_12                           0xE47
#define WM5100_EQ3_13                           0xE48
#define WM5100_EQ3_14                           0xE49
#define WM5100_EQ3_15                           0xE4A
#define WM5100_EQ3_16                           0xE4B
#define WM5100_EQ3_17                           0xE4C
#define WM5100_EQ3_18                           0xE4D
#define WM5100_EQ3_19                           0xE4E
#define WM5100_EQ3_20                           0xE4F
#define WM5100_EQ4_1                            0xE52
#define WM5100_EQ4_2                            0xE53
#define WM5100_EQ4_3                            0xE54
#define WM5100_EQ4_4                            0xE55
#define WM5100_EQ4_5                            0xE56
#define WM5100_EQ4_6                            0xE57
#define WM5100_EQ4_7                            0xE58
#define WM5100_EQ4_8                            0xE59
#define WM5100_EQ4_9                            0xE5A
#define WM5100_EQ4_10                           0xE5B
#define WM5100_EQ4_11                           0xE5C
#define WM5100_EQ4_12                           0xE5D
#define WM5100_EQ4_13                           0xE5E
#define WM5100_EQ4_14                           0xE5F
#define WM5100_EQ4_15                           0xE60
#define WM5100_EQ4_16                           0xE61
#define WM5100_EQ4_17                           0xE62
#define WM5100_EQ4_18                           0xE63
#define WM5100_EQ4_19                           0xE64
#define WM5100_EQ4_20                           0xE65
#define WM5100_DWC1_CTWW1                       0xE80
#define WM5100_DWC1_CTWW2                       0xE81
#define WM5100_DWC1_CTWW3                       0xE82
#define WM5100_DWC1_CTWW4                       0xE83
#define WM5100_DWC1_CTWW5                       0xE84
#define WM5100_HPWPF1_1                         0xEC0
#define WM5100_HPWPF1_2                         0xEC1
#define WM5100_HPWPF2_1                         0xEC4
#define WM5100_HPWPF2_2                         0xEC5
#define WM5100_HPWPF3_1                         0xEC8
#define WM5100_HPWPF3_2                         0xEC9
#define WM5100_HPWPF4_1                         0xECC
#define WM5100_HPWPF4_2                         0xECD
#define WM5100_DSP1_CONTWOW_1                   0xF00
#define WM5100_DSP1_CONTWOW_2                   0xF02
#define WM5100_DSP1_CONTWOW_3                   0xF03
#define WM5100_DSP1_CONTWOW_4                   0xF04
#define WM5100_DSP1_CONTWOW_5                   0xF06
#define WM5100_DSP1_CONTWOW_6                   0xF07
#define WM5100_DSP1_CONTWOW_7                   0xF08
#define WM5100_DSP1_CONTWOW_8                   0xF09
#define WM5100_DSP1_CONTWOW_9                   0xF0A
#define WM5100_DSP1_CONTWOW_10                  0xF0B
#define WM5100_DSP1_CONTWOW_11                  0xF0C
#define WM5100_DSP1_CONTWOW_12                  0xF0D
#define WM5100_DSP1_CONTWOW_13                  0xF0F
#define WM5100_DSP1_CONTWOW_14                  0xF10
#define WM5100_DSP1_CONTWOW_15                  0xF11
#define WM5100_DSP1_CONTWOW_16                  0xF12
#define WM5100_DSP1_CONTWOW_17                  0xF13
#define WM5100_DSP1_CONTWOW_18                  0xF14
#define WM5100_DSP1_CONTWOW_19                  0xF16
#define WM5100_DSP1_CONTWOW_20                  0xF17
#define WM5100_DSP1_CONTWOW_21                  0xF18
#define WM5100_DSP1_CONTWOW_22                  0xF1A
#define WM5100_DSP1_CONTWOW_23                  0xF1B
#define WM5100_DSP1_CONTWOW_24                  0xF1C
#define WM5100_DSP1_CONTWOW_25                  0xF1E
#define WM5100_DSP1_CONTWOW_26                  0xF20
#define WM5100_DSP1_CONTWOW_27                  0xF21
#define WM5100_DSP1_CONTWOW_28                  0xF22
#define WM5100_DSP1_CONTWOW_29                  0xF23
#define WM5100_DSP1_CONTWOW_30                  0xF24
#define WM5100_DSP2_CONTWOW_1                   0x1000
#define WM5100_DSP2_CONTWOW_2                   0x1002
#define WM5100_DSP2_CONTWOW_3                   0x1003
#define WM5100_DSP2_CONTWOW_4                   0x1004
#define WM5100_DSP2_CONTWOW_5                   0x1006
#define WM5100_DSP2_CONTWOW_6                   0x1007
#define WM5100_DSP2_CONTWOW_7                   0x1008
#define WM5100_DSP2_CONTWOW_8                   0x1009
#define WM5100_DSP2_CONTWOW_9                   0x100A
#define WM5100_DSP2_CONTWOW_10                  0x100B
#define WM5100_DSP2_CONTWOW_11                  0x100C
#define WM5100_DSP2_CONTWOW_12                  0x100D
#define WM5100_DSP2_CONTWOW_13                  0x100F
#define WM5100_DSP2_CONTWOW_14                  0x1010
#define WM5100_DSP2_CONTWOW_15                  0x1011
#define WM5100_DSP2_CONTWOW_16                  0x1012
#define WM5100_DSP2_CONTWOW_17                  0x1013
#define WM5100_DSP2_CONTWOW_18                  0x1014
#define WM5100_DSP2_CONTWOW_19                  0x1016
#define WM5100_DSP2_CONTWOW_20                  0x1017
#define WM5100_DSP2_CONTWOW_21                  0x1018
#define WM5100_DSP2_CONTWOW_22                  0x101A
#define WM5100_DSP2_CONTWOW_23                  0x101B
#define WM5100_DSP2_CONTWOW_24                  0x101C
#define WM5100_DSP2_CONTWOW_25                  0x101E
#define WM5100_DSP2_CONTWOW_26                  0x1020
#define WM5100_DSP2_CONTWOW_27                  0x1021
#define WM5100_DSP2_CONTWOW_28                  0x1022
#define WM5100_DSP2_CONTWOW_29                  0x1023
#define WM5100_DSP2_CONTWOW_30                  0x1024
#define WM5100_DSP3_CONTWOW_1                   0x1100
#define WM5100_DSP3_CONTWOW_2                   0x1102
#define WM5100_DSP3_CONTWOW_3                   0x1103
#define WM5100_DSP3_CONTWOW_4                   0x1104
#define WM5100_DSP3_CONTWOW_5                   0x1106
#define WM5100_DSP3_CONTWOW_6                   0x1107
#define WM5100_DSP3_CONTWOW_7                   0x1108
#define WM5100_DSP3_CONTWOW_8                   0x1109
#define WM5100_DSP3_CONTWOW_9                   0x110A
#define WM5100_DSP3_CONTWOW_10                  0x110B
#define WM5100_DSP3_CONTWOW_11                  0x110C
#define WM5100_DSP3_CONTWOW_12                  0x110D
#define WM5100_DSP3_CONTWOW_13                  0x110F
#define WM5100_DSP3_CONTWOW_14                  0x1110
#define WM5100_DSP3_CONTWOW_15                  0x1111
#define WM5100_DSP3_CONTWOW_16                  0x1112
#define WM5100_DSP3_CONTWOW_17                  0x1113
#define WM5100_DSP3_CONTWOW_18                  0x1114
#define WM5100_DSP3_CONTWOW_19                  0x1116
#define WM5100_DSP3_CONTWOW_20                  0x1117
#define WM5100_DSP3_CONTWOW_21                  0x1118
#define WM5100_DSP3_CONTWOW_22                  0x111A
#define WM5100_DSP3_CONTWOW_23                  0x111B
#define WM5100_DSP3_CONTWOW_24                  0x111C
#define WM5100_DSP3_CONTWOW_25                  0x111E
#define WM5100_DSP3_CONTWOW_26                  0x1120
#define WM5100_DSP3_CONTWOW_27                  0x1121
#define WM5100_DSP3_CONTWOW_28                  0x1122
#define WM5100_DSP3_CONTWOW_29                  0x1123
#define WM5100_DSP3_CONTWOW_30                  0x1124
#define WM5100_DSP1_DM_0                        0x4000
#define WM5100_DSP1_DM_1                        0x4001
#define WM5100_DSP1_DM_2                        0x4002
#define WM5100_DSP1_DM_3                        0x4003
#define WM5100_DSP1_DM_508                      0x41FC
#define WM5100_DSP1_DM_509                      0x41FD
#define WM5100_DSP1_DM_510                      0x41FE
#define WM5100_DSP1_DM_511                      0x41FF
#define WM5100_DSP1_PM_0                        0x4800
#define WM5100_DSP1_PM_1                        0x4801
#define WM5100_DSP1_PM_2                        0x4802
#define WM5100_DSP1_PM_3                        0x4803
#define WM5100_DSP1_PM_4                        0x4804
#define WM5100_DSP1_PM_5                        0x4805
#define WM5100_DSP1_PM_1530                     0x4DFA
#define WM5100_DSP1_PM_1531                     0x4DFB
#define WM5100_DSP1_PM_1532                     0x4DFC
#define WM5100_DSP1_PM_1533                     0x4DFD
#define WM5100_DSP1_PM_1534                     0x4DFE
#define WM5100_DSP1_PM_1535                     0x4DFF
#define WM5100_DSP1_ZM_0                        0x5000
#define WM5100_DSP1_ZM_1                        0x5001
#define WM5100_DSP1_ZM_2                        0x5002
#define WM5100_DSP1_ZM_3                        0x5003
#define WM5100_DSP1_ZM_2044                     0x57FC
#define WM5100_DSP1_ZM_2045                     0x57FD
#define WM5100_DSP1_ZM_2046                     0x57FE
#define WM5100_DSP1_ZM_2047                     0x57FF
#define WM5100_DSP2_DM_0                        0x6000
#define WM5100_DSP2_DM_1                        0x6001
#define WM5100_DSP2_DM_2                        0x6002
#define WM5100_DSP2_DM_3                        0x6003
#define WM5100_DSP2_DM_508                      0x61FC
#define WM5100_DSP2_DM_509                      0x61FD
#define WM5100_DSP2_DM_510                      0x61FE
#define WM5100_DSP2_DM_511                      0x61FF
#define WM5100_DSP2_PM_0                        0x6800
#define WM5100_DSP2_PM_1                        0x6801
#define WM5100_DSP2_PM_2                        0x6802
#define WM5100_DSP2_PM_3                        0x6803
#define WM5100_DSP2_PM_4                        0x6804
#define WM5100_DSP2_PM_5                        0x6805
#define WM5100_DSP2_PM_1530                     0x6DFA
#define WM5100_DSP2_PM_1531                     0x6DFB
#define WM5100_DSP2_PM_1532                     0x6DFC
#define WM5100_DSP2_PM_1533                     0x6DFD
#define WM5100_DSP2_PM_1534                     0x6DFE
#define WM5100_DSP2_PM_1535                     0x6DFF
#define WM5100_DSP2_ZM_0                        0x7000
#define WM5100_DSP2_ZM_1                        0x7001
#define WM5100_DSP2_ZM_2                        0x7002
#define WM5100_DSP2_ZM_3                        0x7003
#define WM5100_DSP2_ZM_2044                     0x77FC
#define WM5100_DSP2_ZM_2045                     0x77FD
#define WM5100_DSP2_ZM_2046                     0x77FE
#define WM5100_DSP2_ZM_2047                     0x77FF
#define WM5100_DSP3_DM_0                        0x8000
#define WM5100_DSP3_DM_1                        0x8001
#define WM5100_DSP3_DM_2                        0x8002
#define WM5100_DSP3_DM_3                        0x8003
#define WM5100_DSP3_DM_508                      0x81FC
#define WM5100_DSP3_DM_509                      0x81FD
#define WM5100_DSP3_DM_510                      0x81FE
#define WM5100_DSP3_DM_511                      0x81FF
#define WM5100_DSP3_PM_0                        0x8800
#define WM5100_DSP3_PM_1                        0x8801
#define WM5100_DSP3_PM_2                        0x8802
#define WM5100_DSP3_PM_3                        0x8803
#define WM5100_DSP3_PM_4                        0x8804
#define WM5100_DSP3_PM_5                        0x8805
#define WM5100_DSP3_PM_1530                     0x8DFA
#define WM5100_DSP3_PM_1531                     0x8DFB
#define WM5100_DSP3_PM_1532                     0x8DFC
#define WM5100_DSP3_PM_1533                     0x8DFD
#define WM5100_DSP3_PM_1534                     0x8DFE
#define WM5100_DSP3_PM_1535                     0x8DFF
#define WM5100_DSP3_ZM_0                        0x9000
#define WM5100_DSP3_ZM_1                        0x9001
#define WM5100_DSP3_ZM_2                        0x9002
#define WM5100_DSP3_ZM_3                        0x9003
#define WM5100_DSP3_ZM_2044                     0x97FC
#define WM5100_DSP3_ZM_2045                     0x97FD
#define WM5100_DSP3_ZM_2046                     0x97FE
#define WM5100_DSP3_ZM_2047                     0x97FF

#define WM5100_WEGISTEW_COUNT                   1435
#define WM5100_MAX_WEGISTEW                     0x97FF

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - softwawe weset
 */
#define WM5100_SW_WST_DEV_ID1_MASK              0xFFFF  /* SW_WST_DEV_ID1 - [15:0] */
#define WM5100_SW_WST_DEV_ID1_SHIFT                  0  /* SW_WST_DEV_ID1 - [15:0] */
#define WM5100_SW_WST_DEV_ID1_WIDTH                 16  /* SW_WST_DEV_ID1 - [15:0] */

/*
 * W1 (0x01) - Device Wevision
 */
#define WM5100_DEVICE_WEVISION_MASK             0x000F  /* DEVICE_WEVISION - [3:0] */
#define WM5100_DEVICE_WEVISION_SHIFT                 0  /* DEVICE_WEVISION - [3:0] */
#define WM5100_DEVICE_WEVISION_WIDTH                 4  /* DEVICE_WEVISION - [3:0] */

/*
 * W16 (0x10) - Ctww IF 1
 */
#define WM5100_AUTO_INC                         0x0001  /* AUTO_INC */
#define WM5100_AUTO_INC_MASK                    0x0001  /* AUTO_INC */
#define WM5100_AUTO_INC_SHIFT                        0  /* AUTO_INC */
#define WM5100_AUTO_INC_WIDTH                        1  /* AUTO_INC */

/*
 * W32 (0x20) - Tone Genewatow 1
 */
#define WM5100_TONE_WATE_MASK                   0x3000  /* TONE_WATE - [13:12] */
#define WM5100_TONE_WATE_SHIFT                      12  /* TONE_WATE - [13:12] */
#define WM5100_TONE_WATE_WIDTH                       2  /* TONE_WATE - [13:12] */
#define WM5100_TONE_OFFSET_MASK                 0x0300  /* TONE_OFFSET - [9:8] */
#define WM5100_TONE_OFFSET_SHIFT                     8  /* TONE_OFFSET - [9:8] */
#define WM5100_TONE_OFFSET_WIDTH                     2  /* TONE_OFFSET - [9:8] */
#define WM5100_TONE2_ENA                        0x0002  /* TONE2_ENA */
#define WM5100_TONE2_ENA_MASK                   0x0002  /* TONE2_ENA */
#define WM5100_TONE2_ENA_SHIFT                       1  /* TONE2_ENA */
#define WM5100_TONE2_ENA_WIDTH                       1  /* TONE2_ENA */
#define WM5100_TONE1_ENA                        0x0001  /* TONE1_ENA */
#define WM5100_TONE1_ENA_MASK                   0x0001  /* TONE1_ENA */
#define WM5100_TONE1_ENA_SHIFT                       0  /* TONE1_ENA */
#define WM5100_TONE1_ENA_WIDTH                       1  /* TONE1_ENA */

/*
 * W48 (0x30) - PWM Dwive 1
 */
#define WM5100_PWM_WATE_MASK                    0x3000  /* PWM_WATE - [13:12] */
#define WM5100_PWM_WATE_SHIFT                       12  /* PWM_WATE - [13:12] */
#define WM5100_PWM_WATE_WIDTH                        2  /* PWM_WATE - [13:12] */
#define WM5100_PWM_CWK_SEW_MASK                 0x0300  /* PWM_CWK_SEW - [9:8] */
#define WM5100_PWM_CWK_SEW_SHIFT                     8  /* PWM_CWK_SEW - [9:8] */
#define WM5100_PWM_CWK_SEW_WIDTH                     2  /* PWM_CWK_SEW - [9:8] */
#define WM5100_PWM2_OVD                         0x0020  /* PWM2_OVD */
#define WM5100_PWM2_OVD_MASK                    0x0020  /* PWM2_OVD */
#define WM5100_PWM2_OVD_SHIFT                        5  /* PWM2_OVD */
#define WM5100_PWM2_OVD_WIDTH                        1  /* PWM2_OVD */
#define WM5100_PWM1_OVD                         0x0010  /* PWM1_OVD */
#define WM5100_PWM1_OVD_MASK                    0x0010  /* PWM1_OVD */
#define WM5100_PWM1_OVD_SHIFT                        4  /* PWM1_OVD */
#define WM5100_PWM1_OVD_WIDTH                        1  /* PWM1_OVD */
#define WM5100_PWM2_ENA                         0x0002  /* PWM2_ENA */
#define WM5100_PWM2_ENA_MASK                    0x0002  /* PWM2_ENA */
#define WM5100_PWM2_ENA_SHIFT                        1  /* PWM2_ENA */
#define WM5100_PWM2_ENA_WIDTH                        1  /* PWM2_ENA */
#define WM5100_PWM1_ENA                         0x0001  /* PWM1_ENA */
#define WM5100_PWM1_ENA_MASK                    0x0001  /* PWM1_ENA */
#define WM5100_PWM1_ENA_SHIFT                        0  /* PWM1_ENA */
#define WM5100_PWM1_ENA_WIDTH                        1  /* PWM1_ENA */

/*
 * W49 (0x31) - PWM Dwive 2
 */
#define WM5100_PWM1_WVW_MASK                    0x03FF  /* PWM1_WVW - [9:0] */
#define WM5100_PWM1_WVW_SHIFT                        0  /* PWM1_WVW - [9:0] */
#define WM5100_PWM1_WVW_WIDTH                       10  /* PWM1_WVW - [9:0] */

/*
 * W50 (0x32) - PWM Dwive 3
 */
#define WM5100_PWM2_WVW_MASK                    0x03FF  /* PWM2_WVW - [9:0] */
#define WM5100_PWM2_WVW_SHIFT                        0  /* PWM2_WVW - [9:0] */
#define WM5100_PWM2_WVW_WIDTH                       10  /* PWM2_WVW - [9:0] */

/*
 * W256 (0x100) - Cwocking 1
 */
#define WM5100_CWK_32K_SWC_MASK                 0x000F  /* CWK_32K_SWC - [3:0] */
#define WM5100_CWK_32K_SWC_SHIFT                     0  /* CWK_32K_SWC - [3:0] */
#define WM5100_CWK_32K_SWC_WIDTH                     4  /* CWK_32K_SWC - [3:0] */

/*
 * W257 (0x101) - Cwocking 3
 */
#define WM5100_SYSCWK_FWEQ_MASK                 0x0700  /* SYSCWK_FWEQ - [10:8] */
#define WM5100_SYSCWK_FWEQ_SHIFT                     8  /* SYSCWK_FWEQ - [10:8] */
#define WM5100_SYSCWK_FWEQ_WIDTH                     3  /* SYSCWK_FWEQ - [10:8] */
#define WM5100_SYSCWK_ENA                       0x0040  /* SYSCWK_ENA */
#define WM5100_SYSCWK_ENA_MASK                  0x0040  /* SYSCWK_ENA */
#define WM5100_SYSCWK_ENA_SHIFT                      6  /* SYSCWK_ENA */
#define WM5100_SYSCWK_ENA_WIDTH                      1  /* SYSCWK_ENA */
#define WM5100_SYSCWK_SWC_MASK                  0x000F  /* SYSCWK_SWC - [3:0] */
#define WM5100_SYSCWK_SWC_SHIFT                      0  /* SYSCWK_SWC - [3:0] */
#define WM5100_SYSCWK_SWC_WIDTH                      4  /* SYSCWK_SWC - [3:0] */

/*
 * W258 (0x102) - Cwocking 4
 */
#define WM5100_SAMPWE_WATE_1_MASK               0x001F  /* SAMPWE_WATE_1 - [4:0] */
#define WM5100_SAMPWE_WATE_1_SHIFT                   0  /* SAMPWE_WATE_1 - [4:0] */
#define WM5100_SAMPWE_WATE_1_WIDTH                   5  /* SAMPWE_WATE_1 - [4:0] */

/*
 * W259 (0x103) - Cwocking 5
 */
#define WM5100_SAMPWE_WATE_2_MASK               0x001F  /* SAMPWE_WATE_2 - [4:0] */
#define WM5100_SAMPWE_WATE_2_SHIFT                   0  /* SAMPWE_WATE_2 - [4:0] */
#define WM5100_SAMPWE_WATE_2_WIDTH                   5  /* SAMPWE_WATE_2 - [4:0] */

/*
 * W260 (0x104) - Cwocking 6
 */
#define WM5100_SAMPWE_WATE_3_MASK               0x001F  /* SAMPWE_WATE_3 - [4:0] */
#define WM5100_SAMPWE_WATE_3_SHIFT                   0  /* SAMPWE_WATE_3 - [4:0] */
#define WM5100_SAMPWE_WATE_3_WIDTH                   5  /* SAMPWE_WATE_3 - [4:0] */

/*
 * W263 (0x107) - Cwocking 7
 */
#define WM5100_ASYNC_CWK_FWEQ_MASK              0x0700  /* ASYNC_CWK_FWEQ - [10:8] */
#define WM5100_ASYNC_CWK_FWEQ_SHIFT                  8  /* ASYNC_CWK_FWEQ - [10:8] */
#define WM5100_ASYNC_CWK_FWEQ_WIDTH                  3  /* ASYNC_CWK_FWEQ - [10:8] */
#define WM5100_ASYNC_CWK_ENA                    0x0040  /* ASYNC_CWK_ENA */
#define WM5100_ASYNC_CWK_ENA_MASK               0x0040  /* ASYNC_CWK_ENA */
#define WM5100_ASYNC_CWK_ENA_SHIFT                   6  /* ASYNC_CWK_ENA */
#define WM5100_ASYNC_CWK_ENA_WIDTH                   1  /* ASYNC_CWK_ENA */
#define WM5100_ASYNC_CWK_SWC_MASK               0x000F  /* ASYNC_CWK_SWC - [3:0] */
#define WM5100_ASYNC_CWK_SWC_SHIFT                   0  /* ASYNC_CWK_SWC - [3:0] */
#define WM5100_ASYNC_CWK_SWC_WIDTH                   4  /* ASYNC_CWK_SWC - [3:0] */

/*
 * W264 (0x108) - Cwocking 8
 */
#define WM5100_ASYNC_SAMPWE_WATE_MASK           0x001F  /* ASYNC_SAMPWE_WATE - [4:0] */
#define WM5100_ASYNC_SAMPWE_WATE_SHIFT               0  /* ASYNC_SAMPWE_WATE - [4:0] */
#define WM5100_ASYNC_SAMPWE_WATE_WIDTH               5  /* ASYNC_SAMPWE_WATE - [4:0] */

/*
 * W288 (0x120) - ASWC_ENABWE
 */
#define WM5100_ASWC2W_ENA                       0x0008  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_MASK                  0x0008  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_SHIFT                      3  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_WIDTH                      1  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA                       0x0004  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_MASK                  0x0004  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_SHIFT                      2  /* ASWC2W_ENA */
#define WM5100_ASWC2W_ENA_WIDTH                      1  /* ASWC2W_ENA */
#define WM5100_ASWC1W_ENA                       0x0002  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_MASK                  0x0002  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_SHIFT                      1  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_WIDTH                      1  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA                       0x0001  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_MASK                  0x0001  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_SHIFT                      0  /* ASWC1W_ENA */
#define WM5100_ASWC1W_ENA_WIDTH                      1  /* ASWC1W_ENA */

/*
 * W289 (0x121) - ASWC_STATUS
 */
#define WM5100_ASWC2W_ENA_STS                   0x0008  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_MASK              0x0008  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_SHIFT                  3  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_WIDTH                  1  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS                   0x0004  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_MASK              0x0004  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_SHIFT                  2  /* ASWC2W_ENA_STS */
#define WM5100_ASWC2W_ENA_STS_WIDTH                  1  /* ASWC2W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS                   0x0002  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_MASK              0x0002  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_SHIFT                  1  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_WIDTH                  1  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS                   0x0001  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_MASK              0x0001  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_SHIFT                  0  /* ASWC1W_ENA_STS */
#define WM5100_ASWC1W_ENA_STS_WIDTH                  1  /* ASWC1W_ENA_STS */

/*
 * W290 (0x122) - ASWC_WATE1
 */
#define WM5100_ASWC_WATE1_MASK                  0x0006  /* ASWC_WATE1 - [2:1] */
#define WM5100_ASWC_WATE1_SHIFT                      1  /* ASWC_WATE1 - [2:1] */
#define WM5100_ASWC_WATE1_WIDTH                      2  /* ASWC_WATE1 - [2:1] */

/*
 * W321 (0x141) - ISWC 1 CTWW 1
 */
#define WM5100_ISWC1_DFS_ENA                    0x2000  /* ISWC1_DFS_ENA */
#define WM5100_ISWC1_DFS_ENA_MASK               0x2000  /* ISWC1_DFS_ENA */
#define WM5100_ISWC1_DFS_ENA_SHIFT                  13  /* ISWC1_DFS_ENA */
#define WM5100_ISWC1_DFS_ENA_WIDTH                   1  /* ISWC1_DFS_ENA */
#define WM5100_ISWC1_CWK_SEW_MASK               0x0300  /* ISWC1_CWK_SEW - [9:8] */
#define WM5100_ISWC1_CWK_SEW_SHIFT                   8  /* ISWC1_CWK_SEW - [9:8] */
#define WM5100_ISWC1_CWK_SEW_WIDTH                   2  /* ISWC1_CWK_SEW - [9:8] */
#define WM5100_ISWC1_FSH_MASK                   0x000C  /* ISWC1_FSH - [3:2] */
#define WM5100_ISWC1_FSH_SHIFT                       2  /* ISWC1_FSH - [3:2] */
#define WM5100_ISWC1_FSH_WIDTH                       2  /* ISWC1_FSH - [3:2] */
#define WM5100_ISWC1_FSW_MASK                   0x0003  /* ISWC1_FSW - [1:0] */
#define WM5100_ISWC1_FSW_SHIFT                       0  /* ISWC1_FSW - [1:0] */
#define WM5100_ISWC1_FSW_WIDTH                       2  /* ISWC1_FSW - [1:0] */

/*
 * W322 (0x142) - ISWC 1 CTWW 2
 */
#define WM5100_ISWC1_INT1_ENA                   0x8000  /* ISWC1_INT1_ENA */
#define WM5100_ISWC1_INT1_ENA_MASK              0x8000  /* ISWC1_INT1_ENA */
#define WM5100_ISWC1_INT1_ENA_SHIFT                 15  /* ISWC1_INT1_ENA */
#define WM5100_ISWC1_INT1_ENA_WIDTH                  1  /* ISWC1_INT1_ENA */
#define WM5100_ISWC1_INT2_ENA                   0x4000  /* ISWC1_INT2_ENA */
#define WM5100_ISWC1_INT2_ENA_MASK              0x4000  /* ISWC1_INT2_ENA */
#define WM5100_ISWC1_INT2_ENA_SHIFT                 14  /* ISWC1_INT2_ENA */
#define WM5100_ISWC1_INT2_ENA_WIDTH                  1  /* ISWC1_INT2_ENA */
#define WM5100_ISWC1_INT3_ENA                   0x2000  /* ISWC1_INT3_ENA */
#define WM5100_ISWC1_INT3_ENA_MASK              0x2000  /* ISWC1_INT3_ENA */
#define WM5100_ISWC1_INT3_ENA_SHIFT                 13  /* ISWC1_INT3_ENA */
#define WM5100_ISWC1_INT3_ENA_WIDTH                  1  /* ISWC1_INT3_ENA */
#define WM5100_ISWC1_INT4_ENA                   0x1000  /* ISWC1_INT4_ENA */
#define WM5100_ISWC1_INT4_ENA_MASK              0x1000  /* ISWC1_INT4_ENA */
#define WM5100_ISWC1_INT4_ENA_SHIFT                 12  /* ISWC1_INT4_ENA */
#define WM5100_ISWC1_INT4_ENA_WIDTH                  1  /* ISWC1_INT4_ENA */
#define WM5100_ISWC1_DEC1_ENA                   0x0200  /* ISWC1_DEC1_ENA */
#define WM5100_ISWC1_DEC1_ENA_MASK              0x0200  /* ISWC1_DEC1_ENA */
#define WM5100_ISWC1_DEC1_ENA_SHIFT                  9  /* ISWC1_DEC1_ENA */
#define WM5100_ISWC1_DEC1_ENA_WIDTH                  1  /* ISWC1_DEC1_ENA */
#define WM5100_ISWC1_DEC2_ENA                   0x0100  /* ISWC1_DEC2_ENA */
#define WM5100_ISWC1_DEC2_ENA_MASK              0x0100  /* ISWC1_DEC2_ENA */
#define WM5100_ISWC1_DEC2_ENA_SHIFT                  8  /* ISWC1_DEC2_ENA */
#define WM5100_ISWC1_DEC2_ENA_WIDTH                  1  /* ISWC1_DEC2_ENA */
#define WM5100_ISWC1_DEC3_ENA                   0x0080  /* ISWC1_DEC3_ENA */
#define WM5100_ISWC1_DEC3_ENA_MASK              0x0080  /* ISWC1_DEC3_ENA */
#define WM5100_ISWC1_DEC3_ENA_SHIFT                  7  /* ISWC1_DEC3_ENA */
#define WM5100_ISWC1_DEC3_ENA_WIDTH                  1  /* ISWC1_DEC3_ENA */
#define WM5100_ISWC1_DEC4_ENA                   0x0040  /* ISWC1_DEC4_ENA */
#define WM5100_ISWC1_DEC4_ENA_MASK              0x0040  /* ISWC1_DEC4_ENA */
#define WM5100_ISWC1_DEC4_ENA_SHIFT                  6  /* ISWC1_DEC4_ENA */
#define WM5100_ISWC1_DEC4_ENA_WIDTH                  1  /* ISWC1_DEC4_ENA */
#define WM5100_ISWC1_NOTCH_ENA                  0x0001  /* ISWC1_NOTCH_ENA */
#define WM5100_ISWC1_NOTCH_ENA_MASK             0x0001  /* ISWC1_NOTCH_ENA */
#define WM5100_ISWC1_NOTCH_ENA_SHIFT                 0  /* ISWC1_NOTCH_ENA */
#define WM5100_ISWC1_NOTCH_ENA_WIDTH                 1  /* ISWC1_NOTCH_ENA */

/*
 * W323 (0x143) - ISWC 2 CTWW1
 */
#define WM5100_ISWC2_DFS_ENA                    0x2000  /* ISWC2_DFS_ENA */
#define WM5100_ISWC2_DFS_ENA_MASK               0x2000  /* ISWC2_DFS_ENA */
#define WM5100_ISWC2_DFS_ENA_SHIFT                  13  /* ISWC2_DFS_ENA */
#define WM5100_ISWC2_DFS_ENA_WIDTH                   1  /* ISWC2_DFS_ENA */
#define WM5100_ISWC2_CWK_SEW_MASK               0x0300  /* ISWC2_CWK_SEW - [9:8] */
#define WM5100_ISWC2_CWK_SEW_SHIFT                   8  /* ISWC2_CWK_SEW - [9:8] */
#define WM5100_ISWC2_CWK_SEW_WIDTH                   2  /* ISWC2_CWK_SEW - [9:8] */
#define WM5100_ISWC2_FSH_MASK                   0x000C  /* ISWC2_FSH - [3:2] */
#define WM5100_ISWC2_FSH_SHIFT                       2  /* ISWC2_FSH - [3:2] */
#define WM5100_ISWC2_FSH_WIDTH                       2  /* ISWC2_FSH - [3:2] */
#define WM5100_ISWC2_FSW_MASK                   0x0003  /* ISWC2_FSW - [1:0] */
#define WM5100_ISWC2_FSW_SHIFT                       0  /* ISWC2_FSW - [1:0] */
#define WM5100_ISWC2_FSW_WIDTH                       2  /* ISWC2_FSW - [1:0] */

/*
 * W324 (0x144) - ISWC 2 CTWW 2
 */
#define WM5100_ISWC2_INT1_ENA                   0x8000  /* ISWC2_INT1_ENA */
#define WM5100_ISWC2_INT1_ENA_MASK              0x8000  /* ISWC2_INT1_ENA */
#define WM5100_ISWC2_INT1_ENA_SHIFT                 15  /* ISWC2_INT1_ENA */
#define WM5100_ISWC2_INT1_ENA_WIDTH                  1  /* ISWC2_INT1_ENA */
#define WM5100_ISWC2_INT2_ENA                   0x4000  /* ISWC2_INT2_ENA */
#define WM5100_ISWC2_INT2_ENA_MASK              0x4000  /* ISWC2_INT2_ENA */
#define WM5100_ISWC2_INT2_ENA_SHIFT                 14  /* ISWC2_INT2_ENA */
#define WM5100_ISWC2_INT2_ENA_WIDTH                  1  /* ISWC2_INT2_ENA */
#define WM5100_ISWC2_INT3_ENA                   0x2000  /* ISWC2_INT3_ENA */
#define WM5100_ISWC2_INT3_ENA_MASK              0x2000  /* ISWC2_INT3_ENA */
#define WM5100_ISWC2_INT3_ENA_SHIFT                 13  /* ISWC2_INT3_ENA */
#define WM5100_ISWC2_INT3_ENA_WIDTH                  1  /* ISWC2_INT3_ENA */
#define WM5100_ISWC2_INT4_ENA                   0x1000  /* ISWC2_INT4_ENA */
#define WM5100_ISWC2_INT4_ENA_MASK              0x1000  /* ISWC2_INT4_ENA */
#define WM5100_ISWC2_INT4_ENA_SHIFT                 12  /* ISWC2_INT4_ENA */
#define WM5100_ISWC2_INT4_ENA_WIDTH                  1  /* ISWC2_INT4_ENA */
#define WM5100_ISWC2_DEC1_ENA                   0x0200  /* ISWC2_DEC1_ENA */
#define WM5100_ISWC2_DEC1_ENA_MASK              0x0200  /* ISWC2_DEC1_ENA */
#define WM5100_ISWC2_DEC1_ENA_SHIFT                  9  /* ISWC2_DEC1_ENA */
#define WM5100_ISWC2_DEC1_ENA_WIDTH                  1  /* ISWC2_DEC1_ENA */
#define WM5100_ISWC2_DEC2_ENA                   0x0100  /* ISWC2_DEC2_ENA */
#define WM5100_ISWC2_DEC2_ENA_MASK              0x0100  /* ISWC2_DEC2_ENA */
#define WM5100_ISWC2_DEC2_ENA_SHIFT                  8  /* ISWC2_DEC2_ENA */
#define WM5100_ISWC2_DEC2_ENA_WIDTH                  1  /* ISWC2_DEC2_ENA */
#define WM5100_ISWC2_DEC3_ENA                   0x0080  /* ISWC2_DEC3_ENA */
#define WM5100_ISWC2_DEC3_ENA_MASK              0x0080  /* ISWC2_DEC3_ENA */
#define WM5100_ISWC2_DEC3_ENA_SHIFT                  7  /* ISWC2_DEC3_ENA */
#define WM5100_ISWC2_DEC3_ENA_WIDTH                  1  /* ISWC2_DEC3_ENA */
#define WM5100_ISWC2_DEC4_ENA                   0x0040  /* ISWC2_DEC4_ENA */
#define WM5100_ISWC2_DEC4_ENA_MASK              0x0040  /* ISWC2_DEC4_ENA */
#define WM5100_ISWC2_DEC4_ENA_SHIFT                  6  /* ISWC2_DEC4_ENA */
#define WM5100_ISWC2_DEC4_ENA_WIDTH                  1  /* ISWC2_DEC4_ENA */
#define WM5100_ISWC2_NOTCH_ENA                  0x0001  /* ISWC2_NOTCH_ENA */
#define WM5100_ISWC2_NOTCH_ENA_MASK             0x0001  /* ISWC2_NOTCH_ENA */
#define WM5100_ISWC2_NOTCH_ENA_SHIFT                 0  /* ISWC2_NOTCH_ENA */
#define WM5100_ISWC2_NOTCH_ENA_WIDTH                 1  /* ISWC2_NOTCH_ENA */

/*
 * W386 (0x182) - FWW1 Contwow 1
 */
#define WM5100_FWW1_ENA                         0x0001  /* FWW1_ENA */
#define WM5100_FWW1_ENA_MASK                    0x0001  /* FWW1_ENA */
#define WM5100_FWW1_ENA_SHIFT                        0  /* FWW1_ENA */
#define WM5100_FWW1_ENA_WIDTH                        1  /* FWW1_ENA */

/*
 * W387 (0x183) - FWW1 Contwow 2
 */
#define WM5100_FWW1_OUTDIV_MASK                 0x3F00  /* FWW1_OUTDIV - [13:8] */
#define WM5100_FWW1_OUTDIV_SHIFT                     8  /* FWW1_OUTDIV - [13:8] */
#define WM5100_FWW1_OUTDIV_WIDTH                     6  /* FWW1_OUTDIV - [13:8] */
#define WM5100_FWW1_FWATIO_MASK                 0x0007  /* FWW1_FWATIO - [2:0] */
#define WM5100_FWW1_FWATIO_SHIFT                     0  /* FWW1_FWATIO - [2:0] */
#define WM5100_FWW1_FWATIO_WIDTH                     3  /* FWW1_FWATIO - [2:0] */

/*
 * W388 (0x184) - FWW1 Contwow 3
 */
#define WM5100_FWW1_THETA_MASK                  0xFFFF  /* FWW1_THETA - [15:0] */
#define WM5100_FWW1_THETA_SHIFT                      0  /* FWW1_THETA - [15:0] */
#define WM5100_FWW1_THETA_WIDTH                     16  /* FWW1_THETA - [15:0] */

/*
 * W390 (0x186) - FWW1 Contwow 5
 */
#define WM5100_FWW1_N_MASK                      0x03FF  /* FWW1_N - [9:0] */
#define WM5100_FWW1_N_SHIFT                          0  /* FWW1_N - [9:0] */
#define WM5100_FWW1_N_WIDTH                         10  /* FWW1_N - [9:0] */

/*
 * W391 (0x187) - FWW1 Contwow 6
 */
#define WM5100_FWW1_WEFCWK_DIV_MASK             0x00C0  /* FWW1_WEFCWK_DIV - [7:6] */
#define WM5100_FWW1_WEFCWK_DIV_SHIFT                 6  /* FWW1_WEFCWK_DIV - [7:6] */
#define WM5100_FWW1_WEFCWK_DIV_WIDTH                 2  /* FWW1_WEFCWK_DIV - [7:6] */
#define WM5100_FWW1_WEFCWK_SWC_MASK             0x000F  /* FWW1_WEFCWK_SWC - [3:0] */
#define WM5100_FWW1_WEFCWK_SWC_SHIFT                 0  /* FWW1_WEFCWK_SWC - [3:0] */
#define WM5100_FWW1_WEFCWK_SWC_WIDTH                 4  /* FWW1_WEFCWK_SWC - [3:0] */

/*
 * W392 (0x188) - FWW1 EFS 1
 */
#define WM5100_FWW1_WAMBDA_MASK                 0xFFFF  /* FWW1_WAMBDA - [15:0] */
#define WM5100_FWW1_WAMBDA_SHIFT                     0  /* FWW1_WAMBDA - [15:0] */
#define WM5100_FWW1_WAMBDA_WIDTH                    16  /* FWW1_WAMBDA - [15:0] */

/*
 * W418 (0x1A2) - FWW2 Contwow 1
 */
#define WM5100_FWW2_ENA                         0x0001  /* FWW2_ENA */
#define WM5100_FWW2_ENA_MASK                    0x0001  /* FWW2_ENA */
#define WM5100_FWW2_ENA_SHIFT                        0  /* FWW2_ENA */
#define WM5100_FWW2_ENA_WIDTH                        1  /* FWW2_ENA */

/*
 * W419 (0x1A3) - FWW2 Contwow 2
 */
#define WM5100_FWW2_OUTDIV_MASK                 0x3F00  /* FWW2_OUTDIV - [13:8] */
#define WM5100_FWW2_OUTDIV_SHIFT                     8  /* FWW2_OUTDIV - [13:8] */
#define WM5100_FWW2_OUTDIV_WIDTH                     6  /* FWW2_OUTDIV - [13:8] */
#define WM5100_FWW2_FWATIO_MASK                 0x0007  /* FWW2_FWATIO - [2:0] */
#define WM5100_FWW2_FWATIO_SHIFT                     0  /* FWW2_FWATIO - [2:0] */
#define WM5100_FWW2_FWATIO_WIDTH                     3  /* FWW2_FWATIO - [2:0] */

/*
 * W420 (0x1A4) - FWW2 Contwow 3
 */
#define WM5100_FWW2_THETA_MASK                  0xFFFF  /* FWW2_THETA - [15:0] */
#define WM5100_FWW2_THETA_SHIFT                      0  /* FWW2_THETA - [15:0] */
#define WM5100_FWW2_THETA_WIDTH                     16  /* FWW2_THETA - [15:0] */

/*
 * W422 (0x1A6) - FWW2 Contwow 5
 */
#define WM5100_FWW2_N_MASK                      0x03FF  /* FWW2_N - [9:0] */
#define WM5100_FWW2_N_SHIFT                          0  /* FWW2_N - [9:0] */
#define WM5100_FWW2_N_WIDTH                         10  /* FWW2_N - [9:0] */

/*
 * W423 (0x1A7) - FWW2 Contwow 6
 */
#define WM5100_FWW2_WEFCWK_DIV_MASK             0x00C0  /* FWW2_WEFCWK_DIV - [7:6] */
#define WM5100_FWW2_WEFCWK_DIV_SHIFT                 6  /* FWW2_WEFCWK_DIV - [7:6] */
#define WM5100_FWW2_WEFCWK_DIV_WIDTH                 2  /* FWW2_WEFCWK_DIV - [7:6] */
#define WM5100_FWW2_WEFCWK_SWC_MASK             0x000F  /* FWW2_WEFCWK_SWC - [3:0] */
#define WM5100_FWW2_WEFCWK_SWC_SHIFT                 0  /* FWW2_WEFCWK_SWC - [3:0] */
#define WM5100_FWW2_WEFCWK_SWC_WIDTH                 4  /* FWW2_WEFCWK_SWC - [3:0] */

/*
 * W424 (0x1A8) - FWW2 EFS 1
 */
#define WM5100_FWW2_WAMBDA_MASK                 0xFFFF  /* FWW2_WAMBDA - [15:0] */
#define WM5100_FWW2_WAMBDA_SHIFT                     0  /* FWW2_WAMBDA - [15:0] */
#define WM5100_FWW2_WAMBDA_WIDTH                    16  /* FWW2_WAMBDA - [15:0] */

/*
 * W512 (0x200) - Mic Chawge Pump 1
 */
#define WM5100_CP2_BYPASS                       0x0020  /* CP2_BYPASS */
#define WM5100_CP2_BYPASS_MASK                  0x0020  /* CP2_BYPASS */
#define WM5100_CP2_BYPASS_SHIFT                      5  /* CP2_BYPASS */
#define WM5100_CP2_BYPASS_WIDTH                      1  /* CP2_BYPASS */
#define WM5100_CP2_ENA                          0x0001  /* CP2_ENA */
#define WM5100_CP2_ENA_MASK                     0x0001  /* CP2_ENA */
#define WM5100_CP2_ENA_SHIFT                         0  /* CP2_ENA */
#define WM5100_CP2_ENA_WIDTH                         1  /* CP2_ENA */

/*
 * W513 (0x201) - Mic Chawge Pump 2
 */
#define WM5100_WDO2_VSEW_MASK                   0xF800  /* WDO2_VSEW - [15:11] */
#define WM5100_WDO2_VSEW_SHIFT                      11  /* WDO2_VSEW - [15:11] */
#define WM5100_WDO2_VSEW_WIDTH                       5  /* WDO2_VSEW - [15:11] */

/*
 * W514 (0x202) - HP Chawge Pump 1
 */
#define WM5100_CP1_ENA                          0x0001  /* CP1_ENA */
#define WM5100_CP1_ENA_MASK                     0x0001  /* CP1_ENA */
#define WM5100_CP1_ENA_SHIFT                         0  /* CP1_ENA */
#define WM5100_CP1_ENA_WIDTH                         1  /* CP1_ENA */

/*
 * W529 (0x211) - WDO1 Contwow
 */
#define WM5100_WDO1_BYPASS                      0x0002  /* WDO1_BYPASS */
#define WM5100_WDO1_BYPASS_MASK                 0x0002  /* WDO1_BYPASS */
#define WM5100_WDO1_BYPASS_SHIFT                     1  /* WDO1_BYPASS */
#define WM5100_WDO1_BYPASS_WIDTH                     1  /* WDO1_BYPASS */

/*
 * W533 (0x215) - Mic Bias Ctww 1
 */
#define WM5100_MICB1_DISCH                      0x0040  /* MICB1_DISCH */
#define WM5100_MICB1_DISCH_MASK                 0x0040  /* MICB1_DISCH */
#define WM5100_MICB1_DISCH_SHIFT                     6  /* MICB1_DISCH */
#define WM5100_MICB1_DISCH_WIDTH                     1  /* MICB1_DISCH */
#define WM5100_MICB1_WATE                       0x0020  /* MICB1_WATE */
#define WM5100_MICB1_WATE_MASK                  0x0020  /* MICB1_WATE */
#define WM5100_MICB1_WATE_SHIFT                      5  /* MICB1_WATE */
#define WM5100_MICB1_WATE_WIDTH                      1  /* MICB1_WATE */
#define WM5100_MICB1_WVW_MASK                   0x001C  /* MICB1_WVW - [4:2] */
#define WM5100_MICB1_WVW_SHIFT                       2  /* MICB1_WVW - [4:2] */
#define WM5100_MICB1_WVW_WIDTH                       3  /* MICB1_WVW - [4:2] */
#define WM5100_MICB1_BYPASS                     0x0002  /* MICB1_BYPASS */
#define WM5100_MICB1_BYPASS_MASK                0x0002  /* MICB1_BYPASS */
#define WM5100_MICB1_BYPASS_SHIFT                    1  /* MICB1_BYPASS */
#define WM5100_MICB1_BYPASS_WIDTH                    1  /* MICB1_BYPASS */
#define WM5100_MICB1_ENA                        0x0001  /* MICB1_ENA */
#define WM5100_MICB1_ENA_MASK                   0x0001  /* MICB1_ENA */
#define WM5100_MICB1_ENA_SHIFT                       0  /* MICB1_ENA */
#define WM5100_MICB1_ENA_WIDTH                       1  /* MICB1_ENA */

/*
 * W534 (0x216) - Mic Bias Ctww 2
 */
#define WM5100_MICB2_DISCH                      0x0040  /* MICB2_DISCH */
#define WM5100_MICB2_DISCH_MASK                 0x0040  /* MICB2_DISCH */
#define WM5100_MICB2_DISCH_SHIFT                     6  /* MICB2_DISCH */
#define WM5100_MICB2_DISCH_WIDTH                     1  /* MICB2_DISCH */
#define WM5100_MICB2_WATE                       0x0020  /* MICB2_WATE */
#define WM5100_MICB2_WATE_MASK                  0x0020  /* MICB2_WATE */
#define WM5100_MICB2_WATE_SHIFT                      5  /* MICB2_WATE */
#define WM5100_MICB2_WATE_WIDTH                      1  /* MICB2_WATE */
#define WM5100_MICB2_WVW_MASK                   0x001C  /* MICB2_WVW - [4:2] */
#define WM5100_MICB2_WVW_SHIFT                       2  /* MICB2_WVW - [4:2] */
#define WM5100_MICB2_WVW_WIDTH                       3  /* MICB2_WVW - [4:2] */
#define WM5100_MICB2_BYPASS                     0x0002  /* MICB2_BYPASS */
#define WM5100_MICB2_BYPASS_MASK                0x0002  /* MICB2_BYPASS */
#define WM5100_MICB2_BYPASS_SHIFT                    1  /* MICB2_BYPASS */
#define WM5100_MICB2_BYPASS_WIDTH                    1  /* MICB2_BYPASS */
#define WM5100_MICB2_ENA                        0x0001  /* MICB2_ENA */
#define WM5100_MICB2_ENA_MASK                   0x0001  /* MICB2_ENA */
#define WM5100_MICB2_ENA_SHIFT                       0  /* MICB2_ENA */
#define WM5100_MICB2_ENA_WIDTH                       1  /* MICB2_ENA */

/*
 * W535 (0x217) - Mic Bias Ctww 3
 */
#define WM5100_MICB3_DISCH                      0x0040  /* MICB3_DISCH */
#define WM5100_MICB3_DISCH_MASK                 0x0040  /* MICB3_DISCH */
#define WM5100_MICB3_DISCH_SHIFT                     6  /* MICB3_DISCH */
#define WM5100_MICB3_DISCH_WIDTH                     1  /* MICB3_DISCH */
#define WM5100_MICB3_WATE                       0x0020  /* MICB3_WATE */
#define WM5100_MICB3_WATE_MASK                  0x0020  /* MICB3_WATE */
#define WM5100_MICB3_WATE_SHIFT                      5  /* MICB3_WATE */
#define WM5100_MICB3_WATE_WIDTH                      1  /* MICB3_WATE */
#define WM5100_MICB3_WVW_MASK                   0x001C  /* MICB3_WVW - [4:2] */
#define WM5100_MICB3_WVW_SHIFT                       2  /* MICB3_WVW - [4:2] */
#define WM5100_MICB3_WVW_WIDTH                       3  /* MICB3_WVW - [4:2] */
#define WM5100_MICB3_BYPASS                     0x0002  /* MICB3_BYPASS */
#define WM5100_MICB3_BYPASS_MASK                0x0002  /* MICB3_BYPASS */
#define WM5100_MICB3_BYPASS_SHIFT                    1  /* MICB3_BYPASS */
#define WM5100_MICB3_BYPASS_WIDTH                    1  /* MICB3_BYPASS */
#define WM5100_MICB3_ENA                        0x0001  /* MICB3_ENA */
#define WM5100_MICB3_ENA_MASK                   0x0001  /* MICB3_ENA */
#define WM5100_MICB3_ENA_SHIFT                       0  /* MICB3_ENA */
#define WM5100_MICB3_ENA_WIDTH                       1  /* MICB3_ENA */

/*
 * W640 (0x280) - Accessowy Detect Mode 1
 */
#define WM5100_ACCDET_BIAS_SWC_MASK             0xC000  /* ACCDET_BIAS_SWC - [15:14] */
#define WM5100_ACCDET_BIAS_SWC_SHIFT                14  /* ACCDET_BIAS_SWC - [15:14] */
#define WM5100_ACCDET_BIAS_SWC_WIDTH                 2  /* ACCDET_BIAS_SWC - [15:14] */
#define WM5100_ACCDET_SWC                       0x2000  /* ACCDET_SWC */
#define WM5100_ACCDET_SWC_MASK                  0x2000  /* ACCDET_SWC */
#define WM5100_ACCDET_SWC_SHIFT                     13  /* ACCDET_SWC */
#define WM5100_ACCDET_SWC_WIDTH                      1  /* ACCDET_SWC */
#define WM5100_ACCDET_MODE_MASK                 0x0003  /* ACCDET_MODE - [1:0] */
#define WM5100_ACCDET_MODE_SHIFT                     0  /* ACCDET_MODE - [1:0] */
#define WM5100_ACCDET_MODE_WIDTH                     2  /* ACCDET_MODE - [1:0] */

/*
 * W648 (0x288) - Headphone Detect 1
 */
#define WM5100_HP_HOWDTIME_MASK                 0x00E0  /* HP_HOWDTIME - [7:5] */
#define WM5100_HP_HOWDTIME_SHIFT                     5  /* HP_HOWDTIME - [7:5] */
#define WM5100_HP_HOWDTIME_WIDTH                     3  /* HP_HOWDTIME - [7:5] */
#define WM5100_HP_CWK_DIV_MASK                  0x0018  /* HP_CWK_DIV - [4:3] */
#define WM5100_HP_CWK_DIV_SHIFT                      3  /* HP_CWK_DIV - [4:3] */
#define WM5100_HP_CWK_DIV_WIDTH                      2  /* HP_CWK_DIV - [4:3] */
#define WM5100_HP_STEP_SIZE                     0x0002  /* HP_STEP_SIZE */
#define WM5100_HP_STEP_SIZE_MASK                0x0002  /* HP_STEP_SIZE */
#define WM5100_HP_STEP_SIZE_SHIFT                    1  /* HP_STEP_SIZE */
#define WM5100_HP_STEP_SIZE_WIDTH                    1  /* HP_STEP_SIZE */
#define WM5100_HP_POWW                          0x0001  /* HP_POWW */
#define WM5100_HP_POWW_MASK                     0x0001  /* HP_POWW */
#define WM5100_HP_POWW_SHIFT                         0  /* HP_POWW */
#define WM5100_HP_POWW_WIDTH                         1  /* HP_POWW */

/*
 * W649 (0x289) - Headphone Detect 2
 */
#define WM5100_HP_DONE                          0x0080  /* HP_DONE */
#define WM5100_HP_DONE_MASK                     0x0080  /* HP_DONE */
#define WM5100_HP_DONE_SHIFT                         7  /* HP_DONE */
#define WM5100_HP_DONE_WIDTH                         1  /* HP_DONE */
#define WM5100_HP_WVW_MASK                      0x007F  /* HP_WVW - [6:0] */
#define WM5100_HP_WVW_SHIFT                          0  /* HP_WVW - [6:0] */
#define WM5100_HP_WVW_WIDTH                          7  /* HP_WVW - [6:0] */

/*
 * W656 (0x290) - Mic Detect 1
 */
#define WM5100_ACCDET_BIAS_STAWTTIME_MASK       0xF000  /* ACCDET_BIAS_STAWTTIME - [15:12] */
#define WM5100_ACCDET_BIAS_STAWTTIME_SHIFT          12  /* ACCDET_BIAS_STAWTTIME - [15:12] */
#define WM5100_ACCDET_BIAS_STAWTTIME_WIDTH           4  /* ACCDET_BIAS_STAWTTIME - [15:12] */
#define WM5100_ACCDET_WATE_MASK                 0x0F00  /* ACCDET_WATE - [11:8] */
#define WM5100_ACCDET_WATE_SHIFT                     8  /* ACCDET_WATE - [11:8] */
#define WM5100_ACCDET_WATE_WIDTH                     4  /* ACCDET_WATE - [11:8] */
#define WM5100_ACCDET_DBTIME                    0x0002  /* ACCDET_DBTIME */
#define WM5100_ACCDET_DBTIME_MASK               0x0002  /* ACCDET_DBTIME */
#define WM5100_ACCDET_DBTIME_SHIFT                   1  /* ACCDET_DBTIME */
#define WM5100_ACCDET_DBTIME_WIDTH                   1  /* ACCDET_DBTIME */
#define WM5100_ACCDET_ENA                       0x0001  /* ACCDET_ENA */
#define WM5100_ACCDET_ENA_MASK                  0x0001  /* ACCDET_ENA */
#define WM5100_ACCDET_ENA_SHIFT                      0  /* ACCDET_ENA */
#define WM5100_ACCDET_ENA_WIDTH                      1  /* ACCDET_ENA */

/*
 * W657 (0x291) - Mic Detect 2
 */
#define WM5100_ACCDET_WVW_SEW_MASK              0x00FF  /* ACCDET_WVW_SEW - [7:0] */
#define WM5100_ACCDET_WVW_SEW_SHIFT                  0  /* ACCDET_WVW_SEW - [7:0] */
#define WM5100_ACCDET_WVW_SEW_WIDTH                  8  /* ACCDET_WVW_SEW - [7:0] */

/*
 * W658 (0x292) - Mic Detect 3
 */
#define WM5100_ACCDET_WVW_MASK                  0x07FC  /* ACCDET_WVW - [10:2] */
#define WM5100_ACCDET_WVW_SHIFT                      2  /* ACCDET_WVW - [10:2] */
#define WM5100_ACCDET_WVW_WIDTH                      9  /* ACCDET_WVW - [10:2] */
#define WM5100_ACCDET_VAWID                     0x0002  /* ACCDET_VAWID */
#define WM5100_ACCDET_VAWID_MASK                0x0002  /* ACCDET_VAWID */
#define WM5100_ACCDET_VAWID_SHIFT                    1  /* ACCDET_VAWID */
#define WM5100_ACCDET_VAWID_WIDTH                    1  /* ACCDET_VAWID */
#define WM5100_ACCDET_STS                       0x0001  /* ACCDET_STS */
#define WM5100_ACCDET_STS_MASK                  0x0001  /* ACCDET_STS */
#define WM5100_ACCDET_STS_SHIFT                      0  /* ACCDET_STS */
#define WM5100_ACCDET_STS_WIDTH                      1  /* ACCDET_STS */

/*
 * W699 (0x2BB) - Misc Contwow
 */
#define WM5100_HPCOM_SWC                         0x200  /* HPCOM_SWC */
#define WM5100_HPCOM_SWC_SHIFT                       9  /* HPCOM_SWC */

/*
 * W769 (0x301) - Input Enabwes
 */
#define WM5100_IN4W_ENA                         0x0080  /* IN4W_ENA */
#define WM5100_IN4W_ENA_MASK                    0x0080  /* IN4W_ENA */
#define WM5100_IN4W_ENA_SHIFT                        7  /* IN4W_ENA */
#define WM5100_IN4W_ENA_WIDTH                        1  /* IN4W_ENA */
#define WM5100_IN4W_ENA                         0x0040  /* IN4W_ENA */
#define WM5100_IN4W_ENA_MASK                    0x0040  /* IN4W_ENA */
#define WM5100_IN4W_ENA_SHIFT                        6  /* IN4W_ENA */
#define WM5100_IN4W_ENA_WIDTH                        1  /* IN4W_ENA */
#define WM5100_IN3W_ENA                         0x0020  /* IN3W_ENA */
#define WM5100_IN3W_ENA_MASK                    0x0020  /* IN3W_ENA */
#define WM5100_IN3W_ENA_SHIFT                        5  /* IN3W_ENA */
#define WM5100_IN3W_ENA_WIDTH                        1  /* IN3W_ENA */
#define WM5100_IN3W_ENA                         0x0010  /* IN3W_ENA */
#define WM5100_IN3W_ENA_MASK                    0x0010  /* IN3W_ENA */
#define WM5100_IN3W_ENA_SHIFT                        4  /* IN3W_ENA */
#define WM5100_IN3W_ENA_WIDTH                        1  /* IN3W_ENA */
#define WM5100_IN2W_ENA                         0x0008  /* IN2W_ENA */
#define WM5100_IN2W_ENA_MASK                    0x0008  /* IN2W_ENA */
#define WM5100_IN2W_ENA_SHIFT                        3  /* IN2W_ENA */
#define WM5100_IN2W_ENA_WIDTH                        1  /* IN2W_ENA */
#define WM5100_IN2W_ENA                         0x0004  /* IN2W_ENA */
#define WM5100_IN2W_ENA_MASK                    0x0004  /* IN2W_ENA */
#define WM5100_IN2W_ENA_SHIFT                        2  /* IN2W_ENA */
#define WM5100_IN2W_ENA_WIDTH                        1  /* IN2W_ENA */
#define WM5100_IN1W_ENA                         0x0002  /* IN1W_ENA */
#define WM5100_IN1W_ENA_MASK                    0x0002  /* IN1W_ENA */
#define WM5100_IN1W_ENA_SHIFT                        1  /* IN1W_ENA */
#define WM5100_IN1W_ENA_WIDTH                        1  /* IN1W_ENA */
#define WM5100_IN1W_ENA                         0x0001  /* IN1W_ENA */
#define WM5100_IN1W_ENA_MASK                    0x0001  /* IN1W_ENA */
#define WM5100_IN1W_ENA_SHIFT                        0  /* IN1W_ENA */
#define WM5100_IN1W_ENA_WIDTH                        1  /* IN1W_ENA */

/*
 * W770 (0x302) - Input Enabwes Status
 */
#define WM5100_IN4W_ENA_STS                     0x0080  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_MASK                0x0080  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_SHIFT                    7  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_WIDTH                    1  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS                     0x0040  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_MASK                0x0040  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_SHIFT                    6  /* IN4W_ENA_STS */
#define WM5100_IN4W_ENA_STS_WIDTH                    1  /* IN4W_ENA_STS */
#define WM5100_IN3W_ENA_STS                     0x0020  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_MASK                0x0020  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_SHIFT                    5  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_WIDTH                    1  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS                     0x0010  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_MASK                0x0010  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_SHIFT                    4  /* IN3W_ENA_STS */
#define WM5100_IN3W_ENA_STS_WIDTH                    1  /* IN3W_ENA_STS */
#define WM5100_IN2W_ENA_STS                     0x0008  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_MASK                0x0008  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_SHIFT                    3  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_WIDTH                    1  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS                     0x0004  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_MASK                0x0004  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_SHIFT                    2  /* IN2W_ENA_STS */
#define WM5100_IN2W_ENA_STS_WIDTH                    1  /* IN2W_ENA_STS */
#define WM5100_IN1W_ENA_STS                     0x0002  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_MASK                0x0002  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_SHIFT                    1  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_WIDTH                    1  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS                     0x0001  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_MASK                0x0001  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_SHIFT                    0  /* IN1W_ENA_STS */
#define WM5100_IN1W_ENA_STS_WIDTH                    1  /* IN1W_ENA_STS */

/*
 * W784 (0x310) - IN1W Contwow
 */
#define WM5100_IN_WATE_MASK                     0xC000  /* IN_WATE - [15:14] */
#define WM5100_IN_WATE_SHIFT                        14  /* IN_WATE - [15:14] */
#define WM5100_IN_WATE_WIDTH                         2  /* IN_WATE - [15:14] */
#define WM5100_IN1_OSW                          0x2000  /* IN1_OSW */
#define WM5100_IN1_OSW_MASK                     0x2000  /* IN1_OSW */
#define WM5100_IN1_OSW_SHIFT                        13  /* IN1_OSW */
#define WM5100_IN1_OSW_WIDTH                         1  /* IN1_OSW */
#define WM5100_IN1_DMIC_SUP_MASK                0x1800  /* IN1_DMIC_SUP - [12:11] */
#define WM5100_IN1_DMIC_SUP_SHIFT                   11  /* IN1_DMIC_SUP - [12:11] */
#define WM5100_IN1_DMIC_SUP_WIDTH                    2  /* IN1_DMIC_SUP - [12:11] */
#define WM5100_IN1_MODE_MASK                    0x0600  /* IN1_MODE - [10:9] */
#define WM5100_IN1_MODE_SHIFT                        9  /* IN1_MODE - [10:9] */
#define WM5100_IN1_MODE_WIDTH                        2  /* IN1_MODE - [10:9] */
#define WM5100_IN1W_PGA_VOW_MASK                0x00FE  /* IN1W_PGA_VOW - [7:1] */
#define WM5100_IN1W_PGA_VOW_SHIFT                    1  /* IN1W_PGA_VOW - [7:1] */
#define WM5100_IN1W_PGA_VOW_WIDTH                    7  /* IN1W_PGA_VOW - [7:1] */

/*
 * W785 (0x311) - IN1W Contwow
 */
#define WM5100_IN1W_PGA_VOW_MASK                0x00FE  /* IN1W_PGA_VOW - [7:1] */
#define WM5100_IN1W_PGA_VOW_SHIFT                    1  /* IN1W_PGA_VOW - [7:1] */
#define WM5100_IN1W_PGA_VOW_WIDTH                    7  /* IN1W_PGA_VOW - [7:1] */

/*
 * W786 (0x312) - IN2W Contwow
 */
#define WM5100_IN2_OSW                          0x2000  /* IN2_OSW */
#define WM5100_IN2_OSW_MASK                     0x2000  /* IN2_OSW */
#define WM5100_IN2_OSW_SHIFT                        13  /* IN2_OSW */
#define WM5100_IN2_OSW_WIDTH                         1  /* IN2_OSW */
#define WM5100_IN2_DMIC_SUP_MASK                0x1800  /* IN2_DMIC_SUP - [12:11] */
#define WM5100_IN2_DMIC_SUP_SHIFT                   11  /* IN2_DMIC_SUP - [12:11] */
#define WM5100_IN2_DMIC_SUP_WIDTH                    2  /* IN2_DMIC_SUP - [12:11] */
#define WM5100_IN2_MODE_MASK                    0x0600  /* IN2_MODE - [10:9] */
#define WM5100_IN2_MODE_SHIFT                        9  /* IN2_MODE - [10:9] */
#define WM5100_IN2_MODE_WIDTH                        2  /* IN2_MODE - [10:9] */
#define WM5100_IN2W_PGA_VOW_MASK                0x00FE  /* IN2W_PGA_VOW - [7:1] */
#define WM5100_IN2W_PGA_VOW_SHIFT                    1  /* IN2W_PGA_VOW - [7:1] */
#define WM5100_IN2W_PGA_VOW_WIDTH                    7  /* IN2W_PGA_VOW - [7:1] */

/*
 * W787 (0x313) - IN2W Contwow
 */
#define WM5100_IN2W_PGA_VOW_MASK                0x00FE  /* IN2W_PGA_VOW - [7:1] */
#define WM5100_IN2W_PGA_VOW_SHIFT                    1  /* IN2W_PGA_VOW - [7:1] */
#define WM5100_IN2W_PGA_VOW_WIDTH                    7  /* IN2W_PGA_VOW - [7:1] */

/*
 * W788 (0x314) - IN3W Contwow
 */
#define WM5100_IN3_OSW                          0x2000  /* IN3_OSW */
#define WM5100_IN3_OSW_MASK                     0x2000  /* IN3_OSW */
#define WM5100_IN3_OSW_SHIFT                        13  /* IN3_OSW */
#define WM5100_IN3_OSW_WIDTH                         1  /* IN3_OSW */
#define WM5100_IN3_DMIC_SUP_MASK                0x1800  /* IN3_DMIC_SUP - [12:11] */
#define WM5100_IN3_DMIC_SUP_SHIFT                   11  /* IN3_DMIC_SUP - [12:11] */
#define WM5100_IN3_DMIC_SUP_WIDTH                    2  /* IN3_DMIC_SUP - [12:11] */
#define WM5100_IN3_MODE_MASK                    0x0600  /* IN3_MODE - [10:9] */
#define WM5100_IN3_MODE_SHIFT                        9  /* IN3_MODE - [10:9] */
#define WM5100_IN3_MODE_WIDTH                        2  /* IN3_MODE - [10:9] */
#define WM5100_IN3W_PGA_VOW_MASK                0x00FE  /* IN3W_PGA_VOW - [7:1] */
#define WM5100_IN3W_PGA_VOW_SHIFT                    1  /* IN3W_PGA_VOW - [7:1] */
#define WM5100_IN3W_PGA_VOW_WIDTH                    7  /* IN3W_PGA_VOW - [7:1] */

/*
 * W789 (0x315) - IN3W Contwow
 */
#define WM5100_IN3W_PGA_VOW_MASK                0x00FE  /* IN3W_PGA_VOW - [7:1] */
#define WM5100_IN3W_PGA_VOW_SHIFT                    1  /* IN3W_PGA_VOW - [7:1] */
#define WM5100_IN3W_PGA_VOW_WIDTH                    7  /* IN3W_PGA_VOW - [7:1] */

/*
 * W790 (0x316) - IN4W Contwow
 */
#define WM5100_IN4_OSW                          0x2000  /* IN4_OSW */
#define WM5100_IN4_OSW_MASK                     0x2000  /* IN4_OSW */
#define WM5100_IN4_OSW_SHIFT                        13  /* IN4_OSW */
#define WM5100_IN4_OSW_WIDTH                         1  /* IN4_OSW */
#define WM5100_IN4_DMIC_SUP_MASK                0x1800  /* IN4_DMIC_SUP - [12:11] */
#define WM5100_IN4_DMIC_SUP_SHIFT                   11  /* IN4_DMIC_SUP - [12:11] */
#define WM5100_IN4_DMIC_SUP_WIDTH                    2  /* IN4_DMIC_SUP - [12:11] */
#define WM5100_IN4_MODE_MASK                    0x0600  /* IN4_MODE - [10:9] */
#define WM5100_IN4_MODE_SHIFT                        9  /* IN4_MODE - [10:9] */
#define WM5100_IN4_MODE_WIDTH                        2  /* IN4_MODE - [10:9] */
#define WM5100_IN4W_PGA_VOW_MASK                0x00FE  /* IN4W_PGA_VOW - [7:1] */
#define WM5100_IN4W_PGA_VOW_SHIFT                    1  /* IN4W_PGA_VOW - [7:1] */
#define WM5100_IN4W_PGA_VOW_WIDTH                    7  /* IN4W_PGA_VOW - [7:1] */

/*
 * W791 (0x317) - IN4W Contwow
 */
#define WM5100_IN4W_PGA_VOW_MASK                0x00FE  /* IN4W_PGA_VOW - [7:1] */
#define WM5100_IN4W_PGA_VOW_SHIFT                    1  /* IN4W_PGA_VOW - [7:1] */
#define WM5100_IN4W_PGA_VOW_WIDTH                    7  /* IN4W_PGA_VOW - [7:1] */

/*
 * W792 (0x318) - WXANC_SWC
 */
#define WM5100_IN_WXANC_SEW_MASK                0x0007  /* IN_WXANC_SEW - [2:0] */
#define WM5100_IN_WXANC_SEW_SHIFT                    0  /* IN_WXANC_SEW - [2:0] */
#define WM5100_IN_WXANC_SEW_WIDTH                    3  /* IN_WXANC_SEW - [2:0] */

/*
 * W793 (0x319) - Input Vowume Wamp
 */
#define WM5100_IN_VD_WAMP_MASK                  0x0070  /* IN_VD_WAMP - [6:4] */
#define WM5100_IN_VD_WAMP_SHIFT                      4  /* IN_VD_WAMP - [6:4] */
#define WM5100_IN_VD_WAMP_WIDTH                      3  /* IN_VD_WAMP - [6:4] */
#define WM5100_IN_VI_WAMP_MASK                  0x0007  /* IN_VI_WAMP - [2:0] */
#define WM5100_IN_VI_WAMP_SHIFT                      0  /* IN_VI_WAMP - [2:0] */
#define WM5100_IN_VI_WAMP_WIDTH                      3  /* IN_VI_WAMP - [2:0] */

/*
 * W800 (0x320) - ADC Digitaw Vowume 1W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN1W_MUTE                        0x0100  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_MASK                   0x0100  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_SHIFT                       8  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_WIDTH                       1  /* IN1W_MUTE */
#define WM5100_IN1W_VOW_MASK                    0x00FF  /* IN1W_VOW - [7:0] */
#define WM5100_IN1W_VOW_SHIFT                        0  /* IN1W_VOW - [7:0] */
#define WM5100_IN1W_VOW_WIDTH                        8  /* IN1W_VOW - [7:0] */

/*
 * W801 (0x321) - ADC Digitaw Vowume 1W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN1W_MUTE                        0x0100  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_MASK                   0x0100  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_SHIFT                       8  /* IN1W_MUTE */
#define WM5100_IN1W_MUTE_WIDTH                       1  /* IN1W_MUTE */
#define WM5100_IN1W_VOW_MASK                    0x00FF  /* IN1W_VOW - [7:0] */
#define WM5100_IN1W_VOW_SHIFT                        0  /* IN1W_VOW - [7:0] */
#define WM5100_IN1W_VOW_WIDTH                        8  /* IN1W_VOW - [7:0] */

/*
 * W802 (0x322) - ADC Digitaw Vowume 2W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN2W_MUTE                        0x0100  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_MASK                   0x0100  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_SHIFT                       8  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_WIDTH                       1  /* IN2W_MUTE */
#define WM5100_IN2W_VOW_MASK                    0x00FF  /* IN2W_VOW - [7:0] */
#define WM5100_IN2W_VOW_SHIFT                        0  /* IN2W_VOW - [7:0] */
#define WM5100_IN2W_VOW_WIDTH                        8  /* IN2W_VOW - [7:0] */

/*
 * W803 (0x323) - ADC Digitaw Vowume 2W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN2W_MUTE                        0x0100  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_MASK                   0x0100  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_SHIFT                       8  /* IN2W_MUTE */
#define WM5100_IN2W_MUTE_WIDTH                       1  /* IN2W_MUTE */
#define WM5100_IN2W_VOW_MASK                    0x00FF  /* IN2W_VOW - [7:0] */
#define WM5100_IN2W_VOW_SHIFT                        0  /* IN2W_VOW - [7:0] */
#define WM5100_IN2W_VOW_WIDTH                        8  /* IN2W_VOW - [7:0] */

/*
 * W804 (0x324) - ADC Digitaw Vowume 3W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN3W_MUTE                        0x0100  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_MASK                   0x0100  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_SHIFT                       8  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_WIDTH                       1  /* IN3W_MUTE */
#define WM5100_IN3W_VOW_MASK                    0x00FF  /* IN3W_VOW - [7:0] */
#define WM5100_IN3W_VOW_SHIFT                        0  /* IN3W_VOW - [7:0] */
#define WM5100_IN3W_VOW_WIDTH                        8  /* IN3W_VOW - [7:0] */

/*
 * W805 (0x325) - ADC Digitaw Vowume 3W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN3W_MUTE                        0x0100  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_MASK                   0x0100  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_SHIFT                       8  /* IN3W_MUTE */
#define WM5100_IN3W_MUTE_WIDTH                       1  /* IN3W_MUTE */
#define WM5100_IN3W_VOW_MASK                    0x00FF  /* IN3W_VOW - [7:0] */
#define WM5100_IN3W_VOW_SHIFT                        0  /* IN3W_VOW - [7:0] */
#define WM5100_IN3W_VOW_WIDTH                        8  /* IN3W_VOW - [7:0] */

/*
 * W806 (0x326) - ADC Digitaw Vowume 4W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN4W_MUTE                        0x0100  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_MASK                   0x0100  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_SHIFT                       8  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_WIDTH                       1  /* IN4W_MUTE */
#define WM5100_IN4W_VOW_MASK                    0x00FF  /* IN4W_VOW - [7:0] */
#define WM5100_IN4W_VOW_SHIFT                        0  /* IN4W_VOW - [7:0] */
#define WM5100_IN4W_VOW_WIDTH                        8  /* IN4W_VOW - [7:0] */

/*
 * W807 (0x327) - ADC Digitaw Vowume 4W
 */
#define WM5100_IN_VU                            0x0200  /* IN_VU */
#define WM5100_IN_VU_MASK                       0x0200  /* IN_VU */
#define WM5100_IN_VU_SHIFT                           9  /* IN_VU */
#define WM5100_IN_VU_WIDTH                           1  /* IN_VU */
#define WM5100_IN4W_MUTE                        0x0100  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_MASK                   0x0100  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_SHIFT                       8  /* IN4W_MUTE */
#define WM5100_IN4W_MUTE_WIDTH                       1  /* IN4W_MUTE */
#define WM5100_IN4W_VOW_MASK                    0x00FF  /* IN4W_VOW - [7:0] */
#define WM5100_IN4W_VOW_SHIFT                        0  /* IN4W_VOW - [7:0] */
#define WM5100_IN4W_VOW_WIDTH                        8  /* IN4W_VOW - [7:0] */

/*
 * W1025 (0x401) - Output Enabwes 2
 */
#define WM5100_OUT6W_ENA                        0x0800  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_MASK                   0x0800  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_SHIFT                      11  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_WIDTH                       1  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA                        0x0400  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_MASK                   0x0400  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_SHIFT                      10  /* OUT6W_ENA */
#define WM5100_OUT6W_ENA_WIDTH                       1  /* OUT6W_ENA */
#define WM5100_OUT5W_ENA                        0x0200  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_MASK                   0x0200  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_SHIFT                       9  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_WIDTH                       1  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA                        0x0100  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_MASK                   0x0100  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_SHIFT                       8  /* OUT5W_ENA */
#define WM5100_OUT5W_ENA_WIDTH                       1  /* OUT5W_ENA */
#define WM5100_OUT4W_ENA                        0x0080  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_MASK                   0x0080  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_SHIFT                       7  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_WIDTH                       1  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA                        0x0040  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_MASK                   0x0040  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_SHIFT                       6  /* OUT4W_ENA */
#define WM5100_OUT4W_ENA_WIDTH                       1  /* OUT4W_ENA */

/*
 * W1026 (0x402) - Output Status 1
 */
#define WM5100_OUT3W_ENA_STS                    0x0020  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_MASK               0x0020  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_SHIFT                   5  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_WIDTH                   1  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS                    0x0010  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_MASK               0x0010  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_SHIFT                   4  /* OUT3W_ENA_STS */
#define WM5100_OUT3W_ENA_STS_WIDTH                   1  /* OUT3W_ENA_STS */
#define WM5100_OUT2W_ENA_STS                    0x0008  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_MASK               0x0008  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_SHIFT                   3  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_WIDTH                   1  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS                    0x0004  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_MASK               0x0004  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_SHIFT                   2  /* OUT2W_ENA_STS */
#define WM5100_OUT2W_ENA_STS_WIDTH                   1  /* OUT2W_ENA_STS */
#define WM5100_OUT1W_ENA_STS                    0x0002  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_MASK               0x0002  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_SHIFT                   1  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_WIDTH                   1  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS                    0x0001  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_MASK               0x0001  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_SHIFT                   0  /* OUT1W_ENA_STS */
#define WM5100_OUT1W_ENA_STS_WIDTH                   1  /* OUT1W_ENA_STS */

/*
 * W1027 (0x403) - Output Status 2
 */
#define WM5100_OUT6W_ENA_STS                    0x0800  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_MASK               0x0800  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_SHIFT                  11  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_WIDTH                   1  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS                    0x0400  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_MASK               0x0400  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_SHIFT                  10  /* OUT6W_ENA_STS */
#define WM5100_OUT6W_ENA_STS_WIDTH                   1  /* OUT6W_ENA_STS */
#define WM5100_OUT5W_ENA_STS                    0x0200  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_MASK               0x0200  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_SHIFT                   9  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_WIDTH                   1  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS                    0x0100  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_MASK               0x0100  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_SHIFT                   8  /* OUT5W_ENA_STS */
#define WM5100_OUT5W_ENA_STS_WIDTH                   1  /* OUT5W_ENA_STS */
#define WM5100_OUT4W_ENA_STS                    0x0080  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_MASK               0x0080  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_SHIFT                   7  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_WIDTH                   1  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS                    0x0040  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_MASK               0x0040  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_SHIFT                   6  /* OUT4W_ENA_STS */
#define WM5100_OUT4W_ENA_STS_WIDTH                   1  /* OUT4W_ENA_STS */

/*
 * W1032 (0x408) - Channew Enabwes 1
 */
#define WM5100_HP3W_ENA                         0x0020  /* HP3W_ENA */
#define WM5100_HP3W_ENA_MASK                    0x0020  /* HP3W_ENA */
#define WM5100_HP3W_ENA_SHIFT                        5  /* HP3W_ENA */
#define WM5100_HP3W_ENA_WIDTH                        1  /* HP3W_ENA */
#define WM5100_HP3W_ENA                         0x0010  /* HP3W_ENA */
#define WM5100_HP3W_ENA_MASK                    0x0010  /* HP3W_ENA */
#define WM5100_HP3W_ENA_SHIFT                        4  /* HP3W_ENA */
#define WM5100_HP3W_ENA_WIDTH                        1  /* HP3W_ENA */
#define WM5100_HP2W_ENA                         0x0008  /* HP2W_ENA */
#define WM5100_HP2W_ENA_MASK                    0x0008  /* HP2W_ENA */
#define WM5100_HP2W_ENA_SHIFT                        3  /* HP2W_ENA */
#define WM5100_HP2W_ENA_WIDTH                        1  /* HP2W_ENA */
#define WM5100_HP2W_ENA                         0x0004  /* HP2W_ENA */
#define WM5100_HP2W_ENA_MASK                    0x0004  /* HP2W_ENA */
#define WM5100_HP2W_ENA_SHIFT                        2  /* HP2W_ENA */
#define WM5100_HP2W_ENA_WIDTH                        1  /* HP2W_ENA */
#define WM5100_HP1W_ENA                         0x0002  /* HP1W_ENA */
#define WM5100_HP1W_ENA_MASK                    0x0002  /* HP1W_ENA */
#define WM5100_HP1W_ENA_SHIFT                        1  /* HP1W_ENA */
#define WM5100_HP1W_ENA_WIDTH                        1  /* HP1W_ENA */
#define WM5100_HP1W_ENA                         0x0001  /* HP1W_ENA */
#define WM5100_HP1W_ENA_MASK                    0x0001  /* HP1W_ENA */
#define WM5100_HP1W_ENA_SHIFT                        0  /* HP1W_ENA */
#define WM5100_HP1W_ENA_WIDTH                        1  /* HP1W_ENA */

/*
 * W1040 (0x410) - Out Vowume 1W
 */
#define WM5100_OUT_WATE_MASK                    0xC000  /* OUT_WATE - [15:14] */
#define WM5100_OUT_WATE_SHIFT                       14  /* OUT_WATE - [15:14] */
#define WM5100_OUT_WATE_WIDTH                        2  /* OUT_WATE - [15:14] */
#define WM5100_OUT1_OSW                         0x2000  /* OUT1_OSW */
#define WM5100_OUT1_OSW_MASK                    0x2000  /* OUT1_OSW */
#define WM5100_OUT1_OSW_SHIFT                       13  /* OUT1_OSW */
#define WM5100_OUT1_OSW_WIDTH                        1  /* OUT1_OSW */
#define WM5100_OUT1_MONO                        0x1000  /* OUT1_MONO */
#define WM5100_OUT1_MONO_MASK                   0x1000  /* OUT1_MONO */
#define WM5100_OUT1_MONO_SHIFT                      12  /* OUT1_MONO */
#define WM5100_OUT1_MONO_WIDTH                       1  /* OUT1_MONO */
#define WM5100_OUT1W_ANC_SWC                    0x0800  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_MASK               0x0800  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_SHIFT                  11  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_WIDTH                   1  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_PGA_VOW_MASK               0x00FE  /* OUT1W_PGA_VOW - [7:1] */
#define WM5100_OUT1W_PGA_VOW_SHIFT                   1  /* OUT1W_PGA_VOW - [7:1] */
#define WM5100_OUT1W_PGA_VOW_WIDTH                   7  /* OUT1W_PGA_VOW - [7:1] */

/*
 * W1041 (0x411) - Out Vowume 1W
 */
#define WM5100_OUT1W_ANC_SWC                    0x0800  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_MASK               0x0800  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_SHIFT                  11  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_ANC_SWC_WIDTH                   1  /* OUT1W_ANC_SWC */
#define WM5100_OUT1W_PGA_VOW_MASK               0x00FE  /* OUT1W_PGA_VOW - [7:1] */
#define WM5100_OUT1W_PGA_VOW_SHIFT                   1  /* OUT1W_PGA_VOW - [7:1] */
#define WM5100_OUT1W_PGA_VOW_WIDTH                   7  /* OUT1W_PGA_VOW - [7:1] */

/*
 * W1042 (0x412) - DAC Vowume Wimit 1W
 */
#define WM5100_OUT1W_VOW_WIM_MASK               0x00FF  /* OUT1W_VOW_WIM - [7:0] */
#define WM5100_OUT1W_VOW_WIM_SHIFT                   0  /* OUT1W_VOW_WIM - [7:0] */
#define WM5100_OUT1W_VOW_WIM_WIDTH                   8  /* OUT1W_VOW_WIM - [7:0] */

/*
 * W1043 (0x413) - DAC Vowume Wimit 1W
 */
#define WM5100_OUT1W_VOW_WIM_MASK               0x00FF  /* OUT1W_VOW_WIM - [7:0] */
#define WM5100_OUT1W_VOW_WIM_SHIFT                   0  /* OUT1W_VOW_WIM - [7:0] */
#define WM5100_OUT1W_VOW_WIM_WIDTH                   8  /* OUT1W_VOW_WIM - [7:0] */

/*
 * W1044 (0x414) - Out Vowume 2W
 */
#define WM5100_OUT2_OSW                         0x2000  /* OUT2_OSW */
#define WM5100_OUT2_OSW_MASK                    0x2000  /* OUT2_OSW */
#define WM5100_OUT2_OSW_SHIFT                       13  /* OUT2_OSW */
#define WM5100_OUT2_OSW_WIDTH                        1  /* OUT2_OSW */
#define WM5100_OUT2_MONO                        0x1000  /* OUT2_MONO */
#define WM5100_OUT2_MONO_MASK                   0x1000  /* OUT2_MONO */
#define WM5100_OUT2_MONO_SHIFT                      12  /* OUT2_MONO */
#define WM5100_OUT2_MONO_WIDTH                       1  /* OUT2_MONO */
#define WM5100_OUT2W_ANC_SWC                    0x0800  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_MASK               0x0800  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_SHIFT                  11  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_WIDTH                   1  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_PGA_VOW_MASK               0x00FE  /* OUT2W_PGA_VOW - [7:1] */
#define WM5100_OUT2W_PGA_VOW_SHIFT                   1  /* OUT2W_PGA_VOW - [7:1] */
#define WM5100_OUT2W_PGA_VOW_WIDTH                   7  /* OUT2W_PGA_VOW - [7:1] */

/*
 * W1045 (0x415) - Out Vowume 2W
 */
#define WM5100_OUT2W_ANC_SWC                    0x0800  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_MASK               0x0800  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_SHIFT                  11  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_ANC_SWC_WIDTH                   1  /* OUT2W_ANC_SWC */
#define WM5100_OUT2W_PGA_VOW_MASK               0x00FE  /* OUT2W_PGA_VOW - [7:1] */
#define WM5100_OUT2W_PGA_VOW_SHIFT                   1  /* OUT2W_PGA_VOW - [7:1] */
#define WM5100_OUT2W_PGA_VOW_WIDTH                   7  /* OUT2W_PGA_VOW - [7:1] */

/*
 * W1046 (0x416) - DAC Vowume Wimit 2W
 */
#define WM5100_OUT2W_VOW_WIM_MASK               0x00FF  /* OUT2W_VOW_WIM - [7:0] */
#define WM5100_OUT2W_VOW_WIM_SHIFT                   0  /* OUT2W_VOW_WIM - [7:0] */
#define WM5100_OUT2W_VOW_WIM_WIDTH                   8  /* OUT2W_VOW_WIM - [7:0] */

/*
 * W1047 (0x417) - DAC Vowume Wimit 2W
 */
#define WM5100_OUT2W_VOW_WIM_MASK               0x00FF  /* OUT2W_VOW_WIM - [7:0] */
#define WM5100_OUT2W_VOW_WIM_SHIFT                   0  /* OUT2W_VOW_WIM - [7:0] */
#define WM5100_OUT2W_VOW_WIM_WIDTH                   8  /* OUT2W_VOW_WIM - [7:0] */

/*
 * W1048 (0x418) - Out Vowume 3W
 */
#define WM5100_OUT3_OSW                         0x2000  /* OUT3_OSW */
#define WM5100_OUT3_OSW_MASK                    0x2000  /* OUT3_OSW */
#define WM5100_OUT3_OSW_SHIFT                       13  /* OUT3_OSW */
#define WM5100_OUT3_OSW_WIDTH                        1  /* OUT3_OSW */
#define WM5100_OUT3_MONO                        0x1000  /* OUT3_MONO */
#define WM5100_OUT3_MONO_MASK                   0x1000  /* OUT3_MONO */
#define WM5100_OUT3_MONO_SHIFT                      12  /* OUT3_MONO */
#define WM5100_OUT3_MONO_WIDTH                       1  /* OUT3_MONO */
#define WM5100_OUT3W_ANC_SWC                    0x0800  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_MASK               0x0800  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_SHIFT                  11  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_WIDTH                   1  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_PGA_VOW_MASK               0x00FE  /* OUT3W_PGA_VOW - [7:1] */
#define WM5100_OUT3W_PGA_VOW_SHIFT                   1  /* OUT3W_PGA_VOW - [7:1] */
#define WM5100_OUT3W_PGA_VOW_WIDTH                   7  /* OUT3W_PGA_VOW - [7:1] */

/*
 * W1049 (0x419) - Out Vowume 3W
 */
#define WM5100_OUT3W_ANC_SWC                    0x0800  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_MASK               0x0800  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_SHIFT                  11  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_ANC_SWC_WIDTH                   1  /* OUT3W_ANC_SWC */
#define WM5100_OUT3W_PGA_VOW_MASK               0x00FE  /* OUT3W_PGA_VOW - [7:1] */
#define WM5100_OUT3W_PGA_VOW_SHIFT                   1  /* OUT3W_PGA_VOW - [7:1] */
#define WM5100_OUT3W_PGA_VOW_WIDTH                   7  /* OUT3W_PGA_VOW - [7:1] */

/*
 * W1050 (0x41A) - DAC Vowume Wimit 3W
 */
#define WM5100_OUT3W_VOW_WIM_MASK               0x00FF  /* OUT3W_VOW_WIM - [7:0] */
#define WM5100_OUT3W_VOW_WIM_SHIFT                   0  /* OUT3W_VOW_WIM - [7:0] */
#define WM5100_OUT3W_VOW_WIM_WIDTH                   8  /* OUT3W_VOW_WIM - [7:0] */

/*
 * W1051 (0x41B) - DAC Vowume Wimit 3W
 */
#define WM5100_OUT3W_VOW_WIM_MASK               0x00FF  /* OUT3W_VOW_WIM - [7:0] */
#define WM5100_OUT3W_VOW_WIM_SHIFT                   0  /* OUT3W_VOW_WIM - [7:0] */
#define WM5100_OUT3W_VOW_WIM_WIDTH                   8  /* OUT3W_VOW_WIM - [7:0] */

/*
 * W1052 (0x41C) - Out Vowume 4W
 */
#define WM5100_OUT4_OSW                         0x2000  /* OUT4_OSW */
#define WM5100_OUT4_OSW_MASK                    0x2000  /* OUT4_OSW */
#define WM5100_OUT4_OSW_SHIFT                       13  /* OUT4_OSW */
#define WM5100_OUT4_OSW_WIDTH                        1  /* OUT4_OSW */
#define WM5100_OUT4W_ANC_SWC                    0x0800  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_MASK               0x0800  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_SHIFT                  11  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_WIDTH                   1  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_VOW_WIM_MASK               0x00FF  /* OUT4W_VOW_WIM - [7:0] */
#define WM5100_OUT4W_VOW_WIM_SHIFT                   0  /* OUT4W_VOW_WIM - [7:0] */
#define WM5100_OUT4W_VOW_WIM_WIDTH                   8  /* OUT4W_VOW_WIM - [7:0] */

/*
 * W1053 (0x41D) - Out Vowume 4W
 */
#define WM5100_OUT4W_ANC_SWC                    0x0800  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_MASK               0x0800  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_SHIFT                  11  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_ANC_SWC_WIDTH                   1  /* OUT4W_ANC_SWC */
#define WM5100_OUT4W_VOW_WIM_MASK               0x00FF  /* OUT4W_VOW_WIM - [7:0] */
#define WM5100_OUT4W_VOW_WIM_SHIFT                   0  /* OUT4W_VOW_WIM - [7:0] */
#define WM5100_OUT4W_VOW_WIM_WIDTH                   8  /* OUT4W_VOW_WIM - [7:0] */

/*
 * W1054 (0x41E) - DAC Vowume Wimit 5W
 */
#define WM5100_OUT5_OSW                         0x2000  /* OUT5_OSW */
#define WM5100_OUT5_OSW_MASK                    0x2000  /* OUT5_OSW */
#define WM5100_OUT5_OSW_SHIFT                       13  /* OUT5_OSW */
#define WM5100_OUT5_OSW_WIDTH                        1  /* OUT5_OSW */
#define WM5100_OUT5W_ANC_SWC                    0x0800  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_MASK               0x0800  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_SHIFT                  11  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_WIDTH                   1  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_VOW_WIM_MASK               0x00FF  /* OUT5W_VOW_WIM - [7:0] */
#define WM5100_OUT5W_VOW_WIM_SHIFT                   0  /* OUT5W_VOW_WIM - [7:0] */
#define WM5100_OUT5W_VOW_WIM_WIDTH                   8  /* OUT5W_VOW_WIM - [7:0] */

/*
 * W1055 (0x41F) - DAC Vowume Wimit 5W
 */
#define WM5100_OUT5W_ANC_SWC                    0x0800  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_MASK               0x0800  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_SHIFT                  11  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_ANC_SWC_WIDTH                   1  /* OUT5W_ANC_SWC */
#define WM5100_OUT5W_VOW_WIM_MASK               0x00FF  /* OUT5W_VOW_WIM - [7:0] */
#define WM5100_OUT5W_VOW_WIM_SHIFT                   0  /* OUT5W_VOW_WIM - [7:0] */
#define WM5100_OUT5W_VOW_WIM_WIDTH                   8  /* OUT5W_VOW_WIM - [7:0] */

/*
 * W1056 (0x420) - DAC Vowume Wimit 6W
 */
#define WM5100_OUT6_OSW                         0x2000  /* OUT6_OSW */
#define WM5100_OUT6_OSW_MASK                    0x2000  /* OUT6_OSW */
#define WM5100_OUT6_OSW_SHIFT                       13  /* OUT6_OSW */
#define WM5100_OUT6_OSW_WIDTH                        1  /* OUT6_OSW */
#define WM5100_OUT6W_ANC_SWC                    0x0800  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_MASK               0x0800  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_SHIFT                  11  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_WIDTH                   1  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_VOW_WIM_MASK               0x00FF  /* OUT6W_VOW_WIM - [7:0] */
#define WM5100_OUT6W_VOW_WIM_SHIFT                   0  /* OUT6W_VOW_WIM - [7:0] */
#define WM5100_OUT6W_VOW_WIM_WIDTH                   8  /* OUT6W_VOW_WIM - [7:0] */

/*
 * W1057 (0x421) - DAC Vowume Wimit 6W
 */
#define WM5100_OUT6W_ANC_SWC                    0x0800  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_MASK               0x0800  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_SHIFT                  11  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_ANC_SWC_WIDTH                   1  /* OUT6W_ANC_SWC */
#define WM5100_OUT6W_VOW_WIM_MASK               0x00FF  /* OUT6W_VOW_WIM - [7:0] */
#define WM5100_OUT6W_VOW_WIM_SHIFT                   0  /* OUT6W_VOW_WIM - [7:0] */
#define WM5100_OUT6W_VOW_WIM_WIDTH                   8  /* OUT6W_VOW_WIM - [7:0] */

/*
 * W1088 (0x440) - DAC AEC Contwow 1
 */
#define WM5100_AEC_WOOPBACK_SWC_MASK            0x003C  /* AEC_WOOPBACK_SWC - [5:2] */
#define WM5100_AEC_WOOPBACK_SWC_SHIFT                2  /* AEC_WOOPBACK_SWC - [5:2] */
#define WM5100_AEC_WOOPBACK_SWC_WIDTH                4  /* AEC_WOOPBACK_SWC - [5:2] */
#define WM5100_AEC_ENA_STS                      0x0002  /* AEC_ENA_STS */
#define WM5100_AEC_ENA_STS_MASK                 0x0002  /* AEC_ENA_STS */
#define WM5100_AEC_ENA_STS_SHIFT                     1  /* AEC_ENA_STS */
#define WM5100_AEC_ENA_STS_WIDTH                     1  /* AEC_ENA_STS */
#define WM5100_AEC_WOOPBACK_ENA                 0x0001  /* AEC_WOOPBACK_ENA */
#define WM5100_AEC_WOOPBACK_ENA_MASK            0x0001  /* AEC_WOOPBACK_ENA */
#define WM5100_AEC_WOOPBACK_ENA_SHIFT                0  /* AEC_WOOPBACK_ENA */
#define WM5100_AEC_WOOPBACK_ENA_WIDTH                1  /* AEC_WOOPBACK_ENA */

/*
 * W1089 (0x441) - Output Vowume Wamp
 */
#define WM5100_OUT_VD_WAMP_MASK                 0x0070  /* OUT_VD_WAMP - [6:4] */
#define WM5100_OUT_VD_WAMP_SHIFT                     4  /* OUT_VD_WAMP - [6:4] */
#define WM5100_OUT_VD_WAMP_WIDTH                     3  /* OUT_VD_WAMP - [6:4] */
#define WM5100_OUT_VI_WAMP_MASK                 0x0007  /* OUT_VI_WAMP - [2:0] */
#define WM5100_OUT_VI_WAMP_SHIFT                     0  /* OUT_VI_WAMP - [2:0] */
#define WM5100_OUT_VI_WAMP_WIDTH                     3  /* OUT_VI_WAMP - [2:0] */

/*
 * W1152 (0x480) - DAC Digitaw Vowume 1W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT1W_MUTE                       0x0100  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_MASK                  0x0100  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_SHIFT                      8  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_WIDTH                      1  /* OUT1W_MUTE */
#define WM5100_OUT1W_VOW_MASK                   0x00FF  /* OUT1W_VOW - [7:0] */
#define WM5100_OUT1W_VOW_SHIFT                       0  /* OUT1W_VOW - [7:0] */
#define WM5100_OUT1W_VOW_WIDTH                       8  /* OUT1W_VOW - [7:0] */

/*
 * W1153 (0x481) - DAC Digitaw Vowume 1W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT1W_MUTE                       0x0100  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_MASK                  0x0100  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_SHIFT                      8  /* OUT1W_MUTE */
#define WM5100_OUT1W_MUTE_WIDTH                      1  /* OUT1W_MUTE */
#define WM5100_OUT1W_VOW_MASK                   0x00FF  /* OUT1W_VOW - [7:0] */
#define WM5100_OUT1W_VOW_SHIFT                       0  /* OUT1W_VOW - [7:0] */
#define WM5100_OUT1W_VOW_WIDTH                       8  /* OUT1W_VOW - [7:0] */

/*
 * W1154 (0x482) - DAC Digitaw Vowume 2W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT2W_MUTE                       0x0100  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_MASK                  0x0100  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_SHIFT                      8  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_WIDTH                      1  /* OUT2W_MUTE */
#define WM5100_OUT2W_VOW_MASK                   0x00FF  /* OUT2W_VOW - [7:0] */
#define WM5100_OUT2W_VOW_SHIFT                       0  /* OUT2W_VOW - [7:0] */
#define WM5100_OUT2W_VOW_WIDTH                       8  /* OUT2W_VOW - [7:0] */

/*
 * W1155 (0x483) - DAC Digitaw Vowume 2W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT2W_MUTE                       0x0100  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_MASK                  0x0100  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_SHIFT                      8  /* OUT2W_MUTE */
#define WM5100_OUT2W_MUTE_WIDTH                      1  /* OUT2W_MUTE */
#define WM5100_OUT2W_VOW_MASK                   0x00FF  /* OUT2W_VOW - [7:0] */
#define WM5100_OUT2W_VOW_SHIFT                       0  /* OUT2W_VOW - [7:0] */
#define WM5100_OUT2W_VOW_WIDTH                       8  /* OUT2W_VOW - [7:0] */

/*
 * W1156 (0x484) - DAC Digitaw Vowume 3W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT3W_MUTE                       0x0100  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_MASK                  0x0100  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_SHIFT                      8  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_WIDTH                      1  /* OUT3W_MUTE */
#define WM5100_OUT3W_VOW_MASK                   0x00FF  /* OUT3W_VOW - [7:0] */
#define WM5100_OUT3W_VOW_SHIFT                       0  /* OUT3W_VOW - [7:0] */
#define WM5100_OUT3W_VOW_WIDTH                       8  /* OUT3W_VOW - [7:0] */

/*
 * W1157 (0x485) - DAC Digitaw Vowume 3W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT3W_MUTE                       0x0100  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_MASK                  0x0100  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_SHIFT                      8  /* OUT3W_MUTE */
#define WM5100_OUT3W_MUTE_WIDTH                      1  /* OUT3W_MUTE */
#define WM5100_OUT3W_VOW_MASK                   0x00FF  /* OUT3W_VOW - [7:0] */
#define WM5100_OUT3W_VOW_SHIFT                       0  /* OUT3W_VOW - [7:0] */
#define WM5100_OUT3W_VOW_WIDTH                       8  /* OUT3W_VOW - [7:0] */

/*
 * W1158 (0x486) - DAC Digitaw Vowume 4W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT4W_MUTE                       0x0100  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_MASK                  0x0100  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_SHIFT                      8  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_WIDTH                      1  /* OUT4W_MUTE */
#define WM5100_OUT4W_VOW_MASK                   0x00FF  /* OUT4W_VOW - [7:0] */
#define WM5100_OUT4W_VOW_SHIFT                       0  /* OUT4W_VOW - [7:0] */
#define WM5100_OUT4W_VOW_WIDTH                       8  /* OUT4W_VOW - [7:0] */

/*
 * W1159 (0x487) - DAC Digitaw Vowume 4W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT4W_MUTE                       0x0100  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_MASK                  0x0100  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_SHIFT                      8  /* OUT4W_MUTE */
#define WM5100_OUT4W_MUTE_WIDTH                      1  /* OUT4W_MUTE */
#define WM5100_OUT4W_VOW_MASK                   0x00FF  /* OUT4W_VOW - [7:0] */
#define WM5100_OUT4W_VOW_SHIFT                       0  /* OUT4W_VOW - [7:0] */
#define WM5100_OUT4W_VOW_WIDTH                       8  /* OUT4W_VOW - [7:0] */

/*
 * W1160 (0x488) - DAC Digitaw Vowume 5W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT5W_MUTE                       0x0100  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_MASK                  0x0100  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_SHIFT                      8  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_WIDTH                      1  /* OUT5W_MUTE */
#define WM5100_OUT5W_VOW_MASK                   0x00FF  /* OUT5W_VOW - [7:0] */
#define WM5100_OUT5W_VOW_SHIFT                       0  /* OUT5W_VOW - [7:0] */
#define WM5100_OUT5W_VOW_WIDTH                       8  /* OUT5W_VOW - [7:0] */

/*
 * W1161 (0x489) - DAC Digitaw Vowume 5W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT5W_MUTE                       0x0100  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_MASK                  0x0100  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_SHIFT                      8  /* OUT5W_MUTE */
#define WM5100_OUT5W_MUTE_WIDTH                      1  /* OUT5W_MUTE */
#define WM5100_OUT5W_VOW_MASK                   0x00FF  /* OUT5W_VOW - [7:0] */
#define WM5100_OUT5W_VOW_SHIFT                       0  /* OUT5W_VOW - [7:0] */
#define WM5100_OUT5W_VOW_WIDTH                       8  /* OUT5W_VOW - [7:0] */

/*
 * W1162 (0x48A) - DAC Digitaw Vowume 6W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT6W_MUTE                       0x0100  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_MASK                  0x0100  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_SHIFT                      8  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_WIDTH                      1  /* OUT6W_MUTE */
#define WM5100_OUT6W_VOW_MASK                   0x00FF  /* OUT6W_VOW - [7:0] */
#define WM5100_OUT6W_VOW_SHIFT                       0  /* OUT6W_VOW - [7:0] */
#define WM5100_OUT6W_VOW_WIDTH                       8  /* OUT6W_VOW - [7:0] */

/*
 * W1163 (0x48B) - DAC Digitaw Vowume 6W
 */
#define WM5100_OUT_VU                           0x0200  /* OUT_VU */
#define WM5100_OUT_VU_MASK                      0x0200  /* OUT_VU */
#define WM5100_OUT_VU_SHIFT                          9  /* OUT_VU */
#define WM5100_OUT_VU_WIDTH                          1  /* OUT_VU */
#define WM5100_OUT6W_MUTE                       0x0100  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_MASK                  0x0100  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_SHIFT                      8  /* OUT6W_MUTE */
#define WM5100_OUT6W_MUTE_WIDTH                      1  /* OUT6W_MUTE */
#define WM5100_OUT6W_VOW_MASK                   0x00FF  /* OUT6W_VOW - [7:0] */
#define WM5100_OUT6W_VOW_SHIFT                       0  /* OUT6W_VOW - [7:0] */
#define WM5100_OUT6W_VOW_WIDTH                       8  /* OUT6W_VOW - [7:0] */

/*
 * W1216 (0x4C0) - PDM SPK1 CTWW 1
 */
#define WM5100_SPK1W_MUTE                       0x2000  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_MASK                  0x2000  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_SHIFT                     13  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_WIDTH                      1  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE                       0x1000  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_MASK                  0x1000  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_SHIFT                     12  /* SPK1W_MUTE */
#define WM5100_SPK1W_MUTE_WIDTH                      1  /* SPK1W_MUTE */
#define WM5100_SPK1_MUTE_ENDIAN                 0x0100  /* SPK1_MUTE_ENDIAN */
#define WM5100_SPK1_MUTE_ENDIAN_MASK            0x0100  /* SPK1_MUTE_ENDIAN */
#define WM5100_SPK1_MUTE_ENDIAN_SHIFT                8  /* SPK1_MUTE_ENDIAN */
#define WM5100_SPK1_MUTE_ENDIAN_WIDTH                1  /* SPK1_MUTE_ENDIAN */
#define WM5100_SPK1_MUTE_SEQ1_MASK              0x00FF  /* SPK1_MUTE_SEQ1 - [7:0] */
#define WM5100_SPK1_MUTE_SEQ1_SHIFT                  0  /* SPK1_MUTE_SEQ1 - [7:0] */
#define WM5100_SPK1_MUTE_SEQ1_WIDTH                  8  /* SPK1_MUTE_SEQ1 - [7:0] */

/*
 * W1217 (0x4C1) - PDM SPK1 CTWW 2
 */
#define WM5100_SPK1_FMT                         0x0001  /* SPK1_FMT */
#define WM5100_SPK1_FMT_MASK                    0x0001  /* SPK1_FMT */
#define WM5100_SPK1_FMT_SHIFT                        0  /* SPK1_FMT */
#define WM5100_SPK1_FMT_WIDTH                        1  /* SPK1_FMT */

/*
 * W1218 (0x4C2) - PDM SPK2 CTWW 1
 */
#define WM5100_SPK2W_MUTE                       0x2000  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_MASK                  0x2000  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_SHIFT                     13  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_WIDTH                      1  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE                       0x1000  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_MASK                  0x1000  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_SHIFT                     12  /* SPK2W_MUTE */
#define WM5100_SPK2W_MUTE_WIDTH                      1  /* SPK2W_MUTE */
#define WM5100_SPK2_MUTE_ENDIAN                 0x0100  /* SPK2_MUTE_ENDIAN */
#define WM5100_SPK2_MUTE_ENDIAN_MASK            0x0100  /* SPK2_MUTE_ENDIAN */
#define WM5100_SPK2_MUTE_ENDIAN_SHIFT                8  /* SPK2_MUTE_ENDIAN */
#define WM5100_SPK2_MUTE_ENDIAN_WIDTH                1  /* SPK2_MUTE_ENDIAN */
#define WM5100_SPK2_MUTE_SEQ1_MASK              0x00FF  /* SPK2_MUTE_SEQ1 - [7:0] */
#define WM5100_SPK2_MUTE_SEQ1_SHIFT                  0  /* SPK2_MUTE_SEQ1 - [7:0] */
#define WM5100_SPK2_MUTE_SEQ1_WIDTH                  8  /* SPK2_MUTE_SEQ1 - [7:0] */

/*
 * W1219 (0x4C3) - PDM SPK2 CTWW 2
 */
#define WM5100_SPK2_FMT                         0x0001  /* SPK2_FMT */
#define WM5100_SPK2_FMT_MASK                    0x0001  /* SPK2_FMT */
#define WM5100_SPK2_FMT_SHIFT                        0  /* SPK2_FMT */
#define WM5100_SPK2_FMT_WIDTH                        1  /* SPK2_FMT */

/*
 * W1280 (0x500) - Audio IF 1_1
 */
#define WM5100_AIF1_BCWK_INV                    0x0080  /* AIF1_BCWK_INV */
#define WM5100_AIF1_BCWK_INV_MASK               0x0080  /* AIF1_BCWK_INV */
#define WM5100_AIF1_BCWK_INV_SHIFT                   7  /* AIF1_BCWK_INV */
#define WM5100_AIF1_BCWK_INV_WIDTH                   1  /* AIF1_BCWK_INV */
#define WM5100_AIF1_BCWK_FWC                    0x0040  /* AIF1_BCWK_FWC */
#define WM5100_AIF1_BCWK_FWC_MASK               0x0040  /* AIF1_BCWK_FWC */
#define WM5100_AIF1_BCWK_FWC_SHIFT                   6  /* AIF1_BCWK_FWC */
#define WM5100_AIF1_BCWK_FWC_WIDTH                   1  /* AIF1_BCWK_FWC */
#define WM5100_AIF1_BCWK_MSTW                   0x0020  /* AIF1_BCWK_MSTW */
#define WM5100_AIF1_BCWK_MSTW_MASK              0x0020  /* AIF1_BCWK_MSTW */
#define WM5100_AIF1_BCWK_MSTW_SHIFT                  5  /* AIF1_BCWK_MSTW */
#define WM5100_AIF1_BCWK_MSTW_WIDTH                  1  /* AIF1_BCWK_MSTW */
#define WM5100_AIF1_BCWK_FWEQ_MASK              0x001F  /* AIF1_BCWK_FWEQ - [4:0] */
#define WM5100_AIF1_BCWK_FWEQ_SHIFT                  0  /* AIF1_BCWK_FWEQ - [4:0] */
#define WM5100_AIF1_BCWK_FWEQ_WIDTH                  5  /* AIF1_BCWK_FWEQ - [4:0] */

/*
 * W1281 (0x501) - Audio IF 1_2
 */
#define WM5100_AIF1TX_DAT_TWI                   0x0020  /* AIF1TX_DAT_TWI */
#define WM5100_AIF1TX_DAT_TWI_MASK              0x0020  /* AIF1TX_DAT_TWI */
#define WM5100_AIF1TX_DAT_TWI_SHIFT                  5  /* AIF1TX_DAT_TWI */
#define WM5100_AIF1TX_DAT_TWI_WIDTH                  1  /* AIF1TX_DAT_TWI */
#define WM5100_AIF1TX_WWCWK_SWC                 0x0008  /* AIF1TX_WWCWK_SWC */
#define WM5100_AIF1TX_WWCWK_SWC_MASK            0x0008  /* AIF1TX_WWCWK_SWC */
#define WM5100_AIF1TX_WWCWK_SWC_SHIFT                3  /* AIF1TX_WWCWK_SWC */
#define WM5100_AIF1TX_WWCWK_SWC_WIDTH                1  /* AIF1TX_WWCWK_SWC */
#define WM5100_AIF1TX_WWCWK_INV                 0x0004  /* AIF1TX_WWCWK_INV */
#define WM5100_AIF1TX_WWCWK_INV_MASK            0x0004  /* AIF1TX_WWCWK_INV */
#define WM5100_AIF1TX_WWCWK_INV_SHIFT                2  /* AIF1TX_WWCWK_INV */
#define WM5100_AIF1TX_WWCWK_INV_WIDTH                1  /* AIF1TX_WWCWK_INV */
#define WM5100_AIF1TX_WWCWK_FWC                 0x0002  /* AIF1TX_WWCWK_FWC */
#define WM5100_AIF1TX_WWCWK_FWC_MASK            0x0002  /* AIF1TX_WWCWK_FWC */
#define WM5100_AIF1TX_WWCWK_FWC_SHIFT                1  /* AIF1TX_WWCWK_FWC */
#define WM5100_AIF1TX_WWCWK_FWC_WIDTH                1  /* AIF1TX_WWCWK_FWC */
#define WM5100_AIF1TX_WWCWK_MSTW                0x0001  /* AIF1TX_WWCWK_MSTW */
#define WM5100_AIF1TX_WWCWK_MSTW_MASK           0x0001  /* AIF1TX_WWCWK_MSTW */
#define WM5100_AIF1TX_WWCWK_MSTW_SHIFT               0  /* AIF1TX_WWCWK_MSTW */
#define WM5100_AIF1TX_WWCWK_MSTW_WIDTH               1  /* AIF1TX_WWCWK_MSTW */

/*
 * W1282 (0x502) - Audio IF 1_3
 */
#define WM5100_AIF1WX_WWCWK_INV                 0x0004  /* AIF1WX_WWCWK_INV */
#define WM5100_AIF1WX_WWCWK_INV_MASK            0x0004  /* AIF1WX_WWCWK_INV */
#define WM5100_AIF1WX_WWCWK_INV_SHIFT                2  /* AIF1WX_WWCWK_INV */
#define WM5100_AIF1WX_WWCWK_INV_WIDTH                1  /* AIF1WX_WWCWK_INV */
#define WM5100_AIF1WX_WWCWK_FWC                 0x0002  /* AIF1WX_WWCWK_FWC */
#define WM5100_AIF1WX_WWCWK_FWC_MASK            0x0002  /* AIF1WX_WWCWK_FWC */
#define WM5100_AIF1WX_WWCWK_FWC_SHIFT                1  /* AIF1WX_WWCWK_FWC */
#define WM5100_AIF1WX_WWCWK_FWC_WIDTH                1  /* AIF1WX_WWCWK_FWC */
#define WM5100_AIF1WX_WWCWK_MSTW                0x0001  /* AIF1WX_WWCWK_MSTW */
#define WM5100_AIF1WX_WWCWK_MSTW_MASK           0x0001  /* AIF1WX_WWCWK_MSTW */
#define WM5100_AIF1WX_WWCWK_MSTW_SHIFT               0  /* AIF1WX_WWCWK_MSTW */
#define WM5100_AIF1WX_WWCWK_MSTW_WIDTH               1  /* AIF1WX_WWCWK_MSTW */

/*
 * W1283 (0x503) - Audio IF 1_4
 */
#define WM5100_AIF1_TWI                         0x0040  /* AIF1_TWI */
#define WM5100_AIF1_TWI_MASK                    0x0040  /* AIF1_TWI */
#define WM5100_AIF1_TWI_SHIFT                        6  /* AIF1_TWI */
#define WM5100_AIF1_TWI_WIDTH                        1  /* AIF1_TWI */
#define WM5100_AIF1_WATE_MASK                   0x0003  /* AIF1_WATE - [1:0] */
#define WM5100_AIF1_WATE_SHIFT                       0  /* AIF1_WATE - [1:0] */
#define WM5100_AIF1_WATE_WIDTH                       2  /* AIF1_WATE - [1:0] */

/*
 * W1284 (0x504) - Audio IF 1_5
 */
#define WM5100_AIF1_FMT_MASK                    0x0007  /* AIF1_FMT - [2:0] */
#define WM5100_AIF1_FMT_SHIFT                        0  /* AIF1_FMT - [2:0] */
#define WM5100_AIF1_FMT_WIDTH                        3  /* AIF1_FMT - [2:0] */

/*
 * W1285 (0x505) - Audio IF 1_6
 */
#define WM5100_AIF1TX_BCPF_MASK                 0x1FFF  /* AIF1TX_BCPF - [12:0] */
#define WM5100_AIF1TX_BCPF_SHIFT                     0  /* AIF1TX_BCPF - [12:0] */
#define WM5100_AIF1TX_BCPF_WIDTH                    13  /* AIF1TX_BCPF - [12:0] */

/*
 * W1286 (0x506) - Audio IF 1_7
 */
#define WM5100_AIF1WX_BCPF_MASK                 0x1FFF  /* AIF1WX_BCPF - [12:0] */
#define WM5100_AIF1WX_BCPF_SHIFT                     0  /* AIF1WX_BCPF - [12:0] */
#define WM5100_AIF1WX_BCPF_WIDTH                    13  /* AIF1WX_BCPF - [12:0] */

/*
 * W1287 (0x507) - Audio IF 1_8
 */
#define WM5100_AIF1TX_WW_MASK                   0x3F00  /* AIF1TX_WW - [13:8] */
#define WM5100_AIF1TX_WW_SHIFT                       8  /* AIF1TX_WW - [13:8] */
#define WM5100_AIF1TX_WW_WIDTH                       6  /* AIF1TX_WW - [13:8] */
#define WM5100_AIF1TX_SWOT_WEN_MASK             0x00FF  /* AIF1TX_SWOT_WEN - [7:0] */
#define WM5100_AIF1TX_SWOT_WEN_SHIFT                 0  /* AIF1TX_SWOT_WEN - [7:0] */
#define WM5100_AIF1TX_SWOT_WEN_WIDTH                 8  /* AIF1TX_SWOT_WEN - [7:0] */

/*
 * W1288 (0x508) - Audio IF 1_9
 */
#define WM5100_AIF1WX_WW_MASK                   0x3F00  /* AIF1WX_WW - [13:8] */
#define WM5100_AIF1WX_WW_SHIFT                       8  /* AIF1WX_WW - [13:8] */
#define WM5100_AIF1WX_WW_WIDTH                       6  /* AIF1WX_WW - [13:8] */
#define WM5100_AIF1WX_SWOT_WEN_MASK             0x00FF  /* AIF1WX_SWOT_WEN - [7:0] */
#define WM5100_AIF1WX_SWOT_WEN_SHIFT                 0  /* AIF1WX_SWOT_WEN - [7:0] */
#define WM5100_AIF1WX_SWOT_WEN_WIDTH                 8  /* AIF1WX_SWOT_WEN - [7:0] */

/*
 * W1289 (0x509) - Audio IF 1_10
 */
#define WM5100_AIF1TX1_SWOT_MASK                0x003F  /* AIF1TX1_SWOT - [5:0] */
#define WM5100_AIF1TX1_SWOT_SHIFT                    0  /* AIF1TX1_SWOT - [5:0] */
#define WM5100_AIF1TX1_SWOT_WIDTH                    6  /* AIF1TX1_SWOT - [5:0] */

/*
 * W1290 (0x50A) - Audio IF 1_11
 */
#define WM5100_AIF1TX2_SWOT_MASK                0x003F  /* AIF1TX2_SWOT - [5:0] */
#define WM5100_AIF1TX2_SWOT_SHIFT                    0  /* AIF1TX2_SWOT - [5:0] */
#define WM5100_AIF1TX2_SWOT_WIDTH                    6  /* AIF1TX2_SWOT - [5:0] */

/*
 * W1291 (0x50B) - Audio IF 1_12
 */
#define WM5100_AIF1TX3_SWOT_MASK                0x003F  /* AIF1TX3_SWOT - [5:0] */
#define WM5100_AIF1TX3_SWOT_SHIFT                    0  /* AIF1TX3_SWOT - [5:0] */
#define WM5100_AIF1TX3_SWOT_WIDTH                    6  /* AIF1TX3_SWOT - [5:0] */

/*
 * W1292 (0x50C) - Audio IF 1_13
 */
#define WM5100_AIF1TX4_SWOT_MASK                0x003F  /* AIF1TX4_SWOT - [5:0] */
#define WM5100_AIF1TX4_SWOT_SHIFT                    0  /* AIF1TX4_SWOT - [5:0] */
#define WM5100_AIF1TX4_SWOT_WIDTH                    6  /* AIF1TX4_SWOT - [5:0] */

/*
 * W1293 (0x50D) - Audio IF 1_14
 */
#define WM5100_AIF1TX5_SWOT_MASK                0x003F  /* AIF1TX5_SWOT - [5:0] */
#define WM5100_AIF1TX5_SWOT_SHIFT                    0  /* AIF1TX5_SWOT - [5:0] */
#define WM5100_AIF1TX5_SWOT_WIDTH                    6  /* AIF1TX5_SWOT - [5:0] */

/*
 * W1294 (0x50E) - Audio IF 1_15
 */
#define WM5100_AIF1TX6_SWOT_MASK                0x003F  /* AIF1TX6_SWOT - [5:0] */
#define WM5100_AIF1TX6_SWOT_SHIFT                    0  /* AIF1TX6_SWOT - [5:0] */
#define WM5100_AIF1TX6_SWOT_WIDTH                    6  /* AIF1TX6_SWOT - [5:0] */

/*
 * W1295 (0x50F) - Audio IF 1_16
 */
#define WM5100_AIF1TX7_SWOT_MASK                0x003F  /* AIF1TX7_SWOT - [5:0] */
#define WM5100_AIF1TX7_SWOT_SHIFT                    0  /* AIF1TX7_SWOT - [5:0] */
#define WM5100_AIF1TX7_SWOT_WIDTH                    6  /* AIF1TX7_SWOT - [5:0] */

/*
 * W1296 (0x510) - Audio IF 1_17
 */
#define WM5100_AIF1TX8_SWOT_MASK                0x003F  /* AIF1TX8_SWOT - [5:0] */
#define WM5100_AIF1TX8_SWOT_SHIFT                    0  /* AIF1TX8_SWOT - [5:0] */
#define WM5100_AIF1TX8_SWOT_WIDTH                    6  /* AIF1TX8_SWOT - [5:0] */

/*
 * W1297 (0x511) - Audio IF 1_18
 */
#define WM5100_AIF1WX1_SWOT_MASK                0x003F  /* AIF1WX1_SWOT - [5:0] */
#define WM5100_AIF1WX1_SWOT_SHIFT                    0  /* AIF1WX1_SWOT - [5:0] */
#define WM5100_AIF1WX1_SWOT_WIDTH                    6  /* AIF1WX1_SWOT - [5:0] */

/*
 * W1298 (0x512) - Audio IF 1_19
 */
#define WM5100_AIF1WX2_SWOT_MASK                0x003F  /* AIF1WX2_SWOT - [5:0] */
#define WM5100_AIF1WX2_SWOT_SHIFT                    0  /* AIF1WX2_SWOT - [5:0] */
#define WM5100_AIF1WX2_SWOT_WIDTH                    6  /* AIF1WX2_SWOT - [5:0] */

/*
 * W1299 (0x513) - Audio IF 1_20
 */
#define WM5100_AIF1WX3_SWOT_MASK                0x003F  /* AIF1WX3_SWOT - [5:0] */
#define WM5100_AIF1WX3_SWOT_SHIFT                    0  /* AIF1WX3_SWOT - [5:0] */
#define WM5100_AIF1WX3_SWOT_WIDTH                    6  /* AIF1WX3_SWOT - [5:0] */

/*
 * W1300 (0x514) - Audio IF 1_21
 */
#define WM5100_AIF1WX4_SWOT_MASK                0x003F  /* AIF1WX4_SWOT - [5:0] */
#define WM5100_AIF1WX4_SWOT_SHIFT                    0  /* AIF1WX4_SWOT - [5:0] */
#define WM5100_AIF1WX4_SWOT_WIDTH                    6  /* AIF1WX4_SWOT - [5:0] */

/*
 * W1301 (0x515) - Audio IF 1_22
 */
#define WM5100_AIF1WX5_SWOT_MASK                0x003F  /* AIF1WX5_SWOT - [5:0] */
#define WM5100_AIF1WX5_SWOT_SHIFT                    0  /* AIF1WX5_SWOT - [5:0] */
#define WM5100_AIF1WX5_SWOT_WIDTH                    6  /* AIF1WX5_SWOT - [5:0] */

/*
 * W1302 (0x516) - Audio IF 1_23
 */
#define WM5100_AIF1WX6_SWOT_MASK                0x003F  /* AIF1WX6_SWOT - [5:0] */
#define WM5100_AIF1WX6_SWOT_SHIFT                    0  /* AIF1WX6_SWOT - [5:0] */
#define WM5100_AIF1WX6_SWOT_WIDTH                    6  /* AIF1WX6_SWOT - [5:0] */

/*
 * W1303 (0x517) - Audio IF 1_24
 */
#define WM5100_AIF1WX7_SWOT_MASK                0x003F  /* AIF1WX7_SWOT - [5:0] */
#define WM5100_AIF1WX7_SWOT_SHIFT                    0  /* AIF1WX7_SWOT - [5:0] */
#define WM5100_AIF1WX7_SWOT_WIDTH                    6  /* AIF1WX7_SWOT - [5:0] */

/*
 * W1304 (0x518) - Audio IF 1_25
 */
#define WM5100_AIF1WX8_SWOT_MASK                0x003F  /* AIF1WX8_SWOT - [5:0] */
#define WM5100_AIF1WX8_SWOT_SHIFT                    0  /* AIF1WX8_SWOT - [5:0] */
#define WM5100_AIF1WX8_SWOT_WIDTH                    6  /* AIF1WX8_SWOT - [5:0] */

/*
 * W1305 (0x519) - Audio IF 1_26
 */
#define WM5100_AIF1TX8_ENA                      0x0080  /* AIF1TX8_ENA */
#define WM5100_AIF1TX8_ENA_MASK                 0x0080  /* AIF1TX8_ENA */
#define WM5100_AIF1TX8_ENA_SHIFT                     7  /* AIF1TX8_ENA */
#define WM5100_AIF1TX8_ENA_WIDTH                     1  /* AIF1TX8_ENA */
#define WM5100_AIF1TX7_ENA                      0x0040  /* AIF1TX7_ENA */
#define WM5100_AIF1TX7_ENA_MASK                 0x0040  /* AIF1TX7_ENA */
#define WM5100_AIF1TX7_ENA_SHIFT                     6  /* AIF1TX7_ENA */
#define WM5100_AIF1TX7_ENA_WIDTH                     1  /* AIF1TX7_ENA */
#define WM5100_AIF1TX6_ENA                      0x0020  /* AIF1TX6_ENA */
#define WM5100_AIF1TX6_ENA_MASK                 0x0020  /* AIF1TX6_ENA */
#define WM5100_AIF1TX6_ENA_SHIFT                     5  /* AIF1TX6_ENA */
#define WM5100_AIF1TX6_ENA_WIDTH                     1  /* AIF1TX6_ENA */
#define WM5100_AIF1TX5_ENA                      0x0010  /* AIF1TX5_ENA */
#define WM5100_AIF1TX5_ENA_MASK                 0x0010  /* AIF1TX5_ENA */
#define WM5100_AIF1TX5_ENA_SHIFT                     4  /* AIF1TX5_ENA */
#define WM5100_AIF1TX5_ENA_WIDTH                     1  /* AIF1TX5_ENA */
#define WM5100_AIF1TX4_ENA                      0x0008  /* AIF1TX4_ENA */
#define WM5100_AIF1TX4_ENA_MASK                 0x0008  /* AIF1TX4_ENA */
#define WM5100_AIF1TX4_ENA_SHIFT                     3  /* AIF1TX4_ENA */
#define WM5100_AIF1TX4_ENA_WIDTH                     1  /* AIF1TX4_ENA */
#define WM5100_AIF1TX3_ENA                      0x0004  /* AIF1TX3_ENA */
#define WM5100_AIF1TX3_ENA_MASK                 0x0004  /* AIF1TX3_ENA */
#define WM5100_AIF1TX3_ENA_SHIFT                     2  /* AIF1TX3_ENA */
#define WM5100_AIF1TX3_ENA_WIDTH                     1  /* AIF1TX3_ENA */
#define WM5100_AIF1TX2_ENA                      0x0002  /* AIF1TX2_ENA */
#define WM5100_AIF1TX2_ENA_MASK                 0x0002  /* AIF1TX2_ENA */
#define WM5100_AIF1TX2_ENA_SHIFT                     1  /* AIF1TX2_ENA */
#define WM5100_AIF1TX2_ENA_WIDTH                     1  /* AIF1TX2_ENA */
#define WM5100_AIF1TX1_ENA                      0x0001  /* AIF1TX1_ENA */
#define WM5100_AIF1TX1_ENA_MASK                 0x0001  /* AIF1TX1_ENA */
#define WM5100_AIF1TX1_ENA_SHIFT                     0  /* AIF1TX1_ENA */
#define WM5100_AIF1TX1_ENA_WIDTH                     1  /* AIF1TX1_ENA */

/*
 * W1306 (0x51A) - Audio IF 1_27
 */
#define WM5100_AIF1WX8_ENA                      0x0080  /* AIF1WX8_ENA */
#define WM5100_AIF1WX8_ENA_MASK                 0x0080  /* AIF1WX8_ENA */
#define WM5100_AIF1WX8_ENA_SHIFT                     7  /* AIF1WX8_ENA */
#define WM5100_AIF1WX8_ENA_WIDTH                     1  /* AIF1WX8_ENA */
#define WM5100_AIF1WX7_ENA                      0x0040  /* AIF1WX7_ENA */
#define WM5100_AIF1WX7_ENA_MASK                 0x0040  /* AIF1WX7_ENA */
#define WM5100_AIF1WX7_ENA_SHIFT                     6  /* AIF1WX7_ENA */
#define WM5100_AIF1WX7_ENA_WIDTH                     1  /* AIF1WX7_ENA */
#define WM5100_AIF1WX6_ENA                      0x0020  /* AIF1WX6_ENA */
#define WM5100_AIF1WX6_ENA_MASK                 0x0020  /* AIF1WX6_ENA */
#define WM5100_AIF1WX6_ENA_SHIFT                     5  /* AIF1WX6_ENA */
#define WM5100_AIF1WX6_ENA_WIDTH                     1  /* AIF1WX6_ENA */
#define WM5100_AIF1WX5_ENA                      0x0010  /* AIF1WX5_ENA */
#define WM5100_AIF1WX5_ENA_MASK                 0x0010  /* AIF1WX5_ENA */
#define WM5100_AIF1WX5_ENA_SHIFT                     4  /* AIF1WX5_ENA */
#define WM5100_AIF1WX5_ENA_WIDTH                     1  /* AIF1WX5_ENA */
#define WM5100_AIF1WX4_ENA                      0x0008  /* AIF1WX4_ENA */
#define WM5100_AIF1WX4_ENA_MASK                 0x0008  /* AIF1WX4_ENA */
#define WM5100_AIF1WX4_ENA_SHIFT                     3  /* AIF1WX4_ENA */
#define WM5100_AIF1WX4_ENA_WIDTH                     1  /* AIF1WX4_ENA */
#define WM5100_AIF1WX3_ENA                      0x0004  /* AIF1WX3_ENA */
#define WM5100_AIF1WX3_ENA_MASK                 0x0004  /* AIF1WX3_ENA */
#define WM5100_AIF1WX3_ENA_SHIFT                     2  /* AIF1WX3_ENA */
#define WM5100_AIF1WX3_ENA_WIDTH                     1  /* AIF1WX3_ENA */
#define WM5100_AIF1WX2_ENA                      0x0002  /* AIF1WX2_ENA */
#define WM5100_AIF1WX2_ENA_MASK                 0x0002  /* AIF1WX2_ENA */
#define WM5100_AIF1WX2_ENA_SHIFT                     1  /* AIF1WX2_ENA */
#define WM5100_AIF1WX2_ENA_WIDTH                     1  /* AIF1WX2_ENA */
#define WM5100_AIF1WX1_ENA                      0x0001  /* AIF1WX1_ENA */
#define WM5100_AIF1WX1_ENA_MASK                 0x0001  /* AIF1WX1_ENA */
#define WM5100_AIF1WX1_ENA_SHIFT                     0  /* AIF1WX1_ENA */
#define WM5100_AIF1WX1_ENA_WIDTH                     1  /* AIF1WX1_ENA */

/*
 * W1344 (0x540) - Audio IF 2_1
 */
#define WM5100_AIF2_BCWK_INV                    0x0080  /* AIF2_BCWK_INV */
#define WM5100_AIF2_BCWK_INV_MASK               0x0080  /* AIF2_BCWK_INV */
#define WM5100_AIF2_BCWK_INV_SHIFT                   7  /* AIF2_BCWK_INV */
#define WM5100_AIF2_BCWK_INV_WIDTH                   1  /* AIF2_BCWK_INV */
#define WM5100_AIF2_BCWK_FWC                    0x0040  /* AIF2_BCWK_FWC */
#define WM5100_AIF2_BCWK_FWC_MASK               0x0040  /* AIF2_BCWK_FWC */
#define WM5100_AIF2_BCWK_FWC_SHIFT                   6  /* AIF2_BCWK_FWC */
#define WM5100_AIF2_BCWK_FWC_WIDTH                   1  /* AIF2_BCWK_FWC */
#define WM5100_AIF2_BCWK_MSTW                   0x0020  /* AIF2_BCWK_MSTW */
#define WM5100_AIF2_BCWK_MSTW_MASK              0x0020  /* AIF2_BCWK_MSTW */
#define WM5100_AIF2_BCWK_MSTW_SHIFT                  5  /* AIF2_BCWK_MSTW */
#define WM5100_AIF2_BCWK_MSTW_WIDTH                  1  /* AIF2_BCWK_MSTW */
#define WM5100_AIF2_BCWK_FWEQ_MASK              0x001F  /* AIF2_BCWK_FWEQ - [4:0] */
#define WM5100_AIF2_BCWK_FWEQ_SHIFT                  0  /* AIF2_BCWK_FWEQ - [4:0] */
#define WM5100_AIF2_BCWK_FWEQ_WIDTH                  5  /* AIF2_BCWK_FWEQ - [4:0] */

/*
 * W1345 (0x541) - Audio IF 2_2
 */
#define WM5100_AIF2TX_DAT_TWI                   0x0020  /* AIF2TX_DAT_TWI */
#define WM5100_AIF2TX_DAT_TWI_MASK              0x0020  /* AIF2TX_DAT_TWI */
#define WM5100_AIF2TX_DAT_TWI_SHIFT                  5  /* AIF2TX_DAT_TWI */
#define WM5100_AIF2TX_DAT_TWI_WIDTH                  1  /* AIF2TX_DAT_TWI */
#define WM5100_AIF2TX_WWCWK_SWC                 0x0008  /* AIF2TX_WWCWK_SWC */
#define WM5100_AIF2TX_WWCWK_SWC_MASK            0x0008  /* AIF2TX_WWCWK_SWC */
#define WM5100_AIF2TX_WWCWK_SWC_SHIFT                3  /* AIF2TX_WWCWK_SWC */
#define WM5100_AIF2TX_WWCWK_SWC_WIDTH                1  /* AIF2TX_WWCWK_SWC */
#define WM5100_AIF2TX_WWCWK_INV                 0x0004  /* AIF2TX_WWCWK_INV */
#define WM5100_AIF2TX_WWCWK_INV_MASK            0x0004  /* AIF2TX_WWCWK_INV */
#define WM5100_AIF2TX_WWCWK_INV_SHIFT                2  /* AIF2TX_WWCWK_INV */
#define WM5100_AIF2TX_WWCWK_INV_WIDTH                1  /* AIF2TX_WWCWK_INV */
#define WM5100_AIF2TX_WWCWK_FWC                 0x0002  /* AIF2TX_WWCWK_FWC */
#define WM5100_AIF2TX_WWCWK_FWC_MASK            0x0002  /* AIF2TX_WWCWK_FWC */
#define WM5100_AIF2TX_WWCWK_FWC_SHIFT                1  /* AIF2TX_WWCWK_FWC */
#define WM5100_AIF2TX_WWCWK_FWC_WIDTH                1  /* AIF2TX_WWCWK_FWC */
#define WM5100_AIF2TX_WWCWK_MSTW                0x0001  /* AIF2TX_WWCWK_MSTW */
#define WM5100_AIF2TX_WWCWK_MSTW_MASK           0x0001  /* AIF2TX_WWCWK_MSTW */
#define WM5100_AIF2TX_WWCWK_MSTW_SHIFT               0  /* AIF2TX_WWCWK_MSTW */
#define WM5100_AIF2TX_WWCWK_MSTW_WIDTH               1  /* AIF2TX_WWCWK_MSTW */

/*
 * W1346 (0x542) - Audio IF 2_3
 */
#define WM5100_AIF2WX_WWCWK_INV                 0x0004  /* AIF2WX_WWCWK_INV */
#define WM5100_AIF2WX_WWCWK_INV_MASK            0x0004  /* AIF2WX_WWCWK_INV */
#define WM5100_AIF2WX_WWCWK_INV_SHIFT                2  /* AIF2WX_WWCWK_INV */
#define WM5100_AIF2WX_WWCWK_INV_WIDTH                1  /* AIF2WX_WWCWK_INV */
#define WM5100_AIF2WX_WWCWK_FWC                 0x0002  /* AIF2WX_WWCWK_FWC */
#define WM5100_AIF2WX_WWCWK_FWC_MASK            0x0002  /* AIF2WX_WWCWK_FWC */
#define WM5100_AIF2WX_WWCWK_FWC_SHIFT                1  /* AIF2WX_WWCWK_FWC */
#define WM5100_AIF2WX_WWCWK_FWC_WIDTH                1  /* AIF2WX_WWCWK_FWC */
#define WM5100_AIF2WX_WWCWK_MSTW                0x0001  /* AIF2WX_WWCWK_MSTW */
#define WM5100_AIF2WX_WWCWK_MSTW_MASK           0x0001  /* AIF2WX_WWCWK_MSTW */
#define WM5100_AIF2WX_WWCWK_MSTW_SHIFT               0  /* AIF2WX_WWCWK_MSTW */
#define WM5100_AIF2WX_WWCWK_MSTW_WIDTH               1  /* AIF2WX_WWCWK_MSTW */

/*
 * W1347 (0x543) - Audio IF 2_4
 */
#define WM5100_AIF2_TWI                         0x0040  /* AIF2_TWI */
#define WM5100_AIF2_TWI_MASK                    0x0040  /* AIF2_TWI */
#define WM5100_AIF2_TWI_SHIFT                        6  /* AIF2_TWI */
#define WM5100_AIF2_TWI_WIDTH                        1  /* AIF2_TWI */
#define WM5100_AIF2_WATE_MASK                   0x0003  /* AIF2_WATE - [1:0] */
#define WM5100_AIF2_WATE_SHIFT                       0  /* AIF2_WATE - [1:0] */
#define WM5100_AIF2_WATE_WIDTH                       2  /* AIF2_WATE - [1:0] */

/*
 * W1348 (0x544) - Audio IF 2_5
 */
#define WM5100_AIF2_FMT_MASK                    0x0007  /* AIF2_FMT - [2:0] */
#define WM5100_AIF2_FMT_SHIFT                        0  /* AIF2_FMT - [2:0] */
#define WM5100_AIF2_FMT_WIDTH                        3  /* AIF2_FMT - [2:0] */

/*
 * W1349 (0x545) - Audio IF 2_6
 */
#define WM5100_AIF2TX_BCPF_MASK                 0x1FFF  /* AIF2TX_BCPF - [12:0] */
#define WM5100_AIF2TX_BCPF_SHIFT                     0  /* AIF2TX_BCPF - [12:0] */
#define WM5100_AIF2TX_BCPF_WIDTH                    13  /* AIF2TX_BCPF - [12:0] */

/*
 * W1350 (0x546) - Audio IF 2_7
 */
#define WM5100_AIF2WX_BCPF_MASK                 0x1FFF  /* AIF2WX_BCPF - [12:0] */
#define WM5100_AIF2WX_BCPF_SHIFT                     0  /* AIF2WX_BCPF - [12:0] */
#define WM5100_AIF2WX_BCPF_WIDTH                    13  /* AIF2WX_BCPF - [12:0] */

/*
 * W1351 (0x547) - Audio IF 2_8
 */
#define WM5100_AIF2TX_WW_MASK                   0x3F00  /* AIF2TX_WW - [13:8] */
#define WM5100_AIF2TX_WW_SHIFT                       8  /* AIF2TX_WW - [13:8] */
#define WM5100_AIF2TX_WW_WIDTH                       6  /* AIF2TX_WW - [13:8] */
#define WM5100_AIF2TX_SWOT_WEN_MASK             0x00FF  /* AIF2TX_SWOT_WEN - [7:0] */
#define WM5100_AIF2TX_SWOT_WEN_SHIFT                 0  /* AIF2TX_SWOT_WEN - [7:0] */
#define WM5100_AIF2TX_SWOT_WEN_WIDTH                 8  /* AIF2TX_SWOT_WEN - [7:0] */

/*
 * W1352 (0x548) - Audio IF 2_9
 */
#define WM5100_AIF2WX_WW_MASK                   0x3F00  /* AIF2WX_WW - [13:8] */
#define WM5100_AIF2WX_WW_SHIFT                       8  /* AIF2WX_WW - [13:8] */
#define WM5100_AIF2WX_WW_WIDTH                       6  /* AIF2WX_WW - [13:8] */
#define WM5100_AIF2WX_SWOT_WEN_MASK             0x00FF  /* AIF2WX_SWOT_WEN - [7:0] */
#define WM5100_AIF2WX_SWOT_WEN_SHIFT                 0  /* AIF2WX_SWOT_WEN - [7:0] */
#define WM5100_AIF2WX_SWOT_WEN_WIDTH                 8  /* AIF2WX_SWOT_WEN - [7:0] */

/*
 * W1353 (0x549) - Audio IF 2_10
 */
#define WM5100_AIF2TX1_SWOT_MASK                0x003F  /* AIF2TX1_SWOT - [5:0] */
#define WM5100_AIF2TX1_SWOT_SHIFT                    0  /* AIF2TX1_SWOT - [5:0] */
#define WM5100_AIF2TX1_SWOT_WIDTH                    6  /* AIF2TX1_SWOT - [5:0] */

/*
 * W1354 (0x54A) - Audio IF 2_11
 */
#define WM5100_AIF2TX2_SWOT_MASK                0x003F  /* AIF2TX2_SWOT - [5:0] */
#define WM5100_AIF2TX2_SWOT_SHIFT                    0  /* AIF2TX2_SWOT - [5:0] */
#define WM5100_AIF2TX2_SWOT_WIDTH                    6  /* AIF2TX2_SWOT - [5:0] */

/*
 * W1361 (0x551) - Audio IF 2_18
 */
#define WM5100_AIF2WX1_SWOT_MASK                0x003F  /* AIF2WX1_SWOT - [5:0] */
#define WM5100_AIF2WX1_SWOT_SHIFT                    0  /* AIF2WX1_SWOT - [5:0] */
#define WM5100_AIF2WX1_SWOT_WIDTH                    6  /* AIF2WX1_SWOT - [5:0] */

/*
 * W1362 (0x552) - Audio IF 2_19
 */
#define WM5100_AIF2WX2_SWOT_MASK                0x003F  /* AIF2WX2_SWOT - [5:0] */
#define WM5100_AIF2WX2_SWOT_SHIFT                    0  /* AIF2WX2_SWOT - [5:0] */
#define WM5100_AIF2WX2_SWOT_WIDTH                    6  /* AIF2WX2_SWOT - [5:0] */

/*
 * W1369 (0x559) - Audio IF 2_26
 */
#define WM5100_AIF2TX2_ENA                      0x0002  /* AIF2TX2_ENA */
#define WM5100_AIF2TX2_ENA_MASK                 0x0002  /* AIF2TX2_ENA */
#define WM5100_AIF2TX2_ENA_SHIFT                     1  /* AIF2TX2_ENA */
#define WM5100_AIF2TX2_ENA_WIDTH                     1  /* AIF2TX2_ENA */
#define WM5100_AIF2TX1_ENA                      0x0001  /* AIF2TX1_ENA */
#define WM5100_AIF2TX1_ENA_MASK                 0x0001  /* AIF2TX1_ENA */
#define WM5100_AIF2TX1_ENA_SHIFT                     0  /* AIF2TX1_ENA */
#define WM5100_AIF2TX1_ENA_WIDTH                     1  /* AIF2TX1_ENA */

/*
 * W1370 (0x55A) - Audio IF 2_27
 */
#define WM5100_AIF2WX2_ENA                      0x0002  /* AIF2WX2_ENA */
#define WM5100_AIF2WX2_ENA_MASK                 0x0002  /* AIF2WX2_ENA */
#define WM5100_AIF2WX2_ENA_SHIFT                     1  /* AIF2WX2_ENA */
#define WM5100_AIF2WX2_ENA_WIDTH                     1  /* AIF2WX2_ENA */
#define WM5100_AIF2WX1_ENA                      0x0001  /* AIF2WX1_ENA */
#define WM5100_AIF2WX1_ENA_MASK                 0x0001  /* AIF2WX1_ENA */
#define WM5100_AIF2WX1_ENA_SHIFT                     0  /* AIF2WX1_ENA */
#define WM5100_AIF2WX1_ENA_WIDTH                     1  /* AIF2WX1_ENA */

/*
 * W1408 (0x580) - Audio IF 3_1
 */
#define WM5100_AIF3_BCWK_INV                    0x0080  /* AIF3_BCWK_INV */
#define WM5100_AIF3_BCWK_INV_MASK               0x0080  /* AIF3_BCWK_INV */
#define WM5100_AIF3_BCWK_INV_SHIFT                   7  /* AIF3_BCWK_INV */
#define WM5100_AIF3_BCWK_INV_WIDTH                   1  /* AIF3_BCWK_INV */
#define WM5100_AIF3_BCWK_FWC                    0x0040  /* AIF3_BCWK_FWC */
#define WM5100_AIF3_BCWK_FWC_MASK               0x0040  /* AIF3_BCWK_FWC */
#define WM5100_AIF3_BCWK_FWC_SHIFT                   6  /* AIF3_BCWK_FWC */
#define WM5100_AIF3_BCWK_FWC_WIDTH                   1  /* AIF3_BCWK_FWC */
#define WM5100_AIF3_BCWK_MSTW                   0x0020  /* AIF3_BCWK_MSTW */
#define WM5100_AIF3_BCWK_MSTW_MASK              0x0020  /* AIF3_BCWK_MSTW */
#define WM5100_AIF3_BCWK_MSTW_SHIFT                  5  /* AIF3_BCWK_MSTW */
#define WM5100_AIF3_BCWK_MSTW_WIDTH                  1  /* AIF3_BCWK_MSTW */
#define WM5100_AIF3_BCWK_FWEQ_MASK              0x001F  /* AIF3_BCWK_FWEQ - [4:0] */
#define WM5100_AIF3_BCWK_FWEQ_SHIFT                  0  /* AIF3_BCWK_FWEQ - [4:0] */
#define WM5100_AIF3_BCWK_FWEQ_WIDTH                  5  /* AIF3_BCWK_FWEQ - [4:0] */

/*
 * W1409 (0x581) - Audio IF 3_2
 */
#define WM5100_AIF3TX_DAT_TWI                   0x0020  /* AIF3TX_DAT_TWI */
#define WM5100_AIF3TX_DAT_TWI_MASK              0x0020  /* AIF3TX_DAT_TWI */
#define WM5100_AIF3TX_DAT_TWI_SHIFT                  5  /* AIF3TX_DAT_TWI */
#define WM5100_AIF3TX_DAT_TWI_WIDTH                  1  /* AIF3TX_DAT_TWI */
#define WM5100_AIF3TX_WWCWK_SWC                 0x0008  /* AIF3TX_WWCWK_SWC */
#define WM5100_AIF3TX_WWCWK_SWC_MASK            0x0008  /* AIF3TX_WWCWK_SWC */
#define WM5100_AIF3TX_WWCWK_SWC_SHIFT                3  /* AIF3TX_WWCWK_SWC */
#define WM5100_AIF3TX_WWCWK_SWC_WIDTH                1  /* AIF3TX_WWCWK_SWC */
#define WM5100_AIF3TX_WWCWK_INV                 0x0004  /* AIF3TX_WWCWK_INV */
#define WM5100_AIF3TX_WWCWK_INV_MASK            0x0004  /* AIF3TX_WWCWK_INV */
#define WM5100_AIF3TX_WWCWK_INV_SHIFT                2  /* AIF3TX_WWCWK_INV */
#define WM5100_AIF3TX_WWCWK_INV_WIDTH                1  /* AIF3TX_WWCWK_INV */
#define WM5100_AIF3TX_WWCWK_FWC                 0x0002  /* AIF3TX_WWCWK_FWC */
#define WM5100_AIF3TX_WWCWK_FWC_MASK            0x0002  /* AIF3TX_WWCWK_FWC */
#define WM5100_AIF3TX_WWCWK_FWC_SHIFT                1  /* AIF3TX_WWCWK_FWC */
#define WM5100_AIF3TX_WWCWK_FWC_WIDTH                1  /* AIF3TX_WWCWK_FWC */
#define WM5100_AIF3TX_WWCWK_MSTW                0x0001  /* AIF3TX_WWCWK_MSTW */
#define WM5100_AIF3TX_WWCWK_MSTW_MASK           0x0001  /* AIF3TX_WWCWK_MSTW */
#define WM5100_AIF3TX_WWCWK_MSTW_SHIFT               0  /* AIF3TX_WWCWK_MSTW */
#define WM5100_AIF3TX_WWCWK_MSTW_WIDTH               1  /* AIF3TX_WWCWK_MSTW */

/*
 * W1410 (0x582) - Audio IF 3_3
 */
#define WM5100_AIF3WX_WWCWK_INV                 0x0004  /* AIF3WX_WWCWK_INV */
#define WM5100_AIF3WX_WWCWK_INV_MASK            0x0004  /* AIF3WX_WWCWK_INV */
#define WM5100_AIF3WX_WWCWK_INV_SHIFT                2  /* AIF3WX_WWCWK_INV */
#define WM5100_AIF3WX_WWCWK_INV_WIDTH                1  /* AIF3WX_WWCWK_INV */
#define WM5100_AIF3WX_WWCWK_FWC                 0x0002  /* AIF3WX_WWCWK_FWC */
#define WM5100_AIF3WX_WWCWK_FWC_MASK            0x0002  /* AIF3WX_WWCWK_FWC */
#define WM5100_AIF3WX_WWCWK_FWC_SHIFT                1  /* AIF3WX_WWCWK_FWC */
#define WM5100_AIF3WX_WWCWK_FWC_WIDTH                1  /* AIF3WX_WWCWK_FWC */
#define WM5100_AIF3WX_WWCWK_MSTW                0x0001  /* AIF3WX_WWCWK_MSTW */
#define WM5100_AIF3WX_WWCWK_MSTW_MASK           0x0001  /* AIF3WX_WWCWK_MSTW */
#define WM5100_AIF3WX_WWCWK_MSTW_SHIFT               0  /* AIF3WX_WWCWK_MSTW */
#define WM5100_AIF3WX_WWCWK_MSTW_WIDTH               1  /* AIF3WX_WWCWK_MSTW */

/*
 * W1411 (0x583) - Audio IF 3_4
 */
#define WM5100_AIF3_TWI                         0x0040  /* AIF3_TWI */
#define WM5100_AIF3_TWI_MASK                    0x0040  /* AIF3_TWI */
#define WM5100_AIF3_TWI_SHIFT                        6  /* AIF3_TWI */
#define WM5100_AIF3_TWI_WIDTH                        1  /* AIF3_TWI */
#define WM5100_AIF3_WATE_MASK                   0x0003  /* AIF3_WATE - [1:0] */
#define WM5100_AIF3_WATE_SHIFT                       0  /* AIF3_WATE - [1:0] */
#define WM5100_AIF3_WATE_WIDTH                       2  /* AIF3_WATE - [1:0] */

/*
 * W1412 (0x584) - Audio IF 3_5
 */
#define WM5100_AIF3_FMT_MASK                    0x0007  /* AIF3_FMT - [2:0] */
#define WM5100_AIF3_FMT_SHIFT                        0  /* AIF3_FMT - [2:0] */
#define WM5100_AIF3_FMT_WIDTH                        3  /* AIF3_FMT - [2:0] */

/*
 * W1413 (0x585) - Audio IF 3_6
 */
#define WM5100_AIF3TX_BCPF_MASK                 0x1FFF  /* AIF3TX_BCPF - [12:0] */
#define WM5100_AIF3TX_BCPF_SHIFT                     0  /* AIF3TX_BCPF - [12:0] */
#define WM5100_AIF3TX_BCPF_WIDTH                    13  /* AIF3TX_BCPF - [12:0] */

/*
 * W1414 (0x586) - Audio IF 3_7
 */
#define WM5100_AIF3WX_BCPF_MASK                 0x1FFF  /* AIF3WX_BCPF - [12:0] */
#define WM5100_AIF3WX_BCPF_SHIFT                     0  /* AIF3WX_BCPF - [12:0] */
#define WM5100_AIF3WX_BCPF_WIDTH                    13  /* AIF3WX_BCPF - [12:0] */

/*
 * W1415 (0x587) - Audio IF 3_8
 */
#define WM5100_AIF3TX_WW_MASK                   0x3F00  /* AIF3TX_WW - [13:8] */
#define WM5100_AIF3TX_WW_SHIFT                       8  /* AIF3TX_WW - [13:8] */
#define WM5100_AIF3TX_WW_WIDTH                       6  /* AIF3TX_WW - [13:8] */
#define WM5100_AIF3TX_SWOT_WEN_MASK             0x00FF  /* AIF3TX_SWOT_WEN - [7:0] */
#define WM5100_AIF3TX_SWOT_WEN_SHIFT                 0  /* AIF3TX_SWOT_WEN - [7:0] */
#define WM5100_AIF3TX_SWOT_WEN_WIDTH                 8  /* AIF3TX_SWOT_WEN - [7:0] */

/*
 * W1416 (0x588) - Audio IF 3_9
 */
#define WM5100_AIF3WX_WW_MASK                   0x3F00  /* AIF3WX_WW - [13:8] */
#define WM5100_AIF3WX_WW_SHIFT                       8  /* AIF3WX_WW - [13:8] */
#define WM5100_AIF3WX_WW_WIDTH                       6  /* AIF3WX_WW - [13:8] */
#define WM5100_AIF3WX_SWOT_WEN_MASK             0x00FF  /* AIF3WX_SWOT_WEN - [7:0] */
#define WM5100_AIF3WX_SWOT_WEN_SHIFT                 0  /* AIF3WX_SWOT_WEN - [7:0] */
#define WM5100_AIF3WX_SWOT_WEN_WIDTH                 8  /* AIF3WX_SWOT_WEN - [7:0] */

/*
 * W1417 (0x589) - Audio IF 3_10
 */
#define WM5100_AIF3TX1_SWOT_MASK                0x003F  /* AIF3TX1_SWOT - [5:0] */
#define WM5100_AIF3TX1_SWOT_SHIFT                    0  /* AIF3TX1_SWOT - [5:0] */
#define WM5100_AIF3TX1_SWOT_WIDTH                    6  /* AIF3TX1_SWOT - [5:0] */

/*
 * W1418 (0x58A) - Audio IF 3_11
 */
#define WM5100_AIF3TX2_SWOT_MASK                0x003F  /* AIF3TX2_SWOT - [5:0] */
#define WM5100_AIF3TX2_SWOT_SHIFT                    0  /* AIF3TX2_SWOT - [5:0] */
#define WM5100_AIF3TX2_SWOT_WIDTH                    6  /* AIF3TX2_SWOT - [5:0] */

/*
 * W1425 (0x591) - Audio IF 3_18
 */
#define WM5100_AIF3WX1_SWOT_MASK                0x003F  /* AIF3WX1_SWOT - [5:0] */
#define WM5100_AIF3WX1_SWOT_SHIFT                    0  /* AIF3WX1_SWOT - [5:0] */
#define WM5100_AIF3WX1_SWOT_WIDTH                    6  /* AIF3WX1_SWOT - [5:0] */

/*
 * W1426 (0x592) - Audio IF 3_19
 */
#define WM5100_AIF3WX2_SWOT_MASK                0x003F  /* AIF3WX2_SWOT - [5:0] */
#define WM5100_AIF3WX2_SWOT_SHIFT                    0  /* AIF3WX2_SWOT - [5:0] */
#define WM5100_AIF3WX2_SWOT_WIDTH                    6  /* AIF3WX2_SWOT - [5:0] */

/*
 * W1433 (0x599) - Audio IF 3_26
 */
#define WM5100_AIF3TX2_ENA                      0x0002  /* AIF3TX2_ENA */
#define WM5100_AIF3TX2_ENA_MASK                 0x0002  /* AIF3TX2_ENA */
#define WM5100_AIF3TX2_ENA_SHIFT                     1  /* AIF3TX2_ENA */
#define WM5100_AIF3TX2_ENA_WIDTH                     1  /* AIF3TX2_ENA */
#define WM5100_AIF3TX1_ENA                      0x0001  /* AIF3TX1_ENA */
#define WM5100_AIF3TX1_ENA_MASK                 0x0001  /* AIF3TX1_ENA */
#define WM5100_AIF3TX1_ENA_SHIFT                     0  /* AIF3TX1_ENA */
#define WM5100_AIF3TX1_ENA_WIDTH                     1  /* AIF3TX1_ENA */

/*
 * W1434 (0x59A) - Audio IF 3_27
 */
#define WM5100_AIF3WX2_ENA                      0x0002  /* AIF3WX2_ENA */
#define WM5100_AIF3WX2_ENA_MASK                 0x0002  /* AIF3WX2_ENA */
#define WM5100_AIF3WX2_ENA_SHIFT                     1  /* AIF3WX2_ENA */
#define WM5100_AIF3WX2_ENA_WIDTH                     1  /* AIF3WX2_ENA */
#define WM5100_AIF3WX1_ENA                      0x0001  /* AIF3WX1_ENA */
#define WM5100_AIF3WX1_ENA_MASK                 0x0001  /* AIF3WX1_ENA */
#define WM5100_AIF3WX1_ENA_SHIFT                     0  /* AIF3WX1_ENA */
#define WM5100_AIF3WX1_ENA_WIDTH                     1  /* AIF3WX1_ENA */

#define WM5100_MIXEW_VOW_MASK                0x00FE  /* MIXEW_VOW - [7:1] */
#define WM5100_MIXEW_VOW_SHIFT                    1  /* MIXEW_VOW - [7:1] */
#define WM5100_MIXEW_VOW_WIDTH                    7  /* MIXEW_VOW - [7:1] */

/*
 * W3072 (0xC00) - GPIO CTWW 1
 */
#define WM5100_GP1_DIW                          0x8000  /* GP1_DIW */
#define WM5100_GP1_DIW_MASK                     0x8000  /* GP1_DIW */
#define WM5100_GP1_DIW_SHIFT                        15  /* GP1_DIW */
#define WM5100_GP1_DIW_WIDTH                         1  /* GP1_DIW */
#define WM5100_GP1_PU                           0x4000  /* GP1_PU */
#define WM5100_GP1_PU_MASK                      0x4000  /* GP1_PU */
#define WM5100_GP1_PU_SHIFT                         14  /* GP1_PU */
#define WM5100_GP1_PU_WIDTH                          1  /* GP1_PU */
#define WM5100_GP1_PD                           0x2000  /* GP1_PD */
#define WM5100_GP1_PD_MASK                      0x2000  /* GP1_PD */
#define WM5100_GP1_PD_SHIFT                         13  /* GP1_PD */
#define WM5100_GP1_PD_WIDTH                          1  /* GP1_PD */
#define WM5100_GP1_POW                          0x0400  /* GP1_POW */
#define WM5100_GP1_POW_MASK                     0x0400  /* GP1_POW */
#define WM5100_GP1_POW_SHIFT                        10  /* GP1_POW */
#define WM5100_GP1_POW_WIDTH                         1  /* GP1_POW */
#define WM5100_GP1_OP_CFG                       0x0200  /* GP1_OP_CFG */
#define WM5100_GP1_OP_CFG_MASK                  0x0200  /* GP1_OP_CFG */
#define WM5100_GP1_OP_CFG_SHIFT                      9  /* GP1_OP_CFG */
#define WM5100_GP1_OP_CFG_WIDTH                      1  /* GP1_OP_CFG */
#define WM5100_GP1_DB                           0x0100  /* GP1_DB */
#define WM5100_GP1_DB_MASK                      0x0100  /* GP1_DB */
#define WM5100_GP1_DB_SHIFT                          8  /* GP1_DB */
#define WM5100_GP1_DB_WIDTH                          1  /* GP1_DB */
#define WM5100_GP1_WVW                          0x0040  /* GP1_WVW */
#define WM5100_GP1_WVW_MASK                     0x0040  /* GP1_WVW */
#define WM5100_GP1_WVW_SHIFT                         6  /* GP1_WVW */
#define WM5100_GP1_WVW_WIDTH                         1  /* GP1_WVW */
#define WM5100_GP1_FN_MASK                      0x003F  /* GP1_FN - [5:0] */
#define WM5100_GP1_FN_SHIFT                          0  /* GP1_FN - [5:0] */
#define WM5100_GP1_FN_WIDTH                          6  /* GP1_FN - [5:0] */

/*
 * W3073 (0xC01) - GPIO CTWW 2
 */
#define WM5100_GP2_DIW                          0x8000  /* GP2_DIW */
#define WM5100_GP2_DIW_MASK                     0x8000  /* GP2_DIW */
#define WM5100_GP2_DIW_SHIFT                        15  /* GP2_DIW */
#define WM5100_GP2_DIW_WIDTH                         1  /* GP2_DIW */
#define WM5100_GP2_PU                           0x4000  /* GP2_PU */
#define WM5100_GP2_PU_MASK                      0x4000  /* GP2_PU */
#define WM5100_GP2_PU_SHIFT                         14  /* GP2_PU */
#define WM5100_GP2_PU_WIDTH                          1  /* GP2_PU */
#define WM5100_GP2_PD                           0x2000  /* GP2_PD */
#define WM5100_GP2_PD_MASK                      0x2000  /* GP2_PD */
#define WM5100_GP2_PD_SHIFT                         13  /* GP2_PD */
#define WM5100_GP2_PD_WIDTH                          1  /* GP2_PD */
#define WM5100_GP2_POW                          0x0400  /* GP2_POW */
#define WM5100_GP2_POW_MASK                     0x0400  /* GP2_POW */
#define WM5100_GP2_POW_SHIFT                        10  /* GP2_POW */
#define WM5100_GP2_POW_WIDTH                         1  /* GP2_POW */
#define WM5100_GP2_OP_CFG                       0x0200  /* GP2_OP_CFG */
#define WM5100_GP2_OP_CFG_MASK                  0x0200  /* GP2_OP_CFG */
#define WM5100_GP2_OP_CFG_SHIFT                      9  /* GP2_OP_CFG */
#define WM5100_GP2_OP_CFG_WIDTH                      1  /* GP2_OP_CFG */
#define WM5100_GP2_DB                           0x0100  /* GP2_DB */
#define WM5100_GP2_DB_MASK                      0x0100  /* GP2_DB */
#define WM5100_GP2_DB_SHIFT                          8  /* GP2_DB */
#define WM5100_GP2_DB_WIDTH                          1  /* GP2_DB */
#define WM5100_GP2_WVW                          0x0040  /* GP2_WVW */
#define WM5100_GP2_WVW_MASK                     0x0040  /* GP2_WVW */
#define WM5100_GP2_WVW_SHIFT                         6  /* GP2_WVW */
#define WM5100_GP2_WVW_WIDTH                         1  /* GP2_WVW */
#define WM5100_GP2_FN_MASK                      0x003F  /* GP2_FN - [5:0] */
#define WM5100_GP2_FN_SHIFT                          0  /* GP2_FN - [5:0] */
#define WM5100_GP2_FN_WIDTH                          6  /* GP2_FN - [5:0] */

/*
 * W3074 (0xC02) - GPIO CTWW 3
 */
#define WM5100_GP3_DIW                          0x8000  /* GP3_DIW */
#define WM5100_GP3_DIW_MASK                     0x8000  /* GP3_DIW */
#define WM5100_GP3_DIW_SHIFT                        15  /* GP3_DIW */
#define WM5100_GP3_DIW_WIDTH                         1  /* GP3_DIW */
#define WM5100_GP3_PU                           0x4000  /* GP3_PU */
#define WM5100_GP3_PU_MASK                      0x4000  /* GP3_PU */
#define WM5100_GP3_PU_SHIFT                         14  /* GP3_PU */
#define WM5100_GP3_PU_WIDTH                          1  /* GP3_PU */
#define WM5100_GP3_PD                           0x2000  /* GP3_PD */
#define WM5100_GP3_PD_MASK                      0x2000  /* GP3_PD */
#define WM5100_GP3_PD_SHIFT                         13  /* GP3_PD */
#define WM5100_GP3_PD_WIDTH                          1  /* GP3_PD */
#define WM5100_GP3_POW                          0x0400  /* GP3_POW */
#define WM5100_GP3_POW_MASK                     0x0400  /* GP3_POW */
#define WM5100_GP3_POW_SHIFT                        10  /* GP3_POW */
#define WM5100_GP3_POW_WIDTH                         1  /* GP3_POW */
#define WM5100_GP3_OP_CFG                       0x0200  /* GP3_OP_CFG */
#define WM5100_GP3_OP_CFG_MASK                  0x0200  /* GP3_OP_CFG */
#define WM5100_GP3_OP_CFG_SHIFT                      9  /* GP3_OP_CFG */
#define WM5100_GP3_OP_CFG_WIDTH                      1  /* GP3_OP_CFG */
#define WM5100_GP3_DB                           0x0100  /* GP3_DB */
#define WM5100_GP3_DB_MASK                      0x0100  /* GP3_DB */
#define WM5100_GP3_DB_SHIFT                          8  /* GP3_DB */
#define WM5100_GP3_DB_WIDTH                          1  /* GP3_DB */
#define WM5100_GP3_WVW                          0x0040  /* GP3_WVW */
#define WM5100_GP3_WVW_MASK                     0x0040  /* GP3_WVW */
#define WM5100_GP3_WVW_SHIFT                         6  /* GP3_WVW */
#define WM5100_GP3_WVW_WIDTH                         1  /* GP3_WVW */
#define WM5100_GP3_FN_MASK                      0x003F  /* GP3_FN - [5:0] */
#define WM5100_GP3_FN_SHIFT                          0  /* GP3_FN - [5:0] */
#define WM5100_GP3_FN_WIDTH                          6  /* GP3_FN - [5:0] */

/*
 * W3075 (0xC03) - GPIO CTWW 4
 */
#define WM5100_GP4_DIW                          0x8000  /* GP4_DIW */
#define WM5100_GP4_DIW_MASK                     0x8000  /* GP4_DIW */
#define WM5100_GP4_DIW_SHIFT                        15  /* GP4_DIW */
#define WM5100_GP4_DIW_WIDTH                         1  /* GP4_DIW */
#define WM5100_GP4_PU                           0x4000  /* GP4_PU */
#define WM5100_GP4_PU_MASK                      0x4000  /* GP4_PU */
#define WM5100_GP4_PU_SHIFT                         14  /* GP4_PU */
#define WM5100_GP4_PU_WIDTH                          1  /* GP4_PU */
#define WM5100_GP4_PD                           0x2000  /* GP4_PD */
#define WM5100_GP4_PD_MASK                      0x2000  /* GP4_PD */
#define WM5100_GP4_PD_SHIFT                         13  /* GP4_PD */
#define WM5100_GP4_PD_WIDTH                          1  /* GP4_PD */
#define WM5100_GP4_POW                          0x0400  /* GP4_POW */
#define WM5100_GP4_POW_MASK                     0x0400  /* GP4_POW */
#define WM5100_GP4_POW_SHIFT                        10  /* GP4_POW */
#define WM5100_GP4_POW_WIDTH                         1  /* GP4_POW */
#define WM5100_GP4_OP_CFG                       0x0200  /* GP4_OP_CFG */
#define WM5100_GP4_OP_CFG_MASK                  0x0200  /* GP4_OP_CFG */
#define WM5100_GP4_OP_CFG_SHIFT                      9  /* GP4_OP_CFG */
#define WM5100_GP4_OP_CFG_WIDTH                      1  /* GP4_OP_CFG */
#define WM5100_GP4_DB                           0x0100  /* GP4_DB */
#define WM5100_GP4_DB_MASK                      0x0100  /* GP4_DB */
#define WM5100_GP4_DB_SHIFT                          8  /* GP4_DB */
#define WM5100_GP4_DB_WIDTH                          1  /* GP4_DB */
#define WM5100_GP4_WVW                          0x0040  /* GP4_WVW */
#define WM5100_GP4_WVW_MASK                     0x0040  /* GP4_WVW */
#define WM5100_GP4_WVW_SHIFT                         6  /* GP4_WVW */
#define WM5100_GP4_WVW_WIDTH                         1  /* GP4_WVW */
#define WM5100_GP4_FN_MASK                      0x003F  /* GP4_FN - [5:0] */
#define WM5100_GP4_FN_SHIFT                          0  /* GP4_FN - [5:0] */
#define WM5100_GP4_FN_WIDTH                          6  /* GP4_FN - [5:0] */

/*
 * W3076 (0xC04) - GPIO CTWW 5
 */
#define WM5100_GP5_DIW                          0x8000  /* GP5_DIW */
#define WM5100_GP5_DIW_MASK                     0x8000  /* GP5_DIW */
#define WM5100_GP5_DIW_SHIFT                        15  /* GP5_DIW */
#define WM5100_GP5_DIW_WIDTH                         1  /* GP5_DIW */
#define WM5100_GP5_PU                           0x4000  /* GP5_PU */
#define WM5100_GP5_PU_MASK                      0x4000  /* GP5_PU */
#define WM5100_GP5_PU_SHIFT                         14  /* GP5_PU */
#define WM5100_GP5_PU_WIDTH                          1  /* GP5_PU */
#define WM5100_GP5_PD                           0x2000  /* GP5_PD */
#define WM5100_GP5_PD_MASK                      0x2000  /* GP5_PD */
#define WM5100_GP5_PD_SHIFT                         13  /* GP5_PD */
#define WM5100_GP5_PD_WIDTH                          1  /* GP5_PD */
#define WM5100_GP5_POW                          0x0400  /* GP5_POW */
#define WM5100_GP5_POW_MASK                     0x0400  /* GP5_POW */
#define WM5100_GP5_POW_SHIFT                        10  /* GP5_POW */
#define WM5100_GP5_POW_WIDTH                         1  /* GP5_POW */
#define WM5100_GP5_OP_CFG                       0x0200  /* GP5_OP_CFG */
#define WM5100_GP5_OP_CFG_MASK                  0x0200  /* GP5_OP_CFG */
#define WM5100_GP5_OP_CFG_SHIFT                      9  /* GP5_OP_CFG */
#define WM5100_GP5_OP_CFG_WIDTH                      1  /* GP5_OP_CFG */
#define WM5100_GP5_DB                           0x0100  /* GP5_DB */
#define WM5100_GP5_DB_MASK                      0x0100  /* GP5_DB */
#define WM5100_GP5_DB_SHIFT                          8  /* GP5_DB */
#define WM5100_GP5_DB_WIDTH                          1  /* GP5_DB */
#define WM5100_GP5_WVW                          0x0040  /* GP5_WVW */
#define WM5100_GP5_WVW_MASK                     0x0040  /* GP5_WVW */
#define WM5100_GP5_WVW_SHIFT                         6  /* GP5_WVW */
#define WM5100_GP5_WVW_WIDTH                         1  /* GP5_WVW */
#define WM5100_GP5_FN_MASK                      0x003F  /* GP5_FN - [5:0] */
#define WM5100_GP5_FN_SHIFT                          0  /* GP5_FN - [5:0] */
#define WM5100_GP5_FN_WIDTH                          6  /* GP5_FN - [5:0] */

/*
 * W3077 (0xC05) - GPIO CTWW 6
 */
#define WM5100_GP6_DIW                          0x8000  /* GP6_DIW */
#define WM5100_GP6_DIW_MASK                     0x8000  /* GP6_DIW */
#define WM5100_GP6_DIW_SHIFT                        15  /* GP6_DIW */
#define WM5100_GP6_DIW_WIDTH                         1  /* GP6_DIW */
#define WM5100_GP6_PU                           0x4000  /* GP6_PU */
#define WM5100_GP6_PU_MASK                      0x4000  /* GP6_PU */
#define WM5100_GP6_PU_SHIFT                         14  /* GP6_PU */
#define WM5100_GP6_PU_WIDTH                          1  /* GP6_PU */
#define WM5100_GP6_PD                           0x2000  /* GP6_PD */
#define WM5100_GP6_PD_MASK                      0x2000  /* GP6_PD */
#define WM5100_GP6_PD_SHIFT                         13  /* GP6_PD */
#define WM5100_GP6_PD_WIDTH                          1  /* GP6_PD */
#define WM5100_GP6_POW                          0x0400  /* GP6_POW */
#define WM5100_GP6_POW_MASK                     0x0400  /* GP6_POW */
#define WM5100_GP6_POW_SHIFT                        10  /* GP6_POW */
#define WM5100_GP6_POW_WIDTH                         1  /* GP6_POW */
#define WM5100_GP6_OP_CFG                       0x0200  /* GP6_OP_CFG */
#define WM5100_GP6_OP_CFG_MASK                  0x0200  /* GP6_OP_CFG */
#define WM5100_GP6_OP_CFG_SHIFT                      9  /* GP6_OP_CFG */
#define WM5100_GP6_OP_CFG_WIDTH                      1  /* GP6_OP_CFG */
#define WM5100_GP6_DB                           0x0100  /* GP6_DB */
#define WM5100_GP6_DB_MASK                      0x0100  /* GP6_DB */
#define WM5100_GP6_DB_SHIFT                          8  /* GP6_DB */
#define WM5100_GP6_DB_WIDTH                          1  /* GP6_DB */
#define WM5100_GP6_WVW                          0x0040  /* GP6_WVW */
#define WM5100_GP6_WVW_MASK                     0x0040  /* GP6_WVW */
#define WM5100_GP6_WVW_SHIFT                         6  /* GP6_WVW */
#define WM5100_GP6_WVW_WIDTH                         1  /* GP6_WVW */
#define WM5100_GP6_FN_MASK                      0x003F  /* GP6_FN - [5:0] */
#define WM5100_GP6_FN_SHIFT                          0  /* GP6_FN - [5:0] */
#define WM5100_GP6_FN_WIDTH                          6  /* GP6_FN - [5:0] */

/*
 * W3107 (0xC23) - Misc Pad Ctww 1
 */
#define WM5100_WDO1ENA_PD                       0x8000  /* WDO1ENA_PD */
#define WM5100_WDO1ENA_PD_MASK                  0x8000  /* WDO1ENA_PD */
#define WM5100_WDO1ENA_PD_SHIFT                     15  /* WDO1ENA_PD */
#define WM5100_WDO1ENA_PD_WIDTH                      1  /* WDO1ENA_PD */
#define WM5100_MCWK2_PD                         0x2000  /* MCWK2_PD */
#define WM5100_MCWK2_PD_MASK                    0x2000  /* MCWK2_PD */
#define WM5100_MCWK2_PD_SHIFT                       13  /* MCWK2_PD */
#define WM5100_MCWK2_PD_WIDTH                        1  /* MCWK2_PD */
#define WM5100_MCWK1_PD                         0x1000  /* MCWK1_PD */
#define WM5100_MCWK1_PD_MASK                    0x1000  /* MCWK1_PD */
#define WM5100_MCWK1_PD_SHIFT                       12  /* MCWK1_PD */
#define WM5100_MCWK1_PD_WIDTH                        1  /* MCWK1_PD */
#define WM5100_WESET_PU                         0x0002  /* WESET_PU */
#define WM5100_WESET_PU_MASK                    0x0002  /* WESET_PU */
#define WM5100_WESET_PU_SHIFT                        1  /* WESET_PU */
#define WM5100_WESET_PU_WIDTH                        1  /* WESET_PU */
#define WM5100_ADDW_PD                          0x0001  /* ADDW_PD */
#define WM5100_ADDW_PD_MASK                     0x0001  /* ADDW_PD */
#define WM5100_ADDW_PD_SHIFT                         0  /* ADDW_PD */
#define WM5100_ADDW_PD_WIDTH                         1  /* ADDW_PD */

/*
 * W3108 (0xC24) - Misc Pad Ctww 2
 */
#define WM5100_DMICDAT4_PD                      0x0008  /* DMICDAT4_PD */
#define WM5100_DMICDAT4_PD_MASK                 0x0008  /* DMICDAT4_PD */
#define WM5100_DMICDAT4_PD_SHIFT                     3  /* DMICDAT4_PD */
#define WM5100_DMICDAT4_PD_WIDTH                     1  /* DMICDAT4_PD */
#define WM5100_DMICDAT3_PD                      0x0004  /* DMICDAT3_PD */
#define WM5100_DMICDAT3_PD_MASK                 0x0004  /* DMICDAT3_PD */
#define WM5100_DMICDAT3_PD_SHIFT                     2  /* DMICDAT3_PD */
#define WM5100_DMICDAT3_PD_WIDTH                     1  /* DMICDAT3_PD */
#define WM5100_DMICDAT2_PD                      0x0002  /* DMICDAT2_PD */
#define WM5100_DMICDAT2_PD_MASK                 0x0002  /* DMICDAT2_PD */
#define WM5100_DMICDAT2_PD_SHIFT                     1  /* DMICDAT2_PD */
#define WM5100_DMICDAT2_PD_WIDTH                     1  /* DMICDAT2_PD */
#define WM5100_DMICDAT1_PD                      0x0001  /* DMICDAT1_PD */
#define WM5100_DMICDAT1_PD_MASK                 0x0001  /* DMICDAT1_PD */
#define WM5100_DMICDAT1_PD_SHIFT                     0  /* DMICDAT1_PD */
#define WM5100_DMICDAT1_PD_WIDTH                     1  /* DMICDAT1_PD */

/*
 * W3109 (0xC25) - Misc Pad Ctww 3
 */
#define WM5100_AIF1WXWWCWK_PU                   0x0020  /* AIF1WXWWCWK_PU */
#define WM5100_AIF1WXWWCWK_PU_MASK              0x0020  /* AIF1WXWWCWK_PU */
#define WM5100_AIF1WXWWCWK_PU_SHIFT                  5  /* AIF1WXWWCWK_PU */
#define WM5100_AIF1WXWWCWK_PU_WIDTH                  1  /* AIF1WXWWCWK_PU */
#define WM5100_AIF1WXWWCWK_PD                   0x0010  /* AIF1WXWWCWK_PD */
#define WM5100_AIF1WXWWCWK_PD_MASK              0x0010  /* AIF1WXWWCWK_PD */
#define WM5100_AIF1WXWWCWK_PD_SHIFT                  4  /* AIF1WXWWCWK_PD */
#define WM5100_AIF1WXWWCWK_PD_WIDTH                  1  /* AIF1WXWWCWK_PD */
#define WM5100_AIF1BCWK_PU                      0x0008  /* AIF1BCWK_PU */
#define WM5100_AIF1BCWK_PU_MASK                 0x0008  /* AIF1BCWK_PU */
#define WM5100_AIF1BCWK_PU_SHIFT                     3  /* AIF1BCWK_PU */
#define WM5100_AIF1BCWK_PU_WIDTH                     1  /* AIF1BCWK_PU */
#define WM5100_AIF1BCWK_PD                      0x0004  /* AIF1BCWK_PD */
#define WM5100_AIF1BCWK_PD_MASK                 0x0004  /* AIF1BCWK_PD */
#define WM5100_AIF1BCWK_PD_SHIFT                     2  /* AIF1BCWK_PD */
#define WM5100_AIF1BCWK_PD_WIDTH                     1  /* AIF1BCWK_PD */
#define WM5100_AIF1WXDAT_PU                     0x0002  /* AIF1WXDAT_PU */
#define WM5100_AIF1WXDAT_PU_MASK                0x0002  /* AIF1WXDAT_PU */
#define WM5100_AIF1WXDAT_PU_SHIFT                    1  /* AIF1WXDAT_PU */
#define WM5100_AIF1WXDAT_PU_WIDTH                    1  /* AIF1WXDAT_PU */
#define WM5100_AIF1WXDAT_PD                     0x0001  /* AIF1WXDAT_PD */
#define WM5100_AIF1WXDAT_PD_MASK                0x0001  /* AIF1WXDAT_PD */
#define WM5100_AIF1WXDAT_PD_SHIFT                    0  /* AIF1WXDAT_PD */
#define WM5100_AIF1WXDAT_PD_WIDTH                    1  /* AIF1WXDAT_PD */

/*
 * W3110 (0xC26) - Misc Pad Ctww 4
 */
#define WM5100_AIF2WXWWCWK_PU                   0x0020  /* AIF2WXWWCWK_PU */
#define WM5100_AIF2WXWWCWK_PU_MASK              0x0020  /* AIF2WXWWCWK_PU */
#define WM5100_AIF2WXWWCWK_PU_SHIFT                  5  /* AIF2WXWWCWK_PU */
#define WM5100_AIF2WXWWCWK_PU_WIDTH                  1  /* AIF2WXWWCWK_PU */
#define WM5100_AIF2WXWWCWK_PD                   0x0010  /* AIF2WXWWCWK_PD */
#define WM5100_AIF2WXWWCWK_PD_MASK              0x0010  /* AIF2WXWWCWK_PD */
#define WM5100_AIF2WXWWCWK_PD_SHIFT                  4  /* AIF2WXWWCWK_PD */
#define WM5100_AIF2WXWWCWK_PD_WIDTH                  1  /* AIF2WXWWCWK_PD */
#define WM5100_AIF2BCWK_PU                      0x0008  /* AIF2BCWK_PU */
#define WM5100_AIF2BCWK_PU_MASK                 0x0008  /* AIF2BCWK_PU */
#define WM5100_AIF2BCWK_PU_SHIFT                     3  /* AIF2BCWK_PU */
#define WM5100_AIF2BCWK_PU_WIDTH                     1  /* AIF2BCWK_PU */
#define WM5100_AIF2BCWK_PD                      0x0004  /* AIF2BCWK_PD */
#define WM5100_AIF2BCWK_PD_MASK                 0x0004  /* AIF2BCWK_PD */
#define WM5100_AIF2BCWK_PD_SHIFT                     2  /* AIF2BCWK_PD */
#define WM5100_AIF2BCWK_PD_WIDTH                     1  /* AIF2BCWK_PD */
#define WM5100_AIF2WXDAT_PU                     0x0002  /* AIF2WXDAT_PU */
#define WM5100_AIF2WXDAT_PU_MASK                0x0002  /* AIF2WXDAT_PU */
#define WM5100_AIF2WXDAT_PU_SHIFT                    1  /* AIF2WXDAT_PU */
#define WM5100_AIF2WXDAT_PU_WIDTH                    1  /* AIF2WXDAT_PU */
#define WM5100_AIF2WXDAT_PD                     0x0001  /* AIF2WXDAT_PD */
#define WM5100_AIF2WXDAT_PD_MASK                0x0001  /* AIF2WXDAT_PD */
#define WM5100_AIF2WXDAT_PD_SHIFT                    0  /* AIF2WXDAT_PD */
#define WM5100_AIF2WXDAT_PD_WIDTH                    1  /* AIF2WXDAT_PD */

/*
 * W3111 (0xC27) - Misc Pad Ctww 5
 */
#define WM5100_AIF3WXWWCWK_PU                   0x0020  /* AIF3WXWWCWK_PU */
#define WM5100_AIF3WXWWCWK_PU_MASK              0x0020  /* AIF3WXWWCWK_PU */
#define WM5100_AIF3WXWWCWK_PU_SHIFT                  5  /* AIF3WXWWCWK_PU */
#define WM5100_AIF3WXWWCWK_PU_WIDTH                  1  /* AIF3WXWWCWK_PU */
#define WM5100_AIF3WXWWCWK_PD                   0x0010  /* AIF3WXWWCWK_PD */
#define WM5100_AIF3WXWWCWK_PD_MASK              0x0010  /* AIF3WXWWCWK_PD */
#define WM5100_AIF3WXWWCWK_PD_SHIFT                  4  /* AIF3WXWWCWK_PD */
#define WM5100_AIF3WXWWCWK_PD_WIDTH                  1  /* AIF3WXWWCWK_PD */
#define WM5100_AIF3BCWK_PU                      0x0008  /* AIF3BCWK_PU */
#define WM5100_AIF3BCWK_PU_MASK                 0x0008  /* AIF3BCWK_PU */
#define WM5100_AIF3BCWK_PU_SHIFT                     3  /* AIF3BCWK_PU */
#define WM5100_AIF3BCWK_PU_WIDTH                     1  /* AIF3BCWK_PU */
#define WM5100_AIF3BCWK_PD                      0x0004  /* AIF3BCWK_PD */
#define WM5100_AIF3BCWK_PD_MASK                 0x0004  /* AIF3BCWK_PD */
#define WM5100_AIF3BCWK_PD_SHIFT                     2  /* AIF3BCWK_PD */
#define WM5100_AIF3BCWK_PD_WIDTH                     1  /* AIF3BCWK_PD */
#define WM5100_AIF3WXDAT_PU                     0x0002  /* AIF3WXDAT_PU */
#define WM5100_AIF3WXDAT_PU_MASK                0x0002  /* AIF3WXDAT_PU */
#define WM5100_AIF3WXDAT_PU_SHIFT                    1  /* AIF3WXDAT_PU */
#define WM5100_AIF3WXDAT_PU_WIDTH                    1  /* AIF3WXDAT_PU */
#define WM5100_AIF3WXDAT_PD                     0x0001  /* AIF3WXDAT_PD */
#define WM5100_AIF3WXDAT_PD_MASK                0x0001  /* AIF3WXDAT_PD */
#define WM5100_AIF3WXDAT_PD_SHIFT                    0  /* AIF3WXDAT_PD */
#define WM5100_AIF3WXDAT_PD_WIDTH                    1  /* AIF3WXDAT_PD */

/*
 * W3112 (0xC28) - Misc GPIO 1
 */
#define WM5100_OPCWK_SEW_MASK                   0x0003  /* OPCWK_SEW - [1:0] */
#define WM5100_OPCWK_SEW_SHIFT                       0  /* OPCWK_SEW - [1:0] */
#define WM5100_OPCWK_SEW_WIDTH                       2  /* OPCWK_SEW - [1:0] */

/*
 * W3328 (0xD00) - Intewwupt Status 1
 */
#define WM5100_GP6_EINT                         0x0020  /* GP6_EINT */
#define WM5100_GP6_EINT_MASK                    0x0020  /* GP6_EINT */
#define WM5100_GP6_EINT_SHIFT                        5  /* GP6_EINT */
#define WM5100_GP6_EINT_WIDTH                        1  /* GP6_EINT */
#define WM5100_GP5_EINT                         0x0010  /* GP5_EINT */
#define WM5100_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#define WM5100_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#define WM5100_GP5_EINT_WIDTH                        1  /* GP5_EINT */
#define WM5100_GP4_EINT                         0x0008  /* GP4_EINT */
#define WM5100_GP4_EINT_MASK                    0x0008  /* GP4_EINT */
#define WM5100_GP4_EINT_SHIFT                        3  /* GP4_EINT */
#define WM5100_GP4_EINT_WIDTH                        1  /* GP4_EINT */
#define WM5100_GP3_EINT                         0x0004  /* GP3_EINT */
#define WM5100_GP3_EINT_MASK                    0x0004  /* GP3_EINT */
#define WM5100_GP3_EINT_SHIFT                        2  /* GP3_EINT */
#define WM5100_GP3_EINT_WIDTH                        1  /* GP3_EINT */
#define WM5100_GP2_EINT                         0x0002  /* GP2_EINT */
#define WM5100_GP2_EINT_MASK                    0x0002  /* GP2_EINT */
#define WM5100_GP2_EINT_SHIFT                        1  /* GP2_EINT */
#define WM5100_GP2_EINT_WIDTH                        1  /* GP2_EINT */
#define WM5100_GP1_EINT                         0x0001  /* GP1_EINT */
#define WM5100_GP1_EINT_MASK                    0x0001  /* GP1_EINT */
#define WM5100_GP1_EINT_SHIFT                        0  /* GP1_EINT */
#define WM5100_GP1_EINT_WIDTH                        1  /* GP1_EINT */

/*
 * W3329 (0xD01) - Intewwupt Status 2
 */
#define WM5100_DSP_IWQ6_EINT                    0x0020  /* DSP_IWQ6_EINT */
#define WM5100_DSP_IWQ6_EINT_MASK               0x0020  /* DSP_IWQ6_EINT */
#define WM5100_DSP_IWQ6_EINT_SHIFT                   5  /* DSP_IWQ6_EINT */
#define WM5100_DSP_IWQ6_EINT_WIDTH                   1  /* DSP_IWQ6_EINT */
#define WM5100_DSP_IWQ5_EINT                    0x0010  /* DSP_IWQ5_EINT */
#define WM5100_DSP_IWQ5_EINT_MASK               0x0010  /* DSP_IWQ5_EINT */
#define WM5100_DSP_IWQ5_EINT_SHIFT                   4  /* DSP_IWQ5_EINT */
#define WM5100_DSP_IWQ5_EINT_WIDTH                   1  /* DSP_IWQ5_EINT */
#define WM5100_DSP_IWQ4_EINT                    0x0008  /* DSP_IWQ4_EINT */
#define WM5100_DSP_IWQ4_EINT_MASK               0x0008  /* DSP_IWQ4_EINT */
#define WM5100_DSP_IWQ4_EINT_SHIFT                   3  /* DSP_IWQ4_EINT */
#define WM5100_DSP_IWQ4_EINT_WIDTH                   1  /* DSP_IWQ4_EINT */
#define WM5100_DSP_IWQ3_EINT                    0x0004  /* DSP_IWQ3_EINT */
#define WM5100_DSP_IWQ3_EINT_MASK               0x0004  /* DSP_IWQ3_EINT */
#define WM5100_DSP_IWQ3_EINT_SHIFT                   2  /* DSP_IWQ3_EINT */
#define WM5100_DSP_IWQ3_EINT_WIDTH                   1  /* DSP_IWQ3_EINT */
#define WM5100_DSP_IWQ2_EINT                    0x0002  /* DSP_IWQ2_EINT */
#define WM5100_DSP_IWQ2_EINT_MASK               0x0002  /* DSP_IWQ2_EINT */
#define WM5100_DSP_IWQ2_EINT_SHIFT                   1  /* DSP_IWQ2_EINT */
#define WM5100_DSP_IWQ2_EINT_WIDTH                   1  /* DSP_IWQ2_EINT */
#define WM5100_DSP_IWQ1_EINT                    0x0001  /* DSP_IWQ1_EINT */
#define WM5100_DSP_IWQ1_EINT_MASK               0x0001  /* DSP_IWQ1_EINT */
#define WM5100_DSP_IWQ1_EINT_SHIFT                   0  /* DSP_IWQ1_EINT */
#define WM5100_DSP_IWQ1_EINT_WIDTH                   1  /* DSP_IWQ1_EINT */

/*
 * W3330 (0xD02) - Intewwupt Status 3
 */
#define WM5100_SPK_SHUTDOWN_WAWN_EINT           0x8000  /* SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_SPK_SHUTDOWN_WAWN_EINT_MASK      0x8000  /* SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_SPK_SHUTDOWN_WAWN_EINT_SHIFT         15  /* SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_SPK_SHUTDOWN_WAWN_EINT_WIDTH          1  /* SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_SPK_SHUTDOWN_EINT                0x4000  /* SPK_SHUTDOWN_EINT */
#define WM5100_SPK_SHUTDOWN_EINT_MASK           0x4000  /* SPK_SHUTDOWN_EINT */
#define WM5100_SPK_SHUTDOWN_EINT_SHIFT              14  /* SPK_SHUTDOWN_EINT */
#define WM5100_SPK_SHUTDOWN_EINT_WIDTH               1  /* SPK_SHUTDOWN_EINT */
#define WM5100_HPDET_EINT                       0x2000  /* HPDET_EINT */
#define WM5100_HPDET_EINT_MASK                  0x2000  /* HPDET_EINT */
#define WM5100_HPDET_EINT_SHIFT                     13  /* HPDET_EINT */
#define WM5100_HPDET_EINT_WIDTH                      1  /* HPDET_EINT */
#define WM5100_ACCDET_EINT                      0x1000  /* ACCDET_EINT */
#define WM5100_ACCDET_EINT_MASK                 0x1000  /* ACCDET_EINT */
#define WM5100_ACCDET_EINT_SHIFT                    12  /* ACCDET_EINT */
#define WM5100_ACCDET_EINT_WIDTH                     1  /* ACCDET_EINT */
#define WM5100_DWC_SIG_DET_EINT                 0x0200  /* DWC_SIG_DET_EINT */
#define WM5100_DWC_SIG_DET_EINT_MASK            0x0200  /* DWC_SIG_DET_EINT */
#define WM5100_DWC_SIG_DET_EINT_SHIFT                9  /* DWC_SIG_DET_EINT */
#define WM5100_DWC_SIG_DET_EINT_WIDTH                1  /* DWC_SIG_DET_EINT */
#define WM5100_ASWC2_WOCK_EINT                  0x0100  /* ASWC2_WOCK_EINT */
#define WM5100_ASWC2_WOCK_EINT_MASK             0x0100  /* ASWC2_WOCK_EINT */
#define WM5100_ASWC2_WOCK_EINT_SHIFT                 8  /* ASWC2_WOCK_EINT */
#define WM5100_ASWC2_WOCK_EINT_WIDTH                 1  /* ASWC2_WOCK_EINT */
#define WM5100_ASWC1_WOCK_EINT                  0x0080  /* ASWC1_WOCK_EINT */
#define WM5100_ASWC1_WOCK_EINT_MASK             0x0080  /* ASWC1_WOCK_EINT */
#define WM5100_ASWC1_WOCK_EINT_SHIFT                 7  /* ASWC1_WOCK_EINT */
#define WM5100_ASWC1_WOCK_EINT_WIDTH                 1  /* ASWC1_WOCK_EINT */
#define WM5100_FWW2_WOCK_EINT                   0x0008  /* FWW2_WOCK_EINT */
#define WM5100_FWW2_WOCK_EINT_MASK              0x0008  /* FWW2_WOCK_EINT */
#define WM5100_FWW2_WOCK_EINT_SHIFT                  3  /* FWW2_WOCK_EINT */
#define WM5100_FWW2_WOCK_EINT_WIDTH                  1  /* FWW2_WOCK_EINT */
#define WM5100_FWW1_WOCK_EINT                   0x0004  /* FWW1_WOCK_EINT */
#define WM5100_FWW1_WOCK_EINT_MASK              0x0004  /* FWW1_WOCK_EINT */
#define WM5100_FWW1_WOCK_EINT_SHIFT                  2  /* FWW1_WOCK_EINT */
#define WM5100_FWW1_WOCK_EINT_WIDTH                  1  /* FWW1_WOCK_EINT */
#define WM5100_CWKGEN_EWW_EINT                  0x0002  /* CWKGEN_EWW_EINT */
#define WM5100_CWKGEN_EWW_EINT_MASK             0x0002  /* CWKGEN_EWW_EINT */
#define WM5100_CWKGEN_EWW_EINT_SHIFT                 1  /* CWKGEN_EWW_EINT */
#define WM5100_CWKGEN_EWW_EINT_WIDTH                 1  /* CWKGEN_EWW_EINT */
#define WM5100_CWKGEN_EWW_ASYNC_EINT            0x0001  /* CWKGEN_EWW_ASYNC_EINT */
#define WM5100_CWKGEN_EWW_ASYNC_EINT_MASK       0x0001  /* CWKGEN_EWW_ASYNC_EINT */
#define WM5100_CWKGEN_EWW_ASYNC_EINT_SHIFT           0  /* CWKGEN_EWW_ASYNC_EINT */
#define WM5100_CWKGEN_EWW_ASYNC_EINT_WIDTH           1  /* CWKGEN_EWW_ASYNC_EINT */

/*
 * W3331 (0xD03) - Intewwupt Status 4
 */
#define WM5100_AIF3_EWW_EINT                    0x2000  /* AIF3_EWW_EINT */
#define WM5100_AIF3_EWW_EINT_MASK               0x2000  /* AIF3_EWW_EINT */
#define WM5100_AIF3_EWW_EINT_SHIFT                  13  /* AIF3_EWW_EINT */
#define WM5100_AIF3_EWW_EINT_WIDTH                   1  /* AIF3_EWW_EINT */
#define WM5100_AIF2_EWW_EINT                    0x1000  /* AIF2_EWW_EINT */
#define WM5100_AIF2_EWW_EINT_MASK               0x1000  /* AIF2_EWW_EINT */
#define WM5100_AIF2_EWW_EINT_SHIFT                  12  /* AIF2_EWW_EINT */
#define WM5100_AIF2_EWW_EINT_WIDTH                   1  /* AIF2_EWW_EINT */
#define WM5100_AIF1_EWW_EINT                    0x0800  /* AIF1_EWW_EINT */
#define WM5100_AIF1_EWW_EINT_MASK               0x0800  /* AIF1_EWW_EINT */
#define WM5100_AIF1_EWW_EINT_SHIFT                  11  /* AIF1_EWW_EINT */
#define WM5100_AIF1_EWW_EINT_WIDTH                   1  /* AIF1_EWW_EINT */
#define WM5100_CTWWIF_EWW_EINT                  0x0400  /* CTWWIF_EWW_EINT */
#define WM5100_CTWWIF_EWW_EINT_MASK             0x0400  /* CTWWIF_EWW_EINT */
#define WM5100_CTWWIF_EWW_EINT_SHIFT                10  /* CTWWIF_EWW_EINT */
#define WM5100_CTWWIF_EWW_EINT_WIDTH                 1  /* CTWWIF_EWW_EINT */
#define WM5100_ISWC2_UNDEWCWOCKED_EINT          0x0200  /* ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_ISWC2_UNDEWCWOCKED_EINT_MASK     0x0200  /* ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_ISWC2_UNDEWCWOCKED_EINT_SHIFT         9  /* ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_ISWC2_UNDEWCWOCKED_EINT_WIDTH         1  /* ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_ISWC1_UNDEWCWOCKED_EINT          0x0100  /* ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_ISWC1_UNDEWCWOCKED_EINT_MASK     0x0100  /* ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_ISWC1_UNDEWCWOCKED_EINT_SHIFT         8  /* ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_ISWC1_UNDEWCWOCKED_EINT_WIDTH         1  /* ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_FX_UNDEWCWOCKED_EINT             0x0080  /* FX_UNDEWCWOCKED_EINT */
#define WM5100_FX_UNDEWCWOCKED_EINT_MASK        0x0080  /* FX_UNDEWCWOCKED_EINT */
#define WM5100_FX_UNDEWCWOCKED_EINT_SHIFT            7  /* FX_UNDEWCWOCKED_EINT */
#define WM5100_FX_UNDEWCWOCKED_EINT_WIDTH            1  /* FX_UNDEWCWOCKED_EINT */
#define WM5100_AIF3_UNDEWCWOCKED_EINT           0x0040  /* AIF3_UNDEWCWOCKED_EINT */
#define WM5100_AIF3_UNDEWCWOCKED_EINT_MASK      0x0040  /* AIF3_UNDEWCWOCKED_EINT */
#define WM5100_AIF3_UNDEWCWOCKED_EINT_SHIFT          6  /* AIF3_UNDEWCWOCKED_EINT */
#define WM5100_AIF3_UNDEWCWOCKED_EINT_WIDTH          1  /* AIF3_UNDEWCWOCKED_EINT */
#define WM5100_AIF2_UNDEWCWOCKED_EINT           0x0020  /* AIF2_UNDEWCWOCKED_EINT */
#define WM5100_AIF2_UNDEWCWOCKED_EINT_MASK      0x0020  /* AIF2_UNDEWCWOCKED_EINT */
#define WM5100_AIF2_UNDEWCWOCKED_EINT_SHIFT          5  /* AIF2_UNDEWCWOCKED_EINT */
#define WM5100_AIF2_UNDEWCWOCKED_EINT_WIDTH          1  /* AIF2_UNDEWCWOCKED_EINT */
#define WM5100_AIF1_UNDEWCWOCKED_EINT           0x0010  /* AIF1_UNDEWCWOCKED_EINT */
#define WM5100_AIF1_UNDEWCWOCKED_EINT_MASK      0x0010  /* AIF1_UNDEWCWOCKED_EINT */
#define WM5100_AIF1_UNDEWCWOCKED_EINT_SHIFT          4  /* AIF1_UNDEWCWOCKED_EINT */
#define WM5100_AIF1_UNDEWCWOCKED_EINT_WIDTH          1  /* AIF1_UNDEWCWOCKED_EINT */
#define WM5100_ASWC_UNDEWCWOCKED_EINT           0x0008  /* ASWC_UNDEWCWOCKED_EINT */
#define WM5100_ASWC_UNDEWCWOCKED_EINT_MASK      0x0008  /* ASWC_UNDEWCWOCKED_EINT */
#define WM5100_ASWC_UNDEWCWOCKED_EINT_SHIFT          3  /* ASWC_UNDEWCWOCKED_EINT */
#define WM5100_ASWC_UNDEWCWOCKED_EINT_WIDTH          1  /* ASWC_UNDEWCWOCKED_EINT */
#define WM5100_DAC_UNDEWCWOCKED_EINT            0x0004  /* DAC_UNDEWCWOCKED_EINT */
#define WM5100_DAC_UNDEWCWOCKED_EINT_MASK       0x0004  /* DAC_UNDEWCWOCKED_EINT */
#define WM5100_DAC_UNDEWCWOCKED_EINT_SHIFT           2  /* DAC_UNDEWCWOCKED_EINT */
#define WM5100_DAC_UNDEWCWOCKED_EINT_WIDTH           1  /* DAC_UNDEWCWOCKED_EINT */
#define WM5100_ADC_UNDEWCWOCKED_EINT            0x0002  /* ADC_UNDEWCWOCKED_EINT */
#define WM5100_ADC_UNDEWCWOCKED_EINT_MASK       0x0002  /* ADC_UNDEWCWOCKED_EINT */
#define WM5100_ADC_UNDEWCWOCKED_EINT_SHIFT           1  /* ADC_UNDEWCWOCKED_EINT */
#define WM5100_ADC_UNDEWCWOCKED_EINT_WIDTH           1  /* ADC_UNDEWCWOCKED_EINT */
#define WM5100_MIXEW_UNDEWCWOCKED_EINT          0x0001  /* MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_MIXEW_UNDEWCWOCKED_EINT_MASK     0x0001  /* MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_MIXEW_UNDEWCWOCKED_EINT_SHIFT         0  /* MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_MIXEW_UNDEWCWOCKED_EINT_WIDTH         1  /* MIXEW_UNDEWCWOCKED_EINT */

/*
 * W3332 (0xD04) - Intewwupt Waw Status 2
 */
#define WM5100_DSP_IWQ6_STS                     0x0020  /* DSP_IWQ6_STS */
#define WM5100_DSP_IWQ6_STS_MASK                0x0020  /* DSP_IWQ6_STS */
#define WM5100_DSP_IWQ6_STS_SHIFT                    5  /* DSP_IWQ6_STS */
#define WM5100_DSP_IWQ6_STS_WIDTH                    1  /* DSP_IWQ6_STS */
#define WM5100_DSP_IWQ5_STS                     0x0010  /* DSP_IWQ5_STS */
#define WM5100_DSP_IWQ5_STS_MASK                0x0010  /* DSP_IWQ5_STS */
#define WM5100_DSP_IWQ5_STS_SHIFT                    4  /* DSP_IWQ5_STS */
#define WM5100_DSP_IWQ5_STS_WIDTH                    1  /* DSP_IWQ5_STS */
#define WM5100_DSP_IWQ4_STS                     0x0008  /* DSP_IWQ4_STS */
#define WM5100_DSP_IWQ4_STS_MASK                0x0008  /* DSP_IWQ4_STS */
#define WM5100_DSP_IWQ4_STS_SHIFT                    3  /* DSP_IWQ4_STS */
#define WM5100_DSP_IWQ4_STS_WIDTH                    1  /* DSP_IWQ4_STS */
#define WM5100_DSP_IWQ3_STS                     0x0004  /* DSP_IWQ3_STS */
#define WM5100_DSP_IWQ3_STS_MASK                0x0004  /* DSP_IWQ3_STS */
#define WM5100_DSP_IWQ3_STS_SHIFT                    2  /* DSP_IWQ3_STS */
#define WM5100_DSP_IWQ3_STS_WIDTH                    1  /* DSP_IWQ3_STS */
#define WM5100_DSP_IWQ2_STS                     0x0002  /* DSP_IWQ2_STS */
#define WM5100_DSP_IWQ2_STS_MASK                0x0002  /* DSP_IWQ2_STS */
#define WM5100_DSP_IWQ2_STS_SHIFT                    1  /* DSP_IWQ2_STS */
#define WM5100_DSP_IWQ2_STS_WIDTH                    1  /* DSP_IWQ2_STS */
#define WM5100_DSP_IWQ1_STS                     0x0001  /* DSP_IWQ1_STS */
#define WM5100_DSP_IWQ1_STS_MASK                0x0001  /* DSP_IWQ1_STS */
#define WM5100_DSP_IWQ1_STS_SHIFT                    0  /* DSP_IWQ1_STS */
#define WM5100_DSP_IWQ1_STS_WIDTH                    1  /* DSP_IWQ1_STS */

/*
 * W3333 (0xD05) - Intewwupt Waw Status 3
 */
#define WM5100_SPK_SHUTDOWN_WAWN_STS            0x8000  /* SPK_SHUTDOWN_WAWN_STS */
#define WM5100_SPK_SHUTDOWN_WAWN_STS_MASK       0x8000  /* SPK_SHUTDOWN_WAWN_STS */
#define WM5100_SPK_SHUTDOWN_WAWN_STS_SHIFT          15  /* SPK_SHUTDOWN_WAWN_STS */
#define WM5100_SPK_SHUTDOWN_WAWN_STS_WIDTH           1  /* SPK_SHUTDOWN_WAWN_STS */
#define WM5100_SPK_SHUTDOWN_STS                 0x4000  /* SPK_SHUTDOWN_STS */
#define WM5100_SPK_SHUTDOWN_STS_MASK            0x4000  /* SPK_SHUTDOWN_STS */
#define WM5100_SPK_SHUTDOWN_STS_SHIFT               14  /* SPK_SHUTDOWN_STS */
#define WM5100_SPK_SHUTDOWN_STS_WIDTH                1  /* SPK_SHUTDOWN_STS */
#define WM5100_HPDET_STS                        0x2000  /* HPDET_STS */
#define WM5100_HPDET_STS_MASK                   0x2000  /* HPDET_STS */
#define WM5100_HPDET_STS_SHIFT                      13  /* HPDET_STS */
#define WM5100_HPDET_STS_WIDTH                       1  /* HPDET_STS */
#define WM5100_DWC_SID_DET_STS                  0x0200  /* DWC_SID_DET_STS */
#define WM5100_DWC_SID_DET_STS_MASK             0x0200  /* DWC_SID_DET_STS */
#define WM5100_DWC_SID_DET_STS_SHIFT                 9  /* DWC_SID_DET_STS */
#define WM5100_DWC_SID_DET_STS_WIDTH                 1  /* DWC_SID_DET_STS */
#define WM5100_ASWC2_WOCK_STS                   0x0100  /* ASWC2_WOCK_STS */
#define WM5100_ASWC2_WOCK_STS_MASK              0x0100  /* ASWC2_WOCK_STS */
#define WM5100_ASWC2_WOCK_STS_SHIFT                  8  /* ASWC2_WOCK_STS */
#define WM5100_ASWC2_WOCK_STS_WIDTH                  1  /* ASWC2_WOCK_STS */
#define WM5100_ASWC1_WOCK_STS                   0x0080  /* ASWC1_WOCK_STS */
#define WM5100_ASWC1_WOCK_STS_MASK              0x0080  /* ASWC1_WOCK_STS */
#define WM5100_ASWC1_WOCK_STS_SHIFT                  7  /* ASWC1_WOCK_STS */
#define WM5100_ASWC1_WOCK_STS_WIDTH                  1  /* ASWC1_WOCK_STS */
#define WM5100_FWW2_WOCK_STS                    0x0008  /* FWW2_WOCK_STS */
#define WM5100_FWW2_WOCK_STS_MASK               0x0008  /* FWW2_WOCK_STS */
#define WM5100_FWW2_WOCK_STS_SHIFT                   3  /* FWW2_WOCK_STS */
#define WM5100_FWW2_WOCK_STS_WIDTH                   1  /* FWW2_WOCK_STS */
#define WM5100_FWW1_WOCK_STS                    0x0004  /* FWW1_WOCK_STS */
#define WM5100_FWW1_WOCK_STS_MASK               0x0004  /* FWW1_WOCK_STS */
#define WM5100_FWW1_WOCK_STS_SHIFT                   2  /* FWW1_WOCK_STS */
#define WM5100_FWW1_WOCK_STS_WIDTH                   1  /* FWW1_WOCK_STS */
#define WM5100_CWKGEN_EWW_STS                   0x0002  /* CWKGEN_EWW_STS */
#define WM5100_CWKGEN_EWW_STS_MASK              0x0002  /* CWKGEN_EWW_STS */
#define WM5100_CWKGEN_EWW_STS_SHIFT                  1  /* CWKGEN_EWW_STS */
#define WM5100_CWKGEN_EWW_STS_WIDTH                  1  /* CWKGEN_EWW_STS */
#define WM5100_CWKGEN_EWW_ASYNC_STS             0x0001  /* CWKGEN_EWW_ASYNC_STS */
#define WM5100_CWKGEN_EWW_ASYNC_STS_MASK        0x0001  /* CWKGEN_EWW_ASYNC_STS */
#define WM5100_CWKGEN_EWW_ASYNC_STS_SHIFT            0  /* CWKGEN_EWW_ASYNC_STS */
#define WM5100_CWKGEN_EWW_ASYNC_STS_WIDTH            1  /* CWKGEN_EWW_ASYNC_STS */

/*
 * W3334 (0xD06) - Intewwupt Waw Status 4
 */
#define WM5100_AIF3_EWW_STS                     0x2000  /* AIF3_EWW_STS */
#define WM5100_AIF3_EWW_STS_MASK                0x2000  /* AIF3_EWW_STS */
#define WM5100_AIF3_EWW_STS_SHIFT                   13  /* AIF3_EWW_STS */
#define WM5100_AIF3_EWW_STS_WIDTH                    1  /* AIF3_EWW_STS */
#define WM5100_AIF2_EWW_STS                     0x1000  /* AIF2_EWW_STS */
#define WM5100_AIF2_EWW_STS_MASK                0x1000  /* AIF2_EWW_STS */
#define WM5100_AIF2_EWW_STS_SHIFT                   12  /* AIF2_EWW_STS */
#define WM5100_AIF2_EWW_STS_WIDTH                    1  /* AIF2_EWW_STS */
#define WM5100_AIF1_EWW_STS                     0x0800  /* AIF1_EWW_STS */
#define WM5100_AIF1_EWW_STS_MASK                0x0800  /* AIF1_EWW_STS */
#define WM5100_AIF1_EWW_STS_SHIFT                   11  /* AIF1_EWW_STS */
#define WM5100_AIF1_EWW_STS_WIDTH                    1  /* AIF1_EWW_STS */
#define WM5100_CTWWIF_EWW_STS                   0x0400  /* CTWWIF_EWW_STS */
#define WM5100_CTWWIF_EWW_STS_MASK              0x0400  /* CTWWIF_EWW_STS */
#define WM5100_CTWWIF_EWW_STS_SHIFT                 10  /* CTWWIF_EWW_STS */
#define WM5100_CTWWIF_EWW_STS_WIDTH                  1  /* CTWWIF_EWW_STS */
#define WM5100_ISWC2_UNDEWCWOCKED_STS           0x0200  /* ISWC2_UNDEWCWOCKED_STS */
#define WM5100_ISWC2_UNDEWCWOCKED_STS_MASK      0x0200  /* ISWC2_UNDEWCWOCKED_STS */
#define WM5100_ISWC2_UNDEWCWOCKED_STS_SHIFT          9  /* ISWC2_UNDEWCWOCKED_STS */
#define WM5100_ISWC2_UNDEWCWOCKED_STS_WIDTH          1  /* ISWC2_UNDEWCWOCKED_STS */
#define WM5100_ISWC1_UNDEWCWOCKED_STS           0x0100  /* ISWC1_UNDEWCWOCKED_STS */
#define WM5100_ISWC1_UNDEWCWOCKED_STS_MASK      0x0100  /* ISWC1_UNDEWCWOCKED_STS */
#define WM5100_ISWC1_UNDEWCWOCKED_STS_SHIFT          8  /* ISWC1_UNDEWCWOCKED_STS */
#define WM5100_ISWC1_UNDEWCWOCKED_STS_WIDTH          1  /* ISWC1_UNDEWCWOCKED_STS */
#define WM5100_FX_UNDEWCWOCKED_STS              0x0080  /* FX_UNDEWCWOCKED_STS */
#define WM5100_FX_UNDEWCWOCKED_STS_MASK         0x0080  /* FX_UNDEWCWOCKED_STS */
#define WM5100_FX_UNDEWCWOCKED_STS_SHIFT             7  /* FX_UNDEWCWOCKED_STS */
#define WM5100_FX_UNDEWCWOCKED_STS_WIDTH             1  /* FX_UNDEWCWOCKED_STS */
#define WM5100_AIF3_UNDEWCWOCKED_STS            0x0040  /* AIF3_UNDEWCWOCKED_STS */
#define WM5100_AIF3_UNDEWCWOCKED_STS_MASK       0x0040  /* AIF3_UNDEWCWOCKED_STS */
#define WM5100_AIF3_UNDEWCWOCKED_STS_SHIFT           6  /* AIF3_UNDEWCWOCKED_STS */
#define WM5100_AIF3_UNDEWCWOCKED_STS_WIDTH           1  /* AIF3_UNDEWCWOCKED_STS */
#define WM5100_AIF2_UNDEWCWOCKED_STS            0x0020  /* AIF2_UNDEWCWOCKED_STS */
#define WM5100_AIF2_UNDEWCWOCKED_STS_MASK       0x0020  /* AIF2_UNDEWCWOCKED_STS */
#define WM5100_AIF2_UNDEWCWOCKED_STS_SHIFT           5  /* AIF2_UNDEWCWOCKED_STS */
#define WM5100_AIF2_UNDEWCWOCKED_STS_WIDTH           1  /* AIF2_UNDEWCWOCKED_STS */
#define WM5100_AIF1_UNDEWCWOCKED_STS            0x0010  /* AIF1_UNDEWCWOCKED_STS */
#define WM5100_AIF1_UNDEWCWOCKED_STS_MASK       0x0010  /* AIF1_UNDEWCWOCKED_STS */
#define WM5100_AIF1_UNDEWCWOCKED_STS_SHIFT           4  /* AIF1_UNDEWCWOCKED_STS */
#define WM5100_AIF1_UNDEWCWOCKED_STS_WIDTH           1  /* AIF1_UNDEWCWOCKED_STS */
#define WM5100_ASWC_UNDEWCWOCKED_STS            0x0008  /* ASWC_UNDEWCWOCKED_STS */
#define WM5100_ASWC_UNDEWCWOCKED_STS_MASK       0x0008  /* ASWC_UNDEWCWOCKED_STS */
#define WM5100_ASWC_UNDEWCWOCKED_STS_SHIFT           3  /* ASWC_UNDEWCWOCKED_STS */
#define WM5100_ASWC_UNDEWCWOCKED_STS_WIDTH           1  /* ASWC_UNDEWCWOCKED_STS */
#define WM5100_DAC_UNDEWCWOCKED_STS             0x0004  /* DAC_UNDEWCWOCKED_STS */
#define WM5100_DAC_UNDEWCWOCKED_STS_MASK        0x0004  /* DAC_UNDEWCWOCKED_STS */
#define WM5100_DAC_UNDEWCWOCKED_STS_SHIFT            2  /* DAC_UNDEWCWOCKED_STS */
#define WM5100_DAC_UNDEWCWOCKED_STS_WIDTH            1  /* DAC_UNDEWCWOCKED_STS */
#define WM5100_ADC_UNDEWCWOCKED_STS             0x0002  /* ADC_UNDEWCWOCKED_STS */
#define WM5100_ADC_UNDEWCWOCKED_STS_MASK        0x0002  /* ADC_UNDEWCWOCKED_STS */
#define WM5100_ADC_UNDEWCWOCKED_STS_SHIFT            1  /* ADC_UNDEWCWOCKED_STS */
#define WM5100_ADC_UNDEWCWOCKED_STS_WIDTH            1  /* ADC_UNDEWCWOCKED_STS */
#define WM5100_MIXEW_UNDEWCWOCKED_STS           0x0001  /* MIXEW_UNDEWCWOCKED_STS */
#define WM5100_MIXEW_UNDEWCWOCKED_STS_MASK      0x0001  /* MIXEW_UNDEWCWOCKED_STS */
#define WM5100_MIXEW_UNDEWCWOCKED_STS_SHIFT          0  /* MIXEW_UNDEWCWOCKED_STS */
#define WM5100_MIXEW_UNDEWCWOCKED_STS_WIDTH          1  /* MIXEW_UNDEWCWOCKED_STS */

/*
 * W3335 (0xD07) - Intewwupt Status 1 Mask
 */
#define WM5100_IM_GP6_EINT                      0x0020  /* IM_GP6_EINT */
#define WM5100_IM_GP6_EINT_MASK                 0x0020  /* IM_GP6_EINT */
#define WM5100_IM_GP6_EINT_SHIFT                     5  /* IM_GP6_EINT */
#define WM5100_IM_GP6_EINT_WIDTH                     1  /* IM_GP6_EINT */
#define WM5100_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#define WM5100_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#define WM5100_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#define WM5100_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */
#define WM5100_IM_GP4_EINT                      0x0008  /* IM_GP4_EINT */
#define WM5100_IM_GP4_EINT_MASK                 0x0008  /* IM_GP4_EINT */
#define WM5100_IM_GP4_EINT_SHIFT                     3  /* IM_GP4_EINT */
#define WM5100_IM_GP4_EINT_WIDTH                     1  /* IM_GP4_EINT */
#define WM5100_IM_GP3_EINT                      0x0004  /* IM_GP3_EINT */
#define WM5100_IM_GP3_EINT_MASK                 0x0004  /* IM_GP3_EINT */
#define WM5100_IM_GP3_EINT_SHIFT                     2  /* IM_GP3_EINT */
#define WM5100_IM_GP3_EINT_WIDTH                     1  /* IM_GP3_EINT */
#define WM5100_IM_GP2_EINT                      0x0002  /* IM_GP2_EINT */
#define WM5100_IM_GP2_EINT_MASK                 0x0002  /* IM_GP2_EINT */
#define WM5100_IM_GP2_EINT_SHIFT                     1  /* IM_GP2_EINT */
#define WM5100_IM_GP2_EINT_WIDTH                     1  /* IM_GP2_EINT */
#define WM5100_IM_GP1_EINT                      0x0001  /* IM_GP1_EINT */
#define WM5100_IM_GP1_EINT_MASK                 0x0001  /* IM_GP1_EINT */
#define WM5100_IM_GP1_EINT_SHIFT                     0  /* IM_GP1_EINT */
#define WM5100_IM_GP1_EINT_WIDTH                     1  /* IM_GP1_EINT */

/*
 * W3336 (0xD08) - Intewwupt Status 2 Mask
 */
#define WM5100_IM_DSP_IWQ6_EINT                 0x0020  /* IM_DSP_IWQ6_EINT */
#define WM5100_IM_DSP_IWQ6_EINT_MASK            0x0020  /* IM_DSP_IWQ6_EINT */
#define WM5100_IM_DSP_IWQ6_EINT_SHIFT                5  /* IM_DSP_IWQ6_EINT */
#define WM5100_IM_DSP_IWQ6_EINT_WIDTH                1  /* IM_DSP_IWQ6_EINT */
#define WM5100_IM_DSP_IWQ5_EINT                 0x0010  /* IM_DSP_IWQ5_EINT */
#define WM5100_IM_DSP_IWQ5_EINT_MASK            0x0010  /* IM_DSP_IWQ5_EINT */
#define WM5100_IM_DSP_IWQ5_EINT_SHIFT                4  /* IM_DSP_IWQ5_EINT */
#define WM5100_IM_DSP_IWQ5_EINT_WIDTH                1  /* IM_DSP_IWQ5_EINT */
#define WM5100_IM_DSP_IWQ4_EINT                 0x0008  /* IM_DSP_IWQ4_EINT */
#define WM5100_IM_DSP_IWQ4_EINT_MASK            0x0008  /* IM_DSP_IWQ4_EINT */
#define WM5100_IM_DSP_IWQ4_EINT_SHIFT                3  /* IM_DSP_IWQ4_EINT */
#define WM5100_IM_DSP_IWQ4_EINT_WIDTH                1  /* IM_DSP_IWQ4_EINT */
#define WM5100_IM_DSP_IWQ3_EINT                 0x0004  /* IM_DSP_IWQ3_EINT */
#define WM5100_IM_DSP_IWQ3_EINT_MASK            0x0004  /* IM_DSP_IWQ3_EINT */
#define WM5100_IM_DSP_IWQ3_EINT_SHIFT                2  /* IM_DSP_IWQ3_EINT */
#define WM5100_IM_DSP_IWQ3_EINT_WIDTH                1  /* IM_DSP_IWQ3_EINT */
#define WM5100_IM_DSP_IWQ2_EINT                 0x0002  /* IM_DSP_IWQ2_EINT */
#define WM5100_IM_DSP_IWQ2_EINT_MASK            0x0002  /* IM_DSP_IWQ2_EINT */
#define WM5100_IM_DSP_IWQ2_EINT_SHIFT                1  /* IM_DSP_IWQ2_EINT */
#define WM5100_IM_DSP_IWQ2_EINT_WIDTH                1  /* IM_DSP_IWQ2_EINT */
#define WM5100_IM_DSP_IWQ1_EINT                 0x0001  /* IM_DSP_IWQ1_EINT */
#define WM5100_IM_DSP_IWQ1_EINT_MASK            0x0001  /* IM_DSP_IWQ1_EINT */
#define WM5100_IM_DSP_IWQ1_EINT_SHIFT                0  /* IM_DSP_IWQ1_EINT */
#define WM5100_IM_DSP_IWQ1_EINT_WIDTH                1  /* IM_DSP_IWQ1_EINT */

/*
 * W3337 (0xD09) - Intewwupt Status 3 Mask
 */
#define WM5100_IM_SPK_SHUTDOWN_WAWN_EINT        0x8000  /* IM_SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_WAWN_EINT_MASK   0x8000  /* IM_SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_WAWN_EINT_SHIFT      15  /* IM_SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_WAWN_EINT_WIDTH       1  /* IM_SPK_SHUTDOWN_WAWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_EINT             0x4000  /* IM_SPK_SHUTDOWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_EINT_MASK        0x4000  /* IM_SPK_SHUTDOWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_EINT_SHIFT           14  /* IM_SPK_SHUTDOWN_EINT */
#define WM5100_IM_SPK_SHUTDOWN_EINT_WIDTH            1  /* IM_SPK_SHUTDOWN_EINT */
#define WM5100_IM_HPDET_EINT                    0x2000  /* IM_HPDET_EINT */
#define WM5100_IM_HPDET_EINT_MASK               0x2000  /* IM_HPDET_EINT */
#define WM5100_IM_HPDET_EINT_SHIFT                  13  /* IM_HPDET_EINT */
#define WM5100_IM_HPDET_EINT_WIDTH                   1  /* IM_HPDET_EINT */
#define WM5100_IM_ACCDET_EINT                   0x1000  /* IM_ACCDET_EINT */
#define WM5100_IM_ACCDET_EINT_MASK              0x1000  /* IM_ACCDET_EINT */
#define WM5100_IM_ACCDET_EINT_SHIFT                 12  /* IM_ACCDET_EINT */
#define WM5100_IM_ACCDET_EINT_WIDTH                  1  /* IM_ACCDET_EINT */
#define WM5100_IM_DWC_SIG_DET_EINT              0x0200  /* IM_DWC_SIG_DET_EINT */
#define WM5100_IM_DWC_SIG_DET_EINT_MASK         0x0200  /* IM_DWC_SIG_DET_EINT */
#define WM5100_IM_DWC_SIG_DET_EINT_SHIFT             9  /* IM_DWC_SIG_DET_EINT */
#define WM5100_IM_DWC_SIG_DET_EINT_WIDTH             1  /* IM_DWC_SIG_DET_EINT */
#define WM5100_IM_ASWC2_WOCK_EINT               0x0100  /* IM_ASWC2_WOCK_EINT */
#define WM5100_IM_ASWC2_WOCK_EINT_MASK          0x0100  /* IM_ASWC2_WOCK_EINT */
#define WM5100_IM_ASWC2_WOCK_EINT_SHIFT              8  /* IM_ASWC2_WOCK_EINT */
#define WM5100_IM_ASWC2_WOCK_EINT_WIDTH              1  /* IM_ASWC2_WOCK_EINT */
#define WM5100_IM_ASWC1_WOCK_EINT               0x0080  /* IM_ASWC1_WOCK_EINT */
#define WM5100_IM_ASWC1_WOCK_EINT_MASK          0x0080  /* IM_ASWC1_WOCK_EINT */
#define WM5100_IM_ASWC1_WOCK_EINT_SHIFT              7  /* IM_ASWC1_WOCK_EINT */
#define WM5100_IM_ASWC1_WOCK_EINT_WIDTH              1  /* IM_ASWC1_WOCK_EINT */
#define WM5100_IM_FWW2_WOCK_EINT                0x0008  /* IM_FWW2_WOCK_EINT */
#define WM5100_IM_FWW2_WOCK_EINT_MASK           0x0008  /* IM_FWW2_WOCK_EINT */
#define WM5100_IM_FWW2_WOCK_EINT_SHIFT               3  /* IM_FWW2_WOCK_EINT */
#define WM5100_IM_FWW2_WOCK_EINT_WIDTH               1  /* IM_FWW2_WOCK_EINT */
#define WM5100_IM_FWW1_WOCK_EINT                0x0004  /* IM_FWW1_WOCK_EINT */
#define WM5100_IM_FWW1_WOCK_EINT_MASK           0x0004  /* IM_FWW1_WOCK_EINT */
#define WM5100_IM_FWW1_WOCK_EINT_SHIFT               2  /* IM_FWW1_WOCK_EINT */
#define WM5100_IM_FWW1_WOCK_EINT_WIDTH               1  /* IM_FWW1_WOCK_EINT */
#define WM5100_IM_CWKGEN_EWW_EINT               0x0002  /* IM_CWKGEN_EWW_EINT */
#define WM5100_IM_CWKGEN_EWW_EINT_MASK          0x0002  /* IM_CWKGEN_EWW_EINT */
#define WM5100_IM_CWKGEN_EWW_EINT_SHIFT              1  /* IM_CWKGEN_EWW_EINT */
#define WM5100_IM_CWKGEN_EWW_EINT_WIDTH              1  /* IM_CWKGEN_EWW_EINT */
#define WM5100_IM_CWKGEN_EWW_ASYNC_EINT         0x0001  /* IM_CWKGEN_EWW_ASYNC_EINT */
#define WM5100_IM_CWKGEN_EWW_ASYNC_EINT_MASK    0x0001  /* IM_CWKGEN_EWW_ASYNC_EINT */
#define WM5100_IM_CWKGEN_EWW_ASYNC_EINT_SHIFT        0  /* IM_CWKGEN_EWW_ASYNC_EINT */
#define WM5100_IM_CWKGEN_EWW_ASYNC_EINT_WIDTH        1  /* IM_CWKGEN_EWW_ASYNC_EINT */

/*
 * W3338 (0xD0A) - Intewwupt Status 4 Mask
 */
#define WM5100_IM_AIF3_EWW_EINT                 0x2000  /* IM_AIF3_EWW_EINT */
#define WM5100_IM_AIF3_EWW_EINT_MASK            0x2000  /* IM_AIF3_EWW_EINT */
#define WM5100_IM_AIF3_EWW_EINT_SHIFT               13  /* IM_AIF3_EWW_EINT */
#define WM5100_IM_AIF3_EWW_EINT_WIDTH                1  /* IM_AIF3_EWW_EINT */
#define WM5100_IM_AIF2_EWW_EINT                 0x1000  /* IM_AIF2_EWW_EINT */
#define WM5100_IM_AIF2_EWW_EINT_MASK            0x1000  /* IM_AIF2_EWW_EINT */
#define WM5100_IM_AIF2_EWW_EINT_SHIFT               12  /* IM_AIF2_EWW_EINT */
#define WM5100_IM_AIF2_EWW_EINT_WIDTH                1  /* IM_AIF2_EWW_EINT */
#define WM5100_IM_AIF1_EWW_EINT                 0x0800  /* IM_AIF1_EWW_EINT */
#define WM5100_IM_AIF1_EWW_EINT_MASK            0x0800  /* IM_AIF1_EWW_EINT */
#define WM5100_IM_AIF1_EWW_EINT_SHIFT               11  /* IM_AIF1_EWW_EINT */
#define WM5100_IM_AIF1_EWW_EINT_WIDTH                1  /* IM_AIF1_EWW_EINT */
#define WM5100_IM_CTWWIF_EWW_EINT               0x0400  /* IM_CTWWIF_EWW_EINT */
#define WM5100_IM_CTWWIF_EWW_EINT_MASK          0x0400  /* IM_CTWWIF_EWW_EINT */
#define WM5100_IM_CTWWIF_EWW_EINT_SHIFT             10  /* IM_CTWWIF_EWW_EINT */
#define WM5100_IM_CTWWIF_EWW_EINT_WIDTH              1  /* IM_CTWWIF_EWW_EINT */
#define WM5100_IM_ISWC2_UNDEWCWOCKED_EINT       0x0200  /* IM_ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC2_UNDEWCWOCKED_EINT_MASK  0x0200  /* IM_ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC2_UNDEWCWOCKED_EINT_SHIFT      9  /* IM_ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC2_UNDEWCWOCKED_EINT_WIDTH      1  /* IM_ISWC2_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC1_UNDEWCWOCKED_EINT       0x0100  /* IM_ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC1_UNDEWCWOCKED_EINT_MASK  0x0100  /* IM_ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC1_UNDEWCWOCKED_EINT_SHIFT      8  /* IM_ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_IM_ISWC1_UNDEWCWOCKED_EINT_WIDTH      1  /* IM_ISWC1_UNDEWCWOCKED_EINT */
#define WM5100_IM_FX_UNDEWCWOCKED_EINT          0x0080  /* IM_FX_UNDEWCWOCKED_EINT */
#define WM5100_IM_FX_UNDEWCWOCKED_EINT_MASK     0x0080  /* IM_FX_UNDEWCWOCKED_EINT */
#define WM5100_IM_FX_UNDEWCWOCKED_EINT_SHIFT         7  /* IM_FX_UNDEWCWOCKED_EINT */
#define WM5100_IM_FX_UNDEWCWOCKED_EINT_WIDTH         1  /* IM_FX_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF3_UNDEWCWOCKED_EINT        0x0040  /* IM_AIF3_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF3_UNDEWCWOCKED_EINT_MASK   0x0040  /* IM_AIF3_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF3_UNDEWCWOCKED_EINT_SHIFT       6  /* IM_AIF3_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF3_UNDEWCWOCKED_EINT_WIDTH       1  /* IM_AIF3_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF2_UNDEWCWOCKED_EINT        0x0020  /* IM_AIF2_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF2_UNDEWCWOCKED_EINT_MASK   0x0020  /* IM_AIF2_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF2_UNDEWCWOCKED_EINT_SHIFT       5  /* IM_AIF2_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF2_UNDEWCWOCKED_EINT_WIDTH       1  /* IM_AIF2_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF1_UNDEWCWOCKED_EINT        0x0010  /* IM_AIF1_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF1_UNDEWCWOCKED_EINT_MASK   0x0010  /* IM_AIF1_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF1_UNDEWCWOCKED_EINT_SHIFT       4  /* IM_AIF1_UNDEWCWOCKED_EINT */
#define WM5100_IM_AIF1_UNDEWCWOCKED_EINT_WIDTH       1  /* IM_AIF1_UNDEWCWOCKED_EINT */
#define WM5100_IM_ASWC_UNDEWCWOCKED_EINT        0x0008  /* IM_ASWC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ASWC_UNDEWCWOCKED_EINT_MASK   0x0008  /* IM_ASWC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ASWC_UNDEWCWOCKED_EINT_SHIFT       3  /* IM_ASWC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ASWC_UNDEWCWOCKED_EINT_WIDTH       1  /* IM_ASWC_UNDEWCWOCKED_EINT */
#define WM5100_IM_DAC_UNDEWCWOCKED_EINT         0x0004  /* IM_DAC_UNDEWCWOCKED_EINT */
#define WM5100_IM_DAC_UNDEWCWOCKED_EINT_MASK    0x0004  /* IM_DAC_UNDEWCWOCKED_EINT */
#define WM5100_IM_DAC_UNDEWCWOCKED_EINT_SHIFT        2  /* IM_DAC_UNDEWCWOCKED_EINT */
#define WM5100_IM_DAC_UNDEWCWOCKED_EINT_WIDTH        1  /* IM_DAC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ADC_UNDEWCWOCKED_EINT         0x0002  /* IM_ADC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ADC_UNDEWCWOCKED_EINT_MASK    0x0002  /* IM_ADC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ADC_UNDEWCWOCKED_EINT_SHIFT        1  /* IM_ADC_UNDEWCWOCKED_EINT */
#define WM5100_IM_ADC_UNDEWCWOCKED_EINT_WIDTH        1  /* IM_ADC_UNDEWCWOCKED_EINT */
#define WM5100_IM_MIXEW_UNDEWCWOCKED_EINT       0x0001  /* IM_MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_IM_MIXEW_UNDEWCWOCKED_EINT_MASK  0x0001  /* IM_MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_IM_MIXEW_UNDEWCWOCKED_EINT_SHIFT      0  /* IM_MIXEW_UNDEWCWOCKED_EINT */
#define WM5100_IM_MIXEW_UNDEWCWOCKED_EINT_WIDTH      1  /* IM_MIXEW_UNDEWCWOCKED_EINT */

/*
 * W3359 (0xD1F) - Intewwupt Contwow
 */
#define WM5100_IM_IWQ                           0x0001  /* IM_IWQ */
#define WM5100_IM_IWQ_MASK                      0x0001  /* IM_IWQ */
#define WM5100_IM_IWQ_SHIFT                          0  /* IM_IWQ */
#define WM5100_IM_IWQ_WIDTH                          1  /* IM_IWQ */

/*
 * W3360 (0xD20) - IWQ Debounce 1
 */
#define WM5100_SPK_SHUTDOWN_WAWN_DB             0x0200  /* SPK_SHUTDOWN_WAWN_DB */
#define WM5100_SPK_SHUTDOWN_WAWN_DB_MASK        0x0200  /* SPK_SHUTDOWN_WAWN_DB */
#define WM5100_SPK_SHUTDOWN_WAWN_DB_SHIFT            9  /* SPK_SHUTDOWN_WAWN_DB */
#define WM5100_SPK_SHUTDOWN_WAWN_DB_WIDTH            1  /* SPK_SHUTDOWN_WAWN_DB */
#define WM5100_SPK_SHUTDOWN_DB                  0x0100  /* SPK_SHUTDOWN_DB */
#define WM5100_SPK_SHUTDOWN_DB_MASK             0x0100  /* SPK_SHUTDOWN_DB */
#define WM5100_SPK_SHUTDOWN_DB_SHIFT                 8  /* SPK_SHUTDOWN_DB */
#define WM5100_SPK_SHUTDOWN_DB_WIDTH                 1  /* SPK_SHUTDOWN_DB */
#define WM5100_FWW1_WOCK_IWQ_DB                 0x0008  /* FWW1_WOCK_IWQ_DB */
#define WM5100_FWW1_WOCK_IWQ_DB_MASK            0x0008  /* FWW1_WOCK_IWQ_DB */
#define WM5100_FWW1_WOCK_IWQ_DB_SHIFT                3  /* FWW1_WOCK_IWQ_DB */
#define WM5100_FWW1_WOCK_IWQ_DB_WIDTH                1  /* FWW1_WOCK_IWQ_DB */
#define WM5100_FWW2_WOCK_IWQ_DB                 0x0004  /* FWW2_WOCK_IWQ_DB */
#define WM5100_FWW2_WOCK_IWQ_DB_MASK            0x0004  /* FWW2_WOCK_IWQ_DB */
#define WM5100_FWW2_WOCK_IWQ_DB_SHIFT                2  /* FWW2_WOCK_IWQ_DB */
#define WM5100_FWW2_WOCK_IWQ_DB_WIDTH                1  /* FWW2_WOCK_IWQ_DB */
#define WM5100_CWKGEN_EWW_IWQ_DB                0x0002  /* CWKGEN_EWW_IWQ_DB */
#define WM5100_CWKGEN_EWW_IWQ_DB_MASK           0x0002  /* CWKGEN_EWW_IWQ_DB */
#define WM5100_CWKGEN_EWW_IWQ_DB_SHIFT               1  /* CWKGEN_EWW_IWQ_DB */
#define WM5100_CWKGEN_EWW_IWQ_DB_WIDTH               1  /* CWKGEN_EWW_IWQ_DB */
#define WM5100_CWKGEN_EWW_ASYNC_IWQ_DB          0x0001  /* CWKGEN_EWW_ASYNC_IWQ_DB */
#define WM5100_CWKGEN_EWW_ASYNC_IWQ_DB_MASK     0x0001  /* CWKGEN_EWW_ASYNC_IWQ_DB */
#define WM5100_CWKGEN_EWW_ASYNC_IWQ_DB_SHIFT         0  /* CWKGEN_EWW_ASYNC_IWQ_DB */
#define WM5100_CWKGEN_EWW_ASYNC_IWQ_DB_WIDTH         1  /* CWKGEN_EWW_ASYNC_IWQ_DB */

/*
 * W3361 (0xD21) - IWQ Debounce 2
 */
#define WM5100_AIF_EWW_DB                       0x0001  /* AIF_EWW_DB */
#define WM5100_AIF_EWW_DB_MASK                  0x0001  /* AIF_EWW_DB */
#define WM5100_AIF_EWW_DB_SHIFT                      0  /* AIF_EWW_DB */
#define WM5100_AIF_EWW_DB_WIDTH                      1  /* AIF_EWW_DB */

/*
 * W3584 (0xE00) - FX_Ctww
 */
#define WM5100_FX_STS_MASK                      0xFFC0  /* FX_STS - [15:6] */
#define WM5100_FX_STS_SHIFT                          6  /* FX_STS - [15:6] */
#define WM5100_FX_STS_WIDTH                         10  /* FX_STS - [15:6] */
#define WM5100_FX_WATE_MASK                     0x0003  /* FX_WATE - [1:0] */
#define WM5100_FX_WATE_SHIFT                         0  /* FX_WATE - [1:0] */
#define WM5100_FX_WATE_WIDTH                         2  /* FX_WATE - [1:0] */

/*
 * W3600 (0xE10) - EQ1_1
 */
#define WM5100_EQ1_B1_GAIN_MASK                 0xF800  /* EQ1_B1_GAIN - [15:11] */
#define WM5100_EQ1_B1_GAIN_SHIFT                    11  /* EQ1_B1_GAIN - [15:11] */
#define WM5100_EQ1_B1_GAIN_WIDTH                     5  /* EQ1_B1_GAIN - [15:11] */
#define WM5100_EQ1_B2_GAIN_MASK                 0x07C0  /* EQ1_B2_GAIN - [10:6] */
#define WM5100_EQ1_B2_GAIN_SHIFT                     6  /* EQ1_B2_GAIN - [10:6] */
#define WM5100_EQ1_B2_GAIN_WIDTH                     5  /* EQ1_B2_GAIN - [10:6] */
#define WM5100_EQ1_B3_GAIN_MASK                 0x003E  /* EQ1_B3_GAIN - [5:1] */
#define WM5100_EQ1_B3_GAIN_SHIFT                     1  /* EQ1_B3_GAIN - [5:1] */
#define WM5100_EQ1_B3_GAIN_WIDTH                     5  /* EQ1_B3_GAIN - [5:1] */
#define WM5100_EQ1_ENA                          0x0001  /* EQ1_ENA */
#define WM5100_EQ1_ENA_MASK                     0x0001  /* EQ1_ENA */
#define WM5100_EQ1_ENA_SHIFT                         0  /* EQ1_ENA */
#define WM5100_EQ1_ENA_WIDTH                         1  /* EQ1_ENA */

/*
 * W3601 (0xE11) - EQ1_2
 */
#define WM5100_EQ1_B4_GAIN_MASK                 0xF800  /* EQ1_B4_GAIN - [15:11] */
#define WM5100_EQ1_B4_GAIN_SHIFT                    11  /* EQ1_B4_GAIN - [15:11] */
#define WM5100_EQ1_B4_GAIN_WIDTH                     5  /* EQ1_B4_GAIN - [15:11] */
#define WM5100_EQ1_B5_GAIN_MASK                 0x07C0  /* EQ1_B5_GAIN - [10:6] */
#define WM5100_EQ1_B5_GAIN_SHIFT                     6  /* EQ1_B5_GAIN - [10:6] */
#define WM5100_EQ1_B5_GAIN_WIDTH                     5  /* EQ1_B5_GAIN - [10:6] */

/*
 * W3602 (0xE12) - EQ1_3
 */
#define WM5100_EQ1_B1_A_MASK                    0xFFFF  /* EQ1_B1_A - [15:0] */
#define WM5100_EQ1_B1_A_SHIFT                        0  /* EQ1_B1_A - [15:0] */
#define WM5100_EQ1_B1_A_WIDTH                       16  /* EQ1_B1_A - [15:0] */

/*
 * W3603 (0xE13) - EQ1_4
 */
#define WM5100_EQ1_B1_B_MASK                    0xFFFF  /* EQ1_B1_B - [15:0] */
#define WM5100_EQ1_B1_B_SHIFT                        0  /* EQ1_B1_B - [15:0] */
#define WM5100_EQ1_B1_B_WIDTH                       16  /* EQ1_B1_B - [15:0] */

/*
 * W3604 (0xE14) - EQ1_5
 */
#define WM5100_EQ1_B1_PG_MASK                   0xFFFF  /* EQ1_B1_PG - [15:0] */
#define WM5100_EQ1_B1_PG_SHIFT                       0  /* EQ1_B1_PG - [15:0] */
#define WM5100_EQ1_B1_PG_WIDTH                      16  /* EQ1_B1_PG - [15:0] */

/*
 * W3605 (0xE15) - EQ1_6
 */
#define WM5100_EQ1_B2_A_MASK                    0xFFFF  /* EQ1_B2_A - [15:0] */
#define WM5100_EQ1_B2_A_SHIFT                        0  /* EQ1_B2_A - [15:0] */
#define WM5100_EQ1_B2_A_WIDTH                       16  /* EQ1_B2_A - [15:0] */

/*
 * W3606 (0xE16) - EQ1_7
 */
#define WM5100_EQ1_B2_B_MASK                    0xFFFF  /* EQ1_B2_B - [15:0] */
#define WM5100_EQ1_B2_B_SHIFT                        0  /* EQ1_B2_B - [15:0] */
#define WM5100_EQ1_B2_B_WIDTH                       16  /* EQ1_B2_B - [15:0] */

/*
 * W3607 (0xE17) - EQ1_8
 */
#define WM5100_EQ1_B2_C_MASK                    0xFFFF  /* EQ1_B2_C - [15:0] */
#define WM5100_EQ1_B2_C_SHIFT                        0  /* EQ1_B2_C - [15:0] */
#define WM5100_EQ1_B2_C_WIDTH                       16  /* EQ1_B2_C - [15:0] */

/*
 * W3608 (0xE18) - EQ1_9
 */
#define WM5100_EQ1_B2_PG_MASK                   0xFFFF  /* EQ1_B2_PG - [15:0] */
#define WM5100_EQ1_B2_PG_SHIFT                       0  /* EQ1_B2_PG - [15:0] */
#define WM5100_EQ1_B2_PG_WIDTH                      16  /* EQ1_B2_PG - [15:0] */

/*
 * W3609 (0xE19) - EQ1_10
 */
#define WM5100_EQ1_B3_A_MASK                    0xFFFF  /* EQ1_B3_A - [15:0] */
#define WM5100_EQ1_B3_A_SHIFT                        0  /* EQ1_B3_A - [15:0] */
#define WM5100_EQ1_B3_A_WIDTH                       16  /* EQ1_B3_A - [15:0] */

/*
 * W3610 (0xE1A) - EQ1_11
 */
#define WM5100_EQ1_B3_B_MASK                    0xFFFF  /* EQ1_B3_B - [15:0] */
#define WM5100_EQ1_B3_B_SHIFT                        0  /* EQ1_B3_B - [15:0] */
#define WM5100_EQ1_B3_B_WIDTH                       16  /* EQ1_B3_B - [15:0] */

/*
 * W3611 (0xE1B) - EQ1_12
 */
#define WM5100_EQ1_B3_C_MASK                    0xFFFF  /* EQ1_B3_C - [15:0] */
#define WM5100_EQ1_B3_C_SHIFT                        0  /* EQ1_B3_C - [15:0] */
#define WM5100_EQ1_B3_C_WIDTH                       16  /* EQ1_B3_C - [15:0] */

/*
 * W3612 (0xE1C) - EQ1_13
 */
#define WM5100_EQ1_B3_PG_MASK                   0xFFFF  /* EQ1_B3_PG - [15:0] */
#define WM5100_EQ1_B3_PG_SHIFT                       0  /* EQ1_B3_PG - [15:0] */
#define WM5100_EQ1_B3_PG_WIDTH                      16  /* EQ1_B3_PG - [15:0] */

/*
 * W3613 (0xE1D) - EQ1_14
 */
#define WM5100_EQ1_B4_A_MASK                    0xFFFF  /* EQ1_B4_A - [15:0] */
#define WM5100_EQ1_B4_A_SHIFT                        0  /* EQ1_B4_A - [15:0] */
#define WM5100_EQ1_B4_A_WIDTH                       16  /* EQ1_B4_A - [15:0] */

/*
 * W3614 (0xE1E) - EQ1_15
 */
#define WM5100_EQ1_B4_B_MASK                    0xFFFF  /* EQ1_B4_B - [15:0] */
#define WM5100_EQ1_B4_B_SHIFT                        0  /* EQ1_B4_B - [15:0] */
#define WM5100_EQ1_B4_B_WIDTH                       16  /* EQ1_B4_B - [15:0] */

/*
 * W3615 (0xE1F) - EQ1_16
 */
#define WM5100_EQ1_B4_C_MASK                    0xFFFF  /* EQ1_B4_C - [15:0] */
#define WM5100_EQ1_B4_C_SHIFT                        0  /* EQ1_B4_C - [15:0] */
#define WM5100_EQ1_B4_C_WIDTH                       16  /* EQ1_B4_C - [15:0] */

/*
 * W3616 (0xE20) - EQ1_17
 */
#define WM5100_EQ1_B4_PG_MASK                   0xFFFF  /* EQ1_B4_PG - [15:0] */
#define WM5100_EQ1_B4_PG_SHIFT                       0  /* EQ1_B4_PG - [15:0] */
#define WM5100_EQ1_B4_PG_WIDTH                      16  /* EQ1_B4_PG - [15:0] */

/*
 * W3617 (0xE21) - EQ1_18
 */
#define WM5100_EQ1_B5_A_MASK                    0xFFFF  /* EQ1_B5_A - [15:0] */
#define WM5100_EQ1_B5_A_SHIFT                        0  /* EQ1_B5_A - [15:0] */
#define WM5100_EQ1_B5_A_WIDTH                       16  /* EQ1_B5_A - [15:0] */

/*
 * W3618 (0xE22) - EQ1_19
 */
#define WM5100_EQ1_B5_B_MASK                    0xFFFF  /* EQ1_B5_B - [15:0] */
#define WM5100_EQ1_B5_B_SHIFT                        0  /* EQ1_B5_B - [15:0] */
#define WM5100_EQ1_B5_B_WIDTH                       16  /* EQ1_B5_B - [15:0] */

/*
 * W3619 (0xE23) - EQ1_20
 */
#define WM5100_EQ1_B5_PG_MASK                   0xFFFF  /* EQ1_B5_PG - [15:0] */
#define WM5100_EQ1_B5_PG_SHIFT                       0  /* EQ1_B5_PG - [15:0] */
#define WM5100_EQ1_B5_PG_WIDTH                      16  /* EQ1_B5_PG - [15:0] */

/*
 * W3622 (0xE26) - EQ2_1
 */
#define WM5100_EQ2_B1_GAIN_MASK                 0xF800  /* EQ2_B1_GAIN - [15:11] */
#define WM5100_EQ2_B1_GAIN_SHIFT                    11  /* EQ2_B1_GAIN - [15:11] */
#define WM5100_EQ2_B1_GAIN_WIDTH                     5  /* EQ2_B1_GAIN - [15:11] */
#define WM5100_EQ2_B2_GAIN_MASK                 0x07C0  /* EQ2_B2_GAIN - [10:6] */
#define WM5100_EQ2_B2_GAIN_SHIFT                     6  /* EQ2_B2_GAIN - [10:6] */
#define WM5100_EQ2_B2_GAIN_WIDTH                     5  /* EQ2_B2_GAIN - [10:6] */
#define WM5100_EQ2_B3_GAIN_MASK                 0x003E  /* EQ2_B3_GAIN - [5:1] */
#define WM5100_EQ2_B3_GAIN_SHIFT                     1  /* EQ2_B3_GAIN - [5:1] */
#define WM5100_EQ2_B3_GAIN_WIDTH                     5  /* EQ2_B3_GAIN - [5:1] */
#define WM5100_EQ2_ENA                          0x0001  /* EQ2_ENA */
#define WM5100_EQ2_ENA_MASK                     0x0001  /* EQ2_ENA */
#define WM5100_EQ2_ENA_SHIFT                         0  /* EQ2_ENA */
#define WM5100_EQ2_ENA_WIDTH                         1  /* EQ2_ENA */

/*
 * W3623 (0xE27) - EQ2_2
 */
#define WM5100_EQ2_B4_GAIN_MASK                 0xF800  /* EQ2_B4_GAIN - [15:11] */
#define WM5100_EQ2_B4_GAIN_SHIFT                    11  /* EQ2_B4_GAIN - [15:11] */
#define WM5100_EQ2_B4_GAIN_WIDTH                     5  /* EQ2_B4_GAIN - [15:11] */
#define WM5100_EQ2_B5_GAIN_MASK                 0x07C0  /* EQ2_B5_GAIN - [10:6] */
#define WM5100_EQ2_B5_GAIN_SHIFT                     6  /* EQ2_B5_GAIN - [10:6] */
#define WM5100_EQ2_B5_GAIN_WIDTH                     5  /* EQ2_B5_GAIN - [10:6] */

/*
 * W3624 (0xE28) - EQ2_3
 */
#define WM5100_EQ2_B1_A_MASK                    0xFFFF  /* EQ2_B1_A - [15:0] */
#define WM5100_EQ2_B1_A_SHIFT                        0  /* EQ2_B1_A - [15:0] */
#define WM5100_EQ2_B1_A_WIDTH                       16  /* EQ2_B1_A - [15:0] */

/*
 * W3625 (0xE29) - EQ2_4
 */
#define WM5100_EQ2_B1_B_MASK                    0xFFFF  /* EQ2_B1_B - [15:0] */
#define WM5100_EQ2_B1_B_SHIFT                        0  /* EQ2_B1_B - [15:0] */
#define WM5100_EQ2_B1_B_WIDTH                       16  /* EQ2_B1_B - [15:0] */

/*
 * W3626 (0xE2A) - EQ2_5
 */
#define WM5100_EQ2_B1_PG_MASK                   0xFFFF  /* EQ2_B1_PG - [15:0] */
#define WM5100_EQ2_B1_PG_SHIFT                       0  /* EQ2_B1_PG - [15:0] */
#define WM5100_EQ2_B1_PG_WIDTH                      16  /* EQ2_B1_PG - [15:0] */

/*
 * W3627 (0xE2B) - EQ2_6
 */
#define WM5100_EQ2_B2_A_MASK                    0xFFFF  /* EQ2_B2_A - [15:0] */
#define WM5100_EQ2_B2_A_SHIFT                        0  /* EQ2_B2_A - [15:0] */
#define WM5100_EQ2_B2_A_WIDTH                       16  /* EQ2_B2_A - [15:0] */

/*
 * W3628 (0xE2C) - EQ2_7
 */
#define WM5100_EQ2_B2_B_MASK                    0xFFFF  /* EQ2_B2_B - [15:0] */
#define WM5100_EQ2_B2_B_SHIFT                        0  /* EQ2_B2_B - [15:0] */
#define WM5100_EQ2_B2_B_WIDTH                       16  /* EQ2_B2_B - [15:0] */

/*
 * W3629 (0xE2D) - EQ2_8
 */
#define WM5100_EQ2_B2_C_MASK                    0xFFFF  /* EQ2_B2_C - [15:0] */
#define WM5100_EQ2_B2_C_SHIFT                        0  /* EQ2_B2_C - [15:0] */
#define WM5100_EQ2_B2_C_WIDTH                       16  /* EQ2_B2_C - [15:0] */

/*
 * W3630 (0xE2E) - EQ2_9
 */
#define WM5100_EQ2_B2_PG_MASK                   0xFFFF  /* EQ2_B2_PG - [15:0] */
#define WM5100_EQ2_B2_PG_SHIFT                       0  /* EQ2_B2_PG - [15:0] */
#define WM5100_EQ2_B2_PG_WIDTH                      16  /* EQ2_B2_PG - [15:0] */

/*
 * W3631 (0xE2F) - EQ2_10
 */
#define WM5100_EQ2_B3_A_MASK                    0xFFFF  /* EQ2_B3_A - [15:0] */
#define WM5100_EQ2_B3_A_SHIFT                        0  /* EQ2_B3_A - [15:0] */
#define WM5100_EQ2_B3_A_WIDTH                       16  /* EQ2_B3_A - [15:0] */

/*
 * W3632 (0xE30) - EQ2_11
 */
#define WM5100_EQ2_B3_B_MASK                    0xFFFF  /* EQ2_B3_B - [15:0] */
#define WM5100_EQ2_B3_B_SHIFT                        0  /* EQ2_B3_B - [15:0] */
#define WM5100_EQ2_B3_B_WIDTH                       16  /* EQ2_B3_B - [15:0] */

/*
 * W3633 (0xE31) - EQ2_12
 */
#define WM5100_EQ2_B3_C_MASK                    0xFFFF  /* EQ2_B3_C - [15:0] */
#define WM5100_EQ2_B3_C_SHIFT                        0  /* EQ2_B3_C - [15:0] */
#define WM5100_EQ2_B3_C_WIDTH                       16  /* EQ2_B3_C - [15:0] */

/*
 * W3634 (0xE32) - EQ2_13
 */
#define WM5100_EQ2_B3_PG_MASK                   0xFFFF  /* EQ2_B3_PG - [15:0] */
#define WM5100_EQ2_B3_PG_SHIFT                       0  /* EQ2_B3_PG - [15:0] */
#define WM5100_EQ2_B3_PG_WIDTH                      16  /* EQ2_B3_PG - [15:0] */

/*
 * W3635 (0xE33) - EQ2_14
 */
#define WM5100_EQ2_B4_A_MASK                    0xFFFF  /* EQ2_B4_A - [15:0] */
#define WM5100_EQ2_B4_A_SHIFT                        0  /* EQ2_B4_A - [15:0] */
#define WM5100_EQ2_B4_A_WIDTH                       16  /* EQ2_B4_A - [15:0] */

/*
 * W3636 (0xE34) - EQ2_15
 */
#define WM5100_EQ2_B4_B_MASK                    0xFFFF  /* EQ2_B4_B - [15:0] */
#define WM5100_EQ2_B4_B_SHIFT                        0  /* EQ2_B4_B - [15:0] */
#define WM5100_EQ2_B4_B_WIDTH                       16  /* EQ2_B4_B - [15:0] */

/*
 * W3637 (0xE35) - EQ2_16
 */
#define WM5100_EQ2_B4_C_MASK                    0xFFFF  /* EQ2_B4_C - [15:0] */
#define WM5100_EQ2_B4_C_SHIFT                        0  /* EQ2_B4_C - [15:0] */
#define WM5100_EQ2_B4_C_WIDTH                       16  /* EQ2_B4_C - [15:0] */

/*
 * W3638 (0xE36) - EQ2_17
 */
#define WM5100_EQ2_B4_PG_MASK                   0xFFFF  /* EQ2_B4_PG - [15:0] */
#define WM5100_EQ2_B4_PG_SHIFT                       0  /* EQ2_B4_PG - [15:0] */
#define WM5100_EQ2_B4_PG_WIDTH                      16  /* EQ2_B4_PG - [15:0] */

/*
 * W3639 (0xE37) - EQ2_18
 */
#define WM5100_EQ2_B5_A_MASK                    0xFFFF  /* EQ2_B5_A - [15:0] */
#define WM5100_EQ2_B5_A_SHIFT                        0  /* EQ2_B5_A - [15:0] */
#define WM5100_EQ2_B5_A_WIDTH                       16  /* EQ2_B5_A - [15:0] */

/*
 * W3640 (0xE38) - EQ2_19
 */
#define WM5100_EQ2_B5_B_MASK                    0xFFFF  /* EQ2_B5_B - [15:0] */
#define WM5100_EQ2_B5_B_SHIFT                        0  /* EQ2_B5_B - [15:0] */
#define WM5100_EQ2_B5_B_WIDTH                       16  /* EQ2_B5_B - [15:0] */

/*
 * W3641 (0xE39) - EQ2_20
 */
#define WM5100_EQ2_B5_PG_MASK                   0xFFFF  /* EQ2_B5_PG - [15:0] */
#define WM5100_EQ2_B5_PG_SHIFT                       0  /* EQ2_B5_PG - [15:0] */
#define WM5100_EQ2_B5_PG_WIDTH                      16  /* EQ2_B5_PG - [15:0] */

/*
 * W3644 (0xE3C) - EQ3_1
 */
#define WM5100_EQ3_B1_GAIN_MASK                 0xF800  /* EQ3_B1_GAIN - [15:11] */
#define WM5100_EQ3_B1_GAIN_SHIFT                    11  /* EQ3_B1_GAIN - [15:11] */
#define WM5100_EQ3_B1_GAIN_WIDTH                     5  /* EQ3_B1_GAIN - [15:11] */
#define WM5100_EQ3_B2_GAIN_MASK                 0x07C0  /* EQ3_B2_GAIN - [10:6] */
#define WM5100_EQ3_B2_GAIN_SHIFT                     6  /* EQ3_B2_GAIN - [10:6] */
#define WM5100_EQ3_B2_GAIN_WIDTH                     5  /* EQ3_B2_GAIN - [10:6] */
#define WM5100_EQ3_B3_GAIN_MASK                 0x003E  /* EQ3_B3_GAIN - [5:1] */
#define WM5100_EQ3_B3_GAIN_SHIFT                     1  /* EQ3_B3_GAIN - [5:1] */
#define WM5100_EQ3_B3_GAIN_WIDTH                     5  /* EQ3_B3_GAIN - [5:1] */
#define WM5100_EQ3_ENA                          0x0001  /* EQ3_ENA */
#define WM5100_EQ3_ENA_MASK                     0x0001  /* EQ3_ENA */
#define WM5100_EQ3_ENA_SHIFT                         0  /* EQ3_ENA */
#define WM5100_EQ3_ENA_WIDTH                         1  /* EQ3_ENA */

/*
 * W3645 (0xE3D) - EQ3_2
 */
#define WM5100_EQ3_B4_GAIN_MASK                 0xF800  /* EQ3_B4_GAIN - [15:11] */
#define WM5100_EQ3_B4_GAIN_SHIFT                    11  /* EQ3_B4_GAIN - [15:11] */
#define WM5100_EQ3_B4_GAIN_WIDTH                     5  /* EQ3_B4_GAIN - [15:11] */
#define WM5100_EQ3_B5_GAIN_MASK                 0x07C0  /* EQ3_B5_GAIN - [10:6] */
#define WM5100_EQ3_B5_GAIN_SHIFT                     6  /* EQ3_B5_GAIN - [10:6] */
#define WM5100_EQ3_B5_GAIN_WIDTH                     5  /* EQ3_B5_GAIN - [10:6] */

/*
 * W3646 (0xE3E) - EQ3_3
 */
#define WM5100_EQ3_B1_A_MASK                    0xFFFF  /* EQ3_B1_A - [15:0] */
#define WM5100_EQ3_B1_A_SHIFT                        0  /* EQ3_B1_A - [15:0] */
#define WM5100_EQ3_B1_A_WIDTH                       16  /* EQ3_B1_A - [15:0] */

/*
 * W3647 (0xE3F) - EQ3_4
 */
#define WM5100_EQ3_B1_B_MASK                    0xFFFF  /* EQ3_B1_B - [15:0] */
#define WM5100_EQ3_B1_B_SHIFT                        0  /* EQ3_B1_B - [15:0] */
#define WM5100_EQ3_B1_B_WIDTH                       16  /* EQ3_B1_B - [15:0] */

/*
 * W3648 (0xE40) - EQ3_5
 */
#define WM5100_EQ3_B1_PG_MASK                   0xFFFF  /* EQ3_B1_PG - [15:0] */
#define WM5100_EQ3_B1_PG_SHIFT                       0  /* EQ3_B1_PG - [15:0] */
#define WM5100_EQ3_B1_PG_WIDTH                      16  /* EQ3_B1_PG - [15:0] */

/*
 * W3649 (0xE41) - EQ3_6
 */
#define WM5100_EQ3_B2_A_MASK                    0xFFFF  /* EQ3_B2_A - [15:0] */
#define WM5100_EQ3_B2_A_SHIFT                        0  /* EQ3_B2_A - [15:0] */
#define WM5100_EQ3_B2_A_WIDTH                       16  /* EQ3_B2_A - [15:0] */

/*
 * W3650 (0xE42) - EQ3_7
 */
#define WM5100_EQ3_B2_B_MASK                    0xFFFF  /* EQ3_B2_B - [15:0] */
#define WM5100_EQ3_B2_B_SHIFT                        0  /* EQ3_B2_B - [15:0] */
#define WM5100_EQ3_B2_B_WIDTH                       16  /* EQ3_B2_B - [15:0] */

/*
 * W3651 (0xE43) - EQ3_8
 */
#define WM5100_EQ3_B2_C_MASK                    0xFFFF  /* EQ3_B2_C - [15:0] */
#define WM5100_EQ3_B2_C_SHIFT                        0  /* EQ3_B2_C - [15:0] */
#define WM5100_EQ3_B2_C_WIDTH                       16  /* EQ3_B2_C - [15:0] */

/*
 * W3652 (0xE44) - EQ3_9
 */
#define WM5100_EQ3_B2_PG_MASK                   0xFFFF  /* EQ3_B2_PG - [15:0] */
#define WM5100_EQ3_B2_PG_SHIFT                       0  /* EQ3_B2_PG - [15:0] */
#define WM5100_EQ3_B2_PG_WIDTH                      16  /* EQ3_B2_PG - [15:0] */

/*
 * W3653 (0xE45) - EQ3_10
 */
#define WM5100_EQ3_B3_A_MASK                    0xFFFF  /* EQ3_B3_A - [15:0] */
#define WM5100_EQ3_B3_A_SHIFT                        0  /* EQ3_B3_A - [15:0] */
#define WM5100_EQ3_B3_A_WIDTH                       16  /* EQ3_B3_A - [15:0] */

/*
 * W3654 (0xE46) - EQ3_11
 */
#define WM5100_EQ3_B3_B_MASK                    0xFFFF  /* EQ3_B3_B - [15:0] */
#define WM5100_EQ3_B3_B_SHIFT                        0  /* EQ3_B3_B - [15:0] */
#define WM5100_EQ3_B3_B_WIDTH                       16  /* EQ3_B3_B - [15:0] */

/*
 * W3655 (0xE47) - EQ3_12
 */
#define WM5100_EQ3_B3_C_MASK                    0xFFFF  /* EQ3_B3_C - [15:0] */
#define WM5100_EQ3_B3_C_SHIFT                        0  /* EQ3_B3_C - [15:0] */
#define WM5100_EQ3_B3_C_WIDTH                       16  /* EQ3_B3_C - [15:0] */

/*
 * W3656 (0xE48) - EQ3_13
 */
#define WM5100_EQ3_B3_PG_MASK                   0xFFFF  /* EQ3_B3_PG - [15:0] */
#define WM5100_EQ3_B3_PG_SHIFT                       0  /* EQ3_B3_PG - [15:0] */
#define WM5100_EQ3_B3_PG_WIDTH                      16  /* EQ3_B3_PG - [15:0] */

/*
 * W3657 (0xE49) - EQ3_14
 */
#define WM5100_EQ3_B4_A_MASK                    0xFFFF  /* EQ3_B4_A - [15:0] */
#define WM5100_EQ3_B4_A_SHIFT                        0  /* EQ3_B4_A - [15:0] */
#define WM5100_EQ3_B4_A_WIDTH                       16  /* EQ3_B4_A - [15:0] */

/*
 * W3658 (0xE4A) - EQ3_15
 */
#define WM5100_EQ3_B4_B_MASK                    0xFFFF  /* EQ3_B4_B - [15:0] */
#define WM5100_EQ3_B4_B_SHIFT                        0  /* EQ3_B4_B - [15:0] */
#define WM5100_EQ3_B4_B_WIDTH                       16  /* EQ3_B4_B - [15:0] */

/*
 * W3659 (0xE4B) - EQ3_16
 */
#define WM5100_EQ3_B4_C_MASK                    0xFFFF  /* EQ3_B4_C - [15:0] */
#define WM5100_EQ3_B4_C_SHIFT                        0  /* EQ3_B4_C - [15:0] */
#define WM5100_EQ3_B4_C_WIDTH                       16  /* EQ3_B4_C - [15:0] */

/*
 * W3660 (0xE4C) - EQ3_17
 */
#define WM5100_EQ3_B4_PG_MASK                   0xFFFF  /* EQ3_B4_PG - [15:0] */
#define WM5100_EQ3_B4_PG_SHIFT                       0  /* EQ3_B4_PG - [15:0] */
#define WM5100_EQ3_B4_PG_WIDTH                      16  /* EQ3_B4_PG - [15:0] */

/*
 * W3661 (0xE4D) - EQ3_18
 */
#define WM5100_EQ3_B5_A_MASK                    0xFFFF  /* EQ3_B5_A - [15:0] */
#define WM5100_EQ3_B5_A_SHIFT                        0  /* EQ3_B5_A - [15:0] */
#define WM5100_EQ3_B5_A_WIDTH                       16  /* EQ3_B5_A - [15:0] */

/*
 * W3662 (0xE4E) - EQ3_19
 */
#define WM5100_EQ3_B5_B_MASK                    0xFFFF  /* EQ3_B5_B - [15:0] */
#define WM5100_EQ3_B5_B_SHIFT                        0  /* EQ3_B5_B - [15:0] */
#define WM5100_EQ3_B5_B_WIDTH                       16  /* EQ3_B5_B - [15:0] */

/*
 * W3663 (0xE4F) - EQ3_20
 */
#define WM5100_EQ3_B5_PG_MASK                   0xFFFF  /* EQ3_B5_PG - [15:0] */
#define WM5100_EQ3_B5_PG_SHIFT                       0  /* EQ3_B5_PG - [15:0] */
#define WM5100_EQ3_B5_PG_WIDTH                      16  /* EQ3_B5_PG - [15:0] */

/*
 * W3666 (0xE52) - EQ4_1
 */
#define WM5100_EQ4_B1_GAIN_MASK                 0xF800  /* EQ4_B1_GAIN - [15:11] */
#define WM5100_EQ4_B1_GAIN_SHIFT                    11  /* EQ4_B1_GAIN - [15:11] */
#define WM5100_EQ4_B1_GAIN_WIDTH                     5  /* EQ4_B1_GAIN - [15:11] */
#define WM5100_EQ4_B2_GAIN_MASK                 0x07C0  /* EQ4_B2_GAIN - [10:6] */
#define WM5100_EQ4_B2_GAIN_SHIFT                     6  /* EQ4_B2_GAIN - [10:6] */
#define WM5100_EQ4_B2_GAIN_WIDTH                     5  /* EQ4_B2_GAIN - [10:6] */
#define WM5100_EQ4_B3_GAIN_MASK                 0x003E  /* EQ4_B3_GAIN - [5:1] */
#define WM5100_EQ4_B3_GAIN_SHIFT                     1  /* EQ4_B3_GAIN - [5:1] */
#define WM5100_EQ4_B3_GAIN_WIDTH                     5  /* EQ4_B3_GAIN - [5:1] */
#define WM5100_EQ4_ENA                          0x0001  /* EQ4_ENA */
#define WM5100_EQ4_ENA_MASK                     0x0001  /* EQ4_ENA */
#define WM5100_EQ4_ENA_SHIFT                         0  /* EQ4_ENA */
#define WM5100_EQ4_ENA_WIDTH                         1  /* EQ4_ENA */

/*
 * W3667 (0xE53) - EQ4_2
 */
#define WM5100_EQ4_B4_GAIN_MASK                 0xF800  /* EQ4_B4_GAIN - [15:11] */
#define WM5100_EQ4_B4_GAIN_SHIFT                    11  /* EQ4_B4_GAIN - [15:11] */
#define WM5100_EQ4_B4_GAIN_WIDTH                     5  /* EQ4_B4_GAIN - [15:11] */
#define WM5100_EQ4_B5_GAIN_MASK                 0x07C0  /* EQ4_B5_GAIN - [10:6] */
#define WM5100_EQ4_B5_GAIN_SHIFT                     6  /* EQ4_B5_GAIN - [10:6] */
#define WM5100_EQ4_B5_GAIN_WIDTH                     5  /* EQ4_B5_GAIN - [10:6] */

/*
 * W3668 (0xE54) - EQ4_3
 */
#define WM5100_EQ4_B1_A_MASK                    0xFFFF  /* EQ4_B1_A - [15:0] */
#define WM5100_EQ4_B1_A_SHIFT                        0  /* EQ4_B1_A - [15:0] */
#define WM5100_EQ4_B1_A_WIDTH                       16  /* EQ4_B1_A - [15:0] */

/*
 * W3669 (0xE55) - EQ4_4
 */
#define WM5100_EQ4_B1_B_MASK                    0xFFFF  /* EQ4_B1_B - [15:0] */
#define WM5100_EQ4_B1_B_SHIFT                        0  /* EQ4_B1_B - [15:0] */
#define WM5100_EQ4_B1_B_WIDTH                       16  /* EQ4_B1_B - [15:0] */

/*
 * W3670 (0xE56) - EQ4_5
 */
#define WM5100_EQ4_B1_PG_MASK                   0xFFFF  /* EQ4_B1_PG - [15:0] */
#define WM5100_EQ4_B1_PG_SHIFT                       0  /* EQ4_B1_PG - [15:0] */
#define WM5100_EQ4_B1_PG_WIDTH                      16  /* EQ4_B1_PG - [15:0] */

/*
 * W3671 (0xE57) - EQ4_6
 */
#define WM5100_EQ4_B2_A_MASK                    0xFFFF  /* EQ4_B2_A - [15:0] */
#define WM5100_EQ4_B2_A_SHIFT                        0  /* EQ4_B2_A - [15:0] */
#define WM5100_EQ4_B2_A_WIDTH                       16  /* EQ4_B2_A - [15:0] */

/*
 * W3672 (0xE58) - EQ4_7
 */
#define WM5100_EQ4_B2_B_MASK                    0xFFFF  /* EQ4_B2_B - [15:0] */
#define WM5100_EQ4_B2_B_SHIFT                        0  /* EQ4_B2_B - [15:0] */
#define WM5100_EQ4_B2_B_WIDTH                       16  /* EQ4_B2_B - [15:0] */

/*
 * W3673 (0xE59) - EQ4_8
 */
#define WM5100_EQ4_B2_C_MASK                    0xFFFF  /* EQ4_B2_C - [15:0] */
#define WM5100_EQ4_B2_C_SHIFT                        0  /* EQ4_B2_C - [15:0] */
#define WM5100_EQ4_B2_C_WIDTH                       16  /* EQ4_B2_C - [15:0] */

/*
 * W3674 (0xE5A) - EQ4_9
 */
#define WM5100_EQ4_B2_PG_MASK                   0xFFFF  /* EQ4_B2_PG - [15:0] */
#define WM5100_EQ4_B2_PG_SHIFT                       0  /* EQ4_B2_PG - [15:0] */
#define WM5100_EQ4_B2_PG_WIDTH                      16  /* EQ4_B2_PG - [15:0] */

/*
 * W3675 (0xE5B) - EQ4_10
 */
#define WM5100_EQ4_B3_A_MASK                    0xFFFF  /* EQ4_B3_A - [15:0] */
#define WM5100_EQ4_B3_A_SHIFT                        0  /* EQ4_B3_A - [15:0] */
#define WM5100_EQ4_B3_A_WIDTH                       16  /* EQ4_B3_A - [15:0] */

/*
 * W3676 (0xE5C) - EQ4_11
 */
#define WM5100_EQ4_B3_B_MASK                    0xFFFF  /* EQ4_B3_B - [15:0] */
#define WM5100_EQ4_B3_B_SHIFT                        0  /* EQ4_B3_B - [15:0] */
#define WM5100_EQ4_B3_B_WIDTH                       16  /* EQ4_B3_B - [15:0] */

/*
 * W3677 (0xE5D) - EQ4_12
 */
#define WM5100_EQ4_B3_C_MASK                    0xFFFF  /* EQ4_B3_C - [15:0] */
#define WM5100_EQ4_B3_C_SHIFT                        0  /* EQ4_B3_C - [15:0] */
#define WM5100_EQ4_B3_C_WIDTH                       16  /* EQ4_B3_C - [15:0] */

/*
 * W3678 (0xE5E) - EQ4_13
 */
#define WM5100_EQ4_B3_PG_MASK                   0xFFFF  /* EQ4_B3_PG - [15:0] */
#define WM5100_EQ4_B3_PG_SHIFT                       0  /* EQ4_B3_PG - [15:0] */
#define WM5100_EQ4_B3_PG_WIDTH                      16  /* EQ4_B3_PG - [15:0] */

/*
 * W3679 (0xE5F) - EQ4_14
 */
#define WM5100_EQ4_B4_A_MASK                    0xFFFF  /* EQ4_B4_A - [15:0] */
#define WM5100_EQ4_B4_A_SHIFT                        0  /* EQ4_B4_A - [15:0] */
#define WM5100_EQ4_B4_A_WIDTH                       16  /* EQ4_B4_A - [15:0] */

/*
 * W3680 (0xE60) - EQ4_15
 */
#define WM5100_EQ4_B4_B_MASK                    0xFFFF  /* EQ4_B4_B - [15:0] */
#define WM5100_EQ4_B4_B_SHIFT                        0  /* EQ4_B4_B - [15:0] */
#define WM5100_EQ4_B4_B_WIDTH                       16  /* EQ4_B4_B - [15:0] */

/*
 * W3681 (0xE61) - EQ4_16
 */
#define WM5100_EQ4_B4_C_MASK                    0xFFFF  /* EQ4_B4_C - [15:0] */
#define WM5100_EQ4_B4_C_SHIFT                        0  /* EQ4_B4_C - [15:0] */
#define WM5100_EQ4_B4_C_WIDTH                       16  /* EQ4_B4_C - [15:0] */

/*
 * W3682 (0xE62) - EQ4_17
 */
#define WM5100_EQ4_B4_PG_MASK                   0xFFFF  /* EQ4_B4_PG - [15:0] */
#define WM5100_EQ4_B4_PG_SHIFT                       0  /* EQ4_B4_PG - [15:0] */
#define WM5100_EQ4_B4_PG_WIDTH                      16  /* EQ4_B4_PG - [15:0] */

/*
 * W3683 (0xE63) - EQ4_18
 */
#define WM5100_EQ4_B5_A_MASK                    0xFFFF  /* EQ4_B5_A - [15:0] */
#define WM5100_EQ4_B5_A_SHIFT                        0  /* EQ4_B5_A - [15:0] */
#define WM5100_EQ4_B5_A_WIDTH                       16  /* EQ4_B5_A - [15:0] */

/*
 * W3684 (0xE64) - EQ4_19
 */
#define WM5100_EQ4_B5_B_MASK                    0xFFFF  /* EQ4_B5_B - [15:0] */
#define WM5100_EQ4_B5_B_SHIFT                        0  /* EQ4_B5_B - [15:0] */
#define WM5100_EQ4_B5_B_WIDTH                       16  /* EQ4_B5_B - [15:0] */

/*
 * W3685 (0xE65) - EQ4_20
 */
#define WM5100_EQ4_B5_PG_MASK                   0xFFFF  /* EQ4_B5_PG - [15:0] */
#define WM5100_EQ4_B5_PG_SHIFT                       0  /* EQ4_B5_PG - [15:0] */
#define WM5100_EQ4_B5_PG_WIDTH                      16  /* EQ4_B5_PG - [15:0] */

/*
 * W3712 (0xE80) - DWC1 ctww1
 */
#define WM5100_DWC_SIG_DET_WMS_MASK             0xF800  /* DWC_SIG_DET_WMS - [15:11] */
#define WM5100_DWC_SIG_DET_WMS_SHIFT                11  /* DWC_SIG_DET_WMS - [15:11] */
#define WM5100_DWC_SIG_DET_WMS_WIDTH                 5  /* DWC_SIG_DET_WMS - [15:11] */
#define WM5100_DWC_SIG_DET_PK_MASK              0x0600  /* DWC_SIG_DET_PK - [10:9] */
#define WM5100_DWC_SIG_DET_PK_SHIFT                  9  /* DWC_SIG_DET_PK - [10:9] */
#define WM5100_DWC_SIG_DET_PK_WIDTH                  2  /* DWC_SIG_DET_PK - [10:9] */
#define WM5100_DWC_NG_ENA                       0x0100  /* DWC_NG_ENA */
#define WM5100_DWC_NG_ENA_MASK                  0x0100  /* DWC_NG_ENA */
#define WM5100_DWC_NG_ENA_SHIFT                      8  /* DWC_NG_ENA */
#define WM5100_DWC_NG_ENA_WIDTH                      1  /* DWC_NG_ENA */
#define WM5100_DWC_SIG_DET_MODE                 0x0080  /* DWC_SIG_DET_MODE */
#define WM5100_DWC_SIG_DET_MODE_MASK            0x0080  /* DWC_SIG_DET_MODE */
#define WM5100_DWC_SIG_DET_MODE_SHIFT                7  /* DWC_SIG_DET_MODE */
#define WM5100_DWC_SIG_DET_MODE_WIDTH                1  /* DWC_SIG_DET_MODE */
#define WM5100_DWC_SIG_DET                      0x0040  /* DWC_SIG_DET */
#define WM5100_DWC_SIG_DET_MASK                 0x0040  /* DWC_SIG_DET */
#define WM5100_DWC_SIG_DET_SHIFT                     6  /* DWC_SIG_DET */
#define WM5100_DWC_SIG_DET_WIDTH                     1  /* DWC_SIG_DET */
#define WM5100_DWC_KNEE2_OP_ENA                 0x0020  /* DWC_KNEE2_OP_ENA */
#define WM5100_DWC_KNEE2_OP_ENA_MASK            0x0020  /* DWC_KNEE2_OP_ENA */
#define WM5100_DWC_KNEE2_OP_ENA_SHIFT                5  /* DWC_KNEE2_OP_ENA */
#define WM5100_DWC_KNEE2_OP_ENA_WIDTH                1  /* DWC_KNEE2_OP_ENA */
#define WM5100_DWC_QW                           0x0010  /* DWC_QW */
#define WM5100_DWC_QW_MASK                      0x0010  /* DWC_QW */
#define WM5100_DWC_QW_SHIFT                          4  /* DWC_QW */
#define WM5100_DWC_QW_WIDTH                          1  /* DWC_QW */
#define WM5100_DWC_ANTICWIP                     0x0008  /* DWC_ANTICWIP */
#define WM5100_DWC_ANTICWIP_MASK                0x0008  /* DWC_ANTICWIP */
#define WM5100_DWC_ANTICWIP_SHIFT                    3  /* DWC_ANTICWIP */
#define WM5100_DWC_ANTICWIP_WIDTH                    1  /* DWC_ANTICWIP */
#define WM5100_DWCW_ENA                         0x0002  /* DWCW_ENA */
#define WM5100_DWCW_ENA_MASK                    0x0002  /* DWCW_ENA */
#define WM5100_DWCW_ENA_SHIFT                        1  /* DWCW_ENA */
#define WM5100_DWCW_ENA_WIDTH                        1  /* DWCW_ENA */
#define WM5100_DWCW_ENA                         0x0001  /* DWCW_ENA */
#define WM5100_DWCW_ENA_MASK                    0x0001  /* DWCW_ENA */
#define WM5100_DWCW_ENA_SHIFT                        0  /* DWCW_ENA */
#define WM5100_DWCW_ENA_WIDTH                        1  /* DWCW_ENA */

/*
 * W3713 (0xE81) - DWC1 ctww2
 */
#define WM5100_DWC_ATK_MASK                     0x1E00  /* DWC_ATK - [12:9] */
#define WM5100_DWC_ATK_SHIFT                         9  /* DWC_ATK - [12:9] */
#define WM5100_DWC_ATK_WIDTH                         4  /* DWC_ATK - [12:9] */
#define WM5100_DWC_DCY_MASK                     0x01E0  /* DWC_DCY - [8:5] */
#define WM5100_DWC_DCY_SHIFT                         5  /* DWC_DCY - [8:5] */
#define WM5100_DWC_DCY_WIDTH                         4  /* DWC_DCY - [8:5] */
#define WM5100_DWC_MINGAIN_MASK                 0x001C  /* DWC_MINGAIN - [4:2] */
#define WM5100_DWC_MINGAIN_SHIFT                     2  /* DWC_MINGAIN - [4:2] */
#define WM5100_DWC_MINGAIN_WIDTH                     3  /* DWC_MINGAIN - [4:2] */
#define WM5100_DWC_MAXGAIN_MASK                 0x0003  /* DWC_MAXGAIN - [1:0] */
#define WM5100_DWC_MAXGAIN_SHIFT                     0  /* DWC_MAXGAIN - [1:0] */
#define WM5100_DWC_MAXGAIN_WIDTH                     2  /* DWC_MAXGAIN - [1:0] */

/*
 * W3714 (0xE82) - DWC1 ctww3
 */
#define WM5100_DWC_NG_MINGAIN_MASK              0xF000  /* DWC_NG_MINGAIN - [15:12] */
#define WM5100_DWC_NG_MINGAIN_SHIFT                 12  /* DWC_NG_MINGAIN - [15:12] */
#define WM5100_DWC_NG_MINGAIN_WIDTH                  4  /* DWC_NG_MINGAIN - [15:12] */
#define WM5100_DWC_NG_EXP_MASK                  0x0C00  /* DWC_NG_EXP - [11:10] */
#define WM5100_DWC_NG_EXP_SHIFT                     10  /* DWC_NG_EXP - [11:10] */
#define WM5100_DWC_NG_EXP_WIDTH                      2  /* DWC_NG_EXP - [11:10] */
#define WM5100_DWC_QW_THW_MASK                  0x0300  /* DWC_QW_THW - [9:8] */
#define WM5100_DWC_QW_THW_SHIFT                      8  /* DWC_QW_THW - [9:8] */
#define WM5100_DWC_QW_THW_WIDTH                      2  /* DWC_QW_THW - [9:8] */
#define WM5100_DWC_QW_DCY_MASK                  0x00C0  /* DWC_QW_DCY - [7:6] */
#define WM5100_DWC_QW_DCY_SHIFT                      6  /* DWC_QW_DCY - [7:6] */
#define WM5100_DWC_QW_DCY_WIDTH                      2  /* DWC_QW_DCY - [7:6] */
#define WM5100_DWC_HI_COMP_MASK                 0x0038  /* DWC_HI_COMP - [5:3] */
#define WM5100_DWC_HI_COMP_SHIFT                     3  /* DWC_HI_COMP - [5:3] */
#define WM5100_DWC_HI_COMP_WIDTH                     3  /* DWC_HI_COMP - [5:3] */
#define WM5100_DWC_WO_COMP_MASK                 0x0007  /* DWC_WO_COMP - [2:0] */
#define WM5100_DWC_WO_COMP_SHIFT                     0  /* DWC_WO_COMP - [2:0] */
#define WM5100_DWC_WO_COMP_WIDTH                     3  /* DWC_WO_COMP - [2:0] */

/*
 * W3715 (0xE83) - DWC1 ctww4
 */
#define WM5100_DWC_KNEE_IP_MASK                 0x07E0  /* DWC_KNEE_IP - [10:5] */
#define WM5100_DWC_KNEE_IP_SHIFT                     5  /* DWC_KNEE_IP - [10:5] */
#define WM5100_DWC_KNEE_IP_WIDTH                     6  /* DWC_KNEE_IP - [10:5] */
#define WM5100_DWC_KNEE_OP_MASK                 0x001F  /* DWC_KNEE_OP - [4:0] */
#define WM5100_DWC_KNEE_OP_SHIFT                     0  /* DWC_KNEE_OP - [4:0] */
#define WM5100_DWC_KNEE_OP_WIDTH                     5  /* DWC_KNEE_OP - [4:0] */

/*
 * W3716 (0xE84) - DWC1 ctww5
 */
#define WM5100_DWC_KNEE2_IP_MASK                0x03E0  /* DWC_KNEE2_IP - [9:5] */
#define WM5100_DWC_KNEE2_IP_SHIFT                    5  /* DWC_KNEE2_IP - [9:5] */
#define WM5100_DWC_KNEE2_IP_WIDTH                    5  /* DWC_KNEE2_IP - [9:5] */
#define WM5100_DWC_KNEE2_OP_MASK                0x001F  /* DWC_KNEE2_OP - [4:0] */
#define WM5100_DWC_KNEE2_OP_SHIFT                    0  /* DWC_KNEE2_OP - [4:0] */
#define WM5100_DWC_KNEE2_OP_WIDTH                    5  /* DWC_KNEE2_OP - [4:0] */

/*
 * W3776 (0xEC0) - HPWPF1_1
 */
#define WM5100_WHPF1_MODE                       0x0002  /* WHPF1_MODE */
#define WM5100_WHPF1_MODE_MASK                  0x0002  /* WHPF1_MODE */
#define WM5100_WHPF1_MODE_SHIFT                      1  /* WHPF1_MODE */
#define WM5100_WHPF1_MODE_WIDTH                      1  /* WHPF1_MODE */
#define WM5100_WHPF1_ENA                        0x0001  /* WHPF1_ENA */
#define WM5100_WHPF1_ENA_MASK                   0x0001  /* WHPF1_ENA */
#define WM5100_WHPF1_ENA_SHIFT                       0  /* WHPF1_ENA */
#define WM5100_WHPF1_ENA_WIDTH                       1  /* WHPF1_ENA */

/*
 * W3777 (0xEC1) - HPWPF1_2
 */
#define WM5100_WHPF1_COEFF_MASK                 0xFFFF  /* WHPF1_COEFF - [15:0] */
#define WM5100_WHPF1_COEFF_SHIFT                     0  /* WHPF1_COEFF - [15:0] */
#define WM5100_WHPF1_COEFF_WIDTH                    16  /* WHPF1_COEFF - [15:0] */

/*
 * W3780 (0xEC4) - HPWPF2_1
 */
#define WM5100_WHPF2_MODE                       0x0002  /* WHPF2_MODE */
#define WM5100_WHPF2_MODE_MASK                  0x0002  /* WHPF2_MODE */
#define WM5100_WHPF2_MODE_SHIFT                      1  /* WHPF2_MODE */
#define WM5100_WHPF2_MODE_WIDTH                      1  /* WHPF2_MODE */
#define WM5100_WHPF2_ENA                        0x0001  /* WHPF2_ENA */
#define WM5100_WHPF2_ENA_MASK                   0x0001  /* WHPF2_ENA */
#define WM5100_WHPF2_ENA_SHIFT                       0  /* WHPF2_ENA */
#define WM5100_WHPF2_ENA_WIDTH                       1  /* WHPF2_ENA */

/*
 * W3781 (0xEC5) - HPWPF2_2
 */
#define WM5100_WHPF2_COEFF_MASK                 0xFFFF  /* WHPF2_COEFF - [15:0] */
#define WM5100_WHPF2_COEFF_SHIFT                     0  /* WHPF2_COEFF - [15:0] */
#define WM5100_WHPF2_COEFF_WIDTH                    16  /* WHPF2_COEFF - [15:0] */

/*
 * W3784 (0xEC8) - HPWPF3_1
 */
#define WM5100_WHPF3_MODE                       0x0002  /* WHPF3_MODE */
#define WM5100_WHPF3_MODE_MASK                  0x0002  /* WHPF3_MODE */
#define WM5100_WHPF3_MODE_SHIFT                      1  /* WHPF3_MODE */
#define WM5100_WHPF3_MODE_WIDTH                      1  /* WHPF3_MODE */
#define WM5100_WHPF3_ENA                        0x0001  /* WHPF3_ENA */
#define WM5100_WHPF3_ENA_MASK                   0x0001  /* WHPF3_ENA */
#define WM5100_WHPF3_ENA_SHIFT                       0  /* WHPF3_ENA */
#define WM5100_WHPF3_ENA_WIDTH                       1  /* WHPF3_ENA */

/*
 * W3785 (0xEC9) - HPWPF3_2
 */
#define WM5100_WHPF3_COEFF_MASK                 0xFFFF  /* WHPF3_COEFF - [15:0] */
#define WM5100_WHPF3_COEFF_SHIFT                     0  /* WHPF3_COEFF - [15:0] */
#define WM5100_WHPF3_COEFF_WIDTH                    16  /* WHPF3_COEFF - [15:0] */

/*
 * W3788 (0xECC) - HPWPF4_1
 */
#define WM5100_WHPF4_MODE                       0x0002  /* WHPF4_MODE */
#define WM5100_WHPF4_MODE_MASK                  0x0002  /* WHPF4_MODE */
#define WM5100_WHPF4_MODE_SHIFT                      1  /* WHPF4_MODE */
#define WM5100_WHPF4_MODE_WIDTH                      1  /* WHPF4_MODE */
#define WM5100_WHPF4_ENA                        0x0001  /* WHPF4_ENA */
#define WM5100_WHPF4_ENA_MASK                   0x0001  /* WHPF4_ENA */
#define WM5100_WHPF4_ENA_SHIFT                       0  /* WHPF4_ENA */
#define WM5100_WHPF4_ENA_WIDTH                       1  /* WHPF4_ENA */

/*
 * W3789 (0xECD) - HPWPF4_2
 */
#define WM5100_WHPF4_COEFF_MASK                 0xFFFF  /* WHPF4_COEFF - [15:0] */
#define WM5100_WHPF4_COEFF_SHIFT                     0  /* WHPF4_COEFF - [15:0] */
#define WM5100_WHPF4_COEFF_WIDTH                    16  /* WHPF4_COEFF - [15:0] */

/*
 * W4132 (0x1024) - DSP2 Contwow 30
 */
#define WM5100_DSP2_WATE_MASK                   0xC000  /* DSP2_WATE - [15:14] */
#define WM5100_DSP2_WATE_SHIFT                      14  /* DSP2_WATE - [15:14] */
#define WM5100_DSP2_WATE_WIDTH                       2  /* DSP2_WATE - [15:14] */
#define WM5100_DSP2_DBG_CWK_ENA                 0x0008  /* DSP2_DBG_CWK_ENA */
#define WM5100_DSP2_DBG_CWK_ENA_MASK            0x0008  /* DSP2_DBG_CWK_ENA */
#define WM5100_DSP2_DBG_CWK_ENA_SHIFT                3  /* DSP2_DBG_CWK_ENA */
#define WM5100_DSP2_DBG_CWK_ENA_WIDTH                1  /* DSP2_DBG_CWK_ENA */
#define WM5100_DSP2_SYS_ENA                     0x0004  /* DSP2_SYS_ENA */
#define WM5100_DSP2_SYS_ENA_MASK                0x0004  /* DSP2_SYS_ENA */
#define WM5100_DSP2_SYS_ENA_SHIFT                    2  /* DSP2_SYS_ENA */
#define WM5100_DSP2_SYS_ENA_WIDTH                    1  /* DSP2_SYS_ENA */
#define WM5100_DSP2_COWE_ENA                    0x0002  /* DSP2_COWE_ENA */
#define WM5100_DSP2_COWE_ENA_MASK               0x0002  /* DSP2_COWE_ENA */
#define WM5100_DSP2_COWE_ENA_SHIFT                   1  /* DSP2_COWE_ENA */
#define WM5100_DSP2_COWE_ENA_WIDTH                   1  /* DSP2_COWE_ENA */
#define WM5100_DSP2_STAWT                       0x0001  /* DSP2_STAWT */
#define WM5100_DSP2_STAWT_MASK                  0x0001  /* DSP2_STAWT */
#define WM5100_DSP2_STAWT_SHIFT                      0  /* DSP2_STAWT */
#define WM5100_DSP2_STAWT_WIDTH                      1  /* DSP2_STAWT */

/*
 * W3876 (0xF24) - DSP1 Contwow 30
 */
#define WM5100_DSP1_WATE_MASK                   0xC000  /* DSP1_WATE - [15:14] */
#define WM5100_DSP1_WATE_SHIFT                      14  /* DSP1_WATE - [15:14] */
#define WM5100_DSP1_WATE_WIDTH                       2  /* DSP1_WATE - [15:14] */
#define WM5100_DSP1_DBG_CWK_ENA                 0x0008  /* DSP1_DBG_CWK_ENA */
#define WM5100_DSP1_DBG_CWK_ENA_MASK            0x0008  /* DSP1_DBG_CWK_ENA */
#define WM5100_DSP1_DBG_CWK_ENA_SHIFT                3  /* DSP1_DBG_CWK_ENA */
#define WM5100_DSP1_DBG_CWK_ENA_WIDTH                1  /* DSP1_DBG_CWK_ENA */
#define WM5100_DSP1_SYS_ENA                     0x0004  /* DSP1_SYS_ENA */
#define WM5100_DSP1_SYS_ENA_MASK                0x0004  /* DSP1_SYS_ENA */
#define WM5100_DSP1_SYS_ENA_SHIFT                    2  /* DSP1_SYS_ENA */
#define WM5100_DSP1_SYS_ENA_WIDTH                    1  /* DSP1_SYS_ENA */
#define WM5100_DSP1_COWE_ENA                    0x0002  /* DSP1_COWE_ENA */
#define WM5100_DSP1_COWE_ENA_MASK               0x0002  /* DSP1_COWE_ENA */
#define WM5100_DSP1_COWE_ENA_SHIFT                   1  /* DSP1_COWE_ENA */
#define WM5100_DSP1_COWE_ENA_WIDTH                   1  /* DSP1_COWE_ENA */
#define WM5100_DSP1_STAWT                       0x0001  /* DSP1_STAWT */
#define WM5100_DSP1_STAWT_MASK                  0x0001  /* DSP1_STAWT */
#define WM5100_DSP1_STAWT_SHIFT                      0  /* DSP1_STAWT */
#define WM5100_DSP1_STAWT_WIDTH                      1  /* DSP1_STAWT */

/*
 * W4388 (0x1124) - DSP3 Contwow 30
 */
#define WM5100_DSP3_WATE_MASK                   0xC000  /* DSP3_WATE - [15:14] */
#define WM5100_DSP3_WATE_SHIFT                      14  /* DSP3_WATE - [15:14] */
#define WM5100_DSP3_WATE_WIDTH                       2  /* DSP3_WATE - [15:14] */
#define WM5100_DSP3_DBG_CWK_ENA                 0x0008  /* DSP3_DBG_CWK_ENA */
#define WM5100_DSP3_DBG_CWK_ENA_MASK            0x0008  /* DSP3_DBG_CWK_ENA */
#define WM5100_DSP3_DBG_CWK_ENA_SHIFT                3  /* DSP3_DBG_CWK_ENA */
#define WM5100_DSP3_DBG_CWK_ENA_WIDTH                1  /* DSP3_DBG_CWK_ENA */
#define WM5100_DSP3_SYS_ENA                     0x0004  /* DSP3_SYS_ENA */
#define WM5100_DSP3_SYS_ENA_MASK                0x0004  /* DSP3_SYS_ENA */
#define WM5100_DSP3_SYS_ENA_SHIFT                    2  /* DSP3_SYS_ENA */
#define WM5100_DSP3_SYS_ENA_WIDTH                    1  /* DSP3_SYS_ENA */
#define WM5100_DSP3_COWE_ENA                    0x0002  /* DSP3_COWE_ENA */
#define WM5100_DSP3_COWE_ENA_MASK               0x0002  /* DSP3_COWE_ENA */
#define WM5100_DSP3_COWE_ENA_SHIFT                   1  /* DSP3_COWE_ENA */
#define WM5100_DSP3_COWE_ENA_WIDTH                   1  /* DSP3_COWE_ENA */
#define WM5100_DSP3_STAWT                       0x0001  /* DSP3_STAWT */
#define WM5100_DSP3_STAWT_MASK                  0x0001  /* DSP3_STAWT */
#define WM5100_DSP3_STAWT_SHIFT                      0  /* DSP3_STAWT */
#define WM5100_DSP3_STAWT_WIDTH                      1  /* DSP3_STAWT */

/*
 * W16384 (0x4000) - DSP1 DM 0
 */
#define WM5100_DSP1_DM_STAWT_1_MASK             0x00FF  /* DSP1_DM_STAWT - [7:0] */
#define WM5100_DSP1_DM_STAWT_1_SHIFT                 0  /* DSP1_DM_STAWT - [7:0] */
#define WM5100_DSP1_DM_STAWT_1_WIDTH                 8  /* DSP1_DM_STAWT - [7:0] */

/*
 * W16385 (0x4001) - DSP1 DM 1
 */
#define WM5100_DSP1_DM_STAWT_MASK               0xFFFF  /* DSP1_DM_STAWT - [15:0] */
#define WM5100_DSP1_DM_STAWT_SHIFT                   0  /* DSP1_DM_STAWT - [15:0] */
#define WM5100_DSP1_DM_STAWT_WIDTH                  16  /* DSP1_DM_STAWT - [15:0] */

/*
 * W16386 (0x4002) - DSP1 DM 2
 */
#define WM5100_DSP1_DM_1_1_MASK                 0x00FF  /* DSP1_DM_1 - [7:0] */
#define WM5100_DSP1_DM_1_1_SHIFT                     0  /* DSP1_DM_1 - [7:0] */
#define WM5100_DSP1_DM_1_1_WIDTH                     8  /* DSP1_DM_1 - [7:0] */

/*
 * W16387 (0x4003) - DSP1 DM 3
 */
#define WM5100_DSP1_DM_1_MASK                   0xFFFF  /* DSP1_DM_1 - [15:0] */
#define WM5100_DSP1_DM_1_SHIFT                       0  /* DSP1_DM_1 - [15:0] */
#define WM5100_DSP1_DM_1_WIDTH                      16  /* DSP1_DM_1 - [15:0] */

/*
 * W16892 (0x41FC) - DSP1 DM 508
 */
#define WM5100_DSP1_DM_254_1_MASK               0x00FF  /* DSP1_DM_254 - [7:0] */
#define WM5100_DSP1_DM_254_1_SHIFT                   0  /* DSP1_DM_254 - [7:0] */
#define WM5100_DSP1_DM_254_1_WIDTH                   8  /* DSP1_DM_254 - [7:0] */

/*
 * W16893 (0x41FD) - DSP1 DM 509
 */
#define WM5100_DSP1_DM_254_MASK                 0xFFFF  /* DSP1_DM_254 - [15:0] */
#define WM5100_DSP1_DM_254_SHIFT                     0  /* DSP1_DM_254 - [15:0] */
#define WM5100_DSP1_DM_254_WIDTH                    16  /* DSP1_DM_254 - [15:0] */

/*
 * W16894 (0x41FE) - DSP1 DM 510
 */
#define WM5100_DSP1_DM_END_1_MASK               0x00FF  /* DSP1_DM_END - [7:0] */
#define WM5100_DSP1_DM_END_1_SHIFT                   0  /* DSP1_DM_END - [7:0] */
#define WM5100_DSP1_DM_END_1_WIDTH                   8  /* DSP1_DM_END - [7:0] */

/*
 * W16895 (0x41FF) - DSP1 DM 511
 */
#define WM5100_DSP1_DM_END_MASK                 0xFFFF  /* DSP1_DM_END - [15:0] */
#define WM5100_DSP1_DM_END_SHIFT                     0  /* DSP1_DM_END - [15:0] */
#define WM5100_DSP1_DM_END_WIDTH                    16  /* DSP1_DM_END - [15:0] */

/*
 * W18432 (0x4800) - DSP1 PM 0
 */
#define WM5100_DSP1_PM_STAWT_2_MASK             0x00FF  /* DSP1_PM_STAWT - [7:0] */
#define WM5100_DSP1_PM_STAWT_2_SHIFT                 0  /* DSP1_PM_STAWT - [7:0] */
#define WM5100_DSP1_PM_STAWT_2_WIDTH                 8  /* DSP1_PM_STAWT - [7:0] */

/*
 * W18433 (0x4801) - DSP1 PM 1
 */
#define WM5100_DSP1_PM_STAWT_1_MASK             0xFFFF  /* DSP1_PM_STAWT - [15:0] */
#define WM5100_DSP1_PM_STAWT_1_SHIFT                 0  /* DSP1_PM_STAWT - [15:0] */
#define WM5100_DSP1_PM_STAWT_1_WIDTH                16  /* DSP1_PM_STAWT - [15:0] */

/*
 * W18434 (0x4802) - DSP1 PM 2
 */
#define WM5100_DSP1_PM_STAWT_MASK               0xFFFF  /* DSP1_PM_STAWT - [15:0] */
#define WM5100_DSP1_PM_STAWT_SHIFT                   0  /* DSP1_PM_STAWT - [15:0] */
#define WM5100_DSP1_PM_STAWT_WIDTH                  16  /* DSP1_PM_STAWT - [15:0] */

/*
 * W18435 (0x4803) - DSP1 PM 3
 */
#define WM5100_DSP1_PM_1_2_MASK                 0x00FF  /* DSP1_PM_1 - [7:0] */
#define WM5100_DSP1_PM_1_2_SHIFT                     0  /* DSP1_PM_1 - [7:0] */
#define WM5100_DSP1_PM_1_2_WIDTH                     8  /* DSP1_PM_1 - [7:0] */

/*
 * W18436 (0x4804) - DSP1 PM 4
 */
#define WM5100_DSP1_PM_1_1_MASK                 0xFFFF  /* DSP1_PM_1 - [15:0] */
#define WM5100_DSP1_PM_1_1_SHIFT                     0  /* DSP1_PM_1 - [15:0] */
#define WM5100_DSP1_PM_1_1_WIDTH                    16  /* DSP1_PM_1 - [15:0] */

/*
 * W18437 (0x4805) - DSP1 PM 5
 */
#define WM5100_DSP1_PM_1_MASK                   0xFFFF  /* DSP1_PM_1 - [15:0] */
#define WM5100_DSP1_PM_1_SHIFT                       0  /* DSP1_PM_1 - [15:0] */
#define WM5100_DSP1_PM_1_WIDTH                      16  /* DSP1_PM_1 - [15:0] */

/*
 * W19962 (0x4DFA) - DSP1 PM 1530
 */
#define WM5100_DSP1_PM_510_2_MASK               0x00FF  /* DSP1_PM_510 - [7:0] */
#define WM5100_DSP1_PM_510_2_SHIFT                   0  /* DSP1_PM_510 - [7:0] */
#define WM5100_DSP1_PM_510_2_WIDTH                   8  /* DSP1_PM_510 - [7:0] */

/*
 * W19963 (0x4DFB) - DSP1 PM 1531
 */
#define WM5100_DSP1_PM_510_1_MASK               0xFFFF  /* DSP1_PM_510 - [15:0] */
#define WM5100_DSP1_PM_510_1_SHIFT                   0  /* DSP1_PM_510 - [15:0] */
#define WM5100_DSP1_PM_510_1_WIDTH                  16  /* DSP1_PM_510 - [15:0] */

/*
 * W19964 (0x4DFC) - DSP1 PM 1532
 */
#define WM5100_DSP1_PM_510_MASK                 0xFFFF  /* DSP1_PM_510 - [15:0] */
#define WM5100_DSP1_PM_510_SHIFT                     0  /* DSP1_PM_510 - [15:0] */
#define WM5100_DSP1_PM_510_WIDTH                    16  /* DSP1_PM_510 - [15:0] */

/*
 * W19965 (0x4DFD) - DSP1 PM 1533
 */
#define WM5100_DSP1_PM_END_2_MASK               0x00FF  /* DSP1_PM_END - [7:0] */
#define WM5100_DSP1_PM_END_2_SHIFT                   0  /* DSP1_PM_END - [7:0] */
#define WM5100_DSP1_PM_END_2_WIDTH                   8  /* DSP1_PM_END - [7:0] */

/*
 * W19966 (0x4DFE) - DSP1 PM 1534
 */
#define WM5100_DSP1_PM_END_1_MASK               0xFFFF  /* DSP1_PM_END - [15:0] */
#define WM5100_DSP1_PM_END_1_SHIFT                   0  /* DSP1_PM_END - [15:0] */
#define WM5100_DSP1_PM_END_1_WIDTH                  16  /* DSP1_PM_END - [15:0] */

/*
 * W19967 (0x4DFF) - DSP1 PM 1535
 */
#define WM5100_DSP1_PM_END_MASK                 0xFFFF  /* DSP1_PM_END - [15:0] */
#define WM5100_DSP1_PM_END_SHIFT                     0  /* DSP1_PM_END - [15:0] */
#define WM5100_DSP1_PM_END_WIDTH                    16  /* DSP1_PM_END - [15:0] */

/*
 * W20480 (0x5000) - DSP1 ZM 0
 */
#define WM5100_DSP1_ZM_STAWT_1_MASK             0x00FF  /* DSP1_ZM_STAWT - [7:0] */
#define WM5100_DSP1_ZM_STAWT_1_SHIFT                 0  /* DSP1_ZM_STAWT - [7:0] */
#define WM5100_DSP1_ZM_STAWT_1_WIDTH                 8  /* DSP1_ZM_STAWT - [7:0] */

/*
 * W20481 (0x5001) - DSP1 ZM 1
 */
#define WM5100_DSP1_ZM_STAWT_MASK               0xFFFF  /* DSP1_ZM_STAWT - [15:0] */
#define WM5100_DSP1_ZM_STAWT_SHIFT                   0  /* DSP1_ZM_STAWT - [15:0] */
#define WM5100_DSP1_ZM_STAWT_WIDTH                  16  /* DSP1_ZM_STAWT - [15:0] */

/*
 * W20482 (0x5002) - DSP1 ZM 2
 */
#define WM5100_DSP1_ZM_1_1_MASK                 0x00FF  /* DSP1_ZM_1 - [7:0] */
#define WM5100_DSP1_ZM_1_1_SHIFT                     0  /* DSP1_ZM_1 - [7:0] */
#define WM5100_DSP1_ZM_1_1_WIDTH                     8  /* DSP1_ZM_1 - [7:0] */

/*
 * W20483 (0x5003) - DSP1 ZM 3
 */
#define WM5100_DSP1_ZM_1_MASK                   0xFFFF  /* DSP1_ZM_1 - [15:0] */
#define WM5100_DSP1_ZM_1_SHIFT                       0  /* DSP1_ZM_1 - [15:0] */
#define WM5100_DSP1_ZM_1_WIDTH                      16  /* DSP1_ZM_1 - [15:0] */

/*
 * W22524 (0x57FC) - DSP1 ZM 2044
 */
#define WM5100_DSP1_ZM_1022_1_MASK              0x00FF  /* DSP1_ZM_1022 - [7:0] */
#define WM5100_DSP1_ZM_1022_1_SHIFT                  0  /* DSP1_ZM_1022 - [7:0] */
#define WM5100_DSP1_ZM_1022_1_WIDTH                  8  /* DSP1_ZM_1022 - [7:0] */

/*
 * W22525 (0x57FD) - DSP1 ZM 2045
 */
#define WM5100_DSP1_ZM_1022_MASK                0xFFFF  /* DSP1_ZM_1022 - [15:0] */
#define WM5100_DSP1_ZM_1022_SHIFT                    0  /* DSP1_ZM_1022 - [15:0] */
#define WM5100_DSP1_ZM_1022_WIDTH                   16  /* DSP1_ZM_1022 - [15:0] */

/*
 * W22526 (0x57FE) - DSP1 ZM 2046
 */
#define WM5100_DSP1_ZM_END_1_MASK               0x00FF  /* DSP1_ZM_END - [7:0] */
#define WM5100_DSP1_ZM_END_1_SHIFT                   0  /* DSP1_ZM_END - [7:0] */
#define WM5100_DSP1_ZM_END_1_WIDTH                   8  /* DSP1_ZM_END - [7:0] */

/*
 * W22527 (0x57FF) - DSP1 ZM 2047
 */
#define WM5100_DSP1_ZM_END_MASK                 0xFFFF  /* DSP1_ZM_END - [15:0] */
#define WM5100_DSP1_ZM_END_SHIFT                     0  /* DSP1_ZM_END - [15:0] */
#define WM5100_DSP1_ZM_END_WIDTH                    16  /* DSP1_ZM_END - [15:0] */

/*
 * W24576 (0x6000) - DSP2 DM 0
 */
#define WM5100_DSP2_DM_STAWT_1_MASK             0x00FF  /* DSP2_DM_STAWT - [7:0] */
#define WM5100_DSP2_DM_STAWT_1_SHIFT                 0  /* DSP2_DM_STAWT - [7:0] */
#define WM5100_DSP2_DM_STAWT_1_WIDTH                 8  /* DSP2_DM_STAWT - [7:0] */

/*
 * W24577 (0x6001) - DSP2 DM 1
 */
#define WM5100_DSP2_DM_STAWT_MASK               0xFFFF  /* DSP2_DM_STAWT - [15:0] */
#define WM5100_DSP2_DM_STAWT_SHIFT                   0  /* DSP2_DM_STAWT - [15:0] */
#define WM5100_DSP2_DM_STAWT_WIDTH                  16  /* DSP2_DM_STAWT - [15:0] */

/*
 * W24578 (0x6002) - DSP2 DM 2
 */
#define WM5100_DSP2_DM_1_1_MASK                 0x00FF  /* DSP2_DM_1 - [7:0] */
#define WM5100_DSP2_DM_1_1_SHIFT                     0  /* DSP2_DM_1 - [7:0] */
#define WM5100_DSP2_DM_1_1_WIDTH                     8  /* DSP2_DM_1 - [7:0] */

/*
 * W24579 (0x6003) - DSP2 DM 3
 */
#define WM5100_DSP2_DM_1_MASK                   0xFFFF  /* DSP2_DM_1 - [15:0] */
#define WM5100_DSP2_DM_1_SHIFT                       0  /* DSP2_DM_1 - [15:0] */
#define WM5100_DSP2_DM_1_WIDTH                      16  /* DSP2_DM_1 - [15:0] */

/*
 * W25084 (0x61FC) - DSP2 DM 508
 */
#define WM5100_DSP2_DM_254_1_MASK               0x00FF  /* DSP2_DM_254 - [7:0] */
#define WM5100_DSP2_DM_254_1_SHIFT                   0  /* DSP2_DM_254 - [7:0] */
#define WM5100_DSP2_DM_254_1_WIDTH                   8  /* DSP2_DM_254 - [7:0] */

/*
 * W25085 (0x61FD) - DSP2 DM 509
 */
#define WM5100_DSP2_DM_254_MASK                 0xFFFF  /* DSP2_DM_254 - [15:0] */
#define WM5100_DSP2_DM_254_SHIFT                     0  /* DSP2_DM_254 - [15:0] */
#define WM5100_DSP2_DM_254_WIDTH                    16  /* DSP2_DM_254 - [15:0] */

/*
 * W25086 (0x61FE) - DSP2 DM 510
 */
#define WM5100_DSP2_DM_END_1_MASK               0x00FF  /* DSP2_DM_END - [7:0] */
#define WM5100_DSP2_DM_END_1_SHIFT                   0  /* DSP2_DM_END - [7:0] */
#define WM5100_DSP2_DM_END_1_WIDTH                   8  /* DSP2_DM_END - [7:0] */

/*
 * W25087 (0x61FF) - DSP2 DM 511
 */
#define WM5100_DSP2_DM_END_MASK                 0xFFFF  /* DSP2_DM_END - [15:0] */
#define WM5100_DSP2_DM_END_SHIFT                     0  /* DSP2_DM_END - [15:0] */
#define WM5100_DSP2_DM_END_WIDTH                    16  /* DSP2_DM_END - [15:0] */

/*
 * W26624 (0x6800) - DSP2 PM 0
 */
#define WM5100_DSP2_PM_STAWT_2_MASK             0x00FF  /* DSP2_PM_STAWT - [7:0] */
#define WM5100_DSP2_PM_STAWT_2_SHIFT                 0  /* DSP2_PM_STAWT - [7:0] */
#define WM5100_DSP2_PM_STAWT_2_WIDTH                 8  /* DSP2_PM_STAWT - [7:0] */

/*
 * W26625 (0x6801) - DSP2 PM 1
 */
#define WM5100_DSP2_PM_STAWT_1_MASK             0xFFFF  /* DSP2_PM_STAWT - [15:0] */
#define WM5100_DSP2_PM_STAWT_1_SHIFT                 0  /* DSP2_PM_STAWT - [15:0] */
#define WM5100_DSP2_PM_STAWT_1_WIDTH                16  /* DSP2_PM_STAWT - [15:0] */

/*
 * W26626 (0x6802) - DSP2 PM 2
 */
#define WM5100_DSP2_PM_STAWT_MASK               0xFFFF  /* DSP2_PM_STAWT - [15:0] */
#define WM5100_DSP2_PM_STAWT_SHIFT                   0  /* DSP2_PM_STAWT - [15:0] */
#define WM5100_DSP2_PM_STAWT_WIDTH                  16  /* DSP2_PM_STAWT - [15:0] */

/*
 * W26627 (0x6803) - DSP2 PM 3
 */
#define WM5100_DSP2_PM_1_2_MASK                 0x00FF  /* DSP2_PM_1 - [7:0] */
#define WM5100_DSP2_PM_1_2_SHIFT                     0  /* DSP2_PM_1 - [7:0] */
#define WM5100_DSP2_PM_1_2_WIDTH                     8  /* DSP2_PM_1 - [7:0] */

/*
 * W26628 (0x6804) - DSP2 PM 4
 */
#define WM5100_DSP2_PM_1_1_MASK                 0xFFFF  /* DSP2_PM_1 - [15:0] */
#define WM5100_DSP2_PM_1_1_SHIFT                     0  /* DSP2_PM_1 - [15:0] */
#define WM5100_DSP2_PM_1_1_WIDTH                    16  /* DSP2_PM_1 - [15:0] */

/*
 * W26629 (0x6805) - DSP2 PM 5
 */
#define WM5100_DSP2_PM_1_MASK                   0xFFFF  /* DSP2_PM_1 - [15:0] */
#define WM5100_DSP2_PM_1_SHIFT                       0  /* DSP2_PM_1 - [15:0] */
#define WM5100_DSP2_PM_1_WIDTH                      16  /* DSP2_PM_1 - [15:0] */

/*
 * W28154 (0x6DFA) - DSP2 PM 1530
 */
#define WM5100_DSP2_PM_510_2_MASK               0x00FF  /* DSP2_PM_510 - [7:0] */
#define WM5100_DSP2_PM_510_2_SHIFT                   0  /* DSP2_PM_510 - [7:0] */
#define WM5100_DSP2_PM_510_2_WIDTH                   8  /* DSP2_PM_510 - [7:0] */

/*
 * W28155 (0x6DFB) - DSP2 PM 1531
 */
#define WM5100_DSP2_PM_510_1_MASK               0xFFFF  /* DSP2_PM_510 - [15:0] */
#define WM5100_DSP2_PM_510_1_SHIFT                   0  /* DSP2_PM_510 - [15:0] */
#define WM5100_DSP2_PM_510_1_WIDTH                  16  /* DSP2_PM_510 - [15:0] */

/*
 * W28156 (0x6DFC) - DSP2 PM 1532
 */
#define WM5100_DSP2_PM_510_MASK                 0xFFFF  /* DSP2_PM_510 - [15:0] */
#define WM5100_DSP2_PM_510_SHIFT                     0  /* DSP2_PM_510 - [15:0] */
#define WM5100_DSP2_PM_510_WIDTH                    16  /* DSP2_PM_510 - [15:0] */

/*
 * W28157 (0x6DFD) - DSP2 PM 1533
 */
#define WM5100_DSP2_PM_END_2_MASK               0x00FF  /* DSP2_PM_END - [7:0] */
#define WM5100_DSP2_PM_END_2_SHIFT                   0  /* DSP2_PM_END - [7:0] */
#define WM5100_DSP2_PM_END_2_WIDTH                   8  /* DSP2_PM_END - [7:0] */

/*
 * W28158 (0x6DFE) - DSP2 PM 1534
 */
#define WM5100_DSP2_PM_END_1_MASK               0xFFFF  /* DSP2_PM_END - [15:0] */
#define WM5100_DSP2_PM_END_1_SHIFT                   0  /* DSP2_PM_END - [15:0] */
#define WM5100_DSP2_PM_END_1_WIDTH                  16  /* DSP2_PM_END - [15:0] */

/*
 * W28159 (0x6DFF) - DSP2 PM 1535
 */
#define WM5100_DSP2_PM_END_MASK                 0xFFFF  /* DSP2_PM_END - [15:0] */
#define WM5100_DSP2_PM_END_SHIFT                     0  /* DSP2_PM_END - [15:0] */
#define WM5100_DSP2_PM_END_WIDTH                    16  /* DSP2_PM_END - [15:0] */

/*
 * W28672 (0x7000) - DSP2 ZM 0
 */
#define WM5100_DSP2_ZM_STAWT_1_MASK             0x00FF  /* DSP2_ZM_STAWT - [7:0] */
#define WM5100_DSP2_ZM_STAWT_1_SHIFT                 0  /* DSP2_ZM_STAWT - [7:0] */
#define WM5100_DSP2_ZM_STAWT_1_WIDTH                 8  /* DSP2_ZM_STAWT - [7:0] */

/*
 * W28673 (0x7001) - DSP2 ZM 1
 */
#define WM5100_DSP2_ZM_STAWT_MASK               0xFFFF  /* DSP2_ZM_STAWT - [15:0] */
#define WM5100_DSP2_ZM_STAWT_SHIFT                   0  /* DSP2_ZM_STAWT - [15:0] */
#define WM5100_DSP2_ZM_STAWT_WIDTH                  16  /* DSP2_ZM_STAWT - [15:0] */

/*
 * W28674 (0x7002) - DSP2 ZM 2
 */
#define WM5100_DSP2_ZM_1_1_MASK                 0x00FF  /* DSP2_ZM_1 - [7:0] */
#define WM5100_DSP2_ZM_1_1_SHIFT                     0  /* DSP2_ZM_1 - [7:0] */
#define WM5100_DSP2_ZM_1_1_WIDTH                     8  /* DSP2_ZM_1 - [7:0] */

/*
 * W28675 (0x7003) - DSP2 ZM 3
 */
#define WM5100_DSP2_ZM_1_MASK                   0xFFFF  /* DSP2_ZM_1 - [15:0] */
#define WM5100_DSP2_ZM_1_SHIFT                       0  /* DSP2_ZM_1 - [15:0] */
#define WM5100_DSP2_ZM_1_WIDTH                      16  /* DSP2_ZM_1 - [15:0] */

/*
 * W30716 (0x77FC) - DSP2 ZM 2044
 */
#define WM5100_DSP2_ZM_1022_1_MASK              0x00FF  /* DSP2_ZM_1022 - [7:0] */
#define WM5100_DSP2_ZM_1022_1_SHIFT                  0  /* DSP2_ZM_1022 - [7:0] */
#define WM5100_DSP2_ZM_1022_1_WIDTH                  8  /* DSP2_ZM_1022 - [7:0] */

/*
 * W30717 (0x77FD) - DSP2 ZM 2045
 */
#define WM5100_DSP2_ZM_1022_MASK                0xFFFF  /* DSP2_ZM_1022 - [15:0] */
#define WM5100_DSP2_ZM_1022_SHIFT                    0  /* DSP2_ZM_1022 - [15:0] */
#define WM5100_DSP2_ZM_1022_WIDTH                   16  /* DSP2_ZM_1022 - [15:0] */

/*
 * W30718 (0x77FE) - DSP2 ZM 2046
 */
#define WM5100_DSP2_ZM_END_1_MASK               0x00FF  /* DSP2_ZM_END - [7:0] */
#define WM5100_DSP2_ZM_END_1_SHIFT                   0  /* DSP2_ZM_END - [7:0] */
#define WM5100_DSP2_ZM_END_1_WIDTH                   8  /* DSP2_ZM_END - [7:0] */

/*
 * W30719 (0x77FF) - DSP2 ZM 2047
 */
#define WM5100_DSP2_ZM_END_MASK                 0xFFFF  /* DSP2_ZM_END - [15:0] */
#define WM5100_DSP2_ZM_END_SHIFT                     0  /* DSP2_ZM_END - [15:0] */
#define WM5100_DSP2_ZM_END_WIDTH                    16  /* DSP2_ZM_END - [15:0] */

/*
 * W32768 (0x8000) - DSP3 DM 0
 */
#define WM5100_DSP3_DM_STAWT_1_MASK             0x00FF  /* DSP3_DM_STAWT - [7:0] */
#define WM5100_DSP3_DM_STAWT_1_SHIFT                 0  /* DSP3_DM_STAWT - [7:0] */
#define WM5100_DSP3_DM_STAWT_1_WIDTH                 8  /* DSP3_DM_STAWT - [7:0] */

/*
 * W32769 (0x8001) - DSP3 DM 1
 */
#define WM5100_DSP3_DM_STAWT_MASK               0xFFFF  /* DSP3_DM_STAWT - [15:0] */
#define WM5100_DSP3_DM_STAWT_SHIFT                   0  /* DSP3_DM_STAWT - [15:0] */
#define WM5100_DSP3_DM_STAWT_WIDTH                  16  /* DSP3_DM_STAWT - [15:0] */

/*
 * W32770 (0x8002) - DSP3 DM 2
 */
#define WM5100_DSP3_DM_1_1_MASK                 0x00FF  /* DSP3_DM_1 - [7:0] */
#define WM5100_DSP3_DM_1_1_SHIFT                     0  /* DSP3_DM_1 - [7:0] */
#define WM5100_DSP3_DM_1_1_WIDTH                     8  /* DSP3_DM_1 - [7:0] */

/*
 * W32771 (0x8003) - DSP3 DM 3
 */
#define WM5100_DSP3_DM_1_MASK                   0xFFFF  /* DSP3_DM_1 - [15:0] */
#define WM5100_DSP3_DM_1_SHIFT                       0  /* DSP3_DM_1 - [15:0] */
#define WM5100_DSP3_DM_1_WIDTH                      16  /* DSP3_DM_1 - [15:0] */

/*
 * W33276 (0x81FC) - DSP3 DM 508
 */
#define WM5100_DSP3_DM_254_1_MASK               0x00FF  /* DSP3_DM_254 - [7:0] */
#define WM5100_DSP3_DM_254_1_SHIFT                   0  /* DSP3_DM_254 - [7:0] */
#define WM5100_DSP3_DM_254_1_WIDTH                   8  /* DSP3_DM_254 - [7:0] */

/*
 * W33277 (0x81FD) - DSP3 DM 509
 */
#define WM5100_DSP3_DM_254_MASK                 0xFFFF  /* DSP3_DM_254 - [15:0] */
#define WM5100_DSP3_DM_254_SHIFT                     0  /* DSP3_DM_254 - [15:0] */
#define WM5100_DSP3_DM_254_WIDTH                    16  /* DSP3_DM_254 - [15:0] */

/*
 * W33278 (0x81FE) - DSP3 DM 510
 */
#define WM5100_DSP3_DM_END_1_MASK               0x00FF  /* DSP3_DM_END - [7:0] */
#define WM5100_DSP3_DM_END_1_SHIFT                   0  /* DSP3_DM_END - [7:0] */
#define WM5100_DSP3_DM_END_1_WIDTH                   8  /* DSP3_DM_END - [7:0] */

/*
 * W33279 (0x81FF) - DSP3 DM 511
 */
#define WM5100_DSP3_DM_END_MASK                 0xFFFF  /* DSP3_DM_END - [15:0] */
#define WM5100_DSP3_DM_END_SHIFT                     0  /* DSP3_DM_END - [15:0] */
#define WM5100_DSP3_DM_END_WIDTH                    16  /* DSP3_DM_END - [15:0] */

/*
 * W34816 (0x8800) - DSP3 PM 0
 */
#define WM5100_DSP3_PM_STAWT_2_MASK             0x00FF  /* DSP3_PM_STAWT - [7:0] */
#define WM5100_DSP3_PM_STAWT_2_SHIFT                 0  /* DSP3_PM_STAWT - [7:0] */
#define WM5100_DSP3_PM_STAWT_2_WIDTH                 8  /* DSP3_PM_STAWT - [7:0] */

/*
 * W34817 (0x8801) - DSP3 PM 1
 */
#define WM5100_DSP3_PM_STAWT_1_MASK             0xFFFF  /* DSP3_PM_STAWT - [15:0] */
#define WM5100_DSP3_PM_STAWT_1_SHIFT                 0  /* DSP3_PM_STAWT - [15:0] */
#define WM5100_DSP3_PM_STAWT_1_WIDTH                16  /* DSP3_PM_STAWT - [15:0] */

/*
 * W34818 (0x8802) - DSP3 PM 2
 */
#define WM5100_DSP3_PM_STAWT_MASK               0xFFFF  /* DSP3_PM_STAWT - [15:0] */
#define WM5100_DSP3_PM_STAWT_SHIFT                   0  /* DSP3_PM_STAWT - [15:0] */
#define WM5100_DSP3_PM_STAWT_WIDTH                  16  /* DSP3_PM_STAWT - [15:0] */

/*
 * W34819 (0x8803) - DSP3 PM 3
 */
#define WM5100_DSP3_PM_1_2_MASK                 0x00FF  /* DSP3_PM_1 - [7:0] */
#define WM5100_DSP3_PM_1_2_SHIFT                     0  /* DSP3_PM_1 - [7:0] */
#define WM5100_DSP3_PM_1_2_WIDTH                     8  /* DSP3_PM_1 - [7:0] */

/*
 * W34820 (0x8804) - DSP3 PM 4
 */
#define WM5100_DSP3_PM_1_1_MASK                 0xFFFF  /* DSP3_PM_1 - [15:0] */
#define WM5100_DSP3_PM_1_1_SHIFT                     0  /* DSP3_PM_1 - [15:0] */
#define WM5100_DSP3_PM_1_1_WIDTH                    16  /* DSP3_PM_1 - [15:0] */

/*
 * W34821 (0x8805) - DSP3 PM 5
 */
#define WM5100_DSP3_PM_1_MASK                   0xFFFF  /* DSP3_PM_1 - [15:0] */
#define WM5100_DSP3_PM_1_SHIFT                       0  /* DSP3_PM_1 - [15:0] */
#define WM5100_DSP3_PM_1_WIDTH                      16  /* DSP3_PM_1 - [15:0] */

/*
 * W36346 (0x8DFA) - DSP3 PM 1530
 */
#define WM5100_DSP3_PM_510_2_MASK               0x00FF  /* DSP3_PM_510 - [7:0] */
#define WM5100_DSP3_PM_510_2_SHIFT                   0  /* DSP3_PM_510 - [7:0] */
#define WM5100_DSP3_PM_510_2_WIDTH                   8  /* DSP3_PM_510 - [7:0] */

/*
 * W36347 (0x8DFB) - DSP3 PM 1531
 */
#define WM5100_DSP3_PM_510_1_MASK               0xFFFF  /* DSP3_PM_510 - [15:0] */
#define WM5100_DSP3_PM_510_1_SHIFT                   0  /* DSP3_PM_510 - [15:0] */
#define WM5100_DSP3_PM_510_1_WIDTH                  16  /* DSP3_PM_510 - [15:0] */

/*
 * W36348 (0x8DFC) - DSP3 PM 1532
 */
#define WM5100_DSP3_PM_510_MASK                 0xFFFF  /* DSP3_PM_510 - [15:0] */
#define WM5100_DSP3_PM_510_SHIFT                     0  /* DSP3_PM_510 - [15:0] */
#define WM5100_DSP3_PM_510_WIDTH                    16  /* DSP3_PM_510 - [15:0] */

/*
 * W36349 (0x8DFD) - DSP3 PM 1533
 */
#define WM5100_DSP3_PM_END_2_MASK               0x00FF  /* DSP3_PM_END - [7:0] */
#define WM5100_DSP3_PM_END_2_SHIFT                   0  /* DSP3_PM_END - [7:0] */
#define WM5100_DSP3_PM_END_2_WIDTH                   8  /* DSP3_PM_END - [7:0] */

/*
 * W36350 (0x8DFE) - DSP3 PM 1534
 */
#define WM5100_DSP3_PM_END_1_MASK               0xFFFF  /* DSP3_PM_END - [15:0] */
#define WM5100_DSP3_PM_END_1_SHIFT                   0  /* DSP3_PM_END - [15:0] */
#define WM5100_DSP3_PM_END_1_WIDTH                  16  /* DSP3_PM_END - [15:0] */

/*
 * W36351 (0x8DFF) - DSP3 PM 1535
 */
#define WM5100_DSP3_PM_END_MASK                 0xFFFF  /* DSP3_PM_END - [15:0] */
#define WM5100_DSP3_PM_END_SHIFT                     0  /* DSP3_PM_END - [15:0] */
#define WM5100_DSP3_PM_END_WIDTH                    16  /* DSP3_PM_END - [15:0] */

/*
 * W36864 (0x9000) - DSP3 ZM 0
 */
#define WM5100_DSP3_ZM_STAWT_1_MASK             0x00FF  /* DSP3_ZM_STAWT - [7:0] */
#define WM5100_DSP3_ZM_STAWT_1_SHIFT                 0  /* DSP3_ZM_STAWT - [7:0] */
#define WM5100_DSP3_ZM_STAWT_1_WIDTH                 8  /* DSP3_ZM_STAWT - [7:0] */

/*
 * W36865 (0x9001) - DSP3 ZM 1
 */
#define WM5100_DSP3_ZM_STAWT_MASK               0xFFFF  /* DSP3_ZM_STAWT - [15:0] */
#define WM5100_DSP3_ZM_STAWT_SHIFT                   0  /* DSP3_ZM_STAWT - [15:0] */
#define WM5100_DSP3_ZM_STAWT_WIDTH                  16  /* DSP3_ZM_STAWT - [15:0] */

/*
 * W36866 (0x9002) - DSP3 ZM 2
 */
#define WM5100_DSP3_ZM_1_1_MASK                 0x00FF  /* DSP3_ZM_1 - [7:0] */
#define WM5100_DSP3_ZM_1_1_SHIFT                     0  /* DSP3_ZM_1 - [7:0] */
#define WM5100_DSP3_ZM_1_1_WIDTH                     8  /* DSP3_ZM_1 - [7:0] */

/*
 * W36867 (0x9003) - DSP3 ZM 3
 */
#define WM5100_DSP3_ZM_1_MASK                   0xFFFF  /* DSP3_ZM_1 - [15:0] */
#define WM5100_DSP3_ZM_1_SHIFT                       0  /* DSP3_ZM_1 - [15:0] */
#define WM5100_DSP3_ZM_1_WIDTH                      16  /* DSP3_ZM_1 - [15:0] */

/*
 * W38908 (0x97FC) - DSP3 ZM 2044
 */
#define WM5100_DSP3_ZM_1022_1_MASK              0x00FF  /* DSP3_ZM_1022 - [7:0] */
#define WM5100_DSP3_ZM_1022_1_SHIFT                  0  /* DSP3_ZM_1022 - [7:0] */
#define WM5100_DSP3_ZM_1022_1_WIDTH                  8  /* DSP3_ZM_1022 - [7:0] */

/*
 * W38909 (0x97FD) - DSP3 ZM 2045
 */
#define WM5100_DSP3_ZM_1022_MASK                0xFFFF  /* DSP3_ZM_1022 - [15:0] */
#define WM5100_DSP3_ZM_1022_SHIFT                    0  /* DSP3_ZM_1022 - [15:0] */
#define WM5100_DSP3_ZM_1022_WIDTH                   16  /* DSP3_ZM_1022 - [15:0] */

/*
 * W38910 (0x97FE) - DSP3 ZM 2046
 */
#define WM5100_DSP3_ZM_END_1_MASK               0x00FF  /* DSP3_ZM_END - [7:0] */
#define WM5100_DSP3_ZM_END_1_SHIFT                   0  /* DSP3_ZM_END - [7:0] */
#define WM5100_DSP3_ZM_END_1_WIDTH                   8  /* DSP3_ZM_END - [7:0] */

/*
 * W38911 (0x97FF) - DSP3 ZM 2047
 */
#define WM5100_DSP3_ZM_END_MASK                 0xFFFF  /* DSP3_ZM_END - [15:0] */
#define WM5100_DSP3_ZM_END_SHIFT                     0  /* DSP3_ZM_END - [15:0] */
#define WM5100_DSP3_ZM_END_WIDTH                    16  /* DSP3_ZM_END - [15:0] */

boow wm5100_weadabwe_wegistew(stwuct device *dev, unsigned int weg);
boow wm5100_vowatiwe_wegistew(stwuct device *dev, unsigned int weg);

extewn stwuct weg_defauwt wm5100_weg_defauwts[WM5100_WEGISTEW_COUNT];

#endif
