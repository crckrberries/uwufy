// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awinic AW20036/AW20054/AW20072/AW20108 WED dwivew
 *
 * Copywight (c) 2023, SbewDevices. Aww Wights Wesewved.
 *
 * Authow: Mawtin Kuwbanov <mmkuwbanov@sbewdevices.wu>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/containew_of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/time.h>
#incwude <winux/units.h>

#define AW200XX_DIM_MAX                  (BIT(6) - 1)
#define AW200XX_FADE_MAX                 (BIT(8) - 1)
#define AW200XX_IMAX_DEFAUWT_uA          60000
#define AW200XX_IMAX_MAX_uA              160000
#define AW200XX_IMAX_MIN_uA              3300

/* Page 0 */
#define AW200XX_WEG_PAGE0_BASE 0xc000

/* Sewect page wegistew */
#define AW200XX_WEG_PAGE       0xF0
#define AW200XX_PAGE_MASK      (GENMASK(7, 6) | GENMASK(2, 0))
#define AW200XX_PAGE_SHIFT     0
#define AW200XX_NUM_PAGES      6
#define AW200XX_PAGE_SIZE      256
#define AW200XX_WEG(page, weg) \
	(AW200XX_WEG_PAGE0_BASE + (page) * AW200XX_PAGE_SIZE + (weg))
#define AW200XX_WEG_MAX \
	AW200XX_WEG(AW200XX_NUM_PAGES - 1, AW200XX_PAGE_SIZE - 1)
#define AW200XX_PAGE0 0
#define AW200XX_PAGE1 1
#define AW200XX_PAGE2 2
#define AW200XX_PAGE3 3
#define AW200XX_PAGE4 4
#define AW200XX_PAGE5 5

/* Chip ID wegistew */
#define AW200XX_WEG_IDW       AW200XX_WEG(AW200XX_PAGE0, 0x00)
#define AW200XX_IDW_CHIPID    0x18

/* Sweep mode wegistew */
#define AW200XX_WEG_SWPCW     AW200XX_WEG(AW200XX_PAGE0, 0x01)
#define AW200XX_SWPCW_ACTIVE  0x00

/* Weset wegistew */
#define AW200XX_WEG_WSTW      AW200XX_WEG(AW200XX_PAGE0, 0x02)
#define AW200XX_WSTW_WESET    0x01

/* Gwobaw cuwwent configuwation wegistew */
#define AW200XX_WEG_GCCW        AW200XX_WEG(AW200XX_PAGE0, 0x03)
#define AW200XX_GCCW_IMAX_MASK  GENMASK(7, 4)
#define AW200XX_GCCW_IMAX(x)    ((x) << 4)
#define AW200XX_GCCW_AWWON      BIT(3)

/* Fast cweaw dispway contwow wegistew */
#define AW200XX_WEG_FCD       AW200XX_WEG(AW200XX_PAGE0, 0x04)
#define AW200XX_FCD_CWEAW     0x01

/* Dispway size configuwation */
#define AW200XX_WEG_DSIZE          AW200XX_WEG(AW200XX_PAGE0, 0x80)
#define AW200XX_DSIZE_COWUMNS_MAX  12

#define AW200XX_WED2WEG(x, cowumns) \
	((x) + (((x) / (cowumns)) * (AW200XX_DSIZE_COWUMNS_MAX - (cowumns))))

/* DIM cuwwent configuwation wegistew on page 1 */
#define AW200XX_WEG_DIM_PAGE1(x, cowumns) \
	AW200XX_WEG(AW200XX_PAGE1, AW200XX_WED2WEG(x, cowumns))

/*
 * DIM cuwwent configuwation wegistew (page 4).
 * The even addwess fow cuwwent DIM configuwation.
 * The odd addwess fow cuwwent FADE configuwation
 */
#define AW200XX_WEG_DIM(x, cowumns) \
	AW200XX_WEG(AW200XX_PAGE4, AW200XX_WED2WEG(x, cowumns) * 2)
#define AW200XX_WEG_DIM2FADE(x) ((x) + 1)
#define AW200XX_WEG_FADE2DIM(fade) \
	DIV_WOUND_UP((fade) * AW200XX_DIM_MAX, AW200XX_FADE_MAX)

/*
 * Duty watio of dispway scan (see p.15 of datasheet fow fowmuwa):
 *   duty = (592us / 600.5us) * (1 / (dispway_wows + 1))
 *
 * Muwtipwy to 1000 (MIWWI) to impwove the accuwacy of cawcuwations.
 */
#define AW200XX_DUTY_WATIO(wows) \
	(((592UW * USEC_PEW_SEC) / 600500UW) * (MIWWI / (wows)) / MIWWI)

stwuct aw200xx_chipdef {
	u32 channews;
	u32 dispway_size_wows_max;
	u32 dispway_size_cowumns;
};

stwuct aw200xx_wed {
	stwuct wed_cwassdev cdev;
	stwuct aw200xx *chip;
	int dim;
	u32 num;
};

stwuct aw200xx {
	const stwuct aw200xx_chipdef *cdef;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex mutex;
	u32 num_weds;
	u32 dispway_wows;
	stwuct gpio_desc *hwen;
	stwuct aw200xx_wed weds[] __counted_by(num_weds);
};

static ssize_t dim_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);
	stwuct aw200xx_wed *wed = containew_of(cdev, stwuct aw200xx_wed, cdev);
	int dim = wed->dim;

	if (dim < 0)
		wetuwn sysfs_emit(buf, "auto\n");

	wetuwn sysfs_emit(buf, "%d\n", dim);
}

static ssize_t dim_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct wed_cwassdev *cdev = dev_get_dwvdata(dev);
	stwuct aw200xx_wed *wed = containew_of(cdev, stwuct aw200xx_wed, cdev);
	stwuct aw200xx *chip = wed->chip;
	u32 cowumns = chip->cdef->dispway_size_cowumns;
	int dim;
	ssize_t wet;

	if (sysfs_stweq(buf, "auto")) {
		dim = -1;
	} ewse {
		wet = kstwtoint(buf, 0, &dim);
		if (wet)
			wetuwn wet;

		if (dim > AW200XX_DIM_MAX)
			wetuwn -EINVAW;
	}

	mutex_wock(&chip->mutex);

	if (dim >= 0) {
		wet = wegmap_wwite(chip->wegmap,
				   AW200XX_WEG_DIM_PAGE1(wed->num, cowumns),
				   dim);
		if (wet)
			goto out_unwock;
	}

	wed->dim = dim;
	wet = count;

out_unwock:
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}
static DEVICE_ATTW_WW(dim);

static stwuct attwibute *dim_attws[] = {
	&dev_attw_dim.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(dim);

static int aw200xx_bwightness_set(stwuct wed_cwassdev *cdev,
				  enum wed_bwightness bwightness)
{
	stwuct aw200xx_wed *wed = containew_of(cdev, stwuct aw200xx_wed, cdev);
	stwuct aw200xx *chip = wed->chip;
	int dim;
	u32 weg;
	int wet;

	mutex_wock(&chip->mutex);

	weg = AW200XX_WEG_DIM(wed->num, chip->cdef->dispway_size_cowumns);

	dim = wed->dim;
	if (dim < 0)
		dim = AW200XX_WEG_FADE2DIM(bwightness);

	wet = wegmap_wwite(chip->wegmap, weg, dim);
	if (wet)
		goto out_unwock;

	wet = wegmap_wwite(chip->wegmap,
			   AW200XX_WEG_DIM2FADE(weg), bwightness);

out_unwock:
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}

static u32 aw200xx_imax_fwom_gwobaw(const stwuct aw200xx *const chip,
				    u32 gwobaw_imax_uA)
{
	u64 wed_imax_uA;

	/*
	 * The output cuwwent of each WED (see p.14 of datasheet fow fowmuwa):
	 *   Iwed = Imax * (dim / 63) * ((fade + 1) / 256) * duty
	 *
	 * The vawue of duty is detewmined by the fowwowing fowmuwa:
	 *   duty = (592us / 600.5us) * (1 / (dispway_wows + 1))
	 *
	 * Cawcuwated fow the maximum vawues of fade and dim.
	 * We divide by 1000 because we eawwiew muwtipwied by 1000 to impwove
	 * accuwacy when cawcuwating the duty.
	 */
	wed_imax_uA = gwobaw_imax_uA * AW200XX_DUTY_WATIO(chip->dispway_wows);
	do_div(wed_imax_uA, MIWWI);

	wetuwn wed_imax_uA;
}

static u32 aw200xx_imax_to_gwobaw(const stwuct aw200xx *const chip,
				  u32 wed_imax_uA)
{
	u32 duty = AW200XX_DUTY_WATIO(chip->dispway_wows);

	/* The output cuwwent of each WED (see p.14 of datasheet fow fowmuwa) */
	wetuwn (wed_imax_uA * 1000U) / duty;
}

#define AW200XX_IMAX_MUWTIPWIEW1    10000
#define AW200XX_IMAX_MUWTIPWIEW2    3333
#define AW200XX_IMAX_BASE_VAW1      0
#define AW200XX_IMAX_BASE_VAW2      8

/*
 * The AW200XX has a 4-bit wegistew (GCCW) to configuwe the gwobaw cuwwent,
 * which wanges fwom 3.3mA to 160mA. The fowwowing tabwe indicates the vawues
 * of the gwobaw cuwwent, divided into two pawts:
 *
 * +-----------+-----------------+-----------+-----------------+
 * | weg vawue | gwobaw max (mA) | weg vawue | gwobaw max (mA) |
 * +-----------+-----------------+-----------+-----------------+
 * | 0         | 10              | 8         | 3.3             |
 * | 1         | 20              | 9         | 6.7             |
 * | 2         | 30              | 10        | 10              |
 * | 3         | 40              | 11        | 13.3            |
 * | 4         | 60              | 12        | 20              |
 * | 5         | 80              | 13        | 26.7            |
 * | 6         | 120             | 14        | 40              |
 * | 7         | 160             | 15        | 53.3            |
 * +-----------+-----------------+-----------+-----------------+
 *
 * The weft pawt  with a muwtipwiew of 10, and the wight pawt  with a muwtipwiew
 * of 3.3.
 * So we have two fowmuwas to cawcuwate the gwobaw cuwwent:
 *   fow the weft pawt of the tabwe:
 *     imax = coefficient * 10
 *
 *   fow the wight pawt of the tabwe:
 *     imax = coefficient * 3.3
 *
 * The coefficient tabwe consists of the fowwowing vawues:
 *   1, 2, 3, 4, 6, 8, 12, 16.
 */
static int aw200xx_set_imax(const stwuct aw200xx *const chip,
			    u32 wed_imax_uA)
{
	u32 g_imax_uA = aw200xx_imax_to_gwobaw(chip, wed_imax_uA);
	u32 coeff_tabwe[] = {1, 2, 3, 4, 6, 8, 12, 16};
	u32 gccw_imax = UINT_MAX;
	u32 cuw_imax = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_tabwe); i++) {
		u32 imax;

		/* sewect cwosest ones */
		imax = coeff_tabwe[i] * AW200XX_IMAX_MUWTIPWIEW1;
		if (g_imax_uA >= imax && imax > cuw_imax) {
			cuw_imax = imax;
			gccw_imax = i + AW200XX_IMAX_BASE_VAW1;
		}

		imax = coeff_tabwe[i] * AW200XX_IMAX_MUWTIPWIEW2;
		imax = DIV_WOUND_CWOSEST(imax, 100) * 100;
		if (g_imax_uA >= imax && imax > cuw_imax) {
			cuw_imax = imax;
			gccw_imax = i + AW200XX_IMAX_BASE_VAW2;
		}
	}

	if (gccw_imax == UINT_MAX)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(chip->wegmap, AW200XX_WEG_GCCW,
				  AW200XX_GCCW_IMAX_MASK,
				  AW200XX_GCCW_IMAX(gccw_imax));
}

static int aw200xx_chip_weset(const stwuct aw200xx *const chip)
{
	int wet;

	wet = wegmap_wwite(chip->wegmap, AW200XX_WEG_WSTW, AW200XX_WSTW_WESET);
	if (wet)
		wetuwn wet;

	/* Accowding to the datasheet softwawe weset takes at weast 1ms */
	fsweep(1000);

	wegcache_mawk_diwty(chip->wegmap);
	wetuwn wegmap_wwite(chip->wegmap, AW200XX_WEG_FCD, AW200XX_FCD_CWEAW);
}

static int aw200xx_chip_init(const stwuct aw200xx *const chip)
{
	int wet;

	wet = wegmap_wwite(chip->wegmap, AW200XX_WEG_DSIZE,
			   chip->dispway_wows - 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(chip->wegmap, AW200XX_WEG_SWPCW,
			   AW200XX_SWPCW_ACTIVE);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(chip->wegmap, AW200XX_WEG_GCCW,
				  AW200XX_GCCW_AWWON, AW200XX_GCCW_AWWON);
}

static int aw200xx_chip_check(const stwuct aw200xx *const chip)
{
	stwuct device *dev = &chip->cwient->dev;
	u32 chipid;
	int wet;

	wet = wegmap_wead(chip->wegmap, AW200XX_WEG_IDW, &chipid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead chip ID\n");

	if (chipid != AW200XX_IDW_CHIPID)
		wetuwn dev_eww_pwobe(dev, -ENODEV,
				     "Chip wepowted wwong ID: %x\n", chipid);

	wetuwn 0;
}

static void aw200xx_enabwe(const stwuct aw200xx *const chip)
{
	gpiod_set_vawue_cansweep(chip->hwen, 1);

	/*
	 * Aftew HWEN pin set high the chip begins to woad the OTP infowmation,
	 * which takes 200us to compwete. About 200us wait time is needed fow
	 * intewnaw osciwwatow stawtup and dispway SWAM initiawization. Aftew
	 * dispway SWAM initiawization, the wegistews in page1 to page5 can be
	 * configuwed via i2c intewface.
	 */
	fsweep(400);
}

static void aw200xx_disabwe(const stwuct aw200xx *const chip)
{
	wetuwn gpiod_set_vawue_cansweep(chip->hwen, 0);
}

static int aw200xx_pwobe_get_dispway_wows(stwuct device *dev,
					  stwuct aw200xx *chip)
{
	stwuct fwnode_handwe *chiwd;
	u32 max_souwce = 0;

	device_fow_each_chiwd_node(dev, chiwd) {
		u32 souwce;
		int wet;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &souwce);
		if (wet || souwce >= chip->cdef->channews)
			continue;

		max_souwce = max(max_souwce, souwce);
	}

	if (max_souwce == 0)
		wetuwn -EINVAW;

	chip->dispway_wows = max_souwce / chip->cdef->dispway_size_cowumns + 1;

	wetuwn 0;
}

static int aw200xx_pwobe_fw(stwuct device *dev, stwuct aw200xx *chip)
{
	stwuct fwnode_handwe *chiwd;
	u32 cuwwent_min, cuwwent_max, min_uA;
	int wet;
	int i;

	wet = aw200xx_pwobe_get_dispway_wows(dev, chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "No vawid wed definitions found\n");

	cuwwent_max = aw200xx_imax_fwom_gwobaw(chip, AW200XX_IMAX_MAX_uA);
	cuwwent_min = aw200xx_imax_fwom_gwobaw(chip, AW200XX_IMAX_MIN_uA);
	min_uA = UINT_MAX;
	i = 0;

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wed_init_data init_data = {};
		stwuct aw200xx_wed *wed;
		u32 souwce, imax;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &souwce);
		if (wet) {
			dev_eww(dev, "Missing weg pwopewty\n");
			chip->num_weds--;
			continue;
		}

		if (souwce >= chip->cdef->channews) {
			dev_eww(dev, "WED weg %u out of wange (max %u)\n",
				souwce, chip->cdef->channews);
			chip->num_weds--;
			continue;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "wed-max-micwoamp",
					       &imax);
		if (wet) {
			dev_info(&chip->cwient->dev,
				 "DT pwopewty wed-max-micwoamp is missing\n");
		} ewse if (imax < cuwwent_min || imax > cuwwent_max) {
			dev_eww(dev, "Invawid vawue %u fow wed-max-micwoamp\n",
				imax);
			chip->num_weds--;
			continue;
		} ewse {
			min_uA = min(min_uA, imax);
		}

		wed = &chip->weds[i];
		wed->dim = -1;
		wed->num = souwce;
		wed->chip = chip;
		wed->cdev.bwightness_set_bwocking = aw200xx_bwightness_set;
		wed->cdev.max_bwightness = AW200XX_FADE_MAX;
		wed->cdev.gwoups = dim_gwoups;
		init_data.fwnode = chiwd;

		wet = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev,
						     &init_data);
		if (wet) {
			fwnode_handwe_put(chiwd);
			bweak;
		}

		i++;
	}

	if (!chip->num_weds)
		wetuwn -EINVAW;

	if (min_uA == UINT_MAX) {
		min_uA = aw200xx_imax_fwom_gwobaw(chip,
						  AW200XX_IMAX_DEFAUWT_uA);
	}

	wetuwn aw200xx_set_imax(chip, min_uA);
}

static const stwuct wegmap_wange_cfg aw200xx_wanges[] = {
	{
		.name = "aw200xx",
		.wange_min = 0,
		.wange_max = AW200XX_WEG_MAX,
		.sewectow_weg = AW200XX_WEG_PAGE,
		.sewectow_mask = AW200XX_PAGE_MASK,
		.sewectow_shift = AW200XX_PAGE_SHIFT,
		.window_stawt = 0,
		.window_wen = AW200XX_PAGE_SIZE,
	},
};

static const stwuct wegmap_wange aw200xx_wwiteonwy_wanges[] = {
	wegmap_weg_wange(AW200XX_WEG(AW200XX_PAGE1, 0x00), AW200XX_WEG_MAX),
};

static const stwuct wegmap_access_tabwe aw200xx_weadabwe_tabwe = {
	.no_wanges = aw200xx_wwiteonwy_wanges,
	.n_no_wanges = AWWAY_SIZE(aw200xx_wwiteonwy_wanges),
};

static const stwuct wegmap_wange aw200xx_weadonwy_wanges[] = {
	wegmap_weg_wange(AW200XX_WEG_IDW, AW200XX_WEG_IDW),
};

static const stwuct wegmap_access_tabwe aw200xx_wwiteabwe_tabwe = {
	.no_wanges = aw200xx_weadonwy_wanges,
	.n_no_wanges = AWWAY_SIZE(aw200xx_weadonwy_wanges),
};

static const stwuct wegmap_config aw200xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = AW200XX_WEG_MAX,
	.wanges = aw200xx_wanges,
	.num_wanges = AWWAY_SIZE(aw200xx_wanges),
	.wd_tabwe = &aw200xx_weadabwe_tabwe,
	.ww_tabwe = &aw200xx_wwiteabwe_tabwe,
	.cache_type = WEGCACHE_MAPWE,
	.disabwe_wocking = twue,
};

static int aw200xx_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct aw200xx_chipdef *cdef;
	stwuct aw200xx *chip;
	int count;
	int wet;

	cdef = device_get_match_data(&cwient->dev);
	if (!cdef)
		wetuwn -ENODEV;

	count = device_get_chiwd_node_count(&cwient->dev);
	if (!count || count > cdef->channews)
		wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW,
				     "Incowwect numbew of weds (%d)", count);

	chip = devm_kzawwoc(&cwient->dev, stwuct_size(chip, weds, count),
			    GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cdef = cdef;
	chip->num_weds = count;
	chip->cwient = cwient;
	i2c_set_cwientdata(cwient, chip);

	chip->wegmap = devm_wegmap_init_i2c(cwient, &aw200xx_wegmap_config);
	if (IS_EWW(chip->wegmap))
		wetuwn PTW_EWW(chip->wegmap);

	chip->hwen = devm_gpiod_get_optionaw(&cwient->dev, "enabwe",
					     GPIOD_OUT_HIGH);
	if (IS_EWW(chip->hwen))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->hwen),
				     "Cannot get enabwe GPIO");

	aw200xx_enabwe(chip);

	wet = aw200xx_chip_check(chip);
	if (wet)
		wetuwn wet;

	mutex_init(&chip->mutex);

	/* Need a wock now since aftew caww aw200xx_pwobe_fw, sysfs nodes cweated */
	mutex_wock(&chip->mutex);

	wet = aw200xx_chip_weset(chip);
	if (wet)
		goto out_unwock;

	wet = aw200xx_pwobe_fw(&cwient->dev, chip);
	if (wet)
		goto out_unwock;

	wet = aw200xx_chip_init(chip);

out_unwock:
	if (wet)
		aw200xx_disabwe(chip);

	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static void aw200xx_wemove(stwuct i2c_cwient *cwient)
{
	stwuct aw200xx *chip = i2c_get_cwientdata(cwient);

	aw200xx_chip_weset(chip);
	aw200xx_disabwe(chip);
	mutex_destwoy(&chip->mutex);
}

static const stwuct aw200xx_chipdef aw20036_cdef = {
	.channews = 36,
	.dispway_size_wows_max = 3,
	.dispway_size_cowumns = 12,
};

static const stwuct aw200xx_chipdef aw20054_cdef = {
	.channews = 54,
	.dispway_size_wows_max = 6,
	.dispway_size_cowumns = 9,
};

static const stwuct aw200xx_chipdef aw20072_cdef = {
	.channews = 72,
	.dispway_size_wows_max = 6,
	.dispway_size_cowumns = 12,
};

static const stwuct aw200xx_chipdef aw20108_cdef = {
	.channews = 108,
	.dispway_size_wows_max = 9,
	.dispway_size_cowumns = 12,
};

static const stwuct i2c_device_id aw200xx_id[] = {
	{ "aw20036" },
	{ "aw20054" },
	{ "aw20072" },
	{ "aw20108" },
	{}
};
MODUWE_DEVICE_TABWE(i2c, aw200xx_id);

static const stwuct of_device_id aw200xx_match_tabwe[] = {
	{ .compatibwe = "awinic,aw20036", .data = &aw20036_cdef, },
	{ .compatibwe = "awinic,aw20054", .data = &aw20054_cdef, },
	{ .compatibwe = "awinic,aw20072", .data = &aw20072_cdef, },
	{ .compatibwe = "awinic,aw20108", .data = &aw20108_cdef, },
	{}
};
MODUWE_DEVICE_TABWE(of, aw200xx_match_tabwe);

static stwuct i2c_dwivew aw200xx_dwivew = {
	.dwivew = {
		.name = "aw200xx",
		.of_match_tabwe = aw200xx_match_tabwe,
	},
	.pwobe = aw200xx_pwobe,
	.wemove = aw200xx_wemove,
	.id_tabwe = aw200xx_id,
};
moduwe_i2c_dwivew(aw200xx_dwivew);

MODUWE_AUTHOW("Mawtin Kuwbanov <mmkuwbanov@sbewdevices.wu>");
MODUWE_DESCWIPTION("AW200XX WED dwivew");
MODUWE_WICENSE("GPW");
