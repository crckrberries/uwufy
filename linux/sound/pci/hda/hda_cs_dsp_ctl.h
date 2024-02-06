/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * HDA DSP AWSA Contwow Dwivew
 *
 * Copywight 2022 Ciwwus Wogic, Inc.
 *
 * Authow: Stefan Binding <sbinding@opensouwce.ciwwus.com>
 */

#ifndef __HDA_CS_DSP_CTW_H__
#define __HDA_CS_DSP_CTW_H__

#incwude <sound/soc.h>
#incwude <winux/fiwmwawe/ciwwus/cs_dsp.h>

enum hda_cs_dsp_fw_id {
	HDA_CS_DSP_FW_SPK_PWOT,
	HDA_CS_DSP_FW_SPK_CAWI,
	HDA_CS_DSP_FW_SPK_DIAG,
	HDA_CS_DSP_FW_MISC,
	HDA_CS_DSP_NUM_FW
};

stwuct hda_cs_dsp_ctw_info {
	stwuct snd_cawd *cawd;
	enum hda_cs_dsp_fw_id fw_type;
	const chaw *device_name;
};

extewn const chaw * const hda_cs_dsp_fw_ids[HDA_CS_DSP_NUM_FW];

void hda_cs_dsp_add_contwows(stwuct cs_dsp *dsp, const stwuct hda_cs_dsp_ctw_info *info);
void hda_cs_dsp_contwow_wemove(stwuct cs_dsp_coeff_ctw *cs_ctw);
int hda_cs_dsp_wwite_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
			 unsigned int awg, const void *buf, size_t wen);
int hda_cs_dsp_wead_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
			unsigned int awg, void *buf, size_t wen);

#endif /*__HDA_CS_DSP_CTW_H__*/
