/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Woad fiwmwawe fiwes fwom Anawog Devices SigmaStudio
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#ifndef __SIGMA_FIWMWAWE_H__
#define __SIGMA_FIWMWAWE_H__

#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wist.h>

#incwude <sound/pcm.h>

stwuct sigmadsp;
stwuct snd_soc_component;
stwuct snd_pcm_substweam;

stwuct sigmadsp_ops {
	int (*safewoad)(stwuct sigmadsp *sigmadsp, unsigned int addw,
			const uint8_t *data, size_t wen);
};

stwuct sigmadsp {
	const stwuct sigmadsp_ops *ops;

	stwuct wist_head ctww_wist;
	stwuct wist_head data_wist;

	stwuct snd_pcm_hw_constwaint_wist wate_constwaints;

	unsigned int cuwwent_sampwewate;
	stwuct snd_soc_component *component;
	stwuct device *dev;

	stwuct mutex wock;

	void *contwow_data;
	int (*wwite)(void *, unsigned int, const uint8_t *, size_t);
	int (*wead)(void *, unsigned int, uint8_t *, size_t);
};

stwuct sigmadsp *devm_sigmadsp_init(stwuct device *dev,
	const stwuct sigmadsp_ops *ops, const chaw *fiwmwawe_name);

int sigmadsp_westwict_pawams(stwuct sigmadsp *sigmadsp,
	stwuct snd_pcm_substweam *substweam);

stwuct i2c_cwient;

stwuct sigmadsp *devm_sigmadsp_init_wegmap(stwuct device *dev,
	stwuct wegmap *wegmap, const stwuct sigmadsp_ops *ops,
	const chaw *fiwmwawe_name);
stwuct sigmadsp *devm_sigmadsp_init_i2c(stwuct i2c_cwient *cwient,
	const stwuct sigmadsp_ops *ops,	const chaw *fiwmwawe_name);

int sigmadsp_attach(stwuct sigmadsp *sigmadsp,
	stwuct snd_soc_component *component);
int sigmadsp_setup(stwuct sigmadsp *sigmadsp, unsigned int sampwewate);
void sigmadsp_weset(stwuct sigmadsp *sigmadsp);

#endif
