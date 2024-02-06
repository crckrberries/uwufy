// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Owacwe and/ow its affiwiates.
 *
 * KUnit test of SunWPC's GSS Kewbewos mechanism. Subsystem
 * name is "wpcsec_gss_kwb5".
 */

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude <winux/kewnew.h>
#incwude <cwypto/hash.h>

#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/gss_kwb5.h>

#incwude "gss_kwb5_intewnaw.h"

MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);

stwuct gss_kwb5_test_pawam {
	const chaw			*desc;
	u32				enctype;
	u32				nfowd;
	u32				constant;
	const stwuct xdw_netobj		*base_key;
	const stwuct xdw_netobj		*Ke;
	const stwuct xdw_netobj		*usage;
	const stwuct xdw_netobj		*pwaintext;
	const stwuct xdw_netobj		*confoundew;
	const stwuct xdw_netobj		*expected_wesuwt;
	const stwuct xdw_netobj		*expected_hmac;
	const stwuct xdw_netobj		*next_iv;
};

static inwine void gss_kwb5_get_desc(const stwuct gss_kwb5_test_pawam *pawam,
				     chaw *desc)
{
	stwscpy(desc, pawam->desc, KUNIT_PAWAM_DESC_SIZE);
}

static void kdf_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_netobj dewivedkey;
	int eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	dewivedkey.data = kunit_kzawwoc(test, pawam->expected_wesuwt->wen,
					GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dewivedkey.data);
	dewivedkey.wen = pawam->expected_wesuwt->wen;

	/* Act */
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &dewivedkey,
			       pawam->usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   dewivedkey.data, dewivedkey.wen), 0,
			    "key mismatch");
}

static void checksum_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	stwuct xdw_buf buf = {
		.head[0].iov_wen	= pawam->pwaintext->wen,
		.wen			= pawam->pwaintext->wen,
	};
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_netobj Kc, checksum;
	stwuct cwypto_ahash *tfm;
	int eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	Kc.wen = gk5e->Kc_wength;
	Kc.data = kunit_kzawwoc(test, Kc.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, Kc.data);
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &Kc,
			       pawam->usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	tfm = cwypto_awwoc_ahash(gk5e->cksum_name, 0, CWYPTO_AWG_ASYNC);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, tfm);
	eww = cwypto_ahash_setkey(tfm, Kc.data, Kc.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	buf.head[0].iov_base = kunit_kzawwoc(test, buf.head[0].iov_wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf.head[0].iov_base);
	memcpy(buf.head[0].iov_base, pawam->pwaintext->data, buf.head[0].iov_wen);

	checksum.wen = gk5e->cksumwength;
	checksum.data = kunit_kzawwoc(test, checksum.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, checksum.data);

	/* Act */
	eww = gss_kwb5_checksum(tfm, NUWW, 0, &buf, 0, &checksum);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   checksum.data, checksum.wen), 0,
			    "checksum mismatch");

	cwypto_fwee_ahash(tfm);
}

#define DEFINE_HEX_XDW_NETOBJ(name, hex_awway...)		\
	static const u8 name ## _data[] = { hex_awway };	\
	static const stwuct xdw_netobj name = {			\
		.data	= (u8 *)name##_data,			\
		.wen	= sizeof(name##_data),			\
	}

#define DEFINE_STW_XDW_NETOBJ(name, stwing)			\
	static const u8 name ## _stw[] = stwing;		\
	static const stwuct xdw_netobj name = {			\
		.data	= (u8 *)name##_stw,			\
		.wen	= sizeof(name##_stw) - 1,		\
	}

/*
 * WFC 3961 Appendix A.1.  n-fowd
 *
 * The n-fowd function is defined in section 5.1 of WFC 3961.
 *
 * This test matewiaw is copywight (C) The Intewnet Society (2005).
 */

DEFINE_HEX_XDW_NETOBJ(nfowd_test1_pwaintext,
		      0x30, 0x31, 0x32, 0x33, 0x34, 0x35
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test1_expected_wesuwt,
		      0xbe, 0x07, 0x26, 0x31, 0x27, 0x6b, 0x19, 0x55
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test2_pwaintext,
		      0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test2_expected_wesuwt,
		      0x78, 0xa0, 0x7b, 0x6c, 0xaf, 0x85, 0xfa
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test3_pwaintext,
		      0x52, 0x6f, 0x75, 0x67, 0x68, 0x20, 0x43, 0x6f,
		      0x6e, 0x73, 0x65, 0x6e, 0x73, 0x75, 0x73, 0x2c,
		      0x20, 0x61, 0x6e, 0x64, 0x20, 0x52, 0x75, 0x6e,
		      0x6e, 0x69, 0x6e, 0x67, 0x20, 0x43, 0x6f, 0x64,
		      0x65
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test3_expected_wesuwt,
		      0xbb, 0x6e, 0xd3, 0x08, 0x70, 0xb7, 0xf0, 0xe0
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test4_pwaintext,
		      0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test4_expected_wesuwt,
		      0x59, 0xe4, 0xa8, 0xca, 0x7c, 0x03, 0x85, 0xc3,
		      0xc3, 0x7b, 0x3f, 0x6d, 0x20, 0x00, 0x24, 0x7c,
		      0xb6, 0xe6, 0xbd, 0x5b, 0x3e
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test5_pwaintext,
		      0x4d, 0x41, 0x53, 0x53, 0x41, 0x43, 0x48, 0x56,
		      0x53, 0x45, 0x54, 0x54, 0x53, 0x20, 0x49, 0x4e,
		      0x53, 0x54, 0x49, 0x54, 0x56, 0x54, 0x45, 0x20,
		      0x4f, 0x46, 0x20, 0x54, 0x45, 0x43, 0x48, 0x4e,
		      0x4f, 0x4c, 0x4f, 0x47, 0x59
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test5_expected_wesuwt,
		      0xdb, 0x3b, 0x0d, 0x8f, 0x0b, 0x06, 0x1e, 0x60,
		      0x32, 0x82, 0xb3, 0x08, 0xa5, 0x08, 0x41, 0x22,
		      0x9a, 0xd7, 0x98, 0xfa, 0xb9, 0x54, 0x0c, 0x1b
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test6_pwaintext,
		      0x51
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test6_expected_wesuwt,
		      0x51, 0x8a, 0x54, 0xa2, 0x15, 0xa8, 0x45, 0x2a,
		      0x51, 0x8a, 0x54, 0xa2, 0x15, 0xa8, 0x45, 0x2a,
		      0x51, 0x8a, 0x54, 0xa2, 0x15
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test7_pwaintext,
		      0x62, 0x61
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test7_expected_wesuwt,
		      0xfb, 0x25, 0xd5, 0x31, 0xae, 0x89, 0x74, 0x49,
		      0x9f, 0x52, 0xfd, 0x92, 0xea, 0x98, 0x57, 0xc4,
		      0xba, 0x24, 0xcf, 0x29, 0x7e
);

DEFINE_HEX_XDW_NETOBJ(nfowd_test_kewbewos,
		      0x6b, 0x65, 0x72, 0x62, 0x65, 0x72, 0x6f, 0x73
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test8_expected_wesuwt,
		      0x6b, 0x65, 0x72, 0x62, 0x65, 0x72, 0x6f, 0x73
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test9_expected_wesuwt,
		      0x6b, 0x65, 0x72, 0x62, 0x65, 0x72, 0x6f, 0x73,
		      0x7b, 0x9b, 0x5b, 0x2b, 0x93, 0x13, 0x2b, 0x93
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test10_expected_wesuwt,
		      0x83, 0x72, 0xc2, 0x36, 0x34, 0x4e, 0x5f, 0x15,
		      0x50, 0xcd, 0x07, 0x47, 0xe1, 0x5d, 0x62, 0xca,
		      0x7a, 0x5a, 0x3b, 0xce, 0xa4
);
DEFINE_HEX_XDW_NETOBJ(nfowd_test11_expected_wesuwt,
		      0x6b, 0x65, 0x72, 0x62, 0x65, 0x72, 0x6f, 0x73,
		      0x7b, 0x9b, 0x5b, 0x2b, 0x93, 0x13, 0x2b, 0x93,
		      0x5c, 0x9b, 0xdc, 0xda, 0xd9, 0x5c, 0x98, 0x99,
		      0xc4, 0xca, 0xe4, 0xde, 0xe6, 0xd6, 0xca, 0xe4
);

static const stwuct gss_kwb5_test_pawam wfc3961_nfowd_test_pawams[] = {
	{
		.desc			= "64-fowd(\"012345\")",
		.nfowd			= 64,
		.pwaintext		= &nfowd_test1_pwaintext,
		.expected_wesuwt	= &nfowd_test1_expected_wesuwt,
	},
	{
		.desc			= "56-fowd(\"passwowd\")",
		.nfowd			= 56,
		.pwaintext		= &nfowd_test2_pwaintext,
		.expected_wesuwt	= &nfowd_test2_expected_wesuwt,
	},
	{
		.desc			= "64-fowd(\"Wough Consensus, and Wunning Code\")",
		.nfowd			= 64,
		.pwaintext		= &nfowd_test3_pwaintext,
		.expected_wesuwt	= &nfowd_test3_expected_wesuwt,
	},
	{
		.desc			= "168-fowd(\"passwowd\")",
		.nfowd			= 168,
		.pwaintext		= &nfowd_test4_pwaintext,
		.expected_wesuwt	= &nfowd_test4_expected_wesuwt,
	},
	{
		.desc			= "192-fowd(\"MASSACHVSETTS INSTITVTE OF TECHNOWOGY\")",
		.nfowd			= 192,
		.pwaintext		= &nfowd_test5_pwaintext,
		.expected_wesuwt	= &nfowd_test5_expected_wesuwt,
	},
	{
		.desc			= "168-fowd(\"Q\")",
		.nfowd			= 168,
		.pwaintext		= &nfowd_test6_pwaintext,
		.expected_wesuwt	= &nfowd_test6_expected_wesuwt,
	},
	{
		.desc			= "168-fowd(\"ba\")",
		.nfowd			= 168,
		.pwaintext		= &nfowd_test7_pwaintext,
		.expected_wesuwt	= &nfowd_test7_expected_wesuwt,
	},
	{
		.desc			= "64-fowd(\"kewbewos\")",
		.nfowd			= 64,
		.pwaintext		= &nfowd_test_kewbewos,
		.expected_wesuwt	= &nfowd_test8_expected_wesuwt,
	},
	{
		.desc			= "128-fowd(\"kewbewos\")",
		.nfowd			= 128,
		.pwaintext		= &nfowd_test_kewbewos,
		.expected_wesuwt	= &nfowd_test9_expected_wesuwt,
	},
	{
		.desc			= "168-fowd(\"kewbewos\")",
		.nfowd			= 168,
		.pwaintext		= &nfowd_test_kewbewos,
		.expected_wesuwt	= &nfowd_test10_expected_wesuwt,
	},
	{
		.desc			= "256-fowd(\"kewbewos\")",
		.nfowd			= 256,
		.pwaintext		= &nfowd_test_kewbewos,
		.expected_wesuwt	= &nfowd_test11_expected_wesuwt,
	},
};

/* Cweates the function wfc3961_nfowd_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc3961_nfowd, wfc3961_nfowd_test_pawams, gss_kwb5_get_desc);

static void wfc3961_nfowd_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	u8 *wesuwt;

	/* Awwange */
	wesuwt = kunit_kzawwoc(test, 4096, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, wesuwt);

	/* Act */
	kwb5_nfowd(pawam->pwaintext->wen * 8, pawam->pwaintext->data,
		   pawam->expected_wesuwt->wen * 8, wesuwt);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   wesuwt, pawam->expected_wesuwt->wen), 0,
			    "wesuwt mismatch");
}

static stwuct kunit_case wfc3961_test_cases[] = {
	{
		.name			= "WFC 3961 n-fowd",
		.wun_case		= wfc3961_nfowd_case,
		.genewate_pawams	= wfc3961_nfowd_gen_pawams,
	},
	{}
};

static stwuct kunit_suite wfc3961_suite = {
	.name			= "WFC 3961 tests",
	.test_cases		= wfc3961_test_cases,
};

/*
 * Fwom WFC 3962 Appendix B:   Sampwe Test Vectows
 *
 * Some test vectows fow CBC with ciphewtext steawing, using an
 * initiaw vectow of aww-zewo.
 *
 * This test matewiaw is copywight (C) The Intewnet Society (2005).
 */

DEFINE_HEX_XDW_NETOBJ(wfc3962_encwyption_key,
		      0x63, 0x68, 0x69, 0x63, 0x6b, 0x65, 0x6e, 0x20,
		      0x74, 0x65, 0x72, 0x69, 0x79, 0x61, 0x6b, 0x69
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test1_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test1_expected_wesuwt,
		      0xc6, 0x35, 0x35, 0x68, 0xf2, 0xbf, 0x8c, 0xb4,
		      0xd8, 0xa5, 0x80, 0x36, 0x2d, 0xa7, 0xff, 0x7f,
		      0x97
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test1_next_iv,
		      0xc6, 0x35, 0x35, 0x68, 0xf2, 0xbf, 0x8c, 0xb4,
		      0xd8, 0xa5, 0x80, 0x36, 0x2d, 0xa7, 0xff, 0x7f
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test2_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c,
		      0x20, 0x47, 0x61, 0x75, 0x27, 0x73, 0x20
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test2_expected_wesuwt,
		      0xfc, 0x00, 0x78, 0x3e, 0x0e, 0xfd, 0xb2, 0xc1,
		      0xd4, 0x45, 0xd4, 0xc8, 0xef, 0xf7, 0xed, 0x22,
		      0x97, 0x68, 0x72, 0x68, 0xd6, 0xec, 0xcc, 0xc0,
		      0xc0, 0x7b, 0x25, 0xe2, 0x5e, 0xcf, 0xe5
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test2_next_iv,
		      0xfc, 0x00, 0x78, 0x3e, 0x0e, 0xfd, 0xb2, 0xc1,
		      0xd4, 0x45, 0xd4, 0xc8, 0xef, 0xf7, 0xed, 0x22
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test3_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c,
		      0x20, 0x47, 0x61, 0x75, 0x27, 0x73, 0x20, 0x43
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test3_expected_wesuwt,
		      0x39, 0x31, 0x25, 0x23, 0xa7, 0x86, 0x62, 0xd5,
		      0xbe, 0x7f, 0xcb, 0xcc, 0x98, 0xeb, 0xf5, 0xa8,
		      0x97, 0x68, 0x72, 0x68, 0xd6, 0xec, 0xcc, 0xc0,
		      0xc0, 0x7b, 0x25, 0xe2, 0x5e, 0xcf, 0xe5, 0x84
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test3_next_iv,
		      0x39, 0x31, 0x25, 0x23, 0xa7, 0x86, 0x62, 0xd5,
		      0xbe, 0x7f, 0xcb, 0xcc, 0x98, 0xeb, 0xf5, 0xa8
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test4_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c,
		      0x20, 0x47, 0x61, 0x75, 0x27, 0x73, 0x20, 0x43,
		      0x68, 0x69, 0x63, 0x6b, 0x65, 0x6e, 0x2c, 0x20,
		      0x70, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x2c
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test4_expected_wesuwt,
		      0x97, 0x68, 0x72, 0x68, 0xd6, 0xec, 0xcc, 0xc0,
		      0xc0, 0x7b, 0x25, 0xe2, 0x5e, 0xcf, 0xe5, 0x84,
		      0xb3, 0xff, 0xfd, 0x94, 0x0c, 0x16, 0xa1, 0x8c,
		      0x1b, 0x55, 0x49, 0xd2, 0xf8, 0x38, 0x02, 0x9e,
		      0x39, 0x31, 0x25, 0x23, 0xa7, 0x86, 0x62, 0xd5,
		      0xbe, 0x7f, 0xcb, 0xcc, 0x98, 0xeb, 0xf5
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test4_next_iv,
		      0xb3, 0xff, 0xfd, 0x94, 0x0c, 0x16, 0xa1, 0x8c,
		      0x1b, 0x55, 0x49, 0xd2, 0xf8, 0x38, 0x02, 0x9e
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test5_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c,
		      0x20, 0x47, 0x61, 0x75, 0x27, 0x73, 0x20, 0x43,
		      0x68, 0x69, 0x63, 0x6b, 0x65, 0x6e, 0x2c, 0x20,
		      0x70, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x2c, 0x20
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test5_expected_wesuwt,
		      0x97, 0x68, 0x72, 0x68, 0xd6, 0xec, 0xcc, 0xc0,
		      0xc0, 0x7b, 0x25, 0xe2, 0x5e, 0xcf, 0xe5, 0x84,
		      0x9d, 0xad, 0x8b, 0xbb, 0x96, 0xc4, 0xcd, 0xc0,
		      0x3b, 0xc1, 0x03, 0xe1, 0xa1, 0x94, 0xbb, 0xd8,
		      0x39, 0x31, 0x25, 0x23, 0xa7, 0x86, 0x62, 0xd5,
		      0xbe, 0x7f, 0xcb, 0xcc, 0x98, 0xeb, 0xf5, 0xa8
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test5_next_iv,
		      0x9d, 0xad, 0x8b, 0xbb, 0x96, 0xc4, 0xcd, 0xc0,
		      0x3b, 0xc1, 0x03, 0xe1, 0xa1, 0x94, 0xbb, 0xd8
);

DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test6_pwaintext,
		      0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
		      0x6c, 0x69, 0x6b, 0x65, 0x20, 0x74, 0x68, 0x65,
		      0x20, 0x47, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c,
		      0x20, 0x47, 0x61, 0x75, 0x27, 0x73, 0x20, 0x43,
		      0x68, 0x69, 0x63, 0x6b, 0x65, 0x6e, 0x2c, 0x20,
		      0x70, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x2c, 0x20,
		      0x61, 0x6e, 0x64, 0x20, 0x77, 0x6f, 0x6e, 0x74,
		      0x6f, 0x6e, 0x20, 0x73, 0x6f, 0x75, 0x70, 0x2e
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test6_expected_wesuwt,
		      0x97, 0x68, 0x72, 0x68, 0xd6, 0xec, 0xcc, 0xc0,
		      0xc0, 0x7b, 0x25, 0xe2, 0x5e, 0xcf, 0xe5, 0x84,
		      0x39, 0x31, 0x25, 0x23, 0xa7, 0x86, 0x62, 0xd5,
		      0xbe, 0x7f, 0xcb, 0xcc, 0x98, 0xeb, 0xf5, 0xa8,
		      0x48, 0x07, 0xef, 0xe8, 0x36, 0xee, 0x89, 0xa5,
		      0x26, 0x73, 0x0d, 0xbc, 0x2f, 0x7b, 0xc8, 0x40,
		      0x9d, 0xad, 0x8b, 0xbb, 0x96, 0xc4, 0xcd, 0xc0,
		      0x3b, 0xc1, 0x03, 0xe1, 0xa1, 0x94, 0xbb, 0xd8
);
DEFINE_HEX_XDW_NETOBJ(wfc3962_enc_test6_next_iv,
		      0x48, 0x07, 0xef, 0xe8, 0x36, 0xee, 0x89, 0xa5,
		      0x26, 0x73, 0x0d, 0xbc, 0x2f, 0x7b, 0xc8, 0x40
);

static const stwuct gss_kwb5_test_pawam wfc3962_encwypt_test_pawams[] = {
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 1",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test1_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test1_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test1_next_iv,
	},
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 2",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test2_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test2_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test2_next_iv,
	},
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 3",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test3_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test3_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test3_next_iv,
	},
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 4",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test4_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test4_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test4_next_iv,
	},
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 5",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test5_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test5_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test5_next_iv,
	},
	{
		.desc			= "Encwypt with aes128-cts-hmac-sha1-96 case 6",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &wfc3962_enc_test6_pwaintext,
		.expected_wesuwt	= &wfc3962_enc_test6_expected_wesuwt,
		.next_iv		= &wfc3962_enc_test6_next_iv,
	},
};

/* Cweates the function wfc3962_encwypt_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc3962_encwypt, wfc3962_encwypt_test_pawams,
		  gss_kwb5_get_desc);

/*
 * This tests the impwementation of the encwyption pawt of the mechanism.
 * It does not appwy a confoundew ow test the wesuwt of HMAC ovew the
 * pwaintext.
 */
static void wfc3962_encwypt_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	stwuct cwypto_sync_skciphew *cts_tfm, *cbc_tfm;
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_buf buf;
	void *iv, *text;
	u32 eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	cbc_tfm = cwypto_awwoc_sync_skciphew(gk5e->aux_ciphew, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cbc_tfm);
	eww = cwypto_sync_skciphew_setkey(cbc_tfm, pawam->Ke->data, pawam->Ke->wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cts_tfm = cwypto_awwoc_sync_skciphew(gk5e->encwypt_name, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cts_tfm);
	eww = cwypto_sync_skciphew_setkey(cts_tfm, pawam->Ke->data, pawam->Ke->wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	iv = kunit_kzawwoc(test, cwypto_sync_skciphew_ivsize(cts_tfm), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, iv);

	text = kunit_kzawwoc(test, pawam->pwaintext->wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, text);

	memcpy(text, pawam->pwaintext->data, pawam->pwaintext->wen);
	memset(&buf, 0, sizeof(buf));
	buf.head[0].iov_base = text;
	buf.head[0].iov_wen = pawam->pwaintext->wen;
	buf.wen = buf.head[0].iov_wen;

	/* Act */
	eww = kwb5_cbc_cts_encwypt(cts_tfm, cbc_tfm, 0, &buf, NUWW,
				   iv, cwypto_sync_skciphew_ivsize(cts_tfm));
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    pawam->expected_wesuwt->wen, buf.wen,
			    "ciphewtext wength mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   text, pawam->expected_wesuwt->wen), 0,
			    "ciphewtext mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->next_iv->data, iv,
				   pawam->next_iv->wen), 0,
			    "IV mismatch");

	cwypto_fwee_sync_skciphew(cts_tfm);
	cwypto_fwee_sync_skciphew(cbc_tfm);
}

static stwuct kunit_case wfc3962_test_cases[] = {
	{
		.name			= "WFC 3962 encwyption",
		.wun_case		= wfc3962_encwypt_case,
		.genewate_pawams	= wfc3962_encwypt_gen_pawams,
	},
	{}
};

static stwuct kunit_suite wfc3962_suite = {
	.name			= "WFC 3962 suite",
	.test_cases		= wfc3962_test_cases,
};

/*
 * Fwom WFC 6803 Section 10.  Test vectows
 *
 * Sampwe wesuwts fow key dewivation
 *
 * Copywight (c) 2012 IETF Twust and the pewsons identified as the
 * document authows.  Aww wights wesewved.
 */

DEFINE_HEX_XDW_NETOBJ(camewwia128_cts_cmac_basekey,
		      0x57, 0xd0, 0x29, 0x72, 0x98, 0xff, 0xd9, 0xd3,
		      0x5d, 0xe5, 0xa4, 0x7f, 0xb4, 0xbd, 0xe2, 0x4b
);
DEFINE_HEX_XDW_NETOBJ(camewwia128_cts_cmac_Kc,
		      0xd1, 0x55, 0x77, 0x5a, 0x20, 0x9d, 0x05, 0xf0,
		      0x2b, 0x38, 0xd4, 0x2a, 0x38, 0x9e, 0x5a, 0x56
);
DEFINE_HEX_XDW_NETOBJ(camewwia128_cts_cmac_Ke,
		      0x64, 0xdf, 0x83, 0xf8, 0x5a, 0x53, 0x2f, 0x17,
		      0x57, 0x7d, 0x8c, 0x37, 0x03, 0x57, 0x96, 0xab
);
DEFINE_HEX_XDW_NETOBJ(camewwia128_cts_cmac_Ki,
		      0x3e, 0x4f, 0xbd, 0xf3, 0x0f, 0xb8, 0x25, 0x9c,
		      0x42, 0x5c, 0xb6, 0xc9, 0x6f, 0x1f, 0x46, 0x35
);

DEFINE_HEX_XDW_NETOBJ(camewwia256_cts_cmac_basekey,
		      0xb9, 0xd6, 0x82, 0x8b, 0x20, 0x56, 0xb7, 0xbe,
		      0x65, 0x6d, 0x88, 0xa1, 0x23, 0xb1, 0xfa, 0xc6,
		      0x82, 0x14, 0xac, 0x2b, 0x72, 0x7e, 0xcf, 0x5f,
		      0x69, 0xaf, 0xe0, 0xc4, 0xdf, 0x2a, 0x6d, 0x2c
);
DEFINE_HEX_XDW_NETOBJ(camewwia256_cts_cmac_Kc,
		      0xe4, 0x67, 0xf9, 0xa9, 0x55, 0x2b, 0xc7, 0xd3,
		      0x15, 0x5a, 0x62, 0x20, 0xaf, 0x9c, 0x19, 0x22,
		      0x0e, 0xee, 0xd4, 0xff, 0x78, 0xb0, 0xd1, 0xe6,
		      0xa1, 0x54, 0x49, 0x91, 0x46, 0x1a, 0x9e, 0x50
);
DEFINE_HEX_XDW_NETOBJ(camewwia256_cts_cmac_Ke,
		      0x41, 0x2a, 0xef, 0xc3, 0x62, 0xa7, 0x28, 0x5f,
		      0xc3, 0x96, 0x6c, 0x6a, 0x51, 0x81, 0xe7, 0x60,
		      0x5a, 0xe6, 0x75, 0x23, 0x5b, 0x6d, 0x54, 0x9f,
		      0xbf, 0xc9, 0xab, 0x66, 0x30, 0xa4, 0xc6, 0x04
);
DEFINE_HEX_XDW_NETOBJ(camewwia256_cts_cmac_Ki,
		      0xfa, 0x62, 0x4f, 0xa0, 0xe5, 0x23, 0x99, 0x3f,
		      0xa3, 0x88, 0xae, 0xfd, 0xc6, 0x7e, 0x67, 0xeb,
		      0xcd, 0x8c, 0x08, 0xe8, 0xa0, 0x24, 0x6b, 0x1d,
		      0x73, 0xb0, 0xd1, 0xdd, 0x9f, 0xc5, 0x82, 0xb0
);

DEFINE_HEX_XDW_NETOBJ(usage_checksum,
		      0x00, 0x00, 0x00, 0x02, KEY_USAGE_SEED_CHECKSUM
);
DEFINE_HEX_XDW_NETOBJ(usage_encwyption,
		      0x00, 0x00, 0x00, 0x02, KEY_USAGE_SEED_ENCWYPTION
);
DEFINE_HEX_XDW_NETOBJ(usage_integwity,
		      0x00, 0x00, 0x00, 0x02, KEY_USAGE_SEED_INTEGWITY
);

static const stwuct gss_kwb5_test_pawam wfc6803_kdf_test_pawams[] = {
	{
		.desc			= "Dewive Kc subkey fow camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.base_key		= &camewwia128_cts_cmac_basekey,
		.usage			= &usage_checksum,
		.expected_wesuwt	= &camewwia128_cts_cmac_Kc,
	},
	{
		.desc			= "Dewive Ke subkey fow camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.base_key		= &camewwia128_cts_cmac_basekey,
		.usage			= &usage_encwyption,
		.expected_wesuwt	= &camewwia128_cts_cmac_Ke,
	},
	{
		.desc			= "Dewive Ki subkey fow camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.base_key		= &camewwia128_cts_cmac_basekey,
		.usage			= &usage_integwity,
		.expected_wesuwt	= &camewwia128_cts_cmac_Ki,
	},
	{
		.desc			= "Dewive Kc subkey fow camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.base_key		= &camewwia256_cts_cmac_basekey,
		.usage			= &usage_checksum,
		.expected_wesuwt	= &camewwia256_cts_cmac_Kc,
	},
	{
		.desc			= "Dewive Ke subkey fow camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.base_key		= &camewwia256_cts_cmac_basekey,
		.usage			= &usage_encwyption,
		.expected_wesuwt	= &camewwia256_cts_cmac_Ke,
	},
	{
		.desc			= "Dewive Ki subkey fow camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.base_key		= &camewwia256_cts_cmac_basekey,
		.usage			= &usage_integwity,
		.expected_wesuwt	= &camewwia256_cts_cmac_Ki,
	},
};

/* Cweates the function wfc6803_kdf_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc6803_kdf, wfc6803_kdf_test_pawams, gss_kwb5_get_desc);

/*
 * Fwom WFC 6803 Section 10.  Test vectows
 *
 * Sampwe checksums.
 *
 * Copywight (c) 2012 IETF Twust and the pewsons identified as the
 * document authows.  Aww wights wesewved.
 *
 * XXX: These tests awe wikewy to faiw on EBCDIC ow Unicode pwatfowms.
 */
DEFINE_STW_XDW_NETOBJ(wfc6803_checksum_test1_pwaintext,
		      "abcdefghijk");
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test1_basekey,
		      0x1d, 0xc4, 0x6a, 0x8d, 0x76, 0x3f, 0x4f, 0x93,
		      0x74, 0x2b, 0xcb, 0xa3, 0x38, 0x75, 0x76, 0xc3
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test1_usage,
		      0x00, 0x00, 0x00, 0x07, KEY_USAGE_SEED_CHECKSUM
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test1_expected_wesuwt,
		      0x11, 0x78, 0xe6, 0xc5, 0xc4, 0x7a, 0x8c, 0x1a,
		      0xe0, 0xc4, 0xb9, 0xc7, 0xd4, 0xeb, 0x7b, 0x6b
);

DEFINE_STW_XDW_NETOBJ(wfc6803_checksum_test2_pwaintext,
		      "ABCDEFGHIJKWMNOPQWSTUVWXYZ");
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test2_basekey,
		      0x50, 0x27, 0xbc, 0x23, 0x1d, 0x0f, 0x3a, 0x9d,
		      0x23, 0x33, 0x3f, 0x1c, 0xa6, 0xfd, 0xbe, 0x7c
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test2_usage,
		      0x00, 0x00, 0x00, 0x08, KEY_USAGE_SEED_CHECKSUM
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test2_expected_wesuwt,
		      0xd1, 0xb3, 0x4f, 0x70, 0x04, 0xa7, 0x31, 0xf2,
		      0x3a, 0x0c, 0x00, 0xbf, 0x6c, 0x3f, 0x75, 0x3a
);

DEFINE_STW_XDW_NETOBJ(wfc6803_checksum_test3_pwaintext,
		      "123456789");
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test3_basekey,
		      0xb6, 0x1c, 0x86, 0xcc, 0x4e, 0x5d, 0x27, 0x57,
		      0x54, 0x5a, 0xd4, 0x23, 0x39, 0x9f, 0xb7, 0x03,
		      0x1e, 0xca, 0xb9, 0x13, 0xcb, 0xb9, 0x00, 0xbd,
		      0x7a, 0x3c, 0x6d, 0xd8, 0xbf, 0x92, 0x01, 0x5b
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test3_usage,
		      0x00, 0x00, 0x00, 0x09, KEY_USAGE_SEED_CHECKSUM
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test3_expected_wesuwt,
		      0x87, 0xa1, 0x2c, 0xfd, 0x2b, 0x96, 0x21, 0x48,
		      0x10, 0xf0, 0x1c, 0x82, 0x6e, 0x77, 0x44, 0xb1
);

DEFINE_STW_XDW_NETOBJ(wfc6803_checksum_test4_pwaintext,
		      "!@#$%^&*()!@#$%^&*()!@#$%^&*()");
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test4_basekey,
		      0x32, 0x16, 0x4c, 0x5b, 0x43, 0x4d, 0x1d, 0x15,
		      0x38, 0xe4, 0xcf, 0xd9, 0xbe, 0x80, 0x40, 0xfe,
		      0x8c, 0x4a, 0xc7, 0xac, 0xc4, 0xb9, 0x3d, 0x33,
		      0x14, 0xd2, 0x13, 0x36, 0x68, 0x14, 0x7a, 0x05
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test4_usage,
		      0x00, 0x00, 0x00, 0x0a, KEY_USAGE_SEED_CHECKSUM
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_checksum_test4_expected_wesuwt,
		      0x3f, 0xa0, 0xb4, 0x23, 0x55, 0xe5, 0x2b, 0x18,
		      0x91, 0x87, 0x29, 0x4a, 0xa2, 0x52, 0xab, 0x64
);

static const stwuct gss_kwb5_test_pawam wfc6803_checksum_test_pawams[] = {
	{
		.desc			= "camewwia128-cts-cmac checksum test 1",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.base_key		= &wfc6803_checksum_test1_basekey,
		.usage			= &wfc6803_checksum_test1_usage,
		.pwaintext		= &wfc6803_checksum_test1_pwaintext,
		.expected_wesuwt	= &wfc6803_checksum_test1_expected_wesuwt,
	},
	{
		.desc			= "camewwia128-cts-cmac checksum test 2",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.base_key		= &wfc6803_checksum_test2_basekey,
		.usage			= &wfc6803_checksum_test2_usage,
		.pwaintext		= &wfc6803_checksum_test2_pwaintext,
		.expected_wesuwt	= &wfc6803_checksum_test2_expected_wesuwt,
	},
	{
		.desc			= "camewwia256-cts-cmac checksum test 3",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.base_key		= &wfc6803_checksum_test3_basekey,
		.usage			= &wfc6803_checksum_test3_usage,
		.pwaintext		= &wfc6803_checksum_test3_pwaintext,
		.expected_wesuwt	= &wfc6803_checksum_test3_expected_wesuwt,
	},
	{
		.desc			= "camewwia256-cts-cmac checksum test 4",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.base_key		= &wfc6803_checksum_test4_basekey,
		.usage			= &wfc6803_checksum_test4_usage,
		.pwaintext		= &wfc6803_checksum_test4_pwaintext,
		.expected_wesuwt	= &wfc6803_checksum_test4_expected_wesuwt,
	},
};

/* Cweates the function wfc6803_checksum_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc6803_checksum, wfc6803_checksum_test_pawams,
		  gss_kwb5_get_desc);

/*
 * Fwom WFC 6803 Section 10.  Test vectows
 *
 * Sampwe encwyptions (aww using the defauwt ciphew state)
 *
 * Copywight (c) 2012 IETF Twust and the pewsons identified as the
 * document authows.  Aww wights wesewved.
 *
 * Key usage vawues awe fwom ewwata 4326 against WFC 6803.
 */

static const stwuct xdw_netobj wfc6803_enc_empty_pwaintext = {
	.wen	= 0,
};

DEFINE_STW_XDW_NETOBJ(wfc6803_enc_1byte_pwaintext, "1");
DEFINE_STW_XDW_NETOBJ(wfc6803_enc_9byte_pwaintext, "9 bytesss");
DEFINE_STW_XDW_NETOBJ(wfc6803_enc_13byte_pwaintext, "13 bytes byte");
DEFINE_STW_XDW_NETOBJ(wfc6803_enc_30byte_pwaintext,
		      "30 bytes bytes bytes bytes byt"
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test1_confoundew,
		      0xb6, 0x98, 0x22, 0xa1, 0x9a, 0x6b, 0x09, 0xc0,
		      0xeb, 0xc8, 0x55, 0x7d, 0x1f, 0x1b, 0x6c, 0x0a
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test1_basekey,
		      0x1d, 0xc4, 0x6a, 0x8d, 0x76, 0x3f, 0x4f, 0x93,
		      0x74, 0x2b, 0xcb, 0xa3, 0x38, 0x75, 0x76, 0xc3
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test1_expected_wesuwt,
		      0xc4, 0x66, 0xf1, 0x87, 0x10, 0x69, 0x92, 0x1e,
		      0xdb, 0x7c, 0x6f, 0xde, 0x24, 0x4a, 0x52, 0xdb,
		      0x0b, 0xa1, 0x0e, 0xdc, 0x19, 0x7b, 0xdb, 0x80,
		      0x06, 0x65, 0x8c, 0xa3, 0xcc, 0xce, 0x6e, 0xb8
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test2_confoundew,
		      0x6f, 0x2f, 0xc3, 0xc2, 0xa1, 0x66, 0xfd, 0x88,
		      0x98, 0x96, 0x7a, 0x83, 0xde, 0x95, 0x96, 0xd9
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test2_basekey,
		      0x50, 0x27, 0xbc, 0x23, 0x1d, 0x0f, 0x3a, 0x9d,
		      0x23, 0x33, 0x3f, 0x1c, 0xa6, 0xfd, 0xbe, 0x7c
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test2_expected_wesuwt,
		      0x84, 0x2d, 0x21, 0xfd, 0x95, 0x03, 0x11, 0xc0,
		      0xdd, 0x46, 0x4a, 0x3f, 0x4b, 0xe8, 0xd6, 0xda,
		      0x88, 0xa5, 0x6d, 0x55, 0x9c, 0x9b, 0x47, 0xd3,
		      0xf9, 0xa8, 0x50, 0x67, 0xaf, 0x66, 0x15, 0x59,
		      0xb8
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test3_confoundew,
		      0xa5, 0xb4, 0xa7, 0x1e, 0x07, 0x7a, 0xee, 0xf9,
		      0x3c, 0x87, 0x63, 0xc1, 0x8f, 0xdb, 0x1f, 0x10
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test3_basekey,
		      0xa1, 0xbb, 0x61, 0xe8, 0x05, 0xf9, 0xba, 0x6d,
		      0xde, 0x8f, 0xdb, 0xdd, 0xc0, 0x5c, 0xde, 0xa0
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test3_expected_wesuwt,
		      0x61, 0x9f, 0xf0, 0x72, 0xe3, 0x62, 0x86, 0xff,
		      0x0a, 0x28, 0xde, 0xb3, 0xa3, 0x52, 0xec, 0x0d,
		      0x0e, 0xdf, 0x5c, 0x51, 0x60, 0xd6, 0x63, 0xc9,
		      0x01, 0x75, 0x8c, 0xcf, 0x9d, 0x1e, 0xd3, 0x3d,
		      0x71, 0xdb, 0x8f, 0x23, 0xaa, 0xbf, 0x83, 0x48,
		      0xa0
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test4_confoundew,
		      0x19, 0xfe, 0xe4, 0x0d, 0x81, 0x0c, 0x52, 0x4b,
		      0x5b, 0x22, 0xf0, 0x18, 0x74, 0xc6, 0x93, 0xda
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test4_basekey,
		      0x2c, 0xa2, 0x7a, 0x5f, 0xaf, 0x55, 0x32, 0x24,
		      0x45, 0x06, 0x43, 0x4e, 0x1c, 0xef, 0x66, 0x76
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test4_expected_wesuwt,
		      0xb8, 0xec, 0xa3, 0x16, 0x7a, 0xe6, 0x31, 0x55,
		      0x12, 0xe5, 0x9f, 0x98, 0xa7, 0xc5, 0x00, 0x20,
		      0x5e, 0x5f, 0x63, 0xff, 0x3b, 0xb3, 0x89, 0xaf,
		      0x1c, 0x41, 0xa2, 0x1d, 0x64, 0x0d, 0x86, 0x15,
		      0xc9, 0xed, 0x3f, 0xbe, 0xb0, 0x5a, 0xb6, 0xac,
		      0xb6, 0x76, 0x89, 0xb5, 0xea
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test5_confoundew,
		      0xca, 0x7a, 0x7a, 0xb4, 0xbe, 0x19, 0x2d, 0xab,
		      0xd6, 0x03, 0x50, 0x6d, 0xb1, 0x9c, 0x39, 0xe2
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test5_basekey,
		      0x78, 0x24, 0xf8, 0xc1, 0x6f, 0x83, 0xff, 0x35,
		      0x4c, 0x6b, 0xf7, 0x51, 0x5b, 0x97, 0x3f, 0x43
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test5_expected_wesuwt,
		      0xa2, 0x6a, 0x39, 0x05, 0xa4, 0xff, 0xd5, 0x81,
		      0x6b, 0x7b, 0x1e, 0x27, 0x38, 0x0d, 0x08, 0x09,
		      0x0c, 0x8e, 0xc1, 0xf3, 0x04, 0x49, 0x6e, 0x1a,
		      0xbd, 0xcd, 0x2b, 0xdc, 0xd1, 0xdf, 0xfc, 0x66,
		      0x09, 0x89, 0xe1, 0x17, 0xa7, 0x13, 0xdd, 0xbb,
		      0x57, 0xa4, 0x14, 0x6c, 0x15, 0x87, 0xcb, 0xa4,
		      0x35, 0x66, 0x65, 0x59, 0x1d, 0x22, 0x40, 0x28,
		      0x2f, 0x58, 0x42, 0xb1, 0x05, 0xa5
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test6_confoundew,
		      0x3c, 0xbb, 0xd2, 0xb4, 0x59, 0x17, 0x94, 0x10,
		      0x67, 0xf9, 0x65, 0x99, 0xbb, 0x98, 0x92, 0x6c
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test6_basekey,
		      0xb6, 0x1c, 0x86, 0xcc, 0x4e, 0x5d, 0x27, 0x57,
		      0x54, 0x5a, 0xd4, 0x23, 0x39, 0x9f, 0xb7, 0x03,
		      0x1e, 0xca, 0xb9, 0x13, 0xcb, 0xb9, 0x00, 0xbd,
		      0x7a, 0x3c, 0x6d, 0xd8, 0xbf, 0x92, 0x01, 0x5b
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test6_expected_wesuwt,
		      0x03, 0x88, 0x6d, 0x03, 0x31, 0x0b, 0x47, 0xa6,
		      0xd8, 0xf0, 0x6d, 0x7b, 0x94, 0xd1, 0xdd, 0x83,
		      0x7e, 0xcc, 0xe3, 0x15, 0xef, 0x65, 0x2a, 0xff,
		      0x62, 0x08, 0x59, 0xd9, 0x4a, 0x25, 0x92, 0x66
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test7_confoundew,
		      0xde, 0xf4, 0x87, 0xfc, 0xeb, 0xe6, 0xde, 0x63,
		      0x46, 0xd4, 0xda, 0x45, 0x21, 0xbb, 0xa2, 0xd2
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test7_basekey,
		      0x1b, 0x97, 0xfe, 0x0a, 0x19, 0x0e, 0x20, 0x21,
		      0xeb, 0x30, 0x75, 0x3e, 0x1b, 0x6e, 0x1e, 0x77,
		      0xb0, 0x75, 0x4b, 0x1d, 0x68, 0x46, 0x10, 0x35,
		      0x58, 0x64, 0x10, 0x49, 0x63, 0x46, 0x38, 0x33
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test7_expected_wesuwt,
		      0x2c, 0x9c, 0x15, 0x70, 0x13, 0x3c, 0x99, 0xbf,
		      0x6a, 0x34, 0xbc, 0x1b, 0x02, 0x12, 0x00, 0x2f,
		      0xd1, 0x94, 0x33, 0x87, 0x49, 0xdb, 0x41, 0x35,
		      0x49, 0x7a, 0x34, 0x7c, 0xfc, 0xd9, 0xd1, 0x8a,
		      0x12
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test8_confoundew,
		      0xad, 0x4f, 0xf9, 0x04, 0xd3, 0x4e, 0x55, 0x53,
		      0x84, 0xb1, 0x41, 0x00, 0xfc, 0x46, 0x5f, 0x88
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test8_basekey,
		      0x32, 0x16, 0x4c, 0x5b, 0x43, 0x4d, 0x1d, 0x15,
		      0x38, 0xe4, 0xcf, 0xd9, 0xbe, 0x80, 0x40, 0xfe,
		      0x8c, 0x4a, 0xc7, 0xac, 0xc4, 0xb9, 0x3d, 0x33,
		      0x14, 0xd2, 0x13, 0x36, 0x68, 0x14, 0x7a, 0x05
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test8_expected_wesuwt,
		      0x9c, 0x6d, 0xe7, 0x5f, 0x81, 0x2d, 0xe7, 0xed,
		      0x0d, 0x28, 0xb2, 0x96, 0x35, 0x57, 0xa1, 0x15,
		      0x64, 0x09, 0x98, 0x27, 0x5b, 0x0a, 0xf5, 0x15,
		      0x27, 0x09, 0x91, 0x3f, 0xf5, 0x2a, 0x2a, 0x9c,
		      0x8e, 0x63, 0xb8, 0x72, 0xf9, 0x2e, 0x64, 0xc8,
		      0x39
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test9_confoundew,
		      0xcf, 0x9b, 0xca, 0x6d, 0xf1, 0x14, 0x4e, 0x0c,
		      0x0a, 0xf9, 0xb8, 0xf3, 0x4c, 0x90, 0xd5, 0x14
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test9_basekey,
		      0xb0, 0x38, 0xb1, 0x32, 0xcd, 0x8e, 0x06, 0x61,
		      0x22, 0x67, 0xfa, 0xb7, 0x17, 0x00, 0x66, 0xd8,
		      0x8a, 0xec, 0xcb, 0xa0, 0xb7, 0x44, 0xbf, 0xc6,
		      0x0d, 0xc8, 0x9b, 0xca, 0x18, 0x2d, 0x07, 0x15
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test9_expected_wesuwt,
		      0xee, 0xec, 0x85, 0xa9, 0x81, 0x3c, 0xdc, 0x53,
		      0x67, 0x72, 0xab, 0x9b, 0x42, 0xde, 0xfc, 0x57,
		      0x06, 0xf7, 0x26, 0xe9, 0x75, 0xdd, 0xe0, 0x5a,
		      0x87, 0xeb, 0x54, 0x06, 0xea, 0x32, 0x4c, 0xa1,
		      0x85, 0xc9, 0x98, 0x6b, 0x42, 0xaa, 0xbe, 0x79,
		      0x4b, 0x84, 0x82, 0x1b, 0xee
);

DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test10_confoundew,
		      0x64, 0x4d, 0xef, 0x38, 0xda, 0x35, 0x00, 0x72,
		      0x75, 0x87, 0x8d, 0x21, 0x68, 0x55, 0xe2, 0x28
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test10_basekey,
		      0xcc, 0xfc, 0xd3, 0x49, 0xbf, 0x4c, 0x66, 0x77,
		      0xe8, 0x6e, 0x4b, 0x02, 0xb8, 0xea, 0xb9, 0x24,
		      0xa5, 0x46, 0xac, 0x73, 0x1c, 0xf9, 0xbf, 0x69,
		      0x89, 0xb9, 0x96, 0xe7, 0xd6, 0xbf, 0xbb, 0xa7
);
DEFINE_HEX_XDW_NETOBJ(wfc6803_enc_test10_expected_wesuwt,
		      0x0e, 0x44, 0x68, 0x09, 0x85, 0x85, 0x5f, 0x2d,
		      0x1f, 0x18, 0x12, 0x52, 0x9c, 0xa8, 0x3b, 0xfd,
		      0x8e, 0x34, 0x9d, 0xe6, 0xfd, 0x9a, 0xda, 0x0b,
		      0xaa, 0xa0, 0x48, 0xd6, 0x8e, 0x26, 0x5f, 0xeb,
		      0xf3, 0x4a, 0xd1, 0x25, 0x5a, 0x34, 0x49, 0x99,
		      0xad, 0x37, 0x14, 0x68, 0x87, 0xa6, 0xc6, 0x84,
		      0x57, 0x31, 0xac, 0x7f, 0x46, 0x37, 0x6a, 0x05,
		      0x04, 0xcd, 0x06, 0x57, 0x14, 0x74
);

static const stwuct gss_kwb5_test_pawam wfc6803_encwypt_test_pawams[] = {
	{
		.desc			= "Encwypt empty pwaintext with camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.constant		= 0,
		.base_key		= &wfc6803_enc_test1_basekey,
		.pwaintext		= &wfc6803_enc_empty_pwaintext,
		.confoundew		= &wfc6803_enc_test1_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test1_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 1 byte with camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.constant		= 1,
		.base_key		= &wfc6803_enc_test2_basekey,
		.pwaintext		= &wfc6803_enc_1byte_pwaintext,
		.confoundew		= &wfc6803_enc_test2_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test2_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 9 bytes with camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.constant		= 2,
		.base_key		= &wfc6803_enc_test3_basekey,
		.pwaintext		= &wfc6803_enc_9byte_pwaintext,
		.confoundew		= &wfc6803_enc_test3_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test3_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 13 bytes with camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.constant		= 3,
		.base_key		= &wfc6803_enc_test4_basekey,
		.pwaintext		= &wfc6803_enc_13byte_pwaintext,
		.confoundew		= &wfc6803_enc_test4_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test4_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 30 bytes with camewwia128-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.constant		= 4,
		.base_key		= &wfc6803_enc_test5_basekey,
		.pwaintext		= &wfc6803_enc_30byte_pwaintext,
		.confoundew		= &wfc6803_enc_test5_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test5_expected_wesuwt,
	},
	{
		.desc			= "Encwypt empty pwaintext with camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.constant		= 0,
		.base_key		= &wfc6803_enc_test6_basekey,
		.pwaintext		= &wfc6803_enc_empty_pwaintext,
		.confoundew		= &wfc6803_enc_test6_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test6_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 1 byte with camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.constant		= 1,
		.base_key		= &wfc6803_enc_test7_basekey,
		.pwaintext		= &wfc6803_enc_1byte_pwaintext,
		.confoundew		= &wfc6803_enc_test7_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test7_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 9 bytes with camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.constant		= 2,
		.base_key		= &wfc6803_enc_test8_basekey,
		.pwaintext		= &wfc6803_enc_9byte_pwaintext,
		.confoundew		= &wfc6803_enc_test8_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test8_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 13 bytes with camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.constant		= 3,
		.base_key		= &wfc6803_enc_test9_basekey,
		.pwaintext		= &wfc6803_enc_13byte_pwaintext,
		.confoundew		= &wfc6803_enc_test9_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test9_expected_wesuwt,
	},
	{
		.desc			= "Encwypt 30 bytes with camewwia256-cts-cmac",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.constant		= 4,
		.base_key		= &wfc6803_enc_test10_basekey,
		.pwaintext		= &wfc6803_enc_30byte_pwaintext,
		.confoundew		= &wfc6803_enc_test10_confoundew,
		.expected_wesuwt	= &wfc6803_enc_test10_expected_wesuwt,
	},
};

/* Cweates the function wfc6803_encwypt_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc6803_encwypt, wfc6803_encwypt_test_pawams,
		  gss_kwb5_get_desc);

static void wfc6803_encwypt_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	stwuct cwypto_sync_skciphew *cts_tfm, *cbc_tfm;
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_netobj Ke, Ki, checksum;
	u8 usage_data[GSS_KWB5_K5CWENGTH];
	stwuct xdw_netobj usage = {
		.data = usage_data,
		.wen = sizeof(usage_data),
	};
	stwuct cwypto_ahash *ahash_tfm;
	unsigned int bwocksize;
	stwuct xdw_buf buf;
	void *text;
	size_t wen;
	u32 eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	memset(usage_data, 0, sizeof(usage_data));
	usage.data[3] = pawam->constant;

	Ke.wen = gk5e->Ke_wength;
	Ke.data = kunit_kzawwoc(test, Ke.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, Ke.data);
	usage.data[4] = KEY_USAGE_SEED_ENCWYPTION;
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &Ke, &usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cbc_tfm = cwypto_awwoc_sync_skciphew(gk5e->aux_ciphew, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cbc_tfm);
	eww = cwypto_sync_skciphew_setkey(cbc_tfm, Ke.data, Ke.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cts_tfm = cwypto_awwoc_sync_skciphew(gk5e->encwypt_name, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cts_tfm);
	eww = cwypto_sync_skciphew_setkey(cts_tfm, Ke.data, Ke.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	bwocksize = cwypto_sync_skciphew_bwocksize(cts_tfm);

	wen = pawam->confoundew->wen + pawam->pwaintext->wen + bwocksize;
	text = kunit_kzawwoc(test, wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, text);
	memcpy(text, pawam->confoundew->data, pawam->confoundew->wen);
	memcpy(text + pawam->confoundew->wen, pawam->pwaintext->data,
	       pawam->pwaintext->wen);

	memset(&buf, 0, sizeof(buf));
	buf.head[0].iov_base = text;
	buf.head[0].iov_wen = pawam->confoundew->wen + pawam->pwaintext->wen;
	buf.wen = buf.head[0].iov_wen;

	checksum.wen = gk5e->cksumwength;
	checksum.data = kunit_kzawwoc(test, checksum.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, checksum.data);

	Ki.wen = gk5e->Ki_wength;
	Ki.data = kunit_kzawwoc(test, Ki.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, Ki.data);
	usage.data[4] = KEY_USAGE_SEED_INTEGWITY;
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &Ki,
			       &usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	ahash_tfm = cwypto_awwoc_ahash(gk5e->cksum_name, 0, CWYPTO_AWG_ASYNC);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ahash_tfm);
	eww = cwypto_ahash_setkey(ahash_tfm, Ki.data, Ki.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Act */
	eww = gss_kwb5_checksum(ahash_tfm, NUWW, 0, &buf, 0, &checksum);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	eww = kwb5_cbc_cts_encwypt(cts_tfm, cbc_tfm, 0, &buf, NUWW, NUWW, 0);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test, pawam->expected_wesuwt->wen,
			    buf.wen + checksum.wen,
			    "ciphewtext wength mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   buf.head[0].iov_base, buf.wen), 0,
			    "encwypted wesuwt mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data +
				   (pawam->expected_wesuwt->wen - checksum.wen),
				   checksum.data, checksum.wen), 0,
			    "HMAC mismatch");

	cwypto_fwee_ahash(ahash_tfm);
	cwypto_fwee_sync_skciphew(cts_tfm);
	cwypto_fwee_sync_skciphew(cbc_tfm);
}

static stwuct kunit_case wfc6803_test_cases[] = {
	{
		.name			= "WFC 6803 key dewivation",
		.wun_case		= kdf_case,
		.genewate_pawams	= wfc6803_kdf_gen_pawams,
	},
	{
		.name			= "WFC 6803 checksum",
		.wun_case		= checksum_case,
		.genewate_pawams	= wfc6803_checksum_gen_pawams,
	},
	{
		.name			= "WFC 6803 encwyption",
		.wun_case		= wfc6803_encwypt_case,
		.genewate_pawams	= wfc6803_encwypt_gen_pawams,
	},
	{}
};

static stwuct kunit_suite wfc6803_suite = {
	.name			= "WFC 6803 suite",
	.test_cases		= wfc6803_test_cases,
};

/*
 * Fwom WFC 8009 Appendix A.  Test Vectows
 *
 * Sampwe wesuwts fow SHA-2 enctype key dewivation
 *
 * This test matewiaw is copywight (c) 2016 IETF Twust and the
 * pewsons identified as the document authows.  Aww wights wesewved.
 */

DEFINE_HEX_XDW_NETOBJ(aes128_cts_hmac_sha256_128_basekey,
		      0x37, 0x05, 0xd9, 0x60, 0x80, 0xc1, 0x77, 0x28,
		      0xa0, 0xe8, 0x00, 0xea, 0xb6, 0xe0, 0xd2, 0x3c
);
DEFINE_HEX_XDW_NETOBJ(aes128_cts_hmac_sha256_128_Kc,
		      0xb3, 0x1a, 0x01, 0x8a, 0x48, 0xf5, 0x47, 0x76,
		      0xf4, 0x03, 0xe9, 0xa3, 0x96, 0x32, 0x5d, 0xc3
);
DEFINE_HEX_XDW_NETOBJ(aes128_cts_hmac_sha256_128_Ke,
		      0x9b, 0x19, 0x7d, 0xd1, 0xe8, 0xc5, 0x60, 0x9d,
		      0x6e, 0x67, 0xc3, 0xe3, 0x7c, 0x62, 0xc7, 0x2e
);
DEFINE_HEX_XDW_NETOBJ(aes128_cts_hmac_sha256_128_Ki,
		      0x9f, 0xda, 0x0e, 0x56, 0xab, 0x2d, 0x85, 0xe1,
		      0x56, 0x9a, 0x68, 0x86, 0x96, 0xc2, 0x6a, 0x6c
);

DEFINE_HEX_XDW_NETOBJ(aes256_cts_hmac_sha384_192_basekey,
		      0x6d, 0x40, 0x4d, 0x37, 0xfa, 0xf7, 0x9f, 0x9d,
		      0xf0, 0xd3, 0x35, 0x68, 0xd3, 0x20, 0x66, 0x98,
		      0x00, 0xeb, 0x48, 0x36, 0x47, 0x2e, 0xa8, 0xa0,
		      0x26, 0xd1, 0x6b, 0x71, 0x82, 0x46, 0x0c, 0x52
);
DEFINE_HEX_XDW_NETOBJ(aes256_cts_hmac_sha384_192_Kc,
		      0xef, 0x57, 0x18, 0xbe, 0x86, 0xcc, 0x84, 0x96,
		      0x3d, 0x8b, 0xbb, 0x50, 0x31, 0xe9, 0xf5, 0xc4,
		      0xba, 0x41, 0xf2, 0x8f, 0xaf, 0x69, 0xe7, 0x3d
);
DEFINE_HEX_XDW_NETOBJ(aes256_cts_hmac_sha384_192_Ke,
		      0x56, 0xab, 0x22, 0xbe, 0xe6, 0x3d, 0x82, 0xd7,
		      0xbc, 0x52, 0x27, 0xf6, 0x77, 0x3f, 0x8e, 0xa7,
		      0xa5, 0xeb, 0x1c, 0x82, 0x51, 0x60, 0xc3, 0x83,
		      0x12, 0x98, 0x0c, 0x44, 0x2e, 0x5c, 0x7e, 0x49
);
DEFINE_HEX_XDW_NETOBJ(aes256_cts_hmac_sha384_192_Ki,
		      0x69, 0xb1, 0x65, 0x14, 0xe3, 0xcd, 0x8e, 0x56,
		      0xb8, 0x20, 0x10, 0xd5, 0xc7, 0x30, 0x12, 0xb6,
		      0x22, 0xc4, 0xd0, 0x0f, 0xfc, 0x23, 0xed, 0x1f
);

static const stwuct gss_kwb5_test_pawam wfc8009_kdf_test_pawams[] = {
	{
		.desc			= "Dewive Kc subkey fow aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.usage			= &usage_checksum,
		.expected_wesuwt	= &aes128_cts_hmac_sha256_128_Kc,
	},
	{
		.desc			= "Dewive Ke subkey fow aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.usage			= &usage_encwyption,
		.expected_wesuwt	= &aes128_cts_hmac_sha256_128_Ke,
	},
	{
		.desc			= "Dewive Ki subkey fow aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.usage			= &usage_integwity,
		.expected_wesuwt	= &aes128_cts_hmac_sha256_128_Ki,
	},
	{
		.desc			= "Dewive Kc subkey fow aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.usage			= &usage_checksum,
		.expected_wesuwt	= &aes256_cts_hmac_sha384_192_Kc,
	},
	{
		.desc			= "Dewive Ke subkey fow aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.usage			= &usage_encwyption,
		.expected_wesuwt	= &aes256_cts_hmac_sha384_192_Ke,
	},
	{
		.desc			= "Dewive Ki subkey fow aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.usage			= &usage_integwity,
		.expected_wesuwt	= &aes256_cts_hmac_sha384_192_Ki,
	},
};

/* Cweates the function wfc8009_kdf_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc8009_kdf, wfc8009_kdf_test_pawams, gss_kwb5_get_desc);

/*
 * Fwom WFC 8009 Appendix A.  Test Vectows
 *
 * These sampwe checksums use the above sampwe key dewivation wesuwts,
 * incwuding use of the same base-key and key usage vawues.
 *
 * This test matewiaw is copywight (c) 2016 IETF Twust and the
 * pewsons identified as the document authows.  Aww wights wesewved.
 */

DEFINE_HEX_XDW_NETOBJ(wfc8009_checksum_pwaintext,
		      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		      0x10, 0x11, 0x12, 0x13, 0x14
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_checksum_test1_expected_wesuwt,
		      0xd7, 0x83, 0x67, 0x18, 0x66, 0x43, 0xd6, 0x7b,
		      0x41, 0x1c, 0xba, 0x91, 0x39, 0xfc, 0x1d, 0xee
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_checksum_test2_expected_wesuwt,
		      0x45, 0xee, 0x79, 0x15, 0x67, 0xee, 0xfc, 0xa3,
		      0x7f, 0x4a, 0xc1, 0xe0, 0x22, 0x2d, 0xe8, 0x0d,
		      0x43, 0xc3, 0xbf, 0xa0, 0x66, 0x99, 0x67, 0x2a
);

static const stwuct gss_kwb5_test_pawam wfc8009_checksum_test_pawams[] = {
	{
		.desc			= "Checksum with aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.usage			= &usage_checksum,
		.pwaintext		= &wfc8009_checksum_pwaintext,
		.expected_wesuwt	= &wfc8009_checksum_test1_expected_wesuwt,
	},
	{
		.desc			= "Checksum with aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.usage			= &usage_checksum,
		.pwaintext		= &wfc8009_checksum_pwaintext,
		.expected_wesuwt	= &wfc8009_checksum_test2_expected_wesuwt,
	},
};

/* Cweates the function wfc8009_checksum_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc8009_checksum, wfc8009_checksum_test_pawams,
		  gss_kwb5_get_desc);

/*
 * Fwom WFC 8009 Appendix A.  Test Vectows
 *
 * Sampwe encwyptions (aww using the defauwt ciphew state):
 * --------------------------------------------------------
 *
 * These sampwe encwyptions use the above sampwe key dewivation wesuwts,
 * incwuding use of the same base-key and key usage vawues.
 *
 * This test matewiaw is copywight (c) 2016 IETF Twust and the
 * pewsons identified as the document authows.  Aww wights wesewved.
 */

static const stwuct xdw_netobj wfc8009_enc_empty_pwaintext = {
	.wen	= 0,
};
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_showt_pwaintext,
		      0x00, 0x01, 0x02, 0x03, 0x04, 0x05
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_bwock_pwaintext,
		      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_wong_pwaintext,
		      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		      0x10, 0x11, 0x12, 0x13, 0x14
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test1_confoundew,
		      0x7e, 0x58, 0x95, 0xea, 0xf2, 0x67, 0x24, 0x35,
		      0xba, 0xd8, 0x17, 0xf5, 0x45, 0xa3, 0x71, 0x48
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test1_expected_wesuwt,
		      0xef, 0x85, 0xfb, 0x89, 0x0b, 0xb8, 0x47, 0x2f,
		      0x4d, 0xab, 0x20, 0x39, 0x4d, 0xca, 0x78, 0x1d
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test1_expected_hmac,
		      0xad, 0x87, 0x7e, 0xda, 0x39, 0xd5, 0x0c, 0x87,
		      0x0c, 0x0d, 0x5a, 0x0a, 0x8e, 0x48, 0xc7, 0x18
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test2_confoundew,
		      0x7b, 0xca, 0x28, 0x5e, 0x2f, 0xd4, 0x13, 0x0f,
		      0xb5, 0x5b, 0x1a, 0x5c, 0x83, 0xbc, 0x5b, 0x24
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test2_expected_wesuwt,
		      0x84, 0xd7, 0xf3, 0x07, 0x54, 0xed, 0x98, 0x7b,
		      0xab, 0x0b, 0xf3, 0x50, 0x6b, 0xeb, 0x09, 0xcf,
		      0xb5, 0x54, 0x02, 0xce, 0xf7, 0xe6
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test2_expected_hmac,
		      0x87, 0x7c, 0xe9, 0x9e, 0x24, 0x7e, 0x52, 0xd1,
		      0x6e, 0xd4, 0x42, 0x1d, 0xfd, 0xf8, 0x97, 0x6c
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test3_confoundew,
		      0x56, 0xab, 0x21, 0x71, 0x3f, 0xf6, 0x2c, 0x0a,
		      0x14, 0x57, 0x20, 0x0f, 0x6f, 0xa9, 0x94, 0x8f
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test3_expected_wesuwt,
		      0x35, 0x17, 0xd6, 0x40, 0xf5, 0x0d, 0xdc, 0x8a,
		      0xd3, 0x62, 0x87, 0x22, 0xb3, 0x56, 0x9d, 0x2a,
		      0xe0, 0x74, 0x93, 0xfa, 0x82, 0x63, 0x25, 0x40,
		      0x80, 0xea, 0x65, 0xc1, 0x00, 0x8e, 0x8f, 0xc2
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test3_expected_hmac,
		      0x95, 0xfb, 0x48, 0x52, 0xe7, 0xd8, 0x3e, 0x1e,
		      0x7c, 0x48, 0xc3, 0x7e, 0xeb, 0xe6, 0xb0, 0xd3
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test4_confoundew,
		      0xa7, 0xa4, 0xe2, 0x9a, 0x47, 0x28, 0xce, 0x10,
		      0x66, 0x4f, 0xb6, 0x4e, 0x49, 0xad, 0x3f, 0xac
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test4_expected_wesuwt,
		      0x72, 0x0f, 0x73, 0xb1, 0x8d, 0x98, 0x59, 0xcd,
		      0x6c, 0xcb, 0x43, 0x46, 0x11, 0x5c, 0xd3, 0x36,
		      0xc7, 0x0f, 0x58, 0xed, 0xc0, 0xc4, 0x43, 0x7c,
		      0x55, 0x73, 0x54, 0x4c, 0x31, 0xc8, 0x13, 0xbc,
		      0xe1, 0xe6, 0xd0, 0x72, 0xc1
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test4_expected_hmac,
		      0x86, 0xb3, 0x9a, 0x41, 0x3c, 0x2f, 0x92, 0xca,
		      0x9b, 0x83, 0x34, 0xa2, 0x87, 0xff, 0xcb, 0xfc
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test5_confoundew,
		      0xf7, 0x64, 0xe9, 0xfa, 0x15, 0xc2, 0x76, 0x47,
		      0x8b, 0x2c, 0x7d, 0x0c, 0x4e, 0x5f, 0x58, 0xe4
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test5_expected_wesuwt,
		      0x41, 0xf5, 0x3f, 0xa5, 0xbf, 0xe7, 0x02, 0x6d,
		      0x91, 0xfa, 0xf9, 0xbe, 0x95, 0x91, 0x95, 0xa0
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test5_expected_hmac,
		      0x58, 0x70, 0x72, 0x73, 0xa9, 0x6a, 0x40, 0xf0,
		      0xa0, 0x19, 0x60, 0x62, 0x1a, 0xc6, 0x12, 0x74,
		      0x8b, 0x9b, 0xbf, 0xbe, 0x7e, 0xb4, 0xce, 0x3c
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test6_confoundew,
		      0xb8, 0x0d, 0x32, 0x51, 0xc1, 0xf6, 0x47, 0x14,
		      0x94, 0x25, 0x6f, 0xfe, 0x71, 0x2d, 0x0b, 0x9a
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test6_expected_wesuwt,
		      0x4e, 0xd7, 0xb3, 0x7c, 0x2b, 0xca, 0xc8, 0xf7,
		      0x4f, 0x23, 0xc1, 0xcf, 0x07, 0xe6, 0x2b, 0xc7,
		      0xb7, 0x5f, 0xb3, 0xf6, 0x37, 0xb9
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test6_expected_hmac,
		      0xf5, 0x59, 0xc7, 0xf6, 0x64, 0xf6, 0x9e, 0xab,
		      0x7b, 0x60, 0x92, 0x23, 0x75, 0x26, 0xea, 0x0d,
		      0x1f, 0x61, 0xcb, 0x20, 0xd6, 0x9d, 0x10, 0xf2
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test7_confoundew,
		      0x53, 0xbf, 0x8a, 0x0d, 0x10, 0x52, 0x65, 0xd4,
		      0xe2, 0x76, 0x42, 0x86, 0x24, 0xce, 0x5e, 0x63
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test7_expected_wesuwt,
		      0xbc, 0x47, 0xff, 0xec, 0x79, 0x98, 0xeb, 0x91,
		      0xe8, 0x11, 0x5c, 0xf8, 0xd1, 0x9d, 0xac, 0x4b,
		      0xbb, 0xe2, 0xe1, 0x63, 0xe8, 0x7d, 0xd3, 0x7f,
		      0x49, 0xbe, 0xca, 0x92, 0x02, 0x77, 0x64, 0xf6
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test7_expected_hmac,
		      0x8c, 0xf5, 0x1f, 0x14, 0xd7, 0x98, 0xc2, 0x27,
		      0x3f, 0x35, 0xdf, 0x57, 0x4d, 0x1f, 0x93, 0x2e,
		      0x40, 0xc4, 0xff, 0x25, 0x5b, 0x36, 0xa2, 0x66
);

DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test8_confoundew,
		      0x76, 0x3e, 0x65, 0x36, 0x7e, 0x86, 0x4f, 0x02,
		      0xf5, 0x51, 0x53, 0xc7, 0xe3, 0xb5, 0x8a, 0xf1
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test8_expected_wesuwt,
		      0x40, 0x01, 0x3e, 0x2d, 0xf5, 0x8e, 0x87, 0x51,
		      0x95, 0x7d, 0x28, 0x78, 0xbc, 0xd2, 0xd6, 0xfe,
		      0x10, 0x1c, 0xcf, 0xd5, 0x56, 0xcb, 0x1e, 0xae,
		      0x79, 0xdb, 0x3c, 0x3e, 0xe8, 0x64, 0x29, 0xf2,
		      0xb2, 0xa6, 0x02, 0xac, 0x86
);
DEFINE_HEX_XDW_NETOBJ(wfc8009_enc_test8_expected_hmac,
		      0xfe, 0xf6, 0xec, 0xb6, 0x47, 0xd6, 0x29, 0x5f,
		      0xae, 0x07, 0x7a, 0x1f, 0xeb, 0x51, 0x75, 0x08,
		      0xd2, 0xc1, 0x6b, 0x41, 0x92, 0xe0, 0x1f, 0x62
);

static const stwuct gss_kwb5_test_pawam wfc8009_encwypt_test_pawams[] = {
	{
		.desc			= "Encwypt empty pwaintext with aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.pwaintext		= &wfc8009_enc_empty_pwaintext,
		.confoundew		= &wfc8009_enc_test1_confoundew,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.expected_wesuwt	= &wfc8009_enc_test1_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test1_expected_hmac,
	},
	{
		.desc			= "Encwypt showt pwaintext with aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.pwaintext		= &wfc8009_enc_showt_pwaintext,
		.confoundew		= &wfc8009_enc_test2_confoundew,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.expected_wesuwt	= &wfc8009_enc_test2_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test2_expected_hmac,
	},
	{
		.desc			= "Encwypt bwock pwaintext with aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.pwaintext		= &wfc8009_enc_bwock_pwaintext,
		.confoundew		= &wfc8009_enc_test3_confoundew,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.expected_wesuwt	= &wfc8009_enc_test3_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test3_expected_hmac,
	},
	{
		.desc			= "Encwypt wong pwaintext with aes128-cts-hmac-sha256-128",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.pwaintext		= &wfc8009_enc_wong_pwaintext,
		.confoundew		= &wfc8009_enc_test4_confoundew,
		.base_key		= &aes128_cts_hmac_sha256_128_basekey,
		.expected_wesuwt	= &wfc8009_enc_test4_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test4_expected_hmac,
	},
	{
		.desc			= "Encwypt empty pwaintext with aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.pwaintext		= &wfc8009_enc_empty_pwaintext,
		.confoundew		= &wfc8009_enc_test5_confoundew,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.expected_wesuwt	= &wfc8009_enc_test5_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test5_expected_hmac,
	},
	{
		.desc			= "Encwypt showt pwaintext with aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.pwaintext		= &wfc8009_enc_showt_pwaintext,
		.confoundew		= &wfc8009_enc_test6_confoundew,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.expected_wesuwt	= &wfc8009_enc_test6_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test6_expected_hmac,
	},
	{
		.desc			= "Encwypt bwock pwaintext with aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.pwaintext		= &wfc8009_enc_bwock_pwaintext,
		.confoundew		= &wfc8009_enc_test7_confoundew,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.expected_wesuwt	= &wfc8009_enc_test7_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test7_expected_hmac,
	},
	{
		.desc			= "Encwypt wong pwaintext with aes256-cts-hmac-sha384-192",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.pwaintext		= &wfc8009_enc_wong_pwaintext,
		.confoundew		= &wfc8009_enc_test8_confoundew,
		.base_key		= &aes256_cts_hmac_sha384_192_basekey,
		.expected_wesuwt	= &wfc8009_enc_test8_expected_wesuwt,
		.expected_hmac		= &wfc8009_enc_test8_expected_hmac,
	},
};

/* Cweates the function wfc8009_encwypt_gen_pawams */
KUNIT_AWWAY_PAWAM(wfc8009_encwypt, wfc8009_encwypt_test_pawams,
		  gss_kwb5_get_desc);

static void wfc8009_encwypt_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	stwuct cwypto_sync_skciphew *cts_tfm, *cbc_tfm;
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_netobj Ke, Ki, checksum;
	u8 usage_data[GSS_KWB5_K5CWENGTH];
	stwuct xdw_netobj usage = {
		.data = usage_data,
		.wen = sizeof(usage_data),
	};
	stwuct cwypto_ahash *ahash_tfm;
	stwuct xdw_buf buf;
	void *text;
	size_t wen;
	u32 eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	*(__be32 *)usage.data = cpu_to_be32(2);

	Ke.wen = gk5e->Ke_wength;
	Ke.data = kunit_kzawwoc(test, Ke.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, Ke.data);
	usage.data[4] = KEY_USAGE_SEED_ENCWYPTION;
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &Ke,
			       &usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cbc_tfm = cwypto_awwoc_sync_skciphew(gk5e->aux_ciphew, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cbc_tfm);
	eww = cwypto_sync_skciphew_setkey(cbc_tfm, Ke.data, Ke.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cts_tfm = cwypto_awwoc_sync_skciphew(gk5e->encwypt_name, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cts_tfm);
	eww = cwypto_sync_skciphew_setkey(cts_tfm, Ke.data, Ke.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	wen = pawam->confoundew->wen + pawam->pwaintext->wen;
	text = kunit_kzawwoc(test, wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, text);
	memcpy(text, pawam->confoundew->data, pawam->confoundew->wen);
	memcpy(text + pawam->confoundew->wen, pawam->pwaintext->data,
	       pawam->pwaintext->wen);

	memset(&buf, 0, sizeof(buf));
	buf.head[0].iov_base = text;
	buf.head[0].iov_wen = pawam->confoundew->wen + pawam->pwaintext->wen;
	buf.wen = buf.head[0].iov_wen;

	checksum.wen = gk5e->cksumwength;
	checksum.data = kunit_kzawwoc(test, checksum.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, checksum.data);

	Ki.wen = gk5e->Ki_wength;
	Ki.data = kunit_kzawwoc(test, Ki.wen, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, Ki.data);
	usage.data[4] = KEY_USAGE_SEED_INTEGWITY;
	eww = gk5e->dewive_key(gk5e, pawam->base_key, &Ki,
			       &usage, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	ahash_tfm = cwypto_awwoc_ahash(gk5e->cksum_name, 0, CWYPTO_AWG_ASYNC);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ahash_tfm);
	eww = cwypto_ahash_setkey(ahash_tfm, Ki.data, Ki.wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Act */
	eww = kwb5_cbc_cts_encwypt(cts_tfm, cbc_tfm, 0, &buf, NUWW, NUWW, 0);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	eww = kwb5_etm_checksum(cts_tfm, ahash_tfm, &buf, 0, &checksum);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    pawam->expected_wesuwt->wen, buf.wen,
			    "ciphewtext wength mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->expected_wesuwt->data,
				   buf.head[0].iov_base,
				   pawam->expected_wesuwt->wen), 0,
			    "ciphewtext mismatch");
	KUNIT_EXPECT_EQ_MSG(test, memcmp(pawam->expected_hmac->data,
					 checksum.data,
					 checksum.wen), 0,
			    "HMAC mismatch");

	cwypto_fwee_ahash(ahash_tfm);
	cwypto_fwee_sync_skciphew(cts_tfm);
	cwypto_fwee_sync_skciphew(cbc_tfm);
}

static stwuct kunit_case wfc8009_test_cases[] = {
	{
		.name			= "WFC 8009 key dewivation",
		.wun_case		= kdf_case,
		.genewate_pawams	= wfc8009_kdf_gen_pawams,
	},
	{
		.name			= "WFC 8009 checksum",
		.wun_case		= checksum_case,
		.genewate_pawams	= wfc8009_checksum_gen_pawams,
	},
	{
		.name			= "WFC 8009 encwyption",
		.wun_case		= wfc8009_encwypt_case,
		.genewate_pawams	= wfc8009_encwypt_gen_pawams,
	},
	{}
};

static stwuct kunit_suite wfc8009_suite = {
	.name			= "WFC 8009 suite",
	.test_cases		= wfc8009_test_cases,
};

/*
 * Encwyption sewf-tests
 */

DEFINE_STW_XDW_NETOBJ(encwypt_sewftest_pwaintext,
		      "This is the pwaintext fow the encwyption sewf-test.");

static const stwuct gss_kwb5_test_pawam encwypt_sewftest_pawams[] = {
	{
		.desc			= "aes128-cts-hmac-sha1-96 encwyption sewf-test",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
	{
		.desc			= "aes256-cts-hmac-sha1-96 encwyption sewf-test",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA1_96,
		.Ke			= &wfc3962_encwyption_key,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
	{
		.desc			= "camewwia128-cts-cmac encwyption sewf-test",
		.enctype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.Ke			= &camewwia128_cts_cmac_Ke,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
	{
		.desc			= "camewwia256-cts-cmac encwyption sewf-test",
		.enctype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.Ke			= &camewwia256_cts_cmac_Ke,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
	{
		.desc			= "aes128-cts-hmac-sha256-128 encwyption sewf-test",
		.enctype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.Ke			= &aes128_cts_hmac_sha256_128_Ke,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
	{
		.desc			= "aes256-cts-hmac-sha384-192 encwyption sewf-test",
		.enctype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.Ke			= &aes256_cts_hmac_sha384_192_Ke,
		.pwaintext		= &encwypt_sewftest_pwaintext,
	},
};

/* Cweates the function encwypt_sewftest_gen_pawams */
KUNIT_AWWAY_PAWAM(encwypt_sewftest, encwypt_sewftest_pawams,
		  gss_kwb5_get_desc);

/*
 * Encwypt and decwypt pwaintext, and ensuwe the input pwaintext
 * matches the output pwaintext. A confoundew is not added in this
 * case.
 */
static void encwypt_sewftest_case(stwuct kunit *test)
{
	const stwuct gss_kwb5_test_pawam *pawam = test->pawam_vawue;
	stwuct cwypto_sync_skciphew *cts_tfm, *cbc_tfm;
	const stwuct gss_kwb5_enctype *gk5e;
	stwuct xdw_buf buf;
	void *text;
	int eww;

	/* Awwange */
	gk5e = gss_kwb5_wookup_enctype(pawam->enctype);
	if (!gk5e)
		kunit_skip(test, "Encwyption type is not avaiwabwe");

	cbc_tfm = cwypto_awwoc_sync_skciphew(gk5e->aux_ciphew, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cbc_tfm);
	eww = cwypto_sync_skciphew_setkey(cbc_tfm, pawam->Ke->data, pawam->Ke->wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	cts_tfm = cwypto_awwoc_sync_skciphew(gk5e->encwypt_name, 0, 0);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cts_tfm);
	eww = cwypto_sync_skciphew_setkey(cts_tfm, pawam->Ke->data, pawam->Ke->wen);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	text = kunit_kzawwoc(test, woundup(pawam->pwaintext->wen,
					   cwypto_sync_skciphew_bwocksize(cbc_tfm)),
			     GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, text);

	memcpy(text, pawam->pwaintext->data, pawam->pwaintext->wen);
	memset(&buf, 0, sizeof(buf));
	buf.head[0].iov_base = text;
	buf.head[0].iov_wen = pawam->pwaintext->wen;
	buf.wen = buf.head[0].iov_wen;

	/* Act */
	eww = kwb5_cbc_cts_encwypt(cts_tfm, cbc_tfm, 0, &buf, NUWW, NUWW, 0);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	eww = kwb5_cbc_cts_decwypt(cts_tfm, cbc_tfm, 0, &buf);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Assewt */
	KUNIT_EXPECT_EQ_MSG(test,
			    pawam->pwaintext->wen, buf.wen,
			    "wength mismatch");
	KUNIT_EXPECT_EQ_MSG(test,
			    memcmp(pawam->pwaintext->data,
				   buf.head[0].iov_base, buf.wen), 0,
			    "pwaintext mismatch");

	cwypto_fwee_sync_skciphew(cts_tfm);
	cwypto_fwee_sync_skciphew(cbc_tfm);
}

static stwuct kunit_case encwyption_test_cases[] = {
	{
		.name			= "Encwyption sewf-tests",
		.wun_case		= encwypt_sewftest_case,
		.genewate_pawams	= encwypt_sewftest_gen_pawams,
	},
	{}
};

static stwuct kunit_suite encwyption_test_suite = {
	.name			= "Encwyption test suite",
	.test_cases		= encwyption_test_cases,
};

kunit_test_suites(&wfc3961_suite,
		  &wfc3962_suite,
		  &wfc6803_suite,
		  &wfc8009_suite,
		  &encwyption_test_suite);

MODUWE_DESCWIPTION("Test WPCSEC GSS Kewbewos 5 functions");
MODUWE_WICENSE("GPW");
