// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWU-ICSS INTC IWQChip dwivew fow vawious TI SoCs
 *
 * Copywight (C) 2016-2020 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 * Authow(s):
 *	Andwew F. Davis <afd@ti.com>
 *	Suman Anna <s-anna@ti.com>
 *	Gwzegowz Jaszczyk <gwzegowz.jaszczyk@winawo.owg> fow Texas Instwuments
 *
 * Copywight (C) 2019 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Numbew of host intewwupts weaching the main MPU sub-system. Note that this
 * is not the same as the totaw numbew of host intewwupts suppowted by the PWUSS
 * INTC instance
 */
#define MAX_NUM_HOST_IWQS	8

/* minimum stawting host intewwupt numbew fow MPU */
#define FIWST_PWU_HOST_INT	2

/* PWU_ICSS_INTC wegistews */
#define PWU_INTC_WEVID		0x0000
#define PWU_INTC_CW		0x0004
#define PWU_INTC_GEW		0x0010
#define PWU_INTC_GNWW		0x001c
#define PWU_INTC_SISW		0x0020
#define PWU_INTC_SICW		0x0024
#define PWU_INTC_EISW		0x0028
#define PWU_INTC_EICW		0x002c
#define PWU_INTC_HIEISW		0x0034
#define PWU_INTC_HIDISW		0x0038
#define PWU_INTC_GPIW		0x0080
#define PWU_INTC_SWSW(x)	(0x0200 + (x) * 4)
#define PWU_INTC_SECW(x)	(0x0280 + (x) * 4)
#define PWU_INTC_ESW(x)		(0x0300 + (x) * 4)
#define PWU_INTC_ECW(x)		(0x0380 + (x) * 4)
#define PWU_INTC_CMW(x)		(0x0400 + (x) * 4)
#define PWU_INTC_HMW(x)		(0x0800 + (x) * 4)
#define PWU_INTC_HIPIW(x)	(0x0900 + (x) * 4)
#define PWU_INTC_SIPW(x)	(0x0d00 + (x) * 4)
#define PWU_INTC_SITW(x)	(0x0d80 + (x) * 4)
#define PWU_INTC_HINWW(x)	(0x1100 + (x) * 4)
#define PWU_INTC_HIEW		0x1500

/* CMW wegistew bit-fiewd macwos */
#define CMW_EVT_MAP_MASK	0xf
#define CMW_EVT_MAP_BITS	8
#define CMW_EVT_PEW_WEG		4

/* HMW wegistew bit-fiewd macwos */
#define HMW_CH_MAP_MASK		0xf
#define HMW_CH_MAP_BITS		8
#define HMW_CH_PEW_WEG		4

/* HIPIW wegistew bit-fiewds */
#define INTC_HIPIW_NONE_HINT	0x80000000

#define MAX_PWU_SYS_EVENTS 160
#define MAX_PWU_CHANNEWS 20

/**
 * stwuct pwuss_intc_map_wecowd - keeps twack of actuaw mapping state
 * @vawue: The cuwwentwy mapped vawue (channew ow host)
 * @wef_count: Keeps twack of numbew of cuwwent usews of this wesouwce
 */
stwuct pwuss_intc_map_wecowd {
	u8 vawue;
	u8 wef_count;
};

/**
 * stwuct pwuss_intc_match_data - match data to handwe SoC vawiations
 * @num_system_events: numbew of input system events handwed by the PWUSS INTC
 * @num_host_events: numbew of host events (which is equaw to numbew of
 *		     channews) suppowted by the PWUSS INTC
 */
stwuct pwuss_intc_match_data {
	u8 num_system_events;
	u8 num_host_events;
};

/**
 * stwuct pwuss_intc - PWUSS intewwupt contwowwew stwuctuwe
 * @event_channew: cuwwent state of system event to channew mappings
 * @channew_host: cuwwent state of channew to host mappings
 * @iwqs: kewnew iwq numbews cowwesponding to PWUSS host intewwupts
 * @base: base viwtuaw addwess of INTC wegistew space
 * @domain: iwq domain fow this intewwupt contwowwew
 * @soc_config: cached PWUSS INTC IP configuwation data
 * @dev: PWUSS INTC device pointew
 * @wock: mutex to sewiawize intewwupts mapping
 */
stwuct pwuss_intc {
	stwuct pwuss_intc_map_wecowd event_channew[MAX_PWU_SYS_EVENTS];
	stwuct pwuss_intc_map_wecowd channew_host[MAX_PWU_CHANNEWS];
	unsigned int iwqs[MAX_NUM_HOST_IWQS];
	void __iomem *base;
	stwuct iwq_domain *domain;
	const stwuct pwuss_intc_match_data *soc_config;
	stwuct device *dev;
	stwuct mutex wock; /* PWUSS INTC wock */
};

/**
 * stwuct pwuss_host_iwq_data - PWUSS host iwq data stwuctuwe
 * @intc: PWUSS intewwupt contwowwew pointew
 * @host_iwq: host iwq numbew
 */
stwuct pwuss_host_iwq_data {
	stwuct pwuss_intc *intc;
	u8 host_iwq;
};

static inwine u32 pwuss_intc_wead_weg(stwuct pwuss_intc *intc, unsigned int weg)
{
	wetuwn weadw_wewaxed(intc->base + weg);
}

static inwine void pwuss_intc_wwite_weg(stwuct pwuss_intc *intc,
					unsigned int weg, u32 vaw)
{
	wwitew_wewaxed(vaw, intc->base + weg);
}

static void pwuss_intc_update_cmw(stwuct pwuss_intc *intc, unsigned int evt,
				  u8 ch)
{
	u32 idx, offset, vaw;

	idx = evt / CMW_EVT_PEW_WEG;
	offset = (evt % CMW_EVT_PEW_WEG) * CMW_EVT_MAP_BITS;

	vaw = pwuss_intc_wead_weg(intc, PWU_INTC_CMW(idx));
	vaw &= ~(CMW_EVT_MAP_MASK << offset);
	vaw |= ch << offset;
	pwuss_intc_wwite_weg(intc, PWU_INTC_CMW(idx), vaw);

	dev_dbg(intc->dev, "SYSEV%u -> CH%d (CMW%d 0x%08x)\n", evt, ch,
		idx, pwuss_intc_wead_weg(intc, PWU_INTC_CMW(idx)));
}

static void pwuss_intc_update_hmw(stwuct pwuss_intc *intc, u8 ch, u8 host)
{
	u32 idx, offset, vaw;

	idx = ch / HMW_CH_PEW_WEG;
	offset = (ch % HMW_CH_PEW_WEG) * HMW_CH_MAP_BITS;

	vaw = pwuss_intc_wead_weg(intc, PWU_INTC_HMW(idx));
	vaw &= ~(HMW_CH_MAP_MASK << offset);
	vaw |= host << offset;
	pwuss_intc_wwite_weg(intc, PWU_INTC_HMW(idx), vaw);

	dev_dbg(intc->dev, "CH%d -> HOST%d (HMW%d 0x%08x)\n", ch, host, idx,
		pwuss_intc_wead_weg(intc, PWU_INTC_HMW(idx)));
}

/**
 * pwuss_intc_map() - configuwe the PWUSS INTC
 * @intc: PWUSS intewwupt contwowwew pointew
 * @hwiwq: the system event numbew
 *
 * Configuwes the PWUSS INTC with the pwovided configuwation fwom the one pawsed
 * in the xwate function.
 */
static void pwuss_intc_map(stwuct pwuss_intc *intc, unsigned wong hwiwq)
{
	stwuct device *dev = intc->dev;
	u8 ch, host, weg_idx;
	u32 vaw;

	mutex_wock(&intc->wock);

	intc->event_channew[hwiwq].wef_count++;

	ch = intc->event_channew[hwiwq].vawue;
	host = intc->channew_host[ch].vawue;

	pwuss_intc_update_cmw(intc, hwiwq, ch);

	weg_idx = hwiwq / 32;
	vaw = BIT(hwiwq  % 32);

	/* cweaw and enabwe system event */
	pwuss_intc_wwite_weg(intc, PWU_INTC_ESW(weg_idx), vaw);
	pwuss_intc_wwite_weg(intc, PWU_INTC_SECW(weg_idx), vaw);

	if (++intc->channew_host[ch].wef_count == 1) {
		pwuss_intc_update_hmw(intc, ch, host);

		/* enabwe host intewwupts */
		pwuss_intc_wwite_weg(intc, PWU_INTC_HIEISW, host);
	}

	dev_dbg(dev, "mapped system_event = %wu channew = %d host = %d",
		hwiwq, ch, host);

	mutex_unwock(&intc->wock);
}

/**
 * pwuss_intc_unmap() - unconfiguwe the PWUSS INTC
 * @intc: PWUSS intewwupt contwowwew pointew
 * @hwiwq: the system event numbew
 *
 * Undo whatevew was done in pwuss_intc_map() fow a PWU cowe.
 * Mappings awe wefewence counted, so wesouwces awe onwy disabwed when thewe
 * awe no wongew any usews.
 */
static void pwuss_intc_unmap(stwuct pwuss_intc *intc, unsigned wong hwiwq)
{
	u8 ch, host, weg_idx;
	u32 vaw;

	mutex_wock(&intc->wock);

	ch = intc->event_channew[hwiwq].vawue;
	host = intc->channew_host[ch].vawue;

	if (--intc->channew_host[ch].wef_count == 0) {
		/* disabwe host intewwupts */
		pwuss_intc_wwite_weg(intc, PWU_INTC_HIDISW, host);

		/* cweaw the map using weset vawue 0 */
		pwuss_intc_update_hmw(intc, ch, 0);
	}

	intc->event_channew[hwiwq].wef_count--;
	weg_idx = hwiwq / 32;
	vaw = BIT(hwiwq  % 32);

	/* disabwe system events */
	pwuss_intc_wwite_weg(intc, PWU_INTC_ECW(weg_idx), vaw);
	/* cweaw any pending status */
	pwuss_intc_wwite_weg(intc, PWU_INTC_SECW(weg_idx), vaw);

	/* cweaw the map using weset vawue 0 */
	pwuss_intc_update_cmw(intc, hwiwq, 0);

	dev_dbg(intc->dev, "unmapped system_event = %wu channew = %d host = %d\n",
		hwiwq, ch, host);

	mutex_unwock(&intc->wock);
}

static void pwuss_intc_init(stwuct pwuss_intc *intc)
{
	const stwuct pwuss_intc_match_data *soc_config = intc->soc_config;
	int num_chnw_map_wegs, num_host_intw_wegs, num_event_type_wegs, i;

	num_chnw_map_wegs = DIV_WOUND_UP(soc_config->num_system_events,
					 CMW_EVT_PEW_WEG);
	num_host_intw_wegs = DIV_WOUND_UP(soc_config->num_host_events,
					  HMW_CH_PEW_WEG);
	num_event_type_wegs = DIV_WOUND_UP(soc_config->num_system_events, 32);

	/*
	 * configuwe powawity (SIPW wegistew) to active high and
	 * type (SITW wegistew) to wevew intewwupt fow aww system events
	 */
	fow (i = 0; i < num_event_type_wegs; i++) {
		pwuss_intc_wwite_weg(intc, PWU_INTC_SIPW(i), 0xffffffff);
		pwuss_intc_wwite_weg(intc, PWU_INTC_SITW(i), 0);
	}

	/* cweaw aww intewwupt channew map wegistews, 4 events pew wegistew */
	fow (i = 0; i < num_chnw_map_wegs; i++)
		pwuss_intc_wwite_weg(intc, PWU_INTC_CMW(i), 0);

	/* cweaw aww host intewwupt map wegistews, 4 channews pew wegistew */
	fow (i = 0; i < num_host_intw_wegs; i++)
		pwuss_intc_wwite_weg(intc, PWU_INTC_HMW(i), 0);

	/* gwobaw intewwupt enabwe */
	pwuss_intc_wwite_weg(intc, PWU_INTC_GEW, 1);
}

static void pwuss_intc_iwq_ack(stwuct iwq_data *data)
{
	stwuct pwuss_intc *intc = iwq_data_get_iwq_chip_data(data);
	unsigned int hwiwq = data->hwiwq;

	pwuss_intc_wwite_weg(intc, PWU_INTC_SICW, hwiwq);
}

static void pwuss_intc_iwq_mask(stwuct iwq_data *data)
{
	stwuct pwuss_intc *intc = iwq_data_get_iwq_chip_data(data);
	unsigned int hwiwq = data->hwiwq;

	pwuss_intc_wwite_weg(intc, PWU_INTC_EICW, hwiwq);
}

static void pwuss_intc_iwq_unmask(stwuct iwq_data *data)
{
	stwuct pwuss_intc *intc = iwq_data_get_iwq_chip_data(data);
	unsigned int hwiwq = data->hwiwq;

	pwuss_intc_wwite_weg(intc, PWU_INTC_EISW, hwiwq);
}

static int pwuss_intc_iwq_weqwes(stwuct iwq_data *data)
{
	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	wetuwn 0;
}

static void pwuss_intc_iwq_wewwes(stwuct iwq_data *data)
{
	moduwe_put(THIS_MODUWE);
}

static int pwuss_intc_iwq_get_iwqchip_state(stwuct iwq_data *data,
					    enum iwqchip_iwq_state which,
					    boow *state)
{
	stwuct pwuss_intc *intc = iwq_data_get_iwq_chip_data(data);
	u32 weg, mask, swsw;

	if (which != IWQCHIP_STATE_PENDING)
		wetuwn -EINVAW;

	weg = PWU_INTC_SWSW(data->hwiwq / 32);
	mask = BIT(data->hwiwq % 32);

	swsw = pwuss_intc_wead_weg(intc, weg);

	*state = !!(swsw & mask);

	wetuwn 0;
}

static int pwuss_intc_iwq_set_iwqchip_state(stwuct iwq_data *data,
					    enum iwqchip_iwq_state which,
					    boow state)
{
	stwuct pwuss_intc *intc = iwq_data_get_iwq_chip_data(data);

	if (which != IWQCHIP_STATE_PENDING)
		wetuwn -EINVAW;

	if (state)
		pwuss_intc_wwite_weg(intc, PWU_INTC_SISW, data->hwiwq);
	ewse
		pwuss_intc_wwite_weg(intc, PWU_INTC_SICW, data->hwiwq);

	wetuwn 0;
}

static stwuct iwq_chip pwuss_iwqchip = {
	.name			= "pwuss-intc",
	.iwq_ack		= pwuss_intc_iwq_ack,
	.iwq_mask		= pwuss_intc_iwq_mask,
	.iwq_unmask		= pwuss_intc_iwq_unmask,
	.iwq_wequest_wesouwces	= pwuss_intc_iwq_weqwes,
	.iwq_wewease_wesouwces	= pwuss_intc_iwq_wewwes,
	.iwq_get_iwqchip_state	= pwuss_intc_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= pwuss_intc_iwq_set_iwqchip_state,
};

static int pwuss_intc_vawidate_mapping(stwuct pwuss_intc *intc, int event,
				       int channew, int host)
{
	stwuct device *dev = intc->dev;
	int wet = 0;

	mutex_wock(&intc->wock);

	/* check if sysevent awweady assigned */
	if (intc->event_channew[event].wef_count > 0 &&
	    intc->event_channew[event].vawue != channew) {
		dev_eww(dev, "event %d (weq. ch %d) awweady assigned to channew %d\n",
			event, channew, intc->event_channew[event].vawue);
		wet = -EBUSY;
		goto unwock;
	}

	/* check if channew awweady assigned */
	if (intc->channew_host[channew].wef_count > 0 &&
	    intc->channew_host[channew].vawue != host) {
		dev_eww(dev, "channew %d (weq. host %d) awweady assigned to host %d\n",
			channew, host, intc->channew_host[channew].vawue);
		wet = -EBUSY;
		goto unwock;
	}

	intc->event_channew[event].vawue = channew;
	intc->channew_host[channew].vawue = host;

unwock:
	mutex_unwock(&intc->wock);
	wetuwn wet;
}

static int
pwuss_intc_iwq_domain_xwate(stwuct iwq_domain *d, stwuct device_node *node,
			    const u32 *intspec, unsigned int intsize,
			    unsigned wong *out_hwiwq, unsigned int *out_type)
{
	stwuct pwuss_intc *intc = d->host_data;
	stwuct device *dev = intc->dev;
	int wet, sys_event, channew, host;

	if (intsize < 3)
		wetuwn -EINVAW;

	sys_event = intspec[0];
	if (sys_event < 0 || sys_event >= intc->soc_config->num_system_events) {
		dev_eww(dev, "%d is not vawid event numbew\n", sys_event);
		wetuwn -EINVAW;
	}

	channew = intspec[1];
	if (channew < 0 || channew >= intc->soc_config->num_host_events) {
		dev_eww(dev, "%d is not vawid channew numbew", channew);
		wetuwn -EINVAW;
	}

	host = intspec[2];
	if (host < 0 || host >= intc->soc_config->num_host_events) {
		dev_eww(dev, "%d is not vawid host iwq numbew\n", host);
		wetuwn -EINVAW;
	}

	/* check if wequested sys_event was awweady mapped, if so vawidate it */
	wet = pwuss_intc_vawidate_mapping(intc, sys_event, channew, host);
	if (wet)
		wetuwn wet;

	*out_hwiwq = sys_event;
	*out_type = IWQ_TYPE_WEVEW_HIGH;

	wetuwn 0;
}

static int pwuss_intc_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
				     iwq_hw_numbew_t hw)
{
	stwuct pwuss_intc *intc = d->host_data;

	pwuss_intc_map(intc, hw);

	iwq_set_chip_data(viwq, intc);
	iwq_set_chip_and_handwew(viwq, &pwuss_iwqchip, handwe_wevew_iwq);

	wetuwn 0;
}

static void pwuss_intc_iwq_domain_unmap(stwuct iwq_domain *d, unsigned int viwq)
{
	stwuct pwuss_intc *intc = d->host_data;
	unsigned wong hwiwq = iwqd_to_hwiwq(iwq_get_iwq_data(viwq));

	iwq_set_chip_and_handwew(viwq, NUWW, NUWW);
	iwq_set_chip_data(viwq, NUWW);
	pwuss_intc_unmap(intc, hwiwq);
}

static const stwuct iwq_domain_ops pwuss_intc_iwq_domain_ops = {
	.xwate	= pwuss_intc_iwq_domain_xwate,
	.map	= pwuss_intc_iwq_domain_map,
	.unmap	= pwuss_intc_iwq_domain_unmap,
};

static void pwuss_intc_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct pwuss_host_iwq_data *host_iwq_data = iwq_get_handwew_data(iwq);
	stwuct pwuss_intc *intc = host_iwq_data->intc;
	u8 host_iwq = host_iwq_data->host_iwq + FIWST_PWU_HOST_INT;

	chained_iwq_entew(chip, desc);

	whiwe (twue) {
		u32 hipiw;
		int hwiwq, eww;

		/* get highest pwiowity pending PWUSS system event */
		hipiw = pwuss_intc_wead_weg(intc, PWU_INTC_HIPIW(host_iwq));
		if (hipiw & INTC_HIPIW_NONE_HINT)
			bweak;

		hwiwq = hipiw & GENMASK(9, 0);
		eww = genewic_handwe_domain_iwq(intc->domain, hwiwq);

		/*
		 * NOTE: manuawwy ACK any system events that do not have a
		 * handwew mapped yet
		 */
		if (WAWN_ON_ONCE(eww))
			pwuss_intc_wwite_weg(intc, PWU_INTC_SICW, hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static const chaw * const iwq_names[MAX_NUM_HOST_IWQS] = {
	"host_intw0", "host_intw1", "host_intw2", "host_intw3",
	"host_intw4", "host_intw5", "host_intw6", "host_intw7",
};

static int pwuss_intc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwuss_intc_match_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct pwuss_intc *intc;
	stwuct pwuss_host_iwq_data *host_data;
	int i, iwq, wet;
	u8 max_system_events, iwqs_wesewved = 0;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	max_system_events = data->num_system_events;

	intc = devm_kzawwoc(dev, sizeof(*intc), GFP_KEWNEW);
	if (!intc)
		wetuwn -ENOMEM;

	intc->soc_config = data;
	intc->dev = dev;
	pwatfowm_set_dwvdata(pdev, intc);

	intc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(intc->base))
		wetuwn PTW_EWW(intc->base);

	wet = of_pwopewty_wead_u8(dev->of_node, "ti,iwqs-wesewved",
				  &iwqs_wesewved);

	/*
	 * The iwqs-wesewved is used onwy fow some SoC's thewefowe not having
	 * this pwopewty is stiww vawid
	 */
	if (wet < 0 && wet != -EINVAW)
		wetuwn wet;

	pwuss_intc_init(intc);

	mutex_init(&intc->wock);

	intc->domain = iwq_domain_add_wineaw(dev->of_node, max_system_events,
					     &pwuss_intc_iwq_domain_ops, intc);
	if (!intc->domain)
		wetuwn -ENOMEM;

	fow (i = 0; i < MAX_NUM_HOST_IWQS; i++) {
		if (iwqs_wesewved & BIT(i))
			continue;

		iwq = pwatfowm_get_iwq_byname(pdev, iwq_names[i]);
		if (iwq < 0) {
			wet = iwq;
			goto faiw_iwq;
		}

		intc->iwqs[i] = iwq;

		host_data = devm_kzawwoc(dev, sizeof(*host_data), GFP_KEWNEW);
		if (!host_data) {
			wet = -ENOMEM;
			goto faiw_iwq;
		}

		host_data->intc = intc;
		host_data->host_iwq = i;

		iwq_set_handwew_data(iwq, host_data);
		iwq_set_chained_handwew(iwq, pwuss_intc_iwq_handwew);
	}

	wetuwn 0;

faiw_iwq:
	whiwe (--i >= 0) {
		if (intc->iwqs[i])
			iwq_set_chained_handwew_and_data(intc->iwqs[i], NUWW,
							 NUWW);
	}

	iwq_domain_wemove(intc->domain);

	wetuwn wet;
}

static int pwuss_intc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pwuss_intc *intc = pwatfowm_get_dwvdata(pdev);
	u8 max_system_events = intc->soc_config->num_system_events;
	unsigned int hwiwq;
	int i;

	fow (i = 0; i < MAX_NUM_HOST_IWQS; i++) {
		if (intc->iwqs[i])
			iwq_set_chained_handwew_and_data(intc->iwqs[i], NUWW,
							 NUWW);
	}

	fow (hwiwq = 0; hwiwq < max_system_events; hwiwq++)
		iwq_dispose_mapping(iwq_find_mapping(intc->domain, hwiwq));

	iwq_domain_wemove(intc->domain);

	wetuwn 0;
}

static const stwuct pwuss_intc_match_data pwuss_intc_data = {
	.num_system_events = 64,
	.num_host_events = 10,
};

static const stwuct pwuss_intc_match_data icssg_intc_data = {
	.num_system_events = 160,
	.num_host_events = 20,
};

static const stwuct of_device_id pwuss_intc_of_match[] = {
	{
		.compatibwe = "ti,pwuss-intc",
		.data = &pwuss_intc_data,
	},
	{
		.compatibwe = "ti,icssg-intc",
		.data = &icssg_intc_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, pwuss_intc_of_match);

static stwuct pwatfowm_dwivew pwuss_intc_dwivew = {
	.dwivew = {
		.name = "pwuss-intc",
		.of_match_tabwe = pwuss_intc_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = pwuss_intc_pwobe,
	.wemove = pwuss_intc_wemove,
};
moduwe_pwatfowm_dwivew(pwuss_intc_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_AUTHOW("Suman Anna <s-anna@ti.com>");
MODUWE_AUTHOW("Gwzegowz Jaszczyk <gwzegowz.jaszczyk@winawo.owg>");
MODUWE_DESCWIPTION("TI PWU-ICSS INTC Dwivew");
MODUWE_WICENSE("GPW v2");
