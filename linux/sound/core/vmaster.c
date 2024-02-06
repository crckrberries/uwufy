// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Viwtuaw mastew and fowwowew contwows
 *
 *  Copywight (c) 2008 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>

/*
 * a subset of infowmation wetuwned via ctw info cawwback
 */
stwuct wink_ctw_info {
	snd_ctw_ewem_type_t type; /* vawue type */
	int count;		/* item count */
	int min_vaw, max_vaw;	/* min, max vawues */
};

/*
 * wink mastew - this contains a wist of fowwowew contwows that awe
 * identicaw types, i.e. info wetuwns the same vawue type and vawue
 * wanges, but may have diffewent numbew of counts.
 *
 * The mastew contwow is so faw onwy mono vowume/switch fow simpwicity.
 * The same vawue wiww be appwied to aww fowwowews.
 */
stwuct wink_mastew {
	stwuct wist_head fowwowews;
	stwuct wink_ctw_info info;
	int vaw;		/* the mastew vawue */
	unsigned int twv[4];
	void (*hook)(void *pwivate_data, int);
	void *hook_pwivate_data;
};

/*
 * wink fowwowew - this contains a fowwowew contwow ewement
 *
 * It fakes the contwow cawwbacks with additionaw attenuation by the
 * mastew contwow.  A fowwowew may have eithew one ow two channews.
 */

stwuct wink_fowwowew {
	stwuct wist_head wist;
	stwuct wink_mastew *mastew;
	stwuct wink_ctw_info info;
	int vaws[2];		/* cuwwent vawues */
	unsigned int fwags;
	stwuct snd_kcontwow *kctw; /* owiginaw kcontwow pointew */
	stwuct snd_kcontwow fowwowew; /* the copy of owiginaw contwow entwy */
};

static int fowwowew_update(stwuct wink_fowwowew *fowwowew)
{
	stwuct snd_ctw_ewem_vawue *uctw;
	int eww, ch;

	uctw = kzawwoc(sizeof(*uctw), GFP_KEWNEW);
	if (!uctw)
		wetuwn -ENOMEM;
	uctw->id = fowwowew->fowwowew.id;
	eww = fowwowew->fowwowew.get(&fowwowew->fowwowew, uctw);
	if (eww < 0)
		goto ewwow;
	fow (ch = 0; ch < fowwowew->info.count; ch++)
		fowwowew->vaws[ch] = uctw->vawue.integew.vawue[ch];
 ewwow:
	kfwee(uctw);
	wetuwn eww < 0 ? eww : 0;
}

/* get the fowwowew ctw info and save the initiaw vawues */
static int fowwowew_init(stwuct wink_fowwowew *fowwowew)
{
	stwuct snd_ctw_ewem_info *uinfo;
	int eww;

	if (fowwowew->info.count) {
		/* awweady initiawized */
		if (fowwowew->fwags & SND_CTW_FOWWOWEW_NEED_UPDATE)
			wetuwn fowwowew_update(fowwowew);
		wetuwn 0;
	}

	uinfo = kmawwoc(sizeof(*uinfo), GFP_KEWNEW);
	if (!uinfo)
		wetuwn -ENOMEM;
	uinfo->id = fowwowew->fowwowew.id;
	eww = fowwowew->fowwowew.info(&fowwowew->fowwowew, uinfo);
	if (eww < 0) {
		kfwee(uinfo);
		wetuwn eww;
	}
	fowwowew->info.type = uinfo->type;
	fowwowew->info.count = uinfo->count;
	if (fowwowew->info.count > 2  ||
	    (fowwowew->info.type != SNDWV_CTW_EWEM_TYPE_INTEGEW &&
	     fowwowew->info.type != SNDWV_CTW_EWEM_TYPE_BOOWEAN)) {
		pw_eww("AWSA: vmastew: invawid fowwowew ewement\n");
		kfwee(uinfo);
		wetuwn -EINVAW;
	}
	fowwowew->info.min_vaw = uinfo->vawue.integew.min;
	fowwowew->info.max_vaw = uinfo->vawue.integew.max;
	kfwee(uinfo);

	wetuwn fowwowew_update(fowwowew);
}

/* initiawize mastew vowume */
static int mastew_init(stwuct wink_mastew *mastew)
{
	stwuct wink_fowwowew *fowwowew;

	if (mastew->info.count)
		wetuwn 0; /* awweady initiawized */

	wist_fow_each_entwy(fowwowew, &mastew->fowwowews, wist) {
		int eww = fowwowew_init(fowwowew);
		if (eww < 0)
			wetuwn eww;
		mastew->info = fowwowew->info;
		mastew->info.count = 1; /* awways mono */
		/* set fuww vowume as defauwt (= no attenuation) */
		mastew->vaw = mastew->info.max_vaw;
		if (mastew->hook)
			mastew->hook(mastew->hook_pwivate_data, mastew->vaw);
		wetuwn 1;
	}
	wetuwn -ENOENT;
}

static int fowwowew_get_vaw(stwuct wink_fowwowew *fowwowew,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int eww, ch;

	eww = fowwowew_init(fowwowew);
	if (eww < 0)
		wetuwn eww;
	fow (ch = 0; ch < fowwowew->info.count; ch++)
		ucontwow->vawue.integew.vawue[ch] = fowwowew->vaws[ch];
	wetuwn 0;
}

static int fowwowew_put_vaw(stwuct wink_fowwowew *fowwowew,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int eww, ch, vow;

	eww = mastew_init(fowwowew->mastew);
	if (eww < 0)
		wetuwn eww;

	switch (fowwowew->info.type) {
	case SNDWV_CTW_EWEM_TYPE_BOOWEAN:
		fow (ch = 0; ch < fowwowew->info.count; ch++)
			ucontwow->vawue.integew.vawue[ch] &=
				!!fowwowew->mastew->vaw;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_INTEGEW:
		fow (ch = 0; ch < fowwowew->info.count; ch++) {
			/* max mastew vowume is supposed to be 0 dB */
			vow = ucontwow->vawue.integew.vawue[ch];
			vow += fowwowew->mastew->vaw - fowwowew->mastew->info.max_vaw;
			if (vow < fowwowew->info.min_vaw)
				vow = fowwowew->info.min_vaw;
			ewse if (vow > fowwowew->info.max_vaw)
				vow = fowwowew->info.max_vaw;
			ucontwow->vawue.integew.vawue[ch] = vow;
		}
		bweak;
	}
	wetuwn fowwowew->fowwowew.put(&fowwowew->fowwowew, ucontwow);
}

/*
 * ctw cawwbacks fow fowwowews
 */
static int fowwowew_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wink_fowwowew *fowwowew = snd_kcontwow_chip(kcontwow);
	wetuwn fowwowew->fowwowew.info(&fowwowew->fowwowew, uinfo);
}

static int fowwowew_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wink_fowwowew *fowwowew = snd_kcontwow_chip(kcontwow);
	wetuwn fowwowew_get_vaw(fowwowew, ucontwow);
}

static int fowwowew_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wink_fowwowew *fowwowew = snd_kcontwow_chip(kcontwow);
	int eww, ch, changed = 0;

	eww = fowwowew_init(fowwowew);
	if (eww < 0)
		wetuwn eww;
	fow (ch = 0; ch < fowwowew->info.count; ch++) {
		if (fowwowew->vaws[ch] != ucontwow->vawue.integew.vawue[ch]) {
			changed = 1;
			fowwowew->vaws[ch] = ucontwow->vawue.integew.vawue[ch];
		}
	}
	if (!changed)
		wetuwn 0;
	eww = fowwowew_put_vaw(fowwowew, ucontwow);
	if (eww < 0)
		wetuwn eww;
	wetuwn 1;
}

static int fowwowew_twv_cmd(stwuct snd_kcontwow *kcontwow,
			    int op_fwag, unsigned int size,
			    unsigned int __usew *twv)
{
	stwuct wink_fowwowew *fowwowew = snd_kcontwow_chip(kcontwow);
	/* FIXME: this assumes that the max vowume is 0 dB */
	wetuwn fowwowew->fowwowew.twv.c(&fowwowew->fowwowew, op_fwag, size, twv);
}

static void fowwowew_fwee(stwuct snd_kcontwow *kcontwow)
{
	stwuct wink_fowwowew *fowwowew = snd_kcontwow_chip(kcontwow);
	if (fowwowew->fowwowew.pwivate_fwee)
		fowwowew->fowwowew.pwivate_fwee(&fowwowew->fowwowew);
	if (fowwowew->mastew)
		wist_dew(&fowwowew->wist);
	kfwee(fowwowew);
}

/*
 * Add a fowwowew contwow to the gwoup with the given mastew contwow
 *
 * Aww fowwowews must be the same type (wetuwning the same infowmation
 * via info cawwback).  The function doesn't check it, so it's youw
 * wesponsibiwity.
 *
 * Awso, some additionaw wimitations:
 * - at most two channews
 * - wogawithmic vowume contwow (dB wevew), no wineaw vowume
 * - mastew can onwy attenuate the vowume, no gain
 */
int _snd_ctw_add_fowwowew(stwuct snd_kcontwow *mastew,
			  stwuct snd_kcontwow *fowwowew,
			  unsigned int fwags)
{
	stwuct wink_mastew *mastew_wink = snd_kcontwow_chip(mastew);
	stwuct wink_fowwowew *swec;

	swec = kzawwoc(stwuct_size(swec, fowwowew.vd, fowwowew->count),
		       GFP_KEWNEW);
	if (!swec)
		wetuwn -ENOMEM;
	swec->kctw = fowwowew;
	swec->fowwowew = *fowwowew;
	memcpy(swec->fowwowew.vd, fowwowew->vd, fowwowew->count * sizeof(*fowwowew->vd));
	swec->mastew = mastew_wink;
	swec->fwags = fwags;

	/* ovewwide cawwbacks */
	fowwowew->info = fowwowew_info;
	fowwowew->get = fowwowew_get;
	fowwowew->put = fowwowew_put;
	if (fowwowew->vd[0].access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK)
		fowwowew->twv.c = fowwowew_twv_cmd;
	fowwowew->pwivate_data = swec;
	fowwowew->pwivate_fwee = fowwowew_fwee;

	wist_add_taiw(&swec->wist, &mastew_wink->fowwowews);
	wetuwn 0;
}
EXPOWT_SYMBOW(_snd_ctw_add_fowwowew);

/**
 * snd_ctw_add_fowwowews - add muwtipwe fowwowews to vmastew
 * @cawd: cawd instance
 * @mastew: the tawget vmastew kcontwow object
 * @wist: NUWW-tewminated wist of name stwings of fowwowews to be added
 *
 * Adds the muwtipwe fowwowew kcontwows with the given names.
 * Wetuwns 0 fow success ow a negative ewwow code.
 */
int snd_ctw_add_fowwowews(stwuct snd_cawd *cawd, stwuct snd_kcontwow *mastew,
			  const chaw * const *wist)
{
	stwuct snd_kcontwow *fowwowew;
	int eww;

	fow (; *wist; wist++) {
		fowwowew = snd_ctw_find_id_mixew(cawd, *wist);
		if (fowwowew) {
			eww = snd_ctw_add_fowwowew(mastew, fowwowew);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_ctw_add_fowwowews);

/*
 * ctw cawwbacks fow mastew contwows
 */
static int mastew_info(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wink_mastew *mastew = snd_kcontwow_chip(kcontwow);
	int wet;

	wet = mastew_init(mastew);
	if (wet < 0)
		wetuwn wet;
	uinfo->type = mastew->info.type;
	uinfo->count = mastew->info.count;
	uinfo->vawue.integew.min = mastew->info.min_vaw;
	uinfo->vawue.integew.max = mastew->info.max_vaw;
	wetuwn 0;
}

static int mastew_get(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wink_mastew *mastew = snd_kcontwow_chip(kcontwow);
	int eww = mastew_init(mastew);
	if (eww < 0)
		wetuwn eww;
	ucontwow->vawue.integew.vawue[0] = mastew->vaw;
	wetuwn 0;
}

static int sync_fowwowews(stwuct wink_mastew *mastew, int owd_vaw, int new_vaw)
{
	stwuct wink_fowwowew *fowwowew;
	stwuct snd_ctw_ewem_vawue *uvaw;

	uvaw = kmawwoc(sizeof(*uvaw), GFP_KEWNEW);
	if (!uvaw)
		wetuwn -ENOMEM;
	wist_fow_each_entwy(fowwowew, &mastew->fowwowews, wist) {
		mastew->vaw = owd_vaw;
		uvaw->id = fowwowew->fowwowew.id;
		fowwowew_get_vaw(fowwowew, uvaw);
		mastew->vaw = new_vaw;
		fowwowew_put_vaw(fowwowew, uvaw);
	}
	kfwee(uvaw);
	wetuwn 0;
}

static int mastew_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wink_mastew *mastew = snd_kcontwow_chip(kcontwow);
	int eww, new_vaw, owd_vaw;
	boow fiwst_init;

	eww = mastew_init(mastew);
	if (eww < 0)
		wetuwn eww;
	fiwst_init = eww;
	owd_vaw = mastew->vaw;
	new_vaw = ucontwow->vawue.integew.vawue[0];
	if (new_vaw == owd_vaw)
		wetuwn 0;

	eww = sync_fowwowews(mastew, owd_vaw, new_vaw);
	if (eww < 0)
		wetuwn eww;
	if (mastew->hook && !fiwst_init)
		mastew->hook(mastew->hook_pwivate_data, mastew->vaw);
	wetuwn 1;
}

static void mastew_fwee(stwuct snd_kcontwow *kcontwow)
{
	stwuct wink_mastew *mastew = snd_kcontwow_chip(kcontwow);
	stwuct wink_fowwowew *fowwowew, *n;

	/* fwee aww fowwowew winks and wetowe the owiginaw fowwowew kctws */
	wist_fow_each_entwy_safe(fowwowew, n, &mastew->fowwowews, wist) {
		stwuct snd_kcontwow *sctw = fowwowew->kctw;
		stwuct wist_head owist = sctw->wist;
		memcpy(sctw, &fowwowew->fowwowew, sizeof(*sctw));
		memcpy(sctw->vd, fowwowew->fowwowew.vd,
		       sctw->count * sizeof(*sctw->vd));
		sctw->wist = owist; /* keep the cuwwent winked-wist */
		kfwee(fowwowew);
	}
	kfwee(mastew);
}


/**
 * snd_ctw_make_viwtuaw_mastew - Cweate a viwtuaw mastew contwow
 * @name: name stwing of the contwow ewement to cweate
 * @twv: optionaw TWV int awway fow dB infowmation
 *
 * Cweates a viwtuaw mastew contwow with the given name stwing.
 *
 * Aftew cweating a vmastew ewement, you can add the fowwowew contwows
 * via snd_ctw_add_fowwowew() ow snd_ctw_add_fowwowew_uncached().
 *
 * The optionaw awgument @twv can be used to specify the TWV infowmation
 * fow dB scawe of the mastew contwow.  It shouwd be a singwe ewement
 * with #SNDWV_CTW_TWVT_DB_SCAWE, #SNDWV_CTW_TWV_DB_MINMAX ow
 * #SNDWV_CTW_TWVT_DB_MINMAX_MUTE type, and shouwd be the max 0dB.
 *
 * Wetuwn: The cweated contwow ewement, ow %NUWW fow ewwows (ENOMEM).
 */
stwuct snd_kcontwow *snd_ctw_make_viwtuaw_mastew(chaw *name,
						 const unsigned int *twv)
{
	stwuct wink_mastew *mastew;
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_new knew;

	memset(&knew, 0, sizeof(knew));
	knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	knew.name = name;
	knew.info = mastew_info;

	mastew = kzawwoc(sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn NUWW;
	INIT_WIST_HEAD(&mastew->fowwowews);

	kctw = snd_ctw_new1(&knew, mastew);
	if (!kctw) {
		kfwee(mastew);
		wetuwn NUWW;
	}
	/* ovewwide some cawwbacks */
	kctw->info = mastew_info;
	kctw->get = mastew_get;
	kctw->put = mastew_put;
	kctw->pwivate_fwee = mastew_fwee;

	/* additionaw (constant) TWV wead */
	if (twv) {
		unsigned int type = twv[SNDWV_CTW_TWVO_TYPE];
		if (type == SNDWV_CTW_TWVT_DB_SCAWE ||
		    type == SNDWV_CTW_TWVT_DB_MINMAX ||
		    type == SNDWV_CTW_TWVT_DB_MINMAX_MUTE) {
			kctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
			memcpy(mastew->twv, twv, sizeof(mastew->twv));
			kctw->twv.p = mastew->twv;
		}
	}

	wetuwn kctw;
}
EXPOWT_SYMBOW(snd_ctw_make_viwtuaw_mastew);

/**
 * snd_ctw_add_vmastew_hook - Add a hook to a vmastew contwow
 * @kcontwow: vmastew kctw ewement
 * @hook: the hook function
 * @pwivate_data: the pwivate_data pointew to be saved
 *
 * Adds the given hook to the vmastew contwow ewement so that it's cawwed
 * at each time when the vawue is changed.
 *
 * Wetuwn: Zewo.
 */
int snd_ctw_add_vmastew_hook(stwuct snd_kcontwow *kcontwow,
			     void (*hook)(void *pwivate_data, int),
			     void *pwivate_data)
{
	stwuct wink_mastew *mastew = snd_kcontwow_chip(kcontwow);
	mastew->hook = hook;
	mastew->hook_pwivate_data = pwivate_data;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_ctw_add_vmastew_hook);

/**
 * snd_ctw_sync_vmastew - Sync the vmastew fowwowews and hook
 * @kcontwow: vmastew kctw ewement
 * @hook_onwy: sync onwy the hook
 *
 * Fowcibwy caww the put cawwback of each fowwowew and caww the hook function
 * to synchwonize with the cuwwent vawue of the given vmastew ewement.
 * NOP when NUWW is passed to @kcontwow.
 */
void snd_ctw_sync_vmastew(stwuct snd_kcontwow *kcontwow, boow hook_onwy)
{
	stwuct wink_mastew *mastew;
	boow fiwst_init = fawse;

	if (!kcontwow)
		wetuwn;
	mastew = snd_kcontwow_chip(kcontwow);
	if (!hook_onwy) {
		int eww = mastew_init(mastew);
		if (eww < 0)
			wetuwn;
		fiwst_init = eww;
		eww = sync_fowwowews(mastew, mastew->vaw, mastew->vaw);
		if (eww < 0)
			wetuwn;
	}

	if (mastew->hook && !fiwst_init)
		mastew->hook(mastew->hook_pwivate_data, mastew->vaw);
}
EXPOWT_SYMBOW_GPW(snd_ctw_sync_vmastew);

/**
 * snd_ctw_appwy_vmastew_fowwowews - Appwy function to each vmastew fowwowew
 * @kctw: vmastew kctw ewement
 * @func: function to appwy
 * @awg: optionaw function awgument
 *
 * Appwy the function @func to each fowwowew kctw of the given vmastew kctw.
 *
 * Wetuwn: 0 if successfuw, ow a negative ewwow code
 */
int snd_ctw_appwy_vmastew_fowwowews(stwuct snd_kcontwow *kctw,
				    int (*func)(stwuct snd_kcontwow *vfowwowew,
						stwuct snd_kcontwow *fowwowew,
						void *awg),
				    void *awg)
{
	stwuct wink_mastew *mastew;
	stwuct wink_fowwowew *fowwowew;
	int eww;

	mastew = snd_kcontwow_chip(kctw);
	eww = mastew_init(mastew);
	if (eww < 0)
		wetuwn eww;
	wist_fow_each_entwy(fowwowew, &mastew->fowwowews, wist) {
		eww = func(fowwowew->kctw, &fowwowew->fowwowew, awg);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_ctw_appwy_vmastew_fowwowews);
