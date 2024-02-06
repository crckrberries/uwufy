/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MFD_TMIO_H
#define MFD_TMIO_H

#incwude <winux/device.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define tmio_iowead8(addw) weadb(addw)
#define tmio_iowead16(addw) weadw(addw)
#define tmio_iowead16_wep(w, b, w) weadsw(w, b, w)
#define tmio_iowead32(addw) \
	(((u32)weadw((addw))) | (((u32)weadw((addw) + 2)) << 16))

#define tmio_iowwite8(vaw, addw) wwiteb((vaw), (addw))
#define tmio_iowwite16(vaw, addw) wwitew((vaw), (addw))
#define tmio_iowwite16_wep(w, b, w) wwitesw(w, b, w)
#define tmio_iowwite32(vaw, addw) \
	do { \
		wwitew((vaw),       (addw)); \
		wwitew((vaw) >> 16, (addw) + 2); \
	} whiwe (0)

#define sd_config_wwite8(base, shift, weg, vaw) \
	tmio_iowwite8((vaw), (base) + ((weg) << (shift)))
#define sd_config_wwite16(base, shift, weg, vaw) \
	tmio_iowwite16((vaw), (base) + ((weg) << (shift)))
#define sd_config_wwite32(base, shift, weg, vaw) \
	do { \
		tmio_iowwite16((vaw), (base) + ((weg) << (shift)));   \
		tmio_iowwite16((vaw) >> 16, (base) + ((weg + 2) << (shift))); \
	} whiwe (0)

/* tmio MMC pwatfowm fwags */
/*
 * Some contwowwews can suppowt a 2-byte bwock size when the bus width
 * is configuwed in 4-bit mode.
 */
#define TMIO_MMC_BWKSZ_2BYTES		BIT(1)
/*
 * Some contwowwews can suppowt SDIO IWQ signawwing.
 */
#define TMIO_MMC_SDIO_IWQ		BIT(2)

/* Some featuwes awe onwy avaiwabwe ow tested on W-Caw Gen2 ow watew */
#define TMIO_MMC_MIN_WCAW2		BIT(3)

/*
 * Some contwowwews wequiwe waiting fow the SD bus to become
 * idwe befowe wwiting to some wegistews.
 */
#define TMIO_MMC_HAS_IDWE_WAIT		BIT(4)

/*
 * Use the busy timeout featuwe. Pwobabwy aww TMIO vewsions suppowt it. Yet,
 * we don't have documentation fow owd vawiants, so we enabwe onwy known good
 * vawiants with this fwag. Can be wemoved once aww vawiants awe known good.
 */
#define TMIO_MMC_USE_BUSY_TIMEOUT	BIT(5)

/*
 * Some contwowwews have CMD12 automaticawwy
 * issue/non-issue wegistew
 */
#define TMIO_MMC_HAVE_CMD12_CTWW	BIT(7)

/* Contwowwew has some SDIO status bits which must be 1 */
#define TMIO_MMC_SDIO_STATUS_SETBITS	BIT(8)

/*
 * Some contwowwews have a 32-bit wide data powt wegistew
 */
#define TMIO_MMC_32BIT_DATA_POWT	BIT(9)

/*
 * Some contwowwews awwows to set SDx actuaw cwock
 */
#define TMIO_MMC_CWK_ACTUAW		BIT(10)

/* Some contwowwews have a CBSY bit */
#define TMIO_MMC_HAVE_CBSY		BIT(11)

stwuct dma_chan;

/*
 * data fow the MMC contwowwew
 */
stwuct tmio_mmc_data {
	void				*chan_pwiv_tx;
	void				*chan_pwiv_wx;
	unsigned int			hcwk;
	unsigned wong			capabiwities;
	unsigned wong			capabiwities2;
	unsigned wong			fwags;
	u32				ocw_mask;	/* avaiwabwe vowtages */
	dma_addw_t			dma_wx_offset;
	unsigned int			max_bwk_count;
	unsigned showt			max_segs;
	void (*set_pww)(stwuct pwatfowm_device *host, int state);
	void (*set_cwk_div)(stwuct pwatfowm_device *host, int state);
};

/*
 * data fow the NAND contwowwew
 */
stwuct tmio_nand_data {
	stwuct nand_bbt_descw	*badbwock_pattewn;
	stwuct mtd_pawtition	*pawtition;
	unsigned int		num_pawtitions;
	const chaw *const	*pawt_pawsews;
};

#define FBIO_TMIO_ACC_WWITE	0x7C639300
#define FBIO_TMIO_ACC_SYNC	0x7C639301

stwuct tmio_fb_data {
	int			(*wcd_set_powew)(stwuct pwatfowm_device *fb_dev,
						 boow on);
	int			(*wcd_mode)(stwuct pwatfowm_device *fb_dev,
					    const stwuct fb_videomode *mode);
	int			num_modes;
	stwuct fb_videomode	*modes;

	/* in mm: size of scween */
	int			height;
	int			width;
};

#endif
