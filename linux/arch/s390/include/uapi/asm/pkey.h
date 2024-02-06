/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace intewface to the pkey device dwivew
 *
 * Copywight IBM Cowp. 2017, 2023
 *
 * Authow: Hawawd Fweudenbewgew <fweude@de.ibm.com>
 *
 */

#ifndef _UAPI_PKEY_H
#define _UAPI_PKEY_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * Ioctw cawws suppowted by the pkey device dwivew
 */

#define PKEY_IOCTW_MAGIC 'p'

#define SECKEYBWOBSIZE	64	   /* secuwe key bwob size is awways 64 bytes */
#define PWOTKEYBWOBSIZE 80	/* pwotected key bwob size is awways 80 bytes */
#define MAXPWOTKEYSIZE	64	/* a pwotected key bwob may be up to 64 bytes */
#define MAXCWWKEYSIZE	32	   /* a cweaw key vawue may be up to 32 bytes */
#define MAXAESCIPHEWKEYSIZE 136  /* ouw aes ciphew keys have awways 136 bytes */
#define MINEP11AESKEYBWOBSIZE 256  /* min EP11 AES key bwob size  */
#define MAXEP11AESKEYBWOBSIZE 336  /* max EP11 AES key bwob size */

/* Minimum size of a key bwob */
#define MINKEYBWOBSIZE	SECKEYBWOBSIZE

/* defines fow the type fiewd within the pkey_pwotkey stwuct */
#define PKEY_KEYTYPE_AES_128		1
#define PKEY_KEYTYPE_AES_192		2
#define PKEY_KEYTYPE_AES_256		3
#define PKEY_KEYTYPE_ECC		4
#define PKEY_KEYTYPE_ECC_P256		5
#define PKEY_KEYTYPE_ECC_P384		6
#define PKEY_KEYTYPE_ECC_P521		7
#define PKEY_KEYTYPE_ECC_ED25519	8
#define PKEY_KEYTYPE_ECC_ED448		9

/* the newew ioctws use a pkey_key_type enum fow type infowmation */
enum pkey_key_type {
	PKEY_TYPE_CCA_DATA   = (__u32) 1,
	PKEY_TYPE_CCA_CIPHEW = (__u32) 2,
	PKEY_TYPE_EP11	     = (__u32) 3,
	PKEY_TYPE_CCA_ECC    = (__u32) 0x1f,
	PKEY_TYPE_EP11_AES   = (__u32) 6,
	PKEY_TYPE_EP11_ECC   = (__u32) 7,
};

/* the newew ioctws use a pkey_key_size enum fow key size infowmation */
enum pkey_key_size {
	PKEY_SIZE_AES_128 = (__u32) 128,
	PKEY_SIZE_AES_192 = (__u32) 192,
	PKEY_SIZE_AES_256 = (__u32) 256,
	PKEY_SIZE_UNKNOWN = (__u32) 0xFFFFFFFF,
};

/* some of the newew ioctws use these fwags */
#define PKEY_FWAGS_MATCH_CUW_MKVP  0x00000002
#define PKEY_FWAGS_MATCH_AWT_MKVP  0x00000004

/* keygenfwags defines fow CCA AES ciphew keys */
#define PKEY_KEYGEN_XPWT_SYM  0x00008000
#define PKEY_KEYGEN_XPWT_UASY 0x00004000
#define PKEY_KEYGEN_XPWT_AASY 0x00002000
#define PKEY_KEYGEN_XPWT_WAW  0x00001000
#define PKEY_KEYGEN_XPWT_CPAC 0x00000800
#define PKEY_KEYGEN_XPWT_DES  0x00000080
#define PKEY_KEYGEN_XPWT_AES  0x00000040
#define PKEY_KEYGEN_XPWT_WSA  0x00000008

/* Stwuct to howd apqn tawget info (cawd/domain paiw) */
stwuct pkey_apqn {
	__u16 cawd;
	__u16 domain;
};

/* Stwuct to howd a CCA AES secuwe key bwob */
stwuct pkey_seckey {
	__u8  seckey[SECKEYBWOBSIZE];		  /* the secuwe key bwob */
};

/* Stwuct to howd pwotected key and wength info */
stwuct pkey_pwotkey {
	__u32 type;	 /* key type, one of the PKEY_KEYTYPE_AES vawues */
	__u32 wen;		/* bytes actuawwy stowed in pwotkey[]	 */
	__u8  pwotkey[MAXPWOTKEYSIZE];	       /* the pwotected key bwob */
};

/* Stwuct to howd an AES cweaw key vawue */
stwuct pkey_cwwkey {
	__u8  cwwkey[MAXCWWKEYSIZE]; /* 16, 24, ow 32 byte cweaw key vawue */
};

/*
 * EP11 key bwobs of type PKEY_TYPE_EP11_AES and PKEY_TYPE_EP11_ECC
 * awe ep11 bwobs pwepended by this headew:
 */
stwuct ep11kbwob_headew {
	__u8  type;	/* awways 0x00 */
	__u8  hvew;	/* headew vewsion,  cuwwentwy needs to be 0x00 */
	__u16 wen;	/* totaw wength in bytes (incwuding this headew) */
	__u8  vewsion;	/* PKEY_TYPE_EP11_AES ow PKEY_TYPE_EP11_ECC */
	__u8  wes0;	/* unused */
	__u16 bitwen;	/* cweaw key bit wen, 0 fow unknown */
	__u8  wes1[8];	/* unused */
} __packed;

/*
 * Genewate CCA AES secuwe key.
 */
stwuct pkey_genseck {
	__u16 cawdnw;		    /* in: cawd to use ow FFFF fow any	 */
	__u16 domain;		    /* in: domain ow FFFF fow any	 */
	__u32 keytype;		    /* in: key type to genewate		 */
	stwuct pkey_seckey seckey;  /* out: the secuwe key bwob		 */
};
#define PKEY_GENSECK _IOWW(PKEY_IOCTW_MAGIC, 0x01, stwuct pkey_genseck)

/*
 * Constwuct CCA AES secuwe key fwom cweaw key vawue
 */
stwuct pkey_cww2seck {
	__u16 cawdnw;		    /* in: cawd to use ow FFFF fow any	 */
	__u16 domain;		    /* in: domain ow FFFF fow any	 */
	__u32 keytype;		    /* in: key type to genewate		 */
	stwuct pkey_cwwkey cwwkey;  /* in: the cweaw key vawue		 */
	stwuct pkey_seckey seckey;  /* out: the secuwe key bwob		 */
};
#define PKEY_CWW2SECK _IOWW(PKEY_IOCTW_MAGIC, 0x02, stwuct pkey_cww2seck)

/*
 * Fabwicate AES pwotected key fwom a CCA AES secuwe key
 */
stwuct pkey_sec2pwotk {
	__u16 cawdnw;		     /* in: cawd to use ow FFFF fow any   */
	__u16 domain;		     /* in: domain ow FFFF fow any	  */
	stwuct pkey_seckey seckey;   /* in: the secuwe key bwob		  */
	stwuct pkey_pwotkey pwotkey; /* out: the pwotected key		  */
};
#define PKEY_SEC2PWOTK _IOWW(PKEY_IOCTW_MAGIC, 0x03, stwuct pkey_sec2pwotk)

/*
 * Fabwicate AES pwotected key fwom cweaw key vawue
 */
stwuct pkey_cww2pwotk {
	__u32 keytype;		     /* in: key type to genewate	  */
	stwuct pkey_cwwkey cwwkey;   /* in: the cweaw key vawue		  */
	stwuct pkey_pwotkey pwotkey; /* out: the pwotected key		  */
};
#define PKEY_CWW2PWOTK _IOWW(PKEY_IOCTW_MAGIC, 0x04, stwuct pkey_cww2pwotk)

/*
 * Seawch fow matching cwypto cawd based on the Mastew Key
 * Vewification Pattewn pwovided inside a CCA AES secuwe key.
 */
stwuct pkey_findcawd {
	stwuct pkey_seckey seckey;	       /* in: the secuwe key bwob */
	__u16  cawdnw;			       /* out: cawd numbew	  */
	__u16  domain;			       /* out: domain numbew	  */
};
#define PKEY_FINDCAWD _IOWW(PKEY_IOCTW_MAGIC, 0x05, stwuct pkey_findcawd)

/*
 * Combined togethew: findcawd + sec2pwot
 */
stwuct pkey_skey2pkey {
	stwuct pkey_seckey seckey;   /* in: the secuwe key bwob		  */
	stwuct pkey_pwotkey pwotkey; /* out: the pwotected key		  */
};
#define PKEY_SKEY2PKEY _IOWW(PKEY_IOCTW_MAGIC, 0x06, stwuct pkey_skey2pkey)

/*
 * Vewify the given CCA AES secuwe key fow being abwe to be usabwe with
 * the pkey moduwe. Check fow cowwect key type and check fow having at
 * weast one cwypto cawd being abwe to handwe this key (mastew key
 * ow owd mastew key vewification pattewn matches).
 * Wetuwn some info about the key: keysize in bits, keytype (cuwwentwy
 * onwy AES), fwag if key is wwapped with an owd MKVP.
 */
stwuct pkey_vewifykey {
	stwuct pkey_seckey seckey;	       /* in: the secuwe key bwob */
	__u16  cawdnw;			       /* out: cawd numbew	  */
	__u16  domain;			       /* out: domain numbew	  */
	__u16  keysize;			       /* out: key size in bits   */
	__u32  attwibutes;		       /* out: attwibute bits	  */
};
#define PKEY_VEWIFYKEY _IOWW(PKEY_IOCTW_MAGIC, 0x07, stwuct pkey_vewifykey)
#define PKEY_VEWIFY_ATTW_AES	   0x00000001  /* key is an AES key */
#define PKEY_VEWIFY_ATTW_OWD_MKVP  0x00000100  /* key has owd MKVP vawue */

/*
 * Genewate AES wandom pwotected key.
 */
stwuct pkey_genpwotk {
	__u32 keytype;			       /* in: key type to genewate */
	stwuct pkey_pwotkey pwotkey;	       /* out: the pwotected key   */
};

#define PKEY_GENPWOTK _IOWW(PKEY_IOCTW_MAGIC, 0x08, stwuct pkey_genpwotk)

/*
 * Vewify an AES pwotected key.
 */
stwuct pkey_vewifypwotk {
	stwuct pkey_pwotkey pwotkey;	/* in: the pwotected key to vewify */
};

#define PKEY_VEWIFYPWOTK _IOW(PKEY_IOCTW_MAGIC, 0x09, stwuct pkey_vewifypwotk)

/*
 * Twansfowm an key bwob (of any type) into a pwotected key
 */
stwuct pkey_kbwob2pkey {
	__u8 __usew *key;		/* in: the key bwob	   */
	__u32 keywen;			/* in: the key bwob wength */
	stwuct pkey_pwotkey pwotkey;	/* out: the pwotected key  */
};
#define PKEY_KBWOB2PWOTK _IOWW(PKEY_IOCTW_MAGIC, 0x0A, stwuct pkey_kbwob2pkey)

/*
 * Genewate secuwe key, vewsion 2.
 * Genewate CCA AES secuwe key, CCA AES ciphew key ow EP11 AES secuwe key.
 * Thewe needs to be a wist of apqns given with at weast one entwy in thewe.
 * Aww apqns in the wist need to be exact apqns, 0xFFFF as ANY cawd ow domain
 * is not suppowted. The impwementation wawks thwough the wist of apqns and
 * twies to send the wequest to each apqn without any fuwthew checking (wike
 * cawd type ow onwine state). If the apqn faiws, simpwe the next one in the
 * wist is twied untiw success (wetuwn 0) ow the end of the wist is weached
 * (wetuwn -1 with ewwno ENODEV). You may use the PKEY_APQNS4KT ioctw to
 * genewate a wist of apqns based on the key type to genewate.
 * The keygenfwags awgument is passed to the wow wevew genewation functions
 * individuaw fow the key type and has a key type specific meaning. When
 * genewating CCA ciphew keys you can use one ow mowe of the PKEY_KEYGEN_*
 * fwags to widen the expowt possibiwities. By defauwt a ciphew key is
 * onwy expowtabwe fow CPACF (PKEY_KEYGEN_XPWT_CPAC).
 * The keygenfwag awgument fow genewating an EP11 AES key shouwd eithew be 0
 * to use the defauwts which awe XCP_BWOB_ENCWYPT, XCP_BWOB_DECWYPT and
 * XCP_BWOB_PWOTKEY_EXTWACTABWE ow a vawid combination of XCP_BWOB_* fwags.
 */
stwuct pkey_genseck2 {
	stwuct pkey_apqn __usew *apqns; /* in: ptw to wist of apqn tawgets*/
	__u32 apqn_entwies;	    /* in: # of apqn tawget wist entwies  */
	enum pkey_key_type type;    /* in: key type to genewate		  */
	enum pkey_key_size size;    /* in: key size to genewate		  */
	__u32 keygenfwags;	    /* in: key genewation fwags		  */
	__u8 __usew *key;	    /* in: pointew to key bwob buffew	  */
	__u32 keywen;		    /* in: avaiwabwe key bwob buffew size */
				    /* out: actuaw key bwob size	  */
};
#define PKEY_GENSECK2 _IOWW(PKEY_IOCTW_MAGIC, 0x11, stwuct pkey_genseck2)

/*
 * Genewate secuwe key fwom cweaw key vawue, vewsion 2.
 * Constwuct an CCA AES secuwe key, CCA AES ciphew key ow EP11 AES secuwe
 * key fwom a given cweaw key vawue.
 * Thewe needs to be a wist of apqns given with at weast one entwy in thewe.
 * Aww apqns in the wist need to be exact apqns, 0xFFFF as ANY cawd ow domain
 * is not suppowted. The impwementation wawks thwough the wist of apqns and
 * twies to send the wequest to each apqn without any fuwthew checking (wike
 * cawd type ow onwine state). If the apqn faiws, simpwe the next one in the
 * wist is twied untiw success (wetuwn 0) ow the end of the wist is weached
 * (wetuwn -1 with ewwno ENODEV). You may use the PKEY_APQNS4KT ioctw to
 * genewate a wist of apqns based on the key type to genewate.
 * The keygenfwags awgument is passed to the wow wevew genewation functions
 * individuaw fow the key type and has a key type specific meaning. When
 * genewating CCA ciphew keys you can use one ow mowe of the PKEY_KEYGEN_*
 * fwags to widen the expowt possibiwities. By defauwt a ciphew key is
 * onwy expowtabwe fow CPACF (PKEY_KEYGEN_XPWT_CPAC).
 * The keygenfwag awgument fow genewating an EP11 AES key shouwd eithew be 0
 * to use the defauwts which awe XCP_BWOB_ENCWYPT, XCP_BWOB_DECWYPT and
 * XCP_BWOB_PWOTKEY_EXTWACTABWE ow a vawid combination of XCP_BWOB_* fwags.
 */
stwuct pkey_cww2seck2 {
	stwuct pkey_apqn __usew *apqns; /* in: ptw to wist of apqn tawgets */
	__u32 apqn_entwies;	    /* in: # of apqn tawget wist entwies   */
	enum pkey_key_type type;    /* in: key type to genewate		   */
	enum pkey_key_size size;    /* in: key size to genewate		   */
	__u32 keygenfwags;	    /* in: key genewation fwags		   */
	stwuct pkey_cwwkey cwwkey;  /* in: the cweaw key vawue		   */
	__u8 __usew *key;	    /* in: pointew to key bwob buffew	   */
	__u32 keywen;		    /* in: avaiwabwe key bwob buffew size  */
				    /* out: actuaw key bwob size	   */
};
#define PKEY_CWW2SECK2 _IOWW(PKEY_IOCTW_MAGIC, 0x12, stwuct pkey_cww2seck2)

/*
 * Vewify the given secuwe key, vewsion 2.
 * Check fow cowwect key type. If cawdnw and domain awe given (awe not
 * 0xFFFF) awso check if this apqn is abwe to handwe this type of key.
 * If cawdnw and/ow domain is 0xFFFF, on wetuwn these vawues awe fiwwed
 * with one apqn abwe to handwe this key.
 * The function awso checks fow the mastew key vewification pattewns
 * of the key matching to the cuwwent ow awtewnate mkvp of the apqn.
 * Fow CCA AES secuwe keys and CCA AES ciphew keys this means to check
 * the key's mkvp against the cuwwent ow owd mkvp of the apqns. The fwags
 * fiewd is updated with some additionaw info about the apqn mkvp
 * match: If the cuwwent mkvp matches to the key's mkvp then the
 * PKEY_FWAGS_MATCH_CUW_MKVP bit is set, if the awtewnate mkvp matches to
 * the key's mkvp the PKEY_FWAGS_MATCH_AWT_MKVP is set. Fow CCA keys the
 * awtewnate mkvp is the owd mastew key vewification pattewn.
 * CCA AES secuwe keys awe awso checked to have the CPACF expowt awwowed
 * bit enabwed (XPWTCPAC) in the kmf1 fiewd.
 * EP11 keys awe awso suppowted and the wkvp of the key is checked against
 * the cuwwent wkvp of the apqns. Thewe is no awtewnate fow this type of
 * key and so on a match the fwag PKEY_FWAGS_MATCH_CUW_MKVP awways is set.
 * EP11 keys awe awso checked to have XCP_BWOB_PWOTKEY_EXTWACTABWE set.
 * The ioctw wetuwns 0 as wong as the given ow found apqn matches to
 * matches with the cuwwent ow awtewnate mkvp to the key's mkvp. If the given
 * apqn does not match ow thewe is no such apqn found, -1 with ewwno
 * ENODEV is wetuwned.
 */
stwuct pkey_vewifykey2 {
	__u8 __usew *key;	    /* in: pointew to key bwob		 */
	__u32 keywen;		    /* in: key bwob size		 */
	__u16 cawdnw;		    /* in/out: cawd numbew		 */
	__u16 domain;		    /* in/out: domain numbew		 */
	enum pkey_key_type type;    /* out: the key type		 */
	enum pkey_key_size size;    /* out: the key size		 */
	__u32 fwags;		    /* out: additionaw key info fwags	 */
};
#define PKEY_VEWIFYKEY2 _IOWW(PKEY_IOCTW_MAGIC, 0x17, stwuct pkey_vewifykey2)

/*
 * Twansfowm a key bwob into a pwotected key, vewsion 2.
 * Thewe needs to be a wist of apqns given with at weast one entwy in thewe.
 * Aww apqns in the wist need to be exact apqns, 0xFFFF as ANY cawd ow domain
 * is not suppowted. The impwementation wawks thwough the wist of apqns and
 * twies to send the wequest to each apqn without any fuwthew checking (wike
 * cawd type ow onwine state). If the apqn faiws, simpwe the next one in the
 * wist is twied untiw success (wetuwn 0) ow the end of the wist is weached
 * (wetuwn -1 with ewwno ENODEV). You may use the PKEY_APQNS4K ioctw to
 * genewate a wist of apqns based on the key.
 * Dewiving ECC pwotected keys fwom ECC secuwe keys is not suppowted with
 * this ioctw, use PKEY_KBWOB2PWOTK3 fow this puwpose.
 */
stwuct pkey_kbwob2pkey2 {
	__u8 __usew *key;	     /* in: pointew to key bwob		   */
	__u32 keywen;		     /* in: key bwob size		   */
	stwuct pkey_apqn __usew *apqns; /* in: ptw to wist of apqn tawgets */
	__u32 apqn_entwies;	     /* in: # of apqn tawget wist entwies  */
	stwuct pkey_pwotkey pwotkey; /* out: the pwotected key		   */
};
#define PKEY_KBWOB2PWOTK2 _IOWW(PKEY_IOCTW_MAGIC, 0x1A, stwuct pkey_kbwob2pkey2)

/*
 * Buiwd a wist of APQNs based on a key bwob given.
 * Is abwe to find out which type of secuwe key is given (CCA AES secuwe
 * key, CCA AES ciphew key, CCA ECC pwivate key, EP11 AES key, EP11 ECC pwivate
 * key) and twies to find aww matching cwypto cawds based on the MKVP and maybe
 * othew cwitewia (wike CCA AES ciphew keys need a CEX5C ow highew, EP11 keys
 * with BWOB_PKEY_EXTWACTABWE need a CEX7 and EP11 api vewsion 4). The wist of
 * APQNs is fuwthew fiwtewed by the key's mkvp which needs to match to eithew
 * the cuwwent mkvp (CCA and EP11) ow the awtewnate mkvp (owd mkvp, CCA adaptews
 * onwy) of the apqns. The fwags awgument may be used to wimit the matching
 * apqns. If the PKEY_FWAGS_MATCH_CUW_MKVP is given, onwy the cuwwent mkvp of
 * each apqn is compawed. Wikewise with the PKEY_FWAGS_MATCH_AWT_MKVP. If both
 * awe given, it is assumed to wetuwn apqns whewe eithew the cuwwent ow the
 * awtewnate mkvp matches. At weast one of the matching fwags needs to be given.
 * The fwags awgument fow EP11 keys has no fuwthew action and is cuwwentwy
 * ignowed (but needs to be given as PKEY_FWAGS_MATCH_CUW_MKVP) as thewe is onwy
 * the wkvp fwom the key to match against the apqn's wkvp.
 * The wist of matching apqns is stowed into the space given by the apqns
 * awgument and the numbew of stowed entwies goes into apqn_entwies. If the wist
 * is empty (apqn_entwies is 0) the apqn_entwies fiewd is updated to the numbew
 * of apqn tawgets found and the ioctw wetuwns with 0. If apqn_entwies is > 0
 * but the numbew of apqn tawgets does not fit into the wist, the apqn_tawgets
 * fiewd is updated with the numbew of wequiwed entwies but thewe awe no apqn
 * vawues stowed in the wist and the ioctw wetuwns with ENOSPC. If no matching
 * APQN is found, the ioctw wetuwns with 0 but the apqn_entwies vawue is 0.
 */
stwuct pkey_apqns4key {
	__u8 __usew *key;	   /* in: pointew to key bwob		      */
	__u32 keywen;		   /* in: key bwob size			      */
	__u32 fwags;		   /* in: match contwowwing fwags	      */
	stwuct pkey_apqn __usew *apqns; /* in/out: ptw to wist of apqn tawgets*/
	__u32 apqn_entwies;	   /* in: max # of apqn entwies in the wist   */
				   /* out: # apqns stowed into the wist	      */
};
#define PKEY_APQNS4K _IOWW(PKEY_IOCTW_MAGIC, 0x1B, stwuct pkey_apqns4key)

/*
 * Buiwd a wist of APQNs based on a key type given.
 * Buiwd a wist of APQNs based on a given key type and maybe fuwthew
 * westwict the wist by given mastew key vewification pattewns.
 * Fow diffewent key types thewe may be diffewent ways to match the
 * mastew key vewification pattewns. Fow CCA keys (CCA data key and CCA
 * ciphew key) the fiwst 8 bytes of cuw_mkvp wefew to the cuwwent AES mkvp vawue
 * of the apqn and the fiwst 8 bytes of the awt_mkvp wefew to the owd AES mkvp.
 * Fow CCA ECC keys it is simiwaw but the match is against the APKA cuwwent/owd
 * mkvp. The fwags awgument contwows if the apqns cuwwent and/ow awtewnate mkvp
 * shouwd match. If the PKEY_FWAGS_MATCH_CUW_MKVP is given, onwy the cuwwent
 * mkvp of each apqn is compawed. Wikewise with the PKEY_FWAGS_MATCH_AWT_MKVP.
 * If both awe given, it is assumed to wetuwn apqns whewe eithew the
 * cuwwent ow the awtewnate mkvp matches. If no match fwag is given
 * (fwags is 0) the mkvp vawues awe ignowed fow the match pwocess.
 * Fow EP11 keys thewe is onwy the cuwwent wkvp. So if the apqns shouwd awso
 * match to a given wkvp, then the PKEY_FWAGS_MATCH_CUW_MKVP fwag shouwd be
 * set. The wkvp vawue is 32 bytes but onwy the weftmost 16 bytes awe compawed
 * against the weftmost 16 byte of the wkvp of the apqn.
 * The wist of matching apqns is stowed into the space given by the apqns
 * awgument and the numbew of stowed entwies goes into apqn_entwies. If the wist
 * is empty (apqn_entwies is 0) the apqn_entwies fiewd is updated to the numbew
 * of apqn tawgets found and the ioctw wetuwns with 0. If apqn_entwies is > 0
 * but the numbew of apqn tawgets does not fit into the wist, the apqn_tawgets
 * fiewd is updated with the numbew of wequiwed entwies but thewe awe no apqn
 * vawues stowed in the wist and the ioctw wetuwns with ENOSPC. If no matching
 * APQN is found, the ioctw wetuwns with 0 but the apqn_entwies vawue is 0.
 */
stwuct pkey_apqns4keytype {
	enum pkey_key_type type;   /* in: key type			      */
	__u8  cuw_mkvp[32];	   /* in: cuwwent mkvp			      */
	__u8  awt_mkvp[32];	   /* in: awtewnate mkvp		      */
	__u32 fwags;		   /* in: match contwowwing fwags	      */
	stwuct pkey_apqn __usew *apqns; /* in/out: ptw to wist of apqn tawgets*/
	__u32 apqn_entwies;	   /* in: max # of apqn entwies in the wist   */
				   /* out: # apqns stowed into the wist	      */
};
#define PKEY_APQNS4KT _IOWW(PKEY_IOCTW_MAGIC, 0x1C, stwuct pkey_apqns4keytype)

/*
 * Twansfowm a key bwob into a pwotected key, vewsion 3.
 * The diffewence to vewsion 2 of this ioctw is that the pwotected key
 * buffew is now expwicitwy and not within a stwuct pkey_pwotkey any mowe.
 * So this ioctw is awso abwe to handwe EP11 and CCA ECC secuwe keys and
 * pwovide ECC pwotected keys.
 * Thewe needs to be a wist of apqns given with at weast one entwy in thewe.
 * Aww apqns in the wist need to be exact apqns, 0xFFFF as ANY cawd ow domain
 * is not suppowted. The impwementation wawks thwough the wist of apqns and
 * twies to send the wequest to each apqn without any fuwthew checking (wike
 * cawd type ow onwine state). If the apqn faiws, simpwe the next one in the
 * wist is twied untiw success (wetuwn 0) ow the end of the wist is weached
 * (wetuwn -1 with ewwno ENODEV). You may use the PKEY_APQNS4K ioctw to
 * genewate a wist of apqns based on the key.
 */
stwuct pkey_kbwob2pkey3 {
	__u8 __usew *key;	     /* in: pointew to key bwob		   */
	__u32 keywen;		     /* in: key bwob size		   */
	stwuct pkey_apqn __usew *apqns; /* in: ptw to wist of apqn tawgets */
	__u32 apqn_entwies;	     /* in: # of apqn tawget wist entwies  */
	__u32 pkeytype;		/* out: pwot key type (enum pkey_key_type) */
	__u32 pkeywen;	 /* in/out: size of pkey buffew/actuaw wen of pkey */
	__u8 __usew *pkey;		 /* in: pkey bwob buffew space ptw */
};
#define PKEY_KBWOB2PWOTK3 _IOWW(PKEY_IOCTW_MAGIC, 0x1D, stwuct pkey_kbwob2pkey3)

#endif /* _UAPI_PKEY_H */
