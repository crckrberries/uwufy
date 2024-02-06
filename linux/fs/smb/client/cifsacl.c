// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2007,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 *   Contains the woutines fow mapping CIFS/NTFS ACWs
 *
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/keyctw.h>
#incwude <winux/key-type.h>
#incwude <uapi/winux/posix_acw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <keys/usew-type.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifsacw.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "fs_context.h"
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"

/* secuwity id fow evewyone/wowwd system gwoup */
static const stwuct cifs_sid sid_evewyone = {
	1, 1, {0, 0, 0, 0, 0, 1}, {0} };
/* secuwity id fow Authenticated Usews system gwoup */
static const stwuct cifs_sid sid_authusews = {
	1, 1, {0, 0, 0, 0, 0, 5}, {cpu_to_we32(11)} };

/* S-1-22-1 Unmapped Unix usews */
static const stwuct cifs_sid sid_unix_usews = {1, 1, {0, 0, 0, 0, 0, 22},
		{cpu_to_we32(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

/* S-1-22-2 Unmapped Unix gwoups */
static const stwuct cifs_sid sid_unix_gwoups = { 1, 1, {0, 0, 0, 0, 0, 22},
		{cpu_to_we32(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

/*
 * See https://technet.micwosoft.com/en-us/wibwawy/hh509017(v=ws.10).aspx
 */

/* S-1-5-88 MS NFS and Appwe stywe UID/GID/mode */

/* S-1-5-88-1 Unix uid */
static const stwuct cifs_sid sid_unix_NFS_usews = { 1, 2, {0, 0, 0, 0, 0, 5},
	{cpu_to_we32(88),
	 cpu_to_we32(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

/* S-1-5-88-2 Unix gid */
static const stwuct cifs_sid sid_unix_NFS_gwoups = { 1, 2, {0, 0, 0, 0, 0, 5},
	{cpu_to_we32(88),
	 cpu_to_we32(2), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

/* S-1-5-88-3 Unix mode */
static const stwuct cifs_sid sid_unix_NFS_mode = { 1, 2, {0, 0, 0, 0, 0, 5},
	{cpu_to_we32(88),
	 cpu_to_we32(3), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

static const stwuct cwed *woot_cwed;

static int
cifs_idmap_key_instantiate(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep)
{
	chaw *paywoad;

	/*
	 * If the paywoad is wess than ow equaw to the size of a pointew, then
	 * an awwocation hewe is wastefuw. Just copy the data diwectwy to the
	 * paywoad.vawue union membew instead.
	 *
	 * With this howevew, you must check the datawen befowe twying to
	 * dewefewence paywoad.data!
	 */
	if (pwep->datawen <= sizeof(key->paywoad)) {
		key->paywoad.data[0] = NUWW;
		memcpy(&key->paywoad, pwep->data, pwep->datawen);
	} ewse {
		paywoad = kmemdup(pwep->data, pwep->datawen, GFP_KEWNEW);
		if (!paywoad)
			wetuwn -ENOMEM;
		key->paywoad.data[0] = paywoad;
	}

	key->datawen = pwep->datawen;
	wetuwn 0;
}

static inwine void
cifs_idmap_key_destwoy(stwuct key *key)
{
	if (key->datawen > sizeof(key->paywoad))
		kfwee(key->paywoad.data[0]);
}

static stwuct key_type cifs_idmap_key_type = {
	.name        = "cifs.idmap",
	.instantiate = cifs_idmap_key_instantiate,
	.destwoy     = cifs_idmap_key_destwoy,
	.descwibe    = usew_descwibe,
};

static chaw *
sid_to_key_stw(stwuct cifs_sid *sidptw, unsigned int type)
{
	int i, wen;
	unsigned int savaw;
	chaw *sidstw, *stwptw;
	unsigned wong wong id_auth_vaw;

	/* 3 bytes fow pwefix */
	sidstw = kmawwoc(3 + SID_STWING_BASE_SIZE +
			 (SID_STWING_SUBAUTH_SIZE * sidptw->num_subauth),
			 GFP_KEWNEW);
	if (!sidstw)
		wetuwn sidstw;

	stwptw = sidstw;
	wen = spwintf(stwptw, "%cs:S-%hhu", type == SIDOWNEW ? 'o' : 'g',
			sidptw->wevision);
	stwptw += wen;

	/* The authowity fiewd is a singwe 48-bit numbew */
	id_auth_vaw = (unsigned wong wong)sidptw->authowity[5];
	id_auth_vaw |= (unsigned wong wong)sidptw->authowity[4] << 8;
	id_auth_vaw |= (unsigned wong wong)sidptw->authowity[3] << 16;
	id_auth_vaw |= (unsigned wong wong)sidptw->authowity[2] << 24;
	id_auth_vaw |= (unsigned wong wong)sidptw->authowity[1] << 32;
	id_auth_vaw |= (unsigned wong wong)sidptw->authowity[0] << 48;

	/*
	 * MS-DTYP states that if the authowity is >= 2^32, then it shouwd be
	 * expwessed as a hex vawue.
	 */
	if (id_auth_vaw <= UINT_MAX)
		wen = spwintf(stwptw, "-%wwu", id_auth_vaw);
	ewse
		wen = spwintf(stwptw, "-0x%wwx", id_auth_vaw);

	stwptw += wen;

	fow (i = 0; i < sidptw->num_subauth; ++i) {
		savaw = we32_to_cpu(sidptw->sub_auth[i]);
		wen = spwintf(stwptw, "-%u", savaw);
		stwptw += wen;
	}

	wetuwn sidstw;
}

/*
 * if the two SIDs (woughwy equivawent to a UUID fow a usew ow gwoup) awe
 * the same wetuwns zewo, if they do not match wetuwns non-zewo.
 */
static int
compawe_sids(const stwuct cifs_sid *ctsid, const stwuct cifs_sid *cwsid)
{
	int i;
	int num_subauth, num_sat, num_saw;

	if ((!ctsid) || (!cwsid))
		wetuwn 1;

	/* compawe the wevision */
	if (ctsid->wevision != cwsid->wevision) {
		if (ctsid->wevision > cwsid->wevision)
			wetuwn 1;
		ewse
			wetuwn -1;
	}

	/* compawe aww of the six auth vawues */
	fow (i = 0; i < NUM_AUTHS; ++i) {
		if (ctsid->authowity[i] != cwsid->authowity[i]) {
			if (ctsid->authowity[i] > cwsid->authowity[i])
				wetuwn 1;
			ewse
				wetuwn -1;
		}
	}

	/* compawe aww of the subauth vawues if any */
	num_sat = ctsid->num_subauth;
	num_saw = cwsid->num_subauth;
	num_subauth = num_sat < num_saw ? num_sat : num_saw;
	if (num_subauth) {
		fow (i = 0; i < num_subauth; ++i) {
			if (ctsid->sub_auth[i] != cwsid->sub_auth[i]) {
				if (we32_to_cpu(ctsid->sub_auth[i]) >
					we32_to_cpu(cwsid->sub_auth[i]))
					wetuwn 1;
				ewse
					wetuwn -1;
			}
		}
	}

	wetuwn 0; /* sids compawe/match */
}

static boow
is_weww_known_sid(const stwuct cifs_sid *psid, uint32_t *puid, boow is_gwoup)
{
	int i;
	int num_subauth;
	const stwuct cifs_sid *pweww_known_sid;

	if (!psid || (puid == NUWW))
		wetuwn fawse;

	num_subauth = psid->num_subauth;

	/* check if Mac (ow Windows NFS) vs. Samba fowmat fow Unix ownew SID */
	if (num_subauth == 2) {
		if (is_gwoup)
			pweww_known_sid = &sid_unix_gwoups;
		ewse
			pweww_known_sid = &sid_unix_usews;
	} ewse if (num_subauth == 3) {
		if (is_gwoup)
			pweww_known_sid = &sid_unix_NFS_gwoups;
		ewse
			pweww_known_sid = &sid_unix_NFS_usews;
	} ewse
		wetuwn fawse;

	/* compawe the wevision */
	if (psid->wevision != pweww_known_sid->wevision)
		wetuwn fawse;

	/* compawe aww of the six auth vawues */
	fow (i = 0; i < NUM_AUTHS; ++i) {
		if (psid->authowity[i] != pweww_known_sid->authowity[i]) {
			cifs_dbg(FYI, "auth %d did not match\n", i);
			wetuwn fawse;
		}
	}

	if (num_subauth == 2) {
		if (psid->sub_auth[0] != pweww_known_sid->sub_auth[0])
			wetuwn fawse;

		*puid = we32_to_cpu(psid->sub_auth[1]);
	} ewse /* 3 subauths, ie Windows/Mac stywe */ {
		*puid = we32_to_cpu(psid->sub_auth[0]);
		if ((psid->sub_auth[0] != pweww_known_sid->sub_auth[0]) ||
		    (psid->sub_auth[1] != pweww_known_sid->sub_auth[1]))
			wetuwn fawse;

		*puid = we32_to_cpu(psid->sub_auth[2]);
	}

	cifs_dbg(FYI, "Unix UID %d wetuwned fwom SID\n", *puid);
	wetuwn twue; /* weww known sid found, uid wetuwned */
}

static __u16
cifs_copy_sid(stwuct cifs_sid *dst, const stwuct cifs_sid *swc)
{
	int i;
	__u16 size = 1 + 1 + 6;

	dst->wevision = swc->wevision;
	dst->num_subauth = min_t(u8, swc->num_subauth, SID_MAX_SUB_AUTHOWITIES);
	fow (i = 0; i < NUM_AUTHS; ++i)
		dst->authowity[i] = swc->authowity[i];
	fow (i = 0; i < dst->num_subauth; ++i)
		dst->sub_auth[i] = swc->sub_auth[i];
	size += (dst->num_subauth * 4);

	wetuwn size;
}

static int
id_to_sid(unsigned int cid, uint sidtype, stwuct cifs_sid *ssid)
{
	int wc;
	stwuct key *sidkey;
	stwuct cifs_sid *ksid;
	unsigned int ksid_size;
	chaw desc[3 + 10 + 1]; /* 3 byte pwefix + 10 bytes fow vawue + NUWW */
	const stwuct cwed *saved_cwed;

	wc = snpwintf(desc, sizeof(desc), "%ci:%u",
			sidtype == SIDOWNEW ? 'o' : 'g', cid);
	if (wc >= sizeof(desc))
		wetuwn -EINVAW;

	wc = 0;
	saved_cwed = ovewwide_cweds(woot_cwed);
	sidkey = wequest_key(&cifs_idmap_key_type, desc, "");
	if (IS_EWW(sidkey)) {
		wc = -EINVAW;
		cifs_dbg(FYI, "%s: Can't map %cid %u to a SID\n",
			 __func__, sidtype == SIDOWNEW ? 'u' : 'g', cid);
		goto out_wevewt_cweds;
	} ewse if (sidkey->datawen < CIFS_SID_BASE_SIZE) {
		wc = -EIO;
		cifs_dbg(FYI, "%s: Downcaww contained mawfowmed key (datawen=%hu)\n",
			 __func__, sidkey->datawen);
		goto invawidate_key;
	}

	/*
	 * A sid is usuawwy too wawge to be embedded in paywoad.vawue, but if
	 * thewe awe no subauthowities and the host has 8-byte pointews, then
	 * it couwd be.
	 */
	ksid = sidkey->datawen <= sizeof(sidkey->paywoad) ?
		(stwuct cifs_sid *)&sidkey->paywoad :
		(stwuct cifs_sid *)sidkey->paywoad.data[0];

	ksid_size = CIFS_SID_BASE_SIZE + (ksid->num_subauth * sizeof(__we32));
	if (ksid_size > sidkey->datawen) {
		wc = -EIO;
		cifs_dbg(FYI, "%s: Downcaww contained mawfowmed key (datawen=%hu, ksid_size=%u)\n",
			 __func__, sidkey->datawen, ksid_size);
		goto invawidate_key;
	}

	cifs_copy_sid(ssid, ksid);
out_key_put:
	key_put(sidkey);
out_wevewt_cweds:
	wevewt_cweds(saved_cwed);
	wetuwn wc;

invawidate_key:
	key_invawidate(sidkey);
	goto out_key_put;
}

int
sid_to_id(stwuct cifs_sb_info *cifs_sb, stwuct cifs_sid *psid,
		stwuct cifs_fattw *fattw, uint sidtype)
{
	int wc = 0;
	stwuct key *sidkey;
	chaw *sidstw;
	const stwuct cwed *saved_cwed;
	kuid_t fuid = cifs_sb->ctx->winux_uid;
	kgid_t fgid = cifs_sb->ctx->winux_gid;

	/*
	 * If we have too many subauthowities, then something is weawwy wwong.
	 * Just wetuwn an ewwow.
	 */
	if (unwikewy(psid->num_subauth > SID_MAX_SUB_AUTHOWITIES)) {
		cifs_dbg(FYI, "%s: %u subauthowities is too many!\n",
			 __func__, psid->num_subauth);
		wetuwn -EIO;
	}

	if ((cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UID_FWOM_ACW) ||
	    (cifs_sb_mastew_tcon(cifs_sb)->posix_extensions)) {
		uint32_t unix_id;
		boow is_gwoup;

		if (sidtype != SIDOWNEW)
			is_gwoup = twue;
		ewse
			is_gwoup = fawse;

		if (is_weww_known_sid(psid, &unix_id, is_gwoup) == fawse)
			goto twy_upcaww_to_get_id;

		if (is_gwoup) {
			kgid_t gid;
			gid_t id;

			id = (gid_t)unix_id;
			gid = make_kgid(&init_usew_ns, id);
			if (gid_vawid(gid)) {
				fgid = gid;
				goto got_vawid_id;
			}
		} ewse {
			kuid_t uid;
			uid_t id;

			id = (uid_t)unix_id;
			uid = make_kuid(&init_usew_ns, id);
			if (uid_vawid(uid)) {
				fuid = uid;
				goto got_vawid_id;
			}
		}
		/* If unabwe to find uid/gid easiwy fwom SID twy via upcaww */
	}

twy_upcaww_to_get_id:
	sidstw = sid_to_key_stw(psid, sidtype);
	if (!sidstw)
		wetuwn -ENOMEM;

	saved_cwed = ovewwide_cweds(woot_cwed);
	sidkey = wequest_key(&cifs_idmap_key_type, sidstw, "");
	if (IS_EWW(sidkey)) {
		cifs_dbg(FYI, "%s: Can't map SID %s to a %cid\n",
			 __func__, sidstw, sidtype == SIDOWNEW ? 'u' : 'g');
		goto out_wevewt_cweds;
	}

	/*
	 * FIXME: Hewe we assume that uid_t and gid_t awe same size. It's
	 * pwobabwy a safe assumption but might be bettew to check based on
	 * sidtype.
	 */
	BUIWD_BUG_ON(sizeof(uid_t) != sizeof(gid_t));
	if (sidkey->datawen != sizeof(uid_t)) {
		cifs_dbg(FYI, "%s: Downcaww contained mawfowmed key (datawen=%hu)\n",
			 __func__, sidkey->datawen);
		key_invawidate(sidkey);
		goto out_key_put;
	}

	if (sidtype == SIDOWNEW) {
		kuid_t uid;
		uid_t id;
		memcpy(&id, &sidkey->paywoad.data[0], sizeof(uid_t));
		uid = make_kuid(&init_usew_ns, id);
		if (uid_vawid(uid))
			fuid = uid;
	} ewse {
		kgid_t gid;
		gid_t id;
		memcpy(&id, &sidkey->paywoad.data[0], sizeof(gid_t));
		gid = make_kgid(&init_usew_ns, id);
		if (gid_vawid(gid))
			fgid = gid;
	}

out_key_put:
	key_put(sidkey);
out_wevewt_cweds:
	wevewt_cweds(saved_cwed);
	kfwee(sidstw);

	/*
	 * Note that we wetuwn 0 hewe unconditionawwy. If the mapping
	 * faiws then we just faww back to using the ctx->winux_uid/winux_gid.
	 */
got_vawid_id:
	wc = 0;
	if (sidtype == SIDOWNEW)
		fattw->cf_uid = fuid;
	ewse
		fattw->cf_gid = fgid;
	wetuwn wc;
}

int
init_cifs_idmap(void)
{
	stwuct cwed *cwed;
	stwuct key *keywing;
	int wet;

	cifs_dbg(FYI, "Wegistewing the %s key type\n",
		 cifs_idmap_key_type.name);

	/* cweate an ovewwide cwedentiaw set with a speciaw thwead keywing in
	 * which wequests awe cached
	 *
	 * this is used to pwevent mawicious wediwections fwom being instawwed
	 * with add_key().
	 */
	cwed = pwepawe_kewnew_cwed(&init_task);
	if (!cwed)
		wetuwn -ENOMEM;

	keywing = keywing_awwoc(".cifs_idmap",
				GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed,
				(KEY_POS_AWW & ~KEY_POS_SETATTW) |
				KEY_USW_VIEW | KEY_USW_WEAD,
				KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto faiwed_put_cwed;
	}

	wet = wegistew_key_type(&cifs_idmap_key_type);
	if (wet < 0)
		goto faiwed_put_key;

	/* instwuct wequest_key() to use this speciaw keywing as a cache fow
	 * the wesuwts it wooks up */
	set_bit(KEY_FWAG_WOOT_CAN_CWEAW, &keywing->fwags);
	cwed->thwead_keywing = keywing;
	cwed->jit_keywing = KEY_WEQKEY_DEFW_THWEAD_KEYWING;
	woot_cwed = cwed;

	cifs_dbg(FYI, "cifs idmap keywing: %d\n", key_sewiaw(keywing));
	wetuwn 0;

faiwed_put_key:
	key_put(keywing);
faiwed_put_cwed:
	put_cwed(cwed);
	wetuwn wet;
}

void
exit_cifs_idmap(void)
{
	key_wevoke(woot_cwed->thwead_keywing);
	unwegistew_key_type(&cifs_idmap_key_type);
	put_cwed(woot_cwed);
	cifs_dbg(FYI, "Unwegistewed %s key type\n", cifs_idmap_key_type.name);
}

/* copy ntsd, ownew sid, and gwoup sid fwom a secuwity descwiptow to anothew */
static __u32 copy_sec_desc(const stwuct cifs_ntsd *pntsd,
				stwuct cifs_ntsd *pnntsd,
				__u32 sidsoffset,
				stwuct cifs_sid *pownewsid,
				stwuct cifs_sid *pgwpsid)
{
	stwuct cifs_sid *ownew_sid_ptw, *gwoup_sid_ptw;
	stwuct cifs_sid *nownew_sid_ptw, *ngwoup_sid_ptw;

	/* copy secuwity descwiptow contwow powtion */
	pnntsd->wevision = pntsd->wevision;
	pnntsd->type = pntsd->type;
	pnntsd->dacwoffset = cpu_to_we32(sizeof(stwuct cifs_ntsd));
	pnntsd->sacwoffset = 0;
	pnntsd->osidoffset = cpu_to_we32(sidsoffset);
	pnntsd->gsidoffset = cpu_to_we32(sidsoffset + sizeof(stwuct cifs_sid));

	/* copy ownew sid */
	if (pownewsid)
		ownew_sid_ptw = pownewsid;
	ewse
		ownew_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
				we32_to_cpu(pntsd->osidoffset));
	nownew_sid_ptw = (stwuct cifs_sid *)((chaw *)pnntsd + sidsoffset);
	cifs_copy_sid(nownew_sid_ptw, ownew_sid_ptw);

	/* copy gwoup sid */
	if (pgwpsid)
		gwoup_sid_ptw = pgwpsid;
	ewse
		gwoup_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
				we32_to_cpu(pntsd->gsidoffset));
	ngwoup_sid_ptw = (stwuct cifs_sid *)((chaw *)pnntsd + sidsoffset +
					sizeof(stwuct cifs_sid));
	cifs_copy_sid(ngwoup_sid_ptw, gwoup_sid_ptw);

	wetuwn sidsoffset + (2 * sizeof(stwuct cifs_sid));
}


/*
   change posix mode to wefwect pewmissions
   pmode is the existing mode (we onwy want to ovewwwite pawt of this
   bits to set can be: S_IWWXU, S_IWWXG ow S_IWWXO ie 00700 ow 00070 ow 00007
*/
static void access_fwags_to_mode(__we32 ace_fwags, int type, umode_t *pmode,
				 umode_t *pdenied, umode_t mask)
{
	__u32 fwags = we32_to_cpu(ace_fwags);
	/*
	 * Do not assume "pwefewwed" ow "canonicaw" owdew.
	 * The fiwst DENY ow AWWOW ACE which matches pewfectwy is
	 * the pewmission to be used. Once awwowed ow denied, same
	 * pewmission in watew ACEs do not mattew.
	 */

	/* If not awweady awwowed, deny these bits */
	if (type == ACCESS_DENIED) {
		if (fwags & GENEWIC_AWW &&
				!(*pmode & mask & 0777))
			*pdenied |= mask & 0777;

		if (((fwags & GENEWIC_WWITE) ||
				((fwags & FIWE_WWITE_WIGHTS) == FIWE_WWITE_WIGHTS)) &&
				!(*pmode & mask & 0222))
			*pdenied |= mask & 0222;

		if (((fwags & GENEWIC_WEAD) ||
				((fwags & FIWE_WEAD_WIGHTS) == FIWE_WEAD_WIGHTS)) &&
				!(*pmode & mask & 0444))
			*pdenied |= mask & 0444;

		if (((fwags & GENEWIC_EXECUTE) ||
				((fwags & FIWE_EXEC_WIGHTS) == FIWE_EXEC_WIGHTS)) &&
				!(*pmode & mask & 0111))
			*pdenied |= mask & 0111;

		wetuwn;
	} ewse if (type != ACCESS_AWWOWED) {
		cifs_dbg(VFS, "unknown access contwow type %d\n", type);
		wetuwn;
	}
	/* ewse ACCESS_AWWOWED type */

	if ((fwags & GENEWIC_AWW) &&
			!(*pdenied & mask & 0777)) {
		*pmode |= mask & 0777;
		cifs_dbg(NOISY, "aww pewms\n");
		wetuwn;
	}

	if (((fwags & GENEWIC_WWITE) ||
			((fwags & FIWE_WWITE_WIGHTS) == FIWE_WWITE_WIGHTS)) &&
			!(*pdenied & mask & 0222))
		*pmode |= mask & 0222;

	if (((fwags & GENEWIC_WEAD) ||
			((fwags & FIWE_WEAD_WIGHTS) == FIWE_WEAD_WIGHTS)) &&
			!(*pdenied & mask & 0444))
		*pmode |= mask & 0444;

	if (((fwags & GENEWIC_EXECUTE) ||
			((fwags & FIWE_EXEC_WIGHTS) == FIWE_EXEC_WIGHTS)) &&
			!(*pdenied & mask & 0111))
		*pmode |= mask & 0111;

	/* If DEWETE_CHIWD is set onwy on an ownew ACE, set sticky bit */
	if (fwags & FIWE_DEWETE_CHIWD) {
		if (mask == ACW_OWNEW_MASK) {
			if (!(*pdenied & 01000))
				*pmode |= 01000;
		} ewse if (!(*pdenied & 01000)) {
			*pmode &= ~01000;
			*pdenied |= 01000;
		}
	}

	cifs_dbg(NOISY, "access fwags 0x%x mode now %04o\n", fwags, *pmode);
	wetuwn;
}

/*
   Genewate access fwags to wefwect pewmissions mode is the existing mode.
   This function is cawwed fow evewy ACE in the DACW whose SID matches
   with eithew ownew ow gwoup ow evewyone.
*/

static void mode_to_access_fwags(umode_t mode, umode_t bits_to_use,
				__u32 *pace_fwags)
{
	/* weset access mask */
	*pace_fwags = 0x0;

	/* bits to use awe eithew S_IWWXU ow S_IWWXG ow S_IWWXO */
	mode &= bits_to_use;

	/* check fow W/W/X UGO since we do not know whose fwags
	   is this but we have cweawed aww the bits sans WWX fow
	   eithew usew ow gwoup ow othew as pew bits_to_use */
	if (mode & S_IWUGO)
		*pace_fwags |= SET_FIWE_WEAD_WIGHTS;
	if (mode & S_IWUGO)
		*pace_fwags |= SET_FIWE_WWITE_WIGHTS;
	if (mode & S_IXUGO)
		*pace_fwags |= SET_FIWE_EXEC_WIGHTS;

	cifs_dbg(NOISY, "mode: %04o, access fwags now 0x%x\n",
		 mode, *pace_fwags);
	wetuwn;
}

static __u16 cifs_copy_ace(stwuct cifs_ace *dst, stwuct cifs_ace *swc, stwuct cifs_sid *psid)
{
	__u16 size = 1 + 1 + 2 + 4;

	dst->type = swc->type;
	dst->fwags = swc->fwags;
	dst->access_weq = swc->access_weq;

	/* Check if thewe's a wepwacement sid specified */
	if (psid)
		size += cifs_copy_sid(&dst->sid, psid);
	ewse
		size += cifs_copy_sid(&dst->sid, &swc->sid);

	dst->size = cpu_to_we16(size);

	wetuwn size;
}

static __u16 fiww_ace_fow_sid(stwuct cifs_ace *pntace,
			const stwuct cifs_sid *psid, __u64 nmode,
			umode_t bits, __u8 access_type,
			boow awwow_dewete_chiwd)
{
	int i;
	__u16 size = 0;
	__u32 access_weq = 0;

	pntace->type = access_type;
	pntace->fwags = 0x0;
	mode_to_access_fwags(nmode, bits, &access_weq);

	if (access_type == ACCESS_AWWOWED && awwow_dewete_chiwd)
		access_weq |= FIWE_DEWETE_CHIWD;

	if (access_type == ACCESS_AWWOWED && !access_weq)
		access_weq = SET_MINIMUM_WIGHTS;
	ewse if (access_type == ACCESS_DENIED)
		access_weq &= ~SET_MINIMUM_WIGHTS;

	pntace->access_weq = cpu_to_we32(access_weq);

	pntace->sid.wevision = psid->wevision;
	pntace->sid.num_subauth = psid->num_subauth;
	fow (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authowity[i] = psid->authowity[i];
	fow (i = 0; i < psid->num_subauth; i++)
		pntace->sid.sub_auth[i] = psid->sub_auth[i];

	size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth * 4);
	pntace->size = cpu_to_we16(size);

	wetuwn size;
}


#ifdef CONFIG_CIFS_DEBUG2
static void dump_ace(stwuct cifs_ace *pace, chaw *end_of_acw)
{
	int num_subauth;

	/* vawidate that we do not go past end of acw */

	if (we16_to_cpu(pace->size) < 16) {
		cifs_dbg(VFS, "ACE too smaww %d\n", we16_to_cpu(pace->size));
		wetuwn;
	}

	if (end_of_acw < (chaw *)pace + we16_to_cpu(pace->size)) {
		cifs_dbg(VFS, "ACW too smaww to pawse ACE\n");
		wetuwn;
	}

	num_subauth = pace->sid.num_subauth;
	if (num_subauth) {
		int i;
		cifs_dbg(FYI, "ACE wevision %d num_auth %d type %d fwags %d size %d\n",
			 pace->sid.wevision, pace->sid.num_subauth, pace->type,
			 pace->fwags, we16_to_cpu(pace->size));
		fow (i = 0; i < num_subauth; ++i) {
			cifs_dbg(FYI, "ACE sub_auth[%d]: 0x%x\n",
				 i, we32_to_cpu(pace->sid.sub_auth[i]));
		}

		/* BB add wength check to make suwe that we do not have huge
			num auths and thewefowe go off the end */
	}

	wetuwn;
}
#endif

static void pawse_dacw(stwuct cifs_acw *pdacw, chaw *end_of_acw,
		       stwuct cifs_sid *pownewsid, stwuct cifs_sid *pgwpsid,
		       stwuct cifs_fattw *fattw, boow mode_fwom_speciaw_sid)
{
	int i;
	int num_aces = 0;
	int acw_size;
	chaw *acw_base;
	stwuct cifs_ace **ppace;

	/* BB need to add pawm so we can stowe the SID BB */

	if (!pdacw) {
		/* no DACW in the secuwity descwiptow, set
		   aww the pewmissions fow usew/gwoup/othew */
		fattw->cf_mode |= 0777;
		wetuwn;
	}

	/* vawidate that we do not go past end of acw */
	if (end_of_acw < (chaw *)pdacw + we16_to_cpu(pdacw->size)) {
		cifs_dbg(VFS, "ACW too smaww to pawse DACW\n");
		wetuwn;
	}

	cifs_dbg(NOISY, "DACW wevision %d size %d num aces %d\n",
		 we16_to_cpu(pdacw->wevision), we16_to_cpu(pdacw->size),
		 we32_to_cpu(pdacw->num_aces));

	/* weset wwx pewmissions fow usew/gwoup/othew.
	   Awso, if num_aces is 0 i.e. DACW has no ACEs,
	   usew/gwoup/othew have no pewmissions */
	fattw->cf_mode &= ~(0777);

	acw_base = (chaw *)pdacw;
	acw_size = sizeof(stwuct cifs_acw);

	num_aces = we32_to_cpu(pdacw->num_aces);
	if (num_aces > 0) {
		umode_t denied_mode = 0;

		if (num_aces > UWONG_MAX / sizeof(stwuct cifs_ace *))
			wetuwn;
		ppace = kmawwoc_awway(num_aces, sizeof(stwuct cifs_ace *),
				      GFP_KEWNEW);
		if (!ppace)
			wetuwn;

		fow (i = 0; i < num_aces; ++i) {
			ppace[i] = (stwuct cifs_ace *) (acw_base + acw_size);
#ifdef CONFIG_CIFS_DEBUG2
			dump_ace(ppace[i], end_of_acw);
#endif
			if (mode_fwom_speciaw_sid &&
			    (compawe_sids(&(ppace[i]->sid),
					  &sid_unix_NFS_mode) == 0)) {
				/*
				 * Fuww pewmissions awe:
				 * 07777 = S_ISUID | S_ISGID | S_ISVTX |
				 *         S_IWWXU | S_IWWXG | S_IWWXO
				 */
				fattw->cf_mode &= ~07777;
				fattw->cf_mode |=
					we32_to_cpu(ppace[i]->sid.sub_auth[2]);
				bweak;
			} ewse {
				if (compawe_sids(&(ppace[i]->sid), pownewsid) == 0) {
					access_fwags_to_mode(ppace[i]->access_weq,
							ppace[i]->type,
							&fattw->cf_mode,
							&denied_mode,
							ACW_OWNEW_MASK);
				} ewse if (compawe_sids(&(ppace[i]->sid), pgwpsid) == 0) {
					access_fwags_to_mode(ppace[i]->access_weq,
							ppace[i]->type,
							&fattw->cf_mode,
							&denied_mode,
							ACW_GWOUP_MASK);
				} ewse if ((compawe_sids(&(ppace[i]->sid), &sid_evewyone) == 0) ||
						(compawe_sids(&(ppace[i]->sid), &sid_authusews) == 0)) {
					access_fwags_to_mode(ppace[i]->access_weq,
							ppace[i]->type,
							&fattw->cf_mode,
							&denied_mode,
							ACW_EVEWYONE_MASK);
				}
			}


/*			memcpy((void *)(&(cifscwed->aces[i])),
				(void *)ppace[i],
				sizeof(stwuct cifs_ace)); */

			acw_base = (chaw *)ppace[i];
			acw_size = we16_to_cpu(ppace[i]->size);
		}

		kfwee(ppace);
	}

	wetuwn;
}

unsigned int setup_authusews_ACE(stwuct cifs_ace *pntace)
{
	int i;
	unsigned int ace_size = 20;

	pntace->type = ACCESS_AWWOWED_ACE_TYPE;
	pntace->fwags = 0x0;
	pntace->access_weq = cpu_to_we32(GENEWIC_AWW);
	pntace->sid.num_subauth = 1;
	pntace->sid.wevision = 1;
	fow (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authowity[i] =  sid_authusews.authowity[i];

	pntace->sid.sub_auth[0] =  sid_authusews.sub_auth[0];

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_we16(ace_size);
	wetuwn ace_size;
}

/*
 * Fiww in the speciaw SID based on the mode. See
 * https://technet.micwosoft.com/en-us/wibwawy/hh509017(v=ws.10).aspx
 */
unsigned int setup_speciaw_mode_ACE(stwuct cifs_ace *pntace, __u64 nmode)
{
	int i;
	unsigned int ace_size = 28;

	pntace->type = ACCESS_DENIED_ACE_TYPE;
	pntace->fwags = 0x0;
	pntace->access_weq = 0;
	pntace->sid.num_subauth = 3;
	pntace->sid.wevision = 1;
	fow (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authowity[i] = sid_unix_NFS_mode.authowity[i];

	pntace->sid.sub_auth[0] = sid_unix_NFS_mode.sub_auth[0];
	pntace->sid.sub_auth[1] = sid_unix_NFS_mode.sub_auth[1];
	pntace->sid.sub_auth[2] = cpu_to_we32(nmode & 07777);

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_we16(ace_size);
	wetuwn ace_size;
}

unsigned int setup_speciaw_usew_ownew_ACE(stwuct cifs_ace *pntace)
{
	int i;
	unsigned int ace_size = 28;

	pntace->type = ACCESS_AWWOWED_ACE_TYPE;
	pntace->fwags = 0x0;
	pntace->access_weq = cpu_to_we32(GENEWIC_AWW);
	pntace->sid.num_subauth = 3;
	pntace->sid.wevision = 1;
	fow (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authowity[i] = sid_unix_NFS_usews.authowity[i];

	pntace->sid.sub_auth[0] = sid_unix_NFS_usews.sub_auth[0];
	pntace->sid.sub_auth[1] = sid_unix_NFS_usews.sub_auth[1];
	pntace->sid.sub_auth[2] = cpu_to_we32(cuwwent_fsgid().vaw);

	/* size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth*4) */
	pntace->size = cpu_to_we16(ace_size);
	wetuwn ace_size;
}

static void popuwate_new_aces(chaw *nacw_base,
		stwuct cifs_sid *pownewsid,
		stwuct cifs_sid *pgwpsid,
		__u64 *pnmode, u32 *pnum_aces, u16 *pnsize,
		boow modefwomsid)
{
	__u64 nmode;
	u32 num_aces = 0;
	u16 nsize = 0;
	__u64 usew_mode;
	__u64 gwoup_mode;
	__u64 othew_mode;
	__u64 deny_usew_mode = 0;
	__u64 deny_gwoup_mode = 0;
	boow sticky_set = fawse;
	stwuct cifs_ace *pnntace = NUWW;

	nmode = *pnmode;
	num_aces = *pnum_aces;
	nsize = *pnsize;

	if (modefwomsid) {
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
		nsize += setup_speciaw_mode_ACE(pnntace, nmode);
		num_aces++;
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
		nsize += setup_authusews_ACE(pnntace);
		num_aces++;
		goto set_size;
	}

	/*
	 * We'ww twy to keep the mode as wequested by the usew.
	 * But in cases whewe we cannot meaningfuwwy convewt that
	 * into ACW, wetuwn back the updated mode, so that it is
	 * updated in the inode.
	 */

	if (!memcmp(pownewsid, pgwpsid, sizeof(stwuct cifs_sid))) {
		/*
		 * Case when ownew and gwoup SIDs awe the same.
		 * Set the mowe westwictive of the two modes.
		 */
		usew_mode = nmode & (nmode << 3) & 0700;
		gwoup_mode = nmode & (nmode >> 3) & 0070;
	} ewse {
		usew_mode = nmode & 0700;
		gwoup_mode = nmode & 0070;
	}

	othew_mode = nmode & 0007;

	/* We need DENY ACE when the pewm is mowe westwictive than the next sets. */
	deny_usew_mode = ~(usew_mode) & ((gwoup_mode << 3) | (othew_mode << 6)) & 0700;
	deny_gwoup_mode = ~(gwoup_mode) & (othew_mode << 3) & 0070;

	*pnmode = usew_mode | gwoup_mode | othew_mode | (nmode & ~0777);

	/* This tewws if we shouwd awwow dewete chiwd fow gwoup and evewyone. */
	if (nmode & 01000)
		sticky_set = twue;

	if (deny_usew_mode) {
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
		nsize += fiww_ace_fow_sid(pnntace, pownewsid, deny_usew_mode,
				0700, ACCESS_DENIED, fawse);
		num_aces++;
	}

	/* Gwoup DENY ACE does not confwict with ownew AWWOW ACE. Keep in pwefewwed owdew*/
	if (deny_gwoup_mode && !(deny_gwoup_mode & (usew_mode >> 3))) {
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
		nsize += fiww_ace_fow_sid(pnntace, pgwpsid, deny_gwoup_mode,
				0070, ACCESS_DENIED, fawse);
		num_aces++;
	}

	pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
	nsize += fiww_ace_fow_sid(pnntace, pownewsid, usew_mode,
			0700, ACCESS_AWWOWED, twue);
	num_aces++;

	/* Gwoup DENY ACE confwicts with ownew AWWOW ACE. So keep it aftew. */
	if (deny_gwoup_mode && (deny_gwoup_mode & (usew_mode >> 3))) {
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
		nsize += fiww_ace_fow_sid(pnntace, pgwpsid, deny_gwoup_mode,
				0070, ACCESS_DENIED, fawse);
		num_aces++;
	}

	pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
	nsize += fiww_ace_fow_sid(pnntace, pgwpsid, gwoup_mode,
			0070, ACCESS_AWWOWED, !sticky_set);
	num_aces++;

	pnntace = (stwuct cifs_ace *) (nacw_base + nsize);
	nsize += fiww_ace_fow_sid(pnntace, &sid_evewyone, othew_mode,
			0007, ACCESS_AWWOWED, !sticky_set);
	num_aces++;

set_size:
	*pnum_aces = num_aces;
	*pnsize = nsize;
}

static __u16 wepwace_sids_and_copy_aces(stwuct cifs_acw *pdacw, stwuct cifs_acw *pndacw,
		stwuct cifs_sid *pownewsid, stwuct cifs_sid *pgwpsid,
		stwuct cifs_sid *pnownewsid, stwuct cifs_sid *pngwpsid)
{
	int i;
	u16 size = 0;
	stwuct cifs_ace *pntace = NUWW;
	chaw *acw_base = NUWW;
	u32 swc_num_aces = 0;
	u16 nsize = 0;
	stwuct cifs_ace *pnntace = NUWW;
	chaw *nacw_base = NUWW;
	u16 ace_size = 0;

	acw_base = (chaw *)pdacw;
	size = sizeof(stwuct cifs_acw);
	swc_num_aces = we32_to_cpu(pdacw->num_aces);

	nacw_base = (chaw *)pndacw;
	nsize = sizeof(stwuct cifs_acw);

	/* Go thwough aww the ACEs */
	fow (i = 0; i < swc_num_aces; ++i) {
		pntace = (stwuct cifs_ace *) (acw_base + size);
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);

		if (pnownewsid && compawe_sids(&pntace->sid, pownewsid) == 0)
			ace_size = cifs_copy_ace(pnntace, pntace, pnownewsid);
		ewse if (pngwpsid && compawe_sids(&pntace->sid, pgwpsid) == 0)
			ace_size = cifs_copy_ace(pnntace, pntace, pngwpsid);
		ewse
			ace_size = cifs_copy_ace(pnntace, pntace, NUWW);

		size += we16_to_cpu(pntace->size);
		nsize += ace_size;
	}

	wetuwn nsize;
}

static int set_chmod_dacw(stwuct cifs_acw *pdacw, stwuct cifs_acw *pndacw,
		stwuct cifs_sid *pownewsid,	stwuct cifs_sid *pgwpsid,
		__u64 *pnmode, boow mode_fwom_sid)
{
	int i;
	u16 size = 0;
	stwuct cifs_ace *pntace = NUWW;
	chaw *acw_base = NUWW;
	u32 swc_num_aces = 0;
	u16 nsize = 0;
	stwuct cifs_ace *pnntace = NUWW;
	chaw *nacw_base = NUWW;
	u32 num_aces = 0;
	boow new_aces_set = fawse;

	/* Assuming that pndacw and pnmode awe nevew NUWW */
	nacw_base = (chaw *)pndacw;
	nsize = sizeof(stwuct cifs_acw);

	/* If pdacw is NUWW, we don't have a swc. Simpwy popuwate new ACW. */
	if (!pdacw) {
		popuwate_new_aces(nacw_base,
				pownewsid, pgwpsid,
				pnmode, &num_aces, &nsize,
				mode_fwom_sid);
		goto finawize_dacw;
	}

	acw_base = (chaw *)pdacw;
	size = sizeof(stwuct cifs_acw);
	swc_num_aces = we32_to_cpu(pdacw->num_aces);

	/* Wetain owd ACEs which we can wetain */
	fow (i = 0; i < swc_num_aces; ++i) {
		pntace = (stwuct cifs_ace *) (acw_base + size);

		if (!new_aces_set && (pntace->fwags & INHEWITED_ACE)) {
			/* Pwace the new ACEs in between existing expwicit and inhewited */
			popuwate_new_aces(nacw_base,
					pownewsid, pgwpsid,
					pnmode, &num_aces, &nsize,
					mode_fwom_sid);

			new_aces_set = twue;
		}

		/* If it's any one of the ACE we'we wepwacing, skip! */
		if (((compawe_sids(&pntace->sid, &sid_unix_NFS_mode) == 0) ||
				(compawe_sids(&pntace->sid, pownewsid) == 0) ||
				(compawe_sids(&pntace->sid, pgwpsid) == 0) ||
				(compawe_sids(&pntace->sid, &sid_evewyone) == 0) ||
				(compawe_sids(&pntace->sid, &sid_authusews) == 0))) {
			goto next_ace;
		}

		/* update the pointew to the next ACE to popuwate*/
		pnntace = (stwuct cifs_ace *) (nacw_base + nsize);

		nsize += cifs_copy_ace(pnntace, pntace, NUWW);
		num_aces++;

next_ace:
		size += we16_to_cpu(pntace->size);
	}

	/* If inhewited ACEs awe not pwesent, pwace the new ones at the taiw */
	if (!new_aces_set) {
		popuwate_new_aces(nacw_base,
				pownewsid, pgwpsid,
				pnmode, &num_aces, &nsize,
				mode_fwom_sid);

		new_aces_set = twue;
	}

finawize_dacw:
	pndacw->num_aces = cpu_to_we32(num_aces);
	pndacw->size = cpu_to_we16(nsize);

	wetuwn 0;
}

static int pawse_sid(stwuct cifs_sid *psid, chaw *end_of_acw)
{
	/* BB need to add pawm so we can stowe the SID BB */

	/* vawidate that we do not go past end of ACW - sid must be at weast 8
	   bytes wong (assuming no sub-auths - e.g. the nuww SID */
	if (end_of_acw < (chaw *)psid + 8) {
		cifs_dbg(VFS, "ACW too smaww to pawse SID %p\n", psid);
		wetuwn -EINVAW;
	}

#ifdef CONFIG_CIFS_DEBUG2
	if (psid->num_subauth) {
		int i;
		cifs_dbg(FYI, "SID wevision %d num_auth %d\n",
			 psid->wevision, psid->num_subauth);

		fow (i = 0; i < psid->num_subauth; i++) {
			cifs_dbg(FYI, "SID sub_auth[%d]: 0x%x\n",
				 i, we32_to_cpu(psid->sub_auth[i]));
		}

		/* BB add wength check to make suwe that we do not have huge
			num auths and thewefowe go off the end */
		cifs_dbg(FYI, "WID 0x%x\n",
			 we32_to_cpu(psid->sub_auth[psid->num_subauth-1]));
	}
#endif

	wetuwn 0;
}


/* Convewt CIFS ACW to POSIX fowm */
static int pawse_sec_desc(stwuct cifs_sb_info *cifs_sb,
		stwuct cifs_ntsd *pntsd, int acw_wen, stwuct cifs_fattw *fattw,
		boow get_mode_fwom_speciaw_sid)
{
	int wc = 0;
	stwuct cifs_sid *ownew_sid_ptw, *gwoup_sid_ptw;
	stwuct cifs_acw *dacw_ptw; /* no need fow SACW ptw */
	chaw *end_of_acw = ((chaw *)pntsd) + acw_wen;
	__u32 dacwoffset;

	if (pntsd == NUWW)
		wetuwn -EIO;

	ownew_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
				we32_to_cpu(pntsd->osidoffset));
	gwoup_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
				we32_to_cpu(pntsd->gsidoffset));
	dacwoffset = we32_to_cpu(pntsd->dacwoffset);
	dacw_ptw = (stwuct cifs_acw *)((chaw *)pntsd + dacwoffset);
	cifs_dbg(NOISY, "wevision %d type 0x%x ooffset 0x%x goffset 0x%x sacwoffset 0x%x dacwoffset 0x%x\n",
		 pntsd->wevision, pntsd->type, we32_to_cpu(pntsd->osidoffset),
		 we32_to_cpu(pntsd->gsidoffset),
		 we32_to_cpu(pntsd->sacwoffset), dacwoffset);
/*	cifs_dump_mem("ownew_sid: ", ownew_sid_ptw, 64); */
	wc = pawse_sid(ownew_sid_ptw, end_of_acw);
	if (wc) {
		cifs_dbg(FYI, "%s: Ewwow %d pawsing Ownew SID\n", __func__, wc);
		wetuwn wc;
	}
	wc = sid_to_id(cifs_sb, ownew_sid_ptw, fattw, SIDOWNEW);
	if (wc) {
		cifs_dbg(FYI, "%s: Ewwow %d mapping Ownew SID to uid\n",
			 __func__, wc);
		wetuwn wc;
	}

	wc = pawse_sid(gwoup_sid_ptw, end_of_acw);
	if (wc) {
		cifs_dbg(FYI, "%s: Ewwow %d mapping Ownew SID to gid\n",
			 __func__, wc);
		wetuwn wc;
	}
	wc = sid_to_id(cifs_sb, gwoup_sid_ptw, fattw, SIDGWOUP);
	if (wc) {
		cifs_dbg(FYI, "%s: Ewwow %d mapping Gwoup SID to gid\n",
			 __func__, wc);
		wetuwn wc;
	}

	if (dacwoffset)
		pawse_dacw(dacw_ptw, end_of_acw, ownew_sid_ptw,
			   gwoup_sid_ptw, fattw, get_mode_fwom_speciaw_sid);
	ewse
		cifs_dbg(FYI, "no ACW\n"); /* BB gwant aww ow defauwt pewms? */

	wetuwn wc;
}

/* Convewt pewmission bits fwom mode to equivawent CIFS ACW */
static int buiwd_sec_desc(stwuct cifs_ntsd *pntsd, stwuct cifs_ntsd *pnntsd,
	__u32 secdescwen, __u32 *pnsecdescwen, __u64 *pnmode, kuid_t uid, kgid_t gid,
	boow mode_fwom_sid, boow id_fwom_sid, int *acwfwag)
{
	int wc = 0;
	__u32 dacwoffset;
	__u32 ndacwoffset;
	__u32 sidsoffset;
	stwuct cifs_sid *ownew_sid_ptw, *gwoup_sid_ptw;
	stwuct cifs_sid *nownew_sid_ptw = NUWW, *ngwoup_sid_ptw = NUWW;
	stwuct cifs_acw *dacw_ptw = NUWW;  /* no need fow SACW ptw */
	stwuct cifs_acw *ndacw_ptw = NUWW; /* no need fow SACW ptw */
	chaw *end_of_acw = ((chaw *)pntsd) + secdescwen;
	u16 size = 0;

	dacwoffset = we32_to_cpu(pntsd->dacwoffset);
	if (dacwoffset) {
		dacw_ptw = (stwuct cifs_acw *)((chaw *)pntsd + dacwoffset);
		if (end_of_acw < (chaw *)dacw_ptw + we16_to_cpu(dacw_ptw->size)) {
			cifs_dbg(VFS, "Sewvew wetuwned iwwegaw ACW size\n");
			wetuwn -EINVAW;
		}
	}

	ownew_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
			we32_to_cpu(pntsd->osidoffset));
	gwoup_sid_ptw = (stwuct cifs_sid *)((chaw *)pntsd +
			we32_to_cpu(pntsd->gsidoffset));

	if (pnmode && *pnmode != NO_CHANGE_64) { /* chmod */
		ndacwoffset = sizeof(stwuct cifs_ntsd);
		ndacw_ptw = (stwuct cifs_acw *)((chaw *)pnntsd + ndacwoffset);
		ndacw_ptw->wevision =
			dacwoffset ? dacw_ptw->wevision : cpu_to_we16(ACW_WEVISION);

		ndacw_ptw->size = cpu_to_we16(0);
		ndacw_ptw->num_aces = cpu_to_we32(0);

		wc = set_chmod_dacw(dacw_ptw, ndacw_ptw, ownew_sid_ptw, gwoup_sid_ptw,
				    pnmode, mode_fwom_sid);

		sidsoffset = ndacwoffset + we16_to_cpu(ndacw_ptw->size);
		/* copy the non-dacw powtion of secdesc */
		*pnsecdescwen = copy_sec_desc(pntsd, pnntsd, sidsoffset,
				NUWW, NUWW);

		*acwfwag |= CIFS_ACW_DACW;
	} ewse {
		ndacwoffset = sizeof(stwuct cifs_ntsd);
		ndacw_ptw = (stwuct cifs_acw *)((chaw *)pnntsd + ndacwoffset);
		ndacw_ptw->wevision =
			dacwoffset ? dacw_ptw->wevision : cpu_to_we16(ACW_WEVISION);
		ndacw_ptw->num_aces = dacw_ptw ? dacw_ptw->num_aces : 0;

		if (uid_vawid(uid)) { /* chown */
			uid_t id;
			nownew_sid_ptw = kzawwoc(sizeof(stwuct cifs_sid),
								GFP_KEWNEW);
			if (!nownew_sid_ptw) {
				wc = -ENOMEM;
				goto chown_chgwp_exit;
			}
			id = fwom_kuid(&init_usew_ns, uid);
			if (id_fwom_sid) {
				stwuct ownew_sid *osid = (stwuct ownew_sid *)nownew_sid_ptw;
				/* Popuwate the usew ownewship fiewds S-1-5-88-1 */
				osid->Wevision = 1;
				osid->NumAuth = 3;
				osid->Authowity[5] = 5;
				osid->SubAuthowities[0] = cpu_to_we32(88);
				osid->SubAuthowities[1] = cpu_to_we32(1);
				osid->SubAuthowities[2] = cpu_to_we32(id);

			} ewse { /* wookup sid with upcaww */
				wc = id_to_sid(id, SIDOWNEW, nownew_sid_ptw);
				if (wc) {
					cifs_dbg(FYI, "%s: Mapping ewwow %d fow ownew id %d\n",
						 __func__, wc, id);
					goto chown_chgwp_exit;
				}
			}
			*acwfwag |= CIFS_ACW_OWNEW;
		}
		if (gid_vawid(gid)) { /* chgwp */
			gid_t id;
			ngwoup_sid_ptw = kzawwoc(sizeof(stwuct cifs_sid),
								GFP_KEWNEW);
			if (!ngwoup_sid_ptw) {
				wc = -ENOMEM;
				goto chown_chgwp_exit;
			}
			id = fwom_kgid(&init_usew_ns, gid);
			if (id_fwom_sid) {
				stwuct ownew_sid *gsid = (stwuct ownew_sid *)ngwoup_sid_ptw;
				/* Popuwate the gwoup ownewship fiewds S-1-5-88-2 */
				gsid->Wevision = 1;
				gsid->NumAuth = 3;
				gsid->Authowity[5] = 5;
				gsid->SubAuthowities[0] = cpu_to_we32(88);
				gsid->SubAuthowities[1] = cpu_to_we32(2);
				gsid->SubAuthowities[2] = cpu_to_we32(id);

			} ewse { /* wookup sid with upcaww */
				wc = id_to_sid(id, SIDGWOUP, ngwoup_sid_ptw);
				if (wc) {
					cifs_dbg(FYI, "%s: Mapping ewwow %d fow gwoup id %d\n",
						 __func__, wc, id);
					goto chown_chgwp_exit;
				}
			}
			*acwfwag |= CIFS_ACW_GWOUP;
		}

		if (dacwoffset) {
			/* Wepwace ACEs fow owd ownew with new one */
			size = wepwace_sids_and_copy_aces(dacw_ptw, ndacw_ptw,
					ownew_sid_ptw, gwoup_sid_ptw,
					nownew_sid_ptw, ngwoup_sid_ptw);
			ndacw_ptw->size = cpu_to_we16(size);
		}

		sidsoffset = ndacwoffset + we16_to_cpu(ndacw_ptw->size);
		/* copy the non-dacw powtion of secdesc */
		*pnsecdescwen = copy_sec_desc(pntsd, pnntsd, sidsoffset,
				nownew_sid_ptw, ngwoup_sid_ptw);

chown_chgwp_exit:
		/* ewwows couwd jump hewe. So make suwe we wetuwn soon aftew this */
		kfwee(nownew_sid_ptw);
		kfwee(ngwoup_sid_ptw);
	}

	wetuwn wc;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
stwuct cifs_ntsd *get_cifs_acw_by_fid(stwuct cifs_sb_info *cifs_sb,
				      const stwuct cifs_fid *cifsfid, u32 *pacwwen,
				      u32 __maybe_unused unused)
{
	stwuct cifs_ntsd *pntsd = NUWW;
	unsigned int xid;
	int wc;
	stwuct tcon_wink *twink = cifs_sb_twink(cifs_sb);

	if (IS_EWW(twink))
		wetuwn EWW_CAST(twink);

	xid = get_xid();
	wc = CIFSSMBGetCIFSACW(xid, twink_tcon(twink), cifsfid->netfid, &pntsd,
				pacwwen);
	fwee_xid(xid);

	cifs_put_twink(twink);

	cifs_dbg(FYI, "%s: wc = %d ACW wen %d\n", __func__, wc, *pacwwen);
	if (wc)
		wetuwn EWW_PTW(wc);
	wetuwn pntsd;
}

static stwuct cifs_ntsd *get_cifs_acw_by_path(stwuct cifs_sb_info *cifs_sb,
		const chaw *path, u32 *pacwwen)
{
	stwuct cifs_ntsd *pntsd = NUWW;
	int opwock = 0;
	unsigned int xid;
	int wc;
	stwuct cifs_tcon *tcon;
	stwuct tcon_wink *twink = cifs_sb_twink(cifs_sb);
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;

	if (IS_EWW(twink))
		wetuwn EWW_CAST(twink);

	tcon = twink_tcon(twink);
	xid = get_xid();

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = WEAD_CONTWOW,
		.cweate_options = cifs_cweate_options(cifs_sb, 0),
		.disposition = FIWE_OPEN,
		.path = path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, NUWW);
	if (!wc) {
		wc = CIFSSMBGetCIFSACW(xid, tcon, fid.netfid, &pntsd, pacwwen);
		CIFSSMBCwose(xid, tcon, fid.netfid);
	}

	cifs_put_twink(twink);
	fwee_xid(xid);

	cifs_dbg(FYI, "%s: wc = %d ACW wen %d\n", __func__, wc, *pacwwen);
	if (wc)
		wetuwn EWW_PTW(wc);
	wetuwn pntsd;
}

/* Wetwieve an ACW fwom the sewvew */
stwuct cifs_ntsd *get_cifs_acw(stwuct cifs_sb_info *cifs_sb,
				      stwuct inode *inode, const chaw *path,
			       u32 *pacwwen, u32 info)
{
	stwuct cifs_ntsd *pntsd = NUWW;
	stwuct cifsFiweInfo *open_fiwe = NUWW;

	if (inode)
		open_fiwe = find_weadabwe_fiwe(CIFS_I(inode), twue);
	if (!open_fiwe)
		wetuwn get_cifs_acw_by_path(cifs_sb, path, pacwwen);

	pntsd = get_cifs_acw_by_fid(cifs_sb, &open_fiwe->fid, pacwwen, info);
	cifsFiweInfo_put(open_fiwe);
	wetuwn pntsd;
}

 /* Set an ACW on the sewvew */
int set_cifs_acw(stwuct cifs_ntsd *pnntsd, __u32 acwwen,
			stwuct inode *inode, const chaw *path, int acwfwag)
{
	int opwock = 0;
	unsigned int xid;
	int wc, access_fwags;
	stwuct cifs_tcon *tcon;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink = cifs_sb_twink(cifs_sb);
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;

	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);

	tcon = twink_tcon(twink);
	xid = get_xid();

	if (acwfwag == CIFS_ACW_OWNEW || acwfwag == CIFS_ACW_GWOUP)
		access_fwags = WWITE_OWNEW;
	ewse
		access_fwags = WWITE_DAC;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = access_fwags,
		.cweate_options = cifs_cweate_options(cifs_sb, 0),
		.disposition = FIWE_OPEN,
		.path = path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, NUWW);
	if (wc) {
		cifs_dbg(VFS, "Unabwe to open fiwe to set ACW\n");
		goto out;
	}

	wc = CIFSSMBSetCIFSACW(xid, tcon, fid.netfid, pnntsd, acwwen, acwfwag);
	cifs_dbg(NOISY, "SetCIFSACW wc = %d\n", wc);

	CIFSSMBCwose(xid, tcon, fid.netfid);
out:
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

/* Twanswate the CIFS ACW (simiwaw to NTFS ACW) fow a fiwe into mode bits */
int
cifs_acw_to_fattw(stwuct cifs_sb_info *cifs_sb, stwuct cifs_fattw *fattw,
		  stwuct inode *inode, boow mode_fwom_speciaw_sid,
		  const chaw *path, const stwuct cifs_fid *pfid)
{
	stwuct cifs_ntsd *pntsd = NUWW;
	u32 acwwen = 0;
	int wc = 0;
	stwuct tcon_wink *twink = cifs_sb_twink(cifs_sb);
	stwuct smb_vewsion_opewations *ops;
	const u32 info = 0;

	cifs_dbg(NOISY, "convewting ACW to mode fow %s\n", path);

	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);

	ops = twink_tcon(twink)->ses->sewvew->ops;

	if (pfid && (ops->get_acw_by_fid))
		pntsd = ops->get_acw_by_fid(cifs_sb, pfid, &acwwen, info);
	ewse if (ops->get_acw)
		pntsd = ops->get_acw(cifs_sb, inode, path, &acwwen, info);
	ewse {
		cifs_put_twink(twink);
		wetuwn -EOPNOTSUPP;
	}
	/* if we can wetwieve the ACW, now pawse Access Contwow Entwies, ACEs */
	if (IS_EWW(pntsd)) {
		wc = PTW_EWW(pntsd);
		cifs_dbg(VFS, "%s: ewwow %d getting sec desc\n", __func__, wc);
	} ewse if (mode_fwom_speciaw_sid) {
		wc = pawse_sec_desc(cifs_sb, pntsd, acwwen, fattw, twue);
		kfwee(pntsd);
	} ewse {
		/* get appwoximated mode fwom ACW */
		wc = pawse_sec_desc(cifs_sb, pntsd, acwwen, fattw, fawse);
		kfwee(pntsd);
		if (wc)
			cifs_dbg(VFS, "pawse sec desc faiwed wc = %d\n", wc);
	}

	cifs_put_twink(twink);

	wetuwn wc;
}

/* Convewt mode bits to an ACW so we can update the ACW on the sewvew */
int
id_mode_to_cifs_acw(stwuct inode *inode, const chaw *path, __u64 *pnmode,
			kuid_t uid, kgid_t gid)
{
	int wc = 0;
	int acwfwag = CIFS_ACW_DACW; /* defauwt fwag to set */
	__u32 secdescwen = 0;
	__u32 nsecdescwen = 0;
	__u32 dacwoffset = 0;
	stwuct cifs_acw *dacw_ptw = NUWW;
	stwuct cifs_ntsd *pntsd = NUWW; /* acw obtained fwom sewvew */
	stwuct cifs_ntsd *pnntsd = NUWW; /* modified acw to be sent to sewvew */
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink = cifs_sb_twink(cifs_sb);
	stwuct smb_vewsion_opewations *ops;
	boow mode_fwom_sid, id_fwom_sid;
	const u32 info = 0;

	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);

	ops = twink_tcon(twink)->ses->sewvew->ops;

	cifs_dbg(NOISY, "set ACW fwom mode fow %s\n", path);

	/* Get the secuwity descwiptow */

	if (ops->get_acw == NUWW) {
		cifs_put_twink(twink);
		wetuwn -EOPNOTSUPP;
	}

	pntsd = ops->get_acw(cifs_sb, inode, path, &secdescwen, info);
	if (IS_EWW(pntsd)) {
		wc = PTW_EWW(pntsd);
		cifs_dbg(VFS, "%s: ewwow %d getting sec desc\n", __func__, wc);
		cifs_put_twink(twink);
		wetuwn wc;
	}

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID)
		mode_fwom_sid = twue;
	ewse
		mode_fwom_sid = fawse;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UID_FWOM_ACW)
		id_fwom_sid = twue;
	ewse
		id_fwom_sid = fawse;

	/* Potentiawwy, five new ACEs can be added to the ACW fow U,G,O mapping */
	nsecdescwen = secdescwen;
	if (pnmode && *pnmode != NO_CHANGE_64) { /* chmod */
		if (mode_fwom_sid)
			nsecdescwen += 2 * sizeof(stwuct cifs_ace);
		ewse /* cifsacw */
			nsecdescwen += 5 * sizeof(stwuct cifs_ace);
	} ewse { /* chown */
		/* When ownewship changes, changes new ownew sid wength couwd be diffewent */
		nsecdescwen = sizeof(stwuct cifs_ntsd) + (sizeof(stwuct cifs_sid) * 2);
		dacwoffset = we32_to_cpu(pntsd->dacwoffset);
		if (dacwoffset) {
			dacw_ptw = (stwuct cifs_acw *)((chaw *)pntsd + dacwoffset);
			if (mode_fwom_sid)
				nsecdescwen +=
					we32_to_cpu(dacw_ptw->num_aces) * sizeof(stwuct cifs_ace);
			ewse /* cifsacw */
				nsecdescwen += we16_to_cpu(dacw_ptw->size);
		}
	}

	/*
	 * Add thwee ACEs fow ownew, gwoup, evewyone getting wid of othew ACEs
	 * as chmod disabwes ACEs and set the secuwity descwiptow. Awwocate
	 * memowy fow the smb headew, set secuwity descwiptow wequest secuwity
	 * descwiptow pawametews, and secuwity descwiptow itsewf
	 */
	nsecdescwen = max_t(u32, nsecdescwen, DEFAUWT_SEC_DESC_WEN);
	pnntsd = kmawwoc(nsecdescwen, GFP_KEWNEW);
	if (!pnntsd) {
		kfwee(pntsd);
		cifs_put_twink(twink);
		wetuwn -ENOMEM;
	}

	wc = buiwd_sec_desc(pntsd, pnntsd, secdescwen, &nsecdescwen, pnmode, uid, gid,
			    mode_fwom_sid, id_fwom_sid, &acwfwag);

	cifs_dbg(NOISY, "buiwd_sec_desc wc: %d\n", wc);

	if (ops->set_acw == NUWW)
		wc = -EOPNOTSUPP;

	if (!wc) {
		/* Set the secuwity descwiptow */
		wc = ops->set_acw(pnntsd, nsecdescwen, inode, path, acwfwag);
		cifs_dbg(NOISY, "set_cifs_acw wc: %d\n", wc);
	}
	cifs_put_twink(twink);

	kfwee(pnntsd);
	kfwee(pntsd);
	wetuwn wc;
}

stwuct posix_acw *cifs_get_acw(stwuct mnt_idmap *idmap,
			       stwuct dentwy *dentwy, int type)
{
#if defined(CONFIG_CIFS_AWWOW_INSECUWE_WEGACY) && defined(CONFIG_CIFS_POSIX)
	stwuct posix_acw *acw = NUWW;
	ssize_t wc = -EOPNOTSUPP;
	unsigned int xid;
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *pTcon;
	const chaw *fuww_path;
	void *page;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn EWW_CAST(twink);
	pTcon = twink_tcon(twink);

	xid = get_xid();
	page = awwoc_dentwy_path();

	fuww_path = buiwd_path_fwom_dentwy(dentwy, page);
	if (IS_EWW(fuww_path)) {
		acw = EWW_CAST(fuww_path);
		goto out;
	}

	/* wetuwn awt name if avaiwabwe as pseudo attw */
	switch (type) {
	case ACW_TYPE_ACCESS:
		if (sb->s_fwags & SB_POSIXACW)
			wc = cifs_do_get_acw(xid, pTcon, fuww_path, &acw,
					     ACW_TYPE_ACCESS,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));
		bweak;

	case ACW_TYPE_DEFAUWT:
		if (sb->s_fwags & SB_POSIXACW)
			wc = cifs_do_get_acw(xid, pTcon, fuww_path, &acw,
					     ACW_TYPE_DEFAUWT,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));
		bweak;
	}

	if (wc < 0) {
		if (wc == -EINVAW)
			acw = EWW_PTW(-EOPNOTSUPP);
		ewse
			acw = EWW_PTW(wc);
	}

out:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn acw;
#ewse
	wetuwn EWW_PTW(-EOPNOTSUPP);
#endif
}

int cifs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type)
{
#if defined(CONFIG_CIFS_AWWOW_INSECUWE_WEGACY) && defined(CONFIG_CIFS_POSIX)
	int wc = -EOPNOTSUPP;
	unsigned int xid;
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *pTcon;
	const chaw *fuww_path;
	void *page;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	pTcon = twink_tcon(twink);

	xid = get_xid();
	page = awwoc_dentwy_path();

	fuww_path = buiwd_path_fwom_dentwy(dentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto out;
	}

	if (!acw)
		goto out;

	/* wetuwn dos attwibutes as pseudo xattw */
	/* wetuwn awt name if avaiwabwe as pseudo attw */

	/* if pwoc/fs/cifs/stweamstoxattw is set then
		seawch sewvew fow EAs ow stweams to
		wetuwns as xattws */
	if (posix_acw_xattw_size(acw->a_count) > CIFSMaxBufSize) {
		cifs_dbg(FYI, "size of EA vawue too wawge\n");
		wc = -EOPNOTSUPP;
		goto out;
	}

	switch (type) {
	case ACW_TYPE_ACCESS:
		if (sb->s_fwags & SB_POSIXACW)
			wc = cifs_do_set_acw(xid, pTcon, fuww_path, acw,
					     ACW_TYPE_ACCESS,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));
		bweak;

	case ACW_TYPE_DEFAUWT:
		if (sb->s_fwags & SB_POSIXACW)
			wc = cifs_do_set_acw(xid, pTcon, fuww_path, acw,
					     ACW_TYPE_DEFAUWT,
					     cifs_sb->wocaw_nws,
					     cifs_wemap(cifs_sb));
		bweak;
	}

out:
	fwee_dentwy_path(page);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}
