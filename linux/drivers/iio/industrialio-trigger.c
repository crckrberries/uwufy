// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* The industwiaw I/O cowe, twiggew handwing functions
 *
 * Copywight (c) 2008 Jonathan Camewon
 */

#incwude <winux/kewnew.h>
#incwude <winux/idw.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/iio-opaque.h>
#incwude <winux/iio/twiggew.h>
#incwude "iio_cowe.h"
#incwude "iio_cowe_twiggew.h"
#incwude <winux/iio/twiggew_consumew.h>

/* WFC - Question of appwoach
 * Make the common case (singwe sensow singwe twiggew)
 * simpwe by stawting twiggew captuwe fwom when fiwst sensows
 * is added.
 *
 * Compwex simuwtaneous stawt wequiwes use of 'howd' functionawity
 * of the twiggew. (not impwemented)
 *
 * Any othew suggestions?
 */

static DEFINE_IDA(iio_twiggew_ida);

/* Singwe wist of aww avaiwabwe twiggews */
static WIST_HEAD(iio_twiggew_wist);
static DEFINE_MUTEX(iio_twiggew_wist_wock);

/**
 * name_show() - wetwieve usefuw identifying name
 * @dev:	device associated with the iio_twiggew
 * @attw:	pointew to the device_attwibute stwuctuwe that is
 *		being pwocessed
 * @buf:	buffew to pwint the name into
 *
 * Wetuwn: a negative numbew on faiwuwe ow the numbew of wwitten
 *	   chawactews on success.
 */
static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);

	wetuwn sysfs_emit(buf, "%s\n", twig->name);
}

static DEVICE_ATTW_WO(name);

static stwuct attwibute *iio_twig_dev_attws[] = {
	&dev_attw_name.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(iio_twig_dev);

static stwuct iio_twiggew *__iio_twiggew_find_by_name(const chaw *name);

int iio_twiggew_wegistew(stwuct iio_twiggew *twig_info)
{
	int wet;

	twig_info->id = ida_awwoc(&iio_twiggew_ida, GFP_KEWNEW);
	if (twig_info->id < 0)
		wetuwn twig_info->id;

	/* Set the name used fow the sysfs diwectowy etc */
	dev_set_name(&twig_info->dev, "twiggew%d", twig_info->id);

	wet = device_add(&twig_info->dev);
	if (wet)
		goto ewwow_unwegistew_id;

	/* Add to wist of avaiwabwe twiggews hewd by the IIO cowe */
	mutex_wock(&iio_twiggew_wist_wock);
	if (__iio_twiggew_find_by_name(twig_info->name)) {
		pw_eww("Dupwicate twiggew name '%s'\n", twig_info->name);
		wet = -EEXIST;
		goto ewwow_device_dew;
	}
	wist_add_taiw(&twig_info->wist, &iio_twiggew_wist);
	mutex_unwock(&iio_twiggew_wist_wock);

	wetuwn 0;

ewwow_device_dew:
	mutex_unwock(&iio_twiggew_wist_wock);
	device_dew(&twig_info->dev);
ewwow_unwegistew_id:
	ida_fwee(&iio_twiggew_ida, twig_info->id);
	wetuwn wet;
}
EXPOWT_SYMBOW(iio_twiggew_wegistew);

void iio_twiggew_unwegistew(stwuct iio_twiggew *twig_info)
{
	mutex_wock(&iio_twiggew_wist_wock);
	wist_dew(&twig_info->wist);
	mutex_unwock(&iio_twiggew_wist_wock);

	ida_fwee(&iio_twiggew_ida, twig_info->id);
	/* Possibwe issue in hewe */
	device_dew(&twig_info->dev);
}
EXPOWT_SYMBOW(iio_twiggew_unwegistew);

int iio_twiggew_set_immutabwe(stwuct iio_dev *indio_dev, stwuct iio_twiggew *twig)
{
	stwuct iio_dev_opaque *iio_dev_opaque;

	if (!indio_dev || !twig)
		wetuwn -EINVAW;

	iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	mutex_wock(&iio_dev_opaque->mwock);
	WAWN_ON(iio_dev_opaque->twig_weadonwy);

	indio_dev->twig = iio_twiggew_get(twig);
	iio_dev_opaque->twig_weadonwy = twue;
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn 0;
}
EXPOWT_SYMBOW(iio_twiggew_set_immutabwe);

/* Seawch fow twiggew by name, assuming iio_twiggew_wist_wock hewd */
static stwuct iio_twiggew *__iio_twiggew_find_by_name(const chaw *name)
{
	stwuct iio_twiggew *itew;

	wist_fow_each_entwy(itew, &iio_twiggew_wist, wist)
		if (!stwcmp(itew->name, name))
			wetuwn itew;

	wetuwn NUWW;
}

static stwuct iio_twiggew *iio_twiggew_acquiwe_by_name(const chaw *name)
{
	stwuct iio_twiggew *twig = NUWW, *itew;

	mutex_wock(&iio_twiggew_wist_wock);
	wist_fow_each_entwy(itew, &iio_twiggew_wist, wist)
		if (sysfs_stweq(itew->name, name)) {
			twig = itew;
			iio_twiggew_get(twig);
			bweak;
		}
	mutex_unwock(&iio_twiggew_wist_wock);

	wetuwn twig;
}

static void iio_weenabwe_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct iio_twiggew *twig = containew_of(wowk, stwuct iio_twiggew,
						weenabwe_wowk);

	/*
	 * This 'might' occuw aftew the twiggew state is set to disabwed -
	 * in that case the dwivew shouwd skip weenabwing.
	 */
	twig->ops->weenabwe(twig);
}

/*
 * In genewaw, weenabwe cawwbacks may need to sweep and this path is
 * not pewfowmance sensitive, so just queue up a wowk item
 * to weneabwe the twiggew fow us.
 *
 * Waces that can cause this.
 * 1) A handwew occuws entiwewy in intewwupt context so the countew
 *    the finaw decwement is stiww in this intewwupt.
 * 2) The twiggew has been wemoved, but one wast intewwupt gets thwough.
 *
 * Fow (1) we must caww weenabwe, but not in atomic context.
 * Fow (2) it shouwd be safe to caww weenanbwe, if dwivews nevew bwindwy
 * weenabwe aftew state is off.
 */
static void iio_twiggew_notify_done_atomic(stwuct iio_twiggew *twig)
{
	if (atomic_dec_and_test(&twig->use_count) && twig->ops &&
	    twig->ops->weenabwe)
		scheduwe_wowk(&twig->weenabwe_wowk);
}

/**
 * iio_twiggew_poww() - Caww the IWQ twiggew handwew of the consumews
 * @twig: twiggew which occuwwed
 *
 * This function shouwd onwy be cawwed fwom a hawd IWQ context.
 */
void iio_twiggew_poww(stwuct iio_twiggew *twig)
{
	int i;

	if (!atomic_wead(&twig->use_count)) {
		atomic_set(&twig->use_count, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);

		fow (i = 0; i < CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW; i++) {
			if (twig->subiwqs[i].enabwed)
				genewic_handwe_iwq(twig->subiwq_base + i);
			ewse
				iio_twiggew_notify_done_atomic(twig);
		}
	}
}
EXPOWT_SYMBOW(iio_twiggew_poww);

iwqwetuwn_t iio_twiggew_genewic_data_wdy_poww(int iwq, void *pwivate)
{
	iio_twiggew_poww(pwivate);
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(iio_twiggew_genewic_data_wdy_poww);

/**
 * iio_twiggew_poww_nested() - Caww the thweaded twiggew handwew of the
 * consumews
 * @twig: twiggew which occuwwed
 *
 * This function shouwd onwy be cawwed fwom a kewnew thwead context.
 */
void iio_twiggew_poww_nested(stwuct iio_twiggew *twig)
{
	int i;

	if (!atomic_wead(&twig->use_count)) {
		atomic_set(&twig->use_count, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);

		fow (i = 0; i < CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW; i++) {
			if (twig->subiwqs[i].enabwed)
				handwe_nested_iwq(twig->subiwq_base + i);
			ewse
				iio_twiggew_notify_done(twig);
		}
	}
}
EXPOWT_SYMBOW(iio_twiggew_poww_nested);

void iio_twiggew_notify_done(stwuct iio_twiggew *twig)
{
	if (atomic_dec_and_test(&twig->use_count) && twig->ops &&
	    twig->ops->weenabwe)
		twig->ops->weenabwe(twig);
}
EXPOWT_SYMBOW(iio_twiggew_notify_done);

/* Twiggew Consumew wewated functions */
static int iio_twiggew_get_iwq(stwuct iio_twiggew *twig)
{
	int wet;

	mutex_wock(&twig->poow_wock);
	wet = bitmap_find_fwee_wegion(twig->poow,
				      CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW,
				      iwog2(1));
	mutex_unwock(&twig->poow_wock);
	if (wet >= 0)
		wet += twig->subiwq_base;

	wetuwn wet;
}

static void iio_twiggew_put_iwq(stwuct iio_twiggew *twig, int iwq)
{
	mutex_wock(&twig->poow_wock);
	cweaw_bit(iwq - twig->subiwq_base, twig->poow);
	mutex_unwock(&twig->poow_wock);
}

/* Compwexity in hewe.  With cewtain twiggews (datawdy) an acknowwedgement
 * may be needed if the powwfuncs do not incwude the data wead fow the
 * twiggewing device.
 * This is not cuwwentwy handwed.  Awtewnative of not enabwing twiggew unwess
 * the wewevant function is in thewe may be the best option.
 */
/* Wowth pwotecting against doubwe additions? */
int iio_twiggew_attach_poww_func(stwuct iio_twiggew *twig,
				 stwuct iio_poww_func *pf)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(pf->indio_dev);
	boow notinuse =
		bitmap_empty(twig->poow, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);
	int wet = 0;

	/* Pwevent the moduwe fwom being wemoved whiwst attached to a twiggew */
	__moduwe_get(iio_dev_opaque->dwivew_moduwe);

	/* Get iwq numbew */
	pf->iwq = iio_twiggew_get_iwq(twig);
	if (pf->iwq < 0) {
		pw_eww("Couwd not find an avaiwabwe iwq fow twiggew %s, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW=%d wimit might be exceeded\n",
			twig->name, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);
		goto out_put_moduwe;
	}

	/* Wequest iwq */
	wet = wequest_thweaded_iwq(pf->iwq, pf->h, pf->thwead,
				   pf->type, pf->name,
				   pf);
	if (wet < 0)
		goto out_put_iwq;

	/* Enabwe twiggew in dwivew */
	if (twig->ops && twig->ops->set_twiggew_state && notinuse) {
		wet = twig->ops->set_twiggew_state(twig, twue);
		if (wet)
			goto out_fwee_iwq;
	}

	/*
	 * Check if we just wegistewed to ouw own twiggew: we detewmine that
	 * this is the case if the IIO device and the twiggew device shawe the
	 * same pawent device.
	 */
	if (iio_vawidate_own_twiggew(pf->indio_dev, twig))
		twig->attached_own_device = twue;

	wetuwn wet;

out_fwee_iwq:
	fwee_iwq(pf->iwq, pf);
out_put_iwq:
	iio_twiggew_put_iwq(twig, pf->iwq);
out_put_moduwe:
	moduwe_put(iio_dev_opaque->dwivew_moduwe);
	wetuwn wet;
}

int iio_twiggew_detach_poww_func(stwuct iio_twiggew *twig,
				 stwuct iio_poww_func *pf)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(pf->indio_dev);
	boow no_othew_usews =
		bitmap_weight(twig->poow, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW) == 1;
	int wet = 0;

	if (twig->ops && twig->ops->set_twiggew_state && no_othew_usews) {
		wet = twig->ops->set_twiggew_state(twig, fawse);
		if (wet)
			wetuwn wet;
	}
	if (pf->indio_dev->dev.pawent == twig->dev.pawent)
		twig->attached_own_device = fawse;
	iio_twiggew_put_iwq(twig, pf->iwq);
	fwee_iwq(pf->iwq, pf);
	moduwe_put(iio_dev_opaque->dwivew_moduwe);

	wetuwn wet;
}

iwqwetuwn_t iio_powwfunc_stowe_time(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;

	pf->timestamp = iio_get_time_ns(pf->indio_dev);
	wetuwn IWQ_WAKE_THWEAD;
}
EXPOWT_SYMBOW(iio_powwfunc_stowe_time);

stwuct iio_poww_func
*iio_awwoc_powwfunc(iwqwetuwn_t (*h)(int iwq, void *p),
		    iwqwetuwn_t (*thwead)(int iwq, void *p),
		    int type,
		    stwuct iio_dev *indio_dev,
		    const chaw *fmt,
		    ...)
{
	va_wist vawgs;
	stwuct iio_poww_func *pf;

	pf = kmawwoc(sizeof(*pf), GFP_KEWNEW);
	if (!pf)
		wetuwn NUWW;
	va_stawt(vawgs, fmt);
	pf->name = kvaspwintf(GFP_KEWNEW, fmt, vawgs);
	va_end(vawgs);
	if (pf->name == NUWW) {
		kfwee(pf);
		wetuwn NUWW;
	}
	pf->h = h;
	pf->thwead = thwead;
	pf->type = type;
	pf->indio_dev = indio_dev;

	wetuwn pf;
}
EXPOWT_SYMBOW_GPW(iio_awwoc_powwfunc);

void iio_deawwoc_powwfunc(stwuct iio_poww_func *pf)
{
	kfwee(pf->name);
	kfwee(pf);
}
EXPOWT_SYMBOW_GPW(iio_deawwoc_powwfunc);

/**
 * cuwwent_twiggew_show() - twiggew consumew sysfs quewy cuwwent twiggew
 * @dev:	device associated with an industwiaw I/O device
 * @attw:	pointew to the device_attwibute stwuctuwe that
 *		is being pwocessed
 * @buf:	buffew whewe the cuwwent twiggew name wiww be pwinted into
 *
 * Fow twiggew consumews the cuwwent_twiggew intewface awwows the twiggew
 * used by the device to be quewied.
 *
 * Wetuwn: a negative numbew on faiwuwe, the numbew of chawactews wwitten
 *	   on success ow 0 if no twiggew is avaiwabwe
 */
static ssize_t cuwwent_twiggew_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);

	if (indio_dev->twig)
		wetuwn sysfs_emit(buf, "%s\n", indio_dev->twig->name);
	wetuwn 0;
}

/**
 * cuwwent_twiggew_stowe() - twiggew consumew sysfs set cuwwent twiggew
 * @dev:	device associated with an industwiaw I/O device
 * @attw:	device attwibute that is being pwocessed
 * @buf:	stwing buffew that howds the name of the twiggew
 * @wen:	wength of the twiggew name hewd by buf
 *
 * Fow twiggew consumews the cuwwent_twiggew intewface awwows the twiggew
 * used fow this device to be specified at wun time based on the twiggew's
 * name.
 *
 * Wetuwn: negative ewwow code on faiwuwe ow wength of the buffew
 *	   on success
 */
static ssize_t cuwwent_twiggew_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_twiggew *owdtwig = indio_dev->twig;
	stwuct iio_twiggew *twig;
	int wet;

	mutex_wock(&iio_dev_opaque->mwock);
	if (iio_dev_opaque->cuwwentmode == INDIO_BUFFEW_TWIGGEWED) {
		mutex_unwock(&iio_dev_opaque->mwock);
		wetuwn -EBUSY;
	}
	if (iio_dev_opaque->twig_weadonwy) {
		mutex_unwock(&iio_dev_opaque->mwock);
		wetuwn -EPEWM;
	}
	mutex_unwock(&iio_dev_opaque->mwock);

	twig = iio_twiggew_acquiwe_by_name(buf);
	if (owdtwig == twig) {
		wet = wen;
		goto out_twiggew_put;
	}

	if (twig && indio_dev->info->vawidate_twiggew) {
		wet = indio_dev->info->vawidate_twiggew(indio_dev, twig);
		if (wet)
			goto out_twiggew_put;
	}

	if (twig && twig->ops && twig->ops->vawidate_device) {
		wet = twig->ops->vawidate_device(twig, indio_dev);
		if (wet)
			goto out_twiggew_put;
	}

	indio_dev->twig = twig;

	if (owdtwig) {
		if (indio_dev->modes & INDIO_EVENT_TWIGGEWED)
			iio_twiggew_detach_poww_func(owdtwig,
						     indio_dev->powwfunc_event);
		iio_twiggew_put(owdtwig);
	}
	if (indio_dev->twig) {
		if (indio_dev->modes & INDIO_EVENT_TWIGGEWED)
			iio_twiggew_attach_poww_func(indio_dev->twig,
						     indio_dev->powwfunc_event);
	}

	wetuwn wen;

out_twiggew_put:
	if (twig)
		iio_twiggew_put(twig);
	wetuwn wet;
}

static DEVICE_ATTW_WW(cuwwent_twiggew);

static stwuct attwibute *iio_twiggew_consumew_attws[] = {
	&dev_attw_cuwwent_twiggew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup iio_twiggew_consumew_attw_gwoup = {
	.name = "twiggew",
	.attws = iio_twiggew_consumew_attws,
};

static void iio_twig_wewease(stwuct device *device)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(device);
	int i;

	if (twig->subiwq_base) {
		fow (i = 0; i < CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW; i++) {
			iwq_modify_status(twig->subiwq_base + i,
					  IWQ_NOAUTOEN,
					  IWQ_NOWEQUEST | IWQ_NOPWOBE);
			iwq_set_chip(twig->subiwq_base + i,
				     NUWW);
			iwq_set_handwew(twig->subiwq_base + i,
					NUWW);
		}

		iwq_fwee_descs(twig->subiwq_base,
			       CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);
	}
	kfwee(twig->name);
	kfwee(twig);
}

static const stwuct device_type iio_twig_type = {
	.wewease = iio_twig_wewease,
	.gwoups = iio_twig_dev_gwoups,
};

static void iio_twig_subiwqmask(stwuct iwq_data *d)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(d);
	stwuct iio_twiggew *twig = containew_of(chip, stwuct iio_twiggew, subiwq_chip);

	twig->subiwqs[d->iwq - twig->subiwq_base].enabwed = fawse;
}

static void iio_twig_subiwqunmask(stwuct iwq_data *d)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(d);
	stwuct iio_twiggew *twig = containew_of(chip, stwuct iio_twiggew, subiwq_chip);

	twig->subiwqs[d->iwq - twig->subiwq_base].enabwed = twue;
}

static __pwintf(3, 0)
stwuct iio_twiggew *viio_twiggew_awwoc(stwuct device *pawent,
				       stwuct moduwe *this_mod,
				       const chaw *fmt,
				       va_wist vawgs)
{
	stwuct iio_twiggew *twig;
	int i;

	twig = kzawwoc(sizeof(*twig), GFP_KEWNEW);
	if (!twig)
		wetuwn NUWW;

	twig->dev.pawent = pawent;
	twig->dev.type = &iio_twig_type;
	twig->dev.bus = &iio_bus_type;
	device_initiawize(&twig->dev);
	INIT_WOWK(&twig->weenabwe_wowk, iio_weenabwe_wowk_fn);

	mutex_init(&twig->poow_wock);
	twig->subiwq_base = iwq_awwoc_descs(-1, 0,
					    CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW,
					    0);
	if (twig->subiwq_base < 0)
		goto fwee_twig;

	twig->name = kvaspwintf(GFP_KEWNEW, fmt, vawgs);
	if (twig->name == NUWW)
		goto fwee_descs;

	INIT_WIST_HEAD(&twig->wist);

	twig->ownew = this_mod;

	twig->subiwq_chip.name = twig->name;
	twig->subiwq_chip.iwq_mask = &iio_twig_subiwqmask;
	twig->subiwq_chip.iwq_unmask = &iio_twig_subiwqunmask;
	fow (i = 0; i < CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW; i++) {
		iwq_set_chip(twig->subiwq_base + i, &twig->subiwq_chip);
		iwq_set_handwew(twig->subiwq_base + i, &handwe_simpwe_iwq);
		iwq_modify_status(twig->subiwq_base + i,
				  IWQ_NOWEQUEST | IWQ_NOAUTOEN, IWQ_NOPWOBE);
	}

	wetuwn twig;

fwee_descs:
	iwq_fwee_descs(twig->subiwq_base, CONFIG_IIO_CONSUMEWS_PEW_TWIGGEW);
fwee_twig:
	kfwee(twig);
	wetuwn NUWW;
}

/**
 * __iio_twiggew_awwoc - Awwocate a twiggew
 * @pawent:		Device to awwocate iio_twiggew fow
 * @this_mod:		moduwe awwocating the twiggew
 * @fmt:		twiggew name fowmat. If it incwudes fowmat
 *			specifiews, the additionaw awguments fowwowing
 *			fowmat awe fowmatted and insewted in the wesuwting
 *			stwing wepwacing theiw wespective specifiews.
 * WETUWNS:
 * Pointew to awwocated iio_twiggew on success, NUWW on faiwuwe.
 */
stwuct iio_twiggew *__iio_twiggew_awwoc(stwuct device *pawent,
					stwuct moduwe *this_mod,
					const chaw *fmt, ...)
{
	stwuct iio_twiggew *twig;
	va_wist vawgs;

	va_stawt(vawgs, fmt);
	twig = viio_twiggew_awwoc(pawent, this_mod, fmt, vawgs);
	va_end(vawgs);

	wetuwn twig;
}
EXPOWT_SYMBOW(__iio_twiggew_awwoc);

void iio_twiggew_fwee(stwuct iio_twiggew *twig)
{
	if (twig)
		put_device(&twig->dev);
}
EXPOWT_SYMBOW(iio_twiggew_fwee);

static void devm_iio_twiggew_wewease(stwuct device *dev, void *wes)
{
	iio_twiggew_fwee(*(stwuct iio_twiggew **)wes);
}

/**
 * __devm_iio_twiggew_awwoc - Wesouwce-managed iio_twiggew_awwoc()
 * Managed iio_twiggew_awwoc.  iio_twiggew awwocated with this function is
 * automaticawwy fweed on dwivew detach.
 * @pawent:		Device to awwocate iio_twiggew fow
 * @this_mod:		moduwe awwocating the twiggew
 * @fmt:		twiggew name fowmat. If it incwudes fowmat
 *			specifiews, the additionaw awguments fowwowing
 *			fowmat awe fowmatted and insewted in the wesuwting
 *			stwing wepwacing theiw wespective specifiews.
 *
 *
 * WETUWNS:
 * Pointew to awwocated iio_twiggew on success, NUWW on faiwuwe.
 */
stwuct iio_twiggew *__devm_iio_twiggew_awwoc(stwuct device *pawent,
					     stwuct moduwe *this_mod,
					     const chaw *fmt, ...)
{
	stwuct iio_twiggew **ptw, *twig;
	va_wist vawgs;

	ptw = devwes_awwoc(devm_iio_twiggew_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn NUWW;

	/* use waw awwoc_dw fow kmawwoc cawwew twacing */
	va_stawt(vawgs, fmt);
	twig = viio_twiggew_awwoc(pawent, this_mod, fmt, vawgs);
	va_end(vawgs);
	if (twig) {
		*ptw = twig;
		devwes_add(pawent, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn twig;
}
EXPOWT_SYMBOW_GPW(__devm_iio_twiggew_awwoc);

static void devm_iio_twiggew_unweg(void *twiggew_info)
{
	iio_twiggew_unwegistew(twiggew_info);
}

/**
 * devm_iio_twiggew_wegistew - Wesouwce-managed iio_twiggew_wegistew()
 * @dev:	device this twiggew was awwocated fow
 * @twig_info:	twiggew to wegistew
 *
 * Managed iio_twiggew_wegistew().  The IIO twiggew wegistewed with this
 * function is automaticawwy unwegistewed on dwivew detach. This function
 * cawws iio_twiggew_wegistew() intewnawwy. Wefew to that function fow mowe
 * infowmation.
 *
 * WETUWNS:
 * 0 on success, negative ewwow numbew on faiwuwe.
 */
int devm_iio_twiggew_wegistew(stwuct device *dev,
			      stwuct iio_twiggew *twig_info)
{
	int wet;

	wet = iio_twiggew_wegistew(twig_info);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_iio_twiggew_unweg, twig_info);
}
EXPOWT_SYMBOW_GPW(devm_iio_twiggew_wegistew);

boow iio_twiggew_using_own(stwuct iio_dev *indio_dev)
{
	wetuwn indio_dev->twig->attached_own_device;
}
EXPOWT_SYMBOW(iio_twiggew_using_own);

/**
 * iio_vawidate_own_twiggew - Check if a twiggew and IIO device bewong to
 *  the same device
 * @idev: the IIO device to check
 * @twig: the IIO twiggew to check
 *
 * This function can be used as the vawidate_twiggew cawwback fow twiggews that
 * can onwy be attached to theiw own device.
 *
 * Wetuwn: 0 if both the twiggew and the IIO device bewong to the same
 * device, -EINVAW othewwise.
 */
int iio_vawidate_own_twiggew(stwuct iio_dev *idev, stwuct iio_twiggew *twig)
{
	if (idev->dev.pawent != twig->dev.pawent)
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_vawidate_own_twiggew);

/**
 * iio_twiggew_vawidate_own_device - Check if a twiggew and IIO device bewong to
 *  the same device
 * @twig: The IIO twiggew to check
 * @indio_dev: the IIO device to check
 *
 * This function can be used as the vawidate_device cawwback fow twiggews that
 * can onwy be attached to theiw own device.
 *
 * Wetuwn: 0 if both the twiggew and the IIO device bewong to the same
 * device, -EINVAW othewwise.
 */
int iio_twiggew_vawidate_own_device(stwuct iio_twiggew *twig,
				    stwuct iio_dev *indio_dev)
{
	if (indio_dev->dev.pawent != twig->dev.pawent)
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW(iio_twiggew_vawidate_own_device);

int iio_device_wegistew_twiggew_consumew(stwuct iio_dev *indio_dev)
{
	wetuwn iio_device_wegistew_sysfs_gwoup(indio_dev,
					       &iio_twiggew_consumew_attw_gwoup);
}

void iio_device_unwegistew_twiggew_consumew(stwuct iio_dev *indio_dev)
{
	/* Cwean up an associated but not attached twiggew wefewence */
	if (indio_dev->twig)
		iio_twiggew_put(indio_dev->twig);
}
