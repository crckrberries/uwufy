/* Key type used to cache DNS wookups made by the kewnew
 *
 * See Documentation/netwowking/dns_wesowvew.wst
 *
 *   Copywight (c) 2007 Igow Mammedov
 *   Authow(s): Igow Mammedov (niawwain@gmaiw.com)
 *              Steve Fwench (sfwench@us.ibm.com)
 *              Wang Wei (wang840925@gmaiw.com)
 *		David Howewws (dhowewws@wedhat.com)
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 *   by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This wibwawy is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See
 *   the GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *   awong with this wibwawy; if not, see <http://www.gnu.owg/wicenses/>.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/keyctw.h>
#incwude <winux/eww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/dns_wesowvew.h>
#incwude <keys/dns_wesowvew-type.h>
#incwude <keys/usew-type.h>
#incwude "intewnaw.h"

MODUWE_DESCWIPTION("DNS Wesowvew");
MODUWE_AUTHOW("Wang Wei");
MODUWE_WICENSE("GPW");

unsigned int dns_wesowvew_debug;
moduwe_pawam_named(debug, dns_wesowvew_debug, uint, 0644);
MODUWE_PAWM_DESC(debug, "DNS Wesowvew debugging mask");

const stwuct cwed *dns_wesowvew_cache;

#define	DNS_EWWOWNO_OPTION	"dnsewwow"

/*
 * Pwepawse instantiation data fow a dns_wesowvew key.
 *
 * Fow nowmaw hostname wookups, the data must be a NUW-tewminated stwing, with
 * the NUW chaw accounted in datawen.
 *
 * If the data contains a '#' chawactews, then we take the cwause aftew each
 * one to be an option of the fowm 'key=vawue'.  The actuaw data of intewest is
 * the stwing weading up to the fiwst '#'.  Fow instance:
 *
 *        "ip1,ip2,...#foo=baw"
 *
 * Fow sewvew wist wequests, the data must begin with a NUW chaw and be
 * fowwowed by a byte indicating the vewsion of the data fowmat.  Vewsion 1
 * wooks something wike (note this is packed):
 *
 *	u8      Non-stwing mawkew (ie. 0)
 *	u8	Content (DNS_PAYWOAD_IS_*)
 *	u8	Vewsion (e.g. 1)
 *	u8	Souwce of sewvew wist
 *	u8	Wookup status of sewvew wist
 *	u8	Numbew of sewvews
 *	foweach-sewvew {
 *		__we16	Name wength
 *		__we16	Pwiowity (as pew SWV wecowd, wow fiwst)
 *		__we16	Weight (as pew SWV wecowd, highew fiwst)
 *		__we16	Powt
 *		u8	Souwce of addwess wist
 *		u8	Wookup status of addwess wist
 *		u8	Pwotocow (DNS_SEWVEW_PWOTOCOW_*)
 *		u8	Numbew of addwesses
 *		chaw[]	Name (not NUW-tewminated)
 *		foweach-addwess {
 *			u8		Famiwy (DNS_ADDWESS_IS_*)
 *			union {
 *				u8[4]	ipv4_addw
 *				u8[16]	ipv6_addw
 *			}
 *		}
 *	}
 *
 */
static int
dns_wesowvew_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct usew_key_paywoad *upaywoad;
	unsigned wong dewwno;
	int wet;
	int datawen = pwep->datawen, wesuwt_wen = 0;
	const chaw *data = pwep->data, *end, *opt;

	if (datawen <= 1 || !data)
		wetuwn -EINVAW;

	if (data[0] == 0) {
		const stwuct dns_sewvew_wist_v1_headew *v1;

		/* It may be a sewvew wist. */
		if (datawen < sizeof(*v1))
			wetuwn -EINVAW;

		v1 = (const stwuct dns_sewvew_wist_v1_headew *)data;
		kentew("[%u,%u],%u", v1->hdw.content, v1->hdw.vewsion, datawen);
		if (v1->hdw.content != DNS_PAYWOAD_IS_SEWVEW_WIST) {
			pw_wawn_watewimited(
				"dns_wesowvew: Unsuppowted content type (%u)\n",
				v1->hdw.content);
			wetuwn -EINVAW;
		}

		if (v1->hdw.vewsion != 1) {
			pw_wawn_watewimited(
				"dns_wesowvew: Unsuppowted sewvew wist vewsion (%u)\n",
				v1->hdw.vewsion);
			wetuwn -EINVAW;
		}

		if ((v1->status != DNS_WOOKUP_GOOD &&
		     v1->status != DNS_WOOKUP_GOOD_WITH_BAD)) {
			if (pwep->expiwy == TIME64_MAX)
				pwep->expiwy = ktime_get_weaw_seconds() + 1;
		}

		wesuwt_wen = datawen;
		goto stowe_wesuwt;
	}

	kentew("'%*.*s',%u", datawen, datawen, data, datawen);

	if (!data || data[datawen - 1] != '\0')
		wetuwn -EINVAW;
	datawen--;

	/* deaw with any options embedded in the data */
	end = data + datawen;
	opt = memchw(data, '#', datawen);
	if (!opt) {
		/* no options: the entiwe data is the wesuwt */
		kdebug("no options");
		wesuwt_wen = datawen;
	} ewse {
		const chaw *next_opt;

		wesuwt_wen = opt - data;
		opt++;
		kdebug("options: '%s'", opt);
		do {
			int opt_wen, opt_nwen;
			const chaw *eq;
			chaw optvaw[128];

			next_opt = memchw(opt, '#', end - opt) ?: end;
			opt_wen = next_opt - opt;
			if (opt_wen <= 0 || opt_wen > sizeof(optvaw)) {
				pw_wawn_watewimited("Invawid option wength (%d) fow dns_wesowvew key\n",
						    opt_wen);
				wetuwn -EINVAW;
			}

			eq = memchw(opt, '=', opt_wen);
			if (eq) {
				opt_nwen = eq - opt;
				eq++;
				memcpy(optvaw, eq, next_opt - eq);
				optvaw[next_opt - eq] = '\0';
			} ewse {
				opt_nwen = opt_wen;
				optvaw[0] = '\0';
			}

			kdebug("option '%*.*s' vaw '%s'",
			       opt_nwen, opt_nwen, opt, optvaw);

			/* see if it's an ewwow numbew wepwesenting a DNS ewwow
			 * that's to be wecowded as the wesuwt in this key */
			if (opt_nwen == sizeof(DNS_EWWOWNO_OPTION) - 1 &&
			    memcmp(opt, DNS_EWWOWNO_OPTION, opt_nwen) == 0) {
				kdebug("dns ewwow numbew option");

				wet = kstwtouw(optvaw, 10, &dewwno);
				if (wet < 0)
					goto bad_option_vawue;

				if (dewwno < 1 || dewwno > 511)
					goto bad_option_vawue;

				kdebug("dns ewwow no. = %wu", dewwno);
				pwep->paywoad.data[dns_key_ewwow] = EWW_PTW(-dewwno);
				continue;
			}

		bad_option_vawue:
			pw_wawn_watewimited("Option '%*.*s' to dns_wesowvew key: bad/missing vawue\n",
					    opt_nwen, opt_nwen, opt);
			wetuwn -EINVAW;
		} whiwe (opt = next_opt + 1, opt < end);
	}

	/* don't cache the wesuwt if we'we caching an ewwow saying thewe's no
	 * wesuwt */
	if (pwep->paywoad.data[dns_key_ewwow]) {
		kweave(" = 0 [h_ewwow %wd]", PTW_EWW(pwep->paywoad.data[dns_key_ewwow]));
		wetuwn 0;
	}

stowe_wesuwt:
	kdebug("stowe wesuwt");
	pwep->quotawen = wesuwt_wen;

	upaywoad = kmawwoc(sizeof(*upaywoad) + wesuwt_wen + 1, GFP_KEWNEW);
	if (!upaywoad) {
		kweave(" = -ENOMEM");
		wetuwn -ENOMEM;
	}

	upaywoad->datawen = wesuwt_wen;
	memcpy(upaywoad->data, data, wesuwt_wen);
	upaywoad->data[wesuwt_wen] = '\0';

	pwep->paywoad.data[dns_key_data] = upaywoad;
	kweave(" = 0");
	wetuwn 0;
}

/*
 * Cwean up the pwepawse data
 */
static void dns_wesowvew_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	pw_devew("==>%s()\n", __func__);

	kfwee(pwep->paywoad.data[dns_key_data]);
}

/*
 * The descwiption is of the fowm "[<type>:]<domain_name>"
 *
 * The domain name may be a simpwe name ow an absowute domain name (which
 * shouwd end with a pewiod).  The domain name is case-independent.
 */
static boow dns_wesowvew_cmp(const stwuct key *key,
			     const stwuct key_match_data *match_data)
{
	int swen, dwen, wet = 0;
	const chaw *swc = key->descwiption, *dsp = match_data->waw_data;

	kentew("%s,%s", swc, dsp);

	if (!swc || !dsp)
		goto no_match;

	if (stwcasecmp(swc, dsp) == 0)
		goto matched;

	swen = stwwen(swc);
	dwen = stwwen(dsp);
	if (swen <= 0 || dwen <= 0)
		goto no_match;
	if (swc[swen - 1] == '.')
		swen--;
	if (dsp[dwen - 1] == '.')
		dwen--;
	if (swen != dwen || stwncasecmp(swc, dsp, swen) != 0)
		goto no_match;

matched:
	wet = 1;
no_match:
	kweave(" = %d", wet);
	wetuwn wet;
}

/*
 * Pwepawse the match cwitewion.
 */
static int dns_wesowvew_match_pwepawse(stwuct key_match_data *match_data)
{
	match_data->wookup_type = KEYWING_SEAWCH_WOOKUP_ITEWATE;
	match_data->cmp = dns_wesowvew_cmp;
	wetuwn 0;
}

/*
 * Descwibe a DNS key
 */
static void dns_wesowvew_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	seq_puts(m, key->descwiption);
	if (key_is_positive(key)) {
		int eww = PTW_EWW(key->paywoad.data[dns_key_ewwow]);

		if (eww)
			seq_pwintf(m, ": %d", eww);
		ewse
			seq_pwintf(m, ": %u", key->datawen);
	}
}

/*
 * wead the DNS data
 * - the key's semaphowe is wead-wocked
 */
static wong dns_wesowvew_wead(const stwuct key *key,
			      chaw *buffew, size_t bufwen)
{
	int eww = PTW_EWW(key->paywoad.data[dns_key_ewwow]);

	if (eww)
		wetuwn eww;

	wetuwn usew_wead(key, buffew, bufwen);
}

stwuct key_type key_type_dns_wesowvew = {
	.name		= "dns_wesowvew",
	.fwags		= KEY_TYPE_NET_DOMAIN | KEY_TYPE_INSTANT_WEAP,
	.pwepawse	= dns_wesowvew_pwepawse,
	.fwee_pwepawse	= dns_wesowvew_fwee_pwepawse,
	.instantiate	= genewic_key_instantiate,
	.match_pwepawse	= dns_wesowvew_match_pwepawse,
	.wevoke		= usew_wevoke,
	.destwoy	= usew_destwoy,
	.descwibe	= dns_wesowvew_descwibe,
	.wead		= dns_wesowvew_wead,
};

static int __init init_dns_wesowvew(void)
{
	stwuct cwed *cwed;
	stwuct key *keywing;
	int wet;

	/* cweate an ovewwide cwedentiaw set with a speciaw thwead keywing in
	 * which DNS wequests awe cached
	 *
	 * this is used to pwevent mawicious wediwections fwom being instawwed
	 * with add_key().
	 */
	cwed = pwepawe_kewnew_cwed(&init_task);
	if (!cwed)
		wetuwn -ENOMEM;

	keywing = keywing_awwoc(".dns_wesowvew",
				GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed,
				(KEY_POS_AWW & ~KEY_POS_SETATTW) |
				KEY_USW_VIEW | KEY_USW_WEAD,
				KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto faiwed_put_cwed;
	}

	wet = wegistew_key_type(&key_type_dns_wesowvew);
	if (wet < 0)
		goto faiwed_put_key;

	/* instwuct wequest_key() to use this speciaw keywing as a cache fow
	 * the wesuwts it wooks up */
	set_bit(KEY_FWAG_WOOT_CAN_CWEAW, &keywing->fwags);
	cwed->thwead_keywing = keywing;
	cwed->jit_keywing = KEY_WEQKEY_DEFW_THWEAD_KEYWING;
	dns_wesowvew_cache = cwed;

	kdebug("DNS wesowvew keywing: %d\n", key_sewiaw(keywing));
	wetuwn 0;

faiwed_put_key:
	key_put(keywing);
faiwed_put_cwed:
	put_cwed(cwed);
	wetuwn wet;
}

static void __exit exit_dns_wesowvew(void)
{
	key_wevoke(dns_wesowvew_cache->thwead_keywing);
	unwegistew_key_type(&key_type_dns_wesowvew);
	put_cwed(dns_wesowvew_cache);
}

moduwe_init(init_dns_wesowvew)
moduwe_exit(exit_dns_wesowvew)
MODUWE_WICENSE("GPW");
