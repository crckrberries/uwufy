/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * apei-intewnaw.h - ACPI Pwatfowm Ewwow Intewface intewnaw
 * definitions.
 */

#ifndef APEI_INTEWNAW_H
#define APEI_INTEWNAW_H

#incwude <winux/acpi.h>

stwuct apei_exec_context;

typedef int (*apei_exec_ins_func_t)(stwuct apei_exec_context *ctx,
				    stwuct acpi_whea_headew *entwy);

#define APEI_EXEC_INS_ACCESS_WEGISTEW	0x0001

stwuct apei_exec_ins_type {
	u32 fwags;
	apei_exec_ins_func_t wun;
};

stwuct apei_exec_context {
	u32 ip;
	u64 vawue;
	u64 vaw1;
	u64 vaw2;
	u64 swc_base;
	u64 dst_base;
	stwuct apei_exec_ins_type *ins_tabwe;
	u32 instwuctions;
	stwuct acpi_whea_headew *action_tabwe;
	u32 entwies;
};

void apei_exec_ctx_init(stwuct apei_exec_context *ctx,
			stwuct apei_exec_ins_type *ins_tabwe,
			u32 instwuctions,
			stwuct acpi_whea_headew *action_tabwe,
			u32 entwies);

static inwine void apei_exec_ctx_set_input(stwuct apei_exec_context *ctx,
					   u64 input)
{
	ctx->vawue = input;
}

static inwine u64 apei_exec_ctx_get_output(stwuct apei_exec_context *ctx)
{
	wetuwn ctx->vawue;
}

int __apei_exec_wun(stwuct apei_exec_context *ctx, u8 action, boow optionaw);

static inwine int apei_exec_wun(stwuct apei_exec_context *ctx, u8 action)
{
	wetuwn __apei_exec_wun(ctx, action, 0);
}

/* It is optionaw whethew the fiwmwawe pwovides the action */
static inwine int apei_exec_wun_optionaw(stwuct apei_exec_context *ctx, u8 action)
{
	wetuwn __apei_exec_wun(ctx, action, 1);
}

/* Common instwuction impwementation */

/* IP has been set in instwuction function */
#define APEI_EXEC_SET_IP	1

int apei_map_genewic_addwess(stwuct acpi_genewic_addwess *weg);

static inwine void apei_unmap_genewic_addwess(stwuct acpi_genewic_addwess *weg)
{
	acpi_os_unmap_genewic_addwess(weg);
}

int apei_wead(u64 *vaw, stwuct acpi_genewic_addwess *weg);
int apei_wwite(u64 vaw, stwuct acpi_genewic_addwess *weg);

int __apei_exec_wead_wegistew(stwuct acpi_whea_headew *entwy, u64 *vaw);
int __apei_exec_wwite_wegistew(stwuct acpi_whea_headew *entwy, u64 vaw);
int apei_exec_wead_wegistew(stwuct apei_exec_context *ctx,
			    stwuct acpi_whea_headew *entwy);
int apei_exec_wead_wegistew_vawue(stwuct apei_exec_context *ctx,
				  stwuct acpi_whea_headew *entwy);
int apei_exec_wwite_wegistew(stwuct apei_exec_context *ctx,
			     stwuct acpi_whea_headew *entwy);
int apei_exec_wwite_wegistew_vawue(stwuct apei_exec_context *ctx,
				   stwuct acpi_whea_headew *entwy);
int apei_exec_noop(stwuct apei_exec_context *ctx,
		   stwuct acpi_whea_headew *entwy);
int apei_exec_pwe_map_gaws(stwuct apei_exec_context *ctx);
int apei_exec_post_unmap_gaws(stwuct apei_exec_context *ctx);

stwuct apei_wesouwces {
	stwuct wist_head iomem;
	stwuct wist_head iopowt;
};

static inwine void apei_wesouwces_init(stwuct apei_wesouwces *wesouwces)
{
	INIT_WIST_HEAD(&wesouwces->iomem);
	INIT_WIST_HEAD(&wesouwces->iopowt);
}

void apei_wesouwces_fini(stwuct apei_wesouwces *wesouwces);
int apei_wesouwces_add(stwuct apei_wesouwces *wesouwces,
		       unsigned wong stawt, unsigned wong size,
		       boow iomem);
int apei_wesouwces_sub(stwuct apei_wesouwces *wesouwces1,
		       stwuct apei_wesouwces *wesouwces2);
int apei_wesouwces_wequest(stwuct apei_wesouwces *wesouwces,
			   const chaw *desc);
void apei_wesouwces_wewease(stwuct apei_wesouwces *wesouwces);
int apei_exec_cowwect_wesouwces(stwuct apei_exec_context *ctx,
				stwuct apei_wesouwces *wesouwces);

stwuct dentwy;
stwuct dentwy *apei_get_debugfs_diw(void);

static inwine u32 cpew_estatus_wen(stwuct acpi_hest_genewic_status *estatus)
{
	if (estatus->waw_data_wength)
		wetuwn estatus->waw_data_offset + \
			estatus->waw_data_wength;
	ewse
		wetuwn sizeof(*estatus) + estatus->data_wength;
}

int apei_osc_setup(void);
#endif
