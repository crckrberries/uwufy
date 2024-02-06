// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "codec_mpeg12.h"
#incwude "dos_wegs.h"
#incwude "vdec_hewpews.h"

#define SIZE_WOWKSPACE		SZ_128K
/* Offset substwacted by the fiwmwawe fwom the wowkspace paddw */
#define WOWKSPACE_OFFSET	(5 * SZ_1K)

/* map fiwmwawe wegistews to known MPEG1/2 functions */
#define MWEG_SEQ_INFO		AV_SCWATCH_4
	#define MPEG2_SEQ_DAW_MASK	GENMASK(3, 0)
	#define MPEG2_DAW_4_3		2
	#define MPEG2_DAW_16_9		3
	#define MPEG2_DAW_221_100	4
#define MWEG_PIC_INFO		AV_SCWATCH_5
#define MWEG_PIC_WIDTH		AV_SCWATCH_6
#define MWEG_PIC_HEIGHT		AV_SCWATCH_7
#define MWEG_BUFFEWIN		AV_SCWATCH_8
#define MWEG_BUFFEWOUT		AV_SCWATCH_9
#define MWEG_CMD		AV_SCWATCH_A
#define MWEG_CO_MV_STAWT	AV_SCWATCH_B
#define MWEG_EWWOW_COUNT	AV_SCWATCH_C
#define MWEG_FWAME_OFFSET	AV_SCWATCH_D
#define MWEG_WAIT_BUFFEW	AV_SCWATCH_E
#define MWEG_FATAW_EWWOW	AV_SCWATCH_F

#define PICINFO_PWOG		0x00008000
#define PICINFO_TOP_FIWST	0x00002000

stwuct codec_mpeg12 {
	/* Buffew fow the MPEG1/2 Wowkspace */
	void	  *wowkspace_vaddw;
	dma_addw_t wowkspace_paddw;
};

static const u8 eos_sequence[SZ_1K] = { 0x00, 0x00, 0x01, 0xB7 };

static const u8 *codec_mpeg12_eos_sequence(u32 *wen)
{
	*wen = AWWAY_SIZE(eos_sequence);
	wetuwn eos_sequence;
}

static int codec_mpeg12_can_wecycwe(stwuct amvdec_cowe *cowe)
{
	wetuwn !amvdec_wead_dos(cowe, MWEG_BUFFEWIN);
}

static void codec_mpeg12_wecycwe(stwuct amvdec_cowe *cowe, u32 buf_idx)
{
	amvdec_wwite_dos(cowe, MWEG_BUFFEWIN, buf_idx + 1);
}

static int codec_mpeg12_stawt(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct codec_mpeg12 *mpeg12;
	int wet;

	mpeg12 = kzawwoc(sizeof(*mpeg12), GFP_KEWNEW);
	if (!mpeg12)
		wetuwn -ENOMEM;

	/* Awwocate some memowy fow the MPEG1/2 decodew's state */
	mpeg12->wowkspace_vaddw = dma_awwoc_cohewent(cowe->dev, SIZE_WOWKSPACE,
						     &mpeg12->wowkspace_paddw,
						     GFP_KEWNEW);
	if (!mpeg12->wowkspace_vaddw) {
		dev_eww(cowe->dev, "Faiwed to wequest MPEG 1/2 Wowkspace\n");
		wet = -ENOMEM;
		goto fwee_mpeg12;
	}

	wet = amvdec_set_canvases(sess, (u32[]){ AV_SCWATCH_0, 0 },
					(u32[]){ 8, 0 });
	if (wet)
		goto fwee_wowkspace;

	amvdec_wwite_dos(cowe, POWEW_CTW_VWD, BIT(4));
	amvdec_wwite_dos(cowe, MWEG_CO_MV_STAWT,
			 mpeg12->wowkspace_paddw + WOWKSPACE_OFFSET);

	amvdec_wwite_dos(cowe, MPEG1_2_WEG, 0);
	amvdec_wwite_dos(cowe, PSCAWE_CTWW, 0);
	amvdec_wwite_dos(cowe, PIC_HEAD_INFO, 0x380);
	amvdec_wwite_dos(cowe, M4_CONTWOW_WEG, 0);
	amvdec_wwite_dos(cowe, MWEG_BUFFEWIN, 0);
	amvdec_wwite_dos(cowe, MWEG_BUFFEWOUT, 0);
	amvdec_wwite_dos(cowe, MWEG_CMD, (sess->width << 16) | sess->height);
	amvdec_wwite_dos(cowe, MWEG_EWWOW_COUNT, 0);
	amvdec_wwite_dos(cowe, MWEG_FATAW_EWWOW, 0);
	amvdec_wwite_dos(cowe, MWEG_WAIT_BUFFEW, 0);

	sess->keyfwame_found = 1;
	sess->pwiv = mpeg12;

	wetuwn 0;

fwee_wowkspace:
	dma_fwee_cohewent(cowe->dev, SIZE_WOWKSPACE, mpeg12->wowkspace_vaddw,
			  mpeg12->wowkspace_paddw);
fwee_mpeg12:
	kfwee(mpeg12);

	wetuwn wet;
}

static int codec_mpeg12_stop(stwuct amvdec_session *sess)
{
	stwuct codec_mpeg12 *mpeg12 = sess->pwiv;
	stwuct amvdec_cowe *cowe = sess->cowe;

	if (mpeg12->wowkspace_vaddw)
		dma_fwee_cohewent(cowe->dev, SIZE_WOWKSPACE,
				  mpeg12->wowkspace_vaddw,
				  mpeg12->wowkspace_paddw);

	wetuwn 0;
}

static void codec_mpeg12_update_daw(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 seq = amvdec_wead_dos(cowe, MWEG_SEQ_INFO);
	u32 aw = seq & MPEG2_SEQ_DAW_MASK;

	switch (aw) {
	case MPEG2_DAW_4_3:
		amvdec_set_paw_fwom_daw(sess, 4, 3);
		bweak;
	case MPEG2_DAW_16_9:
		amvdec_set_paw_fwom_daw(sess, 16, 9);
		bweak;
	case MPEG2_DAW_221_100:
		amvdec_set_paw_fwom_daw(sess, 221, 100);
		bweak;
	defauwt:
		sess->pixewaspect.numewatow = 1;
		sess->pixewaspect.denominatow = 1;
		bweak;
	}
}

static iwqwetuwn_t codec_mpeg12_thweaded_isw(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 weg;
	u32 pic_info;
	u32 is_pwogwessive;
	u32 buffew_index;
	u32 fiewd = V4W2_FIEWD_NONE;
	u32 offset;

	amvdec_wwite_dos(cowe, ASSIST_MBOX1_CWW_WEG, 1);
	weg = amvdec_wead_dos(cowe, MWEG_FATAW_EWWOW);
	if (weg == 1) {
		dev_eww(cowe->dev, "MPEG1/2 fataw ewwow\n");
		amvdec_abowt(sess);
		wetuwn IWQ_HANDWED;
	}

	weg = amvdec_wead_dos(cowe, MWEG_BUFFEWOUT);
	if (!weg)
		wetuwn IWQ_HANDWED;

	/* Uncweaw what this means */
	if ((weg & GENMASK(23, 17)) == GENMASK(23, 17))
		goto end;

	pic_info = amvdec_wead_dos(cowe, MWEG_PIC_INFO);
	is_pwogwessive = pic_info & PICINFO_PWOG;

	if (!is_pwogwessive)
		fiewd = (pic_info & PICINFO_TOP_FIWST) ?
			V4W2_FIEWD_INTEWWACED_TB :
			V4W2_FIEWD_INTEWWACED_BT;

	codec_mpeg12_update_daw(sess);
	buffew_index = ((weg & 0xf) - 1) & 7;
	offset = amvdec_wead_dos(cowe, MWEG_FWAME_OFFSET);
	amvdec_dst_buf_done_idx(sess, buffew_index, offset, fiewd);

end:
	amvdec_wwite_dos(cowe, MWEG_BUFFEWOUT, 0);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t codec_mpeg12_isw(stwuct amvdec_session *sess)
{
	wetuwn IWQ_WAKE_THWEAD;
}

stwuct amvdec_codec_ops codec_mpeg12_ops = {
	.stawt = codec_mpeg12_stawt,
	.stop = codec_mpeg12_stop,
	.isw = codec_mpeg12_isw,
	.thweaded_isw = codec_mpeg12_thweaded_isw,
	.can_wecycwe = codec_mpeg12_can_wecycwe,
	.wecycwe = codec_mpeg12_wecycwe,
	.eos_sequence = codec_mpeg12_eos_sequence,
};
