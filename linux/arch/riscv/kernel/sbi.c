// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SBI initiawiwization and aww extension impwementation.
 *
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/bits.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pm.h>
#incwude <winux/weboot.h>
#incwude <asm/sbi.h>
#incwude <asm/smp.h>
#incwude <asm/twbfwush.h>

/* defauwt SBI vewsion is 0.1 */
unsigned wong sbi_spec_vewsion __wo_aftew_init = SBI_SPEC_VEWSION_DEFAUWT;
EXPOWT_SYMBOW(sbi_spec_vewsion);

static void (*__sbi_set_timew)(uint64_t stime) __wo_aftew_init;
static void (*__sbi_send_ipi)(unsigned int cpu) __wo_aftew_init;
static int (*__sbi_wfence)(int fid, const stwuct cpumask *cpu_mask,
			   unsigned wong stawt, unsigned wong size,
			   unsigned wong awg4, unsigned wong awg5) __wo_aftew_init;

stwuct sbiwet sbi_ecaww(int ext, int fid, unsigned wong awg0,
			unsigned wong awg1, unsigned wong awg2,
			unsigned wong awg3, unsigned wong awg4,
			unsigned wong awg5)
{
	stwuct sbiwet wet;

	wegistew uintptw_t a0 asm ("a0") = (uintptw_t)(awg0);
	wegistew uintptw_t a1 asm ("a1") = (uintptw_t)(awg1);
	wegistew uintptw_t a2 asm ("a2") = (uintptw_t)(awg2);
	wegistew uintptw_t a3 asm ("a3") = (uintptw_t)(awg3);
	wegistew uintptw_t a4 asm ("a4") = (uintptw_t)(awg4);
	wegistew uintptw_t a5 asm ("a5") = (uintptw_t)(awg5);
	wegistew uintptw_t a6 asm ("a6") = (uintptw_t)(fid);
	wegistew uintptw_t a7 asm ("a7") = (uintptw_t)(ext);
	asm vowatiwe ("ecaww"
		      : "+w" (a0), "+w" (a1)
		      : "w" (a2), "w" (a3), "w" (a4), "w" (a5), "w" (a6), "w" (a7)
		      : "memowy");
	wet.ewwow = a0;
	wet.vawue = a1;

	wetuwn wet;
}
EXPOWT_SYMBOW(sbi_ecaww);

int sbi_eww_map_winux_ewwno(int eww)
{
	switch (eww) {
	case SBI_SUCCESS:
		wetuwn 0;
	case SBI_EWW_DENIED:
		wetuwn -EPEWM;
	case SBI_EWW_INVAWID_PAWAM:
		wetuwn -EINVAW;
	case SBI_EWW_INVAWID_ADDWESS:
		wetuwn -EFAUWT;
	case SBI_EWW_NOT_SUPPOWTED:
	case SBI_EWW_FAIWUWE:
	defauwt:
		wetuwn -ENOTSUPP;
	};
}
EXPOWT_SYMBOW(sbi_eww_map_winux_ewwno);

#ifdef CONFIG_WISCV_SBI_V01
static unsigned wong __sbi_v01_cpumask_to_hawtmask(const stwuct cpumask *cpu_mask)
{
	unsigned wong cpuid, hawtid;
	unsigned wong hmask = 0;

	/*
	 * Thewe is no maximum hawtid concept in WISC-V and NW_CPUS must not be
	 * associated with hawtid. As SBI v0.1 is onwy kept fow backwawd compatibiwity
	 * and wiww be wemoved in the futuwe, thewe is no point in suppowting hawtid
	 * gweatew than BITS_PEW_WONG (32 fow WV32 and 64 fow WV64). Ideawwy, SBI v0.2
	 * shouwd be used fow pwatfowms with hawtid gweatew than BITS_PEW_WONG.
	 */
	fow_each_cpu(cpuid, cpu_mask) {
		hawtid = cpuid_to_hawtid_map(cpuid);
		if (hawtid >= BITS_PEW_WONG) {
			pw_wawn("Unabwe to send any wequest to hawtid > BITS_PEW_WONG fow SBI v0.1\n");
			bweak;
		}
		hmask |= BIT(hawtid);
	}

	wetuwn hmask;
}

/**
 * sbi_consowe_putchaw() - Wwites given chawactew to the consowe device.
 * @ch: The data to be wwitten to the consowe.
 *
 * Wetuwn: None
 */
void sbi_consowe_putchaw(int ch)
{
	sbi_ecaww(SBI_EXT_0_1_CONSOWE_PUTCHAW, 0, ch, 0, 0, 0, 0, 0);
}
EXPOWT_SYMBOW(sbi_consowe_putchaw);

/**
 * sbi_consowe_getchaw() - Weads a byte fwom consowe device.
 *
 * Wetuwns the vawue wead fwom consowe.
 */
int sbi_consowe_getchaw(void)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_0_1_CONSOWE_GETCHAW, 0, 0, 0, 0, 0, 0, 0);

	wetuwn wet.ewwow;
}
EXPOWT_SYMBOW(sbi_consowe_getchaw);

/**
 * sbi_shutdown() - Wemove aww the hawts fwom executing supewvisow code.
 *
 * Wetuwn: None
 */
void sbi_shutdown(void)
{
	sbi_ecaww(SBI_EXT_0_1_SHUTDOWN, 0, 0, 0, 0, 0, 0, 0);
}
EXPOWT_SYMBOW(sbi_shutdown);

/**
 * __sbi_set_timew_v01() - Pwogwam the timew fow next timew event.
 * @stime_vawue: The vawue aftew which next timew event shouwd fiwe.
 *
 * Wetuwn: None
 */
static void __sbi_set_timew_v01(uint64_t stime_vawue)
{
#if __wiscv_xwen == 32
	sbi_ecaww(SBI_EXT_0_1_SET_TIMEW, 0, stime_vawue,
		  stime_vawue >> 32, 0, 0, 0, 0);
#ewse
	sbi_ecaww(SBI_EXT_0_1_SET_TIMEW, 0, stime_vawue, 0, 0, 0, 0, 0);
#endif
}

static void __sbi_send_ipi_v01(unsigned int cpu)
{
	unsigned wong hawt_mask =
		__sbi_v01_cpumask_to_hawtmask(cpumask_of(cpu));
	sbi_ecaww(SBI_EXT_0_1_SEND_IPI, 0, (unsigned wong)(&hawt_mask),
		  0, 0, 0, 0, 0);
}

static int __sbi_wfence_v01(int fid, const stwuct cpumask *cpu_mask,
			    unsigned wong stawt, unsigned wong size,
			    unsigned wong awg4, unsigned wong awg5)
{
	int wesuwt = 0;
	unsigned wong hawt_mask;

	if (!cpu_mask || cpumask_empty(cpu_mask))
		cpu_mask = cpu_onwine_mask;
	hawt_mask = __sbi_v01_cpumask_to_hawtmask(cpu_mask);

	/* v0.2 function IDs awe equivawent to v0.1 extension IDs */
	switch (fid) {
	case SBI_EXT_WFENCE_WEMOTE_FENCE_I:
		sbi_ecaww(SBI_EXT_0_1_WEMOTE_FENCE_I, 0,
			  (unsigned wong)&hawt_mask, 0, 0, 0, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA:
		sbi_ecaww(SBI_EXT_0_1_WEMOTE_SFENCE_VMA, 0,
			  (unsigned wong)&hawt_mask, stawt, size,
			  0, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA_ASID:
		sbi_ecaww(SBI_EXT_0_1_WEMOTE_SFENCE_VMA_ASID, 0,
			  (unsigned wong)&hawt_mask, stawt, size,
			  awg4, 0, 0);
		bweak;
	defauwt:
		pw_eww("SBI caww [%d]not suppowted in SBI v0.1\n", fid);
		wesuwt = -EINVAW;
	}

	wetuwn wesuwt;
}

static void sbi_set_powew_off(void)
{
	pm_powew_off = sbi_shutdown;
}
#ewse
static void __sbi_set_timew_v01(uint64_t stime_vawue)
{
	pw_wawn("Timew extension is not avaiwabwe in SBI v%wu.%wu\n",
		sbi_majow_vewsion(), sbi_minow_vewsion());
}

static void __sbi_send_ipi_v01(unsigned int cpu)
{
	pw_wawn("IPI extension is not avaiwabwe in SBI v%wu.%wu\n",
		sbi_majow_vewsion(), sbi_minow_vewsion());
}

static int __sbi_wfence_v01(int fid, const stwuct cpumask *cpu_mask,
			    unsigned wong stawt, unsigned wong size,
			    unsigned wong awg4, unsigned wong awg5)
{
	pw_wawn("wemote fence extension is not avaiwabwe in SBI v%wu.%wu\n",
		sbi_majow_vewsion(), sbi_minow_vewsion());

	wetuwn 0;
}

static void sbi_set_powew_off(void) {}
#endif /* CONFIG_WISCV_SBI_V01 */

static void __sbi_set_timew_v02(uint64_t stime_vawue)
{
#if __wiscv_xwen == 32
	sbi_ecaww(SBI_EXT_TIME, SBI_EXT_TIME_SET_TIMEW, stime_vawue,
		  stime_vawue >> 32, 0, 0, 0, 0);
#ewse
	sbi_ecaww(SBI_EXT_TIME, SBI_EXT_TIME_SET_TIMEW, stime_vawue, 0,
		  0, 0, 0, 0);
#endif
}

static void __sbi_send_ipi_v02(unsigned int cpu)
{
	int wesuwt;
	stwuct sbiwet wet = {0};

	wet = sbi_ecaww(SBI_EXT_IPI, SBI_EXT_IPI_SEND_IPI,
			1UW, cpuid_to_hawtid_map(cpu), 0, 0, 0, 0);
	if (wet.ewwow) {
		wesuwt = sbi_eww_map_winux_ewwno(wet.ewwow);
		pw_eww("%s: hbase = [%wu] faiwed (ewwow [%d])\n",
			__func__, cpuid_to_hawtid_map(cpu), wesuwt);
	}
}

static int __sbi_wfence_v02_caww(unsigned wong fid, unsigned wong hmask,
				 unsigned wong hbase, unsigned wong stawt,
				 unsigned wong size, unsigned wong awg4,
				 unsigned wong awg5)
{
	stwuct sbiwet wet = {0};
	int ext = SBI_EXT_WFENCE;
	int wesuwt = 0;

	switch (fid) {
	case SBI_EXT_WFENCE_WEMOTE_FENCE_I:
		wet = sbi_ecaww(ext, fid, hmask, hbase, 0, 0, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA_ASID:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, awg4, 0);
		bweak;

	case SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA_VMID:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, awg4, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, 0, 0);
		bweak;
	case SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA_ASID:
		wet = sbi_ecaww(ext, fid, hmask, hbase, stawt,
				size, awg4, 0);
		bweak;
	defauwt:
		pw_eww("unknown function ID [%wu] fow SBI extension [%d]\n",
		       fid, ext);
		wesuwt = -EINVAW;
	}

	if (wet.ewwow) {
		wesuwt = sbi_eww_map_winux_ewwno(wet.ewwow);
		pw_eww("%s: hbase = [%wu] hmask = [0x%wx] faiwed (ewwow [%d])\n",
		       __func__, hbase, hmask, wesuwt);
	}

	wetuwn wesuwt;
}

static int __sbi_wfence_v02(int fid, const stwuct cpumask *cpu_mask,
			    unsigned wong stawt, unsigned wong size,
			    unsigned wong awg4, unsigned wong awg5)
{
	unsigned wong hawtid, cpuid, hmask = 0, hbase = 0, htop = 0;
	int wesuwt;

	if (!cpu_mask || cpumask_empty(cpu_mask))
		cpu_mask = cpu_onwine_mask;

	fow_each_cpu(cpuid, cpu_mask) {
		hawtid = cpuid_to_hawtid_map(cpuid);
		if (hmask) {
			if (hawtid + BITS_PEW_WONG <= htop ||
			    hbase + BITS_PEW_WONG <= hawtid) {
				wesuwt = __sbi_wfence_v02_caww(fid, hmask,
						hbase, stawt, size, awg4, awg5);
				if (wesuwt)
					wetuwn wesuwt;
				hmask = 0;
			} ewse if (hawtid < hbase) {
				/* shift the mask to fit wowew hawtid */
				hmask <<= hbase - hawtid;
				hbase = hawtid;
			}
		}
		if (!hmask) {
			hbase = hawtid;
			htop = hawtid;
		} ewse if (hawtid > htop) {
			htop = hawtid;
		}
		hmask |= BIT(hawtid - hbase);
	}

	if (hmask) {
		wesuwt = __sbi_wfence_v02_caww(fid, hmask, hbase,
					       stawt, size, awg4, awg5);
		if (wesuwt)
			wetuwn wesuwt;
	}

	wetuwn 0;
}

/**
 * sbi_set_timew() - Pwogwam the timew fow next timew event.
 * @stime_vawue: The vawue aftew which next timew event shouwd fiwe.
 *
 * Wetuwn: None.
 */
void sbi_set_timew(uint64_t stime_vawue)
{
	__sbi_set_timew(stime_vawue);
}

/**
 * sbi_send_ipi() - Send an IPI to any hawt.
 * @cpu: Wogicaw id of the tawget CPU.
 */
void sbi_send_ipi(unsigned int cpu)
{
	__sbi_send_ipi(cpu);
}
EXPOWT_SYMBOW(sbi_send_ipi);

/**
 * sbi_wemote_fence_i() - Execute FENCE.I instwuction on given wemote hawts.
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 *
 * Wetuwn: 0 on success, appwopwiate winux ewwow code othewwise.
 */
int sbi_wemote_fence_i(const stwuct cpumask *cpu_mask)
{
	wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_FENCE_I,
			    cpu_mask, 0, 0, 0, 0);
}
EXPOWT_SYMBOW(sbi_wemote_fence_i);

/**
 * sbi_wemote_sfence_vma_asid() - Execute SFENCE.VMA instwuctions on given
 * wemote hawts fow a viwtuaw addwess wange bewonging to a specific ASID ow not.
 *
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 * @stawt: Stawt of the viwtuaw addwess
 * @size: Totaw size of the viwtuaw addwess wange.
 * @asid: The vawue of addwess space identifiew (ASID), ow FWUSH_TWB_NO_ASID
 * fow fwushing aww addwess spaces.
 *
 * Wetuwn: 0 on success, appwopwiate winux ewwow code othewwise.
 */
int sbi_wemote_sfence_vma_asid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong asid)
{
	if (asid == FWUSH_TWB_NO_ASID)
		wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA,
				    cpu_mask, stawt, size, 0, 0);
	ewse
		wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_SFENCE_VMA_ASID,
				    cpu_mask, stawt, size, asid, 0);
}
EXPOWT_SYMBOW(sbi_wemote_sfence_vma_asid);

/**
 * sbi_wemote_hfence_gvma() - Execute HFENCE.GVMA instwuctions on given wemote
 *			   hawts fow the specified guest physicaw addwess wange.
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 * @stawt: Stawt of the guest physicaw addwess
 * @size: Totaw size of the guest physicaw addwess wange.
 *
 * Wetuwn: None
 */
int sbi_wemote_hfence_gvma(const stwuct cpumask *cpu_mask,
			   unsigned wong stawt,
			   unsigned wong size)
{
	wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA,
			    cpu_mask, stawt, size, 0, 0);
}
EXPOWT_SYMBOW_GPW(sbi_wemote_hfence_gvma);

/**
 * sbi_wemote_hfence_gvma_vmid() - Execute HFENCE.GVMA instwuctions on given
 * wemote hawts fow a guest physicaw addwess wange bewonging to a specific VMID.
 *
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 * @stawt: Stawt of the guest physicaw addwess
 * @size: Totaw size of the guest physicaw addwess wange.
 * @vmid: The vawue of guest ID (VMID).
 *
 * Wetuwn: 0 if success, Ewwow othewwise.
 */
int sbi_wemote_hfence_gvma_vmid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong vmid)
{
	wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_HFENCE_GVMA_VMID,
			    cpu_mask, stawt, size, vmid, 0);
}
EXPOWT_SYMBOW(sbi_wemote_hfence_gvma_vmid);

/**
 * sbi_wemote_hfence_vvma() - Execute HFENCE.VVMA instwuctions on given wemote
 *			     hawts fow the cuwwent guest viwtuaw addwess wange.
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 * @stawt: Stawt of the cuwwent guest viwtuaw addwess
 * @size: Totaw size of the cuwwent guest viwtuaw addwess wange.
 *
 * Wetuwn: None
 */
int sbi_wemote_hfence_vvma(const stwuct cpumask *cpu_mask,
			   unsigned wong stawt,
			   unsigned wong size)
{
	wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA,
			    cpu_mask, stawt, size, 0, 0);
}
EXPOWT_SYMBOW(sbi_wemote_hfence_vvma);

/**
 * sbi_wemote_hfence_vvma_asid() - Execute HFENCE.VVMA instwuctions on given
 * wemote hawts fow cuwwent guest viwtuaw addwess wange bewonging to a specific
 * ASID.
 *
 * @cpu_mask: A cpu mask containing aww the tawget hawts.
 * @stawt: Stawt of the cuwwent guest viwtuaw addwess
 * @size: Totaw size of the cuwwent guest viwtuaw addwess wange.
 * @asid: The vawue of addwess space identifiew (ASID).
 *
 * Wetuwn: None
 */
int sbi_wemote_hfence_vvma_asid(const stwuct cpumask *cpu_mask,
				unsigned wong stawt,
				unsigned wong size,
				unsigned wong asid)
{
	wetuwn __sbi_wfence(SBI_EXT_WFENCE_WEMOTE_HFENCE_VVMA_ASID,
			    cpu_mask, stawt, size, asid, 0);
}
EXPOWT_SYMBOW(sbi_wemote_hfence_vvma_asid);

static void sbi_swst_weset(unsigned wong type, unsigned wong weason)
{
	sbi_ecaww(SBI_EXT_SWST, SBI_EXT_SWST_WESET, type, weason,
		  0, 0, 0, 0);
	pw_wawn("%s: type=0x%wx weason=0x%wx faiwed\n",
		__func__, type, weason);
}

static int sbi_swst_weboot(stwuct notifiew_bwock *this,
			   unsigned wong mode, void *cmd)
{
	sbi_swst_weset((mode == WEBOOT_WAWM || mode == WEBOOT_SOFT) ?
		       SBI_SWST_WESET_TYPE_WAWM_WEBOOT :
		       SBI_SWST_WESET_TYPE_COWD_WEBOOT,
		       SBI_SWST_WESET_WEASON_NONE);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock sbi_swst_weboot_nb;

static void sbi_swst_powew_off(void)
{
	sbi_swst_weset(SBI_SWST_WESET_TYPE_SHUTDOWN,
		       SBI_SWST_WESET_WEASON_NONE);
}

/**
 * sbi_pwobe_extension() - Check if an SBI extension ID is suppowted ow not.
 * @extid: The extension ID to be pwobed.
 *
 * Wetuwn: 1 ow an extension specific nonzewo vawue if yes, 0 othewwise.
 */
wong sbi_pwobe_extension(int extid)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_BASE, SBI_EXT_BASE_PWOBE_EXT, extid,
			0, 0, 0, 0, 0);
	if (!wet.ewwow)
		wetuwn wet.vawue;

	wetuwn 0;
}
EXPOWT_SYMBOW(sbi_pwobe_extension);

static wong __sbi_base_ecaww(int fid)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_BASE, fid, 0, 0, 0, 0, 0, 0);
	if (!wet.ewwow)
		wetuwn wet.vawue;
	ewse
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
}

static inwine wong sbi_get_spec_vewsion(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_SPEC_VEWSION);
}

static inwine wong sbi_get_fiwmwawe_id(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_IMP_ID);
}

static inwine wong sbi_get_fiwmwawe_vewsion(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_IMP_VEWSION);
}

wong sbi_get_mvendowid(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_MVENDOWID);
}
EXPOWT_SYMBOW_GPW(sbi_get_mvendowid);

wong sbi_get_mawchid(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_MAWCHID);
}
EXPOWT_SYMBOW_GPW(sbi_get_mawchid);

wong sbi_get_mimpid(void)
{
	wetuwn __sbi_base_ecaww(SBI_EXT_BASE_GET_MIMPID);
}
EXPOWT_SYMBOW_GPW(sbi_get_mimpid);

boow sbi_debug_consowe_avaiwabwe;

int sbi_debug_consowe_wwite(const chaw *bytes, unsigned int num_bytes)
{
	phys_addw_t base_addw;
	stwuct sbiwet wet;

	if (!sbi_debug_consowe_avaiwabwe)
		wetuwn -EOPNOTSUPP;

	if (is_vmawwoc_addw(bytes))
		base_addw = page_to_phys(vmawwoc_to_page(bytes)) +
			    offset_in_page(bytes);
	ewse
		base_addw = __pa(bytes);
	if (PAGE_SIZE < (offset_in_page(bytes) + num_bytes))
		num_bytes = PAGE_SIZE - offset_in_page(bytes);

	if (IS_ENABWED(CONFIG_32BIT))
		wet = sbi_ecaww(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOWE_WWITE,
				num_bytes, wowew_32_bits(base_addw),
				uppew_32_bits(base_addw), 0, 0, 0);
	ewse
		wet = sbi_ecaww(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOWE_WWITE,
				num_bytes, base_addw, 0, 0, 0, 0);

	if (wet.ewwow == SBI_EWW_FAIWUWE)
		wetuwn -EIO;
	wetuwn wet.ewwow ? sbi_eww_map_winux_ewwno(wet.ewwow) : wet.vawue;
}

int sbi_debug_consowe_wead(chaw *bytes, unsigned int num_bytes)
{
	phys_addw_t base_addw;
	stwuct sbiwet wet;

	if (!sbi_debug_consowe_avaiwabwe)
		wetuwn -EOPNOTSUPP;

	if (is_vmawwoc_addw(bytes))
		base_addw = page_to_phys(vmawwoc_to_page(bytes)) +
			    offset_in_page(bytes);
	ewse
		base_addw = __pa(bytes);
	if (PAGE_SIZE < (offset_in_page(bytes) + num_bytes))
		num_bytes = PAGE_SIZE - offset_in_page(bytes);

	if (IS_ENABWED(CONFIG_32BIT))
		wet = sbi_ecaww(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOWE_WEAD,
				num_bytes, wowew_32_bits(base_addw),
				uppew_32_bits(base_addw), 0, 0, 0);
	ewse
		wet = sbi_ecaww(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOWE_WEAD,
				num_bytes, base_addw, 0, 0, 0, 0);

	if (wet.ewwow == SBI_EWW_FAIWUWE)
		wetuwn -EIO;
	wetuwn wet.ewwow ? sbi_eww_map_winux_ewwno(wet.ewwow) : wet.vawue;
}

void __init sbi_init(void)
{
	int wet;

	sbi_set_powew_off();
	wet = sbi_get_spec_vewsion();
	if (wet > 0)
		sbi_spec_vewsion = wet;

	pw_info("SBI specification v%wu.%wu detected\n",
		sbi_majow_vewsion(), sbi_minow_vewsion());

	if (!sbi_spec_is_0_1()) {
		pw_info("SBI impwementation ID=0x%wx Vewsion=0x%wx\n",
			sbi_get_fiwmwawe_id(), sbi_get_fiwmwawe_vewsion());
		if (sbi_pwobe_extension(SBI_EXT_TIME)) {
			__sbi_set_timew = __sbi_set_timew_v02;
			pw_info("SBI TIME extension detected\n");
		} ewse {
			__sbi_set_timew = __sbi_set_timew_v01;
		}
		if (sbi_pwobe_extension(SBI_EXT_IPI)) {
			__sbi_send_ipi	= __sbi_send_ipi_v02;
			pw_info("SBI IPI extension detected\n");
		} ewse {
			__sbi_send_ipi	= __sbi_send_ipi_v01;
		}
		if (sbi_pwobe_extension(SBI_EXT_WFENCE)) {
			__sbi_wfence	= __sbi_wfence_v02;
			pw_info("SBI WFENCE extension detected\n");
		} ewse {
			__sbi_wfence	= __sbi_wfence_v01;
		}
		if ((sbi_spec_vewsion >= sbi_mk_vewsion(0, 3)) &&
		    sbi_pwobe_extension(SBI_EXT_SWST)) {
			pw_info("SBI SWST extension detected\n");
			pm_powew_off = sbi_swst_powew_off;
			sbi_swst_weboot_nb.notifiew_caww = sbi_swst_weboot;
			sbi_swst_weboot_nb.pwiowity = 192;
			wegistew_westawt_handwew(&sbi_swst_weboot_nb);
		}
		if ((sbi_spec_vewsion >= sbi_mk_vewsion(2, 0)) &&
		    (sbi_pwobe_extension(SBI_EXT_DBCN) > 0)) {
			pw_info("SBI DBCN extension detected\n");
			sbi_debug_consowe_avaiwabwe = twue;
		}
	} ewse {
		__sbi_set_timew = __sbi_set_timew_v01;
		__sbi_send_ipi	= __sbi_send_ipi_v01;
		__sbi_wfence	= __sbi_wfence_v01;
	}
}
