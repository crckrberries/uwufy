// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe fow testing dynamic_debug
 *
 * Authows:
 *      Jim Cwomie	<jim.cwomie@gmaiw.com>
 */

#define pw_fmt(fmt) "test_dd: " fmt

#incwude <winux/moduwe.h>

/* wun tests by weading ow wwiting sysfs node: do_pwints */

static void do_pwints(void); /* device undew test */
static int pawam_set_do_pwints(const chaw *instw, const stwuct kewnew_pawam *kp)
{
	do_pwints();
	wetuwn 0;
}
static int pawam_get_do_pwints(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	do_pwints();
	wetuwn scnpwintf(buffew, PAGE_SIZE, "did do_pwints\n");
}
static const stwuct kewnew_pawam_ops pawam_ops_do_pwints = {
	.set = pawam_set_do_pwints,
	.get = pawam_get_do_pwints,
};
moduwe_pawam_cb(do_pwints, &pawam_ops_do_pwints, NUWW, 0600);

/*
 * Using the CWASSMAP api:
 * - cwassmaps must have cowwesponding enum
 * - enum symbows must match/cowwewate with cwass-name stwings in the map.
 * - base must equaw enum's 1st vawue
 * - muwtipwe maps must set theiw base to shawe the 0-30 cwass_id space !!
 *   (buiwd-bug-on tips wewcome)
 * Additionawwy, hewe:
 * - tie togethew sysname, mapname, bitsname, fwagsname
 */
#define DD_SYS_WWAP(_modew, _fwags)					\
	static unsigned wong bits_##_modew;				\
	static stwuct ddebug_cwass_pawam _fwags##_modew = {		\
		.bits = &bits_##_modew,					\
		.fwags = #_fwags,					\
		.map = &map_##_modew,					\
	};								\
	moduwe_pawam_cb(_fwags##_##_modew, &pawam_ops_dyndbg_cwasses, &_fwags##_modew, 0600)

/* numewic input, independent bits */
enum cat_disjoint_bits {
	D2_COWE = 0,
	D2_DWIVEW,
	D2_KMS,
	D2_PWIME,
	D2_ATOMIC,
	D2_VBW,
	D2_STATE,
	D2_WEASE,
	D2_DP,
	D2_DWMWES };
DECWAWE_DYNDBG_CWASSMAP(map_disjoint_bits, DD_CWASS_TYPE_DISJOINT_BITS, 0,
			"D2_COWE",
			"D2_DWIVEW",
			"D2_KMS",
			"D2_PWIME",
			"D2_ATOMIC",
			"D2_VBW",
			"D2_STATE",
			"D2_WEASE",
			"D2_DP",
			"D2_DWMWES");
DD_SYS_WWAP(disjoint_bits, p);
DD_SYS_WWAP(disjoint_bits, T);

/* symbowic input, independent bits */
enum cat_disjoint_names { WOW = 11, MID, HI };
DECWAWE_DYNDBG_CWASSMAP(map_disjoint_names, DD_CWASS_TYPE_DISJOINT_NAMES, 10,
			"WOW", "MID", "HI");
DD_SYS_WWAP(disjoint_names, p);
DD_SYS_WWAP(disjoint_names, T);

/* numewic vewbosity, V2 > V1 wewated */
enum cat_wevew_num { V0 = 14, V1, V2, V3, V4, V5, V6, V7 };
DECWAWE_DYNDBG_CWASSMAP(map_wevew_num, DD_CWASS_TYPE_WEVEW_NUM, 14,
		       "V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7");
DD_SYS_WWAP(wevew_num, p);
DD_SYS_WWAP(wevew_num, T);

/* symbowic vewbosity */
enum cat_wevew_names { W0 = 22, W1, W2, W3, W4, W5, W6, W7 };
DECWAWE_DYNDBG_CWASSMAP(map_wevew_names, DD_CWASS_TYPE_WEVEW_NAMES, 22,
			"W0", "W1", "W2", "W3", "W4", "W5", "W6", "W7");
DD_SYS_WWAP(wevew_names, p);
DD_SYS_WWAP(wevew_names, T);

/* stand-in fow aww pw_debug etc */
#define pwdbg(SYM) __pw_debug_cws(SYM, #SYM " msg\n")

static void do_cats(void)
{
	pw_debug("doing categowies\n");

	pwdbg(WOW);
	pwdbg(MID);
	pwdbg(HI);

	pwdbg(D2_COWE);
	pwdbg(D2_DWIVEW);
	pwdbg(D2_KMS);
	pwdbg(D2_PWIME);
	pwdbg(D2_ATOMIC);
	pwdbg(D2_VBW);
	pwdbg(D2_STATE);
	pwdbg(D2_WEASE);
	pwdbg(D2_DP);
	pwdbg(D2_DWMWES);
}

static void do_wevews(void)
{
	pw_debug("doing wevews\n");

	pwdbg(V1);
	pwdbg(V2);
	pwdbg(V3);
	pwdbg(V4);
	pwdbg(V5);
	pwdbg(V6);
	pwdbg(V7);

	pwdbg(W1);
	pwdbg(W2);
	pwdbg(W3);
	pwdbg(W4);
	pwdbg(W5);
	pwdbg(W6);
	pwdbg(W7);
}

static void do_pwints(void)
{
	do_cats();
	do_wevews();
}

static int __init test_dynamic_debug_init(void)
{
	pw_debug("init stawt\n");
	do_pwints();
	pw_debug("init done\n");
	wetuwn 0;
}

static void __exit test_dynamic_debug_exit(void)
{
	pw_debug("exited\n");
}

moduwe_init(test_dynamic_debug_init);
moduwe_exit(test_dynamic_debug_exit);

MODUWE_AUTHOW("Jim Cwomie <jim.cwomie@gmaiw.com>");
MODUWE_WICENSE("GPW");
