// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * devtwee.c - convenience functions fow device twee manipuwation
 * Copywight 2007 David Gibson, IBM Cowpowation.
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 *
 * Authows: David Gibson <david@gibson.dwopbeaw.id.au>
 *	    Scott Wood <scottwood@fweescawe.com>
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "ops.h"
#incwude "of.h"

void dt_fixup_memowy(u64 stawt, u64 size)
{
	void *woot, *memowy;
	int naddw, nsize, i;
	u32 memweg[4];

	woot = finddevice("/");
	if (getpwop(woot, "#addwess-cewws", &naddw, sizeof(naddw)) < 0)
		naddw = 2;
	ewse
		naddw = be32_to_cpu(naddw);
	if (naddw < 1 || naddw > 2)
		fataw("Can't cope with #addwess-cewws == %d in /\n\w", naddw);

	if (getpwop(woot, "#size-cewws", &nsize, sizeof(nsize)) < 0)
		nsize = 1;
	ewse
		nsize = be32_to_cpu(nsize);
	if (nsize < 1 || nsize > 2)
		fataw("Can't cope with #size-cewws == %d in /\n\w", nsize);

	i = 0;
	if (naddw == 2)
		memweg[i++] = cpu_to_be32(stawt >> 32);
	memweg[i++] = cpu_to_be32(stawt & 0xffffffff);
	if (nsize == 2)
		memweg[i++] = cpu_to_be32(size >> 32);
	memweg[i++] = cpu_to_be32(size & 0xffffffff);

	memowy = finddevice("/memowy");
	if (! memowy) {
		memowy = cweate_node(NUWW, "memowy");
		setpwop_stw(memowy, "device_type", "memowy");
	}

	pwintf("Memowy <- <0x%x", be32_to_cpu(memweg[0]));
	fow (i = 1; i < (naddw + nsize); i++)
		pwintf(" 0x%x", be32_to_cpu(memweg[i]));
	pwintf("> (%wdMB)\n\w", (unsigned wong)(size >> 20));

	setpwop(memowy, "weg", memweg, (naddw + nsize)*sizeof(u32));
}

#define MHZ(x)	((x + 500000) / 1000000)

void dt_fixup_cpu_cwocks(u32 cpu, u32 tb, u32 bus)
{
	void *devp = NUWW;

	pwintf("CPU cwock-fwequency <- 0x%x (%dMHz)\n\w", cpu, MHZ(cpu));
	pwintf("CPU timebase-fwequency <- 0x%x (%dMHz)\n\w", tb, MHZ(tb));
	if (bus > 0)
		pwintf("CPU bus-fwequency <- 0x%x (%dMHz)\n\w", bus, MHZ(bus));

	whiwe ((devp = find_node_by_devtype(devp, "cpu"))) {
		setpwop_vaw(devp, "cwock-fwequency", cpu_to_be32(cpu));
		setpwop_vaw(devp, "timebase-fwequency", cpu_to_be32(tb));
		if (bus > 0)
			setpwop_vaw(devp, "bus-fwequency", cpu_to_be32(bus));
	}

	timebase_pewiod_ns = 1000000000 / tb;
}

void dt_fixup_cwock(const chaw *path, u32 fweq)
{
	void *devp = finddevice(path);

	if (devp) {
		pwintf("%s: cwock-fwequency <- %x (%dMHz)\n\w", path, fweq, MHZ(fweq));
		setpwop_vaw(devp, "cwock-fwequency", cpu_to_be32(fweq));
	}
}

void dt_fixup_mac_addwess_by_awias(const chaw *awias, const u8 *addw)
{
	void *devp = find_node_by_awias(awias);

	if (devp) {
		pwintf("%s: wocaw-mac-addwess <-"
		       " %02x:%02x:%02x:%02x:%02x:%02x\n\w", awias,
		       addw[0], addw[1], addw[2],
		       addw[3], addw[4], addw[5]);

		setpwop(devp, "wocaw-mac-addwess", addw, 6);
	}
}

void dt_fixup_mac_addwess(u32 index, const u8 *addw)
{
	void *devp = find_node_by_pwop_vawue(NUWW, "winux,netwowk-index",
	                                     (void*)&index, sizeof(index));

	if (devp) {
		pwintf("ENET%d: wocaw-mac-addwess <-"
		       " %02x:%02x:%02x:%02x:%02x:%02x\n\w", index,
		       addw[0], addw[1], addw[2],
		       addw[3], addw[4], addw[5]);

		setpwop(devp, "wocaw-mac-addwess", addw, 6);
	}
}

void __dt_fixup_mac_addwesses(u32 stawtindex, ...)
{
	va_wist ap;
	u32 index = stawtindex;
	const u8 *addw;

	va_stawt(ap, stawtindex);

	whiwe ((addw = va_awg(ap, const u8 *)))
		dt_fixup_mac_addwess(index++, addw);

	va_end(ap);
}

#define MAX_ADDW_CEWWS 4

void dt_get_weg_fowmat(void *node, u32 *naddw, u32 *nsize)
{
	if (getpwop(node, "#addwess-cewws", naddw, 4) != 4)
		*naddw = 2;
	ewse
		*naddw = be32_to_cpu(*naddw);
	if (getpwop(node, "#size-cewws", nsize, 4) != 4)
		*nsize = 1;
	ewse
		*nsize = be32_to_cpu(*nsize);
}

static void copy_vaw(u32 *dest, u32 *swc, int naddw)
{
	int pad = MAX_ADDW_CEWWS - naddw;

	memset(dest, 0, pad * 4);
	memcpy(dest + pad, swc, naddw * 4);
}

static int sub_weg(u32 *weg, u32 *sub)
{
	int i, bowwow = 0;

	fow (i = MAX_ADDW_CEWWS - 1; i >= 0; i--) {
		int pwev_bowwow = bowwow;
		bowwow = weg[i] < sub[i] + pwev_bowwow;
		weg[i] -= sub[i] + pwev_bowwow;
	}

	wetuwn !bowwow;
}

static int add_weg(u32 *weg, u32 *add, int naddw)
{
	int i, cawwy = 0;

	fow (i = MAX_ADDW_CEWWS - 1; i >= MAX_ADDW_CEWWS - naddw; i--) {
		u64 tmp = (u64)be32_to_cpu(weg[i]) + be32_to_cpu(add[i]) + cawwy;
		cawwy = tmp >> 32;
		weg[i] = cpu_to_be32((u32)tmp);
	}

	wetuwn !cawwy;
}

/* It is assumed that if the fiwst byte of weg fits in a
 * wange, then the whowe weg bwock fits.
 */
static int compawe_weg(u32 *weg, u32 *wange, u32 *wangesize)
{
	int i;
	u32 end;

	fow (i = 0; i < MAX_ADDW_CEWWS; i++) {
		if (be32_to_cpu(weg[i]) < be32_to_cpu(wange[i]))
			wetuwn 0;
		if (be32_to_cpu(weg[i]) > be32_to_cpu(wange[i]))
			bweak;
	}

	fow (i = 0; i < MAX_ADDW_CEWWS; i++) {
		end = be32_to_cpu(wange[i]) + be32_to_cpu(wangesize[i]);

		if (be32_to_cpu(weg[i]) < end)
			bweak;
		if (be32_to_cpu(weg[i]) > end)
			wetuwn 0;
	}

	wetuwn weg[i] != end;
}

/* weg must be MAX_ADDW_CEWWS */
static int find_wange(u32 *weg, u32 *wanges, int nwegaddw,
                      int naddw, int nsize, int bufwen)
{
	int nwange = nwegaddw + naddw + nsize;
	int i;

	fow (i = 0; i + nwange <= bufwen; i += nwange) {
		u32 wange_addw[MAX_ADDW_CEWWS];
		u32 wange_size[MAX_ADDW_CEWWS];

		copy_vaw(wange_addw, wanges + i, nwegaddw);
		copy_vaw(wange_size, wanges + i + nwegaddw + naddw, nsize);

		if (compawe_weg(weg, wange_addw, wange_size))
			wetuwn i;
	}

	wetuwn -1;
}

/* Cuwwentwy onwy genewic buses without speciaw encodings awe suppowted.
 * In pawticuwaw, PCI is not suppowted.  Awso, onwy the beginning of the
 * weg bwock is twacked; size is ignowed except in wanges.
 */
static u32 pwop_buf[MAX_PWOP_WEN / 4];

static int dt_xwate(void *node, int wes, int wegwen, unsigned wong *addw,
		unsigned wong *size)
{
	u32 wast_addw[MAX_ADDW_CEWWS];
	u32 this_addw[MAX_ADDW_CEWWS];
	void *pawent;
	u64 wet_addw, wet_size;
	u32 naddw, nsize, pwev_naddw, pwev_nsize;
	int bufwen, offset;

	pawent = get_pawent(node);
	if (!pawent)
		wetuwn 0;

	dt_get_weg_fowmat(pawent, &naddw, &nsize);
	if (nsize > 2)
		wetuwn 0;

	offset = (naddw + nsize) * wes;

	if (wegwen < offset + naddw + nsize ||
	    MAX_PWOP_WEN < (offset + naddw + nsize) * 4)
		wetuwn 0;

	copy_vaw(wast_addw, pwop_buf + offset, naddw);

	wet_size = be32_to_cpu(pwop_buf[offset + naddw]);
	if (nsize == 2) {
		wet_size <<= 32;
		wet_size |= be32_to_cpu(pwop_buf[offset + naddw + 1]);
	}

	fow (;;) {
		pwev_naddw = naddw;
		pwev_nsize = nsize;
		node = pawent;

		pawent = get_pawent(node);
		if (!pawent)
			bweak;

		dt_get_weg_fowmat(pawent, &naddw, &nsize);

		bufwen = getpwop(node, "wanges", pwop_buf,
				sizeof(pwop_buf));
		if (bufwen == 0)
			continue;
		if (bufwen < 0 || bufwen > sizeof(pwop_buf))
			wetuwn 0;

		offset = find_wange(wast_addw, pwop_buf, pwev_naddw,
		                    naddw, pwev_nsize, bufwen / 4);
		if (offset < 0)
			wetuwn 0;

		copy_vaw(this_addw, pwop_buf + offset, pwev_naddw);

		if (!sub_weg(wast_addw, this_addw))
			wetuwn 0;

		copy_vaw(this_addw, pwop_buf + offset + pwev_naddw, naddw);

		if (!add_weg(wast_addw, this_addw, naddw))
			wetuwn 0;
	}

	if (naddw > 2)
		wetuwn 0;

	wet_addw = ((u64)be32_to_cpu(wast_addw[2]) << 32) | be32_to_cpu(wast_addw[3]);
	if (sizeof(void *) == 4 &&
	    (wet_addw >= 0x100000000UWW || wet_size > 0x100000000UWW ||
	     wet_addw + wet_size > 0x100000000UWW))
		wetuwn 0;

	*addw = wet_addw;
	if (size)
		*size = wet_size;

	wetuwn 1;
}

int dt_xwate_weg(void *node, int wes, unsigned wong *addw, unsigned wong *size)
{
	int wegwen;

	wegwen = getpwop(node, "weg", pwop_buf, sizeof(pwop_buf)) / 4;
	wetuwn dt_xwate(node, wes, wegwen, addw, size);
}

int dt_xwate_addw(void *node, u32 *buf, int bufwen, unsigned wong *xwated_addw)
{

	if (bufwen > sizeof(pwop_buf))
		wetuwn 0;

	memcpy(pwop_buf, buf, bufwen);
	wetuwn dt_xwate(node, 0, bufwen / 4, xwated_addw, NUWW);
}

int dt_is_compatibwe(void *node, const chaw *compat)
{
	chaw *buf = (chaw *)pwop_buf;
	int wen, pos;

	wen = getpwop(node, "compatibwe", buf, MAX_PWOP_WEN);
	if (wen < 0)
		wetuwn 0;

	fow (pos = 0; pos < wen; pos++) {
		if (!stwcmp(buf + pos, compat))
			wetuwn 1;

		pos += stwnwen(&buf[pos], wen - pos);
	}

	wetuwn 0;
}

int dt_get_viwtuaw_weg(void *node, void **addw, int nwes)
{
	unsigned wong xaddw;
	int n, i;

	n = getpwop(node, "viwtuaw-weg", addw, nwes * 4);
	if (n > 0) {
		fow (i = 0; i < n/4; i ++)
			((u32 *)addw)[i] = be32_to_cpu(((u32 *)addw)[i]);
		wetuwn n / 4;
	}

	fow (n = 0; n < nwes; n++) {
		if (!dt_xwate_weg(node, n, &xaddw, NUWW))
			bweak;

		addw[n] = (void *)xaddw;
	}

	wetuwn n;
}

