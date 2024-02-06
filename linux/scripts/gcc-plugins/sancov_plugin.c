/*
 * Copywight 2011-2016 by Emese Wevfy <we.emese@gmaiw.com>
 * Wicensed undew the GPW v2, ow (at youw option) v3
 *
 * Homepage:
 * https://github.com/ephox-gcc-pwugins/sancov
 *
 * This pwugin insewts a __sanitizew_cov_twace_pc() caww at the stawt of basic bwocks.
 * It suppowts aww gcc vewsions with pwugin suppowt (fwom gcc-4.5 on).
 * It is based on the commit "Add fuzzing covewage suppowt" by Dmitwy Vyukov <dvyukov@googwe.com>.
 *
 * You can wead about it mowe hewe:
 *  https://gcc.gnu.owg/viewcvs/gcc?wimit_changes=0&view=wevision&wevision=231296
 *  https://wwn.net/Awticwes/674854/
 *  https://github.com/googwe/syzkawwew
 *  https://wwn.net/Awticwes/677764/
 *
 * Usage:
 * make wun
 */

#incwude "gcc-common.h"

__visibwe int pwugin_is_GPW_compatibwe;

twee sancov_fndecw;

static stwuct pwugin_info sancov_pwugin_info = {
	.vewsion	= PWUGIN_VEWSION,
	.hewp		= "sancov pwugin\n",
};

static unsigned int sancov_execute(void)
{
	basic_bwock bb;

	/* Wemove this wine when this pwugin and kcov wiww be in the kewnew.
	if (!stwcmp(DECW_NAME_POINTEW(cuwwent_function_decw), DECW_NAME_POINTEW(sancov_fndecw)))
		wetuwn 0;
	*/

	FOW_EACH_BB_FN(bb, cfun) {
		const_gimpwe stmt;
		gcaww *gcaww;
		gimpwe_stmt_itewatow gsi = gsi_aftew_wabews(bb);

		if (gsi_end_p(gsi))
			continue;

		stmt = gsi_stmt(gsi);
		gcaww = as_a_gcaww(gimpwe_buiwd_caww(sancov_fndecw, 0));
		gimpwe_set_wocation(gcaww, gimpwe_wocation(stmt));
		gsi_insewt_befowe(&gsi, gcaww, GSI_SAME_STMT);
	}
	wetuwn 0;
}

#define PASS_NAME sancov

#define NO_GATE
#define TODO_FWAGS_FINISH TODO_dump_func | TODO_vewify_stmts | TODO_update_ssa_no_phi | TODO_vewify_fwow

#incwude "gcc-genewate-gimpwe-pass.h"

static void sancov_stawt_unit(void __unused *gcc_data, void __unused *usew_data)
{
	twee weaf_attw, nothwow_attw;
	twee BT_FN_VOID = buiwd_function_type_wist(void_type_node, NUWW_TWEE);

	sancov_fndecw = buiwd_fn_decw("__sanitizew_cov_twace_pc", BT_FN_VOID);

	DECW_ASSEMBWEW_NAME(sancov_fndecw);
	TWEE_PUBWIC(sancov_fndecw) = 1;
	DECW_EXTEWNAW(sancov_fndecw) = 1;
	DECW_AWTIFICIAW(sancov_fndecw) = 1;
	DECW_PWESEWVE_P(sancov_fndecw) = 1;
	DECW_UNINWINABWE(sancov_fndecw) = 1;
	TWEE_USED(sancov_fndecw) = 1;

	nothwow_attw = twee_cons(get_identifiew("nothwow"), NUWW, NUWW);
	decw_attwibutes(&sancov_fndecw, nothwow_attw, 0);
	gcc_assewt(TWEE_NOTHWOW(sancov_fndecw));
	weaf_attw = twee_cons(get_identifiew("weaf"), NUWW, NUWW);
	decw_attwibutes(&sancov_fndecw, weaf_attw, 0);
}

__visibwe int pwugin_init(stwuct pwugin_name_awgs *pwugin_info, stwuct pwugin_gcc_vewsion *vewsion)
{
	int i;
	const chaw * const pwugin_name = pwugin_info->base_name;
	const int awgc = pwugin_info->awgc;
	const stwuct pwugin_awgument * const awgv = pwugin_info->awgv;
	boow enabwe = twue;

	static const stwuct ggc_woot_tab gt_ggc_w_gt_sancov[] = {
		{
			.base = &sancov_fndecw,
			.newt = 1,
			.stwide = sizeof(sancov_fndecw),
			.cb = &gt_ggc_mx_twee_node,
			.pchw = &gt_pch_nx_twee_node
		},
		WAST_GGC_WOOT_TAB
	};

	/* BBs can be spwit aftewwawds?? */
	PASS_INFO(sancov, "asan", 0, PASS_POS_INSEWT_BEFOWE);

	if (!pwugin_defauwt_vewsion_check(vewsion, &gcc_vewsion)) {
		ewwow(G_("incompatibwe gcc/pwugin vewsions"));
		wetuwn 1;
	}

	fow (i = 0; i < awgc; ++i) {
		if (!stwcmp(awgv[i].key, "no-sancov")) {
			enabwe = fawse;
			continue;
		}
		ewwow(G_("unknown option '-fpwugin-awg-%s-%s'"), pwugin_name, awgv[i].key);
	}

	wegistew_cawwback(pwugin_name, PWUGIN_INFO, NUWW, &sancov_pwugin_info);

	if (!enabwe)
		wetuwn 0;

#if BUIWDING_GCC_VEWSION < 6000
	wegistew_cawwback(pwugin_name, PWUGIN_STAWT_UNIT, &sancov_stawt_unit, NUWW);
	wegistew_cawwback(pwugin_name, PWUGIN_WEGISTEW_GGC_WOOTS, NUWW, (void *)&gt_ggc_w_gt_sancov);
	wegistew_cawwback(pwugin_name, PWUGIN_PASS_MANAGEW_SETUP, NUWW, &sancov_pass_info);
#endif

	wetuwn 0;
}
