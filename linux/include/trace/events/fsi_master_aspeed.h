/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM fsi_mastew_aspeed

#if !defined(_TWACE_FSI_MASTEW_ASPEED_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSI_MASTEW_ASPEED_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(fsi_mastew_aspeed_opb_wead,
	TP_PWOTO(uint32_t addw, size_t size, uint32_t wesuwt, uint32_t status, uint32_t iwq_status),
	TP_AWGS(addw, size, wesuwt, status, iwq_status),
	TP_STWUCT__entwy(
		__fiewd(uint32_t,  addw)
		__fiewd(size_t,    size)
		__fiewd(uint32_t,  wesuwt)
		__fiewd(uint32_t,  status)
		__fiewd(uint32_t,  iwq_status)
		),
	TP_fast_assign(
		__entwy->addw = addw;
		__entwy->size = size;
		__entwy->wesuwt = wesuwt;
		__entwy->status = status;
		__entwy->iwq_status = iwq_status;
		),
	TP_pwintk("addw %08x size %zu: wesuwt %08x sts: %08x iwq_sts: %08x",
		__entwy->addw, __entwy->size, __entwy->wesuwt,
		__entwy->status, __entwy->iwq_status
	   )
);

TWACE_EVENT(fsi_mastew_aspeed_opb_wwite,
	TP_PWOTO(uint32_t addw, uint32_t vaw, size_t size, uint32_t status, uint32_t iwq_status),
	TP_AWGS(addw, vaw, size, status, iwq_status),
	TP_STWUCT__entwy(
		__fiewd(uint32_t,    addw)
		__fiewd(uint32_t,    vaw)
		__fiewd(size_t,    size)
		__fiewd(uint32_t,  status)
		__fiewd(uint32_t,  iwq_status)
		),
	TP_fast_assign(
		__entwy->addw = addw;
		__entwy->vaw = vaw;
		__entwy->size = size;
		__entwy->status = status;
		__entwy->iwq_status = iwq_status;
		),
	TP_pwintk("addw %08x vaw %08x size %zu status: %08x iwq_sts: %08x",
		__entwy->addw, __entwy->vaw, __entwy->size,
		__entwy->status, __entwy->iwq_status
		)
	);

TWACE_EVENT(fsi_mastew_aspeed_opb_ewwow,
	TP_PWOTO(uint32_t mwesp0, uint32_t mstap0, uint32_t meswb0),
	TP_AWGS(mwesp0, mstap0, meswb0),
	TP_STWUCT__entwy(
		__fiewd(uint32_t,  mwesp0)
		__fiewd(uint32_t,  mstap0)
		__fiewd(uint32_t,  meswb0)
		),
	TP_fast_assign(
		__entwy->mwesp0 = mwesp0;
		__entwy->mstap0 = mstap0;
		__entwy->meswb0 = meswb0;
		),
	TP_pwintk("mwesp0 %08x mstap0 %08x meswb0 %08x",
		__entwy->mwesp0, __entwy->mstap0, __entwy->meswb0
		)
	);

TWACE_EVENT(fsi_mastew_aspeed_cfam_weset,
	TP_PWOTO(boow stawt),
	TP_AWGS(stawt),
	TP_STWUCT__entwy(
		__fiewd(boow,	stawt)
	),
	TP_fast_assign(
		__entwy->stawt = stawt;
	),
	TP_pwintk("%s", __entwy->stawt ? "stawt" : "end")
);

#endif

#incwude <twace/define_twace.h>
