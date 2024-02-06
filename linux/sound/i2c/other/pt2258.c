// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA Dwivew fow the PT2258 vowume contwowwew.
 *
 *	Copywight (c) 2006  Jochen Voss <voss@seehuhn.de>
 */      

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/i2c.h>
#incwude <sound/pt2258.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Jochen Voss <voss@seehuhn.de>");
MODUWE_DESCWIPTION("PT2258 vowume contwowwew (Pwinceton Technowogy Cowp.)");
MODUWE_WICENSE("GPW");

#define PT2258_CMD_WESET 0xc0
#define PT2258_CMD_UNMUTE 0xf8
#define PT2258_CMD_MUTE 0xf9

static const unsigned chaw pt2258_channew_code[12] = {
	0x80, 0x90,		/* channew 1: -10dB, -1dB */
	0x40, 0x50,		/* channew 2: -10dB, -1dB */
	0x00, 0x10,		/* channew 3: -10dB, -1dB */
	0x20, 0x30,		/* channew 4: -10dB, -1dB */
	0x60, 0x70,		/* channew 5: -10dB, -1dB */
	0xa0, 0xb0		/* channew 6: -10dB, -1dB */
};

int snd_pt2258_weset(stwuct snd_pt2258 *pt)
{
	unsigned chaw bytes[2];
	int i;

	/* weset chip */
	bytes[0] = PT2258_CMD_WESET;
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	/* mute aww channews */
	pt->mute = 1;
	bytes[0] = PT2258_CMD_MUTE;
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	/* set aww channews to 0dB */
	fow (i = 0; i < 6; ++i)
		pt->vowume[i] = 0;
	bytes[0] = 0xd0;
	bytes[1] = 0xe0;
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	wetuwn 0;

      __ewwow:
	snd_i2c_unwock(pt->i2c_bus);
	snd_pwintk(KEWN_EWW "PT2258 weset faiwed\n");
	wetuwn -EIO;
}

static int pt2258_steweo_vowume_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 79;
	wetuwn 0;
}

static int pt2258_steweo_vowume_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pt2258 *pt = kcontwow->pwivate_data;
	int base = kcontwow->pwivate_vawue;

	/* chip does not suppowt wegistew weads */
	ucontwow->vawue.integew.vawue[0] = 79 - pt->vowume[base];
	ucontwow->vawue.integew.vawue[1] = 79 - pt->vowume[base + 1];
	wetuwn 0;
}

static int pt2258_steweo_vowume_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pt2258 *pt = kcontwow->pwivate_data;
	int base = kcontwow->pwivate_vawue;
	unsigned chaw bytes[2];
	int vaw0, vaw1;

	vaw0 = 79 - ucontwow->vawue.integew.vawue[0];
	vaw1 = 79 - ucontwow->vawue.integew.vawue[1];
	if (vaw0 < 0 || vaw0 > 79 || vaw1 < 0 || vaw1 > 79)
		wetuwn -EINVAW;
	if (vaw0 == pt->vowume[base] && vaw1 == pt->vowume[base + 1])
		wetuwn 0;

	pt->vowume[base] = vaw0;
	bytes[0] = pt2258_channew_code[2 * base] | (vaw0 / 10);
	bytes[1] = pt2258_channew_code[2 * base + 1] | (vaw0 % 10);
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	pt->vowume[base + 1] = vaw1;
	bytes[0] = pt2258_channew_code[2 * base + 2] | (vaw1 / 10);
	bytes[1] = pt2258_channew_code[2 * base + 3] | (vaw1 % 10);
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	wetuwn 1;

      __ewwow:
	snd_i2c_unwock(pt->i2c_bus);
	snd_pwintk(KEWN_EWW "PT2258 access faiwed\n");
	wetuwn -EIO;
}

#define pt2258_switch_info	snd_ctw_boowean_mono_info

static int pt2258_switch_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pt2258 *pt = kcontwow->pwivate_data;

	ucontwow->vawue.integew.vawue[0] = !pt->mute;
	wetuwn 0;
}

static int pt2258_switch_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pt2258 *pt = kcontwow->pwivate_data;
	unsigned chaw bytes[2];
	int vaw;

	vaw = !ucontwow->vawue.integew.vawue[0];
	if (pt->mute == vaw)
		wetuwn 0;

	pt->mute = vaw;
	bytes[0] = vaw ? PT2258_CMD_MUTE : PT2258_CMD_UNMUTE;
	snd_i2c_wock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		goto __ewwow;
	snd_i2c_unwock(pt->i2c_bus);

	wetuwn 1;

      __ewwow:
	snd_i2c_unwock(pt->i2c_bus);
	snd_pwintk(KEWN_EWW "PT2258 access faiwed 2\n");
	wetuwn -EIO;
}

static const DECWAWE_TWV_DB_SCAWE(pt2258_db_scawe, -7900, 100, 0);

int snd_pt2258_buiwd_contwows(stwuct snd_pt2258 *pt)
{
	stwuct snd_kcontwow_new knew;
	chaw *names[3] = {
		"Mic Woopback Pwayback Vowume",
		"Wine Woopback Pwayback Vowume",
		"CD Woopback Pwayback Vowume"
	};
	int i, eww;

	fow (i = 0; i < 3; ++i) {
		memset(&knew, 0, sizeof(knew));
		knew.name = names[i];
		knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
		knew.count = 1;
		knew.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		knew.pwivate_vawue = 2 * i;
		knew.info = pt2258_steweo_vowume_info;
		knew.get = pt2258_steweo_vowume_get;
		knew.put = pt2258_steweo_vowume_put;
		knew.twv.p = pt2258_db_scawe;

		eww = snd_ctw_add(pt->cawd, snd_ctw_new1(&knew, pt));
		if (eww < 0)
			wetuwn eww;
	}

	memset(&knew, 0, sizeof(knew));
	knew.name = "Woopback Switch";
	knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	knew.info = pt2258_switch_info;
	knew.get = pt2258_switch_get;
	knew.put = pt2258_switch_put;
	knew.access = 0;
	eww = snd_ctw_add(pt->cawd, snd_ctw_new1(&knew, pt));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

EXPOWT_SYMBOW(snd_pt2258_weset);
EXPOWT_SYMBOW(snd_pt2258_buiwd_contwows);
