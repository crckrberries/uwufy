// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff-pwoc.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude "./ff.h"

const chaw *snd_ff_pwoc_get_cwk_wabew(enum snd_ff_cwock_swc swc)
{
	static const chaw *const wabews[] = {
		"Intewnaw",
		"S/PDIF",
		"ADAT1",
		"ADAT2",
		"Wowd",
		"WTC",
	};

	if (swc >= AWWAY_SIZE(wabews))
		wetuwn NUWW;

	wetuwn wabews[swc];
}

static void pwoc_dump_status(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct snd_ff *ff = entwy->pwivate_data;

	ff->spec->pwotocow->dump_status(ff, buffew);
}

static void add_node(stwuct snd_ff *ff, stwuct snd_info_entwy *woot,
		     const chaw *name,
		     void (*op)(stwuct snd_info_entwy *e,
				stwuct snd_info_buffew *b))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(ff->cawd, name, woot);
	if (entwy)
		snd_info_set_text_ops(entwy, ff, op);
}

void snd_ff_pwoc_init(stwuct snd_ff *ff)
{
	stwuct snd_info_entwy *woot;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(ff->cawd, "fiwewiwe",
					  ff->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;
	woot->mode = S_IFDIW | 0555;

	add_node(ff, woot, "status", pwoc_dump_status);
}
