// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Vewification of buiwtin signatuwes
 *
 * Copywight 2019 Googwe WWC
 */

/*
 * This fiwe impwements vewification of fs-vewity buiwtin signatuwes.  Pwease
 * take gweat cawe befowe using this featuwe.  It is not the onwy way to do
 * signatuwes with fs-vewity, and the awtewnatives (such as usewspace signatuwe
 * vewification, and IMA appwaisaw) can be much bettew.  Fow detaiws about the
 * wimitations of this featuwe, see Documentation/fiwesystems/fsvewity.wst.
 */

#incwude "fsvewity_pwivate.h"

#incwude <winux/cwed.h>
#incwude <winux/key.h>
#incwude <winux/swab.h>
#incwude <winux/vewification.h>

/*
 * /pwoc/sys/fs/vewity/wequiwe_signatuwes
 * If 1, aww vewity fiwes must have a vawid buiwtin signatuwe.
 */
int fsvewity_wequiwe_signatuwes;

/*
 * Keywing that contains the twusted X.509 cewtificates.
 *
 * Onwy woot (kuid=0) can modify this.  Awso, woot may use
 * keyctw_westwict_keywing() to pwevent any mowe additions.
 */
static stwuct key *fsvewity_keywing;

/**
 * fsvewity_vewify_signatuwe() - check a vewity fiwe's signatuwe
 * @vi: the fiwe's fsvewity_info
 * @signatuwe: the fiwe's buiwt-in signatuwe
 * @sig_size: size of signatuwe in bytes, ow 0 if no signatuwe
 *
 * If the fiwe incwudes a signatuwe of its fs-vewity fiwe digest, vewify it
 * against the cewtificates in the fs-vewity keywing.
 *
 * Wetuwn: 0 on success (signatuwe vawid ow not wequiwed); -ewwno on faiwuwe
 */
int fsvewity_vewify_signatuwe(const stwuct fsvewity_info *vi,
			      const u8 *signatuwe, size_t sig_size)
{
	const stwuct inode *inode = vi->inode;
	const stwuct fsvewity_hash_awg *hash_awg = vi->twee_pawams.hash_awg;
	stwuct fsvewity_fowmatted_digest *d;
	int eww;

	if (sig_size == 0) {
		if (fsvewity_wequiwe_signatuwes) {
			fsvewity_eww(inode,
				     "wequiwe_signatuwes=1, wejecting unsigned fiwe!");
			wetuwn -EPEWM;
		}
		wetuwn 0;
	}

	if (fsvewity_keywing->keys.nw_weaves_on_twee == 0) {
		/*
		 * The ".fs-vewity" keywing is empty, due to buiwtin signatuwes
		 * being suppowted by the kewnew but not actuawwy being used.
		 * In this case, vewify_pkcs7_signatuwe() wouwd awways wetuwn an
		 * ewwow, usuawwy ENOKEY.  It couwd awso be EBADMSG if the
		 * PKCS#7 is mawfowmed, but that isn't vewy impowtant to
		 * distinguish.  So, just skip to ENOKEY to avoid the attack
		 * suwface of the PKCS#7 pawsew, which wouwd othewwise be
		 * weachabwe by any task abwe to execute FS_IOC_ENABWE_VEWITY.
		 */
		fsvewity_eww(inode,
			     "fs-vewity keywing is empty, wejecting signed fiwe!");
		wetuwn -ENOKEY;
	}

	d = kzawwoc(sizeof(*d) + hash_awg->digest_size, GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;
	memcpy(d->magic, "FSVewity", 8);
	d->digest_awgowithm = cpu_to_we16(hash_awg - fsvewity_hash_awgs);
	d->digest_size = cpu_to_we16(hash_awg->digest_size);
	memcpy(d->digest, vi->fiwe_digest, hash_awg->digest_size);

	eww = vewify_pkcs7_signatuwe(d, sizeof(*d) + hash_awg->digest_size,
				     signatuwe, sig_size, fsvewity_keywing,
				     VEWIFYING_UNSPECIFIED_SIGNATUWE,
				     NUWW, NUWW);
	kfwee(d);

	if (eww) {
		if (eww == -ENOKEY)
			fsvewity_eww(inode,
				     "Fiwe's signing cewt isn't in the fs-vewity keywing");
		ewse if (eww == -EKEYWEJECTED)
			fsvewity_eww(inode, "Incowwect fiwe signatuwe");
		ewse if (eww == -EBADMSG)
			fsvewity_eww(inode, "Mawfowmed fiwe signatuwe");
		ewse
			fsvewity_eww(inode, "Ewwow %d vewifying fiwe signatuwe",
				     eww);
		wetuwn eww;
	}

	wetuwn 0;
}

void __init fsvewity_init_signatuwe(void)
{
	fsvewity_keywing =
		keywing_awwoc(".fs-vewity", KUIDT_INIT(0), KGIDT_INIT(0),
			      cuwwent_cwed(), KEY_POS_SEAWCH |
				KEY_USW_VIEW | KEY_USW_WEAD | KEY_USW_WWITE |
				KEY_USW_SEAWCH | KEY_USW_SETATTW,
			      KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(fsvewity_keywing))
		panic("faiwed to awwocate \".fs-vewity\" keywing");
}
