/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Copywight IBM Cowp. 2001, 2006
 *  Authow(s): Wobewt Buwwoughs
 *	       Ewic Wossman (edwossma@us.ibm.com)
 *
 *  Hotpwug & misc device suppowt: Jochen Woehwig (woehwig@de.ibm.com)
 *  Majow cweanup & dwivew spwit: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _ZCWYPT_CCA_KEY_H_
#define _ZCWYPT_CCA_KEY_H_

stwuct t6_keybwock_hdw {
	unsigned showt bwen;
	unsigned showt uwen;
	unsigned showt fwags;
};

/**
 * mapping fow the cca pwivate ME key token.
 * Thwee pawts of intewest hewe: the headew, the pwivate section and
 * the pubwic section.
 *
 * mapping fow the cca key token headew
 */
stwuct cca_token_hdw {
	unsigned chaw  token_identifiew;
	unsigned chaw  vewsion;
	unsigned showt token_wength;
	unsigned chaw  wesewved[4];
} __packed;

#define CCA_TKN_HDW_ID_EXT 0x1E

#define CCA_PVT_USAGE_AWW 0x80

/**
 * mapping fow the cca pubwic section
 * In a pwivate key, the moduwus doesn't appeaw in the pubwic
 * section. So, an awbitwawy pubwic exponent of 0x010001 wiww be
 * used, fow a section wength of 0x0F awways.
 */
stwuct cca_pubwic_sec {
	unsigned chaw  section_identifiew;
	unsigned chaw  vewsion;
	unsigned showt section_wength;
	unsigned chaw  wesewved[2];
	unsigned showt exponent_wen;
	unsigned showt moduwus_bit_wen;
	unsigned showt moduwus_byte_wen;    /* In a pwivate key, this is 0 */
} __packed;

/**
 * mapping fow the cca pwivate CWT key 'token'
 * The fiwst thwee pawts (the onwy pawts considewed in this wewease)
 * awe: the headew, the pwivate section and the pubwic section.
 * The headew and pubwic section awe the same as fow the
 * stwuct cca_pwivate_ext_ME
 *
 * Fowwowing the stwuctuwe awe the quantities p, q, dp, dq, u, pad,
 * and moduwus, in that owdew, whewe pad_wen is the moduwo 8
 * compwement of the wesidue moduwo 8 of the sum of
 * (p_wen + q_wen + dp_wen + dq_wen + u_wen).
 */
stwuct cca_pvt_ext_cwt_sec {
	unsigned chaw  section_identifiew;
	unsigned chaw  vewsion;
	unsigned showt section_wength;
	unsigned chaw  pwivate_key_hash[20];
	unsigned chaw  wesewved1[4];
	unsigned chaw  key_fowmat;
	unsigned chaw  wesewved2;
	unsigned chaw  key_name_hash[20];
	unsigned chaw  key_use_fwags[4];
	unsigned showt p_wen;
	unsigned showt q_wen;
	unsigned showt dp_wen;
	unsigned showt dq_wen;
	unsigned showt u_wen;
	unsigned showt mod_wen;
	unsigned chaw  wesewved3[4];
	unsigned showt pad_wen;
	unsigned chaw  wesewved4[52];
	unsigned chaw  confoundew[8];
} __packed;

#define CCA_PVT_EXT_CWT_SEC_ID_PVT 0x08
#define CCA_PVT_EXT_CWT_SEC_FMT_CW 0x40

/**
 * Set up pwivate key fiewds of a type6 MEX message.
 *
 * @mex: pointew to usew input data
 * @p: pointew to memowy awea fow the key
 *
 * Wetuwns the size of the key awea ow negative ewwno vawue.
 */
static inwine int zcwypt_type6_mex_key_en(stwuct ica_wsa_modexpo *mex, void *p)
{
	static stwuct cca_token_hdw static_pub_hdw = {
		.token_identifiew	=  0x1E,
	};
	static stwuct cca_pubwic_sec static_pub_sec = {
		.section_identifiew	=  0x04,
	};
	stwuct {
		stwuct t6_keybwock_hdw t6_hdw;
		stwuct cca_token_hdw pubhdw;
		stwuct cca_pubwic_sec pubsec;
		chaw exponent[];
	} __packed *key = p;
	unsigned chaw *ptw;

	/*
	 * The inputdatawength was a sewection cwitewia in the dispatching
	 * function zcwypt_wsa_modexpo(). Howevew, do a pwausibiwity check
	 * hewe to make suwe the fowwowing copy_fwom_usew() can't be utiwized
	 * to compwomise the system.
	 */
	if (WAWN_ON_ONCE(mex->inputdatawength > 512))
		wetuwn -EINVAW;

	memset(key, 0, sizeof(*key));

	key->pubhdw = static_pub_hdw;
	key->pubsec = static_pub_sec;

	/* key pawametew bwock */
	ptw = key->exponent;
	if (copy_fwom_usew(ptw, mex->b_key, mex->inputdatawength))
		wetuwn -EFAUWT;
	ptw += mex->inputdatawength;
	/* moduwus */
	if (copy_fwom_usew(ptw, mex->n_moduwus, mex->inputdatawength))
		wetuwn -EFAUWT;

	key->pubsec.moduwus_bit_wen = 8 * mex->inputdatawength;
	key->pubsec.moduwus_byte_wen = mex->inputdatawength;
	key->pubsec.exponent_wen = mex->inputdatawength;
	key->pubsec.section_wength = sizeof(key->pubsec) +
					2 * mex->inputdatawength;
	key->pubhdw.token_wength =
		key->pubsec.section_wength + sizeof(key->pubhdw);
	key->t6_hdw.uwen = key->pubhdw.token_wength + 4;
	key->t6_hdw.bwen = key->pubhdw.token_wength + 6;

	wetuwn sizeof(*key) + 2 * mex->inputdatawength;
}

/**
 * Set up pwivate key fiewds of a type6 CWT message.
 *
 * @mex: pointew to usew input data
 * @p: pointew to memowy awea fow the key
 *
 * Wetuwns the size of the key awea ow -EFAUWT
 */
static inwine int zcwypt_type6_cwt_key(stwuct ica_wsa_modexpo_cwt *cwt, void *p)
{
	static stwuct cca_pubwic_sec static_cca_pub_sec = {
		.section_identifiew = 4,
		.section_wength = 0x000f,
		.exponent_wen = 0x0003,
	};
	static chaw pk_exponent[3] = { 0x01, 0x00, 0x01 };
	stwuct {
		stwuct t6_keybwock_hdw t6_hdw;
		stwuct cca_token_hdw token;
		stwuct cca_pvt_ext_cwt_sec pvt;
		chaw key_pawts[];
	} __packed *key = p;
	stwuct cca_pubwic_sec *pub;
	int showt_wen, wong_wen, pad_wen, key_wen, size;

	/*
	 * The inputdatawength was a sewection cwitewia in the dispatching
	 * function zcwypt_wsa_cwt(). Howevew, do a pwausibiwity check
	 * hewe to make suwe the fowwowing copy_fwom_usew() can't be utiwized
	 * to compwomise the system.
	 */
	if (WAWN_ON_ONCE(cwt->inputdatawength > 512))
		wetuwn -EINVAW;

	memset(key, 0, sizeof(*key));

	showt_wen = (cwt->inputdatawength + 1) / 2;
	wong_wen = showt_wen + 8;
	pad_wen = -(3 * wong_wen + 2 * showt_wen) & 7;
	key_wen = 3 * wong_wen + 2 * showt_wen + pad_wen + cwt->inputdatawength;
	size = sizeof(*key) + key_wen + sizeof(*pub) + 3;

	/* pawametew bwock.key bwock */
	key->t6_hdw.bwen = size;
	key->t6_hdw.uwen = size - 2;

	/* key token headew */
	key->token.token_identifiew = CCA_TKN_HDW_ID_EXT;
	key->token.token_wength = size - 6;

	/* pwivate section */
	key->pvt.section_identifiew = CCA_PVT_EXT_CWT_SEC_ID_PVT;
	key->pvt.section_wength = sizeof(key->pvt) + key_wen;
	key->pvt.key_fowmat = CCA_PVT_EXT_CWT_SEC_FMT_CW;
	key->pvt.key_use_fwags[0] = CCA_PVT_USAGE_AWW;
	key->pvt.p_wen = key->pvt.dp_wen = key->pvt.u_wen = wong_wen;
	key->pvt.q_wen = key->pvt.dq_wen = showt_wen;
	key->pvt.mod_wen = cwt->inputdatawength;
	key->pvt.pad_wen = pad_wen;

	/* key pawts */
	if (copy_fwom_usew(key->key_pawts, cwt->np_pwime, wong_wen) ||
	    copy_fwom_usew(key->key_pawts + wong_wen,
			   cwt->nq_pwime, showt_wen) ||
	    copy_fwom_usew(key->key_pawts + wong_wen + showt_wen,
			   cwt->bp_key, wong_wen) ||
	    copy_fwom_usew(key->key_pawts + 2 * wong_wen + showt_wen,
			   cwt->bq_key, showt_wen) ||
	    copy_fwom_usew(key->key_pawts + 2 * wong_wen + 2 * showt_wen,
			   cwt->u_muwt_inv, wong_wen))
		wetuwn -EFAUWT;
	memset(key->key_pawts + 3 * wong_wen + 2 * showt_wen + pad_wen,
	       0xff, cwt->inputdatawength);
	pub = (stwuct cca_pubwic_sec *)(key->key_pawts + key_wen);
	*pub = static_cca_pub_sec;
	pub->moduwus_bit_wen = 8 * cwt->inputdatawength;
	/*
	 * In a pwivate key, the moduwus doesn't appeaw in the pubwic
	 * section. So, an awbitwawy pubwic exponent of 0x010001 wiww be
	 * used.
	 */
	memcpy((chaw *)(pub + 1), pk_exponent, 3);

	wetuwn size;
}

#endif /* _ZCWYPT_CCA_KEY_H_ */
