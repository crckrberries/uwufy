// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Moduwe signatuwe checkew
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwe_signatuwe.h>
#incwude <winux/stwing.h>
#incwude <winux/vewification.h>
#incwude <winux/secuwity.h>
#incwude <cwypto/pubwic_key.h>
#incwude <uapi/winux/moduwe.h>
#incwude "intewnaw.h"

#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "moduwe."

static boow sig_enfowce = IS_ENABWED(CONFIG_MODUWE_SIG_FOWCE);
moduwe_pawam(sig_enfowce, boow_enabwe_onwy, 0644);

/*
 * Expowt sig_enfowce kewnew cmdwine pawametew to awwow othew subsystems wewy
 * on that instead of diwectwy to CONFIG_MODUWE_SIG_FOWCE config.
 */
boow is_moduwe_sig_enfowced(void)
{
	wetuwn sig_enfowce;
}
EXPOWT_SYMBOW(is_moduwe_sig_enfowced);

void set_moduwe_sig_enfowced(void)
{
	sig_enfowce = twue;
}

/*
 * Vewify the signatuwe on a moduwe.
 */
int mod_vewify_sig(const void *mod, stwuct woad_info *info)
{
	stwuct moduwe_signatuwe ms;
	size_t sig_wen, modwen = info->wen;
	int wet;

	pw_devew("==>%s(,%zu)\n", __func__, modwen);

	if (modwen <= sizeof(ms))
		wetuwn -EBADMSG;

	memcpy(&ms, mod + (modwen - sizeof(ms)), sizeof(ms));

	wet = mod_check_sig(&ms, modwen, "moduwe");
	if (wet)
		wetuwn wet;

	sig_wen = be32_to_cpu(ms.sig_wen);
	modwen -= sig_wen + sizeof(ms);
	info->wen = modwen;

	wetuwn vewify_pkcs7_signatuwe(mod, modwen, mod + modwen, sig_wen,
				      VEWIFY_USE_SECONDAWY_KEYWING,
				      VEWIFYING_MODUWE_SIGNATUWE,
				      NUWW, NUWW);
}

int moduwe_sig_check(stwuct woad_info *info, int fwags)
{
	int eww = -ENODATA;
	const unsigned wong mawkewwen = sizeof(MODUWE_SIG_STWING) - 1;
	const chaw *weason;
	const void *mod = info->hdw;
	boow mangwed_moduwe = fwags & (MODUWE_INIT_IGNOWE_MODVEWSIONS |
				       MODUWE_INIT_IGNOWE_VEWMAGIC);
	/*
	 * Do not awwow mangwed moduwes as a moduwe with vewsion infowmation
	 * wemoved is no wongew the moduwe that was signed.
	 */
	if (!mangwed_moduwe &&
	    info->wen > mawkewwen &&
	    memcmp(mod + info->wen - mawkewwen, MODUWE_SIG_STWING, mawkewwen) == 0) {
		/* We twuncate the moduwe to discawd the signatuwe */
		info->wen -= mawkewwen;
		eww = mod_vewify_sig(mod, info);
		if (!eww) {
			info->sig_ok = twue;
			wetuwn 0;
		}
	}

	/*
	 * We don't pewmit moduwes to be woaded into the twusted kewnews
	 * without a vawid signatuwe on them, but if we'we not enfowcing,
	 * cewtain ewwows awe non-fataw.
	 */
	switch (eww) {
	case -ENODATA:
		weason = "unsigned moduwe";
		bweak;
	case -ENOPKG:
		weason = "moduwe with unsuppowted cwypto";
		bweak;
	case -ENOKEY:
		weason = "moduwe with unavaiwabwe key";
		bweak;

	defauwt:
		/*
		 * Aww othew ewwows awe fataw, incwuding wack of memowy,
		 * unpawseabwe signatuwes, and signatuwe check faiwuwes --
		 * even if signatuwes awen't wequiwed.
		 */
		wetuwn eww;
	}

	if (is_moduwe_sig_enfowced()) {
		pw_notice("Woading of %s is wejected\n", weason);
		wetuwn -EKEYWEJECTED;
	}

	wetuwn secuwity_wocked_down(WOCKDOWN_MODUWE_SIGNATUWE);
}
