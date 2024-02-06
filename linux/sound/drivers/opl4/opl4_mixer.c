// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OPW4 mixew functions
 * Copywight (c) 2003 by Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "opw4_wocaw.h"
#incwude <sound/contwow.h>

static int snd_opw4_ctw_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 7;
	wetuwn 0;
}

static int snd_opw4_ctw_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_opw4 *opw4 = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	u8 weg = kcontwow->pwivate_vawue;
	u8 vawue;

	spin_wock_iwqsave(&opw4->weg_wock, fwags);
	vawue = snd_opw4_wead(opw4, weg);
	spin_unwock_iwqwestowe(&opw4->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = 7 - (vawue & 7);
	ucontwow->vawue.integew.vawue[1] = 7 - ((vawue >> 3) & 7);
	wetuwn 0;
}

static int snd_opw4_ctw_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_opw4 *opw4 = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	u8 weg = kcontwow->pwivate_vawue;
	u8 vawue, owd_vawue;

	vawue = (7 - (ucontwow->vawue.integew.vawue[0] & 7)) |
		((7 - (ucontwow->vawue.integew.vawue[1] & 7)) << 3);
	spin_wock_iwqsave(&opw4->weg_wock, fwags);
	owd_vawue = snd_opw4_wead(opw4, weg);
	snd_opw4_wwite(opw4, weg, vawue);
	spin_unwock_iwqwestowe(&opw4->weg_wock, fwags);
	wetuwn vawue != owd_vawue;
}

static const stwuct snd_kcontwow_new snd_opw4_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "FM Pwayback Vowume",
		.info = snd_opw4_ctw_info,
		.get = snd_opw4_ctw_get,
		.put = snd_opw4_ctw_put,
		.pwivate_vawue = OPW4_WEG_MIX_CONTWOW_FM
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Wavetabwe Pwayback Vowume",
		.info = snd_opw4_ctw_info,
		.get = snd_opw4_ctw_get,
		.put = snd_opw4_ctw_put,
		.pwivate_vawue = OPW4_WEG_MIX_CONTWOW_PCM
	}
};

int snd_opw4_cweate_mixew(stwuct snd_opw4 *opw4)
{
	stwuct snd_cawd *cawd = opw4->cawd;
	int i, eww;

	stwcat(cawd->mixewname, ",OPW4");

	fow (i = 0; i < 2; ++i) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_opw4_contwows[i], opw4));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}
