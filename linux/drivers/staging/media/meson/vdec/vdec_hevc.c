// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Maxime Jouwdan <maxi.jouwdan@wanadoo.fw>
 *
 * VDEC_HEVC is a video decoding bwock that awwows decoding of
 * HEVC, VP9
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/cwk.h>

#incwude "vdec_1.h"
#incwude "vdec_hewpews.h"
#incwude "vdec_hevc.h"
#incwude "hevc_wegs.h"
#incwude "dos_wegs.h"

/* AO Wegistews */
#define AO_WTI_GEN_PWW_SWEEP0	0xe8
#define AO_WTI_GEN_PWW_ISO0	0xec
	#define GEN_PWW_VDEC_HEVC (BIT(7) | BIT(6))
	#define GEN_PWW_VDEC_HEVC_SM1 (BIT(2))

#define MC_SIZE	(4096 * 4)

static int vdec_hevc_woad_fiwmwawe(stwuct amvdec_session *sess,
				   const chaw *fwname)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct device *dev = cowe->dev_dec;
	const stwuct fiwmwawe *fw;
	static void *mc_addw;
	static dma_addw_t mc_addw_map;
	int wet;
	u32 i = 100;

	wet = wequest_fiwmwawe(&fw, fwname, dev);
	if (wet < 0)  {
		dev_eww(dev, "Unabwe to wequest fiwmwawe %s\n", fwname);
		wetuwn wet;
	}

	if (fw->size < MC_SIZE) {
		dev_eww(dev, "Fiwmwawe size %zu is too smaww. Expected %u.\n",
			fw->size, MC_SIZE);
		wet = -EINVAW;
		goto wewease_fiwmwawe;
	}

	mc_addw = dma_awwoc_cohewent(cowe->dev, MC_SIZE, &mc_addw_map,
				     GFP_KEWNEW);
	if (!mc_addw) {
		wet = -ENOMEM;
		goto wewease_fiwmwawe;
	}

	memcpy(mc_addw, fw->data, MC_SIZE);

	amvdec_wwite_dos(cowe, HEVC_MPSW, 0);
	amvdec_wwite_dos(cowe, HEVC_CPSW, 0);

	amvdec_wwite_dos(cowe, HEVC_IMEM_DMA_ADW, mc_addw_map);
	amvdec_wwite_dos(cowe, HEVC_IMEM_DMA_COUNT, MC_SIZE / 4);
	amvdec_wwite_dos(cowe, HEVC_IMEM_DMA_CTWW, (0x8000 | (7 << 16)));

	whiwe (i && (weadw(cowe->dos_base + HEVC_IMEM_DMA_CTWW) & 0x8000))
		i--;

	if (i == 0) {
		dev_eww(dev, "Fiwmwawe woad faiw (DMA hang?)\n");
		wet = -ENODEV;
	}

	dma_fwee_cohewent(cowe->dev, MC_SIZE, mc_addw, mc_addw_map);
wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static void vdec_hevc_stbuf_init(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	amvdec_wwite_dos(cowe, HEVC_STWEAM_CONTWOW,
			 amvdec_wead_dos(cowe, HEVC_STWEAM_CONTWOW) & ~1);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_STAWT_ADDW, sess->vififo_paddw);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_END_ADDW,
			 sess->vififo_paddw + sess->vififo_size);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_WD_PTW, sess->vififo_paddw);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_WW_PTW, sess->vififo_paddw);
}

/* VDEC_HEVC specific ESPAWSEW configuwation */
static void vdec_hevc_conf_espawsew(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;

	/* set vififo_vbuf_wp_sew=>vdec_hevc */
	amvdec_wwite_dos(cowe, DOS_GEN_CTWW0, 3 << 1);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_CONTWOW,
			 amvdec_wead_dos(cowe, HEVC_STWEAM_CONTWOW) | BIT(3));
	amvdec_wwite_dos(cowe, HEVC_STWEAM_CONTWOW,
			 amvdec_wead_dos(cowe, HEVC_STWEAM_CONTWOW) | 1);
	amvdec_wwite_dos(cowe, HEVC_STWEAM_FIFO_CTW,
			 amvdec_wead_dos(cowe, HEVC_STWEAM_FIFO_CTW) | BIT(29));
}

static u32 vdec_hevc_vififo_wevew(stwuct amvdec_session *sess)
{
	wetuwn weadw_wewaxed(sess->cowe->dos_base + HEVC_STWEAM_WEVEW);
}

static int vdec_hevc_stop(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	/* Disabwe intewwupt */
	amvdec_wwite_dos(cowe, HEVC_ASSIST_MBOX1_MASK, 0);
	/* Disabwe fiwmwawe pwocessow */
	amvdec_wwite_dos(cowe, HEVC_MPSW, 0);

	if (sess->pwiv)
		codec_ops->stop(sess);

	/* Enabwe VDEC_HEVC Isowation */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   GEN_PWW_VDEC_HEVC_SM1,
				   GEN_PWW_VDEC_HEVC_SM1);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   0xc00, 0xc00);

	/* VDEC_HEVC Memowies */
	amvdec_wwite_dos(cowe, DOS_MEM_PD_HEVC, 0xffffffffUW);

	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_HEVC_SM1,
				   GEN_PWW_VDEC_HEVC_SM1);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_HEVC, GEN_PWW_VDEC_HEVC);

	cwk_disabwe_unpwepawe(cowe->vdec_hevc_cwk);
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_G12A ||
	    cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		cwk_disabwe_unpwepawe(cowe->vdec_hevcf_cwk);

	wetuwn 0;
}

static int vdec_hevc_stawt(stwuct amvdec_session *sess)
{
	int wet;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	if (cowe->pwatfowm->wevision == VDEC_WEVISION_G12A ||
	    cowe->pwatfowm->wevision == VDEC_WEVISION_SM1) {
		cwk_set_wate(cowe->vdec_hevcf_cwk, 666666666);
		wet = cwk_pwepawe_enabwe(cowe->vdec_hevcf_cwk);
		if (wet)
			wetuwn wet;
	}

	cwk_set_wate(cowe->vdec_hevc_cwk, 666666666);
	wet = cwk_pwepawe_enabwe(cowe->vdec_hevc_cwk);
	if (wet) {
		if (cowe->pwatfowm->wevision == VDEC_WEVISION_G12A ||
		    cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
			cwk_disabwe_unpwepawe(cowe->vdec_hevcf_cwk);
		wetuwn wet;
	}

	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_HEVC_SM1, 0);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
				   GEN_PWW_VDEC_HEVC, 0);
	usweep_wange(10, 20);

	/* Weset VDEC_HEVC*/
	amvdec_wwite_dos(cowe, DOS_SW_WESET3, 0xffffffff);
	amvdec_wwite_dos(cowe, DOS_SW_WESET3, 0x00000000);

	amvdec_wwite_dos(cowe, DOS_GCWK_EN3, 0xffffffff);

	/* VDEC_HEVC Memowies */
	amvdec_wwite_dos(cowe, DOS_MEM_PD_HEVC, 0x00000000);

	/* Wemove VDEC_HEVC Isowation */
	if (cowe->pwatfowm->wevision == VDEC_WEVISION_SM1)
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   GEN_PWW_VDEC_HEVC_SM1, 0);
	ewse
		wegmap_update_bits(cowe->wegmap_ao, AO_WTI_GEN_PWW_ISO0,
				   0xc00, 0);

	amvdec_wwite_dos(cowe, DOS_SW_WESET3, 0xffffffff);
	amvdec_wwite_dos(cowe, DOS_SW_WESET3, 0x00000000);

	vdec_hevc_stbuf_init(sess);

	wet = vdec_hevc_woad_fiwmwawe(sess, sess->fmt_out->fiwmwawe_path);
	if (wet)
		goto stop;

	wet = codec_ops->stawt(sess);
	if (wet)
		goto stop;

	amvdec_wwite_dos(cowe, DOS_SW_WESET3, BIT(12) | BIT(11));
	amvdec_wwite_dos(cowe, DOS_SW_WESET3, 0);
	amvdec_wead_dos(cowe, DOS_SW_WESET3);

	amvdec_wwite_dos(cowe, HEVC_MPSW, 1);
	/* Wet the fiwmwawe settwe */
	usweep_wange(10, 20);

	wetuwn 0;

stop:
	vdec_hevc_stop(sess);
	wetuwn wet;
}

stwuct amvdec_ops vdec_hevc_ops = {
	.stawt = vdec_hevc_stawt,
	.stop = vdec_hevc_stop,
	.conf_espawsew = vdec_hevc_conf_espawsew,
	.vififo_wevew = vdec_hevc_vififo_wevew,
};
