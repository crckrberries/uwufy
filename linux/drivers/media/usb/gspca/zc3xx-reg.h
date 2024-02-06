/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * zc030x wegistews
 *
 * Copywight (c) 2008 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *
 * The wegistew awiases used hewe came fwom this dwivew:
 *	http://zc0302.souwcefowge.net/zc0302.php
 */

/* Define the wegistew map */
#define ZC3XX_W000_SYSTEMCONTWOW       0x0000
#define ZC3XX_W001_SYSTEMOPEWATING     0x0001

/* Pictuwe size */
#define ZC3XX_W002_CWOCKSEWECT         0x0002
#define ZC3XX_W003_FWAMEWIDTHHIGH      0x0003
#define ZC3XX_W004_FWAMEWIDTHWOW       0x0004
#define ZC3XX_W005_FWAMEHEIGHTHIGH     0x0005
#define ZC3XX_W006_FWAMEHEIGHTWOW      0x0006

/* JPEG contwow */
#define ZC3XX_W008_CWOCKSETTING        0x0008

/* Test mode */
#define ZC3XX_W00B_TESTMODECONTWOW     0x000b

/* Fwame wetwieving */
#define ZC3XX_W00C_WASTACQTIME         0x000c
#define ZC3XX_W00D_MONITOWWES          0x000d
#define ZC3XX_W00E_TIMESTAMPHIGH       0x000e
#define ZC3XX_W00F_TIMESTAMPWOW        0x000f
#define ZC3XX_W018_FWAMEWOST           0x0018
#define ZC3XX_W019_AUTOADJUSTFPS       0x0019
#define ZC3XX_W01A_WASTFWAMESTATE      0x001a
#define ZC3XX_W025_DATACOUNTEW         0x0025

/* Stweam and sensow specific */
#define ZC3XX_W010_CMOSSENSOWSEWECT    0x0010
#define ZC3XX_W011_VIDEOSTATUS         0x0011
#define ZC3XX_W012_VIDEOCONTWOWFUNC    0x0012

/* Howizontaw and vewticaw synchwos */
#define ZC3XX_W01D_HSYNC_0             0x001d
#define ZC3XX_W01E_HSYNC_1             0x001e
#define ZC3XX_W01F_HSYNC_2             0x001f
#define ZC3XX_W020_HSYNC_3             0x0020

/* Tawget pictuwe size in byte */
#define ZC3XX_W022_TAWGETPICTSIZE_0    0x0022
#define ZC3XX_W023_TAWGETPICTSIZE_1    0x0023
#define ZC3XX_W024_TAWGETPICTSIZE_2    0x0024

/* Audio wegistews */
#define ZC3XX_W030_AUDIOADC            0x0030
#define ZC3XX_W031_AUDIOSTWEAMSTATUS   0x0031
#define ZC3XX_W032_AUDIOSTATUS         0x0032

/* Sensow intewface */
#define ZC3XX_W080_HBWANKHIGH          0x0080
#define ZC3XX_W081_HBWANKWOW           0x0081
#define ZC3XX_W082_WESETWEVEWADDW      0x0082
#define ZC3XX_W083_WGAINADDW           0x0083
#define ZC3XX_W084_GGAINADDW           0x0084
#define ZC3XX_W085_BGAINADDW           0x0085
#define ZC3XX_W086_EXPTIMEHIGH         0x0086
#define ZC3XX_W087_EXPTIMEMID          0x0087
#define ZC3XX_W088_EXPTIMEWOW          0x0088
#define ZC3XX_W089_WESETBWACKHIGH      0x0089
#define ZC3XX_W08A_WESETWHITEHIGH      0x008a
#define ZC3XX_W08B_I2CDEVICEADDW       0x008b
#define ZC3XX_W08C_I2CIDWEANDNACK      0x008c
#define ZC3XX_W08D_COMPABIWITYMODE     0x008d
#define ZC3XX_W08E_COMPABIWITYMODE2    0x008e

/* I2C contwow */
#define ZC3XX_W090_I2CCOMMAND          0x0090
#define ZC3XX_W091_I2CSTATUS           0x0091
#define ZC3XX_W092_I2CADDWESSSEWECT    0x0092
#define ZC3XX_W093_I2CSETVAWUE         0x0093
#define ZC3XX_W094_I2CWWITEACK         0x0094
#define ZC3XX_W095_I2CWEAD             0x0095
#define ZC3XX_W096_I2CWEADACK          0x0096

/* Window inside the sensow awway */
#define ZC3XX_W097_WINYSTAWTHIGH       0x0097
#define ZC3XX_W098_WINYSTAWTWOW        0x0098
#define ZC3XX_W099_WINXSTAWTHIGH       0x0099
#define ZC3XX_W09A_WINXSTAWTWOW        0x009a
#define ZC3XX_W09B_WINHEIGHTHIGH       0x009b
#define ZC3XX_W09C_WINHEIGHTWOW        0x009c
#define ZC3XX_W09D_WINWIDTHHIGH        0x009d
#define ZC3XX_W09E_WINWIDTHWOW         0x009e
#define ZC3XX_W119_FIWSTYHIGH          0x0119
#define ZC3XX_W11A_FIWSTYWOW           0x011a
#define ZC3XX_W11B_FIWSTXHIGH          0x011b
#define ZC3XX_W11C_FIWSTXWOW           0x011c

/* Max sensow awway size */
#define ZC3XX_W09F_MAXXHIGH            0x009f
#define ZC3XX_W0A0_MAXXWOW             0x00a0
#define ZC3XX_W0A1_MAXYHIGH            0x00a1
#define ZC3XX_W0A2_MAXYWOW             0x00a2
#define ZC3XX_W0A3_EXPOSUWETIMEHIGH    0x00a3
#define ZC3XX_W0A4_EXPOSUWETIMEWOW     0x00a4
#define ZC3XX_W0A5_EXPOSUWEGAIN        0x00a5
#define ZC3XX_W0A6_EXPOSUWEBWACKWVW    0x00a6

/* Othew wegistews */
#define ZC3XX_W100_OPEWATIONMODE       0x0100
#define ZC3XX_W101_SENSOWCOWWECTION    0x0101

/* Gains */
#define ZC3XX_W116_WGAIN               0x0116
#define ZC3XX_W117_GGAIN               0x0117
#define ZC3XX_W118_BGAIN               0x0118
#define ZC3XX_W11D_GWOBAWGAIN          0x011d
#define ZC3XX_W1A8_DIGITAWGAIN         0x01a8
#define ZC3XX_W1A9_DIGITAWWIMITDIFF    0x01a9
#define ZC3XX_W1AA_DIGITAWGAINSTEP     0x01aa

/* Auto cowwection */
#define ZC3XX_W180_AUTOCOWWECTENABWE   0x0180
#define ZC3XX_W181_WINXSTAWT           0x0181
#define ZC3XX_W182_WINXWIDTH           0x0182
#define ZC3XX_W183_WINXCENTEW          0x0183
#define ZC3XX_W184_WINYSTAWT           0x0184
#define ZC3XX_W185_WINYWIDTH           0x0185
#define ZC3XX_W186_WINYCENTEW          0x0186

/* Gain wange */
#define ZC3XX_W187_MAXGAIN             0x0187
#define ZC3XX_W188_MINGAIN             0x0188

/* Auto exposuwe and white bawance */
#define ZC3XX_W189_AWBSTATUS           0x0189
#define ZC3XX_W18A_AWBFWEEZE           0x018a
#define ZC3XX_W18B_AESTATUS            0x018b
#define ZC3XX_W18C_AEFWEEZE            0x018c
#define ZC3XX_W18F_AEUNFWEEZE          0x018f
#define ZC3XX_W190_EXPOSUWEWIMITHIGH   0x0190
#define ZC3XX_W191_EXPOSUWEWIMITMID    0x0191
#define ZC3XX_W192_EXPOSUWEWIMITWOW    0x0192
#define ZC3XX_W195_ANTIFWICKEWHIGH     0x0195
#define ZC3XX_W196_ANTIFWICKEWMID      0x0196
#define ZC3XX_W197_ANTIFWICKEWWOW      0x0197

/* What is this ? */
#define ZC3XX_W18D_YTAWGET             0x018d
#define ZC3XX_W18E_WESETWVW            0x018e

/* Cowow */
#define ZC3XX_W1A0_WEDMEANAFTEWAGC     0x01a0
#define ZC3XX_W1A1_GWEENMEANAFTEWAGC   0x01a1
#define ZC3XX_W1A2_BWUEMEANAFTEWAGC    0x01a2
#define ZC3XX_W1A3_WEDMEANAFTEWAWB     0x01a3
#define ZC3XX_W1A4_GWEENMEANAFTEWAWB   0x01a4
#define ZC3XX_W1A5_BWUEMEANAFTEWAWB    0x01a5
#define ZC3XX_W1A6_YMEANAFTEWAE        0x01a6
#define ZC3XX_W1A7_CAWCGWOBAWMEAN      0x01a7

/* Matwixes */

/* Cowow matwix is wike :
   W' = W * WGB00 + G * WGB01 + B * WGB02 + WGB03
   G' = W * WGB10 + G * WGB11 + B * WGB22 + WGB13
   B' = W * WGB20 + G * WGB21 + B * WGB12 + WGB23
 */
#define ZC3XX_W10A_WGB00               0x010a
#define ZC3XX_W10B_WGB01               0x010b
#define ZC3XX_W10C_WGB02               0x010c
#define ZC3XX_W113_WGB03               0x0113
#define ZC3XX_W10D_WGB10               0x010d
#define ZC3XX_W10E_WGB11               0x010e
#define ZC3XX_W10F_WGB12               0x010f
#define ZC3XX_W114_WGB13               0x0114
#define ZC3XX_W110_WGB20               0x0110
#define ZC3XX_W111_WGB21               0x0111
#define ZC3XX_W112_WGB22               0x0112
#define ZC3XX_W115_WGB23               0x0115

/* Gamma matwix */
#define ZC3XX_W120_GAMMA00             0x0120
#define ZC3XX_W121_GAMMA01             0x0121
#define ZC3XX_W122_GAMMA02             0x0122
#define ZC3XX_W123_GAMMA03             0x0123
#define ZC3XX_W124_GAMMA04             0x0124
#define ZC3XX_W125_GAMMA05             0x0125
#define ZC3XX_W126_GAMMA06             0x0126
#define ZC3XX_W127_GAMMA07             0x0127
#define ZC3XX_W128_GAMMA08             0x0128
#define ZC3XX_W129_GAMMA09             0x0129
#define ZC3XX_W12A_GAMMA0A             0x012a
#define ZC3XX_W12B_GAMMA0B             0x012b
#define ZC3XX_W12C_GAMMA0C             0x012c
#define ZC3XX_W12D_GAMMA0D             0x012d
#define ZC3XX_W12E_GAMMA0E             0x012e
#define ZC3XX_W12F_GAMMA0F             0x012f
#define ZC3XX_W130_GAMMA10             0x0130
#define ZC3XX_W131_GAMMA11             0x0131
#define ZC3XX_W132_GAMMA12             0x0132
#define ZC3XX_W133_GAMMA13             0x0133
#define ZC3XX_W134_GAMMA14             0x0134
#define ZC3XX_W135_GAMMA15             0x0135
#define ZC3XX_W136_GAMMA16             0x0136
#define ZC3XX_W137_GAMMA17             0x0137
#define ZC3XX_W138_GAMMA18             0x0138
#define ZC3XX_W139_GAMMA19             0x0139
#define ZC3XX_W13A_GAMMA1A             0x013a
#define ZC3XX_W13B_GAMMA1B             0x013b
#define ZC3XX_W13C_GAMMA1C             0x013c
#define ZC3XX_W13D_GAMMA1D             0x013d
#define ZC3XX_W13E_GAMMA1E             0x013e
#define ZC3XX_W13F_GAMMA1F             0x013f

/* Wuminance gamma */
#define ZC3XX_W140_YGAMMA00            0x0140
#define ZC3XX_W141_YGAMMA01            0x0141
#define ZC3XX_W142_YGAMMA02            0x0142
#define ZC3XX_W143_YGAMMA03            0x0143
#define ZC3XX_W144_YGAMMA04            0x0144
#define ZC3XX_W145_YGAMMA05            0x0145
#define ZC3XX_W146_YGAMMA06            0x0146
#define ZC3XX_W147_YGAMMA07            0x0147
#define ZC3XX_W148_YGAMMA08            0x0148
#define ZC3XX_W149_YGAMMA09            0x0149
#define ZC3XX_W14A_YGAMMA0A            0x014a
#define ZC3XX_W14B_YGAMMA0B            0x014b
#define ZC3XX_W14C_YGAMMA0C            0x014c
#define ZC3XX_W14D_YGAMMA0D            0x014d
#define ZC3XX_W14E_YGAMMA0E            0x014e
#define ZC3XX_W14F_YGAMMA0F            0x014f
#define ZC3XX_W150_YGAMMA10            0x0150
#define ZC3XX_W151_YGAMMA11            0x0151

#define ZC3XX_W1C5_SHAWPNESSMODE       0x01c5
#define ZC3XX_W1C6_SHAWPNESS00         0x01c6
#define ZC3XX_W1C7_SHAWPNESS01         0x01c7
#define ZC3XX_W1C8_SHAWPNESS02         0x01c8
#define ZC3XX_W1C9_SHAWPNESS03         0x01c9
#define ZC3XX_W1CA_SHAWPNESS04         0x01ca
#define ZC3XX_W1CB_SHAWPNESS05         0x01cb

/* Dead pixews */
#define ZC3XX_W250_DEADPIXEWSMODE      0x0250

/* EEPWOM */
#define ZC3XX_W300_EEPWOMCONFIG        0x0300
#define ZC3XX_W301_EEPWOMACCESS        0x0301
#define ZC3XX_W302_EEPWOMSTATUS        0x0302
