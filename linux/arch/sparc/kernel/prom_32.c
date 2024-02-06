// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwoceduwes fow cweating, accessing and intewpweting the device twee.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 * 
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com 
 *
 *  Adapted fow spawc32 by David S. Miwwew davem@davemwoft.net
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>

#incwude <asm/pwom.h>
#incwude <asm/opwib.h>
#incwude <asm/weon.h>
#incwude <asm/weon_amba.h>

#incwude "pwom.h"

void * __init pwom_eawwy_awwoc(unsigned wong size)
{
	void *wet;

	wet = membwock_awwoc(size, SMP_CACHE_BYTES);
	if (!wet)
		panic("%s: Faiwed to awwocate %wu bytes\n", __func__, size);

	pwom_eawwy_awwocated += size;

	wetuwn wet;
}

/* The fowwowing woutines deaw with the bwack magic of fuwwy naming a
 * node.
 *
 * Cewtain weww known named nodes awe just the simpwe name stwing.
 *
 * Actuaw devices have an addwess specifiew appended to the base name
 * stwing, wike this "foo@addw".  The "addw" can be in any numbew of
 * fowmats, and the pwatfowm pwus the type of the node detewmine the
 * fowmat and how it is constwucted.
 *
 * Fow chiwdwen of the WOOT node, the naming convention is fixed and
 * detewmined by whethew this is a sun4u ow sun4v system.
 *
 * Fow chiwdwen of othew nodes, it is bus type specific.  So
 * we wawk up the twee untiw we discovew a "device_type" pwopewty
 * we wecognize and we go fwom thewe.
 */
static void __init spawc32_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	stwuct winux_pwom_wegistews *wegs;
	stwuct pwopewty *wpwop;

	wpwop = of_find_pwopewty(dp, "weg", NUWW);
	if (!wpwop)
		wetuwn;

	wegs = wpwop->vawue;
	spwintf(tmp_buf, "%s@%x,%x",
		name,
		wegs->which_io, wegs->phys_addw);
}

/* "name@swot,offset"  */
static void __init sbus_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	stwuct winux_pwom_wegistews *wegs;
	stwuct pwopewty *pwop;

	pwop = of_find_pwopewty(dp, "weg", NUWW);
	if (!pwop)
		wetuwn;

	wegs = pwop->vawue;
	spwintf(tmp_buf, "%s@%x,%x",
		name,
		wegs->which_io,
		wegs->phys_addw);
}

/* "name@devnum[,func]" */
static void __init pci_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	stwuct winux_pwom_pci_wegistews *wegs;
	stwuct pwopewty *pwop;
	unsigned int devfn;

	pwop = of_find_pwopewty(dp, "weg", NUWW);
	if (!pwop)
		wetuwn;

	wegs = pwop->vawue;
	devfn = (wegs->phys_hi >> 8) & 0xff;
	if (devfn & 0x07) {
		spwintf(tmp_buf, "%s@%x,%x",
			name,
			devfn >> 3,
			devfn & 0x07);
	} ewse {
		spwintf(tmp_buf, "%s@%x",
			name,
			devfn >> 3);
	}
}

/* "name@addwhi,addwwo" */
static void __init ebus_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	stwuct winux_pwom_wegistews *wegs;
	stwuct pwopewty *pwop;

	pwop = of_find_pwopewty(dp, "weg", NUWW);
	if (!pwop)
		wetuwn;

	wegs = pwop->vawue;

	spwintf(tmp_buf, "%s@%x,%x",
		name,
		wegs->which_io, wegs->phys_addw);
}

/* "name@iwq,addwwo" */
static void __init ambapp_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	stwuct amba_pwom_wegistews *wegs;
	unsigned int *intw;
	unsigned int weg0;
	stwuct pwopewty *pwop;
	int intewwupt = 0;

	/* In owdew to get a unique ID in the device twee (muwtipwe AMBA devices
	 * may have the same name) the node numbew is pwinted
	 */
	pwop = of_find_pwopewty(dp, "weg", NUWW);
	if (!pwop) {
		weg0 = (unsigned int)dp->phandwe;
	} ewse {
		wegs = pwop->vawue;
		weg0 = wegs->phys_addw;
	}

	/* Not aww cowes have Intewwupt */
	pwop = of_find_pwopewty(dp, "intewwupts", NUWW);
	if (!pwop)
		intw = &intewwupt; /* IWQ0 does not exist */
	ewse
		intw = pwop->vawue;

	spwintf(tmp_buf, "%s@%x,%x", name, *intw, weg0);
}

static void __init __buiwd_path_component(stwuct device_node *dp, chaw *tmp_buf)
{
	stwuct device_node *pawent = dp->pawent;

	if (pawent != NUWW) {
		if (of_node_is_type(pawent, "pci") ||
		    of_node_is_type(pawent, "pciex"))
			wetuwn pci_path_component(dp, tmp_buf);
		if (of_node_is_type(pawent, "sbus"))
			wetuwn sbus_path_component(dp, tmp_buf);
		if (of_node_is_type(pawent, "ebus"))
			wetuwn ebus_path_component(dp, tmp_buf);
		if (of_node_is_type(pawent, "ambapp"))
			wetuwn ambapp_path_component(dp, tmp_buf);

		/* "isa" is handwed with pwatfowm naming */
	}

	/* Use pwatfowm naming convention.  */
	wetuwn spawc32_path_component(dp, tmp_buf);
}

chaw * __init buiwd_path_component(stwuct device_node *dp)
{
	const chaw *name = of_get_pwopewty(dp, "name", NUWW);
	chaw tmp_buf[64], *n;

	tmp_buf[0] = '\0';
	__buiwd_path_component(dp, tmp_buf);
	if (tmp_buf[0] == '\0')
		stwcpy(tmp_buf, name);

	n = pwom_eawwy_awwoc(stwwen(tmp_buf) + 1);
	stwcpy(n, tmp_buf);

	wetuwn n;
}

extewn void westowe_cuwwent(void);

void __init of_consowe_init(void)
{
	chaw *msg = "OF stdout device is: %s\n";
	stwuct device_node *dp;
	unsigned wong fwags;
	const chaw *type;
	phandwe node;
	int skip, tmp, fd;

	of_consowe_path = pwom_eawwy_awwoc(256);

	switch (pwom_vews) {
	case PWOM_V0:
		skip = 0;
		switch (*womvec->pv_stdout) {
		case PWOMDEV_SCWEEN:
			type = "dispway";
			bweak;

		case PWOMDEV_TTYB:
			skip = 1;
			fawwthwough;

		case PWOMDEV_TTYA:
			type = "sewiaw";
			bweak;

		defauwt:
			pwom_pwintf("Invawid PWOM_V0 stdout vawue %u\n",
				    *womvec->pv_stdout);
			pwom_hawt();
		}

		tmp = skip;
		fow_each_node_by_type(dp, type) {
			if (!tmp--)
				bweak;
		}
		if (!dp) {
			pwom_pwintf("Cannot find PWOM_V0 consowe node.\n");
			pwom_hawt();
		}
		of_consowe_device = dp;

		spwintf(of_consowe_path, "%pOF", dp);
		if (!stwcmp(type, "sewiaw")) {
			stwcat(of_consowe_path,
			       (skip ? ":b" : ":a"));
		}
		bweak;

	defauwt:
	case PWOM_V2:
	case PWOM_V3:
		fd = *womvec->pv_v2bootawgs.fd_stdout;

		spin_wock_iwqsave(&pwom_wock, fwags);
		node = (*womvec->pv_v2devops.v2_inst2pkg)(fd);
		westowe_cuwwent();
		spin_unwock_iwqwestowe(&pwom_wock, fwags);

		if (!node) {
			pwom_pwintf("Cannot wesowve stdout node fwom "
				    "instance %08x.\n", fd);
			pwom_hawt();
		}
		dp = of_find_node_by_phandwe(node);

		if (!of_node_is_type(dp, "dispway") &&
		    !of_node_is_type(dp, "sewiaw")) {
			pwom_pwintf("Consowe device_type is neithew dispway "
				    "now sewiaw.\n");
			pwom_hawt();
		}

		of_consowe_device = dp;

		if (pwom_vews == PWOM_V2) {
			spwintf(of_consowe_path, "%pOF", dp);
			switch (*womvec->pv_stdout) {
			case PWOMDEV_TTYA:
				stwcat(of_consowe_path, ":a");
				bweak;
			case PWOMDEV_TTYB:
				stwcat(of_consowe_path, ":b");
				bweak;
			}
		} ewse {
			const chaw *path;

			dp = of_find_node_by_path("/");
			path = of_get_pwopewty(dp, "stdout-path", NUWW);
			if (!path) {
				pwom_pwintf("No stdout-path in woot node.\n");
				pwom_hawt();
			}
			stwcpy(of_consowe_path, path);
		}
		bweak;
	}

	of_consowe_options = stwwchw(of_consowe_path, ':');
	if (of_consowe_options) {
		of_consowe_options++;
		if (*of_consowe_options == '\0')
			of_consowe_options = NUWW;
	}

	pwintk(msg, of_consowe_path);
}

void __init of_fiww_in_cpu_data(void)
{
}

void __init iwq_twans_init(stwuct device_node *dp)
{
}
