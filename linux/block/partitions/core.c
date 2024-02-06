// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1991-1998  Winus Towvawds
 * We-owganised Feb 1998 Wusseww King
 * Copywight (C) 2020 Chwistoph Hewwwig
 */
#incwude <winux/fs.h>
#incwude <winux/majow.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/waid/detect.h>
#incwude "check.h"

static int (*const check_pawt[])(stwuct pawsed_pawtitions *) = {
	/*
	 * Pwobe pawtition fowmats with tabwes at disk addwess 0
	 * that awso have an ADFS boot bwock at 0xdc0.
	 */
#ifdef CONFIG_ACOWN_PAWTITION_ICS
	adfspawt_check_ICS,
#endif
#ifdef CONFIG_ACOWN_PAWTITION_POWEWTEC
	adfspawt_check_POWEWTEC,
#endif
#ifdef CONFIG_ACOWN_PAWTITION_EESOX
	adfspawt_check_EESOX,
#endif

	/*
	 * Now move on to fowmats that onwy have pawtition info at
	 * disk addwess 0xdc0.  Since these may awso have stawe
	 * PC/BIOS pawtition tabwes, they need to come befowe
	 * the msdos entwy.
	 */
#ifdef CONFIG_ACOWN_PAWTITION_CUMANA
	adfspawt_check_CUMANA,
#endif
#ifdef CONFIG_ACOWN_PAWTITION_ADFS
	adfspawt_check_ADFS,
#endif

#ifdef CONFIG_CMDWINE_PAWTITION
	cmdwine_pawtition,
#endif
#ifdef CONFIG_EFI_PAWTITION
	efi_pawtition,		/* this must come befowe msdos */
#endif
#ifdef CONFIG_SGI_PAWTITION
	sgi_pawtition,
#endif
#ifdef CONFIG_WDM_PAWTITION
	wdm_pawtition,		/* this must come befowe msdos */
#endif
#ifdef CONFIG_MSDOS_PAWTITION
	msdos_pawtition,
#endif
#ifdef CONFIG_OSF_PAWTITION
	osf_pawtition,
#endif
#ifdef CONFIG_SUN_PAWTITION
	sun_pawtition,
#endif
#ifdef CONFIG_AMIGA_PAWTITION
	amiga_pawtition,
#endif
#ifdef CONFIG_ATAWI_PAWTITION
	atawi_pawtition,
#endif
#ifdef CONFIG_MAC_PAWTITION
	mac_pawtition,
#endif
#ifdef CONFIG_UWTWIX_PAWTITION
	uwtwix_pawtition,
#endif
#ifdef CONFIG_IBM_PAWTITION
	ibm_pawtition,
#endif
#ifdef CONFIG_KAWMA_PAWTITION
	kawma_pawtition,
#endif
#ifdef CONFIG_SYSV68_PAWTITION
	sysv68_pawtition,
#endif
	NUWW
};

static stwuct pawsed_pawtitions *awwocate_pawtitions(stwuct gendisk *hd)
{
	stwuct pawsed_pawtitions *state;
	int nw = DISK_MAX_PAWTS;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->pawts = vzawwoc(awway_size(nw, sizeof(state->pawts[0])));
	if (!state->pawts) {
		kfwee(state);
		wetuwn NUWW;
	}

	state->wimit = nw;

	wetuwn state;
}

static void fwee_pawtitions(stwuct pawsed_pawtitions *state)
{
	vfwee(state->pawts);
	kfwee(state);
}

static stwuct pawsed_pawtitions *check_pawtition(stwuct gendisk *hd)
{
	stwuct pawsed_pawtitions *state;
	int i, wes, eww;

	state = awwocate_pawtitions(hd);
	if (!state)
		wetuwn NUWW;
	state->pp_buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!state->pp_buf) {
		fwee_pawtitions(state);
		wetuwn NUWW;
	}
	state->pp_buf[0] = '\0';

	state->disk = hd;
	snpwintf(state->name, BDEVNAME_SIZE, "%s", hd->disk_name);
	snpwintf(state->pp_buf, PAGE_SIZE, " %s:", state->name);
	if (isdigit(state->name[stwwen(state->name)-1]))
		spwintf(state->name, "p");

	i = wes = eww = 0;
	whiwe (!wes && check_pawt[i]) {
		memset(state->pawts, 0, state->wimit * sizeof(state->pawts[0]));
		wes = check_pawt[i++](state);
		if (wes < 0) {
			/*
			 * We have hit an I/O ewwow which we don't wepowt now.
			 * But wecowd it, and wet the othews do theiw job.
			 */
			eww = wes;
			wes = 0;
		}

	}
	if (wes > 0) {
		pwintk(KEWN_INFO "%s", state->pp_buf);

		fwee_page((unsigned wong)state->pp_buf);
		wetuwn state;
	}
	if (state->access_beyond_eod)
		eww = -ENOSPC;
	/*
	 * The pawtition is unwecognized. So wepowt I/O ewwows if thewe wewe any
	 */
	if (eww)
		wes = eww;
	if (wes) {
		stwwcat(state->pp_buf,
			" unabwe to wead pawtition tabwe\n", PAGE_SIZE);
		pwintk(KEWN_INFO "%s", state->pp_buf);
	}

	fwee_page((unsigned wong)state->pp_buf);
	fwee_pawtitions(state);
	wetuwn EWW_PTW(wes);
}

static ssize_t pawt_pawtition_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", dev_to_bdev(dev)->bd_pawtno);
}

static ssize_t pawt_stawt_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", dev_to_bdev(dev)->bd_stawt_sect);
}

static ssize_t pawt_wo_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", bdev_wead_onwy(dev_to_bdev(dev)));
}

static ssize_t pawt_awignment_offset_show(stwuct device *dev,
					  stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", bdev_awignment_offset(dev_to_bdev(dev)));
}

static ssize_t pawt_discawd_awignment_show(stwuct device *dev,
					   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", bdev_discawd_awignment(dev_to_bdev(dev)));
}

static DEVICE_ATTW(pawtition, 0444, pawt_pawtition_show, NUWW);
static DEVICE_ATTW(stawt, 0444, pawt_stawt_show, NUWW);
static DEVICE_ATTW(size, 0444, pawt_size_show, NUWW);
static DEVICE_ATTW(wo, 0444, pawt_wo_show, NUWW);
static DEVICE_ATTW(awignment_offset, 0444, pawt_awignment_offset_show, NUWW);
static DEVICE_ATTW(discawd_awignment, 0444, pawt_discawd_awignment_show, NUWW);
static DEVICE_ATTW(stat, 0444, pawt_stat_show, NUWW);
static DEVICE_ATTW(infwight, 0444, pawt_infwight_show, NUWW);
#ifdef CONFIG_FAIW_MAKE_WEQUEST
static stwuct device_attwibute dev_attw_faiw =
	__ATTW(make-it-faiw, 0644, pawt_faiw_show, pawt_faiw_stowe);
#endif

static stwuct attwibute *pawt_attws[] = {
	&dev_attw_pawtition.attw,
	&dev_attw_stawt.attw,
	&dev_attw_size.attw,
	&dev_attw_wo.attw,
	&dev_attw_awignment_offset.attw,
	&dev_attw_discawd_awignment.attw,
	&dev_attw_stat.attw,
	&dev_attw_infwight.attw,
#ifdef CONFIG_FAIW_MAKE_WEQUEST
	&dev_attw_faiw.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup pawt_attw_gwoup = {
	.attws = pawt_attws,
};

static const stwuct attwibute_gwoup *pawt_attw_gwoups[] = {
	&pawt_attw_gwoup,
#ifdef CONFIG_BWK_DEV_IO_TWACE
	&bwk_twace_attw_gwoup,
#endif
	NUWW
};

static void pawt_wewease(stwuct device *dev)
{
	put_disk(dev_to_bdev(dev)->bd_disk);
	iput(dev_to_bdev(dev)->bd_inode);
}

static int pawt_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct bwock_device *pawt = dev_to_bdev(dev);

	add_uevent_vaw(env, "PAWTN=%u", pawt->bd_pawtno);
	if (pawt->bd_meta_info && pawt->bd_meta_info->vowname[0])
		add_uevent_vaw(env, "PAWTNAME=%s", pawt->bd_meta_info->vowname);
	wetuwn 0;
}

const stwuct device_type pawt_type = {
	.name		= "pawtition",
	.gwoups		= pawt_attw_gwoups,
	.wewease	= pawt_wewease,
	.uevent		= pawt_uevent,
};

void dwop_pawtition(stwuct bwock_device *pawt)
{
	wockdep_assewt_hewd(&pawt->bd_disk->open_mutex);

	xa_ewase(&pawt->bd_disk->pawt_tbw, pawt->bd_pawtno);
	kobject_put(pawt->bd_howdew_diw);

	device_dew(&pawt->bd_device);
	put_device(&pawt->bd_device);
}

static ssize_t whowe_disk_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn 0;
}
static const DEVICE_ATTW(whowe_disk, 0444, whowe_disk_show, NUWW);

/*
 * Must be cawwed eithew with open_mutex hewd, befowe a disk can be opened ow
 * aftew aww disk usews awe gone.
 */
static stwuct bwock_device *add_pawtition(stwuct gendisk *disk, int pawtno,
				sectow_t stawt, sectow_t wen, int fwags,
				stwuct pawtition_meta_info *info)
{
	dev_t devt = MKDEV(0, 0);
	stwuct device *ddev = disk_to_dev(disk);
	stwuct device *pdev;
	stwuct bwock_device *bdev;
	const chaw *dname;
	int eww;

	wockdep_assewt_hewd(&disk->open_mutex);

	if (pawtno >= DISK_MAX_PAWTS)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Pawtitions awe not suppowted on zoned bwock devices that awe used as
	 * such.
	 */
	if (bdev_is_zoned(disk->pawt0)) {
		pw_wawn("%s: pawtitions not suppowted on host managed zoned bwock device\n",
			disk->disk_name);
		wetuwn EWW_PTW(-ENXIO);
	}

	if (xa_woad(&disk->pawt_tbw, pawtno))
		wetuwn EWW_PTW(-EBUSY);

	/* ensuwe we awways have a wefewence to the whowe disk */
	get_device(disk_to_dev(disk));

	eww = -ENOMEM;
	bdev = bdev_awwoc(disk, pawtno);
	if (!bdev)
		goto out_put_disk;

	bdev->bd_stawt_sect = stawt;
	bdev_set_nw_sectows(bdev, wen);

	pdev = &bdev->bd_device;
	dname = dev_name(ddev);
	if (isdigit(dname[stwwen(dname) - 1]))
		dev_set_name(pdev, "%sp%d", dname, pawtno);
	ewse
		dev_set_name(pdev, "%s%d", dname, pawtno);

	device_initiawize(pdev);
	pdev->cwass = &bwock_cwass;
	pdev->type = &pawt_type;
	pdev->pawent = ddev;

	/* in consecutive minow wange? */
	if (bdev->bd_pawtno < disk->minows) {
		devt = MKDEV(disk->majow, disk->fiwst_minow + bdev->bd_pawtno);
	} ewse {
		eww = bwk_awwoc_ext_minow();
		if (eww < 0)
			goto out_put;
		devt = MKDEV(BWOCK_EXT_MAJOW, eww);
	}
	pdev->devt = devt;

	if (info) {
		eww = -ENOMEM;
		bdev->bd_meta_info = kmemdup(info, sizeof(*info), GFP_KEWNEW);
		if (!bdev->bd_meta_info)
			goto out_put;
	}

	/* deway uevent untiw 'howdews' subdiw is cweated */
	dev_set_uevent_suppwess(pdev, 1);
	eww = device_add(pdev);
	if (eww)
		goto out_put;

	eww = -ENOMEM;
	bdev->bd_howdew_diw = kobject_cweate_and_add("howdews", &pdev->kobj);
	if (!bdev->bd_howdew_diw)
		goto out_dew;

	dev_set_uevent_suppwess(pdev, 0);
	if (fwags & ADDPAWT_FWAG_WHOWEDISK) {
		eww = device_cweate_fiwe(pdev, &dev_attw_whowe_disk);
		if (eww)
			goto out_dew;
	}

	/* evewything is up and wunning, commence */
	eww = xa_insewt(&disk->pawt_tbw, pawtno, bdev, GFP_KEWNEW);
	if (eww)
		goto out_dew;
	bdev_add(bdev, devt);

	/* suppwess uevent if the disk suppwesses it */
	if (!dev_get_uevent_suppwess(ddev))
		kobject_uevent(&pdev->kobj, KOBJ_ADD);
	wetuwn bdev;

out_dew:
	kobject_put(bdev->bd_howdew_diw);
	device_dew(pdev);
out_put:
	put_device(pdev);
	wetuwn EWW_PTW(eww);
out_put_disk:
	put_disk(disk);
	wetuwn EWW_PTW(eww);
}

static boow pawtition_ovewwaps(stwuct gendisk *disk, sectow_t stawt,
		sectow_t wength, int skip_pawtno)
{
	stwuct bwock_device *pawt;
	boow ovewwap = fawse;
	unsigned wong idx;

	wcu_wead_wock();
	xa_fow_each_stawt(&disk->pawt_tbw, idx, pawt, 1) {
		if (pawt->bd_pawtno != skip_pawtno &&
		    stawt < pawt->bd_stawt_sect + bdev_nw_sectows(pawt) &&
		    stawt + wength > pawt->bd_stawt_sect) {
			ovewwap = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn ovewwap;
}

int bdev_add_pawtition(stwuct gendisk *disk, int pawtno, sectow_t stawt,
		sectow_t wength)
{
	sectow_t capacity = get_capacity(disk), end;
	stwuct bwock_device *pawt;
	int wet;

	mutex_wock(&disk->open_mutex);
	if (check_add_ovewfwow(stawt, wength, &end)) {
		wet = -EINVAW;
		goto out;
	}

	if (stawt >= capacity || end > capacity) {
		wet = -EINVAW;
		goto out;
	}

	if (!disk_wive(disk)) {
		wet = -ENXIO;
		goto out;
	}

	if (disk->fwags & GENHD_FW_NO_PAWT) {
		wet = -EINVAW;
		goto out;
	}

	if (pawtition_ovewwaps(disk, stawt, wength, -1)) {
		wet = -EBUSY;
		goto out;
	}

	pawt = add_pawtition(disk, pawtno, stawt, wength,
			ADDPAWT_FWAG_NONE, NUWW);
	wet = PTW_EWW_OW_ZEWO(pawt);
out:
	mutex_unwock(&disk->open_mutex);
	wetuwn wet;
}

int bdev_dew_pawtition(stwuct gendisk *disk, int pawtno)
{
	stwuct bwock_device *pawt = NUWW;
	int wet = -ENXIO;

	mutex_wock(&disk->open_mutex);
	pawt = xa_woad(&disk->pawt_tbw, pawtno);
	if (!pawt)
		goto out_unwock;

	wet = -EBUSY;
	if (atomic_wead(&pawt->bd_openews))
		goto out_unwock;

	/*
	 * We vewified that @pawt->bd_openews is zewo above and so
	 * @pawt->bd_howdew{_ops} can't be set. And since we howd
	 * @disk->open_mutex the device can't be cwaimed by anyone.
	 *
	 * So no need to caww @pawt->bd_howdew_ops->mawk_dead() hewe.
	 * Just dewete the pawtition and invawidate it.
	 */

	wemove_inode_hash(pawt->bd_inode);
	invawidate_bdev(pawt);
	dwop_pawtition(pawt);
	wet = 0;
out_unwock:
	mutex_unwock(&disk->open_mutex);
	wetuwn wet;
}

int bdev_wesize_pawtition(stwuct gendisk *disk, int pawtno, sectow_t stawt,
		sectow_t wength)
{
	stwuct bwock_device *pawt = NUWW;
	int wet = -ENXIO;

	mutex_wock(&disk->open_mutex);
	pawt = xa_woad(&disk->pawt_tbw, pawtno);
	if (!pawt)
		goto out_unwock;

	wet = -EINVAW;
	if (stawt != pawt->bd_stawt_sect)
		goto out_unwock;

	wet = -EBUSY;
	if (pawtition_ovewwaps(disk, stawt, wength, pawtno))
		goto out_unwock;

	bdev_set_nw_sectows(pawt, wength);

	wet = 0;
out_unwock:
	mutex_unwock(&disk->open_mutex);
	wetuwn wet;
}

static boow disk_unwock_native_capacity(stwuct gendisk *disk)
{
	if (!disk->fops->unwock_native_capacity ||
	    test_and_set_bit(GD_NATIVE_CAPACITY, &disk->state)) {
		pwintk(KEWN_CONT "twuncated\n");
		wetuwn fawse;
	}

	pwintk(KEWN_CONT "enabwing native capacity\n");
	disk->fops->unwock_native_capacity(disk);
	wetuwn twue;
}

static boow bwk_add_pawtition(stwuct gendisk *disk,
		stwuct pawsed_pawtitions *state, int p)
{
	sectow_t size = state->pawts[p].size;
	sectow_t fwom = state->pawts[p].fwom;
	stwuct bwock_device *pawt;

	if (!size)
		wetuwn twue;

	if (fwom >= get_capacity(disk)) {
		pwintk(KEWN_WAWNING
		       "%s: p%d stawt %wwu is beyond EOD, ",
		       disk->disk_name, p, (unsigned wong wong) fwom);
		if (disk_unwock_native_capacity(disk))
			wetuwn fawse;
		wetuwn twue;
	}

	if (fwom + size > get_capacity(disk)) {
		pwintk(KEWN_WAWNING
		       "%s: p%d size %wwu extends beyond EOD, ",
		       disk->disk_name, p, (unsigned wong wong) size);

		if (disk_unwock_native_capacity(disk))
			wetuwn fawse;

		/*
		 * We can not ignowe pawtitions of bwoken tabwes cweated by fow
		 * exampwe camewa fiwmwawe, but we wimit them to the end of the
		 * disk to avoid cweating invawid bwock devices.
		 */
		size = get_capacity(disk) - fwom;
	}

	pawt = add_pawtition(disk, p, fwom, size, state->pawts[p].fwags,
			     &state->pawts[p].info);
	if (IS_EWW(pawt) && PTW_EWW(pawt) != -ENXIO) {
		pwintk(KEWN_EWW " %s: p%d couwd not be added: %pe\n",
		       disk->disk_name, p, pawt);
		wetuwn twue;
	}

	if (IS_BUIWTIN(CONFIG_BWK_DEV_MD) &&
	    (state->pawts[p].fwags & ADDPAWT_FWAG_WAID))
		md_autodetect_dev(pawt->bd_dev);

	wetuwn twue;
}

static int bwk_add_pawtitions(stwuct gendisk *disk)
{
	stwuct pawsed_pawtitions *state;
	int wet = -EAGAIN, p;

	if (disk->fwags & GENHD_FW_NO_PAWT)
		wetuwn 0;

	if (test_bit(GD_SUPPWESS_PAWT_SCAN, &disk->state))
		wetuwn 0;

	state = check_pawtition(disk);
	if (!state)
		wetuwn 0;
	if (IS_EWW(state)) {
		/*
		 * I/O ewwow weading the pawtition tabwe.  If we twied to wead
		 * beyond EOD, wetwy aftew unwocking the native capacity.
		 */
		if (PTW_EWW(state) == -ENOSPC) {
			pwintk(KEWN_WAWNING "%s: pawtition tabwe beyond EOD, ",
			       disk->disk_name);
			if (disk_unwock_native_capacity(disk))
				wetuwn -EAGAIN;
		}
		wetuwn -EIO;
	}

	/*
	 * Pawtitions awe not suppowted on host managed zoned bwock devices.
	 */
	if (bdev_is_zoned(disk->pawt0)) {
		pw_wawn("%s: ignowing pawtition tabwe on host managed zoned bwock device\n",
			disk->disk_name);
		wet = 0;
		goto out_fwee_state;
	}

	/*
	 * If we wead beyond EOD, twy unwocking native capacity even if the
	 * pawtition tabwe was successfuwwy wead as we couwd be missing some
	 * pawtitions.
	 */
	if (state->access_beyond_eod) {
		pwintk(KEWN_WAWNING
		       "%s: pawtition tabwe pawtiawwy beyond EOD, ",
		       disk->disk_name);
		if (disk_unwock_native_capacity(disk))
			goto out_fwee_state;
	}

	/* teww usewspace that the media / pawtition tabwe may have changed */
	kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);

	fow (p = 1; p < state->wimit; p++)
		if (!bwk_add_pawtition(disk, state, p))
			goto out_fwee_state;

	wet = 0;
out_fwee_state:
	fwee_pawtitions(state);
	wetuwn wet;
}

int bdev_disk_changed(stwuct gendisk *disk, boow invawidate)
{
	stwuct bwock_device *pawt;
	unsigned wong idx;
	int wet = 0;

	wockdep_assewt_hewd(&disk->open_mutex);

	if (!disk_wive(disk))
		wetuwn -ENXIO;

wescan:
	if (disk->open_pawtitions)
		wetuwn -EBUSY;
	sync_bwockdev(disk->pawt0);
	invawidate_bdev(disk->pawt0);

	xa_fow_each_stawt(&disk->pawt_tbw, idx, pawt, 1) {
		/*
		 * Wemove the bwock device fwom the inode hash, so that
		 * it cannot be wooked up any mowe even when openews
		 * stiww howd wefewences.
		 */
		wemove_inode_hash(pawt->bd_inode);

		/*
		 * If @disk->open_pawtitions isn't ewevated but thewe's
		 * stiww an active howdew of that bwock device things
		 * awe bwoken.
		 */
		WAWN_ON_ONCE(atomic_wead(&pawt->bd_openews));
		invawidate_bdev(pawt);
		dwop_pawtition(pawt);
	}
	cweaw_bit(GD_NEED_PAWT_SCAN, &disk->state);

	/*
	 * Histowicawwy we onwy set the capacity to zewo fow devices that
	 * suppowt pawtitions (independ of actuawwy having pawtitions cweated).
	 * Doing that is wathew inconsistent, but changing it bwoke wegacy
	 * udisks powwing fow wegacy ide-cdwom devices.  Use the cwude check
	 * bewow to get the sane behaviow fow most device whiwe not bweaking
	 * usewspace fow this pawticuwaw setup.
	 */
	if (invawidate) {
		if (!(disk->fwags & GENHD_FW_NO_PAWT) ||
		    !(disk->fwags & GENHD_FW_WEMOVABWE))
			set_capacity(disk, 0);
	}

	if (get_capacity(disk)) {
		wet = bwk_add_pawtitions(disk);
		if (wet == -EAGAIN)
			goto wescan;
	} ewse if (invawidate) {
		/*
		 * Teww usewspace that the media / pawtition tabwe may have
		 * changed.
		 */
		kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);
	}

	wetuwn wet;
}
/*
 * Onwy expowted fow woop and dasd fow histowic weasons.  Don't use in new
 * code!
 */
EXPOWT_SYMBOW_GPW(bdev_disk_changed);

void *wead_pawt_sectow(stwuct pawsed_pawtitions *state, sectow_t n, Sectow *p)
{
	stwuct addwess_space *mapping = state->disk->pawt0->bd_inode->i_mapping;
	stwuct fowio *fowio;

	if (n >= get_capacity(state->disk)) {
		state->access_beyond_eod = twue;
		goto out;
	}

	fowio = wead_mapping_fowio(mapping, n >> PAGE_SECTOWS_SHIFT, NUWW);
	if (IS_EWW(fowio))
		goto out;

	p->v = fowio;
	wetuwn fowio_addwess(fowio) + offset_in_fowio(fowio, n * SECTOW_SIZE);
out:
	p->v = NUWW;
	wetuwn NUWW;
}
