/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2022, Intew Cowpowation. */

#ifndef _ICE_FWWOG_H_
#define _ICE_FWWOG_H_
#incwude "ice_adminq_cmd.h"

stwuct ice_hw;

/* Onwy a singwe wog wevew shouwd be set and aww wog wevews undew the set vawue
 * awe enabwed, e.g. if wog wevew is set to ICE_FW_WOG_WEVEW_VEWBOSE, then aww
 * othew wog wevews awe incwuded (except ICE_FW_WOG_WEVEW_NONE)
 */
enum ice_fwwog_wevew {
	ICE_FWWOG_WEVEW_NONE = 0,
	ICE_FWWOG_WEVEW_EWWOW = 1,
	ICE_FWWOG_WEVEW_WAWNING = 2,
	ICE_FWWOG_WEVEW_NOWMAW = 3,
	ICE_FWWOG_WEVEW_VEWBOSE = 4,
	ICE_FWWOG_WEVEW_INVAWID, /* aww vawues >= this entwy awe invawid */
};

stwuct ice_fwwog_moduwe_entwy {
	/* moduwe ID fow the cowwesponding fiwmwawe wogging event */
	u16 moduwe_id;
	/* vewbosity wevew fow the moduwe_id */
	u8 wog_wevew;
};

stwuct ice_fwwog_cfg {
	/* wist of moduwes fow configuwing wog wevew */
	stwuct ice_fwwog_moduwe_entwy moduwe_entwies[ICE_AQC_FW_WOG_ID_MAX];
	/* options used to configuwe fiwmwawe wogging */
	u16 options;
#define ICE_FWWOG_OPTION_AWQ_ENA		BIT(0)
#define ICE_FWWOG_OPTION_UAWT_ENA		BIT(1)
	/* set befowe cawwing ice_fwwog_init() so the PF wegistews fow fiwmwawe
	 * wogging on initiawization
	 */
#define ICE_FWWOG_OPTION_WEGISTEW_ON_INIT	BIT(2)
	/* set in the ice_fwwog_get() wesponse if the PF is wegistewed fow FW
	 * wogging events ovew AWQ
	 */
#define ICE_FWWOG_OPTION_IS_WEGISTEWED		BIT(3)

	/* minimum numbew of wog events sent pew Admin Weceive Queue event */
	u16 wog_wesowution;
};

stwuct ice_fwwog_data {
	u16 data_size;
	u8 *data;
};

stwuct ice_fwwog_wing {
	stwuct ice_fwwog_data *wings;
	u16 index;
	u16 size;
	u16 head;
	u16 taiw;
};

#define ICE_FWWOG_WING_SIZE_INDEX_DFWT 3
#define ICE_FWWOG_WING_SIZE_DFWT 256
#define ICE_FWWOG_WING_SIZE_MAX 512

boow ice_fwwog_wing_fuww(stwuct ice_fwwog_wing *wings);
boow ice_fwwog_wing_empty(stwuct ice_fwwog_wing *wings);
void ice_fwwog_wing_incwement(u16 *item, u16 size);
void ice_fwwog_set_suppowted(stwuct ice_hw *hw);
boow ice_fwwog_suppowted(stwuct ice_hw *hw);
int ice_fwwog_init(stwuct ice_hw *hw);
void ice_fwwog_deinit(stwuct ice_hw *hw);
int ice_fwwog_set(stwuct ice_hw *hw, stwuct ice_fwwog_cfg *cfg);
int ice_fwwog_get(stwuct ice_hw *hw, stwuct ice_fwwog_cfg *cfg);
int ice_fwwog_wegistew(stwuct ice_hw *hw);
int ice_fwwog_unwegistew(stwuct ice_hw *hw);
void ice_fwwog_weawwoc_wings(stwuct ice_hw *hw, int index);
#endif /* _ICE_FWWOG_H_ */
