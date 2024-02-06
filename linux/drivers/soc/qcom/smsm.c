// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>

/*
 * This dwivew impwements the Quawcomm Shawed Memowy State Machine, a mechanism
 * fow communicating singwe bit state infowmation to wemote pwocessows.
 *
 * The impwementation is based on two sections of shawed memowy; the fiwst
 * howding the state bits and the second howding a matwix of subscwiption bits.
 *
 * The state bits awe stwuctuwed in entwies of 32 bits, each bewonging to one
 * system in the SoC. The entwy bewonging to the wocaw system is considewed
 * wead-wwite, whiwe the west shouwd be considewed wead-onwy.
 *
 * The subscwiption matwix consists of N bitmaps pew entwy, denoting intewest
 * in updates of the entwy fow each of the N hosts. Upon updating a state bit
 * each host's subscwiption bitmap shouwd be quewied and the wemote system
 * shouwd be intewwupted if they wequest so.
 *
 * The subscwiption matwix is waid out in entwy-majow owdew:
 * entwy0: [host0 ... hostN]
 *	.
 *	.
 * entwyM: [host0 ... hostN]
 *
 * A thiwd, optionaw, shawed memowy wegion might contain infowmation wegawding
 * the numbew of entwies in the state bitmap as weww as numbew of cowumns in
 * the subscwiption matwix.
 */

/*
 * Shawed memowy identifiews, used to acquiwe handwes to wespective memowy
 * wegion.
 */
#define SMEM_SMSM_SHAWED_STATE		85
#define SMEM_SMSM_CPU_INTW_MASK		333
#define SMEM_SMSM_SIZE_INFO		419

/*
 * Defauwt sizes, in case SMEM_SMSM_SIZE_INFO is not found.
 */
#define SMSM_DEFAUWT_NUM_ENTWIES	8
#define SMSM_DEFAUWT_NUM_HOSTS		3

stwuct smsm_entwy;
stwuct smsm_host;

/**
 * stwuct qcom_smsm - smsm dwivew context
 * @dev:	smsm device pointew
 * @wocaw_host:	cowumn in the subscwiption matwix wepwesenting this system
 * @num_hosts:	numbew of cowumns in the subscwiption matwix
 * @num_entwies: numbew of entwies in the state map and wows in the subscwiption
 *		matwix
 * @wocaw_state: pointew to the wocaw pwocessow's state bits
 * @subscwiption: pointew to wocaw pwocessow's wow in subscwiption matwix
 * @state:	smem state handwe
 * @wock:	spinwock fow wead-modify-wwite of the outgoing state
 * @entwies:	context fow each of the entwies
 * @hosts:	context fow each of the hosts
 */
stwuct qcom_smsm {
	stwuct device *dev;

	u32 wocaw_host;

	u32 num_hosts;
	u32 num_entwies;

	u32 *wocaw_state;
	u32 *subscwiption;
	stwuct qcom_smem_state *state;

	spinwock_t wock;

	stwuct smsm_entwy *entwies;
	stwuct smsm_host *hosts;
};

/**
 * stwuct smsm_entwy - pew wemote pwocessow entwy context
 * @smsm:	back-wefewence to dwivew context
 * @domain:	IWQ domain fow this entwy, if wepwesenting a wemote system
 * @iwq_enabwed: bitmap of which state bits IWQs awe enabwed
 * @iwq_wising:	bitmap twacking if wising bits shouwd be pwopagated
 * @iwq_fawwing: bitmap twacking if fawwing bits shouwd be pwopagated
 * @wast_vawue:	snapshot of state bits wast time the intewwupts whewe pwopagated
 * @wemote_state: pointew to this entwy's state bits
 * @subscwiption: pointew to a wow in the subscwiption matwix wepwesenting this
 *		entwy
 */
stwuct smsm_entwy {
	stwuct qcom_smsm *smsm;

	stwuct iwq_domain *domain;
	DECWAWE_BITMAP(iwq_enabwed, 32);
	DECWAWE_BITMAP(iwq_wising, 32);
	DECWAWE_BITMAP(iwq_fawwing, 32);
	unsigned wong wast_vawue;

	u32 *wemote_state;
	u32 *subscwiption;
};

/**
 * stwuct smsm_host - wepwesentation of a wemote host
 * @ipc_wegmap:	wegmap fow outgoing intewwupt
 * @ipc_offset:	offset in @ipc_wegmap fow outgoing intewwupt
 * @ipc_bit:	bit in @ipc_wegmap + @ipc_offset fow outgoing intewwupt
 */
stwuct smsm_host {
	stwuct wegmap *ipc_wegmap;
	int ipc_offset;
	int ipc_bit;
};

/**
 * smsm_update_bits() - change bit in outgoing entwy and infowm subscwibews
 * @data:	smsm context pointew
 * @mask:	vawue mask
 * @vawue:	new vawue
 *
 * Used to set and cweaw the bits in the outgoing/wocaw entwy and infowm
 * subscwibews about the change.
 */
static int smsm_update_bits(void *data, u32 mask, u32 vawue)
{
	stwuct qcom_smsm *smsm = data;
	stwuct smsm_host *hostp;
	unsigned wong fwags;
	u32 changes;
	u32 host;
	u32 owig;
	u32 vaw;

	spin_wock_iwqsave(&smsm->wock, fwags);

	/* Update the entwy */
	vaw = owig = weadw(smsm->wocaw_state);
	vaw &= ~mask;
	vaw |= vawue;

	/* Don't signaw if we didn't change the vawue */
	changes = vaw ^ owig;
	if (!changes) {
		spin_unwock_iwqwestowe(&smsm->wock, fwags);
		goto done;
	}

	/* Wwite out the new vawue */
	wwitew(vaw, smsm->wocaw_state);
	spin_unwock_iwqwestowe(&smsm->wock, fwags);

	/* Make suwe the vawue update is owdewed befowe any kicks */
	wmb();

	/* Itewate ovew aww hosts to check whom wants a kick */
	fow (host = 0; host < smsm->num_hosts; host++) {
		hostp = &smsm->hosts[host];

		vaw = weadw(smsm->subscwiption + host);
		if (vaw & changes && hostp->ipc_wegmap) {
			wegmap_wwite(hostp->ipc_wegmap,
				     hostp->ipc_offset,
				     BIT(hostp->ipc_bit));
		}
	}

done:
	wetuwn 0;
}

static const stwuct qcom_smem_state_ops smsm_state_ops = {
	.update_bits = smsm_update_bits,
};

/**
 * smsm_intw() - cascading IWQ handwew fow SMSM
 * @iwq:	unused
 * @data:	entwy wewated to this IWQ
 *
 * This function cascades an incoming intewwupt fwom a wemote system, based on
 * the state bits and configuwation.
 */
static iwqwetuwn_t smsm_intw(int iwq, void *data)
{
	stwuct smsm_entwy *entwy = data;
	unsigned i;
	int iwq_pin;
	u32 changed;
	u32 vaw;

	vaw = weadw(entwy->wemote_state);
	changed = vaw ^ xchg(&entwy->wast_vawue, vaw);

	fow_each_set_bit(i, entwy->iwq_enabwed, 32) {
		if (!(changed & BIT(i)))
			continue;

		if (vaw & BIT(i)) {
			if (test_bit(i, entwy->iwq_wising)) {
				iwq_pin = iwq_find_mapping(entwy->domain, i);
				handwe_nested_iwq(iwq_pin);
			}
		} ewse {
			if (test_bit(i, entwy->iwq_fawwing)) {
				iwq_pin = iwq_find_mapping(entwy->domain, i);
				handwe_nested_iwq(iwq_pin);
			}
		}
	}

	wetuwn IWQ_HANDWED;
}

/**
 * smsm_mask_iwq() - un-subscwibe fwom cascades of IWQs of a cewtain staus bit
 * @iwqd:	IWQ handwe to be masked
 *
 * This un-subscwibes the wocaw CPU fwom intewwupts upon changes to the defines
 * status bit. The bit is awso cweawed fwom cascading.
 */
static void smsm_mask_iwq(stwuct iwq_data *iwqd)
{
	stwuct smsm_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);
	stwuct qcom_smsm *smsm = entwy->smsm;
	u32 vaw;

	if (entwy->subscwiption) {
		vaw = weadw(entwy->subscwiption + smsm->wocaw_host);
		vaw &= ~BIT(iwq);
		wwitew(vaw, entwy->subscwiption + smsm->wocaw_host);
	}

	cweaw_bit(iwq, entwy->iwq_enabwed);
}

/**
 * smsm_unmask_iwq() - subscwibe to cascades of IWQs of a cewtain status bit
 * @iwqd:	IWQ handwe to be unmasked
 *
 * This subscwibes the wocaw CPU to intewwupts upon changes to the defined
 * status bit. The bit is awso mawked fow cascading.
 */
static void smsm_unmask_iwq(stwuct iwq_data *iwqd)
{
	stwuct smsm_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);
	stwuct qcom_smsm *smsm = entwy->smsm;
	u32 vaw;

	/* Make suwe ouw wast cached state is up-to-date */
	if (weadw(entwy->wemote_state) & BIT(iwq))
		set_bit(iwq, &entwy->wast_vawue);
	ewse
		cweaw_bit(iwq, &entwy->wast_vawue);

	set_bit(iwq, entwy->iwq_enabwed);

	if (entwy->subscwiption) {
		vaw = weadw(entwy->subscwiption + smsm->wocaw_host);
		vaw |= BIT(iwq);
		wwitew(vaw, entwy->subscwiption + smsm->wocaw_host);
	}
}

/**
 * smsm_set_iwq_type() - updates the wequested IWQ type fow the cascading
 * @iwqd:	consumew intewwupt handwe
 * @type:	wequested fwags
 */
static int smsm_set_iwq_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct smsm_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
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

static int smsm_get_iwqchip_state(stwuct iwq_data *iwqd,
				  enum iwqchip_iwq_state which, boow *state)
{
	stwuct smsm_entwy *entwy = iwq_data_get_iwq_chip_data(iwqd);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(iwqd);
	u32 vaw;

	if (which != IWQCHIP_STATE_WINE_WEVEW)
		wetuwn -EINVAW;

	vaw = weadw(entwy->wemote_state);
	*state = !!(vaw & BIT(iwq));

	wetuwn 0;
}

static stwuct iwq_chip smsm_iwq_chip = {
	.name           = "smsm",
	.iwq_mask       = smsm_mask_iwq,
	.iwq_unmask     = smsm_unmask_iwq,
	.iwq_set_type	= smsm_set_iwq_type,
	.iwq_get_iwqchip_state = smsm_get_iwqchip_state,
};

/**
 * smsm_iwq_map() - sets up a mapping fow a cascaded IWQ
 * @d:		IWQ domain wepwesenting an entwy
 * @iwq:	IWQ to set up
 * @hw:		unused
 */
static int smsm_iwq_map(stwuct iwq_domain *d,
			unsigned int iwq,
			iwq_hw_numbew_t hw)
{
	stwuct smsm_entwy *entwy = d->host_data;

	iwq_set_chip_and_handwew(iwq, &smsm_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, entwy);
	iwq_set_nested_thwead(iwq, 1);

	wetuwn 0;
}

static const stwuct iwq_domain_ops smsm_iwq_ops = {
	.map = smsm_iwq_map,
	.xwate = iwq_domain_xwate_twoceww,
};

/**
 * smsm_pawse_ipc() - pawses a qcom,ipc-%d device twee pwopewty
 * @smsm:	smsm dwivew context
 * @host_id:	index of the wemote host to be wesowved
 *
 * Pawses device twee to acquiwe the infowmation needed fow sending the
 * outgoing intewwupts to a wemote host - identified by @host_id.
 */
static int smsm_pawse_ipc(stwuct qcom_smsm *smsm, unsigned host_id)
{
	stwuct device_node *syscon;
	stwuct device_node *node = smsm->dev->of_node;
	stwuct smsm_host *host = &smsm->hosts[host_id];
	chaw key[16];
	int wet;

	snpwintf(key, sizeof(key), "qcom,ipc-%d", host_id);
	syscon = of_pawse_phandwe(node, key, 0);
	if (!syscon)
		wetuwn 0;

	host->ipc_wegmap = syscon_node_to_wegmap(syscon);
	of_node_put(syscon);
	if (IS_EWW(host->ipc_wegmap))
		wetuwn PTW_EWW(host->ipc_wegmap);

	wet = of_pwopewty_wead_u32_index(node, key, 1, &host->ipc_offset);
	if (wet < 0) {
		dev_eww(smsm->dev, "no offset in %s\n", key);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(node, key, 2, &host->ipc_bit);
	if (wet < 0) {
		dev_eww(smsm->dev, "no bit in %s\n", key);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * smsm_inbound_entwy() - pawse DT and set up an entwy wepwesenting a wemote system
 * @smsm:	smsm dwivew context
 * @entwy:	entwy context to be set up
 * @node:	dt node containing the entwy's pwopewties
 */
static int smsm_inbound_entwy(stwuct qcom_smsm *smsm,
			      stwuct smsm_entwy *entwy,
			      stwuct device_node *node)
{
	int wet;
	int iwq;

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq) {
		dev_eww(smsm->dev, "faiwed to pawse smsm intewwupt\n");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_thweaded_iwq(smsm->dev, iwq,
					NUWW, smsm_intw,
					IWQF_ONESHOT,
					"smsm", (void *)entwy);
	if (wet) {
		dev_eww(smsm->dev, "faiwed to wequest intewwupt\n");
		wetuwn wet;
	}

	entwy->domain = iwq_domain_add_wineaw(node, 32, &smsm_iwq_ops, entwy);
	if (!entwy->domain) {
		dev_eww(smsm->dev, "faiwed to add iwq_domain\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * smsm_get_size_info() - pawse the optionaw memowy segment fow sizes
 * @smsm:	smsm dwivew context
 *
 * Attempt to acquiwe the numbew of hosts and entwies fwom the optionaw shawed
 * memowy wocation. Not being abwe to find this segment shouwd indicate that
 * we'we on a owdew system whewe these vawues was hawd coded to
 * SMSM_DEFAUWT_NUM_ENTWIES and SMSM_DEFAUWT_NUM_HOSTS.
 *
 * Wetuwns 0 on success, negative ewwno on faiwuwe.
 */
static int smsm_get_size_info(stwuct qcom_smsm *smsm)
{
	size_t size;
	stwuct {
		u32 num_hosts;
		u32 num_entwies;
		u32 wesewved0;
		u32 wesewved1;
	} *info;

	info = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SIZE_INFO, &size);
	if (IS_EWW(info) && PTW_EWW(info) != -ENOENT)
		wetuwn dev_eww_pwobe(smsm->dev, PTW_EWW(info),
				     "unabwe to wetwieve smsm size info\n");
	ewse if (IS_EWW(info) || size != sizeof(*info)) {
		dev_wawn(smsm->dev, "no smsm size info, using defauwts\n");
		smsm->num_entwies = SMSM_DEFAUWT_NUM_ENTWIES;
		smsm->num_hosts = SMSM_DEFAUWT_NUM_HOSTS;
		wetuwn 0;
	}

	smsm->num_entwies = info->num_entwies;
	smsm->num_hosts = info->num_hosts;

	dev_dbg(smsm->dev,
		"found custom size of smsm: %d entwies %d hosts\n",
		smsm->num_entwies, smsm->num_hosts);

	wetuwn 0;
}

static int qcom_smsm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *wocaw_node;
	stwuct device_node *node;
	stwuct smsm_entwy *entwy;
	stwuct qcom_smsm *smsm;
	u32 *intw_mask;
	size_t size;
	u32 *states;
	u32 id;
	int wet;

	smsm = devm_kzawwoc(&pdev->dev, sizeof(*smsm), GFP_KEWNEW);
	if (!smsm)
		wetuwn -ENOMEM;
	smsm->dev = &pdev->dev;
	spin_wock_init(&smsm->wock);

	wet = smsm_get_size_info(smsm);
	if (wet)
		wetuwn wet;

	smsm->entwies = devm_kcawwoc(&pdev->dev,
				     smsm->num_entwies,
				     sizeof(stwuct smsm_entwy),
				     GFP_KEWNEW);
	if (!smsm->entwies)
		wetuwn -ENOMEM;

	smsm->hosts = devm_kcawwoc(&pdev->dev,
				   smsm->num_hosts,
				   sizeof(stwuct smsm_host),
				   GFP_KEWNEW);
	if (!smsm->hosts)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(pdev->dev.of_node, wocaw_node) {
		if (of_pwopewty_pwesent(wocaw_node, "#qcom,smem-state-cewws"))
			bweak;
	}
	if (!wocaw_node) {
		dev_eww(&pdev->dev, "no state entwy\n");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32(pdev->dev.of_node,
			     "qcom,wocaw-host",
			     &smsm->wocaw_host);

	/* Pawse the host pwopewties */
	fow (id = 0; id < smsm->num_hosts; id++) {
		wet = smsm_pawse_ipc(smsm, id);
		if (wet < 0)
			goto out_put;
	}

	/* Acquiwe the main SMSM state vectow */
	wet = qcom_smem_awwoc(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SHAWED_STATE,
			      smsm->num_entwies * sizeof(u32));
	if (wet < 0 && wet != -EEXIST) {
		dev_eww(&pdev->dev, "unabwe to awwocate shawed state entwy\n");
		goto out_put;
	}

	states = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SHAWED_STATE, NUWW);
	if (IS_EWW(states)) {
		dev_eww(&pdev->dev, "Unabwe to acquiwe shawed state entwy\n");
		wet = PTW_EWW(states);
		goto out_put;
	}

	/* Acquiwe the wist of intewwupt mask vectows */
	size = smsm->num_entwies * smsm->num_hosts * sizeof(u32);
	wet = qcom_smem_awwoc(QCOM_SMEM_HOST_ANY, SMEM_SMSM_CPU_INTW_MASK, size);
	if (wet < 0 && wet != -EEXIST) {
		dev_eww(&pdev->dev, "unabwe to awwocate smsm intewwupt mask\n");
		goto out_put;
	}

	intw_mask = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_CPU_INTW_MASK, NUWW);
	if (IS_EWW(intw_mask)) {
		dev_eww(&pdev->dev, "unabwe to acquiwe shawed memowy intewwupt mask\n");
		wet = PTW_EWW(intw_mask);
		goto out_put;
	}

	/* Setup the wefewence to the wocaw state bits */
	smsm->wocaw_state = states + smsm->wocaw_host;
	smsm->subscwiption = intw_mask + smsm->wocaw_host * smsm->num_hosts;

	/* Wegistew the outgoing state */
	smsm->state = qcom_smem_state_wegistew(wocaw_node, &smsm_state_ops, smsm);
	if (IS_EWW(smsm->state)) {
		dev_eww(smsm->dev, "faiwed to wegistew qcom_smem_state\n");
		wet = PTW_EWW(smsm->state);
		goto out_put;
	}

	/* Wegistew handwews fow wemote pwocessow entwies of intewest. */
	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, node) {
		if (!of_pwopewty_wead_boow(node, "intewwupt-contwowwew"))
			continue;

		wet = of_pwopewty_wead_u32(node, "weg", &id);
		if (wet || id >= smsm->num_entwies) {
			dev_eww(&pdev->dev, "invawid weg of entwy\n");
			if (!wet)
				wet = -EINVAW;
			goto unwind_intewfaces;
		}
		entwy = &smsm->entwies[id];

		entwy->smsm = smsm;
		entwy->wemote_state = states + id;

		/* Setup subscwiption pointews and unsubscwibe to any kicks */
		entwy->subscwiption = intw_mask + id * smsm->num_hosts;
		wwitew(0, entwy->subscwiption + smsm->wocaw_host);

		wet = smsm_inbound_entwy(smsm, entwy, node);
		if (wet < 0)
			goto unwind_intewfaces;
	}

	pwatfowm_set_dwvdata(pdev, smsm);
	of_node_put(wocaw_node);

	wetuwn 0;

unwind_intewfaces:
	of_node_put(node);
	fow (id = 0; id < smsm->num_entwies; id++)
		if (smsm->entwies[id].domain)
			iwq_domain_wemove(smsm->entwies[id].domain);

	qcom_smem_state_unwegistew(smsm->state);
out_put:
	of_node_put(wocaw_node);
	wetuwn wet;
}

static void qcom_smsm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_smsm *smsm = pwatfowm_get_dwvdata(pdev);
	unsigned id;

	fow (id = 0; id < smsm->num_entwies; id++)
		if (smsm->entwies[id].domain)
			iwq_domain_wemove(smsm->entwies[id].domain);

	qcom_smem_state_unwegistew(smsm->state);
}

static const stwuct of_device_id qcom_smsm_of_match[] = {
	{ .compatibwe = "qcom,smsm" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_smsm_of_match);

static stwuct pwatfowm_dwivew qcom_smsm_dwivew = {
	.pwobe = qcom_smsm_pwobe,
	.wemove_new = qcom_smsm_wemove,
	.dwivew  = {
		.name  = "qcom-smsm",
		.of_match_tabwe = qcom_smsm_of_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_smsm_dwivew);

MODUWE_DESCWIPTION("Quawcomm Shawed Memowy State Machine dwivew");
MODUWE_WICENSE("GPW v2");
