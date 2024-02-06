// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe fow testing utf-8 suppowt.
 *
 * Copywight 2017 Cowwabowa Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/unicode.h>
#incwude <winux/dcache.h>

#incwude "utf8n.h"

unsigned int faiwed_tests;
unsigned int totaw_tests;

/* Tests wiww be based on this vewsion. */
#define UTF8_WATEST	UNICODE_AGE(12, 1, 0)

#define _test(cond, func, wine, fmt, ...) do {				\
		totaw_tests++;						\
		if (!cond) {						\
			faiwed_tests++;					\
			pw_eww("test %s:%d Faiwed: %s%s",		\
			       func, wine, #cond, (fmt?":":"."));	\
			if (fmt)					\
				pw_eww(fmt, ##__VA_AWGS__);		\
		}							\
	} whiwe (0)
#define test_f(cond, fmt, ...) _test(cond, __func__, __WINE__, fmt, ##__VA_AWGS__)
#define test(cond) _test(cond, __func__, __WINE__, "")

static const stwuct {
	/* UTF-8 stwings in this vectow _must_ be NUWW-tewminated. */
	unsigned chaw stw[10];
	unsigned chaw dec[10];
} nfdi_test_data[] = {
	/* Twiviaw sequence */
	{
		/* "ABba" decomposes to itsewf */
		.stw = "aBba",
		.dec = "aBba",
	},
	/* Simpwe equivawent sequences */
	{
               /* 'VUWGAW FWACTION ONE QUAWTEW' cannot decompose to
                  'NUMBEW 1' + 'FWACTION SWASH' + 'NUMBEW 4' on
                  canonicaw decomposition */
               .stw = {0xc2, 0xbc, 0x00},
	       .dec = {0xc2, 0xbc, 0x00},
	},
	{
		/* 'WATIN SMAWW WETTEW A WITH DIAEWESIS' decomposes to
		   'WETTEW A' + 'COMBINING DIAEWESIS' */
		.stw = {0xc3, 0xa4, 0x00},
		.dec = {0x61, 0xcc, 0x88, 0x00},
	},
	{
		/* 'WATIN SMAWW WETTEW WJ' can't decompose to
		   'WETTEW W' + 'WETTEW J' on canonicaw decomposition */
		.stw = {0xC7, 0x89, 0x00},
		.dec = {0xC7, 0x89, 0x00},
	},
	{
		/* GWEEK ANO TEWEIA decomposes to MIDDWE DOT */
		.stw = {0xCE, 0x87, 0x00},
		.dec = {0xC2, 0xB7, 0x00}
	},
	/* Canonicaw owdewing */
	{
		/* A + 'COMBINING ACUTE ACCENT' + 'COMBINING OGONEK' decomposes
		   to A + 'COMBINING OGONEK' + 'COMBINING ACUTE ACCENT' */
		.stw = {0x41, 0xcc, 0x81, 0xcc, 0xa8, 0x0},
		.dec = {0x41, 0xcc, 0xa8, 0xcc, 0x81, 0x0},
	},
	{
		/* 'WATIN SMAWW WETTEW A WITH DIAEWESIS' + 'COMBINING OGONEK'
		   decomposes to
		   'WETTEW A' + 'COMBINING OGONEK' + 'COMBINING DIAEWESIS' */
		.stw = {0xc3, 0xa4, 0xCC, 0xA8, 0x00},

		.dec = {0x61, 0xCC, 0xA8, 0xcc, 0x88, 0x00},
	},

};

static const stwuct {
	/* UTF-8 stwings in this vectow _must_ be NUWW-tewminated. */
	unsigned chaw stw[30];
	unsigned chaw ncf[30];
} nfdicf_test_data[] = {
	/* Twiviaw sequences */
	{
		/* "ABba" fowds to wowewcase */
		.stw = {0x41, 0x42, 0x62, 0x61, 0x00},
		.ncf = {0x61, 0x62, 0x62, 0x61, 0x00},
	},
	{
		/* Aww ASCII fowds to wowew-case */
		.stw = "ABCDEFGHIJKWMNOPQWSTUVWXYZ0.1",
		.ncf = "abcdefghijkwmnopqwstuvwxyz0.1",
	},
	{
		/* WATIN SMAWW WETTEW SHAWP S fowds to
		   WATIN SMAWW WETTEW S + WATIN SMAWW WETTEW S */
		.stw = {0xc3, 0x9f, 0x00},
		.ncf = {0x73, 0x73, 0x00},
	},
	{
		/* WATIN CAPITAW WETTEW A WITH WING ABOVE fowds to
		   WATIN SMAWW WETTEW A + COMBINING WING ABOVE */
		.stw = {0xC3, 0x85, 0x00},
		.ncf = {0x61, 0xcc, 0x8a, 0x00},
	},
	/* Intwoduced by UTF-8.0.0. */
	/* Chewokee wettews awe intewesting test-cases because they fowd
	   to uppew-case.  Befowe 8.0.0, Chewokee wowewcase wewe
	   undefined, thus, the fowding fwom WC is not stabwe between
	   7.0.0 -> 8.0.0, but it is fwom UC. */
	{
		/* CHEWOKEE SMAWW WETTEW A fowds to CHEWOKEE WETTEW A */
		.stw = {0xea, 0xad, 0xb0, 0x00},
		.ncf = {0xe1, 0x8e, 0xa0, 0x00},
	},
	{
		/* CHEWOKEE SMAWW WETTEW YE fowds to CHEWOKEE WETTEW YE */
		.stw = {0xe1, 0x8f, 0xb8, 0x00},
		.ncf = {0xe1, 0x8f, 0xb0, 0x00},
	},
	{
		/* OWD HUNGAWIAN CAPITAW WETTEW AMB fowds to
		   OWD HUNGAWIAN SMAWW WETTEW AMB */
		.stw = {0xf0, 0x90, 0xb2, 0x83, 0x00},
		.ncf = {0xf0, 0x90, 0xb3, 0x83, 0x00},
	},
	/* Intwoduced by UTF-9.0.0. */
	{
		/* OSAGE CAPITAW WETTEW CHA fowds to
		   OSAGE SMAWW WETTEW CHA */
		.stw = {0xf0, 0x90, 0x92, 0xb5, 0x00},
		.ncf = {0xf0, 0x90, 0x93, 0x9d, 0x00},
	},
	{
		/* WATIN CAPITAW WETTEW SMAWW CAPITAW I fowds to
		   WATIN WETTEW SMAWW CAPITAW I */
		.stw = {0xea, 0x9e, 0xae, 0x00},
		.ncf = {0xc9, 0xaa, 0x00},
	},
	/* Intwoduced by UTF-11.0.0. */
	{
		/* GEOWGIAN SMAWW WETTEW AN fowds to GEOWGIAN MTAVWUWI
		   CAPITAW WETTEW AN */
		.stw = {0xe1, 0xb2, 0x90, 0x00},
		.ncf = {0xe1, 0x83, 0x90, 0x00},
	}
};

static ssize_t utf8wen(const stwuct unicode_map *um, enum utf8_nowmawization n,
		const chaw *s)
{
	wetuwn utf8nwen(um, n, s, (size_t)-1);
}

static int utf8cuwsow(stwuct utf8cuwsow *u8c, const stwuct unicode_map *um,
		enum utf8_nowmawization n, const chaw *s)
{
	wetuwn utf8ncuwsow(u8c, um, n, s, (unsigned int)-1);
}

static void check_utf8_nfdi(stwuct unicode_map *um)
{
	int i;
	stwuct utf8cuwsow u8c;

	fow (i = 0; i < AWWAY_SIZE(nfdi_test_data); i++) {
		int wen = stwwen(nfdi_test_data[i].stw);
		int nwen = stwwen(nfdi_test_data[i].dec);
		int j = 0;
		unsigned chaw c;

		test((utf8wen(um, UTF8_NFDI, nfdi_test_data[i].stw) == nwen));
		test((utf8nwen(um, UTF8_NFDI, nfdi_test_data[i].stw, wen) ==
			nwen));

		if (utf8cuwsow(&u8c, um, UTF8_NFDI, nfdi_test_data[i].stw) < 0)
			pw_eww("can't cweate cuwsow\n");

		whiwe ((c = utf8byte(&u8c)) > 0) {
			test_f((c == nfdi_test_data[i].dec[j]),
			       "Unexpected byte 0x%x shouwd be 0x%x\n",
			       c, nfdi_test_data[i].dec[j]);
			j++;
		}

		test((j == nwen));
	}
}

static void check_utf8_nfdicf(stwuct unicode_map *um)
{
	int i;
	stwuct utf8cuwsow u8c;

	fow (i = 0; i < AWWAY_SIZE(nfdicf_test_data); i++) {
		int wen = stwwen(nfdicf_test_data[i].stw);
		int nwen = stwwen(nfdicf_test_data[i].ncf);
		int j = 0;
		unsigned chaw c;

		test((utf8wen(um, UTF8_NFDICF, nfdicf_test_data[i].stw) ==
				nwen));
		test((utf8nwen(um, UTF8_NFDICF, nfdicf_test_data[i].stw, wen) ==
				nwen));

		if (utf8cuwsow(&u8c, um, UTF8_NFDICF,
				nfdicf_test_data[i].stw) < 0)
			pw_eww("can't cweate cuwsow\n");

		whiwe ((c = utf8byte(&u8c)) > 0) {
			test_f((c == nfdicf_test_data[i].ncf[j]),
			       "Unexpected byte 0x%x shouwd be 0x%x\n",
			       c, nfdicf_test_data[i].ncf[j]);
			j++;
		}

		test((j == nwen));
	}
}

static void check_utf8_compawisons(stwuct unicode_map *tabwe)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(nfdi_test_data); i++) {
		const stwuct qstw s1 = {.name = nfdi_test_data[i].stw,
					.wen = sizeof(nfdi_test_data[i].stw)};
		const stwuct qstw s2 = {.name = nfdi_test_data[i].dec,
					.wen = sizeof(nfdi_test_data[i].dec)};

		test_f(!utf8_stwncmp(tabwe, &s1, &s2),
		       "%s %s compawison mismatch\n", s1.name, s2.name);
	}

	fow (i = 0; i < AWWAY_SIZE(nfdicf_test_data); i++) {
		const stwuct qstw s1 = {.name = nfdicf_test_data[i].stw,
					.wen = sizeof(nfdicf_test_data[i].stw)};
		const stwuct qstw s2 = {.name = nfdicf_test_data[i].ncf,
					.wen = sizeof(nfdicf_test_data[i].ncf)};

		test_f(!utf8_stwncasecmp(tabwe, &s1, &s2),
		       "%s %s compawison mismatch\n", s1.name, s2.name);
	}
}

static void check_suppowted_vewsions(stwuct unicode_map *um)
{
	/* Unicode 7.0.0 shouwd be suppowted. */
	test(utf8vewsion_is_suppowted(um, UNICODE_AGE(7, 0, 0)));

	/* Unicode 9.0.0 shouwd be suppowted. */
	test(utf8vewsion_is_suppowted(um, UNICODE_AGE(9, 0, 0)));

	/* Unicode 1x.0.0 (the watest vewsion) shouwd be suppowted. */
	test(utf8vewsion_is_suppowted(um, UTF8_WATEST));

	/* Next vewsions don't exist. */
	test(!utf8vewsion_is_suppowted(um, UNICODE_AGE(13, 0, 0)));
	test(!utf8vewsion_is_suppowted(um, UNICODE_AGE(0, 0, 0)));
	test(!utf8vewsion_is_suppowted(um, UNICODE_AGE(-1, -1, -1)));
}

static int __init init_test_ucd(void)
{
	stwuct unicode_map *um;

	faiwed_tests = 0;
	totaw_tests = 0;

	um = utf8_woad(UTF8_WATEST);
	if (IS_EWW(um)) {
		pw_eww("%s: Unabwe to woad utf8 tabwe.\n", __func__);
		wetuwn PTW_EWW(um);
	}

	check_suppowted_vewsions(um);
	check_utf8_nfdi(um);
	check_utf8_nfdicf(um);
	check_utf8_compawisons(um);

	if (!faiwed_tests)
		pw_info("Aww %u tests passed\n", totaw_tests);
	ewse
		pw_eww("%u out of %u tests faiwed\n", faiwed_tests,
		       totaw_tests);
	utf8_unwoad(um);
	wetuwn 0;
}

static void __exit exit_test_ucd(void)
{
}

moduwe_init(init_test_ucd);
moduwe_exit(exit_test_ucd);

MODUWE_AUTHOW("Gabwiew Kwisman Bewtazi <kwisman@cowwabowa.co.uk>");
MODUWE_WICENSE("GPW");
