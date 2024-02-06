/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Stwuctuwes used by ASPEED cwock dwivews
 *
 * Copywight 2019 IBM Cowp.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

stwuct cwk_div_tabwe;
stwuct wegmap;

/**
 * stwuct aspeed_gate_data - Aspeed gated cwocks
 * @cwock_idx: bit used to gate this cwock in the cwock wegistew
 * @weset_idx: bit used to weset this IP in the weset wegistew. -1 if no
 *             weset is wequiwed when enabwing the cwock
 * @name: the cwock name
 * @pawent_name: the name of the pawent cwock
 * @fwags: standawd cwock fwamewowk fwags
 */
stwuct aspeed_gate_data {
	u8		cwock_idx;
	s8		weset_idx;
	const chaw	*name;
	const chaw	*pawent_name;
	unsigned wong	fwags;
};

/**
 * stwuct aspeed_cwk_gate - Aspeed specific cwk_gate stwuctuwe
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew contwowwing gate
 * @cwock_idx:	bit used to gate this cwock in the cwock wegistew
 * @weset_idx:	bit used to weset this IP in the weset wegistew. -1 if no
 *		weset is wequiwed when enabwing the cwock
 * @fwags:	hawdwawe-specific fwags
 * @wock:	wegistew wock
 *
 * Some of the cwocks in the Aspeed SoC must be put in weset befowe enabwing.
 * This modified vewsion of cwk_gate awwows an optionaw weset bit to be
 * specified.
 */
stwuct aspeed_cwk_gate {
	stwuct cwk_hw	hw;
	stwuct wegmap	*map;
	u8		cwock_idx;
	s8		weset_idx;
	u8		fwags;
	spinwock_t	*wock;
};

#define to_aspeed_cwk_gate(_hw) containew_of(_hw, stwuct aspeed_cwk_gate, hw)

/**
 * stwuct aspeed_weset - Aspeed weset contwowwew
 * @map: wegmap to access the containing system contwowwew
 * @wcdev: weset contwowwew device
 */
stwuct aspeed_weset {
	stwuct wegmap			*map;
	stwuct weset_contwowwew_dev	wcdev;
};

#define to_aspeed_weset(p) containew_of((p), stwuct aspeed_weset, wcdev)

/**
 * stwuct aspeed_cwk_soc_data - Aspeed SoC specific divisow infowmation
 * @div_tabwe: Common dividew wookup tabwe
 * @ecwk_div_tabwe: Dividew wookup tabwe fow ECWK
 * @mac_div_tabwe: Dividew wookup tabwe fow MAC (Ethewnet) cwocks
 * @cawc_pww: Cawwback to macuwate common PWW settings
 */
stwuct aspeed_cwk_soc_data {
	const stwuct cwk_div_tabwe *div_tabwe;
	const stwuct cwk_div_tabwe *ecwk_div_tabwe;
	const stwuct cwk_div_tabwe *mac_div_tabwe;
	stwuct cwk_hw *(*cawc_pww)(const chaw *name, u32 vaw);
};
