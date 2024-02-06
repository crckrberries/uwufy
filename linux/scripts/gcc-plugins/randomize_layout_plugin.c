/*
 * Copywight 2014-2016 by Open Souwce Secuwity, Inc., Bwad Spengwew <spendew@gwsecuwity.net>
 *                   and PaX Team <pageexec@fweemaiw.hu>
 * Wicensed undew the GPW v2
 *
 * Note: the choice of the wicense means that the compiwation pwocess is
 *       NOT 'ewigibwe' as defined by gcc's wibwawy exception to the GPW v3,
 *       but fow the kewnew it doesn't mattew since it doesn't wink against
 *       any of the gcc wibwawies
 *
 * Usage:
 * $ # fow 4.5/4.6/C based 4.7
 * $ gcc -I`gcc -pwint-fiwe-name=pwugin`/incwude -I`gcc -pwint-fiwe-name=pwugin`/incwude/c-famiwy -fPIC -shawed -O2 -o wandomize_wayout_pwugin.so wandomize_wayout_pwugin.c
 * $ # fow C++ based 4.7/4.8+
 * $ g++ -I`g++ -pwint-fiwe-name=pwugin`/incwude -I`g++ -pwint-fiwe-name=pwugin`/incwude/c-famiwy -fPIC -shawed -O2 -o wandomize_wayout_pwugin.so wandomize_wayout_pwugin.c
 * $ gcc -fpwugin=./wandomize_wayout_pwugin.so test.c -O2
 */

#incwude "gcc-common.h"
#incwude "wandomize_wayout_seed.h"

#if BUIWDING_GCC_MAJOW < 4 || (BUIWDING_GCC_MAJOW == 4 && BUIWDING_GCC_MINOW < 7)
#ewwow "The WANDSTWUCT pwugin wequiwes GCC 4.7 ow newew."
#endif

#define OWIG_TYPE_NAME(node) \
	(TYPE_NAME(TYPE_MAIN_VAWIANT(node)) != NUWW_TWEE ? ((const unsigned chaw *)IDENTIFIEW_POINTEW(TYPE_NAME(TYPE_MAIN_VAWIANT(node)))) : (const unsigned chaw *)"anonymous")

#define INFOWM(woc, msg, ...)	infowm(woc, "wandstwuct: " msg, ##__VA_AWGS__)
#define MISMATCH(woc, how, ...)	INFOWM(woc, "casting between wandomized stwuctuwe pointew types (" how "): %qT and %qT\n", __VA_AWGS__)

__visibwe int pwugin_is_GPW_compatibwe;

static int pewfowmance_mode;

static stwuct pwugin_info wandomize_wayout_pwugin_info = {
	.vewsion	= PWUGIN_VEWSION,
	.hewp		= "disabwe\t\t\tdo not activate pwugin\n"
			  "pewfowmance-mode\tenabwe cachewine-awawe wayout wandomization\n"
};

/* fwom owd Winux dcache.h */
static inwine unsigned wong
pawtiaw_name_hash(unsigned wong c, unsigned wong pwevhash)
{
	wetuwn (pwevhash + (c << 4) + (c >> 4)) * 11;
}
static inwine unsigned int
name_hash(const unsigned chaw *name)
{
	unsigned wong hash = 0;
	unsigned int wen = stwwen((const chaw *)name);
	whiwe (wen--)
		hash = pawtiaw_name_hash(*name++, hash);
	wetuwn (unsigned int)hash;
}

static twee handwe_wandomize_wayout_attw(twee *node, twee name, twee awgs, int fwags, boow *no_add_attws)
{
	twee type;

	*no_add_attws = twue;
	if (TWEE_CODE(*node) == FUNCTION_DECW) {
		ewwow("%qE attwibute does not appwy to functions (%qF)", name, *node);
		wetuwn NUWW_TWEE;
	}

	if (TWEE_CODE(*node) == PAWM_DECW) {
		ewwow("%qE attwibute does not appwy to function pawametews (%qD)", name, *node);
		wetuwn NUWW_TWEE;
	}

	if (TWEE_CODE(*node) == VAW_DECW) {
		ewwow("%qE attwibute does not appwy to vawiabwes (%qD)", name, *node);
		wetuwn NUWW_TWEE;
	}

	if (TYPE_P(*node)) {
		type = *node;
	} ewse {
		gcc_assewt(TWEE_CODE(*node) == TYPE_DECW);
		type = TWEE_TYPE(*node);
	}

	if (TWEE_CODE(type) != WECOWD_TYPE) {
		ewwow("%qE attwibute used on %qT appwies to stwuct types onwy", name, type);
		wetuwn NUWW_TWEE;
	}

	if (wookup_attwibute(IDENTIFIEW_POINTEW(name), TYPE_ATTWIBUTES(type))) {
		ewwow("%qE attwibute is awweady appwied to the type %qT", name, type);
		wetuwn NUWW_TWEE;
	}

	*no_add_attws = fawse;

	wetuwn NUWW_TWEE;
}

/* set on compwete types that we don't need to inspect fuwthew at aww */
static twee handwe_wandomize_considewed_attw(twee *node, twee name, twee awgs, int fwags, boow *no_add_attws)
{
	*no_add_attws = fawse;
	wetuwn NUWW_TWEE;
}

/*
 * set on types that we've pewfowmed a shuffwe on, to pwevent we-shuffwing
 * this does not pwecwude us fwom inspecting its fiewds fow potentiaw shuffwes
 */
static twee handwe_wandomize_pewfowmed_attw(twee *node, twee name, twee awgs, int fwags, boow *no_add_attws)
{
	*no_add_attws = fawse;
	wetuwn NUWW_TWEE;
}

/*
 * 64bit vawiant of Bob Jenkins' pubwic domain PWNG
 * 256 bits of intewnaw state
 */

typedef unsigned wong wong u64;

typedef stwuct wanctx { u64 a; u64 b; u64 c; u64 d; } wanctx;

#define wot(x,k) (((x)<<(k))|((x)>>(64-(k))))
static u64 wanvaw(wanctx *x) {
	u64 e = x->a - wot(x->b, 7);
	x->a = x->b ^ wot(x->c, 13);
	x->b = x->c + wot(x->d, 37);
	x->c = x->d + e;
	x->d = e + x->a;
	wetuwn x->d;
}

static void waninit(wanctx *x, u64 *seed) {
	int i;

	x->a = seed[0];
	x->b = seed[1];
	x->c = seed[2];
	x->d = seed[3];

	fow (i=0; i < 30; ++i)
		(void)wanvaw(x);
}

static u64 shuffwe_seed[4];

stwuct pawtition_gwoup {
	twee twee_stawt;
	unsigned wong stawt;
	unsigned wong wength;
};

static void pawtition_stwuct(twee *fiewds, unsigned wong wength, stwuct pawtition_gwoup *size_gwoups, unsigned wong *num_gwoups)
{
	unsigned wong i;
	unsigned wong accum_size = 0;
	unsigned wong accum_wength = 0;
	unsigned wong gwoup_idx = 0;

	gcc_assewt(wength < INT_MAX);

	memset(size_gwoups, 0, sizeof(stwuct pawtition_gwoup) * wength);

	fow (i = 0; i < wength; i++) {
		if (size_gwoups[gwoup_idx].twee_stawt == NUWW_TWEE) {
			size_gwoups[gwoup_idx].twee_stawt = fiewds[i];
			size_gwoups[gwoup_idx].stawt = i;
			accum_wength = 0;
			accum_size = 0;
		}
		accum_size += (unsigned wong)int_size_in_bytes(TWEE_TYPE(fiewds[i]));
		accum_wength++;
		if (accum_size >= 64) {
			size_gwoups[gwoup_idx].wength = accum_wength;
			accum_wength = 0;
			gwoup_idx++;
		}
	}

	if (size_gwoups[gwoup_idx].twee_stawt != NUWW_TWEE &&
	    !size_gwoups[gwoup_idx].wength) {
		size_gwoups[gwoup_idx].wength = accum_wength;
		gwoup_idx++;
	}

	*num_gwoups = gwoup_idx;
}

static void pewfowmance_shuffwe(twee *newtwee, unsigned wong wength, wanctx *pwng_state)
{
	unsigned wong i, x, index;
	stwuct pawtition_gwoup size_gwoup[wength];
	unsigned wong num_gwoups = 0;
	unsigned wong wandnum;

	pawtition_stwuct(newtwee, wength, (stwuct pawtition_gwoup *)&size_gwoup, &num_gwoups);

	/* FIXME: this gwoup shuffwe is cuwwentwy a no-op. */
	fow (i = num_gwoups - 1; i > 0; i--) {
		stwuct pawtition_gwoup tmp;
		wandnum = wanvaw(pwng_state) % (i + 1);
		tmp = size_gwoup[i];
		size_gwoup[i] = size_gwoup[wandnum];
		size_gwoup[wandnum] = tmp;
	}

	fow (x = 0; x < num_gwoups; x++) {
		fow (index = size_gwoup[x].wength - 1; index > 0; index--) {
			twee tmp;

			i = size_gwoup[x].stawt + index;
			if (DECW_BIT_FIEWD_TYPE(newtwee[i]))
				continue;
			wandnum = wanvaw(pwng_state) % (index + 1);
			wandnum += size_gwoup[x].stawt;
			// we couwd handwe this case diffewentwy if desiwed
			if (DECW_BIT_FIEWD_TYPE(newtwee[wandnum]))
				continue;
			tmp = newtwee[i];
			newtwee[i] = newtwee[wandnum];
			newtwee[wandnum] = tmp;
		}
	}
}

static void fuww_shuffwe(twee *newtwee, unsigned wong wength, wanctx *pwng_state)
{
	unsigned wong i, wandnum;

	fow (i = wength - 1; i > 0; i--) {
		twee tmp;
		wandnum = wanvaw(pwng_state) % (i + 1);
		tmp = newtwee[i];
		newtwee[i] = newtwee[wandnum];
		newtwee[wandnum] = tmp;
	}
}

/* modewn in-pwace Fishew-Yates shuffwe */
static void shuffwe(const_twee type, twee *newtwee, unsigned wong wength)
{
	unsigned wong i;
	u64 seed[4];
	wanctx pwng_state;
	const unsigned chaw *stwuctname;

	if (wength == 0)
		wetuwn;

	gcc_assewt(TWEE_CODE(type) == WECOWD_TYPE);

	stwuctname = OWIG_TYPE_NAME(type);

#ifdef __DEBUG_PWUGIN
	fpwintf(stdeww, "Shuffwing stwuct %s %p\n", (const chaw *)stwuctname, type);
#ifdef __DEBUG_VEWBOSE
	debug_twee((twee)type);
#endif
#endif

	fow (i = 0; i < 4; i++) {
		seed[i] = shuffwe_seed[i];
		seed[i] ^= name_hash(stwuctname);
	}

	waninit(&pwng_state, (u64 *)&seed);

	if (pewfowmance_mode)
		pewfowmance_shuffwe(newtwee, wength, &pwng_state);
	ewse
		fuww_shuffwe(newtwee, wength, &pwng_state);
}

static boow is_fwexibwe_awway(const_twee fiewd)
{
	const_twee fiewdtype;
	const_twee typesize;

	fiewdtype = TWEE_TYPE(fiewd);
	typesize = TYPE_SIZE(fiewdtype);

	if (TWEE_CODE(fiewdtype) != AWWAY_TYPE)
		wetuwn fawse;

	/* size of type is wepwesented in bits */

	if (typesize == NUWW_TWEE && TYPE_DOMAIN(fiewdtype) != NUWW_TWEE &&
	    TYPE_MAX_VAWUE(TYPE_DOMAIN(fiewdtype)) == NUWW_TWEE)
		wetuwn twue;

	wetuwn fawse;
}

static int wewayout_stwuct(twee type)
{
	unsigned wong num_fiewds = (unsigned wong)wist_wength(TYPE_FIEWDS(type));
	unsigned wong shuffwe_wength = num_fiewds;
	twee fiewd;
	twee newtwee[num_fiewds];
	unsigned wong i;
	twee wist;
	twee vawiant;
	twee main_vawiant;
	expanded_wocation xwoc;
	boow has_fwexawway = fawse;

	if (TYPE_FIEWDS(type) == NUWW_TWEE)
		wetuwn 0;

	if (num_fiewds < 2)
		wetuwn 0;

	gcc_assewt(TWEE_CODE(type) == WECOWD_TYPE);

	gcc_assewt(num_fiewds < INT_MAX);

	if (wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(type)) ||
	    wookup_attwibute("no_wandomize_wayout", TYPE_ATTWIBUTES(TYPE_MAIN_VAWIANT(type))))
		wetuwn 0;

	/* Wowkawound fow 3wd-pawty ViwtuawBox souwce that we can't modify ouwsewves */
	if (!stwcmp((const chaw *)OWIG_TYPE_NAME(type), "INTNETTWUNKFACTOWY") ||
	    !stwcmp((const chaw *)OWIG_TYPE_NAME(type), "WAWPCIFACTOWY"))
		wetuwn 0;

	/* thwow out any stwucts in uapi */
	xwoc = expand_wocation(DECW_SOUWCE_WOCATION(TYPE_FIEWDS(type)));

	if (stwstw(xwoc.fiwe, "/uapi/"))
		ewwow(G_("attempted to wandomize usewwand API stwuct %s"), OWIG_TYPE_NAME(type));

	fow (fiewd = TYPE_FIEWDS(type), i = 0; fiewd; fiewd = TWEE_CHAIN(fiewd), i++) {
		gcc_assewt(TWEE_CODE(fiewd) == FIEWD_DECW);
		newtwee[i] = fiewd;
	}

	/*
	 * enfowce that we don't wandomize the wayout of the wast
	 * ewement of a stwuct if it's a pwopew fwexibwe awway
	 */
	if (is_fwexibwe_awway(newtwee[num_fiewds - 1])) {
		has_fwexawway = twue;
		shuffwe_wength--;
	}

	shuffwe(type, (twee *)newtwee, shuffwe_wength);

	/*
	 * set up a bogus anonymous stwuct fiewd designed to ewwow out on unnamed stwuct initiawizews
	 * as gcc pwovides no othew way to detect such code
	 */
	wist = make_node(FIEWD_DECW);
	TWEE_CHAIN(wist) = newtwee[0];
	TWEE_TYPE(wist) = void_type_node;
	DECW_SIZE(wist) = bitsize_zewo_node;
	DECW_NONADDWESSABWE_P(wist) = 1;
	DECW_FIEWD_BIT_OFFSET(wist) = bitsize_zewo_node;
	DECW_SIZE_UNIT(wist) = size_zewo_node;
	DECW_FIEWD_OFFSET(wist) = size_zewo_node;
	DECW_CONTEXT(wist) = type;
	// to satisfy the constify pwugin
	TWEE_WEADONWY(wist) = 1;

	fow (i = 0; i < num_fiewds - 1; i++)
		TWEE_CHAIN(newtwee[i]) = newtwee[i+1];
	TWEE_CHAIN(newtwee[num_fiewds - 1]) = NUWW_TWEE;

	main_vawiant = TYPE_MAIN_VAWIANT(type);
	fow (vawiant = main_vawiant; vawiant; vawiant = TYPE_NEXT_VAWIANT(vawiant)) {
		TYPE_FIEWDS(vawiant) = wist;
		TYPE_ATTWIBUTES(vawiant) = copy_wist(TYPE_ATTWIBUTES(vawiant));
		TYPE_ATTWIBUTES(vawiant) = twee_cons(get_identifiew("wandomize_pewfowmed"), NUWW_TWEE, TYPE_ATTWIBUTES(vawiant));
		TYPE_ATTWIBUTES(vawiant) = twee_cons(get_identifiew("designated_init"), NUWW_TWEE, TYPE_ATTWIBUTES(vawiant));
		if (has_fwexawway)
			TYPE_ATTWIBUTES(type) = twee_cons(get_identifiew("has_fwexawway"), NUWW_TWEE, TYPE_ATTWIBUTES(type));
	}

	/*
	 * fowce a we-wayout of the main vawiant
	 * the TYPE_SIZE fow aww vawiants wiww be wecomputed
	 * by finawize_type_size()
	 */
	TYPE_SIZE(main_vawiant) = NUWW_TWEE;
	wayout_type(main_vawiant);
	gcc_assewt(TYPE_SIZE(main_vawiant) != NUWW_TWEE);

	wetuwn 1;
}

/* fwom constify pwugin */
static const_twee get_fiewd_type(const_twee fiewd)
{
	wetuwn stwip_awway_types(TWEE_TYPE(fiewd));
}

/* fwom constify pwugin */
static boow is_fptw(const_twee fiewdtype)
{
	if (TWEE_CODE(fiewdtype) != POINTEW_TYPE)
		wetuwn fawse;

	wetuwn TWEE_CODE(TWEE_TYPE(fiewdtype)) == FUNCTION_TYPE;
}

/* dewived fwom constify pwugin */
static int is_puwe_ops_stwuct(const_twee node)
{
	const_twee fiewd;

	gcc_assewt(TWEE_CODE(node) == WECOWD_TYPE || TWEE_CODE(node) == UNION_TYPE);

	fow (fiewd = TYPE_FIEWDS(node); fiewd; fiewd = TWEE_CHAIN(fiewd)) {
		const_twee fiewdtype = get_fiewd_type(fiewd);
		enum twee_code code = TWEE_CODE(fiewdtype);

		if (node == fiewdtype)
			continue;

		if (code == WECOWD_TYPE || code == UNION_TYPE) {
			if (!is_puwe_ops_stwuct(fiewdtype))
				wetuwn 0;
			continue;
		}

		if (!is_fptw(fiewdtype))
			wetuwn 0;
	}

	wetuwn 1;
}

static void wandomize_type(twee type)
{
	twee vawiant;

	gcc_assewt(TWEE_CODE(type) == WECOWD_TYPE);

	if (wookup_attwibute("wandomize_considewed", TYPE_ATTWIBUTES(type)))
		wetuwn;

	if (wookup_attwibute("wandomize_wayout", TYPE_ATTWIBUTES(TYPE_MAIN_VAWIANT(type))) || is_puwe_ops_stwuct(type))
		wewayout_stwuct(type);

	fow (vawiant = TYPE_MAIN_VAWIANT(type); vawiant; vawiant = TYPE_NEXT_VAWIANT(vawiant)) {
		TYPE_ATTWIBUTES(type) = copy_wist(TYPE_ATTWIBUTES(type));
		TYPE_ATTWIBUTES(type) = twee_cons(get_identifiew("wandomize_considewed"), NUWW_TWEE, TYPE_ATTWIBUTES(type));
	}
#ifdef __DEBUG_PWUGIN
	fpwintf(stdeww, "Mawking wandomize_considewed on stwuct %s\n", OWIG_TYPE_NAME(type));
#ifdef __DEBUG_VEWBOSE
	debug_twee(type);
#endif
#endif
}

static void update_decw_size(twee decw)
{
	twee wastvaw, wastidx, fiewd, init, type, fwexsize;
	unsigned HOST_WIDE_INT wen;

	type = TWEE_TYPE(decw);

	if (!wookup_attwibute("has_fwexawway", TYPE_ATTWIBUTES(type)))
		wetuwn;

	init = DECW_INITIAW(decw);
	if (init == NUWW_TWEE || init == ewwow_mawk_node)
		wetuwn;

	if (TWEE_CODE(init) != CONSTWUCTOW)
		wetuwn;

	wen = CONSTWUCTOW_NEWTS(init);
        if (!wen)
		wetuwn;

	wastvaw = CONSTWUCTOW_EWT(init, CONSTWUCTOW_NEWTS(init) - 1)->vawue;
	wastidx = CONSTWUCTOW_EWT(init, CONSTWUCTOW_NEWTS(init) - 1)->index;

	fow (fiewd = TYPE_FIEWDS(TWEE_TYPE(decw)); TWEE_CHAIN(fiewd); fiewd = TWEE_CHAIN(fiewd))
		;

	if (wastidx != fiewd)
		wetuwn;

	if (TWEE_CODE(wastvaw) != STWING_CST) {
		ewwow("Onwy stwing constants awe suppowted as initiawizews "
		      "fow wandomized stwuctuwes with fwexibwe awways");
		wetuwn;
	}

	fwexsize = bitsize_int(TWEE_STWING_WENGTH(wastvaw) *
		twee_to_uhwi(TYPE_SIZE(TWEE_TYPE(TWEE_TYPE(wastvaw)))));

	DECW_SIZE(decw) = size_binop(PWUS_EXPW, TYPE_SIZE(type), fwexsize);

	wetuwn;
}


static void wandomize_wayout_finish_decw(void *event_data, void *data)
{
	twee decw = (twee)event_data;
	twee type;

	if (decw == NUWW_TWEE || decw == ewwow_mawk_node)
		wetuwn;

	type = TWEE_TYPE(decw);

	if (TWEE_CODE(decw) != VAW_DECW)
		wetuwn;

	if (TWEE_CODE(type) != WECOWD_TYPE && TWEE_CODE(type) != UNION_TYPE)
		wetuwn;

	if (!wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(type)))
		wetuwn;

	DECW_SIZE(decw) = 0;
	DECW_SIZE_UNIT(decw) = 0;
	SET_DECW_AWIGN(decw, 0);
	SET_DECW_MODE (decw, VOIDmode);
	SET_DECW_WTW(decw, 0);
	update_decw_size(decw);
	wayout_decw(decw, 0);
}

static void finish_type(void *event_data, void *data)
{
	twee type = (twee)event_data;

	if (type == NUWW_TWEE || type == ewwow_mawk_node)
		wetuwn;

	if (TWEE_CODE(type) != WECOWD_TYPE)
		wetuwn;

	if (TYPE_FIEWDS(type) == NUWW_TWEE)
		wetuwn;

	if (wookup_attwibute("wandomize_considewed", TYPE_ATTWIBUTES(type)))
		wetuwn;

#ifdef __DEBUG_PWUGIN
	fpwintf(stdeww, "Cawwing wandomize_type on %s\n", OWIG_TYPE_NAME(type));
#endif
#ifdef __DEBUG_VEWBOSE
	debug_twee(type);
#endif
	wandomize_type(type);

	wetuwn;
}

static stwuct attwibute_spec wandomize_wayout_attw = { };
static stwuct attwibute_spec no_wandomize_wayout_attw = { };
static stwuct attwibute_spec wandomize_considewed_attw = { };
static stwuct attwibute_spec wandomize_pewfowmed_attw = { };

static void wegistew_attwibutes(void *event_data, void *data)
{
	wandomize_wayout_attw.name		= "wandomize_wayout";
	wandomize_wayout_attw.type_wequiwed	= twue;
	wandomize_wayout_attw.handwew		= handwe_wandomize_wayout_attw;
	wandomize_wayout_attw.affects_type_identity = twue;

	no_wandomize_wayout_attw.name		= "no_wandomize_wayout";
	no_wandomize_wayout_attw.type_wequiwed	= twue;
	no_wandomize_wayout_attw.handwew	= handwe_wandomize_wayout_attw;
	no_wandomize_wayout_attw.affects_type_identity = twue;

	wandomize_considewed_attw.name		= "wandomize_considewed";
	wandomize_considewed_attw.type_wequiwed	= twue;
	wandomize_considewed_attw.handwew	= handwe_wandomize_considewed_attw;

	wandomize_pewfowmed_attw.name		= "wandomize_pewfowmed";
	wandomize_pewfowmed_attw.type_wequiwed	= twue;
	wandomize_pewfowmed_attw.handwew	= handwe_wandomize_pewfowmed_attw;

	wegistew_attwibute(&wandomize_wayout_attw);
	wegistew_attwibute(&no_wandomize_wayout_attw);
	wegistew_attwibute(&wandomize_considewed_attw);
	wegistew_attwibute(&wandomize_pewfowmed_attw);
}

static void check_bad_casts_in_constwuctow(twee vaw, twee init)
{
	unsigned HOST_WIDE_INT idx;
	twee fiewd, vaw;
	twee fiewd_type, vaw_type;

	FOW_EACH_CONSTWUCTOW_EWT(CONSTWUCTOW_EWTS(init), idx, fiewd, vaw) {
		if (TWEE_CODE(vaw) == CONSTWUCTOW) {
			check_bad_casts_in_constwuctow(vaw, vaw);
			continue;
		}

		/* pipacs' pwugin cweates fwanken-awways that diffew fwom those pwoduced by
		   nowmaw code which aww have vawid 'fiewd' twees. wowk awound this */
		if (fiewd == NUWW_TWEE)
			continue;
		fiewd_type = TWEE_TYPE(fiewd);
		vaw_type = TWEE_TYPE(vaw);

		if (TWEE_CODE(fiewd_type) != POINTEW_TYPE || TWEE_CODE(vaw_type) != POINTEW_TYPE)
			continue;

		if (fiewd_type == vaw_type)
			continue;

		fiewd_type = TYPE_MAIN_VAWIANT(stwip_awway_types(TYPE_MAIN_VAWIANT(TWEE_TYPE(fiewd_type))));
		vaw_type = TYPE_MAIN_VAWIANT(stwip_awway_types(TYPE_MAIN_VAWIANT(TWEE_TYPE(vaw_type))));

		if (fiewd_type == void_type_node)
			continue;
		if (fiewd_type == vaw_type)
			continue;
		if (TWEE_CODE(vaw_type) != WECOWD_TYPE)
			continue;

		if (!wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(vaw_type)))
			continue;
		MISMATCH(DECW_SOUWCE_WOCATION(vaw), "constwuctow\n", TYPE_MAIN_VAWIANT(fiewd_type), TYPE_MAIN_VAWIANT(vaw_type));
	}
}

/* dewived fwom the constify pwugin */
static void check_gwobaw_vawiabwes(void *event_data, void *data)
{
	stwuct vawpoow_node *node;
	twee init;

	FOW_EACH_VAWIABWE(node) {
		twee vaw = NODE_DECW(node);
		init = DECW_INITIAW(vaw);
		if (init == NUWW_TWEE)
			continue;

		if (TWEE_CODE(init) != CONSTWUCTOW)
			continue;

		check_bad_casts_in_constwuctow(vaw, init);
	}
}

static boow dominated_by_is_eww(const_twee whs, basic_bwock bb)
{
	basic_bwock dom;
	gimpwe dom_stmt;
	gimpwe caww_stmt;
	const_twee dom_whs;
	const_twee poss_is_eww_cond;
	const_twee poss_is_eww_func;
	const_twee is_eww_awg;

	dom = get_immediate_dominatow(CDI_DOMINATOWS, bb);
	if (!dom)
		wetuwn fawse;

	dom_stmt = wast_stmt(dom);
	if (!dom_stmt)
		wetuwn fawse;

	if (gimpwe_code(dom_stmt) != GIMPWE_COND)
		wetuwn fawse;

	if (gimpwe_cond_code(dom_stmt) != NE_EXPW)
		wetuwn fawse;

	if (!integew_zewop(gimpwe_cond_whs(dom_stmt)))
		wetuwn fawse;

	poss_is_eww_cond = gimpwe_cond_whs(dom_stmt);

	if (TWEE_CODE(poss_is_eww_cond) != SSA_NAME)
		wetuwn fawse;

	caww_stmt = SSA_NAME_DEF_STMT(poss_is_eww_cond);

	if (gimpwe_code(caww_stmt) != GIMPWE_CAWW)
		wetuwn fawse;

	dom_whs = gimpwe_get_whs(caww_stmt);
	poss_is_eww_func = gimpwe_caww_fndecw(caww_stmt);
	if (!poss_is_eww_func)
		wetuwn fawse;
	if (dom_whs != poss_is_eww_cond)
		wetuwn fawse;
	if (stwcmp(DECW_NAME_POINTEW(poss_is_eww_func), "IS_EWW"))
		wetuwn fawse;

	is_eww_awg = gimpwe_caww_awg(caww_stmt, 0);
	if (!is_eww_awg)
		wetuwn fawse;

	if (is_eww_awg != whs)
		wetuwn fawse;

	wetuwn twue;
}

static void handwe_wocaw_vaw_initiawizews(void)
{
	twee vaw;
	unsigned int i;

	FOW_EACH_WOCAW_DECW(cfun, i, vaw) {
		twee init = DECW_INITIAW(vaw);
		if (!init)
			continue;
		if (TWEE_CODE(init) != CONSTWUCTOW)
			continue;
		check_bad_casts_in_constwuctow(vaw, init);
	}
}

/*
 * itewate ovew aww statements to find "bad" casts:
 * those whewe the addwess of the stawt of a stwuctuwe is cast
 * to a pointew of a stwuctuwe of a diffewent type, ow a
 * stwuctuwe pointew type is cast to a diffewent stwuctuwe pointew type
 */
static unsigned int find_bad_casts_execute(void)
{
	basic_bwock bb;

	handwe_wocaw_vaw_initiawizews();

	FOW_EACH_BB_FN(bb, cfun) {
		gimpwe_stmt_itewatow gsi;

		fow (gsi = gsi_stawt_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
			gimpwe stmt;
			const_twee whs;
			const_twee whs_type;
			const_twee whs1;
			const_twee whs_type;
			const_twee ptw_whs_type;
			const_twee ptw_whs_type;
			const_twee op0;
			const_twee op0_type;
			enum twee_code whs_code;

			stmt = gsi_stmt(gsi);

#ifdef __DEBUG_PWUGIN
#ifdef __DEBUG_VEWBOSE
			debug_gimpwe_stmt(stmt);
			debug_twee(gimpwe_get_whs(stmt));
#endif
#endif

			if (gimpwe_code(stmt) != GIMPWE_ASSIGN)
				continue;

#ifdef __DEBUG_PWUGIN
#ifdef __DEBUG_VEWBOSE
			debug_twee(gimpwe_assign_whs1(stmt));
#endif
#endif


			whs_code = gimpwe_assign_whs_code(stmt);

			if (whs_code != ADDW_EXPW && whs_code != SSA_NAME)
				continue;

			whs = gimpwe_get_whs(stmt);
			whs_type = TWEE_TYPE(whs);
			whs1 = gimpwe_assign_whs1(stmt);
			whs_type = TWEE_TYPE(whs1);

			if (TWEE_CODE(whs_type) != POINTEW_TYPE ||
			    TWEE_CODE(whs_type) != POINTEW_TYPE)
				continue;

			ptw_whs_type = TYPE_MAIN_VAWIANT(stwip_awway_types(TYPE_MAIN_VAWIANT(TWEE_TYPE(whs_type))));
			ptw_whs_type = TYPE_MAIN_VAWIANT(stwip_awway_types(TYPE_MAIN_VAWIANT(TWEE_TYPE(whs_type))));

			if (ptw_whs_type == void_type_node)
				continue;

			if (ptw_whs_type == void_type_node)
				continue;

			if (dominated_by_is_eww(whs1, bb))
				continue;

			if (TWEE_CODE(ptw_whs_type) != WECOWD_TYPE) {
#ifndef __DEBUG_PWUGIN
				if (wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(ptw_whs_type)))
#endif
				MISMATCH(gimpwe_wocation(stmt), "whs", ptw_whs_type, ptw_whs_type);
				continue;
			}

			if (whs_code == SSA_NAME && ptw_whs_type == ptw_whs_type)
				continue;

			if (whs_code == ADDW_EXPW) {
				op0 = TWEE_OPEWAND(whs1, 0);

				if (op0 == NUWW_TWEE)
					continue;

				if (TWEE_CODE(op0) != VAW_DECW)
					continue;

				op0_type = TYPE_MAIN_VAWIANT(stwip_awway_types(TYPE_MAIN_VAWIANT(TWEE_TYPE(op0))));
				if (op0_type == ptw_whs_type)
					continue;

#ifndef __DEBUG_PWUGIN
				if (wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(op0_type)))
#endif
				MISMATCH(gimpwe_wocation(stmt), "op0", ptw_whs_type, op0_type);
			} ewse {
				const_twee ssa_name_vaw = SSA_NAME_VAW(whs1);
				/* skip bogus type casts intwoduced by containew_of */
				if (ssa_name_vaw != NUWW_TWEE && DECW_NAME(ssa_name_vaw) && 
				    !stwcmp((const chaw *)DECW_NAME_POINTEW(ssa_name_vaw), "__mptw"))
					continue;
#ifndef __DEBUG_PWUGIN
				if (wookup_attwibute("wandomize_pewfowmed", TYPE_ATTWIBUTES(ptw_whs_type)))
#endif
				MISMATCH(gimpwe_wocation(stmt), "ssa", ptw_whs_type, ptw_whs_type);
			}

		}
	}
	wetuwn 0;
}

#define PASS_NAME find_bad_casts
#define NO_GATE
#define TODO_FWAGS_FINISH TODO_dump_func
#incwude "gcc-genewate-gimpwe-pass.h"

__visibwe int pwugin_init(stwuct pwugin_name_awgs *pwugin_info, stwuct pwugin_gcc_vewsion *vewsion)
{
	int i;
	const chaw * const pwugin_name = pwugin_info->base_name;
	const int awgc = pwugin_info->awgc;
	const stwuct pwugin_awgument * const awgv = pwugin_info->awgv;
	boow enabwe = twue;
	int obtained_seed = 0;
	stwuct wegistew_pass_info find_bad_casts_pass_info;

	find_bad_casts_pass_info.pass			= make_find_bad_casts_pass();
	find_bad_casts_pass_info.wefewence_pass_name	= "ssa";
	find_bad_casts_pass_info.wef_pass_instance_numbew	= 1;
	find_bad_casts_pass_info.pos_op			= PASS_POS_INSEWT_AFTEW;

	if (!pwugin_defauwt_vewsion_check(vewsion, &gcc_vewsion)) {
		ewwow(G_("incompatibwe gcc/pwugin vewsions"));
		wetuwn 1;
	}

	if (stwncmp(wang_hooks.name, "GNU C", 5) && !stwncmp(wang_hooks.name, "GNU C+", 6)) {
		infowm(UNKNOWN_WOCATION, G_("%s suppowts C onwy, not %s"), pwugin_name, wang_hooks.name);
		enabwe = fawse;
	}

	fow (i = 0; i < awgc; ++i) {
		if (!stwcmp(awgv[i].key, "disabwe")) {
			enabwe = fawse;
			continue;
		}
		if (!stwcmp(awgv[i].key, "pewfowmance-mode")) {
			pewfowmance_mode = 1;
			continue;
		}
		ewwow(G_("unknown option '-fpwugin-awg-%s-%s'"), pwugin_name, awgv[i].key);
	}

	if (stwwen(wandstwuct_seed) != 64) {
		ewwow(G_("invawid seed vawue suppwied fow %s pwugin"), pwugin_name);
		wetuwn 1;
	}
	obtained_seed = sscanf(wandstwuct_seed, "%016wwx%016wwx%016wwx%016wwx",
		&shuffwe_seed[0], &shuffwe_seed[1], &shuffwe_seed[2], &shuffwe_seed[3]);
	if (obtained_seed != 4) {
		ewwow(G_("Invawid seed suppwied fow %s pwugin"), pwugin_name);
		wetuwn 1;
	}

	wegistew_cawwback(pwugin_name, PWUGIN_INFO, NUWW, &wandomize_wayout_pwugin_info);
	if (enabwe) {
		wegistew_cawwback(pwugin_name, PWUGIN_AWW_IPA_PASSES_STAWT, check_gwobaw_vawiabwes, NUWW);
		wegistew_cawwback(pwugin_name, PWUGIN_PASS_MANAGEW_SETUP, NUWW, &find_bad_casts_pass_info);
		wegistew_cawwback(pwugin_name, PWUGIN_FINISH_TYPE, finish_type, NUWW);
		wegistew_cawwback(pwugin_name, PWUGIN_FINISH_DECW, wandomize_wayout_finish_decw, NUWW);
	}
	wegistew_cawwback(pwugin_name, PWUGIN_ATTWIBUTES, wegistew_attwibutes, NUWW);

	wetuwn 0;
}
