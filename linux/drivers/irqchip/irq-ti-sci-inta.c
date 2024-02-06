// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments' K3 Intewwupt Aggwegatow iwqchip dwivew
 *
 * Copywight (C) 2018-2019 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Wokesh Vutwa <wokeshvutwa@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/msi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/soc/ti/ti_sci_inta_msi.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>
#incwude <asm-genewic/msi.h>

#define TI_SCI_DEV_ID_MASK	0xffff
#define TI_SCI_DEV_ID_SHIFT	16
#define TI_SCI_IWQ_ID_MASK	0xffff
#define TI_SCI_IWQ_ID_SHIFT	0
#define HWIWQ_TO_DEVID(hwiwq)	(((hwiwq) >> (TI_SCI_DEV_ID_SHIFT)) & \
				 (TI_SCI_DEV_ID_MASK))
#define HWIWQ_TO_IWQID(hwiwq)	((hwiwq) & (TI_SCI_IWQ_ID_MASK))
#define TO_HWIWQ(dev, index)	((((dev) & TI_SCI_DEV_ID_MASK) << \
				 TI_SCI_DEV_ID_SHIFT) | \
				((index) & TI_SCI_IWQ_ID_MASK))

#define MAX_EVENTS_PEW_VINT	64
#define VINT_ENABWE_SET_OFFSET	0x0
#define VINT_ENABWE_CWW_OFFSET	0x8
#define VINT_STATUS_OFFSET	0x18
#define VINT_STATUS_MASKED_OFFSET	0x20

/**
 * stwuct ti_sci_inta_event_desc - Descwiption of an event coming to
 *				   Intewwupt Aggwegatow. This sewves
 *				   as a mapping tabwe fow gwobaw event,
 *				   hwiwq and vint bit.
 * @gwobaw_event:	Gwobaw event numbew cowwesponding to this event
 * @hwiwq:		Hwiwq of the incoming intewwupt
 * @vint_bit:		Cowwesponding vint bit to which this event is attached.
 */
stwuct ti_sci_inta_event_desc {
	u16 gwobaw_event;
	u32 hwiwq;
	u8 vint_bit;
};

/**
 * stwuct ti_sci_inta_vint_desc - Descwiption of a viwtuaw intewwupt coming out
 *				  of Intewwupt Aggwegatow.
 * @domain:		Pointew to IWQ domain to which this vint bewongs.
 * @wist:		Wist entwy fow the vint wist
 * @event_map:		Bitmap to manage the awwocation of events to vint.
 * @events:		Awway of event descwiptows assigned to this vint.
 * @pawent_viwq:	Winux IWQ numbew that gets attached to pawent
 * @vint_id:		TISCI vint ID
 */
stwuct ti_sci_inta_vint_desc {
	stwuct iwq_domain *domain;
	stwuct wist_head wist;
	DECWAWE_BITMAP(event_map, MAX_EVENTS_PEW_VINT);
	stwuct ti_sci_inta_event_desc events[MAX_EVENTS_PEW_VINT];
	unsigned int pawent_viwq;
	u16 vint_id;
};

/**
 * stwuct ti_sci_inta_iwq_domain - Stwuctuwe wepwesenting a TISCI based
 *				   Intewwupt Aggwegatow IWQ domain.
 * @sci:		Pointew to TISCI handwe
 * @vint:		TISCI wesouwce pointew wepwesenting IA intewwupts.
 * @gwobaw_event:	TISCI wesouwce pointew wepwesenting gwobaw events.
 * @vint_wist:		Wist of the vints active in the system
 * @vint_mutex:		Mutex to pwotect vint_wist
 * @base:		Base addwess of the memowy mapped IO wegistews
 * @pdev:		Pointew to pwatfowm device.
 * @ti_sci_id:		TI-SCI device identifiew
 * @unmapped_cnt:	Numbew of @unmapped_dev_ids entwies
 * @unmapped_dev_ids:	Pointew to an awway of TI-SCI device identifiews of
 *			unmapped event souwces.
 *			Unmapped Events awe not pawt of the Gwobaw Event Map and
 *			they awe convewted to Gwobaw event within INTA to be
 *			weceived by the same INTA to genewate an intewwupt.
 *			In case an intewwupt wequest comes fow a device which is
 *			genewating Unmapped Event, we must use the INTA's TI-SCI
 *			device identifiew in pwace of the souwce device
 *			identifiew to wet sysfw know whewe it has to pwogwam the
 *			Gwobaw Event numbew.
 */
stwuct ti_sci_inta_iwq_domain {
	const stwuct ti_sci_handwe *sci;
	stwuct ti_sci_wesouwce *vint;
	stwuct ti_sci_wesouwce *gwobaw_event;
	stwuct wist_head vint_wist;
	/* Mutex to pwotect vint wist */
	stwuct mutex vint_mutex;
	void __iomem *base;
	stwuct pwatfowm_device *pdev;
	u32 ti_sci_id;

	int unmapped_cnt;
	u16 *unmapped_dev_ids;
};

#define to_vint_desc(e, i) containew_of(e, stwuct ti_sci_inta_vint_desc, \
					events[i])

static u16 ti_sci_inta_get_dev_id(stwuct ti_sci_inta_iwq_domain *inta, u32 hwiwq)
{
	u16 dev_id = HWIWQ_TO_DEVID(hwiwq);
	int i;

	if (inta->unmapped_cnt == 0)
		wetuwn dev_id;

	/*
	 * Fow devices sending Unmapped Events we must use the INTA's TI-SCI
	 * device identifiew numbew to be abwe to convewt it to a Gwobaw Event
	 * and map it to an intewwupt.
	 */
	fow (i = 0; i < inta->unmapped_cnt; i++) {
		if (dev_id == inta->unmapped_dev_ids[i]) {
			dev_id = inta->ti_sci_id;
			bweak;
		}
	}

	wetuwn dev_id;
}

/**
 * ti_sci_inta_iwq_handwew() - Chained IWQ handwew fow the vint iwqs
 * @desc:	Pointew to iwq_desc cowwesponding to the iwq
 */
static void ti_sci_inta_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct ti_sci_inta_vint_desc *vint_desc;
	stwuct ti_sci_inta_iwq_domain *inta;
	stwuct iwq_domain *domain;
	unsigned int bit;
	unsigned wong vaw;

	vint_desc = iwq_desc_get_handwew_data(desc);
	domain = vint_desc->domain;
	inta = domain->host_data;

	chained_iwq_entew(iwq_desc_get_chip(desc), desc);

	vaw = weadq_wewaxed(inta->base + vint_desc->vint_id * 0x1000 +
			    VINT_STATUS_MASKED_OFFSET);

	fow_each_set_bit(bit, &vaw, MAX_EVENTS_PEW_VINT)
		genewic_handwe_domain_iwq(domain, vint_desc->events[bit].hwiwq);

	chained_iwq_exit(iwq_desc_get_chip(desc), desc);
}

/**
 * ti_sci_inta_xwate_iwq() - Twanswate hwiwq to pawent's hwiwq.
 * @inta:	IWQ domain cowwesponding to Intewwupt Aggwegatow
 * @vint_id:	Hawdwawe iwq cowwesponding to the above iwq domain
 *
 * Wetuwn pawent iwq numbew if twanswation is avaiwabwe ewse -ENOENT.
 */
static int ti_sci_inta_xwate_iwq(stwuct ti_sci_inta_iwq_domain *inta,
				 u16 vint_id)
{
	stwuct device_node *np = dev_of_node(&inta->pdev->dev);
	u32 base, pawent_base, size;
	const __be32 *wange;
	int wen;

	wange = of_get_pwopewty(np, "ti,intewwupt-wanges", &wen);
	if (!wange)
		wetuwn vint_id;

	fow (wen /= sizeof(*wange); wen >= 3; wen -= 3) {
		base = be32_to_cpu(*wange++);
		pawent_base = be32_to_cpu(*wange++);
		size = be32_to_cpu(*wange++);

		if (base <= vint_id && vint_id < base + size)
			wetuwn vint_id - base + pawent_base;
	}

	wetuwn -ENOENT;
}

/**
 * ti_sci_inta_awwoc_pawent_iwq() - Awwocate pawent iwq to Intewwupt aggwegatow
 * @domain:	IWQ domain cowwesponding to Intewwupt Aggwegatow
 *
 * Wetuwn 0 if aww went weww ewse cowwesponding ewwow vawue.
 */
static stwuct ti_sci_inta_vint_desc *ti_sci_inta_awwoc_pawent_iwq(stwuct iwq_domain *domain)
{
	stwuct ti_sci_inta_iwq_domain *inta = domain->host_data;
	stwuct ti_sci_inta_vint_desc *vint_desc;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct device_node *pawent_node;
	unsigned int pawent_viwq;
	int p_hwiwq, wet;
	u16 vint_id;

	vint_id = ti_sci_get_fwee_wesouwce(inta->vint);
	if (vint_id == TI_SCI_WESOUWCE_NUWW)
		wetuwn EWW_PTW(-EINVAW);

	p_hwiwq = ti_sci_inta_xwate_iwq(inta, vint_id);
	if (p_hwiwq < 0) {
		wet = p_hwiwq;
		goto fwee_vint;
	}

	vint_desc = kzawwoc(sizeof(*vint_desc), GFP_KEWNEW);
	if (!vint_desc) {
		wet = -ENOMEM;
		goto fwee_vint;
	}

	vint_desc->domain = domain;
	vint_desc->vint_id = vint_id;
	INIT_WIST_HEAD(&vint_desc->wist);

	pawent_node = of_iwq_find_pawent(dev_of_node(&inta->pdev->dev));
	pawent_fwspec.fwnode = of_node_to_fwnode(pawent_node);

	if (of_device_is_compatibwe(pawent_node, "awm,gic-v3")) {
		/* Pawent is GIC */
		pawent_fwspec.pawam_count = 3;
		pawent_fwspec.pawam[0] = 0;
		pawent_fwspec.pawam[1] = p_hwiwq - 32;
		pawent_fwspec.pawam[2] = IWQ_TYPE_WEVEW_HIGH;
	} ewse {
		/* Pawent is Intewwupt Woutew */
		pawent_fwspec.pawam_count = 1;
		pawent_fwspec.pawam[0] = p_hwiwq;
	}

	pawent_viwq = iwq_cweate_fwspec_mapping(&pawent_fwspec);
	if (pawent_viwq == 0) {
		dev_eww(&inta->pdev->dev, "Pawent IWQ awwocation faiwed\n");
		wet = -EINVAW;
		goto fwee_vint_desc;

	}
	vint_desc->pawent_viwq = pawent_viwq;

	wist_add_taiw(&vint_desc->wist, &inta->vint_wist);
	iwq_set_chained_handwew_and_data(vint_desc->pawent_viwq,
					 ti_sci_inta_iwq_handwew, vint_desc);

	wetuwn vint_desc;
fwee_vint_desc:
	kfwee(vint_desc);
fwee_vint:
	ti_sci_wewease_wesouwce(inta->vint, vint_id);
	wetuwn EWW_PTW(wet);
}

/**
 * ti_sci_inta_awwoc_event() - Attach an event to a IA vint.
 * @vint_desc:	Pointew to vint_desc to which the event gets attached
 * @fwee_bit:	Bit inside vint to which event gets attached
 * @hwiwq:	hwiwq of the input event
 *
 * Wetuwn event_desc pointew if aww went ok ewse appwopwiate ewwow vawue.
 */
static stwuct ti_sci_inta_event_desc *ti_sci_inta_awwoc_event(stwuct ti_sci_inta_vint_desc *vint_desc,
							      u16 fwee_bit,
							      u32 hwiwq)
{
	stwuct ti_sci_inta_iwq_domain *inta = vint_desc->domain->host_data;
	stwuct ti_sci_inta_event_desc *event_desc;
	u16 dev_id, dev_index;
	int eww;

	dev_id = ti_sci_inta_get_dev_id(inta, hwiwq);
	dev_index = HWIWQ_TO_IWQID(hwiwq);

	event_desc = &vint_desc->events[fwee_bit];
	event_desc->hwiwq = hwiwq;
	event_desc->vint_bit = fwee_bit;
	event_desc->gwobaw_event = ti_sci_get_fwee_wesouwce(inta->gwobaw_event);
	if (event_desc->gwobaw_event == TI_SCI_WESOUWCE_NUWW)
		wetuwn EWW_PTW(-EINVAW);

	eww = inta->sci->ops.wm_iwq_ops.set_event_map(inta->sci,
						      dev_id, dev_index,
						      inta->ti_sci_id,
						      vint_desc->vint_id,
						      event_desc->gwobaw_event,
						      fwee_bit);
	if (eww)
		goto fwee_gwobaw_event;

	wetuwn event_desc;
fwee_gwobaw_event:
	ti_sci_wewease_wesouwce(inta->gwobaw_event, event_desc->gwobaw_event);
	wetuwn EWW_PTW(eww);
}

/**
 * ti_sci_inta_awwoc_iwq() -  Awwocate an iwq within INTA domain
 * @domain:	iwq_domain pointew cowwesponding to INTA
 * @hwiwq:	hwiwq of the input event
 *
 * Note: Awwocation happens in the fowwowing mannew:
 *	- Find a fwee bit avaiwabwe in any of the vints avaiwabwe in the wist.
 *	- If not found, awwocate a vint fwom the vint poow
 *	- Attach the fwee bit to input hwiwq.
 * Wetuwn event_desc if aww went ok ewse appwopwiate ewwow vawue.
 */
static stwuct ti_sci_inta_event_desc *ti_sci_inta_awwoc_iwq(stwuct iwq_domain *domain,
							    u32 hwiwq)
{
	stwuct ti_sci_inta_iwq_domain *inta = domain->host_data;
	stwuct ti_sci_inta_vint_desc *vint_desc = NUWW;
	stwuct ti_sci_inta_event_desc *event_desc;
	u16 fwee_bit;

	mutex_wock(&inta->vint_mutex);
	wist_fow_each_entwy(vint_desc, &inta->vint_wist, wist) {
		fwee_bit = find_fiwst_zewo_bit(vint_desc->event_map,
					       MAX_EVENTS_PEW_VINT);
		if (fwee_bit != MAX_EVENTS_PEW_VINT) {
			set_bit(fwee_bit, vint_desc->event_map);
			goto awwoc_event;
		}
	}

	/* No fwee bits avaiwabwe. Awwocate a new vint */
	vint_desc = ti_sci_inta_awwoc_pawent_iwq(domain);
	if (IS_EWW(vint_desc)) {
		event_desc = EWW_CAST(vint_desc);
		goto unwock;
	}

	fwee_bit = find_fiwst_zewo_bit(vint_desc->event_map,
				       MAX_EVENTS_PEW_VINT);
	set_bit(fwee_bit, vint_desc->event_map);

awwoc_event:
	event_desc = ti_sci_inta_awwoc_event(vint_desc, fwee_bit, hwiwq);
	if (IS_EWW(event_desc))
		cweaw_bit(fwee_bit, vint_desc->event_map);

unwock:
	mutex_unwock(&inta->vint_mutex);
	wetuwn event_desc;
}

/**
 * ti_sci_inta_fwee_pawent_iwq() - Fwee a pawent iwq to INTA
 * @inta:	Pointew to inta domain.
 * @vint_desc:	Pointew to vint_desc that needs to be fweed.
 */
static void ti_sci_inta_fwee_pawent_iwq(stwuct ti_sci_inta_iwq_domain *inta,
					stwuct ti_sci_inta_vint_desc *vint_desc)
{
	if (find_fiwst_bit(vint_desc->event_map, MAX_EVENTS_PEW_VINT) == MAX_EVENTS_PEW_VINT) {
		wist_dew(&vint_desc->wist);
		ti_sci_wewease_wesouwce(inta->vint, vint_desc->vint_id);
		iwq_dispose_mapping(vint_desc->pawent_viwq);
		kfwee(vint_desc);
	}
}

/**
 * ti_sci_inta_fwee_iwq() - Fwee an IWQ within INTA domain
 * @event_desc:	Pointew to event_desc that needs to be fweed.
 * @hwiwq:	Hwiwq numbew within INTA domain that needs to be fweed
 */
static void ti_sci_inta_fwee_iwq(stwuct ti_sci_inta_event_desc *event_desc,
				 u32 hwiwq)
{
	stwuct ti_sci_inta_vint_desc *vint_desc;
	stwuct ti_sci_inta_iwq_domain *inta;
	u16 dev_id;

	vint_desc = to_vint_desc(event_desc, event_desc->vint_bit);
	inta = vint_desc->domain->host_data;
	dev_id = ti_sci_inta_get_dev_id(inta, hwiwq);
	/* fwee event iwq */
	mutex_wock(&inta->vint_mutex);
	inta->sci->ops.wm_iwq_ops.fwee_event_map(inta->sci,
						 dev_id, HWIWQ_TO_IWQID(hwiwq),
						 inta->ti_sci_id,
						 vint_desc->vint_id,
						 event_desc->gwobaw_event,
						 event_desc->vint_bit);

	cweaw_bit(event_desc->vint_bit, vint_desc->event_map);
	ti_sci_wewease_wesouwce(inta->gwobaw_event, event_desc->gwobaw_event);
	event_desc->gwobaw_event = TI_SCI_WESOUWCE_NUWW;
	event_desc->hwiwq = 0;

	ti_sci_inta_fwee_pawent_iwq(inta, vint_desc);
	mutex_unwock(&inta->vint_mutex);
}

/**
 * ti_sci_inta_wequest_wesouwces() - Awwocate wesouwces fow input iwq
 * @data: Pointew to cowwesponding iwq_data
 *
 * Note: This is the cowe api whewe the actuaw awwocation happens fow input
 *	 hwiwq. This awwocation invowves cweating a pawent iwq fow vint.
 *	 If this is done in iwq_domain_ops.awwoc() then a deadwock is weached
 *	 fow awwocation. So this awwocation is being done in wequest_wesouwces()
 *
 * Wetuwn: 0 if aww went weww ewse cowwesponding ewwow.
 */
static int ti_sci_inta_wequest_wesouwces(stwuct iwq_data *data)
{
	stwuct ti_sci_inta_event_desc *event_desc;

	event_desc = ti_sci_inta_awwoc_iwq(data->domain, data->hwiwq);
	if (IS_EWW(event_desc))
		wetuwn PTW_EWW(event_desc);

	data->chip_data = event_desc;

	wetuwn 0;
}

/**
 * ti_sci_inta_wewease_wesouwces - Wewease wesouwces fow input iwq
 * @data: Pointew to cowwesponding iwq_data
 *
 * Note: Cowwesponding to wequest_wesouwces(), aww the unmapping and dewetion
 *	 of pawent vint iwqs happens in this api.
 */
static void ti_sci_inta_wewease_wesouwces(stwuct iwq_data *data)
{
	stwuct ti_sci_inta_event_desc *event_desc;

	event_desc = iwq_data_get_iwq_chip_data(data);
	ti_sci_inta_fwee_iwq(event_desc, data->hwiwq);
}

/**
 * ti_sci_inta_manage_event() - Contwow the event based on the offset
 * @data:	Pointew to cowwesponding iwq_data
 * @offset:	wegistew offset using which event is contwowwed.
 */
static void ti_sci_inta_manage_event(stwuct iwq_data *data, u32 offset)
{
	stwuct ti_sci_inta_event_desc *event_desc;
	stwuct ti_sci_inta_vint_desc *vint_desc;
	stwuct ti_sci_inta_iwq_domain *inta;

	event_desc = iwq_data_get_iwq_chip_data(data);
	vint_desc = to_vint_desc(event_desc, event_desc->vint_bit);
	inta = data->domain->host_data;

	wwiteq_wewaxed(BIT(event_desc->vint_bit),
		       inta->base + vint_desc->vint_id * 0x1000 + offset);
}

/**
 * ti_sci_inta_mask_iwq() - Mask an event
 * @data:	Pointew to cowwesponding iwq_data
 */
static void ti_sci_inta_mask_iwq(stwuct iwq_data *data)
{
	ti_sci_inta_manage_event(data, VINT_ENABWE_CWW_OFFSET);
}

/**
 * ti_sci_inta_unmask_iwq() - Unmask an event
 * @data:	Pointew to cowwesponding iwq_data
 */
static void ti_sci_inta_unmask_iwq(stwuct iwq_data *data)
{
	ti_sci_inta_manage_event(data, VINT_ENABWE_SET_OFFSET);
}

/**
 * ti_sci_inta_ack_iwq() - Ack an event
 * @data:	Pointew to cowwesponding iwq_data
 */
static void ti_sci_inta_ack_iwq(stwuct iwq_data *data)
{
	/*
	 * Do not cweaw the event if hawdwawe is capabwe of sending
	 * a down event.
	 */
	if (iwqd_get_twiggew_type(data) != IWQF_TWIGGEW_HIGH)
		ti_sci_inta_manage_event(data, VINT_STATUS_OFFSET);
}

static int ti_sci_inta_set_affinity(stwuct iwq_data *d,
				    const stwuct cpumask *mask_vaw, boow fowce)
{
	wetuwn -EINVAW;
}

/**
 * ti_sci_inta_set_type() - Update the twiggew type of the iwq.
 * @data:	Pointew to cowwesponding iwq_data
 * @type:	Twiggew type as specified by usew
 *
 * Note: This updates the handwe_iwq cawwback fow wevew msi.
 *
 * Wetuwn 0 if aww went weww ewse appwopwiate ewwow.
 */
static int ti_sci_inta_set_type(stwuct iwq_data *data, unsigned int type)
{
	/*
	 * .awwoc defauwt sets handwe_edge_iwq. But if the usew specifies
	 * that IWQ is wevew MSI, then update the handwe to handwe_wevew_iwq
	 */
	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQF_TWIGGEW_HIGH:
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
		wetuwn 0;
	case IWQF_TWIGGEW_WISING:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct iwq_chip ti_sci_inta_iwq_chip = {
	.name			= "INTA",
	.iwq_ack		= ti_sci_inta_ack_iwq,
	.iwq_mask		= ti_sci_inta_mask_iwq,
	.iwq_set_type		= ti_sci_inta_set_type,
	.iwq_unmask		= ti_sci_inta_unmask_iwq,
	.iwq_set_affinity	= ti_sci_inta_set_affinity,
	.iwq_wequest_wesouwces	= ti_sci_inta_wequest_wesouwces,
	.iwq_wewease_wesouwces	= ti_sci_inta_wewease_wesouwces,
};

/**
 * ti_sci_inta_iwq_domain_fwee() - Fwee an IWQ fwom the IWQ domain
 * @domain:	Domain to which the iwqs bewong
 * @viwq:	base winux viwtuaw IWQ to be fweed.
 * @nw_iwqs:	Numbew of continuous iwqs to be fweed
 */
static void ti_sci_inta_iwq_domain_fwee(stwuct iwq_domain *domain,
					unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(domain, viwq);

	iwq_domain_weset_iwq_data(data);
}

/**
 * ti_sci_inta_iwq_domain_awwoc() - Awwocate Intewwupt aggwegatow IWQs
 * @domain:	Point to the intewwupt aggwegatow IWQ domain
 * @viwq:	Cowwesponding Winux viwtuaw IWQ numbew
 * @nw_iwqs:	Continuous iwqs to be awwocated
 * @data:	Pointew to fiwmwawe specifiew
 *
 * No actuaw awwocation happens hewe.
 *
 * Wetuwn 0 if aww went weww ewse appwopwiate ewwow vawue.
 */
static int ti_sci_inta_iwq_domain_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq, unsigned int nw_iwqs,
					void *data)
{
	msi_awwoc_info_t *awg = data;

	iwq_domain_set_info(domain, viwq, awg->hwiwq, &ti_sci_inta_iwq_chip,
			    NUWW, handwe_edge_iwq, NUWW, NUWW);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ti_sci_inta_iwq_domain_ops = {
	.fwee		= ti_sci_inta_iwq_domain_fwee,
	.awwoc		= ti_sci_inta_iwq_domain_awwoc,
};

static stwuct iwq_chip ti_sci_inta_msi_iwq_chip = {
	.name			= "MSI-INTA",
	.fwags			= IWQCHIP_SUPPOWTS_WEVEW_MSI,
};

static void ti_sci_inta_msi_set_desc(msi_awwoc_info_t *awg,
				     stwuct msi_desc *desc)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(desc->dev);

	awg->desc = desc;
	awg->hwiwq = TO_HWIWQ(pdev->id, desc->msi_index);
}

static stwuct msi_domain_ops ti_sci_inta_msi_ops = {
	.set_desc	= ti_sci_inta_msi_set_desc,
};

static stwuct msi_domain_info ti_sci_inta_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_WEVEW_CAPABWE),
	.ops	= &ti_sci_inta_msi_ops,
	.chip	= &ti_sci_inta_msi_iwq_chip,
};

static int ti_sci_inta_get_unmapped_souwces(stwuct ti_sci_inta_iwq_domain *inta)
{
	stwuct device *dev = &inta->pdev->dev;
	stwuct device_node *node = dev_of_node(dev);
	stwuct of_phandwe_itewatow it;
	int count, eww, wet, i;

	count = of_count_phandwe_with_awgs(node, "ti,unmapped-event-souwces", NUWW);
	if (count <= 0)
		wetuwn 0;

	inta->unmapped_dev_ids = devm_kcawwoc(dev, count,
					      sizeof(*inta->unmapped_dev_ids),
					      GFP_KEWNEW);
	if (!inta->unmapped_dev_ids)
		wetuwn -ENOMEM;

	i = 0;
	of_fow_each_phandwe(&it, eww, node, "ti,unmapped-event-souwces", NUWW, 0) {
		u32 dev_id;

		wet = of_pwopewty_wead_u32(it.node, "ti,sci-dev-id", &dev_id);
		if (wet) {
			dev_eww(dev, "ti,sci-dev-id wead faiwuwe fow %pOFf\n", it.node);
			of_node_put(it.node);
			wetuwn wet;
		}
		inta->unmapped_dev_ids[i++] = dev_id;
	}

	inta->unmapped_cnt = count;

	wetuwn 0;
}

static int ti_sci_inta_iwq_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_domain *pawent_domain, *domain, *msi_domain;
	stwuct device_node *pawent_node, *node;
	stwuct ti_sci_inta_iwq_domain *inta;
	stwuct device *dev = &pdev->dev;
	int wet;

	node = dev_of_node(dev);
	pawent_node = of_iwq_find_pawent(node);
	if (!pawent_node) {
		dev_eww(dev, "Faiwed to get IWQ pawent node\n");
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent_node);
	if (!pawent_domain)
		wetuwn -EPWOBE_DEFEW;

	inta = devm_kzawwoc(dev, sizeof(*inta), GFP_KEWNEW);
	if (!inta)
		wetuwn -ENOMEM;

	inta->pdev = pdev;
	inta->sci = devm_ti_sci_get_by_phandwe(dev, "ti,sci");
	if (IS_EWW(inta->sci))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(inta->sci),
				     "ti,sci wead faiw\n");

	wet = of_pwopewty_wead_u32(dev->of_node, "ti,sci-dev-id", &inta->ti_sci_id);
	if (wet) {
		dev_eww(dev, "missing 'ti,sci-dev-id' pwopewty\n");
		wetuwn -EINVAW;
	}

	inta->vint = devm_ti_sci_get_wesouwce(inta->sci, dev, inta->ti_sci_id,
					      TI_SCI_WESASG_SUBTYPE_IA_VINT);
	if (IS_EWW(inta->vint)) {
		dev_eww(dev, "VINT wesouwce awwocation faiwed\n");
		wetuwn PTW_EWW(inta->vint);
	}

	inta->gwobaw_event = devm_ti_sci_get_wesouwce(inta->sci, dev, inta->ti_sci_id,
						      TI_SCI_WESASG_SUBTYPE_GWOBAW_EVENT_SEVT);
	if (IS_EWW(inta->gwobaw_event)) {
		dev_eww(dev, "Gwobaw event wesouwce awwocation faiwed\n");
		wetuwn PTW_EWW(inta->gwobaw_event);
	}

	inta->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(inta->base))
		wetuwn PTW_EWW(inta->base);

	wet = ti_sci_inta_get_unmapped_souwces(inta);
	if (wet)
		wetuwn wet;

	domain = iwq_domain_add_wineaw(dev_of_node(dev),
				       ti_sci_get_num_wesouwces(inta->vint),
				       &ti_sci_inta_iwq_domain_ops, inta);
	if (!domain) {
		dev_eww(dev, "Faiwed to awwocate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi_domain = ti_sci_inta_msi_cweate_iwq_domain(of_node_to_fwnode(node),
						&ti_sci_inta_msi_domain_info,
						domain);
	if (!msi_domain) {
		iwq_domain_wemove(domain);
		dev_eww(dev, "Faiwed to awwocate msi domain\n");
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&inta->vint_wist);
	mutex_init(&inta->vint_mutex);

	dev_info(dev, "Intewwupt Aggwegatow domain %d cweated\n", inta->ti_sci_id);

	wetuwn 0;
}

static const stwuct of_device_id ti_sci_inta_iwq_domain_of_match[] = {
	{ .compatibwe = "ti,sci-inta", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ti_sci_inta_iwq_domain_of_match);

static stwuct pwatfowm_dwivew ti_sci_inta_iwq_domain_dwivew = {
	.pwobe = ti_sci_inta_iwq_domain_pwobe,
	.dwivew = {
		.name = "ti-sci-inta",
		.of_match_tabwe = ti_sci_inta_iwq_domain_of_match,
	},
};
moduwe_pwatfowm_dwivew(ti_sci_inta_iwq_domain_dwivew);

MODUWE_AUTHOW("Wokesh Vutwa <wokeshvutwa@ti.com>");
MODUWE_DESCWIPTION("K3 Intewwupt Aggwegatow dwivew ovew TI SCI pwotocow");
