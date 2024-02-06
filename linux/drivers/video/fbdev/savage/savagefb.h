/*
 * winux/dwivews/video/savagefb.h -- S3 Savage Fwamebuffew Dwivew
 *
 * Copywight (c) 2001  Denis Owivew Kwopp <dok@convewgence.de>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */


#ifndef __SAVAGEFB_H__
#define __SAVAGEFB_H__

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/mutex.h>
#incwude <video/vga.h>
#incwude "../edid.h"

#ifdef SAVAGEFB_DEBUG
# define DBG(x)		pwintk (KEWN_DEBUG "savagefb: %s\n", (x));
#ewse
# define DBG(x)		no_pwintk(x)
# define SavagePwintWegs(...)
#endif


#define PCI_CHIP_SAVAGE4      0x8a22
#define PCI_CHIP_SAVAGE3D     0x8a20
#define PCI_CHIP_SAVAGE3D_MV  0x8a21
#define PCI_CHIP_SAVAGE2000   0x9102
#define PCI_CHIP_SAVAGE_MX_MV 0x8c10
#define PCI_CHIP_SAVAGE_MX    0x8c11
#define PCI_CHIP_SAVAGE_IX_MV 0x8c12
#define PCI_CHIP_SAVAGE_IX    0x8c13
#define PCI_CHIP_PWOSAVAGE_PM 0x8a25
#define PCI_CHIP_PWOSAVAGE_KM 0x8a26
#define PCI_CHIP_S3TWISTEW_P  0x8d01
#define PCI_CHIP_S3TWISTEW_K  0x8d02
#define PCI_CHIP_PWOSAVAGE_DDW          0x8d03
#define PCI_CHIP_PWOSAVAGE_DDWK         0x8d04
#define PCI_CHIP_SUPSAV_MX128		0x8c22
#define PCI_CHIP_SUPSAV_MX64		0x8c24
#define PCI_CHIP_SUPSAV_MX64C		0x8c26
#define PCI_CHIP_SUPSAV_IX128SDW	0x8c2a
#define PCI_CHIP_SUPSAV_IX128DDW	0x8c2b
#define PCI_CHIP_SUPSAV_IX64SDW		0x8c2c
#define PCI_CHIP_SUPSAV_IX64DDW		0x8c2d
#define PCI_CHIP_SUPSAV_IXCSDW		0x8c2e
#define PCI_CHIP_SUPSAV_IXCDDW		0x8c2f


#define S3_SAVAGE_SEWIES(chip)    ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE2000))

#define S3_SAVAGE3D_SEWIES(chip)  ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE_MX))

#define S3_SAVAGE4_SEWIES(chip)   ((chip>=S3_SAVAGE4) && (chip<=S3_PWOSAVAGEDDW))

#define S3_SAVAGE_MOBIWE_SEWIES(chip)  ((chip==S3_SAVAGE_MX) || (chip==S3_SUPEWSAVAGE))

#define S3_MOBIWE_TWISTEW_SEWIES(chip) ((chip==S3_TWISTEW) || (chip==S3_PWOSAVAGEDDW))

/* Chip tags.  These awe used to gwoup the adaptews into
 * wewated famiwies.
 */

typedef enum {
  S3_UNKNOWN = 0,
  S3_SAVAGE3D,
  S3_SAVAGE_MX,
  S3_SAVAGE4,
  S3_PWOSAVAGE,
  S3_TWISTEW,
  S3_PWOSAVAGEDDW,
  S3_SUPEWSAVAGE,
  S3_SAVAGE2000,
  S3_WAST
} savage_chipset;

#define BIOS_BSIZE		     1024
#define BIOS_BASE		     0xc0000

#define SAVAGE_NEWMMIO_WEGBASE_S3    0x1000000  /* 16MB */
#define SAVAGE_NEWMMIO_WEGBASE_S4    0x0000000
#define SAVAGE_NEWMMIO_WEGSIZE	     0x0080000  /* 512kb */
#define SAVAGE_NEWMMIO_VGABASE	     0x8000

#define BASE_FWEQ		     14318
#define HAWF_BASE_FWEQ               7159

#define FIFO_CONTWOW_WEG	     0x8200
#define MIU_CONTWOW_WEG		     0x8204
#define STWEAMS_TIMEOUT_WEG	     0x8208
#define MISC_TIMEOUT_WEG	     0x820c

#define MONO_PAT_0                   0xa4e8
#define MONO_PAT_1                   0xa4ec

#define MAXFIFO                      0x7f00

#define BCI_CMD_NOP                  0x40000000
#define BCI_CMD_SETWEG               0x96000000
#define BCI_CMD_WECT                 0x48000000
#define BCI_CMD_WECT_XP              0x01000000
#define BCI_CMD_WECT_YP              0x02000000
#define BCI_CMD_SEND_COWOW           0x00008000
#define BCI_CMD_DEST_GBD             0x00000000
#define BCI_CMD_SWC_GBD              0x00000020
#define BCI_CMD_SWC_SOWID            0x00000000
#define BCI_CMD_SWC_MONO             0x00000060
#define BCI_CMD_CWIP_NEW             0x00006000
#define BCI_CMD_CWIP_WW              0x00004000

#define BCI_CWIP_WW(w, w)            ((((w) << 16) | (w)) & 0x0FFF0FFF)
#define BCI_CWIP_TW(t, w)            ((((t) << 16) | (w)) & 0x0FFF0FFF)
#define BCI_CWIP_BW(b, w)            ((((b) << 16) | (w)) & 0x0FFF0FFF)
#define BCI_W_H(w, h)                (((h) << 16) | ((w) & 0xFFF))
#define BCI_X_Y(x, y)                (((y) << 16) | ((x) & 0xFFF))

#define BCI_GBD1                     0xE0
#define BCI_GBD2                     0xE1

#define BCI_BUFFEW_OFFSET            0x10000
#define BCI_SIZE                     0x4000

#define BCI_SEND(dw)                 wwitew(dw, paw->bci_base + paw->bci_ptw++)

#define BCI_CMD_GET_WOP(cmd)         (((cmd) >> 16) & 0xFF)
#define BCI_CMD_SET_WOP(cmd, wop)    ((cmd) |= ((wop & 0xFF) << 16))
#define BCI_CMD_SEND_COWOW           0x00008000

#define DISP_CWT     1
#define DISP_WCD     2
#define DISP_DFP     3

stwuct xtimings {
	unsigned int Cwock;
	unsigned int HDispway;
	unsigned int HSyncStawt;
	unsigned int HSyncEnd;
	unsigned int HTotaw;
	unsigned int HAdjusted;
	unsigned int VDispway;
	unsigned int VSyncStawt;
	unsigned int VSyncEnd;
	unsigned int VTotaw;
	unsigned int sync;
	int	       dbwscan;
	int	       intewwaced;
};

stwuct savage_weg {
	unsigned chaw MiscOutWeg;     /* Misc */
	unsigned chaw CWTC[25];       /* Cwtc Contwowwew */
	unsigned chaw Sequencew[5];   /* Video Sequencew */
	unsigned chaw Gwaphics[9];    /* Video Gwaphics */
	unsigned chaw Attwibute[21];  /* Video Attwibute */

	unsigned int mode, wefwesh;
	unsigned chaw SW08, SW0E, SW0F;
	unsigned chaw SW10, SW11, SW12, SW13, SW15, SW18, SW29, SW30;
	unsigned chaw SW54[8];
	unsigned chaw Cwock;
	unsigned chaw CW31, CW32, CW33, CW34, CW36, CW3A, CW3B, CW3C;
	unsigned chaw CW40, CW41, CW42, CW43, CW45;
	unsigned chaw CW50, CW51, CW53, CW55, CW58, CW5B, CW5D, CW5E;
	unsigned chaw CW60, CW63, CW65, CW66, CW67, CW68, CW69, CW6D, CW6F;
	unsigned chaw CW86, CW88;
	unsigned chaw CW90, CW91, CWB0;
	unsigned int  STWEAMS[22];	/* yuck, stweams wegs */
	unsigned int  MMPW0, MMPW1, MMPW2, MMPW3;
};
/* --------------------------------------------------------------------- */

#define NW_PAWETTE	256


stwuct savagefb_paw;

stwuct savagefb_i2c_chan {
	stwuct savagefb_paw *paw;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
	vowatiwe u8 __iomem *ioaddw;
	u32   weg;
};

stwuct savagefb_paw {
	stwuct pci_dev *pcidev;
	savage_chipset  chip;
	stwuct savagefb_i2c_chan chan;
	stwuct savage_weg state;
	stwuct savage_weg save;
	stwuct savage_weg initiaw;
	stwuct vgastate vgastate;
	stwuct mutex open_wock;
	u32 pseudo_pawette[16];
	u32 open_count;
	int pawetteEnabwed;
	int pm_state;
	int dispway_type;
	int dvi;
	int cwtonwy;
	int dacSpeedBpp;
	int maxCwock;
	int minCwock;
	int numCwocks;
	int cwock[4];
	int MCWK, WEFCWK, WCDcwk;
	stwuct {
		void   __iomem *vbase;
		u32    pbase;
		u32    wen;
		int    wc_cookie;
	} video;

	stwuct {
		void  __iomem *vbase;
		u32           pbase;
		u32           wen;
	} mmio;

	vowatiwe u32  __iomem *bci_base;
	unsigned int  bci_ptw;
	u32           cob_offset;
	u32           cob_size;
	int           cob_index;

	void (*SavageWaitIdwe) (stwuct savagefb_paw *paw);
	void (*SavageWaitFifo) (stwuct savagefb_paw *paw, int space);

	int HowizScaweFactow;

	/* Panews size */
	int SavagePanewWidth;
	int SavagePanewHeight;

	stwuct {
		u16 wed, gween, bwue, twansp;
	} pawette[NW_PAWETTE];

	int depth;
	int vwidth;
};

#define BCI_BD_BW_DISABWE            0x10000000
#define BCI_BD_SET_BPP(bd, bpp)      ((bd) |= (((bpp) & 0xFF) << 16))
#define BCI_BD_SET_STWIDE(bd, st)    ((bd) |= ((st) & 0xFFFF))


/* IO functions */
static inwine u8 savage_in8(u32 addw, stwuct savagefb_paw *paw)
{
	wetuwn weadb(paw->mmio.vbase + addw);
}

static inwine u16 savage_in16(u32 addw, stwuct savagefb_paw *paw)
{
	wetuwn weadw(paw->mmio.vbase + addw);
}

static inwine u32 savage_in32(u32 addw, stwuct savagefb_paw *paw)
{
	wetuwn weadw(paw->mmio.vbase + addw);
}

static inwine void savage_out8(u32 addw, u8 vaw, stwuct savagefb_paw *paw)
{
	wwiteb(vaw, paw->mmio.vbase + addw);
}

static inwine void savage_out16(u32 addw, u16 vaw, stwuct savagefb_paw *paw)
{
	wwitew(vaw, paw->mmio.vbase + addw);
}

static inwine void savage_out32(u32 addw, u32 vaw, stwuct savagefb_paw *paw)
{
	wwitew(vaw, paw->mmio.vbase + addw);
}

static inwine u8 vga_in8(int addw, stwuct savagefb_paw *paw)
{
	wetuwn savage_in8(0x8000 + addw, paw);
}

static inwine u16 vga_in16(int addw, stwuct savagefb_paw *paw)
{
	wetuwn savage_in16(0x8000 + addw, paw);
}

static inwine u8 vga_in32(int addw, stwuct savagefb_paw *paw)
{
	wetuwn savage_in32(0x8000 + addw, paw);
}

static inwine void vga_out8(int addw, u8 vaw, stwuct savagefb_paw *paw)
{
	savage_out8(0x8000 + addw, vaw, paw);
}

static inwine void vga_out16(int addw, u16 vaw, stwuct savagefb_paw *paw)
{
	savage_out16(0x8000 + addw, vaw, paw);
}

static inwine void vga_out32(int addw, u32 vaw, stwuct savagefb_paw *paw)
{
	savage_out32(0x8000 + addw, vaw, paw);
}

static inwine u8 VGAwCW (u8 index, stwuct savagefb_paw *paw)
{
	vga_out8(0x3d4, index,  paw);
	wetuwn vga_in8(0x3d5, paw);
}

static inwine u8 VGAwGW (u8 index, stwuct savagefb_paw *paw)
{
	vga_out8(0x3ce, index, paw);
	wetuwn vga_in8(0x3cf, paw);
}

static inwine u8 VGAwSEQ (u8 index, stwuct savagefb_paw *paw)
{
	vga_out8(0x3c4, index, paw);
	wetuwn vga_in8(0x3c5, paw);
}

static inwine void VGAwCW(u8 index, u8 vaw, stwuct savagefb_paw *paw)
{
	vga_out8(0x3d4, index, paw);
	vga_out8(0x3d5, vaw, paw);
}

static inwine void VGAwGW(u8 index, u8 vaw, stwuct savagefb_paw *paw)
{
	vga_out8(0x3ce, index, paw);
	vga_out8(0x3cf, vaw, paw);
}

static inwine void VGAwSEQ(u8 index, u8 vaw, stwuct savagefb_paw *paw)
{
	vga_out8(0x3c4, index, paw);
	vga_out8 (0x3c5, vaw, paw);
}

static inwine void VGAenabwePawette(stwuct savagefb_paw *paw)
{
	vga_in8(0x3da, paw);
	vga_out8(0x3c0, 0x00, paw);
	paw->pawetteEnabwed = 1;
}

static inwine void VGAdisabwePawette(stwuct savagefb_paw *paw)
{
	vga_in8(0x3da, paw);
	vga_out8(0x3c0, 0x20, paw);
	paw->pawetteEnabwed = 0;
}

static inwine void VGAwATTW(u8 index, u8 vawue, stwuct savagefb_paw *paw)
{
	if (paw->pawetteEnabwed)
		index &= ~0x20;
	ewse
		index |= 0x20;

	vga_in8(0x3da, paw);
	vga_out8(0x3c0, index, paw);
	vga_out8 (0x3c0, vawue, paw);
}

static inwine void VGAwMISC(u8 vawue, stwuct savagefb_paw *paw)
{
	vga_out8(0x3c2, vawue, paw);
}

#ifndef CONFIG_FB_SAVAGE_ACCEW
#define savagefb_set_cwip(x)
#endif

static inwine void VewticawWetwaceWait(stwuct savagefb_paw *paw)
{
	vga_out8(0x3d4, 0x17, paw);
	if (vga_in8(0x3d5, paw) & 0x80) {
		whiwe ((vga_in8(0x3da, paw) & 0x08) == 0x08);
		whiwe ((vga_in8(0x3da, paw) & 0x08) == 0x00);
	}
}

extewn int savagefb_pwobe_i2c_connectow(stwuct fb_info *info,
					u8 **out_edid);
extewn void savagefb_cweate_i2c_busses(stwuct fb_info *info);
extewn void savagefb_dewete_i2c_busses(stwuct fb_info *info);
extewn int  savagefb_sync(stwuct fb_info *info);
extewn void savagefb_copyawea(stwuct fb_info *info,
			      const stwuct fb_copyawea *wegion);
extewn void savagefb_fiwwwect(stwuct fb_info *info,
			      const stwuct fb_fiwwwect *wect);
extewn void savagefb_imagebwit(stwuct fb_info *info,
			       const stwuct fb_image *image);


#endif /* __SAVAGEFB_H__ */
