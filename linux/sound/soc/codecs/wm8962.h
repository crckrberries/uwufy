/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8962.h  --  WM8962 ASoC dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8962_H
#define _WM8962_H

#incwude <asm/types.h>
#incwude <sound/soc.h>

#define WM8962_SYSCWK_MCWK 0
#define WM8962_SYSCWK_FWW  1
#define WM8962_SYSCWK_PWW3 2

#define WM8962_FWW  1

#define WM8962_FWW_MCWK 1
#define WM8962_FWW_BCWK 2
#define WM8962_FWW_OSC  3
#define WM8962_FWW_INT  4

/*
 * Wegistew vawues.
 */
#define WM8962_WEFT_INPUT_VOWUME                0x00
#define WM8962_WIGHT_INPUT_VOWUME               0x01
#define WM8962_HPOUTW_VOWUME                    0x02
#define WM8962_HPOUTW_VOWUME                    0x03
#define WM8962_CWOCKING1                        0x04
#define WM8962_ADC_DAC_CONTWOW_1                0x05
#define WM8962_ADC_DAC_CONTWOW_2                0x06
#define WM8962_AUDIO_INTEWFACE_0                0x07
#define WM8962_CWOCKING2                        0x08
#define WM8962_AUDIO_INTEWFACE_1                0x09
#define WM8962_WEFT_DAC_VOWUME                  0x0A
#define WM8962_WIGHT_DAC_VOWUME                 0x0B
#define WM8962_AUDIO_INTEWFACE_2                0x0E
#define WM8962_SOFTWAWE_WESET                   0x0F
#define WM8962_AWC1                             0x11
#define WM8962_AWC2                             0x12
#define WM8962_AWC3                             0x13
#define WM8962_NOISE_GATE                       0x14
#define WM8962_WEFT_ADC_VOWUME                  0x15
#define WM8962_WIGHT_ADC_VOWUME                 0x16
#define WM8962_ADDITIONAW_CONTWOW_1             0x17
#define WM8962_ADDITIONAW_CONTWOW_2             0x18
#define WM8962_PWW_MGMT_1                       0x19
#define WM8962_PWW_MGMT_2                       0x1A
#define WM8962_ADDITIONAW_CONTWOW_3             0x1B
#define WM8962_ANTI_POP                         0x1C
#define WM8962_CWOCKING_3                       0x1E
#define WM8962_INPUT_MIXEW_CONTWOW_1            0x1F
#define WM8962_WEFT_INPUT_MIXEW_VOWUME          0x20
#define WM8962_WIGHT_INPUT_MIXEW_VOWUME         0x21
#define WM8962_INPUT_MIXEW_CONTWOW_2            0x22
#define WM8962_INPUT_BIAS_CONTWOW               0x23
#define WM8962_WEFT_INPUT_PGA_CONTWOW           0x25
#define WM8962_WIGHT_INPUT_PGA_CONTWOW          0x26
#define WM8962_SPKOUTW_VOWUME                   0x28
#define WM8962_SPKOUTW_VOWUME                   0x29
#define WM8962_THEWMAW_SHUTDOWN_STATUS          0x2F
#define WM8962_ADDITIONAW_CONTWOW_4             0x30
#define WM8962_CWASS_D_CONTWOW_1                0x31
#define WM8962_CWASS_D_CONTWOW_2                0x33
#define WM8962_CWOCKING_4                       0x38
#define WM8962_DAC_DSP_MIXING_1                 0x39
#define WM8962_DAC_DSP_MIXING_2                 0x3A
#define WM8962_DC_SEWVO_0                       0x3C
#define WM8962_DC_SEWVO_1                       0x3D
#define WM8962_DC_SEWVO_4                       0x40
#define WM8962_DC_SEWVO_6                       0x42
#define WM8962_ANAWOGUE_PGA_BIAS                0x44
#define WM8962_ANAWOGUE_HP_0                    0x45
#define WM8962_ANAWOGUE_HP_2                    0x47
#define WM8962_CHAWGE_PUMP_1                    0x48
#define WM8962_CHAWGE_PUMP_B                    0x52
#define WM8962_WWITE_SEQUENCEW_CONTWOW_1        0x57
#define WM8962_WWITE_SEQUENCEW_CONTWOW_2        0x5A
#define WM8962_WWITE_SEQUENCEW_CONTWOW_3        0x5D
#define WM8962_CONTWOW_INTEWFACE                0x5E
#define WM8962_MIXEW_ENABWES                    0x63
#define WM8962_HEADPHONE_MIXEW_1                0x64
#define WM8962_HEADPHONE_MIXEW_2                0x65
#define WM8962_HEADPHONE_MIXEW_3                0x66
#define WM8962_HEADPHONE_MIXEW_4                0x67
#define WM8962_SPEAKEW_MIXEW_1                  0x69
#define WM8962_SPEAKEW_MIXEW_2                  0x6A
#define WM8962_SPEAKEW_MIXEW_3                  0x6B
#define WM8962_SPEAKEW_MIXEW_4                  0x6C
#define WM8962_SPEAKEW_MIXEW_5                  0x6D
#define WM8962_BEEP_GENEWATOW_1                 0x6E
#define WM8962_OSCIWWATOW_TWIM_3                0x73
#define WM8962_OSCIWWATOW_TWIM_4                0x74
#define WM8962_OSCIWWATOW_TWIM_7                0x77
#define WM8962_ANAWOGUE_CWOCKING1               0x7C
#define WM8962_ANAWOGUE_CWOCKING2               0x7D
#define WM8962_ANAWOGUE_CWOCKING3               0x7E
#define WM8962_PWW_SOFTWAWE_WESET               0x7F
#define WM8962_PWW2                             0x81
#define WM8962_PWW_4                            0x83
#define WM8962_PWW_9                            0x88
#define WM8962_PWW_10                           0x89
#define WM8962_PWW_11                           0x8A
#define WM8962_PWW_12                           0x8B
#define WM8962_PWW_13                           0x8C
#define WM8962_PWW_14                           0x8D
#define WM8962_PWW_15                           0x8E
#define WM8962_PWW_16                           0x8F
#define WM8962_FWW_CONTWOW_1                    0x9B
#define WM8962_FWW_CONTWOW_2                    0x9C
#define WM8962_FWW_CONTWOW_3                    0x9D
#define WM8962_FWW_CONTWOW_5                    0x9F
#define WM8962_FWW_CONTWOW_6                    0xA0
#define WM8962_FWW_CONTWOW_7                    0xA1
#define WM8962_FWW_CONTWOW_8                    0xA2
#define WM8962_GENEWAW_TEST_1                   0xFC
#define WM8962_DF1                              0x100
#define WM8962_DF2                              0x101
#define WM8962_DF3                              0x102
#define WM8962_DF4                              0x103
#define WM8962_DF5                              0x104
#define WM8962_DF6                              0x105
#define WM8962_DF7                              0x106
#define WM8962_WHPF1                            0x108
#define WM8962_WHPF2                            0x109
#define WM8962_THWEED1                          0x10C
#define WM8962_THWEED2                          0x10D
#define WM8962_THWEED3                          0x10E
#define WM8962_THWEED4                          0x10F
#define WM8962_DWC_1                            0x114
#define WM8962_DWC_2                            0x115
#define WM8962_DWC_3                            0x116
#define WM8962_DWC_4                            0x117
#define WM8962_DWC_5                            0x118
#define WM8962_TWOOPBACK                        0x11D
#define WM8962_EQ1                              0x14F
#define WM8962_EQ2                              0x150
#define WM8962_EQ3                              0x151
#define WM8962_EQ4                              0x152
#define WM8962_EQ5                              0x153
#define WM8962_EQ6                              0x154
#define WM8962_EQ7                              0x155
#define WM8962_EQ8                              0x156
#define WM8962_EQ9                              0x157
#define WM8962_EQ10                             0x158
#define WM8962_EQ11                             0x159
#define WM8962_EQ12                             0x15A
#define WM8962_EQ13                             0x15B
#define WM8962_EQ14                             0x15C
#define WM8962_EQ15                             0x15D
#define WM8962_EQ16                             0x15E
#define WM8962_EQ17                             0x15F
#define WM8962_EQ18                             0x160
#define WM8962_EQ19                             0x161
#define WM8962_EQ20                             0x162
#define WM8962_EQ21                             0x163
#define WM8962_EQ22                             0x164
#define WM8962_EQ23                             0x165
#define WM8962_EQ24                             0x166
#define WM8962_EQ25                             0x167
#define WM8962_EQ26                             0x168
#define WM8962_EQ27                             0x169
#define WM8962_EQ28                             0x16A
#define WM8962_EQ29                             0x16B
#define WM8962_EQ30                             0x16C
#define WM8962_EQ31                             0x16D
#define WM8962_EQ32                             0x16E
#define WM8962_EQ33                             0x16F
#define WM8962_EQ34                             0x170
#define WM8962_EQ35                             0x171
#define WM8962_EQ36                             0x172
#define WM8962_EQ37                             0x173
#define WM8962_EQ38                             0x174
#define WM8962_EQ39                             0x175
#define WM8962_EQ40                             0x176
#define WM8962_EQ41                             0x177
#define WM8962_GPIO_BASE			0x200
#define WM8962_GPIO_2                           0x201
#define WM8962_GPIO_3                           0x202
#define WM8962_GPIO_5                           0x204
#define WM8962_GPIO_6                           0x205
#define WM8962_INTEWWUPT_STATUS_1               0x230
#define WM8962_INTEWWUPT_STATUS_2               0x231
#define WM8962_INTEWWUPT_STATUS_1_MASK          0x238
#define WM8962_INTEWWUPT_STATUS_2_MASK          0x239
#define WM8962_INTEWWUPT_CONTWOW                0x240
#define WM8962_IWQ_DEBOUNCE                     0x248
#define WM8962_MICINT_SOUWCE_POW                0x24A
#define WM8962_DSP2_POWEW_MANAGEMENT            0x300
#define WM8962_DSP2_EXECCONTWOW                 0x40D
#define WM8962_WWITE_SEQUENCEW_0                0x1000
#define WM8962_WWITE_SEQUENCEW_1                0x1001
#define WM8962_WWITE_SEQUENCEW_2                0x1002
#define WM8962_WWITE_SEQUENCEW_3                0x1003
#define WM8962_WWITE_SEQUENCEW_4                0x1004
#define WM8962_WWITE_SEQUENCEW_5                0x1005
#define WM8962_WWITE_SEQUENCEW_6                0x1006
#define WM8962_WWITE_SEQUENCEW_7                0x1007
#define WM8962_WWITE_SEQUENCEW_8                0x1008
#define WM8962_WWITE_SEQUENCEW_9                0x1009
#define WM8962_WWITE_SEQUENCEW_10               0x100A
#define WM8962_WWITE_SEQUENCEW_11               0x100B
#define WM8962_WWITE_SEQUENCEW_12               0x100C
#define WM8962_WWITE_SEQUENCEW_13               0x100D
#define WM8962_WWITE_SEQUENCEW_14               0x100E
#define WM8962_WWITE_SEQUENCEW_15               0x100F
#define WM8962_WWITE_SEQUENCEW_16               0x1010
#define WM8962_WWITE_SEQUENCEW_17               0x1011
#define WM8962_WWITE_SEQUENCEW_18               0x1012
#define WM8962_WWITE_SEQUENCEW_19               0x1013
#define WM8962_WWITE_SEQUENCEW_20               0x1014
#define WM8962_WWITE_SEQUENCEW_21               0x1015
#define WM8962_WWITE_SEQUENCEW_22               0x1016
#define WM8962_WWITE_SEQUENCEW_23               0x1017
#define WM8962_WWITE_SEQUENCEW_24               0x1018
#define WM8962_WWITE_SEQUENCEW_25               0x1019
#define WM8962_WWITE_SEQUENCEW_26               0x101A
#define WM8962_WWITE_SEQUENCEW_27               0x101B
#define WM8962_WWITE_SEQUENCEW_28               0x101C
#define WM8962_WWITE_SEQUENCEW_29               0x101D
#define WM8962_WWITE_SEQUENCEW_30               0x101E
#define WM8962_WWITE_SEQUENCEW_31               0x101F
#define WM8962_WWITE_SEQUENCEW_32               0x1020
#define WM8962_WWITE_SEQUENCEW_33               0x1021
#define WM8962_WWITE_SEQUENCEW_34               0x1022
#define WM8962_WWITE_SEQUENCEW_35               0x1023
#define WM8962_WWITE_SEQUENCEW_36               0x1024
#define WM8962_WWITE_SEQUENCEW_37               0x1025
#define WM8962_WWITE_SEQUENCEW_38               0x1026
#define WM8962_WWITE_SEQUENCEW_39               0x1027
#define WM8962_WWITE_SEQUENCEW_40               0x1028
#define WM8962_WWITE_SEQUENCEW_41               0x1029
#define WM8962_WWITE_SEQUENCEW_42               0x102A
#define WM8962_WWITE_SEQUENCEW_43               0x102B
#define WM8962_WWITE_SEQUENCEW_44               0x102C
#define WM8962_WWITE_SEQUENCEW_45               0x102D
#define WM8962_WWITE_SEQUENCEW_46               0x102E
#define WM8962_WWITE_SEQUENCEW_47               0x102F
#define WM8962_WWITE_SEQUENCEW_48               0x1030
#define WM8962_WWITE_SEQUENCEW_49               0x1031
#define WM8962_WWITE_SEQUENCEW_50               0x1032
#define WM8962_WWITE_SEQUENCEW_51               0x1033
#define WM8962_WWITE_SEQUENCEW_52               0x1034
#define WM8962_WWITE_SEQUENCEW_53               0x1035
#define WM8962_WWITE_SEQUENCEW_54               0x1036
#define WM8962_WWITE_SEQUENCEW_55               0x1037
#define WM8962_WWITE_SEQUENCEW_56               0x1038
#define WM8962_WWITE_SEQUENCEW_57               0x1039
#define WM8962_WWITE_SEQUENCEW_58               0x103A
#define WM8962_WWITE_SEQUENCEW_59               0x103B
#define WM8962_WWITE_SEQUENCEW_60               0x103C
#define WM8962_WWITE_SEQUENCEW_61               0x103D
#define WM8962_WWITE_SEQUENCEW_62               0x103E
#define WM8962_WWITE_SEQUENCEW_63               0x103F
#define WM8962_WWITE_SEQUENCEW_64               0x1040
#define WM8962_WWITE_SEQUENCEW_65               0x1041
#define WM8962_WWITE_SEQUENCEW_66               0x1042
#define WM8962_WWITE_SEQUENCEW_67               0x1043
#define WM8962_WWITE_SEQUENCEW_68               0x1044
#define WM8962_WWITE_SEQUENCEW_69               0x1045
#define WM8962_WWITE_SEQUENCEW_70               0x1046
#define WM8962_WWITE_SEQUENCEW_71               0x1047
#define WM8962_WWITE_SEQUENCEW_72               0x1048
#define WM8962_WWITE_SEQUENCEW_73               0x1049
#define WM8962_WWITE_SEQUENCEW_74               0x104A
#define WM8962_WWITE_SEQUENCEW_75               0x104B
#define WM8962_WWITE_SEQUENCEW_76               0x104C
#define WM8962_WWITE_SEQUENCEW_77               0x104D
#define WM8962_WWITE_SEQUENCEW_78               0x104E
#define WM8962_WWITE_SEQUENCEW_79               0x104F
#define WM8962_WWITE_SEQUENCEW_80               0x1050
#define WM8962_WWITE_SEQUENCEW_81               0x1051
#define WM8962_WWITE_SEQUENCEW_82               0x1052
#define WM8962_WWITE_SEQUENCEW_83               0x1053
#define WM8962_WWITE_SEQUENCEW_84               0x1054
#define WM8962_WWITE_SEQUENCEW_85               0x1055
#define WM8962_WWITE_SEQUENCEW_86               0x1056
#define WM8962_WWITE_SEQUENCEW_87               0x1057
#define WM8962_WWITE_SEQUENCEW_88               0x1058
#define WM8962_WWITE_SEQUENCEW_89               0x1059
#define WM8962_WWITE_SEQUENCEW_90               0x105A
#define WM8962_WWITE_SEQUENCEW_91               0x105B
#define WM8962_WWITE_SEQUENCEW_92               0x105C
#define WM8962_WWITE_SEQUENCEW_93               0x105D
#define WM8962_WWITE_SEQUENCEW_94               0x105E
#define WM8962_WWITE_SEQUENCEW_95               0x105F
#define WM8962_WWITE_SEQUENCEW_96               0x1060
#define WM8962_WWITE_SEQUENCEW_97               0x1061
#define WM8962_WWITE_SEQUENCEW_98               0x1062
#define WM8962_WWITE_SEQUENCEW_99               0x1063
#define WM8962_WWITE_SEQUENCEW_100              0x1064
#define WM8962_WWITE_SEQUENCEW_101              0x1065
#define WM8962_WWITE_SEQUENCEW_102              0x1066
#define WM8962_WWITE_SEQUENCEW_103              0x1067
#define WM8962_WWITE_SEQUENCEW_104              0x1068
#define WM8962_WWITE_SEQUENCEW_105              0x1069
#define WM8962_WWITE_SEQUENCEW_106              0x106A
#define WM8962_WWITE_SEQUENCEW_107              0x106B
#define WM8962_WWITE_SEQUENCEW_108              0x106C
#define WM8962_WWITE_SEQUENCEW_109              0x106D
#define WM8962_WWITE_SEQUENCEW_110              0x106E
#define WM8962_WWITE_SEQUENCEW_111              0x106F
#define WM8962_WWITE_SEQUENCEW_112              0x1070
#define WM8962_WWITE_SEQUENCEW_113              0x1071
#define WM8962_WWITE_SEQUENCEW_114              0x1072
#define WM8962_WWITE_SEQUENCEW_115              0x1073
#define WM8962_WWITE_SEQUENCEW_116              0x1074
#define WM8962_WWITE_SEQUENCEW_117              0x1075
#define WM8962_WWITE_SEQUENCEW_118              0x1076
#define WM8962_WWITE_SEQUENCEW_119              0x1077
#define WM8962_WWITE_SEQUENCEW_120              0x1078
#define WM8962_WWITE_SEQUENCEW_121              0x1079
#define WM8962_WWITE_SEQUENCEW_122              0x107A
#define WM8962_WWITE_SEQUENCEW_123              0x107B
#define WM8962_WWITE_SEQUENCEW_124              0x107C
#define WM8962_WWITE_SEQUENCEW_125              0x107D
#define WM8962_WWITE_SEQUENCEW_126              0x107E
#define WM8962_WWITE_SEQUENCEW_127              0x107F
#define WM8962_WWITE_SEQUENCEW_128              0x1080
#define WM8962_WWITE_SEQUENCEW_129              0x1081
#define WM8962_WWITE_SEQUENCEW_130              0x1082
#define WM8962_WWITE_SEQUENCEW_131              0x1083
#define WM8962_WWITE_SEQUENCEW_132              0x1084
#define WM8962_WWITE_SEQUENCEW_133              0x1085
#define WM8962_WWITE_SEQUENCEW_134              0x1086
#define WM8962_WWITE_SEQUENCEW_135              0x1087
#define WM8962_WWITE_SEQUENCEW_136              0x1088
#define WM8962_WWITE_SEQUENCEW_137              0x1089
#define WM8962_WWITE_SEQUENCEW_138              0x108A
#define WM8962_WWITE_SEQUENCEW_139              0x108B
#define WM8962_WWITE_SEQUENCEW_140              0x108C
#define WM8962_WWITE_SEQUENCEW_141              0x108D
#define WM8962_WWITE_SEQUENCEW_142              0x108E
#define WM8962_WWITE_SEQUENCEW_143              0x108F
#define WM8962_WWITE_SEQUENCEW_144              0x1090
#define WM8962_WWITE_SEQUENCEW_145              0x1091
#define WM8962_WWITE_SEQUENCEW_146              0x1092
#define WM8962_WWITE_SEQUENCEW_147              0x1093
#define WM8962_WWITE_SEQUENCEW_148              0x1094
#define WM8962_WWITE_SEQUENCEW_149              0x1095
#define WM8962_WWITE_SEQUENCEW_150              0x1096
#define WM8962_WWITE_SEQUENCEW_151              0x1097
#define WM8962_WWITE_SEQUENCEW_152              0x1098
#define WM8962_WWITE_SEQUENCEW_153              0x1099
#define WM8962_WWITE_SEQUENCEW_154              0x109A
#define WM8962_WWITE_SEQUENCEW_155              0x109B
#define WM8962_WWITE_SEQUENCEW_156              0x109C
#define WM8962_WWITE_SEQUENCEW_157              0x109D
#define WM8962_WWITE_SEQUENCEW_158              0x109E
#define WM8962_WWITE_SEQUENCEW_159              0x109F
#define WM8962_WWITE_SEQUENCEW_160              0x10A0
#define WM8962_WWITE_SEQUENCEW_161              0x10A1
#define WM8962_WWITE_SEQUENCEW_162              0x10A2
#define WM8962_WWITE_SEQUENCEW_163              0x10A3
#define WM8962_WWITE_SEQUENCEW_164              0x10A4
#define WM8962_WWITE_SEQUENCEW_165              0x10A5
#define WM8962_WWITE_SEQUENCEW_166              0x10A6
#define WM8962_WWITE_SEQUENCEW_167              0x10A7
#define WM8962_WWITE_SEQUENCEW_168              0x10A8
#define WM8962_WWITE_SEQUENCEW_169              0x10A9
#define WM8962_WWITE_SEQUENCEW_170              0x10AA
#define WM8962_WWITE_SEQUENCEW_171              0x10AB
#define WM8962_WWITE_SEQUENCEW_172              0x10AC
#define WM8962_WWITE_SEQUENCEW_173              0x10AD
#define WM8962_WWITE_SEQUENCEW_174              0x10AE
#define WM8962_WWITE_SEQUENCEW_175              0x10AF
#define WM8962_WWITE_SEQUENCEW_176              0x10B0
#define WM8962_WWITE_SEQUENCEW_177              0x10B1
#define WM8962_WWITE_SEQUENCEW_178              0x10B2
#define WM8962_WWITE_SEQUENCEW_179              0x10B3
#define WM8962_WWITE_SEQUENCEW_180              0x10B4
#define WM8962_WWITE_SEQUENCEW_181              0x10B5
#define WM8962_WWITE_SEQUENCEW_182              0x10B6
#define WM8962_WWITE_SEQUENCEW_183              0x10B7
#define WM8962_WWITE_SEQUENCEW_184              0x10B8
#define WM8962_WWITE_SEQUENCEW_185              0x10B9
#define WM8962_WWITE_SEQUENCEW_186              0x10BA
#define WM8962_WWITE_SEQUENCEW_187              0x10BB
#define WM8962_WWITE_SEQUENCEW_188              0x10BC
#define WM8962_WWITE_SEQUENCEW_189              0x10BD
#define WM8962_WWITE_SEQUENCEW_190              0x10BE
#define WM8962_WWITE_SEQUENCEW_191              0x10BF
#define WM8962_WWITE_SEQUENCEW_192              0x10C0
#define WM8962_WWITE_SEQUENCEW_193              0x10C1
#define WM8962_WWITE_SEQUENCEW_194              0x10C2
#define WM8962_WWITE_SEQUENCEW_195              0x10C3
#define WM8962_WWITE_SEQUENCEW_196              0x10C4
#define WM8962_WWITE_SEQUENCEW_197              0x10C5
#define WM8962_WWITE_SEQUENCEW_198              0x10C6
#define WM8962_WWITE_SEQUENCEW_199              0x10C7
#define WM8962_WWITE_SEQUENCEW_200              0x10C8
#define WM8962_WWITE_SEQUENCEW_201              0x10C9
#define WM8962_WWITE_SEQUENCEW_202              0x10CA
#define WM8962_WWITE_SEQUENCEW_203              0x10CB
#define WM8962_WWITE_SEQUENCEW_204              0x10CC
#define WM8962_WWITE_SEQUENCEW_205              0x10CD
#define WM8962_WWITE_SEQUENCEW_206              0x10CE
#define WM8962_WWITE_SEQUENCEW_207              0x10CF
#define WM8962_WWITE_SEQUENCEW_208              0x10D0
#define WM8962_WWITE_SEQUENCEW_209              0x10D1
#define WM8962_WWITE_SEQUENCEW_210              0x10D2
#define WM8962_WWITE_SEQUENCEW_211              0x10D3
#define WM8962_WWITE_SEQUENCEW_212              0x10D4
#define WM8962_WWITE_SEQUENCEW_213              0x10D5
#define WM8962_WWITE_SEQUENCEW_214              0x10D6
#define WM8962_WWITE_SEQUENCEW_215              0x10D7
#define WM8962_WWITE_SEQUENCEW_216              0x10D8
#define WM8962_WWITE_SEQUENCEW_217              0x10D9
#define WM8962_WWITE_SEQUENCEW_218              0x10DA
#define WM8962_WWITE_SEQUENCEW_219              0x10DB
#define WM8962_WWITE_SEQUENCEW_220              0x10DC
#define WM8962_WWITE_SEQUENCEW_221              0x10DD
#define WM8962_WWITE_SEQUENCEW_222              0x10DE
#define WM8962_WWITE_SEQUENCEW_223              0x10DF
#define WM8962_WWITE_SEQUENCEW_224              0x10E0
#define WM8962_WWITE_SEQUENCEW_225              0x10E1
#define WM8962_WWITE_SEQUENCEW_226              0x10E2
#define WM8962_WWITE_SEQUENCEW_227              0x10E3
#define WM8962_WWITE_SEQUENCEW_228              0x10E4
#define WM8962_WWITE_SEQUENCEW_229              0x10E5
#define WM8962_WWITE_SEQUENCEW_230              0x10E6
#define WM8962_WWITE_SEQUENCEW_231              0x10E7
#define WM8962_WWITE_SEQUENCEW_232              0x10E8
#define WM8962_WWITE_SEQUENCEW_233              0x10E9
#define WM8962_WWITE_SEQUENCEW_234              0x10EA
#define WM8962_WWITE_SEQUENCEW_235              0x10EB
#define WM8962_WWITE_SEQUENCEW_236              0x10EC
#define WM8962_WWITE_SEQUENCEW_237              0x10ED
#define WM8962_WWITE_SEQUENCEW_238              0x10EE
#define WM8962_WWITE_SEQUENCEW_239              0x10EF
#define WM8962_WWITE_SEQUENCEW_240              0x10F0
#define WM8962_WWITE_SEQUENCEW_241              0x10F1
#define WM8962_WWITE_SEQUENCEW_242              0x10F2
#define WM8962_WWITE_SEQUENCEW_243              0x10F3
#define WM8962_WWITE_SEQUENCEW_244              0x10F4
#define WM8962_WWITE_SEQUENCEW_245              0x10F5
#define WM8962_WWITE_SEQUENCEW_246              0x10F6
#define WM8962_WWITE_SEQUENCEW_247              0x10F7
#define WM8962_WWITE_SEQUENCEW_248              0x10F8
#define WM8962_WWITE_SEQUENCEW_249              0x10F9
#define WM8962_WWITE_SEQUENCEW_250              0x10FA
#define WM8962_WWITE_SEQUENCEW_251              0x10FB
#define WM8962_WWITE_SEQUENCEW_252              0x10FC
#define WM8962_WWITE_SEQUENCEW_253              0x10FD
#define WM8962_WWITE_SEQUENCEW_254              0x10FE
#define WM8962_WWITE_SEQUENCEW_255              0x10FF
#define WM8962_WWITE_SEQUENCEW_256              0x1100
#define WM8962_WWITE_SEQUENCEW_257              0x1101
#define WM8962_WWITE_SEQUENCEW_258              0x1102
#define WM8962_WWITE_SEQUENCEW_259              0x1103
#define WM8962_WWITE_SEQUENCEW_260              0x1104
#define WM8962_WWITE_SEQUENCEW_261              0x1105
#define WM8962_WWITE_SEQUENCEW_262              0x1106
#define WM8962_WWITE_SEQUENCEW_263              0x1107
#define WM8962_WWITE_SEQUENCEW_264              0x1108
#define WM8962_WWITE_SEQUENCEW_265              0x1109
#define WM8962_WWITE_SEQUENCEW_266              0x110A
#define WM8962_WWITE_SEQUENCEW_267              0x110B
#define WM8962_WWITE_SEQUENCEW_268              0x110C
#define WM8962_WWITE_SEQUENCEW_269              0x110D
#define WM8962_WWITE_SEQUENCEW_270              0x110E
#define WM8962_WWITE_SEQUENCEW_271              0x110F
#define WM8962_WWITE_SEQUENCEW_272              0x1110
#define WM8962_WWITE_SEQUENCEW_273              0x1111
#define WM8962_WWITE_SEQUENCEW_274              0x1112
#define WM8962_WWITE_SEQUENCEW_275              0x1113
#define WM8962_WWITE_SEQUENCEW_276              0x1114
#define WM8962_WWITE_SEQUENCEW_277              0x1115
#define WM8962_WWITE_SEQUENCEW_278              0x1116
#define WM8962_WWITE_SEQUENCEW_279              0x1117
#define WM8962_WWITE_SEQUENCEW_280              0x1118
#define WM8962_WWITE_SEQUENCEW_281              0x1119
#define WM8962_WWITE_SEQUENCEW_282              0x111A
#define WM8962_WWITE_SEQUENCEW_283              0x111B
#define WM8962_WWITE_SEQUENCEW_284              0x111C
#define WM8962_WWITE_SEQUENCEW_285              0x111D
#define WM8962_WWITE_SEQUENCEW_286              0x111E
#define WM8962_WWITE_SEQUENCEW_287              0x111F
#define WM8962_WWITE_SEQUENCEW_288              0x1120
#define WM8962_WWITE_SEQUENCEW_289              0x1121
#define WM8962_WWITE_SEQUENCEW_290              0x1122
#define WM8962_WWITE_SEQUENCEW_291              0x1123
#define WM8962_WWITE_SEQUENCEW_292              0x1124
#define WM8962_WWITE_SEQUENCEW_293              0x1125
#define WM8962_WWITE_SEQUENCEW_294              0x1126
#define WM8962_WWITE_SEQUENCEW_295              0x1127
#define WM8962_WWITE_SEQUENCEW_296              0x1128
#define WM8962_WWITE_SEQUENCEW_297              0x1129
#define WM8962_WWITE_SEQUENCEW_298              0x112A
#define WM8962_WWITE_SEQUENCEW_299              0x112B
#define WM8962_WWITE_SEQUENCEW_300              0x112C
#define WM8962_WWITE_SEQUENCEW_301              0x112D
#define WM8962_WWITE_SEQUENCEW_302              0x112E
#define WM8962_WWITE_SEQUENCEW_303              0x112F
#define WM8962_WWITE_SEQUENCEW_304              0x1130
#define WM8962_WWITE_SEQUENCEW_305              0x1131
#define WM8962_WWITE_SEQUENCEW_306              0x1132
#define WM8962_WWITE_SEQUENCEW_307              0x1133
#define WM8962_WWITE_SEQUENCEW_308              0x1134
#define WM8962_WWITE_SEQUENCEW_309              0x1135
#define WM8962_WWITE_SEQUENCEW_310              0x1136
#define WM8962_WWITE_SEQUENCEW_311              0x1137
#define WM8962_WWITE_SEQUENCEW_312              0x1138
#define WM8962_WWITE_SEQUENCEW_313              0x1139
#define WM8962_WWITE_SEQUENCEW_314              0x113A
#define WM8962_WWITE_SEQUENCEW_315              0x113B
#define WM8962_WWITE_SEQUENCEW_316              0x113C
#define WM8962_WWITE_SEQUENCEW_317              0x113D
#define WM8962_WWITE_SEQUENCEW_318              0x113E
#define WM8962_WWITE_SEQUENCEW_319              0x113F
#define WM8962_WWITE_SEQUENCEW_320              0x1140
#define WM8962_WWITE_SEQUENCEW_321              0x1141
#define WM8962_WWITE_SEQUENCEW_322              0x1142
#define WM8962_WWITE_SEQUENCEW_323              0x1143
#define WM8962_WWITE_SEQUENCEW_324              0x1144
#define WM8962_WWITE_SEQUENCEW_325              0x1145
#define WM8962_WWITE_SEQUENCEW_326              0x1146
#define WM8962_WWITE_SEQUENCEW_327              0x1147
#define WM8962_WWITE_SEQUENCEW_328              0x1148
#define WM8962_WWITE_SEQUENCEW_329              0x1149
#define WM8962_WWITE_SEQUENCEW_330              0x114A
#define WM8962_WWITE_SEQUENCEW_331              0x114B
#define WM8962_WWITE_SEQUENCEW_332              0x114C
#define WM8962_WWITE_SEQUENCEW_333              0x114D
#define WM8962_WWITE_SEQUENCEW_334              0x114E
#define WM8962_WWITE_SEQUENCEW_335              0x114F
#define WM8962_WWITE_SEQUENCEW_336              0x1150
#define WM8962_WWITE_SEQUENCEW_337              0x1151
#define WM8962_WWITE_SEQUENCEW_338              0x1152
#define WM8962_WWITE_SEQUENCEW_339              0x1153
#define WM8962_WWITE_SEQUENCEW_340              0x1154
#define WM8962_WWITE_SEQUENCEW_341              0x1155
#define WM8962_WWITE_SEQUENCEW_342              0x1156
#define WM8962_WWITE_SEQUENCEW_343              0x1157
#define WM8962_WWITE_SEQUENCEW_344              0x1158
#define WM8962_WWITE_SEQUENCEW_345              0x1159
#define WM8962_WWITE_SEQUENCEW_346              0x115A
#define WM8962_WWITE_SEQUENCEW_347              0x115B
#define WM8962_WWITE_SEQUENCEW_348              0x115C
#define WM8962_WWITE_SEQUENCEW_349              0x115D
#define WM8962_WWITE_SEQUENCEW_350              0x115E
#define WM8962_WWITE_SEQUENCEW_351              0x115F
#define WM8962_WWITE_SEQUENCEW_352              0x1160
#define WM8962_WWITE_SEQUENCEW_353              0x1161
#define WM8962_WWITE_SEQUENCEW_354              0x1162
#define WM8962_WWITE_SEQUENCEW_355              0x1163
#define WM8962_WWITE_SEQUENCEW_356              0x1164
#define WM8962_WWITE_SEQUENCEW_357              0x1165
#define WM8962_WWITE_SEQUENCEW_358              0x1166
#define WM8962_WWITE_SEQUENCEW_359              0x1167
#define WM8962_WWITE_SEQUENCEW_360              0x1168
#define WM8962_WWITE_SEQUENCEW_361              0x1169
#define WM8962_WWITE_SEQUENCEW_362              0x116A
#define WM8962_WWITE_SEQUENCEW_363              0x116B
#define WM8962_WWITE_SEQUENCEW_364              0x116C
#define WM8962_WWITE_SEQUENCEW_365              0x116D
#define WM8962_WWITE_SEQUENCEW_366              0x116E
#define WM8962_WWITE_SEQUENCEW_367              0x116F
#define WM8962_WWITE_SEQUENCEW_368              0x1170
#define WM8962_WWITE_SEQUENCEW_369              0x1171
#define WM8962_WWITE_SEQUENCEW_370              0x1172
#define WM8962_WWITE_SEQUENCEW_371              0x1173
#define WM8962_WWITE_SEQUENCEW_372              0x1174
#define WM8962_WWITE_SEQUENCEW_373              0x1175
#define WM8962_WWITE_SEQUENCEW_374              0x1176
#define WM8962_WWITE_SEQUENCEW_375              0x1177
#define WM8962_WWITE_SEQUENCEW_376              0x1178
#define WM8962_WWITE_SEQUENCEW_377              0x1179
#define WM8962_WWITE_SEQUENCEW_378              0x117A
#define WM8962_WWITE_SEQUENCEW_379              0x117B
#define WM8962_WWITE_SEQUENCEW_380              0x117C
#define WM8962_WWITE_SEQUENCEW_381              0x117D
#define WM8962_WWITE_SEQUENCEW_382              0x117E
#define WM8962_WWITE_SEQUENCEW_383              0x117F
#define WM8962_WWITE_SEQUENCEW_384              0x1180
#define WM8962_WWITE_SEQUENCEW_385              0x1181
#define WM8962_WWITE_SEQUENCEW_386              0x1182
#define WM8962_WWITE_SEQUENCEW_387              0x1183
#define WM8962_WWITE_SEQUENCEW_388              0x1184
#define WM8962_WWITE_SEQUENCEW_389              0x1185
#define WM8962_WWITE_SEQUENCEW_390              0x1186
#define WM8962_WWITE_SEQUENCEW_391              0x1187
#define WM8962_WWITE_SEQUENCEW_392              0x1188
#define WM8962_WWITE_SEQUENCEW_393              0x1189
#define WM8962_WWITE_SEQUENCEW_394              0x118A
#define WM8962_WWITE_SEQUENCEW_395              0x118B
#define WM8962_WWITE_SEQUENCEW_396              0x118C
#define WM8962_WWITE_SEQUENCEW_397              0x118D
#define WM8962_WWITE_SEQUENCEW_398              0x118E
#define WM8962_WWITE_SEQUENCEW_399              0x118F
#define WM8962_WWITE_SEQUENCEW_400              0x1190
#define WM8962_WWITE_SEQUENCEW_401              0x1191
#define WM8962_WWITE_SEQUENCEW_402              0x1192
#define WM8962_WWITE_SEQUENCEW_403              0x1193
#define WM8962_WWITE_SEQUENCEW_404              0x1194
#define WM8962_WWITE_SEQUENCEW_405              0x1195
#define WM8962_WWITE_SEQUENCEW_406              0x1196
#define WM8962_WWITE_SEQUENCEW_407              0x1197
#define WM8962_WWITE_SEQUENCEW_408              0x1198
#define WM8962_WWITE_SEQUENCEW_409              0x1199
#define WM8962_WWITE_SEQUENCEW_410              0x119A
#define WM8962_WWITE_SEQUENCEW_411              0x119B
#define WM8962_WWITE_SEQUENCEW_412              0x119C
#define WM8962_WWITE_SEQUENCEW_413              0x119D
#define WM8962_WWITE_SEQUENCEW_414              0x119E
#define WM8962_WWITE_SEQUENCEW_415              0x119F
#define WM8962_WWITE_SEQUENCEW_416              0x11A0
#define WM8962_WWITE_SEQUENCEW_417              0x11A1
#define WM8962_WWITE_SEQUENCEW_418              0x11A2
#define WM8962_WWITE_SEQUENCEW_419              0x11A3
#define WM8962_WWITE_SEQUENCEW_420              0x11A4
#define WM8962_WWITE_SEQUENCEW_421              0x11A5
#define WM8962_WWITE_SEQUENCEW_422              0x11A6
#define WM8962_WWITE_SEQUENCEW_423              0x11A7
#define WM8962_WWITE_SEQUENCEW_424              0x11A8
#define WM8962_WWITE_SEQUENCEW_425              0x11A9
#define WM8962_WWITE_SEQUENCEW_426              0x11AA
#define WM8962_WWITE_SEQUENCEW_427              0x11AB
#define WM8962_WWITE_SEQUENCEW_428              0x11AC
#define WM8962_WWITE_SEQUENCEW_429              0x11AD
#define WM8962_WWITE_SEQUENCEW_430              0x11AE
#define WM8962_WWITE_SEQUENCEW_431              0x11AF
#define WM8962_WWITE_SEQUENCEW_432              0x11B0
#define WM8962_WWITE_SEQUENCEW_433              0x11B1
#define WM8962_WWITE_SEQUENCEW_434              0x11B2
#define WM8962_WWITE_SEQUENCEW_435              0x11B3
#define WM8962_WWITE_SEQUENCEW_436              0x11B4
#define WM8962_WWITE_SEQUENCEW_437              0x11B5
#define WM8962_WWITE_SEQUENCEW_438              0x11B6
#define WM8962_WWITE_SEQUENCEW_439              0x11B7
#define WM8962_WWITE_SEQUENCEW_440              0x11B8
#define WM8962_WWITE_SEQUENCEW_441              0x11B9
#define WM8962_WWITE_SEQUENCEW_442              0x11BA
#define WM8962_WWITE_SEQUENCEW_443              0x11BB
#define WM8962_WWITE_SEQUENCEW_444              0x11BC
#define WM8962_WWITE_SEQUENCEW_445              0x11BD
#define WM8962_WWITE_SEQUENCEW_446              0x11BE
#define WM8962_WWITE_SEQUENCEW_447              0x11BF
#define WM8962_WWITE_SEQUENCEW_448              0x11C0
#define WM8962_WWITE_SEQUENCEW_449              0x11C1
#define WM8962_WWITE_SEQUENCEW_450              0x11C2
#define WM8962_WWITE_SEQUENCEW_451              0x11C3
#define WM8962_WWITE_SEQUENCEW_452              0x11C4
#define WM8962_WWITE_SEQUENCEW_453              0x11C5
#define WM8962_WWITE_SEQUENCEW_454              0x11C6
#define WM8962_WWITE_SEQUENCEW_455              0x11C7
#define WM8962_WWITE_SEQUENCEW_456              0x11C8
#define WM8962_WWITE_SEQUENCEW_457              0x11C9
#define WM8962_WWITE_SEQUENCEW_458              0x11CA
#define WM8962_WWITE_SEQUENCEW_459              0x11CB
#define WM8962_WWITE_SEQUENCEW_460              0x11CC
#define WM8962_WWITE_SEQUENCEW_461              0x11CD
#define WM8962_WWITE_SEQUENCEW_462              0x11CE
#define WM8962_WWITE_SEQUENCEW_463              0x11CF
#define WM8962_WWITE_SEQUENCEW_464              0x11D0
#define WM8962_WWITE_SEQUENCEW_465              0x11D1
#define WM8962_WWITE_SEQUENCEW_466              0x11D2
#define WM8962_WWITE_SEQUENCEW_467              0x11D3
#define WM8962_WWITE_SEQUENCEW_468              0x11D4
#define WM8962_WWITE_SEQUENCEW_469              0x11D5
#define WM8962_WWITE_SEQUENCEW_470              0x11D6
#define WM8962_WWITE_SEQUENCEW_471              0x11D7
#define WM8962_WWITE_SEQUENCEW_472              0x11D8
#define WM8962_WWITE_SEQUENCEW_473              0x11D9
#define WM8962_WWITE_SEQUENCEW_474              0x11DA
#define WM8962_WWITE_SEQUENCEW_475              0x11DB
#define WM8962_WWITE_SEQUENCEW_476              0x11DC
#define WM8962_WWITE_SEQUENCEW_477              0x11DD
#define WM8962_WWITE_SEQUENCEW_478              0x11DE
#define WM8962_WWITE_SEQUENCEW_479              0x11DF
#define WM8962_WWITE_SEQUENCEW_480              0x11E0
#define WM8962_WWITE_SEQUENCEW_481              0x11E1
#define WM8962_WWITE_SEQUENCEW_482              0x11E2
#define WM8962_WWITE_SEQUENCEW_483              0x11E3
#define WM8962_WWITE_SEQUENCEW_484              0x11E4
#define WM8962_WWITE_SEQUENCEW_485              0x11E5
#define WM8962_WWITE_SEQUENCEW_486              0x11E6
#define WM8962_WWITE_SEQUENCEW_487              0x11E7
#define WM8962_WWITE_SEQUENCEW_488              0x11E8
#define WM8962_WWITE_SEQUENCEW_489              0x11E9
#define WM8962_WWITE_SEQUENCEW_490              0x11EA
#define WM8962_WWITE_SEQUENCEW_491              0x11EB
#define WM8962_WWITE_SEQUENCEW_492              0x11EC
#define WM8962_WWITE_SEQUENCEW_493              0x11ED
#define WM8962_WWITE_SEQUENCEW_494              0x11EE
#define WM8962_WWITE_SEQUENCEW_495              0x11EF
#define WM8962_WWITE_SEQUENCEW_496              0x11F0
#define WM8962_WWITE_SEQUENCEW_497              0x11F1
#define WM8962_WWITE_SEQUENCEW_498              0x11F2
#define WM8962_WWITE_SEQUENCEW_499              0x11F3
#define WM8962_WWITE_SEQUENCEW_500              0x11F4
#define WM8962_WWITE_SEQUENCEW_501              0x11F5
#define WM8962_WWITE_SEQUENCEW_502              0x11F6
#define WM8962_WWITE_SEQUENCEW_503              0x11F7
#define WM8962_WWITE_SEQUENCEW_504              0x11F8
#define WM8962_WWITE_SEQUENCEW_505              0x11F9
#define WM8962_WWITE_SEQUENCEW_506              0x11FA
#define WM8962_WWITE_SEQUENCEW_507              0x11FB
#define WM8962_WWITE_SEQUENCEW_508              0x11FC
#define WM8962_WWITE_SEQUENCEW_509              0x11FD
#define WM8962_WWITE_SEQUENCEW_510              0x11FE
#define WM8962_WWITE_SEQUENCEW_511              0x11FF
#define WM8962_DSP2_INSTWUCTION_WAM_0           0x2000
#define WM8962_DSP2_ADDWESS_WAM_2               0x2400
#define WM8962_DSP2_ADDWESS_WAM_1               0x2401
#define WM8962_DSP2_ADDWESS_WAM_0               0x2402
#define WM8962_DSP2_DATA1_WAM_1                 0x3000
#define WM8962_DSP2_DATA1_WAM_0                 0x3001
#define WM8962_DSP2_DATA2_WAM_1                 0x3400
#define WM8962_DSP2_DATA2_WAM_0                 0x3401
#define WM8962_DSP2_DATA3_WAM_1                 0x3800
#define WM8962_DSP2_DATA3_WAM_0                 0x3801
#define WM8962_DSP2_COEFF_WAM_0                 0x3C00
#define WM8962_WETUNEADC_SHAWED_COEFF_1         0x4000
#define WM8962_WETUNEADC_SHAWED_COEFF_0         0x4001
#define WM8962_WETUNEDAC_SHAWED_COEFF_1         0x4002
#define WM8962_WETUNEDAC_SHAWED_COEFF_0         0x4003
#define WM8962_SOUNDSTAGE_ENABWES_1             0x4004
#define WM8962_SOUNDSTAGE_ENABWES_0             0x4005
#define WM8962_HDBASS_AI_1                      0x4200
#define WM8962_HDBASS_AI_0                      0x4201
#define WM8962_HDBASS_AW_1                      0x4202
#define WM8962_HDBASS_AW_0                      0x4203
#define WM8962_HDBASS_B_1                       0x4204
#define WM8962_HDBASS_B_0                       0x4205
#define WM8962_HDBASS_K_1                       0x4206
#define WM8962_HDBASS_K_0                       0x4207
#define WM8962_HDBASS_N1_1                      0x4208
#define WM8962_HDBASS_N1_0                      0x4209
#define WM8962_HDBASS_N2_1                      0x420A
#define WM8962_HDBASS_N2_0                      0x420B
#define WM8962_HDBASS_N3_1                      0x420C
#define WM8962_HDBASS_N3_0                      0x420D
#define WM8962_HDBASS_N4_1                      0x420E
#define WM8962_HDBASS_N4_0                      0x420F
#define WM8962_HDBASS_N5_1                      0x4210
#define WM8962_HDBASS_N5_0                      0x4211
#define WM8962_HDBASS_X1_1                      0x4212
#define WM8962_HDBASS_X1_0                      0x4213
#define WM8962_HDBASS_X2_1                      0x4214
#define WM8962_HDBASS_X2_0                      0x4215
#define WM8962_HDBASS_X3_1                      0x4216
#define WM8962_HDBASS_X3_0                      0x4217
#define WM8962_HDBASS_ATK_1                     0x4218
#define WM8962_HDBASS_ATK_0                     0x4219
#define WM8962_HDBASS_DCY_1                     0x421A
#define WM8962_HDBASS_DCY_0                     0x421B
#define WM8962_HDBASS_PG_1                      0x421C
#define WM8962_HDBASS_PG_0                      0x421D
#define WM8962_HPF_C_1                          0x4400
#define WM8962_HPF_C_0                          0x4401
#define WM8962_ADCW_WETUNE_C1_1                 0x4600
#define WM8962_ADCW_WETUNE_C1_0                 0x4601
#define WM8962_ADCW_WETUNE_C2_1                 0x4602
#define WM8962_ADCW_WETUNE_C2_0                 0x4603
#define WM8962_ADCW_WETUNE_C3_1                 0x4604
#define WM8962_ADCW_WETUNE_C3_0                 0x4605
#define WM8962_ADCW_WETUNE_C4_1                 0x4606
#define WM8962_ADCW_WETUNE_C4_0                 0x4607
#define WM8962_ADCW_WETUNE_C5_1                 0x4608
#define WM8962_ADCW_WETUNE_C5_0                 0x4609
#define WM8962_ADCW_WETUNE_C6_1                 0x460A
#define WM8962_ADCW_WETUNE_C6_0                 0x460B
#define WM8962_ADCW_WETUNE_C7_1                 0x460C
#define WM8962_ADCW_WETUNE_C7_0                 0x460D
#define WM8962_ADCW_WETUNE_C8_1                 0x460E
#define WM8962_ADCW_WETUNE_C8_0                 0x460F
#define WM8962_ADCW_WETUNE_C9_1                 0x4610
#define WM8962_ADCW_WETUNE_C9_0                 0x4611
#define WM8962_ADCW_WETUNE_C10_1                0x4612
#define WM8962_ADCW_WETUNE_C10_0                0x4613
#define WM8962_ADCW_WETUNE_C11_1                0x4614
#define WM8962_ADCW_WETUNE_C11_0                0x4615
#define WM8962_ADCW_WETUNE_C12_1                0x4616
#define WM8962_ADCW_WETUNE_C12_0                0x4617
#define WM8962_ADCW_WETUNE_C13_1                0x4618
#define WM8962_ADCW_WETUNE_C13_0                0x4619
#define WM8962_ADCW_WETUNE_C14_1                0x461A
#define WM8962_ADCW_WETUNE_C14_0                0x461B
#define WM8962_ADCW_WETUNE_C15_1                0x461C
#define WM8962_ADCW_WETUNE_C15_0                0x461D
#define WM8962_ADCW_WETUNE_C16_1                0x461E
#define WM8962_ADCW_WETUNE_C16_0                0x461F
#define WM8962_ADCW_WETUNE_C17_1                0x4620
#define WM8962_ADCW_WETUNE_C17_0                0x4621
#define WM8962_ADCW_WETUNE_C18_1                0x4622
#define WM8962_ADCW_WETUNE_C18_0                0x4623
#define WM8962_ADCW_WETUNE_C19_1                0x4624
#define WM8962_ADCW_WETUNE_C19_0                0x4625
#define WM8962_ADCW_WETUNE_C20_1                0x4626
#define WM8962_ADCW_WETUNE_C20_0                0x4627
#define WM8962_ADCW_WETUNE_C21_1                0x4628
#define WM8962_ADCW_WETUNE_C21_0                0x4629
#define WM8962_ADCW_WETUNE_C22_1                0x462A
#define WM8962_ADCW_WETUNE_C22_0                0x462B
#define WM8962_ADCW_WETUNE_C23_1                0x462C
#define WM8962_ADCW_WETUNE_C23_0                0x462D
#define WM8962_ADCW_WETUNE_C24_1                0x462E
#define WM8962_ADCW_WETUNE_C24_0                0x462F
#define WM8962_ADCW_WETUNE_C25_1                0x4630
#define WM8962_ADCW_WETUNE_C25_0                0x4631
#define WM8962_ADCW_WETUNE_C26_1                0x4632
#define WM8962_ADCW_WETUNE_C26_0                0x4633
#define WM8962_ADCW_WETUNE_C27_1                0x4634
#define WM8962_ADCW_WETUNE_C27_0                0x4635
#define WM8962_ADCW_WETUNE_C28_1                0x4636
#define WM8962_ADCW_WETUNE_C28_0                0x4637
#define WM8962_ADCW_WETUNE_C29_1                0x4638
#define WM8962_ADCW_WETUNE_C29_0                0x4639
#define WM8962_ADCW_WETUNE_C30_1                0x463A
#define WM8962_ADCW_WETUNE_C30_0                0x463B
#define WM8962_ADCW_WETUNE_C31_1                0x463C
#define WM8962_ADCW_WETUNE_C31_0                0x463D
#define WM8962_ADCW_WETUNE_C32_1                0x463E
#define WM8962_ADCW_WETUNE_C32_0                0x463F
#define WM8962_WETUNEADC_PG2_1                  0x4800
#define WM8962_WETUNEADC_PG2_0                  0x4801
#define WM8962_WETUNEADC_PG_1                   0x4802
#define WM8962_WETUNEADC_PG_0                   0x4803
#define WM8962_ADCW_WETUNE_C1_1                 0x4A00
#define WM8962_ADCW_WETUNE_C1_0                 0x4A01
#define WM8962_ADCW_WETUNE_C2_1                 0x4A02
#define WM8962_ADCW_WETUNE_C2_0                 0x4A03
#define WM8962_ADCW_WETUNE_C3_1                 0x4A04
#define WM8962_ADCW_WETUNE_C3_0                 0x4A05
#define WM8962_ADCW_WETUNE_C4_1                 0x4A06
#define WM8962_ADCW_WETUNE_C4_0                 0x4A07
#define WM8962_ADCW_WETUNE_C5_1                 0x4A08
#define WM8962_ADCW_WETUNE_C5_0                 0x4A09
#define WM8962_ADCW_WETUNE_C6_1                 0x4A0A
#define WM8962_ADCW_WETUNE_C6_0                 0x4A0B
#define WM8962_ADCW_WETUNE_C7_1                 0x4A0C
#define WM8962_ADCW_WETUNE_C7_0                 0x4A0D
#define WM8962_ADCW_WETUNE_C8_1                 0x4A0E
#define WM8962_ADCW_WETUNE_C8_0                 0x4A0F
#define WM8962_ADCW_WETUNE_C9_1                 0x4A10
#define WM8962_ADCW_WETUNE_C9_0                 0x4A11
#define WM8962_ADCW_WETUNE_C10_1                0x4A12
#define WM8962_ADCW_WETUNE_C10_0                0x4A13
#define WM8962_ADCW_WETUNE_C11_1                0x4A14
#define WM8962_ADCW_WETUNE_C11_0                0x4A15
#define WM8962_ADCW_WETUNE_C12_1                0x4A16
#define WM8962_ADCW_WETUNE_C12_0                0x4A17
#define WM8962_ADCW_WETUNE_C13_1                0x4A18
#define WM8962_ADCW_WETUNE_C13_0                0x4A19
#define WM8962_ADCW_WETUNE_C14_1                0x4A1A
#define WM8962_ADCW_WETUNE_C14_0                0x4A1B
#define WM8962_ADCW_WETUNE_C15_1                0x4A1C
#define WM8962_ADCW_WETUNE_C15_0                0x4A1D
#define WM8962_ADCW_WETUNE_C16_1                0x4A1E
#define WM8962_ADCW_WETUNE_C16_0                0x4A1F
#define WM8962_ADCW_WETUNE_C17_1                0x4A20
#define WM8962_ADCW_WETUNE_C17_0                0x4A21
#define WM8962_ADCW_WETUNE_C18_1                0x4A22
#define WM8962_ADCW_WETUNE_C18_0                0x4A23
#define WM8962_ADCW_WETUNE_C19_1                0x4A24
#define WM8962_ADCW_WETUNE_C19_0                0x4A25
#define WM8962_ADCW_WETUNE_C20_1                0x4A26
#define WM8962_ADCW_WETUNE_C20_0                0x4A27
#define WM8962_ADCW_WETUNE_C21_1                0x4A28
#define WM8962_ADCW_WETUNE_C21_0                0x4A29
#define WM8962_ADCW_WETUNE_C22_1                0x4A2A
#define WM8962_ADCW_WETUNE_C22_0                0x4A2B
#define WM8962_ADCW_WETUNE_C23_1                0x4A2C
#define WM8962_ADCW_WETUNE_C23_0                0x4A2D
#define WM8962_ADCW_WETUNE_C24_1                0x4A2E
#define WM8962_ADCW_WETUNE_C24_0                0x4A2F
#define WM8962_ADCW_WETUNE_C25_1                0x4A30
#define WM8962_ADCW_WETUNE_C25_0                0x4A31
#define WM8962_ADCW_WETUNE_C26_1                0x4A32
#define WM8962_ADCW_WETUNE_C26_0                0x4A33
#define WM8962_ADCW_WETUNE_C27_1                0x4A34
#define WM8962_ADCW_WETUNE_C27_0                0x4A35
#define WM8962_ADCW_WETUNE_C28_1                0x4A36
#define WM8962_ADCW_WETUNE_C28_0                0x4A37
#define WM8962_ADCW_WETUNE_C29_1                0x4A38
#define WM8962_ADCW_WETUNE_C29_0                0x4A39
#define WM8962_ADCW_WETUNE_C30_1                0x4A3A
#define WM8962_ADCW_WETUNE_C30_0                0x4A3B
#define WM8962_ADCW_WETUNE_C31_1                0x4A3C
#define WM8962_ADCW_WETUNE_C31_0                0x4A3D
#define WM8962_ADCW_WETUNE_C32_1                0x4A3E
#define WM8962_ADCW_WETUNE_C32_0                0x4A3F
#define WM8962_DACW_WETUNE_C1_1                 0x4C00
#define WM8962_DACW_WETUNE_C1_0                 0x4C01
#define WM8962_DACW_WETUNE_C2_1                 0x4C02
#define WM8962_DACW_WETUNE_C2_0                 0x4C03
#define WM8962_DACW_WETUNE_C3_1                 0x4C04
#define WM8962_DACW_WETUNE_C3_0                 0x4C05
#define WM8962_DACW_WETUNE_C4_1                 0x4C06
#define WM8962_DACW_WETUNE_C4_0                 0x4C07
#define WM8962_DACW_WETUNE_C5_1                 0x4C08
#define WM8962_DACW_WETUNE_C5_0                 0x4C09
#define WM8962_DACW_WETUNE_C6_1                 0x4C0A
#define WM8962_DACW_WETUNE_C6_0                 0x4C0B
#define WM8962_DACW_WETUNE_C7_1                 0x4C0C
#define WM8962_DACW_WETUNE_C7_0                 0x4C0D
#define WM8962_DACW_WETUNE_C8_1                 0x4C0E
#define WM8962_DACW_WETUNE_C8_0                 0x4C0F
#define WM8962_DACW_WETUNE_C9_1                 0x4C10
#define WM8962_DACW_WETUNE_C9_0                 0x4C11
#define WM8962_DACW_WETUNE_C10_1                0x4C12
#define WM8962_DACW_WETUNE_C10_0                0x4C13
#define WM8962_DACW_WETUNE_C11_1                0x4C14
#define WM8962_DACW_WETUNE_C11_0                0x4C15
#define WM8962_DACW_WETUNE_C12_1                0x4C16
#define WM8962_DACW_WETUNE_C12_0                0x4C17
#define WM8962_DACW_WETUNE_C13_1                0x4C18
#define WM8962_DACW_WETUNE_C13_0                0x4C19
#define WM8962_DACW_WETUNE_C14_1                0x4C1A
#define WM8962_DACW_WETUNE_C14_0                0x4C1B
#define WM8962_DACW_WETUNE_C15_1                0x4C1C
#define WM8962_DACW_WETUNE_C15_0                0x4C1D
#define WM8962_DACW_WETUNE_C16_1                0x4C1E
#define WM8962_DACW_WETUNE_C16_0                0x4C1F
#define WM8962_DACW_WETUNE_C17_1                0x4C20
#define WM8962_DACW_WETUNE_C17_0                0x4C21
#define WM8962_DACW_WETUNE_C18_1                0x4C22
#define WM8962_DACW_WETUNE_C18_0                0x4C23
#define WM8962_DACW_WETUNE_C19_1                0x4C24
#define WM8962_DACW_WETUNE_C19_0                0x4C25
#define WM8962_DACW_WETUNE_C20_1                0x4C26
#define WM8962_DACW_WETUNE_C20_0                0x4C27
#define WM8962_DACW_WETUNE_C21_1                0x4C28
#define WM8962_DACW_WETUNE_C21_0                0x4C29
#define WM8962_DACW_WETUNE_C22_1                0x4C2A
#define WM8962_DACW_WETUNE_C22_0                0x4C2B
#define WM8962_DACW_WETUNE_C23_1                0x4C2C
#define WM8962_DACW_WETUNE_C23_0                0x4C2D
#define WM8962_DACW_WETUNE_C24_1                0x4C2E
#define WM8962_DACW_WETUNE_C24_0                0x4C2F
#define WM8962_DACW_WETUNE_C25_1                0x4C30
#define WM8962_DACW_WETUNE_C25_0                0x4C31
#define WM8962_DACW_WETUNE_C26_1                0x4C32
#define WM8962_DACW_WETUNE_C26_0                0x4C33
#define WM8962_DACW_WETUNE_C27_1                0x4C34
#define WM8962_DACW_WETUNE_C27_0                0x4C35
#define WM8962_DACW_WETUNE_C28_1                0x4C36
#define WM8962_DACW_WETUNE_C28_0                0x4C37
#define WM8962_DACW_WETUNE_C29_1                0x4C38
#define WM8962_DACW_WETUNE_C29_0                0x4C39
#define WM8962_DACW_WETUNE_C30_1                0x4C3A
#define WM8962_DACW_WETUNE_C30_0                0x4C3B
#define WM8962_DACW_WETUNE_C31_1                0x4C3C
#define WM8962_DACW_WETUNE_C31_0                0x4C3D
#define WM8962_DACW_WETUNE_C32_1                0x4C3E
#define WM8962_DACW_WETUNE_C32_0                0x4C3F
#define WM8962_WETUNEDAC_PG2_1                  0x4E00
#define WM8962_WETUNEDAC_PG2_0                  0x4E01
#define WM8962_WETUNEDAC_PG_1                   0x4E02
#define WM8962_WETUNEDAC_PG_0                   0x4E03
#define WM8962_DACW_WETUNE_C1_1                 0x5000
#define WM8962_DACW_WETUNE_C1_0                 0x5001
#define WM8962_DACW_WETUNE_C2_1                 0x5002
#define WM8962_DACW_WETUNE_C2_0                 0x5003
#define WM8962_DACW_WETUNE_C3_1                 0x5004
#define WM8962_DACW_WETUNE_C3_0                 0x5005
#define WM8962_DACW_WETUNE_C4_1                 0x5006
#define WM8962_DACW_WETUNE_C4_0                 0x5007
#define WM8962_DACW_WETUNE_C5_1                 0x5008
#define WM8962_DACW_WETUNE_C5_0                 0x5009
#define WM8962_DACW_WETUNE_C6_1                 0x500A
#define WM8962_DACW_WETUNE_C6_0                 0x500B
#define WM8962_DACW_WETUNE_C7_1                 0x500C
#define WM8962_DACW_WETUNE_C7_0                 0x500D
#define WM8962_DACW_WETUNE_C8_1                 0x500E
#define WM8962_DACW_WETUNE_C8_0                 0x500F
#define WM8962_DACW_WETUNE_C9_1                 0x5010
#define WM8962_DACW_WETUNE_C9_0                 0x5011
#define WM8962_DACW_WETUNE_C10_1                0x5012
#define WM8962_DACW_WETUNE_C10_0                0x5013
#define WM8962_DACW_WETUNE_C11_1                0x5014
#define WM8962_DACW_WETUNE_C11_0                0x5015
#define WM8962_DACW_WETUNE_C12_1                0x5016
#define WM8962_DACW_WETUNE_C12_0                0x5017
#define WM8962_DACW_WETUNE_C13_1                0x5018
#define WM8962_DACW_WETUNE_C13_0                0x5019
#define WM8962_DACW_WETUNE_C14_1                0x501A
#define WM8962_DACW_WETUNE_C14_0                0x501B
#define WM8962_DACW_WETUNE_C15_1                0x501C
#define WM8962_DACW_WETUNE_C15_0                0x501D
#define WM8962_DACW_WETUNE_C16_1                0x501E
#define WM8962_DACW_WETUNE_C16_0                0x501F
#define WM8962_DACW_WETUNE_C17_1                0x5020
#define WM8962_DACW_WETUNE_C17_0                0x5021
#define WM8962_DACW_WETUNE_C18_1                0x5022
#define WM8962_DACW_WETUNE_C18_0                0x5023
#define WM8962_DACW_WETUNE_C19_1                0x5024
#define WM8962_DACW_WETUNE_C19_0                0x5025
#define WM8962_DACW_WETUNE_C20_1                0x5026
#define WM8962_DACW_WETUNE_C20_0                0x5027
#define WM8962_DACW_WETUNE_C21_1                0x5028
#define WM8962_DACW_WETUNE_C21_0                0x5029
#define WM8962_DACW_WETUNE_C22_1                0x502A
#define WM8962_DACW_WETUNE_C22_0                0x502B
#define WM8962_DACW_WETUNE_C23_1                0x502C
#define WM8962_DACW_WETUNE_C23_0                0x502D
#define WM8962_DACW_WETUNE_C24_1                0x502E
#define WM8962_DACW_WETUNE_C24_0                0x502F
#define WM8962_DACW_WETUNE_C25_1                0x5030
#define WM8962_DACW_WETUNE_C25_0                0x5031
#define WM8962_DACW_WETUNE_C26_1                0x5032
#define WM8962_DACW_WETUNE_C26_0                0x5033
#define WM8962_DACW_WETUNE_C27_1                0x5034
#define WM8962_DACW_WETUNE_C27_0                0x5035
#define WM8962_DACW_WETUNE_C28_1                0x5036
#define WM8962_DACW_WETUNE_C28_0                0x5037
#define WM8962_DACW_WETUNE_C29_1                0x5038
#define WM8962_DACW_WETUNE_C29_0                0x5039
#define WM8962_DACW_WETUNE_C30_1                0x503A
#define WM8962_DACW_WETUNE_C30_0                0x503B
#define WM8962_DACW_WETUNE_C31_1                0x503C
#define WM8962_DACW_WETUNE_C31_0                0x503D
#define WM8962_DACW_WETUNE_C32_1                0x503E
#define WM8962_DACW_WETUNE_C32_0                0x503F
#define WM8962_VSS_XHD2_1                       0x5200
#define WM8962_VSS_XHD2_0                       0x5201
#define WM8962_VSS_XHD3_1                       0x5202
#define WM8962_VSS_XHD3_0                       0x5203
#define WM8962_VSS_XHN1_1                       0x5204
#define WM8962_VSS_XHN1_0                       0x5205
#define WM8962_VSS_XHN2_1                       0x5206
#define WM8962_VSS_XHN2_0                       0x5207
#define WM8962_VSS_XHN3_1                       0x5208
#define WM8962_VSS_XHN3_0                       0x5209
#define WM8962_VSS_XWA_1                        0x520A
#define WM8962_VSS_XWA_0                        0x520B
#define WM8962_VSS_XWB_1                        0x520C
#define WM8962_VSS_XWB_0                        0x520D
#define WM8962_VSS_XWG_1                        0x520E
#define WM8962_VSS_XWG_0                        0x520F
#define WM8962_VSS_PG2_1                        0x5210
#define WM8962_VSS_PG2_0                        0x5211
#define WM8962_VSS_PG_1                         0x5212
#define WM8962_VSS_PG_0                         0x5213
#define WM8962_VSS_XTD1_1                       0x5214
#define WM8962_VSS_XTD1_0                       0x5215
#define WM8962_VSS_XTD2_1                       0x5216
#define WM8962_VSS_XTD2_0                       0x5217
#define WM8962_VSS_XTD3_1                       0x5218
#define WM8962_VSS_XTD3_0                       0x5219
#define WM8962_VSS_XTD4_1                       0x521A
#define WM8962_VSS_XTD4_0                       0x521B
#define WM8962_VSS_XTD5_1                       0x521C
#define WM8962_VSS_XTD5_0                       0x521D
#define WM8962_VSS_XTD6_1                       0x521E
#define WM8962_VSS_XTD6_0                       0x521F
#define WM8962_VSS_XTD7_1                       0x5220
#define WM8962_VSS_XTD7_0                       0x5221
#define WM8962_VSS_XTD8_1                       0x5222
#define WM8962_VSS_XTD8_0                       0x5223
#define WM8962_VSS_XTD9_1                       0x5224
#define WM8962_VSS_XTD9_0                       0x5225
#define WM8962_VSS_XTD10_1                      0x5226
#define WM8962_VSS_XTD10_0                      0x5227
#define WM8962_VSS_XTD11_1                      0x5228
#define WM8962_VSS_XTD11_0                      0x5229
#define WM8962_VSS_XTD12_1                      0x522A
#define WM8962_VSS_XTD12_0                      0x522B
#define WM8962_VSS_XTD13_1                      0x522C
#define WM8962_VSS_XTD13_0                      0x522D
#define WM8962_VSS_XTD14_1                      0x522E
#define WM8962_VSS_XTD14_0                      0x522F
#define WM8962_VSS_XTD15_1                      0x5230
#define WM8962_VSS_XTD15_0                      0x5231
#define WM8962_VSS_XTD16_1                      0x5232
#define WM8962_VSS_XTD16_0                      0x5233
#define WM8962_VSS_XTD17_1                      0x5234
#define WM8962_VSS_XTD17_0                      0x5235
#define WM8962_VSS_XTD18_1                      0x5236
#define WM8962_VSS_XTD18_0                      0x5237
#define WM8962_VSS_XTD19_1                      0x5238
#define WM8962_VSS_XTD19_0                      0x5239
#define WM8962_VSS_XTD20_1                      0x523A
#define WM8962_VSS_XTD20_0                      0x523B
#define WM8962_VSS_XTD21_1                      0x523C
#define WM8962_VSS_XTD21_0                      0x523D
#define WM8962_VSS_XTD22_1                      0x523E
#define WM8962_VSS_XTD22_0                      0x523F
#define WM8962_VSS_XTD23_1                      0x5240
#define WM8962_VSS_XTD23_0                      0x5241
#define WM8962_VSS_XTD24_1                      0x5242
#define WM8962_VSS_XTD24_0                      0x5243
#define WM8962_VSS_XTD25_1                      0x5244
#define WM8962_VSS_XTD25_0                      0x5245
#define WM8962_VSS_XTD26_1                      0x5246
#define WM8962_VSS_XTD26_0                      0x5247
#define WM8962_VSS_XTD27_1                      0x5248
#define WM8962_VSS_XTD27_0                      0x5249
#define WM8962_VSS_XTD28_1                      0x524A
#define WM8962_VSS_XTD28_0                      0x524B
#define WM8962_VSS_XTD29_1                      0x524C
#define WM8962_VSS_XTD29_0                      0x524D
#define WM8962_VSS_XTD30_1                      0x524E
#define WM8962_VSS_XTD30_0                      0x524F
#define WM8962_VSS_XTD31_1                      0x5250
#define WM8962_VSS_XTD31_0                      0x5251
#define WM8962_VSS_XTD32_1                      0x5252
#define WM8962_VSS_XTD32_0                      0x5253
#define WM8962_VSS_XTS1_1                       0x5254
#define WM8962_VSS_XTS1_0                       0x5255
#define WM8962_VSS_XTS2_1                       0x5256
#define WM8962_VSS_XTS2_0                       0x5257
#define WM8962_VSS_XTS3_1                       0x5258
#define WM8962_VSS_XTS3_0                       0x5259
#define WM8962_VSS_XTS4_1                       0x525A
#define WM8962_VSS_XTS4_0                       0x525B
#define WM8962_VSS_XTS5_1                       0x525C
#define WM8962_VSS_XTS5_0                       0x525D
#define WM8962_VSS_XTS6_1                       0x525E
#define WM8962_VSS_XTS6_0                       0x525F
#define WM8962_VSS_XTS7_1                       0x5260
#define WM8962_VSS_XTS7_0                       0x5261
#define WM8962_VSS_XTS8_1                       0x5262
#define WM8962_VSS_XTS8_0                       0x5263
#define WM8962_VSS_XTS9_1                       0x5264
#define WM8962_VSS_XTS9_0                       0x5265
#define WM8962_VSS_XTS10_1                      0x5266
#define WM8962_VSS_XTS10_0                      0x5267
#define WM8962_VSS_XTS11_1                      0x5268
#define WM8962_VSS_XTS11_0                      0x5269
#define WM8962_VSS_XTS12_1                      0x526A
#define WM8962_VSS_XTS12_0                      0x526B
#define WM8962_VSS_XTS13_1                      0x526C
#define WM8962_VSS_XTS13_0                      0x526D
#define WM8962_VSS_XTS14_1                      0x526E
#define WM8962_VSS_XTS14_0                      0x526F
#define WM8962_VSS_XTS15_1                      0x5270
#define WM8962_VSS_XTS15_0                      0x5271
#define WM8962_VSS_XTS16_1                      0x5272
#define WM8962_VSS_XTS16_0                      0x5273
#define WM8962_VSS_XTS17_1                      0x5274
#define WM8962_VSS_XTS17_0                      0x5275
#define WM8962_VSS_XTS18_1                      0x5276
#define WM8962_VSS_XTS18_0                      0x5277
#define WM8962_VSS_XTS19_1                      0x5278
#define WM8962_VSS_XTS19_0                      0x5279
#define WM8962_VSS_XTS20_1                      0x527A
#define WM8962_VSS_XTS20_0                      0x527B
#define WM8962_VSS_XTS21_1                      0x527C
#define WM8962_VSS_XTS21_0                      0x527D
#define WM8962_VSS_XTS22_1                      0x527E
#define WM8962_VSS_XTS22_0                      0x527F
#define WM8962_VSS_XTS23_1                      0x5280
#define WM8962_VSS_XTS23_0                      0x5281
#define WM8962_VSS_XTS24_1                      0x5282
#define WM8962_VSS_XTS24_0                      0x5283
#define WM8962_VSS_XTS25_1                      0x5284
#define WM8962_VSS_XTS25_0                      0x5285
#define WM8962_VSS_XTS26_1                      0x5286
#define WM8962_VSS_XTS26_0                      0x5287
#define WM8962_VSS_XTS27_1                      0x5288
#define WM8962_VSS_XTS27_0                      0x5289
#define WM8962_VSS_XTS28_1                      0x528A
#define WM8962_VSS_XTS28_0                      0x528B
#define WM8962_VSS_XTS29_1                      0x528C
#define WM8962_VSS_XTS29_0                      0x528D
#define WM8962_VSS_XTS30_1                      0x528E
#define WM8962_VSS_XTS30_0                      0x528F
#define WM8962_VSS_XTS31_1                      0x5290
#define WM8962_VSS_XTS31_0                      0x5291
#define WM8962_VSS_XTS32_1                      0x5292
#define WM8962_VSS_XTS32_0                      0x5293

#define WM8962_WEGISTEW_COUNT                   1138
#define WM8962_MAX_WEGISTEW                     0x5293

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weft Input vowume
 */
#define WM8962_IN_VU                            0x0100  /* IN_VU */
#define WM8962_IN_VU_MASK                       0x0100  /* IN_VU */
#define WM8962_IN_VU_SHIFT                           8  /* IN_VU */
#define WM8962_IN_VU_WIDTH                           1  /* IN_VU */
#define WM8962_INPGAW_MUTE                      0x0080  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_MASK                 0x0080  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_SHIFT                     7  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_WIDTH                     1  /* INPGAW_MUTE */
#define WM8962_INW_ZC                           0x0040  /* INW_ZC */
#define WM8962_INW_ZC_MASK                      0x0040  /* INW_ZC */
#define WM8962_INW_ZC_SHIFT                          6  /* INW_ZC */
#define WM8962_INW_ZC_WIDTH                          1  /* INW_ZC */
#define WM8962_INW_VOW_MASK                     0x003F  /* INW_VOW - [5:0] */
#define WM8962_INW_VOW_SHIFT                         0  /* INW_VOW - [5:0] */
#define WM8962_INW_VOW_WIDTH                         6  /* INW_VOW - [5:0] */

/*
 * W1 (0x01) - Wight Input vowume
 */
#define WM8962_CUST_ID_MASK                     0xF000  /* CUST_ID - [15:12] */
#define WM8962_CUST_ID_SHIFT                        12  /* CUST_ID - [15:12] */
#define WM8962_CUST_ID_WIDTH                         4  /* CUST_ID - [15:12] */
#define WM8962_CHIP_WEV_MASK                    0x0E00  /* CHIP_WEV - [11:9] */
#define WM8962_CHIP_WEV_SHIFT                        9  /* CHIP_WEV - [11:9] */
#define WM8962_CHIP_WEV_WIDTH                        3  /* CHIP_WEV - [11:9] */
#define WM8962_IN_VU                            0x0100  /* IN_VU */
#define WM8962_IN_VU_MASK                       0x0100  /* IN_VU */
#define WM8962_IN_VU_SHIFT                           8  /* IN_VU */
#define WM8962_IN_VU_WIDTH                           1  /* IN_VU */
#define WM8962_INPGAW_MUTE                      0x0080  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_MASK                 0x0080  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_SHIFT                     7  /* INPGAW_MUTE */
#define WM8962_INPGAW_MUTE_WIDTH                     1  /* INPGAW_MUTE */
#define WM8962_INW_ZC                           0x0040  /* INW_ZC */
#define WM8962_INW_ZC_MASK                      0x0040  /* INW_ZC */
#define WM8962_INW_ZC_SHIFT                          6  /* INW_ZC */
#define WM8962_INW_ZC_WIDTH                          1  /* INW_ZC */
#define WM8962_INW_VOW_MASK                     0x003F  /* INW_VOW - [5:0] */
#define WM8962_INW_VOW_SHIFT                         0  /* INW_VOW - [5:0] */
#define WM8962_INW_VOW_WIDTH                         6  /* INW_VOW - [5:0] */

/*
 * W2 (0x02) - HPOUTW vowume
 */
#define WM8962_HPOUT_VU                         0x0100  /* HPOUT_VU */
#define WM8962_HPOUT_VU_MASK                    0x0100  /* HPOUT_VU */
#define WM8962_HPOUT_VU_SHIFT                        8  /* HPOUT_VU */
#define WM8962_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#define WM8962_HPOUTW_ZC                        0x0080  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_MASK                   0x0080  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_SHIFT                       7  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_WIDTH                       1  /* HPOUTW_ZC */
#define WM8962_HPOUTW_VOW_MASK                  0x007F  /* HPOUTW_VOW - [6:0] */
#define WM8962_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [6:0] */
#define WM8962_HPOUTW_VOW_WIDTH                      7  /* HPOUTW_VOW - [6:0] */

/*
 * W3 (0x03) - HPOUTW vowume
 */
#define WM8962_HPOUT_VU                         0x0100  /* HPOUT_VU */
#define WM8962_HPOUT_VU_MASK                    0x0100  /* HPOUT_VU */
#define WM8962_HPOUT_VU_SHIFT                        8  /* HPOUT_VU */
#define WM8962_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#define WM8962_HPOUTW_ZC                        0x0080  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_MASK                   0x0080  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_SHIFT                       7  /* HPOUTW_ZC */
#define WM8962_HPOUTW_ZC_WIDTH                       1  /* HPOUTW_ZC */
#define WM8962_HPOUTW_VOW_MASK                  0x007F  /* HPOUTW_VOW - [6:0] */
#define WM8962_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [6:0] */
#define WM8962_HPOUTW_VOW_WIDTH                      7  /* HPOUTW_VOW - [6:0] */

/*
 * W4 (0x04) - Cwocking1
 */
#define WM8962_DSPCWK_DIV_MASK                  0x0600  /* DSPCWK_DIV - [10:9] */
#define WM8962_DSPCWK_DIV_SHIFT                      9  /* DSPCWK_DIV - [10:9] */
#define WM8962_DSPCWK_DIV_WIDTH                      2  /* DSPCWK_DIV - [10:9] */
#define WM8962_ADCSYS_CWK_DIV_MASK              0x01C0  /* ADCSYS_CWK_DIV - [8:6] */
#define WM8962_ADCSYS_CWK_DIV_SHIFT                  6  /* ADCSYS_CWK_DIV - [8:6] */
#define WM8962_ADCSYS_CWK_DIV_WIDTH                  3  /* ADCSYS_CWK_DIV - [8:6] */
#define WM8962_DACSYS_CWK_DIV_MASK              0x0038  /* DACSYS_CWK_DIV - [5:3] */
#define WM8962_DACSYS_CWK_DIV_SHIFT                  3  /* DACSYS_CWK_DIV - [5:3] */
#define WM8962_DACSYS_CWK_DIV_WIDTH                  3  /* DACSYS_CWK_DIV - [5:3] */
#define WM8962_MCWKDIV_MASK                     0x0006  /* MCWKDIV - [2:1] */
#define WM8962_MCWKDIV_SHIFT                         1  /* MCWKDIV - [2:1] */
#define WM8962_MCWKDIV_WIDTH                         2  /* MCWKDIV - [2:1] */

/*
 * W5 (0x05) - ADC & DAC Contwow 1
 */
#define WM8962_ADCW_DAT_INV                     0x0040  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_MASK                0x0040  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_SHIFT                    6  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_WIDTH                    1  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV                     0x0020  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_MASK                0x0020  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_SHIFT                    5  /* ADCW_DAT_INV */
#define WM8962_ADCW_DAT_INV_WIDTH                    1  /* ADCW_DAT_INV */
#define WM8962_DAC_MUTE_WAMP                    0x0010  /* DAC_MUTE_WAMP */
#define WM8962_DAC_MUTE_WAMP_MASK               0x0010  /* DAC_MUTE_WAMP */
#define WM8962_DAC_MUTE_WAMP_SHIFT                   4  /* DAC_MUTE_WAMP */
#define WM8962_DAC_MUTE_WAMP_WIDTH                   1  /* DAC_MUTE_WAMP */
#define WM8962_DAC_MUTE                         0x0008  /* DAC_MUTE */
#define WM8962_DAC_MUTE_MASK                    0x0008  /* DAC_MUTE */
#define WM8962_DAC_MUTE_SHIFT                        3  /* DAC_MUTE */
#define WM8962_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#define WM8962_DAC_DEEMP_MASK                   0x0006  /* DAC_DEEMP - [2:1] */
#define WM8962_DAC_DEEMP_SHIFT                       1  /* DAC_DEEMP - [2:1] */
#define WM8962_DAC_DEEMP_WIDTH                       2  /* DAC_DEEMP - [2:1] */
#define WM8962_ADC_HPF_DIS                      0x0001  /* ADC_HPF_DIS */
#define WM8962_ADC_HPF_DIS_MASK                 0x0001  /* ADC_HPF_DIS */
#define WM8962_ADC_HPF_DIS_SHIFT                     0  /* ADC_HPF_DIS */
#define WM8962_ADC_HPF_DIS_WIDTH                     1  /* ADC_HPF_DIS */

/*
 * W6 (0x06) - ADC & DAC Contwow 2
 */
#define WM8962_ADC_HPF_SW_MASK                  0x3000  /* ADC_HPF_SW - [13:12] */
#define WM8962_ADC_HPF_SW_SHIFT                     12  /* ADC_HPF_SW - [13:12] */
#define WM8962_ADC_HPF_SW_WIDTH                      2  /* ADC_HPF_SW - [13:12] */
#define WM8962_ADC_HPF_MODE                     0x0400  /* ADC_HPF_MODE */
#define WM8962_ADC_HPF_MODE_MASK                0x0400  /* ADC_HPF_MODE */
#define WM8962_ADC_HPF_MODE_SHIFT                   10  /* ADC_HPF_MODE */
#define WM8962_ADC_HPF_MODE_WIDTH                    1  /* ADC_HPF_MODE */
#define WM8962_ADC_HPF_CUT_MASK                 0x0380  /* ADC_HPF_CUT - [9:7] */
#define WM8962_ADC_HPF_CUT_SHIFT                     7  /* ADC_HPF_CUT - [9:7] */
#define WM8962_ADC_HPF_CUT_WIDTH                     3  /* ADC_HPF_CUT - [9:7] */
#define WM8962_DACW_DAT_INV                     0x0040  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_MASK                0x0040  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_SHIFT                    6  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_WIDTH                    1  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV                     0x0020  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_MASK                0x0020  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_SHIFT                    5  /* DACW_DAT_INV */
#define WM8962_DACW_DAT_INV_WIDTH                    1  /* DACW_DAT_INV */
#define WM8962_DAC_UNMUTE_WAMP                  0x0008  /* DAC_UNMUTE_WAMP */
#define WM8962_DAC_UNMUTE_WAMP_MASK             0x0008  /* DAC_UNMUTE_WAMP */
#define WM8962_DAC_UNMUTE_WAMP_SHIFT                 3  /* DAC_UNMUTE_WAMP */
#define WM8962_DAC_UNMUTE_WAMP_WIDTH                 1  /* DAC_UNMUTE_WAMP */
#define WM8962_DAC_MUTEWATE                     0x0004  /* DAC_MUTEWATE */
#define WM8962_DAC_MUTEWATE_MASK                0x0004  /* DAC_MUTEWATE */
#define WM8962_DAC_MUTEWATE_SHIFT                    2  /* DAC_MUTEWATE */
#define WM8962_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */
#define WM8962_DAC_HP                           0x0001  /* DAC_HP */
#define WM8962_DAC_HP_MASK                      0x0001  /* DAC_HP */
#define WM8962_DAC_HP_SHIFT                          0  /* DAC_HP */
#define WM8962_DAC_HP_WIDTH                          1  /* DAC_HP */

/*
 * W7 (0x07) - Audio Intewface 0
 */
#define WM8962_AIFDAC_TDM_MODE                  0x1000  /* AIFDAC_TDM_MODE */
#define WM8962_AIFDAC_TDM_MODE_MASK             0x1000  /* AIFDAC_TDM_MODE */
#define WM8962_AIFDAC_TDM_MODE_SHIFT                12  /* AIFDAC_TDM_MODE */
#define WM8962_AIFDAC_TDM_MODE_WIDTH                 1  /* AIFDAC_TDM_MODE */
#define WM8962_AIFDAC_TDM_SWOT                  0x0800  /* AIFDAC_TDM_SWOT */
#define WM8962_AIFDAC_TDM_SWOT_MASK             0x0800  /* AIFDAC_TDM_SWOT */
#define WM8962_AIFDAC_TDM_SWOT_SHIFT                11  /* AIFDAC_TDM_SWOT */
#define WM8962_AIFDAC_TDM_SWOT_WIDTH                 1  /* AIFDAC_TDM_SWOT */
#define WM8962_AIFADC_TDM_MODE                  0x0400  /* AIFADC_TDM_MODE */
#define WM8962_AIFADC_TDM_MODE_MASK             0x0400  /* AIFADC_TDM_MODE */
#define WM8962_AIFADC_TDM_MODE_SHIFT                10  /* AIFADC_TDM_MODE */
#define WM8962_AIFADC_TDM_MODE_WIDTH                 1  /* AIFADC_TDM_MODE */
#define WM8962_AIFADC_TDM_SWOT                  0x0200  /* AIFADC_TDM_SWOT */
#define WM8962_AIFADC_TDM_SWOT_MASK             0x0200  /* AIFADC_TDM_SWOT */
#define WM8962_AIFADC_TDM_SWOT_SHIFT                 9  /* AIFADC_TDM_SWOT */
#define WM8962_AIFADC_TDM_SWOT_WIDTH                 1  /* AIFADC_TDM_SWOT */
#define WM8962_ADC_WWSWAP                       0x0100  /* ADC_WWSWAP */
#define WM8962_ADC_WWSWAP_MASK                  0x0100  /* ADC_WWSWAP */
#define WM8962_ADC_WWSWAP_SHIFT                      8  /* ADC_WWSWAP */
#define WM8962_ADC_WWSWAP_WIDTH                      1  /* ADC_WWSWAP */
#define WM8962_BCWK_INV                         0x0080  /* BCWK_INV */
#define WM8962_BCWK_INV_MASK                    0x0080  /* BCWK_INV */
#define WM8962_BCWK_INV_SHIFT                        7  /* BCWK_INV */
#define WM8962_BCWK_INV_WIDTH                        1  /* BCWK_INV */
#define WM8962_MSTW                             0x0040  /* MSTW */
#define WM8962_MSTW_MASK                        0x0040  /* MSTW */
#define WM8962_MSTW_SHIFT                            6  /* MSTW */
#define WM8962_MSTW_WIDTH                            1  /* MSTW */
#define WM8962_DAC_WWSWAP                       0x0020  /* DAC_WWSWAP */
#define WM8962_DAC_WWSWAP_MASK                  0x0020  /* DAC_WWSWAP */
#define WM8962_DAC_WWSWAP_SHIFT                      5  /* DAC_WWSWAP */
#define WM8962_DAC_WWSWAP_WIDTH                      1  /* DAC_WWSWAP */
#define WM8962_WWCWK_INV                        0x0010  /* WWCWK_INV */
#define WM8962_WWCWK_INV_MASK                   0x0010  /* WWCWK_INV */
#define WM8962_WWCWK_INV_SHIFT                       4  /* WWCWK_INV */
#define WM8962_WWCWK_INV_WIDTH                       1  /* WWCWK_INV */
#define WM8962_WW_MASK                          0x000C  /* WW - [3:2] */
#define WM8962_WW_SHIFT                              2  /* WW - [3:2] */
#define WM8962_WW_WIDTH                              2  /* WW - [3:2] */
#define WM8962_FMT_MASK                         0x0003  /* FMT - [1:0] */
#define WM8962_FMT_SHIFT                             0  /* FMT - [1:0] */
#define WM8962_FMT_WIDTH                             2  /* FMT - [1:0] */

/*
 * W8 (0x08) - Cwocking2
 */
#define WM8962_CWKWEG_OVD                       0x0800  /* CWKWEG_OVD */
#define WM8962_CWKWEG_OVD_MASK                  0x0800  /* CWKWEG_OVD */
#define WM8962_CWKWEG_OVD_SHIFT                     11  /* CWKWEG_OVD */
#define WM8962_CWKWEG_OVD_WIDTH                      1  /* CWKWEG_OVD */
#define WM8962_SYSCWK_SWC_MASK                  0x0600  /* SYSCWK_SWC - [10:9] */
#define WM8962_SYSCWK_SWC_SHIFT                      9  /* SYSCWK_SWC - [10:9] */
#define WM8962_SYSCWK_SWC_WIDTH                      2  /* SYSCWK_SWC - [10:9] */
#define WM8962_CWASSD_CWK_DIV_MASK              0x01C0  /* CWASSD_CWK_DIV - [8:6] */
#define WM8962_CWASSD_CWK_DIV_SHIFT                  6  /* CWASSD_CWK_DIV - [8:6] */
#define WM8962_CWASSD_CWK_DIV_WIDTH                  3  /* CWASSD_CWK_DIV - [8:6] */
#define WM8962_SYSCWK_ENA                       0x0020  /* SYSCWK_ENA */
#define WM8962_SYSCWK_ENA_MASK                  0x0020  /* SYSCWK_ENA */
#define WM8962_SYSCWK_ENA_SHIFT                      5  /* SYSCWK_ENA */
#define WM8962_SYSCWK_ENA_WIDTH                      1  /* SYSCWK_ENA */
#define WM8962_BCWK_DIV_MASK                    0x000F  /* BCWK_DIV - [3:0] */
#define WM8962_BCWK_DIV_SHIFT                        0  /* BCWK_DIV - [3:0] */
#define WM8962_BCWK_DIV_WIDTH                        4  /* BCWK_DIV - [3:0] */

/*
 * W9 (0x09) - Audio Intewface 1
 */
#define WM8962_AUTOMUTE_STS                     0x0800  /* AUTOMUTE_STS */
#define WM8962_AUTOMUTE_STS_MASK                0x0800  /* AUTOMUTE_STS */
#define WM8962_AUTOMUTE_STS_SHIFT                   11  /* AUTOMUTE_STS */
#define WM8962_AUTOMUTE_STS_WIDTH                    1  /* AUTOMUTE_STS */
#define WM8962_DAC_AUTOMUTE_SAMPWES_MASK        0x0300  /* DAC_AUTOMUTE_SAMPWES - [9:8] */
#define WM8962_DAC_AUTOMUTE_SAMPWES_SHIFT            8  /* DAC_AUTOMUTE_SAMPWES - [9:8] */
#define WM8962_DAC_AUTOMUTE_SAMPWES_WIDTH            2  /* DAC_AUTOMUTE_SAMPWES - [9:8] */
#define WM8962_DAC_AUTOMUTE                     0x0080  /* DAC_AUTOMUTE */
#define WM8962_DAC_AUTOMUTE_MASK                0x0080  /* DAC_AUTOMUTE */
#define WM8962_DAC_AUTOMUTE_SHIFT                    7  /* DAC_AUTOMUTE */
#define WM8962_DAC_AUTOMUTE_WIDTH                    1  /* DAC_AUTOMUTE */
#define WM8962_DAC_COMP                         0x0010  /* DAC_COMP */
#define WM8962_DAC_COMP_MASK                    0x0010  /* DAC_COMP */
#define WM8962_DAC_COMP_SHIFT                        4  /* DAC_COMP */
#define WM8962_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#define WM8962_DAC_COMPMODE                     0x0008  /* DAC_COMPMODE */
#define WM8962_DAC_COMPMODE_MASK                0x0008  /* DAC_COMPMODE */
#define WM8962_DAC_COMPMODE_SHIFT                    3  /* DAC_COMPMODE */
#define WM8962_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */
#define WM8962_ADC_COMP                         0x0004  /* ADC_COMP */
#define WM8962_ADC_COMP_MASK                    0x0004  /* ADC_COMP */
#define WM8962_ADC_COMP_SHIFT                        2  /* ADC_COMP */
#define WM8962_ADC_COMP_WIDTH                        1  /* ADC_COMP */
#define WM8962_ADC_COMPMODE                     0x0002  /* ADC_COMPMODE */
#define WM8962_ADC_COMPMODE_MASK                0x0002  /* ADC_COMPMODE */
#define WM8962_ADC_COMPMODE_SHIFT                    1  /* ADC_COMPMODE */
#define WM8962_ADC_COMPMODE_WIDTH                    1  /* ADC_COMPMODE */
#define WM8962_WOOPBACK                         0x0001  /* WOOPBACK */
#define WM8962_WOOPBACK_MASK                    0x0001  /* WOOPBACK */
#define WM8962_WOOPBACK_SHIFT                        0  /* WOOPBACK */
#define WM8962_WOOPBACK_WIDTH                        1  /* WOOPBACK */

/*
 * W10 (0x0A) - Weft DAC vowume
 */
#define WM8962_DAC_VU                           0x0100  /* DAC_VU */
#define WM8962_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8962_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8962_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8962_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8962_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8962_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W11 (0x0B) - Wight DAC vowume
 */
#define WM8962_DAC_VU                           0x0100  /* DAC_VU */
#define WM8962_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8962_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8962_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8962_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8962_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8962_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W14 (0x0E) - Audio Intewface 2
 */
#define WM8962_AIF_WATE_MASK                    0x07FF  /* AIF_WATE - [10:0] */
#define WM8962_AIF_WATE_SHIFT                        0  /* AIF_WATE - [10:0] */
#define WM8962_AIF_WATE_WIDTH                       11  /* AIF_WATE - [10:0] */

/*
 * W15 (0x0F) - Softwawe Weset
 */
#define WM8962_SW_WESET_MASK                    0xFFFF  /* SW_WESET - [15:0] */
#define WM8962_SW_WESET_SHIFT                        0  /* SW_WESET - [15:0] */
#define WM8962_SW_WESET_WIDTH                       16  /* SW_WESET - [15:0] */

/*
 * W17 (0x11) - AWC1
 */
#define WM8962_AWC_INACTIVE_ENA                 0x0400  /* AWC_INACTIVE_ENA */
#define WM8962_AWC_INACTIVE_ENA_MASK            0x0400  /* AWC_INACTIVE_ENA */
#define WM8962_AWC_INACTIVE_ENA_SHIFT               10  /* AWC_INACTIVE_ENA */
#define WM8962_AWC_INACTIVE_ENA_WIDTH                1  /* AWC_INACTIVE_ENA */
#define WM8962_AWC_WVW_MODE                     0x0200  /* AWC_WVW_MODE */
#define WM8962_AWC_WVW_MODE_MASK                0x0200  /* AWC_WVW_MODE */
#define WM8962_AWC_WVW_MODE_SHIFT                    9  /* AWC_WVW_MODE */
#define WM8962_AWC_WVW_MODE_WIDTH                    1  /* AWC_WVW_MODE */
#define WM8962_AWCW_ENA                         0x0100  /* AWCW_ENA */
#define WM8962_AWCW_ENA_MASK                    0x0100  /* AWCW_ENA */
#define WM8962_AWCW_ENA_SHIFT                        8  /* AWCW_ENA */
#define WM8962_AWCW_ENA_WIDTH                        1  /* AWCW_ENA */
#define WM8962_AWCW_ENA                         0x0080  /* AWCW_ENA */
#define WM8962_AWCW_ENA_MASK                    0x0080  /* AWCW_ENA */
#define WM8962_AWCW_ENA_SHIFT                        7  /* AWCW_ENA */
#define WM8962_AWCW_ENA_WIDTH                        1  /* AWCW_ENA */
#define WM8962_AWC_MAXGAIN_MASK                 0x0070  /* AWC_MAXGAIN - [6:4] */
#define WM8962_AWC_MAXGAIN_SHIFT                     4  /* AWC_MAXGAIN - [6:4] */
#define WM8962_AWC_MAXGAIN_WIDTH                     3  /* AWC_MAXGAIN - [6:4] */
#define WM8962_AWC_WVW_MASK                     0x000F  /* AWC_WVW - [3:0] */
#define WM8962_AWC_WVW_SHIFT                         0  /* AWC_WVW - [3:0] */
#define WM8962_AWC_WVW_WIDTH                         4  /* AWC_WVW - [3:0] */

/*
 * W18 (0x12) - AWC2
 */
#define WM8962_AWC_WOCK_STS                     0x8000  /* AWC_WOCK_STS */
#define WM8962_AWC_WOCK_STS_MASK                0x8000  /* AWC_WOCK_STS */
#define WM8962_AWC_WOCK_STS_SHIFT                   15  /* AWC_WOCK_STS */
#define WM8962_AWC_WOCK_STS_WIDTH                    1  /* AWC_WOCK_STS */
#define WM8962_AWC_THWESH_STS                   0x4000  /* AWC_THWESH_STS */
#define WM8962_AWC_THWESH_STS_MASK              0x4000  /* AWC_THWESH_STS */
#define WM8962_AWC_THWESH_STS_SHIFT                 14  /* AWC_THWESH_STS */
#define WM8962_AWC_THWESH_STS_WIDTH                  1  /* AWC_THWESH_STS */
#define WM8962_AWC_SAT_STS                      0x2000  /* AWC_SAT_STS */
#define WM8962_AWC_SAT_STS_MASK                 0x2000  /* AWC_SAT_STS */
#define WM8962_AWC_SAT_STS_SHIFT                    13  /* AWC_SAT_STS */
#define WM8962_AWC_SAT_STS_WIDTH                     1  /* AWC_SAT_STS */
#define WM8962_AWC_PKOVW_STS                    0x1000  /* AWC_PKOVW_STS */
#define WM8962_AWC_PKOVW_STS_MASK               0x1000  /* AWC_PKOVW_STS */
#define WM8962_AWC_PKOVW_STS_SHIFT                  12  /* AWC_PKOVW_STS */
#define WM8962_AWC_PKOVW_STS_WIDTH                   1  /* AWC_PKOVW_STS */
#define WM8962_AWC_NGATE_STS                    0x0800  /* AWC_NGATE_STS */
#define WM8962_AWC_NGATE_STS_MASK               0x0800  /* AWC_NGATE_STS */
#define WM8962_AWC_NGATE_STS_SHIFT                  11  /* AWC_NGATE_STS */
#define WM8962_AWC_NGATE_STS_WIDTH                   1  /* AWC_NGATE_STS */
#define WM8962_AWC_ZC                           0x0080  /* AWC_ZC */
#define WM8962_AWC_ZC_MASK                      0x0080  /* AWC_ZC */
#define WM8962_AWC_ZC_SHIFT                          7  /* AWC_ZC */
#define WM8962_AWC_ZC_WIDTH                          1  /* AWC_ZC */
#define WM8962_AWC_MINGAIN_MASK                 0x0070  /* AWC_MINGAIN - [6:4] */
#define WM8962_AWC_MINGAIN_SHIFT                     4  /* AWC_MINGAIN - [6:4] */
#define WM8962_AWC_MINGAIN_WIDTH                     3  /* AWC_MINGAIN - [6:4] */
#define WM8962_AWC_HWD_MASK                     0x000F  /* AWC_HWD - [3:0] */
#define WM8962_AWC_HWD_SHIFT                         0  /* AWC_HWD - [3:0] */
#define WM8962_AWC_HWD_WIDTH                         4  /* AWC_HWD - [3:0] */

/*
 * W19 (0x13) - AWC3
 */
#define WM8962_AWC_NGATE_GAIN_MASK              0x1C00  /* AWC_NGATE_GAIN - [12:10] */
#define WM8962_AWC_NGATE_GAIN_SHIFT                 10  /* AWC_NGATE_GAIN - [12:10] */
#define WM8962_AWC_NGATE_GAIN_WIDTH                  3  /* AWC_NGATE_GAIN - [12:10] */
#define WM8962_AWC_MODE                         0x0100  /* AWC_MODE */
#define WM8962_AWC_MODE_MASK                    0x0100  /* AWC_MODE */
#define WM8962_AWC_MODE_SHIFT                        8  /* AWC_MODE */
#define WM8962_AWC_MODE_WIDTH                        1  /* AWC_MODE */
#define WM8962_AWC_DCY_MASK                     0x00F0  /* AWC_DCY - [7:4] */
#define WM8962_AWC_DCY_SHIFT                         4  /* AWC_DCY - [7:4] */
#define WM8962_AWC_DCY_WIDTH                         4  /* AWC_DCY - [7:4] */
#define WM8962_AWC_ATK_MASK                     0x000F  /* AWC_ATK - [3:0] */
#define WM8962_AWC_ATK_SHIFT                         0  /* AWC_ATK - [3:0] */
#define WM8962_AWC_ATK_WIDTH                         4  /* AWC_ATK - [3:0] */

/*
 * W20 (0x14) - Noise Gate
 */
#define WM8962_AWC_NGATE_DCY_MASK               0xF000  /* AWC_NGATE_DCY - [15:12] */
#define WM8962_AWC_NGATE_DCY_SHIFT                  12  /* AWC_NGATE_DCY - [15:12] */
#define WM8962_AWC_NGATE_DCY_WIDTH                   4  /* AWC_NGATE_DCY - [15:12] */
#define WM8962_AWC_NGATE_ATK_MASK               0x0F00  /* AWC_NGATE_ATK - [11:8] */
#define WM8962_AWC_NGATE_ATK_SHIFT                   8  /* AWC_NGATE_ATK - [11:8] */
#define WM8962_AWC_NGATE_ATK_WIDTH                   4  /* AWC_NGATE_ATK - [11:8] */
#define WM8962_AWC_NGATE_THW_MASK               0x00F8  /* AWC_NGATE_THW - [7:3] */
#define WM8962_AWC_NGATE_THW_SHIFT                   3  /* AWC_NGATE_THW - [7:3] */
#define WM8962_AWC_NGATE_THW_WIDTH                   5  /* AWC_NGATE_THW - [7:3] */
#define WM8962_AWC_NGATE_MODE_MASK              0x0006  /* AWC_NGATE_MODE - [2:1] */
#define WM8962_AWC_NGATE_MODE_SHIFT                  1  /* AWC_NGATE_MODE - [2:1] */
#define WM8962_AWC_NGATE_MODE_WIDTH                  2  /* AWC_NGATE_MODE - [2:1] */
#define WM8962_AWC_NGATE_ENA                    0x0001  /* AWC_NGATE_ENA */
#define WM8962_AWC_NGATE_ENA_MASK               0x0001  /* AWC_NGATE_ENA */
#define WM8962_AWC_NGATE_ENA_SHIFT                   0  /* AWC_NGATE_ENA */
#define WM8962_AWC_NGATE_ENA_WIDTH                   1  /* AWC_NGATE_ENA */

/*
 * W21 (0x15) - Weft ADC vowume
 */
#define WM8962_ADC_VU                           0x0100  /* ADC_VU */
#define WM8962_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8962_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8962_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8962_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8962_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8962_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W22 (0x16) - Wight ADC vowume
 */
#define WM8962_ADC_VU                           0x0100  /* ADC_VU */
#define WM8962_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8962_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8962_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8962_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8962_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8962_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W23 (0x17) - Additionaw contwow(1)
 */
#define WM8962_THEWW_ACT                        0x0100  /* THEWW_ACT */
#define WM8962_THEWW_ACT_MASK                   0x0100  /* THEWW_ACT */
#define WM8962_THEWW_ACT_SHIFT                       8  /* THEWW_ACT */
#define WM8962_THEWW_ACT_WIDTH                       1  /* THEWW_ACT */
#define WM8962_ADC_BIAS                         0x0040  /* ADC_BIAS */
#define WM8962_ADC_BIAS_MASK                    0x0040  /* ADC_BIAS */
#define WM8962_ADC_BIAS_SHIFT                        6  /* ADC_BIAS */
#define WM8962_ADC_BIAS_WIDTH                        1  /* ADC_BIAS */
#define WM8962_ADC_HP                           0x0020  /* ADC_HP */
#define WM8962_ADC_HP_MASK                      0x0020  /* ADC_HP */
#define WM8962_ADC_HP_SHIFT                          5  /* ADC_HP */
#define WM8962_ADC_HP_WIDTH                          1  /* ADC_HP */
#define WM8962_TOCWK_ENA                        0x0001  /* TOCWK_ENA */
#define WM8962_TOCWK_ENA_MASK                   0x0001  /* TOCWK_ENA */
#define WM8962_TOCWK_ENA_SHIFT                       0  /* TOCWK_ENA */
#define WM8962_TOCWK_ENA_WIDTH                       1  /* TOCWK_ENA */

/*
 * W24 (0x18) - Additionaw contwow(2)
 */
#define WM8962_AIF_TWI                          0x0008  /* AIF_TWI */
#define WM8962_AIF_TWI_MASK                     0x0008  /* AIF_TWI */
#define WM8962_AIF_TWI_SHIFT                         3  /* AIF_TWI */
#define WM8962_AIF_TWI_WIDTH                         1  /* AIF_TWI */

/*
 * W25 (0x19) - Pww Mgmt (1)
 */
#define WM8962_DMIC_ENA                         0x0400  /* DMIC_ENA */
#define WM8962_DMIC_ENA_MASK                    0x0400  /* DMIC_ENA */
#define WM8962_DMIC_ENA_SHIFT                       10  /* DMIC_ENA */
#define WM8962_DMIC_ENA_WIDTH                        1  /* DMIC_ENA */
#define WM8962_OPCWK_ENA                        0x0200  /* OPCWK_ENA */
#define WM8962_OPCWK_ENA_MASK                   0x0200  /* OPCWK_ENA */
#define WM8962_OPCWK_ENA_SHIFT                       9  /* OPCWK_ENA */
#define WM8962_OPCWK_ENA_WIDTH                       1  /* OPCWK_ENA */
#define WM8962_VMID_SEW_MASK                    0x0180  /* VMID_SEW - [8:7] */
#define WM8962_VMID_SEW_SHIFT                        7  /* VMID_SEW - [8:7] */
#define WM8962_VMID_SEW_WIDTH                        2  /* VMID_SEW - [8:7] */
#define WM8962_BIAS_ENA                         0x0040  /* BIAS_ENA */
#define WM8962_BIAS_ENA_MASK                    0x0040  /* BIAS_ENA */
#define WM8962_BIAS_ENA_SHIFT                        6  /* BIAS_ENA */
#define WM8962_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */
#define WM8962_INW_ENA                          0x0020  /* INW_ENA */
#define WM8962_INW_ENA_MASK                     0x0020  /* INW_ENA */
#define WM8962_INW_ENA_SHIFT                         5  /* INW_ENA */
#define WM8962_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8962_INW_ENA                          0x0010  /* INW_ENA */
#define WM8962_INW_ENA_MASK                     0x0010  /* INW_ENA */
#define WM8962_INW_ENA_SHIFT                         4  /* INW_ENA */
#define WM8962_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8962_ADCW_ENA                         0x0008  /* ADCW_ENA */
#define WM8962_ADCW_ENA_MASK                    0x0008  /* ADCW_ENA */
#define WM8962_ADCW_ENA_SHIFT                        3  /* ADCW_ENA */
#define WM8962_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8962_ADCW_ENA                         0x0004  /* ADCW_ENA */
#define WM8962_ADCW_ENA_MASK                    0x0004  /* ADCW_ENA */
#define WM8962_ADCW_ENA_SHIFT                        2  /* ADCW_ENA */
#define WM8962_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8962_MICBIAS_ENA                      0x0002  /* MICBIAS_ENA */
#define WM8962_MICBIAS_ENA_MASK                 0x0002  /* MICBIAS_ENA */
#define WM8962_MICBIAS_ENA_SHIFT                     1  /* MICBIAS_ENA */
#define WM8962_MICBIAS_ENA_WIDTH                     1  /* MICBIAS_ENA */

/*
 * W26 (0x1A) - Pww Mgmt (2)
 */
#define WM8962_DACW_ENA                         0x0100  /* DACW_ENA */
#define WM8962_DACW_ENA_MASK                    0x0100  /* DACW_ENA */
#define WM8962_DACW_ENA_SHIFT                        8  /* DACW_ENA */
#define WM8962_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8962_DACW_ENA                         0x0080  /* DACW_ENA */
#define WM8962_DACW_ENA_MASK                    0x0080  /* DACW_ENA */
#define WM8962_DACW_ENA_SHIFT                        7  /* DACW_ENA */
#define WM8962_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8962_HPOUTW_PGA_ENA                   0x0040  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_MASK              0x0040  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_SHIFT                  6  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_WIDTH                  1  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA                   0x0020  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_MASK              0x0020  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_SHIFT                  5  /* HPOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_ENA_WIDTH                  1  /* HPOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA                  0x0010  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_MASK             0x0010  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_SHIFT                 4  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_WIDTH                 1  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA                  0x0008  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_MASK             0x0008  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_SHIFT                 3  /* SPKOUTW_PGA_ENA */
#define WM8962_SPKOUTW_PGA_ENA_WIDTH                 1  /* SPKOUTW_PGA_ENA */
#define WM8962_HPOUTW_PGA_MUTE                  0x0002  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_MASK             0x0002  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_SHIFT                 1  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_WIDTH                 1  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE                  0x0001  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_MASK             0x0001  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_SHIFT                 0  /* HPOUTW_PGA_MUTE */
#define WM8962_HPOUTW_PGA_MUTE_WIDTH                 1  /* HPOUTW_PGA_MUTE */

/*
 * W27 (0x1B) - Additionaw Contwow (3)
 */
#define WM8962_SAMPWE_WATE_INT_MODE             0x0010  /* SAMPWE_WATE_INT_MODE */
#define WM8962_SAMPWE_WATE_INT_MODE_MASK        0x0010  /* SAMPWE_WATE_INT_MODE */
#define WM8962_SAMPWE_WATE_INT_MODE_SHIFT            4  /* SAMPWE_WATE_INT_MODE */
#define WM8962_SAMPWE_WATE_INT_MODE_WIDTH            1  /* SAMPWE_WATE_INT_MODE */
#define WM8962_SAMPWE_WATE_MASK                 0x0007  /* SAMPWE_WATE - [2:0] */
#define WM8962_SAMPWE_WATE_SHIFT                     0  /* SAMPWE_WATE - [2:0] */
#define WM8962_SAMPWE_WATE_WIDTH                     3  /* SAMPWE_WATE - [2:0] */

/*
 * W28 (0x1C) - Anti-pop
 */
#define WM8962_STAWTUP_BIAS_ENA                 0x0010  /* STAWTUP_BIAS_ENA */
#define WM8962_STAWTUP_BIAS_ENA_MASK            0x0010  /* STAWTUP_BIAS_ENA */
#define WM8962_STAWTUP_BIAS_ENA_SHIFT                4  /* STAWTUP_BIAS_ENA */
#define WM8962_STAWTUP_BIAS_ENA_WIDTH                1  /* STAWTUP_BIAS_ENA */
#define WM8962_VMID_BUF_ENA                     0x0008  /* VMID_BUF_ENA */
#define WM8962_VMID_BUF_ENA_MASK                0x0008  /* VMID_BUF_ENA */
#define WM8962_VMID_BUF_ENA_SHIFT                    3  /* VMID_BUF_ENA */
#define WM8962_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */
#define WM8962_VMID_WAMP                        0x0004  /* VMID_WAMP */
#define WM8962_VMID_WAMP_MASK                   0x0004  /* VMID_WAMP */
#define WM8962_VMID_WAMP_SHIFT                       2  /* VMID_WAMP */
#define WM8962_VMID_WAMP_WIDTH                       1  /* VMID_WAMP */

/*
 * W30 (0x1E) - Cwocking 3
 */
#define WM8962_DBCWK_DIV_MASK                   0xE000  /* DBCWK_DIV - [15:13] */
#define WM8962_DBCWK_DIV_SHIFT                      13  /* DBCWK_DIV - [15:13] */
#define WM8962_DBCWK_DIV_WIDTH                       3  /* DBCWK_DIV - [15:13] */
#define WM8962_OPCWK_DIV_MASK                   0x1C00  /* OPCWK_DIV - [12:10] */
#define WM8962_OPCWK_DIV_SHIFT                      10  /* OPCWK_DIV - [12:10] */
#define WM8962_OPCWK_DIV_WIDTH                       3  /* OPCWK_DIV - [12:10] */
#define WM8962_TOCWK_DIV_MASK                   0x0380  /* TOCWK_DIV - [9:7] */
#define WM8962_TOCWK_DIV_SHIFT                       7  /* TOCWK_DIV - [9:7] */
#define WM8962_TOCWK_DIV_WIDTH                       3  /* TOCWK_DIV - [9:7] */
#define WM8962_F256KCWK_DIV_MASK                0x007E  /* F256KCWK_DIV - [6:1] */
#define WM8962_F256KCWK_DIV_SHIFT                    1  /* F256KCWK_DIV - [6:1] */
#define WM8962_F256KCWK_DIV_WIDTH                    6  /* F256KCWK_DIV - [6:1] */

/*
 * W31 (0x1F) - Input mixew contwow (1)
 */
#define WM8962_MIXINW_MUTE                      0x0008  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_MASK                 0x0008  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_SHIFT                     3  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_WIDTH                     1  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE                      0x0004  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_MASK                 0x0004  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_SHIFT                     2  /* MIXINW_MUTE */
#define WM8962_MIXINW_MUTE_WIDTH                     1  /* MIXINW_MUTE */
#define WM8962_MIXINW_ENA                       0x0002  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_MASK                  0x0002  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_SHIFT                      1  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_WIDTH                      1  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA                       0x0001  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_MASK                  0x0001  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_SHIFT                      0  /* MIXINW_ENA */
#define WM8962_MIXINW_ENA_WIDTH                      1  /* MIXINW_ENA */

/*
 * W32 (0x20) - Weft input mixew vowume
 */
#define WM8962_IN2W_MIXINW_VOW_MASK             0x01C0  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_IN2W_MIXINW_VOW_SHIFT                 6  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_IN2W_MIXINW_VOW_WIDTH                 3  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_INPGAW_MIXINW_VOW_MASK           0x0038  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_INPGAW_MIXINW_VOW_SHIFT               3  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_INPGAW_MIXINW_VOW_WIDTH               3  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_IN3W_MIXINW_VOW_MASK             0x0007  /* IN3W_MIXINW_VOW - [2:0] */
#define WM8962_IN3W_MIXINW_VOW_SHIFT                 0  /* IN3W_MIXINW_VOW - [2:0] */
#define WM8962_IN3W_MIXINW_VOW_WIDTH                 3  /* IN3W_MIXINW_VOW - [2:0] */

/*
 * W33 (0x21) - Wight input mixew vowume
 */
#define WM8962_IN2W_MIXINW_VOW_MASK             0x01C0  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_IN2W_MIXINW_VOW_SHIFT                 6  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_IN2W_MIXINW_VOW_WIDTH                 3  /* IN2W_MIXINW_VOW - [8:6] */
#define WM8962_INPGAW_MIXINW_VOW_MASK           0x0038  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_INPGAW_MIXINW_VOW_SHIFT               3  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_INPGAW_MIXINW_VOW_WIDTH               3  /* INPGAW_MIXINW_VOW - [5:3] */
#define WM8962_IN3W_MIXINW_VOW_MASK             0x0007  /* IN3W_MIXINW_VOW - [2:0] */
#define WM8962_IN3W_MIXINW_VOW_SHIFT                 0  /* IN3W_MIXINW_VOW - [2:0] */
#define WM8962_IN3W_MIXINW_VOW_WIDTH                 3  /* IN3W_MIXINW_VOW - [2:0] */

/*
 * W34 (0x22) - Input mixew contwow (2)
 */
#define WM8962_IN2W_TO_MIXINW                   0x0020  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_MASK              0x0020  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_SHIFT                  5  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_WIDTH                  1  /* IN2W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW                   0x0010  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_MASK              0x0010  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_SHIFT                  4  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_WIDTH                  1  /* IN3W_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW                 0x0008  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_MASK            0x0008  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_SHIFT                3  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_WIDTH                1  /* INPGAW_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW                   0x0004  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_MASK              0x0004  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_SHIFT                  2  /* IN2W_TO_MIXINW */
#define WM8962_IN2W_TO_MIXINW_WIDTH                  1  /* IN2W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW                   0x0002  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_MASK              0x0002  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_SHIFT                  1  /* IN3W_TO_MIXINW */
#define WM8962_IN3W_TO_MIXINW_WIDTH                  1  /* IN3W_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW                 0x0001  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_MASK            0x0001  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_SHIFT                0  /* INPGAW_TO_MIXINW */
#define WM8962_INPGAW_TO_MIXINW_WIDTH                1  /* INPGAW_TO_MIXINW */

/*
 * W35 (0x23) - Input bias contwow
 */
#define WM8962_MIXIN_BIAS_MASK                  0x0038  /* MIXIN_BIAS - [5:3] */
#define WM8962_MIXIN_BIAS_SHIFT                      3  /* MIXIN_BIAS - [5:3] */
#define WM8962_MIXIN_BIAS_WIDTH                      3  /* MIXIN_BIAS - [5:3] */
#define WM8962_INPGA_BIAS_MASK                  0x0007  /* INPGA_BIAS - [2:0] */
#define WM8962_INPGA_BIAS_SHIFT                      0  /* INPGA_BIAS - [2:0] */
#define WM8962_INPGA_BIAS_WIDTH                      3  /* INPGA_BIAS - [2:0] */

/*
 * W37 (0x25) - Weft input PGA contwow
 */
#define WM8962_INPGAW_ENA                       0x0010  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_MASK                  0x0010  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_SHIFT                      4  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_WIDTH                      1  /* INPGAW_ENA */
#define WM8962_IN1W_TO_INPGAW                   0x0008  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_MASK              0x0008  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_SHIFT                  3  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_WIDTH                  1  /* IN1W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW                   0x0004  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_MASK              0x0004  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_SHIFT                  2  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_WIDTH                  1  /* IN2W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW                   0x0002  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_MASK              0x0002  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_SHIFT                  1  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_WIDTH                  1  /* IN3W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW                   0x0001  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_MASK              0x0001  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_SHIFT                  0  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_WIDTH                  1  /* IN4W_TO_INPGAW */

/*
 * W38 (0x26) - Wight input PGA contwow
 */
#define WM8962_INPGAW_ENA                       0x0010  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_MASK                  0x0010  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_SHIFT                      4  /* INPGAW_ENA */
#define WM8962_INPGAW_ENA_WIDTH                      1  /* INPGAW_ENA */
#define WM8962_IN1W_TO_INPGAW                   0x0008  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_MASK              0x0008  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_SHIFT                  3  /* IN1W_TO_INPGAW */
#define WM8962_IN1W_TO_INPGAW_WIDTH                  1  /* IN1W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW                   0x0004  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_MASK              0x0004  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_SHIFT                  2  /* IN2W_TO_INPGAW */
#define WM8962_IN2W_TO_INPGAW_WIDTH                  1  /* IN2W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW                   0x0002  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_MASK              0x0002  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_SHIFT                  1  /* IN3W_TO_INPGAW */
#define WM8962_IN3W_TO_INPGAW_WIDTH                  1  /* IN3W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW                   0x0001  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_MASK              0x0001  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_SHIFT                  0  /* IN4W_TO_INPGAW */
#define WM8962_IN4W_TO_INPGAW_WIDTH                  1  /* IN4W_TO_INPGAW */

/*
 * W40 (0x28) - SPKOUTW vowume
 */
#define WM8962_SPKOUT_VU                        0x0100  /* SPKOUT_VU */
#define WM8962_SPKOUT_VU_MASK                   0x0100  /* SPKOUT_VU */
#define WM8962_SPKOUT_VU_SHIFT                       8  /* SPKOUT_VU */
#define WM8962_SPKOUT_VU_WIDTH                       1  /* SPKOUT_VU */
#define WM8962_SPKOUTW_ZC                       0x0080  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_MASK                  0x0080  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_SHIFT                      7  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_WIDTH                      1  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_VOW_MASK                 0x007F  /* SPKOUTW_VOW - [6:0] */
#define WM8962_SPKOUTW_VOW_SHIFT                     0  /* SPKOUTW_VOW - [6:0] */
#define WM8962_SPKOUTW_VOW_WIDTH                     7  /* SPKOUTW_VOW - [6:0] */

/*
 * W41 (0x29) - SPKOUTW vowume
 */
#define WM8962_SPKOUTW_ZC                       0x0080  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_MASK                  0x0080  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_SHIFT                      7  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_ZC_WIDTH                      1  /* SPKOUTW_ZC */
#define WM8962_SPKOUTW_VOW_MASK                 0x007F  /* SPKOUTW_VOW - [6:0] */
#define WM8962_SPKOUTW_VOW_SHIFT                     0  /* SPKOUTW_VOW - [6:0] */
#define WM8962_SPKOUTW_VOW_WIDTH                     7  /* SPKOUTW_VOW - [6:0] */

/*
 * W47 (0x2F) - Thewmaw Shutdown Status
 */
#define WM8962_TEMP_EWW_HP                      0x0008  /* TEMP_EWW_HP */
#define WM8962_TEMP_EWW_HP_MASK                 0x0008  /* TEMP_EWW_HP */
#define WM8962_TEMP_EWW_HP_SHIFT                     3  /* TEMP_EWW_HP */
#define WM8962_TEMP_EWW_HP_WIDTH                     1  /* TEMP_EWW_HP */
#define WM8962_TEMP_WAWN_HP                     0x0004  /* TEMP_WAWN_HP */
#define WM8962_TEMP_WAWN_HP_MASK                0x0004  /* TEMP_WAWN_HP */
#define WM8962_TEMP_WAWN_HP_SHIFT                    2  /* TEMP_WAWN_HP */
#define WM8962_TEMP_WAWN_HP_WIDTH                    1  /* TEMP_WAWN_HP */
#define WM8962_TEMP_EWW_SPK                     0x0002  /* TEMP_EWW_SPK */
#define WM8962_TEMP_EWW_SPK_MASK                0x0002  /* TEMP_EWW_SPK */
#define WM8962_TEMP_EWW_SPK_SHIFT                    1  /* TEMP_EWW_SPK */
#define WM8962_TEMP_EWW_SPK_WIDTH                    1  /* TEMP_EWW_SPK */
#define WM8962_TEMP_WAWN_SPK                    0x0001  /* TEMP_WAWN_SPK */
#define WM8962_TEMP_WAWN_SPK_MASK               0x0001  /* TEMP_WAWN_SPK */
#define WM8962_TEMP_WAWN_SPK_SHIFT                   0  /* TEMP_WAWN_SPK */
#define WM8962_TEMP_WAWN_SPK_WIDTH                   1  /* TEMP_WAWN_SPK */

/*
 * W48 (0x30) - Additionaw Contwow (4)
 */
#define WM8962_MICDET_THW_MASK                  0x7000  /* MICDET_THW - [14:12] */
#define WM8962_MICDET_THW_SHIFT                     12  /* MICDET_THW - [14:12] */
#define WM8962_MICDET_THW_WIDTH                      3  /* MICDET_THW - [14:12] */
#define WM8962_MICSHOWT_THW_MASK                0x0C00  /* MICSHOWT_THW - [11:10] */
#define WM8962_MICSHOWT_THW_SHIFT                   10  /* MICSHOWT_THW - [11:10] */
#define WM8962_MICSHOWT_THW_WIDTH                    2  /* MICSHOWT_THW - [11:10] */
#define WM8962_MICDET_ENA                       0x0200  /* MICDET_ENA */
#define WM8962_MICDET_ENA_MASK                  0x0200  /* MICDET_ENA */
#define WM8962_MICDET_ENA_SHIFT                      9  /* MICDET_ENA */
#define WM8962_MICDET_ENA_WIDTH                      1  /* MICDET_ENA */
#define WM8962_MICDET_STS                       0x0080  /* MICDET_STS */
#define WM8962_MICDET_STS_MASK                  0x0080  /* MICDET_STS */
#define WM8962_MICDET_STS_SHIFT                      7  /* MICDET_STS */
#define WM8962_MICDET_STS_WIDTH                      1  /* MICDET_STS */
#define WM8962_MICSHOWT_STS                     0x0040  /* MICSHOWT_STS */
#define WM8962_MICSHOWT_STS_MASK                0x0040  /* MICSHOWT_STS */
#define WM8962_MICSHOWT_STS_SHIFT                    6  /* MICSHOWT_STS */
#define WM8962_MICSHOWT_STS_WIDTH                    1  /* MICSHOWT_STS */
#define WM8962_TEMP_ENA_HP                      0x0004  /* TEMP_ENA_HP */
#define WM8962_TEMP_ENA_HP_MASK                 0x0004  /* TEMP_ENA_HP */
#define WM8962_TEMP_ENA_HP_SHIFT                     2  /* TEMP_ENA_HP */
#define WM8962_TEMP_ENA_HP_WIDTH                     1  /* TEMP_ENA_HP */
#define WM8962_TEMP_ENA_SPK                     0x0002  /* TEMP_ENA_SPK */
#define WM8962_TEMP_ENA_SPK_MASK                0x0002  /* TEMP_ENA_SPK */
#define WM8962_TEMP_ENA_SPK_SHIFT                    1  /* TEMP_ENA_SPK */
#define WM8962_TEMP_ENA_SPK_WIDTH                    1  /* TEMP_ENA_SPK */
#define WM8962_MICBIAS_WVW                      0x0001  /* MICBIAS_WVW */
#define WM8962_MICBIAS_WVW_MASK                 0x0001  /* MICBIAS_WVW */
#define WM8962_MICBIAS_WVW_SHIFT                     0  /* MICBIAS_WVW */
#define WM8962_MICBIAS_WVW_WIDTH                     1  /* MICBIAS_WVW */

/*
 * W49 (0x31) - Cwass D Contwow 1
 */
#define WM8962_SPKOUTW_ENA                      0x0080  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_MASK                 0x0080  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_SHIFT                     7  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_WIDTH                     1  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA                      0x0040  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_MASK                 0x0040  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_SHIFT                     6  /* SPKOUTW_ENA */
#define WM8962_SPKOUTW_ENA_WIDTH                     1  /* SPKOUTW_ENA */
#define WM8962_DAC_MUTE_AWT                     0x0010  /* DAC_MUTE */
#define WM8962_DAC_MUTE_AWT_MASK                0x0010  /* DAC_MUTE */
#define WM8962_DAC_MUTE_AWT_SHIFT                    4  /* DAC_MUTE */
#define WM8962_DAC_MUTE_AWT_WIDTH                    1  /* DAC_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE                 0x0002  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_MASK            0x0002  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_SHIFT                1  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_WIDTH                1  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE                 0x0001  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_MASK            0x0001  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_SHIFT                0  /* SPKOUTW_PGA_MUTE */
#define WM8962_SPKOUTW_PGA_MUTE_WIDTH                1  /* SPKOUTW_PGA_MUTE */

/*
 * W51 (0x33) - Cwass D Contwow 2
 */
#define WM8962_SPK_MONO                         0x0040  /* SPK_MONO */
#define WM8962_SPK_MONO_MASK                    0x0040  /* SPK_MONO */
#define WM8962_SPK_MONO_SHIFT                        6  /* SPK_MONO */
#define WM8962_SPK_MONO_WIDTH                        1  /* SPK_MONO */
#define WM8962_CWASSD_VOW_MASK                  0x0007  /* CWASSD_VOW - [2:0] */
#define WM8962_CWASSD_VOW_SHIFT                      0  /* CWASSD_VOW - [2:0] */
#define WM8962_CWASSD_VOW_WIDTH                      3  /* CWASSD_VOW - [2:0] */

/*
 * W56 (0x38) - Cwocking 4
 */
#define WM8962_SYSCWK_WATE_MASK                 0x001E  /* SYSCWK_WATE - [4:1] */
#define WM8962_SYSCWK_WATE_SHIFT                     1  /* SYSCWK_WATE - [4:1] */
#define WM8962_SYSCWK_WATE_WIDTH                     4  /* SYSCWK_WATE - [4:1] */

/*
 * W57 (0x39) - DAC DSP Mixing (1)
 */
#define WM8962_DAC_MONOMIX                      0x0200  /* DAC_MONOMIX */
#define WM8962_DAC_MONOMIX_MASK                 0x0200  /* DAC_MONOMIX */
#define WM8962_DAC_MONOMIX_SHIFT                     9  /* DAC_MONOMIX */
#define WM8962_DAC_MONOMIX_WIDTH                     1  /* DAC_MONOMIX */
#define WM8962_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8962_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8962_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */

/*
 * W58 (0x3A) - DAC DSP Mixing (2)
 */
#define WM8962_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8962_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8962_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8962_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */

/*
 * W60 (0x3C) - DC Sewvo 0
 */
#define WM8962_INW_DCS_ENA                      0x0080  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_MASK                 0x0080  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_SHIFT                     7  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_WIDTH                     1  /* INW_DCS_ENA */
#define WM8962_INW_DCS_STAWTUP                  0x0040  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_MASK             0x0040  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_SHIFT                 6  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_WIDTH                 1  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_ENA                      0x0008  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_MASK                 0x0008  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_SHIFT                     3  /* INW_DCS_ENA */
#define WM8962_INW_DCS_ENA_WIDTH                     1  /* INW_DCS_ENA */
#define WM8962_INW_DCS_STAWTUP                  0x0004  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_MASK             0x0004  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_SHIFT                 2  /* INW_DCS_STAWTUP */
#define WM8962_INW_DCS_STAWTUP_WIDTH                 1  /* INW_DCS_STAWTUP */

/*
 * W61 (0x3D) - DC Sewvo 1
 */
#define WM8962_HP1W_DCS_ENA                     0x0080  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_MASK                0x0080  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_SHIFT                    7  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_WIDTH                    1  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_STAWTUP                 0x0040  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_MASK            0x0040  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_SHIFT                6  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_WIDTH                1  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_SYNC                    0x0010  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_MASK               0x0010  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_SHIFT                   4  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_WIDTH                   1  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_ENA                     0x0008  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_MASK                0x0008  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_SHIFT                    3  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_ENA_WIDTH                    1  /* HP1W_DCS_ENA */
#define WM8962_HP1W_DCS_STAWTUP                 0x0004  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_MASK            0x0004  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_SHIFT                2  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_STAWTUP_WIDTH                1  /* HP1W_DCS_STAWTUP */
#define WM8962_HP1W_DCS_SYNC                    0x0001  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_MASK               0x0001  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_SHIFT                   0  /* HP1W_DCS_SYNC */
#define WM8962_HP1W_DCS_SYNC_WIDTH                   1  /* HP1W_DCS_SYNC */

/*
 * W64 (0x40) - DC Sewvo 4
 */
#define WM8962_HP1_DCS_SYNC_STEPS_MASK          0x3F80  /* HP1_DCS_SYNC_STEPS - [13:7] */
#define WM8962_HP1_DCS_SYNC_STEPS_SHIFT              7  /* HP1_DCS_SYNC_STEPS - [13:7] */
#define WM8962_HP1_DCS_SYNC_STEPS_WIDTH              7  /* HP1_DCS_SYNC_STEPS - [13:7] */

/*
 * W66 (0x42) - DC Sewvo 6
 */
#define WM8962_DCS_STAWTUP_DONE_INW             0x0400  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_MASK        0x0400  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_SHIFT           10  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_WIDTH            1  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW             0x0200  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_MASK        0x0200  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_SHIFT            9  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_INW_WIDTH            1  /* DCS_STAWTUP_DONE_INW */
#define WM8962_DCS_STAWTUP_DONE_HP1W            0x0100  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_MASK       0x0100  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_SHIFT           8  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_WIDTH           1  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W            0x0080  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_MASK       0x0080  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_SHIFT           7  /* DCS_STAWTUP_DONE_HP1W */
#define WM8962_DCS_STAWTUP_DONE_HP1W_WIDTH           1  /* DCS_STAWTUP_DONE_HP1W */

/*
 * W68 (0x44) - Anawogue PGA Bias
 */
#define WM8962_HP_PGAS_BIAS_MASK                0x0007  /* HP_PGAS_BIAS - [2:0] */
#define WM8962_HP_PGAS_BIAS_SHIFT                    0  /* HP_PGAS_BIAS - [2:0] */
#define WM8962_HP_PGAS_BIAS_WIDTH                    3  /* HP_PGAS_BIAS - [2:0] */

/*
 * W69 (0x45) - Anawogue HP 0
 */
#define WM8962_HP1W_WMV_SHOWT                   0x0080  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_MASK              0x0080  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_SHIFT                  7  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_WIDTH                  1  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_ENA_OUTP                    0x0040  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_MASK               0x0040  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_SHIFT                   6  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_WIDTH                   1  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_DWY                     0x0020  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_MASK                0x0020  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_SHIFT                    5  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_WIDTH                    1  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA                         0x0010  /* HP1W_ENA */
#define WM8962_HP1W_ENA_MASK                    0x0010  /* HP1W_ENA */
#define WM8962_HP1W_ENA_SHIFT                        4  /* HP1W_ENA */
#define WM8962_HP1W_ENA_WIDTH                        1  /* HP1W_ENA */
#define WM8962_HP1W_WMV_SHOWT                   0x0008  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_MASK              0x0008  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_SHIFT                  3  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_WMV_SHOWT_WIDTH                  1  /* HP1W_WMV_SHOWT */
#define WM8962_HP1W_ENA_OUTP                    0x0004  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_MASK               0x0004  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_SHIFT                   2  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_OUTP_WIDTH                   1  /* HP1W_ENA_OUTP */
#define WM8962_HP1W_ENA_DWY                     0x0002  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_MASK                0x0002  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_SHIFT                    1  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA_DWY_WIDTH                    1  /* HP1W_ENA_DWY */
#define WM8962_HP1W_ENA                         0x0001  /* HP1W_ENA */
#define WM8962_HP1W_ENA_MASK                    0x0001  /* HP1W_ENA */
#define WM8962_HP1W_ENA_SHIFT                        0  /* HP1W_ENA */
#define WM8962_HP1W_ENA_WIDTH                        1  /* HP1W_ENA */

/*
 * W71 (0x47) - Anawogue HP 2
 */
#define WM8962_HP1W_VOW_MASK                    0x01C0  /* HP1W_VOW - [8:6] */
#define WM8962_HP1W_VOW_SHIFT                        6  /* HP1W_VOW - [8:6] */
#define WM8962_HP1W_VOW_WIDTH                        3  /* HP1W_VOW - [8:6] */
#define WM8962_HP1W_VOW_MASK                    0x0038  /* HP1W_VOW - [5:3] */
#define WM8962_HP1W_VOW_SHIFT                        3  /* HP1W_VOW - [5:3] */
#define WM8962_HP1W_VOW_WIDTH                        3  /* HP1W_VOW - [5:3] */
#define WM8962_HP_BIAS_BOOST_MASK               0x0007  /* HP_BIAS_BOOST - [2:0] */
#define WM8962_HP_BIAS_BOOST_SHIFT                   0  /* HP_BIAS_BOOST - [2:0] */
#define WM8962_HP_BIAS_BOOST_WIDTH                   3  /* HP_BIAS_BOOST - [2:0] */

/*
 * W72 (0x48) - Chawge Pump 1
 */
#define WM8962_CP_ENA                           0x0001  /* CP_ENA */
#define WM8962_CP_ENA_MASK                      0x0001  /* CP_ENA */
#define WM8962_CP_ENA_SHIFT                          0  /* CP_ENA */
#define WM8962_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W82 (0x52) - Chawge Pump B
 */
#define WM8962_CP_DYN_PWW                       0x0001  /* CP_DYN_PWW */
#define WM8962_CP_DYN_PWW_MASK                  0x0001  /* CP_DYN_PWW */
#define WM8962_CP_DYN_PWW_SHIFT                      0  /* CP_DYN_PWW */
#define WM8962_CP_DYN_PWW_WIDTH                      1  /* CP_DYN_PWW */

/*
 * W87 (0x57) - Wwite Sequencew Contwow 1
 */
#define WM8962_WSEQ_AUTOSEQ_ENA                 0x0080  /* WSEQ_AUTOSEQ_ENA */
#define WM8962_WSEQ_AUTOSEQ_ENA_MASK            0x0080  /* WSEQ_AUTOSEQ_ENA */
#define WM8962_WSEQ_AUTOSEQ_ENA_SHIFT                7  /* WSEQ_AUTOSEQ_ENA */
#define WM8962_WSEQ_AUTOSEQ_ENA_WIDTH                1  /* WSEQ_AUTOSEQ_ENA */
#define WM8962_WSEQ_ENA                         0x0020  /* WSEQ_ENA */
#define WM8962_WSEQ_ENA_MASK                    0x0020  /* WSEQ_ENA */
#define WM8962_WSEQ_ENA_SHIFT                        5  /* WSEQ_ENA */
#define WM8962_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */

/*
 * W90 (0x5A) - Wwite Sequencew Contwow 2
 */
#define WM8962_WSEQ_ABOWT                       0x0100  /* WSEQ_ABOWT */
#define WM8962_WSEQ_ABOWT_MASK                  0x0100  /* WSEQ_ABOWT */
#define WM8962_WSEQ_ABOWT_SHIFT                      8  /* WSEQ_ABOWT */
#define WM8962_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM8962_WSEQ_STAWT                       0x0080  /* WSEQ_STAWT */
#define WM8962_WSEQ_STAWT_MASK                  0x0080  /* WSEQ_STAWT */
#define WM8962_WSEQ_STAWT_SHIFT                      7  /* WSEQ_STAWT */
#define WM8962_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM8962_WSEQ_STAWT_INDEX_MASK            0x007F  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM8962_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM8962_WSEQ_STAWT_INDEX_WIDTH                7  /* WSEQ_STAWT_INDEX - [6:0] */

/*
 * W93 (0x5D) - Wwite Sequencew Contwow 3
 */
#define WM8962_WSEQ_CUWWENT_INDEX_MASK          0x03F8  /* WSEQ_CUWWENT_INDEX - [9:3] */
#define WM8962_WSEQ_CUWWENT_INDEX_SHIFT              3  /* WSEQ_CUWWENT_INDEX - [9:3] */
#define WM8962_WSEQ_CUWWENT_INDEX_WIDTH              7  /* WSEQ_CUWWENT_INDEX - [9:3] */
#define WM8962_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM8962_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM8962_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM8962_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W94 (0x5E) - Contwow Intewface
 */
#define WM8962_SPI_CONTWD                       0x0040  /* SPI_CONTWD */
#define WM8962_SPI_CONTWD_MASK                  0x0040  /* SPI_CONTWD */
#define WM8962_SPI_CONTWD_SHIFT                      6  /* SPI_CONTWD */
#define WM8962_SPI_CONTWD_WIDTH                      1  /* SPI_CONTWD */
#define WM8962_SPI_4WIWE                        0x0020  /* SPI_4WIWE */
#define WM8962_SPI_4WIWE_MASK                   0x0020  /* SPI_4WIWE */
#define WM8962_SPI_4WIWE_SHIFT                       5  /* SPI_4WIWE */
#define WM8962_SPI_4WIWE_WIDTH                       1  /* SPI_4WIWE */
#define WM8962_SPI_CFG                          0x0010  /* SPI_CFG */
#define WM8962_SPI_CFG_MASK                     0x0010  /* SPI_CFG */
#define WM8962_SPI_CFG_SHIFT                         4  /* SPI_CFG */
#define WM8962_SPI_CFG_WIDTH                         1  /* SPI_CFG */

/*
 * W99 (0x63) - Mixew Enabwes
 */
#define WM8962_HPMIXW_ENA                       0x0008  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_MASK                  0x0008  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_SHIFT                      3  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_WIDTH                      1  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA                       0x0004  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_MASK                  0x0004  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_SHIFT                      2  /* HPMIXW_ENA */
#define WM8962_HPMIXW_ENA_WIDTH                      1  /* HPMIXW_ENA */
#define WM8962_SPKMIXW_ENA                      0x0002  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_MASK                 0x0002  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_SHIFT                     1  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_WIDTH                     1  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA                      0x0001  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_MASK                 0x0001  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_SHIFT                     0  /* SPKMIXW_ENA */
#define WM8962_SPKMIXW_ENA_WIDTH                     1  /* SPKMIXW_ENA */

/*
 * W100 (0x64) - Headphone Mixew (1)
 */
#define WM8962_HPMIXW_TO_HPOUTW_PGA             0x0080  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_MASK        0x0080  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_SHIFT            7  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_WIDTH            1  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_DACW_TO_HPMIXW                   0x0020  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_MASK              0x0020  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_SHIFT                  5  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_WIDTH                  1  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW                   0x0010  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_MASK              0x0010  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_SHIFT                  4  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_WIDTH                  1  /* DACW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW                 0x0008  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_MASK            0x0008  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_SHIFT                3  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_WIDTH                1  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW                 0x0004  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_MASK            0x0004  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_SHIFT                2  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_WIDTH                1  /* MIXINW_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW                   0x0002  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_MASK              0x0002  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_SHIFT                  1  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_WIDTH                  1  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW                   0x0001  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_MASK              0x0001  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_SHIFT                  0  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_WIDTH                  1  /* IN4W_TO_HPMIXW */

/*
 * W101 (0x65) - Headphone Mixew (2)
 */
#define WM8962_HPMIXW_TO_HPOUTW_PGA             0x0080  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_MASK        0x0080  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_SHIFT            7  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_HPMIXW_TO_HPOUTW_PGA_WIDTH            1  /* HPMIXW_TO_HPOUTW_PGA */
#define WM8962_DACW_TO_HPMIXW                   0x0020  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_MASK              0x0020  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_SHIFT                  5  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_WIDTH                  1  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW                   0x0010  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_MASK              0x0010  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_SHIFT                  4  /* DACW_TO_HPMIXW */
#define WM8962_DACW_TO_HPMIXW_WIDTH                  1  /* DACW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW                 0x0008  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_MASK            0x0008  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_SHIFT                3  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_WIDTH                1  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW                 0x0004  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_MASK            0x0004  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_SHIFT                2  /* MIXINW_TO_HPMIXW */
#define WM8962_MIXINW_TO_HPMIXW_WIDTH                1  /* MIXINW_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW                   0x0002  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_MASK              0x0002  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_SHIFT                  1  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_WIDTH                  1  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW                   0x0001  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_MASK              0x0001  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_SHIFT                  0  /* IN4W_TO_HPMIXW */
#define WM8962_IN4W_TO_HPMIXW_WIDTH                  1  /* IN4W_TO_HPMIXW */

/*
 * W102 (0x66) - Headphone Mixew (3)
 */
#define WM8962_HPMIXW_MUTE                      0x0100  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_MASK                 0x0100  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_SHIFT                     8  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_WIDTH                     1  /* HPMIXW_MUTE */
#define WM8962_MIXINW_HPMIXW_VOW                0x0080  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_MASK           0x0080  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_SHIFT               7  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_WIDTH               1  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW                0x0040  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_MASK           0x0040  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_SHIFT               6  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_WIDTH               1  /* MIXINW_HPMIXW_VOW */
#define WM8962_IN4W_HPMIXW_VOW_MASK             0x0038  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_SHIFT                 3  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_WIDTH                 3  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_MASK             0x0007  /* IN4W_HPMIXW_VOW - [2:0] */
#define WM8962_IN4W_HPMIXW_VOW_SHIFT                 0  /* IN4W_HPMIXW_VOW - [2:0] */
#define WM8962_IN4W_HPMIXW_VOW_WIDTH                 3  /* IN4W_HPMIXW_VOW - [2:0] */

/*
 * W103 (0x67) - Headphone Mixew (4)
 */
#define WM8962_HPMIXW_MUTE                      0x0100  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_MASK                 0x0100  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_SHIFT                     8  /* HPMIXW_MUTE */
#define WM8962_HPMIXW_MUTE_WIDTH                     1  /* HPMIXW_MUTE */
#define WM8962_MIXINW_HPMIXW_VOW                0x0080  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_MASK           0x0080  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_SHIFT               7  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_WIDTH               1  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW                0x0040  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_MASK           0x0040  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_SHIFT               6  /* MIXINW_HPMIXW_VOW */
#define WM8962_MIXINW_HPMIXW_VOW_WIDTH               1  /* MIXINW_HPMIXW_VOW */
#define WM8962_IN4W_HPMIXW_VOW_MASK             0x0038  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_SHIFT                 3  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_WIDTH                 3  /* IN4W_HPMIXW_VOW - [5:3] */
#define WM8962_IN4W_HPMIXW_VOW_MASK             0x0007  /* IN4W_HPMIXW_VOW - [2:0] */
#define WM8962_IN4W_HPMIXW_VOW_SHIFT                 0  /* IN4W_HPMIXW_VOW - [2:0] */
#define WM8962_IN4W_HPMIXW_VOW_WIDTH                 3  /* IN4W_HPMIXW_VOW - [2:0] */

/*
 * W105 (0x69) - Speakew Mixew (1)
 */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA           0x0080  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_MASK      0x0080  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_SHIFT          7  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_WIDTH          1  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_DACW_TO_SPKMIXW                  0x0020  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_MASK             0x0020  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_SHIFT                 5  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_WIDTH                 1  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW                  0x0010  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_MASK             0x0010  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_SHIFT                 4  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_WIDTH                 1  /* DACW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW                0x0008  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_MASK           0x0008  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_SHIFT               3  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_WIDTH               1  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW                0x0004  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_MASK           0x0004  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_SHIFT               2  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_WIDTH               1  /* MIXINW_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW                  0x0002  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_MASK             0x0002  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_SHIFT                 1  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_WIDTH                 1  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW                  0x0001  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_MASK             0x0001  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_SHIFT                 0  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_WIDTH                 1  /* IN4W_TO_SPKMIXW */

/*
 * W106 (0x6A) - Speakew Mixew (2)
 */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA           0x0080  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_MASK      0x0080  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_SHIFT          7  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_SPKMIXW_TO_SPKOUTW_PGA_WIDTH          1  /* SPKMIXW_TO_SPKOUTW_PGA */
#define WM8962_DACW_TO_SPKMIXW                  0x0020  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_MASK             0x0020  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_SHIFT                 5  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_WIDTH                 1  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW                  0x0010  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_MASK             0x0010  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_SHIFT                 4  /* DACW_TO_SPKMIXW */
#define WM8962_DACW_TO_SPKMIXW_WIDTH                 1  /* DACW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW                0x0008  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_MASK           0x0008  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_SHIFT               3  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_WIDTH               1  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW                0x0004  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_MASK           0x0004  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_SHIFT               2  /* MIXINW_TO_SPKMIXW */
#define WM8962_MIXINW_TO_SPKMIXW_WIDTH               1  /* MIXINW_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW                  0x0002  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_MASK             0x0002  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_SHIFT                 1  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_WIDTH                 1  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW                  0x0001  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_MASK             0x0001  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_SHIFT                 0  /* IN4W_TO_SPKMIXW */
#define WM8962_IN4W_TO_SPKMIXW_WIDTH                 1  /* IN4W_TO_SPKMIXW */

/*
 * W107 (0x6B) - Speakew Mixew (3)
 */
#define WM8962_SPKMIXW_MUTE                     0x0100  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_MASK                0x0100  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_SHIFT                    8  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_WIDTH                    1  /* SPKMIXW_MUTE */
#define WM8962_MIXINW_SPKMIXW_VOW               0x0080  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_MASK          0x0080  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_SHIFT              7  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_WIDTH              1  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW               0x0040  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_MASK          0x0040  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_SHIFT              6  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_WIDTH              1  /* MIXINW_SPKMIXW_VOW */
#define WM8962_IN4W_SPKMIXW_VOW_MASK            0x0038  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_SHIFT                3  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_WIDTH                3  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_MASK            0x0007  /* IN4W_SPKMIXW_VOW - [2:0] */
#define WM8962_IN4W_SPKMIXW_VOW_SHIFT                0  /* IN4W_SPKMIXW_VOW - [2:0] */
#define WM8962_IN4W_SPKMIXW_VOW_WIDTH                3  /* IN4W_SPKMIXW_VOW - [2:0] */

/*
 * W108 (0x6C) - Speakew Mixew (4)
 */
#define WM8962_SPKMIXW_MUTE                     0x0100  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_MASK                0x0100  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_SHIFT                    8  /* SPKMIXW_MUTE */
#define WM8962_SPKMIXW_MUTE_WIDTH                    1  /* SPKMIXW_MUTE */
#define WM8962_MIXINW_SPKMIXW_VOW               0x0080  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_MASK          0x0080  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_SHIFT              7  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_WIDTH              1  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW               0x0040  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_MASK          0x0040  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_SHIFT              6  /* MIXINW_SPKMIXW_VOW */
#define WM8962_MIXINW_SPKMIXW_VOW_WIDTH              1  /* MIXINW_SPKMIXW_VOW */
#define WM8962_IN4W_SPKMIXW_VOW_MASK            0x0038  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_SHIFT                3  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_WIDTH                3  /* IN4W_SPKMIXW_VOW - [5:3] */
#define WM8962_IN4W_SPKMIXW_VOW_MASK            0x0007  /* IN4W_SPKMIXW_VOW - [2:0] */
#define WM8962_IN4W_SPKMIXW_VOW_SHIFT                0  /* IN4W_SPKMIXW_VOW - [2:0] */
#define WM8962_IN4W_SPKMIXW_VOW_WIDTH                3  /* IN4W_SPKMIXW_VOW - [2:0] */

/*
 * W109 (0x6D) - Speakew Mixew (5)
 */
#define WM8962_DACW_SPKMIXW_VOW                 0x0080  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_MASK            0x0080  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_SHIFT                7  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_WIDTH                1  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW                 0x0040  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_MASK            0x0040  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_SHIFT                6  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_WIDTH                1  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW                 0x0020  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_MASK            0x0020  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_SHIFT                5  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_WIDTH                1  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW                 0x0010  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_MASK            0x0010  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_SHIFT                4  /* DACW_SPKMIXW_VOW */
#define WM8962_DACW_SPKMIXW_VOW_WIDTH                1  /* DACW_SPKMIXW_VOW */

/*
 * W110 (0x6E) - Beep Genewatow (1)
 */
#define WM8962_BEEP_GAIN_MASK                   0x00F0  /* BEEP_GAIN - [7:4] */
#define WM8962_BEEP_GAIN_SHIFT                       4  /* BEEP_GAIN - [7:4] */
#define WM8962_BEEP_GAIN_WIDTH                       4  /* BEEP_GAIN - [7:4] */
#define WM8962_BEEP_WATE_MASK                   0x0006  /* BEEP_WATE - [2:1] */
#define WM8962_BEEP_WATE_SHIFT                       1  /* BEEP_WATE - [2:1] */
#define WM8962_BEEP_WATE_WIDTH                       2  /* BEEP_WATE - [2:1] */
#define WM8962_BEEP_ENA                         0x0001  /* BEEP_ENA */
#define WM8962_BEEP_ENA_MASK                    0x0001  /* BEEP_ENA */
#define WM8962_BEEP_ENA_SHIFT                        0  /* BEEP_ENA */
#define WM8962_BEEP_ENA_WIDTH                        1  /* BEEP_ENA */

/*
 * W115 (0x73) - Osciwwatow Twim (3)
 */
#define WM8962_OSC_TWIM_XTI_MASK                0x001F  /* OSC_TWIM_XTI - [4:0] */
#define WM8962_OSC_TWIM_XTI_SHIFT                    0  /* OSC_TWIM_XTI - [4:0] */
#define WM8962_OSC_TWIM_XTI_WIDTH                    5  /* OSC_TWIM_XTI - [4:0] */

/*
 * W116 (0x74) - Osciwwatow Twim (4)
 */
#define WM8962_OSC_TWIM_XTO_MASK                0x001F  /* OSC_TWIM_XTO - [4:0] */
#define WM8962_OSC_TWIM_XTO_SHIFT                    0  /* OSC_TWIM_XTO - [4:0] */
#define WM8962_OSC_TWIM_XTO_WIDTH                    5  /* OSC_TWIM_XTO - [4:0] */

/*
 * W119 (0x77) - Osciwwatow Twim (7)
 */
#define WM8962_XTO_CAP_SEW_MASK                 0x00F0  /* XTO_CAP_SEW - [7:4] */
#define WM8962_XTO_CAP_SEW_SHIFT                     4  /* XTO_CAP_SEW - [7:4] */
#define WM8962_XTO_CAP_SEW_WIDTH                     4  /* XTO_CAP_SEW - [7:4] */
#define WM8962_XTI_CAP_SEW_MASK                 0x000F  /* XTI_CAP_SEW - [3:0] */
#define WM8962_XTI_CAP_SEW_SHIFT                     0  /* XTI_CAP_SEW - [3:0] */
#define WM8962_XTI_CAP_SEW_WIDTH                     4  /* XTI_CAP_SEW - [3:0] */

/*
 * W124 (0x7C) - Anawogue Cwocking1
 */
#define WM8962_CWKOUT2_SEW_MASK                 0x0060  /* CWKOUT2_SEW - [6:5] */
#define WM8962_CWKOUT2_SEW_SHIFT                     5  /* CWKOUT2_SEW - [6:5] */
#define WM8962_CWKOUT2_SEW_WIDTH                     2  /* CWKOUT2_SEW - [6:5] */
#define WM8962_CWKOUT3_SEW_MASK                 0x0018  /* CWKOUT3_SEW - [4:3] */
#define WM8962_CWKOUT3_SEW_SHIFT                     3  /* CWKOUT3_SEW - [4:3] */
#define WM8962_CWKOUT3_SEW_WIDTH                     2  /* CWKOUT3_SEW - [4:3] */
#define WM8962_CWKOUT5_SEW                      0x0001  /* CWKOUT5_SEW */
#define WM8962_CWKOUT5_SEW_MASK                 0x0001  /* CWKOUT5_SEW */
#define WM8962_CWKOUT5_SEW_SHIFT                     0  /* CWKOUT5_SEW */
#define WM8962_CWKOUT5_SEW_WIDTH                     1  /* CWKOUT5_SEW */

/*
 * W125 (0x7D) - Anawogue Cwocking2
 */
#define WM8962_PWW2_OUTDIV                      0x0080  /* PWW2_OUTDIV */
#define WM8962_PWW2_OUTDIV_MASK                 0x0080  /* PWW2_OUTDIV */
#define WM8962_PWW2_OUTDIV_SHIFT                     7  /* PWW2_OUTDIV */
#define WM8962_PWW2_OUTDIV_WIDTH                     1  /* PWW2_OUTDIV */
#define WM8962_PWW3_OUTDIV                      0x0040  /* PWW3_OUTDIV */
#define WM8962_PWW3_OUTDIV_MASK                 0x0040  /* PWW3_OUTDIV */
#define WM8962_PWW3_OUTDIV_SHIFT                     6  /* PWW3_OUTDIV */
#define WM8962_PWW3_OUTDIV_WIDTH                     1  /* PWW3_OUTDIV */
#define WM8962_PWW_SYSCWK_DIV_MASK              0x0018  /* PWW_SYSCWK_DIV - [4:3] */
#define WM8962_PWW_SYSCWK_DIV_SHIFT                  3  /* PWW_SYSCWK_DIV - [4:3] */
#define WM8962_PWW_SYSCWK_DIV_WIDTH                  2  /* PWW_SYSCWK_DIV - [4:3] */
#define WM8962_CWKOUT3_DIV                      0x0004  /* CWKOUT3_DIV */
#define WM8962_CWKOUT3_DIV_MASK                 0x0004  /* CWKOUT3_DIV */
#define WM8962_CWKOUT3_DIV_SHIFT                     2  /* CWKOUT3_DIV */
#define WM8962_CWKOUT3_DIV_WIDTH                     1  /* CWKOUT3_DIV */
#define WM8962_CWKOUT2_DIV                      0x0002  /* CWKOUT2_DIV */
#define WM8962_CWKOUT2_DIV_MASK                 0x0002  /* CWKOUT2_DIV */
#define WM8962_CWKOUT2_DIV_SHIFT                     1  /* CWKOUT2_DIV */
#define WM8962_CWKOUT2_DIV_WIDTH                     1  /* CWKOUT2_DIV */
#define WM8962_CWKOUT5_DIV                      0x0001  /* CWKOUT5_DIV */
#define WM8962_CWKOUT5_DIV_MASK                 0x0001  /* CWKOUT5_DIV */
#define WM8962_CWKOUT5_DIV_SHIFT                     0  /* CWKOUT5_DIV */
#define WM8962_CWKOUT5_DIV_WIDTH                     1  /* CWKOUT5_DIV */

/*
 * W126 (0x7E) - Anawogue Cwocking3
 */
#define WM8962_CWKOUT2_OE                       0x0008  /* CWKOUT2_OE */
#define WM8962_CWKOUT2_OE_MASK                  0x0008  /* CWKOUT2_OE */
#define WM8962_CWKOUT2_OE_SHIFT                      3  /* CWKOUT2_OE */
#define WM8962_CWKOUT2_OE_WIDTH                      1  /* CWKOUT2_OE */
#define WM8962_CWKOUT3_OE                       0x0004  /* CWKOUT3_OE */
#define WM8962_CWKOUT3_OE_MASK                  0x0004  /* CWKOUT3_OE */
#define WM8962_CWKOUT3_OE_SHIFT                      2  /* CWKOUT3_OE */
#define WM8962_CWKOUT3_OE_WIDTH                      1  /* CWKOUT3_OE */
#define WM8962_CWKOUT5_OE                       0x0001  /* CWKOUT5_OE */
#define WM8962_CWKOUT5_OE_MASK                  0x0001  /* CWKOUT5_OE */
#define WM8962_CWKOUT5_OE_SHIFT                      0  /* CWKOUT5_OE */
#define WM8962_CWKOUT5_OE_WIDTH                      1  /* CWKOUT5_OE */

/*
 * W127 (0x7F) - PWW Softwawe Weset
 */
#define WM8962_SW_WESET_PWW_MASK                0xFFFF  /* SW_WESET_PWW - [15:0] */
#define WM8962_SW_WESET_PWW_SHIFT                    0  /* SW_WESET_PWW - [15:0] */
#define WM8962_SW_WESET_PWW_WIDTH                   16  /* SW_WESET_PWW - [15:0] */

/*
 * W129 (0x81) - PWW2
 */
#define WM8962_OSC_ENA                          0x0080  /* OSC_ENA */
#define WM8962_OSC_ENA_MASK                     0x0080  /* OSC_ENA */
#define WM8962_OSC_ENA_SHIFT                         7  /* OSC_ENA */
#define WM8962_OSC_ENA_WIDTH                         1  /* OSC_ENA */
#define WM8962_PWW2_ENA                         0x0020  /* PWW2_ENA */
#define WM8962_PWW2_ENA_MASK                    0x0020  /* PWW2_ENA */
#define WM8962_PWW2_ENA_SHIFT                        5  /* PWW2_ENA */
#define WM8962_PWW2_ENA_WIDTH                        1  /* PWW2_ENA */
#define WM8962_PWW3_ENA                         0x0010  /* PWW3_ENA */
#define WM8962_PWW3_ENA_MASK                    0x0010  /* PWW3_ENA */
#define WM8962_PWW3_ENA_SHIFT                        4  /* PWW3_ENA */
#define WM8962_PWW3_ENA_WIDTH                        1  /* PWW3_ENA */

/*
 * W131 (0x83) - PWW 4
 */
#define WM8962_PWW_CWK_SWC                      0x0002  /* PWW_CWK_SWC */
#define WM8962_PWW_CWK_SWC_MASK                 0x0002  /* PWW_CWK_SWC */
#define WM8962_PWW_CWK_SWC_SHIFT                     1  /* PWW_CWK_SWC */
#define WM8962_PWW_CWK_SWC_WIDTH                     1  /* PWW_CWK_SWC */
#define WM8962_FWW_TO_PWW3                      0x0001  /* FWW_TO_PWW3 */
#define WM8962_FWW_TO_PWW3_MASK                 0x0001  /* FWW_TO_PWW3 */
#define WM8962_FWW_TO_PWW3_SHIFT                     0  /* FWW_TO_PWW3 */
#define WM8962_FWW_TO_PWW3_WIDTH                     1  /* FWW_TO_PWW3 */

/*
 * W136 (0x88) - PWW 9
 */
#define WM8962_PWW2_FWAC                        0x0040  /* PWW2_FWAC */
#define WM8962_PWW2_FWAC_MASK                   0x0040  /* PWW2_FWAC */
#define WM8962_PWW2_FWAC_SHIFT                       6  /* PWW2_FWAC */
#define WM8962_PWW2_FWAC_WIDTH                       1  /* PWW2_FWAC */
#define WM8962_PWW2_N_MASK                      0x001F  /* PWW2_N - [4:0] */
#define WM8962_PWW2_N_SHIFT                          0  /* PWW2_N - [4:0] */
#define WM8962_PWW2_N_WIDTH                          5  /* PWW2_N - [4:0] */

/*
 * W137 (0x89) - PWW 10
 */
#define WM8962_PWW2_K_MASK                      0x00FF  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_SHIFT                          0  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_WIDTH                          8  /* PWW2_K - [7:0] */

/*
 * W138 (0x8A) - PWW 11
 */
#define WM8962_PWW2_K_MASK                      0x00FF  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_SHIFT                          0  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_WIDTH                          8  /* PWW2_K - [7:0] */

/*
 * W139 (0x8B) - PWW 12
 */
#define WM8962_PWW2_K_MASK                      0x00FF  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_SHIFT                          0  /* PWW2_K - [7:0] */
#define WM8962_PWW2_K_WIDTH                          8  /* PWW2_K - [7:0] */

/*
 * W140 (0x8C) - PWW 13
 */
#define WM8962_PWW3_FWAC                        0x0040  /* PWW3_FWAC */
#define WM8962_PWW3_FWAC_MASK                   0x0040  /* PWW3_FWAC */
#define WM8962_PWW3_FWAC_SHIFT                       6  /* PWW3_FWAC */
#define WM8962_PWW3_FWAC_WIDTH                       1  /* PWW3_FWAC */
#define WM8962_PWW3_N_MASK                      0x001F  /* PWW3_N - [4:0] */
#define WM8962_PWW3_N_SHIFT                          0  /* PWW3_N - [4:0] */
#define WM8962_PWW3_N_WIDTH                          5  /* PWW3_N - [4:0] */

/*
 * W141 (0x8D) - PWW 14
 */
#define WM8962_PWW3_K_MASK                      0x00FF  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_SHIFT                          0  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_WIDTH                          8  /* PWW3_K - [7:0] */

/*
 * W142 (0x8E) - PWW 15
 */
#define WM8962_PWW3_K_MASK                      0x00FF  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_SHIFT                          0  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_WIDTH                          8  /* PWW3_K - [7:0] */

/*
 * W143 (0x8F) - PWW 16
 */
#define WM8962_PWW3_K_MASK                      0x00FF  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_SHIFT                          0  /* PWW3_K - [7:0] */
#define WM8962_PWW3_K_WIDTH                          8  /* PWW3_K - [7:0] */

/*
 * W155 (0x9B) - FWW Contwow (1)
 */
#define WM8962_FWW_WEFCWK_SWC_MASK              0x0060  /* FWW_WEFCWK_SWC - [6:5] */
#define WM8962_FWW_WEFCWK_SWC_SHIFT                  5  /* FWW_WEFCWK_SWC - [6:5] */
#define WM8962_FWW_WEFCWK_SWC_WIDTH                  2  /* FWW_WEFCWK_SWC - [6:5] */
#define WM8962_FWW_FWAC                         0x0004  /* FWW_FWAC */
#define WM8962_FWW_FWAC_MASK                    0x0004  /* FWW_FWAC */
#define WM8962_FWW_FWAC_SHIFT                        2  /* FWW_FWAC */
#define WM8962_FWW_FWAC_WIDTH                        1  /* FWW_FWAC */
#define WM8962_FWW_OSC_ENA                      0x0002  /* FWW_OSC_ENA */
#define WM8962_FWW_OSC_ENA_MASK                 0x0002  /* FWW_OSC_ENA */
#define WM8962_FWW_OSC_ENA_SHIFT                     1  /* FWW_OSC_ENA */
#define WM8962_FWW_OSC_ENA_WIDTH                     1  /* FWW_OSC_ENA */
#define WM8962_FWW_ENA                          0x0001  /* FWW_ENA */
#define WM8962_FWW_ENA_MASK                     0x0001  /* FWW_ENA */
#define WM8962_FWW_ENA_SHIFT                         0  /* FWW_ENA */
#define WM8962_FWW_ENA_WIDTH                         1  /* FWW_ENA */

/*
 * W156 (0x9C) - FWW Contwow (2)
 */
#define WM8962_FWW_OUTDIV_MASK                  0x01F8  /* FWW_OUTDIV - [8:3] */
#define WM8962_FWW_OUTDIV_SHIFT                      3  /* FWW_OUTDIV - [8:3] */
#define WM8962_FWW_OUTDIV_WIDTH                      6  /* FWW_OUTDIV - [8:3] */
#define WM8962_FWW_WEFCWK_DIV_MASK              0x0003  /* FWW_WEFCWK_DIV - [1:0] */
#define WM8962_FWW_WEFCWK_DIV_SHIFT                  0  /* FWW_WEFCWK_DIV - [1:0] */
#define WM8962_FWW_WEFCWK_DIV_WIDTH                  2  /* FWW_WEFCWK_DIV - [1:0] */

/*
 * W157 (0x9D) - FWW Contwow (3)
 */
#define WM8962_FWW_FWATIO_MASK                  0x0007  /* FWW_FWATIO - [2:0] */
#define WM8962_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [2:0] */
#define WM8962_FWW_FWATIO_WIDTH                      3  /* FWW_FWATIO - [2:0] */

/*
 * W159 (0x9F) - FWW Contwow (5)
 */
#define WM8962_FWW_FWC_NCO_VAW_MASK             0x007E  /* FWW_FWC_NCO_VAW - [6:1] */
#define WM8962_FWW_FWC_NCO_VAW_SHIFT                 1  /* FWW_FWC_NCO_VAW - [6:1] */
#define WM8962_FWW_FWC_NCO_VAW_WIDTH                 6  /* FWW_FWC_NCO_VAW - [6:1] */
#define WM8962_FWW_FWC_NCO                      0x0001  /* FWW_FWC_NCO */
#define WM8962_FWW_FWC_NCO_MASK                 0x0001  /* FWW_FWC_NCO */
#define WM8962_FWW_FWC_NCO_SHIFT                     0  /* FWW_FWC_NCO */
#define WM8962_FWW_FWC_NCO_WIDTH                     1  /* FWW_FWC_NCO */

/*
 * W160 (0xA0) - FWW Contwow (6)
 */
#define WM8962_FWW_THETA_MASK                   0xFFFF  /* FWW_THETA - [15:0] */
#define WM8962_FWW_THETA_SHIFT                       0  /* FWW_THETA - [15:0] */
#define WM8962_FWW_THETA_WIDTH                      16  /* FWW_THETA - [15:0] */

/*
 * W161 (0xA1) - FWW Contwow (7)
 */
#define WM8962_FWW_WAMBDA_MASK                  0xFFFF  /* FWW_WAMBDA - [15:0] */
#define WM8962_FWW_WAMBDA_SHIFT                      0  /* FWW_WAMBDA - [15:0] */
#define WM8962_FWW_WAMBDA_WIDTH                     16  /* FWW_WAMBDA - [15:0] */

/*
 * W162 (0xA2) - FWW Contwow (8)
 */
#define WM8962_FWW_N_MASK                       0x03FF  /* FWW_N - [9:0] */
#define WM8962_FWW_N_SHIFT                           0  /* FWW_N - [9:0] */
#define WM8962_FWW_N_WIDTH                          10  /* FWW_N - [9:0] */

/*
 * W252 (0xFC) - Genewaw test 1
 */
#define WM8962_WEG_SYNC                         0x0004  /* WEG_SYNC */
#define WM8962_WEG_SYNC_MASK                    0x0004  /* WEG_SYNC */
#define WM8962_WEG_SYNC_SHIFT                        2  /* WEG_SYNC */
#define WM8962_WEG_SYNC_WIDTH                        1  /* WEG_SYNC */
#define WM8962_AUTO_INC                         0x0001  /* AUTO_INC */
#define WM8962_AUTO_INC_MASK                    0x0001  /* AUTO_INC */
#define WM8962_AUTO_INC_SHIFT                        0  /* AUTO_INC */
#define WM8962_AUTO_INC_WIDTH                        1  /* AUTO_INC */

/*
 * W256 (0x100) - DF1
 */
#define WM8962_DWC_DF1_ENA                      0x0008  /* DWC_DF1_ENA */
#define WM8962_DWC_DF1_ENA_MASK                 0x0008  /* DWC_DF1_ENA */
#define WM8962_DWC_DF1_ENA_SHIFT                     3  /* DWC_DF1_ENA */
#define WM8962_DWC_DF1_ENA_WIDTH                     1  /* DWC_DF1_ENA */
#define WM8962_DF1_SHAWED_COEFF                 0x0004  /* DF1_SHAWED_COEFF */
#define WM8962_DF1_SHAWED_COEFF_MASK            0x0004  /* DF1_SHAWED_COEFF */
#define WM8962_DF1_SHAWED_COEFF_SHIFT                2  /* DF1_SHAWED_COEFF */
#define WM8962_DF1_SHAWED_COEFF_WIDTH                1  /* DF1_SHAWED_COEFF */
#define WM8962_DF1_SHAWED_COEFF_SEW             0x0002  /* DF1_SHAWED_COEFF_SEW */
#define WM8962_DF1_SHAWED_COEFF_SEW_MASK        0x0002  /* DF1_SHAWED_COEFF_SEW */
#define WM8962_DF1_SHAWED_COEFF_SEW_SHIFT            1  /* DF1_SHAWED_COEFF_SEW */
#define WM8962_DF1_SHAWED_COEFF_SEW_WIDTH            1  /* DF1_SHAWED_COEFF_SEW */
#define WM8962_DF1_ENA                          0x0001  /* DF1_ENA */
#define WM8962_DF1_ENA_MASK                     0x0001  /* DF1_ENA */
#define WM8962_DF1_ENA_SHIFT                         0  /* DF1_ENA */
#define WM8962_DF1_ENA_WIDTH                         1  /* DF1_ENA */

/*
 * W257 (0x101) - DF2
 */
#define WM8962_DF1_COEFF_W0_MASK                0xFFFF  /* DF1_COEFF_W0 - [15:0] */
#define WM8962_DF1_COEFF_W0_SHIFT                    0  /* DF1_COEFF_W0 - [15:0] */
#define WM8962_DF1_COEFF_W0_WIDTH                   16  /* DF1_COEFF_W0 - [15:0] */

/*
 * W258 (0x102) - DF3
 */
#define WM8962_DF1_COEFF_W1_MASK                0xFFFF  /* DF1_COEFF_W1 - [15:0] */
#define WM8962_DF1_COEFF_W1_SHIFT                    0  /* DF1_COEFF_W1 - [15:0] */
#define WM8962_DF1_COEFF_W1_WIDTH                   16  /* DF1_COEFF_W1 - [15:0] */

/*
 * W259 (0x103) - DF4
 */
#define WM8962_DF1_COEFF_W2_MASK                0xFFFF  /* DF1_COEFF_W2 - [15:0] */
#define WM8962_DF1_COEFF_W2_SHIFT                    0  /* DF1_COEFF_W2 - [15:0] */
#define WM8962_DF1_COEFF_W2_WIDTH                   16  /* DF1_COEFF_W2 - [15:0] */

/*
 * W260 (0x104) - DF5
 */
#define WM8962_DF1_COEFF_W0_MASK                0xFFFF  /* DF1_COEFF_W0 - [15:0] */
#define WM8962_DF1_COEFF_W0_SHIFT                    0  /* DF1_COEFF_W0 - [15:0] */
#define WM8962_DF1_COEFF_W0_WIDTH                   16  /* DF1_COEFF_W0 - [15:0] */

/*
 * W261 (0x105) - DF6
 */
#define WM8962_DF1_COEFF_W1_MASK                0xFFFF  /* DF1_COEFF_W1 - [15:0] */
#define WM8962_DF1_COEFF_W1_SHIFT                    0  /* DF1_COEFF_W1 - [15:0] */
#define WM8962_DF1_COEFF_W1_WIDTH                   16  /* DF1_COEFF_W1 - [15:0] */

/*
 * W262 (0x106) - DF7
 */
#define WM8962_DF1_COEFF_W2_MASK                0xFFFF  /* DF1_COEFF_W2 - [15:0] */
#define WM8962_DF1_COEFF_W2_SHIFT                    0  /* DF1_COEFF_W2 - [15:0] */
#define WM8962_DF1_COEFF_W2_WIDTH                   16  /* DF1_COEFF_W2 - [15:0] */

/*
 * W264 (0x108) - WHPF1
 */
#define WM8962_WHPF_MODE                        0x0002  /* WHPF_MODE */
#define WM8962_WHPF_MODE_MASK                   0x0002  /* WHPF_MODE */
#define WM8962_WHPF_MODE_SHIFT                       1  /* WHPF_MODE */
#define WM8962_WHPF_MODE_WIDTH                       1  /* WHPF_MODE */
#define WM8962_WHPF_ENA                         0x0001  /* WHPF_ENA */
#define WM8962_WHPF_ENA_MASK                    0x0001  /* WHPF_ENA */
#define WM8962_WHPF_ENA_SHIFT                        0  /* WHPF_ENA */
#define WM8962_WHPF_ENA_WIDTH                        1  /* WHPF_ENA */

/*
 * W265 (0x109) - WHPF2
 */
#define WM8962_WHPF_COEFF_MASK                  0xFFFF  /* WHPF_COEFF - [15:0] */
#define WM8962_WHPF_COEFF_SHIFT                      0  /* WHPF_COEFF - [15:0] */
#define WM8962_WHPF_COEFF_WIDTH                     16  /* WHPF_COEFF - [15:0] */

/*
 * W268 (0x10C) - THWEED1
 */
#define WM8962_ADC_MONOMIX                      0x0040  /* ADC_MONOMIX */
#define WM8962_ADC_MONOMIX_MASK                 0x0040  /* ADC_MONOMIX */
#define WM8962_ADC_MONOMIX_SHIFT                     6  /* ADC_MONOMIX */
#define WM8962_ADC_MONOMIX_WIDTH                     1  /* ADC_MONOMIX */
#define WM8962_THWEED_SIGN_W                    0x0020  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_MASK               0x0020  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_SHIFT                   5  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_WIDTH                   1  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W                    0x0010  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_MASK               0x0010  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_SHIFT                   4  /* THWEED_SIGN_W */
#define WM8962_THWEED_SIGN_W_WIDTH                   1  /* THWEED_SIGN_W */
#define WM8962_THWEED_WHPF_MODE                 0x0004  /* THWEED_WHPF_MODE */
#define WM8962_THWEED_WHPF_MODE_MASK            0x0004  /* THWEED_WHPF_MODE */
#define WM8962_THWEED_WHPF_MODE_SHIFT                2  /* THWEED_WHPF_MODE */
#define WM8962_THWEED_WHPF_MODE_WIDTH                1  /* THWEED_WHPF_MODE */
#define WM8962_THWEED_WHPF_ENA                  0x0002  /* THWEED_WHPF_ENA */
#define WM8962_THWEED_WHPF_ENA_MASK             0x0002  /* THWEED_WHPF_ENA */
#define WM8962_THWEED_WHPF_ENA_SHIFT                 1  /* THWEED_WHPF_ENA */
#define WM8962_THWEED_WHPF_ENA_WIDTH                 1  /* THWEED_WHPF_ENA */
#define WM8962_THWEED_ENA                       0x0001  /* THWEED_ENA */
#define WM8962_THWEED_ENA_MASK                  0x0001  /* THWEED_ENA */
#define WM8962_THWEED_ENA_SHIFT                      0  /* THWEED_ENA */
#define WM8962_THWEED_ENA_WIDTH                      1  /* THWEED_ENA */

/*
 * W269 (0x10D) - THWEED2
 */
#define WM8962_THWEED_FGAINW_MASK               0xF800  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_FGAINW_SHIFT                  11  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_FGAINW_WIDTH                   5  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_CGAINW_MASK               0x07C0  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_CGAINW_SHIFT                   6  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_CGAINW_WIDTH                   5  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_DEWAYW_MASK               0x003C  /* THWEED_DEWAYW - [5:2] */
#define WM8962_THWEED_DEWAYW_SHIFT                   2  /* THWEED_DEWAYW - [5:2] */
#define WM8962_THWEED_DEWAYW_WIDTH                   4  /* THWEED_DEWAYW - [5:2] */

/*
 * W270 (0x10E) - THWEED3
 */
#define WM8962_THWEED_WHPF_COEFF_MASK           0xFFFF  /* THWEED_WHPF_COEFF - [15:0] */
#define WM8962_THWEED_WHPF_COEFF_SHIFT               0  /* THWEED_WHPF_COEFF - [15:0] */
#define WM8962_THWEED_WHPF_COEFF_WIDTH              16  /* THWEED_WHPF_COEFF - [15:0] */

/*
 * W271 (0x10F) - THWEED4
 */
#define WM8962_THWEED_FGAINW_MASK               0xF800  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_FGAINW_SHIFT                  11  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_FGAINW_WIDTH                   5  /* THWEED_FGAINW - [15:11] */
#define WM8962_THWEED_CGAINW_MASK               0x07C0  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_CGAINW_SHIFT                   6  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_CGAINW_WIDTH                   5  /* THWEED_CGAINW - [10:6] */
#define WM8962_THWEED_DEWAYW_MASK               0x003C  /* THWEED_DEWAYW - [5:2] */
#define WM8962_THWEED_DEWAYW_SHIFT                   2  /* THWEED_DEWAYW - [5:2] */
#define WM8962_THWEED_DEWAYW_WIDTH                   4  /* THWEED_DEWAYW - [5:2] */

/*
 * W276 (0x114) - DWC 1
 */
#define WM8962_DWC_SIG_DET_WMS_MASK             0x7C00  /* DWC_SIG_DET_WMS - [14:10] */
#define WM8962_DWC_SIG_DET_WMS_SHIFT                10  /* DWC_SIG_DET_WMS - [14:10] */
#define WM8962_DWC_SIG_DET_WMS_WIDTH                 5  /* DWC_SIG_DET_WMS - [14:10] */
#define WM8962_DWC_SIG_DET_PK_MASK              0x0300  /* DWC_SIG_DET_PK - [9:8] */
#define WM8962_DWC_SIG_DET_PK_SHIFT                  8  /* DWC_SIG_DET_PK - [9:8] */
#define WM8962_DWC_SIG_DET_PK_WIDTH                  2  /* DWC_SIG_DET_PK - [9:8] */
#define WM8962_DWC_NG_ENA                       0x0080  /* DWC_NG_ENA */
#define WM8962_DWC_NG_ENA_MASK                  0x0080  /* DWC_NG_ENA */
#define WM8962_DWC_NG_ENA_SHIFT                      7  /* DWC_NG_ENA */
#define WM8962_DWC_NG_ENA_WIDTH                      1  /* DWC_NG_ENA */
#define WM8962_DWC_SIG_DET_MODE                 0x0040  /* DWC_SIG_DET_MODE */
#define WM8962_DWC_SIG_DET_MODE_MASK            0x0040  /* DWC_SIG_DET_MODE */
#define WM8962_DWC_SIG_DET_MODE_SHIFT                6  /* DWC_SIG_DET_MODE */
#define WM8962_DWC_SIG_DET_MODE_WIDTH                1  /* DWC_SIG_DET_MODE */
#define WM8962_DWC_SIG_DET                      0x0020  /* DWC_SIG_DET */
#define WM8962_DWC_SIG_DET_MASK                 0x0020  /* DWC_SIG_DET */
#define WM8962_DWC_SIG_DET_SHIFT                     5  /* DWC_SIG_DET */
#define WM8962_DWC_SIG_DET_WIDTH                     1  /* DWC_SIG_DET */
#define WM8962_DWC_KNEE2_OP_ENA                 0x0010  /* DWC_KNEE2_OP_ENA */
#define WM8962_DWC_KNEE2_OP_ENA_MASK            0x0010  /* DWC_KNEE2_OP_ENA */
#define WM8962_DWC_KNEE2_OP_ENA_SHIFT                4  /* DWC_KNEE2_OP_ENA */
#define WM8962_DWC_KNEE2_OP_ENA_WIDTH                1  /* DWC_KNEE2_OP_ENA */
#define WM8962_DWC_QW                           0x0008  /* DWC_QW */
#define WM8962_DWC_QW_MASK                      0x0008  /* DWC_QW */
#define WM8962_DWC_QW_SHIFT                          3  /* DWC_QW */
#define WM8962_DWC_QW_WIDTH                          1  /* DWC_QW */
#define WM8962_DWC_ANTICWIP                     0x0004  /* DWC_ANTICWIP */
#define WM8962_DWC_ANTICWIP_MASK                0x0004  /* DWC_ANTICWIP */
#define WM8962_DWC_ANTICWIP_SHIFT                    2  /* DWC_ANTICWIP */
#define WM8962_DWC_ANTICWIP_WIDTH                    1  /* DWC_ANTICWIP */
#define WM8962_DWC_MODE                         0x0002  /* DWC_MODE */
#define WM8962_DWC_MODE_MASK                    0x0002  /* DWC_MODE */
#define WM8962_DWC_MODE_SHIFT                        1  /* DWC_MODE */
#define WM8962_DWC_MODE_WIDTH                        1  /* DWC_MODE */
#define WM8962_DWC_ENA                          0x0001  /* DWC_ENA */
#define WM8962_DWC_ENA_MASK                     0x0001  /* DWC_ENA */
#define WM8962_DWC_ENA_SHIFT                         0  /* DWC_ENA */
#define WM8962_DWC_ENA_WIDTH                         1  /* DWC_ENA */

/*
 * W277 (0x115) - DWC 2
 */
#define WM8962_DWC_ATK_MASK                     0x1E00  /* DWC_ATK - [12:9] */
#define WM8962_DWC_ATK_SHIFT                         9  /* DWC_ATK - [12:9] */
#define WM8962_DWC_ATK_WIDTH                         4  /* DWC_ATK - [12:9] */
#define WM8962_DWC_DCY_MASK                     0x01E0  /* DWC_DCY - [8:5] */
#define WM8962_DWC_DCY_SHIFT                         5  /* DWC_DCY - [8:5] */
#define WM8962_DWC_DCY_WIDTH                         4  /* DWC_DCY - [8:5] */
#define WM8962_DWC_MINGAIN_MASK                 0x001C  /* DWC_MINGAIN - [4:2] */
#define WM8962_DWC_MINGAIN_SHIFT                     2  /* DWC_MINGAIN - [4:2] */
#define WM8962_DWC_MINGAIN_WIDTH                     3  /* DWC_MINGAIN - [4:2] */
#define WM8962_DWC_MAXGAIN_MASK                 0x0003  /* DWC_MAXGAIN - [1:0] */
#define WM8962_DWC_MAXGAIN_SHIFT                     0  /* DWC_MAXGAIN - [1:0] */
#define WM8962_DWC_MAXGAIN_WIDTH                     2  /* DWC_MAXGAIN - [1:0] */

/*
 * W278 (0x116) - DWC 3
 */
#define WM8962_DWC_NG_MINGAIN_MASK              0xF000  /* DWC_NG_MINGAIN - [15:12] */
#define WM8962_DWC_NG_MINGAIN_SHIFT                 12  /* DWC_NG_MINGAIN - [15:12] */
#define WM8962_DWC_NG_MINGAIN_WIDTH                  4  /* DWC_NG_MINGAIN - [15:12] */
#define WM8962_DWC_QW_THW_MASK                  0x0C00  /* DWC_QW_THW - [11:10] */
#define WM8962_DWC_QW_THW_SHIFT                     10  /* DWC_QW_THW - [11:10] */
#define WM8962_DWC_QW_THW_WIDTH                      2  /* DWC_QW_THW - [11:10] */
#define WM8962_DWC_QW_DCY_MASK                  0x0300  /* DWC_QW_DCY - [9:8] */
#define WM8962_DWC_QW_DCY_SHIFT                      8  /* DWC_QW_DCY - [9:8] */
#define WM8962_DWC_QW_DCY_WIDTH                      2  /* DWC_QW_DCY - [9:8] */
#define WM8962_DWC_NG_EXP_MASK                  0x00C0  /* DWC_NG_EXP - [7:6] */
#define WM8962_DWC_NG_EXP_SHIFT                      6  /* DWC_NG_EXP - [7:6] */
#define WM8962_DWC_NG_EXP_WIDTH                      2  /* DWC_NG_EXP - [7:6] */
#define WM8962_DWC_HI_COMP_MASK                 0x0038  /* DWC_HI_COMP - [5:3] */
#define WM8962_DWC_HI_COMP_SHIFT                     3  /* DWC_HI_COMP - [5:3] */
#define WM8962_DWC_HI_COMP_WIDTH                     3  /* DWC_HI_COMP - [5:3] */
#define WM8962_DWC_WO_COMP_MASK                 0x0007  /* DWC_WO_COMP - [2:0] */
#define WM8962_DWC_WO_COMP_SHIFT                     0  /* DWC_WO_COMP - [2:0] */
#define WM8962_DWC_WO_COMP_WIDTH                     3  /* DWC_WO_COMP - [2:0] */

/*
 * W279 (0x117) - DWC 4
 */
#define WM8962_DWC_KNEE_IP_MASK                 0x07E0  /* DWC_KNEE_IP - [10:5] */
#define WM8962_DWC_KNEE_IP_SHIFT                     5  /* DWC_KNEE_IP - [10:5] */
#define WM8962_DWC_KNEE_IP_WIDTH                     6  /* DWC_KNEE_IP - [10:5] */
#define WM8962_DWC_KNEE_OP_MASK                 0x001F  /* DWC_KNEE_OP - [4:0] */
#define WM8962_DWC_KNEE_OP_SHIFT                     0  /* DWC_KNEE_OP - [4:0] */
#define WM8962_DWC_KNEE_OP_WIDTH                     5  /* DWC_KNEE_OP - [4:0] */

/*
 * W280 (0x118) - DWC 5
 */
#define WM8962_DWC_KNEE2_IP_MASK                0x03E0  /* DWC_KNEE2_IP - [9:5] */
#define WM8962_DWC_KNEE2_IP_SHIFT                    5  /* DWC_KNEE2_IP - [9:5] */
#define WM8962_DWC_KNEE2_IP_WIDTH                    5  /* DWC_KNEE2_IP - [9:5] */
#define WM8962_DWC_KNEE2_OP_MASK                0x001F  /* DWC_KNEE2_OP - [4:0] */
#define WM8962_DWC_KNEE2_OP_SHIFT                    0  /* DWC_KNEE2_OP - [4:0] */
#define WM8962_DWC_KNEE2_OP_WIDTH                    5  /* DWC_KNEE2_OP - [4:0] */

/*
 * W285 (0x11D) - Twoopback
 */
#define WM8962_TWB_ENA                          0x0002  /* TWB_ENA */
#define WM8962_TWB_ENA_MASK                     0x0002  /* TWB_ENA */
#define WM8962_TWB_ENA_SHIFT                         1  /* TWB_ENA */
#define WM8962_TWB_ENA_WIDTH                         1  /* TWB_ENA */
#define WM8962_TWB_MODE                         0x0001  /* TWB_MODE */
#define WM8962_TWB_MODE_MASK                    0x0001  /* TWB_MODE */
#define WM8962_TWB_MODE_SHIFT                        0  /* TWB_MODE */
#define WM8962_TWB_MODE_WIDTH                        1  /* TWB_MODE */

/*
 * W335 (0x14F) - EQ1
 */
#define WM8962_EQ_SHAWED_COEFF                  0x0004  /* EQ_SHAWED_COEFF */
#define WM8962_EQ_SHAWED_COEFF_MASK             0x0004  /* EQ_SHAWED_COEFF */
#define WM8962_EQ_SHAWED_COEFF_SHIFT                 2  /* EQ_SHAWED_COEFF */
#define WM8962_EQ_SHAWED_COEFF_WIDTH                 1  /* EQ_SHAWED_COEFF */
#define WM8962_EQ_SHAWED_COEFF_SEW              0x0002  /* EQ_SHAWED_COEFF_SEW */
#define WM8962_EQ_SHAWED_COEFF_SEW_MASK         0x0002  /* EQ_SHAWED_COEFF_SEW */
#define WM8962_EQ_SHAWED_COEFF_SEW_SHIFT             1  /* EQ_SHAWED_COEFF_SEW */
#define WM8962_EQ_SHAWED_COEFF_SEW_WIDTH             1  /* EQ_SHAWED_COEFF_SEW */
#define WM8962_EQ_ENA                           0x0001  /* EQ_ENA */
#define WM8962_EQ_ENA_MASK                      0x0001  /* EQ_ENA */
#define WM8962_EQ_ENA_SHIFT                          0  /* EQ_ENA */
#define WM8962_EQ_ENA_WIDTH                          1  /* EQ_ENA */

/*
 * W336 (0x150) - EQ2
 */
#define WM8962_EQW_B1_GAIN_MASK                 0xF800  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B1_GAIN_SHIFT                    11  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B1_GAIN_WIDTH                     5  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B2_GAIN_MASK                 0x07C0  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B2_GAIN_SHIFT                     6  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B2_GAIN_WIDTH                     5  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B3_GAIN_MASK                 0x003E  /* EQW_B3_GAIN - [5:1] */
#define WM8962_EQW_B3_GAIN_SHIFT                     1  /* EQW_B3_GAIN - [5:1] */
#define WM8962_EQW_B3_GAIN_WIDTH                     5  /* EQW_B3_GAIN - [5:1] */

/*
 * W337 (0x151) - EQ3
 */
#define WM8962_EQW_B4_GAIN_MASK                 0xF800  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B4_GAIN_SHIFT                    11  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B4_GAIN_WIDTH                     5  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B5_GAIN_MASK                 0x07C0  /* EQW_B5_GAIN - [10:6] */
#define WM8962_EQW_B5_GAIN_SHIFT                     6  /* EQW_B5_GAIN - [10:6] */
#define WM8962_EQW_B5_GAIN_WIDTH                     5  /* EQW_B5_GAIN - [10:6] */

/*
 * W338 (0x152) - EQ4
 */
#define WM8962_EQW_B1_A_MASK                    0xFFFF  /* EQW_B1_A - [15:0] */
#define WM8962_EQW_B1_A_SHIFT                        0  /* EQW_B1_A - [15:0] */
#define WM8962_EQW_B1_A_WIDTH                       16  /* EQW_B1_A - [15:0] */

/*
 * W339 (0x153) - EQ5
 */
#define WM8962_EQW_B1_B_MASK                    0xFFFF  /* EQW_B1_B - [15:0] */
#define WM8962_EQW_B1_B_SHIFT                        0  /* EQW_B1_B - [15:0] */
#define WM8962_EQW_B1_B_WIDTH                       16  /* EQW_B1_B - [15:0] */

/*
 * W340 (0x154) - EQ6
 */
#define WM8962_EQW_B1_PG_MASK                   0xFFFF  /* EQW_B1_PG - [15:0] */
#define WM8962_EQW_B1_PG_SHIFT                       0  /* EQW_B1_PG - [15:0] */
#define WM8962_EQW_B1_PG_WIDTH                      16  /* EQW_B1_PG - [15:0] */

/*
 * W341 (0x155) - EQ7
 */
#define WM8962_EQW_B2_A_MASK                    0xFFFF  /* EQW_B2_A - [15:0] */
#define WM8962_EQW_B2_A_SHIFT                        0  /* EQW_B2_A - [15:0] */
#define WM8962_EQW_B2_A_WIDTH                       16  /* EQW_B2_A - [15:0] */

/*
 * W342 (0x156) - EQ8
 */
#define WM8962_EQW_B2_B_MASK                    0xFFFF  /* EQW_B2_B - [15:0] */
#define WM8962_EQW_B2_B_SHIFT                        0  /* EQW_B2_B - [15:0] */
#define WM8962_EQW_B2_B_WIDTH                       16  /* EQW_B2_B - [15:0] */

/*
 * W343 (0x157) - EQ9
 */
#define WM8962_EQW_B2_C_MASK                    0xFFFF  /* EQW_B2_C - [15:0] */
#define WM8962_EQW_B2_C_SHIFT                        0  /* EQW_B2_C - [15:0] */
#define WM8962_EQW_B2_C_WIDTH                       16  /* EQW_B2_C - [15:0] */

/*
 * W344 (0x158) - EQ10
 */
#define WM8962_EQW_B2_PG_MASK                   0xFFFF  /* EQW_B2_PG - [15:0] */
#define WM8962_EQW_B2_PG_SHIFT                       0  /* EQW_B2_PG - [15:0] */
#define WM8962_EQW_B2_PG_WIDTH                      16  /* EQW_B2_PG - [15:0] */

/*
 * W345 (0x159) - EQ11
 */
#define WM8962_EQW_B3_A_MASK                    0xFFFF  /* EQW_B3_A - [15:0] */
#define WM8962_EQW_B3_A_SHIFT                        0  /* EQW_B3_A - [15:0] */
#define WM8962_EQW_B3_A_WIDTH                       16  /* EQW_B3_A - [15:0] */

/*
 * W346 (0x15A) - EQ12
 */
#define WM8962_EQW_B3_B_MASK                    0xFFFF  /* EQW_B3_B - [15:0] */
#define WM8962_EQW_B3_B_SHIFT                        0  /* EQW_B3_B - [15:0] */
#define WM8962_EQW_B3_B_WIDTH                       16  /* EQW_B3_B - [15:0] */

/*
 * W347 (0x15B) - EQ13
 */
#define WM8962_EQW_B3_C_MASK                    0xFFFF  /* EQW_B3_C - [15:0] */
#define WM8962_EQW_B3_C_SHIFT                        0  /* EQW_B3_C - [15:0] */
#define WM8962_EQW_B3_C_WIDTH                       16  /* EQW_B3_C - [15:0] */

/*
 * W348 (0x15C) - EQ14
 */
#define WM8962_EQW_B3_PG_MASK                   0xFFFF  /* EQW_B3_PG - [15:0] */
#define WM8962_EQW_B3_PG_SHIFT                       0  /* EQW_B3_PG - [15:0] */
#define WM8962_EQW_B3_PG_WIDTH                      16  /* EQW_B3_PG - [15:0] */

/*
 * W349 (0x15D) - EQ15
 */
#define WM8962_EQW_B4_A_MASK                    0xFFFF  /* EQW_B4_A - [15:0] */
#define WM8962_EQW_B4_A_SHIFT                        0  /* EQW_B4_A - [15:0] */
#define WM8962_EQW_B4_A_WIDTH                       16  /* EQW_B4_A - [15:0] */

/*
 * W350 (0x15E) - EQ16
 */
#define WM8962_EQW_B4_B_MASK                    0xFFFF  /* EQW_B4_B - [15:0] */
#define WM8962_EQW_B4_B_SHIFT                        0  /* EQW_B4_B - [15:0] */
#define WM8962_EQW_B4_B_WIDTH                       16  /* EQW_B4_B - [15:0] */

/*
 * W351 (0x15F) - EQ17
 */
#define WM8962_EQW_B4_C_MASK                    0xFFFF  /* EQW_B4_C - [15:0] */
#define WM8962_EQW_B4_C_SHIFT                        0  /* EQW_B4_C - [15:0] */
#define WM8962_EQW_B4_C_WIDTH                       16  /* EQW_B4_C - [15:0] */

/*
 * W352 (0x160) - EQ18
 */
#define WM8962_EQW_B4_PG_MASK                   0xFFFF  /* EQW_B4_PG - [15:0] */
#define WM8962_EQW_B4_PG_SHIFT                       0  /* EQW_B4_PG - [15:0] */
#define WM8962_EQW_B4_PG_WIDTH                      16  /* EQW_B4_PG - [15:0] */

/*
 * W353 (0x161) - EQ19
 */
#define WM8962_EQW_B5_A_MASK                    0xFFFF  /* EQW_B5_A - [15:0] */
#define WM8962_EQW_B5_A_SHIFT                        0  /* EQW_B5_A - [15:0] */
#define WM8962_EQW_B5_A_WIDTH                       16  /* EQW_B5_A - [15:0] */

/*
 * W354 (0x162) - EQ20
 */
#define WM8962_EQW_B5_B_MASK                    0xFFFF  /* EQW_B5_B - [15:0] */
#define WM8962_EQW_B5_B_SHIFT                        0  /* EQW_B5_B - [15:0] */
#define WM8962_EQW_B5_B_WIDTH                       16  /* EQW_B5_B - [15:0] */

/*
 * W355 (0x163) - EQ21
 */
#define WM8962_EQW_B5_PG_MASK                   0xFFFF  /* EQW_B5_PG - [15:0] */
#define WM8962_EQW_B5_PG_SHIFT                       0  /* EQW_B5_PG - [15:0] */
#define WM8962_EQW_B5_PG_WIDTH                      16  /* EQW_B5_PG - [15:0] */

/*
 * W356 (0x164) - EQ22
 */
#define WM8962_EQW_B1_GAIN_MASK                 0xF800  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B1_GAIN_SHIFT                    11  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B1_GAIN_WIDTH                     5  /* EQW_B1_GAIN - [15:11] */
#define WM8962_EQW_B2_GAIN_MASK                 0x07C0  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B2_GAIN_SHIFT                     6  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B2_GAIN_WIDTH                     5  /* EQW_B2_GAIN - [10:6] */
#define WM8962_EQW_B3_GAIN_MASK                 0x003E  /* EQW_B3_GAIN - [5:1] */
#define WM8962_EQW_B3_GAIN_SHIFT                     1  /* EQW_B3_GAIN - [5:1] */
#define WM8962_EQW_B3_GAIN_WIDTH                     5  /* EQW_B3_GAIN - [5:1] */

/*
 * W357 (0x165) - EQ23
 */
#define WM8962_EQW_B4_GAIN_MASK                 0xF800  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B4_GAIN_SHIFT                    11  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B4_GAIN_WIDTH                     5  /* EQW_B4_GAIN - [15:11] */
#define WM8962_EQW_B5_GAIN_MASK                 0x07C0  /* EQW_B5_GAIN - [10:6] */
#define WM8962_EQW_B5_GAIN_SHIFT                     6  /* EQW_B5_GAIN - [10:6] */
#define WM8962_EQW_B5_GAIN_WIDTH                     5  /* EQW_B5_GAIN - [10:6] */

/*
 * W358 (0x166) - EQ24
 */
#define WM8962_EQW_B1_A_MASK                    0xFFFF  /* EQW_B1_A - [15:0] */
#define WM8962_EQW_B1_A_SHIFT                        0  /* EQW_B1_A - [15:0] */
#define WM8962_EQW_B1_A_WIDTH                       16  /* EQW_B1_A - [15:0] */

/*
 * W359 (0x167) - EQ25
 */
#define WM8962_EQW_B1_B_MASK                    0xFFFF  /* EQW_B1_B - [15:0] */
#define WM8962_EQW_B1_B_SHIFT                        0  /* EQW_B1_B - [15:0] */
#define WM8962_EQW_B1_B_WIDTH                       16  /* EQW_B1_B - [15:0] */

/*
 * W360 (0x168) - EQ26
 */
#define WM8962_EQW_B1_PG_MASK                   0xFFFF  /* EQW_B1_PG - [15:0] */
#define WM8962_EQW_B1_PG_SHIFT                       0  /* EQW_B1_PG - [15:0] */
#define WM8962_EQW_B1_PG_WIDTH                      16  /* EQW_B1_PG - [15:0] */

/*
 * W361 (0x169) - EQ27
 */
#define WM8962_EQW_B2_A_MASK                    0xFFFF  /* EQW_B2_A - [15:0] */
#define WM8962_EQW_B2_A_SHIFT                        0  /* EQW_B2_A - [15:0] */
#define WM8962_EQW_B2_A_WIDTH                       16  /* EQW_B2_A - [15:0] */

/*
 * W362 (0x16A) - EQ28
 */
#define WM8962_EQW_B2_B_MASK                    0xFFFF  /* EQW_B2_B - [15:0] */
#define WM8962_EQW_B2_B_SHIFT                        0  /* EQW_B2_B - [15:0] */
#define WM8962_EQW_B2_B_WIDTH                       16  /* EQW_B2_B - [15:0] */

/*
 * W363 (0x16B) - EQ29
 */
#define WM8962_EQW_B2_C_MASK                    0xFFFF  /* EQW_B2_C - [15:0] */
#define WM8962_EQW_B2_C_SHIFT                        0  /* EQW_B2_C - [15:0] */
#define WM8962_EQW_B2_C_WIDTH                       16  /* EQW_B2_C - [15:0] */

/*
 * W364 (0x16C) - EQ30
 */
#define WM8962_EQW_B2_PG_MASK                   0xFFFF  /* EQW_B2_PG - [15:0] */
#define WM8962_EQW_B2_PG_SHIFT                       0  /* EQW_B2_PG - [15:0] */
#define WM8962_EQW_B2_PG_WIDTH                      16  /* EQW_B2_PG - [15:0] */

/*
 * W365 (0x16D) - EQ31
 */
#define WM8962_EQW_B3_A_MASK                    0xFFFF  /* EQW_B3_A - [15:0] */
#define WM8962_EQW_B3_A_SHIFT                        0  /* EQW_B3_A - [15:0] */
#define WM8962_EQW_B3_A_WIDTH                       16  /* EQW_B3_A - [15:0] */

/*
 * W366 (0x16E) - EQ32
 */
#define WM8962_EQW_B3_B_MASK                    0xFFFF  /* EQW_B3_B - [15:0] */
#define WM8962_EQW_B3_B_SHIFT                        0  /* EQW_B3_B - [15:0] */
#define WM8962_EQW_B3_B_WIDTH                       16  /* EQW_B3_B - [15:0] */

/*
 * W367 (0x16F) - EQ33
 */
#define WM8962_EQW_B3_C_MASK                    0xFFFF  /* EQW_B3_C - [15:0] */
#define WM8962_EQW_B3_C_SHIFT                        0  /* EQW_B3_C - [15:0] */
#define WM8962_EQW_B3_C_WIDTH                       16  /* EQW_B3_C - [15:0] */

/*
 * W368 (0x170) - EQ34
 */
#define WM8962_EQW_B3_PG_MASK                   0xFFFF  /* EQW_B3_PG - [15:0] */
#define WM8962_EQW_B3_PG_SHIFT                       0  /* EQW_B3_PG - [15:0] */
#define WM8962_EQW_B3_PG_WIDTH                      16  /* EQW_B3_PG - [15:0] */

/*
 * W369 (0x171) - EQ35
 */
#define WM8962_EQW_B4_A_MASK                    0xFFFF  /* EQW_B4_A - [15:0] */
#define WM8962_EQW_B4_A_SHIFT                        0  /* EQW_B4_A - [15:0] */
#define WM8962_EQW_B4_A_WIDTH                       16  /* EQW_B4_A - [15:0] */

/*
 * W370 (0x172) - EQ36
 */
#define WM8962_EQW_B4_B_MASK                    0xFFFF  /* EQW_B4_B - [15:0] */
#define WM8962_EQW_B4_B_SHIFT                        0  /* EQW_B4_B - [15:0] */
#define WM8962_EQW_B4_B_WIDTH                       16  /* EQW_B4_B - [15:0] */

/*
 * W371 (0x173) - EQ37
 */
#define WM8962_EQW_B4_C_MASK                    0xFFFF  /* EQW_B4_C - [15:0] */
#define WM8962_EQW_B4_C_SHIFT                        0  /* EQW_B4_C - [15:0] */
#define WM8962_EQW_B4_C_WIDTH                       16  /* EQW_B4_C - [15:0] */

/*
 * W372 (0x174) - EQ38
 */
#define WM8962_EQW_B4_PG_MASK                   0xFFFF  /* EQW_B4_PG - [15:0] */
#define WM8962_EQW_B4_PG_SHIFT                       0  /* EQW_B4_PG - [15:0] */
#define WM8962_EQW_B4_PG_WIDTH                      16  /* EQW_B4_PG - [15:0] */

/*
 * W373 (0x175) - EQ39
 */
#define WM8962_EQW_B5_A_MASK                    0xFFFF  /* EQW_B5_A - [15:0] */
#define WM8962_EQW_B5_A_SHIFT                        0  /* EQW_B5_A - [15:0] */
#define WM8962_EQW_B5_A_WIDTH                       16  /* EQW_B5_A - [15:0] */

/*
 * W374 (0x176) - EQ40
 */
#define WM8962_EQW_B5_B_MASK                    0xFFFF  /* EQW_B5_B - [15:0] */
#define WM8962_EQW_B5_B_SHIFT                        0  /* EQW_B5_B - [15:0] */
#define WM8962_EQW_B5_B_WIDTH                       16  /* EQW_B5_B - [15:0] */

/*
 * W375 (0x177) - EQ41
 */
#define WM8962_EQW_B5_PG_MASK                   0xFFFF  /* EQW_B5_PG - [15:0] */
#define WM8962_EQW_B5_PG_SHIFT                       0  /* EQW_B5_PG - [15:0] */
#define WM8962_EQW_B5_PG_WIDTH                      16  /* EQW_B5_PG - [15:0] */

/*
 * W513 (0x201) - GPIO 2
 */
#define WM8962_GP2_POW                          0x0400  /* GP2_POW */
#define WM8962_GP2_POW_MASK                     0x0400  /* GP2_POW */
#define WM8962_GP2_POW_SHIFT                        10  /* GP2_POW */
#define WM8962_GP2_POW_WIDTH                         1  /* GP2_POW */
#define WM8962_GP2_WVW                          0x0040  /* GP2_WVW */
#define WM8962_GP2_WVW_MASK                     0x0040  /* GP2_WVW */
#define WM8962_GP2_WVW_SHIFT                         6  /* GP2_WVW */
#define WM8962_GP2_WVW_WIDTH                         1  /* GP2_WVW */
#define WM8962_GP2_FN_MASK                      0x001F  /* GP2_FN - [4:0] */
#define WM8962_GP2_FN_SHIFT                          0  /* GP2_FN - [4:0] */
#define WM8962_GP2_FN_WIDTH                          5  /* GP2_FN - [4:0] */

/*
 * W514 (0x202) - GPIO 3
 */
#define WM8962_GP3_POW                          0x0400  /* GP3_POW */
#define WM8962_GP3_POW_MASK                     0x0400  /* GP3_POW */
#define WM8962_GP3_POW_SHIFT                        10  /* GP3_POW */
#define WM8962_GP3_POW_WIDTH                         1  /* GP3_POW */
#define WM8962_GP3_WVW                          0x0040  /* GP3_WVW */
#define WM8962_GP3_WVW_MASK                     0x0040  /* GP3_WVW */
#define WM8962_GP3_WVW_SHIFT                         6  /* GP3_WVW */
#define WM8962_GP3_WVW_WIDTH                         1  /* GP3_WVW */
#define WM8962_GP3_FN_MASK                      0x001F  /* GP3_FN - [4:0] */
#define WM8962_GP3_FN_SHIFT                          0  /* GP3_FN - [4:0] */
#define WM8962_GP3_FN_WIDTH                          5  /* GP3_FN - [4:0] */

/*
 * W516 (0x204) - GPIO 5
 */
#define WM8962_GP5_DIW                          0x8000  /* GP5_DIW */
#define WM8962_GP5_DIW_MASK                     0x8000  /* GP5_DIW */
#define WM8962_GP5_DIW_SHIFT                        15  /* GP5_DIW */
#define WM8962_GP5_DIW_WIDTH                         1  /* GP5_DIW */
#define WM8962_GP5_PU                           0x4000  /* GP5_PU */
#define WM8962_GP5_PU_MASK                      0x4000  /* GP5_PU */
#define WM8962_GP5_PU_SHIFT                         14  /* GP5_PU */
#define WM8962_GP5_PU_WIDTH                          1  /* GP5_PU */
#define WM8962_GP5_PD                           0x2000  /* GP5_PD */
#define WM8962_GP5_PD_MASK                      0x2000  /* GP5_PD */
#define WM8962_GP5_PD_SHIFT                         13  /* GP5_PD */
#define WM8962_GP5_PD_WIDTH                          1  /* GP5_PD */
#define WM8962_GP5_POW                          0x0400  /* GP5_POW */
#define WM8962_GP5_POW_MASK                     0x0400  /* GP5_POW */
#define WM8962_GP5_POW_SHIFT                        10  /* GP5_POW */
#define WM8962_GP5_POW_WIDTH                         1  /* GP5_POW */
#define WM8962_GP5_OP_CFG                       0x0200  /* GP5_OP_CFG */
#define WM8962_GP5_OP_CFG_MASK                  0x0200  /* GP5_OP_CFG */
#define WM8962_GP5_OP_CFG_SHIFT                      9  /* GP5_OP_CFG */
#define WM8962_GP5_OP_CFG_WIDTH                      1  /* GP5_OP_CFG */
#define WM8962_GP5_DB                           0x0100  /* GP5_DB */
#define WM8962_GP5_DB_MASK                      0x0100  /* GP5_DB */
#define WM8962_GP5_DB_SHIFT                          8  /* GP5_DB */
#define WM8962_GP5_DB_WIDTH                          1  /* GP5_DB */
#define WM8962_GP5_WVW                          0x0040  /* GP5_WVW */
#define WM8962_GP5_WVW_MASK                     0x0040  /* GP5_WVW */
#define WM8962_GP5_WVW_SHIFT                         6  /* GP5_WVW */
#define WM8962_GP5_WVW_WIDTH                         1  /* GP5_WVW */
#define WM8962_GP5_FN_MASK                      0x001F  /* GP5_FN - [4:0] */
#define WM8962_GP5_FN_SHIFT                          0  /* GP5_FN - [4:0] */
#define WM8962_GP5_FN_WIDTH                          5  /* GP5_FN - [4:0] */

/*
 * W517 (0x205) - GPIO 6
 */
#define WM8962_GP6_DIW                          0x8000  /* GP6_DIW */
#define WM8962_GP6_DIW_MASK                     0x8000  /* GP6_DIW */
#define WM8962_GP6_DIW_SHIFT                        15  /* GP6_DIW */
#define WM8962_GP6_DIW_WIDTH                         1  /* GP6_DIW */
#define WM8962_GP6_PU                           0x4000  /* GP6_PU */
#define WM8962_GP6_PU_MASK                      0x4000  /* GP6_PU */
#define WM8962_GP6_PU_SHIFT                         14  /* GP6_PU */
#define WM8962_GP6_PU_WIDTH                          1  /* GP6_PU */
#define WM8962_GP6_PD                           0x2000  /* GP6_PD */
#define WM8962_GP6_PD_MASK                      0x2000  /* GP6_PD */
#define WM8962_GP6_PD_SHIFT                         13  /* GP6_PD */
#define WM8962_GP6_PD_WIDTH                          1  /* GP6_PD */
#define WM8962_GP6_POW                          0x0400  /* GP6_POW */
#define WM8962_GP6_POW_MASK                     0x0400  /* GP6_POW */
#define WM8962_GP6_POW_SHIFT                        10  /* GP6_POW */
#define WM8962_GP6_POW_WIDTH                         1  /* GP6_POW */
#define WM8962_GP6_OP_CFG                       0x0200  /* GP6_OP_CFG */
#define WM8962_GP6_OP_CFG_MASK                  0x0200  /* GP6_OP_CFG */
#define WM8962_GP6_OP_CFG_SHIFT                      9  /* GP6_OP_CFG */
#define WM8962_GP6_OP_CFG_WIDTH                      1  /* GP6_OP_CFG */
#define WM8962_GP6_DB                           0x0100  /* GP6_DB */
#define WM8962_GP6_DB_MASK                      0x0100  /* GP6_DB */
#define WM8962_GP6_DB_SHIFT                          8  /* GP6_DB */
#define WM8962_GP6_DB_WIDTH                          1  /* GP6_DB */
#define WM8962_GP6_WVW                          0x0040  /* GP6_WVW */
#define WM8962_GP6_WVW_MASK                     0x0040  /* GP6_WVW */
#define WM8962_GP6_WVW_SHIFT                         6  /* GP6_WVW */
#define WM8962_GP6_WVW_WIDTH                         1  /* GP6_WVW */
#define WM8962_GP6_FN_MASK                      0x001F  /* GP6_FN - [4:0] */
#define WM8962_GP6_FN_SHIFT                          0  /* GP6_FN - [4:0] */
#define WM8962_GP6_FN_WIDTH                          5  /* GP6_FN - [4:0] */

/*
 * W560 (0x230) - Intewwupt Status 1
 */
#define WM8962_GP6_EINT                         0x0020  /* GP6_EINT */
#define WM8962_GP6_EINT_MASK                    0x0020  /* GP6_EINT */
#define WM8962_GP6_EINT_SHIFT                        5  /* GP6_EINT */
#define WM8962_GP6_EINT_WIDTH                        1  /* GP6_EINT */
#define WM8962_GP5_EINT                         0x0010  /* GP5_EINT */
#define WM8962_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#define WM8962_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#define WM8962_GP5_EINT_WIDTH                        1  /* GP5_EINT */

/*
 * W561 (0x231) - Intewwupt Status 2
 */
#define WM8962_MICSCD_EINT                      0x8000  /* MICSCD_EINT */
#define WM8962_MICSCD_EINT_MASK                 0x8000  /* MICSCD_EINT */
#define WM8962_MICSCD_EINT_SHIFT                    15  /* MICSCD_EINT */
#define WM8962_MICSCD_EINT_WIDTH                     1  /* MICSCD_EINT */
#define WM8962_MICD_EINT                        0x4000  /* MICD_EINT */
#define WM8962_MICD_EINT_MASK                   0x4000  /* MICD_EINT */
#define WM8962_MICD_EINT_SHIFT                      14  /* MICD_EINT */
#define WM8962_MICD_EINT_WIDTH                       1  /* MICD_EINT */
#define WM8962_FIFOS_EWW_EINT                   0x2000  /* FIFOS_EWW_EINT */
#define WM8962_FIFOS_EWW_EINT_MASK              0x2000  /* FIFOS_EWW_EINT */
#define WM8962_FIFOS_EWW_EINT_SHIFT                 13  /* FIFOS_EWW_EINT */
#define WM8962_FIFOS_EWW_EINT_WIDTH                  1  /* FIFOS_EWW_EINT */
#define WM8962_AWC_WOCK_EINT                    0x1000  /* AWC_WOCK_EINT */
#define WM8962_AWC_WOCK_EINT_MASK               0x1000  /* AWC_WOCK_EINT */
#define WM8962_AWC_WOCK_EINT_SHIFT                  12  /* AWC_WOCK_EINT */
#define WM8962_AWC_WOCK_EINT_WIDTH                   1  /* AWC_WOCK_EINT */
#define WM8962_AWC_THWESH_EINT                  0x0800  /* AWC_THWESH_EINT */
#define WM8962_AWC_THWESH_EINT_MASK             0x0800  /* AWC_THWESH_EINT */
#define WM8962_AWC_THWESH_EINT_SHIFT                11  /* AWC_THWESH_EINT */
#define WM8962_AWC_THWESH_EINT_WIDTH                 1  /* AWC_THWESH_EINT */
#define WM8962_AWC_SAT_EINT                     0x0400  /* AWC_SAT_EINT */
#define WM8962_AWC_SAT_EINT_MASK                0x0400  /* AWC_SAT_EINT */
#define WM8962_AWC_SAT_EINT_SHIFT                   10  /* AWC_SAT_EINT */
#define WM8962_AWC_SAT_EINT_WIDTH                    1  /* AWC_SAT_EINT */
#define WM8962_AWC_PKOVW_EINT                   0x0200  /* AWC_PKOVW_EINT */
#define WM8962_AWC_PKOVW_EINT_MASK              0x0200  /* AWC_PKOVW_EINT */
#define WM8962_AWC_PKOVW_EINT_SHIFT                  9  /* AWC_PKOVW_EINT */
#define WM8962_AWC_PKOVW_EINT_WIDTH                  1  /* AWC_PKOVW_EINT */
#define WM8962_AWC_NGATE_EINT                   0x0100  /* AWC_NGATE_EINT */
#define WM8962_AWC_NGATE_EINT_MASK              0x0100  /* AWC_NGATE_EINT */
#define WM8962_AWC_NGATE_EINT_SHIFT                  8  /* AWC_NGATE_EINT */
#define WM8962_AWC_NGATE_EINT_WIDTH                  1  /* AWC_NGATE_EINT */
#define WM8962_WSEQ_DONE_EINT                   0x0080  /* WSEQ_DONE_EINT */
#define WM8962_WSEQ_DONE_EINT_MASK              0x0080  /* WSEQ_DONE_EINT */
#define WM8962_WSEQ_DONE_EINT_SHIFT                  7  /* WSEQ_DONE_EINT */
#define WM8962_WSEQ_DONE_EINT_WIDTH                  1  /* WSEQ_DONE_EINT */
#define WM8962_DWC_ACTDET_EINT                  0x0040  /* DWC_ACTDET_EINT */
#define WM8962_DWC_ACTDET_EINT_MASK             0x0040  /* DWC_ACTDET_EINT */
#define WM8962_DWC_ACTDET_EINT_SHIFT                 6  /* DWC_ACTDET_EINT */
#define WM8962_DWC_ACTDET_EINT_WIDTH                 1  /* DWC_ACTDET_EINT */
#define WM8962_FWW_WOCK_EINT                    0x0020  /* FWW_WOCK_EINT */
#define WM8962_FWW_WOCK_EINT_MASK               0x0020  /* FWW_WOCK_EINT */
#define WM8962_FWW_WOCK_EINT_SHIFT                   5  /* FWW_WOCK_EINT */
#define WM8962_FWW_WOCK_EINT_WIDTH                   1  /* FWW_WOCK_EINT */
#define WM8962_PWW3_WOCK_EINT                   0x0008  /* PWW3_WOCK_EINT */
#define WM8962_PWW3_WOCK_EINT_MASK              0x0008  /* PWW3_WOCK_EINT */
#define WM8962_PWW3_WOCK_EINT_SHIFT                  3  /* PWW3_WOCK_EINT */
#define WM8962_PWW3_WOCK_EINT_WIDTH                  1  /* PWW3_WOCK_EINT */
#define WM8962_PWW2_WOCK_EINT                   0x0004  /* PWW2_WOCK_EINT */
#define WM8962_PWW2_WOCK_EINT_MASK              0x0004  /* PWW2_WOCK_EINT */
#define WM8962_PWW2_WOCK_EINT_SHIFT                  2  /* PWW2_WOCK_EINT */
#define WM8962_PWW2_WOCK_EINT_WIDTH                  1  /* PWW2_WOCK_EINT */
#define WM8962_TEMP_SHUT_EINT                   0x0001  /* TEMP_SHUT_EINT */
#define WM8962_TEMP_SHUT_EINT_MASK              0x0001  /* TEMP_SHUT_EINT */
#define WM8962_TEMP_SHUT_EINT_SHIFT                  0  /* TEMP_SHUT_EINT */
#define WM8962_TEMP_SHUT_EINT_WIDTH                  1  /* TEMP_SHUT_EINT */

/*
 * W568 (0x238) - Intewwupt Status 1 Mask
 */
#define WM8962_IM_GP6_EINT                      0x0020  /* IM_GP6_EINT */
#define WM8962_IM_GP6_EINT_MASK                 0x0020  /* IM_GP6_EINT */
#define WM8962_IM_GP6_EINT_SHIFT                     5  /* IM_GP6_EINT */
#define WM8962_IM_GP6_EINT_WIDTH                     1  /* IM_GP6_EINT */
#define WM8962_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#define WM8962_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#define WM8962_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#define WM8962_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */

/*
 * W569 (0x239) - Intewwupt Status 2 Mask
 */
#define WM8962_IM_MICSCD_EINT                   0x8000  /* IM_MICSCD_EINT */
#define WM8962_IM_MICSCD_EINT_MASK              0x8000  /* IM_MICSCD_EINT */
#define WM8962_IM_MICSCD_EINT_SHIFT                 15  /* IM_MICSCD_EINT */
#define WM8962_IM_MICSCD_EINT_WIDTH                  1  /* IM_MICSCD_EINT */
#define WM8962_IM_MICD_EINT                     0x4000  /* IM_MICD_EINT */
#define WM8962_IM_MICD_EINT_MASK                0x4000  /* IM_MICD_EINT */
#define WM8962_IM_MICD_EINT_SHIFT                   14  /* IM_MICD_EINT */
#define WM8962_IM_MICD_EINT_WIDTH                    1  /* IM_MICD_EINT */
#define WM8962_IM_FIFOS_EWW_EINT                0x2000  /* IM_FIFOS_EWW_EINT */
#define WM8962_IM_FIFOS_EWW_EINT_MASK           0x2000  /* IM_FIFOS_EWW_EINT */
#define WM8962_IM_FIFOS_EWW_EINT_SHIFT              13  /* IM_FIFOS_EWW_EINT */
#define WM8962_IM_FIFOS_EWW_EINT_WIDTH               1  /* IM_FIFOS_EWW_EINT */
#define WM8962_IM_AWC_WOCK_EINT                 0x1000  /* IM_AWC_WOCK_EINT */
#define WM8962_IM_AWC_WOCK_EINT_MASK            0x1000  /* IM_AWC_WOCK_EINT */
#define WM8962_IM_AWC_WOCK_EINT_SHIFT               12  /* IM_AWC_WOCK_EINT */
#define WM8962_IM_AWC_WOCK_EINT_WIDTH                1  /* IM_AWC_WOCK_EINT */
#define WM8962_IM_AWC_THWESH_EINT               0x0800  /* IM_AWC_THWESH_EINT */
#define WM8962_IM_AWC_THWESH_EINT_MASK          0x0800  /* IM_AWC_THWESH_EINT */
#define WM8962_IM_AWC_THWESH_EINT_SHIFT             11  /* IM_AWC_THWESH_EINT */
#define WM8962_IM_AWC_THWESH_EINT_WIDTH              1  /* IM_AWC_THWESH_EINT */
#define WM8962_IM_AWC_SAT_EINT                  0x0400  /* IM_AWC_SAT_EINT */
#define WM8962_IM_AWC_SAT_EINT_MASK             0x0400  /* IM_AWC_SAT_EINT */
#define WM8962_IM_AWC_SAT_EINT_SHIFT                10  /* IM_AWC_SAT_EINT */
#define WM8962_IM_AWC_SAT_EINT_WIDTH                 1  /* IM_AWC_SAT_EINT */
#define WM8962_IM_AWC_PKOVW_EINT                0x0200  /* IM_AWC_PKOVW_EINT */
#define WM8962_IM_AWC_PKOVW_EINT_MASK           0x0200  /* IM_AWC_PKOVW_EINT */
#define WM8962_IM_AWC_PKOVW_EINT_SHIFT               9  /* IM_AWC_PKOVW_EINT */
#define WM8962_IM_AWC_PKOVW_EINT_WIDTH               1  /* IM_AWC_PKOVW_EINT */
#define WM8962_IM_AWC_NGATE_EINT                0x0100  /* IM_AWC_NGATE_EINT */
#define WM8962_IM_AWC_NGATE_EINT_MASK           0x0100  /* IM_AWC_NGATE_EINT */
#define WM8962_IM_AWC_NGATE_EINT_SHIFT               8  /* IM_AWC_NGATE_EINT */
#define WM8962_IM_AWC_NGATE_EINT_WIDTH               1  /* IM_AWC_NGATE_EINT */
#define WM8962_IM_WSEQ_DONE_EINT                0x0080  /* IM_WSEQ_DONE_EINT */
#define WM8962_IM_WSEQ_DONE_EINT_MASK           0x0080  /* IM_WSEQ_DONE_EINT */
#define WM8962_IM_WSEQ_DONE_EINT_SHIFT               7  /* IM_WSEQ_DONE_EINT */
#define WM8962_IM_WSEQ_DONE_EINT_WIDTH               1  /* IM_WSEQ_DONE_EINT */
#define WM8962_IM_DWC_ACTDET_EINT               0x0040  /* IM_DWC_ACTDET_EINT */
#define WM8962_IM_DWC_ACTDET_EINT_MASK          0x0040  /* IM_DWC_ACTDET_EINT */
#define WM8962_IM_DWC_ACTDET_EINT_SHIFT              6  /* IM_DWC_ACTDET_EINT */
#define WM8962_IM_DWC_ACTDET_EINT_WIDTH              1  /* IM_DWC_ACTDET_EINT */
#define WM8962_IM_FWW_WOCK_EINT                 0x0020  /* IM_FWW_WOCK_EINT */
#define WM8962_IM_FWW_WOCK_EINT_MASK            0x0020  /* IM_FWW_WOCK_EINT */
#define WM8962_IM_FWW_WOCK_EINT_SHIFT                5  /* IM_FWW_WOCK_EINT */
#define WM8962_IM_FWW_WOCK_EINT_WIDTH                1  /* IM_FWW_WOCK_EINT */
#define WM8962_IM_PWW3_WOCK_EINT                0x0008  /* IM_PWW3_WOCK_EINT */
#define WM8962_IM_PWW3_WOCK_EINT_MASK           0x0008  /* IM_PWW3_WOCK_EINT */
#define WM8962_IM_PWW3_WOCK_EINT_SHIFT               3  /* IM_PWW3_WOCK_EINT */
#define WM8962_IM_PWW3_WOCK_EINT_WIDTH               1  /* IM_PWW3_WOCK_EINT */
#define WM8962_IM_PWW2_WOCK_EINT                0x0004  /* IM_PWW2_WOCK_EINT */
#define WM8962_IM_PWW2_WOCK_EINT_MASK           0x0004  /* IM_PWW2_WOCK_EINT */
#define WM8962_IM_PWW2_WOCK_EINT_SHIFT               2  /* IM_PWW2_WOCK_EINT */
#define WM8962_IM_PWW2_WOCK_EINT_WIDTH               1  /* IM_PWW2_WOCK_EINT */
#define WM8962_IM_TEMP_SHUT_EINT                0x0001  /* IM_TEMP_SHUT_EINT */
#define WM8962_IM_TEMP_SHUT_EINT_MASK           0x0001  /* IM_TEMP_SHUT_EINT */
#define WM8962_IM_TEMP_SHUT_EINT_SHIFT               0  /* IM_TEMP_SHUT_EINT */
#define WM8962_IM_TEMP_SHUT_EINT_WIDTH               1  /* IM_TEMP_SHUT_EINT */

/*
 * W576 (0x240) - Intewwupt Contwow
 */
#define WM8962_IWQ_POW                          0x0001  /* IWQ_POW */
#define WM8962_IWQ_POW_MASK                     0x0001  /* IWQ_POW */
#define WM8962_IWQ_POW_SHIFT                         0  /* IWQ_POW */
#define WM8962_IWQ_POW_WIDTH                         1  /* IWQ_POW */

/*
 * W584 (0x248) - IWQ Debounce
 */
#define WM8962_FWW_WOCK_DB                      0x0020  /* FWW_WOCK_DB */
#define WM8962_FWW_WOCK_DB_MASK                 0x0020  /* FWW_WOCK_DB */
#define WM8962_FWW_WOCK_DB_SHIFT                     5  /* FWW_WOCK_DB */
#define WM8962_FWW_WOCK_DB_WIDTH                     1  /* FWW_WOCK_DB */
#define WM8962_PWW3_WOCK_DB                     0x0008  /* PWW3_WOCK_DB */
#define WM8962_PWW3_WOCK_DB_MASK                0x0008  /* PWW3_WOCK_DB */
#define WM8962_PWW3_WOCK_DB_SHIFT                    3  /* PWW3_WOCK_DB */
#define WM8962_PWW3_WOCK_DB_WIDTH                    1  /* PWW3_WOCK_DB */
#define WM8962_PWW2_WOCK_DB                     0x0004  /* PWW2_WOCK_DB */
#define WM8962_PWW2_WOCK_DB_MASK                0x0004  /* PWW2_WOCK_DB */
#define WM8962_PWW2_WOCK_DB_SHIFT                    2  /* PWW2_WOCK_DB */
#define WM8962_PWW2_WOCK_DB_WIDTH                    1  /* PWW2_WOCK_DB */
#define WM8962_TEMP_SHUT_DB                     0x0001  /* TEMP_SHUT_DB */
#define WM8962_TEMP_SHUT_DB_MASK                0x0001  /* TEMP_SHUT_DB */
#define WM8962_TEMP_SHUT_DB_SHIFT                    0  /* TEMP_SHUT_DB */
#define WM8962_TEMP_SHUT_DB_WIDTH                    1  /* TEMP_SHUT_DB */

/*
 * W586 (0x24A) -  MICINT Souwce Pow
 */
#define WM8962_MICSCD_IWQ_POW                   0x8000  /* MICSCD_IWQ_POW */
#define WM8962_MICSCD_IWQ_POW_MASK              0x8000  /* MICSCD_IWQ_POW */
#define WM8962_MICSCD_IWQ_POW_SHIFT                 15  /* MICSCD_IWQ_POW */
#define WM8962_MICSCD_IWQ_POW_WIDTH                  1  /* MICSCD_IWQ_POW */
#define WM8962_MICD_IWQ_POW                     0x4000  /* MICD_IWQ_POW */
#define WM8962_MICD_IWQ_POW_MASK                0x4000  /* MICD_IWQ_POW */
#define WM8962_MICD_IWQ_POW_SHIFT                   14  /* MICD_IWQ_POW */
#define WM8962_MICD_IWQ_POW_WIDTH                    1  /* MICD_IWQ_POW */

/*
 * W768 (0x300) - DSP2 Powew Management
 */
#define WM8962_DSP2_ENA                         0x0001  /* DSP2_ENA */
#define WM8962_DSP2_ENA_MASK                    0x0001  /* DSP2_ENA */
#define WM8962_DSP2_ENA_SHIFT                        0  /* DSP2_ENA */
#define WM8962_DSP2_ENA_WIDTH                        1  /* DSP2_ENA */

/*
 * W1037 (0x40D) - DSP2_ExecContwow
 */
#define WM8962_DSP2_STOPC                       0x0020  /* DSP2_STOPC */
#define WM8962_DSP2_STOPC_MASK                  0x0020  /* DSP2_STOPC */
#define WM8962_DSP2_STOPC_SHIFT                      5  /* DSP2_STOPC */
#define WM8962_DSP2_STOPC_WIDTH                      1  /* DSP2_STOPC */
#define WM8962_DSP2_STOPS                       0x0010  /* DSP2_STOPS */
#define WM8962_DSP2_STOPS_MASK                  0x0010  /* DSP2_STOPS */
#define WM8962_DSP2_STOPS_SHIFT                      4  /* DSP2_STOPS */
#define WM8962_DSP2_STOPS_WIDTH                      1  /* DSP2_STOPS */
#define WM8962_DSP2_STOPI                       0x0008  /* DSP2_STOPI */
#define WM8962_DSP2_STOPI_MASK                  0x0008  /* DSP2_STOPI */
#define WM8962_DSP2_STOPI_SHIFT                      3  /* DSP2_STOPI */
#define WM8962_DSP2_STOPI_WIDTH                      1  /* DSP2_STOPI */
#define WM8962_DSP2_STOP                        0x0004  /* DSP2_STOP */
#define WM8962_DSP2_STOP_MASK                   0x0004  /* DSP2_STOP */
#define WM8962_DSP2_STOP_SHIFT                       2  /* DSP2_STOP */
#define WM8962_DSP2_STOP_WIDTH                       1  /* DSP2_STOP */
#define WM8962_DSP2_WUNW                        0x0002  /* DSP2_WUNW */
#define WM8962_DSP2_WUNW_MASK                   0x0002  /* DSP2_WUNW */
#define WM8962_DSP2_WUNW_SHIFT                       1  /* DSP2_WUNW */
#define WM8962_DSP2_WUNW_WIDTH                       1  /* DSP2_WUNW */
#define WM8962_DSP2_WUN                         0x0001  /* DSP2_WUN */
#define WM8962_DSP2_WUN_MASK                    0x0001  /* DSP2_WUN */
#define WM8962_DSP2_WUN_SHIFT                        0  /* DSP2_WUN */
#define WM8962_DSP2_WUN_WIDTH                        1  /* DSP2_WUN */

/*
 * W8192 (0x2000) - DSP2 Instwuction WAM 0
 */
#define WM8962_DSP2_INSTW_WAM_1024_10_9_0_MASK  0x03FF  /* DSP2_INSTW_WAM_1024_10_9_0 - [9:0] */
#define WM8962_DSP2_INSTW_WAM_1024_10_9_0_SHIFT      0  /* DSP2_INSTW_WAM_1024_10_9_0 - [9:0] */
#define WM8962_DSP2_INSTW_WAM_1024_10_9_0_WIDTH     10  /* DSP2_INSTW_WAM_1024_10_9_0 - [9:0] */

/*
 * W9216 (0x2400) - DSP2 Addwess WAM 2
 */
#define WM8962_DSP2_ADDW_WAM_1024_38_37_32_MASK 0x003F  /* DSP2_ADDW_WAM_1024_38_37_32 - [5:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_37_32_SHIFT      0  /* DSP2_ADDW_WAM_1024_38_37_32 - [5:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_37_32_WIDTH      6  /* DSP2_ADDW_WAM_1024_38_37_32 - [5:0] */

/*
 * W9217 (0x2401) - DSP2 Addwess WAM 1
 */
#define WM8962_DSP2_ADDW_WAM_1024_38_31_16_MASK 0xFFFF  /* DSP2_ADDW_WAM_1024_38_31_16 - [15:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_31_16_SHIFT      0  /* DSP2_ADDW_WAM_1024_38_31_16 - [15:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_31_16_WIDTH     16  /* DSP2_ADDW_WAM_1024_38_31_16 - [15:0] */

/*
 * W9218 (0x2402) - DSP2 Addwess WAM 0
 */
#define WM8962_DSP2_ADDW_WAM_1024_38_15_0_MASK  0xFFFF  /* DSP2_ADDW_WAM_1024_38_15_0 - [15:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_15_0_SHIFT      0  /* DSP2_ADDW_WAM_1024_38_15_0 - [15:0] */
#define WM8962_DSP2_ADDW_WAM_1024_38_15_0_WIDTH     16  /* DSP2_ADDW_WAM_1024_38_15_0 - [15:0] */

/*
 * W12288 (0x3000) - DSP2 Data1 WAM 1
 */
#define WM8962_DSP2_DATA1_WAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA1_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA1_WAM_384_24_23_16_SHIFT      0  /* DSP2_DATA1_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA1_WAM_384_24_23_16_WIDTH      8  /* DSP2_DATA1_WAM_384_24_23_16 - [7:0] */

/*
 * W12289 (0x3001) - DSP2 Data1 WAM 0
 */
#define WM8962_DSP2_DATA1_WAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA1_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA1_WAM_384_24_15_0_SHIFT      0  /* DSP2_DATA1_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA1_WAM_384_24_15_0_WIDTH     16  /* DSP2_DATA1_WAM_384_24_15_0 - [15:0] */

/*
 * W13312 (0x3400) - DSP2 Data2 WAM 1
 */
#define WM8962_DSP2_DATA2_WAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA2_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA2_WAM_384_24_23_16_SHIFT      0  /* DSP2_DATA2_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA2_WAM_384_24_23_16_WIDTH      8  /* DSP2_DATA2_WAM_384_24_23_16 - [7:0] */

/*
 * W13313 (0x3401) - DSP2 Data2 WAM 0
 */
#define WM8962_DSP2_DATA2_WAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA2_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA2_WAM_384_24_15_0_SHIFT      0  /* DSP2_DATA2_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA2_WAM_384_24_15_0_WIDTH     16  /* DSP2_DATA2_WAM_384_24_15_0 - [15:0] */

/*
 * W14336 (0x3800) - DSP2 Data3 WAM 1
 */
#define WM8962_DSP2_DATA3_WAM_384_24_23_16_MASK 0x00FF  /* DSP2_DATA3_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA3_WAM_384_24_23_16_SHIFT      0  /* DSP2_DATA3_WAM_384_24_23_16 - [7:0] */
#define WM8962_DSP2_DATA3_WAM_384_24_23_16_WIDTH      8  /* DSP2_DATA3_WAM_384_24_23_16 - [7:0] */

/*
 * W14337 (0x3801) - DSP2 Data3 WAM 0
 */
#define WM8962_DSP2_DATA3_WAM_384_24_15_0_MASK  0xFFFF  /* DSP2_DATA3_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA3_WAM_384_24_15_0_SHIFT      0  /* DSP2_DATA3_WAM_384_24_15_0 - [15:0] */
#define WM8962_DSP2_DATA3_WAM_384_24_15_0_WIDTH     16  /* DSP2_DATA3_WAM_384_24_15_0 - [15:0] */

/*
 * W15360 (0x3C00) - DSP2 Coeff WAM 0
 */
#define WM8962_DSP2_CMAP_WAM_384_11_10_0_MASK   0x07FF  /* DSP2_CMAP_WAM_384_11_10_0 - [10:0] */
#define WM8962_DSP2_CMAP_WAM_384_11_10_0_SHIFT       0  /* DSP2_CMAP_WAM_384_11_10_0 - [10:0] */
#define WM8962_DSP2_CMAP_WAM_384_11_10_0_WIDTH      11  /* DSP2_CMAP_WAM_384_11_10_0 - [10:0] */

/*
 * W16384 (0x4000) - WETUNEADC_SHAWED_COEFF_1
 */
#define WM8962_ADC_WETUNE_SCV                   0x0080  /* ADC_WETUNE_SCV */
#define WM8962_ADC_WETUNE_SCV_MASK              0x0080  /* ADC_WETUNE_SCV */
#define WM8962_ADC_WETUNE_SCV_SHIFT                  7  /* ADC_WETUNE_SCV */
#define WM8962_ADC_WETUNE_SCV_WIDTH                  1  /* ADC_WETUNE_SCV */
#define WM8962_WETUNEADC_SHAWED_COEFF_22_16_MASK 0x007F  /* WETUNEADC_SHAWED_COEFF_22_16 - [6:0] */
#define WM8962_WETUNEADC_SHAWED_COEFF_22_16_SHIFT      0  /* WETUNEADC_SHAWED_COEFF_22_16 - [6:0] */
#define WM8962_WETUNEADC_SHAWED_COEFF_22_16_WIDTH      7  /* WETUNEADC_SHAWED_COEFF_22_16 - [6:0] */

/*
 * W16385 (0x4001) - WETUNEADC_SHAWED_COEFF_0
 */
#define WM8962_WETUNEADC_SHAWED_COEFF_15_00_MASK 0xFFFF  /* WETUNEADC_SHAWED_COEFF_15_00 - [15:0] */
#define WM8962_WETUNEADC_SHAWED_COEFF_15_00_SHIFT      0  /* WETUNEADC_SHAWED_COEFF_15_00 - [15:0] */
#define WM8962_WETUNEADC_SHAWED_COEFF_15_00_WIDTH     16  /* WETUNEADC_SHAWED_COEFF_15_00 - [15:0] */

/*
 * W16386 (0x4002) - WETUNEDAC_SHAWED_COEFF_1
 */
#define WM8962_DAC_WETUNE_SCV                   0x0080  /* DAC_WETUNE_SCV */
#define WM8962_DAC_WETUNE_SCV_MASK              0x0080  /* DAC_WETUNE_SCV */
#define WM8962_DAC_WETUNE_SCV_SHIFT                  7  /* DAC_WETUNE_SCV */
#define WM8962_DAC_WETUNE_SCV_WIDTH                  1  /* DAC_WETUNE_SCV */
#define WM8962_WETUNEDAC_SHAWED_COEFF_23_16_MASK 0x007F  /* WETUNEDAC_SHAWED_COEFF_23_16 - [6:0] */
#define WM8962_WETUNEDAC_SHAWED_COEFF_23_16_SHIFT      0  /* WETUNEDAC_SHAWED_COEFF_23_16 - [6:0] */
#define WM8962_WETUNEDAC_SHAWED_COEFF_23_16_WIDTH      7  /* WETUNEDAC_SHAWED_COEFF_23_16 - [6:0] */

/*
 * W16387 (0x4003) - WETUNEDAC_SHAWED_COEFF_0
 */
#define WM8962_WETUNEDAC_SHAWED_COEFF_15_00_MASK 0xFFFF  /* WETUNEDAC_SHAWED_COEFF_15_00 - [15:0] */
#define WM8962_WETUNEDAC_SHAWED_COEFF_15_00_SHIFT      0  /* WETUNEDAC_SHAWED_COEFF_15_00 - [15:0] */
#define WM8962_WETUNEDAC_SHAWED_COEFF_15_00_WIDTH     16  /* WETUNEDAC_SHAWED_COEFF_15_00 - [15:0] */

/*
 * W16388 (0x4004) - SOUNDSTAGE_ENABWES_1
 */
#define WM8962_SOUNDSTAGE_ENABWES_23_16_MASK    0x00FF  /* SOUNDSTAGE_ENABWES_23_16 - [7:0] */
#define WM8962_SOUNDSTAGE_ENABWES_23_16_SHIFT        0  /* SOUNDSTAGE_ENABWES_23_16 - [7:0] */
#define WM8962_SOUNDSTAGE_ENABWES_23_16_WIDTH        8  /* SOUNDSTAGE_ENABWES_23_16 - [7:0] */

/*
 * W16389 (0x4005) - SOUNDSTAGE_ENABWES_0
 */
#define WM8962_SOUNDSTAGE_ENABWES_15_06_MASK    0xFFC0  /* SOUNDSTAGE_ENABWES_15_06 - [15:6] */
#define WM8962_SOUNDSTAGE_ENABWES_15_06_SHIFT        6  /* SOUNDSTAGE_ENABWES_15_06 - [15:6] */
#define WM8962_SOUNDSTAGE_ENABWES_15_06_WIDTH       10  /* SOUNDSTAGE_ENABWES_15_06 - [15:6] */
#define WM8962_WTN_ADC_ENA                      0x0020  /* WTN_ADC_ENA */
#define WM8962_WTN_ADC_ENA_MASK                 0x0020  /* WTN_ADC_ENA */
#define WM8962_WTN_ADC_ENA_SHIFT                     5  /* WTN_ADC_ENA */
#define WM8962_WTN_ADC_ENA_WIDTH                     1  /* WTN_ADC_ENA */
#define WM8962_WTN_DAC_ENA                      0x0010  /* WTN_DAC_ENA */
#define WM8962_WTN_DAC_ENA_MASK                 0x0010  /* WTN_DAC_ENA */
#define WM8962_WTN_DAC_ENA_SHIFT                     4  /* WTN_DAC_ENA */
#define WM8962_WTN_DAC_ENA_WIDTH                     1  /* WTN_DAC_ENA */
#define WM8962_HDBASS_ENA                       0x0008  /* HDBASS_ENA */
#define WM8962_HDBASS_ENA_MASK                  0x0008  /* HDBASS_ENA */
#define WM8962_HDBASS_ENA_SHIFT                      3  /* HDBASS_ENA */
#define WM8962_HDBASS_ENA_WIDTH                      1  /* HDBASS_ENA */
#define WM8962_HPF2_ENA                         0x0004  /* HPF2_ENA */
#define WM8962_HPF2_ENA_MASK                    0x0004  /* HPF2_ENA */
#define WM8962_HPF2_ENA_SHIFT                        2  /* HPF2_ENA */
#define WM8962_HPF2_ENA_WIDTH                        1  /* HPF2_ENA */
#define WM8962_HPF1_ENA                         0x0002  /* HPF1_ENA */
#define WM8962_HPF1_ENA_MASK                    0x0002  /* HPF1_ENA */
#define WM8962_HPF1_ENA_SHIFT                        1  /* HPF1_ENA */
#define WM8962_HPF1_ENA_WIDTH                        1  /* HPF1_ENA */
#define WM8962_VSS_ENA                          0x0001  /* VSS_ENA */
#define WM8962_VSS_ENA_MASK                     0x0001  /* VSS_ENA */
#define WM8962_VSS_ENA_SHIFT                         0  /* VSS_ENA */
#define WM8962_VSS_ENA_WIDTH                         1  /* VSS_ENA */

int wm8962_mic_detect(stwuct snd_soc_component *component, stwuct snd_soc_jack *jack);

#endif
