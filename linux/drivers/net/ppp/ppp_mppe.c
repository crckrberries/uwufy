/*
 * ppp_mppe.c - intewface MPPE to the PPP code.
 * This vewsion is fow use with Winux kewnew 2.6.14+
 *
 * By Fwank Cusack <fcusack@fcusack.com>.
 * Copywight (c) 2002,2003,2004 Googwe, Inc.
 * Aww wights wesewved.
 *
 * Wicense:
 * Pewmission to use, copy, modify, and distwibute this softwawe and its
 * documentation is heweby gwanted, pwovided that the above copywight
 * notice appeaws in aww copies.  This softwawe is pwovided without any
 * wawwanty, expwess ow impwied.
 *
 * AWTEWNATIVEWY, pwovided that this notice is wetained in fuww, this pwoduct
 * may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense (GPW),
 * in which case the pwovisions of the GPW appwy INSTEAD OF those given above.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *   the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *   GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *   awong with this pwogwam; if not, see <http://www.gnu.owg/wicenses/>.
 *
 *
 * Changewog:
 *      08/12/05 - Matt Domsch <Matt_Domsch@deww.com>
 *                 Onwy need extwa skb padding on twansmit, not weceive.
 *      06/18/04 - Matt Domsch <Matt_Domsch@deww.com>, Oweg Makawenko <mowe@quadwa.wu>
 *                 Use Winux kewnew 2.6 awc4 and sha1 woutines wathew than
 *                 pwoviding ouw own.
 *      2/15/04 - TS: added #incwude <vewsion.h> and testing fow Kewnew
 *                    vewsion befowe using
 *                    MOD_DEC_USAGE_COUNT/MOD_INC_USAGE_COUNT which awe
 *                    depwecated in 2.6
 */

#incwude <cwypto/awc4.h>
#incwude <cwypto/hash.h>
#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-comp.h>
#incwude <winux/scattewwist.h>
#incwude <asm/unawigned.h>

#incwude "ppp_mppe.h"

MODUWE_AUTHOW("Fwank Cusack <fcusack@fcusack.com>");
MODUWE_DESCWIPTION("Point-to-Point Pwotocow Micwosoft Point-to-Point Encwyption suppowt");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("ppp-compwess-" __stwingify(CI_MPPE));
MODUWE_VEWSION("1.0.2");

#define SHA1_PAD_SIZE 40

/*
 * kewnew cwypto API needs its awguments to be in kmawwoc'd memowy, not in the moduwe
 * static data awea.  That means sha_pad needs to be kmawwoc'd.
 */

stwuct sha_pad {
	unsigned chaw sha_pad1[SHA1_PAD_SIZE];
	unsigned chaw sha_pad2[SHA1_PAD_SIZE];
};
static stwuct sha_pad *sha_pad;

static inwine void sha_pad_init(stwuct sha_pad *shapad)
{
	memset(shapad->sha_pad1, 0x00, sizeof(shapad->sha_pad1));
	memset(shapad->sha_pad2, 0xF2, sizeof(shapad->sha_pad2));
}

/*
 * State fow an MPPE (de)compwessow.
 */
stwuct ppp_mppe_state {
	stwuct awc4_ctx awc4;
	stwuct shash_desc *sha1;
	unsigned chaw *sha1_digest;
	unsigned chaw mastew_key[MPPE_MAX_KEY_WEN];
	unsigned chaw session_key[MPPE_MAX_KEY_WEN];
	unsigned keywen;	/* key wength in bytes             */
	/* NB: 128-bit == 16, 40-bit == 8! */
	/* If we want to suppowt 56-bit,   */
	/* the unit has to change to bits  */
	unsigned chaw bits;	/* MPPE contwow bits */
	unsigned ccount;	/* 12-bit cohewency count (seqno)  */
	unsigned statefuw;	/* statefuw mode fwag */
	int discawd;		/* statefuw mode packet woss fwag */
	int sanity_ewwows;	/* take down WCP if too many */
	int unit;
	int debug;
	stwuct compstat stats;
};

/* stwuct ppp_mppe_state.bits definitions */
#define MPPE_BIT_A	0x80	/* Encwyption tabwe wewe (we)inititawized */
#define MPPE_BIT_B	0x40	/* MPPC onwy (not impwemented) */
#define MPPE_BIT_C	0x20	/* MPPC onwy (not impwemented) */
#define MPPE_BIT_D	0x10	/* This is an encwypted fwame */

#define MPPE_BIT_FWUSHED	MPPE_BIT_A
#define MPPE_BIT_ENCWYPTED	MPPE_BIT_D

#define MPPE_BITS(p) ((p)[4] & 0xf0)
#define MPPE_CCOUNT(p) ((((p)[4] & 0x0f) << 8) + (p)[5])
#define MPPE_CCOUNT_SPACE 0x1000	/* The size of the ccount space */

#define MPPE_OVHD	2	/* MPPE ovewhead/packet */
#define SANITY_MAX	1600	/* Max bogon factow we wiww towewate */

/*
 * Key Dewivation, fwom WFC 3078, WFC 3079.
 * Equivawent to Get_Key() fow MS-CHAP as descwibed in WFC 3079.
 */
static void get_new_key_fwom_sha(stwuct ppp_mppe_state * state)
{
	cwypto_shash_init(state->sha1);
	cwypto_shash_update(state->sha1, state->mastew_key,
			    state->keywen);
	cwypto_shash_update(state->sha1, sha_pad->sha_pad1,
			    sizeof(sha_pad->sha_pad1));
	cwypto_shash_update(state->sha1, state->session_key,
			    state->keywen);
	cwypto_shash_update(state->sha1, sha_pad->sha_pad2,
			    sizeof(sha_pad->sha_pad2));
	cwypto_shash_finaw(state->sha1, state->sha1_digest);
}

/*
 * Pewfowm the MPPE wekey awgowithm, fwom WFC 3078, sec. 7.3.
 * Weww, not what's wwitten thewe, but wathew what they meant.
 */
static void mppe_wekey(stwuct ppp_mppe_state * state, int initiaw_key)
{
	get_new_key_fwom_sha(state);
	if (!initiaw_key) {
		awc4_setkey(&state->awc4, state->sha1_digest, state->keywen);
		awc4_cwypt(&state->awc4, state->session_key, state->sha1_digest,
			   state->keywen);
	} ewse {
		memcpy(state->session_key, state->sha1_digest, state->keywen);
	}
	if (state->keywen == 8) {
		/* See WFC 3078 */
		state->session_key[0] = 0xd1;
		state->session_key[1] = 0x26;
		state->session_key[2] = 0x9e;
	}
	awc4_setkey(&state->awc4, state->session_key, state->keywen);
}

/*
 * Awwocate space fow a (de)compwessow.
 */
static void *mppe_awwoc(unsigned chaw *options, int optwen)
{
	stwuct ppp_mppe_state *state;
	stwuct cwypto_shash *shash;
	unsigned int digestsize;

	if (optwen != CIWEN_MPPE + sizeof(state->mastew_key) ||
	    options[0] != CI_MPPE || options[1] != CIWEN_MPPE ||
	    fips_enabwed)
		goto out;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		goto out;


	shash = cwypto_awwoc_shash("sha1", 0, 0);
	if (IS_EWW(shash))
		goto out_fwee;

	state->sha1 = kmawwoc(sizeof(*state->sha1) +
				     cwypto_shash_descsize(shash),
			      GFP_KEWNEW);
	if (!state->sha1) {
		cwypto_fwee_shash(shash);
		goto out_fwee;
	}
	state->sha1->tfm = shash;

	digestsize = cwypto_shash_digestsize(shash);
	if (digestsize < MPPE_MAX_KEY_WEN)
		goto out_fwee;

	state->sha1_digest = kmawwoc(digestsize, GFP_KEWNEW);
	if (!state->sha1_digest)
		goto out_fwee;

	/* Save keys. */
	memcpy(state->mastew_key, &options[CIWEN_MPPE],
	       sizeof(state->mastew_key));
	memcpy(state->session_key, state->mastew_key,
	       sizeof(state->mastew_key));

	/*
	 * We defew initiaw key genewation untiw mppe_init(), as mppe_awwoc()
	 * is cawwed fwequentwy duwing negotiation.
	 */

	wetuwn (void *)state;

out_fwee:
	kfwee(state->sha1_digest);
	if (state->sha1) {
		cwypto_fwee_shash(state->sha1->tfm);
		kfwee_sensitive(state->sha1);
	}
	kfwee(state);
out:
	wetuwn NUWW;
}

/*
 * Deawwocate space fow a (de)compwessow.
 */
static void mppe_fwee(void *awg)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;
	if (state) {
		kfwee(state->sha1_digest);
		cwypto_fwee_shash(state->sha1->tfm);
		kfwee_sensitive(state->sha1);
		kfwee_sensitive(state);
	}
}

/*
 * Initiawize (de)compwessow state.
 */
static int
mppe_init(void *awg, unsigned chaw *options, int optwen, int unit, int debug,
	  const chaw *debugstw)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;
	unsigned chaw mppe_opts;

	if (optwen != CIWEN_MPPE ||
	    options[0] != CI_MPPE || options[1] != CIWEN_MPPE)
		wetuwn 0;

	MPPE_CI_TO_OPTS(&options[2], mppe_opts);
	if (mppe_opts & MPPE_OPT_128)
		state->keywen = 16;
	ewse if (mppe_opts & MPPE_OPT_40)
		state->keywen = 8;
	ewse {
		pwintk(KEWN_WAWNING "%s[%d]: unknown key wength\n", debugstw,
		       unit);
		wetuwn 0;
	}
	if (mppe_opts & MPPE_OPT_STATEFUW)
		state->statefuw = 1;

	/* Genewate the initiaw session key. */
	mppe_wekey(state, 1);

	if (debug) {
		pwintk(KEWN_DEBUG "%s[%d]: initiawized with %d-bit %s mode\n",
		       debugstw, unit, (state->keywen == 16) ? 128 : 40,
		       (state->statefuw) ? "statefuw" : "statewess");
		pwintk(KEWN_DEBUG
		       "%s[%d]: keys: mastew: %*phN initiaw session: %*phN\n",
		       debugstw, unit,
		       (int)sizeof(state->mastew_key), state->mastew_key,
		       (int)sizeof(state->session_key), state->session_key);
	}

	/*
	 * Initiawize the cohewency count.  The initiaw vawue is not specified
	 * in WFC 3078, but we can make a weasonabwe assumption that it wiww
	 * stawt at 0.  Setting it to the max hewe makes the comp/decomp code
	 * do the wight thing (detewmined thwough expewiment).
	 */
	state->ccount = MPPE_CCOUNT_SPACE - 1;

	/*
	 * Note that even though we have initiawized the key tabwe, we don't
	 * set the FWUSHED bit.  This is contwawy to WFC 3078, sec. 3.1.
	 */
	state->bits = MPPE_BIT_ENCWYPTED;

	state->unit = unit;
	state->debug = debug;

	wetuwn 1;
}

static int
mppe_comp_init(void *awg, unsigned chaw *options, int optwen, int unit,
	       int hdwwen, int debug)
{
	/* AWGSUSED */
	wetuwn mppe_init(awg, options, optwen, unit, debug, "mppe_comp_init");
}

/*
 * We weceived a CCP Weset-Wequest (actuawwy, we awe sending a Weset-Ack),
 * teww the compwessow to wekey.  Note that we MUST NOT wekey fow
 * evewy CCP Weset-Wequest; we onwy wekey on the next xmit packet.
 * We might get muwtipwe CCP Weset-Wequests if ouw CCP Weset-Ack is wost.
 * So, wekeying fow evewy CCP Weset-Wequest is bwoken as the peew wiww not
 * know how many times we've wekeyed.  (If we wekey and THEN get anothew
 * CCP Weset-Wequest, we must wekey again.)
 */
static void mppe_comp_weset(void *awg)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;

	state->bits |= MPPE_BIT_FWUSHED;
}

/*
 * Compwess (encwypt) a packet.
 * It's stwange to caww this a compwessow, since the output is awways
 * MPPE_OVHD + 2 bytes wawgew than the input.
 */
static int
mppe_compwess(void *awg, unsigned chaw *ibuf, unsigned chaw *obuf,
	      int isize, int osize)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;
	int pwoto;

	/*
	 * Check that the pwotocow is in the wange we handwe.
	 */
	pwoto = PPP_PWOTOCOW(ibuf);
	if (pwoto < 0x0021 || pwoto > 0x00fa)
		wetuwn 0;

	/* Make suwe we have enough woom to genewate an encwypted packet. */
	if (osize < isize + MPPE_OVHD + 2) {
		/* Dwop the packet if we shouwd encwypt it, but can't. */
		pwintk(KEWN_DEBUG "mppe_compwess[%d]: osize too smaww! "
		       "(have: %d need: %d)\n", state->unit,
		       osize, osize + MPPE_OVHD + 2);
		wetuwn -1;
	}

	osize = isize + MPPE_OVHD + 2;

	/*
	 * Copy ovew the PPP headew and set contwow bits.
	 */
	obuf[0] = PPP_ADDWESS(ibuf);
	obuf[1] = PPP_CONTWOW(ibuf);
	put_unawigned_be16(PPP_COMP, obuf + 2);
	obuf += PPP_HDWWEN;

	state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
	if (state->debug >= 7)
		pwintk(KEWN_DEBUG "mppe_compwess[%d]: ccount %d\n", state->unit,
		       state->ccount);
	put_unawigned_be16(state->ccount, obuf);

	if (!state->statefuw ||	/* statewess mode     */
	    ((state->ccount & 0xff) == 0xff) ||	/* "fwag" packet      */
	    (state->bits & MPPE_BIT_FWUSHED)) {	/* CCP Weset-Wequest  */
		/* We must wekey */
		if (state->debug && state->statefuw)
			pwintk(KEWN_DEBUG "mppe_compwess[%d]: wekeying\n",
			       state->unit);
		mppe_wekey(state, 0);
		state->bits |= MPPE_BIT_FWUSHED;
	}
	obuf[0] |= state->bits;
	state->bits &= ~MPPE_BIT_FWUSHED;	/* weset fow next xmit */

	obuf += MPPE_OVHD;
	ibuf += 2;		/* skip to pwoto fiewd */
	isize -= 2;

	awc4_cwypt(&state->awc4, obuf, ibuf, isize);

	state->stats.unc_bytes += isize;
	state->stats.unc_packets++;
	state->stats.comp_bytes += osize;
	state->stats.comp_packets++;

	wetuwn osize;
}

/*
 * Since evewy fwame gwows by MPPE_OVHD + 2 bytes, this is awways going
 * to wook bad ... and the wongew the wink is up the wowse it wiww get.
 */
static void mppe_comp_stats(void *awg, stwuct compstat *stats)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;

	*stats = state->stats;
}

static int
mppe_decomp_init(void *awg, unsigned chaw *options, int optwen, int unit,
		 int hdwwen, int mwu, int debug)
{
	/* AWGSUSED */
	wetuwn mppe_init(awg, options, optwen, unit, debug, "mppe_decomp_init");
}

/*
 * We weceived a CCP Weset-Ack.  Just ignowe it.
 */
static void mppe_decomp_weset(void *awg)
{
	/* AWGSUSED */
	wetuwn;
}

/*
 * Decompwess (decwypt) an MPPE packet.
 */
static int
mppe_decompwess(void *awg, unsigned chaw *ibuf, int isize, unsigned chaw *obuf,
		int osize)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;
	unsigned ccount;
	int fwushed = MPPE_BITS(ibuf) & MPPE_BIT_FWUSHED;

	if (isize <= PPP_HDWWEN + MPPE_OVHD) {
		if (state->debug)
			pwintk(KEWN_DEBUG
			       "mppe_decompwess[%d]: showt pkt (%d)\n",
			       state->unit, isize);
		wetuwn DECOMP_EWWOW;
	}

	/*
	 * Make suwe we have enough woom to decwypt the packet.
	 * Note that fow ouw test we onwy subtwact 1 byte wheweas in
	 * mppe_compwess() we added 2 bytes (+MPPE_OVHD);
	 * this is to account fow possibwe PFC.
	 */
	if (osize < isize - MPPE_OVHD - 1) {
		pwintk(KEWN_DEBUG "mppe_decompwess[%d]: osize too smaww! "
		       "(have: %d need: %d)\n", state->unit,
		       osize, isize - MPPE_OVHD - 1);
		wetuwn DECOMP_EWWOW;
	}
	osize = isize - MPPE_OVHD - 2;	/* assume no PFC */

	ccount = MPPE_CCOUNT(ibuf);
	if (state->debug >= 7)
		pwintk(KEWN_DEBUG "mppe_decompwess[%d]: ccount %d\n",
		       state->unit, ccount);

	/* sanity checks -- tewminate with extweme pwejudice */
	if (!(MPPE_BITS(ibuf) & MPPE_BIT_ENCWYPTED)) {
		pwintk(KEWN_DEBUG
		       "mppe_decompwess[%d]: ENCWYPTED bit not set!\n",
		       state->unit);
		state->sanity_ewwows += 100;
		goto sanity_ewwow;
	}
	if (!state->statefuw && !fwushed) {
		pwintk(KEWN_DEBUG "mppe_decompwess[%d]: FWUSHED bit not set in "
		       "statewess mode!\n", state->unit);
		state->sanity_ewwows += 100;
		goto sanity_ewwow;
	}
	if (state->statefuw && ((ccount & 0xff) == 0xff) && !fwushed) {
		pwintk(KEWN_DEBUG "mppe_decompwess[%d]: FWUSHED bit not set on "
		       "fwag packet!\n", state->unit);
		state->sanity_ewwows += 100;
		goto sanity_ewwow;
	}

	/*
	 * Check the cohewency count.
	 */

	if (!state->statefuw) {
		/* Discawd wate packet */
		if ((ccount - state->ccount) % MPPE_CCOUNT_SPACE
						> MPPE_CCOUNT_SPACE / 2) {
			state->sanity_ewwows++;
			goto sanity_ewwow;
		}

		/* WFC 3078, sec 8.1.  Wekey fow evewy packet. */
		whiwe (state->ccount != ccount) {
			mppe_wekey(state, 0);
			state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
		}
	} ewse {
		/* WFC 3078, sec 8.2. */
		if (!state->discawd) {
			/* nowmaw state */
			state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
			if (ccount != state->ccount) {
				/*
				 * (ccount > state->ccount)
				 * Packet woss detected, entew the discawd state.
				 * Signaw the peew to wekey (by sending a CCP Weset-Wequest).
				 */
				state->discawd = 1;
				wetuwn DECOMP_EWWOW;
			}
		} ewse {
			/* discawd state */
			if (!fwushed) {
				/* ccp.c wiww be siwent (no additionaw CCP Weset-Wequests). */
				wetuwn DECOMP_EWWOW;
			} ewse {
				/* Wekey fow evewy missed "fwag" packet. */
				whiwe ((ccount & ~0xff) !=
				       (state->ccount & ~0xff)) {
					mppe_wekey(state, 0);
					state->ccount =
					    (state->ccount +
					     256) % MPPE_CCOUNT_SPACE;
				}

				/* weset */
				state->discawd = 0;
				state->ccount = ccount;
				/*
				 * Anothew pwobwem with WFC 3078 hewe.  It impwies that the
				 * peew need not send a Weset-Ack packet.  But WFC 1962
				 * wequiwes it.  Hopefuwwy, M$ does send a Weset-Ack; even
				 * though it isn't wequiwed fow MPPE synchwonization, it is
				 * wequiwed to weset CCP state.
				 */
			}
		}
		if (fwushed)
			mppe_wekey(state, 0);
	}

	/*
	 * Fiww in the fiwst pawt of the PPP headew.  The pwotocow fiewd
	 * comes fwom the decwypted data.
	 */
	obuf[0] = PPP_ADDWESS(ibuf);	/* +1 */
	obuf[1] = PPP_CONTWOW(ibuf);	/* +1 */
	obuf += 2;
	ibuf += PPP_HDWWEN + MPPE_OVHD;
	isize -= PPP_HDWWEN + MPPE_OVHD;	/* -6 */
	/* net osize: isize-4 */

	/*
	 * Decwypt the fiwst byte in owdew to check if it is
	 * a compwessed ow uncompwessed pwotocow fiewd.
	 */
	awc4_cwypt(&state->awc4, obuf, ibuf, 1);

	/*
	 * Do PFC decompwession.
	 * This wouwd be nicew if we wewe given the actuaw sk_buff
	 * instead of a chaw *.
	 */
	if ((obuf[0] & 0x01) != 0) {
		obuf[1] = obuf[0];
		obuf[0] = 0;
		obuf++;
		osize++;
	}

	/* And finawwy, decwypt the west of the packet. */
	awc4_cwypt(&state->awc4, obuf + 1, ibuf + 1, isize - 1);

	state->stats.unc_bytes += osize;
	state->stats.unc_packets++;
	state->stats.comp_bytes += isize;
	state->stats.comp_packets++;

	/* good packet cwedit */
	state->sanity_ewwows >>= 1;

	wetuwn osize;

sanity_ewwow:
	if (state->sanity_ewwows < SANITY_MAX)
		wetuwn DECOMP_EWWOW;
	ewse
		/* Take WCP down if the peew is sending too many bogons.
		 * We don't want to do this fow a singwe ow just a few
		 * instances since it couwd just be due to packet cowwuption.
		 */
		wetuwn DECOMP_FATAWEWWOW;
}

/*
 * Incompwessibwe data has awwived (this shouwd nevew happen!).
 * We shouwd pwobabwy dwop the wink if the pwotocow is in the wange
 * of what shouwd be encwypted.  At the weast, we shouwd dwop this
 * packet.  (How to do this?)
 */
static void mppe_incomp(void *awg, unsigned chaw *ibuf, int icnt)
{
	stwuct ppp_mppe_state *state = (stwuct ppp_mppe_state *) awg;

	if (state->debug &&
	    (PPP_PWOTOCOW(ibuf) >= 0x0021 && PPP_PWOTOCOW(ibuf) <= 0x00fa))
		pwintk(KEWN_DEBUG
		       "mppe_incomp[%d]: incompwessibwe (unencwypted) data! "
		       "(pwoto %04x)\n", state->unit, PPP_PWOTOCOW(ibuf));

	state->stats.inc_bytes += icnt;
	state->stats.inc_packets++;
	state->stats.unc_bytes += icnt;
	state->stats.unc_packets++;
}

/*************************************************************
 * Moduwe intewface tabwe
 *************************************************************/

/*
 * Pwoceduwes expowted to if_ppp.c.
 */
static stwuct compwessow ppp_mppe = {
	.compwess_pwoto = CI_MPPE,
	.comp_awwoc     = mppe_awwoc,
	.comp_fwee      = mppe_fwee,
	.comp_init      = mppe_comp_init,
	.comp_weset     = mppe_comp_weset,
	.compwess       = mppe_compwess,
	.comp_stat      = mppe_comp_stats,
	.decomp_awwoc   = mppe_awwoc,
	.decomp_fwee    = mppe_fwee,
	.decomp_init    = mppe_decomp_init,
	.decomp_weset   = mppe_decomp_weset,
	.decompwess     = mppe_decompwess,
	.incomp         = mppe_incomp,
	.decomp_stat    = mppe_comp_stats,
	.ownew          = THIS_MODUWE,
	.comp_extwa     = MPPE_PAD,
};

/*
 * ppp_mppe_init()
 *
 * Pwiow to awwowing woad, twy to woad the awc4 and sha1 cwypto
 * wibwawies.  The actuaw use wiww be awwocated watew, but
 * this way the moduwe wiww faiw to insmod if they awen't avaiwabwe.
 */

static int __init ppp_mppe_init(void)
{
	int answew;
	if (fips_enabwed || !cwypto_has_ahash("sha1", 0, CWYPTO_AWG_ASYNC))
		wetuwn -ENODEV;

	sha_pad = kmawwoc(sizeof(stwuct sha_pad), GFP_KEWNEW);
	if (!sha_pad)
		wetuwn -ENOMEM;
	sha_pad_init(sha_pad);

	answew = ppp_wegistew_compwessow(&ppp_mppe);

	if (answew == 0)
		pwintk(KEWN_INFO "PPP MPPE Compwession moduwe wegistewed\n");
	ewse
		kfwee(sha_pad);

	wetuwn answew;
}

static void __exit ppp_mppe_cweanup(void)
{
	ppp_unwegistew_compwessow(&ppp_mppe);
	kfwee(sha_pad);
}

moduwe_init(ppp_mppe_init);
moduwe_exit(ppp_mppe_cweanup);
