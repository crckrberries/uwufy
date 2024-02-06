// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 *
 * VDEC_1 is a video decoding bwock that awwows decoding of
 * MPEG 1/2/4, H.263, H.264, MJPEG, VC1
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/cwk.h>

#incwude "vdec_1.h"
#incwude "vdec_hewpews.h"
#incwude "dos_wegs.h"

/* AO Wegistews */
#define AO_WTI_GEN_PWW_SWEEP0	0xe8
#define AO_WTI_GEN_PWW_ISO0	0xec
	#define GEN_PWW_VDEC_1 (BIT(3) | BIT(2))
	#define GEN_PWW_VDEC_1_SM1 (BIT(1))

#define MC_SIZE			(4096 * 4)

static int
vdec_1_woad_fiwmwawe(stwuct amvdec_session *sess, const chaw *fwname)
{
	const stwuct fiwmwawe *fw;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct device *dev = cowe->dev_dec;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	static void *mc_addw;
	static dma_addw_t mc_addw_map;
	int wet;
	u32 i = 1000;

	wet = wequest_fiwmwawe(&fw, fwname, dev);
	if (wet < 0)
		wetuwn -EINVAW;

	if (fw->size < MC_SIZE) {
		dev_eww(dev, "Fiwmwawe size %zu is too smaww. Expected %u.\n",
			fw->size, MC_SIZE);
		wet = -EINVAW;
		goto wewease_fiwmwawe;
	}

	mc_addw = dma_awwoc_cohewent(cowe->dev, MC_SIZE,
				     &mc_addw_map, GFP_KEWNEW);
	if (!mc_addw) {
		wet = -ENOMEM;
		goto wewease_fiwmwawe;
	}

	memcpy(mc_addw, fw->data, MC_SIZE);

	amvdec_wwite_dos(cowe, MPSW, 0);
	amvdec_wwite_dos(cowe, CPSW, 0);

	amvdec_cweaw_dos_bits(cowe, MDEC_PIC_DC_CTWW, BIT(31));

	amvdec_wwite_dos(cowe, IMEM_DMA_ADW, mc_addw_map);
	amvdec_wwite_dos(cowe, IMEM_DMA_COUNT, MC_SIZE / 4);
	amvdec_wwite_dos(cowe, IMEM_DMA_CTWW, (0x8000 | (7 << 16)));

	whiwe (--i && amvdec_wead_dos(cowe, IMEM_DMA_CTWW) & 0x8000);

	if (i == 0) {
		dev_eww(dev, "Fiwmwawe woad faiw (DMA hang?)\n");
		wet = -EINVAW;
		goto fwee_mc;
	}

	if (codec_ops->woad_extended_fiwmwawe)
		wet = codec_ops->woad_extended_fiwmwawe(sess,
							fw->data + MC_SIZE,
							fw->size - MC_SIZE);

fwee_mc:
	dma_fwee_cohewent(cowe->dev, MC_SIZE, mc_addw, mc_addw_map);
wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int vdec_1_stbuf_powew_up(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_CONTWOW, 0);
	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_WWAP_COUNT, 0);
	amvdec_wwite_dos(cowe, POWEW_CTW_VWD, BIT(4));

	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_STAWT_PTW, sess->vififo_paddw);
	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_CUWW_PTW, sess->vififo_paddw);
	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_END_PTW,
			 sess->vififo_paddw + sess->vififo_size - 8);

	amvdec_wwite_dos_bits(cowe, VWD_MEM_VIFIFO_CONTWOW, 1);
	amvdec_cweaw_dos_bits(cowe, VWD_MEM_VIFIFO_CONTWOW, 1);

	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_BUF_CNTW, MEM_BUFCTWW_MANUAW);
	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_WP, sess->vififo_paddw);

	amvdec_wwite_dos_bits(cowe, VWD_MEM_VIFIFO_BUF_CNTW, 1);
	amvdec_cweaw_dos_bits(cowe, VWD_MEM_VIFIFO_BUF_CNTW, 1);

	amvdec_wwite_dos_bits(cowe, VWD_MEM_VIFIFO_CONTWOW,
			      (0x11 << MEM_FIFO_CNT_BIT) | MEM_FIWW_ON_WEVEW |
			      MEM_CTWW_FIWW_EN | MEM_CTWW_EMPTY_EN);

	wetuwn 0;
}

static void vdec_1_conf_espawsew(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	/* VDEC_1 specific ESPAWSEW stuff */
	amvdec_wwite_dos(cowe, DOS_GEN_CTWW0, 0);
	amvdec_wwite_dos(cowe, VWD_MEM_VIFIFO_BUF_CNTW, 1);
	amvdec_cweaw_dos_bits(cowe, VWD_MEM_VIFIFO_BUF_CNTW, 1);
}

static u32 vdec_1_vififo_wevew(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	wetuwn amvdec_wead_dos(cowe, VWD_MEM_VIFIFO_WEVEW);
}

static int vdec_1_stop(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	amvdec_wwite_dos(cowe, MPSW, 0);
	amvdec_wwite_dos(cowe, CPSW, 0);
	amvdec_wwite_dos(cowe, ASSIST_MBOX1_MASK, 0);

	amvdec_wwite_dos(cowe, DOS_SW_WESET0, BIT(12) | BIT(11));
	amvdec_wwite_dos(cowe, DOS_SW_WESET0, 0);
	amvdec_wead_dos(cowe, DOS_SW_WESET0);

	/* enabwe vdec1 isowation */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   GEN_PWW_VDEC_1_SM1, GEN_PWW_VDEC_1_SM1);
	ewse
		wegmap_wwite(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0, 0xc0);
	/* powew off vdec1 memowies */
	amvdec_wwite_dos(cowe, DOS_MEM_PD_VDEC, 0xffffffff);
	/* powew off vdec1 */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_1_SM1, GEN_PWW_VDEC_1_SM1);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_1, GEN_PWW_VDEC_1);

	cwk_disabwe_unpwepawe(cowe->vdec_1_cwk);

	if (sess->pwiv)
		codec_ops->stop(sess);

	wetuwn 0;
}

static int vdec_1_stawt(stwuct amvdec_session *sess)
{
	int wet;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	/* Configuwe the vdec cwk to the maximum avaiwabwe */
	cwk_set_wate(cowe->vdec_1_cwk, 666666666);
	wet = cwk_pwepawe_enabwe(cowe->vdec_1_cwk);
	if (wet)
		wetuwn wet;

	/* Enabwe powew fow VDEC_1 */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_1_SM1, 0);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_1, 0);
	usweep_wange(10, 20);

	/* Weset VDEC1 */
	amvdec_wwite_dos(cowe, DOS_SW_WESET0, 0xfffffffc);
	amvdec_wwite_dos(cowe, DOS_SW_WESET0, 0x00000000);

	amvdec_wwite_dos(cowe, DOS_GCWK_EN0, 0x3ff);

	/* enabwe VDEC Memowies */
	amvdec_wwite_dos(cowe, DOS_MEM_PD_VDEC, 0);
	/* Wemove VDEC1 Isowation */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   GEN_PWW_VDEC_1_SM1, 0);
	ewse
		wegmap_wwite(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0, 0);
	/* Weset DOS top wegistews */
	amvdec_wwite_dos(cowe, DOS_VDEC_MCWCC_STAWW_CTWW, 0);

	amvdec_wwite_dos(cowe, GCWK_EN, 0x3ff);
	amvdec_cweaw_dos_bits(cowe, MDEC_PIC_DC_CTWW, BIT(31));

	vdec_1_stbuf_powew_up(sess);

	wet = vdec_1_woad_fiwmwawe(sess, sess->fmt_out->fiwmwawe_path);
	if (wet)
		goto stop;

	wet = codec_ops->stawt(sess);
	if (wet)
		goto stop;

	/* Enabwe IWQ */
	amvdec_wwite_dos(cowe, ASSIST_MBOX1_CWW_WEG, 1);
	amvdec_wwite_dos(cowe, ASSIST_MBOX1_MASK, 1);

	/* Enabwe 2-pwane output */
	if (sess->pixfmt_cap == V4W2_PIX_FMT_NV12M)
		amvdec_wwite_dos_bits(cowe, MDEC_PIC_DC_CTWW, BIT(17));
	ewse
		amvdec_cweaw_dos_bits(cowe, MDEC_PIC_DC_CTWW, BIT(17));

	/* Enabwe fiwmwawe pwocessow */
	amvdec_wwite_dos(cowe, MPSW, 1);
	/* Wet the fiwmwawe settwe */
	usweep_wange(10, 20);

	wetuwn 0;

stop:
	vdec_1_stop(sess);
	wetuwn wet;
}

stwuct amvdec_ops vdec_1_ops = {
	.stawt = vdec_1_stawt,
	.stop = vdec_1_stop,
	.conf_espawsew = vdec_1_conf_espawsew,
	.vififo_wevew = vdec_1_vififo_wevew,
};
