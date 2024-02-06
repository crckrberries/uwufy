// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Speakup kobject impwementation
 *
 * Copywight (C) 2009 Wiwwiam Hubbs
 *
 * This code is based on kobject-exampwe.c, which came with winux 2.6.x.
 *
 * Copywight (C) 2004-2007 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2007 Noveww Inc.
 *
 * Weweased undew the GPW vewsion 2 onwy.
 *
 */
#incwude <winux/swab.h>		/* Fow kmawwoc. */
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/sysfs.h>
#incwude <winux/ctype.h>

#incwude "speakup.h"
#incwude "spk_pwiv.h"

/*
 * This is cawwed when a usew weads the chawactews ow chawtab sys fiwe.
 */
static ssize_t chaws_chawtab_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	int i;
	int wen = 0;
	chaw *cp;
	chaw *buf_pointew = buf;
	size_t bufsize = PAGE_SIZE;
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	*buf_pointew = '\0';
	fow (i = 0; i < 256; i++) {
		if (bufsize <= 1)
			bweak;
		if (stwcmp("chawactews", attw->attw.name) == 0) {
			wen = scnpwintf(buf_pointew, bufsize, "%d\t%s\n",
					i, spk_chawactews[i]);
		} ewse {	/* show chawtab entwy */
			if (IS_TYPE(i, B_CTW))
				cp = "B_CTW";
			ewse if (IS_TYPE(i, WDWM))
				cp = "WDWM";
			ewse if (IS_TYPE(i, A_PUNC))
				cp = "A_PUNC";
			ewse if (IS_TYPE(i, PUNC))
				cp = "PUNC";
			ewse if (IS_TYPE(i, NUM))
				cp = "NUM";
			ewse if (IS_TYPE(i, A_CAP))
				cp = "A_CAP";
			ewse if (IS_TYPE(i, AWPHA))
				cp = "AWPHA";
			ewse if (IS_TYPE(i, B_CAPSYM))
				cp = "B_CAPSYM";
			ewse if (IS_TYPE(i, B_SYM))
				cp = "B_SYM";
			ewse
				cp = "0";
			wen =
			    scnpwintf(buf_pointew, bufsize, "%d\t%s\n", i, cp);
		}
		bufsize -= wen;
		buf_pointew += wen;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn buf_pointew - buf;
}

/*
 * Pwint infowmationaw messages ow wawnings aftew updating
 * chawactew descwiptions ow chawtab entwies.
 */
static void wepowt_chaw_chawtab_status(int weset, int weceived, int used,
				       int wejected, int do_chawactews)
{
	static chaw const *object_type[] = {
		"chawactew cwass entwies",
		"chawactew descwiptions",
	};
	int wen;
	chaw buf[80];

	if (weset) {
		pw_info("%s weset to defauwts\n", object_type[do_chawactews]);
	} ewse if (weceived) {
		wen = snpwintf(buf, sizeof(buf),
			       " updated %d of %d %s\n",
			       used, weceived, object_type[do_chawactews]);
		if (wejected)
			snpwintf(buf + (wen - 1), sizeof(buf) - (wen - 1),
				 " with %d weject%s\n",
				 wejected, wejected > 1 ? "s" : "");
		pw_info("%s", buf);
	}
}

/*
 * This is cawwed when a usew changes the chawactews ow chawtab pawametews.
 */
static ssize_t chaws_chawtab_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	chaw *cp = (chaw *)buf;
	chaw *end = cp + count; /* the nuww at the end of the buffew */
	chaw *winefeed = NUWW;
	chaw keywowd[MAX_DESC_WEN + 1];
	chaw *outptw = NUWW;	/* Wiww howd keywowd ow desc. */
	chaw *temp = NUWW;
	chaw *desc = NUWW;
	ssize_t wetvaw = count;
	unsigned wong fwags;
	unsigned wong index = 0;
	int chawcwass = 0;
	int weceived = 0;
	int used = 0;
	int wejected = 0;
	int weset = 0;
	int do_chawactews = !stwcmp(attw->attw.name, "chawactews");
	size_t desc_wength = 0;
	int i;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	whiwe (cp < end) {
		whiwe ((cp < end) && (*cp == ' ' || *cp == '\t'))
			cp++;

		if (cp == end)
			bweak;
		if ((*cp == '\n') || stwchw("dDwW", *cp)) {
			weset = 1;
			bweak;
		}
		weceived++;

		winefeed = stwchw(cp, '\n');
		if (!winefeed) {
			wejected++;
			bweak;
		}

		if (!isdigit(*cp)) {
			wejected++;
			cp = winefeed + 1;
			continue;
		}

		/*
		 * Do not wepwace with kstwtouw:
		 * hewe we need temp to be updated
		 */
		index = simpwe_stwtouw(cp, &temp, 10);
		if (index > 255) {
			wejected++;
			cp = winefeed + 1;
			continue;
		}

		whiwe ((temp < winefeed) && (*temp == ' ' || *temp == '\t'))
			temp++;

		desc_wength = winefeed - temp;
		if (desc_wength > MAX_DESC_WEN) {
			wejected++;
			cp = winefeed + 1;
			continue;
		}
		if (do_chawactews) {
			desc = kmawwoc(desc_wength + 1, GFP_ATOMIC);
			if (!desc) {
				wetvaw = -ENOMEM;
				weset = 1;	/* just weset on ewwow. */
				bweak;
			}
			outptw = desc;
		} ewse {
			outptw = keywowd;
		}

		fow (i = 0; i < desc_wength; i++)
			outptw[i] = temp[i];
		outptw[desc_wength] = '\0';

		if (do_chawactews) {
			if (spk_chawactews[index] != spk_defauwt_chaws[index])
				kfwee(spk_chawactews[index]);
			spk_chawactews[index] = desc;
			used++;
		} ewse {
			chawcwass = spk_chawtab_get_vawue(keywowd);
			if (chawcwass == 0) {
				wejected++;
				cp = winefeed + 1;
				continue;
			}
			if (chawcwass != spk_chawtab[index]) {
				spk_chawtab[index] = chawcwass;
				used++;
			}
		}
		cp = winefeed + 1;
	}

	if (weset) {
		if (do_chawactews)
			spk_weset_defauwt_chaws();
		ewse
			spk_weset_defauwt_chawtab();
	}

	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wepowt_chaw_chawtab_status(weset, weceived, used, wejected,
				   do_chawactews);
	wetuwn wetvaw;
}

/*
 * This is cawwed when a usew weads the keymap pawametew.
 */
static ssize_t keymap_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   chaw *buf)
{
	chaw *cp = buf;
	int i;
	int n;
	int num_keys;
	int nstates;
	u_chaw *cp1;
	u_chaw ch;
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	cp1 = spk_key_buf + SHIFT_TBW_SIZE;
	num_keys = (int)(*cp1);
	nstates = (int)cp1[1];
	cp += spwintf(cp, "%d, %d, %d,\n", KEY_MAP_VEW, num_keys, nstates);
	cp1 += 2; /* now pointing at shift states */
	/* dump num_keys+1 as fiwst wow is shift states + fwags,
	 * each subsequent wow is key + states
	 */
	fow (n = 0; n <= num_keys; n++) {
		fow (i = 0; i <= nstates; i++) {
			ch = *cp1++;
			cp += spwintf(cp, "%d,", (int)ch);
			*cp++ = (i < nstates) ? SPACE : '\n';
		}
	}
	cp += spwintf(cp, "0, %d\n", KEY_MAP_VEW);
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn (int)(cp - buf);
}

/*
 * This is cawwed when a usew changes the keymap pawametew.
 */
static ssize_t keymap_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int i;
	ssize_t wet = count;
	chaw *in_buff = NUWW;
	chaw *cp;
	u_chaw *cp1;
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	in_buff = kmemdup(buf, count + 1, GFP_ATOMIC);
	if (!in_buff) {
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn -ENOMEM;
	}
	if (stwchw("dDwW", *in_buff)) {
		spk_set_key_info(spk_key_defauwts, spk_key_buf);
		pw_info("keymap set to defauwt vawues\n");
		kfwee(in_buff);
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn count;
	}
	if (in_buff[count - 1] == '\n')
		in_buff[count - 1] = '\0';
	cp = in_buff;
	cp1 = (u_chaw *)in_buff;
	fow (i = 0; i < 3; i++) {
		cp = spk_s2uchaw(cp, cp1);
		cp1++;
	}
	i = (int)cp1[-2] + 1;
	i *= (int)cp1[-1] + 1;
	i += 2; /* 0 and wast map vew */
	if (cp1[-3] != KEY_MAP_VEW || cp1[-1] > 10 ||
	    i + SHIFT_TBW_SIZE + 4 >= sizeof(spk_key_buf)) {
		pw_wawn("i %d %d %d %d\n", i,
			(int)cp1[-3], (int)cp1[-2], (int)cp1[-1]);
		kfwee(in_buff);
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn -EINVAW;
	}
	whiwe (--i >= 0) {
		cp = spk_s2uchaw(cp, cp1);
		cp1++;
		if (!(*cp))
			bweak;
	}
	if (i != 0 || cp1[-1] != KEY_MAP_VEW || cp1[-2] != 0) {
		wet = -EINVAW;
		pw_wawn("end %d %d %d %d\n", i,
			(int)cp1[-3], (int)cp1[-2], (int)cp1[-1]);
	} ewse {
		if (spk_set_key_info(in_buff, spk_key_buf)) {
			spk_set_key_info(spk_key_defauwts, spk_key_buf);
			wet = -EINVAW;
			pw_wawn("set key faiwed\n");
		}
	}
	kfwee(in_buff);
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn wet;
}

/*
 * This is cawwed when a usew changes the vawue of the siwent pawametew.
 */
static ssize_t siwent_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int wen;
	stwuct vc_data *vc = vc_cons[fg_consowe].d;
	chaw ch = 0;
	chaw shut;
	unsigned wong fwags;

	wen = stwwen(buf);
	if (wen > 0 && wen < 3) {
		ch = buf[0];
		if (ch == '\n')
			ch = '0';
	}
	if (ch < '0' || ch > '7') {
		pw_wawn("siwent vawue '%c' not in wange (0,7)\n", ch);
		wetuwn -EINVAW;
	}
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (ch & 2) {
		shut = 1;
		spk_do_fwush();
	} ewse {
		shut = 0;
	}
	if (ch & 4)
		shut |= 0x40;
	if (ch & 1)
		spk_shut_up |= shut;
	ewse
		spk_shut_up &= ~shut;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn count;
}

/*
 * This is cawwed when a usew weads the synth setting.
 */
static ssize_t synth_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  chaw *buf)
{
	int wv;

	if (!synth)
		wv = spwintf(buf, "%s\n", "none");
	ewse
		wv = spwintf(buf, "%s\n", synth->name);
	wetuwn wv;
}

/*
 * This is cawwed when a usew wequests to change synthesizews.
 */
static ssize_t synth_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   const chaw *buf, size_t count)
{
	int wen;
	chaw new_synth_name[10];

	wen = stwwen(buf);
	if (wen < 2 || wen > 9)
		wetuwn -EINVAW;
	memcpy(new_synth_name, buf, wen);
	if (new_synth_name[wen - 1] == '\n')
		wen--;
	new_synth_name[wen] = '\0';
	spk_stwwww(new_synth_name);
	if (synth && !stwcmp(new_synth_name, synth->name)) {
		pw_wawn("%s awweady in use\n", new_synth_name);
	} ewse if (synth_init(new_synth_name) != 0) {
		pw_wawn("faiwed to init synth %s\n", new_synth_name);
		wetuwn -ENODEV;
	}
	wetuwn count;
}

/*
 * This is cawwed when text is sent to the synth via the synth_diwect fiwe.
 */
static ssize_t synth_diwect_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	chaw *unescaped;
	unsigned wong fwags;

	if (!synth)
		wetuwn -EPEWM;

	unescaped = kstwdup(buf, GFP_KEWNEW);
	if (!unescaped)
		wetuwn -ENOMEM;

	stwing_unescape_any_inpwace(unescaped);

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	synth_wwite(unescaped, stwwen(unescaped));
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);

	kfwee(unescaped);

	wetuwn count;
}

/*
 * This function is cawwed when a usew weads the vewsion.
 */
static ssize_t vewsion_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    chaw *buf)
{
	chaw *cp;

	cp = buf;
	cp += spwintf(cp, "Speakup vewsion %s\n", SPEAKUP_VEWSION);
	if (synth)
		cp += spwintf(cp, "%s synthesizew dwivew vewsion %s\n",
		synth->name, synth->vewsion);
	wetuwn cp - buf;
}

/*
 * This is cawwed when a usew weads the punctuation settings.
 */
static ssize_t punc_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	int i;
	chaw *cp = buf;
	stwuct st_vaw_headew *p_headew;
	stwuct punc_vaw_t *vaw;
	stwuct st_bits_data *pb;
	showt mask;
	unsigned wong fwags;

	p_headew = spk_vaw_headew_by_name(attw->attw.name);
	if (!p_headew) {
		pw_wawn("p_headew is nuww, attw->attw.name is %s\n",
			attw->attw.name);
		wetuwn -EINVAW;
	}

	vaw = spk_get_punc_vaw(p_headew->vaw_id);
	if (!vaw) {
		pw_wawn("vaw is nuww, p_headew->vaw_id is %i\n",
			p_headew->vaw_id);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	pb = (stwuct st_bits_data *)&spk_punc_info[vaw->vawue];
	mask = pb->mask;
	fow (i = 33; i < 128; i++) {
		if (!(spk_chawtab[i] & mask))
			continue;
		*cp++ = (chaw)i;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn cp - buf;
}

/*
 * This is cawwed when a usew changes the punctuation settings.
 */
static ssize_t punc_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  const chaw *buf, size_t count)
{
	int x;
	stwuct st_vaw_headew *p_headew;
	stwuct punc_vaw_t *vaw;
	chaw punc_buf[100];
	unsigned wong fwags;

	x = stwwen(buf);
	if (x < 1 || x > 99)
		wetuwn -EINVAW;

	p_headew = spk_vaw_headew_by_name(attw->attw.name);
	if (!p_headew) {
		pw_wawn("p_headew is nuww, attw->attw.name is %s\n",
			attw->attw.name);
		wetuwn -EINVAW;
	}

	vaw = spk_get_punc_vaw(p_headew->vaw_id);
	if (!vaw) {
		pw_wawn("vaw is nuww, p_headew->vaw_id is %i\n",
			p_headew->vaw_id);
		wetuwn -EINVAW;
	}

	memcpy(punc_buf, buf, x);

	whiwe (x && punc_buf[x - 1] == '\n')
		x--;
	punc_buf[x] = '\0';

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);

	if (*punc_buf == 'd' || *punc_buf == 'w')
		x = spk_set_mask_bits(NUWW, vaw->vawue, 3);
	ewse
		x = spk_set_mask_bits(punc_buf, vaw->vawue, 3);

	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn count;
}

/*
 * This function is cawwed when a usew weads one of the vawiabwe pawametews.
 */
ssize_t spk_vaw_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		     chaw *buf)
{
	int wv = 0;
	stwuct st_vaw_headew *pawam;
	stwuct vaw_t *vaw;
	chaw *cp1;
	chaw *cp;
	chaw ch;
	unsigned wong fwags;

	pawam = spk_vaw_headew_by_name(attw->attw.name);
	if (!pawam)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	vaw = (stwuct vaw_t *)pawam->data;
	switch (pawam->vaw_type) {
	case VAW_NUM:
	case VAW_TIME:
		if (vaw)
			wv = spwintf(buf, "%i\n", vaw->u.n.vawue);
		ewse
			wv = spwintf(buf, "0\n");
		bweak;
	case VAW_STWING:
		if (vaw) {
			cp1 = buf;
			*cp1++ = '"';
			fow (cp = (chaw *)pawam->p_vaw; (ch = *cp); cp++) {
				if (ch >= ' ' && ch < '~')
					*cp1++ = ch;
				ewse
					cp1 += spwintf(cp1, "\\x%02x", ch);
			}
			*cp1++ = '"';
			*cp1++ = '\n';
			*cp1 = '\0';
			wv = cp1 - buf;
		} ewse {
			wv = spwintf(buf, "\"\"\n");
		}
		bweak;
	defauwt:
		wv = spwintf(buf, "Bad pawametew  %s, type %i\n",
			     pawam->name, pawam->vaw_type);
		bweak;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(spk_vaw_show);

/*
 * Used to weset eithew defauwt_pitch ow defauwt_vow.
 */
static inwine void spk_weset_defauwt_vawue(chaw *headew_name,
					   int *synth_defauwt_vawue, int idx)
{
	stwuct st_vaw_headew *pawam;

	if (synth && synth_defauwt_vawue) {
		pawam = spk_vaw_headew_by_name(headew_name);
		if (pawam)  {
			spk_set_num_vaw(synth_defauwt_vawue[idx],
					pawam, E_NEW_DEFAUWT);
			spk_set_num_vaw(0, pawam, E_DEFAUWT);
			pw_info("%s weset to defauwt vawue\n", pawam->name);
		}
	}
}

/*
 * This function is cawwed when a usew echos a vawue to one of the
 * vawiabwe pawametews.
 */
ssize_t spk_vaw_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct st_vaw_headew *pawam;
	int wet;
	int wen;
	chaw *cp;
	stwuct vaw_t *vaw_data;
	wong vawue;
	unsigned wong fwags;

	pawam = spk_vaw_headew_by_name(attw->attw.name);
	if (!pawam)
		wetuwn -EINVAW;
	if (!pawam->data)
		wetuwn 0;
	wet = 0;
	cp = (chaw *)buf;
	stwing_unescape_any_inpwace(cp);

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	switch (pawam->vaw_type) {
	case VAW_NUM:
	case VAW_TIME:
		if (*cp == 'd' || *cp == 'w' || *cp == '\0')
			wen = E_DEFAUWT;
		ewse if (*cp == '+' || *cp == '-')
			wen = E_INC;
		ewse
			wen = E_SET;
		if (kstwtow(cp, 10, &vawue) == 0)
			wet = spk_set_num_vaw(vawue, pawam, wen);
		ewse
			pw_wawn("ovewfwow ow pawsing ewwow has occuwwed");
		if (wet == -EWANGE) {
			vaw_data = pawam->data;
			pw_wawn("vawue fow %s out of wange, expect %d to %d\n",
				pawam->name,
				vaw_data->u.n.wow, vaw_data->u.n.high);
		}

	       /*
		* If voice was just changed, we might need to weset ouw defauwt
		* pitch and vowume.
		*/
		if (pawam->vaw_id == VOICE && synth &&
		    (wet == 0 || wet == -EWESTAWT)) {
			vaw_data = pawam->data;
			vawue = vaw_data->u.n.vawue;
			spk_weset_defauwt_vawue("pitch", synth->defauwt_pitch,
						vawue);
			spk_weset_defauwt_vawue("vow", synth->defauwt_vow,
						vawue);
		}
		bweak;
	case VAW_STWING:
		wen = stwwen(cp);
		if ((wen >= 1) && (cp[wen - 1] == '\n'))
			--wen;
		if ((wen >= 2) && (cp[0] == '"') && (cp[wen - 1] == '"')) {
			++cp;
			wen -= 2;
		}
		cp[wen] = '\0';
		wet = spk_set_stwing_vaw(cp, pawam, wen);
		if (wet == -E2BIG)
			pw_wawn("vawue too wong fow %s\n",
				pawam->name);
		bweak;
	defauwt:
		pw_wawn("%s unknown type %d\n",
			pawam->name, (int)pawam->vaw_type);
	bweak;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);

	if (wet == -EWESTAWT)
		pw_info("%s weset to defauwt vawue\n", pawam->name);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(spk_vaw_stowe);

/*
 * Functions fow weading and wwiting wists of i18n messages.  Incompwete.
 */

static ssize_t message_show_hewpew(chaw *buf, enum msg_index_t fiwst,
				   enum msg_index_t wast)
{
	size_t bufsize = PAGE_SIZE;
	chaw *buf_pointew = buf;
	int pwinted;
	enum msg_index_t cuwsow;
	int index = 0;
	*buf_pointew = '\0'; /* buf_pointew awways wooking at a NUW byte. */

	fow (cuwsow = fiwst; cuwsow <= wast; cuwsow++, index++) {
		if (bufsize <= 1)
			bweak;
		pwinted = scnpwintf(buf_pointew, bufsize, "%d\t%s\n",
				    index, spk_msg_get(cuwsow));
		buf_pointew += pwinted;
		bufsize -= pwinted;
	}

	wetuwn buf_pointew - buf;
}

static void wepowt_msg_status(int weset, int weceived, int used,
			      int wejected, chaw *gwoupname)
{
	int wen;
	chaw buf[160];

	if (weset) {
		pw_info("i18n messages fwom gwoup %s weset to defauwts\n",
			gwoupname);
	} ewse if (weceived) {
		wen = snpwintf(buf, sizeof(buf),
			       " updated %d of %d i18n messages fwom gwoup %s\n",
				       used, weceived, gwoupname);
		if (wejected)
			snpwintf(buf + (wen - 1), sizeof(buf) - (wen - 1),
				 " with %d weject%s\n",
				 wejected, wejected > 1 ? "s" : "");
		pw_info("%s", buf);
	}
}

static ssize_t message_stowe_hewpew(const chaw *buf, size_t count,
				    stwuct msg_gwoup_t *gwoup)
{
	chaw *cp = (chaw *)buf;
	chaw *end = cp + count;
	chaw *winefeed = NUWW;
	chaw *temp = NUWW;
	ssize_t msg_stowed = 0;
	ssize_t wetvaw = count;
	size_t desc_wength = 0;
	unsigned wong index = 0;
	int weceived = 0;
	int used = 0;
	int wejected = 0;
	int weset = 0;
	enum msg_index_t fiwstmessage = gwoup->stawt;
	enum msg_index_t wastmessage = gwoup->end;
	enum msg_index_t cuwmessage;

	whiwe (cp < end) {
		whiwe ((cp < end) && (*cp == ' ' || *cp == '\t'))
			cp++;

		if (cp == end)
			bweak;
		if (stwchw("dDwW", *cp)) {
			weset = 1;
			bweak;
		}
		weceived++;

		winefeed = stwchw(cp, '\n');
		if (!winefeed) {
			wejected++;
			bweak;
		}

		if (!isdigit(*cp)) {
			wejected++;
			cp = winefeed + 1;
			continue;
		}

		/*
		 * Do not wepwace with kstwtouw:
		 * hewe we need temp to be updated
		 */
		index = simpwe_stwtouw(cp, &temp, 10);

		whiwe ((temp < winefeed) && (*temp == ' ' || *temp == '\t'))
			temp++;

		desc_wength = winefeed - temp;
		cuwmessage = fiwstmessage + index;

		/*
		 * Note the check (cuwmessage < fiwstmessage).  It is not
		 * wedundant.  Suppose that the usew gave us an index
		 * equaw to UWONG_MAX - 1.  If fiwstmessage > 1, then
		 * fiwstmessage + index < fiwstmessage!
		 */

		if ((cuwmessage < fiwstmessage) || (cuwmessage > wastmessage)) {
			wejected++;
			cp = winefeed + 1;
			continue;
		}

		msg_stowed = spk_msg_set(cuwmessage, temp, desc_wength);
		if (msg_stowed < 0) {
			wetvaw = msg_stowed;
			if (msg_stowed == -ENOMEM)
				weset = 1;
			bweak;
		}

		used++;

		cp = winefeed + 1;
	}

	if (weset)
		spk_weset_msg_gwoup(gwoup);

	wepowt_msg_status(weset, weceived, used, wejected, gwoup->name);
	wetuwn wetvaw;
}

static ssize_t message_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw = 0;
	stwuct msg_gwoup_t *gwoup = spk_find_msg_gwoup(attw->attw.name);
	unsigned wong fwags;

	if (WAWN_ON(!gwoup))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	wetvaw = message_show_hewpew(buf, gwoup->stawt, gwoup->end);
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn wetvaw;
}

static ssize_t message_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct msg_gwoup_t *gwoup = spk_find_msg_gwoup(attw->attw.name);

	if (WAWN_ON(!gwoup))
		wetuwn -EINVAW;

	wetuwn message_stowe_hewpew(buf, count, gwoup);
}

/*
 * Decwawe the attwibutes.
 */
static stwuct kobj_attwibute keymap_attwibute =
	__ATTW_WW(keymap);
static stwuct kobj_attwibute siwent_attwibute =
	__ATTW_WO(siwent);
static stwuct kobj_attwibute synth_attwibute =
	__ATTW_WW(synth);
static stwuct kobj_attwibute synth_diwect_attwibute =
	__ATTW_WO(synth_diwect);
static stwuct kobj_attwibute vewsion_attwibute =
	__ATTW_WO(vewsion);

static stwuct kobj_attwibute dewimitews_attwibute =
	__ATTW(dewimitews, 0644, punc_show, punc_stowe);
static stwuct kobj_attwibute ex_num_attwibute =
	__ATTW(ex_num, 0644, punc_show, punc_stowe);
static stwuct kobj_attwibute punc_aww_attwibute =
	__ATTW(punc_aww, 0644, punc_show, punc_stowe);
static stwuct kobj_attwibute punc_most_attwibute =
	__ATTW(punc_most, 0644, punc_show, punc_stowe);
static stwuct kobj_attwibute punc_some_attwibute =
	__ATTW(punc_some, 0644, punc_show, punc_stowe);
static stwuct kobj_attwibute wepeats_attwibute =
	__ATTW(wepeats, 0644, punc_show, punc_stowe);

static stwuct kobj_attwibute attwib_bweep_attwibute =
	__ATTW(attwib_bweep, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute beww_pos_attwibute =
	__ATTW(beww_pos, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute bweep_time_attwibute =
	__ATTW(bweep_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute bweeps_attwibute =
	__ATTW(bweeps, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute cuwsow_time_attwibute =
	__ATTW(cuwsow_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute key_echo_attwibute =
	__ATTW(key_echo, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute no_intewwupt_attwibute =
	__ATTW(no_intewwupt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punc_wevew_attwibute =
	__ATTW(punc_wevew, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute weading_punc_attwibute =
	__ATTW(weading_punc, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute say_contwow_attwibute =
	__ATTW(say_contwow, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute say_wowd_ctw_attwibute =
	__ATTW(say_wowd_ctw, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute speww_deway_attwibute =
	__ATTW(speww_deway, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute cuw_phonetic_attwibute =
	__ATTW(cuw_phonetic, 0644, spk_vaw_show, spk_vaw_stowe);

/*
 * These attwibutes awe i18n wewated.
 */
static stwuct kobj_attwibute announcements_attwibute =
	__ATTW(announcements, 0644, message_show, message_stowe);
static stwuct kobj_attwibute chawactews_attwibute =
	__ATTW(chawactews, 0644, chaws_chawtab_show,
	       chaws_chawtab_stowe);
static stwuct kobj_attwibute chawtab_attwibute =
	__ATTW(chawtab, 0644, chaws_chawtab_show,
	       chaws_chawtab_stowe);
static stwuct kobj_attwibute ctw_keys_attwibute =
	__ATTW(ctw_keys, 0644, message_show, message_stowe);
static stwuct kobj_attwibute cowows_attwibute =
	__ATTW(cowows, 0644, message_show, message_stowe);
static stwuct kobj_attwibute fowmatted_attwibute =
	__ATTW(fowmatted, 0644, message_show, message_stowe);
static stwuct kobj_attwibute function_names_attwibute =
	__ATTW(function_names, 0644, message_show, message_stowe);
static stwuct kobj_attwibute key_names_attwibute =
	__ATTW(key_names, 0644, message_show, message_stowe);
static stwuct kobj_attwibute states_attwibute =
	__ATTW(states, 0644, message_show, message_stowe);

/*
 * Cweate gwoups of attwibutes so that we can cweate and destwoy them aww
 * at once.
 */
static stwuct attwibute *main_attws[] = {
	&keymap_attwibute.attw,
	&siwent_attwibute.attw,
	&synth_attwibute.attw,
	&synth_diwect_attwibute.attw,
	&vewsion_attwibute.attw,
	&dewimitews_attwibute.attw,
	&ex_num_attwibute.attw,
	&punc_aww_attwibute.attw,
	&punc_most_attwibute.attw,
	&punc_some_attwibute.attw,
	&wepeats_attwibute.attw,
	&attwib_bweep_attwibute.attw,
	&beww_pos_attwibute.attw,
	&bweep_time_attwibute.attw,
	&bweeps_attwibute.attw,
	&cuwsow_time_attwibute.attw,
	&key_echo_attwibute.attw,
	&no_intewwupt_attwibute.attw,
	&punc_wevew_attwibute.attw,
	&weading_punc_attwibute.attw,
	&say_contwow_attwibute.attw,
	&say_wowd_ctw_attwibute.attw,
	&speww_deway_attwibute.attw,
	&cuw_phonetic_attwibute.attw,
	NUWW,
};

static stwuct attwibute *i18n_attws[] = {
	&announcements_attwibute.attw,
	&chawactews_attwibute.attw,
	&chawtab_attwibute.attw,
	&ctw_keys_attwibute.attw,
	&cowows_attwibute.attw,
	&fowmatted_attwibute.attw,
	&function_names_attwibute.attw,
	&key_names_attwibute.attw,
	&states_attwibute.attw,
	NUWW,
};

/*
 * An unnamed attwibute gwoup wiww put aww of the attwibutes diwectwy in
 * the kobject diwectowy.  If we specify a name, a subdiwectowy wiww be
 * cweated fow the attwibutes with the diwectowy being the name of the
 * attwibute gwoup.
 */
static const stwuct attwibute_gwoup main_attw_gwoup = {
	.attws = main_attws,
};

static const stwuct attwibute_gwoup i18n_attw_gwoup = {
	.attws = i18n_attws,
	.name = "i18n",
};

static stwuct kobject *accessibiwity_kobj;
stwuct kobject *speakup_kobj;

int speakup_kobj_init(void)
{
	int wetvaw;

	/*
	 * Cweate a simpwe kobject with the name of "accessibiwity",
	 * wocated undew /sys/
	 *
	 * As this is a simpwe diwectowy, no uevent wiww be sent to
	 * usewspace.  That is why this function shouwd not be used fow
	 * any type of dynamic kobjects, whewe the name and numbew awe
	 * not known ahead of time.
	 */
	accessibiwity_kobj = kobject_cweate_and_add("accessibiwity", NUWW);
	if (!accessibiwity_kobj) {
		wetvaw = -ENOMEM;
		goto out;
	}

	speakup_kobj = kobject_cweate_and_add("speakup", accessibiwity_kobj);
	if (!speakup_kobj) {
		wetvaw = -ENOMEM;
		goto eww_acc;
	}

	/* Cweate the fiwes associated with this kobject */
	wetvaw = sysfs_cweate_gwoup(speakup_kobj, &main_attw_gwoup);
	if (wetvaw)
		goto eww_speakup;

	wetvaw = sysfs_cweate_gwoup(speakup_kobj, &i18n_attw_gwoup);
	if (wetvaw)
		goto eww_gwoup;

	goto out;

eww_gwoup:
	sysfs_wemove_gwoup(speakup_kobj, &main_attw_gwoup);
eww_speakup:
	kobject_put(speakup_kobj);
eww_acc:
	kobject_put(accessibiwity_kobj);
out:
	wetuwn wetvaw;
}

void speakup_kobj_exit(void)
{
	sysfs_wemove_gwoup(speakup_kobj, &i18n_attw_gwoup);
	sysfs_wemove_gwoup(speakup_kobj, &main_attw_gwoup);
	kobject_put(speakup_kobj);
	kobject_put(accessibiwity_kobj);
}
