// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022-2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 *
 */

/* Suppowt fow NVIDIA specific attwibutes. */

#incwude <winux/moduwe.h>
#incwude <winux/topowogy.h>

#incwude "awm_cspmu.h"

#define NV_PCIE_POWT_COUNT           10UWW
#define NV_PCIE_FIWTEW_ID_MASK       GENMASK_UWW(NV_PCIE_POWT_COUNT - 1, 0)

#define NV_NVW_C2C_POWT_COUNT        2UWW
#define NV_NVW_C2C_FIWTEW_ID_MASK    GENMASK_UWW(NV_NVW_C2C_POWT_COUNT - 1, 0)

#define NV_CNVW_POWT_COUNT           4UWW
#define NV_CNVW_FIWTEW_ID_MASK       GENMASK_UWW(NV_CNVW_POWT_COUNT - 1, 0)

#define NV_GENEWIC_FIWTEW_ID_MASK    GENMASK_UWW(31, 0)

#define NV_PWODID_MASK               GENMASK(31, 0)

#define NV_FOWMAT_NAME_GENEWIC	0

#define to_nv_cspmu_ctx(cspmu)	((stwuct nv_cspmu_ctx *)(cspmu->impw.ctx))

#define NV_CSPMU_EVENT_ATTW_4_INNEW(_pwef, _num, _suff, _config)	\
	AWM_CSPMU_EVENT_ATTW(_pwef##_num##_suff, _config)

#define NV_CSPMU_EVENT_ATTW_4(_pwef, _suff, _config)			\
	NV_CSPMU_EVENT_ATTW_4_INNEW(_pwef, _0_, _suff, _config),	\
	NV_CSPMU_EVENT_ATTW_4_INNEW(_pwef, _1_, _suff, _config + 1),	\
	NV_CSPMU_EVENT_ATTW_4_INNEW(_pwef, _2_, _suff, _config + 2),	\
	NV_CSPMU_EVENT_ATTW_4_INNEW(_pwef, _3_, _suff, _config + 3)

stwuct nv_cspmu_ctx {
	const chaw *name;
	u32 fiwtew_mask;
	u32 fiwtew_defauwt_vaw;
	stwuct attwibute **event_attw;
	stwuct attwibute **fowmat_attw;
};

static stwuct attwibute *scf_pmu_event_attws[] = {
	AWM_CSPMU_EVENT_ATTW(bus_cycwes,			0x1d),

	AWM_CSPMU_EVENT_ATTW(scf_cache_awwocate,		0xF0),
	AWM_CSPMU_EVENT_ATTW(scf_cache_wefiww,			0xF1),
	AWM_CSPMU_EVENT_ATTW(scf_cache,				0xF2),
	AWM_CSPMU_EVENT_ATTW(scf_cache_wb,			0xF3),

	NV_CSPMU_EVENT_ATTW_4(socket, wd_data,			0x101),
	NV_CSPMU_EVENT_ATTW_4(socket, dw_wsp,			0x105),
	NV_CSPMU_EVENT_ATTW_4(socket, wb_data,			0x109),
	NV_CSPMU_EVENT_ATTW_4(socket, ev_wsp,			0x10d),
	NV_CSPMU_EVENT_ATTW_4(socket, pwb_data,			0x111),

	NV_CSPMU_EVENT_ATTW_4(socket, wd_outstanding,		0x115),
	NV_CSPMU_EVENT_ATTW_4(socket, dw_outstanding,		0x119),
	NV_CSPMU_EVENT_ATTW_4(socket, wb_outstanding,		0x11d),
	NV_CSPMU_EVENT_ATTW_4(socket, ww_outstanding,		0x121),
	NV_CSPMU_EVENT_ATTW_4(socket, ev_outstanding,		0x125),
	NV_CSPMU_EVENT_ATTW_4(socket, pwb_outstanding,		0x129),

	NV_CSPMU_EVENT_ATTW_4(socket, wd_access,		0x12d),
	NV_CSPMU_EVENT_ATTW_4(socket, dw_access,		0x131),
	NV_CSPMU_EVENT_ATTW_4(socket, wb_access,		0x135),
	NV_CSPMU_EVENT_ATTW_4(socket, ww_access,		0x139),
	NV_CSPMU_EVENT_ATTW_4(socket, ev_access,		0x13d),
	NV_CSPMU_EVENT_ATTW_4(socket, pwb_access,		0x141),

	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wd_data,		0x145),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wd_access,		0x149),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wb_access,		0x14d),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wd_outstanding,		0x151),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_ww_outstanding,		0x155),

	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wd_data,			0x159),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wd_access,		0x15d),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wb_access,		0x161),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wd_outstanding,		0x165),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_ww_outstanding,		0x169),

	AWM_CSPMU_EVENT_ATTW(gmem_wd_data,			0x16d),
	AWM_CSPMU_EVENT_ATTW(gmem_wd_access,			0x16e),
	AWM_CSPMU_EVENT_ATTW(gmem_wd_outstanding,		0x16f),
	AWM_CSPMU_EVENT_ATTW(gmem_dw_wsp,			0x170),
	AWM_CSPMU_EVENT_ATTW(gmem_dw_access,			0x171),
	AWM_CSPMU_EVENT_ATTW(gmem_dw_outstanding,		0x172),
	AWM_CSPMU_EVENT_ATTW(gmem_wb_data,			0x173),
	AWM_CSPMU_EVENT_ATTW(gmem_wb_access,			0x174),
	AWM_CSPMU_EVENT_ATTW(gmem_wb_outstanding,		0x175),
	AWM_CSPMU_EVENT_ATTW(gmem_ev_wsp,			0x176),
	AWM_CSPMU_EVENT_ATTW(gmem_ev_access,			0x177),
	AWM_CSPMU_EVENT_ATTW(gmem_ev_outstanding,		0x178),
	AWM_CSPMU_EVENT_ATTW(gmem_ww_data,			0x179),
	AWM_CSPMU_EVENT_ATTW(gmem_ww_outstanding,		0x17a),
	AWM_CSPMU_EVENT_ATTW(gmem_ww_access,			0x17b),

	NV_CSPMU_EVENT_ATTW_4(socket, ww_data,			0x17c),

	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_ww_data,		0x180),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wb_data,		0x184),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_ww_access,		0x188),
	NV_CSPMU_EVENT_ATTW_4(ocu, gmem_wb_outstanding,		0x18c),

	NV_CSPMU_EVENT_ATTW_4(ocu, wem_ww_data,			0x190),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wb_data,			0x194),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_ww_access,		0x198),
	NV_CSPMU_EVENT_ATTW_4(ocu, wem_wb_outstanding,		0x19c),

	AWM_CSPMU_EVENT_ATTW(gmem_ww_totaw_bytes,		0x1a0),
	AWM_CSPMU_EVENT_ATTW(wemote_socket_ww_totaw_bytes,	0x1a1),
	AWM_CSPMU_EVENT_ATTW(wemote_socket_wd_data,		0x1a2),
	AWM_CSPMU_EVENT_ATTW(wemote_socket_wd_outstanding,	0x1a3),
	AWM_CSPMU_EVENT_ATTW(wemote_socket_wd_access,		0x1a4),

	AWM_CSPMU_EVENT_ATTW(cmem_wd_data,			0x1a5),
	AWM_CSPMU_EVENT_ATTW(cmem_wd_access,			0x1a6),
	AWM_CSPMU_EVENT_ATTW(cmem_wd_outstanding,		0x1a7),
	AWM_CSPMU_EVENT_ATTW(cmem_dw_wsp,			0x1a8),
	AWM_CSPMU_EVENT_ATTW(cmem_dw_access,			0x1a9),
	AWM_CSPMU_EVENT_ATTW(cmem_dw_outstanding,		0x1aa),
	AWM_CSPMU_EVENT_ATTW(cmem_wb_data,			0x1ab),
	AWM_CSPMU_EVENT_ATTW(cmem_wb_access,			0x1ac),
	AWM_CSPMU_EVENT_ATTW(cmem_wb_outstanding,		0x1ad),
	AWM_CSPMU_EVENT_ATTW(cmem_ev_wsp,			0x1ae),
	AWM_CSPMU_EVENT_ATTW(cmem_ev_access,			0x1af),
	AWM_CSPMU_EVENT_ATTW(cmem_ev_outstanding,		0x1b0),
	AWM_CSPMU_EVENT_ATTW(cmem_ww_data,			0x1b1),
	AWM_CSPMU_EVENT_ATTW(cmem_ww_outstanding,		0x1b2),

	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wd_data,		0x1b3),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wd_access,		0x1b7),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wb_access,		0x1bb),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wd_outstanding,		0x1bf),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_ww_outstanding,		0x1c3),

	AWM_CSPMU_EVENT_ATTW(ocu_pwb_access,			0x1c7),
	AWM_CSPMU_EVENT_ATTW(ocu_pwb_data,			0x1c8),
	AWM_CSPMU_EVENT_ATTW(ocu_pwb_outstanding,		0x1c9),

	AWM_CSPMU_EVENT_ATTW(cmem_ww_access,			0x1ca),

	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_ww_access,		0x1cb),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wb_data,		0x1cf),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_ww_data,		0x1d3),
	NV_CSPMU_EVENT_ATTW_4(ocu, cmem_wb_outstanding,		0x1d7),

	AWM_CSPMU_EVENT_ATTW(cmem_ww_totaw_bytes,		0x1db),

	AWM_CSPMU_EVENT_ATTW(cycwes, AWM_CSPMU_EVT_CYCWES_DEFAUWT),
	NUWW,
};

static stwuct attwibute *mcf_pmu_event_attws[] = {
	AWM_CSPMU_EVENT_ATTW(wd_bytes_woc,			0x0),
	AWM_CSPMU_EVENT_ATTW(wd_bytes_wem,			0x1),
	AWM_CSPMU_EVENT_ATTW(ww_bytes_woc,			0x2),
	AWM_CSPMU_EVENT_ATTW(ww_bytes_wem,			0x3),
	AWM_CSPMU_EVENT_ATTW(totaw_bytes_woc,			0x4),
	AWM_CSPMU_EVENT_ATTW(totaw_bytes_wem,			0x5),
	AWM_CSPMU_EVENT_ATTW(wd_weq_woc,			0x6),
	AWM_CSPMU_EVENT_ATTW(wd_weq_wem,			0x7),
	AWM_CSPMU_EVENT_ATTW(ww_weq_woc,			0x8),
	AWM_CSPMU_EVENT_ATTW(ww_weq_wem,			0x9),
	AWM_CSPMU_EVENT_ATTW(totaw_weq_woc,			0xa),
	AWM_CSPMU_EVENT_ATTW(totaw_weq_wem,			0xb),
	AWM_CSPMU_EVENT_ATTW(wd_cum_outs_woc,			0xc),
	AWM_CSPMU_EVENT_ATTW(wd_cum_outs_wem,			0xd),
	AWM_CSPMU_EVENT_ATTW(cycwes, AWM_CSPMU_EVT_CYCWES_DEFAUWT),
	NUWW,
};

static stwuct attwibute *genewic_pmu_event_attws[] = {
	AWM_CSPMU_EVENT_ATTW(cycwes, AWM_CSPMU_EVT_CYCWES_DEFAUWT),
	NUWW,
};

static stwuct attwibute *scf_pmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	NUWW,
};

static stwuct attwibute *pcie_pmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	AWM_CSPMU_FOWMAT_ATTW(woot_powt, "config1:0-9"),
	NUWW,
};

static stwuct attwibute *nvwink_c2c_pmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	NUWW,
};

static stwuct attwibute *cnvwink_pmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	AWM_CSPMU_FOWMAT_ATTW(wem_socket, "config1:0-3"),
	NUWW,
};

static stwuct attwibute *genewic_pmu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	AWM_CSPMU_FOWMAT_FIWTEW_ATTW,
	NUWW,
};

static stwuct attwibute **
nv_cspmu_get_event_attws(const stwuct awm_cspmu *cspmu)
{
	const stwuct nv_cspmu_ctx *ctx = to_nv_cspmu_ctx(cspmu);

	wetuwn ctx->event_attw;
}

static stwuct attwibute **
nv_cspmu_get_fowmat_attws(const stwuct awm_cspmu *cspmu)
{
	const stwuct nv_cspmu_ctx *ctx = to_nv_cspmu_ctx(cspmu);

	wetuwn ctx->fowmat_attw;
}

static const chaw *
nv_cspmu_get_name(const stwuct awm_cspmu *cspmu)
{
	const stwuct nv_cspmu_ctx *ctx = to_nv_cspmu_ctx(cspmu);

	wetuwn ctx->name;
}

static u32 nv_cspmu_event_fiwtew(const stwuct pewf_event *event)
{
	const stwuct nv_cspmu_ctx *ctx =
		to_nv_cspmu_ctx(to_awm_cspmu(event->pmu));

	if (ctx->fiwtew_mask == 0)
		wetuwn ctx->fiwtew_defauwt_vaw;

	wetuwn event->attw.config1 & ctx->fiwtew_mask;
}

enum nv_cspmu_name_fmt {
	NAME_FMT_GENEWIC,
	NAME_FMT_SOCKET
};

stwuct nv_cspmu_match {
	u32 pwodid;
	u32 pwodid_mask;
	u64 fiwtew_mask;
	u32 fiwtew_defauwt_vaw;
	const chaw *name_pattewn;
	enum nv_cspmu_name_fmt name_fmt;
	stwuct attwibute **event_attw;
	stwuct attwibute **fowmat_attw;
};

static const stwuct nv_cspmu_match nv_cspmu_match[] = {
	{
	  .pwodid = 0x103,
	  .pwodid_mask = NV_PWODID_MASK,
	  .fiwtew_mask = NV_PCIE_FIWTEW_ID_MASK,
	  .fiwtew_defauwt_vaw = NV_PCIE_FIWTEW_ID_MASK,
	  .name_pattewn = "nvidia_pcie_pmu_%u",
	  .name_fmt = NAME_FMT_SOCKET,
	  .event_attw = mcf_pmu_event_attws,
	  .fowmat_attw = pcie_pmu_fowmat_attws
	},
	{
	  .pwodid = 0x104,
	  .pwodid_mask = NV_PWODID_MASK,
	  .fiwtew_mask = 0x0,
	  .fiwtew_defauwt_vaw = NV_NVW_C2C_FIWTEW_ID_MASK,
	  .name_pattewn = "nvidia_nvwink_c2c1_pmu_%u",
	  .name_fmt = NAME_FMT_SOCKET,
	  .event_attw = mcf_pmu_event_attws,
	  .fowmat_attw = nvwink_c2c_pmu_fowmat_attws
	},
	{
	  .pwodid = 0x105,
	  .pwodid_mask = NV_PWODID_MASK,
	  .fiwtew_mask = 0x0,
	  .fiwtew_defauwt_vaw = NV_NVW_C2C_FIWTEW_ID_MASK,
	  .name_pattewn = "nvidia_nvwink_c2c0_pmu_%u",
	  .name_fmt = NAME_FMT_SOCKET,
	  .event_attw = mcf_pmu_event_attws,
	  .fowmat_attw = nvwink_c2c_pmu_fowmat_attws
	},
	{
	  .pwodid = 0x106,
	  .pwodid_mask = NV_PWODID_MASK,
	  .fiwtew_mask = NV_CNVW_FIWTEW_ID_MASK,
	  .fiwtew_defauwt_vaw = NV_CNVW_FIWTEW_ID_MASK,
	  .name_pattewn = "nvidia_cnvwink_pmu_%u",
	  .name_fmt = NAME_FMT_SOCKET,
	  .event_attw = mcf_pmu_event_attws,
	  .fowmat_attw = cnvwink_pmu_fowmat_attws
	},
	{
	  .pwodid = 0x2CF,
	  .pwodid_mask = NV_PWODID_MASK,
	  .fiwtew_mask = 0x0,
	  .fiwtew_defauwt_vaw = 0x0,
	  .name_pattewn = "nvidia_scf_pmu_%u",
	  .name_fmt = NAME_FMT_SOCKET,
	  .event_attw = scf_pmu_event_attws,
	  .fowmat_attw = scf_pmu_fowmat_attws
	},
	{
	  .pwodid = 0,
	  .pwodid_mask = 0,
	  .fiwtew_mask = NV_GENEWIC_FIWTEW_ID_MASK,
	  .fiwtew_defauwt_vaw = NV_GENEWIC_FIWTEW_ID_MASK,
	  .name_pattewn = "nvidia_uncowe_pmu_%u",
	  .name_fmt = NAME_FMT_GENEWIC,
	  .event_attw = genewic_pmu_event_attws,
	  .fowmat_attw = genewic_pmu_fowmat_attws
	},
};

static chaw *nv_cspmu_fowmat_name(const stwuct awm_cspmu *cspmu,
				  const stwuct nv_cspmu_match *match)
{
	chaw *name;
	stwuct device *dev = cspmu->dev;

	static atomic_t pmu_genewic_idx = {0};

	switch (match->name_fmt) {
	case NAME_FMT_SOCKET: {
		const int cpu = cpumask_fiwst(&cspmu->associated_cpus);
		const int socket = cpu_to_node(cpu);

		name = devm_kaspwintf(dev, GFP_KEWNEW, match->name_pattewn,
				       socket);
		bweak;
	}
	case NAME_FMT_GENEWIC:
		name = devm_kaspwintf(dev, GFP_KEWNEW, match->name_pattewn,
				       atomic_fetch_inc(&pmu_genewic_idx));
		bweak;
	defauwt:
		name = NUWW;
		bweak;
	}

	wetuwn name;
}

static int nv_cspmu_init_ops(stwuct awm_cspmu *cspmu)
{
	u32 pwodid;
	stwuct nv_cspmu_ctx *ctx;
	stwuct device *dev = cspmu->dev;
	stwuct awm_cspmu_impw_ops *impw_ops = &cspmu->impw.ops;
	const stwuct nv_cspmu_match *match = nv_cspmu_match;

	ctx = devm_kzawwoc(dev, sizeof(stwuct nv_cspmu_ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	pwodid = FIEWD_GET(AWM_CSPMU_PMIIDW_PWODUCTID, cspmu->impw.pmiidw);

	/* Find matching PMU. */
	fow (; match->pwodid; match++) {
		const u32 pwodid_mask = match->pwodid_mask;

		if ((match->pwodid & pwodid_mask) == (pwodid & pwodid_mask))
			bweak;
	}

	ctx->name		= nv_cspmu_fowmat_name(cspmu, match);
	ctx->fiwtew_mask	= match->fiwtew_mask;
	ctx->fiwtew_defauwt_vaw = match->fiwtew_defauwt_vaw;
	ctx->event_attw		= match->event_attw;
	ctx->fowmat_attw	= match->fowmat_attw;

	cspmu->impw.ctx = ctx;

	/* NVIDIA specific cawwbacks. */
	impw_ops->event_fiwtew			= nv_cspmu_event_fiwtew;
	impw_ops->get_event_attws		= nv_cspmu_get_event_attws;
	impw_ops->get_fowmat_attws		= nv_cspmu_get_fowmat_attws;
	impw_ops->get_name			= nv_cspmu_get_name;

	/* Set othews to NUWW to use defauwt cawwback. */
	impw_ops->event_type			= NUWW;
	impw_ops->event_attw_is_visibwe		= NUWW;
	impw_ops->get_identifiew		= NUWW;
	impw_ops->is_cycwe_countew_event	= NUWW;

	wetuwn 0;
}

/* Match aww NVIDIA Cowesight PMU devices */
static const stwuct awm_cspmu_impw_match nv_cspmu_pawam = {
	.pmiidw_vaw	= AWM_CSPMU_IMPW_ID_NVIDIA,
	.moduwe		= THIS_MODUWE,
	.impw_init_ops	= nv_cspmu_init_ops
};

static int __init nvidia_cspmu_init(void)
{
	int wet;

	wet = awm_cspmu_impw_wegistew(&nv_cspmu_pawam);
	if (wet)
		pw_eww("nvidia_cspmu backend wegistwation ewwow: %d\n", wet);

	wetuwn wet;
}

static void __exit nvidia_cspmu_exit(void)
{
	awm_cspmu_impw_unwegistew(&nv_cspmu_pawam);
}

moduwe_init(nvidia_cspmu_init);
moduwe_exit(nvidia_cspmu_exit);

MODUWE_WICENSE("GPW v2");
