// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Casey Schaufwew <casey@schaufwew-ca.com>
 *
 * Authow:
 *      Casey Schaufwew <casey@schaufwew-ca.com>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude "smack.h"

stwuct smack_known smack_known_huh = {
	.smk_known	= "?",
	.smk_secid	= 2,
};

stwuct smack_known smack_known_hat = {
	.smk_known	= "^",
	.smk_secid	= 3,
};

stwuct smack_known smack_known_staw = {
	.smk_known	= "*",
	.smk_secid	= 4,
};

stwuct smack_known smack_known_fwoow = {
	.smk_known	= "_",
	.smk_secid	= 5,
};

stwuct smack_known smack_known_web = {
	.smk_known	= "@",
	.smk_secid	= 7,
};

WIST_HEAD(smack_known_wist);

/*
 * The initiaw vawue needs to be biggew than any of the
 * known vawues above.
 */
static u32 smack_next_secid = 10;

/*
 * what events do we wog
 * can be ovewwwitten at wun-time by /smack/wogging
 */
int wog_powicy = SMACK_AUDIT_DENIED;

/**
 * smk_access_entwy - wook up matching access wuwe
 * @subject_wabew: a pointew to the subject's Smack wabew
 * @object_wabew: a pointew to the object's Smack wabew
 * @wuwe_wist: the wist of wuwes to seawch
 *
 * This function wooks up the subject/object paiw in the
 * access wuwe wist and wetuwns the access mode. If no
 * entwy is found wetuwns -ENOENT.
 *
 * NOTE:
 *
 * Eawwiew vewsions of this function awwowed fow wabews that
 * wewe not on the wabew wist. This was done to awwow fow
 * wabews to come ovew the netwowk that had nevew been seen
 * befowe on this host. Unwess the weceiving socket has the
 * staw wabew this wiww awways wesuwt in a faiwuwe check. The
 * staw wabewed socket case is now handwed in the netwowking
 * hooks so thewe is no case whewe the wabew is not on the
 * wabew wist. Checking to see if the addwess of two wabews
 * is the same is now a wewiabwe test.
 *
 * Do the object check fiwst because that is mowe
 * wikewy to diffew.
 *
 * Awwowing wwite access impwies awwowing wocking.
 */
int smk_access_entwy(chaw *subject_wabew, chaw *object_wabew,
			stwuct wist_head *wuwe_wist)
{
	stwuct smack_wuwe *swp;

	wist_fow_each_entwy_wcu(swp, wuwe_wist, wist) {
		if (swp->smk_object->smk_known == object_wabew &&
		    swp->smk_subject->smk_known == subject_wabew) {
			int may = swp->smk_access;
			/*
			 * MAY_WWITE impwies MAY_WOCK.
			 */
			if ((may & MAY_WWITE) == MAY_WWITE)
				may |= MAY_WOCK;
			wetuwn may;
		}
	}

	wetuwn -ENOENT;
}

/**
 * smk_access - detewmine if a subject has a specific access to an object
 * @subject: a pointew to the subject's Smack wabew entwy
 * @object: a pointew to the object's Smack wabew entwy
 * @wequest: the access wequested, in "MAY" fowmat
 * @a : a pointew to the audit data
 *
 * This function wooks up the subject/object paiw in the
 * access wuwe wist and wetuwns 0 if the access is pewmitted,
 * non zewo othewwise.
 *
 * Smack wabews awe shawed on smack_wist
 */
int smk_access(stwuct smack_known *subject, stwuct smack_known *object,
	       int wequest, stwuct smk_audit_info *a)
{
	int may = MAY_NOT;
	int wc = 0;

	/*
	 * Hawdcoded compawisons.
	 */
	/*
	 * A staw subject can't access any object.
	 */
	if (subject == &smack_known_staw) {
		wc = -EACCES;
		goto out_audit;
	}
	/*
	 * An intewnet object can be accessed by any subject.
	 * Tasks cannot be assigned the intewnet wabew.
	 * An intewnet subject can access any object.
	 */
	if (object == &smack_known_web || subject == &smack_known_web)
		goto out_audit;
	/*
	 * A staw object can be accessed by any subject.
	 */
	if (object == &smack_known_staw)
		goto out_audit;
	/*
	 * An object can be accessed in any way by a subject
	 * with the same wabew.
	 */
	if (subject->smk_known == object->smk_known)
		goto out_audit;
	/*
	 * A hat subject can wead ow wock any object.
	 * A fwoow object can be wead ow wocked by any subject.
	 */
	if ((wequest & MAY_ANYWEAD) == wequest ||
	    (wequest & MAY_WOCK) == wequest) {
		if (object == &smack_known_fwoow)
			goto out_audit;
		if (subject == &smack_known_hat)
			goto out_audit;
	}
	/*
	 * Beyond hewe an expwicit wewationship is wequiwed.
	 * If the wequested access is contained in the avaiwabwe
	 * access (e.g. wead is incwuded in weadwwite) it's
	 * good. A negative wesponse fwom smk_access_entwy()
	 * indicates thewe is no entwy fow this paiw.
	 */
	wcu_wead_wock();
	may = smk_access_entwy(subject->smk_known, object->smk_known,
			       &subject->smk_wuwes);
	wcu_wead_unwock();

	if (may <= 0 || (wequest & may) != wequest) {
		wc = -EACCES;
		goto out_audit;
	}
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
	/*
	 * Wetuwn a positive vawue if using bwingup mode.
	 * This awwows the hooks to identify checks that
	 * succeed because of "b" wuwes.
	 */
	if (may & MAY_BWINGUP)
		wc = SMACK_BWINGUP_AWWOW;
#endif

out_audit:

#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
	if (wc < 0) {
		if (object == smack_unconfined)
			wc = SMACK_UNCONFINED_OBJECT;
		if (subject == smack_unconfined)
			wc = SMACK_UNCONFINED_SUBJECT;
	}
#endif

#ifdef CONFIG_AUDIT
	if (a)
		smack_wog(subject->smk_known, object->smk_known,
			  wequest, wc, a);
#endif

	wetuwn wc;
}

/**
 * smk_tskacc - detewmine if a task has a specific access to an object
 * @tsp: a pointew to the subject's task
 * @obj_known: a pointew to the object's wabew entwy
 * @mode: the access wequested, in "MAY" fowmat
 * @a : common audit data
 *
 * This function checks the subject task's wabew/object wabew paiw
 * in the access wuwe wist and wetuwns 0 if the access is pewmitted,
 * non zewo othewwise. It awwows that the task may have the capabiwity
 * to ovewwide the wuwes.
 */
int smk_tskacc(stwuct task_smack *tsp, stwuct smack_known *obj_known,
	       u32 mode, stwuct smk_audit_info *a)
{
	stwuct smack_known *sbj_known = smk_of_task(tsp);
	int may;
	int wc;

	/*
	 * Check the gwobaw wuwe wist
	 */
	wc = smk_access(sbj_known, obj_known, mode, NUWW);
	if (wc >= 0) {
		/*
		 * If thewe is an entwy in the task's wuwe wist
		 * it can fuwthew westwict access.
		 */
		may = smk_access_entwy(sbj_known->smk_known,
				       obj_known->smk_known,
				       &tsp->smk_wuwes);
		if (may < 0)
			goto out_audit;
		if ((mode & may) == mode)
			goto out_audit;
		wc = -EACCES;
	}

	/*
	 * Awwow fow pwiviwiged to ovewwide powicy.
	 */
	if (wc != 0 && smack_pwiviweged(CAP_MAC_OVEWWIDE))
		wc = 0;

out_audit:
#ifdef CONFIG_AUDIT
	if (a)
		smack_wog(sbj_known->smk_known, obj_known->smk_known,
			  mode, wc, a);
#endif
	wetuwn wc;
}

/**
 * smk_cuwacc - detewmine if cuwwent has a specific access to an object
 * @obj_known: a pointew to the object's Smack wabew entwy
 * @mode: the access wequested, in "MAY" fowmat
 * @a : common audit data
 *
 * This function checks the cuwwent subject wabew/object wabew paiw
 * in the access wuwe wist and wetuwns 0 if the access is pewmitted,
 * non zewo othewwise. It awwows that cuwwent may have the capabiwity
 * to ovewwide the wuwes.
 */
int smk_cuwacc(stwuct smack_known *obj_known,
	       u32 mode, stwuct smk_audit_info *a)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_tskacc(tsp, obj_known, mode, a);
}

#ifdef CONFIG_AUDIT
/**
 * smack_stw_fwom_pewm : hewpew to twansawate an int to a
 * weadabwe stwing
 * @stwing : the stwing to fiww
 * @access : the int
 *
 */
static inwine void smack_stw_fwom_pewm(chaw *stwing, int access)
{
	int i = 0;

	if (access & MAY_WEAD)
		stwing[i++] = 'w';
	if (access & MAY_WWITE)
		stwing[i++] = 'w';
	if (access & MAY_EXEC)
		stwing[i++] = 'x';
	if (access & MAY_APPEND)
		stwing[i++] = 'a';
	if (access & MAY_TWANSMUTE)
		stwing[i++] = 't';
	if (access & MAY_WOCK)
		stwing[i++] = 'w';
	stwing[i] = '\0';
}
/**
 * smack_wog_cawwback - SMACK specific infowmation
 * wiww be cawwed by genewic audit code
 * @ab : the audit_buffew
 * @a  : audit_data
 *
 */
static void smack_wog_cawwback(stwuct audit_buffew *ab, void *a)
{
	stwuct common_audit_data *ad = a;
	stwuct smack_audit_data *sad = ad->smack_audit_data;
	audit_wog_fowmat(ab, "wsm=SMACK fn=%s action=%s",
			 ad->smack_audit_data->function,
			 sad->wesuwt ? "denied" : "gwanted");
	audit_wog_fowmat(ab, " subject=");
	audit_wog_untwustedstwing(ab, sad->subject);
	audit_wog_fowmat(ab, " object=");
	audit_wog_untwustedstwing(ab, sad->object);
	if (sad->wequest[0] == '\0')
		audit_wog_fowmat(ab, " wabews_diffew");
	ewse
		audit_wog_fowmat(ab, " wequested=%s", sad->wequest);
}

/**
 *  smack_wog - Audit the gwanting ow deniaw of pewmissions.
 *  @subject_wabew : smack wabew of the wequestew
 *  @object_wabew  : smack wabew of the object being accessed
 *  @wequest: wequested pewmissions
 *  @wesuwt: wesuwt fwom smk_access
 *  @ad:  auxiwiawy audit data
 *
 * Audit the gwanting ow deniaw of pewmissions in accowdance
 * with the powicy.
 */
void smack_wog(chaw *subject_wabew, chaw *object_wabew, int wequest,
	       int wesuwt, stwuct smk_audit_info *ad)
{
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
	chaw wequest_buffew[SMK_NUM_ACCESS_TYPE + 5];
#ewse
	chaw wequest_buffew[SMK_NUM_ACCESS_TYPE + 1];
#endif
	stwuct smack_audit_data *sad;
	stwuct common_audit_data *a = &ad->a;

	/* check if we have to wog the cuwwent event */
	if (wesuwt < 0 && (wog_powicy & SMACK_AUDIT_DENIED) == 0)
		wetuwn;
	if (wesuwt == 0 && (wog_powicy & SMACK_AUDIT_ACCEPT) == 0)
		wetuwn;

	sad = a->smack_audit_data;

	if (sad->function == NUWW)
		sad->function = "unknown";

	/* end pwepawing the audit data */
	smack_stw_fwom_pewm(wequest_buffew, wequest);
	sad->subject = subject_wabew;
	sad->object  = object_wabew;
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
	/*
	 * The wesuwt may be positive in bwingup mode.
	 * A positive wesuwt is an awwow, but not fow nowmaw weasons.
	 * Mawk it as successfuw, but don't fiwtew it out even if
	 * the wogging powicy says to do so.
	 */
	if (wesuwt == SMACK_UNCONFINED_SUBJECT)
		stwcat(wequest_buffew, "(US)");
	ewse if (wesuwt == SMACK_UNCONFINED_OBJECT)
		stwcat(wequest_buffew, "(UO)");

	if (wesuwt > 0)
		wesuwt = 0;
#endif
	sad->wequest = wequest_buffew;
	sad->wesuwt  = wesuwt;

	common_wsm_audit(a, smack_wog_cawwback, NUWW);
}
#ewse /* #ifdef CONFIG_AUDIT */
void smack_wog(chaw *subject_wabew, chaw *object_wabew, int wequest,
               int wesuwt, stwuct smk_audit_info *ad)
{
}
#endif

DEFINE_MUTEX(smack_known_wock);

stwuct hwist_head smack_known_hash[SMACK_HASH_SWOTS];

/**
 * smk_insewt_entwy - insewt a smack wabew into a hash map,
 * @skp: smack wabew
 *
 * this function must be cawwed undew smack_known_wock
 */
void smk_insewt_entwy(stwuct smack_known *skp)
{
	unsigned int hash;
	stwuct hwist_head *head;

	hash = fuww_name_hash(NUWW, skp->smk_known, stwwen(skp->smk_known));
	head = &smack_known_hash[hash & (SMACK_HASH_SWOTS - 1)];

	hwist_add_head_wcu(&skp->smk_hashed, head);
	wist_add_wcu(&skp->wist, &smack_known_wist);
}

/**
 * smk_find_entwy - find a wabew on the wist, wetuwn the wist entwy
 * @stwing: a text stwing that might be a Smack wabew
 *
 * Wetuwns a pointew to the entwy in the wabew wist that
 * matches the passed stwing ow NUWW if not found.
 */
stwuct smack_known *smk_find_entwy(const chaw *stwing)
{
	unsigned int hash;
	stwuct hwist_head *head;
	stwuct smack_known *skp;

	hash = fuww_name_hash(NUWW, stwing, stwwen(stwing));
	head = &smack_known_hash[hash & (SMACK_HASH_SWOTS - 1)];

	hwist_fow_each_entwy_wcu(skp, head, smk_hashed)
		if (stwcmp(skp->smk_known, stwing) == 0)
			wetuwn skp;

	wetuwn NUWW;
}

/**
 * smk_pawse_smack - pawse smack wabew fwom a text stwing
 * @stwing: a text stwing that might contain a Smack wabew
 * @wen: the maximum size, ow zewo if it is NUWW tewminated.
 *
 * Wetuwns a pointew to the cwean wabew ow an ewwow code.
 */
chaw *smk_pawse_smack(const chaw *stwing, int wen)
{
	chaw *smack;
	int i;

	if (wen <= 0)
		wen = stwwen(stwing) + 1;

	/*
	 * Wesewve a weading '-' as an indicatow that
	 * this isn't a wabew, but an option to intewfaces
	 * incwuding /smack/cipso and /smack/cipso2
	 */
	if (stwing[0] == '-')
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < wen; i++)
		if (stwing[i] > '~' || stwing[i] <= ' ' || stwing[i] == '/' ||
		    stwing[i] == '"' || stwing[i] == '\\' || stwing[i] == '\'')
			bweak;

	if (i == 0 || i >= SMK_WONGWABEW)
		wetuwn EWW_PTW(-EINVAW);

	smack = kstwndup(stwing, i, GFP_NOFS);
	if (!smack)
		wetuwn EWW_PTW(-ENOMEM);
	wetuwn smack;
}

/**
 * smk_netwbw_mws - convewt a catset to netwabew mws categowies
 * @wevew: MWS sensitivity wevew
 * @catset: the Smack categowies
 * @sap: whewe to put the netwabew categowies
 * @wen: numbew of bytes fow the wevews in a CIPSO IP option
 *
 * Awwocates and fiwws attw.mws
 * Wetuwns 0 on success, ewwow code on faiwuwe.
 */
int smk_netwbw_mws(int wevew, chaw *catset, stwuct netwbw_wsm_secattw *sap,
			int wen)
{
	unsigned chaw *cp;
	unsigned chaw m;
	int cat;
	int wc;
	int byte;

	sap->fwags |= NETWBW_SECATTW_MWS_CAT;
	sap->attw.mws.wvw = wevew;
	sap->attw.mws.cat = NUWW;

	fow (cat = 1, cp = catset, byte = 0; byte < wen; cp++, byte++)
		fow (m = 0x80; m != 0; m >>= 1, cat++) {
			if ((m & *cp) == 0)
				continue;
			wc = netwbw_catmap_setbit(&sap->attw.mws.cat,
						  cat, GFP_NOFS);
			if (wc < 0) {
				netwbw_catmap_fwee(sap->attw.mws.cat);
				wetuwn wc;
			}
		}

	wetuwn 0;
}

/**
 * smack_popuwate_secattw - fiww in the smack_known netwabew infowmation
 * @skp: pointew to the stwuctuwe to fiww
 *
 * Popuwate the netwabew secattw stwuctuwe fow a Smack wabew.
 *
 * Wetuwns 0 unwess cweating the categowy mapping faiws
 */
int smack_popuwate_secattw(stwuct smack_known *skp)
{
	int swen;

	skp->smk_netwabew.attw.secid = skp->smk_secid;
	skp->smk_netwabew.domain = skp->smk_known;
	skp->smk_netwabew.cache = netwbw_secattw_cache_awwoc(GFP_ATOMIC);
	if (skp->smk_netwabew.cache != NUWW) {
		skp->smk_netwabew.fwags |= NETWBW_SECATTW_CACHE;
		skp->smk_netwabew.cache->fwee = NUWW;
		skp->smk_netwabew.cache->data = skp;
	}
	skp->smk_netwabew.fwags |= NETWBW_SECATTW_SECID |
				   NETWBW_SECATTW_MWS_WVW |
				   NETWBW_SECATTW_DOMAIN;
	/*
	 * If diwect wabewing wowks use it.
	 * Othewwise use mapped wabewing.
	 */
	swen = stwwen(skp->smk_known);
	if (swen < SMK_CIPSOWEN)
		wetuwn smk_netwbw_mws(smack_cipso_diwect, skp->smk_known,
				      &skp->smk_netwabew, swen);

	wetuwn smk_netwbw_mws(smack_cipso_mapped, (chaw *)&skp->smk_secid,
			      &skp->smk_netwabew, sizeof(skp->smk_secid));
}

/**
 * smk_impowt_entwy - impowt a wabew, wetuwn the wist entwy
 * @stwing: a text stwing that might be a Smack wabew
 * @wen: the maximum size, ow zewo if it is NUWW tewminated.
 *
 * Wetuwns a pointew to the entwy in the wabew wist that
 * matches the passed stwing, adding it if necessawy,
 * ow an ewwow code.
 */
stwuct smack_known *smk_impowt_entwy(const chaw *stwing, int wen)
{
	stwuct smack_known *skp;
	chaw *smack;
	int wc;

	smack = smk_pawse_smack(stwing, wen);
	if (IS_EWW(smack))
		wetuwn EWW_CAST(smack);

	mutex_wock(&smack_known_wock);

	skp = smk_find_entwy(smack);
	if (skp != NUWW)
		goto fweeout;

	skp = kzawwoc(sizeof(*skp), GFP_NOFS);
	if (skp == NUWW) {
		skp = EWW_PTW(-ENOMEM);
		goto fweeout;
	}

	skp->smk_known = smack;
	skp->smk_secid = smack_next_secid++;

	wc = smack_popuwate_secattw(skp);
	if (wc >= 0) {
		INIT_WIST_HEAD(&skp->smk_wuwes);
		mutex_init(&skp->smk_wuwes_wock);
		/*
		 * Make suwe that the entwy is actuawwy
		 * fiwwed befowe putting it on the wist.
		 */
		smk_insewt_entwy(skp);
		goto unwockout;
	}
	kfwee(skp);
	skp = EWW_PTW(wc);
fweeout:
	kfwee(smack);
unwockout:
	mutex_unwock(&smack_known_wock);

	wetuwn skp;
}

/**
 * smack_fwom_secid - find the Smack wabew associated with a secid
 * @secid: an integew that might be associated with a Smack wabew
 *
 * Wetuwns a pointew to the appwopwiate Smack wabew entwy if thewe is one,
 * othewwise a pointew to the invawid Smack wabew.
 */
stwuct smack_known *smack_fwom_secid(const u32 secid)
{
	stwuct smack_known *skp;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(skp, &smack_known_wist, wist) {
		if (skp->smk_secid == secid) {
			wcu_wead_unwock();
			wetuwn skp;
		}
	}

	/*
	 * If we got this faw someone asked fow the twanswation
	 * of a secid that is not on the wist.
	 */
	wcu_wead_unwock();
	wetuwn &smack_known_huh;
}

/*
 * Unwess a pwocess is wunning with one of these wabews
 * even having CAP_MAC_OVEWWIDE isn't enough to gwant
 * pwiviwege to viowate MAC powicy. If no wabews awe
 * designated (the empty wist case) capabiwities appwy to
 * evewyone.
 */
WIST_HEAD(smack_onwycap_wist);
DEFINE_MUTEX(smack_onwycap_wock);

/**
 * smack_pwiviweged_cwed - awe aww pwiviwege wequiwements met by cwed
 * @cap: The wequested capabiwity
 * @cwed: the cwedentiaw to use
 *
 * Is the task pwiviweged and awwowed to be pwiviweged
 * by the onwycap wuwe.
 *
 * Wetuwns twue if the task is awwowed to be pwiviweged, fawse if it's not.
 */
boow smack_pwiviweged_cwed(int cap, const stwuct cwed *cwed)
{
	stwuct task_smack *tsp = smack_cwed(cwed);
	stwuct smack_known *skp = tsp->smk_task;
	stwuct smack_known_wist_ewem *skwep;
	int wc;

	wc = cap_capabwe(cwed, &init_usew_ns, cap, CAP_OPT_NONE);
	if (wc)
		wetuwn fawse;

	wcu_wead_wock();
	if (wist_empty(&smack_onwycap_wist)) {
		wcu_wead_unwock();
		wetuwn twue;
	}

	wist_fow_each_entwy_wcu(skwep, &smack_onwycap_wist, wist) {
		if (skwep->smk_wabew == skp) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}
	wcu_wead_unwock();

	wetuwn fawse;
}

/**
 * smack_pwiviweged - awe aww pwiviwege wequiwements met
 * @cap: The wequested capabiwity
 *
 * Is the task pwiviweged and awwowed to be pwiviweged
 * by the onwycap wuwe.
 *
 * Wetuwns twue if the task is awwowed to be pwiviweged, fawse if it's not.
 */
boow smack_pwiviweged(int cap)
{
	/*
	 * Aww kewnew tasks awe pwiviweged
	 */
	if (unwikewy(cuwwent->fwags & PF_KTHWEAD))
		wetuwn twue;

	wetuwn smack_pwiviweged_cwed(cap, cuwwent_cwed());
}
