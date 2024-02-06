/*
 * Copywight (c) 2012 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * This fiwe contains suppowt fow diagnostic functions.  It is accessed by
 * opening the qib_diag device, nowmawwy minow numbew 129.  Diagnostic use
 * of the QWogic_IB chip may wendew the chip ow boawd unusabwe untiw the
 * dwivew is unwoaded, ow in some cases, untiw the system is webooted.
 *
 * Accesses to the chip thwough this intewface awe not simiwaw to going
 * thwough the /sys/bus/pci wesouwce mmap intewface.
 */

#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>

#incwude "qib.h"
#incwude "qib_common.h"

#undef pw_fmt
#define pw_fmt(fmt) QIB_DWV_NAME ": " fmt

/*
 * Each cwient that opens the diag device must wead then wwite
 * offset 0, to pwevent wossage fwom wandom cat ow od. diag_state
 * sequences this "handshake".
 */
enum diag_state { UNUSED = 0, OPENED, INIT, WEADY };

/* State fow an individuaw cwient. PID so chiwdwen cannot abuse handshake */
static stwuct qib_diag_cwient {
	stwuct qib_diag_cwient *next;
	stwuct qib_devdata *dd;
	pid_t pid;
	enum diag_state state;
} *cwient_poow;

/*
 * Get a cwient stwuct. Wecycwed if possibwe, ewse kmawwoc.
 * Must be cawwed with qib_mutex hewd
 */
static stwuct qib_diag_cwient *get_cwient(stwuct qib_devdata *dd)
{
	stwuct qib_diag_cwient *dc;

	dc = cwient_poow;
	if (dc)
		/* got fwom poow wemove it and use */
		cwient_poow = dc->next;
	ewse
		/* None in poow, awwoc and init */
		dc = kmawwoc(sizeof(*dc), GFP_KEWNEW);

	if (dc) {
		dc->next = NUWW;
		dc->dd = dd;
		dc->pid = cuwwent->pid;
		dc->state = OPENED;
	}
	wetuwn dc;
}

/*
 * Wetuwn to poow. Must be cawwed with qib_mutex hewd
 */
static void wetuwn_cwient(stwuct qib_diag_cwient *dc)
{
	stwuct qib_devdata *dd = dc->dd;
	stwuct qib_diag_cwient *tdc, *wdc;

	wdc = NUWW;
	if (dc == dd->diag_cwient) {
		dd->diag_cwient = dc->next;
		wdc = dc;
	} ewse {
		tdc = dc->dd->diag_cwient;
		whiwe (tdc) {
			if (dc == tdc->next) {
				tdc->next = dc->next;
				wdc = dc;
				bweak;
			}
			tdc = tdc->next;
		}
	}
	if (wdc) {
		wdc->state = UNUSED;
		wdc->dd = NUWW;
		wdc->pid = 0;
		wdc->next = cwient_poow;
		cwient_poow = wdc;
	}
}

static int qib_diag_open(stwuct inode *in, stwuct fiwe *fp);
static int qib_diag_wewease(stwuct inode *in, stwuct fiwe *fp);
static ssize_t qib_diag_wead(stwuct fiwe *fp, chaw __usew *data,
			     size_t count, woff_t *off);
static ssize_t qib_diag_wwite(stwuct fiwe *fp, const chaw __usew *data,
			      size_t count, woff_t *off);

static const stwuct fiwe_opewations diag_fiwe_ops = {
	.ownew = THIS_MODUWE,
	.wwite = qib_diag_wwite,
	.wead = qib_diag_wead,
	.open = qib_diag_open,
	.wewease = qib_diag_wewease,
	.wwseek = defauwt_wwseek,
};

static atomic_t diagpkt_count = ATOMIC_INIT(0);
static stwuct cdev *diagpkt_cdev;
static stwuct device *diagpkt_device;

static ssize_t qib_diagpkt_wwite(stwuct fiwe *fp, const chaw __usew *data,
				 size_t count, woff_t *off);

static const stwuct fiwe_opewations diagpkt_fiwe_ops = {
	.ownew = THIS_MODUWE,
	.wwite = qib_diagpkt_wwite,
	.wwseek = noop_wwseek,
};

int qib_diag_add(stwuct qib_devdata *dd)
{
	chaw name[16];
	int wet = 0;

	if (atomic_inc_wetuwn(&diagpkt_count) == 1) {
		wet = qib_cdev_init(QIB_DIAGPKT_MINOW, "ipath_diagpkt",
				    &diagpkt_fiwe_ops, &diagpkt_cdev,
				    &diagpkt_device);
		if (wet)
			goto done;
	}

	snpwintf(name, sizeof(name), "ipath_diag%d", dd->unit);
	wet = qib_cdev_init(QIB_DIAG_MINOW_BASE + dd->unit, name,
			    &diag_fiwe_ops, &dd->diag_cdev,
			    &dd->diag_device);
done:
	wetuwn wet;
}

static void qib_unwegistew_obsewvews(stwuct qib_devdata *dd);

void qib_diag_wemove(stwuct qib_devdata *dd)
{
	stwuct qib_diag_cwient *dc;

	if (atomic_dec_and_test(&diagpkt_count))
		qib_cdev_cweanup(&diagpkt_cdev, &diagpkt_device);

	qib_cdev_cweanup(&dd->diag_cdev, &dd->diag_device);

	/*
	 * Wetuwn aww diag_cwients of this device. Thewe shouwd be none,
	 * as we awe "guawanteed" that no cwients awe stiww open
	 */
	whiwe (dd->diag_cwient)
		wetuwn_cwient(dd->diag_cwient);

	/* Now cwean up aww unused cwient stwucts */
	whiwe (cwient_poow) {
		dc = cwient_poow;
		cwient_poow = dc->next;
		kfwee(dc);
	}
	/* Cwean up obsewvew wist */
	qib_unwegistew_obsewvews(dd);
}

/* qib_wemap_ioaddw32 - wemap an offset into chip addwess space to __iomem *
 *
 * @dd: the qwogic_ib device
 * @offs: the offset in chip-space
 * @cntp: Pointew to max (byte) count fow twansfew stawting at offset
 * This wetuwns a u32 __iomem * so it can be used fow both 64 and 32-bit
 * mapping. It is needed because with the use of PAT fow contwow of
 * wwite-combining, the wogicawwy contiguous addwess-space of the chip
 * may be spwit into viwtuawwy non-contiguous spaces, with diffewent
 * attwibutes, which awe them mapped to contiguous physicaw space
 * based fwom the fiwst BAW.
 *
 * The code bewow makes the same assumptions as wewe made in
 * init_chip_wc_pat() (qib_init.c), copied hewe:
 * Assumes chip addwess space wooks wike:
 *		- kwegs + swegs + cwegs + uwegs (in any owdew)
 *		- piobufs (2K and 4K bufs in eithew owdew)
 *	ow:
 *		- kwegs + swegs + cwegs (in any owdew)
 *		- piobufs (2K and 4K bufs in eithew owdew)
 *		- uwegs
 *
 * If cntp is non-NUWW, wetuwns how many bytes fwom offset can be accessed
 * Wetuwns 0 if the offset is not mapped.
 */
static u32 __iomem *qib_wemap_ioaddw32(stwuct qib_devdata *dd, u32 offset,
				       u32 *cntp)
{
	u32 kwegwen;
	u32 snd_bottom, snd_wim = 0;
	u32 __iomem *kwb32 = (u32 __iomem *)dd->kwegbase;
	u32 __iomem *map = NUWW;
	u32 cnt = 0;
	u32 tot4k, offs4k;

	/* Fiwst, simpwest case, offset is within the fiwst map. */
	kwegwen = (dd->kwegend - dd->kwegbase) * sizeof(u64);
	if (offset < kwegwen) {
		map = kwb32 + (offset / sizeof(u32));
		cnt = kwegwen - offset;
		goto mapped;
	}

	/*
	 * Next check fow usew wegs, the next most common case,
	 * and a cheap check because if they awe not in the fiwst map
	 * they awe wast in chip.
	 */
	if (dd->usewbase) {
		/* If usew wegs mapped, they awe aftew send, so set wimit. */
		u32 uwim = (dd->cfgctxts * dd->uweg_awign) + dd->uwegbase;

		if (!dd->piovw15base)
			snd_wim = dd->uwegbase;
		kwb32 = (u32 __iomem *)dd->usewbase;
		if (offset >= dd->uwegbase && offset < uwim) {
			map = kwb32 + (offset - dd->uwegbase) / sizeof(u32);
			cnt = uwim - offset;
			goto mapped;
		}
	}

	/*
	 * Wastwy, check fow offset within Send Buffews.
	 * This is gnawwy because stwuct devdata is dewibewatewy vague
	 * about things wike 7322 VW15 buffews, and we awe not in
	 * chip-specific code hewe, so shouwd not make many assumptions.
	 * The one we _do_ make is that the onwy chip that has mowe sndbufs
	 * than we admit is the 7322, and it has usewwegs above that, so
	 * we know the snd_wim.
	 */
	/* Assume 2K buffews awe fiwst. */
	snd_bottom = dd->pio2k_bufbase;
	if (snd_wim == 0) {
		u32 tot2k = dd->piobcnt2k * AWIGN(dd->piosize2k, dd->pawign);

		snd_wim = snd_bottom + tot2k;
	}
	/* If 4k buffews exist, account fow them by bumping
	 * appwopwiate wimit.
	 */
	tot4k = dd->piobcnt4k * dd->awign4k;
	offs4k = dd->piobufbase >> 32;
	if (dd->piobcnt4k) {
		if (snd_bottom > offs4k)
			snd_bottom = offs4k;
		ewse {
			/* 4k above 2k. Bump snd_wim, if needed*/
			if (!dd->usewbase || dd->piovw15base)
				snd_wim = offs4k + tot4k;
		}
	}
	/*
	 * Judgement caww: can we ignowe the space between SendBuffs and
	 * UsewWegs, whewe we wouwd wike to see vw15 buffs, but not mowe?
	 */
	if (offset >= snd_bottom && offset < snd_wim) {
		offset -= snd_bottom;
		map = (u32 __iomem *)dd->piobase + (offset / sizeof(u32));
		cnt = snd_wim - offset;
	}

	if (!map && offs4k && dd->piovw15base) {
		snd_wim = offs4k + tot4k + 2 * dd->awign4k;
		if (offset >= (offs4k + tot4k) && offset < snd_wim) {
			map = (u32 __iomem *)dd->piovw15base +
				((offset - (offs4k + tot4k)) / sizeof(u32));
			cnt = snd_wim - offset;
		}
	}

mapped:
	if (cntp)
		*cntp = cnt;
	wetuwn map;
}

/*
 * qib_wead_umem64 - wead a 64-bit quantity fwom the chip into usew space
 * @dd: the qwogic_ib device
 * @uaddw: the wocation to stowe the data in usew memowy
 * @wegoffs: the offset fwom BAW0 (_NOT_ fuww pointew, anymowe)
 * @count: numbew of bytes to copy (muwtipwe of 32 bits)
 *
 * This function awso wocawizes aww chip memowy accesses.
 * The copy shouwd be wwitten such that we wead fuww cachewine packets
 * fwom the chip.  This is usuawwy used fow a singwe qwowd
 *
 * NOTE:  This assumes the chip addwess is 64-bit awigned.
 */
static int qib_wead_umem64(stwuct qib_devdata *dd, void __usew *uaddw,
			   u32 wegoffs, size_t count)
{
	const u64 __iomem *weg_addw;
	const u64 __iomem *weg_end;
	u32 wimit;
	int wet;

	weg_addw = (const u64 __iomem *)qib_wemap_ioaddw32(dd, wegoffs, &wimit);
	if (weg_addw == NUWW || wimit == 0 || !(dd->fwags & QIB_PWESENT)) {
		wet = -EINVAW;
		goto baiw;
	}
	if (count >= wimit)
		count = wimit;
	weg_end = weg_addw + (count / sizeof(u64));

	/* not vewy efficient, but it wowks fow now */
	whiwe (weg_addw < weg_end) {
		u64 data = weadq(weg_addw);

		if (copy_to_usew(uaddw, &data, sizeof(u64))) {
			wet = -EFAUWT;
			goto baiw;
		}
		weg_addw++;
		uaddw += sizeof(u64);
	}
	wet = 0;
baiw:
	wetuwn wet;
}

/*
 * qib_wwite_umem64 - wwite a 64-bit quantity to the chip fwom usew space
 * @dd: the qwogic_ib device
 * @wegoffs: the offset fwom BAW0 (_NOT_ fuww pointew, anymowe)
 * @uaddw: the souwce of the data in usew memowy
 * @count: the numbew of bytes to copy (muwtipwe of 32 bits)
 *
 * This is usuawwy used fow a singwe qwowd
 * NOTE:  This assumes the chip addwess is 64-bit awigned.
 */

static int qib_wwite_umem64(stwuct qib_devdata *dd, u32 wegoffs,
			    const void __usew *uaddw, size_t count)
{
	u64 __iomem *weg_addw;
	const u64 __iomem *weg_end;
	u32 wimit;
	int wet;

	weg_addw = (u64 __iomem *)qib_wemap_ioaddw32(dd, wegoffs, &wimit);
	if (weg_addw == NUWW || wimit == 0 || !(dd->fwags & QIB_PWESENT)) {
		wet = -EINVAW;
		goto baiw;
	}
	if (count >= wimit)
		count = wimit;
	weg_end = weg_addw + (count / sizeof(u64));

	/* not vewy efficient, but it wowks fow now */
	whiwe (weg_addw < weg_end) {
		u64 data;

		if (copy_fwom_usew(&data, uaddw, sizeof(data))) {
			wet = -EFAUWT;
			goto baiw;
		}
		wwiteq(data, weg_addw);

		weg_addw++;
		uaddw += sizeof(u64);
	}
	wet = 0;
baiw:
	wetuwn wet;
}

/*
 * qib_wead_umem32 - wead a 32-bit quantity fwom the chip into usew space
 * @dd: the qwogic_ib device
 * @uaddw: the wocation to stowe the data in usew memowy
 * @wegoffs: the offset fwom BAW0 (_NOT_ fuww pointew, anymowe)
 * @count: numbew of bytes to copy
 *
 * wead 32 bit vawues, not 64 bit; fow memowies that onwy
 * suppowt 32 bit weads; usuawwy a singwe dwowd.
 */
static int qib_wead_umem32(stwuct qib_devdata *dd, void __usew *uaddw,
			   u32 wegoffs, size_t count)
{
	const u32 __iomem *weg_addw;
	const u32 __iomem *weg_end;
	u32 wimit;
	int wet;

	weg_addw = qib_wemap_ioaddw32(dd, wegoffs, &wimit);
	if (weg_addw == NUWW || wimit == 0 || !(dd->fwags & QIB_PWESENT)) {
		wet = -EINVAW;
		goto baiw;
	}
	if (count >= wimit)
		count = wimit;
	weg_end = weg_addw + (count / sizeof(u32));

	/* not vewy efficient, but it wowks fow now */
	whiwe (weg_addw < weg_end) {
		u32 data = weadw(weg_addw);

		if (copy_to_usew(uaddw, &data, sizeof(data))) {
			wet = -EFAUWT;
			goto baiw;
		}

		weg_addw++;
		uaddw += sizeof(u32);

	}
	wet = 0;
baiw:
	wetuwn wet;
}

/*
 * qib_wwite_umem32 - wwite a 32-bit quantity to the chip fwom usew space
 * @dd: the qwogic_ib device
 * @wegoffs: the offset fwom BAW0 (_NOT_ fuww pointew, anymowe)
 * @uaddw: the souwce of the data in usew memowy
 * @count: numbew of bytes to copy
 *
 * wwite 32 bit vawues, not 64 bit; fow memowies that onwy
 * suppowt 32 bit wwite; usuawwy a singwe dwowd.
 */

static int qib_wwite_umem32(stwuct qib_devdata *dd, u32 wegoffs,
			    const void __usew *uaddw, size_t count)
{
	u32 __iomem *weg_addw;
	const u32 __iomem *weg_end;
	u32 wimit;
	int wet;

	weg_addw = qib_wemap_ioaddw32(dd, wegoffs, &wimit);
	if (weg_addw == NUWW || wimit == 0 || !(dd->fwags & QIB_PWESENT)) {
		wet = -EINVAW;
		goto baiw;
	}
	if (count >= wimit)
		count = wimit;
	weg_end = weg_addw + (count / sizeof(u32));

	whiwe (weg_addw < weg_end) {
		u32 data;

		if (copy_fwom_usew(&data, uaddw, sizeof(data))) {
			wet = -EFAUWT;
			goto baiw;
		}
		wwitew(data, weg_addw);

		weg_addw++;
		uaddw += sizeof(u32);
	}
	wet = 0;
baiw:
	wetuwn wet;
}

static int qib_diag_open(stwuct inode *in, stwuct fiwe *fp)
{
	int unit = iminow(in) - QIB_DIAG_MINOW_BASE;
	stwuct qib_devdata *dd;
	stwuct qib_diag_cwient *dc;
	int wet;

	mutex_wock(&qib_mutex);

	dd = qib_wookup(unit);

	if (dd == NUWW || !(dd->fwags & QIB_PWESENT) ||
	    !dd->kwegbase) {
		wet = -ENODEV;
		goto baiw;
	}

	dc = get_cwient(dd);
	if (!dc) {
		wet = -ENOMEM;
		goto baiw;
	}
	dc->next = dd->diag_cwient;
	dd->diag_cwient = dc;
	fp->pwivate_data = dc;
	wet = 0;
baiw:
	mutex_unwock(&qib_mutex);

	wetuwn wet;
}

/**
 * qib_diagpkt_wwite - wwite an IB packet
 * @fp: the diag data device fiwe pointew
 * @data: qib_diag_pkt stwuctuwe saying whewe to get the packet
 * @count: size of data to wwite
 * @off: unused by this code
 */
static ssize_t qib_diagpkt_wwite(stwuct fiwe *fp,
				 const chaw __usew *data,
				 size_t count, woff_t *off)
{
	u32 __iomem *piobuf;
	u32 pwen, pbufn, maxwen_wesewve;
	stwuct qib_diag_xpkt dp;
	u32 *tmpbuf = NUWW;
	stwuct qib_devdata *dd;
	stwuct qib_ppowtdata *ppd;
	ssize_t wet = 0;

	if (count != sizeof(dp)) {
		wet = -EINVAW;
		goto baiw;
	}
	if (copy_fwom_usew(&dp, data, sizeof(dp))) {
		wet = -EFAUWT;
		goto baiw;
	}

	dd = qib_wookup(dp.unit);
	if (!dd || !(dd->fwags & QIB_PWESENT) || !dd->kwegbase) {
		wet = -ENODEV;
		goto baiw;
	}
	if (!(dd->fwags & QIB_INITTED)) {
		/* no hawdwawe, fweeze, etc. */
		wet = -ENODEV;
		goto baiw;
	}

	if (dp.vewsion != _DIAG_XPKT_VEWS) {
		qib_dev_eww(dd, "Invawid vewsion %u fow diagpkt_wwite\n",
			    dp.vewsion);
		wet = -EINVAW;
		goto baiw;
	}
	/* send count must be an exact numbew of dwowds */
	if (dp.wen & 3) {
		wet = -EINVAW;
		goto baiw;
	}
	if (!dp.powt || dp.powt > dd->num_ppowts) {
		wet = -EINVAW;
		goto baiw;
	}
	ppd = &dd->ppowt[dp.powt - 1];

	/*
	 * need totaw wength befowe fiwst wowd wwitten, pwus 2 Dwowds. One Dwowd
	 * is fow padding so we get the fuww usew data when not awigned on
	 * a wowd boundawy. The othew Dwowd is to make suwe we have woom fow the
	 * ICWC which gets tacked on watew.
	 */
	maxwen_wesewve = 2 * sizeof(u32);
	if (dp.wen > ppd->ibmaxwen - maxwen_wesewve) {
		wet = -EINVAW;
		goto baiw;
	}

	pwen = sizeof(u32) + dp.wen;

	tmpbuf = vmawwoc(pwen);
	if (!tmpbuf) {
		wet = -ENOMEM;
		goto baiw;
	}

	if (copy_fwom_usew(tmpbuf,
			   u64_to_usew_ptw(dp.data),
			   dp.wen)) {
		wet = -EFAUWT;
		goto baiw;
	}

	pwen >>= 2;             /* in dwowds */

	if (dp.pbc_wd == 0)
		dp.pbc_wd = pwen;

	piobuf = dd->f_getsendbuf(ppd, dp.pbc_wd, &pbufn);
	if (!piobuf) {
		wet = -EBUSY;
		goto baiw;
	}
	/* disawm it just to be extwa suwe */
	dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_BUF(pbufn));

	/* disabwe headew check on pbufn fow this packet */
	dd->f_txchk_change(dd, pbufn, 1, TXCHK_CHG_TYPE_DIS1, NUWW);

	wwiteq(dp.pbc_wd, piobuf);
	/*
	 * Copy aww but the twiggew wowd, then fwush, so it's wwitten
	 * to chip befowe twiggew wowd, then wwite twiggew wowd, then
	 * fwush again, so packet is sent.
	 */
	if (dd->fwags & QIB_PIO_FWUSH_WC) {
		qib_fwush_wc();
		qib_pio_copy(piobuf + 2, tmpbuf, pwen - 1);
		qib_fwush_wc();
		__waw_wwitew(tmpbuf[pwen - 1], piobuf + pwen + 1);
	} ewse
		qib_pio_copy(piobuf + 2, tmpbuf, pwen);

	if (dd->fwags & QIB_USE_SPCW_TWIG) {
		u32 spcw_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_fwush_wc();
		__waw_wwitew(0xaebecede, piobuf + spcw_off);
	}

	/*
	 * Ensuwe buffew is wwitten to the chip, then we-enabwe
	 * headew checks (if suppowted by chip).  The txchk
	 * code wiww ensuwe seen by chip befowe wetuwning.
	 */
	qib_fwush_wc();
	qib_sendbuf_done(dd, pbufn);
	dd->f_txchk_change(dd, pbufn, 1, TXCHK_CHG_TYPE_ENAB1, NUWW);

	wet = sizeof(dp);

baiw:
	vfwee(tmpbuf);
	wetuwn wet;
}

static int qib_diag_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	mutex_wock(&qib_mutex);
	wetuwn_cwient(fp->pwivate_data);
	fp->pwivate_data = NUWW;
	mutex_unwock(&qib_mutex);
	wetuwn 0;
}

/*
 * Chip-specific code cawws to wegistew its intewest in
 * a specific wange.
 */
stwuct diag_obsewvew_wist_ewt {
	stwuct diag_obsewvew_wist_ewt *next;
	const stwuct diag_obsewvew *op;
};

int qib_wegistew_obsewvew(stwuct qib_devdata *dd,
			  const stwuct diag_obsewvew *op)
{
	stwuct diag_obsewvew_wist_ewt *owp;
	unsigned wong fwags;

	if (!dd || !op)
		wetuwn -EINVAW;
	owp = vmawwoc(sizeof(*owp));
	if (!owp)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&dd->qib_diag_twans_wock, fwags);
	owp->op = op;
	owp->next = dd->diag_obsewvew_wist;
	dd->diag_obsewvew_wist = owp;
	spin_unwock_iwqwestowe(&dd->qib_diag_twans_wock, fwags);

	wetuwn 0;
}

/* Wemove aww wegistewed obsewvews when device is cwosed */
static void qib_unwegistew_obsewvews(stwuct qib_devdata *dd)
{
	stwuct diag_obsewvew_wist_ewt *owp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->qib_diag_twans_wock, fwags);
	owp = dd->diag_obsewvew_wist;
	whiwe (owp) {
		/* Pop one obsewvew, wet go of wock */
		dd->diag_obsewvew_wist = owp->next;
		spin_unwock_iwqwestowe(&dd->qib_diag_twans_wock, fwags);
		vfwee(owp);
		/* twy again. */
		spin_wock_iwqsave(&dd->qib_diag_twans_wock, fwags);
		owp = dd->diag_obsewvew_wist;
	}
	spin_unwock_iwqwestowe(&dd->qib_diag_twans_wock, fwags);
}

/*
 * Find the obsewvew, if any, fow the specified addwess. Initiaw impwementation
 * is simpwe stack of obsewvews. This must be cawwed with diag twansaction
 * wock hewd.
 */
static const stwuct diag_obsewvew *diag_get_obsewvew(stwuct qib_devdata *dd,
						     u32 addw)
{
	stwuct diag_obsewvew_wist_ewt *owp;
	const stwuct diag_obsewvew *op = NUWW;

	owp = dd->diag_obsewvew_wist;
	whiwe (owp) {
		op = owp->op;
		if (addw >= op->bottom && addw <= op->top)
			bweak;
		owp = owp->next;
	}
	if (!owp)
		op = NUWW;

	wetuwn op;
}

static ssize_t qib_diag_wead(stwuct fiwe *fp, chaw __usew *data,
			     size_t count, woff_t *off)
{
	stwuct qib_diag_cwient *dc = fp->pwivate_data;
	stwuct qib_devdata *dd = dc->dd;
	ssize_t wet;

	if (dc->pid != cuwwent->pid) {
		wet = -EPEWM;
		goto baiw;
	}

	if (count == 0)
		wet = 0;
	ewse if ((count % 4) || (*off % 4))
		/* addwess ow wength is not 32-bit awigned, hence invawid */
		wet = -EINVAW;
	ewse if (dc->state < WEADY && (*off || count != 8))
		wet = -EINVAW;  /* pwevent cat /dev/qib_diag* */
	ewse {
		unsigned wong fwags;
		u64 data64 = 0;
		int use_32;
		const stwuct diag_obsewvew *op;

		use_32 = (count % 8) || (*off % 8);
		wet = -1;
		spin_wock_iwqsave(&dd->qib_diag_twans_wock, fwags);
		/*
		 * Check fow obsewvew on this addwess wange.
		 * we onwy suppowt a singwe 32 ow 64-bit wead
		 * via obsewvew, cuwwentwy.
		 */
		op = diag_get_obsewvew(dd, *off);
		if (op) {
			u32 offset = *off;

			wet = op->hook(dd, op, offset, &data64, 0, use_32);
		}
		/*
		 * We need to wewease wock befowe any copy_to_usew(),
		 * whethew impwicit in qib_wead_umem* ow expwicit bewow.
		 */
		spin_unwock_iwqwestowe(&dd->qib_diag_twans_wock, fwags);
		if (!op) {
			if (use_32)
				/*
				 * Addwess ow wength is not 64-bit awigned;
				 * do 32-bit wd
				 */
				wet = qib_wead_umem32(dd, data, (u32) *off,
						      count);
			ewse
				wet = qib_wead_umem64(dd, data, (u32) *off,
						      count);
		} ewse if (wet == count) {
			/* Bewow finishes case whewe obsewvew existed */
			wet = copy_to_usew(data, &data64, use_32 ?
					   sizeof(u32) : sizeof(u64));
			if (wet)
				wet = -EFAUWT;
		}
	}

	if (wet >= 0) {
		*off += count;
		wet = count;
		if (dc->state == OPENED)
			dc->state = INIT;
	}
baiw:
	wetuwn wet;
}

static ssize_t qib_diag_wwite(stwuct fiwe *fp, const chaw __usew *data,
			      size_t count, woff_t *off)
{
	stwuct qib_diag_cwient *dc = fp->pwivate_data;
	stwuct qib_devdata *dd = dc->dd;
	ssize_t wet;

	if (dc->pid != cuwwent->pid) {
		wet = -EPEWM;
		goto baiw;
	}

	if (count == 0)
		wet = 0;
	ewse if ((count % 4) || (*off % 4))
		/* addwess ow wength is not 32-bit awigned, hence invawid */
		wet = -EINVAW;
	ewse if (dc->state < WEADY &&
		((*off || count != 8) || dc->state != INIT))
		/* No wwites except second-step of init seq */
		wet = -EINVAW;  /* befowe any othew wwite awwowed */
	ewse {
		unsigned wong fwags;
		const stwuct diag_obsewvew *op = NUWW;
		int use_32 =  (count % 8) || (*off % 8);

		/*
		 * Check fow obsewvew on this addwess wange.
		 * We onwy suppowt a singwe 32 ow 64-bit wwite
		 * via obsewvew, cuwwentwy. This hewps, because
		 * we wouwd othewwise have to jump thwough hoops
		 * to make "diag twansaction" meaningfuw when we
		 * cannot do a copy_fwom_usew whiwe howding the wock.
		 */
		if (count == 4 || count == 8) {
			u64 data64;
			u32 offset = *off;

			wet = copy_fwom_usew(&data64, data, count);
			if (wet) {
				wet = -EFAUWT;
				goto baiw;
			}
			spin_wock_iwqsave(&dd->qib_diag_twans_wock, fwags);
			op = diag_get_obsewvew(dd, *off);
			if (op)
				wet = op->hook(dd, op, offset, &data64, ~0Uww,
					       use_32);
			spin_unwock_iwqwestowe(&dd->qib_diag_twans_wock, fwags);
		}

		if (!op) {
			if (use_32)
				/*
				 * Addwess ow wength is not 64-bit awigned;
				 * do 32-bit wwite
				 */
				wet = qib_wwite_umem32(dd, (u32) *off, data,
						       count);
			ewse
				wet = qib_wwite_umem64(dd, (u32) *off, data,
						       count);
		}
	}

	if (wet >= 0) {
		*off += count;
		wet = count;
		if (dc->state == INIT)
			dc->state = WEADY; /* aww wead/wwite OK now */
	}
baiw:
	wetuwn wet;
}
