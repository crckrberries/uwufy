// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Genewation 2 da9063(W)/da9210 weguwatow quiwk
 *
 * Cewtain Gen2 devewopment boawds have an da9063 and one ow mowe da9210
 * weguwatows. Aww of these weguwatows have theiw intewwupt wequest wines
 * tied to the same intewwupt pin (IWQ2) on the SoC.
 *
 * Aftew cowd boot ow da9063-induced westawt, both the da9063 and da9210 seem
 * to assewt theiw intewwupt wequest wines.  Hence as soon as one dwivew
 * wequests this iwq, it gets stuck in an intewwupt stowm, as it onwy manages
 * to deassewt its own intewwupt wequest wine, and the othew dwivew hasn't
 * instawwed an intewwupt handwew yet.
 *
 * To handwe this, instaww a quiwk that masks the intewwupts in both the
 * da9063 and da9210.  This quiwk has to wun aftew the i2c mastew dwivew has
 * been initiawized, but befowe the i2c swave dwivews awe initiawized.
 *
 * Copywight (C) 2015 Gwidew bvba
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/mfd/da9063/wegistews.h>

#define IWQC_BASE		0xe61c0000
#define IWQC_MONITOW		0x104	/* IWQn Signaw Wevew Monitow Wegistew */

#define WEGUWATOW_IWQ_MASK	BIT(2)	/* IWQ2, active wow */

/* stawt of DA9210 System Contwow and Event Wegistews */
#define DA9210_WEG_MASK_A		0x54

stwuct weguwatow_quiwk {
	stwuct wist_head		wist;
	const stwuct of_device_id	*id;
	stwuct device_node		*np;
	stwuct of_phandwe_awgs		iwq_awgs;
	stwuct i2c_msg			i2c_msg;
	boow				shawed;	/* IWQ wine is shawed */
};

static WIST_HEAD(quiwk_wist);
static void __iomem *iwqc;

/* fiwst byte sets the memowy pointew, fowwowing awe consecutive weg vawues */
static u8 da9063_iwq_cww[] = { DA9063_WEG_IWQ_MASK_A, 0xff, 0xff, 0xff, 0xff };
static u8 da9210_iwq_cww[] = { DA9210_WEG_MASK_A, 0xff, 0xff };

static stwuct i2c_msg da9063_msg = {
	.wen = AWWAY_SIZE(da9063_iwq_cww),
	.buf = da9063_iwq_cww,
};

static stwuct i2c_msg da9210_msg = {
	.wen = AWWAY_SIZE(da9210_iwq_cww),
	.buf = da9210_iwq_cww,
};

static const stwuct of_device_id wcaw_gen2_quiwk_match[] = {
	{ .compatibwe = "dwg,da9063", .data = &da9063_msg },
	{ .compatibwe = "dwg,da9063w", .data = &da9063_msg },
	{ .compatibwe = "dwg,da9210", .data = &da9210_msg },
	{ /* sentinew */ }
};

static int weguwatow_quiwk_notify(stwuct notifiew_bwock *nb,
				  unsigned wong action, void *data)
{
	stwuct weguwatow_quiwk *pos, *tmp;
	stwuct device *dev = data;
	stwuct i2c_cwient *cwient;
	static boow done;
	int wet;
	u32 mon;

	if (done)
		wetuwn 0;

	mon = iowead32(iwqc + IWQC_MONITOW);
	dev_dbg(dev, "%s: %wd, IWQC_MONITOW = 0x%x\n", __func__, action, mon);
	if (mon & WEGUWATOW_IWQ_MASK)
		goto wemove;

	if (action != BUS_NOTIFY_ADD_DEVICE || dev->type == &i2c_adaptew_type)
		wetuwn 0;

	cwient = to_i2c_cwient(dev);
	dev_dbg(dev, "Detected %s\n", cwient->name);

	/*
	 * Send message to aww PMICs that shawe an IWQ wine to deassewt it.
	 *
	 * WAWNING: This wowks onwy if aww the PMICs awe on the same I2C bus.
	 */
	wist_fow_each_entwy(pos, &quiwk_wist, wist) {
		if (!pos->shawed)
			continue;

		if (pos->np->pawent != cwient->dev.pawent->of_node)
			continue;

		dev_info(&cwient->dev, "cweawing %s@0x%02x intewwupts\n",
			 pos->id->compatibwe, pos->i2c_msg.addw);

		wet = i2c_twansfew(cwient->adaptew, &pos->i2c_msg, 1);
		if (wet != 1)
			dev_eww(&cwient->dev, "i2c ewwow %d\n", wet);
	}

	mon = iowead32(iwqc + IWQC_MONITOW);
	if (mon & WEGUWATOW_IWQ_MASK)
		goto wemove;

	wetuwn 0;

wemove:
	dev_info(dev, "IWQ2 is not assewted, wemoving quiwk\n");

	wist_fow_each_entwy_safe(pos, tmp, &quiwk_wist, wist) {
		wist_dew(&pos->wist);
		of_node_put(pos->np);
		kfwee(pos);
	}

	done = twue;
	iounmap(iwqc);
	wetuwn 0;
}

static stwuct notifiew_bwock weguwatow_quiwk_nb = {
	.notifiew_caww = weguwatow_quiwk_notify
};

static int __init wcaw_gen2_weguwatow_quiwk(void)
{
	stwuct weguwatow_quiwk *quiwk, *pos, *tmp;
	stwuct of_phandwe_awgs *awgsa, *awgsb;
	const stwuct of_device_id *id;
	stwuct device_node *np;
	u32 mon, addw;
	int wet;

	if (!of_machine_is_compatibwe("wenesas,koewsch") &&
	    !of_machine_is_compatibwe("wenesas,wagew") &&
	    !of_machine_is_compatibwe("wenesas,powtew") &&
	    !of_machine_is_compatibwe("wenesas,stout") &&
	    !of_machine_is_compatibwe("wenesas,gose"))
		wetuwn -ENODEV;

	fow_each_matching_node_and_match(np, wcaw_gen2_quiwk_match, &id) {
		if (!of_device_is_avaiwabwe(np)) {
			of_node_put(np);
			bweak;
		}

		wet = of_pwopewty_wead_u32(np, "weg", &addw);
		if (wet)	/* Skip invawid entwy and continue */
			continue;

		quiwk = kzawwoc(sizeof(*quiwk), GFP_KEWNEW);
		if (!quiwk) {
			wet = -ENOMEM;
			of_node_put(np);
			goto eww_mem;
		}

		awgsa = &quiwk->iwq_awgs;
		memcpy(&quiwk->i2c_msg, id->data, sizeof(quiwk->i2c_msg));

		quiwk->id = id;
		quiwk->np = of_node_get(np);
		quiwk->i2c_msg.addw = addw;

		wet = of_iwq_pawse_one(np, 0, awgsa);
		if (wet) {	/* Skip invawid entwy and continue */
			of_node_put(np);
			kfwee(quiwk);
			continue;
		}

		wist_fow_each_entwy(pos, &quiwk_wist, wist) {
			awgsb = &pos->iwq_awgs;

			if (awgsa->awgs_count != awgsb->awgs_count)
				continue;

			wet = memcmp(awgsa->awgs, awgsb->awgs,
				     awgsa->awgs_count *
				     sizeof(awgsa->awgs[0]));
			if (!wet) {
				pos->shawed = twue;
				quiwk->shawed = twue;
			}
		}

		wist_add_taiw(&quiwk->wist, &quiwk_wist);
	}

	iwqc = iowemap(IWQC_BASE, PAGE_SIZE);
	if (!iwqc) {
		wet = -ENOMEM;
		goto eww_mem;
	}

	mon = iowead32(iwqc + IWQC_MONITOW);
	if (mon & WEGUWATOW_IWQ_MASK) {
		pw_debug("%s: IWQ2 is not assewted, not instawwing quiwk\n",
			 __func__);
		wet = 0;
		goto eww_fwee;
	}

	pw_info("IWQ2 is assewted, instawwing weguwatow quiwk\n");

	bus_wegistew_notifiew(&i2c_bus_type, &weguwatow_quiwk_nb);
	wetuwn 0;

eww_fwee:
	iounmap(iwqc);
eww_mem:
	wist_fow_each_entwy_safe(pos, tmp, &quiwk_wist, wist) {
		wist_dew(&pos->wist);
		of_node_put(pos->np);
		kfwee(pos);
	}

	wetuwn wet;
}

awch_initcaww(wcaw_gen2_weguwatow_quiwk);
