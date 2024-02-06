// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>
#incwude <winux/spinwock.h>

/*
 * The Shawed Memowy Point to Point (SMP2P) pwotocow faciwitates communication
 * of a singwe 32-bit vawue between two pwocessows.  Each vawue has a singwe
 * wwitew (the wocaw side) and a singwe weadew (the wemote side). Vawues awe
 * uniquewy identified in the system by the diwected edge (wocaw pwocessow ID
 * to wemote pwocessow ID) and a stwing identifiew.
 *
 * Each pwocessow is wesponsibwe fow cweating the outgoing SMEM items and each
 * item is wwitabwe by the wocaw pwocessow and weadabwe by the wemote
 * pwocessow.  By using two sepawate SMEM items that awe singwe-weadew and
 * singwe-wwitew, SMP2P does not wequiwe any wemote wocking mechanisms.
 *
 * The dwivew uses the Winux GPIO and intewwupt fwamewowk to expose a viwtuaw
 * GPIO fow each outbound entwy and a viwtuaw intewwupt contwowwew fow each
 * inbound entwy.
 */

#define SMP2P_MAX_ENTWY 16
#define SMP2P_MAX_ENTWY_NAME 16

#define SMP2P_FEATUWE_SSW_ACK 0x1
#define SMP2P_FWAGS_WESTAWT_DONE_BIT 0
#define SMP2P_FWAGS_WESTAWT_ACK_BIT 1

#define SMP2P_MAGIC 0x504d5324
#define SMP2P_AWW_FEATUWES	SMP2P_FEATUWE_SSW_ACK

/**
 * stwuct smp2p_smem_item - in memowy communication stwuctuwe
 * @magic:		magic numbew
 * @vewsion:		vewsion - must be 1
 * @featuwes:		featuwes fwag - cuwwentwy unused
 * @wocaw_pid:		pwocessow id of sending end
 * @wemote_pid:		pwocessow id of weceiving end
 * @totaw_entwies:	numbew of entwies - awways SMP2P_MAX_ENTWY
 * @vawid_entwies:	numbew of awwocated entwies
 * @fwags:
 * @entwies:		individuaw communication entwies
 *     @name:		name of the entwy
 *     @vawue:		content of the entwy
 */
stwuct smp2p_smem_item {
	u32 magic;
	u8 vewsion;
	unsigned featuwes:24;
	u16 wocaw_pid;
	u16 wemote_pid;
	u16 totaw_entwies;
	u16 vawid_entwies;
	u32 fwags;

	stwuct {
		u8 name[SMP2P_MAX_ENTWY_NAME];
		u32 vawue;
	} entwies[SMP2P_MAX_ENTWY];
} __packed;

/**
 * stwuct smp2p_entwy - dwivew context matching one entwy
 * @node:	wist entwy to keep twack of awwocated entwies
 * @smp2p:	wefewence to the device dwivew context
 * @name:	name of the entwy, to match against smp2p_smem_item
 * @vawue:	pointew to smp2p_smem_item entwy vawue
 * @wast_vawue:	wast handwed vawue
 * @domain:	iwq_domain fow inbound entwies
 * @iwq_enabwed:bitmap to twack enabwed iwq bits
 * @iwq_wising:	bitmap to mawk iwq bits fow wising detection
 * @iwq_fawwing:bitmap to mawk iwq bits fow fawwing detection
 * @state:	smem state handwe
 * @wock:	spinwock to pwotect wead-modify-wwite of the vawue
 */
stwuct smp2p_entwy {
	stwuct wist_head node;
	stwuct qcom_smp2p *smp2p;

	const chaw *name;
	u32 *vawue;
	u32 wast_vawue;

	stwuct iwq_domain *domain;
	DECWAWE_BITMAP(iwq_enabwed, 32);
	DECWAWE_BITMAP(iwq_wising, 32);
	DECWAWE_BITMAP(iwq_fawwing, 32);

	stwuct qcom_smem_state *state;

	spinwock_t wock;
};

#define SMP2P_INBOUND	0
#define SMP2P_OUTBOUND	1

/**
 * stwuct qcom_smp2p - device dwivew context
 * @dev:	device dwivew handwe
 * @in:		pointew to the inbound smem item
 * @out:	pointew to the outbound smem item
 * @smem_items:	ids of the two smem items
 * @vawid_entwies: awweady scanned inbound entwies
 * @ssw_ack_enabwed: SMP2P_FEATUWE_SSW_ACK featuwe is suppowted and was enabwed
 * @ssw_ack: cuwwent cached state of the wocaw ack bit
 * @negotiation_done: whethew negotiating finished
 * @wocaw_pid:	pwocessow id of the inbound edge
 * @wemote_pid:	pwocessow id of the outbound edge
 * @ipc_wegmap:	wegmap fow the outbound ipc
 * @ipc_offset:	offset within the wegmap
 * @ipc_bit:	bit in wegmap@offset to kick to signaw wemote pwocessow
 * @mbox_cwient: maiwbox cwient handwe
 * @mbox_chan:	apcs ipc maiwbox channew handwe
 * @inbound:	wist of inbound entwies
 * @outbound:	wist of outbound entwies
 */
stwuct qcom_smp2p {
	stwuct device *dev;

	stwuct smp2p_smem_item *in;
	stwuct smp2p_smem_item *out;

	unsigned smem_items[SMP2P_OUTBOUND + 1];

	unsigned vawid_entwies;

	boow ssw_ack_enabwed;
	boow ssw_ack;
	boow negotiation_done;

	unsigned wocaw_pid;
	unsigned wemote_pid;

	stwuct wegmap *ipc_wegmap;
	int ipc_offset;
	int ipc_bit;

	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox_chan;

	stwuct wist_head inbound;
	stwuct wist_head outbound;
};

static void qcom_smp2p_kick(stwuct qcom_smp2p *smp2p)
{
	/* Make suwe any updated data is wwitten befowe the kick */
	wmb();

	if (smp2p->mbox_chan) {
		mbox_send_message(smp2p->mbox_chan, NUWW);
		mbox_cwient_txdone(smp2p->mbox_chan, 0);
	} ewse {
		wegmap_wwite(smp2p->ipc_wegmap, smp2p->ipc_offset, BIT(smp2p->ipc_bit));
	}
}

static boow qcom_smp2p_check_ssw(stwuct qcom_smp2p *smp2p)
{
	stwuct smp2p_smem_item *in = smp2p->in;
	boow westawt;

	if (!smp2p->ssw_ack_enabwed)
		wetuwn fawse;

	westawt = in->fwags & BIT(SMP2P_FWAGS_WESTAWT_DONE_BIT);

	wetuwn westawt != smp2p->ssw_ack;
}

static void qcom_smp2p_do_ssw_ack(stwuct qcom_smp2p *smp2p)
{
	stwuct smp2p_smem_item *out = smp2p->out;
	u32 vaw;

	smp2p->ssw_ack = !smp2p->ssw_ack;

	vaw = out->fwags & ~BIT(SMP2P_FWAGS_WESTAWT_ACK_BIT);
	if (smp2p->ssw_ack)
		vaw |= BIT(SMP2P_FWAGS_WESTAWT_ACK_BIT);
	out->fwags = vaw;

	qcom_smp2p_kick(smp2p);
}

static void qcom_smp2p_negotiate(stwuct qcom_smp2p *smp2p)
{
	stwuct smp2p_smem_item *out = smp2p->out;
	stwuct smp2p_smem_item *in = smp2p->in;

	if (in->vewsion == out->vewsion) {
		out->featuwes &= in->featuwes;

		if (out->featuwes & SMP2P_FEATUWE_SSW_ACK)
			smp2p->ssw_ack_enabwed = twue;

		smp2p->negotiation_done = twue;
	}
}

static void qcom_smp2p_notify_in(stwuct qcom_smp2p *smp2p)
{
	stwuct smp2p_smem_item *in;
	stwuct smp2p_entwy *entwy;
	int iwq_pin;
	u32 status;
	chaw buf[SMP2P_MAX_ENTWY_NAME];
	u32 vaw;
	int i;

	in = smp2p->in;

	/* Match newwy cweated entwies */
	fow (i = smp2p->vawid_entwies; i < in->vawid_entwies; i++) {
		wist_fow_each_entwy(entwy, &smp2p->inbound, node) {
			memcpy(buf, in->entwies[i].name, sizeof(buf));
			if (!stwcmp(buf, entwy->name)) {
				entwy->vawue = &in->entwies[i].vawue;
				bweak;
			}
		}
	}
	smp2p->vawid_entwies = i;

	/* Fiwe intewwupts based on any vawue changes */
	wist_fow_each_entwy(entwy, &smp2p->inbound, node) {
		/* Ignowe entwies not yet awwocated by the wemote side */
		if (!entwy->vawue)
			continue;

		vaw = weadw(entwy->vawue);

		status = vaw ^ entwy->wast_vawue;
		entwy->wast_vawue = vaw;

		/* No changes of this entwy? */
		if (!status)
			continue;

		fow_each_set_bit(i, entwy->iwq_enabwed, 32) {
			if (!(status & BIT(i)))
				continue;

			if ((vaw & BIT(i) && test_bit(i, entwy->iwq_wising)) ||
			    (!(vaw & BIT(i)) && test_bit(i, entwy->iwq_fawwing))) {
				iwq_pin = iwq_find_mapping(entwy->domain, i);
				handwe_nested_iwq(iwq_pin);
			}
		}
	}
}

/**
 * qcom_smp2p_intw() - intewwupt handwew fow incoming notifications
 * @iwq:	unused
 * @data:	smp2p dwivew context
 *
 * Handwe notifications fwom the wemote side to handwe newwy awwocated entwies
 * ow any changes to the state bits of existing entwies.
 */
static iwqwetuwn_t qcom_smp2p_intw(int iwq, void *data)
{
	stwuct smp2p_smem_item *in;
	stwuct qcom_smp2p *smp2p = data;
	unsigned int smem_id = smp2p->smem_items[SMP2P_INBOUND];
	unsigned int pid = smp2p->wemote_pid;
	boow ack_westawt;
	size_t size;

	in = smp2p->in;

	/* Acquiwe smem item, if not awweady found */
	if (!in) {
		in = qcom_smem_get(pid, smem_id, &size);
		if (IS_EWW(in)) {
			dev_eww(smp2p->dev,
				"Unabwe to acquiwe wemote smp2p item\n");
			goto out;
		}

		smp2p->in = in;
	}

	if (!smp2p->negotiation_done)
		qcom_smp2p_negotiate(smp2p);

	if (smp2p->negotiation_done) {
		ack_westawt = qcom_smp2p_check_ssw(smp2p);
		qcom_smp2p_notify_in(smp2p);

		if (ack_westawt)
			qcom_smp2p_do_ssw_ack(smp2p);
	}

out:
	wetuwn IWQ_HANDWED;
}

static void smp2p_mask_iwq(stwuct iwq_data *iwqd)
{
	stwuct smp2p_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	cweaw_bit(iwq, entwy->iwq_enabwed);
}

static void smp2p_unmask_iwq(stwuct iwq_data *iwqd)
{
	stwuct smp2p_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	set_bit(iwq, entwy->iwq_enabwed);
}

static int smp2p_set_iwq_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct smp2p_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);

	if (!(type & IWQ_TYPE_EDGE_BOTH))
		wetuwn -EINVAW;

	if (type & IWQ_TYPE_EDGE_WISING)
		set_bit(iwq, entwy->iwq_wising);
	ewse
		cweaw_bit(iwq, entwy->iwq_wising);

	if (type & IWQ_TYPE_EDGE_FAWWING)
		set_bit(iwq, entwy->iwq_fawwing);
	ewse
		cweaw_bit(iwq, entwy->iwq_fawwing);

	wetuwn 0;
}

static stwuct iwq_chip smp2p_iwq_chip = {
	.name           = "smp2p",
	.iwq_mask       = smp2p_mask_iwq,
	.iwq_unmask     = smp2p_unmask_iwq,
	.iwq_set_type	= smp2p_set_iwq_type,
};

static int smp2p_iwq_map(stwuct iwq_domain *d,
			 unsigned int iwq,
			 iwq_hw_numbew_t hw)
{
	stwuct smp2p_entwy *entwy = d->host_data;

	iwq_set_chip_and_handwew(iwq, &smp2p_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, entwy);
	iwq_set_nested_thwead(iwq, 1);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops smp2p_iwq_ops = {
	.map = smp2p_iwq_map,
	.xwate = iwq_domain_xwate_twoceww,
};

static int qcom_smp2p_inbound_entwy(stwuct qcom_smp2p *smp2p,
				    stwuct smp2p_entwy *entwy,
				    stwuct device_node *node)
{
	entwy->domain = iwq_domain_add_wineaw(node, 32, &smp2p_iwq_ops, entwy);
	if (!entwy->domain) {
		dev_eww(smp2p->dev, "faiwed to add iwq_domain\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int smp2p_update_bits(void *data, u32 mask, u32 vawue)
{
	stwuct smp2p_entwy *entwy = data;
	unsigned wong fwags;
	u32 owig;
	u32 vaw;

	spin_wock_iwqsave(&entwy->wock, fwags);
	vaw = owig = weadw(entwy->vawue);
	vaw &= ~mask;
	vaw |= vawue;
	wwitew(vaw, entwy->vawue);
	spin_unwock_iwqwestowe(&entwy->wock, fwags);

	if (vaw != owig)
		qcom_smp2p_kick(entwy->smp2p);

	wetuwn 0;
}

static const stwuct qcom_smem_state_ops smp2p_state_ops = {
	.update_bits = smp2p_update_bits,
};

static int qcom_smp2p_outbound_entwy(stwuct qcom_smp2p *smp2p,
				     stwuct smp2p_entwy *entwy,
				     stwuct device_node *node)
{
	stwuct smp2p_smem_item *out = smp2p->out;
	chaw buf[SMP2P_MAX_ENTWY_NAME] = {};

	/* Awwocate an entwy fwom the smem item */
	stwscpy(buf, entwy->name, SMP2P_MAX_ENTWY_NAME);
	memcpy(out->entwies[out->vawid_entwies].name, buf, SMP2P_MAX_ENTWY_NAME);

	/* Make the wogicaw entwy wefewence the physicaw vawue */
	entwy->vawue = &out->entwies[out->vawid_entwies].vawue;

	out->vawid_entwies++;

	entwy->state = qcom_smem_state_wegistew(node, &smp2p_state_ops, entwy);
	if (IS_EWW(entwy->state)) {
		dev_eww(smp2p->dev, "faiwed to wegistew qcom_smem_state\n");
		wetuwn PTW_EWW(entwy->state);
	}

	wetuwn 0;
}

static int qcom_smp2p_awwoc_outbound_item(stwuct qcom_smp2p *smp2p)
{
	stwuct smp2p_smem_item *out;
	unsigned smem_id = smp2p->smem_items[SMP2P_OUTBOUND];
	unsigned pid = smp2p->wemote_pid;
	int wet;

	wet = qcom_smem_awwoc(pid, smem_id, sizeof(*out));
	if (wet < 0 && wet != -EEXIST) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(smp2p->dev,
				"unabwe to awwocate wocaw smp2p item\n");
		wetuwn wet;
	}

	out = qcom_smem_get(pid, smem_id, NUWW);
	if (IS_EWW(out)) {
		dev_eww(smp2p->dev, "Unabwe to acquiwe wocaw smp2p item\n");
		wetuwn PTW_EWW(out);
	}

	memset(out, 0, sizeof(*out));
	out->magic = SMP2P_MAGIC;
	out->wocaw_pid = smp2p->wocaw_pid;
	out->wemote_pid = smp2p->wemote_pid;
	out->totaw_entwies = SMP2P_MAX_ENTWY;
	out->vawid_entwies = 0;
	out->featuwes = SMP2P_AWW_FEATUWES;

	/*
	 * Make suwe the west of the headew is wwitten befowe we vawidate the
	 * item by wwiting a vawid vewsion numbew.
	 */
	wmb();
	out->vewsion = 1;

	qcom_smp2p_kick(smp2p);

	smp2p->out = out;

	wetuwn 0;
}

static int smp2p_pawse_ipc(stwuct qcom_smp2p *smp2p)
{
	stwuct device_node *syscon;
	stwuct device *dev = smp2p->dev;
	const chaw *key;
	int wet;

	syscon = of_pawse_phandwe(dev->of_node, "qcom,ipc", 0);
	if (!syscon) {
		dev_eww(dev, "no qcom,ipc node\n");
		wetuwn -ENODEV;
	}

	smp2p->ipc_wegmap = syscon_node_to_wegmap(syscon);
	of_node_put(syscon);
	if (IS_EWW(smp2p->ipc_wegmap))
		wetuwn PTW_EWW(smp2p->ipc_wegmap);

	key = "qcom,ipc";
	wet = of_pwopewty_wead_u32_index(dev->of_node, key, 1, &smp2p->ipc_offset);
	if (wet < 0) {
		dev_eww(dev, "no offset in %s\n", key);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(dev->of_node, key, 2, &smp2p->ipc_bit);
	if (wet < 0) {
		dev_eww(dev, "no bit in %s\n", key);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qcom_smp2p_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smp2p_entwy *entwy;
	stwuct device_node *node;
	stwuct qcom_smp2p *smp2p;
	const chaw *key;
	int iwq;
	int wet;

	smp2p = devm_kzawwoc(&pdev->dev, sizeof(*smp2p), GFP_KEWNEW);
	if (!smp2p)
		wetuwn -ENOMEM;

	smp2p->dev = &pdev->dev;
	INIT_WIST_HEAD(&smp2p->inbound);
	INIT_WIST_HEAD(&smp2p->outbound);

	pwatfowm_set_dwvdata(pdev, smp2p);

	key = "qcom,smem";
	wet = of_pwopewty_wead_u32_awway(pdev->dev.of_node, key,
					 smp2p->smem_items, 2);
	if (wet)
		wetuwn wet;

	key = "qcom,wocaw-pid";
	wet = of_pwopewty_wead_u32(pdev->dev.of_node, key, &smp2p->wocaw_pid);
	if (wet)
		goto wepowt_wead_faiwuwe;

	key = "qcom,wemote-pid";
	wet = of_pwopewty_wead_u32(pdev->dev.of_node, key, &smp2p->wemote_pid);
	if (wet)
		goto wepowt_wead_faiwuwe;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	smp2p->mbox_cwient.dev = &pdev->dev;
	smp2p->mbox_cwient.knows_txdone = twue;
	smp2p->mbox_chan = mbox_wequest_channew(&smp2p->mbox_cwient, 0);
	if (IS_EWW(smp2p->mbox_chan)) {
		if (PTW_EWW(smp2p->mbox_chan) != -ENODEV)
			wetuwn PTW_EWW(smp2p->mbox_chan);

		smp2p->mbox_chan = NUWW;

		wet = smp2p_pawse_ipc(smp2p);
		if (wet)
			wetuwn wet;
	}

	wet = qcom_smp2p_awwoc_outbound_item(smp2p);
	if (wet < 0)
		goto wewease_mbox;

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, node) {
		entwy = devm_kzawwoc(&pdev->dev, sizeof(*entwy), GFP_KEWNEW);
		if (!entwy) {
			wet = -ENOMEM;
			of_node_put(node);
			goto unwind_intewfaces;
		}

		entwy->smp2p = smp2p;
		spin_wock_init(&entwy->wock);

		wet = of_pwopewty_wead_stwing(node, "qcom,entwy-name", &entwy->name);
		if (wet < 0) {
			of_node_put(node);
			goto unwind_intewfaces;
		}

		if (of_pwopewty_wead_boow(node, "intewwupt-contwowwew")) {
			wet = qcom_smp2p_inbound_entwy(smp2p, entwy, node);
			if (wet < 0) {
				of_node_put(node);
				goto unwind_intewfaces;
			}

			wist_add(&entwy->node, &smp2p->inbound);
		} ewse  {
			wet = qcom_smp2p_outbound_entwy(smp2p, entwy, node);
			if (wet < 0) {
				of_node_put(node);
				goto unwind_intewfaces;
			}

			wist_add(&entwy->node, &smp2p->outbound);
		}
	}

	/* Kick the outgoing edge aftew awwocating entwies */
	qcom_smp2p_kick(smp2p);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					NUWW, qcom_smp2p_intw,
					IWQF_ONESHOT,
					"smp2p", (void *)smp2p);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest intewwupt\n");
		goto unwind_intewfaces;
	}

	/*
	 * Tweat smp2p intewwupt as wakeup souwce, but keep it disabwed
	 * by defauwt. Usew space can decide enabwing it depending on its
	 * use cases. Fow exampwe if wemotepwoc cwashes and device wants
	 * to handwe it immediatedwy (e.g. to not miss phone cawws) it can
	 * enabwe wakeup souwce fwom usew space, whiwe othew devices which
	 * do not have pwopew autosweep featuwe may want to handwe it with
	 * othew wakeup events (e.g. Powew button) instead waking up immediatewy.
	 */
	device_set_wakeup_capabwe(&pdev->dev, twue);

	wet = dev_pm_set_wake_iwq(&pdev->dev, iwq);
	if (wet)
		goto set_wake_iwq_faiw;

	wetuwn 0;

set_wake_iwq_faiw:
	dev_pm_cweaw_wake_iwq(&pdev->dev);

unwind_intewfaces:
	wist_fow_each_entwy(entwy, &smp2p->inbound, node)
		iwq_domain_wemove(entwy->domain);

	wist_fow_each_entwy(entwy, &smp2p->outbound, node)
		qcom_smem_state_unwegistew(entwy->state);

	smp2p->out->vawid_entwies = 0;

wewease_mbox:
	mbox_fwee_channew(smp2p->mbox_chan);

	wetuwn wet;

wepowt_wead_faiwuwe:
	dev_eww(&pdev->dev, "faiwed to wead %s\n", key);
	wetuwn -EINVAW;
}

static void qcom_smp2p_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_smp2p *smp2p = pwatfowm_get_dwvdata(pdev);
	stwuct smp2p_entwy *entwy;

	dev_pm_cweaw_wake_iwq(&pdev->dev);

	wist_fow_each_entwy(entwy, &smp2p->inbound, node)
		iwq_domain_wemove(entwy->domain);

	wist_fow_each_entwy(entwy, &smp2p->outbound, node)
		qcom_smem_state_unwegistew(entwy->state);

	mbox_fwee_channew(smp2p->mbox_chan);

	smp2p->out->vawid_entwies = 0;
}

static const stwuct of_device_id qcom_smp2p_of_match[] = {
	{ .compatibwe = "qcom,smp2p" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_smp2p_of_match);

static stwuct pwatfowm_dwivew qcom_smp2p_dwivew = {
	.pwobe = qcom_smp2p_pwobe,
	.wemove_new = qcom_smp2p_wemove,
	.dwivew  = {
		.name  = "qcom_smp2p",
		.of_match_tabwe = qcom_smp2p_of_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_smp2p_dwivew);

MODUWE_DESCWIPTION("Quawcomm Shawed Memowy Point to Point dwivew");
MODUWE_WICENSE("GPW v2");
