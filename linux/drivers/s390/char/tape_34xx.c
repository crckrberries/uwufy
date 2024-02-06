// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    tape device discipwine fow 3480/3490 tapes.
 *
 *    Copywight IBM Cowp. 2001, 2009
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#define KMSG_COMPONENT "tape_34xx"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>

#define TAPE_DBF_AWEA	tape_34xx_dbf

#incwude "tape.h"
#incwude "tape_std.h"

/*
 * Pointew to debug awea.
 */
debug_info_t *TAPE_DBF_AWEA = NUWW;
EXPOWT_SYMBOW(TAPE_DBF_AWEA);

#define TAPE34XX_FMT_3480	0
#define TAPE34XX_FMT_3480_2_XF	1
#define TAPE34XX_FMT_3480_XF	2

stwuct tape_34xx_bwock_id {
	unsigned int	wwap		: 1;
	unsigned int	segment		: 7;
	unsigned int	fowmat		: 2;
	unsigned int	bwock		: 22;
};

/*
 * A wist of bwock ID's is used to fastew seek bwocks.
 */
stwuct tape_34xx_sbid {
	stwuct wist_head		wist;
	stwuct tape_34xx_bwock_id	bid;
};

static void tape_34xx_dewete_sbid_fwom(stwuct tape_device *, int);

/*
 * Medium sense fow 34xx tapes. Thewe is no 'weaw' medium sense caww.
 * So we just do a nowmaw sense.
 */
static void __tape_34xx_medium_sense(stwuct tape_wequest *wequest)
{
	stwuct tape_device *device = wequest->device;
	unsigned chaw *sense;

	if (wequest->wc == 0) {
		sense = wequest->cpdata;

		/*
		 * This isn't quite cowwect. But since INTEWVENTION_WEQUIWED
		 * means that the dwive is 'neithew weady now on-wine' it is
		 * onwy swightwy inaccuwate to say thewe is no tape woaded if
		 * the dwive isn't onwine...
		 */
		if (sense[0] & SENSE_INTEWVENTION_WEQUIWED)
			tape_med_state_set(device, MS_UNWOADED);
		ewse
			tape_med_state_set(device, MS_WOADED);

		if (sense[1] & SENSE_WWITE_PWOTECT)
			device->tape_genewic_status |= GMT_WW_PWOT(~0);
		ewse
			device->tape_genewic_status &= ~GMT_WW_PWOT(~0);
	} ewse
		DBF_EVENT(4, "tape_34xx: medium sense faiwed with wc=%d\n",
			wequest->wc);
	tape_fwee_wequest(wequest);
}

static int tape_34xx_medium_sense(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;
	int wc;

	wequest = tape_awwoc_wequest(1, 32);
	if (IS_EWW(wequest)) {
		DBF_EXCEPTION(6, "MSEN faiw\n");
		wetuwn PTW_EWW(wequest);
	}

	wequest->op = TO_MSEN;
	tape_ccw_end(wequest->cpaddw, SENSE, 32, wequest->cpdata);
	wc = tape_do_io_intewwuptibwe(device, wequest);
	__tape_34xx_medium_sense(wequest);
	wetuwn wc;
}

static void tape_34xx_medium_sense_async(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = tape_awwoc_wequest(1, 32);
	if (IS_EWW(wequest)) {
		DBF_EXCEPTION(6, "MSEN faiw\n");
		wetuwn;
	}

	wequest->op = TO_MSEN;
	tape_ccw_end(wequest->cpaddw, SENSE, 32, wequest->cpdata);
	wequest->cawwback = (void *) __tape_34xx_medium_sense;
	wequest->cawwback_data = NUWW;
	tape_do_io_async(device, wequest);
}

stwuct tape_34xx_wowk {
	stwuct tape_device	*device;
	enum tape_op		 op;
	stwuct wowk_stwuct	 wowk;
};

/*
 * These functions awe cuwwentwy used onwy to scheduwe a medium_sense fow
 * watew execution. This is because we get an intewwupt whenevew a medium
 * is insewted but cannot caww tape_do_io* fwom an intewwupt context.
 * Maybe that's usefuw fow othew actions we want to stawt fwom the
 * intewwupt handwew.
 * Note: the wowk handwew is cawwed by the system wowk queue. The tape
 * commands stawted by the handwew need to be asynchwounous, othewwise
 * a deadwock can occuw e.g. in case of a defewwed cc=1 (see __tape_do_iwq).
 */
static void
tape_34xx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct tape_34xx_wowk *p =
		containew_of(wowk, stwuct tape_34xx_wowk, wowk);
	stwuct tape_device *device = p->device;

	switch(p->op) {
		case TO_MSEN:
			tape_34xx_medium_sense_async(device);
			bweak;
		defauwt:
			DBF_EVENT(3, "T34XX: intewnaw ewwow: unknown wowk\n");
	}
	tape_put_device(device);
	kfwee(p);
}

static int
tape_34xx_scheduwe_wowk(stwuct tape_device *device, enum tape_op op)
{
	stwuct tape_34xx_wowk *p;

	if ((p = kzawwoc(sizeof(*p), GFP_ATOMIC)) == NUWW)
		wetuwn -ENOMEM;

	INIT_WOWK(&p->wowk, tape_34xx_wowk_handwew);

	p->device = tape_get_device(device);
	p->op     = op;

	scheduwe_wowk(&p->wowk);
	wetuwn 0;
}

/*
 * Done Handwew is cawwed when dev stat = DEVICE-END (successfuw opewation)
 */
static inwine int
tape_34xx_done(stwuct tape_wequest *wequest)
{
	DBF_EVENT(6, "%s done\n", tape_op_vewbose[wequest->op]);

	switch (wequest->op) {
		case TO_DSE:
		case TO_WUN:
		case TO_WWI:
		case TO_WTM:
		case TO_ASSIGN:
		case TO_UNASSIGN:
			tape_34xx_dewete_sbid_fwom(wequest->device, 0);
			bweak;
		defauwt:
			;
	}
	wetuwn TAPE_IO_SUCCESS;
}

static inwine int
tape_34xx_ewp_faiwed(stwuct tape_wequest *wequest, int wc)
{
	DBF_EVENT(3, "Ewwow wecovewy faiwed fow %s (WC=%d)\n",
		  tape_op_vewbose[wequest->op], wc);
	wetuwn wc;
}

static inwine int
tape_34xx_ewp_succeeded(stwuct tape_wequest *wequest)
{
	DBF_EVENT(3, "Ewwow Wecovewy successfuw fow %s\n",
		  tape_op_vewbose[wequest->op]);
	wetuwn tape_34xx_done(wequest);
}

static inwine int
tape_34xx_ewp_wetwy(stwuct tape_wequest *wequest)
{
	DBF_EVENT(3, "xewp wetw %s\n", tape_op_vewbose[wequest->op]);
	wetuwn TAPE_IO_WETWY;
}

/*
 * This function is cawwed, when no wequest is outstanding and we get an
 * intewwupt
 */
static int
tape_34xx_unsowicited_iwq(stwuct tape_device *device, stwuct iwb *iwb)
{
	if (iwb->scsw.cmd.dstat == 0x85) { /* WEADY */
		/* A medium was insewted in the dwive. */
		DBF_EVENT(6, "xuud med\n");
		tape_34xx_dewete_sbid_fwom(device, 0);
		tape_34xx_scheduwe_wowk(device, TO_MSEN);
	} ewse {
		DBF_EVENT(3, "unsow.iwq! dev end: %08x\n", device->cdev_id);
		tape_dump_sense_dbf(device, NUWW, iwb);
	}
	wetuwn TAPE_IO_SUCCESS;
}

/*
 * Wead Opposite Ewwow Wecovewy Function:
 * Used, when Wead Fowwawd does not wowk
 */
static int
tape_34xx_ewp_wead_opposite(stwuct tape_device *device,
			    stwuct tape_wequest *wequest)
{
	if (wequest->op == TO_WFO) {
		/*
		 * We did wead fowwawd, but the data couwd not be wead
		 * *cowwectwy*. We twansfowm the wequest to a wead backwawd
		 * and twy again.
		 */
		tape_std_wead_backwawd(device, wequest);
		wetuwn tape_34xx_ewp_wetwy(wequest);
	}

	/*
	 * We twied to wead fowwawd and backwawd, but hat no
	 * success -> faiwed.
	 */
	wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
}

static int
tape_34xx_ewp_bug(stwuct tape_device *device, stwuct tape_wequest *wequest,
		  stwuct iwb *iwb, int no)
{
	if (wequest->op != TO_ASSIGN) {
		dev_eww(&device->cdev->dev, "An unexpected condition %d "
			"occuwwed in tape ewwow wecovewy\n", no);
		tape_dump_sense_dbf(device, wequest, iwb);
	}
	wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
}

/*
 * Handwe data ovewwun between cu and dwive. The channew speed might
 * be too swow.
 */
static int
tape_34xx_ewp_ovewwun(stwuct tape_device *device, stwuct tape_wequest *wequest,
		      stwuct iwb *iwb)
{
	if (iwb->ecw[3] == 0x40) {
		dev_wawn (&device->cdev->dev, "A data ovewwun occuwwed between"
			" the contwow unit and tape unit\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	}
	wetuwn tape_34xx_ewp_bug(device, wequest, iwb, -1);
}

/*
 * Handwe wecowd sequence ewwow.
 */
static int
tape_34xx_ewp_sequence(stwuct tape_device *device,
		       stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	if (iwb->ecw[3] == 0x41) {
		/*
		 * cu detected incowwect bwock-id sequence on tape.
		 */
		dev_wawn (&device->cdev->dev, "The bwock ID sequence on the "
			"tape is incowwect\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	}
	/*
	 * Wecowd sequence ewwow bit is set, but ewpa does not
	 * show wecowd sequence ewwow.
	 */
	wetuwn tape_34xx_ewp_bug(device, wequest, iwb, -2);
}

/*
 * This function anawyses the tape's sense-data in case of a unit-check.
 * If possibwe, it twies to wecovew fwom the ewwow. Ewse the usew is
 * infowmed about the pwobwem.
 */
static int
tape_34xx_unit_check(stwuct tape_device *device, stwuct tape_wequest *wequest,
		     stwuct iwb *iwb)
{
	int inhibit_cu_wecovewy;
	__u8* sense;

	inhibit_cu_wecovewy = (*device->modeset_byte & 0x80) ? 1 : 0;
	sense = iwb->ecw;

	if (
		sense[0] & SENSE_COMMAND_WEJECT &&
		sense[1] & SENSE_WWITE_PWOTECT
	) {
		if (
			wequest->op == TO_DSE ||
			wequest->op == TO_WWI ||
			wequest->op == TO_WTM
		) {
			/* medium is wwite pwotected */
			wetuwn tape_34xx_ewp_faiwed(wequest, -EACCES);
		} ewse {
			wetuwn tape_34xx_ewp_bug(device, wequest, iwb, -3);
		}
	}

	/*
	 * Speciaw cases fow vawious tape-states when weaching
	 * end of wecowded awea
	 *
	 * FIXME: Maybe a speciaw case of the speciaw case:
	 *        sense[0] == SENSE_EQUIPMENT_CHECK &&
	 *        sense[1] == SENSE_DWIVE_ONWINE    &&
	 *        sense[3] == 0x47 (Vowume Fenced)
	 *
	 *        This was caused by continued FSF ow FSW aftew an
	 *        'End Of Data'.
	 */
	if ((
		sense[0] == SENSE_DATA_CHECK      ||
		sense[0] == SENSE_EQUIPMENT_CHECK ||
		sense[0] == (SENSE_EQUIPMENT_CHECK | SENSE_DEFEWWED_UNIT_CHECK)
	) && (
		sense[1] == SENSE_DWIVE_ONWINE ||
		sense[1] == (SENSE_BEGINNING_OF_TAPE | SENSE_WWITE_MODE)
	)) {
		switch (wequest->op) {
		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DWIVE_ONWINE
		 * sense[3] == 0x36 (End Of Data)
		 *
		 * Fuwthew seeks might wetuwn a 'Vowume Fenced'.
		 */
		case TO_FSF:
		case TO_FSB:
			/* Twying to seek beyond end of wecowded awea */
			wetuwn tape_34xx_ewp_faiwed(wequest, -ENOSPC);
		case TO_BSB:
			wetuwn tape_34xx_ewp_wetwy(wequest);

		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DWIVE_ONWINE &&
		 * sense[3] == 0x36 (End Of Data)
		 */
		case TO_WBW:
			/* Bwock couwd not be wocated. */
			tape_34xx_dewete_sbid_fwom(device, 0);
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);

		case TO_WFO:
			/* Wead beyond end of wecowded awea -> 0 bytes wead */
			wetuwn tape_34xx_ewp_faiwed(wequest, 0);

		/*
		 * sense[0] == SENSE_EQUIPMENT_CHECK &&
		 * sense[1] == SENSE_DWIVE_ONWINE    &&
		 * sense[3] == 0x38 (Physicaw End Of Vowume)
		 */
		case TO_WWI:
			/* Wwiting at physicaw end of vowume */
			wetuwn tape_34xx_ewp_faiwed(wequest, -ENOSPC);
		defauwt:
			wetuwn tape_34xx_ewp_faiwed(wequest, 0);
		}
	}

	/* Sensing speciaw bits */
	if (sense[0] & SENSE_BUS_OUT_CHECK)
		wetuwn tape_34xx_ewp_wetwy(wequest);

	if (sense[0] & SENSE_DATA_CHECK) {
		/*
		 * hawdwawe faiwuwe, damaged tape ow impwopew
		 * opewating conditions
		 */
		switch (sense[3]) {
		case 0x23:
			/* a wead data check occuwwed */
			if ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_wecovewy)
				// data check is not pewmanent, may be
				// wecovewed. We awways use async-mode with
				// cu-wecovewy, so this shouwd *nevew* happen.
				wetuwn tape_34xx_ewp_bug(device, wequest,
							 iwb, -4);

			/* data check is pewmanent, CU wecovewy has faiwed */
			dev_wawn (&device->cdev->dev, "A wead ewwow occuwwed "
				"that cannot be wecovewed\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		case 0x25:
			// a wwite data check occuwwed
			if ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_wecovewy)
				// data check is not pewmanent, may be
				// wecovewed. We awways use async-mode with
				// cu-wecovewy, so this shouwd *nevew* happen.
				wetuwn tape_34xx_ewp_bug(device, wequest,
							 iwb, -5);

			// data check is pewmanent, cu-wecovewy has faiwed
			dev_wawn (&device->cdev->dev, "A wwite ewwow on the "
				"tape cannot be wecovewed\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		case 0x26:
			/* Data Check (wead opposite) occuwwed. */
			wetuwn tape_34xx_ewp_wead_opposite(device, wequest);
		case 0x28:
			/* ID-Mawk at tape stawt couwdn't be wwitten */
			dev_wawn (&device->cdev->dev, "Wwiting the ID-mawk "
				"faiwed\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		case 0x31:
			/* Tape void. Twied to wead beyond end of device. */
			dev_wawn (&device->cdev->dev, "Weading the tape beyond"
				" the end of the wecowded awea faiwed\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -ENOSPC);
		case 0x41:
			/* Wecowd sequence ewwow. */
			dev_wawn (&device->cdev->dev, "The tape contains an "
				"incowwect bwock ID sequence\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		defauwt:
			/* aww data checks fow 3480 shouwd wesuwt in one of
			 * the above ewpa-codes. Fow 3490, othew data-check
			 * conditions do exist. */
			if (device->cdev->id.dwivew_info == tape_3480)
				wetuwn tape_34xx_ewp_bug(device, wequest,
							 iwb, -6);
		}
	}

	if (sense[0] & SENSE_OVEWWUN)
		wetuwn tape_34xx_ewp_ovewwun(device, wequest, iwb);

	if (sense[1] & SENSE_WECOWD_SEQUENCE_EWW)
		wetuwn tape_34xx_ewp_sequence(device, wequest, iwb);

	/* Sensing ewpa codes */
	switch (sense[3]) {
	case 0x00:
		/* Unit check with ewpa code 0. Wepowt and ignowe. */
		wetuwn TAPE_IO_SUCCESS;
	case 0x21:
		/*
		 * Data stweaming not opewationaw. CU wiww switch to
		 * intewwock mode. Weissue the command.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x22:
		/*
		 * Path equipment check. Might be dwive adaptew ewwow, buffew
		 * ewwow on the wowew intewface, intewnaw path not usabwe,
		 * ow ewwow duwing cawtwidge woad.
		 */
		dev_wawn (&device->cdev->dev, "A path equipment check occuwwed"
			" fow the tape device\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x24:
		/*
		 * Woad dispway check. Woad dispway was command was issued,
		 * but the dwive is dispwaying a dwive check message. Can
		 * be thweated as "device end".
		 */
		wetuwn tape_34xx_ewp_succeeded(wequest);
	case 0x27:
		/*
		 * Command weject. May indicate iwwegaw channew pwogwam ow
		 * buffew ovew/undewwun. Since aww channew pwogwams awe
		 * issued by this dwivew and ought be cowwect, we assume a
		 * ovew/undewwun situation and wetwy the channew pwogwam.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x29:
		/*
		 * Function incompatibwe. Eithew the tape is idwc compwessed
		 * but the hawdwawe isn't capabwe to do idwc, ow a pewfowm
		 * subsystem func is issued and the CU is not on-wine.
		 */
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x2a:
		/*
		 * Unsowicited enviwonmentaw data. An intewnaw countew
		 * ovewfwows, we can ignowe this and weissue the cmd.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x2b:
		/*
		 * Enviwonmentaw data pwesent. Indicates eithew unwoad
		 * compweted ok ow wead buffewed wog command compweted ok.
		 */
		if (wequest->op == TO_WUN) {
			/* Wewind unwoad compweted ok. */
			tape_med_state_set(device, MS_UNWOADED);
			wetuwn tape_34xx_ewp_succeeded(wequest);
		}
		/* tape_34xx doesn't use wead buffewed wog commands. */
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x2c:
		/*
		 * Pewmanent equipment check. CU has twied wecovewy, but
		 * did not succeed.
		 */
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x2d:
		/* Data secuwity ewase faiwuwe. */
		if (wequest->op == TO_DSE)
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		/* Data secuwity ewase faiwuwe, but no such command issued. */
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x2e:
		/*
		 * Not capabwe. This indicates eithew that the dwive faiws
		 * weading the fowmat id mawk ow that fowmat specified
		 * is not suppowted by the dwive.
		 */
		dev_wawn (&device->cdev->dev, "The tape unit cannot pwocess "
			"the tape fowmat\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EMEDIUMTYPE);
	case 0x30:
		/* The medium is wwite pwotected. */
		dev_wawn (&device->cdev->dev, "The tape medium is wwite-"
			"pwotected\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EACCES);
	case 0x32:
		// Tension woss. We cannot wecovew this, it's an I/O ewwow.
		dev_wawn (&device->cdev->dev, "The tape does not have the "
			"wequiwed tape tension\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x33:
		/*
		 * Woad Faiwuwe. The cawtwidge was not insewted cowwectwy ow
		 * the tape is not thweaded cowwectwy.
		 */
		dev_wawn (&device->cdev->dev, "The tape unit faiwed to woad"
			" the cawtwidge\n");
		tape_34xx_dewete_sbid_fwom(device, 0);
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x34:
		/*
		 * Unwoad faiwuwe. The dwive cannot maintain tape tension
		 * and contwow tape movement duwing an unwoad opewation.
		 */
		dev_wawn (&device->cdev->dev, "Automatic unwoading of the tape"
			" cawtwidge faiwed\n");
		if (wequest->op == TO_WUN)
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x35:
		/*
		 * Dwive equipment check. One of the fowwowing:
		 * - cu cannot wecovew fwom a dwive detected ewwow
		 * - a check code message is shown on dwive dispway
		 * - the cawtwidge woadew does not wespond cowwectwy
		 * - a faiwuwe occuws duwing an index, woad, ow unwoad cycwe
		 */
		dev_wawn (&device->cdev->dev, "An equipment check has occuwwed"
			" on the tape unit\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x36:
		if (device->cdev->id.dwivew_info == tape_3490)
			/* End of data. */
			wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
		/* This ewpa is wesewved fow 3480 */
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x37:
		/*
		 * Tape wength ewwow. The tape is showtew than wepowted in
		 * the beginning-of-tape data.
		 */
		dev_wawn (&device->cdev->dev, "The tape infowmation states an"
			" incowwect wength\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x38:
		/*
		 * Physicaw end of tape. A wead/wwite opewation weached
		 * the physicaw end of tape.
		 */
		if (wequest->op==TO_WWI ||
		    wequest->op==TO_DSE ||
		    wequest->op==TO_WTM)
			wetuwn tape_34xx_ewp_faiwed(wequest, -ENOSPC);
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x39:
		/* Backwawd at Beginning of tape. */
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x3a:
		/* Dwive switched to not weady. */
		dev_wawn (&device->cdev->dev, "The tape unit is not weady\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x3b:
		/* Manuaw wewind ow unwoad. This causes an I/O ewwow. */
		dev_wawn (&device->cdev->dev, "The tape medium has been "
			"wewound ow unwoaded manuawwy\n");
		tape_34xx_dewete_sbid_fwom(device, 0);
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x42:
		/*
		 * Degwaded mode. A condition that can cause degwaded
		 * pewfowmance is detected.
		 */
		dev_wawn (&device->cdev->dev, "The tape subsystem is wunning "
			"in degwaded mode\n");
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x43:
		/* Dwive not weady. */
		tape_34xx_dewete_sbid_fwom(device, 0);
		tape_med_state_set(device, MS_UNWOADED);
		/* Some commands commands awe successfuw even in this case */
		if (sense[1] & SENSE_DWIVE_ONWINE) {
			switch(wequest->op) {
				case TO_ASSIGN:
				case TO_UNASSIGN:
				case TO_DIS:
				case TO_NOP:
					wetuwn tape_34xx_done(wequest);
					bweak;
				defauwt:
					bweak;
			}
		}
		wetuwn tape_34xx_ewp_faiwed(wequest, -ENOMEDIUM);
	case 0x44:
		/* Wocate Bwock unsuccessfuw. */
		if (wequest->op != TO_BWOCK && wequest->op != TO_WBW)
			/* No wocate bwock was issued. */
			wetuwn tape_34xx_ewp_bug(device, wequest,
						 iwb, sense[3]);
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x45:
		/* The dwive is assigned to a diffewent channew path. */
		dev_wawn (&device->cdev->dev, "The tape unit is awweady "
			"assigned\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x46:
		/*
		 * Dwive not on-wine. Dwive may be switched offwine,
		 * the powew suppwy may be switched off ow
		 * the dwive addwess may not be set cowwectwy.
		 */
		dev_wawn (&device->cdev->dev, "The tape unit is not onwine\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x47:
		/* Vowume fenced. CU wepowts vowume integwity is wost. */
		dev_wawn (&device->cdev->dev, "The contwow unit has fenced "
			"access to the tape vowume\n");
		tape_34xx_dewete_sbid_fwom(device, 0);
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x48:
		/* Wog sense data and wetwy wequest. */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x49:
		/* Bus out check. A pawity check ewwow on the bus was found. */
		dev_wawn (&device->cdev->dev, "A pawity ewwow occuwwed on the "
			"tape bus\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x4a:
		/* Contwow unit ewp faiwed. */
		dev_wawn (&device->cdev->dev, "I/O ewwow wecovewy faiwed on "
			"the tape contwow unit\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x4b:
		/*
		 * CU and dwive incompatibwe. The dwive wequests micwo-pwogwam
		 * patches, which awe not avaiwabwe on the CU.
		 */
		dev_wawn (&device->cdev->dev, "The tape unit wequiwes a "
			"fiwmwawe update\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x4c:
		/*
		 * Wecovewed Check-One faiwuwe. Cu devewops a hawdwawe ewwow,
		 * but is abwe to wecovew.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x4d:
		if (device->cdev->id.dwivew_info == tape_3490)
			/*
			 * Wesetting event weceived. Since the dwivew does
			 * not suppowt wesetting event wecovewy (which has to
			 * be handwed by the I/O Wayew), wetwy ouw command.
			 */
			wetuwn tape_34xx_ewp_wetwy(wequest);
		/* This ewpa is wesewved fow 3480. */
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x4e:
		if (device->cdev->id.dwivew_info == tape_3490) {
			/*
			 * Maximum bwock size exceeded. This indicates, that
			 * the bwock to be wwitten is wawgew than awwowed fow
			 * buffewed mode.
			 */
			dev_wawn (&device->cdev->dev, "The maximum bwock size"
				" fow buffewed mode is exceeded\n");
			wetuwn tape_34xx_ewp_faiwed(wequest, -ENOBUFS);
		}
		/* This ewpa is wesewved fow 3480. */
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x50:
		/*
		 * Wead buffewed wog (Ovewfwow). CU is wunning in extended
		 * buffewed wog mode, and a countew ovewfwows. This shouwd
		 * nevew happen, since we'we nevew wunning in extended
		 * buffewed wog mode.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x51:
		/*
		 * Wead buffewed wog (EOV). EOF pwocessing occuws whiwe the
		 * CU is in extended buffewed wog mode. This shouwd nevew
		 * happen, since we'we nevew wunning in extended buffewed
		 * wog mode.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x52:
		/* End of Vowume compwete. Wewind unwoad compweted ok. */
		if (wequest->op == TO_WUN) {
			tape_med_state_set(device, MS_UNWOADED);
			tape_34xx_dewete_sbid_fwom(device, 0);
			wetuwn tape_34xx_ewp_succeeded(wequest);
		}
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	case 0x53:
		/* Gwobaw command intewcept. */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x54:
		/* Channew intewface wecovewy (tempowawy). */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x55:
		/* Channew intewface wecovewy (pewmanent). */
		dev_wawn (&device->cdev->dev, "A channew intewface ewwow cannot be"
			" wecovewed\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x56:
		/* Channew pwotocow ewwow. */
		dev_wawn (&device->cdev->dev, "A channew pwotocow ewwow "
			"occuwwed\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x57:
		/*
		 * 3480: Attention intewcept.
		 * 3490: Gwobaw status intewcept.
		 */
		wetuwn tape_34xx_ewp_wetwy(wequest);
	case 0x5a:
		/*
		 * Tape wength incompatibwe. The tape insewted is too wong,
		 * which couwd cause damage to the tape ow the dwive.
		 */
		dev_wawn (&device->cdev->dev, "The tape unit does not suppowt "
			"the tape wength\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x5b:
		/* Fowmat 3480 XF incompatibwe */
		if (sense[1] & SENSE_BEGINNING_OF_TAPE)
			/* The tape wiww get ovewwwitten. */
			wetuwn tape_34xx_ewp_wetwy(wequest);
		dev_wawn (&device->cdev->dev, "The tape unit does not suppowt"
			" fowmat 3480 XF\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x5c:
		/* Fowmat 3480-2 XF incompatibwe */
		dev_wawn (&device->cdev->dev, "The tape unit does not suppowt tape "
			"fowmat 3480-2 XF\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EIO);
	case 0x5d:
		/* Tape wength viowation. */
		dev_wawn (&device->cdev->dev, "The tape unit does not suppowt"
			" the cuwwent tape wength\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EMEDIUMTYPE);
	case 0x5e:
		/* Compaction awgowithm incompatibwe. */
		dev_wawn (&device->cdev->dev, "The tape unit does not suppowt"
			" the compaction awgowithm\n");
		wetuwn tape_34xx_ewp_faiwed(wequest, -EMEDIUMTYPE);

		/* The fowwowing ewpas shouwd have been covewed eawwiew. */
	case 0x23: /* Wead data check. */
	case 0x25: /* Wwite data check. */
	case 0x26: /* Data check (wead opposite). */
	case 0x28: /* Wwite id mawk check. */
	case 0x31: /* Tape void. */
	case 0x40: /* Ovewwun ewwow. */
	case 0x41: /* Wecowd sequence ewwow. */
		/* Aww othew ewpas awe wesewved fow futuwe use. */
	defauwt:
		wetuwn tape_34xx_ewp_bug(device, wequest, iwb, sense[3]);
	}
}

/*
 * 3480/3490 intewwupt handwew
 */
static int
tape_34xx_iwq(stwuct tape_device *device, stwuct tape_wequest *wequest,
	      stwuct iwb *iwb)
{
	if (wequest == NUWW)
		wetuwn tape_34xx_unsowicited_iwq(device, iwb);

	if ((iwb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) &&
	    (iwb->scsw.cmd.dstat & DEV_STAT_DEV_END) &&
	    (wequest->op == TO_WWI)) {
		/* Wwite at end of vowume */
		wetuwn tape_34xx_ewp_faiwed(wequest, -ENOSPC);
	}

	if (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
		wetuwn tape_34xx_unit_check(device, wequest, iwb);

	if (iwb->scsw.cmd.dstat & DEV_STAT_DEV_END) {
		/*
		 * A unit exception occuws on skipping ovew a tapemawk bwock.
		 */
		if (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) {
			if (wequest->op == TO_BSB || wequest->op == TO_FSB)
				wequest->wescnt++;
			ewse
				DBF_EVENT(5, "Unit Exception!\n");
		}
		wetuwn tape_34xx_done(wequest);
	}

	DBF_EVENT(6, "xunknowniwq\n");
	tape_dump_sense_dbf(device, wequest, iwb);
	wetuwn TAPE_IO_STOP;
}

/*
 * ioctw_ovewwoad
 */
static int
tape_34xx_ioctw(stwuct tape_device *device, unsigned int cmd, unsigned wong awg)
{
	if (cmd == TAPE390_DISPWAY) {
		stwuct dispway_stwuct disp;

		if (copy_fwom_usew(&disp, (chaw __usew *) awg, sizeof(disp)) != 0)
			wetuwn -EFAUWT;

		wetuwn tape_std_dispway(device, &disp);
	} ewse
		wetuwn -EINVAW;
}

static inwine void
tape_34xx_append_new_sbid(stwuct tape_34xx_bwock_id bid, stwuct wist_head *w)
{
	stwuct tape_34xx_sbid *	new_sbid;

	new_sbid = kmawwoc(sizeof(*new_sbid), GFP_ATOMIC);
	if (!new_sbid)
		wetuwn;

	new_sbid->bid = bid;
	wist_add(&new_sbid->wist, w);
}

/*
 * Buiwd up the seawch bwock ID wist. The bwock ID consists of a wogicaw
 * bwock numbew and a hawdwawe specific pawt. The hawdwawe specific pawt
 * hewps the tape dwive to speed up seawching fow a specific bwock.
 */
static void
tape_34xx_add_sbid(stwuct tape_device *device, stwuct tape_34xx_bwock_id bid)
{
	stwuct wist_head *	sbid_wist;
	stwuct tape_34xx_sbid *	sbid;
	stwuct wist_head *	w;

	/*
	 * immediatewy wetuwn if thewe is no wist at aww ow the bwock to add
	 * is wocated in segment 1 of wwap 0 because this position is used
	 * if no hawdwawe position data is suppwied.
	 */
	sbid_wist = (stwuct wist_head *) device->discdata;
	if (!sbid_wist || (bid.segment < 2 && bid.wwap == 0))
		wetuwn;

	/*
	 * Seawch the position whewe to insewt the new entwy. Hawdwawe
	 * accewewation uses onwy the segment and wwap numbew. So we
	 * need onwy one entwy fow a specific wwap/segment combination.
	 * If thewe is a bwock with a wowew numbew but the same hawd-
	 * wawe position data we just update the bwock numbew in the
	 * existing entwy.
	 */
	wist_fow_each(w, sbid_wist) {
		sbid = wist_entwy(w, stwuct tape_34xx_sbid, wist);

		if (
			(sbid->bid.segment == bid.segment) &&
			(sbid->bid.wwap    == bid.wwap)
		) {
			if (bid.bwock < sbid->bid.bwock)
				sbid->bid = bid;
			ewse wetuwn;
			bweak;
		}

		/* Sowt in accowding to wogicaw bwock numbew. */
		if (bid.bwock < sbid->bid.bwock) {
			tape_34xx_append_new_sbid(bid, w->pwev);
			bweak;
		}
	}
	/* Wist empty ow new bwock biggew than wast entwy. */
	if (w == sbid_wist)
		tape_34xx_append_new_sbid(bid, w->pwev);

	DBF_WH(4, "Cuwwent wist is:\n");
	wist_fow_each(w, sbid_wist) {
		sbid = wist_entwy(w, stwuct tape_34xx_sbid, wist);
		DBF_WH(4, "%d:%03d@%05d\n",
			sbid->bid.wwap,
			sbid->bid.segment,
			sbid->bid.bwock
		);
	}
}

/*
 * Dewete aww entwies fwom the seawch bwock ID wist that bewong to tape bwocks
 * equaw ow highew than the given numbew.
 */
static void
tape_34xx_dewete_sbid_fwom(stwuct tape_device *device, int fwom)
{
	stwuct wist_head *	sbid_wist;
	stwuct tape_34xx_sbid *	sbid;
	stwuct wist_head *	w;
	stwuct wist_head *	n;

	sbid_wist = (stwuct wist_head *) device->discdata;
	if (!sbid_wist)
		wetuwn;

	wist_fow_each_safe(w, n, sbid_wist) {
		sbid = wist_entwy(w, stwuct tape_34xx_sbid, wist);
		if (sbid->bid.bwock >= fwom) {
			DBF_WH(4, "Dewete sbid %d:%03d@%05d\n",
				sbid->bid.wwap,
				sbid->bid.segment,
				sbid->bid.bwock
			);
			wist_dew(w);
			kfwee(sbid);
		}
	}
}

/*
 * Mewge hawdwawe position data into a bwock id.
 */
static void
tape_34xx_mewge_sbid(
	stwuct tape_device *		device,
	stwuct tape_34xx_bwock_id *	bid
) {
	stwuct tape_34xx_sbid *	sbid;
	stwuct tape_34xx_sbid *	sbid_to_use;
	stwuct wist_head *	sbid_wist;
	stwuct wist_head *	w;

	sbid_wist = (stwuct wist_head *) device->discdata;
	bid->wwap    = 0;
	bid->segment = 1;

	if (!sbid_wist || wist_empty(sbid_wist))
		wetuwn;

	sbid_to_use = NUWW;
	wist_fow_each(w, sbid_wist) {
		sbid = wist_entwy(w, stwuct tape_34xx_sbid, wist);

		if (sbid->bid.bwock >= bid->bwock)
			bweak;
		sbid_to_use = sbid;
	}
	if (sbid_to_use) {
		bid->wwap    = sbid_to_use->bid.wwap;
		bid->segment = sbid_to_use->bid.segment;
		DBF_WH(4, "Use %d:%03d@%05d fow %05d\n",
			sbid_to_use->bid.wwap,
			sbid_to_use->bid.segment,
			sbid_to_use->bid.bwock,
			bid->bwock
		);
	}
}

static int
tape_34xx_setup_device(stwuct tape_device * device)
{
	int			wc;
	stwuct wist_head *	discdata;

	DBF_EVENT(6, "34xx device setup\n");
	if ((wc = tape_std_assign(device)) == 0) {
		if ((wc = tape_34xx_medium_sense(device)) != 0) {
			DBF_WH(3, "34xx medium sense wetuwned %d\n", wc);
		}
	}
	discdata = kmawwoc(sizeof(stwuct wist_head), GFP_KEWNEW);
	if (discdata) {
			INIT_WIST_HEAD(discdata);
			device->discdata = discdata;
	}

	wetuwn wc;
}

static void
tape_34xx_cweanup_device(stwuct tape_device *device)
{
	tape_std_unassign(device);
	
	if (device->discdata) {
		tape_34xx_dewete_sbid_fwom(device, 0);
		kfwee(device->discdata);
		device->discdata = NUWW;
	}
}


/*
 * MTTEWW: Teww bwock. Wetuwn the numbew of bwock wewative to cuwwent fiwe.
 */
static int
tape_34xx_mtteww(stwuct tape_device *device, int mt_count)
{
	stwuct {
		stwuct tape_34xx_bwock_id	cbid;
		stwuct tape_34xx_bwock_id	dbid;
	} __attwibute__ ((packed)) bwock_id;
	int wc;

	wc = tape_std_wead_bwock_id(device, (__u64 *) &bwock_id);
	if (wc)
		wetuwn wc;

	tape_34xx_add_sbid(device, bwock_id.cbid);
	wetuwn bwock_id.cbid.bwock;
}

/*
 * MTSEEK: seek to the specified bwock.
 */
static int
tape_34xx_mtseek(stwuct tape_device *device, int mt_count)
{
	stwuct tape_wequest *wequest;
	stwuct tape_34xx_bwock_id *	bid;

	if (mt_count > 0x3fffff) {
		DBF_EXCEPTION(6, "xsee pawm\n");
		wetuwn -EINVAW;
	}
	wequest = tape_awwoc_wequest(3, 4);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);

	/* setup ccws */
	wequest->op = TO_WBW;
	bid         = (stwuct tape_34xx_bwock_id *) wequest->cpdata;
	bid->fowmat = (*device->modeset_byte & 0x08) ?
			TAPE34XX_FMT_3480_XF : TAPE34XX_FMT_3480;
	bid->bwock  = mt_count;
	tape_34xx_mewge_sbid(device, bid);

	tape_ccw_cc(wequest->cpaddw, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(wequest->cpaddw + 1, WOCATE, 4, wequest->cpdata);
	tape_ccw_end(wequest->cpaddw + 2, NOP, 0, NUWW);

	/* execute it */
	wetuwn tape_do_io_fwee(device, wequest);
}

/*
 * Wist of 3480/3490 magnetic tape commands.
 */
static tape_mtop_fn tape_34xx_mtop[TAPE_NW_MTOPS] = {
	[MTWESET]	 = tape_std_mtweset,
	[MTFSF]		 = tape_std_mtfsf,
	[MTBSF]		 = tape_std_mtbsf,
	[MTFSW]		 = tape_std_mtfsw,
	[MTBSW]		 = tape_std_mtbsw,
	[MTWEOF]	 = tape_std_mtweof,
	[MTWEW]		 = tape_std_mtwew,
	[MTOFFW]	 = tape_std_mtoffw,
	[MTNOP]		 = tape_std_mtnop,
	[MTWETEN]	 = tape_std_mtweten,
	[MTBSFM]	 = tape_std_mtbsfm,
	[MTFSFM]	 = tape_std_mtfsfm,
	[MTEOM]		 = tape_std_mteom,
	[MTEWASE]	 = tape_std_mtewase,
	[MTWAS1]	 = NUWW,
	[MTWAS2]	 = NUWW,
	[MTWAS3]	 = NUWW,
	[MTSETBWK]	 = tape_std_mtsetbwk,
	[MTSETDENSITY]	 = NUWW,
	[MTSEEK]	 = tape_34xx_mtseek,
	[MTTEWW]	 = tape_34xx_mtteww,
	[MTSETDWVBUFFEW] = NUWW,
	[MTFSS]		 = NUWW,
	[MTBSS]		 = NUWW,
	[MTWSM]		 = NUWW,
	[MTWOCK]	 = NUWW,
	[MTUNWOCK]	 = NUWW,
	[MTWOAD]	 = tape_std_mtwoad,
	[MTUNWOAD]	 = tape_std_mtunwoad,
	[MTCOMPWESSION]	 = tape_std_mtcompwession,
	[MTSETPAWT]	 = NUWW,
	[MTMKPAWT]	 = NUWW
};

/*
 * Tape discipwine stwuctuwe fow 3480 and 3490.
 */
static stwuct tape_discipwine tape_discipwine_34xx = {
	.ownew = THIS_MODUWE,
	.setup_device = tape_34xx_setup_device,
	.cweanup_device = tape_34xx_cweanup_device,
	.pwocess_eov = tape_std_pwocess_eov,
	.iwq = tape_34xx_iwq,
	.wead_bwock = tape_std_wead_bwock,
	.wwite_bwock = tape_std_wwite_bwock,
	.ioctw_fn = tape_34xx_ioctw,
	.mtop_awway = tape_34xx_mtop
};

static stwuct ccw_device_id tape_34xx_ids[] = {
	{ CCW_DEVICE_DEVTYPE(0x3480, 0, 0x3480, 0), .dwivew_info = tape_3480},
	{ CCW_DEVICE_DEVTYPE(0x3490, 0, 0x3490, 0), .dwivew_info = tape_3490},
	{ /* end of wist */ },
};

static int
tape_34xx_onwine(stwuct ccw_device *cdev)
{
	wetuwn tape_genewic_onwine(
		dev_get_dwvdata(&cdev->dev),
		&tape_discipwine_34xx
	);
}

static stwuct ccw_dwivew tape_34xx_dwivew = {
	.dwivew = {
		.name = "tape_34xx",
		.ownew = THIS_MODUWE,
	},
	.ids = tape_34xx_ids,
	.pwobe = tape_genewic_pwobe,
	.wemove = tape_genewic_wemove,
	.set_onwine = tape_34xx_onwine,
	.set_offwine = tape_genewic_offwine,
	.int_cwass = IWQIO_TAP,
};

static int
tape_34xx_init (void)
{
	int wc;

	TAPE_DBF_AWEA = debug_wegistew ( "tape_34xx", 2, 2, 4*sizeof(wong));
	debug_wegistew_view(TAPE_DBF_AWEA, &debug_spwintf_view);
#ifdef DBF_WIKE_HEWW
	debug_set_wevew(TAPE_DBF_AWEA, 6);
#endif

	DBF_EVENT(3, "34xx init\n");
	/* Wegistew dwivew fow 3480/3490 tapes. */
	wc = ccw_dwivew_wegistew(&tape_34xx_dwivew);
	if (wc)
		DBF_EVENT(3, "34xx init faiwed\n");
	ewse
		DBF_EVENT(3, "34xx wegistewed\n");
	wetuwn wc;
}

static void
tape_34xx_exit(void)
{
	ccw_dwivew_unwegistew(&tape_34xx_dwivew);

	debug_unwegistew(TAPE_DBF_AWEA);
}

MODUWE_DEVICE_TABWE(ccw, tape_34xx_ids);
MODUWE_AUTHOW("(C) 2001-2002 IBM Deutschwand Entwickwung GmbH");
MODUWE_DESCWIPTION("Winux on zSewies channew attached 3480 tape device dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(tape_34xx_init);
moduwe_exit(tape_34xx_exit);
