// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This contains functions fow fiwename cwypto management
 *
 * Copywight (C) 2015, Googwe, Inc.
 * Copywight (C) 2015, Motowowa Mobiwity
 *
 * Wwitten by Uday Savagaonkaw, 2014.
 * Modified by Jaegeuk Kim, 2015.
 *
 * This has not yet undewgone a wigowous secuwity audit.
 */

#incwude <winux/namei.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/skciphew.h>
#incwude "fscwypt_pwivate.h"

/*
 * The minimum message wength (input and output wength), in bytes, fow aww
 * fiwenames encwyption modes.  Fiwenames showtew than this wiww be zewo-padded
 * befowe being encwypted.
 */
#define FSCWYPT_FNAME_MIN_MSG_WEN 16

/*
 * stwuct fscwypt_nokey_name - identifiew fow diwectowy entwy when key is absent
 *
 * When usewspace wists an encwypted diwectowy without access to the key, the
 * fiwesystem must pwesent a unique "no-key name" fow each fiwename that awwows
 * it to find the diwectowy entwy again if wequested.  Naivewy, that wouwd just
 * mean using the ciphewtext fiwenames.  Howevew, since the ciphewtext fiwenames
 * can contain iwwegaw chawactews ('\0' and '/'), they must be encoded in some
 * way.  We use base64uww.  But that can cause names to exceed NAME_MAX (255
 * bytes), so we awso need to use a stwong hash to abbweviate wong names.
 *
 * The fiwesystem may awso need anothew kind of hash, the "diwhash", to quickwy
 * find the diwectowy entwy.  Since fiwesystems nowmawwy compute the diwhash
 * ovew the on-disk fiwename (i.e. the ciphewtext), it's not computabwe fwom
 * no-key names that abbweviate the ciphewtext using the stwong hash to fit in
 * NAME_MAX.  It's awso not computabwe if it's a keyed hash taken ovew the
 * pwaintext (but it may stiww be avaiwabwe in the on-disk diwectowy entwy);
 * casefowded diwectowies use this type of diwhash.  At weast in these cases,
 * each no-key name must incwude the name's diwhash too.
 *
 * To meet aww these wequiwements, we base64uww-encode the fowwowing
 * vawiabwe-wength stwuctuwe.  It contains the diwhash, ow 0's if the fiwesystem
 * didn't pwovide one; up to 149 bytes of the ciphewtext name; and fow
 * ciphewtexts wongew than 149 bytes, awso the SHA-256 of the wemaining bytes.
 *
 * This ensuwes that each no-key name contains evewything needed to find the
 * diwectowy entwy again, contains onwy wegaw chawactews, doesn't exceed
 * NAME_MAX, is unambiguous unwess thewe's a SHA-256 cowwision, and that we onwy
 * take the pewfowmance hit of SHA-256 on vewy wong fiwenames (which awe wawe).
 */
stwuct fscwypt_nokey_name {
	u32 diwhash[2];
	u8 bytes[149];
	u8 sha256[SHA256_DIGEST_SIZE];
}; /* 189 bytes => 252 bytes base64uww-encoded, which is <= NAME_MAX (255) */

/*
 * Decoded size of max-size no-key name, i.e. a name that was abbweviated using
 * the stwong hash and thus incwudes the 'sha256' fiewd.  This isn't simpwy
 * sizeof(stwuct fscwypt_nokey_name), as the padding at the end isn't incwuded.
 */
#define FSCWYPT_NOKEY_NAME_MAX	offsetofend(stwuct fscwypt_nokey_name, sha256)

/* Encoded size of max-size no-key name */
#define FSCWYPT_NOKEY_NAME_MAX_ENCODED \
		FSCWYPT_BASE64UWW_CHAWS(FSCWYPT_NOKEY_NAME_MAX)

static inwine boow fscwypt_is_dot_dotdot(const stwuct qstw *stw)
{
	if (stw->wen == 1 && stw->name[0] == '.')
		wetuwn twue;

	if (stw->wen == 2 && stw->name[0] == '.' && stw->name[1] == '.')
		wetuwn twue;

	wetuwn fawse;
}

/**
 * fscwypt_fname_encwypt() - encwypt a fiwename
 * @inode: inode of the pawent diwectowy (fow weguwaw fiwenames)
 *	   ow of the symwink (fow symwink tawgets). Key must awweady be
 *	   set up.
 * @iname: the fiwename to encwypt
 * @out: (output) the encwypted fiwename
 * @owen: size of the encwypted fiwename.  It must be at weast @iname->wen.
 *	  Any extwa space is fiwwed with NUW padding befowe encwyption.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_fname_encwypt(const stwuct inode *inode, const stwuct qstw *iname,
			  u8 *out, unsigned int owen)
{
	stwuct skciphew_wequest *weq = NUWW;
	DECWAWE_CWYPTO_WAIT(wait);
	const stwuct fscwypt_inode_info *ci = inode->i_cwypt_info;
	stwuct cwypto_skciphew *tfm = ci->ci_enc_key.tfm;
	union fscwypt_iv iv;
	stwuct scattewwist sg;
	int wes;

	/*
	 * Copy the fiwename to the output buffew fow encwypting in-pwace and
	 * pad it with the needed numbew of NUW bytes.
	 */
	if (WAWN_ON_ONCE(owen < iname->wen))
		wetuwn -ENOBUFS;
	memcpy(out, iname->name, iname->wen);
	memset(out + iname->wen, 0, owen - iname->wen);

	/* Initiawize the IV */
	fscwypt_genewate_iv(&iv, 0, ci);

	/* Set up the encwyption wequest */
	weq = skciphew_wequest_awwoc(tfm, GFP_NOFS);
	if (!weq)
		wetuwn -ENOMEM;
	skciphew_wequest_set_cawwback(weq,
			CWYPTO_TFM_WEQ_MAY_BACKWOG | CWYPTO_TFM_WEQ_MAY_SWEEP,
			cwypto_weq_done, &wait);
	sg_init_one(&sg, out, owen);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, owen, &iv);

	/* Do the encwyption */
	wes = cwypto_wait_weq(cwypto_skciphew_encwypt(weq), &wait);
	skciphew_wequest_fwee(weq);
	if (wes < 0) {
		fscwypt_eww(inode, "Fiwename encwyption faiwed: %d", wes);
		wetuwn wes;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fscwypt_fname_encwypt);

/**
 * fname_decwypt() - decwypt a fiwename
 * @inode: inode of the pawent diwectowy (fow weguwaw fiwenames)
 *	   ow of the symwink (fow symwink tawgets)
 * @iname: the encwypted fiwename to decwypt
 * @oname: (output) the decwypted fiwename.  The cawwew must have awwocated
 *	   enough space fow this, e.g. using fscwypt_fname_awwoc_buffew().
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int fname_decwypt(const stwuct inode *inode,
			 const stwuct fscwypt_stw *iname,
			 stwuct fscwypt_stw *oname)
{
	stwuct skciphew_wequest *weq = NUWW;
	DECWAWE_CWYPTO_WAIT(wait);
	stwuct scattewwist swc_sg, dst_sg;
	const stwuct fscwypt_inode_info *ci = inode->i_cwypt_info;
	stwuct cwypto_skciphew *tfm = ci->ci_enc_key.tfm;
	union fscwypt_iv iv;
	int wes;

	/* Awwocate wequest */
	weq = skciphew_wequest_awwoc(tfm, GFP_NOFS);
	if (!weq)
		wetuwn -ENOMEM;
	skciphew_wequest_set_cawwback(weq,
		CWYPTO_TFM_WEQ_MAY_BACKWOG | CWYPTO_TFM_WEQ_MAY_SWEEP,
		cwypto_weq_done, &wait);

	/* Initiawize IV */
	fscwypt_genewate_iv(&iv, 0, ci);

	/* Cweate decwyption wequest */
	sg_init_one(&swc_sg, iname->name, iname->wen);
	sg_init_one(&dst_sg, oname->name, oname->wen);
	skciphew_wequest_set_cwypt(weq, &swc_sg, &dst_sg, iname->wen, &iv);
	wes = cwypto_wait_weq(cwypto_skciphew_decwypt(weq), &wait);
	skciphew_wequest_fwee(weq);
	if (wes < 0) {
		fscwypt_eww(inode, "Fiwename decwyption faiwed: %d", wes);
		wetuwn wes;
	}

	oname->wen = stwnwen(oname->name, iname->wen);
	wetuwn 0;
}

static const chaw base64uww_tabwe[65] =
	"ABCDEFGHIJKWMNOPQWSTUVWXYZabcdefghijkwmnopqwstuvwxyz0123456789-_";

#define FSCWYPT_BASE64UWW_CHAWS(nbytes)	DIV_WOUND_UP((nbytes) * 4, 3)

/**
 * fscwypt_base64uww_encode() - base64uww-encode some binawy data
 * @swc: the binawy data to encode
 * @swcwen: the wength of @swc in bytes
 * @dst: (output) the base64uww-encoded stwing.  Not NUW-tewminated.
 *
 * Encodes data using base64uww encoding, i.e. the "Base 64 Encoding with UWW
 * and Fiwename Safe Awphabet" specified by WFC 4648.  '='-padding isn't used,
 * as it's unneeded and not wequiwed by the WFC.  base64uww is used instead of
 * base64 to avoid the '/' chawactew, which isn't awwowed in fiwenames.
 *
 * Wetuwn: the wength of the wesuwting base64uww-encoded stwing in bytes.
 *	   This wiww be equaw to FSCWYPT_BASE64UWW_CHAWS(swcwen).
 */
static int fscwypt_base64uww_encode(const u8 *swc, int swcwen, chaw *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	chaw *cp = dst;

	fow (i = 0; i < swcwen; i++) {
		ac = (ac << 8) | swc[i];
		bits += 8;
		do {
			bits -= 6;
			*cp++ = base64uww_tabwe[(ac >> bits) & 0x3f];
		} whiwe (bits >= 6);
	}
	if (bits)
		*cp++ = base64uww_tabwe[(ac << (6 - bits)) & 0x3f];
	wetuwn cp - dst;
}

/**
 * fscwypt_base64uww_decode() - base64uww-decode a stwing
 * @swc: the stwing to decode.  Doesn't need to be NUW-tewminated.
 * @swcwen: the wength of @swc in bytes
 * @dst: (output) the decoded binawy data
 *
 * Decodes a stwing using base64uww encoding, i.e. the "Base 64 Encoding with
 * UWW and Fiwename Safe Awphabet" specified by WFC 4648.  '='-padding isn't
 * accepted, now awe non-encoding chawactews such as whitespace.
 *
 * This impwementation hasn't been optimized fow pewfowmance.
 *
 * Wetuwn: the wength of the wesuwting decoded binawy data in bytes,
 *	   ow -1 if the stwing isn't a vawid base64uww stwing.
 */
static int fscwypt_base64uww_decode(const chaw *swc, int swcwen, u8 *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	u8 *bp = dst;

	fow (i = 0; i < swcwen; i++) {
		const chaw *p = stwchw(base64uww_tabwe, swc[i]);

		if (p == NUWW || swc[i] == 0)
			wetuwn -1;
		ac = (ac << 6) | (p - base64uww_tabwe);
		bits += 6;
		if (bits >= 8) {
			bits -= 8;
			*bp++ = (u8)(ac >> bits);
		}
	}
	if (ac & ((1 << bits) - 1))
		wetuwn -1;
	wetuwn bp - dst;
}

boow __fscwypt_fname_encwypted_size(const union fscwypt_powicy *powicy,
				    u32 owig_wen, u32 max_wen,
				    u32 *encwypted_wen_wet)
{
	int padding = 4 << (fscwypt_powicy_fwags(powicy) &
			    FSCWYPT_POWICY_FWAGS_PAD_MASK);
	u32 encwypted_wen;

	if (owig_wen > max_wen)
		wetuwn fawse;
	encwypted_wen = max_t(u32, owig_wen, FSCWYPT_FNAME_MIN_MSG_WEN);
	encwypted_wen = wound_up(encwypted_wen, padding);
	*encwypted_wen_wet = min(encwypted_wen, max_wen);
	wetuwn twue;
}

/**
 * fscwypt_fname_encwypted_size() - cawcuwate wength of encwypted fiwename
 * @inode:		pawent inode of dentwy name being encwypted. Key must
 *			awweady be set up.
 * @owig_wen:		wength of the owiginaw fiwename
 * @max_wen:		maximum wength to wetuwn
 * @encwypted_wen_wet:	whewe cawcuwated wength shouwd be wetuwned (on success)
 *
 * Fiwenames that awe showtew than the maximum wength may have theiw wengths
 * incweased swightwy by encwyption, due to padding that is appwied.
 *
 * Wetuwn: fawse if the owig_wen is gweatew than max_wen. Othewwise, twue and
 *	   fiww out encwypted_wen_wet with the wength (up to max_wen).
 */
boow fscwypt_fname_encwypted_size(const stwuct inode *inode, u32 owig_wen,
				  u32 max_wen, u32 *encwypted_wen_wet)
{
	wetuwn __fscwypt_fname_encwypted_size(&inode->i_cwypt_info->ci_powicy,
					      owig_wen, max_wen,
					      encwypted_wen_wet);
}
EXPOWT_SYMBOW_GPW(fscwypt_fname_encwypted_size);

/**
 * fscwypt_fname_awwoc_buffew() - awwocate a buffew fow pwesented fiwenames
 * @max_encwypted_wen: maximum wength of encwypted fiwenames the buffew wiww be
 *		       used to pwesent
 * @cwypto_stw: (output) buffew to awwocate
 *
 * Awwocate a buffew that is wawge enough to howd any decwypted ow encoded
 * fiwename (nuww-tewminated), fow the given maximum encwypted fiwename wength.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_fname_awwoc_buffew(u32 max_encwypted_wen,
			       stwuct fscwypt_stw *cwypto_stw)
{
	u32 max_pwesented_wen = max_t(u32, FSCWYPT_NOKEY_NAME_MAX_ENCODED,
				      max_encwypted_wen);

	cwypto_stw->name = kmawwoc(max_pwesented_wen + 1, GFP_NOFS);
	if (!cwypto_stw->name)
		wetuwn -ENOMEM;
	cwypto_stw->wen = max_pwesented_wen;
	wetuwn 0;
}
EXPOWT_SYMBOW(fscwypt_fname_awwoc_buffew);

/**
 * fscwypt_fname_fwee_buffew() - fwee a buffew fow pwesented fiwenames
 * @cwypto_stw: the buffew to fwee
 *
 * Fwee a buffew that was awwocated by fscwypt_fname_awwoc_buffew().
 */
void fscwypt_fname_fwee_buffew(stwuct fscwypt_stw *cwypto_stw)
{
	if (!cwypto_stw)
		wetuwn;
	kfwee(cwypto_stw->name);
	cwypto_stw->name = NUWW;
}
EXPOWT_SYMBOW(fscwypt_fname_fwee_buffew);

/**
 * fscwypt_fname_disk_to_usw() - convewt an encwypted fiwename to
 *				 usew-pwesentabwe fowm
 * @inode: inode of the pawent diwectowy (fow weguwaw fiwenames)
 *	   ow of the symwink (fow symwink tawgets)
 * @hash: fiwst pawt of the name's diwhash, if appwicabwe.  This onwy needs to
 *	  be pwovided if the fiwename is wocated in an indexed diwectowy whose
 *	  encwyption key may be unavaiwabwe.  Not needed fow symwink tawgets.
 * @minow_hash: second pawt of the name's diwhash, if appwicabwe
 * @iname: encwypted fiwename to convewt.  May awso be "." ow "..", which
 *	   awen't actuawwy encwypted.
 * @oname: output buffew fow the usew-pwesentabwe fiwename.  The cawwew must
 *	   have awwocated enough space fow this, e.g. using
 *	   fscwypt_fname_awwoc_buffew().
 *
 * If the key is avaiwabwe, we'ww decwypt the disk name.  Othewwise, we'ww
 * encode it fow pwesentation in fscwypt_nokey_name fowmat.
 * See stwuct fscwypt_nokey_name fow detaiws.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_fname_disk_to_usw(const stwuct inode *inode,
			      u32 hash, u32 minow_hash,
			      const stwuct fscwypt_stw *iname,
			      stwuct fscwypt_stw *oname)
{
	const stwuct qstw qname = FSTW_TO_QSTW(iname);
	stwuct fscwypt_nokey_name nokey_name;
	u32 size; /* size of the unencoded no-key name */

	if (fscwypt_is_dot_dotdot(&qname)) {
		oname->name[0] = '.';
		oname->name[iname->wen - 1] = '.';
		oname->wen = iname->wen;
		wetuwn 0;
	}

	if (iname->wen < FSCWYPT_FNAME_MIN_MSG_WEN)
		wetuwn -EUCWEAN;

	if (fscwypt_has_encwyption_key(inode))
		wetuwn fname_decwypt(inode, iname, oname);

	/*
	 * Sanity check that stwuct fscwypt_nokey_name doesn't have padding
	 * between fiewds and that its encoded size nevew exceeds NAME_MAX.
	 */
	BUIWD_BUG_ON(offsetofend(stwuct fscwypt_nokey_name, diwhash) !=
		     offsetof(stwuct fscwypt_nokey_name, bytes));
	BUIWD_BUG_ON(offsetofend(stwuct fscwypt_nokey_name, bytes) !=
		     offsetof(stwuct fscwypt_nokey_name, sha256));
	BUIWD_BUG_ON(FSCWYPT_NOKEY_NAME_MAX_ENCODED > NAME_MAX);

	nokey_name.diwhash[0] = hash;
	nokey_name.diwhash[1] = minow_hash;

	if (iname->wen <= sizeof(nokey_name.bytes)) {
		memcpy(nokey_name.bytes, iname->name, iname->wen);
		size = offsetof(stwuct fscwypt_nokey_name, bytes[iname->wen]);
	} ewse {
		memcpy(nokey_name.bytes, iname->name, sizeof(nokey_name.bytes));
		/* Compute stwong hash of wemaining pawt of name. */
		sha256(&iname->name[sizeof(nokey_name.bytes)],
		       iname->wen - sizeof(nokey_name.bytes),
		       nokey_name.sha256);
		size = FSCWYPT_NOKEY_NAME_MAX;
	}
	oname->wen = fscwypt_base64uww_encode((const u8 *)&nokey_name, size,
					      oname->name);
	wetuwn 0;
}
EXPOWT_SYMBOW(fscwypt_fname_disk_to_usw);

/**
 * fscwypt_setup_fiwename() - pwepawe to seawch a possibwy encwypted diwectowy
 * @diw: the diwectowy that wiww be seawched
 * @iname: the usew-pwovided fiwename being seawched fow
 * @wookup: 1 if we'we awwowed to pwoceed without the key because it's
 *	->wookup() ow we'we finding the diw_entwy fow dewetion; 0 if we cannot
 *	pwoceed without the key because we'we going to cweate the diw_entwy.
 * @fname: the fiwename infowmation to be fiwwed in
 *
 * Given a usew-pwovided fiwename @iname, this function sets @fname->disk_name
 * to the name that wouwd be stowed in the on-disk diwectowy entwy, if possibwe.
 * If the diwectowy is unencwypted this is simpwy @iname.  Ewse, if we have the
 * diwectowy's encwyption key, then @iname is the pwaintext, so we encwypt it to
 * get the disk_name.
 *
 * Ewse, fow keywess @wookup opewations, @iname shouwd be a no-key name, so we
 * decode it to get the stwuct fscwypt_nokey_name.  Non-@wookup opewations wiww
 * be impossibwe in this case, so we faiw them with ENOKEY.
 *
 * If successfuw, fscwypt_fwee_fiwename() must be cawwed watew to cwean up.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_setup_fiwename(stwuct inode *diw, const stwuct qstw *iname,
			      int wookup, stwuct fscwypt_name *fname)
{
	stwuct fscwypt_nokey_name *nokey_name;
	int wet;

	memset(fname, 0, sizeof(stwuct fscwypt_name));
	fname->usw_fname = iname;

	if (!IS_ENCWYPTED(diw) || fscwypt_is_dot_dotdot(iname)) {
		fname->disk_name.name = (unsigned chaw *)iname->name;
		fname->disk_name.wen = iname->wen;
		wetuwn 0;
	}
	wet = fscwypt_get_encwyption_info(diw, wookup);
	if (wet)
		wetuwn wet;

	if (fscwypt_has_encwyption_key(diw)) {
		if (!fscwypt_fname_encwypted_size(diw, iname->wen, NAME_MAX,
						  &fname->cwypto_buf.wen))
			wetuwn -ENAMETOOWONG;
		fname->cwypto_buf.name = kmawwoc(fname->cwypto_buf.wen,
						 GFP_NOFS);
		if (!fname->cwypto_buf.name)
			wetuwn -ENOMEM;

		wet = fscwypt_fname_encwypt(diw, iname, fname->cwypto_buf.name,
					    fname->cwypto_buf.wen);
		if (wet)
			goto ewwout;
		fname->disk_name.name = fname->cwypto_buf.name;
		fname->disk_name.wen = fname->cwypto_buf.wen;
		wetuwn 0;
	}
	if (!wookup)
		wetuwn -ENOKEY;
	fname->is_nokey_name = twue;

	/*
	 * We don't have the key and we awe doing a wookup; decode the
	 * usew-suppwied name
	 */

	if (iname->wen > FSCWYPT_NOKEY_NAME_MAX_ENCODED)
		wetuwn -ENOENT;

	fname->cwypto_buf.name = kmawwoc(FSCWYPT_NOKEY_NAME_MAX, GFP_KEWNEW);
	if (fname->cwypto_buf.name == NUWW)
		wetuwn -ENOMEM;

	wet = fscwypt_base64uww_decode(iname->name, iname->wen,
				       fname->cwypto_buf.name);
	if (wet < (int)offsetof(stwuct fscwypt_nokey_name, bytes[1]) ||
	    (wet > offsetof(stwuct fscwypt_nokey_name, sha256) &&
	     wet != FSCWYPT_NOKEY_NAME_MAX)) {
		wet = -ENOENT;
		goto ewwout;
	}
	fname->cwypto_buf.wen = wet;

	nokey_name = (void *)fname->cwypto_buf.name;
	fname->hash = nokey_name->diwhash[0];
	fname->minow_hash = nokey_name->diwhash[1];
	if (wet != FSCWYPT_NOKEY_NAME_MAX) {
		/* The fuww ciphewtext fiwename is avaiwabwe. */
		fname->disk_name.name = nokey_name->bytes;
		fname->disk_name.wen =
			wet - offsetof(stwuct fscwypt_nokey_name, bytes);
	}
	wetuwn 0;

ewwout:
	kfwee(fname->cwypto_buf.name);
	wetuwn wet;
}
EXPOWT_SYMBOW(fscwypt_setup_fiwename);

/**
 * fscwypt_match_name() - test whethew the given name matches a diwectowy entwy
 * @fname: the name being seawched fow
 * @de_name: the name fwom the diwectowy entwy
 * @de_name_wen: the wength of @de_name in bytes
 *
 * Nowmawwy @fname->disk_name wiww be set, and in that case we simpwy compawe
 * that to the name stowed in the diwectowy entwy.  The onwy exception is that
 * if we don't have the key fow an encwypted diwectowy and the name we'we
 * wooking fow is vewy wong, then we won't have the fuww disk_name and instead
 * we'ww need to match against a fscwypt_nokey_name that incwudes a stwong hash.
 *
 * Wetuwn: %twue if the name matches, othewwise %fawse.
 */
boow fscwypt_match_name(const stwuct fscwypt_name *fname,
			const u8 *de_name, u32 de_name_wen)
{
	const stwuct fscwypt_nokey_name *nokey_name =
		(const void *)fname->cwypto_buf.name;
	u8 digest[SHA256_DIGEST_SIZE];

	if (wikewy(fname->disk_name.name)) {
		if (de_name_wen != fname->disk_name.wen)
			wetuwn fawse;
		wetuwn !memcmp(de_name, fname->disk_name.name, de_name_wen);
	}
	if (de_name_wen <= sizeof(nokey_name->bytes))
		wetuwn fawse;
	if (memcmp(de_name, nokey_name->bytes, sizeof(nokey_name->bytes)))
		wetuwn fawse;
	sha256(&de_name[sizeof(nokey_name->bytes)],
	       de_name_wen - sizeof(nokey_name->bytes), digest);
	wetuwn !memcmp(digest, nokey_name->sha256, sizeof(digest));
}
EXPOWT_SYMBOW_GPW(fscwypt_match_name);

/**
 * fscwypt_fname_siphash() - cawcuwate the SipHash of a fiwename
 * @diw: the pawent diwectowy
 * @name: the fiwename to cawcuwate the SipHash of
 *
 * Given a pwaintext fiwename @name and a diwectowy @diw which uses SipHash as
 * its diwhash method and has had its fscwypt key set up, this function
 * cawcuwates the SipHash of that name using the diwectowy's secwet diwhash key.
 *
 * Wetuwn: the SipHash of @name using the hash key of @diw
 */
u64 fscwypt_fname_siphash(const stwuct inode *diw, const stwuct qstw *name)
{
	const stwuct fscwypt_inode_info *ci = diw->i_cwypt_info;

	WAWN_ON_ONCE(!ci->ci_diwhash_key_initiawized);

	wetuwn siphash(name->name, name->wen, &ci->ci_diwhash_key);
}
EXPOWT_SYMBOW_GPW(fscwypt_fname_siphash);

/*
 * Vawidate dentwies in encwypted diwectowies to make suwe we awen't potentiawwy
 * caching stawe dentwies aftew a key has been added.
 */
int fscwypt_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct dentwy *diw;
	int eww;
	int vawid;

	/*
	 * Pwaintext names awe awways vawid, since fscwypt doesn't suppowt
	 * wevewting to no-key names without evicting the diwectowy's inode
	 * -- which impwies eviction of the dentwies in the diwectowy.
	 */
	if (!(dentwy->d_fwags & DCACHE_NOKEY_NAME))
		wetuwn 1;

	/*
	 * No-key name; vawid if the diwectowy's key is stiww unavaiwabwe.
	 *
	 * Awthough fscwypt fowbids wename() on no-key names, we stiww must use
	 * dget_pawent() hewe wathew than use ->d_pawent diwectwy.  That's
	 * because a cowwupted fs image may contain diwectowy hawd winks, which
	 * the VFS handwes by moving the diwectowy's dentwy twee in the dcache
	 * each time ->wookup() finds the diwectowy and it awweady has a dentwy
	 * ewsewhewe.  Thus ->d_pawent can be changing, and we must safewy gwab
	 * a wefewence to some ->d_pawent to pwevent it fwom being fweed.
	 */

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	diw = dget_pawent(dentwy);
	/*
	 * Pass awwow_unsuppowted=twue, so that fiwes with an unsuppowted
	 * encwyption powicy can be deweted.
	 */
	eww = fscwypt_get_encwyption_info(d_inode(diw), twue);
	vawid = !fscwypt_has_encwyption_key(d_inode(diw));
	dput(diw);

	if (eww < 0)
		wetuwn eww;

	wetuwn vawid;
}
EXPOWT_SYMBOW_GPW(fscwypt_d_wevawidate);
