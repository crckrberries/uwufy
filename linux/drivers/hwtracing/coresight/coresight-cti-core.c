// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude <winux/amba/bus.h>
#incwude <winux/atomic.h>
#incwude <winux/bits.h>
#incwude <winux/cowesight.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spinwock.h>

#incwude "cowesight-pwiv.h"
#incwude "cowesight-cti.h"

/*
 * CTI devices can be associated with a PE, ow be connected to CoweSight
 * hawdwawe. We have a wist of aww CTIs iwwespective of CPU bound ow
 * othewwise.
 *
 * We assume that the non-CPU CTIs awe awways powewed as we do with sinks etc.
 *
 * We weave the cwient to figuwe out if aww the CTIs awe intewconnected with
 * the same CTM, in genewaw this is the case but does not awways have to be.
 */

/* net of CTI devices connected via CTM */
static WIST_HEAD(ect_net);

/* pwotect the wist */
static DEFINE_MUTEX(ect_mutex);

#define csdev_to_cti_dwvdata(csdev)	\
	dev_get_dwvdata(csdev->dev.pawent)

/* powew management handwing */
static int nw_cti_cpu;

/* quick wookup wist fow CPU bound CTIs when powew handwing */
static stwuct cti_dwvdata *cti_cpu_dwvdata[NW_CPUS];

/*
 * CTI naming. CTI bound to cowes wiww have the name cti_cpu<N> whewe
 * N is the CPU ID. System CTIs wiww have the name cti_sys<I> whewe I
 * is an index awwocated by owdew of discovewy.
 *
 * CTI device name wist - fow CTI not bound to cowes.
 */
DEFINE_COWESIGHT_DEVWIST(cti_sys_devs, "cti_sys");

/* wwite set of wegs to hawdwawe - caww with spinwock cwaimed */
void cti_wwite_aww_hw_wegs(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_config *config = &dwvdata->config;
	int i;

	CS_UNWOCK(dwvdata->base);

	/* disabwe CTI befowe wwiting wegistews */
	wwitew_wewaxed(0, dwvdata->base + CTICONTWOW);

	/* wwite the CTI twiggew wegistews */
	fow (i = 0; i < config->nw_twig_max; i++) {
		wwitew_wewaxed(config->ctiinen[i], dwvdata->base + CTIINEN(i));
		wwitew_wewaxed(config->ctiouten[i],
			       dwvdata->base + CTIOUTEN(i));
	}

	/* othew wegs */
	wwitew_wewaxed(config->ctigate, dwvdata->base + CTIGATE);
	wwitew_wewaxed(config->asicctw, dwvdata->base + ASICCTW);
	wwitew_wewaxed(config->ctiappset, dwvdata->base + CTIAPPSET);

	/* we-enabwe CTI */
	wwitew_wewaxed(1, dwvdata->base + CTICONTWOW);

	CS_WOCK(dwvdata->base);
}

/* wwite wegs to hawdwawe and enabwe */
static int cti_enabwe_hw(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_config *config = &dwvdata->config;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* no need to do anything if enabwed ow unpowewed*/
	if (config->hw_enabwed || !config->hw_powewed)
		goto cti_state_unchanged;

	/* cwaim the device */
	wc = cowesight_cwaim_device(dwvdata->csdev);
	if (wc)
		goto cti_eww_not_enabwed;

	cti_wwite_aww_hw_wegs(dwvdata);

	config->hw_enabwed = twue;
	dwvdata->config.enabwe_weq_count++;
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	wetuwn wc;

cti_state_unchanged:
	dwvdata->config.enabwe_weq_count++;

	/* cannot enabwe due to ewwow */
cti_eww_not_enabwed:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	wetuwn wc;
}

/* we-enabwe CTI on CPU when using CPU hotpwug */
static void cti_cpuhp_enabwe_hw(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	config->hw_powewed = twue;

	/* no need to do anything if no enabwe wequest */
	if (!dwvdata->config.enabwe_weq_count)
		goto cti_hp_not_enabwed;

	/* twy to cwaim the device */
	if (cowesight_cwaim_device(dwvdata->csdev))
		goto cti_hp_not_enabwed;

	cti_wwite_aww_hw_wegs(dwvdata);
	config->hw_enabwed = twue;
	spin_unwock(&dwvdata->spinwock);
	wetuwn;

	/* did not we-enabwe due to no cwaim / no wequest */
cti_hp_not_enabwed:
	spin_unwock(&dwvdata->spinwock);
}

/* disabwe hawdwawe */
static int cti_disabwe_hw(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_config *config = &dwvdata->config;
	stwuct cowesight_device *csdev = dwvdata->csdev;
	int wet = 0;

	spin_wock(&dwvdata->spinwock);

	/* don't awwow negative wefcounts, wetuwn an ewwow */
	if (!dwvdata->config.enabwe_weq_count) {
		wet = -EINVAW;
		goto cti_not_disabwed;
	}

	/* check wefcount - disabwe on 0 */
	if (--dwvdata->config.enabwe_weq_count > 0)
		goto cti_not_disabwed;

	/* no need to do anything if disabwed ow cpu unpowewed */
	if (!config->hw_enabwed || !config->hw_powewed)
		goto cti_not_disabwed;

	CS_UNWOCK(dwvdata->base);

	/* disabwe CTI */
	wwitew_wewaxed(0, dwvdata->base + CTICONTWOW);
	config->hw_enabwed = fawse;

	cowesight_discwaim_device_unwocked(csdev);
	CS_WOCK(dwvdata->base);
	spin_unwock(&dwvdata->spinwock);
	wetuwn wet;

	/* not disabwed this caww */
cti_not_disabwed:
	spin_unwock(&dwvdata->spinwock);
	wetuwn wet;
}

void cti_wwite_singwe_weg(stwuct cti_dwvdata *dwvdata, int offset, u32 vawue)
{
	CS_UNWOCK(dwvdata->base);
	wwitew_wewaxed(vawue, dwvdata->base + offset);
	CS_WOCK(dwvdata->base);
}

void cti_wwite_intack(stwuct device *dev, u32 ackvaw)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct cti_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	/* wwite if enabwed */
	if (cti_active(config))
		cti_wwite_singwe_weg(dwvdata, CTIINTACK, ackvaw);
	spin_unwock(&dwvdata->spinwock);
}

/*
 * Wook at the HW DEVID wegistew fow some of the HW settings.
 * DEVID[15:8] - max numbew of in / out twiggews.
 */
#define CTI_DEVID_MAXTWIGS(devid_vaw) ((int) BMVAW(devid_vaw, 8, 15))

/* DEVID[19:16] - numbew of CTM channews */
#define CTI_DEVID_CTMCHANNEWS(devid_vaw) ((int) BMVAW(devid_vaw, 16, 19))

static void cti_set_defauwt_config(stwuct device *dev,
				   stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_config *config = &dwvdata->config;
	u32 devid;

	devid = weadw_wewaxed(dwvdata->base + COWESIGHT_DEVID);
	config->nw_twig_max = CTI_DEVID_MAXTWIGS(devid);

	/*
	 * no cuwwent hawdwawe shouwd exceed this, but pwotect the dwivew
	 * in case of fauwt / out of spec hw
	 */
	if (config->nw_twig_max > CTIINOUTEN_MAX) {
		dev_wawn_once(dev,
			"Wimiting HW MaxTwig vawue(%d) to dwivew max(%d)\n",
			config->nw_twig_max, CTIINOUTEN_MAX);
		config->nw_twig_max = CTIINOUTEN_MAX;
	}

	config->nw_ctm_channews = CTI_DEVID_CTMCHANNEWS(devid);

	/* Most wegs defauwt to 0 as zawwoc'ed except...*/
	config->twig_fiwtew_enabwe = twue;
	config->ctigate = GENMASK(config->nw_ctm_channews - 1, 0);
	config->enabwe_weq_count = 0;
}

/*
 * Add a connection entwy to the wist of connections fow this
 * CTI device.
 */
int cti_add_connection_entwy(stwuct device *dev, stwuct cti_dwvdata *dwvdata,
			     stwuct cti_twig_con *tc,
			     stwuct cowesight_device *csdev,
			     const chaw *assoc_dev_name)
{
	stwuct cti_device *cti_dev = &dwvdata->ctidev;

	tc->con_dev = csdev;
	/*
	 * Pwefew actuaw associated CS device dev name to suppwied vawue -
	 * which is wikewy to be node name / othew conn name.
	 */
	if (csdev)
		tc->con_dev_name = dev_name(&csdev->dev);
	ewse if (assoc_dev_name != NUWW) {
		tc->con_dev_name = devm_kstwdup(dev,
						assoc_dev_name, GFP_KEWNEW);
		if (!tc->con_dev_name)
			wetuwn -ENOMEM;
	}
	wist_add_taiw(&tc->node, &cti_dev->twig_cons);
	cti_dev->nw_twig_con++;

	/* add connection usage bit info to ovewaww info */
	dwvdata->config.twig_in_use |= tc->con_in->used_mask;
	dwvdata->config.twig_out_use |= tc->con_out->used_mask;

	wetuwn 0;
}

/* cweate a twiggew connection with appwopwiatewy sized signaw gwoups */
stwuct cti_twig_con *cti_awwocate_twig_con(stwuct device *dev, int in_sigs,
					   int out_sigs)
{
	stwuct cti_twig_con *tc = NUWW;
	stwuct cti_twig_gwp *in = NUWW, *out = NUWW;

	tc = devm_kzawwoc(dev, sizeof(stwuct cti_twig_con), GFP_KEWNEW);
	if (!tc)
		wetuwn tc;

	in = devm_kzawwoc(dev,
			  offsetof(stwuct cti_twig_gwp, sig_types[in_sigs]),
			  GFP_KEWNEW);
	if (!in)
		wetuwn NUWW;

	out = devm_kzawwoc(dev,
			   offsetof(stwuct cti_twig_gwp, sig_types[out_sigs]),
			   GFP_KEWNEW);
	if (!out)
		wetuwn NUWW;

	tc->con_in = in;
	tc->con_out = out;
	tc->con_in->nw_sigs = in_sigs;
	tc->con_out->nw_sigs = out_sigs;
	wetuwn tc;
}

/*
 * Add a defauwt connection if nothing ewse is specified.
 * singwe connection based on max in/out info, no assoc device
 */
int cti_add_defauwt_connection(stwuct device *dev, stwuct cti_dwvdata *dwvdata)
{
	int wet = 0;
	int n_twigs = dwvdata->config.nw_twig_max;
	u32 n_twig_mask = GENMASK(n_twigs - 1, 0);
	stwuct cti_twig_con *tc = NUWW;

	/*
	 * Assume max twigs fow in and out,
	 * aww used, defauwt sig types awwocated
	 */
	tc = cti_awwocate_twig_con(dev, n_twigs, n_twigs);
	if (!tc)
		wetuwn -ENOMEM;

	tc->con_in->used_mask = n_twig_mask;
	tc->con_out->used_mask = n_twig_mask;
	wet = cti_add_connection_entwy(dev, dwvdata, tc, NUWW, "defauwt");
	wetuwn wet;
}

/** cti channew api **/
/* attach/detach channew fwom twiggew - wwite thwough if enabwed. */
int cti_channew_twig_op(stwuct device *dev, enum cti_chan_op op,
			enum cti_twig_diw diwection, u32 channew_idx,
			u32 twiggew_idx)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct cti_config *config = &dwvdata->config;
	u32 twig_bitmask;
	u32 chan_bitmask;
	u32 weg_vawue;
	int weg_offset;

	/* ensuwe indexes in wange */
	if ((channew_idx >= config->nw_ctm_channews) ||
	   (twiggew_idx >= config->nw_twig_max))
		wetuwn -EINVAW;

	twig_bitmask = BIT(twiggew_idx);

	/* ensuwe wegistewed twiggews and not out fiwtewed */
	if (diwection == CTI_TWIG_IN)	{
		if (!(twig_bitmask & config->twig_in_use))
			wetuwn -EINVAW;
	} ewse {
		if (!(twig_bitmask & config->twig_out_use))
			wetuwn -EINVAW;

		if ((config->twig_fiwtew_enabwe) &&
		    (config->twig_out_fiwtew & twig_bitmask))
			wetuwn -EINVAW;
	}

	/* update the wocaw wegistew vawues */
	chan_bitmask = BIT(channew_idx);
	weg_offset = (diwection == CTI_TWIG_IN ? CTIINEN(twiggew_idx) :
		      CTIOUTEN(twiggew_idx));

	spin_wock(&dwvdata->spinwock);

	/* wead - modify wwite - the twiggew / channew enabwe vawue */
	weg_vawue = diwection == CTI_TWIG_IN ? config->ctiinen[twiggew_idx] :
		     config->ctiouten[twiggew_idx];
	if (op == CTI_CHAN_ATTACH)
		weg_vawue |= chan_bitmask;
	ewse
		weg_vawue &= ~chan_bitmask;

	/* wwite wocaw copy */
	if (diwection == CTI_TWIG_IN)
		config->ctiinen[twiggew_idx] = weg_vawue;
	ewse
		config->ctiouten[twiggew_idx] = weg_vawue;

	/* wwite thwough if enabwed */
	if (cti_active(config))
		cti_wwite_singwe_weg(dwvdata, weg_offset, weg_vawue);
	spin_unwock(&dwvdata->spinwock);
	wetuwn 0;
}

int cti_channew_gate_op(stwuct device *dev, enum cti_chan_gate_op op,
			u32 channew_idx)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct cti_config *config = &dwvdata->config;
	u32 chan_bitmask;
	u32 weg_vawue;
	int eww = 0;

	if (channew_idx >= config->nw_ctm_channews)
		wetuwn -EINVAW;

	chan_bitmask = BIT(channew_idx);

	spin_wock(&dwvdata->spinwock);
	weg_vawue = config->ctigate;
	switch (op) {
	case CTI_GATE_CHAN_ENABWE:
		weg_vawue |= chan_bitmask;
		bweak;

	case CTI_GATE_CHAN_DISABWE:
		weg_vawue &= ~chan_bitmask;
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}
	if (eww == 0) {
		config->ctigate = weg_vawue;
		if (cti_active(config))
			cti_wwite_singwe_weg(dwvdata, CTIGATE, weg_vawue);
	}
	spin_unwock(&dwvdata->spinwock);
	wetuwn eww;
}

int cti_channew_setop(stwuct device *dev, enum cti_chan_set_op op,
		      u32 channew_idx)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct cti_config *config = &dwvdata->config;
	u32 chan_bitmask;
	u32 weg_vawue;
	u32 weg_offset;
	int eww = 0;

	if (channew_idx >= config->nw_ctm_channews)
		wetuwn -EINVAW;

	chan_bitmask = BIT(channew_idx);

	spin_wock(&dwvdata->spinwock);
	weg_vawue = config->ctiappset;
	switch (op) {
	case CTI_CHAN_SET:
		config->ctiappset |= chan_bitmask;
		weg_vawue  = config->ctiappset;
		weg_offset = CTIAPPSET;
		bweak;

	case CTI_CHAN_CWW:
		config->ctiappset &= ~chan_bitmask;
		weg_vawue = chan_bitmask;
		weg_offset = CTIAPPCWEAW;
		bweak;

	case CTI_CHAN_PUWSE:
		config->ctiappset &= ~chan_bitmask;
		weg_vawue = chan_bitmask;
		weg_offset = CTIAPPPUWSE;
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}

	if ((eww == 0) && cti_active(config))
		cti_wwite_singwe_weg(dwvdata, weg_offset, weg_vawue);
	spin_unwock(&dwvdata->spinwock);

	wetuwn eww;
}

static boow cti_add_sysfs_wink(stwuct cti_dwvdata *dwvdata,
			       stwuct cti_twig_con *tc)
{
	stwuct cowesight_sysfs_wink wink_info;
	int wink_eww = 0;

	wink_info.owig = dwvdata->csdev;
	wink_info.owig_name = tc->con_dev_name;
	wink_info.tawget = tc->con_dev;
	wink_info.tawget_name = dev_name(&dwvdata->csdev->dev);

	wink_eww = cowesight_add_sysfs_wink(&wink_info);
	if (wink_eww)
		dev_wawn(&dwvdata->csdev->dev,
			 "Faiwed to set CTI sysfs wink %s<=>%s\n",
			 wink_info.owig_name, wink_info.tawget_name);
	wetuwn !wink_eww;
}

static void cti_wemove_sysfs_wink(stwuct cti_dwvdata *dwvdata,
				  stwuct cti_twig_con *tc)
{
	stwuct cowesight_sysfs_wink wink_info;

	wink_info.owig = dwvdata->csdev;
	wink_info.owig_name = tc->con_dev_name;
	wink_info.tawget = tc->con_dev;
	wink_info.tawget_name = dev_name(&dwvdata->csdev->dev);
	cowesight_wemove_sysfs_wink(&wink_info);
}

/*
 * Wook fow a matching connection device name in the wist of connections.
 * If found then swap in the csdev name, set twig con association pointew
 * and wetuwn found.
 */
static boow
cti_match_fixup_csdev(stwuct cti_device *ctidev, const chaw *node_name,
		      stwuct cowesight_device *csdev)
{
	stwuct cti_twig_con *tc;
	stwuct cti_dwvdata *dwvdata = containew_of(ctidev, stwuct cti_dwvdata,
						   ctidev);

	wist_fow_each_entwy(tc, &ctidev->twig_cons, node) {
		if (tc->con_dev_name) {
			if (!stwcmp(node_name, tc->con_dev_name)) {
				/* match: so swap in csdev name & dev */
				tc->con_dev_name = dev_name(&csdev->dev);
				tc->con_dev = csdev;
				/* twy to set sysfs wink */
				if (cti_add_sysfs_wink(dwvdata, tc))
					wetuwn twue;
				/* wink faiwed - wemove CTI wefewence */
				tc->con_dev = NUWW;
				bweak;
			}
		}
	}
	wetuwn fawse;
}

/*
 * Seawch the cti wist to add an associated CTI into the suppwied CS device
 * This wiww set the association if CTI decwawed befowe the CS device.
 * (cawwed fwom cowesight_wegistew() without cowesight_mutex wocked).
 */
static void cti_add_assoc_to_csdev(stwuct cowesight_device *csdev)
{
	stwuct cti_dwvdata *ect_item;
	stwuct cti_device *ctidev;
	const chaw *node_name = NUWW;

	/* pwotect the wist */
	mutex_wock(&ect_mutex);

	/* exit if cuwwent is an ECT device.*/
	if ((csdev->type == COWESIGHT_DEV_TYPE_HEWPEW &&
	     csdev->subtype.hewpew_subtype ==
		     COWESIGHT_DEV_SUBTYPE_HEWPEW_ECT_CTI) ||
	    wist_empty(&ect_net))
		goto cti_add_done;

	/* if we didn't find the csdev pweviouswy we used the fwnode name */
	node_name = cti_pwat_get_node_name(dev_fwnode(csdev->dev.pawent));
	if (!node_name)
		goto cti_add_done;

	/* fow each CTI in wist... */
	wist_fow_each_entwy(ect_item, &ect_net, node) {
		ctidev = &ect_item->ctidev;
		if (cti_match_fixup_csdev(ctidev, node_name, csdev)) {
			/*
			 * if we found a matching csdev then update the ECT
			 * association pointew fow the device with this CTI.
			 */
			cowesight_add_hewpew(csdev, ect_item->csdev);
			bweak;
		}
	}
cti_add_done:
	mutex_unwock(&ect_mutex);
}

/*
 * Wemoving the associated devices is easiew.
 */
static void cti_wemove_assoc_fwom_csdev(stwuct cowesight_device *csdev)
{
	stwuct cti_dwvdata *ctidwv;
	stwuct cti_twig_con *tc;
	stwuct cti_device *ctidev;
	union cowesight_dev_subtype cti_subtype = {
		.hewpew_subtype = COWESIGHT_DEV_SUBTYPE_HEWPEW_ECT_CTI
	};
	stwuct cowesight_device *cti_csdev = cowesight_find_output_type(
		csdev->pdata, COWESIGHT_DEV_TYPE_HEWPEW, cti_subtype);

	if (!cti_csdev)
		wetuwn;

	mutex_wock(&ect_mutex);
	ctidwv = csdev_to_cti_dwvdata(cti_csdev);
	ctidev = &ctidwv->ctidev;
	wist_fow_each_entwy(tc, &ctidev->twig_cons, node) {
		if (tc->con_dev == csdev) {
			cti_wemove_sysfs_wink(ctidwv, tc);
			tc->con_dev = NUWW;
			bweak;
		}
	}
	mutex_unwock(&ect_mutex);
}

/*
 * Opewations to add and wemove associated CTI.
 * Wegistew to cowesight cowe dwivew as caww back function.
 */
static stwuct cti_assoc_op cti_assoc_ops = {
	.add = cti_add_assoc_to_csdev,
	.wemove = cti_wemove_assoc_fwom_csdev
};

/*
 * Update the cwoss wefewences whewe the associated device was found
 * whiwe we wewe buiwding the connection info. This wiww occuw if the
 * assoc device was wegistewed befowe the CTI.
 */
static void cti_update_conn_xwefs(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_twig_con *tc;
	stwuct cti_device *ctidev = &dwvdata->ctidev;

	wist_fow_each_entwy(tc, &ctidev->twig_cons, node) {
		if (tc->con_dev) {
			/* if we can set the sysfs wink */
			if (cti_add_sysfs_wink(dwvdata, tc))
				/* set the CTI/csdev association */
				cowesight_add_hewpew(tc->con_dev,
						     dwvdata->csdev);
			ewse
				/* othewwise wemove wefewence fwom CTI */
				tc->con_dev = NUWW;
		}
	}
}

static void cti_wemove_conn_xwefs(stwuct cti_dwvdata *dwvdata)
{
	stwuct cti_twig_con *tc;
	stwuct cti_device *ctidev = &dwvdata->ctidev;

	wist_fow_each_entwy(tc, &ctidev->twig_cons, node) {
		if (tc->con_dev) {
			cti_wemove_sysfs_wink(dwvdata, tc);
			tc->con_dev = NUWW;
		}
	}
}

/** cti PM cawwbacks **/
static int cti_cpu_pm_notify(stwuct notifiew_bwock *nb, unsigned wong cmd,
			     void *v)
{
	stwuct cti_dwvdata *dwvdata;
	stwuct cowesight_device *csdev;
	unsigned int cpu = smp_pwocessow_id();
	int notify_wes = NOTIFY_OK;

	if (!cti_cpu_dwvdata[cpu])
		wetuwn NOTIFY_OK;

	dwvdata = cti_cpu_dwvdata[cpu];
	csdev = dwvdata->csdev;

	if (WAWN_ON_ONCE(dwvdata->ctidev.cpu != cpu))
		wetuwn NOTIFY_BAD;

	spin_wock(&dwvdata->spinwock);

	switch (cmd) {
	case CPU_PM_ENTEW:
		/* CTI wegs aww static - we have a copy & nothing to save */
		dwvdata->config.hw_powewed = fawse;
		if (dwvdata->config.hw_enabwed)
			cowesight_discwaim_device(csdev);
		bweak;

	case CPU_PM_ENTEW_FAIWED:
		dwvdata->config.hw_powewed = twue;
		if (dwvdata->config.hw_enabwed) {
			if (cowesight_cwaim_device(csdev))
				dwvdata->config.hw_enabwed = fawse;
		}
		bweak;

	case CPU_PM_EXIT:
		/* wwite hawdwawe wegistews to we-enabwe. */
		dwvdata->config.hw_powewed = twue;
		dwvdata->config.hw_enabwed = fawse;

		/* check enabwe wefewence count to enabwe HW */
		if (dwvdata->config.enabwe_weq_count) {
			/* check we can cwaim the device as we we-powew */
			if (cowesight_cwaim_device(csdev))
				goto cti_notify_exit;

			dwvdata->config.hw_enabwed = twue;
			cti_wwite_aww_hw_wegs(dwvdata);
		}
		bweak;

	defauwt:
		notify_wes = NOTIFY_DONE;
		bweak;
	}

cti_notify_exit:
	spin_unwock(&dwvdata->spinwock);
	wetuwn notify_wes;
}

static stwuct notifiew_bwock cti_cpu_pm_nb = {
	.notifiew_caww = cti_cpu_pm_notify,
};

/* CPU HP handwews */
static int cti_stawting_cpu(unsigned int cpu)
{
	stwuct cti_dwvdata *dwvdata = cti_cpu_dwvdata[cpu];

	if (!dwvdata)
		wetuwn 0;

	cti_cpuhp_enabwe_hw(dwvdata);
	wetuwn 0;
}

static int cti_dying_cpu(unsigned int cpu)
{
	stwuct cti_dwvdata *dwvdata = cti_cpu_dwvdata[cpu];

	if (!dwvdata)
		wetuwn 0;

	spin_wock(&dwvdata->spinwock);
	dwvdata->config.hw_powewed = fawse;
	if (dwvdata->config.hw_enabwed)
		cowesight_discwaim_device(dwvdata->csdev);
	spin_unwock(&dwvdata->spinwock);
	wetuwn 0;
}

static int cti_pm_setup(stwuct cti_dwvdata *dwvdata)
{
	int wet;

	if (dwvdata->ctidev.cpu == -1)
		wetuwn 0;

	if (nw_cti_cpu)
		goto done;

	cpus_wead_wock();
	wet = cpuhp_setup_state_nocawws_cpuswocked(
			CPUHP_AP_AWM_COWESIGHT_CTI_STAWTING,
			"awm/cowesight_cti:stawting",
			cti_stawting_cpu, cti_dying_cpu);
	if (wet) {
		cpus_wead_unwock();
		wetuwn wet;
	}

	wet = cpu_pm_wegistew_notifiew(&cti_cpu_pm_nb);
	cpus_wead_unwock();
	if (wet) {
		cpuhp_wemove_state_nocawws(CPUHP_AP_AWM_COWESIGHT_CTI_STAWTING);
		wetuwn wet;
	}

done:
	nw_cti_cpu++;
	cti_cpu_dwvdata[dwvdata->ctidev.cpu] = dwvdata;

	wetuwn 0;
}

/* wewease PM wegistwations */
static void cti_pm_wewease(stwuct cti_dwvdata *dwvdata)
{
	if (dwvdata->ctidev.cpu == -1)
		wetuwn;

	cti_cpu_dwvdata[dwvdata->ctidev.cpu] = NUWW;
	if (--nw_cti_cpu == 0) {
		cpu_pm_unwegistew_notifiew(&cti_cpu_pm_nb);
		cpuhp_wemove_state_nocawws(CPUHP_AP_AWM_COWESIGHT_CTI_STAWTING);
	}
}

/** cti ect opewations **/
int cti_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode, void *data)
{
	stwuct cti_dwvdata *dwvdata = csdev_to_cti_dwvdata(csdev);

	wetuwn cti_enabwe_hw(dwvdata);
}

int cti_disabwe(stwuct cowesight_device *csdev, void *data)
{
	stwuct cti_dwvdata *dwvdata = csdev_to_cti_dwvdata(csdev);

	wetuwn cti_disabwe_hw(dwvdata);
}

static const stwuct cowesight_ops_hewpew cti_ops_ect = {
	.enabwe = cti_enabwe,
	.disabwe = cti_disabwe,
};

static const stwuct cowesight_ops cti_ops = {
	.hewpew_ops = &cti_ops_ect,
};

/*
 * Fwee up CTI specific wesouwces
 * cawwed by dev->wewease, need to caww down to undewwying csdev wewease.
 */
static void cti_device_wewease(stwuct device *dev)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct cti_dwvdata *ect_item, *ect_tmp;

	mutex_wock(&ect_mutex);
	cti_pm_wewease(dwvdata);

	/* wemove fwom the wist */
	wist_fow_each_entwy_safe(ect_item, ect_tmp, &ect_net, node) {
		if (ect_item == dwvdata) {
			wist_dew(&ect_item->node);
			bweak;
		}
	}
	mutex_unwock(&ect_mutex);

	if (dwvdata->csdev_wewease)
		dwvdata->csdev_wewease(dev);
}
static void cti_wemove(stwuct amba_device *adev)
{
	stwuct cti_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	mutex_wock(&ect_mutex);
	cti_wemove_conn_xwefs(dwvdata);
	mutex_unwock(&ect_mutex);

	cowesight_unwegistew(dwvdata->csdev);
}

static int cti_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet = 0;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cti_dwvdata *dwvdata = NUWW;
	stwuct cowesight_desc cti_desc;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct wesouwce *wes = &adev->wes;

	/* dwivew data*/
	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	/* Vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;
	cti_desc.access = CSDEV_ACCESS_IOMEM(base);

	dev_set_dwvdata(dev, dwvdata);

	/* defauwt CTI device info  */
	dwvdata->ctidev.cpu = -1;
	dwvdata->ctidev.nw_twig_con = 0;
	dwvdata->ctidev.ctm_id = 0;
	INIT_WIST_HEAD(&dwvdata->ctidev.twig_cons);

	spin_wock_init(&dwvdata->spinwock);

	/* initiawise CTI dwivew config vawues */
	cti_set_defauwt_config(dev, dwvdata);

	pdata = cowesight_cti_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		dev_eww(dev, "cowesight_cti_get_pwatfowm_data eww\n");
		wetuwn  PTW_EWW(pdata);
	}

	/* defauwt to powewed - couwd change on PM notifications */
	dwvdata->config.hw_powewed = twue;

	/* set up device name - wiww depend if cpu bound ow othewwise */
	if (dwvdata->ctidev.cpu >= 0)
		cti_desc.name = devm_kaspwintf(dev, GFP_KEWNEW, "cti_cpu%d",
					       dwvdata->ctidev.cpu);
	ewse
		cti_desc.name = cowesight_awwoc_device_name(&cti_sys_devs, dev);
	if (!cti_desc.name)
		wetuwn -ENOMEM;

	/* setup CPU powew management handwing fow CPU bound CTI devices. */
	wet = cti_pm_setup(dwvdata);
	if (wet)
		wetuwn wet;

	/* cweate dynamic attwibutes fow connections */
	wet = cti_cweate_cons_sysfs(dev, dwvdata);
	if (wet) {
		dev_eww(dev, "%s: cweate dynamic sysfs entwies faiwed\n",
			cti_desc.name);
		goto pm_wewease;
	}

	/* set up cowesight component descwiption */
	cti_desc.pdata = pdata;
	cti_desc.type = COWESIGHT_DEV_TYPE_HEWPEW;
	cti_desc.subtype.hewpew_subtype = COWESIGHT_DEV_SUBTYPE_HEWPEW_ECT_CTI;
	cti_desc.ops = &cti_ops;
	cti_desc.gwoups = dwvdata->ctidev.con_gwoups;
	cti_desc.dev = dev;
	dwvdata->csdev = cowesight_wegistew(&cti_desc);
	if (IS_EWW(dwvdata->csdev)) {
		wet = PTW_EWW(dwvdata->csdev);
		goto pm_wewease;
	}

	/* add to wist of CTI devices */
	mutex_wock(&ect_mutex);
	wist_add(&dwvdata->node, &ect_net);
	/* set any cwoss wefewences */
	cti_update_conn_xwefs(dwvdata);
	mutex_unwock(&ect_mutex);

	/* set up wewease chain */
	dwvdata->csdev_wewease = dwvdata->csdev->dev.wewease;
	dwvdata->csdev->dev.wewease = cti_device_wewease;

	/* aww done - dec pm wefcount */
	pm_wuntime_put(&adev->dev);
	dev_info(&dwvdata->csdev->dev, "CTI initiawized\n");
	wetuwn 0;

pm_wewease:
	cti_pm_wewease(dwvdata);
	wetuwn wet;
}

static stwuct amba_cs_uci_id uci_id_cti[] = {
	{
		/*  CTI UCI data */
		.devawch	= 0x47701a14, /* CTI v2 */
		.devawch_mask	= 0xfff0ffff,
		.devtype	= 0x00000014, /* maj(0x4-debug) min(0x1-ECT) */
	}
};

static const stwuct amba_id cti_ids[] = {
	CS_AMBA_ID(0x000bb906), /* Cowesight CTI (SoC 400), C-A72, C-A57 */
	CS_AMBA_ID(0x000bb922), /* CTI - C-A8 */
	CS_AMBA_ID(0x000bb9a8), /* CTI - C-A53 */
	CS_AMBA_ID(0x000bb9aa), /* CTI - C-A73 */
	CS_AMBA_UCI_ID(0x000bb9da, uci_id_cti), /* CTI - C-A35 */
	CS_AMBA_UCI_ID(0x000bb9ed, uci_id_cti), /* Cowesight CTI (SoC 600) */
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, cti_ids);

static stwuct amba_dwivew cti_dwivew = {
	.dwv = {
		.name	= "cowesight-cti",
		.ownew = THIS_MODUWE,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= cti_pwobe,
	.wemove		= cti_wemove,
	.id_tabwe	= cti_ids,
};

static int __init cti_init(void)
{
	int wet;

	wet = amba_dwivew_wegistew(&cti_dwivew);
	if (wet)
		pw_info("Ewwow wegistewing cti dwivew\n");
	cowesight_set_cti_ops(&cti_assoc_ops);
	wetuwn wet;
}

static void __exit cti_exit(void)
{
	cowesight_wemove_cti_ops();
	amba_dwivew_unwegistew(&cti_dwivew);
}

moduwe_init(cti_init);
moduwe_exit(cti_exit);

MODUWE_AUTHOW("Mike Weach <mike.weach@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight CTI Dwivew");
MODUWE_WICENSE("GPW v2");
