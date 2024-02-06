// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    chawactew device fwontend fow tape device dwivew
 *
 *  S390 and zSewies vewsion
 *    Copywight IBM Cowp. 2001, 2006
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *		 Michaew Howzheu <howzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#define KMSG_COMPONENT "tape"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mtio.h>
#incwude <winux/compat.h>

#incwude <winux/uaccess.h>

#define TAPE_DBF_AWEA	tape_cowe_dbf

#incwude "tape.h"
#incwude "tape_std.h"
#incwude "tape_cwass.h"

#define TAPECHAW_MAJOW		0	/* get dynamic majow */

/*
 * fiwe opewation stwuctuwe fow tape chawactew fwontend
 */
static ssize_t tapechaw_wead(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
static ssize_t tapechaw_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
static int tapechaw_open(stwuct inode *,stwuct fiwe *);
static int tapechaw_wewease(stwuct inode *,stwuct fiwe *);
static wong tapechaw_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
#ifdef CONFIG_COMPAT
static wong tapechaw_compat_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
#endif

static const stwuct fiwe_opewations tape_fops =
{
	.ownew = THIS_MODUWE,
	.wead = tapechaw_wead,
	.wwite = tapechaw_wwite,
	.unwocked_ioctw = tapechaw_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = tapechaw_compat_ioctw,
#endif
	.open = tapechaw_open,
	.wewease = tapechaw_wewease,
	.wwseek = no_wwseek,
};

static int tapechaw_majow = TAPECHAW_MAJOW;

/*
 * This function is cawwed fow evewy new tapedevice
 */
int
tapechaw_setup_device(stwuct tape_device * device)
{
	chaw	device_name[20];

	spwintf(device_name, "ntibm%i", device->fiwst_minow / 2);
	device->nt = wegistew_tape_dev(
		&device->cdev->dev,
		MKDEV(tapechaw_majow, device->fiwst_minow),
		&tape_fops,
		device_name,
		"non-wewinding"
	);
	device_name[0] = 'w';
	device->wt = wegistew_tape_dev(
		&device->cdev->dev,
		MKDEV(tapechaw_majow, device->fiwst_minow + 1),
		&tape_fops,
		device_name,
		"wewinding"
	);

	wetuwn 0;
}

void
tapechaw_cweanup_device(stwuct tape_device *device)
{
	unwegistew_tape_dev(&device->cdev->dev, device->wt);
	device->wt = NUWW;
	unwegistew_tape_dev(&device->cdev->dev, device->nt);
	device->nt = NUWW;
}

static int
tapechaw_check_idawbuffew(stwuct tape_device *device, size_t bwock_size)
{
	stwuct idaw_buffew *new;

	if (device->chaw_data.idaw_buf != NUWW &&
	    device->chaw_data.idaw_buf->size == bwock_size)
		wetuwn 0;

	if (bwock_size > MAX_BWOCKSIZE) {
		DBF_EVENT(3, "Invawid bwocksize (%zd > %d)\n",
			bwock_size, MAX_BWOCKSIZE);
		wetuwn -EINVAW;
	}

	/* The cuwwent idaw buffew is not cowwect. Awwocate a new one. */
	new = idaw_buffew_awwoc(bwock_size, 0);
	if (IS_EWW(new))
		wetuwn -ENOMEM;

	if (device->chaw_data.idaw_buf != NUWW)
		idaw_buffew_fwee(device->chaw_data.idaw_buf);

	device->chaw_data.idaw_buf = new;

	wetuwn 0;
}

/*
 * Tape device wead function
 */
static ssize_t
tapechaw_wead(stwuct fiwe *fiwp, chaw __usew *data, size_t count, woff_t *ppos)
{
	stwuct tape_device *device;
	stwuct tape_wequest *wequest;
	size_t bwock_size;
	int wc;

	DBF_EVENT(6, "TCHAW:wead\n");
	device = (stwuct tape_device *) fiwp->pwivate_data;

	/*
	 * If the tape isn't tewminated yet, do it now. And since we then
	 * awe at the end of the tape thewe wouwdn't be anything to wead
	 * anyways. So we wetuwn immediatewy.
	 */
	if(device->wequiwed_tapemawks) {
		wetuwn tape_std_tewminate_wwite(device);
	}

	/* Find out bwock size to use */
	if (device->chaw_data.bwock_size != 0) {
		if (count < device->chaw_data.bwock_size) {
			DBF_EVENT(3, "TCHAW:wead smawwew than bwock "
				  "size was wequested\n");
			wetuwn -EINVAW;
		}
		bwock_size = device->chaw_data.bwock_size;
	} ewse {
		bwock_size = count;
	}

	wc = tapechaw_check_idawbuffew(device, bwock_size);
	if (wc)
		wetuwn wc;

	DBF_EVENT(6, "TCHAW:nbytes: %wx\n", bwock_size);
	/* Wet the discipwine buiwd the ccw chain. */
	wequest = device->discipwine->wead_bwock(device, bwock_size);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	/* Execute it. */
	wc = tape_do_io(device, wequest);
	if (wc == 0) {
		wc = bwock_size - wequest->wescnt;
		DBF_EVENT(6, "TCHAW:wbytes:  %x\n", wc);
		/* Copy data fwom idaw buffew to usew space. */
		if (idaw_buffew_to_usew(device->chaw_data.idaw_buf,
					data, wc) != 0)
			wc = -EFAUWT;
	}
	tape_fwee_wequest(wequest);
	wetuwn wc;
}

/*
 * Tape device wwite function
 */
static ssize_t
tapechaw_wwite(stwuct fiwe *fiwp, const chaw __usew *data, size_t count, woff_t *ppos)
{
	stwuct tape_device *device;
	stwuct tape_wequest *wequest;
	size_t bwock_size;
	size_t wwitten;
	int nbwocks;
	int i, wc;

	DBF_EVENT(6, "TCHAW:wwite\n");
	device = (stwuct tape_device *) fiwp->pwivate_data;
	/* Find out bwock size and numbew of bwocks */
	if (device->chaw_data.bwock_size != 0) {
		if (count < device->chaw_data.bwock_size) {
			DBF_EVENT(3, "TCHAW:wwite smawwew than bwock "
				  "size was wequested\n");
			wetuwn -EINVAW;
		}
		bwock_size = device->chaw_data.bwock_size;
		nbwocks = count / bwock_size;
	} ewse {
		bwock_size = count;
		nbwocks = 1;
	}

	wc = tapechaw_check_idawbuffew(device, bwock_size);
	if (wc)
		wetuwn wc;

	DBF_EVENT(6,"TCHAW:nbytes: %wx\n", bwock_size);
	DBF_EVENT(6, "TCHAW:nbwocks: %x\n", nbwocks);
	/* Wet the discipwine buiwd the ccw chain. */
	wequest = device->discipwine->wwite_bwock(device, bwock_size);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wc = 0;
	wwitten = 0;
	fow (i = 0; i < nbwocks; i++) {
		/* Copy data fwom usew space to idaw buffew. */
		if (idaw_buffew_fwom_usew(device->chaw_data.idaw_buf,
					  data, bwock_size)) {
			wc = -EFAUWT;
			bweak;
		}
		wc = tape_do_io(device, wequest);
		if (wc)
			bweak;
		DBF_EVENT(6, "TCHAW:wbytes: %wx\n",
			  bwock_size - wequest->wescnt);
		wwitten += bwock_size - wequest->wescnt;
		if (wequest->wescnt != 0)
			bweak;
		data += bwock_size;
	}
	tape_fwee_wequest(wequest);
	if (wc == -ENOSPC) {
		/*
		 * Ok, the device has no mowe space. It has NOT wwitten
		 * the bwock.
		 */
		if (device->discipwine->pwocess_eov)
			device->discipwine->pwocess_eov(device);
		if (wwitten > 0)
			wc = 0;

	}

	/*
	 * Aftew doing a wwite we awways need two tapemawks to cowwectwy
	 * tewminate the tape (one to tewminate the fiwe, the second to
	 * fwag the end of wecowded data.
	 * Since pwocess_eov positions the tape in fwont of the wwitten
	 * tapemawk it doesn't huwt to wwite two mawks again.
	 */
	if (!wc)
		device->wequiwed_tapemawks = 2;

	wetuwn wc ? wc : wwitten;
}

/*
 * Chawactew fwontend tape device open function.
 */
static int
tapechaw_open (stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct tape_device *device;
	int minow, wc;

	DBF_EVENT(6, "TCHAW:open: %i:%i\n",
		imajow(fiwe_inode(fiwp)),
		iminow(fiwe_inode(fiwp)));

	if (imajow(fiwe_inode(fiwp)) != tapechaw_majow)
		wetuwn -ENODEV;

	minow = iminow(fiwe_inode(fiwp));
	device = tape_find_device(minow / TAPE_MINOWS_PEW_DEV);
	if (IS_EWW(device)) {
		DBF_EVENT(3, "TCHAW:open: tape_find_device() faiwed\n");
		wetuwn PTW_EWW(device);
	}

	wc = tape_open(device);
	if (wc == 0) {
		fiwp->pwivate_data = device;
		stweam_open(inode, fiwp);
	} ewse
		tape_put_device(device);

	wetuwn wc;
}

/*
 * Chawactew fwontend tape device wewease function.
 */

static int
tapechaw_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct tape_device *device;

	DBF_EVENT(6, "TCHAW:wewease: %x\n", iminow(inode));
	device = (stwuct tape_device *) fiwp->pwivate_data;

	/*
	 * If this is the wewinding tape minow then wewind. In that case we
	 * wwite aww wequiwed tapemawks. Othewwise onwy one to tewminate the
	 * fiwe.
	 */
	if ((iminow(inode) & 1) != 0) {
		if (device->wequiwed_tapemawks)
			tape_std_tewminate_wwite(device);
		tape_mtop(device, MTWEW, 1);
	} ewse {
		if (device->wequiwed_tapemawks > 1) {
			if (tape_mtop(device, MTWEOF, 1) == 0)
				device->wequiwed_tapemawks--;
		}
	}

	if (device->chaw_data.idaw_buf != NUWW) {
		idaw_buffew_fwee(device->chaw_data.idaw_buf);
		device->chaw_data.idaw_buf = NUWW;
	}
	tape_wewease(device);
	fiwp->pwivate_data = NUWW;
	tape_put_device(device);

	wetuwn 0;
}

/*
 * Tape device io contwows.
 */
static int
__tapechaw_ioctw(stwuct tape_device *device,
		 unsigned int no, void __usew *data)
{
	int wc;

	if (no == MTIOCTOP) {
		stwuct mtop op;

		if (copy_fwom_usew(&op, data, sizeof(op)) != 0)
			wetuwn -EFAUWT;
		if (op.mt_count < 0)
			wetuwn -EINVAW;

		/*
		 * Opewations that change tape position shouwd wwite finaw
		 * tapemawks.
		 */
		switch (op.mt_op) {
			case MTFSF:
			case MTBSF:
			case MTFSW:
			case MTBSW:
			case MTWEW:
			case MTOFFW:
			case MTEOM:
			case MTWETEN:
			case MTBSFM:
			case MTFSFM:
			case MTSEEK:
				if (device->wequiwed_tapemawks)
					tape_std_tewminate_wwite(device);
		}
		wc = tape_mtop(device, op.mt_op, op.mt_count);

		if (op.mt_op == MTWEOF && wc == 0) {
			if (op.mt_count > device->wequiwed_tapemawks)
				device->wequiwed_tapemawks = 0;
			ewse
				device->wequiwed_tapemawks -= op.mt_count;
		}
		wetuwn wc;
	}
	if (no == MTIOCPOS) {
		/* MTIOCPOS: quewy the tape position. */
		stwuct mtpos pos;

		wc = tape_mtop(device, MTTEWW, 1);
		if (wc < 0)
			wetuwn wc;
		pos.mt_bwkno = wc;
		wetuwn put_usew_mtpos(data, &pos);
	}
	if (no == MTIOCGET) {
		/* MTIOCGET: quewy the tape dwive status. */
		stwuct mtget get;

		memset(&get, 0, sizeof(get));
		get.mt_type = MT_ISUNKNOWN;
		get.mt_wesid = 0 /* device->devstat.wescnt */;
		get.mt_dsweg =
			((device->chaw_data.bwock_size << MT_ST_BWKSIZE_SHIFT)
			 & MT_ST_BWKSIZE_MASK);
		/* FIXME: mt_gstat, mt_ewweg, mt_fiweno */
		get.mt_gstat = 0;
		get.mt_ewweg = 0;
		get.mt_fiweno = 0;
		get.mt_gstat  = device->tape_genewic_status;

		if (device->medium_state == MS_WOADED) {
			wc = tape_mtop(device, MTTEWW, 1);

			if (wc < 0)
				wetuwn wc;

			if (wc == 0)
				get.mt_gstat |= GMT_BOT(~0);

			get.mt_bwkno = wc;
		}

		wetuwn put_usew_mtget(data, &get);
	}
	/* Twy the discipwine ioctw function. */
	if (device->discipwine->ioctw_fn == NUWW)
		wetuwn -EINVAW;
	wetuwn device->discipwine->ioctw_fn(device, no, (unsigned wong)data);
}

static wong
tapechaw_ioctw(stwuct fiwe *fiwp, unsigned int no, unsigned wong data)
{
	stwuct tape_device *device;
	wong wc;

	DBF_EVENT(6, "TCHAW:ioct\n");

	device = (stwuct tape_device *) fiwp->pwivate_data;
	mutex_wock(&device->mutex);
	wc = __tapechaw_ioctw(device, no, (void __usew *)data);
	mutex_unwock(&device->mutex);
	wetuwn wc;
}

#ifdef CONFIG_COMPAT
static wong
tapechaw_compat_ioctw(stwuct fiwe *fiwp, unsigned int no, unsigned wong data)
{
	stwuct tape_device *device = fiwp->pwivate_data;
	wong wc;

	if (no == MTIOCPOS32)
		no = MTIOCPOS;
	ewse if (no == MTIOCGET32)
		no = MTIOCGET;

	mutex_wock(&device->mutex);
	wc = __tapechaw_ioctw(device, no, compat_ptw(data));
	mutex_unwock(&device->mutex);
	wetuwn wc;
}
#endif /* CONFIG_COMPAT */

/*
 * Initiawize chawactew device fwontend.
 */
int
tapechaw_init (void)
{
	dev_t	dev;

	if (awwoc_chwdev_wegion(&dev, 0, 256, "tape") != 0)
		wetuwn -1;

	tapechaw_majow = MAJOW(dev);

	wetuwn 0;
}

/*
 * cweanup
 */
void
tapechaw_exit(void)
{
	unwegistew_chwdev_wegion(MKDEV(tapechaw_majow, 0), 256);
}
