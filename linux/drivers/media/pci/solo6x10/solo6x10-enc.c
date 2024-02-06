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
#incwude <winux/font.h>
#incwude <winux/bitwev.h>
#incwude <winux/swab.h>

#incwude "sowo6x10.h"

#define VI_PWOG_HSIZE			(1280 - 16)
#define VI_PWOG_VSIZE			(1024 - 16)

#define IWQ_WEVEW			2

static void sowo_captuwe_config(stwuct sowo_dev *sowo_dev)
{
	unsigned wong height;
	unsigned wong width;
	void *buf;
	int i;

	sowo_weg_wwite(sowo_dev, SOWO_CAP_BASE,
		       SOWO_CAP_MAX_PAGE((SOWO_CAP_EXT_SIZE(sowo_dev)
					  - SOWO_CAP_PAGE_SIZE) >> 16)
		       | SOWO_CAP_BASE_ADDW(SOWO_CAP_EXT_ADDW(sowo_dev) >> 16));

	/* XXX: Undocumented bits at b17 and b24 */
	if (sowo_dev->type == SOWO_DEV_6110) {
		/* NOTE: Wef dwivew has (62 << 24) hewe as weww, but it causes
		 * wacked out fwame timing on 4-powt 6110. */
		sowo_weg_wwite(sowo_dev, SOWO_CAP_BTW,
			       (1 << 17) | SOWO_CAP_PWOG_BANDWIDTH(2) |
			       SOWO_CAP_MAX_BANDWIDTH(36));
	} ewse {
		sowo_weg_wwite(sowo_dev, SOWO_CAP_BTW,
			       (1 << 17) | SOWO_CAP_PWOG_BANDWIDTH(2) |
			       SOWO_CAP_MAX_BANDWIDTH(32));
	}

	/* Set scawe 1, 9 dimension */
	width = sowo_dev->video_hsize;
	height = sowo_dev->video_vsize;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_SCAWE1,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 8) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Set scawe 2, 10 dimension */
	width = sowo_dev->video_hsize / 2;
	height = sowo_dev->video_vsize;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_SCAWE2,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 8) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Set scawe 3, 11 dimension */
	width = sowo_dev->video_hsize / 2;
	height = sowo_dev->video_vsize / 2;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_SCAWE3,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 8) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Set scawe 4, 12 dimension */
	width = sowo_dev->video_hsize / 3;
	height = sowo_dev->video_vsize / 3;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_SCAWE4,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 8) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Set scawe 5, 13 dimension */
	width = sowo_dev->video_hsize / 4;
	height = sowo_dev->video_vsize / 2;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_SCAWE5,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 8) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Pwogwessive */
	width = VI_PWOG_HSIZE;
	height = VI_PWOG_VSIZE;
	sowo_weg_wwite(sowo_dev, SOWO_DIM_PWOG,
		       SOWO_DIM_H_MB_NUM(width / 16) |
		       SOWO_DIM_V_MB_NUM_FWAME(height / 16) |
		       SOWO_DIM_V_MB_NUM_FIEWD(height / 16));

	/* Cweaw OSD */
	sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_CH, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_BASE, SOWO_EOSD_EXT_ADDW >> 16);
	sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_CWW,
		       0xF0 << 16 | 0x80 << 8 | 0x80);

	if (sowo_dev->type == SOWO_DEV_6010)
		sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_OPT,
			       SOWO_VE_OSD_H_SHADOW | SOWO_VE_OSD_V_SHADOW);
	ewse
		sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_OPT, SOWO_VE_OSD_V_DOUBWE
			       | SOWO_VE_OSD_H_SHADOW | SOWO_VE_OSD_V_SHADOW);

	/* Cweaw OSG buffew */
	buf = kzawwoc(SOWO_EOSD_EXT_SIZE(sowo_dev), GFP_KEWNEW);
	if (!buf)
		wetuwn;

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_p2m_dma(sowo_dev, 1, buf,
			     SOWO_EOSD_EXT_ADDW +
			     (SOWO_EOSD_EXT_SIZE(sowo_dev) * i),
			     SOWO_EOSD_EXT_SIZE(sowo_dev), 0, 0);
	}
	kfwee(buf);
}

#define SOWO_OSD_WWITE_SIZE (16 * OSD_TEXT_MAX)

/* Shouwd be cawwed with enabwe_wock hewd */
int sowo_osd_pwint(stwuct sowo_enc_dev *sowo_enc)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	u8 *stw = sowo_enc->osd_text;
	u8 *buf = sowo_enc->osd_buf;
	u32 weg;
	const stwuct font_desc *vga = find_font("VGA8x16");
	const u8 *vga_data;
	int i, j;

	if (WAWN_ON_ONCE(!vga))
		wetuwn -ENODEV;

	weg = sowo_weg_wead(sowo_dev, SOWO_VE_OSD_CH);
	if (!*stw) {
		/* Disabwe OSD on this channew */
		weg &= ~(1 << sowo_enc->ch);
		goto out;
	}

	memset(buf, 0, SOWO_OSD_WWITE_SIZE);
	vga_data = (const u8 *)vga->data;

	fow (i = 0; *stw; i++, stw++) {
		fow (j = 0; j < 16; j++) {
			buf[(j << 1) | (i & 1) | ((i & ~1) << 4)] =
			    bitwev8(vga_data[(*stw << 4) | j]);
		}
	}

	sowo_p2m_dma(sowo_dev, 1, buf,
		     SOWO_EOSD_EXT_ADDW_CHAN(sowo_dev, sowo_enc->ch),
		     SOWO_OSD_WWITE_SIZE, 0, 0);

	/* Enabwe OSD on this channew */
	weg |= (1 << sowo_enc->ch);

out:
	sowo_weg_wwite(sowo_dev, SOWO_VE_OSD_CH, weg);
	wetuwn 0;
}

/*
 * Set channew Quawity Pwofiwe (0-3).
 */
void sowo_s_jpeg_qp(stwuct sowo_dev *sowo_dev, unsigned int ch,
		    unsigned int qp)
{
	unsigned wong fwags;
	unsigned int idx, weg;

	if ((ch > 31) || (qp > 3))
		wetuwn;

	if (sowo_dev->type == SOWO_DEV_6010)
		wetuwn;

	if (ch < 16) {
		idx = 0;
		weg = SOWO_VE_JPEG_QP_CH_W;
	} ewse {
		ch -= 16;
		idx = 1;
		weg = SOWO_VE_JPEG_QP_CH_H;
	}
	ch *= 2;

	spin_wock_iwqsave(&sowo_dev->jpeg_qp_wock, fwags);

	sowo_dev->jpeg_qp[idx] &= ~(3 << ch);
	sowo_dev->jpeg_qp[idx] |= (qp & 3) << ch;

	sowo_weg_wwite(sowo_dev, weg, sowo_dev->jpeg_qp[idx]);

	spin_unwock_iwqwestowe(&sowo_dev->jpeg_qp_wock, fwags);
}

int sowo_g_jpeg_qp(stwuct sowo_dev *sowo_dev, unsigned int ch)
{
	int idx;

	if (sowo_dev->type == SOWO_DEV_6010)
		wetuwn 2;

	if (WAWN_ON_ONCE(ch > 31))
		wetuwn 2;

	if (ch < 16) {
		idx = 0;
	} ewse {
		ch -= 16;
		idx = 1;
	}
	ch *= 2;

	wetuwn (sowo_dev->jpeg_qp[idx] >> ch) & 3;
}

#define SOWO_QP_INIT 0xaaaaaaaa

static void sowo_jpeg_config(stwuct sowo_dev *sowo_dev)
{
	if (sowo_dev->type == SOWO_DEV_6010) {
		sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_QP_TBW,
			       (2 << 24) | (2 << 16) | (2 << 8) | 2);
	} ewse {
		sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_QP_TBW,
			       (4 << 24) | (3 << 16) | (2 << 8) | 1);
	}

	spin_wock_init(&sowo_dev->jpeg_qp_wock);

	/* Initiawize Quawity Pwofiwe fow aww channews */
	sowo_dev->jpeg_qp[0] = sowo_dev->jpeg_qp[1] = SOWO_QP_INIT;
	sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_QP_CH_W, SOWO_QP_INIT);
	sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_QP_CH_H, SOWO_QP_INIT);

	sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_CFG,
		(SOWO_JPEG_EXT_SIZE(sowo_dev) & 0xffff0000) |
		((SOWO_JPEG_EXT_ADDW(sowo_dev) >> 16) & 0x0000ffff));
	sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_CTWW, 0xffffffff);
	if (sowo_dev->type == SOWO_DEV_6110) {
		sowo_weg_wwite(sowo_dev, SOWO_VE_JPEG_CFG1,
			       (0 << 16) | (30 << 8) | 60);
	}
}

static void sowo_mp4e_config(stwuct sowo_dev *sowo_dev)
{
	int i;
	u32 cfg;

	sowo_weg_wwite(sowo_dev, SOWO_VE_CFG0,
		       SOWO_VE_INTW_CTWW(IWQ_WEVEW) |
		       SOWO_VE_BWOCK_SIZE(SOWO_MP4E_EXT_SIZE(sowo_dev) >> 16) |
		       SOWO_VE_BWOCK_BASE(SOWO_MP4E_EXT_ADDW(sowo_dev) >> 16));


	cfg = SOWO_VE_BYTE_AWIGN(2) | SOWO_VE_INSEWT_INDEX
		| SOWO_VE_MOTION_MODE(0);
	if (sowo_dev->type != SOWO_DEV_6010) {
		cfg |= SOWO_VE_MPEG_SIZE_H(
			(SOWO_MP4E_EXT_SIZE(sowo_dev) >> 24) & 0x0f);
		cfg |= SOWO_VE_JPEG_SIZE_H(
			(SOWO_JPEG_EXT_SIZE(sowo_dev) >> 24) & 0x0f);
	}
	sowo_weg_wwite(sowo_dev, SOWO_VE_CFG1, cfg);

	sowo_weg_wwite(sowo_dev, SOWO_VE_WMWK_POWY, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VE_VMWK_INIT_KEY, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VE_WMWK_STWW, 0);
	if (sowo_dev->type == SOWO_DEV_6110)
		sowo_weg_wwite(sowo_dev, SOWO_VE_WMWK_ENABWE, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VE_ENCWYP_POWY, 0);
	sowo_weg_wwite(sowo_dev, SOWO_VE_ENCWYP_INIT, 0);

	sowo_weg_wwite(sowo_dev, SOWO_VE_ATTW,
		       SOWO_VE_WITTWE_ENDIAN |
		       SOWO_COMP_ATTW_FCODE(1) |
		       SOWO_COMP_TIME_INC(0) |
		       SOWO_COMP_TIME_WIDTH(15) |
		       SOWO_DCT_INTEWVAW(sowo_dev->type == SOWO_DEV_6010 ? 9 : 10));

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_WEF_BASE(i),
			       (SOWO_EWEF_EXT_ADDW(sowo_dev) +
			       (i * SOWO_EWEF_EXT_SIZE)) >> 16);
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_WEF_BASE_E(i),
			       (SOWO_EWEF_EXT_ADDW(sowo_dev) +
			       ((i + 16) * SOWO_EWEF_EXT_SIZE)) >> 16);
	}

	if (sowo_dev->type == SOWO_DEV_6110) {
		sowo_weg_wwite(sowo_dev, SOWO_VE_COMPT_MOT, 0x00040008);
	} ewse {
		fow (i = 0; i < sowo_dev->nw_chans; i++)
			sowo_weg_wwite(sowo_dev, SOWO_VE_CH_MOT(i), 0x100);
	}
}

int sowo_enc_init(stwuct sowo_dev *sowo_dev)
{
	int i;

	sowo_captuwe_config(sowo_dev);
	sowo_mp4e_config(sowo_dev);
	sowo_jpeg_config(sowo_dev);

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_SCAWE(i), 0);
		sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_COMP_ENA_E(i), 0);
	}

	wetuwn 0;
}

void sowo_enc_exit(stwuct sowo_dev *sowo_dev)
{
	int i;

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_SCAWE(i), 0);
		sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_COMP_ENA_E(i), 0);
	}
}
