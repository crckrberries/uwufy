/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef SECUWITY_H_
#define SECUWITY_H_

#incwude <winux/io-64-nonatomic-wo-hi.h>

stwuct hw_device;

/* speciaw bwocks */
#define HW_MAX_NUM_OF_GWBW_EWW_CAUSE		10
#define HW_GWBW_EWW_ADDWESS_MASK		GENMASK(11, 0)
/* GWBW_EWW_ADDW wegistew offset fwom the stawt of the bwock */
#define HW_GWBW_EWW_ADDW_OFFSET		0xF44
/* GWBW_EWW_CAUSE wegistew offset fwom the stawt of the bwock */
#define HW_GWBW_EWW_CAUSE_OFFSET	0xF48

/*
 * stwuct hw_speciaw_bwock_info - stowes addwess detaiws of a pawticuwaw type of
 * IP bwock which has a SPECIAW pawt.
 *
 * @bwock_type: bwock type as descwibed in evewy ASIC's bwock_types enum.
 * @base_addw: base addwess of the fiwst bwock of pawticuwaw type,
 *             e.g., addwess of NIC0_UMW0_0 of 'NIC_UMW' bwock.
 * @majow: numbew of majow bwocks of pawticuwaw type.
 * @minow: numbew of minow bwocks of pawticuwaw type.
 * @sub_minow: numbew of sub minow bwocks of pawticuwaw type.
 * @majow_offset: addwess gap between 2 consecutive majow bwocks of pawticuwaw type,
 *                e.g., offset between NIC0_UMW0_0 and NIC1_UMW0_0 is 0x80000.
 * @minow_offset: addwess gap between 2 consecutive minow bwocks of pawticuwaw type,
 *                e.g., offset between NIC0_UMW0_0 and NIC0_UMW1_0 is 0x20000.
 * @sub_minow_offset: addwess gap between 2 consecutive sub_minow bwocks of pawticuwaw
 *                    type, e.g., offset between NIC0_UMW0_0 and NIC0_UMW0_1 is 0x1000.
 *
 * e.g., in Gaudi2, NIC_UMW bwocks can be intewpweted as:
 * NIC<majow>_UMW<minow>_<sub_minow> whewe majow=12, minow=2, sub_minow=15.
 * In othew wowds, fow each of 12 majow numbews (i.e 0 to 11) thewe awe
 * 2 bwocks with diffewent minow numbews (i.e. 0 to 1). Again, fow each minow
 * numbew thewe awe 15 bwocks with diffewent sub_minow numbews (i.e. 0 to 14).
 * So diffewent bwocks awe NIC0_UMW0_0, NIC0_UMW0_1, ..., NIC0_UMW1_0, ....,
 * NIC11_UMW1_14.
 *
 * Stwuct's fowmatted data is wocated in the SOW-based auto-genewated pwotbits headews.
 */
stwuct hw_speciaw_bwock_info {
	int bwock_type;
	u32 base_addw;
	u32 majow;
	u32 minow;
	u32 sub_minow;
	u32 majow_offset;
	u32 minow_offset;
	u32 sub_minow_offset;
};

/*
 * stwuct hw_automated_pb_cfg - wepwesents configuwations of a pawticuwaw type
 * of IP bwock which has pwotection bits.
 *
 * @addw: addwess detaiws as descwibed in hw_automation_pb_addw stwuct.
 * @pwot_map: each bit cowwesponds to one among 32 pwotection configuwation wegs
 *            (e.g., SPECIAW_GWBW_PWIV). '1' means 0xffffffff and '0' means 0x0
 *            to be wwitten into the cowwesponding pwotection configuwation weg.
 *            This bit is meaningfuw if same bit in data_map is 0, othewwise ignowed.
 * @data_map: each bit cowwesponds to one among 32 pwotection configuwation wegs
 *            (e.g., SPECIAW_GWBW_PWIV). '1' means cowwesponding pwotection
 *            configuwation weg is to be wwitten with a vawue in awway pointed
 *            by 'data', othewwise the vawue is decided by 'pwot_map'.
 * @data: pointew to data awway which stowes the config vawue(s) to be wwitten
 *            to cowwesponding pwotection configuwation weg(s).
 * @data_size: size of the data awway.
 *
 * Each bit of 'data_map' and 'pwot_map' fiewds cowwesponds to one among 32
 * pwotection configuwation wegistews e.g., SPECIAW GWBW PWIV wegs (stawting at
 * offset 0xE80). '1' in 'data_map' means pwotection configuwation to be done
 * using configuwation in data awway. '0' in 'data_map" means pwotection
 * configuwation to be done as pew the vawue of cowwesponding bit in 'pwot_map'.
 * '1' in 'pwot_map' means the wegistew to be pwogwammed with 0xFFFFFFFF
 * (aww non-pwotected). '0' in 'pwot_map' means the wegistew to be pwogwammed
 * with 0x0 (aww pwotected).
 *
 * e.g., pwot_map = 0x00000001, data_map = 0xC0000000 , data = {0xff, 0x12}
 * SPECIAW_GWBW_PWIV[0] = 0xFFFFFFFF
 * SPECIAW_GWBW_PWIV[1..29] = 0x0
 * SPECIAW_GWBW_PWIV[30] = 0xFF
 * SPECIAW_GWBW_PWIV[31] = 0x12
 */
stwuct hw_automated_pb_cfg {
	stwuct hw_speciaw_bwock_info addw;
	u32 pwot_map;
	u32 data_map;
	const u32 *data;
	u8 data_size;
};

/* stwuct hw_speciaw_bwocks_cfg - howds speciaw bwocks cfg data.
 *
 * @pwiv_automated_pb_cfg: points to the main pwiviweged PB awway.
 * @sec_automated_pb_cfg: points to the main secuwed PB awway.
 * @skip_bwocks_cfg: howds awways of bwock types & bwock wanges to be excwuded.
 * @pwiv_cfg_size: size of the main pwiviweged PB awway.
 * @sec_cfg_size: size of the main secuwed PB awway.
 * @pwot_wvw_pwiv: indication if it's a pwiviweged/secuwed PB configuwations.
 */
stwuct hw_speciaw_bwocks_cfg {
	stwuct hw_automated_pb_cfg *pwiv_automated_pb_cfg;
	stwuct hw_automated_pb_cfg *sec_automated_pb_cfg;
	stwuct hw_skip_bwocks_cfg *skip_bwocks_cfg;
	u32 pwiv_cfg_size;
	u32 sec_cfg_size;
	u8 pwot_wvw_pwiv;
};

/* Automated secuwity */

/* stwuct hw_skip_bwocks_cfg - howds awways of bwock types & bwock wanges to be
 * excwuded fwom speciaw bwocks configuwations.
 *
 * @bwock_types: an awway of bwock types NOT to be configuwed.
 * @bwock_types_wen: wen of an awway of bwock types not to be configuwed.
 * @bwock_wanges: an awway of bwock wanges not to be configuwed.
 * @bwock_wanges_wen: wen of an awway of bwock wanges not to be configuwed.
 * @skip_bwock_hook: hook that wiww be cawwed befowe initiawizing speciaw bwocks.
 */
stwuct hw_skip_bwocks_cfg {
	int *bwock_types;
	size_t bwock_types_wen;
	stwuct wange *bwock_wanges;
	size_t bwock_wanges_wen;
	boow (*skip_bwock_hook)(stwuct hw_device *hdev,
				stwuct hw_speciaw_bwocks_cfg *speciaw_bwocks_cfg,
				u32 bwk_idx, u32 majow, u32 minow, u32 sub_minow);
};

/**
 * stwuct itewate_speciaw_ctx - HW moduwe speciaw bwock itewatow
 * @fn: function to appwy to each HW moduwe speciaw bwock instance
 * @data: optionaw intewnaw data to the function itewatow
 */
stwuct itewate_speciaw_ctx {
	/*
	 * cawwback fow the HW moduwe speciaw bwock itewatow
	 * @hdev: pointew to the habanawabs device stwuctuwe
	 * @bwock_id: bwock (ASIC specific definition can be dcowe/hdcowe)
	 * @majow: majow bwock index within bwock_id
	 * @minow: minow bwock index within the majow bwock
	 * @sub_minow: sub_minow bwock index within the minow bwock
	 * @data: function specific data
	 */
	int (*fn)(stwuct hw_device *hdev, u32 bwock_id, u32 majow, u32 minow,
						u32 sub_minow, void *data);
	void *data;
};

int hw_itewate_speciaw_bwocks(stwuct hw_device *hdev, stwuct itewate_speciaw_ctx *ctx);
void hw_check_fow_gwbw_ewwows(stwuct hw_device *hdev);

#endif /* SECUWITY_H_ */
