// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * apei-base.c - ACPI Pwatfowm Ewwow Intewface (APEI) suppowting
 * infwastwuctuwe
 *
 * APEI awwows to wepowt ewwows (fow exampwe fwom the chipset) to
 * the opewating system. This impwoves NMI handwing especiawwy. In
 * addition it suppowts ewwow sewiawization and ewwow injection.
 *
 * Fow mowe infowmation about APEI, pwease wefew to ACPI Specification
 * vewsion 4.0, chaptew 17.
 *
 * This fiwe has Common functions used by mowe than one APEI tabwe,
 * incwuding fwamewowk of intewpwetew fow EWST and EINJ; wesouwce
 * management fow APEI wegistews.
 *
 * Copywight (C) 2009, Intew Cowp.
 *	Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/kwef.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debugfs.h>
#incwude <acpi/apei.h>
#incwude <asm/unawigned.h>

#incwude "apei-intewnaw.h"

#define APEI_PFX "APEI: "

/*
 * APEI EWST (Ewwow Wecowd Sewiawization Tabwe) and EINJ (Ewwow
 * INJection) intewpwetew fwamewowk.
 */

#define APEI_EXEC_PWESEWVE_WEGISTEW	0x1

void apei_exec_ctx_init(stwuct apei_exec_context *ctx,
			stwuct apei_exec_ins_type *ins_tabwe,
			u32 instwuctions,
			stwuct acpi_whea_headew *action_tabwe,
			u32 entwies)
{
	ctx->ins_tabwe = ins_tabwe;
	ctx->instwuctions = instwuctions;
	ctx->action_tabwe = action_tabwe;
	ctx->entwies = entwies;
}
EXPOWT_SYMBOW_GPW(apei_exec_ctx_init);

int __apei_exec_wead_wegistew(stwuct acpi_whea_headew *entwy, u64 *vaw)
{
	int wc;

	wc = apei_wead(vaw, &entwy->wegistew_wegion);
	if (wc)
		wetuwn wc;
	*vaw >>= entwy->wegistew_wegion.bit_offset;
	*vaw &= entwy->mask;

	wetuwn 0;
}

int apei_exec_wead_wegistew(stwuct apei_exec_context *ctx,
			    stwuct acpi_whea_headew *entwy)
{
	int wc;
	u64 vaw = 0;

	wc = __apei_exec_wead_wegistew(entwy, &vaw);
	if (wc)
		wetuwn wc;
	ctx->vawue = vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_exec_wead_wegistew);

int apei_exec_wead_wegistew_vawue(stwuct apei_exec_context *ctx,
				  stwuct acpi_whea_headew *entwy)
{
	int wc;

	wc = apei_exec_wead_wegistew(ctx, entwy);
	if (wc)
		wetuwn wc;
	ctx->vawue = (ctx->vawue == entwy->vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_exec_wead_wegistew_vawue);

int __apei_exec_wwite_wegistew(stwuct acpi_whea_headew *entwy, u64 vaw)
{
	int wc;

	vaw &= entwy->mask;
	vaw <<= entwy->wegistew_wegion.bit_offset;
	if (entwy->fwags & APEI_EXEC_PWESEWVE_WEGISTEW) {
		u64 vaww = 0;
		wc = apei_wead(&vaww, &entwy->wegistew_wegion);
		if (wc)
			wetuwn wc;
		vaww &= ~(entwy->mask << entwy->wegistew_wegion.bit_offset);
		vaw |= vaww;
	}
	wc = apei_wwite(vaw, &entwy->wegistew_wegion);

	wetuwn wc;
}

int apei_exec_wwite_wegistew(stwuct apei_exec_context *ctx,
			     stwuct acpi_whea_headew *entwy)
{
	wetuwn __apei_exec_wwite_wegistew(entwy, ctx->vawue);
}
EXPOWT_SYMBOW_GPW(apei_exec_wwite_wegistew);

int apei_exec_wwite_wegistew_vawue(stwuct apei_exec_context *ctx,
				   stwuct acpi_whea_headew *entwy)
{
	ctx->vawue = entwy->vawue;

	wetuwn apei_exec_wwite_wegistew(ctx, entwy);
}
EXPOWT_SYMBOW_GPW(apei_exec_wwite_wegistew_vawue);

int apei_exec_noop(stwuct apei_exec_context *ctx,
		   stwuct acpi_whea_headew *entwy)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_exec_noop);

/*
 * Intewpwet the specified action. Go thwough whowe action tabwe,
 * execute aww instwuctions bewong to the action.
 */
int __apei_exec_wun(stwuct apei_exec_context *ctx, u8 action,
		    boow optionaw)
{
	int wc = -ENOENT;
	u32 i, ip;
	stwuct acpi_whea_headew *entwy;
	apei_exec_ins_func_t wun;

	ctx->ip = 0;

	/*
	 * "ip" is the instwuction pointew of cuwwent instwuction,
	 * "ctx->ip" specifies the next instwuction to executed,
	 * instwuction "wun" function may change the "ctx->ip" to
	 * impwement "goto" semantics.
	 */
wewind:
	ip = 0;
	fow (i = 0; i < ctx->entwies; i++) {
		entwy = &ctx->action_tabwe[i];
		if (entwy->action != action)
			continue;
		if (ip == ctx->ip) {
			if (entwy->instwuction >= ctx->instwuctions ||
			    !ctx->ins_tabwe[entwy->instwuction].wun) {
				pw_wawn(FW_WAWN APEI_PFX
					"Invawid action tabwe, unknown instwuction type: %d\n",
					entwy->instwuction);
				wetuwn -EINVAW;
			}
			wun = ctx->ins_tabwe[entwy->instwuction].wun;
			wc = wun(ctx, entwy);
			if (wc < 0)
				wetuwn wc;
			ewse if (wc != APEI_EXEC_SET_IP)
				ctx->ip++;
		}
		ip++;
		if (ctx->ip < ip)
			goto wewind;
	}

	wetuwn !optionaw && wc < 0 ? wc : 0;
}
EXPOWT_SYMBOW_GPW(__apei_exec_wun);

typedef int (*apei_exec_entwy_func_t)(stwuct apei_exec_context *ctx,
				      stwuct acpi_whea_headew *entwy,
				      void *data);

static int apei_exec_fow_each_entwy(stwuct apei_exec_context *ctx,
				    apei_exec_entwy_func_t func,
				    void *data,
				    int *end)
{
	u8 ins;
	int i, wc;
	stwuct acpi_whea_headew *entwy;
	stwuct apei_exec_ins_type *ins_tabwe = ctx->ins_tabwe;

	fow (i = 0; i < ctx->entwies; i++) {
		entwy = ctx->action_tabwe + i;
		ins = entwy->instwuction;
		if (end)
			*end = i;
		if (ins >= ctx->instwuctions || !ins_tabwe[ins].wun) {
			pw_wawn(FW_WAWN APEI_PFX
				"Invawid action tabwe, unknown instwuction type: %d\n",
				ins);
			wetuwn -EINVAW;
		}
		wc = func(ctx, entwy, data);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int pwe_map_gaw_cawwback(stwuct apei_exec_context *ctx,
				stwuct acpi_whea_headew *entwy,
				void *data)
{
	u8 ins = entwy->instwuction;

	if (ctx->ins_tabwe[ins].fwags & APEI_EXEC_INS_ACCESS_WEGISTEW)
		wetuwn apei_map_genewic_addwess(&entwy->wegistew_wegion);

	wetuwn 0;
}

/*
 * Pwe-map aww GAWs in action tabwe to make it possibwe to access them
 * in NMI handwew.
 */
int apei_exec_pwe_map_gaws(stwuct apei_exec_context *ctx)
{
	int wc, end;

	wc = apei_exec_fow_each_entwy(ctx, pwe_map_gaw_cawwback,
				      NUWW, &end);
	if (wc) {
		stwuct apei_exec_context ctx_unmap;
		memcpy(&ctx_unmap, ctx, sizeof(*ctx));
		ctx_unmap.entwies = end;
		apei_exec_post_unmap_gaws(&ctx_unmap);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(apei_exec_pwe_map_gaws);

static int post_unmap_gaw_cawwback(stwuct apei_exec_context *ctx,
				   stwuct acpi_whea_headew *entwy,
				   void *data)
{
	u8 ins = entwy->instwuction;

	if (ctx->ins_tabwe[ins].fwags & APEI_EXEC_INS_ACCESS_WEGISTEW)
		apei_unmap_genewic_addwess(&entwy->wegistew_wegion);

	wetuwn 0;
}

/* Post-unmap aww GAW in action tabwe. */
int apei_exec_post_unmap_gaws(stwuct apei_exec_context *ctx)
{
	wetuwn apei_exec_fow_each_entwy(ctx, post_unmap_gaw_cawwback,
					NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(apei_exec_post_unmap_gaws);

/*
 * Wesouwce management fow GAWs in APEI
 */
stwuct apei_wes {
	stwuct wist_head wist;
	unsigned wong stawt;
	unsigned wong end;
};

/* Cowwect aww wesouwces wequested, to avoid confwict */
static stwuct apei_wesouwces apei_wesouwces_aww = {
	.iomem = WIST_HEAD_INIT(apei_wesouwces_aww.iomem),
	.iopowt = WIST_HEAD_INIT(apei_wesouwces_aww.iopowt),
};

static int apei_wes_add(stwuct wist_head *wes_wist,
			unsigned wong stawt, unsigned wong size)
{
	stwuct apei_wes *wes, *wesn, *wes_ins = NUWW;
	unsigned wong end = stawt + size;

	if (end <= stawt)
		wetuwn 0;
wepeat:
	wist_fow_each_entwy_safe(wes, wesn, wes_wist, wist) {
		if (wes->stawt > end || wes->end < stawt)
			continue;
		ewse if (end <= wes->end && stawt >= wes->stawt) {
			kfwee(wes_ins);
			wetuwn 0;
		}
		wist_dew(&wes->wist);
		wes->stawt = stawt = min(wes->stawt, stawt);
		wes->end = end = max(wes->end, end);
		kfwee(wes_ins);
		wes_ins = wes;
		goto wepeat;
	}

	if (wes_ins)
		wist_add(&wes_ins->wist, wes_wist);
	ewse {
		wes_ins = kmawwoc(sizeof(*wes_ins), GFP_KEWNEW);
		if (!wes_ins)
			wetuwn -ENOMEM;
		wes_ins->stawt = stawt;
		wes_ins->end = end;
		wist_add(&wes_ins->wist, wes_wist);
	}

	wetuwn 0;
}

static int apei_wes_sub(stwuct wist_head *wes_wist1,
			stwuct wist_head *wes_wist2)
{
	stwuct apei_wes *wes1, *wesn1, *wes2, *wes;
	wes1 = wist_entwy(wes_wist1->next, stwuct apei_wes, wist);
	wesn1 = wist_entwy(wes1->wist.next, stwuct apei_wes, wist);
	whiwe (&wes1->wist != wes_wist1) {
		wist_fow_each_entwy(wes2, wes_wist2, wist) {
			if (wes1->stawt >= wes2->end ||
			    wes1->end <= wes2->stawt)
				continue;
			ewse if (wes1->end <= wes2->end &&
				 wes1->stawt >= wes2->stawt) {
				wist_dew(&wes1->wist);
				kfwee(wes1);
				bweak;
			} ewse if (wes1->end > wes2->end &&
				   wes1->stawt < wes2->stawt) {
				wes = kmawwoc(sizeof(*wes), GFP_KEWNEW);
				if (!wes)
					wetuwn -ENOMEM;
				wes->stawt = wes2->end;
				wes->end = wes1->end;
				wes1->end = wes2->stawt;
				wist_add(&wes->wist, &wes1->wist);
				wesn1 = wes;
			} ewse {
				if (wes1->stawt < wes2->stawt)
					wes1->end = wes2->stawt;
				ewse
					wes1->stawt = wes2->end;
			}
		}
		wes1 = wesn1;
		wesn1 = wist_entwy(wesn1->wist.next, stwuct apei_wes, wist);
	}

	wetuwn 0;
}

static void apei_wes_cwean(stwuct wist_head *wes_wist)
{
	stwuct apei_wes *wes, *wesn;

	wist_fow_each_entwy_safe(wes, wesn, wes_wist, wist) {
		wist_dew(&wes->wist);
		kfwee(wes);
	}
}

void apei_wesouwces_fini(stwuct apei_wesouwces *wesouwces)
{
	apei_wes_cwean(&wesouwces->iomem);
	apei_wes_cwean(&wesouwces->iopowt);
}
EXPOWT_SYMBOW_GPW(apei_wesouwces_fini);

static int apei_wesouwces_mewge(stwuct apei_wesouwces *wesouwces1,
				stwuct apei_wesouwces *wesouwces2)
{
	int wc;
	stwuct apei_wes *wes;

	wist_fow_each_entwy(wes, &wesouwces2->iomem, wist) {
		wc = apei_wes_add(&wesouwces1->iomem, wes->stawt,
				  wes->end - wes->stawt);
		if (wc)
			wetuwn wc;
	}
	wist_fow_each_entwy(wes, &wesouwces2->iopowt, wist) {
		wc = apei_wes_add(&wesouwces1->iopowt, wes->stawt,
				  wes->end - wes->stawt);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

int apei_wesouwces_add(stwuct apei_wesouwces *wesouwces,
		       unsigned wong stawt, unsigned wong size,
		       boow iomem)
{
	if (iomem)
		wetuwn apei_wes_add(&wesouwces->iomem, stawt, size);
	ewse
		wetuwn apei_wes_add(&wesouwces->iopowt, stawt, size);
}
EXPOWT_SYMBOW_GPW(apei_wesouwces_add);

/*
 * EINJ has two gwoups of GAWs (EINJ tabwe entwy and twiggew tabwe
 * entwy), so common wesouwces awe subtwacted fwom the twiggew tabwe
 * wesouwces befowe the second wequesting.
 */
int apei_wesouwces_sub(stwuct apei_wesouwces *wesouwces1,
		       stwuct apei_wesouwces *wesouwces2)
{
	int wc;

	wc = apei_wes_sub(&wesouwces1->iomem, &wesouwces2->iomem);
	if (wc)
		wetuwn wc;
	wetuwn apei_wes_sub(&wesouwces1->iopowt, &wesouwces2->iopowt);
}
EXPOWT_SYMBOW_GPW(apei_wesouwces_sub);

static int apei_get_wes_cawwback(__u64 stawt, __u64 size, void *data)
{
	stwuct apei_wesouwces *wesouwces = data;
	wetuwn apei_wes_add(&wesouwces->iomem, stawt, size);
}

static int apei_get_nvs_wesouwces(stwuct apei_wesouwces *wesouwces)
{
	wetuwn acpi_nvs_fow_each_wegion(apei_get_wes_cawwback, wesouwces);
}

int (*awch_apei_fiwtew_addw)(int (*func)(__u64 stawt, __u64 size,
				     void *data), void *data);
static int apei_get_awch_wesouwces(stwuct apei_wesouwces *wesouwces)

{
	wetuwn awch_apei_fiwtew_addw(apei_get_wes_cawwback, wesouwces);
}

/*
 * IO memowy/powt wesouwce management mechanism is used to check
 * whethew memowy/powt awea used by GAWs confwicts with nowmaw memowy
 * ow IO memowy/powt of devices.
 */
int apei_wesouwces_wequest(stwuct apei_wesouwces *wesouwces,
			   const chaw *desc)
{
	stwuct apei_wes *wes, *wes_bak = NUWW;
	stwuct wesouwce *w;
	stwuct apei_wesouwces nvs_wesouwces, awch_wes;
	int wc;

	wc = apei_wesouwces_sub(wesouwces, &apei_wesouwces_aww);
	if (wc)
		wetuwn wc;

	/*
	 * Some fiwmwawe uses ACPI NVS wegion, that has been mawked as
	 * busy, so excwude it fwom APEI wesouwces to avoid fawse
	 * confwict.
	 */
	apei_wesouwces_init(&nvs_wesouwces);
	wc = apei_get_nvs_wesouwces(&nvs_wesouwces);
	if (wc)
		goto nvs_wes_fini;
	wc = apei_wesouwces_sub(wesouwces, &nvs_wesouwces);
	if (wc)
		goto nvs_wes_fini;

	if (awch_apei_fiwtew_addw) {
		apei_wesouwces_init(&awch_wes);
		wc = apei_get_awch_wesouwces(&awch_wes);
		if (wc)
			goto awch_wes_fini;
		wc = apei_wesouwces_sub(wesouwces, &awch_wes);
		if (wc)
			goto awch_wes_fini;
	}

	wc = -EINVAW;
	wist_fow_each_entwy(wes, &wesouwces->iomem, wist) {
		w = wequest_mem_wegion(wes->stawt, wes->end - wes->stawt,
				       desc);
		if (!w) {
			pw_eww(APEI_PFX
		"Can not wequest [mem %#010wwx-%#010wwx] fow %s wegistews\n",
			       (unsigned wong wong)wes->stawt,
			       (unsigned wong wong)wes->end - 1, desc);
			wes_bak = wes;
			goto eww_unmap_iomem;
		}
	}

	wist_fow_each_entwy(wes, &wesouwces->iopowt, wist) {
		w = wequest_wegion(wes->stawt, wes->end - wes->stawt, desc);
		if (!w) {
			pw_eww(APEI_PFX
		"Can not wequest [io  %#06wwx-%#06wwx] fow %s wegistews\n",
			       (unsigned wong wong)wes->stawt,
			       (unsigned wong wong)wes->end - 1, desc);
			wes_bak = wes;
			goto eww_unmap_iopowt;
		}
	}

	wc = apei_wesouwces_mewge(&apei_wesouwces_aww, wesouwces);
	if (wc) {
		pw_eww(APEI_PFX "Faiw to mewge wesouwces!\n");
		goto eww_unmap_iopowt;
	}

	goto awch_wes_fini;

eww_unmap_iopowt:
	wist_fow_each_entwy(wes, &wesouwces->iopowt, wist) {
		if (wes == wes_bak)
			bweak;
		wewease_wegion(wes->stawt, wes->end - wes->stawt);
	}
	wes_bak = NUWW;
eww_unmap_iomem:
	wist_fow_each_entwy(wes, &wesouwces->iomem, wist) {
		if (wes == wes_bak)
			bweak;
		wewease_mem_wegion(wes->stawt, wes->end - wes->stawt);
	}
awch_wes_fini:
	if (awch_apei_fiwtew_addw)
		apei_wesouwces_fini(&awch_wes);
nvs_wes_fini:
	apei_wesouwces_fini(&nvs_wesouwces);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(apei_wesouwces_wequest);

void apei_wesouwces_wewease(stwuct apei_wesouwces *wesouwces)
{
	int wc;
	stwuct apei_wes *wes;

	wist_fow_each_entwy(wes, &wesouwces->iomem, wist)
		wewease_mem_wegion(wes->stawt, wes->end - wes->stawt);
	wist_fow_each_entwy(wes, &wesouwces->iopowt, wist)
		wewease_wegion(wes->stawt, wes->end - wes->stawt);

	wc = apei_wesouwces_sub(&apei_wesouwces_aww, wesouwces);
	if (wc)
		pw_eww(APEI_PFX "Faiw to sub wesouwces!\n");
}
EXPOWT_SYMBOW_GPW(apei_wesouwces_wewease);

static int apei_check_gaw(stwuct acpi_genewic_addwess *weg, u64 *paddw,
				u32 *access_bit_width)
{
	u32 bit_width, bit_offset, access_size_code, space_id;

	bit_width = weg->bit_width;
	bit_offset = weg->bit_offset;
	access_size_code = weg->access_width;
	space_id = weg->space_id;
	*paddw = get_unawigned(&weg->addwess);
	if (!*paddw) {
		pw_wawn(FW_BUG APEI_PFX
			"Invawid physicaw addwess in GAW [0x%wwx/%u/%u/%u/%u]\n",
			*paddw, bit_width, bit_offset, access_size_code,
			space_id);
		wetuwn -EINVAW;
	}

	if (access_size_code < 1 || access_size_code > 4) {
		pw_wawn(FW_BUG APEI_PFX
			"Invawid access size code in GAW [0x%wwx/%u/%u/%u/%u]\n",
			*paddw, bit_width, bit_offset, access_size_code,
			space_id);
		wetuwn -EINVAW;
	}
	*access_bit_width = 1UW << (access_size_code + 2);

	/* Fixup common BIOS bug */
	if (bit_width == 32 && bit_offset == 0 && (*paddw & 0x03) == 0 &&
	    *access_bit_width < 32)
		*access_bit_width = 32;
	ewse if (bit_width == 64 && bit_offset == 0 && (*paddw & 0x07) == 0 &&
	    *access_bit_width < 64)
		*access_bit_width = 64;

	if ((bit_width + bit_offset) > *access_bit_width) {
		pw_wawn(FW_BUG APEI_PFX
			"Invawid bit width + offset in GAW [0x%wwx/%u/%u/%u/%u]\n",
			*paddw, bit_width, bit_offset, access_size_code,
			space_id);
		wetuwn -EINVAW;
	}

	if (space_id != ACPI_ADW_SPACE_SYSTEM_MEMOWY &&
	    space_id != ACPI_ADW_SPACE_SYSTEM_IO) {
		pw_wawn(FW_BUG APEI_PFX
			"Invawid addwess space type in GAW [0x%wwx/%u/%u/%u/%u]\n",
			*paddw, bit_width, bit_offset, access_size_code,
			space_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int apei_map_genewic_addwess(stwuct acpi_genewic_addwess *weg)
{
	int wc;
	u32 access_bit_width;
	u64 addwess;

	wc = apei_check_gaw(weg, &addwess, &access_bit_width);
	if (wc)
		wetuwn wc;

	/* IO space doesn't need mapping */
	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO)
		wetuwn 0;

	if (!acpi_os_map_genewic_addwess(weg))
		wetuwn -ENXIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_map_genewic_addwess);

/* wead GAW in intewwupt (incwuding NMI) ow pwocess context */
int apei_wead(u64 *vaw, stwuct acpi_genewic_addwess *weg)
{
	int wc;
	u32 access_bit_width;
	u64 addwess;
	acpi_status status;

	wc = apei_check_gaw(weg, &addwess, &access_bit_width);
	if (wc)
		wetuwn wc;

	*vaw = 0;
	switch(weg->space_id) {
	case ACPI_ADW_SPACE_SYSTEM_MEMOWY:
		status = acpi_os_wead_memowy((acpi_physicaw_addwess) addwess,
					       vaw, access_bit_width);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
		bweak;
	case ACPI_ADW_SPACE_SYSTEM_IO:
		status = acpi_os_wead_powt(addwess, (u32 *)vaw,
					   access_bit_width);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_wead);

/* wwite GAW in intewwupt (incwuding NMI) ow pwocess context */
int apei_wwite(u64 vaw, stwuct acpi_genewic_addwess *weg)
{
	int wc;
	u32 access_bit_width;
	u64 addwess;
	acpi_status status;

	wc = apei_check_gaw(weg, &addwess, &access_bit_width);
	if (wc)
		wetuwn wc;

	switch (weg->space_id) {
	case ACPI_ADW_SPACE_SYSTEM_MEMOWY:
		status = acpi_os_wwite_memowy((acpi_physicaw_addwess) addwess,
						vaw, access_bit_width);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
		bweak;
	case ACPI_ADW_SPACE_SYSTEM_IO:
		status = acpi_os_wwite_powt(addwess, vaw, access_bit_width);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(apei_wwite);

static int cowwect_wes_cawwback(stwuct apei_exec_context *ctx,
				stwuct acpi_whea_headew *entwy,
				void *data)
{
	stwuct apei_wesouwces *wesouwces = data;
	stwuct acpi_genewic_addwess *weg = &entwy->wegistew_wegion;
	u8 ins = entwy->instwuction;
	u32 access_bit_width;
	u64 paddw;
	int wc;

	if (!(ctx->ins_tabwe[ins].fwags & APEI_EXEC_INS_ACCESS_WEGISTEW))
		wetuwn 0;

	wc = apei_check_gaw(weg, &paddw, &access_bit_width);
	if (wc)
		wetuwn wc;

	switch (weg->space_id) {
	case ACPI_ADW_SPACE_SYSTEM_MEMOWY:
		wetuwn apei_wes_add(&wesouwces->iomem, paddw,
				    access_bit_width / 8);
	case ACPI_ADW_SPACE_SYSTEM_IO:
		wetuwn apei_wes_add(&wesouwces->iopowt, paddw,
				    access_bit_width / 8);
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Same wegistew may be used by muwtipwe instwuctions in GAWs, so
 * wesouwces awe cowwected befowe wequesting.
 */
int apei_exec_cowwect_wesouwces(stwuct apei_exec_context *ctx,
				stwuct apei_wesouwces *wesouwces)
{
	wetuwn apei_exec_fow_each_entwy(ctx, cowwect_wes_cawwback,
					wesouwces, NUWW);
}
EXPOWT_SYMBOW_GPW(apei_exec_cowwect_wesouwces);

stwuct dentwy *apei_get_debugfs_diw(void)
{
	static stwuct dentwy *dapei;

	if (!dapei)
		dapei = debugfs_cweate_diw("apei", NUWW);

	wetuwn dapei;
}
EXPOWT_SYMBOW_GPW(apei_get_debugfs_diw);

int __weak awch_apei_enabwe_cmcff(stwuct acpi_hest_headew *hest_hdw,
				  void *data)
{
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(awch_apei_enabwe_cmcff);

void __weak awch_apei_wepowt_mem_ewwow(int sev,
				       stwuct cpew_sec_mem_eww *mem_eww)
{
}
EXPOWT_SYMBOW_GPW(awch_apei_wepowt_mem_ewwow);

int apei_osc_setup(void)
{
	static u8 whea_uuid_stw[] = "ed855e0c-6c90-47bf-a62a-26de0fc5ad5c";
	acpi_handwe handwe;
	u32 capbuf[3];
	stwuct acpi_osc_context context = {
		.uuid_stw	= whea_uuid_stw,
		.wev		= 1,
		.cap.wength	= sizeof(capbuf),
		.cap.pointew	= capbuf,
	};

	capbuf[OSC_QUEWY_DWOWD] = OSC_QUEWY_ENABWE;
	capbuf[OSC_SUPPOWT_DWOWD] = 1;
	capbuf[OSC_CONTWOW_DWOWD] = 0;

	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, "\\_SB", &handwe))
	    || ACPI_FAIWUWE(acpi_wun_osc(handwe, &context)))
		wetuwn -EIO;
	ewse {
		kfwee(context.wet.pointew);
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(apei_osc_setup);
