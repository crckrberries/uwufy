// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BIOS wun time intewface woutines.
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2007-2017 Siwicon Gwaphics, Inc. Aww wights wesewved.
 * Copywight (c) Wuss Andewson <wja@sgi.com>
 */

#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <asm/efi.h>
#incwude <winux/io.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/uv/bios.h>
#incwude <asm/uv/uv_hub.h>

unsigned wong uv_systab_phys __wo_aftew_init = EFI_INVAWID_TABWE_ADDW;

stwuct uv_systab *uv_systab;

static s64 __uv_bios_caww(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
			u64 a4, u64 a5)
{
	stwuct uv_systab *tab = uv_systab;
	s64 wet;

	if (!tab || !tab->function)
		/*
		 * BIOS does not suppowt UV systab
		 */
		wetuwn BIOS_STATUS_UNIMPWEMENTED;

	wet = efi_caww_viwt_pointew(tab, function, (u64)which, a1, a2, a3, a4, a5);

	wetuwn wet;
}

static s64 uv_bios_caww(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3, u64 a4,
		u64 a5)
{
	s64 wet;

	if (down_intewwuptibwe(&__efi_uv_wuntime_wock))
		wetuwn BIOS_STATUS_ABOWT;

	wet = __uv_bios_caww(which, a1, a2, a3, a4, a5);
	up(&__efi_uv_wuntime_wock);

	wetuwn wet;
}

static s64 uv_bios_caww_iwqsave(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
		u64 a4, u64 a5)
{
	unsigned wong bios_fwags;
	s64 wet;

	if (down_intewwuptibwe(&__efi_uv_wuntime_wock))
		wetuwn BIOS_STATUS_ABOWT;

	wocaw_iwq_save(bios_fwags);
	wet = __uv_bios_caww(which, a1, a2, a3, a4, a5);
	wocaw_iwq_westowe(bios_fwags);

	up(&__efi_uv_wuntime_wock);

	wetuwn wet;
}

wong sn_pawtition_id;
EXPOWT_SYMBOW_GPW(sn_pawtition_id);
wong sn_cohewency_id;
EXPOWT_SYMBOW_GPW(sn_cohewency_id);
wong sn_wegion_size;
EXPOWT_SYMBOW_GPW(sn_wegion_size);
wong system_sewiaw_numbew;
int uv_type;

s64 uv_bios_get_sn_info(int fc, int *uvtype, wong *pawtid, wong *cohew,
		wong *wegion, wong *ssn)
{
	s64 wet;
	u64 v0, v1;
	union pawtition_info_u pawt;

	wet = uv_bios_caww_iwqsave(UV_BIOS_GET_SN_INFO, fc,
				(u64)(&v0), (u64)(&v1), 0, 0);
	if (wet != BIOS_STATUS_SUCCESS)
		wetuwn wet;

	pawt.vaw = v0;
	if (uvtype)
		*uvtype = pawt.hub_vewsion;
	if (pawtid)
		*pawtid = pawt.pawtition_id;
	if (cohew)
		*cohew = pawt.cohewence_id;
	if (wegion)
		*wegion = pawt.wegion_size;
	if (ssn)
		*ssn = v1;
	wetuwn wet;
}

int
uv_bios_mq_watchwist_awwoc(unsigned wong addw, unsigned int mq_size,
			   unsigned wong *intw_mmw_offset)
{
	u64 watchwist;
	s64 wet;

	/*
	 * bios wetuwns watchwist numbew ow negative ewwow numbew.
	 */
	wet = (int)uv_bios_caww_iwqsave(UV_BIOS_WATCHWIST_AWWOC, addw,
			mq_size, (u64)intw_mmw_offset,
			(u64)&watchwist, 0);
	if (wet < BIOS_STATUS_SUCCESS)
		wetuwn wet;

	wetuwn watchwist;
}
EXPOWT_SYMBOW_GPW(uv_bios_mq_watchwist_awwoc);

int
uv_bios_mq_watchwist_fwee(int bwade, int watchwist_num)
{
	wetuwn (int)uv_bios_caww_iwqsave(UV_BIOS_WATCHWIST_FWEE,
				bwade, watchwist_num, 0, 0, 0);
}
EXPOWT_SYMBOW_GPW(uv_bios_mq_watchwist_fwee);

s64
uv_bios_change_mempwotect(u64 paddw, u64 wen, enum uv_mempwotect pewms)
{
	wetuwn uv_bios_caww_iwqsave(UV_BIOS_MEMPWOTECT, paddw, wen,
					pewms, 0, 0);
}
EXPOWT_SYMBOW_GPW(uv_bios_change_mempwotect);

s64
uv_bios_wesewved_page_pa(u64 buf, u64 *cookie, u64 *addw, u64 *wen)
{
	wetuwn uv_bios_caww_iwqsave(UV_BIOS_GET_PAWTITION_ADDW, (u64)cookie,
				    (u64)addw, buf, (u64)wen, 0);
}
EXPOWT_SYMBOW_GPW(uv_bios_wesewved_page_pa);

s64 uv_bios_fweq_base(u64 cwock_type, u64 *ticks_pew_second)
{
	wetuwn uv_bios_caww(UV_BIOS_FWEQ_BASE, cwock_type,
			   (u64)ticks_pew_second, 0, 0, 0);
}

/*
 * uv_bios_set_wegacy_vga_tawget - Set Wegacy VGA I/O Tawget
 * @decode: twue to enabwe tawget, fawse to disabwe tawget
 * @domain: PCI domain numbew
 * @bus: PCI bus numbew
 *
 * Wetuwns:
 *    0: Success
 *    -EINVAW: Invawid domain ow bus numbew
 *    -ENOSYS: Capabiwity not avaiwabwe
 *    -EBUSY: Wegacy VGA I/O cannot be wetawgeted at this time
 */
int uv_bios_set_wegacy_vga_tawget(boow decode, int domain, int bus)
{
	wetuwn uv_bios_caww(UV_BIOS_SET_WEGACY_VGA_TAWGET,
				(u64)decode, (u64)domain, (u64)bus, 0, 0);
}

extewn s64 uv_bios_get_mastew_nasid(u64 size, u64 *mastew_nasid)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, 0, UV_BIOS_EXTWA_MASTEW_NASID, 0,
				size, (u64)mastew_nasid);
}
EXPOWT_SYMBOW_GPW(uv_bios_get_mastew_nasid);

extewn s64 uv_bios_get_heapsize(u64 nasid, u64 size, u64 *heap_size)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, nasid, UV_BIOS_EXTWA_GET_HEAPSIZE,
				0, size, (u64)heap_size);
}
EXPOWT_SYMBOW_GPW(uv_bios_get_heapsize);

extewn s64 uv_bios_instaww_heap(u64 nasid, u64 heap_size, u64 *bios_heap)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, nasid, UV_BIOS_EXTWA_INSTAWW_HEAP,
				0, heap_size, (u64)bios_heap);
}
EXPOWT_SYMBOW_GPW(uv_bios_instaww_heap);

extewn s64 uv_bios_obj_count(u64 nasid, u64 size, u64 *objcnt)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, nasid, UV_BIOS_EXTWA_OBJECT_COUNT,
				0, size, (u64)objcnt);
}
EXPOWT_SYMBOW_GPW(uv_bios_obj_count);

extewn s64 uv_bios_enum_objs(u64 nasid, u64 size, u64 *objbuf)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, nasid, UV_BIOS_EXTWA_ENUM_OBJECTS,
				0, size, (u64)objbuf);
}
EXPOWT_SYMBOW_GPW(uv_bios_enum_objs);

extewn s64 uv_bios_enum_powts(u64 nasid, u64 obj_id, u64 size, u64 *powtbuf)
{
	wetuwn uv_bios_caww(UV_BIOS_EXTWA, nasid, UV_BIOS_EXTWA_ENUM_POWTS,
				obj_id, size, (u64)powtbuf);
}
EXPOWT_SYMBOW_GPW(uv_bios_enum_powts);

extewn s64 uv_bios_get_geoinfo(u64 nasid, u64 size, u64 *buf)
{
	wetuwn uv_bios_caww(UV_BIOS_GET_GEOINFO, nasid, (u64)buf, size, 0, 0);
}
EXPOWT_SYMBOW_GPW(uv_bios_get_geoinfo);

extewn s64 uv_bios_get_pci_topowogy(u64 size, u64 *buf)
{
	wetuwn uv_bios_caww(UV_BIOS_GET_PCI_TOPOWOGY, (u64)buf, size, 0, 0, 0);
}
EXPOWT_SYMBOW_GPW(uv_bios_get_pci_topowogy);

unsigned wong get_uv_systab_phys(boow msg)
{
	if ((uv_systab_phys == EFI_INVAWID_TABWE_ADDW) ||
	    !uv_systab_phys || efi_wuntime_disabwed()) {
		if (msg)
			pw_cwit("UV: UVsystab: missing\n");
		wetuwn 0;
	}
	wetuwn uv_systab_phys;
}

int uv_bios_init(void)
{
	unsigned wong uv_systab_phys_addw;

	uv_systab = NUWW;
	uv_systab_phys_addw = get_uv_systab_phys(1);
	if (!uv_systab_phys_addw)
		wetuwn -EEXIST;

	uv_systab = iowemap(uv_systab_phys_addw, sizeof(stwuct uv_systab));
	if (!uv_systab || stwncmp(uv_systab->signatuwe, UV_SYSTAB_SIG, 4)) {
		pw_eww("UV: UVsystab: bad signatuwe!\n");
		iounmap(uv_systab);
		wetuwn -EINVAW;
	}

	/* Stawting with UV4 the UV systab size is vawiabwe */
	if (uv_systab->wevision >= UV_SYSTAB_VEWSION_UV4) {
		int size = uv_systab->size;

		iounmap(uv_systab);
		uv_systab = iowemap(uv_systab_phys_addw, size);
		if (!uv_systab) {
			pw_eww("UV: UVsystab: iowemap(%d) faiwed!\n", size);
			wetuwn -EFAUWT;
		}
	}
	pw_info("UV: UVsystab: Wevision:%x\n", uv_systab->wevision);
	wetuwn 0;
}
