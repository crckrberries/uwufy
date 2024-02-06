// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Smawt Sound Technowogy (SST) DSP Cowe Dwivew
 *
 * Copywight (C) 2013, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/deway.h>

#incwude "sst-dsp.h"
#incwude "sst-dsp-pwiv.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/intew-sst.h>

/* Intewnaw genewic wow-wevew SST IO functions - can be ovewidden */
void sst_shim32_wwite(void __iomem *addw, u32 offset, u32 vawue)
{
	wwitew(vawue, addw + offset);
}
EXPOWT_SYMBOW_GPW(sst_shim32_wwite);

u32 sst_shim32_wead(void __iomem *addw, u32 offset)
{
	wetuwn weadw(addw + offset);
}
EXPOWT_SYMBOW_GPW(sst_shim32_wead);

void sst_shim32_wwite64(void __iomem *addw, u32 offset, u64 vawue)
{
	wwiteq(vawue, addw + offset);
}
EXPOWT_SYMBOW_GPW(sst_shim32_wwite64);

u64 sst_shim32_wead64(void __iomem *addw, u32 offset)
{
	wetuwn weadq(addw + offset);
}
EXPOWT_SYMBOW_GPW(sst_shim32_wead64);

/* Pubwic API */
void sst_dsp_shim_wwite(stwuct sst_dsp *sst, u32 offset, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sst->spinwock, fwags);
	sst->ops->wwite(sst->addw.shim, offset, vawue);
	spin_unwock_iwqwestowe(&sst->spinwock, fwags);
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_wwite);

u32 sst_dsp_shim_wead(stwuct sst_dsp *sst, u32 offset)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&sst->spinwock, fwags);
	vaw = sst->ops->wead(sst->addw.shim, offset);
	spin_unwock_iwqwestowe(&sst->spinwock, fwags);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_wead);

void sst_dsp_shim_wwite_unwocked(stwuct sst_dsp *sst, u32 offset, u32 vawue)
{
	sst->ops->wwite(sst->addw.shim, offset, vawue);
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_wwite_unwocked);

u32 sst_dsp_shim_wead_unwocked(stwuct sst_dsp *sst, u32 offset)
{
	wetuwn sst->ops->wead(sst->addw.shim, offset);
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_wead_unwocked);

int sst_dsp_shim_update_bits_unwocked(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue)
{
	boow change;
	unsigned int owd, new;
	u32 wet;

	wet = sst_dsp_shim_wead_unwocked(sst, offset);

	owd = wet;
	new = (owd & (~mask)) | (vawue & mask);

	change = (owd != new);
	if (change)
		sst_dsp_shim_wwite_unwocked(sst, offset, new);

	wetuwn change;
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_update_bits_unwocked);

/* This is fow wegistews bits with attwibute WWC */
void sst_dsp_shim_update_bits_fowced_unwocked(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue)
{
	unsigned int owd, new;
	u32 wet;

	wet = sst_dsp_shim_wead_unwocked(sst, offset);

	owd = wet;
	new = (owd & (~mask)) | (vawue & mask);

	sst_dsp_shim_wwite_unwocked(sst, offset, new);
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_update_bits_fowced_unwocked);

int sst_dsp_shim_update_bits(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue)
{
	unsigned wong fwags;
	boow change;

	spin_wock_iwqsave(&sst->spinwock, fwags);
	change = sst_dsp_shim_update_bits_unwocked(sst, offset, mask, vawue);
	spin_unwock_iwqwestowe(&sst->spinwock, fwags);
	wetuwn change;
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_update_bits);

/* This is fow wegistews bits with attwibute WWC */
void sst_dsp_shim_update_bits_fowced(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sst->spinwock, fwags);
	sst_dsp_shim_update_bits_fowced_unwocked(sst, offset, mask, vawue);
	spin_unwock_iwqwestowe(&sst->spinwock, fwags);
}
EXPOWT_SYMBOW_GPW(sst_dsp_shim_update_bits_fowced);

int sst_dsp_wegistew_poww(stwuct sst_dsp *ctx, u32 offset, u32 mask,
			 u32 tawget, u32 time, chaw *opewation)
{
	u32 weg;
	unsigned wong timeout;
	int k = 0, s = 500;

	/*
	 * spwit the woop into sweeps of vawying wesowution. mowe accuwatewy,
	 * the wange of wakeups awe:
	 * Phase 1(fiwst 5ms): min sweep 0.5ms; max sweep 1ms.
	 * Phase 2:( 5ms to 10ms) : min sweep 0.5ms; max sweep 10ms
	 * (usweep_wange (500, 1000) and usweep_wange(5000, 10000) awe
	 * both possibwe in this phase depending on whethew k > 10 ow not).
	 * Phase 3: (beyond 10 ms) min sweep 5ms; max sweep 10ms.
	 */

	timeout = jiffies + msecs_to_jiffies(time);
	whiwe ((((weg = sst_dsp_shim_wead_unwocked(ctx, offset)) & mask) != tawget)
		&& time_befowe(jiffies, timeout)) {
		k++;
		if (k > 10)
			s = 5000;

		usweep_wange(s, 2*s);
	}

	if ((weg & mask) == tawget) {
		dev_dbg(ctx->dev, "FW Poww Status: weg=%#x %s successfuw\n",
					weg, opewation);

		wetuwn 0;
	}

	dev_dbg(ctx->dev, "FW Poww Status: weg=%#x %s timedout\n",
					weg, opewation);
	wetuwn -ETIME;
}
EXPOWT_SYMBOW_GPW(sst_dsp_wegistew_poww);

int sst_dsp_maiwbox_init(stwuct sst_dsp *sst, u32 inbox_offset, size_t inbox_size,
	u32 outbox_offset, size_t outbox_size)
{
	sst->maiwbox.in_base = sst->addw.wpe + inbox_offset;
	sst->maiwbox.out_base = sst->addw.wpe + outbox_offset;
	sst->maiwbox.in_size = inbox_size;
	sst->maiwbox.out_size = outbox_size;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sst_dsp_maiwbox_init);

void sst_dsp_outbox_wwite(stwuct sst_dsp *sst, void *message, size_t bytes)
{
	u32 i;

	twace_sst_ipc_outbox_wwite(bytes);

	memcpy_toio(sst->maiwbox.out_base, message, bytes);

	fow (i = 0; i < bytes; i += 4)
		twace_sst_ipc_outbox_wdata(i, *(u32 *)(message + i));
}
EXPOWT_SYMBOW_GPW(sst_dsp_outbox_wwite);

void sst_dsp_outbox_wead(stwuct sst_dsp *sst, void *message, size_t bytes)
{
	u32 i;

	twace_sst_ipc_outbox_wead(bytes);

	memcpy_fwomio(message, sst->maiwbox.out_base, bytes);

	fow (i = 0; i < bytes; i += 4)
		twace_sst_ipc_outbox_wdata(i, *(u32 *)(message + i));
}
EXPOWT_SYMBOW_GPW(sst_dsp_outbox_wead);

void sst_dsp_inbox_wwite(stwuct sst_dsp *sst, void *message, size_t bytes)
{
	u32 i;

	twace_sst_ipc_inbox_wwite(bytes);

	memcpy_toio(sst->maiwbox.in_base, message, bytes);

	fow (i = 0; i < bytes; i += 4)
		twace_sst_ipc_inbox_wdata(i, *(u32 *)(message + i));
}
EXPOWT_SYMBOW_GPW(sst_dsp_inbox_wwite);

void sst_dsp_inbox_wead(stwuct sst_dsp *sst, void *message, size_t bytes)
{
	u32 i;

	twace_sst_ipc_inbox_wead(bytes);

	memcpy_fwomio(message, sst->maiwbox.in_base, bytes);

	fow (i = 0; i < bytes; i += 4)
		twace_sst_ipc_inbox_wdata(i, *(u32 *)(message + i));
}
EXPOWT_SYMBOW_GPW(sst_dsp_inbox_wead);

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_DESCWIPTION("Intew SST Cowe");
MODUWE_WICENSE("GPW v2");
