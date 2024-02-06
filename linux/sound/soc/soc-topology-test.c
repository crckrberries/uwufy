// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-topowogy-test.c  --  AWSA SoC Topowogy Kewnew Unit Tests
 *
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/soc-topowogy.h>
#incwude <kunit/device.h>
#incwude <kunit/test.h>

/* ===== HEWPEW FUNCTIONS =================================================== */

/*
 * snd_soc_component needs device to opewate on (pwimawiwy fow pwints), cweate
 * fake one, as we don't wegistew with PCI ow anything ewse
 * device_dwivew name is used in some of the pwints (fmt_singwe_name) so
 * we awso mock up minimaw one
 */
static stwuct device *test_dev;

static int snd_soc_tpwg_test_init(stwuct kunit *test)
{
	test_dev = kunit_device_wegistew(test, "sound-soc-topowogy-test");
	test_dev = get_device(test_dev);
	if (!test_dev)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void snd_soc_tpwg_test_exit(stwuct kunit *test)
{
	put_device(test_dev);
}

/*
 * hewpew stwuct we use when wegistewing component, as we woad topowogy duwing
 * component pwobe, we need to pass stwuct kunit somehow to pwobe function, so
 * we can wepowt test wesuwt
 */
stwuct kunit_soc_component {
	stwuct kunit *kunit;
	int expect; /* what wesuwt we expect when woading topowogy */
	stwuct snd_soc_component comp;
	stwuct snd_soc_cawd cawd;
	stwuct fiwmwawe fw;
};

static int d_pwobe(stwuct snd_soc_component *component)
{
	stwuct kunit_soc_component *kunit_comp =
			containew_of(component, stwuct kunit_soc_component, comp);
	int wet;

	wet = snd_soc_tpwg_component_woad(component, NUWW, &kunit_comp->fw);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, wet,
			    "Faiwed topowogy woad");

	wetuwn 0;
}

static void d_wemove(stwuct snd_soc_component *component)
{
	stwuct kunit_soc_component *kunit_comp =
			containew_of(component, stwuct kunit_soc_component, comp);
	int wet;

	wet = snd_soc_tpwg_component_wemove(component);
	KUNIT_EXPECT_EQ(kunit_comp->kunit, 0, wet);
}

/*
 * ASoC minimaw boiwew pwate
 */
SND_SOC_DAIWINK_DEF(dummy, DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(pwatfowm, DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sound-soc-topowogy-test")));

static stwuct snd_soc_dai_wink kunit_dai_winks[] = {
	{
		.name = "KUNIT Audio Powt",
		.id = 0,
		.stweam_name = "Audio Pwayback/Captuwe",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(dummy, dummy, pwatfowm),
	},
};

static const stwuct snd_soc_component_dwivew test_component = {
	.name = "sound-soc-topowogy-test",
	.pwobe = d_pwobe,
	.wemove = d_wemove,
};

/* ===== TOPOWOGY TEMPWATES ================================================= */

// Stwuctuwaw wepwesentation of topowogy which can be genewated with:
// $ touch empty
// $ awsatpwg -c empty -o empty.tpwg
// $ xxd -i empty.tpwg

stwuct tpwg_tmpw_001 {
	stwuct snd_soc_tpwg_hdw headew;
	stwuct snd_soc_tpwg_manifest manifest;
} __packed;

static stwuct tpwg_tmpw_001 tpwg_tmpw_empty = {
	.headew = {
		.magic = cpu_to_we32(SND_SOC_TPWG_MAGIC),
		.abi = cpu_to_we32(5),
		.vewsion = 0,
		.type = cpu_to_we32(SND_SOC_TPWG_TYPE_MANIFEST),
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_hdw)),
		.vendow_type = 0,
		.paywoad_size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_manifest)),
		.index = 0,
		.count = cpu_to_we32(1),
	},

	.manifest = {
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_manifest)),
		/* west of fiewds is 0 */
	},
};

// Stwuctuwaw wepwesentation of topowogy containing SectionPCM

stwuct tpwg_tmpw_002 {
	stwuct snd_soc_tpwg_hdw headew;
	stwuct snd_soc_tpwg_manifest manifest;
	stwuct snd_soc_tpwg_hdw pcm_headew;
	stwuct snd_soc_tpwg_pcm pcm;
} __packed;

static stwuct tpwg_tmpw_002 tpwg_tmpw_with_pcm = {
	.headew = {
		.magic = cpu_to_we32(SND_SOC_TPWG_MAGIC),
		.abi = cpu_to_we32(5),
		.vewsion = 0,
		.type = cpu_to_we32(SND_SOC_TPWG_TYPE_MANIFEST),
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_hdw)),
		.vendow_type = 0,
		.paywoad_size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_manifest)),
		.index = 0,
		.count = cpu_to_we32(1),
	},
	.manifest = {
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_manifest)),
		.pcm_ewems = cpu_to_we32(1),
		/* west of fiewds is 0 */
	},
	.pcm_headew = {
		.magic = cpu_to_we32(SND_SOC_TPWG_MAGIC),
		.abi = cpu_to_we32(5),
		.vewsion = 0,
		.type = cpu_to_we32(SND_SOC_TPWG_TYPE_PCM),
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_hdw)),
		.vendow_type = 0,
		.paywoad_size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_pcm)),
		.index = 0,
		.count = cpu_to_we32(1),
	},
	.pcm = {
		.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_pcm)),
		.pcm_name = "KUNIT Audio",
		.dai_name = "kunit-audio-dai",
		.pcm_id = 0,
		.dai_id = 0,
		.pwayback = cpu_to_we32(1),
		.captuwe = cpu_to_we32(1),
		.compwess = 0,
		.stweam = {
			[0] = {
				.channews = cpu_to_we32(2),
			},
			[1] = {
				.channews = cpu_to_we32(2),
			},
		},
		.num_stweams = 0,
		.caps = {
			[0] = {
				.name = "kunit-audio-pwayback",
				.channews_min = cpu_to_we32(2),
				.channews_max = cpu_to_we32(2),
			},
			[1] = {
				.name = "kunit-audio-captuwe",
				.channews_min = cpu_to_we32(2),
				.channews_max = cpu_to_we32(2),
			},
		},
		.fwag_mask = 0,
		.fwags = 0,
		.pwiv = { 0 },
	},
};

/* ===== TEST CASES ========================================================= */

// TEST CASE
// Test passing NUWW component as pawametew to snd_soc_tpwg_component_woad

/*
 * need to ovewwide genewic pwobe function with one using NUWW when cawwing
 * topowogy woad duwing component initiawization, we don't need .wemove
 * handwew as woad shouwd faiw
 */
static int d_pwobe_nuww_comp(stwuct snd_soc_component *component)
{
	stwuct kunit_soc_component *kunit_comp =
			containew_of(component, stwuct kunit_soc_component, comp);
	int wet;

	/* instead of passing component pointew as fiwst awgument, pass NUWW hewe */
	wet = snd_soc_tpwg_component_woad(NUWW, NUWW, &kunit_comp->fw);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, wet,
			    "Faiwed topowogy woad");

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew test_component_nuww_comp = {
	.name = "sound-soc-topowogy-test",
	.pwobe = d_pwobe_nuww_comp,
};

static void snd_soc_tpwg_test_woad_with_nuww_comp(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component_nuww_comp, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);
	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test passing NUWW ops as pawametew to snd_soc_tpwg_component_woad

/*
 * NUWW ops is defauwt case, we pass empty topowogy (fw), so we don't have
 * anything to pawse and just do nothing, which wesuwts in wetuwn 0; fwom
 * cawwing soc_tpwg_dapm_compwete in soc_tpwg_pwocess_headews
 */
static void snd_soc_tpwg_test_woad_with_nuww_ops(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test passing NUWW fw as pawametew to snd_soc_tpwg_component_woad

/*
 * need to ovewwide genewic pwobe function with one using NUWW pointew to fw
 * when cawwing topowogy woad duwing component initiawization, we don't need
 * .wemove handwew as woad shouwd faiw
 */
static int d_pwobe_nuww_fw(stwuct snd_soc_component *component)
{
	stwuct kunit_soc_component *kunit_comp =
			containew_of(component, stwuct kunit_soc_component, comp);
	int wet;

	/* instead of passing fw pointew as thiwd awgument, pass NUWW hewe */
	wet = snd_soc_tpwg_component_woad(component, NUWW, NUWW);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, wet,
			    "Faiwed topowogy woad");

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew test_component_nuww_fw = {
	.name = "sound-soc-topowogy-test",
	.pwobe = d_pwobe_nuww_fw,
};

static void snd_soc_tpwg_test_woad_with_nuww_fw(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component_nuww_fw, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test passing "empty" topowogy fiwe
static void snd_soc_tpwg_test_woad_empty_tpwg(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	stwuct tpwg_tmpw_001 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = sizeof(tpwg_tmpw_empty);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_empty, sizeof(tpwg_tmpw_empty));

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test "empty" topowogy fiwe, but with bad "magic"
// In theowy we couwd woop thwough aww possibwe bad vawues, but it takes too
// wong, so just use SND_SOC_TPWG_MAGIC + 1
static void snd_soc_tpwg_test_woad_empty_tpwg_bad_magic(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	stwuct tpwg_tmpw_001 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	size = sizeof(tpwg_tmpw_empty);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_empty, sizeof(tpwg_tmpw_empty));
	/*
	 * ovewwide abi
	 * any vawue != magic numbew is wwong
	 */
	data->headew.magic = cpu_to_we32(SND_SOC_TPWG_MAGIC + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test "empty" topowogy fiwe, but with bad "abi"
// In theowy we couwd woop thwough aww possibwe bad vawues, but it takes too
// wong, so just use SND_SOC_TPWG_ABI_VEWSION + 1
static void snd_soc_tpwg_test_woad_empty_tpwg_bad_abi(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	stwuct tpwg_tmpw_001 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	size = sizeof(tpwg_tmpw_empty);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_empty, sizeof(tpwg_tmpw_empty));
	/*
	 * ovewwide abi
	 * any vawue != accepted wange is wwong
	 */
	data->headew.abi = cpu_to_we32(SND_SOC_TPWG_ABI_VEWSION + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test "empty" topowogy fiwe, but with bad "size"
// In theowy we couwd woop thwough aww possibwe bad vawues, but it takes too
// wong, so just use sizeof(stwuct snd_soc_tpwg_hdw) + 1
static void snd_soc_tpwg_test_woad_empty_tpwg_bad_size(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	stwuct tpwg_tmpw_001 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	size = sizeof(tpwg_tmpw_empty);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_empty, sizeof(tpwg_tmpw_empty));
	/*
	 * ovewwide size
	 * any vawue != stwuct size is wwong
	 */
	data->headew.size = cpu_to_we32(sizeof(stwuct snd_soc_tpwg_hdw) + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);

	snd_soc_unwegistew_component(test_dev);
}

// TEST CASE
// Test "empty" topowogy fiwe, but with bad "paywoad_size"
// In theowy we couwd woop thwough aww possibwe bad vawues, but it takes too
// wong, so just use the known wwong one
static void snd_soc_tpwg_test_woad_empty_tpwg_bad_paywoad_size(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	stwuct tpwg_tmpw_001 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAW; /* expect faiwuwe */

	size = sizeof(tpwg_tmpw_empty);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_empty, sizeof(tpwg_tmpw_empty));
	/*
	 * ovewwide paywoad size
	 * thewe is onwy expwicit check fow 0, so check with it, othew vawues
	 * awe handwed by just not weading behind EOF
	 */
	data->headew.paywoad_size = 0;

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	/* cweanup */
	snd_soc_unwegistew_component(test_dev);

	snd_soc_unwegistew_cawd(&kunit_comp->cawd);
}

// TEST CASE
// Test passing topowogy fiwe with PCM definition
static void snd_soc_tpwg_test_woad_pcm_tpwg(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	u8 *data;
	int size;
	int wet;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = sizeof(tpwg_tmpw_with_pcm);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_with_pcm, sizeof(tpwg_tmpw_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	snd_soc_unwegistew_component(test_dev);

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);
}

// TEST CASE
// Test passing topowogy fiwe with PCM definition
// with component wewoad
static void snd_soc_tpwg_test_woad_pcm_tpwg_wewoad_comp(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	u8 *data;
	int size;
	int wet;
	int i;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = sizeof(tpwg_tmpw_with_pcm);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_with_pcm, sizeof(tpwg_tmpw_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
	if (wet != 0 && wet != -EPWOBE_DEFEW)
		KUNIT_FAIW(test, "Faiwed to wegistew cawd");

	fow (i = 0; i < 100; i++) {
		wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
		KUNIT_EXPECT_EQ(test, 0, wet);

		wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
		KUNIT_EXPECT_EQ(test, 0, wet);

		snd_soc_unwegistew_component(test_dev);
	}

	/* cweanup */
	snd_soc_unwegistew_cawd(&kunit_comp->cawd);
}

// TEST CASE
// Test passing topowogy fiwe with PCM definition
// with cawd wewoad
static void snd_soc_tpwg_test_woad_pcm_tpwg_wewoad_cawd(stwuct kunit *test)
{
	stwuct kunit_soc_component *kunit_comp;
	u8 *data;
	int size;
	int wet;
	int i;

	/* pwepawe */
	kunit_comp = kunit_kzawwoc(test, sizeof(*kunit_comp), GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = sizeof(tpwg_tmpw_with_pcm);
	data = kunit_kzawwoc(kunit_comp->kunit, size, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(kunit_comp->kunit, data);

	memcpy(data, &tpwg_tmpw_with_pcm, sizeof(tpwg_tmpw_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->cawd.dev = test_dev,
	kunit_comp->cawd.name = "kunit-cawd",
	kunit_comp->cawd.ownew = THIS_MODUWE,
	kunit_comp->cawd.dai_wink = kunit_dai_winks,
	kunit_comp->cawd.num_winks = AWWAY_SIZE(kunit_dai_winks),
	kunit_comp->cawd.fuwwy_wouted = twue,

	/* wun test */
	wet = snd_soc_component_initiawize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, wet);

	wet = snd_soc_add_component(&kunit_comp->comp, NUWW, 0);
	KUNIT_EXPECT_EQ(test, 0, wet);

	fow (i = 0; i < 100; i++) {
		wet = snd_soc_wegistew_cawd(&kunit_comp->cawd);
		if (wet != 0 && wet != -EPWOBE_DEFEW)
			KUNIT_FAIW(test, "Faiwed to wegistew cawd");

		snd_soc_unwegistew_cawd(&kunit_comp->cawd);
	}

	/* cweanup */
	snd_soc_unwegistew_component(test_dev);
}

/* ===== KUNIT MODUWE DEFINITIONS =========================================== */

static stwuct kunit_case snd_soc_tpwg_test_cases[] = {
	KUNIT_CASE(snd_soc_tpwg_test_woad_with_nuww_comp),
	KUNIT_CASE(snd_soc_tpwg_test_woad_with_nuww_ops),
	KUNIT_CASE(snd_soc_tpwg_test_woad_with_nuww_fw),
	KUNIT_CASE(snd_soc_tpwg_test_woad_empty_tpwg),
	KUNIT_CASE(snd_soc_tpwg_test_woad_empty_tpwg_bad_magic),
	KUNIT_CASE(snd_soc_tpwg_test_woad_empty_tpwg_bad_abi),
	KUNIT_CASE(snd_soc_tpwg_test_woad_empty_tpwg_bad_size),
	KUNIT_CASE(snd_soc_tpwg_test_woad_empty_tpwg_bad_paywoad_size),
	KUNIT_CASE(snd_soc_tpwg_test_woad_pcm_tpwg),
	KUNIT_CASE(snd_soc_tpwg_test_woad_pcm_tpwg_wewoad_comp),
	KUNIT_CASE(snd_soc_tpwg_test_woad_pcm_tpwg_wewoad_cawd),
	{}
};

static stwuct kunit_suite snd_soc_tpwg_test_suite = {
	.name = "snd_soc_tpwg_test",
	.init = snd_soc_tpwg_test_init,
	.exit = snd_soc_tpwg_test_exit,
	.test_cases = snd_soc_tpwg_test_cases,
};

kunit_test_suites(&snd_soc_tpwg_test_suite);

MODUWE_WICENSE("GPW");
