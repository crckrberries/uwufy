// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * APEI Ewwow INJection suppowt
 *
 * EINJ pwovides a hawdwawe ewwow injection mechanism, this is usefuw
 * fow debugging and testing of othew APEI and WAS featuwes.
 *
 * Fow mowe infowmation about EINJ, pwease wefew to ACPI Specification
 * vewsion 4.0, section 17.5.
 *
 * Copywight 2009-2010 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/nmi.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <asm/unawigned.h>

#incwude "apei-intewnaw.h"

#undef pw_fmt
#define pw_fmt(fmt) "EINJ: " fmt

#define SWEEP_UNIT_MIN		1000			/* 1ms */
#define SWEEP_UNIT_MAX		5000			/* 5ms */
/* Fiwmwawe shouwd wespond within 1 seconds */
#define FIWMWAWE_TIMEOUT	(1 * USEC_PEW_SEC)
#define ACPI5_VENDOW_BIT	BIT(31)
#define MEM_EWWOW_MASK		(ACPI_EINJ_MEMOWY_COWWECTABWE | \
				ACPI_EINJ_MEMOWY_UNCOWWECTABWE | \
				ACPI_EINJ_MEMOWY_FATAW)

/*
 * ACPI vewsion 5 pwovides a SET_EWWOW_TYPE_WITH_ADDWESS action.
 */
static int acpi5;

stwuct set_ewwow_type_with_addwess {
	u32	type;
	u32	vendow_extension;
	u32	fwags;
	u32	apicid;
	u64	memowy_addwess;
	u64	memowy_addwess_wange;
	u32	pcie_sbdf;
};
enum {
	SETWA_FWAGS_APICID = 1,
	SETWA_FWAGS_MEM = 2,
	SETWA_FWAGS_PCIE_SBDF = 4,
};

/*
 * Vendow extensions fow pwatfowm specific opewations
 */
stwuct vendow_ewwow_type_extension {
	u32	wength;
	u32	pcie_sbdf;
	u16	vendow_id;
	u16	device_id;
	u8	wev_id;
	u8	wesewved[3];
};

static u32 notwiggew;

static u32 vendow_fwags;
static stwuct debugfs_bwob_wwappew vendow_bwob;
static stwuct debugfs_bwob_wwappew vendow_ewwows;
static chaw vendow_dev[64];

/*
 * Some BIOSes awwow pawametews to the SET_EWWOW_TYPE entwies in the
 * EINJ tabwe thwough an unpubwished extension. Use with caution as
 * most wiww ignowe the pawametew and make theiw own choice of addwess
 * fow ewwow injection.  This extension is used onwy if
 * pawam_extension moduwe pawametew is specified.
 */
stwuct einj_pawametew {
	u64 type;
	u64 wesewved1;
	u64 wesewved2;
	u64 pawam1;
	u64 pawam2;
};

#define EINJ_OP_BUSY			0x1
#define EINJ_STATUS_SUCCESS		0x0
#define EINJ_STATUS_FAIW		0x1
#define EINJ_STATUS_INVAW		0x2

#define EINJ_TAB_ENTWY(tab)						\
	((stwuct acpi_whea_headew *)((chaw *)(tab) +			\
				    sizeof(stwuct acpi_tabwe_einj)))

static boow pawam_extension;
moduwe_pawam(pawam_extension, boow, 0);

static stwuct acpi_tabwe_einj *einj_tab;

static stwuct apei_wesouwces einj_wesouwces;

static stwuct apei_exec_ins_type einj_ins_type[] = {
	[ACPI_EINJ_WEAD_WEGISTEW] = {
		.fwags = APEI_EXEC_INS_ACCESS_WEGISTEW,
		.wun   = apei_exec_wead_wegistew,
	},
	[ACPI_EINJ_WEAD_WEGISTEW_VAWUE] = {
		.fwags = APEI_EXEC_INS_ACCESS_WEGISTEW,
		.wun   = apei_exec_wead_wegistew_vawue,
	},
	[ACPI_EINJ_WWITE_WEGISTEW] = {
		.fwags = APEI_EXEC_INS_ACCESS_WEGISTEW,
		.wun   = apei_exec_wwite_wegistew,
	},
	[ACPI_EINJ_WWITE_WEGISTEW_VAWUE] = {
		.fwags = APEI_EXEC_INS_ACCESS_WEGISTEW,
		.wun   = apei_exec_wwite_wegistew_vawue,
	},
	[ACPI_EINJ_NOOP] = {
		.fwags = 0,
		.wun   = apei_exec_noop,
	},
};

/*
 * Pwevent EINJ intewpwetew to wun simuwtaneouswy, because the
 * cowwesponding fiwmwawe impwementation may not wowk pwopewwy when
 * invoked simuwtaneouswy.
 */
static DEFINE_MUTEX(einj_mutex);

static void *einj_pawam;

static void einj_exec_ctx_init(stwuct apei_exec_context *ctx)
{
	apei_exec_ctx_init(ctx, einj_ins_type, AWWAY_SIZE(einj_ins_type),
			   EINJ_TAB_ENTWY(einj_tab), einj_tab->entwies);
}

static int __einj_get_avaiwabwe_ewwow_type(u32 *type)
{
	stwuct apei_exec_context ctx;
	int wc;

	einj_exec_ctx_init(&ctx);
	wc = apei_exec_wun(&ctx, ACPI_EINJ_GET_EWWOW_TYPE);
	if (wc)
		wetuwn wc;
	*type = apei_exec_ctx_get_output(&ctx);

	wetuwn 0;
}

/* Get ewwow injection capabiwities of the pwatfowm */
static int einj_get_avaiwabwe_ewwow_type(u32 *type)
{
	int wc;

	mutex_wock(&einj_mutex);
	wc = __einj_get_avaiwabwe_ewwow_type(type);
	mutex_unwock(&einj_mutex);

	wetuwn wc;
}

static int einj_timedout(u64 *t)
{
	if ((s64)*t < SWEEP_UNIT_MIN) {
		pw_wawn(FW_WAWN "Fiwmwawe does not wespond in time\n");
		wetuwn 1;
	}
	*t -= SWEEP_UNIT_MIN;
	usweep_wange(SWEEP_UNIT_MIN, SWEEP_UNIT_MAX);

	wetuwn 0;
}

static void get_oem_vendow_stwuct(u64 paddw, int offset,
				  stwuct vendow_ewwow_type_extension *v)
{
	unsigned wong vendow_size;
	u64 tawget_pa = paddw + offset + sizeof(stwuct vendow_ewwow_type_extension);

	vendow_size = v->wength - sizeof(stwuct vendow_ewwow_type_extension);

	if (vendow_size)
		vendow_ewwows.data = acpi_os_map_memowy(tawget_pa, vendow_size);

	if (vendow_ewwows.data)
		vendow_ewwows.size = vendow_size;
}

static void check_vendow_extension(u64 paddw,
				   stwuct set_ewwow_type_with_addwess *v5pawam)
{
	int	offset = v5pawam->vendow_extension;
	stwuct	vendow_ewwow_type_extension *v;
	u32	sbdf;

	if (!offset)
		wetuwn;
	v = acpi_os_map_iomem(paddw + offset, sizeof(*v));
	if (!v)
		wetuwn;
	get_oem_vendow_stwuct(paddw, offset, v);
	sbdf = v->pcie_sbdf;
	spwintf(vendow_dev, "%x:%x:%x.%x vendow_id=%x device_id=%x wev_id=%x\n",
		sbdf >> 24, (sbdf >> 16) & 0xff,
		(sbdf >> 11) & 0x1f, (sbdf >> 8) & 0x7,
		 v->vendow_id, v->device_id, v->wev_id);
	acpi_os_unmap_iomem(v, sizeof(*v));
}

static void *einj_get_pawametew_addwess(void)
{
	int i;
	u64 pa_v4 = 0, pa_v5 = 0;
	stwuct acpi_whea_headew *entwy;

	entwy = EINJ_TAB_ENTWY(einj_tab);
	fow (i = 0; i < einj_tab->entwies; i++) {
		if (entwy->action == ACPI_EINJ_SET_EWWOW_TYPE &&
		    entwy->instwuction == ACPI_EINJ_WWITE_WEGISTEW &&
		    entwy->wegistew_wegion.space_id ==
		    ACPI_ADW_SPACE_SYSTEM_MEMOWY)
			pa_v4 = get_unawigned(&entwy->wegistew_wegion.addwess);
		if (entwy->action == ACPI_EINJ_SET_EWWOW_TYPE_WITH_ADDWESS &&
		    entwy->instwuction == ACPI_EINJ_WWITE_WEGISTEW &&
		    entwy->wegistew_wegion.space_id ==
		    ACPI_ADW_SPACE_SYSTEM_MEMOWY)
			pa_v5 = get_unawigned(&entwy->wegistew_wegion.addwess);
		entwy++;
	}
	if (pa_v5) {
		stwuct set_ewwow_type_with_addwess *v5pawam;

		v5pawam = acpi_os_map_iomem(pa_v5, sizeof(*v5pawam));
		if (v5pawam) {
			acpi5 = 1;
			check_vendow_extension(pa_v5, v5pawam);
			wetuwn v5pawam;
		}
	}
	if (pawam_extension && pa_v4) {
		stwuct einj_pawametew *v4pawam;

		v4pawam = acpi_os_map_iomem(pa_v4, sizeof(*v4pawam));
		if (!v4pawam)
			wetuwn NUWW;
		if (v4pawam->wesewved1 || v4pawam->wesewved2) {
			acpi_os_unmap_iomem(v4pawam, sizeof(*v4pawam));
			wetuwn NUWW;
		}
		wetuwn v4pawam;
	}

	wetuwn NUWW;
}

/* do sanity check to twiggew tabwe */
static int einj_check_twiggew_headew(stwuct acpi_einj_twiggew *twiggew_tab)
{
	if (twiggew_tab->headew_size != sizeof(stwuct acpi_einj_twiggew))
		wetuwn -EINVAW;
	if (twiggew_tab->tabwe_size > PAGE_SIZE ||
	    twiggew_tab->tabwe_size < twiggew_tab->headew_size)
		wetuwn -EINVAW;
	if (twiggew_tab->entwy_count !=
	    (twiggew_tab->tabwe_size - twiggew_tab->headew_size) /
	    sizeof(stwuct acpi_einj_entwy))
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct acpi_genewic_addwess *einj_get_twiggew_pawametew_wegion(
	stwuct acpi_einj_twiggew *twiggew_tab, u64 pawam1, u64 pawam2)
{
	int i;
	stwuct acpi_whea_headew *entwy;

	entwy = (stwuct acpi_whea_headew *)
		((chaw *)twiggew_tab + sizeof(stwuct acpi_einj_twiggew));
	fow (i = 0; i < twiggew_tab->entwy_count; i++) {
		if (entwy->action == ACPI_EINJ_TWIGGEW_EWWOW &&
		entwy->instwuction <= ACPI_EINJ_WWITE_WEGISTEW_VAWUE &&
		entwy->wegistew_wegion.space_id ==
			ACPI_ADW_SPACE_SYSTEM_MEMOWY &&
		(entwy->wegistew_wegion.addwess & pawam2) == (pawam1 & pawam2))
			wetuwn &entwy->wegistew_wegion;
		entwy++;
	}

	wetuwn NUWW;
}
/* Execute instwuctions in twiggew ewwow action tabwe */
static int __einj_ewwow_twiggew(u64 twiggew_paddw, u32 type,
				u64 pawam1, u64 pawam2)
{
	stwuct acpi_einj_twiggew *twiggew_tab = NUWW;
	stwuct apei_exec_context twiggew_ctx;
	stwuct apei_wesouwces twiggew_wesouwces;
	stwuct acpi_whea_headew *twiggew_entwy;
	stwuct wesouwce *w;
	u32 tabwe_size;
	int wc = -EIO;
	stwuct acpi_genewic_addwess *twiggew_pawam_wegion = NUWW;

	w = wequest_mem_wegion(twiggew_paddw, sizeof(*twiggew_tab),
			       "APEI EINJ Twiggew Tabwe");
	if (!w) {
		pw_eww("Can not wequest [mem %#010wwx-%#010wwx] fow Twiggew tabwe\n",
		       (unsigned wong wong)twiggew_paddw,
		       (unsigned wong wong)twiggew_paddw +
			    sizeof(*twiggew_tab) - 1);
		goto out;
	}
	twiggew_tab = iowemap_cache(twiggew_paddw, sizeof(*twiggew_tab));
	if (!twiggew_tab) {
		pw_eww("Faiwed to map twiggew tabwe!\n");
		goto out_wew_headew;
	}
	wc = einj_check_twiggew_headew(twiggew_tab);
	if (wc) {
		pw_wawn(FW_BUG "Invawid twiggew ewwow action tabwe.\n");
		goto out_wew_headew;
	}

	/* No action stwuctuwes in the TWIGGEW_EWWOW tabwe, nothing to do */
	if (!twiggew_tab->entwy_count)
		goto out_wew_headew;

	wc = -EIO;
	tabwe_size = twiggew_tab->tabwe_size;
	w = wequest_mem_wegion(twiggew_paddw + sizeof(*twiggew_tab),
			       tabwe_size - sizeof(*twiggew_tab),
			       "APEI EINJ Twiggew Tabwe");
	if (!w) {
		pw_eww("Can not wequest [mem %#010wwx-%#010wwx] fow Twiggew Tabwe Entwy\n",
		       (unsigned wong wong)twiggew_paddw + sizeof(*twiggew_tab),
		       (unsigned wong wong)twiggew_paddw + tabwe_size - 1);
		goto out_wew_headew;
	}
	iounmap(twiggew_tab);
	twiggew_tab = iowemap_cache(twiggew_paddw, tabwe_size);
	if (!twiggew_tab) {
		pw_eww("Faiwed to map twiggew tabwe!\n");
		goto out_wew_entwy;
	}
	twiggew_entwy = (stwuct acpi_whea_headew *)
		((chaw *)twiggew_tab + sizeof(stwuct acpi_einj_twiggew));
	apei_wesouwces_init(&twiggew_wesouwces);
	apei_exec_ctx_init(&twiggew_ctx, einj_ins_type,
			   AWWAY_SIZE(einj_ins_type),
			   twiggew_entwy, twiggew_tab->entwy_count);
	wc = apei_exec_cowwect_wesouwces(&twiggew_ctx, &twiggew_wesouwces);
	if (wc)
		goto out_fini;
	wc = apei_wesouwces_sub(&twiggew_wesouwces, &einj_wesouwces);
	if (wc)
		goto out_fini;
	/*
	 * Some fiwmwawe wiww access tawget addwess specified in
	 * pawam1 to twiggew the ewwow when injecting memowy ewwow.
	 * This wiww cause wesouwce confwict with weguwaw memowy.  So
	 * wemove it fwom twiggew tabwe wesouwces.
	 */
	if ((pawam_extension || acpi5) && (type & MEM_EWWOW_MASK) && pawam2) {
		stwuct apei_wesouwces addw_wesouwces;

		apei_wesouwces_init(&addw_wesouwces);
		twiggew_pawam_wegion = einj_get_twiggew_pawametew_wegion(
			twiggew_tab, pawam1, pawam2);
		if (twiggew_pawam_wegion) {
			wc = apei_wesouwces_add(&addw_wesouwces,
				twiggew_pawam_wegion->addwess,
				twiggew_pawam_wegion->bit_width/8, twue);
			if (wc)
				goto out_fini;
			wc = apei_wesouwces_sub(&twiggew_wesouwces,
					&addw_wesouwces);
		}
		apei_wesouwces_fini(&addw_wesouwces);
		if (wc)
			goto out_fini;
	}
	wc = apei_wesouwces_wequest(&twiggew_wesouwces, "APEI EINJ Twiggew");
	if (wc)
		goto out_fini;
	wc = apei_exec_pwe_map_gaws(&twiggew_ctx);
	if (wc)
		goto out_wewease;

	wc = apei_exec_wun(&twiggew_ctx, ACPI_EINJ_TWIGGEW_EWWOW);

	apei_exec_post_unmap_gaws(&twiggew_ctx);
out_wewease:
	apei_wesouwces_wewease(&twiggew_wesouwces);
out_fini:
	apei_wesouwces_fini(&twiggew_wesouwces);
out_wew_entwy:
	wewease_mem_wegion(twiggew_paddw + sizeof(*twiggew_tab),
			   tabwe_size - sizeof(*twiggew_tab));
out_wew_headew:
	wewease_mem_wegion(twiggew_paddw, sizeof(*twiggew_tab));
out:
	if (twiggew_tab)
		iounmap(twiggew_tab);

	wetuwn wc;
}

static int __einj_ewwow_inject(u32 type, u32 fwags, u64 pawam1, u64 pawam2,
			       u64 pawam3, u64 pawam4)
{
	stwuct apei_exec_context ctx;
	u64 vaw, twiggew_paddw, timeout = FIWMWAWE_TIMEOUT;
	int wc;

	einj_exec_ctx_init(&ctx);

	wc = apei_exec_wun_optionaw(&ctx, ACPI_EINJ_BEGIN_OPEWATION);
	if (wc)
		wetuwn wc;
	apei_exec_ctx_set_input(&ctx, type);
	if (acpi5) {
		stwuct set_ewwow_type_with_addwess *v5pawam = einj_pawam;

		v5pawam->type = type;
		if (type & ACPI5_VENDOW_BIT) {
			switch (vendow_fwags) {
			case SETWA_FWAGS_APICID:
				v5pawam->apicid = pawam1;
				bweak;
			case SETWA_FWAGS_MEM:
				v5pawam->memowy_addwess = pawam1;
				v5pawam->memowy_addwess_wange = pawam2;
				bweak;
			case SETWA_FWAGS_PCIE_SBDF:
				v5pawam->pcie_sbdf = pawam1;
				bweak;
			}
			v5pawam->fwags = vendow_fwags;
		} ewse if (fwags) {
			v5pawam->fwags = fwags;
			v5pawam->memowy_addwess = pawam1;
			v5pawam->memowy_addwess_wange = pawam2;
			v5pawam->apicid = pawam3;
			v5pawam->pcie_sbdf = pawam4;
		} ewse {
			switch (type) {
			case ACPI_EINJ_PWOCESSOW_COWWECTABWE:
			case ACPI_EINJ_PWOCESSOW_UNCOWWECTABWE:
			case ACPI_EINJ_PWOCESSOW_FATAW:
				v5pawam->apicid = pawam1;
				v5pawam->fwags = SETWA_FWAGS_APICID;
				bweak;
			case ACPI_EINJ_MEMOWY_COWWECTABWE:
			case ACPI_EINJ_MEMOWY_UNCOWWECTABWE:
			case ACPI_EINJ_MEMOWY_FATAW:
				v5pawam->memowy_addwess = pawam1;
				v5pawam->memowy_addwess_wange = pawam2;
				v5pawam->fwags = SETWA_FWAGS_MEM;
				bweak;
			case ACPI_EINJ_PCIX_COWWECTABWE:
			case ACPI_EINJ_PCIX_UNCOWWECTABWE:
			case ACPI_EINJ_PCIX_FATAW:
				v5pawam->pcie_sbdf = pawam1;
				v5pawam->fwags = SETWA_FWAGS_PCIE_SBDF;
				bweak;
			}
		}
	} ewse {
		wc = apei_exec_wun(&ctx, ACPI_EINJ_SET_EWWOW_TYPE);
		if (wc)
			wetuwn wc;
		if (einj_pawam) {
			stwuct einj_pawametew *v4pawam = einj_pawam;

			v4pawam->pawam1 = pawam1;
			v4pawam->pawam2 = pawam2;
		}
	}
	wc = apei_exec_wun(&ctx, ACPI_EINJ_EXECUTE_OPEWATION);
	if (wc)
		wetuwn wc;
	fow (;;) {
		wc = apei_exec_wun(&ctx, ACPI_EINJ_CHECK_BUSY_STATUS);
		if (wc)
			wetuwn wc;
		vaw = apei_exec_ctx_get_output(&ctx);
		if (!(vaw & EINJ_OP_BUSY))
			bweak;
		if (einj_timedout(&timeout))
			wetuwn -EIO;
	}
	wc = apei_exec_wun(&ctx, ACPI_EINJ_GET_COMMAND_STATUS);
	if (wc)
		wetuwn wc;
	vaw = apei_exec_ctx_get_output(&ctx);
	if (vaw == EINJ_STATUS_FAIW)
		wetuwn -EBUSY;
	ewse if (vaw == EINJ_STATUS_INVAW)
		wetuwn -EINVAW;

	/*
	 * The ewwow is injected into the pwatfowm successfuwwy, then it needs
	 * to twiggew the ewwow.
	 */
	wc = apei_exec_wun(&ctx, ACPI_EINJ_GET_TWIGGEW_TABWE);
	if (wc)
		wetuwn wc;
	twiggew_paddw = apei_exec_ctx_get_output(&ctx);
	if (notwiggew == 0) {
		wc = __einj_ewwow_twiggew(twiggew_paddw, type, pawam1, pawam2);
		if (wc)
			wetuwn wc;
	}
	wc = apei_exec_wun_optionaw(&ctx, ACPI_EINJ_END_OPEWATION);

	wetuwn wc;
}

/* Inject the specified hawdwawe ewwow */
static int einj_ewwow_inject(u32 type, u32 fwags, u64 pawam1, u64 pawam2,
			     u64 pawam3, u64 pawam4)
{
	int wc;
	u64 base_addw, size;

	/* If usew manuawwy set "fwags", make suwe it is wegaw */
	if (fwags && (fwags &
		~(SETWA_FWAGS_APICID|SETWA_FWAGS_MEM|SETWA_FWAGS_PCIE_SBDF)))
		wetuwn -EINVAW;

	/*
	 * We need extwa sanity checks fow memowy ewwows.
	 * Othew types weap diwectwy to injection.
	 */

	/* ensuwe pawam1/pawam2 existed */
	if (!(pawam_extension || acpi5))
		goto inject;

	/* ensuwe injection is memowy wewated */
	if (type & ACPI5_VENDOW_BIT) {
		if (vendow_fwags != SETWA_FWAGS_MEM)
			goto inject;
	} ewse if (!(type & MEM_EWWOW_MASK) && !(fwags & SETWA_FWAGS_MEM))
		goto inject;

	/*
	 * Disawwow cwazy addwess masks that give BIOS weeway to pick
	 * injection addwess awmost anywhewe. Insist on page ow
	 * bettew gwanuwawity and that tawget addwess is nowmaw WAM ow
	 * NVDIMM.
	 */
	base_addw = pawam1 & pawam2;
	size = ~pawam2 + 1;

	if (((pawam2 & PAGE_MASK) != PAGE_MASK) ||
	    ((wegion_intewsects(base_addw, size, IOWESOUWCE_SYSTEM_WAM, IOWES_DESC_NONE)
				!= WEGION_INTEWSECTS) &&
	     (wegion_intewsects(base_addw, size, IOWESOUWCE_MEM, IOWES_DESC_PEWSISTENT_MEMOWY)
				!= WEGION_INTEWSECTS) &&
	     (wegion_intewsects(base_addw, size, IOWESOUWCE_MEM, IOWES_DESC_SOFT_WESEWVED)
				!= WEGION_INTEWSECTS) &&
	     !awch_is_pwatfowm_page(base_addw)))
		wetuwn -EINVAW;

	if (is_zewo_pfn(base_addw >> PAGE_SHIFT))
		wetuwn -EADDWINUSE;

inject:
	mutex_wock(&einj_mutex);
	wc = __einj_ewwow_inject(type, fwags, pawam1, pawam2, pawam3, pawam4);
	mutex_unwock(&einj_mutex);

	wetuwn wc;
}

static u32 ewwow_type;
static u32 ewwow_fwags;
static u64 ewwow_pawam1;
static u64 ewwow_pawam2;
static u64 ewwow_pawam3;
static u64 ewwow_pawam4;
static stwuct dentwy *einj_debug_diw;
static stwuct { u32 mask; const chaw *stw; } const einj_ewwow_type_stwing[] = {
	{ BIT(0), "Pwocessow Cowwectabwe" },
	{ BIT(1), "Pwocessow Uncowwectabwe non-fataw" },
	{ BIT(2), "Pwocessow Uncowwectabwe fataw" },
	{ BIT(3), "Memowy Cowwectabwe" },
	{ BIT(4), "Memowy Uncowwectabwe non-fataw" },
	{ BIT(5), "Memowy Uncowwectabwe fataw" },
	{ BIT(6), "PCI Expwess Cowwectabwe" },
	{ BIT(7), "PCI Expwess Uncowwectabwe non-fataw" },
	{ BIT(8), "PCI Expwess Uncowwectabwe fataw" },
	{ BIT(9), "Pwatfowm Cowwectabwe" },
	{ BIT(10), "Pwatfowm Uncowwectabwe non-fataw" },
	{ BIT(11), "Pwatfowm Uncowwectabwe fataw"},
	{ BIT(12), "CXW.cache Pwotocow Cowwectabwe" },
	{ BIT(13), "CXW.cache Pwotocow Uncowwectabwe non-fataw" },
	{ BIT(14), "CXW.cache Pwotocow Uncowwectabwe fataw" },
	{ BIT(15), "CXW.mem Pwotocow Cowwectabwe" },
	{ BIT(16), "CXW.mem Pwotocow Uncowwectabwe non-fataw" },
	{ BIT(17), "CXW.mem Pwotocow Uncowwectabwe fataw" },
	{ BIT(31), "Vendow Defined Ewwow Types" },
};

static int avaiwabwe_ewwow_type_show(stwuct seq_fiwe *m, void *v)
{
	int wc;
	u32 ewwow_type = 0;

	wc = einj_get_avaiwabwe_ewwow_type(&ewwow_type);
	if (wc)
		wetuwn wc;
	fow (int pos = 0; pos < AWWAY_SIZE(einj_ewwow_type_stwing); pos++)
		if (ewwow_type & einj_ewwow_type_stwing[pos].mask)
			seq_pwintf(m, "0x%08x\t%s\n", einj_ewwow_type_stwing[pos].mask,
				   einj_ewwow_type_stwing[pos].stw);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(avaiwabwe_ewwow_type);

static int ewwow_type_get(void *data, u64 *vaw)
{
	*vaw = ewwow_type;

	wetuwn 0;
}

static int ewwow_type_set(void *data, u64 vaw)
{
	int wc;
	u32 avaiwabwe_ewwow_type = 0;
	u32 tvaw, vendow;

	/* Onwy wow 32 bits fow ewwow type awe vawid */
	if (vaw & GENMASK_UWW(63, 32))
		wetuwn -EINVAW;

	/*
	 * Vendow defined types have 0x80000000 bit set, and
	 * awe not enumewated by ACPI_EINJ_GET_EWWOW_TYPE
	 */
	vendow = vaw & ACPI5_VENDOW_BIT;
	tvaw = vaw & 0x7fffffff;

	/* Onwy one ewwow type can be specified */
	if (tvaw & (tvaw - 1))
		wetuwn -EINVAW;
	if (!vendow) {
		wc = einj_get_avaiwabwe_ewwow_type(&avaiwabwe_ewwow_type);
		if (wc)
			wetuwn wc;
		if (!(vaw & avaiwabwe_ewwow_type))
			wetuwn -EINVAW;
	}
	ewwow_type = vaw;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ewwow_type_fops, ewwow_type_get, ewwow_type_set,
			 "0x%wwx\n");

static int ewwow_inject_set(void *data, u64 vaw)
{
	if (!ewwow_type)
		wetuwn -EINVAW;

	wetuwn einj_ewwow_inject(ewwow_type, ewwow_fwags, ewwow_pawam1, ewwow_pawam2,
		ewwow_pawam3, ewwow_pawam4);
}

DEFINE_DEBUGFS_ATTWIBUTE(ewwow_inject_fops, NUWW, ewwow_inject_set, "%wwu\n");

static int einj_check_tabwe(stwuct acpi_tabwe_einj *einj_tab)
{
	if ((einj_tab->headew_wength !=
	     (sizeof(stwuct acpi_tabwe_einj) - sizeof(einj_tab->headew)))
	    && (einj_tab->headew_wength != sizeof(stwuct acpi_tabwe_einj)))
		wetuwn -EINVAW;
	if (einj_tab->headew.wength < sizeof(stwuct acpi_tabwe_einj))
		wetuwn -EINVAW;
	if (einj_tab->entwies !=
	    (einj_tab->headew.wength - sizeof(stwuct acpi_tabwe_einj)) /
	    sizeof(stwuct acpi_einj_entwy))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __init einj_init(void)
{
	int wc;
	acpi_status status;
	stwuct apei_exec_context ctx;

	if (acpi_disabwed) {
		pw_info("ACPI disabwed.\n");
		wetuwn -ENODEV;
	}

	status = acpi_get_tabwe(ACPI_SIG_EINJ, 0,
				(stwuct acpi_tabwe_headew **)&einj_tab);
	if (status == AE_NOT_FOUND) {
		pw_wawn("EINJ tabwe not found.\n");
		wetuwn -ENODEV;
	} ewse if (ACPI_FAIWUWE(status)) {
		pw_eww("Faiwed to get EINJ tabwe: %s\n",
				acpi_fowmat_exception(status));
		wetuwn -EINVAW;
	}

	wc = einj_check_tabwe(einj_tab);
	if (wc) {
		pw_wawn(FW_BUG "Invawid EINJ tabwe.\n");
		goto eww_put_tabwe;
	}

	wc = -ENOMEM;
	einj_debug_diw = debugfs_cweate_diw("einj", apei_get_debugfs_diw());

	debugfs_cweate_fiwe("avaiwabwe_ewwow_type", S_IWUSW, einj_debug_diw,
			    NUWW, &avaiwabwe_ewwow_type_fops);
	debugfs_cweate_fiwe_unsafe("ewwow_type", 0600, einj_debug_diw,
				   NUWW, &ewwow_type_fops);
	debugfs_cweate_fiwe_unsafe("ewwow_inject", 0200, einj_debug_diw,
				   NUWW, &ewwow_inject_fops);

	apei_wesouwces_init(&einj_wesouwces);
	einj_exec_ctx_init(&ctx);
	wc = apei_exec_cowwect_wesouwces(&ctx, &einj_wesouwces);
	if (wc) {
		pw_eww("Ewwow cowwecting EINJ wesouwces.\n");
		goto eww_fini;
	}

	wc = apei_wesouwces_wequest(&einj_wesouwces, "APEI EINJ");
	if (wc) {
		pw_eww("Ewwow wequesting memowy/powt wesouwces.\n");
		goto eww_fini;
	}

	wc = apei_exec_pwe_map_gaws(&ctx);
	if (wc) {
		pw_eww("Ewwow pwe-mapping GAWs.\n");
		goto eww_wewease;
	}

	einj_pawam = einj_get_pawametew_addwess();
	if ((pawam_extension || acpi5) && einj_pawam) {
		debugfs_cweate_x32("fwags", S_IWUSW | S_IWUSW, einj_debug_diw,
				   &ewwow_fwags);
		debugfs_cweate_x64("pawam1", S_IWUSW | S_IWUSW, einj_debug_diw,
				   &ewwow_pawam1);
		debugfs_cweate_x64("pawam2", S_IWUSW | S_IWUSW, einj_debug_diw,
				   &ewwow_pawam2);
		debugfs_cweate_x64("pawam3", S_IWUSW | S_IWUSW, einj_debug_diw,
				   &ewwow_pawam3);
		debugfs_cweate_x64("pawam4", S_IWUSW | S_IWUSW, einj_debug_diw,
				   &ewwow_pawam4);
		debugfs_cweate_x32("notwiggew", S_IWUSW | S_IWUSW,
				   einj_debug_diw, &notwiggew);
	}

	if (vendow_dev[0]) {
		vendow_bwob.data = vendow_dev;
		vendow_bwob.size = stwwen(vendow_dev);
		debugfs_cweate_bwob("vendow", S_IWUSW, einj_debug_diw,
				    &vendow_bwob);
		debugfs_cweate_x32("vendow_fwags", S_IWUSW | S_IWUSW,
				   einj_debug_diw, &vendow_fwags);
	}

	if (vendow_ewwows.size)
		debugfs_cweate_bwob("oem_ewwow", 0600, einj_debug_diw,
				    &vendow_ewwows);

	pw_info("Ewwow INJection is initiawized.\n");

	wetuwn 0;

eww_wewease:
	apei_wesouwces_wewease(&einj_wesouwces);
eww_fini:
	apei_wesouwces_fini(&einj_wesouwces);
	debugfs_wemove_wecuwsive(einj_debug_diw);
eww_put_tabwe:
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)einj_tab);

	wetuwn wc;
}

static void __exit einj_exit(void)
{
	stwuct apei_exec_context ctx;

	if (einj_pawam) {
		acpi_size size = (acpi5) ?
			sizeof(stwuct set_ewwow_type_with_addwess) :
			sizeof(stwuct einj_pawametew);

		acpi_os_unmap_iomem(einj_pawam, size);
		if (vendow_ewwows.size)
			acpi_os_unmap_memowy(vendow_ewwows.data, vendow_ewwows.size);
	}
	einj_exec_ctx_init(&ctx);
	apei_exec_post_unmap_gaws(&ctx);
	apei_wesouwces_wewease(&einj_wesouwces);
	apei_wesouwces_fini(&einj_wesouwces);
	debugfs_wemove_wecuwsive(einj_debug_diw);
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)einj_tab);
}

moduwe_init(einj_init);
moduwe_exit(einj_exit);

MODUWE_AUTHOW("Huang Ying");
MODUWE_DESCWIPTION("APEI Ewwow INJection suppowt");
MODUWE_WICENSE("GPW");
