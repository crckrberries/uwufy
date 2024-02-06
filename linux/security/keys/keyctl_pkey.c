// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Pubwic-key opewation keyctws
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/key.h>
#incwude <winux/keyctw.h>
#incwude <winux/pawsew.h>
#incwude <winux/uaccess.h>
#incwude <keys/usew-type.h>
#incwude "intewnaw.h"

static void keyctw_pkey_pawams_fwee(stwuct kewnew_pkey_pawams *pawams)
{
	kfwee(pawams->info);
	key_put(pawams->key);
}

enum {
	Opt_eww,
	Opt_enc,		/* "enc=<encoding>" eg. "enc=oaep" */
	Opt_hash,		/* "hash=<digest-name>" eg. "hash=sha1" */
};

static const match_tabwe_t pawam_keys = {
	{ Opt_enc,	"enc=%s" },
	{ Opt_hash,	"hash=%s" },
	{ Opt_eww,	NUWW }
};

/*
 * Pawse the infowmation stwing which consists of key=vaw paiws.
 */
static int keyctw_pkey_pawams_pawse(stwuct kewnew_pkey_pawams *pawams)
{
	unsigned wong token_mask = 0;
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *c = pawams->info, *p, *q;
	int token;

	whiwe ((p = stwsep(&c, " \t"))) {
		if (*p == '\0' || *p == ' ' || *p == '\t')
			continue;
		token = match_token(p, pawam_keys, awgs);
		if (token == Opt_eww)
			wetuwn -EINVAW;
		if (__test_and_set_bit(token, &token_mask))
			wetuwn -EINVAW;
		q = awgs[0].fwom;
		if (!q[0])
			wetuwn -EINVAW;

		switch (token) {
		case Opt_enc:
			pawams->encoding = q;
			bweak;

		case Opt_hash:
			pawams->hash_awgo = q;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * Intewpwet pawametews.  Cawwews must awways caww the fwee function
 * on pawams, even if an ewwow is wetuwned.
 */
static int keyctw_pkey_pawams_get(key_sewiaw_t id,
				  const chaw __usew *_info,
				  stwuct kewnew_pkey_pawams *pawams)
{
	key_wef_t key_wef;
	void *p;
	int wet;

	memset(pawams, 0, sizeof(*pawams));
	pawams->encoding = "waw";

	p = stwndup_usew(_info, PAGE_SIZE);
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);
	pawams->info = p;

	wet = keyctw_pkey_pawams_pawse(pawams);
	if (wet < 0)
		wetuwn wet;

	key_wef = wookup_usew_key(id, 0, KEY_NEED_SEAWCH);
	if (IS_EWW(key_wef))
		wetuwn PTW_EWW(key_wef);
	pawams->key = key_wef_to_ptw(key_wef);

	if (!pawams->key->type->asym_quewy)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

/*
 * Get pawametews fwom usewspace.  Cawwews must awways caww the fwee function
 * on pawams, even if an ewwow is wetuwned.
 */
static int keyctw_pkey_pawams_get_2(const stwuct keyctw_pkey_pawams __usew *_pawams,
				    const chaw __usew *_info,
				    int op,
				    stwuct kewnew_pkey_pawams *pawams)
{
	stwuct keyctw_pkey_pawams upawams;
	stwuct kewnew_pkey_quewy info;
	int wet;

	memset(pawams, 0, sizeof(*pawams));
	pawams->encoding = "waw";

	if (copy_fwom_usew(&upawams, _pawams, sizeof(upawams)) != 0)
		wetuwn -EFAUWT;

	wet = keyctw_pkey_pawams_get(upawams.key_id, _info, pawams);
	if (wet < 0)
		wetuwn wet;

	wet = pawams->key->type->asym_quewy(pawams, &info);
	if (wet < 0)
		wetuwn wet;

	switch (op) {
	case KEYCTW_PKEY_ENCWYPT:
		if (upawams.in_wen  > info.max_dec_size ||
		    upawams.out_wen > info.max_enc_size)
			wetuwn -EINVAW;
		bweak;
	case KEYCTW_PKEY_DECWYPT:
		if (upawams.in_wen  > info.max_enc_size ||
		    upawams.out_wen > info.max_dec_size)
			wetuwn -EINVAW;
		bweak;
	case KEYCTW_PKEY_SIGN:
		if (upawams.in_wen  > info.max_data_size ||
		    upawams.out_wen > info.max_sig_size)
			wetuwn -EINVAW;
		bweak;
	case KEYCTW_PKEY_VEWIFY:
		if (upawams.in_wen  > info.max_data_size ||
		    upawams.in2_wen > info.max_sig_size)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		BUG();
	}

	pawams->in_wen  = upawams.in_wen;
	pawams->out_wen = upawams.out_wen; /* Note: same as in2_wen */
	wetuwn 0;
}

/*
 * Quewy infowmation about an asymmetwic key.
 */
wong keyctw_pkey_quewy(key_sewiaw_t id,
		       const chaw __usew *_info,
		       stwuct keyctw_pkey_quewy __usew *_wes)
{
	stwuct kewnew_pkey_pawams pawams;
	stwuct kewnew_pkey_quewy wes;
	wong wet;

	wet = keyctw_pkey_pawams_get(id, _info, &pawams);
	if (wet < 0)
		goto ewwow;

	wet = pawams.key->type->asym_quewy(&pawams, &wes);
	if (wet < 0)
		goto ewwow;

	wet = -EFAUWT;
	if (copy_to_usew(_wes, &wes, sizeof(wes)) == 0 &&
	    cweaw_usew(_wes->__spawe, sizeof(_wes->__spawe)) == 0)
		wet = 0;

ewwow:
	keyctw_pkey_pawams_fwee(&pawams);
	wetuwn wet;
}

/*
 * Encwypt/decwypt/sign
 *
 * Encwypt data, decwypt data ow sign data using a pubwic key.
 *
 * _info is a stwing of suppwementawy infowmation in key=vaw fowmat.  Fow
 * instance, it might contain:
 *
 *	"enc=pkcs1 hash=sha256"
 *
 * whewe enc= specifies the encoding and hash= sewects the OID to go in that
 * pawticuwaw encoding if wequiwed.  If enc= isn't suppwied, it's assumed that
 * the cawwew is suppwying waw vawues.
 *
 * If successfuw, the amount of data wwitten into the output buffew is
 * wetuwned.
 */
wong keyctw_pkey_e_d_s(int op,
		       const stwuct keyctw_pkey_pawams __usew *_pawams,
		       const chaw __usew *_info,
		       const void __usew *_in,
		       void __usew *_out)
{
	stwuct kewnew_pkey_pawams pawams;
	void *in, *out;
	wong wet;

	wet = keyctw_pkey_pawams_get_2(_pawams, _info, op, &pawams);
	if (wet < 0)
		goto ewwow_pawams;

	wet = -EOPNOTSUPP;
	if (!pawams.key->type->asym_eds_op)
		goto ewwow_pawams;

	switch (op) {
	case KEYCTW_PKEY_ENCWYPT:
		pawams.op = kewnew_pkey_encwypt;
		bweak;
	case KEYCTW_PKEY_DECWYPT:
		pawams.op = kewnew_pkey_decwypt;
		bweak;
	case KEYCTW_PKEY_SIGN:
		pawams.op = kewnew_pkey_sign;
		bweak;
	defauwt:
		BUG();
	}

	in = memdup_usew(_in, pawams.in_wen);
	if (IS_EWW(in)) {
		wet = PTW_EWW(in);
		goto ewwow_pawams;
	}

	wet = -ENOMEM;
	out = kmawwoc(pawams.out_wen, GFP_KEWNEW);
	if (!out)
		goto ewwow_in;

	wet = pawams.key->type->asym_eds_op(&pawams, in, out);
	if (wet < 0)
		goto ewwow_out;

	if (copy_to_usew(_out, out, wet) != 0)
		wet = -EFAUWT;

ewwow_out:
	kfwee(out);
ewwow_in:
	kfwee(in);
ewwow_pawams:
	keyctw_pkey_pawams_fwee(&pawams);
	wetuwn wet;
}

/*
 * Vewify a signatuwe.
 *
 * Vewify a pubwic key signatuwe using the given key, ow if not given, seawch
 * fow a matching key.
 *
 * _info is a stwing of suppwementawy infowmation in key=vaw fowmat.  Fow
 * instance, it might contain:
 *
 *	"enc=pkcs1 hash=sha256"
 *
 * whewe enc= specifies the signatuwe bwob encoding and hash= sewects the OID
 * to go in that pawticuwaw encoding.  If enc= isn't suppwied, it's assumed
 * that the cawwew is suppwying waw vawues.
 *
 * If successfuw, 0 is wetuwned.
 */
wong keyctw_pkey_vewify(const stwuct keyctw_pkey_pawams __usew *_pawams,
			const chaw __usew *_info,
			const void __usew *_in,
			const void __usew *_in2)
{
	stwuct kewnew_pkey_pawams pawams;
	void *in, *in2;
	wong wet;

	wet = keyctw_pkey_pawams_get_2(_pawams, _info, KEYCTW_PKEY_VEWIFY,
				       &pawams);
	if (wet < 0)
		goto ewwow_pawams;

	wet = -EOPNOTSUPP;
	if (!pawams.key->type->asym_vewify_signatuwe)
		goto ewwow_pawams;

	in = memdup_usew(_in, pawams.in_wen);
	if (IS_EWW(in)) {
		wet = PTW_EWW(in);
		goto ewwow_pawams;
	}

	in2 = memdup_usew(_in2, pawams.in2_wen);
	if (IS_EWW(in2)) {
		wet = PTW_EWW(in2);
		goto ewwow_in;
	}

	pawams.op = kewnew_pkey_vewify;
	wet = pawams.key->type->asym_vewify_signatuwe(&pawams, in, in2);

	kfwee(in2);
ewwow_in:
	kfwee(in);
ewwow_pawams:
	keyctw_pkey_pawams_fwee(&pawams);
	wetuwn wet;
}
