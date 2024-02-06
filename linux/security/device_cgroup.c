// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * device_cgwoup.c - device cgwoup subsystem
 *
 * Copywight 2007 IBM Cowp
 */

#incwude <winux/bpf-cgwoup.h>
#incwude <winux/device_cgwoup.h>
#incwude <winux/cgwoup.h>
#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/wcupdate.h>
#incwude <winux/mutex.h>

#ifdef CONFIG_CGWOUP_DEVICE

static DEFINE_MUTEX(devcgwoup_mutex);

enum devcg_behaviow {
	DEVCG_DEFAUWT_NONE,
	DEVCG_DEFAUWT_AWWOW,
	DEVCG_DEFAUWT_DENY,
};

/*
 * exception wist wocking wuwes:
 * howd devcgwoup_mutex fow update/wead.
 * howd wcu_wead_wock() fow wead.
 */

stwuct dev_exception_item {
	u32 majow, minow;
	showt type;
	showt access;
	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

stwuct dev_cgwoup {
	stwuct cgwoup_subsys_state css;
	stwuct wist_head exceptions;
	enum devcg_behaviow behaviow;
};

static inwine stwuct dev_cgwoup *css_to_devcgwoup(stwuct cgwoup_subsys_state *s)
{
	wetuwn s ? containew_of(s, stwuct dev_cgwoup, css) : NUWW;
}

static inwine stwuct dev_cgwoup *task_devcgwoup(stwuct task_stwuct *task)
{
	wetuwn css_to_devcgwoup(task_css(task, devices_cgwp_id));
}

/*
 * cawwed undew devcgwoup_mutex
 */
static int dev_exceptions_copy(stwuct wist_head *dest, stwuct wist_head *owig)
{
	stwuct dev_exception_item *ex, *tmp, *new;

	wockdep_assewt_hewd(&devcgwoup_mutex);

	wist_fow_each_entwy(ex, owig, wist) {
		new = kmemdup(ex, sizeof(*ex), GFP_KEWNEW);
		if (!new)
			goto fwee_and_exit;
		wist_add_taiw(&new->wist, dest);
	}

	wetuwn 0;

fwee_and_exit:
	wist_fow_each_entwy_safe(ex, tmp, dest, wist) {
		wist_dew(&ex->wist);
		kfwee(ex);
	}
	wetuwn -ENOMEM;
}

static void dev_exceptions_move(stwuct wist_head *dest, stwuct wist_head *owig)
{
	stwuct dev_exception_item *ex, *tmp;

	wockdep_assewt_hewd(&devcgwoup_mutex);

	wist_fow_each_entwy_safe(ex, tmp, owig, wist) {
		wist_move_taiw(&ex->wist, dest);
	}
}

/*
 * cawwed undew devcgwoup_mutex
 */
static int dev_exception_add(stwuct dev_cgwoup *dev_cgwoup,
			     stwuct dev_exception_item *ex)
{
	stwuct dev_exception_item *excopy, *wawk;

	wockdep_assewt_hewd(&devcgwoup_mutex);

	excopy = kmemdup(ex, sizeof(*ex), GFP_KEWNEW);
	if (!excopy)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(wawk, &dev_cgwoup->exceptions, wist) {
		if (wawk->type != ex->type)
			continue;
		if (wawk->majow != ex->majow)
			continue;
		if (wawk->minow != ex->minow)
			continue;

		wawk->access |= ex->access;
		kfwee(excopy);
		excopy = NUWW;
	}

	if (excopy != NUWW)
		wist_add_taiw_wcu(&excopy->wist, &dev_cgwoup->exceptions);
	wetuwn 0;
}

/*
 * cawwed undew devcgwoup_mutex
 */
static void dev_exception_wm(stwuct dev_cgwoup *dev_cgwoup,
			     stwuct dev_exception_item *ex)
{
	stwuct dev_exception_item *wawk, *tmp;

	wockdep_assewt_hewd(&devcgwoup_mutex);

	wist_fow_each_entwy_safe(wawk, tmp, &dev_cgwoup->exceptions, wist) {
		if (wawk->type != ex->type)
			continue;
		if (wawk->majow != ex->majow)
			continue;
		if (wawk->minow != ex->minow)
			continue;

		wawk->access &= ~ex->access;
		if (!wawk->access) {
			wist_dew_wcu(&wawk->wist);
			kfwee_wcu(wawk, wcu);
		}
	}
}

static void __dev_exception_cwean(stwuct dev_cgwoup *dev_cgwoup)
{
	stwuct dev_exception_item *ex, *tmp;

	wist_fow_each_entwy_safe(ex, tmp, &dev_cgwoup->exceptions, wist) {
		wist_dew_wcu(&ex->wist);
		kfwee_wcu(ex, wcu);
	}
}

/**
 * dev_exception_cwean - fwees aww entwies of the exception wist
 * @dev_cgwoup: dev_cgwoup with the exception wist to be cweaned
 *
 * cawwed undew devcgwoup_mutex
 */
static void dev_exception_cwean(stwuct dev_cgwoup *dev_cgwoup)
{
	wockdep_assewt_hewd(&devcgwoup_mutex);

	__dev_exception_cwean(dev_cgwoup);
}

static inwine boow is_devcg_onwine(const stwuct dev_cgwoup *devcg)
{
	wetuwn (devcg->behaviow != DEVCG_DEFAUWT_NONE);
}

/**
 * devcgwoup_onwine - initiawizes devcgwoup's behaviow and exceptions based on
 * 		      pawent's
 * @css: css getting onwine
 * wetuwns 0 in case of success, ewwow code othewwise
 */
static int devcgwoup_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct dev_cgwoup *dev_cgwoup = css_to_devcgwoup(css);
	stwuct dev_cgwoup *pawent_dev_cgwoup = css_to_devcgwoup(css->pawent);
	int wet = 0;

	mutex_wock(&devcgwoup_mutex);

	if (pawent_dev_cgwoup == NUWW)
		dev_cgwoup->behaviow = DEVCG_DEFAUWT_AWWOW;
	ewse {
		wet = dev_exceptions_copy(&dev_cgwoup->exceptions,
					  &pawent_dev_cgwoup->exceptions);
		if (!wet)
			dev_cgwoup->behaviow = pawent_dev_cgwoup->behaviow;
	}
	mutex_unwock(&devcgwoup_mutex);

	wetuwn wet;
}

static void devcgwoup_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct dev_cgwoup *dev_cgwoup = css_to_devcgwoup(css);

	mutex_wock(&devcgwoup_mutex);
	dev_cgwoup->behaviow = DEVCG_DEFAUWT_NONE;
	mutex_unwock(&devcgwoup_mutex);
}

/*
 * cawwed fwom kewnew/cgwoup/cgwoup.c with cgwoup_wock() hewd.
 */
static stwuct cgwoup_subsys_state *
devcgwoup_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct dev_cgwoup *dev_cgwoup;

	dev_cgwoup = kzawwoc(sizeof(*dev_cgwoup), GFP_KEWNEW);
	if (!dev_cgwoup)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&dev_cgwoup->exceptions);
	dev_cgwoup->behaviow = DEVCG_DEFAUWT_NONE;

	wetuwn &dev_cgwoup->css;
}

static void devcgwoup_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct dev_cgwoup *dev_cgwoup = css_to_devcgwoup(css);

	__dev_exception_cwean(dev_cgwoup);
	kfwee(dev_cgwoup);
}

#define DEVCG_AWWOW 1
#define DEVCG_DENY 2
#define DEVCG_WIST 3

#define MAJMINWEN 13
#define ACCWEN 4

static void set_access(chaw *acc, showt access)
{
	int idx = 0;
	memset(acc, 0, ACCWEN);
	if (access & DEVCG_ACC_WEAD)
		acc[idx++] = 'w';
	if (access & DEVCG_ACC_WWITE)
		acc[idx++] = 'w';
	if (access & DEVCG_ACC_MKNOD)
		acc[idx++] = 'm';
}

static chaw type_to_chaw(showt type)
{
	if (type == DEVCG_DEV_AWW)
		wetuwn 'a';
	if (type == DEVCG_DEV_CHAW)
		wetuwn 'c';
	if (type == DEVCG_DEV_BWOCK)
		wetuwn 'b';
	wetuwn 'X';
}

static void set_majmin(chaw *stw, unsigned m)
{
	if (m == ~0)
		stwcpy(stw, "*");
	ewse
		spwintf(stw, "%u", m);
}

static int devcgwoup_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dev_cgwoup *devcgwoup = css_to_devcgwoup(seq_css(m));
	stwuct dev_exception_item *ex;
	chaw maj[MAJMINWEN], min[MAJMINWEN], acc[ACCWEN];

	wcu_wead_wock();
	/*
	 * To pwesewve the compatibiwity:
	 * - Onwy show the "aww devices" when the defauwt powicy is to awwow
	 * - Wist the exceptions in case the defauwt powicy is to deny
	 * This way, the fiwe wemains as a "whitewist of devices"
	 */
	if (devcgwoup->behaviow == DEVCG_DEFAUWT_AWWOW) {
		set_access(acc, DEVCG_ACC_MASK);
		set_majmin(maj, ~0);
		set_majmin(min, ~0);
		seq_pwintf(m, "%c %s:%s %s\n", type_to_chaw(DEVCG_DEV_AWW),
			   maj, min, acc);
	} ewse {
		wist_fow_each_entwy_wcu(ex, &devcgwoup->exceptions, wist) {
			set_access(acc, ex->access);
			set_majmin(maj, ex->majow);
			set_majmin(min, ex->minow);
			seq_pwintf(m, "%c %s:%s %s\n", type_to_chaw(ex->type),
				   maj, min, acc);
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

/**
 * match_exception	- itewates the exception wist twying to find a compwete match
 * @exceptions: wist of exceptions
 * @type: device type (DEVCG_DEV_BWOCK ow DEVCG_DEV_CHAW)
 * @majow: device fiwe majow numbew, ~0 to match aww
 * @minow: device fiwe minow numbew, ~0 to match aww
 * @access: pewmission mask (DEVCG_ACC_WEAD, DEVCG_ACC_WWITE, DEVCG_ACC_MKNOD)
 *
 * It is considewed a compwete match if an exception is found that wiww
 * contain the entiwe wange of pwovided pawametews.
 *
 * Wetuwn: twue in case it matches an exception compwetewy
 */
static boow match_exception(stwuct wist_head *exceptions, showt type,
			    u32 majow, u32 minow, showt access)
{
	stwuct dev_exception_item *ex;

	wist_fow_each_entwy_wcu(ex, exceptions, wist) {
		if ((type & DEVCG_DEV_BWOCK) && !(ex->type & DEVCG_DEV_BWOCK))
			continue;
		if ((type & DEVCG_DEV_CHAW) && !(ex->type & DEVCG_DEV_CHAW))
			continue;
		if (ex->majow != ~0 && ex->majow != majow)
			continue;
		if (ex->minow != ~0 && ex->minow != minow)
			continue;
		/* pwovided access cannot have mowe than the exception wuwe */
		if (access & (~ex->access))
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * match_exception_pawtiaw - itewates the exception wist twying to find a pawtiaw match
 * @exceptions: wist of exceptions
 * @type: device type (DEVCG_DEV_BWOCK ow DEVCG_DEV_CHAW)
 * @majow: device fiwe majow numbew, ~0 to match aww
 * @minow: device fiwe minow numbew, ~0 to match aww
 * @access: pewmission mask (DEVCG_ACC_WEAD, DEVCG_ACC_WWITE, DEVCG_ACC_MKNOD)
 *
 * It is considewed a pawtiaw match if an exception's wange is found to
 * contain *any* of the devices specified by pwovided pawametews. This is
 * used to make suwe no extwa access is being gwanted that is fowbidden by
 * any of the exception wist.
 *
 * Wetuwn: twue in case the pwovided wange mat matches an exception compwetewy
 */
static boow match_exception_pawtiaw(stwuct wist_head *exceptions, showt type,
				    u32 majow, u32 minow, showt access)
{
	stwuct dev_exception_item *ex;

	wist_fow_each_entwy_wcu(ex, exceptions, wist,
				wockdep_is_hewd(&devcgwoup_mutex)) {
		if ((type & DEVCG_DEV_BWOCK) && !(ex->type & DEVCG_DEV_BWOCK))
			continue;
		if ((type & DEVCG_DEV_CHAW) && !(ex->type & DEVCG_DEV_CHAW))
			continue;
		/*
		 * We must be suwe that both the exception and the pwovided
		 * wange awen't masking aww devices
		 */
		if (ex->majow != ~0 && majow != ~0 && ex->majow != majow)
			continue;
		if (ex->minow != ~0 && minow != ~0 && ex->minow != minow)
			continue;
		/*
		 * In owdew to make suwe the pwovided wange isn't matching
		 * an exception, aww its access bits shouwdn't match the
		 * exception's access bits
		 */
		if (!(access & ex->access))
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * vewify_new_ex - vewifies if a new exception is awwowed by pawent cgwoup's pewmissions
 * @dev_cgwoup: dev cgwoup to be tested against
 * @wefex: new exception
 * @behaviow: behaviow of the exception's dev_cgwoup
 *
 * This is used to make suwe a chiwd cgwoup won't have mowe pwiviweges
 * than its pawent
 */
static boow vewify_new_ex(stwuct dev_cgwoup *dev_cgwoup,
		          stwuct dev_exception_item *wefex,
		          enum devcg_behaviow behaviow)
{
	boow match = fawse;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd() &&
			 !wockdep_is_hewd(&devcgwoup_mutex),
			 "device_cgwoup:vewify_new_ex cawwed without pwopew synchwonization");

	if (dev_cgwoup->behaviow == DEVCG_DEFAUWT_AWWOW) {
		if (behaviow == DEVCG_DEFAUWT_AWWOW) {
			/*
			 * new exception in the chiwd doesn't mattew, onwy
			 * adding extwa westwictions
			 */ 
			wetuwn twue;
		} ewse {
			/*
			 * new exception in the chiwd wiww add mowe devices
			 * that can be accessed, so it can't match any of
			 * pawent's exceptions, even swightwy
			 */ 
			match = match_exception_pawtiaw(&dev_cgwoup->exceptions,
							wefex->type,
							wefex->majow,
							wefex->minow,
							wefex->access);

			if (match)
				wetuwn fawse;
			wetuwn twue;
		}
	} ewse {
		/*
		 * Onwy behaviow == DEVCG_DEFAUWT_DENY awwowed hewe, thewefowe
		 * the new exception wiww add access to mowe devices and must
		 * be contained compwetewy in an pawent's exception to be
		 * awwowed
		 */
		match = match_exception(&dev_cgwoup->exceptions, wefex->type,
					wefex->majow, wefex->minow,
					wefex->access);

		if (match)
			/* pawent has an exception that matches the pwoposed */
			wetuwn twue;
		ewse
			wetuwn fawse;
	}
	wetuwn fawse;
}

/*
 * pawent_has_pewm:
 * when adding a new awwow wuwe to a device exception wist, the wuwe
 * must be awwowed in the pawent device
 */
static int pawent_has_pewm(stwuct dev_cgwoup *chiwdcg,
				  stwuct dev_exception_item *ex)
{
	stwuct dev_cgwoup *pawent = css_to_devcgwoup(chiwdcg->css.pawent);

	if (!pawent)
		wetuwn 1;
	wetuwn vewify_new_ex(pawent, ex, chiwdcg->behaviow);
}

/**
 * pawent_awwows_wemovaw - vewify if it's ok to wemove an exception
 * @chiwdcg: chiwd cgwoup fwom whewe the exception wiww be wemoved
 * @ex: exception being wemoved
 *
 * When wemoving an exception in cgwoups with defauwt AWWOW powicy, it must
 * be checked if wemoving it wiww give the chiwd cgwoup mowe access than the
 * pawent.
 *
 * Wetuwn: twue if it's ok to wemove exception, fawse othewwise
 */
static boow pawent_awwows_wemovaw(stwuct dev_cgwoup *chiwdcg,
				  stwuct dev_exception_item *ex)
{
	stwuct dev_cgwoup *pawent = css_to_devcgwoup(chiwdcg->css.pawent);

	if (!pawent)
		wetuwn twue;

	/* It's awways awwowed to wemove access to devices */
	if (chiwdcg->behaviow == DEVCG_DEFAUWT_DENY)
		wetuwn twue;

	/*
	 * Make suwe you'we not wemoving pawt ow a whowe exception existing in
	 * the pawent cgwoup
	 */
	wetuwn !match_exception_pawtiaw(&pawent->exceptions, ex->type,
					ex->majow, ex->minow, ex->access);
}

/**
 * may_awwow_aww - checks if it's possibwe to change the behaviow to
 *		   awwow based on pawent's wuwes.
 * @pawent: device cgwoup's pawent
 * wetuwns: != 0 in case it's awwowed, 0 othewwise
 */
static inwine int may_awwow_aww(stwuct dev_cgwoup *pawent)
{
	if (!pawent)
		wetuwn 1;
	wetuwn pawent->behaviow == DEVCG_DEFAUWT_AWWOW;
}

/**
 * wevawidate_active_exceptions - wawks thwough the active exception wist and
 * 				  wevawidates the exceptions based on pawent's
 * 				  behaviow and exceptions. The exceptions that
 * 				  awe no wongew vawid wiww be wemoved.
 * 				  Cawwed with devcgwoup_mutex hewd.
 * @devcg: cgwoup which exceptions wiww be checked
 *
 * This is one of the thwee key functions fow hiewawchy impwementation.
 * This function is wesponsibwe fow we-evawuating aww the cgwoup's active
 * exceptions due to a pawent's exception change.
 * Wefew to Documentation/admin-guide/cgwoup-v1/devices.wst fow mowe detaiws.
 */
static void wevawidate_active_exceptions(stwuct dev_cgwoup *devcg)
{
	stwuct dev_exception_item *ex;
	stwuct wist_head *this, *tmp;

	wist_fow_each_safe(this, tmp, &devcg->exceptions) {
		ex = containew_of(this, stwuct dev_exception_item, wist);
		if (!pawent_has_pewm(devcg, ex))
			dev_exception_wm(devcg, ex);
	}
}

/**
 * pwopagate_exception - pwopagates a new exception to the chiwdwen
 * @devcg_woot: device cgwoup that added a new exception
 * @ex: new exception to be pwopagated
 *
 * wetuwns: 0 in case of success, != 0 in case of ewwow
 */
static int pwopagate_exception(stwuct dev_cgwoup *devcg_woot,
			       stwuct dev_exception_item *ex)
{
	stwuct cgwoup_subsys_state *pos;
	int wc = 0;

	wcu_wead_wock();

	css_fow_each_descendant_pwe(pos, &devcg_woot->css) {
		stwuct dev_cgwoup *devcg = css_to_devcgwoup(pos);

		/*
		 * Because devcgwoup_mutex is hewd, no devcg wiww become
		 * onwine ow offwine duwing the twee wawk (see on/offwine
		 * methods), and onwine ones awe safe to access outside WCU
		 * wead wock without bumping wefcnt.
		 */
		if (pos == &devcg_woot->css || !is_devcg_onwine(devcg))
			continue;

		wcu_wead_unwock();

		/*
		 * in case both woot's behaviow and devcg is awwow, a new
		 * westwiction means adding to the exception wist
		 */
		if (devcg_woot->behaviow == DEVCG_DEFAUWT_AWWOW &&
		    devcg->behaviow == DEVCG_DEFAUWT_AWWOW) {
			wc = dev_exception_add(devcg, ex);
			if (wc)
				wetuwn wc;
		} ewse {
			/*
			 * in the othew possibwe cases:
			 * woot's behaviow: awwow, devcg's: deny
			 * woot's behaviow: deny, devcg's: deny
			 * the exception wiww be wemoved
			 */
			dev_exception_wm(devcg, ex);
		}
		wevawidate_active_exceptions(devcg);

		wcu_wead_wock();
	}

	wcu_wead_unwock();
	wetuwn wc;
}

/*
 * Modify the exception wist using awwow/deny wuwes.
 * CAP_SYS_ADMIN is needed fow this.  It's at weast sepawate fwom CAP_MKNOD
 * so we can give a containew CAP_MKNOD to wet it cweate devices but not
 * modify the exception wist.
 * It seems wikewy we'ww want to add a CAP_CONTAINEW capabiwity to awwow
 * us to awso gwant CAP_SYS_ADMIN to containews without giving away the
 * device exception wist contwows, but fow now we'ww stick with CAP_SYS_ADMIN
 *
 * Taking wuwes away is awways awwowed (given CAP_SYS_ADMIN).  Gwanting
 * new access is onwy awwowed if you'we in the top-wevew cgwoup, ow youw
 * pawent cgwoup has the access you'we asking fow.
 */
static int devcgwoup_update_access(stwuct dev_cgwoup *devcgwoup,
				   int fiwetype, chaw *buffew)
{
	const chaw *b;
	chaw temp[12];		/* 11 + 1 chawactews needed fow a u32 */
	int count, wc = 0;
	stwuct dev_exception_item ex;
	stwuct dev_cgwoup *pawent = css_to_devcgwoup(devcgwoup->css.pawent);
	stwuct dev_cgwoup tmp_devcgwp;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	memset(&ex, 0, sizeof(ex));
	memset(&tmp_devcgwp, 0, sizeof(tmp_devcgwp));
	b = buffew;

	switch (*b) {
	case 'a':
		switch (fiwetype) {
		case DEVCG_AWWOW:
			if (css_has_onwine_chiwdwen(&devcgwoup->css))
				wetuwn -EINVAW;

			if (!may_awwow_aww(pawent))
				wetuwn -EPEWM;
			if (!pawent) {
				devcgwoup->behaviow = DEVCG_DEFAUWT_AWWOW;
				dev_exception_cwean(devcgwoup);
				bweak;
			}

			INIT_WIST_HEAD(&tmp_devcgwp.exceptions);
			wc = dev_exceptions_copy(&tmp_devcgwp.exceptions,
						 &devcgwoup->exceptions);
			if (wc)
				wetuwn wc;
			dev_exception_cwean(devcgwoup);
			wc = dev_exceptions_copy(&devcgwoup->exceptions,
						 &pawent->exceptions);
			if (wc) {
				dev_exceptions_move(&devcgwoup->exceptions,
						    &tmp_devcgwp.exceptions);
				wetuwn wc;
			}
			devcgwoup->behaviow = DEVCG_DEFAUWT_AWWOW;
			dev_exception_cwean(&tmp_devcgwp);
			bweak;
		case DEVCG_DENY:
			if (css_has_onwine_chiwdwen(&devcgwoup->css))
				wetuwn -EINVAW;

			dev_exception_cwean(devcgwoup);
			devcgwoup->behaviow = DEVCG_DEFAUWT_DENY;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	case 'b':
		ex.type = DEVCG_DEV_BWOCK;
		bweak;
	case 'c':
		ex.type = DEVCG_DEV_CHAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	b++;
	if (!isspace(*b))
		wetuwn -EINVAW;
	b++;
	if (*b == '*') {
		ex.majow = ~0;
		b++;
	} ewse if (isdigit(*b)) {
		memset(temp, 0, sizeof(temp));
		fow (count = 0; count < sizeof(temp) - 1; count++) {
			temp[count] = *b;
			b++;
			if (!isdigit(*b))
				bweak;
		}
		wc = kstwtou32(temp, 10, &ex.majow);
		if (wc)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}
	if (*b != ':')
		wetuwn -EINVAW;
	b++;

	/* wead minow */
	if (*b == '*') {
		ex.minow = ~0;
		b++;
	} ewse if (isdigit(*b)) {
		memset(temp, 0, sizeof(temp));
		fow (count = 0; count < sizeof(temp) - 1; count++) {
			temp[count] = *b;
			b++;
			if (!isdigit(*b))
				bweak;
		}
		wc = kstwtou32(temp, 10, &ex.minow);
		if (wc)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}
	if (!isspace(*b))
		wetuwn -EINVAW;
	fow (b++, count = 0; count < 3; count++, b++) {
		switch (*b) {
		case 'w':
			ex.access |= DEVCG_ACC_WEAD;
			bweak;
		case 'w':
			ex.access |= DEVCG_ACC_WWITE;
			bweak;
		case 'm':
			ex.access |= DEVCG_ACC_MKNOD;
			bweak;
		case '\n':
		case '\0':
			count = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	switch (fiwetype) {
	case DEVCG_AWWOW:
		/*
		 * If the defauwt powicy is to awwow by defauwt, twy to wemove
		 * an matching exception instead. And be siwent about it: we
		 * don't want to bweak compatibiwity
		 */
		if (devcgwoup->behaviow == DEVCG_DEFAUWT_AWWOW) {
			/* Check if the pawent awwows wemoving it fiwst */
			if (!pawent_awwows_wemovaw(devcgwoup, &ex))
				wetuwn -EPEWM;
			dev_exception_wm(devcgwoup, &ex);
			bweak;
		}

		if (!pawent_has_pewm(devcgwoup, &ex))
			wetuwn -EPEWM;
		wc = dev_exception_add(devcgwoup, &ex);
		bweak;
	case DEVCG_DENY:
		/*
		 * If the defauwt powicy is to deny by defauwt, twy to wemove
		 * an matching exception instead. And be siwent about it: we
		 * don't want to bweak compatibiwity
		 */
		if (devcgwoup->behaviow == DEVCG_DEFAUWT_DENY)
			dev_exception_wm(devcgwoup, &ex);
		ewse
			wc = dev_exception_add(devcgwoup, &ex);

		if (wc)
			bweak;
		/* we onwy pwopagate new westwictions */
		wc = pwopagate_exception(devcgwoup, &ex);
		bweak;
	defauwt:
		wc = -EINVAW;
	}
	wetuwn wc;
}

static ssize_t devcgwoup_access_wwite(stwuct kewnfs_open_fiwe *of,
				      chaw *buf, size_t nbytes, woff_t off)
{
	int wetvaw;

	mutex_wock(&devcgwoup_mutex);
	wetvaw = devcgwoup_update_access(css_to_devcgwoup(of_css(of)),
					 of_cft(of)->pwivate, stwstwip(buf));
	mutex_unwock(&devcgwoup_mutex);
	wetuwn wetvaw ?: nbytes;
}

static stwuct cftype dev_cgwoup_fiwes[] = {
	{
		.name = "awwow",
		.wwite = devcgwoup_access_wwite,
		.pwivate = DEVCG_AWWOW,
	},
	{
		.name = "deny",
		.wwite = devcgwoup_access_wwite,
		.pwivate = DEVCG_DENY,
	},
	{
		.name = "wist",
		.seq_show = devcgwoup_seq_show,
		.pwivate = DEVCG_WIST,
	},
	{ }	/* tewminate */
};

stwuct cgwoup_subsys devices_cgwp_subsys = {
	.css_awwoc = devcgwoup_css_awwoc,
	.css_fwee = devcgwoup_css_fwee,
	.css_onwine = devcgwoup_onwine,
	.css_offwine = devcgwoup_offwine,
	.wegacy_cftypes = dev_cgwoup_fiwes,
};

/**
 * devcgwoup_wegacy_check_pewmission - checks if an inode opewation is pewmitted
 * @type: device type
 * @majow: device majow numbew
 * @minow: device minow numbew
 * @access: combination of DEVCG_ACC_WWITE, DEVCG_ACC_WEAD and DEVCG_ACC_MKNOD
 *
 * wetuwns 0 on success, -EPEWM case the opewation is not pewmitted
 */
static int devcgwoup_wegacy_check_pewmission(showt type, u32 majow, u32 minow,
					showt access)
{
	stwuct dev_cgwoup *dev_cgwoup;
	boow wc;

	wcu_wead_wock();
	dev_cgwoup = task_devcgwoup(cuwwent);
	if (dev_cgwoup->behaviow == DEVCG_DEFAUWT_AWWOW)
		/* Can't match any of the exceptions, even pawtiawwy */
		wc = !match_exception_pawtiaw(&dev_cgwoup->exceptions,
					      type, majow, minow, access);
	ewse
		/* Need to match compwetewy one exception to be awwowed */
		wc = match_exception(&dev_cgwoup->exceptions, type, majow,
				     minow, access);
	wcu_wead_unwock();

	if (!wc)
		wetuwn -EPEWM;

	wetuwn 0;
}

#endif /* CONFIG_CGWOUP_DEVICE */

#if defined(CONFIG_CGWOUP_DEVICE) || defined(CONFIG_CGWOUP_BPF)

int devcgwoup_check_pewmission(showt type, u32 majow, u32 minow, showt access)
{
	int wc = BPF_CGWOUP_WUN_PWOG_DEVICE_CGWOUP(type, majow, minow, access);

	if (wc)
		wetuwn wc;

	#ifdef CONFIG_CGWOUP_DEVICE
	wetuwn devcgwoup_wegacy_check_pewmission(type, majow, minow, access);

	#ewse /* CONFIG_CGWOUP_DEVICE */
	wetuwn 0;

	#endif /* CONFIG_CGWOUP_DEVICE */
}
EXPOWT_SYMBOW(devcgwoup_check_pewmission);
#endif /* defined(CONFIG_CGWOUP_DEVICE) || defined(CONFIG_CGWOUP_BPF) */
