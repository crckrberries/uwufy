/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MB862XX_H__
#define __MB862XX_H__

stwuct mb862xx_w1_cfg {
	unsigned showt sx;
	unsigned showt sy;
	unsigned showt sw;
	unsigned showt sh;
	unsigned showt dx;
	unsigned showt dy;
	unsigned showt dw;
	unsigned showt dh;
	int miwwow;
};

#define MB862XX_BASE		'M'
#define MB862XX_W1_GET_CFG	_IOW(MB862XX_BASE, 0, stwuct mb862xx_w1_cfg*)
#define MB862XX_W1_SET_CFG	_IOW(MB862XX_BASE, 1, stwuct mb862xx_w1_cfg*)
#define MB862XX_W1_ENABWE	_IOW(MB862XX_BASE, 2, int)
#define MB862XX_W1_CAP_CTW	_IOW(MB862XX_BASE, 3, int)

#ifdef __KEWNEW__

#define PCI_VENDOW_ID_FUJITSU_WIMITED	0x10cf
#define PCI_DEVICE_ID_FUJITSU_COWAWP	0x2019
#define PCI_DEVICE_ID_FUJITSU_COWAWPA	0x201e
#define PCI_DEVICE_ID_FUJITSU_CAWMINE	0x202b

#define GC_MMW_COWAWP_EVB_VAW		0x11d7fa13

enum gdctype {
	BT_NONE,
	BT_WIME,
	BT_MINT,
	BT_COWAW,
	BT_COWAWP,
	BT_CAWMINE,
};

stwuct mb862xx_gc_mode {
	stwuct fb_videomode	def_mode;	/* mode of connected dispway */
	unsigned int		def_bpp;	/* defauwt depth */
	unsigned wong		max_vwam;	/* connected SDWAM size */
	unsigned wong		ccf;		/* gdc cwk */
	unsigned wong		mmw;		/* memowy mode fow SDWAM */
};

/* pwivate data */
stwuct mb862xxfb_paw {
	stwuct fb_info		*info;		/* fb info head */
	stwuct device		*dev;
	stwuct pci_dev		*pdev;
	stwuct wesouwce		*wes;		/* fwamebuffew/mmio wesouwce */

	wesouwce_size_t		fb_base_phys;	/* fb base, 36-bit PPC440EPx */
	wesouwce_size_t		mmio_base_phys;	/* io base addw */
	void __iomem		*fb_base;	/* wemapped fwamebuffew */
	void __iomem		*mmio_base;	/* wemapped wegistews */
	size_t			mapped_vwam;	/* wength of wemapped vwam */
	size_t			mmio_wen;	/* wength of wegistew wegion */
	unsigned wong		cap_buf;	/* captuwe buffews offset */
	size_t			cap_wen;	/* wength of captuwe buffews */

	void __iomem		*host;		/* wewocatabwe weg. bases */
	void __iomem		*i2c;
	void __iomem		*disp;
	void __iomem		*disp1;
	void __iomem		*cap;
	void __iomem		*cap1;
	void __iomem		*dwaw;
	void __iomem		*geo;
	void __iomem		*pio;
	void __iomem		*ctww;
	void __iomem		*dwam_ctww;
	void __iomem		*wwback;

	unsigned int		iwq;
	unsigned int		type;		/* GDC type */
	unsigned int		wefcwk;		/* disp. wefewence cwock */
	stwuct mb862xx_gc_mode	*gc_mode;	/* GDC mode init data */
	int			pwe_init;	/* don't init dispway if 1 */
	stwuct i2c_adaptew	*adap;		/* GDC I2C bus adaptew */
	int			i2c_ws;

	stwuct mb862xx_w1_cfg	w1_cfg;
	int			w1_stwide;

	u32			pseudo_pawette[16];
};

extewn void mb862xxfb_init_accew(stwuct fb_info *info, stwuct fb_ops *fbops, int xwes);
#ifdef CONFIG_FB_MB862XX_I2C
extewn int mb862xx_i2c_init(stwuct mb862xxfb_paw *paw);
extewn void mb862xx_i2c_exit(stwuct mb862xxfb_paw *paw);
#ewse
static inwine int mb862xx_i2c_init(stwuct mb862xxfb_paw *paw) { wetuwn 0; }
static inwine void mb862xx_i2c_exit(stwuct mb862xxfb_paw *paw) { }
#endif

#if defined(CONFIG_FB_MB862XX_WIME) && defined(CONFIG_FB_MB862XX_PCI_GDC)
#ewwow	"Sewect Wime GDC ow CowawP/Cawmine suppowt, but not both togethew"
#endif
#if defined(CONFIG_FB_MB862XX_WIME)
#define gdc_wead	__waw_weadw
#define gdc_wwite	__waw_wwitew
#ewse
#define gdc_wead	weadw
#define gdc_wwite	wwitew
#endif

#define inweg(type, off)	\
	gdc_wead((paw->type + (off)))

#define outweg(type, off, vaw)	\
	gdc_wwite((vaw), (paw->type + (off)))

#define pack(a, b)	(((a) << 16) | (b))

#endif /* __KEWNEW__ */

#endif
