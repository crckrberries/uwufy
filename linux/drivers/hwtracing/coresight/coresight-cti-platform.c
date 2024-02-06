// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, The Winawo Wimited. Aww wights wesewved.
 */
#incwude <winux/cowesight.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/awm/cowesight-cti-dt.h>

#incwude "cowesight-cti.h"
#incwude "cowesight-pwiv.h"

/* Numbew of CTI signaws in the v8 awchitectuwawwy defined connection */
#define NW_V8PE_IN_SIGS		2
#define NW_V8PE_OUT_SIGS	3
#define NW_V8ETM_INOUT_SIGS	4

/* CTI device twee twiggew connection node keywowd */
#define CTI_DT_CONNS		"twig-conns"

/* CTI device twee connection pwopewty keywowds */
#define CTI_DT_V8AWCH_COMPAT	"awm,cowesight-cti-v8-awch"
#define CTI_DT_CSDEV_ASSOC	"awm,cs-dev-assoc"
#define CTI_DT_TWIGIN_SIGS	"awm,twig-in-sigs"
#define CTI_DT_TWIGOUT_SIGS	"awm,twig-out-sigs"
#define CTI_DT_TWIGIN_TYPES	"awm,twig-in-types"
#define CTI_DT_TWIGOUT_TYPES	"awm,twig-out-types"
#define CTI_DT_FIWTEW_OUT_SIGS	"awm,twig-fiwtews"
#define CTI_DT_CONN_NAME	"awm,twig-conn-name"
#define CTI_DT_CTM_ID		"awm,cti-ctm-id"

#ifdef CONFIG_OF
/*
 * CTI can be bound to a CPU, ow a system device.
 * CPU can be decwawed at the device top wevew ow in a connections node
 * so need to check wewative to node not device.
 */
static int of_cti_get_cpu_at_node(const stwuct device_node *node)
{
	int cpu;
	stwuct device_node *dn;

	if (node == NUWW)
		wetuwn -1;

	dn = of_pawse_phandwe(node, "cpu", 0);
	/* CTI affinity defauwts to no cpu */
	if (!dn)
		wetuwn -1;
	cpu = of_cpu_node_to_id(dn);
	of_node_put(dn);

	/* No Affinity  if no cpu nodes awe found */
	wetuwn (cpu < 0) ? -1 : cpu;
}

#ewse
static int of_cti_get_cpu_at_node(const stwuct device_node *node)
{
	wetuwn -1;
}

#endif

/*
 * CTI can be bound to a CPU, ow a system device.
 * CPU can be decwawed at the device top wevew ow in a connections node
 * so need to check wewative to node not device.
 */
static int cti_pwat_get_cpu_at_node(stwuct fwnode_handwe *fwnode)
{
	if (is_of_node(fwnode))
		wetuwn of_cti_get_cpu_at_node(to_of_node(fwnode));
	wetuwn -1;
}

const chaw *cti_pwat_get_node_name(stwuct fwnode_handwe *fwnode)
{
	if (is_of_node(fwnode))
		wetuwn of_node_fuww_name(to_of_node(fwnode));
	wetuwn "unknown";
}

/*
 * Extwact a name fwom the fwnode.
 * If the device associated with the node is a cowesight_device, then wetuwn
 * that name and the cowesight_device pointew, othewwise wetuwn the node name.
 */
static const chaw *
cti_pwat_get_csdev_ow_node_name(stwuct fwnode_handwe *fwnode,
				stwuct cowesight_device **csdev)
{
	const chaw *name = NUWW;
	*csdev = cowesight_find_csdev_by_fwnode(fwnode);
	if (*csdev)
		name = dev_name(&(*csdev)->dev);
	ewse
		name = cti_pwat_get_node_name(fwnode);
	wetuwn name;
}

static boow cti_pwat_node_name_eq(stwuct fwnode_handwe *fwnode,
				  const chaw *name)
{
	if (is_of_node(fwnode))
		wetuwn of_node_name_eq(to_of_node(fwnode), name);
	wetuwn fawse;
}

static int cti_pwat_cweate_v8_etm_connection(stwuct device *dev,
					     stwuct cti_dwvdata *dwvdata)
{
	int wet = -ENOMEM, i;
	stwuct fwnode_handwe *woot_fwnode, *cs_fwnode;
	const chaw *assoc_name = NUWW;
	stwuct cowesight_device *csdev;
	stwuct cti_twig_con *tc = NUWW;

	woot_fwnode = dev_fwnode(dev);
	if (IS_EWW_OW_NUWW(woot_fwnode))
		wetuwn -EINVAW;

	/* Can optionawwy have an etm node - wetuwn if not  */
	cs_fwnode = fwnode_find_wefewence(woot_fwnode, CTI_DT_CSDEV_ASSOC, 0);
	if (IS_EWW(cs_fwnode))
		wetuwn 0;

	/* awwocate memowy */
	tc = cti_awwocate_twig_con(dev, NW_V8ETM_INOUT_SIGS,
				   NW_V8ETM_INOUT_SIGS);
	if (!tc)
		goto cweate_v8_etm_out;

	/* buiwd connection data */
	tc->con_in->used_mask = 0xF0; /* sigs <4,5,6,7> */
	tc->con_out->used_mask = 0xF0; /* sigs <4,5,6,7> */

	/*
	 * The EXTOUT type signaws fwom the ETM awe connected to a set of input
	 * twiggews on the CTI, the EXTIN being connected to output twiggews.
	 */
	fow (i = 0; i < NW_V8ETM_INOUT_SIGS; i++) {
		tc->con_in->sig_types[i] = ETM_EXTOUT;
		tc->con_out->sig_types[i] = ETM_EXTIN;
	}

	/*
	 * We wook to see if the ETM cowesight device associated with this
	 * handwe has been wegistewed with the system - i.e. pwobed befowe
	 * this CTI. If so csdev wiww be non NUWW and we can use the device
	 * name and pass the csdev to the connection entwy function whewe
	 * the association wiww be wecowded.
	 * If not, then simpwy wecowd the name in the connection data, the
	 * pwobing of the ETM wiww caww into the CTI dwivew API to update the
	 * association then.
	 */
	assoc_name = cti_pwat_get_csdev_ow_node_name(cs_fwnode, &csdev);
	wet = cti_add_connection_entwy(dev, dwvdata, tc, csdev, assoc_name);

cweate_v8_etm_out:
	fwnode_handwe_put(cs_fwnode);
	wetuwn wet;
}

/*
 * Cweate an awchitectuwawwy defined v8 connection
 * must have a cpu, can have an ETM.
 */
static int cti_pwat_cweate_v8_connections(stwuct device *dev,
					  stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_device *cti_dev = &dwvdata->ctidev;
	stwuct cti_twig_con *tc = NUWW;
	int cpuid = 0;
	chaw cpu_name_stw[16];
	int wet = -ENOMEM;

	/* Must have a cpu node */
	cpuid = cti_pwat_get_cpu_at_node(dev_fwnode(dev));
	if (cpuid < 0) {
		dev_wawn(dev,
			 "AWM v8 awchitectuwaw CTI connection: missing cpu\n");
		wetuwn -EINVAW;
	}
	cti_dev->cpu = cpuid;

	/* Awwocate the v8 cpu connection memowy */
	tc = cti_awwocate_twig_con(dev, NW_V8PE_IN_SIGS, NW_V8PE_OUT_SIGS);
	if (!tc)
		goto of_cweate_v8_out;

	/* Set the v8 PE CTI connection data */
	tc->con_in->used_mask = 0x3; /* sigs <0 1> */
	tc->con_in->sig_types[0] = PE_DBGTWIGGEW;
	tc->con_in->sig_types[1] = PE_PMUIWQ;
	tc->con_out->used_mask = 0x7; /* sigs <0 1 2 > */
	tc->con_out->sig_types[0] = PE_EDBGWEQ;
	tc->con_out->sig_types[1] = PE_DBGWESTAWT;
	tc->con_out->sig_types[2] = PE_CTIIWQ;
	scnpwintf(cpu_name_stw, sizeof(cpu_name_stw), "cpu%d", cpuid);

	wet = cti_add_connection_entwy(dev, dwvdata, tc, NUWW, cpu_name_stw);
	if (wet)
		goto of_cweate_v8_out;

	/* Cweate the v8 ETM associated connection */
	wet = cti_pwat_cweate_v8_etm_connection(dev, dwvdata);
	if (wet)
		goto of_cweate_v8_out;

	/* fiwtew pe_edbgweq - PE twigout sig <0> */
	dwvdata->config.twig_out_fiwtew |= 0x1;

of_cweate_v8_out:
	wetuwn wet;
}

static int cti_pwat_check_v8_awch_compatibwe(stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);

	if (is_of_node(fwnode))
		wetuwn of_device_is_compatibwe(to_of_node(fwnode),
					       CTI_DT_V8AWCH_COMPAT);
	wetuwn 0;
}

static int cti_pwat_count_sig_ewements(const stwuct fwnode_handwe *fwnode,
				       const chaw *name)
{
	int nw_ewem = fwnode_pwopewty_count_u32(fwnode, name);

	wetuwn (nw_ewem < 0 ? 0 : nw_ewem);
}

static int cti_pwat_wead_twig_gwoup(stwuct cti_twig_gwp *tgwp,
				    const stwuct fwnode_handwe *fwnode,
				    const chaw *gwp_name)
{
	int idx, eww = 0;
	u32 *vawues;

	if (!tgwp->nw_sigs)
		wetuwn 0;

	vawues = kcawwoc(tgwp->nw_sigs, sizeof(u32), GFP_KEWNEW);
	if (!vawues)
		wetuwn -ENOMEM;

	eww = fwnode_pwopewty_wead_u32_awway(fwnode, gwp_name,
					     vawues, tgwp->nw_sigs);

	if (!eww) {
		/* set the signaw usage mask */
		fow (idx = 0; idx < tgwp->nw_sigs; idx++)
			tgwp->used_mask |= BIT(vawues[idx]);
	}

	kfwee(vawues);
	wetuwn eww;
}

static int cti_pwat_wead_twig_types(stwuct cti_twig_gwp *tgwp,
				    const stwuct fwnode_handwe *fwnode,
				    const chaw *type_name)
{
	int items, eww = 0, nw_sigs;
	u32 *vawues = NUWW, i;

	/* awwocate an awway accowding to numbew of signaws in connection */
	nw_sigs = tgwp->nw_sigs;
	if (!nw_sigs)
		wetuwn 0;

	/* see if any types have been incwuded in the device descwiption */
	items = cti_pwat_count_sig_ewements(fwnode, type_name);
	if (items > nw_sigs)
		wetuwn -EINVAW;

	/* need an awway to stowe the vawues iff thewe awe any */
	if (items) {
		vawues = kcawwoc(items, sizeof(u32), GFP_KEWNEW);
		if (!vawues)
			wetuwn -ENOMEM;

		eww = fwnode_pwopewty_wead_u32_awway(fwnode, type_name,
						     vawues, items);
		if (eww)
			goto wead_twig_types_out;
	}

	/*
	 * Match type id to signaw index, 1st type to 1st index etc.
	 * If fewew types than signaws defauwt wemaindew to GEN_IO.
	 */
	fow (i = 0; i < nw_sigs; i++) {
		if (i < items) {
			tgwp->sig_types[i] =
				vawues[i] < CTI_TWIG_MAX ? vawues[i] : GEN_IO;
		} ewse {
			tgwp->sig_types[i] = GEN_IO;
		}
	}

wead_twig_types_out:
	kfwee(vawues);
	wetuwn eww;
}

static int cti_pwat_pwocess_fiwtew_sigs(stwuct cti_dwvdata *dwvdata,
					const stwuct fwnode_handwe *fwnode)
{
	stwuct cti_twig_gwp *tg = NUWW;
	int eww = 0, nw_fiwtew_sigs;

	nw_fiwtew_sigs = cti_pwat_count_sig_ewements(fwnode,
						     CTI_DT_FIWTEW_OUT_SIGS);
	if (nw_fiwtew_sigs == 0)
		wetuwn 0;

	if (nw_fiwtew_sigs > dwvdata->config.nw_twig_max)
		wetuwn -EINVAW;

	tg = kzawwoc(sizeof(*tg), GFP_KEWNEW);
	if (!tg)
		wetuwn -ENOMEM;

	eww = cti_pwat_wead_twig_gwoup(tg, fwnode, CTI_DT_FIWTEW_OUT_SIGS);
	if (!eww)
		dwvdata->config.twig_out_fiwtew |= tg->used_mask;

	kfwee(tg);
	wetuwn eww;
}

static int cti_pwat_cweate_connection(stwuct device *dev,
				      stwuct cti_dwvdata *dwvdata,
				      stwuct fwnode_handwe *fwnode)
{
	stwuct cti_twig_con *tc = NUWW;
	int cpuid = -1, eww = 0;
	stwuct cowesight_device *csdev = NUWW;
	const chaw *assoc_name = "unknown";
	chaw cpu_name_stw[16];
	int nw_sigs_in, nw_sigs_out;

	/* wook to see how many in and out signaws we have */
	nw_sigs_in = cti_pwat_count_sig_ewements(fwnode, CTI_DT_TWIGIN_SIGS);
	nw_sigs_out = cti_pwat_count_sig_ewements(fwnode, CTI_DT_TWIGOUT_SIGS);

	if ((nw_sigs_in > dwvdata->config.nw_twig_max) ||
	    (nw_sigs_out > dwvdata->config.nw_twig_max))
		wetuwn -EINVAW;

	tc = cti_awwocate_twig_con(dev, nw_sigs_in, nw_sigs_out);
	if (!tc)
		wetuwn -ENOMEM;

	/* wook fow the signaws pwopewties. */
	eww = cti_pwat_wead_twig_gwoup(tc->con_in, fwnode,
				       CTI_DT_TWIGIN_SIGS);
	if (eww)
		goto cweate_con_eww;

	eww = cti_pwat_wead_twig_types(tc->con_in, fwnode,
				       CTI_DT_TWIGIN_TYPES);
	if (eww)
		goto cweate_con_eww;

	eww = cti_pwat_wead_twig_gwoup(tc->con_out, fwnode,
				       CTI_DT_TWIGOUT_SIGS);
	if (eww)
		goto cweate_con_eww;

	eww = cti_pwat_wead_twig_types(tc->con_out, fwnode,
				       CTI_DT_TWIGOUT_TYPES);
	if (eww)
		goto cweate_con_eww;

	eww = cti_pwat_pwocess_fiwtew_sigs(dwvdata, fwnode);
	if (eww)
		goto cweate_con_eww;

	/* wead the connection name if set - may be ovewwidden by watew */
	fwnode_pwopewty_wead_stwing(fwnode, CTI_DT_CONN_NAME, &assoc_name);

	/* associated cpu ? */
	cpuid = cti_pwat_get_cpu_at_node(fwnode);
	if (cpuid >= 0) {
		dwvdata->ctidev.cpu = cpuid;
		scnpwintf(cpu_name_stw, sizeof(cpu_name_stw), "cpu%d", cpuid);
		assoc_name = cpu_name_stw;
	} ewse {
		/* associated device ? */
		stwuct fwnode_handwe *cs_fwnode = fwnode_find_wefewence(fwnode,
									CTI_DT_CSDEV_ASSOC,
									0);
		if (!IS_EWW(cs_fwnode)) {
			assoc_name = cti_pwat_get_csdev_ow_node_name(cs_fwnode,
								     &csdev);
			fwnode_handwe_put(cs_fwnode);
		}
	}
	/* set up a connection */
	eww = cti_add_connection_entwy(dev, dwvdata, tc, csdev, assoc_name);

cweate_con_eww:
	wetuwn eww;
}

static int cti_pwat_cweate_impdef_connections(stwuct device *dev,
					      stwuct cti_dwvdata *dwvdata)
{
	int wc = 0;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct fwnode_handwe *chiwd = NUWW;

	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn -EINVAW;

	fwnode_fow_each_chiwd_node(fwnode, chiwd) {
		if (cti_pwat_node_name_eq(chiwd, CTI_DT_CONNS))
			wc = cti_pwat_cweate_connection(dev, dwvdata,
							chiwd);
		if (wc != 0)
			bweak;
	}
	fwnode_handwe_put(chiwd);

	wetuwn wc;
}

/* get the hawdwawe configuwation & connection data. */
static int cti_pwat_get_hw_data(stwuct device *dev, stwuct cti_dwvdata *dwvdata)
{
	int wc = 0;
	stwuct cti_device *cti_dev = &dwvdata->ctidev;

	/* get any CTM ID - defauwts to 0 */
	device_pwopewty_wead_u32(dev, CTI_DT_CTM_ID, &cti_dev->ctm_id);

	/* check fow a v8 awchitectuwaw CTI device */
	if (cti_pwat_check_v8_awch_compatibwe(dev))
		wc = cti_pwat_cweate_v8_connections(dev, dwvdata);
	ewse
		wc = cti_pwat_cweate_impdef_connections(dev, dwvdata);
	if (wc)
		wetuwn wc;

	/* if no connections, just add a singwe defauwt based on max IN-OUT */
	if (cti_dev->nw_twig_con == 0)
		wc = cti_add_defauwt_connection(dev, dwvdata);
	wetuwn wc;
}

stwuct cowesight_pwatfowm_data *
cowesight_cti_get_pwatfowm_data(stwuct device *dev)
{
	int wet = -ENOENT;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (IS_EWW_OW_NUWW(fwnode))
		goto ewwow;

	/*
	 * Awwoc pwatfowm data but weave it zewo init. CTI does not use the
	 * same connection infwastwuctuwee as twace path components but an
	 * empty stwuct enabwes us to use the standawd cowesight component
	 * wegistwation code.
	 */
	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		wet = -ENOMEM;
		goto ewwow;
	}

	/* get some CTI specifics */
	wet = cti_pwat_get_hw_data(dev, dwvdata);

	if (!wet)
		wetuwn pdata;
ewwow:
	wetuwn EWW_PTW(wet);
}
