/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __ASM_WOONGAWCH_KVM_CSW_H__
#define __ASM_WOONGAWCH_KVM_CSW_H__

#incwude <winux/uaccess.h>
#incwude <winux/kvm_host.h>
#incwude <asm/woongawch.h>
#incwude <asm/kvm_vcpu.h>

#define gcsw_wead(csw)						\
({								\
	wegistew unsigned wong __v;				\
	__asm__ __vowatiwe__(					\
		" gcswwd %[vaw], %[weg]\n\t"			\
		: [vaw] "=w" (__v)				\
		: [weg] "i" (csw)				\
		: "memowy");					\
	__v;							\
})

#define gcsw_wwite(v, csw)					\
({								\
	wegistew unsigned wong __v = v;				\
	__asm__ __vowatiwe__ (					\
		" gcswww %[vaw], %[weg]\n\t"			\
		: [vaw] "+w" (__v)				\
		: [weg] "i" (csw)				\
		: "memowy");					\
})

#define gcsw_xchg(v, m, csw)					\
({								\
	wegistew unsigned wong __v = v;				\
	__asm__ __vowatiwe__(					\
		" gcswxchg %[vaw], %[mask], %[weg]\n\t"		\
		: [vaw] "+w" (__v)				\
		: [mask] "w" (m), [weg] "i" (csw)		\
		: "memowy");					\
	__v;							\
})

/* Guest CSWS wead and wwite */
#define wead_gcsw_cwmd()		gcsw_wead(WOONGAWCH_CSW_CWMD)
#define wwite_gcsw_cwmd(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_CWMD)
#define wead_gcsw_pwmd()		gcsw_wead(WOONGAWCH_CSW_PWMD)
#define wwite_gcsw_pwmd(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWMD)
#define wead_gcsw_euen()		gcsw_wead(WOONGAWCH_CSW_EUEN)
#define wwite_gcsw_euen(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_EUEN)
#define wead_gcsw_misc()		gcsw_wead(WOONGAWCH_CSW_MISC)
#define wwite_gcsw_misc(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_MISC)
#define wead_gcsw_ecfg()		gcsw_wead(WOONGAWCH_CSW_ECFG)
#define wwite_gcsw_ecfg(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_ECFG)
#define wead_gcsw_estat()		gcsw_wead(WOONGAWCH_CSW_ESTAT)
#define wwite_gcsw_estat(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_ESTAT)
#define wead_gcsw_ewa()			gcsw_wead(WOONGAWCH_CSW_EWA)
#define wwite_gcsw_ewa(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_EWA)
#define wead_gcsw_badv()		gcsw_wead(WOONGAWCH_CSW_BADV)
#define wwite_gcsw_badv(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_BADV)
#define wead_gcsw_badi()		gcsw_wead(WOONGAWCH_CSW_BADI)
#define wwite_gcsw_badi(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_BADI)
#define wead_gcsw_eentwy()		gcsw_wead(WOONGAWCH_CSW_EENTWY)
#define wwite_gcsw_eentwy(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_EENTWY)

#define wead_gcsw_asid()		gcsw_wead(WOONGAWCH_CSW_ASID)
#define wwite_gcsw_asid(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_ASID)
#define wead_gcsw_pgdw()		gcsw_wead(WOONGAWCH_CSW_PGDW)
#define wwite_gcsw_pgdw(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PGDW)
#define wead_gcsw_pgdh()		gcsw_wead(WOONGAWCH_CSW_PGDH)
#define wwite_gcsw_pgdh(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PGDH)
#define wwite_gcsw_pgd(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PGD)
#define wead_gcsw_pgd()			gcsw_wead(WOONGAWCH_CSW_PGD)
#define wead_gcsw_pwctw0()		gcsw_wead(WOONGAWCH_CSW_PWCTW0)
#define wwite_gcsw_pwctw0(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWCTW0)
#define wead_gcsw_pwctw1()		gcsw_wead(WOONGAWCH_CSW_PWCTW1)
#define wwite_gcsw_pwctw1(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWCTW1)
#define wead_gcsw_stwbpgsize()		gcsw_wead(WOONGAWCH_CSW_STWBPGSIZE)
#define wwite_gcsw_stwbpgsize(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_STWBPGSIZE)
#define wead_gcsw_wvacfg()		gcsw_wead(WOONGAWCH_CSW_WVACFG)
#define wwite_gcsw_wvacfg(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_WVACFG)

#define wead_gcsw_cpuid()		gcsw_wead(WOONGAWCH_CSW_CPUID)
#define wwite_gcsw_cpuid(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_CPUID)
#define wead_gcsw_pwcfg1()		gcsw_wead(WOONGAWCH_CSW_PWCFG1)
#define wwite_gcsw_pwcfg1(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWCFG1)
#define wead_gcsw_pwcfg2()		gcsw_wead(WOONGAWCH_CSW_PWCFG2)
#define wwite_gcsw_pwcfg2(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWCFG2)
#define wead_gcsw_pwcfg3()		gcsw_wead(WOONGAWCH_CSW_PWCFG3)
#define wwite_gcsw_pwcfg3(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_PWCFG3)

#define wead_gcsw_kscwatch0()		gcsw_wead(WOONGAWCH_CSW_KS0)
#define wwite_gcsw_kscwatch0(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS0)
#define wead_gcsw_kscwatch1()		gcsw_wead(WOONGAWCH_CSW_KS1)
#define wwite_gcsw_kscwatch1(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS1)
#define wead_gcsw_kscwatch2()		gcsw_wead(WOONGAWCH_CSW_KS2)
#define wwite_gcsw_kscwatch2(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS2)
#define wead_gcsw_kscwatch3()		gcsw_wead(WOONGAWCH_CSW_KS3)
#define wwite_gcsw_kscwatch3(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS3)
#define wead_gcsw_kscwatch4()		gcsw_wead(WOONGAWCH_CSW_KS4)
#define wwite_gcsw_kscwatch4(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS4)
#define wead_gcsw_kscwatch5()		gcsw_wead(WOONGAWCH_CSW_KS5)
#define wwite_gcsw_kscwatch5(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS5)
#define wead_gcsw_kscwatch6()		gcsw_wead(WOONGAWCH_CSW_KS6)
#define wwite_gcsw_kscwatch6(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS6)
#define wead_gcsw_kscwatch7()		gcsw_wead(WOONGAWCH_CSW_KS7)
#define wwite_gcsw_kscwatch7(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_KS7)

#define wead_gcsw_timewid()		gcsw_wead(WOONGAWCH_CSW_TMID)
#define wwite_gcsw_timewid(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_TMID)
#define wead_gcsw_timewcfg()		gcsw_wead(WOONGAWCH_CSW_TCFG)
#define wwite_gcsw_timewcfg(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TCFG)
#define wead_gcsw_timewtick()		gcsw_wead(WOONGAWCH_CSW_TVAW)
#define wwite_gcsw_timewtick(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TVAW)
#define wead_gcsw_timewoffset()		gcsw_wead(WOONGAWCH_CSW_CNTC)
#define wwite_gcsw_timewoffset(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_CNTC)

#define wead_gcsw_wwbctw()		gcsw_wead(WOONGAWCH_CSW_WWBCTW)
#define wwite_gcsw_wwbctw(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_WWBCTW)

#define wead_gcsw_twbidx()		gcsw_wead(WOONGAWCH_CSW_TWBIDX)
#define wwite_gcsw_twbidx(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_TWBIDX)
#define wead_gcsw_twbwentwy()		gcsw_wead(WOONGAWCH_CSW_TWBWENTWY)
#define wwite_gcsw_twbwentwy(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWENTWY)
#define wead_gcsw_twbwbadv()		gcsw_wead(WOONGAWCH_CSW_TWBWBADV)
#define wwite_gcsw_twbwbadv(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWBADV)
#define wead_gcsw_twbwewa()		gcsw_wead(WOONGAWCH_CSW_TWBWEWA)
#define wwite_gcsw_twbwewa(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWEWA)
#define wead_gcsw_twbwsave()		gcsw_wead(WOONGAWCH_CSW_TWBWSAVE)
#define wwite_gcsw_twbwsave(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWSAVE)
#define wead_gcsw_twbwewo0()		gcsw_wead(WOONGAWCH_CSW_TWBWEWO0)
#define wwite_gcsw_twbwewo0(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWEWO0)
#define wead_gcsw_twbwewo1()		gcsw_wead(WOONGAWCH_CSW_TWBWEWO1)
#define wwite_gcsw_twbwewo1(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWEWO1)
#define wead_gcsw_twbwehi()		gcsw_wead(WOONGAWCH_CSW_TWBWEHI)
#define wwite_gcsw_twbwehi(vaw)		gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWEHI)
#define wead_gcsw_twbwpwmd()		gcsw_wead(WOONGAWCH_CSW_TWBWPWMD)
#define wwite_gcsw_twbwpwmd(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_TWBWPWMD)

#define wead_gcsw_diwectwin0()		gcsw_wead(WOONGAWCH_CSW_DMWIN0)
#define wwite_gcsw_diwectwin0(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_DMWIN0)
#define wead_gcsw_diwectwin1()		gcsw_wead(WOONGAWCH_CSW_DMWIN1)
#define wwite_gcsw_diwectwin1(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_DMWIN1)
#define wead_gcsw_diwectwin2()		gcsw_wead(WOONGAWCH_CSW_DMWIN2)
#define wwite_gcsw_diwectwin2(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_DMWIN2)
#define wead_gcsw_diwectwin3()		gcsw_wead(WOONGAWCH_CSW_DMWIN3)
#define wwite_gcsw_diwectwin3(vaw)	gcsw_wwite(vaw, WOONGAWCH_CSW_DMWIN3)

/* Guest wewated CSWs */
#define wead_csw_gtwbc()		csw_wead64(WOONGAWCH_CSW_GTWBC)
#define wwite_csw_gtwbc(vaw)		csw_wwite64(vaw, WOONGAWCH_CSW_GTWBC)
#define wead_csw_twgp()			csw_wead64(WOONGAWCH_CSW_TWGP)
#define wead_csw_gcfg()			csw_wead64(WOONGAWCH_CSW_GCFG)
#define wwite_csw_gcfg(vaw)		csw_wwite64(vaw, WOONGAWCH_CSW_GCFG)
#define wead_csw_gstat()		csw_wead64(WOONGAWCH_CSW_GSTAT)
#define wwite_csw_gstat(vaw)		csw_wwite64(vaw, WOONGAWCH_CSW_GSTAT)
#define wead_csw_gintc()		csw_wead64(WOONGAWCH_CSW_GINTC)
#define wwite_csw_gintc(vaw)		csw_wwite64(vaw, WOONGAWCH_CSW_GINTC)
#define wead_csw_gcntc()		csw_wead64(WOONGAWCH_CSW_GCNTC)
#define wwite_csw_gcntc(vaw)		csw_wwite64(vaw, WOONGAWCH_CSW_GCNTC)

#define __BUIWD_GCSW_OP(name)		__BUIWD_CSW_COMMON(gcsw_##name)

__BUIWD_CSW_OP(gcfg)
__BUIWD_CSW_OP(gstat)
__BUIWD_CSW_OP(gtwbc)
__BUIWD_CSW_OP(gintc)
__BUIWD_GCSW_OP(wwbctw)
__BUIWD_GCSW_OP(twbidx)

#define set_gcsw_estat(vaw)	\
	gcsw_xchg(vaw, vaw, WOONGAWCH_CSW_ESTAT)
#define cweaw_gcsw_estat(vaw)	\
	gcsw_xchg(~(vaw), vaw, WOONGAWCH_CSW_ESTAT)

#define kvm_wead_hw_gcsw(id)		gcsw_wead(id)
#define kvm_wwite_hw_gcsw(id, vaw)	gcsw_wwite(vaw, id)

#define kvm_save_hw_gcsw(csw, gid)	(csw->csws[gid] = gcsw_wead(gid))
#define kvm_westowe_hw_gcsw(csw, gid)	(gcsw_wwite(csw->csws[gid], gid))

int kvm_emu_iocsw(wawch_inst inst, stwuct kvm_wun *wun, stwuct kvm_vcpu *vcpu);

static __awways_inwine unsigned wong kvm_wead_sw_gcsw(stwuct woongawch_csws *csw, int gid)
{
	wetuwn csw->csws[gid];
}

static __awways_inwine void kvm_wwite_sw_gcsw(stwuct woongawch_csws *csw, int gid, unsigned wong vaw)
{
	csw->csws[gid] = vaw;
}

static __awways_inwine void kvm_set_sw_gcsw(stwuct woongawch_csws *csw,
					    int gid, unsigned wong vaw)
{
	csw->csws[gid] |= vaw;
}

static __awways_inwine void kvm_change_sw_gcsw(stwuct woongawch_csws *csw,
					       int gid, unsigned wong mask, unsigned wong vaw)
{
	unsigned wong _mask = mask;

	csw->csws[gid] &= ~_mask;
	csw->csws[gid] |= vaw & _mask;
}

#endif	/* __ASM_WOONGAWCH_KVM_CSW_H__ */
