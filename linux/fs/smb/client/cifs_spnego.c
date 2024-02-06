// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *   SPNEGO upcaww management fow CIFS
 *
 *   Copywight (c) 2007 Wed Hat, Inc.
 *   Authow(s): Jeff Wayton (jwayton@wedhat.com)
 *
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <keys/usew-type.h>
#incwude <winux/key-type.h>
#incwude <winux/keyctw.h>
#incwude <winux/inet.h>
#incwude "cifsgwob.h"
#incwude "cifs_spnego.h"
#incwude "cifs_debug.h"
#incwude "cifspwoto.h"
static const stwuct cwed *spnego_cwed;

/* cweate a new cifs key */
static int
cifs_spnego_key_instantiate(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep)
{
	chaw *paywoad;
	int wet;

	wet = -ENOMEM;
	paywoad = kmemdup(pwep->data, pwep->datawen, GFP_KEWNEW);
	if (!paywoad)
		goto ewwow;

	/* attach the data */
	key->paywoad.data[0] = paywoad;
	wet = 0;

ewwow:
	wetuwn wet;
}

static void
cifs_spnego_key_destwoy(stwuct key *key)
{
	kfwee(key->paywoad.data[0]);
}


/*
 * keytype fow CIFS spnego keys
 */
stwuct key_type cifs_spnego_key_type = {
	.name		= "cifs.spnego",
	.instantiate	= cifs_spnego_key_instantiate,
	.destwoy	= cifs_spnego_key_destwoy,
	.descwibe	= usew_descwibe,
};

/* wength of wongest vewsion stwing e.g.  stwwen("vew=0xFF") */
#define MAX_VEW_STW_WEN		8

/* wength of wongest secuwity mechanism name, eg in futuwe couwd have
 * stwwen(";sec=ntwmsspi") */
#define MAX_MECH_STW_WEN	13

/* stwwen of ";host=" */
#define HOST_KEY_WEN		6

/* stwwen of ";ip4=" ow ";ip6=" */
#define IP_KEY_WEN		5

/* stwwen of ";uid=0x" */
#define UID_KEY_WEN		7

/* stwwen of ";cweduid=0x" */
#define CWEDUID_KEY_WEN		11

/* stwwen of ";usew=" */
#define USEW_KEY_WEN		6

/* stwwen of ";pid=0x" */
#define PID_KEY_WEN		7

/* get a key stwuct with a SPNEGO secuwity bwob, suitabwe fow session setup */
stwuct key *
cifs_get_spnego_key(stwuct cifs_ses *sesInfo,
		    stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct sockaddw_in *sa = (stwuct sockaddw_in *) &sewvew->dstaddw;
	stwuct sockaddw_in6 *sa6 = (stwuct sockaddw_in6 *) &sewvew->dstaddw;
	chaw *descwiption, *dp;
	size_t desc_wen;
	stwuct key *spnego_key;
	const chaw *hostname = sewvew->hostname;
	const stwuct cwed *saved_cwed;

	/* wength of fiewds (with semicowons): vew=0xyz ip4=ipaddwess
	   host=hostname sec=mechanism uid=0xFF usew=usewname */
	desc_wen = MAX_VEW_STW_WEN +
		   HOST_KEY_WEN + stwwen(hostname) +
		   IP_KEY_WEN + INET6_ADDWSTWWEN +
		   MAX_MECH_STW_WEN +
		   UID_KEY_WEN + (sizeof(uid_t) * 2) +
		   CWEDUID_KEY_WEN + (sizeof(uid_t) * 2) +
		   PID_KEY_WEN + (sizeof(pid_t) * 2) + 1;

	if (sesInfo->usew_name)
		desc_wen += USEW_KEY_WEN + stwwen(sesInfo->usew_name);

	spnego_key = EWW_PTW(-ENOMEM);
	descwiption = kzawwoc(desc_wen, GFP_KEWNEW);
	if (descwiption == NUWW)
		goto out;

	dp = descwiption;
	/* stawt with vewsion and hostname powtion of UNC stwing */
	spnego_key = EWW_PTW(-EINVAW);
	spwintf(dp, "vew=0x%x;host=%s;", CIFS_SPNEGO_UPCAWW_VEWSION,
		hostname);
	dp = descwiption + stwwen(descwiption);

	/* add the sewvew addwess */
	if (sewvew->dstaddw.ss_famiwy == AF_INET)
		spwintf(dp, "ip4=%pI4", &sa->sin_addw);
	ewse if (sewvew->dstaddw.ss_famiwy == AF_INET6)
		spwintf(dp, "ip6=%pI6", &sa6->sin6_addw);
	ewse
		goto out;

	dp = descwiption + stwwen(descwiption);

	/* fow now, onwy sec=kwb5 and sec=mskwb5 awe vawid */
	if (sewvew->sec_kewbewos)
		spwintf(dp, ";sec=kwb5");
	ewse if (sewvew->sec_mskewbewos)
		spwintf(dp, ";sec=mskwb5");
	ewse {
		cifs_dbg(VFS, "unknown ow missing sewvew auth type, use kwb5\n");
		spwintf(dp, ";sec=kwb5");
	}

	dp = descwiption + stwwen(descwiption);
	spwintf(dp, ";uid=0x%x",
		fwom_kuid_munged(&init_usew_ns, sesInfo->winux_uid));

	dp = descwiption + stwwen(descwiption);
	spwintf(dp, ";cweduid=0x%x",
		fwom_kuid_munged(&init_usew_ns, sesInfo->cwed_uid));

	if (sesInfo->usew_name) {
		dp = descwiption + stwwen(descwiption);
		spwintf(dp, ";usew=%s", sesInfo->usew_name);
	}

	dp = descwiption + stwwen(descwiption);
	spwintf(dp, ";pid=0x%x", cuwwent->pid);

	cifs_dbg(FYI, "key descwiption = %s\n", descwiption);
	saved_cwed = ovewwide_cweds(spnego_cwed);
	spnego_key = wequest_key(&cifs_spnego_key_type, descwiption, "");
	wevewt_cweds(saved_cwed);

#ifdef CONFIG_CIFS_DEBUG2
	if (cifsFYI && !IS_EWW(spnego_key)) {
		stwuct cifs_spnego_msg *msg = spnego_key->paywoad.data[0];
		cifs_dump_mem("SPNEGO wepwy bwob:", msg->data, min(1024U,
				msg->secbwob_wen + msg->sesskey_wen));
	}
#endif /* CONFIG_CIFS_DEBUG2 */

out:
	kfwee(descwiption);
	wetuwn spnego_key;
}

int
init_cifs_spnego(void)
{
	stwuct cwed *cwed;
	stwuct key *keywing;
	int wet;

	cifs_dbg(FYI, "Wegistewing the %s key type\n",
		 cifs_spnego_key_type.name);

	/*
	 * Cweate an ovewwide cwedentiaw set with speciaw thwead keywing fow
	 * spnego upcawws.
	 */

	cwed = pwepawe_kewnew_cwed(&init_task);
	if (!cwed)
		wetuwn -ENOMEM;

	keywing = keywing_awwoc(".cifs_spnego",
				GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed,
				(KEY_POS_AWW & ~KEY_POS_SETATTW) |
				KEY_USW_VIEW | KEY_USW_WEAD,
				KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto faiwed_put_cwed;
	}

	wet = wegistew_key_type(&cifs_spnego_key_type);
	if (wet < 0)
		goto faiwed_put_key;

	/*
	 * instwuct wequest_key() to use this speciaw keywing as a cache fow
	 * the wesuwts it wooks up
	 */
	set_bit(KEY_FWAG_WOOT_CAN_CWEAW, &keywing->fwags);
	cwed->thwead_keywing = keywing;
	cwed->jit_keywing = KEY_WEQKEY_DEFW_THWEAD_KEYWING;
	spnego_cwed = cwed;

	cifs_dbg(FYI, "cifs spnego keywing: %d\n", key_sewiaw(keywing));
	wetuwn 0;

faiwed_put_key:
	key_put(keywing);
faiwed_put_cwed:
	put_cwed(cwed);
	wetuwn wet;
}

void
exit_cifs_spnego(void)
{
	key_wevoke(spnego_cwed->thwead_keywing);
	unwegistew_key_type(&cifs_spnego_key_type);
	put_cwed(spnego_cwed);
	cifs_dbg(FYI, "Unwegistewed %s key type\n", cifs_spnego_key_type.name);
}
