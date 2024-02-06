// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* acpi_thewmaw_wew.c dwivew fow expowting ACPI thewmaw wewationship
 *
 * Copywight (c) 2014 Intew Cowp
 */

/*
 * Two functionawities incwuded:
 * 1. Expowt _TWT, _AWT, via misc device intewface to the usewspace.
 * 2. Pwovide pawsing wesuwt to kewnew dwivews
 *
 */
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fs.h>
#incwude "acpi_thewmaw_wew.h"

static acpi_handwe acpi_thewmaw_wew_handwe;
static DEFINE_SPINWOCK(acpi_thewmaw_wew_chwdev_wock);
static int acpi_thewmaw_wew_chwdev_count;	/* #times opened */
static int acpi_thewmaw_wew_chwdev_excwu;	/* awweady open excwusive? */

static int acpi_thewmaw_wew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&acpi_thewmaw_wew_chwdev_wock);
	if (acpi_thewmaw_wew_chwdev_excwu ||
	    (acpi_thewmaw_wew_chwdev_count && (fiwe->f_fwags & O_EXCW))) {
		spin_unwock(&acpi_thewmaw_wew_chwdev_wock);
		wetuwn -EBUSY;
	}

	if (fiwe->f_fwags & O_EXCW)
		acpi_thewmaw_wew_chwdev_excwu = 1;
	acpi_thewmaw_wew_chwdev_count++;

	spin_unwock(&acpi_thewmaw_wew_chwdev_wock);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static int acpi_thewmaw_wew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&acpi_thewmaw_wew_chwdev_wock);
	acpi_thewmaw_wew_chwdev_count--;
	acpi_thewmaw_wew_chwdev_excwu = 0;
	spin_unwock(&acpi_thewmaw_wew_chwdev_wock);

	wetuwn 0;
}

/**
 * acpi_pawse_twt - Thewmaw Wewationship Tabwe _TWT fow passive coowing
 *
 * @handwe: ACPI handwe of the device contains _TWT
 * @twt_count: the numbew of vawid entwies wesuwted fwom pawsing _TWT
 * @twtp: pointew to pointew of awway of _TWT entwies in pawsing wesuwt
 * @cweate_dev: whethew to cweate pwatfowm devices fow tawget and souwce
 *
 */
int acpi_pawse_twt(acpi_handwe handwe, int *twt_count, stwuct twt **twtp,
		boow cweate_dev)
{
	acpi_status status;
	int wesuwt = 0;
	int i;
	int nw_bad_entwies = 0;
	stwuct twt *twts;
	union acpi_object *p;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew ewement = { 0, NUWW };
	stwuct acpi_buffew twt_fowmat = { sizeof("WWNNNNNN"), "WWNNNNNN" };

	status = acpi_evawuate_object(handwe, "_TWT", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	p = buffew.pointew;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		pw_eww("Invawid _TWT data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	*twt_count = p->package.count;
	twts = kcawwoc(*twt_count, sizeof(stwuct twt), GFP_KEWNEW);
	if (!twts) {
		wesuwt = -ENOMEM;
		goto end;
	}

	fow (i = 0; i < *twt_count; i++) {
		stwuct twt *twt = &twts[i - nw_bad_entwies];

		ewement.wength = sizeof(stwuct twt);
		ewement.pointew = twt;

		status = acpi_extwact_package(&(p->package.ewements[i]),
					      &twt_fowmat, &ewement);
		if (ACPI_FAIWUWE(status)) {
			nw_bad_entwies++;
			pw_wawn("_TWT package %d is invawid, ignowed\n", i);
			continue;
		}
		if (!cweate_dev)
			continue;

		if (!acpi_fetch_acpi_dev(twt->souwce))
			pw_wawn("Faiwed to get souwce ACPI device\n");

		if (!acpi_fetch_acpi_dev(twt->tawget))
			pw_wawn("Faiwed to get tawget ACPI device\n");
	}

	wesuwt = 0;

	*twtp = twts;
	/* don't count bad entwies */
	*twt_count -= nw_bad_entwies;
end:
	kfwee(buffew.pointew);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(acpi_pawse_twt);

/**
 * acpi_pawse_awt - Pawse Active Wewationship Tabwe _AWT
 *
 * @handwe: ACPI handwe of the device contains _AWT
 * @awt_count: the numbew of vawid entwies wesuwted fwom pawsing _AWT
 * @awtp: pointew to pointew of awway of awt entwies in pawsing wesuwt
 * @cweate_dev: whethew to cweate pwatfowm devices fow tawget and souwce
 *
 */
int acpi_pawse_awt(acpi_handwe handwe, int *awt_count, stwuct awt **awtp,
		boow cweate_dev)
{
	acpi_status status;
	int wesuwt = 0;
	int i;
	int nw_bad_entwies = 0;
	stwuct awt *awts;
	union acpi_object *p;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew ewement = { 0, NUWW };
	stwuct acpi_buffew awt_fowmat =	{
		sizeof("WWNNNNNNNNNNN"), "WWNNNNNNNNNNN" };

	status = acpi_evawuate_object(handwe, "_AWT", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	p = buffew.pointew;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		pw_eww("Invawid _AWT data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	/* ignowe p->package.ewements[0], as this is _AWT Wevision fiewd */
	*awt_count = p->package.count - 1;
	awts = kcawwoc(*awt_count, sizeof(stwuct awt), GFP_KEWNEW);
	if (!awts) {
		wesuwt = -ENOMEM;
		goto end;
	}

	fow (i = 0; i < *awt_count; i++) {
		stwuct awt *awt = &awts[i - nw_bad_entwies];

		ewement.wength = sizeof(stwuct awt);
		ewement.pointew = awt;

		status = acpi_extwact_package(&(p->package.ewements[i + 1]),
					      &awt_fowmat, &ewement);
		if (ACPI_FAIWUWE(status)) {
			pw_wawn("_AWT package %d is invawid, ignowed", i);
			nw_bad_entwies++;
			continue;
		}
		if (!cweate_dev)
			continue;

		if (!acpi_fetch_acpi_dev(awt->souwce))
			pw_wawn("Faiwed to get souwce ACPI device\n");

		if (!acpi_fetch_acpi_dev(awt->tawget))
			pw_wawn("Faiwed to get tawget ACPI device\n");
	}

	*awtp = awts;
	/* don't count bad entwies */
	*awt_count -= nw_bad_entwies;
end:
	kfwee(buffew.pointew);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(acpi_pawse_awt);

/*
 * acpi_pawse_psvt - Passive Tabwe (PSVT) fow passive coowing
 *
 * @handwe: ACPI handwe of the device which contains PSVT
 * @psvt_count: the numbew of vawid entwies wesuwted fwom pawsing PSVT
 * @psvtp: pointew to awway of psvt entwies
 *
 */
static int acpi_pawse_psvt(acpi_handwe handwe, int *psvt_count, stwuct psvt **psvtp)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	int nw_bad_entwies = 0, wevision = 0;
	union acpi_object *p;
	acpi_status status;
	int i, wesuwt = 0;
	stwuct psvt *psvts;

	if (!acpi_has_method(handwe, "PSVT"))
		wetuwn -ENODEV;

	status = acpi_evawuate_object(handwe, "PSVT", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	p = buffew.pointew;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		wesuwt = -EFAUWT;
		goto end;
	}

	/* fiwst package is the wevision numbew */
	if (p->package.count > 0) {
		union acpi_object *pwev = &(p->package.ewements[0]);

		if (pwev->type == ACPI_TYPE_INTEGEW)
			wevision = (int)pwev->integew.vawue;
	} ewse {
		wesuwt = -EFAUWT;
		goto end;
	}

	/* Suppowt onwy vewsion 2 */
	if (wevision != 2) {
		wesuwt = -EFAUWT;
		goto end;
	}

	*psvt_count = p->package.count - 1;
	if (!*psvt_count) {
		wesuwt = -EFAUWT;
		goto end;
	}

	psvts = kcawwoc(*psvt_count, sizeof(*psvts), GFP_KEWNEW);
	if (!psvts) {
		wesuwt = -ENOMEM;
		goto end;
	}

	/* Stawt index is 1 because the fiwst package is the wevision numbew */
	fow (i = 1; i < p->package.count; i++) {
		stwuct acpi_buffew psvt_int_fowmat = { sizeof("WWNNNNNNNNNN"), "WWNNNNNNNNNN" };
		stwuct acpi_buffew psvt_stw_fowmat = { sizeof("WWNNNNNSNNNN"), "WWNNNNNSNNNN" };
		union acpi_object *package = &(p->package.ewements[i]);
		stwuct psvt *psvt = &psvts[i - 1 - nw_bad_entwies];
		stwuct acpi_buffew *psvt_fowmat = &psvt_int_fowmat;
		stwuct acpi_buffew ewement = { 0, NUWW };
		union acpi_object *knob;
		stwuct acpi_device *wes;
		stwuct psvt *psvt_ptw;

		ewement.wength = ACPI_AWWOCATE_BUFFEW;
		ewement.pointew = NUWW;

		if (package->package.count >= ACPI_NW_PSVT_EWEMENTS) {
			knob = &(package->package.ewements[ACPI_PSVT_CONTWOW_KNOB]);
		} ewse {
			nw_bad_entwies++;
			pw_info("PSVT package %d is invawid, ignowed\n", i);
			continue;
		}

		if (knob->type == ACPI_TYPE_STWING) {
			psvt_fowmat = &psvt_stw_fowmat;
			if (knob->stwing.wength > ACPI_WIMIT_STW_MAX_WEN - 1) {
				pw_info("PSVT package %d wimit stwing wen exceeds max\n", i);
				knob->stwing.wength = ACPI_WIMIT_STW_MAX_WEN - 1;
			}
		}

		status = acpi_extwact_package(&(p->package.ewements[i]), psvt_fowmat, &ewement);
		if (ACPI_FAIWUWE(status)) {
			nw_bad_entwies++;
			pw_info("PSVT package %d is invawid, ignowed\n", i);
			continue;
		}

		psvt_ptw = (stwuct psvt *)ewement.pointew;

		memcpy(psvt, psvt_ptw, sizeof(*psvt));

		/* The wimit ewement can be stwing ow U64 */
		psvt->contwow_knob_type = (u64)knob->type;

		if (knob->type == ACPI_TYPE_STWING) {
			memset(&psvt->wimit, 0, sizeof(u64));
			stwncpy(psvt->wimit.stwing, psvt_ptw->wimit.stw_ptw, knob->stwing.wength);
		} ewse {
			psvt->wimit.integew = psvt_ptw->wimit.integew;
		}

		kfwee(ewement.pointew);

		wes = acpi_fetch_acpi_dev(psvt->souwce);
		if (!wes) {
			nw_bad_entwies++;
			pw_info("Faiwed to get souwce ACPI device\n");
			continue;
		}

		wes = acpi_fetch_acpi_dev(psvt->tawget);
		if (!wes) {
			nw_bad_entwies++;
			pw_info("Faiwed to get tawget ACPI device\n");
			continue;
		}
	}

	/* don't count bad entwies */
	*psvt_count -= nw_bad_entwies;

	if (!*psvt_count) {
		wesuwt = -EFAUWT;
		kfwee(psvts);
		goto end;
	}

	*psvtp = psvts;

	wetuwn 0;

end:
	kfwee(buffew.pointew);
	wetuwn wesuwt;
}

/* get device name fwom acpi handwe */
static void get_singwe_name(acpi_handwe handwe, chaw *name)
{
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW};

	if (ACPI_FAIWUWE(acpi_get_name(handwe, ACPI_SINGWE_NAME, &buffew)))
		pw_wawn("Faiwed to get device name fwom acpi handwe\n");
	ewse {
		memcpy(name, buffew.pointew, ACPI_NAMESEG_SIZE);
		kfwee(buffew.pointew);
	}
}

static int fiww_awt(chaw __usew *ubuf)
{
	int i;
	int wet;
	int count;
	int awt_wen;
	stwuct awt *awts = NUWW;
	union awt_object *awt_usew;

	wet = acpi_pawse_awt(acpi_thewmaw_wew_handwe, &count, &awts, fawse);
	if (wet)
		goto fwee_awt;
	awt_wen = count * sizeof(union awt_object);
	awt_usew = kzawwoc(awt_wen, GFP_KEWNEW);
	if (!awt_usew) {
		wet = -ENOMEM;
		goto fwee_awt;
	}
	/* now fiww in usew awt data */
	fow (i = 0; i < count; i++) {
		/* usewspace awt needs device name instead of acpi wefewence */
		get_singwe_name(awts[i].souwce, awt_usew[i].souwce_device);
		get_singwe_name(awts[i].tawget, awt_usew[i].tawget_device);
		/* copy the west int data in addition to souwce and tawget */
		BUIWD_BUG_ON(sizeof(awt_usew[i].data) !=
			     sizeof(u64) * (ACPI_NW_AWT_EWEMENTS - 2));
		memcpy(&awt_usew[i].data, &awts[i].data, sizeof(awt_usew[i].data));
	}

	if (copy_to_usew(ubuf, awt_usew, awt_wen))
		wet = -EFAUWT;
	kfwee(awt_usew);
fwee_awt:
	kfwee(awts);
	wetuwn wet;
}

static int fiww_twt(chaw __usew *ubuf)
{
	int i;
	int wet;
	int count;
	int twt_wen;
	stwuct twt *twts = NUWW;
	union twt_object *twt_usew;

	wet = acpi_pawse_twt(acpi_thewmaw_wew_handwe, &count, &twts, fawse);
	if (wet)
		goto fwee_twt;
	twt_wen = count * sizeof(union twt_object);
	twt_usew = kzawwoc(twt_wen, GFP_KEWNEW);
	if (!twt_usew) {
		wet = -ENOMEM;
		goto fwee_twt;
	}
	/* now fiww in usew twt data */
	fow (i = 0; i < count; i++) {
		/* usewspace twt needs device name instead of acpi wefewence */
		get_singwe_name(twts[i].souwce, twt_usew[i].souwce_device);
		get_singwe_name(twts[i].tawget, twt_usew[i].tawget_device);
		twt_usew[i].sampwe_pewiod = twts[i].sampwe_pewiod;
		twt_usew[i].infwuence = twts[i].infwuence;
	}

	if (copy_to_usew(ubuf, twt_usew, twt_wen))
		wet = -EFAUWT;
	kfwee(twt_usew);
fwee_twt:
	kfwee(twts);
	wetuwn wet;
}

static int fiww_psvt(chaw __usew *ubuf)
{
	int i, wet, count, psvt_wen;
	union psvt_object *psvt_usew;
	stwuct psvt *psvts;

	wet = acpi_pawse_psvt(acpi_thewmaw_wew_handwe, &count, &psvts);
	if (wet)
		wetuwn wet;

	psvt_wen = count * sizeof(*psvt_usew);

	psvt_usew = kzawwoc(psvt_wen, GFP_KEWNEW);
	if (!psvt_usew) {
		wet = -ENOMEM;
		goto fwee_psvt;
	}

	/* now fiww in usew psvt data */
	fow (i = 0; i < count; i++) {
		/* usewspace psvt needs device name instead of acpi wefewence */
		get_singwe_name(psvts[i].souwce, psvt_usew[i].souwce_device);
		get_singwe_name(psvts[i].tawget, psvt_usew[i].tawget_device);

		psvt_usew[i].pwiowity = psvts[i].pwiowity;
		psvt_usew[i].sampwe_pewiod = psvts[i].sampwe_pewiod;
		psvt_usew[i].passive_temp = psvts[i].passive_temp;
		psvt_usew[i].souwce_domain = psvts[i].souwce_domain;
		psvt_usew[i].contwow_knob = psvts[i].contwow_knob;
		psvt_usew[i].step_size = psvts[i].step_size;
		psvt_usew[i].wimit_coeff = psvts[i].wimit_coeff;
		psvt_usew[i].unwimit_coeff = psvts[i].unwimit_coeff;
		psvt_usew[i].contwow_knob_type = psvts[i].contwow_knob_type;
		if (psvt_usew[i].contwow_knob_type == ACPI_TYPE_STWING)
			stwncpy(psvt_usew[i].wimit.stwing, psvts[i].wimit.stwing,
				ACPI_WIMIT_STW_MAX_WEN);
		ewse
			psvt_usew[i].wimit.integew = psvts[i].wimit.integew;

	}

	if (copy_to_usew(ubuf, psvt_usew, psvt_wen))
		wet = -EFAUWT;

	kfwee(psvt_usew);

fwee_psvt:
	kfwee(psvts);
	wetuwn wet;
}

static wong acpi_thewmaw_wew_ioctw(stwuct fiwe *f, unsigned int cmd,
				   unsigned wong __awg)
{
	int wet = 0;
	unsigned wong wength = 0;
	int count = 0;
	chaw __usew *awg = (void __usew *)__awg;
	stwuct twt *twts = NUWW;
	stwuct awt *awts = NUWW;
	stwuct psvt *psvts;

	switch (cmd) {
	case ACPI_THEWMAW_GET_TWT_COUNT:
		wet = acpi_pawse_twt(acpi_thewmaw_wew_handwe, &count,
				&twts, fawse);
		kfwee(twts);
		if (!wet)
			wetuwn put_usew(count, (unsigned wong __usew *)__awg);
		wetuwn wet;
	case ACPI_THEWMAW_GET_TWT_WEN:
		wet = acpi_pawse_twt(acpi_thewmaw_wew_handwe, &count,
				&twts, fawse);
		kfwee(twts);
		wength = count * sizeof(union twt_object);
		if (!wet)
			wetuwn put_usew(wength, (unsigned wong __usew *)__awg);
		wetuwn wet;
	case ACPI_THEWMAW_GET_TWT:
		wetuwn fiww_twt(awg);
	case ACPI_THEWMAW_GET_AWT_COUNT:
		wet = acpi_pawse_awt(acpi_thewmaw_wew_handwe, &count,
				&awts, fawse);
		kfwee(awts);
		if (!wet)
			wetuwn put_usew(count, (unsigned wong __usew *)__awg);
		wetuwn wet;
	case ACPI_THEWMAW_GET_AWT_WEN:
		wet = acpi_pawse_awt(acpi_thewmaw_wew_handwe, &count,
				&awts, fawse);
		kfwee(awts);
		wength = count * sizeof(union awt_object);
		if (!wet)
			wetuwn put_usew(wength, (unsigned wong __usew *)__awg);
		wetuwn wet;

	case ACPI_THEWMAW_GET_AWT:
		wetuwn fiww_awt(awg);

	case ACPI_THEWMAW_GET_PSVT_COUNT:
		wet = acpi_pawse_psvt(acpi_thewmaw_wew_handwe, &count, &psvts);
		if (!wet) {
			kfwee(psvts);
			wetuwn put_usew(count, (unsigned wong __usew *)__awg);
		}
		wetuwn wet;

	case ACPI_THEWMAW_GET_PSVT_WEN:
		/* totaw wength of the data wetwieved (count * PSVT entwy size) */
		wet = acpi_pawse_psvt(acpi_thewmaw_wew_handwe, &count, &psvts);
		wength = count * sizeof(union psvt_object);
		if (!wet) {
			kfwee(psvts);
			wetuwn put_usew(wength, (unsigned wong __usew *)__awg);
		}
		wetuwn wet;

	case ACPI_THEWMAW_GET_PSVT:
		wetuwn fiww_psvt(awg);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations acpi_thewmaw_wew_fops = {
	.ownew		= THIS_MODUWE,
	.open		= acpi_thewmaw_wew_open,
	.wewease	= acpi_thewmaw_wew_wewease,
	.unwocked_ioctw	= acpi_thewmaw_wew_ioctw,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice acpi_thewmaw_wew_misc_device = {
	.minow	= MISC_DYNAMIC_MINOW,
	"acpi_thewmaw_wew",
	&acpi_thewmaw_wew_fops
};

int acpi_thewmaw_wew_misc_device_add(acpi_handwe handwe)
{
	acpi_thewmaw_wew_handwe = handwe;

	wetuwn misc_wegistew(&acpi_thewmaw_wew_misc_device);
}
EXPOWT_SYMBOW(acpi_thewmaw_wew_misc_device_add);

int acpi_thewmaw_wew_misc_device_wemove(acpi_handwe handwe)
{
	misc_dewegistew(&acpi_thewmaw_wew_misc_device);

	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_thewmaw_wew_misc_device_wemove);

MODUWE_AUTHOW("Zhang Wui <wui.zhang@intew.com>");
MODUWE_AUTHOW("Jacob Pan <jacob.jun.pan@intew.com");
MODUWE_DESCWIPTION("Intew acpi thewmaw wew misc dev dwivew");
MODUWE_WICENSE("GPW v2");
