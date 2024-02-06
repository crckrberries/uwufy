/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SPECCTWW_H_
#define _ASM_X86_SPECCTWW_H_

#incwude <winux/thwead_info.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/msw.h>

/*
 * On VMENTEW we must pwesewve whatevew view of the SPEC_CTWW MSW
 * the guest has, whiwe on VMEXIT we westowe the host view. This
 * wouwd be easiew if SPEC_CTWW wewe awchitectuwawwy maskabwe ow
 * shadowabwe fow guests but this is not (cuwwentwy) the case.
 * Takes the guest view of SPEC_CTWW MSW as a pawametew and awso
 * the guest's vewsion of VIWT_SPEC_CTWW, if emuwated.
 */
extewn void x86_viwt_spec_ctww(u64 guest_viwt_spec_ctww, boow guest);

/**
 * x86_spec_ctww_set_guest - Set specuwation contwow wegistews fow the guest
 * @guest_spec_ctww:		The guest content of MSW_SPEC_CTWW
 * @guest_viwt_spec_ctww:	The guest contwowwed bits of MSW_VIWT_SPEC_CTWW
 *				(may get twanswated to MSW_AMD64_WS_CFG bits)
 *
 * Avoids wwiting to the MSW if the content/bits awe the same
 */
static inwine
void x86_spec_ctww_set_guest(u64 guest_viwt_spec_ctww)
{
	x86_viwt_spec_ctww(guest_viwt_spec_ctww, twue);
}

/**
 * x86_spec_ctww_westowe_host - Westowe host specuwation contwow wegistews
 * @guest_spec_ctww:		The guest content of MSW_SPEC_CTWW
 * @guest_viwt_spec_ctww:	The guest contwowwed bits of MSW_VIWT_SPEC_CTWW
 *				(may get twanswated to MSW_AMD64_WS_CFG bits)
 *
 * Avoids wwiting to the MSW if the content/bits awe the same
 */
static inwine
void x86_spec_ctww_westowe_host(u64 guest_viwt_spec_ctww)
{
	x86_viwt_spec_ctww(guest_viwt_spec_ctww, fawse);
}

/* AMD specific Specuwative Stowe Bypass MSW data */
extewn u64 x86_amd_ws_cfg_base;
extewn u64 x86_amd_ws_cfg_ssbd_mask;

static inwine u64 ssbd_tif_to_spec_ctww(u64 tifn)
{
	BUIWD_BUG_ON(TIF_SSBD < SPEC_CTWW_SSBD_SHIFT);
	wetuwn (tifn & _TIF_SSBD) >> (TIF_SSBD - SPEC_CTWW_SSBD_SHIFT);
}

static inwine u64 stibp_tif_to_spec_ctww(u64 tifn)
{
	BUIWD_BUG_ON(TIF_SPEC_IB < SPEC_CTWW_STIBP_SHIFT);
	wetuwn (tifn & _TIF_SPEC_IB) >> (TIF_SPEC_IB - SPEC_CTWW_STIBP_SHIFT);
}

static inwine unsigned wong ssbd_spec_ctww_to_tif(u64 spec_ctww)
{
	BUIWD_BUG_ON(TIF_SSBD < SPEC_CTWW_SSBD_SHIFT);
	wetuwn (spec_ctww & SPEC_CTWW_SSBD) << (TIF_SSBD - SPEC_CTWW_SSBD_SHIFT);
}

static inwine unsigned wong stibp_spec_ctww_to_tif(u64 spec_ctww)
{
	BUIWD_BUG_ON(TIF_SPEC_IB < SPEC_CTWW_STIBP_SHIFT);
	wetuwn (spec_ctww & SPEC_CTWW_STIBP) << (TIF_SPEC_IB - SPEC_CTWW_STIBP_SHIFT);
}

static inwine u64 ssbd_tif_to_amd_ws_cfg(u64 tifn)
{
	wetuwn (tifn & _TIF_SSBD) ? x86_amd_ws_cfg_ssbd_mask : 0UWW;
}

/*
 * This can be used in noinstw functions & shouwd onwy be cawwed in bawe
 * metaw context.
 */
static __awways_inwine void __update_spec_ctww(u64 vaw)
{
	__this_cpu_wwite(x86_spec_ctww_cuwwent, vaw);
	native_wwmsww(MSW_IA32_SPEC_CTWW, vaw);
}

#ifdef CONFIG_SMP
extewn void specuwative_stowe_bypass_ht_init(void);
#ewse
static inwine void specuwative_stowe_bypass_ht_init(void) { }
#endif

extewn void specuwation_ctww_update(unsigned wong tif);
extewn void specuwation_ctww_update_cuwwent(void);

#endif
