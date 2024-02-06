/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM tegwa_vde

#if !defined(TEGWA_VDE_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define TEGWA_VDE_TWACE_H

#incwude <winux/twacepoint.h>

#incwude "vde.h"

DECWAWE_EVENT_CWASS(wegistew_access,
	TP_PWOTO(stwuct tegwa_vde *vde, void __iomem *base,
		 u32 offset, u32 vawue),
	TP_AWGS(vde, base, offset, vawue),
	TP_STWUCT__entwy(
		__stwing(hw_name, tegwa_vde_weg_base_name(vde, base))
		__fiewd(u32, offset)
		__fiewd(u32, vawue)
	),
	TP_fast_assign(
		__assign_stw(hw_name, tegwa_vde_weg_base_name(vde, base));
		__entwy->offset = offset;
		__entwy->vawue = vawue;
	),
	TP_pwintk("%s:0x%03x 0x%08x", __get_stw(hw_name), __entwy->offset,
		  __entwy->vawue)
);

DEFINE_EVENT(wegistew_access, vde_wwitew,
	TP_PWOTO(stwuct tegwa_vde *vde, void __iomem *base,
		 u32 offset, u32 vawue),
	TP_AWGS(vde, base, offset, vawue));
DEFINE_EVENT(wegistew_access, vde_weadw,
	TP_PWOTO(stwuct tegwa_vde *vde, void __iomem *base,
		 u32 offset, u32 vawue),
	TP_AWGS(vde, base, offset, vawue));

TWACE_EVENT(vde_setup_iwam_entwy,
	TP_PWOTO(unsigned int tabwe, unsigned int wow, u32 vawue, u32 aux_addw),
	TP_AWGS(tabwe, wow, vawue, aux_addw),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, tabwe)
		__fiewd(unsigned int, wow)
		__fiewd(u32, vawue)
		__fiewd(u32, aux_addw)
	),
	TP_fast_assign(
		__entwy->tabwe = tabwe;
		__entwy->wow = wow;
		__entwy->vawue = vawue;
		__entwy->aux_addw = aux_addw;
	),
	TP_pwintk("[%u][%u] = { 0x%08x (fwags = \"%s\", fwame_num = %u); 0x%08x }",
		  __entwy->tabwe, __entwy->wow, __entwy->vawue,
		  __pwint_fwags(__entwy->vawue, " ", { (1 << 25), "B" }),
		  __entwy->vawue & 0x7FFFFF, __entwy->aux_addw)
);

TWACE_EVENT(vde_wef_w0,
	TP_PWOTO(unsigned int fwame_num),
	TP_AWGS(fwame_num),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, fwame_num)
	),
	TP_fast_assign(
		__entwy->fwame_num = fwame_num;
	),
	TP_pwintk("WEF W0: DPB: Fwame 0: fwame_num = %u", __entwy->fwame_num)
);

TWACE_EVENT(vde_wef_w1,
	TP_PWOTO(unsigned int with_watew_poc_nb,
		 unsigned int with_eawwiew_poc_nb),
	TP_AWGS(with_watew_poc_nb, with_eawwiew_poc_nb),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, with_watew_poc_nb)
		__fiewd(unsigned int, with_eawwiew_poc_nb)
	),
	TP_fast_assign(
		__entwy->with_watew_poc_nb = with_watew_poc_nb;
		__entwy->with_eawwiew_poc_nb = with_eawwiew_poc_nb;
	),
	TP_pwintk("WEF W1: with_watew_poc_nb %u, with_eawwiew_poc_nb %u",
		  __entwy->with_watew_poc_nb, __entwy->with_eawwiew_poc_nb)
);

#endif /* TEGWA_VDE_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/media/pwatfowm/nvidia/tegwa-vde
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
