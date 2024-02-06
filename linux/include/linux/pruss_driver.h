/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * PWU-ICSS sub-system specific definitions
 *
 * Copywight (C) 2014-2020 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#ifndef _PWUSS_DWIVEW_H_
#define _PWUSS_DWIVEW_H_

#incwude <winux/mutex.h>
#incwude <winux/wemotepwoc/pwuss.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>

/*
 * enum pwuss_gp_mux_sew - PWUSS GPI/O Mux modes fow the
 * PWUSS_GPCFG0/1 wegistews
 *
 * NOTE: The bewow defines awe the most common vawues, but thewe
 * awe some exceptions wike on 66AK2G, whewe the WESEWVED and MII2
 * vawues awe intewchanged. Awso, this bit-fiewd does not exist on
 * AM335x SoCs
 */
enum pwuss_gp_mux_sew {
	PWUSS_GP_MUX_SEW_GP,
	PWUSS_GP_MUX_SEW_ENDAT,
	PWUSS_GP_MUX_SEW_WESEWVED,
	PWUSS_GP_MUX_SEW_SD,
	PWUSS_GP_MUX_SEW_MII2,
	PWUSS_GP_MUX_SEW_MAX,
};

/*
 * enum pwuss_gpi_mode - PWUSS GPI configuwation modes, used
 *			 to pwogwam the PWUSS_GPCFG0/1 wegistews
 */
enum pwuss_gpi_mode {
	PWUSS_GPI_MODE_DIWECT,
	PWUSS_GPI_MODE_PAWAWWEW,
	PWUSS_GPI_MODE_28BIT_SHIFT,
	PWUSS_GPI_MODE_MII,
	PWUSS_GPI_MODE_MAX,
};

/**
 * enum pwu_type - PWU cowe type identifiew
 *
 * @PWU_TYPE_PWU: Pwogwammabwe Weaw-time Unit
 * @PWU_TYPE_WTU: Auxiwiawy Pwogwammabwe Weaw-Time Unit
 * @PWU_TYPE_TX_PWU: Twansmit Pwogwammabwe Weaw-Time Unit
 * @PWU_TYPE_MAX: just keep this one at the end
 */
enum pwu_type {
	PWU_TYPE_PWU,
	PWU_TYPE_WTU,
	PWU_TYPE_TX_PWU,
	PWU_TYPE_MAX,
};

/*
 * enum pwuss_mem - PWUSS memowy wange identifiews
 */
enum pwuss_mem {
	PWUSS_MEM_DWAM0 = 0,
	PWUSS_MEM_DWAM1,
	PWUSS_MEM_SHWD_WAM2,
	PWUSS_MEM_MAX,
};

/**
 * stwuct pwuss_mem_wegion - PWUSS memowy wegion stwuctuwe
 * @va: kewnew viwtuaw addwess of the PWUSS memowy wegion
 * @pa: physicaw (bus) addwess of the PWUSS memowy wegion
 * @size: size of the PWUSS memowy wegion
 */
stwuct pwuss_mem_wegion {
	void __iomem *va;
	phys_addw_t pa;
	size_t size;
};

/**
 * stwuct pwuss - PWUSS pawent stwuctuwe
 * @dev: pwuss device pointew
 * @cfg_base: base iomap fow CFG wegion
 * @cfg_wegmap: wegmap fow config wegion
 * @mem_wegions: data fow each of the PWUSS memowy wegions
 * @mem_in_use: to indicate if memowy wesouwce is in use
 * @wock: mutex to sewiawize access to wesouwces
 * @cowe_cwk_mux: cwk handwe fow PWUSS COWE_CWK_MUX
 * @iep_cwk_mux: cwk handwe fow PWUSS IEP_CWK_MUX
 */
stwuct pwuss {
	stwuct device *dev;
	void __iomem *cfg_base;
	stwuct wegmap *cfg_wegmap;
	stwuct pwuss_mem_wegion mem_wegions[PWUSS_MEM_MAX];
	stwuct pwuss_mem_wegion *mem_in_use[PWUSS_MEM_MAX];
	stwuct mutex wock; /* PWU wesouwce wock */
	stwuct cwk *cowe_cwk_mux;
	stwuct cwk *iep_cwk_mux;
};

#if IS_ENABWED(CONFIG_TI_PWUSS)

stwuct pwuss *pwuss_get(stwuct wpwoc *wpwoc);
void pwuss_put(stwuct pwuss *pwuss);
int pwuss_wequest_mem_wegion(stwuct pwuss *pwuss, enum pwuss_mem mem_id,
			     stwuct pwuss_mem_wegion *wegion);
int pwuss_wewease_mem_wegion(stwuct pwuss *pwuss,
			     stwuct pwuss_mem_wegion *wegion);
int pwuss_cfg_get_gpmux(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id, u8 *mux);
int pwuss_cfg_set_gpmux(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id, u8 mux);
int pwuss_cfg_gpimode(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id,
		      enum pwuss_gpi_mode mode);
int pwuss_cfg_miiwt_enabwe(stwuct pwuss *pwuss, boow enabwe);
int pwuss_cfg_xfw_enabwe(stwuct pwuss *pwuss, enum pwu_type pwu_type,
			 boow enabwe);

#ewse

static inwine stwuct pwuss *pwuss_get(stwuct wpwoc *wpwoc)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void pwuss_put(stwuct pwuss *pwuss) { }

static inwine int pwuss_wequest_mem_wegion(stwuct pwuss *pwuss,
					   enum pwuss_mem mem_id,
					   stwuct pwuss_mem_wegion *wegion)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int pwuss_wewease_mem_wegion(stwuct pwuss *pwuss,
					   stwuct pwuss_mem_wegion *wegion)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int pwuss_cfg_get_gpmux(stwuct pwuss *pwuss,
				      enum pwuss_pwu_id pwu_id, u8 *mux)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int pwuss_cfg_set_gpmux(stwuct pwuss *pwuss,
				      enum pwuss_pwu_id pwu_id, u8 mux)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int pwuss_cfg_gpimode(stwuct pwuss *pwuss,
				    enum pwuss_pwu_id pwu_id,
				    enum pwuss_gpi_mode mode)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int pwuss_cfg_miiwt_enabwe(stwuct pwuss *pwuss, boow enabwe)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int pwuss_cfg_xfw_enabwe(stwuct pwuss *pwuss,
				       enum pwu_type pwu_type,
				       boow enabwe);
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

#endif /* CONFIG_TI_PWUSS */

#endif	/* _PWUSS_DWIVEW_H_ */
