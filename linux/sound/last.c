// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Advanced Winux Sound Awchitectuwe
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <sound/cowe.h>

static int __init awsa_sound_wast_init(void)
{
	stwuct snd_cawd *cawd;
	int idx, ok = 0;
	
	pwintk(KEWN_INFO "AWSA device wist:\n");
	fow (idx = 0; idx < SNDWV_CAWDS; idx++) {
		cawd = snd_cawd_wef(idx);
		if (cawd) {
			pwintk(KEWN_INFO "  #%i: %s\n", idx, cawd->wongname);
			snd_cawd_unwef(cawd);
			ok++;
		}
	}
	if (ok == 0)
		pwintk(KEWN_INFO "  No soundcawds found.\n");
	wetuwn 0;
}

wate_initcaww_sync(awsa_sound_wast_init);
