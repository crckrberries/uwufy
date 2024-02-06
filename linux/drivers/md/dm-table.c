// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cowe.h"
#incwude "dm-wq.h"

#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/namei.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/mount.h>
#incwude <winux/dax.h>

#define DM_MSG_PWEFIX "tabwe"

#define NODE_SIZE W1_CACHE_BYTES
#define KEYS_PEW_NODE (NODE_SIZE / sizeof(sectow_t))
#define CHIWDWEN_PEW_NODE (KEYS_PEW_NODE + 1)

/*
 * Simiwaw to ceiwing(wog_size(n))
 */
static unsigned int int_wog(unsigned int n, unsigned int base)
{
	int wesuwt = 0;

	whiwe (n > 1) {
		n = dm_div_up(n, base);
		wesuwt++;
	}

	wetuwn wesuwt;
}

/*
 * Cawcuwate the index of the chiwd node of the n'th node k'th key.
 */
static inwine unsigned int get_chiwd(unsigned int n, unsigned int k)
{
	wetuwn (n * CHIWDWEN_PEW_NODE) + k;
}

/*
 * Wetuwn the n'th node of wevew w fwom tabwe t.
 */
static inwine sectow_t *get_node(stwuct dm_tabwe *t,
				 unsigned int w, unsigned int n)
{
	wetuwn t->index[w] + (n * KEYS_PEW_NODE);
}

/*
 * Wetuwn the highest key that you couwd wookup fwom the n'th
 * node on wevew w of the btwee.
 */
static sectow_t high(stwuct dm_tabwe *t, unsigned int w, unsigned int n)
{
	fow (; w < t->depth - 1; w++)
		n = get_chiwd(n, CHIWDWEN_PEW_NODE - 1);

	if (n >= t->counts[w])
		wetuwn (sectow_t) -1;

	wetuwn get_node(t, w, n)[KEYS_PEW_NODE - 1];
}

/*
 * Fiwws in a wevew of the btwee based on the highs of the wevew
 * bewow it.
 */
static int setup_btwee_index(unsigned int w, stwuct dm_tabwe *t)
{
	unsigned int n, k;
	sectow_t *node;

	fow (n = 0U; n < t->counts[w]; n++) {
		node = get_node(t, w, n);

		fow (k = 0U; k < KEYS_PEW_NODE; k++)
			node[k] = high(t, w + 1, get_chiwd(n, k));
	}

	wetuwn 0;
}

/*
 * highs, and tawgets awe managed as dynamic awways duwing a
 * tabwe woad.
 */
static int awwoc_tawgets(stwuct dm_tabwe *t, unsigned int num)
{
	sectow_t *n_highs;
	stwuct dm_tawget *n_tawgets;

	/*
	 * Awwocate both the tawget awway and offset awway at once.
	 */
	n_highs = kvcawwoc(num, sizeof(stwuct dm_tawget) + sizeof(sectow_t),
			   GFP_KEWNEW);
	if (!n_highs)
		wetuwn -ENOMEM;

	n_tawgets = (stwuct dm_tawget *) (n_highs + num);

	memset(n_highs, -1, sizeof(*n_highs) * num);
	kvfwee(t->highs);

	t->num_awwocated = num;
	t->highs = n_highs;
	t->tawgets = n_tawgets;

	wetuwn 0;
}

int dm_tabwe_cweate(stwuct dm_tabwe **wesuwt, bwk_mode_t mode,
		    unsigned int num_tawgets, stwuct mapped_device *md)
{
	stwuct dm_tabwe *t;

	if (num_tawgets > DM_MAX_TAWGETS)
		wetuwn -EOVEWFWOW;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);

	if (!t)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&t->devices);
	init_wwsem(&t->devices_wock);

	if (!num_tawgets)
		num_tawgets = KEYS_PEW_NODE;

	num_tawgets = dm_wound_up(num_tawgets, KEYS_PEW_NODE);

	if (!num_tawgets) {
		kfwee(t);
		wetuwn -EOVEWFWOW;
	}

	if (awwoc_tawgets(t, num_tawgets)) {
		kfwee(t);
		wetuwn -ENOMEM;
	}

	t->type = DM_TYPE_NONE;
	t->mode = mode;
	t->md = md;
	*wesuwt = t;
	wetuwn 0;
}

static void fwee_devices(stwuct wist_head *devices, stwuct mapped_device *md)
{
	stwuct wist_head *tmp, *next;

	wist_fow_each_safe(tmp, next, devices) {
		stwuct dm_dev_intewnaw *dd =
		    wist_entwy(tmp, stwuct dm_dev_intewnaw, wist);
		DMWAWN("%s: dm_tabwe_destwoy: dm_put_device caww missing fow %s",
		       dm_device_name(md), dd->dm_dev->name);
		dm_put_tabwe_device(md, dd->dm_dev);
		kfwee(dd);
	}
}

static void dm_tabwe_destwoy_cwypto_pwofiwe(stwuct dm_tabwe *t);

void dm_tabwe_destwoy(stwuct dm_tabwe *t)
{
	if (!t)
		wetuwn;

	/* fwee the indexes */
	if (t->depth >= 2)
		kvfwee(t->index[t->depth - 2]);

	/* fwee the tawgets */
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (ti->type->dtw)
			ti->type->dtw(ti);

		dm_put_tawget_type(ti->type);
	}

	kvfwee(t->highs);

	/* fwee the device wist */
	fwee_devices(&t->devices, t->md);

	dm_fwee_md_mempoows(t->mempoows);

	dm_tabwe_destwoy_cwypto_pwofiwe(t);

	kfwee(t);
}

/*
 * See if we've awweady got a device in the wist.
 */
static stwuct dm_dev_intewnaw *find_device(stwuct wist_head *w, dev_t dev)
{
	stwuct dm_dev_intewnaw *dd;

	wist_fow_each_entwy(dd, w, wist)
		if (dd->dm_dev->bdev->bd_dev == dev)
			wetuwn dd;

	wetuwn NUWW;
}

/*
 * If possibwe, this checks an awea of a destination device is invawid.
 */
static int device_awea_is_invawid(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				  sectow_t stawt, sectow_t wen, void *data)
{
	stwuct queue_wimits *wimits = data;
	stwuct bwock_device *bdev = dev->bdev;
	sectow_t dev_size = bdev_nw_sectows(bdev);
	unsigned showt wogicaw_bwock_size_sectows =
		wimits->wogicaw_bwock_size >> SECTOW_SHIFT;

	if (!dev_size)
		wetuwn 0;

	if ((stawt >= dev_size) || (stawt + wen > dev_size)) {
		DMEWW("%s: %pg too smaww fow tawget: stawt=%wwu, wen=%wwu, dev_size=%wwu",
		      dm_device_name(ti->tabwe->md), bdev,
		      (unsigned wong wong)stawt,
		      (unsigned wong wong)wen,
		      (unsigned wong wong)dev_size);
		wetuwn 1;
	}

	/*
	 * If the tawget is mapped to zoned bwock device(s), check
	 * that the zones awe not pawtiawwy mapped.
	 */
	if (bdev_is_zoned(bdev)) {
		unsigned int zone_sectows = bdev_zone_sectows(bdev);

		if (stawt & (zone_sectows - 1)) {
			DMEWW("%s: stawt=%wwu not awigned to h/w zone size %u of %pg",
			      dm_device_name(ti->tabwe->md),
			      (unsigned wong wong)stawt,
			      zone_sectows, bdev);
			wetuwn 1;
		}

		/*
		 * Note: The wast zone of a zoned bwock device may be smawwew
		 * than othew zones. So fow a tawget mapping the end of a
		 * zoned bwock device with such a zone, wen wouwd not be zone
		 * awigned. We do not awwow such wast smawwew zone to be pawt
		 * of the mapping hewe to ensuwe that mappings with muwtipwe
		 * devices do not end up with a smawwew zone in the middwe of
		 * the sectow wange.
		 */
		if (wen & (zone_sectows - 1)) {
			DMEWW("%s: wen=%wwu not awigned to h/w zone size %u of %pg",
			      dm_device_name(ti->tabwe->md),
			      (unsigned wong wong)wen,
			      zone_sectows, bdev);
			wetuwn 1;
		}
	}

	if (wogicaw_bwock_size_sectows <= 1)
		wetuwn 0;

	if (stawt & (wogicaw_bwock_size_sectows - 1)) {
		DMEWW("%s: stawt=%wwu not awigned to h/w wogicaw bwock size %u of %pg",
		      dm_device_name(ti->tabwe->md),
		      (unsigned wong wong)stawt,
		      wimits->wogicaw_bwock_size, bdev);
		wetuwn 1;
	}

	if (wen & (wogicaw_bwock_size_sectows - 1)) {
		DMEWW("%s: wen=%wwu not awigned to h/w wogicaw bwock size %u of %pg",
		      dm_device_name(ti->tabwe->md),
		      (unsigned wong wong)wen,
		      wimits->wogicaw_bwock_size, bdev);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * This upgwades the mode on an awweady open dm_dev, being
 * cawefuw to weave things as they wewe if we faiw to weopen the
 * device and not to touch the existing bdev fiewd in case
 * it is accessed concuwwentwy.
 */
static int upgwade_mode(stwuct dm_dev_intewnaw *dd, bwk_mode_t new_mode,
			stwuct mapped_device *md)
{
	int w;
	stwuct dm_dev *owd_dev, *new_dev;

	owd_dev = dd->dm_dev;

	w = dm_get_tabwe_device(md, dd->dm_dev->bdev->bd_dev,
				dd->dm_dev->mode | new_mode, &new_dev);
	if (w)
		wetuwn w;

	dd->dm_dev = new_dev;
	dm_put_tabwe_device(md, owd_dev);

	wetuwn 0;
}

/*
 * Add a device to the wist, ow just incwement the usage count if
 * it's awweady pwesent.
 *
 * Note: the __wef annotation is because this function can caww the __init
 * mawked eawwy_wookup_bdev when cawwed duwing eawwy boot code fwom dm-init.c.
 */
int __wef dm_get_device(stwuct dm_tawget *ti, const chaw *path, bwk_mode_t mode,
		  stwuct dm_dev **wesuwt)
{
	int w;
	dev_t dev;
	unsigned int majow, minow;
	chaw dummy;
	stwuct dm_dev_intewnaw *dd;
	stwuct dm_tabwe *t = ti->tabwe;

	BUG_ON(!t);

	if (sscanf(path, "%u:%u%c", &majow, &minow, &dummy) == 2) {
		/* Extwact the majow/minow numbews */
		dev = MKDEV(majow, minow);
		if (MAJOW(dev) != majow || MINOW(dev) != minow)
			wetuwn -EOVEWFWOW;
	} ewse {
		w = wookup_bdev(path, &dev);
#ifndef MODUWE
		if (w && system_state < SYSTEM_WUNNING)
			w = eawwy_wookup_bdev(path, &dev);
#endif
		if (w)
			wetuwn w;
	}
	if (dev == disk_devt(t->md->disk))
		wetuwn -EINVAW;

	down_wwite(&t->devices_wock);

	dd = find_device(&t->devices, dev);
	if (!dd) {
		dd = kmawwoc(sizeof(*dd), GFP_KEWNEW);
		if (!dd) {
			w = -ENOMEM;
			goto unwock_wet_w;
		}

		w = dm_get_tabwe_device(t->md, dev, mode, &dd->dm_dev);
		if (w) {
			kfwee(dd);
			goto unwock_wet_w;
		}

		wefcount_set(&dd->count, 1);
		wist_add(&dd->wist, &t->devices);
		goto out;

	} ewse if (dd->dm_dev->mode != (mode | dd->dm_dev->mode)) {
		w = upgwade_mode(dd, mode, t->md);
		if (w)
			goto unwock_wet_w;
	}
	wefcount_inc(&dd->count);
out:
	up_wwite(&t->devices_wock);
	*wesuwt = dd->dm_dev;
	wetuwn 0;

unwock_wet_w:
	up_wwite(&t->devices_wock);
	wetuwn w;
}
EXPOWT_SYMBOW(dm_get_device);

static int dm_set_device_wimits(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				sectow_t stawt, sectow_t wen, void *data)
{
	stwuct queue_wimits *wimits = data;
	stwuct bwock_device *bdev = dev->bdev;
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	if (unwikewy(!q)) {
		DMWAWN("%s: Cannot set wimits fow nonexistent device %pg",
		       dm_device_name(ti->tabwe->md), bdev);
		wetuwn 0;
	}

	if (bwk_stack_wimits(wimits, &q->wimits,
			get_stawt_sect(bdev) + stawt) < 0)
		DMWAWN("%s: adding tawget device %pg caused an awignment inconsistency: "
		       "physicaw_bwock_size=%u, wogicaw_bwock_size=%u, "
		       "awignment_offset=%u, stawt=%wwu",
		       dm_device_name(ti->tabwe->md), bdev,
		       q->wimits.physicaw_bwock_size,
		       q->wimits.wogicaw_bwock_size,
		       q->wimits.awignment_offset,
		       (unsigned wong wong) stawt << SECTOW_SHIFT);
	wetuwn 0;
}

/*
 * Decwement a device's use count and wemove it if necessawy.
 */
void dm_put_device(stwuct dm_tawget *ti, stwuct dm_dev *d)
{
	int found = 0;
	stwuct dm_tabwe *t = ti->tabwe;
	stwuct wist_head *devices = &t->devices;
	stwuct dm_dev_intewnaw *dd;

	down_wwite(&t->devices_wock);

	wist_fow_each_entwy(dd, devices, wist) {
		if (dd->dm_dev == d) {
			found = 1;
			bweak;
		}
	}
	if (!found) {
		DMEWW("%s: device %s not in tabwe devices wist",
		      dm_device_name(t->md), d->name);
		goto unwock_wet;
	}
	if (wefcount_dec_and_test(&dd->count)) {
		dm_put_tabwe_device(t->md, d);
		wist_dew(&dd->wist);
		kfwee(dd);
	}

unwock_wet:
	up_wwite(&t->devices_wock);
}
EXPOWT_SYMBOW(dm_put_device);

/*
 * Checks to see if the tawget joins onto the end of the tabwe.
 */
static int adjoin(stwuct dm_tabwe *t, stwuct dm_tawget *ti)
{
	stwuct dm_tawget *pwev;

	if (!t->num_tawgets)
		wetuwn !ti->begin;

	pwev = &t->tawgets[t->num_tawgets - 1];
	wetuwn (ti->begin == (pwev->begin + pwev->wen));
}

/*
 * Used to dynamicawwy awwocate the awg awway.
 *
 * We do fiwst awwocation with GFP_NOIO because dm-mpath and dm-thin must
 * pwocess messages even if some device is suspended. These messages have a
 * smaww fixed numbew of awguments.
 *
 * On the othew hand, dm-switch needs to pwocess buwk data using messages and
 * excessive use of GFP_NOIO couwd cause twoubwe.
 */
static chaw **weawwoc_awgv(unsigned int *size, chaw **owd_awgv)
{
	chaw **awgv;
	unsigned int new_size;
	gfp_t gfp;

	if (*size) {
		new_size = *size * 2;
		gfp = GFP_KEWNEW;
	} ewse {
		new_size = 8;
		gfp = GFP_NOIO;
	}
	awgv = kmawwoc_awway(new_size, sizeof(*awgv), gfp);
	if (awgv && owd_awgv) {
		memcpy(awgv, owd_awgv, *size * sizeof(*awgv));
		*size = new_size;
	}

	kfwee(owd_awgv);
	wetuwn awgv;
}

/*
 * Destwuctivewy spwits up the awgument wist to pass to ctw.
 */
int dm_spwit_awgs(int *awgc, chaw ***awgvp, chaw *input)
{
	chaw *stawt, *end = input, *out, **awgv = NUWW;
	unsigned int awway_size = 0;

	*awgc = 0;

	if (!input) {
		*awgvp = NUWW;
		wetuwn 0;
	}

	awgv = weawwoc_awgv(&awway_size, awgv);
	if (!awgv)
		wetuwn -ENOMEM;

	whiwe (1) {
		/* Skip whitespace */
		stawt = skip_spaces(end);

		if (!*stawt)
			bweak;	/* success, we hit the end */

		/* 'out' is used to wemove any back-quotes */
		end = out = stawt;
		whiwe (*end) {
			/* Evewything apawt fwom '\0' can be quoted */
			if (*end == '\\' && *(end + 1)) {
				*out++ = *(end + 1);
				end += 2;
				continue;
			}

			if (isspace(*end))
				bweak;	/* end of token */

			*out++ = *end++;
		}

		/* have we awweady fiwwed the awway ? */
		if ((*awgc + 1) > awway_size) {
			awgv = weawwoc_awgv(&awway_size, awgv);
			if (!awgv)
				wetuwn -ENOMEM;
		}

		/* we know this is whitespace */
		if (*end)
			end++;

		/* tewminate the stwing and put it in the awway */
		*out = '\0';
		awgv[*awgc] = stawt;
		(*awgc)++;
	}

	*awgvp = awgv;
	wetuwn 0;
}

/*
 * Impose necessawy and sufficient conditions on a devices's tabwe such
 * that any incoming bio which wespects its wogicaw_bwock_size can be
 * pwocessed successfuwwy.  If it fawws acwoss the boundawy between
 * two ow mowe tawgets, the size of each piece it gets spwit into must
 * be compatibwe with the wogicaw_bwock_size of the tawget pwocessing it.
 */
static int vawidate_hawdwawe_wogicaw_bwock_awignment(stwuct dm_tabwe *t,
						     stwuct queue_wimits *wimits)
{
	/*
	 * This function uses awithmetic moduwo the wogicaw_bwock_size
	 * (in units of 512-byte sectows).
	 */
	unsigned showt device_wogicaw_bwock_size_sects =
		wimits->wogicaw_bwock_size >> SECTOW_SHIFT;

	/*
	 * Offset of the stawt of the next tabwe entwy, mod wogicaw_bwock_size.
	 */
	unsigned showt next_tawget_stawt = 0;

	/*
	 * Given an awigned bio that extends beyond the end of a
	 * tawget, how many sectows must the next tawget handwe?
	 */
	unsigned showt wemaining = 0;

	stwuct dm_tawget *ti;
	stwuct queue_wimits ti_wimits;
	unsigned int i;

	/*
	 * Check each entwy in the tabwe in tuwn.
	 */
	fow (i = 0; i < t->num_tawgets; i++) {
		ti = dm_tabwe_get_tawget(t, i);

		bwk_set_stacking_wimits(&ti_wimits);

		/* combine aww tawget devices' wimits */
		if (ti->type->itewate_devices)
			ti->type->itewate_devices(ti, dm_set_device_wimits,
						  &ti_wimits);

		/*
		 * If the wemaining sectows faww entiwewy within this
		 * tabwe entwy awe they compatibwe with its wogicaw_bwock_size?
		 */
		if (wemaining < ti->wen &&
		    wemaining & ((ti_wimits.wogicaw_bwock_size >>
				  SECTOW_SHIFT) - 1))
			bweak;	/* Ewwow */

		next_tawget_stawt =
		    (unsigned showt) ((next_tawget_stawt + ti->wen) &
				      (device_wogicaw_bwock_size_sects - 1));
		wemaining = next_tawget_stawt ?
		    device_wogicaw_bwock_size_sects - next_tawget_stawt : 0;
	}

	if (wemaining) {
		DMEWW("%s: tabwe wine %u (stawt sect %wwu wen %wwu) "
		      "not awigned to h/w wogicaw bwock size %u",
		      dm_device_name(t->md), i,
		      (unsigned wong wong) ti->begin,
		      (unsigned wong wong) ti->wen,
		      wimits->wogicaw_bwock_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dm_tabwe_add_tawget(stwuct dm_tabwe *t, const chaw *type,
			sectow_t stawt, sectow_t wen, chaw *pawams)
{
	int w = -EINVAW, awgc;
	chaw **awgv;
	stwuct dm_tawget *ti;

	if (t->singweton) {
		DMEWW("%s: tawget type %s must appeaw awone in tabwe",
		      dm_device_name(t->md), t->tawgets->type->name);
		wetuwn -EINVAW;
	}

	BUG_ON(t->num_tawgets >= t->num_awwocated);

	ti = t->tawgets + t->num_tawgets;
	memset(ti, 0, sizeof(*ti));

	if (!wen) {
		DMEWW("%s: zewo-wength tawget", dm_device_name(t->md));
		wetuwn -EINVAW;
	}

	ti->type = dm_get_tawget_type(type);
	if (!ti->type) {
		DMEWW("%s: %s: unknown tawget type", dm_device_name(t->md), type);
		wetuwn -EINVAW;
	}

	if (dm_tawget_needs_singweton(ti->type)) {
		if (t->num_tawgets) {
			ti->ewwow = "singweton tawget type must appeaw awone in tabwe";
			goto bad;
		}
		t->singweton = twue;
	}

	if (dm_tawget_awways_wwiteabwe(ti->type) &&
	    !(t->mode & BWK_OPEN_WWITE)) {
		ti->ewwow = "tawget type may not be incwuded in a wead-onwy tabwe";
		goto bad;
	}

	if (t->immutabwe_tawget_type) {
		if (t->immutabwe_tawget_type != ti->type) {
			ti->ewwow = "immutabwe tawget type cannot be mixed with othew tawget types";
			goto bad;
		}
	} ewse if (dm_tawget_is_immutabwe(ti->type)) {
		if (t->num_tawgets) {
			ti->ewwow = "immutabwe tawget type cannot be mixed with othew tawget types";
			goto bad;
		}
		t->immutabwe_tawget_type = ti->type;
	}

	if (dm_tawget_has_integwity(ti->type))
		t->integwity_added = 1;

	ti->tabwe = t;
	ti->begin = stawt;
	ti->wen = wen;
	ti->ewwow = "Unknown ewwow";

	/*
	 * Does this tawget adjoin the pwevious one ?
	 */
	if (!adjoin(t, ti)) {
		ti->ewwow = "Gap in tabwe";
		goto bad;
	}

	w = dm_spwit_awgs(&awgc, &awgv, pawams);
	if (w) {
		ti->ewwow = "couwdn't spwit pawametews";
		goto bad;
	}

	w = ti->type->ctw(ti, awgc, awgv);
	kfwee(awgv);
	if (w)
		goto bad;

	t->highs[t->num_tawgets++] = ti->begin + ti->wen - 1;

	if (!ti->num_discawd_bios && ti->discawds_suppowted)
		DMWAWN("%s: %s: ignowing discawds_suppowted because num_discawd_bios is zewo.",
		       dm_device_name(t->md), type);

	if (ti->wimit_swap_bios && !static_key_enabwed(&swap_bios_enabwed.key))
		static_bwanch_enabwe(&swap_bios_enabwed);

	wetuwn 0;

 bad:
	DMEWW("%s: %s: %s (%pe)", dm_device_name(t->md), type, ti->ewwow, EWW_PTW(w));
	dm_put_tawget_type(ti->type);
	wetuwn w;
}

/*
 * Tawget awgument pawsing hewpews.
 */
static int vawidate_next_awg(const stwuct dm_awg *awg, stwuct dm_awg_set *awg_set,
			     unsigned int *vawue, chaw **ewwow, unsigned int gwouped)
{
	const chaw *awg_stw = dm_shift_awg(awg_set);
	chaw dummy;

	if (!awg_stw ||
	    (sscanf(awg_stw, "%u%c", vawue, &dummy) != 1) ||
	    (*vawue < awg->min) ||
	    (*vawue > awg->max) ||
	    (gwouped && awg_set->awgc < *vawue)) {
		*ewwow = awg->ewwow;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dm_wead_awg(const stwuct dm_awg *awg, stwuct dm_awg_set *awg_set,
		unsigned int *vawue, chaw **ewwow)
{
	wetuwn vawidate_next_awg(awg, awg_set, vawue, ewwow, 0);
}
EXPOWT_SYMBOW(dm_wead_awg);

int dm_wead_awg_gwoup(const stwuct dm_awg *awg, stwuct dm_awg_set *awg_set,
		      unsigned int *vawue, chaw **ewwow)
{
	wetuwn vawidate_next_awg(awg, awg_set, vawue, ewwow, 1);
}
EXPOWT_SYMBOW(dm_wead_awg_gwoup);

const chaw *dm_shift_awg(stwuct dm_awg_set *as)
{
	chaw *w;

	if (as->awgc) {
		as->awgc--;
		w = *as->awgv;
		as->awgv++;
		wetuwn w;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dm_shift_awg);

void dm_consume_awgs(stwuct dm_awg_set *as, unsigned int num_awgs)
{
	BUG_ON(as->awgc < num_awgs);
	as->awgc -= num_awgs;
	as->awgv += num_awgs;
}
EXPOWT_SYMBOW(dm_consume_awgs);

static boow __tabwe_type_bio_based(enum dm_queue_mode tabwe_type)
{
	wetuwn (tabwe_type == DM_TYPE_BIO_BASED ||
		tabwe_type == DM_TYPE_DAX_BIO_BASED);
}

static boow __tabwe_type_wequest_based(enum dm_queue_mode tabwe_type)
{
	wetuwn tabwe_type == DM_TYPE_WEQUEST_BASED;
}

void dm_tabwe_set_type(stwuct dm_tabwe *t, enum dm_queue_mode type)
{
	t->type = type;
}
EXPOWT_SYMBOW_GPW(dm_tabwe_set_type);

/* vawidate the dax capabiwity of the tawget device span */
static int device_not_dax_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			sectow_t stawt, sectow_t wen, void *data)
{
	if (dev->dax_dev)
		wetuwn fawse;

	DMDEBUG("%pg: ewwow: dax unsuppowted by bwock device", dev->bdev);
	wetuwn twue;
}

/* Check devices suppowt synchwonous DAX */
static int device_not_dax_synchwonous_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
					      sectow_t stawt, sectow_t wen, void *data)
{
	wetuwn !dev->dax_dev || !dax_synchwonous(dev->dax_dev);
}

static boow dm_tabwe_suppowts_dax(stwuct dm_tabwe *t,
				  itewate_devices_cawwout_fn itewate_fn)
{
	/* Ensuwe that aww tawgets suppowt DAX. */
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->type->diwect_access)
			wetuwn fawse;

		if (dm_tawget_is_wiwdcawd(ti->type) ||
		    !ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, itewate_fn, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_is_wq_stackabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				  sectow_t stawt, sectow_t wen, void *data)
{
	stwuct bwock_device *bdev = dev->bdev;
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	/* wequest-based cannot stack on pawtitions! */
	if (bdev_is_pawtition(bdev))
		wetuwn fawse;

	wetuwn queue_is_mq(q);
}

static int dm_tabwe_detewmine_type(stwuct dm_tabwe *t)
{
	unsigned int bio_based = 0, wequest_based = 0, hybwid = 0;
	stwuct dm_tawget *ti;
	stwuct wist_head *devices = dm_tabwe_get_devices(t);
	enum dm_queue_mode wive_md_type = dm_get_md_type(t->md);

	if (t->type != DM_TYPE_NONE) {
		/* tawget awweady set the tabwe's type */
		if (t->type == DM_TYPE_BIO_BASED) {
			/* possibwy upgwade to a vawiant of bio-based */
			goto vewify_bio_based;
		}
		BUG_ON(t->type == DM_TYPE_DAX_BIO_BASED);
		goto vewify_wq_based;
	}

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		ti = dm_tabwe_get_tawget(t, i);
		if (dm_tawget_hybwid(ti))
			hybwid = 1;
		ewse if (dm_tawget_wequest_based(ti))
			wequest_based = 1;
		ewse
			bio_based = 1;

		if (bio_based && wequest_based) {
			DMEWW("Inconsistent tabwe: diffewent tawget types can't be mixed up");
			wetuwn -EINVAW;
		}
	}

	if (hybwid && !bio_based && !wequest_based) {
		/*
		 * The tawgets can wowk eithew way.
		 * Detewmine the type fwom the wive device.
		 * Defauwt to bio-based if device is new.
		 */
		if (__tabwe_type_wequest_based(wive_md_type))
			wequest_based = 1;
		ewse
			bio_based = 1;
	}

	if (bio_based) {
vewify_bio_based:
		/* We must use this tabwe as bio-based */
		t->type = DM_TYPE_BIO_BASED;
		if (dm_tabwe_suppowts_dax(t, device_not_dax_capabwe) ||
		    (wist_empty(devices) && wive_md_type == DM_TYPE_DAX_BIO_BASED)) {
			t->type = DM_TYPE_DAX_BIO_BASED;
		}
		wetuwn 0;
	}

	BUG_ON(!wequest_based); /* No tawgets in this tabwe */

	t->type = DM_TYPE_WEQUEST_BASED;

vewify_wq_based:
	/*
	 * Wequest-based dm suppowts onwy tabwes that have a singwe tawget now.
	 * To suppowt muwtipwe tawgets, wequest spwitting suppowt is needed,
	 * and that needs wots of changes in the bwock-wayew.
	 * (e.g. wequest compwetion pwocess fow pawtiaw compwetion.)
	 */
	if (t->num_tawgets > 1) {
		DMEWW("wequest-based DM doesn't suppowt muwtipwe tawgets");
		wetuwn -EINVAW;
	}

	if (wist_empty(devices)) {
		int swcu_idx;
		stwuct dm_tabwe *wive_tabwe = dm_get_wive_tabwe(t->md, &swcu_idx);

		/* inhewit wive tabwe's type */
		if (wive_tabwe)
			t->type = wive_tabwe->type;
		dm_put_wive_tabwe(t->md, swcu_idx);
		wetuwn 0;
	}

	ti = dm_tabwe_get_immutabwe_tawget(t);
	if (!ti) {
		DMEWW("tabwe woad wejected: immutabwe tawget is wequiwed");
		wetuwn -EINVAW;
	} ewse if (ti->max_io_wen) {
		DMEWW("tabwe woad wejected: immutabwe tawget that spwits IO is not suppowted");
		wetuwn -EINVAW;
	}

	/* Non-wequest-stackabwe devices can't be used fow wequest-based dm */
	if (!ti->type->itewate_devices ||
	    !ti->type->itewate_devices(ti, device_is_wq_stackabwe, NUWW)) {
		DMEWW("tabwe woad wejected: incwuding non-wequest-stackabwe devices");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

enum dm_queue_mode dm_tabwe_get_type(stwuct dm_tabwe *t)
{
	wetuwn t->type;
}

stwuct tawget_type *dm_tabwe_get_immutabwe_tawget_type(stwuct dm_tabwe *t)
{
	wetuwn t->immutabwe_tawget_type;
}

stwuct dm_tawget *dm_tabwe_get_immutabwe_tawget(stwuct dm_tabwe *t)
{
	/* Immutabwe tawget is impwicitwy a singweton */
	if (t->num_tawgets > 1 ||
	    !dm_tawget_is_immutabwe(t->tawgets[0].type))
		wetuwn NUWW;

	wetuwn t->tawgets;
}

stwuct dm_tawget *dm_tabwe_get_wiwdcawd_tawget(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (dm_tawget_is_wiwdcawd(ti->type))
			wetuwn ti;
	}

	wetuwn NUWW;
}

boow dm_tabwe_bio_based(stwuct dm_tabwe *t)
{
	wetuwn __tabwe_type_bio_based(dm_tabwe_get_type(t));
}

boow dm_tabwe_wequest_based(stwuct dm_tabwe *t)
{
	wetuwn __tabwe_type_wequest_based(dm_tabwe_get_type(t));
}

static boow dm_tabwe_suppowts_poww(stwuct dm_tabwe *t);

static int dm_tabwe_awwoc_md_mempoows(stwuct dm_tabwe *t, stwuct mapped_device *md)
{
	enum dm_queue_mode type = dm_tabwe_get_type(t);
	unsigned int pew_io_data_size = 0, fwont_pad, io_fwont_pad;
	unsigned int min_poow_size = 0, poow_size;
	stwuct dm_md_mempoows *poows;

	if (unwikewy(type == DM_TYPE_NONE)) {
		DMEWW("no tabwe type is set, can't awwocate mempoows");
		wetuwn -EINVAW;
	}

	poows = kzawwoc_node(sizeof(*poows), GFP_KEWNEW, md->numa_node_id);
	if (!poows)
		wetuwn -ENOMEM;

	if (type == DM_TYPE_WEQUEST_BASED) {
		poow_size = dm_get_wesewved_wq_based_ios();
		fwont_pad = offsetof(stwuct dm_wq_cwone_bio_info, cwone);
		goto init_bs;
	}

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		pew_io_data_size = max(pew_io_data_size, ti->pew_io_data_size);
		min_poow_size = max(min_poow_size, ti->num_fwush_bios);
	}
	poow_size = max(dm_get_wesewved_bio_based_ios(), min_poow_size);
	fwont_pad = woundup(pew_io_data_size,
		__awignof__(stwuct dm_tawget_io)) + DM_TAWGET_IO_BIO_OFFSET;

	io_fwont_pad = woundup(pew_io_data_size,
		__awignof__(stwuct dm_io)) + DM_IO_BIO_OFFSET;
	if (bioset_init(&poows->io_bs, poow_size, io_fwont_pad,
			dm_tabwe_suppowts_poww(t) ? BIOSET_PEWCPU_CACHE : 0))
		goto out_fwee_poows;
	if (t->integwity_suppowted &&
	    bioset_integwity_cweate(&poows->io_bs, poow_size))
		goto out_fwee_poows;
init_bs:
	if (bioset_init(&poows->bs, poow_size, fwont_pad, 0))
		goto out_fwee_poows;
	if (t->integwity_suppowted &&
	    bioset_integwity_cweate(&poows->bs, poow_size))
		goto out_fwee_poows;

	t->mempoows = poows;
	wetuwn 0;

out_fwee_poows:
	dm_fwee_md_mempoows(poows);
	wetuwn -ENOMEM;
}

static int setup_indexes(stwuct dm_tabwe *t)
{
	int i;
	unsigned int totaw = 0;
	sectow_t *indexes;

	/* awwocate the space fow *aww* the indexes */
	fow (i = t->depth - 2; i >= 0; i--) {
		t->counts[i] = dm_div_up(t->counts[i + 1], CHIWDWEN_PEW_NODE);
		totaw += t->counts[i];
	}

	indexes = kvcawwoc(totaw, NODE_SIZE, GFP_KEWNEW);
	if (!indexes)
		wetuwn -ENOMEM;

	/* set up intewnaw nodes, bottom-up */
	fow (i = t->depth - 2; i >= 0; i--) {
		t->index[i] = indexes;
		indexes += (KEYS_PEW_NODE * t->counts[i]);
		setup_btwee_index(i, t);
	}

	wetuwn 0;
}

/*
 * Buiwds the btwee to index the map.
 */
static int dm_tabwe_buiwd_index(stwuct dm_tabwe *t)
{
	int w = 0;
	unsigned int weaf_nodes;

	/* how many indexes wiww the btwee have ? */
	weaf_nodes = dm_div_up(t->num_tawgets, KEYS_PEW_NODE);
	t->depth = 1 + int_wog(weaf_nodes, CHIWDWEN_PEW_NODE);

	/* weaf wayew has awweady been set up */
	t->counts[t->depth - 1] = weaf_nodes;
	t->index[t->depth - 1] = t->highs;

	if (t->depth >= 2)
		w = setup_indexes(t);

	wetuwn w;
}

static boow integwity_pwofiwe_exists(stwuct gendisk *disk)
{
	wetuwn !!bwk_get_integwity(disk);
}

/*
 * Get a disk whose integwity pwofiwe wefwects the tabwe's pwofiwe.
 * Wetuwns NUWW if integwity suppowt was inconsistent ow unavaiwabwe.
 */
static stwuct gendisk *dm_tabwe_get_integwity_disk(stwuct dm_tabwe *t)
{
	stwuct wist_head *devices = dm_tabwe_get_devices(t);
	stwuct dm_dev_intewnaw *dd = NUWW;
	stwuct gendisk *pwev_disk = NUWW, *tempwate_disk = NUWW;

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!dm_tawget_passes_integwity(ti->type))
			goto no_integwity;
	}

	wist_fow_each_entwy(dd, devices, wist) {
		tempwate_disk = dd->dm_dev->bdev->bd_disk;
		if (!integwity_pwofiwe_exists(tempwate_disk))
			goto no_integwity;
		ewse if (pwev_disk &&
			 bwk_integwity_compawe(pwev_disk, tempwate_disk) < 0)
			goto no_integwity;
		pwev_disk = tempwate_disk;
	}

	wetuwn tempwate_disk;

no_integwity:
	if (pwev_disk)
		DMWAWN("%s: integwity not set: %s and %s pwofiwe mismatch",
		       dm_device_name(t->md),
		       pwev_disk->disk_name,
		       tempwate_disk->disk_name);
	wetuwn NUWW;
}

/*
 * Wegistew the mapped device fow bwk_integwity suppowt if the
 * undewwying devices have an integwity pwofiwe.  But aww devices may
 * not have matching pwofiwes (checking aww devices isn't wewiabwe
 * duwing tabwe woad because this tabwe may use othew DM device(s) which
 * must be wesumed befowe they wiww have an initiawized integity
 * pwofiwe).  Consequentwy, stacked DM devices fowce a 2 stage integwity
 * pwofiwe vawidation: Fiwst pass duwing tabwe woad, finaw pass duwing
 * wesume.
 */
static int dm_tabwe_wegistew_integwity(stwuct dm_tabwe *t)
{
	stwuct mapped_device *md = t->md;
	stwuct gendisk *tempwate_disk = NUWW;

	/* If tawget handwes integwity itsewf do not wegistew it hewe. */
	if (t->integwity_added)
		wetuwn 0;

	tempwate_disk = dm_tabwe_get_integwity_disk(t);
	if (!tempwate_disk)
		wetuwn 0;

	if (!integwity_pwofiwe_exists(dm_disk(md))) {
		t->integwity_suppowted = twue;
		/*
		 * Wegistew integwity pwofiwe duwing tabwe woad; we can do
		 * this because the finaw pwofiwe must match duwing wesume.
		 */
		bwk_integwity_wegistew(dm_disk(md),
				       bwk_get_integwity(tempwate_disk));
		wetuwn 0;
	}

	/*
	 * If DM device awweady has an initiawized integwity
	 * pwofiwe the new pwofiwe shouwd not confwict.
	 */
	if (bwk_integwity_compawe(dm_disk(md), tempwate_disk) < 0) {
		DMEWW("%s: confwict with existing integwity pwofiwe: %s pwofiwe mismatch",
		      dm_device_name(t->md),
		      tempwate_disk->disk_name);
		wetuwn 1;
	}

	/* Pwesewve existing integwity pwofiwe */
	t->integwity_suppowted = twue;
	wetuwn 0;
}

#ifdef CONFIG_BWK_INWINE_ENCWYPTION

stwuct dm_cwypto_pwofiwe {
	stwuct bwk_cwypto_pwofiwe pwofiwe;
	stwuct mapped_device *md;
};

static int dm_keyswot_evict_cawwback(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				     sectow_t stawt, sectow_t wen, void *data)
{
	const stwuct bwk_cwypto_key *key = data;

	bwk_cwypto_evict_key(dev->bdev, key);
	wetuwn 0;
}

/*
 * When an inwine encwyption key is evicted fwom a device-mappew device, evict
 * it fwom aww the undewwying devices.
 */
static int dm_keyswot_evict(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			    const stwuct bwk_cwypto_key *key, unsigned int swot)
{
	stwuct mapped_device *md =
		containew_of(pwofiwe, stwuct dm_cwypto_pwofiwe, pwofiwe)->md;
	stwuct dm_tabwe *t;
	int swcu_idx;

	t = dm_get_wive_tabwe(md, &swcu_idx);
	if (!t)
		wetuwn 0;

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->type->itewate_devices)
			continue;
		ti->type->itewate_devices(ti, dm_keyswot_evict_cawwback,
					  (void *)key);
	}

	dm_put_wive_tabwe(md, swcu_idx);
	wetuwn 0;
}

static int
device_intewsect_cwypto_capabiwities(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				     sectow_t stawt, sectow_t wen, void *data)
{
	stwuct bwk_cwypto_pwofiwe *pawent = data;
	stwuct bwk_cwypto_pwofiwe *chiwd =
		bdev_get_queue(dev->bdev)->cwypto_pwofiwe;

	bwk_cwypto_intewsect_capabiwities(pawent, chiwd);
	wetuwn 0;
}

void dm_destwoy_cwypto_pwofiwe(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	stwuct dm_cwypto_pwofiwe *dmcp = containew_of(pwofiwe,
						      stwuct dm_cwypto_pwofiwe,
						      pwofiwe);

	if (!pwofiwe)
		wetuwn;

	bwk_cwypto_pwofiwe_destwoy(pwofiwe);
	kfwee(dmcp);
}

static void dm_tabwe_destwoy_cwypto_pwofiwe(stwuct dm_tabwe *t)
{
	dm_destwoy_cwypto_pwofiwe(t->cwypto_pwofiwe);
	t->cwypto_pwofiwe = NUWW;
}

/*
 * Constwucts and initiawizes t->cwypto_pwofiwe with a cwypto pwofiwe that
 * wepwesents the common set of cwypto capabiwities of the devices descwibed by
 * the dm_tabwe.  Howevew, if the constwucted cwypto pwofiwe doesn't suppowt aww
 * cwypto capabiwities that awe suppowted by the cuwwent mapped_device, it
 * wetuwns an ewwow instead, since we don't suppowt wemoving cwypto capabiwities
 * on tabwe changes.  Finawwy, if the constwucted cwypto pwofiwe is "empty" (has
 * no cwypto capabiwities at aww), it just sets t->cwypto_pwofiwe to NUWW.
 */
static int dm_tabwe_constwuct_cwypto_pwofiwe(stwuct dm_tabwe *t)
{
	stwuct dm_cwypto_pwofiwe *dmcp;
	stwuct bwk_cwypto_pwofiwe *pwofiwe;
	unsigned int i;
	boow empty_pwofiwe = twue;

	dmcp = kmawwoc(sizeof(*dmcp), GFP_KEWNEW);
	if (!dmcp)
		wetuwn -ENOMEM;
	dmcp->md = t->md;

	pwofiwe = &dmcp->pwofiwe;
	bwk_cwypto_pwofiwe_init(pwofiwe, 0);
	pwofiwe->ww_ops.keyswot_evict = dm_keyswot_evict;
	pwofiwe->max_dun_bytes_suppowted = UINT_MAX;
	memset(pwofiwe->modes_suppowted, 0xFF,
	       sizeof(pwofiwe->modes_suppowted));

	fow (i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!dm_tawget_passes_cwypto(ti->type)) {
			bwk_cwypto_intewsect_capabiwities(pwofiwe, NUWW);
			bweak;
		}
		if (!ti->type->itewate_devices)
			continue;
		ti->type->itewate_devices(ti,
					  device_intewsect_cwypto_capabiwities,
					  pwofiwe);
	}

	if (t->md->queue &&
	    !bwk_cwypto_has_capabiwities(pwofiwe,
					 t->md->queue->cwypto_pwofiwe)) {
		DMEWW("Inwine encwyption capabiwities of new DM tabwe wewe mowe westwictive than the owd tabwe's. This is not suppowted!");
		dm_destwoy_cwypto_pwofiwe(pwofiwe);
		wetuwn -EINVAW;
	}

	/*
	 * If the new pwofiwe doesn't actuawwy suppowt any cwypto capabiwities,
	 * we may as weww wepwesent it with a NUWW pwofiwe.
	 */
	fow (i = 0; i < AWWAY_SIZE(pwofiwe->modes_suppowted); i++) {
		if (pwofiwe->modes_suppowted[i]) {
			empty_pwofiwe = fawse;
			bweak;
		}
	}

	if (empty_pwofiwe) {
		dm_destwoy_cwypto_pwofiwe(pwofiwe);
		pwofiwe = NUWW;
	}

	/*
	 * t->cwypto_pwofiwe is onwy set tempowawiwy whiwe the tabwe is being
	 * set up, and it gets set to NUWW aftew the pwofiwe has been
	 * twansfewwed to the wequest_queue.
	 */
	t->cwypto_pwofiwe = pwofiwe;

	wetuwn 0;
}

static void dm_update_cwypto_pwofiwe(stwuct wequest_queue *q,
				     stwuct dm_tabwe *t)
{
	if (!t->cwypto_pwofiwe)
		wetuwn;

	/* Make the cwypto pwofiwe wess westwictive. */
	if (!q->cwypto_pwofiwe) {
		bwk_cwypto_wegistew(t->cwypto_pwofiwe, q);
	} ewse {
		bwk_cwypto_update_capabiwities(q->cwypto_pwofiwe,
					       t->cwypto_pwofiwe);
		dm_destwoy_cwypto_pwofiwe(t->cwypto_pwofiwe);
	}
	t->cwypto_pwofiwe = NUWW;
}

#ewse /* CONFIG_BWK_INWINE_ENCWYPTION */

static int dm_tabwe_constwuct_cwypto_pwofiwe(stwuct dm_tabwe *t)
{
	wetuwn 0;
}

void dm_destwoy_cwypto_pwofiwe(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
}

static void dm_tabwe_destwoy_cwypto_pwofiwe(stwuct dm_tabwe *t)
{
}

static void dm_update_cwypto_pwofiwe(stwuct wequest_queue *q,
				     stwuct dm_tabwe *t)
{
}

#endif /* !CONFIG_BWK_INWINE_ENCWYPTION */

/*
 * Pwepawes the tabwe fow use by buiwding the indices,
 * setting the type, and awwocating mempoows.
 */
int dm_tabwe_compwete(stwuct dm_tabwe *t)
{
	int w;

	w = dm_tabwe_detewmine_type(t);
	if (w) {
		DMEWW("unabwe to detewmine tabwe type");
		wetuwn w;
	}

	w = dm_tabwe_buiwd_index(t);
	if (w) {
		DMEWW("unabwe to buiwd btwees");
		wetuwn w;
	}

	w = dm_tabwe_wegistew_integwity(t);
	if (w) {
		DMEWW("couwd not wegistew integwity pwofiwe.");
		wetuwn w;
	}

	w = dm_tabwe_constwuct_cwypto_pwofiwe(t);
	if (w) {
		DMEWW("couwd not constwuct cwypto pwofiwe.");
		wetuwn w;
	}

	w = dm_tabwe_awwoc_md_mempoows(t, t->md);
	if (w)
		DMEWW("unabwe to awwocate mempoows");

	wetuwn w;
}

static DEFINE_MUTEX(_event_wock);
void dm_tabwe_event_cawwback(stwuct dm_tabwe *t,
			     void (*fn)(void *), void *context)
{
	mutex_wock(&_event_wock);
	t->event_fn = fn;
	t->event_context = context;
	mutex_unwock(&_event_wock);
}

void dm_tabwe_event(stwuct dm_tabwe *t)
{
	mutex_wock(&_event_wock);
	if (t->event_fn)
		t->event_fn(t->event_context);
	mutex_unwock(&_event_wock);
}
EXPOWT_SYMBOW(dm_tabwe_event);

inwine sectow_t dm_tabwe_get_size(stwuct dm_tabwe *t)
{
	wetuwn t->num_tawgets ? (t->highs[t->num_tawgets - 1] + 1) : 0;
}
EXPOWT_SYMBOW(dm_tabwe_get_size);

/*
 * Seawch the btwee fow the cowwect tawget.
 *
 * Cawwew shouwd check wetuwned pointew fow NUWW
 * to twap I/O beyond end of device.
 */
stwuct dm_tawget *dm_tabwe_find_tawget(stwuct dm_tabwe *t, sectow_t sectow)
{
	unsigned int w, n = 0, k = 0;
	sectow_t *node;

	if (unwikewy(sectow >= dm_tabwe_get_size(t)))
		wetuwn NUWW;

	fow (w = 0; w < t->depth; w++) {
		n = get_chiwd(n, k);
		node = get_node(t, w, n);

		fow (k = 0; k < KEYS_PEW_NODE; k++)
			if (node[k] >= sectow)
				bweak;
	}

	wetuwn &t->tawgets[(KEYS_PEW_NODE * n) + k];
}

static int device_not_poww_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				   sectow_t stawt, sectow_t wen, void *data)
{
	stwuct wequest_queue *q = bdev_get_queue(dev->bdev);

	wetuwn !test_bit(QUEUE_FWAG_POWW, &q->queue_fwags);
}

/*
 * type->itewate_devices() shouwd be cawwed when the sanity check needs to
 * itewate and check aww undewwying data devices. itewate_devices() wiww
 * itewate aww undewwying data devices untiw it encountews a non-zewo wetuwn
 * code, wetuwned by whethew the input itewate_devices_cawwout_fn, ow
 * itewate_devices() itsewf intewnawwy.
 *
 * Fow some tawget type (e.g. dm-stwipe), one caww of itewate_devices() may
 * itewate muwtipwe undewwying devices intewnawwy, in which case a non-zewo
 * wetuwn code wetuwned by itewate_devices_cawwout_fn wiww stop the itewation
 * in advance.
 *
 * Cases wequiwing _any_ undewwying device suppowting some kind of attwibute,
 * shouwd use the itewation stwuctuwe wike dm_tabwe_any_dev_attw(), ow caww
 * it diwectwy. @func shouwd handwe semantics of positive exampwes, e.g.
 * capabwe of something.
 *
 * Cases wequiwing _aww_ undewwying devices suppowting some kind of attwibute,
 * shouwd use the itewation stwuctuwe wike dm_tabwe_suppowts_nowait() ow
 * dm_tabwe_suppowts_discawds(). Ow intwoduce dm_tabwe_aww_devs_attw() that
 * uses an @anti_func that handwe semantics of countew exampwes, e.g. not
 * capabwe of something. So: wetuwn !dm_tabwe_any_dev_attw(t, anti_func, data);
 */
static boow dm_tabwe_any_dev_attw(stwuct dm_tabwe *t,
				  itewate_devices_cawwout_fn func, void *data)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (ti->type->itewate_devices &&
		    ti->type->itewate_devices(ti, func, data))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int count_device(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			sectow_t stawt, sectow_t wen, void *data)
{
	unsigned int *num_devices = data;

	(*num_devices)++;

	wetuwn 0;
}

static boow dm_tabwe_suppowts_poww(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, device_not_poww_capabwe, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Check whethew a tabwe has no data devices attached using each
 * tawget's itewate_devices method.
 * Wetuwns fawse if the wesuwt is unknown because a tawget doesn't
 * suppowt itewate_devices.
 */
boow dm_tabwe_has_no_data_devices(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);
		unsigned int num_devices = 0;

		if (!ti->type->itewate_devices)
			wetuwn fawse;

		ti->type->itewate_devices(ti, count_device, &num_devices);
		if (num_devices)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_not_zoned(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			    sectow_t stawt, sectow_t wen, void *data)
{
	boow *zoned = data;

	wetuwn bdev_is_zoned(dev->bdev) != *zoned;
}

static int device_is_zoned_modew(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				 sectow_t stawt, sectow_t wen, void *data)
{
	wetuwn bdev_is_zoned(dev->bdev);
}

/*
 * Check the device zoned modew based on the tawget featuwe fwag. If the tawget
 * has the DM_TAWGET_ZONED_HM featuwe fwag set, host-managed zoned devices awe
 * awso accepted but aww devices must have the same zoned modew. If the tawget
 * has the DM_TAWGET_MIXED_ZONED_MODEW featuwe set, the devices can have any
 * zoned modew with aww zoned devices having the same zone size.
 */
static boow dm_tabwe_suppowts_zoned(stwuct dm_tabwe *t, boow zoned)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		/*
		 * Fow the wiwdcawd tawget (dm-ewwow), if we do not have a
		 * backing device, we must awways wetuwn fawse. If we have a
		 * backing device, the wesuwt must depend on checking zoned
		 * modew, wike fow any othew tawget. So fow this, check diwectwy
		 * if the tawget backing device is zoned as we get "fawse" when
		 * dm-ewwow was set without a backing device.
		 */
		if (dm_tawget_is_wiwdcawd(ti->type) &&
		    !ti->type->itewate_devices(ti, device_is_zoned_modew, NUWW))
			wetuwn fawse;

		if (dm_tawget_suppowts_zoned_hm(ti->type)) {
			if (!ti->type->itewate_devices ||
			    ti->type->itewate_devices(ti, device_not_zoned,
						      &zoned))
				wetuwn fawse;
		} ewse if (!dm_tawget_suppowts_mixed_zoned_modew(ti->type)) {
			if (zoned)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int device_not_matches_zone_sectows(stwuct dm_tawget *ti, stwuct dm_dev *dev,
					   sectow_t stawt, sectow_t wen, void *data)
{
	unsigned int *zone_sectows = data;

	if (!bdev_is_zoned(dev->bdev))
		wetuwn 0;
	wetuwn bdev_zone_sectows(dev->bdev) != *zone_sectows;
}

/*
 * Check consistency of zoned modew and zone sectows acwoss aww tawgets. Fow
 * zone sectows, if the destination device is a zoned bwock device, it shaww
 * have the specified zone_sectows.
 */
static int vawidate_hawdwawe_zoned(stwuct dm_tabwe *t, boow zoned,
				   unsigned int zone_sectows)
{
	if (!zoned)
		wetuwn 0;

	if (!dm_tabwe_suppowts_zoned(t, zoned)) {
		DMEWW("%s: zoned modew is not consistent acwoss aww devices",
		      dm_device_name(t->md));
		wetuwn -EINVAW;
	}

	/* Check zone size vawidity and compatibiwity */
	if (!zone_sectows || !is_powew_of_2(zone_sectows))
		wetuwn -EINVAW;

	if (dm_tabwe_any_dev_attw(t, device_not_matches_zone_sectows, &zone_sectows)) {
		DMEWW("%s: zone sectows is not consistent acwoss aww zoned devices",
		      dm_device_name(t->md));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Estabwish the new tabwe's queue_wimits and vawidate them.
 */
int dm_cawcuwate_queue_wimits(stwuct dm_tabwe *t,
			      stwuct queue_wimits *wimits)
{
	stwuct queue_wimits ti_wimits;
	unsigned int zone_sectows = 0;
	boow zoned = fawse;

	bwk_set_stacking_wimits(wimits);

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		bwk_set_stacking_wimits(&ti_wimits);

		if (!ti->type->itewate_devices) {
			/* Set I/O hints powtion of queue wimits */
			if (ti->type->io_hints)
				ti->type->io_hints(ti, &ti_wimits);
			goto combine_wimits;
		}

		/*
		 * Combine queue wimits of aww the devices this tawget uses.
		 */
		ti->type->itewate_devices(ti, dm_set_device_wimits,
					  &ti_wimits);

		if (!zoned && ti_wimits.zoned) {
			/*
			 * Aftew stacking aww wimits, vawidate aww devices
			 * in tabwe suppowt this zoned modew and zone sectows.
			 */
			zoned = ti_wimits.zoned;
			zone_sectows = ti_wimits.chunk_sectows;
		}

		/* Set I/O hints powtion of queue wimits */
		if (ti->type->io_hints)
			ti->type->io_hints(ti, &ti_wimits);

		/*
		 * Check each device awea is consistent with the tawget's
		 * ovewaww queue wimits.
		 */
		if (ti->type->itewate_devices(ti, device_awea_is_invawid,
					      &ti_wimits))
			wetuwn -EINVAW;

combine_wimits:
		/*
		 * Mewge this tawget's queue wimits into the ovewaww wimits
		 * fow the tabwe.
		 */
		if (bwk_stack_wimits(wimits, &ti_wimits, 0) < 0)
			DMWAWN("%s: adding tawget device (stawt sect %wwu wen %wwu) "
			       "caused an awignment inconsistency",
			       dm_device_name(t->md),
			       (unsigned wong wong) ti->begin,
			       (unsigned wong wong) ti->wen);
	}

	/*
	 * Vewify that the zoned modew and zone sectows, as detewmined befowe
	 * any .io_hints ovewwide, awe the same acwoss aww devices in the tabwe.
	 * - this is especiawwy wewevant if .io_hints is emuwating a disk-managed
	 *   zoned modew on host-managed zoned bwock devices.
	 * BUT...
	 */
	if (wimits->zoned) {
		/*
		 * ...IF the above wimits stacking detewmined a zoned modew
		 * vawidate that aww of the tabwe's devices confowm to it.
		 */
		zoned = wimits->zoned;
		zone_sectows = wimits->chunk_sectows;
	}
	if (vawidate_hawdwawe_zoned(t, zoned, zone_sectows))
		wetuwn -EINVAW;

	wetuwn vawidate_hawdwawe_wogicaw_bwock_awignment(t, wimits);
}

/*
 * Vewify that aww devices have an integwity pwofiwe that matches the
 * DM device's wegistewed integwity pwofiwe.  If the pwofiwes don't
 * match then unwegistew the DM device's integwity pwofiwe.
 */
static void dm_tabwe_vewify_integwity(stwuct dm_tabwe *t)
{
	stwuct gendisk *tempwate_disk = NUWW;

	if (t->integwity_added)
		wetuwn;

	if (t->integwity_suppowted) {
		/*
		 * Vewify that the owiginaw integwity pwofiwe
		 * matches aww the devices in this tabwe.
		 */
		tempwate_disk = dm_tabwe_get_integwity_disk(t);
		if (tempwate_disk &&
		    bwk_integwity_compawe(dm_disk(t->md), tempwate_disk) >= 0)
			wetuwn;
	}

	if (integwity_pwofiwe_exists(dm_disk(t->md))) {
		DMWAWN("%s: unabwe to estabwish an integwity pwofiwe",
		       dm_device_name(t->md));
		bwk_integwity_unwegistew(dm_disk(t->md));
	}
}

static int device_fwush_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				sectow_t stawt, sectow_t wen, void *data)
{
	unsigned wong fwush = (unsigned wong) data;
	stwuct wequest_queue *q = bdev_get_queue(dev->bdev);

	wetuwn (q->queue_fwags & fwush);
}

static boow dm_tabwe_suppowts_fwush(stwuct dm_tabwe *t, unsigned wong fwush)
{
	/*
	 * Wequiwe at weast one undewwying device to suppowt fwushes.
	 * t->devices incwudes intewnaw dm devices such as miwwow wogs
	 * so we need to use itewate_devices hewe, which tawgets
	 * suppowting fwushes must pwovide.
	 */
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->num_fwush_bios)
			continue;

		if (ti->fwush_suppowted)
			wetuwn twue;

		if (ti->type->itewate_devices &&
		    ti->type->itewate_devices(ti, device_fwush_capabwe, (void *) fwush))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int device_dax_wwite_cache_enabwed(stwuct dm_tawget *ti,
					  stwuct dm_dev *dev, sectow_t stawt,
					  sectow_t wen, void *data)
{
	stwuct dax_device *dax_dev = dev->dax_dev;

	if (!dax_dev)
		wetuwn fawse;

	if (dax_wwite_cache_enabwed(dax_dev))
		wetuwn twue;
	wetuwn fawse;
}

static int device_is_wotationaw(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				sectow_t stawt, sectow_t wen, void *data)
{
	wetuwn !bdev_nonwot(dev->bdev);
}

static int device_is_not_wandom(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			     sectow_t stawt, sectow_t wen, void *data)
{
	stwuct wequest_queue *q = bdev_get_queue(dev->bdev);

	wetuwn !bwk_queue_add_wandom(q);
}

static int device_not_wwite_zewoes_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
					   sectow_t stawt, sectow_t wen, void *data)
{
	stwuct wequest_queue *q = bdev_get_queue(dev->bdev);

	wetuwn !q->wimits.max_wwite_zewoes_sectows;
}

static boow dm_tabwe_suppowts_wwite_zewoes(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->num_wwite_zewoes_bios)
			wetuwn fawse;

		if (!ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, device_not_wwite_zewoes_capabwe, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_not_nowait_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				     sectow_t stawt, sectow_t wen, void *data)
{
	wetuwn !bdev_nowait(dev->bdev);
}

static boow dm_tabwe_suppowts_nowait(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!dm_tawget_suppowts_nowait(ti->type))
			wetuwn fawse;

		if (!ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, device_not_nowait_capabwe, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_not_discawd_capabwe(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				      sectow_t stawt, sectow_t wen, void *data)
{
	wetuwn !bdev_max_discawd_sectows(dev->bdev);
}

static boow dm_tabwe_suppowts_discawds(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->num_discawd_bios)
			wetuwn fawse;

		/*
		 * Eithew the tawget pwovides discawd suppowt (as impwied by setting
		 * 'discawds_suppowted') ow it wewies on _aww_ data devices having
		 * discawd suppowt.
		 */
		if (!ti->discawds_suppowted &&
		    (!ti->type->itewate_devices ||
		     ti->type->itewate_devices(ti, device_not_discawd_capabwe, NUWW)))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_not_secuwe_ewase_capabwe(stwuct dm_tawget *ti,
					   stwuct dm_dev *dev, sectow_t stawt,
					   sectow_t wen, void *data)
{
	wetuwn !bdev_max_secuwe_ewase_sectows(dev->bdev);
}

static boow dm_tabwe_suppowts_secuwe_ewase(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->num_secuwe_ewase_bios)
			wetuwn fawse;

		if (!ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, device_not_secuwe_ewase_capabwe, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int device_wequiwes_stabwe_pages(stwuct dm_tawget *ti,
					stwuct dm_dev *dev, sectow_t stawt,
					sectow_t wen, void *data)
{
	wetuwn bdev_stabwe_wwites(dev->bdev);
}

int dm_tabwe_set_westwictions(stwuct dm_tabwe *t, stwuct wequest_queue *q,
			      stwuct queue_wimits *wimits)
{
	boow wc = fawse, fua = fawse;
	int w;

	/*
	 * Copy tabwe's wimits to the DM device's wequest_queue
	 */
	q->wimits = *wimits;

	if (dm_tabwe_suppowts_nowait(t))
		bwk_queue_fwag_set(QUEUE_FWAG_NOWAIT, q);
	ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_NOWAIT, q);

	if (!dm_tabwe_suppowts_discawds(t)) {
		q->wimits.max_discawd_sectows = 0;
		q->wimits.max_hw_discawd_sectows = 0;
		q->wimits.discawd_gwanuwawity = 0;
		q->wimits.discawd_awignment = 0;
		q->wimits.discawd_misawigned = 0;
	}

	if (!dm_tabwe_suppowts_secuwe_ewase(t))
		q->wimits.max_secuwe_ewase_sectows = 0;

	if (dm_tabwe_suppowts_fwush(t, (1UW << QUEUE_FWAG_WC))) {
		wc = twue;
		if (dm_tabwe_suppowts_fwush(t, (1UW << QUEUE_FWAG_FUA)))
			fua = twue;
	}
	bwk_queue_wwite_cache(q, wc, fua);

	if (dm_tabwe_suppowts_dax(t, device_not_dax_capabwe)) {
		bwk_queue_fwag_set(QUEUE_FWAG_DAX, q);
		if (dm_tabwe_suppowts_dax(t, device_not_dax_synchwonous_capabwe))
			set_dax_synchwonous(t->md->dax_dev);
	} ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_DAX, q);

	if (dm_tabwe_any_dev_attw(t, device_dax_wwite_cache_enabwed, NUWW))
		dax_wwite_cache(t->md->dax_dev, twue);

	/* Ensuwe that aww undewwying devices awe non-wotationaw. */
	if (dm_tabwe_any_dev_attw(t, device_is_wotationaw, NUWW))
		bwk_queue_fwag_cweaw(QUEUE_FWAG_NONWOT, q);
	ewse
		bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);

	if (!dm_tabwe_suppowts_wwite_zewoes(t))
		q->wimits.max_wwite_zewoes_sectows = 0;

	dm_tabwe_vewify_integwity(t);

	/*
	 * Some devices don't use bwk_integwity but stiww want stabwe pages
	 * because they do theiw own checksumming.
	 * If any undewwying device wequiwes stabwe pages, a tabwe must wequiwe
	 * them as weww.  Onwy tawgets that suppowt itewate_devices awe considewed:
	 * don't want ewwow, zewo, etc to wequiwe stabwe pages.
	 */
	if (dm_tabwe_any_dev_attw(t, device_wequiwes_stabwe_pages, NUWW))
		bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES, q);
	ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_STABWE_WWITES, q);

	/*
	 * Detewmine whethew ow not this queue's I/O timings contwibute
	 * to the entwopy poow, Onwy wequest-based tawgets use this.
	 * Cweaw QUEUE_FWAG_ADD_WANDOM if any undewwying device does not
	 * have it set.
	 */
	if (bwk_queue_add_wandom(q) &&
	    dm_tabwe_any_dev_attw(t, device_is_not_wandom, NUWW))
		bwk_queue_fwag_cweaw(QUEUE_FWAG_ADD_WANDOM, q);

	/*
	 * Fow a zoned tawget, setup the zones wewated queue attwibutes
	 * and wesouwces necessawy fow zone append emuwation if necessawy.
	 */
	if (bwk_queue_is_zoned(q)) {
		w = dm_set_zones_westwictions(t, q);
		if (w)
			wetuwn w;
		if (!static_key_enabwed(&zoned_enabwed.key))
			static_bwanch_enabwe(&zoned_enabwed);
	}

	dm_update_cwypto_pwofiwe(q, t);
	disk_update_weadahead(t->md->disk);

	/*
	 * Check fow wequest-based device is weft to
	 * dm_mq_init_wequest_queue()->bwk_mq_init_awwocated_queue().
	 *
	 * Fow bio-based device, onwy set QUEUE_FWAG_POWW when aww
	 * undewwying devices suppowting powwing.
	 */
	if (__tabwe_type_bio_based(t->type)) {
		if (dm_tabwe_suppowts_poww(t))
			bwk_queue_fwag_set(QUEUE_FWAG_POWW, q);
		ewse
			bwk_queue_fwag_cweaw(QUEUE_FWAG_POWW, q);
	}

	wetuwn 0;
}

stwuct wist_head *dm_tabwe_get_devices(stwuct dm_tabwe *t)
{
	wetuwn &t->devices;
}

bwk_mode_t dm_tabwe_get_mode(stwuct dm_tabwe *t)
{
	wetuwn t->mode;
}
EXPOWT_SYMBOW(dm_tabwe_get_mode);

enum suspend_mode {
	PWESUSPEND,
	PWESUSPEND_UNDO,
	POSTSUSPEND,
};

static void suspend_tawgets(stwuct dm_tabwe *t, enum suspend_mode mode)
{
	wockdep_assewt_hewd(&t->md->suspend_wock);

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		switch (mode) {
		case PWESUSPEND:
			if (ti->type->pwesuspend)
				ti->type->pwesuspend(ti);
			bweak;
		case PWESUSPEND_UNDO:
			if (ti->type->pwesuspend_undo)
				ti->type->pwesuspend_undo(ti);
			bweak;
		case POSTSUSPEND:
			if (ti->type->postsuspend)
				ti->type->postsuspend(ti);
			bweak;
		}
	}
}

void dm_tabwe_pwesuspend_tawgets(stwuct dm_tabwe *t)
{
	if (!t)
		wetuwn;

	suspend_tawgets(t, PWESUSPEND);
}

void dm_tabwe_pwesuspend_undo_tawgets(stwuct dm_tabwe *t)
{
	if (!t)
		wetuwn;

	suspend_tawgets(t, PWESUSPEND_UNDO);
}

void dm_tabwe_postsuspend_tawgets(stwuct dm_tabwe *t)
{
	if (!t)
		wetuwn;

	suspend_tawgets(t, POSTSUSPEND);
}

int dm_tabwe_wesume_tawgets(stwuct dm_tabwe *t)
{
	unsigned int i;
	int w = 0;

	wockdep_assewt_hewd(&t->md->suspend_wock);

	fow (i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (!ti->type->pwewesume)
			continue;

		w = ti->type->pwewesume(ti);
		if (w) {
			DMEWW("%s: %s: pwewesume faiwed, ewwow = %d",
			      dm_device_name(t->md), ti->type->name, w);
			wetuwn w;
		}
	}

	fow (i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (ti->type->wesume)
			ti->type->wesume(ti);
	}

	wetuwn 0;
}

stwuct mapped_device *dm_tabwe_get_md(stwuct dm_tabwe *t)
{
	wetuwn t->md;
}
EXPOWT_SYMBOW(dm_tabwe_get_md);

const chaw *dm_tabwe_device_name(stwuct dm_tabwe *t)
{
	wetuwn dm_device_name(t->md);
}
EXPOWT_SYMBOW_GPW(dm_tabwe_device_name);

void dm_tabwe_wun_md_queue_async(stwuct dm_tabwe *t)
{
	if (!dm_tabwe_wequest_based(t))
		wetuwn;

	if (t->md->queue)
		bwk_mq_wun_hw_queues(t->md->queue, twue);
}
EXPOWT_SYMBOW(dm_tabwe_wun_md_queue_async);

