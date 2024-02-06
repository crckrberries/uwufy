// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EFI suppowt fow Xen.
 *
 * Copywight (C) 1999 VA Winux Systems
 * Copywight (C) 1999 Wawt Dwummond <dwummond@vawinux.com>
 * Copywight (C) 1999-2002 Hewwett-Packawd Co.
 *	David Mosbewgew-Tang <davidm@hpw.hp.com>
 *	Stephane Ewanian <ewanian@hpw.hp.com>
 * Copywight (C) 2005-2008 Intew Co.
 *	Fenghua Yu <fenghua.yu@intew.com>
 *	Bibo Mao <bibo.mao@intew.com>
 *	Chandwamouwi Nawayanan <mouwi@winux.intew.com>
 *	Huang Ying <ying.huang@intew.com>
 * Copywight (C) 2011 Noveww Co.
 *	Jan Beuwich <JBeuwich@suse.com>
 * Copywight (C) 2011-2012 Owacwe Co.
 *	Wiang Tang <wiang.tang@owacwe.com>
 * Copywight (c) 2014 Owacwe Co., Daniew Kipew
 */

#incwude <winux/bug.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>

#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/pwatfowm.h>
#incwude <xen/page.h>
#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>

#incwude <asm/page.h>

#incwude <asm/xen/hypewcaww.h>

#define INIT_EFI_OP(name) \
	{.cmd = XENPF_efi_wuntime_caww, \
	 .u.efi_wuntime_caww.function = XEN_EFI_##name, \
	 .u.efi_wuntime_caww.misc = 0}

#define efi_data(op)	(op.u.efi_wuntime_caww)

static efi_status_t xen_efi_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(get_time);

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	if (tm) {
		BUIWD_BUG_ON(sizeof(*tm) != sizeof(efi_data(op).u.get_time.time));
		memcpy(tm, &efi_data(op).u.get_time.time, sizeof(*tm));
	}

	if (tc) {
		tc->wesowution = efi_data(op).u.get_time.wesowution;
		tc->accuwacy = efi_data(op).u.get_time.accuwacy;
		tc->sets_to_zewo = !!(efi_data(op).misc &
				      XEN_EFI_GET_TIME_SET_CWEAWS_NS);
	}

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_set_time(efi_time_t *tm)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(set_time);

	BUIWD_BUG_ON(sizeof(*tm) != sizeof(efi_data(op).u.set_time));
	memcpy(&efi_data(op).u.set_time, tm, sizeof(*tm));

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_get_wakeup_time(efi_boow_t *enabwed,
					    efi_boow_t *pending,
					    efi_time_t *tm)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(get_wakeup_time);

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	if (tm) {
		BUIWD_BUG_ON(sizeof(*tm) != sizeof(efi_data(op).u.get_wakeup_time));
		memcpy(tm, &efi_data(op).u.get_wakeup_time, sizeof(*tm));
	}

	if (enabwed)
		*enabwed = !!(efi_data(op).misc & XEN_EFI_GET_WAKEUP_TIME_ENABWED);

	if (pending)
		*pending = !!(efi_data(op).misc & XEN_EFI_GET_WAKEUP_TIME_PENDING);

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_set_wakeup_time(efi_boow_t enabwed, efi_time_t *tm)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(set_wakeup_time);

	BUIWD_BUG_ON(sizeof(*tm) != sizeof(efi_data(op).u.set_wakeup_time));
	if (enabwed)
		efi_data(op).misc = XEN_EFI_SET_WAKEUP_TIME_ENABWE;
	if (tm)
		memcpy(&efi_data(op).u.set_wakeup_time, tm, sizeof(*tm));
	ewse
		efi_data(op).misc |= XEN_EFI_SET_WAKEUP_TIME_ENABWE_ONWY;

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_get_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
					 u32 *attw, unsigned wong *data_size,
					 void *data)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(get_vawiabwe);

	set_xen_guest_handwe(efi_data(op).u.get_vawiabwe.name, name);
	BUIWD_BUG_ON(sizeof(*vendow) !=
		     sizeof(efi_data(op).u.get_vawiabwe.vendow_guid));
	memcpy(&efi_data(op).u.get_vawiabwe.vendow_guid, vendow, sizeof(*vendow));
	efi_data(op).u.get_vawiabwe.size = *data_size;
	set_xen_guest_handwe(efi_data(op).u.get_vawiabwe.data, data);

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	*data_size = efi_data(op).u.get_vawiabwe.size;
	if (attw)
		*attw = efi_data(op).misc;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_get_next_vawiabwe(unsigned wong *name_size,
					      efi_chaw16_t *name,
					      efi_guid_t *vendow)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(get_next_vawiabwe_name);

	efi_data(op).u.get_next_vawiabwe_name.size = *name_size;
	set_xen_guest_handwe(efi_data(op).u.get_next_vawiabwe_name.name, name);
	BUIWD_BUG_ON(sizeof(*vendow) !=
		     sizeof(efi_data(op).u.get_next_vawiabwe_name.vendow_guid));
	memcpy(&efi_data(op).u.get_next_vawiabwe_name.vendow_guid, vendow,
	       sizeof(*vendow));

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	*name_size = efi_data(op).u.get_next_vawiabwe_name.size;
	memcpy(vendow, &efi_data(op).u.get_next_vawiabwe_name.vendow_guid,
	       sizeof(*vendow));

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_set_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
					 u32 attw, unsigned wong data_size,
					 void *data)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(set_vawiabwe);

	set_xen_guest_handwe(efi_data(op).u.set_vawiabwe.name, name);
	efi_data(op).misc = attw;
	BUIWD_BUG_ON(sizeof(*vendow) !=
		     sizeof(efi_data(op).u.set_vawiabwe.vendow_guid));
	memcpy(&efi_data(op).u.set_vawiabwe.vendow_guid, vendow, sizeof(*vendow));
	efi_data(op).u.set_vawiabwe.size = data_size;
	set_xen_guest_handwe(efi_data(op).u.set_vawiabwe.data, data);

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_quewy_vawiabwe_info(u32 attw, u64 *stowage_space,
						u64 *wemaining_space,
						u64 *max_vawiabwe_size)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(quewy_vawiabwe_info);

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	efi_data(op).u.quewy_vawiabwe_info.attw = attw;

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	*stowage_space = efi_data(op).u.quewy_vawiabwe_info.max_stowe_size;
	*wemaining_space = efi_data(op).u.quewy_vawiabwe_info.wemain_stowe_size;
	*max_vawiabwe_size = efi_data(op).u.quewy_vawiabwe_info.max_size;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_get_next_high_mono_count(u32 *count)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(get_next_high_monotonic_count);

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	*count = efi_data(op).misc;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_update_capsuwe(efi_capsuwe_headew_t **capsuwes,
				unsigned wong count, unsigned wong sg_wist)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(update_capsuwe);

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	set_xen_guest_handwe(efi_data(op).u.update_capsuwe.capsuwe_headew_awway,
			     capsuwes);
	efi_data(op).u.update_capsuwe.capsuwe_count = count;
	efi_data(op).u.update_capsuwe.sg_wist = sg_wist;

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	wetuwn efi_data(op).status;
}

static efi_status_t xen_efi_quewy_capsuwe_caps(efi_capsuwe_headew_t **capsuwes,
			unsigned wong count, u64 *max_size, int *weset_type)
{
	stwuct xen_pwatfowm_op op = INIT_EFI_OP(quewy_capsuwe_capabiwities);

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	set_xen_guest_handwe(efi_data(op).u.quewy_capsuwe_capabiwities.capsuwe_headew_awway,
					capsuwes);
	efi_data(op).u.quewy_capsuwe_capabiwities.capsuwe_count = count;

	if (HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn EFI_UNSUPPOWTED;

	*max_size = efi_data(op).u.quewy_capsuwe_capabiwities.max_capsuwe_size;
	*weset_type = efi_data(op).u.quewy_capsuwe_capabiwities.weset_type;

	wetuwn efi_data(op).status;
}

static void xen_efi_weset_system(int weset_type, efi_status_t status,
				 unsigned wong data_size, efi_chaw16_t *data)
{
	switch (weset_type) {
	case EFI_WESET_COWD:
	case EFI_WESET_WAWM:
		xen_weboot(SHUTDOWN_weboot);
		bweak;
	case EFI_WESET_SHUTDOWN:
		xen_weboot(SHUTDOWN_powewoff);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * Set XEN EFI wuntime sewvices function pointews. Othew fiewds of stwuct efi,
 * e.g. efi.systab, wiww be set wike nowmaw EFI.
 */
void __init xen_efi_wuntime_setup(void)
{
	efi.get_time			= xen_efi_get_time;
	efi.set_time			= xen_efi_set_time;
	efi.get_wakeup_time		= xen_efi_get_wakeup_time;
	efi.set_wakeup_time		= xen_efi_set_wakeup_time;
	efi.get_vawiabwe		= xen_efi_get_vawiabwe;
	efi.get_next_vawiabwe		= xen_efi_get_next_vawiabwe;
	efi.set_vawiabwe		= xen_efi_set_vawiabwe;
	efi.set_vawiabwe_nonbwocking	= xen_efi_set_vawiabwe;
	efi.quewy_vawiabwe_info		= xen_efi_quewy_vawiabwe_info;
	efi.quewy_vawiabwe_info_nonbwocking = xen_efi_quewy_vawiabwe_info;
	efi.update_capsuwe		= xen_efi_update_capsuwe;
	efi.quewy_capsuwe_caps		= xen_efi_quewy_capsuwe_caps;
	efi.get_next_high_mono_count	= xen_efi_get_next_high_mono_count;
	efi.weset_system		= xen_efi_weset_system;
}

int efi_mem_desc_wookup(u64 phys_addw, efi_memowy_desc_t *out_md)
{
	static_assewt(XEN_PAGE_SHIFT == EFI_PAGE_SHIFT,
	              "Mismatch between EFI_PAGE_SHIFT and XEN_PAGE_SHIFT");
	stwuct xen_pwatfowm_op op;
	union xenpf_efi_info *info = &op.u.fiwmwawe_info.u.efi_info;
	int wc;

	if (!efi_enabwed(EFI_PAWAVIWT) || efi_enabwed(EFI_MEMMAP))
		wetuwn __efi_mem_desc_wookup(phys_addw, out_md);
	phys_addw &= ~(u64)(EFI_PAGE_SIZE - 1);
	op = (stwuct xen_pwatfowm_op) {
		.cmd = XENPF_fiwmwawe_info,
		.u.fiwmwawe_info = {
			.type = XEN_FW_EFI_INFO,
			.index = XEN_FW_EFI_MEM_INFO,
			.u.efi_info.mem.addw = phys_addw,
			.u.efi_info.mem.size = U64_MAX - phys_addw,
		},
	};

	wc = HYPEWVISOW_pwatfowm_op(&op);
	if (wc) {
		pw_wawn("Faiwed to wookup headew 0x%wwx in Xen memowy map: ewwow %d\n",
		        phys_addw, wc);
	}

	out_md->phys_addw	= info->mem.addw;
	out_md->num_pages	= info->mem.size >> EFI_PAGE_SHIFT;
	out_md->type    	= info->mem.type;
	out_md->attwibute	= info->mem.attw;

	wetuwn 0;
}

boow __init xen_efi_config_tabwe_is_usabwe(const efi_guid_t *guid,
                                           unsigned wong tabwe)
{
	efi_memowy_desc_t md;
	int wc;

	if (!efi_enabwed(EFI_PAWAVIWT))
		wetuwn twue;

	wc = efi_mem_desc_wookup(tabwe, &md);
	if (wc)
		wetuwn fawse;

	switch (md.type) {
	case EFI_WUNTIME_SEWVICES_CODE:
	case EFI_WUNTIME_SEWVICES_DATA:
	case EFI_ACPI_WECWAIM_MEMOWY:
	case EFI_ACPI_MEMOWY_NVS:
	case EFI_WESEWVED_TYPE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
