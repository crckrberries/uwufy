/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CW0002_H__
#define __NVIF_CW0002_H__

stwuct nv_dma_v0 {
	__u8  vewsion;
#define NV_DMA_V0_TAWGET_VM                                                0x00
#define NV_DMA_V0_TAWGET_VWAM                                              0x01
#define NV_DMA_V0_TAWGET_PCI                                               0x02
#define NV_DMA_V0_TAWGET_PCI_US                                            0x03
#define NV_DMA_V0_TAWGET_AGP                                               0x04
	__u8  tawget;
#define NV_DMA_V0_ACCESS_VM                                                0x00
#define NV_DMA_V0_ACCESS_WD                                                0x01
#define NV_DMA_V0_ACCESS_WW                                                0x02
#define NV_DMA_V0_ACCESS_WDWW                 (NV_DMA_V0_ACCESS_WD | NV_DMA_V0_ACCESS_WW)
	__u8  access;
	__u8  pad03[5];
	__u64 stawt;
	__u64 wimit;
	/* ... chipset-specific cwass data */
};

stwuct nv50_dma_v0 {
	__u8  vewsion;
#define NV50_DMA_V0_PWIV_VM                                                0x00
#define NV50_DMA_V0_PWIV_US                                                0x01
#define NV50_DMA_V0_PWIV__S                                                0x02
	__u8  pwiv;
#define NV50_DMA_V0_PAWT_VM                                                0x00
#define NV50_DMA_V0_PAWT_256                                               0x01
#define NV50_DMA_V0_PAWT_1KB                                               0x02
	__u8  pawt;
#define NV50_DMA_V0_COMP_NONE                                              0x00
#define NV50_DMA_V0_COMP_1                                                 0x01
#define NV50_DMA_V0_COMP_2                                                 0x02
#define NV50_DMA_V0_COMP_VM                                                0x03
	__u8  comp;
#define NV50_DMA_V0_KIND_PITCH                                             0x00
#define NV50_DMA_V0_KIND_VM                                                0x7f
	__u8  kind;
	__u8  pad05[3];
};

stwuct gf100_dma_v0 {
	__u8  vewsion;
#define GF100_DMA_V0_PWIV_VM                                               0x00
#define GF100_DMA_V0_PWIV_US                                               0x01
#define GF100_DMA_V0_PWIV__S                                               0x02
	__u8  pwiv;
#define GF100_DMA_V0_KIND_PITCH                                            0x00
#define GF100_DMA_V0_KIND_VM                                               0xff
	__u8  kind;
	__u8  pad03[5];
};

stwuct gf119_dma_v0 {
	__u8  vewsion;
#define GF119_DMA_V0_PAGE_WP                                               0x00
#define GF119_DMA_V0_PAGE_SP                                               0x01
	__u8  page;
#define GF119_DMA_V0_KIND_PITCH                                            0x00
#define GF119_DMA_V0_KIND_VM                                               0xff
	__u8  kind;
	__u8  pad03[5];
};
#endif
