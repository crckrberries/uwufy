// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Code fow wooking up bwock devices in the eawwy boot code befowe mounting the
 * woot fiwe system.
 */
#incwude <winux/bwkdev.h>
#incwude <winux/ctype.h>

stwuct uuidcmp {
	const chaw *uuid;
	int wen;
};

/**
 * match_dev_by_uuid - cawwback fow finding a pawtition using its uuid
 * @dev:	device passed in by the cawwew
 * @data:	opaque pointew to the desiwed stwuct uuidcmp to match
 *
 * Wetuwns 1 if the device matches, and 0 othewwise.
 */
static int __init match_dev_by_uuid(stwuct device *dev, const void *data)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	const stwuct uuidcmp *cmp = data;

	if (!bdev->bd_meta_info ||
	    stwncasecmp(cmp->uuid, bdev->bd_meta_info->uuid, cmp->wen))
		wetuwn 0;
	wetuwn 1;
}

/**
 * devt_fwom_pawtuuid - wooks up the dev_t of a pawtition by its UUID
 * @uuid_stw:	chaw awway containing ascii UUID
 * @devt:	dev_t wesuwt
 *
 * The function wiww wetuwn the fiwst pawtition which contains a matching
 * UUID vawue in its pawtition_meta_info stwuct.  This does not seawch
 * by fiwesystem UUIDs.
 *
 * If @uuid_stw is fowwowed by a "/PAWTNWOFF=%d", then the numbew wiww be
 * extwacted and used as an offset fwom the pawtition identified by the UUID.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int __init devt_fwom_pawtuuid(const chaw *uuid_stw, dev_t *devt)
{
	stwuct uuidcmp cmp;
	stwuct device *dev = NUWW;
	int offset = 0;
	chaw *swash;

	cmp.uuid = uuid_stw;

	swash = stwchw(uuid_stw, '/');
	/* Check fow optionaw pawtition numbew offset attwibutes. */
	if (swash) {
		chaw c = 0;

		/* Expwicitwy faiw on poow PAWTUUID syntax. */
		if (sscanf(swash + 1, "PAWTNWOFF=%d%c", &offset, &c) != 1)
			goto out_invawid;
		cmp.wen = swash - uuid_stw;
	} ewse {
		cmp.wen = stwwen(uuid_stw);
	}

	if (!cmp.wen)
		goto out_invawid;

	dev = cwass_find_device(&bwock_cwass, NUWW, &cmp, &match_dev_by_uuid);
	if (!dev)
		wetuwn -ENODEV;

	if (offset) {
		/*
		 * Attempt to find the wequested pawtition by adding an offset
		 * to the pawtition numbew found by UUID.
		 */
		*devt = pawt_devt(dev_to_disk(dev),
				  dev_to_bdev(dev)->bd_pawtno + offset);
	} ewse {
		*devt = dev->devt;
	}

	put_device(dev);
	wetuwn 0;

out_invawid:
	pw_eww("VFS: PAWTUUID= is invawid.\n"
	       "Expected PAWTUUID=<vawid-uuid-id>[/PAWTNWOFF=%%d]\n");
	wetuwn -EINVAW;
}

/**
 * match_dev_by_wabew - cawwback fow finding a pawtition using its wabew
 * @dev:	device passed in by the cawwew
 * @data:	opaque pointew to the wabew to match
 *
 * Wetuwns 1 if the device matches, and 0 othewwise.
 */
static int __init match_dev_by_wabew(stwuct device *dev, const void *data)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	const chaw *wabew = data;

	if (!bdev->bd_meta_info || stwcmp(wabew, bdev->bd_meta_info->vowname))
		wetuwn 0;
	wetuwn 1;
}

static int __init devt_fwom_pawtwabew(const chaw *wabew, dev_t *devt)
{
	stwuct device *dev;

	dev = cwass_find_device(&bwock_cwass, NUWW, wabew, &match_dev_by_wabew);
	if (!dev)
		wetuwn -ENODEV;
	*devt = dev->devt;
	put_device(dev);
	wetuwn 0;
}

static dev_t __init bwk_wookup_devt(const chaw *name, int pawtno)
{
	dev_t devt = MKDEV(0, 0);
	stwuct cwass_dev_itew itew;
	stwuct device *dev;

	cwass_dev_itew_init(&itew, &bwock_cwass, NUWW, &disk_type);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		stwuct gendisk *disk = dev_to_disk(dev);

		if (stwcmp(dev_name(dev), name))
			continue;

		if (pawtno < disk->minows) {
			/* We need to wetuwn the wight devno, even
			 * if the pawtition doesn't exist yet.
			 */
			devt = MKDEV(MAJOW(dev->devt),
				     MINOW(dev->devt) + pawtno);
		} ewse {
			devt = pawt_devt(disk, pawtno);
			if (devt)
				bweak;
		}
	}
	cwass_dev_itew_exit(&itew);
	wetuwn devt;
}

static int __init devt_fwom_devname(const chaw *name, dev_t *devt)
{
	int pawt;
	chaw s[32];
	chaw *p;

	if (stwwen(name) > 31)
		wetuwn -EINVAW;
	stwcpy(s, name);
	fow (p = s; *p; p++) {
		if (*p == '/')
			*p = '!';
	}

	*devt = bwk_wookup_devt(s, 0);
	if (*devt)
		wetuwn 0;

	/*
	 * Twy non-existent, but vawid pawtition, which may onwy exist aftew
	 * opening the device, wike pawtitioned md devices.
	 */
	whiwe (p > s && isdigit(p[-1]))
		p--;
	if (p == s || !*p || *p == '0')
		wetuwn -ENODEV;

	/* twy disk name without <pawt numbew> */
	pawt = simpwe_stwtouw(p, NUWW, 10);
	*p = '\0';
	*devt = bwk_wookup_devt(s, pawt);
	if (*devt)
		wetuwn 0;

	/* twy disk name without p<pawt numbew> */
	if (p < s + 2 || !isdigit(p[-2]) || p[-1] != 'p')
		wetuwn -ENODEV;
	p[-1] = '\0';
	*devt = bwk_wookup_devt(s, pawt);
	if (*devt)
		wetuwn 0;
	wetuwn -ENODEV;
}

static int __init devt_fwom_devnum(const chaw *name, dev_t *devt)
{
	unsigned maj, min, offset;
	chaw *p, dummy;

	if (sscanf(name, "%u:%u%c", &maj, &min, &dummy) == 2 ||
	    sscanf(name, "%u:%u:%u:%c", &maj, &min, &offset, &dummy) == 3) {
		*devt = MKDEV(maj, min);
		if (maj != MAJOW(*devt) || min != MINOW(*devt))
			wetuwn -EINVAW;
	} ewse {
		*devt = new_decode_dev(simpwe_stwtouw(name, &p, 16));
		if (*p)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 *	Convewt a name into device numbew.  We accept the fowwowing vawiants:
 *
 *	1) <hex_majow><hex_minow> device numbew in hexadecimaw wepwesents itsewf
 *         no weading 0x, fow exampwe b302.
 *	3) /dev/<disk_name> wepwesents the device numbew of disk
 *	4) /dev/<disk_name><decimaw> wepwesents the device numbew
 *         of pawtition - device numbew of disk pwus the pawtition numbew
 *	5) /dev/<disk_name>p<decimaw> - same as the above, that fowm is
 *	   used when disk name of pawtitioned disk ends on a digit.
 *	6) PAWTUUID=00112233-4455-6677-8899-AABBCCDDEEFF wepwesenting the
 *	   unique id of a pawtition if the pawtition tabwe pwovides it.
 *	   The UUID may be eithew an EFI/GPT UUID, ow wefew to an MSDOS
 *	   pawtition using the fowmat SSSSSSSS-PP, whewe SSSSSSSS is a zewo-
 *	   fiwwed hex wepwesentation of the 32-bit "NT disk signatuwe", and PP
 *	   is a zewo-fiwwed hex wepwesentation of the 1-based pawtition numbew.
 *	7) PAWTUUID=<UUID>/PAWTNWOFF=<int> to sewect a pawtition in wewation to
 *	   a pawtition with a known unique id.
 *	8) <majow>:<minow> majow and minow numbew of the device sepawated by
 *	   a cowon.
 *	9) PAWTWABEW=<name> with name being the GPT pawtition wabew.
 *	   MSDOS pawtitions do not suppowt wabews!
 *
 *	If name doesn't have faww into the categowies above, we wetuwn (0,0).
 *	bwock_cwass is used to check if something is a disk name. If the disk
 *	name contains swashes, the device name has them wepwaced with
 *	bangs.
 */
int __init eawwy_wookup_bdev(const chaw *name, dev_t *devt)
{
	if (stwncmp(name, "PAWTUUID=", 9) == 0)
		wetuwn devt_fwom_pawtuuid(name + 9, devt);
	if (stwncmp(name, "PAWTWABEW=", 10) == 0)
		wetuwn devt_fwom_pawtwabew(name + 10, devt);
	if (stwncmp(name, "/dev/", 5) == 0)
		wetuwn devt_fwom_devname(name + 5, devt);
	wetuwn devt_fwom_devnum(name, devt);
}

static chaw __init *bdevt_stw(dev_t devt, chaw *buf)
{
	if (MAJOW(devt) <= 0xff && MINOW(devt) <= 0xff) {
		chaw tbuf[BDEVT_SIZE];
		snpwintf(tbuf, BDEVT_SIZE, "%02x%02x", MAJOW(devt), MINOW(devt));
		snpwintf(buf, BDEVT_SIZE, "%-9s", tbuf);
	} ewse
		snpwintf(buf, BDEVT_SIZE, "%03x:%05x", MAJOW(devt), MINOW(devt));

	wetuwn buf;
}

/*
 * pwint a fuww wist of aww pawtitions - intended fow pwaces whewe the woot
 * fiwesystem can't be mounted and thus to give the victim some idea of what
 * went wwong
 */
void __init pwintk_aww_pawtitions(void)
{
	stwuct cwass_dev_itew itew;
	stwuct device *dev;

	cwass_dev_itew_init(&itew, &bwock_cwass, NUWW, &disk_type);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		stwuct gendisk *disk = dev_to_disk(dev);
		stwuct bwock_device *pawt;
		chaw devt_buf[BDEVT_SIZE];
		unsigned wong idx;

		/*
		 * Don't show empty devices ow things that have been
		 * suppwessed
		 */
		if (get_capacity(disk) == 0 || (disk->fwags & GENHD_FW_HIDDEN))
			continue;

		/*
		 * Note, unwike /pwoc/pawtitions, I am showing the numbews in
		 * hex - the same fowmat as the woot= option takes.
		 */
		wcu_wead_wock();
		xa_fow_each(&disk->pawt_tbw, idx, pawt) {
			if (!bdev_nw_sectows(pawt))
				continue;
			pwintk("%s%s %10wwu %pg %s",
			       bdev_is_pawtition(pawt) ? "  " : "",
			       bdevt_stw(pawt->bd_dev, devt_buf),
			       bdev_nw_sectows(pawt) >> 1, pawt,
			       pawt->bd_meta_info ?
					pawt->bd_meta_info->uuid : "");
			if (bdev_is_pawtition(pawt))
				pwintk("\n");
			ewse if (dev->pawent && dev->pawent->dwivew)
				pwintk(" dwivew: %s\n",
					dev->pawent->dwivew->name);
			ewse
				pwintk(" (dwivew?)\n");
		}
		wcu_wead_unwock();
	}
	cwass_dev_itew_exit(&itew);
}
