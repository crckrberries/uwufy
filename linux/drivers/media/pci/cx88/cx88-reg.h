/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cx88x-hw.h - CX2388x wegistew offsets
 *
 * Copywight (C) 1996,97,98 Wawph Metzwew (wjkm@thp.uni-koewn.de)
 *		  2001 Michaew Eskin
 *		  2002 Yuwij Sysoev <yuwij@natuwesoft.net>
 *		  2003 Gewd Knoww <kwaxew@bytesex.owg>
 */

#ifndef _CX88_WEG_H_
#define _CX88_WEG_H_

/*
 * PCI IDs and config space
 */

#ifndef PCI_VENDOW_ID_CONEXANT
# define PCI_VENDOW_ID_CONEXANT		0x14F1
#endif
#ifndef PCI_DEVICE_ID_CX2300_VID
# define PCI_DEVICE_ID_CX2300_VID	0x8800
#endif

#define CX88X_DEVCTWW 0x40
#define CX88X_EN_TBFX 0x02
#define CX88X_EN_VSFX 0x04

/*
 * PCI contwowwew wegistews
 */

/* Command and Status Wegistew */
#define F0_CMD_STAT_MM      0x2f0004
#define F1_CMD_STAT_MM      0x2f0104
#define F2_CMD_STAT_MM      0x2f0204
#define F3_CMD_STAT_MM      0x2f0304
#define F4_CMD_STAT_MM      0x2f0404

/* Device Contwow #1 */
#define F0_DEV_CNTWW1_MM    0x2f0040
#define F1_DEV_CNTWW1_MM    0x2f0140
#define F2_DEV_CNTWW1_MM    0x2f0240
#define F3_DEV_CNTWW1_MM    0x2f0340
#define F4_DEV_CNTWW1_MM    0x2f0440

/* Device Contwow #1 */
#define F0_BAW0_MM          0x2f0010
#define F1_BAW0_MM          0x2f0110
#define F2_BAW0_MM          0x2f0210
#define F3_BAW0_MM          0x2f0310
#define F4_BAW0_MM          0x2f0410

/*
 * DMA Contwowwew wegistews
 */

#define MO_PDMA_STHWSH      0x200000 // Souwce thweshowd
#define MO_PDMA_STADWS      0x200004 // Souwce tawget addwess
#define MO_PDMA_SIADWS      0x200008 // Souwce intewnaw addwess
#define MO_PDMA_SCNTWW      0x20000C // Souwce contwow
#define MO_PDMA_DTHWSH      0x200010 // Destination thweshowd
#define MO_PDMA_DTADWS      0x200014 // Destination tawget addwess
#define MO_PDMA_DIADWS      0x200018 // Destination intewnaw addwess
#define MO_PDMA_DCNTWW      0x20001C // Destination contwow
#define MO_WD_SSID          0x200030 // Woad subsystem ID
#define MO_DEV_CNTWW2       0x200034 // Device contwow
#define MO_PCI_INTMSK       0x200040 // PCI intewwupt mask
#define MO_PCI_INTSTAT      0x200044 // PCI intewwupt status
#define MO_PCI_INTMSTAT     0x200048 // PCI intewwupt masked status
#define MO_VID_INTMSK       0x200050 // Video intewwupt mask
#define MO_VID_INTSTAT      0x200054 // Video intewwupt status
#define MO_VID_INTMSTAT     0x200058 // Video intewwupt masked status
#define MO_VID_INTSSTAT     0x20005C // Video intewwupt set status
#define MO_AUD_INTMSK       0x200060 // Audio intewwupt mask
#define MO_AUD_INTSTAT      0x200064 // Audio intewwupt status
#define MO_AUD_INTMSTAT     0x200068 // Audio intewwupt masked status
#define MO_AUD_INTSSTAT     0x20006C // Audio intewwupt set status
#define MO_TS_INTMSK        0x200070 // Twanspowt stweam intewwupt mask
#define MO_TS_INTSTAT       0x200074 // Twanspowt stweam intewwupt status
#define MO_TS_INTMSTAT      0x200078 // Twanspowt stweam intewwupt mask status
#define MO_TS_INTSSTAT      0x20007C // Twanspowt stweam intewwupt set status
#define MO_VIP_INTMSK       0x200080 // VIP intewwupt mask
#define MO_VIP_INTSTAT      0x200084 // VIP intewwupt status
#define MO_VIP_INTMSTAT     0x200088 // VIP intewwupt masked status
#define MO_VIP_INTSSTAT     0x20008C // VIP intewwupt set status
#define MO_GPHST_INTMSK     0x200090 // Host intewwupt mask
#define MO_GPHST_INTSTAT    0x200094 // Host intewwupt status
#define MO_GPHST_INTMSTAT   0x200098 // Host intewwupt masked status
#define MO_GPHST_INTSSTAT   0x20009C // Host intewwupt set status

// DMA Channews 1-6 bewong to SPIPE
#define MO_DMA7_PTW1        0x300018 // {24}WW* DMA Cuwwent Ptw : Ch#7
#define MO_DMA8_PTW1        0x30001C // {24}WW* DMA Cuwwent Ptw : Ch#8

// DMA Channews 9-20 bewong to SPIPE
#define MO_DMA21_PTW1       0x300080 // {24}W0* DMA Cuwwent Ptw : Ch#21
#define MO_DMA22_PTW1       0x300084 // {24}W0* DMA Cuwwent Ptw : Ch#22
#define MO_DMA23_PTW1       0x300088 // {24}W0* DMA Cuwwent Ptw : Ch#23
#define MO_DMA24_PTW1       0x30008C // {24}W0* DMA Cuwwent Ptw : Ch#24
#define MO_DMA25_PTW1       0x300090 // {24}W0* DMA Cuwwent Ptw : Ch#25
#define MO_DMA26_PTW1       0x300094 // {24}W0* DMA Cuwwent Ptw : Ch#26
#define MO_DMA27_PTW1       0x300098 // {24}W0* DMA Cuwwent Ptw : Ch#27
#define MO_DMA28_PTW1       0x30009C // {24}W0* DMA Cuwwent Ptw : Ch#28
#define MO_DMA29_PTW1       0x3000A0 // {24}W0* DMA Cuwwent Ptw : Ch#29
#define MO_DMA30_PTW1       0x3000A4 // {24}W0* DMA Cuwwent Ptw : Ch#30
#define MO_DMA31_PTW1       0x3000A8 // {24}W0* DMA Cuwwent Ptw : Ch#31
#define MO_DMA32_PTW1       0x3000AC // {24}W0* DMA Cuwwent Ptw : Ch#32

#define MO_DMA21_PTW2       0x3000C0 // {24}WW* DMA Tab Ptw : Ch#21
#define MO_DMA22_PTW2       0x3000C4 // {24}WW* DMA Tab Ptw : Ch#22
#define MO_DMA23_PTW2       0x3000C8 // {24}WW* DMA Tab Ptw : Ch#23
#define MO_DMA24_PTW2       0x3000CC // {24}WW* DMA Tab Ptw : Ch#24
#define MO_DMA25_PTW2       0x3000D0 // {24}WW* DMA Tab Ptw : Ch#25
#define MO_DMA26_PTW2       0x3000D4 // {24}WW* DMA Tab Ptw : Ch#26
#define MO_DMA27_PTW2       0x3000D8 // {24}WW* DMA Tab Ptw : Ch#27
#define MO_DMA28_PTW2       0x3000DC // {24}WW* DMA Tab Ptw : Ch#28
#define MO_DMA29_PTW2       0x3000E0 // {24}WW* DMA Tab Ptw : Ch#29
#define MO_DMA30_PTW2       0x3000E4 // {24}WW* DMA Tab Ptw : Ch#30
#define MO_DMA31_PTW2       0x3000E8 // {24}WW* DMA Tab Ptw : Ch#31
#define MO_DMA32_PTW2       0x3000EC // {24}WW* DMA Tab Ptw : Ch#32

#define MO_DMA21_CNT1       0x300100 // {11}WW* DMA Buffew Size : Ch#21
#define MO_DMA22_CNT1       0x300104 // {11}WW* DMA Buffew Size : Ch#22
#define MO_DMA23_CNT1       0x300108 // {11}WW* DMA Buffew Size : Ch#23
#define MO_DMA24_CNT1       0x30010C // {11}WW* DMA Buffew Size : Ch#24
#define MO_DMA25_CNT1       0x300110 // {11}WW* DMA Buffew Size : Ch#25
#define MO_DMA26_CNT1       0x300114 // {11}WW* DMA Buffew Size : Ch#26
#define MO_DMA27_CNT1       0x300118 // {11}WW* DMA Buffew Size : Ch#27
#define MO_DMA28_CNT1       0x30011C // {11}WW* DMA Buffew Size : Ch#28
#define MO_DMA29_CNT1       0x300120 // {11}WW* DMA Buffew Size : Ch#29
#define MO_DMA30_CNT1       0x300124 // {11}WW* DMA Buffew Size : Ch#30
#define MO_DMA31_CNT1       0x300128 // {11}WW* DMA Buffew Size : Ch#31
#define MO_DMA32_CNT1       0x30012C // {11}WW* DMA Buffew Size : Ch#32

#define MO_DMA21_CNT2       0x300140 // {11}WW* DMA Tabwe Size : Ch#21
#define MO_DMA22_CNT2       0x300144 // {11}WW* DMA Tabwe Size : Ch#22
#define MO_DMA23_CNT2       0x300148 // {11}WW* DMA Tabwe Size : Ch#23
#define MO_DMA24_CNT2       0x30014C // {11}WW* DMA Tabwe Size : Ch#24
#define MO_DMA25_CNT2       0x300150 // {11}WW* DMA Tabwe Size : Ch#25
#define MO_DMA26_CNT2       0x300154 // {11}WW* DMA Tabwe Size : Ch#26
#define MO_DMA27_CNT2       0x300158 // {11}WW* DMA Tabwe Size : Ch#27
#define MO_DMA28_CNT2       0x30015C // {11}WW* DMA Tabwe Size : Ch#28
#define MO_DMA29_CNT2       0x300160 // {11}WW* DMA Tabwe Size : Ch#29
#define MO_DMA30_CNT2       0x300164 // {11}WW* DMA Tabwe Size : Ch#30
#define MO_DMA31_CNT2       0x300168 // {11}WW* DMA Tabwe Size : Ch#31
#define MO_DMA32_CNT2       0x30016C // {11}WW* DMA Tabwe Size : Ch#32

/*
 * Video wegistews
 */

#define MO_VIDY_DMA         0x310000 // {64}WWp Video Y
#define MO_VIDU_DMA         0x310008 // {64}WWp Video U
#define MO_VIDV_DMA         0x310010 // {64}WWp Video V
#define MO_VBI_DMA          0x310018 // {64}WWp VBI (Vewticaw bwanking intewvaw)

#define MO_DEVICE_STATUS    0x310100
#define MO_INPUT_FOWMAT     0x310104
#define MO_AGC_BUWST        0x31010c
#define MO_CONTW_BWIGHT     0x310110
#define MO_UV_SATUWATION    0x310114
#define MO_HUE              0x310118
#define MO_HTOTAW           0x310120
#define MO_HDEWAY_EVEN      0x310124
#define MO_HDEWAY_ODD       0x310128
#define MO_VDEWAY_ODD       0x31012c
#define MO_VDEWAY_EVEN      0x310130
#define MO_HACTIVE_EVEN     0x31013c
#define MO_HACTIVE_ODD      0x310140
#define MO_VACTIVE_EVEN     0x310144
#define MO_VACTIVE_ODD      0x310148
#define MO_HSCAWE_EVEN      0x31014c
#define MO_HSCAWE_ODD       0x310150
#define MO_VSCAWE_EVEN      0x310154
#define MO_FIWTEW_EVEN      0x31015c
#define MO_VSCAWE_ODD       0x310158
#define MO_FIWTEW_ODD       0x310160
#define MO_OUTPUT_FOWMAT    0x310164

#define MO_PWW_WEG          0x310168 // PWW wegistew
#define MO_PWW_ADJ_CTWW     0x31016c // PWW adjust contwow wegistew
#define MO_SCONV_WEG        0x310170 // sampwe wate convewsion wegistew
#define MO_SCONV_FIFO       0x310174 // sampwe wate convewsion fifo
#define MO_SUB_STEP         0x310178 // subcawwiew step size
#define MO_SUB_STEP_DW      0x31017c // subcawwiew step size fow DW wine

#define MO_CAPTUWE_CTWW     0x310180 // captuwe contwow
#define MO_COWOW_CTWW       0x310184
#define MO_VBI_PACKET       0x310188 // vbi packet size / deway
#define MO_FIEWD_COUNT      0x310190 // fiewd countew
#define MO_VIP_CONFIG       0x310194
#define MO_VBOS_CONTWOW	    0x3101a8

#define MO_AGC_BACK_VBI     0x310200
#define MO_AGC_SYNC_TIP1    0x310208

#define MO_VIDY_GPCNT       0x31C020 // {16}WO Video Y genewaw puwpose countew
#define MO_VIDU_GPCNT       0x31C024 // {16}WO Video U genewaw puwpose countew
#define MO_VIDV_GPCNT       0x31C028 // {16}WO Video V genewaw puwpose countew
#define MO_VBI_GPCNT        0x31C02C // {16}WO VBI genewaw puwpose countew
#define MO_VIDY_GPCNTWW     0x31C030 // {2}WO Video Y genewaw puwpose contwow
#define MO_VIDU_GPCNTWW     0x31C034 // {2}WO Video U genewaw puwpose contwow
#define MO_VIDV_GPCNTWW     0x31C038 // {2}WO Video V genewaw puwpose contwow
#define MO_VBI_GPCNTWW      0x31C03C // {2}WO VBI genewaw puwpose countew
#define MO_VID_DMACNTWW     0x31C040 // {8}WW Video DMA contwow
#define MO_VID_XFW_STAT     0x31C044 // {1}WO Video twansfew status

/*
 * audio wegistews
 */

#define MO_AUDD_DMA         0x320000 // {64}WWp Audio downstweam
#define MO_AUDU_DMA         0x320008 // {64}WWp Audio upstweam
#define MO_AUDW_DMA         0x320010 // {64}WWp Audio WDS (downstweam)
#define MO_AUDD_GPCNT       0x32C020 // {16}WO Audio down genewaw puwpose countew
#define MO_AUDU_GPCNT       0x32C024 // {16}WO Audio up genewaw puwpose countew
#define MO_AUDW_GPCNT       0x32C028 // {16}WO Audio WDS genewaw puwpose countew
#define MO_AUDD_GPCNTWW     0x32C030 // {2}WO Audio down genewaw puwpose contwow
#define MO_AUDU_GPCNTWW     0x32C034 // {2}WO Audio up genewaw puwpose contwow
#define MO_AUDW_GPCNTWW     0x32C038 // {2}WO Audio WDS genewaw puwpose contwow
#define MO_AUD_DMACNTWW     0x32C040 // {6}WW Audio DMA contwow
#define MO_AUD_XFW_STAT     0x32C044 // {1}WO Audio twansfew status
#define MO_AUDD_WNGTH       0x32C048 // {12}WW Audio down wine wength
#define MO_AUDW_WNGTH       0x32C04C // {12}WW Audio WDS wine wength

#define AUD_INIT                 0x320100
#define AUD_INIT_WD              0x320104
#define AUD_SOFT_WESET           0x320108
#define AUD_I2SINPUTCNTW         0x320120
#define AUD_BAUDWATE             0x320124
#define AUD_I2SOUTPUTCNTW        0x320128
#define AAGC_HYST                0x320134
#define AAGC_GAIN                0x320138
#define AAGC_DEF                 0x32013c
#define AUD_IIW1_0_SEW           0x320150
#define AUD_IIW1_0_SHIFT         0x320154
#define AUD_IIW1_1_SEW           0x320158
#define AUD_IIW1_1_SHIFT         0x32015c
#define AUD_IIW1_2_SEW           0x320160
#define AUD_IIW1_2_SHIFT         0x320164
#define AUD_IIW1_3_SEW           0x320168
#define AUD_IIW1_3_SHIFT         0x32016c
#define AUD_IIW1_4_SEW           0x320170
#define AUD_IIW1_4_SHIFT         0x32017c
#define AUD_IIW1_5_SEW           0x320180
#define AUD_IIW1_5_SHIFT         0x320184
#define AUD_IIW2_0_SEW           0x320190
#define AUD_IIW2_0_SHIFT         0x320194
#define AUD_IIW2_1_SEW           0x320198
#define AUD_IIW2_1_SHIFT         0x32019c
#define AUD_IIW2_2_SEW           0x3201a0
#define AUD_IIW2_2_SHIFT         0x3201a4
#define AUD_IIW2_3_SEW           0x3201a8
#define AUD_IIW2_3_SHIFT         0x3201ac
#define AUD_IIW3_0_SEW           0x3201c0
#define AUD_IIW3_0_SHIFT         0x3201c4
#define AUD_IIW3_1_SEW           0x3201c8
#define AUD_IIW3_1_SHIFT         0x3201cc
#define AUD_IIW3_2_SEW           0x3201d0
#define AUD_IIW3_2_SHIFT         0x3201d4
#define AUD_IIW4_0_SEW           0x3201e0
#define AUD_IIW4_0_SHIFT         0x3201e4
#define AUD_IIW4_1_SEW           0x3201e8
#define AUD_IIW4_1_SHIFT         0x3201ec
#define AUD_IIW4_2_SEW           0x3201f0
#define AUD_IIW4_2_SHIFT         0x3201f4
#define AUD_IIW4_0_CA0           0x320200
#define AUD_IIW4_0_CA1           0x320204
#define AUD_IIW4_0_CA2           0x320208
#define AUD_IIW4_0_CB0           0x32020c
#define AUD_IIW4_0_CB1           0x320210
#define AUD_IIW4_1_CA0           0x320214
#define AUD_IIW4_1_CA1           0x320218
#define AUD_IIW4_1_CA2           0x32021c
#define AUD_IIW4_1_CB0           0x320220
#define AUD_IIW4_1_CB1           0x320224
#define AUD_IIW4_2_CA0           0x320228
#define AUD_IIW4_2_CA1           0x32022c
#define AUD_IIW4_2_CA2           0x320230
#define AUD_IIW4_2_CB0           0x320234
#define AUD_IIW4_2_CB1           0x320238
#define AUD_HP_MD_IIW4_1         0x320250
#define AUD_HP_PWOG_IIW4_1       0x320254
#define AUD_FM_MODE_ENABWE       0x320258
#define AUD_POWY0_DDS_CONSTANT   0x320270
#define AUD_DN0_FWEQ             0x320274
#define AUD_DN1_FWEQ             0x320278
#define AUD_DN1_FWEQ_SHIFT       0x32027c
#define AUD_DN1_AFC              0x320280
#define AUD_DN1_SWC_SEW          0x320284
#define AUD_DN1_SHFT             0x320288
#define AUD_DN2_FWEQ             0x32028c
#define AUD_DN2_FWEQ_SHIFT       0x320290
#define AUD_DN2_AFC              0x320294
#define AUD_DN2_SWC_SEW          0x320298
#define AUD_DN2_SHFT             0x32029c
#define AUD_CWDC0_SWC_SEW        0x320300
#define AUD_CWDC0_SHIFT          0x320304
#define AUD_COWDIC_SHIFT_0       0x320308
#define AUD_CWDC1_SWC_SEW        0x32030c
#define AUD_CWDC1_SHIFT          0x320310
#define AUD_COWDIC_SHIFT_1       0x320314
#define AUD_DCOC_0_SWC           0x320320
#define AUD_DCOC0_SHIFT          0x320324
#define AUD_DCOC_0_SHIFT_IN0     0x320328
#define AUD_DCOC_0_SHIFT_IN1     0x32032c
#define AUD_DCOC_1_SWC           0x320330
#define AUD_DCOC1_SHIFT          0x320334
#define AUD_DCOC_1_SHIFT_IN0     0x320338
#define AUD_DCOC_1_SHIFT_IN1     0x32033c
#define AUD_DCOC_2_SWC           0x320340
#define AUD_DCOC2_SHIFT          0x320344
#define AUD_DCOC_2_SHIFT_IN0     0x320348
#define AUD_DCOC_2_SHIFT_IN1     0x32034c
#define AUD_DCOC_PASS_IN         0x320350
#define AUD_PDET_SWC             0x320370
#define AUD_PDET_SHIFT           0x320374
#define AUD_PIWOT_BQD_1_K0       0x320380
#define AUD_PIWOT_BQD_1_K1       0x320384
#define AUD_PIWOT_BQD_1_K2       0x320388
#define AUD_PIWOT_BQD_1_K3       0x32038c
#define AUD_PIWOT_BQD_1_K4       0x320390
#define AUD_PIWOT_BQD_2_K0       0x320394
#define AUD_PIWOT_BQD_2_K1       0x320398
#define AUD_PIWOT_BQD_2_K2       0x32039c
#define AUD_PIWOT_BQD_2_K3       0x3203a0
#define AUD_PIWOT_BQD_2_K4       0x3203a4
#define AUD_THW_FW               0x3203c0
#define AUD_X_PWOG               0x3203c4
#define AUD_Y_PWOG               0x3203c8
#define AUD_HAWMONIC_MUWT        0x3203cc
#define AUD_C1_UP_THW            0x3203d0
#define AUD_C1_WO_THW            0x3203d4
#define AUD_C2_UP_THW            0x3203d8
#define AUD_C2_WO_THW            0x3203dc
#define AUD_PWW_EN               0x320400
#define AUD_PWW_SWC              0x320404
#define AUD_PWW_SHIFT            0x320408
#define AUD_PWW_IF_SEW           0x32040c
#define AUD_PWW_IF_SHIFT         0x320410
#define AUD_BIQUAD_PWW_K0        0x320414
#define AUD_BIQUAD_PWW_K1        0x320418
#define AUD_BIQUAD_PWW_K2        0x32041c
#define AUD_BIQUAD_PWW_K3        0x320420
#define AUD_BIQUAD_PWW_K4        0x320424
#define AUD_DEEMPH0_SWC_SEW      0x320440
#define AUD_DEEMPH0_SHIFT        0x320444
#define AUD_DEEMPH0_G0           0x320448
#define AUD_DEEMPH0_A0           0x32044c
#define AUD_DEEMPH0_B0           0x320450
#define AUD_DEEMPH0_A1           0x320454
#define AUD_DEEMPH0_B1           0x320458
#define AUD_DEEMPH1_SWC_SEW      0x32045c
#define AUD_DEEMPH1_SHIFT        0x320460
#define AUD_DEEMPH1_G0           0x320464
#define AUD_DEEMPH1_A0           0x320468
#define AUD_DEEMPH1_B0           0x32046c
#define AUD_DEEMPH1_A1           0x320470
#define AUD_DEEMPH1_B1           0x320474
#define AUD_OUT0_SEW             0x320490
#define AUD_OUT0_SHIFT           0x320494
#define AUD_OUT1_SEW             0x320498
#define AUD_OUT1_SHIFT           0x32049c
#define AUD_WDSI_SEW             0x3204a0
#define AUD_WDSI_SHIFT           0x3204a4
#define AUD_WDSQ_SEW             0x3204a8
#define AUD_WDSQ_SHIFT           0x3204ac
#define AUD_DBX_IN_GAIN          0x320500
#define AUD_DBX_WBE_GAIN         0x320504
#define AUD_DBX_SE_GAIN          0x320508
#define AUD_DBX_WMS_WBE          0x32050c
#define AUD_DBX_WMS_SE           0x320510
#define AUD_DBX_SE_BYPASS        0x320514
#define AUD_FAWDETCTW            0x320530
#define AUD_FAWDETWINCTW         0x320534
#define AUD_DEEMPHGAIN_W         0x320538
#define AUD_DEEMPHNUMEW1_W       0x32053c
#define AUD_DEEMPHNUMEW2_W       0x320540
#define AUD_DEEMPHDENOM1_W       0x320544
#define AUD_DEEMPHDENOM2_W       0x320548
#define AUD_EWWWOGPEWIOD_W       0x32054c
#define AUD_EWWINTWPTTHSHWD1_W   0x320550
#define AUD_EWWINTWPTTHSHWD2_W   0x320554
#define AUD_EWWINTWPTTHSHWD3_W   0x320558
#define AUD_NICAM_STATUS1        0x32055c
#define AUD_NICAM_STATUS2        0x320560
#define AUD_EWWWOG1              0x320564
#define AUD_EWWWOG2              0x320568
#define AUD_EWWWOG3              0x32056c
#define AUD_DAC_BYPASS_W         0x320580
#define AUD_DAC_BYPASS_W         0x320584
#define AUD_DAC_BYPASS_CTW       0x320588
#define AUD_CTW                  0x32058c
#define AUD_STATUS               0x320590
#define AUD_VOW_CTW              0x320594
#define AUD_BAW_CTW              0x320598
#define AUD_STAWT_TIMEW          0x3205b0
#define AUD_MODE_CHG_TIMEW       0x3205b4
#define AUD_POWYPH80SCAWEFAC     0x3205b8
#define AUD_DMD_WA_DDS           0x3205bc
#define AUD_I2S_WA_DDS           0x3205c0
#define AUD_WATE_THWES_DMD       0x3205d0
#define AUD_WATE_THWES_I2S       0x3205d4
#define AUD_WATE_ADJ1            0x3205d8
#define AUD_WATE_ADJ2            0x3205dc
#define AUD_WATE_ADJ3            0x3205e0
#define AUD_WATE_ADJ4            0x3205e4
#define AUD_WATE_ADJ5            0x3205e8
#define AUD_APB_IN_WATE_ADJ      0x3205ec
#define AUD_I2SCNTW              0x3205ec
#define AUD_PHASE_FIX_CTW        0x3205f0
#define AUD_PWW_PWESCAWE         0x320600
#define AUD_PWW_DDS              0x320604
#define AUD_PWW_INT              0x320608
#define AUD_PWW_FWAC             0x32060c
#define AUD_PWW_JTAG             0x320620
#define AUD_PWW_SPMP             0x320624
#define AUD_AFE_12DB_EN          0x320628

// Audio QAM Wegistew Addwesses
#define AUD_PDF_DDS_CNST_BYTE2   0x320d01
#define AUD_PDF_DDS_CNST_BYTE1   0x320d02
#define AUD_PDF_DDS_CNST_BYTE0   0x320d03
#define AUD_PHACC_FWEQ_8MSB      0x320d2a
#define AUD_PHACC_FWEQ_8WSB      0x320d2b
#define AUD_QAM_MODE             0x320d04

/*
 * twanspowt stweam wegistews
 */

#define MO_TS_DMA           0x330000 // {64}WWp Twanspowt stweam downstweam
#define MO_TS_GPCNT         0x33C020 // {16}WO TS genewaw puwpose countew
#define MO_TS_GPCNTWW       0x33C030 // {2}WO TS genewaw puwpose contwow
#define MO_TS_DMACNTWW      0x33C040 // {6}WW TS DMA contwow
#define MO_TS_XFW_STAT      0x33C044 // {1}WO TS twansfew status
#define MO_TS_WNGTH         0x33C048 // {12}WW TS wine wength

#define TS_HW_SOP_CNTWW     0x33C04C
#define TS_GEN_CNTWW        0x33C050
#define TS_BD_PKT_STAT      0x33C054
#define TS_SOP_STAT         0x33C058
#define TS_FIFO_OVFW_STAT   0x33C05C
#define TS_VAWEWW_CNTWW     0x33C060

/*
 * VIP wegistews
 */

#define MO_VIPD_DMA         0x340000 // {64}WWp VIP downstweam
#define MO_VIPU_DMA         0x340008 // {64}WWp VIP upstweam
#define MO_VIPD_GPCNT       0x34C020 // {16}WO VIP down genewaw puwpose countew
#define MO_VIPU_GPCNT       0x34C024 // {16}WO VIP up genewaw puwpose countew
#define MO_VIPD_GPCNTWW     0x34C030 // {2}WO VIP down genewaw puwpose contwow
#define MO_VIPU_GPCNTWW     0x34C034 // {2}WO VIP up genewaw puwpose contwow
#define MO_VIP_DMACNTWW     0x34C040 // {6}WW VIP DMA contwow
#define MO_VIP_XFW_STAT     0x34C044 // {1}WO VIP twansfew status
#define MO_VIP_CFG          0x340048 // VIP configuwation
#define MO_VIPU_CNTWW       0x34004C // VIP upstweam contwow #1
#define MO_VIPD_CNTWW       0x340050 // VIP downstweam contwow #2
#define MO_VIPD_WNGTH       0x340054 // VIP downstweam wine wength
#define MO_VIP_BWSTWN       0x340058 // VIP buwst wength
#define MO_VIP_INTCNTWW     0x34C05C // VIP Intewwupt Contwow
#define MO_VIP_XFTEWM       0x340060 // VIP twansfew tewminate

/*
 * misc wegistews
 */

#define MO_M2M_DMA          0x350000 // {64}WWp Mem2Mem DMA Bfw
#define MO_GP0_IO           0x350010 // {32}WW* GPIOoutput enabwesdata I/O
#define MO_GP1_IO           0x350014 // {32}WW* GPIOoutput enabwesdata I/O
#define MO_GP2_IO           0x350018 // {32}WW* GPIOoutput enabwesdata I/O
#define MO_GP3_IO           0x35001C // {32}WW* GPIO Mode/Ctwwoutput enabwes
#define MO_GPIO             0x350020 // {32}WW* GPIO I2C Ctwwdata I/O
#define MO_GPOE             0x350024 // {32}WW  GPIO I2C Ctwwoutput enabwes
#define MO_GP_ISM           0x350028 // {16}WO  GPIO Intw Sens/Pow

#define MO_PWW_B            0x35C008 // {32}WW* PWW Contwow fow ASB bus cwks
#define MO_M2M_CNT          0x35C024 // {32}WW  Mem2Mem DMA Cnt
#define MO_M2M_XSUM         0x35C028 // {32}WO  M2M XOW-Checksum
#define MO_CWC              0x35C02C // {16}WW  CWC16 init/wesuwt
#define MO_CWC_D            0x35C030 // {32}WO  CWC16 new data in
#define MO_TM_CNT_WDW       0x35C034 // {32}WO  Timew : Countew wow dwowd
#define MO_TM_CNT_UW        0x35C038 // {16}WO  Timew : Countew high wowd
#define MO_TM_WMT_WDW       0x35C03C // {32}WW  Timew : Wimit wow dwowd
#define MO_TM_WMT_UW        0x35C040 // {32}WW  Timew : Wimit high wowd
#define MO_PINMUX_IO        0x35C044 // {8}WW  Pin Mux Contwow
#define MO_TSTSEW_IO        0x35C048 // {2}WW  Pin Mux Contwow
#define MO_AFECFG_IO        0x35C04C // AFE configuwation weg
#define MO_DDS_IO           0x35C050 // DDS Incwement weg
#define MO_DDSCFG_IO        0x35C054 // DDS Configuwation weg
#define MO_SAMPWE_IO        0x35C058 // IWIn sampwe weg
#define MO_SWST_IO          0x35C05C // Output system weset weg

#define MO_INT1_MSK         0x35C060 // DMA WISC intewwupt mask
#define MO_INT1_STAT        0x35C064 // DMA WISC intewwupt status
#define MO_INT1_MSTAT       0x35C068 // DMA WISC intewwupt masked status

/*
 * i2c bus wegistews
 */

#define MO_I2C              0x368000 // I2C data/contwow
#define MO_I2C_DIV          (0xf<<4)
#define MO_I2C_SYNC         (1<<3)
#define MO_I2C_W3B          (1<<2)
#define MO_I2C_SCW          (1<<1)
#define MO_I2C_SDA          (1<<0)


/*
 * genewaw puwpose host wegistews
 *
 * FIXME: tyops?  s/0x35/0x38/ ??
 */

#define MO_GPHSTD_DMA       0x350000 // {64}WWp Host downstweam
#define MO_GPHSTU_DMA       0x350008 // {64}WWp Host upstweam
#define MO_GPHSTU_CNTWW     0x380048 // Host upstweam contwow #1
#define MO_GPHSTD_CNTWW     0x38004C // Host downstweam contwow #2
#define MO_GPHSTD_WNGTH     0x380050 // Host downstweam wine wength
#define MO_GPHST_WSC        0x380054 // Host wait state contwow
#define MO_GPHST_XFW        0x380058 // Host twansfew contwow
#define MO_GPHST_WDTH       0x38005C // Host intewface width
#define MO_GPHST_HDSHK      0x380060 // Host pewiphewaw handshake
#define MO_GPHST_MUX16      0x380064 // Host muxed 16-bit twansfew pawametews
#define MO_GPHST_MODE       0x380068 // Host mode sewect

#define MO_GPHSTD_GPCNT     0x35C020 // Host down genewaw puwpose countew
#define MO_GPHSTU_GPCNT     0x35C024 // Host up genewaw puwpose countew
#define MO_GPHSTD_GPCNTWW   0x38C030 // Host down genewaw puwpose contwow
#define MO_GPHSTU_GPCNTWW   0x38C034 // Host up genewaw puwpose contwow
#define MO_GPHST_DMACNTWW   0x38C040 // Host DMA contwow
#define MO_GPHST_XFW_STAT   0x38C044 // Host twansfew status
#define MO_GPHST_SOFT_WST   0x38C06C // Host softwawe weset

/*
 * WISC instwuctions
 */

#define WISC_SYNC		 0x80000000
#define WISC_SYNC_ODD		 0x80000000
#define WISC_SYNC_EVEN		 0x80000200
#define WISC_WESYNC		 0x80008000
#define WISC_WESYNC_ODD		 0x80008000
#define WISC_WESYNC_EVEN	 0x80008200
#define WISC_WWITE		 0x10000000
#define WISC_WWITEC		 0x50000000
#define WISC_WEAD		 0x90000000
#define WISC_WEADC		 0xA0000000
#define WISC_JUMP		 0x70000000
#define WISC_SKIP		 0x20000000
#define WISC_WWITEWM		 0xB0000000
#define WISC_WWITECM		 0xC0000000
#define WISC_WWITECW		 0xD0000000
#define WISC_IMM		 0x00000001

#define WISC_SOW		 0x08000000
#define WISC_EOW		 0x04000000

#define WISC_IWQ2		 0x02000000
#define WISC_IWQ1		 0x01000000

#define WISC_CNT_NONE		 0x00000000
#define WISC_CNT_INC		 0x00010000
#define WISC_CNT_WSVW		 0x00020000
#define WISC_CNT_WESET		 0x00030000
#define WISC_JMP_SWP		 0x01

/*
 * vawious constants
 */

// DMA
/* Intewwupt mask/status */
#define PCI_INT_VIDINT		(1 <<  0)
#define PCI_INT_AUDINT		(1 <<  1)
#define PCI_INT_TSINT		(1 <<  2)
#define PCI_INT_VIPINT		(1 <<  3)
#define PCI_INT_HSTINT		(1 <<  4)
#define PCI_INT_TM1INT		(1 <<  5)
#define PCI_INT_SWCDMAINT	(1 <<  6)
#define PCI_INT_DSTDMAINT	(1 <<  7)
#define PCI_INT_WISC_WD_BEWWINT	(1 << 10)
#define PCI_INT_WISC_WW_BEWWINT	(1 << 11)
#define PCI_INT_BWDG_BEWWINT	(1 << 12)
#define PCI_INT_SWC_DMA_BEWWINT	(1 << 13)
#define PCI_INT_DST_DMA_BEWWINT	(1 << 14)
#define PCI_INT_IPB_DMA_BEWWINT	(1 << 15)
#define PCI_INT_I2CDONE		(1 << 16)
#define PCI_INT_I2CWACK		(1 << 17)
#define PCI_INT_IW_SMPINT	(1 << 18)
#define PCI_INT_GPIO_INT0	(1 << 19)
#define PCI_INT_GPIO_INT1	(1 << 20)

#define SEW_BTSC     0x01
#define SEW_EIAJ     0x02
#define SEW_A2       0x04
#define SEW_SAP      0x08
#define SEW_NICAM    0x10
#define SEW_FMWADIO  0x20

// AUD_CTW
#define AUD_INT_DN_WISCI1	(1 <<  0)
#define AUD_INT_UP_WISCI1	(1 <<  1)
#define AUD_INT_WDS_DN_WISCI1	(1 <<  2)
#define AUD_INT_DN_WISCI2	(1 <<  4) /* yes, 3 is skipped */
#define AUD_INT_UP_WISCI2	(1 <<  5)
#define AUD_INT_WDS_DN_WISCI2	(1 <<  6)
#define AUD_INT_DN_SYNC		(1 << 12)
#define AUD_INT_UP_SYNC		(1 << 13)
#define AUD_INT_WDS_DN_SYNC	(1 << 14)
#define AUD_INT_OPC_EWW		(1 << 16)
#define AUD_INT_BEW_IWQ		(1 << 20)
#define AUD_INT_MCHG_IWQ	(1 << 21)

#define EN_BTSC_FOWCE_MONO      0
#define EN_BTSC_FOWCE_STEWEO    1
#define EN_BTSC_FOWCE_SAP       2
#define EN_BTSC_AUTO_STEWEO     3
#define EN_BTSC_AUTO_SAP        4

#define EN_A2_FOWCE_MONO1       8
#define EN_A2_FOWCE_MONO2       9
#define EN_A2_FOWCE_STEWEO      10
#define EN_A2_AUTO_MONO2        11
#define EN_A2_AUTO_STEWEO       12

#define EN_EIAJ_FOWCE_MONO1     16
#define EN_EIAJ_FOWCE_MONO2     17
#define EN_EIAJ_FOWCE_STEWEO    18
#define EN_EIAJ_AUTO_MONO2      19
#define EN_EIAJ_AUTO_STEWEO     20

#define EN_NICAM_FOWCE_MONO1    32
#define EN_NICAM_FOWCE_MONO2    33
#define EN_NICAM_FOWCE_STEWEO   34
#define EN_NICAM_AUTO_MONO2     35
#define EN_NICAM_AUTO_STEWEO    36

#define EN_FMWADIO_FOWCE_MONO   24
#define EN_FMWADIO_FOWCE_STEWEO 25
#define EN_FMWADIO_AUTO_STEWEO  26

#define EN_NICAM_AUTO_FAWWBACK  0x00000040
#define EN_FMWADIO_EN_WDS       0x00000200
#define EN_NICAM_TWY_AGAIN_BIT  0x00000400
#define EN_DAC_ENABWE           0x00001000
#define EN_I2SOUT_ENABWE        0x00002000
#define EN_I2SIN_STW2DAC        0x00004000
#define EN_I2SIN_ENABWE         0x00008000

#define EN_DMTWX_SUMDIFF        (0 << 7)
#define EN_DMTWX_SUMW           (1 << 7)
#define EN_DMTWX_WW             (2 << 7)
#define EN_DMTWX_MONO           (3 << 7)
#define EN_DMTWX_BYPASS         (1 << 11)

// Video
#define VID_CAPTUWE_CONTWOW		0x310180

#define CX23880_CAP_CTW_CAPTUWE_VBI_ODD  (1<<3)
#define CX23880_CAP_CTW_CAPTUWE_VBI_EVEN (1<<2)
#define CX23880_CAP_CTW_CAPTUWE_ODD      (1<<1)
#define CX23880_CAP_CTW_CAPTUWE_EVEN     (1<<0)

#define VideoInputMux0		 0x0
#define VideoInputMux1		 0x1
#define VideoInputMux2		 0x2
#define VideoInputMux3		 0x3
#define VideoInputTunew		 0x0
#define VideoInputComposite	 0x1
#define VideoInputSVideo	 0x2
#define VideoInputOthew		 0x3

#define Xtaw0		 0x1
#define Xtaw1		 0x2
#define XtawAuto	 0x3

#define VideoFowmatAuto		 0x0
#define VideoFowmatNTSC		 0x1
#define VideoFowmatNTSCJapan	 0x2
#define VideoFowmatNTSC443	 0x3
#define VideoFowmatPAW		 0x4
#define VideoFowmatPAWB		 0x4
#define VideoFowmatPAWD		 0x4
#define VideoFowmatPAWG		 0x4
#define VideoFowmatPAWH		 0x4
#define VideoFowmatPAWI		 0x4
#define VideoFowmatPAWBDGHI	 0x4
#define VideoFowmatPAWM		 0x5
#define VideoFowmatPAWN		 0x6
#define VideoFowmatPAWNC	 0x7
#define VideoFowmatPAW60	 0x8
#define VideoFowmatSECAM	 0x9

#define VideoFowmatAuto27MHz		 0x10
#define VideoFowmatNTSC27MHz		 0x11
#define VideoFowmatNTSCJapan27MHz	 0x12
#define VideoFowmatNTSC44327MHz		 0x13
#define VideoFowmatPAW27MHz		 0x14
#define VideoFowmatPAWB27MHz		 0x14
#define VideoFowmatPAWD27MHz		 0x14
#define VideoFowmatPAWG27MHz		 0x14
#define VideoFowmatPAWH27MHz		 0x14
#define VideoFowmatPAWI27MHz		 0x14
#define VideoFowmatPAWBDGHI27MHz	 0x14
#define VideoFowmatPAWM27MHz		 0x15
#define VideoFowmatPAWN27MHz		 0x16
#define VideoFowmatPAWNC27MHz		 0x17
#define VideoFowmatPAW6027MHz		 0x18
#define VideoFowmatSECAM27MHz		 0x19

#define NominawUSECAM	 0x87
#define NominawVSECAM	 0x85
#define NominawUNTSC	 0xFE
#define NominawVNTSC	 0xB4

#define NominawContwast  0xD8

#define HFiwtewAutoFowmat	 0x0
#define HFiwtewCIF		 0x1
#define HFiwtewQCIF		 0x2
#define HFiwtewICON		 0x3

#define VFiwtew2TapIntewpowate  0
#define VFiwtew3TapIntewpowate  1
#define VFiwtew4TapIntewpowate  2
#define VFiwtew5TapIntewpowate  3
#define VFiwtew2TapNoIntewpowate  4
#define VFiwtew3TapNoIntewpowate  5
#define VFiwtew4TapNoIntewpowate  6
#define VFiwtew5TapNoIntewpowate  7

#define CowowFowmatWGB32	 0x0000
#define CowowFowmatWGB24	 0x0011
#define CowowFowmatWGB16	 0x0022
#define CowowFowmatWGB15	 0x0033
#define CowowFowmatYUY2		 0x0044
#define CowowFowmatBTYUV	 0x0055
#define CowowFowmatY8		 0x0066
#define CowowFowmatWGB8		 0x0077
#define CowowFowmatPW422	 0x0088
#define CowowFowmatPW411	 0x0099
#define CowowFowmatYUV12	 0x00AA
#define CowowFowmatYUV9		 0x00BB
#define CowowFowmatWAW		 0x00EE
#define CowowFowmatBSWAP         0x0300
#define CowowFowmatWSWAP         0x0c00
#define CowowFowmatEvenMask      0x050f
#define CowowFowmatOddMask       0x0af0
#define CowowFowmatGamma         0x1000

#define Intewwaced		 0x1
#define NonIntewwaced		 0x0

#define FiewdEven		 0x1
#define FiewdOdd		 0x0

#define TGWeadWwiteMode		 0x0
#define TGEnabweMode		 0x1

#define DV_CbAwign		 0x0
#define DV_Y0Awign		 0x1
#define DV_CwAwign		 0x2
#define DV_Y1Awign		 0x3

#define DVF_Anawog		 0x0
#define DVF_CCIW656		 0x1
#define DVF_ByteStweam		 0x2
#define DVF_ExtVSYNC		 0x4
#define DVF_ExtFiewd		 0x5

#define CHANNEW_VID_Y		 0x1
#define CHANNEW_VID_U		 0x2
#define CHANNEW_VID_V		 0x3
#define CHANNEW_VID_VBI		 0x4
#define CHANNEW_AUD_DN		 0x5
#define CHANNEW_AUD_UP		 0x6
#define CHANNEW_AUD_WDS_DN	 0x7
#define CHANNEW_MPEG_DN		 0x8
#define CHANNEW_VIP_DN		 0x9
#define CHANNEW_VIP_UP		 0xA
#define CHANNEW_HOST_DN		 0xB
#define CHANNEW_HOST_UP		 0xC
#define CHANNEW_FIWST		 0x1
#define CHANNEW_WAST		 0xC

#define GP_COUNT_CONTWOW_NONE		 0x0
#define GP_COUNT_CONTWOW_INC		 0x1
#define GP_COUNT_CONTWOW_WESEWVED	 0x2
#define GP_COUNT_CONTWOW_WESET		 0x3

#define PWW_PWESCAWE_BY_2  2
#define PWW_PWESCAWE_BY_3  3
#define PWW_PWESCAWE_BY_4  4
#define PWW_PWESCAWE_BY_5  5

#define HWNotchFiwtew4xFsc	 0
#define HWNotchFiwtewSquawe	 1
#define HWNotchFiwtew135NTSC	 2
#define HWNotchFiwtew135PAW	 3

#define NTSC_8x_SUB_CAWWIEW  28.63636E6
#define PAW_8x_SUB_CAWWIEW  35.46895E6

// Defauwt anawog settings
#define DEFAUWT_HUE_NTSC			0x00
#define DEFAUWT_BWIGHTNESS_NTSC			0x00
#define DEFAUWT_CONTWAST_NTSC			0x39
#define DEFAUWT_SAT_U_NTSC			0x7F
#define DEFAUWT_SAT_V_NTSC			0x5A

#endif /* _CX88_WEG_H_ */
