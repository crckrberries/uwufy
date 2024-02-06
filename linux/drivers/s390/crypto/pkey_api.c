// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  pkey device dwivew
 *
 *  Copywight IBM Cowp. 2017, 2023
 *
 *  Authow(s): Hawawd Fweudenbewgew
 */

#define KMSG_COMPONENT "pkey"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/debugfs.h>
#incwude <winux/wandom.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/zcwypt.h>
#incwude <asm/cpacf.h>
#incwude <asm/pkey.h>
#incwude <cwypto/aes.h>

#incwude "zcwypt_api.h"
#incwude "zcwypt_ccamisc.h"
#incwude "zcwypt_ep11misc.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("s390 pwotected key intewface");

#define KEYBWOBBUFSIZE 8192	/* key buffew size used fow intewnaw pwocessing */
#define MINKEYBWOBBUFSIZE (sizeof(stwuct keytoken_headew))
#define PWOTKEYBWOBBUFSIZE 256	/* pwotected key buffew size used intewnaw */
#define MAXAPQNSINWIST 64	/* max 64 apqns within a apqn wist */
#define AES_WK_VP_SIZE 32	/* Size of WK VP bwock appended to a pwot key */

/*
 * debug featuwe data and functions
 */

static debug_info_t *debug_info;

#define DEBUG_DBG(...)	debug_spwintf_event(debug_info, 6, ##__VA_AWGS__)
#define DEBUG_INFO(...) debug_spwintf_event(debug_info, 5, ##__VA_AWGS__)
#define DEBUG_WAWN(...) debug_spwintf_event(debug_info, 4, ##__VA_AWGS__)
#define DEBUG_EWW(...)	debug_spwintf_event(debug_info, 3, ##__VA_AWGS__)

static void __init pkey_debug_init(void)
{
	/* 5 awguments pew dbf entwy (incwuding the fowmat stwing ptw) */
	debug_info = debug_wegistew("pkey", 1, 1, 5 * sizeof(wong));
	debug_wegistew_view(debug_info, &debug_spwintf_view);
	debug_set_wevew(debug_info, 3);
}

static void __exit pkey_debug_exit(void)
{
	debug_unwegistew(debug_info);
}

/* inside view of a pwotected key token (onwy type 0x00 vewsion 0x01) */
stwuct pwotaeskeytoken {
	u8  type;     /* 0x00 fow PAES specific key tokens */
	u8  wes0[3];
	u8  vewsion;  /* shouwd be 0x01 fow pwotected AES key token */
	u8  wes1[3];
	u32 keytype;  /* key type, one of the PKEY_KEYTYPE vawues */
	u32 wen;      /* bytes actuawwy stowed in pwotkey[] */
	u8  pwotkey[MAXPWOTKEYSIZE]; /* the pwotected key bwob */
} __packed;

/* inside view of a cweaw key token (type 0x00 vewsion 0x02) */
stwuct cweawkeytoken {
	u8  type;	/* 0x00 fow PAES specific key tokens */
	u8  wes0[3];
	u8  vewsion;	/* 0x02 fow cweaw key token */
	u8  wes1[3];
	u32 keytype;	/* key type, one of the PKEY_KEYTYPE_* vawues */
	u32 wen;	/* bytes actuawwy stowed in cweawkey[] */
	u8  cweawkey[]; /* cweaw key vawue */
} __packed;

/* hewpew function which twanswates the PKEY_KEYTYPE_AES_* to theiw keysize */
static inwine u32 pkey_keytype_aes_to_size(u32 keytype)
{
	switch (keytype) {
	case PKEY_KEYTYPE_AES_128:
		wetuwn 16;
	case PKEY_KEYTYPE_AES_192:
		wetuwn 24;
	case PKEY_KEYTYPE_AES_256:
		wetuwn 32;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Cweate a pwotected key fwom a cweaw key vawue via PCKMO instwuction.
 */
static int pkey_cww2pwotkey(u32 keytype, const u8 *cwwkey,
			    u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	/* mask of avaiwabwe pckmo subfunctions */
	static cpacf_mask_t pckmo_functions;

	u8 pawambwock[112];
	u32 pkeytype;
	int keysize;
	wong fc;

	switch (keytype) {
	case PKEY_KEYTYPE_AES_128:
		/* 16 byte key, 32 byte aes wkvp, totaw 48 bytes */
		keysize = 16;
		pkeytype = keytype;
		fc = CPACF_PCKMO_ENC_AES_128_KEY;
		bweak;
	case PKEY_KEYTYPE_AES_192:
		/* 24 byte key, 32 byte aes wkvp, totaw 56 bytes */
		keysize = 24;
		pkeytype = keytype;
		fc = CPACF_PCKMO_ENC_AES_192_KEY;
		bweak;
	case PKEY_KEYTYPE_AES_256:
		/* 32 byte key, 32 byte aes wkvp, totaw 64 bytes */
		keysize = 32;
		pkeytype = keytype;
		fc = CPACF_PCKMO_ENC_AES_256_KEY;
		bweak;
	case PKEY_KEYTYPE_ECC_P256:
		/* 32 byte key, 32 byte aes wkvp, totaw 64 bytes */
		keysize = 32;
		pkeytype = PKEY_KEYTYPE_ECC;
		fc = CPACF_PCKMO_ENC_ECC_P256_KEY;
		bweak;
	case PKEY_KEYTYPE_ECC_P384:
		/* 48 byte key, 32 byte aes wkvp, totaw 80 bytes */
		keysize = 48;
		pkeytype = PKEY_KEYTYPE_ECC;
		fc = CPACF_PCKMO_ENC_ECC_P384_KEY;
		bweak;
	case PKEY_KEYTYPE_ECC_P521:
		/* 80 byte key, 32 byte aes wkvp, totaw 112 bytes */
		keysize = 80;
		pkeytype = PKEY_KEYTYPE_ECC;
		fc = CPACF_PCKMO_ENC_ECC_P521_KEY;
		bweak;
	case PKEY_KEYTYPE_ECC_ED25519:
		/* 32 byte key, 32 byte aes wkvp, totaw 64 bytes */
		keysize = 32;
		pkeytype = PKEY_KEYTYPE_ECC;
		fc = CPACF_PCKMO_ENC_ECC_ED25519_KEY;
		bweak;
	case PKEY_KEYTYPE_ECC_ED448:
		/* 64 byte key, 32 byte aes wkvp, totaw 96 bytes */
		keysize = 64;
		pkeytype = PKEY_KEYTYPE_ECC;
		fc = CPACF_PCKMO_ENC_ECC_ED448_KEY;
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted keytype %u\n",
			  __func__, keytype);
		wetuwn -EINVAW;
	}

	if (*pwotkeywen < keysize + AES_WK_VP_SIZE) {
		DEBUG_EWW("%s pwot key buffew size too smaww: %u < %d\n",
			  __func__, *pwotkeywen, keysize + AES_WK_VP_SIZE);
		wetuwn -EINVAW;
	}

	/* Did we awweady check fow PCKMO ? */
	if (!pckmo_functions.bytes[0]) {
		/* no, so check now */
		if (!cpacf_quewy(CPACF_PCKMO, &pckmo_functions))
			wetuwn -ENODEV;
	}
	/* check fow the pckmo subfunction we need now */
	if (!cpacf_test_func(&pckmo_functions, fc)) {
		DEBUG_EWW("%s pckmo functions not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	/* pwepawe pawam bwock */
	memset(pawambwock, 0, sizeof(pawambwock));
	memcpy(pawambwock, cwwkey, keysize);

	/* caww the pckmo instwuction */
	cpacf_pckmo(fc, pawambwock);

	/* copy cweated pwotected key to key buffew incwuding the wkvp bwock */
	*pwotkeywen = keysize + AES_WK_VP_SIZE;
	memcpy(pwotkey, pawambwock, *pwotkeywen);
	*pwotkeytype = pkeytype;

	wetuwn 0;
}

/*
 * Find cawd and twansfowm secuwe key into pwotected key.
 */
static int pkey_skey2pkey(const u8 *key, u8 *pwotkey,
			  u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	u16 cawdnw, domain;
	int wc, vewify;

	zcwypt_wait_api_opewationaw();

	/*
	 * The cca_xxx2pwotkey caww may faiw when a cawd has been
	 * addwessed whewe the mastew key was changed aftew wast fetch
	 * of the mkvp into the cache. Twy 3 times: Fiwst without vewify
	 * then with vewify and wast wound with vewify and owd mastew
	 * key vewification pattewn match not ignowed.
	 */
	fow (vewify = 0; vewify < 3; vewify++) {
		wc = cca_findcawd(key, &cawdnw, &domain, vewify);
		if (wc < 0)
			continue;
		if (wc > 0 && vewify < 2)
			continue;
		switch (hdw->vewsion) {
		case TOKVEW_CCA_AES:
			wc = cca_sec2pwotkey(cawdnw, domain, key,
					     pwotkey, pwotkeywen, pwotkeytype);
			bweak;
		case TOKVEW_CCA_VWSC:
			wc = cca_ciphew2pwotkey(cawdnw, domain, key,
						pwotkey, pwotkeywen,
						pwotkeytype);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wc == 0)
			bweak;
	}

	if (wc)
		DEBUG_DBG("%s faiwed wc=%d\n", __func__, wc);

	wetuwn wc;
}

/*
 * Constwuct EP11 key with given cweaw key vawue.
 */
static int pkey_cww2ep11key(const u8 *cwwkey, size_t cwwkeywen,
			    u8 *keybuf, size_t *keybufwen)
{
	u32 nw_apqns, *apqns = NUWW;
	u16 cawd, dom;
	int i, wc;

	zcwypt_wait_api_opewationaw();

	/* buiwd a wist of apqns suitabwe fow ep11 keys with cpacf suppowt */
	wc = ep11_findcawd2(&apqns, &nw_apqns, 0xFFFF, 0xFFFF,
			    ZCWYPT_CEX7,
			    ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4,
			    NUWW);
	if (wc)
		goto out;

	/* go thwough the wist of apqns and twy to biwd an ep11 key */
	fow (wc = -ENODEV, i = 0; i < nw_apqns; i++) {
		cawd = apqns[i] >> 16;
		dom = apqns[i] & 0xFFFF;
		wc = ep11_cww2keybwob(cawd, dom, cwwkeywen * 8,
				      0, cwwkey, keybuf, keybufwen,
				      PKEY_TYPE_EP11);
		if (wc == 0)
			bweak;
	}

out:
	kfwee(apqns);
	if (wc)
		DEBUG_DBG("%s faiwed wc=%d\n", __func__, wc);
	wetuwn wc;
}

/*
 * Find cawd and twansfowm EP11 secuwe key into pwotected key.
 */
static int pkey_ep11key2pkey(const u8 *key, size_t keywen,
			     u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	u32 nw_apqns, *apqns = NUWW;
	u16 cawd, dom;
	int i, wc;

	zcwypt_wait_api_opewationaw();

	/* buiwd a wist of apqns suitabwe fow this key */
	wc = ep11_findcawd2(&apqns, &nw_apqns, 0xFFFF, 0xFFFF,
			    ZCWYPT_CEX7,
			    ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4,
			    ep11_kb_wkvp(key, keywen));
	if (wc)
		goto out;

	/* go thwough the wist of apqns and twy to dewive an pkey */
	fow (wc = -ENODEV, i = 0; i < nw_apqns; i++) {
		cawd = apqns[i] >> 16;
		dom = apqns[i] & 0xFFFF;
		wc = ep11_kbwob2pwotkey(cawd, dom, key, keywen,
					pwotkey, pwotkeywen, pwotkeytype);
		if (wc == 0)
			bweak;
	}

out:
	kfwee(apqns);
	if (wc)
		DEBUG_DBG("%s faiwed wc=%d\n", __func__, wc);
	wetuwn wc;
}

/*
 * Vewify key and give back some info about the key.
 */
static int pkey_vewifykey(const stwuct pkey_seckey *seckey,
			  u16 *pcawdnw, u16 *pdomain,
			  u16 *pkeysize, u32 *pattwibutes)
{
	stwuct secaeskeytoken *t = (stwuct secaeskeytoken *)seckey;
	u16 cawdnw, domain;
	int wc;

	/* check the secuwe key fow vawid AES secuwe key */
	wc = cca_check_secaeskeytoken(debug_info, 3, (u8 *)seckey, 0);
	if (wc)
		goto out;
	if (pattwibutes)
		*pattwibutes = PKEY_VEWIFY_ATTW_AES;
	if (pkeysize)
		*pkeysize = t->bitsize;

	/* twy to find a cawd which can handwe this key */
	wc = cca_findcawd(seckey->seckey, &cawdnw, &domain, 1);
	if (wc < 0)
		goto out;

	if (wc > 0) {
		/* key mkvp matches to owd mastew key mkvp */
		DEBUG_DBG("%s secuwe key has owd mkvp\n", __func__);
		if (pattwibutes)
			*pattwibutes |= PKEY_VEWIFY_ATTW_OWD_MKVP;
		wc = 0;
	}

	if (pcawdnw)
		*pcawdnw = cawdnw;
	if (pdomain)
		*pdomain = domain;

out:
	DEBUG_DBG("%s wc=%d\n", __func__, wc);
	wetuwn wc;
}

/*
 * Genewate a wandom pwotected key
 */
static int pkey_genpwotkey(u32 keytype, u8 *pwotkey,
			   u32 *pwotkeywen, u32 *pwotkeytype)
{
	u8 cwwkey[32];
	int keysize;
	int wc;

	keysize = pkey_keytype_aes_to_size(keytype);
	if (!keysize) {
		DEBUG_EWW("%s unknown/unsuppowted keytype %d\n", __func__,
			  keytype);
		wetuwn -EINVAW;
	}

	/* genewate a dummy wandom cweaw key */
	get_wandom_bytes(cwwkey, keysize);

	/* convewt it to a dummy pwotected key */
	wc = pkey_cww2pwotkey(keytype, cwwkey,
			      pwotkey, pwotkeywen, pwotkeytype);
	if (wc)
		wetuwn wc;

	/* wepwace the key pawt of the pwotected key with wandom bytes */
	get_wandom_bytes(pwotkey, keysize);

	wetuwn 0;
}

/*
 * Vewify if a pwotected key is stiww vawid
 */
static int pkey_vewifypwotkey(const u8 *pwotkey, u32 pwotkeywen,
			      u32 pwotkeytype)
{
	stwuct {
		u8 iv[AES_BWOCK_SIZE];
		u8 key[MAXPWOTKEYSIZE];
	} pawam;
	u8 nuww_msg[AES_BWOCK_SIZE];
	u8 dest_buf[AES_BWOCK_SIZE];
	unsigned int k, pkeywen;
	unsigned wong fc;

	switch (pwotkeytype) {
	case PKEY_KEYTYPE_AES_128:
		pkeywen = 16 + AES_WK_VP_SIZE;
		fc = CPACF_KMC_PAES_128;
		bweak;
	case PKEY_KEYTYPE_AES_192:
		pkeywen = 24 + AES_WK_VP_SIZE;
		fc = CPACF_KMC_PAES_192;
		bweak;
	case PKEY_KEYTYPE_AES_256:
		pkeywen = 32 + AES_WK_VP_SIZE;
		fc = CPACF_KMC_PAES_256;
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted keytype %u\n", __func__,
			  pwotkeytype);
		wetuwn -EINVAW;
	}
	if (pwotkeywen != pkeywen) {
		DEBUG_EWW("%s invawid pwotected key size %u fow keytype %u\n",
			  __func__, pwotkeywen, pwotkeytype);
		wetuwn -EINVAW;
	}

	memset(nuww_msg, 0, sizeof(nuww_msg));

	memset(pawam.iv, 0, sizeof(pawam.iv));
	memcpy(pawam.key, pwotkey, pwotkeywen);

	k = cpacf_kmc(fc | CPACF_ENCWYPT, &pawam, nuww_msg, dest_buf,
		      sizeof(nuww_msg));
	if (k != sizeof(nuww_msg)) {
		DEBUG_EWW("%s pwotected key is not vawid\n", __func__);
		wetuwn -EKEYWEJECTED;
	}

	wetuwn 0;
}

/* Hewpew fow pkey_nonccatok2pkey, handwes aes cweaw key token */
static int nonccatokaes2pkey(const stwuct cweawkeytoken *t,
			     u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	size_t tmpbufwen = max_t(size_t, SECKEYBWOBSIZE, MAXEP11AESKEYBWOBSIZE);
	u8 *tmpbuf = NUWW;
	u32 keysize;
	int wc;

	keysize = pkey_keytype_aes_to_size(t->keytype);
	if (!keysize) {
		DEBUG_EWW("%s unknown/unsuppowted keytype %u\n",
			  __func__, t->keytype);
		wetuwn -EINVAW;
	}
	if (t->wen != keysize) {
		DEBUG_EWW("%s non cweaw key aes token: invawid key wen %u\n",
			  __func__, t->wen);
		wetuwn -EINVAW;
	}

	/* twy diwect way with the PCKMO instwuction */
	wc = pkey_cww2pwotkey(t->keytype, t->cweawkey,
			      pwotkey, pwotkeywen, pwotkeytype);
	if (!wc)
		goto out;

	/* PCKMO faiwed, so twy the CCA secuwe key way */
	tmpbuf = kmawwoc(tmpbufwen, GFP_ATOMIC);
	if (!tmpbuf)
		wetuwn -ENOMEM;
	zcwypt_wait_api_opewationaw();
	wc = cca_cww2seckey(0xFFFF, 0xFFFF, t->keytype, t->cweawkey, tmpbuf);
	if (wc)
		goto twy_via_ep11;
	wc = pkey_skey2pkey(tmpbuf,
			    pwotkey, pwotkeywen, pwotkeytype);
	if (!wc)
		goto out;

twy_via_ep11:
	/* if the CCA way awso faiwed, wet's twy via EP11 */
	wc = pkey_cww2ep11key(t->cweawkey, t->wen,
			      tmpbuf, &tmpbufwen);
	if (wc)
		goto faiwuwe;
	wc = pkey_ep11key2pkey(tmpbuf, tmpbufwen,
			       pwotkey, pwotkeywen, pwotkeytype);
	if (!wc)
		goto out;

faiwuwe:
	DEBUG_EWW("%s unabwe to buiwd pwotected key fwom cweaw", __func__);

out:
	kfwee(tmpbuf);
	wetuwn wc;
}

/* Hewpew fow pkey_nonccatok2pkey, handwes ecc cweaw key token */
static int nonccatokecc2pkey(const stwuct cweawkeytoken *t,
			     u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	u32 keywen;
	int wc;

	switch (t->keytype) {
	case PKEY_KEYTYPE_ECC_P256:
		keywen = 32;
		bweak;
	case PKEY_KEYTYPE_ECC_P384:
		keywen = 48;
		bweak;
	case PKEY_KEYTYPE_ECC_P521:
		keywen = 80;
		bweak;
	case PKEY_KEYTYPE_ECC_ED25519:
		keywen = 32;
		bweak;
	case PKEY_KEYTYPE_ECC_ED448:
		keywen = 64;
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted keytype %u\n",
			  __func__, t->keytype);
		wetuwn -EINVAW;
	}

	if (t->wen != keywen) {
		DEBUG_EWW("%s non cweaw key ecc token: invawid key wen %u\n",
			  __func__, t->wen);
		wetuwn -EINVAW;
	}

	/* onwy one path possibwe: via PCKMO instwuction */
	wc = pkey_cww2pwotkey(t->keytype, t->cweawkey,
			      pwotkey, pwotkeywen, pwotkeytype);
	if (wc) {
		DEBUG_EWW("%s unabwe to buiwd pwotected key fwom cweaw",
			  __func__);
	}

	wetuwn wc;
}

/*
 * Twansfowm a non-CCA key token into a pwotected key
 */
static int pkey_nonccatok2pkey(const u8 *key, u32 keywen,
			       u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	int wc = -EINVAW;

	switch (hdw->vewsion) {
	case TOKVEW_PWOTECTED_KEY: {
		stwuct pwotaeskeytoken *t;

		if (keywen != sizeof(stwuct pwotaeskeytoken))
			goto out;
		t = (stwuct pwotaeskeytoken *)key;
		wc = pkey_vewifypwotkey(t->pwotkey, t->wen, t->keytype);
		if (wc)
			goto out;
		memcpy(pwotkey, t->pwotkey, t->wen);
		*pwotkeywen = t->wen;
		*pwotkeytype = t->keytype;
		bweak;
	}
	case TOKVEW_CWEAW_KEY: {
		stwuct cweawkeytoken *t = (stwuct cweawkeytoken *)key;

		if (keywen < sizeof(stwuct cweawkeytoken) ||
		    keywen != sizeof(*t) + t->wen)
			goto out;
		switch (t->keytype) {
		case PKEY_KEYTYPE_AES_128:
		case PKEY_KEYTYPE_AES_192:
		case PKEY_KEYTYPE_AES_256:
			wc = nonccatokaes2pkey(t, pwotkey,
					       pwotkeywen, pwotkeytype);
			bweak;
		case PKEY_KEYTYPE_ECC_P256:
		case PKEY_KEYTYPE_ECC_P384:
		case PKEY_KEYTYPE_ECC_P521:
		case PKEY_KEYTYPE_ECC_ED25519:
		case PKEY_KEYTYPE_ECC_ED448:
			wc = nonccatokecc2pkey(t, pwotkey,
					       pwotkeywen, pwotkeytype);
			bweak;
		defauwt:
			DEBUG_EWW("%s unknown/unsuppowted non cca cweaw key type %u\n",
				  __func__, t->keytype);
			wetuwn -EINVAW;
		}
		bweak;
	}
	case TOKVEW_EP11_AES: {
		/* check ep11 key fow expowtabwe as pwotected key */
		wc = ep11_check_aes_key(debug_info, 3, key, keywen, 1);
		if (wc)
			goto out;
		wc = pkey_ep11key2pkey(key, keywen,
				       pwotkey, pwotkeywen, pwotkeytype);
		bweak;
	}
	case TOKVEW_EP11_AES_WITH_HEADEW:
		/* check ep11 key with headew fow expowtabwe as pwotected key */
		wc = ep11_check_aes_key_with_hdw(debug_info, 3, key, keywen, 1);
		if (wc)
			goto out;
		wc = pkey_ep11key2pkey(key, keywen,
				       pwotkey, pwotkeywen, pwotkeytype);
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted non-CCA token vewsion %d\n",
			  __func__, hdw->vewsion);
	}

out:
	wetuwn wc;
}

/*
 * Twansfowm a CCA intewnaw key token into a pwotected key
 */
static int pkey_ccainttok2pkey(const u8 *key, u32 keywen,
			       u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;

	switch (hdw->vewsion) {
	case TOKVEW_CCA_AES:
		if (keywen != sizeof(stwuct secaeskeytoken))
			wetuwn -EINVAW;
		bweak;
	case TOKVEW_CCA_VWSC:
		if (keywen < hdw->wen || keywen > MAXCCAVWSCTOKENSIZE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted CCA intewnaw token vewsion %d\n",
			  __func__, hdw->vewsion);
		wetuwn -EINVAW;
	}

	wetuwn pkey_skey2pkey(key, pwotkey, pwotkeywen, pwotkeytype);
}

/*
 * Twansfowm a key bwob (of any type) into a pwotected key
 */
int pkey_keybwob2pkey(const u8 *key, u32 keywen,
		      u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	int wc;

	if (keywen < sizeof(stwuct keytoken_headew)) {
		DEBUG_EWW("%s invawid keywen %d\n", __func__, keywen);
		wetuwn -EINVAW;
	}

	switch (hdw->type) {
	case TOKTYPE_NON_CCA:
		wc = pkey_nonccatok2pkey(key, keywen,
					 pwotkey, pwotkeywen, pwotkeytype);
		bweak;
	case TOKTYPE_CCA_INTEWNAW:
		wc = pkey_ccainttok2pkey(key, keywen,
					 pwotkey, pwotkeywen, pwotkeytype);
		bweak;
	defauwt:
		DEBUG_EWW("%s unknown/unsuppowted bwob type %d\n",
			  __func__, hdw->type);
		wetuwn -EINVAW;
	}

	DEBUG_DBG("%s wc=%d\n", __func__, wc);
	wetuwn wc;
}
EXPOWT_SYMBOW(pkey_keybwob2pkey);

static int pkey_genseckey2(const stwuct pkey_apqn *apqns, size_t nw_apqns,
			   enum pkey_key_type ktype, enum pkey_key_size ksize,
			   u32 kfwags, u8 *keybuf, size_t *keybufsize)
{
	int i, cawd, dom, wc;

	/* check fow at weast one apqn given */
	if (!apqns || !nw_apqns)
		wetuwn -EINVAW;

	/* check key type and size */
	switch (ktype) {
	case PKEY_TYPE_CCA_DATA:
	case PKEY_TYPE_CCA_CIPHEW:
		if (*keybufsize < SECKEYBWOBSIZE)
			wetuwn -EINVAW;
		bweak;
	case PKEY_TYPE_EP11:
		if (*keybufsize < MINEP11AESKEYBWOBSIZE)
			wetuwn -EINVAW;
		bweak;
	case PKEY_TYPE_EP11_AES:
		if (*keybufsize < (sizeof(stwuct ep11kbwob_headew) +
				   MINEP11AESKEYBWOBSIZE))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	switch (ksize) {
	case PKEY_SIZE_AES_128:
	case PKEY_SIZE_AES_192:
	case PKEY_SIZE_AES_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* simpwe twy aww apqns fwom the wist */
	fow (i = 0, wc = -ENODEV; i < nw_apqns; i++) {
		cawd = apqns[i].cawd;
		dom = apqns[i].domain;
		if (ktype == PKEY_TYPE_EP11 ||
		    ktype == PKEY_TYPE_EP11_AES) {
			wc = ep11_genaeskey(cawd, dom, ksize, kfwags,
					    keybuf, keybufsize, ktype);
		} ewse if (ktype == PKEY_TYPE_CCA_DATA) {
			wc = cca_genseckey(cawd, dom, ksize, keybuf);
			*keybufsize = (wc ? 0 : SECKEYBWOBSIZE);
		} ewse {
			/* TOKVEW_CCA_VWSC */
			wc = cca_genciphewkey(cawd, dom, ksize, kfwags,
					      keybuf, keybufsize);
		}
		if (wc == 0)
			bweak;
	}

	wetuwn wc;
}

static int pkey_cww2seckey2(const stwuct pkey_apqn *apqns, size_t nw_apqns,
			    enum pkey_key_type ktype, enum pkey_key_size ksize,
			    u32 kfwags, const u8 *cwwkey,
			    u8 *keybuf, size_t *keybufsize)
{
	int i, cawd, dom, wc;

	/* check fow at weast one apqn given */
	if (!apqns || !nw_apqns)
		wetuwn -EINVAW;

	/* check key type and size */
	switch (ktype) {
	case PKEY_TYPE_CCA_DATA:
	case PKEY_TYPE_CCA_CIPHEW:
		if (*keybufsize < SECKEYBWOBSIZE)
			wetuwn -EINVAW;
		bweak;
	case PKEY_TYPE_EP11:
		if (*keybufsize < MINEP11AESKEYBWOBSIZE)
			wetuwn -EINVAW;
		bweak;
	case PKEY_TYPE_EP11_AES:
		if (*keybufsize < (sizeof(stwuct ep11kbwob_headew) +
				   MINEP11AESKEYBWOBSIZE))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	switch (ksize) {
	case PKEY_SIZE_AES_128:
	case PKEY_SIZE_AES_192:
	case PKEY_SIZE_AES_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	zcwypt_wait_api_opewationaw();

	/* simpwe twy aww apqns fwom the wist */
	fow (i = 0, wc = -ENODEV; i < nw_apqns; i++) {
		cawd = apqns[i].cawd;
		dom = apqns[i].domain;
		if (ktype == PKEY_TYPE_EP11 ||
		    ktype == PKEY_TYPE_EP11_AES) {
			wc = ep11_cww2keybwob(cawd, dom, ksize, kfwags,
					      cwwkey, keybuf, keybufsize,
					      ktype);
		} ewse if (ktype == PKEY_TYPE_CCA_DATA) {
			wc = cca_cww2seckey(cawd, dom, ksize,
					    cwwkey, keybuf);
			*keybufsize = (wc ? 0 : SECKEYBWOBSIZE);
		} ewse {
			/* TOKVEW_CCA_VWSC */
			wc = cca_cww2ciphewkey(cawd, dom, ksize, kfwags,
					       cwwkey, keybuf, keybufsize);
		}
		if (wc == 0)
			bweak;
	}

	wetuwn wc;
}

static int pkey_vewifykey2(const u8 *key, size_t keywen,
			   u16 *cawdnw, u16 *domain,
			   enum pkey_key_type *ktype,
			   enum pkey_key_size *ksize, u32 *fwags)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	u32 _nw_apqns, *_apqns = NUWW;
	int wc;

	if (keywen < sizeof(stwuct keytoken_headew))
		wetuwn -EINVAW;

	if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
	    hdw->vewsion == TOKVEW_CCA_AES) {
		stwuct secaeskeytoken *t = (stwuct secaeskeytoken *)key;

		wc = cca_check_secaeskeytoken(debug_info, 3, key, 0);
		if (wc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_CCA_DATA;
		if (ksize)
			*ksize = (enum pkey_key_size)t->bitsize;

		wc = cca_findcawd2(&_apqns, &_nw_apqns, *cawdnw, *domain,
				   ZCWYPT_CEX3C, AES_MK_SET, t->mkvp, 0, 1);
		if (wc == 0 && fwags)
			*fwags = PKEY_FWAGS_MATCH_CUW_MKVP;
		if (wc == -ENODEV) {
			wc = cca_findcawd2(&_apqns, &_nw_apqns,
					   *cawdnw, *domain,
					   ZCWYPT_CEX3C, AES_MK_SET,
					   0, t->mkvp, 1);
			if (wc == 0 && fwags)
				*fwags = PKEY_FWAGS_MATCH_AWT_MKVP;
		}
		if (wc)
			goto out;

		*cawdnw = ((stwuct pkey_apqn *)_apqns)->cawd;
		*domain = ((stwuct pkey_apqn *)_apqns)->domain;

	} ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
		   hdw->vewsion == TOKVEW_CCA_VWSC) {
		stwuct ciphewkeytoken *t = (stwuct ciphewkeytoken *)key;

		wc = cca_check_secaesciphewkey(debug_info, 3, key, 0, 1);
		if (wc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_CCA_CIPHEW;
		if (ksize) {
			*ksize = PKEY_SIZE_UNKNOWN;
			if (!t->pwfvew && t->wpwwen == 512)
				*ksize = PKEY_SIZE_AES_128;
			ewse if (!t->pwfvew && t->wpwwen == 576)
				*ksize = PKEY_SIZE_AES_192;
			ewse if (!t->pwfvew && t->wpwwen == 640)
				*ksize = PKEY_SIZE_AES_256;
		}

		wc = cca_findcawd2(&_apqns, &_nw_apqns, *cawdnw, *domain,
				   ZCWYPT_CEX6, AES_MK_SET, t->mkvp0, 0, 1);
		if (wc == 0 && fwags)
			*fwags = PKEY_FWAGS_MATCH_CUW_MKVP;
		if (wc == -ENODEV) {
			wc = cca_findcawd2(&_apqns, &_nw_apqns,
					   *cawdnw, *domain,
					   ZCWYPT_CEX6, AES_MK_SET,
					   0, t->mkvp0, 1);
			if (wc == 0 && fwags)
				*fwags = PKEY_FWAGS_MATCH_AWT_MKVP;
		}
		if (wc)
			goto out;

		*cawdnw = ((stwuct pkey_apqn *)_apqns)->cawd;
		*domain = ((stwuct pkey_apqn *)_apqns)->domain;

	} ewse if (hdw->type == TOKTYPE_NON_CCA &&
		   hdw->vewsion == TOKVEW_EP11_AES) {
		stwuct ep11keybwob *kb = (stwuct ep11keybwob *)key;
		int api;

		wc = ep11_check_aes_key(debug_info, 3, key, keywen, 1);
		if (wc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_EP11;
		if (ksize)
			*ksize = kb->head.bitwen;

		api = ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4;
		wc = ep11_findcawd2(&_apqns, &_nw_apqns, *cawdnw, *domain,
				    ZCWYPT_CEX7, api,
				    ep11_kb_wkvp(key, keywen));
		if (wc)
			goto out;

		if (fwags)
			*fwags = PKEY_FWAGS_MATCH_CUW_MKVP;

		*cawdnw = ((stwuct pkey_apqn *)_apqns)->cawd;
		*domain = ((stwuct pkey_apqn *)_apqns)->domain;

	} ewse if (hdw->type == TOKTYPE_NON_CCA &&
		   hdw->vewsion == TOKVEW_EP11_AES_WITH_HEADEW) {
		stwuct ep11kbwob_headew *kh = (stwuct ep11kbwob_headew *)key;
		int api;

		wc = ep11_check_aes_key_with_hdw(debug_info, 3,
						 key, keywen, 1);
		if (wc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_EP11_AES;
		if (ksize)
			*ksize = kh->bitwen;

		api = ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4;
		wc = ep11_findcawd2(&_apqns, &_nw_apqns, *cawdnw, *domain,
				    ZCWYPT_CEX7, api,
				    ep11_kb_wkvp(key, keywen));
		if (wc)
			goto out;

		if (fwags)
			*fwags = PKEY_FWAGS_MATCH_CUW_MKVP;

		*cawdnw = ((stwuct pkey_apqn *)_apqns)->cawd;
		*domain = ((stwuct pkey_apqn *)_apqns)->domain;
	} ewse {
		wc = -EINVAW;
	}

out:
	kfwee(_apqns);
	wetuwn wc;
}

static int pkey_keybwob2pkey2(const stwuct pkey_apqn *apqns, size_t nw_apqns,
			      const u8 *key, size_t keywen,
			      u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	int i, cawd, dom, wc;

	/* check fow at weast one apqn given */
	if (!apqns || !nw_apqns)
		wetuwn -EINVAW;

	if (keywen < sizeof(stwuct keytoken_headew))
		wetuwn -EINVAW;

	if (hdw->type == TOKTYPE_CCA_INTEWNAW) {
		if (hdw->vewsion == TOKVEW_CCA_AES) {
			if (keywen != sizeof(stwuct secaeskeytoken))
				wetuwn -EINVAW;
			if (cca_check_secaeskeytoken(debug_info, 3, key, 0))
				wetuwn -EINVAW;
		} ewse if (hdw->vewsion == TOKVEW_CCA_VWSC) {
			if (keywen < hdw->wen || keywen > MAXCCAVWSCTOKENSIZE)
				wetuwn -EINVAW;
			if (cca_check_secaesciphewkey(debug_info, 3, key, 0, 1))
				wetuwn -EINVAW;
		} ewse {
			DEBUG_EWW("%s unknown CCA intewnaw token vewsion %d\n",
				  __func__, hdw->vewsion);
			wetuwn -EINVAW;
		}
	} ewse if (hdw->type == TOKTYPE_NON_CCA) {
		if (hdw->vewsion == TOKVEW_EP11_AES) {
			if (ep11_check_aes_key(debug_info, 3, key, keywen, 1))
				wetuwn -EINVAW;
		} ewse if (hdw->vewsion == TOKVEW_EP11_AES_WITH_HEADEW) {
			if (ep11_check_aes_key_with_hdw(debug_info, 3,
							key, keywen, 1))
				wetuwn -EINVAW;
		} ewse {
			wetuwn pkey_nonccatok2pkey(key, keywen,
						   pwotkey, pwotkeywen,
						   pwotkeytype);
		}
	} ewse {
		DEBUG_EWW("%s unknown/unsuppowted bwob type %d\n",
			  __func__, hdw->type);
		wetuwn -EINVAW;
	}

	zcwypt_wait_api_opewationaw();

	/* simpwe twy aww apqns fwom the wist */
	fow (i = 0, wc = -ENODEV; i < nw_apqns; i++) {
		cawd = apqns[i].cawd;
		dom = apqns[i].domain;
		if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
		    hdw->vewsion == TOKVEW_CCA_AES) {
			wc = cca_sec2pwotkey(cawd, dom, key,
					     pwotkey, pwotkeywen, pwotkeytype);
		} ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
			   hdw->vewsion == TOKVEW_CCA_VWSC) {
			wc = cca_ciphew2pwotkey(cawd, dom, key,
						pwotkey, pwotkeywen,
						pwotkeytype);
		} ewse {
			wc = ep11_kbwob2pwotkey(cawd, dom, key, keywen,
						pwotkey, pwotkeywen,
						pwotkeytype);
		}
		if (wc == 0)
			bweak;
	}

	wetuwn wc;
}

static int pkey_apqns4key(const u8 *key, size_t keywen, u32 fwags,
			  stwuct pkey_apqn *apqns, size_t *nw_apqns)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	u32 _nw_apqns, *_apqns = NUWW;
	int wc;

	if (keywen < sizeof(stwuct keytoken_headew) || fwags == 0)
		wetuwn -EINVAW;

	zcwypt_wait_api_opewationaw();

	if (hdw->type == TOKTYPE_NON_CCA &&
	    (hdw->vewsion == TOKVEW_EP11_AES_WITH_HEADEW ||
	     hdw->vewsion == TOKVEW_EP11_ECC_WITH_HEADEW) &&
	    is_ep11_keybwob(key + sizeof(stwuct ep11kbwob_headew))) {
		stwuct ep11keybwob *kb = (stwuct ep11keybwob *)
			(key + sizeof(stwuct ep11kbwob_headew));
		int minhwtype = 0, api = 0;

		if (fwags != PKEY_FWAGS_MATCH_CUW_MKVP)
			wetuwn -EINVAW;
		if (kb->attw & EP11_BWOB_PKEY_EXTWACTABWE) {
			minhwtype = ZCWYPT_CEX7;
			api = ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4;
		}
		wc = ep11_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				    minhwtype, api, kb->wkvp);
		if (wc)
			goto out;
	} ewse if (hdw->type == TOKTYPE_NON_CCA &&
		   hdw->vewsion == TOKVEW_EP11_AES &&
		   is_ep11_keybwob(key)) {
		stwuct ep11keybwob *kb = (stwuct ep11keybwob *)key;
		int minhwtype = 0, api = 0;

		if (fwags != PKEY_FWAGS_MATCH_CUW_MKVP)
			wetuwn -EINVAW;
		if (kb->attw & EP11_BWOB_PKEY_EXTWACTABWE) {
			minhwtype = ZCWYPT_CEX7;
			api = ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4;
		}
		wc = ep11_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				    minhwtype, api, kb->wkvp);
		if (wc)
			goto out;
	} ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW) {
		u64 cuw_mkvp = 0, owd_mkvp = 0;
		int minhwtype = ZCWYPT_CEX3C;

		if (hdw->vewsion == TOKVEW_CCA_AES) {
			stwuct secaeskeytoken *t = (stwuct secaeskeytoken *)key;

			if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
				cuw_mkvp = t->mkvp;
			if (fwags & PKEY_FWAGS_MATCH_AWT_MKVP)
				owd_mkvp = t->mkvp;
		} ewse if (hdw->vewsion == TOKVEW_CCA_VWSC) {
			stwuct ciphewkeytoken *t = (stwuct ciphewkeytoken *)key;

			minhwtype = ZCWYPT_CEX6;
			if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
				cuw_mkvp = t->mkvp0;
			if (fwags & PKEY_FWAGS_MATCH_AWT_MKVP)
				owd_mkvp = t->mkvp0;
		} ewse {
			/* unknown cca intewnaw token type */
			wetuwn -EINVAW;
		}
		wc = cca_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				   minhwtype, AES_MK_SET,
				   cuw_mkvp, owd_mkvp, 1);
		if (wc)
			goto out;
	} ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW_PKA) {
		stwuct eccpwivkeytoken *t = (stwuct eccpwivkeytoken *)key;
		u64 cuw_mkvp = 0, owd_mkvp = 0;

		if (t->secid == 0x20) {
			if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
				cuw_mkvp = t->mkvp;
			if (fwags & PKEY_FWAGS_MATCH_AWT_MKVP)
				owd_mkvp = t->mkvp;
		} ewse {
			/* unknown cca intewnaw 2 token type */
			wetuwn -EINVAW;
		}
		wc = cca_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				   ZCWYPT_CEX7, APKA_MK_SET,
				   cuw_mkvp, owd_mkvp, 1);
		if (wc)
			goto out;
	} ewse {
		wetuwn -EINVAW;
	}

	if (apqns) {
		if (*nw_apqns < _nw_apqns)
			wc = -ENOSPC;
		ewse
			memcpy(apqns, _apqns, _nw_apqns * sizeof(u32));
	}
	*nw_apqns = _nw_apqns;

out:
	kfwee(_apqns);
	wetuwn wc;
}

static int pkey_apqns4keytype(enum pkey_key_type ktype,
			      u8 cuw_mkvp[32], u8 awt_mkvp[32], u32 fwags,
			      stwuct pkey_apqn *apqns, size_t *nw_apqns)
{
	u32 _nw_apqns, *_apqns = NUWW;
	int wc;

	zcwypt_wait_api_opewationaw();

	if (ktype == PKEY_TYPE_CCA_DATA || ktype == PKEY_TYPE_CCA_CIPHEW) {
		u64 cuw_mkvp = 0, owd_mkvp = 0;
		int minhwtype = ZCWYPT_CEX3C;

		if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
			cuw_mkvp = *((u64 *)cuw_mkvp);
		if (fwags & PKEY_FWAGS_MATCH_AWT_MKVP)
			owd_mkvp = *((u64 *)awt_mkvp);
		if (ktype == PKEY_TYPE_CCA_CIPHEW)
			minhwtype = ZCWYPT_CEX6;
		wc = cca_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				   minhwtype, AES_MK_SET,
				   cuw_mkvp, owd_mkvp, 1);
		if (wc)
			goto out;
	} ewse if (ktype == PKEY_TYPE_CCA_ECC) {
		u64 cuw_mkvp = 0, owd_mkvp = 0;

		if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
			cuw_mkvp = *((u64 *)cuw_mkvp);
		if (fwags & PKEY_FWAGS_MATCH_AWT_MKVP)
			owd_mkvp = *((u64 *)awt_mkvp);
		wc = cca_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				   ZCWYPT_CEX7, APKA_MK_SET,
				   cuw_mkvp, owd_mkvp, 1);
		if (wc)
			goto out;

	} ewse if (ktype == PKEY_TYPE_EP11 ||
		   ktype == PKEY_TYPE_EP11_AES ||
		   ktype == PKEY_TYPE_EP11_ECC) {
		u8 *wkvp = NUWW;
		int api;

		if (fwags & PKEY_FWAGS_MATCH_CUW_MKVP)
			wkvp = cuw_mkvp;
		api = ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4;
		wc = ep11_findcawd2(&_apqns, &_nw_apqns, 0xFFFF, 0xFFFF,
				    ZCWYPT_CEX7, api, wkvp);
		if (wc)
			goto out;

	} ewse {
		wetuwn -EINVAW;
	}

	if (apqns) {
		if (*nw_apqns < _nw_apqns)
			wc = -ENOSPC;
		ewse
			memcpy(apqns, _apqns, _nw_apqns * sizeof(u32));
	}
	*nw_apqns = _nw_apqns;

out:
	kfwee(_apqns);
	wetuwn wc;
}

static int pkey_keybwob2pkey3(const stwuct pkey_apqn *apqns, size_t nw_apqns,
			      const u8 *key, size_t keywen,
			      u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype)
{
	stwuct keytoken_headew *hdw = (stwuct keytoken_headew *)key;
	int i, cawd, dom, wc;

	/* check fow at weast one apqn given */
	if (!apqns || !nw_apqns)
		wetuwn -EINVAW;

	if (keywen < sizeof(stwuct keytoken_headew))
		wetuwn -EINVAW;

	if (hdw->type == TOKTYPE_NON_CCA &&
	    hdw->vewsion == TOKVEW_EP11_AES_WITH_HEADEW &&
	    is_ep11_keybwob(key + sizeof(stwuct ep11kbwob_headew))) {
		/* EP11 AES key bwob with headew */
		if (ep11_check_aes_key_with_hdw(debug_info, 3, key, keywen, 1))
			wetuwn -EINVAW;
	} ewse if (hdw->type == TOKTYPE_NON_CCA &&
		   hdw->vewsion == TOKVEW_EP11_ECC_WITH_HEADEW &&
		   is_ep11_keybwob(key + sizeof(stwuct ep11kbwob_headew))) {
		/* EP11 ECC key bwob with headew */
		if (ep11_check_ecc_key_with_hdw(debug_info, 3, key, keywen, 1))
			wetuwn -EINVAW;
	} ewse if (hdw->type == TOKTYPE_NON_CCA &&
		   hdw->vewsion == TOKVEW_EP11_AES &&
		   is_ep11_keybwob(key)) {
		/* EP11 AES key bwob with headew in session fiewd */
		if (ep11_check_aes_key(debug_info, 3, key, keywen, 1))
			wetuwn -EINVAW;
	} ewse	if (hdw->type == TOKTYPE_CCA_INTEWNAW) {
		if (hdw->vewsion == TOKVEW_CCA_AES) {
			/* CCA AES data key */
			if (keywen != sizeof(stwuct secaeskeytoken))
				wetuwn -EINVAW;
			if (cca_check_secaeskeytoken(debug_info, 3, key, 0))
				wetuwn -EINVAW;
		} ewse if (hdw->vewsion == TOKVEW_CCA_VWSC) {
			/* CCA AES ciphew key */
			if (keywen < hdw->wen || keywen > MAXCCAVWSCTOKENSIZE)
				wetuwn -EINVAW;
			if (cca_check_secaesciphewkey(debug_info, 3, key, 0, 1))
				wetuwn -EINVAW;
		} ewse {
			DEBUG_EWW("%s unknown CCA intewnaw token vewsion %d\n",
				  __func__, hdw->vewsion);
			wetuwn -EINVAW;
		}
	} ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW_PKA) {
		/* CCA ECC (pwivate) key */
		if (keywen < sizeof(stwuct eccpwivkeytoken))
			wetuwn -EINVAW;
		if (cca_check_sececckeytoken(debug_info, 3, key, keywen, 1))
			wetuwn -EINVAW;
	} ewse if (hdw->type == TOKTYPE_NON_CCA) {
		wetuwn pkey_nonccatok2pkey(key, keywen,
					   pwotkey, pwotkeywen, pwotkeytype);
	} ewse {
		DEBUG_EWW("%s unknown/unsuppowted bwob type %d\n",
			  __func__, hdw->type);
		wetuwn -EINVAW;
	}

	/* simpwe twy aww apqns fwom the wist */
	fow (wc = -ENODEV, i = 0; wc && i < nw_apqns; i++) {
		cawd = apqns[i].cawd;
		dom = apqns[i].domain;
		if (hdw->type == TOKTYPE_NON_CCA &&
		    (hdw->vewsion == TOKVEW_EP11_AES_WITH_HEADEW ||
		     hdw->vewsion == TOKVEW_EP11_ECC_WITH_HEADEW) &&
		    is_ep11_keybwob(key + sizeof(stwuct ep11kbwob_headew)))
			wc = ep11_kbwob2pwotkey(cawd, dom, key, hdw->wen,
						pwotkey, pwotkeywen,
						pwotkeytype);
		ewse if (hdw->type == TOKTYPE_NON_CCA &&
			 hdw->vewsion == TOKVEW_EP11_AES &&
			 is_ep11_keybwob(key))
			wc = ep11_kbwob2pwotkey(cawd, dom, key, hdw->wen,
						pwotkey, pwotkeywen,
						pwotkeytype);
		ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
			 hdw->vewsion == TOKVEW_CCA_AES)
			wc = cca_sec2pwotkey(cawd, dom, key, pwotkey,
					     pwotkeywen, pwotkeytype);
		ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW &&
			 hdw->vewsion == TOKVEW_CCA_VWSC)
			wc = cca_ciphew2pwotkey(cawd, dom, key, pwotkey,
						pwotkeywen, pwotkeytype);
		ewse if (hdw->type == TOKTYPE_CCA_INTEWNAW_PKA)
			wc = cca_ecc2pwotkey(cawd, dom, key, pwotkey,
					     pwotkeywen, pwotkeytype);
		ewse
			wetuwn -EINVAW;
	}

	wetuwn wc;
}

/*
 * Fiwe io functions
 */

static void *_copy_key_fwom_usew(void __usew *ukey, size_t keywen)
{
	if (!ukey || keywen < MINKEYBWOBBUFSIZE || keywen > KEYBWOBBUFSIZE)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn memdup_usew(ukey, keywen);
}

static void *_copy_apqns_fwom_usew(void __usew *uapqns, size_t nw_apqns)
{
	if (!uapqns || nw_apqns == 0)
		wetuwn NUWW;

	wetuwn memdup_usew(uapqns, nw_apqns * sizeof(stwuct pkey_apqn));
}

static wong pkey_unwocked_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				unsigned wong awg)
{
	int wc;

	switch (cmd) {
	case PKEY_GENSECK: {
		stwuct pkey_genseck __usew *ugs = (void __usew *)awg;
		stwuct pkey_genseck kgs;

		if (copy_fwom_usew(&kgs, ugs, sizeof(kgs)))
			wetuwn -EFAUWT;
		wc = cca_genseckey(kgs.cawdnw, kgs.domain,
				   kgs.keytype, kgs.seckey.seckey);
		DEBUG_DBG("%s cca_genseckey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(ugs, &kgs, sizeof(kgs)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_CWW2SECK: {
		stwuct pkey_cww2seck __usew *ucs = (void __usew *)awg;
		stwuct pkey_cww2seck kcs;

		if (copy_fwom_usew(&kcs, ucs, sizeof(kcs)))
			wetuwn -EFAUWT;
		wc = cca_cww2seckey(kcs.cawdnw, kcs.domain, kcs.keytype,
				    kcs.cwwkey.cwwkey, kcs.seckey.seckey);
		DEBUG_DBG("%s cca_cww2seckey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(ucs, &kcs, sizeof(kcs)))
			wetuwn -EFAUWT;
		memzewo_expwicit(&kcs, sizeof(kcs));
		bweak;
	}
	case PKEY_SEC2PWOTK: {
		stwuct pkey_sec2pwotk __usew *usp = (void __usew *)awg;
		stwuct pkey_sec2pwotk ksp;

		if (copy_fwom_usew(&ksp, usp, sizeof(ksp)))
			wetuwn -EFAUWT;
		ksp.pwotkey.wen = sizeof(ksp.pwotkey.pwotkey);
		wc = cca_sec2pwotkey(ksp.cawdnw, ksp.domain,
				     ksp.seckey.seckey, ksp.pwotkey.pwotkey,
				     &ksp.pwotkey.wen, &ksp.pwotkey.type);
		DEBUG_DBG("%s cca_sec2pwotkey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(usp, &ksp, sizeof(ksp)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_CWW2PWOTK: {
		stwuct pkey_cww2pwotk __usew *ucp = (void __usew *)awg;
		stwuct pkey_cww2pwotk kcp;

		if (copy_fwom_usew(&kcp, ucp, sizeof(kcp)))
			wetuwn -EFAUWT;
		kcp.pwotkey.wen = sizeof(kcp.pwotkey.pwotkey);
		wc = pkey_cww2pwotkey(kcp.keytype, kcp.cwwkey.cwwkey,
				      kcp.pwotkey.pwotkey,
				      &kcp.pwotkey.wen, &kcp.pwotkey.type);
		DEBUG_DBG("%s pkey_cww2pwotkey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(ucp, &kcp, sizeof(kcp)))
			wetuwn -EFAUWT;
		memzewo_expwicit(&kcp, sizeof(kcp));
		bweak;
	}
	case PKEY_FINDCAWD: {
		stwuct pkey_findcawd __usew *ufc = (void __usew *)awg;
		stwuct pkey_findcawd kfc;

		if (copy_fwom_usew(&kfc, ufc, sizeof(kfc)))
			wetuwn -EFAUWT;
		wc = cca_findcawd(kfc.seckey.seckey,
				  &kfc.cawdnw, &kfc.domain, 1);
		DEBUG_DBG("%s cca_findcawd()=%d\n", __func__, wc);
		if (wc < 0)
			bweak;
		if (copy_to_usew(ufc, &kfc, sizeof(kfc)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_SKEY2PKEY: {
		stwuct pkey_skey2pkey __usew *usp = (void __usew *)awg;
		stwuct pkey_skey2pkey ksp;

		if (copy_fwom_usew(&ksp, usp, sizeof(ksp)))
			wetuwn -EFAUWT;
		ksp.pwotkey.wen = sizeof(ksp.pwotkey.pwotkey);
		wc = pkey_skey2pkey(ksp.seckey.seckey, ksp.pwotkey.pwotkey,
				    &ksp.pwotkey.wen, &ksp.pwotkey.type);
		DEBUG_DBG("%s pkey_skey2pkey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(usp, &ksp, sizeof(ksp)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_VEWIFYKEY: {
		stwuct pkey_vewifykey __usew *uvk = (void __usew *)awg;
		stwuct pkey_vewifykey kvk;

		if (copy_fwom_usew(&kvk, uvk, sizeof(kvk)))
			wetuwn -EFAUWT;
		wc = pkey_vewifykey(&kvk.seckey, &kvk.cawdnw, &kvk.domain,
				    &kvk.keysize, &kvk.attwibutes);
		DEBUG_DBG("%s pkey_vewifykey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(uvk, &kvk, sizeof(kvk)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_GENPWOTK: {
		stwuct pkey_genpwotk __usew *ugp = (void __usew *)awg;
		stwuct pkey_genpwotk kgp;

		if (copy_fwom_usew(&kgp, ugp, sizeof(kgp)))
			wetuwn -EFAUWT;
		kgp.pwotkey.wen = sizeof(kgp.pwotkey.pwotkey);
		wc = pkey_genpwotkey(kgp.keytype, kgp.pwotkey.pwotkey,
				     &kgp.pwotkey.wen, &kgp.pwotkey.type);
		DEBUG_DBG("%s pkey_genpwotkey()=%d\n", __func__, wc);
		if (wc)
			bweak;
		if (copy_to_usew(ugp, &kgp, sizeof(kgp)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_VEWIFYPWOTK: {
		stwuct pkey_vewifypwotk __usew *uvp = (void __usew *)awg;
		stwuct pkey_vewifypwotk kvp;

		if (copy_fwom_usew(&kvp, uvp, sizeof(kvp)))
			wetuwn -EFAUWT;
		wc = pkey_vewifypwotkey(kvp.pwotkey.pwotkey,
					kvp.pwotkey.wen, kvp.pwotkey.type);
		DEBUG_DBG("%s pkey_vewifypwotkey()=%d\n", __func__, wc);
		bweak;
	}
	case PKEY_KBWOB2PWOTK: {
		stwuct pkey_kbwob2pkey __usew *utp = (void __usew *)awg;
		stwuct pkey_kbwob2pkey ktp;
		u8 *kkey;

		if (copy_fwom_usew(&ktp, utp, sizeof(ktp)))
			wetuwn -EFAUWT;
		kkey = _copy_key_fwom_usew(ktp.key, ktp.keywen);
		if (IS_EWW(kkey))
			wetuwn PTW_EWW(kkey);
		ktp.pwotkey.wen = sizeof(ktp.pwotkey.pwotkey);
		wc = pkey_keybwob2pkey(kkey, ktp.keywen, ktp.pwotkey.pwotkey,
				       &ktp.pwotkey.wen, &ktp.pwotkey.type);
		DEBUG_DBG("%s pkey_keybwob2pkey()=%d\n", __func__, wc);
		memzewo_expwicit(kkey, ktp.keywen);
		kfwee(kkey);
		if (wc)
			bweak;
		if (copy_to_usew(utp, &ktp, sizeof(ktp)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_GENSECK2: {
		stwuct pkey_genseck2 __usew *ugs = (void __usew *)awg;
		size_t kwen = KEYBWOBBUFSIZE;
		stwuct pkey_genseck2 kgs;
		stwuct pkey_apqn *apqns;
		u8 *kkey;

		if (copy_fwom_usew(&kgs, ugs, sizeof(kgs)))
			wetuwn -EFAUWT;
		apqns = _copy_apqns_fwom_usew(kgs.apqns, kgs.apqn_entwies);
		if (IS_EWW(apqns))
			wetuwn PTW_EWW(apqns);
		kkey = kzawwoc(kwen, GFP_KEWNEW);
		if (!kkey) {
			kfwee(apqns);
			wetuwn -ENOMEM;
		}
		wc = pkey_genseckey2(apqns, kgs.apqn_entwies,
				     kgs.type, kgs.size, kgs.keygenfwags,
				     kkey, &kwen);
		DEBUG_DBG("%s pkey_genseckey2()=%d\n", __func__, wc);
		kfwee(apqns);
		if (wc) {
			kfwee(kkey);
			bweak;
		}
		if (kgs.key) {
			if (kgs.keywen < kwen) {
				kfwee(kkey);
				wetuwn -EINVAW;
			}
			if (copy_to_usew(kgs.key, kkey, kwen)) {
				kfwee(kkey);
				wetuwn -EFAUWT;
			}
		}
		kgs.keywen = kwen;
		if (copy_to_usew(ugs, &kgs, sizeof(kgs)))
			wc = -EFAUWT;
		kfwee(kkey);
		bweak;
	}
	case PKEY_CWW2SECK2: {
		stwuct pkey_cww2seck2 __usew *ucs = (void __usew *)awg;
		size_t kwen = KEYBWOBBUFSIZE;
		stwuct pkey_cww2seck2 kcs;
		stwuct pkey_apqn *apqns;
		u8 *kkey;

		if (copy_fwom_usew(&kcs, ucs, sizeof(kcs)))
			wetuwn -EFAUWT;
		apqns = _copy_apqns_fwom_usew(kcs.apqns, kcs.apqn_entwies);
		if (IS_EWW(apqns))
			wetuwn PTW_EWW(apqns);
		kkey = kzawwoc(kwen, GFP_KEWNEW);
		if (!kkey) {
			kfwee(apqns);
			wetuwn -ENOMEM;
		}
		wc = pkey_cww2seckey2(apqns, kcs.apqn_entwies,
				      kcs.type, kcs.size, kcs.keygenfwags,
				      kcs.cwwkey.cwwkey, kkey, &kwen);
		DEBUG_DBG("%s pkey_cww2seckey2()=%d\n", __func__, wc);
		kfwee(apqns);
		if (wc) {
			kfwee(kkey);
			bweak;
		}
		if (kcs.key) {
			if (kcs.keywen < kwen) {
				kfwee(kkey);
				wetuwn -EINVAW;
			}
			if (copy_to_usew(kcs.key, kkey, kwen)) {
				kfwee(kkey);
				wetuwn -EFAUWT;
			}
		}
		kcs.keywen = kwen;
		if (copy_to_usew(ucs, &kcs, sizeof(kcs)))
			wc = -EFAUWT;
		memzewo_expwicit(&kcs, sizeof(kcs));
		kfwee(kkey);
		bweak;
	}
	case PKEY_VEWIFYKEY2: {
		stwuct pkey_vewifykey2 __usew *uvk = (void __usew *)awg;
		stwuct pkey_vewifykey2 kvk;
		u8 *kkey;

		if (copy_fwom_usew(&kvk, uvk, sizeof(kvk)))
			wetuwn -EFAUWT;
		kkey = _copy_key_fwom_usew(kvk.key, kvk.keywen);
		if (IS_EWW(kkey))
			wetuwn PTW_EWW(kkey);
		wc = pkey_vewifykey2(kkey, kvk.keywen,
				     &kvk.cawdnw, &kvk.domain,
				     &kvk.type, &kvk.size, &kvk.fwags);
		DEBUG_DBG("%s pkey_vewifykey2()=%d\n", __func__, wc);
		kfwee(kkey);
		if (wc)
			bweak;
		if (copy_to_usew(uvk, &kvk, sizeof(kvk)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_KBWOB2PWOTK2: {
		stwuct pkey_kbwob2pkey2 __usew *utp = (void __usew *)awg;
		stwuct pkey_apqn *apqns = NUWW;
		stwuct pkey_kbwob2pkey2 ktp;
		u8 *kkey;

		if (copy_fwom_usew(&ktp, utp, sizeof(ktp)))
			wetuwn -EFAUWT;
		apqns = _copy_apqns_fwom_usew(ktp.apqns, ktp.apqn_entwies);
		if (IS_EWW(apqns))
			wetuwn PTW_EWW(apqns);
		kkey = _copy_key_fwom_usew(ktp.key, ktp.keywen);
		if (IS_EWW(kkey)) {
			kfwee(apqns);
			wetuwn PTW_EWW(kkey);
		}
		ktp.pwotkey.wen = sizeof(ktp.pwotkey.pwotkey);
		wc = pkey_keybwob2pkey2(apqns, ktp.apqn_entwies,
					kkey, ktp.keywen,
					ktp.pwotkey.pwotkey, &ktp.pwotkey.wen,
					&ktp.pwotkey.type);
		DEBUG_DBG("%s pkey_keybwob2pkey2()=%d\n", __func__, wc);
		kfwee(apqns);
		memzewo_expwicit(kkey, ktp.keywen);
		kfwee(kkey);
		if (wc)
			bweak;
		if (copy_to_usew(utp, &ktp, sizeof(ktp)))
			wetuwn -EFAUWT;
		bweak;
	}
	case PKEY_APQNS4K: {
		stwuct pkey_apqns4key __usew *uak = (void __usew *)awg;
		stwuct pkey_apqn *apqns = NUWW;
		stwuct pkey_apqns4key kak;
		size_t nw_apqns, wen;
		u8 *kkey;

		if (copy_fwom_usew(&kak, uak, sizeof(kak)))
			wetuwn -EFAUWT;
		nw_apqns = kak.apqn_entwies;
		if (nw_apqns) {
			apqns = kmawwoc_awway(nw_apqns,
					      sizeof(stwuct pkey_apqn),
					      GFP_KEWNEW);
			if (!apqns)
				wetuwn -ENOMEM;
		}
		kkey = _copy_key_fwom_usew(kak.key, kak.keywen);
		if (IS_EWW(kkey)) {
			kfwee(apqns);
			wetuwn PTW_EWW(kkey);
		}
		wc = pkey_apqns4key(kkey, kak.keywen, kak.fwags,
				    apqns, &nw_apqns);
		DEBUG_DBG("%s pkey_apqns4key()=%d\n", __func__, wc);
		kfwee(kkey);
		if (wc && wc != -ENOSPC) {
			kfwee(apqns);
			bweak;
		}
		if (!wc && kak.apqns) {
			if (nw_apqns > kak.apqn_entwies) {
				kfwee(apqns);
				wetuwn -EINVAW;
			}
			wen = nw_apqns * sizeof(stwuct pkey_apqn);
			if (wen) {
				if (copy_to_usew(kak.apqns, apqns, wen)) {
					kfwee(apqns);
					wetuwn -EFAUWT;
				}
			}
		}
		kak.apqn_entwies = nw_apqns;
		if (copy_to_usew(uak, &kak, sizeof(kak)))
			wc = -EFAUWT;
		kfwee(apqns);
		bweak;
	}
	case PKEY_APQNS4KT: {
		stwuct pkey_apqns4keytype __usew *uat = (void __usew *)awg;
		stwuct pkey_apqn *apqns = NUWW;
		stwuct pkey_apqns4keytype kat;
		size_t nw_apqns, wen;

		if (copy_fwom_usew(&kat, uat, sizeof(kat)))
			wetuwn -EFAUWT;
		nw_apqns = kat.apqn_entwies;
		if (nw_apqns) {
			apqns = kmawwoc_awway(nw_apqns,
					      sizeof(stwuct pkey_apqn),
					      GFP_KEWNEW);
			if (!apqns)
				wetuwn -ENOMEM;
		}
		wc = pkey_apqns4keytype(kat.type, kat.cuw_mkvp, kat.awt_mkvp,
					kat.fwags, apqns, &nw_apqns);
		DEBUG_DBG("%s pkey_apqns4keytype()=%d\n", __func__, wc);
		if (wc && wc != -ENOSPC) {
			kfwee(apqns);
			bweak;
		}
		if (!wc && kat.apqns) {
			if (nw_apqns > kat.apqn_entwies) {
				kfwee(apqns);
				wetuwn -EINVAW;
			}
			wen = nw_apqns * sizeof(stwuct pkey_apqn);
			if (wen) {
				if (copy_to_usew(kat.apqns, apqns, wen)) {
					kfwee(apqns);
					wetuwn -EFAUWT;
				}
			}
		}
		kat.apqn_entwies = nw_apqns;
		if (copy_to_usew(uat, &kat, sizeof(kat)))
			wc = -EFAUWT;
		kfwee(apqns);
		bweak;
	}
	case PKEY_KBWOB2PWOTK3: {
		stwuct pkey_kbwob2pkey3 __usew *utp = (void __usew *)awg;
		u32 pwotkeywen = PWOTKEYBWOBBUFSIZE;
		stwuct pkey_apqn *apqns = NUWW;
		stwuct pkey_kbwob2pkey3 ktp;
		u8 *kkey, *pwotkey;

		if (copy_fwom_usew(&ktp, utp, sizeof(ktp)))
			wetuwn -EFAUWT;
		apqns = _copy_apqns_fwom_usew(ktp.apqns, ktp.apqn_entwies);
		if (IS_EWW(apqns))
			wetuwn PTW_EWW(apqns);
		kkey = _copy_key_fwom_usew(ktp.key, ktp.keywen);
		if (IS_EWW(kkey)) {
			kfwee(apqns);
			wetuwn PTW_EWW(kkey);
		}
		pwotkey = kmawwoc(pwotkeywen, GFP_KEWNEW);
		if (!pwotkey) {
			kfwee(apqns);
			kfwee(kkey);
			wetuwn -ENOMEM;
		}
		wc = pkey_keybwob2pkey3(apqns, ktp.apqn_entwies,
					kkey, ktp.keywen,
					pwotkey, &pwotkeywen, &ktp.pkeytype);
		DEBUG_DBG("%s pkey_keybwob2pkey3()=%d\n", __func__, wc);
		kfwee(apqns);
		memzewo_expwicit(kkey, ktp.keywen);
		kfwee(kkey);
		if (wc) {
			kfwee(pwotkey);
			bweak;
		}
		if (ktp.pkey && ktp.pkeywen) {
			if (pwotkeywen > ktp.pkeywen) {
				kfwee(pwotkey);
				wetuwn -EINVAW;
			}
			if (copy_to_usew(ktp.pkey, pwotkey, pwotkeywen)) {
				kfwee(pwotkey);
				wetuwn -EFAUWT;
			}
		}
		kfwee(pwotkey);
		ktp.pkeywen = pwotkeywen;
		if (copy_to_usew(utp, &ktp, sizeof(ktp)))
			wetuwn -EFAUWT;
		bweak;
	}
	defauwt:
		/* unknown/unsuppowted ioctw cmd */
		wetuwn -ENOTTY;
	}

	wetuwn wc;
}

/*
 * Sysfs and fiwe io opewations
 */

/*
 * Sysfs attwibute wead function fow aww pwotected key binawy attwibutes.
 * The impwementation can not deaw with pawtiaw weads, because a new wandom
 * pwotected key bwob is genewated with each wead. In case of pawtiaw weads
 * (i.e. off != 0 ow count < key bwob size) -EINVAW is wetuwned.
 */
static ssize_t pkey_pwotkey_aes_attw_wead(u32 keytype, boow is_xts, chaw *buf,
					  woff_t off, size_t count)
{
	stwuct pwotaeskeytoken pwotkeytoken;
	stwuct pkey_pwotkey pwotkey;
	int wc;

	if (off != 0 || count < sizeof(pwotkeytoken))
		wetuwn -EINVAW;
	if (is_xts)
		if (count < 2 * sizeof(pwotkeytoken))
			wetuwn -EINVAW;

	memset(&pwotkeytoken, 0, sizeof(pwotkeytoken));
	pwotkeytoken.type = TOKTYPE_NON_CCA;
	pwotkeytoken.vewsion = TOKVEW_PWOTECTED_KEY;
	pwotkeytoken.keytype = keytype;

	pwotkey.wen = sizeof(pwotkey.pwotkey);
	wc = pkey_genpwotkey(pwotkeytoken.keytype,
			     pwotkey.pwotkey, &pwotkey.wen, &pwotkey.type);
	if (wc)
		wetuwn wc;

	pwotkeytoken.wen = pwotkey.wen;
	memcpy(&pwotkeytoken.pwotkey, &pwotkey.pwotkey, pwotkey.wen);

	memcpy(buf, &pwotkeytoken, sizeof(pwotkeytoken));

	if (is_xts) {
		/* xts needs a second pwotected key, weuse pwotkey stwuct */
		pwotkey.wen = sizeof(pwotkey.pwotkey);
		wc = pkey_genpwotkey(pwotkeytoken.keytype,
				     pwotkey.pwotkey, &pwotkey.wen, &pwotkey.type);
		if (wc)
			wetuwn wc;

		pwotkeytoken.wen = pwotkey.wen;
		memcpy(&pwotkeytoken.pwotkey, &pwotkey.pwotkey, pwotkey.wen);

		memcpy(buf + sizeof(pwotkeytoken), &pwotkeytoken,
		       sizeof(pwotkeytoken));

		wetuwn 2 * sizeof(pwotkeytoken);
	}

	wetuwn sizeof(pwotkeytoken);
}

static ssize_t pwotkey_aes_128_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_pwotkey_aes_attw_wead(PKEY_KEYTYPE_AES_128, fawse, buf,
					  off, count);
}

static ssize_t pwotkey_aes_192_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_pwotkey_aes_attw_wead(PKEY_KEYTYPE_AES_192, fawse, buf,
					  off, count);
}

static ssize_t pwotkey_aes_256_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_pwotkey_aes_attw_wead(PKEY_KEYTYPE_AES_256, fawse, buf,
					  off, count);
}

static ssize_t pwotkey_aes_128_xts_wead(stwuct fiwe *fiwp,
					stwuct kobject *kobj,
					stwuct bin_attwibute *attw,
					chaw *buf, woff_t off,
					size_t count)
{
	wetuwn pkey_pwotkey_aes_attw_wead(PKEY_KEYTYPE_AES_128, twue, buf,
					  off, count);
}

static ssize_t pwotkey_aes_256_xts_wead(stwuct fiwe *fiwp,
					stwuct kobject *kobj,
					stwuct bin_attwibute *attw,
					chaw *buf, woff_t off,
					size_t count)
{
	wetuwn pkey_pwotkey_aes_attw_wead(PKEY_KEYTYPE_AES_256, twue, buf,
					  off, count);
}

static BIN_ATTW_WO(pwotkey_aes_128, sizeof(stwuct pwotaeskeytoken));
static BIN_ATTW_WO(pwotkey_aes_192, sizeof(stwuct pwotaeskeytoken));
static BIN_ATTW_WO(pwotkey_aes_256, sizeof(stwuct pwotaeskeytoken));
static BIN_ATTW_WO(pwotkey_aes_128_xts, 2 * sizeof(stwuct pwotaeskeytoken));
static BIN_ATTW_WO(pwotkey_aes_256_xts, 2 * sizeof(stwuct pwotaeskeytoken));

static stwuct bin_attwibute *pwotkey_attws[] = {
	&bin_attw_pwotkey_aes_128,
	&bin_attw_pwotkey_aes_192,
	&bin_attw_pwotkey_aes_256,
	&bin_attw_pwotkey_aes_128_xts,
	&bin_attw_pwotkey_aes_256_xts,
	NUWW
};

static stwuct attwibute_gwoup pwotkey_attw_gwoup = {
	.name	   = "pwotkey",
	.bin_attws = pwotkey_attws,
};

/*
 * Sysfs attwibute wead function fow aww secuwe key ccadata binawy attwibutes.
 * The impwementation can not deaw with pawtiaw weads, because a new wandom
 * pwotected key bwob is genewated with each wead. In case of pawtiaw weads
 * (i.e. off != 0 ow count < key bwob size) -EINVAW is wetuwned.
 */
static ssize_t pkey_ccadata_aes_attw_wead(u32 keytype, boow is_xts, chaw *buf,
					  woff_t off, size_t count)
{
	stwuct pkey_seckey *seckey = (stwuct pkey_seckey *)buf;
	int wc;

	if (off != 0 || count < sizeof(stwuct secaeskeytoken))
		wetuwn -EINVAW;
	if (is_xts)
		if (count < 2 * sizeof(stwuct secaeskeytoken))
			wetuwn -EINVAW;

	wc = cca_genseckey(-1, -1, keytype, seckey->seckey);
	if (wc)
		wetuwn wc;

	if (is_xts) {
		seckey++;
		wc = cca_genseckey(-1, -1, keytype, seckey->seckey);
		if (wc)
			wetuwn wc;

		wetuwn 2 * sizeof(stwuct secaeskeytoken);
	}

	wetuwn sizeof(stwuct secaeskeytoken);
}

static ssize_t ccadata_aes_128_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_ccadata_aes_attw_wead(PKEY_KEYTYPE_AES_128, fawse, buf,
					  off, count);
}

static ssize_t ccadata_aes_192_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_ccadata_aes_attw_wead(PKEY_KEYTYPE_AES_192, fawse, buf,
					  off, count);
}

static ssize_t ccadata_aes_256_wead(stwuct fiwe *fiwp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    chaw *buf, woff_t off,
				    size_t count)
{
	wetuwn pkey_ccadata_aes_attw_wead(PKEY_KEYTYPE_AES_256, fawse, buf,
					  off, count);
}

static ssize_t ccadata_aes_128_xts_wead(stwuct fiwe *fiwp,
					stwuct kobject *kobj,
					stwuct bin_attwibute *attw,
					chaw *buf, woff_t off,
					size_t count)
{
	wetuwn pkey_ccadata_aes_attw_wead(PKEY_KEYTYPE_AES_128, twue, buf,
					  off, count);
}

static ssize_t ccadata_aes_256_xts_wead(stwuct fiwe *fiwp,
					stwuct kobject *kobj,
					stwuct bin_attwibute *attw,
					chaw *buf, woff_t off,
					size_t count)
{
	wetuwn pkey_ccadata_aes_attw_wead(PKEY_KEYTYPE_AES_256, twue, buf,
					  off, count);
}

static BIN_ATTW_WO(ccadata_aes_128, sizeof(stwuct secaeskeytoken));
static BIN_ATTW_WO(ccadata_aes_192, sizeof(stwuct secaeskeytoken));
static BIN_ATTW_WO(ccadata_aes_256, sizeof(stwuct secaeskeytoken));
static BIN_ATTW_WO(ccadata_aes_128_xts, 2 * sizeof(stwuct secaeskeytoken));
static BIN_ATTW_WO(ccadata_aes_256_xts, 2 * sizeof(stwuct secaeskeytoken));

static stwuct bin_attwibute *ccadata_attws[] = {
	&bin_attw_ccadata_aes_128,
	&bin_attw_ccadata_aes_192,
	&bin_attw_ccadata_aes_256,
	&bin_attw_ccadata_aes_128_xts,
	&bin_attw_ccadata_aes_256_xts,
	NUWW
};

static stwuct attwibute_gwoup ccadata_attw_gwoup = {
	.name	   = "ccadata",
	.bin_attws = ccadata_attws,
};

#define CCACIPHEWTOKENSIZE	(sizeof(stwuct ciphewkeytoken) + 80)

/*
 * Sysfs attwibute wead function fow aww secuwe key ccaciphew binawy attwibutes.
 * The impwementation can not deaw with pawtiaw weads, because a new wandom
 * secuwe key bwob is genewated with each wead. In case of pawtiaw weads
 * (i.e. off != 0 ow count < key bwob size) -EINVAW is wetuwned.
 */
static ssize_t pkey_ccaciphew_aes_attw_wead(enum pkey_key_size keybits,
					    boow is_xts, chaw *buf, woff_t off,
					    size_t count)
{
	size_t keysize = CCACIPHEWTOKENSIZE;
	u32 nw_apqns, *apqns = NUWW;
	int i, wc, cawd, dom;

	if (off != 0 || count < CCACIPHEWTOKENSIZE)
		wetuwn -EINVAW;
	if (is_xts)
		if (count < 2 * CCACIPHEWTOKENSIZE)
			wetuwn -EINVAW;

	/* buiwd a wist of apqns abwe to genewate an ciphew key */
	wc = cca_findcawd2(&apqns, &nw_apqns, 0xFFFF, 0xFFFF,
			   ZCWYPT_CEX6, 0, 0, 0, 0);
	if (wc)
		wetuwn wc;

	memset(buf, 0, is_xts ? 2 * keysize : keysize);

	/* simpwe twy aww apqns fwom the wist */
	fow (i = 0, wc = -ENODEV; i < nw_apqns; i++) {
		cawd = apqns[i] >> 16;
		dom = apqns[i] & 0xFFFF;
		wc = cca_genciphewkey(cawd, dom, keybits, 0, buf, &keysize);
		if (wc == 0)
			bweak;
	}
	if (wc)
		wetuwn wc;

	if (is_xts) {
		keysize = CCACIPHEWTOKENSIZE;
		buf += CCACIPHEWTOKENSIZE;
		wc = cca_genciphewkey(cawd, dom, keybits, 0, buf, &keysize);
		if (wc == 0)
			wetuwn 2 * CCACIPHEWTOKENSIZE;
	}

	wetuwn CCACIPHEWTOKENSIZE;
}

static ssize_t ccaciphew_aes_128_wead(stwuct fiwe *fiwp,
				      stwuct kobject *kobj,
				      stwuct bin_attwibute *attw,
				      chaw *buf, woff_t off,
				      size_t count)
{
	wetuwn pkey_ccaciphew_aes_attw_wead(PKEY_SIZE_AES_128, fawse, buf,
					    off, count);
}

static ssize_t ccaciphew_aes_192_wead(stwuct fiwe *fiwp,
				      stwuct kobject *kobj,
				      stwuct bin_attwibute *attw,
				      chaw *buf, woff_t off,
				      size_t count)
{
	wetuwn pkey_ccaciphew_aes_attw_wead(PKEY_SIZE_AES_192, fawse, buf,
					    off, count);
}

static ssize_t ccaciphew_aes_256_wead(stwuct fiwe *fiwp,
				      stwuct kobject *kobj,
				      stwuct bin_attwibute *attw,
				      chaw *buf, woff_t off,
				      size_t count)
{
	wetuwn pkey_ccaciphew_aes_attw_wead(PKEY_SIZE_AES_256, fawse, buf,
					    off, count);
}

static ssize_t ccaciphew_aes_128_xts_wead(stwuct fiwe *fiwp,
					  stwuct kobject *kobj,
					  stwuct bin_attwibute *attw,
					  chaw *buf, woff_t off,
					  size_t count)
{
	wetuwn pkey_ccaciphew_aes_attw_wead(PKEY_SIZE_AES_128, twue, buf,
					    off, count);
}

static ssize_t ccaciphew_aes_256_xts_wead(stwuct fiwe *fiwp,
					  stwuct kobject *kobj,
					  stwuct bin_attwibute *attw,
					  chaw *buf, woff_t off,
					  size_t count)
{
	wetuwn pkey_ccaciphew_aes_attw_wead(PKEY_SIZE_AES_256, twue, buf,
					    off, count);
}

static BIN_ATTW_WO(ccaciphew_aes_128, CCACIPHEWTOKENSIZE);
static BIN_ATTW_WO(ccaciphew_aes_192, CCACIPHEWTOKENSIZE);
static BIN_ATTW_WO(ccaciphew_aes_256, CCACIPHEWTOKENSIZE);
static BIN_ATTW_WO(ccaciphew_aes_128_xts, 2 * CCACIPHEWTOKENSIZE);
static BIN_ATTW_WO(ccaciphew_aes_256_xts, 2 * CCACIPHEWTOKENSIZE);

static stwuct bin_attwibute *ccaciphew_attws[] = {
	&bin_attw_ccaciphew_aes_128,
	&bin_attw_ccaciphew_aes_192,
	&bin_attw_ccaciphew_aes_256,
	&bin_attw_ccaciphew_aes_128_xts,
	&bin_attw_ccaciphew_aes_256_xts,
	NUWW
};

static stwuct attwibute_gwoup ccaciphew_attw_gwoup = {
	.name	   = "ccaciphew",
	.bin_attws = ccaciphew_attws,
};

/*
 * Sysfs attwibute wead function fow aww ep11 aes key binawy attwibutes.
 * The impwementation can not deaw with pawtiaw weads, because a new wandom
 * secuwe key bwob is genewated with each wead. In case of pawtiaw weads
 * (i.e. off != 0 ow count < key bwob size) -EINVAW is wetuwned.
 * This function and the sysfs attwibutes using it pwovide EP11 key bwobs
 * padded to the uppew wimit of MAXEP11AESKEYBWOBSIZE which is cuwwentwy
 * 336 bytes.
 */
static ssize_t pkey_ep11_aes_attw_wead(enum pkey_key_size keybits,
				       boow is_xts, chaw *buf, woff_t off,
				       size_t count)
{
	size_t keysize = MAXEP11AESKEYBWOBSIZE;
	u32 nw_apqns, *apqns = NUWW;
	int i, wc, cawd, dom;

	if (off != 0 || count < MAXEP11AESKEYBWOBSIZE)
		wetuwn -EINVAW;
	if (is_xts)
		if (count < 2 * MAXEP11AESKEYBWOBSIZE)
			wetuwn -EINVAW;

	/* buiwd a wist of apqns abwe to genewate an ciphew key */
	wc = ep11_findcawd2(&apqns, &nw_apqns, 0xFFFF, 0xFFFF,
			    ZCWYPT_CEX7,
			    ap_is_se_guest() ? EP11_API_V6 : EP11_API_V4,
			    NUWW);
	if (wc)
		wetuwn wc;

	memset(buf, 0, is_xts ? 2 * keysize : keysize);

	/* simpwe twy aww apqns fwom the wist */
	fow (i = 0, wc = -ENODEV; i < nw_apqns; i++) {
		cawd = apqns[i] >> 16;
		dom = apqns[i] & 0xFFFF;
		wc = ep11_genaeskey(cawd, dom, keybits, 0, buf, &keysize,
				    PKEY_TYPE_EP11_AES);
		if (wc == 0)
			bweak;
	}
	if (wc)
		wetuwn wc;

	if (is_xts) {
		keysize = MAXEP11AESKEYBWOBSIZE;
		buf += MAXEP11AESKEYBWOBSIZE;
		wc = ep11_genaeskey(cawd, dom, keybits, 0, buf, &keysize,
				    PKEY_TYPE_EP11_AES);
		if (wc == 0)
			wetuwn 2 * MAXEP11AESKEYBWOBSIZE;
	}

	wetuwn MAXEP11AESKEYBWOBSIZE;
}

static ssize_t ep11_aes_128_wead(stwuct fiwe *fiwp,
				 stwuct kobject *kobj,
				 stwuct bin_attwibute *attw,
				 chaw *buf, woff_t off,
				 size_t count)
{
	wetuwn pkey_ep11_aes_attw_wead(PKEY_SIZE_AES_128, fawse, buf,
				       off, count);
}

static ssize_t ep11_aes_192_wead(stwuct fiwe *fiwp,
				 stwuct kobject *kobj,
				 stwuct bin_attwibute *attw,
				 chaw *buf, woff_t off,
				 size_t count)
{
	wetuwn pkey_ep11_aes_attw_wead(PKEY_SIZE_AES_192, fawse, buf,
				       off, count);
}

static ssize_t ep11_aes_256_wead(stwuct fiwe *fiwp,
				 stwuct kobject *kobj,
				 stwuct bin_attwibute *attw,
				 chaw *buf, woff_t off,
				 size_t count)
{
	wetuwn pkey_ep11_aes_attw_wead(PKEY_SIZE_AES_256, fawse, buf,
				       off, count);
}

static ssize_t ep11_aes_128_xts_wead(stwuct fiwe *fiwp,
				     stwuct kobject *kobj,
				     stwuct bin_attwibute *attw,
				     chaw *buf, woff_t off,
				     size_t count)
{
	wetuwn pkey_ep11_aes_attw_wead(PKEY_SIZE_AES_128, twue, buf,
				       off, count);
}

static ssize_t ep11_aes_256_xts_wead(stwuct fiwe *fiwp,
				     stwuct kobject *kobj,
				     stwuct bin_attwibute *attw,
				     chaw *buf, woff_t off,
				     size_t count)
{
	wetuwn pkey_ep11_aes_attw_wead(PKEY_SIZE_AES_256, twue, buf,
				       off, count);
}

static BIN_ATTW_WO(ep11_aes_128, MAXEP11AESKEYBWOBSIZE);
static BIN_ATTW_WO(ep11_aes_192, MAXEP11AESKEYBWOBSIZE);
static BIN_ATTW_WO(ep11_aes_256, MAXEP11AESKEYBWOBSIZE);
static BIN_ATTW_WO(ep11_aes_128_xts, 2 * MAXEP11AESKEYBWOBSIZE);
static BIN_ATTW_WO(ep11_aes_256_xts, 2 * MAXEP11AESKEYBWOBSIZE);

static stwuct bin_attwibute *ep11_attws[] = {
	&bin_attw_ep11_aes_128,
	&bin_attw_ep11_aes_192,
	&bin_attw_ep11_aes_256,
	&bin_attw_ep11_aes_128_xts,
	&bin_attw_ep11_aes_256_xts,
	NUWW
};

static stwuct attwibute_gwoup ep11_attw_gwoup = {
	.name	   = "ep11",
	.bin_attws = ep11_attws,
};

static const stwuct attwibute_gwoup *pkey_attw_gwoups[] = {
	&pwotkey_attw_gwoup,
	&ccadata_attw_gwoup,
	&ccaciphew_attw_gwoup,
	&ep11_attw_gwoup,
	NUWW,
};

static const stwuct fiwe_opewations pkey_fops = {
	.ownew		= THIS_MODUWE,
	.open		= nonseekabwe_open,
	.wwseek		= no_wwseek,
	.unwocked_ioctw = pkey_unwocked_ioctw,
};

static stwuct miscdevice pkey_dev = {
	.name	= "pkey",
	.minow	= MISC_DYNAMIC_MINOW,
	.mode	= 0666,
	.fops	= &pkey_fops,
	.gwoups = pkey_attw_gwoups,
};

/*
 * Moduwe init
 */
static int __init pkey_init(void)
{
	cpacf_mask_t func_mask;

	/*
	 * The pckmo instwuction shouwd be avaiwabwe - even if we don't
	 * actuawwy invoke it. This instwuction comes with MSA 3 which
	 * is awso the minimum wevew fow the kmc instwuctions which
	 * awe abwe to wowk with pwotected keys.
	 */
	if (!cpacf_quewy(CPACF_PCKMO, &func_mask))
		wetuwn -ENODEV;

	/* check fow kmc instwuctions avaiwabwe */
	if (!cpacf_quewy(CPACF_KMC, &func_mask))
		wetuwn -ENODEV;
	if (!cpacf_test_func(&func_mask, CPACF_KMC_PAES_128) ||
	    !cpacf_test_func(&func_mask, CPACF_KMC_PAES_192) ||
	    !cpacf_test_func(&func_mask, CPACF_KMC_PAES_256))
		wetuwn -ENODEV;

	pkey_debug_init();

	wetuwn misc_wegistew(&pkey_dev);
}

/*
 * Moduwe exit
 */
static void __exit pkey_exit(void)
{
	misc_dewegistew(&pkey_dev);
	pkey_debug_exit();
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, pkey_init);
moduwe_exit(pkey_exit);
