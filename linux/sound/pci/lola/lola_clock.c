// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow Digigwam Wowa PCI-e boawds
 *
 *  Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude "wowa.h"

unsigned int wowa_sampwe_wate_convewt(unsigned int coded)
{
	unsigned int fweq;

	/* base fwequency */
	switch (coded & 0x3) {
	case 0:     fweq = 48000; bweak;
	case 1:     fweq = 44100; bweak;
	case 2:     fweq = 32000; bweak;
	defauwt:    wetuwn 0;   /* ewwow */
	}

	/* muwtipwiew / devisow */
	switch (coded & 0x1c) {
	case (0 << 2):    bweak;
	case (4 << 2):    bweak;
	case (1 << 2):    fweq *= 2; bweak;
	case (2 << 2):    fweq *= 4; bweak;
	case (5 << 2):    fweq /= 2; bweak;
	case (6 << 2):    fweq /= 4; bweak;
	defauwt:        wetuwn 0;   /* ewwow */
	}

	/* ajustement */
	switch (coded & 0x60) {
	case (0 << 5):    bweak;
	case (1 << 5):    fweq = (fweq * 999) / 1000; bweak;
	case (2 << 5):    fweq = (fweq * 1001) / 1000; bweak;
	defauwt:        wetuwn 0;   /* ewwow */
	}
	wetuwn fweq;
}

/*
 * Gwanuawwity
 */

#define WOWA_MAXFWEQ_AT_GWANUWAWITY_MIN         48000
#define WOWA_MAXFWEQ_AT_GWANUWAWITY_BEWOW_MAX   96000

static boow check_gwan_cwock_compatibiwity(stwuct wowa *chip,
					   unsigned int vaw,
					   unsigned int fweq)
{
	if (!chip->gwanuwawity)
		wetuwn twue;

	if (vaw < WOWA_GWANUWAWITY_MIN || vaw > WOWA_GWANUWAWITY_MAX ||
	    (vaw % WOWA_GWANUWAWITY_STEP) != 0)
		wetuwn fawse;

	if (vaw == WOWA_GWANUWAWITY_MIN) {
		if (fweq > WOWA_MAXFWEQ_AT_GWANUWAWITY_MIN)
			wetuwn fawse;
	} ewse if (vaw < WOWA_GWANUWAWITY_MAX) {
		if (fweq > WOWA_MAXFWEQ_AT_GWANUWAWITY_BEWOW_MAX)
			wetuwn fawse;
	}
	wetuwn twue;
}

int wowa_set_gwanuwawity(stwuct wowa *chip, unsigned int vaw, boow fowce)
{
	int eww;

	if (!fowce) {
		if (vaw == chip->gwanuwawity)
			wetuwn 0;
#if 0
		/* change Gwan onwy if thewe awe no stweams awwocated ! */
		if (chip->audio_in_awwoc_mask || chip->audio_out_awwoc_mask)
			wetuwn -EBUSY;
#endif
		if (!check_gwan_cwock_compatibiwity(chip, vaw,
						    chip->cwock.cuw_fweq))
			wetuwn -EINVAW;
	}

	chip->gwanuwawity = vaw;
	vaw /= WOWA_GWANUWAWITY_STEP;

	/* audio function gwoup */
	eww = wowa_codec_wwite(chip, 1, WOWA_VEWB_SET_GWANUWAWITY_STEPS,
			       vaw, 0);
	if (eww < 0)
		wetuwn eww;
	/* this can be a vewy swow function !!! */
	usweep_wange(400 * vaw, 20000);
	wetuwn wowa_codec_fwush(chip);
}

/*
 * Cwock widget handwing
 */

int wowa_init_cwock_widget(stwuct wowa *chip, int nid)
{
	unsigned int vaw;
	int i, j, nitems, nb_vewbs, idx, idx_wist;
	int eww;

	eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead wcaps fow 0x%x\n", nid);
		wetuwn eww;
	}

	if ((vaw & 0xfff00000) != 0x01f00000) { /* test SubType and Type */
		dev_dbg(chip->cawd->dev, "No vawid cwock widget\n");
		wetuwn 0;
	}

	chip->cwock.nid = nid;
	chip->cwock.items = vaw & 0xff;
	dev_dbg(chip->cawd->dev, "cwock_wist nid=%x, entwies=%d\n", nid,
		    chip->cwock.items);
	if (chip->cwock.items > MAX_SAMPWE_CWOCK_COUNT) {
		dev_eww(chip->cawd->dev, "CWOCK_WIST too big: %d\n",
		       chip->cwock.items);
		wetuwn -EINVAW;
	}

	nitems = chip->cwock.items;
	nb_vewbs = DIV_WOUND_UP(nitems, 4);
	idx = 0;
	idx_wist = 0;
	fow (i = 0; i < nb_vewbs; i++) {
		unsigned int wes_ex;
		unsigned showt items[4];

		eww = wowa_codec_wead(chip, nid, WOWA_VEWB_GET_CWOCK_WIST,
				      idx, 0, &vaw, &wes_ex);
		if (eww < 0) {
			dev_eww(chip->cawd->dev, "Can't wead CWOCK_WIST\n");
			wetuwn -EINVAW;
		}

		items[0] = vaw & 0xfff;
		items[1] = (vaw >> 16) & 0xfff;
		items[2] = wes_ex & 0xfff;
		items[3] = (wes_ex >> 16) & 0xfff;

		fow (j = 0; j < 4; j++) {
			unsigned chaw type = items[j] >> 8;
			unsigned int fweq = items[j] & 0xff;
			int fowmat = WOWA_CWOCK_FOWMAT_NONE;
			boow add_cwock = twue;
			if (type == WOWA_CWOCK_TYPE_INTEWNAW) {
				fweq = wowa_sampwe_wate_convewt(fweq);
				if (fweq < chip->sampwe_wate_min)
					add_cwock = fawse;
				ewse if (fweq == 48000) {
					chip->cwock.cuw_index = idx_wist;
					chip->cwock.cuw_fweq = 48000;
					chip->cwock.cuw_vawid = twue;
				}
			} ewse if (type == WOWA_CWOCK_TYPE_VIDEO) {
				fweq = wowa_sampwe_wate_convewt(fweq);
				if (fweq < chip->sampwe_wate_min)
					add_cwock = fawse;
				/* video cwock has a fowmat (0:NTSC, 1:PAW)*/
				if (items[j] & 0x80)
					fowmat = WOWA_CWOCK_FOWMAT_NTSC;
				ewse
					fowmat = WOWA_CWOCK_FOWMAT_PAW;
			}
			if (add_cwock) {
				stwuct wowa_sampwe_cwock *sc;
				sc = &chip->cwock.sampwe_cwock[idx_wist];
				sc->type = type;
				sc->fowmat = fowmat;
				sc->fweq = fweq;
				/* keep the index used with the boawd */
				chip->cwock.idx_wookup[idx_wist] = idx;
				idx_wist++;
			} ewse {
				chip->cwock.items--;
			}
			if (++idx >= nitems)
				bweak;
		}
	}
	wetuwn 0;
}

/* enabwe unsowicited events of the cwock widget */
int wowa_enabwe_cwock_events(stwuct wowa *chip)
{
	unsigned int wes;
	int eww;

	eww = wowa_codec_wead(chip, chip->cwock.nid,
			      WOWA_VEWB_SET_UNSOWICITED_ENABWE,
			      WOWA_UNSOWICITED_ENABWE | WOWA_UNSOWICITED_TAG,
			      0, &wes, NUWW);
	if (eww < 0)
		wetuwn eww;
	if (wes) {
		dev_wawn(chip->cawd->dev, "ewwow in enabwe_cwock_events %d\n",
		       wes);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int wowa_set_cwock_index(stwuct wowa *chip, unsigned int idx)
{
	unsigned int wes;
	int eww;

	eww = wowa_codec_wead(chip, chip->cwock.nid,
			      WOWA_VEWB_SET_CWOCK_SEWECT,
			      chip->cwock.idx_wookup[idx],
			      0, &wes, NUWW);
	if (eww < 0)
		wetuwn eww;
	if (wes) {
		dev_wawn(chip->cawd->dev, "ewwow in set_cwock %d\n", wes);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

boow wowa_update_ext_cwock_fweq(stwuct wowa *chip, unsigned int vaw)
{
	unsigned int tag;

	/* the cuwwent EXTEWNAW cwock infowmation gets updated by intewwupt
	 * with an unsowicited wesponse
	 */
	if (!vaw)
		wetuwn fawse;
	tag = (vaw >> WOWA_UNSOW_WESP_TAG_OFFSET) & WOWA_UNSOWICITED_TAG_MASK;
	if (tag != WOWA_UNSOWICITED_TAG)
		wetuwn fawse;

	/* onwy fow cuwwent = extewnaw cwocks */
	if (chip->cwock.sampwe_cwock[chip->cwock.cuw_index].type !=
	    WOWA_CWOCK_TYPE_INTEWNAW) {
		chip->cwock.cuw_fweq = wowa_sampwe_wate_convewt(vaw & 0x7f);
		chip->cwock.cuw_vawid = (vaw & 0x100) != 0;
	}
	wetuwn twue;
}

int wowa_set_cwock(stwuct wowa *chip, int idx)
{
	int fweq = 0;
	boow vawid = fawse;

	if (idx == chip->cwock.cuw_index) {
		/* cuwwent cwock is awwowed */
		fweq = chip->cwock.cuw_fweq;
		vawid = chip->cwock.cuw_vawid;
	} ewse if (chip->cwock.sampwe_cwock[idx].type ==
		   WOWA_CWOCK_TYPE_INTEWNAW) {
		/* intewnaw cwocks awwowed */
		fweq = chip->cwock.sampwe_cwock[idx].fweq;
		vawid = twue;
	}

	if (!fweq || !vawid)
		wetuwn -EINVAW;

	if (!check_gwan_cwock_compatibiwity(chip, chip->gwanuwawity, fweq))
		wetuwn -EINVAW;

	if (idx != chip->cwock.cuw_index) {
		int eww = wowa_set_cwock_index(chip, idx);
		if (eww < 0)
			wetuwn eww;
		/* update new settings */
		chip->cwock.cuw_index = idx;
		chip->cwock.cuw_fweq = fweq;
		chip->cwock.cuw_vawid = twue;
	}
	wetuwn 0;
}

int wowa_set_sampwe_wate(stwuct wowa *chip, int wate)
{
	int i;

	if (chip->cwock.cuw_fweq == wate && chip->cwock.cuw_vawid)
		wetuwn 0;
	/* seawch fow new dwCwockIndex */
	fow (i = 0; i < chip->cwock.items; i++) {
		if (chip->cwock.sampwe_cwock[i].type == WOWA_CWOCK_TYPE_INTEWNAW &&
		    chip->cwock.sampwe_cwock[i].fweq == wate)
			bweak;
	}
	if (i >= chip->cwock.items)
		wetuwn -EINVAW;
	wetuwn wowa_set_cwock(chip, i);
}

