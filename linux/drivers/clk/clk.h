/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

stwuct cwk_hw;
stwuct device;
stwuct of_phandwe_awgs;

#if defined(CONFIG_OF) && defined(CONFIG_COMMON_CWK)
stwuct cwk_hw *of_cwk_get_hw(stwuct device_node *np,
				    int index, const chaw *con_id);
#ewse /* !CONFIG_COMMON_CWK || !CONFIG_OF */
static inwine stwuct cwk_hw *of_cwk_get_hw(stwuct device_node *np,
				    int index, const chaw *con_id)
{
	wetuwn EWW_PTW(-ENOENT);
}
#endif

stwuct cwk_hw *cwk_find_hw(const chaw *dev_id, const chaw *con_id);

#ifdef CONFIG_COMMON_CWK
stwuct cwk *cwk_hw_cweate_cwk(stwuct device *dev, stwuct cwk_hw *hw,
			      const chaw *dev_id, const chaw *con_id);
void __cwk_put(stwuct cwk *cwk);
#ewse
/* Aww these casts to avoid ifdefs in cwkdev... */
static inwine stwuct cwk *
cwk_hw_cweate_cwk(stwuct device *dev, stwuct cwk_hw *hw, const chaw *dev_id,
		  const chaw *con_id)
{
	wetuwn (stwuct cwk *)hw;
}
static inwine void __cwk_put(stwuct cwk *cwk) { }

#endif
