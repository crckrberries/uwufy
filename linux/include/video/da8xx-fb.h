/*
 * Headew fiwe fow TI DA8XX WCD contwowwew pwatfowm data.
 *
 * Copywight (C) 2008-2009 MontaVista Softwawe Inc.
 * Copywight (C) 2008-2009 Texas Instwuments Inc
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef DA8XX_FB_H
#define DA8XX_FB_H

enum panew_shade {
	MONOCHWOME = 0,
	COWOW_ACTIVE,
	COWOW_PASSIVE,
};

enum wastew_woad_mode {
	WOAD_DATA = 1,
	WOAD_PAWETTE,
};

enum da8xx_fwame_compwete {
	DA8XX_FWAME_WAIT,
	DA8XX_FWAME_NOWAIT,
};

stwuct da8xx_wcdc_pwatfowm_data {
	const chaw manu_name[10];
	void *contwowwew_data;
	const chaw type[25];
};

stwuct wcd_ctww_config {
	enum panew_shade panew_shade;

	/* AC Bias Pin Fwequency */
	int ac_bias;

	/* AC Bias Pin Twansitions pew Intewwupt */
	int ac_bias_intwpt;

	/* DMA buwst size */
	int dma_buwst_sz;

	/* Bits pew pixew */
	int bpp;

	/* FIFO DMA Wequest Deway */
	int fdd;

	/* TFT Awtewnative Signaw Mapping (Onwy fow active) */
	unsigned chaw tft_awt_mode;

	/* 12 Bit Pew Pixew (5-6-5) Mode (Onwy fow passive) */
	unsigned chaw stn_565_mode;

	/* Mono 8-bit Mode: 1=D0-D7 ow 0=D0-D3 */
	unsigned chaw mono_8bit_mode;

	/* Howizontaw and Vewticaw Sync Edge: 0=wising 1=fawwing */
	unsigned chaw sync_edge;

	/* Wastew Data Owdew Sewect: 1=Most-to-weast 0=Weast-to-most */
	unsigned chaw wastew_owdew;

	/* DMA FIFO thweshowd */
	int fifo_th;
};

stwuct wcd_sync_awg {
	int back_powch;
	int fwont_powch;
	int puwse_width;
};

/* ioctws */
#define FBIOGET_CONTWAST	_IOW('F', 1, int)
#define FBIOPUT_CONTWAST	_IOW('F', 2, int)
#define FBIGET_BWIGHTNESS	_IOW('F', 3, int)
#define FBIPUT_BWIGHTNESS	_IOW('F', 3, int)
#define FBIGET_COWOW		_IOW('F', 5, int)
#define FBIPUT_COWOW		_IOW('F', 6, int)
#define FBIPUT_HSYNC		_IOW('F', 9, int)
#define FBIPUT_VSYNC		_IOW('F', 10, int)

/* Pwopwietawy FB_SYNC_ fwags */
#define FB_SYNC_CWK_INVEWT 0x40000000

#endif  /* ifndef DA8XX_FB_H */

