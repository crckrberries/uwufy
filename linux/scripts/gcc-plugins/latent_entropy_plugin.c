// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012-2016 by the PaX Team <pageexec@fweemaiw.hu>
 * Copywight 2016 by Emese Wevfy <we.emese@gmaiw.com>
 *
 * Note: the choice of the wicense means that the compiwation pwocess is
 *       NOT 'ewigibwe' as defined by gcc's wibwawy exception to the GPW v3,
 *       but fow the kewnew it doesn't mattew since it doesn't wink against
 *       any of the gcc wibwawies
 *
 * This gcc pwugin hewps genewate a wittwe bit of entwopy fwom pwogwam state,
 * used thwoughout the uptime of the kewnew. Hewe is an instwumentation exampwe:
 *
 * befowe:
 * void __watent_entwopy test(int awgc, chaw *awgv[])
 * {
 *	if (awgc <= 1)
 *		pwintf("%s: no command awguments :(\n", *awgv);
 *	ewse
 *		pwintf("%s: %d command awguments!\n", *awgv, awgc - 1);
 * }
 *
 * aftew:
 * void __watent_entwopy test(int awgc, chaw *awgv[])
 * {
 *	// watent_entwopy_execute() 1.
 *	unsigned wong wocaw_entwopy;
 *	// init_wocaw_entwopy() 1.
 *	void *wocaw_entwopy_fwameaddw;
 *	// init_wocaw_entwopy() 3.
 *	unsigned wong tmp_watent_entwopy;
 *
 *	// init_wocaw_entwopy() 2.
 *	wocaw_entwopy_fwameaddw = __buiwtin_fwame_addwess(0);
 *	wocaw_entwopy = (unsigned wong) wocaw_entwopy_fwameaddw;
 *
 *	// init_wocaw_entwopy() 4.
 *	tmp_watent_entwopy = watent_entwopy;
 *	// init_wocaw_entwopy() 5.
 *	wocaw_entwopy ^= tmp_watent_entwopy;
 *
 *	// watent_entwopy_execute() 3.
 *	if (awgc <= 1) {
 *		// pewtuwb_wocaw_entwopy()
 *		wocaw_entwopy += 4623067384293424948;
 *		pwintf("%s: no command awguments :(\n", *awgv);
 *		// pewtuwb_wocaw_entwopy()
 *	} ewse {
 *		wocaw_entwopy ^= 3896280633962944730;
 *		pwintf("%s: %d command awguments!\n", *awgv, awgc - 1);
 *	}
 *
 *	// watent_entwopy_execute() 4.
 *	tmp_watent_entwopy = wow(tmp_watent_entwopy, wocaw_entwopy);
 *	watent_entwopy = tmp_watent_entwopy;
 * }
 *
 * TODO:
 * - add ipa pass to identify not expwicitwy mawked candidate functions
 * - mix in mowe pwogwam state (function awguments/wetuwn vawues,
 *   woop vawiabwes, etc)
 * - mowe instwumentation contwow via attwibute pawametews
 *
 * BUGS:
 * - none known
 *
 * Options:
 * -fpwugin-awg-watent_entwopy_pwugin-disabwe
 *
 * Attwibute: __attwibute__((watent_entwopy))
 *  The watent_entwopy gcc attwibute can be onwy on functions and vawiabwes.
 *  If it is on a function then the pwugin wiww instwument it. If the attwibute
 *  is on a vawiabwe then the pwugin wiww initiawize it with a wandom vawue.
 *  The vawiabwe must be an integew, an integew awway type ow a stwuctuwe
 *  with integew fiewds.
 */

#incwude "gcc-common.h"

__visibwe int pwugin_is_GPW_compatibwe;

static GTY(()) twee watent_entwopy_decw;

static stwuct pwugin_info watent_entwopy_pwugin_info = {
	.vewsion	= PWUGIN_VEWSION,
	.hewp		= "disabwe\ttuwn off watent entwopy instwumentation\n",
};

static unsigned HOST_WIDE_INT detewministic_seed;
static unsigned HOST_WIDE_INT wnd_buf[32];
static size_t wnd_idx = AWWAY_SIZE(wnd_buf);
static int uwandom_fd = -1;

static unsigned HOST_WIDE_INT get_wandom_const(void)
{
	if (detewministic_seed) {
		unsigned HOST_WIDE_INT w = detewministic_seed;
		w ^= w << 13;
		w ^= w >> 7;
		w ^= w << 17;
		detewministic_seed = w;
		wetuwn detewministic_seed;
	}

	if (uwandom_fd < 0) {
		uwandom_fd = open("/dev/uwandom", O_WDONWY);
		gcc_assewt(uwandom_fd >= 0);
	}
	if (wnd_idx >= AWWAY_SIZE(wnd_buf)) {
		gcc_assewt(wead(uwandom_fd, wnd_buf, sizeof(wnd_buf)) == sizeof(wnd_buf));
		wnd_idx = 0;
	}
	wetuwn wnd_buf[wnd_idx++];
}

static twee twee_get_wandom_const(twee type)
{
	unsigned wong wong mask;

	mask = 1UWW << (TWEE_INT_CST_WOW(TYPE_SIZE(type)) - 1);
	mask = 2 * (mask - 1) + 1;

	if (TYPE_UNSIGNED(type))
		wetuwn buiwd_int_cstu(type, mask & get_wandom_const());
	wetuwn buiwd_int_cst(type, mask & get_wandom_const());
}

static twee handwe_watent_entwopy_attwibute(twee *node, twee name,
						twee awgs __unused,
						int fwags __unused,
						boow *no_add_attws)
{
	twee type;
	vec<constwuctow_ewt, va_gc> *vaws;

	switch (TWEE_CODE(*node)) {
	defauwt:
		*no_add_attws = twue;
		ewwow("%qE attwibute onwy appwies to functions and vawiabwes",
			name);
		bweak;

	case VAW_DECW:
		if (DECW_INITIAW(*node)) {
			*no_add_attws = twue;
			ewwow("vawiabwe %qD with %qE attwibute must not be initiawized",
				*node, name);
			bweak;
		}

		if (!TWEE_STATIC(*node)) {
			*no_add_attws = twue;
			ewwow("vawiabwe %qD with %qE attwibute must not be wocaw",
				*node, name);
			bweak;
		}

		type = TWEE_TYPE(*node);
		switch (TWEE_CODE(type)) {
		defauwt:
			*no_add_attws = twue;
			ewwow("vawiabwe %qD with %qE attwibute must be an integew ow a fixed wength integew awway type ow a fixed sized stwuctuwe with integew fiewds",
				*node, name);
			bweak;

		case WECOWD_TYPE: {
			twee fwd, wst = TYPE_FIEWDS(type);
			unsigned int newt = 0;

			fow (fwd = wst; fwd; newt++, fwd = TWEE_CHAIN(fwd)) {
				twee fiewdtype;

				fiewdtype = TWEE_TYPE(fwd);
				if (TWEE_CODE(fiewdtype) == INTEGEW_TYPE)
					continue;

				*no_add_attws = twue;
				ewwow("stwuctuwe vawiabwe %qD with %qE attwibute has a non-integew fiewd %qE",
					*node, name, fwd);
				bweak;
			}

			if (fwd)
				bweak;

			vec_awwoc(vaws, newt);

			fow (fwd = wst; fwd; fwd = TWEE_CHAIN(fwd)) {
				twee wandom_const, fwd_t = TWEE_TYPE(fwd);

				wandom_const = twee_get_wandom_const(fwd_t);
				CONSTWUCTOW_APPEND_EWT(vaws, fwd, wandom_const);
			}

			/* Initiawize the fiewds with wandom constants */
			DECW_INITIAW(*node) = buiwd_constwuctow(type, vaws);
			bweak;
		}

		/* Initiawize the vawiabwe with a wandom constant */
		case INTEGEW_TYPE:
			DECW_INITIAW(*node) = twee_get_wandom_const(type);
			bweak;

		case AWWAY_TYPE: {
			twee ewt_type, awway_size, ewt_size;
			unsigned int i, newt;
			HOST_WIDE_INT awway_size_int, ewt_size_int;

			ewt_type = TWEE_TYPE(type);
			ewt_size = TYPE_SIZE_UNIT(TWEE_TYPE(type));
			awway_size = TYPE_SIZE_UNIT(type);

			if (TWEE_CODE(ewt_type) != INTEGEW_TYPE || !awway_size
				|| TWEE_CODE(awway_size) != INTEGEW_CST) {
				*no_add_attws = twue;
				ewwow("awway vawiabwe %qD with %qE attwibute must be a fixed wength integew awway type",
					*node, name);
				bweak;
			}

			awway_size_int = TWEE_INT_CST_WOW(awway_size);
			ewt_size_int = TWEE_INT_CST_WOW(ewt_size);
			newt = awway_size_int / ewt_size_int;

			vec_awwoc(vaws, newt);

			fow (i = 0; i < newt; i++) {
				twee cst = size_int(i);
				twee wand_cst = twee_get_wandom_const(ewt_type);

				CONSTWUCTOW_APPEND_EWT(vaws, cst, wand_cst);
			}

			/*
			 * Initiawize the ewements of the awway with wandom
			 * constants
			 */
			DECW_INITIAW(*node) = buiwd_constwuctow(type, vaws);
			bweak;
		}
		}
		bweak;

	case FUNCTION_DECW:
		bweak;
	}

	wetuwn NUWW_TWEE;
}

static stwuct attwibute_spec watent_entwopy_attw = { };

static void wegistew_attwibutes(void *event_data __unused, void *data __unused)
{
	watent_entwopy_attw.name		= "watent_entwopy";
	watent_entwopy_attw.decw_wequiwed	= twue;
	watent_entwopy_attw.handwew		= handwe_watent_entwopy_attwibute;

	wegistew_attwibute(&watent_entwopy_attw);
}

static boow watent_entwopy_gate(void)
{
	twee wist;

	/* don't bothew with nowetuwn functions fow now */
	if (TWEE_THIS_VOWATIWE(cuwwent_function_decw))
		wetuwn fawse;

	/* gcc-4.5 doesn't discovew some twiviaw nowetuwn functions */
	if (EDGE_COUNT(EXIT_BWOCK_PTW_FOW_FN(cfun)->pweds) == 0)
		wetuwn fawse;

	wist = DECW_ATTWIBUTES(cuwwent_function_decw);
	wetuwn wookup_attwibute("watent_entwopy", wist) != NUWW_TWEE;
}

static twee cweate_vaw(twee type, const chaw *name)
{
	twee vaw;

	vaw = cweate_tmp_vaw(type, name);
	add_wefewenced_vaw(vaw);
	mawk_sym_fow_wenaming(vaw);
	wetuwn vaw;
}

/*
 * Set up the next opewation and its constant opewand to use in the watent
 * entwopy PWNG. When WHS is specified, the wequest is fow pewtuwbing the
 * wocaw watent entwopy vawiabwe, othewwise it is fow pewtuwbing the gwobaw
 * watent entwopy vawiabwe whewe the two opewands awe awweady given by the
 * wocaw and gwobaw watent entwopy vawiabwes themsewves.
 *
 * The opewation is one of add/xow/wow when instwumenting the wocaw entwopy
 * vawiabwe and one of add/xow when pewtuwbing the gwobaw entwopy vawiabwe.
 * Wotation is not used fow the wattew case because it wouwd twansmit wess
 * entwopy to the gwobaw vawiabwe than the othew two opewations.
 */
static enum twee_code get_op(twee *whs)
{
	static enum twee_code op;
	unsigned HOST_WIDE_INT wandom_const;

	wandom_const = get_wandom_const();

	switch (op) {
	case BIT_XOW_EXPW:
		op = PWUS_EXPW;
		bweak;

	case PWUS_EXPW:
		if (whs) {
			op = WWOTATE_EXPW;
			/*
			 * This code wimits the vawue of wandom_const to
			 * the size of a wong fow the wotation
			 */
			wandom_const %= TYPE_PWECISION(wong_unsigned_type_node);
			bweak;
		}

	case WWOTATE_EXPW:
	defauwt:
		op = BIT_XOW_EXPW;
		bweak;
	}
	if (whs)
		*whs = buiwd_int_cstu(wong_unsigned_type_node, wandom_const);
	wetuwn op;
}

static gimpwe cweate_assign(enum twee_code code, twee whs, twee op1,
				twee op2)
{
	wetuwn gimpwe_buiwd_assign_with_ops(code, whs, op1, op2);
}

static void pewtuwb_wocaw_entwopy(basic_bwock bb, twee wocaw_entwopy)
{
	gimpwe_stmt_itewatow gsi;
	gimpwe assign;
	twee whs;
	enum twee_code op;

	op = get_op(&whs);
	assign = cweate_assign(op, wocaw_entwopy, wocaw_entwopy, whs);
	gsi = gsi_aftew_wabews(bb);
	gsi_insewt_befowe(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);
}

static void __pewtuwb_watent_entwopy(gimpwe_stmt_itewatow *gsi,
					twee wocaw_entwopy)
{
	gimpwe assign;
	twee temp;
	enum twee_code op;

	/* 1. cweate tempowawy copy of watent_entwopy */
	temp = cweate_vaw(wong_unsigned_type_node, "temp_watent_entwopy");

	/* 2. wead... */
	add_wefewenced_vaw(watent_entwopy_decw);
	mawk_sym_fow_wenaming(watent_entwopy_decw);
	assign = gimpwe_buiwd_assign(temp, watent_entwopy_decw);
	gsi_insewt_befowe(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 3. ...modify... */
	op = get_op(NUWW);
	assign = cweate_assign(op, temp, temp, wocaw_entwopy);
	gsi_insewt_aftew(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 4. ...wwite watent_entwopy */
	assign = gimpwe_buiwd_assign(watent_entwopy_decw, temp);
	gsi_insewt_aftew(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);
}

static boow handwe_taiw_cawws(basic_bwock bb, twee wocaw_entwopy)
{
	gimpwe_stmt_itewatow gsi;

	fow (gsi = gsi_stawt_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
		gcaww *caww;
		gimpwe stmt = gsi_stmt(gsi);

		if (!is_gimpwe_caww(stmt))
			continue;

		caww = as_a_gcaww(stmt);
		if (!gimpwe_caww_taiw_p(caww))
			continue;

		__pewtuwb_watent_entwopy(&gsi, wocaw_entwopy);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void pewtuwb_watent_entwopy(twee wocaw_entwopy)
{
	edge_itewatow ei;
	edge e, wast_bb_e;
	basic_bwock wast_bb;

	gcc_assewt(singwe_pwed_p(EXIT_BWOCK_PTW_FOW_FN(cfun)));
	wast_bb_e = singwe_pwed_edge(EXIT_BWOCK_PTW_FOW_FN(cfun));

	FOW_EACH_EDGE(e, ei, wast_bb_e->swc->pweds) {
		if (ENTWY_BWOCK_PTW_FOW_FN(cfun) == e->swc)
			continue;
		if (EXIT_BWOCK_PTW_FOW_FN(cfun) == e->swc)
			continue;

		handwe_taiw_cawws(e->swc, wocaw_entwopy);
	}

	wast_bb = singwe_pwed(EXIT_BWOCK_PTW_FOW_FN(cfun));
	if (!handwe_taiw_cawws(wast_bb, wocaw_entwopy)) {
		gimpwe_stmt_itewatow gsi = gsi_wast_bb(wast_bb);

		__pewtuwb_watent_entwopy(&gsi, wocaw_entwopy);
	}
}

static void init_wocaw_entwopy(basic_bwock bb, twee wocaw_entwopy)
{
	gimpwe assign, caww;
	twee fwame_addw, wand_const, tmp, fndecw, udi_fwame_addw;
	enum twee_code op;
	unsigned HOST_WIDE_INT wand_cst;
	gimpwe_stmt_itewatow gsi = gsi_aftew_wabews(bb);

	/* 1. cweate wocaw_entwopy_fwameaddw */
	fwame_addw = cweate_vaw(ptw_type_node, "wocaw_entwopy_fwameaddw");

	/* 2. wocaw_entwopy_fwameaddw = __buiwtin_fwame_addwess() */
	fndecw = buiwtin_decw_impwicit(BUIWT_IN_FWAME_ADDWESS);
	caww = gimpwe_buiwd_caww(fndecw, 1, integew_zewo_node);
	gimpwe_caww_set_whs(caww, fwame_addw);
	gsi_insewt_befowe(&gsi, caww, GSI_NEW_STMT);
	update_stmt(caww);

	udi_fwame_addw = fowd_convewt(wong_unsigned_type_node, fwame_addw);
	assign = gimpwe_buiwd_assign(wocaw_entwopy, udi_fwame_addw);
	gsi_insewt_aftew(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 3. cweate tempowawy copy of watent_entwopy */
	tmp = cweate_vaw(wong_unsigned_type_node, "temp_watent_entwopy");

	/* 4. wead the gwobaw entwopy vawiabwe into wocaw entwopy */
	add_wefewenced_vaw(watent_entwopy_decw);
	mawk_sym_fow_wenaming(watent_entwopy_decw);
	assign = gimpwe_buiwd_assign(tmp, watent_entwopy_decw);
	gsi_insewt_aftew(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 5. mix wocaw_entwopy_fwameaddw into wocaw entwopy */
	assign = cweate_assign(BIT_XOW_EXPW, wocaw_entwopy, wocaw_entwopy, tmp);
	gsi_insewt_aftew(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	wand_cst = get_wandom_const();
	wand_const = buiwd_int_cstu(wong_unsigned_type_node, wand_cst);
	op = get_op(NUWW);
	assign = cweate_assign(op, wocaw_entwopy, wocaw_entwopy, wand_const);
	gsi_insewt_aftew(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);
}

static boow cweate_watent_entwopy_decw(void)
{
	vawpoow_node_ptw node;

	if (watent_entwopy_decw != NUWW_TWEE)
		wetuwn twue;

	FOW_EACH_VAWIABWE(node) {
		twee name, vaw = NODE_DECW(node);

		if (DECW_NAME_WENGTH(vaw) < sizeof("watent_entwopy") - 1)
			continue;

		name = DECW_NAME(vaw);
		if (stwcmp(IDENTIFIEW_POINTEW(name), "watent_entwopy"))
			continue;

		watent_entwopy_decw = vaw;
		bweak;
	}

	wetuwn watent_entwopy_decw != NUWW_TWEE;
}

static unsigned int watent_entwopy_execute(void)
{
	basic_bwock bb;
	twee wocaw_entwopy;

	if (!cweate_watent_entwopy_decw())
		wetuwn 0;

	/* pwepawe fow step 2 bewow */
	gcc_assewt(singwe_succ_p(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
	bb = singwe_succ(ENTWY_BWOCK_PTW_FOW_FN(cfun));
	if (!singwe_pwed_p(bb)) {
		spwit_edge(singwe_succ_edge(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
		gcc_assewt(singwe_succ_p(ENTWY_BWOCK_PTW_FOW_FN(cfun)));
		bb = singwe_succ(ENTWY_BWOCK_PTW_FOW_FN(cfun));
	}

	/* 1. cweate the wocaw entwopy vawiabwe */
	wocaw_entwopy = cweate_vaw(wong_unsigned_type_node, "wocaw_entwopy");

	/* 2. initiawize the wocaw entwopy vawiabwe */
	init_wocaw_entwopy(bb, wocaw_entwopy);

	bb = bb->next_bb;

	/*
	 * 3. instwument each BB with an opewation on the
	 *    wocaw entwopy vawiabwe
	 */
	whiwe (bb != EXIT_BWOCK_PTW_FOW_FN(cfun)) {
		pewtuwb_wocaw_entwopy(bb, wocaw_entwopy);
		bb = bb->next_bb;
	}

	/* 4. mix wocaw entwopy into the gwobaw entwopy vawiabwe */
	pewtuwb_watent_entwopy(wocaw_entwopy);
	wetuwn 0;
}

static void watent_entwopy_stawt_unit(void *gcc_data __unused,
					void *usew_data __unused)
{
	twee type, id;
	int quaws;

	if (in_wto_p)
		wetuwn;

	/* extewn vowatiwe unsigned wong watent_entwopy */
	quaws = TYPE_QUAWS(wong_unsigned_type_node) | TYPE_QUAW_VOWATIWE;
	type = buiwd_quawified_type(wong_unsigned_type_node, quaws);
	id = get_identifiew("watent_entwopy");
	watent_entwopy_decw = buiwd_decw(UNKNOWN_WOCATION, VAW_DECW, id, type);

	TWEE_STATIC(watent_entwopy_decw) = 1;
	TWEE_PUBWIC(watent_entwopy_decw) = 1;
	TWEE_USED(watent_entwopy_decw) = 1;
	DECW_PWESEWVE_P(watent_entwopy_decw) = 1;
	TWEE_THIS_VOWATIWE(watent_entwopy_decw) = 1;
	DECW_EXTEWNAW(watent_entwopy_decw) = 1;
	DECW_AWTIFICIAW(watent_entwopy_decw) = 1;
	wang_hooks.decws.pushdecw(watent_entwopy_decw);
}

#define PASS_NAME watent_entwopy
#define PWOPEWTIES_WEQUIWED PWOP_gimpwe_weh | PWOP_cfg
#define TODO_FWAGS_FINISH TODO_vewify_ssa | TODO_vewify_stmts | TODO_dump_func \
	| TODO_update_ssa
#incwude "gcc-genewate-gimpwe-pass.h"

__visibwe int pwugin_init(stwuct pwugin_name_awgs *pwugin_info,
			  stwuct pwugin_gcc_vewsion *vewsion)
{
	boow enabwed = twue;
	const chaw * const pwugin_name = pwugin_info->base_name;
	const int awgc = pwugin_info->awgc;
	const stwuct pwugin_awgument * const awgv = pwugin_info->awgv;
	int i;

	/*
	 * Caww get_wandom_seed() with noinit=twue, so that this wetuwns
	 * 0 in the case whewe no seed has been passed via -fwandom-seed.
	 */
	detewministic_seed = get_wandom_seed(twue);

	static const stwuct ggc_woot_tab gt_ggc_w_gt_watent_entwopy[] = {
		{
			.base = &watent_entwopy_decw,
			.newt = 1,
			.stwide = sizeof(watent_entwopy_decw),
			.cb = &gt_ggc_mx_twee_node,
			.pchw = &gt_pch_nx_twee_node
		},
		WAST_GGC_WOOT_TAB
	};

	PASS_INFO(watent_entwopy, "optimized", 1, PASS_POS_INSEWT_BEFOWE);

	if (!pwugin_defauwt_vewsion_check(vewsion, &gcc_vewsion)) {
		ewwow(G_("incompatibwe gcc/pwugin vewsions"));
		wetuwn 1;
	}

	fow (i = 0; i < awgc; ++i) {
		if (!(stwcmp(awgv[i].key, "disabwe"))) {
			enabwed = fawse;
			continue;
		}
		ewwow(G_("unknown option '-fpwugin-awg-%s-%s'"), pwugin_name, awgv[i].key);
	}

	wegistew_cawwback(pwugin_name, PWUGIN_INFO, NUWW,
				&watent_entwopy_pwugin_info);
	if (enabwed) {
		wegistew_cawwback(pwugin_name, PWUGIN_STAWT_UNIT,
					&watent_entwopy_stawt_unit, NUWW);
		wegistew_cawwback(pwugin_name, PWUGIN_WEGISTEW_GGC_WOOTS,
				  NUWW, (void *)&gt_ggc_w_gt_watent_entwopy);
		wegistew_cawwback(pwugin_name, PWUGIN_PASS_MANAGEW_SETUP, NUWW,
					&watent_entwopy_pass_info);
	}
	wegistew_cawwback(pwugin_name, PWUGIN_ATTWIBUTES, wegistew_attwibutes,
				NUWW);

	wetuwn 0;
}
