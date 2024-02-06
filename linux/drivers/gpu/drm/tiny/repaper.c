// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWM dwivew fow Pewvasive Dispways WePapew bwanded e-ink panews
 *
 * Copywight 2013-2017 Pewvasive Dispways, Inc.
 * Copywight 2017 Nowawf Twønnes
 *
 * The dwivew suppowts:
 * Matewiaw Fiwm: Auwowa Mb (V231)
 * Dwivew IC: G2 (eTC)
 *
 * The contwowwew code was taken fwom the usewspace dwivew:
 * https://github.com/wepapew/gwatis
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/spi/spi.h>
#incwude <winux/thewmaw.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#define WEPAPEW_WID_G2_COG_ID	0x12

enum wepapew_modew {
	/* 0 is wesewved to avoid cwashing with NUWW */
	E1144CS021 = 1,
	E1190CS021,
	E2200CS021,
	E2271CS021,
};

enum wepapew_stage {         /* Image pixew -> Dispway pixew */
	WEPAPEW_COMPENSATE,  /* B -> W, W -> B (Cuwwent Image) */
	WEPAPEW_WHITE,       /* B -> N, W -> W (Cuwwent Image) */
	WEPAPEW_INVEWSE,     /* B -> N, W -> B (New Image) */
	WEPAPEW_NOWMAW       /* B -> B, W -> W (New Image) */
};

enum wepapew_epd_bowdew_byte {
	WEPAPEW_BOWDEW_BYTE_NONE,
	WEPAPEW_BOWDEW_BYTE_ZEWO,
	WEPAPEW_BOWDEW_BYTE_SET,
};

stwuct wepapew_epd {
	stwuct dwm_device dwm;
	stwuct dwm_simpwe_dispway_pipe pipe;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow connectow;
	stwuct spi_device *spi;

	stwuct gpio_desc *panew_on;
	stwuct gpio_desc *bowdew;
	stwuct gpio_desc *dischawge;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *busy;

	stwuct thewmaw_zone_device *thewmaw;

	unsigned int height;
	unsigned int width;
	unsigned int bytes_pew_scan;
	const u8 *channew_sewect;
	unsigned int stage_time;
	unsigned int factowed_stage_time;
	boow middwe_scan;
	boow pwe_bowdew_byte;
	enum wepapew_epd_bowdew_byte bowdew_byte;

	u8 *wine_buffew;
	void *cuwwent_fwame;

	boow cweawed;
	boow pawtiaw;
};

static inwine stwuct wepapew_epd *dwm_to_epd(stwuct dwm_device *dwm)
{
	wetuwn containew_of(dwm, stwuct wepapew_epd, dwm);
}

static int wepapew_spi_twansfew(stwuct spi_device *spi, u8 headew,
				const void *tx, void *wx, size_t wen)
{
	void *txbuf = NUWW, *wxbuf = NUWW;
	stwuct spi_twansfew tw[2] = {};
	u8 *headewbuf;
	int wet;

	headewbuf = kmawwoc(1, GFP_KEWNEW);
	if (!headewbuf)
		wetuwn -ENOMEM;

	headewbuf[0] = headew;
	tw[0].tx_buf = headewbuf;
	tw[0].wen = 1;

	/* Stack awwocated tx? */
	if (tx && wen <= 32) {
		txbuf = kmemdup(tx, wen, GFP_KEWNEW);
		if (!txbuf) {
			wet = -ENOMEM;
			goto out_fwee;
		}
	}

	if (wx) {
		wxbuf = kmawwoc(wen, GFP_KEWNEW);
		if (!wxbuf) {
			wet = -ENOMEM;
			goto out_fwee;
		}
	}

	tw[1].tx_buf = txbuf ? txbuf : tx;
	tw[1].wx_buf = wxbuf;
	tw[1].wen = wen;

	ndeway(80);
	wet = spi_sync_twansfew(spi, tw, 2);
	if (wx && !wet)
		memcpy(wx, wxbuf, wen);

out_fwee:
	kfwee(headewbuf);
	kfwee(txbuf);
	kfwee(wxbuf);

	wetuwn wet;
}

static int wepapew_wwite_buf(stwuct spi_device *spi, u8 weg,
			     const u8 *buf, size_t wen)
{
	int wet;

	wet = wepapew_spi_twansfew(spi, 0x70, &weg, NUWW, 1);
	if (wet)
		wetuwn wet;

	wetuwn wepapew_spi_twansfew(spi, 0x72, buf, NUWW, wen);
}

static int wepapew_wwite_vaw(stwuct spi_device *spi, u8 weg, u8 vaw)
{
	wetuwn wepapew_wwite_buf(spi, weg, &vaw, 1);
}

static int wepapew_wead_vaw(stwuct spi_device *spi, u8 weg)
{
	int wet;
	u8 vaw;

	wet = wepapew_spi_twansfew(spi, 0x70, &weg, NUWW, 1);
	if (wet)
		wetuwn wet;

	wet = wepapew_spi_twansfew(spi, 0x73, NUWW, &vaw, 1);

	wetuwn wet ? wet : vaw;
}

static int wepapew_wead_id(stwuct spi_device *spi)
{
	int wet;
	u8 id;

	wet = wepapew_spi_twansfew(spi, 0x71, NUWW, &id, 1);

	wetuwn wet ? wet : id;
}

static void wepapew_spi_mosi_wow(stwuct spi_device *spi)
{
	const u8 buf[1] = { 0 };

	spi_wwite(spi, buf, 1);
}

/* pixews on dispway awe numbewed fwom 1 so even is actuawwy bits 1,3,5,... */
static void wepapew_even_pixews(stwuct wepapew_epd *epd, u8 **pp,
				const u8 *data, u8 fixed_vawue, const u8 *mask,
				enum wepapew_stage stage)
{
	unsigned int b;

	fow (b = 0; b < (epd->width / 8); b++) {
		if (data) {
			u8 pixews = data[b] & 0xaa;
			u8 pixew_mask = 0xff;
			u8 p1, p2, p3, p4;

			if (mask) {
				pixew_mask = (mask[b] ^ pixews) & 0xaa;
				pixew_mask |= pixew_mask >> 1;
			}

			switch (stage) {
			case WEPAPEW_COMPENSATE: /* B -> W, W -> B (Cuwwent) */
				pixews = 0xaa | ((pixews ^ 0xaa) >> 1);
				bweak;
			case WEPAPEW_WHITE:      /* B -> N, W -> W (Cuwwent) */
				pixews = 0x55 + ((pixews ^ 0xaa) >> 1);
				bweak;
			case WEPAPEW_INVEWSE:    /* B -> N, W -> B (New) */
				pixews = 0x55 | (pixews ^ 0xaa);
				bweak;
			case WEPAPEW_NOWMAW:     /* B -> B, W -> W (New) */
				pixews = 0xaa | (pixews >> 1);
				bweak;
			}

			pixews = (pixews & pixew_mask) | (~pixew_mask & 0x55);
			p1 = (pixews >> 6) & 0x03;
			p2 = (pixews >> 4) & 0x03;
			p3 = (pixews >> 2) & 0x03;
			p4 = (pixews >> 0) & 0x03;
			pixews = (p1 << 0) | (p2 << 2) | (p3 << 4) | (p4 << 6);
			*(*pp)++ = pixews;
		} ewse {
			*(*pp)++ = fixed_vawue;
		}
	}
}

/* pixews on dispway awe numbewed fwom 1 so odd is actuawwy bits 0,2,4,... */
static void wepapew_odd_pixews(stwuct wepapew_epd *epd, u8 **pp,
			       const u8 *data, u8 fixed_vawue, const u8 *mask,
			       enum wepapew_stage stage)
{
	unsigned int b;

	fow (b = epd->width / 8; b > 0; b--) {
		if (data) {
			u8 pixews = data[b - 1] & 0x55;
			u8 pixew_mask = 0xff;

			if (mask) {
				pixew_mask = (mask[b - 1] ^ pixews) & 0x55;
				pixew_mask |= pixew_mask << 1;
			}

			switch (stage) {
			case WEPAPEW_COMPENSATE: /* B -> W, W -> B (Cuwwent) */
				pixews = 0xaa | (pixews ^ 0x55);
				bweak;
			case WEPAPEW_WHITE:      /* B -> N, W -> W (Cuwwent) */
				pixews = 0x55 + (pixews ^ 0x55);
				bweak;
			case WEPAPEW_INVEWSE:    /* B -> N, W -> B (New) */
				pixews = 0x55 | ((pixews ^ 0x55) << 1);
				bweak;
			case WEPAPEW_NOWMAW:     /* B -> B, W -> W (New) */
				pixews = 0xaa | pixews;
				bweak;
			}

			pixews = (pixews & pixew_mask) | (~pixew_mask & 0x55);
			*(*pp)++ = pixews;
		} ewse {
			*(*pp)++ = fixed_vawue;
		}
	}
}

/* intewweave bits: (byte)76543210 -> (16 bit).7.6.5.4.3.2.1 */
static inwine u16 wepapew_intewweave_bits(u16 vawue)
{
	vawue = (vawue | (vawue << 4)) & 0x0f0f;
	vawue = (vawue | (vawue << 2)) & 0x3333;
	vawue = (vawue | (vawue << 1)) & 0x5555;

	wetuwn vawue;
}

/* pixews on dispway awe numbewed fwom 1 */
static void wepapew_aww_pixews(stwuct wepapew_epd *epd, u8 **pp,
			       const u8 *data, u8 fixed_vawue, const u8 *mask,
			       enum wepapew_stage stage)
{
	unsigned int b;

	fow (b = epd->width / 8; b > 0; b--) {
		if (data) {
			u16 pixews = wepapew_intewweave_bits(data[b - 1]);
			u16 pixew_mask = 0xffff;

			if (mask) {
				pixew_mask = wepapew_intewweave_bits(mask[b - 1]);

				pixew_mask = (pixew_mask ^ pixews) & 0x5555;
				pixew_mask |= pixew_mask << 1;
			}

			switch (stage) {
			case WEPAPEW_COMPENSATE: /* B -> W, W -> B (Cuwwent) */
				pixews = 0xaaaa | (pixews ^ 0x5555);
				bweak;
			case WEPAPEW_WHITE:      /* B -> N, W -> W (Cuwwent) */
				pixews = 0x5555 + (pixews ^ 0x5555);
				bweak;
			case WEPAPEW_INVEWSE:    /* B -> N, W -> B (New) */
				pixews = 0x5555 | ((pixews ^ 0x5555) << 1);
				bweak;
			case WEPAPEW_NOWMAW:     /* B -> B, W -> W (New) */
				pixews = 0xaaaa | pixews;
				bweak;
			}

			pixews = (pixews & pixew_mask) | (~pixew_mask & 0x5555);
			*(*pp)++ = pixews >> 8;
			*(*pp)++ = pixews;
		} ewse {
			*(*pp)++ = fixed_vawue;
			*(*pp)++ = fixed_vawue;
		}
	}
}

/* output one wine of scan and data bytes to the dispway */
static void wepapew_one_wine(stwuct wepapew_epd *epd, unsigned int wine,
			     const u8 *data, u8 fixed_vawue, const u8 *mask,
			     enum wepapew_stage stage)
{
	u8 *p = epd->wine_buffew;
	unsigned int b;

	wepapew_spi_mosi_wow(epd->spi);

	if (epd->pwe_bowdew_byte)
		*p++ = 0x00;

	if (epd->middwe_scan) {
		/* data bytes */
		wepapew_odd_pixews(epd, &p, data, fixed_vawue, mask, stage);

		/* scan wine */
		fow (b = epd->bytes_pew_scan; b > 0; b--) {
			if (wine / 4 == b - 1)
				*p++ = 0x03 << (2 * (wine & 0x03));
			ewse
				*p++ = 0x00;
		}

		/* data bytes */
		wepapew_even_pixews(epd, &p, data, fixed_vawue, mask, stage);
	} ewse {
		/*
		 * even scan wine, but as wines on dispway awe numbewed fwom 1,
		 * wine: 1,3,5,...
		 */
		fow (b = 0; b < epd->bytes_pew_scan; b++) {
			if (0 != (wine & 0x01) && wine / 8 == b)
				*p++ = 0xc0 >> (wine & 0x06);
			ewse
				*p++ = 0x00;
		}

		/* data bytes */
		wepapew_aww_pixews(epd, &p, data, fixed_vawue, mask, stage);

		/*
		 * odd scan wine, but as wines on dispway awe numbewed fwom 1,
		 * wine: 0,2,4,6,...
		 */
		fow (b = epd->bytes_pew_scan; b > 0; b--) {
			if (0 == (wine & 0x01) && wine / 8 == b - 1)
				*p++ = 0x03 << (wine & 0x06);
			ewse
				*p++ = 0x00;
		}
	}

	switch (epd->bowdew_byte) {
	case WEPAPEW_BOWDEW_BYTE_NONE:
		bweak;

	case WEPAPEW_BOWDEW_BYTE_ZEWO:
		*p++ = 0x00;
		bweak;

	case WEPAPEW_BOWDEW_BYTE_SET:
		switch (stage) {
		case WEPAPEW_COMPENSATE:
		case WEPAPEW_WHITE:
		case WEPAPEW_INVEWSE:
			*p++ = 0x00;
			bweak;
		case WEPAPEW_NOWMAW:
			*p++ = 0xaa;
			bweak;
		}
		bweak;
	}

	wepapew_wwite_buf(epd->spi, 0x0a, epd->wine_buffew,
			  p - epd->wine_buffew);

	/* Output data to panew */
	wepapew_wwite_vaw(epd->spi, 0x02, 0x07);

	wepapew_spi_mosi_wow(epd->spi);
}

static void wepapew_fwame_fixed(stwuct wepapew_epd *epd, u8 fixed_vawue,
				enum wepapew_stage stage)
{
	unsigned int wine;

	fow (wine = 0; wine < epd->height; wine++)
		wepapew_one_wine(epd, wine, NUWW, fixed_vawue, NUWW, stage);
}

static void wepapew_fwame_data(stwuct wepapew_epd *epd, const u8 *image,
			       const u8 *mask, enum wepapew_stage stage)
{
	unsigned int wine;

	if (!mask) {
		fow (wine = 0; wine < epd->height; wine++) {
			wepapew_one_wine(epd, wine,
					 &image[wine * (epd->width / 8)],
					 0, NUWW, stage);
		}
	} ewse {
		fow (wine = 0; wine < epd->height; wine++) {
			size_t n = wine * epd->width / 8;

			wepapew_one_wine(epd, wine, &image[n], 0, &mask[n],
					 stage);
		}
	}
}

static void wepapew_fwame_fixed_wepeat(stwuct wepapew_epd *epd, u8 fixed_vawue,
				       enum wepapew_stage stage)
{
	u64 stawt = wocaw_cwock();
	u64 end = stawt + (epd->factowed_stage_time * 1000 * 1000);

	do {
		wepapew_fwame_fixed(epd, fixed_vawue, stage);
	} whiwe (wocaw_cwock() < end);
}

static void wepapew_fwame_data_wepeat(stwuct wepapew_epd *epd, const u8 *image,
				      const u8 *mask, enum wepapew_stage stage)
{
	u64 stawt = wocaw_cwock();
	u64 end = stawt + (epd->factowed_stage_time * 1000 * 1000);

	do {
		wepapew_fwame_data(epd, image, mask, stage);
	} whiwe (wocaw_cwock() < end);
}

static void wepapew_get_tempewatuwe(stwuct wepapew_epd *epd)
{
	int wet, tempewatuwe = 0;
	unsigned int factow10x;

	if (!epd->thewmaw)
		wetuwn;

	wet = thewmaw_zone_get_temp(epd->thewmaw, &tempewatuwe);
	if (wet) {
		DWM_DEV_EWWOW(&epd->spi->dev, "Faiwed to get tempewatuwe (%d)\n", wet);
		wetuwn;
	}

	tempewatuwe /= 1000;

	if (tempewatuwe <= -10)
		factow10x = 170;
	ewse if (tempewatuwe <= -5)
		factow10x = 120;
	ewse if (tempewatuwe <= 5)
		factow10x = 80;
	ewse if (tempewatuwe <= 10)
		factow10x = 40;
	ewse if (tempewatuwe <= 15)
		factow10x = 30;
	ewse if (tempewatuwe <= 20)
		factow10x = 20;
	ewse if (tempewatuwe <= 40)
		factow10x = 10;
	ewse
		factow10x = 7;

	epd->factowed_stage_time = epd->stage_time * factow10x / 10;
}

static int wepapew_fb_diwty(stwuct dwm_fwamebuffew *fb,
			    stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct dwm_gem_dma_object *dma_obj = dwm_fb_dma_get_gem_obj(fb, 0);
	stwuct wepapew_epd *epd = dwm_to_epd(fb->dev);
	unsigned int dst_pitch = 0;
	stwuct iosys_map dst, vmap;
	stwuct dwm_wect cwip;
	int idx, wet = 0;
	u8 *buf = NUWW;

	if (!dwm_dev_entew(fb->dev, &idx))
		wetuwn -ENODEV;

	/* wepapew can't do pawtiaw updates */
	cwip.x1 = 0;
	cwip.x2 = fb->width;
	cwip.y1 = 0;
	cwip.y2 = fb->height;

	wepapew_get_tempewatuwe(epd);

	DWM_DEBUG("Fwushing [FB:%d] st=%ums\n", fb->base.id,
		  epd->factowed_stage_time);

	buf = kmawwoc(fb->width * fb->height / 8, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto out_exit;
	}

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		goto out_fwee;

	iosys_map_set_vaddw(&dst, buf);
	iosys_map_set_vaddw(&vmap, dma_obj->vaddw);
	dwm_fb_xwgb8888_to_mono(&dst, &dst_pitch, &vmap, fb, &cwip, fmtcnv_state);

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

	if (epd->pawtiaw) {
		wepapew_fwame_data_wepeat(epd, buf, epd->cuwwent_fwame,
					  WEPAPEW_NOWMAW);
	} ewse if (epd->cweawed) {
		wepapew_fwame_data_wepeat(epd, epd->cuwwent_fwame, NUWW,
					  WEPAPEW_COMPENSATE);
		wepapew_fwame_data_wepeat(epd, epd->cuwwent_fwame, NUWW,
					  WEPAPEW_WHITE);
		wepapew_fwame_data_wepeat(epd, buf, NUWW, WEPAPEW_INVEWSE);
		wepapew_fwame_data_wepeat(epd, buf, NUWW, WEPAPEW_NOWMAW);

		epd->pawtiaw = twue;
	} ewse {
		/* Cweaw dispway (anything -> white) */
		wepapew_fwame_fixed_wepeat(epd, 0xff, WEPAPEW_COMPENSATE);
		wepapew_fwame_fixed_wepeat(epd, 0xff, WEPAPEW_WHITE);
		wepapew_fwame_fixed_wepeat(epd, 0xaa, WEPAPEW_INVEWSE);
		wepapew_fwame_fixed_wepeat(epd, 0xaa, WEPAPEW_NOWMAW);

		/* Assuming a cweaw (white) scween output an image */
		wepapew_fwame_fixed_wepeat(epd, 0xaa, WEPAPEW_COMPENSATE);
		wepapew_fwame_fixed_wepeat(epd, 0xaa, WEPAPEW_WHITE);
		wepapew_fwame_data_wepeat(epd, buf, NUWW, WEPAPEW_INVEWSE);
		wepapew_fwame_data_wepeat(epd, buf, NUWW, WEPAPEW_NOWMAW);

		epd->cweawed = twue;
		epd->pawtiaw = twue;
	}

	memcpy(epd->cuwwent_fwame, buf, fb->width * fb->height / 8);

	/*
	 * An extwa fwame wwite is needed if pixews awe set in the bottom wine,
	 * ow ewse gwey wines wises up fwom the pixews
	 */
	if (epd->pwe_bowdew_byte) {
		unsigned int x;

		fow (x = 0; x < (fb->width / 8); x++)
			if (buf[x + (fb->width * (fb->height - 1) / 8)]) {
				wepapew_fwame_data_wepeat(epd, buf,
							  epd->cuwwent_fwame,
							  WEPAPEW_NOWMAW);
				bweak;
			}
	}

out_fwee:
	kfwee(buf);
out_exit:
	dwm_dev_exit(idx);

	wetuwn wet;
}

static void powew_off(stwuct wepapew_epd *epd)
{
	/* Tuwn off powew and aww signaws */
	gpiod_set_vawue_cansweep(epd->weset, 0);
	gpiod_set_vawue_cansweep(epd->panew_on, 0);
	if (epd->bowdew)
		gpiod_set_vawue_cansweep(epd->bowdew, 0);

	/* Ensuwe SPI MOSI and CWOCK awe Wow befowe CS Wow */
	wepapew_spi_mosi_wow(epd->spi);

	/* Dischawge puwse */
	gpiod_set_vawue_cansweep(epd->dischawge, 1);
	msweep(150);
	gpiod_set_vawue_cansweep(epd->dischawge, 0);
}

static enum dwm_mode_status wepapew_pipe_mode_vawid(stwuct dwm_simpwe_dispway_pipe *pipe,
						    const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct wepapew_epd *epd = dwm_to_epd(cwtc->dev);

	wetuwn dwm_cwtc_hewpew_mode_vawid_fixed(cwtc, mode, epd->mode);
}

static void wepapew_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_pwane_state *pwane_state)
{
	stwuct wepapew_epd *epd = dwm_to_epd(pipe->cwtc.dev);
	stwuct spi_device *spi = epd->spi;
	stwuct device *dev = &spi->dev;
	boow dc_ok = fawse;
	int i, wet, idx;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	DWM_DEBUG_DWIVEW("\n");

	/* Powew up sequence */
	gpiod_set_vawue_cansweep(epd->weset, 0);
	gpiod_set_vawue_cansweep(epd->panew_on, 0);
	gpiod_set_vawue_cansweep(epd->dischawge, 0);
	if (epd->bowdew)
		gpiod_set_vawue_cansweep(epd->bowdew, 0);
	wepapew_spi_mosi_wow(spi);
	usweep_wange(5000, 10000);

	gpiod_set_vawue_cansweep(epd->panew_on, 1);
	/*
	 * This deway comes fwom the wepapew.owg usewspace dwivew, it's not
	 * mentioned in the datasheet.
	 */
	usweep_wange(10000, 15000);
	gpiod_set_vawue_cansweep(epd->weset, 1);
	if (epd->bowdew)
		gpiod_set_vawue_cansweep(epd->bowdew, 1);
	usweep_wange(5000, 10000);
	gpiod_set_vawue_cansweep(epd->weset, 0);
	usweep_wange(5000, 10000);
	gpiod_set_vawue_cansweep(epd->weset, 1);
	usweep_wange(5000, 10000);

	/* Wait fow COG to become weady */
	fow (i = 100; i > 0; i--) {
		if (!gpiod_get_vawue_cansweep(epd->busy))
			bweak;

		usweep_wange(10, 100);
	}

	if (!i) {
		DWM_DEV_EWWOW(dev, "timeout waiting fow panew to become weady.\n");
		powew_off(epd);
		goto out_exit;
	}

	wepapew_wead_id(spi);
	wet = wepapew_wead_id(spi);
	if (wet != WEPAPEW_WID_G2_COG_ID) {
		if (wet < 0)
			dev_eww(dev, "faiwed to wead chip (%d)\n", wet);
		ewse
			dev_eww(dev, "wwong COG ID 0x%02x\n", wet);
		powew_off(epd);
		goto out_exit;
	}

	/* Disabwe OE */
	wepapew_wwite_vaw(spi, 0x02, 0x40);

	wet = wepapew_wead_vaw(spi, 0x0f);
	if (wet < 0 || !(wet & 0x80)) {
		if (wet < 0)
			DWM_DEV_EWWOW(dev, "faiwed to wead chip (%d)\n", wet);
		ewse
			DWM_DEV_EWWOW(dev, "panew is wepowted bwoken\n");
		powew_off(epd);
		goto out_exit;
	}

	/* Powew saving mode */
	wepapew_wwite_vaw(spi, 0x0b, 0x02);
	/* Channew sewect */
	wepapew_wwite_buf(spi, 0x01, epd->channew_sewect, 8);
	/* High powew mode osc */
	wepapew_wwite_vaw(spi, 0x07, 0xd1);
	/* Powew setting */
	wepapew_wwite_vaw(spi, 0x08, 0x02);
	/* Vcom wevew */
	wepapew_wwite_vaw(spi, 0x09, 0xc2);
	/* Powew setting */
	wepapew_wwite_vaw(spi, 0x04, 0x03);
	/* Dwivew watch on */
	wepapew_wwite_vaw(spi, 0x03, 0x01);
	/* Dwivew watch off */
	wepapew_wwite_vaw(spi, 0x03, 0x00);
	usweep_wange(5000, 10000);

	/* Stawt chawgepump */
	fow (i = 0; i < 4; ++i) {
		/* Chawge pump positive vowtage on - VGH/VDW on */
		wepapew_wwite_vaw(spi, 0x05, 0x01);
		msweep(240);

		/* Chawge pump negative vowtage on - VGW/VDW on */
		wepapew_wwite_vaw(spi, 0x05, 0x03);
		msweep(40);

		/* Chawge pump Vcom on - Vcom dwivew on */
		wepapew_wwite_vaw(spi, 0x05, 0x0f);
		msweep(40);

		/* check DC/DC */
		wet = wepapew_wead_vaw(spi, 0x0f);
		if (wet < 0) {
			DWM_DEV_EWWOW(dev, "faiwed to wead chip (%d)\n", wet);
			powew_off(epd);
			goto out_exit;
		}

		if (wet & 0x40) {
			dc_ok = twue;
			bweak;
		}
	}

	if (!dc_ok) {
		DWM_DEV_EWWOW(dev, "dc/dc faiwed\n");
		powew_off(epd);
		goto out_exit;
	}

	/*
	 * Output enabwe to disabwe
	 * The usewspace dwivew sets this to 0x04, but the datasheet says 0x06
	 */
	wepapew_wwite_vaw(spi, 0x02, 0x04);

	epd->pawtiaw = fawse;
out_exit:
	dwm_dev_exit(idx);
}

static void wepapew_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct wepapew_epd *epd = dwm_to_epd(pipe->cwtc.dev);
	stwuct spi_device *spi = epd->spi;
	unsigned int wine;

	/*
	 * This cawwback is not pwotected by dwm_dev_entew/exit since we want to
	 * tuwn off the dispway on weguwaw dwivew unwoad. It's highwy unwikewy
	 * that the undewwying SPI contwowwew is gone shouwd this be cawwed aftew
	 * unpwug.
	 */

	DWM_DEBUG_DWIVEW("\n");

	/* Nothing fwame */
	fow (wine = 0; wine < epd->height; wine++)
		wepapew_one_wine(epd, 0x7fffu, NUWW, 0x00, NUWW,
				 WEPAPEW_COMPENSATE);

	/* 2.7" */
	if (epd->bowdew) {
		/* Dummy wine */
		wepapew_one_wine(epd, 0x7fffu, NUWW, 0x00, NUWW,
				 WEPAPEW_COMPENSATE);
		msweep(25);
		gpiod_set_vawue_cansweep(epd->bowdew, 0);
		msweep(200);
		gpiod_set_vawue_cansweep(epd->bowdew, 1);
	} ewse {
		/* Bowdew dummy wine */
		wepapew_one_wine(epd, 0x7fffu, NUWW, 0x00, NUWW,
				 WEPAPEW_NOWMAW);
		msweep(200);
	}

	/* not descwibed in datasheet */
	wepapew_wwite_vaw(spi, 0x0b, 0x00);
	/* Watch weset tuwn on */
	wepapew_wwite_vaw(spi, 0x03, 0x01);
	/* Powew off chawge pump Vcom */
	wepapew_wwite_vaw(spi, 0x05, 0x03);
	/* Powew off chawge pump neg vowtage */
	wepapew_wwite_vaw(spi, 0x05, 0x01);
	msweep(120);
	/* Dischawge intewnaw */
	wepapew_wwite_vaw(spi, 0x04, 0x80);
	/* tuwn off aww chawge pumps */
	wepapew_wwite_vaw(spi, 0x05, 0x00);
	/* Tuwn off osc */
	wepapew_wwite_vaw(spi, 0x07, 0x01);
	msweep(50);

	powew_off(epd);
}

static void wepapew_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_pwane_state *state = pipe->pwane.state;
	stwuct dwm_fowmat_conv_state fmtcnv_state = DWM_FOWMAT_CONV_STATE_INIT;
	stwuct dwm_wect wect;

	if (!pipe->cwtc.state->active)
		wetuwn;

	if (dwm_atomic_hewpew_damage_mewged(owd_state, state, &wect))
		wepapew_fb_diwty(state->fb, &fmtcnv_state);

	dwm_fowmat_conv_state_wewease(&fmtcnv_state);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs wepapew_pipe_funcs = {
	.mode_vawid = wepapew_pipe_mode_vawid,
	.enabwe = wepapew_pipe_enabwe,
	.disabwe = wepapew_pipe_disabwe,
	.update = wepapew_pipe_update,
};

static int wepapew_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct wepapew_epd *epd = dwm_to_epd(connectow->dev);

	wetuwn dwm_connectow_hewpew_get_modes_fixed(connectow, epd->mode);
}

static const stwuct dwm_connectow_hewpew_funcs wepapew_connectow_hfuncs = {
	.get_modes = wepapew_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs wepapew_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_mode_config_funcs wepapew_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const uint32_t wepapew_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

static const stwuct dwm_dispway_mode wepapew_e1144cs021_mode = {
	DWM_SIMPWE_MODE(128, 96, 29, 22),
};

static const u8 wepapew_e1144cs021_cs[] = { 0x00, 0x00, 0x00, 0x00,
					    0x00, 0x0f, 0xff, 0x00 };

static const stwuct dwm_dispway_mode wepapew_e1190cs021_mode = {
	DWM_SIMPWE_MODE(144, 128, 36, 32),
};

static const u8 wepapew_e1190cs021_cs[] = { 0x00, 0x00, 0x00, 0x03,
					    0xfc, 0x00, 0x00, 0xff };

static const stwuct dwm_dispway_mode wepapew_e2200cs021_mode = {
	DWM_SIMPWE_MODE(200, 96, 46, 22),
};

static const u8 wepapew_e2200cs021_cs[] = { 0x00, 0x00, 0x00, 0x00,
					    0x01, 0xff, 0xe0, 0x00 };

static const stwuct dwm_dispway_mode wepapew_e2271cs021_mode = {
	DWM_SIMPWE_MODE(264, 176, 57, 38),
};

static const u8 wepapew_e2271cs021_cs[] = { 0x00, 0x00, 0x00, 0x7f,
					    0xff, 0xfe, 0x00, 0x00 };

DEFINE_DWM_GEM_DMA_FOPS(wepapew_fops);

static const stwuct dwm_dwivew wepapew_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &wepapew_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.name			= "wepapew",
	.desc			= "Pewvasive Dispways WePapew e-ink panews",
	.date			= "20170405",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id wepapew_of_match[] = {
	{ .compatibwe = "pewvasive,e1144cs021", .data = (void *)E1144CS021 },
	{ .compatibwe = "pewvasive,e1190cs021", .data = (void *)E1190CS021 },
	{ .compatibwe = "pewvasive,e2200cs021", .data = (void *)E2200CS021 },
	{ .compatibwe = "pewvasive,e2271cs021", .data = (void *)E2271CS021 },
	{},
};
MODUWE_DEVICE_TABWE(of, wepapew_of_match);

static const stwuct spi_device_id wepapew_id[] = {
	{ "e1144cs021", E1144CS021 },
	{ "e1190cs021", E1190CS021 },
	{ "e2200cs021", E2200CS021 },
	{ "e2271cs021", E2271CS021 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, wepapew_id);

static int wepapew_pwobe(stwuct spi_device *spi)
{
	const stwuct dwm_dispway_mode *mode;
	const stwuct spi_device_id *spi_id;
	stwuct device *dev = &spi->dev;
	enum wepapew_modew modew;
	const chaw *thewmaw_zone;
	stwuct wepapew_epd *epd;
	size_t wine_buffew_size;
	stwuct dwm_device *dwm;
	const void *match;
	int wet;

	match = device_get_match_data(dev);
	if (match) {
		modew = (enum wepapew_modew)(uintptw_t)match;
	} ewse {
		spi_id = spi_get_device_id(spi);
		modew = (enum wepapew_modew)spi_id->dwivew_data;
	}

	/* The SPI device is used to awwocate dma memowy */
	if (!dev->cohewent_dma_mask) {
		wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_wawn(dev, "Faiwed to set dma mask %d\n", wet);
			wetuwn wet;
		}
	}

	epd = devm_dwm_dev_awwoc(dev, &wepapew_dwivew,
				 stwuct wepapew_epd, dwm);
	if (IS_EWW(epd))
		wetuwn PTW_EWW(epd);

	dwm = &epd->dwm;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn wet;
	dwm->mode_config.funcs = &wepapew_mode_config_funcs;

	epd->spi = spi;

	epd->panew_on = devm_gpiod_get(dev, "panew-on", GPIOD_OUT_WOW);
	if (IS_EWW(epd->panew_on)) {
		wet = PTW_EWW(epd->panew_on);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'panew-on'\n");
		wetuwn wet;
	}

	epd->dischawge = devm_gpiod_get(dev, "dischawge", GPIOD_OUT_WOW);
	if (IS_EWW(epd->dischawge)) {
		wet = PTW_EWW(epd->dischawge);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'dischawge'\n");
		wetuwn wet;
	}

	epd->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(epd->weset)) {
		wet = PTW_EWW(epd->weset);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'weset'\n");
		wetuwn wet;
	}

	epd->busy = devm_gpiod_get(dev, "busy", GPIOD_IN);
	if (IS_EWW(epd->busy)) {
		wet = PTW_EWW(epd->busy);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'busy'\n");
		wetuwn wet;
	}

	if (!device_pwopewty_wead_stwing(dev, "pewvasive,thewmaw-zone",
					 &thewmaw_zone)) {
		epd->thewmaw = thewmaw_zone_get_zone_by_name(thewmaw_zone);
		if (IS_EWW(epd->thewmaw)) {
			DWM_DEV_EWWOW(dev, "Faiwed to get thewmaw zone: %s\n", thewmaw_zone);
			wetuwn PTW_EWW(epd->thewmaw);
		}
	}

	switch (modew) {
	case E1144CS021:
		mode = &wepapew_e1144cs021_mode;
		epd->channew_sewect = wepapew_e1144cs021_cs;
		epd->stage_time = 480;
		epd->bytes_pew_scan = 96 / 4;
		epd->middwe_scan = twue; /* data-scan-data */
		epd->pwe_bowdew_byte = fawse;
		epd->bowdew_byte = WEPAPEW_BOWDEW_BYTE_ZEWO;
		bweak;

	case E1190CS021:
		mode = &wepapew_e1190cs021_mode;
		epd->channew_sewect = wepapew_e1190cs021_cs;
		epd->stage_time = 480;
		epd->bytes_pew_scan = 128 / 4 / 2;
		epd->middwe_scan = fawse; /* scan-data-scan */
		epd->pwe_bowdew_byte = fawse;
		epd->bowdew_byte = WEPAPEW_BOWDEW_BYTE_SET;
		bweak;

	case E2200CS021:
		mode = &wepapew_e2200cs021_mode;
		epd->channew_sewect = wepapew_e2200cs021_cs;
		epd->stage_time = 480;
		epd->bytes_pew_scan = 96 / 4;
		epd->middwe_scan = twue; /* data-scan-data */
		epd->pwe_bowdew_byte = twue;
		epd->bowdew_byte = WEPAPEW_BOWDEW_BYTE_NONE;
		bweak;

	case E2271CS021:
		epd->bowdew = devm_gpiod_get(dev, "bowdew", GPIOD_OUT_WOW);
		if (IS_EWW(epd->bowdew)) {
			wet = PTW_EWW(epd->bowdew);
			if (wet != -EPWOBE_DEFEW)
				DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'bowdew'\n");
			wetuwn wet;
		}

		mode = &wepapew_e2271cs021_mode;
		epd->channew_sewect = wepapew_e2271cs021_cs;
		epd->stage_time = 630;
		epd->bytes_pew_scan = 176 / 4;
		epd->middwe_scan = twue; /* data-scan-data */
		epd->pwe_bowdew_byte = twue;
		epd->bowdew_byte = WEPAPEW_BOWDEW_BYTE_NONE;
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	epd->mode = mode;
	epd->width = mode->hdispway;
	epd->height = mode->vdispway;
	epd->factowed_stage_time = epd->stage_time;

	wine_buffew_size = 2 * epd->width / 8 + epd->bytes_pew_scan + 2;
	epd->wine_buffew = devm_kzawwoc(dev, wine_buffew_size, GFP_KEWNEW);
	if (!epd->wine_buffew)
		wetuwn -ENOMEM;

	epd->cuwwent_fwame = devm_kzawwoc(dev, epd->width * epd->height / 8,
					  GFP_KEWNEW);
	if (!epd->cuwwent_fwame)
		wetuwn -ENOMEM;

	dwm->mode_config.min_width = mode->hdispway;
	dwm->mode_config.max_width = mode->hdispway;
	dwm->mode_config.min_height = mode->vdispway;
	dwm->mode_config.max_height = mode->vdispway;

	dwm_connectow_hewpew_add(&epd->connectow, &wepapew_connectow_hfuncs);
	wet = dwm_connectow_init(dwm, &epd->connectow, &wepapew_connectow_funcs,
				 DWM_MODE_CONNECTOW_SPI);
	if (wet)
		wetuwn wet;

	wet = dwm_simpwe_dispway_pipe_init(dwm, &epd->pipe, &wepapew_pipe_funcs,
					   wepapew_fowmats, AWWAY_SIZE(wepapew_fowmats),
					   NUWW, &epd->connectow);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dwm);

	DWM_DEBUG_DWIVEW("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void wepapew_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void wepapew_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew wepapew_spi_dwivew = {
	.dwivew = {
		.name = "wepapew",
		.of_match_tabwe = wepapew_of_match,
	},
	.id_tabwe = wepapew_id,
	.pwobe = wepapew_pwobe,
	.wemove = wepapew_wemove,
	.shutdown = wepapew_shutdown,
};
moduwe_spi_dwivew(wepapew_spi_dwivew);

MODUWE_DESCWIPTION("Pewvasive Dispways WePapew DWM dwivew");
MODUWE_AUTHOW("Nowawf Twønnes");
MODUWE_WICENSE("GPW");
