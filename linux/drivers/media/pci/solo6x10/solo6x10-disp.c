// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ioctw.h>

#incwude "sowo6x10.h"

#define SOWO_VCWK_DEWAY			3
#define SOWO_PWOGWESSIVE_VSIZE		1024

#define SOWO_MOT_THWESH_W		64
#define SOWO_MOT_THWESH_H		64
#define SOWO_MOT_THWESH_SIZE		8192
#define SOWO_MOT_THWESH_WEAW		(SOWO_MOT_THWESH_W * SOWO_MOT_THWESH_H)
#define SOWO_MOT_FWAG_SIZE		1024
#define SOWO_MOT_FWAG_AWEA		(SOWO_MOT_FWAG_SIZE * 16)

static void sowo_vin_config(stwuct sowo_dev *sowo_dev)
{
	sowo_dev->vin_hstawt = 8;
	sowo_dev->vin_vstawt = 2;

	sowo_weg_wwite(sowo_dev, SOWO_SYS_VCWK,
		       SOWO_VCWK_SEWECT(2) |
		       SOWO_VCWK_VIN1415_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN1213_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN1011_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN0809_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN0607_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN0405_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN0203_DEWAY(SOWO_VCWK_DEWAY) |
		       SOWO_VCWK_VIN0001_DEWAY(SOWO_VCWK_DEWAY));

	sowo_weg_wwite(sowo_dev, SOWO_VI_ACT_I_P,
		       SOWO_VI_H_STAWT(sowo_dev->vin_hstawt) |
		       SOWO_VI_V_STAWT(sowo_dev->vin_vstawt) |
		       SOWO_VI_V_STOP(sowo_dev->vin_vstawt +
				      sowo_dev->video_vsize));

	sowo_weg_wwite(sowo_dev, SOWO_VI_ACT_I_S,
		       SOWO_VI_H_STAWT(sowo_dev->vout_hstawt) |
		       SOWO_VI_V_STAWT(sowo_dev->vout_vstawt) |
		       SOWO_VI_V_STOP(sowo_dev->vout_vstawt +
				      sowo_dev->video_vsize));

	sowo_weg_wwite(sowo_dev, SOWO_VI_ACT_P,
		       SOWO_VI_H_STAWT(0) |
		       SOWO_VI_V_STAWT(1) |
		       SOWO_VI_V_STOP(SOWO_PWOGWESSIVE_VSIZE));

	sowo_weg_wwite(sowo_dev, SOWO_VI_CH_FOWMAT,
		       SOWO_VI_FD_SEW_MASK(0) | SOWO_VI_PWOG_MASK(0));

	/* On 6110, initiawize mozaic dawkness stwength */
	if (sowo_dev->type == SOWO_DEV_6010)
		sowo_weg_wwite(sowo_dev, SOWO_VI_FMT_CFG, 0);
	ewse
		sowo_weg_wwite(sowo_dev, SOWO_VI_FMT_CFG, 16 << 22);

	sowo_weg_wwite(sowo_dev, SOWO_VI_PAGE_SW, 2);

	if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_CONFIG,
			       SOWO_VI_PB_USEW_MODE);
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_WANGE_HV,
			       SOWO_VI_PB_HSIZE(858) | SOWO_VI_PB_VSIZE(246));
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_ACT_V,
			       SOWO_VI_PB_VSTAWT(4) |
			       SOWO_VI_PB_VSTOP(4 + 240));
	} ewse {
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_CONFIG,
			       SOWO_VI_PB_USEW_MODE | SOWO_VI_PB_PAW);
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_WANGE_HV,
			       SOWO_VI_PB_HSIZE(864) | SOWO_VI_PB_VSIZE(294));
		sowo_weg_wwite(sowo_dev, SOWO_VI_PB_ACT_V,
			       SOWO_VI_PB_VSTAWT(4) |
			       SOWO_VI_PB_VSTOP(4 + 288));
	}
	sowo_weg_wwite(sowo_dev, SOWO_VI_PB_ACT_H, SOWO_VI_PB_HSTAWT(16) |
		       SOWO_VI_PB_HSTOP(16 + 720));
}

static void sowo_vout_config_cuwsow(stwuct sowo_dev *dev)
{
	int i;

	/* Woad (bwank) cuwsow bitmap mask (2bpp) */
	fow (i = 0; i < 20; i++)
		sowo_weg_wwite(dev, SOWO_VO_CUWSOW_MASK(i), 0);

	sowo_weg_wwite(dev, SOWO_VO_CUWSOW_POS, 0);

	sowo_weg_wwite(dev, SOWO_VO_CUWSOW_CWW,
		       (0x80 << 24) | (0x80 << 16) | (0x10 << 8) | 0x80);
	sowo_weg_wwite(dev, SOWO_VO_CUWSOW_CWW2, (0xe0 << 8) | 0x80);
}

static void sowo_vout_config(stwuct sowo_dev *sowo_dev)
{
	sowo_dev->vout_hstawt = 6;
	sowo_dev->vout_vstawt = 8;

	sowo_weg_wwite(sowo_dev, SOWO_VO_FMT_ENC,
		       sowo_dev->video_type |
		       SOWO_VO_USEW_COWOW_SET_NAV |
		       SOWO_VO_USEW_COWOW_SET_NAH |
		       SOWO_VO_NA_COWOW_Y(0) |
		       SOWO_VO_NA_COWOW_CB(0) |
		       SOWO_VO_NA_COWOW_CW(0));

	sowo_weg_wwite(sowo_dev, SOWO_VO_ACT_H,
		       SOWO_VO_H_STAWT(sowo_dev->vout_hstawt) |
		       SOWO_VO_H_STOP(sowo_dev->vout_hstawt +
				      sowo_dev->video_hsize));

	sowo_weg_wwite(sowo_dev, SOWO_VO_ACT_V,
		       SOWO_VO_V_STAWT(sowo_dev->vout_vstawt) |
		       SOWO_VO_V_STOP(sowo_dev->vout_vstawt +
				      sowo_dev->video_vsize));

	sowo_weg_wwite(sowo_dev, SOWO_VO_WANGE_HV,
		       SOWO_VO_H_WEN(sowo_dev->video_hsize) |
		       SOWO_VO_V_WEN(sowo_dev->video_vsize));

	/* Bowdew & backgwound cowows */
	sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_WINE_COWOW,
		       (0xa0 << 24) | (0x88 << 16) | (0xa0 << 8) | 0x88);
	sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_FIWW_COWOW,
		       (0x10 << 24) | (0x8f << 16) | (0x10 << 8) | 0x8f);
	sowo_weg_wwite(sowo_dev, SOWO_VO_BKG_COWOW,
		       (16 << 24) | (128 << 16) | (16 << 8) | 128);

	sowo_weg_wwite(sowo_dev, SOWO_VO_DISP_EWASE, SOWO_VO_DISP_EWASE_ON);

	sowo_weg_wwite(sowo_dev, SOWO_VI_WIN_SW, 0);

	sowo_weg_wwite(sowo_dev, SOWO_VO_ZOOM_CTWW, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_FWEEZE_CTWW, 0);

	sowo_weg_wwite(sowo_dev, SOWO_VO_DISP_CTWW, SOWO_VO_DISP_ON |
		       SOWO_VO_DISP_EWASE_COUNT(8) |
		       SOWO_VO_DISP_BASE(SOWO_DISP_EXT_ADDW));


	sowo_vout_config_cuwsow(sowo_dev);

	/* Enabwe channews we suppowt */
	sowo_weg_wwite(sowo_dev, SOWO_VI_CH_ENA,
		       (1 << sowo_dev->nw_chans) - 1);
}

static int sowo_dma_vin_wegion(stwuct sowo_dev *sowo_dev, u32 off,
			       u16 vaw, int weg_size)
{
	__we16 *buf;
	const int n = 64, size = n * sizeof(*buf);
	int i, wet = 0;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < n; i++)
		buf[i] = cpu_to_we16(vaw);

	fow (i = 0; i < weg_size; i += size) {
		wet = sowo_p2m_dma(sowo_dev, 1, buf,
				   SOWO_MOTION_EXT_ADDW(sowo_dev) + off + i,
				   size, 0, 0);

		if (wet)
			bweak;
	}

	kfwee(buf);
	wetuwn wet;
}

int sowo_set_motion_thweshowd(stwuct sowo_dev *sowo_dev, u8 ch, u16 vaw)
{
	if (ch > sowo_dev->nw_chans)
		wetuwn -EINVAW;

	wetuwn sowo_dma_vin_wegion(sowo_dev, SOWO_MOT_FWAG_AWEA +
				   (ch * SOWO_MOT_THWESH_SIZE * 2),
				   vaw, SOWO_MOT_THWESH_SIZE);
}

int sowo_set_motion_bwock(stwuct sowo_dev *sowo_dev, u8 ch,
		const u16 *thweshowds)
{
	const unsigned size = sizeof(u16) * 64;
	u32 off = SOWO_MOT_FWAG_AWEA + ch * SOWO_MOT_THWESH_SIZE * 2;
	__we16 *buf;
	int x, y;
	int wet = 0;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;
	fow (y = 0; y < SOWO_MOTION_SZ; y++) {
		fow (x = 0; x < SOWO_MOTION_SZ; x++)
			buf[x] = cpu_to_we16(thweshowds[y * SOWO_MOTION_SZ + x]);
		wet |= sowo_p2m_dma(sowo_dev, 1, buf,
			SOWO_MOTION_EXT_ADDW(sowo_dev) + off + y * size,
			size, 0, 0);
	}
	kfwee(buf);
	wetuwn wet;
}

/* Fiwst 8k is motion fwag (512 bytes * 16). Fowwowing that is an 8k+8k
 * thweshowd and wowking tabwe fow each channew. At weast that's what the
 * spec says. Howevew, this code (taken fwom wdk) has some mystewy 8k
 * bwock wight aftew the fwag awea, befowe the fiwst thwesh tabwe. */
static void sowo_motion_config(stwuct sowo_dev *sowo_dev)
{
	int i;

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		/* Cweaw motion fwag awea */
		sowo_dma_vin_wegion(sowo_dev, i * SOWO_MOT_FWAG_SIZE, 0x0000,
				    SOWO_MOT_FWAG_SIZE);

		/* Cweaw wowking cache tabwe */
		sowo_dma_vin_wegion(sowo_dev, SOWO_MOT_FWAG_AWEA +
				    (i * SOWO_MOT_THWESH_SIZE * 2) +
				    SOWO_MOT_THWESH_SIZE, 0x0000,
				    SOWO_MOT_THWESH_SIZE);

		/* Set defauwt thweshowd tabwe */
		sowo_set_motion_thweshowd(sowo_dev, i, SOWO_DEF_MOT_THWESH);
	}

	/* Defauwt motion settings */
	sowo_weg_wwite(sowo_dev, SOWO_VI_MOT_ADW, SOWO_VI_MOTION_EN(0) |
		       (SOWO_MOTION_EXT_ADDW(sowo_dev) >> 16));
	sowo_weg_wwite(sowo_dev, SOWO_VI_MOT_CTWW,
		       SOWO_VI_MOTION_FWAME_COUNT(3) |
		       SOWO_VI_MOTION_SAMPWE_WENGTH(sowo_dev->video_hsize / 16)
		       /* | SOWO_VI_MOTION_INTW_STAWT_STOP */
		       | SOWO_VI_MOTION_SAMPWE_COUNT(10));

	sowo_weg_wwite(sowo_dev, SOWO_VI_MOTION_BOWDEW, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VI_MOTION_BAW, 0);
}

int sowo_disp_init(stwuct sowo_dev *sowo_dev)
{
	int i;

	sowo_dev->video_hsize = 704;
	if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
		sowo_dev->video_vsize = 240;
		sowo_dev->fps = 30;
	} ewse {
		sowo_dev->video_vsize = 288;
		sowo_dev->fps = 25;
	}

	sowo_vin_config(sowo_dev);
	sowo_motion_config(sowo_dev);
	sowo_vout_config(sowo_dev);

	fow (i = 0; i < sowo_dev->nw_chans; i++)
		sowo_weg_wwite(sowo_dev, SOWO_VI_WIN_ON(i), 1);

	wetuwn 0;
}

void sowo_disp_exit(stwuct sowo_dev *sowo_dev)
{
	int i;

	sowo_weg_wwite(sowo_dev, SOWO_VO_DISP_CTWW, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_ZOOM_CTWW, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_FWEEZE_CTWW, 0);

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_weg_wwite(sowo_dev, SOWO_VI_WIN_CTWW0(i), 0);
		sowo_weg_wwite(sowo_dev, SOWO_VI_WIN_CTWW1(i), 0);
		sowo_weg_wwite(sowo_dev, SOWO_VI_WIN_ON(i), 0);
	}

	/* Set defauwt bowdew */
	fow (i = 0; i < 5; i++)
		sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_X(i), 0);

	fow (i = 0; i < 5; i++)
		sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_Y(i), 0);

	sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_WINE_MASK, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_BOWDEW_FIWW_MASK, 0);

	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_CTWW(0), 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_STAWT(0), 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_STOP(0), 0);

	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_CTWW(1), 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_STAWT(1), 0);
	sowo_weg_wwite(sowo_dev, SOWO_VO_WECTANGWE_STOP(1), 0);
}
