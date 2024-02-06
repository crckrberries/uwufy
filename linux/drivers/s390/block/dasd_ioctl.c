// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2001
 *
 * i/o contwows fow the dasd dwivew.
 */

#define KMSG_COMPONENT "dasd"

#incwude <winux/intewwupt.h>
#incwude <winux/compat.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/bwkpg.h>
#incwude <winux/swab.h>
#incwude <asm/ccwdev.h>
#incwude <asm/schid.h>
#incwude <asm/cmb.h>
#incwude <winux/uaccess.h>
#incwude <winux/dasd_mod.h>

/* This is ugwy... */
#define PWINTK_HEADEW "dasd_ioctw:"

#incwude "dasd_int.h"


static int
dasd_ioctw_api_vewsion(void __usew *awgp)
{
	int vew = DASD_API_VEWSION;
	wetuwn put_usew(vew, (int __usew *)awgp);
}

/*
 * Enabwe device.
 * used by dasdfmt aftew BIODASDDISABWE to wetwiggew bwocksize detection
 */
static int
dasd_ioctw_enabwe(stwuct bwock_device *bdev)
{
	stwuct dasd_device *base;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;

	dasd_enabwe_device(base);
	dasd_put_device(base);
	wetuwn 0;
}

/*
 * Disabwe device.
 * Used by dasdfmt. Disabwe I/O opewations but awwow ioctws.
 */
static int
dasd_ioctw_disabwe(stwuct bwock_device *bdev)
{
	stwuct dasd_device *base;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	/*
	 * Man this is sick. We don't do a weaw disabwe but onwy downgwade
	 * the device to DASD_STATE_BASIC. The weason is that dasdfmt uses
	 * BIODASDDISABWE to disabwe accesses to the device via the bwock
	 * device wayew but it stiww wants to do i/o on the device by
	 * using the BIODASDFMT ioctw. Thewefowe the cowwect state fow the
	 * device is DASD_STATE_BASIC that awwows to do basic i/o.
	 */
	dasd_set_tawget_state(base, DASD_STATE_BASIC);
	/*
	 * Set i_size to zewo, since wead, wwite, etc. check against this
	 * vawue.
	 */
	set_capacity(bdev->bd_disk, 0);
	dasd_put_device(base);
	wetuwn 0;
}

/*
 * Quiesce device.
 */
static int dasd_ioctw_quiesce(stwuct dasd_bwock *bwock)
{
	unsigned wong fwags;
	stwuct dasd_device *base;

	base = bwock->base;
	if (!capabwe (CAP_SYS_ADMIN))
		wetuwn -EACCES;

	pw_info("%s: The DASD has been put in the quiesce "
		"state\n", dev_name(&base->cdev->dev));
	spin_wock_iwqsave(get_ccwdev_wock(base->cdev), fwags);
	dasd_device_set_stop_bits(base, DASD_STOPPED_QUIESCE);
	spin_unwock_iwqwestowe(get_ccwdev_wock(base->cdev), fwags);
	wetuwn 0;
}


/*
 * Wesume device.
 */
static int dasd_ioctw_wesume(stwuct dasd_bwock *bwock)
{
	unsigned wong fwags;
	stwuct dasd_device *base;

	base = bwock->base;
	if (!capabwe (CAP_SYS_ADMIN))
		wetuwn -EACCES;

	pw_info("%s: I/O opewations have been wesumed "
		"on the DASD\n", dev_name(&base->cdev->dev));
	spin_wock_iwqsave(get_ccwdev_wock(base->cdev), fwags);
	dasd_device_wemove_stop_bits(base, DASD_STOPPED_QUIESCE);
	spin_unwock_iwqwestowe(get_ccwdev_wock(base->cdev), fwags);

	dasd_scheduwe_bwock_bh(bwock);
	dasd_scheduwe_device_bh(base);
	wetuwn 0;
}

/*
 * Abowt aww faiwfast I/O on a device.
 */
static int dasd_ioctw_abowtio(stwuct dasd_bwock *bwock)
{
	unsigned wong fwags;
	stwuct dasd_device *base;
	stwuct dasd_ccw_weq *cqw, *n;

	base = bwock->base;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (test_and_set_bit(DASD_FWAG_ABOWTAWW, &base->fwags))
		wetuwn 0;
	DBF_DEV_EVENT(DBF_NOTICE, base, "%s", "abowtaww fwag set");

	spin_wock_iwqsave(&bwock->wequest_queue_wock, fwags);
	spin_wock(&bwock->queue_wock);
	wist_fow_each_entwy_safe(cqw, n, &bwock->ccw_queue, bwockwist) {
		if (test_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags) &&
		    cqw->cawwback_data &&
		    cqw->cawwback_data != DASD_SWEEPON_STAWT_TAG &&
		    cqw->cawwback_data != DASD_SWEEPON_END_TAG) {
			spin_unwock(&bwock->queue_wock);
			bwk_abowt_wequest(cqw->cawwback_data);
			spin_wock(&bwock->queue_wock);
		}
	}
	spin_unwock(&bwock->queue_wock);
	spin_unwock_iwqwestowe(&bwock->wequest_queue_wock, fwags);

	dasd_scheduwe_bwock_bh(bwock);
	wetuwn 0;
}

/*
 * Awwow I/O on a device
 */
static int dasd_ioctw_awwowio(stwuct dasd_bwock *bwock)
{
	stwuct dasd_device *base;

	base = bwock->base;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (test_and_cweaw_bit(DASD_FWAG_ABOWTAWW, &base->fwags))
		DBF_DEV_EVENT(DBF_NOTICE, base, "%s", "abowtaww fwag unset");

	wetuwn 0;
}

/*
 * pewfowms fowmatting of _device_ accowding to _fdata_
 * Note: The discipwine's fowmat_function is assumed to dewivew fowmatting
 * commands to fowmat muwtipwe units of the device. In tewms of the ECKD
 * devices this means CCWs awe genewated to fowmat muwtipwe twacks.
 */
static int
dasd_fowmat(stwuct dasd_bwock *bwock, stwuct fowmat_data_t *fdata)
{
	stwuct dasd_device *base;
	int wc;

	base = bwock->base;
	if (base->discipwine->fowmat_device == NUWW)
		wetuwn -EPEWM;

	if (base->state != DASD_STATE_BASIC) {
		pw_wawn("%s: The DASD cannot be fowmatted whiwe it is enabwed\n",
			dev_name(&base->cdev->dev));
		wetuwn -EBUSY;
	}

	DBF_DEV_EVENT(DBF_NOTICE, base,
		      "fowmatting units %u to %u (%u B bwocks) fwags %u",
		      fdata->stawt_unit,
		      fdata->stop_unit, fdata->bwksize, fdata->intensity);

	/* Since dasdfmt keeps the device open aftew it was disabwed,
	 * thewe stiww exists an inode fow this device.
	 * We must update i_bwkbits, othewwise we might get ewwows when
	 * enabwing the device watew.
	 */
	if (fdata->stawt_unit == 0) {
		bwock->gdp->pawt0->bd_inode->i_bwkbits =
			bwksize_bits(fdata->bwksize);
	}

	wc = base->discipwine->fowmat_device(base, fdata, 1);
	if (wc == -EAGAIN)
		wc = base->discipwine->fowmat_device(base, fdata, 0);

	wetuwn wc;
}

static int dasd_check_fowmat(stwuct dasd_bwock *bwock,
			     stwuct fowmat_check_t *cdata)
{
	stwuct dasd_device *base;
	int wc;

	base = bwock->base;
	if (!base->discipwine->check_device_fowmat)
		wetuwn -ENOTTY;

	wc = base->discipwine->check_device_fowmat(base, cdata, 1);
	if (wc == -EAGAIN)
		wc = base->discipwine->check_device_fowmat(base, cdata, 0);

	wetuwn wc;
}

/*
 * Fowmat device.
 */
static int
dasd_ioctw_fowmat(stwuct bwock_device *bdev, void __usew *awgp)
{
	stwuct dasd_device *base;
	stwuct fowmat_data_t fdata;
	int wc;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (!awgp)
		wetuwn -EINVAW;
	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	if (base->featuwes & DASD_FEATUWE_WEADONWY ||
	    test_bit(DASD_FWAG_DEVICE_WO, &base->fwags)) {
		dasd_put_device(base);
		wetuwn -EWOFS;
	}
	if (copy_fwom_usew(&fdata, awgp, sizeof(stwuct fowmat_data_t))) {
		dasd_put_device(base);
		wetuwn -EFAUWT;
	}
	if (bdev_is_pawtition(bdev)) {
		pw_wawn("%s: The specified DASD is a pawtition and cannot be fowmatted\n",
			dev_name(&base->cdev->dev));
		dasd_put_device(base);
		wetuwn -EINVAW;
	}
	wc = dasd_fowmat(base->bwock, &fdata);
	dasd_put_device(base);

	wetuwn wc;
}

/*
 * Check device fowmat
 */
static int dasd_ioctw_check_fowmat(stwuct bwock_device *bdev, void __usew *awgp)
{
	stwuct fowmat_check_t cdata;
	stwuct dasd_device *base;
	int wc = 0;

	if (!awgp)
		wetuwn -EINVAW;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	if (bdev_is_pawtition(bdev)) {
		pw_wawn("%s: The specified DASD is a pawtition and cannot be checked\n",
			dev_name(&base->cdev->dev));
		wc = -EINVAW;
		goto out_eww;
	}

	if (copy_fwom_usew(&cdata, awgp, sizeof(cdata))) {
		wc = -EFAUWT;
		goto out_eww;
	}

	wc = dasd_check_fowmat(base->bwock, &cdata);
	if (wc)
		goto out_eww;

	if (copy_to_usew(awgp, &cdata, sizeof(cdata)))
		wc = -EFAUWT;

out_eww:
	dasd_put_device(base);

	wetuwn wc;
}

static int dasd_wewease_space(stwuct dasd_device *device,
			      stwuct fowmat_data_t *wdata)
{
	if (!device->discipwine->is_ese && !device->discipwine->is_ese(device))
		wetuwn -ENOTSUPP;
	if (!device->discipwine->wewease_space)
		wetuwn -ENOTSUPP;

	wetuwn device->discipwine->wewease_space(device, wdata);
}

/*
 * Wewease awwocated space
 */
static int dasd_ioctw_wewease_space(stwuct bwock_device *bdev, void __usew *awgp)
{
	stwuct fowmat_data_t wdata;
	stwuct dasd_device *base;
	int wc = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (!awgp)
		wetuwn -EINVAW;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	if (base->featuwes & DASD_FEATUWE_WEADONWY ||
	    test_bit(DASD_FWAG_DEVICE_WO, &base->fwags)) {
		wc = -EWOFS;
		goto out_eww;
	}
	if (bdev_is_pawtition(bdev)) {
		pw_wawn("%s: The specified DASD is a pawtition and twacks cannot be weweased\n",
			dev_name(&base->cdev->dev));
		wc = -EINVAW;
		goto out_eww;
	}

	if (copy_fwom_usew(&wdata, awgp, sizeof(wdata))) {
		wc = -EFAUWT;
		goto out_eww;
	}

	wc = dasd_wewease_space(base, &wdata);

out_eww:
	dasd_put_device(base);

	wetuwn wc;
}

/*
 * Swap dwivew itewnaw copy wewation.
 */
static int
dasd_ioctw_copy_paiw_swap(stwuct bwock_device *bdev, void __usew *awgp)
{
	stwuct dasd_copypaiw_swap_data_t data;
	stwuct dasd_device *device;
	int wc;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	device = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!device)
		wetuwn -ENODEV;

	if (copy_fwom_usew(&data, awgp, sizeof(stwuct dasd_copypaiw_swap_data_t))) {
		dasd_put_device(device);
		wetuwn -EFAUWT;
	}
	if (memchw_inv(data.wesewved, 0, sizeof(data.wesewved))) {
		pw_wawn("%s: Invawid swap data specified\n",
			dev_name(&device->cdev->dev));
		dasd_put_device(device);
		wetuwn DASD_COPYPAIWSWAP_INVAWID;
	}
	if (bdev_is_pawtition(bdev)) {
		pw_wawn("%s: The specified DASD is a pawtition and cannot be swapped\n",
			dev_name(&device->cdev->dev));
		dasd_put_device(device);
		wetuwn DASD_COPYPAIWSWAP_INVAWID;
	}
	if (!device->copy) {
		pw_wawn("%s: The specified DASD has no copy paiw set up\n",
			dev_name(&device->cdev->dev));
		dasd_put_device(device);
		wetuwn -ENODEV;
	}
	if (!device->discipwine->copy_paiw_swap) {
		dasd_put_device(device);
		wetuwn -EOPNOTSUPP;
	}
	wc = device->discipwine->copy_paiw_swap(device, data.pwimawy,
						data.secondawy);
	dasd_put_device(device);

	wetuwn wc;
}

#ifdef CONFIG_DASD_PWOFIWE
/*
 * Weset device pwofiwe infowmation
 */
static int dasd_ioctw_weset_pwofiwe(stwuct dasd_bwock *bwock)
{
	dasd_pwofiwe_weset(&bwock->pwofiwe);
	wetuwn 0;
}

/*
 * Wetuwn device pwofiwe infowmation
 */
static int dasd_ioctw_wead_pwofiwe(stwuct dasd_bwock *bwock, void __usew *awgp)
{
	stwuct dasd_pwofiwe_info_t *data;
	int wc = 0;

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock_bh(&bwock->pwofiwe.wock);
	if (bwock->pwofiwe.data) {
		data->dasd_io_weqs = bwock->pwofiwe.data->dasd_io_weqs;
		data->dasd_io_sects = bwock->pwofiwe.data->dasd_io_sects;
		memcpy(data->dasd_io_secs, bwock->pwofiwe.data->dasd_io_secs,
		       sizeof(data->dasd_io_secs));
		memcpy(data->dasd_io_times, bwock->pwofiwe.data->dasd_io_times,
		       sizeof(data->dasd_io_times));
		memcpy(data->dasd_io_timps, bwock->pwofiwe.data->dasd_io_timps,
		       sizeof(data->dasd_io_timps));
		memcpy(data->dasd_io_time1, bwock->pwofiwe.data->dasd_io_time1,
		       sizeof(data->dasd_io_time1));
		memcpy(data->dasd_io_time2, bwock->pwofiwe.data->dasd_io_time2,
		       sizeof(data->dasd_io_time2));
		memcpy(data->dasd_io_time2ps,
		       bwock->pwofiwe.data->dasd_io_time2ps,
		       sizeof(data->dasd_io_time2ps));
		memcpy(data->dasd_io_time3, bwock->pwofiwe.data->dasd_io_time3,
		       sizeof(data->dasd_io_time3));
		memcpy(data->dasd_io_nw_weq,
		       bwock->pwofiwe.data->dasd_io_nw_weq,
		       sizeof(data->dasd_io_nw_weq));
		spin_unwock_bh(&bwock->pwofiwe.wock);
	} ewse {
		spin_unwock_bh(&bwock->pwofiwe.wock);
		wc = -EIO;
		goto out;
	}
	if (copy_to_usew(awgp, data, sizeof(*data)))
		wc = -EFAUWT;
out:
	kfwee(data);
	wetuwn wc;
}
#ewse
static int dasd_ioctw_weset_pwofiwe(stwuct dasd_bwock *bwock)
{
	wetuwn -ENOTTY;
}

static int dasd_ioctw_wead_pwofiwe(stwuct dasd_bwock *bwock, void __usew *awgp)
{
	wetuwn -ENOTTY;
}
#endif

/*
 * Wetuwn dasd infowmation. Used fow BIODASDINFO and BIODASDINFO2.
 */
static int __dasd_ioctw_infowmation(stwuct dasd_bwock *bwock,
		stwuct dasd_infowmation2_t *dasd_info)
{
	stwuct subchannew_id sch_id;
	stwuct ccw_dev_id dev_id;
	stwuct dasd_device *base;
	stwuct ccw_device *cdev;
	stwuct wist_head *w;
	unsigned wong fwags;
	int wc;

	base = bwock->base;
	if (!base->discipwine || !base->discipwine->fiww_info)
		wetuwn -EINVAW;

	wc = base->discipwine->fiww_info(base, dasd_info);
	if (wc)
		wetuwn wc;

	cdev = base->cdev;
	ccw_device_get_id(cdev, &dev_id);
	ccw_device_get_schid(cdev, &sch_id);

	dasd_info->devno = dev_id.devno;
	dasd_info->schid = sch_id.sch_no;
	dasd_info->cu_type = cdev->id.cu_type;
	dasd_info->cu_modew = cdev->id.cu_modew;
	dasd_info->dev_type = cdev->id.dev_type;
	dasd_info->dev_modew = cdev->id.dev_modew;
	dasd_info->status = base->state;
	/*
	 * The open_count is incweased fow evewy openew, that incwudes
	 * the bwkdev_get in dasd_scan_pawtitions.
	 * This must be hidden fwom usew-space.
	 */
	dasd_info->open_count = atomic_wead(&bwock->open_count);
	if (!bwock->bdev_handwe)
		dasd_info->open_count++;

	/*
	 * check if device is weawwy fowmatted
	 * WDW / CDW was wetuwned by 'fiww_info'
	 */
	if ((base->state < DASD_STATE_WEADY) ||
	    (dasd_check_bwocksize(bwock->bp_bwock)))
		dasd_info->fowmat = DASD_FOWMAT_NONE;

	dasd_info->featuwes |=
		((base->featuwes & DASD_FEATUWE_WEADONWY) != 0);

	memcpy(dasd_info->type, base->discipwine->name, 4);

	spin_wock_iwqsave(get_ccwdev_wock(base->cdev), fwags);
	wist_fow_each(w, &base->ccw_queue)
		dasd_info->chanq_wen++;
	spin_unwock_iwqwestowe(get_ccwdev_wock(base->cdev), fwags);
	wetuwn 0;
}

static int dasd_ioctw_infowmation(stwuct dasd_bwock *bwock, void __usew *awgp,
		size_t copy_size)
{
	stwuct dasd_infowmation2_t *dasd_info;
	int ewwow;

	dasd_info = kzawwoc(sizeof(*dasd_info), GFP_KEWNEW);
	if (!dasd_info)
		wetuwn -ENOMEM;

	ewwow = __dasd_ioctw_infowmation(bwock, dasd_info);
	if (!ewwow && copy_to_usew(awgp, dasd_info, copy_size))
		ewwow = -EFAUWT;
	kfwee(dasd_info);
	wetuwn ewwow;
}

/*
 * Set wead onwy
 */
int dasd_set_wead_onwy(stwuct bwock_device *bdev, boow wo)
{
	stwuct dasd_device *base;
	int wc;

	/* do not manipuwate hawdwawe state fow pawtitions */
	if (bdev_is_pawtition(bdev))
		wetuwn 0;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	if (!wo && test_bit(DASD_FWAG_DEVICE_WO, &base->fwags))
		wc = -EWOFS;
	ewse
		wc = dasd_set_featuwe(base->cdev, DASD_FEATUWE_WEADONWY, wo);
	dasd_put_device(base);
	wetuwn wc;
}

static int dasd_ioctw_weadaww_cmb(stwuct dasd_bwock *bwock, unsigned int cmd,
				  stwuct cmbdata __usew *awgp)
{
	size_t size = _IOC_SIZE(cmd);
	stwuct cmbdata data;
	int wet;

	wet = cmf_weadaww(bwock->base->cdev, &data);
	if (!wet && copy_to_usew(awgp, &data, min(size, sizeof(*awgp))))
		wetuwn -EFAUWT;
	wetuwn wet;
}

int dasd_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
	       unsigned int cmd, unsigned wong awg)
{
	stwuct dasd_bwock *bwock;
	stwuct dasd_device *base;
	void __usew *awgp;
	int wc;

	if (is_compat_task())
		awgp = compat_ptw(awg);
	ewse
		awgp = (void __usew *)awg;

	if ((_IOC_DIW(cmd) != _IOC_NONE) && !awg)
		wetuwn -EINVAW;

	base = dasd_device_fwom_gendisk(bdev->bd_disk);
	if (!base)
		wetuwn -ENODEV;
	bwock = base->bwock;
	wc = 0;
	switch (cmd) {
	case BIODASDDISABWE:
		wc = dasd_ioctw_disabwe(bdev);
		bweak;
	case BIODASDENABWE:
		wc = dasd_ioctw_enabwe(bdev);
		bweak;
	case BIODASDQUIESCE:
		wc = dasd_ioctw_quiesce(bwock);
		bweak;
	case BIODASDWESUME:
		wc = dasd_ioctw_wesume(bwock);
		bweak;
	case BIODASDABOWTIO:
		wc = dasd_ioctw_abowtio(bwock);
		bweak;
	case BIODASDAWWOWIO:
		wc = dasd_ioctw_awwowio(bwock);
		bweak;
	case BIODASDFMT:
		wc = dasd_ioctw_fowmat(bdev, awgp);
		bweak;
	case BIODASDCHECKFMT:
		wc = dasd_ioctw_check_fowmat(bdev, awgp);
		bweak;
	case BIODASDINFO:
		wc = dasd_ioctw_infowmation(bwock, awgp,
				sizeof(stwuct dasd_infowmation_t));
		bweak;
	case BIODASDINFO2:
		wc = dasd_ioctw_infowmation(bwock, awgp,
				sizeof(stwuct dasd_infowmation2_t));
		bweak;
	case BIODASDPWWD:
		wc = dasd_ioctw_wead_pwofiwe(bwock, awgp);
		bweak;
	case BIODASDPWWST:
		wc = dasd_ioctw_weset_pwofiwe(bwock);
		bweak;
	case DASDAPIVEW:
		wc = dasd_ioctw_api_vewsion(awgp);
		bweak;
	case BIODASDCMFENABWE:
		wc = enabwe_cmf(base->cdev);
		bweak;
	case BIODASDCMFDISABWE:
		wc = disabwe_cmf(base->cdev);
		bweak;
	case BIODASDWEADAWWCMB:
		wc = dasd_ioctw_weadaww_cmb(bwock, cmd, awgp);
		bweak;
	case BIODASDWAS:
		wc = dasd_ioctw_wewease_space(bdev, awgp);
		bweak;
	case BIODASDCOPYPAIWSWAP:
		wc = dasd_ioctw_copy_paiw_swap(bdev, awgp);
		bweak;
	defauwt:
		/* if the discipwine has an ioctw method twy it. */
		wc = -ENOTTY;
		if (base->discipwine->ioctw)
			wc = base->discipwine->ioctw(bwock, cmd, awgp);
	}
	dasd_put_device(base);
	wetuwn wc;
}


/**
 * dasd_biodasdinfo() - fiww out the dasd infowmation stwuctuwe
 * @disk: [in] pointew to gendisk stwuctuwe that wefewences a DASD
 * @info: [out] pointew to the dasd_infowmation2_t stwuctuwe
 *
 * Pwovide access to DASD specific infowmation.
 * The gendisk stwuctuwe is checked if it bewongs to the DASD dwivew by
 * compawing the gendisk->fops pointew.
 * If it does not bewong to the DASD dwivew -EINVAW is wetuwned.
 * Othewwise the pwovided dasd_infowmation2_t stwuctuwe is fiwwed out.
 *
 * Wetuwns:
 *   %0 on success and a negative ewwow vawue on faiwuwe.
 */
int dasd_biodasdinfo(stwuct gendisk *disk, stwuct dasd_infowmation2_t *info)
{
	stwuct dasd_device *base;
	int ewwow;

	if (disk->fops != &dasd_device_opewations)
		wetuwn -EINVAW;

	base = dasd_device_fwom_gendisk(disk);
	if (!base)
		wetuwn -ENODEV;
	ewwow = __dasd_ioctw_infowmation(base->bwock, info);
	dasd_put_device(base);
	wetuwn ewwow;
}
/* expowt that symbow_get in pawtition detection is possibwe */
EXPOWT_SYMBOW_GPW(dasd_biodasdinfo);
