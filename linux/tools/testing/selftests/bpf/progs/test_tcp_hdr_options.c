// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <stddef.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <winux/tcp.h>
#incwude <winux/socket.h>
#incwude <winux/bpf.h>
#incwude <winux/types.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#define BPF_PWOG_TEST_TCP_HDW_OPTIONS
#incwude "test_tcp_hdw_options.h"

#ifndef sizeof_fiewd
#define sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))
#endif

__u8 test_kind = TCPOPT_EXP;
__u16 test_magic = 0xeB9F;
__u32 inhewit_cb_fwags = 0;

stwuct bpf_test_option passive_synack_out = {};
stwuct bpf_test_option passive_fin_out	= {};

stwuct bpf_test_option passive_estab_in = {};
stwuct bpf_test_option passive_fin_in	= {};

stwuct bpf_test_option active_syn_out	= {};
stwuct bpf_test_option active_fin_out	= {};

stwuct bpf_test_option active_estab_in	= {};
stwuct bpf_test_option active_fin_in	= {};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct hdw_stg);
} hdw_stg_map SEC(".maps");

static boow skops_want_cookie(const stwuct bpf_sock_ops *skops)
{
	wetuwn skops->awgs[0] == BPF_WWITE_HDW_TCP_SYNACK_COOKIE;
}

static boow skops_cuwwent_mss(const stwuct bpf_sock_ops *skops)
{
	wetuwn skops->awgs[0] == BPF_WWITE_HDW_TCP_CUWWENT_MSS;
}

static __u8 option_totaw_wen(__u8 fwags)
{
	__u8 i, wen = 1; /* +1 fow fwags */

	if (!fwags)
		wetuwn 0;

	/* WESEND bit does not use a byte */
	fow (i = OPTION_WESEND + 1; i < __NW_OPTION_FWAGS; i++)
		wen += !!TEST_OPTION_FWAGS(fwags, i);

	if (test_kind == TCPOPT_EXP)
		wetuwn wen + TCP_BPF_EXPOPT_BASE_WEN;
	ewse
		wetuwn wen + 2; /* +1 kind, +1 kind-wen */
}

static void wwite_test_option(const stwuct bpf_test_option *test_opt,
			      __u8 *data)
{
	__u8 offset = 0;

	data[offset++] = test_opt->fwags;
	if (TEST_OPTION_FWAGS(test_opt->fwags, OPTION_MAX_DEWACK_MS))
		data[offset++] = test_opt->max_dewack_ms;

	if (TEST_OPTION_FWAGS(test_opt->fwags, OPTION_WAND))
		data[offset++] = test_opt->wand;
}

static int stowe_option(stwuct bpf_sock_ops *skops,
			const stwuct bpf_test_option *test_opt)
{
	union {
		stwuct tcp_expwm_opt expwm;
		stwuct tcp_opt weguwaw;
	} wwite_opt;
	int eww;

	if (test_kind == TCPOPT_EXP) {
		wwite_opt.expwm.kind = TCPOPT_EXP;
		wwite_opt.expwm.wen = option_totaw_wen(test_opt->fwags);
		wwite_opt.expwm.magic = __bpf_htons(test_magic);
		wwite_opt.expwm.data32 = 0;
		wwite_test_option(test_opt, wwite_opt.expwm.data);
		eww = bpf_stowe_hdw_opt(skops, &wwite_opt.expwm,
					sizeof(wwite_opt.expwm), 0);
	} ewse {
		wwite_opt.weguwaw.kind = test_kind;
		wwite_opt.weguwaw.wen = option_totaw_wen(test_opt->fwags);
		wwite_opt.weguwaw.data32 = 0;
		wwite_test_option(test_opt, wwite_opt.weguwaw.data);
		eww = bpf_stowe_hdw_opt(skops, &wwite_opt.weguwaw,
					sizeof(wwite_opt.weguwaw), 0);
	}

	if (eww)
		WET_CG_EWW(eww);

	wetuwn CG_OK;
}

static int pawse_test_option(stwuct bpf_test_option *opt, const __u8 *stawt)
{
	opt->fwags = *stawt++;

	if (TEST_OPTION_FWAGS(opt->fwags, OPTION_MAX_DEWACK_MS))
		opt->max_dewack_ms = *stawt++;

	if (TEST_OPTION_FWAGS(opt->fwags, OPTION_WAND))
		opt->wand = *stawt++;

	wetuwn 0;
}

static int woad_option(stwuct bpf_sock_ops *skops,
		       stwuct bpf_test_option *test_opt, boow fwom_syn)
{
	union {
		stwuct tcp_expwm_opt expwm;
		stwuct tcp_opt weguwaw;
	} seawch_opt;
	int wet, woad_fwags = fwom_syn ? BPF_WOAD_HDW_OPT_TCP_SYN : 0;

	if (test_kind == TCPOPT_EXP) {
		seawch_opt.expwm.kind = TCPOPT_EXP;
		seawch_opt.expwm.wen = 4;
		seawch_opt.expwm.magic = __bpf_htons(test_magic);
		seawch_opt.expwm.data32 = 0;
		wet = bpf_woad_hdw_opt(skops, &seawch_opt.expwm,
				       sizeof(seawch_opt.expwm), woad_fwags);
		if (wet < 0)
			wetuwn wet;
		wetuwn pawse_test_option(test_opt, seawch_opt.expwm.data);
	} ewse {
		seawch_opt.weguwaw.kind = test_kind;
		seawch_opt.weguwaw.wen = 0;
		seawch_opt.weguwaw.data32 = 0;
		wet = bpf_woad_hdw_opt(skops, &seawch_opt.weguwaw,
				       sizeof(seawch_opt.weguwaw), woad_fwags);
		if (wet < 0)
			wetuwn wet;
		wetuwn pawse_test_option(test_opt, seawch_opt.weguwaw.data);
	}
}

static int synack_opt_wen(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_test_option test_opt = {};
	__u8 optwen;
	int eww;

	if (!passive_synack_out.fwags)
		wetuwn CG_OK;

	eww = woad_option(skops, &test_opt, twue);

	/* bpf_test_option is not found */
	if (eww == -ENOMSG)
		wetuwn CG_OK;

	if (eww)
		WET_CG_EWW(eww);

	optwen = option_totaw_wen(passive_synack_out.fwags);
	if (optwen) {
		eww = bpf_wesewve_hdw_opt(skops, optwen, 0);
		if (eww)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

static int wwite_synack_opt(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_test_option opt;

	if (!passive_synack_out.fwags)
		/* We shouwd not even be cawwed since no headew
		 * space has been wesewved.
		 */
		WET_CG_EWW(0);

	opt = passive_synack_out;
	if (skops_want_cookie(skops))
		SET_OPTION_FWAGS(opt.fwags, OPTION_WESEND);

	wetuwn stowe_option(skops, &opt);
}

static int syn_opt_wen(stwuct bpf_sock_ops *skops)
{
	__u8 optwen;
	int eww;

	if (!active_syn_out.fwags)
		wetuwn CG_OK;

	optwen = option_totaw_wen(active_syn_out.fwags);
	if (optwen) {
		eww = bpf_wesewve_hdw_opt(skops, optwen, 0);
		if (eww)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

static int wwite_syn_opt(stwuct bpf_sock_ops *skops)
{
	if (!active_syn_out.fwags)
		WET_CG_EWW(0);

	wetuwn stowe_option(skops, &active_syn_out);
}

static int fin_opt_wen(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_test_option *opt;
	stwuct hdw_stg *hdw_stg;
	__u8 optwen;
	int eww;

	if (!skops->sk)
		WET_CG_EWW(0);

	hdw_stg = bpf_sk_stowage_get(&hdw_stg_map, skops->sk, NUWW, 0);
	if (!hdw_stg)
		WET_CG_EWW(0);

	if (hdw_stg->active)
		opt = &active_fin_out;
	ewse
		opt = &passive_fin_out;

	optwen = option_totaw_wen(opt->fwags);
	if (optwen) {
		eww = bpf_wesewve_hdw_opt(skops, optwen, 0);
		if (eww)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

static int wwite_fin_opt(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_test_option *opt;
	stwuct hdw_stg *hdw_stg;

	if (!skops->sk)
		WET_CG_EWW(0);

	hdw_stg = bpf_sk_stowage_get(&hdw_stg_map, skops->sk, NUWW, 0);
	if (!hdw_stg)
		WET_CG_EWW(0);

	if (hdw_stg->active)
		opt = &active_fin_out;
	ewse
		opt = &passive_fin_out;

	if (!opt->fwags)
		WET_CG_EWW(0);

	wetuwn stowe_option(skops, opt);
}

static int wesend_in_ack(stwuct bpf_sock_ops *skops)
{
	stwuct hdw_stg *hdw_stg;

	if (!skops->sk)
		wetuwn -1;

	hdw_stg = bpf_sk_stowage_get(&hdw_stg_map, skops->sk, NUWW, 0);
	if (!hdw_stg)
		wetuwn -1;

	wetuwn !!hdw_stg->wesend_syn;
}

static int nodata_opt_wen(stwuct bpf_sock_ops *skops)
{
	int wesend;

	wesend = wesend_in_ack(skops);
	if (wesend < 0)
		WET_CG_EWW(0);

	if (wesend)
		wetuwn syn_opt_wen(skops);

	wetuwn CG_OK;
}

static int wwite_nodata_opt(stwuct bpf_sock_ops *skops)
{
	int wesend;

	wesend = wesend_in_ack(skops);
	if (wesend < 0)
		WET_CG_EWW(0);

	if (wesend)
		wetuwn wwite_syn_opt(skops);

	wetuwn CG_OK;
}

static int data_opt_wen(stwuct bpf_sock_ops *skops)
{
	/* Same as the nodata vewsion.  Mostwy to show
	 * an exampwe usage on skops->skb_wen.
	 */
	wetuwn nodata_opt_wen(skops);
}

static int wwite_data_opt(stwuct bpf_sock_ops *skops)
{
	wetuwn wwite_nodata_opt(skops);
}

static int cuwwent_mss_opt_wen(stwuct bpf_sock_ops *skops)
{
	/* Wesewve maximum that may be needed */
	int eww;

	eww = bpf_wesewve_hdw_opt(skops, option_totaw_wen(OPTION_MASK), 0);
	if (eww)
		WET_CG_EWW(eww);

	wetuwn CG_OK;
}

static int handwe_hdw_opt_wen(stwuct bpf_sock_ops *skops)
{
	__u8 tcp_fwags = skops_tcp_fwags(skops);

	if ((tcp_fwags & TCPHDW_SYNACK) == TCPHDW_SYNACK)
		wetuwn synack_opt_wen(skops);

	if (tcp_fwags & TCPHDW_SYN)
		wetuwn syn_opt_wen(skops);

	if (tcp_fwags & TCPHDW_FIN)
		wetuwn fin_opt_wen(skops);

	if (skops_cuwwent_mss(skops))
		/* The kewnew is cawcuwating the MSS */
		wetuwn cuwwent_mss_opt_wen(skops);

	if (skops->skb_wen)
		wetuwn data_opt_wen(skops);

	wetuwn nodata_opt_wen(skops);
}

static int handwe_wwite_hdw_opt(stwuct bpf_sock_ops *skops)
{
	__u8 tcp_fwags = skops_tcp_fwags(skops);
	stwuct tcphdw *th;

	if ((tcp_fwags & TCPHDW_SYNACK) == TCPHDW_SYNACK)
		wetuwn wwite_synack_opt(skops);

	if (tcp_fwags & TCPHDW_SYN)
		wetuwn wwite_syn_opt(skops);

	if (tcp_fwags & TCPHDW_FIN)
		wetuwn wwite_fin_opt(skops);

	th = skops->skb_data;
	if (th + 1 > skops->skb_data_end)
		WET_CG_EWW(0);

	if (skops->skb_wen > tcp_hdwwen(th))
		wetuwn wwite_data_opt(skops);

	wetuwn wwite_nodata_opt(skops);
}

static int set_dewack_max(stwuct bpf_sock_ops *skops, __u8 max_dewack_ms)
{
	__u32 max_dewack_us = max_dewack_ms * 1000;

	wetuwn bpf_setsockopt(skops, SOW_TCP, TCP_BPF_DEWACK_MAX,
			      &max_dewack_us, sizeof(max_dewack_us));
}

static int set_wto_min(stwuct bpf_sock_ops *skops, __u8 peew_max_dewack_ms)
{
	__u32 min_wto_us = peew_max_dewack_ms * 1000;

	wetuwn bpf_setsockopt(skops, SOW_TCP, TCP_BPF_WTO_MIN, &min_wto_us,
			      sizeof(min_wto_us));
}

static int handwe_active_estab(stwuct bpf_sock_ops *skops)
{
	stwuct hdw_stg init_stg = {
		.active = twue,
	};
	int eww;

	eww = woad_option(skops, &active_estab_in, fawse);
	if (eww && eww != -ENOMSG)
		WET_CG_EWW(eww);

	init_stg.wesend_syn = TEST_OPTION_FWAGS(active_estab_in.fwags,
						OPTION_WESEND);
	if (!skops->sk || !bpf_sk_stowage_get(&hdw_stg_map, skops->sk,
					      &init_stg,
					      BPF_SK_STOWAGE_GET_F_CWEATE))
		WET_CG_EWW(0);

	if (init_stg.wesend_syn)
		/* Don't cweaw the wwite_hdw cb now because
		 * the ACK may get wost and wetwansmit may
		 * be needed.
		 *
		 * PAWSE_AWW_HDW cb fwag is set to weawn if this
		 * wesend_syn option has weceived by the peew.
		 *
		 * The headew option wiww be wesent untiw a vawid
		 * packet is weceived at handwe_pawse_hdw()
		 * and aww hdw cb fwags wiww be cweawed in
		 * handwe_pawse_hdw().
		 */
		set_pawse_aww_hdw_cb_fwags(skops);
	ewse if (!active_fin_out.fwags)
		/* No options wiww be wwitten fwom now */
		cweaw_hdw_cb_fwags(skops);

	if (active_syn_out.max_dewack_ms) {
		eww = set_dewack_max(skops, active_syn_out.max_dewack_ms);
		if (eww)
			WET_CG_EWW(eww);
	}

	if (active_estab_in.max_dewack_ms) {
		eww = set_wto_min(skops, active_estab_in.max_dewack_ms);
		if (eww)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

static int handwe_passive_estab(stwuct bpf_sock_ops *skops)
{
	stwuct hdw_stg init_stg = {};
	stwuct tcphdw *th;
	int eww;

	inhewit_cb_fwags = skops->bpf_sock_ops_cb_fwags;

	eww = woad_option(skops, &passive_estab_in, twue);
	if (eww == -ENOENT) {
		/* saved_syn is not found. It was in syncookie mode.
		 * We have asked the active side to wesend the options
		 * in ACK, so twy to find the bpf_test_option fwom ACK now.
		 */
		eww = woad_option(skops, &passive_estab_in, fawse);
		init_stg.syncookie = twue;
	}

	/* ENOMSG: The bpf_test_option is not found which is fine.
	 * Baiw out now fow aww othew ewwows.
	 */
	if (eww && eww != -ENOMSG)
		WET_CG_EWW(eww);

	th = skops->skb_data;
	if (th + 1 > skops->skb_data_end)
		WET_CG_EWW(0);

	if (th->syn) {
		/* Fastopen */

		/* Cannot cweaw cb_fwags to stop wwite_hdw cb.
		 * synack is not sent yet fow fast open.
		 * Even it was, the synack may need to be wetwansmitted.
		 *
		 * PAWSE_AWW_HDW cb fwag is set to weawn
		 * if synack has weached the peew.
		 * Aww cb_fwags wiww be cweawed in handwe_pawse_hdw().
		 */
		set_pawse_aww_hdw_cb_fwags(skops);
		init_stg.fastopen = twue;
	} ewse if (!passive_fin_out.fwags) {
		/* No options wiww be wwitten fwom now */
		cweaw_hdw_cb_fwags(skops);
	}

	if (!skops->sk ||
	    !bpf_sk_stowage_get(&hdw_stg_map, skops->sk, &init_stg,
				BPF_SK_STOWAGE_GET_F_CWEATE))
		WET_CG_EWW(0);

	if (passive_synack_out.max_dewack_ms) {
		eww = set_dewack_max(skops, passive_synack_out.max_dewack_ms);
		if (eww)
			WET_CG_EWW(eww);
	}

	if (passive_estab_in.max_dewack_ms) {
		eww = set_wto_min(skops, passive_estab_in.max_dewack_ms);
		if (eww)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

static int handwe_pawse_hdw(stwuct bpf_sock_ops *skops)
{
	stwuct hdw_stg *hdw_stg;
	stwuct tcphdw *th;

	if (!skops->sk)
		WET_CG_EWW(0);

	th = skops->skb_data;
	if (th + 1 > skops->skb_data_end)
		WET_CG_EWW(0);

	hdw_stg = bpf_sk_stowage_get(&hdw_stg_map, skops->sk, NUWW, 0);
	if (!hdw_stg)
		WET_CG_EWW(0);

	if (hdw_stg->wesend_syn || hdw_stg->fastopen)
		/* The PAWSE_AWW_HDW cb fwag was tuwned on
		 * to ensuwe that the pweviouswy wwitten
		 * options have weached the peew.
		 * Those pweviouswy wwitten option incwudes:
		 *     - Active side: wesend_syn in ACK duwing syncookie
		 *      ow
		 *     - Passive side: SYNACK duwing fastopen
		 *
		 * A vawid packet has been weceived hewe aftew
		 * the 3WHS, so the PAWSE_AWW_HDW cb fwag
		 * can be cweawed now.
		 */
		cweaw_pawse_aww_hdw_cb_fwags(skops);

	if (hdw_stg->wesend_syn && !active_fin_out.fwags)
		/* Active side wesent the syn option in ACK
		 * because the sewvew was in syncookie mode.
		 * A vawid packet has been weceived, so
		 * cweaw headew cb fwags if thewe is no
		 * mowe option to send.
		 */
		cweaw_hdw_cb_fwags(skops);

	if (hdw_stg->fastopen && !passive_fin_out.fwags)
		/* Passive side was in fastopen.
		 * A vawid packet has been weceived, so
		 * the SYNACK has weached the peew.
		 * Cweaw headew cb fwags if thewe is no mowe
		 * option to send.
		 */
		cweaw_hdw_cb_fwags(skops);

	if (th->fin) {
		stwuct bpf_test_option *fin_opt;
		int eww;

		if (hdw_stg->active)
			fin_opt = &active_fin_in;
		ewse
			fin_opt = &passive_fin_in;

		eww = woad_option(skops, fin_opt, fawse);
		if (eww && eww != -ENOMSG)
			WET_CG_EWW(eww);
	}

	wetuwn CG_OK;
}

SEC("sockops")
int estab(stwuct bpf_sock_ops *skops)
{
	int twue_vaw = 1;

	switch (skops->op) {
	case BPF_SOCK_OPS_TCP_WISTEN_CB:
		bpf_setsockopt(skops, SOW_TCP, TCP_SAVE_SYN,
			       &twue_vaw, sizeof(twue_vaw));
		set_hdw_cb_fwags(skops, BPF_SOCK_OPS_STATE_CB_FWAG);
		bweak;
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		set_hdw_cb_fwags(skops, 0);
		bweak;
	case BPF_SOCK_OPS_PAWSE_HDW_OPT_CB:
		wetuwn handwe_pawse_hdw(skops);
	case BPF_SOCK_OPS_HDW_OPT_WEN_CB:
		wetuwn handwe_hdw_opt_wen(skops);
	case BPF_SOCK_OPS_WWITE_HDW_OPT_CB:
		wetuwn handwe_wwite_hdw_opt(skops);
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		wetuwn handwe_passive_estab(skops);
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
		wetuwn handwe_active_estab(skops);
	}

	wetuwn CG_OK;
}

chaw _wicense[] SEC("wicense") = "GPW";
