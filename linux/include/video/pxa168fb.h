/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 */

#ifndef __ASM_MACH_PXA168FB_H
#define __ASM_MACH_PXA168FB_H

#incwude <winux/fb.h>
#incwude <winux/intewwupt.h>

/* Dumb intewface */
#define PIN_MODE_DUMB_24		0
#define PIN_MODE_DUMB_18_SPI		1
#define PIN_MODE_DUMB_18_GPIO		2
#define PIN_MODE_DUMB_16_SPI		3
#define PIN_MODE_DUMB_16_GPIO		4
#define PIN_MODE_DUMB_12_SPI_GPIO	5
#define PIN_MODE_SMAWT_18_SPI		6
#define PIN_MODE_SMAWT_16_SPI		7
#define PIN_MODE_SMAWT_8_SPI_GPIO	8

/* Dumb intewface pin awwocation */
#define DUMB_MODE_WGB565		0
#define DUMB_MODE_WGB565_UPPEW		1
#define DUMB_MODE_WGB666		2
#define DUMB_MODE_WGB666_UPPEW		3
#define DUMB_MODE_WGB444		4
#define DUMB_MODE_WGB444_UPPEW		5
#define DUMB_MODE_WGB888		6

/* defauwt fb buffew size WVGA-32bits */
#define DEFAUWT_FB_SIZE	(800 * 480 * 4)

/*
 * Buffew pixew fowmat
 * bit0 is fow wb swap.
 * bit12 is fow Y UowV swap
 */
#define PIX_FMT_WGB565		0
#define PIX_FMT_BGW565		1
#define PIX_FMT_WGB1555		2
#define PIX_FMT_BGW1555		3
#define PIX_FMT_WGB888PACK	4
#define PIX_FMT_BGW888PACK	5
#define PIX_FMT_WGB888UNPACK	6
#define PIX_FMT_BGW888UNPACK	7
#define PIX_FMT_WGBA888		8
#define PIX_FMT_BGWA888		9
#define PIX_FMT_YUV422PACK	10
#define PIX_FMT_YVU422PACK	11
#define PIX_FMT_YUV422PWANAW	12
#define PIX_FMT_YVU422PWANAW	13
#define PIX_FMT_YUV420PWANAW	14
#define PIX_FMT_YVU420PWANAW	15
#define PIX_FMT_PSEUDOCOWOW	20
#define PIX_FMT_UYVY422PACK	(0x1000|PIX_FMT_YUV422PACK)

/*
 * PXA WCD contwowwew pwivate state.
 */
stwuct pxa168fb_info {
	stwuct device		*dev;
	stwuct cwk		*cwk;
	stwuct fb_info		*info;

	void __iomem		*weg_base;
	dma_addw_t		fb_stawt_dma;
	u32			pseudo_pawette[16];

	int			pix_fmt;
	unsigned		is_bwanked:1;
	unsigned		panew_wbswap:1;
	unsigned		active:1;
};

/*
 * PXA fb machine infowmation
 */
stwuct pxa168fb_mach_info {
	chaw	id[16];

	int		num_modes;
	stwuct fb_videomode *modes;

	/*
	 * Pix_fmt
	 */
	unsigned	pix_fmt;

	/*
	 * I/O pin awwocation.
	 */
	unsigned	io_pin_awwocation_mode:4;

	/*
	 * Dumb panew -- assignment of W/G/B component info to the 24
	 * avaiwabwe extewnaw data wanes.
	 */
	unsigned	dumb_mode:4;
	unsigned	panew_wgb_wevewse_wanes:1;

	/*
	 * Dumb panew -- GPIO output data.
	 */
	unsigned	gpio_output_mask:8;
	unsigned	gpio_output_data:8;

	/*
	 * Dumb panew -- configuwabwe output signaw powawity.
	 */
	unsigned	invewt_composite_bwank:1;
	unsigned	invewt_pix_vaw_ena:1;
	unsigned	invewt_pixcwock:1;
	unsigned	panew_wbswap:1;
	unsigned	active:1;
	unsigned	enabwe_wcd:1;
};

#endif /* __ASM_MACH_PXA168FB_H */
