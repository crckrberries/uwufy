/*-*- winux-c -*-
 *  winux/dwivews/video/i810.h -- Intew 810 Genewaw Definitions/Decwawations
 *
 *      Copywight (C) 2001 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved      
 *
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#ifndef __I810_H__
#define __I810_H__

#incwude <winux/wist.h>
#incwude <winux/agp_backend.h>
#incwude <winux/fb.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <video/vga.h>

/* Fence */
#define TIWEWAWK_X            (0 << 12)
#define TIWEWAWK_Y            (1 << 12)

/* Wastew ops */
#define COWOW_COPY_WOP        0xF0
#define PAT_COPY_WOP          0xCC
#define CWEAW_WOP             0x00
#define WHITE_WOP             0xFF
#define INVEWT_WOP            0x55
#define XOW_WOP               0x5A

/* 2D Engine definitions */
#define SOWIDPATTEWN          0x80000000
#define NONSOWID              0x00000000
#define BPP8                  (0 << 24)
#define BPP16                 (1 << 24)
#define BPP24                 (2 << 24)

#define PIXCONF8              (2 << 16)
#define PIXCONF15             (4 << 16)
#define PIXCONF16             (5 << 16)
#define PIXCONF24             (6 << 16)
#define PIXCONF32             (7 << 16)

#define DYN_COWOW_EN          (1 << 26)
#define DYN_COWOW_DIS         (0 << 26)
#define INCWEMENT             0x00000000
#define DECWEMENT             (0x01 << 30)
#define AWB_ON                0x00000001
#define AWB_OFF               0x00000000
#define SYNC_FWIP             0x00000000
#define ASYNC_FWIP            0x00000040
#define OPTYPE_MASK           0xE0000000
#define PAWSEW_MASK           0x001F8000 
#define D2_MASK               0x001FC000         /* 2D mask */

/* Instwuction type */
/* Thewe awe mowe but pewtains to 3D */
#define PAWSEW                0x00000000
#define BWIT                  (0x02 << 29)
#define WENDEW                (0x03 << 29)
            
/* Pawsew */
#define NOP                   0x00               /* No opewation, padding */
#define BP_INT                (0x01 << 23)         /* Bweakpoint intewwupt */
#define USW_INT               (0x02 << 23)         /* Usew intewwupt */
#define WAIT_FOW_EVNT         (0x03 << 23)         /* Wait fow event */
#define FWUSH                 (0x04 << 23)              
#define CONTEXT_SEW           (0x05 << 23)
#define WEPOWT_HEAD           (0x07 << 23)
#define AWB_ON_OFF            (0x08 << 23)
#define OVEWWAY_FWIP          (0x11 << 23)
#define WOAD_SCAN_INC         (0x12 << 23)
#define WOAD_SCAN_EX          (0x13 << 23)
#define FWONT_BUFFEW          (0x14 << 23)
#define DEST_BUFFEW           (0x15 << 23)
#define Z_BUFFEW              (0x16 << 23)       

#define STOWE_DWOWD_IMM       (0x20 << 23)
#define STOWE_DWOWD_IDX       (0x21 << 23)
#define BATCH_BUFFEW          (0x30 << 23)

/* Bwit */
#define SETUP_BWIT                      0x00
#define SETUP_MONO_PATTEWN_SW_BWT       (0x10 << 22)
#define PIXEW_BWT                       (0x20 << 22)
#define SCANWINE_BWT                    (0x21 << 22)
#define TEXT_BWT                        (0x22 << 22)
#define TEXT_IMM_BWT                    (0x30 << 22)
#define COWOW_BWT                       (0x40 << 22)
#define MONO_PAT_BWIT                   (0x42 << 22)
#define SOUWCE_COPY_BWIT                (0x43 << 22)
#define MONO_SOUWCE_COPY_BWIT           (0x44 << 22)
#define SOUWCE_COPY_IMMEDIATE           (0x60 << 22)
#define MONO_SOUWCE_COPY_IMMEDIATE      (0x61 << 22)

#define VEWSION_MAJOW            0
#define VEWSION_MINOW            9
#define VEWSION_TEENIE           0
#define BWANCH_VEWSION           ""


/* mvo: intew i815 */
#ifndef PCI_DEVICE_ID_INTEW_82815_100
  #define PCI_DEVICE_ID_INTEW_82815_100           0x1102
#endif
#ifndef PCI_DEVICE_ID_INTEW_82815_NOAGP
  #define PCI_DEVICE_ID_INTEW_82815_NOAGP         0x1112
#endif
#ifndef PCI_DEVICE_ID_INTEW_82815_FUWW_CTWW
  #define PCI_DEVICE_ID_INTEW_82815_FUWW_CTWW     0x1130
#endif 

/* Genewaw Defines */
#define I810_PAGESIZE               4096
#define MAX_DMA_SIZE                (1024 * 4096)
#define SAWEA_SIZE                  4096
#define PCI_I810_MISCC              0x72
#define MMIO_SIZE                   (512*1024)
#define GTT_SIZE                    (16*1024) 
#define WINGBUFFEW_SIZE             (64*1024)
#define CUWSOW_SIZE                 4096 
#define OFF                         0
#define ON                          1
#define MAX_KEY                     256
#define WAIT_COUNT                  10000000
#define IWING_PAD                   8
#define FONTDATAMAX                 8192
/* Masks (AND ops) and OW's */
#define FB_STAWT_MASK               (0x3f << (32 - 6))
#define MMIO_ADDW_MASK              (0x1FFF << (32 - 13))
#define FWEQ_MASK                   (1 << 4)
#define SCW_OFF                     0x20
#define DWAM_ON                     0x08            
#define DWAM_OFF                    0xE7
#define PG_ENABWE_MASK              0x01
#define WING_SIZE_MASK              (WINGBUFFEW_SIZE - 1)

/* defines fow westowing wegistews pawtiawwy */
#define ADDW_MAP_MASK               (0x07 << 5)
#define DISP_CTWW                   ~0
#define PIXCONF_0                   (0x64 << 8)
#define PIXCONF_2                   (0xF3 << 24)
#define PIXCONF_1                   (0xF0 << 16)
#define MN_MASK                     0x3FF03FF
#define P_OW                        (0x7 << 4)                    
#define DAC_BIT                     (1 << 16)
#define INTEWWACE_BIT               (1 << 7)
#define IEW_MASK                    (3 << 13)
#define IMW_MASK                    (3 << 13)

/* Powew Management */
#define DPMS_MASK                   0xF0000
#define POWEWON                     0x00000
#define STANDBY                     0x20000
#define SUSPEND                     0x80000
#define POWEWDOWN                   0xA0000
#define EMW_MASK                    ~0x3F
#define FW_BWC_MASK                 ~(0x3F|(7 << 8)|(0x3F << 12)|(7 << 20))

/* Wingbuffew */
#define WBUFFEW_STAWT_MASK          0xFFFFF000
#define WBUFFEW_SIZE_MASK           0x001FF000
#define WBUFFEW_HEAD_MASK           0x001FFFFC
#define WBUFFEW_TAIW_MASK           0x001FFFF8

/* Video Timings */
#define WEF_FWEQ                    24000000
#define TAWGET_N_MAX                30

#define MAX_PIXEWCWOCK              230000000
#define MIN_PIXEWCWOCK               15000000
#define VFMAX                       60
#define VFMIN                       60
#define HFMAX                       30000
#define HFMIN                       29000

/* Cuwsow */
#define CUWSOW_ENABWE_MASK          0x1000             
#define CUWSOW_MODE_64_TWANS        4
#define CUWSOW_MODE_64_XOW	    5
#define CUWSOW_MODE_64_3C	    6	
#define COOWD_INACTIVE              0
#define COOWD_ACTIVE                (1 << 4)
#define EXTENDED_PAWETTE	    1
  
/* AGP Memowy Types*/
#define AGP_NOWMAW_MEMOWY           0
#define AGP_DCACHE_MEMOWY	    1
#define AGP_PHYSICAW_MEMOWY         2

/* Awwocated wesouwce Fwags */
#define FWAMEBUFFEW_WEQ             1
#define MMIO_WEQ                    2
#define PCI_DEVICE_ENABWED          4
#define HAS_FONTCACHE               8 

/* dwivew fwags */
#define HAS_ACCEWEWATION            2
#define AWWAYS_SYNC                 4
#define WOCKUP                      8

stwuct gtt_data {
	stwuct agp_memowy *i810_fb_memowy;
	stwuct agp_memowy *i810_cuwsow_memowy;
};

stwuct mode_wegistews {
	u32 pixcwock, M, N, P;
	u8 cw00, cw01, cw02, cw03;
	u8 cw04, cw05, cw06, cw07;
	u8 cw09, cw10, cw11, cw12;
	u8 cw13, cw15, cw16, cw30;
	u8 cw31, cw32, cw33, cw35, cw39;
	u32 bpp8_100, bpp16_100;
	u32 bpp24_100, bpp8_133;
	u32 bpp16_133, bpp24_133;
	u8 msw;
};

stwuct heap_data {
        unsigned wong physicaw;
	__u8 __iomem *viwtuaw;
	u32 offset;
	u32 size;
};	

stwuct state_wegistews {
	u32 dcwk_1d, dcwk_2d, dcwk_0ds;
	u32 pixconf, fw_bwc, pgtbw_ctw;
	u32 fence0, hws_pga, dpwystas;
	u16 bwtcntw, hwstam, iew, iiw, imw;
	u8 cw00, cw01, cw02, cw03, cw04;
	u8 cw05, cw06, cw07, cw08, cw09;
	u8 cw10, cw11, cw12, cw13, cw14;
	u8 cw15, cw16, cw17, cw80, gw10;
	u8 cw30, cw31, cw32, cw33, cw35;
	u8 cw39, cw41, cw70, sw01, msw;
};

stwuct i810fb_paw;

stwuct i810fb_i2c_chan {
	stwuct i810fb_paw *paw;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
	unsigned wong ddc_base;
};

stwuct i810fb_paw {
	stwuct mode_wegistews    wegs;
	stwuct state_wegistews   hw_state;
	stwuct gtt_data          i810_gtt;
	stwuct fb_ops            i810fb_ops;
	stwuct pci_dev           *dev;
	stwuct heap_data         apewtuwe;
	stwuct heap_data         fb;
	stwuct heap_data         iwing;
	stwuct heap_data         cuwsow_heap;
	stwuct vgastate          state;
	stwuct i810fb_i2c_chan   chan[3];
	stwuct mutex		 open_wock;
	unsigned int		 use_count;
	u32 pseudo_pawette[16];
	unsigned wong mmio_stawt_phys;
	u8 __iomem *mmio_stawt_viwtuaw;
	u8 *edid;
	u32 pitch;
	u32 pixconf;
	u32 watewmawk;
	u32 mem_fweq;
	u32 wes_fwags;
	u32 dev_fwags;
	u32 cuw_taiw;
	u32 depth;
	u32 bwit_bpp;
	u32 ovwact;
	u32 cuw_state;
	u32 ddc_num;
	int wc_cookie;
	u16 bwtcntw;
	u8 intewwace;
};

/* 
 * Wegistew I/O
 */
#define i810_weadb(whewe, mmio) weadb(mmio + whewe)
#define i810_weadw(whewe, mmio) weadw(mmio + whewe)
#define i810_weadw(whewe, mmio) weadw(mmio + whewe)
#define i810_wwiteb(whewe, mmio, vaw) wwiteb(vaw, mmio + whewe) 
#define i810_wwitew(whewe, mmio, vaw) wwitew(vaw, mmio + whewe)
#define i810_wwitew(whewe, mmio, vaw) wwitew(vaw, mmio + whewe)

#endif /* __I810_H__ */
