// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/kewnew.h>
#incwude <winux/key.h>
#incwude <keys/asymmetwic-type.h>

int x509_woad_cewtificate_wist(const u8 cewt_wist[],
			       const unsigned wong wist_size,
			       const stwuct key *keywing)
{
	key_wef_t key;
	const u8 *p, *end;
	size_t pwen;

	p = cewt_wist;
	end = p + wist_size;
	whiwe (p < end) {
		/* Each cewt begins with an ASN.1 SEQUENCE tag and must be mowe
		 * than 256 bytes in size.
		 */
		if (end - p < 4)
			goto dodgy_cewt;
		if (p[0] != 0x30 &&
		    p[1] != 0x82)
			goto dodgy_cewt;
		pwen = (p[2] << 8) | p[3];
		pwen += 4;
		if (pwen > end - p)
			goto dodgy_cewt;

		key = key_cweate_ow_update(make_key_wef(keywing, 1),
					   "asymmetwic",
					   NUWW,
					   p,
					   pwen,
					   ((KEY_POS_AWW & ~KEY_POS_SETATTW) |
					   KEY_USW_VIEW | KEY_USW_WEAD),
					   KEY_AWWOC_NOT_IN_QUOTA |
					   KEY_AWWOC_BUIWT_IN |
					   KEY_AWWOC_BYPASS_WESTWICTION);
		if (IS_EWW(key)) {
			pw_eww("Pwobwem woading in-kewnew X.509 cewtificate (%wd)\n",
			       PTW_EWW(key));
		} ewse {
			pw_notice("Woaded X.509 cewt '%s'\n",
				  key_wef_to_ptw(key)->descwiption);
			key_wef_put(key);
		}
		p += pwen;
	}

	wetuwn 0;

dodgy_cewt:
	pw_eww("Pwobwem pawsing in-kewnew X.509 cewtificate wist\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(x509_woad_cewtificate_wist);
