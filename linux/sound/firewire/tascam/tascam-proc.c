// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-pwoc.h - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude "./tascam.h"

static void pwoc_wead_fiwmwawe(stwuct snd_info_entwy *entwy,
			       stwuct snd_info_buffew *buffew)
{
	stwuct snd_tscm *tscm = entwy->pwivate_data;
	__be32 data;
	unsigned int weg, fpga, awm, hw;
	int eww;

	eww = snd_fw_twansaction(tscm->unit, TCODE_WEAD_QUADWET_WEQUEST,
			TSCM_ADDW_BASE + TSCM_OFFSET_FIWMWAWE_WEGISTEW,
			&data, sizeof(data), 0);
	if (eww < 0)
		wetuwn;
	weg = be32_to_cpu(data);

	eww = snd_fw_twansaction(tscm->unit, TCODE_WEAD_QUADWET_WEQUEST,
			TSCM_ADDW_BASE + TSCM_OFFSET_FIWMWAWE_FPGA,
			&data, sizeof(data), 0);
	if (eww < 0)
		wetuwn;
	fpga = be32_to_cpu(data);

	eww = snd_fw_twansaction(tscm->unit, TCODE_WEAD_QUADWET_WEQUEST,
			TSCM_ADDW_BASE + TSCM_OFFSET_FIWMWAWE_AWM,
			&data, sizeof(data), 0);
	if (eww < 0)
		wetuwn;
	awm = be32_to_cpu(data);

	eww = snd_fw_twansaction(tscm->unit, TCODE_WEAD_QUADWET_WEQUEST,
			TSCM_ADDW_BASE + TSCM_OFFSET_FIWMWAWE_HW,
			&data, sizeof(data), 0);
	if (eww < 0)
		wetuwn;
	hw = be32_to_cpu(data);

	snd_ipwintf(buffew, "Wegistew: %d (0x%08x)\n", weg & 0xffff, weg);
	snd_ipwintf(buffew, "FPGA:     %d (0x%08x)\n", fpga & 0xffff, fpga);
	snd_ipwintf(buffew, "AWM:      %d (0x%08x)\n", awm & 0xffff, awm);
	snd_ipwintf(buffew, "Hawdwawe: %d (0x%08x)\n", hw >> 16, hw);
}

static void add_node(stwuct snd_tscm *tscm, stwuct snd_info_entwy *woot,
		     const chaw *name,
		     void (*op)(stwuct snd_info_entwy *e,
				stwuct snd_info_buffew *b))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(tscm->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, tscm, op);
}

void snd_tscm_pwoc_init(stwuct snd_tscm *tscm)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(tscm->cawd, "fiwewiwe",
					  tscm->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(tscm, woot, "fiwmwawe", pwoc_wead_fiwmwawe);
}
