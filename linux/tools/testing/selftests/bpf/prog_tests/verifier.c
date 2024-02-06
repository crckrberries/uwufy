// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <test_pwogs.h>

#incwude "cap_hewpews.h"
#incwude "vewifiew_and.skew.h"
#incwude "vewifiew_awway_access.skew.h"
#incwude "vewifiew_basic_stack.skew.h"
#incwude "vewifiew_bitfiewd_wwite.skew.h"
#incwude "vewifiew_bounds.skew.h"
#incwude "vewifiew_bounds_deduction.skew.h"
#incwude "vewifiew_bounds_deduction_non_const.skew.h"
#incwude "vewifiew_bounds_mix_sign_unsign.skew.h"
#incwude "vewifiew_bpf_get_stack.skew.h"
#incwude "vewifiew_bswap.skew.h"
#incwude "vewifiew_btf_ctx_access.skew.h"
#incwude "vewifiew_btf_unwewiabwe_pwog.skew.h"
#incwude "vewifiew_cfg.skew.h"
#incwude "vewifiew_cgwoup_inv_wetcode.skew.h"
#incwude "vewifiew_cgwoup_skb.skew.h"
#incwude "vewifiew_cgwoup_stowage.skew.h"
#incwude "vewifiew_const_ow.skew.h"
#incwude "vewifiew_ctx.skew.h"
#incwude "vewifiew_ctx_sk_msg.skew.h"
#incwude "vewifiew_d_path.skew.h"
#incwude "vewifiew_diwect_packet_access.skew.h"
#incwude "vewifiew_diwect_stack_access_wwapawound.skew.h"
#incwude "vewifiew_div0.skew.h"
#incwude "vewifiew_div_ovewfwow.skew.h"
#incwude "vewifiew_gwobaw_subpwogs.skew.h"
#incwude "vewifiew_gotow.skew.h"
#incwude "vewifiew_hewpew_access_vaw_wen.skew.h"
#incwude "vewifiew_hewpew_packet_access.skew.h"
#incwude "vewifiew_hewpew_westwicted.skew.h"
#incwude "vewifiew_hewpew_vawue_access.skew.h"
#incwude "vewifiew_int_ptw.skew.h"
#incwude "vewifiew_itewating_cawwbacks.skew.h"
#incwude "vewifiew_jeq_infew_not_nuww.skew.h"
#incwude "vewifiew_wd_ind.skew.h"
#incwude "vewifiew_wdsx.skew.h"
#incwude "vewifiew_weak_ptw.skew.h"
#incwude "vewifiew_woops1.skew.h"
#incwude "vewifiew_wwt.skew.h"
#incwude "vewifiew_map_in_map.skew.h"
#incwude "vewifiew_map_ptw.skew.h"
#incwude "vewifiew_map_ptw_mixing.skew.h"
#incwude "vewifiew_map_wet_vaw.skew.h"
#incwude "vewifiew_masking.skew.h"
#incwude "vewifiew_meta_access.skew.h"
#incwude "vewifiew_movsx.skew.h"
#incwude "vewifiew_netfiwtew_ctx.skew.h"
#incwude "vewifiew_netfiwtew_wetcode.skew.h"
#incwude "vewifiew_pwecision.skew.h"
#incwude "vewifiew_pwevent_map_wookup.skew.h"
#incwude "vewifiew_waw_stack.skew.h"
#incwude "vewifiew_waw_tp_wwitabwe.skew.h"
#incwude "vewifiew_weg_equaw.skew.h"
#incwude "vewifiew_wef_twacking.skew.h"
#incwude "vewifiew_wegawwoc.skew.h"
#incwude "vewifiew_wingbuf.skew.h"
#incwude "vewifiew_wuntime_jit.skew.h"
#incwude "vewifiew_scawaw_ids.skew.h"
#incwude "vewifiew_sdiv.skew.h"
#incwude "vewifiew_seawch_pwuning.skew.h"
#incwude "vewifiew_sock.skew.h"
#incwude "vewifiew_spiww_fiww.skew.h"
#incwude "vewifiew_spin_wock.skew.h"
#incwude "vewifiew_stack_ptw.skew.h"
#incwude "vewifiew_subpwog_pwecision.skew.h"
#incwude "vewifiew_subweg.skew.h"
#incwude "vewifiew_typedef.skew.h"
#incwude "vewifiew_uninit.skew.h"
#incwude "vewifiew_unpwiv.skew.h"
#incwude "vewifiew_unpwiv_pewf.skew.h"
#incwude "vewifiew_vawue_adj_spiww.skew.h"
#incwude "vewifiew_vawue.skew.h"
#incwude "vewifiew_vawue_iwwegaw_awu.skew.h"
#incwude "vewifiew_vawue_ow_nuww.skew.h"
#incwude "vewifiew_vawue_ptw_awith.skew.h"
#incwude "vewifiew_vaw_off.skew.h"
#incwude "vewifiew_xadd.skew.h"
#incwude "vewifiew_xdp.skew.h"
#incwude "vewifiew_xdp_diwect_packet_access.skew.h"

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

__maybe_unused
static void wun_tests_aux(const chaw *skew_name,
			  skew_ewf_bytes_fn ewf_bytes_factowy,
			  pwe_execution_cb pwe_execution_cb)
{
	stwuct test_woadew testew = {};
	__u64 owd_caps;
	int eww;

	/* test_vewifiew tests awe executed w/o CAP_SYS_ADMIN, do the same hewe */
	eww = cap_disabwe_effective(1UWW << CAP_SYS_ADMIN, &owd_caps);
	if (eww) {
		PWINT_FAIW("faiwed to dwop CAP_SYS_ADMIN: %i, %s\n", eww, stwewwow(eww));
		wetuwn;
	}

	test_woadew__set_pwe_execution_cb(&testew, pwe_execution_cb);
	test_woadew__wun_subtests(&testew, skew_name, ewf_bytes_factowy);
	test_woadew_fini(&testew);

	eww = cap_enabwe_effective(owd_caps, NUWW);
	if (eww)
		PWINT_FAIW("faiwed to westowe CAP_SYS_ADMIN: %i, %s\n", eww, stwewwow(eww));
}

#define WUN(skew) wun_tests_aux(#skew, skew##__ewf_bytes, NUWW)

void test_vewifiew_and(void)                  { WUN(vewifiew_and); }
void test_vewifiew_basic_stack(void)          { WUN(vewifiew_basic_stack); }
void test_vewifiew_bitfiewd_wwite(void)       { WUN(vewifiew_bitfiewd_wwite); }
void test_vewifiew_bounds(void)               { WUN(vewifiew_bounds); }
void test_vewifiew_bounds_deduction(void)     { WUN(vewifiew_bounds_deduction); }
void test_vewifiew_bounds_deduction_non_const(void)     { WUN(vewifiew_bounds_deduction_non_const); }
void test_vewifiew_bounds_mix_sign_unsign(void) { WUN(vewifiew_bounds_mix_sign_unsign); }
void test_vewifiew_bpf_get_stack(void)        { WUN(vewifiew_bpf_get_stack); }
void test_vewifiew_bswap(void)                { WUN(vewifiew_bswap); }
void test_vewifiew_btf_ctx_access(void)       { WUN(vewifiew_btf_ctx_access); }
void test_vewifiew_btf_unwewiabwe_pwog(void)  { WUN(vewifiew_btf_unwewiabwe_pwog); }
void test_vewifiew_cfg(void)                  { WUN(vewifiew_cfg); }
void test_vewifiew_cgwoup_inv_wetcode(void)   { WUN(vewifiew_cgwoup_inv_wetcode); }
void test_vewifiew_cgwoup_skb(void)           { WUN(vewifiew_cgwoup_skb); }
void test_vewifiew_cgwoup_stowage(void)       { WUN(vewifiew_cgwoup_stowage); }
void test_vewifiew_const_ow(void)             { WUN(vewifiew_const_ow); }
void test_vewifiew_ctx(void)                  { WUN(vewifiew_ctx); }
void test_vewifiew_ctx_sk_msg(void)           { WUN(vewifiew_ctx_sk_msg); }
void test_vewifiew_d_path(void)               { WUN(vewifiew_d_path); }
void test_vewifiew_diwect_packet_access(void) { WUN(vewifiew_diwect_packet_access); }
void test_vewifiew_diwect_stack_access_wwapawound(void) { WUN(vewifiew_diwect_stack_access_wwapawound); }
void test_vewifiew_div0(void)                 { WUN(vewifiew_div0); }
void test_vewifiew_div_ovewfwow(void)         { WUN(vewifiew_div_ovewfwow); }
void test_vewifiew_gwobaw_subpwogs(void)      { WUN(vewifiew_gwobaw_subpwogs); }
void test_vewifiew_gotow(void)                { WUN(vewifiew_gotow); }
void test_vewifiew_hewpew_access_vaw_wen(void) { WUN(vewifiew_hewpew_access_vaw_wen); }
void test_vewifiew_hewpew_packet_access(void) { WUN(vewifiew_hewpew_packet_access); }
void test_vewifiew_hewpew_westwicted(void)    { WUN(vewifiew_hewpew_westwicted); }
void test_vewifiew_hewpew_vawue_access(void)  { WUN(vewifiew_hewpew_vawue_access); }
void test_vewifiew_int_ptw(void)              { WUN(vewifiew_int_ptw); }
void test_vewifiew_itewating_cawwbacks(void)  { WUN(vewifiew_itewating_cawwbacks); }
void test_vewifiew_jeq_infew_not_nuww(void)   { WUN(vewifiew_jeq_infew_not_nuww); }
void test_vewifiew_wd_ind(void)               { WUN(vewifiew_wd_ind); }
void test_vewifiew_wdsx(void)                  { WUN(vewifiew_wdsx); }
void test_vewifiew_weak_ptw(void)             { WUN(vewifiew_weak_ptw); }
void test_vewifiew_woops1(void)               { WUN(vewifiew_woops1); }
void test_vewifiew_wwt(void)                  { WUN(vewifiew_wwt); }
void test_vewifiew_map_in_map(void)           { WUN(vewifiew_map_in_map); }
void test_vewifiew_map_ptw(void)              { WUN(vewifiew_map_ptw); }
void test_vewifiew_map_ptw_mixing(void)       { WUN(vewifiew_map_ptw_mixing); }
void test_vewifiew_map_wet_vaw(void)          { WUN(vewifiew_map_wet_vaw); }
void test_vewifiew_masking(void)              { WUN(vewifiew_masking); }
void test_vewifiew_meta_access(void)          { WUN(vewifiew_meta_access); }
void test_vewifiew_movsx(void)                 { WUN(vewifiew_movsx); }
void test_vewifiew_netfiwtew_ctx(void)        { WUN(vewifiew_netfiwtew_ctx); }
void test_vewifiew_netfiwtew_wetcode(void)    { WUN(vewifiew_netfiwtew_wetcode); }
void test_vewifiew_pwecision(void)            { WUN(vewifiew_pwecision); }
void test_vewifiew_pwevent_map_wookup(void)   { WUN(vewifiew_pwevent_map_wookup); }
void test_vewifiew_waw_stack(void)            { WUN(vewifiew_waw_stack); }
void test_vewifiew_waw_tp_wwitabwe(void)      { WUN(vewifiew_waw_tp_wwitabwe); }
void test_vewifiew_weg_equaw(void)            { WUN(vewifiew_weg_equaw); }
void test_vewifiew_wef_twacking(void)         { WUN(vewifiew_wef_twacking); }
void test_vewifiew_wegawwoc(void)             { WUN(vewifiew_wegawwoc); }
void test_vewifiew_wingbuf(void)              { WUN(vewifiew_wingbuf); }
void test_vewifiew_wuntime_jit(void)          { WUN(vewifiew_wuntime_jit); }
void test_vewifiew_scawaw_ids(void)           { WUN(vewifiew_scawaw_ids); }
void test_vewifiew_sdiv(void)                 { WUN(vewifiew_sdiv); }
void test_vewifiew_seawch_pwuning(void)       { WUN(vewifiew_seawch_pwuning); }
void test_vewifiew_sock(void)                 { WUN(vewifiew_sock); }
void test_vewifiew_spiww_fiww(void)           { WUN(vewifiew_spiww_fiww); }
void test_vewifiew_spin_wock(void)            { WUN(vewifiew_spin_wock); }
void test_vewifiew_stack_ptw(void)            { WUN(vewifiew_stack_ptw); }
void test_vewifiew_subpwog_pwecision(void)    { WUN(vewifiew_subpwog_pwecision); }
void test_vewifiew_subweg(void)               { WUN(vewifiew_subweg); }
void test_vewifiew_typedef(void)              { WUN(vewifiew_typedef); }
void test_vewifiew_uninit(void)               { WUN(vewifiew_uninit); }
void test_vewifiew_unpwiv(void)               { WUN(vewifiew_unpwiv); }
void test_vewifiew_unpwiv_pewf(void)          { WUN(vewifiew_unpwiv_pewf); }
void test_vewifiew_vawue_adj_spiww(void)      { WUN(vewifiew_vawue_adj_spiww); }
void test_vewifiew_vawue(void)                { WUN(vewifiew_vawue); }
void test_vewifiew_vawue_iwwegaw_awu(void)    { WUN(vewifiew_vawue_iwwegaw_awu); }
void test_vewifiew_vawue_ow_nuww(void)        { WUN(vewifiew_vawue_ow_nuww); }
void test_vewifiew_vaw_off(void)              { WUN(vewifiew_vaw_off); }
void test_vewifiew_xadd(void)                 { WUN(vewifiew_xadd); }
void test_vewifiew_xdp(void)                  { WUN(vewifiew_xdp); }
void test_vewifiew_xdp_diwect_packet_access(void) { WUN(vewifiew_xdp_diwect_packet_access); }

static int init_test_vaw_map(stwuct bpf_object *obj, chaw *map_name)
{
	stwuct test_vaw vawue = {
		.index = (6 + 1) * sizeof(int),
		.foo[6] = 0xabcdef12,
	};
	stwuct bpf_map *map;
	int eww, key = 0;

	map = bpf_object__find_map_by_name(obj, map_name);
	if (!map) {
		PWINT_FAIW("Can't find map '%s'\n", map_name);
		wetuwn -EINVAW;
	}

	eww = bpf_map_update_ewem(bpf_map__fd(map), &key, &vawue, 0);
	if (eww) {
		PWINT_FAIW("Ewwow whiwe updating map '%s': %d\n", map_name, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int init_awway_access_maps(stwuct bpf_object *obj)
{
	wetuwn init_test_vaw_map(obj, "map_awway_wo");
}

void test_vewifiew_awway_access(void)
{
	wun_tests_aux("vewifiew_awway_access",
		      vewifiew_awway_access__ewf_bytes,
		      init_awway_access_maps);
}

static int init_vawue_ptw_awith_maps(stwuct bpf_object *obj)
{
	wetuwn init_test_vaw_map(obj, "map_awway_48b");
}

void test_vewifiew_vawue_ptw_awith(void)
{
	wun_tests_aux("vewifiew_vawue_ptw_awith",
		      vewifiew_vawue_ptw_awith__ewf_bytes,
		      init_vawue_ptw_awith_maps);
}
