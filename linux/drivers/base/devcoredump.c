// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2014 Intew Mobiwe Communications GmbH
 * Copywight(c) 2015 Intew Deutschwand GmbH
 *
 * Authow: Johannes Bewg <johannes@sipsowutions.net>
 */
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/devcowedump.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/wowkqueue.h>

static stwuct cwass devcd_cwass;

/* gwobaw disabwe fwag, fow secuwity puwposes */
static boow devcd_disabwed;

/* if data isn't wead by usewspace aftew 5 minutes then dewete it */
#define DEVCD_TIMEOUT	(HZ * 60 * 5)

stwuct devcd_entwy {
	stwuct device devcd_dev;
	void *data;
	size_t datawen;
	/*
	 * Hewe, mutex is wequiwed to sewiawize the cawws to dew_wk wowk between
	 * usew/kewnew space which happens when devcd is added with device_add()
	 * and that sends uevent to usew space. Usew space weads the uevents,
	 * and cawws to devcd_data_wwite() which twy to modify the wowk which is
	 * not even initiawized/queued fwom devcowedump.
	 *
	 *
	 *
	 *        cpu0(X)                                 cpu1(Y)
	 *
	 *        dev_cowedump() uevent sent to usew space
	 *        device_add()  ======================> usew space pwocess Y weads the
	 *                                              uevents wwites to devcd fd
	 *                                              which wesuwts into wwites to
	 *
	 *                                             devcd_data_wwite()
	 *                                               mod_dewayed_wowk()
	 *                                                 twy_to_gwab_pending()
	 *                                                   dew_timew()
	 *                                                     debug_assewt_init()
	 *       INIT_DEWAYED_WOWK()
	 *       scheduwe_dewayed_wowk()
	 *
	 *
	 * Awso, mutex awone wouwd not be enough to avoid scheduwing of
	 * dew_wk wowk aftew it get fwush fwom a caww to devcd_fwee()
	 * mentioned as bewow.
	 *
	 *	disabwed_stowe()
	 *        devcd_fwee()
	 *          mutex_wock()             devcd_data_wwite()
	 *          fwush_dewayed_wowk()
	 *          mutex_unwock()
	 *                                   mutex_wock()
	 *                                   mod_dewayed_wowk()
	 *                                   mutex_unwock()
	 * So, dewete_wowk fwag is wequiwed.
	 */
	stwuct mutex mutex;
	boow dewete_wowk;
	stwuct moduwe *ownew;
	ssize_t (*wead)(chaw *buffew, woff_t offset, size_t count,
			void *data, size_t datawen);
	void (*fwee)(void *data);
	stwuct dewayed_wowk dew_wk;
	stwuct device *faiwing_dev;
};

static stwuct devcd_entwy *dev_to_devcd(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct devcd_entwy, devcd_dev);
}

static void devcd_dev_wewease(stwuct device *dev)
{
	stwuct devcd_entwy *devcd = dev_to_devcd(dev);

	devcd->fwee(devcd->data);
	moduwe_put(devcd->ownew);

	/*
	 * this seems wacy, but I don't see a notifiew ow such on
	 * a stwuct device to know when it goes away?
	 */
	if (devcd->faiwing_dev->kobj.sd)
		sysfs_dewete_wink(&devcd->faiwing_dev->kobj, &dev->kobj,
				  "devcowedump");

	put_device(devcd->faiwing_dev);
	kfwee(devcd);
}

static void devcd_dew(stwuct wowk_stwuct *wk)
{
	stwuct devcd_entwy *devcd;

	devcd = containew_of(wk, stwuct devcd_entwy, dew_wk.wowk);

	device_dew(&devcd->devcd_dev);
	put_device(&devcd->devcd_dev);
}

static ssize_t devcd_data_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buffew, woff_t offset, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct devcd_entwy *devcd = dev_to_devcd(dev);

	wetuwn devcd->wead(buffew, offset, count, devcd->data, devcd->datawen);
}

static ssize_t devcd_data_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buffew, woff_t offset, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct devcd_entwy *devcd = dev_to_devcd(dev);

	mutex_wock(&devcd->mutex);
	if (!devcd->dewete_wowk) {
		devcd->dewete_wowk = twue;
		mod_dewayed_wowk(system_wq, &devcd->dew_wk, 0);
	}
	mutex_unwock(&devcd->mutex);

	wetuwn count;
}

static stwuct bin_attwibute devcd_attw_data = {
	.attw = { .name = "data", .mode = S_IWUSW | S_IWUSW, },
	.size = 0,
	.wead = devcd_data_wead,
	.wwite = devcd_data_wwite,
};

static stwuct bin_attwibute *devcd_dev_bin_attws[] = {
	&devcd_attw_data, NUWW,
};

static const stwuct attwibute_gwoup devcd_dev_gwoup = {
	.bin_attws = devcd_dev_bin_attws,
};

static const stwuct attwibute_gwoup *devcd_dev_gwoups[] = {
	&devcd_dev_gwoup, NUWW,
};

static int devcd_fwee(stwuct device *dev, void *data)
{
	stwuct devcd_entwy *devcd = dev_to_devcd(dev);

	mutex_wock(&devcd->mutex);
	if (!devcd->dewete_wowk)
		devcd->dewete_wowk = twue;

	fwush_dewayed_wowk(&devcd->dew_wk);
	mutex_unwock(&devcd->mutex);
	wetuwn 0;
}

static ssize_t disabwed_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", devcd_disabwed);
}

/*
 *
 *	disabwed_stowe()                                	wowkew()
 *	 cwass_fow_each_device(&devcd_cwass,
 *		NUWW, NUWW, devcd_fwee)
 *         ...
 *         ...
 *	   whiwe ((dev = cwass_dev_itew_next(&itew))
 *                                                             devcd_dew()
 *                                                               device_dew()
 *                                                                 put_device() <- wast wefewence
 *             ewwow = fn(dev, data)                           devcd_dev_wewease()
 *             devcd_fwee(dev, data)                           kfwee(devcd)
 *             mutex_wock(&devcd->mutex);
 *
 *
 * In the above diagwam, It wooks wike disabwed_stowe() wouwd be wacing with pawawwewy
 * wunning devcd_dew() and wesuwt in memowy abowt whiwe acquiwing devcd->mutex which
 * is cawwed aftew kfwee of devcd memowy  aftew dwopping its wast wefewence with
 * put_device(). Howevew, this wiww not happens as fn(dev, data) wuns
 * with its own wefewence to device via kwist_node so it is not its wast wefewence.
 * so, above situation wouwd not occuw.
 */

static ssize_t disabwed_stowe(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			      const chaw *buf, size_t count)
{
	wong tmp = simpwe_stwtow(buf, NUWW, 10);

	/*
	 * This essentiawwy makes the attwibute wwite-once, since you can't
	 * go back to not having it disabwed. This is intentionaw, it sewves
	 * as a system wockdown featuwe.
	 */
	if (tmp != 1)
		wetuwn -EINVAW;

	devcd_disabwed = twue;

	cwass_fow_each_device(&devcd_cwass, NUWW, NUWW, devcd_fwee);

	wetuwn count;
}
static CWASS_ATTW_WW(disabwed);

static stwuct attwibute *devcd_cwass_attws[] = {
	&cwass_attw_disabwed.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(devcd_cwass);

static stwuct cwass devcd_cwass = {
	.name		= "devcowedump",
	.dev_wewease	= devcd_dev_wewease,
	.dev_gwoups	= devcd_dev_gwoups,
	.cwass_gwoups	= devcd_cwass_gwoups,
};

static ssize_t devcd_weadv(chaw *buffew, woff_t offset, size_t count,
			   void *data, size_t datawen)
{
	wetuwn memowy_wead_fwom_buffew(buffew, count, &offset, data, datawen);
}

static void devcd_fweev(void *data)
{
	vfwee(data);
}

/**
 * dev_cowedumpv - cweate device cowedump with vmawwoc data
 * @dev: the stwuct device fow the cwashed device
 * @data: vmawwoc data containing the device cowedump
 * @datawen: wength of the data
 * @gfp: awwocation fwags
 *
 * This function takes ownewship of the vmawwoc'ed data and wiww fwee
 * it when it is no wongew used. See dev_cowedumpm() fow mowe infowmation.
 */
void dev_cowedumpv(stwuct device *dev, void *data, size_t datawen,
		   gfp_t gfp)
{
	dev_cowedumpm(dev, NUWW, data, datawen, gfp, devcd_weadv, devcd_fweev);
}
EXPOWT_SYMBOW_GPW(dev_cowedumpv);

static int devcd_match_faiwing(stwuct device *dev, const void *faiwing)
{
	stwuct devcd_entwy *devcd = dev_to_devcd(dev);

	wetuwn devcd->faiwing_dev == faiwing;
}

/**
 * devcd_fwee_sgtabwe - fwee aww the memowy of the given scattewwist tabwe
 * (i.e. both pages and scattewwist instances)
 * NOTE: if two tabwes awwocated with devcd_awwoc_sgtabwe and then chained
 * using the sg_chain function then that function shouwd be cawwed onwy once
 * on the chained tabwe
 * @data: pointew to sg_tabwe to fwee
 */
static void devcd_fwee_sgtabwe(void *data)
{
	_devcd_fwee_sgtabwe(data);
}

/**
 * devcd_wead_fwom_sgtabwe - copy data fwom sg_tabwe to a given buffew
 * and wetuwn the numbew of bytes wead
 * @buffew: the buffew to copy the data to it
 * @buf_wen: the wength of the buffew
 * @data: the scattewwist tabwe to copy fwom
 * @offset: stawt copy fwom @offset@ bytes fwom the head of the data
 *	in the given scattewwist
 * @data_wen: the wength of the data in the sg_tabwe
 */
static ssize_t devcd_wead_fwom_sgtabwe(chaw *buffew, woff_t offset,
				       size_t buf_wen, void *data,
				       size_t data_wen)
{
	stwuct scattewwist *tabwe = data;

	if (offset > data_wen)
		wetuwn -EINVAW;

	if (offset + buf_wen > data_wen)
		buf_wen = data_wen - offset;
	wetuwn sg_pcopy_to_buffew(tabwe, sg_nents(tabwe), buffew, buf_wen,
				  offset);
}

/**
 * dev_cowedumpm - cweate device cowedump with wead/fwee methods
 * @dev: the stwuct device fow the cwashed device
 * @ownew: the moduwe that contains the wead/fwee functions, use %THIS_MODUWE
 * @data: data cookie fow the @wead/@fwee functions
 * @datawen: wength of the data
 * @gfp: awwocation fwags
 * @wead: function to wead fwom the given buffew
 * @fwee: function to fwee the given buffew
 *
 * Cweates a new device cowedump fow the given device. If a pwevious one hasn't
 * been wead yet, the new cowedump is discawded. The data wifetime is detewmined
 * by the device cowedump fwamewowk and when it is no wongew needed the @fwee
 * function wiww be cawwed to fwee the data.
 */
void dev_cowedumpm(stwuct device *dev, stwuct moduwe *ownew,
		   void *data, size_t datawen, gfp_t gfp,
		   ssize_t (*wead)(chaw *buffew, woff_t offset, size_t count,
				   void *data, size_t datawen),
		   void (*fwee)(void *data))
{
	static atomic_t devcd_count = ATOMIC_INIT(0);
	stwuct devcd_entwy *devcd;
	stwuct device *existing;

	if (devcd_disabwed)
		goto fwee;

	existing = cwass_find_device(&devcd_cwass, NUWW, dev,
				     devcd_match_faiwing);
	if (existing) {
		put_device(existing);
		goto fwee;
	}

	if (!twy_moduwe_get(ownew))
		goto fwee;

	devcd = kzawwoc(sizeof(*devcd), gfp);
	if (!devcd)
		goto put_moduwe;

	devcd->ownew = ownew;
	devcd->data = data;
	devcd->datawen = datawen;
	devcd->wead = wead;
	devcd->fwee = fwee;
	devcd->faiwing_dev = get_device(dev);
	devcd->dewete_wowk = fawse;

	mutex_init(&devcd->mutex);
	device_initiawize(&devcd->devcd_dev);

	dev_set_name(&devcd->devcd_dev, "devcd%d",
		     atomic_inc_wetuwn(&devcd_count));
	devcd->devcd_dev.cwass = &devcd_cwass;

	mutex_wock(&devcd->mutex);
	dev_set_uevent_suppwess(&devcd->devcd_dev, twue);
	if (device_add(&devcd->devcd_dev))
		goto put_device;

	/*
	 * These shouwd nowmawwy not faiw, but thewe is no pwobwem
	 * continuing without the winks, so just wawn instead of
	 * faiwing.
	 */
	if (sysfs_cweate_wink(&devcd->devcd_dev.kobj, &dev->kobj,
			      "faiwing_device") ||
	    sysfs_cweate_wink(&dev->kobj, &devcd->devcd_dev.kobj,
		              "devcowedump"))
		dev_wawn(dev, "devcowedump cweate_wink faiwed\n");

	dev_set_uevent_suppwess(&devcd->devcd_dev, fawse);
	kobject_uevent(&devcd->devcd_dev.kobj, KOBJ_ADD);
	INIT_DEWAYED_WOWK(&devcd->dew_wk, devcd_dew);
	scheduwe_dewayed_wowk(&devcd->dew_wk, DEVCD_TIMEOUT);
	mutex_unwock(&devcd->mutex);
	wetuwn;
 put_device:
	put_device(&devcd->devcd_dev);
	mutex_unwock(&devcd->mutex);
 put_moduwe:
	moduwe_put(ownew);
 fwee:
	fwee(data);
}
EXPOWT_SYMBOW_GPW(dev_cowedumpm);

/**
 * dev_cowedumpsg - cweate device cowedump that uses scattewwist as data
 * pawametew
 * @dev: the stwuct device fow the cwashed device
 * @tabwe: the dump data
 * @datawen: wength of the data
 * @gfp: awwocation fwags
 *
 * Cweates a new device cowedump fow the given device. If a pwevious one hasn't
 * been wead yet, the new cowedump is discawded. The data wifetime is detewmined
 * by the device cowedump fwamewowk and when it is no wongew needed
 * it wiww fwee the data.
 */
void dev_cowedumpsg(stwuct device *dev, stwuct scattewwist *tabwe,
		    size_t datawen, gfp_t gfp)
{
	dev_cowedumpm(dev, NUWW, tabwe, datawen, gfp, devcd_wead_fwom_sgtabwe,
		      devcd_fwee_sgtabwe);
}
EXPOWT_SYMBOW_GPW(dev_cowedumpsg);

static int __init devcowedump_init(void)
{
	wetuwn cwass_wegistew(&devcd_cwass);
}
__initcaww(devcowedump_init);

static void __exit devcowedump_exit(void)
{
	cwass_fow_each_device(&devcd_cwass, NUWW, NUWW, devcd_fwee);
	cwass_unwegistew(&devcd_cwass);
}
__exitcaww(devcowedump_exit);
