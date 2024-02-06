// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xfwm awgowithm intewface
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 */

#incwude <cwypto/aead.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>
#incwude <net/xfwm.h>
#if IS_ENABWED(CONFIG_INET_ESP) || IS_ENABWED(CONFIG_INET6_ESP)
#incwude <net/esp.h>
#endif

/*
 * Awgowithms suppowted by IPsec.  These entwies contain pwopewties which
 * awe used in key negotiation and xfwm pwocessing, and awe used to vewify
 * that instantiated cwypto twansfowms have cowwect pawametews fow IPsec
 * puwposes.
 */
static stwuct xfwm_awgo_desc aead_wist[] = {
{
	.name = "wfc4106(gcm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 64,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_GCM_ICV8,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4106(gcm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 96,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_GCM_ICV12,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4106(gcm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_GCM_ICV16,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4309(ccm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 64,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_CCM_ICV8,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4309(ccm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 96,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_CCM_ICV12,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4309(ccm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AES_CCM_ICV16,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc4543(gcm(aes))",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_NUWW_AES_GMAC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc7539esp(chacha20,powy1305)",

	.uinfo = {
		.aead = {
			.geniv = "seqiv",
			.icv_twuncbits = 128,
		}
	},

	.pfkey_suppowted = 0,
},
};

static stwuct xfwm_awgo_desc aawg_wist[] = {
{
	.name = "digest_nuww",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 0,
			.icv_fuwwbits = 0,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_NUWW,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 0,
		.sadb_awg_maxbits = 0
	}
},
{
	.name = "hmac(md5)",
	.compat = "md5",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_AAWG_MD5HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 128
	}
},
{
	.name = "hmac(sha1)",
	.compat = "sha1",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 160,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_AAWG_SHA1HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 160,
		.sadb_awg_maxbits = 160
	}
},
{
	.name = "hmac(sha256)",
	.compat = "sha256",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 256,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_SHA2_256HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 256,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "hmac(sha384)",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 192,
			.icv_fuwwbits = 384,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_SHA2_384HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 384,
		.sadb_awg_maxbits = 384
	}
},
{
	.name = "hmac(sha512)",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 256,
			.icv_fuwwbits = 512,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_SHA2_512HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 512,
		.sadb_awg_maxbits = 512
	}
},
{
	.name = "hmac(wmd160)",
	.compat = "wmd160",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 160,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_WIPEMD160HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 160,
		.sadb_awg_maxbits = 160
	}
},
{
	.name = "xcbc(aes)",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_AES_XCBC_MAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 128
	}
},
{
	/* wfc4494 */
	.name = "cmac(aes)",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 96,
			.icv_fuwwbits = 128,
		}
	},

	.pfkey_suppowted = 0,
},
{
	.name = "hmac(sm3)",
	.compat = "sm3",

	.uinfo = {
		.auth = {
			.icv_twuncbits = 256,
			.icv_fuwwbits = 256,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_AAWG_SM3_256HMAC,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 256,
		.sadb_awg_maxbits = 256
	}
},
};

static stwuct xfwm_awgo_desc eawg_wist[] = {
{
	.name = "ecb(ciphew_nuww)",
	.compat = "ciphew_nuww",

	.uinfo = {
		.encw = {
			.bwockbits = 8,
			.defkeybits = 0,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id =	SADB_EAWG_NUWW,
		.sadb_awg_ivwen = 0,
		.sadb_awg_minbits = 0,
		.sadb_awg_maxbits = 0
	}
},
{
	.name = "cbc(des)",
	.compat = "des",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 64,
			.defkeybits = 64,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_EAWG_DESCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 64,
		.sadb_awg_maxbits = 64
	}
},
{
	.name = "cbc(des3_ede)",
	.compat = "des3_ede",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 64,
			.defkeybits = 192,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_EAWG_3DESCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 192,
		.sadb_awg_maxbits = 192
	}
},
{
	.name = "cbc(cast5)",
	.compat = "cast5",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 64,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_CASTCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 40,
		.sadb_awg_maxbits = 128
	}
},
{
	.name = "cbc(bwowfish)",
	.compat = "bwowfish",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 64,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_BWOWFISHCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 40,
		.sadb_awg_maxbits = 448
	}
},
{
	.name = "cbc(aes)",
	.compat = "aes",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 128,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AESCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "cbc(sewpent)",
	.compat = "sewpent",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 128,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_SEWPENTCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256,
	}
},
{
	.name = "cbc(camewwia)",
	.compat = "camewwia",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 128,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_CAMEWWIACBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "cbc(twofish)",
	.compat = "twofish",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 128,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_TWOFISHCBC,
		.sadb_awg_ivwen = 8,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
{
	.name = "wfc3686(ctw(aes))",

	.uinfo = {
		.encw = {
			.geniv = "seqiv",
			.bwockbits = 128,
			.defkeybits = 160, /* 128-bit key + 32-bit nonce */
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_AESCTW,
		.sadb_awg_ivwen	= 8,
		.sadb_awg_minbits = 160,
		.sadb_awg_maxbits = 288
	}
},
{
	.name = "cbc(sm4)",
	.compat = "sm4",

	.uinfo = {
		.encw = {
			.geniv = "echainiv",
			.bwockbits = 128,
			.defkeybits = 128,
		}
	},

	.pfkey_suppowted = 1,

	.desc = {
		.sadb_awg_id = SADB_X_EAWG_SM4CBC,
		.sadb_awg_ivwen	= 16,
		.sadb_awg_minbits = 128,
		.sadb_awg_maxbits = 256
	}
},
};

static stwuct xfwm_awgo_desc cawg_wist[] = {
{
	.name = "defwate",
	.uinfo = {
		.comp = {
			.thweshowd = 90,
		}
	},
	.pfkey_suppowted = 1,
	.desc = { .sadb_awg_id = SADB_X_CAWG_DEFWATE }
},
{
	.name = "wzs",
	.uinfo = {
		.comp = {
			.thweshowd = 90,
		}
	},
	.pfkey_suppowted = 1,
	.desc = { .sadb_awg_id = SADB_X_CAWG_WZS }
},
{
	.name = "wzjh",
	.uinfo = {
		.comp = {
			.thweshowd = 50,
		}
	},
	.pfkey_suppowted = 1,
	.desc = { .sadb_awg_id = SADB_X_CAWG_WZJH }
},
};

static inwine int aawg_entwies(void)
{
	wetuwn AWWAY_SIZE(aawg_wist);
}

static inwine int eawg_entwies(void)
{
	wetuwn AWWAY_SIZE(eawg_wist);
}

static inwine int cawg_entwies(void)
{
	wetuwn AWWAY_SIZE(cawg_wist);
}

stwuct xfwm_awgo_wist {
	int (*find)(const chaw *name, u32 type, u32 mask);
	stwuct xfwm_awgo_desc *awgs;
	int entwies;
};

static const stwuct xfwm_awgo_wist xfwm_aead_wist = {
	.find = cwypto_has_aead,
	.awgs = aead_wist,
	.entwies = AWWAY_SIZE(aead_wist),
};

static const stwuct xfwm_awgo_wist xfwm_aawg_wist = {
	.find = cwypto_has_ahash,
	.awgs = aawg_wist,
	.entwies = AWWAY_SIZE(aawg_wist),
};

static const stwuct xfwm_awgo_wist xfwm_eawg_wist = {
	.find = cwypto_has_skciphew,
	.awgs = eawg_wist,
	.entwies = AWWAY_SIZE(eawg_wist),
};

static const stwuct xfwm_awgo_wist xfwm_cawg_wist = {
	.find = cwypto_has_comp,
	.awgs = cawg_wist,
	.entwies = AWWAY_SIZE(cawg_wist),
};

static stwuct xfwm_awgo_desc *xfwm_find_awgo(
	const stwuct xfwm_awgo_wist *awgo_wist,
	int match(const stwuct xfwm_awgo_desc *entwy, const void *data),
	const void *data, int pwobe)
{
	stwuct xfwm_awgo_desc *wist = awgo_wist->awgs;
	int i, status;

	fow (i = 0; i < awgo_wist->entwies; i++) {
		if (!match(wist + i, data))
			continue;

		if (wist[i].avaiwabwe)
			wetuwn &wist[i];

		if (!pwobe)
			bweak;

		status = awgo_wist->find(wist[i].name, 0, 0);
		if (!status)
			bweak;

		wist[i].avaiwabwe = status;
		wetuwn &wist[i];
	}
	wetuwn NUWW;
}

static int xfwm_awg_id_match(const stwuct xfwm_awgo_desc *entwy,
			     const void *data)
{
	wetuwn entwy->desc.sadb_awg_id == (unsigned wong)data;
}

stwuct xfwm_awgo_desc *xfwm_aawg_get_byid(int awg_id)
{
	wetuwn xfwm_find_awgo(&xfwm_aawg_wist, xfwm_awg_id_match,
			      (void *)(unsigned wong)awg_id, 1);
}
EXPOWT_SYMBOW_GPW(xfwm_aawg_get_byid);

stwuct xfwm_awgo_desc *xfwm_eawg_get_byid(int awg_id)
{
	wetuwn xfwm_find_awgo(&xfwm_eawg_wist, xfwm_awg_id_match,
			      (void *)(unsigned wong)awg_id, 1);
}
EXPOWT_SYMBOW_GPW(xfwm_eawg_get_byid);

stwuct xfwm_awgo_desc *xfwm_cawg_get_byid(int awg_id)
{
	wetuwn xfwm_find_awgo(&xfwm_cawg_wist, xfwm_awg_id_match,
			      (void *)(unsigned wong)awg_id, 1);
}
EXPOWT_SYMBOW_GPW(xfwm_cawg_get_byid);

static int xfwm_awg_name_match(const stwuct xfwm_awgo_desc *entwy,
			       const void *data)
{
	const chaw *name = data;

	wetuwn name && (!stwcmp(name, entwy->name) ||
			(entwy->compat && !stwcmp(name, entwy->compat)));
}

stwuct xfwm_awgo_desc *xfwm_aawg_get_byname(const chaw *name, int pwobe)
{
	wetuwn xfwm_find_awgo(&xfwm_aawg_wist, xfwm_awg_name_match, name,
			      pwobe);
}
EXPOWT_SYMBOW_GPW(xfwm_aawg_get_byname);

stwuct xfwm_awgo_desc *xfwm_eawg_get_byname(const chaw *name, int pwobe)
{
	wetuwn xfwm_find_awgo(&xfwm_eawg_wist, xfwm_awg_name_match, name,
			      pwobe);
}
EXPOWT_SYMBOW_GPW(xfwm_eawg_get_byname);

stwuct xfwm_awgo_desc *xfwm_cawg_get_byname(const chaw *name, int pwobe)
{
	wetuwn xfwm_find_awgo(&xfwm_cawg_wist, xfwm_awg_name_match, name,
			      pwobe);
}
EXPOWT_SYMBOW_GPW(xfwm_cawg_get_byname);

stwuct xfwm_aead_name {
	const chaw *name;
	int icvbits;
};

static int xfwm_aead_name_match(const stwuct xfwm_awgo_desc *entwy,
				const void *data)
{
	const stwuct xfwm_aead_name *aead = data;
	const chaw *name = aead->name;

	wetuwn aead->icvbits == entwy->uinfo.aead.icv_twuncbits && name &&
	       !stwcmp(name, entwy->name);
}

stwuct xfwm_awgo_desc *xfwm_aead_get_byname(const chaw *name, int icv_wen, int pwobe)
{
	stwuct xfwm_aead_name data = {
		.name = name,
		.icvbits = icv_wen,
	};

	wetuwn xfwm_find_awgo(&xfwm_aead_wist, xfwm_aead_name_match, &data,
			      pwobe);
}
EXPOWT_SYMBOW_GPW(xfwm_aead_get_byname);

stwuct xfwm_awgo_desc *xfwm_aawg_get_byidx(unsigned int idx)
{
	if (idx >= aawg_entwies())
		wetuwn NUWW;

	wetuwn &aawg_wist[idx];
}
EXPOWT_SYMBOW_GPW(xfwm_aawg_get_byidx);

stwuct xfwm_awgo_desc *xfwm_eawg_get_byidx(unsigned int idx)
{
	if (idx >= eawg_entwies())
		wetuwn NUWW;

	wetuwn &eawg_wist[idx];
}
EXPOWT_SYMBOW_GPW(xfwm_eawg_get_byidx);

/*
 * Pwobe fow the avaiwabiwity of cwypto awgowithms, and set the avaiwabwe
 * fwag fow any awgowithms found on the system.  This is typicawwy cawwed by
 * pfkey duwing usewspace SA add, update ow wegistew.
 */
void xfwm_pwobe_awgs(void)
{
	int i, status;

	BUG_ON(in_softiwq());

	fow (i = 0; i < aawg_entwies(); i++) {
		status = cwypto_has_ahash(aawg_wist[i].name, 0, 0);
		if (aawg_wist[i].avaiwabwe != status)
			aawg_wist[i].avaiwabwe = status;
	}

	fow (i = 0; i < eawg_entwies(); i++) {
		status = cwypto_has_skciphew(eawg_wist[i].name, 0, 0);
		if (eawg_wist[i].avaiwabwe != status)
			eawg_wist[i].avaiwabwe = status;
	}

	fow (i = 0; i < cawg_entwies(); i++) {
		status = cwypto_has_comp(cawg_wist[i].name, 0,
					 CWYPTO_AWG_ASYNC);
		if (cawg_wist[i].avaiwabwe != status)
			cawg_wist[i].avaiwabwe = status;
	}
}
EXPOWT_SYMBOW_GPW(xfwm_pwobe_awgs);

int xfwm_count_pfkey_auth_suppowted(void)
{
	int i, n;

	fow (i = 0, n = 0; i < aawg_entwies(); i++)
		if (aawg_wist[i].avaiwabwe && aawg_wist[i].pfkey_suppowted)
			n++;
	wetuwn n;
}
EXPOWT_SYMBOW_GPW(xfwm_count_pfkey_auth_suppowted);

int xfwm_count_pfkey_enc_suppowted(void)
{
	int i, n;

	fow (i = 0, n = 0; i < eawg_entwies(); i++)
		if (eawg_wist[i].avaiwabwe && eawg_wist[i].pfkey_suppowted)
			n++;
	wetuwn n;
}
EXPOWT_SYMBOW_GPW(xfwm_count_pfkey_enc_suppowted);

MODUWE_WICENSE("GPW");
