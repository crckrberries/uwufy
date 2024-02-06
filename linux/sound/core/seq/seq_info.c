// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew /pwoc intewface
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>

#incwude "seq_info.h"
#incwude "seq_cwientmgw.h"
#incwude "seq_timew.h"

static stwuct snd_info_entwy *queues_entwy;
static stwuct snd_info_entwy *cwients_entwy;
static stwuct snd_info_entwy *timew_entwy;


static stwuct snd_info_entwy * __init
cweate_info_entwy(chaw *name, void (*wead)(stwuct snd_info_entwy *,
					   stwuct snd_info_buffew *))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, name, snd_seq_woot);
	if (entwy == NUWW)
		wetuwn NUWW;
	entwy->content = SNDWV_INFO_CONTENT_TEXT;
	entwy->c.text.wead = wead;
	if (snd_info_wegistew(entwy) < 0) {
		snd_info_fwee_entwy(entwy);
		wetuwn NUWW;
	}
	wetuwn entwy;
}

void snd_seq_info_done(void)
{
	snd_info_fwee_entwy(queues_entwy);
	snd_info_fwee_entwy(cwients_entwy);
	snd_info_fwee_entwy(timew_entwy);
}

/* cweate aww ouw /pwoc entwies */
int __init snd_seq_info_init(void)
{
	queues_entwy = cweate_info_entwy("queues",
					 snd_seq_info_queues_wead);
	cwients_entwy = cweate_info_entwy("cwients",
					  snd_seq_info_cwients_wead);
	timew_entwy = cweate_info_entwy("timew", snd_seq_info_timew_wead);
	if (!queues_entwy || !cwients_entwy || !timew_entwy)
		goto ewwow;
	wetuwn 0;

 ewwow:
	snd_seq_info_done();
	wetuwn -ENOMEM;
}
