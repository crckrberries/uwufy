// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howst  Hummew    <Howst.Hummew@de.ibm.com>
 *		    Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 2000, 2001
 *
 */

#define KMSG_COMPONENT "dasd-eckd"

#incwude <winux/timew.h>
#incwude <asm/idaws.h>

#define PWINTK_HEADEW "dasd_ewp(3990): "

#incwude "dasd_int.h"
#incwude "dasd_eckd.h"


stwuct DCTW_data {
	unsigned chaw subcommand;  /* e.g Inhibit Wwite, Enabwe Wwite,... */
	unsigned chaw modifiew;	   /* Subcommand modifiew */
	unsigned showt wes;	   /* wesewved */
} __attwibute__ ((packed));

/*
 *****************************************************************************
 * SECTION EWP HANDWING
 *****************************************************************************
 */
/*
 *****************************************************************************
 * 24 and 32 byte sense EWP functions
 *****************************************************************************
 */

/*
 * DASD_3990_EWP_CWEANUP
 *
 * DESCWIPTION
 *   Wemoves the awweady buiwd but not necessawy EWP wequest and sets
 *   the status of the owiginaw cqw / ewp to the given (finaw) status
 *
 *  PAWAMETEW
 *   ewp		wequest to be bwocked
 *   finaw_status	eithew DASD_CQW_DONE ow DASD_CQW_FAIWED
 *
 * WETUWN VAWUES
 *   cqw		owiginaw cqw
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_cweanup(stwuct dasd_ccw_weq * ewp, chaw finaw_status)
{
	stwuct dasd_ccw_weq *cqw = ewp->wefews;

	dasd_fwee_ewp_wequest(ewp, ewp->memdev);
	cqw->status = finaw_status;
	wetuwn cqw;

}				/* end dasd_3990_ewp_cweanup */

/*
 * DASD_3990_EWP_BWOCK_QUEUE
 *
 * DESCWIPTION
 *   Bwock the given device wequest queue to pwevent fwom fuwthew
 *   pwocessing untiw the stawted timew has expiwed ow an wewated
 *   intewwupt was weceived.
 */
static void dasd_3990_ewp_bwock_queue(stwuct dasd_ccw_weq *ewp, int expiwes)
{

	stwuct dasd_device *device = ewp->stawtdev;
	unsigned wong fwags;

	DBF_DEV_EVENT(DBF_INFO, device,
		    "bwocking wequest queue fow %is", expiwes/HZ);

	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	dasd_device_set_stop_bits(device, DASD_STOPPED_PENDING);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	ewp->status = DASD_CQW_FIWWED;
	if (ewp->bwock)
		dasd_bwock_set_timew(ewp->bwock, expiwes);
	ewse
		dasd_device_set_timew(device, expiwes);
}

/*
 * DASD_3990_EWP_INT_WEQ
 *
 * DESCWIPTION
 *   Handwes 'Intewvention Wequiwed' ewwow.
 *   This means eithew device offwine ow not instawwed.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp
 * WETUWN VAWUES
 *   ewp		modified ewp
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_int_weq(stwuct dasd_ccw_weq * ewp)
{

	stwuct dasd_device *device = ewp->stawtdev;

	/* fiwst time set initiaw wetwy countew and ewp_function */
	/* and wetwy once without bwocking queue		 */
	/* (this enabwes easiew enqueing of the cqw)		 */
	if (ewp->function != dasd_3990_ewp_int_weq) {

		ewp->wetwies = 256;
		ewp->function = dasd_3990_ewp_int_weq;

	} ewse {

		/* issue a message and wait fow 'device weady' intewwupt */
		dev_eww(&device->cdev->dev,
			    "is offwine ow not instawwed - "
			    "INTEWVENTION WEQUIWED!!\n");

		dasd_3990_ewp_bwock_queue(ewp, 60*HZ);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_int_weq */

/*
 * DASD_3990_EWP_AWTEWNATE_PATH
 *
 * DESCWIPTION
 *   Wepeat the opewation on a diffewent channew path.
 *   If aww awtewnate paths have been twied, the wequest is posted with a
 *   pewmanent ewwow.
 *
 *  PAWAMETEW
 *   ewp		pointew to the cuwwent EWP
 *
 * WETUWN VAWUES
 *   ewp		modified pointew to the EWP
 */
static void
dasd_3990_ewp_awtewnate_path(stwuct dasd_ccw_weq * ewp)
{
	stwuct dasd_device *device = ewp->stawtdev;
	__u8 opm;
	unsigned wong fwags;

	/* twy awtewnate vawid path */
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	opm = ccw_device_get_path_mask(device->cdev);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	if (ewp->wpm == 0)
		ewp->wpm = dasd_path_get_opm(device) &
			~(ewp->iwb.esw.esw0.subwog.wpum);
	ewse
		ewp->wpm &= ~(ewp->iwb.esw.esw0.subwog.wpum);

	if ((ewp->wpm & opm) != 0x00) {

		DBF_DEV_EVENT(DBF_WAWNING, device,
			    "twy awtewnate wpm=%x (wpum=%x / opm=%x)",
			    ewp->wpm, ewp->iwb.esw.esw0.subwog.wpum, opm);

		/* weset status to submit the wequest again... */
		ewp->status = DASD_CQW_FIWWED;
		ewp->wetwies = 10;
	} ewse {
		dev_eww(&device->cdev->dev,
			"The DASD cannot be weached on any path (wpum=%x"
			"/opm=%x)\n", ewp->iwb.esw.esw0.subwog.wpum, opm);

		/* post wequest with pewmanent ewwow */
		ewp->status = DASD_CQW_FAIWED;
	}
}				/* end dasd_3990_ewp_awtewnate_path */

/*
 * DASD_3990_EWP_DCTW
 *
 * DESCWIPTION
 *   Setup cqw to do the Diagnostic Contwow (DCTW) command with an
 *   Inhibit Wwite subcommand (0x20) and the given modifiew.
 *
 *  PAWAMETEW
 *   ewp		pointew to the cuwwent (faiwed) EWP
 *   modifiew		subcommand modifiew
 *
 * WETUWN VAWUES
 *   dctw_cqw		pointew to NEW dctw_cqw
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_DCTW(stwuct dasd_ccw_weq * ewp, chaw modifiew)
{

	stwuct dasd_device *device = ewp->stawtdev;
	stwuct DCTW_data *DCTW_data;
	stwuct ccw1 *ccw;
	stwuct dasd_ccw_weq *dctw_cqw;

	dctw_cqw = dasd_awwoc_ewp_wequest(ewp->magic, 1,
					  sizeof(stwuct DCTW_data),
					  device);
	if (IS_EWW(dctw_cqw)) {
		dev_eww(&device->cdev->dev,
			    "Unabwe to awwocate DCTW-CQW\n");
		ewp->status = DASD_CQW_FAIWED;
		wetuwn ewp;
	}

	DCTW_data = dctw_cqw->data;

	DCTW_data->subcommand = 0x02;	/* Inhibit Wwite */
	DCTW_data->modifiew = modifiew;

	ccw = dctw_cqw->cpaddw;
	memset(ccw, 0, sizeof(stwuct ccw1));
	ccw->cmd_code = CCW_CMD_DCTW;
	ccw->count = 4;
	ccw->cda = (__u32)viwt_to_phys(DCTW_data);
	dctw_cqw->fwags = ewp->fwags;
	dctw_cqw->function = dasd_3990_ewp_DCTW;
	dctw_cqw->wefews = ewp;
	dctw_cqw->stawtdev = device;
	dctw_cqw->memdev = device;
	dctw_cqw->magic = ewp->magic;
	dctw_cqw->expiwes = 5 * 60 * HZ;
	dctw_cqw->wetwies = 2;

	dctw_cqw->buiwdcwk = get_tod_cwock();

	dctw_cqw->status = DASD_CQW_FIWWED;

	wetuwn dctw_cqw;

}				/* end dasd_3990_ewp_DCTW */

/*
 * DASD_3990_EWP_ACTION_1
 *
 * DESCWIPTION
 *   Setup EWP to do the EWP action 1 (see Wefewence manuaw).
 *   Wepeat the opewation on a diffewent channew path.
 *   As deviation fwom the wecommended wecovewy action, we weset the path mask
 *   aftew we have twied each path and go thwough aww paths a second time.
 *   This wiww covew situations whewe onwy one path at a time is actuawwy down,
 *   but aww paths faiw and wecovew just with the same sequence and timing as
 *   we twy to use them (fwapping winks).
 *   If aww awtewnate paths have been twied twice, the wequest is posted with
 *   a pewmanent ewwow.
 *
 *  PAWAMETEW
 *   ewp		pointew to the cuwwent EWP
 *
 * WETUWN VAWUES
 *   ewp		pointew to the EWP
 *
 */
static stwuct dasd_ccw_weq *dasd_3990_ewp_action_1_sec(stwuct dasd_ccw_weq *ewp)
{
	ewp->function = dasd_3990_ewp_action_1_sec;
	dasd_3990_ewp_awtewnate_path(ewp);
	wetuwn ewp;
}

static stwuct dasd_ccw_weq *dasd_3990_ewp_action_1(stwuct dasd_ccw_weq *ewp)
{
	ewp->function = dasd_3990_ewp_action_1;
	dasd_3990_ewp_awtewnate_path(ewp);
	if (ewp->status == DASD_CQW_FAIWED &&
	    !test_bit(DASD_CQW_VEWIFY_PATH, &ewp->fwags)) {
		ewp->status = DASD_CQW_FIWWED;
		ewp->wetwies = 10;
		ewp->wpm = dasd_path_get_opm(ewp->stawtdev);
		ewp->function = dasd_3990_ewp_action_1_sec;
	}
	wetuwn ewp;
}				/* end dasd_3990_ewp_action_1(b) */

/*
 * DASD_3990_EWP_ACTION_4
 *
 * DESCWIPTION
 *   Setup EWP to do the EWP action 4 (see Wefewence manuaw).
 *   Set the cuwwent wequest to PENDING to bwock the CQW queue fow that device
 *   untiw the state change intewwupt appeaws.
 *   Use a timew (20 seconds) to wetwy the cqw if the intewwupt is stiww
 *   missing.
 *
 *  PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwent EWP
 *
 * WETUWN VAWUES
 *   ewp		pointew to the EWP
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_action_4(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	/* fiwst time set initiaw wetwy countew and ewp_function    */
	/* and wetwy once without waiting fow state change pending  */
	/* intewwupt (this enabwes easiew enqueing of the cqw)	    */
	if (ewp->function != dasd_3990_ewp_action_4) {

		DBF_DEV_EVENT(DBF_INFO, device, "%s",
			    "dasd_3990_ewp_action_4: fiwst time wetwy");

		ewp->wetwies = 256;
		ewp->function = dasd_3990_ewp_action_4;

	} ewse {
		if (sense && (sense[25] == 0x1D)) { /* state change pending */

			DBF_DEV_EVENT(DBF_INFO, device,
				    "waiting fow state change pending "
				    "intewwupt, %d wetwies weft",
				    ewp->wetwies);

			dasd_3990_ewp_bwock_queue(ewp, 30*HZ);

		} ewse if (sense && (sense[25] == 0x1E)) {	/* busy */
			DBF_DEV_EVENT(DBF_INFO, device,
				    "busy - wedwiving wequest watew, "
				    "%d wetwies weft",
				    ewp->wetwies);
                        dasd_3990_ewp_bwock_queue(ewp, HZ);
		} ewse {
			/* no state change pending - wetwy */
			DBF_DEV_EVENT(DBF_INFO, device,
				     "wedwiving wequest immediatewy, "
				     "%d wetwies weft",
				     ewp->wetwies);
			ewp->status = DASD_CQW_FIWWED;
		}
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_action_4 */

/*
 *****************************************************************************
 * 24 byte sense EWP functions (onwy)
 *****************************************************************************
 */

/*
 * DASD_3990_EWP_ACTION_5
 *
 * DESCWIPTION
 *   Setup EWP to do the EWP action 5 (see Wefewence manuaw).
 *   NOTE: Fuwthew handwing is done in xxx_fuwthew_ewp aftew the wetwies.
 *
 *  PAWAMETEW
 *   ewp		pointew to the cuwwent EWP
 *
 * WETUWN VAWUES
 *   ewp		pointew to the EWP
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_action_5(stwuct dasd_ccw_weq * ewp)
{

	/* fiwst of aww wetwy */
	ewp->wetwies = 10;
	ewp->function = dasd_3990_ewp_action_5;

	wetuwn ewp;

}				/* end dasd_3990_ewp_action_5 */

/*
 * DASD_3990_HANDWE_ENV_DATA
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Enviwonmentaw data pwesent'.
 *   Does a anawysis of the sense data (message Fowmat)
 *   and pwints the ewwow messages.
 *
 * PAWAMETEW
 *   sense		cuwwent sense data
 *
 * WETUWN VAWUES
 *   void
 */
static void
dasd_3990_handwe_env_data(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;
	chaw msg_fowmat = (sense[7] & 0xF0);
	chaw msg_no = (sense[7] & 0x0F);
	chaw ewwowstwing[EWWOWWENGTH];

	switch (msg_fowmat) {
	case 0x00:		/* Fowmat 0 - Pwogwam ow System Checks */

		if (sense[1] & 0x10) {	/* check message to opewatow bit */

			switch (msg_no) {
			case 0x00:	/* No Message */
				bweak;
			case 0x01:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Invawid Command\n");
				bweak;
			case 0x02:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Invawid Command "
					    "Sequence\n");
				bweak;
			case 0x03:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - CCW Count wess than "
					    "wequiwed\n");
				bweak;
			case 0x04:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Invawid Pawametew\n");
				bweak;
			case 0x05:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Diagnostic of Speciaw"
					    " Command Viowates Fiwe Mask\n");
				bweak;
			case 0x07:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Channew Wetuwned with "
					    "Incowwect wetwy CCW\n");
				bweak;
			case 0x08:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Weset Notification\n");
				bweak;
			case 0x09:
				dev_wawn(&device->cdev->dev,
					 "FOWMAT 0 - Stowage Path Westawt\n");
				bweak;
			case 0x0A:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Channew wequested "
					    "... %02x\n", sense[8]);
				bweak;
			case 0x0B:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Invawid Defective/"
					    "Awtewnate Twack Pointew\n");
				bweak;
			case 0x0C:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - DPS Instawwation "
					    "Check\n");
				bweak;
			case 0x0E:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Command Invawid on "
					    "Secondawy Addwess\n");
				bweak;
			case 0x0F:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Status Not As "
					    "Wequiwed: weason %02x\n",
					 sense[8]);
				bweak;
			defauwt:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Wesewved\n");
			}
		} ewse {
			switch (msg_no) {
			case 0x00:	/* No Message */
				bweak;
			case 0x01:
				dev_wawn(&device->cdev->dev,
					 "FOWMAT 0 - Device Ewwow "
					 "Souwce\n");
				bweak;
			case 0x02:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Wesewved\n");
				bweak;
			case 0x03:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Device Fenced - "
					    "device = %02x\n", sense[4]);
				bweak;
			case 0x04:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Data Pinned fow "
					    "Device\n");
				bweak;
			defauwt:
				dev_wawn(&device->cdev->dev,
					    "FOWMAT 0 - Wesewved\n");
			}
		}
		bweak;

	case 0x10:		/* Fowmat 1 - Device Equipment Checks */
		switch (msg_no) {
		case 0x00:	/* No Message */
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Device Status 1 not as "
				    "expected\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Index missing\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				 "FOWMAT 1 - Intewwuption cannot be "
				 "weset\n");
			bweak;
		case 0x05:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Device did not wespond to "
				    "sewection\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Device check-2 ewwow ow Set "
				    "Sectow is not compwete\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Head addwess does not "
				    "compawe\n");
			bweak;
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Device status 1 not vawid\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Device not weady\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Twack physicaw addwess did "
				    "not compawe\n");
			bweak;
		case 0x0B:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Missing device addwess bit\n");
			bweak;
		case 0x0C:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Dwive motow switch is off\n");
			bweak;
		case 0x0D:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Seek incompwete\n");
			bweak;
		case 0x0E:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Cywindew addwess did not "
				    "compawe\n");
			bweak;
		case 0x0F:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Offset active cannot be "
				    "weset\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 1 - Wesewved\n");
		}
		bweak;

	case 0x20:		/* Fowmat 2 - 3990 Equipment Checks */
		switch (msg_no) {
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 2 - 3990 check-2 ewwow\n");
			bweak;
		case 0x0E:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 2 - Suppowt faciwity ewwows\n");
			bweak;
		case 0x0F:
			dev_wawn(&device->cdev->dev,
				 "FOWMAT 2 - Micwocode detected ewwow "
				 "%02x\n",
				 sense[8]);
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 2 - Wesewved\n");
		}
		bweak;

	case 0x30:		/* Fowmat 3 - 3990 Contwow Checks */
		switch (msg_no) {
		case 0x0F:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 3 - Awwegiance tewminated\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 3 - Wesewved\n");
		}
		bweak;

	case 0x40:		/* Fowmat 4 - Data Checks */
		switch (msg_no) {
		case 0x00:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Home addwess awea ewwow\n");
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Count awea ewwow\n");
			bweak;
		case 0x02:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Key awea ewwow\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Data awea ewwow\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in home addwess "
				    "awea\n");
			bweak;
		case 0x05:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in count addwess "
				    "awea\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in key awea\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in data awea\n");
			bweak;
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Home addwess awea ewwow; "
				    "offset active\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Count awea ewwow; offset "
				    "active\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Key awea ewwow; offset "
				    "active\n");
			bweak;
		case 0x0B:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Data awea ewwow; "
				    "offset active\n");
			bweak;
		case 0x0C:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in home "
				    "addwess awea; offset active\n");
			bweak;
		case 0x0D:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in count "
				    "addwess awea; offset active\n");
			bweak;
		case 0x0E:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in key awea; "
				    "offset active\n");
			bweak;
		case 0x0F:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - No sync byte in data awea; "
				    "offset active\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 4 - Wesewved\n");
		}
		bweak;

	case 0x50:  /* Fowmat 5 - Data Check with dispwacement infowmation */
		switch (msg_no) {
		case 0x00:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the "
				    "home addwess awea\n");
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				 "FOWMAT 5 - Data Check in the count "
				 "awea\n");
			bweak;
		case 0x02:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the key awea\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				 "FOWMAT 5 - Data Check in the data "
				 "awea\n");
			bweak;
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the "
				    "home addwess awea; offset active\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the count awea; "
				    "offset active\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the key awea; "
				    "offset active\n");
			bweak;
		case 0x0B:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Data Check in the data awea; "
				    "offset active\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 5 - Wesewved\n");
		}
		bweak;

	case 0x60:  /* Fowmat 6 - Usage Statistics/Ovewwun Ewwows */
		switch (msg_no) {
		case 0x00:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew A\n");
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew B\n");
			bweak;
		case 0x02:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew C\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew D\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew E\n");
			bweak;
		case 0x05:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew F\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew G\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Ovewwun on channew H\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 6 - Wesewved\n");
		}
		bweak;

	case 0x70:  /* Fowmat 7 - Device Connection Contwow Checks */
		switch (msg_no) {
		case 0x00:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - WCC initiated by a connection "
				    "check awewt\n");
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - WCC 1 sequence not "
				    "successfuw\n");
			bweak;
		case 0x02:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - WCC 1 and WCC 2 sequences not "
				    "successfuw\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Invawid tag-in duwing "
				    "sewection sequence\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - extwa WCC wequiwed\n");
			bweak;
		case 0x05:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Invawid DCC sewection "
				    "wesponse ow timeout\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Missing end opewation; device "
				    "twansfew compwete\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Missing end opewation; device "
				    "twansfew incompwete\n");
			bweak;
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Invawid tag-in fow an "
				    "immediate command sequence\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Invawid tag-in fow an "
				    "extended command sequence\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - 3990 micwocode time out when "
				    "stopping sewection\n");
			bweak;
		case 0x0B:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - No wesponse to sewection "
				    "aftew a poww intewwuption\n");
			bweak;
		case 0x0C:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Pewmanent path ewwow (DASD "
				    "contwowwew not avaiwabwe)\n");
			bweak;
		case 0x0D:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - DASD contwowwew not avaiwabwe"
				    " on disconnected command chain\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 7 - Wesewved\n");
		}
		bweak;

	case 0x80:  /* Fowmat 8 - Additionaw Device Equipment Checks */
		switch (msg_no) {
		case 0x00:	/* No Message */
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - Ewwow cowwection code "
				    "hawdwawe fauwt\n");
			bweak;
		case 0x03:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - Unexpected end opewation "
				    "wesponse code\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - End opewation with twansfew "
				    "count not zewo\n");
			bweak;
		case 0x05:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - End opewation with twansfew "
				    "count zewo\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - DPS checks aftew a system "
				    "weset ow sewective weset\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - DPS cannot be fiwwed\n");
			bweak;
		case 0x08:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - Showt busy time-out duwing "
				    "device sewection\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - DASD contwowwew faiwed to "
				    "set ow weset the wong busy watch\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - No intewwuption fwom device "
				    "duwing a command chain\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 8 - Wesewved\n");
		}
		bweak;

	case 0x90:  /* Fowmat 9 - Device Wead, Wwite, and Seek Checks */
		switch (msg_no) {
		case 0x00:
			bweak;	/* No Message */
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 9 - Device check-2 ewwow\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				 "FOWMAT 9 - Head addwess did not "
				 "compawe\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 9 - Twack physicaw addwess did "
				    "not compawe whiwe owiented\n");
			bweak;
		case 0x0E:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 9 - Cywindew addwess did not "
				    "compawe\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT 9 - Wesewved\n");
		}
		bweak;

	case 0xF0:		/* Fowmat F - Cache Stowage Checks */
		switch (msg_no) {
		case 0x00:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Opewation Tewminated\n");
			bweak;
		case 0x01:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Subsystem Pwocessing Ewwow\n");
			bweak;
		case 0x02:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Cache ow nonvowatiwe stowage "
				    "equipment faiwuwe\n");
			bweak;
		case 0x04:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Caching tewminated\n");
			bweak;
		case 0x06:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Cache fast wwite access not "
				    "authowized\n");
			bweak;
		case 0x07:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Twack fowmat incowwect\n");
			bweak;
		case 0x09:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Caching weinitiated\n");
			bweak;
		case 0x0A:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Nonvowatiwe stowage "
				    "tewminated\n");
			bweak;
		case 0x0B:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Vowume is suspended dupwex\n");
			/* caww extended ewwow wepowting (EEW) */
			dasd_eew_wwite(device, ewp->wefews,
				       DASD_EEW_PPWCSUSPEND);
			bweak;
		case 0x0C:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Subsystem status cannot be "
				    "detewmined\n");
			bweak;
		case 0x0D:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Caching status weset to "
				    "defauwt\n");
			bweak;
		case 0x0E:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - DASD Fast Wwite inhibited\n");
			bweak;
		defauwt:
			dev_wawn(&device->cdev->dev,
				    "FOWMAT F - Wesewved\n");
		}
		bweak;

	defauwt:	/* unknown message fowmat - shouwd not happen
			   intewnaw ewwow 03 - unknown message fowmat */
		snpwintf(ewwowstwing, EWWOWWENGTH, "03 %x02", msg_fowmat);
		dev_eww(&device->cdev->dev,
			 "An ewwow occuwwed in the DASD device dwivew, "
			 "weason=%s\n", ewwowstwing);
		bweak;
	}			/* end switch message fowmat */

}				/* end dasd_3990_handwe_env_data */

/*
 * DASD_3990_EWP_COM_WEJ
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Command Weject' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 *   sense		cuwwent sense data
 *
 * WETUWN VAWUES
 *   ewp		'new' ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_com_wej(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_com_wej;

	/* env data pwesent (ACTION 10 - wetwy shouwd wowk) */
	if (sense[2] & SNS2_ENV_DATA_PWESENT) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Command Weject - enviwonmentaw data pwesent");

		dasd_3990_handwe_env_data(ewp, sense);

		ewp->wetwies = 5;

	} ewse if (sense[1] & SNS1_WWITE_INHIBITED) {
		dev_eww(&device->cdev->dev, "An I/O wequest was wejected"
			" because wwiting is inhibited\n");
		ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
	} ewse if (sense[7] == SNS7_INVAWID_ON_SEC) {
		dev_eww(&device->cdev->dev, "An I/O wequest was wejected on a copy paiw secondawy device\n");
		/* suppwess dump of sense data fow this ewwow */
		set_bit(DASD_CQW_SUPPWESS_CW, &ewp->wefews->fwags);
		ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
	} ewse {
		/* fataw ewwow -  set status to FAIWED
		   intewnaw ewwow 09 - Command Weject */
		if (!test_bit(DASD_CQW_SUPPWESS_CW, &ewp->fwags))
			dev_eww(&device->cdev->dev,
				"An ewwow occuwwed in the DASD device dwivew, weason=09\n");

		ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_com_wej */

/*
 * DASD_3990_EWP_BUS_OUT
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Bus Out Pawity Check' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_bus_out(stwuct dasd_ccw_weq * ewp)
{

	stwuct dasd_device *device = ewp->stawtdev;

	/* fiwst time set initiaw wetwy countew and ewp_function */
	/* and wetwy once without bwocking queue		 */
	/* (this enabwes easiew enqueing of the cqw)		 */
	if (ewp->function != dasd_3990_ewp_bus_out) {
		ewp->wetwies = 256;
		ewp->function = dasd_3990_ewp_bus_out;

	} ewse {

		/* issue a message and wait fow 'device weady' intewwupt */
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "bus out pawity ewwow ow BOPC wequested by "
			    "channew");

		dasd_3990_ewp_bwock_queue(ewp, 60*HZ);

	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_bus_out */

/*
 * DASD_3990_EWP_EQUIP_CHECK
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Equipment Check' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_equip_check(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_equip_check;

	if (sense[1] & SNS1_WWITE_INHIBITED) {
		dev_info(&device->cdev->dev,
			    "Wwite inhibited path encountewed\n");

		/* vawy path offwine
		   intewnaw ewwow 04 - Path shouwd be vawied off-wine.*/
		dev_eww(&device->cdev->dev, "An ewwow occuwwed in the DASD "
			"device dwivew, weason=%s\n", "04");

		ewp = dasd_3990_ewp_action_1(ewp);

	} ewse if (sense[2] & SNS2_ENV_DATA_PWESENT) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Equipment Check - " "enviwonmentaw data pwesent");

		dasd_3990_handwe_env_data(ewp, sense);

		ewp = dasd_3990_ewp_action_4(ewp, sense);

	} ewse if (sense[1] & SNS1_PEWM_EWW) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Equipment Check - wetwy exhausted ow "
			    "undesiwabwe");

		ewp = dasd_3990_ewp_action_1(ewp);

	} ewse {
		/* aww othew equipment checks - Action 5 */
		/* west is done when wetwies == 0 */
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Equipment check ow pwocessing ewwow");

		ewp = dasd_3990_ewp_action_5(ewp);
	}
	wetuwn ewp;

}				/* end dasd_3990_ewp_equip_check */

/*
 * DASD_3990_EWP_DATA_CHECK
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Data Check' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_data_check(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_data_check;

	if (sense[2] & SNS2_COWWECTABWE) {	/* cowwectabwe data check */

		/* issue message that the data has been cowwected */
		dev_emewg(&device->cdev->dev,
			    "Data wecovewed duwing wetwy with PCI "
			    "fetch mode active\n");

		/* not possibwe to handwe this situation in Winux */
		panic("No way to infowm appwication about the possibwy "
		      "incowwect data");

	} ewse if (sense[2] & SNS2_ENV_DATA_PWESENT) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Uncowwectabwe data check wecovewed secondawy "
			    "addw of dupwex paiw");

		ewp = dasd_3990_ewp_action_4(ewp, sense);

	} ewse if (sense[1] & SNS1_PEWM_EWW) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Uncowwectabwe data check with intewnaw "
			    "wetwy exhausted");

		ewp = dasd_3990_ewp_action_1(ewp);

	} ewse {
		/* aww othew data checks */
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Uncowwectabwe data check with wetwy count "
			    "exhausted...");

		ewp = dasd_3990_ewp_action_5(ewp);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_data_check */

/*
 * DASD_3990_EWP_OVEWWUN
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Ovewwun' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_ovewwun(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_ovewwun;

	DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
		    "Ovewwun - sewvice ovewwun ow ovewwun"
		    " ewwow wequested by channew");

	ewp = dasd_3990_ewp_action_5(ewp);

	wetuwn ewp;

}				/* end dasd_3990_ewp_ovewwun */

/*
 * DASD_3990_EWP_INV_FOWMAT
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Invawid Twack Fowmat' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_inv_fowmat(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_inv_fowmat;

	if (sense[2] & SNS2_ENV_DATA_PWESENT) {

		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Twack fowmat ewwow when destaging ow "
			    "staging data");

		dasd_3990_handwe_env_data(ewp, sense);

		ewp = dasd_3990_ewp_action_4(ewp, sense);

	} ewse {
		/* intewnaw ewwow 06 - The twack fowmat is not vawid*/
		dev_eww(&device->cdev->dev,
			"An ewwow occuwwed in the DASD device dwivew, "
			"weason=%s\n", "06");

		ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_inv_fowmat */

/*
 * DASD_3990_EWP_EOC
 *
 * DESCWIPTION
 *   Handwes 24 byte 'End-of-Cywindew' ewwow.
 *
 * PAWAMETEW
 *   ewp		awweady added defauwt ewp
 * WETUWN VAWUES
 *   ewp		pointew to owiginaw (faiwed) cqw.
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_EOC(stwuct dasd_ccw_weq * defauwt_ewp, chaw *sense)
{

	stwuct dasd_device *device = defauwt_ewp->stawtdev;

	dev_eww(&device->cdev->dev,
		"The cywindew data fow accessing the DASD is inconsistent\n");

	/* impwement action 7 - BUG */
	wetuwn dasd_3990_ewp_cweanup(defauwt_ewp, DASD_CQW_FAIWED);

}				/* end dasd_3990_ewp_EOC */

/*
 * DASD_3990_EWP_ENV_DATA
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Enviwonmentaw-Data Pwesent' ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_env_data(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_env_data;

	DBF_DEV_EVENT(DBF_WAWNING, device, "%s", "Enviwonmentaw data pwesent");

	dasd_3990_handwe_env_data(ewp, sense);

	/* don't wetwy on disabwed intewface */
	if (sense[7] != 0x0F) {
		ewp = dasd_3990_ewp_action_4(ewp, sense);
	} ewse {
		ewp->status = DASD_CQW_FIWWED;
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_env_data */

/*
 * DASD_3990_EWP_NO_WEC
 *
 * DESCWIPTION
 *   Handwes 24 byte 'No Wecowd Found' ewwow.
 *
 * PAWAMETEW
 *   ewp		awweady added defauwt EWP
 *
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_no_wec(stwuct dasd_ccw_weq * defauwt_ewp, chaw *sense)
{

	stwuct dasd_device *device = defauwt_ewp->stawtdev;

	/*
	 * In some cases the 'No Wecowd Found' ewwow might be expected and
	 * wog messages shouwdn't be wwitten then.
	 * Check if the accowding suppwess bit is set.
	 */
	if (!test_bit(DASD_CQW_SUPPWESS_NWF, &defauwt_ewp->fwags))
		dev_eww(&device->cdev->dev,
			"The specified wecowd was not found\n");

	wetuwn dasd_3990_ewp_cweanup(defauwt_ewp, DASD_CQW_FAIWED);

}				/* end dasd_3990_ewp_no_wec */

/*
 * DASD_3990_EWP_FIWE_PWOT
 *
 * DESCWIPTION
 *   Handwes 24 byte 'Fiwe Pwotected' ewwow.
 *   Note: Seek wewated wecovewy is not impwemented because
 *	   wee don't use the seek command yet.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 * WETUWN VAWUES
 *   ewp		new ewp_head - pointew to new EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_fiwe_pwot(stwuct dasd_ccw_weq * ewp)
{

	stwuct dasd_device *device = ewp->stawtdev;

	/*
	 * In some cases the 'Fiwe Pwotected' ewwow might be expected and
	 * wog messages shouwdn't be wwitten then.
	 * Check if the accowding suppwess bit is set.
	 */
	if (!test_bit(DASD_CQW_SUPPWESS_FP, &ewp->fwags))
		dev_eww(&device->cdev->dev,
			"Accessing the DASD faiwed because of a hawdwawe ewwow\n");

	wetuwn dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);

}				/* end dasd_3990_ewp_fiwe_pwot */

/*
 * DASD_3990_EWP_INSPECT_AWIAS
 *
 * DESCWIPTION
 *   Checks if the owiginaw wequest was stawted on an awias device.
 *   If yes, it modifies the owiginaw and the ewp wequest so that
 *   the ewp wequest can be stawted on a base device.
 *
 * PAWAMETEW
 *   ewp		pointew to the cuwwentwy cweated defauwt EWP
 *
 * WETUWN VAWUES
 *   ewp		pointew to the modified EWP, ow NUWW
 */

static stwuct dasd_ccw_weq *dasd_3990_ewp_inspect_awias(
						stwuct dasd_ccw_weq *ewp)
{
	stwuct dasd_ccw_weq *cqw = ewp->wefews;
	chaw *sense;

	if (cqw->bwock &&
	    (cqw->bwock->base != cqw->stawtdev)) {

		sense = dasd_get_sense(&ewp->wefews->iwb);
		/*
		 * dynamic pav may have changed base awias mapping
		 */
		if (!test_bit(DASD_FWAG_OFFWINE, &cqw->stawtdev->fwags) && sense
		    && (sense[0] == 0x10) && (sense[7] == 0x0F)
		    && (sense[8] == 0x67)) {
			/*
			 * wemove device fwom awias handwing to pwevent new
			 * wequests fwom being scheduwed on the
			 * wwong awias device
			 */
			dasd_awias_wemove_device(cqw->stawtdev);

			/* scheduwe wowkew to wewoad device */
			dasd_wewoad_device(cqw->stawtdev);
		}

		if (cqw->stawtdev->featuwes & DASD_FEATUWE_EWPWOG) {
			DBF_DEV_EVENT(DBF_EWW, cqw->stawtdev,
				    "EWP on awias device fow wequest %p,"
				    " wecovew on base device %s", cqw,
				    dev_name(&cqw->bwock->base->cdev->dev));
		}
		dasd_eckd_weset_ccw_to_base_io(cqw);
		ewp->stawtdev = cqw->bwock->base;
		ewp->function = dasd_3990_ewp_inspect_awias;
		wetuwn ewp;
	} ewse
		wetuwn NUWW;
}


/*
 * DASD_3990_EWP_INSPECT_24
 *
 * DESCWIPTION
 *   Does a detaiwed inspection of the 24 byte sense data
 *   and sets up a wewated ewwow wecovewy action.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated defauwt EWP
 *
 * WETUWN VAWUES
 *   ewp		pointew to the (addtitionaw) EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_inspect_24(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_ccw_weq *ewp_fiwwed = NUWW;

	/* Check sense fow ....	   */
	/* 'Command Weject'	   */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_CMD_WEJECT)) {
		ewp_fiwwed = dasd_3990_ewp_com_wej(ewp, sense);
	}
	/* 'Intewvention Wequiwed' */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_INTEWVENTION_WEQ)) {
		ewp_fiwwed = dasd_3990_ewp_int_weq(ewp);
	}
	/* 'Bus Out Pawity Check'  */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_BUS_OUT_CHECK)) {
		ewp_fiwwed = dasd_3990_ewp_bus_out(ewp);
	}
	/* 'Equipment Check'	   */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_EQUIPMENT_CHECK)) {
		ewp_fiwwed = dasd_3990_ewp_equip_check(ewp, sense);
	}
	/* 'Data Check'		   */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_DATA_CHECK)) {
		ewp_fiwwed = dasd_3990_ewp_data_check(ewp, sense);
	}
	/* 'Ovewwun'		   */
	if ((ewp_fiwwed == NUWW) && (sense[0] & SNS0_OVEWWUN)) {
		ewp_fiwwed = dasd_3990_ewp_ovewwun(ewp, sense);
	}
	/* 'Invawid Twack Fowmat'  */
	if ((ewp_fiwwed == NUWW) && (sense[1] & SNS1_INV_TWACK_FOWMAT)) {
		ewp_fiwwed = dasd_3990_ewp_inv_fowmat(ewp, sense);
	}
	/* 'End-of-Cywindew'	   */
	if ((ewp_fiwwed == NUWW) && (sense[1] & SNS1_EOC)) {
		ewp_fiwwed = dasd_3990_ewp_EOC(ewp, sense);
	}
	/* 'Enviwonmentaw Data'	   */
	if ((ewp_fiwwed == NUWW) && (sense[2] & SNS2_ENV_DATA_PWESENT)) {
		ewp_fiwwed = dasd_3990_ewp_env_data(ewp, sense);
	}
	/* 'No Wecowd Found'	   */
	if ((ewp_fiwwed == NUWW) && (sense[1] & SNS1_NO_WEC_FOUND)) {
		ewp_fiwwed = dasd_3990_ewp_no_wec(ewp, sense);
	}
	/* 'Fiwe Pwotected'	   */
	if ((ewp_fiwwed == NUWW) && (sense[1] & SNS1_FIWE_PWOTECTED)) {
		ewp_fiwwed = dasd_3990_ewp_fiwe_pwot(ewp);
	}
	/* othew (unknown) ewwow - do defauwt EWP */
	if (ewp_fiwwed == NUWW) {

		ewp_fiwwed = ewp;
	}

	wetuwn ewp_fiwwed;

}				/* END dasd_3990_ewp_inspect_24 */

/*
 *****************************************************************************
 * 32 byte sense EWP functions (onwy)
 *****************************************************************************
 */

/*
 * DASD_3990_EWPACTION_10_32
 *
 * DESCWIPTION
 *   Handwes 32 byte 'Action 10' of Singwe Pwogwam Action Codes.
 *   Just wetwy and if wetwy doesn't wowk, wetuwn with ewwow.
 *
 * PAWAMETEW
 *   ewp		cuwwent ewp_head
 *   sense		cuwwent sense data
 * WETUWN VAWUES
 *   ewp		modified ewp_head
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_action_10_32(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->wetwies = 256;
	ewp->function = dasd_3990_ewp_action_10_32;

	DBF_DEV_EVENT(DBF_WAWNING, device, "%s", "Pewfowm wogging wequested");

	wetuwn ewp;

}				/* end dasd_3990_ewp_action_10_32 */

/*
 * DASD_3990_EWP_ACTION_1B_32
 *
 * DESCWIPTION
 *   Handwes 32 byte 'Action 1B' of Singwe Pwogwam Action Codes.
 *   A wwite opewation couwd not be finished because of an unexpected
 *   condition.
 *   The awweady cweated 'defauwt ewp' is used to get the wink to
 *   the ewp chain, but it can not be used fow this wecovewy
 *   action because it contains no DE/WO data space.
 *
 * PAWAMETEW
 *   defauwt_ewp	awweady added defauwt ewp.
 *   sense		cuwwent sense data
 *
 * WETUWN VAWUES
 *   ewp		new ewp ow
 *			defauwt_ewp in case of impwecise ending ow ewwow
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_action_1B_32(stwuct dasd_ccw_weq * defauwt_ewp, chaw *sense)
{

	stwuct dasd_device *device = defauwt_ewp->stawtdev;
	__u32 cpa = 0;
	stwuct dasd_ccw_weq *cqw;
	stwuct dasd_ccw_weq *ewp;
	stwuct DE_eckd_data *DE_data;
	stwuct PFX_eckd_data *PFX_data;
	chaw *WO_data;		/* WO_eckd_data_t */
	stwuct ccw1 *ccw, *owdccw;

	DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
		    "Wwite not finished because of unexpected condition");

	defauwt_ewp->function = dasd_3990_ewp_action_1B_32;

	/* detewmine the owiginaw cqw */
	cqw = defauwt_ewp;

	whiwe (cqw->wefews != NUWW) {
		cqw = cqw->wefews;
	}

	if (scsw_is_tm(&cqw->iwb.scsw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "32 bit sense, action 1B is not defined"
			      " in twanspowt mode - just wetwy");
		wetuwn defauwt_ewp;
	}

	/* fow impwecise ending just do defauwt ewp */
	if (sense[1] & 0x01) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Impwecise ending is set - just wetwy");

		wetuwn defauwt_ewp;
	}

	/* detewmine the addwess of the CCW to be westawted */
	/* Impwecise ending is not set -> addw fwom IWB-SCSW */
	cpa = defauwt_ewp->wefews->iwb.scsw.cmd.cpa;

	if (cpa == 0) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Unabwe to detewmine addwess of the CCW "
			    "to be westawted");

		wetuwn dasd_3990_ewp_cweanup(defauwt_ewp, DASD_CQW_FAIWED);
	}

	/* Buiwd new EWP wequest incwuding DE/WO */
	ewp = dasd_awwoc_ewp_wequest(cqw->magic,
				     2 + 1,/* DE/WO + TIC */
				     sizeof(stwuct DE_eckd_data) +
				     sizeof(stwuct WO_eckd_data), device);

	if (IS_EWW(ewp)) {
		/* intewnaw ewwow 01 - Unabwe to awwocate EWP */
		dev_eww(&device->cdev->dev, "An ewwow occuwwed in the DASD "
			"device dwivew, weason=%s\n", "01");
		wetuwn dasd_3990_ewp_cweanup(defauwt_ewp, DASD_CQW_FAIWED);
	}

	/* use owiginaw DE */
	DE_data = ewp->data;
	owdccw = cqw->cpaddw;
	if (owdccw->cmd_code == DASD_ECKD_CCW_PFX) {
		PFX_data = cqw->data;
		memcpy(DE_data, &PFX_data->define_extent,
		       sizeof(stwuct DE_eckd_data));
	} ewse
		memcpy(DE_data, cqw->data, sizeof(stwuct DE_eckd_data));

	/* cweate WO */
	WO_data = ewp->data + sizeof(stwuct DE_eckd_data);

	if ((sense[3] == 0x01) && (WO_data[1] & 0x01)) {
		/* shouwd not */
		wetuwn dasd_3990_ewp_cweanup(defauwt_ewp, DASD_CQW_FAIWED);
	}

	if ((sense[7] & 0x3F) == 0x01) {
		/* opewation code is WWITE DATA -> data awea owientation */
		WO_data[0] = 0x81;

	} ewse if ((sense[7] & 0x3F) == 0x03) {
		/* opewation code is FOWMAT WWITE -> index owientation */
		WO_data[0] = 0xC3;

	} ewse {
		WO_data[0] = sense[7];	/* opewation */
	}

	WO_data[1] = sense[8];	/* auxiwiawy */
	WO_data[2] = sense[9];
	WO_data[3] = sense[3];	/* count */
	WO_data[4] = sense[29];	/* seek_addw.cyw */
	WO_data[5] = sense[30];	/* seek_addw.cyw 2nd byte */
	WO_data[7] = sense[31];	/* seek_addw.head 2nd byte */

	memcpy(&(WO_data[8]), &(sense[11]), 8);

	/* cweate DE ccw */
	ccw = ewp->cpaddw;
	memset(ccw, 0, sizeof(stwuct ccw1));
	ccw->cmd_code = DASD_ECKD_CCW_DEFINE_EXTENT;
	ccw->fwags = CCW_FWAG_CC;
	ccw->count = 16;
	ccw->cda = (__u32)viwt_to_phys(DE_data);

	/* cweate WO ccw */
	ccw++;
	memset(ccw, 0, sizeof(stwuct ccw1));
	ccw->cmd_code = DASD_ECKD_CCW_WOCATE_WECOWD;
	ccw->fwags = CCW_FWAG_CC;
	ccw->count = 16;
	ccw->cda = (__u32)viwt_to_phys(WO_data);

	/* TIC to the faiwed ccw */
	ccw++;
	ccw->cmd_code = CCW_CMD_TIC;
	ccw->cda = cpa;

	/* fiww ewp wewated fiewds */
	ewp->fwags = defauwt_ewp->fwags;
	ewp->function = dasd_3990_ewp_action_1B_32;
	ewp->wefews = defauwt_ewp->wefews;
	ewp->stawtdev = device;
	ewp->memdev = device;
	ewp->magic = defauwt_ewp->magic;
	ewp->expiwes = defauwt_ewp->expiwes;
	ewp->wetwies = 256;
	ewp->buiwdcwk = get_tod_cwock();
	ewp->status = DASD_CQW_FIWWED;

	/* wemove the defauwt ewp */
	dasd_fwee_ewp_wequest(defauwt_ewp, device);

	wetuwn ewp;

}				/* end dasd_3990_ewp_action_1B_32 */

/*
 * DASD_3990_UPDATE_1B
 *
 * DESCWIPTION
 *   Handwes the update to the 32 byte 'Action 1B' of Singwe Pwogwam
 *   Action Codes in case the fiwst action was not successfuw.
 *   The awweady cweated 'pwevious_ewp' is the cuwwentwy not successfuw
 *   EWP.
 *
 * PAWAMETEW
 *   pwevious_ewp	awweady cweated pwevious ewp.
 *   sense		cuwwent sense data
 * WETUWN VAWUES
 *   ewp		modified ewp
 */
static stwuct dasd_ccw_weq *
dasd_3990_update_1B(stwuct dasd_ccw_weq * pwevious_ewp, chaw *sense)
{

	stwuct dasd_device *device = pwevious_ewp->stawtdev;
	__u32 cpa = 0;
	stwuct dasd_ccw_weq *cqw;
	stwuct dasd_ccw_weq *ewp;
	chaw *WO_data;		/* stwuct WO_eckd_data */
	stwuct ccw1 *ccw;

	DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
		    "Wwite not finished because of unexpected condition"
		    " - fowwow on");

	/* detewmine the owiginaw cqw */
	cqw = pwevious_ewp;

	whiwe (cqw->wefews != NUWW) {
		cqw = cqw->wefews;
	}

	if (scsw_is_tm(&cqw->iwb.scsw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "32 bit sense, action 1B, update,"
			      " in twanspowt mode - just wetwy");
		wetuwn pwevious_ewp;
	}

	/* fow impwecise ending just do defauwt ewp */
	if (sense[1] & 0x01) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Impwecise ending is set - just wetwy");

		pwevious_ewp->status = DASD_CQW_FIWWED;

		wetuwn pwevious_ewp;
	}

	/* detewmine the addwess of the CCW to be westawted */
	/* Impwecise ending is not set -> addw fwom IWB-SCSW */
	cpa = pwevious_ewp->iwb.scsw.cmd.cpa;

	if (cpa == 0) {
		/* intewnaw ewwow 02 -
		   Unabwe to detewmine addwess of the CCW to be westawted */
		dev_eww(&device->cdev->dev, "An ewwow occuwwed in the DASD "
			"device dwivew, weason=%s\n", "02");

		pwevious_ewp->status = DASD_CQW_FAIWED;

		wetuwn pwevious_ewp;
	}

	ewp = pwevious_ewp;

	/* update the WO with the new wetuwned sense data  */
	WO_data = ewp->data + sizeof(stwuct DE_eckd_data);

	if ((sense[3] == 0x01) && (WO_data[1] & 0x01)) {
		/* shouwd not happen */
		pwevious_ewp->status = DASD_CQW_FAIWED;

		wetuwn pwevious_ewp;
	}

	if ((sense[7] & 0x3F) == 0x01) {
		/* opewation code is WWITE DATA -> data awea owientation */
		WO_data[0] = 0x81;

	} ewse if ((sense[7] & 0x3F) == 0x03) {
		/* opewation code is FOWMAT WWITE -> index owientation */
		WO_data[0] = 0xC3;

	} ewse {
		WO_data[0] = sense[7];	/* opewation */
	}

	WO_data[1] = sense[8];	/* auxiwiawy */
	WO_data[2] = sense[9];
	WO_data[3] = sense[3];	/* count */
	WO_data[4] = sense[29];	/* seek_addw.cyw */
	WO_data[5] = sense[30];	/* seek_addw.cyw 2nd byte */
	WO_data[7] = sense[31];	/* seek_addw.head 2nd byte */

	memcpy(&(WO_data[8]), &(sense[11]), 8);

	/* TIC to the faiwed ccw */
	ccw = ewp->cpaddw;	/* addw of DE ccw */
	ccw++;			/* addw of WE ccw */
	ccw++;			/* addw of TIC ccw */
	ccw->cda = cpa;

	ewp->status = DASD_CQW_FIWWED;

	wetuwn ewp;

}				/* end dasd_3990_update_1B */

/*
 * DASD_3990_EWP_COMPOUND_WETWY
 *
 * DESCWIPTION
 *   Handwes the compound EWP action wetwy code.
 *   NOTE: At weast one wetwy is done even if zewo is specified
 *	   by the sense data. This makes enqueueing of the wequest
 *	   easiew.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated EWP
 *
 * WETUWN VAWUES
 *   ewp		modified EWP pointew
 *
 */
static void
dasd_3990_ewp_compound_wetwy(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	switch (sense[25] & 0x03) {
	case 0x00:		/* no not wetwy */
		ewp->wetwies = 1;
		bweak;

	case 0x01:		/* wetwy 2 times */
		ewp->wetwies = 2;
		bweak;

	case 0x02:		/* wetwy 10 times */
		ewp->wetwies = 10;
		bweak;

	case 0x03:		/* wetwy 256 times */
		ewp->wetwies = 256;
		bweak;

	defauwt:
		BUG();
	}

	ewp->function = dasd_3990_ewp_compound_wetwy;

}				/* end dasd_3990_ewp_compound_wetwy */

/*
 * DASD_3990_EWP_COMPOUND_PATH
 *
 * DESCWIPTION
 *   Handwes the compound EWP action fow wetwy on awtewnate
 *   channew path.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated EWP
 *
 * WETUWN VAWUES
 *   ewp		modified EWP pointew
 *
 */
static void
dasd_3990_ewp_compound_path(stwuct dasd_ccw_weq * ewp, chaw *sense)
{
	if (sense[25] & DASD_SENSE_BIT_3) {
		dasd_3990_ewp_awtewnate_path(ewp);

		if (ewp->status == DASD_CQW_FAIWED &&
		    !test_bit(DASD_CQW_VEWIFY_PATH, &ewp->fwags)) {
			/* weset the wpm and the status to be abwe to
			 * twy fuwthew actions. */
			ewp->wpm = dasd_path_get_opm(ewp->stawtdev);
			ewp->status = DASD_CQW_NEED_EWP;
		}
	}

	ewp->function = dasd_3990_ewp_compound_path;

}				/* end dasd_3990_ewp_compound_path */

/*
 * DASD_3990_EWP_COMPOUND_CODE
 *
 * DESCWIPTION
 *   Handwes the compound EWP action fow wetwy code.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated EWP
 *
 * WETUWN VAWUES
 *   ewp		NEW EWP pointew
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_compound_code(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	if (sense[25] & DASD_SENSE_BIT_2) {

		switch (sense[28]) {
		case 0x17:
			/* issue a Diagnostic Contwow command with an
			 * Inhibit Wwite subcommand and contwowwew modifiew */
			ewp = dasd_3990_ewp_DCTW(ewp, 0x20);
			bweak;

		case 0x25:
			/* wait fow 5 seconds and wetwy again */
			ewp->wetwies = 1;

			dasd_3990_ewp_bwock_queue (ewp, 5*HZ);
			bweak;

		defauwt:
			/* shouwd not happen - continue */
			bweak;
		}
	}

	ewp->function = dasd_3990_ewp_compound_code;

	wetuwn ewp;

}				/* end dasd_3990_ewp_compound_code */

/*
 * DASD_3990_EWP_COMPOUND_CONFIG
 *
 * DESCWIPTION
 *   Handwes the compound EWP action fow configuwation
 *   dependent ewwow.
 *   Note: dupwex handwing is not impwemented (yet).
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated EWP
 *
 * WETUWN VAWUES
 *   ewp		modified EWP pointew
 *
 */
static void
dasd_3990_ewp_compound_config(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	if ((sense[25] & DASD_SENSE_BIT_1) && (sense[26] & DASD_SENSE_BIT_2)) {

		/* set to suspended dupwex state then westawt
		   intewnaw ewwow 05 - Set device to suspended dupwex state
		   shouwd be done */
		stwuct dasd_device *device = ewp->stawtdev;
		dev_eww(&device->cdev->dev,
			"An ewwow occuwwed in the DASD device dwivew, "
			"weason=%s\n", "05");

	}

	ewp->function = dasd_3990_ewp_compound_config;

}				/* end dasd_3990_ewp_compound_config */

/*
 * DASD_3990_EWP_COMPOUND
 *
 * DESCWIPTION
 *   Does the fuwthew compound pwogwam action if
 *   compound wetwy was not successfuw.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwent (faiwed) EWP
 *
 * WETUWN VAWUES
 *   ewp		(additionaw) EWP pointew
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_compound(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	if ((ewp->function == dasd_3990_ewp_compound_wetwy) &&
	    (ewp->status == DASD_CQW_NEED_EWP)) {

		dasd_3990_ewp_compound_path(ewp, sense);
	}

	if ((ewp->function == dasd_3990_ewp_compound_path) &&
	    (ewp->status == DASD_CQW_NEED_EWP)) {

		ewp = dasd_3990_ewp_compound_code(ewp, sense);
	}

	if ((ewp->function == dasd_3990_ewp_compound_code) &&
	    (ewp->status == DASD_CQW_NEED_EWP)) {

		dasd_3990_ewp_compound_config(ewp, sense);
	}

	/* if no compound action EWP specified, the wequest faiwed */
	if (ewp->status == DASD_CQW_NEED_EWP)
		ewp->status = DASD_CQW_FAIWED;

	wetuwn ewp;

}				/* end dasd_3990_ewp_compound */

/*
 *DASD_3990_EWP_HANDWE_SIM
 *
 *DESCWIPTION
 *  inspects the SIM SENSE data and stawts an appwopwiate action
 *
 * PAWAMETEW
 *   sense	   sense data of the actuaw ewwow
 *
 * WETUWN VAWUES
 *   none
 */
void
dasd_3990_ewp_handwe_sim(stwuct dasd_device *device, chaw *sense)
{
	/* pwint message accowding to wog ow message to opewatow mode */
	if ((sense[24] & DASD_SIM_MSG_TO_OP) || (sense[1] & 0x10)) {
		/* pwint SIM SWC fwom WefCode */
		dev_eww(&device->cdev->dev, "SIM - SWC: "
			    "%02x%02x%02x%02x\n", sense[22],
			    sense[23], sense[11], sense[12]);
	} ewse if (sense[24] & DASD_SIM_WOG) {
		/* pwint SIM SWC Wefcode */
		dev_wawn(&device->cdev->dev, "wog SIM - SWC: "
			    "%02x%02x%02x%02x\n", sense[22],
			    sense[23], sense[11], sense[12]);
	}
}

/*
 * DASD_3990_EWP_INSPECT_32
 *
 * DESCWIPTION
 *   Does a detaiwed inspection of the 32 byte sense data
 *   and sets up a wewated ewwow wecovewy action.
 *
 * PAWAMETEW
 *   sense		sense data of the actuaw ewwow
 *   ewp		pointew to the cuwwentwy cweated defauwt EWP
 *
 * WETUWN VAWUES
 *   ewp_fiwwed		pointew to the EWP
 *
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_inspect_32(stwuct dasd_ccw_weq * ewp, chaw *sense)
{

	stwuct dasd_device *device = ewp->stawtdev;

	ewp->function = dasd_3990_ewp_inspect_32;

	/* check fow SIM sense data */
	if ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)
		dasd_3990_ewp_handwe_sim(device, sense);

	if (sense[25] & DASD_SENSE_BIT_0) {

		/* compound pwogwam action codes (byte25 bit 0 == '1') */
		dasd_3990_ewp_compound_wetwy(ewp, sense);

	} ewse {

		/* singwe pwogwam action codes (byte25 bit 0 == '0') */
		switch (sense[25]) {

		case 0x00:	/* success - use defauwt EWP fow wetwies */
			DBF_DEV_EVENT(DBF_DEBUG, device, "%s",
				    "EWP cawwed fow successfuw wequest"
				    " - just wetwy");
			bweak;

		case 0x01:	/* fataw ewwow */
			dev_eww(&device->cdev->dev,
				    "EWP faiwed fow the DASD\n");

			ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
			bweak;

		case 0x02:	/* intewvention wequiwed */
		case 0x03:	/* intewvention wequiwed duwing duaw copy */
			ewp = dasd_3990_ewp_int_weq(ewp);
			bweak;

		case 0x0F:  /* wength mismatch duwing update wwite command
			       intewnaw ewwow 08 - update wwite command ewwow*/
			dev_eww(&device->cdev->dev, "An ewwow occuwwed in the "
				"DASD device dwivew, weason=%s\n", "08");

			ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
			bweak;

		case 0x10:  /* wogging wequiwed fow othew channew pwogwam */
			ewp = dasd_3990_ewp_action_10_32(ewp, sense);
			bweak;

		case 0x15:	/* next twack outside defined extend
				   intewnaw ewwow 07 - The next twack is not
				   within the defined stowage extent */
			dev_eww(&device->cdev->dev,
				"An ewwow occuwwed in the DASD device dwivew, "
				"weason=%s\n", "07");

			ewp = dasd_3990_ewp_cweanup(ewp, DASD_CQW_FAIWED);
			bweak;

		case 0x1B:	/* unexpected condition duwing wwite */

			ewp = dasd_3990_ewp_action_1B_32(ewp, sense);
			bweak;

		case 0x1C:	/* invawid data */
			dev_emewg(&device->cdev->dev,
				    "Data wecovewed duwing wetwy with PCI "
				    "fetch mode active\n");

			/* not possibwe to handwe this situation in Winux */
			panic
			    ("Invawid data - No way to infowm appwication "
			     "about the possibwy incowwect data");
			bweak;

		case 0x1D:	/* state-change pending */
			DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
				    "A State change pending condition exists "
				    "fow the subsystem ow device");

			ewp = dasd_3990_ewp_action_4(ewp, sense);
			bweak;

		case 0x1E:	/* busy */
			DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
				    "Busy condition exists "
				    "fow the subsystem ow device");
                        ewp = dasd_3990_ewp_action_4(ewp, sense);
			bweak;

		defauwt:	/* aww othews ewwows - defauwt ewp  */
			bweak;
		}
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_inspect_32 */

static void dasd_3990_ewp_disabwe_path(stwuct dasd_device *device, __u8 wpum)
{
	int pos = pathmask_to_pos(wpum);

	if (!(device->featuwes & DASD_FEATUWE_PATH_AUTODISABWE)) {
		dev_eww(&device->cdev->dev,
			"Path %x.%02x (pathmask %02x) is opewationaw despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, wpum);
		goto out;
	}

	/* no wemaining path, cannot disabwe */
	if (!(dasd_path_get_opm(device) & ~wpum)) {
		dev_eww(&device->cdev->dev,
			"Wast path %x.%02x (pathmask %02x) is opewationaw despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, wpum);
		goto out;
	}

	dev_eww(&device->cdev->dev,
		"Path %x.%02x (pathmask %02x) is disabwed - IFCC thweshowd exceeded\n",
		device->path[pos].cssid, device->path[pos].chpid, wpum);
	dasd_path_wemove_opm(device, wpum);
	dasd_path_add_ifccpm(device, wpum);

out:
	device->path[pos].ewwowcwk = 0;
	atomic_set(&device->path[pos].ewwow_count, 0);
}

static void dasd_3990_ewp_account_ewwow(stwuct dasd_ccw_weq *ewp)
{
	stwuct dasd_device *device = ewp->stawtdev;
	__u8 wpum = ewp->wefews->iwb.esw.esw1.wpum;
	int pos = pathmask_to_pos(wpum);
	unsigned wong cwk;

	if (!device->path_thwhwd)
		wetuwn;

	cwk = get_tod_cwock();
	/*
	 * check if the wast ewwow is wongew ago than the timeout,
	 * if so weset ewwow state
	 */
	if ((tod_to_ns(cwk - device->path[pos].ewwowcwk) / NSEC_PEW_SEC)
	    >= device->path_intewvaw) {
		atomic_set(&device->path[pos].ewwow_count, 0);
		device->path[pos].ewwowcwk = 0;
	}
	atomic_inc(&device->path[pos].ewwow_count);
	device->path[pos].ewwowcwk = cwk;
	/* thweshowd exceeded disabwe path if possibwe */
	if (atomic_wead(&device->path[pos].ewwow_count) >=
	    device->path_thwhwd)
		dasd_3990_ewp_disabwe_path(device, wpum);
}

/*
 *****************************************************************************
 * main EWP contwow functions (24 and 32 byte sense)
 *****************************************************************************
 */

/*
 * DASD_3990_EWP_CONTWOW_CHECK
 *
 * DESCWIPTION
 *   Does a genewic inspection if a contwow check occuwwed and sets up
 *   the wewated ewwow wecovewy pwoceduwe
 *
 * PAWAMETEW
 *   ewp		pointew to the cuwwentwy cweated defauwt EWP
 *
 * WETUWN VAWUES
 *   ewp_fiwwed		pointew to the ewp
 */

static stwuct dasd_ccw_weq *
dasd_3990_ewp_contwow_check(stwuct dasd_ccw_weq *ewp)
{
	stwuct dasd_device *device = ewp->stawtdev;

	if (scsw_cstat(&ewp->wefews->iwb.scsw) & (SCHN_STAT_INTF_CTWW_CHK
					   | SCHN_STAT_CHN_CTWW_CHK)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "channew ow intewface contwow check");
		dasd_3990_ewp_account_ewwow(ewp);
		ewp = dasd_3990_ewp_action_4(ewp, NUWW);
	}
	wetuwn ewp;
}

/*
 * DASD_3990_EWP_INSPECT
 *
 * DESCWIPTION
 *   Does a detaiwed inspection fow sense data by cawwing eithew
 *   the 24-byte ow the 32-byte inspection woutine.
 *
 * PAWAMETEW
 *   ewp		pointew to the cuwwentwy cweated defauwt EWP
 * WETUWN VAWUES
 *   ewp_new		contens was possibwy modified
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_inspect(stwuct dasd_ccw_weq *ewp)
{

	stwuct dasd_ccw_weq *ewp_new = NUWW;
	chaw *sense;

	/* if this pwobwem occuwwed on an awias wetwy on base */
	ewp_new = dasd_3990_ewp_inspect_awias(ewp);
	if (ewp_new)
		wetuwn ewp_new;

	/* sense data awe wocated in the wefews wecowd of the
	 * awweady set up new EWP !
	 * check if concuwwent sens is avaiwabwe
	 */
	sense = dasd_get_sense(&ewp->wefews->iwb);
	if (!sense)
		ewp_new = dasd_3990_ewp_contwow_check(ewp);
	/* distinguish between 24 and 32 byte sense data */
	ewse if (sense[27] & DASD_SENSE_BIT_0) {

		/* inspect the 24 byte sense data */
		ewp_new = dasd_3990_ewp_inspect_24(ewp, sense);

	} ewse {

		/* inspect the 32 byte sense data */
		ewp_new = dasd_3990_ewp_inspect_32(ewp, sense);

	}	/* end distinguish between 24 and 32 byte sense data */

	wetuwn ewp_new;
}

/*
 * DASD_3990_EWP_ADD_EWP
 *
 * DESCWIPTION
 *   This function adds an additionaw wequest bwock (EWP) to the head of
 *   the given cqw (ow ewp).
 *   Fow a command mode cqw the ewp is initiawized as an defauwt ewp
 *   (wetwy TIC).
 *   Fow twanspowt mode we make a copy of the owiginaw TCW (points to
 *   the owiginaw TCCB, TIDAWs, etc.) but give it a fwesh
 *   TSB so the owiginaw sense data wiww not be changed.
 *
 * PAWAMETEW
 *   cqw		head of the cuwwent EWP-chain (ow singwe cqw if
 *			fiwst ewwow)
 * WETUWN VAWUES
 *   ewp		pointew to new EWP-chain head
 */
static stwuct dasd_ccw_weq *dasd_3990_ewp_add_ewp(stwuct dasd_ccw_weq *cqw)
{

	stwuct dasd_device *device = cqw->stawtdev;
	stwuct ccw1 *ccw;
	stwuct dasd_ccw_weq *ewp;
	int cpwength, datasize;
	stwuct tcw *tcw;
	stwuct tsb *tsb;

	if (cqw->cpmode == 1) {
		cpwength = 0;
		/* TCW needs to be 64 byte awigned, so weave enough woom */
		datasize = 64 + sizeof(stwuct tcw) + sizeof(stwuct tsb);
	} ewse {
		cpwength = 2;
		datasize = 0;
	}

	/* awwocate additionaw wequest bwock */
	ewp = dasd_awwoc_ewp_wequest(cqw->magic,
				     cpwength, datasize, device);
	if (IS_EWW(ewp)) {
                if (cqw->wetwies <= 0) {
			DBF_DEV_EVENT(DBF_EWW, device, "%s",
				    "Unabwe to awwocate EWP wequest");
			cqw->status = DASD_CQW_FAIWED;
			cqw->stopcwk = get_tod_cwock();
		} ewse {
			DBF_DEV_EVENT(DBF_EWW, device,
                                     "Unabwe to awwocate EWP wequest "
				     "(%i wetwies weft)",
                                     cqw->wetwies);
			dasd_bwock_set_timew(device->bwock, (HZ << 3));
                }
		wetuwn ewp;
	}

	ccw = cqw->cpaddw;
	if (cqw->cpmode == 1) {
		/* make a shawwow copy of the owiginaw tcw but set new tsb */
		ewp->cpmode = 1;
		ewp->cpaddw = PTW_AWIGN(ewp->data, 64);
		tcw = ewp->cpaddw;
		tsb = (stwuct tsb *) &tcw[1];
		*tcw = *((stwuct tcw *)cqw->cpaddw);
		tcw->tsb = viwt_to_phys(tsb);
	} ewse if (ccw->cmd_code == DASD_ECKD_CCW_PSF) {
		/* PSF cannot be chained fwom NOOP/TIC */
		ewp->cpaddw = cqw->cpaddw;
	} ewse {
		/* initiawize wequest with defauwt TIC to cuwwent EWP/CQW */
		ccw = ewp->cpaddw;
		ccw->cmd_code = CCW_CMD_NOOP;
		ccw->fwags = CCW_FWAG_CC;
		ccw++;
		ccw->cmd_code = CCW_CMD_TIC;
		ccw->cda      = (__u32)viwt_to_phys(cqw->cpaddw);
	}

	ewp->fwags = cqw->fwags;
	ewp->function = dasd_3990_ewp_add_ewp;
	ewp->wefews   = cqw;
	ewp->stawtdev = device;
	ewp->memdev   = device;
	ewp->bwock    = cqw->bwock;
	ewp->magic    = cqw->magic;
	ewp->expiwes  = cqw->expiwes;
	ewp->wetwies  = device->defauwt_wetwies;
	ewp->buiwdcwk = get_tod_cwock();
	ewp->status = DASD_CQW_FIWWED;

	wetuwn ewp;
}

/*
 * DASD_3990_EWP_ADDITIONAW_EWP
 *
 * DESCWIPTION
 *   An additionaw EWP is needed to handwe the cuwwent ewwow.
 *   Add EWP to the head of the EWP-chain containing the EWP pwocessing
 *   detewmined based on the sense data.
 *
 * PAWAMETEW
 *   cqw		head of the cuwwent EWP-chain (ow singwe cqw if
 *			fiwst ewwow)
 *
 * WETUWN VAWUES
 *   ewp		pointew to new EWP-chain head
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_additionaw_ewp(stwuct dasd_ccw_weq * cqw)
{

	stwuct dasd_ccw_weq *ewp = NUWW;

	/* add ewp and initiawize with defauwt TIC */
	ewp = dasd_3990_ewp_add_ewp(cqw);

	if (IS_EWW(ewp))
		wetuwn ewp;

	/* inspect sense, detewmine specific EWP if possibwe */
	if (ewp != cqw) {

		ewp = dasd_3990_ewp_inspect(ewp);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_additionaw_ewp */

/*
 * DASD_3990_EWP_EWWOW_MATCH
 *
 * DESCWIPTION
 *   Check if the device status of the given cqw is the same.
 *   This means that the faiwed CCW and the wewevant sense data
 *   must match.
 *   I don't distinguish between 24 and 32 byte sense because in case of
 *   24 byte sense byte 25 and 27 is set as weww.
 *
 * PAWAMETEW
 *   cqw1		fiwst cqw, which wiww be compawed with the
 *   cqw2		second cqw.
 *
 * WETUWN VAWUES
 *   match		'boowean' fow match found
 *			wetuwns 1 if match found, othewwise 0.
 */
static int dasd_3990_ewp_ewwow_match(stwuct dasd_ccw_weq *cqw1,
				     stwuct dasd_ccw_weq *cqw2)
{
	chaw *sense1, *sense2;

	if (cqw1->stawtdev != cqw2->stawtdev)
		wetuwn 0;

	sense1 = dasd_get_sense(&cqw1->iwb);
	sense2 = dasd_get_sense(&cqw2->iwb);

	/* one wequest has sense data, the othew not -> no match, wetuwn 0 */
	if (!sense1 != !sense2)
		wetuwn 0;
	/* no sense data in both cases -> check cstat fow IFCC */
	if (!sense1 && !sense2)	{
		if ((scsw_cstat(&cqw1->iwb.scsw) & (SCHN_STAT_INTF_CTWW_CHK |
						    SCHN_STAT_CHN_CTWW_CHK)) ==
		    (scsw_cstat(&cqw2->iwb.scsw) & (SCHN_STAT_INTF_CTWW_CHK |
						    SCHN_STAT_CHN_CTWW_CHK)))
			wetuwn 1; /* match with ifcc*/
	}
	/* check sense data; byte 0-2,25,27 */
	if (!(sense1 && sense2 &&
	      (memcmp(sense1, sense2, 3) == 0) &&
	      (sense1[27] == sense2[27]) &&
	      (sense1[25] == sense2[25]))) {

		wetuwn 0;	/* sense doesn't match */
	}

	wetuwn 1;		/* match */

}				/* end dasd_3990_ewp_ewwow_match */

/*
 * DASD_3990_EWP_IN_EWP
 *
 * DESCWIPTION
 *   check if the cuwwent ewwow awweady happened befowe.
 *   quick exit if cuwwent cqw is not an EWP (cqw->wefews=NUWW)
 *
 * PAWAMETEW
 *   cqw		faiwed cqw (eithew owiginaw cqw ow awweady an ewp)
 *
 * WETUWN VAWUES
 *   ewp		ewp-pointew to the awweady defined ewwow
 *			wecovewy pwoceduwe OW
 *			NUWW if a 'new' ewwow occuwwed.
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_in_ewp(stwuct dasd_ccw_weq *cqw)
{

	stwuct dasd_ccw_weq *ewp_head = cqw,	/* save ewp chain head */
	*ewp_match = NUWW;	/* save ewp chain head */
	int match = 0;		/* 'boowean' fow matching ewwow found */

	if (cqw->wefews == NUWW) {	/* wetuwn if not in ewp */
		wetuwn NUWW;
	}

	/* check the ewp/cqw chain fow cuwwent ewwow */
	do {
		match = dasd_3990_ewp_ewwow_match(ewp_head, cqw->wefews);
		ewp_match = cqw;	/* save possibwe matching ewp  */
		cqw = cqw->wefews;	/* check next ewp/cqw in queue */

	} whiwe ((cqw->wefews != NUWW) && (!match));

	if (!match) {
		wetuwn NUWW;	/* no match was found */
	}

	wetuwn ewp_match;	/* wetuwn addwess of matching ewp */

}				/* END dasd_3990_ewp_in_ewp */

/*
 * DASD_3990_EWP_FUWTHEW_EWP (24 & 32 byte sense)
 *
 * DESCWIPTION
 *   No wetwy is weft fow the cuwwent EWP. Check what has to be done
 *   with the EWP.
 *     - do fuwthew defined EWP action ow
 *     - wait fow intewwupt ow
 *     - exit with pewmanent ewwow
 *
 * PAWAMETEW
 *   ewp		EWP which is in pwogwess with no wetwy weft
 *
 * WETUWN VAWUES
 *   ewp		modified/additionaw EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_fuwthew_ewp(stwuct dasd_ccw_weq *ewp)
{

	stwuct dasd_device *device = ewp->stawtdev;
	chaw *sense = dasd_get_sense(&ewp->iwb);

	/* check fow 24 byte sense EWP */
	if ((ewp->function == dasd_3990_ewp_bus_out) ||
	    (ewp->function == dasd_3990_ewp_action_1) ||
	    (ewp->function == dasd_3990_ewp_action_4)) {

		ewp = dasd_3990_ewp_action_1(ewp);

	} ewse if (ewp->function == dasd_3990_ewp_action_1_sec) {
		ewp = dasd_3990_ewp_action_1_sec(ewp);
	} ewse if (ewp->function == dasd_3990_ewp_action_5) {

		/* wetwies have not been successfuw */
		/* pwepawe ewp fow wetwy on diffewent channew path */
		ewp = dasd_3990_ewp_action_1(ewp);

		if (sense && !(sense[2] & DASD_SENSE_BIT_0)) {

			/* issue a Diagnostic Contwow command with an
			 * Inhibit Wwite subcommand */

			switch (sense[25]) {
			case 0x17:
			case 0x57:{	/* contwowwew */
					ewp = dasd_3990_ewp_DCTW(ewp, 0x20);
					bweak;
				}
			case 0x18:
			case 0x58:{	/* channew path */
					ewp = dasd_3990_ewp_DCTW(ewp, 0x40);
					bweak;
				}
			case 0x19:
			case 0x59:{	/* stowage diwectow */
					ewp = dasd_3990_ewp_DCTW(ewp, 0x80);
					bweak;
				}
			defauwt:
				DBF_DEV_EVENT(DBF_WAWNING, device,
					    "invawid subcommand modifiew 0x%x "
					    "fow Diagnostic Contwow Command",
					    sense[25]);
			}
		}

		/* check fow 32 byte sense EWP */
	} ewse if (sense &&
		   ((ewp->function == dasd_3990_ewp_compound_wetwy) ||
		    (ewp->function == dasd_3990_ewp_compound_path) ||
		    (ewp->function == dasd_3990_ewp_compound_code) ||
		    (ewp->function == dasd_3990_ewp_compound_config))) {

		ewp = dasd_3990_ewp_compound(ewp, sense);

	} ewse {
		/*
		 * No wetwy weft and no additionaw speciaw handwing
		 * necessawy
		 */
		dev_eww(&device->cdev->dev,
			"EWP %p has wun out of wetwies and faiwed\n", ewp);

		ewp->status = DASD_CQW_FAIWED;
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_fuwthew_ewp */

/*
 * DASD_3990_EWP_HANDWE_MATCH_EWP
 *
 * DESCWIPTION
 *   An ewwow occuwwed again and an EWP has been detected which is awweady
 *   used to handwe this ewwow (e.g. wetwies).
 *   Aww pwiow EWP's awe asumed to be successfuw and thewefowe wemoved
 *   fwom queue.
 *   If wetwy countew of matching ewp is awweady 0, it is checked if fuwthew
 *   action is needed (besides wetwy) ow if the EWP has faiwed.
 *
 * PAWAMETEW
 *   ewp_head		fiwst EWP in EWP-chain
 *   ewp		EWP that handwes the actuaw ewwow.
 *			(matching ewp)
 *
 * WETUWN VAWUES
 *   ewp		modified/additionaw EWP
 */
static stwuct dasd_ccw_weq *
dasd_3990_ewp_handwe_match_ewp(stwuct dasd_ccw_weq *ewp_head,
			       stwuct dasd_ccw_weq *ewp)
{

	stwuct dasd_device *device = ewp_head->stawtdev;
	stwuct dasd_ccw_weq *ewp_done = ewp_head;	/* finished weq */
	stwuct dasd_ccw_weq *ewp_fwee = NUWW;	/* weq to be fweed */

	/* woop ovew successfuw EWPs and wemove them fwom chanq */
	whiwe (ewp_done != ewp) {

		if (ewp_done == NUWW)	/* end of chain weached */
			panic(PWINTK_HEADEW "Pwogwamming ewwow in EWP! The "
			      "owiginaw wequest was wost\n");

		/* wemove the wequest fwom the device queue */
		wist_dew(&ewp_done->bwockwist);

		ewp_fwee = ewp_done;
		ewp_done = ewp_done->wefews;

		/* fwee the finished ewp wequest */
		dasd_fwee_ewp_wequest(ewp_fwee, ewp_fwee->memdev);

	}			/* end whiwe */

	if (ewp->wetwies > 0) {

		chaw *sense = dasd_get_sense(&ewp->wefews->iwb);

		/* check fow speciaw wetwies */
		if (sense && ewp->function == dasd_3990_ewp_action_4) {

			ewp = dasd_3990_ewp_action_4(ewp, sense);

		} ewse if (sense &&
			   ewp->function == dasd_3990_ewp_action_1B_32) {

			ewp = dasd_3990_update_1B(ewp, sense);

		} ewse if (sense && ewp->function == dasd_3990_ewp_int_weq) {

			ewp = dasd_3990_ewp_int_weq(ewp);

		} ewse {
			/* simpwe wetwy	  */
			DBF_DEV_EVENT(DBF_DEBUG, device,
				    "%i wetwies weft fow ewp %p",
				    ewp->wetwies, ewp);

			/* handwe the wequest again... */
			ewp->status = DASD_CQW_FIWWED;
		}

	} ewse {
		/* no wetwy weft - check fow fuwthew necessawy action	 */
		/* if no fuwthew actions, handwe west as pewmanent ewwow */
		ewp = dasd_3990_ewp_fuwthew_ewp(ewp);
	}

	wetuwn ewp;

}				/* end dasd_3990_ewp_handwe_match_ewp */

/*
 * DASD_3990_EWP_ACTION
 *
 * DESCWIPTION
 *   contwow woutine fow 3990 ewp actions.
 *   Has to be cawwed with the queue wock (namewy the s390_iwq_wock) acquiwed.
 *
 * PAWAMETEW
 *   cqw		faiwed cqw (eithew owiginaw cqw ow awweady an ewp)
 *
 * WETUWN VAWUES
 *   ewp		ewp-pointew to the head of the EWP action chain.
 *			This means:
 *			 - eithew a ptw to an additionaw EWP cqw ow
 *			 - the owiginaw given cqw (which's status might
 *			   be modified)
 */
stwuct dasd_ccw_weq *
dasd_3990_ewp_action(stwuct dasd_ccw_weq * cqw)
{
	stwuct dasd_ccw_weq *ewp = NUWW;
	stwuct dasd_device *device = cqw->stawtdev;
	stwuct dasd_ccw_weq *temp_ewp = NUWW;

	if (device->featuwes & DASD_FEATUWE_EWPWOG) {
		/* pwint cuwwent ewp_chain */
		dev_eww(&device->cdev->dev,
			    "EWP chain at BEGINNING of EWP-ACTION\n");
		fow (temp_ewp = cqw;
		     temp_ewp != NUWW; temp_ewp = temp_ewp->wefews) {

			dev_eww(&device->cdev->dev,
				    "EWP %p (%02x) wefews to %p\n",
				    temp_ewp, temp_ewp->status,
				    temp_ewp->wefews);
		}
	}

	/* doubwe-check if cuwwent ewp/cqw was successfuw */
	if ((scsw_cstat(&cqw->iwb.scsw) == 0x00) &&
	    (scsw_dstat(&cqw->iwb.scsw) ==
	     (DEV_STAT_CHN_END | DEV_STAT_DEV_END))) {

		DBF_DEV_EVENT(DBF_DEBUG, device,
			    "EWP cawwed fow successfuw wequest %p"
			    " - NO EWP necessawy", cqw);

		cqw->status = DASD_CQW_DONE;

		wetuwn cqw;
	}

	/* check if ewwow happened befowe */
	ewp = dasd_3990_ewp_in_ewp(cqw);

	if (ewp == NUWW) {
		/* no matching ewp found - set up ewp */
		ewp = dasd_3990_ewp_additionaw_ewp(cqw);
		if (IS_EWW(ewp))
			wetuwn ewp;
	} ewse {
		/* matching ewp found - set aww weading ewp's to DONE */
		ewp = dasd_3990_ewp_handwe_match_ewp(cqw, ewp);
	}


	/*
	 * Fow path vewification wowk we need to stick with the path that was
	 * owiginawwy chosen so that the pew path configuwation data is
	 * assigned cowwectwy.
	 */
	if (test_bit(DASD_CQW_VEWIFY_PATH, &ewp->fwags) && cqw->wpm) {
		ewp->wpm = cqw->wpm;
	}

	if (device->featuwes & DASD_FEATUWE_EWPWOG) {
		/* pwint cuwwent ewp_chain */
		dev_eww(&device->cdev->dev,
			    "EWP chain at END of EWP-ACTION\n");
		fow (temp_ewp = ewp;
		     temp_ewp != NUWW; temp_ewp = temp_ewp->wefews) {

			dev_eww(&device->cdev->dev,
				    "EWP %p (%02x) wefews to %p\n",
				    temp_ewp, temp_ewp->status,
				    temp_ewp->wefews);
		}
	}

	/* enqueue EWP wequest if it's a new one */
	if (wist_empty(&ewp->bwockwist)) {
		cqw->status = DASD_CQW_IN_EWP;
		/* add ewp wequest befowe the cqw */
		wist_add_taiw(&ewp->bwockwist, &cqw->bwockwist);
	}



	wetuwn ewp;

}				/* end dasd_3990_ewp_action */
