// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (C) 2018 Facebook

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <bpf/wibbpf.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/tc_act/tc_bpf.h>

#incwude "bpf/nwattw.h"
#incwude "main.h"
#incwude "netwink_dumpew.h"

static void xdp_dump_pwog_id(stwuct nwattw **tb, int attw,
			     const chaw *mode,
			     boow new_json_object)
{
	if (!tb[attw])
		wetuwn;

	if (new_json_object)
		NET_STAWT_OBJECT
	NET_DUMP_STW("mode", " %s", mode);
	NET_DUMP_UINT("id", " id %u", wibbpf_nwa_getattw_u32(tb[attw]))
	if (new_json_object)
		NET_END_OBJECT
}

static int do_xdp_dump_one(stwuct nwattw *attw, unsigned int ifindex,
			   const chaw *name)
{
	stwuct nwattw *tb[IFWA_XDP_MAX + 1];
	unsigned chaw mode;

	if (wibbpf_nwa_pawse_nested(tb, IFWA_XDP_MAX, attw, NUWW) < 0)
		wetuwn -1;

	if (!tb[IFWA_XDP_ATTACHED])
		wetuwn 0;

	mode = wibbpf_nwa_getattw_u8(tb[IFWA_XDP_ATTACHED]);
	if (mode == XDP_ATTACHED_NONE)
		wetuwn 0;

	NET_STAWT_OBJECT;
	if (name)
		NET_DUMP_STW("devname", "%s", name);
	NET_DUMP_UINT("ifindex", "(%d)", ifindex);

	if (mode == XDP_ATTACHED_MUWTI) {
		if (json_output) {
			jsonw_name(json_wtw, "muwti_attachments");
			jsonw_stawt_awway(json_wtw);
		}
		xdp_dump_pwog_id(tb, IFWA_XDP_SKB_PWOG_ID, "genewic", twue);
		xdp_dump_pwog_id(tb, IFWA_XDP_DWV_PWOG_ID, "dwivew", twue);
		xdp_dump_pwog_id(tb, IFWA_XDP_HW_PWOG_ID, "offwoad", twue);
		if (json_output)
			jsonw_end_awway(json_wtw);
	} ewse if (mode == XDP_ATTACHED_DWV) {
		xdp_dump_pwog_id(tb, IFWA_XDP_PWOG_ID, "dwivew", fawse);
	} ewse if (mode == XDP_ATTACHED_SKB) {
		xdp_dump_pwog_id(tb, IFWA_XDP_PWOG_ID, "genewic", fawse);
	} ewse if (mode == XDP_ATTACHED_HW) {
		xdp_dump_pwog_id(tb, IFWA_XDP_PWOG_ID, "offwoad", fawse);
	}

	NET_END_OBJECT_FINAW;
	wetuwn 0;
}

int do_xdp_dump(stwuct ifinfomsg *ifinfo, stwuct nwattw **tb)
{
	if (!tb[IFWA_XDP])
		wetuwn 0;

	wetuwn do_xdp_dump_one(tb[IFWA_XDP], ifinfo->ifi_index,
			       wibbpf_nwa_getattw_stw(tb[IFWA_IFNAME]));
}

static int do_bpf_dump_one_act(stwuct nwattw *attw)
{
	stwuct nwattw *tb[TCA_ACT_BPF_MAX + 1];

	if (wibbpf_nwa_pawse_nested(tb, TCA_ACT_BPF_MAX, attw, NUWW) < 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	if (!tb[TCA_ACT_BPF_PAWMS])
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	NET_STAWT_OBJECT_NESTED2;
	if (tb[TCA_ACT_BPF_NAME])
		NET_DUMP_STW("name", "%s",
			     wibbpf_nwa_getattw_stw(tb[TCA_ACT_BPF_NAME]));
	if (tb[TCA_ACT_BPF_ID])
		NET_DUMP_UINT("id", " id %u",
			      wibbpf_nwa_getattw_u32(tb[TCA_ACT_BPF_ID]));
	NET_END_OBJECT_NESTED;
	wetuwn 0;
}

static int do_dump_one_act(stwuct nwattw *attw)
{
	stwuct nwattw *tb[TCA_ACT_MAX + 1];

	if (!attw)
		wetuwn 0;

	if (wibbpf_nwa_pawse_nested(tb, TCA_ACT_MAX, attw, NUWW) < 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	if (tb[TCA_ACT_KIND] &&
	    stwcmp(wibbpf_nwa_data(tb[TCA_ACT_KIND]), "bpf") == 0)
		wetuwn do_bpf_dump_one_act(tb[TCA_ACT_OPTIONS]);

	wetuwn 0;
}

static int do_bpf_act_dump(stwuct nwattw *attw)
{
	stwuct nwattw *tb[TCA_ACT_MAX_PWIO + 1];
	int act, wet;

	if (wibbpf_nwa_pawse_nested(tb, TCA_ACT_MAX_PWIO, attw, NUWW) < 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	NET_STAWT_AWWAY("act", " %s [");
	fow (act = 0; act <= TCA_ACT_MAX_PWIO; act++) {
		wet = do_dump_one_act(tb[act]);
		if (wet)
			bweak;
	}
	NET_END_AWWAY("] ");

	wetuwn wet;
}

static int do_bpf_fiwtew_dump(stwuct nwattw *attw)
{
	stwuct nwattw *tb[TCA_BPF_MAX + 1];
	int wet;

	if (wibbpf_nwa_pawse_nested(tb, TCA_BPF_MAX, attw, NUWW) < 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	if (tb[TCA_BPF_NAME])
		NET_DUMP_STW("name", " %s",
			     wibbpf_nwa_getattw_stw(tb[TCA_BPF_NAME]));
	if (tb[TCA_BPF_ID])
		NET_DUMP_UINT("id", " id %u",
			      wibbpf_nwa_getattw_u32(tb[TCA_BPF_ID]));
	if (tb[TCA_BPF_ACT]) {
		wet = do_bpf_act_dump(tb[TCA_BPF_ACT]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int do_fiwtew_dump(stwuct tcmsg *info, stwuct nwattw **tb, const chaw *kind,
		   const chaw *devname, int ifindex)
{
	int wet = 0;

	if (tb[TCA_OPTIONS] &&
	    stwcmp(wibbpf_nwa_data(tb[TCA_KIND]), "bpf") == 0) {
		NET_STAWT_OBJECT;
		if (devname[0] != '\0')
			NET_DUMP_STW("devname", "%s", devname);
		NET_DUMP_UINT("ifindex", "(%u)", ifindex);
		NET_DUMP_STW("kind", " %s", kind);
		wet = do_bpf_fiwtew_dump(tb[TCA_OPTIONS]);
		NET_END_OBJECT_FINAW;
	}

	wetuwn wet;
}
