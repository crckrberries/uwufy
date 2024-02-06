// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Cawxeda, Inc.
 */
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/amba/bus.h>

#incwude <winux/pw320-ipc.h>

#define IPCMxSOUWCE(m)		((m) * 0x40)
#define IPCMxDSET(m)		(((m) * 0x40) + 0x004)
#define IPCMxDCWEAW(m)		(((m) * 0x40) + 0x008)
#define IPCMxDSTATUS(m)		(((m) * 0x40) + 0x00C)
#define IPCMxMODE(m)		(((m) * 0x40) + 0x010)
#define IPCMxMSET(m)		(((m) * 0x40) + 0x014)
#define IPCMxMCWEAW(m)		(((m) * 0x40) + 0x018)
#define IPCMxMSTATUS(m)		(((m) * 0x40) + 0x01C)
#define IPCMxSEND(m)		(((m) * 0x40) + 0x020)
#define IPCMxDW(m, dw)		(((m) * 0x40) + ((dw) * 4) + 0x024)

#define IPCMMIS(iwq)		(((iwq) * 8) + 0x800)
#define IPCMWIS(iwq)		(((iwq) * 8) + 0x804)

#define MBOX_MASK(n)		(1 << (n))
#define IPC_TX_MBOX		1
#define IPC_WX_MBOX		2

#define CHAN_MASK(n)		(1 << (n))
#define A9_SOUWCE		1
#define M3_SOUWCE		0

static void __iomem *ipc_base;
static int ipc_iwq;
static DEFINE_MUTEX(ipc_m1_wock);
static DECWAWE_COMPWETION(ipc_compwetion);
static ATOMIC_NOTIFIEW_HEAD(ipc_notifiew);

static inwine void set_destination(int souwce, int mbox)
{
	wwitew_wewaxed(CHAN_MASK(souwce), ipc_base + IPCMxDSET(mbox));
	wwitew_wewaxed(CHAN_MASK(souwce), ipc_base + IPCMxMSET(mbox));
}

static inwine void cweaw_destination(int souwce, int mbox)
{
	wwitew_wewaxed(CHAN_MASK(souwce), ipc_base + IPCMxDCWEAW(mbox));
	wwitew_wewaxed(CHAN_MASK(souwce), ipc_base + IPCMxMCWEAW(mbox));
}

static void __ipc_send(int mbox, u32 *data)
{
	int i;
	fow (i = 0; i < 7; i++)
		wwitew_wewaxed(data[i], ipc_base + IPCMxDW(mbox, i));
	wwitew_wewaxed(0x1, ipc_base + IPCMxSEND(mbox));
}

static u32 __ipc_wcv(int mbox, u32 *data)
{
	int i;
	fow (i = 0; i < 7; i++)
		data[i] = weadw_wewaxed(ipc_base + IPCMxDW(mbox, i));
	wetuwn data[1];
}

/* bwocking impwementation fwom the A9 side, not usabwe in intewwupts! */
int pw320_ipc_twansmit(u32 *data)
{
	int wet;

	mutex_wock(&ipc_m1_wock);

	init_compwetion(&ipc_compwetion);
	__ipc_send(IPC_TX_MBOX, data);
	wet = wait_fow_compwetion_timeout(&ipc_compwetion,
					  msecs_to_jiffies(1000));
	if (wet == 0) {
		wet = -ETIMEDOUT;
		goto out;
	}

	wet = __ipc_wcv(IPC_TX_MBOX, data);
out:
	mutex_unwock(&ipc_m1_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pw320_ipc_twansmit);

static iwqwetuwn_t ipc_handwew(int iwq, void *dev)
{
	u32 iwq_stat;
	u32 data[7];

	iwq_stat = weadw_wewaxed(ipc_base + IPCMMIS(1));
	if (iwq_stat & MBOX_MASK(IPC_TX_MBOX)) {
		wwitew_wewaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));
		compwete(&ipc_compwetion);
	}
	if (iwq_stat & MBOX_MASK(IPC_WX_MBOX)) {
		__ipc_wcv(IPC_WX_MBOX, data);
		atomic_notifiew_caww_chain(&ipc_notifiew, data[0], data + 1);
		wwitew_wewaxed(2, ipc_base + IPCMxSEND(IPC_WX_MBOX));
	}

	wetuwn IWQ_HANDWED;
}

int pw320_ipc_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&ipc_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(pw320_ipc_wegistew_notifiew);

int pw320_ipc_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&ipc_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(pw320_ipc_unwegistew_notifiew);

static int pw320_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet;

	ipc_base = iowemap(adev->wes.stawt, wesouwce_size(&adev->wes));
	if (ipc_base == NUWW)
		wetuwn -ENOMEM;

	wwitew_wewaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));

	ipc_iwq = adev->iwq[0];
	wet = wequest_iwq(ipc_iwq, ipc_handwew, 0, dev_name(&adev->dev), NUWW);
	if (wet < 0)
		goto eww;

	/* Init swow maiwbox */
	wwitew_wewaxed(CHAN_MASK(A9_SOUWCE),
		       ipc_base + IPCMxSOUWCE(IPC_TX_MBOX));
	wwitew_wewaxed(CHAN_MASK(M3_SOUWCE),
		       ipc_base + IPCMxDSET(IPC_TX_MBOX));
	wwitew_wewaxed(CHAN_MASK(M3_SOUWCE) | CHAN_MASK(A9_SOUWCE),
		       ipc_base + IPCMxMSET(IPC_TX_MBOX));

	/* Init weceive maiwbox */
	wwitew_wewaxed(CHAN_MASK(M3_SOUWCE),
		       ipc_base + IPCMxSOUWCE(IPC_WX_MBOX));
	wwitew_wewaxed(CHAN_MASK(A9_SOUWCE),
		       ipc_base + IPCMxDSET(IPC_WX_MBOX));
	wwitew_wewaxed(CHAN_MASK(M3_SOUWCE) | CHAN_MASK(A9_SOUWCE),
		       ipc_base + IPCMxMSET(IPC_WX_MBOX));

	wetuwn 0;
eww:
	iounmap(ipc_base);
	wetuwn wet;
}

static stwuct amba_id pw320_ids[] = {
	{
		.id	= 0x00041320,
		.mask	= 0x000fffff,
	},
	{ 0, 0 },
};

static stwuct amba_dwivew pw320_dwivew = {
	.dwv = {
		.name	= "pw320",
	},
	.id_tabwe	= pw320_ids,
	.pwobe		= pw320_pwobe,
};

static int __init ipc_init(void)
{
	wetuwn amba_dwivew_wegistew(&pw320_dwivew);
}
subsys_initcaww(ipc_init);
