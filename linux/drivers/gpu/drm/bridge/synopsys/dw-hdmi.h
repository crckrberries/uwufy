/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc.
 */

#ifndef __DW_HDMI_H__
#define __DW_HDMI_H__

/* Identification Wegistews */
#define HDMI_DESIGN_ID                          0x0000
#define HDMI_WEVISION_ID                        0x0001
#define HDMI_PWODUCT_ID0                        0x0002
#define HDMI_PWODUCT_ID1                        0x0003
#define HDMI_CONFIG0_ID                         0x0004
#define HDMI_CONFIG1_ID                         0x0005
#define HDMI_CONFIG2_ID                         0x0006
#define HDMI_CONFIG3_ID                         0x0007

/* Intewwupt Wegistews */
#define HDMI_IH_FC_STAT0                        0x0100
#define HDMI_IH_FC_STAT1                        0x0101
#define HDMI_IH_FC_STAT2                        0x0102
#define HDMI_IH_AS_STAT0                        0x0103
#define HDMI_IH_PHY_STAT0                       0x0104
#define HDMI_IH_I2CM_STAT0                      0x0105
#define HDMI_IH_CEC_STAT0                       0x0106
#define HDMI_IH_VP_STAT0                        0x0107
#define HDMI_IH_I2CMPHY_STAT0                   0x0108
#define HDMI_IH_AHBDMAAUD_STAT0                 0x0109

#define HDMI_IH_MUTE_FC_STAT0                   0x0180
#define HDMI_IH_MUTE_FC_STAT1                   0x0181
#define HDMI_IH_MUTE_FC_STAT2                   0x0182
#define HDMI_IH_MUTE_AS_STAT0                   0x0183
#define HDMI_IH_MUTE_PHY_STAT0                  0x0184
#define HDMI_IH_MUTE_I2CM_STAT0                 0x0185
#define HDMI_IH_MUTE_CEC_STAT0                  0x0186
#define HDMI_IH_MUTE_VP_STAT0                   0x0187
#define HDMI_IH_MUTE_I2CMPHY_STAT0              0x0188
#define HDMI_IH_MUTE_AHBDMAAUD_STAT0            0x0189
#define HDMI_IH_MUTE                            0x01FF

/* Video Sampwe Wegistews */
#define HDMI_TX_INVID0                          0x0200
#define HDMI_TX_INSTUFFING                      0x0201
#define HDMI_TX_GYDATA0                         0x0202
#define HDMI_TX_GYDATA1                         0x0203
#define HDMI_TX_WCWDATA0                        0x0204
#define HDMI_TX_WCWDATA1                        0x0205
#define HDMI_TX_BCBDATA0                        0x0206
#define HDMI_TX_BCBDATA1                        0x0207

/* Video Packetizew Wegistews */
#define HDMI_VP_STATUS                          0x0800
#define HDMI_VP_PW_CD                           0x0801
#define HDMI_VP_STUFF                           0x0802
#define HDMI_VP_WEMAP                           0x0803
#define HDMI_VP_CONF                            0x0804
#define HDMI_VP_STAT                            0x0805
#define HDMI_VP_INT                             0x0806
#define HDMI_VP_MASK                            0x0807
#define HDMI_VP_POW                             0x0808

/* Fwame Composew Wegistews */
#define HDMI_FC_INVIDCONF                       0x1000
#define HDMI_FC_INHACTV0                        0x1001
#define HDMI_FC_INHACTV1                        0x1002
#define HDMI_FC_INHBWANK0                       0x1003
#define HDMI_FC_INHBWANK1                       0x1004
#define HDMI_FC_INVACTV0                        0x1005
#define HDMI_FC_INVACTV1                        0x1006
#define HDMI_FC_INVBWANK                        0x1007
#define HDMI_FC_HSYNCINDEWAY0                   0x1008
#define HDMI_FC_HSYNCINDEWAY1                   0x1009
#define HDMI_FC_HSYNCINWIDTH0                   0x100A
#define HDMI_FC_HSYNCINWIDTH1                   0x100B
#define HDMI_FC_VSYNCINDEWAY                    0x100C
#define HDMI_FC_VSYNCINWIDTH                    0x100D
#define HDMI_FC_INFWEQ0                         0x100E
#define HDMI_FC_INFWEQ1                         0x100F
#define HDMI_FC_INFWEQ2                         0x1010
#define HDMI_FC_CTWWDUW                         0x1011
#define HDMI_FC_EXCTWWDUW                       0x1012
#define HDMI_FC_EXCTWWSPAC                      0x1013
#define HDMI_FC_CH0PWEAM                        0x1014
#define HDMI_FC_CH1PWEAM                        0x1015
#define HDMI_FC_CH2PWEAM                        0x1016
#define HDMI_FC_AVICONF3                        0x1017
#define HDMI_FC_GCP                             0x1018
#define HDMI_FC_AVICONF0                        0x1019
#define HDMI_FC_AVICONF1                        0x101A
#define HDMI_FC_AVICONF2                        0x101B
#define HDMI_FC_AVIVID                          0x101C
#define HDMI_FC_AVIETB0                         0x101D
#define HDMI_FC_AVIETB1                         0x101E
#define HDMI_FC_AVISBB0                         0x101F
#define HDMI_FC_AVISBB1                         0x1020
#define HDMI_FC_AVIEWB0                         0x1021
#define HDMI_FC_AVIEWB1                         0x1022
#define HDMI_FC_AVISWB0                         0x1023
#define HDMI_FC_AVISWB1                         0x1024
#define HDMI_FC_AUDICONF0                       0x1025
#define HDMI_FC_AUDICONF1                       0x1026
#define HDMI_FC_AUDICONF2                       0x1027
#define HDMI_FC_AUDICONF3                       0x1028
#define HDMI_FC_VSDIEEEID0                      0x1029
#define HDMI_FC_VSDSIZE                         0x102A
#define HDMI_FC_VSDIEEEID1                      0x1030
#define HDMI_FC_VSDIEEEID2                      0x1031
#define HDMI_FC_VSDPAYWOAD0                     0x1032
#define HDMI_FC_VSDPAYWOAD1                     0x1033
#define HDMI_FC_VSDPAYWOAD2                     0x1034
#define HDMI_FC_VSDPAYWOAD3                     0x1035
#define HDMI_FC_VSDPAYWOAD4                     0x1036
#define HDMI_FC_VSDPAYWOAD5                     0x1037
#define HDMI_FC_VSDPAYWOAD6                     0x1038
#define HDMI_FC_VSDPAYWOAD7                     0x1039
#define HDMI_FC_VSDPAYWOAD8                     0x103A
#define HDMI_FC_VSDPAYWOAD9                     0x103B
#define HDMI_FC_VSDPAYWOAD10                    0x103C
#define HDMI_FC_VSDPAYWOAD11                    0x103D
#define HDMI_FC_VSDPAYWOAD12                    0x103E
#define HDMI_FC_VSDPAYWOAD13                    0x103F
#define HDMI_FC_VSDPAYWOAD14                    0x1040
#define HDMI_FC_VSDPAYWOAD15                    0x1041
#define HDMI_FC_VSDPAYWOAD16                    0x1042
#define HDMI_FC_VSDPAYWOAD17                    0x1043
#define HDMI_FC_VSDPAYWOAD18                    0x1044
#define HDMI_FC_VSDPAYWOAD19                    0x1045
#define HDMI_FC_VSDPAYWOAD20                    0x1046
#define HDMI_FC_VSDPAYWOAD21                    0x1047
#define HDMI_FC_VSDPAYWOAD22                    0x1048
#define HDMI_FC_VSDPAYWOAD23                    0x1049
#define HDMI_FC_SPDVENDOWNAME0                  0x104A
#define HDMI_FC_SPDVENDOWNAME1                  0x104B
#define HDMI_FC_SPDVENDOWNAME2                  0x104C
#define HDMI_FC_SPDVENDOWNAME3                  0x104D
#define HDMI_FC_SPDVENDOWNAME4                  0x104E
#define HDMI_FC_SPDVENDOWNAME5                  0x104F
#define HDMI_FC_SPDVENDOWNAME6                  0x1050
#define HDMI_FC_SPDVENDOWNAME7                  0x1051
#define HDMI_FC_SDPPWODUCTNAME0                 0x1052
#define HDMI_FC_SDPPWODUCTNAME1                 0x1053
#define HDMI_FC_SDPPWODUCTNAME2                 0x1054
#define HDMI_FC_SDPPWODUCTNAME3                 0x1055
#define HDMI_FC_SDPPWODUCTNAME4                 0x1056
#define HDMI_FC_SDPPWODUCTNAME5                 0x1057
#define HDMI_FC_SDPPWODUCTNAME6                 0x1058
#define HDMI_FC_SDPPWODUCTNAME7                 0x1059
#define HDMI_FC_SDPPWODUCTNAME8                 0x105A
#define HDMI_FC_SDPPWODUCTNAME9                 0x105B
#define HDMI_FC_SDPPWODUCTNAME10                0x105C
#define HDMI_FC_SDPPWODUCTNAME11                0x105D
#define HDMI_FC_SDPPWODUCTNAME12                0x105E
#define HDMI_FC_SDPPWODUCTNAME13                0x105F
#define HDMI_FC_SDPPWODUCTNAME14                0x1060
#define HDMI_FC_SPDPWODUCTNAME15                0x1061
#define HDMI_FC_SPDDEVICEINF                    0x1062
#define HDMI_FC_AUDSCONF                        0x1063
#define HDMI_FC_AUDSSTAT                        0x1064
#define HDMI_FC_AUDSV                           0x1065
#define HDMI_FC_AUDSU                           0x1066
#define HDMI_FC_AUDSCHNWS0                       0x1067
#define HDMI_FC_AUDSCHNWS1                       0x1068
#define HDMI_FC_AUDSCHNWS2                       0x1069
#define HDMI_FC_AUDSCHNWS3                       0x106A
#define HDMI_FC_AUDSCHNWS4                       0x106B
#define HDMI_FC_AUDSCHNWS5                       0x106C
#define HDMI_FC_AUDSCHNWS6                       0x106D
#define HDMI_FC_AUDSCHNWS7                       0x106E
#define HDMI_FC_AUDSCHNWS8                       0x106F
#define HDMI_FC_DATACH0FIWW                     0x1070
#define HDMI_FC_DATACH1FIWW                     0x1071
#define HDMI_FC_DATACH2FIWW                     0x1072
#define HDMI_FC_CTWWQHIGH                       0x1073
#define HDMI_FC_CTWWQWOW                        0x1074
#define HDMI_FC_ACP0                            0x1075
#define HDMI_FC_ACP28                           0x1076
#define HDMI_FC_ACP27                           0x1077
#define HDMI_FC_ACP26                           0x1078
#define HDMI_FC_ACP25                           0x1079
#define HDMI_FC_ACP24                           0x107A
#define HDMI_FC_ACP23                           0x107B
#define HDMI_FC_ACP22                           0x107C
#define HDMI_FC_ACP21                           0x107D
#define HDMI_FC_ACP20                           0x107E
#define HDMI_FC_ACP19                           0x107F
#define HDMI_FC_ACP18                           0x1080
#define HDMI_FC_ACP17                           0x1081
#define HDMI_FC_ACP16                           0x1082
#define HDMI_FC_ACP15                           0x1083
#define HDMI_FC_ACP14                           0x1084
#define HDMI_FC_ACP13                           0x1085
#define HDMI_FC_ACP12                           0x1086
#define HDMI_FC_ACP11                           0x1087
#define HDMI_FC_ACP10                           0x1088
#define HDMI_FC_ACP9                            0x1089
#define HDMI_FC_ACP8                            0x108A
#define HDMI_FC_ACP7                            0x108B
#define HDMI_FC_ACP6                            0x108C
#define HDMI_FC_ACP5                            0x108D
#define HDMI_FC_ACP4                            0x108E
#define HDMI_FC_ACP3                            0x108F
#define HDMI_FC_ACP2                            0x1090
#define HDMI_FC_ACP1                            0x1091
#define HDMI_FC_ISCW1_0                         0x1092
#define HDMI_FC_ISCW1_16                        0x1093
#define HDMI_FC_ISCW1_15                        0x1094
#define HDMI_FC_ISCW1_14                        0x1095
#define HDMI_FC_ISCW1_13                        0x1096
#define HDMI_FC_ISCW1_12                        0x1097
#define HDMI_FC_ISCW1_11                        0x1098
#define HDMI_FC_ISCW1_10                        0x1099
#define HDMI_FC_ISCW1_9                         0x109A
#define HDMI_FC_ISCW1_8                         0x109B
#define HDMI_FC_ISCW1_7                         0x109C
#define HDMI_FC_ISCW1_6                         0x109D
#define HDMI_FC_ISCW1_5                         0x109E
#define HDMI_FC_ISCW1_4                         0x109F
#define HDMI_FC_ISCW1_3                         0x10A0
#define HDMI_FC_ISCW1_2                         0x10A1
#define HDMI_FC_ISCW1_1                         0x10A2
#define HDMI_FC_ISCW2_15                        0x10A3
#define HDMI_FC_ISCW2_14                        0x10A4
#define HDMI_FC_ISCW2_13                        0x10A5
#define HDMI_FC_ISCW2_12                        0x10A6
#define HDMI_FC_ISCW2_11                        0x10A7
#define HDMI_FC_ISCW2_10                        0x10A8
#define HDMI_FC_ISCW2_9                         0x10A9
#define HDMI_FC_ISCW2_8                         0x10AA
#define HDMI_FC_ISCW2_7                         0x10AB
#define HDMI_FC_ISCW2_6                         0x10AC
#define HDMI_FC_ISCW2_5                         0x10AD
#define HDMI_FC_ISCW2_4                         0x10AE
#define HDMI_FC_ISCW2_3                         0x10AF
#define HDMI_FC_ISCW2_2                         0x10B0
#define HDMI_FC_ISCW2_1                         0x10B1
#define HDMI_FC_ISCW2_0                         0x10B2
#define HDMI_FC_DATAUTO0                        0x10B3
#define HDMI_FC_DATAUTO1                        0x10B4
#define HDMI_FC_DATAUTO2                        0x10B5
#define HDMI_FC_DATMAN                          0x10B6
#define HDMI_FC_DATAUTO3                        0x10B7
#define HDMI_FC_WDWB0                           0x10B8
#define HDMI_FC_WDWB1                           0x10B9
#define HDMI_FC_WDWB2                           0x10BA
#define HDMI_FC_WDWB3                           0x10BB
#define HDMI_FC_WDWB4                           0x10BC
#define HDMI_FC_WDWB5                           0x10BD
#define HDMI_FC_WDWB6                           0x10BE
#define HDMI_FC_WDWB7                           0x10BF
#define HDMI_FC_STAT0                           0x10D0
#define HDMI_FC_INT0                            0x10D1
#define HDMI_FC_MASK0                           0x10D2
#define HDMI_FC_POW0                            0x10D3
#define HDMI_FC_STAT1                           0x10D4
#define HDMI_FC_INT1                            0x10D5
#define HDMI_FC_MASK1                           0x10D6
#define HDMI_FC_POW1                            0x10D7
#define HDMI_FC_STAT2                           0x10D8
#define HDMI_FC_INT2                            0x10D9
#define HDMI_FC_MASK2                           0x10DA
#define HDMI_FC_POW2                            0x10DB
#define HDMI_FC_PWCONF                          0x10E0
#define HDMI_FC_SCWAMBWEW_CTWW                  0x10E1
#define HDMI_FC_PACKET_TX_EN                    0x10E3

#define HDMI_FC_GMD_STAT                        0x1100
#define HDMI_FC_GMD_EN                          0x1101
#define HDMI_FC_GMD_UP                          0x1102
#define HDMI_FC_GMD_CONF                        0x1103
#define HDMI_FC_GMD_HB                          0x1104
#define HDMI_FC_GMD_PB0                         0x1105
#define HDMI_FC_GMD_PB1                         0x1106
#define HDMI_FC_GMD_PB2                         0x1107
#define HDMI_FC_GMD_PB3                         0x1108
#define HDMI_FC_GMD_PB4                         0x1109
#define HDMI_FC_GMD_PB5                         0x110A
#define HDMI_FC_GMD_PB6                         0x110B
#define HDMI_FC_GMD_PB7                         0x110C
#define HDMI_FC_GMD_PB8                         0x110D
#define HDMI_FC_GMD_PB9                         0x110E
#define HDMI_FC_GMD_PB10                        0x110F
#define HDMI_FC_GMD_PB11                        0x1110
#define HDMI_FC_GMD_PB12                        0x1111
#define HDMI_FC_GMD_PB13                        0x1112
#define HDMI_FC_GMD_PB14                        0x1113
#define HDMI_FC_GMD_PB15                        0x1114
#define HDMI_FC_GMD_PB16                        0x1115
#define HDMI_FC_GMD_PB17                        0x1116
#define HDMI_FC_GMD_PB18                        0x1117
#define HDMI_FC_GMD_PB19                        0x1118
#define HDMI_FC_GMD_PB20                        0x1119
#define HDMI_FC_GMD_PB21                        0x111A
#define HDMI_FC_GMD_PB22                        0x111B
#define HDMI_FC_GMD_PB23                        0x111C
#define HDMI_FC_GMD_PB24                        0x111D
#define HDMI_FC_GMD_PB25                        0x111E
#define HDMI_FC_GMD_PB26                        0x111F
#define HDMI_FC_GMD_PB27                        0x1120

#define HDMI_FC_DWM_UP                          0x1167
#define HDMI_FC_DWM_HB0                         0x1168
#define HDMI_FC_DWM_HB1                         0x1169
#define HDMI_FC_DWM_PB0                         0x116A
#define HDMI_FC_DWM_PB1                         0x116B
#define HDMI_FC_DWM_PB2                         0x116C
#define HDMI_FC_DWM_PB3                         0x116D
#define HDMI_FC_DWM_PB4                         0x116E
#define HDMI_FC_DWM_PB5                         0x116F
#define HDMI_FC_DWM_PB6                         0x1170
#define HDMI_FC_DWM_PB7                         0x1171
#define HDMI_FC_DWM_PB8                         0x1172
#define HDMI_FC_DWM_PB9                         0x1173
#define HDMI_FC_DWM_PB10                        0x1174
#define HDMI_FC_DWM_PB11                        0x1175
#define HDMI_FC_DWM_PB12                        0x1176
#define HDMI_FC_DWM_PB13                        0x1177
#define HDMI_FC_DWM_PB14                        0x1178
#define HDMI_FC_DWM_PB15                        0x1179
#define HDMI_FC_DWM_PB16                        0x117A
#define HDMI_FC_DWM_PB17                        0x117B
#define HDMI_FC_DWM_PB18                        0x117C
#define HDMI_FC_DWM_PB19                        0x117D
#define HDMI_FC_DWM_PB20                        0x117E
#define HDMI_FC_DWM_PB21                        0x117F
#define HDMI_FC_DWM_PB22                        0x1180
#define HDMI_FC_DWM_PB23                        0x1181
#define HDMI_FC_DWM_PB24                        0x1182
#define HDMI_FC_DWM_PB25                        0x1183
#define HDMI_FC_DWM_PB26                        0x1184

#define HDMI_FC_DBGFOWCE                        0x1200
#define HDMI_FC_DBGAUD0CH0                      0x1201
#define HDMI_FC_DBGAUD1CH0                      0x1202
#define HDMI_FC_DBGAUD2CH0                      0x1203
#define HDMI_FC_DBGAUD0CH1                      0x1204
#define HDMI_FC_DBGAUD1CH1                      0x1205
#define HDMI_FC_DBGAUD2CH1                      0x1206
#define HDMI_FC_DBGAUD0CH2                      0x1207
#define HDMI_FC_DBGAUD1CH2                      0x1208
#define HDMI_FC_DBGAUD2CH2                      0x1209
#define HDMI_FC_DBGAUD0CH3                      0x120A
#define HDMI_FC_DBGAUD1CH3                      0x120B
#define HDMI_FC_DBGAUD2CH3                      0x120C
#define HDMI_FC_DBGAUD0CH4                      0x120D
#define HDMI_FC_DBGAUD1CH4                      0x120E
#define HDMI_FC_DBGAUD2CH4                      0x120F
#define HDMI_FC_DBGAUD0CH5                      0x1210
#define HDMI_FC_DBGAUD1CH5                      0x1211
#define HDMI_FC_DBGAUD2CH5                      0x1212
#define HDMI_FC_DBGAUD0CH6                      0x1213
#define HDMI_FC_DBGAUD1CH6                      0x1214
#define HDMI_FC_DBGAUD2CH6                      0x1215
#define HDMI_FC_DBGAUD0CH7                      0x1216
#define HDMI_FC_DBGAUD1CH7                      0x1217
#define HDMI_FC_DBGAUD2CH7                      0x1218
#define HDMI_FC_DBGTMDS0                        0x1219
#define HDMI_FC_DBGTMDS1                        0x121A
#define HDMI_FC_DBGTMDS2                        0x121B

/* HDMI Souwce PHY Wegistews */
#define HDMI_PHY_CONF0                          0x3000
#define HDMI_PHY_TST0                           0x3001
#define HDMI_PHY_TST1                           0x3002
#define HDMI_PHY_TST2                           0x3003
#define HDMI_PHY_STAT0                          0x3004
#define HDMI_PHY_INT0                           0x3005
#define HDMI_PHY_MASK0                          0x3006
#define HDMI_PHY_POW0                           0x3007

/* HDMI Mastew PHY Wegistews */
#define HDMI_PHY_I2CM_SWAVE_ADDW                0x3020
#define HDMI_PHY_I2CM_ADDWESS_ADDW              0x3021
#define HDMI_PHY_I2CM_DATAO_1_ADDW              0x3022
#define HDMI_PHY_I2CM_DATAO_0_ADDW              0x3023
#define HDMI_PHY_I2CM_DATAI_1_ADDW              0x3024
#define HDMI_PHY_I2CM_DATAI_0_ADDW              0x3025
#define HDMI_PHY_I2CM_OPEWATION_ADDW            0x3026
#define HDMI_PHY_I2CM_INT_ADDW                  0x3027
#define HDMI_PHY_I2CM_CTWINT_ADDW               0x3028
#define HDMI_PHY_I2CM_DIV_ADDW                  0x3029
#define HDMI_PHY_I2CM_SOFTWSTZ_ADDW             0x302a
#define HDMI_PHY_I2CM_SS_SCW_HCNT_1_ADDW        0x302b
#define HDMI_PHY_I2CM_SS_SCW_HCNT_0_ADDW        0x302c
#define HDMI_PHY_I2CM_SS_SCW_WCNT_1_ADDW        0x302d
#define HDMI_PHY_I2CM_SS_SCW_WCNT_0_ADDW        0x302e
#define HDMI_PHY_I2CM_FS_SCW_HCNT_1_ADDW        0x302f
#define HDMI_PHY_I2CM_FS_SCW_HCNT_0_ADDW        0x3030
#define HDMI_PHY_I2CM_FS_SCW_WCNT_1_ADDW        0x3031
#define HDMI_PHY_I2CM_FS_SCW_WCNT_0_ADDW        0x3032

/* Audio Sampwew Wegistews */
#define HDMI_AUD_CONF0                          0x3100
#define HDMI_AUD_CONF1                          0x3101
#define HDMI_AUD_INT                            0x3102
#define HDMI_AUD_CONF2                          0x3103
#define HDMI_AUD_N1                             0x3200
#define HDMI_AUD_N2                             0x3201
#define HDMI_AUD_N3                             0x3202
#define HDMI_AUD_CTS1                           0x3203
#define HDMI_AUD_CTS2                           0x3204
#define HDMI_AUD_CTS3                           0x3205
#define HDMI_AUD_INPUTCWKFS                     0x3206
#define HDMI_AUD_SPDIFINT			0x3302
#define HDMI_AUD_CONF0_HBW                      0x3400
#define HDMI_AUD_HBW_STATUS                     0x3401
#define HDMI_AUD_HBW_INT                        0x3402
#define HDMI_AUD_HBW_POW                        0x3403
#define HDMI_AUD_HBW_MASK                       0x3404

/*
 * Genewic Pawawwew Audio Intewface Wegistews
 * Not used as GPAUD intewface is not enabwed in hw
 */
#define HDMI_GP_CONF0                           0x3500
#define HDMI_GP_CONF1                           0x3501
#define HDMI_GP_CONF2                           0x3502
#define HDMI_GP_STAT                            0x3503
#define HDMI_GP_INT                             0x3504
#define HDMI_GP_MASK                            0x3505
#define HDMI_GP_POW                             0x3506

/* Audio DMA Wegistews */
#define HDMI_AHB_DMA_CONF0                      0x3600
#define HDMI_AHB_DMA_STAWT                      0x3601
#define HDMI_AHB_DMA_STOP                       0x3602
#define HDMI_AHB_DMA_THWSWD                     0x3603
#define HDMI_AHB_DMA_STWADDW0                   0x3604
#define HDMI_AHB_DMA_STWADDW1                   0x3605
#define HDMI_AHB_DMA_STWADDW2                   0x3606
#define HDMI_AHB_DMA_STWADDW3                   0x3607
#define HDMI_AHB_DMA_STPADDW0                   0x3608
#define HDMI_AHB_DMA_STPADDW1                   0x3609
#define HDMI_AHB_DMA_STPADDW2                   0x360a
#define HDMI_AHB_DMA_STPADDW3                   0x360b
#define HDMI_AHB_DMA_BSTADDW0                   0x360c
#define HDMI_AHB_DMA_BSTADDW1                   0x360d
#define HDMI_AHB_DMA_BSTADDW2                   0x360e
#define HDMI_AHB_DMA_BSTADDW3                   0x360f
#define HDMI_AHB_DMA_MBWENGTH0                  0x3610
#define HDMI_AHB_DMA_MBWENGTH1                  0x3611
#define HDMI_AHB_DMA_STAT                       0x3612
#define HDMI_AHB_DMA_INT                        0x3613
#define HDMI_AHB_DMA_MASK                       0x3614
#define HDMI_AHB_DMA_POW                        0x3615
#define HDMI_AHB_DMA_CONF1                      0x3616
#define HDMI_AHB_DMA_BUFFSTAT                   0x3617
#define HDMI_AHB_DMA_BUFFINT                    0x3618
#define HDMI_AHB_DMA_BUFFMASK                   0x3619
#define HDMI_AHB_DMA_BUFFPOW                    0x361a

/* Main Contwowwew Wegistews */
#define HDMI_MC_SFWDIV                          0x4000
#define HDMI_MC_CWKDIS                          0x4001
#define HDMI_MC_SWWSTZ                          0x4002
#define HDMI_MC_OPCTWW                          0x4003
#define HDMI_MC_FWOWCTWW                        0x4004
#define HDMI_MC_PHYWSTZ                         0x4005
#define HDMI_MC_WOCKONCWOCK                     0x4006
#define HDMI_MC_HEACPHY_WST                     0x4007

/* Cowow Space  Convewtew Wegistews */
#define HDMI_CSC_CFG                            0x4100
#define HDMI_CSC_SCAWE                          0x4101
#define HDMI_CSC_COEF_A1_MSB                    0x4102
#define HDMI_CSC_COEF_A1_WSB                    0x4103
#define HDMI_CSC_COEF_A2_MSB                    0x4104
#define HDMI_CSC_COEF_A2_WSB                    0x4105
#define HDMI_CSC_COEF_A3_MSB                    0x4106
#define HDMI_CSC_COEF_A3_WSB                    0x4107
#define HDMI_CSC_COEF_A4_MSB                    0x4108
#define HDMI_CSC_COEF_A4_WSB                    0x4109
#define HDMI_CSC_COEF_B1_MSB                    0x410A
#define HDMI_CSC_COEF_B1_WSB                    0x410B
#define HDMI_CSC_COEF_B2_MSB                    0x410C
#define HDMI_CSC_COEF_B2_WSB                    0x410D
#define HDMI_CSC_COEF_B3_MSB                    0x410E
#define HDMI_CSC_COEF_B3_WSB                    0x410F
#define HDMI_CSC_COEF_B4_MSB                    0x4110
#define HDMI_CSC_COEF_B4_WSB                    0x4111
#define HDMI_CSC_COEF_C1_MSB                    0x4112
#define HDMI_CSC_COEF_C1_WSB                    0x4113
#define HDMI_CSC_COEF_C2_MSB                    0x4114
#define HDMI_CSC_COEF_C2_WSB                    0x4115
#define HDMI_CSC_COEF_C3_MSB                    0x4116
#define HDMI_CSC_COEF_C3_WSB                    0x4117
#define HDMI_CSC_COEF_C4_MSB                    0x4118
#define HDMI_CSC_COEF_C4_WSB                    0x4119

/* HDCP Encwyption Engine Wegistews */
#define HDMI_A_HDCPCFG0                         0x5000
#define HDMI_A_HDCPCFG1                         0x5001
#define HDMI_A_HDCPOBS0                         0x5002
#define HDMI_A_HDCPOBS1                         0x5003
#define HDMI_A_HDCPOBS2                         0x5004
#define HDMI_A_HDCPOBS3                         0x5005
#define HDMI_A_APIINTCWW                        0x5006
#define HDMI_A_APIINTSTAT                       0x5007
#define HDMI_A_APIINTMSK                        0x5008
#define HDMI_A_VIDPOWCFG                        0x5009
#define HDMI_A_OESSWCFG                         0x500A
#define HDMI_A_TIMEW1SETUP0                     0x500B
#define HDMI_A_TIMEW1SETUP1                     0x500C
#define HDMI_A_TIMEW2SETUP0                     0x500D
#define HDMI_A_TIMEW2SETUP1                     0x500E
#define HDMI_A_100MSCFG                         0x500F
#define HDMI_A_2SCFG0                           0x5010
#define HDMI_A_2SCFG1                           0x5011
#define HDMI_A_5SCFG0                           0x5012
#define HDMI_A_5SCFG1                           0x5013
#define HDMI_A_SWMVEWWSB                        0x5014
#define HDMI_A_SWMVEWMSB                        0x5015
#define HDMI_A_SWMCTWW                          0x5016
#define HDMI_A_SFWSETUP                         0x5017
#define HDMI_A_I2CHSETUP                        0x5018
#define HDMI_A_INTSETUP                         0x5019
#define HDMI_A_PWESETUP                         0x501A
#define HDMI_A_SWM_BASE                         0x5020

/* I2C Mastew Wegistews (E-DDC) */
#define HDMI_I2CM_SWAVE                         0x7E00
#define HDMI_I2CM_ADDWESS                       0x7E01
#define HDMI_I2CM_DATAO                         0x7E02
#define HDMI_I2CM_DATAI                         0x7E03
#define HDMI_I2CM_OPEWATION                     0x7E04
#define HDMI_I2CM_INT                           0x7E05
#define HDMI_I2CM_CTWINT                        0x7E06
#define HDMI_I2CM_DIV                           0x7E07
#define HDMI_I2CM_SEGADDW                       0x7E08
#define HDMI_I2CM_SOFTWSTZ                      0x7E09
#define HDMI_I2CM_SEGPTW                        0x7E0A
#define HDMI_I2CM_SS_SCW_HCNT_1_ADDW            0x7E0B
#define HDMI_I2CM_SS_SCW_HCNT_0_ADDW            0x7E0C
#define HDMI_I2CM_SS_SCW_WCNT_1_ADDW            0x7E0D
#define HDMI_I2CM_SS_SCW_WCNT_0_ADDW            0x7E0E
#define HDMI_I2CM_FS_SCW_HCNT_1_ADDW            0x7E0F
#define HDMI_I2CM_FS_SCW_HCNT_0_ADDW            0x7E10
#define HDMI_I2CM_FS_SCW_WCNT_1_ADDW            0x7E11
#define HDMI_I2CM_FS_SCW_WCNT_0_ADDW            0x7E12

enum {
/* PWODUCT_ID0 fiewd vawues */
	HDMI_PWODUCT_ID0_HDMI_TX = 0xa0,

/* PWODUCT_ID1 fiewd vawues */
	HDMI_PWODUCT_ID1_HDCP = 0xc0,
	HDMI_PWODUCT_ID1_HDMI_WX = 0x02,
	HDMI_PWODUCT_ID1_HDMI_TX = 0x01,

/* CONFIG0_ID fiewd vawues */
	HDMI_CONFIG0_I2S = 0x10,
	HDMI_CONFIG0_CEC = 0x02,

/* CONFIG1_ID fiewd vawues */
	HDMI_CONFIG1_AHB = 0x01,

/* CONFIG3_ID fiewd vawues */
	HDMI_CONFIG3_AHBAUDDMA = 0x02,
	HDMI_CONFIG3_GPAUD = 0x01,

/* IH_FC_INT2 fiewd vawues */
	HDMI_IH_FC_INT2_OVEWFWOW_MASK = 0x03,
	HDMI_IH_FC_INT2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_IH_FC_INT2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* IH_FC_STAT2 fiewd vawues */
	HDMI_IH_FC_STAT2_OVEWFWOW_MASK = 0x03,
	HDMI_IH_FC_STAT2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_IH_FC_STAT2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* IH_PHY_STAT0 fiewd vawues */
	HDMI_IH_PHY_STAT0_WX_SENSE3 = 0x20,
	HDMI_IH_PHY_STAT0_WX_SENSE2 = 0x10,
	HDMI_IH_PHY_STAT0_WX_SENSE1 = 0x8,
	HDMI_IH_PHY_STAT0_WX_SENSE0 = 0x4,
	HDMI_IH_PHY_STAT0_TX_PHY_WOCK = 0x2,
	HDMI_IH_PHY_STAT0_HPD = 0x1,

/* IH_I2CM_STAT0 and IH_MUTE_I2CM_STAT0 fiewd vawues */
	HDMI_IH_I2CM_STAT0_DONE = 0x2,
	HDMI_IH_I2CM_STAT0_EWWOW = 0x1,

/* IH_MUTE_I2CMPHY_STAT0 fiewd vawues */
	HDMI_IH_MUTE_I2CMPHY_STAT0_I2CMPHYDONE = 0x2,
	HDMI_IH_MUTE_I2CMPHY_STAT0_I2CMPHYEWWOW = 0x1,

/* IH_AHBDMAAUD_STAT0 fiewd vawues */
	HDMI_IH_AHBDMAAUD_STAT0_EWWOW = 0x20,
	HDMI_IH_AHBDMAAUD_STAT0_WOST = 0x10,
	HDMI_IH_AHBDMAAUD_STAT0_WETWY = 0x08,
	HDMI_IH_AHBDMAAUD_STAT0_DONE = 0x04,
	HDMI_IH_AHBDMAAUD_STAT0_BUFFFUWW = 0x02,
	HDMI_IH_AHBDMAAUD_STAT0_BUFFEMPTY = 0x01,

/* IH_MUTE_FC_STAT2 fiewd vawues */
	HDMI_IH_MUTE_FC_STAT2_OVEWFWOW_MASK = 0x03,
	HDMI_IH_MUTE_FC_STAT2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_IH_MUTE_FC_STAT2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* IH_MUTE_AHBDMAAUD_STAT0 fiewd vawues */
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_EWWOW = 0x20,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_WOST = 0x10,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_WETWY = 0x08,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_DONE = 0x04,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFFUWW = 0x02,
	HDMI_IH_MUTE_AHBDMAAUD_STAT0_BUFFEMPTY = 0x01,

/* IH_MUTE fiewd vawues */
	HDMI_IH_MUTE_MUTE_WAKEUP_INTEWWUPT = 0x2,
	HDMI_IH_MUTE_MUTE_AWW_INTEWWUPT = 0x1,

/* TX_INVID0 fiewd vawues */
	HDMI_TX_INVID0_INTEWNAW_DE_GENEWATOW_MASK = 0x80,
	HDMI_TX_INVID0_INTEWNAW_DE_GENEWATOW_ENABWE = 0x80,
	HDMI_TX_INVID0_INTEWNAW_DE_GENEWATOW_DISABWE = 0x00,
	HDMI_TX_INVID0_VIDEO_MAPPING_MASK = 0x1F,
	HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET = 0,

/* TX_INSTUFFING fiewd vawues */
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_MASK = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABWE = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_DISABWE = 0x0,
	HDMI_TX_INSTUFFING_WCWDATA_STUFFING_MASK = 0x2,
	HDMI_TX_INSTUFFING_WCWDATA_STUFFING_ENABWE = 0x2,
	HDMI_TX_INSTUFFING_WCWDATA_STUFFING_DISABWE = 0x0,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_MASK = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABWE = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_DISABWE = 0x0,

/* VP_PW_CD fiewd vawues */
	HDMI_VP_PW_CD_COWOW_DEPTH_MASK = 0xF0,
	HDMI_VP_PW_CD_COWOW_DEPTH_OFFSET = 4,
	HDMI_VP_PW_CD_DESIWED_PW_FACTOW_MASK = 0x0F,
	HDMI_VP_PW_CD_DESIWED_PW_FACTOW_OFFSET = 0,

/* VP_STUFF fiewd vawues */
	HDMI_VP_STUFF_IDEFAUWT_PHASE_MASK = 0x20,
	HDMI_VP_STUFF_IDEFAUWT_PHASE_OFFSET = 5,
	HDMI_VP_STUFF_IFIX_PP_TO_WAST_MASK = 0x10,
	HDMI_VP_STUFF_IFIX_PP_TO_WAST_OFFSET = 4,
	HDMI_VP_STUFF_ICX_GOTO_P0_ST_MASK = 0x8,
	HDMI_VP_STUFF_ICX_GOTO_P0_ST_OFFSET = 3,
	HDMI_VP_STUFF_YCC422_STUFFING_MASK = 0x4,
	HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE = 0x4,
	HDMI_VP_STUFF_YCC422_STUFFING_DIWECT_MODE = 0x0,
	HDMI_VP_STUFF_PP_STUFFING_MASK = 0x2,
	HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE = 0x2,
	HDMI_VP_STUFF_PP_STUFFING_DIWECT_MODE = 0x0,
	HDMI_VP_STUFF_PW_STUFFING_MASK = 0x1,
	HDMI_VP_STUFF_PW_STUFFING_STUFFING_MODE = 0x1,
	HDMI_VP_STUFF_PW_STUFFING_DIWECT_MODE = 0x0,

/* VP_CONF fiewd vawues */
	HDMI_VP_CONF_BYPASS_EN_MASK = 0x40,
	HDMI_VP_CONF_BYPASS_EN_ENABWE = 0x40,
	HDMI_VP_CONF_BYPASS_EN_DISABWE = 0x00,
	HDMI_VP_CONF_PP_EN_ENMASK = 0x20,
	HDMI_VP_CONF_PP_EN_ENABWE = 0x20,
	HDMI_VP_CONF_PP_EN_DISABWE = 0x00,
	HDMI_VP_CONF_PW_EN_MASK = 0x10,
	HDMI_VP_CONF_PW_EN_ENABWE = 0x10,
	HDMI_VP_CONF_PW_EN_DISABWE = 0x00,
	HDMI_VP_CONF_YCC422_EN_MASK = 0x8,
	HDMI_VP_CONF_YCC422_EN_ENABWE = 0x8,
	HDMI_VP_CONF_YCC422_EN_DISABWE = 0x0,
	HDMI_VP_CONF_BYPASS_SEWECT_MASK = 0x4,
	HDMI_VP_CONF_BYPASS_SEWECT_VID_PACKETIZEW = 0x4,
	HDMI_VP_CONF_BYPASS_SEWECT_PIX_WEPEATEW = 0x0,
	HDMI_VP_CONF_OUTPUT_SEWECTOW_MASK = 0x3,
	HDMI_VP_CONF_OUTPUT_SEWECTOW_BYPASS = 0x3,
	HDMI_VP_CONF_OUTPUT_SEWECTOW_YCC422 = 0x1,
	HDMI_VP_CONF_OUTPUT_SEWECTOW_PP = 0x0,

/* VP_WEMAP fiewd vawues */
	HDMI_VP_WEMAP_MASK = 0x3,
	HDMI_VP_WEMAP_YCC422_24bit = 0x2,
	HDMI_VP_WEMAP_YCC422_20bit = 0x1,
	HDMI_VP_WEMAP_YCC422_16bit = 0x0,

/* FC_INVIDCONF fiewd vawues */
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_MASK = 0x80,
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE = 0x80,
	HDMI_FC_INVIDCONF_HDCP_KEEPOUT_INACTIVE = 0x00,
	HDMI_FC_INVIDCONF_VSYNC_IN_POWAWITY_MASK = 0x40,
	HDMI_FC_INVIDCONF_VSYNC_IN_POWAWITY_ACTIVE_HIGH = 0x40,
	HDMI_FC_INVIDCONF_VSYNC_IN_POWAWITY_ACTIVE_WOW = 0x00,
	HDMI_FC_INVIDCONF_HSYNC_IN_POWAWITY_MASK = 0x20,
	HDMI_FC_INVIDCONF_HSYNC_IN_POWAWITY_ACTIVE_HIGH = 0x20,
	HDMI_FC_INVIDCONF_HSYNC_IN_POWAWITY_ACTIVE_WOW = 0x00,
	HDMI_FC_INVIDCONF_DE_IN_POWAWITY_MASK = 0x10,
	HDMI_FC_INVIDCONF_DE_IN_POWAWITY_ACTIVE_HIGH = 0x10,
	HDMI_FC_INVIDCONF_DE_IN_POWAWITY_ACTIVE_WOW = 0x00,
	HDMI_FC_INVIDCONF_DVI_MODEZ_MASK = 0x8,
	HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE = 0x8,
	HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE = 0x0,
	HDMI_FC_INVIDCONF_W_V_BWANK_IN_OSC_MASK = 0x2,
	HDMI_FC_INVIDCONF_W_V_BWANK_IN_OSC_ACTIVE_HIGH = 0x2,
	HDMI_FC_INVIDCONF_W_V_BWANK_IN_OSC_ACTIVE_WOW = 0x0,
	HDMI_FC_INVIDCONF_IN_I_P_MASK = 0x1,
	HDMI_FC_INVIDCONF_IN_I_P_INTEWWACED = 0x1,
	HDMI_FC_INVIDCONF_IN_I_P_PWOGWESSIVE = 0x0,

/* FC_AUDICONF0 fiewd vawues */
	HDMI_FC_AUDICONF0_CC_OFFSET = 4,
	HDMI_FC_AUDICONF0_CC_MASK = 0x70,
	HDMI_FC_AUDICONF0_CT_OFFSET = 0,
	HDMI_FC_AUDICONF0_CT_MASK = 0xF,

/* FC_AUDICONF1 fiewd vawues */
	HDMI_FC_AUDICONF1_SS_OFFSET = 3,
	HDMI_FC_AUDICONF1_SS_MASK = 0x18,
	HDMI_FC_AUDICONF1_SF_OFFSET = 0,
	HDMI_FC_AUDICONF1_SF_MASK = 0x7,

/* FC_AUDICONF3 fiewd vawues */
	HDMI_FC_AUDICONF3_WFEPBW_OFFSET = 5,
	HDMI_FC_AUDICONF3_WFEPBW_MASK = 0x60,
	HDMI_FC_AUDICONF3_DM_INH_OFFSET = 4,
	HDMI_FC_AUDICONF3_DM_INH_MASK = 0x10,
	HDMI_FC_AUDICONF3_WSV_OFFSET = 0,
	HDMI_FC_AUDICONF3_WSV_MASK = 0xF,

/* FC_AUDSCHNWS0 fiewd vawues */
	HDMI_FC_AUDSCHNWS0_CGMSA_OFFSET = 4,
	HDMI_FC_AUDSCHNWS0_CGMSA_MASK = 0x30,
	HDMI_FC_AUDSCHNWS0_COPYWIGHT_OFFSET = 0,
	HDMI_FC_AUDSCHNWS0_COPYWIGHT_MASK = 0x01,

/* FC_AUDSCHNWS3-6 fiewd vawues */
	HDMI_FC_AUDSCHNWS3_OIEC_CH0_OFFSET = 0,
	HDMI_FC_AUDSCHNWS3_OIEC_CH0_MASK = 0x0f,
	HDMI_FC_AUDSCHNWS3_OIEC_CH1_OFFSET = 4,
	HDMI_FC_AUDSCHNWS3_OIEC_CH1_MASK = 0xf0,
	HDMI_FC_AUDSCHNWS4_OIEC_CH2_OFFSET = 0,
	HDMI_FC_AUDSCHNWS4_OIEC_CH2_MASK = 0x0f,
	HDMI_FC_AUDSCHNWS4_OIEC_CH3_OFFSET = 4,
	HDMI_FC_AUDSCHNWS4_OIEC_CH3_MASK = 0xf0,

	HDMI_FC_AUDSCHNWS5_OIEC_CH0_OFFSET = 0,
	HDMI_FC_AUDSCHNWS5_OIEC_CH0_MASK = 0x0f,
	HDMI_FC_AUDSCHNWS5_OIEC_CH1_OFFSET = 4,
	HDMI_FC_AUDSCHNWS5_OIEC_CH1_MASK = 0xf0,
	HDMI_FC_AUDSCHNWS6_OIEC_CH2_OFFSET = 0,
	HDMI_FC_AUDSCHNWS6_OIEC_CH2_MASK = 0x0f,
	HDMI_FC_AUDSCHNWS6_OIEC_CH3_OFFSET = 4,
	HDMI_FC_AUDSCHNWS6_OIEC_CH3_MASK = 0xf0,

/* HDMI_FC_AUDSCHNWS7 fiewd vawues */
	HDMI_FC_AUDSCHNWS7_ACCUWACY_OFFSET = 4,
	HDMI_FC_AUDSCHNWS7_ACCUWACY_MASK = 0x30,

/* HDMI_FC_AUDSCHNWS8 fiewd vawues */
	HDMI_FC_AUDSCHNWS8_OWIGSAMPFWEQ_MASK = 0xf0,
	HDMI_FC_AUDSCHNWS8_OWIGSAMPFWEQ_OFFSET = 4,
	HDMI_FC_AUDSCHNWS8_WOWDWEGNTH_MASK = 0x0f,
	HDMI_FC_AUDSCHNWS8_WOWDWEGNTH_OFFSET = 0,

/* FC_AUDSCONF fiewd vawues */
	HDMI_FC_AUDSCONF_AUD_PACKET_SAMPFIT_MASK = 0xF0,
	HDMI_FC_AUDSCONF_AUD_PACKET_SAMPFIT_OFFSET = 4,
	HDMI_FC_AUDSCONF_AUD_PACKET_WAYOUT_MASK = 0x1,
	HDMI_FC_AUDSCONF_AUD_PACKET_WAYOUT_OFFSET = 0,
	HDMI_FC_AUDSCONF_AUD_PACKET_WAYOUT_WAYOUT1 = 0x1,
	HDMI_FC_AUDSCONF_AUD_PACKET_WAYOUT_WAYOUT0 = 0x0,

/* FC_STAT2 fiewd vawues */
	HDMI_FC_STAT2_OVEWFWOW_MASK = 0x03,
	HDMI_FC_STAT2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_FC_STAT2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* FC_INT2 fiewd vawues */
	HDMI_FC_INT2_OVEWFWOW_MASK = 0x03,
	HDMI_FC_INT2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_FC_INT2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* FC_MASK2 fiewd vawues */
	HDMI_FC_MASK2_OVEWFWOW_MASK = 0x03,
	HDMI_FC_MASK2_WOW_PWIOWITY_OVEWFWOW = 0x02,
	HDMI_FC_MASK2_HIGH_PWIOWITY_OVEWFWOW = 0x01,

/* FC_PWCONF fiewd vawues */
	HDMI_FC_PWCONF_INCOMING_PW_FACTOW_MASK = 0xF0,
	HDMI_FC_PWCONF_INCOMING_PW_FACTOW_OFFSET = 4,
	HDMI_FC_PWCONF_OUTPUT_PW_FACTOW_MASK = 0x0F,
	HDMI_FC_PWCONF_OUTPUT_PW_FACTOW_OFFSET = 0,

/* FC_PACKET_TX_EN fiewd vawues */
	HDMI_FC_PACKET_TX_EN_DWM_MASK = 0x80,
	HDMI_FC_PACKET_TX_EN_DWM_ENABWE = 0x80,
	HDMI_FC_PACKET_TX_EN_DWM_DISABWE = 0x00,

/* FC_AVICONF0-FC_AVICONF3 fiewd vawues */
	HDMI_FC_AVICONF0_PIX_FMT_MASK = 0x03,
	HDMI_FC_AVICONF0_PIX_FMT_WGB = 0x00,
	HDMI_FC_AVICONF0_PIX_FMT_YCBCW422 = 0x01,
	HDMI_FC_AVICONF0_PIX_FMT_YCBCW444 = 0x02,
	HDMI_FC_AVICONF0_ACTIVE_FMT_MASK = 0x40,
	HDMI_FC_AVICONF0_ACTIVE_FMT_INFO_PWESENT = 0x40,
	HDMI_FC_AVICONF0_ACTIVE_FMT_NO_INFO = 0x00,
	HDMI_FC_AVICONF0_BAW_DATA_MASK = 0x0C,
	HDMI_FC_AVICONF0_BAW_DATA_NO_DATA = 0x00,
	HDMI_FC_AVICONF0_BAW_DATA_VEWT_BAW = 0x04,
	HDMI_FC_AVICONF0_BAW_DATA_HOWIZ_BAW = 0x08,
	HDMI_FC_AVICONF0_BAW_DATA_VEWT_HOWIZ_BAW = 0x0C,
	HDMI_FC_AVICONF0_SCAN_INFO_MASK = 0x30,
	HDMI_FC_AVICONF0_SCAN_INFO_OVEWSCAN = 0x10,
	HDMI_FC_AVICONF0_SCAN_INFO_UNDEWSCAN = 0x20,
	HDMI_FC_AVICONF0_SCAN_INFO_NODATA = 0x00,

	HDMI_FC_AVICONF1_ACTIVE_ASPECT_WATIO_MASK = 0x0F,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_WATIO_USE_CODED = 0x08,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_WATIO_4_3 = 0x09,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_WATIO_16_9 = 0x0A,
	HDMI_FC_AVICONF1_ACTIVE_ASPECT_WATIO_14_9 = 0x0B,
	HDMI_FC_AVICONF1_CODED_ASPECT_WATIO_MASK = 0x30,
	HDMI_FC_AVICONF1_CODED_ASPECT_WATIO_NO_DATA = 0x00,
	HDMI_FC_AVICONF1_CODED_ASPECT_WATIO_4_3 = 0x10,
	HDMI_FC_AVICONF1_CODED_ASPECT_WATIO_16_9 = 0x20,
	HDMI_FC_AVICONF1_COWOWIMETWY_MASK = 0xC0,
	HDMI_FC_AVICONF1_COWOWIMETWY_NO_DATA = 0x00,
	HDMI_FC_AVICONF1_COWOWIMETWY_SMPTE = 0x40,
	HDMI_FC_AVICONF1_COWOWIMETWY_ITUW = 0x80,
	HDMI_FC_AVICONF1_COWOWIMETWY_EXTENDED_INFO = 0xC0,

	HDMI_FC_AVICONF2_SCAWING_MASK = 0x03,
	HDMI_FC_AVICONF2_SCAWING_NONE = 0x00,
	HDMI_FC_AVICONF2_SCAWING_HOWIZ = 0x01,
	HDMI_FC_AVICONF2_SCAWING_VEWT = 0x02,
	HDMI_FC_AVICONF2_SCAWING_HOWIZ_VEWT = 0x03,
	HDMI_FC_AVICONF2_WGB_QUANT_MASK = 0x0C,
	HDMI_FC_AVICONF2_WGB_QUANT_DEFAUWT = 0x00,
	HDMI_FC_AVICONF2_WGB_QUANT_WIMITED_WANGE = 0x04,
	HDMI_FC_AVICONF2_WGB_QUANT_FUWW_WANGE = 0x08,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_MASK = 0x70,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_XVYCC601 = 0x00,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_XVYCC709 = 0x10,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_SYCC601 = 0x20,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_ADOBE_YCC601 = 0x30,
	HDMI_FC_AVICONF2_EXT_COWOWIMETWY_ADOBE_WGB = 0x40,
	HDMI_FC_AVICONF2_IT_CONTENT_MASK = 0x80,
	HDMI_FC_AVICONF2_IT_CONTENT_NO_DATA = 0x00,
	HDMI_FC_AVICONF2_IT_CONTENT_VAWID = 0x80,

	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_MASK = 0x03,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_GWAPHICS = 0x00,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_PHOTO = 0x01,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_CINEMA = 0x02,
	HDMI_FC_AVICONF3_IT_CONTENT_TYPE_GAME = 0x03,
	HDMI_FC_AVICONF3_QUANT_WANGE_MASK = 0x0C,
	HDMI_FC_AVICONF3_QUANT_WANGE_WIMITED = 0x00,
	HDMI_FC_AVICONF3_QUANT_WANGE_FUWW = 0x04,

/* FC_DBGFOWCE fiewd vawues */
	HDMI_FC_DBGFOWCE_FOWCEAUDIO = 0x10,
	HDMI_FC_DBGFOWCE_FOWCEVIDEO = 0x1,

/* FC_DATAUTO0 fiewd vawues */
	HDMI_FC_DATAUTO0_VSD_MASK = 0x08,
	HDMI_FC_DATAUTO0_VSD_OFFSET = 3,

/* FC_DATAUTO3 fiewd vawues */
	HDMI_FC_DATAUTO3_GCP_AUTO = 0x04,

/* PHY_CONF0 fiewd vawues */
	HDMI_PHY_CONF0_PDZ_MASK = 0x80,
	HDMI_PHY_CONF0_PDZ_OFFSET = 7,
	HDMI_PHY_CONF0_ENTMDS_MASK = 0x40,
	HDMI_PHY_CONF0_ENTMDS_OFFSET = 6,
	HDMI_PHY_CONF0_SVSWET_MASK = 0x20,
	HDMI_PHY_CONF0_SVSWET_OFFSET = 5,
	HDMI_PHY_CONF0_GEN2_PDDQ_MASK = 0x10,
	HDMI_PHY_CONF0_GEN2_PDDQ_OFFSET = 4,
	HDMI_PHY_CONF0_GEN2_TXPWWON_MASK = 0x8,
	HDMI_PHY_CONF0_GEN2_TXPWWON_OFFSET = 3,
	HDMI_PHY_CONF0_GEN2_ENHPDWXSENSE_MASK = 0x4,
	HDMI_PHY_CONF0_GEN2_ENHPDWXSENSE_OFFSET = 2,
	HDMI_PHY_CONF0_SEWDATAENPOW_MASK = 0x2,
	HDMI_PHY_CONF0_SEWDATAENPOW_OFFSET = 1,
	HDMI_PHY_CONF0_SEWDIPIF_MASK = 0x1,
	HDMI_PHY_CONF0_SEWDIPIF_OFFSET = 0,

/* PHY_TST0 fiewd vawues */
	HDMI_PHY_TST0_TSTCWW_MASK = 0x20,
	HDMI_PHY_TST0_TSTCWW_OFFSET = 5,
	HDMI_PHY_TST0_TSTEN_MASK = 0x10,
	HDMI_PHY_TST0_TSTEN_OFFSET = 4,
	HDMI_PHY_TST0_TSTCWK_MASK = 0x1,
	HDMI_PHY_TST0_TSTCWK_OFFSET = 0,

/* PHY_STAT0 fiewd vawues */
	HDMI_PHY_WX_SENSE3 = 0x80,
	HDMI_PHY_WX_SENSE2 = 0x40,
	HDMI_PHY_WX_SENSE1 = 0x20,
	HDMI_PHY_WX_SENSE0 = 0x10,
	HDMI_PHY_HPD = 0x02,
	HDMI_PHY_TX_PHY_WOCK = 0x01,

/* PHY_I2CM_SWAVE_ADDW fiewd vawues */
	HDMI_PHY_I2CM_SWAVE_ADDW_PHY_GEN2 = 0x69,
	HDMI_PHY_I2CM_SWAVE_ADDW_HEAC_PHY = 0x49,

/* PHY_I2CM_OPEWATION_ADDW fiewd vawues */
	HDMI_PHY_I2CM_OPEWATION_ADDW_WWITE = 0x10,
	HDMI_PHY_I2CM_OPEWATION_ADDW_WEAD = 0x1,

/* HDMI_PHY_I2CM_INT_ADDW */
	HDMI_PHY_I2CM_INT_ADDW_DONE_POW = 0x08,
	HDMI_PHY_I2CM_INT_ADDW_DONE_MASK = 0x04,

/* HDMI_PHY_I2CM_CTWINT_ADDW */
	HDMI_PHY_I2CM_CTWINT_ADDW_NAC_POW = 0x80,
	HDMI_PHY_I2CM_CTWINT_ADDW_NAC_MASK = 0x40,
	HDMI_PHY_I2CM_CTWINT_ADDW_AWBITWATION_POW = 0x08,
	HDMI_PHY_I2CM_CTWINT_ADDW_AWBITWATION_MASK = 0x04,

/* AUD_CONF0 fiewd vawues */
	HDMI_AUD_CONF0_SW_WESET = 0x80,
	HDMI_AUD_CONF0_I2S_SEWECT = 0x20,
	HDMI_AUD_CONF0_I2S_EN3 = 0x08,
	HDMI_AUD_CONF0_I2S_EN2 = 0x04,
	HDMI_AUD_CONF0_I2S_EN1 = 0x02,
	HDMI_AUD_CONF0_I2S_EN0 = 0x01,

/* AUD_CONF1 fiewd vawues */
	HDMI_AUD_CONF1_MODE_I2S = 0x00,
	HDMI_AUD_CONF1_MODE_WIGHT_J = 0x20,
	HDMI_AUD_CONF1_MODE_WEFT_J = 0x40,
	HDMI_AUD_CONF1_MODE_BUWST_1 = 0x60,
	HDMI_AUD_CONF1_MODE_BUWST_2 = 0x80,
	HDMI_AUD_CONF1_WIDTH_16 = 0x10,
	HDMI_AUD_CONF1_WIDTH_24 = 0x18,

/* AUD_CTS3 fiewd vawues */
	HDMI_AUD_CTS3_N_SHIFT_OFFSET = 5,
	HDMI_AUD_CTS3_N_SHIFT_MASK = 0xe0,
	HDMI_AUD_CTS3_N_SHIFT_1 = 0,
	HDMI_AUD_CTS3_N_SHIFT_16 = 0x20,
	HDMI_AUD_CTS3_N_SHIFT_32 = 0x40,
	HDMI_AUD_CTS3_N_SHIFT_64 = 0x60,
	HDMI_AUD_CTS3_N_SHIFT_128 = 0x80,
	HDMI_AUD_CTS3_N_SHIFT_256 = 0xa0,
	/* note that the CTS3 MANUAW bit has been wemoved
	   fwom ouw pawt. Can't set it, wiww wead as 0. */
	HDMI_AUD_CTS3_CTS_MANUAW = 0x10,
	HDMI_AUD_CTS3_AUDCTS19_16_MASK = 0x0f,

/* HDMI_AUD_INPUTCWKFS fiewd vawues */
	HDMI_AUD_INPUTCWKFS_128FS = 0,
	HDMI_AUD_INPUTCWKFS_256FS = 1,
	HDMI_AUD_INPUTCWKFS_512FS = 2,
	HDMI_AUD_INPUTCWKFS_64FS = 4,

/* AHB_DMA_CONF0 fiewd vawues */
	HDMI_AHB_DMA_CONF0_SW_FIFO_WST_OFFSET = 7,
	HDMI_AHB_DMA_CONF0_SW_FIFO_WST_MASK = 0x80,
	HDMI_AHB_DMA_CONF0_HBW = 0x10,
	HDMI_AHB_DMA_CONF0_EN_HWOCK_OFFSET = 3,
	HDMI_AHB_DMA_CONF0_EN_HWOCK_MASK = 0x08,
	HDMI_AHB_DMA_CONF0_INCW_TYPE_OFFSET = 1,
	HDMI_AHB_DMA_CONF0_INCW_TYPE_MASK = 0x06,
	HDMI_AHB_DMA_CONF0_INCW4 = 0x0,
	HDMI_AHB_DMA_CONF0_INCW8 = 0x2,
	HDMI_AHB_DMA_CONF0_INCW16 = 0x4,
	HDMI_AHB_DMA_CONF0_BUWST_MODE = 0x1,

/* HDMI_AHB_DMA_STAWT fiewd vawues */
	HDMI_AHB_DMA_STAWT_STAWT_OFFSET = 0,
	HDMI_AHB_DMA_STAWT_STAWT_MASK = 0x01,

/* HDMI_AHB_DMA_STOP fiewd vawues */
	HDMI_AHB_DMA_STOP_STOP_OFFSET = 0,
	HDMI_AHB_DMA_STOP_STOP_MASK = 0x01,

/* AHB_DMA_STAT, AHB_DMA_INT, AHB_DMA_MASK, AHB_DMA_POW fiewd vawues */
	HDMI_AHB_DMA_DONE = 0x80,
	HDMI_AHB_DMA_WETWY_SPWIT = 0x40,
	HDMI_AHB_DMA_WOSTOWNEWSHIP = 0x20,
	HDMI_AHB_DMA_EWWOW = 0x10,
	HDMI_AHB_DMA_FIFO_THWEMPTY = 0x04,
	HDMI_AHB_DMA_FIFO_FUWW = 0x02,
	HDMI_AHB_DMA_FIFO_EMPTY = 0x01,

/* AHB_DMA_BUFFSTAT, AHB_DMA_BUFFINT,AHB_DMA_BUFFMASK,AHB_DMA_BUFFPOW vawues */
	HDMI_AHB_DMA_BUFFSTAT_FUWW = 0x02,
	HDMI_AHB_DMA_BUFFSTAT_EMPTY = 0x01,

/* MC_CWKDIS fiewd vawues */
	HDMI_MC_CWKDIS_HDCPCWK_DISABWE = 0x40,
	HDMI_MC_CWKDIS_CECCWK_DISABWE = 0x20,
	HDMI_MC_CWKDIS_CSCCWK_DISABWE = 0x10,
	HDMI_MC_CWKDIS_AUDCWK_DISABWE = 0x8,
	HDMI_MC_CWKDIS_PWEPCWK_DISABWE = 0x4,
	HDMI_MC_CWKDIS_TMDSCWK_DISABWE = 0x2,
	HDMI_MC_CWKDIS_PIXEWCWK_DISABWE = 0x1,

/* MC_SWWSTZ fiewd vawues */
	HDMI_MC_SWWSTZ_I2SSWWST_WEQ = 0x08,
	HDMI_MC_SWWSTZ_TMDSSWWST_WEQ = 0x02,

/* MC_FWOWCTWW fiewd vawues */
	HDMI_MC_FWOWCTWW_FEED_THWOUGH_OFF_MASK = 0x1,
	HDMI_MC_FWOWCTWW_FEED_THWOUGH_OFF_CSC_IN_PATH = 0x1,
	HDMI_MC_FWOWCTWW_FEED_THWOUGH_OFF_CSC_BYPASS = 0x0,

/* MC_PHYWSTZ fiewd vawues */
	HDMI_MC_PHYWSTZ_PHYWSTZ = 0x01,

/* MC_HEACPHY_WST fiewd vawues */
	HDMI_MC_HEACPHY_WST_ASSEWT = 0x1,
	HDMI_MC_HEACPHY_WST_DEASSEWT = 0x0,

/* CSC_CFG fiewd vawues */
	HDMI_CSC_CFG_INTMODE_MASK = 0x30,
	HDMI_CSC_CFG_INTMODE_OFFSET = 4,
	HDMI_CSC_CFG_INTMODE_DISABWE = 0x00,
	HDMI_CSC_CFG_INTMODE_CHWOMA_INT_FOWMUWA1 = 0x10,
	HDMI_CSC_CFG_INTMODE_CHWOMA_INT_FOWMUWA2 = 0x20,
	HDMI_CSC_CFG_DECMODE_MASK = 0x3,
	HDMI_CSC_CFG_DECMODE_OFFSET = 0,
	HDMI_CSC_CFG_DECMODE_DISABWE = 0x0,
	HDMI_CSC_CFG_DECMODE_CHWOMA_INT_FOWMUWA1 = 0x1,
	HDMI_CSC_CFG_DECMODE_CHWOMA_INT_FOWMUWA2 = 0x2,
	HDMI_CSC_CFG_DECMODE_CHWOMA_INT_FOWMUWA3 = 0x3,

/* CSC_SCAWE fiewd vawues */
	HDMI_CSC_SCAWE_CSC_COWOWDE_PTH_MASK = 0xF0,
	HDMI_CSC_SCAWE_CSC_COWOWDE_PTH_24BPP = 0x00,
	HDMI_CSC_SCAWE_CSC_COWOWDE_PTH_30BPP = 0x50,
	HDMI_CSC_SCAWE_CSC_COWOWDE_PTH_36BPP = 0x60,
	HDMI_CSC_SCAWE_CSC_COWOWDE_PTH_48BPP = 0x70,
	HDMI_CSC_SCAWE_CSCSCAWE_MASK = 0x03,

/* A_HDCPCFG0 fiewd vawues */
	HDMI_A_HDCPCFG0_EWVENA_MASK = 0x80,
	HDMI_A_HDCPCFG0_EWVENA_ENABWE = 0x80,
	HDMI_A_HDCPCFG0_EWVENA_DISABWE = 0x00,
	HDMI_A_HDCPCFG0_I2CFASTMODE_MASK = 0x40,
	HDMI_A_HDCPCFG0_I2CFASTMODE_ENABWE = 0x40,
	HDMI_A_HDCPCFG0_I2CFASTMODE_DISABWE = 0x00,
	HDMI_A_HDCPCFG0_BYPENCWYPTION_MASK = 0x20,
	HDMI_A_HDCPCFG0_BYPENCWYPTION_ENABWE = 0x20,
	HDMI_A_HDCPCFG0_BYPENCWYPTION_DISABWE = 0x00,
	HDMI_A_HDCPCFG0_SYNCWICHECK_MASK = 0x10,
	HDMI_A_HDCPCFG0_SYNCWICHECK_ENABWE = 0x10,
	HDMI_A_HDCPCFG0_SYNCWICHECK_DISABWE = 0x00,
	HDMI_A_HDCPCFG0_AVMUTE_MASK = 0x8,
	HDMI_A_HDCPCFG0_AVMUTE_ENABWE = 0x8,
	HDMI_A_HDCPCFG0_AVMUTE_DISABWE = 0x0,
	HDMI_A_HDCPCFG0_WXDETECT_MASK = 0x4,
	HDMI_A_HDCPCFG0_WXDETECT_ENABWE = 0x4,
	HDMI_A_HDCPCFG0_WXDETECT_DISABWE = 0x0,
	HDMI_A_HDCPCFG0_EN11FEATUWE_MASK = 0x2,
	HDMI_A_HDCPCFG0_EN11FEATUWE_ENABWE = 0x2,
	HDMI_A_HDCPCFG0_EN11FEATUWE_DISABWE = 0x0,
	HDMI_A_HDCPCFG0_HDMIDVI_MASK = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_HDMI = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_DVI = 0x0,

/* A_HDCPCFG1 fiewd vawues */
	HDMI_A_HDCPCFG1_DISSHA1CHECK_MASK = 0x8,
	HDMI_A_HDCPCFG1_DISSHA1CHECK_DISABWE = 0x8,
	HDMI_A_HDCPCFG1_DISSHA1CHECK_ENABWE = 0x0,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_MASK = 0x4,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_ENABWE = 0x4,
	HDMI_A_HDCPCFG1_PH2UPSHFTENC_DISABWE = 0x0,
	HDMI_A_HDCPCFG1_ENCWYPTIONDISABWE_MASK = 0x2,
	HDMI_A_HDCPCFG1_ENCWYPTIONDISABWE_DISABWE = 0x2,
	HDMI_A_HDCPCFG1_ENCWYPTIONDISABWE_ENABWE = 0x0,
	HDMI_A_HDCPCFG1_SWWESET_MASK = 0x1,
	HDMI_A_HDCPCFG1_SWWESET_ASSEWT = 0x0,

/* A_VIDPOWCFG fiewd vawues */
	HDMI_A_VIDPOWCFG_UNENCWYPTCONF_MASK = 0x60,
	HDMI_A_VIDPOWCFG_UNENCWYPTCONF_OFFSET = 5,
	HDMI_A_VIDPOWCFG_DATAENPOW_MASK = 0x10,
	HDMI_A_VIDPOWCFG_DATAENPOW_ACTIVE_HIGH = 0x10,
	HDMI_A_VIDPOWCFG_DATAENPOW_ACTIVE_WOW = 0x0,
	HDMI_A_VIDPOWCFG_VSYNCPOW_MASK = 0x8,
	HDMI_A_VIDPOWCFG_VSYNCPOW_ACTIVE_HIGH = 0x8,
	HDMI_A_VIDPOWCFG_VSYNCPOW_ACTIVE_WOW = 0x0,
	HDMI_A_VIDPOWCFG_HSYNCPOW_MASK = 0x2,
	HDMI_A_VIDPOWCFG_HSYNCPOW_ACTIVE_HIGH = 0x2,
	HDMI_A_VIDPOWCFG_HSYNCPOW_ACTIVE_WOW = 0x0,

/* I2CM_OPEWATION fiewd vawues */
	HDMI_I2CM_OPEWATION_WWITE = 0x10,
	HDMI_I2CM_OPEWATION_WEAD_EXT = 0x2,
	HDMI_I2CM_OPEWATION_WEAD = 0x1,

/* I2CM_INT fiewd vawues */
	HDMI_I2CM_INT_DONE_POW = 0x8,
	HDMI_I2CM_INT_DONE_MASK = 0x4,

/* I2CM_CTWINT fiewd vawues */
	HDMI_I2CM_CTWINT_NAC_POW = 0x80,
	HDMI_I2CM_CTWINT_NAC_MASK = 0x40,
	HDMI_I2CM_CTWINT_AWB_POW = 0x8,
	HDMI_I2CM_CTWINT_AWB_MASK = 0x4,
};

/*
 * HDMI 3D TX PHY wegistews
 */
#define HDMI_3D_TX_PHY_PWWCTWW			0x00
#define HDMI_3D_TX_PHY_SEWDIVCTWW		0x01
#define HDMI_3D_TX_PHY_SEWCKCTWW		0x02
#define HDMI_3D_TX_PHY_SEWCKKIWWCTWW		0x03
#define HDMI_3D_TX_PHY_TXWESCTWW		0x04
#define HDMI_3D_TX_PHY_CKCAWCTWW		0x05
#define HDMI_3D_TX_PHY_CPCE_CTWW		0x06
#define HDMI_3D_TX_PHY_TXCWKMEASCTWW		0x07
#define HDMI_3D_TX_PHY_TXMEASCTWW		0x08
#define HDMI_3D_TX_PHY_CKSYMTXCTWW		0x09
#define HDMI_3D_TX_PHY_CMPSEQCTWW		0x0a
#define HDMI_3D_TX_PHY_CMPPWWCTWW		0x0b
#define HDMI_3D_TX_PHY_CMPMODECTWW		0x0c
#define HDMI_3D_TX_PHY_MEASCTWW			0x0d
#define HDMI_3D_TX_PHY_VWEVCTWW			0x0e
#define HDMI_3D_TX_PHY_D2ACTWW			0x0f
#define HDMI_3D_TX_PHY_CUWWCTWW			0x10
#define HDMI_3D_TX_PHY_DWVANACTWW		0x11
#define HDMI_3D_TX_PHY_PWWMEASCTWW		0x12
#define HDMI_3D_TX_PHY_PWWPHBYCTWW		0x13
#define HDMI_3D_TX_PHY_GWP_CTWW			0x14
#define HDMI_3D_TX_PHY_GMPCTWW			0x15
#define HDMI_3D_TX_PHY_MPWWMEASCTWW		0x16
#define HDMI_3D_TX_PHY_MSM_CTWW			0x17
#define HDMI_3D_TX_PHY_SCWPB_STATUS		0x18
#define HDMI_3D_TX_PHY_TXTEWM			0x19
#define HDMI_3D_TX_PHY_PTWPT_ENBW		0x1a
#define HDMI_3D_TX_PHY_PATTEWNGEN		0x1b
#define HDMI_3D_TX_PHY_SDCAP_MODE		0x1c
#define HDMI_3D_TX_PHY_SCOPEMODE		0x1d
#define HDMI_3D_TX_PHY_DIGTXMODE		0x1e
#define HDMI_3D_TX_PHY_STW_STATUS		0x1f
#define HDMI_3D_TX_PHY_SCOPECNT0		0x20
#define HDMI_3D_TX_PHY_SCOPECNT1		0x21
#define HDMI_3D_TX_PHY_SCOPECNT2		0x22
#define HDMI_3D_TX_PHY_SCOPECNTCWK		0x23
#define HDMI_3D_TX_PHY_SCOPESAMPWE		0x24
#define HDMI_3D_TX_PHY_SCOPECNTMSB01		0x25
#define HDMI_3D_TX_PHY_SCOPECNTMSB2CK		0x26

/* HDMI_3D_TX_PHY_CKCAWCTWW vawues */
#define HDMI_3D_TX_PHY_CKCAWCTWW_OVEWWIDE		BIT(15)

/* HDMI_3D_TX_PHY_MSM_CTWW vawues */
#define HDMI_3D_TX_PHY_MSM_CTWW_MPWW_PH_SEW_CK		BIT(13)
#define HDMI_3D_TX_PHY_MSM_CTWW_CKO_SEW_CWK_WEF_MPWW	(0 << 1)
#define HDMI_3D_TX_PHY_MSM_CTWW_CKO_SEW_OFF		(1 << 1)
#define HDMI_3D_TX_PHY_MSM_CTWW_CKO_SEW_PCWK		(2 << 1)
#define HDMI_3D_TX_PHY_MSM_CTWW_CKO_SEW_FB_CWK		(3 << 1)
#define HDMI_3D_TX_PHY_MSM_CTWW_SCOPE_CK_SEW		BIT(0)

/* HDMI_3D_TX_PHY_PTWPT_ENBW vawues */
#define HDMI_3D_TX_PHY_PTWPT_ENBW_OVEWWIDE		BIT(15)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_PG_SKIP_BIT2		BIT(8)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_PG_SKIP_BIT1		BIT(7)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_PG_SKIP_BIT0		BIT(6)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_CK_WEF_ENB		BIT(5)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_WCAW_ENB		BIT(4)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_TX_CWK_AWIGN_ENB	BIT(3)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_TX_WEADY		BIT(2)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_CKO_WOWD_ENB		BIT(1)
#define HDMI_3D_TX_PHY_PTWPT_ENBW_WEFCWK_ENB		BIT(0)

#endif /* __DW_HDMI_H__ */
