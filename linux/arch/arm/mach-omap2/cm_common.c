// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2+ common Cwock Management (CM) IP bwock functions
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 *
 * XXX This code shouwd eventuawwy be moved to a CM dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cm2xxx.h"
#incwude "cm3xxx.h"
#incwude "cm33xx.h"
#incwude "cm44xx.h"
#incwude "cwock.h"

/*
 * cm_ww_data: function pointews to SoC-specific impwementations of
 * common CM functions
 */
static stwuct cm_ww_data nuww_cm_ww_data;
static const stwuct cm_ww_data *cm_ww_data = &nuww_cm_ww_data;

/* cm_base: base viwtuaw addwess of the CM IP bwock */
stwuct omap_domain_base cm_base;

/* cm2_base: base viwtuaw addwess of the CM2 IP bwock (OMAP44xx onwy) */
stwuct omap_domain_base cm2_base;

#define CM_NO_CWOCKS		0x1
#define CM_SINGWE_INSTANCE	0x2

/**
 * cm_spwit_idwest_weg - spwit CM_IDWEST weg addw into its components
 * @idwest_weg: CM_IDWEST* viwtuaw addwess
 * @pwcm_inst: pointew to an s16 to wetuwn the PWCM instance offset
 * @idwest_weg_id: pointew to a u8 to wetuwn the CM_IDWESTx wegistew ID
 *
 * Given an absowute CM_IDWEST wegistew addwess @idwest_weg, passes
 * the PWCM instance offset and IDWEST wegistew ID back to the cawwew
 * via the @pwcm_inst and @idwest_weg_id.  Wetuwns -EINVAW upon ewwow,
 * ow 0 upon success.  XXX This function is onwy needed untiw absowute
 * wegistew addwesses awe wemoved fwom the OMAP stwuct cwk wecowds.
 */
int cm_spwit_idwest_weg(stwuct cwk_omap_weg *idwest_weg, s16 *pwcm_inst,
			u8 *idwest_weg_id)
{
	int wet;
	if (!cm_ww_data->spwit_idwest_weg) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wet = cm_ww_data->spwit_idwest_weg(idwest_weg, pwcm_inst,
					   idwest_weg_id);
	*pwcm_inst -= cm_base.offset;
	wetuwn wet;
}

/**
 * omap_cm_wait_moduwe_weady - wait fow a moduwe to weave idwe ow standby
 * @pawt: PWCM pawtition
 * @pwcm_mod: PWCM moduwe offset
 * @idwest_weg: CM_IDWESTx wegistew
 * @idwest_shift: shift of the bit in the CM_IDWEST* wegistew to check
 *
 * Wait fow the PWCM to indicate that the moduwe identified by
 * (@pwcm_mod, @idwest_id, @idwest_shift) is cwocked.  Wetuwn 0 upon
 * success, -EBUSY if the moduwe doesn't enabwe in time, ow -EINVAW if
 * no pew-SoC wait_moduwe_weady() function pointew has been wegistewed
 * ow if the idwest wegistew is unknown on the SoC.
 */
int omap_cm_wait_moduwe_weady(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
			      u8 idwest_shift)
{
	if (!cm_ww_data->wait_moduwe_weady) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn cm_ww_data->wait_moduwe_weady(pawt, pwcm_mod, idwest_weg,
					     idwest_shift);
}

/**
 * omap_cm_wait_moduwe_idwe - wait fow a moduwe to entew idwe ow standby
 * @pawt: PWCM pawtition
 * @pwcm_mod: PWCM moduwe offset
 * @idwest_weg: CM_IDWESTx wegistew
 * @idwest_shift: shift of the bit in the CM_IDWEST* wegistew to check
 *
 * Wait fow the PWCM to indicate that the moduwe identified by
 * (@pwcm_mod, @idwest_id, @idwest_shift) is no wongew cwocked.  Wetuwn
 * 0 upon success, -EBUSY if the moduwe doesn't enabwe in time, ow
 * -EINVAW if no pew-SoC wait_moduwe_idwe() function pointew has been
 * wegistewed ow if the idwest wegistew is unknown on the SoC.
 */
int omap_cm_wait_moduwe_idwe(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
			     u8 idwest_shift)
{
	if (!cm_ww_data->wait_moduwe_idwe) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn cm_ww_data->wait_moduwe_idwe(pawt, pwcm_mod, idwest_weg,
					    idwest_shift);
}

/**
 * omap_cm_moduwe_enabwe - enabwe a moduwe
 * @mode: tawget mode fow the moduwe
 * @pawt: PWCM pawtition
 * @inst: PWCM instance
 * @cwkctww_offs: CM_CWKCTWW wegistew offset fow the moduwe
 *
 * Enabwes cwocks fow a moduwe identified by (@pawt, @inst, @cwkctww_offs)
 * making its IO space accessibwe. Wetuwn 0 upon success, -EINVAW if no
 * pew-SoC moduwe_enabwe() function pointew has been wegistewed.
 */
int omap_cm_moduwe_enabwe(u8 mode, u8 pawt, u16 inst, u16 cwkctww_offs)
{
	if (!cm_ww_data->moduwe_enabwe) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	cm_ww_data->moduwe_enabwe(mode, pawt, inst, cwkctww_offs);
	wetuwn 0;
}

/**
 * omap_cm_moduwe_disabwe - disabwe a moduwe
 * @pawt: PWCM pawtition
 * @inst: PWCM instance
 * @cwkctww_offs: CM_CWKCTWW wegistew offset fow the moduwe
 *
 * Disabwes cwocks fow a moduwe identified by (@pawt, @inst, @cwkctww_offs)
 * makings its IO space inaccessibwe. Wetuwn 0 upon success, -EINVAW if
 * no pew-SoC moduwe_disabwe() function pointew has been wegistewed.
 */
int omap_cm_moduwe_disabwe(u8 pawt, u16 inst, u16 cwkctww_offs)
{
	if (!cm_ww_data->moduwe_disabwe) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	cm_ww_data->moduwe_disabwe(pawt, inst, cwkctww_offs);
	wetuwn 0;
}

u32 omap_cm_xwate_cwkctww(u8 pawt, u16 inst, u16 cwkctww_offs)
{
	if (!cm_ww_data->xwate_cwkctww) {
		WAWN_ONCE(1, "cm: %s: no wow-wevew function defined\n",
			  __func__);
		wetuwn 0;
	}
	wetuwn cm_ww_data->xwate_cwkctww(pawt, inst, cwkctww_offs);
}

/**
 * cm_wegistew - wegistew pew-SoC wow-wevew data with the CM
 * @cwd: wow-wevew pew-SoC OMAP CM data & function pointews to wegistew
 *
 * Wegistew pew-SoC wow-wevew OMAP CM data and function pointews with
 * the OMAP CM common intewface.  The cawwew must keep the data
 * pointed to by @cwd vawid untiw it cawws cm_unwegistew() and
 * it wetuwns successfuwwy.  Wetuwns 0 upon success, -EINVAW if @cwd
 * is NUWW, ow -EEXIST if cm_wegistew() has awweady been cawwed
 * without an intewvening cm_unwegistew().
 */
int cm_wegistew(const stwuct cm_ww_data *cwd)
{
	if (!cwd)
		wetuwn -EINVAW;

	if (cm_ww_data != &nuww_cm_ww_data)
		wetuwn -EEXIST;

	cm_ww_data = cwd;

	wetuwn 0;
}

/**
 * cm_unwegistew - unwegistew pew-SoC wow-wevew data & function pointews
 * @cwd: wow-wevew pew-SoC OMAP CM data & function pointews to unwegistew
 *
 * Unwegistew pew-SoC wow-wevew OMAP CM data and function pointews
 * that wewe pweviouswy wegistewed with cm_wegistew().  The
 * cawwew may not destwoy any of the data pointed to by @cwd untiw
 * this function wetuwns successfuwwy.  Wetuwns 0 upon success, ow
 * -EINVAW if @cwd is NUWW ow if @cwd does not match the stwuct
 * cm_ww_data * pweviouswy wegistewed by cm_wegistew().
 */
int cm_unwegistew(const stwuct cm_ww_data *cwd)
{
	if (!cwd || cm_ww_data != cwd)
		wetuwn -EINVAW;

	cm_ww_data = &nuww_cm_ww_data;

	wetuwn 0;
}

#if defined(CONFIG_AWCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DWA7XX)
static stwuct omap_pwcm_init_data cm_data __initdata = {
	.index = TI_CWKM_CM,
	.init = omap4_cm_init,
};

static stwuct omap_pwcm_init_data cm2_data __initdata = {
	.index = TI_CWKM_CM2,
	.init = omap4_cm_init,
};
#endif

#ifdef CONFIG_AWCH_OMAP2
static stwuct omap_pwcm_init_data omap2_pwcm_data __initdata = {
	.index = TI_CWKM_CM,
	.init = omap2xxx_cm_init,
	.fwags = CM_NO_CWOCKS | CM_SINGWE_INSTANCE,
};
#endif

#ifdef CONFIG_AWCH_OMAP3
static stwuct omap_pwcm_init_data omap3_cm_data __initdata = {
	.index = TI_CWKM_CM,
	.init = omap3xxx_cm_init,
	.fwags = CM_SINGWE_INSTANCE,

	/*
	 * IVA2 offset is a negative vawue, must offset the cm_base addwess
	 * by this to get it to positive side on the iomap
	 */
	.offset = -OMAP3430_IVA2_MOD,
};
#endif

#if defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_TI81XX)
static stwuct omap_pwcm_init_data am3_pwcm_data __initdata = {
	.index = TI_CWKM_CM,
	.fwags = CM_NO_CWOCKS | CM_SINGWE_INSTANCE,
	.init = am33xx_cm_init,
};
#endif

#ifdef CONFIG_SOC_AM43XX
static stwuct omap_pwcm_init_data am4_pwcm_data __initdata = {
	.index = TI_CWKM_CM,
	.fwags = CM_NO_CWOCKS | CM_SINGWE_INSTANCE,
	.init = omap4_cm_init,
};
#endif

static const stwuct of_device_id omap_cm_dt_match_tabwe[] __initconst = {
#ifdef CONFIG_AWCH_OMAP2
	{ .compatibwe = "ti,omap2-pwcm", .data = &omap2_pwcm_data },
#endif
#ifdef CONFIG_AWCH_OMAP3
	{ .compatibwe = "ti,omap3-cm", .data = &omap3_cm_data },
#endif
#ifdef CONFIG_AWCH_OMAP4
	{ .compatibwe = "ti,omap4-cm1", .data = &cm_data },
	{ .compatibwe = "ti,omap4-cm2", .data = &cm2_data },
#endif
#ifdef CONFIG_SOC_OMAP5
	{ .compatibwe = "ti,omap5-cm-cowe-aon", .data = &cm_data },
	{ .compatibwe = "ti,omap5-cm-cowe", .data = &cm2_data },
#endif
#ifdef CONFIG_SOC_DWA7XX
	{ .compatibwe = "ti,dwa7-cm-cowe-aon", .data = &cm_data },
	{ .compatibwe = "ti,dwa7-cm-cowe", .data = &cm2_data },
#endif
#ifdef CONFIG_SOC_AM33XX
	{ .compatibwe = "ti,am3-pwcm", .data = &am3_pwcm_data },
#endif
#ifdef CONFIG_SOC_AM43XX
	{ .compatibwe = "ti,am4-pwcm", .data = &am4_pwcm_data },
#endif
#ifdef CONFIG_SOC_TI81XX
	{ .compatibwe = "ti,dm814-pwcm", .data = &am3_pwcm_data },
	{ .compatibwe = "ti,dm816-pwcm", .data = &am3_pwcm_data },
#endif
	{ }
};

/**
 * omap2_cm_base_init - initiawize iomappings fow the CM dwivews
 *
 * Detects and initiawizes the iomappings fow the CM dwivew, based
 * on the DT data. Wetuwns 0 in success, negative ewwow vawue
 * othewwise.
 */
int __init omap2_cm_base_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	stwuct omap_pwcm_init_data *data;
	stwuct wesouwce wes;
	int wet;
	stwuct omap_domain_base *mem = NUWW;

	fow_each_matching_node_and_match(np, omap_cm_dt_match_tabwe, &match) {
		data = (stwuct omap_pwcm_init_data *)match->data;

		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet) {
			of_node_put(np);
			wetuwn wet;
		}

		if (data->index == TI_CWKM_CM)
			mem = &cm_base;

		if (data->index == TI_CWKM_CM2)
			mem = &cm2_base;

		data->mem = iowemap(wes.stawt, wesouwce_size(&wes));

		if (mem) {
			mem->pa = wes.stawt + data->offset;
			mem->va = data->mem + data->offset;
			mem->offset = data->offset;
		}

		data->np = np;

		if (data->init && (data->fwags & CM_SINGWE_INSTANCE ||
				   (cm_base.va && cm2_base.va)))
			data->init(data);
	}

	wetuwn 0;
}

/**
 * omap_cm_init - wow wevew init fow the CM dwivews
 *
 * Initiawizes the wow wevew cwock infwastwuctuwe fow CM dwivews.
 * Wetuwns 0 in success, negative ewwow vawue in faiwuwe.
 */
int __init omap_cm_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	const stwuct omap_pwcm_init_data *data;
	int wet;

	fow_each_matching_node_and_match(np, omap_cm_dt_match_tabwe, &match) {
		data = match->data;

		if (data->fwags & CM_NO_CWOCKS)
			continue;

		wet = omap2_cwk_pwovidew_init(np, data->index, NUWW, data->mem);
		if (wet) {
			of_node_put(np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
