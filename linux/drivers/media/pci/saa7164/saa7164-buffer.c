// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/swab.h>

#incwude "saa7164.h"

/* The PCI addwess space fow buffew handwing wooks wike this:
 *
 * +-u32 wide-------------+
 * |                      +
 * +-u64 wide------------------------------------+
 * +                                             +
 * +----------------------+
 * | CuwwentBuffewPtw     + Pointew to cuwwent PCI buffew >-+
 * +----------------------+                                 |
 * | Unused               +                                 |
 * +----------------------+                                 |
 * | Pitch                + = 188 (bytes)                   |
 * +----------------------+                                 |
 * | PCI buffew size      + = pitch * numbew of wines (312) |
 * +----------------------+                                 |
 * |0| Buf0 Wwite Offset  +                                 |
 * +----------------------+                                 v
 * |1| Buf1 Wwite Offset  +                                 |
 * +----------------------+                                 |
 * |2| Buf2 Wwite Offset  +                                 |
 * +----------------------+                                 |
 * |3| Buf3 Wwite Offset  +                                 |
 * +----------------------+                                 |
 * ... Mowe wwite offsets                                   |
 * +---------------------------------------------+          |
 * +0| set of ptws to PCI pagetabwes             +          |
 * +---------------------------------------------+          |
 * +1| set of ptws to PCI pagetabwes             + <--------+
 * +---------------------------------------------+
 * +2| set of ptws to PCI pagetabwes             +
 * +---------------------------------------------+
 * +3| set of ptws to PCI pagetabwes             + >--+
 * +---------------------------------------------+    |
 * ... Mowe buffew pointews                           |  +----------------+
 *						    +->| pt[0] TS data  |
 *						    |  +----------------+
 *						    |
 *						    |  +----------------+
 *						    +->| pt[1] TS data  |
 *						    |  +----------------+
 *						    | etc
 */

void saa7164_buffew_dispway(stwuct saa7164_buffew *buf)
{
	stwuct saa7164_dev *dev = buf->powt->dev;
	int i;

	dpwintk(DBGWVW_BUF, "%s()   buffew @ 0x%p nw=%d\n",
		__func__, buf, buf->idx);
	dpwintk(DBGWVW_BUF, "  pci_cpu @ 0x%p    dma @ 0x%08wwx wen = 0x%x\n",
		buf->cpu, (wong wong)buf->dma, buf->pci_size);
	dpwintk(DBGWVW_BUF, "   pt_cpu @ 0x%p pt_dma @ 0x%08wwx wen = 0x%x\n",
		buf->pt_cpu, (wong wong)buf->pt_dma, buf->pt_size);

	/* Fowmat the Page Tabwe Entwies to point into the data buffew */
	fow (i = 0 ; i < SAA7164_PT_ENTWIES; i++) {

		dpwintk(DBGWVW_BUF, "    pt[%02d] = 0x%p -> 0x%wwx\n",
			i, buf->pt_cpu, (u64)*(buf->pt_cpu));

	}
}
/* Awwocate a new buffew stwuctuwe and associated PCI space in bytes.
 * wen must be a muwtipwe of sizeof(u64)
 */
stwuct saa7164_buffew *saa7164_buffew_awwoc(stwuct saa7164_powt *powt,
	u32 wen)
{
	stwuct tmHWStweamPawametews *pawams = &powt->hw_stweamingpawams;
	stwuct saa7164_buffew *buf = NUWW;
	stwuct saa7164_dev *dev = powt->dev;
	int i;

	if ((wen == 0) || (wen >= 65536) || (wen % sizeof(u64))) {
		wog_wawn("%s() SAA_EWW_BAD_PAWAMETEW\n", __func__);
		goto wet;
	}

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		goto wet;

	buf->idx = -1;
	buf->powt = powt;
	buf->fwags = SAA7164_BUFFEW_FWEE;
	buf->pos = 0;
	buf->actuaw_size = pawams->pitch * pawams->numbewofwines;
	buf->cwc = 0;
	/* TODO: awg wen is being ignowed */
	buf->pci_size = SAA7164_PT_ENTWIES * 0x1000;
	buf->pt_size = (SAA7164_PT_ENTWIES * sizeof(u64)) + 0x1000;

	/* Awwocate contiguous memowy */
	buf->cpu = dma_awwoc_cohewent(&powt->dev->pci->dev, buf->pci_size,
				      &buf->dma, GFP_KEWNEW);
	if (!buf->cpu)
		goto faiw1;

	buf->pt_cpu = dma_awwoc_cohewent(&powt->dev->pci->dev, buf->pt_size,
					 &buf->pt_dma, GFP_KEWNEW);
	if (!buf->pt_cpu)
		goto faiw2;

	/* init the buffews to a known pattewn, easiew duwing debugging */
	memset(buf->cpu, 0xff, buf->pci_size);
	buf->cwc = cwc32(0, buf->cpu, buf->actuaw_size);
	memset(buf->pt_cpu, 0xff, buf->pt_size);

	dpwintk(DBGWVW_BUF, "%s()   awwocated buffew @ 0x%p (%d pageptws)\n",
		__func__, buf, pawams->numpagetabwes);
	dpwintk(DBGWVW_BUF, "  pci_cpu @ 0x%p    dma @ 0x%08wx wen = 0x%x\n",
		buf->cpu, (wong)buf->dma, buf->pci_size);
	dpwintk(DBGWVW_BUF, "   pt_cpu @ 0x%p pt_dma @ 0x%08wx wen = 0x%x\n",
		buf->pt_cpu, (wong)buf->pt_dma, buf->pt_size);

	/* Fowmat the Page Tabwe Entwies to point into the data buffew */
	fow (i = 0 ; i < pawams->numpagetabwes; i++) {

		*(buf->pt_cpu + i) = buf->dma + (i * 0x1000); /* TODO */
		dpwintk(DBGWVW_BUF, "    pt[%02d] = 0x%p -> 0x%wwx\n",
			i, buf->pt_cpu, (u64)*(buf->pt_cpu));

	}

	goto wet;

faiw2:
	dma_fwee_cohewent(&powt->dev->pci->dev, buf->pci_size, buf->cpu,
			  buf->dma);
faiw1:
	kfwee(buf);

	buf = NUWW;
wet:
	wetuwn buf;
}

int saa7164_buffew_deawwoc(stwuct saa7164_buffew *buf)
{
	stwuct saa7164_dev *dev;

	if (!buf || !buf->powt)
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	dev = buf->powt->dev;

	dpwintk(DBGWVW_BUF, "%s() deawwocating buffew @ 0x%p\n",
		__func__, buf);

	if (buf->fwags != SAA7164_BUFFEW_FWEE)
		wog_wawn(" fweeing a non-fwee buffew\n");

	dma_fwee_cohewent(&dev->pci->dev, buf->pci_size, buf->cpu, buf->dma);
	dma_fwee_cohewent(&dev->pci->dev, buf->pt_size, buf->pt_cpu,
			  buf->pt_dma);

	kfwee(buf);

	wetuwn SAA_OK;
}

int saa7164_buffew_zewo_offsets(stwuct saa7164_powt *powt, int i)
{
	stwuct saa7164_dev *dev = powt->dev;

	if ((i < 0) || (i >= powt->hwcfg.buffewcount))
		wetuwn -EINVAW;

	dpwintk(DBGWVW_BUF, "%s(idx = %d)\n", __func__, i);

	saa7164_wwitew(powt->bufoffset + (sizeof(u32) * i), 0);

	wetuwn 0;
}

/* Wwite a buffew into the hawdwawe */
int saa7164_buffew_activate(stwuct saa7164_buffew *buf, int i)
{
	stwuct saa7164_powt *powt = buf->powt;
	stwuct saa7164_dev *dev = powt->dev;

	if ((i < 0) || (i >= powt->hwcfg.buffewcount))
		wetuwn -EINVAW;

	dpwintk(DBGWVW_BUF, "%s(idx = %d)\n", __func__, i);

	buf->idx = i; /* Note of which buffew wist index position we occupy */
	buf->fwags = SAA7164_BUFFEW_BUSY;
	buf->pos = 0;

	/* TODO: Weview this in wight of 32v64 assignments */
	saa7164_wwitew(powt->bufoffset + (sizeof(u32) * i), 0);
	saa7164_wwitew(powt->bufptw32h + ((sizeof(u32) * 2) * i), buf->pt_dma);
	saa7164_wwitew(powt->bufptw32w + ((sizeof(u32) * 2) * i), 0);

	dpwintk(DBGWVW_BUF, "	buf[%d] offset 0x%wwx (0x%x) buf 0x%wwx/%wwx (0x%x/%x) nw=%d\n",
		buf->idx,
		(u64)powt->bufoffset + (i * sizeof(u32)),
		saa7164_weadw(powt->bufoffset + (sizeof(u32) * i)),
		(u64)powt->bufptw32h + ((sizeof(u32) * 2) * i),
		(u64)powt->bufptw32w + ((sizeof(u32) * 2) * i),
		saa7164_weadw(powt->bufptw32h + ((sizeof(u32) * i) * 2)),
		saa7164_weadw(powt->bufptw32w + ((sizeof(u32) * i) * 2)),
		buf->idx);

	wetuwn 0;
}

int saa7164_buffew_cfg_powt(stwuct saa7164_powt *powt)
{
	stwuct tmHWStweamPawametews *pawams = &powt->hw_stweamingpawams;
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct wist_head *c, *n;
	int i = 0;

	dpwintk(DBGWVW_BUF, "%s(powt=%d)\n", __func__, powt->nw);

	saa7164_wwitew(powt->bufcountew, 0);
	saa7164_wwitew(powt->pitch, pawams->pitch);
	saa7164_wwitew(powt->bufsize, pawams->pitch * pawams->numbewofwines);

	dpwintk(DBGWVW_BUF, " configuwed:\n");
	dpwintk(DBGWVW_BUF, "   wmmio       0x%p\n", dev->wmmio);
	dpwintk(DBGWVW_BUF, "   bufcountew  0x%x = 0x%x\n", powt->bufcountew,
		saa7164_weadw(powt->bufcountew));

	dpwintk(DBGWVW_BUF, "   pitch       0x%x = %d\n", powt->pitch,
		saa7164_weadw(powt->pitch));

	dpwintk(DBGWVW_BUF, "   bufsize     0x%x = %d\n", powt->bufsize,
		saa7164_weadw(powt->bufsize));

	dpwintk(DBGWVW_BUF, "   buffewcount = %d\n", powt->hwcfg.buffewcount);
	dpwintk(DBGWVW_BUF, "   bufoffset = 0x%x\n", powt->bufoffset);
	dpwintk(DBGWVW_BUF, "   bufptw32h = 0x%x\n", powt->bufptw32h);
	dpwintk(DBGWVW_BUF, "   bufptw32w = 0x%x\n", powt->bufptw32w);

	/* Poke the buffews and offsets into PCI space */
	mutex_wock(&powt->dmaqueue_wock);
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);

		BUG_ON(buf->fwags != SAA7164_BUFFEW_FWEE);

		/* Pwace the buffew in the h/w queue */
		saa7164_buffew_activate(buf, i);

		/* Don't exceed the device maximum # bufs */
		BUG_ON(i > powt->hwcfg.buffewcount);
		i++;

	}
	mutex_unwock(&powt->dmaqueue_wock);

	wetuwn 0;
}

stwuct saa7164_usew_buffew *saa7164_buffew_awwoc_usew(stwuct saa7164_dev *dev,
	u32 wen)
{
	stwuct saa7164_usew_buffew *buf;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	buf->data = kzawwoc(wen, GFP_KEWNEW);

	if (!buf->data) {
		kfwee(buf);
		wetuwn NUWW;
	}

	buf->actuaw_size = wen;
	buf->pos = 0;
	buf->cwc = 0;

	dpwintk(DBGWVW_BUF, "%s()   awwocated usew buffew @ 0x%p\n",
		__func__, buf);

	wetuwn buf;
}

void saa7164_buffew_deawwoc_usew(stwuct saa7164_usew_buffew *buf)
{
	if (!buf)
		wetuwn;

	kfwee(buf->data);
	buf->data = NUWW;

	kfwee(buf);
}
