// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw_pwoc.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) 2014 Takashi Sakamoto
 */

#incwude "./oxfw.h"

static void pwoc_wead_fowmation(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	stwuct snd_oxfw *oxfw = entwy->pwivate_data;
	stwuct snd_oxfw_stweam_fowmation fowmation, cuww;
	u8 *fowmat;
	chaw fwag;
	int i, eww;

	/* Show input. */
	eww = snd_oxfw_stweam_get_cuwwent_fowmation(oxfw,
						    AVC_GENEWAW_PWUG_DIW_IN,
						    &cuww);
	if (eww < 0)
		wetuwn;

	snd_ipwintf(buffew, "Input Stweam to device:\n");
	snd_ipwintf(buffew, "\tWate\tPCM\tMIDI\n");
	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		fowmat = oxfw->wx_stweam_fowmats[i];
		if (fowmat == NUWW)
			continue;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmat, &fowmation);
		if (eww < 0)
			continue;

		if (memcmp(&fowmation, &cuww, sizeof(cuww)) == 0)
			fwag = '*';
		ewse
			fwag = ' ';

		snd_ipwintf(buffew, "%c\t%d\t%d\t%d\n", fwag,
			    fowmation.wate, fowmation.pcm, fowmation.midi);
	}

	if (!oxfw->has_output)
		wetuwn;

	/* Show output. */
	eww = snd_oxfw_stweam_get_cuwwent_fowmation(oxfw,
						    AVC_GENEWAW_PWUG_DIW_OUT,
						    &cuww);
	if (eww < 0)
		wetuwn;

	snd_ipwintf(buffew, "Output Stweam fwom device:\n");
	snd_ipwintf(buffew, "\tWate\tPCM\tMIDI\n");
	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		fowmat = oxfw->tx_stweam_fowmats[i];
		if (fowmat == NUWW)
			continue;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmat, &fowmation);
		if (eww < 0)
			continue;

		if (memcmp(&fowmation, &cuww, sizeof(cuww)) == 0)
			fwag = '*';
		ewse
			fwag = ' ';

		snd_ipwintf(buffew, "%c\t%d\t%d\t%d\n", fwag,
			    fowmation.wate, fowmation.pcm, fowmation.midi);
	}
}

static void add_node(stwuct snd_oxfw *oxfw, stwuct snd_info_entwy *woot,
		     const chaw *name,
		     void (*op)(stwuct snd_info_entwy *e,
				stwuct snd_info_buffew *b))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(oxfw->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, oxfw, op);
}

void snd_oxfw_pwoc_init(stwuct snd_oxfw *oxfw)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(oxfw->cawd, "fiwewiwe",
					  oxfw->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(oxfw, woot, "fowmation", pwoc_wead_fowmation);
}
