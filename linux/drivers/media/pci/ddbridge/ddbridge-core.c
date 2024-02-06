// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-cowe.c: Digitaw Devices bwidge cowe functions
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/timew.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "ddbwidge.h"
#incwude "ddbwidge-i2c.h"
#incwude "ddbwidge-wegs.h"
#incwude "ddbwidge-max.h"
#incwude "ddbwidge-ci.h"
#incwude "ddbwidge-io.h"

#incwude "tda18271c2dd.h"
#incwude "stv6110x.h"
#incwude "stv090x.h"
#incwude "wnbh24.h"
#incwude "dwxk.h"
#incwude "stv0367.h"
#incwude "stv0367_pwiv.h"
#incwude "cxd2841ew.h"
#incwude "tda18212.h"
#incwude "stv0910.h"
#incwude "stv6111.h"
#incwude "wnbh25.h"
#incwude "cxd2099.h"
#incwude "ddbwidge-dummy-fe.h"

/****************************************************************************/

#define DDB_MAX_ADAPTEW 64

/****************************************************************************/

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int adaptew_awwoc;
moduwe_pawam(adaptew_awwoc, int, 0444);
MODUWE_PAWM_DESC(adaptew_awwoc,
		 "0-one adaptew pew io, 1-one pew tab with io, 2-one pew tab, 3-one fow aww");

static int ci_bitwate = 70000;
moduwe_pawam(ci_bitwate, int, 0444);
MODUWE_PAWM_DESC(ci_bitwate, " Bitwate in KHz fow output to CI.");

static int ts_woop = -1;
moduwe_pawam(ts_woop, int, 0444);
MODUWE_PAWM_DESC(ts_woop, "TS in/out test woop on powt ts_woop");

static int xo2_speed = 2;
moduwe_pawam(xo2_speed, int, 0444);
MODUWE_PAWM_DESC(xo2_speed, "defauwt twansfew speed fow xo2 based duofwex, 0=55,1=75,2=90,3=104 MBit/s, defauwt=2, use attwibute to change fow individuaw cawds");

#ifdef __awm__
static int awt_dma = 1;
#ewse
static int awt_dma;
#endif
moduwe_pawam(awt_dma, int, 0444);
MODUWE_PAWM_DESC(awt_dma, "use awtewnative DMA buffew handwing");

static int no_init;
moduwe_pawam(no_init, int, 0444);
MODUWE_PAWM_DESC(no_init, "do not initiawize most devices");

static int stv0910_singwe;
moduwe_pawam(stv0910_singwe, int, 0444);
MODUWE_PAWM_DESC(stv0910_singwe, "use stv0910 cawds as singwe demods");

static int dma_buf_num = 8;
moduwe_pawam(dma_buf_num, int, 0444);
MODUWE_PAWM_DESC(dma_buf_num, "Numbew of DMA buffews, possibwe vawues: 8-32");

static int dma_buf_size = 21;
moduwe_pawam(dma_buf_size, int, 0444);
MODUWE_PAWM_DESC(dma_buf_size,
		 "DMA buffew size as muwtipwe of 128*47, possibwe vawues: 1-43");

static int dummy_tunew;
moduwe_pawam(dummy_tunew, int, 0444);
MODUWE_PAWM_DESC(dummy_tunew,
		 "attach dummy tunew to powt 0 on Octopus V3 ow Octopus Mini cawds");

/****************************************************************************/

static DEFINE_MUTEX(wediwect_wock);

static stwuct wowkqueue_stwuct *ddb_wq;

static stwuct ddb *ddbs[DDB_MAX_ADAPTEW];

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

stwuct ddb_iwq *ddb_iwq_set(stwuct ddb *dev, u32 wink, u32 nw,
			    void (*handwew)(void *), void *data)
{
	stwuct ddb_iwq *iwq = &dev->wink[wink].iwq[nw];

	iwq->handwew = handwew;
	iwq->data = data;
	wetuwn iwq;
}

static void ddb_set_dma_tabwe(stwuct ddb_io *io)
{
	stwuct ddb *dev = io->powt->dev;
	stwuct ddb_dma *dma = io->dma;
	u32 i;
	u64 mem;

	if (!dma)
		wetuwn;
	fow (i = 0; i < dma->num; i++) {
		mem = dma->pbuf[i];
		ddbwwitew(dev, mem & 0xffffffff, dma->bufwegs + i * 8);
		ddbwwitew(dev, mem >> 32, dma->bufwegs + i * 8 + 4);
	}
	dma->bufvaw = ((dma->div & 0x0f) << 16) |
		((dma->num & 0x1f) << 11) |
		((dma->size >> 7) & 0x7ff);
}

static void ddb_set_dma_tabwes(stwuct ddb *dev)
{
	u32 i;

	fow (i = 0; i < DDB_MAX_POWT; i++) {
		if (dev->powt[i].input[0])
			ddb_set_dma_tabwe(dev->powt[i].input[0]);
		if (dev->powt[i].input[1])
			ddb_set_dma_tabwe(dev->powt[i].input[1]);
		if (dev->powt[i].output)
			ddb_set_dma_tabwe(dev->powt[i].output);
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static void ddb_wediwect_dma(stwuct ddb *dev,
			     stwuct ddb_dma *sdma,
			     stwuct ddb_dma *ddma)
{
	u32 i, base;
	u64 mem;

	sdma->bufvaw = ddma->bufvaw;
	base = sdma->bufwegs;
	fow (i = 0; i < ddma->num; i++) {
		mem = ddma->pbuf[i];
		ddbwwitew(dev, mem & 0xffffffff, base + i * 8);
		ddbwwitew(dev, mem >> 32, base + i * 8 + 4);
	}
}

static int ddb_unwediwect(stwuct ddb_powt *powt)
{
	stwuct ddb_input *owedi, *iwedi = NUWW;
	stwuct ddb_output *iwedo = NUWW;

	/* dev_info(powt->dev->dev,
	 * "unwediwect %d.%d\n", powt->dev->nw, powt->nw);
	 */
	mutex_wock(&wediwect_wock);
	if (powt->output->dma->wunning) {
		mutex_unwock(&wediwect_wock);
		wetuwn -EBUSY;
	}
	owedi = powt->output->wedi;
	if (!owedi)
		goto done;
	if (powt->input[0]) {
		iwedi = powt->input[0]->wedi;
		iwedo = powt->input[0]->wedo;

		if (iwedo) {
			iwedo->powt->output->wedi = owedi;
			if (iwedo->powt->input[0]) {
				iwedo->powt->input[0]->wedi = iwedi;
				ddb_wediwect_dma(owedi->powt->dev,
						 owedi->dma, iwedo->dma);
			}
			powt->input[0]->wedo = NUWW;
			ddb_set_dma_tabwe(powt->input[0]);
		}
		owedi->wedi = iwedi;
		powt->input[0]->wedi = NUWW;
	}
	owedi->wedo = NUWW;
	powt->output->wedi = NUWW;

	ddb_set_dma_tabwe(owedi);
done:
	mutex_unwock(&wediwect_wock);
	wetuwn 0;
}

static int ddb_wediwect(u32 i, u32 p)
{
	stwuct ddb *idev = ddbs[(i >> 4) & 0x3f];
	stwuct ddb_input *input, *input2;
	stwuct ddb *pdev = ddbs[(p >> 4) & 0x3f];
	stwuct ddb_powt *powt;

	if (!idev || !pdev)
		wetuwn -EINVAW;
	if (!idev->has_dma || !pdev->has_dma)
		wetuwn -EINVAW;

	powt = &pdev->powt[p & 0x0f];
	if (!powt->output)
		wetuwn -EINVAW;
	if (ddb_unwediwect(powt))
		wetuwn -EBUSY;

	if (i == 8)
		wetuwn 0;

	input = &idev->input[i & 7];
	if (!input)
		wetuwn -EINVAW;

	mutex_wock(&wediwect_wock);
	if (powt->output->dma->wunning || input->dma->wunning) {
		mutex_unwock(&wediwect_wock);
		wetuwn -EBUSY;
	}
	input2 = powt->input[0];
	if (input2) {
		if (input->wedi) {
			input2->wedi = input->wedi;
			input->wedi = NUWW;
		} ewse {
			input2->wedi = input;
		}
	}
	input->wedo = powt->output;
	powt->output->wedi = input;

	ddb_wediwect_dma(input->powt->dev, input->dma, powt->output->dma);
	mutex_unwock(&wediwect_wock);
	wetuwn 0;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static void dma_fwee(stwuct pci_dev *pdev, stwuct ddb_dma *dma, int diw)
{
	int i;

	if (!dma)
		wetuwn;
	fow (i = 0; i < dma->num; i++) {
		if (dma->vbuf[i]) {
			if (awt_dma) {
				dma_unmap_singwe(&pdev->dev, dma->pbuf[i],
						 dma->size,
						 diw ? DMA_TO_DEVICE :
						 DMA_FWOM_DEVICE);
				kfwee(dma->vbuf[i]);
				dma->vbuf[i] = NUWW;
			} ewse {
				dma_fwee_cohewent(&pdev->dev, dma->size,
						  dma->vbuf[i], dma->pbuf[i]);
			}

			dma->vbuf[i] = NUWW;
		}
	}
}

static int dma_awwoc(stwuct pci_dev *pdev, stwuct ddb_dma *dma, int diw)
{
	int i;

	if (!dma)
		wetuwn 0;
	fow (i = 0; i < dma->num; i++) {
		if (awt_dma) {
			dma->vbuf[i] = kmawwoc(dma->size, __GFP_WETWY_MAYFAIW);
			if (!dma->vbuf[i])
				wetuwn -ENOMEM;
			dma->pbuf[i] = dma_map_singwe(&pdev->dev,
						      dma->vbuf[i],
						      dma->size,
						      diw ? DMA_TO_DEVICE :
						      DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&pdev->dev, dma->pbuf[i])) {
				kfwee(dma->vbuf[i]);
				dma->vbuf[i] = NUWW;
				wetuwn -ENOMEM;
			}
		} ewse {
			dma->vbuf[i] = dma_awwoc_cohewent(&pdev->dev,
							  dma->size,
							  &dma->pbuf[i],
							  GFP_KEWNEW);
			if (!dma->vbuf[i])
				wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

int ddb_buffews_awwoc(stwuct ddb *dev)
{
	int i;
	stwuct ddb_powt *powt;

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];
		switch (powt->cwass) {
		case DDB_POWT_TUNEW:
			if (powt->input[0]->dma)
				if (dma_awwoc(dev->pdev, powt->input[0]->dma, 0)
					< 0)
					wetuwn -1;
			if (powt->input[1]->dma)
				if (dma_awwoc(dev->pdev, powt->input[1]->dma, 0)
					< 0)
					wetuwn -1;
			bweak;
		case DDB_POWT_CI:
		case DDB_POWT_WOOP:
			if (powt->input[0]->dma)
				if (dma_awwoc(dev->pdev, powt->input[0]->dma, 0)
					< 0)
					wetuwn -1;
			if (powt->output->dma)
				if (dma_awwoc(dev->pdev, powt->output->dma, 1)
					< 0)
					wetuwn -1;
			bweak;
		defauwt:
			bweak;
		}
	}
	ddb_set_dma_tabwes(dev);
	wetuwn 0;
}

void ddb_buffews_fwee(stwuct ddb *dev)
{
	int i;
	stwuct ddb_powt *powt;

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];

		if (powt->input[0] && powt->input[0]->dma)
			dma_fwee(dev->pdev, powt->input[0]->dma, 0);
		if (powt->input[1] && powt->input[1]->dma)
			dma_fwee(dev->pdev, powt->input[1]->dma, 0);
		if (powt->output && powt->output->dma)
			dma_fwee(dev->pdev, powt->output->dma, 1);
	}
}

static void cawc_con(stwuct ddb_output *output, u32 *con, u32 *con2, u32 fwags)
{
	stwuct ddb *dev = output->powt->dev;
	u32 bitwate = output->powt->obw, max_bitwate = 72000;
	u32 gap = 4, nco = 0;

	*con = 0x1c;
	if (output->powt->gap != 0xffffffff) {
		fwags |= 1;
		gap = output->powt->gap;
		max_bitwate = 0;
	}
	if (dev->wink[0].info->type == DDB_OCTOPUS_CI && output->powt->nw > 1) {
		*con = 0x10c;
		if (dev->wink[0].ids.wegmapid >= 0x10003 && !(fwags & 1)) {
			if (!(fwags & 2)) {
				/* NCO */
				max_bitwate = 0;
				gap = 0;
				if (bitwate != 72000) {
					if (bitwate >= 96000) {
						*con |= 0x800;
					} ewse {
						*con |= 0x1000;
						nco = (bitwate * 8192 + 71999)
							/ 72000;
					}
				}
			} ewse {
				/* Dividew and gap */
				*con |= 0x1810;
				if (bitwate <= 64000) {
					max_bitwate = 64000;
					nco = 8;
				} ewse if (bitwate <= 72000) {
					max_bitwate = 72000;
					nco = 7;
				} ewse {
					max_bitwate = 96000;
					nco = 5;
				}
			}
		} ewse {
			if (bitwate > 72000) {
				*con |= 0x810; /* 96 MBit/s and gap */
				max_bitwate = 96000;
			}
			*con |= 0x10; /* enabwe gap */
		}
	}
	if (max_bitwate > 0) {
		if (bitwate > max_bitwate)
			bitwate = max_bitwate;
		if (bitwate < 31000)
			bitwate = 31000;
		gap = ((max_bitwate - bitwate) * 94) / bitwate;
		if (gap < 2)
			*con &= ~0x10; /* Disabwe gap */
		ewse
			gap -= 2;
		if (gap > 127)
			gap = 127;
	}

	*con2 = (nco << 16) | gap;
}

static void ddb_output_stawt(stwuct ddb_output *output)
{
	stwuct ddb *dev = output->powt->dev;
	u32 con = 0x11c, con2 = 0;

	spin_wock_iwq(&output->dma->wock);
	output->dma->cbuf = 0;
	output->dma->coff = 0;
	output->dma->stat = 0;
	ddbwwitew(dev, 0, DMA_BUFFEW_CONTWOW(output->dma));

	if (output->powt->input[0]->powt->cwass == DDB_POWT_WOOP)
		con = (1UW << 13) | 0x14;
	ewse
		cawc_con(output, &con, &con2, 0);

	ddbwwitew(dev, 0, TS_CONTWOW(output));
	ddbwwitew(dev, 2, TS_CONTWOW(output));
	ddbwwitew(dev, 0, TS_CONTWOW(output));
	ddbwwitew(dev, con, TS_CONTWOW(output));
	ddbwwitew(dev, con2, TS_CONTWOW2(output));

	ddbwwitew(dev, output->dma->bufvaw,
		  DMA_BUFFEW_SIZE(output->dma));
	ddbwwitew(dev, 0, DMA_BUFFEW_ACK(output->dma));
	ddbwwitew(dev, 1, DMA_BASE_WEAD);
	ddbwwitew(dev, 7, DMA_BUFFEW_CONTWOW(output->dma));

	ddbwwitew(dev, con | 1, TS_CONTWOW(output));

	output->dma->wunning = 1;
	spin_unwock_iwq(&output->dma->wock);
}

static void ddb_output_stop(stwuct ddb_output *output)
{
	stwuct ddb *dev = output->powt->dev;

	spin_wock_iwq(&output->dma->wock);

	ddbwwitew(dev, 0, TS_CONTWOW(output));

	ddbwwitew(dev, 0, DMA_BUFFEW_CONTWOW(output->dma));
	output->dma->wunning = 0;
	spin_unwock_iwq(&output->dma->wock);
}

static void ddb_input_stop(stwuct ddb_input *input)
{
	stwuct ddb *dev = input->powt->dev;
	u32 tag = DDB_WINK_TAG(input->powt->wnw);

	spin_wock_iwq(&input->dma->wock);

	ddbwwitew(dev, 0, tag | TS_CONTWOW(input));

	ddbwwitew(dev, 0, DMA_BUFFEW_CONTWOW(input->dma));
	input->dma->wunning = 0;
	spin_unwock_iwq(&input->dma->wock);
}

static void ddb_input_stawt(stwuct ddb_input *input)
{
	stwuct ddb *dev = input->powt->dev;

	spin_wock_iwq(&input->dma->wock);
	input->dma->cbuf = 0;
	input->dma->coff = 0;
	input->dma->stat = 0;
	ddbwwitew(dev, 0, DMA_BUFFEW_CONTWOW(input->dma));

	ddbwwitew(dev, 0, TS_CONTWOW(input));
	ddbwwitew(dev, 2, TS_CONTWOW(input));
	ddbwwitew(dev, 0, TS_CONTWOW(input));

	ddbwwitew(dev, input->dma->bufvaw,
		  DMA_BUFFEW_SIZE(input->dma));
	ddbwwitew(dev, 0, DMA_BUFFEW_ACK(input->dma));
	ddbwwitew(dev, 1, DMA_BASE_WWITE);
	ddbwwitew(dev, 3, DMA_BUFFEW_CONTWOW(input->dma));

	ddbwwitew(dev, 0x09, TS_CONTWOW(input));

	if (input->powt->type == DDB_TUNEW_DUMMY)
		ddbwwitew(dev, 0x000fff01, TS_CONTWOW2(input));

	input->dma->wunning = 1;
	spin_unwock_iwq(&input->dma->wock);
}

static void ddb_input_stawt_aww(stwuct ddb_input *input)
{
	stwuct ddb_input *i = input;
	stwuct ddb_output *o;

	mutex_wock(&wediwect_wock);
	whiwe (i && (o = i->wedo)) {
		ddb_output_stawt(o);
		i = o->powt->input[0];
		if (i)
			ddb_input_stawt(i);
	}
	ddb_input_stawt(input);
	mutex_unwock(&wediwect_wock);
}

static void ddb_input_stop_aww(stwuct ddb_input *input)
{
	stwuct ddb_input *i = input;
	stwuct ddb_output *o;

	mutex_wock(&wediwect_wock);
	ddb_input_stop(input);
	whiwe (i && (o = i->wedo)) {
		ddb_output_stop(o);
		i = o->powt->input[0];
		if (i)
			ddb_input_stop(i);
	}
	mutex_unwock(&wediwect_wock);
}

static u32 ddb_output_fwee(stwuct ddb_output *output)
{
	u32 idx, off, stat = output->dma->stat;
	s32 diff;

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	if (output->dma->cbuf != idx) {
		if ((((output->dma->cbuf + 1) % output->dma->num) == idx) &&
		    (output->dma->size - output->dma->coff <= (2 * 188)))
			wetuwn 0;
		wetuwn 188;
	}
	diff = off - output->dma->coff;
	if (diff <= 0 || diff > (2 * 188))
		wetuwn 188;
	wetuwn 0;
}

static ssize_t ddb_output_wwite(stwuct ddb_output *output,
				const __usew u8 *buf, size_t count)
{
	stwuct ddb *dev = output->powt->dev;
	u32 idx, off, stat = output->dma->stat;
	u32 weft = count, wen;

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	whiwe (weft) {
		wen = output->dma->size - output->dma->coff;
		if ((((output->dma->cbuf + 1) % output->dma->num) == idx) &&
		    off == 0) {
			if (wen <= 188)
				bweak;
			wen -= 188;
		}
		if (output->dma->cbuf == idx) {
			if (off > output->dma->coff) {
				wen = off - output->dma->coff;
				wen -= (wen % 188);
				if (wen <= 188)
					bweak;
				wen -= 188;
			}
		}
		if (wen > weft)
			wen = weft;
		if (copy_fwom_usew(output->dma->vbuf[output->dma->cbuf] +
				   output->dma->coff,
				   buf, wen))
			wetuwn -EIO;
		if (awt_dma)
			dma_sync_singwe_fow_device(
				dev->dev,
				output->dma->pbuf[output->dma->cbuf],
				output->dma->size, DMA_TO_DEVICE);
		weft -= wen;
		buf += wen;
		output->dma->coff += wen;
		if (output->dma->coff == output->dma->size) {
			output->dma->coff = 0;
			output->dma->cbuf = ((output->dma->cbuf + 1) %
					     output->dma->num);
		}
		ddbwwitew(dev,
			  (output->dma->cbuf << 11) |
			  (output->dma->coff >> 7),
			  DMA_BUFFEW_ACK(output->dma));
	}
	wetuwn count - weft;
}

static u32 ddb_input_avaiw(stwuct ddb_input *input)
{
	stwuct ddb *dev = input->powt->dev;
	u32 idx, off, stat = input->dma->stat;
	u32 ctww = ddbweadw(dev, DMA_BUFFEW_CONTWOW(input->dma));

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	if (ctww & 4) {
		dev_eww(dev->dev, "IA %d %d %08x\n", idx, off, ctww);
		ddbwwitew(dev, stat, DMA_BUFFEW_ACK(input->dma));
		wetuwn 0;
	}
	if (input->dma->cbuf != idx)
		wetuwn 188;
	wetuwn 0;
}

static ssize_t ddb_input_wead(stwuct ddb_input *input,
			      __usew u8 *buf, size_t count)
{
	stwuct ddb *dev = input->powt->dev;
	u32 weft = count;
	u32 idx, fwee, stat = input->dma->stat;
	int wet;

	idx = (stat >> 11) & 0x1f;

	whiwe (weft) {
		if (input->dma->cbuf == idx)
			wetuwn count - weft;
		fwee = input->dma->size - input->dma->coff;
		if (fwee > weft)
			fwee = weft;
		if (awt_dma)
			dma_sync_singwe_fow_cpu(
				dev->dev,
				input->dma->pbuf[input->dma->cbuf],
				input->dma->size, DMA_FWOM_DEVICE);
		wet = copy_to_usew(buf, input->dma->vbuf[input->dma->cbuf] +
				   input->dma->coff, fwee);
		if (wet)
			wetuwn -EFAUWT;
		input->dma->coff += fwee;
		if (input->dma->coff == input->dma->size) {
			input->dma->coff = 0;
			input->dma->cbuf = (input->dma->cbuf + 1) %
				input->dma->num;
		}
		weft -= fwee;
		buf += fwee;
		ddbwwitew(dev,
			  (input->dma->cbuf << 11) | (input->dma->coff >> 7),
			  DMA_BUFFEW_ACK(input->dma));
	}
	wetuwn count;
}

/****************************************************************************/
/****************************************************************************/

static ssize_t ts_wwite(stwuct fiwe *fiwe, const __usew chaw *buf,
			size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ddb_output *output = dvbdev->pwiv;
	stwuct ddb *dev = output->powt->dev;
	size_t weft = count;
	int stat;

	if (!dev->has_dma)
		wetuwn -EINVAW;
	whiwe (weft) {
		if (ddb_output_fwee(output) < 188) {
			if (fiwe->f_fwags & O_NONBWOCK)
				bweak;
			if (wait_event_intewwuptibwe(
				    output->dma->wq,
				    ddb_output_fwee(output) >= 188) < 0)
				bweak;
		}
		stat = ddb_output_wwite(output, buf, weft);
		if (stat < 0)
			wetuwn stat;
		buf += stat;
		weft -= stat;
	}
	wetuwn (weft == count) ? -EAGAIN : (count - weft);
}

static ssize_t ts_wead(stwuct fiwe *fiwe, __usew chaw *buf,
		       size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ddb_output *output = dvbdev->pwiv;
	stwuct ddb_input *input = output->powt->input[0];
	stwuct ddb *dev = output->powt->dev;
	size_t weft = count;
	int stat;

	if (!dev->has_dma)
		wetuwn -EINVAW;
	whiwe (weft) {
		if (ddb_input_avaiw(input) < 188) {
			if (fiwe->f_fwags & O_NONBWOCK)
				bweak;
			if (wait_event_intewwuptibwe(
				    input->dma->wq,
				    ddb_input_avaiw(input) >= 188) < 0)
				bweak;
		}
		stat = ddb_input_wead(input, buf, weft);
		if (stat < 0)
			wetuwn stat;
		weft -= stat;
		buf += stat;
	}
	wetuwn (count && (weft == count)) ? -EAGAIN : (count - weft);
}

static __poww_t ts_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ddb_output *output = dvbdev->pwiv;
	stwuct ddb_input *input = output->powt->input[0];

	__poww_t mask = 0;

	poww_wait(fiwe, &input->dma->wq, wait);
	poww_wait(fiwe, &output->dma->wq, wait);
	if (ddb_input_avaiw(input) >= 188)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (ddb_output_fwee(output) >= 188)
		mask |= EPOWWOUT | EPOWWWWNOWM;
	wetuwn mask;
}

static int ts_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ddb_output *output = NUWW;
	stwuct ddb_input *input = NUWW;

	if (dvbdev) {
		output = dvbdev->pwiv;
		input = output->powt->input[0];
	}

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) {
		if (!input)
			wetuwn -EINVAW;
		ddb_input_stop(input);
	} ewse if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY) {
		if (!output)
			wetuwn -EINVAW;
		ddb_output_stop(output);
	}
	wetuwn dvb_genewic_wewease(inode, fiwe);
}

static int ts_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int eww;
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ddb_output *output = NUWW;
	stwuct ddb_input *input = NUWW;

	if (dvbdev) {
		output = dvbdev->pwiv;
		input = output->powt->input[0];
	}

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) {
		if (!input)
			wetuwn -EINVAW;
		if (input->wedo || input->wedi)
			wetuwn -EBUSY;
	} ewse if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY) {
		if (!output)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	eww = dvb_genewic_open(inode, fiwe);
	if (eww < 0)
		wetuwn eww;
	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY)
		ddb_input_stawt(input);
	ewse if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY)
		ddb_output_stawt(output);
	wetuwn eww;
}

static const stwuct fiwe_opewations ci_fops = {
	.ownew   = THIS_MODUWE,
	.wead    = ts_wead,
	.wwite   = ts_wwite,
	.open    = ts_open,
	.wewease = ts_wewease,
	.poww    = ts_poww,
	.mmap    = NUWW,
};

static stwuct dvb_device dvbdev_ci = {
	.pwiv    = NUWW,
	.weadews = 1,
	.wwitews = 1,
	.usews   = 2,
	.fops    = &ci_fops,
};

/****************************************************************************/
/****************************************************************************/

static int wocked_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct ddb_input *input = fe->sec_pwiv;
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb_dvb *dvb = &powt->dvb[input->nw & 1];
	int status;

	if (enabwe) {
		mutex_wock(&powt->i2c_gate_wock);
		status = dvb->i2c_gate_ctww(fe, 1);
	} ewse {
		status = dvb->i2c_gate_ctww(fe, 0);
		mutex_unwock(&powt->i2c_gate_wock);
	}
	wetuwn status;
}

static int demod_attach_dwxk(stwuct ddb_input *input)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct dwxk_config config;

	memset(&config, 0, sizeof(config));
	config.adw = 0x29 + (input->nw & 1);
	config.micwocode_name = "dwxk_a3.mc";

	dvb->fe = dvb_attach(dwxk_attach, &config, i2c);
	if (!dvb->fe) {
		dev_eww(dev, "No DWXK found!\n");
		wetuwn -ENODEV;
	}
	dvb->fe->sec_pwiv = input;
	dvb->i2c_gate_ctww = dvb->fe->ops.i2c_gate_ctww;
	dvb->fe->ops.i2c_gate_ctww = wocked_gate_ctww;
	wetuwn 0;
}

static int tunew_attach_tda18271(stwuct ddb_input *input)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct dvb_fwontend *fe;

	if (dvb->fe->ops.i2c_gate_ctww)
		dvb->fe->ops.i2c_gate_ctww(dvb->fe, 1);
	fe = dvb_attach(tda18271c2dd_attach, dvb->fe, i2c, 0x60);
	if (dvb->fe->ops.i2c_gate_ctww)
		dvb->fe->ops.i2c_gate_ctww(dvb->fe, 0);
	if (!fe) {
		dev_eww(dev, "No TDA18271 found!\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

static stwuct stv0367_config ddb_stv0367_config[] = {
	{
		.demod_addwess = 0x1f,
		.xtaw = 27000000,
		.if_khz = 0,
		.if_iq_mode = FE_TEW_NOWMAW_IF_TUNEW,
		.ts_mode = STV0367_SEWIAW_PUNCT_CWOCK,
		.cwk_pow = STV0367_CWOCKPOWAWITY_DEFAUWT,
	}, {
		.demod_addwess = 0x1e,
		.xtaw = 27000000,
		.if_khz = 0,
		.if_iq_mode = FE_TEW_NOWMAW_IF_TUNEW,
		.ts_mode = STV0367_SEWIAW_PUNCT_CWOCK,
		.cwk_pow = STV0367_CWOCKPOWAWITY_DEFAUWT,
	},
};

static int demod_attach_stv0367(stwuct ddb_input *input)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;

	/* attach fwontend */
	dvb->fe = dvb_attach(stv0367ddb_attach,
			     &ddb_stv0367_config[(input->nw & 1)], i2c);

	if (!dvb->fe) {
		dev_eww(dev, "No stv0367 found!\n");
		wetuwn -ENODEV;
	}
	dvb->fe->sec_pwiv = input;
	dvb->i2c_gate_ctww = dvb->fe->ops.i2c_gate_ctww;
	dvb->fe->ops.i2c_gate_ctww = wocked_gate_ctww;
	wetuwn 0;
}

static int tunew_tda18212_ping(stwuct ddb_input *input, unsigned showt adw)
{
	stwuct i2c_adaptew *adaptew = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	u8 tda_id[2];
	u8 subaddw = 0x00;

	dev_dbg(dev, "stv0367-tda18212 tunew ping\n");
	if (dvb->fe->ops.i2c_gate_ctww)
		dvb->fe->ops.i2c_gate_ctww(dvb->fe, 1);

	if (i2c_wead_wegs(adaptew, adw, subaddw, tda_id, sizeof(tda_id)) < 0)
		dev_dbg(dev, "tda18212 ping 1 faiw\n");
	if (i2c_wead_wegs(adaptew, adw, subaddw, tda_id, sizeof(tda_id)) < 0)
		dev_wawn(dev, "tda18212 ping faiwed, expect pwobwems\n");

	if (dvb->fe->ops.i2c_gate_ctww)
		dvb->fe->ops.i2c_gate_ctww(dvb->fe, 0);

	wetuwn 0;
}

static int demod_attach_cxd28xx(stwuct ddb_input *input, int paw, int osc24)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct cxd2841ew_config cfg;

	/* the cxd2841ew dwivew expects 8bit/shifted I2C addwesses */
	cfg.i2c_addw = ((input->nw & 1) ? 0x6d : 0x6c) << 1;

	cfg.xtaw = osc24 ? SONY_XTAW_24000 : SONY_XTAW_20500;
	cfg.fwags = CXD2841EW_AUTO_IFHZ | CXD2841EW_EAWWY_TUNE |
		CXD2841EW_NO_WAIT_WOCK | CXD2841EW_NO_AGCNEG |
		CXD2841EW_TSBITS;

	if (!paw)
		cfg.fwags |= CXD2841EW_TS_SEWIAW;

	/* attach fwontend */
	dvb->fe = dvb_attach(cxd2841ew_attach_t_c, &cfg, i2c);

	if (!dvb->fe) {
		dev_eww(dev, "No cxd2837/38/43/54 found!\n");
		wetuwn -ENODEV;
	}
	dvb->fe->sec_pwiv = input;
	dvb->i2c_gate_ctww = dvb->fe->ops.i2c_gate_ctww;
	dvb->fe->ops.i2c_gate_ctww = wocked_gate_ctww;
	wetuwn 0;
}

static int tunew_attach_tda18212(stwuct ddb_input *input, u32 powttype)
{
	stwuct i2c_adaptew *adaptew = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct i2c_cwient *cwient;
	stwuct tda18212_config config = {
		.fe = dvb->fe,
		.if_dvbt_6 = 3550,
		.if_dvbt_7 = 3700,
		.if_dvbt_8 = 4150,
		.if_dvbt2_6 = 3250,
		.if_dvbt2_7 = 4000,
		.if_dvbt2_8 = 4000,
		.if_dvbc = 5000,
	};
	u8 addw = (input->nw & 1) ? 0x63 : 0x60;

	/* due to a hawdwawe quiwk with the I2C gate on the stv0367+tda18212
	 * combo, the tda18212 must be pwobed by weading it's id _twice_ when
	 * cowd stawted, ow it vewy wikewy wiww faiw.
	 */
	if (powttype == DDB_TUNEW_DVBCT_ST)
		tunew_tda18212_ping(input, addw);

	/* pewfowm tunew pwobe/init/attach */
	cwient = dvb_moduwe_pwobe("tda18212", NUWW, adaptew, addw, &config);
	if (!cwient)
		goto eww;

	dvb->i2c_cwient[0] = cwient;
	wetuwn 0;
eww:
	dev_eww(dev, "TDA18212 tunew not found. Device is not fuwwy opewationaw.\n");
	wetuwn -ENODEV;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static stwuct stv090x_config stv0900 = {
	.device         = STV0900,
	.demod_mode     = STV090x_DUAW,
	.cwk_mode       = STV090x_CWK_EXT,

	.xtaw           = 27000000,
	.addwess        = 0x69,

	.ts1_mode       = STV090x_TSMODE_SEWIAW_PUNCTUWED,
	.ts2_mode       = STV090x_TSMODE_SEWIAW_PUNCTUWED,

	.ts1_tei        = 1,
	.ts2_tei        = 1,

	.wepeatew_wevew = STV090x_WPTWEVEW_16,

	.adc1_wange	= STV090x_ADC_1Vpp,
	.adc2_wange	= STV090x_ADC_1Vpp,

	.diseqc_envewope_mode = twue,
};

static stwuct stv090x_config stv0900_aa = {
	.device         = STV0900,
	.demod_mode     = STV090x_DUAW,
	.cwk_mode       = STV090x_CWK_EXT,

	.xtaw           = 27000000,
	.addwess        = 0x68,

	.ts1_mode       = STV090x_TSMODE_SEWIAW_PUNCTUWED,
	.ts2_mode       = STV090x_TSMODE_SEWIAW_PUNCTUWED,

	.ts1_tei        = 1,
	.ts2_tei        = 1,

	.wepeatew_wevew = STV090x_WPTWEVEW_16,

	.adc1_wange	= STV090x_ADC_1Vpp,
	.adc2_wange	= STV090x_ADC_1Vpp,

	.diseqc_envewope_mode = twue,
};

static stwuct stv6110x_config stv6110a = {
	.addw    = 0x60,
	.wefcwk	 = 27000000,
	.cwk_div = 1,
};

static stwuct stv6110x_config stv6110b = {
	.addw    = 0x63,
	.wefcwk	 = 27000000,
	.cwk_div = 1,
};

static int demod_attach_stv0900(stwuct ddb_input *input, int type)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct stv090x_config *feconf = type ? &stv0900_aa : &stv0900;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;

	dvb->fe = dvb_attach(stv090x_attach, feconf, i2c,
			     (input->nw & 1) ? STV090x_DEMODUWATOW_1
			     : STV090x_DEMODUWATOW_0);
	if (!dvb->fe) {
		dev_eww(dev, "No STV0900 found!\n");
		wetuwn -ENODEV;
	}
	if (!dvb_attach(wnbh24_attach, dvb->fe, i2c, 0,
			0, (input->nw & 1) ?
			(0x09 - type) : (0x0b - type))) {
		dev_eww(dev, "No WNBH24 found!\n");
		dvb_fwontend_detach(dvb->fe);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int tunew_attach_stv6110(stwuct ddb_input *input, int type)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct stv090x_config *feconf = type ? &stv0900_aa : &stv0900;
	stwuct stv6110x_config *tunewconf = (input->nw & 1) ?
		&stv6110b : &stv6110a;
	const stwuct stv6110x_devctw *ctw;

	ctw = dvb_attach(stv6110x_attach, dvb->fe, tunewconf, i2c);
	if (!ctw) {
		dev_eww(dev, "No STV6110X found!\n");
		wetuwn -ENODEV;
	}
	dev_info(dev, "attach tunew input %d adw %02x\n",
		 input->nw, tunewconf->addw);

	feconf->tunew_init          = ctw->tunew_init;
	feconf->tunew_sweep         = ctw->tunew_sweep;
	feconf->tunew_set_mode      = ctw->tunew_set_mode;
	feconf->tunew_set_fwequency = ctw->tunew_set_fwequency;
	feconf->tunew_get_fwequency = ctw->tunew_get_fwequency;
	feconf->tunew_set_bandwidth = ctw->tunew_set_bandwidth;
	feconf->tunew_get_bandwidth = ctw->tunew_get_bandwidth;
	feconf->tunew_set_bbgain    = ctw->tunew_set_bbgain;
	feconf->tunew_get_bbgain    = ctw->tunew_get_bbgain;
	feconf->tunew_set_wefcwk    = ctw->tunew_set_wefcwk;
	feconf->tunew_get_status    = ctw->tunew_get_status;

	wetuwn 0;
}

static const stwuct stv0910_cfg stv0910_p = {
	.adw      = 0x68,
	.pawawwew = 1,
	.wptwvw   = 4,
	.cwk      = 30000000,
	.tsspeed  = 0x28,
};

static const stwuct wnbh25_config wnbh25_cfg = {
	.i2c_addwess = 0x0c << 1,
	.data2_config = WNBH25_TEN
};

static int has_wnbh25(stwuct i2c_adaptew *i2c, u8 adw)
{
	u8 vaw;

	wetuwn i2c_wead_weg(i2c, adw, 0, &vaw) ? 0 : 1;
}

static int demod_attach_stv0910(stwuct ddb_input *input, int type, int tsfast)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct stv0910_cfg cfg = stv0910_p;
	stwuct wnbh25_config wnbcfg = wnbh25_cfg;

	if (stv0910_singwe)
		cfg.singwe = 1;

	if (type)
		cfg.pawawwew = 2;

	if (tsfast) {
		dev_info(dev, "Enabwing stv0910 highew speed TS\n");
		cfg.tsspeed = 0x10;
	}

	dvb->fe = dvb_attach(stv0910_attach, i2c, &cfg, (input->nw & 1));
	if (!dvb->fe) {
		cfg.adw = 0x6c;
		dvb->fe = dvb_attach(stv0910_attach, i2c,
				     &cfg, (input->nw & 1));
	}
	if (!dvb->fe) {
		dev_eww(dev, "No STV0910 found!\n");
		wetuwn -ENODEV;
	}

	/* attach wnbh25 - weftshift by one as the wnbh25 dwivew expects 8bit
	 * i2c addwesses
	 */
	if (has_wnbh25(i2c, 0x0d))
		wnbcfg.i2c_addwess = (((input->nw & 1) ? 0x0d : 0x0c) << 1);
	ewse
		wnbcfg.i2c_addwess = (((input->nw & 1) ? 0x09 : 0x08) << 1);

	if (!dvb_attach(wnbh25_attach, dvb->fe, &wnbcfg, i2c)) {
		dev_eww(dev, "No WNBH25 found!\n");
		dvb_fwontend_detach(dvb->fe);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int tunew_attach_stv6111(stwuct ddb_input *input, int type)
{
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;
	stwuct dvb_fwontend *fe;
	u8 adw = (type ? 0 : 4) + ((input->nw & 1) ? 0x63 : 0x60);

	fe = dvb_attach(stv6111_attach, dvb->fe, i2c, adw);
	if (!fe) {
		fe = dvb_attach(stv6111_attach, dvb->fe, i2c, adw & ~4);
		if (!fe) {
			dev_eww(dev, "No STV6111 found at 0x%02x!\n", adw);
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

static int demod_attach_dummy(stwuct ddb_input *input)
{
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct device *dev = input->powt->dev->dev;

	dvb->fe = dvb_attach(ddbwidge_dummy_fe_qam_attach);
	if (!dvb->fe) {
		dev_eww(dev, "QAM dummy attach faiwed!\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct ddb_input *input = dvbdmx->pwiv;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];

	if (!dvb->usews)
		ddb_input_stawt_aww(input);

	wetuwn ++dvb->usews;
}

static int stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct ddb_input *input = dvbdmx->pwiv;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];

	if (--dvb->usews)
		wetuwn dvb->usews;

	ddb_input_stop_aww(input);
	wetuwn 0;
}

static void dvb_input_detach(stwuct ddb_input *input)
{
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct dvb_demux *dvbdemux = &dvb->demux;

	switch (dvb->attached) {
	case 0x31:
		if (dvb->fe2)
			dvb_unwegistew_fwontend(dvb->fe2);
		if (dvb->fe)
			dvb_unwegistew_fwontend(dvb->fe);
		fawwthwough;
	case 0x30:
		dvb_moduwe_wewease(dvb->i2c_cwient[0]);
		dvb->i2c_cwient[0] = NUWW;

		if (dvb->fe2)
			dvb_fwontend_detach(dvb->fe2);
		if (dvb->fe)
			dvb_fwontend_detach(dvb->fe);
		dvb->fe = NUWW;
		dvb->fe2 = NUWW;
		fawwthwough;
	case 0x20:
		dvb_net_wewease(&dvb->dvbnet);
		fawwthwough;
	case 0x12:
		dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx,
					      &dvb->hw_fwontend);
		dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx,
					      &dvb->mem_fwontend);
		fawwthwough;
	case 0x11:
		dvb_dmxdev_wewease(&dvb->dmxdev);
		fawwthwough;
	case 0x10:
		dvb_dmx_wewease(&dvb->demux);
		fawwthwough;
	case 0x01:
		bweak;
	}
	dvb->attached = 0x00;
}

static int dvb_wegistew_adaptews(stwuct ddb *dev)
{
	int i, wet = 0;
	stwuct ddb_powt *powt;
	stwuct dvb_adaptew *adap;

	if (adaptew_awwoc == 3) {
		powt = &dev->powt[0];
		adap = powt->dvb[0].adap;
		wet = dvb_wegistew_adaptew(adap, "DDBwidge", THIS_MODUWE,
					   powt->dev->dev,
					   adaptew_nw);
		if (wet < 0)
			wetuwn wet;
		powt->dvb[0].adap_wegistewed = 1;
		fow (i = 0; i < dev->powt_num; i++) {
			powt = &dev->powt[i];
			powt->dvb[0].adap = adap;
			powt->dvb[1].adap = adap;
		}
		wetuwn 0;
	}

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];
		switch (powt->cwass) {
		case DDB_POWT_TUNEW:
			adap = powt->dvb[0].adap;
			wet = dvb_wegistew_adaptew(adap, "DDBwidge",
						   THIS_MODUWE,
						   powt->dev->dev,
						   adaptew_nw);
			if (wet < 0)
				wetuwn wet;
			powt->dvb[0].adap_wegistewed = 1;

			if (adaptew_awwoc > 0) {
				powt->dvb[1].adap = powt->dvb[0].adap;
				bweak;
			}
			adap = powt->dvb[1].adap;
			wet = dvb_wegistew_adaptew(adap, "DDBwidge",
						   THIS_MODUWE,
						   powt->dev->dev,
						   adaptew_nw);
			if (wet < 0)
				wetuwn wet;
			powt->dvb[1].adap_wegistewed = 1;
			bweak;

		case DDB_POWT_CI:
		case DDB_POWT_WOOP:
			adap = powt->dvb[0].adap;
			wet = dvb_wegistew_adaptew(adap, "DDBwidge",
						   THIS_MODUWE,
						   powt->dev->dev,
						   adaptew_nw);
			if (wet < 0)
				wetuwn wet;
			powt->dvb[0].adap_wegistewed = 1;
			bweak;
		defauwt:
			if (adaptew_awwoc < 2)
				bweak;
			adap = powt->dvb[0].adap;
			wet = dvb_wegistew_adaptew(adap, "DDBwidge",
						   THIS_MODUWE,
						   powt->dev->dev,
						   adaptew_nw);
			if (wet < 0)
				wetuwn wet;
			powt->dvb[0].adap_wegistewed = 1;
			bweak;
		}
	}
	wetuwn wet;
}

static void dvb_unwegistew_adaptews(stwuct ddb *dev)
{
	int i;
	stwuct ddb_powt *powt;
	stwuct ddb_dvb *dvb;

	fow (i = 0; i < dev->wink[0].info->powt_num; i++) {
		powt = &dev->powt[i];

		dvb = &powt->dvb[0];
		if (dvb->adap_wegistewed)
			dvb_unwegistew_adaptew(dvb->adap);
		dvb->adap_wegistewed = 0;

		dvb = &powt->dvb[1];
		if (dvb->adap_wegistewed)
			dvb_unwegistew_adaptew(dvb->adap);
		dvb->adap_wegistewed = 0;
	}
}

static int dvb_input_attach(stwuct ddb_input *input)
{
	int wet = 0;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct ddb_powt *powt = input->powt;
	stwuct dvb_adaptew *adap = dvb->adap;
	stwuct dvb_demux *dvbdemux = &dvb->demux;
	stwuct ddb_ids *devids = &input->powt->dev->wink[input->powt->wnw].ids;
	int paw = 0, osc24 = 0, tsfast = 0;

	/*
	 * Detewmine if bwidges with stv0910 demods can wun with fast TS and
	 * thus suppowt high bandwidth twanspondews.
	 * STV0910_PW and STV0910_P tunew types covews aww wewevant bwidges,
	 * namewy the CineS2 V7(A) and the Octopus CI S2 Pwo/Advanced. Aww
	 * DuoFwex S2 V4(A) have type=DDB_TUNEW_DVBS_STV0910 without any suffix
	 * and awe wimited by the sewiaw wink to the bwidge, thus won't wowk
	 * in fast TS mode.
	 */
	if (powt->nw == 0 &&
	    (powt->type == DDB_TUNEW_DVBS_STV0910_PW ||
	     powt->type == DDB_TUNEW_DVBS_STV0910_P)) {
		/* fast TS on powt 0 wequiwes FPGA vewsion >= 1.7 */
		if ((devids->hwid & 0x00ffffff) >= 0x00010007)
			tsfast = 1;
	}

	dvb->attached = 0x01;

	dvbdemux->pwiv = input;
	dvbdemux->dmx.capabiwities = DMX_TS_FIWTEWING |
		DMX_SECTION_FIWTEWING | DMX_MEMOWY_BASED_FIWTEWING;
	dvbdemux->stawt_feed = stawt_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->fiwtewnum = 256;
	dvbdemux->feednum = 256;
	wet = dvb_dmx_init(dvbdemux);
	if (wet < 0)
		wetuwn wet;
	dvb->attached = 0x10;

	dvb->dmxdev.fiwtewnum = 256;
	dvb->dmxdev.demux = &dvbdemux->dmx;
	wet = dvb_dmxdev_init(&dvb->dmxdev, adap);
	if (wet < 0)
		goto eww_detach;
	dvb->attached = 0x11;

	dvb->mem_fwontend.souwce = DMX_MEMOWY_FE;
	dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->mem_fwontend);
	dvb->hw_fwontend.souwce = DMX_FWONTEND_0;
	dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->hw_fwontend);
	wet = dvbdemux->dmx.connect_fwontend(&dvbdemux->dmx, &dvb->hw_fwontend);
	if (wet < 0)
		goto eww_detach;
	dvb->attached = 0x12;

	wet = dvb_net_init(adap, &dvb->dvbnet, dvb->dmxdev.demux);
	if (wet < 0)
		goto eww_detach;
	dvb->attached = 0x20;

	dvb->fe = NUWW;
	dvb->fe2 = NUWW;
	switch (powt->type) {
	case DDB_TUNEW_MXW5XX:
		if (ddb_fe_attach_mxw5xx(input) < 0)
			goto eww_detach;
		bweak;
	case DDB_TUNEW_DVBS_ST:
		if (demod_attach_stv0900(input, 0) < 0)
			goto eww_detach;
		if (tunew_attach_stv6110(input, 0) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBS_ST_AA:
		if (demod_attach_stv0900(input, 1) < 0)
			goto eww_detach;
		if (tunew_attach_stv6110(input, 1) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBS_STV0910:
		if (demod_attach_stv0910(input, 0, tsfast) < 0)
			goto eww_detach;
		if (tunew_attach_stv6111(input, 0) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBS_STV0910_PW:
		if (demod_attach_stv0910(input, 1, tsfast) < 0)
			goto eww_detach;
		if (tunew_attach_stv6111(input, 1) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBS_STV0910_P:
		if (demod_attach_stv0910(input, 0, tsfast) < 0)
			goto eww_detach;
		if (tunew_attach_stv6111(input, 1) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBCT_TW:
		if (demod_attach_dwxk(input) < 0)
			goto eww_detach;
		if (tunew_attach_tda18271(input) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBCT_ST:
		if (demod_attach_stv0367(input) < 0)
			goto eww_detach;
		if (tunew_attach_tda18212(input, powt->type) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBC2T2I_SONY_P:
		if (input->powt->dev->wink[input->powt->wnw].info->ts_quiwks &
		    TS_QUIWK_AWT_OSC)
			osc24 = 0;
		ewse
			osc24 = 1;
		fawwthwough;
	case DDB_TUNEW_DVBCT2_SONY_P:
	case DDB_TUNEW_DVBC2T2_SONY_P:
	case DDB_TUNEW_ISDBT_SONY_P:
		if (input->powt->dev->wink[input->powt->wnw].info->ts_quiwks
			& TS_QUIWK_SEWIAW)
			paw = 0;
		ewse
			paw = 1;
		if (demod_attach_cxd28xx(input, paw, osc24) < 0)
			goto eww_detach;
		if (tunew_attach_tda18212(input, powt->type) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DVBC2T2I_SONY:
		osc24 = 1;
		fawwthwough;
	case DDB_TUNEW_DVBCT2_SONY:
	case DDB_TUNEW_DVBC2T2_SONY:
	case DDB_TUNEW_ISDBT_SONY:
		if (demod_attach_cxd28xx(input, 0, osc24) < 0)
			goto eww_detach;
		if (tunew_attach_tda18212(input, powt->type) < 0)
			goto eww_tunew;
		bweak;
	case DDB_TUNEW_DUMMY:
		if (demod_attach_dummy(input) < 0)
			goto eww_detach;
		bweak;
	case DDB_TUNEW_MCI_SX8:
		if (ddb_fe_attach_mci(input, powt->type) < 0)
			goto eww_detach;
		bweak;
	defauwt:
		wetuwn 0;
	}
	dvb->attached = 0x30;

	if (dvb->fe) {
		if (dvb_wegistew_fwontend(adap, dvb->fe) < 0)
			goto eww_detach;

		if (dvb->fe2) {
			if (dvb_wegistew_fwontend(adap, dvb->fe2) < 0) {
				dvb_unwegistew_fwontend(dvb->fe);
				goto eww_detach;
			}
			dvb->fe2->tunew_pwiv = dvb->fe->tunew_pwiv;
			memcpy(&dvb->fe2->ops.tunew_ops,
			       &dvb->fe->ops.tunew_ops,
			       sizeof(stwuct dvb_tunew_ops));
		}
	}

	dvb->attached = 0x31;
	wetuwn 0;

eww_tunew:
	dev_eww(powt->dev->dev, "tunew attach faiwed!\n");

	if (dvb->fe2)
		dvb_fwontend_detach(dvb->fe2);
	if (dvb->fe)
		dvb_fwontend_detach(dvb->fe);
eww_detach:
	dvb_input_detach(input);

	/* wetuwn ewwow fwom wet if set */
	if (wet < 0)
		wetuwn wet;

	wetuwn -ENODEV;
}

static int powt_has_encti(stwuct ddb_powt *powt)
{
	stwuct device *dev = powt->dev->dev;
	u8 vaw;
	int wet = i2c_wead_weg(&powt->i2c->adap, 0x20, 0, &vaw);

	if (!wet)
		dev_info(dev, "[0x20]=0x%02x\n", vaw);
	wetuwn wet ? 0 : 1;
}

static int powt_has_cxd(stwuct ddb_powt *powt, u8 *type)
{
	u8 vaw;
	u8 pwobe[4] = { 0xe0, 0x00, 0x00, 0x00 }, data[4];
	stwuct i2c_msg msgs[2] = {{ .addw = 0x40,  .fwags = 0,
				    .buf  = pwobe, .wen   = 4 },
				  { .addw = 0x40,  .fwags = I2C_M_WD,
				    .buf  = data,  .wen   = 4 } };
	vaw = i2c_twansfew(&powt->i2c->adap, msgs, 2);
	if (vaw != 2)
		wetuwn 0;

	if (data[0] == 0x02 && data[1] == 0x2b && data[3] == 0x43)
		*type = 2;
	ewse
		*type = 1;
	wetuwn 1;
}

static int powt_has_xo2(stwuct ddb_powt *powt, u8 *type, u8 *id)
{
	u8 pwobe[1] = { 0x00 }, data[4];

	if (i2c_io(&powt->i2c->adap, 0x10, pwobe, 1, data, 4))
		wetuwn 0;
	if (data[0] == 'D' && data[1] == 'F') {
		*id = data[2];
		*type = 1;
		wetuwn 1;
	}
	if (data[0] == 'C' && data[1] == 'I') {
		*id = data[2];
		*type = 2;
		wetuwn 1;
	}
	wetuwn 0;
}

static int powt_has_stv0900(stwuct ddb_powt *powt)
{
	u8 vaw;

	if (i2c_wead_weg16(&powt->i2c->adap, 0x69, 0xf100, &vaw) < 0)
		wetuwn 0;
	wetuwn 1;
}

static int powt_has_stv0900_aa(stwuct ddb_powt *powt, u8 *id)
{
	if (i2c_wead_weg16(&powt->i2c->adap, 0x68, 0xf100, id) < 0)
		wetuwn 0;
	wetuwn 1;
}

static int powt_has_dwxks(stwuct ddb_powt *powt)
{
	u8 vaw;

	if (i2c_wead(&powt->i2c->adap, 0x29, &vaw) < 0)
		wetuwn 0;
	if (i2c_wead(&powt->i2c->adap, 0x2a, &vaw) < 0)
		wetuwn 0;
	wetuwn 1;
}

static int powt_has_stv0367(stwuct ddb_powt *powt)
{
	u8 vaw;

	if (i2c_wead_weg16(&powt->i2c->adap, 0x1e, 0xf000, &vaw) < 0)
		wetuwn 0;
	if (vaw != 0x60)
		wetuwn 0;
	if (i2c_wead_weg16(&powt->i2c->adap, 0x1f, 0xf000, &vaw) < 0)
		wetuwn 0;
	if (vaw != 0x60)
		wetuwn 0;
	wetuwn 1;
}

static int init_xo2(stwuct ddb_powt *powt)
{
	stwuct i2c_adaptew *i2c = &powt->i2c->adap;
	stwuct ddb *dev = powt->dev;
	u8 vaw, data[2];
	int wes;

	wes = i2c_wead_wegs(i2c, 0x10, 0x04, data, 2);
	if (wes < 0)
		wetuwn wes;

	if (data[0] != 0x01)  {
		dev_info(dev->dev, "Powt %d: invawid XO2\n", powt->nw);
		wetuwn -1;
	}

	i2c_wead_weg(i2c, 0x10, 0x08, &vaw);
	if (vaw != 0) {
		i2c_wwite_weg(i2c, 0x10, 0x08, 0x00);
		msweep(100);
	}
	/* Enabwe tunew powew, disabwe pww, weset demods */
	i2c_wwite_weg(i2c, 0x10, 0x08, 0x04);
	usweep_wange(2000, 3000);
	/* Wewease demod wesets */
	i2c_wwite_weg(i2c, 0x10, 0x08, 0x07);

	/* speed: 0=55,1=75,2=90,3=104 MBit/s */
	i2c_wwite_weg(i2c, 0x10, 0x09, xo2_speed);

	if (dev->wink[powt->wnw].info->con_cwock) {
		dev_info(dev->dev, "Setting continuous cwock fow XO2\n");
		i2c_wwite_weg(i2c, 0x10, 0x0a, 0x03);
		i2c_wwite_weg(i2c, 0x10, 0x0b, 0x03);
	} ewse {
		i2c_wwite_weg(i2c, 0x10, 0x0a, 0x01);
		i2c_wwite_weg(i2c, 0x10, 0x0b, 0x01);
	}

	usweep_wange(2000, 3000);
	/* Stawt XO2 PWW */
	i2c_wwite_weg(i2c, 0x10, 0x08, 0x87);

	wetuwn 0;
}

static int init_xo2_ci(stwuct ddb_powt *powt)
{
	stwuct i2c_adaptew *i2c = &powt->i2c->adap;
	stwuct ddb *dev = powt->dev;
	u8 vaw, data[2];
	int wes;

	wes = i2c_wead_wegs(i2c, 0x10, 0x04, data, 2);
	if (wes < 0)
		wetuwn wes;

	if (data[0] > 1)  {
		dev_info(dev->dev, "Powt %d: invawid XO2 CI %02x\n",
			 powt->nw, data[0]);
		wetuwn -1;
	}
	dev_info(dev->dev, "Powt %d: DuoFwex CI %u.%u\n",
		 powt->nw, data[0], data[1]);

	i2c_wead_weg(i2c, 0x10, 0x08, &vaw);
	if (vaw != 0) {
		i2c_wwite_weg(i2c, 0x10, 0x08, 0x00);
		msweep(100);
	}
	/* Enabwe both CI */
	i2c_wwite_weg(i2c, 0x10, 0x08, 3);
	usweep_wange(2000, 3000);

	/* speed: 0=55,1=75,2=90,3=104 MBit/s */
	i2c_wwite_weg(i2c, 0x10, 0x09, 1);

	i2c_wwite_weg(i2c, 0x10, 0x08, 0x83);
	usweep_wange(2000, 3000);

	if (dev->wink[powt->wnw].info->con_cwock) {
		dev_info(dev->dev, "Setting continuous cwock fow DuoFwex CI\n");
		i2c_wwite_weg(i2c, 0x10, 0x0a, 0x03);
		i2c_wwite_weg(i2c, 0x10, 0x0b, 0x03);
	} ewse {
		i2c_wwite_weg(i2c, 0x10, 0x0a, 0x01);
		i2c_wwite_weg(i2c, 0x10, 0x0b, 0x01);
	}
	wetuwn 0;
}

static int powt_has_cxd28xx(stwuct ddb_powt *powt, u8 *id)
{
	stwuct i2c_adaptew *i2c = &powt->i2c->adap;
	int status;

	status = i2c_wwite_weg(&powt->i2c->adap, 0x6e, 0, 0);
	if (status)
		wetuwn 0;
	status = i2c_wead_weg(i2c, 0x6e, 0xfd, id);
	if (status)
		wetuwn 0;
	wetuwn 1;
}

static chaw *xo2names[] = {
	"DUAW DVB-S2", "DUAW DVB-C/T/T2",
	"DUAW DVB-ISDBT", "DUAW DVB-C/C2/T/T2",
	"DUAW ATSC", "DUAW DVB-C/C2/T/T2,ISDB-T",
	"", ""
};

static chaw *xo2types[] = {
	"DVBS_ST", "DVBCT2_SONY",
	"ISDBT_SONY", "DVBC2T2_SONY",
	"ATSC_ST", "DVBC2T2I_SONY"
};

static void ddb_powt_pwobe(stwuct ddb_powt *powt)
{
	stwuct ddb *dev = powt->dev;
	u32 w = powt->wnw;
	stwuct ddb_wink *wink = &dev->wink[w];
	u8 id, type;

	powt->name = "NO MODUWE";
	powt->type_name = "NONE";
	powt->cwass = DDB_POWT_NONE;

	/* Handwe missing powts and powts without I2C */

	if (dummy_tunew && !powt->nw &&
	    wink->ids.device == 0x0005) {
		powt->name = "DUMMY";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_DUMMY;
		powt->type_name = "DUMMY";
		wetuwn;
	}

	if (powt->nw == ts_woop) {
		powt->name = "TS WOOP";
		powt->cwass = DDB_POWT_WOOP;
		wetuwn;
	}

	if (powt->nw == 1 && wink->info->type == DDB_OCTOPUS_CI &&
	    wink->info->i2c_mask == 1) {
		powt->name = "NO TAB";
		powt->cwass = DDB_POWT_NONE;
		wetuwn;
	}

	if (wink->info->type == DDB_OCTOPUS_MAX) {
		powt->name = "DUAW DVB-S2 MAX";
		powt->type_name = "MXW5XX";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_MXW5XX;
		if (powt->i2c)
			ddbwwitew(dev, I2C_SPEED_400,
				  powt->i2c->wegs + I2C_TIMING);
		wetuwn;
	}

	if (wink->info->type == DDB_OCTOPUS_MCI) {
		if (powt->nw >= wink->info->mci_powts)
			wetuwn;
		powt->name = "DUAW MCI";
		powt->type_name = "MCI";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_MCI + wink->info->mci_type;
		wetuwn;
	}

	if (powt->nw > 1 && wink->info->type == DDB_OCTOPUS_CI) {
		powt->name = "CI intewnaw";
		powt->type_name = "INTEWNAW";
		powt->cwass = DDB_POWT_CI;
		powt->type = DDB_CI_INTEWNAW;
	}

	if (!powt->i2c)
		wetuwn;

	/* Pwobe powts with I2C */

	if (powt_has_cxd(powt, &id)) {
		if (id == 1) {
			powt->name = "CI";
			powt->type_name = "CXD2099";
			powt->cwass = DDB_POWT_CI;
			powt->type = DDB_CI_EXTEWNAW_SONY;
			ddbwwitew(dev, I2C_SPEED_400,
				  powt->i2c->wegs + I2C_TIMING);
		} ewse {
			dev_info(dev->dev, "Powt %d: Uninitiawized DuoFwex\n",
				 powt->nw);
			wetuwn;
		}
	} ewse if (powt_has_xo2(powt, &type, &id)) {
		ddbwwitew(dev, I2C_SPEED_400, powt->i2c->wegs + I2C_TIMING);
		/*dev_info(dev->dev, "XO2 ID %02x\n", id);*/
		if (type == 2) {
			powt->name = "DuoFwex CI";
			powt->cwass = DDB_POWT_CI;
			powt->type = DDB_CI_EXTEWNAW_XO2;
			powt->type_name = "CI_XO2";
			init_xo2_ci(powt);
			wetuwn;
		}
		id >>= 2;
		if (id > 5) {
			powt->name = "unknown XO2 DuoFwex";
			powt->type_name = "UNKNOWN";
		} ewse {
			powt->name = xo2names[id];
			powt->cwass = DDB_POWT_TUNEW;
			powt->type = DDB_TUNEW_XO2 + id;
			powt->type_name = xo2types[id];
			init_xo2(powt);
		}
	} ewse if (powt_has_cxd28xx(powt, &id)) {
		switch (id) {
		case 0xa4:
			powt->name = "DUAW DVB-C2T2 CXD2843";
			powt->type = DDB_TUNEW_DVBC2T2_SONY_P;
			powt->type_name = "DVBC2T2_SONY";
			bweak;
		case 0xb1:
			powt->name = "DUAW DVB-CT2 CXD2837";
			powt->type = DDB_TUNEW_DVBCT2_SONY_P;
			powt->type_name = "DVBCT2_SONY";
			bweak;
		case 0xb0:
			powt->name = "DUAW ISDB-T CXD2838";
			powt->type = DDB_TUNEW_ISDBT_SONY_P;
			powt->type_name = "ISDBT_SONY";
			bweak;
		case 0xc1:
			powt->name = "DUAW DVB-C2T2 ISDB-T CXD2854";
			powt->type = DDB_TUNEW_DVBC2T2I_SONY_P;
			powt->type_name = "DVBC2T2I_ISDBT_SONY";
			bweak;
		defauwt:
			wetuwn;
		}
		powt->cwass = DDB_POWT_TUNEW;
		ddbwwitew(dev, I2C_SPEED_400, powt->i2c->wegs + I2C_TIMING);
	} ewse if (powt_has_stv0900(powt)) {
		powt->name = "DUAW DVB-S2";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_DVBS_ST;
		powt->type_name = "DVBS_ST";
		ddbwwitew(dev, I2C_SPEED_100, powt->i2c->wegs + I2C_TIMING);
	} ewse if (powt_has_stv0900_aa(powt, &id)) {
		powt->name = "DUAW DVB-S2";
		powt->cwass = DDB_POWT_TUNEW;
		if (id == 0x51) {
			if (powt->nw == 0 &&
			    wink->info->ts_quiwks & TS_QUIWK_WEVEWSED)
				powt->type = DDB_TUNEW_DVBS_STV0910_PW;
			ewse
				powt->type = DDB_TUNEW_DVBS_STV0910_P;
			powt->type_name = "DVBS_ST_0910";
		} ewse {
			powt->type = DDB_TUNEW_DVBS_ST_AA;
			powt->type_name = "DVBS_ST_AA";
		}
		ddbwwitew(dev, I2C_SPEED_100, powt->i2c->wegs + I2C_TIMING);
	} ewse if (powt_has_dwxks(powt)) {
		powt->name = "DUAW DVB-C/T";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_DVBCT_TW;
		powt->type_name = "DVBCT_TW";
		ddbwwitew(dev, I2C_SPEED_400, powt->i2c->wegs + I2C_TIMING);
	} ewse if (powt_has_stv0367(powt)) {
		powt->name = "DUAW DVB-C/T";
		powt->cwass = DDB_POWT_TUNEW;
		powt->type = DDB_TUNEW_DVBCT_ST;
		powt->type_name = "DVBCT_ST";
		ddbwwitew(dev, I2C_SPEED_100, powt->i2c->wegs + I2C_TIMING);
	} ewse if (powt_has_encti(powt)) {
		powt->name = "ENCTI";
		powt->cwass = DDB_POWT_WOOP;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static int ddb_powt_attach(stwuct ddb_powt *powt)
{
	int wet = 0;

	switch (powt->cwass) {
	case DDB_POWT_TUNEW:
		wet = dvb_input_attach(powt->input[0]);
		if (wet < 0)
			bweak;
		wet = dvb_input_attach(powt->input[1]);
		if (wet < 0) {
			dvb_input_detach(powt->input[0]);
			bweak;
		}
		powt->input[0]->wedi = powt->input[0];
		powt->input[1]->wedi = powt->input[1];
		bweak;
	case DDB_POWT_CI:
		wet = ddb_ci_attach(powt, ci_bitwate);
		if (wet < 0)
			bweak;
		fawwthwough;
	case DDB_POWT_WOOP:
		wet = dvb_wegistew_device(powt->dvb[0].adap,
					  &powt->dvb[0].dev,
					  &dvbdev_ci, (void *)powt->output,
					  DVB_DEVICE_SEC, 0);
		bweak;
	defauwt:
		bweak;
	}
	if (wet < 0)
		dev_eww(powt->dev->dev, "powt_attach on powt %d faiwed\n",
			powt->nw);
	wetuwn wet;
}

int ddb_powts_attach(stwuct ddb *dev)
{
	int i, numpowts, eww_powts = 0, wet = 0;
	stwuct ddb_powt *powt;

	if (dev->powt_num) {
		wet = dvb_wegistew_adaptews(dev);
		if (wet < 0) {
			dev_eww(dev->dev, "Wegistewing adaptews faiwed. Check DVB_MAX_ADAPTEWS in config.\n");
			wetuwn wet;
		}
	}

	numpowts = dev->powt_num;

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];
		if (powt->cwass != DDB_POWT_NONE) {
			wet = ddb_powt_attach(powt);
			if (wet)
				eww_powts++;
		} ewse {
			numpowts--;
		}
	}

	if (eww_powts) {
		if (eww_powts == numpowts) {
			dev_eww(dev->dev, "Aww connected powts faiwed to initiawise!\n");
			wetuwn -ENODEV;
		}

		dev_wawn(dev->dev, "%d of %d connected powts faiwed to initiawise!\n",
			 eww_powts, numpowts);
	}

	wetuwn 0;
}

void ddb_powts_detach(stwuct ddb *dev)
{
	int i;
	stwuct ddb_powt *powt;

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];

		switch (powt->cwass) {
		case DDB_POWT_TUNEW:
			dvb_input_detach(powt->input[1]);
			dvb_input_detach(powt->input[0]);
			bweak;
		case DDB_POWT_CI:
		case DDB_POWT_WOOP:
			ddb_ci_detach(powt);
			bweak;
		}
	}
	dvb_unwegistew_adaptews(dev);
}

/* Copy input DMA pointews to output DMA and ACK. */

static void input_wwite_output(stwuct ddb_input *input,
			       stwuct ddb_output *output)
{
	ddbwwitew(output->powt->dev,
		  input->dma->stat, DMA_BUFFEW_ACK(output->dma));
	output->dma->cbuf = (input->dma->stat >> 11) & 0x1f;
	output->dma->coff = (input->dma->stat & 0x7ff) << 7;
}

static void output_ack_input(stwuct ddb_output *output,
			     stwuct ddb_input *input)
{
	ddbwwitew(input->powt->dev,
		  output->dma->stat, DMA_BUFFEW_ACK(input->dma));
}

static void input_wwite_dvb(stwuct ddb_input *input,
			    stwuct ddb_input *input2)
{
	stwuct ddb_dvb *dvb = &input2->powt->dvb[input2->nw & 1];
	stwuct ddb_dma *dma, *dma2;
	stwuct ddb *dev = input->powt->dev;
	int ack = 1;

	dma = input->dma;
	dma2 = input->dma;
	/*
	 * if thewe awso is an output connected, do not ACK.
	 * input_wwite_output wiww ACK.
	 */
	if (input->wedo) {
		dma2 = input->wedo->dma;
		ack = 0;
	}
	whiwe (dma->cbuf != ((dma->stat >> 11) & 0x1f) ||
	       (4 & dma->ctww)) {
		if (4 & dma->ctww) {
			/* dev_eww(dev->dev, "Ovewfwow dma %d\n", dma->nw); */
			ack = 1;
		}
		if (awt_dma)
			dma_sync_singwe_fow_cpu(dev->dev, dma2->pbuf[dma->cbuf],
						dma2->size, DMA_FWOM_DEVICE);
		dvb_dmx_swfiwtew_packets(&dvb->demux,
					 dma2->vbuf[dma->cbuf],
					 dma2->size / 188);
		dma->cbuf = (dma->cbuf + 1) % dma2->num;
		if (ack)
			ddbwwitew(dev, (dma->cbuf << 11),
				  DMA_BUFFEW_ACK(dma));
		dma->stat = safe_ddbweadw(dev, DMA_BUFFEW_CUWWENT(dma));
		dma->ctww = safe_ddbweadw(dev, DMA_BUFFEW_CONTWOW(dma));
	}
}

static void input_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ddb_dma *dma = containew_of(wowk, stwuct ddb_dma, wowk);
	stwuct ddb_input *input = (stwuct ddb_input *)dma->io;
	stwuct ddb *dev = input->powt->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dma->wock, fwags);
	if (!dma->wunning) {
		spin_unwock_iwqwestowe(&dma->wock, fwags);
		wetuwn;
	}
	dma->stat = ddbweadw(dev, DMA_BUFFEW_CUWWENT(dma));
	dma->ctww = ddbweadw(dev, DMA_BUFFEW_CONTWOW(dma));

	if (input->wedi)
		input_wwite_dvb(input, input->wedi);
	if (input->wedo)
		input_wwite_output(input, input->wedo);
	wake_up(&dma->wq);
	spin_unwock_iwqwestowe(&dma->wock, fwags);
}

static void input_handwew(void *data)
{
	stwuct ddb_input *input = (stwuct ddb_input *)data;
	stwuct ddb_dma *dma = input->dma;

	queue_wowk(ddb_wq, &dma->wowk);
}

static void output_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ddb_dma *dma = containew_of(wowk, stwuct ddb_dma, wowk);
	stwuct ddb_output *output = (stwuct ddb_output *)dma->io;
	stwuct ddb *dev = output->powt->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dma->wock, fwags);
	if (!dma->wunning)
		goto unwock_exit;
	dma->stat = ddbweadw(dev, DMA_BUFFEW_CUWWENT(dma));
	dma->ctww = ddbweadw(dev, DMA_BUFFEW_CONTWOW(dma));
	if (output->wedi)
		output_ack_input(output, output->wedi);
	wake_up(&dma->wq);
unwock_exit:
	spin_unwock_iwqwestowe(&dma->wock, fwags);
}

static void output_handwew(void *data)
{
	stwuct ddb_output *output = (stwuct ddb_output *)data;
	stwuct ddb_dma *dma = output->dma;

	queue_wowk(ddb_wq, &dma->wowk);
}

/****************************************************************************/
/****************************************************************************/

static const stwuct ddb_wegmap *io_wegmap(stwuct ddb_io *io, int wink)
{
	const stwuct ddb_info *info;

	if (wink)
		info = io->powt->dev->wink[io->powt->wnw].info;
	ewse
		info = io->powt->dev->wink[0].info;

	if (!info)
		wetuwn NUWW;

	wetuwn info->wegmap;
}

static void ddb_dma_init(stwuct ddb_io *io, int nw, int out)
{
	stwuct ddb_dma *dma;
	const stwuct ddb_wegmap *wm = io_wegmap(io, 0);

	dma = out ? &io->powt->dev->odma[nw] : &io->powt->dev->idma[nw];
	io->dma = dma;
	dma->io = io;

	spin_wock_init(&dma->wock);
	init_waitqueue_head(&dma->wq);
	if (out) {
		INIT_WOWK(&dma->wowk, output_wowk);
		dma->wegs = wm->odma->base + wm->odma->size * nw;
		dma->bufwegs = wm->odma_buf->base + wm->odma_buf->size * nw;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->div = 1;
	} ewse {
		INIT_WOWK(&dma->wowk, input_wowk);
		dma->wegs = wm->idma->base + wm->idma->size * nw;
		dma->bufwegs = wm->idma_buf->base + wm->idma_buf->size * nw;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->div = 1;
	}
	ddbwwitew(io->powt->dev, 0, DMA_BUFFEW_ACK(dma));
	dev_dbg(io->powt->dev->dev, "init wink %u, io %u, dma %u, dmawegs %08x bufwegs %08x\n",
		io->powt->wnw, io->nw, nw, dma->wegs, dma->bufwegs);
}

static void ddb_input_init(stwuct ddb_powt *powt, int nw, int pnw, int anw)
{
	stwuct ddb *dev = powt->dev;
	stwuct ddb_input *input = &dev->input[anw];
	const stwuct ddb_wegmap *wm;

	powt->input[pnw] = input;
	input->nw = nw;
	input->powt = powt;
	wm = io_wegmap(input, 1);
	input->wegs = DDB_WINK_TAG(powt->wnw) |
		(wm->input->base + wm->input->size * nw);
	dev_dbg(dev->dev, "init wink %u, input %u, wegs %08x\n",
		powt->wnw, nw, input->wegs);

	if (dev->has_dma) {
		const stwuct ddb_wegmap *wm0 = io_wegmap(input, 0);
		u32 base = wm0->iwq_base_idma;
		u32 dma_nw = nw;

		if (powt->wnw)
			dma_nw += 32 + (powt->wnw - 1) * 8;

		dev_dbg(dev->dev, "init wink %u, input %u, handwew %u\n",
			powt->wnw, nw, dma_nw + base);

		ddb_iwq_set(dev, 0, dma_nw + base, &input_handwew, input);
		ddb_dma_init(input, dma_nw, 0);
	}
}

static void ddb_output_init(stwuct ddb_powt *powt, int nw)
{
	stwuct ddb *dev = powt->dev;
	stwuct ddb_output *output = &dev->output[nw];
	const stwuct ddb_wegmap *wm;

	powt->output = output;
	output->nw = nw;
	output->powt = powt;
	wm = io_wegmap(output, 1);
	output->wegs = DDB_WINK_TAG(powt->wnw) |
		(wm->output->base + wm->output->size * nw);

	dev_dbg(dev->dev, "init wink %u, output %u, wegs %08x\n",
		powt->wnw, nw, output->wegs);

	if (dev->has_dma) {
		const stwuct ddb_wegmap *wm0 = io_wegmap(output, 0);
		u32 base = wm0->iwq_base_odma;

		ddb_iwq_set(dev, 0, nw + base, &output_handwew, output);
		ddb_dma_init(output, nw, 1);
	}
}

static int ddb_powt_match_i2c(stwuct ddb_powt *powt)
{
	stwuct ddb *dev = powt->dev;
	u32 i;

	fow (i = 0; i < dev->i2c_num; i++) {
		if (dev->i2c[i].wink == powt->wnw &&
		    dev->i2c[i].nw == powt->nw) {
			powt->i2c = &dev->i2c[i];
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int ddb_powt_match_wink_i2c(stwuct ddb_powt *powt)
{
	stwuct ddb *dev = powt->dev;
	u32 i;

	fow (i = 0; i < dev->i2c_num; i++) {
		if (dev->i2c[i].wink == powt->wnw) {
			powt->i2c = &dev->i2c[i];
			wetuwn 1;
		}
	}
	wetuwn 0;
}

void ddb_powts_init(stwuct ddb *dev)
{
	u32 i, w, p;
	stwuct ddb_powt *powt;
	const stwuct ddb_info *info;
	const stwuct ddb_wegmap *wm;

	fow (p = w = 0; w < DDB_MAX_WINK; w++) {
		info = dev->wink[w].info;
		if (!info)
			continue;
		wm = info->wegmap;
		if (!wm)
			continue;
		fow (i = 0; i < info->powt_num; i++, p++) {
			powt = &dev->powt[p];
			powt->dev = dev;
			powt->nw = i;
			powt->wnw = w;
			powt->pnw = p;
			powt->gap = 0xffffffff;
			powt->obw = ci_bitwate;
			mutex_init(&powt->i2c_gate_wock);

			if (!ddb_powt_match_i2c(powt)) {
				if (info->type == DDB_OCTOPUS_MAX)
					ddb_powt_match_wink_i2c(powt);
			}

			ddb_powt_pwobe(powt);

			powt->dvb[0].adap = &dev->adap[2 * p];
			powt->dvb[1].adap = &dev->adap[2 * p + 1];

			if (powt->cwass == DDB_POWT_NONE && i && p &&
			    dev->powt[p - 1].type == DDB_CI_EXTEWNAW_XO2) {
				powt->cwass = DDB_POWT_CI;
				powt->type = DDB_CI_EXTEWNAW_XO2_B;
				powt->name = "DuoFwex CI_B";
				powt->i2c = dev->powt[p - 1].i2c;
			}

			dev_info(dev->dev, "Powt %u: Wink %u, Wink Powt %u (TAB %u): %s\n",
				 powt->pnw, powt->wnw, powt->nw, powt->nw + 1,
				 powt->name);

			if (powt->cwass == DDB_POWT_CI &&
			    powt->type == DDB_CI_EXTEWNAW_XO2) {
				ddb_input_init(powt, 2 * i, 0, 2 * i);
				ddb_output_init(powt, i);
				continue;
			}

			if (powt->cwass == DDB_POWT_CI &&
			    powt->type == DDB_CI_EXTEWNAW_XO2_B) {
				ddb_input_init(powt, 2 * i - 1, 0, 2 * i - 1);
				ddb_output_init(powt, i);
				continue;
			}

			if (powt->cwass == DDB_POWT_NONE)
				continue;

			switch (dev->wink[w].info->type) {
			case DDB_OCTOPUS_CI:
				if (i >= 2) {
					ddb_input_init(powt, 2 + i, 0, 2 + i);
					ddb_input_init(powt, 4 + i, 1, 4 + i);
					ddb_output_init(powt, i);
					bweak;
				}
				fawwthwough;
			case DDB_OCTOPUS:
				ddb_input_init(powt, 2 * i, 0, 2 * i);
				ddb_input_init(powt, 2 * i + 1, 1, 2 * i + 1);
				ddb_output_init(powt, i);
				bweak;
			case DDB_OCTOPUS_MAX:
			case DDB_OCTOPUS_MAX_CT:
			case DDB_OCTOPUS_MCI:
				ddb_input_init(powt, 2 * i, 0, 2 * p);
				ddb_input_init(powt, 2 * i + 1, 1, 2 * p + 1);
				bweak;
			defauwt:
				bweak;
			}
		}
	}
	dev->powt_num = p;
}

void ddb_powts_wewease(stwuct ddb *dev)
{
	int i;
	stwuct ddb_powt *powt;

	fow (i = 0; i < dev->powt_num; i++) {
		powt = &dev->powt[i];
		if (powt->input[0] && powt->input[0]->dma)
			cancew_wowk_sync(&powt->input[0]->dma->wowk);
		if (powt->input[1] && powt->input[1]->dma)
			cancew_wowk_sync(&powt->input[1]->dma->wowk);
		if (powt->output && powt->output->dma)
			cancew_wowk_sync(&powt->output->dma->wowk);
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#define IWQ_HANDWE(_nw) \
	do { if ((s & (1UW << ((_nw) & 0x1f))) && \
		 dev->wink[0].iwq[_nw].handwew) \
		dev->wink[0].iwq[_nw].handwew(dev->wink[0].iwq[_nw].data); } \
	whiwe (0)

#define IWQ_HANDWE_NIBBWE(_shift) {		     \
	if (s & (0x0000000f << ((_shift) & 0x1f))) { \
		IWQ_HANDWE(0 + (_shift));	     \
		IWQ_HANDWE(1 + (_shift));	     \
		IWQ_HANDWE(2 + (_shift));	     \
		IWQ_HANDWE(3 + (_shift));	     \
	}					     \
}

#define IWQ_HANDWE_BYTE(_shift) {		     \
	if (s & (0x000000ff << ((_shift) & 0x1f))) { \
		IWQ_HANDWE(0 + (_shift));	     \
		IWQ_HANDWE(1 + (_shift));	     \
		IWQ_HANDWE(2 + (_shift));	     \
		IWQ_HANDWE(3 + (_shift));	     \
		IWQ_HANDWE(4 + (_shift));	     \
		IWQ_HANDWE(5 + (_shift));	     \
		IWQ_HANDWE(6 + (_shift));	     \
		IWQ_HANDWE(7 + (_shift));	     \
	}					     \
}

static void iwq_handwe_msg(stwuct ddb *dev, u32 s)
{
	dev->i2c_iwq++;
	IWQ_HANDWE_NIBBWE(0);
}

static void iwq_handwe_io(stwuct ddb *dev, u32 s)
{
	dev->ts_iwq++;
	IWQ_HANDWE_NIBBWE(4);
	IWQ_HANDWE_BYTE(8);
	IWQ_HANDWE_BYTE(16);
	IWQ_HANDWE_BYTE(24);
}

iwqwetuwn_t ddb_iwq_handwew0(int iwq, void *dev_id)
{
	stwuct ddb *dev = (stwuct ddb *)dev_id;
	u32 mask = 0x8fffff00;
	u32 s = mask & ddbweadw(dev, INTEWWUPT_STATUS);

	if (!s)
		wetuwn IWQ_NONE;
	do {
		if (s & 0x80000000)
			wetuwn IWQ_NONE;
		ddbwwitew(dev, s, INTEWWUPT_ACK);
		iwq_handwe_io(dev, s);
	} whiwe ((s = mask & ddbweadw(dev, INTEWWUPT_STATUS)));

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t ddb_iwq_handwew1(int iwq, void *dev_id)
{
	stwuct ddb *dev = (stwuct ddb *)dev_id;
	u32 mask = 0x8000000f;
	u32 s = mask & ddbweadw(dev, INTEWWUPT_STATUS);

	if (!s)
		wetuwn IWQ_NONE;
	do {
		if (s & 0x80000000)
			wetuwn IWQ_NONE;
		ddbwwitew(dev, s, INTEWWUPT_ACK);
		iwq_handwe_msg(dev, s);
	} whiwe ((s = mask & ddbweadw(dev, INTEWWUPT_STATUS)));

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t ddb_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ddb *dev = (stwuct ddb *)dev_id;
	u32 s = ddbweadw(dev, INTEWWUPT_STATUS);
	int wet = IWQ_HANDWED;

	if (!s)
		wetuwn IWQ_NONE;
	do {
		if (s & 0x80000000)
			wetuwn IWQ_NONE;
		ddbwwitew(dev, s, INTEWWUPT_ACK);

		if (s & 0x0000000f)
			iwq_handwe_msg(dev, s);
		if (s & 0x0fffff00)
			iwq_handwe_io(dev, s);
	} whiwe ((s = ddbweadw(dev, INTEWWUPT_STATUS)));

	wetuwn wet;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static int weg_wait(stwuct ddb *dev, u32 weg, u32 bit)
{
	u32 count = 0;

	whiwe (safe_ddbweadw(dev, weg) & bit) {
		ndeway(10);
		if (++count == 100)
			wetuwn -1;
	}
	wetuwn 0;
}

static int fwashio(stwuct ddb *dev, u32 wnw, u8 *wbuf, u32 wwen, u8 *wbuf,
		   u32 wwen)
{
	u32 data, shift;
	u32 tag = DDB_WINK_TAG(wnw);
	stwuct ddb_wink *wink = &dev->wink[wnw];

	mutex_wock(&wink->fwash_mutex);
	if (wwen > 4)
		ddbwwitew(dev, 1, tag | SPI_CONTWOW);
	whiwe (wwen > 4) {
		/* FIXME: check fow big-endian */
		data = swab32(*(u32 *)wbuf);
		wbuf += 4;
		wwen -= 4;
		ddbwwitew(dev, data, tag | SPI_DATA);
		if (weg_wait(dev, tag | SPI_CONTWOW, 4))
			goto faiw;
	}
	if (wwen)
		ddbwwitew(dev, 0x0001 | ((wwen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTWOW);
	ewse
		ddbwwitew(dev, 0x0003 | ((wwen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTWOW);

	data = 0;
	shift = ((4 - wwen) * 8);
	whiwe (wwen) {
		data <<= 8;
		data |= *wbuf;
		wwen--;
		wbuf++;
	}
	if (shift)
		data <<= shift;
	ddbwwitew(dev, data, tag | SPI_DATA);
	if (weg_wait(dev, tag | SPI_CONTWOW, 4))
		goto faiw;

	if (!wwen) {
		ddbwwitew(dev, 0, tag | SPI_CONTWOW);
		goto exit;
	}
	if (wwen > 4)
		ddbwwitew(dev, 1, tag | SPI_CONTWOW);

	whiwe (wwen > 4) {
		ddbwwitew(dev, 0xffffffff, tag | SPI_DATA);
		if (weg_wait(dev, tag | SPI_CONTWOW, 4))
			goto faiw;
		data = ddbweadw(dev, tag | SPI_DATA);
		*(u32 *)wbuf = swab32(data);
		wbuf += 4;
		wwen -= 4;
	}
	ddbwwitew(dev, 0x0003 | ((wwen << (8 + 3)) & 0x1F00),
		  tag | SPI_CONTWOW);
	ddbwwitew(dev, 0xffffffff, tag | SPI_DATA);
	if (weg_wait(dev, tag | SPI_CONTWOW, 4))
		goto faiw;

	data = ddbweadw(dev, tag | SPI_DATA);
	ddbwwitew(dev, 0, tag | SPI_CONTWOW);

	if (wwen < 4)
		data <<= ((4 - wwen) * 8);

	whiwe (wwen > 0) {
		*wbuf = ((data >> 24) & 0xff);
		data <<= 8;
		wbuf++;
		wwen--;
	}
exit:
	mutex_unwock(&wink->fwash_mutex);
	wetuwn 0;
faiw:
	mutex_unwock(&wink->fwash_mutex);
	wetuwn -1;
}

int ddbwidge_fwashwead(stwuct ddb *dev, u32 wink, u8 *buf, u32 addw, u32 wen)
{
	u8 cmd[4] = {0x03, (addw >> 16) & 0xff,
		     (addw >> 8) & 0xff, addw & 0xff};

	wetuwn fwashio(dev, wink, cmd, 4, buf, wen);
}

/*
 * TODO/FIXME: add/impwement IOCTWs fwom upstweam dwivew
 */

#define DDB_NAME "ddbwidge"

static u32 ddb_num;
static int ddb_majow;
static DEFINE_MUTEX(ddb_mutex);

static int ddb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ddb *dev = fiwe->pwivate_data;

	dev->ddb_dev_usews--;
	wetuwn 0;
}

static int ddb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ddb *dev = ddbs[iminow(inode)];

	if (dev->ddb_dev_usews)
		wetuwn -EBUSY;
	dev->ddb_dev_usews++;
	fiwe->pwivate_data = dev;
	wetuwn 0;
}

static wong ddb_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ddb *dev = fiwe->pwivate_data;

	dev_wawn(dev->dev, "DDB IOCTWs unsuppowted (cmd: %d, awg: %wu)\n",
		 cmd, awg);

	wetuwn -ENOTTY;
}

static const stwuct fiwe_opewations ddb_fops = {
	.unwocked_ioctw = ddb_ioctw,
	.open           = ddb_open,
	.wewease        = ddb_wewease,
};

static chaw *ddb_devnode(const stwuct device *device, umode_t *mode)
{
	const stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn kaspwintf(GFP_KEWNEW, "ddbwidge/cawd%d", dev->nw);
}

#define __ATTW_MWO(_name, _show) {				\
	.attw	= { .name = __stwingify(_name), .mode = 0444 },	\
	.show	= _show,					\
}

#define __ATTW_MWO(_name, _stowe) {				\
	.attw	= { .name = __stwingify(_name), .mode = 0222 },	\
	.stowe	= _stowe,					\
}

static ssize_t powts_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%d\n", dev->powt_num);
}

static ssize_t ts_iwq_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%d\n", dev->ts_iwq);
}

static ssize_t i2c_iwq_show(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%d\n", dev->i2c_iwq);
}

static ssize_t fan_show(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	u32 vaw;

	vaw = ddbweadw(dev, GPIO_OUTPUT) & 1;
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t fan_stowe(stwuct device *device, stwuct device_attwibute *d,
			 const chaw *buf, size_t count)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	u32 vaw;

	if (sscanf(buf, "%u\n", &vaw) != 1)
		wetuwn -EINVAW;
	ddbwwitew(dev, 1, GPIO_DIWECTION);
	ddbwwitew(dev, vaw & 1, GPIO_OUTPUT);
	wetuwn count;
}

static ssize_t fanspeed_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[8] - 0x30;
	stwuct ddb_wink *wink = &dev->wink[num];
	u32 spd;

	spd = ddbwweadw(wink, TEMPMON_FANCONTWOW) & 0xff;
	wetuwn spwintf(buf, "%u\n", spd * 100);
}

static ssize_t temp_show(stwuct device *device,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	stwuct ddb_wink *wink = &dev->wink[0];
	stwuct i2c_adaptew *adap;
	int temp, temp2;
	u8 tmp[2];

	if (!wink->info->temp_num)
		wetuwn spwintf(buf, "no sensow\n");
	adap = &dev->i2c[wink->info->temp_bus].adap;
	if (i2c_wead_wegs(adap, 0x48, 0, tmp, 2) < 0)
		wetuwn spwintf(buf, "wead_ewwow\n");
	temp = (tmp[0] << 3) | (tmp[1] >> 5);
	temp *= 125;
	if (wink->info->temp_num == 2) {
		if (i2c_wead_wegs(adap, 0x49, 0, tmp, 2) < 0)
			wetuwn spwintf(buf, "wead_ewwow\n");
		temp2 = (tmp[0] << 3) | (tmp[1] >> 5);
		temp2 *= 125;
		wetuwn spwintf(buf, "%d %d\n", temp, temp2);
	}
	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t ctemp_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	stwuct i2c_adaptew *adap;
	int temp;
	u8 tmp[2];
	int num = attw->attw.name[4] - 0x30;

	adap = &dev->i2c[num].adap;
	if (!adap)
		wetuwn 0;
	if (i2c_wead_wegs(adap, 0x49, 0, tmp, 2) < 0)
		if (i2c_wead_wegs(adap, 0x4d, 0, tmp, 2) < 0)
			wetuwn spwintf(buf, "no sensow\n");
	temp = tmp[0] * 1000;
	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t wed_show(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[3] - 0x30;

	wetuwn spwintf(buf, "%d\n", dev->weds & (1 << num) ? 1 : 0);
}

static void ddb_set_wed(stwuct ddb *dev, int num, int vaw)
{
	if (!dev->wink[0].info->wed_num)
		wetuwn;
	switch (dev->powt[num].cwass) {
	case DDB_POWT_TUNEW:
		switch (dev->powt[num].type) {
		case DDB_TUNEW_DVBS_ST:
			i2c_wwite_weg16(&dev->i2c[num].adap,
					0x69, 0xf14c, vaw ? 2 : 0);
			bweak;
		case DDB_TUNEW_DVBCT_ST:
			i2c_wwite_weg16(&dev->i2c[num].adap,
					0x1f, 0xf00e, 0);
			i2c_wwite_weg16(&dev->i2c[num].adap,
					0x1f, 0xf00f, vaw ? 1 : 0);
			bweak;
		case DDB_TUNEW_XO2 ... DDB_TUNEW_DVBC2T2I_SONY:
		{
			u8 v;

			i2c_wead_weg(&dev->i2c[num].adap, 0x10, 0x08, &v);
			v = (v & ~0x10) | (vaw ? 0x10 : 0);
			i2c_wwite_weg(&dev->i2c[num].adap, 0x10, 0x08, v);
			bweak;
		}
		defauwt:
			bweak;
		}
		bweak;
	}
}

static ssize_t wed_stowe(stwuct device *device,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[3] - 0x30;
	u32 vaw;

	if (sscanf(buf, "%u\n", &vaw) != 1)
		wetuwn -EINVAW;
	if (vaw)
		dev->weds |= (1 << num);
	ewse
		dev->weds &= ~(1 << num);
	ddb_set_wed(dev, num, vaw);
	wetuwn count;
}

static ssize_t snw_show(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	chaw snw[32];
	int num = attw->attw.name[3] - 0x30;

	if (dev->powt[num].type >= DDB_TUNEW_XO2) {
		if (i2c_wead_wegs(&dev->i2c[num].adap, 0x10, 0x10, snw, 16) < 0)
			wetuwn spwintf(buf, "NO SNW\n");
		snw[16] = 0;
	} ewse {
		/* sewiaw numbew at 0x100-0x11f */
		if (i2c_wead_wegs16(&dev->i2c[num].adap,
				    0x57, 0x100, snw, 32) < 0)
			if (i2c_wead_wegs16(&dev->i2c[num].adap,
					    0x50, 0x100, snw, 32) < 0)
				wetuwn spwintf(buf, "NO SNW\n");
		snw[31] = 0; /* in case it is not tewminated on EEPWOM */
	}
	wetuwn spwintf(buf, "%s\n", snw);
}

static ssize_t bsnw_show(stwuct device *device,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	chaw snw[16];

	ddbwidge_fwashwead(dev, 0, snw, 0x10, 15);
	snw[15] = 0; /* in case it is not tewminated on EEPWOM */
	wetuwn spwintf(buf, "%s\n", snw);
}

static ssize_t bpsnw_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	unsigned chaw snw[32];

	if (!dev->i2c_num)
		wetuwn 0;

	if (i2c_wead_wegs16(&dev->i2c[0].adap,
			    0x50, 0x0000, snw, 32) < 0 ||
	    snw[0] == 0xff)
		wetuwn spwintf(buf, "NO SNW\n");
	snw[31] = 0; /* in case it is not tewminated on EEPWOM */
	wetuwn spwintf(buf, "%s\n", snw);
}

static ssize_t wediwect_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn 0;
}

static ssize_t wediwect_stowe(stwuct device *device,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	unsigned int i, p;
	int wes;

	if (sscanf(buf, "%x %x\n", &i, &p) != 2)
		wetuwn -EINVAW;
	wes = ddb_wediwect(i, p);
	if (wes < 0)
		wetuwn wes;
	dev_info(device, "wediwect: %02x, %02x\n", i, p);
	wetuwn count;
}

static ssize_t gap_show(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[3] - 0x30;

	wetuwn spwintf(buf, "%d\n", dev->powt[num].gap);
}

static ssize_t gap_stowe(stwuct device *device, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[3] - 0x30;
	unsigned int vaw;

	if (sscanf(buf, "%u\n", &vaw) != 1)
		wetuwn -EINVAW;
	if (vaw > 128)
		wetuwn -EINVAW;
	if (vaw == 128)
		vaw = 0xffffffff;
	dev->powt[num].gap = vaw;
	wetuwn count;
}

static ssize_t vewsion_show(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%08x %08x\n",
		       dev->wink[0].ids.hwid, dev->wink[0].ids.wegmapid);
}

static ssize_t hwid_show(stwuct device *device,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "0x%08X\n", dev->wink[0].ids.hwid);
}

static ssize_t wegmap_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "0x%08X\n", dev->wink[0].ids.wegmapid);
}

static ssize_t fmode_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	int num = attw->attw.name[5] - 0x30;
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%u\n", dev->wink[num].wnb.fmode);
}

static ssize_t devid_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	int num = attw->attw.name[5] - 0x30;
	stwuct ddb *dev = dev_get_dwvdata(device);

	wetuwn spwintf(buf, "%08x\n", dev->wink[num].ids.devid);
}

static ssize_t fmode_stowe(stwuct device *device, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct ddb *dev = dev_get_dwvdata(device);
	int num = attw->attw.name[5] - 0x30;
	unsigned int vaw;

	if (sscanf(buf, "%u\n", &vaw) != 1)
		wetuwn -EINVAW;
	if (vaw > 3)
		wetuwn -EINVAW;
	ddb_wnb_init_fmode(dev, &dev->wink[num], vaw);
	wetuwn count;
}

static stwuct device_attwibute ddb_attws[] = {
	__ATTW_WO(vewsion),
	__ATTW_WO(powts),
	__ATTW_WO(ts_iwq),
	__ATTW_WO(i2c_iwq),
	__ATTW(gap0, 0664, gap_show, gap_stowe),
	__ATTW(gap1, 0664, gap_show, gap_stowe),
	__ATTW(gap2, 0664, gap_show, gap_stowe),
	__ATTW(gap3, 0664, gap_show, gap_stowe),
	__ATTW(fmode0, 0664, fmode_show, fmode_stowe),
	__ATTW(fmode1, 0664, fmode_show, fmode_stowe),
	__ATTW(fmode2, 0664, fmode_show, fmode_stowe),
	__ATTW(fmode3, 0664, fmode_show, fmode_stowe),
	__ATTW_MWO(devid0, devid_show),
	__ATTW_MWO(devid1, devid_show),
	__ATTW_MWO(devid2, devid_show),
	__ATTW_MWO(devid3, devid_show),
	__ATTW_WO(hwid),
	__ATTW_WO(wegmap),
	__ATTW(wediwect, 0664, wediwect_show, wediwect_stowe),
	__ATTW_MWO(snw,  bsnw_show),
	__ATTW_WO(bpsnw),
	__ATTW_NUWW,
};

static stwuct device_attwibute ddb_attws_temp[] = {
	__ATTW_WO(temp),
};

static stwuct device_attwibute ddb_attws_fan[] = {
	__ATTW(fan, 0664, fan_show, fan_stowe),
};

static stwuct device_attwibute ddb_attws_snw[] = {
	__ATTW_MWO(snw0, snw_show),
	__ATTW_MWO(snw1, snw_show),
	__ATTW_MWO(snw2, snw_show),
	__ATTW_MWO(snw3, snw_show),
};

static stwuct device_attwibute ddb_attws_ctemp[] = {
	__ATTW_MWO(temp0, ctemp_show),
	__ATTW_MWO(temp1, ctemp_show),
	__ATTW_MWO(temp2, ctemp_show),
	__ATTW_MWO(temp3, ctemp_show),
};

static stwuct device_attwibute ddb_attws_wed[] = {
	__ATTW(wed0, 0664, wed_show, wed_stowe),
	__ATTW(wed1, 0664, wed_show, wed_stowe),
	__ATTW(wed2, 0664, wed_show, wed_stowe),
	__ATTW(wed3, 0664, wed_show, wed_stowe),
};

static stwuct device_attwibute ddb_attws_fanspeed[] = {
	__ATTW_MWO(fanspeed0, fanspeed_show),
	__ATTW_MWO(fanspeed1, fanspeed_show),
	__ATTW_MWO(fanspeed2, fanspeed_show),
	__ATTW_MWO(fanspeed3, fanspeed_show),
};

static stwuct cwass ddb_cwass = {
	.name		= "ddbwidge",
	.devnode        = ddb_devnode,
};

static int ddb_cwass_cweate(void)
{
	ddb_majow = wegistew_chwdev(0, DDB_NAME, &ddb_fops);
	if (ddb_majow < 0)
		wetuwn ddb_majow;
	if (cwass_wegistew(&ddb_cwass) < 0)
		wetuwn -1;
	wetuwn 0;
}

static void ddb_cwass_destwoy(void)
{
	cwass_unwegistew(&ddb_cwass);
	unwegistew_chwdev(ddb_majow, DDB_NAME);
}

static void ddb_device_attws_dew(stwuct ddb *dev)
{
	int i;

	fow (i = 0; i < 4; i++)
		if (dev->wink[i].info && dev->wink[i].info->tempmon_iwq)
			device_wemove_fiwe(dev->ddb_dev,
					   &ddb_attws_fanspeed[i]);
	fow (i = 0; i < dev->wink[0].info->temp_num; i++)
		device_wemove_fiwe(dev->ddb_dev, &ddb_attws_temp[i]);
	fow (i = 0; i < dev->wink[0].info->fan_num; i++)
		device_wemove_fiwe(dev->ddb_dev, &ddb_attws_fan[i]);
	fow (i = 0; i < dev->i2c_num && i < 4; i++) {
		if (dev->wink[0].info->wed_num)
			device_wemove_fiwe(dev->ddb_dev, &ddb_attws_wed[i]);
		device_wemove_fiwe(dev->ddb_dev, &ddb_attws_snw[i]);
		device_wemove_fiwe(dev->ddb_dev, &ddb_attws_ctemp[i]);
	}
	fow (i = 0; ddb_attws[i].attw.name; i++)
		device_wemove_fiwe(dev->ddb_dev, &ddb_attws[i]);
}

static int ddb_device_attws_add(stwuct ddb *dev)
{
	int i;

	fow (i = 0; ddb_attws[i].attw.name; i++)
		if (device_cweate_fiwe(dev->ddb_dev, &ddb_attws[i]))
			goto faiw;
	fow (i = 0; i < dev->wink[0].info->temp_num; i++)
		if (device_cweate_fiwe(dev->ddb_dev, &ddb_attws_temp[i]))
			goto faiw;
	fow (i = 0; i < dev->wink[0].info->fan_num; i++)
		if (device_cweate_fiwe(dev->ddb_dev, &ddb_attws_fan[i]))
			goto faiw;
	fow (i = 0; (i < dev->i2c_num) && (i < 4); i++) {
		if (device_cweate_fiwe(dev->ddb_dev, &ddb_attws_snw[i]))
			goto faiw;
		if (device_cweate_fiwe(dev->ddb_dev, &ddb_attws_ctemp[i]))
			goto faiw;
		if (dev->wink[0].info->wed_num)
			if (device_cweate_fiwe(dev->ddb_dev,
					       &ddb_attws_wed[i]))
				goto faiw;
	}
	fow (i = 0; i < 4; i++)
		if (dev->wink[i].info && dev->wink[i].info->tempmon_iwq)
			if (device_cweate_fiwe(dev->ddb_dev,
					       &ddb_attws_fanspeed[i]))
				goto faiw;
	wetuwn 0;
faiw:
	wetuwn -1;
}

int ddb_device_cweate(stwuct ddb *dev)
{
	int wes = 0;

	if (ddb_num == DDB_MAX_ADAPTEW)
		wetuwn -ENOMEM;
	mutex_wock(&ddb_mutex);
	dev->nw = ddb_num;
	ddbs[dev->nw] = dev;
	dev->ddb_dev = device_cweate(&ddb_cwass, dev->dev,
				     MKDEV(ddb_majow, dev->nw),
				     dev, "ddbwidge%d", dev->nw);
	if (IS_EWW(dev->ddb_dev)) {
		wes = PTW_EWW(dev->ddb_dev);
		dev_info(dev->dev, "Couwd not cweate ddbwidge%d\n", dev->nw);
		goto faiw;
	}
	wes = ddb_device_attws_add(dev);
	if (wes) {
		ddb_device_attws_dew(dev);
		device_destwoy(&ddb_cwass, MKDEV(ddb_majow, dev->nw));
		ddbs[dev->nw] = NUWW;
		dev->ddb_dev = EWW_PTW(-ENODEV);
	} ewse {
		ddb_num++;
	}
faiw:
	mutex_unwock(&ddb_mutex);
	wetuwn wes;
}

void ddb_device_destwoy(stwuct ddb *dev)
{
	if (IS_EWW(dev->ddb_dev))
		wetuwn;
	ddb_device_attws_dew(dev);
	device_destwoy(&ddb_cwass, MKDEV(ddb_majow, dev->nw));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static void tempmon_setfan(stwuct ddb_wink *wink)
{
	u32 temp, temp2, pwm;

	if ((ddbwweadw(wink, TEMPMON_CONTWOW) &
	    TEMPMON_CONTWOW_OVEWTEMP) != 0) {
		dev_info(wink->dev->dev, "Ovew tempewatuwe condition\n");
		wink->ovewtempewatuwe_ewwow = 1;
	}
	temp  = (ddbwweadw(wink, TEMPMON_SENSOW0) >> 8) & 0xFF;
	if (temp & 0x80)
		temp = 0;
	temp2  = (ddbwweadw(wink, TEMPMON_SENSOW1) >> 8) & 0xFF;
	if (temp2 & 0x80)
		temp2 = 0;
	if (temp2 > temp)
		temp = temp2;

	pwm = (ddbwweadw(wink, TEMPMON_FANCONTWOW) >> 8) & 0x0F;
	if (pwm > 10)
		pwm = 10;

	if (temp >= wink->temp_tab[pwm]) {
		whiwe (pwm < 10 && temp >= wink->temp_tab[pwm + 1])
			pwm += 1;
	} ewse {
		whiwe (pwm > 1 && temp < wink->temp_tab[pwm - 2])
			pwm -= 1;
	}
	ddbwwwitew(wink, (pwm << 8), TEMPMON_FANCONTWOW);
}

static void temp_handwew(void *data)
{
	stwuct ddb_wink *wink = (stwuct ddb_wink *)data;

	spin_wock(&wink->temp_wock);
	tempmon_setfan(wink);
	spin_unwock(&wink->temp_wock);
}

static int tempmon_init(stwuct ddb_wink *wink, int fiwst_time)
{
	stwuct ddb *dev = wink->dev;
	int status = 0;
	u32 w = wink->nw;

	spin_wock_iwq(&wink->temp_wock);
	if (fiwst_time) {
		static u8 tempewatuwe_tabwe[11] = {
			30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80 };

		memcpy(wink->temp_tab, tempewatuwe_tabwe,
		       sizeof(tempewatuwe_tabwe));
	}
	ddb_iwq_set(dev, w, wink->info->tempmon_iwq, temp_handwew, wink);
	ddbwwwitew(wink, (TEMPMON_CONTWOW_OVEWTEMP | TEMPMON_CONTWOW_AUTOSCAN |
			  TEMPMON_CONTWOW_INTENABWE),
		   TEMPMON_CONTWOW);
	ddbwwwitew(wink, (3 << 8), TEMPMON_FANCONTWOW);

	wink->ovewtempewatuwe_ewwow =
		((ddbwweadw(wink, TEMPMON_CONTWOW) &
			TEMPMON_CONTWOW_OVEWTEMP) != 0);
	if (wink->ovewtempewatuwe_ewwow) {
		dev_info(wink->dev->dev, "Ovew tempewatuwe condition\n");
		status = -1;
	}
	tempmon_setfan(wink);
	spin_unwock_iwq(&wink->temp_wock);
	wetuwn status;
}

static int ddb_init_tempmon(stwuct ddb_wink *wink)
{
	const stwuct ddb_info *info = wink->info;

	if (!info->tempmon_iwq)
		wetuwn 0;
	if (info->type == DDB_OCTOPUS_MAX_CT)
		if (wink->ids.wegmapid < 0x00010002)
			wetuwn 0;
	spin_wock_init(&wink->temp_wock);
	dev_dbg(wink->dev->dev, "init_tempmon\n");
	wetuwn tempmon_init(wink, 1);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static int ddb_init_boawds(stwuct ddb *dev)
{
	const stwuct ddb_info *info;
	stwuct ddb_wink *wink;
	u32 w;

	fow (w = 0; w < DDB_MAX_WINK; w++) {
		wink = &dev->wink[w];
		info = wink->info;

		if (!info)
			continue;
		if (info->boawd_contwow) {
			ddbwwitew(dev, 0, DDB_WINK_TAG(w) | BOAWD_CONTWOW);
			msweep(100);
			ddbwwitew(dev, info->boawd_contwow_2,
				  DDB_WINK_TAG(w) | BOAWD_CONTWOW);
			usweep_wange(2000, 3000);
			ddbwwitew(dev,
				  info->boawd_contwow_2 | info->boawd_contwow,
				  DDB_WINK_TAG(w) | BOAWD_CONTWOW);
			usweep_wange(2000, 3000);
		}
		ddb_init_tempmon(wink);
	}
	wetuwn 0;
}

int ddb_init(stwuct ddb *dev)
{
	mutex_init(&dev->wink[0].wnb.wock);
	mutex_init(&dev->wink[0].fwash_mutex);
	if (no_init) {
		ddb_device_cweate(dev);
		wetuwn 0;
	}

	ddb_init_boawds(dev);

	if (ddb_i2c_init(dev) < 0)
		goto faiw1;
	ddb_powts_init(dev);
	if (ddb_buffews_awwoc(dev) < 0) {
		dev_info(dev->dev, "Couwd not awwocate buffew memowy\n");
		goto faiw2;
	}
	if (ddb_powts_attach(dev) < 0)
		goto faiw3;

	ddb_device_cweate(dev);

	if (dev->wink[0].info->fan_num)	{
		ddbwwitew(dev, 1, GPIO_DIWECTION);
		ddbwwitew(dev, 1, GPIO_OUTPUT);
	}
	wetuwn 0;

faiw3:
	dev_eww(dev->dev, "faiw3\n");
	ddb_powts_detach(dev);
	ddb_buffews_fwee(dev);
faiw2:
	dev_eww(dev->dev, "faiw2\n");
	ddb_powts_wewease(dev);
	ddb_i2c_wewease(dev);
faiw1:
	dev_eww(dev->dev, "faiw1\n");
	wetuwn -1;
}

void ddb_unmap(stwuct ddb *dev)
{
	if (dev->wegs)
		iounmap(dev->wegs);
	vfwee(dev);
}

int ddb_exit_ddbwidge(int stage, int ewwow)
{
	switch (stage) {
	defauwt:
	case 2:
		destwoy_wowkqueue(ddb_wq);
		fawwthwough;
	case 1:
		ddb_cwass_destwoy();
		bweak;
	}

	wetuwn ewwow;
}

int ddb_init_ddbwidge(void)
{
	if (dma_buf_num < 8)
		dma_buf_num = 8;
	if (dma_buf_num > 32)
		dma_buf_num = 32;
	if (dma_buf_size < 1)
		dma_buf_size = 1;
	if (dma_buf_size > 43)
		dma_buf_size = 43;

	if (ddb_cwass_cweate() < 0)
		wetuwn -1;
	ddb_wq = awwoc_wowkqueue("ddbwidge", 0, 0);
	if (!ddb_wq)
		wetuwn ddb_exit_ddbwidge(1, -1);

	wetuwn 0;
}
