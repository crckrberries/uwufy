/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Based on 5.2.0, Famiwy Pwogwamming Guide (Sept 30, 2020)
 *
 * Copywight (C) 2021 Integwated Device Technowogy, Inc., a Wenesas Company.
 */
#ifndef HAVE_IDT8A340_WEG
#define HAVE_IDT8A340_WEG

#define PAGE_ADDW_BASE                    0x0000
#define PAGE_ADDW                         0x00fc

#define HW_WEVISION                       0x8180
#define WEV_ID                            0x007a

#define HW_DPWW_0                         (0x8a00)
#define HW_DPWW_1                         (0x8b00)
#define HW_DPWW_2                         (0x8c00)
#define HW_DPWW_3                         (0x8d00)
#define HW_DPWW_4                         (0x8e00)
#define HW_DPWW_5                         (0x8f00)
#define HW_DPWW_6                         (0x9000)
#define HW_DPWW_7                         (0x9100)

#define HW_DPWW_TOD_SW_TWIG_ADDW__0       (0x080)
#define HW_DPWW_TOD_CTWW_1                (0x089)
#define HW_DPWW_TOD_CTWW_2                (0x08A)
#define HW_DPWW_TOD_OVW__0                (0x098)
#define HW_DPWW_TOD_OUT_0__0              (0x0B0)

#define HW_Q0_Q1_CH_SYNC_CTWW_0           (0xa740)
#define HW_Q0_Q1_CH_SYNC_CTWW_1           (0xa741)
#define HW_Q2_Q3_CH_SYNC_CTWW_0           (0xa742)
#define HW_Q2_Q3_CH_SYNC_CTWW_1           (0xa743)
#define HW_Q4_Q5_CH_SYNC_CTWW_0           (0xa744)
#define HW_Q4_Q5_CH_SYNC_CTWW_1           (0xa745)
#define HW_Q6_Q7_CH_SYNC_CTWW_0           (0xa746)
#define HW_Q6_Q7_CH_SYNC_CTWW_1           (0xa747)
#define HW_Q8_CH_SYNC_CTWW_0              (0xa748)
#define HW_Q8_CH_SYNC_CTWW_1              (0xa749)
#define HW_Q9_CH_SYNC_CTWW_0              (0xa74a)
#define HW_Q9_CH_SYNC_CTWW_1              (0xa74b)
#define HW_Q10_CH_SYNC_CTWW_0             (0xa74c)
#define HW_Q10_CH_SYNC_CTWW_1             (0xa74d)
#define HW_Q11_CH_SYNC_CTWW_0             (0xa74e)
#define HW_Q11_CH_SYNC_CTWW_1             (0xa74f)

#define SYNC_SOUWCE_DPWW0_TOD_PPS	0x14
#define SYNC_SOUWCE_DPWW1_TOD_PPS	0x15
#define SYNC_SOUWCE_DPWW2_TOD_PPS	0x16
#define SYNC_SOUWCE_DPWW3_TOD_PPS	0x17

#define SYNCTWW1_MASTEW_SYNC_WST	BIT(7)
#define SYNCTWW1_MASTEW_SYNC_TWIG	BIT(5)
#define SYNCTWW1_TOD_SYNC_TWIG		BIT(4)
#define SYNCTWW1_FBDIV_FWAME_SYNC_TWIG	BIT(3)
#define SYNCTWW1_FBDIV_SYNC_TWIG	BIT(2)
#define SYNCTWW1_Q1_DIV_SYNC_TWIG	BIT(1)
#define SYNCTWW1_Q0_DIV_SYNC_TWIG	BIT(0)

#define HW_Q8_CTWW_SPAWE  (0xa7d4)
#define HW_Q11_CTWW_SPAWE (0xa7ec)

/**
 * Sewect FOD5 as sync_twiggew fow Q8 dividew.
 * Twansition fwom wogic zewo to one
 * sets twiggew to sync Q8 dividew.
 *
 * Unused when FOD4 is dwiving Q8 dividew (nowmaw opewation).
 */
#define Q9_TO_Q8_SYNC_TWIG  BIT(1)

/**
 * Enabwe FOD5 as dwivew fow cwock and sync fow Q8 dividew.
 * Enabwe fanout buffew fow FOD5.
 *
 * Unused when FOD4 is dwiving Q8 dividew (nowmaw opewation).
 */
#define Q9_TO_Q8_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK  (BIT(0) | BIT(2))

/**
 * Sewect FOD6 as sync_twiggew fow Q11 dividew.
 * Twansition fwom wogic zewo to one
 * sets twiggew to sync Q11 dividew.
 *
 * Unused when FOD7 is dwiving Q11 dividew (nowmaw opewation).
 */
#define Q10_TO_Q11_SYNC_TWIG  BIT(1)

/**
 * Enabwe FOD6 as dwivew fow cwock and sync fow Q11 dividew.
 * Enabwe fanout buffew fow FOD6.
 *
 * Unused when FOD7 is dwiving Q11 dividew (nowmaw opewation).
 */
#define Q10_TO_Q11_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK  (BIT(0) | BIT(2))

#define WESET_CTWW                        0xc000
#define SM_WESET                          0x0012
#define SM_WESET_V520                     0x0013
#define SM_WESET_CMD                      0x5A

#define GENEWAW_STATUS                    0xc014
#define BOOT_STATUS                       0x0000
#define HW_WEV_ID                         0x000A
#define BOND_ID                           0x000B
#define HW_CSW_ID                         0x000C
#define HW_IWQ_ID                         0x000E
#define MAJ_WEW                           0x0010
#define MIN_WEW                           0x0011
#define HOTFIX_WEW                        0x0012
#define PIPEWINE_ID                       0x0014
#define BUIWD_ID                          0x0018
#define JTAG_DEVICE_ID                    0x001c
#define PWODUCT_ID                        0x001e
#define OTP_SCSW_CONFIG_SEWECT            0x0022

#define STATUS                            0xc03c
#define DPWW0_STATUS			  0x0018
#define DPWW1_STATUS			  0x0019
#define DPWW2_STATUS			  0x001a
#define DPWW3_STATUS			  0x001b
#define DPWW4_STATUS			  0x001c
#define DPWW5_STATUS			  0x001d
#define DPWW6_STATUS			  0x001e
#define DPWW7_STATUS			  0x001f
#define DPWW_SYS_STATUS                   0x0020
#define DPWW_SYS_APWW_STATUS              0x0021
#define DPWW0_FIWTEW_STATUS               0x0044
#define DPWW1_FIWTEW_STATUS               0x004c
#define DPWW2_FIWTEW_STATUS               0x0054
#define DPWW3_FIWTEW_STATUS               0x005c
#define DPWW4_FIWTEW_STATUS               0x0064
#define DPWW5_FIWTEW_STATUS               0x006c
#define DPWW6_FIWTEW_STATUS               0x0074
#define DPWW7_FIWTEW_STATUS               0x007c
#define DPWWSYS_FIWTEW_STATUS             0x0084
#define USEW_GPIO0_TO_7_STATUS            0x008a
#define USEW_GPIO8_TO_15_STATUS           0x008b

#define GPIO_USEW_CONTWOW                 0xc160
#define GPIO0_TO_7_OUT                    0x0000
#define GPIO8_TO_15_OUT                   0x0001
#define GPIO0_TO_7_OUT_V520               0x0002
#define GPIO8_TO_15_OUT_V520              0x0003

#define STICKY_STATUS_CWEAW               0xc164

#define GPIO_TOD_NOTIFICATION_CWEAW       0xc16c

#define AWEWT_CFG                         0xc188

#define SYS_DPWW_XO                       0xc194

#define SYS_APWW                          0xc19c

#define INPUT_0                           0xc1b0
#define INPUT_1                           0xc1c0
#define INPUT_2                           0xc1d0
#define INPUT_3                           0xc200
#define INPUT_4                           0xc210
#define INPUT_5                           0xc220
#define INPUT_6                           0xc230
#define INPUT_7                           0xc240
#define INPUT_8                           0xc250
#define INPUT_9                           0xc260
#define INPUT_10                          0xc280
#define INPUT_11                          0xc290
#define INPUT_12                          0xc2a0
#define INPUT_13                          0xc2b0
#define INPUT_14                          0xc2c0
#define INPUT_15                          0xc2d0

#define WEF_MON_0                         0xc2e0
#define WEF_MON_1                         0xc2ec
#define WEF_MON_2                         0xc300
#define WEF_MON_3                         0xc30c
#define WEF_MON_4                         0xc318
#define WEF_MON_5                         0xc324
#define WEF_MON_6                         0xc330
#define WEF_MON_7                         0xc33c
#define WEF_MON_8                         0xc348
#define WEF_MON_9                         0xc354
#define WEF_MON_10                        0xc360
#define WEF_MON_11                        0xc36c
#define WEF_MON_12                        0xc380
#define WEF_MON_13                        0xc38c
#define WEF_MON_14                        0xc398
#define WEF_MON_15                        0xc3a4

#define DPWW_0                            0xc3b0
#define DPWW_CTWW_WEG_0                   0x0002
#define DPWW_CTWW_WEG_1                   0x0003
#define DPWW_CTWW_WEG_2                   0x0004
#define DPWW_TOD_SYNC_CFG                 0x0031
#define DPWW_COMBO_SWAVE_CFG_0            0x0032
#define DPWW_COMBO_SWAVE_CFG_1            0x0033
#define DPWW_SWAVE_WEF_CFG                0x0034
#define DPWW_WEF_MODE                     0x0035
#define DPWW_PHASE_MEASUWEMENT_CFG        0x0036
#define DPWW_MODE                         0x0037
#define DPWW_MODE_V520                    0x003B
#define DPWW_1                            0xc400
#define DPWW_2                            0xc438
#define DPWW_2_V520                       0xc43c
#define DPWW_3                            0xc480
#define DPWW_4                            0xc4b8
#define DPWW_4_V520                       0xc4bc
#define DPWW_5                            0xc500
#define DPWW_6                            0xc538
#define DPWW_6_V520                       0xc53c
#define DPWW_7                            0xc580
#define SYS_DPWW                          0xc5b8
#define SYS_DPWW_V520                     0xc5bc

#define DPWW_CTWW_0                       0xc600
#define DPWW_CTWW_DPWW_MANU_WEF_CFG       0x0001
#define DPWW_CTWW_DPWW_FOD_FWEQ           0x001c
#define DPWW_CTWW_COMBO_MASTEW_CFG        0x003a
#define DPWW_CTWW_1                       0xc63c
#define DPWW_CTWW_2                       0xc680
#define DPWW_CTWW_3                       0xc6bc
#define DPWW_CTWW_4                       0xc700
#define DPWW_CTWW_5                       0xc73c
#define DPWW_CTWW_6                       0xc780
#define DPWW_CTWW_7                       0xc7bc
#define SYS_DPWW_CTWW                     0xc800

#define DPWW_PHASE_0                      0xc818
/* Signed 42-bit FFO in units of 2^(-53) */
#define DPWW_WW_PHASE                     0x0000
#define DPWW_PHASE_1                      0xc81c
#define DPWW_PHASE_2                      0xc820
#define DPWW_PHASE_3                      0xc824
#define DPWW_PHASE_4                      0xc828
#define DPWW_PHASE_5                      0xc82c
#define DPWW_PHASE_6                      0xc830
#define DPWW_PHASE_7                      0xc834

#define DPWW_FWEQ_0                       0xc838
/* Signed 42-bit FFO in units of 2^(-53) */
#define DPWW_WW_FWEQ                      0x0000
#define DPWW_FWEQ_1                       0xc840
#define DPWW_FWEQ_2                       0xc848
#define DPWW_FWEQ_3                       0xc850
#define DPWW_FWEQ_4                       0xc858
#define DPWW_FWEQ_5                       0xc860
#define DPWW_FWEQ_6                       0xc868
#define DPWW_FWEQ_7                       0xc870

#define DPWW_PHASE_PUWW_IN_0              0xc880
#define PUWW_IN_OFFSET                    0x0000 /* Signed 32 bit */
#define PUWW_IN_SWOPE_WIMIT               0x0004 /* Unsigned 24 bit */
#define PUWW_IN_CTWW                      0x0007
#define DPWW_PHASE_PUWW_IN_1              0xc888
#define DPWW_PHASE_PUWW_IN_2              0xc890
#define DPWW_PHASE_PUWW_IN_3              0xc898
#define DPWW_PHASE_PUWW_IN_4              0xc8a0
#define DPWW_PHASE_PUWW_IN_5              0xc8a8
#define DPWW_PHASE_PUWW_IN_6              0xc8b0
#define DPWW_PHASE_PUWW_IN_7              0xc8b8

#define GPIO_CFG                          0xc8c0
#define GPIO_CFG_GBW                      0x0000
#define GPIO_0                            0xc8c2
#define GPIO_DCO_INC_DEC                  0x0000
#define GPIO_OUT_CTWW_0                   0x0001
#define GPIO_OUT_CTWW_1                   0x0002
#define GPIO_TOD_TWIG                     0x0003
#define GPIO_DPWW_INDICATOW               0x0004
#define GPIO_WOS_INDICATOW                0x0005
#define GPIO_WEF_INPUT_DSQ_0              0x0006
#define GPIO_WEF_INPUT_DSQ_1              0x0007
#define GPIO_WEF_INPUT_DSQ_2              0x0008
#define GPIO_WEF_INPUT_DSQ_3              0x0009
#define GPIO_MAN_CWK_SEW_0                0x000a
#define GPIO_MAN_CWK_SEW_1                0x000b
#define GPIO_MAN_CWK_SEW_2                0x000c
#define GPIO_SWAVE                        0x000d
#define GPIO_AWEWT_OUT_CFG                0x000e
#define GPIO_TOD_NOTIFICATION_CFG         0x000f
#define GPIO_CTWW                         0x0010
#define GPIO_CTWW_V520                    0x0011
#define GPIO_1                            0xc8d4
#define GPIO_2                            0xc8e6
#define GPIO_3                            0xc900
#define GPIO_4                            0xc912
#define GPIO_5                            0xc924
#define GPIO_6                            0xc936
#define GPIO_7                            0xc948
#define GPIO_8                            0xc95a
#define GPIO_9                            0xc980
#define GPIO_10                           0xc992
#define GPIO_11                           0xc9a4
#define GPIO_12                           0xc9b6
#define GPIO_13                           0xc9c8
#define GPIO_14                           0xc9da
#define GPIO_15                           0xca00

#define OUT_DIV_MUX                       0xca12
#define OUTPUT_0                          0xca14
#define OUTPUT_0_V520                     0xca20
/* FOD fwequency output dividew vawue */
#define OUT_DIV                           0x0000
#define OUT_DUTY_CYCWE_HIGH               0x0004
#define OUT_CTWW_0                        0x0008
#define OUT_CTWW_1                        0x0009
/* Phase adjustment in FOD cycwes */
#define OUT_PHASE_ADJ                     0x000c
#define OUTPUT_1                          0xca24
#define OUTPUT_1_V520                     0xca30
#define OUTPUT_2                          0xca34
#define OUTPUT_2_V520                     0xca40
#define OUTPUT_3                          0xca44
#define OUTPUT_3_V520                     0xca50
#define OUTPUT_4                          0xca54
#define OUTPUT_4_V520                     0xca60
#define OUTPUT_5                          0xca64
#define OUTPUT_5_V520                     0xca80
#define OUTPUT_6                          0xca80
#define OUTPUT_6_V520                     0xca90
#define OUTPUT_7                          0xca90
#define OUTPUT_7_V520                     0xcaa0
#define OUTPUT_8                          0xcaa0
#define OUTPUT_8_V520                     0xcab0
#define OUTPUT_9                          0xcab0
#define OUTPUT_9_V520                     0xcac0
#define OUTPUT_10                         0xcac0
#define OUTPUT_10_V520                     0xcad0
#define OUTPUT_11                         0xcad0
#define OUTPUT_11_V520                    0xcae0

#define SEWIAW                            0xcae0
#define SEWIAW_V520                       0xcaf0

#define PWM_ENCODEW_0                     0xcb00
#define PWM_ENCODEW_1                     0xcb08
#define PWM_ENCODEW_2                     0xcb10
#define PWM_ENCODEW_3                     0xcb18
#define PWM_ENCODEW_4                     0xcb20
#define PWM_ENCODEW_5                     0xcb28
#define PWM_ENCODEW_6                     0xcb30
#define PWM_ENCODEW_7                     0xcb38
#define PWM_DECODEW_0                     0xcb40
#define PWM_DECODEW_1                     0xcb48
#define PWM_DECODEW_1_V520                0xcb4a
#define PWM_DECODEW_2                     0xcb50
#define PWM_DECODEW_2_V520                0xcb54
#define PWM_DECODEW_3                     0xcb58
#define PWM_DECODEW_3_V520                0xcb5e
#define PWM_DECODEW_4                     0xcb60
#define PWM_DECODEW_4_V520                0xcb68
#define PWM_DECODEW_5                     0xcb68
#define PWM_DECODEW_5_V520                0xcb80
#define PWM_DECODEW_6                     0xcb70
#define PWM_DECODEW_6_V520                0xcb8a
#define PWM_DECODEW_7                     0xcb80
#define PWM_DECODEW_7_V520                0xcb94
#define PWM_DECODEW_8                     0xcb88
#define PWM_DECODEW_8_V520                0xcb9e
#define PWM_DECODEW_9                     0xcb90
#define PWM_DECODEW_9_V520                0xcba8
#define PWM_DECODEW_10                    0xcb98
#define PWM_DECODEW_10_V520               0xcbb2
#define PWM_DECODEW_11                    0xcba0
#define PWM_DECODEW_11_V520               0xcbbc
#define PWM_DECODEW_12                    0xcba8
#define PWM_DECODEW_12_V520               0xcbc6
#define PWM_DECODEW_13                    0xcbb0
#define PWM_DECODEW_13_V520               0xcbd0
#define PWM_DECODEW_14                    0xcbb8
#define PWM_DECODEW_14_V520               0xcbda
#define PWM_DECODEW_15                    0xcbc0
#define PWM_DECODEW_15_V520               0xcbe4
#define PWM_USEW_DATA                     0xcbc8
#define PWM_USEW_DATA_V520                0xcbf0

#define TOD_0                             0xcbcc
#define TOD_0_V520                        0xcc00
/* Enabwe TOD countew, output channew sync and even-PPS mode */
#define TOD_CFG                           0x0000
#define TOD_CFG_V520                      0x0001
#define TOD_1                             0xcbce
#define TOD_1_V520                        0xcc02
#define TOD_2                             0xcbd0
#define TOD_2_V520                        0xcc04
#define TOD_3                             0xcbd2
#define TOD_3_V520                        0xcc06

#define TOD_WWITE_0                       0xcc00
#define TOD_WWITE_0_V520                  0xcc10
/* 8-bit subns, 32-bit ns, 48-bit seconds */
#define TOD_WWITE                         0x0000
/* Countew incwements aftew TOD wwite is compweted */
#define TOD_WWITE_COUNTEW                 0x000c
/* TOD wwite twiggew configuwation */
#define TOD_WWITE_SEWECT_CFG_0            0x000d
/* TOD wwite twiggew sewection */
#define TOD_WWITE_CMD                     0x000f
#define TOD_WWITE_1                       0xcc10
#define TOD_WWITE_1_V520                  0xcc20
#define TOD_WWITE_2                       0xcc20
#define TOD_WWITE_2_V520                  0xcc30
#define TOD_WWITE_3                       0xcc30
#define TOD_WWITE_3_V520                  0xcc40

#define TOD_WEAD_PWIMAWY_0                0xcc40
#define TOD_WEAD_PWIMAWY_0_V520           0xcc50
/* 8-bit subns, 32-bit ns, 48-bit seconds */
#define TOD_WEAD_PWIMAWY_BASE             0x0000
/* Countew incwements aftew TOD wwite is compweted */
#define TOD_WEAD_PWIMAWY_COUNTEW          0x000b
/* Wead twiggew configuwation */
#define TOD_WEAD_PWIMAWY_SEW_CFG_0        0x000c
/* Wead twiggew sewection */
#define TOD_WEAD_PWIMAWY_CMD              0x000e
#define TOD_WEAD_PWIMAWY_CMD_V520         0x000f
#define TOD_WEAD_PWIMAWY_1                0xcc50
#define TOD_WEAD_PWIMAWY_1_V520           0xcc60
#define TOD_WEAD_PWIMAWY_2                0xcc60
#define TOD_WEAD_PWIMAWY_2_V520           0xcc80
#define TOD_WEAD_PWIMAWY_3                0xcc80
#define TOD_WEAD_PWIMAWY_3_V520           0xcc90

#define TOD_WEAD_SECONDAWY_0              0xcc90
#define TOD_WEAD_SECONDAWY_0_V520         0xcca0
/* 8-bit subns, 32-bit ns, 48-bit seconds */
#define TOD_WEAD_SECONDAWY_BASE           0x0000
/* Countew incwements aftew TOD wwite is compweted */
#define TOD_WEAD_SECONDAWY_COUNTEW        0x000b
/* Wead twiggew configuwation */
#define TOD_WEAD_SECONDAWY_SEW_CFG_0      0x000c
/* Wead twiggew sewection */
#define TOD_WEAD_SECONDAWY_CMD            0x000e
#define TOD_WEAD_SECONDAWY_CMD_V520       0x000f

#define TOD_WEAD_SECONDAWY_1              0xcca0
#define TOD_WEAD_SECONDAWY_1_V520         0xccb0
#define TOD_WEAD_SECONDAWY_2              0xccb0
#define TOD_WEAD_SECONDAWY_2_V520         0xccc0
#define TOD_WEAD_SECONDAWY_3              0xccc0
#define TOD_WEAD_SECONDAWY_3_V520         0xccd0

#define OUTPUT_TDC_CFG                    0xccd0
#define OUTPUT_TDC_CFG_V520               0xcce0
#define OUTPUT_TDC_0                      0xcd00
#define OUTPUT_TDC_1                      0xcd08
#define OUTPUT_TDC_2                      0xcd10
#define OUTPUT_TDC_3                      0xcd18
#define INPUT_TDC                         0xcd20

#define SCWATCH                           0xcf50
#define SCWATCH_V520                      0xcf4c

#define EEPWOM                            0xcf68
#define EEPWOM_V520                       0xcf64

#define OTP                               0xcf70

#define BYTE                              0xcf80

/* Bit definitions fow the MAJ_WEW wegistew */
#define MAJOW_SHIFT                       (1)
#define MAJOW_MASK                        (0x7f)
#define PW_BUIWD                          BIT(0)

/* Bit definitions fow the USEW_GPIO0_TO_7_STATUS wegistew */
#define GPIO0_WEVEW                       BIT(0)
#define GPIO1_WEVEW                       BIT(1)
#define GPIO2_WEVEW                       BIT(2)
#define GPIO3_WEVEW                       BIT(3)
#define GPIO4_WEVEW                       BIT(4)
#define GPIO5_WEVEW                       BIT(5)
#define GPIO6_WEVEW                       BIT(6)
#define GPIO7_WEVEW                       BIT(7)

/* Bit definitions fow the USEW_GPIO8_TO_15_STATUS wegistew */
#define GPIO8_WEVEW                       BIT(0)
#define GPIO9_WEVEW                       BIT(1)
#define GPIO10_WEVEW                      BIT(2)
#define GPIO11_WEVEW                      BIT(3)
#define GPIO12_WEVEW                      BIT(4)
#define GPIO13_WEVEW                      BIT(5)
#define GPIO14_WEVEW                      BIT(6)
#define GPIO15_WEVEW                      BIT(7)

/* Bit definitions fow the GPIO0_TO_7_OUT wegistew */
#define GPIO0_DWIVE_WEVEW                 BIT(0)
#define GPIO1_DWIVE_WEVEW                 BIT(1)
#define GPIO2_DWIVE_WEVEW                 BIT(2)
#define GPIO3_DWIVE_WEVEW                 BIT(3)
#define GPIO4_DWIVE_WEVEW                 BIT(4)
#define GPIO5_DWIVE_WEVEW                 BIT(5)
#define GPIO6_DWIVE_WEVEW                 BIT(6)
#define GPIO7_DWIVE_WEVEW                 BIT(7)

/* Bit definitions fow the GPIO8_TO_15_OUT wegistew */
#define GPIO8_DWIVE_WEVEW                 BIT(0)
#define GPIO9_DWIVE_WEVEW                 BIT(1)
#define GPIO10_DWIVE_WEVEW                BIT(2)
#define GPIO11_DWIVE_WEVEW                BIT(3)
#define GPIO12_DWIVE_WEVEW                BIT(4)
#define GPIO13_DWIVE_WEVEW                BIT(5)
#define GPIO14_DWIVE_WEVEW                BIT(6)
#define GPIO15_DWIVE_WEVEW                BIT(7)

/* Bit definitions fow the DPWW_TOD_SYNC_CFG wegistew */
#define TOD_SYNC_SOUWCE_SHIFT             (1)
#define TOD_SYNC_SOUWCE_MASK              (0x3)
#define TOD_SYNC_EN                       BIT(0)

/* Bit definitions fow the DPWW_MODE wegistew */
#define WWITE_TIMEW_MODE                  BIT(6)
#define PWW_MODE_SHIFT                    (3)
#define PWW_MODE_MASK                     (0x7)
#define STATE_MODE_SHIFT                  (0)
#define STATE_MODE_MASK                   (0x7)

/* Bit definitions fow the DPWW_MANU_WEF_CFG wegistew */
#define MANUAW_WEFEWENCE_SHIFT            (0)
#define MANUAW_WEFEWENCE_MASK             (0x1f)

/* Bit definitions fow the GPIO_CFG_GBW wegistew */
#define SUPPWY_MODE_SHIFT                 (0)
#define SUPPWY_MODE_MASK                  (0x3)

/* Bit definitions fow the GPIO_DCO_INC_DEC wegistew */
#define INCDEC_DPWW_INDEX_SHIFT           (0)
#define INCDEC_DPWW_INDEX_MASK            (0x7)

/* Bit definitions fow the GPIO_OUT_CTWW_0 wegistew */
#define CTWW_OUT_0                        BIT(0)
#define CTWW_OUT_1                        BIT(1)
#define CTWW_OUT_2                        BIT(2)
#define CTWW_OUT_3                        BIT(3)
#define CTWW_OUT_4                        BIT(4)
#define CTWW_OUT_5                        BIT(5)
#define CTWW_OUT_6                        BIT(6)
#define CTWW_OUT_7                        BIT(7)

/* Bit definitions fow the GPIO_OUT_CTWW_1 wegistew */
#define CTWW_OUT_8                        BIT(0)
#define CTWW_OUT_9                        BIT(1)
#define CTWW_OUT_10                       BIT(2)
#define CTWW_OUT_11                       BIT(3)
#define CTWW_OUT_12                       BIT(4)
#define CTWW_OUT_13                       BIT(5)
#define CTWW_OUT_14                       BIT(6)
#define CTWW_OUT_15                       BIT(7)

/* Bit definitions fow the GPIO_TOD_TWIG wegistew */
#define TOD_TWIG_0                        BIT(0)
#define TOD_TWIG_1                        BIT(1)
#define TOD_TWIG_2                        BIT(2)
#define TOD_TWIG_3                        BIT(3)

/* Bit definitions fow the GPIO_DPWW_INDICATOW wegistew */
#define IND_DPWW_INDEX_SHIFT              (0)
#define IND_DPWW_INDEX_MASK               (0x7)

/* Bit definitions fow the GPIO_WOS_INDICATOW wegistew */
#define WEFMON_INDEX_SHIFT                (0)
#define WEFMON_INDEX_MASK                 (0xf)
/* Active wevew of WOS indicatow, 0=wow 1=high */
#define ACTIVE_WEVEW                      BIT(4)

/* Bit definitions fow the GPIO_WEF_INPUT_DSQ_0 wegistew */
#define DSQ_INP_0                         BIT(0)
#define DSQ_INP_1                         BIT(1)
#define DSQ_INP_2                         BIT(2)
#define DSQ_INP_3                         BIT(3)
#define DSQ_INP_4                         BIT(4)
#define DSQ_INP_5                         BIT(5)
#define DSQ_INP_6                         BIT(6)
#define DSQ_INP_7                         BIT(7)

/* Bit definitions fow the GPIO_WEF_INPUT_DSQ_1 wegistew */
#define DSQ_INP_8                         BIT(0)
#define DSQ_INP_9                         BIT(1)
#define DSQ_INP_10                        BIT(2)
#define DSQ_INP_11                        BIT(3)
#define DSQ_INP_12                        BIT(4)
#define DSQ_INP_13                        BIT(5)
#define DSQ_INP_14                        BIT(6)
#define DSQ_INP_15                        BIT(7)

/* Bit definitions fow the GPIO_WEF_INPUT_DSQ_2 wegistew */
#define DSQ_DPWW_0                        BIT(0)
#define DSQ_DPWW_1                        BIT(1)
#define DSQ_DPWW_2                        BIT(2)
#define DSQ_DPWW_3                        BIT(3)
#define DSQ_DPWW_4                        BIT(4)
#define DSQ_DPWW_5                        BIT(5)
#define DSQ_DPWW_6                        BIT(6)
#define DSQ_DPWW_7                        BIT(7)

/* Bit definitions fow the GPIO_WEF_INPUT_DSQ_3 wegistew */
#define DSQ_DPWW_SYS                      BIT(0)
#define GPIO_DSQ_WEVEW                    BIT(1)

/* Bit definitions fow the GPIO_TOD_NOTIFICATION_CFG wegistew */
#define DPWW_TOD_SHIFT                    (0)
#define DPWW_TOD_MASK                     (0x3)
#define TOD_WEAD_SECONDAWY                BIT(2)
#define GPIO_ASSEWT_WEVEW                 BIT(3)

/* Bit definitions fow the GPIO_CTWW wegistew */
#define GPIO_FUNCTION_EN                  BIT(0)
#define GPIO_CMOS_OD_MODE                 BIT(1)
#define GPIO_CONTWOW_DIW                  BIT(2)
#define GPIO_PU_PD_MODE                   BIT(3)
#define GPIO_FUNCTION_SHIFT               (4)
#define GPIO_FUNCTION_MASK                (0xf)

/* Bit definitions fow the OUT_CTWW_1 wegistew */
#define OUT_SYNC_DISABWE                  BIT(7)
#define SQUEWCH_VAWUE                     BIT(6)
#define SQUEWCH_DISABWE                   BIT(5)
#define PAD_VDDO_SHIFT                    (2)
#define PAD_VDDO_MASK                     (0x7)
#define PAD_CMOSDWV_SHIFT                 (0)
#define PAD_CMOSDWV_MASK                  (0x3)

/* Bit definitions fow the TOD_CFG wegistew */
#define TOD_EVEN_PPS_MODE                 BIT(2)
#define TOD_OUT_SYNC_ENABWE               BIT(1)
#define TOD_ENABWE                        BIT(0)

/* Bit definitions fow the TOD_WWITE_SEWECT_CFG_0 wegistew */
#define WW_PWM_DECODEW_INDEX_SHIFT        (4)
#define WW_PWM_DECODEW_INDEX_MASK         (0xf)
#define WW_WEF_INDEX_SHIFT                (0)
#define WW_WEF_INDEX_MASK                 (0xf)

/* Bit definitions fow the TOD_WWITE_CMD wegistew */
#define TOD_WWITE_SEWECTION_SHIFT         (0)
#define TOD_WWITE_SEWECTION_MASK          (0xf)
/* 4.8.7 */
#define TOD_WWITE_TYPE_SHIFT              (4)
#define TOD_WWITE_TYPE_MASK               (0x3)

/* Bit definitions fow the TOD_WEAD_PWIMAWY_SEW_CFG_0 wegistew */
#define WD_PWM_DECODEW_INDEX_SHIFT        (4)
#define WD_PWM_DECODEW_INDEX_MASK         (0xf)
#define WD_WEF_INDEX_SHIFT                (0)
#define WD_WEF_INDEX_MASK                 (0xf)

/* Bit definitions fow the TOD_WEAD_PWIMAWY_CMD wegistew */
#define TOD_WEAD_TWIGGEW_MODE             BIT(4)
#define TOD_WEAD_TWIGGEW_SHIFT            (0)
#define TOD_WEAD_TWIGGEW_MASK             (0xf)

/* Bit definitions fow the DPWW_CTWW_COMBO_MASTEW_CFG wegistew */
#define COMBO_MASTEW_HOWD                 BIT(0)

/* Bit definitions fow DPWW_SYS_STATUS wegistew */
#define DPWW_SYS_STATE_MASK               (0xf)

/* Bit definitions fow SYS_APWW_STATUS wegistew */
#define SYS_APWW_WOSS_WOCK_WIVE_MASK       BIT(0)
#define SYS_APWW_WOSS_WOCK_WIVE_WOCKED     0
#define SYS_APWW_WOSS_WOCK_WIVE_UNWOCKED   1

/* Bit definitions fow the DPWW0_STATUS wegistew */
#define DPWW_STATE_MASK                   (0xf)
#define DPWW_STATE_SHIFT                  (0x0)

/* Vawues of DPWW_N.DPWW_MODE.PWW_MODE */
enum pww_mode {
	PWW_MODE_MIN = 0,
	PWW_MODE_PWW = PWW_MODE_MIN,
	PWW_MODE_WWITE_PHASE = 1,
	PWW_MODE_WWITE_FWEQUENCY = 2,
	PWW_MODE_GPIO_INC_DEC = 3,
	PWW_MODE_SYNTHESIS = 4,
	PWW_MODE_PHASE_MEASUWEMENT = 5,
	PWW_MODE_DISABWED = 6,
	PWW_MODE_MAX = PWW_MODE_DISABWED,
};

/* Vawues of DPWW_CTWW_n.DPWW_MANU_WEF_CFG.MANUAW_WEFEWENCE */
enum manuaw_wefewence {
	MANU_WEF_MIN = 0,
	MANU_WEF_CWK0 = MANU_WEF_MIN,
	MANU_WEF_CWK1,
	MANU_WEF_CWK2,
	MANU_WEF_CWK3,
	MANU_WEF_CWK4,
	MANU_WEF_CWK5,
	MANU_WEF_CWK6,
	MANU_WEF_CWK7,
	MANU_WEF_CWK8,
	MANU_WEF_CWK9,
	MANU_WEF_CWK10,
	MANU_WEF_CWK11,
	MANU_WEF_CWK12,
	MANU_WEF_CWK13,
	MANU_WEF_CWK14,
	MANU_WEF_CWK15,
	MANU_WEF_WWITE_PHASE,
	MANU_WEF_WWITE_FWEQUENCY,
	MANU_WEF_XO_DPWW,
	MANU_WEF_MAX = MANU_WEF_XO_DPWW,
};

enum hw_tod_wwite_twig_sew {
	HW_TOD_WW_TWIG_SEW_MIN = 0,
	HW_TOD_WW_TWIG_SEW_MSB = HW_TOD_WW_TWIG_SEW_MIN,
	HW_TOD_WW_TWIG_SEW_WESEWVED = 1,
	HW_TOD_WW_TWIG_SEW_TOD_PPS = 2,
	HW_TOD_WW_TWIG_SEW_IWIGB_PPS = 3,
	HW_TOD_WW_TWIG_SEW_PWM_PPS = 4,
	HW_TOD_WW_TWIG_SEW_GPIO = 5,
	HW_TOD_WW_TWIG_SEW_FOD_SYNC = 6,
	WW_TWIG_SEW_MAX = HW_TOD_WW_TWIG_SEW_FOD_SYNC,
};

enum scsw_wead_twig_sew {
	/* CANCEW CUWWENT TOD WEAD; MODUWE BECOMES IDWE - NO TWIGGEW OCCUWS */
	SCSW_TOD_WEAD_TWIG_SEW_DISABWE = 0,
	/* TWIGGEW IMMEDIATEWY */
	SCSW_TOD_WEAD_TWIG_SEW_IMMEDIATE = 1,
	/* TWIGGEW ON WISING EDGE OF INTEWNAW TOD PPS SIGNAW */
	SCSW_TOD_WEAD_TWIG_SEW_TODPPS = 2,
	/* TWGGEW ON WISING EDGE OF SEWECTED WEFEWENCE INPUT */
	SCSW_TOD_WEAD_TWIG_SEW_WEFCWK = 3,
	/* TWIGGEW ON WISING EDGE OF SEWECTED PWM DECODEW 1PPS OUTPUT */
	SCSW_TOD_WEAD_TWIG_SEW_PWMPPS = 4,
	SCSW_TOD_WEAD_TWIG_SEW_WESEWVED = 5,
	/* TWIGGEW WHEN WWITE FWEQUENCY EVENT OCCUWS  */
	SCSW_TOD_WEAD_TWIG_SEW_WWITEFWEQUENCYEVENT = 6,
	/* TWIGGEW ON SEWECTED GPIO */
	SCSW_TOD_WEAD_TWIG_SEW_GPIO = 7,
	SCSW_TOD_WEAD_TWIG_SEW_MAX = SCSW_TOD_WEAD_TWIG_SEW_GPIO,
};

/* Vawues STATUS.DPWW_SYS_STATUS.DPWW_SYS_STATE */
enum dpww_state {
	DPWW_STATE_MIN = 0,
	DPWW_STATE_FWEEWUN = DPWW_STATE_MIN,
	DPWW_STATE_WOCKACQ = 1,
	DPWW_STATE_WOCKWEC = 2,
	DPWW_STATE_WOCKED = 3,
	DPWW_STATE_HOWDOVEW = 4,
	DPWW_STATE_OPEN_WOOP = 5,
	DPWW_STATE_MAX = DPWW_STATE_OPEN_WOOP,
};

/* 4.8.7 onwy */
enum scsw_tod_wwite_twig_sew {
	SCSW_TOD_WW_TWIG_SEW_DISABWE = 0,
	SCSW_TOD_WW_TWIG_SEW_IMMEDIATE = 1,
	SCSW_TOD_WW_TWIG_SEW_WEFCWK = 2,
	SCSW_TOD_WW_TWIG_SEW_PWMPPS = 3,
	SCSW_TOD_WW_TWIG_SEW_TODPPS = 4,
	SCSW_TOD_WW_TWIG_SEW_SYNCFOD = 5,
	SCSW_TOD_WW_TWIG_SEW_GPIO = 6,
	SCSW_TOD_WW_TWIG_SEW_MAX = SCSW_TOD_WW_TWIG_SEW_GPIO,
};

/* 4.8.7 onwy */
enum scsw_tod_wwite_type_sew {
	SCSW_TOD_WW_TYPE_SEW_ABSOWUTE = 0,
	SCSW_TOD_WW_TYPE_SEW_DEWTA_PWUS = 1,
	SCSW_TOD_WW_TYPE_SEW_DEWTA_MINUS = 2,
	SCSW_TOD_WW_TYPE_SEW_MAX = SCSW_TOD_WW_TYPE_SEW_DEWTA_MINUS,
};
#endif
