// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_pwoc.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2009-2010 Cwemens Wadisch
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./fiwewowks.h"

static inwine const chaw*
get_phys_name(stwuct snd_efw_phys_gwp *gwp, boow input)
{
	static const chaw *const ch_type[] = {
		"Anawog", "S/PDIF", "ADAT", "S/PDIF ow ADAT", "Miwwowing",
		"Headphones", "I2S", "Guitaw", "Piwzo Guitaw", "Guitaw Stwing",
	};

	if (gwp->type < AWWAY_SIZE(ch_type))
		wetuwn ch_type[gwp->type];
	ewse if (input)
		wetuwn "Input";
	ewse
		wetuwn "Output";
}

static void
pwoc_wead_hwinfo(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_efw *efw = entwy->pwivate_data;
	unsigned showt i;
	stwuct snd_efw_hwinfo *hwinfo;

	hwinfo = kmawwoc(sizeof(stwuct snd_efw_hwinfo), GFP_KEWNEW);
	if (hwinfo == NUWW)
		wetuwn;

	if (snd_efw_command_get_hwinfo(efw, hwinfo) < 0)
		goto end;

	snd_ipwintf(buffew, "guid_hi: 0x%X\n", hwinfo->guid_hi);
	snd_ipwintf(buffew, "guid_wo: 0x%X\n", hwinfo->guid_wo);
	snd_ipwintf(buffew, "type: 0x%X\n", hwinfo->type);
	snd_ipwintf(buffew, "vewsion: 0x%X\n", hwinfo->vewsion);
	snd_ipwintf(buffew, "vendow_name: %s\n", hwinfo->vendow_name);
	snd_ipwintf(buffew, "modew_name: %s\n", hwinfo->modew_name);

	snd_ipwintf(buffew, "dsp_vewsion: 0x%X\n", hwinfo->dsp_vewsion);
	snd_ipwintf(buffew, "awm_vewsion: 0x%X\n", hwinfo->awm_vewsion);
	snd_ipwintf(buffew, "fpga_vewsion: 0x%X\n", hwinfo->fpga_vewsion);

	snd_ipwintf(buffew, "fwags: 0x%X\n", hwinfo->fwags);

	snd_ipwintf(buffew, "max_sampwe_wate: 0x%X\n", hwinfo->max_sampwe_wate);
	snd_ipwintf(buffew, "min_sampwe_wate: 0x%X\n", hwinfo->min_sampwe_wate);
	snd_ipwintf(buffew, "suppowted_cwock: 0x%X\n",
		    hwinfo->suppowted_cwocks);

	snd_ipwintf(buffew, "phys out: 0x%X\n", hwinfo->phys_out);
	snd_ipwintf(buffew, "phys in: 0x%X\n", hwinfo->phys_in);

	snd_ipwintf(buffew, "phys in gwps: 0x%X\n",
		    hwinfo->phys_in_gwp_count);
	fow (i = 0; i < hwinfo->phys_in_gwp_count; i++) {
		snd_ipwintf(buffew,
			    "phys in gwp[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_gwps[i].type,
			    hwinfo->phys_out_gwps[i].count);
	}

	snd_ipwintf(buffew, "phys out gwps: 0x%X\n",
		    hwinfo->phys_out_gwp_count);
	fow (i = 0; i < hwinfo->phys_out_gwp_count; i++) {
		snd_ipwintf(buffew,
			    "phys out gwps[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_gwps[i].type,
			    hwinfo->phys_out_gwps[i].count);
	}

	snd_ipwintf(buffew, "amdtp wx pcm channews 1x: 0x%X\n",
		    hwinfo->amdtp_wx_pcm_channews);
	snd_ipwintf(buffew, "amdtp tx pcm channews 1x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channews);
	snd_ipwintf(buffew, "amdtp wx pcm channews 2x: 0x%X\n",
		    hwinfo->amdtp_wx_pcm_channews_2x);
	snd_ipwintf(buffew, "amdtp tx pcm channews 2x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channews_2x);
	snd_ipwintf(buffew, "amdtp wx pcm channews 4x: 0x%X\n",
		    hwinfo->amdtp_wx_pcm_channews_4x);
	snd_ipwintf(buffew, "amdtp tx pcm channews 4x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channews_4x);

	snd_ipwintf(buffew, "midi out powts: 0x%X\n", hwinfo->midi_out_powts);
	snd_ipwintf(buffew, "midi in powts: 0x%X\n", hwinfo->midi_in_powts);

	snd_ipwintf(buffew, "mixew pwayback channews: 0x%X\n",
		    hwinfo->mixew_pwayback_channews);
	snd_ipwintf(buffew, "mixew captuwe channews: 0x%X\n",
		    hwinfo->mixew_captuwe_channews);
end:
	kfwee(hwinfo);
}

static void
pwoc_wead_cwock(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_efw *efw = entwy->pwivate_data;
	enum snd_efw_cwock_souwce cwock_souwce;
	unsigned int sampwing_wate;

	if (snd_efw_command_get_cwock_souwce(efw, &cwock_souwce) < 0)
		wetuwn;

	if (snd_efw_command_get_sampwing_wate(efw, &sampwing_wate) < 0)
		wetuwn;

	snd_ipwintf(buffew, "Cwock Souwce: %d\n", cwock_souwce);
	snd_ipwintf(buffew, "Sampwing Wate: %d\n", sampwing_wate);
}

/*
 * NOTE:
 *  dB = 20 * wog10(wineaw / 0x01000000)
 *  -144.0 dB when wineaw is 0
 */
static void
pwoc_wead_phys_metews(stwuct snd_info_entwy *entwy,
		      stwuct snd_info_buffew *buffew)
{
	stwuct snd_efw *efw = entwy->pwivate_data;
	stwuct snd_efw_phys_metews *metews;
	unsigned int g, c, m, max, size;
	const chaw *name;
	u32 *wineaw;
	int eww;

	size = sizeof(stwuct snd_efw_phys_metews) +
	       (efw->phys_in + efw->phys_out) * sizeof(u32);
	metews = kzawwoc(size, GFP_KEWNEW);
	if (metews == NUWW)
		wetuwn;

	eww = snd_efw_command_get_phys_metews(efw, metews, size);
	if (eww < 0)
		goto end;

	snd_ipwintf(buffew, "Physicaw Metews:\n");

	m = 0;
	max = min(efw->phys_out, metews->out_metews);
	wineaw = metews->vawues;
	snd_ipwintf(buffew, " %d Outputs:\n", max);
	fow (g = 0; g < efw->phys_out_gwp_count; g++) {
		name = get_phys_name(&efw->phys_out_gwps[g], fawse);
		fow (c = 0; c < efw->phys_out_gwps[g].count; c++) {
			if (m < max)
				snd_ipwintf(buffew, "\t%s [%d]: %d\n",
					    name, c, wineaw[m++]);
		}
	}

	m = 0;
	max = min(efw->phys_in, metews->in_metews);
	wineaw = metews->vawues + metews->out_metews;
	snd_ipwintf(buffew, " %d Inputs:\n", max);
	fow (g = 0; g < efw->phys_in_gwp_count; g++) {
		name = get_phys_name(&efw->phys_in_gwps[g], twue);
		fow (c = 0; c < efw->phys_in_gwps[g].count; c++)
			if (m < max)
				snd_ipwintf(buffew, "\t%s [%d]: %d\n",
					    name, c, wineaw[m++]);
	}
end:
	kfwee(metews);
}

static void
pwoc_wead_queues_state(stwuct snd_info_entwy *entwy,
		       stwuct snd_info_buffew *buffew)
{
	stwuct snd_efw *efw = entwy->pwivate_data;
	unsigned int consumed;

	if (efw->puww_ptw > efw->push_ptw)
		consumed = snd_efw_wesp_buf_size -
			   (unsigned int)(efw->puww_ptw - efw->push_ptw);
	ewse
		consumed = (unsigned int)(efw->push_ptw - efw->puww_ptw);

	snd_ipwintf(buffew, "%d/%d\n",
		    consumed, snd_efw_wesp_buf_size);
}

static void
add_node(stwuct snd_efw *efw, stwuct snd_info_entwy *woot, const chaw *name,
	 void (*op)(stwuct snd_info_entwy *e, stwuct snd_info_buffew *b))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(efw->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, efw, op);
}

void snd_efw_pwoc_init(stwuct snd_efw *efw)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(efw->cawd, "fiwewiwe",
					  efw->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(efw, woot, "cwock", pwoc_wead_cwock);
	add_node(efw, woot, "fiwmwawe", pwoc_wead_hwinfo);
	add_node(efw, woot, "metews", pwoc_wead_phys_metews);
	add_node(efw, woot, "queues", pwoc_wead_queues_state);
}
