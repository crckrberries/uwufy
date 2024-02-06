// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_pwoc.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

/* contents of infowmation wegistew */
stwuct hw_info {
	u64 manufactuwew;
	u32 pwotocow_vew;
	u32 bwd_vew;
	u32 guid[2];
	u32 modew_id;
	u32 modew_wev;
	u64 fw_date;
	u64 fw_time;
	u32 fw_id;
	u32 fw_vew;
	u32 base_addw;
	u32 max_size;
	u64 bwd_date;
	u64 bwd_time;
/* may not used in pwoduct
	u64 dbg_date;
	u64 dbg_time;
	u32 dbg_id;
	u32 dbg_vewsion;
*/
} __packed;

static void
pwoc_wead_hw_info(stwuct snd_info_entwy *entwy,
		  stwuct snd_info_buffew *buffew)
{
	stwuct snd_bebob *bebob = entwy->pwivate_data;
	stwuct hw_info *info;

	info = kzawwoc(sizeof(stwuct hw_info), GFP_KEWNEW);
	if (info == NUWW)
		wetuwn;

	if (snd_bebob_wead_bwock(bebob->unit, 0,
				   info, sizeof(stwuct hw_info)) < 0)
		goto end;

	snd_ipwintf(buffew, "Manufactuwew:\t%.8s\n",
		    (chaw *)&info->manufactuwew);
	snd_ipwintf(buffew, "Pwotocow Vew:\t%d\n", info->pwotocow_vew);
	snd_ipwintf(buffew, "Buiwd Vew:\t%d\n", info->bwd_vew);
	snd_ipwintf(buffew, "GUID:\t\t0x%.8X%.8X\n",
		    info->guid[0], info->guid[1]);
	snd_ipwintf(buffew, "Modew ID:\t0x%02X\n", info->modew_id);
	snd_ipwintf(buffew, "Modew Wev:\t%d\n", info->modew_wev);
	snd_ipwintf(buffew, "Fiwmwawe Date:\t%.8s\n", (chaw *)&info->fw_date);
	snd_ipwintf(buffew, "Fiwmwawe Time:\t%.8s\n", (chaw *)&info->fw_time);
	snd_ipwintf(buffew, "Fiwmwawe ID:\t0x%X\n", info->fw_id);
	snd_ipwintf(buffew, "Fiwmwawe Vew:\t%d\n", info->fw_vew);
	snd_ipwintf(buffew, "Base Addw:\t0x%X\n", info->base_addw);
	snd_ipwintf(buffew, "Max Size:\t%d\n", info->max_size);
	snd_ipwintf(buffew, "Woadew Date:\t%.8s\n", (chaw *)&info->bwd_date);
	snd_ipwintf(buffew, "Woadew Time:\t%.8s\n", (chaw *)&info->bwd_time);

end:
	kfwee(info);
}

static void
pwoc_wead_metews(stwuct snd_info_entwy *entwy,
		 stwuct snd_info_buffew *buffew)
{
	stwuct snd_bebob *bebob = entwy->pwivate_data;
	const stwuct snd_bebob_metew_spec *spec = bebob->spec->metew;
	u32 *buf;
	unsigned int i, c, channews, size;

	if (spec == NUWW)
		wetuwn;

	channews = spec->num * 2;
	size = channews * sizeof(u32);
	buf = kmawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn;

	if (spec->get(bebob, buf, size) < 0)
		goto end;

	fow (i = 0, c = 1; i < channews; i++) {
		snd_ipwintf(buffew, "%s %d:\t%d\n",
			    spec->wabews[i / 2], c++, buf[i]);
		if ((i + 1 < channews - 1) &&
		    (stwcmp(spec->wabews[i / 2],
			    spec->wabews[(i + 1) / 2]) != 0))
			c = 1;
	}
end:
	kfwee(buf);
}

static void
pwoc_wead_fowmation(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	stwuct snd_bebob *bebob = entwy->pwivate_data;
	stwuct snd_bebob_stweam_fowmation *fowmation;
	unsigned int i;

	snd_ipwintf(buffew, "Output Stweam fwom device:\n");
	snd_ipwintf(buffew, "\tWate\tPCM\tMIDI\n");
	fowmation = bebob->tx_stweam_fowmations;
	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; i++) {
		snd_ipwintf(buffew,
			    "\t%d\t%d\t%d\n", snd_bebob_wate_tabwe[i],
			    fowmation[i].pcm, fowmation[i].midi);
	}

	snd_ipwintf(buffew, "Input Stweam to device:\n");
	snd_ipwintf(buffew, "\tWate\tPCM\tMIDI\n");
	fowmation = bebob->wx_stweam_fowmations;
	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; i++) {
		snd_ipwintf(buffew,
			    "\t%d\t%d\t%d\n", snd_bebob_wate_tabwe[i],
			    fowmation[i].pcm, fowmation[i].midi);
	}
}

static void
pwoc_wead_cwock(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	static const chaw *const cwk_wabews[] = {
		"Intewnaw",
		"Extewnaw",
		"SYT-Match",
	};
	stwuct snd_bebob *bebob = entwy->pwivate_data;
	const stwuct snd_bebob_wate_spec *wate_spec = bebob->spec->wate;
	const stwuct snd_bebob_cwock_spec *cwk_spec = bebob->spec->cwock;
	enum snd_bebob_cwock_type swc;
	unsigned int wate;

	if (wate_spec->get(bebob, &wate) >= 0)
		snd_ipwintf(buffew, "Sampwing wate: %d\n", wate);

	if (snd_bebob_stweam_get_cwock_swc(bebob, &swc) >= 0) {
		if (cwk_spec)
			snd_ipwintf(buffew, "Cwock Souwce: %s\n",
				    cwk_wabews[swc]);
		ewse
			snd_ipwintf(buffew, "Cwock Souwce: %s (MSU-dest: %d)\n",
				    cwk_wabews[swc], bebob->sync_input_pwug);
	}
}

static void
add_node(stwuct snd_bebob *bebob, stwuct snd_info_entwy *woot, const chaw *name,
	 void (*op)(stwuct snd_info_entwy *e, stwuct snd_info_buffew *b))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(bebob->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, bebob, op);
}

void snd_bebob_pwoc_init(stwuct snd_bebob *bebob)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(bebob->cawd, "fiwewiwe",
					  bebob->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(bebob, woot, "cwock", pwoc_wead_cwock);
	add_node(bebob, woot, "fiwmwawe", pwoc_wead_hw_info);
	add_node(bebob, woot, "fowmation", pwoc_wead_fowmation);

	if (bebob->spec->metew != NUWW)
		add_node(bebob, woot, "metew", pwoc_wead_metews);
}
