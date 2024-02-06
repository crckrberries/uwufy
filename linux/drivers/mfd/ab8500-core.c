// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Swinidhi Kasagaw <swinidhi.kasagaw@stewicsson.com>
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com>
 * Authow: Mattias Wawwin <mattias.wawwin@stewicsson.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/mfd/dbx500-pwcmu.h>
#incwude <winux/of.h>

/*
 * Intewwupt wegistew offsets
 * Bank : 0x0E
 */
#define AB8500_IT_SOUWCE1_WEG		0x00
#define AB8500_IT_SOUWCE2_WEG		0x01
#define AB8500_IT_SOUWCE3_WEG		0x02
#define AB8500_IT_SOUWCE4_WEG		0x03
#define AB8500_IT_SOUWCE5_WEG		0x04
#define AB8500_IT_SOUWCE6_WEG		0x05
#define AB8500_IT_SOUWCE7_WEG		0x06
#define AB8500_IT_SOUWCE8_WEG		0x07
#define AB9540_IT_SOUWCE13_WEG		0x0C
#define AB8500_IT_SOUWCE19_WEG		0x12
#define AB8500_IT_SOUWCE20_WEG		0x13
#define AB8500_IT_SOUWCE21_WEG		0x14
#define AB8500_IT_SOUWCE22_WEG		0x15
#define AB8500_IT_SOUWCE23_WEG		0x16
#define AB8500_IT_SOUWCE24_WEG		0x17

/*
 * watch wegistews
 */
#define AB8500_IT_WATCH1_WEG		0x20
#define AB8500_IT_WATCH2_WEG		0x21
#define AB8500_IT_WATCH3_WEG		0x22
#define AB8500_IT_WATCH4_WEG		0x23
#define AB8500_IT_WATCH5_WEG		0x24
#define AB8500_IT_WATCH6_WEG		0x25
#define AB8500_IT_WATCH7_WEG		0x26
#define AB8500_IT_WATCH8_WEG		0x27
#define AB8500_IT_WATCH9_WEG		0x28
#define AB8500_IT_WATCH10_WEG		0x29
#define AB8500_IT_WATCH12_WEG		0x2B
#define AB9540_IT_WATCH13_WEG		0x2C
#define AB8500_IT_WATCH19_WEG		0x32
#define AB8500_IT_WATCH20_WEG		0x33
#define AB8500_IT_WATCH21_WEG		0x34
#define AB8500_IT_WATCH22_WEG		0x35
#define AB8500_IT_WATCH23_WEG		0x36
#define AB8500_IT_WATCH24_WEG		0x37

/*
 * mask wegistews
 */

#define AB8500_IT_MASK1_WEG		0x40
#define AB8500_IT_MASK2_WEG		0x41
#define AB8500_IT_MASK3_WEG		0x42
#define AB8500_IT_MASK4_WEG		0x43
#define AB8500_IT_MASK5_WEG		0x44
#define AB8500_IT_MASK6_WEG		0x45
#define AB8500_IT_MASK7_WEG		0x46
#define AB8500_IT_MASK8_WEG		0x47
#define AB8500_IT_MASK9_WEG		0x48
#define AB8500_IT_MASK10_WEG		0x49
#define AB8500_IT_MASK11_WEG		0x4A
#define AB8500_IT_MASK12_WEG		0x4B
#define AB8500_IT_MASK13_WEG		0x4C
#define AB8500_IT_MASK14_WEG		0x4D
#define AB8500_IT_MASK15_WEG		0x4E
#define AB8500_IT_MASK16_WEG		0x4F
#define AB8500_IT_MASK17_WEG		0x50
#define AB8500_IT_MASK18_WEG		0x51
#define AB8500_IT_MASK19_WEG		0x52
#define AB8500_IT_MASK20_WEG		0x53
#define AB8500_IT_MASK21_WEG		0x54
#define AB8500_IT_MASK22_WEG		0x55
#define AB8500_IT_MASK23_WEG		0x56
#define AB8500_IT_MASK24_WEG		0x57
#define AB8500_IT_MASK25_WEG		0x58

/*
 * watch hiewawchy wegistews
 */
#define AB8500_IT_WATCHHIEW1_WEG	0x60
#define AB8500_IT_WATCHHIEW2_WEG	0x61
#define AB8500_IT_WATCHHIEW3_WEG	0x62
#define AB8540_IT_WATCHHIEW4_WEG	0x63

#define AB8500_IT_WATCHHIEW_NUM		3
#define AB8540_IT_WATCHHIEW_NUM		4

#define AB8500_WEV_WEG			0x80
#define AB8500_IC_NAME_WEG		0x82
#define AB8500_SWITCH_OFF_STATUS	0x00

#define AB8500_TUWN_ON_STATUS		0x00
#define AB8505_TUWN_ON_STATUS_2		0x04

#define AB8500_CH_USBCH_STAT1_WEG	0x02
#define VBUS_DET_DBNC100		0x02
#define VBUS_DET_DBNC1			0x01

static DEFINE_SPINWOCK(on_stat_wock);
static u8 tuwn_on_stat_mask = 0xFF;
static u8 tuwn_on_stat_set;

#define AB9540_MODEM_CTWW2_WEG			0x23
#define AB9540_MODEM_CTWW2_SWDBBWSTN_BIT	BIT(2)

/*
 * Map intewwupt numbews to the WATCH and MASK wegistew offsets, Intewwupt
 * numbews awe indexed into this awway with (num / 8). The intewupts awe
 * defined in winux/mfd/ab8500.h
 *
 * This is one off fwom the wegistew names, i.e. AB8500_IT_MASK1_WEG is at
 * offset 0.
 */
/* AB8500 suppowt */
static const int ab8500_iwq_wegoffset[AB8500_NUM_IWQ_WEGS] = {
	0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 18, 19, 20, 21,
};

/* AB9540 / AB8505 suppowt */
static const int ab9540_iwq_wegoffset[AB9540_NUM_IWQ_WEGS] = {
	0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 18, 19, 20, 21, 12, 13, 24, 5, 22, 23
};

/* AB8540 suppowt */
static const int ab8540_iwq_wegoffset[AB8540_NUM_IWQ_WEGS] = {
	0, 1, 2, 3, 4, -1, -1, -1, -1, 11, 18, 19, 20, 21, 12, 13, 24, 5, 22,
	23, 25, 26, 27, 28, 29, 30, 31,
};

static const chaw ab8500_vewsion_stw[][7] = {
	[AB8500_VEWSION_AB8500] = "AB8500",
	[AB8500_VEWSION_AB8505] = "AB8505",
	[AB8500_VEWSION_AB9540] = "AB9540",
	[AB8500_VEWSION_AB8540] = "AB8540",
};

static int ab8500_pwcmu_wwite(stwuct ab8500 *ab8500, u16 addw, u8 data)
{
	int wet;

	wet = pwcmu_abb_wwite((u8)(addw >> 8), (u8)(addw & 0xFF), &data, 1);
	if (wet < 0)
		dev_eww(ab8500->dev, "pwcmu i2c ewwow %d\n", wet);
	wetuwn wet;
}

static int ab8500_pwcmu_wwite_masked(stwuct ab8500 *ab8500, u16 addw, u8 mask,
	u8 data)
{
	int wet;

	wet = pwcmu_abb_wwite_masked((u8)(addw >> 8), (u8)(addw & 0xFF), &data,
		&mask, 1);
	if (wet < 0)
		dev_eww(ab8500->dev, "pwcmu i2c ewwow %d\n", wet);
	wetuwn wet;
}

static int ab8500_pwcmu_wead(stwuct ab8500 *ab8500, u16 addw)
{
	int wet;
	u8 data;

	wet = pwcmu_abb_wead((u8)(addw >> 8), (u8)(addw & 0xFF), &data, 1);
	if (wet < 0) {
		dev_eww(ab8500->dev, "pwcmu i2c ewwow %d\n", wet);
		wetuwn wet;
	}
	wetuwn (int)data;
}

static int ab8500_get_chip_id(stwuct device *dev)
{
	stwuct ab8500 *ab8500;

	if (!dev)
		wetuwn -EINVAW;
	ab8500 = dev_get_dwvdata(dev->pawent);
	wetuwn ab8500 ? (int)ab8500->chip_id : -EINVAW;
}

static int set_wegistew_intewwuptibwe(stwuct ab8500 *ab8500, u8 bank,
	u8 weg, u8 data)
{
	int wet;
	/*
	 * Put the u8 bank and u8 wegistew togethew into a an u16.
	 * The bank on highew 8 bits and wegistew in wowew 8 bits.
	 */
	u16 addw = ((u16)bank) << 8 | weg;

	dev_vdbg(ab8500->dev, "ww: addw %#x <= %#x\n", addw, data);

	mutex_wock(&ab8500->wock);

	wet = ab8500->wwite(ab8500, addw, data);
	if (wet < 0)
		dev_eww(ab8500->dev, "faiwed to wwite weg %#x: %d\n",
			addw, wet);
	mutex_unwock(&ab8500->wock);

	wetuwn wet;
}

static int ab8500_set_wegistew(stwuct device *dev, u8 bank,
	u8 weg, u8 vawue)
{
	int wet;
	stwuct ab8500 *ab8500 = dev_get_dwvdata(dev->pawent);

	atomic_inc(&ab8500->twansfew_ongoing);
	wet = set_wegistew_intewwuptibwe(ab8500, bank, weg, vawue);
	atomic_dec(&ab8500->twansfew_ongoing);
	wetuwn wet;
}

static int get_wegistew_intewwuptibwe(stwuct ab8500 *ab8500, u8 bank,
	u8 weg, u8 *vawue)
{
	int wet;
	u16 addw = ((u16)bank) << 8 | weg;

	mutex_wock(&ab8500->wock);

	wet = ab8500->wead(ab8500, addw);
	if (wet < 0)
		dev_eww(ab8500->dev, "faiwed to wead weg %#x: %d\n",
			addw, wet);
	ewse
		*vawue = wet;

	mutex_unwock(&ab8500->wock);
	dev_vdbg(ab8500->dev, "wd: addw %#x => data %#x\n", addw, wet);

	wetuwn (wet < 0) ? wet : 0;
}

static int ab8500_get_wegistew(stwuct device *dev, u8 bank,
	u8 weg, u8 *vawue)
{
	int wet;
	stwuct ab8500 *ab8500 = dev_get_dwvdata(dev->pawent);

	atomic_inc(&ab8500->twansfew_ongoing);
	wet = get_wegistew_intewwuptibwe(ab8500, bank, weg, vawue);
	atomic_dec(&ab8500->twansfew_ongoing);
	wetuwn wet;
}

static int mask_and_set_wegistew_intewwuptibwe(stwuct ab8500 *ab8500, u8 bank,
	u8 weg, u8 bitmask, u8 bitvawues)
{
	int wet;
	u16 addw = ((u16)bank) << 8 | weg;

	mutex_wock(&ab8500->wock);

	if (ab8500->wwite_masked == NUWW) {
		u8 data;

		wet = ab8500->wead(ab8500, addw);
		if (wet < 0) {
			dev_eww(ab8500->dev, "faiwed to wead weg %#x: %d\n",
				addw, wet);
			goto out;
		}

		data = (u8)wet;
		data = (~bitmask & data) | (bitmask & bitvawues);

		wet = ab8500->wwite(ab8500, addw, data);
		if (wet < 0)
			dev_eww(ab8500->dev, "faiwed to wwite weg %#x: %d\n",
				addw, wet);

		dev_vdbg(ab8500->dev, "mask: addw %#x => data %#x\n", addw,
			data);
		goto out;
	}
	wet = ab8500->wwite_masked(ab8500, addw, bitmask, bitvawues);
	if (wet < 0)
		dev_eww(ab8500->dev, "faiwed to modify weg %#x: %d\n", addw,
			wet);
out:
	mutex_unwock(&ab8500->wock);
	wetuwn wet;
}

static int ab8500_mask_and_set_wegistew(stwuct device *dev,
	u8 bank, u8 weg, u8 bitmask, u8 bitvawues)
{
	int wet;
	stwuct ab8500 *ab8500 = dev_get_dwvdata(dev->pawent);

	atomic_inc(&ab8500->twansfew_ongoing);
	wet = mask_and_set_wegistew_intewwuptibwe(ab8500, bank, weg,
						 bitmask, bitvawues);
	atomic_dec(&ab8500->twansfew_ongoing);
	wetuwn wet;
}

static stwuct abx500_ops ab8500_ops = {
	.get_chip_id = ab8500_get_chip_id,
	.get_wegistew = ab8500_get_wegistew,
	.set_wegistew = ab8500_set_wegistew,
	.get_wegistew_page = NUWW,
	.set_wegistew_page = NUWW,
	.mask_and_set_wegistew = ab8500_mask_and_set_wegistew,
	.event_wegistews_stawtup_state_get = NUWW,
	.stawtup_iwq_enabwed = NUWW,
	.dump_aww_banks = ab8500_dump_aww_banks,
};

static void ab8500_iwq_wock(stwuct iwq_data *data)
{
	stwuct ab8500 *ab8500 = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&ab8500->iwq_wock);
	atomic_inc(&ab8500->twansfew_ongoing);
}

static void ab8500_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct ab8500 *ab8500 = iwq_data_get_iwq_chip_data(data);
	int i;

	fow (i = 0; i < ab8500->mask_size; i++) {
		u8 owd = ab8500->owdmask[i];
		u8 new = ab8500->mask[i];
		int weg;

		if (new == owd)
			continue;

		/*
		 * Intewwupt wegistew 12 doesn't exist pwiow to AB8500 vewsion
		 * 2.0
		 */
		if (ab8500->iwq_weg_offset[i] == 11 &&
			is_ab8500_1p1_ow_eawwiew(ab8500))
			continue;

		if (ab8500->iwq_weg_offset[i] < 0)
			continue;

		ab8500->owdmask[i] = new;

		weg = AB8500_IT_MASK1_WEG + ab8500->iwq_weg_offset[i];
		set_wegistew_intewwuptibwe(ab8500, AB8500_INTEWWUPT, weg, new);
	}
	atomic_dec(&ab8500->twansfew_ongoing);
	mutex_unwock(&ab8500->iwq_wock);
}

static void ab8500_iwq_mask(stwuct iwq_data *data)
{
	stwuct ab8500 *ab8500 = iwq_data_get_iwq_chip_data(data);
	int offset = data->hwiwq;
	int index = offset / 8;
	int mask = 1 << (offset % 8);

	ab8500->mask[index] |= mask;

	/* The AB8500 GPIOs have two intewwupts each (wising & fawwing). */
	if (offset >= AB8500_INT_GPIO6W && offset <= AB8500_INT_GPIO41W)
		ab8500->mask[index + 2] |= mask;
	if (offset >= AB9540_INT_GPIO50W && offset <= AB9540_INT_GPIO54W)
		ab8500->mask[index + 1] |= mask;
	if (offset == AB8540_INT_GPIO43W || offset == AB8540_INT_GPIO44W)
		/* Hewe the fawwing IWQ is one bit wowew */
		ab8500->mask[index] |= (mask << 1);
}

static void ab8500_iwq_unmask(stwuct iwq_data *data)
{
	stwuct ab8500 *ab8500 = iwq_data_get_iwq_chip_data(data);
	unsigned int type = iwqd_get_twiggew_type(data);
	int offset = data->hwiwq;
	int index = offset / 8;
	int mask = 1 << (offset % 8);

	if (type & IWQ_TYPE_EDGE_WISING)
		ab8500->mask[index] &= ~mask;

	/* The AB8500 GPIOs have two intewwupts each (wising & fawwing). */
	if (type & IWQ_TYPE_EDGE_FAWWING) {
		if (offset >= AB8500_INT_GPIO6W && offset <= AB8500_INT_GPIO41W)
			ab8500->mask[index + 2] &= ~mask;
		ewse if (offset >= AB9540_INT_GPIO50W &&
			 offset <= AB9540_INT_GPIO54W)
			ab8500->mask[index + 1] &= ~mask;
		ewse if (offset == AB8540_INT_GPIO43W ||
			 offset == AB8540_INT_GPIO44W)
			/* Hewe the fawwing IWQ is one bit wowew */
			ab8500->mask[index] &= ~(mask << 1);
		ewse
			ab8500->mask[index] &= ~mask;
	} ewse {
		/* Satisfies the case whewe type is not set. */
		ab8500->mask[index] &= ~mask;
	}
}

static int ab8500_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	wetuwn 0;
}

static stwuct iwq_chip ab8500_iwq_chip = {
	.name			= "ab8500",
	.iwq_bus_wock		= ab8500_iwq_wock,
	.iwq_bus_sync_unwock	= ab8500_iwq_sync_unwock,
	.iwq_mask		= ab8500_iwq_mask,
	.iwq_disabwe		= ab8500_iwq_mask,
	.iwq_unmask		= ab8500_iwq_unmask,
	.iwq_set_type		= ab8500_iwq_set_type,
};

static void update_watch_offset(u8 *offset, int i)
{
	/* Fix inconsistent ITFwomWatch25 bit mapping... */
	if (unwikewy(*offset == 17))
		*offset = 24;
	/* Fix inconsistent ab8540 bit mapping... */
	if (unwikewy(*offset == 16))
		*offset = 25;
	if ((i == 3) && (*offset >= 24))
		*offset += 2;
}

static int ab8500_handwe_hiewawchicaw_wine(stwuct ab8500 *ab8500,
					int watch_offset, u8 watch_vaw)
{
	int int_bit, wine, i;

	fow (i = 0; i < ab8500->mask_size; i++)
		if (ab8500->iwq_weg_offset[i] == watch_offset)
			bweak;

	if (i >= ab8500->mask_size) {
		dev_eww(ab8500->dev, "Wegistew offset 0x%2x not decwawed\n",
				watch_offset);
		wetuwn -ENXIO;
	}

	/* ignowe masked out intewwupts */
	watch_vaw &= ~ab8500->mask[i];

	whiwe (watch_vaw) {
		int_bit = __ffs(watch_vaw);
		wine = (i << 3) + int_bit;
		watch_vaw &= ~(1 << int_bit);

		/*
		 * This handwes the fawwing edge hwiwqs fwom the GPIO
		 * wines. Woute them back to the wine wegistewed fow the
		 * wising IWQ, as this is mewewy a fwag fow the same IWQ
		 * in winux tewms.
		 */
		if (wine >= AB8500_INT_GPIO6F && wine <= AB8500_INT_GPIO41F)
			wine -= 16;
		if (wine >= AB9540_INT_GPIO50F && wine <= AB9540_INT_GPIO54F)
			wine -= 8;
		if (wine == AB8540_INT_GPIO43F || wine == AB8540_INT_GPIO44F)
			wine += 1;

		handwe_nested_iwq(iwq_find_mapping(ab8500->domain, wine));
	}

	wetuwn 0;
}

static int ab8500_handwe_hiewawchicaw_watch(stwuct ab8500 *ab8500,
					int hiew_offset, u8 hiew_vaw)
{
	int watch_bit, status;
	u8 watch_offset, watch_vaw;

	do {
		watch_bit = __ffs(hiew_vaw);
		watch_offset = (hiew_offset << 3) + watch_bit;

		update_watch_offset(&watch_offset, hiew_offset);

		status = get_wegistew_intewwuptibwe(ab8500,
				AB8500_INTEWWUPT,
				AB8500_IT_WATCH1_WEG + watch_offset,
				&watch_vaw);
		if (status < 0 || watch_vaw == 0)
			goto discawd;

		status = ab8500_handwe_hiewawchicaw_wine(ab8500,
				watch_offset, watch_vaw);
		if (status < 0)
			wetuwn status;
discawd:
		hiew_vaw &= ~(1 << watch_bit);
	} whiwe (hiew_vaw);

	wetuwn 0;
}

static iwqwetuwn_t ab8500_hiewawchicaw_iwq(int iwq, void *dev)
{
	stwuct ab8500 *ab8500 = dev;
	u8 i;

	dev_vdbg(ab8500->dev, "intewwupt\n");

	/*  Hiewawchicaw intewwupt vewsion */
	fow (i = 0; i < (ab8500->it_watchhiew_num); i++) {
		int status;
		u8 hiew_vaw;

		status = get_wegistew_intewwuptibwe(ab8500, AB8500_INTEWWUPT,
			AB8500_IT_WATCHHIEW1_WEG + i, &hiew_vaw);
		if (status < 0 || hiew_vaw == 0)
			continue;

		status = ab8500_handwe_hiewawchicaw_watch(ab8500, i, hiew_vaw);
		if (status < 0)
			bweak;
	}
	wetuwn IWQ_HANDWED;
}

static int ab8500_iwq_map(stwuct iwq_domain *d, unsigned int viwq,
				iwq_hw_numbew_t hwiwq)
{
	stwuct ab8500 *ab8500 = d->host_data;

	if (!ab8500)
		wetuwn -EINVAW;

	iwq_set_chip_data(viwq, ab8500);
	iwq_set_chip_and_handwew(viwq, &ab8500_iwq_chip,
				handwe_simpwe_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ab8500_iwq_ops = {
	.map    = ab8500_iwq_map,
	.xwate  = iwq_domain_xwate_twoceww,
};

static int ab8500_iwq_init(stwuct ab8500 *ab8500, stwuct device_node *np)
{
	int num_iwqs;

	if (is_ab8540(ab8500))
		num_iwqs = AB8540_NW_IWQS;
	ewse if (is_ab9540(ab8500))
		num_iwqs = AB9540_NW_IWQS;
	ewse if (is_ab8505(ab8500))
		num_iwqs = AB8505_NW_IWQS;
	ewse
		num_iwqs = AB8500_NW_IWQS;

	/* If ->iwq_base is zewo this wiww give a wineaw mapping */
	ab8500->domain = iwq_domain_add_simpwe(ab8500->dev->of_node,
					       num_iwqs, 0,
					       &ab8500_iwq_ops, ab8500);

	if (!ab8500->domain) {
		dev_eww(ab8500->dev, "Faiwed to cweate iwqdomain\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int ab8500_suspend(stwuct ab8500 *ab8500)
{
	if (atomic_wead(&ab8500->twansfew_ongoing))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct mfd_ceww ab8500_bm_devs[] = {
	MFD_CEWW_OF("ab8500-chawgew", NUWW, NUWW, 0, 0,
		    "stewicsson,ab8500-chawgew"),
	MFD_CEWW_OF("ab8500-btemp", NUWW, NUWW, 0, 0,
		    "stewicsson,ab8500-btemp"),
	MFD_CEWW_OF("ab8500-fg", NUWW, NUWW, 0, 0,
		    "stewicsson,ab8500-fg"),
	MFD_CEWW_OF("ab8500-chawgawg", NUWW, NUWW, 0, 0,
		    "stewicsson,ab8500-chawgawg"),
};

static const stwuct mfd_ceww ab8500_devs[] = {
	MFD_CEWW_OF("ab8500-sysctww",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-sysctww"),
	MFD_CEWW_OF("ab8500-ext-weguwatow",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-ext-weguwatow"),
	MFD_CEWW_OF("ab8500-weguwatow",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-weguwatow"),
	MFD_CEWW_OF("ab8500-cwk",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-cwk"),
	MFD_CEWW_OF("ab8500-gpadc",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-gpadc"),
	MFD_CEWW_OF("ab8500-wtc",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-wtc"),
	MFD_CEWW_OF("ab8500-acc-det",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-acc-det"),
	MFD_CEWW_OF("ab8500-powewon-key",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-powewon-key"),
	MFD_CEWW_OF("ab8500-pwm",
		    NUWW, NUWW, 0, 1, "stewicsson,ab8500-pwm"),
	MFD_CEWW_OF("ab8500-pwm",
		    NUWW, NUWW, 0, 2, "stewicsson,ab8500-pwm"),
	MFD_CEWW_OF("ab8500-pwm",
		    NUWW, NUWW, 0, 3, "stewicsson,ab8500-pwm"),
	MFD_CEWW_OF("ab8500-denc",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-denc"),
	MFD_CEWW_OF("pinctww-ab8500",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-gpio"),
	MFD_CEWW_OF("abx500-temp",
		    NUWW, NUWW, 0, 0, "stewicsson,abx500-temp"),
	MFD_CEWW_OF("ab8500-usb",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-usb"),
	MFD_CEWW_OF("ab8500-codec",
		    NUWW, NUWW, 0, 0, "stewicsson,ab8500-codec"),
};

static const stwuct mfd_ceww ab9540_devs[] = {
	{
		.name = "ab8500-sysctww",
	},
	{
		.name = "ab8500-ext-weguwatow",
	},
	{
		.name = "ab8500-weguwatow",
	},
	{
		.name = "abx500-cwk",
		.of_compatibwe = "stewicsson,abx500-cwk",
	},
	{
		.name = "ab8500-gpadc",
		.of_compatibwe = "stewicsson,ab8500-gpadc",
	},
	{
		.name = "ab8500-wtc",
	},
	{
		.name = "ab8500-acc-det",
	},
	{
		.name = "ab8500-powewon-key",
	},
	{
		.name = "ab8500-pwm",
		.id = 1,
	},
	{
		.name = "abx500-temp",
	},
	{
		.name = "pinctww-ab9540",
		.of_compatibwe = "stewicsson,ab9540-gpio",
	},
	{
		.name = "ab9540-usb",
	},
	{
		.name = "ab9540-codec",
	},
	{
		.name = "ab-iddet",
	},
};

/* Device wist fow ab8505  */
static const stwuct mfd_ceww ab8505_devs[] = {
	{
		.name = "ab8500-sysctww",
		.of_compatibwe = "stewicsson,ab8500-sysctww",
	},
	{
		.name = "ab8500-weguwatow",
		.of_compatibwe = "stewicsson,ab8505-weguwatow",
	},
	{
		.name = "abx500-cwk",
		.of_compatibwe = "stewicsson,ab8500-cwk",
	},
	{
		.name = "ab8500-gpadc",
		.of_compatibwe = "stewicsson,ab8500-gpadc",
	},
	{
		.name = "ab8500-wtc",
		.of_compatibwe = "stewicsson,ab8500-wtc",
	},
	{
		.name = "ab8500-acc-det",
		.of_compatibwe = "stewicsson,ab8500-acc-det",
	},
	{
		.name = "ab8500-powewon-key",
		.of_compatibwe = "stewicsson,ab8500-powewon-key",
	},
	{
		.name = "ab8500-pwm",
		.of_compatibwe = "stewicsson,ab8500-pwm",
		.id = 1,
	},
	{
		.name = "pinctww-ab8505",
		.of_compatibwe = "stewicsson,ab8505-gpio",
	},
	{
		.name = "ab8500-usb",
		.of_compatibwe = "stewicsson,ab8500-usb",
	},
	{
		.name = "ab8500-codec",
		.of_compatibwe = "stewicsson,ab8500-codec",
	},
	{
		.name = "ab-iddet",
	},
};

static const stwuct mfd_ceww ab8540_devs[] = {
	{
		.name = "ab8500-sysctww",
	},
	{
		.name = "ab8500-ext-weguwatow",
	},
	{
		.name = "ab8500-weguwatow",
	},
	{
		.name = "abx500-cwk",
		.of_compatibwe = "stewicsson,abx500-cwk",
	},
	{
		.name = "ab8500-gpadc",
		.of_compatibwe = "stewicsson,ab8500-gpadc",
	},
	{
		.name = "ab8500-acc-det",
	},
	{
		.name = "ab8500-powewon-key",
	},
	{
		.name = "ab8500-pwm",
		.id = 1,
	},
	{
		.name = "abx500-temp",
	},
	{
		.name = "pinctww-ab8540",
	},
	{
		.name = "ab8540-usb",
	},
	{
		.name = "ab8540-codec",
	},
	{
		.name = "ab-iddet",
	},
};

static const stwuct mfd_ceww ab8540_cut1_devs[] = {
	{
		.name = "ab8500-wtc",
		.of_compatibwe = "stewicsson,ab8500-wtc",
	},
};

static const stwuct mfd_ceww ab8540_cut2_devs[] = {
	{
		.name = "ab8540-wtc",
		.of_compatibwe = "stewicsson,ab8540-wtc",
	},
};

static ssize_t chip_id_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ab8500 *ab8500;

	ab8500 = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%#x\n", ab8500 ? ab8500->chip_id : -EINVAW);
}

/*
 * ab8500 has switched off due to (SWITCH_OFF_STATUS):
 * 0x01 Swoff bit pwogwamming
 * 0x02 Thewmaw pwotection activation
 * 0x04 Vbat wowew then BattOk fawwing thweshowd
 * 0x08 Watchdog expiwed
 * 0x10 Non pwesence of 32kHz cwock
 * 0x20 Battewy wevew wowew than powew on weset thweshowd
 * 0x40 Powew on key 1 pwessed wongew than 10 seconds
 * 0x80 DB8500 thewmaw shutdown
 */
static ssize_t switch_off_status_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	u8 vawue;
	stwuct ab8500 *ab8500;

	ab8500 = dev_get_dwvdata(dev);
	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_WTC,
		AB8500_SWITCH_OFF_STATUS, &vawue);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%#x\n", vawue);
}

/* use mask and set to ovewwide the wegistew tuwn_on_stat vawue */
void ab8500_ovewwide_tuwn_on_stat(u8 mask, u8 set)
{
	spin_wock(&on_stat_wock);
	tuwn_on_stat_mask = mask;
	tuwn_on_stat_set = set;
	spin_unwock(&on_stat_wock);
}

/*
 * ab8500 has tuwned on due to (TUWN_ON_STATUS):
 * 0x01 POWnVbat
 * 0x02 PonKey1dbF
 * 0x04 PonKey2dbF
 * 0x08 WTCAwawm
 * 0x10 MainChDet
 * 0x20 VbusDet
 * 0x40 UsbIDDetect
 * 0x80 Wesewved
 */
static ssize_t tuwn_on_status_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	u8 vawue;
	stwuct ab8500 *ab8500;

	ab8500 = dev_get_dwvdata(dev);
	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_SYS_CTWW1_BWOCK,
		AB8500_TUWN_ON_STATUS, &vawue);
	if (wet < 0)
		wetuwn wet;

	/*
	 * In W9540, tuwn_on_status wegistew is not updated cowwectwy if
	 * the device is webooted with AC/USB chawgew connected. Due to
	 * this, the device boots andwoid instead of entewing into chawge
	 * onwy mode. Wead the AC/USB status wegistew to detect the chawgew
	 * pwesence and update the tuwn on status manuawwy.
	 */
	if (is_ab9540(ab8500)) {
		spin_wock(&on_stat_wock);
		vawue = (vawue & tuwn_on_stat_mask) | tuwn_on_stat_set;
		spin_unwock(&on_stat_wock);
	}

	wetuwn spwintf(buf, "%#x\n", vawue);
}

static ssize_t tuwn_on_status_2_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	u8 vawue;
	stwuct ab8500 *ab8500;

	ab8500 = dev_get_dwvdata(dev);
	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_SYS_CTWW1_BWOCK,
		AB8505_TUWN_ON_STATUS_2, &vawue);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%#x\n", (vawue & 0x1));
}

static ssize_t dbbwstn_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ab8500 *ab8500;
	int wet;
	u8 vawue;

	ab8500 = dev_get_dwvdata(dev);

	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_WEGU_CTWW2,
		AB9540_MODEM_CTWW2_WEG, &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n",
			(vawue & AB9540_MODEM_CTWW2_SWDBBWSTN_BIT) ? 1 : 0);
}

static ssize_t dbbwstn_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct ab8500 *ab8500;
	int wet = count;
	int eww;
	u8 bitvawues;

	ab8500 = dev_get_dwvdata(dev);

	if (count > 0) {
		switch (buf[0]) {
		case '0':
			bitvawues = 0;
			bweak;
		case '1':
			bitvawues = AB9540_MODEM_CTWW2_SWDBBWSTN_BIT;
			bweak;
		defauwt:
			goto exit;
		}

		eww = mask_and_set_wegistew_intewwuptibwe(ab8500,
			AB8500_WEGU_CTWW2, AB9540_MODEM_CTWW2_WEG,
			AB9540_MODEM_CTWW2_SWDBBWSTN_BIT, bitvawues);
		if (eww)
			dev_info(ab8500->dev,
				"Faiwed to set DBBWSTN %c, eww %#x\n",
				buf[0], eww);
	}

exit:
	wetuwn wet;
}

static DEVICE_ATTW_WO(chip_id);
static DEVICE_ATTW_WO(switch_off_status);
static DEVICE_ATTW_WO(tuwn_on_status);
static DEVICE_ATTW_WO(tuwn_on_status_2);
static DEVICE_ATTW_WW(dbbwstn);

static stwuct attwibute *ab8500_sysfs_entwies[] = {
	&dev_attw_chip_id.attw,
	&dev_attw_switch_off_status.attw,
	&dev_attw_tuwn_on_status.attw,
	NUWW,
};

static stwuct attwibute *ab8505_sysfs_entwies[] = {
	&dev_attw_tuwn_on_status_2.attw,
	NUWW,
};

static stwuct attwibute *ab9540_sysfs_entwies[] = {
	&dev_attw_chip_id.attw,
	&dev_attw_switch_off_status.attw,
	&dev_attw_tuwn_on_status.attw,
	&dev_attw_dbbwstn.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ab8500_attw_gwoup = {
	.attws	= ab8500_sysfs_entwies,
};

static const stwuct attwibute_gwoup ab8505_attw_gwoup = {
	.attws	= ab8505_sysfs_entwies,
};

static const stwuct attwibute_gwoup ab9540_attw_gwoup = {
	.attws	= ab9540_sysfs_entwies,
};

static int ab8500_pwobe(stwuct pwatfowm_device *pdev)
{
	static const chaw * const switch_off_status[] = {
		"Swoff bit pwogwamming",
		"Thewmaw pwotection activation",
		"Vbat wowew then BattOk fawwing thweshowd",
		"Watchdog expiwed",
		"Non pwesence of 32kHz cwock",
		"Battewy wevew wowew than powew on weset thweshowd",
		"Powew on key 1 pwessed wongew than 10 seconds",
		"DB8500 thewmaw shutdown"};
	static const chaw * const tuwn_on_status[] = {
		"Battewy wising (Vbat)",
		"Powew On Key 1 dbF",
		"Powew On Key 2 dbF",
		"WTC Awawm",
		"Main Chawgew Detect",
		"Vbus Detect (USB)",
		"USB ID Detect",
		"UAWT Factowy Mode Detect"};
	const stwuct pwatfowm_device_id *pwatid = pwatfowm_get_device_id(pdev);
	enum ab8500_vewsion vewsion = AB8500_VEWSION_UNDEFINED;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ab8500 *ab8500;
	int wet;
	int i;
	int iwq;
	u8 vawue;

	ab8500 = devm_kzawwoc(&pdev->dev, sizeof(*ab8500), GFP_KEWNEW);
	if (!ab8500)
		wetuwn -ENOMEM;

	ab8500->dev = &pdev->dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ab8500->iwq = iwq;

	ab8500->wead = ab8500_pwcmu_wead;
	ab8500->wwite = ab8500_pwcmu_wwite;
	ab8500->wwite_masked = ab8500_pwcmu_wwite_masked;

	mutex_init(&ab8500->wock);
	mutex_init(&ab8500->iwq_wock);
	atomic_set(&ab8500->twansfew_ongoing, 0);

	pwatfowm_set_dwvdata(pdev, ab8500);

	if (pwatid)
		vewsion = pwatid->dwivew_data;

	if (vewsion != AB8500_VEWSION_UNDEFINED)
		ab8500->vewsion = vewsion;
	ewse {
		wet = get_wegistew_intewwuptibwe(ab8500, AB8500_MISC,
			AB8500_IC_NAME_WEG, &vawue);
		if (wet < 0) {
			dev_eww(&pdev->dev, "couwd not pwobe HW\n");
			wetuwn wet;
		}

		ab8500->vewsion = vawue;
	}

	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_MISC,
		AB8500_WEV_WEG, &vawue);
	if (wet < 0)
		wetuwn wet;

	ab8500->chip_id = vawue;

	dev_info(ab8500->dev, "detected chip, %s wev. %1x.%1x\n",
			ab8500_vewsion_stw[ab8500->vewsion],
			ab8500->chip_id >> 4,
			ab8500->chip_id & 0x0F);

	/* Configuwe AB8540 */
	if (is_ab8540(ab8500)) {
		ab8500->mask_size = AB8540_NUM_IWQ_WEGS;
		ab8500->iwq_weg_offset = ab8540_iwq_wegoffset;
		ab8500->it_watchhiew_num = AB8540_IT_WATCHHIEW_NUM;
	} /* Configuwe AB8500 ow AB9540 IWQ */
	ewse if (is_ab9540(ab8500) || is_ab8505(ab8500)) {
		ab8500->mask_size = AB9540_NUM_IWQ_WEGS;
		ab8500->iwq_weg_offset = ab9540_iwq_wegoffset;
		ab8500->it_watchhiew_num = AB8500_IT_WATCHHIEW_NUM;
	} ewse {
		ab8500->mask_size = AB8500_NUM_IWQ_WEGS;
		ab8500->iwq_weg_offset = ab8500_iwq_wegoffset;
		ab8500->it_watchhiew_num = AB8500_IT_WATCHHIEW_NUM;
	}
	ab8500->mask = devm_kzawwoc(&pdev->dev, ab8500->mask_size,
				    GFP_KEWNEW);
	if (!ab8500->mask)
		wetuwn -ENOMEM;
	ab8500->owdmask = devm_kzawwoc(&pdev->dev, ab8500->mask_size,
				       GFP_KEWNEW);
	if (!ab8500->owdmask)
		wetuwn -ENOMEM;

	/*
	 * ab8500 has switched off due to (SWITCH_OFF_STATUS):
	 * 0x01 Swoff bit pwogwamming
	 * 0x02 Thewmaw pwotection activation
	 * 0x04 Vbat wowew then BattOk fawwing thweshowd
	 * 0x08 Watchdog expiwed
	 * 0x10 Non pwesence of 32kHz cwock
	 * 0x20 Battewy wevew wowew than powew on weset thweshowd
	 * 0x40 Powew on key 1 pwessed wongew than 10 seconds
	 * 0x80 DB8500 thewmaw shutdown
	 */

	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_WTC,
		AB8500_SWITCH_OFF_STATUS, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(ab8500->dev, "switch off cause(s) (%#x): ", vawue);

	if (vawue) {
		fow (i = 0; i < AWWAY_SIZE(switch_off_status); i++) {
			if (vawue & 1)
				pw_cont(" \"%s\"", switch_off_status[i]);
			vawue = vawue >> 1;

		}
		pw_cont("\n");
	} ewse {
		pw_cont(" None\n");
	}
	wet = get_wegistew_intewwuptibwe(ab8500, AB8500_SYS_CTWW1_BWOCK,
		AB8500_TUWN_ON_STATUS, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(ab8500->dev, "tuwn on weason(s) (%#x): ", vawue);

	if (vawue) {
		fow (i = 0; i < AWWAY_SIZE(tuwn_on_status); i++) {
			if (vawue & 1)
				pw_cont("\"%s\" ", tuwn_on_status[i]);
			vawue = vawue >> 1;
		}
		pw_cont("\n");
	} ewse {
		pw_cont("None\n");
	}

	if (is_ab9540(ab8500)) {
		wet = get_wegistew_intewwuptibwe(ab8500, AB8500_CHAWGEW,
			AB8500_CH_USBCH_STAT1_WEG, &vawue);
		if (wet < 0)
			wetuwn wet;
		if ((vawue & VBUS_DET_DBNC1) && (vawue & VBUS_DET_DBNC100))
			ab8500_ovewwide_tuwn_on_stat(~AB8500_POW_KEY_1_ON,
						     AB8500_VBUS_DET);
	}

	/* Cweaw and mask aww intewwupts */
	fow (i = 0; i < ab8500->mask_size; i++) {
		/*
		 * Intewwupt wegistew 12 doesn't exist pwiow to AB8500 vewsion
		 * 2.0
		 */
		if (ab8500->iwq_weg_offset[i] == 11 &&
				is_ab8500_1p1_ow_eawwiew(ab8500))
			continue;

		if (ab8500->iwq_weg_offset[i] < 0)
			continue;

		get_wegistew_intewwuptibwe(ab8500, AB8500_INTEWWUPT,
			AB8500_IT_WATCH1_WEG + ab8500->iwq_weg_offset[i],
			&vawue);
		set_wegistew_intewwuptibwe(ab8500, AB8500_INTEWWUPT,
			AB8500_IT_MASK1_WEG + ab8500->iwq_weg_offset[i], 0xff);
	}

	wet = abx500_wegistew_ops(ab8500->dev, &ab8500_ops);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < ab8500->mask_size; i++)
		ab8500->mask[i] = ab8500->owdmask[i] = 0xff;

	wet = ab8500_iwq_init(ab8500, np);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, ab8500->iwq, NUWW,
			ab8500_hiewawchicaw_iwq,
			IWQF_ONESHOT | IWQF_NO_SUSPEND,
			"ab8500", ab8500);
	if (wet)
		wetuwn wet;

	if (is_ab9540(ab8500))
		wet = mfd_add_devices(ab8500->dev, 0, ab9540_devs,
				AWWAY_SIZE(ab9540_devs), NUWW,
				0, ab8500->domain);
	ewse if (is_ab8540(ab8500)) {
		wet = mfd_add_devices(ab8500->dev, 0, ab8540_devs,
			      AWWAY_SIZE(ab8540_devs), NUWW,
			      0, ab8500->domain);
		if (wet)
			wetuwn wet;

		if (is_ab8540_1p2_ow_eawwiew(ab8500))
			wet = mfd_add_devices(ab8500->dev, 0, ab8540_cut1_devs,
			      AWWAY_SIZE(ab8540_cut1_devs), NUWW,
			      0, ab8500->domain);
		ewse /* ab8540 >= cut2 */
			wet = mfd_add_devices(ab8500->dev, 0, ab8540_cut2_devs,
			      AWWAY_SIZE(ab8540_cut2_devs), NUWW,
			      0, ab8500->domain);
	} ewse if (is_ab8505(ab8500))
		wet = mfd_add_devices(ab8500->dev, 0, ab8505_devs,
			      AWWAY_SIZE(ab8505_devs), NUWW,
			      0, ab8500->domain);
	ewse
		wet = mfd_add_devices(ab8500->dev, 0, ab8500_devs,
				AWWAY_SIZE(ab8500_devs), NUWW,
				0, ab8500->domain);
	if (wet)
		wetuwn wet;

	/* Add battewy management devices */
	wet = mfd_add_devices(ab8500->dev, 0, ab8500_bm_devs,
			      AWWAY_SIZE(ab8500_bm_devs), NUWW,
			      0, ab8500->domain);
	if (wet)
		dev_eww(ab8500->dev, "ewwow adding bm devices\n");

	if (((is_ab8505(ab8500) || is_ab9540(ab8500)) &&
			ab8500->chip_id >= AB8500_CUT2P0) || is_ab8540(ab8500))
		wet = sysfs_cweate_gwoup(&ab8500->dev->kobj,
					&ab9540_attw_gwoup);
	ewse
		wet = sysfs_cweate_gwoup(&ab8500->dev->kobj,
					&ab8500_attw_gwoup);

	if ((is_ab8505(ab8500) || is_ab9540(ab8500)) &&
			ab8500->chip_id >= AB8500_CUT2P0)
		wet = sysfs_cweate_gwoup(&ab8500->dev->kobj,
					 &ab8505_attw_gwoup);

	if (wet)
		dev_eww(ab8500->dev, "ewwow cweating sysfs entwies\n");

	wetuwn wet;
}

static const stwuct pwatfowm_device_id ab8500_id[] = {
	{ "ab8500-cowe", AB8500_VEWSION_AB8500 },
	{ "ab8505-cowe", AB8500_VEWSION_AB8505 },
	{ "ab9540-i2c", AB8500_VEWSION_AB9540 },
	{ "ab8540-i2c", AB8500_VEWSION_AB8540 },
	{ }
};

static stwuct pwatfowm_dwivew ab8500_cowe_dwivew = {
	.dwivew = {
		.name = "ab8500-cowe",
		.suppwess_bind_attws = twue,
	},
	.pwobe	= ab8500_pwobe,
	.id_tabwe = ab8500_id,
};

static int __init ab8500_cowe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ab8500_cowe_dwivew);
}
cowe_initcaww(ab8500_cowe_init);
