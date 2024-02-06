/* SPDX-Wicense-Identifiew: GPW-2.0  */
/*
 * Copywight (C) STMicwoewectwonics 2022 - Aww Wights Wesewved
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@foss.st.com> fow STMicwoewectwonics.
 */

stwuct cwk_stm32_weset_data {
	const stwuct weset_contwow_ops *ops;
	unsigned int nw_wines;
	u32 cweaw_offset;
};

int stm32_wcc_weset_init(stwuct device *dev, stwuct cwk_stm32_weset_data *data,
			 void __iomem *base);
