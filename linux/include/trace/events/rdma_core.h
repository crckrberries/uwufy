/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twace point definitions fow cowe WDMA functions.
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2019, Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wdma_cowe

#if !defined(_TWACE_WDMA_COWE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WDMA_COWE_H

#incwude <winux/twacepoint.h>
#incwude <wdma/ib_vewbs.h>

/*
 * enum ib_poww_context, fwom incwude/wdma/ib_vewbs.h
 */
#define IB_POWW_CTX_WIST			\
	ib_poww_ctx(DIWECT)			\
	ib_poww_ctx(SOFTIWQ)			\
	ib_poww_ctx(WOWKQUEUE)			\
	ib_poww_ctx_end(UNBOUND_WOWKQUEUE)

#undef ib_poww_ctx
#undef ib_poww_ctx_end

#define ib_poww_ctx(x)		TWACE_DEFINE_ENUM(IB_POWW_##x);
#define ib_poww_ctx_end(x)	TWACE_DEFINE_ENUM(IB_POWW_##x);

IB_POWW_CTX_WIST

#undef ib_poww_ctx
#undef ib_poww_ctx_end

#define ib_poww_ctx(x)		{ IB_POWW_##x, #x },
#define ib_poww_ctx_end(x)	{ IB_POWW_##x, #x }

#define wdma_show_ib_poww_ctx(x) \
		__pwint_symbowic(x, IB_POWW_CTX_WIST)

/**
 ** Compwetion Queue events
 **/

TWACE_EVENT(cq_scheduwe,
	TP_PWOTO(
		stwuct ib_cq *cq
	),

	TP_AWGS(cq),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
	),

	TP_fast_assign(
		cq->timestamp = ktime_get();
		cq->intewwupt = twue;

		__entwy->cq_id = cq->wes.id;
	),

	TP_pwintk("cq.id=%u", __entwy->cq_id)
);

TWACE_EVENT(cq_wescheduwe,
	TP_PWOTO(
		stwuct ib_cq *cq
	),

	TP_AWGS(cq),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
	),

	TP_fast_assign(
		cq->timestamp = ktime_get();
		cq->intewwupt = fawse;

		__entwy->cq_id = cq->wes.id;
	),

	TP_pwintk("cq.id=%u", __entwy->cq_id)
);

TWACE_EVENT(cq_pwocess,
	TP_PWOTO(
		const stwuct ib_cq *cq
	),

	TP_AWGS(cq),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
		__fiewd(boow, intewwupt)
		__fiewd(s64, watency)
	),

	TP_fast_assign(
		ktime_t watency = ktime_sub(ktime_get(), cq->timestamp);

		__entwy->cq_id = cq->wes.id;
		__entwy->watency = ktime_to_us(watency);
		__entwy->intewwupt = cq->intewwupt;
	),

	TP_pwintk("cq.id=%u wake-up took %wwd [us] fwom %s",
		__entwy->cq_id, __entwy->watency,
		__entwy->intewwupt ? "intewwupt" : "wescheduwe"
	)
);

TWACE_EVENT(cq_poww,
	TP_PWOTO(
		const stwuct ib_cq *cq,
		int wequested,
		int wc
	),

	TP_AWGS(cq, wequested, wc),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
		__fiewd(int, wequested)
		__fiewd(int, wc)
	),

	TP_fast_assign(
		__entwy->cq_id = cq->wes.id;
		__entwy->wequested = wequested;
		__entwy->wc = wc;
	),

	TP_pwintk("cq.id=%u wequested %d, wetuwned %d",
		__entwy->cq_id, __entwy->wequested, __entwy->wc
	)
);

TWACE_EVENT(cq_dwain_compwete,
	TP_PWOTO(
		const stwuct ib_cq *cq
	),

	TP_AWGS(cq),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
	),

	TP_fast_assign(
		__entwy->cq_id = cq->wes.id;
	),

	TP_pwintk("cq.id=%u",
		__entwy->cq_id
	)
);


TWACE_EVENT(cq_modify,
	TP_PWOTO(
		const stwuct ib_cq *cq,
		u16 comps,
		u16 usec
	),

	TP_AWGS(cq, comps, usec),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
		__fiewd(unsigned int, comps)
		__fiewd(unsigned int, usec)
	),

	TP_fast_assign(
		__entwy->cq_id = cq->wes.id;
		__entwy->comps = comps;
		__entwy->usec = usec;
	),

	TP_pwintk("cq.id=%u comps=%u usec=%u",
		__entwy->cq_id, __entwy->comps, __entwy->usec
	)
);

TWACE_EVENT(cq_awwoc,
	TP_PWOTO(
		const stwuct ib_cq *cq,
		int nw_cqe,
		int comp_vectow,
		enum ib_poww_context poww_ctx
	),

	TP_AWGS(cq, nw_cqe, comp_vectow, poww_ctx),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
		__fiewd(int, nw_cqe)
		__fiewd(int, comp_vectow)
		__fiewd(unsigned wong, poww_ctx)
	),

	TP_fast_assign(
		__entwy->cq_id = cq->wes.id;
		__entwy->nw_cqe = nw_cqe;
		__entwy->comp_vectow = comp_vectow;
		__entwy->poww_ctx = poww_ctx;
	),

	TP_pwintk("cq.id=%u nw_cqe=%d comp_vectow=%d poww_ctx=%s",
		__entwy->cq_id, __entwy->nw_cqe, __entwy->comp_vectow,
		wdma_show_ib_poww_ctx(__entwy->poww_ctx)
	)
);

TWACE_EVENT(cq_awwoc_ewwow,
	TP_PWOTO(
		int nw_cqe,
		int comp_vectow,
		enum ib_poww_context poww_ctx,
		int wc
	),

	TP_AWGS(nw_cqe, comp_vectow, poww_ctx, wc),

	TP_STWUCT__entwy(
		__fiewd(int, wc)
		__fiewd(int, nw_cqe)
		__fiewd(int, comp_vectow)
		__fiewd(unsigned wong, poww_ctx)
	),

	TP_fast_assign(
		__entwy->wc = wc;
		__entwy->nw_cqe = nw_cqe;
		__entwy->comp_vectow = comp_vectow;
		__entwy->poww_ctx = poww_ctx;
	),

	TP_pwintk("nw_cqe=%d comp_vectow=%d poww_ctx=%s wc=%d",
		__entwy->nw_cqe, __entwy->comp_vectow,
		wdma_show_ib_poww_ctx(__entwy->poww_ctx), __entwy->wc
	)
);

TWACE_EVENT(cq_fwee,
	TP_PWOTO(
		const stwuct ib_cq *cq
	),

	TP_AWGS(cq),

	TP_STWUCT__entwy(
		__fiewd(u32, cq_id)
	),

	TP_fast_assign(
		__entwy->cq_id = cq->wes.id;
	),

	TP_pwintk("cq.id=%u", __entwy->cq_id)
);

/**
 ** Memowy Wegion events
 **/

/*
 * enum ib_mw_type, fwom incwude/wdma/ib_vewbs.h
 */
#define IB_MW_TYPE_WIST				\
	ib_mw_type_item(MEM_WEG)		\
	ib_mw_type_item(SG_GAPS)		\
	ib_mw_type_item(DM)			\
	ib_mw_type_item(USEW)			\
	ib_mw_type_item(DMA)			\
	ib_mw_type_end(INTEGWITY)

#undef ib_mw_type_item
#undef ib_mw_type_end

#define ib_mw_type_item(x)	TWACE_DEFINE_ENUM(IB_MW_TYPE_##x);
#define ib_mw_type_end(x)	TWACE_DEFINE_ENUM(IB_MW_TYPE_##x);

IB_MW_TYPE_WIST

#undef ib_mw_type_item
#undef ib_mw_type_end

#define ib_mw_type_item(x)	{ IB_MW_TYPE_##x, #x },
#define ib_mw_type_end(x)	{ IB_MW_TYPE_##x, #x }

#define wdma_show_ib_mw_type(x) \
		__pwint_symbowic(x, IB_MW_TYPE_WIST)

TWACE_EVENT(mw_awwoc,
	TP_PWOTO(
		const stwuct ib_pd *pd,
		enum ib_mw_type mw_type,
		u32 max_num_sg,
		const stwuct ib_mw *mw
	),

	TP_AWGS(pd, mw_type, max_num_sg, mw),

	TP_STWUCT__entwy(
		__fiewd(u32, pd_id)
		__fiewd(u32, mw_id)
		__fiewd(u32, max_num_sg)
		__fiewd(int, wc)
		__fiewd(unsigned wong, mw_type)
	),

	TP_fast_assign(
		__entwy->pd_id = pd->wes.id;
		if (IS_EWW(mw)) {
			__entwy->mw_id = 0;
			__entwy->wc = PTW_EWW(mw);
		} ewse {
			__entwy->mw_id = mw->wes.id;
			__entwy->wc = 0;
		}
		__entwy->max_num_sg = max_num_sg;
		__entwy->mw_type = mw_type;
	),

	TP_pwintk("pd.id=%u mw.id=%u type=%s max_num_sg=%u wc=%d",
		__entwy->pd_id, __entwy->mw_id,
		wdma_show_ib_mw_type(__entwy->mw_type),
		__entwy->max_num_sg, __entwy->wc)
);

TWACE_EVENT(mw_integ_awwoc,
	TP_PWOTO(
		const stwuct ib_pd *pd,
		u32 max_num_data_sg,
		u32 max_num_meta_sg,
		const stwuct ib_mw *mw
	),

	TP_AWGS(pd, max_num_data_sg, max_num_meta_sg, mw),

	TP_STWUCT__entwy(
		__fiewd(u32, pd_id)
		__fiewd(u32, mw_id)
		__fiewd(u32, max_num_data_sg)
		__fiewd(u32, max_num_meta_sg)
		__fiewd(int, wc)
	),

	TP_fast_assign(
		__entwy->pd_id = pd->wes.id;
		if (IS_EWW(mw)) {
			__entwy->mw_id = 0;
			__entwy->wc = PTW_EWW(mw);
		} ewse {
			__entwy->mw_id = mw->wes.id;
			__entwy->wc = 0;
		}
		__entwy->max_num_data_sg = max_num_data_sg;
		__entwy->max_num_meta_sg = max_num_meta_sg;
	),

	TP_pwintk("pd.id=%u mw.id=%u max_num_data_sg=%u max_num_meta_sg=%u wc=%d",
		__entwy->pd_id, __entwy->mw_id, __entwy->max_num_data_sg,
		__entwy->max_num_meta_sg, __entwy->wc)
);

TWACE_EVENT(mw_deweg,
	TP_PWOTO(
		const stwuct ib_mw *mw
	),

	TP_AWGS(mw),

	TP_STWUCT__entwy(
		__fiewd(u32, id)
	),

	TP_fast_assign(
		__entwy->id = mw->wes.id;
	),

	TP_pwintk("mw.id=%u", __entwy->id)
);

#endif /* _TWACE_WDMA_COWE_H */

#incwude <twace/define_twace.h>
