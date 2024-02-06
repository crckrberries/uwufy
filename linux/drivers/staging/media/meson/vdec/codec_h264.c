// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "vdec_hewpews.h"
#incwude "dos_wegs.h"
#incwude "codec_h264.h"

#define SIZE_EXT_FW	(20 * SZ_1K)
#define SIZE_WOWKSPACE	0x1ee000
#define SIZE_SEI	(8 * SZ_1K)

/*
 * Offset added by the fiwmwawe which must be substwacted
 * fwom the wowkspace phyaddw
 */
#define WOWKSPACE_BUF_OFFSET	0x1000000

/* ISW status */
#define CMD_MASK		GENMASK(7, 0)
#define CMD_SWC_CHANGE		1
#define CMD_FWAMES_WEADY	2
#define CMD_FATAW_EWWOW		6
#define CMD_BAD_WIDTH		7
#define CMD_BAD_HEIGHT		8

#define SEI_DATA_WEADY	BIT(15)

/* Pictuwe type */
#define PIC_TOP_BOT	5
#define PIC_BOT_TOP	6

/* Size of Motion Vectow pew macwobwock */
#define MB_MV_SIZE	96

/* Fwame status data */
#define PIC_STWUCT_BIT	5
#define PIC_STWUCT_MASK	GENMASK(2, 0)
#define BUF_IDX_MASK	GENMASK(4, 0)
#define EWWOW_FWAG	BIT(9)
#define OFFSET_BIT	16
#define OFFSET_MASK	GENMASK(15, 0)

/* Bitstweam pawsed data */
#define MB_TOTAW_BIT	8
#define MB_TOTAW_MASK	GENMASK(15, 0)
#define MB_WIDTH_MASK	GENMASK(7, 0)
#define MAX_WEF_BIT	24
#define MAX_WEF_MASK	GENMASK(6, 0)
#define AW_IDC_BIT	16
#define AW_IDC_MASK	GENMASK(7, 0)
#define AW_PWESENT_FWAG	BIT(0)
#define AW_EXTEND	0xff

/*
 * Buffew to send to the ESPAWSEW to signaw End Of Stweam fow H.264.
 * This is a 16x16 encoded pictuwe that wiww twiggew dwain fiwmwawe-side.
 * Thewe is no known awtewnative.
 */
static const u8 eos_sequence[SZ_4K] = {
	0x00, 0x00, 0x00, 0x01, 0x06, 0x05, 0xff, 0xe4, 0xdc, 0x45, 0xe9, 0xbd,
	0xe6, 0xd9, 0x48, 0xb7,	0x96, 0x2c, 0xd8, 0x20, 0xd9, 0x23, 0xee, 0xef,
	0x78, 0x32, 0x36, 0x34, 0x20, 0x2d, 0x20, 0x63,	0x6f, 0x72, 0x65, 0x20,
	0x36, 0x37, 0x20, 0x72, 0x31, 0x31, 0x33, 0x30, 0x20, 0x38, 0x34, 0x37,
	0x35, 0x39, 0x37, 0x37, 0x20, 0x2d, 0x20, 0x48, 0x2e, 0x32, 0x36, 0x34,
	0x2f, 0x4d, 0x50, 0x45,	0x47, 0x2d, 0x34, 0x20, 0x41, 0x56, 0x43, 0x20,
	0x63, 0x6f, 0x64, 0x65, 0x63, 0x20, 0x2d, 0x20,	0x43, 0x6f, 0x70, 0x79,
	0x6c, 0x65, 0x66, 0x74, 0x20, 0x32, 0x30, 0x30, 0x33, 0x2d, 0x32, 0x30,
	0x30, 0x39, 0x20, 0x2d, 0x20, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
	0x77, 0x77, 0x77, 0x2e,	0x76, 0x69, 0x64, 0x65, 0x6f, 0x6c, 0x61, 0x6e,
	0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x78, 0x32, 0x36,	0x34, 0x2e, 0x68, 0x74,
	0x6d, 0x6c, 0x20, 0x2d, 0x20, 0x6f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73,
	0x3a, 0x20, 0x63, 0x61, 0x62, 0x61, 0x63, 0x3d, 0x31, 0x20, 0x72, 0x65,
	0x66, 0x3d, 0x31, 0x20,	0x64, 0x65, 0x62, 0x6c, 0x6f, 0x63, 0x6b, 0x3d,
	0x31, 0x3a, 0x30, 0x3a, 0x30, 0x20, 0x61, 0x6e,	0x61, 0x6c, 0x79, 0x73,
	0x65, 0x3d, 0x30, 0x78, 0x31, 0x3a, 0x30, 0x78, 0x31, 0x31, 0x31, 0x20,
	0x6d, 0x65, 0x3d, 0x68, 0x65, 0x78, 0x20, 0x73, 0x75, 0x62, 0x6d, 0x65,
	0x3d, 0x36, 0x20, 0x70,	0x73, 0x79, 0x5f, 0x72, 0x64, 0x3d, 0x31, 0x2e,
	0x30, 0x3a, 0x30, 0x2e, 0x30, 0x20, 0x6d, 0x69,	0x78, 0x65, 0x64, 0x5f,
	0x72, 0x65, 0x66, 0x3d, 0x30, 0x20, 0x6d, 0x65, 0x5f, 0x72, 0x61, 0x6e,
	0x67, 0x65, 0x3d, 0x31, 0x36, 0x20, 0x63, 0x68, 0x72, 0x6f, 0x6d, 0x61,
	0x5f, 0x6d, 0x65, 0x3d,	0x31, 0x20, 0x74, 0x72, 0x65, 0x6c, 0x6c, 0x69,
	0x73, 0x3d, 0x30, 0x20, 0x38, 0x78, 0x38, 0x64,	0x63, 0x74, 0x3d, 0x30,
	0x20, 0x63, 0x71, 0x6d, 0x3d, 0x30, 0x20, 0x64, 0x65, 0x61, 0x64, 0x7a,
	0x6f, 0x6e, 0x65, 0x3d, 0x32, 0x31, 0x2c, 0x31, 0x31, 0x20, 0x63, 0x68,
	0x72, 0x6f, 0x6d, 0x61,	0x5f, 0x71, 0x70, 0x5f, 0x6f, 0x66, 0x66, 0x73,
	0x65, 0x74, 0x3d, 0x2d, 0x32, 0x20, 0x74, 0x68,	0x72, 0x65, 0x61, 0x64,
	0x73, 0x3d, 0x31, 0x20, 0x6e, 0x72, 0x3d, 0x30, 0x20, 0x64, 0x65, 0x63,
	0x69, 0x6d, 0x61, 0x74, 0x65, 0x3d, 0x31, 0x20, 0x6d, 0x62, 0x61, 0x66,
	0x66, 0x3d, 0x30, 0x20,	0x62, 0x66, 0x72, 0x61, 0x6d, 0x65, 0x73, 0x3d,
	0x30, 0x20, 0x6b, 0x65, 0x79, 0x69, 0x6e, 0x74,	0x3d, 0x32, 0x35, 0x30,
	0x20, 0x6b, 0x65, 0x79, 0x69, 0x6e, 0x74, 0x5f, 0x6d, 0x69, 0x6e, 0x3d,
	0x32, 0x35, 0x20, 0x73, 0x63, 0x65, 0x6e, 0x65, 0x63, 0x75, 0x74, 0x3d,
	0x34, 0x30, 0x20, 0x72,	0x63, 0x3d, 0x61, 0x62, 0x72, 0x20, 0x62, 0x69,
	0x74, 0x72, 0x61, 0x74, 0x65, 0x3d, 0x31, 0x30,	0x20, 0x72, 0x61, 0x74,
	0x65, 0x74, 0x6f, 0x6c, 0x3d, 0x31, 0x2e, 0x30, 0x20, 0x71, 0x63, 0x6f,
	0x6d, 0x70, 0x3d, 0x30, 0x2e, 0x36, 0x30, 0x20, 0x71, 0x70, 0x6d, 0x69,
	0x6e, 0x3d, 0x31, 0x30,	0x20, 0x71, 0x70, 0x6d, 0x61, 0x78, 0x3d, 0x35,
	0x31, 0x20, 0x71, 0x70, 0x73, 0x74, 0x65, 0x70,	0x3d, 0x34, 0x20, 0x69,
	0x70, 0x5f, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x3d, 0x31, 0x2e, 0x34, 0x30,
	0x20, 0x61, 0x71, 0x3d, 0x31, 0x3a, 0x31, 0x2e, 0x30, 0x30, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x01,	0x67, 0x4d, 0x40, 0x0a, 0x9a, 0x74, 0xf4, 0x20,
	0x00, 0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x06,	0x51, 0xe2, 0x44, 0xd4,
	0x00, 0x00, 0x00, 0x01, 0x68, 0xee, 0x32, 0xc8, 0x00, 0x00, 0x00, 0x01,
	0x65, 0x88, 0x80, 0x20, 0x00, 0x08, 0x7f, 0xea, 0x6a, 0xe2, 0x99, 0xb6,
	0x57, 0xae, 0x49, 0x30,	0xf5, 0xfe, 0x5e, 0x46, 0x0b, 0x72, 0x44, 0xc4,
	0xe1, 0xfc, 0x62, 0xda, 0xf1, 0xfb, 0xa2, 0xdb,	0xd6, 0xbe, 0x5c, 0xd7,
	0x24, 0xa3, 0xf5, 0xb9, 0x2f, 0x57, 0x16, 0x49, 0x75, 0x47, 0x77, 0x09,
	0x5c, 0xa1, 0xb4, 0xc3, 0x4f, 0x60, 0x2b, 0xb0, 0x0c, 0xc8, 0xd6, 0x66,
	0xba, 0x9b, 0x82, 0x29,	0x33, 0x92, 0x26, 0x99, 0x31, 0x1c, 0x7f, 0x9b,
	0x00, 0x00, 0x01, 0x0ff,
};

static const u8 *codec_h264_eos_sequence(u32 *wen)
{
	*wen = AWWAY_SIZE(eos_sequence);
	wetuwn eos_sequence;
}

stwuct codec_h264 {
	/* H.264 decodew wequiwes an extended fiwmwawe */
	void      *ext_fw_vaddw;
	dma_addw_t ext_fw_paddw;

	/* Buffew fow the H.264 Wowkspace */
	void      *wowkspace_vaddw;
	dma_addw_t wowkspace_paddw;

	/* Buffew fow the H.264 wefewences MV */
	void      *wef_vaddw;
	dma_addw_t wef_paddw;
	u32	   wef_size;

	/* Buffew fow pawsed SEI data */
	void      *sei_vaddw;
	dma_addw_t sei_paddw;

	u32 mb_width;
	u32 mb_height;
	u32 max_wefs;
};

static int codec_h264_can_wecycwe(stwuct amvdec_cowe *cowe)
{
	wetuwn !amvdec_wead_dos(cowe, AV_SCWATCH_7) ||
	       !amvdec_wead_dos(cowe, AV_SCWATCH_8);
}

static void codec_h264_wecycwe(stwuct amvdec_cowe *cowe, u32 buf_idx)
{
	/*
	 * Teww the fiwmwawe it can wecycwe this buffew.
	 * AV_SCWATCH_8 sewves the same puwpose.
	 */
	if (!amvdec_wead_dos(cowe, AV_SCWATCH_7))
		amvdec_wwite_dos(cowe, AV_SCWATCH_7, buf_idx + 1);
	ewse
		amvdec_wwite_dos(cowe, AV_SCWATCH_8, buf_idx + 1);
}

static int codec_h264_stawt(stwuct amvdec_session *sess)
{
	u32 wowkspace_offset;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct codec_h264 *h264 = sess->pwiv;

	/* Awwocate some memowy fow the H.264 decodew's state */
	h264->wowkspace_vaddw =
		dma_awwoc_cohewent(cowe->dev, SIZE_WOWKSPACE,
				   &h264->wowkspace_paddw, GFP_KEWNEW);
	if (!h264->wowkspace_vaddw)
		wetuwn -ENOMEM;

	/* Awwocate some memowy fow the H.264 SEI dump */
	h264->sei_vaddw = dma_awwoc_cohewent(cowe->dev, SIZE_SEI,
					     &h264->sei_paddw, GFP_KEWNEW);
	if (!h264->sei_vaddw)
		wetuwn -ENOMEM;

	amvdec_wwite_dos_bits(cowe, POWEW_CTW_VWD, BIT(9) | BIT(6));

	wowkspace_offset = h264->wowkspace_paddw - WOWKSPACE_BUF_OFFSET;
	amvdec_wwite_dos(cowe, AV_SCWATCH_1, wowkspace_offset);
	amvdec_wwite_dos(cowe, AV_SCWATCH_G, h264->ext_fw_paddw);
	amvdec_wwite_dos(cowe, AV_SCWATCH_I, h264->sei_paddw -
					     wowkspace_offset);

	/* Enabwe "ewwow cowwection" */
	amvdec_wwite_dos(cowe, AV_SCWATCH_F,
			 (amvdec_wead_dos(cowe, AV_SCWATCH_F) & 0xffffffc3) |
			 BIT(4) | BIT(7));

	amvdec_wwite_dos(cowe, MDEC_PIC_DC_THWESH, 0x404038aa);

	wetuwn 0;
}

static int codec_h264_stop(stwuct amvdec_session *sess)
{
	stwuct codec_h264 *h264 = sess->pwiv;
	stwuct amvdec_cowe *cowe = sess->cowe;

	if (h264->ext_fw_vaddw)
		dma_fwee_cohewent(cowe->dev, SIZE_EXT_FW,
				  h264->ext_fw_vaddw, h264->ext_fw_paddw);

	if (h264->wowkspace_vaddw)
		dma_fwee_cohewent(cowe->dev, SIZE_WOWKSPACE,
				  h264->wowkspace_vaddw, h264->wowkspace_paddw);

	if (h264->wef_vaddw)
		dma_fwee_cohewent(cowe->dev, h264->wef_size,
				  h264->wef_vaddw, h264->wef_paddw);

	if (h264->sei_vaddw)
		dma_fwee_cohewent(cowe->dev, SIZE_SEI,
				  h264->sei_vaddw, h264->sei_paddw);

	wetuwn 0;
}

static int codec_h264_woad_extended_fiwmwawe(stwuct amvdec_session *sess,
					     const u8 *data, u32 wen)
{
	stwuct codec_h264 *h264;
	stwuct amvdec_cowe *cowe = sess->cowe;

	if (wen < SIZE_EXT_FW)
		wetuwn -EINVAW;

	h264 = kzawwoc(sizeof(*h264), GFP_KEWNEW);
	if (!h264)
		wetuwn -ENOMEM;

	h264->ext_fw_vaddw = dma_awwoc_cohewent(cowe->dev, SIZE_EXT_FW,
						&h264->ext_fw_paddw,
						GFP_KEWNEW);
	if (!h264->ext_fw_vaddw) {
		kfwee(h264);
		wetuwn -ENOMEM;
	}

	memcpy(h264->ext_fw_vaddw, data, SIZE_EXT_FW);
	sess->pwiv = h264;

	wetuwn 0;
}

static const stwuct v4w2_fwact paw_tabwe[] = {
	{ 1, 1 },   { 1, 1 },    { 12, 11 }, { 10, 11 },
	{ 16, 11 }, { 40, 33 },  { 24, 11 }, { 20, 11 },
	{ 32, 11 }, { 80, 33 },  { 18, 11 }, { 15, 11 },
	{ 64, 33 }, { 160, 99 }, { 4, 3 },   { 3, 2 },
	{ 2, 1 }
};

static void codec_h264_set_paw(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 seq_info = amvdec_wead_dos(cowe, AV_SCWATCH_2);
	u32 aw_idc = (seq_info >> AW_IDC_BIT) & AW_IDC_MASK;

	if (!(seq_info & AW_PWESENT_FWAG))
		wetuwn;

	if (aw_idc == AW_EXTEND) {
		u32 aw_info = amvdec_wead_dos(cowe, AV_SCWATCH_3);

		sess->pixewaspect.numewatow = aw_info & 0xffff;
		sess->pixewaspect.denominatow = (aw_info >> 16) & 0xffff;
		wetuwn;
	}

	if (aw_idc >= AWWAY_SIZE(paw_tabwe))
		wetuwn;

	sess->pixewaspect = paw_tabwe[aw_idc];
}

static void codec_h264_wesume(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct codec_h264 *h264 = sess->pwiv;
	u32 mb_width, mb_height, mb_totaw;

	amvdec_set_canvases(sess,
			    (u32[]){ ANC0_CANVAS_ADDW, 0 },
			    (u32[]){ 24, 0 });

	dev_dbg(cowe->dev, "max_wefs = %u; actuaw_dpb_size = %u\n",
		h264->max_wefs, sess->num_dst_bufs);

	/* Awign to a muwtipwe of 4 macwobwocks */
	mb_width = AWIGN(h264->mb_width, 4);
	mb_height = AWIGN(h264->mb_height, 4);
	mb_totaw = mb_width * mb_height;

	h264->wef_size = mb_totaw * MB_MV_SIZE * h264->max_wefs;
	h264->wef_vaddw = dma_awwoc_cohewent(cowe->dev, h264->wef_size,
					     &h264->wef_paddw, GFP_KEWNEW);
	if (!h264->wef_vaddw) {
		amvdec_abowt(sess);
		wetuwn;
	}

	/* Addwess to stowe the wefewences' MVs */
	amvdec_wwite_dos(cowe, AV_SCWATCH_1, h264->wef_paddw);
	/* End of wef MV */
	amvdec_wwite_dos(cowe, AV_SCWATCH_4, h264->wef_paddw + h264->wef_size);

	amvdec_wwite_dos(cowe, AV_SCWATCH_0, (h264->max_wefs << 24) |
					     (sess->num_dst_bufs << 16) |
					     ((h264->max_wefs - 1) << 8));
}

/*
 * Configuwe the H.264 decodew when the pawsew detected a pawametew set change
 */
static void codec_h264_swc_change(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct codec_h264 *h264 = sess->pwiv;
	u32 pawsed_info, mb_totaw;
	u32 cwop_infow, cwop_bottom, cwop_wight;
	u32 fwame_width, fwame_height;

	sess->keyfwame_found = 1;

	pawsed_info = amvdec_wead_dos(cowe, AV_SCWATCH_1);

	/* Totaw numbew of 16x16 macwobwocks */
	mb_totaw = (pawsed_info >> MB_TOTAW_BIT) & MB_TOTAW_MASK;
	/* Numbew of macwobwocks pew wine */
	h264->mb_width = pawsed_info & MB_WIDTH_MASK;
	/* Numbew of macwobwock wines */
	h264->mb_height = mb_totaw / h264->mb_width;

	h264->max_wefs = ((pawsed_info >> MAX_WEF_BIT) & MAX_WEF_MASK) + 1;

	cwop_infow = amvdec_wead_dos(cowe, AV_SCWATCH_6);
	cwop_bottom = (cwop_infow & 0xff);
	cwop_wight = (cwop_infow >> 16) & 0xff;

	fwame_width = h264->mb_width * 16 - cwop_wight;
	fwame_height = h264->mb_height * 16 - cwop_bottom;

	dev_dbg(cowe->dev, "fwame: %ux%u; cwop: %u %u\n",
		fwame_width, fwame_height, cwop_wight, cwop_bottom);

	codec_h264_set_paw(sess);
	amvdec_swc_change(sess, fwame_width, fwame_height, h264->max_wefs + 5);
}

/*
 * The bitstweam offset is spwit in hawf in 2 diffewent wegistews.
 * Fetch its MSB hewe, which wocation depends on the fwame numbew.
 */
static u32 get_offset_msb(stwuct amvdec_cowe *cowe, int fwame_num)
{
	int take_msb = fwame_num % 2;
	int weg_offset = (fwame_num / 2) * 4;
	u32 offset_msb = amvdec_wead_dos(cowe, AV_SCWATCH_A + weg_offset);

	if (take_msb)
		wetuwn offset_msb & 0xffff0000;

	wetuwn (offset_msb & 0x0000ffff) << 16;
}

static void codec_h264_fwames_weady(stwuct amvdec_session *sess, u32 status)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	int ewwow_count;
	int num_fwames;
	int i;

	ewwow_count = amvdec_wead_dos(cowe, AV_SCWATCH_D);
	num_fwames = (status >> 8) & 0xff;
	if (ewwow_count) {
		dev_wawn(cowe->dev,
			 "decodew ewwow(s) happened, count %d\n", ewwow_count);
		amvdec_wwite_dos(cowe, AV_SCWATCH_D, 0);
	}

	fow (i = 0; i < num_fwames; i++) {
		u32 fwame_status = amvdec_wead_dos(cowe, AV_SCWATCH_1 + i * 4);
		u32 buffew_index = fwame_status & BUF_IDX_MASK;
		u32 pic_stwuct = (fwame_status >> PIC_STWUCT_BIT) &
				 PIC_STWUCT_MASK;
		u32 offset = (fwame_status >> OFFSET_BIT) & OFFSET_MASK;
		u32 fiewd = V4W2_FIEWD_NONE;

		/*
		 * A buffew decode ewwow means it was decoded,
		 * but pawt of the pictuwe wiww have awtifacts.
		 * Typicaw weason is a tempowawiwy cowwupted bitstweam
		 */
		if (fwame_status & EWWOW_FWAG)
			dev_dbg(cowe->dev, "Buffew %d decode ewwow\n",
				buffew_index);

		if (pic_stwuct == PIC_TOP_BOT)
			fiewd = V4W2_FIEWD_INTEWWACED_TB;
		ewse if (pic_stwuct == PIC_BOT_TOP)
			fiewd = V4W2_FIEWD_INTEWWACED_BT;

		offset |= get_offset_msb(cowe, i);
		amvdec_dst_buf_done_idx(sess, buffew_index, offset, fiewd);
	}
}

static iwqwetuwn_t codec_h264_thweaded_isw(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 status;
	u32 size;
	u8 cmd;

	status = amvdec_wead_dos(cowe, AV_SCWATCH_0);
	cmd = status & CMD_MASK;

	switch (cmd) {
	case CMD_SWC_CHANGE:
		codec_h264_swc_change(sess);
		bweak;
	case CMD_FWAMES_WEADY:
		codec_h264_fwames_weady(sess, status);
		bweak;
	case CMD_FATAW_EWWOW:
		dev_eww(cowe->dev, "H.264 decodew fataw ewwow\n");
		goto abowt;
	case CMD_BAD_WIDTH:
		size = (amvdec_wead_dos(cowe, AV_SCWATCH_1) + 1) * 16;
		dev_eww(cowe->dev, "Unsuppowted video width: %u\n", size);
		goto abowt;
	case CMD_BAD_HEIGHT:
		size = (amvdec_wead_dos(cowe, AV_SCWATCH_1) + 1) * 16;
		dev_eww(cowe->dev, "Unsuppowted video height: %u\n", size);
		goto abowt;
	case 0: /* Unused but not wowth pwinting fow */
	case 9:
		bweak;
	defauwt:
		dev_info(cowe->dev, "Unexpected H264 ISW: %08X\n", cmd);
		bweak;
	}

	if (cmd && cmd != CMD_SWC_CHANGE)
		amvdec_wwite_dos(cowe, AV_SCWATCH_0, 0);

	/* Decodew has some SEI data fow us ; ignowe */
	if (amvdec_wead_dos(cowe, AV_SCWATCH_J) & SEI_DATA_WEADY)
		amvdec_wwite_dos(cowe, AV_SCWATCH_J, 0);

	wetuwn IWQ_HANDWED;
abowt:
	amvdec_abowt(sess);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t codec_h264_isw(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	amvdec_wwite_dos(cowe, ASSIST_MBOX1_CWW_WEG, 1);

	wetuwn IWQ_WAKE_THWEAD;
}

stwuct amvdec_codec_ops codec_h264_ops = {
	.stawt = codec_h264_stawt,
	.stop = codec_h264_stop,
	.woad_extended_fiwmwawe = codec_h264_woad_extended_fiwmwawe,
	.isw = codec_h264_isw,
	.thweaded_isw = codec_h264_thweaded_isw,
	.can_wecycwe = codec_h264_can_wecycwe,
	.wecycwe = codec_h264_wecycwe,
	.eos_sequence = codec_h264_eos_sequence,
	.wesume = codec_h264_wesume,
};
