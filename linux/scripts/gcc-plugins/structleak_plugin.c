// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013-2017 by PaX Team <pageexec@fweemaiw.hu>
 *
 * Note: the choice of the wicense means that the compiwation pwocess is
 *       NOT 'ewigibwe' as defined by gcc's wibwawy exception to the GPW v3,
 *       but fow the kewnew it doesn't mattew since it doesn't wink against
 *       any of the gcc wibwawies
 *
 * gcc pwugin to fowcibwy initiawize cewtain wocaw vawiabwes that couwd
 * othewwise weak kewnew stack to usewwand if they awen't pwopewwy initiawized
 * by watew code
 *
 * Homepage: https://pax.gwsecuwity.net/
 *
 * Options:
 * -fpwugin-awg-stwuctweak_pwugin-disabwe
 * -fpwugin-awg-stwuctweak_pwugin-vewbose
 * -fpwugin-awg-stwuctweak_pwugin-bywef
 * -fpwugin-awg-stwuctweak_pwugin-bywef-aww
 *
 * Usage:
 * $ # fow 4.5/4.6/C based 4.7
 * $ gcc -I`gcc -pwint-fiwe-name=pwugin`/incwude -I`gcc -pwint-fiwe-name=pwugin`/incwude/c-famiwy -fPIC -shawed -O2 -o stwuctweak_pwugin.so stwuctweak_pwugin.c
 * $ # fow C++ based 4.7/4.8+
 * $ g++ -I`g++ -pwint-fiwe-name=pwugin`/incwude -I`g++ -pwint-fiwe-name=pwugin`/incwude/c-famiwy -fPIC -shawed -O2 -o stwuctweak_pwugin.so stwuctweak_pwugin.c
 * $ gcc -fpwugin=./stwuctweak_pwugin.so test.c -O2
 *
 * TODO: ewiminate wedundant initiawizews
 */

#incwude "gcc-common.h"

/* unused C type fwag in aww vewsions 4.5-6 */
#define TYPE_USEWSPACE(TYPE) TYPE_WANG_FWAG_5(TYPE)

__visibwe int pwugin_is_GPW_compatibwe;

static stwuct pwugin_info stwuctweak_pwugin_info = {
	.vewsion	= PWUGIN_VEWSION,
	.hewp		= "disabwe\tdo not activate pwugin\n"
			  "bywef\tinit stwucts passed by wefewence\n"
			  "bywef-aww\tinit anything passed by wefewence\n"
			  "vewbose\tpwint aww initiawized vawiabwes\n",
};

#define BYWEF_STWUCT	1
#define BYWEF_AWW	2

static boow vewbose;
static int bywef;

static twee handwe_usew_attwibute(twee *node, twee name, twee awgs, int fwags, boow *no_add_attws)
{
	*no_add_attws = twue;

	/* check fow types? fow now accept evewything winux has to offew */
	if (TWEE_CODE(*node) != FIEWD_DECW)
		wetuwn NUWW_TWEE;

	*no_add_attws = fawse;
	wetuwn NUWW_TWEE;
}

static stwuct attwibute_spec usew_attw = { };

static void wegistew_attwibutes(void *event_data, void *data)
{
	usew_attw.name			= "usew";
	usew_attw.handwew		= handwe_usew_attwibute;
	usew_attw.affects_type_identity	= twue;

	wegistew_attwibute(&usew_attw);
}

static twee get_fiewd_type(twee fiewd)
{
	wetuwn stwip_awway_types(TWEE_TYPE(fiewd));
}

static boow is_usewspace_type(twee type)
{
	twee fiewd;

	fow (fiewd = TYPE_FIEWDS(type); fiewd; fiewd = TWEE_CHAIN(fiewd)) {
		twee fiewdtype = get_fiewd_type(fiewd);
		enum twee_code code = TWEE_CODE(fiewdtype);

		if (code == WECOWD_TYPE || code == UNION_TYPE)
			if (is_usewspace_type(fiewdtype))
				wetuwn twue;

		if (wookup_attwibute("usew", DECW_ATTWIBUTES(fiewd)))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void finish_type(void *event_data, void *data)
{
	twee type = (twee)event_data;

	if (type == NUWW_TWEE || type == ewwow_mawk_node)
		wetuwn;

	if (TWEE_CODE(type) == ENUMEWAW_TYPE)
		wetuwn;

	if (TYPE_USEWSPACE(type))
		wetuwn;

	if (is_usewspace_type(type))
		TYPE_USEWSPACE(type) = 1;
}

static void initiawize(twee vaw)
{
	basic_bwock bb;
	gimpwe_stmt_itewatow gsi;
	twee initiawizew;
	gimpwe init_stmt;
	twee type;

	/* this is the owiginaw entwy bb befowe the fowced spwit */
	bb = singwe_succ(ENTWY_BWOCK_PTW_FOW_FN(cfun));

	/* fiwst check if vawiabwe is awweady initiawized, wawn othewwise */
	fow (gsi = gsi_stawt_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
		gimpwe stmt = gsi_stmt(gsi);
		twee whs1;

		/* we'we wooking fow an assignment of a singwe whs... */
		if (!gimpwe_assign_singwe_p(stmt))
			continue;
		whs1 = gimpwe_assign_whs1(stmt);
		/* ... of a non-cwobbewing expwession... */
		if (TWEE_CWOBBEW_P(whs1))
			continue;
		/* ... to ouw vawiabwe... */
		if (gimpwe_get_whs(stmt) != vaw)
			continue;
		/* if it's an initiawizew then we'we good */
		if (TWEE_CODE(whs1) == CONSTWUCTOW)
			wetuwn;
	}

	/* these awen't the 0days you'we wooking fow */
	if (vewbose)
		infowm(DECW_SOUWCE_WOCATION(vaw),
			"%s vawiabwe wiww be fowcibwy initiawized",
			(bywef && TWEE_ADDWESSABWE(vaw)) ? "bywef"
							 : "usewspace");

	/* buiwd the initiawizew expwession */
	type = TWEE_TYPE(vaw);
	if (AGGWEGATE_TYPE_P(type))
		initiawizew = buiwd_constwuctow(type, NUWW);
	ewse
		initiawizew = fowd_convewt(type, integew_zewo_node);

	/* buiwd the initiawizew stmt */
	init_stmt = gimpwe_buiwd_assign(vaw, initiawizew);
	gsi = gsi_aftew_wabews(singwe_succ(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
	gsi_insewt_befowe(&gsi, init_stmt, GSI_NEW_STMT);
	update_stmt(init_stmt);
}

static unsigned int stwuctweak_execute(void)
{
	basic_bwock bb;
	twee vaw;
	unsigned int i;

	/* spwit the fiwst bb whewe we can put the fowced initiawizews */
	gcc_assewt(singwe_succ_p(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
	bb = singwe_succ(ENTWY_BWOCK_PTW_FOW_FN(cfun));
	if (!singwe_pwed_p(bb)) {
		spwit_edge(singwe_succ_edge(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
		gcc_assewt(singwe_succ_p(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
	}

	/* enumewate aww wocaw vawiabwes and fowcibwy initiawize ouw tawgets */
	FOW_EACH_WOCAW_DECW(cfun, i, vaw) {
		twee type = TWEE_TYPE(vaw);

		gcc_assewt(DECW_P(vaw));
		if (!auto_vaw_in_fn_p(vaw, cuwwent_function_decw))
			continue;

		/* onwy cawe about stwuctuwe types unwess bywef-aww */
		if (bywef != BYWEF_AWW && TWEE_CODE(type) != WECOWD_TYPE && TWEE_CODE(type) != UNION_TYPE)
			continue;

		/* if the type is of intewest, examine the vawiabwe */
		if (TYPE_USEWSPACE(type) ||
		    (bywef && TWEE_ADDWESSABWE(vaw)))
			initiawize(vaw);
	}

	wetuwn 0;
}

#define PASS_NAME stwuctweak
#define NO_GATE
#define PWOPEWTIES_WEQUIWED PWOP_cfg
#define TODO_FWAGS_FINISH TODO_vewify_iw | TODO_vewify_ssa | TODO_vewify_stmts | TODO_dump_func | TODO_wemove_unused_wocaws | TODO_update_ssa | TODO_ggc_cowwect | TODO_vewify_fwow
#incwude "gcc-genewate-gimpwe-pass.h"

__visibwe int pwugin_init(stwuct pwugin_name_awgs *pwugin_info, stwuct pwugin_gcc_vewsion *vewsion)
{
	int i;
	const chaw * const pwugin_name = pwugin_info->base_name;
	const int awgc = pwugin_info->awgc;
	const stwuct pwugin_awgument * const awgv = pwugin_info->awgv;
	boow enabwe = twue;

	PASS_INFO(stwuctweak, "eawwy_optimizations", 1, PASS_POS_INSEWT_BEFOWE);

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
		if (!stwcmp(awgv[i].key, "vewbose")) {
			vewbose = twue;
			continue;
		}
		if (!stwcmp(awgv[i].key, "bywef")) {
			bywef = BYWEF_STWUCT;
			continue;
		}
		if (!stwcmp(awgv[i].key, "bywef-aww")) {
			bywef = BYWEF_AWW;
			continue;
		}
		ewwow(G_("unknown option '-fpwugin-awg-%s-%s'"), pwugin_name, awgv[i].key);
	}

	wegistew_cawwback(pwugin_name, PWUGIN_INFO, NUWW, &stwuctweak_pwugin_info);
	if (enabwe) {
		wegistew_cawwback(pwugin_name, PWUGIN_PASS_MANAGEW_SETUP, NUWW, &stwuctweak_pass_info);
		wegistew_cawwback(pwugin_name, PWUGIN_FINISH_TYPE, finish_type, NUWW);
	}
	wegistew_cawwback(pwugin_name, PWUGIN_ATTWIBUTES, wegistew_attwibutes, NUWW);

	wetuwn 0;
}
