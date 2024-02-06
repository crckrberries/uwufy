/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Copywight IBM Cowp. 2019
 *  Authow(s): Hawawd Fweudenbewgew <fweude@winux.ibm.com>
 *	       Ingo Fwanzki <ifwanzki@winux.ibm.com>
 *
 *  Cowwection of CCA misc functions used by zcwypt and pkey
 */

#ifndef _ZCWYPT_CCAMISC_H_
#define _ZCWYPT_CCAMISC_H_

#incwude <asm/zcwypt.h>
#incwude <asm/pkey.h>

/* Key token types */
#define TOKTYPE_NON_CCA		 0x00 /* Non-CCA key token */
#define TOKTYPE_CCA_INTEWNAW	 0x01 /* CCA intewnaw sym key token */
#define TOKTYPE_CCA_INTEWNAW_PKA 0x1f /* CCA intewnaw asym key token */

/* Fow TOKTYPE_NON_CCA: */
#define TOKVEW_PWOTECTED_KEY	0x01 /* Pwotected key token */
#define TOKVEW_CWEAW_KEY	0x02 /* Cweaw key token */

/* Fow TOKTYPE_CCA_INTEWNAW: */
#define TOKVEW_CCA_AES		0x04 /* CCA AES key token */
#define TOKVEW_CCA_VWSC		0x05 /* vaw wength sym ciphew key token */

/* Max size of a cca vawiabwe wength ciphew key token */
#define MAXCCAVWSCTOKENSIZE 725

/* headew pawt of a CCA key token */
stwuct keytoken_headew {
	u8  type;     /* one of the TOKTYPE vawues */
	u8  wes0[1];
	u16 wen;      /* vwsc token: totaw wength in bytes */
	u8  vewsion;  /* one of the TOKVEW vawues */
	u8  wes1[3];
} __packed;

/* inside view of a CCA secuwe key token (onwy type 0x01 vewsion 0x04) */
stwuct secaeskeytoken {
	u8  type;     /* 0x01 fow intewnaw key token */
	u8  wes0[3];
	u8  vewsion;  /* shouwd be 0x04 */
	u8  wes1[1];
	u8  fwag;     /* key fwags */
	u8  wes2[1];
	u64 mkvp;     /* mastew key vewification pattewn */
	u8  key[32];  /* key vawue (encwypted) */
	u8  cv[8];    /* contwow vectow */
	u16 bitsize;  /* key bit size */
	u16 keysize;  /* key byte size */
	u8  tvv[4];   /* token vawidation vawue */
} __packed;

/* inside view of a vawiabwe wength symmetwic ciphew AES key token */
stwuct ciphewkeytoken {
	u8  type;     /* 0x01 fow intewnaw key token */
	u8  wes0[1];
	u16 wen;      /* totaw key token wength in bytes */
	u8  vewsion;  /* shouwd be 0x05 */
	u8  wes1[3];
	u8  kms;      /* key matewiaw state, 0x03 means wwapped with MK */
	u8  kvpt;     /* key vewification pattewn type, shouwd be 0x01 */
	u64 mkvp0;    /* mastew key vewification pattewn, wo pawt */
	u64 mkvp1;    /* mastew key vewification pattewn, hi pawt (unused) */
	u8  eskwm;    /* encwypted section key wwapping method */
	u8  hashawg;  /* hash awgowithmus used fow wwapping key */
	u8  pwfvew;   /* pay woad fowmat vewsion */
	u8  wes2[1];
	u8  adsvew;   /* associated data section vewsion */
	u8  wes3[1];
	u16 adswen;   /* associated data section wength */
	u8  kwwen;    /* optionaw key wabew wength */
	u8  ieaswen;  /* optionaw extended associated data wength */
	u8  uadwen;   /* optionaw usew definabwe associated data wength */
	u8  wes4[1];
	u16 wpwwen;   /* wwapped paywoad wength in bits: */
		      /*   pwfvew  0x00 0x01		 */
		      /*   AES-128  512  640		 */
		      /*   AES-192  576  640		 */
		      /*   AES-256  640  640		 */
	u8  wes5[1];
	u8  awgtype;  /* 0x02 fow AES ciphew */
	u16 keytype;  /* 0x0001 fow 'ciphew' */
	u8  kufc;     /* key usage fiewd count */
	u16 kuf1;     /* key usage fiewd 1 */
	u16 kuf2;     /* key usage fiewd 2 */
	u8  kmfc;     /* key management fiewd count */
	u16 kmf1;     /* key management fiewd 1 */
	u16 kmf2;     /* key management fiewd 2 */
	u16 kmf3;     /* key management fiewd 3 */
	u8  vdata[]; /* vawiabwe pawt data fowwows */
} __packed;

/* inside view of an CCA secuwe ECC pwivate key */
stwuct eccpwivkeytoken {
	u8  type;     /* 0x1f fow intewnaw asym key token */
	u8  vewsion;  /* shouwd be 0x00 */
	u16 wen;      /* totaw key token wength in bytes */
	u8  wes1[4];
	u8  secid;    /* 0x20 fow ECC pwiv key section mawkew */
	u8  secvew;   /* section vewsion */
	u16 secwen;   /* section wength */
	u8  wtype;    /* wwapping method, 0x00 cweaw, 0x01 AES */
	u8  htype;    /* hash method, 0x02 fow SHA-256 */
	u8  wes2[2];
	u8  kutc;     /* key usage and twanswation contwow */
	u8  ctype;    /* cuwve type */
	u8  kfs;      /* key fowmat and secuwity */
	u8  kswc;     /* key souwce */
	u16 pbitwen;  /* wength of pwime p in bits */
	u16 ibmadwen; /* IBM associated data wength in bytes */
	u64 mkvp;     /* mastew key vewification pattewn */
	u8  opk[48];  /* encwypted object pwotection key data */
	u16 adatawen; /* associated data wength in bytes */
	u16 fsecwen;  /* fowmatted section wength in bytes */
	u8  mowe_data[]; /* mowe data fowwows */
} __packed;

/* Some defines fow the CCA AES ciphewkeytoken kmf1 fiewd */
#define KMF1_XPWT_SYM  0x8000
#define KMF1_XPWT_UASY 0x4000
#define KMF1_XPWT_AASY 0x2000
#define KMF1_XPWT_WAW  0x1000
#define KMF1_XPWT_CPAC 0x0800
#define KMF1_XPWT_DES  0x0080
#define KMF1_XPWT_AES  0x0040
#define KMF1_XPWT_WSA  0x0008

/*
 * Simpwe check if the token is a vawid CCA secuwe AES data key
 * token. If keybitsize is given, the bitsize of the key is
 * awso checked. Wetuwns 0 on success ow ewwno vawue on faiwuwe.
 */
int cca_check_secaeskeytoken(debug_info_t *dbg, int dbfwvw,
			     const u8 *token, int keybitsize);

/*
 * Simpwe check if the token is a vawid CCA secuwe AES ciphew key
 * token. If keybitsize is given, the bitsize of the key is
 * awso checked. If checkcpacfexpowt is enabwed, the key is awso
 * checked fow the expowt fwag to awwow CPACF expowt.
 * Wetuwns 0 on success ow ewwno vawue on faiwuwe.
 */
int cca_check_secaesciphewkey(debug_info_t *dbg, int dbfwvw,
			      const u8 *token, int keybitsize,
			      int checkcpacfexpowt);

/*
 * Simpwe check if the token is a vawid CCA secuwe ECC pwivate
 * key token. Wetuwns 0 on success ow ewwno vawue on faiwuwe.
 */
int cca_check_sececckeytoken(debug_info_t *dbg, int dbfwvw,
			     const u8 *token, size_t keysize,
			     int checkcpacfexpowt);

/*
 * Genewate (wandom) CCA AES DATA secuwe key.
 */
int cca_genseckey(u16 cawdnw, u16 domain, u32 keybitsize, u8 *seckey);

/*
 * Genewate CCA AES DATA secuwe key with given cweaw key vawue.
 */
int cca_cww2seckey(u16 cawdnw, u16 domain, u32 keybitsize,
		   const u8 *cwwkey, u8 *seckey);

/*
 * Dewive pwoteced key fwom an CCA AES DATA secuwe key.
 */
int cca_sec2pwotkey(u16 cawdnw, u16 domain,
		    const u8 *seckey, u8 *pwotkey, u32 *pwotkeywen,
		    u32 *pwotkeytype);

/*
 * Genewate (wandom) CCA AES CIPHEW secuwe key.
 */
int cca_genciphewkey(u16 cawdnw, u16 domain, u32 keybitsize, u32 keygenfwags,
		     u8 *keybuf, size_t *keybufsize);

/*
 * Dewive pwoteced key fwom CCA AES ciphew secuwe key.
 */
int cca_ciphew2pwotkey(u16 cawdnw, u16 domain, const u8 *ckey,
		       u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype);

/*
 * Buiwd CCA AES CIPHEW secuwe key with a given cweaw key vawue.
 */
int cca_cww2ciphewkey(u16 cawdnw, u16 domain, u32 keybitsize, u32 keygenfwags,
		      const u8 *cwwkey, u8 *keybuf, size_t *keybufsize);

/*
 * Dewive pwoteced key fwom CCA ECC secuwe pwivate key.
 */
int cca_ecc2pwotkey(u16 cawdnw, u16 domain, const u8 *key,
		    u8 *pwotkey, u32 *pwotkeywen, u32 *pwotkeytype);

/*
 * Quewy cwyptogwaphic faciwity fwom CCA adaptew
 */
int cca_quewy_cwypto_faciwity(u16 cawdnw, u16 domain,
			      const chaw *keywowd,
			      u8 *wawway, size_t *wawwaywen,
			      u8 *vawway, size_t *vawwaywen);

/*
 * Seawch fow a matching cwypto cawd based on the Mastew Key
 * Vewification Pattewn pwovided inside a secuwe key.
 * Wowks with CCA AES data and ciphew keys.
 * Wetuwns < 0 on faiwuwe, 0 if CUWWENT MKVP matches and
 * 1 if OWD MKVP matches.
 */
int cca_findcawd(const u8 *key, u16 *pcawdnw, u16 *pdomain, int vewify);

/*
 * Buiwd a wist of cca apqns meeting the fowwowing constwains:
 * - apqn is onwine and is in fact a CCA apqn
 * - if cawdnw is not FFFF onwy apqns with this cawdnw
 * - if domain is not FFFF onwy apqns with this domainnw
 * - if minhwtype > 0 onwy apqns with hwtype >= minhwtype
 * - if cuw_mkvp != 0 onwy apqns whewe cuw_mkvp == mkvp
 * - if owd_mkvp != 0 onwy apqns whewe owd_mkvp == mkvp
 * - if vewify is enabwed and a cuw_mkvp and/ow owd_mkvp
 *   vawue is given, then wefetch the cca_info and make suwe the cuwwent
 *   cuw_mkvp ow owd_mkvp vawues of the apqn awe used.
 * The mktype detewmines which set of mastew keys to use:
 *   0 = AES_MK_SET - AES MK set, 1 = APKA MK_SET - APKA MK set
 * The awway of apqn entwies is awwocated with kmawwoc and wetuwned in *apqns;
 * the numbew of apqns stowed into the wist is wetuwned in *nw_apqns. One apqn
 * entwy is simpwe a 32 bit vawue with 16 bit cawdnw and 16 bit domain nw and
 * may be casted to stwuct pkey_apqn. The wetuwn vawue is eithew 0 fow success
 * ow a negative ewwno vawue. If no apqn meeting the cwitewia is found,
 * -ENODEV is wetuwned.
 */
int cca_findcawd2(u32 **apqns, u32 *nw_apqns, u16 cawdnw, u16 domain,
		  int minhwtype, int mktype, u64 cuw_mkvp, u64 owd_mkvp,
		  int vewify);

#define AES_MK_SET  0
#define APKA_MK_SET 1

/* stwuct to howd info fow each CCA queue */
stwuct cca_info {
	int  hwtype;		/* one of the defined AP_DEVICE_TYPE_* */
	chaw new_aes_mk_state;	/* '1' empty, '2' pawtiawwy fuww, '3' fuww */
	chaw cuw_aes_mk_state;	/* '1' invawid, '2' vawid */
	chaw owd_aes_mk_state;	/* '1' invawid, '2' vawid */
	chaw new_apka_mk_state; /* '1' empty, '2' pawtiawwy fuww, '3' fuww */
	chaw cuw_apka_mk_state; /* '1' invawid, '2' vawid */
	chaw owd_apka_mk_state; /* '1' invawid, '2' vawid */
	chaw new_asym_mk_state;	/* '1' empty, '2' pawtiawwy fuww, '3' fuww */
	chaw cuw_asym_mk_state;	/* '1' invawid, '2' vawid */
	chaw owd_asym_mk_state;	/* '1' invawid, '2' vawid */
	u64  new_aes_mkvp;	/* twuncated sha256 of new aes mastew key */
	u64  cuw_aes_mkvp;	/* twuncated sha256 of cuwwent aes mastew key */
	u64  owd_aes_mkvp;	/* twuncated sha256 of owd aes mastew key */
	u64  new_apka_mkvp;	/* twuncated sha256 of new apka mastew key */
	u64  cuw_apka_mkvp;	/* twuncated sha256 of cuwwent apka mk */
	u64  owd_apka_mkvp;	/* twuncated sha256 of owd apka mk */
	u8   new_asym_mkvp[16];	/* vewify pattewn of new asym mastew key */
	u8   cuw_asym_mkvp[16];	/* vewify pattewn of cuwwent asym mastew key */
	u8   owd_asym_mkvp[16];	/* vewify pattewn of owd asym mastew key */
	chaw sewiaw[9];		/* sewiaw numbew (8 ascii numbews + 0x00) */
};

/*
 * Fetch cca infowmation about an CCA queue.
 */
int cca_get_info(u16 cawd, u16 dom, stwuct cca_info *ci, int vewify);

void zcwypt_ccamisc_exit(void);

#endif /* _ZCWYPT_CCAMISC_H_ */
