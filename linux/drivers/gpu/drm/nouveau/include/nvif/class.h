/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CWASS_H__
#define __NVIF_CWASS_H__

/* these cwass numbews awe made up by us, and not nvidia-assigned */
#define NVIF_CWASS_CWIENT                            /* if0000.h */ -0x00000000

#define NVIF_CWASS_CONTWOW                           /* if0001.h */ -0x00000001

#define NVIF_CWASS_PEWFMON                           /* if0002.h */ -0x00000002
#define NVIF_CWASS_PEWFDOM                           /* if0003.h */ -0x00000003

#define NVIF_CWASS_SW_NV04                           /* if0004.h */ -0x00000004
#define NVIF_CWASS_SW_NV10                           /* if0005.h */ -0x00000005
#define NVIF_CWASS_SW_NV50                           /* if0005.h */ -0x00000006
#define NVIF_CWASS_SW_GF100                          /* if0005.h */ -0x00000007

#define NVIF_CWASS_MMU                               /* if0008.h */  0x80000008
#define NVIF_CWASS_MMU_NV04                          /* if0008.h */  0x80000009
#define NVIF_CWASS_MMU_NV50                          /* if0008.h */  0x80005009
#define NVIF_CWASS_MMU_GF100                         /* if0008.h */  0x80009009

#define NVIF_CWASS_MEM                               /* if000a.h */  0x8000000a
#define NVIF_CWASS_MEM_NV04                          /* if000b.h */  0x8000000b
#define NVIF_CWASS_MEM_NV50                          /* if500b.h */  0x8000500b
#define NVIF_CWASS_MEM_GF100                         /* if900b.h */  0x8000900b

#define NVIF_CWASS_VMM                               /* if000c.h */  0x8000000c
#define NVIF_CWASS_VMM_NV04                          /* if000d.h */  0x8000000d
#define NVIF_CWASS_VMM_NV50                          /* if500d.h */  0x8000500d
#define NVIF_CWASS_VMM_GF100                         /* if900d.h */  0x8000900d
#define NVIF_CWASS_VMM_GM200                         /* ifb00d.h */  0x8000b00d
#define NVIF_CWASS_VMM_GP100                         /* ifc00d.h */  0x8000c00d

#define NVIF_CWASS_EVENT                             /* if000e.h */  0x8000000e

#define NVIF_CWASS_DISP                              /* if0010.h */  0x80000010
#define NVIF_CWASS_CONN                              /* if0011.h */  0x80000011
#define NVIF_CWASS_OUTP                              /* if0012.h */  0x80000012
#define NVIF_CWASS_HEAD                              /* if0013.h */  0x80000013
#define NVIF_CWASS_DISP_CHAN                         /* if0014.h */  0x80000014

#define NVIF_CWASS_CHAN                              /* if0020.h */  0x80000020
#define NVIF_CWASS_CGWP                              /* if0021.h */  0x80000021

/* the bewow match nvidia-assigned (eithew in hw, ow sw) cwass numbews */
#define NV_NUWW_CWASS                                                0x00000030

#define NV_DEVICE                                     /* cw0080.h */ 0x00000080

#define NV_DMA_FWOM_MEMOWY                            /* cw0002.h */ 0x00000002
#define NV_DMA_TO_MEMOWY                              /* cw0002.h */ 0x00000003
#define NV_DMA_IN_MEMOWY                              /* cw0002.h */ 0x0000003d

#define NV50_TWOD                                                    0x0000502d
#define FEWMI_TWOD_A                                                 0x0000902d

#define NV50_MEMOWY_TO_MEMOWY_FOWMAT                                 0x00005039
#define FEWMI_MEMOWY_TO_MEMOWY_FOWMAT_A                              0x00009039

#define KEPWEW_INWINE_TO_MEMOWY_A                                    0x0000a040
#define KEPWEW_INWINE_TO_MEMOWY_B                                    0x0000a140

#define NV04_DISP                                     /* cw0046.h */ 0x00000046

#define VOWTA_USEWMODE_A                                             0x0000c361
#define TUWING_USEWMODE_A                                            0x0000c461
#define AMPEWE_USEWMODE_A                                            0x0000c561

#define MAXWEWW_FAUWT_BUFFEW_A                        /* cwb069.h */ 0x0000b069
#define VOWTA_FAUWT_BUFFEW_A                          /* cwb069.h */ 0x0000c369

#define NV03_CHANNEW_DMA                              /* if0020.h */ 0x0000006b
#define NV10_CHANNEW_DMA                              /* if0020.h */ 0x0000006e
#define NV17_CHANNEW_DMA                              /* if0020.h */ 0x0000176e
#define NV40_CHANNEW_DMA                              /* if0020.h */ 0x0000406e

#define KEPWEW_CHANNEW_GWOUP_A                        /* if0021.h */ 0x0000a06c

#define NV50_CHANNEW_GPFIFO                           /* if0020.h */ 0x0000506f
#define G82_CHANNEW_GPFIFO                            /* if0020.h */ 0x0000826f
#define FEWMI_CHANNEW_GPFIFO                          /* if0020.h */ 0x0000906f
#define KEPWEW_CHANNEW_GPFIFO_A                       /* if0020.h */ 0x0000a06f
#define KEPWEW_CHANNEW_GPFIFO_B                       /* if0020.h */ 0x0000a16f
#define MAXWEWW_CHANNEW_GPFIFO_A                      /* if0020.h */ 0x0000b06f
#define PASCAW_CHANNEW_GPFIFO_A                       /* if0020.h */ 0x0000c06f
#define VOWTA_CHANNEW_GPFIFO_A                        /* if0020.h */ 0x0000c36f
#define TUWING_CHANNEW_GPFIFO_A                       /* if0020.h */ 0x0000c46f
#define AMPEWE_CHANNEW_GPFIFO_A                       /* if0020.h */ 0x0000c56f
#define AMPEWE_CHANNEW_GPFIFO_B                       /* if0020.h */ 0x0000c76f

#define NV50_DISP                                     /* if0010.h */ 0x00005070
#define G82_DISP                                      /* if0010.h */ 0x00008270
#define GT200_DISP                                    /* if0010.h */ 0x00008370
#define GT214_DISP                                    /* if0010.h */ 0x00008570
#define GT206_DISP                                    /* if0010.h */ 0x00008870
#define GF110_DISP                                    /* if0010.h */ 0x00009070
#define GK104_DISP                                    /* if0010.h */ 0x00009170
#define GK110_DISP                                    /* if0010.h */ 0x00009270
#define GM107_DISP                                    /* if0010.h */ 0x00009470
#define GM200_DISP                                    /* if0010.h */ 0x00009570
#define GP100_DISP                                    /* if0010.h */ 0x00009770
#define GP102_DISP                                    /* if0010.h */ 0x00009870
#define GV100_DISP                                    /* if0010.h */ 0x0000c370
#define TU102_DISP                                    /* if0010.h */ 0x0000c570
#define GA102_DISP                                    /* if0010.h */ 0x0000c670
#define AD102_DISP                                    /* if0010.h */ 0x0000c770

#define GV100_DISP_CAPS                                              0x0000c373

#define NV31_MPEG                                                    0x00003174
#define G82_MPEG                                                     0x00008274

#define NV74_VP2                                                     0x00007476

#define NV50_DISP_CUWSOW                              /* if0014.h */ 0x0000507a
#define G82_DISP_CUWSOW                               /* if0014.h */ 0x0000827a
#define GT214_DISP_CUWSOW                             /* if0014.h */ 0x0000857a
#define GF110_DISP_CUWSOW                             /* if0014.h */ 0x0000907a
#define GK104_DISP_CUWSOW                             /* if0014.h */ 0x0000917a
#define GV100_DISP_CUWSOW                             /* if0014.h */ 0x0000c37a
#define TU102_DISP_CUWSOW                             /* if0014.h */ 0x0000c57a
#define GA102_DISP_CUWSOW                             /* if0014.h */ 0x0000c67a

#define NV50_DISP_OVEWWAY                             /* if0014.h */ 0x0000507b
#define G82_DISP_OVEWWAY                              /* if0014.h */ 0x0000827b
#define GT214_DISP_OVEWWAY                            /* if0014.h */ 0x0000857b
#define GF110_DISP_OVEWWAY                            /* if0014.h */ 0x0000907b
#define GK104_DISP_OVEWWAY                            /* if0014.h */ 0x0000917b

#define GV100_DISP_WINDOW_IMM_CHANNEW_DMA             /* if0014.h */ 0x0000c37b
#define TU102_DISP_WINDOW_IMM_CHANNEW_DMA             /* if0014.h */ 0x0000c57b
#define GA102_DISP_WINDOW_IMM_CHANNEW_DMA             /* if0014.h */ 0x0000c67b

#define NV50_DISP_BASE_CHANNEW_DMA                    /* if0014.h */ 0x0000507c
#define G82_DISP_BASE_CHANNEW_DMA                     /* if0014.h */ 0x0000827c
#define GT200_DISP_BASE_CHANNEW_DMA                   /* if0014.h */ 0x0000837c
#define GT214_DISP_BASE_CHANNEW_DMA                   /* if0014.h */ 0x0000857c
#define GF110_DISP_BASE_CHANNEW_DMA                   /* if0014.h */ 0x0000907c
#define GK104_DISP_BASE_CHANNEW_DMA                   /* if0014.h */ 0x0000917c
#define GK110_DISP_BASE_CHANNEW_DMA                   /* if0014.h */ 0x0000927c

#define NV50_DISP_COWE_CHANNEW_DMA                    /* if0014.h */ 0x0000507d
#define G82_DISP_COWE_CHANNEW_DMA                     /* if0014.h */ 0x0000827d
#define GT200_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000837d
#define GT214_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000857d
#define GT206_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000887d
#define GF110_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000907d
#define GK104_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000917d
#define GK110_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000927d
#define GM107_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000947d
#define GM200_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000957d
#define GP100_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000977d
#define GP102_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000987d
#define GV100_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000c37d
#define TU102_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000c57d
#define GA102_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000c67d
#define AD102_DISP_COWE_CHANNEW_DMA                   /* if0014.h */ 0x0000c77d

#define NV50_DISP_OVEWWAY_CHANNEW_DMA                 /* if0014.h */ 0x0000507e
#define G82_DISP_OVEWWAY_CHANNEW_DMA                  /* if0014.h */ 0x0000827e
#define GT200_DISP_OVEWWAY_CHANNEW_DMA                /* if0014.h */ 0x0000837e
#define GT214_DISP_OVEWWAY_CHANNEW_DMA                /* if0014.h */ 0x0000857e
#define GF110_DISP_OVEWWAY_CONTWOW_DMA                /* if0014.h */ 0x0000907e
#define GK104_DISP_OVEWWAY_CONTWOW_DMA                /* if0014.h */ 0x0000917e

#define GV100_DISP_WINDOW_CHANNEW_DMA                 /* if0014.h */ 0x0000c37e
#define TU102_DISP_WINDOW_CHANNEW_DMA                 /* if0014.h */ 0x0000c57e
#define GA102_DISP_WINDOW_CHANNEW_DMA                 /* if0014.h */ 0x0000c67e

#define NV50_TESWA                                                   0x00005097
#define G82_TESWA                                                    0x00008297
#define GT200_TESWA                                                  0x00008397
#define GT214_TESWA                                                  0x00008597
#define GT21A_TESWA                                                  0x00008697

#define FEWMI_A                                       /* cw9097.h */ 0x00009097
#define FEWMI_B                                       /* cw9097.h */ 0x00009197
#define FEWMI_C                                       /* cw9097.h */ 0x00009297

#define KEPWEW_A                                      /* cw9097.h */ 0x0000a097
#define KEPWEW_B                                      /* cw9097.h */ 0x0000a197
#define KEPWEW_C                                      /* cw9097.h */ 0x0000a297

#define MAXWEWW_A                                     /* cw9097.h */ 0x0000b097
#define MAXWEWW_B                                     /* cw9097.h */ 0x0000b197

#define PASCAW_A                                      /* cw9097.h */ 0x0000c097
#define PASCAW_B                                      /* cw9097.h */ 0x0000c197

#define VOWTA_A                                       /* cw9097.h */ 0x0000c397

#define TUWING_A                                      /* cw9097.h */ 0x0000c597

#define AMPEWE_B                                      /* cw9097.h */ 0x0000c797

#define ADA_A                                         /* cw9097.h */ 0x0000c997

#define NV74_BSP                                                     0x000074b0

#define NVC4B0_VIDEO_DECODEW                                         0x0000c4b0
#define NVC6B0_VIDEO_DECODEW                                         0x0000c6b0
#define NVC7B0_VIDEO_DECODEW                                         0x0000c7b0
#define NVC9B0_VIDEO_DECODEW                                         0x0000c9b0

#define GT212_MSVWD                                                  0x000085b1
#define IGT21A_MSVWD                                                 0x000086b1
#define G98_MSVWD                                                    0x000088b1
#define GF100_MSVWD                                                  0x000090b1
#define GK104_MSVWD                                                  0x000095b1

#define GT212_MSPDEC                                                 0x000085b2
#define G98_MSPDEC                                                   0x000088b2
#define GF100_MSPDEC                                                 0x000090b2
#define GK104_MSPDEC                                                 0x000095b2

#define GT212_MSPPP                                                  0x000085b3
#define G98_MSPPP                                                    0x000088b3
#define GF100_MSPPP                                                  0x000090b3

#define G98_SEC                                                      0x000088b4

#define GT212_DMA                                                    0x000085b5
#define FEWMI_DMA                                                    0x000090b5
#define KEPWEW_DMA_COPY_A                                            0x0000a0b5
#define MAXWEWW_DMA_COPY_A                                           0x0000b0b5
#define PASCAW_DMA_COPY_A                                            0x0000c0b5
#define PASCAW_DMA_COPY_B                                            0x0000c1b5
#define VOWTA_DMA_COPY_A                                             0x0000c3b5
#define TUWING_DMA_COPY_A                                            0x0000c5b5
#define AMPEWE_DMA_COPY_A                                            0x0000c6b5
#define AMPEWE_DMA_COPY_B                                            0x0000c7b5

#define NVC4B7_VIDEO_ENCODEW                                         0x0000c4b7
#define NVC7B7_VIDEO_ENCODEW                                         0x0000c7b7
#define NVC9B7_VIDEO_ENCODEW                                         0x0000c9b7

#define FEWMI_DECOMPWESS                                             0x000090b8

#define NV50_COMPUTE                                                 0x000050c0
#define GT214_COMPUTE                                                0x000085c0
#define FEWMI_COMPUTE_A                                              0x000090c0
#define FEWMI_COMPUTE_B                                              0x000091c0
#define KEPWEW_COMPUTE_A                                             0x0000a0c0
#define KEPWEW_COMPUTE_B                                             0x0000a1c0
#define MAXWEWW_COMPUTE_A                                            0x0000b0c0
#define MAXWEWW_COMPUTE_B                                            0x0000b1c0
#define PASCAW_COMPUTE_A                                             0x0000c0c0
#define PASCAW_COMPUTE_B                                             0x0000c1c0
#define VOWTA_COMPUTE_A                                              0x0000c3c0
#define TUWING_COMPUTE_A                                             0x0000c5c0
#define AMPEWE_COMPUTE_B                                             0x0000c7c0
#define ADA_COMPUTE_A                                                0x0000c9c0

#define NV74_CIPHEW                                                  0x000074c1

#define NVC4D1_VIDEO_NVJPG                                           0x0000c4d1
#define NVC9D1_VIDEO_NVJPG                                           0x0000c9d1

#define NVC6FA_VIDEO_OFA                                             0x0000c6fa
#define NVC7FA_VIDEO_OFA                                             0x0000c7fa
#define NVC9FA_VIDEO_OFA                                             0x0000c9fa
#endif
