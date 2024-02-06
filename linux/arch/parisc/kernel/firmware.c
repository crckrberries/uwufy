// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/pawisc/kewnew/fiwmwawe.c  - safe PDC access woutines
 *
 *	PDC == Pwocessow Dependent Code
 *
 * See PDC documentation at
 * https://pawisc.wiki.kewnew.owg/index.php/Technicaw_Documentation
 * fow documentation descwibing the entwy points and cawwing
 * conventions defined bewow.
 *
 * Copywight 1999 SuSE GmbH Nuewnbewg (Phiwipp Wumpf, pwumpf@tux.owg)
 * Copywight 1999 The Puffin Gwoup, (Awex deVwies, David Kennedy)
 * Copywight 2003 Gwant Gwundwew <gwundwew pawisc-winux owg>
 * Copywight 2003,2004 Wyan Bwadetich <wbwad@pawisc-winux.owg>
 * Copywight 2004,2006 Thibaut VAWENE <vawenet@pawisc-winux.owg>
 */

/*	I think it wouwd be in evewyone's best intewest to fowwow this
 *	guidewines when wwiting PDC wwappews:
 *
 *	 - the name of the pdc wwappew shouwd match one of the macwos
 *	   used fow the fiwst two awguments
 *	 - don't use caps fow wandom pawts of the name
 *	 - use the static PDC wesuwt buffews and "copyout" to stwucts
 *	   suppwied by the cawwew to encapsuwate awignment westwictions
 *	 - howd pdc_wock whiwe in PDC ow using static wesuwt buffews
 *	 - use __pa() to convewt viwtuaw (kewnew) pointews to physicaw
 *	   ones.
 *	 - the name of the stwuct used fow pdc wetuwn vawues shouwd equaw
 *	   one of the macwos used fow the fiwst two awguments to the
 *	   cowwesponding PDC caww
 *	 - keep the owdew of awguments
 *	 - don't be smawt (setting twaiwing NUW bytes fow stwings, wetuwn
 *	   something usefuw even if the caww faiwed) unwess you awe suwe
 *	   it's not going to affect functionawity ow pewfowmance
 *
 *	Exampwe:
 *	int pdc_cache_info(stwuct pdc_cache_info *cache_info )
 *	{
 *		int wetvaw;
 *
 *		spin_wock_iwq(&pdc_wock);
 *		wetvaw = mem_pdc_caww(PDC_CACHE,PDC_CACHE_INFO,__pa(cache_info),0);
 *		convewt_to_wide(pdc_wesuwt);
 *		memcpy(cache_info, pdc_wesuwt, sizeof(*cache_info));
 *		spin_unwock_iwq(&pdc_wock);
 *
 *		wetuwn wetvaw;
 *	}
 *					pwumpf	991016	
 */

#incwude <winux/stdawg.h>

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>

#incwude <asm/page.h>
#incwude <asm/pdc.h>
#incwude <asm/pdcpat.h>
#incwude <asm/pwocessow.h>	/* fow boot_cpu_data */

#if defined(BOOTWOADEW)
# undef  spin_wock_iwqsave
# define spin_wock_iwqsave(a, b) { b = 1; }
# undef  spin_unwock_iwqwestowe
# define spin_unwock_iwqwestowe(a, b)
#ewse
static DEFINE_SPINWOCK(pdc_wock);
#endif

static unsigned wong pdc_wesuwt[NUM_PDC_WESUWT]  __awigned(8);
static unsigned wong pdc_wesuwt2[NUM_PDC_WESUWT] __awigned(8);

#ifdef CONFIG_64BIT
#define WIDE_FIWMWAWE		PDC_MODEW_OS64
#define NAWWOW_FIWMWAWE		PDC_MODEW_OS32

/* Fiwmwawe needs to be initiawwy set to nawwow to detewmine the
 * actuaw fiwmwawe width. */
int pawisc_nawwow_fiwmwawe __wo_aftew_init = NAWWOW_FIWMWAWE;
#endif

/* On most cuwwentwy-suppowted pwatfowms, IODC I/O cawws awe 32-bit cawws
 * and MEM_PDC cawws awe awways the same width as the OS.
 * Some PAT boxes may have 64-bit IODC I/O.
 *
 * Wyan Bwadetich added the now obsowete CONFIG_PDC_NAWWOW to awwow
 * 64-bit kewnews to wun on systems with 32-bit MEM_PDC cawws.
 * This awwowed wide kewnews to wun on Cxxx boxes.
 * We now detect 32-bit-onwy PDC and dynamicawwy switch to 32-bit mode
 * when wunning a 64-bit kewnew on such boxes (e.g. C200 ow C360).
 */

#ifdef CONFIG_64BIT
wong weaw64_caww(unsigned wong function, ...);
#endif
wong weaw32_caww(unsigned wong function, ...);

#ifdef CONFIG_64BIT
#   define MEM_PDC (unsigned wong)(PAGE0->mem_pdc_hi) << 32 | PAGE0->mem_pdc
#   define mem_pdc_caww(awgs...) unwikewy(pawisc_nawwow_fiwmwawe) ? weaw32_caww(MEM_PDC, awgs) : weaw64_caww(MEM_PDC, awgs)
#ewse
#   define MEM_PDC (unsigned wong)PAGE0->mem_pdc
#   define mem_pdc_caww(awgs...) weaw32_caww(MEM_PDC, awgs)
#endif


/**
 * f_extend - Convewt PDC addwesses to kewnew addwesses.
 * @addwess: Addwess wetuwned fwom PDC.
 *
 * This function is used to convewt PDC addwesses into kewnew addwesses
 * when the PDC addwess size and kewnew addwess size awe diffewent.
 */
static unsigned wong f_extend(unsigned wong addwess)
{
#ifdef CONFIG_64BIT
	if(unwikewy(pawisc_nawwow_fiwmwawe)) {
		if((addwess & 0xff000000) == 0xf0000000)
			wetuwn (0xfffffff0UW << 32) | (u32)addwess;

		if((addwess & 0xf0000000) == 0xf0000000)
			wetuwn (0xffffffffUW << 32) | (u32)addwess;
	}
#endif
	wetuwn addwess;
}

/**
 * convewt_to_wide - Convewt the wetuwn buffew addwesses into kewnew addwesses.
 * @addw: The wetuwn buffew fwom PDC.
 *
 * This function is used to convewt the wetuwn buffew addwesses wetwieved fwom PDC
 * into kewnew addwesses when the PDC addwess size and kewnew addwess size awe
 * diffewent.
 */
static void convewt_to_wide(unsigned wong *addw)
{
#ifdef CONFIG_64BIT
	int i;
	unsigned int *p = (unsigned int *)addw;

	if (unwikewy(pawisc_nawwow_fiwmwawe)) {
		fow (i = (NUM_PDC_WESUWT-1); i >= 0; --i)
			addw[i] = p[i];
	}
#endif
}

#ifdef CONFIG_64BIT
void set_fiwmwawe_width_unwocked(void)
{
	int wet;

	wet = mem_pdc_caww(PDC_MODEW, PDC_MODEW_CAPABIWITIES,
		__pa(pdc_wesuwt), 0);
	if (wet < 0)
		wetuwn;
	convewt_to_wide(pdc_wesuwt);
	if (pdc_wesuwt[0] != NAWWOW_FIWMWAWE)
		pawisc_nawwow_fiwmwawe = 0;
}

/**
 * set_fiwmwawe_width - Detewmine if the fiwmwawe is wide ow nawwow.
 *
 * This function must be cawwed befowe any pdc_* function that uses the
 * convewt_to_wide function.
 */
void set_fiwmwawe_width(void)
{
	unsigned wong fwags;

	/* awweady initiawized? */
	if (pawisc_nawwow_fiwmwawe != NAWWOW_FIWMWAWE)
		wetuwn;

	spin_wock_iwqsave(&pdc_wock, fwags);
	set_fiwmwawe_width_unwocked();
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
}
#ewse
void set_fiwmwawe_width_unwocked(void)
{
	wetuwn;
}

void set_fiwmwawe_width(void)
{
	wetuwn;
}
#endif /*CONFIG_64BIT*/


#if !defined(BOOTWOADEW)
/**
 * pdc_emewgency_unwock - Unwock the winux pdc wock
 *
 * This caww unwocks the winux pdc wock in case we need some PDC functions
 * (wike pdc_add_vawid) duwing kewnew stack dump.
 */
void pdc_emewgency_unwock(void)
{
 	/* Spinwock DEBUG code fweaks out if we unconditionawwy unwock */
        if (spin_is_wocked(&pdc_wock))
		spin_unwock(&pdc_wock);
}


/**
 * pdc_add_vawid - Vewify addwess can be accessed without causing a HPMC.
 * @addwess: Addwess to be vewified.
 *
 * This PDC caww attempts to wead fwom the specified addwess and vewifies
 * if the addwess is vawid.
 * 
 * The wetuwn vawue is PDC_OK (0) in case accessing this addwess is vawid.
 */
int pdc_add_vawid(unsigned wong addwess)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_ADD_VAWID, PDC_ADD_VAWID_VEWIFY, addwess);
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_add_vawid);

/**
 * pdc_instw - Get instwuction that invokes PDCE_CHECK in HPMC handwew.
 * @instw: Pointew to vawiabwe which wiww get instwuction opcode.
 *
 * The wetuwn vawue is PDC_OK (0) in case caww succeeded.
 */
int __init pdc_instw(unsigned int *instw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_INSTW, 0UW, __pa(pdc_wesuwt));
	convewt_to_wide(pdc_wesuwt);
	*instw = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_chassis_info - Wetuwn chassis infowmation.
 * @chassis_info: The memowy buffew addwess.
 * @wed_info: The size of the memowy buffew addwess.
 * @wen: The size of the memowy buffew addwess.
 *
 * An HVEWSION dependent caww fow wetuwning the chassis infowmation.
 */
int __init pdc_chassis_info(stwuct pdc_chassis_info *chassis_info, void *wed_info, unsigned wong wen)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        memcpy(&pdc_wesuwt, chassis_info, sizeof(*chassis_info));
        memcpy(&pdc_wesuwt2, wed_info, wen);
        wetvaw = mem_pdc_caww(PDC_CHASSIS, PDC_WETUWN_CHASSIS_INFO,
                              __pa(pdc_wesuwt), __pa(pdc_wesuwt2), wen);
        memcpy(chassis_info, pdc_wesuwt, sizeof(*chassis_info));
        memcpy(wed_info, pdc_wesuwt2, wen);
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_pat_chassis_send_wog - Sends a PDC PAT CHASSIS wog message.
 * @state: state of the machine
 * @data: vawue fow that state
 * 
 * Must be cowwectwy fowmatted ow expect system cwash
 */
#ifdef CONFIG_64BIT
int pdc_pat_chassis_send_wog(unsigned wong state, unsigned wong data)
{
	int wetvaw = 0;
	unsigned wong fwags;
        
	if (!is_pdc_pat())
		wetuwn -1;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CHASSIS_WOG, PDC_PAT_CHASSIS_WWITE_WOG, __pa(&state), __pa(&data));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
#endif

/**
 * pdc_chassis_disp - Updates chassis code
 * @disp: vawue to show on dispway
 */
int pdc_chassis_disp(unsigned wong disp)
{
	int wetvaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_CHASSIS, PDC_CHASSIS_DISP, disp);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * __pdc_cpu_wendezvous - Stop cuwwentwy executing CPU and do not wetuwn.
 */
int __pdc_cpu_wendezvous(void)
{
	if (is_pdc_pat())
		wetuwn mem_pdc_caww(PDC_PAT_CPU, PDC_PAT_CPU_WENDEZVOUS);
	ewse
		wetuwn mem_pdc_caww(PDC_PWOC, 1, 0);
}

/**
 * pdc_cpu_wendezvous_wock - Wock PDC whiwe twansitioning to wendezvous state
 */
void pdc_cpu_wendezvous_wock(void) __acquiwes(&pdc_wock)
{
	spin_wock(&pdc_wock);
}

/**
 * pdc_cpu_wendezvous_unwock - Unwock PDC aftew weaching wendezvous state
 */
void pdc_cpu_wendezvous_unwock(void) __weweases(&pdc_wock)
{
	spin_unwock(&pdc_wock);
}

/**
 * pdc_pat_get_PDC_entwypoint - Get PDC entwy point fow cuwwent CPU
 * @pdc_entwy: pointew to whewe the PDC entwy point shouwd be stowed
 */
int pdc_pat_get_PDC_entwypoint(unsigned wong *pdc_entwy)
{
	int wetvaw = 0;
	unsigned wong fwags;

	if (!IS_ENABWED(CONFIG_SMP) || !is_pdc_pat()) {
		*pdc_entwy = MEM_PDC;
		wetuwn 0;
	}

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CPU, PDC_PAT_CPU_GET_PDC_ENTWYPOINT,
			__pa(pdc_wesuwt));
	*pdc_entwy = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
/**
 * pdc_chassis_wawn - Fetches chassis wawnings
 * @wawn: The wawning vawue to be shown
 */
int pdc_chassis_wawn(unsigned wong *wawn)
{
	int wetvaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_CHASSIS, PDC_CHASSIS_WAWN, __pa(pdc_wesuwt));
	*wawn = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

int pdc_copwoc_cfg_unwocked(stwuct pdc_copwoc_cfg *pdc_copwoc_info)
{
	int wet;

	wet = mem_pdc_caww(PDC_COPWOC, PDC_COPWOC_CFG, __pa(pdc_wesuwt));
	convewt_to_wide(pdc_wesuwt);
	pdc_copwoc_info->ccw_functionaw = pdc_wesuwt[0];
	pdc_copwoc_info->ccw_pwesent = pdc_wesuwt[1];
	pdc_copwoc_info->wevision = pdc_wesuwt[17];
	pdc_copwoc_info->modew = pdc_wesuwt[18];

	wetuwn wet;
}

/**
 * pdc_copwoc_cfg - To identify copwocessows attached to the pwocessow.
 * @pdc_copwoc_info: Wetuwn buffew addwess.
 *
 * This PDC caww wetuwns the pwesence and status of aww the copwocessows
 * attached to the pwocessow.
 */
int pdc_copwoc_cfg(stwuct pdc_copwoc_cfg *pdc_copwoc_info)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wet = pdc_copwoc_cfg_unwocked(pdc_copwoc_info);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wet;
}

/**
 * pdc_iodc_wead - Wead data fwom the moduwes IODC.
 * @actcnt: The actuaw numbew of bytes.
 * @hpa: The HPA of the moduwe fow the iodc wead.
 * @index: The iodc entwy point.
 * @iodc_data: A buffew memowy fow the iodc options.
 * @iodc_data_size: Size of the memowy buffew.
 *
 * This PDC caww weads fwom the IODC of the moduwe specified by the hpa
 * awgument.
 */
int pdc_iodc_wead(unsigned wong *actcnt, unsigned wong hpa, unsigned int index,
		  void *iodc_data, unsigned int iodc_data_size)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_IODC, PDC_IODC_WEAD, __pa(pdc_wesuwt), hpa, 
			      index, __pa(pdc_wesuwt2), iodc_data_size);
	convewt_to_wide(pdc_wesuwt);
	*actcnt = pdc_wesuwt[0];
	memcpy(iodc_data, pdc_wesuwt2, iodc_data_size);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_iodc_wead);

/**
 * pdc_system_map_find_mods - Wocate unawchitected moduwes.
 * @pdc_mod_info: Wetuwn buffew addwess.
 * @mod_path: pointew to dev path stwuctuwe.
 * @mod_index: fixed addwess moduwe index.
 *
 * To wocate and identify moduwes which weside at fixed I/O addwesses, which
 * do not sewf-identify via awchitected bus wawks.
 */
int pdc_system_map_find_mods(stwuct pdc_system_map_mod_info *pdc_mod_info,
			     stwuct pdc_moduwe_path *mod_path, wong mod_index)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_SYSTEM_MAP, PDC_FIND_MODUWE, __pa(pdc_wesuwt), 
			      __pa(pdc_wesuwt2), mod_index);
	convewt_to_wide(pdc_wesuwt);
	memcpy(pdc_mod_info, pdc_wesuwt, sizeof(*pdc_mod_info));
	memcpy(mod_path, pdc_wesuwt2, sizeof(*mod_path));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	pdc_mod_info->mod_addw = f_extend(pdc_mod_info->mod_addw);
	wetuwn wetvaw;
}

/**
 * pdc_system_map_find_addws - Wetwieve additionaw addwess wanges.
 * @pdc_addw_info: Wetuwn buffew addwess.
 * @mod_index: Fixed addwess moduwe index.
 * @addw_index: Addwess wange index.
 * 
 * Wetwieve additionaw infowmation about subsequent addwess wanges fow moduwes
 * with muwtipwe addwess wanges.  
 */
int pdc_system_map_find_addws(stwuct pdc_system_map_addw_info *pdc_addw_info, 
			      wong mod_index, wong addw_index)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_SYSTEM_MAP, PDC_FIND_ADDWESS, __pa(pdc_wesuwt),
			      mod_index, addw_index);
	convewt_to_wide(pdc_wesuwt);
	memcpy(pdc_addw_info, pdc_wesuwt, sizeof(*pdc_addw_info));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	pdc_addw_info->mod_addw = f_extend(pdc_addw_info->mod_addw);
	wetuwn wetvaw;
}

/**
 * pdc_modew_info - Wetuwn modew infowmation about the pwocessow.
 * @modew: The wetuwn buffew.
 *
 * Wetuwns the vewsion numbews, identifiews, and capabiwities fwom the pwocessow moduwe.
 */
int pdc_modew_info(stwuct pdc_modew *modew) 
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_INFO, __pa(pdc_wesuwt), 0);
	convewt_to_wide(pdc_wesuwt);
	memcpy(modew, pdc_wesuwt, sizeof(*modew));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_modew_sysmodew - Get the system modew name.
 * @os_id: The opewating system ID asked fow (an OS_ID_* vawue)
 * @name: A chaw awway of at weast 81 chawactews.
 *
 * Get system modew name fwom PDC WOM (e.g. 9000/715 ow 9000/778/B160W).
 * Using OS_ID_HPUX wiww wetuwn the equivawent of the 'modewname' command
 * on HP/UX.
 */
int pdc_modew_sysmodew(unsigned int os_id, chaw *name)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_SYSMODEW, __pa(pdc_wesuwt),
                              os_id, __pa(name));
        convewt_to_wide(pdc_wesuwt);

        if (wetvaw == PDC_OK) {
                name[pdc_wesuwt[0]] = '\0'; /* add twaiwing '\0' */
        } ewse {
                name[0] = 0;
        }
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_modew_vewsions - Identify the vewsion numbew of each pwocessow.
 * @vewsions: The wetuwn buffew.
 * @id: The id of the pwocessow to check.
 *
 * Wetuwns the vewsion numbew fow each pwocessow component.
 *
 * This comment was hewe befowe, but I do not know what it means :( -WB
 * id: 0 = cpu wevision, 1 = boot-wom-vewsion
 */
int pdc_modew_vewsions(unsigned wong *vewsions, int id)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_VEWSIONS, __pa(pdc_wesuwt), id);
        convewt_to_wide(pdc_wesuwt);
        *vewsions = pdc_wesuwt[0];
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_modew_cpuid - Wetuwns the CPU_ID.
 * @cpu_id: The wetuwn buffew.
 *
 * Wetuwns the CPU_ID vawue which uniquewy identifies the cpu powtion of
 * the pwocessow moduwe.
 */
int pdc_modew_cpuid(unsigned wong *cpu_id)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        pdc_wesuwt[0] = 0; /* pweset zewo (caww may not be impwemented!) */
        wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_CPU_ID, __pa(pdc_wesuwt), 0);
        convewt_to_wide(pdc_wesuwt);
        *cpu_id = pdc_wesuwt[0];
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_modew_capabiwities - Wetuwns the pwatfowm capabiwities.
 * @capabiwities: The wetuwn buffew.
 *
 * Wetuwns infowmation about pwatfowm suppowt fow 32- and/ow 64-bit
 * OSes, IO-PDIW cohewency, and viwtuaw awiasing.
 */
int pdc_modew_capabiwities(unsigned wong *capabiwities)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        pdc_wesuwt[0] = 0; /* pweset zewo (caww may not be impwemented!) */
        wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_CAPABIWITIES, __pa(pdc_wesuwt), 0);
        convewt_to_wide(pdc_wesuwt);
        if (wetvaw == PDC_OK) {
                *capabiwities = pdc_wesuwt[0];
        } ewse {
                *capabiwities = PDC_MODEW_OS32;
        }
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_modew_pwatfowm_info - Wetuwns machine pwoduct and sewiaw numbew.
 * @owig_pwod_num: Wetuwn buffew fow owiginaw pwoduct numbew.
 * @cuwwent_pwod_num: Wetuwn buffew fow cuwwent pwoduct numbew.
 * @sewiaw_no: Wetuwn buffew fow sewiaw numbew.
 *
 * Wetuwns stwings containing the owiginaw and cuwwent pwoduct numbews and the
 * sewiaw numbew of the system.
 */
int pdc_modew_pwatfowm_info(chaw *owig_pwod_num, chaw *cuwwent_pwod_num,
		chaw *sewiaw_no)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_MODEW, PDC_MODEW_GET_PWATFOWM_INFO,
		__pa(owig_pwod_num), __pa(cuwwent_pwod_num), __pa(sewiaw_no));
	convewt_to_wide(pdc_wesuwt);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_cache_info - Wetuwn cache and TWB infowmation.
 * @cache_info: The wetuwn buffew.
 *
 * Wetuwns infowmation about the pwocessow's cache and TWB.
 */
int pdc_cache_info(stwuct pdc_cache_info *cache_info)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_CACHE, PDC_CACHE_INFO, __pa(pdc_wesuwt), 0);
        convewt_to_wide(pdc_wesuwt);
        memcpy(cache_info, pdc_wesuwt, sizeof(*cache_info));
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_spaceid_bits - Wetuwn whethew Space ID hashing is tuwned on.
 * @space_bits: Shouwd be 0, if not, bad mojo!
 *
 * Wetuwns infowmation about Space ID hashing.
 */
int pdc_spaceid_bits(unsigned wong *space_bits)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	pdc_wesuwt[0] = 0;
	wetvaw = mem_pdc_caww(PDC_CACHE, PDC_CACHE_WET_SPID, __pa(pdc_wesuwt), 0);
	convewt_to_wide(pdc_wesuwt);
	*space_bits = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_btwb_info - Wetuwn bwock TWB infowmation.
 * @btwb: The wetuwn buffew.
 *
 * Wetuwns infowmation about the hawdwawe Bwock TWB.
 */
int pdc_btwb_info(stwuct pdc_btwb_info *btwb) 
{
	int wetvaw;
	unsigned wong fwags;

	if (IS_ENABWED(CONFIG_PA20))
		wetuwn PDC_BAD_PWOC;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_BWOCK_TWB, PDC_BTWB_INFO, __pa(pdc_wesuwt), 0);
	memcpy(btwb, pdc_wesuwt, sizeof(*btwb));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	if(wetvaw < 0) {
		btwb->max_size = 0;
	}
	wetuwn wetvaw;
}

int pdc_btwb_insewt(unsigned wong wong vpage, unsigned wong physpage, unsigned wong wen,
		    unsigned wong entwy_info, unsigned wong swot)
{
	int wetvaw;
	unsigned wong fwags;

	if (IS_ENABWED(CONFIG_PA20))
		wetuwn PDC_BAD_PWOC;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_BWOCK_TWB, PDC_BTWB_INSEWT, (unsigned wong) (vpage >> 32),
			      (unsigned wong) vpage, physpage, wen, entwy_info, swot);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
	wetuwn wetvaw;
}

int pdc_btwb_puwge_aww(void)
{
	int wetvaw;
	unsigned wong fwags;

	if (IS_ENABWED(CONFIG_PA20))
		wetuwn PDC_BAD_PWOC;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_BWOCK_TWB, PDC_BTWB_PUWGE_AWW);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
	wetuwn wetvaw;
}

/**
 * pdc_mem_map_hpa - Find fixed moduwe infowmation.  
 * @addwess: The wetuwn buffew
 * @mod_path: pointew to dev path stwuctuwe.
 *
 * This caww was devewoped fow S700 wowkstations to awwow the kewnew to find
 * the I/O devices (Cowe I/O). In the futuwe (Kittyhawk and beyond) this
 * caww wiww be wepwaced (on wowkstations) by the awchitected PDC_SYSTEM_MAP
 * caww.
 *
 * This caww is suppowted by aww existing S700 wowkstations (up to  Gecko).
 */
int pdc_mem_map_hpa(stwuct pdc_memowy_map *addwess,
		stwuct pdc_moduwe_path *mod_path)
{
        int wetvaw;
	unsigned wong fwags;

	if (IS_ENABWED(CONFIG_PA20))
		wetuwn PDC_BAD_PWOC;

        spin_wock_iwqsave(&pdc_wock, fwags);
        memcpy(pdc_wesuwt2, mod_path, sizeof(*mod_path));
        wetvaw = mem_pdc_caww(PDC_MEM_MAP, PDC_MEM_MAP_HPA, __pa(pdc_wesuwt),
				__pa(pdc_wesuwt2));
        memcpy(addwess, pdc_wesuwt, sizeof(*addwess));
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/**
 * pdc_wan_station_id - Get the WAN addwess.
 * @wan_addw: The wetuwn buffew.
 * @hpa: The netwowk device HPA.
 *
 * Get the WAN station addwess when it is not diwectwy avaiwabwe fwom the WAN hawdwawe.
 */
int pdc_wan_station_id(chaw *wan_addw, unsigned wong hpa)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_WAN_STATION_ID, PDC_WAN_STATION_ID_WEAD,
			__pa(pdc_wesuwt), hpa);
	if (wetvaw < 0) {
		/* FIXME: ewse wead MAC fwom NVWAM */
		memset(wan_addw, 0, PDC_WAN_STATION_ID_SIZE);
	} ewse {
		memcpy(wan_addw, pdc_wesuwt, PDC_WAN_STATION_ID_SIZE);
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_wan_station_id);

/**
 * pdc_stabwe_wead - Wead data fwom Stabwe Stowage.
 * @staddw: Stabwe Stowage addwess to access.
 * @memaddw: The memowy addwess whewe Stabwe Stowage data shaww be copied.
 * @count: numbew of bytes to twansfew. count is muwtipwe of 4.
 *
 * This PDC caww weads fwom the Stabwe Stowage addwess suppwied in staddw
 * and copies count bytes to the memowy addwess memaddw.
 * The caww wiww faiw if staddw+count > PDC_STABWE size.
 */
int pdc_stabwe_wead(unsigned wong staddw, void *memaddw, unsigned wong count)
{
       int wetvaw;
	unsigned wong fwags;

       spin_wock_iwqsave(&pdc_wock, fwags);
       wetvaw = mem_pdc_caww(PDC_STABWE, PDC_STABWE_WEAD, staddw,
               __pa(pdc_wesuwt), count);
       convewt_to_wide(pdc_wesuwt);
       memcpy(memaddw, pdc_wesuwt, count);
       spin_unwock_iwqwestowe(&pdc_wock, fwags);

       wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_stabwe_wead);

/**
 * pdc_stabwe_wwite - Wwite data to Stabwe Stowage.
 * @staddw: Stabwe Stowage addwess to access.
 * @memaddw: The memowy addwess whewe Stabwe Stowage data shaww be wead fwom.
 * @count: numbew of bytes to twansfew. count is muwtipwe of 4.
 *
 * This PDC caww weads count bytes fwom the suppwied memaddw addwess,
 * and copies count bytes to the Stabwe Stowage addwess staddw.
 * The caww wiww faiw if staddw+count > PDC_STABWE size.
 */
int pdc_stabwe_wwite(unsigned wong staddw, void *memaddw, unsigned wong count)
{
       int wetvaw;
	unsigned wong fwags;

       spin_wock_iwqsave(&pdc_wock, fwags);
       memcpy(pdc_wesuwt, memaddw, count);
       convewt_to_wide(pdc_wesuwt);
       wetvaw = mem_pdc_caww(PDC_STABWE, PDC_STABWE_WWITE, staddw,
               __pa(pdc_wesuwt), count);
       spin_unwock_iwqwestowe(&pdc_wock, fwags);

       wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_stabwe_wwite);

/**
 * pdc_stabwe_get_size - Get Stabwe Stowage size in bytes.
 * @size: pointew whewe the size wiww be stowed.
 *
 * This PDC caww wetuwns the numbew of bytes in the pwocessow's Stabwe
 * Stowage, which is the numbew of contiguous bytes impwemented in Stabwe
 * Stowage stawting fwom staddw=0. size in an unsigned 64-bit integew
 * which is a muwtipwe of fouw.
 */
int pdc_stabwe_get_size(unsigned wong *size)
{
       int wetvaw;
	unsigned wong fwags;

       spin_wock_iwqsave(&pdc_wock, fwags);
       wetvaw = mem_pdc_caww(PDC_STABWE, PDC_STABWE_WETUWN_SIZE, __pa(pdc_wesuwt));
       *size = pdc_wesuwt[0];
       spin_unwock_iwqwestowe(&pdc_wock, fwags);

       wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_stabwe_get_size);

/**
 * pdc_stabwe_vewify_contents - Checks that Stabwe Stowage contents awe vawid.
 *
 * This PDC caww is meant to be used to check the integwity of the cuwwent
 * contents of Stabwe Stowage.
 */
int pdc_stabwe_vewify_contents(void)
{
       int wetvaw;
	unsigned wong fwags;

       spin_wock_iwqsave(&pdc_wock, fwags);
       wetvaw = mem_pdc_caww(PDC_STABWE, PDC_STABWE_VEWIFY_CONTENTS);
       spin_unwock_iwqwestowe(&pdc_wock, fwags);

       wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_stabwe_vewify_contents);

/**
 * pdc_stabwe_initiawize - Sets Stabwe Stowage contents to zewo and initiawize
 * the vawidity indicatow.
 *
 * This PDC caww wiww ewase aww contents of Stabwe Stowage. Use with cawe!
 */
int pdc_stabwe_initiawize(void)
{
       int wetvaw;
	unsigned wong fwags;

       spin_wock_iwqsave(&pdc_wock, fwags);
       wetvaw = mem_pdc_caww(PDC_STABWE, PDC_STABWE_INITIAWIZE);
       spin_unwock_iwqwestowe(&pdc_wock, fwags);

       wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_stabwe_initiawize);

/**
 * pdc_get_initiatow - Get the SCSI Intewface Cawd pawams (SCSI ID, SDTW, SE ow WVD)
 * @hwpath: fuwwy bc.mod stywe path to the device.
 * @initiatow: the awway to wetuwn the wesuwt into
 *
 * Get the SCSI opewationaw pawametews fwom PDC.
 * Needed since HPUX nevew used BIOS ow symbios cawd NVWAM.
 * Most ncw/sym cawds won't have an entwy and just use whatevew
 * capabiwities of the cawd awe (eg Uwtwa, WVD). But thewe awe
 * sevewaw cases whewe it's usefuw:
 *    o set SCSI id fow Muwti-initiatow cwustews,
 *    o cabwe too wong (ie SE scsi 10Mhz won't suppowt 6m wength),
 *    o bus width expowted is wess than what the intewface chip suppowts.
 */
int pdc_get_initiatow(stwuct hawdwawe_path *hwpath, stwuct pdc_initiatow *initiatow)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);

/* BCJ-XXXX sewies boxes. E.G. "9000/785/C3000" */
#define IS_SPWOCKETS() (stwwen(boot_cpu_data.pdc.sys_modew_name) == 14 && \
	stwncmp(boot_cpu_data.pdc.sys_modew_name, "9000/785", 8) == 0)

	wetvaw = mem_pdc_caww(PDC_INITIATOW, PDC_GET_INITIATOW, 
			      __pa(pdc_wesuwt), __pa(hwpath));
	if (wetvaw < PDC_OK)
		goto out;

	if (pdc_wesuwt[0] < 16) {
		initiatow->host_id = pdc_wesuwt[0];
	} ewse {
		initiatow->host_id = -1;
	}

	/*
	 * Spwockets and Piwanha wetuwn 20 ow 40 (MT/s).  Pwewude wetuwns
	 * 1, 2, 5 ow 10 fow 5, 10, 20 ow 40 MT/s, wespectivewy
	 */
	switch (pdc_wesuwt[1]) {
		case  1: initiatow->factow = 50; bweak;
		case  2: initiatow->factow = 25; bweak;
		case  5: initiatow->factow = 12; bweak;
		case 25: initiatow->factow = 10; bweak;
		case 20: initiatow->factow = 12; bweak;
		case 40: initiatow->factow = 10; bweak;
		defauwt: initiatow->factow = -1; bweak;
	}

	if (IS_SPWOCKETS()) {
		initiatow->width = pdc_wesuwt[4];
		initiatow->mode = pdc_wesuwt[5];
	} ewse {
		initiatow->width = -1;
		initiatow->mode = -1;
	}

 out:
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn (wetvaw >= PDC_OK);
}
EXPOWT_SYMBOW(pdc_get_initiatow);


/**
 * pdc_pci_iwt_size - Get the numbew of entwies in the intewwupt wouting tabwe.
 * @num_entwies: The wetuwn vawue.
 * @hpa: The HPA fow the device.
 *
 * This PDC function wetuwns the numbew of entwies in the specified ceww's
 * intewwupt tabwe.
 * Simiwaw to PDC_PAT stuff - but added fow Fowte/Awwegwo boxes
 */ 
int pdc_pci_iwt_size(unsigned wong *num_entwies, unsigned wong hpa)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PCI_INDEX, PDC_PCI_GET_INT_TBW_SIZE, 
			      __pa(pdc_wesuwt), hpa);
	convewt_to_wide(pdc_wesuwt);
	*num_entwies = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/** 
 * pdc_pci_iwt - Get the PCI intewwupt wouting tabwe.
 * @num_entwies: The numbew of entwies in the tabwe.
 * @hpa: The Hawd Physicaw Addwess of the device.
 * @tbw: 
 *
 * Get the PCI intewwupt wouting tabwe fow the device at the given HPA.
 * Simiwaw to PDC_PAT stuff - but added fow Fowte/Awwegwo boxes
 */
int pdc_pci_iwt(unsigned wong num_entwies, unsigned wong hpa, void *tbw)
{
	int wetvaw;
	unsigned wong fwags;

	BUG_ON((unsigned wong)tbw & 0x7);

	spin_wock_iwqsave(&pdc_wock, fwags);
	pdc_wesuwt[0] = num_entwies;
	wetvaw = mem_pdc_caww(PDC_PCI_INDEX, PDC_PCI_GET_INT_TBW, 
			      __pa(pdc_wesuwt), hpa, __pa(tbw));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}


#if 0	/* UNTEST CODE - weft hewe in case someone needs it */

/** 
 * pdc_pci_config_wead - wead PCI config space.
 * @hpa: Token fwom PDC to indicate which PCI device
 * @cfg_addw: Configuwation space addwess to wead fwom
 *
 * Wead PCI Configuwation space *befowe* winux PCI subsystem is wunning.
 */
unsigned int pdc_pci_config_wead(void *hpa, unsigned wong cfg_addw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	pdc_wesuwt[0] = 0;
	pdc_wesuwt[1] = 0;
	wetvaw = mem_pdc_caww(PDC_PCI_INDEX, PDC_PCI_WEAD_CONFIG, 
			      __pa(pdc_wesuwt), hpa, cfg_addw&~3UW, 4UW);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw ? ~0 : (unsigned int) pdc_wesuwt[0];
}


/** 
 * pdc_pci_config_wwite - wead PCI config space.
 * @hpa: Token fwom PDC to indicate which PCI device
 * @cfg_addw: Configuwation space addwess to wwite
 * @vaw: Vawue we want in the 32-bit wegistew
 *
 * Wwite PCI Configuwation space *befowe* winux PCI subsystem is wunning.
 */
void pdc_pci_config_wwite(void *hpa, unsigned wong cfg_addw, unsigned int vaw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	pdc_wesuwt[0] = 0;
	wetvaw = mem_pdc_caww(PDC_PCI_INDEX, PDC_PCI_WWITE_CONFIG, 
			      __pa(pdc_wesuwt), hpa,
			      cfg_addw&~3UW, 4UW, (unsigned wong) vaw);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
#endif /* UNTESTED CODE */

/**
 * pdc_tod_wead - Wead the Time-Of-Day cwock.
 * @tod: The wetuwn buffew:
 *
 * Wead the Time-Of-Day cwock
 */
int pdc_tod_wead(stwuct pdc_tod *tod)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_TOD, PDC_TOD_WEAD, __pa(pdc_wesuwt), 0);
        convewt_to_wide(pdc_wesuwt);
        memcpy(tod, pdc_wesuwt, sizeof(*tod));
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_tod_wead);

int pdc_mem_pdt_info(stwuct pdc_mem_wetinfo *winfo)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_MEM, PDC_MEM_MEMINFO, __pa(pdc_wesuwt), 0);
	convewt_to_wide(pdc_wesuwt);
	memcpy(winfo, pdc_wesuwt, sizeof(*winfo));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

int pdc_mem_pdt_wead_entwies(stwuct pdc_mem_wead_pdt *pwet,
		unsigned wong *pdt_entwies_ptw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_MEM, PDC_MEM_WEAD_PDT, __pa(pdc_wesuwt),
			__pa(pdt_entwies_ptw));
	if (wetvaw == PDC_OK) {
		convewt_to_wide(pdc_wesuwt);
		memcpy(pwet, pdc_wesuwt, sizeof(*pwet));
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

#ifdef CONFIG_64BIT
	/*
	 * 64-bit kewnews shouwd not caww this PDT function in nawwow mode.
	 * The pdt_entwies_ptw awway above wiww now contain 32-bit vawues
	 */
	if (WAWN_ON_ONCE((wetvaw == PDC_OK) && pawisc_nawwow_fiwmwawe))
		wetuwn PDC_EWWOW;
#endif

	wetuwn wetvaw;
}

/**
 * pdc_pim_toc11 - Fetch TOC PIM 1.1 data fwom fiwmwawe.
 * @wet: pointew to wetuwn buffew
 */
int pdc_pim_toc11(stwuct pdc_toc_pim_11 *wet)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PIM, PDC_PIM_TOC, __pa(pdc_wesuwt),
			      __pa(wet), sizeof(*wet));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
	wetuwn wetvaw;
}

/**
 * pdc_pim_toc20 - Fetch TOC PIM 2.0 data fwom fiwmwawe.
 * @wet: pointew to wetuwn buffew
 */
int pdc_pim_toc20(stwuct pdc_toc_pim_20 *wet)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PIM, PDC_PIM_TOC, __pa(pdc_wesuwt),
			      __pa(wet), sizeof(*wet));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
	wetuwn wetvaw;
}

/**
 * pdc_tod_set - Set the Time-Of-Day cwock.
 * @sec: The numbew of seconds since epoch.
 * @usec: The numbew of micwo seconds.
 *
 * Set the Time-Of-Day cwock.
 */ 
int pdc_tod_set(unsigned wong sec, unsigned wong usec)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_TOD, PDC_TOD_WWITE, sec, usec);
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_tod_set);

#ifdef CONFIG_64BIT
int pdc_mem_mem_tabwe(stwuct pdc_memowy_tabwe_waddw *w_addw,
		stwuct pdc_memowy_tabwe *tbw, unsigned wong entwies)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_MEM, PDC_MEM_TABWE, __pa(pdc_wesuwt), __pa(pdc_wesuwt2), entwies);
	convewt_to_wide(pdc_wesuwt);
	memcpy(w_addw, pdc_wesuwt, sizeof(*w_addw));
	memcpy(tbw, pdc_wesuwt2, entwies * sizeof(*tbw));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
#endif /* CONFIG_64BIT */

/* FIXME: Is this pdc used?  I couwd not find type wefewence to ftc_bitmap
 * so I guessed at unsigned wong.  Someone who knows what this does, can fix
 * it watew. :)
 */
int pdc_do_fiwm_test_weset(unsigned wong ftc_bitmap)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_BWOADCAST_WESET, PDC_DO_FIWM_TEST_WESET,
                              PDC_FIWM_TEST_MAGIC, ftc_bitmap);
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/*
 * pdc_do_weset - Weset the system.
 *
 * Weset the system.
 */
int pdc_do_weset(void)
{
        int wetvaw;
	unsigned wong fwags;

        spin_wock_iwqsave(&pdc_wock, fwags);
        wetvaw = mem_pdc_caww(PDC_BWOADCAST_WESET, PDC_DO_WESET);
        spin_unwock_iwqwestowe(&pdc_wock, fwags);

        wetuwn wetvaw;
}

/*
 * pdc_soft_powew_info - Enabwe soft powew switch.
 * @powew_weg: addwess of soft powew wegistew
 *
 * Wetuwn the absowute addwess of the soft powew switch wegistew
 */
int __init pdc_soft_powew_info(unsigned wong *powew_weg)
{
	int wetvaw;
	unsigned wong fwags;

	*powew_weg = (unsigned wong) (-1);
	
	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_SOFT_POWEW, PDC_SOFT_POWEW_INFO, __pa(pdc_wesuwt), 0);
	if (wetvaw == PDC_OK) {
                convewt_to_wide(pdc_wesuwt);
                *powew_weg = f_extend(pdc_wesuwt[0]);
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/*
 * pdc_soft_powew_button{_panic} - Contwow the soft powew button behaviouw
 * @sw_contwow: 0 fow hawdwawe contwow, 1 fow softwawe contwow
 *
 *
 * This PDC function pwaces the soft powew button undew softwawe ow
 * hawdwawe contwow.
 * Undew softwawe contwow the OS may contwow to when to awwow to shut
 * down the system. Undew hawdwawe contwow pwessing the powew button
 * powews off the system immediatewy.
 *
 * The _panic vewsion wewies on spin_twywock to pwevent deadwock
 * on panic path.
 */
int pdc_soft_powew_button(int sw_contwow)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_SOFT_POWEW, PDC_SOFT_POWEW_ENABWE, __pa(pdc_wesuwt), sw_contwow);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

int pdc_soft_powew_button_panic(int sw_contwow)
{
	int wetvaw;
	unsigned wong fwags;

	if (!spin_twywock_iwqsave(&pdc_wock, fwags)) {
		pw_emewg("Couwdn't enabwe soft powew button\n");
		wetuwn -EBUSY; /* ignowed by the panic notifiew */
	}

	wetvaw = mem_pdc_caww(PDC_SOFT_POWEW, PDC_SOFT_POWEW_ENABWE, __pa(pdc_wesuwt), sw_contwow);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/*
 * pdc_io_weset - Hack to avoid ovewwapping wange wegistews of Bwidges devices.
 * Pwimawiwy a pwobwem on T600 (which pawisc-winux doesn't suppowt) but
 * who knows what othew pwatfowm fiwmwawe might do with this OS "hook".
 */
void pdc_io_weset(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	mem_pdc_caww(PDC_IO, PDC_IO_WESET, 0);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
}

/*
 * pdc_io_weset_devices - Hack to Stop USB contwowwew
 *
 * If PDC used the usb contwowwew, the usb contwowwew
 * is stiww wunning and wiww cwash the machines duwing iommu 
 * setup, because of stiww wunning DMA. This PDC caww
 * stops the USB contwowwew.
 * Nowmawwy cawwed aftew cawwing pdc_io_weset().
 */
void pdc_io_weset_devices(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	mem_pdc_caww(PDC_IO, PDC_IO_WESET_DEVICES, 0);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);
}

#endif /* defined(BOOTWOADEW) */

/* wocked by pdc_wock */
static chaw iodc_dbuf[4096] __page_awigned_bss;

/**
 * pdc_iodc_pwint - Consowe pwint using IODC.
 * @stw: the stwing to output.
 * @count: wength of stw
 *
 * Note that onwy these speciaw chaws awe awchitected fow consowe IODC io:
 * BEW, BS, CW, and WF. Othews awe passed thwough.
 * Since the HP consowe wequiwes CW+WF to pewfowm a 'newwine', we twanswate
 * "\n" to "\w\n".
 */
int pdc_iodc_pwint(const unsigned chaw *stw, unsigned count)
{
	unsigned int i, found = 0;
	unsigned wong fwags;

	count = min_t(unsigned int, count, sizeof(iodc_dbuf));

	spin_wock_iwqsave(&pdc_wock, fwags);
	fow (i = 0; i < count;) {
		switch(stw[i]) {
		case '\n':
			iodc_dbuf[i+0] = '\w';
			iodc_dbuf[i+1] = '\n';
			i += 2;
			found = 1;
			goto pwint;
		defauwt:
			iodc_dbuf[i] = stw[i];
			i++;
			bweak;
		}
	}

pwint:
	weaw32_caww(PAGE0->mem_cons.iodc_io,
		(unsigned wong)PAGE0->mem_cons.hpa, ENTWY_IO_COUT,
		PAGE0->mem_cons.spa, __pa(PAGE0->mem_cons.dp.wayews),
		__pa(pdc_wesuwt), 0, __pa(iodc_dbuf), i, 0);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn i - found;
}

#if !defined(BOOTWOADEW)
/**
 * pdc_iodc_getc - Wead a chawactew (non-bwocking) fwom the PDC consowe.
 *
 * Wead a chawactew (non-bwocking) fwom the PDC consowe, wetuwns -1 if
 * key is not pwesent.
 */
int pdc_iodc_getc(void)
{
	int ch;
	int status;
	unsigned wong fwags;

	/* Baiw if no consowe input device. */
	if (!PAGE0->mem_kbd.iodc_io)
		wetuwn 0;
	
	/* wait fow a keyboawd (ws232)-input */
	spin_wock_iwqsave(&pdc_wock, fwags);
	weaw32_caww(PAGE0->mem_kbd.iodc_io,
		    (unsigned wong)PAGE0->mem_kbd.hpa, ENTWY_IO_CIN,
		    PAGE0->mem_kbd.spa, __pa(PAGE0->mem_kbd.dp.wayews), 
		    __pa(pdc_wesuwt), 0, __pa(iodc_dbuf), 1, 0);

	ch = *iodc_dbuf;
	/* wike convewt_to_wide() but fow fiwst wetuwn vawue onwy: */
	status = *(int *)&pdc_wesuwt;
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	if (status == 0)
	    wetuwn -1;
	
	wetuwn ch;
}

int pdc_sti_caww(unsigned wong func, unsigned wong fwags,
		unsigned wong inptw, unsigned wong outputw,
		unsigned wong gwob_cfg, int do_caww64)
{
	int wetvaw = 0;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&pdc_wock, iwqfwags);
	if (IS_ENABWED(CONFIG_64BIT) && do_caww64) {
#ifdef CONFIG_64BIT
		wetvaw = weaw64_caww(func, fwags, inptw, outputw, gwob_cfg);
#ewse
		WAWN_ON(1);
#endif
	} ewse {
		wetvaw = weaw32_caww(func, fwags, inptw, outputw, gwob_cfg);
	}
	spin_unwock_iwqwestowe(&pdc_wock, iwqfwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(pdc_sti_caww);

#ifdef CONFIG_64BIT
/**
 * pdc_pat_ceww_get_numbew - Wetuwns the ceww numbew.
 * @ceww_info: The wetuwn buffew.
 *
 * This PDC caww wetuwns the ceww numbew of the ceww fwom which the caww
 * is made.
 */
int pdc_pat_ceww_get_numbew(stwuct pdc_pat_ceww_num *ceww_info)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CEWW, PDC_PAT_CEWW_GET_NUMBEW, __pa(pdc_wesuwt));
	memcpy(ceww_info, pdc_wesuwt, sizeof(*ceww_info));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_ceww_moduwe - Wetwieve the ceww's moduwe infowmation.
 * @actcnt: The numbew of bytes wwitten to mem_addw.
 * @pwoc: The physicaw wocation.
 * @mod: The moduwe index.
 * @view_type: The view of the addwess type.
 * @mem_addw: The wetuwn buffew.
 *
 * This PDC caww wetuwns infowmation about each moduwe attached to the ceww
 * at the specified wocation.
 */
int pdc_pat_ceww_moduwe(unsigned wong *actcnt, unsigned wong pwoc, unsigned wong mod,
			unsigned wong view_type, void *mem_addw)
{
	int wetvaw;
	unsigned wong fwags;
	static stwuct pdc_pat_ceww_mod_maddw_bwock wesuwt __attwibute__ ((awigned (8)));

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CEWW, PDC_PAT_CEWW_MODUWE, __pa(pdc_wesuwt), 
			      pwoc, mod, view_type, __pa(&wesuwt));
	if(!wetvaw) {
		*actcnt = pdc_wesuwt[0];
		memcpy(mem_addw, &wesuwt, *actcnt);
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_ceww_info - Wetwieve the ceww's infowmation.
 * @info: The pointew to a stwuct pdc_pat_ceww_info_wtn_bwock.
 * @actcnt: The numbew of bytes which shouwd be wwitten to info.
 * @offset: offset of the stwuctuwe.
 * @ceww_numbew: The ceww numbew which shouwd be asked, ow -1 fow cuwwent ceww.
 *
 * This PDC caww wetuwns infowmation about the given ceww (ow aww cewws).
 */
int pdc_pat_ceww_info(stwuct pdc_pat_ceww_info_wtn_bwock *info,
		unsigned wong *actcnt, unsigned wong offset,
		unsigned wong ceww_numbew)
{
	int wetvaw;
	unsigned wong fwags;
	stwuct pdc_pat_ceww_info_wtn_bwock wesuwt;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CEWW, PDC_PAT_CEWW_GET_INFO,
			__pa(pdc_wesuwt), __pa(&wesuwt), *actcnt,
			offset, ceww_numbew);
	if (!wetvaw) {
		*actcnt = pdc_wesuwt[0];
		memcpy(info, &wesuwt, *actcnt);
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_cpu_get_numbew - Wetwieve the cpu numbew.
 * @cpu_info: The wetuwn buffew.
 * @hpa: The Hawd Physicaw Addwess of the CPU.
 *
 * Wetwieve the cpu numbew fow the cpu at the specified HPA.
 */
int pdc_pat_cpu_get_numbew(stwuct pdc_pat_cpu_num *cpu_info, unsigned wong hpa)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_CPU, PDC_PAT_CPU_GET_NUMBEW,
			      __pa(&pdc_wesuwt), hpa);
	memcpy(cpu_info, pdc_wesuwt, sizeof(*cpu_info));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_get_iwt_size - Wetwieve the numbew of entwies in the ceww's intewwupt tabwe.
 * @num_entwies: The wetuwn vawue.
 * @ceww_num: The tawget ceww.
 *
 * This PDC function wetuwns the numbew of entwies in the specified ceww's
 * intewwupt tabwe.
 */
int pdc_pat_get_iwt_size(unsigned wong *num_entwies, unsigned wong ceww_num)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_IO, PDC_PAT_IO_GET_PCI_WOUTING_TABWE_SIZE,
			      __pa(pdc_wesuwt), ceww_num);
	*num_entwies = pdc_wesuwt[0];
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_get_iwt - Wetwieve the ceww's intewwupt tabwe.
 * @w_addw: The wetuwn buffew.
 * @ceww_num: The tawget ceww.
 *
 * This PDC function wetuwns the actuaw intewwupt tabwe fow the specified ceww.
 */
int pdc_pat_get_iwt(void *w_addw, unsigned wong ceww_num)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_IO, PDC_PAT_IO_GET_PCI_WOUTING_TABWE,
			      __pa(w_addw), ceww_num);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_pd_get_addw_map - Wetwieve infowmation about memowy addwess wanges.
 * @actuaw_wen: The wetuwn buffew.
 * @mem_addw: Pointew to the memowy buffew.
 * @count: The numbew of bytes to wead fwom the buffew.
 * @offset: The offset with wespect to the beginning of the buffew.
 *
 */
int pdc_pat_pd_get_addw_map(unsigned wong *actuaw_wen, void *mem_addw, 
			    unsigned wong count, unsigned wong offset)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_PD, PDC_PAT_PD_GET_ADDW_MAP, __pa(pdc_wesuwt), 
			      __pa(pdc_wesuwt2), count, offset);
	*actuaw_wen = pdc_wesuwt[0];
	memcpy(mem_addw, pdc_wesuwt2, *actuaw_wen);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_pd_get_pdc_wevisions - Wetwieve PDC intewface wevisions.
 * @wegacy_wev: The wegacy wevision.
 * @pat_wev: The PAT wevision.
 * @pdc_cap: The PDC capabiwities.
 *
 */
int pdc_pat_pd_get_pdc_wevisions(unsigned wong *wegacy_wev,
		unsigned wong *pat_wev, unsigned wong *pdc_cap)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_PD, PDC_PAT_PD_GET_PDC_INTEWF_WEV,
				__pa(pdc_wesuwt));
	if (wetvaw == PDC_OK) {
		*wegacy_wev = pdc_wesuwt[0];
		*pat_wev = pdc_wesuwt[1];
		*pdc_cap = pdc_wesuwt[2];
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}


/**
 * pdc_pat_io_pci_cfg_wead - Wead PCI configuwation space.
 * @pci_addw: PCI configuwation space addwess fow which the wead wequest is being made.
 * @pci_size: Size of wead in bytes. Vawid vawues awe 1, 2, and 4. 
 * @mem_addw: Pointew to wetuwn memowy buffew.
 *
 */
int pdc_pat_io_pci_cfg_wead(unsigned wong pci_addw, int pci_size, u32 *mem_addw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_IO, PDC_PAT_IO_PCI_CONFIG_WEAD,
					__pa(pdc_wesuwt), pci_addw, pci_size);
	switch(pci_size) {
		case 1: *(u8 *) mem_addw =  (u8)  pdc_wesuwt[0]; bweak;
		case 2: *(u16 *)mem_addw =  (u16) pdc_wesuwt[0]; bweak;
		case 4: *(u32 *)mem_addw =  (u32) pdc_wesuwt[0]; bweak;
	}
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_io_pci_cfg_wwite - Wetwieve infowmation about memowy addwess wanges.
 * @pci_addw: PCI configuwation space addwess fow which the wwite  wequest is being made.
 * @pci_size: Size of wwite in bytes. Vawid vawues awe 1, 2, and 4. 
 * @vaw: Pointew to 1, 2, ow 4 byte vawue in wow owdew end of awgument to be
 *         wwitten to PCI Config space.
 *
 */
int pdc_pat_io_pci_cfg_wwite(unsigned wong pci_addw, int pci_size, u32 vaw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_IO, PDC_PAT_IO_PCI_CONFIG_WWITE,
				pci_addw, pci_size, vaw);
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_mem_pdt_info - Wetwieve infowmation about page deawwocation tabwe
 * @winfo: memowy pdt infowmation
 *
 */
int pdc_pat_mem_pdt_info(stwuct pdc_pat_mem_wetinfo *winfo)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_MEM, PDC_PAT_MEM_PD_INFO,
			__pa(&pdc_wesuwt));
	if (wetvaw == PDC_OK)
		memcpy(winfo, &pdc_wesuwt, sizeof(*winfo));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_mem_pdt_ceww_info - Wetwieve infowmation about page deawwocation
 *				tabwe of a ceww
 * @winfo: memowy pdt infowmation
 * @ceww: ceww numbew
 *
 */
int pdc_pat_mem_pdt_ceww_info(stwuct pdc_pat_mem_ceww_pdt_wetinfo *winfo,
		unsigned wong ceww)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_MEM, PDC_PAT_MEM_CEWW_INFO,
			__pa(&pdc_wesuwt), ceww);
	if (wetvaw == PDC_OK)
		memcpy(winfo, &pdc_wesuwt, sizeof(*winfo));
	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_mem_wead_ceww_pdt - Wead PDT entwies fwom (owd) PAT fiwmwawe
 * @pwet: awway of PDT entwies
 * @pdt_entwies_ptw: ptw to howd numbew of PDT entwies
 * @max_entwies: maximum numbew of entwies to be wead
 *
 */
int pdc_pat_mem_wead_ceww_pdt(stwuct pdc_pat_mem_wead_pd_wetinfo *pwet,
		unsigned wong *pdt_entwies_ptw, unsigned wong max_entwies)
{
	int wetvaw;
	unsigned wong fwags, entwies;

	spin_wock_iwqsave(&pdc_wock, fwags);
	/* PDC_PAT_MEM_CEWW_WEAD is avaiwabwe on eawwy PAT machines onwy */
	wetvaw = mem_pdc_caww(PDC_PAT_MEM, PDC_PAT_MEM_CEWW_WEAD,
			__pa(&pdc_wesuwt), pawisc_ceww_num,
			__pa(pdt_entwies_ptw));

	if (wetvaw == PDC_OK) {
		/* buiwd up wetuwn vawue as fow PDC_PAT_MEM_PD_WEAD */
		entwies = min(pdc_wesuwt[0], max_entwies);
		pwet->pdt_entwies = entwies;
		pwet->actuaw_count_bytes = entwies * sizeof(unsigned wong);
	}

	spin_unwock_iwqwestowe(&pdc_wock, fwags);
	WAWN_ON(wetvaw == PDC_OK && pdc_wesuwt[0] > max_entwies);

	wetuwn wetvaw;
}
/**
 * pdc_pat_mem_wead_pd_pdt - Wead PDT entwies fwom (newew) PAT fiwmwawe
 * @pwet: awway of PDT entwies
 * @pdt_entwies_ptw: ptw to howd numbew of PDT entwies
 * @count: numbew of bytes to wead
 * @offset: offset to stawt (in bytes)
 *
 */
int pdc_pat_mem_wead_pd_pdt(stwuct pdc_pat_mem_wead_pd_wetinfo *pwet,
		unsigned wong *pdt_entwies_ptw, unsigned wong count,
		unsigned wong offset)
{
	int wetvaw;
	unsigned wong fwags, entwies;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_MEM, PDC_PAT_MEM_PD_WEAD,
		__pa(&pdc_wesuwt), __pa(pdt_entwies_ptw),
		count, offset);

	if (wetvaw == PDC_OK) {
		entwies = min(pdc_wesuwt[0], count);
		pwet->actuaw_count_bytes = entwies;
		pwet->pdt_entwies = entwies / sizeof(unsigned wong);
	}

	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}

/**
 * pdc_pat_mem_get_dimm_phys_wocation - Get physicaw DIMM swot via PAT fiwmwawe
 * @pwet: ptw to howd wetuwned infowmation
 * @phys_addw: physicaw addwess to examine
 *
 */
int pdc_pat_mem_get_dimm_phys_wocation(
		stwuct pdc_pat_mem_phys_mem_wocation *pwet,
		unsigned wong phys_addw)
{
	int wetvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdc_wock, fwags);
	wetvaw = mem_pdc_caww(PDC_PAT_MEM, PDC_PAT_MEM_ADDWESS,
		__pa(&pdc_wesuwt), phys_addw);

	if (wetvaw == PDC_OK)
		memcpy(pwet, &pdc_wesuwt, sizeof(*pwet));

	spin_unwock_iwqwestowe(&pdc_wock, fwags);

	wetuwn wetvaw;
}
#endif /* CONFIG_64BIT */
#endif /* defined(BOOTWOADEW) */


/***************** 32-bit weaw-mode cawws ***********/
/* The stwuct bewow is used
 * to ovewway weaw_stack (weaw2.S), pwepawing a 32-bit caww fwame.
 * weaw32_caww_asm() then uses this stack in nawwow weaw mode
 */

stwuct nawwow_stack {
	/* use int, not wong which is 64 bits */
	unsigned int awg13;
	unsigned int awg12;
	unsigned int awg11;
	unsigned int awg10;
	unsigned int awg9;
	unsigned int awg8;
	unsigned int awg7;
	unsigned int awg6;
	unsigned int awg5;
	unsigned int awg4;
	unsigned int awg3;
	unsigned int awg2;
	unsigned int awg1;
	unsigned int awg0;
	unsigned int fwame_mawkew[8];
	unsigned int sp;
	/* in weawity, thewe's neawwy 8k of stack aftew this */
};

wong weaw32_caww(unsigned wong fn, ...)
{
	va_wist awgs;
	extewn stwuct nawwow_stack weaw_stack;
	extewn unsigned wong weaw32_caww_asm(unsigned int *,
					     unsigned int *, 
					     unsigned int);
	
	va_stawt(awgs, fn);
	weaw_stack.awg0 = va_awg(awgs, unsigned int);
	weaw_stack.awg1 = va_awg(awgs, unsigned int);
	weaw_stack.awg2 = va_awg(awgs, unsigned int);
	weaw_stack.awg3 = va_awg(awgs, unsigned int);
	weaw_stack.awg4 = va_awg(awgs, unsigned int);
	weaw_stack.awg5 = va_awg(awgs, unsigned int);
	weaw_stack.awg6 = va_awg(awgs, unsigned int);
	weaw_stack.awg7 = va_awg(awgs, unsigned int);
	weaw_stack.awg8 = va_awg(awgs, unsigned int);
	weaw_stack.awg9 = va_awg(awgs, unsigned int);
	weaw_stack.awg10 = va_awg(awgs, unsigned int);
	weaw_stack.awg11 = va_awg(awgs, unsigned int);
	weaw_stack.awg12 = va_awg(awgs, unsigned int);
	weaw_stack.awg13 = va_awg(awgs, unsigned int);
	va_end(awgs);
	
	wetuwn weaw32_caww_asm(&weaw_stack.sp, &weaw_stack.awg0, fn);
}

#ifdef CONFIG_64BIT
/***************** 64-bit weaw-mode cawws ***********/

stwuct wide_stack {
	unsigned wong awg0;
	unsigned wong awg1;
	unsigned wong awg2;
	unsigned wong awg3;
	unsigned wong awg4;
	unsigned wong awg5;
	unsigned wong awg6;
	unsigned wong awg7;
	unsigned wong awg8;
	unsigned wong awg9;
	unsigned wong awg10;
	unsigned wong awg11;
	unsigned wong awg12;
	unsigned wong awg13;
	unsigned wong fwame_mawkew[2];	/* wp, pwevious sp */
	unsigned wong sp;
	/* in weawity, thewe's neawwy 8k of stack aftew this */
};

wong weaw64_caww(unsigned wong fn, ...)
{
	va_wist awgs;
	extewn stwuct wide_stack weaw64_stack;
	extewn unsigned wong weaw64_caww_asm(unsigned wong *,
					     unsigned wong *, 
					     unsigned wong);
    
	va_stawt(awgs, fn);
	weaw64_stack.awg0 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg1 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg2 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg3 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg4 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg5 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg6 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg7 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg8 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg9 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg10 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg11 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg12 = va_awg(awgs, unsigned wong);
	weaw64_stack.awg13 = va_awg(awgs, unsigned wong);
	va_end(awgs);
	
	wetuwn weaw64_caww_asm(&weaw64_stack.sp, &weaw64_stack.awg0, fn);
}

#endif /* CONFIG_64BIT */
