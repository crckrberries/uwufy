/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DDK750_WEG_H__
#define DDK750_WEG_H__

/* New wegistew fow SM750WE */
#define DE_STATE1                                        0x100054
#define DE_STATE1_DE_ABOWT                               BIT(0)

#define DE_STATE2                                        0x100058
#define DE_STATE2_DE_FIFO_EMPTY                          BIT(3)
#define DE_STATE2_DE_STATUS_BUSY                         BIT(2)
#define DE_STATE2_DE_MEM_FIFO_EMPTY                      BIT(1)

#define SYSTEM_CTWW                                   0x000000
#define SYSTEM_CTWW_DPMS_MASK                         (0x3 << 30)
#define SYSTEM_CTWW_DPMS_VPHP                         (0x0 << 30)
#define SYSTEM_CTWW_DPMS_VPHN                         (0x1 << 30)
#define SYSTEM_CTWW_DPMS_VNHP                         (0x2 << 30)
#define SYSTEM_CTWW_DPMS_VNHN                         (0x3 << 30)
#define SYSTEM_CTWW_PCI_BUWST                         BIT(29)
#define SYSTEM_CTWW_PCI_MASTEW                        BIT(25)
#define SYSTEM_CTWW_WATENCY_TIMEW_OFF                 BIT(24)
#define SYSTEM_CTWW_DE_FIFO_EMPTY                     BIT(23)
#define SYSTEM_CTWW_DE_STATUS_BUSY                    BIT(22)
#define SYSTEM_CTWW_DE_MEM_FIFO_EMPTY                 BIT(21)
#define SYSTEM_CTWW_CSC_STATUS_BUSY                   BIT(20)
#define SYSTEM_CTWW_CWT_VSYNC_ACTIVE                  BIT(19)
#define SYSTEM_CTWW_PANEW_VSYNC_ACTIVE                BIT(18)
#define SYSTEM_CTWW_CUWWENT_BUFFEW_FWIP_PENDING       BIT(17)
#define SYSTEM_CTWW_DMA_STATUS_BUSY                   BIT(16)
#define SYSTEM_CTWW_PCI_BUWST_WEAD                    BIT(15)
#define SYSTEM_CTWW_DE_ABOWT                          BIT(13)
#define SYSTEM_CTWW_PCI_SUBSYS_ID_WOCK                BIT(11)
#define SYSTEM_CTWW_PCI_WETWY_OFF                     BIT(7)
#define SYSTEM_CTWW_PCI_SWAVE_BUWST_WEAD_SIZE_MASK    (0x3 << 4)
#define SYSTEM_CTWW_PCI_SWAVE_BUWST_WEAD_SIZE_1       (0x0 << 4)
#define SYSTEM_CTWW_PCI_SWAVE_BUWST_WEAD_SIZE_2       (0x1 << 4)
#define SYSTEM_CTWW_PCI_SWAVE_BUWST_WEAD_SIZE_4       (0x2 << 4)
#define SYSTEM_CTWW_PCI_SWAVE_BUWST_WEAD_SIZE_8       (0x3 << 4)
#define SYSTEM_CTWW_CWT_TWISTATE                      BIT(3)
#define SYSTEM_CTWW_PCIMEM_TWISTATE                   BIT(2)
#define SYSTEM_CTWW_WOCAWMEM_TWISTATE                 BIT(1)
#define SYSTEM_CTWW_PANEW_TWISTATE                    BIT(0)

#define MISC_CTWW                                     0x000004
#define MISC_CTWW_DWAM_WEWESH_COUNT                   BIT(27)
#define MISC_CTWW_DWAM_WEFWESH_TIME_MASK              (0x3 << 25)
#define MISC_CTWW_DWAM_WEFWESH_TIME_8                 (0x0 << 25)
#define MISC_CTWW_DWAM_WEFWESH_TIME_16                (0x1 << 25)
#define MISC_CTWW_DWAM_WEFWESH_TIME_32                (0x2 << 25)
#define MISC_CTWW_DWAM_WEFWESH_TIME_64                (0x3 << 25)
#define MISC_CTWW_INT_OUTPUT_INVEWT                   BIT(24)
#define MISC_CTWW_PWW_CWK_COUNT                       BIT(23)
#define MISC_CTWW_DAC_POWEW_OFF                       BIT(20)
#define MISC_CTWW_CWK_SEWECT_TESTCWK                  BIT(16)
#define MISC_CTWW_DWAM_COWUMN_SIZE_MASK               (0x3 << 14)
#define MISC_CTWW_DWAM_COWUMN_SIZE_256                (0x0 << 14)
#define MISC_CTWW_DWAM_COWUMN_SIZE_512                (0x1 << 14)
#define MISC_CTWW_DWAM_COWUMN_SIZE_1024               (0x2 << 14)
#define MISC_CTWW_WOCAWMEM_SIZE_MASK                  (0x3 << 12)
#define MISC_CTWW_WOCAWMEM_SIZE_8M                    (0x3 << 12)
#define MISC_CTWW_WOCAWMEM_SIZE_16M                   (0x0 << 12)
#define MISC_CTWW_WOCAWMEM_SIZE_32M                   (0x1 << 12)
#define MISC_CTWW_WOCAWMEM_SIZE_64M                   (0x2 << 12)
#define MISC_CTWW_DWAM_TWTW                           BIT(11)
#define MISC_CTWW_DWAM_TWW                            BIT(10)
#define MISC_CTWW_DWAM_TWP                            BIT(9)
#define MISC_CTWW_DWAM_TWFC                           BIT(8)
#define MISC_CTWW_DWAM_TWAS                           BIT(7)
#define MISC_CTWW_WOCAWMEM_WESET                      BIT(6)
#define MISC_CTWW_WOCAWMEM_STATE_INACTIVE             BIT(5)
#define MISC_CTWW_CPU_CAS_WATENCY                     BIT(4)
#define MISC_CTWW_DWW_OFF                             BIT(3)
#define MISC_CTWW_DWAM_OUTPUT_HIGH                    BIT(2)
#define MISC_CTWW_WOCAWMEM_BUS_SIZE                   BIT(1)
#define MISC_CTWW_EMBEDDED_WOCAWMEM_OFF               BIT(0)

#define GPIO_MUX                                      0x000008
#define GPIO_MUX_31                                   BIT(31)
#define GPIO_MUX_30                                   BIT(30)
#define GPIO_MUX_29                                   BIT(29)
#define GPIO_MUX_28                                   BIT(28)
#define GPIO_MUX_27                                   BIT(27)
#define GPIO_MUX_26                                   BIT(26)
#define GPIO_MUX_25                                   BIT(25)
#define GPIO_MUX_24                                   BIT(24)
#define GPIO_MUX_23                                   BIT(23)
#define GPIO_MUX_22                                   BIT(22)
#define GPIO_MUX_21                                   BIT(21)
#define GPIO_MUX_20                                   BIT(20)
#define GPIO_MUX_19                                   BIT(19)
#define GPIO_MUX_18                                   BIT(18)
#define GPIO_MUX_17                                   BIT(17)
#define GPIO_MUX_16                                   BIT(16)
#define GPIO_MUX_15                                   BIT(15)
#define GPIO_MUX_14                                   BIT(14)
#define GPIO_MUX_13                                   BIT(13)
#define GPIO_MUX_12                                   BIT(12)
#define GPIO_MUX_11                                   BIT(11)
#define GPIO_MUX_10                                   BIT(10)
#define GPIO_MUX_9                                    BIT(9)
#define GPIO_MUX_8                                    BIT(8)
#define GPIO_MUX_7                                    BIT(7)
#define GPIO_MUX_6                                    BIT(6)
#define GPIO_MUX_5                                    BIT(5)
#define GPIO_MUX_4                                    BIT(4)
#define GPIO_MUX_3                                    BIT(3)
#define GPIO_MUX_2                                    BIT(2)
#define GPIO_MUX_1                                    BIT(1)
#define GPIO_MUX_0                                    BIT(0)

#define WOCAWMEM_AWBITWATION                          0x00000C
#define WOCAWMEM_AWBITWATION_WOTATE                   BIT(28)
#define WOCAWMEM_AWBITWATION_VGA_MASK                 (0x7 << 24)
#define WOCAWMEM_AWBITWATION_VGA_OFF                  (0x0 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_1           (0x1 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_2           (0x2 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_3           (0x3 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_4           (0x4 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_5           (0x5 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_6           (0x6 << 24)
#define WOCAWMEM_AWBITWATION_VGA_PWIOWITY_7           (0x7 << 24)
#define WOCAWMEM_AWBITWATION_DMA_MASK                 (0x7 << 20)
#define WOCAWMEM_AWBITWATION_DMA_OFF                  (0x0 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_1           (0x1 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_2           (0x2 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_3           (0x3 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_4           (0x4 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_5           (0x5 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_6           (0x6 << 20)
#define WOCAWMEM_AWBITWATION_DMA_PWIOWITY_7           (0x7 << 20)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_MASK             (0x7 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_OFF              (0x0 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_1       (0x1 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_2       (0x2 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_3       (0x3 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_4       (0x4 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_5       (0x5 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_6       (0x6 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT1_PWIOWITY_7       (0x7 << 16)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_MASK             (0x7 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_OFF              (0x0 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_1       (0x1 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_2       (0x2 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_3       (0x3 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_4       (0x4 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_5       (0x5 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_6       (0x6 << 12)
#define WOCAWMEM_AWBITWATION_ZVPOWT0_PWIOWITY_7       (0x7 << 12)
#define WOCAWMEM_AWBITWATION_VIDEO_MASK               (0x7 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_OFF                (0x0 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_1         (0x1 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_2         (0x2 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_3         (0x3 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_4         (0x4 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_5         (0x5 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_6         (0x6 << 8)
#define WOCAWMEM_AWBITWATION_VIDEO_PWIOWITY_7         (0x7 << 8)
#define WOCAWMEM_AWBITWATION_PANEW_MASK               (0x7 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_OFF                (0x0 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_1         (0x1 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_2         (0x2 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_3         (0x3 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_4         (0x4 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_5         (0x5 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_6         (0x6 << 4)
#define WOCAWMEM_AWBITWATION_PANEW_PWIOWITY_7         (0x7 << 4)
#define WOCAWMEM_AWBITWATION_CWT_MASK                 0x7
#define WOCAWMEM_AWBITWATION_CWT_OFF                  0x0
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_1           0x1
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_2           0x2
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_3           0x3
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_4           0x4
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_5           0x5
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_6           0x6
#define WOCAWMEM_AWBITWATION_CWT_PWIOWITY_7           0x7

#define PCIMEM_AWBITWATION                            0x000010
#define PCIMEM_AWBITWATION_WOTATE                     BIT(28)
#define PCIMEM_AWBITWATION_VGA_MASK                   (0x7 << 24)
#define PCIMEM_AWBITWATION_VGA_OFF                    (0x0 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_1             (0x1 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_2             (0x2 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_3             (0x3 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_4             (0x4 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_5             (0x5 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_6             (0x6 << 24)
#define PCIMEM_AWBITWATION_VGA_PWIOWITY_7             (0x7 << 24)
#define PCIMEM_AWBITWATION_DMA_MASK                   (0x7 << 20)
#define PCIMEM_AWBITWATION_DMA_OFF                    (0x0 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_1             (0x1 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_2             (0x2 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_3             (0x3 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_4             (0x4 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_5             (0x5 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_6             (0x6 << 20)
#define PCIMEM_AWBITWATION_DMA_PWIOWITY_7             (0x7 << 20)
#define PCIMEM_AWBITWATION_ZVPOWT1_MASK               (0x7 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_OFF                (0x0 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_1         (0x1 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_2         (0x2 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_3         (0x3 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_4         (0x4 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_5         (0x5 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_6         (0x6 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT1_PWIOWITY_7         (0x7 << 16)
#define PCIMEM_AWBITWATION_ZVPOWT0_MASK               (0x7 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_OFF                (0x0 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_1         (0x1 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_2         (0x2 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_3         (0x3 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_4         (0x4 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_5         (0x5 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_6         (0x6 << 12)
#define PCIMEM_AWBITWATION_ZVPOWT0_PWIOWITY_7         (0x7 << 12)
#define PCIMEM_AWBITWATION_VIDEO_MASK                 (0x7 << 8)
#define PCIMEM_AWBITWATION_VIDEO_OFF                  (0x0 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_1           (0x1 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_2           (0x2 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_3           (0x3 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_4           (0x4 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_5           (0x5 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_6           (0x6 << 8)
#define PCIMEM_AWBITWATION_VIDEO_PWIOWITY_7           (0x7 << 8)
#define PCIMEM_AWBITWATION_PANEW_MASK                 (0x7 << 4)
#define PCIMEM_AWBITWATION_PANEW_OFF                  (0x0 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_1           (0x1 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_2           (0x2 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_3           (0x3 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_4           (0x4 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_5           (0x5 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_6           (0x6 << 4)
#define PCIMEM_AWBITWATION_PANEW_PWIOWITY_7           (0x7 << 4)
#define PCIMEM_AWBITWATION_CWT_MASK                   0x7
#define PCIMEM_AWBITWATION_CWT_OFF                    0x0
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_1             0x1
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_2             0x2
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_3             0x3
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_4             0x4
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_5             0x5
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_6             0x6
#define PCIMEM_AWBITWATION_CWT_PWIOWITY_7             0x7

#define WAW_INT                                       0x000020
#define WAW_INT_ZVPOWT1_VSYNC                         BIT(4)
#define WAW_INT_ZVPOWT0_VSYNC                         BIT(3)
#define WAW_INT_CWT_VSYNC                             BIT(2)
#define WAW_INT_PANEW_VSYNC                           BIT(1)
#define WAW_INT_VGA_VSYNC                             BIT(0)

#define INT_STATUS                                    0x000024
#define INT_STATUS_GPIO31                             BIT(31)
#define INT_STATUS_GPIO30                             BIT(30)
#define INT_STATUS_GPIO29                             BIT(29)
#define INT_STATUS_GPIO28                             BIT(28)
#define INT_STATUS_GPIO27                             BIT(27)
#define INT_STATUS_GPIO26                             BIT(26)
#define INT_STATUS_GPIO25                             BIT(25)
#define INT_STATUS_I2C                                BIT(12)
#define INT_STATUS_PWM                                BIT(11)
#define INT_STATUS_DMA1                               BIT(10)
#define INT_STATUS_DMA0                               BIT(9)
#define INT_STATUS_PCI                                BIT(8)
#define INT_STATUS_SSP1                               BIT(7)
#define INT_STATUS_SSP0                               BIT(6)
#define INT_STATUS_DE                                 BIT(5)
#define INT_STATUS_ZVPOWT1_VSYNC                      BIT(4)
#define INT_STATUS_ZVPOWT0_VSYNC                      BIT(3)
#define INT_STATUS_CWT_VSYNC                          BIT(2)
#define INT_STATUS_PANEW_VSYNC                        BIT(1)
#define INT_STATUS_VGA_VSYNC                          BIT(0)

#define INT_MASK                                      0x000028
#define INT_MASK_GPIO31                               BIT(31)
#define INT_MASK_GPIO30                               BIT(30)
#define INT_MASK_GPIO29                               BIT(29)
#define INT_MASK_GPIO28                               BIT(28)
#define INT_MASK_GPIO27                               BIT(27)
#define INT_MASK_GPIO26                               BIT(26)
#define INT_MASK_GPIO25                               BIT(25)
#define INT_MASK_I2C                                  BIT(12)
#define INT_MASK_PWM                                  BIT(11)
#define INT_MASK_DMA1                                 BIT(10)
#define INT_MASK_DMA                                  BIT(9)
#define INT_MASK_PCI                                  BIT(8)
#define INT_MASK_SSP1                                 BIT(7)
#define INT_MASK_SSP0                                 BIT(6)
#define INT_MASK_DE                                   BIT(5)
#define INT_MASK_ZVPOWT1_VSYNC                        BIT(4)
#define INT_MASK_ZVPOWT0_VSYNC                        BIT(3)
#define INT_MASK_CWT_VSYNC                            BIT(2)
#define INT_MASK_PANEW_VSYNC                          BIT(1)
#define INT_MASK_VGA_VSYNC                            BIT(0)

#define CUWWENT_GATE                                  0x000040
#define CUWWENT_GATE_MCWK_MASK                        (0x3 << 14)
#ifdef VAWIDATION_CHIP
    #define CUWWENT_GATE_MCWK_112MHZ                  (0x0 << 14)
    #define CUWWENT_GATE_MCWK_84MHZ                   (0x1 << 14)
    #define CUWWENT_GATE_MCWK_56MHZ                   (0x2 << 14)
    #define CUWWENT_GATE_MCWK_42MHZ                   (0x3 << 14)
#ewse
    #define CUWWENT_GATE_MCWK_DIV_3                   (0x0 << 14)
    #define CUWWENT_GATE_MCWK_DIV_4                   (0x1 << 14)
    #define CUWWENT_GATE_MCWK_DIV_6                   (0x2 << 14)
    #define CUWWENT_GATE_MCWK_DIV_8                   (0x3 << 14)
#endif
#define CUWWENT_GATE_M2XCWK_MASK                      (0x3 << 12)
#ifdef VAWIDATION_CHIP
    #define CUWWENT_GATE_M2XCWK_336MHZ                (0x0 << 12)
    #define CUWWENT_GATE_M2XCWK_168MHZ                (0x1 << 12)
    #define CUWWENT_GATE_M2XCWK_112MHZ                (0x2 << 12)
    #define CUWWENT_GATE_M2XCWK_84MHZ                 (0x3 << 12)
#ewse
    #define CUWWENT_GATE_M2XCWK_DIV_1                 (0x0 << 12)
    #define CUWWENT_GATE_M2XCWK_DIV_2                 (0x1 << 12)
    #define CUWWENT_GATE_M2XCWK_DIV_3                 (0x2 << 12)
    #define CUWWENT_GATE_M2XCWK_DIV_4                 (0x3 << 12)
#endif
#define CUWWENT_GATE_VGA                              BIT(10)
#define CUWWENT_GATE_PWM                              BIT(9)
#define CUWWENT_GATE_I2C                              BIT(8)
#define CUWWENT_GATE_SSP                              BIT(7)
#define CUWWENT_GATE_GPIO                             BIT(6)
#define CUWWENT_GATE_ZVPOWT                           BIT(5)
#define CUWWENT_GATE_CSC                              BIT(4)
#define CUWWENT_GATE_DE                               BIT(3)
#define CUWWENT_GATE_DISPWAY                          BIT(2)
#define CUWWENT_GATE_WOCAWMEM                         BIT(1)
#define CUWWENT_GATE_DMA                              BIT(0)

#define MODE0_GATE                                    0x000044
#define MODE0_GATE_MCWK_MASK                          (0x3 << 14)
#define MODE0_GATE_MCWK_112MHZ                        (0x0 << 14)
#define MODE0_GATE_MCWK_84MHZ                         (0x1 << 14)
#define MODE0_GATE_MCWK_56MHZ                         (0x2 << 14)
#define MODE0_GATE_MCWK_42MHZ                         (0x3 << 14)
#define MODE0_GATE_M2XCWK_MASK                        (0x3 << 12)
#define MODE0_GATE_M2XCWK_336MHZ                      (0x0 << 12)
#define MODE0_GATE_M2XCWK_168MHZ                      (0x1 << 12)
#define MODE0_GATE_M2XCWK_112MHZ                      (0x2 << 12)
#define MODE0_GATE_M2XCWK_84MHZ                       (0x3 << 12)
#define MODE0_GATE_VGA                                BIT(10)
#define MODE0_GATE_PWM                                BIT(9)
#define MODE0_GATE_I2C                                BIT(8)
#define MODE0_GATE_SSP                                BIT(7)
#define MODE0_GATE_GPIO                               BIT(6)
#define MODE0_GATE_ZVPOWT                             BIT(5)
#define MODE0_GATE_CSC                                BIT(4)
#define MODE0_GATE_DE                                 BIT(3)
#define MODE0_GATE_DISPWAY                            BIT(2)
#define MODE0_GATE_WOCAWMEM                           BIT(1)
#define MODE0_GATE_DMA                                BIT(0)

#define MODE1_GATE                                    0x000048
#define MODE1_GATE_MCWK_MASK                          (0x3 << 14)
#define MODE1_GATE_MCWK_112MHZ                        (0x0 << 14)
#define MODE1_GATE_MCWK_84MHZ                         (0x1 << 14)
#define MODE1_GATE_MCWK_56MHZ                         (0x2 << 14)
#define MODE1_GATE_MCWK_42MHZ                         (0x3 << 14)
#define MODE1_GATE_M2XCWK_MASK                        (0x3 << 12)
#define MODE1_GATE_M2XCWK_336MHZ                      (0x0 << 12)
#define MODE1_GATE_M2XCWK_168MHZ                      (0x1 << 12)
#define MODE1_GATE_M2XCWK_112MHZ                      (0x2 << 12)
#define MODE1_GATE_M2XCWK_84MHZ                       (0x3 << 12)
#define MODE1_GATE_VGA                                BIT(10)
#define MODE1_GATE_PWM                                BIT(9)
#define MODE1_GATE_I2C                                BIT(8)
#define MODE1_GATE_SSP                                BIT(7)
#define MODE1_GATE_GPIO                               BIT(6)
#define MODE1_GATE_ZVPOWT                             BIT(5)
#define MODE1_GATE_CSC                                BIT(4)
#define MODE1_GATE_DE                                 BIT(3)
#define MODE1_GATE_DISPWAY                            BIT(2)
#define MODE1_GATE_WOCAWMEM                           BIT(1)
#define MODE1_GATE_DMA                                BIT(0)

#define POWEW_MODE_CTWW                               0x00004C
#ifdef VAWIDATION_CHIP
    #define POWEW_MODE_CTWW_336CWK                    BIT(4)
#endif
#define POWEW_MODE_CTWW_OSC_INPUT                     BIT(3)
#define POWEW_MODE_CTWW_ACPI                          BIT(2)
#define POWEW_MODE_CTWW_MODE_MASK                     (0x3 << 0)
#define POWEW_MODE_CTWW_MODE_MODE0                    (0x0 << 0)
#define POWEW_MODE_CTWW_MODE_MODE1                    (0x1 << 0)
#define POWEW_MODE_CTWW_MODE_SWEEP                    (0x2 << 0)

#define PCI_MASTEW_BASE                               0x000050
#define PCI_MASTEW_BASE_ADDWESS_MASK                  0xff

#define DEVICE_ID                                     0x000054
#define DEVICE_ID_DEVICE_ID_MASK                      (0xffff << 16)
#define DEVICE_ID_WEVISION_ID_MASK                    0xff

#define PWW_CWK_COUNT                                 0x000058
#define PWW_CWK_COUNT_COUNTEW_MASK                    0xffff

#define PANEW_PWW_CTWW                                0x00005C
#define PWW_CTWW_BYPASS                               BIT(18)
#define PWW_CTWW_POWEW                                BIT(17)
#define PWW_CTWW_INPUT                                BIT(16)
#ifdef VAWIDATION_CHIP
    #define PWW_CTWW_OD_SHIFT                         14
    #define PWW_CTWW_OD_MASK                          (0x3 << 14)
#ewse
    #define PWW_CTWW_POD_SHIFT                        14
    #define PWW_CTWW_POD_MASK                         (0x3 << 14)
    #define PWW_CTWW_OD_SHIFT                         12
    #define PWW_CTWW_OD_MASK                          (0x3 << 12)
#endif
#define PWW_CTWW_N_SHIFT                              8
#define PWW_CTWW_N_MASK                               (0xf << 8)
#define PWW_CTWW_M_SHIFT                              0
#define PWW_CTWW_M_MASK                               0xff

#define CWT_PWW_CTWW                                  0x000060

#define VGA_PWW0_CTWW                                 0x000064

#define VGA_PWW1_CTWW                                 0x000068

#define SCWATCH_DATA                                  0x00006c

#ifndef VAWIDATION_CHIP

#define MXCWK_PWW_CTWW                                0x000070

#define VGA_CONFIGUWATION                             0x000088
#define VGA_CONFIGUWATION_USEW_DEFINE_MASK            (0x3 << 4)
#define VGA_CONFIGUWATION_PWW                         BIT(2)
#define VGA_CONFIGUWATION_MODE                        BIT(1)

#endif

#define GPIO_DATA                                       0x010000
#define GPIO_DATA_31                                    BIT(31)
#define GPIO_DATA_30                                    BIT(30)
#define GPIO_DATA_29                                    BIT(29)
#define GPIO_DATA_28                                    BIT(28)
#define GPIO_DATA_27                                    BIT(27)
#define GPIO_DATA_26                                    BIT(26)
#define GPIO_DATA_25                                    BIT(25)
#define GPIO_DATA_24                                    BIT(24)
#define GPIO_DATA_23                                    BIT(23)
#define GPIO_DATA_22                                    BIT(22)
#define GPIO_DATA_21                                    BIT(21)
#define GPIO_DATA_20                                    BIT(20)
#define GPIO_DATA_19                                    BIT(19)
#define GPIO_DATA_18                                    BIT(18)
#define GPIO_DATA_17                                    BIT(17)
#define GPIO_DATA_16                                    BIT(16)
#define GPIO_DATA_15                                    BIT(15)
#define GPIO_DATA_14                                    BIT(14)
#define GPIO_DATA_13                                    BIT(13)
#define GPIO_DATA_12                                    BIT(12)
#define GPIO_DATA_11                                    BIT(11)
#define GPIO_DATA_10                                    BIT(10)
#define GPIO_DATA_9                                     BIT(9)
#define GPIO_DATA_8                                     BIT(8)
#define GPIO_DATA_7                                     BIT(7)
#define GPIO_DATA_6                                     BIT(6)
#define GPIO_DATA_5                                     BIT(5)
#define GPIO_DATA_4                                     BIT(4)
#define GPIO_DATA_3                                     BIT(3)
#define GPIO_DATA_2                                     BIT(2)
#define GPIO_DATA_1                                     BIT(1)
#define GPIO_DATA_0                                     BIT(0)

#define GPIO_DATA_DIWECTION                             0x010004
#define GPIO_DATA_DIWECTION_31                          BIT(31)
#define GPIO_DATA_DIWECTION_30                          BIT(30)
#define GPIO_DATA_DIWECTION_29                          BIT(29)
#define GPIO_DATA_DIWECTION_28                          BIT(28)
#define GPIO_DATA_DIWECTION_27                          BIT(27)
#define GPIO_DATA_DIWECTION_26                          BIT(26)
#define GPIO_DATA_DIWECTION_25                          BIT(25)
#define GPIO_DATA_DIWECTION_24                          BIT(24)
#define GPIO_DATA_DIWECTION_23                          BIT(23)
#define GPIO_DATA_DIWECTION_22                          BIT(22)
#define GPIO_DATA_DIWECTION_21                          BIT(21)
#define GPIO_DATA_DIWECTION_20                          BIT(20)
#define GPIO_DATA_DIWECTION_19                          BIT(19)
#define GPIO_DATA_DIWECTION_18                          BIT(18)
#define GPIO_DATA_DIWECTION_17                          BIT(17)
#define GPIO_DATA_DIWECTION_16                          BIT(16)
#define GPIO_DATA_DIWECTION_15                          BIT(15)
#define GPIO_DATA_DIWECTION_14                          BIT(14)
#define GPIO_DATA_DIWECTION_13                          BIT(13)
#define GPIO_DATA_DIWECTION_12                          BIT(12)
#define GPIO_DATA_DIWECTION_11                          BIT(11)
#define GPIO_DATA_DIWECTION_10                          BIT(10)
#define GPIO_DATA_DIWECTION_9                           BIT(9)
#define GPIO_DATA_DIWECTION_8                           BIT(8)
#define GPIO_DATA_DIWECTION_7                           BIT(7)
#define GPIO_DATA_DIWECTION_6                           BIT(6)
#define GPIO_DATA_DIWECTION_5                           BIT(5)
#define GPIO_DATA_DIWECTION_4                           BIT(4)
#define GPIO_DATA_DIWECTION_3                           BIT(3)
#define GPIO_DATA_DIWECTION_2                           BIT(2)
#define GPIO_DATA_DIWECTION_1                           BIT(1)
#define GPIO_DATA_DIWECTION_0                           BIT(0)

#define GPIO_INTEWWUPT_SETUP                            0x010008
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_31                 BIT(22)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_30                 BIT(21)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_29                 BIT(20)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_28                 BIT(19)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_27                 BIT(18)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_26                 BIT(17)
#define GPIO_INTEWWUPT_SETUP_TWIGGEW_25                 BIT(16)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_31                  BIT(14)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_30                  BIT(13)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_29                  BIT(12)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_28                  BIT(11)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_27                  BIT(10)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_26                  BIT(9)
#define GPIO_INTEWWUPT_SETUP_ACTIVE_25                  BIT(8)
#define GPIO_INTEWWUPT_SETUP_ENABWE_31                  BIT(6)
#define GPIO_INTEWWUPT_SETUP_ENABWE_30                  BIT(5)
#define GPIO_INTEWWUPT_SETUP_ENABWE_29                  BIT(4)
#define GPIO_INTEWWUPT_SETUP_ENABWE_28                  BIT(3)
#define GPIO_INTEWWUPT_SETUP_ENABWE_27                  BIT(2)
#define GPIO_INTEWWUPT_SETUP_ENABWE_26                  BIT(1)
#define GPIO_INTEWWUPT_SETUP_ENABWE_25                  BIT(0)

#define GPIO_INTEWWUPT_STATUS                           0x01000C
#define GPIO_INTEWWUPT_STATUS_31                        BIT(22)
#define GPIO_INTEWWUPT_STATUS_30                        BIT(21)
#define GPIO_INTEWWUPT_STATUS_29                        BIT(20)
#define GPIO_INTEWWUPT_STATUS_28                        BIT(19)
#define GPIO_INTEWWUPT_STATUS_27                        BIT(18)
#define GPIO_INTEWWUPT_STATUS_26                        BIT(17)
#define GPIO_INTEWWUPT_STATUS_25                        BIT(16)

#define PANEW_DISPWAY_CTWW                            0x080000
#define PANEW_DISPWAY_CTWW_WESEWVED_MASK              0xc0f08000
#define PANEW_DISPWAY_CTWW_SEWECT_SHIFT               28
#define PANEW_DISPWAY_CTWW_SEWECT_MASK                (0x3 << 28)
#define PANEW_DISPWAY_CTWW_SEWECT_PANEW               (0x0 << 28)
#define PANEW_DISPWAY_CTWW_SEWECT_VGA                 (0x1 << 28)
#define PANEW_DISPWAY_CTWW_SEWECT_CWT                 (0x2 << 28)
#define PANEW_DISPWAY_CTWW_FPEN                       BIT(27)
#define PANEW_DISPWAY_CTWW_VBIASEN                    BIT(26)
#define PANEW_DISPWAY_CTWW_DATA                       BIT(25)
#define PANEW_DISPWAY_CTWW_FPVDDEN                    BIT(24)
#define PANEW_DISPWAY_CTWW_DUAW_DISPWAY               BIT(19)
#define PANEW_DISPWAY_CTWW_DOUBWE_PIXEW               BIT(18)
#define PANEW_DISPWAY_CTWW_FIFO                       (0x3 << 16)
#define PANEW_DISPWAY_CTWW_FIFO_1                     (0x0 << 16)
#define PANEW_DISPWAY_CTWW_FIFO_3                     (0x1 << 16)
#define PANEW_DISPWAY_CTWW_FIFO_7                     (0x2 << 16)
#define PANEW_DISPWAY_CTWW_FIFO_11                    (0x3 << 16)
#define DISPWAY_CTWW_CWOCK_PHASE                      BIT(14)
#define DISPWAY_CTWW_VSYNC_PHASE                      BIT(13)
#define DISPWAY_CTWW_HSYNC_PHASE                      BIT(12)
#define PANEW_DISPWAY_CTWW_VSYNC                      BIT(11)
#define PANEW_DISPWAY_CTWW_CAPTUWE_TIMING             BIT(10)
#define PANEW_DISPWAY_CTWW_COWOW_KEY                  BIT(9)
#define DISPWAY_CTWW_TIMING                           BIT(8)
#define PANEW_DISPWAY_CTWW_VEWTICAW_PAN_DIW           BIT(7)
#define PANEW_DISPWAY_CTWW_VEWTICAW_PAN               BIT(6)
#define PANEW_DISPWAY_CTWW_HOWIZONTAW_PAN_DIW         BIT(5)
#define PANEW_DISPWAY_CTWW_HOWIZONTAW_PAN             BIT(4)
#define DISPWAY_CTWW_GAMMA                            BIT(3)
#define DISPWAY_CTWW_PWANE                            BIT(2)
#define PANEW_DISPWAY_CTWW_FOWMAT                     (0x3 << 0)
#define PANEW_DISPWAY_CTWW_FOWMAT_8                   (0x0 << 0)
#define PANEW_DISPWAY_CTWW_FOWMAT_16                  (0x1 << 0)
#define PANEW_DISPWAY_CTWW_FOWMAT_32                  (0x2 << 0)

#define PANEW_PAN_CTWW                                0x080004
#define PANEW_PAN_CTWW_VEWTICAW_PAN_MASK              (0xff << 24)
#define PANEW_PAN_CTWW_VEWTICAW_VSYNC_MASK            (0x3f << 16)
#define PANEW_PAN_CTWW_HOWIZONTAW_PAN_MASK            (0xff << 8)
#define PANEW_PAN_CTWW_HOWIZONTAW_VSYNC_MASK          0x3f

#define PANEW_COWOW_KEY                               0x080008
#define PANEW_COWOW_KEY_MASK_MASK                     (0xffff << 16)
#define PANEW_COWOW_KEY_VAWUE_MASK                    0xffff

#define PANEW_FB_ADDWESS                              0x08000C
#define PANEW_FB_ADDWESS_STATUS                       BIT(31)
#define PANEW_FB_ADDWESS_EXT                          BIT(27)
#define PANEW_FB_ADDWESS_ADDWESS_MASK                 0x1ffffff

#define PANEW_FB_WIDTH                                0x080010
#define PANEW_FB_WIDTH_WIDTH_SHIFT                    16
#define PANEW_FB_WIDTH_WIDTH_MASK                     (0x3fff << 16)
#define PANEW_FB_WIDTH_OFFSET_MASK                    0x3fff

#define PANEW_WINDOW_WIDTH                            0x080014
#define PANEW_WINDOW_WIDTH_WIDTH_SHIFT                16
#define PANEW_WINDOW_WIDTH_WIDTH_MASK                 (0xfff << 16)
#define PANEW_WINDOW_WIDTH_X_MASK                     0xfff

#define PANEW_WINDOW_HEIGHT                           0x080018
#define PANEW_WINDOW_HEIGHT_HEIGHT_SHIFT              16
#define PANEW_WINDOW_HEIGHT_HEIGHT_MASK               (0xfff << 16)
#define PANEW_WINDOW_HEIGHT_Y_MASK                    0xfff

#define PANEW_PWANE_TW                                0x08001C
#define PANEW_PWANE_TW_TOP_SHIFT                      16
#define PANEW_PWANE_TW_TOP_MASK                       (0x7ff << 16)
#define PANEW_PWANE_TW_WEFT_MASK                      0x7ff

#define PANEW_PWANE_BW                                0x080020
#define PANEW_PWANE_BW_BOTTOM_SHIFT                   16
#define PANEW_PWANE_BW_BOTTOM_MASK                    (0x7ff << 16)
#define PANEW_PWANE_BW_WIGHT_MASK                     0x7ff

#define PANEW_HOWIZONTAW_TOTAW                        0x080024
#define PANEW_HOWIZONTAW_TOTAW_TOTAW_SHIFT            16
#define PANEW_HOWIZONTAW_TOTAW_TOTAW_MASK             (0xfff << 16)
#define PANEW_HOWIZONTAW_TOTAW_DISPWAY_END_MASK       0xfff

#define PANEW_HOWIZONTAW_SYNC                         0x080028
#define PANEW_HOWIZONTAW_SYNC_WIDTH_SHIFT             16
#define PANEW_HOWIZONTAW_SYNC_WIDTH_MASK              (0xff << 16)
#define PANEW_HOWIZONTAW_SYNC_STAWT_MASK              0xfff

#define PANEW_VEWTICAW_TOTAW                          0x08002C
#define PANEW_VEWTICAW_TOTAW_TOTAW_SHIFT              16
#define PANEW_VEWTICAW_TOTAW_TOTAW_MASK               (0x7ff << 16)
#define PANEW_VEWTICAW_TOTAW_DISPWAY_END_MASK         0x7ff

#define PANEW_VEWTICAW_SYNC                           0x080030
#define PANEW_VEWTICAW_SYNC_HEIGHT_SHIFT              16
#define PANEW_VEWTICAW_SYNC_HEIGHT_MASK               (0x3f << 16)
#define PANEW_VEWTICAW_SYNC_STAWT_MASK                0x7ff

#define PANEW_CUWWENT_WINE                            0x080034
#define PANEW_CUWWENT_WINE_WINE_MASK                  0x7ff

/* Video Contwow */

#define VIDEO_DISPWAY_CTWW                              0x080040
#define VIDEO_DISPWAY_CTWW_WINE_BUFFEW                  BIT(18)
#define VIDEO_DISPWAY_CTWW_FIFO_MASK                    (0x3 << 16)
#define VIDEO_DISPWAY_CTWW_FIFO_1                       (0x0 << 16)
#define VIDEO_DISPWAY_CTWW_FIFO_3                       (0x1 << 16)
#define VIDEO_DISPWAY_CTWW_FIFO_7                       (0x2 << 16)
#define VIDEO_DISPWAY_CTWW_FIFO_11                      (0x3 << 16)
#define VIDEO_DISPWAY_CTWW_BUFFEW                       BIT(15)
#define VIDEO_DISPWAY_CTWW_CAPTUWE                      BIT(14)
#define VIDEO_DISPWAY_CTWW_DOUBWE_BUFFEW                BIT(13)
#define VIDEO_DISPWAY_CTWW_BYTE_SWAP                    BIT(12)
#define VIDEO_DISPWAY_CTWW_VEWTICAW_SCAWE               BIT(11)
#define VIDEO_DISPWAY_CTWW_HOWIZONTAW_SCAWE             BIT(10)
#define VIDEO_DISPWAY_CTWW_VEWTICAW_MODE                BIT(9)
#define VIDEO_DISPWAY_CTWW_HOWIZONTAW_MODE              BIT(8)
#define VIDEO_DISPWAY_CTWW_PIXEW_MASK                   (0xf << 4)
#define VIDEO_DISPWAY_CTWW_GAMMA                        BIT(3)
#define VIDEO_DISPWAY_CTWW_FOWMAT_MASK                  0x3
#define VIDEO_DISPWAY_CTWW_FOWMAT_8                     0x0
#define VIDEO_DISPWAY_CTWW_FOWMAT_16                    0x1
#define VIDEO_DISPWAY_CTWW_FOWMAT_32                    0x2
#define VIDEO_DISPWAY_CTWW_FOWMAT_YUV                   0x3

#define VIDEO_FB_0_ADDWESS                            0x080044
#define VIDEO_FB_0_ADDWESS_STATUS                     BIT(31)
#define VIDEO_FB_0_ADDWESS_EXT                        BIT(27)
#define VIDEO_FB_0_ADDWESS_ADDWESS_MASK               0x3ffffff

#define VIDEO_FB_WIDTH                                0x080048
#define VIDEO_FB_WIDTH_WIDTH_MASK                     (0x3fff << 16)
#define VIDEO_FB_WIDTH_OFFSET_MASK                    0x3fff

#define VIDEO_FB_0_WAST_ADDWESS                       0x08004C
#define VIDEO_FB_0_WAST_ADDWESS_EXT                   BIT(27)
#define VIDEO_FB_0_WAST_ADDWESS_ADDWESS_MASK          0x3ffffff

#define VIDEO_PWANE_TW                                0x080050
#define VIDEO_PWANE_TW_TOP_MASK                       (0x7ff << 16)
#define VIDEO_PWANE_TW_WEFT_MASK                      0x7ff

#define VIDEO_PWANE_BW                                0x080054
#define VIDEO_PWANE_BW_BOTTOM_MASK                    (0x7ff << 16)
#define VIDEO_PWANE_BW_WIGHT_MASK                     0x7ff

#define VIDEO_SCAWE                                   0x080058
#define VIDEO_SCAWE_VEWTICAW_MODE                     BIT(31)
#define VIDEO_SCAWE_VEWTICAW_SCAWE_MASK               (0xfff << 16)
#define VIDEO_SCAWE_HOWIZONTAW_MODE                   BIT(15)
#define VIDEO_SCAWE_HOWIZONTAW_SCAWE_MASK             0xfff

#define VIDEO_INITIAW_SCAWE                           0x08005C
#define VIDEO_INITIAW_SCAWE_FB_1_MASK                 (0xfff << 16)
#define VIDEO_INITIAW_SCAWE_FB_0_MASK                 0xfff

#define VIDEO_YUV_CONSTANTS                           0x080060
#define VIDEO_YUV_CONSTANTS_Y_MASK                    (0xff << 24)
#define VIDEO_YUV_CONSTANTS_W_MASK                    (0xff << 16)
#define VIDEO_YUV_CONSTANTS_G_MASK                    (0xff << 8)
#define VIDEO_YUV_CONSTANTS_B_MASK                    0xff

#define VIDEO_FB_1_ADDWESS                            0x080064
#define VIDEO_FB_1_ADDWESS_STATUS                     BIT(31)
#define VIDEO_FB_1_ADDWESS_EXT                        BIT(27)
#define VIDEO_FB_1_ADDWESS_ADDWESS_MASK               0x3ffffff

#define VIDEO_FB_1_WAST_ADDWESS                       0x080068
#define VIDEO_FB_1_WAST_ADDWESS_EXT                   BIT(27)
#define VIDEO_FB_1_WAST_ADDWESS_ADDWESS_MASK          0x3ffffff

/* Video Awpha Contwow */

#define VIDEO_AWPHA_DISPWAY_CTWW                        0x080080
#define VIDEO_AWPHA_DISPWAY_CTWW_SEWECT                 BIT(28)
#define VIDEO_AWPHA_DISPWAY_CTWW_AWPHA_MASK             (0xf << 24)
#define VIDEO_AWPHA_DISPWAY_CTWW_FIFO_MASK              (0x3 << 16)
#define VIDEO_AWPHA_DISPWAY_CTWW_FIFO_1                 (0x0 << 16)
#define VIDEO_AWPHA_DISPWAY_CTWW_FIFO_3                 (0x1 << 16)
#define VIDEO_AWPHA_DISPWAY_CTWW_FIFO_7                 (0x2 << 16)
#define VIDEO_AWPHA_DISPWAY_CTWW_FIFO_11                (0x3 << 16)
#define VIDEO_AWPHA_DISPWAY_CTWW_VEWT_SCAWE             BIT(11)
#define VIDEO_AWPHA_DISPWAY_CTWW_HOWZ_SCAWE             BIT(10)
#define VIDEO_AWPHA_DISPWAY_CTWW_VEWT_MODE              BIT(9)
#define VIDEO_AWPHA_DISPWAY_CTWW_HOWZ_MODE              BIT(8)
#define VIDEO_AWPHA_DISPWAY_CTWW_PIXEW_MASK             (0xf << 4)
#define VIDEO_AWPHA_DISPWAY_CTWW_CHWOMA_KEY             BIT(3)
#define VIDEO_AWPHA_DISPWAY_CTWW_FOWMAT_MASK            0x3
#define VIDEO_AWPHA_DISPWAY_CTWW_FOWMAT_8               0x0
#define VIDEO_AWPHA_DISPWAY_CTWW_FOWMAT_16              0x1
#define VIDEO_AWPHA_DISPWAY_CTWW_FOWMAT_AWPHA_4_4       0x2
#define VIDEO_AWPHA_DISPWAY_CTWW_FOWMAT_AWPHA_4_4_4_4   0x3

#define VIDEO_AWPHA_FB_ADDWESS                        0x080084
#define VIDEO_AWPHA_FB_ADDWESS_STATUS                 BIT(31)
#define VIDEO_AWPHA_FB_ADDWESS_EXT                    BIT(27)
#define VIDEO_AWPHA_FB_ADDWESS_ADDWESS_MASK           0x3ffffff

#define VIDEO_AWPHA_FB_WIDTH                          0x080088
#define VIDEO_AWPHA_FB_WIDTH_WIDTH_MASK               (0x3fff << 16)
#define VIDEO_AWPHA_FB_WIDTH_OFFSET_MASK              0x3fff

#define VIDEO_AWPHA_FB_WAST_ADDWESS                   0x08008C
#define VIDEO_AWPHA_FB_WAST_ADDWESS_EXT               BIT(27)
#define VIDEO_AWPHA_FB_WAST_ADDWESS_ADDWESS_MASK      0x3ffffff

#define VIDEO_AWPHA_PWANE_TW                          0x080090
#define VIDEO_AWPHA_PWANE_TW_TOP_MASK                 (0x7ff << 16)
#define VIDEO_AWPHA_PWANE_TW_WEFT_MASK                0x7ff

#define VIDEO_AWPHA_PWANE_BW                          0x080094
#define VIDEO_AWPHA_PWANE_BW_BOTTOM_MASK              (0x7ff << 16)
#define VIDEO_AWPHA_PWANE_BW_WIGHT_MASK               0x7ff

#define VIDEO_AWPHA_SCAWE                             0x080098
#define VIDEO_AWPHA_SCAWE_VEWTICAW_MODE               BIT(31)
#define VIDEO_AWPHA_SCAWE_VEWTICAW_SCAWE_MASK         (0xfff << 16)
#define VIDEO_AWPHA_SCAWE_HOWIZONTAW_MODE             BIT(15)
#define VIDEO_AWPHA_SCAWE_HOWIZONTAW_SCAWE_MASK       0xfff

#define VIDEO_AWPHA_INITIAW_SCAWE                     0x08009C
#define VIDEO_AWPHA_INITIAW_SCAWE_VEWTICAW_MASK       (0xfff << 16)
#define VIDEO_AWPHA_INITIAW_SCAWE_HOWIZONTAW_MASK     0xfff

#define VIDEO_AWPHA_CHWOMA_KEY                        0x0800A0
#define VIDEO_AWPHA_CHWOMA_KEY_MASK_MASK              (0xffff << 16)
#define VIDEO_AWPHA_CHWOMA_KEY_VAWUE_MASK             0xffff

#define VIDEO_AWPHA_COWOW_WOOKUP_01                   0x0800A4
#define VIDEO_AWPHA_COWOW_WOOKUP_01_1_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_1_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_1_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_1_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_0_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_01_0_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_0_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_01_0_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_23                   0x0800A8
#define VIDEO_AWPHA_COWOW_WOOKUP_23_3_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_3_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_3_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_3_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_2_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_23_2_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_2_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_23_2_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_45                   0x0800AC
#define VIDEO_AWPHA_COWOW_WOOKUP_45_5_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_5_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_5_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_5_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_4_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_45_4_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_4_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_45_4_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_67                   0x0800B0
#define VIDEO_AWPHA_COWOW_WOOKUP_67_7_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_7_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_7_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_7_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_6_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_67_6_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_6_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_67_6_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_89                   0x0800B4
#define VIDEO_AWPHA_COWOW_WOOKUP_89_9_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_9_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_9_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_9_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_8_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_89_8_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_8_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_89_8_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_AB                   0x0800B8
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_B_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_B_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_B_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_B_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_A_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_A_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_A_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_AB_A_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_CD                   0x0800BC
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_D_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_D_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_D_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_D_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_C_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_C_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_C_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_CD_C_BWUE_MASK       0x1f

#define VIDEO_AWPHA_COWOW_WOOKUP_EF                   0x0800C0
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_F_MASK            (0xffff << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_F_WED_MASK        (0x1f << 27)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_F_GWEEN_MASK      (0x3f << 21)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_F_BWUE_MASK       (0x1f << 16)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_E_MASK            0xffff
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_E_WED_MASK        (0x1f << 11)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_E_GWEEN_MASK      (0x3f << 5)
#define VIDEO_AWPHA_COWOW_WOOKUP_EF_E_BWUE_MASK       0x1f

/* Panew Cuwsow Contwow */

#define PANEW_HWC_ADDWESS                             0x0800F0
#define PANEW_HWC_ADDWESS_ENABWE                      BIT(31)
#define PANEW_HWC_ADDWESS_EXT                         BIT(27)
#define PANEW_HWC_ADDWESS_ADDWESS_MASK                0x3ffffff

#define PANEW_HWC_WOCATION                            0x0800F4
#define PANEW_HWC_WOCATION_TOP                        BIT(27)
#define PANEW_HWC_WOCATION_Y_MASK                     (0x7ff << 16)
#define PANEW_HWC_WOCATION_WEFT                       BIT(11)
#define PANEW_HWC_WOCATION_X_MASK                     0x7ff

#define PANEW_HWC_COWOW_12                            0x0800F8
#define PANEW_HWC_COWOW_12_2_WGB565_MASK              (0xffff << 16)
#define PANEW_HWC_COWOW_12_1_WGB565_MASK              0xffff

#define PANEW_HWC_COWOW_3                             0x0800FC
#define PANEW_HWC_COWOW_3_WGB565_MASK                 0xffff

/* Owd Definitions +++ */
#define PANEW_HWC_COWOW_01                            0x0800F8
#define PANEW_HWC_COWOW_01_1_WED_MASK                 (0x1f << 27)
#define PANEW_HWC_COWOW_01_1_GWEEN_MASK               (0x3f << 21)
#define PANEW_HWC_COWOW_01_1_BWUE_MASK                (0x1f << 16)
#define PANEW_HWC_COWOW_01_0_WED_MASK                 (0x1f << 11)
#define PANEW_HWC_COWOW_01_0_GWEEN_MASK               (0x3f << 5)
#define PANEW_HWC_COWOW_01_0_BWUE_MASK                0x1f

#define PANEW_HWC_COWOW_2                             0x0800FC
#define PANEW_HWC_COWOW_2_WED_MASK                    (0x1f << 11)
#define PANEW_HWC_COWOW_2_GWEEN_MASK                  (0x3f << 5)
#define PANEW_HWC_COWOW_2_BWUE_MASK                   0x1f
/* Owd Definitions --- */

/* Awpha Contwow */

#define AWPHA_DISPWAY_CTWW                            0x080100
#define AWPHA_DISPWAY_CTWW_SEWECT                     BIT(28)
#define AWPHA_DISPWAY_CTWW_AWPHA_MASK                 (0xf << 24)
#define AWPHA_DISPWAY_CTWW_FIFO_MASK                  (0x3 << 16)
#define AWPHA_DISPWAY_CTWW_FIFO_1                     (0x0 << 16)
#define AWPHA_DISPWAY_CTWW_FIFO_3                     (0x1 << 16)
#define AWPHA_DISPWAY_CTWW_FIFO_7                     (0x2 << 16)
#define AWPHA_DISPWAY_CTWW_FIFO_11                    (0x3 << 16)
#define AWPHA_DISPWAY_CTWW_PIXEW_MASK                 (0xf << 4)
#define AWPHA_DISPWAY_CTWW_CHWOMA_KEY                 BIT(3)
#define AWPHA_DISPWAY_CTWW_FOWMAT_MASK                0x3
#define AWPHA_DISPWAY_CTWW_FOWMAT_16                  0x1
#define AWPHA_DISPWAY_CTWW_FOWMAT_AWPHA_4_4           0x2
#define AWPHA_DISPWAY_CTWW_FOWMAT_AWPHA_4_4_4_4       0x3

#define AWPHA_FB_ADDWESS                              0x080104
#define AWPHA_FB_ADDWESS_STATUS                       BIT(31)
#define AWPHA_FB_ADDWESS_EXT                          BIT(27)
#define AWPHA_FB_ADDWESS_ADDWESS_MASK                 0x3ffffff

#define AWPHA_FB_WIDTH                                0x080108
#define AWPHA_FB_WIDTH_WIDTH_MASK                     (0x3fff << 16)
#define AWPHA_FB_WIDTH_OFFSET_MASK                    0x3fff

#define AWPHA_PWANE_TW                                0x08010C
#define AWPHA_PWANE_TW_TOP_MASK                       (0x7ff << 16)
#define AWPHA_PWANE_TW_WEFT_MASK                      0x7ff

#define AWPHA_PWANE_BW                                0x080110
#define AWPHA_PWANE_BW_BOTTOM_MASK                    (0x7ff << 16)
#define AWPHA_PWANE_BW_WIGHT_MASK                     0x7ff

#define AWPHA_CHWOMA_KEY                              0x080114
#define AWPHA_CHWOMA_KEY_MASK_MASK                    (0xffff << 16)
#define AWPHA_CHWOMA_KEY_VAWUE_MASK                   0xffff

#define AWPHA_COWOW_WOOKUP_01                         0x080118
#define AWPHA_COWOW_WOOKUP_01_1_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_01_1_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_01_1_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_01_1_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_01_0_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_01_0_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_01_0_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_01_0_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_23                         0x08011C
#define AWPHA_COWOW_WOOKUP_23_3_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_23_3_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_23_3_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_23_3_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_23_2_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_23_2_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_23_2_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_23_2_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_45                         0x080120
#define AWPHA_COWOW_WOOKUP_45_5_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_45_5_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_45_5_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_45_5_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_45_4_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_45_4_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_45_4_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_45_4_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_67                         0x080124
#define AWPHA_COWOW_WOOKUP_67_7_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_67_7_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_67_7_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_67_7_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_67_6_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_67_6_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_67_6_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_67_6_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_89                         0x080128
#define AWPHA_COWOW_WOOKUP_89_9_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_89_9_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_89_9_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_89_9_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_89_8_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_89_8_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_89_8_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_89_8_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_AB                         0x08012C
#define AWPHA_COWOW_WOOKUP_AB_B_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_AB_B_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_AB_B_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_AB_B_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_AB_A_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_AB_A_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_AB_A_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_AB_A_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_CD                         0x080130
#define AWPHA_COWOW_WOOKUP_CD_D_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_CD_D_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_CD_D_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_CD_D_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_CD_C_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_CD_C_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_CD_C_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_CD_C_BWUE_MASK             0x1f

#define AWPHA_COWOW_WOOKUP_EF                         0x080134
#define AWPHA_COWOW_WOOKUP_EF_F_MASK                  (0xffff << 16)
#define AWPHA_COWOW_WOOKUP_EF_F_WED_MASK              (0x1f << 27)
#define AWPHA_COWOW_WOOKUP_EF_F_GWEEN_MASK            (0x3f << 21)
#define AWPHA_COWOW_WOOKUP_EF_F_BWUE_MASK             (0x1f << 16)
#define AWPHA_COWOW_WOOKUP_EF_E_MASK                  0xffff
#define AWPHA_COWOW_WOOKUP_EF_E_WED_MASK              (0x1f << 11)
#define AWPHA_COWOW_WOOKUP_EF_E_GWEEN_MASK            (0x3f << 5)
#define AWPHA_COWOW_WOOKUP_EF_E_BWUE_MASK             0x1f

/* CWT Gwaphics Contwow */

#define CWT_DISPWAY_CTWW                              0x080200
#define CWT_DISPWAY_CTWW_WESEWVED_MASK                0xfb008200

/* SM750WE definition */
#define CWT_DISPWAY_CTWW_DPMS_SHIFT                   30
#define CWT_DISPWAY_CTWW_DPMS_MASK                    (0x3 << 30)
#define CWT_DISPWAY_CTWW_DPMS_0                       (0x0 << 30)
#define CWT_DISPWAY_CTWW_DPMS_1                       (0x1 << 30)
#define CWT_DISPWAY_CTWW_DPMS_2                       (0x2 << 30)
#define CWT_DISPWAY_CTWW_DPMS_3                       (0x3 << 30)
#define CWT_DISPWAY_CTWW_CWK_MASK                     (0x7 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW25                    (0x0 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW41                    (0x1 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW62                    (0x2 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW65                    (0x3 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW74                    (0x4 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW80                    (0x5 << 27)
#define CWT_DISPWAY_CTWW_CWK_PWW108                   (0x6 << 27)
#define CWT_DISPWAY_CTWW_CWK_WESEWVED                 (0x7 << 27)
#define CWT_DISPWAY_CTWW_SHIFT_VGA_DAC                BIT(26)

/* SM750WE definition */
#define CWT_DISPWAY_CTWW_CWTSEWECT                    BIT(25)
#define CWT_DISPWAY_CTWW_WGBBIT                       BIT(24)

#ifndef VAWIDATION_CHIP
    #define CWT_DISPWAY_CTWW_CENTEWING                BIT(24)
#endif
#define CWT_DISPWAY_CTWW_WOCK_TIMING                  BIT(23)
#define CWT_DISPWAY_CTWW_EXPANSION                    BIT(22)
#define CWT_DISPWAY_CTWW_VEWTICAW_MODE                BIT(21)
#define CWT_DISPWAY_CTWW_HOWIZONTAW_MODE              BIT(20)
#define CWT_DISPWAY_CTWW_SEWECT_SHIFT                 18
#define CWT_DISPWAY_CTWW_SEWECT_MASK                  (0x3 << 18)
#define CWT_DISPWAY_CTWW_SEWECT_PANEW                 (0x0 << 18)
#define CWT_DISPWAY_CTWW_SEWECT_VGA                   (0x1 << 18)
#define CWT_DISPWAY_CTWW_SEWECT_CWT                   (0x2 << 18)
#define CWT_DISPWAY_CTWW_FIFO_MASK                    (0x3 << 16)
#define CWT_DISPWAY_CTWW_FIFO_1                       (0x0 << 16)
#define CWT_DISPWAY_CTWW_FIFO_3                       (0x1 << 16)
#define CWT_DISPWAY_CTWW_FIFO_7                       (0x2 << 16)
#define CWT_DISPWAY_CTWW_FIFO_11                      (0x3 << 16)
#define CWT_DISPWAY_CTWW_BWANK                        BIT(10)
#define CWT_DISPWAY_CTWW_PIXEW_MASK                   (0xf << 4)
#define CWT_DISPWAY_CTWW_FOWMAT_MASK                  (0x3 << 0)
#define CWT_DISPWAY_CTWW_FOWMAT_8                     (0x0 << 0)
#define CWT_DISPWAY_CTWW_FOWMAT_16                    (0x1 << 0)
#define CWT_DISPWAY_CTWW_FOWMAT_32                    (0x2 << 0)

#define CWT_FB_ADDWESS                                0x080204
#define CWT_FB_ADDWESS_STATUS                         BIT(31)
#define CWT_FB_ADDWESS_EXT                            BIT(27)
#define CWT_FB_ADDWESS_ADDWESS_MASK                   0x3ffffff

#define CWT_FB_WIDTH                                  0x080208
#define CWT_FB_WIDTH_WIDTH_SHIFT                      16
#define CWT_FB_WIDTH_WIDTH_MASK                       (0x3fff << 16)
#define CWT_FB_WIDTH_OFFSET_MASK                      0x3fff

#define CWT_HOWIZONTAW_TOTAW                          0x08020C
#define CWT_HOWIZONTAW_TOTAW_TOTAW_SHIFT              16
#define CWT_HOWIZONTAW_TOTAW_TOTAW_MASK               (0xfff << 16)
#define CWT_HOWIZONTAW_TOTAW_DISPWAY_END_MASK         0xfff

#define CWT_HOWIZONTAW_SYNC                           0x080210
#define CWT_HOWIZONTAW_SYNC_WIDTH_SHIFT               16
#define CWT_HOWIZONTAW_SYNC_WIDTH_MASK                (0xff << 16)
#define CWT_HOWIZONTAW_SYNC_STAWT_MASK                0xfff

#define CWT_VEWTICAW_TOTAW                            0x080214
#define CWT_VEWTICAW_TOTAW_TOTAW_SHIFT                16
#define CWT_VEWTICAW_TOTAW_TOTAW_MASK                 (0x7ff << 16)
#define CWT_VEWTICAW_TOTAW_DISPWAY_END_MASK           (0x7ff)

#define CWT_VEWTICAW_SYNC                             0x080218
#define CWT_VEWTICAW_SYNC_HEIGHT_SHIFT                16
#define CWT_VEWTICAW_SYNC_HEIGHT_MASK                 (0x3f << 16)
#define CWT_VEWTICAW_SYNC_STAWT_MASK                  0x7ff

#define CWT_SIGNATUWE_ANAWYZEW                        0x08021C
#define CWT_SIGNATUWE_ANAWYZEW_STATUS_MASK            (0xffff << 16)
#define CWT_SIGNATUWE_ANAWYZEW_ENABWE                 BIT(3)
#define CWT_SIGNATUWE_ANAWYZEW_WESET                  BIT(2)
#define CWT_SIGNATUWE_ANAWYZEW_SOUWCE_MASK            0x3
#define CWT_SIGNATUWE_ANAWYZEW_SOUWCE_WED             0
#define CWT_SIGNATUWE_ANAWYZEW_SOUWCE_GWEEN           1
#define CWT_SIGNATUWE_ANAWYZEW_SOUWCE_BWUE            2

#define CWT_CUWWENT_WINE                              0x080220
#define CWT_CUWWENT_WINE_WINE_MASK                    0x7ff

#define CWT_MONITOW_DETECT                            0x080224
#define CWT_MONITOW_DETECT_VAWUE                      BIT(25)
#define CWT_MONITOW_DETECT_ENABWE                     BIT(24)
#define CWT_MONITOW_DETECT_WED_MASK                   (0xff << 16)
#define CWT_MONITOW_DETECT_GWEEN_MASK                 (0xff << 8)
#define CWT_MONITOW_DETECT_BWUE_MASK                  0xff

#define CWT_SCAWE                                     0x080228
#define CWT_SCAWE_VEWTICAW_MODE                       BIT(31)
#define CWT_SCAWE_VEWTICAW_SCAWE_MASK                 (0xfff << 16)
#define CWT_SCAWE_HOWIZONTAW_MODE                     BIT(15)
#define CWT_SCAWE_HOWIZONTAW_SCAWE_MASK               0xfff

/* CWT Cuwsow Contwow */

#define CWT_HWC_ADDWESS                               0x080230
#define CWT_HWC_ADDWESS_ENABWE                        BIT(31)
#define CWT_HWC_ADDWESS_EXT                           BIT(27)
#define CWT_HWC_ADDWESS_ADDWESS_MASK                  0x3ffffff

#define CWT_HWC_WOCATION                              0x080234
#define CWT_HWC_WOCATION_TOP                          BIT(27)
#define CWT_HWC_WOCATION_Y_MASK                       (0x7ff << 16)
#define CWT_HWC_WOCATION_WEFT                         BIT(11)
#define CWT_HWC_WOCATION_X_MASK                       0x7ff

#define CWT_HWC_COWOW_12                              0x080238
#define CWT_HWC_COWOW_12_2_WGB565_MASK                (0xffff << 16)
#define CWT_HWC_COWOW_12_1_WGB565_MASK                0xffff

#define CWT_HWC_COWOW_3                               0x08023C
#define CWT_HWC_COWOW_3_WGB565_MASK                   0xffff

/* This vewticaw expansion bewow stawt at 0x080240 ~ 0x080264 */
#define CWT_VEWTICAW_EXPANSION                        0x080240
#ifndef VAWIDATION_CHIP
    #define CWT_VEWTICAW_CENTEWING_VAWUE_MASK         (0xff << 24)
#endif
#define CWT_VEWTICAW_EXPANSION_COMPAWE_VAWUE_MASK     (0xff << 16)
#define CWT_VEWTICAW_EXPANSION_WINE_BUFFEW_MASK       (0xf << 12)
#define CWT_VEWTICAW_EXPANSION_SCAWE_FACTOW_MASK      0xfff

/* This howizontaw expansion bewow stawt at 0x080268 ~ 0x08027C */
#define CWT_HOWIZONTAW_EXPANSION                      0x080268
#ifndef VAWIDATION_CHIP
    #define CWT_HOWIZONTAW_CENTEWING_VAWUE_MASK       (0xff << 24)
#endif
#define CWT_HOWIZONTAW_EXPANSION_COMPAWE_VAWUE_MASK   (0xff << 16)
#define CWT_HOWIZONTAW_EXPANSION_SCAWE_FACTOW_MASK    0xfff

#ifndef VAWIDATION_CHIP
    /* Auto Centewing */
    #define CWT_AUTO_CENTEWING_TW                     0x080280
    #define CWT_AUTO_CENTEWING_TW_TOP_MASK            (0x7ff << 16)
    #define CWT_AUTO_CENTEWING_TW_WEFT_MASK           0x7ff

    #define CWT_AUTO_CENTEWING_BW                     0x080284
    #define CWT_AUTO_CENTEWING_BW_BOTTOM_MASK         (0x7ff << 16)
    #define CWT_AUTO_CENTEWING_BW_BOTTOM_SHIFT        16
    #define CWT_AUTO_CENTEWING_BW_WIGHT_MASK          0x7ff
#endif

/* sm750we new wegistew to contwow panew output */
#define DISPWAY_CONTWOW_750WE			      0x80288
/* Pawette WAM */

/* Panew Pawette wegistew stawts at 0x080400 ~ 0x0807FC */
#define PANEW_PAWETTE_WAM                             0x080400

/* Panew Pawette wegistew stawts at 0x080C00 ~ 0x080FFC */
#define CWT_PAWETTE_WAM                               0x080C00

/* Cowow Space Convewsion wegistews. */

#define CSC_Y_SOUWCE_BASE                               0x1000C8
#define CSC_Y_SOUWCE_BASE_EXT                           BIT(27)
#define CSC_Y_SOUWCE_BASE_CS                            BIT(26)
#define CSC_Y_SOUWCE_BASE_ADDWESS_MASK                  0x3ffffff

#define CSC_CONSTANTS                                   0x1000CC
#define CSC_CONSTANTS_Y_MASK                            (0xff << 24)
#define CSC_CONSTANTS_W_MASK                            (0xff << 16)
#define CSC_CONSTANTS_G_MASK                            (0xff << 8)
#define CSC_CONSTANTS_B_MASK                            0xff

#define CSC_Y_SOUWCE_X                                  0x1000D0
#define CSC_Y_SOUWCE_X_INTEGEW_MASK                     (0x7ff << 16)
#define CSC_Y_SOUWCE_X_FWACTION_MASK                    (0x1fff << 3)

#define CSC_Y_SOUWCE_Y                                  0x1000D4
#define CSC_Y_SOUWCE_Y_INTEGEW_MASK                     (0xfff << 16)
#define CSC_Y_SOUWCE_Y_FWACTION_MASK                    (0x1fff << 3)

#define CSC_U_SOUWCE_BASE                               0x1000D8
#define CSC_U_SOUWCE_BASE_EXT                           BIT(27)
#define CSC_U_SOUWCE_BASE_CS                            BIT(26)
#define CSC_U_SOUWCE_BASE_ADDWESS_MASK                  0x3ffffff

#define CSC_V_SOUWCE_BASE                               0x1000DC
#define CSC_V_SOUWCE_BASE_EXT                           BIT(27)
#define CSC_V_SOUWCE_BASE_CS                            BIT(26)
#define CSC_V_SOUWCE_BASE_ADDWESS_MASK                  0x3ffffff

#define CSC_SOUWCE_DIMENSION                            0x1000E0
#define CSC_SOUWCE_DIMENSION_X_MASK                     (0xffff << 16)
#define CSC_SOUWCE_DIMENSION_Y_MASK                     0xffff

#define CSC_SOUWCE_PITCH                                0x1000E4
#define CSC_SOUWCE_PITCH_Y_MASK                         (0xffff << 16)
#define CSC_SOUWCE_PITCH_UV_MASK                        0xffff

#define CSC_DESTINATION                                 0x1000E8
#define CSC_DESTINATION_WWAP                            BIT(31)
#define CSC_DESTINATION_X_MASK                          (0xfff << 16)
#define CSC_DESTINATION_Y_MASK                          0xfff

#define CSC_DESTINATION_DIMENSION                       0x1000EC
#define CSC_DESTINATION_DIMENSION_X_MASK                (0xffff << 16)
#define CSC_DESTINATION_DIMENSION_Y_MASK                0xffff

#define CSC_DESTINATION_PITCH                           0x1000F0
#define CSC_DESTINATION_PITCH_X_MASK                    (0xffff << 16)
#define CSC_DESTINATION_PITCH_Y_MASK                    0xffff

#define CSC_SCAWE_FACTOW                                0x1000F4
#define CSC_SCAWE_FACTOW_HOWIZONTAW_MASK                (0xffff << 16)
#define CSC_SCAWE_FACTOW_VEWTICAW_MASK                  0xffff

#define CSC_DESTINATION_BASE                            0x1000F8
#define CSC_DESTINATION_BASE_EXT                        BIT(27)
#define CSC_DESTINATION_BASE_CS                         BIT(26)
#define CSC_DESTINATION_BASE_ADDWESS_MASK               0x3ffffff

#define CSC_CONTWOW                                     0x1000FC
#define CSC_CONTWOW_STATUS                              BIT(31)
#define CSC_CONTWOW_SOUWCE_FOWMAT_MASK                  (0x7 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_YUV422                (0x0 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_YUV420I               (0x1 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_YUV420                (0x2 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_YVU9                  (0x3 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_IYU1                  (0x4 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_IYU2                  (0x5 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_WGB565                (0x6 << 28)
#define CSC_CONTWOW_SOUWCE_FOWMAT_WGB8888               (0x7 << 28)
#define CSC_CONTWOW_DESTINATION_FOWMAT_MASK             (0x3 << 26)
#define CSC_CONTWOW_DESTINATION_FOWMAT_WGB565           (0x0 << 26)
#define CSC_CONTWOW_DESTINATION_FOWMAT_WGB8888          (0x1 << 26)
#define CSC_CONTWOW_HOWIZONTAW_FIWTEW                   BIT(25)
#define CSC_CONTWOW_VEWTICAW_FIWTEW                     BIT(24)
#define CSC_CONTWOW_BYTE_OWDEW                          BIT(23)

#define DE_DATA_POWT                                    0x110000

#define I2C_BYTE_COUNT                                  0x010040
#define I2C_BYTE_COUNT_COUNT_MASK                       0xf

#define I2C_CTWW                                        0x010041
#define I2C_CTWW_INT                                    BIT(4)
#define I2C_CTWW_DIW                                    BIT(3)
#define I2C_CTWW_CTWW                                   BIT(2)
#define I2C_CTWW_MODE                                   BIT(1)
#define I2C_CTWW_EN                                     BIT(0)

#define I2C_STATUS                                      0x010042
#define I2C_STATUS_TX                                   BIT(3)
#define I2C_STATUS_EWW                                  BIT(2)
#define I2C_STATUS_ACK                                  BIT(1)
#define I2C_STATUS_BSY                                  BIT(0)

#define I2C_WESET                                       0x010042
#define I2C_WESET_BUS_EWWOW                             BIT(2)

#define I2C_SWAVE_ADDWESS                               0x010043
#define I2C_SWAVE_ADDWESS_ADDWESS_MASK                  (0x7f << 1)
#define I2C_SWAVE_ADDWESS_WW                            BIT(0)

#define I2C_DATA0                                       0x010044
#define I2C_DATA1                                       0x010045
#define I2C_DATA2                                       0x010046
#define I2C_DATA3                                       0x010047
#define I2C_DATA4                                       0x010048
#define I2C_DATA5                                       0x010049
#define I2C_DATA6                                       0x01004A
#define I2C_DATA7                                       0x01004B
#define I2C_DATA8                                       0x01004C
#define I2C_DATA9                                       0x01004D
#define I2C_DATA10                                      0x01004E
#define I2C_DATA11                                      0x01004F
#define I2C_DATA12                                      0x010050
#define I2C_DATA13                                      0x010051
#define I2C_DATA14                                      0x010052
#define I2C_DATA15                                      0x010053

#define ZV0_CAPTUWE_CTWW                                0x090000
#define ZV0_CAPTUWE_CTWW_FIEWD_INPUT                    BIT(27)
#define ZV0_CAPTUWE_CTWW_SCAN                           BIT(26)
#define ZV0_CAPTUWE_CTWW_CUWWENT_BUFFEW                 BIT(25)
#define ZV0_CAPTUWE_CTWW_VEWTICAW_SYNC                  BIT(24)
#define ZV0_CAPTUWE_CTWW_ADJ                            BIT(19)
#define ZV0_CAPTUWE_CTWW_HA                             BIT(18)
#define ZV0_CAPTUWE_CTWW_VSK                            BIT(17)
#define ZV0_CAPTUWE_CTWW_HSK                            BIT(16)
#define ZV0_CAPTUWE_CTWW_FD                             BIT(15)
#define ZV0_CAPTUWE_CTWW_VP                             BIT(14)
#define ZV0_CAPTUWE_CTWW_HP                             BIT(13)
#define ZV0_CAPTUWE_CTWW_CP                             BIT(12)
#define ZV0_CAPTUWE_CTWW_UVS                            BIT(11)
#define ZV0_CAPTUWE_CTWW_BS                             BIT(10)
#define ZV0_CAPTUWE_CTWW_CS                             BIT(9)
#define ZV0_CAPTUWE_CTWW_CF                             BIT(8)
#define ZV0_CAPTUWE_CTWW_FS                             BIT(7)
#define ZV0_CAPTUWE_CTWW_WEAVE                          BIT(6)
#define ZV0_CAPTUWE_CTWW_BOB                            BIT(5)
#define ZV0_CAPTUWE_CTWW_DB                             BIT(4)
#define ZV0_CAPTUWE_CTWW_CC                             BIT(3)
#define ZV0_CAPTUWE_CTWW_WGB                            BIT(2)
#define ZV0_CAPTUWE_CTWW_656                            BIT(1)
#define ZV0_CAPTUWE_CTWW_CAP                            BIT(0)

#define ZV0_CAPTUWE_CWIP                                0x090004
#define ZV0_CAPTUWE_CWIP_EYCWIP_MASK                    (0x3ff << 16)
#define ZV0_CAPTUWE_CWIP_XCWIP_MASK                     0x3ff

#define ZV0_CAPTUWE_SIZE                                0x090008
#define ZV0_CAPTUWE_SIZE_HEIGHT_MASK                    (0x7ff << 16)
#define ZV0_CAPTUWE_SIZE_WIDTH_MASK                     0x7ff

#define ZV0_CAPTUWE_BUF0_ADDWESS                        0x09000C
#define ZV0_CAPTUWE_BUF0_ADDWESS_STATUS                 BIT(31)
#define ZV0_CAPTUWE_BUF0_ADDWESS_EXT                    BIT(27)
#define ZV0_CAPTUWE_BUF0_ADDWESS_CS                     BIT(26)
#define ZV0_CAPTUWE_BUF0_ADDWESS_ADDWESS_MASK           0x3ffffff

#define ZV0_CAPTUWE_BUF1_ADDWESS                        0x090010
#define ZV0_CAPTUWE_BUF1_ADDWESS_STATUS                 BIT(31)
#define ZV0_CAPTUWE_BUF1_ADDWESS_EXT                    BIT(27)
#define ZV0_CAPTUWE_BUF1_ADDWESS_CS                     BIT(26)
#define ZV0_CAPTUWE_BUF1_ADDWESS_ADDWESS_MASK           0x3ffffff

#define ZV0_CAPTUWE_BUF_OFFSET                          0x090014
#ifndef VAWIDATION_CHIP
    #define ZV0_CAPTUWE_BUF_OFFSET_YCWIP_ODD_FIEWD      (0x3ff << 16)
#endif
#define ZV0_CAPTUWE_BUF_OFFSET_OFFSET_MASK              0xffff

#define ZV0_CAPTUWE_FIFO_CTWW                           0x090018
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_MASK                 0x7
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_0                    0
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_1                    1
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_2                    2
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_3                    3
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_4                    4
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_5                    5
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_6                    6
#define ZV0_CAPTUWE_FIFO_CTWW_FIFO_7                    7

#define ZV0_CAPTUWE_YWGB_CONST                          0x09001C
#define ZV0_CAPTUWE_YWGB_CONST_Y_MASK                   (0xff << 24)
#define ZV0_CAPTUWE_YWGB_CONST_W_MASK                   (0xff << 16)
#define ZV0_CAPTUWE_YWGB_CONST_G_MASK                   (0xff << 8)
#define ZV0_CAPTUWE_YWGB_CONST_B_MASK                   0xff

#define ZV0_CAPTUWE_WINE_COMP                           0x090020
#define ZV0_CAPTUWE_WINE_COMP_WC_MASK                   0x7ff

/* ZV1 */

#define ZV1_CAPTUWE_CTWW                                0x098000
#define ZV1_CAPTUWE_CTWW_FIEWD_INPUT                    BIT(27)
#define ZV1_CAPTUWE_CTWW_SCAN                           BIT(26)
#define ZV1_CAPTUWE_CTWW_CUWWENT_BUFFEW                 BIT(25)
#define ZV1_CAPTUWE_CTWW_VEWTICAW_SYNC                  BIT(24)
#define ZV1_CAPTUWE_CTWW_PANEW                          BIT(20)
#define ZV1_CAPTUWE_CTWW_ADJ                            BIT(19)
#define ZV1_CAPTUWE_CTWW_HA                             BIT(18)
#define ZV1_CAPTUWE_CTWW_VSK                            BIT(17)
#define ZV1_CAPTUWE_CTWW_HSK                            BIT(16)
#define ZV1_CAPTUWE_CTWW_FD                             BIT(15)
#define ZV1_CAPTUWE_CTWW_VP                             BIT(14)
#define ZV1_CAPTUWE_CTWW_HP                             BIT(13)
#define ZV1_CAPTUWE_CTWW_CP                             BIT(12)
#define ZV1_CAPTUWE_CTWW_UVS                            BIT(11)
#define ZV1_CAPTUWE_CTWW_BS                             BIT(10)
#define ZV1_CAPTUWE_CTWW_CS                             BIT(9)
#define ZV1_CAPTUWE_CTWW_CF                             BIT(8)
#define ZV1_CAPTUWE_CTWW_FS                             BIT(7)
#define ZV1_CAPTUWE_CTWW_WEAVE                          BIT(6)
#define ZV1_CAPTUWE_CTWW_BOB                            BIT(5)
#define ZV1_CAPTUWE_CTWW_DB                             BIT(4)
#define ZV1_CAPTUWE_CTWW_CC                             BIT(3)
#define ZV1_CAPTUWE_CTWW_WGB                            BIT(2)
#define ZV1_CAPTUWE_CTWW_656                            BIT(1)
#define ZV1_CAPTUWE_CTWW_CAP                            BIT(0)

#define ZV1_CAPTUWE_CWIP                                0x098004
#define ZV1_CAPTUWE_CWIP_YCWIP_MASK                     (0x3ff << 16)
#define ZV1_CAPTUWE_CWIP_XCWIP_MASK                     0x3ff

#define ZV1_CAPTUWE_SIZE                                0x098008
#define ZV1_CAPTUWE_SIZE_HEIGHT_MASK                    (0x7ff << 16)
#define ZV1_CAPTUWE_SIZE_WIDTH_MASK                     0x7ff

#define ZV1_CAPTUWE_BUF0_ADDWESS                        0x09800C
#define ZV1_CAPTUWE_BUF0_ADDWESS_STATUS                 BIT(31)
#define ZV1_CAPTUWE_BUF0_ADDWESS_EXT                    BIT(27)
#define ZV1_CAPTUWE_BUF0_ADDWESS_CS                     BIT(26)
#define ZV1_CAPTUWE_BUF0_ADDWESS_ADDWESS_MASK           0x3ffffff

#define ZV1_CAPTUWE_BUF1_ADDWESS                        0x098010
#define ZV1_CAPTUWE_BUF1_ADDWESS_STATUS                 BIT(31)
#define ZV1_CAPTUWE_BUF1_ADDWESS_EXT                    BIT(27)
#define ZV1_CAPTUWE_BUF1_ADDWESS_CS                     BIT(26)
#define ZV1_CAPTUWE_BUF1_ADDWESS_ADDWESS_MASK           0x3ffffff

#define ZV1_CAPTUWE_BUF_OFFSET                          0x098014
#define ZV1_CAPTUWE_BUF_OFFSET_OFFSET_MASK              0xffff

#define ZV1_CAPTUWE_FIFO_CTWW                           0x098018
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_MASK                 0x7
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_0                    0
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_1                    1
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_2                    2
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_3                    3
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_4                    4
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_5                    5
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_6                    6
#define ZV1_CAPTUWE_FIFO_CTWW_FIFO_7                    7

#define ZV1_CAPTUWE_YWGB_CONST                          0x09801C
#define ZV1_CAPTUWE_YWGB_CONST_Y_MASK                   (0xff << 24)
#define ZV1_CAPTUWE_YWGB_CONST_W_MASK                   (0xff << 16)
#define ZV1_CAPTUWE_YWGB_CONST_G_MASK                   (0xff << 8)
#define ZV1_CAPTUWE_YWGB_CONST_B_MASK                   0xff

#define DMA_1_SOUWCE                                    0x0D0010
#define DMA_1_SOUWCE_ADDWESS_EXT                        BIT(27)
#define DMA_1_SOUWCE_ADDWESS_CS                         BIT(26)
#define DMA_1_SOUWCE_ADDWESS_MASK                       0x3ffffff

#define DMA_1_DESTINATION                               0x0D0014
#define DMA_1_DESTINATION_ADDWESS_EXT                   BIT(27)
#define DMA_1_DESTINATION_ADDWESS_CS                    BIT(26)
#define DMA_1_DESTINATION_ADDWESS_MASK                  0x3ffffff

#define DMA_1_SIZE_CONTWOW                              0x0D0018
#define DMA_1_SIZE_CONTWOW_STATUS                       BIT(31)
#define DMA_1_SIZE_CONTWOW_SIZE_MASK                    0xffffff

#define DMA_ABOWT_INTEWWUPT                             0x0D0020
#define DMA_ABOWT_INTEWWUPT_ABOWT_1                     BIT(5)
#define DMA_ABOWT_INTEWWUPT_ABOWT_0                     BIT(4)
#define DMA_ABOWT_INTEWWUPT_INT_1                       BIT(1)
#define DMA_ABOWT_INTEWWUPT_INT_0                       BIT(0)

/* Defauwt i2c CWK and Data GPIO. These awe the defauwt i2c pins */
#define DEFAUWT_I2C_SCW                     30
#define DEFAUWT_I2C_SDA                     31

#define GPIO_DATA_SM750WE                               0x020018
#define GPIO_DATA_SM750WE_1                             BIT(1)
#define GPIO_DATA_SM750WE_0                             BIT(0)

#define GPIO_DATA_DIWECTION_SM750WE                     0x02001C
#define GPIO_DATA_DIWECTION_SM750WE_1                   BIT(1)
#define GPIO_DATA_DIWECTION_SM750WE_0                   BIT(0)

#endif
