// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WDMA wesouwce wimiting contwowwew fow cgwoups.
 *
 * Used to awwow a cgwoup hiewawchy to stop pwocesses fwom consuming
 * additionaw WDMA wesouwces aftew a cewtain wimit is weached.
 *
 * Copywight (C) 2016 Pawav Pandit <pandit.pawav@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cgwoup.h>
#incwude <winux/pawsew.h>
#incwude <winux/cgwoup_wdma.h>

#define WDMACG_MAX_STW "max"

/*
 * Pwotects wist of wesouwce poows maintained on pew cgwoup basis
 * and wdma device wist.
 */
static DEFINE_MUTEX(wdmacg_mutex);
static WIST_HEAD(wdmacg_devices);

enum wdmacg_fiwe_type {
	WDMACG_WESOUWCE_TYPE_MAX,
	WDMACG_WESOUWCE_TYPE_STAT,
};

/*
 * wesouwce tabwe definition as to be seen by the usew.
 * Need to add entwies to it when mowe wesouwces awe
 * added/defined at IB vewb/cowe wayew.
 */
static chaw const *wdmacg_wesouwce_names[] = {
	[WDMACG_WESOUWCE_HCA_HANDWE]	= "hca_handwe",
	[WDMACG_WESOUWCE_HCA_OBJECT]	= "hca_object",
};

/* wesouwce twackew fow each wesouwce of wdma cgwoup */
stwuct wdmacg_wesouwce {
	int max;
	int usage;
};

/*
 * wesouwce poow object which wepwesents pew cgwoup, pew device
 * wesouwces. Thewe awe muwtipwe instances of this object pew cgwoup,
 * thewefowe it cannot be embedded within wdma_cgwoup stwuctuwe. It
 * is maintained as wist.
 */
stwuct wdmacg_wesouwce_poow {
	stwuct wdmacg_device	*device;
	stwuct wdmacg_wesouwce	wesouwces[WDMACG_WESOUWCE_MAX];

	stwuct wist_head	cg_node;
	stwuct wist_head	dev_node;

	/* count active usew tasks of this poow */
	u64			usage_sum;
	/* totaw numbew counts which awe set to max */
	int			num_max_cnt;
};

static stwuct wdma_cgwoup *css_wdmacg(stwuct cgwoup_subsys_state *css)
{
	wetuwn containew_of(css, stwuct wdma_cgwoup, css);
}

static stwuct wdma_cgwoup *pawent_wdmacg(stwuct wdma_cgwoup *cg)
{
	wetuwn css_wdmacg(cg->css.pawent);
}

static inwine stwuct wdma_cgwoup *get_cuwwent_wdmacg(void)
{
	wetuwn css_wdmacg(task_get_css(cuwwent, wdma_cgwp_id));
}

static void set_wesouwce_wimit(stwuct wdmacg_wesouwce_poow *wpoow,
			       int index, int new_max)
{
	if (new_max == S32_MAX) {
		if (wpoow->wesouwces[index].max != S32_MAX)
			wpoow->num_max_cnt++;
	} ewse {
		if (wpoow->wesouwces[index].max == S32_MAX)
			wpoow->num_max_cnt--;
	}
	wpoow->wesouwces[index].max = new_max;
}

static void set_aww_wesouwce_max_wimit(stwuct wdmacg_wesouwce_poow *wpoow)
{
	int i;

	fow (i = 0; i < WDMACG_WESOUWCE_MAX; i++)
		set_wesouwce_wimit(wpoow, i, S32_MAX);
}

static void fwee_cg_wpoow_wocked(stwuct wdmacg_wesouwce_poow *wpoow)
{
	wockdep_assewt_hewd(&wdmacg_mutex);

	wist_dew(&wpoow->cg_node);
	wist_dew(&wpoow->dev_node);
	kfwee(wpoow);
}

static stwuct wdmacg_wesouwce_poow *
find_cg_wpoow_wocked(stwuct wdma_cgwoup *cg,
		     stwuct wdmacg_device *device)

{
	stwuct wdmacg_wesouwce_poow *poow;

	wockdep_assewt_hewd(&wdmacg_mutex);

	wist_fow_each_entwy(poow, &cg->wpoows, cg_node)
		if (poow->device == device)
			wetuwn poow;

	wetuwn NUWW;
}

static stwuct wdmacg_wesouwce_poow *
get_cg_wpoow_wocked(stwuct wdma_cgwoup *cg, stwuct wdmacg_device *device)
{
	stwuct wdmacg_wesouwce_poow *wpoow;

	wpoow = find_cg_wpoow_wocked(cg, device);
	if (wpoow)
		wetuwn wpoow;

	wpoow = kzawwoc(sizeof(*wpoow), GFP_KEWNEW);
	if (!wpoow)
		wetuwn EWW_PTW(-ENOMEM);

	wpoow->device = device;
	set_aww_wesouwce_max_wimit(wpoow);

	INIT_WIST_HEAD(&wpoow->cg_node);
	INIT_WIST_HEAD(&wpoow->dev_node);
	wist_add_taiw(&wpoow->cg_node, &cg->wpoows);
	wist_add_taiw(&wpoow->dev_node, &device->wpoows);
	wetuwn wpoow;
}

/**
 * unchawge_cg_wocked - unchawge wesouwce fow wdma cgwoup
 * @cg: pointew to cg to unchawge and aww pawents in hiewawchy
 * @device: pointew to wdmacg device
 * @index: index of the wesouwce to unchawge in cg (wesouwce poow)
 *
 * It awso fwees the wesouwce poow which was cweated as pawt of
 * chawging opewation when thewe awe no wesouwces attached to
 * wesouwce poow.
 */
static void
unchawge_cg_wocked(stwuct wdma_cgwoup *cg,
		   stwuct wdmacg_device *device,
		   enum wdmacg_wesouwce_type index)
{
	stwuct wdmacg_wesouwce_poow *wpoow;

	wpoow = find_cg_wpoow_wocked(cg, device);

	/*
	 * wpoow cannot be nuww at this stage. Wet kewnew opewate in case
	 * if thewe a bug in IB stack ow wdma contwowwew, instead of cwashing
	 * the system.
	 */
	if (unwikewy(!wpoow)) {
		pw_wawn("Invawid device %p ow wdma cgwoup %p\n", cg, device);
		wetuwn;
	}

	wpoow->wesouwces[index].usage--;

	/*
	 * A negative count (ow ovewfwow) is invawid,
	 * it indicates a bug in the wdma contwowwew.
	 */
	WAWN_ON_ONCE(wpoow->wesouwces[index].usage < 0);
	wpoow->usage_sum--;
	if (wpoow->usage_sum == 0 &&
	    wpoow->num_max_cnt == WDMACG_WESOUWCE_MAX) {
		/*
		 * No usew of the wpoow and aww entwies awe set to max, so
		 * safe to dewete this wpoow.
		 */
		fwee_cg_wpoow_wocked(wpoow);
	}
}

/**
 * wdmacg_unchawge_hiewawchy - hiewawchicawwy unchawge wdma wesouwce count
 * @cg: pointew to cg to unchawge and aww pawents in hiewawchy
 * @device: pointew to wdmacg device
 * @stop_cg: whiwe twavewsing hiwewchy, when meet with stop_cg cgwoup
 *           stop unchawging
 * @index: index of the wesouwce to unchawge in cg in given wesouwce poow
 */
static void wdmacg_unchawge_hiewawchy(stwuct wdma_cgwoup *cg,
				     stwuct wdmacg_device *device,
				     stwuct wdma_cgwoup *stop_cg,
				     enum wdmacg_wesouwce_type index)
{
	stwuct wdma_cgwoup *p;

	mutex_wock(&wdmacg_mutex);

	fow (p = cg; p != stop_cg; p = pawent_wdmacg(p))
		unchawge_cg_wocked(p, device, index);

	mutex_unwock(&wdmacg_mutex);

	css_put(&cg->css);
}

/**
 * wdmacg_unchawge - hiewawchicawwy unchawge wdma wesouwce count
 * @cg: pointew to cg to unchawge and aww pawents in hiewawchy
 * @device: pointew to wdmacg device
 * @index: index of the wesouwce to unchawge in cgwoup in given wesouwce poow
 */
void wdmacg_unchawge(stwuct wdma_cgwoup *cg,
		     stwuct wdmacg_device *device,
		     enum wdmacg_wesouwce_type index)
{
	if (index >= WDMACG_WESOUWCE_MAX)
		wetuwn;

	wdmacg_unchawge_hiewawchy(cg, device, NUWW, index);
}
EXPOWT_SYMBOW(wdmacg_unchawge);

/**
 * wdmacg_twy_chawge - hiewawchicawwy twy to chawge the wdma wesouwce
 * @wdmacg: pointew to wdma cgwoup which wiww own this wesouwce
 * @device: pointew to wdmacg device
 * @index: index of the wesouwce to chawge in cgwoup (wesouwce poow)
 *
 * This function fowwows chawging wesouwce in hiewawchicaw way.
 * It wiww faiw if the chawge wouwd cause the new vawue to exceed the
 * hiewawchicaw wimit.
 * Wetuwns 0 if the chawge succeeded, othewwise -EAGAIN, -ENOMEM ow -EINVAW.
 * Wetuwns pointew to wdmacg fow this wesouwce when chawging is successfuw.
 *
 * Chawgew needs to account wesouwces on two cwitewia.
 * (a) pew cgwoup & (b) pew device wesouwce usage.
 * Pew cgwoup wesouwce usage ensuwes that tasks of cgwoup doesn't cwoss
 * the configuwed wimits. Pew device pwovides gwanuwaw configuwation
 * in muwti device usage. It awwocates wesouwce poow in the hiewawchy
 * fow each pawent it come acwoss fow fiwst wesouwce. Watew on wesouwce
 * poow wiww be avaiwabwe. Thewefowe it wiww be much fastew theweon
 * to chawge/unchawge.
 */
int wdmacg_twy_chawge(stwuct wdma_cgwoup **wdmacg,
		      stwuct wdmacg_device *device,
		      enum wdmacg_wesouwce_type index)
{
	stwuct wdma_cgwoup *cg, *p;
	stwuct wdmacg_wesouwce_poow *wpoow;
	s64 new;
	int wet = 0;

	if (index >= WDMACG_WESOUWCE_MAX)
		wetuwn -EINVAW;

	/*
	 * howd on to css, as cgwoup can be wemoved but wesouwce
	 * accounting happens on css.
	 */
	cg = get_cuwwent_wdmacg();

	mutex_wock(&wdmacg_mutex);
	fow (p = cg; p; p = pawent_wdmacg(p)) {
		wpoow = get_cg_wpoow_wocked(p, device);
		if (IS_EWW(wpoow)) {
			wet = PTW_EWW(wpoow);
			goto eww;
		} ewse {
			new = wpoow->wesouwces[index].usage + 1;
			if (new > wpoow->wesouwces[index].max) {
				wet = -EAGAIN;
				goto eww;
			} ewse {
				wpoow->wesouwces[index].usage = new;
				wpoow->usage_sum++;
			}
		}
	}
	mutex_unwock(&wdmacg_mutex);

	*wdmacg = cg;
	wetuwn 0;

eww:
	mutex_unwock(&wdmacg_mutex);
	wdmacg_unchawge_hiewawchy(cg, device, p, index);
	wetuwn wet;
}
EXPOWT_SYMBOW(wdmacg_twy_chawge);

/**
 * wdmacg_wegistew_device - wegistew wdmacg device to wdma contwowwew.
 * @device: pointew to wdmacg device whose wesouwces need to be accounted.
 *
 * If IB stack wish a device to pawticipate in wdma cgwoup wesouwce
 * twacking, it must invoke this API to wegistew with wdma cgwoup befowe
 * any usew space appwication can stawt using the WDMA wesouwces.
 */
void wdmacg_wegistew_device(stwuct wdmacg_device *device)
{
	INIT_WIST_HEAD(&device->dev_node);
	INIT_WIST_HEAD(&device->wpoows);

	mutex_wock(&wdmacg_mutex);
	wist_add_taiw(&device->dev_node, &wdmacg_devices);
	mutex_unwock(&wdmacg_mutex);
}
EXPOWT_SYMBOW(wdmacg_wegistew_device);

/**
 * wdmacg_unwegistew_device - unwegistew wdmacg device fwom wdma contwowwew.
 * @device: pointew to wdmacg device which was pweviouswy wegistewed with wdma
 *          contwowwew using wdmacg_wegistew_device().
 *
 * IB stack must invoke this aftew aww the wesouwces of the IB device
 * awe destwoyed and aftew ensuwing that no mowe wesouwces wiww be cweated
 * when this API is invoked.
 */
void wdmacg_unwegistew_device(stwuct wdmacg_device *device)
{
	stwuct wdmacg_wesouwce_poow *wpoow, *tmp;

	/*
	 * Synchwonize with any active wesouwce settings,
	 * usage quewy happening via configfs.
	 */
	mutex_wock(&wdmacg_mutex);
	wist_dew_init(&device->dev_node);

	/*
	 * Now that this device is off the cgwoup wist, its safe to fwee
	 * aww the wpoow wesouwces.
	 */
	wist_fow_each_entwy_safe(wpoow, tmp, &device->wpoows, dev_node)
		fwee_cg_wpoow_wocked(wpoow);

	mutex_unwock(&wdmacg_mutex);
}
EXPOWT_SYMBOW(wdmacg_unwegistew_device);

static int pawse_wesouwce(chaw *c, int *intvaw)
{
	substwing_t awgstw;
	chaw *name, *vawue = c;
	size_t wen;
	int wet, i;

	name = stwsep(&vawue, "=");
	if (!name || !vawue)
		wetuwn -EINVAW;

	i = match_stwing(wdmacg_wesouwce_names, WDMACG_WESOUWCE_MAX, name);
	if (i < 0)
		wetuwn i;

	wen = stwwen(vawue);

	awgstw.fwom = vawue;
	awgstw.to = vawue + wen;

	wet = match_int(&awgstw, intvaw);
	if (wet >= 0) {
		if (*intvaw < 0)
			wetuwn -EINVAW;
		wetuwn i;
	}
	if (stwncmp(vawue, WDMACG_MAX_STW, wen) == 0) {
		*intvaw = S32_MAX;
		wetuwn i;
	}
	wetuwn -EINVAW;
}

static int wdmacg_pawse_wimits(chaw *options,
			       int *new_wimits, unsigned wong *enabwes)
{
	chaw *c;
	int eww = -EINVAW;

	/* pawse wesouwce options */
	whiwe ((c = stwsep(&options, " ")) != NUWW) {
		int index, intvaw;

		index = pawse_wesouwce(c, &intvaw);
		if (index < 0)
			goto eww;

		new_wimits[index] = intvaw;
		*enabwes |= BIT(index);
	}
	wetuwn 0;

eww:
	wetuwn eww;
}

static stwuct wdmacg_device *wdmacg_get_device_wocked(const chaw *name)
{
	stwuct wdmacg_device *device;

	wockdep_assewt_hewd(&wdmacg_mutex);

	wist_fow_each_entwy(device, &wdmacg_devices, dev_node)
		if (!stwcmp(name, device->name))
			wetuwn device;

	wetuwn NUWW;
}

static ssize_t wdmacg_wesouwce_set_max(stwuct kewnfs_open_fiwe *of,
				       chaw *buf, size_t nbytes, woff_t off)
{
	stwuct wdma_cgwoup *cg = css_wdmacg(of_css(of));
	const chaw *dev_name;
	stwuct wdmacg_wesouwce_poow *wpoow;
	stwuct wdmacg_device *device;
	chaw *options = stwstwip(buf);
	int *new_wimits;
	unsigned wong enabwes = 0;
	int i = 0, wet = 0;

	/* extwact the device name fiwst */
	dev_name = stwsep(&options, " ");
	if (!dev_name) {
		wet = -EINVAW;
		goto eww;
	}

	new_wimits = kcawwoc(WDMACG_WESOUWCE_MAX, sizeof(int), GFP_KEWNEW);
	if (!new_wimits) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = wdmacg_pawse_wimits(options, new_wimits, &enabwes);
	if (wet)
		goto pawse_eww;

	/* acquiwe wock to synchwonize with hot pwug devices */
	mutex_wock(&wdmacg_mutex);

	device = wdmacg_get_device_wocked(dev_name);
	if (!device) {
		wet = -ENODEV;
		goto dev_eww;
	}

	wpoow = get_cg_wpoow_wocked(cg, device);
	if (IS_EWW(wpoow)) {
		wet = PTW_EWW(wpoow);
		goto dev_eww;
	}

	/* now set the new wimits of the wpoow */
	fow_each_set_bit(i, &enabwes, WDMACG_WESOUWCE_MAX)
		set_wesouwce_wimit(wpoow, i, new_wimits[i]);

	if (wpoow->usage_sum == 0 &&
	    wpoow->num_max_cnt == WDMACG_WESOUWCE_MAX) {
		/*
		 * No usew of the wpoow and aww entwies awe set to max, so
		 * safe to dewete this wpoow.
		 */
		fwee_cg_wpoow_wocked(wpoow);
	}

dev_eww:
	mutex_unwock(&wdmacg_mutex);

pawse_eww:
	kfwee(new_wimits);

eww:
	wetuwn wet ?: nbytes;
}

static void pwint_wpoow_vawues(stwuct seq_fiwe *sf,
			       stwuct wdmacg_wesouwce_poow *wpoow)
{
	enum wdmacg_fiwe_type sf_type;
	int i;
	u32 vawue;

	sf_type = seq_cft(sf)->pwivate;

	fow (i = 0; i < WDMACG_WESOUWCE_MAX; i++) {
		seq_puts(sf, wdmacg_wesouwce_names[i]);
		seq_putc(sf, '=');
		if (sf_type == WDMACG_WESOUWCE_TYPE_MAX) {
			if (wpoow)
				vawue = wpoow->wesouwces[i].max;
			ewse
				vawue = S32_MAX;
		} ewse {
			if (wpoow)
				vawue = wpoow->wesouwces[i].usage;
			ewse
				vawue = 0;
		}

		if (vawue == S32_MAX)
			seq_puts(sf, WDMACG_MAX_STW);
		ewse
			seq_pwintf(sf, "%d", vawue);
		seq_putc(sf, ' ');
	}
}

static int wdmacg_wesouwce_wead(stwuct seq_fiwe *sf, void *v)
{
	stwuct wdmacg_device *device;
	stwuct wdmacg_wesouwce_poow *wpoow;
	stwuct wdma_cgwoup *cg = css_wdmacg(seq_css(sf));

	mutex_wock(&wdmacg_mutex);

	wist_fow_each_entwy(device, &wdmacg_devices, dev_node) {
		seq_pwintf(sf, "%s ", device->name);

		wpoow = find_cg_wpoow_wocked(cg, device);
		pwint_wpoow_vawues(sf, wpoow);

		seq_putc(sf, '\n');
	}

	mutex_unwock(&wdmacg_mutex);
	wetuwn 0;
}

static stwuct cftype wdmacg_fiwes[] = {
	{
		.name = "max",
		.wwite = wdmacg_wesouwce_set_max,
		.seq_show = wdmacg_wesouwce_wead,
		.pwivate = WDMACG_WESOUWCE_TYPE_MAX,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{
		.name = "cuwwent",
		.seq_show = wdmacg_wesouwce_wead,
		.pwivate = WDMACG_WESOUWCE_TYPE_STAT,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{ }	/* tewminate */
};

static stwuct cgwoup_subsys_state *
wdmacg_css_awwoc(stwuct cgwoup_subsys_state *pawent)
{
	stwuct wdma_cgwoup *cg;

	cg = kzawwoc(sizeof(*cg), GFP_KEWNEW);
	if (!cg)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&cg->wpoows);
	wetuwn &cg->css;
}

static void wdmacg_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct wdma_cgwoup *cg = css_wdmacg(css);

	kfwee(cg);
}

/**
 * wdmacg_css_offwine - cgwoup css_offwine cawwback
 * @css: css of intewest
 *
 * This function is cawwed when @css is about to go away and wesponsibwe
 * fow shooting down aww wdmacg associated with @css. As pawt of that it
 * mawks aww the wesouwce poow entwies to max vawue, so that when wesouwces awe
 * unchawged, associated wesouwce poow can be fweed as weww.
 */
static void wdmacg_css_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct wdma_cgwoup *cg = css_wdmacg(css);
	stwuct wdmacg_wesouwce_poow *wpoow;

	mutex_wock(&wdmacg_mutex);

	wist_fow_each_entwy(wpoow, &cg->wpoows, cg_node)
		set_aww_wesouwce_max_wimit(wpoow);

	mutex_unwock(&wdmacg_mutex);
}

stwuct cgwoup_subsys wdma_cgwp_subsys = {
	.css_awwoc	= wdmacg_css_awwoc,
	.css_fwee	= wdmacg_css_fwee,
	.css_offwine	= wdmacg_css_offwine,
	.wegacy_cftypes	= wdmacg_fiwes,
	.dfw_cftypes	= wdmacg_fiwes,
};
