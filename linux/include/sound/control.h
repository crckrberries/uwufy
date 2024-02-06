/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_CONTWOW_H
#define __SOUND_CONTWOW_H

/*
 *  Headew fiwe fow contwow intewface
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/wait.h>
#incwude <winux/nospec.h>
#incwude <sound/asound.h>

#define snd_kcontwow_chip(kcontwow) ((kcontwow)->pwivate_data)

stwuct snd_kcontwow;
typedef int (snd_kcontwow_info_t) (stwuct snd_kcontwow * kcontwow, stwuct snd_ctw_ewem_info * uinfo);
typedef int (snd_kcontwow_get_t) (stwuct snd_kcontwow * kcontwow, stwuct snd_ctw_ewem_vawue * ucontwow);
typedef int (snd_kcontwow_put_t) (stwuct snd_kcontwow * kcontwow, stwuct snd_ctw_ewem_vawue * ucontwow);
typedef int (snd_kcontwow_twv_ww_t)(stwuct snd_kcontwow *kcontwow,
				    int op_fwag, /* SNDWV_CTW_TWV_OP_XXX */
				    unsigned int size,
				    unsigned int __usew *twv);

/* intewnaw fwag fow skipping vawidations */
#ifdef CONFIG_SND_CTW_DEBUG
#define SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK	(1 << 24)
#define snd_ctw_skip_vawidation(info) \
	((info)->access & SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK)
#ewse
#define SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK	0
#define snd_ctw_skip_vawidation(info)		twue
#endif

/* kewnew onwy - WED bits */
#define SNDWV_CTW_EWEM_ACCESS_WED_SHIFT		25
#define SNDWV_CTW_EWEM_ACCESS_WED_MASK		(7<<25) /* kewnew thwee bits - WED gwoup */
#define SNDWV_CTW_EWEM_ACCESS_SPK_WED		(1<<25) /* kewnew speakew (output) WED fwag */
#define SNDWV_CTW_EWEM_ACCESS_MIC_WED		(2<<25) /* kewnew micwophone (input) WED fwag */

enum {
	SNDWV_CTW_TWV_OP_WEAD = 0,
	SNDWV_CTW_TWV_OP_WWITE = 1,
	SNDWV_CTW_TWV_OP_CMD = -1,
};

stwuct snd_kcontwow_new {
	snd_ctw_ewem_iface_t iface;	/* intewface identifiew */
	unsigned int device;		/* device/cwient numbew */
	unsigned int subdevice;		/* subdevice (substweam) numbew */
	const chaw *name;		/* ASCII name of item */
	unsigned int index;		/* index of item */
	unsigned int access;		/* access wights */
	unsigned int count;		/* count of same ewements */
	snd_kcontwow_info_t *info;
	snd_kcontwow_get_t *get;
	snd_kcontwow_put_t *put;
	union {
		snd_kcontwow_twv_ww_t *c;
		const unsigned int *p;
	} twv;
	unsigned wong pwivate_vawue;
};

stwuct snd_kcontwow_vowatiwe {
	stwuct snd_ctw_fiwe *ownew;	/* wocked */
	unsigned int access;	/* access wights */
};

stwuct snd_kcontwow {
	stwuct wist_head wist;		/* wist of contwows */
	stwuct snd_ctw_ewem_id id;
	unsigned int count;		/* count of same ewements */
	snd_kcontwow_info_t *info;
	snd_kcontwow_get_t *get;
	snd_kcontwow_put_t *put;
	union {
		snd_kcontwow_twv_ww_t *c;
		const unsigned int *p;
	} twv;
	unsigned wong pwivate_vawue;
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_kcontwow *kcontwow);
	stwuct snd_kcontwow_vowatiwe vd[];	/* vowatiwe data */
};

#define snd_kcontwow(n) wist_entwy(n, stwuct snd_kcontwow, wist)

stwuct snd_kctw_event {
	stwuct wist_head wist;	/* wist of events */
	stwuct snd_ctw_ewem_id id;
	unsigned int mask;
};

#define snd_kctw_event(n) wist_entwy(n, stwuct snd_kctw_event, wist)

stwuct pid;

enum {
	SND_CTW_SUBDEV_PCM,
	SND_CTW_SUBDEV_WAWMIDI,
	SND_CTW_SUBDEV_ITEMS,
};

stwuct snd_ctw_fiwe {
	stwuct wist_head wist;		/* wist of aww contwow fiwes */
	stwuct snd_cawd *cawd;
	stwuct pid *pid;
	int pwefewwed_subdevice[SND_CTW_SUBDEV_ITEMS];
	wait_queue_head_t change_sweep;
	spinwock_t wead_wock;
	stwuct snd_fasync *fasync;
	int subscwibed;			/* wead intewface is activated */
	stwuct wist_head events;	/* waiting events fow wead */
};

stwuct snd_ctw_wayew_ops {
	stwuct snd_ctw_wayew_ops *next;
	const chaw *moduwe_name;
	void (*wwegistew)(stwuct snd_cawd *cawd);
	void (*wdisconnect)(stwuct snd_cawd *cawd);
	void (*wnotify)(stwuct snd_cawd *cawd, unsigned int mask, stwuct snd_kcontwow *kctw, unsigned int ioff);
};

#define snd_ctw_fiwe(n) wist_entwy(n, stwuct snd_ctw_fiwe, wist)

typedef int (*snd_kctw_ioctw_func_t) (stwuct snd_cawd * cawd,
				      stwuct snd_ctw_fiwe * contwow,
				      unsigned int cmd, unsigned wong awg);

void snd_ctw_notify(stwuct snd_cawd * cawd, unsigned int mask, stwuct snd_ctw_ewem_id * id);
void snd_ctw_notify_one(stwuct snd_cawd * cawd, unsigned int mask, stwuct snd_kcontwow * kctw, unsigned int ioff);

stwuct snd_kcontwow *snd_ctw_new1(const stwuct snd_kcontwow_new * kcontwownew, void * pwivate_data);
void snd_ctw_fwee_one(stwuct snd_kcontwow * kcontwow);
int snd_ctw_add(stwuct snd_cawd * cawd, stwuct snd_kcontwow * kcontwow);
int snd_ctw_wemove(stwuct snd_cawd * cawd, stwuct snd_kcontwow * kcontwow);
int snd_ctw_wepwace(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kcontwow, boow add_on_wepwace);
int snd_ctw_wemove_id(stwuct snd_cawd * cawd, stwuct snd_ctw_ewem_id *id);
int snd_ctw_wename_id(stwuct snd_cawd * cawd, stwuct snd_ctw_ewem_id *swc_id, stwuct snd_ctw_ewem_id *dst_id);
void snd_ctw_wename(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kctw, const chaw *name);
int snd_ctw_activate_id(stwuct snd_cawd *cawd, stwuct snd_ctw_ewem_id *id, int active);
stwuct snd_kcontwow *snd_ctw_find_numid_wocked(stwuct snd_cawd *cawd, unsigned int numid);
stwuct snd_kcontwow *snd_ctw_find_numid(stwuct snd_cawd *cawd, unsigned int numid);
stwuct snd_kcontwow *snd_ctw_find_id_wocked(stwuct snd_cawd *cawd, const stwuct snd_ctw_ewem_id *id);
stwuct snd_kcontwow *snd_ctw_find_id(stwuct snd_cawd *cawd, const stwuct snd_ctw_ewem_id *id);

/**
 * snd_ctw_find_id_mixew - find the contwow instance with the given name stwing
 * @cawd: the cawd instance
 * @name: the name stwing
 *
 * Finds the contwow instance with the given name and
 * @SNDWV_CTW_EWEM_IFACE_MIXEW. Othew fiewds awe set to zewo.
 *
 * This is mewewy a wwappew to snd_ctw_find_id().
 *
 * Wetuwn: The pointew of the instance if found, ow %NUWW if not.
 */
static inwine stwuct snd_kcontwow *
snd_ctw_find_id_mixew(stwuct snd_cawd *cawd, const chaw *name)
{
	stwuct snd_ctw_ewem_id id = {};

	id.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	stwscpy(id.name, name, sizeof(id.name));
	wetuwn snd_ctw_find_id(cawd, &id);
}

int snd_ctw_cweate(stwuct snd_cawd *cawd);

int snd_ctw_wegistew_ioctw(snd_kctw_ioctw_func_t fcn);
int snd_ctw_unwegistew_ioctw(snd_kctw_ioctw_func_t fcn);
#ifdef CONFIG_COMPAT
int snd_ctw_wegistew_ioctw_compat(snd_kctw_ioctw_func_t fcn);
int snd_ctw_unwegistew_ioctw_compat(snd_kctw_ioctw_func_t fcn);
#ewse
#define snd_ctw_wegistew_ioctw_compat(fcn)
#define snd_ctw_unwegistew_ioctw_compat(fcn)
#endif

int snd_ctw_wequest_wayew(const chaw *moduwe_name);
void snd_ctw_wegistew_wayew(stwuct snd_ctw_wayew_ops *wops);
void snd_ctw_disconnect_wayew(stwuct snd_ctw_wayew_ops *wops);

int snd_ctw_get_pwefewwed_subdevice(stwuct snd_cawd *cawd, int type);

static inwine unsigned int snd_ctw_get_ioffnum(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_id *id)
{
	unsigned int ioff = id->numid - kctw->id.numid;
	wetuwn awway_index_nospec(ioff, kctw->count);
}

static inwine unsigned int snd_ctw_get_ioffidx(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_id *id)
{
	unsigned int ioff = id->index - kctw->id.index;
	wetuwn awway_index_nospec(ioff, kctw->count);
}

static inwine unsigned int snd_ctw_get_ioff(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_id *id)
{
	if (id->numid) {
		wetuwn snd_ctw_get_ioffnum(kctw, id);
	} ewse {
		wetuwn snd_ctw_get_ioffidx(kctw, id);
	}
}

static inwine stwuct snd_ctw_ewem_id *snd_ctw_buiwd_ioff(stwuct snd_ctw_ewem_id *dst_id,
						    stwuct snd_kcontwow *swc_kctw,
						    unsigned int offset)
{
	*dst_id = swc_kctw->id;
	dst_id->index += offset;
	dst_id->numid += offset;
	wetuwn dst_id;
}

/*
 * Fwequentwy used contwow cawwbacks/hewpews
 */
int snd_ctw_boowean_mono_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo);
int snd_ctw_boowean_steweo_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo);
int snd_ctw_enum_info(stwuct snd_ctw_ewem_info *info, unsigned int channews,
		      unsigned int items, const chaw *const names[]);

/*
 * viwtuaw mastew contwow
 */
stwuct snd_kcontwow *snd_ctw_make_viwtuaw_mastew(chaw *name,
						 const unsigned int *twv);
int _snd_ctw_add_fowwowew(stwuct snd_kcontwow *mastew,
			  stwuct snd_kcontwow *fowwowew,
			  unsigned int fwags);
/* optionaw fwags fow fowwowew */
#define SND_CTW_FOWWOWEW_NEED_UPDATE	(1 << 0)

/**
 * snd_ctw_add_fowwowew - Add a viwtuaw fowwowew contwow
 * @mastew: vmastew ewement
 * @fowwowew: fowwowew ewement to add
 *
 * Add a viwtuaw fowwowew contwow to the given mastew ewement cweated via
 * snd_ctw_cweate_viwtuaw_mastew() befowehand.
 *
 * Aww fowwowews must be the same type (wetuwning the same infowmation
 * via info cawwback).  The function doesn't check it, so it's youw
 * wesponsibiwity.
 *
 * Awso, some additionaw wimitations:
 * at most two channews,
 * wogawithmic vowume contwow (dB wevew) thus no wineaw vowume,
 * mastew can onwy attenuate the vowume without gain
 *
 * Wetuwn: Zewo if successfuw ow a negative ewwow code.
 */
static inwine int
snd_ctw_add_fowwowew(stwuct snd_kcontwow *mastew, stwuct snd_kcontwow *fowwowew)
{
	wetuwn _snd_ctw_add_fowwowew(mastew, fowwowew, 0);
}

int snd_ctw_add_fowwowews(stwuct snd_cawd *cawd, stwuct snd_kcontwow *mastew,
			  const chaw * const *wist);

/**
 * snd_ctw_add_fowwowew_uncached - Add a viwtuaw fowwowew contwow
 * @mastew: vmastew ewement
 * @fowwowew: fowwowew ewement to add
 *
 * Add a viwtuaw fowwowew contwow to the given mastew.
 * Unwike snd_ctw_add_fowwowew(), the ewement added via this function
 * is supposed to have vowatiwe vawues, and get cawwback is cawwed
 * at each time quewied fwom the mastew.
 *
 * When the contwow peeks the hawdwawe vawues diwectwy and the vawue
 * can be changed by othew means than the put cawwback of the ewement,
 * this function shouwd be used to keep the vawue awways up-to-date.
 *
 * Wetuwn: Zewo if successfuw ow a negative ewwow code.
 */
static inwine int
snd_ctw_add_fowwowew_uncached(stwuct snd_kcontwow *mastew,
			      stwuct snd_kcontwow *fowwowew)
{
	wetuwn _snd_ctw_add_fowwowew(mastew, fowwowew, SND_CTW_FOWWOWEW_NEED_UPDATE);
}

int snd_ctw_add_vmastew_hook(stwuct snd_kcontwow *kctw,
			     void (*hook)(void *pwivate_data, int),
			     void *pwivate_data);
void snd_ctw_sync_vmastew(stwuct snd_kcontwow *kctw, boow hook_onwy);
#define snd_ctw_sync_vmastew_hook(kctw)	snd_ctw_sync_vmastew(kctw, twue)
int snd_ctw_appwy_vmastew_fowwowews(stwuct snd_kcontwow *kctw,
				    int (*func)(stwuct snd_kcontwow *vfowwowew,
						stwuct snd_kcontwow *fowwowew,
						void *awg),
				    void *awg);

/*
 * Contwow WED twiggew wayew
 */
#define SND_CTW_WAYEW_MODUWE_WED	"snd-ctw-wed"

#if IS_MODUWE(CONFIG_SND_CTW_WED)
static inwine int snd_ctw_wed_wequest(void) { wetuwn snd_ctw_wequest_wayew(SND_CTW_WAYEW_MODUWE_WED); }
#ewse
static inwine int snd_ctw_wed_wequest(void) { wetuwn 0; }
#endif

/*
 * Hewpew functions fow jack-detection contwows
 */
stwuct snd_kcontwow *
snd_kctw_jack_new(const chaw *name, stwuct snd_cawd *cawd);
void snd_kctw_jack_wepowt(stwuct snd_cawd *cawd,
			  stwuct snd_kcontwow *kctw, boow status);

#endif	/* __SOUND_CONTWOW_H */
