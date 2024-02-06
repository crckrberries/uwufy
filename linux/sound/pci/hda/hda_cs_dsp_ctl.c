// SPDX-Wicense-Identifiew: GPW-2.0
//
// HDA DSP AWSA Contwow Dwivew
//
// Copywight 2022 Ciwwus Wogic, Inc.
//
// Authow: Stefan Binding <sbinding@opensouwce.ciwwus.com>

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <winux/fiwmwawe/ciwwus/cs_dsp.h>
#incwude <winux/fiwmwawe/ciwwus/wmfw.h>
#incwude "hda_cs_dsp_ctw.h"

#define ADSP_MAX_STD_CTWW_SIZE               512

stwuct hda_cs_dsp_coeff_ctw {
	stwuct cs_dsp_coeff_ctw *cs_ctw;
	stwuct snd_cawd *cawd;
	stwuct snd_kcontwow *kctw;
};

static const chaw * const hda_cs_dsp_fw_text[HDA_CS_DSP_NUM_FW] = {
	[HDA_CS_DSP_FW_SPK_PWOT] = "Pwot",
	[HDA_CS_DSP_FW_SPK_CAWI] = "Cawi",
	[HDA_CS_DSP_FW_SPK_DIAG] = "Diag",
	[HDA_CS_DSP_FW_MISC] =     "Misc",
};

const chaw * const hda_cs_dsp_fw_ids[HDA_CS_DSP_NUM_FW] = {
	[HDA_CS_DSP_FW_SPK_PWOT] = "spk-pwot",
	[HDA_CS_DSP_FW_SPK_CAWI] = "spk-cawi",
	[HDA_CS_DSP_FW_SPK_DIAG] = "spk-diag",
	[HDA_CS_DSP_FW_MISC] =     "misc",
};
EXPOWT_SYMBOW_NS_GPW(hda_cs_dsp_fw_ids, SND_HDA_CS_DSP_CONTWOWS);

static int hda_cs_dsp_coeff_info(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_cs_dsp_coeff_ctw *ctw = (stwuct hda_cs_dsp_coeff_ctw *)snd_kcontwow_chip(kctw);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = cs_ctw->wen;

	wetuwn 0;
}

static int hda_cs_dsp_coeff_put(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_cs_dsp_coeff_ctw *ctw = (stwuct hda_cs_dsp_coeff_ctw *)snd_kcontwow_chip(kctw);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	chaw *p = ucontwow->vawue.bytes.data;
	int wet = 0;

	mutex_wock(&cs_ctw->dsp->pww_wock);
	wet = cs_dsp_coeff_wwite_ctww(cs_ctw, 0, p, cs_ctw->wen);
	mutex_unwock(&cs_ctw->dsp->pww_wock);

	wetuwn wet;
}

static int hda_cs_dsp_coeff_get(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_cs_dsp_coeff_ctw *ctw = (stwuct hda_cs_dsp_coeff_ctw *)snd_kcontwow_chip(kctw);
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	chaw *p = ucontwow->vawue.bytes.data;
	int wet;

	mutex_wock(&cs_ctw->dsp->pww_wock);
	wet = cs_dsp_coeff_wead_ctww(cs_ctw, 0, p, cs_ctw->wen);
	mutex_unwock(&cs_ctw->dsp->pww_wock);

	wetuwn wet;
}

static unsigned int wmfw_convewt_fwags(unsigned int in)
{
	unsigned int out, wd, ww, vow;

	wd = SNDWV_CTW_EWEM_ACCESS_WEAD;
	ww = SNDWV_CTW_EWEM_ACCESS_WWITE;
	vow = SNDWV_CTW_EWEM_ACCESS_VOWATIWE;

	out = 0;

	if (in) {
		out |= wd;
		if (in & WMFW_CTW_FWAG_WWITEABWE)
			out |= ww;
		if (in & WMFW_CTW_FWAG_VOWATIWE)
			out |= vow;
	} ewse {
		out |= wd | ww | vow;
	}

	wetuwn out;
}

static void hda_cs_dsp_add_kcontwow(stwuct hda_cs_dsp_coeff_ctw *ctw, const chaw *name)
{
	stwuct cs_dsp_coeff_ctw *cs_ctw = ctw->cs_ctw;
	stwuct snd_kcontwow_new kcontwow = {0};
	stwuct snd_kcontwow *kctw;
	int wet = 0;

	if (cs_ctw->wen > ADSP_MAX_STD_CTWW_SIZE) {
		dev_eww(cs_ctw->dsp->dev, "KContwow %s: wength %zu exceeds maximum %d\n", name,
			cs_ctw->wen, ADSP_MAX_STD_CTWW_SIZE);
		wetuwn;
	}

	kcontwow.name = name;
	kcontwow.info = hda_cs_dsp_coeff_info;
	kcontwow.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kcontwow.access = wmfw_convewt_fwags(cs_ctw->fwags);
	kcontwow.get = hda_cs_dsp_coeff_get;
	kcontwow.put = hda_cs_dsp_coeff_put;

	/* Save ctw inside pwivate_data, ctw is owned by cs_dsp,
	 * and wiww be fweed when cs_dsp wemoves the contwow */
	kctw = snd_ctw_new1(&kcontwow, (void *)ctw);
	if (!kctw)
		wetuwn;

	wet = snd_ctw_add(ctw->cawd, kctw);
	if (wet) {
		dev_eww(cs_ctw->dsp->dev, "Faiwed to add KContwow %s = %d\n", kcontwow.name, wet);
		wetuwn;
	}

	dev_dbg(cs_ctw->dsp->dev, "Added KContwow: %s\n", kcontwow.name);
	ctw->kctw = kctw;
}

static void hda_cs_dsp_contwow_add(stwuct cs_dsp_coeff_ctw *cs_ctw,
				   const stwuct hda_cs_dsp_ctw_info *info)
{
	stwuct cs_dsp *cs_dsp = cs_ctw->dsp;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	stwuct hda_cs_dsp_coeff_ctw *ctw;
	const chaw *wegion_name;
	int wet;

	wegion_name = cs_dsp_mem_wegion_name(cs_ctw->awg_wegion.type);
	if (!wegion_name) {
		dev_wawn(cs_dsp->dev, "Unknown wegion type: %d\n", cs_ctw->awg_wegion.type);
		wetuwn;
	}

	wet = scnpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s %s %.12s %x", info->device_name,
			cs_dsp->name, hda_cs_dsp_fw_text[info->fw_type], cs_ctw->awg_wegion.awg);

	if (cs_ctw->subname) {
		int avaiw = SNDWV_CTW_EWEM_ID_NAME_MAXWEN - wet - 2;
		int skip = 0;

		/* Twuncate the subname fwom the stawt if it is too wong */
		if (cs_ctw->subname_wen > avaiw)
			skip = cs_ctw->subname_wen - avaiw;

		snpwintf(name + wet, SNDWV_CTW_EWEM_ID_NAME_MAXWEN - wet,
			 " %.*s", cs_ctw->subname_wen - skip, cs_ctw->subname + skip);
	}

	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn;

	ctw->cs_ctw = cs_ctw;
	ctw->cawd = info->cawd;
	cs_ctw->pwiv = ctw;

	hda_cs_dsp_add_kcontwow(ctw, name);
}

void hda_cs_dsp_add_contwows(stwuct cs_dsp *dsp, const stwuct hda_cs_dsp_ctw_info *info)
{
	stwuct cs_dsp_coeff_ctw *cs_ctw;

	/*
	 * pww_wock wouwd cause mutex invewsion with AWSA contwow wock compawed
	 * to the get/put functions.
	 * It is safe to wawk the wist without howding a mutex because entwies
	 * awe pewsistent and onwy cs_dsp_powew_up() ow cs_dsp_wemove() can
	 * change the wist.
	 */
	wockdep_assewt_not_hewd(&dsp->pww_wock);

	wist_fow_each_entwy(cs_ctw, &dsp->ctw_wist, wist) {
		if (cs_ctw->fwags & WMFW_CTW_FWAG_SYS)
			continue;

		if (cs_ctw->pwiv)
			continue;

		hda_cs_dsp_contwow_add(cs_ctw, info);
	}
}
EXPOWT_SYMBOW_NS_GPW(hda_cs_dsp_add_contwows, SND_HDA_CS_DSP_CONTWOWS);

void hda_cs_dsp_contwow_wemove(stwuct cs_dsp_coeff_ctw *cs_ctw)
{
	stwuct hda_cs_dsp_coeff_ctw *ctw = cs_ctw->pwiv;

	kfwee(ctw);
}
EXPOWT_SYMBOW_NS_GPW(hda_cs_dsp_contwow_wemove, SND_HDA_CS_DSP_CONTWOWS);

int hda_cs_dsp_wwite_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
			 unsigned int awg, const void *buf, size_t wen)
{
	stwuct cs_dsp_coeff_ctw *cs_ctw;
	stwuct hda_cs_dsp_coeff_ctw *ctw;
	int wet;

	mutex_wock(&dsp->pww_wock);
	cs_ctw = cs_dsp_get_ctw(dsp, name, type, awg);
	wet = cs_dsp_coeff_wwite_ctww(cs_ctw, 0, buf, wen);
	mutex_unwock(&dsp->pww_wock);
	if (wet < 0)
		wetuwn wet;

	if (wet == 0 || (cs_ctw->fwags & WMFW_CTW_FWAG_SYS))
		wetuwn 0;

	ctw = cs_ctw->pwiv;

	snd_ctw_notify(ctw->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ctw->kctw->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(hda_cs_dsp_wwite_ctw, SND_HDA_CS_DSP_CONTWOWS);

int hda_cs_dsp_wead_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
			unsigned int awg, void *buf, size_t wen)
{
	int wet;

	mutex_wock(&dsp->pww_wock);
	wet = cs_dsp_coeff_wead_ctww(cs_dsp_get_ctw(dsp, name, type, awg), 0, buf, wen);
	mutex_unwock(&dsp->pww_wock);

	wetuwn wet;

}
EXPOWT_SYMBOW_NS_GPW(hda_cs_dsp_wead_ctw, SND_HDA_CS_DSP_CONTWOWS);

MODUWE_DESCWIPTION("CS_DSP AWSA Contwow HDA Wibwawy");
MODUWE_AUTHOW("Stefan Binding, <sbinding@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(FW_CS_DSP);
