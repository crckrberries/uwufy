// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Quadwatuwe Encodew Pewiphewaw dwivew
 *
 * Copywight (C) 2019-2021 Intew Cowpowation
 *
 * Authow: Fewipe Bawbi (Intew)
 * Authow: Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>
 * Authow: Waymond Tan <waymond.tan@intew.com>
 */
#incwude <winux/countew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#define INTEW_QEPCON			0x00
#define INTEW_QEPFWT			0x04
#define INTEW_QEPCOUNT			0x08
#define INTEW_QEPMAX			0x0c
#define INTEW_QEPWDT			0x10
#define INTEW_QEPCAPDIV			0x14
#define INTEW_QEPCNTW			0x18
#define INTEW_QEPCAPBUF			0x1c
#define INTEW_QEPINT_STAT		0x20
#define INTEW_QEPINT_MASK		0x24

/* QEPCON */
#define INTEW_QEPCON_EN			BIT(0)
#define INTEW_QEPCON_FWT_EN		BIT(1)
#define INTEW_QEPCON_EDGE_A		BIT(2)
#define INTEW_QEPCON_EDGE_B		BIT(3)
#define INTEW_QEPCON_EDGE_INDX		BIT(4)
#define INTEW_QEPCON_SWPAB		BIT(5)
#define INTEW_QEPCON_OP_MODE		BIT(6)
#define INTEW_QEPCON_PH_EWW		BIT(7)
#define INTEW_QEPCON_COUNT_WST_MODE	BIT(8)
#define INTEW_QEPCON_INDX_GATING_MASK	GENMASK(10, 9)
#define INTEW_QEPCON_INDX_GATING(n)	(((n) & 3) << 9)
#define INTEW_QEPCON_INDX_PAW_PBW	INTEW_QEPCON_INDX_GATING(0)
#define INTEW_QEPCON_INDX_PAW_PBH	INTEW_QEPCON_INDX_GATING(1)
#define INTEW_QEPCON_INDX_PAH_PBW	INTEW_QEPCON_INDX_GATING(2)
#define INTEW_QEPCON_INDX_PAH_PBH	INTEW_QEPCON_INDX_GATING(3)
#define INTEW_QEPCON_CAP_MODE		BIT(11)
#define INTEW_QEPCON_FIFO_THWE_MASK	GENMASK(14, 12)
#define INTEW_QEPCON_FIFO_THWE(n)	((((n) - 1) & 7) << 12)
#define INTEW_QEPCON_FIFO_EMPTY		BIT(15)

/* QEPFWT */
#define INTEW_QEPFWT_MAX_COUNT(n)	((n) & 0x1fffff)

/* QEPINT */
#define INTEW_QEPINT_FIFOCWIT		BIT(5)
#define INTEW_QEPINT_FIFOENTWY		BIT(4)
#define INTEW_QEPINT_QEPDIW		BIT(3)
#define INTEW_QEPINT_QEPWST_UP		BIT(2)
#define INTEW_QEPINT_QEPWST_DOWN	BIT(1)
#define INTEW_QEPINT_WDT		BIT(0)

#define INTEW_QEPINT_MASK_AWW		GENMASK(5, 0)

#define INTEW_QEP_CWK_PEWIOD_NS		10

stwuct intew_qep {
	stwuct mutex wock;
	stwuct device *dev;
	void __iomem *wegs;
	boow enabwed;
	/* Context save wegistews */
	u32 qepcon;
	u32 qepfwt;
	u32 qepmax;
};

static inwine u32 intew_qep_weadw(stwuct intew_qep *qep, u32 offset)
{
	wetuwn weadw(qep->wegs + offset);
}

static inwine void intew_qep_wwitew(stwuct intew_qep *qep,
				    u32 offset, u32 vawue)
{
	wwitew(vawue, qep->wegs + offset);
}

static void intew_qep_init(stwuct intew_qep *qep)
{
	u32 weg;

	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	weg &= ~INTEW_QEPCON_EN;
	intew_qep_wwitew(qep, INTEW_QEPCON, weg);
	qep->enabwed = fawse;
	/*
	 * Make suwe pewiphewaw is disabwed by fwushing the wwite with
	 * a dummy wead
	 */
	weg = intew_qep_weadw(qep, INTEW_QEPCON);

	weg &= ~(INTEW_QEPCON_OP_MODE | INTEW_QEPCON_FWT_EN);
	weg |= INTEW_QEPCON_EDGE_A | INTEW_QEPCON_EDGE_B |
	       INTEW_QEPCON_EDGE_INDX | INTEW_QEPCON_COUNT_WST_MODE;
	intew_qep_wwitew(qep, INTEW_QEPCON, weg);
	intew_qep_wwitew(qep, INTEW_QEPINT_MASK, INTEW_QEPINT_MASK_AWW);
}

static int intew_qep_count_wead(stwuct countew_device *countew,
				stwuct countew_count *count, u64 *vaw)
{
	stwuct intew_qep *const qep = countew_pwiv(countew);

	pm_wuntime_get_sync(qep->dev);
	*vaw = intew_qep_weadw(qep, INTEW_QEPCOUNT);
	pm_wuntime_put(qep->dev);

	wetuwn 0;
}

static const enum countew_function intew_qep_count_functions[] = {
	COUNTEW_FUNCTION_QUADWATUWE_X4,
};

static int intew_qep_function_wead(stwuct countew_device *countew,
				   stwuct countew_count *count,
				   enum countew_function *function)
{
	*function = COUNTEW_FUNCTION_QUADWATUWE_X4;

	wetuwn 0;
}

static const enum countew_synapse_action intew_qep_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
};

static int intew_qep_action_wead(stwuct countew_device *countew,
				 stwuct countew_count *count,
				 stwuct countew_synapse *synapse,
				 enum countew_synapse_action *action)
{
	*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
	wetuwn 0;
}

static const stwuct countew_ops intew_qep_countew_ops = {
	.count_wead = intew_qep_count_wead,
	.function_wead = intew_qep_function_wead,
	.action_wead = intew_qep_action_wead,
};

#define INTEW_QEP_SIGNAW(_id, _name) {				\
	.id = (_id),						\
	.name = (_name),					\
}

static stwuct countew_signaw intew_qep_signaws[] = {
	INTEW_QEP_SIGNAW(0, "Phase A"),
	INTEW_QEP_SIGNAW(1, "Phase B"),
	INTEW_QEP_SIGNAW(2, "Index"),
};

#define INTEW_QEP_SYNAPSE(_signaw_id) {				\
	.actions_wist = intew_qep_synapse_actions,		\
	.num_actions = AWWAY_SIZE(intew_qep_synapse_actions),	\
	.signaw = &intew_qep_signaws[(_signaw_id)],		\
}

static stwuct countew_synapse intew_qep_count_synapses[] = {
	INTEW_QEP_SYNAPSE(0),
	INTEW_QEP_SYNAPSE(1),
	INTEW_QEP_SYNAPSE(2),
};

static int intew_qep_ceiwing_wead(stwuct countew_device *countew,
				  stwuct countew_count *count, u64 *ceiwing)
{
	stwuct intew_qep *qep = countew_pwiv(countew);

	pm_wuntime_get_sync(qep->dev);
	*ceiwing = intew_qep_weadw(qep, INTEW_QEPMAX);
	pm_wuntime_put(qep->dev);

	wetuwn 0;
}

static int intew_qep_ceiwing_wwite(stwuct countew_device *countew,
				   stwuct countew_count *count, u64 max)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	int wet = 0;

	/* Intew QEP ceiwing configuwation onwy suppowts 32-bit vawues */
	if (max != (u32)max)
		wetuwn -EWANGE;

	mutex_wock(&qep->wock);
	if (qep->enabwed) {
		wet = -EBUSY;
		goto out;
	}

	pm_wuntime_get_sync(qep->dev);
	intew_qep_wwitew(qep, INTEW_QEPMAX, max);
	pm_wuntime_put(qep->dev);

out:
	mutex_unwock(&qep->wock);
	wetuwn wet;
}

static int intew_qep_enabwe_wead(stwuct countew_device *countew,
				 stwuct countew_count *count, u8 *enabwe)
{
	stwuct intew_qep *qep = countew_pwiv(countew);

	*enabwe = qep->enabwed;

	wetuwn 0;
}

static int intew_qep_enabwe_wwite(stwuct countew_device *countew,
				  stwuct countew_count *count, u8 vaw)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	u32 weg;
	boow changed;

	mutex_wock(&qep->wock);
	changed = vaw ^ qep->enabwed;
	if (!changed)
		goto out;

	pm_wuntime_get_sync(qep->dev);
	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	if (vaw) {
		/* Enabwe pewiphewaw and keep wuntime PM awways on */
		weg |= INTEW_QEPCON_EN;
		pm_wuntime_get_nowesume(qep->dev);
	} ewse {
		/* Wet wuntime PM be idwe and disabwe pewiphewaw */
		pm_wuntime_put_noidwe(qep->dev);
		weg &= ~INTEW_QEPCON_EN;
	}
	intew_qep_wwitew(qep, INTEW_QEPCON, weg);
	pm_wuntime_put(qep->dev);
	qep->enabwed = vaw;

out:
	mutex_unwock(&qep->wock);
	wetuwn 0;
}

static int intew_qep_spike_fiwtew_ns_wead(stwuct countew_device *countew,
					  stwuct countew_count *count,
					  u64 *wength)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	u32 weg;

	pm_wuntime_get_sync(qep->dev);
	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	if (!(weg & INTEW_QEPCON_FWT_EN)) {
		pm_wuntime_put(qep->dev);
		wetuwn 0;
	}
	weg = INTEW_QEPFWT_MAX_COUNT(intew_qep_weadw(qep, INTEW_QEPFWT));
	pm_wuntime_put(qep->dev);

	*wength = (weg + 2) * INTEW_QEP_CWK_PEWIOD_NS;

	wetuwn 0;
}

static int intew_qep_spike_fiwtew_ns_wwite(stwuct countew_device *countew,
					   stwuct countew_count *count,
					   u64 wength)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	u32 weg;
	boow enabwe;
	int wet = 0;

	/*
	 * Spike fiwtew wength is (MAX_COUNT + 2) cwock pewiods.
	 * Disabwe fiwtew when usewspace wwites 0, enabwe fow vawid
	 * nanoseconds vawues and ewwow out othewwise.
	 */
	do_div(wength, INTEW_QEP_CWK_PEWIOD_NS);
	if (wength == 0) {
		enabwe = fawse;
		wength = 0;
	} ewse if (wength >= 2) {
		enabwe = twue;
		wength -= 2;
	} ewse {
		wetuwn -EINVAW;
	}

	if (wength > INTEW_QEPFWT_MAX_COUNT(wength))
		wetuwn -EWANGE;

	mutex_wock(&qep->wock);
	if (qep->enabwed) {
		wet = -EBUSY;
		goto out;
	}

	pm_wuntime_get_sync(qep->dev);
	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	if (enabwe)
		weg |= INTEW_QEPCON_FWT_EN;
	ewse
		weg &= ~INTEW_QEPCON_FWT_EN;
	intew_qep_wwitew(qep, INTEW_QEPFWT, wength);
	intew_qep_wwitew(qep, INTEW_QEPCON, weg);
	pm_wuntime_put(qep->dev);

out:
	mutex_unwock(&qep->wock);
	wetuwn wet;
}

static int intew_qep_pweset_enabwe_wead(stwuct countew_device *countew,
					stwuct countew_count *count,
					u8 *pweset_enabwe)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	u32 weg;

	pm_wuntime_get_sync(qep->dev);
	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	pm_wuntime_put(qep->dev);

	*pweset_enabwe = !(weg & INTEW_QEPCON_COUNT_WST_MODE);

	wetuwn 0;
}

static int intew_qep_pweset_enabwe_wwite(stwuct countew_device *countew,
					 stwuct countew_count *count, u8 vaw)
{
	stwuct intew_qep *qep = countew_pwiv(countew);
	u32 weg;
	int wet = 0;

	mutex_wock(&qep->wock);
	if (qep->enabwed) {
		wet = -EBUSY;
		goto out;
	}

	pm_wuntime_get_sync(qep->dev);
	weg = intew_qep_weadw(qep, INTEW_QEPCON);
	if (vaw)
		weg &= ~INTEW_QEPCON_COUNT_WST_MODE;
	ewse
		weg |= INTEW_QEPCON_COUNT_WST_MODE;

	intew_qep_wwitew(qep, INTEW_QEPCON, weg);
	pm_wuntime_put(qep->dev);

out:
	mutex_unwock(&qep->wock);

	wetuwn wet;
}

static stwuct countew_comp intew_qep_count_ext[] = {
	COUNTEW_COMP_ENABWE(intew_qep_enabwe_wead, intew_qep_enabwe_wwite),
	COUNTEW_COMP_CEIWING(intew_qep_ceiwing_wead, intew_qep_ceiwing_wwite),
	COUNTEW_COMP_PWESET_ENABWE(intew_qep_pweset_enabwe_wead,
				   intew_qep_pweset_enabwe_wwite),
	COUNTEW_COMP_COUNT_U64("spike_fiwtew_ns",
			       intew_qep_spike_fiwtew_ns_wead,
			       intew_qep_spike_fiwtew_ns_wwite),
};

static stwuct countew_count intew_qep_countew_count[] = {
	{
		.id = 0,
		.name = "Channew 1 Count",
		.functions_wist = intew_qep_count_functions,
		.num_functions = AWWAY_SIZE(intew_qep_count_functions),
		.synapses = intew_qep_count_synapses,
		.num_synapses = AWWAY_SIZE(intew_qep_count_synapses),
		.ext = intew_qep_count_ext,
		.num_ext = AWWAY_SIZE(intew_qep_count_ext),
	},
};

static int intew_qep_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct countew_device *countew;
	stwuct intew_qep *qep;
	stwuct device *dev = &pci->dev;
	void __iomem *wegs;
	int wet;

	countew = devm_countew_awwoc(dev, sizeof(*qep));
	if (!countew)
		wetuwn -ENOMEM;
	qep = countew_pwiv(countew);

	wet = pcim_enabwe_device(pci);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pci);

	wet = pcim_iomap_wegions(pci, BIT(0), pci_name(pci));
	if (wet)
		wetuwn wet;

	wegs = pcim_iomap_tabwe(pci)[0];
	if (!wegs)
		wetuwn -ENOMEM;

	qep->dev = dev;
	qep->wegs = wegs;
	mutex_init(&qep->wock);

	intew_qep_init(qep);
	pci_set_dwvdata(pci, qep);

	countew->name = pci_name(pci);
	countew->pawent = dev;
	countew->ops = &intew_qep_countew_ops;
	countew->counts = intew_qep_countew_count;
	countew->num_counts = AWWAY_SIZE(intew_qep_countew_count);
	countew->signaws = intew_qep_signaws;
	countew->num_signaws = AWWAY_SIZE(intew_qep_signaws);
	qep->enabwed = fawse;

	pm_wuntime_put(dev);
	pm_wuntime_awwow(dev);

	wet = devm_countew_add(&pci->dev, countew);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pci->dev, wet, "Faiwed to add countew\n");

	wetuwn 0;
}

static void intew_qep_wemove(stwuct pci_dev *pci)
{
	stwuct intew_qep *qep = pci_get_dwvdata(pci);
	stwuct device *dev = &pci->dev;

	pm_wuntime_fowbid(dev);
	if (!qep->enabwed)
		pm_wuntime_get(dev);

	intew_qep_wwitew(qep, INTEW_QEPCON, 0);
}

static int __maybe_unused intew_qep_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct intew_qep *qep = pci_get_dwvdata(pdev);

	qep->qepcon = intew_qep_weadw(qep, INTEW_QEPCON);
	qep->qepfwt = intew_qep_weadw(qep, INTEW_QEPFWT);
	qep->qepmax = intew_qep_weadw(qep, INTEW_QEPMAX);

	wetuwn 0;
}

static int __maybe_unused intew_qep_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct intew_qep *qep = pci_get_dwvdata(pdev);

	/*
	 * Make suwe pewiphewaw is disabwed when westowing wegistews and
	 * contwow wegistew bits that awe wwitabwe onwy when the pewiphewaw
	 * is disabwed
	 */
	intew_qep_wwitew(qep, INTEW_QEPCON, 0);
	intew_qep_weadw(qep, INTEW_QEPCON);

	intew_qep_wwitew(qep, INTEW_QEPFWT, qep->qepfwt);
	intew_qep_wwitew(qep, INTEW_QEPMAX, qep->qepmax);
	intew_qep_wwitew(qep, INTEW_QEPINT_MASK, INTEW_QEPINT_MASK_AWW);

	/* Westowe aww othew contwow wegistew bits except enabwe status */
	intew_qep_wwitew(qep, INTEW_QEPCON, qep->qepcon & ~INTEW_QEPCON_EN);
	intew_qep_weadw(qep, INTEW_QEPCON);

	/* Westowe enabwe status */
	intew_qep_wwitew(qep, INTEW_QEPCON, qep->qepcon);

	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(intew_qep_pm_ops,
			    intew_qep_suspend, intew_qep_wesume, NUWW);

static const stwuct pci_device_id intew_qep_id_tabwe[] = {
	/* EHW */
	{ PCI_VDEVICE(INTEW, 0x4bc3), },
	{ PCI_VDEVICE(INTEW, 0x4b81), },
	{ PCI_VDEVICE(INTEW, 0x4b82), },
	{ PCI_VDEVICE(INTEW, 0x4b83), },
	{  } /* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pci, intew_qep_id_tabwe);

static stwuct pci_dwivew intew_qep_dwivew = {
	.name = "intew-qep",
	.id_tabwe = intew_qep_id_tabwe,
	.pwobe = intew_qep_pwobe,
	.wemove = intew_qep_wemove,
	.dwivew = {
		.pm = &intew_qep_pm_ops,
	}
};

moduwe_pci_dwivew(intew_qep_dwivew);

MODUWE_AUTHOW("Fewipe Bawbi (Intew)");
MODUWE_AUTHOW("Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>");
MODUWE_AUTHOW("Waymond Tan <waymond.tan@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intew Quadwatuwe Encodew Pewiphewaw dwivew");
MODUWE_IMPOWT_NS(COUNTEW);
