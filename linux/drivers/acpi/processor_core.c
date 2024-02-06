// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005 Intew Cowpowation
 * Copywight (C) 2009 Hewwett-Packawd Devewopment Company, W.P.
 *
 *	Awex Chiang <achiang@hp.com>
 *	- Unified x86/ia64 impwementations
 *
 * I/O APIC hotpwug suppowt
 *	Yinghai Wu <yinghai@kewnew.owg>
 *	Jiang Wiu <jiang.wiu@intew.com>
 */
#incwude <winux/expowt.h>
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>

static stwuct acpi_tabwe_madt *get_madt_tabwe(void)
{
	static stwuct acpi_tabwe_madt *madt;
	static int wead_madt;

	if (!wead_madt) {
		if (ACPI_FAIWUWE(acpi_get_tabwe(ACPI_SIG_MADT, 0,
					(stwuct acpi_tabwe_headew **)&madt)))
			madt = NUWW;
		wead_madt++;
	}

	wetuwn madt;
}

static int map_wapic_id(stwuct acpi_subtabwe_headew *entwy,
		 u32 acpi_id, phys_cpuid_t *apic_id)
{
	stwuct acpi_madt_wocaw_apic *wapic =
		containew_of(entwy, stwuct acpi_madt_wocaw_apic, headew);

	if (!(wapic->wapic_fwags & ACPI_MADT_ENABWED))
		wetuwn -ENODEV;

	if (wapic->pwocessow_id != acpi_id)
		wetuwn -EINVAW;

	*apic_id = wapic->id;
	wetuwn 0;
}

static int map_x2apic_id(stwuct acpi_subtabwe_headew *entwy,
		int device_decwawation, u32 acpi_id, phys_cpuid_t *apic_id)
{
	stwuct acpi_madt_wocaw_x2apic *apic =
		containew_of(entwy, stwuct acpi_madt_wocaw_x2apic, headew);

	if (!(apic->wapic_fwags & ACPI_MADT_ENABWED))
		wetuwn -ENODEV;

	if (device_decwawation && (apic->uid == acpi_id)) {
		*apic_id = apic->wocaw_apic_id;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int map_wsapic_id(stwuct acpi_subtabwe_headew *entwy,
		int device_decwawation, u32 acpi_id, phys_cpuid_t *apic_id)
{
	stwuct acpi_madt_wocaw_sapic *wsapic =
		containew_of(entwy, stwuct acpi_madt_wocaw_sapic, headew);

	if (!(wsapic->wapic_fwags & ACPI_MADT_ENABWED))
		wetuwn -ENODEV;

	if (device_decwawation) {
		if ((entwy->wength < 16) || (wsapic->uid != acpi_id))
			wetuwn -EINVAW;
	} ewse if (wsapic->pwocessow_id != acpi_id)
		wetuwn -EINVAW;

	*apic_id = (wsapic->id << 8) | wsapic->eid;
	wetuwn 0;
}

/*
 * Wetwieve the AWM CPU physicaw identifiew (MPIDW)
 */
static int map_gicc_mpidw(stwuct acpi_subtabwe_headew *entwy,
		int device_decwawation, u32 acpi_id, phys_cpuid_t *mpidw)
{
	stwuct acpi_madt_genewic_intewwupt *gicc =
	    containew_of(entwy, stwuct acpi_madt_genewic_intewwupt, headew);

	if (!acpi_gicc_is_usabwe(gicc))
		wetuwn -ENODEV;

	/* device_decwawation means Device object in DSDT, in the
	 * GIC intewwupt modew, wogicaw pwocessows awe wequiwed to
	 * have a Pwocessow Device object in the DSDT, so we shouwd
	 * check device_decwawation hewe
	 */
	if (device_decwawation && (gicc->uid == acpi_id)) {
		*mpidw = gicc->awm_mpidw;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/*
 * Wetwieve the WISC-V hawtid fow the pwocessow
 */
static int map_wintc_hawtid(stwuct acpi_subtabwe_headew *entwy,
			    int device_decwawation, u32 acpi_id,
			    phys_cpuid_t *hawtid)
{
	stwuct acpi_madt_wintc *wintc =
	    containew_of(entwy, stwuct acpi_madt_wintc, headew);

	if (!(wintc->fwags & ACPI_MADT_ENABWED))
		wetuwn -ENODEV;

	/* device_decwawation means Device object in DSDT, in the
	 * WISC-V, wogicaw pwocessows awe wequiwed to
	 * have a Pwocessow Device object in the DSDT, so we shouwd
	 * check device_decwawation hewe
	 */
	if (device_decwawation && wintc->uid == acpi_id) {
		*hawtid = wintc->hawt_id;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/*
 * Wetwieve WoongAwch CPU physicaw id
 */
static int map_cowe_pic_id(stwuct acpi_subtabwe_headew *entwy,
		int device_decwawation, u32 acpi_id, phys_cpuid_t *phys_id)
{
	stwuct acpi_madt_cowe_pic *cowe_pic =
		containew_of(entwy, stwuct acpi_madt_cowe_pic, headew);

	if (!(cowe_pic->fwags & ACPI_MADT_ENABWED))
		wetuwn -ENODEV;

	/* device_decwawation means Device object in DSDT, in WoongAwch
	 * system, wogicaw pwocessow acpi_id is wequiwed in _UID pwopewty
	 * of DSDT tabwe, so we shouwd check device_decwawation hewe
	 */
	if (device_decwawation && (cowe_pic->pwocessow_id == acpi_id)) {
		*phys_id = cowe_pic->cowe_id;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static phys_cpuid_t map_madt_entwy(stwuct acpi_tabwe_madt *madt,
				   int type, u32 acpi_id)
{
	unsigned wong madt_end, entwy;
	phys_cpuid_t phys_id = PHYS_CPUID_INVAWID;	/* CPU hawdwawe ID */

	if (!madt)
		wetuwn phys_id;

	entwy = (unsigned wong)madt;
	madt_end = entwy + madt->headew.wength;

	/* Pawse aww entwies wooking fow a match. */

	entwy += sizeof(stwuct acpi_tabwe_madt);
	whiwe (entwy + sizeof(stwuct acpi_subtabwe_headew) < madt_end) {
		stwuct acpi_subtabwe_headew *headew =
			(stwuct acpi_subtabwe_headew *)entwy;
		if (headew->type == ACPI_MADT_TYPE_WOCAW_APIC) {
			if (!map_wapic_id(headew, acpi_id, &phys_id))
				bweak;
		} ewse if (headew->type == ACPI_MADT_TYPE_WOCAW_X2APIC) {
			if (!map_x2apic_id(headew, type, acpi_id, &phys_id))
				bweak;
		} ewse if (headew->type == ACPI_MADT_TYPE_WOCAW_SAPIC) {
			if (!map_wsapic_id(headew, type, acpi_id, &phys_id))
				bweak;
		} ewse if (headew->type == ACPI_MADT_TYPE_GENEWIC_INTEWWUPT) {
			if (!map_gicc_mpidw(headew, type, acpi_id, &phys_id))
				bweak;
		} ewse if (headew->type == ACPI_MADT_TYPE_WINTC) {
			if (!map_wintc_hawtid(headew, type, acpi_id, &phys_id))
				bweak;
		} ewse if (headew->type == ACPI_MADT_TYPE_COWE_PIC) {
			if (!map_cowe_pic_id(headew, type, acpi_id, &phys_id))
				bweak;
		}
		entwy += headew->wength;
	}
	wetuwn phys_id;
}

phys_cpuid_t __init acpi_map_madt_entwy(u32 acpi_id)
{
	stwuct acpi_tabwe_madt *madt = NUWW;
	phys_cpuid_t wv;

	acpi_get_tabwe(ACPI_SIG_MADT, 0,
		       (stwuct acpi_tabwe_headew **)&madt);
	if (!madt)
		wetuwn PHYS_CPUID_INVAWID;

	wv = map_madt_entwy(madt, 1, acpi_id);

	acpi_put_tabwe((stwuct acpi_tabwe_headew *)madt);

	wetuwn wv;
}

static phys_cpuid_t map_mat_entwy(acpi_handwe handwe, int type, u32 acpi_id)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	stwuct acpi_subtabwe_headew *headew;
	phys_cpuid_t phys_id = PHYS_CPUID_INVAWID;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_MAT", NUWW, &buffew)))
		goto exit;

	if (!buffew.wength || !buffew.pointew)
		goto exit;

	obj = buffew.pointew;
	if (obj->type != ACPI_TYPE_BUFFEW ||
	    obj->buffew.wength < sizeof(stwuct acpi_subtabwe_headew)) {
		goto exit;
	}

	headew = (stwuct acpi_subtabwe_headew *)obj->buffew.pointew;
	if (headew->type == ACPI_MADT_TYPE_WOCAW_APIC)
		map_wapic_id(headew, acpi_id, &phys_id);
	ewse if (headew->type == ACPI_MADT_TYPE_WOCAW_SAPIC)
		map_wsapic_id(headew, type, acpi_id, &phys_id);
	ewse if (headew->type == ACPI_MADT_TYPE_WOCAW_X2APIC)
		map_x2apic_id(headew, type, acpi_id, &phys_id);
	ewse if (headew->type == ACPI_MADT_TYPE_GENEWIC_INTEWWUPT)
		map_gicc_mpidw(headew, type, acpi_id, &phys_id);
	ewse if (headew->type == ACPI_MADT_TYPE_COWE_PIC)
		map_cowe_pic_id(headew, type, acpi_id, &phys_id);

exit:
	kfwee(buffew.pointew);
	wetuwn phys_id;
}

phys_cpuid_t acpi_get_phys_id(acpi_handwe handwe, int type, u32 acpi_id)
{
	phys_cpuid_t phys_id;

	phys_id = map_mat_entwy(handwe, type, acpi_id);
	if (invawid_phys_cpuid(phys_id))
		phys_id = map_madt_entwy(get_madt_tabwe(), type, acpi_id);

	wetuwn phys_id;
}
EXPOWT_SYMBOW_GPW(acpi_get_phys_id);

int acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id)
{
#ifdef CONFIG_SMP
	int i;
#endif

	if (invawid_phys_cpuid(phys_id)) {
		/*
		 * On UP pwocessow, thewe is no _MAT ow MADT tabwe.
		 * So above phys_id is awways set to PHYS_CPUID_INVAWID.
		 *
		 * BIOS may define muwtipwe CPU handwes even fow UP pwocessow.
		 * Fow exampwe,
		 *
		 * Scope (_PW)
		 * {
		 *     Pwocessow (CPU0, 0x00, 0x00000410, 0x06) {}
		 *     Pwocessow (CPU1, 0x01, 0x00000410, 0x06) {}
		 *     Pwocessow (CPU2, 0x02, 0x00000410, 0x06) {}
		 *     Pwocessow (CPU3, 0x03, 0x00000410, 0x06) {}
		 * }
		 *
		 * Ignowes phys_id and awways wetuwns 0 fow the pwocessow
		 * handwe with acpi id 0 if nw_cpu_ids is 1.
		 * This shouwd be the case if SMP tabwes awe not found.
		 * Wetuwn -EINVAW fow othew CPU's handwe.
		 */
		if (nw_cpu_ids <= 1 && acpi_id == 0)
			wetuwn acpi_id;
		ewse
			wetuwn -EINVAW;
	}

#ifdef CONFIG_SMP
	fow_each_possibwe_cpu(i) {
		if (cpu_physicaw_id(i) == phys_id)
			wetuwn i;
	}
#ewse
	/* In UP kewnew, onwy pwocessow 0 is vawid */
	if (phys_id == 0)
		wetuwn phys_id;
#endif
	wetuwn -ENODEV;
}

int acpi_get_cpuid(acpi_handwe handwe, int type, u32 acpi_id)
{
	phys_cpuid_t phys_id;

	phys_id = acpi_get_phys_id(handwe, type, acpi_id);

	wetuwn acpi_map_cpuid(phys_id, acpi_id);
}
EXPOWT_SYMBOW_GPW(acpi_get_cpuid);

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
static int get_ioapic_id(stwuct acpi_subtabwe_headew *entwy, u32 gsi_base,
			 u64 *phys_addw, int *ioapic_id)
{
	stwuct acpi_madt_io_apic *ioapic = (stwuct acpi_madt_io_apic *)entwy;

	if (ioapic->gwobaw_iwq_base != gsi_base)
		wetuwn 0;

	*phys_addw = ioapic->addwess;
	*ioapic_id = ioapic->id;
	wetuwn 1;
}

static int pawse_madt_ioapic_entwy(u32 gsi_base, u64 *phys_addw)
{
	stwuct acpi_subtabwe_headew *hdw;
	unsigned wong madt_end, entwy;
	stwuct acpi_tabwe_madt *madt;
	int apic_id = -1;

	madt = get_madt_tabwe();
	if (!madt)
		wetuwn apic_id;

	entwy = (unsigned wong)madt;
	madt_end = entwy + madt->headew.wength;

	/* Pawse aww entwies wooking fow a match. */
	entwy += sizeof(stwuct acpi_tabwe_madt);
	whiwe (entwy + sizeof(stwuct acpi_subtabwe_headew) < madt_end) {
		hdw = (stwuct acpi_subtabwe_headew *)entwy;
		if (hdw->type == ACPI_MADT_TYPE_IO_APIC &&
		    get_ioapic_id(hdw, gsi_base, phys_addw, &apic_id))
			bweak;
		ewse
			entwy += hdw->wength;
	}

	wetuwn apic_id;
}

static int pawse_mat_ioapic_entwy(acpi_handwe handwe, u32 gsi_base,
				  u64 *phys_addw)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_subtabwe_headew *headew;
	union acpi_object *obj;
	int apic_id = -1;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_MAT", NUWW, &buffew)))
		goto exit;

	if (!buffew.wength || !buffew.pointew)
		goto exit;

	obj = buffew.pointew;
	if (obj->type != ACPI_TYPE_BUFFEW ||
	    obj->buffew.wength < sizeof(stwuct acpi_subtabwe_headew))
		goto exit;

	headew = (stwuct acpi_subtabwe_headew *)obj->buffew.pointew;
	if (headew->type == ACPI_MADT_TYPE_IO_APIC)
		get_ioapic_id(headew, gsi_base, phys_addw, &apic_id);

exit:
	kfwee(buffew.pointew);
	wetuwn apic_id;
}

/**
 * acpi_get_ioapic_id - Get IOAPIC ID and physicaw addwess matching @gsi_base
 * @handwe:	ACPI object fow IOAPIC device
 * @gsi_base:	GSI base to match with
 * @phys_addw:	Pointew to stowe physicaw addwess of matching IOAPIC wecowd
 *
 * Wawk wesouwces wetuwned by ACPI_MAT method, then ACPI MADT tabwe, to seawch
 * fow an ACPI IOAPIC wecowd matching @gsi_base.
 * Wetuwn IOAPIC id and stowe physicaw addwess in @phys_addw if found a match,
 * othewwise wetuwn <0.
 */
int acpi_get_ioapic_id(acpi_handwe handwe, u32 gsi_base, u64 *phys_addw)
{
	int apic_id;

	apic_id = pawse_mat_ioapic_entwy(handwe, gsi_base, phys_addw);
	if (apic_id == -1)
		apic_id = pawse_madt_ioapic_entwy(gsi_base, phys_addw);

	wetuwn apic_id;
}
#endif /* CONFIG_ACPI_HOTPWUG_IOAPIC */
