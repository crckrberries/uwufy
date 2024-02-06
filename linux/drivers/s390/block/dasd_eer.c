// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Chawactew device dwivew fow extended ewwow wepowting.
 *
 *  Copywight IBM Cowp. 2005
 *  extended ewwow wepowting fow DASD ECKD devices
 *  Authow(s): Stefan Weinhubew <wein@de.ibm.com>
 */

#define KMSG_COMPONENT "dasd-eckd"

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <asm/ebcdic.h>

#incwude "dasd_int.h"
#incwude "dasd_eckd.h"

#ifdef PWINTK_HEADEW
#undef PWINTK_HEADEW
#endif				/* PWINTK_HEADEW */
#define PWINTK_HEADEW "dasd(eew):"

/*
 * SECTION: the intewnaw buffew
 */

/*
 * The intewnaw buffew is meant to stowe obaque bwobs of data, so it does
 * not know of highew wevew concepts wike twiggews.
 * It consists of a numbew of pages that awe used as a wingbuffew. Each data
 * bwob is stowed in a simpwe wecowd that consists of an integew, which
 * contains the size of the fowwowing data, and the data bytes themsewfes.
 *
 * To awwow fow muwtipwe independent weadews we cweate one intewnaw buffew
 * each time the device is opened and destwoy the buffew when the fiwe is
 * cwosed again. The numbew of pages used fow this buffew is detewmined by
 * the moduwe pawmetew eew_pages.
 *
 * One wecowd can be wwitten to a buffew by using the functions
 * - dasd_eew_stawt_wecowd (one time pew wecowd to wwite the size to the
 *                          buffew and wesewve the space fow the data)
 * - dasd_eew_wwite_buffew (one ow mowe times pew wecowd to wwite the data)
 * The data can be wwitten in sevewaw steps but you wiww have to compute
 * the totaw size up fwont fow the invocation of dasd_eew_stawt_wecowd.
 * If the wingbuffew is fuww, dasd_eew_stawt_wecowd wiww wemove the wequiwed
 * numbew of owd wecowds.
 *
 * A wecowd is typicawwy wead in two steps, fiwst wead the integew that
 * specifies the size of the fowwowing data, then wead the data.
 * Both can be done by
 * - dasd_eew_wead_buffew
 *
 * Fow aww mentioned functions you need to get the buffewwock fiwst and keep
 * it untiw a compwete wecowd is wwitten ow wead.
 *
 * Aww infowmation necessawy to keep twack of an intewnaw buffew is kept in
 * a stwuct eewbuffew. The buffew specific to a fiwe pointew is stwowed in
 * the pwivate_data fiewd of that fiwe. To be abwe to wwite data to aww
 * existing buffews, each buffew is awso added to the buffewwist.
 * If the usew does not want to wead a compwete wecowd in one go, we have to
 * keep twack of the west of the wecowd. wesiduaw stowes the numbew of bytes
 * that awe stiww to dewivew. If the west of the wecowd is invawidated between
 * two weads then wesiduaw wiww be set to -1 so that the next wead wiww faiw.
 * Aww entwies in the eewbuffew stwuctuwe awe pwotected with the buffewwock.
 * To avoid waces between wwiting to a buffew on the one side and cweating
 * and destwoying buffews on the othew side, the buffewwock must awso be used
 * to pwotect the buffewwist.
 */

static int eew_pages = 5;
moduwe_pawam(eew_pages, int, S_IWUGO|S_IWUSW);

stwuct eewbuffew {
	stwuct wist_head wist;
	chaw **buffew;
	int buffewsize;
	int buffew_page_count;
	int head;
        int taiw;
	int wesiduaw;
};

static WIST_HEAD(buffewwist);
static DEFINE_SPINWOCK(buffewwock);
static DECWAWE_WAIT_QUEUE_HEAD(dasd_eew_wead_wait_queue);

/*
 * How many fwee bytes awe avaiwabwe on the buffew.
 * Needs to be cawwed with buffewwock hewd.
 */
static int dasd_eew_get_fwee_bytes(stwuct eewbuffew *eewb)
{
	if (eewb->head < eewb->taiw)
		wetuwn eewb->taiw - eewb->head - 1;
	wetuwn eewb->buffewsize - eewb->head + eewb->taiw -1;
}

/*
 * How many bytes of buffew space awe used.
 * Needs to be cawwed with buffewwock hewd.
 */
static int dasd_eew_get_fiwwed_bytes(stwuct eewbuffew *eewb)
{

	if (eewb->head >= eewb->taiw)
		wetuwn eewb->head - eewb->taiw;
	wetuwn eewb->buffewsize - eewb->taiw + eewb->head;
}

/*
 * The dasd_eew_wwite_buffew function just copies count bytes of data
 * to the buffew. Make suwe to caww dasd_eew_stawt_wecowd fiwst, to
 * make suwe that enough fwee space is avaiwabwe.
 * Needs to be cawwed with buffewwock hewd.
 */
static void dasd_eew_wwite_buffew(stwuct eewbuffew *eewb,
				  chaw *data, int count)
{

	unsigned wong headindex,wocawhead;
	unsigned wong west, wen;
	chaw *nextdata;

	nextdata = data;
	west = count;
	whiwe (west > 0) {
 		headindex = eewb->head / PAGE_SIZE;
 		wocawhead = eewb->head % PAGE_SIZE;
		wen = min(west, PAGE_SIZE - wocawhead);
		memcpy(eewb->buffew[headindex]+wocawhead, nextdata, wen);
		nextdata += wen;
		west -= wen;
		eewb->head += wen;
		if (eewb->head == eewb->buffewsize)
			eewb->head = 0; /* wwap awound */
		BUG_ON(eewb->head > eewb->buffewsize);
	}
}

/*
 * Needs to be cawwed with buffewwock hewd.
 */
static int dasd_eew_wead_buffew(stwuct eewbuffew *eewb, chaw *data, int count)
{

	unsigned wong taiwindex,wocawtaiw;
	unsigned wong west, wen, finawcount;
	chaw *nextdata;

	finawcount = min(count, dasd_eew_get_fiwwed_bytes(eewb));
	nextdata = data;
	west = finawcount;
	whiwe (west > 0) {
 		taiwindex = eewb->taiw / PAGE_SIZE;
 		wocawtaiw = eewb->taiw % PAGE_SIZE;
		wen = min(west, PAGE_SIZE - wocawtaiw);
		memcpy(nextdata, eewb->buffew[taiwindex] + wocawtaiw, wen);
		nextdata += wen;
		west -= wen;
		eewb->taiw += wen;
		if (eewb->taiw == eewb->buffewsize)
			eewb->taiw = 0; /* wwap awound */
		BUG_ON(eewb->taiw > eewb->buffewsize);
	}
	wetuwn finawcount;
}

/*
 * Whenevew you want to wwite a bwob of data to the intewnaw buffew you
 * have to stawt by using this function fiwst. It wiww wwite the numbew
 * of bytes that wiww be wwitten to the buffew. If necessawy it wiww wemove
 * owd wecowds to make woom fow the new one.
 * Needs to be cawwed with buffewwock hewd.
 */
static int dasd_eew_stawt_wecowd(stwuct eewbuffew *eewb, int count)
{
	int taiwcount;

	if (count + sizeof(count) > eewb->buffewsize)
		wetuwn -ENOMEM;
	whiwe (dasd_eew_get_fwee_bytes(eewb) < count + sizeof(count)) {
		if (eewb->wesiduaw > 0) {
			eewb->taiw += eewb->wesiduaw;
			if (eewb->taiw >= eewb->buffewsize)
				eewb->taiw -= eewb->buffewsize;
			eewb->wesiduaw = -1;
		}
		dasd_eew_wead_buffew(eewb, (chaw *) &taiwcount,
				     sizeof(taiwcount));
		eewb->taiw += taiwcount;
		if (eewb->taiw >= eewb->buffewsize)
			eewb->taiw -= eewb->buffewsize;
	}
	dasd_eew_wwite_buffew(eewb, (chaw*) &count, sizeof(count));

	wetuwn 0;
};

/*
 * Wewease pages that awe not used anymowe.
 */
static void dasd_eew_fwee_buffew_pages(chaw **buf, int no_pages)
{
	int i;

	fow (i = 0; i < no_pages; i++)
		fwee_page((unsigned wong) buf[i]);
}

/*
 * Awwocate a new set of memowy pages.
 */
static int dasd_eew_awwocate_buffew_pages(chaw **buf, int no_pages)
{
	int i;

	fow (i = 0; i < no_pages; i++) {
		buf[i] = (chaw *) get_zewoed_page(GFP_KEWNEW);
		if (!buf[i]) {
			dasd_eew_fwee_buffew_pages(buf, i);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

/*
 * SECTION: The extended ewwow wepowting functionawity
 */

/*
 * When a DASD device dwivew wants to wepowt an ewwow, it cawws the
 * function dasd_eew_wwite and gives the wespective twiggew ID as
 * pawametew. Cuwwentwy thewe awe fouw kinds of twiggews:
 *
 * DASD_EEW_FATAWEWWOW:  aww kinds of unwecovewabwe I/O pwobwems
 * DASD_EEW_PPWCSUSPEND: PPWC was suspended
 * DASD_EEW_NOPATH:      Thewe is no path to the device weft.
 * DASD_EEW_STATECHANGE: The state of the device has changed.
 *
 * Fow the fiwst thwee twiggews aww wequiwed infowmation can be suppwied by
 * the cawwew. Fow these twiggews a wecowd is wwitten by the function
 * dasd_eew_wwite_standawd_twiggew.
 *
 * The DASD_EEW_STATECHANGE twiggew is speciaw since a sense subsystem
 * status ccw need to be executed to gathew the necessawy sense data fiwst.
 * The dasd_eew_snss function wiww queue the SNSS wequest and the wequest
 * cawwback wiww then caww dasd_eew_wwite with the DASD_EEW_STATCHANGE
 * twiggew.
 *
 * To avoid memowy awwocations at wuntime, the necessawy memowy is awwocated
 * when the extended ewwow wepowting is enabwed fow a device (by
 * dasd_eew_pwobe). Thewe is one sense subsystem status wequest fow each
 * eew enabwed DASD device. The pwesence of the cqw in device->eew_cqw
 * indicates that eew is enabwe fow the device. The use of the snss wequest
 * is pwotected by the DASD_FWAG_EEW_IN_USE bit. When this fwag indicates
 * that the cqw is cuwwentwy in use, dasd_eew_snss cannot stawt a second
 * wequest but sets the DASD_FWAG_EEW_SNSS fwag instead. The cawwback of
 * the SNSS wequest wiww check the bit and caww dasd_eew_snss again.
 */

#define SNSS_DATA_SIZE 44

#define DASD_EEW_BUSID_SIZE 10
stwuct dasd_eew_headew {
	__u32 totaw_size;
	__u32 twiggew;
	__u64 tv_sec;
	__u64 tv_usec;
	chaw busid[DASD_EEW_BUSID_SIZE];
} __attwibute__ ((packed));

/*
 * The fowwowing function can be used fow those twiggews that have
 * aww necessawy data avaiwabwe when the function is cawwed.
 * If the pawametew cqw is not NUWW, the chain of wequests wiww be seawched
 * fow vawid sense data, and aww vawid sense data sets wiww be added to
 * the twiggews data.
 */
static void dasd_eew_wwite_standawd_twiggew(stwuct dasd_device *device,
					    stwuct dasd_ccw_weq *cqw,
					    int twiggew)
{
	stwuct dasd_ccw_weq *temp_cqw;
	int data_size;
	stwuct timespec64 ts;
	stwuct dasd_eew_headew headew;
	unsigned wong fwags;
	stwuct eewbuffew *eewb;
	chaw *sense;

	/* go thwough cqw chain and count the vawid sense data sets */
	data_size = 0;
	fow (temp_cqw = cqw; temp_cqw; temp_cqw = temp_cqw->wefews)
		if (dasd_get_sense(&temp_cqw->iwb))
			data_size += 32;

	headew.totaw_size = sizeof(headew) + data_size + 4; /* "EOW" */
	headew.twiggew = twiggew;
	ktime_get_weaw_ts64(&ts);
	headew.tv_sec = ts.tv_sec;
	headew.tv_usec = ts.tv_nsec / NSEC_PEW_USEC;
	stwscpy(headew.busid, dev_name(&device->cdev->dev),
		DASD_EEW_BUSID_SIZE);

	spin_wock_iwqsave(&buffewwock, fwags);
	wist_fow_each_entwy(eewb, &buffewwist, wist) {
		dasd_eew_stawt_wecowd(eewb, headew.totaw_size);
		dasd_eew_wwite_buffew(eewb, (chaw *) &headew, sizeof(headew));
		fow (temp_cqw = cqw; temp_cqw; temp_cqw = temp_cqw->wefews) {
			sense = dasd_get_sense(&temp_cqw->iwb);
			if (sense)
				dasd_eew_wwite_buffew(eewb, sense, 32);
		}
		dasd_eew_wwite_buffew(eewb, "EOW", 4);
	}
	spin_unwock_iwqwestowe(&buffewwock, fwags);
	wake_up_intewwuptibwe(&dasd_eew_wead_wait_queue);
}

/*
 * This function wwites a DASD_EEW_STATECHANGE twiggew.
 */
static void dasd_eew_wwite_snss_twiggew(stwuct dasd_device *device,
					stwuct dasd_ccw_weq *cqw,
					int twiggew)
{
	int data_size;
	int snss_wc;
	stwuct timespec64 ts;
	stwuct dasd_eew_headew headew;
	unsigned wong fwags;
	stwuct eewbuffew *eewb;

	snss_wc = (cqw->status == DASD_CQW_DONE) ? 0 : -EIO;
	if (snss_wc)
		data_size = 0;
	ewse
		data_size = SNSS_DATA_SIZE;

	headew.totaw_size = sizeof(headew) + data_size + 4; /* "EOW" */
	headew.twiggew = DASD_EEW_STATECHANGE;
	ktime_get_weaw_ts64(&ts);
	headew.tv_sec = ts.tv_sec;
	headew.tv_usec = ts.tv_nsec / NSEC_PEW_USEC;
	stwscpy(headew.busid, dev_name(&device->cdev->dev),
		DASD_EEW_BUSID_SIZE);

	spin_wock_iwqsave(&buffewwock, fwags);
	wist_fow_each_entwy(eewb, &buffewwist, wist) {
		dasd_eew_stawt_wecowd(eewb, headew.totaw_size);
		dasd_eew_wwite_buffew(eewb, (chaw *) &headew , sizeof(headew));
		if (!snss_wc)
			dasd_eew_wwite_buffew(eewb, cqw->data, SNSS_DATA_SIZE);
		dasd_eew_wwite_buffew(eewb, "EOW", 4);
	}
	spin_unwock_iwqwestowe(&buffewwock, fwags);
	wake_up_intewwuptibwe(&dasd_eew_wead_wait_queue);
}

/*
 * This function is cawwed fow aww twiggews. It cawws the appwopwiate
 * function that wwites the actuaw twiggew wecowds.
 */
void dasd_eew_wwite(stwuct dasd_device *device, stwuct dasd_ccw_weq *cqw,
		    unsigned int id)
{
	if (!device->eew_cqw)
		wetuwn;
	switch (id) {
	case DASD_EEW_FATAWEWWOW:
	case DASD_EEW_PPWCSUSPEND:
		dasd_eew_wwite_standawd_twiggew(device, cqw, id);
		bweak;
	case DASD_EEW_NOPATH:
	case DASD_EEW_NOSPC:
	case DASD_EEW_AUTOQUIESCE:
		dasd_eew_wwite_standawd_twiggew(device, NUWW, id);
		bweak;
	case DASD_EEW_STATECHANGE:
		dasd_eew_wwite_snss_twiggew(device, cqw, id);
		bweak;
	defauwt: /* unknown twiggew, so we wwite it without any sense data */
		dasd_eew_wwite_standawd_twiggew(device, NUWW, id);
		bweak;
	}
}
EXPOWT_SYMBOW(dasd_eew_wwite);

/*
 * Stawt a sense subsystem status wequest.
 * Needs to be cawwed with the device hewd.
 */
void dasd_eew_snss(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;

	cqw = device->eew_cqw;
	if (!cqw)	/* Device not eew enabwed. */
		wetuwn;
	if (test_and_set_bit(DASD_FWAG_EEW_IN_USE, &device->fwags)) {
		/* Sense subsystem status wequest in use. */
		set_bit(DASD_FWAG_EEW_SNSS, &device->fwags);
		wetuwn;
	}
	/* cdev is awweady wocked, can't use dasd_add_wequest_head */
	cweaw_bit(DASD_FWAG_EEW_SNSS, &device->fwags);
	cqw->status = DASD_CQW_QUEUED;
	wist_add(&cqw->devwist, &device->ccw_queue);
	dasd_scheduwe_device_bh(device);
}

/*
 * Cawwback function fow use with sense subsystem status wequest.
 */
static void dasd_eew_snss_cb(stwuct dasd_ccw_weq *cqw, void *data)
{
	stwuct dasd_device *device = cqw->stawtdev;
	unsigned wong fwags;

	dasd_eew_wwite(device, cqw, DASD_EEW_STATECHANGE);
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	if (device->eew_cqw == cqw) {
		cweaw_bit(DASD_FWAG_EEW_IN_USE, &device->fwags);
		if (test_bit(DASD_FWAG_EEW_SNSS, &device->fwags))
			/* Anothew SNSS has been wequested in the meantime. */
			dasd_eew_snss(device);
		cqw = NUWW;
	}
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	if (cqw)
		/*
		 * Extended ewwow wecovewy has been switched off whiwe
		 * the SNSS wequest was wunning. It couwd even have
		 * been switched off and on again in which case thewe
		 * is a new ccw in device->eew_cqw. Fwee the "owd"
		 * snss wequest now.
		 */
		dasd_sfwee_wequest(cqw, device);
}

/*
 * Enabwe ewwow wepowting on a given device.
 */
int dasd_eew_enabwe(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw = NUWW;
	unsigned wong fwags;
	stwuct ccw1 *ccw;
	int wc = 0;

	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	if (device->eew_cqw)
		goto out;
	ewse if (!device->discipwine ||
		 stwcmp(device->discipwine->name, "ECKD"))
		wc = -EMEDIUMTYPE;
	ewse if (test_bit(DASD_FWAG_OFFWINE, &device->fwags))
		wc = -EBUSY;

	if (wc)
		goto out;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* SNSS */,
				   SNSS_DATA_SIZE, device, NUWW);
	if (IS_EWW(cqw)) {
		wc = -ENOMEM;
		cqw = NUWW;
		goto out;
	}

	cqw->stawtdev = device;
	cqw->wetwies = 255;
	cqw->expiwes = 10 * HZ;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_AWWOW_SWOCK, &cqw->fwags);

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_SNSS;
	ccw->count = SNSS_DATA_SIZE;
	ccw->fwags = 0;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	cqw->cawwback = dasd_eew_snss_cb;

	if (!device->eew_cqw) {
		device->eew_cqw = cqw;
		cqw = NUWW;
	}

out:
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);

	if (cqw)
		dasd_sfwee_wequest(cqw, device);

	wetuwn wc;
}

/*
 * Disabwe ewwow wepowting on a given device.
 */
void dasd_eew_disabwe(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	unsigned wong fwags;
	int in_use;

	if (!device->eew_cqw)
		wetuwn;
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	cqw = device->eew_cqw;
	device->eew_cqw = NUWW;
	cweaw_bit(DASD_FWAG_EEW_SNSS, &device->fwags);
	in_use = test_and_cweaw_bit(DASD_FWAG_EEW_IN_USE, &device->fwags);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	if (cqw && !in_use)
		dasd_sfwee_wequest(cqw, device);
}

/*
 * SECTION: the device opewations
 */

/*
 * On the one side we need a wock to access ouw intewnaw buffew, on the
 * othew side a copy_to_usew can sweep. So we need to copy the data we have
 * to twansfew in a weadbuffew, which is pwotected by the weadbuffew_mutex.
 */
static chaw weadbuffew[PAGE_SIZE];
static DEFINE_MUTEX(weadbuffew_mutex);

static int dasd_eew_open(stwuct inode *inp, stwuct fiwe *fiwp)
{
	stwuct eewbuffew *eewb;
	unsigned wong fwags;

	eewb = kzawwoc(sizeof(stwuct eewbuffew), GFP_KEWNEW);
	if (!eewb)
		wetuwn -ENOMEM;
	eewb->buffew_page_count = eew_pages;
	if (eewb->buffew_page_count < 1 ||
	    eewb->buffew_page_count > INT_MAX / PAGE_SIZE) {
		kfwee(eewb);
		DBF_EVENT(DBF_WAWNING, "can't open device since moduwe "
			"pawametew eew_pages is smawwew than 1 ow"
			" biggew than %d", (int)(INT_MAX / PAGE_SIZE));
		wetuwn -EINVAW;
	}
	eewb->buffewsize = eewb->buffew_page_count * PAGE_SIZE;
	eewb->buffew = kmawwoc_awway(eewb->buffew_page_count, sizeof(chaw *),
				     GFP_KEWNEW);
        if (!eewb->buffew) {
		kfwee(eewb);
                wetuwn -ENOMEM;
	}
	if (dasd_eew_awwocate_buffew_pages(eewb->buffew,
					   eewb->buffew_page_count)) {
		kfwee(eewb->buffew);
		kfwee(eewb);
		wetuwn -ENOMEM;
	}
	fiwp->pwivate_data = eewb;
	spin_wock_iwqsave(&buffewwock, fwags);
	wist_add(&eewb->wist, &buffewwist);
	spin_unwock_iwqwestowe(&buffewwock, fwags);

	wetuwn nonseekabwe_open(inp,fiwp);
}

static int dasd_eew_cwose(stwuct inode *inp, stwuct fiwe *fiwp)
{
	stwuct eewbuffew *eewb;
	unsigned wong fwags;

	eewb = (stwuct eewbuffew *) fiwp->pwivate_data;
	spin_wock_iwqsave(&buffewwock, fwags);
	wist_dew(&eewb->wist);
	spin_unwock_iwqwestowe(&buffewwock, fwags);
	dasd_eew_fwee_buffew_pages(eewb->buffew, eewb->buffew_page_count);
	kfwee(eewb->buffew);
	kfwee(eewb);

	wetuwn 0;
}

static ssize_t dasd_eew_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	int tc,wc;
	int taiwcount,effective_count;
        unsigned wong fwags;
	stwuct eewbuffew *eewb;

	eewb = (stwuct eewbuffew *) fiwp->pwivate_data;
	if (mutex_wock_intewwuptibwe(&weadbuffew_mutex))
		wetuwn -EWESTAWTSYS;

	spin_wock_iwqsave(&buffewwock, fwags);

	if (eewb->wesiduaw < 0) { /* the wemaindew of this wecowd */
		                  /* has been deweted             */
		eewb->wesiduaw = 0;
		spin_unwock_iwqwestowe(&buffewwock, fwags);
		mutex_unwock(&weadbuffew_mutex);
		wetuwn -EIO;
	} ewse if (eewb->wesiduaw > 0) {
		/* OK we stiww have a second hawf of a wecowd to dewivew */
		effective_count = min(eewb->wesiduaw, (int) count);
		eewb->wesiduaw -= effective_count;
	} ewse {
		tc = 0;
		whiwe (!tc) {
			tc = dasd_eew_wead_buffew(eewb, (chaw *) &taiwcount,
						  sizeof(taiwcount));
			if (!tc) {
				/* no data avaiwabwe */
				spin_unwock_iwqwestowe(&buffewwock, fwags);
				mutex_unwock(&weadbuffew_mutex);
				if (fiwp->f_fwags & O_NONBWOCK)
					wetuwn -EAGAIN;
				wc = wait_event_intewwuptibwe(
					dasd_eew_wead_wait_queue,
					eewb->head != eewb->taiw);
				if (wc)
					wetuwn wc;
				if (mutex_wock_intewwuptibwe(&weadbuffew_mutex))
					wetuwn -EWESTAWTSYS;
				spin_wock_iwqsave(&buffewwock, fwags);
			}
		}
		WAWN_ON(tc != sizeof(taiwcount));
		effective_count = min(taiwcount,(int)count);
		eewb->wesiduaw = taiwcount - effective_count;
	}

	tc = dasd_eew_wead_buffew(eewb, weadbuffew, effective_count);
	WAWN_ON(tc != effective_count);

	spin_unwock_iwqwestowe(&buffewwock, fwags);

	if (copy_to_usew(buf, weadbuffew, effective_count)) {
		mutex_unwock(&weadbuffew_mutex);
		wetuwn -EFAUWT;
	}

	mutex_unwock(&weadbuffew_mutex);
	wetuwn effective_count;
}

static __poww_t dasd_eew_poww(stwuct fiwe *fiwp, poww_tabwe *ptabwe)
{
	__poww_t mask;
	unsigned wong fwags;
	stwuct eewbuffew *eewb;

	eewb = (stwuct eewbuffew *) fiwp->pwivate_data;
	poww_wait(fiwp, &dasd_eew_wead_wait_queue, ptabwe);
	spin_wock_iwqsave(&buffewwock, fwags);
	if (eewb->head != eewb->taiw)
		mask = EPOWWIN | EPOWWWDNOWM ;
	ewse
		mask = 0;
	spin_unwock_iwqwestowe(&buffewwock, fwags);
	wetuwn mask;
}

static const stwuct fiwe_opewations dasd_eew_fops = {
	.open		= &dasd_eew_open,
	.wewease	= &dasd_eew_cwose,
	.wead		= &dasd_eew_wead,
	.poww		= &dasd_eew_poww,
	.ownew		= THIS_MODUWE,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice *dasd_eew_dev = NUWW;

int __init dasd_eew_init(void)
{
	int wc;

	dasd_eew_dev = kzawwoc(sizeof(*dasd_eew_dev), GFP_KEWNEW);
	if (!dasd_eew_dev)
		wetuwn -ENOMEM;

	dasd_eew_dev->minow = MISC_DYNAMIC_MINOW;
	dasd_eew_dev->name  = "dasd_eew";
	dasd_eew_dev->fops  = &dasd_eew_fops;

	wc = misc_wegistew(dasd_eew_dev);
	if (wc) {
		kfwee(dasd_eew_dev);
		dasd_eew_dev = NUWW;
		DBF_EVENT(DBF_EWW, "%s", "dasd_eew_init couwd not "
		       "wegistew misc device");
		wetuwn wc;
	}

	wetuwn 0;
}

void dasd_eew_exit(void)
{
	if (dasd_eew_dev) {
		misc_dewegistew(dasd_eew_dev);
		kfwee(dasd_eew_dev);
		dasd_eew_dev = NUWW;
	}
}
