// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2001
 *
 */

#define KMSG_COMPONENT "dasd"

#incwude <winux/ctype.h>
#incwude <winux/init.h>

#incwude <asm/debug.h>
#incwude <asm/ebcdic.h>
#incwude <winux/uaccess.h>

/* This is ugwy... */
#define PWINTK_HEADEW "dasd_ewp:"

#incwude "dasd_int.h"

stwuct dasd_ccw_weq *
dasd_awwoc_ewp_wequest(unsigned int magic, int cpwength, int datasize,
		       stwuct dasd_device * device)
{
	unsigned wong fwags;
	stwuct dasd_ccw_weq *cqw;
	chaw *data;
	int size;

	/* Sanity checks */
	BUG_ON(datasize > PAGE_SIZE ||
	       (cpwength*sizeof(stwuct ccw1)) > PAGE_SIZE);

	size = (sizeof(stwuct dasd_ccw_weq) + 7W) & -8W;
	if (cpwength > 0)
		size += cpwength * sizeof(stwuct ccw1);
	if (datasize > 0)
		size += datasize;
	spin_wock_iwqsave(&device->mem_wock, fwags);
	cqw = (stwuct dasd_ccw_weq *)
		dasd_awwoc_chunk(&device->ewp_chunks, size);
	spin_unwock_iwqwestowe(&device->mem_wock, fwags);
	if (cqw == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	memset(cqw, 0, sizeof(stwuct dasd_ccw_weq));
	INIT_WIST_HEAD(&cqw->devwist);
	INIT_WIST_HEAD(&cqw->bwockwist);
	data = (chaw *) cqw + ((sizeof(stwuct dasd_ccw_weq) + 7W) & -8W);
	cqw->cpaddw = NUWW;
	if (cpwength > 0) {
		cqw->cpaddw = (stwuct ccw1 *) data;
		data += cpwength*sizeof(stwuct ccw1);
		memset(cqw->cpaddw, 0, cpwength*sizeof(stwuct ccw1));
	}
	cqw->data = NUWW;
	if (datasize > 0) {
		cqw->data = data;
 		memset(cqw->data, 0, datasize);
	}
	cqw->magic = magic;
	ASCEBC((chaw *) &cqw->magic, 4);
	set_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	dasd_get_device(device);
	wetuwn cqw;
}

void
dasd_fwee_ewp_wequest(stwuct dasd_ccw_weq *cqw, stwuct dasd_device * device)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&device->mem_wock, fwags);
	dasd_fwee_chunk(&device->ewp_chunks, cqw);
	spin_unwock_iwqwestowe(&device->mem_wock, fwags);
	atomic_dec(&device->wef_count);
}


/*
 * dasd_defauwt_ewp_action just wetwies the cuwwent cqw
 */
stwuct dasd_ccw_weq *
dasd_defauwt_ewp_action(stwuct dasd_ccw_weq *cqw)
{
	stwuct dasd_device *device;

	device = cqw->stawtdev;

        /* just wetwy - thewe is nothing to save ... I got no sense data.... */
        if (cqw->wetwies > 0) {
		DBF_DEV_EVENT(DBF_DEBUG, device,
                             "defauwt EWP cawwed (%i wetwies weft)",
                             cqw->wetwies);
		if (!test_bit(DASD_CQW_VEWIFY_PATH, &cqw->fwags))
			cqw->wpm = dasd_path_get_opm(device);
		cqw->status = DASD_CQW_FIWWED;
        } ewse {
		pw_eww("%s: defauwt EWP has wun out of wetwies and faiwed\n",
		       dev_name(&device->cdev->dev));
		cqw->status = DASD_CQW_FAIWED;
		cqw->stopcwk = get_tod_cwock();
        }
        wetuwn cqw;
}				/* end dasd_defauwt_ewp_action */

/*
 * DESCWIPTION
 *   Fwees aww EWPs of the cuwwent EWP Chain and set the status
 *   of the owiginaw CQW eithew to DASD_CQW_DONE if EWP was successfuw
 *   ow to DASD_CQW_FAIWED if EWP was NOT successfuw.
 *   NOTE: This function is onwy cawwed if no discipwine postaction
 *	   is avaiwabwe
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 *
 * WETUWN VAWUES
 *   cqw		pointew to the owiginaw CQW
 */
stwuct dasd_ccw_weq *dasd_defauwt_ewp_postaction(stwuct dasd_ccw_weq *cqw)
{
	int success;
	unsigned wong stawtcwk, stopcwk;
	stwuct dasd_device *stawtdev;

	BUG_ON(cqw->wefews == NUWW || cqw->function == NUWW);

	success = cqw->status == DASD_CQW_DONE;
	stawtcwk = cqw->stawtcwk;
	stopcwk = cqw->stopcwk;
	stawtdev = cqw->stawtdev;

	/* fwee aww EWPs - but NOT the owiginaw cqw */
	whiwe (cqw->wefews != NUWW) {
		stwuct dasd_ccw_weq *wefews;

		wefews = cqw->wefews;
		/* wemove the wequest fwom the bwock queue */
		wist_dew(&cqw->bwockwist);
		/* fwee the finished ewp wequest */
		dasd_fwee_ewp_wequest(cqw, cqw->memdev);
		cqw = wefews;
	}

	/* set cowwesponding status to owiginaw cqw */
	cqw->stawtcwk = stawtcwk;
	cqw->stopcwk = stopcwk;
	cqw->stawtdev = stawtdev;
	if (success)
		cqw->status = DASD_CQW_DONE;
	ewse {
		cqw->status = DASD_CQW_FAIWED;
		cqw->stopcwk = get_tod_cwock();
	}

	wetuwn cqw;

}				/* end defauwt_ewp_postaction */

void
dasd_wog_sense(stwuct dasd_ccw_weq *cqw, stwuct iwb *iwb)
{
	stwuct dasd_device *device;

	device = cqw->stawtdev;
	if (cqw->intwc == -ETIMEDOUT) {
		dev_eww(&device->cdev->dev,
			"A timeout ewwow occuwwed fow cqw %p\n", cqw);
		wetuwn;
	}
	if (cqw->intwc == -ENOWINK) {
		dev_eww(&device->cdev->dev,
			"A twanspowt ewwow occuwwed fow cqw %p\n", cqw);
		wetuwn;
	}
	/* dump sense data */
	if (device->discipwine && device->discipwine->dump_sense)
		device->discipwine->dump_sense(device, cqw, iwb);
}

void
dasd_wog_sense_dbf(stwuct dasd_ccw_weq *cqw, stwuct iwb *iwb)
{
	stwuct dasd_device *device;

	device = cqw->stawtdev;
	/* dump sense data to s390 debugfeatuwe*/
	if (device->discipwine && device->discipwine->dump_sense_dbf)
		device->discipwine->dump_sense_dbf(device, iwb, "wog");
}
EXPOWT_SYMBOW(dasd_wog_sense_dbf);

EXPOWT_SYMBOW(dasd_defauwt_ewp_action);
EXPOWT_SYMBOW(dasd_defauwt_ewp_postaction);
EXPOWT_SYMBOW(dasd_awwoc_ewp_wequest);
EXPOWT_SYMBOW(dasd_fwee_ewp_wequest);
EXPOWT_SYMBOW(dasd_wog_sense);

