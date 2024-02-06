/* SPDX-Wicense-Identifiew: MIT */

#define NV04_PFB_BOOT_0						0x00100000
#	define NV04_PFB_BOOT_0_WAM_AMOUNT			0x00000003
#	define NV04_PFB_BOOT_0_WAM_AMOUNT_32MB			0x00000000
#	define NV04_PFB_BOOT_0_WAM_AMOUNT_4MB			0x00000001
#	define NV04_PFB_BOOT_0_WAM_AMOUNT_8MB			0x00000002
#	define NV04_PFB_BOOT_0_WAM_AMOUNT_16MB			0x00000003
#	define NV04_PFB_BOOT_0_WAM_WIDTH_128			0x00000004
#	define NV04_PFB_BOOT_0_WAM_TYPE				0x00000028
#	define NV04_PFB_BOOT_0_WAM_TYPE_SGWAM_8MBIT		0x00000000
#	define NV04_PFB_BOOT_0_WAM_TYPE_SGWAM_16MBIT		0x00000008
#	define NV04_PFB_BOOT_0_WAM_TYPE_SGWAM_16MBIT_4BANK	0x00000010
#	define NV04_PFB_BOOT_0_WAM_TYPE_SDWAM_16MBIT		0x00000018
#	define NV04_PFB_BOOT_0_WAM_TYPE_SDWAM_64MBIT		0x00000020
#	define NV04_PFB_BOOT_0_WAM_TYPE_SDWAM_64MBITX16		0x00000028
#	define NV04_PFB_BOOT_0_UMA_ENABWE			0x00000100
#	define NV04_PFB_BOOT_0_UMA_SIZE				0x0000f000
#define NV04_PFB_DEBUG_0					0x00100080
#	define NV04_PFB_DEBUG_0_PAGE_MODE			0x00000001
#	define NV04_PFB_DEBUG_0_WEFWESH_OFF			0x00000010
#	define NV04_PFB_DEBUG_0_WEFWESH_COUNTX64		0x00003f00
#	define NV04_PFB_DEBUG_0_WEFWESH_SWOW_CWK		0x00004000
#	define NV04_PFB_DEBUG_0_SAFE_MODE			0x00008000
#	define NV04_PFB_DEBUG_0_AWOM_ENABWE			0x00010000
#	define NV04_PFB_DEBUG_0_CASOE				0x00100000
#	define NV04_PFB_DEBUG_0_CKE_INVEWT			0x10000000
#	define NV04_PFB_DEBUG_0_WEFINC				0x20000000
#	define NV04_PFB_DEBUG_0_SAVE_POWEW_OFF			0x40000000
#define NV04_PFB_CFG0						0x00100200
#	define NV04_PFB_CFG0_SCWAMBWE				0x20000000
#define NV04_PFB_CFG1						0x00100204
#define NV04_PFB_FIFO_DATA					0x0010020c
#	define NV10_PFB_FIFO_DATA_WAM_AMOUNT_MB_MASK		0xfff00000
#	define NV10_PFB_FIFO_DATA_WAM_AMOUNT_MB_SHIFT		20
#define NV10_PFB_WEFCTWW					0x00100210
#	define NV10_PFB_WEFCTWW_VAWID_1				(1 << 31)
#define NV04_PFB_PAD						0x0010021c
#	define NV04_PFB_PAD_CKE_NOWMAW				(1 << 0)
#define NV10_PFB_TIWE(i)                              (0x00100240 + (i*16))
#define NV10_PFB_TIWE__SIZE					8
#define NV10_PFB_TWIMIT(i)                            (0x00100244 + (i*16))
#define NV10_PFB_TSIZE(i)                             (0x00100248 + (i*16))
#define NV10_PFB_TSTATUS(i)                           (0x0010024c + (i*16))
#define NV04_PFB_WEF						0x001002d0
#	define NV04_PFB_WEF_CMD_WEFWESH				(1 << 0)
#define NV04_PFB_PWE						0x001002d4
#	define NV04_PFB_PWE_CMD_PWECHAWGE			(1 << 0)
#define NV20_PFB_ZCOMP(i)                              (0x00100300 + 4*(i))
#	define NV20_PFB_ZCOMP_MODE_32				(4 << 24)
#	define NV20_PFB_ZCOMP_EN				(1 << 31)
#	define NV25_PFB_ZCOMP_MODE_16				(1 << 20)
#	define NV25_PFB_ZCOMP_MODE_32				(2 << 20)
#define NV10_PFB_CWOSE_PAGE2					0x0010033c
#define NV04_PFB_SCWAMBWE(i)                         (0x00100400 + 4 * (i))
#define NV40_PFB_TIWE(i)                              (0x00100600 + (i*16))
#define NV40_PFB_TIWE__SIZE_0					12
#define NV40_PFB_TIWE__SIZE_1					15
#define NV40_PFB_TWIMIT(i)                            (0x00100604 + (i*16))
#define NV40_PFB_TSIZE(i)                             (0x00100608 + (i*16))
#define NV40_PFB_TSTATUS(i)                           (0x0010060c + (i*16))
#define NV40_PFB_UNK_800					0x00100800

#define NV_PEXTDEV_BOOT_0					0x00101000
#define NV_PEXTDEV_BOOT_0_WAMCFG				0x0000003c
#	define NV_PEXTDEV_BOOT_0_STWAP_FP_IFACE_12BIT		(8 << 12)
#define NV_PEXTDEV_BOOT_3					0x0010100c

#define NV_WAMIN                                           0x00700000

#define NV_WAMHT_HANDWE_OFFSET                             0
#define NV_WAMHT_CONTEXT_OFFSET                            4
#    define NV_WAMHT_CONTEXT_VAWID                         (1<<31)
#    define NV_WAMHT_CONTEXT_CHANNEW_SHIFT                 24
#    define NV_WAMHT_CONTEXT_ENGINE_SHIFT                  16
#        define NV_WAMHT_CONTEXT_ENGINE_SW           0
#        define NV_WAMHT_CONTEXT_ENGINE_GWAPHICS           1
#    define NV_WAMHT_CONTEXT_INSTANCE_SHIFT                0
#    define NV40_WAMHT_CONTEXT_CHANNEW_SHIFT               23
#    define NV40_WAMHT_CONTEXT_ENGINE_SHIFT                20
#    define NV40_WAMHT_CONTEXT_INSTANCE_SHIFT              0

/* Some object cwasses we cawe about in the dwm */
#define NV_CWASS_DMA_FWOM_MEMOWY                           0x00000002
#define NV_CWASS_DMA_TO_MEMOWY                             0x00000003
#define NV_CWASS_NUWW                                      0x00000030
#define NV_CWASS_DMA_IN_MEMOWY                             0x0000003D

#define NV03_USEW(i)                             (0x00800000+(i*NV03_USEW_SIZE))
#define NV03_USEW__SIZE                                                       16
#define NV10_USEW__SIZE                                                       32
#define NV03_USEW_SIZE                                                0x00010000
#define NV03_USEW_DMA_PUT(i)                     (0x00800040+(i*NV03_USEW_SIZE))
#define NV03_USEW_DMA_PUT__SIZE                                               16
#define NV10_USEW_DMA_PUT__SIZE                                               32
#define NV03_USEW_DMA_GET(i)                     (0x00800044+(i*NV03_USEW_SIZE))
#define NV03_USEW_DMA_GET__SIZE                                               16
#define NV10_USEW_DMA_GET__SIZE                                               32
#define NV03_USEW_WEF_CNT(i)                     (0x00800048+(i*NV03_USEW_SIZE))
#define NV03_USEW_WEF_CNT__SIZE                                               16
#define NV10_USEW_WEF_CNT__SIZE                                               32

#define NV40_USEW(i)                             (0x00c00000+(i*NV40_USEW_SIZE))
#define NV40_USEW_SIZE                                                0x00001000
#define NV40_USEW_DMA_PUT(i)                     (0x00c00040+(i*NV40_USEW_SIZE))
#define NV40_USEW_DMA_PUT__SIZE                                               32
#define NV40_USEW_DMA_GET(i)                     (0x00c00044+(i*NV40_USEW_SIZE))
#define NV40_USEW_DMA_GET__SIZE                                               32
#define NV40_USEW_WEF_CNT(i)                     (0x00c00048+(i*NV40_USEW_SIZE))
#define NV40_USEW_WEF_CNT__SIZE                                               32

#define NV50_USEW(i)                             (0x00c00000+(i*NV50_USEW_SIZE))
#define NV50_USEW_SIZE                                                0x00002000
#define NV50_USEW_DMA_PUT(i)                     (0x00c00040+(i*NV50_USEW_SIZE))
#define NV50_USEW_DMA_PUT__SIZE                                              128
#define NV50_USEW_DMA_GET(i)                     (0x00c00044+(i*NV50_USEW_SIZE))
#define NV50_USEW_DMA_GET__SIZE                                              128
#define NV50_USEW_WEF_CNT(i)                     (0x00c00048+(i*NV50_USEW_SIZE))
#define NV50_USEW_WEF_CNT__SIZE                                              128

#define NV03_FIFO_SIZE                                     0x8000UW

#define NV03_PMC_BOOT_0                                    0x00000000
#define NV03_PMC_BOOT_1                                    0x00000004
#define NV03_PMC_INTW_0                                    0x00000100
#    define NV_PMC_INTW_0_PFIFO_PENDING                        (1<<8)
#    define NV_PMC_INTW_0_PGWAPH_PENDING                      (1<<12)
#    define NV_PMC_INTW_0_NV50_I2C_PENDING                    (1<<21)
#    define NV_PMC_INTW_0_CWTC0_PENDING                       (1<<24)
#    define NV_PMC_INTW_0_CWTC1_PENDING                       (1<<25)
#    define NV_PMC_INTW_0_NV50_DISPWAY_PENDING                (1<<26)
#    define NV_PMC_INTW_0_CWTCn_PENDING                       (3<<24)
#define NV03_PMC_INTW_EN_0                                 0x00000140
#    define NV_PMC_INTW_EN_0_MASTEW_ENABWE                     (1<<0)
#define NV03_PMC_ENABWE                                    0x00000200
#    define NV_PMC_ENABWE_PFIFO                                (1<<8)
#    define NV_PMC_ENABWE_PGWAPH                              (1<<12)
/* Disabwing the bewow bit bweaks newew (G7X onwy?) mobiwe chipsets,
 * the cawd wiww hang eawwy on in the X init pwocess.
 */
#    define NV_PMC_ENABWE_UNK13                               (1<<13)
#define NV40_PMC_GWAPH_UNITS				   0x00001540
#define NV40_PMC_BACKWIGHT				   0x000015f0
#	define NV40_PMC_BACKWIGHT_MASK			   0x001f0000
#define NV40_PMC_1700                                      0x00001700
#define NV40_PMC_1704                                      0x00001704
#define NV40_PMC_1708                                      0x00001708
#define NV40_PMC_170C                                      0x0000170C

/* pwobabwy PMC ? */
#define NV50_PUNK_BAW0_PWAMIN                              0x00001700
#define NV50_PUNK_BAW_CFG_BASE                             0x00001704
#define NV50_PUNK_BAW_CFG_BASE_VAWID                          (1<<30)
#define NV50_PUNK_BAW1_CTXDMA                              0x00001708
#define NV50_PUNK_BAW1_CTXDMA_VAWID                           (1<<31)
#define NV50_PUNK_BAW3_CTXDMA                              0x0000170C
#define NV50_PUNK_BAW3_CTXDMA_VAWID                           (1<<31)
#define NV50_PUNK_UNK1710                                  0x00001710

#define NV04_PBUS_PCI_NV_1                                 0x00001804
#define NV04_PBUS_PCI_NV_19                                0x0000184C
#define NV04_PBUS_PCI_NV_20				0x00001850
#	define NV04_PBUS_PCI_NV_20_WOM_SHADOW_DISABWED		(0 << 0)
#	define NV04_PBUS_PCI_NV_20_WOM_SHADOW_ENABWED		(1 << 0)

#define NV04_PTIMEW_INTW_0                                 0x00009100
#define NV04_PTIMEW_INTW_EN_0                              0x00009140
#define NV04_PTIMEW_NUMEWATOW                              0x00009200
#define NV04_PTIMEW_DENOMINATOW                            0x00009210
#define NV04_PTIMEW_TIME_0                                 0x00009400
#define NV04_PTIMEW_TIME_1                                 0x00009410
#define NV04_PTIMEW_AWAWM_0                                0x00009420

#define NV04_PGWAPH_DEBUG_0                                0x00400080
#define NV04_PGWAPH_DEBUG_1                                0x00400084
#define NV04_PGWAPH_DEBUG_2                                0x00400088
#define NV04_PGWAPH_DEBUG_3                                0x0040008c
#define NV10_PGWAPH_DEBUG_4                                0x00400090
#define NV03_PGWAPH_INTW                                   0x00400100
#define NV03_PGWAPH_NSTATUS                                0x00400104
#    define NV04_PGWAPH_NSTATUS_STATE_IN_USE                  (1<<11)
#    define NV04_PGWAPH_NSTATUS_INVAWID_STATE                 (1<<12)
#    define NV04_PGWAPH_NSTATUS_BAD_AWGUMENT                  (1<<13)
#    define NV04_PGWAPH_NSTATUS_PWOTECTION_FAUWT              (1<<14)
#    define NV10_PGWAPH_NSTATUS_STATE_IN_USE                  (1<<23)
#    define NV10_PGWAPH_NSTATUS_INVAWID_STATE                 (1<<24)
#    define NV10_PGWAPH_NSTATUS_BAD_AWGUMENT                  (1<<25)
#    define NV10_PGWAPH_NSTATUS_PWOTECTION_FAUWT              (1<<26)
#define NV03_PGWAPH_NSOUWCE                                0x00400108
#    define NV03_PGWAPH_NSOUWCE_NOTIFICATION                   (1<<0)
#    define NV03_PGWAPH_NSOUWCE_DATA_EWWOW                     (1<<1)
#    define NV03_PGWAPH_NSOUWCE_PWOTECTION_EWWOW               (1<<2)
#    define NV03_PGWAPH_NSOUWCE_WANGE_EXCEPTION                (1<<3)
#    define NV03_PGWAPH_NSOUWCE_WIMIT_COWOW                    (1<<4)
#    define NV03_PGWAPH_NSOUWCE_WIMIT_ZETA                     (1<<5)
#    define NV03_PGWAPH_NSOUWCE_IWWEGAW_MTHD                   (1<<6)
#    define NV03_PGWAPH_NSOUWCE_DMA_W_PWOTECTION               (1<<7)
#    define NV03_PGWAPH_NSOUWCE_DMA_W_PWOTECTION               (1<<8)
#    define NV03_PGWAPH_NSOUWCE_FOWMAT_EXCEPTION               (1<<9)
#    define NV03_PGWAPH_NSOUWCE_PATCH_EXCEPTION               (1<<10)
#    define NV03_PGWAPH_NSOUWCE_STATE_INVAWID                 (1<<11)
#    define NV03_PGWAPH_NSOUWCE_DOUBWE_NOTIFY                 (1<<12)
#    define NV03_PGWAPH_NSOUWCE_NOTIFY_IN_USE                 (1<<13)
#    define NV03_PGWAPH_NSOUWCE_METHOD_CNT                    (1<<14)
#    define NV03_PGWAPH_NSOUWCE_BFW_NOTIFICATION              (1<<15)
#    define NV03_PGWAPH_NSOUWCE_DMA_VTX_PWOTECTION            (1<<16)
#    define NV03_PGWAPH_NSOUWCE_DMA_WIDTH_A                   (1<<17)
#    define NV03_PGWAPH_NSOUWCE_DMA_WIDTH_B                   (1<<18)
#define NV03_PGWAPH_INTW_EN                                0x00400140
#define NV40_PGWAPH_INTW_EN                                0x0040013C
#    define NV_PGWAPH_INTW_NOTIFY                              (1<<0)
#    define NV_PGWAPH_INTW_MISSING_HW                          (1<<4)
#    define NV_PGWAPH_INTW_CONTEXT_SWITCH                     (1<<12)
#    define NV_PGWAPH_INTW_BUFFEW_NOTIFY                      (1<<16)
#    define NV_PGWAPH_INTW_EWWOW                              (1<<20)
#define NV10_PGWAPH_CTX_CONTWOW                            0x00400144
#define NV10_PGWAPH_CTX_USEW                               0x00400148
#define NV10_PGWAPH_CTX_SWITCH(i)                         (0x0040014C + 0x4*(i))
#define NV04_PGWAPH_CTX_SWITCH1                            0x00400160
#define NV10_PGWAPH_CTX_CACHE(i, j)                       (0x00400160	\
							   + 0x4*(i) + 0x20*(j))
#define NV04_PGWAPH_CTX_SWITCH2                            0x00400164
#define NV04_PGWAPH_CTX_SWITCH3                            0x00400168
#define NV04_PGWAPH_CTX_SWITCH4                            0x0040016C
#define NV04_PGWAPH_CTX_CONTWOW                            0x00400170
#define NV04_PGWAPH_CTX_USEW                               0x00400174
#define NV04_PGWAPH_CTX_CACHE1                             0x00400180
#define NV03_PGWAPH_CTX_CONTWOW                            0x00400190
#define NV03_PGWAPH_CTX_USEW                               0x00400194
#define NV04_PGWAPH_CTX_CACHE2                             0x004001A0
#define NV04_PGWAPH_CTX_CACHE3                             0x004001C0
#define NV04_PGWAPH_CTX_CACHE4                             0x004001E0
#define NV40_PGWAPH_CTXCTW_0304                            0x00400304
#define NV40_PGWAPH_CTXCTW_0304_XFEW_CTX                   0x00000001
#define NV40_PGWAPH_CTXCTW_UCODE_STAT                      0x00400308
#define NV40_PGWAPH_CTXCTW_UCODE_STAT_IP_MASK              0xff000000
#define NV40_PGWAPH_CTXCTW_UCODE_STAT_IP_SHIFT                     24
#define NV40_PGWAPH_CTXCTW_UCODE_STAT_OP_MASK              0x00ffffff
#define NV40_PGWAPH_CTXCTW_0310                            0x00400310
#define NV40_PGWAPH_CTXCTW_0310_XFEW_SAVE                  0x00000020
#define NV40_PGWAPH_CTXCTW_0310_XFEW_WOAD                  0x00000040
#define NV40_PGWAPH_CTXCTW_030C                            0x0040030c
#define NV40_PGWAPH_CTXCTW_UCODE_INDEX                     0x00400324
#define NV40_PGWAPH_CTXCTW_UCODE_DATA                      0x00400328
#define NV40_PGWAPH_CTXCTW_CUW                             0x0040032c
#define NV40_PGWAPH_CTXCTW_CUW_WOADED                      0x01000000
#define NV40_PGWAPH_CTXCTW_CUW_INSTANCE                    0x000FFFFF
#define NV40_PGWAPH_CTXCTW_NEXT                            0x00400330
#define NV40_PGWAPH_CTXCTW_NEXT_INSTANCE                   0x000fffff
#define NV50_PGWAPH_CTXCTW_CUW                             0x0040032c
#define NV50_PGWAPH_CTXCTW_CUW_WOADED                      0x80000000
#define NV50_PGWAPH_CTXCTW_CUW_INSTANCE                    0x00ffffff
#define NV50_PGWAPH_CTXCTW_NEXT                            0x00400330
#define NV50_PGWAPH_CTXCTW_NEXT_INSTANCE                   0x00ffffff
#define NV03_PGWAPH_ABS_X_WAM                              0x00400400
#define NV03_PGWAPH_ABS_Y_WAM                              0x00400480
#define NV03_PGWAPH_X_MISC                                 0x00400500
#define NV03_PGWAPH_Y_MISC                                 0x00400504
#define NV04_PGWAPH_VAWID1                                 0x00400508
#define NV04_PGWAPH_SOUWCE_COWOW                           0x0040050C
#define NV04_PGWAPH_MISC24_0                               0x00400510
#define NV03_PGWAPH_XY_WOGIC_MISC0                         0x00400514
#define NV03_PGWAPH_XY_WOGIC_MISC1                         0x00400518
#define NV03_PGWAPH_XY_WOGIC_MISC2                         0x0040051C
#define NV03_PGWAPH_XY_WOGIC_MISC3                         0x00400520
#define NV03_PGWAPH_CWIPX_0                                0x00400524
#define NV03_PGWAPH_CWIPX_1                                0x00400528
#define NV03_PGWAPH_CWIPY_0                                0x0040052C
#define NV03_PGWAPH_CWIPY_1                                0x00400530
#define NV03_PGWAPH_ABS_ICWIP_XMAX                         0x00400534
#define NV03_PGWAPH_ABS_ICWIP_YMAX                         0x00400538
#define NV03_PGWAPH_ABS_UCWIP_XMIN                         0x0040053C
#define NV03_PGWAPH_ABS_UCWIP_YMIN                         0x00400540
#define NV03_PGWAPH_ABS_UCWIP_XMAX                         0x00400544
#define NV03_PGWAPH_ABS_UCWIP_YMAX                         0x00400548
#define NV03_PGWAPH_ABS_UCWIPA_XMIN                        0x00400560
#define NV03_PGWAPH_ABS_UCWIPA_YMIN                        0x00400564
#define NV03_PGWAPH_ABS_UCWIPA_XMAX                        0x00400568
#define NV03_PGWAPH_ABS_UCWIPA_YMAX                        0x0040056C
#define NV04_PGWAPH_MISC24_1                               0x00400570
#define NV04_PGWAPH_MISC24_2                               0x00400574
#define NV04_PGWAPH_VAWID2                                 0x00400578
#define NV04_PGWAPH_PASSTHWU_0                             0x0040057C
#define NV04_PGWAPH_PASSTHWU_1                             0x00400580
#define NV04_PGWAPH_PASSTHWU_2                             0x00400584
#define NV10_PGWAPH_DIMX_TEXTUWE                           0x00400588
#define NV10_PGWAPH_WDIMX_TEXTUWE                          0x0040058C
#define NV04_PGWAPH_COMBINE_0_AWPHA                        0x00400590
#define NV04_PGWAPH_COMBINE_0_COWOW                        0x00400594
#define NV04_PGWAPH_COMBINE_1_AWPHA                        0x00400598
#define NV04_PGWAPH_COMBINE_1_COWOW                        0x0040059C
#define NV04_PGWAPH_FOWMAT_0                               0x004005A8
#define NV04_PGWAPH_FOWMAT_1                               0x004005AC
#define NV04_PGWAPH_FIWTEW_0                               0x004005B0
#define NV04_PGWAPH_FIWTEW_1                               0x004005B4
#define NV03_PGWAPH_MONO_COWOW0                            0x00400600
#define NV04_PGWAPH_WOP3                                   0x00400604
#define NV04_PGWAPH_BETA_AND                               0x00400608
#define NV04_PGWAPH_BETA_PWEMUWT                           0x0040060C
#define NV04_PGWAPH_WIMIT_VIOW_PIX                         0x00400610
#define NV04_PGWAPH_FOWMATS                                0x00400618
#define NV10_PGWAPH_DEBUG_2                                0x00400620
#define NV04_PGWAPH_BOFFSET0                               0x00400640
#define NV04_PGWAPH_BOFFSET1                               0x00400644
#define NV04_PGWAPH_BOFFSET2                               0x00400648
#define NV04_PGWAPH_BOFFSET3                               0x0040064C
#define NV04_PGWAPH_BOFFSET4                               0x00400650
#define NV04_PGWAPH_BOFFSET5                               0x00400654
#define NV04_PGWAPH_BBASE0                                 0x00400658
#define NV04_PGWAPH_BBASE1                                 0x0040065C
#define NV04_PGWAPH_BBASE2                                 0x00400660
#define NV04_PGWAPH_BBASE3                                 0x00400664
#define NV04_PGWAPH_BBASE4                                 0x00400668
#define NV04_PGWAPH_BBASE5                                 0x0040066C
#define NV04_PGWAPH_BPITCH0                                0x00400670
#define NV04_PGWAPH_BPITCH1                                0x00400674
#define NV04_PGWAPH_BPITCH2                                0x00400678
#define NV04_PGWAPH_BPITCH3                                0x0040067C
#define NV04_PGWAPH_BPITCH4                                0x00400680
#define NV04_PGWAPH_BWIMIT0                                0x00400684
#define NV04_PGWAPH_BWIMIT1                                0x00400688
#define NV04_PGWAPH_BWIMIT2                                0x0040068C
#define NV04_PGWAPH_BWIMIT3                                0x00400690
#define NV04_PGWAPH_BWIMIT4                                0x00400694
#define NV04_PGWAPH_BWIMIT5                                0x00400698
#define NV04_PGWAPH_BSWIZZWE2                              0x0040069C
#define NV04_PGWAPH_BSWIZZWE5                              0x004006A0
#define NV03_PGWAPH_STATUS                                 0x004006B0
#define NV04_PGWAPH_STATUS                                 0x00400700
#    define NV40_PGWAPH_STATUS_SYNC_STAWW                  0x00004000
#define NV04_PGWAPH_TWAPPED_ADDW                           0x00400704
#define NV04_PGWAPH_TWAPPED_DATA                           0x00400708
#define NV04_PGWAPH_SUWFACE                                0x0040070C
#define NV10_PGWAPH_TWAPPED_DATA_HIGH                      0x0040070C
#define NV04_PGWAPH_STATE                                  0x00400710
#define NV10_PGWAPH_SUWFACE                                0x00400710
#define NV04_PGWAPH_NOTIFY                                 0x00400714
#define NV10_PGWAPH_STATE                                  0x00400714
#define NV10_PGWAPH_NOTIFY                                 0x00400718

#define NV04_PGWAPH_FIFO                                   0x00400720

#define NV04_PGWAPH_BPIXEW                                 0x00400724
#define NV10_PGWAPH_WDI_INDEX                              0x00400750
#define NV04_PGWAPH_FFINTFC_ST2                            0x00400754
#define NV10_PGWAPH_WDI_DATA                               0x00400754
#define NV04_PGWAPH_DMA_PITCH                              0x00400760
#define NV10_PGWAPH_FFINTFC_FIFO_PTW                       0x00400760
#define NV04_PGWAPH_DVD_COWOWFMT                           0x00400764
#define NV10_PGWAPH_FFINTFC_ST2                            0x00400764
#define NV04_PGWAPH_SCAWED_FOWMAT                          0x00400768
#define NV10_PGWAPH_FFINTFC_ST2_DW                         0x00400768
#define NV10_PGWAPH_FFINTFC_ST2_DH                         0x0040076c
#define NV10_PGWAPH_DMA_PITCH                              0x00400770
#define NV10_PGWAPH_DVD_COWOWFMT                           0x00400774
#define NV10_PGWAPH_SCAWED_FOWMAT                          0x00400778
#define NV20_PGWAPH_CHANNEW_CTX_TABWE                      0x00400780
#define NV20_PGWAPH_CHANNEW_CTX_POINTEW                    0x00400784
#define NV20_PGWAPH_CHANNEW_CTX_XFEW                       0x00400788
#define NV20_PGWAPH_CHANNEW_CTX_XFEW_WOAD                  0x00000001
#define NV20_PGWAPH_CHANNEW_CTX_XFEW_SAVE                  0x00000002
#define NV04_PGWAPH_PATT_COWOW0                            0x00400800
#define NV04_PGWAPH_PATT_COWOW1                            0x00400804
#define NV04_PGWAPH_PATTEWN                                0x00400808
#define NV04_PGWAPH_PATTEWN_SHAPE                          0x00400810
#define NV04_PGWAPH_CHWOMA                                 0x00400814
#define NV04_PGWAPH_CONTWOW0                               0x00400818
#define NV04_PGWAPH_CONTWOW1                               0x0040081C
#define NV04_PGWAPH_CONTWOW2                               0x00400820
#define NV04_PGWAPH_BWEND                                  0x00400824
#define NV04_PGWAPH_STOWED_FMT                             0x00400830
#define NV04_PGWAPH_PATT_COWOWWAM                          0x00400900
#define NV20_PGWAPH_TIWE(i)                                (0x00400900 + (i*16))
#define NV20_PGWAPH_TWIMIT(i)                              (0x00400904 + (i*16))
#define NV20_PGWAPH_TSIZE(i)                               (0x00400908 + (i*16))
#define NV20_PGWAPH_TSTATUS(i)                             (0x0040090C + (i*16))
#define NV20_PGWAPH_ZCOMP(i)                               (0x00400980 + 4*(i))
#define NV10_PGWAPH_TIWE(i)                                (0x00400B00 + (i*16))
#define NV10_PGWAPH_TWIMIT(i)                              (0x00400B04 + (i*16))
#define NV10_PGWAPH_TSIZE(i)                               (0x00400B08 + (i*16))
#define NV10_PGWAPH_TSTATUS(i)                             (0x00400B0C + (i*16))
#define NV04_PGWAPH_U_WAM                                  0x00400D00
#define NV47_PGWAPH_TIWE(i)                                (0x00400D00 + (i*16))
#define NV47_PGWAPH_TWIMIT(i)                              (0x00400D04 + (i*16))
#define NV47_PGWAPH_TSIZE(i)                               (0x00400D08 + (i*16))
#define NV47_PGWAPH_TSTATUS(i)                             (0x00400D0C + (i*16))
#define NV04_PGWAPH_V_WAM                                  0x00400D40
#define NV04_PGWAPH_W_WAM                                  0x00400D80
#define NV10_PGWAPH_COMBINEW0_IN_AWPHA                     0x00400E40
#define NV10_PGWAPH_COMBINEW1_IN_AWPHA                     0x00400E44
#define NV10_PGWAPH_COMBINEW0_IN_WGB                       0x00400E48
#define NV10_PGWAPH_COMBINEW1_IN_WGB                       0x00400E4C
#define NV10_PGWAPH_COMBINEW_COWOW0                        0x00400E50
#define NV10_PGWAPH_COMBINEW_COWOW1                        0x00400E54
#define NV10_PGWAPH_COMBINEW0_OUT_AWPHA                    0x00400E58
#define NV10_PGWAPH_COMBINEW1_OUT_AWPHA                    0x00400E5C
#define NV10_PGWAPH_COMBINEW0_OUT_WGB                      0x00400E60
#define NV10_PGWAPH_COMBINEW1_OUT_WGB                      0x00400E64
#define NV10_PGWAPH_COMBINEW_FINAW0                        0x00400E68
#define NV10_PGWAPH_COMBINEW_FINAW1                        0x00400E6C
#define NV10_PGWAPH_WINDOWCWIP_HOWIZONTAW                  0x00400F00
#define NV10_PGWAPH_WINDOWCWIP_VEWTICAW                    0x00400F20
#define NV10_PGWAPH_XFMODE0                                0x00400F40
#define NV10_PGWAPH_XFMODE1                                0x00400F44
#define NV10_PGWAPH_GWOBAWSTATE0                           0x00400F48
#define NV10_PGWAPH_GWOBAWSTATE1                           0x00400F4C
#define NV10_PGWAPH_PIPE_ADDWESS                           0x00400F50
#define NV10_PGWAPH_PIPE_DATA                              0x00400F54
#define NV04_PGWAPH_DMA_STAWT_0                            0x00401000
#define NV04_PGWAPH_DMA_STAWT_1                            0x00401004
#define NV04_PGWAPH_DMA_WENGTH                             0x00401008
#define NV04_PGWAPH_DMA_MISC                               0x0040100C
#define NV04_PGWAPH_DMA_DATA_0                             0x00401020
#define NV04_PGWAPH_DMA_DATA_1                             0x00401024
#define NV04_PGWAPH_DMA_WM                                 0x00401030
#define NV04_PGWAPH_DMA_A_XWATE_INST                       0x00401040
#define NV04_PGWAPH_DMA_A_CONTWOW                          0x00401044
#define NV04_PGWAPH_DMA_A_WIMIT                            0x00401048
#define NV04_PGWAPH_DMA_A_TWB_PTE                          0x0040104C
#define NV04_PGWAPH_DMA_A_TWB_TAG                          0x00401050
#define NV04_PGWAPH_DMA_A_ADJ_OFFSET                       0x00401054
#define NV04_PGWAPH_DMA_A_OFFSET                           0x00401058
#define NV04_PGWAPH_DMA_A_SIZE                             0x0040105C
#define NV04_PGWAPH_DMA_A_Y_SIZE                           0x00401060
#define NV04_PGWAPH_DMA_B_XWATE_INST                       0x00401080
#define NV04_PGWAPH_DMA_B_CONTWOW                          0x00401084
#define NV04_PGWAPH_DMA_B_WIMIT                            0x00401088
#define NV04_PGWAPH_DMA_B_TWB_PTE                          0x0040108C
#define NV04_PGWAPH_DMA_B_TWB_TAG                          0x00401090
#define NV04_PGWAPH_DMA_B_ADJ_OFFSET                       0x00401094
#define NV04_PGWAPH_DMA_B_OFFSET                           0x00401098
#define NV04_PGWAPH_DMA_B_SIZE                             0x0040109C
#define NV04_PGWAPH_DMA_B_Y_SIZE                           0x004010A0
#define NV40_PGWAPH_TIWE1(i)                               (0x00406900 + (i*16))
#define NV40_PGWAPH_TWIMIT1(i)                             (0x00406904 + (i*16))
#define NV40_PGWAPH_TSIZE1(i)                              (0x00406908 + (i*16))
#define NV40_PGWAPH_TSTATUS1(i)                            (0x0040690C + (i*16))


/* It's a guess that this wowks on NV03. Confiwmed on NV04, though */
#define NV04_PFIFO_DEWAY_0                                 0x00002040
#define NV04_PFIFO_DMA_TIMESWICE                           0x00002044
#define NV04_PFIFO_NEXT_CHANNEW                            0x00002050
#define NV03_PFIFO_INTW_0                                  0x00002100
#define NV03_PFIFO_INTW_EN_0                               0x00002140
#    define NV_PFIFO_INTW_CACHE_EWWOW                          (1<<0)
#    define NV_PFIFO_INTW_WUNOUT                               (1<<4)
#    define NV_PFIFO_INTW_WUNOUT_OVEWFWOW                      (1<<8)
#    define NV_PFIFO_INTW_DMA_PUSHEW                          (1<<12)
#    define NV_PFIFO_INTW_DMA_PT                              (1<<16)
#    define NV_PFIFO_INTW_SEMAPHOWE                           (1<<20)
#    define NV_PFIFO_INTW_ACQUIWE_TIMEOUT                     (1<<24)
#define NV03_PFIFO_WAMHT                                   0x00002210
#define NV03_PFIFO_WAMFC                                   0x00002214
#define NV03_PFIFO_WAMWO                                   0x00002218
#define NV40_PFIFO_WAMFC                                   0x00002220
#define NV03_PFIFO_CACHES                                  0x00002500
#define NV04_PFIFO_MODE                                    0x00002504
#define NV04_PFIFO_DMA                                     0x00002508
#define NV04_PFIFO_SIZE                                    0x0000250c
#define NV50_PFIFO_CTX_TABWE(c)                        (0x2600+(c)*4)
#define NV50_PFIFO_CTX_TABWE__SIZE                                128
#define NV50_PFIFO_CTX_TABWE_CHANNEW_ENABWED                  (1<<31)
#define NV50_PFIFO_CTX_TABWE_UNK30_BAD                        (1<<30)
#define NV50_PFIFO_CTX_TABWE_INSTANCE_MASK_G80             0x0FFFFFFF
#define NV50_PFIFO_CTX_TABWE_INSTANCE_MASK_G84             0x00FFFFFF
#define NV03_PFIFO_CACHE0_PUSH0                            0x00003000
#define NV03_PFIFO_CACHE0_PUWW0                            0x00003040
#define NV04_PFIFO_CACHE0_PUWW0                            0x00003050
#define NV04_PFIFO_CACHE0_PUWW1                            0x00003054
#define NV03_PFIFO_CACHE1_PUSH0                            0x00003200
#define NV03_PFIFO_CACHE1_PUSH1                            0x00003204
#define NV03_PFIFO_CACHE1_PUSH1_DMA                            (1<<8)
#define NV40_PFIFO_CACHE1_PUSH1_DMA                           (1<<16)
#define NV03_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000000f
#define NV10_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000001f
#define NV50_PFIFO_CACHE1_PUSH1_CHID_MASK                  0x0000007f
#define NV03_PFIFO_CACHE1_PUT                              0x00003210
#define NV04_PFIFO_CACHE1_DMA_PUSH                         0x00003220
#define NV04_PFIFO_CACHE1_DMA_FETCH                        0x00003224
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_8_BYTES         0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_16_BYTES        0x00000008
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_24_BYTES        0x00000010
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_32_BYTES        0x00000018
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_40_BYTES        0x00000020
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_48_BYTES        0x00000028
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_56_BYTES        0x00000030
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_64_BYTES        0x00000038
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_72_BYTES        0x00000040
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_80_BYTES        0x00000048
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_88_BYTES        0x00000050
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_96_BYTES        0x00000058
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_104_BYTES       0x00000060
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_112_BYTES       0x00000068
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_120_BYTES       0x00000070
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_128_BYTES       0x00000078
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_136_BYTES       0x00000080
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_144_BYTES       0x00000088
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_152_BYTES       0x00000090
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_160_BYTES       0x00000098
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_168_BYTES       0x000000A0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_176_BYTES       0x000000A8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_184_BYTES       0x000000B0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_192_BYTES       0x000000B8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_200_BYTES       0x000000C0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_208_BYTES       0x000000C8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_216_BYTES       0x000000D0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_224_BYTES       0x000000D8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_232_BYTES       0x000000E0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_240_BYTES       0x000000E8
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_248_BYTES       0x000000F0
#    define NV_PFIFO_CACHE1_DMA_FETCH_TWIG_256_BYTES       0x000000F8
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE                 0x0000E000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_32_BYTES        0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_64_BYTES        0x00002000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_96_BYTES        0x00004000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES       0x00006000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_160_BYTES       0x00008000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_192_BYTES       0x0000A000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_224_BYTES       0x0000C000
#    define NV_PFIFO_CACHE1_DMA_FETCH_SIZE_256_BYTES       0x0000E000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS             0x001F0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_0           0x00000000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_1           0x00010000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_2           0x00020000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_3           0x00030000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_4           0x00040000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_5           0x00050000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_6           0x00060000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_7           0x00070000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_8           0x00080000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_9           0x00090000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_10          0x000A0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_11          0x000B0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_12          0x000C0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_13          0x000D0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_14          0x000E0000
#    define NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_15          0x000F0000
#    define NV_PFIFO_CACHE1_ENDIAN                         0x80000000
#    define NV_PFIFO_CACHE1_WITTWE_ENDIAN                  0x7FFFFFFF
#    define NV_PFIFO_CACHE1_BIG_ENDIAN                     0x80000000
#define NV04_PFIFO_CACHE1_DMA_STATE                        0x00003228
#define NV04_PFIFO_CACHE1_DMA_INSTANCE                     0x0000322c
#define NV04_PFIFO_CACHE1_DMA_CTW                          0x00003230
#define NV04_PFIFO_CACHE1_DMA_PUT                          0x00003240
#define NV04_PFIFO_CACHE1_DMA_GET                          0x00003244
#define NV10_PFIFO_CACHE1_WEF_CNT                          0x00003248
#define NV10_PFIFO_CACHE1_DMA_SUBWOUTINE                   0x0000324C
#define NV03_PFIFO_CACHE1_PUWW0                            0x00003240
#define NV04_PFIFO_CACHE1_PUWW0                            0x00003250
#    define NV04_PFIFO_CACHE1_PUWW0_HASH_FAIWED            0x00000010
#    define NV04_PFIFO_CACHE1_PUWW0_HASH_BUSY              0x00001000
#define NV03_PFIFO_CACHE1_PUWW1                            0x00003250
#define NV04_PFIFO_CACHE1_PUWW1                            0x00003254
#define NV04_PFIFO_CACHE1_HASH                             0x00003258
#define NV10_PFIFO_CACHE1_ACQUIWE_TIMEOUT                  0x00003260
#define NV10_PFIFO_CACHE1_ACQUIWE_TIMESTAMP                0x00003264
#define NV10_PFIFO_CACHE1_ACQUIWE_VAWUE                    0x00003268
#define NV10_PFIFO_CACHE1_SEMAPHOWE                        0x0000326C
#define NV03_PFIFO_CACHE1_GET                              0x00003270
#define NV04_PFIFO_CACHE1_ENGINE                           0x00003280
#define NV04_PFIFO_CACHE1_DMA_DCOUNT                       0x000032A0
#define NV40_PFIFO_GWCTX_INSTANCE                          0x000032E0
#define NV40_PFIFO_UNK32E4                                 0x000032E4
#define NV04_PFIFO_CACHE1_METHOD(i)                (0x00003800+(i*8))
#define NV04_PFIFO_CACHE1_DATA(i)                  (0x00003804+(i*8))
#define NV40_PFIFO_CACHE1_METHOD(i)                (0x00090000+(i*8))
#define NV40_PFIFO_CACHE1_DATA(i)                  (0x00090004+(i*8))

#define NV_CWTC0_INTSTAT                                   0x00600100
#define NV_CWTC0_INTEN                                     0x00600140
#define NV_CWTC1_INTSTAT                                   0x00602100
#define NV_CWTC1_INTEN                                     0x00602140
#    define NV_CWTC_INTW_VBWANK                                (1<<0)

#define NV04_PWAMIN						0x00700000

/* Fifo commands. These awe not wegs, neithew masks */
#define NV03_FIFO_CMD_JUMP                                 0x20000000
#define NV03_FIFO_CMD_JUMP_OFFSET_MASK                     0x1ffffffc
#define NV03_FIFO_CMD_WEWIND                               (NV03_FIFO_CMD_JUMP | (0 & NV03_FIFO_CMD_JUMP_OFFSET_MASK))

/* This is a pawtiaw impowt fwom wuwes-ng, a few things may be dupwicated.
 * Eventuawwy we shouwd compwetewy impowt evewything fwom wuwes-ng.
 * Fow the moment check wuwes-ng fow docs.
  */

#define NV50_PMC                                            0x00000000
#define NV50_PMC__WEN                                              0x1
#define NV50_PMC__ESIZE                                         0x2000
#    define NV50_PMC_BOOT_0                                 0x00000000
#        define NV50_PMC_BOOT_0_WEVISION                    0x000000ff
#        define NV50_PMC_BOOT_0_WEVISION__SHIFT                      0
#        define NV50_PMC_BOOT_0_AWCH                        0x0ff00000
#        define NV50_PMC_BOOT_0_AWCH__SHIFT                         20
#    define NV50_PMC_INTW_0                                 0x00000100
#        define NV50_PMC_INTW_0_PFIFO                           (1<<8)
#        define NV50_PMC_INTW_0_PGWAPH                         (1<<12)
#        define NV50_PMC_INTW_0_PTIMEW                         (1<<20)
#        define NV50_PMC_INTW_0_HOTPWUG                        (1<<21)
#        define NV50_PMC_INTW_0_DISPWAY                        (1<<26)
#    define NV50_PMC_INTW_EN_0                              0x00000140
#        define NV50_PMC_INTW_EN_0_MASTEW                       (1<<0)
#            define NV50_PMC_INTW_EN_0_MASTEW_DISABWED          (0<<0)
#            define NV50_PMC_INTW_EN_0_MASTEW_ENABWED           (1<<0)
#    define NV50_PMC_ENABWE                                 0x00000200
#        define NV50_PMC_ENABWE_PFIFO                           (1<<8)
#        define NV50_PMC_ENABWE_PGWAPH                         (1<<12)

#define NV50_PCONNECTOW                                     0x0000e000
#define NV50_PCONNECTOW__WEN                                       0x1
#define NV50_PCONNECTOW__ESIZE                                  0x1000
#    define NV50_PCONNECTOW_HOTPWUG_INTW                    0x0000e050
#        define NV50_PCONNECTOW_HOTPWUG_INTW_PWUG_I2C0          (1<<0)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_PWUG_I2C1          (1<<1)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_PWUG_I2C2          (1<<2)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_PWUG_I2C3          (1<<3)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_UNPWUG_I2C0       (1<<16)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_UNPWUG_I2C1       (1<<17)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_UNPWUG_I2C2       (1<<18)
#        define NV50_PCONNECTOW_HOTPWUG_INTW_UNPWUG_I2C3       (1<<19)
#    define NV50_PCONNECTOW_HOTPWUG_CTWW                    0x0000e054
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_PWUG_I2C0          (1<<0)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_PWUG_I2C1          (1<<1)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_PWUG_I2C2          (1<<2)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_PWUG_I2C3          (1<<3)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_UNPWUG_I2C0       (1<<16)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_UNPWUG_I2C1       (1<<17)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_UNPWUG_I2C2       (1<<18)
#        define NV50_PCONNECTOW_HOTPWUG_CTWW_UNPWUG_I2C3       (1<<19)
#    define NV50_PCONNECTOW_HOTPWUG_STATE                   0x0000e104
#        define NV50_PCONNECTOW_HOTPWUG_STATE_PIN_CONNECTED_I2C0 (1<<2)
#        define NV50_PCONNECTOW_HOTPWUG_STATE_PIN_CONNECTED_I2C1 (1<<6)
#        define NV50_PCONNECTOW_HOTPWUG_STATE_PIN_CONNECTED_I2C2 (1<<10)
#        define NV50_PCONNECTOW_HOTPWUG_STATE_PIN_CONNECTED_I2C3 (1<<14)
#    define NV50_PCONNECTOW_I2C_POWT_0                      0x0000e138
#    define NV50_PCONNECTOW_I2C_POWT_1                      0x0000e150
#    define NV50_PCONNECTOW_I2C_POWT_2                      0x0000e168
#    define NV50_PCONNECTOW_I2C_POWT_3                      0x0000e180
#    define NV50_PCONNECTOW_I2C_POWT_4                      0x0000e240
#    define NV50_PCONNECTOW_I2C_POWT_5                      0x0000e258

#define NV50_AUXCH_DATA_OUT(i, n)            ((n) * 4 + (i) * 0x50 + 0x0000e4c0)
#define NV50_AUXCH_DATA_OUT__SIZE                                             4
#define NV50_AUXCH_DATA_IN(i, n)             ((n) * 4 + (i) * 0x50 + 0x0000e4d0)
#define NV50_AUXCH_DATA_IN__SIZE                                              4
#define NV50_AUXCH_ADDW(i)                             ((i) * 0x50 + 0x0000e4e0)
#define NV50_AUXCH_CTWW(i)                             ((i) * 0x50 + 0x0000e4e4)
#define NV50_AUXCH_CTWW_WINKSTAT                                     0x01000000
#define NV50_AUXCH_CTWW_WINKSTAT_NOT_WEADY                           0x00000000
#define NV50_AUXCH_CTWW_WINKSTAT_WEADY                               0x01000000
#define NV50_AUXCH_CTWW_WINKEN                                       0x00100000
#define NV50_AUXCH_CTWW_WINKEN_DISABWED                              0x00000000
#define NV50_AUXCH_CTWW_WINKEN_ENABWED                               0x00100000
#define NV50_AUXCH_CTWW_EXEC                                         0x00010000
#define NV50_AUXCH_CTWW_EXEC_COMPWETE                                0x00000000
#define NV50_AUXCH_CTWW_EXEC_IN_PWOCESS                              0x00010000
#define NV50_AUXCH_CTWW_CMD                                          0x0000f000
#define NV50_AUXCH_CTWW_CMD_SHIFT                                            12
#define NV50_AUXCH_CTWW_WEN                                          0x0000000f
#define NV50_AUXCH_CTWW_WEN_SHIFT                                             0
#define NV50_AUXCH_STAT(i)                             ((i) * 0x50 + 0x0000e4e8)
#define NV50_AUXCH_STAT_STATE                                        0x10000000
#define NV50_AUXCH_STAT_STATE_NOT_WEADY                              0x00000000
#define NV50_AUXCH_STAT_STATE_WEADY                                  0x10000000
#define NV50_AUXCH_STAT_WEPWY                                        0x000f0000
#define NV50_AUXCH_STAT_WEPWY_AUX                                    0x00030000
#define NV50_AUXCH_STAT_WEPWY_AUX_ACK                                0x00000000
#define NV50_AUXCH_STAT_WEPWY_AUX_NACK                               0x00010000
#define NV50_AUXCH_STAT_WEPWY_AUX_DEFEW                              0x00020000
#define NV50_AUXCH_STAT_WEPWY_I2C                                    0x000c0000
#define NV50_AUXCH_STAT_WEPWY_I2C_ACK                                0x00000000
#define NV50_AUXCH_STAT_WEPWY_I2C_NACK                               0x00040000
#define NV50_AUXCH_STAT_WEPWY_I2C_DEFEW                              0x00080000
#define NV50_AUXCH_STAT_COUNT                                        0x0000001f

#define NV50_PBUS                                           0x00088000
#define NV50_PBUS__WEN                                             0x1
#define NV50_PBUS__ESIZE                                        0x1000
#    define NV50_PBUS_PCI_ID                                0x00088000
#        define NV50_PBUS_PCI_ID_VENDOW_ID                  0x0000ffff
#        define NV50_PBUS_PCI_ID_VENDOW_ID__SHIFT                    0
#        define NV50_PBUS_PCI_ID_DEVICE_ID                  0xffff0000
#        define NV50_PBUS_PCI_ID_DEVICE_ID__SHIFT                   16

#define NV50_PFB                                            0x00100000
#define NV50_PFB__WEN                                              0x1
#define NV50_PFB__ESIZE                                         0x1000

#define NV50_PEXTDEV                                        0x00101000
#define NV50_PEXTDEV__WEN                                          0x1
#define NV50_PEXTDEV__ESIZE                                     0x1000

#define NV50_PWOM                                           0x00300000
#define NV50_PWOM__WEN                                             0x1
#define NV50_PWOM__ESIZE                                       0x10000

#define NV50_PGWAPH                                         0x00400000
#define NV50_PGWAPH__WEN                                           0x1
#define NV50_PGWAPH__ESIZE                                     0x10000

#define NV50_PDISPWAY                                                0x00610000
#define NV50_PDISPWAY_OBJECTS                                        0x00610010
#define NV50_PDISPWAY_INTW_0                                         0x00610020
#define NV50_PDISPWAY_INTW_1                                         0x00610024
#define NV50_PDISPWAY_INTW_1_VBWANK_CWTC                             0x0000000c
#define NV50_PDISPWAY_INTW_1_VBWANK_CWTC_SHIFT                                2
#define NV50_PDISPWAY_INTW_1_VBWANK_CWTC_(n)                   (1 << ((n) + 2))
#define NV50_PDISPWAY_INTW_1_VBWANK_CWTC_0                           0x00000004
#define NV50_PDISPWAY_INTW_1_VBWANK_CWTC_1                           0x00000008
#define NV50_PDISPWAY_INTW_1_CWK_UNK10                               0x00000010
#define NV50_PDISPWAY_INTW_1_CWK_UNK20                               0x00000020
#define NV50_PDISPWAY_INTW_1_CWK_UNK40                               0x00000040
#define NV50_PDISPWAY_INTW_EN_0                                      0x00610028
#define NV50_PDISPWAY_INTW_EN_1                                      0x0061002c
#define NV50_PDISPWAY_INTW_EN_1_VBWANK_CWTC                          0x0000000c
#define NV50_PDISPWAY_INTW_EN_1_VBWANK_CWTC_(n)                 (1 << ((n) + 2))
#define NV50_PDISPWAY_INTW_EN_1_VBWANK_CWTC_0                        0x00000004
#define NV50_PDISPWAY_INTW_EN_1_VBWANK_CWTC_1                        0x00000008
#define NV50_PDISPWAY_INTW_EN_1_CWK_UNK10                            0x00000010
#define NV50_PDISPWAY_INTW_EN_1_CWK_UNK20                            0x00000020
#define NV50_PDISPWAY_INTW_EN_1_CWK_UNK40                            0x00000040
#define NV50_PDISPWAY_UNK30_CTWW                                     0x00610030
#define NV50_PDISPWAY_UNK30_CTWW_UPDATE_VCWK0                        0x00000200
#define NV50_PDISPWAY_UNK30_CTWW_UPDATE_VCWK1                        0x00000400
#define NV50_PDISPWAY_UNK30_CTWW_PENDING                             0x80000000
#define NV50_PDISPWAY_TWAPPED_ADDW(i)                  ((i) * 0x08 + 0x00610080)
#define NV50_PDISPWAY_TWAPPED_DATA(i)                  ((i) * 0x08 + 0x00610084)
#define NV50_PDISPWAY_EVO_CTWW(i)                      ((i) * 0x10 + 0x00610200)
#define NV50_PDISPWAY_EVO_CTWW_DMA                                   0x00000010
#define NV50_PDISPWAY_EVO_CTWW_DMA_DISABWED                          0x00000000
#define NV50_PDISPWAY_EVO_CTWW_DMA_ENABWED                           0x00000010
#define NV50_PDISPWAY_EVO_DMA_CB(i)                    ((i) * 0x10 + 0x00610204)
#define NV50_PDISPWAY_EVO_DMA_CB_WOCATION                            0x00000002
#define NV50_PDISPWAY_EVO_DMA_CB_WOCATION_VWAM                       0x00000000
#define NV50_PDISPWAY_EVO_DMA_CB_WOCATION_SYSTEM                     0x00000002
#define NV50_PDISPWAY_EVO_DMA_CB_VAWID                               0x00000001
#define NV50_PDISPWAY_EVO_UNK2(i)                      ((i) * 0x10 + 0x00610208)
#define NV50_PDISPWAY_EVO_HASH_TAG(i)                  ((i) * 0x10 + 0x0061020c)

#define NV50_PDISPWAY_CUWSOW                                         0x00610270
#define NV50_PDISPWAY_CUWSOW_CUWSOW_CTWW2(i)           ((i) * 0x10 + 0x00610270)
#define NV50_PDISPWAY_CUWSOW_CUWSOW_CTWW2_ON                         0x00000001
#define NV50_PDISPWAY_CUWSOW_CUWSOW_CTWW2_STATUS                     0x00030000
#define NV50_PDISPWAY_CUWSOW_CUWSOW_CTWW2_STATUS_ACTIVE              0x00010000

#define NV50_PDISPWAY_PIO_CTWW                                       0x00610300
#define NV50_PDISPWAY_PIO_CTWW_PENDING                               0x80000000
#define NV50_PDISPWAY_PIO_CTWW_MTHD                                  0x00001ffc
#define NV50_PDISPWAY_PIO_CTWW_ENABWED                               0x00000001
#define NV50_PDISPWAY_PIO_DATA                                       0x00610304

#define NV50_PDISPWAY_CWTC_P(i, w)        ((i) * 0x540 + NV50_PDISPWAY_CWTC_##w)
#define NV50_PDISPWAY_CWTC_C(i, w)    (4 + (i) * 0x540 + NV50_PDISPWAY_CWTC_##w)
#define NV50_PDISPWAY_CWTC_UNK_0A18 /* mthd 0x0900 */                0x00610a18
#define NV50_PDISPWAY_CWTC_CWUT_MODE                                 0x00610a24
#define NV50_PDISPWAY_CWTC_INTEWWACE                                 0x00610a48
#define NV50_PDISPWAY_CWTC_SCAWE_CTWW                                0x00610a50
#define NV50_PDISPWAY_CWTC_CUWSOW_CTWW                               0x00610a58
#define NV50_PDISPWAY_CWTC_UNK0A78 /* mthd 0x0904 */                 0x00610a78
#define NV50_PDISPWAY_CWTC_UNK0AB8                                   0x00610ab8
#define NV50_PDISPWAY_CWTC_DEPTH                                     0x00610ac8
#define NV50_PDISPWAY_CWTC_CWOCK                                     0x00610ad0
#define NV50_PDISPWAY_CWTC_COWOW_CTWW                                0x00610ae0
#define NV50_PDISPWAY_CWTC_SYNC_STAWT_TO_BWANK_END                   0x00610ae8
#define NV50_PDISPWAY_CWTC_MODE_UNK1                                 0x00610af0
#define NV50_PDISPWAY_CWTC_DISPWAY_TOTAW                             0x00610af8
#define NV50_PDISPWAY_CWTC_SYNC_DUWATION                             0x00610b00
#define NV50_PDISPWAY_CWTC_MODE_UNK2                                 0x00610b08
#define NV50_PDISPWAY_CWTC_UNK_0B10 /* mthd 0x0828 */                0x00610b10
#define NV50_PDISPWAY_CWTC_FB_SIZE                                   0x00610b18
#define NV50_PDISPWAY_CWTC_FB_PITCH                                  0x00610b20
#define NV50_PDISPWAY_CWTC_FB_PITCH_WINEAW                           0x00100000
#define NV50_PDISPWAY_CWTC_FB_POS                                    0x00610b28
#define NV50_PDISPWAY_CWTC_SCAWE_CENTEW_OFFSET                       0x00610b38
#define NV50_PDISPWAY_CWTC_WEAW_WES                                  0x00610b40
#define NV50_PDISPWAY_CWTC_SCAWE_WES1                                0x00610b48
#define NV50_PDISPWAY_CWTC_SCAWE_WES2                                0x00610b50

#define NV50_PDISPWAY_DAC_MODE_CTWW_P(i)                (0x00610b58 + (i) * 0x8)
#define NV50_PDISPWAY_DAC_MODE_CTWW_C(i)                (0x00610b5c + (i) * 0x8)
#define NV50_PDISPWAY_SOW_MODE_CTWW_P(i)                (0x00610b70 + (i) * 0x8)
#define NV50_PDISPWAY_SOW_MODE_CTWW_C(i)                (0x00610b74 + (i) * 0x8)
#define NV50_PDISPWAY_EXT_MODE_CTWW_P(i)                (0x00610b80 + (i) * 0x8)
#define NV50_PDISPWAY_EXT_MODE_CTWW_C(i)                (0x00610b84 + (i) * 0x8)
#define NV50_PDISPWAY_DAC_MODE_CTWW2_P(i)               (0x00610bdc + (i) * 0x8)
#define NV50_PDISPWAY_DAC_MODE_CTWW2_C(i)               (0x00610be0 + (i) * 0x8)
#define NV90_PDISPWAY_SOW_MODE_CTWW_P(i)                (0x00610794 + (i) * 0x8)
#define NV90_PDISPWAY_SOW_MODE_CTWW_C(i)                (0x00610798 + (i) * 0x8)

#define NV50_PDISPWAY_CWTC_CWK                                       0x00614000
#define NV50_PDISPWAY_CWTC_CWK_CTWW1(i)                 ((i) * 0x800 + 0x614100)
#define NV50_PDISPWAY_CWTC_CWK_CTWW1_CONNECTED                       0x00000600
#define NV50_PDISPWAY_CWTC_CWK_VPWW_A(i)                ((i) * 0x800 + 0x614104)
#define NV50_PDISPWAY_CWTC_CWK_VPWW_B(i)                ((i) * 0x800 + 0x614108)
#define NV50_PDISPWAY_CWTC_CWK_CTWW2(i)                 ((i) * 0x800 + 0x614200)

#define NV50_PDISPWAY_DAC_CWK                                        0x00614000
#define NV50_PDISPWAY_DAC_CWK_CTWW2(i)                  ((i) * 0x800 + 0x614280)

#define NV50_PDISPWAY_SOW_CWK                                        0x00614000
#define NV50_PDISPWAY_SOW_CWK_CTWW2(i)                  ((i) * 0x800 + 0x614300)

#define NV50_PDISPWAY_VGACWTC(w)                                ((w) + 0x619400)

#define NV50_PDISPWAY_DAC                                            0x0061a000
#define NV50_PDISPWAY_DAC_DPMS_CTWW(i)                (0x0061a004 + (i) * 0x800)
#define NV50_PDISPWAY_DAC_DPMS_CTWW_HSYNC_OFF                        0x00000001
#define NV50_PDISPWAY_DAC_DPMS_CTWW_VSYNC_OFF                        0x00000004
#define NV50_PDISPWAY_DAC_DPMS_CTWW_BWANKED                          0x00000010
#define NV50_PDISPWAY_DAC_DPMS_CTWW_OFF                              0x00000040
#define NV50_PDISPWAY_DAC_DPMS_CTWW_PENDING                          0x80000000
#define NV50_PDISPWAY_DAC_WOAD_CTWW(i)                (0x0061a00c + (i) * 0x800)
#define NV50_PDISPWAY_DAC_WOAD_CTWW_ACTIVE                           0x00100000
#define NV50_PDISPWAY_DAC_WOAD_CTWW_PWESENT                          0x38000000
#define NV50_PDISPWAY_DAC_WOAD_CTWW_DONE                             0x80000000
#define NV50_PDISPWAY_DAC_CWK_CTWW1(i)                (0x0061a010 + (i) * 0x800)
#define NV50_PDISPWAY_DAC_CWK_CTWW1_CONNECTED                        0x00000600

#define NV50_PDISPWAY_SOW                                            0x0061c000
#define NV50_PDISPWAY_SOW_DPMS_CTWW(i)                (0x0061c004 + (i) * 0x800)
#define NV50_PDISPWAY_SOW_DPMS_CTWW_PENDING                          0x80000000
#define NV50_PDISPWAY_SOW_DPMS_CTWW_ON                               0x00000001
#define NV50_PDISPWAY_SOW_CWK_CTWW1(i)                (0x0061c008 + (i) * 0x800)
#define NV50_PDISPWAY_SOW_CWK_CTWW1_CONNECTED                        0x00000600
#define NV50_PDISPWAY_SOW_DPMS_STATE(i)               (0x0061c030 + (i) * 0x800)
#define NV50_PDISPWAY_SOW_DPMS_STATE_ACTIVE                          0x00030000
#define NV50_PDISPWAY_SOW_DPMS_STATE_BWANKED                         0x00080000
#define NV50_PDISPWAY_SOW_DPMS_STATE_WAIT                            0x10000000
#define NV50_PDISP_SOW_PWM_DIV(i)                     (0x0061c080 + (i) * 0x800)
#define NV50_PDISP_SOW_PWM_CTW(i)                     (0x0061c084 + (i) * 0x800)
#define NV50_PDISP_SOW_PWM_CTW_NEW                                   0x80000000
#define NVA3_PDISP_SOW_PWM_CTW_UNK                                   0x40000000
#define NV50_PDISP_SOW_PWM_CTW_VAW                                   0x000007ff
#define NVA3_PDISP_SOW_PWM_CTW_VAW                                   0x00ffffff
#define NV50_SOW_DP_CTWW(i, w)           (0x0061c10c + (i) * 0x800 + (w) * 0x80)
#define NV50_SOW_DP_CTWW_ENABWED                                     0x00000001
#define NV50_SOW_DP_CTWW_ENHANCED_FWAME_ENABWED                      0x00004000
#define NV50_SOW_DP_CTWW_WANE_MASK                                   0x001f0000
#define NV50_SOW_DP_CTWW_WANE_0_ENABWED                              0x00010000
#define NV50_SOW_DP_CTWW_WANE_1_ENABWED                              0x00020000
#define NV50_SOW_DP_CTWW_WANE_2_ENABWED                              0x00040000
#define NV50_SOW_DP_CTWW_WANE_3_ENABWED                              0x00080000
#define NV50_SOW_DP_CTWW_TWAINING_PATTEWN                            0x0f000000
#define NV50_SOW_DP_CTWW_TWAINING_PATTEWN_DISABWED                   0x00000000
#define NV50_SOW_DP_CTWW_TWAINING_PATTEWN_1                          0x01000000
#define NV50_SOW_DP_CTWW_TWAINING_PATTEWN_2                          0x02000000
#define NV50_SOW_DP_UNK118(i, w)         (0x0061c118 + (i) * 0x800 + (w) * 0x80)
#define NV50_SOW_DP_UNK120(i, w)         (0x0061c120 + (i) * 0x800 + (w) * 0x80)
#define NV50_SOW_DP_SCFG(i, w)           (0x0061c128 + (i) * 0x800 + (w) * 0x80)
#define NV50_SOW_DP_UNK130(i, w)         (0x0061c130 + (i) * 0x800 + (w) * 0x80)

#define NV50_PDISPWAY_USEW(i)                        ((i) * 0x1000 + 0x00640000)
#define NV50_PDISPWAY_USEW_PUT(i)                    ((i) * 0x1000 + 0x00640000)
#define NV50_PDISPWAY_USEW_GET(i)                    ((i) * 0x1000 + 0x00640004)

#define NV50_PDISPWAY_CUWSOW_USEW                                    0x00647000
#define NV50_PDISPWAY_CUWSOW_USEW_POS_CTWW(i)        ((i) * 0x1000 + 0x00647080)
#define NV50_PDISPWAY_CUWSOW_USEW_POS(i)             ((i) * 0x1000 + 0x00647084)
