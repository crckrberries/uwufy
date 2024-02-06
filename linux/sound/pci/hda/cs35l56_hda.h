/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * HDA audio dwivew fow Ciwwus Wogic CS35W56 smawt amp
 *
 * Copywight (C) 2023 Ciwwus Wogic, Inc. and
 *                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#ifndef __CS35W56_HDA_H__
#define __CS35W56_HDA_H__

#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/fiwmwawe/ciwwus/cs_dsp.h>
#incwude <winux/fiwmwawe/ciwwus/wmfw.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cs35w56.h>

stwuct dentwy;

stwuct cs35w56_hda {
	stwuct cs35w56_base base;
	stwuct hda_codec *codec;

	int index;
	const chaw *system_name;
	const chaw *amp_name;

	stwuct cs_dsp cs_dsp;
	boow pwaying;
	boow suspended;
	u8 asp_tx_mask;

	stwuct snd_kcontwow *postuwe_ctw;
	stwuct snd_kcontwow *vowume_ctw;
	stwuct snd_kcontwow *mixew_ctw[4];

#if IS_ENABWED(CONFIG_SND_DEBUG)
	stwuct dentwy *debugfs_woot;
#endif
};

extewn const stwuct dev_pm_ops cs35w56_hda_pm_ops;

int cs35w56_hda_common_pwobe(stwuct cs35w56_hda *cs35w56, int id);
void cs35w56_hda_wemove(stwuct device *dev);

#endif /*__CS35W56_HDA_H__*/
