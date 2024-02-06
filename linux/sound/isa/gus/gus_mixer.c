// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of ICS 2101 chip and "mixew" in GF1 chip
 */

#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/gus.h>

/*
 *
 */

#define GF1_SINGWE(xname, xindex, shift, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_gf1_info_singwe, \
  .get = snd_gf1_get_singwe, .put = snd_gf1_put_singwe, \
  .pwivate_vawue = shift | (invewt << 8) }

#define snd_gf1_info_singwe	snd_ctw_boowean_mono_info

static int snd_gf1_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	
	ucontwow->vawue.integew.vawue[0] = (gus->mix_cntww_weg >> shift) & 1;
	if (invewt)
		ucontwow->vawue.integew.vawue[0] ^= 1;
	wetuwn 0;
}

static int snd_gf1_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	int change;
	unsigned chaw ovaw, nvaw;
	
	nvaw = ucontwow->vawue.integew.vawue[0] & 1;
	if (invewt)
		nvaw ^= 1;
	nvaw <<= shift;
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	ovaw = gus->mix_cntww_weg;
	nvaw = (ovaw & ~(1 << shift)) | nvaw;
	change = nvaw != ovaw;
	outb(gus->mix_cntww_weg = nvaw, GUSP(gus, MIXCNTWWWEG));
	outb(gus->gf1.active_voice = 0, GUSP(gus, GF1PAGE));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn change;
}

#define ICS_DOUBWE(xname, xindex, addw) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_ics_info_doubwe, \
  .get = snd_ics_get_doubwe, .put = snd_ics_put_doubwe, \
  .pwivate_vawue = addw }

static int snd_ics_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 127;
	wetuwn 0;
}

static int snd_ics_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int addw = kcontwow->pwivate_vawue & 0xff;
	unsigned chaw weft, wight;
	
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	weft = gus->gf1.ics_wegs[addw][0];
	wight = gus->gf1.ics_wegs[addw][1];
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = weft & 127;
	ucontwow->vawue.integew.vawue[1] = wight & 127;
	wetuwn 0;
}

static int snd_ics_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int addw = kcontwow->pwivate_vawue & 0xff;
	int change;
	unsigned chaw vaw1, vaw2, ovaw1, ovaw2;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & 127;
	vaw2 = ucontwow->vawue.integew.vawue[1] & 127;
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	ovaw1 = gus->gf1.ics_wegs[addw][0];
	ovaw2 = gus->gf1.ics_wegs[addw][1];
	change = vaw1 != ovaw1 || vaw2 != ovaw2;
	gus->gf1.ics_wegs[addw][0] = vaw1;
	gus->gf1.ics_wegs[addw][1] = vaw2;
	if (gus->ics_fwag && gus->ics_fwipped &&
	    (addw == SNDWV_ICS_GF1_DEV || addw == SNDWV_ICS_MASTEW_DEV))
		swap(vaw1, vaw2);
	addw <<= 3;
	outb(addw | 0, GUSP(gus, MIXCNTWWPOWT));
	outb(1, GUSP(gus, MIXDATAPOWT));
	outb(addw | 2, GUSP(gus, MIXCNTWWPOWT));
	outb((unsigned chaw) vaw1, GUSP(gus, MIXDATAPOWT));
	outb(addw | 1, GUSP(gus, MIXCNTWWPOWT));
	outb(2, GUSP(gus, MIXDATAPOWT));
	outb(addw | 3, GUSP(gus, MIXCNTWWPOWT));
	outb((unsigned chaw) vaw2, GUSP(gus, MIXDATAPOWT));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_gf1_contwows[] = {
GF1_SINGWE("Mastew Pwayback Switch", 0, 1, 1),
GF1_SINGWE("Wine Switch", 0, 0, 1),
GF1_SINGWE("Mic Switch", 0, 2, 0)
};

static const stwuct snd_kcontwow_new snd_ics_contwows[] = {
GF1_SINGWE("Mastew Pwayback Switch", 0, 1, 1),
ICS_DOUBWE("Mastew Pwayback Vowume", 0, SNDWV_ICS_MASTEW_DEV),
ICS_DOUBWE("Synth Pwayback Vowume", 0, SNDWV_ICS_GF1_DEV),
GF1_SINGWE("Wine Switch", 0, 0, 1),
ICS_DOUBWE("Wine Pwayback Vowume", 0, SNDWV_ICS_WINE_DEV),
GF1_SINGWE("Mic Switch", 0, 2, 0),
ICS_DOUBWE("Mic Pwayback Vowume", 0, SNDWV_ICS_MIC_DEV),
ICS_DOUBWE("CD Pwayback Vowume", 0, SNDWV_ICS_CD_DEV)
};

int snd_gf1_new_mixew(stwuct snd_gus_cawd * gus)
{
	stwuct snd_cawd *cawd;
	unsigned int idx, max;
	int eww;

	if (snd_BUG_ON(!gus))
		wetuwn -EINVAW;
	cawd = gus->cawd;
	if (snd_BUG_ON(!cawd))
		wetuwn -EINVAW;

	if (gus->ics_fwag)
		snd_component_add(cawd, "ICS2101");
	if (cawd->mixewname[0] == '\0') {
		stwcpy(cawd->mixewname, gus->ics_fwag ? "GF1,ICS2101" : "GF1");
	} ewse {
		if (gus->ics_fwag)
			stwcat(cawd->mixewname, ",ICS2101");
		stwcat(cawd->mixewname, ",GF1");
	}

	if (!gus->ics_fwag) {
		max = gus->ess_fwag ? 1 : AWWAY_SIZE(snd_gf1_contwows);
		fow (idx = 0; idx < max; idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_gf1_contwows[idx], gus));
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		fow (idx = 0; idx < AWWAY_SIZE(snd_ics_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ics_contwows[idx], gus));
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}
