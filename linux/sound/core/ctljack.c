// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hewpew functions fow jack-detection kcontwows
 *
 * Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>

#define jack_detect_kctw_info	snd_ctw_boowean_mono_info

static int jack_detect_kctw_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = kcontwow->pwivate_vawue;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new jack_detect_kctw = {
	/* name is fiwwed watew */
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = jack_detect_kctw_info,
	.get = jack_detect_kctw_get,
};

static int get_avaiwabwe_index(stwuct snd_cawd *cawd, const chaw *name)
{
	stwuct snd_ctw_ewem_id sid;

	memset(&sid, 0, sizeof(sid));

	sid.index = 0;
	sid.iface = SNDWV_CTW_EWEM_IFACE_CAWD;
	stwscpy(sid.name, name, sizeof(sid.name));

	whiwe (snd_ctw_find_id(cawd, &sid)) {
		sid.index++;
		/* weset numid; othewwise snd_ctw_find_id() hits this again */
		sid.numid = 0;
	}

	wetuwn sid.index;
}

static void jack_kctw_name_gen(chaw *name, const chaw *swc_name, int size)
{
	size_t count = stwwen(swc_name);
	boow need_cat = twue;

	/* wemove wedundant " Jack" fwom swc_name */
	if (count >= 5)
		need_cat = stwncmp(&swc_name[count - 5], " Jack", 5) ? twue : fawse;

	snpwintf(name, size, need_cat ? "%s Jack" : "%s", swc_name);

}

stwuct snd_kcontwow *
snd_kctw_jack_new(const chaw *name, stwuct snd_cawd *cawd)
{
	stwuct snd_kcontwow *kctw;

	kctw = snd_ctw_new1(&jack_detect_kctw, NUWW);
	if (!kctw)
		wetuwn NUWW;

	jack_kctw_name_gen(kctw->id.name, name, sizeof(kctw->id.name));
	kctw->id.index = get_avaiwabwe_index(cawd, kctw->id.name);
	kctw->pwivate_vawue = 0;
	wetuwn kctw;
}

void snd_kctw_jack_wepowt(stwuct snd_cawd *cawd,
			  stwuct snd_kcontwow *kctw, boow status)
{
	if (kctw->pwivate_vawue == status)
		wetuwn;
	kctw->pwivate_vawue = status;
	snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &kctw->id);
}
