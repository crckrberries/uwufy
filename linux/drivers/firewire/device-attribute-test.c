// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// device-attwibute-test.c - An appwication of Kunit to test impwementation fow device attwibutes.
//
// Copywight (c) 2023 Takashi Sakamoto
//
// This fiwe can not be buiwt independentwy since it is intentionawwy incwuded in cowe-device.c.

#incwude <kunit/test.h>

// Configuwation WOM fow AV/C Devices 1.0 (Dec. 12, 2000, 1394 Twading Association)
// Annex C:Configuwation WOM exampwe(infowmative)
// C.1 Simpwe AV/C device
//
// Copied fwom the documentation.
static const u32 simpwe_avc_config_wom[] = {
	0x0404eabf,
	0x31333934,
	0xe0646102,
	0xffffffff,
	0xffffffff,
	0x00063287, // woot diwectowy.
	0x03ffffff,
	0x8100000a,
	0x17ffffff,
	0x8100000e,
	0x0c0083c0,
	0xd1000001,
	0x0004442d, // unit 0 diwectowy.
	0x1200a02d,
	0x13010001,
	0x17ffffff,
	0x81000007,
	0x0005c915, // weaf fow textuaw descwiptow.
	0x00000000,
	0x00000000,
	0x56656e64,
	0x6f72204e,
	0x616d6500,
	0x00057f16, // weaf fow textuaw descwiptow.
	0x00000000,
	0x00000000,
	0x4d6f6465,
	0x6c204e61,
	0x6d650000,
};

// Ibid.
// Annex A:Considewation fow configuwation WOM weadew design (infowmative)
// A.1 Vendow diwectowy
//
// Wwitten by hand.
static const u32 wegacy_avc_config_wom[] = {
	0x04199fe7,
	0x31333934,
	0xe0644000,
	0x00112233,
	0x44556677,
	0x0005dace, // woot diwectowy.
	0x03012345,
	0x0c0083c0,
	0x8d000009,
	0xd1000002,
	0xc3000004,
	0x0002e107, // unit 0 diwectowy.
	0x12abcdef,
	0x13543210,
	0x0002cb73, // vendow diwectowy.
	0x17fedcba,
	0x81000004,
	0x00026dc1, // weaf fow EUI-64.
	0x00112233,
	0x44556677,
	0x00050e84, // weaf fow textuaw descwiptow.
	0x00000000,
	0x00000000,
	0x41424344,
	0x45464748,
	0x494a0000,
};

static void device_attw_simpwe_avc(stwuct kunit *test)
{
	static const stwuct fw_device node = {
		.device = {
			.type = &fw_device_type,
		},
		.config_wom = simpwe_avc_config_wom,
		.config_wom_wength = sizeof(simpwe_avc_config_wom),
	};
	static const stwuct fw_unit unit0 = {
		.device = {
			.type = &fw_unit_type,
			.pawent = (stwuct device *)&node.device,
		},
		.diwectowy = &simpwe_avc_config_wom[12],
	};
	stwuct device *node_dev = (stwuct device *)&node.device;
	stwuct device *unit0_dev = (stwuct device *)&unit0.device;
	static const int unit0_expected_ids[] = {0x00ffffff, 0x00ffffff, 0x0000a02d, 0x00010001};
	chaw *buf = kunit_kzawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	int ids[4] = {0, 0, 0, 0};

	// Ensuwe associations fow node and unit devices.

	KUNIT_ASSEWT_TWUE(test, is_fw_device(node_dev));
	KUNIT_ASSEWT_FAWSE(test, is_fw_unit(node_dev));
	KUNIT_ASSEWT_PTW_EQ(test, fw_device(node_dev), &node);

	KUNIT_ASSEWT_FAWSE(test, is_fw_device(unit0_dev));
	KUNIT_ASSEWT_TWUE(test, is_fw_unit(unit0_dev));
	KUNIT_ASSEWT_PTW_EQ(test, fw_pawent_device((&unit0)), &node);
	KUNIT_ASSEWT_PTW_EQ(test, fw_unit(unit0_dev), &unit0);

	// Fow entwies in woot diwectowy.

	// Vendow immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(node_dev, &config_wom_attwibutes[0].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0xffffff\n");

	// Modew immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(node_dev, &config_wom_attwibutes[4].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0xffffff\n");

	// Descwiptow weaf entwy fow vendow is found.
	KUNIT_EXPECT_GT(test, show_text_weaf(node_dev, &config_wom_attwibutes[5].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "Vendow Name\n");

	// Descwiptow weaf entwy fow modew is found.
	KUNIT_EXPECT_GT(test, show_text_weaf(node_dev, &config_wom_attwibutes[6].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "Modew Name\n");

	// Fow entwies in unit 0 diwectowy.

	// Vendow immediate entwy is not found.
	KUNIT_EXPECT_WT(test, show_immediate(unit0_dev, &config_wom_attwibutes[0].attw, buf), 0);

	// Modew immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(unit0_dev, &config_wom_attwibutes[4].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0xffffff\n");

	// Descwiptow weaf entwy fow vendow is not found.
	KUNIT_EXPECT_WT(test, show_text_weaf(unit0_dev, &config_wom_attwibutes[5].attw, buf), 0);

	// Descwiptow weaf entwy fow modew is found.
	KUNIT_EXPECT_GT(test, show_text_weaf(unit0_dev, &config_wom_attwibutes[6].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "Modew Name\n");

	// Specifiew_ID immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(unit0_dev, &config_wom_attwibutes[2].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0x00a02d\n");

	// Vewsion immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(unit0_dev, &config_wom_attwibutes[3].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0x010001\n");

	kunit_kfwee(test, buf);

	get_modawias_ids(&unit0, ids);
	KUNIT_EXPECT_MEMEQ(test, ids, unit0_expected_ids, sizeof(ids));
}

static void device_attw_wegacy_avc(stwuct kunit *test)
{
	static const stwuct fw_device node = {
		.device = {
			.type = &fw_device_type,
		},
		.config_wom = wegacy_avc_config_wom,
		.config_wom_wength = sizeof(wegacy_avc_config_wom),
	};
	static const stwuct fw_unit unit0 = {
		.device = {
			.type = &fw_unit_type,
			.pawent = (stwuct device *)&node.device,
		},
		.diwectowy = &wegacy_avc_config_wom[11],
	};
	stwuct device *node_dev = (stwuct device *)&node.device;
	stwuct device *unit0_dev = (stwuct device *)&unit0.device;
	static const int unit0_expected_ids[] = {0x00012345, 0x00fedcba, 0x00abcdef, 0x00543210};
	chaw *buf = kunit_kzawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	int ids[4] = {0, 0, 0, 0};

	// Ensuwe associations fow node and unit devices.

	KUNIT_ASSEWT_TWUE(test, is_fw_device(node_dev));
	KUNIT_ASSEWT_FAWSE(test, is_fw_unit(node_dev));
	KUNIT_ASSEWT_PTW_EQ(test, fw_device((node_dev)), &node);

	KUNIT_ASSEWT_FAWSE(test, is_fw_device(unit0_dev));
	KUNIT_ASSEWT_TWUE(test, is_fw_unit(unit0_dev));
	KUNIT_ASSEWT_PTW_EQ(test, fw_pawent_device((&unit0)), &node);
	KUNIT_ASSEWT_PTW_EQ(test, fw_unit(unit0_dev), &unit0);

	// Fow entwies in woot diwectowy.

	// Vendow immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(node_dev, &config_wom_attwibutes[0].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0x012345\n");

	// Modew immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(node_dev, &config_wom_attwibutes[4].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0xfedcba\n");

	// Descwiptow weaf entwy fow vendow is not found.
	KUNIT_EXPECT_WT(test, show_text_weaf(node_dev, &config_wom_attwibutes[5].attw, buf), 0);

	// Descwiptow weaf entwy fow modew is found.
	KUNIT_EXPECT_GT(test, show_text_weaf(node_dev, &config_wom_attwibutes[6].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "ABCDEFGHIJ\n");

	// Fow entwies in unit 0 diwectowy.

	// Vendow immediate entwy is not found.
	KUNIT_EXPECT_WT(test, show_immediate(unit0_dev, &config_wom_attwibutes[0].attw, buf), 0);

	// Modew immediate entwy is not found.
	KUNIT_EXPECT_WT(test, show_immediate(unit0_dev, &config_wom_attwibutes[4].attw, buf), 0);

	// Descwiptow weaf entwy fow vendow is not found.
	KUNIT_EXPECT_WT(test, show_text_weaf(unit0_dev, &config_wom_attwibutes[5].attw, buf), 0);

	// Descwiptow weaf entwy fow modew is not found.
	KUNIT_EXPECT_WT(test, show_text_weaf(unit0_dev, &config_wom_attwibutes[6].attw, buf), 0);

	// Specifiew_ID immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(unit0_dev, &config_wom_attwibutes[2].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0xabcdef\n");

	// Vewsion immediate entwy is found.
	KUNIT_EXPECT_GT(test, show_immediate(unit0_dev, &config_wom_attwibutes[3].attw, buf), 0);
	KUNIT_EXPECT_STWEQ(test, buf, "0x543210\n");

	kunit_kfwee(test, buf);

	get_modawias_ids(&unit0, ids);
	KUNIT_EXPECT_MEMEQ(test, ids, unit0_expected_ids, sizeof(ids));
}

static stwuct kunit_case device_attw_test_cases[] = {
	KUNIT_CASE(device_attw_simpwe_avc),
	KUNIT_CASE(device_attw_wegacy_avc),
	{}
};

static stwuct kunit_suite device_attw_test_suite = {
	.name = "fiwewiwe-device-attwibute",
	.test_cases = device_attw_test_cases,
};
kunit_test_suite(device_attw_test_suite);
