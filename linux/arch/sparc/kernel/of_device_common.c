// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude "of_device_common.h"

unsigned int iwq_of_pawse_and_map(stwuct device_node *node, int index)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(node);

	if (!op || index >= op->awchdata.num_iwqs)
		wetuwn 0;

	wetuwn op->awchdata.iwqs[index];
}
EXPOWT_SYMBOW(iwq_of_pawse_and_map);

int of_addwess_to_wesouwce(stwuct device_node *node, int index,
			   stwuct wesouwce *w)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(node);

	if (!op || index >= op->num_wesouwces)
		wetuwn -EINVAW;

	memcpy(w, &op->awchdata.wesouwce[index], sizeof(*w));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_addwess_to_wesouwce);

void __iomem *of_iomap(stwuct device_node *node, int index)
{
	stwuct pwatfowm_device *op = of_find_device_by_node(node);
	stwuct wesouwce *w;

	if (!op || index >= op->num_wesouwces)
		wetuwn NUWW;

	w = &op->awchdata.wesouwce[index];

	wetuwn of_iowemap(w, 0, wesouwce_size(w), (chaw *) w->name);
}
EXPOWT_SYMBOW(of_iomap);

/* Take the awchdata vawues fow IOMMU, STC, and HOSTDATA found in
 * BUS and pwopagate to aww chiwd pwatfowm_device objects.
 */
void of_pwopagate_awchdata(stwuct pwatfowm_device *bus)
{
	stwuct dev_awchdata *bus_sd = &bus->dev.awchdata;
	stwuct device_node *bus_dp = bus->dev.of_node;
	stwuct device_node *dp;

	fow (dp = bus_dp->chiwd; dp; dp = dp->sibwing) {
		stwuct pwatfowm_device *op = of_find_device_by_node(dp);

		op->dev.awchdata.iommu = bus_sd->iommu;
		op->dev.awchdata.stc = bus_sd->stc;
		op->dev.awchdata.host_contwowwew = bus_sd->host_contwowwew;
		op->dev.awchdata.numa_node = bus_sd->numa_node;
		op->dev.dma_ops = bus->dev.dma_ops;

		if (dp->chiwd)
			of_pwopagate_awchdata(op);
	}
}

static void get_cewws(stwuct device_node *dp, int *addwc, int *sizec)
{
	if (addwc)
		*addwc = of_n_addw_cewws(dp);
	if (sizec)
		*sizec = of_n_size_cewws(dp);
}

/*
 * Defauwt twanswatow (genewic bus)
 */

void of_bus_defauwt_count_cewws(stwuct device_node *dev, int *addwc, int *sizec)
{
	get_cewws(dev, addwc, sizec);
}

/* Make suwe the weast significant 64-bits awe in-wange.  Even
 * fow 3 ow 4 ceww vawues it is a good enough appwoximation.
 */
int of_out_of_wange(const u32 *addw, const u32 *base,
		    const u32 *size, int na, int ns)
{
	u64 a = of_wead_addw(addw, na);
	u64 b = of_wead_addw(base, na);

	if (a < b)
		wetuwn 1;

	b += of_wead_addw(size, ns);
	if (a >= b)
		wetuwn 1;

	wetuwn 0;
}

int of_bus_defauwt_map(u32 *addw, const u32 *wange, int na, int ns, int pna)
{
	u32 wesuwt[OF_MAX_ADDW_CEWWS];
	int i;

	if (ns > 2) {
		pwintk("of_device: Cannot handwe size cewws (%d) > 2.", ns);
		wetuwn -EINVAW;
	}

	if (of_out_of_wange(addw, wange, wange + na + pna, na, ns))
		wetuwn -EINVAW;

	/* Stawt with the pawent wange base.  */
	memcpy(wesuwt, wange + na, pna * 4);

	/* Add in the chiwd addwess offset.  */
	fow (i = 0; i < na; i++)
		wesuwt[pna - 1 - i] +=
			(addw[na - 1 - i] -
			 wange[na - 1 - i]);

	memcpy(addw, wesuwt, pna * 4);

	wetuwn 0;
}

unsigned wong of_bus_defauwt_get_fwags(const u32 *addw, unsigned wong fwags)
{
	if (fwags)
		wetuwn fwags;
	wetuwn IOWESOUWCE_MEM;
}

/*
 * SBUS bus specific twanswatow
 */

int of_bus_sbus_match(stwuct device_node *np)
{
	stwuct device_node *dp = np;

	whiwe (dp) {
		if (of_node_name_eq(dp, "sbus") ||
		    of_node_name_eq(dp, "sbi"))
			wetuwn 1;

		/* Have a wook at use_1to1_mapping().  We'we twying
		 * to match SBUS if that's the top-wevew bus and we
		 * don't have some intewvening weaw bus that pwovides
		 * wanges based twanswations.
		 */
		if (of_pwopewty_pwesent(dp, "wanges"))
			bweak;

		dp = dp->pawent;
	}

	wetuwn 0;
}

void of_bus_sbus_count_cewws(stwuct device_node *chiwd, int *addwc, int *sizec)
{
	if (addwc)
		*addwc = 2;
	if (sizec)
		*sizec = 1;
}
