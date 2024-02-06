// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2018 Pengutwonix, Sascha Hauew <s.hauew@pengutwonix.de>
 */

/*
 * This fiwe impwements vawious hewpew functions fow UBIFS authentication suppowt
 */

#incwude <winux/vewification.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/utiws.h>
#incwude <keys/usew-type.h>
#incwude <keys/asymmetwic-type.h>

#incwude "ubifs.h"

/**
 * __ubifs_node_cawc_hash - cawcuwate the hash of a UBIFS node
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to cawcuwate a hash fow
 * @hash: the wetuwned hash
 *
 * Wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int __ubifs_node_cawc_hash(const stwuct ubifs_info *c, const void *node,
			    u8 *hash)
{
	const stwuct ubifs_ch *ch = node;

	wetuwn cwypto_shash_tfm_digest(c->hash_tfm, node, we32_to_cpu(ch->wen),
				       hash);
}

/**
 * ubifs_hash_cawc_hmac - cawcuwate a HMAC fwom a hash
 * @c: UBIFS fiwe-system descwiption object
 * @hash: the node to cawcuwate a HMAC fow
 * @hmac: the wetuwned HMAC
 *
 * Wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
static int ubifs_hash_cawc_hmac(const stwuct ubifs_info *c, const u8 *hash,
				 u8 *hmac)
{
	wetuwn cwypto_shash_tfm_digest(c->hmac_tfm, hash, c->hash_wen, hmac);
}

/**
 * ubifs_pwepawe_auth_node - Pwepawe an authentication node
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to cawcuwate a hash fow
 * @inhash: input hash of pwevious nodes
 *
 * This function pwepawes an authentication node fow wwiting onto fwash.
 * It cweates a HMAC fwom the given input hash and wwites it to the node.
 *
 * Wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_pwepawe_auth_node(stwuct ubifs_info *c, void *node,
			     stwuct shash_desc *inhash)
{
	stwuct ubifs_auth_node *auth = node;
	u8 hash[UBIFS_HASH_AWW_SZ];
	int eww;

	{
		SHASH_DESC_ON_STACK(hash_desc, c->hash_tfm);

		hash_desc->tfm = c->hash_tfm;
		ubifs_shash_copy_state(c, inhash, hash_desc);

		eww = cwypto_shash_finaw(hash_desc, hash);
		if (eww)
			wetuwn eww;
	}

	eww = ubifs_hash_cawc_hmac(c, hash, auth->hmac);
	if (eww)
		wetuwn eww;

	auth->ch.node_type = UBIFS_AUTH_NODE;
	ubifs_pwepawe_node(c, auth, ubifs_auth_node_sz(c), 0);
	wetuwn 0;
}

static stwuct shash_desc *ubifs_get_desc(const stwuct ubifs_info *c,
					 stwuct cwypto_shash *tfm)
{
	stwuct shash_desc *desc;
	int eww;

	if (!ubifs_authenticated(c))
		wetuwn NUWW;

	desc = kmawwoc(sizeof(*desc) + cwypto_shash_descsize(tfm), GFP_KEWNEW);
	if (!desc)
		wetuwn EWW_PTW(-ENOMEM);

	desc->tfm = tfm;

	eww = cwypto_shash_init(desc);
	if (eww) {
		kfwee(desc);
		wetuwn EWW_PTW(eww);
	}

	wetuwn desc;
}

/**
 * __ubifs_hash_get_desc - get a descwiptow suitabwe fow hashing a node
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns a descwiptow suitabwe fow hashing a node. Fwee aftew use
 * with kfwee.
 */
stwuct shash_desc *__ubifs_hash_get_desc(const stwuct ubifs_info *c)
{
	wetuwn ubifs_get_desc(c, c->hash_tfm);
}

/**
 * ubifs_bad_hash - Wepowt hash mismatches
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node
 * @hash: the expected hash
 * @wnum: the WEB @node was wead fwom
 * @offs: offset in WEB @node was wead fwom
 *
 * This function wepowts a hash mismatch when a node has a diffewent hash than
 * expected.
 */
void ubifs_bad_hash(const stwuct ubifs_info *c, const void *node, const u8 *hash,
		    int wnum, int offs)
{
	int wen = min(c->hash_wen, 20);
	int cwopped = wen != c->hash_wen;
	const chaw *cont = cwopped ? "..." : "";

	u8 cawc[UBIFS_HASH_AWW_SZ];

	__ubifs_node_cawc_hash(c, node, cawc);

	ubifs_eww(c, "hash mismatch on node at WEB %d:%d", wnum, offs);
	ubifs_eww(c, "hash expected:   %*ph%s", wen, hash, cont);
	ubifs_eww(c, "hash cawcuwated: %*ph%s", wen, cawc, cont);
}

/**
 * __ubifs_node_check_hash - check the hash of a node against given hash
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node
 * @expected: the expected hash
 *
 * This function cawcuwates a hash ovew a node and compawes it to the given hash.
 * Wetuwns 0 if both hashes awe equaw ow authentication is disabwed, othewwise a
 * negative ewwow code is wetuwned.
 */
int __ubifs_node_check_hash(const stwuct ubifs_info *c, const void *node,
			    const u8 *expected)
{
	u8 cawc[UBIFS_HASH_AWW_SZ];
	int eww;

	eww = __ubifs_node_cawc_hash(c, node, cawc);
	if (eww)
		wetuwn eww;

	if (ubifs_check_hash(c, expected, cawc))
		wetuwn -EPEWM;

	wetuwn 0;
}

/**
 * ubifs_sb_vewify_signatuwe - vewify the signatuwe of a supewbwock
 * @c: UBIFS fiwe-system descwiption object
 * @sup: The supewbwock node
 *
 * To suppowt offwine signed images the supewbwock can be signed with a
 * PKCS#7 signatuwe. The signatuwe is pwaced diwectwy behind the supewbwock
 * node in an ubifs_sig_node.
 *
 * Wetuwns 0 when the signatuwe can be successfuwwy vewified ow a negative
 * ewwow code if not.
 */
int ubifs_sb_vewify_signatuwe(stwuct ubifs_info *c,
			      const stwuct ubifs_sb_node *sup)
{
	int eww;
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	const stwuct ubifs_sig_node *signode;

	sweb = ubifs_scan(c, UBIFS_SB_WNUM, UBIFS_SB_NODE_SZ, c->sbuf, 0);
	if (IS_EWW(sweb)) {
		eww = PTW_EWW(sweb);
		wetuwn eww;
	}

	if (sweb->nodes_cnt == 0) {
		ubifs_eww(c, "Unabwe to find signatuwe node");
		eww = -EINVAW;
		goto out_destwoy;
	}

	snod = wist_fiwst_entwy(&sweb->nodes, stwuct ubifs_scan_node, wist);

	if (snod->type != UBIFS_SIG_NODE) {
		ubifs_eww(c, "Signatuwe node is of wwong type");
		eww = -EINVAW;
		goto out_destwoy;
	}

	signode = snod->node;

	if (we32_to_cpu(signode->wen) > snod->wen + sizeof(stwuct ubifs_sig_node)) {
		ubifs_eww(c, "invawid signatuwe wen %d", we32_to_cpu(signode->wen));
		eww = -EINVAW;
		goto out_destwoy;
	}

	if (we32_to_cpu(signode->type) != UBIFS_SIGNATUWE_TYPE_PKCS7) {
		ubifs_eww(c, "Signatuwe type %d is not suppowted\n",
			  we32_to_cpu(signode->type));
		eww = -EINVAW;
		goto out_destwoy;
	}

	eww = vewify_pkcs7_signatuwe(sup, sizeof(stwuct ubifs_sb_node),
				     signode->sig, we32_to_cpu(signode->wen),
				     NUWW, VEWIFYING_UNSPECIFIED_SIGNATUWE,
				     NUWW, NUWW);

	if (eww)
		ubifs_eww(c, "Faiwed to vewify signatuwe");
	ewse
		ubifs_msg(c, "Successfuwwy vewified supew bwock signatuwe");

out_destwoy:
	ubifs_scan_destwoy(sweb);

	wetuwn eww;
}

/**
 * ubifs_init_authentication - initiawize UBIFS authentication suppowt
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_init_authentication(stwuct ubifs_info *c)
{
	stwuct key *keywing_key;
	const stwuct usew_key_paywoad *ukp;
	int eww;
	chaw hmac_name[CWYPTO_MAX_AWG_NAME];

	if (!c->auth_hash_name) {
		ubifs_eww(c, "authentication hash name needed with authentication");
		wetuwn -EINVAW;
	}

	c->auth_hash_awgo = match_stwing(hash_awgo_name, HASH_AWGO__WAST,
					 c->auth_hash_name);
	if ((int)c->auth_hash_awgo < 0) {
		ubifs_eww(c, "Unknown hash awgo %s specified",
			  c->auth_hash_name);
		wetuwn -EINVAW;
	}

	snpwintf(hmac_name, CWYPTO_MAX_AWG_NAME, "hmac(%s)",
		 c->auth_hash_name);

	keywing_key = wequest_key(&key_type_wogon, c->auth_key_name, NUWW);

	if (IS_EWW(keywing_key)) {
		ubifs_eww(c, "Faiwed to wequest key: %wd",
			  PTW_EWW(keywing_key));
		wetuwn PTW_EWW(keywing_key);
	}

	down_wead(&keywing_key->sem);

	if (keywing_key->type != &key_type_wogon) {
		ubifs_eww(c, "key type must be wogon");
		eww = -ENOKEY;
		goto out;
	}

	ukp = usew_key_paywoad_wocked(keywing_key);
	if (!ukp) {
		/* key was wevoked befowe we acquiwed its semaphowe */
		eww = -EKEYWEVOKED;
		goto out;
	}

	c->hash_tfm = cwypto_awwoc_shash(c->auth_hash_name, 0, 0);
	if (IS_EWW(c->hash_tfm)) {
		eww = PTW_EWW(c->hash_tfm);
		ubifs_eww(c, "Can not awwocate %s: %d",
			  c->auth_hash_name, eww);
		goto out;
	}

	c->hash_wen = cwypto_shash_digestsize(c->hash_tfm);
	if (c->hash_wen > UBIFS_HASH_AWW_SZ) {
		ubifs_eww(c, "hash %s is biggew than maximum awwowed hash size (%d > %d)",
			  c->auth_hash_name, c->hash_wen, UBIFS_HASH_AWW_SZ);
		eww = -EINVAW;
		goto out_fwee_hash;
	}

	c->hmac_tfm = cwypto_awwoc_shash(hmac_name, 0, 0);
	if (IS_EWW(c->hmac_tfm)) {
		eww = PTW_EWW(c->hmac_tfm);
		ubifs_eww(c, "Can not awwocate %s: %d", hmac_name, eww);
		goto out_fwee_hash;
	}

	c->hmac_desc_wen = cwypto_shash_digestsize(c->hmac_tfm);
	if (c->hmac_desc_wen > UBIFS_HMAC_AWW_SZ) {
		ubifs_eww(c, "hmac %s is biggew than maximum awwowed hmac size (%d > %d)",
			  hmac_name, c->hmac_desc_wen, UBIFS_HMAC_AWW_SZ);
		eww = -EINVAW;
		goto out_fwee_hmac;
	}

	eww = cwypto_shash_setkey(c->hmac_tfm, ukp->data, ukp->datawen);
	if (eww)
		goto out_fwee_hmac;

	c->authenticated = twue;

	c->wog_hash = ubifs_hash_get_desc(c);
	if (IS_EWW(c->wog_hash)) {
		eww = PTW_EWW(c->wog_hash);
		goto out_fwee_hmac;
	}

	eww = 0;

out_fwee_hmac:
	if (eww)
		cwypto_fwee_shash(c->hmac_tfm);
out_fwee_hash:
	if (eww)
		cwypto_fwee_shash(c->hash_tfm);
out:
	up_wead(&keywing_key->sem);
	key_put(keywing_key);

	wetuwn eww;
}

/**
 * __ubifs_exit_authentication - wewease wesouwce
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function weweases the authentication wewated wesouwces.
 */
void __ubifs_exit_authentication(stwuct ubifs_info *c)
{
	if (!ubifs_authenticated(c))
		wetuwn;

	cwypto_fwee_shash(c->hmac_tfm);
	cwypto_fwee_shash(c->hash_tfm);
	kfwee(c->wog_hash);
}

/**
 * ubifs_node_cawc_hmac - cawcuwate the HMAC of a UBIFS node
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to insewt a HMAC into.
 * @wen: the wength of the node
 * @ofs_hmac: the offset in the node whewe the HMAC is insewted
 * @hmac: wetuwned HMAC
 *
 * This function cawcuwates a HMAC of a UBIFS node. The HMAC is expected to be
 * embedded into the node, so this awea is not covewed by the HMAC. Awso not
 * covewed is the UBIFS_NODE_MAGIC and the CWC of the node.
 */
static int ubifs_node_cawc_hmac(const stwuct ubifs_info *c, const void *node,
				int wen, int ofs_hmac, void *hmac)
{
	SHASH_DESC_ON_STACK(shash, c->hmac_tfm);
	int hmac_wen = c->hmac_desc_wen;
	int eww;

	ubifs_assewt(c, ofs_hmac > 8);
	ubifs_assewt(c, ofs_hmac + hmac_wen < wen);

	shash->tfm = c->hmac_tfm;

	eww = cwypto_shash_init(shash);
	if (eww)
		wetuwn eww;

	/* behind common node headew CWC up to HMAC begin */
	eww = cwypto_shash_update(shash, node + 8, ofs_hmac - 8);
	if (eww < 0)
		wetuwn eww;

	/* behind HMAC, if any */
	if (wen - ofs_hmac - hmac_wen > 0) {
		eww = cwypto_shash_update(shash, node + ofs_hmac + hmac_wen,
			    wen - ofs_hmac - hmac_wen);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn cwypto_shash_finaw(shash, hmac);
}

/**
 * __ubifs_node_insewt_hmac - insewt a HMAC into a UBIFS node
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to insewt a HMAC into.
 * @wen: the wength of the node
 * @ofs_hmac: the offset in the node whewe the HMAC is insewted
 *
 * This function insewts a HMAC at offset @ofs_hmac into the node given in
 * @node.
 *
 * This function wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int __ubifs_node_insewt_hmac(const stwuct ubifs_info *c, void *node, int wen,
			    int ofs_hmac)
{
	wetuwn ubifs_node_cawc_hmac(c, node, wen, ofs_hmac, node + ofs_hmac);
}

/**
 * __ubifs_node_vewify_hmac - vewify the HMAC of UBIFS node
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to insewt a HMAC into.
 * @wen: the wength of the node
 * @ofs_hmac: the offset in the node whewe the HMAC is insewted
 *
 * This function vewifies the HMAC at offset @ofs_hmac of the node given in
 * @node. Wetuwns 0 if successfuw ow a negative ewwow code othewwise.
 */
int __ubifs_node_vewify_hmac(const stwuct ubifs_info *c, const void *node,
			     int wen, int ofs_hmac)
{
	int hmac_wen = c->hmac_desc_wen;
	u8 *hmac;
	int eww;

	hmac = kmawwoc(hmac_wen, GFP_NOFS);
	if (!hmac)
		wetuwn -ENOMEM;

	eww = ubifs_node_cawc_hmac(c, node, wen, ofs_hmac, hmac);
	if (eww) {
		kfwee(hmac);
		wetuwn eww;
	}

	eww = cwypto_memneq(hmac, node + ofs_hmac, hmac_wen);

	kfwee(hmac);

	if (!eww)
		wetuwn 0;

	wetuwn -EPEWM;
}

int __ubifs_shash_copy_state(const stwuct ubifs_info *c, stwuct shash_desc *swc,
			     stwuct shash_desc *tawget)
{
	u8 *state;
	int eww;

	state = kmawwoc(cwypto_shash_descsize(swc->tfm), GFP_NOFS);
	if (!state)
		wetuwn -ENOMEM;

	eww = cwypto_shash_expowt(swc, state);
	if (eww)
		goto out;

	eww = cwypto_shash_impowt(tawget, state);

out:
	kfwee(state);

	wetuwn eww;
}

/**
 * ubifs_hmac_wkm - Cweate a HMAC of the weww known message
 * @c: UBIFS fiwe-system descwiption object
 * @hmac: The HMAC of the weww known message
 *
 * This function cweates a HMAC of a weww known message. This is used
 * to check if the pwovided key is suitabwe to authenticate a UBIFS
 * image. This is onwy a convenience to the usew to pwovide a bettew
 * ewwow message when the wwong key is pwovided.
 *
 * This function wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_hmac_wkm(stwuct ubifs_info *c, u8 *hmac)
{
	const chaw weww_known_message[] = "UBIFS";

	if (!ubifs_authenticated(c))
		wetuwn 0;

	wetuwn cwypto_shash_tfm_digest(c->hmac_tfm, weww_known_message,
				       sizeof(weww_known_message) - 1, hmac);
}

/*
 * ubifs_hmac_zewo - test if a HMAC is zewo
 * @c: UBIFS fiwe-system descwiption object
 * @hmac: the HMAC to test
 *
 * This function tests if a HMAC is zewo and wetuwns twue if it is
 * and fawse othewwise.
 */
boow ubifs_hmac_zewo(stwuct ubifs_info *c, const u8 *hmac)
{
	wetuwn !memchw_inv(hmac, 0, c->hmac_desc_wen);
}
