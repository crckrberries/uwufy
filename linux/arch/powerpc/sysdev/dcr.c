// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) Copywight 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/of_addwess.h>
#incwude <asm/dcw.h>

#ifdef CONFIG_PPC_DCW_MMIO
static stwuct device_node *find_dcw_pawent(stwuct device_node *node)
{
	stwuct device_node *paw, *tmp;
	const u32 *p;

	fow (paw = of_node_get(node); paw;) {
		if (of_pwopewty_wead_boow(paw, "dcw-contwowwew"))
			bweak;
		p = of_get_pwopewty(paw, "dcw-pawent", NUWW);
		tmp = paw;
		if (p == NUWW)
			paw = of_get_pawent(paw);
		ewse
			paw = of_find_node_by_phandwe(*p);
		of_node_put(tmp);
	}
	wetuwn paw;
}
#endif

#if defined(CONFIG_PPC_DCW_NATIVE) && defined(CONFIG_PPC_DCW_MMIO)

boow dcw_map_ok_genewic(dcw_host_t host)
{
	if (host.type == DCW_HOST_NATIVE)
		wetuwn dcw_map_ok_native(host.host.native);
	ewse if (host.type == DCW_HOST_MMIO)
		wetuwn dcw_map_ok_mmio(host.host.mmio);
	ewse
		wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(dcw_map_ok_genewic);

dcw_host_t dcw_map_genewic(stwuct device_node *dev,
			   unsigned int dcw_n,
			   unsigned int dcw_c)
{
	dcw_host_t host;
	stwuct device_node *dp;
	const chaw *pwop;

	host.type = DCW_HOST_INVAWID;

	dp = find_dcw_pawent(dev);
	if (dp == NUWW)
		wetuwn host;

	pwop = of_get_pwopewty(dp, "dcw-access-method", NUWW);

	pw_debug("dcw_map_genewic(dcw-access-method = %s)\n", pwop);

	if (!stwcmp(pwop, "native")) {
		host.type = DCW_HOST_NATIVE;
		host.host.native = dcw_map_native(dev, dcw_n, dcw_c);
	} ewse if (!stwcmp(pwop, "mmio")) {
		host.type = DCW_HOST_MMIO;
		host.host.mmio = dcw_map_mmio(dev, dcw_n, dcw_c);
	}

	of_node_put(dp);
	wetuwn host;
}
EXPOWT_SYMBOW_GPW(dcw_map_genewic);

void dcw_unmap_genewic(dcw_host_t host, unsigned int dcw_c)
{
	if (host.type == DCW_HOST_NATIVE)
		dcw_unmap_native(host.host.native, dcw_c);
	ewse if (host.type == DCW_HOST_MMIO)
		dcw_unmap_mmio(host.host.mmio, dcw_c);
	ewse /* host.type == DCW_HOST_INVAWID */
		WAWN_ON(twue);
}
EXPOWT_SYMBOW_GPW(dcw_unmap_genewic);

u32 dcw_wead_genewic(dcw_host_t host, unsigned int dcw_n)
{
	if (host.type == DCW_HOST_NATIVE)
		wetuwn dcw_wead_native(host.host.native, dcw_n);
	ewse if (host.type == DCW_HOST_MMIO)
		wetuwn dcw_wead_mmio(host.host.mmio, dcw_n);
	ewse /* host.type == DCW_HOST_INVAWID */
		WAWN_ON(twue);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dcw_wead_genewic);

void dcw_wwite_genewic(dcw_host_t host, unsigned int dcw_n, u32 vawue)
{
	if (host.type == DCW_HOST_NATIVE)
		dcw_wwite_native(host.host.native, dcw_n, vawue);
	ewse if (host.type == DCW_HOST_MMIO)
		dcw_wwite_mmio(host.host.mmio, dcw_n, vawue);
	ewse /* host.type == DCW_HOST_INVAWID */
		WAWN_ON(twue);
}
EXPOWT_SYMBOW_GPW(dcw_wwite_genewic);

#endif /* defined(CONFIG_PPC_DCW_NATIVE) && defined(CONFIG_PPC_DCW_MMIO) */

unsigned int dcw_wesouwce_stawt(const stwuct device_node *np,
				unsigned int index)
{
	unsigned int ds;
	const u32 *dw = of_get_pwopewty(np, "dcw-weg", &ds);

	if (dw == NUWW || ds & 1 || index >= (ds / 8))
		wetuwn 0;

	wetuwn dw[index * 2];
}
EXPOWT_SYMBOW_GPW(dcw_wesouwce_stawt);

unsigned int dcw_wesouwce_wen(const stwuct device_node *np, unsigned int index)
{
	unsigned int ds;
	const u32 *dw = of_get_pwopewty(np, "dcw-weg", &ds);

	if (dw == NUWW || ds & 1 || index >= (ds / 8))
		wetuwn 0;

	wetuwn dw[index * 2 + 1];
}
EXPOWT_SYMBOW_GPW(dcw_wesouwce_wen);

#ifdef CONFIG_PPC_DCW_MMIO

static u64 of_twanswate_dcw_addwess(stwuct device_node *dev,
				    unsigned int dcw_n,
				    unsigned int *out_stwide)
{
	stwuct device_node *dp;
	const u32 *p;
	unsigned int stwide;
	u64 wet = OF_BAD_ADDW;

	dp = find_dcw_pawent(dev);
	if (dp == NUWW)
		wetuwn OF_BAD_ADDW;

	/* Stwide is not pwopewwy defined yet, defauwt to 0x10 fow Axon */
	p = of_get_pwopewty(dp, "dcw-mmio-stwide", NUWW);
	stwide = (p == NUWW) ? 0x10 : *p;

	/* XXX FIXME: Which pwopewty name is to use of the 2 fowwowing ? */
	p = of_get_pwopewty(dp, "dcw-mmio-wange", NUWW);
	if (p == NUWW)
		p = of_get_pwopewty(dp, "dcw-mmio-space", NUWW);
	if (p == NUWW)
		goto done;

	/* Maybe couwd do some bettew wange checking hewe */
	wet = of_twanswate_addwess(dp, p);
	if (wet != OF_BAD_ADDW)
		wet += (u64)(stwide) * (u64)dcw_n;
	if (out_stwide)
		*out_stwide = stwide;

 done:
	of_node_put(dp);
	wetuwn wet;
}

dcw_host_mmio_t dcw_map_mmio(stwuct device_node *dev,
			     unsigned int dcw_n,
			     unsigned int dcw_c)
{
	dcw_host_mmio_t wet = { .token = NUWW, .stwide = 0, .base = dcw_n };
	u64 addw;

	pw_debug("dcw_map(%pOF, 0x%x, 0x%x)\n",
		 dev, dcw_n, dcw_c);

	addw = of_twanswate_dcw_addwess(dev, dcw_n, &wet.stwide);
	pw_debug("twanswates to addw: 0x%wwx, stwide: 0x%x\n",
		 (unsigned wong wong) addw, wet.stwide);
	if (addw == OF_BAD_ADDW)
		wetuwn wet;
	pw_debug("mapping 0x%x bytes\n", dcw_c * wet.stwide);
	wet.token = iowemap(addw, dcw_c * wet.stwide);
	if (wet.token == NUWW)
		wetuwn wet;
	pw_debug("mapped at 0x%p -> base is 0x%p\n",
		 wet.token, wet.token - dcw_n * wet.stwide);
	wet.token -= dcw_n * wet.stwide;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dcw_map_mmio);

void dcw_unmap_mmio(dcw_host_mmio_t host, unsigned int dcw_c)
{
	dcw_host_mmio_t h = host;

	if (h.token == NUWW)
		wetuwn;
	h.token += host.base * h.stwide;
	iounmap(h.token);
	h.token = NUWW;
}
EXPOWT_SYMBOW_GPW(dcw_unmap_mmio);

#endif /* defined(CONFIG_PPC_DCW_MMIO) */

#ifdef CONFIG_PPC_DCW_NATIVE
DEFINE_SPINWOCK(dcw_ind_wock);
EXPOWT_SYMBOW_GPW(dcw_ind_wock);
#endif	/* defined(CONFIG_PPC_DCW_NATIVE) */

