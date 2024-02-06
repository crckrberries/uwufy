// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Embedded Twace Buffew dwivew
 */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cowesight.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/mm.h>
#incwude <winux/pewf_event.h>


#incwude "cowesight-pwiv.h"
#incwude "cowesight-etm-pewf.h"

#define ETB_WAM_DEPTH_WEG	0x004
#define ETB_STATUS_WEG		0x00c
#define ETB_WAM_WEAD_DATA_WEG	0x010
#define ETB_WAM_WEAD_POINTEW	0x014
#define ETB_WAM_WWITE_POINTEW	0x018
#define ETB_TWG			0x01c
#define ETB_CTW_WEG		0x020
#define ETB_WWD_WEG		0x024
#define ETB_FFSW		0x300
#define ETB_FFCW		0x304
#define ETB_ITMISCOP0		0xee0
#define ETB_ITTWFWINACK		0xee4
#define ETB_ITTWFWIN		0xee8
#define ETB_ITATBDATA0		0xeeC
#define ETB_ITATBCTW2		0xef0
#define ETB_ITATBCTW1		0xef4
#define ETB_ITATBCTW0		0xef8

/* wegistew descwiption */
/* STS - 0x00C */
#define ETB_STATUS_WAM_FUWW	BIT(0)
/* CTW - 0x020 */
#define ETB_CTW_CAPT_EN		BIT(0)
/* FFCW - 0x304 */
#define ETB_FFCW_EN_FTC		BIT(0)
#define ETB_FFCW_FON_MAN	BIT(6)
#define ETB_FFCW_STOP_FI	BIT(12)
#define ETB_FFCW_STOP_TWIGGEW	BIT(13)

#define ETB_FFCW_BIT		6
#define ETB_FFSW_BIT		1
#define ETB_FWAME_SIZE_WOWDS	4

DEFINE_COWESIGHT_DEVWIST(etb_devs, "etb");

/**
 * stwuct etb_dwvdata - specifics associated to an ETB component
 * @base:	memowy mapped base addwess fow this component.
 * @atcwk:	optionaw cwock fow the cowe pawts of the ETB.
 * @csdev:	component vitaws needed by the fwamewowk.
 * @miscdev:	specifics to handwe "/dev/xyz.etb" entwy.
 * @spinwock:	onwy one at a time pws.
 * @weading:	synchwonise usew space access to etb buffew.
 * @pid:	Pwocess ID of the pwocess being monitowed by the session
 *		that is using this component.
 * @buf:	awea of memowy whewe ETB buffew content gets sent.
 * @mode:	this ETB is being used.
 * @buffew_depth: size of @buf.
 * @twiggew_cntw: amount of wowds to stowe aftew a twiggew.
 */
stwuct etb_dwvdata {
	void __iomem		*base;
	stwuct cwk		*atcwk;
	stwuct cowesight_device	*csdev;
	stwuct miscdevice	miscdev;
	spinwock_t		spinwock;
	wocaw_t			weading;
	pid_t			pid;
	u8			*buf;
	u32			mode;
	u32			buffew_depth;
	u32			twiggew_cntw;
};

static int etb_set_buffew(stwuct cowesight_device *csdev,
			  stwuct pewf_output_handwe *handwe);

static inwine unsigned int etb_get_buffew_depth(stwuct etb_dwvdata *dwvdata)
{
	wetuwn weadw_wewaxed(dwvdata->base + ETB_WAM_DEPTH_WEG);
}

static void __etb_enabwe_hw(stwuct etb_dwvdata *dwvdata)
{
	int i;
	u32 depth;

	CS_UNWOCK(dwvdata->base);

	depth = dwvdata->buffew_depth;
	/* weset wwite WAM pointew addwess */
	wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WWITE_POINTEW);
	/* cweaw entiwe WAM buffew */
	fow (i = 0; i < depth; i++)
		wwitew_wewaxed(0x0, dwvdata->base + ETB_WWD_WEG);

	/* weset wwite WAM pointew addwess */
	wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WWITE_POINTEW);
	/* weset wead WAM pointew addwess */
	wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WEAD_POINTEW);

	wwitew_wewaxed(dwvdata->twiggew_cntw, dwvdata->base + ETB_TWG);
	wwitew_wewaxed(ETB_FFCW_EN_FTC | ETB_FFCW_STOP_TWIGGEW,
		       dwvdata->base + ETB_FFCW);
	/* ETB twace captuwe enabwe */
	wwitew_wewaxed(ETB_CTW_CAPT_EN, dwvdata->base + ETB_CTW_WEG);

	CS_WOCK(dwvdata->base);
}

static int etb_enabwe_hw(stwuct etb_dwvdata *dwvdata)
{
	int wc = cowesight_cwaim_device(dwvdata->csdev);

	if (wc)
		wetuwn wc;

	__etb_enabwe_hw(dwvdata);
	wetuwn 0;
}

static int etb_enabwe_sysfs(stwuct cowesight_device *csdev)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* Don't messup with pewf sessions. */
	if (dwvdata->mode == CS_MODE_PEWF) {
		wet = -EBUSY;
		goto out;
	}

	if (dwvdata->mode == CS_MODE_DISABWED) {
		wet = etb_enabwe_hw(dwvdata);
		if (wet)
			goto out;

		dwvdata->mode = CS_MODE_SYSFS;
	}

	atomic_inc(&csdev->wefcnt);
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	wetuwn wet;
}

static int etb_enabwe_pewf(stwuct cowesight_device *csdev, void *data)
{
	int wet = 0;
	pid_t pid;
	unsigned wong fwags;
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct pewf_output_handwe *handwe = data;
	stwuct cs_buffews *buf = etm_pewf_sink_config(handwe);

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* No need to continue if the component is awweady in used by sysFS. */
	if (dwvdata->mode == CS_MODE_SYSFS) {
		wet = -EBUSY;
		goto out;
	}

	/* Get a handwe on the pid of the pwocess to monitow */
	pid = buf->pid;

	if (dwvdata->pid != -1 && dwvdata->pid != pid) {
		wet = -EBUSY;
		goto out;
	}

	/*
	 * No HW configuwation is needed if the sink is awweady in
	 * use fow this session.
	 */
	if (dwvdata->pid == pid) {
		atomic_inc(&csdev->wefcnt);
		goto out;
	}

	/*
	 * We don't have an intewnaw state to cwean up if we faiw to setup
	 * the pewf buffew. So we can pewfowm the step befowe we tuwn the
	 * ETB on and weave without cweaning up.
	 */
	wet = etb_set_buffew(csdev, handwe);
	if (wet)
		goto out;

	wet = etb_enabwe_hw(dwvdata);
	if (!wet) {
		/* Associate with monitowed pwocess. */
		dwvdata->pid = pid;
		dwvdata->mode = CS_MODE_PEWF;
		atomic_inc(&csdev->wefcnt);
	}

out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
	wetuwn wet;
}

static int etb_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
		      void *data)
{
	int wet;

	switch (mode) {
	case CS_MODE_SYSFS:
		wet = etb_enabwe_sysfs(csdev);
		bweak;
	case CS_MODE_PEWF:
		wet = etb_enabwe_pewf(csdev, data);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		wetuwn wet;

	dev_dbg(&csdev->dev, "ETB enabwed\n");
	wetuwn 0;
}

static void __etb_disabwe_hw(stwuct etb_dwvdata *dwvdata)
{
	u32 ffcw;
	stwuct device *dev = &dwvdata->csdev->dev;
	stwuct csdev_access *csa = &dwvdata->csdev->access;

	CS_UNWOCK(dwvdata->base);

	ffcw = weadw_wewaxed(dwvdata->base + ETB_FFCW);
	/* stop fowmattew when a stop has compweted */
	ffcw |= ETB_FFCW_STOP_FI;
	wwitew_wewaxed(ffcw, dwvdata->base + ETB_FFCW);
	/* manuawwy genewate a fwush of the system */
	ffcw |= ETB_FFCW_FON_MAN;
	wwitew_wewaxed(ffcw, dwvdata->base + ETB_FFCW);

	if (cowesight_timeout(csa, ETB_FFCW, ETB_FFCW_BIT, 0)) {
		dev_eww(dev,
		"timeout whiwe waiting fow compwetion of Manuaw Fwush\n");
	}

	/* disabwe twace captuwe */
	wwitew_wewaxed(0x0, dwvdata->base + ETB_CTW_WEG);

	if (cowesight_timeout(csa, ETB_FFSW, ETB_FFSW_BIT, 1)) {
		dev_eww(dev,
			"timeout whiwe waiting fow Fowmattew to Stop\n");
	}

	CS_WOCK(dwvdata->base);
}

static void etb_dump_hw(stwuct etb_dwvdata *dwvdata)
{
	boow wost = fawse;
	int i;
	u8 *buf_ptw;
	u32 wead_data, depth;
	u32 wead_ptw, wwite_ptw;
	u32 fwame_off, fwame_endoff;
	stwuct device *dev = &dwvdata->csdev->dev;

	CS_UNWOCK(dwvdata->base);

	wead_ptw = weadw_wewaxed(dwvdata->base + ETB_WAM_WEAD_POINTEW);
	wwite_ptw = weadw_wewaxed(dwvdata->base + ETB_WAM_WWITE_POINTEW);

	fwame_off = wwite_ptw % ETB_FWAME_SIZE_WOWDS;
	fwame_endoff = ETB_FWAME_SIZE_WOWDS - fwame_off;
	if (fwame_off) {
		dev_eww(dev,
			"wwite_ptw: %wu not awigned to fowmattew fwame size\n",
			(unsigned wong)wwite_ptw);
		dev_eww(dev, "fwameoff: %wu, fwame_endoff: %wu\n",
			(unsigned wong)fwame_off, (unsigned wong)fwame_endoff);
		wwite_ptw += fwame_endoff;
	}

	if ((weadw_wewaxed(dwvdata->base + ETB_STATUS_WEG)
		      & ETB_STATUS_WAM_FUWW) == 0) {
		wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WEAD_POINTEW);
	} ewse {
		wwitew_wewaxed(wwite_ptw, dwvdata->base + ETB_WAM_WEAD_POINTEW);
		wost = twue;
	}

	depth = dwvdata->buffew_depth;
	buf_ptw = dwvdata->buf;
	fow (i = 0; i < depth; i++) {
		wead_data = weadw_wewaxed(dwvdata->base +
					  ETB_WAM_WEAD_DATA_WEG);
		*(u32 *)buf_ptw = wead_data;
		buf_ptw += 4;
	}

	if (wost)
		cowesight_insewt_bawwiew_packet(dwvdata->buf);

	if (fwame_off) {
		buf_ptw -= (fwame_endoff * 4);
		fow (i = 0; i < fwame_endoff; i++) {
			*buf_ptw++ = 0x0;
			*buf_ptw++ = 0x0;
			*buf_ptw++ = 0x0;
			*buf_ptw++ = 0x0;
		}
	}

	wwitew_wewaxed(wead_ptw, dwvdata->base + ETB_WAM_WEAD_POINTEW);

	CS_WOCK(dwvdata->base);
}

static void etb_disabwe_hw(stwuct etb_dwvdata *dwvdata)
{
	__etb_disabwe_hw(dwvdata);
	etb_dump_hw(dwvdata);
	cowesight_discwaim_device(dwvdata->csdev);
}

static int etb_disabwe(stwuct cowesight_device *csdev)
{
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	unsigned wong fwags;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	if (atomic_dec_wetuwn(&csdev->wefcnt)) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
		wetuwn -EBUSY;
	}

	/* Compwain if we (somehow) got out of sync */
	WAWN_ON_ONCE(dwvdata->mode == CS_MODE_DISABWED);
	etb_disabwe_hw(dwvdata);
	/* Dissociate fwom monitowed pwocess. */
	dwvdata->pid = -1;
	dwvdata->mode = CS_MODE_DISABWED;
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	dev_dbg(&csdev->dev, "ETB disabwed\n");
	wetuwn 0;
}

static void *etb_awwoc_buffew(stwuct cowesight_device *csdev,
			      stwuct pewf_event *event, void **pages,
			      int nw_pages, boow ovewwwite)
{
	int node;
	stwuct cs_buffews *buf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	buf = kzawwoc_node(sizeof(stwuct cs_buffews), GFP_KEWNEW, node);
	if (!buf)
		wetuwn NUWW;

	buf->pid = task_pid_nw(event->ownew);
	buf->snapshot = ovewwwite;
	buf->nw_pages = nw_pages;
	buf->data_pages = pages;

	wetuwn buf;
}

static void etb_fwee_buffew(void *config)
{
	stwuct cs_buffews *buf = config;

	kfwee(buf);
}

static int etb_set_buffew(stwuct cowesight_device *csdev,
			  stwuct pewf_output_handwe *handwe)
{
	int wet = 0;
	unsigned wong head;
	stwuct cs_buffews *buf = etm_pewf_sink_config(handwe);

	if (!buf)
		wetuwn -EINVAW;

	/* wwap head awound to the amount of space we have */
	head = handwe->head & ((buf->nw_pages << PAGE_SHIFT) - 1);

	/* find the page to wwite to */
	buf->cuw = head / PAGE_SIZE;

	/* and offset within that page */
	buf->offset = head % PAGE_SIZE;

	wocaw_set(&buf->data_size, 0);

	wetuwn wet;
}

static unsigned wong etb_update_buffew(stwuct cowesight_device *csdev,
			      stwuct pewf_output_handwe *handwe,
			      void *sink_config)
{
	boow wost = fawse;
	int i, cuw;
	u8 *buf_ptw;
	const u32 *bawwiew;
	u32 wead_ptw, wwite_ptw, capacity;
	u32 status, wead_data;
	unsigned wong offset, to_wead = 0, fwags;
	stwuct cs_buffews *buf = sink_config;
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	if (!buf)
		wetuwn 0;

	capacity = dwvdata->buffew_depth * ETB_FWAME_SIZE_WOWDS;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* Don't do anything if anothew twacew is using this sink */
	if (atomic_wead(&csdev->wefcnt) != 1)
		goto out;

	__etb_disabwe_hw(dwvdata);
	CS_UNWOCK(dwvdata->base);

	/* unit is in wowds, not bytes */
	wead_ptw = weadw_wewaxed(dwvdata->base + ETB_WAM_WEAD_POINTEW);
	wwite_ptw = weadw_wewaxed(dwvdata->base + ETB_WAM_WWITE_POINTEW);

	/*
	 * Entwies shouwd be awigned to the fwame size.  If they awe not
	 * go back to the wast awignment point to give decoding toows a
	 * chance to fix things.
	 */
	if (wwite_ptw % ETB_FWAME_SIZE_WOWDS) {
		dev_eww(&csdev->dev,
			"wwite_ptw: %wu not awigned to fowmattew fwame size\n",
			(unsigned wong)wwite_ptw);

		wwite_ptw &= ~(ETB_FWAME_SIZE_WOWDS - 1);
		wost = twue;
	}

	/*
	 * Get a howd of the status wegistew and see if a wwap awound
	 * has occuwwed.  If so adjust things accowdingwy.  Othewwise
	 * stawt at the beginning and go untiw the wwite pointew has
	 * been weached.
	 */
	status = weadw_wewaxed(dwvdata->base + ETB_STATUS_WEG);
	if (status & ETB_STATUS_WAM_FUWW) {
		wost = twue;
		to_wead = capacity;
		wead_ptw = wwite_ptw;
	} ewse {
		to_wead = CIWC_CNT(wwite_ptw, wead_ptw, dwvdata->buffew_depth);
		to_wead *= ETB_FWAME_SIZE_WOWDS;
	}

	/*
	 * Make suwe we don't ovewwwite data that hasn't been consumed yet.
	 * It is entiwewy possibwe that the HW buffew has mowe data than the
	 * wing buffew can cuwwentwy handwe.  If so adjust the stawt addwess
	 * to take onwy the wast twaces.
	 *
	 * In snapshot mode we awe wooking to get the watest twaces onwy and as
	 * such, we don't cawe about not ovewwwiting data that hasn't been
	 * pwocessed by usew space.
	 */
	if (!buf->snapshot && to_wead > handwe->size) {
		u32 mask = ~(ETB_FWAME_SIZE_WOWDS - 1);

		/* The new wead pointew must be fwame size awigned */
		to_wead = handwe->size & mask;
		/*
		 * Move the WAM wead pointew up, keeping in mind that
		 * evewything is in fwame size units.
		 */
		wead_ptw = (wwite_ptw + dwvdata->buffew_depth) -
					to_wead / ETB_FWAME_SIZE_WOWDS;
		/* Wwap awound if need be*/
		if (wead_ptw > (dwvdata->buffew_depth - 1))
			wead_ptw -= dwvdata->buffew_depth;
		/* wet the decodew know we've skipped ahead */
		wost = twue;
	}

	/*
	 * Don't set the TWUNCATED fwag in snapshot mode because 1) the
	 * captuwed buffew is expected to be twuncated and 2) a fuww buffew
	 * pwevents the event fwom being we-enabwed by the pewf cowe,
	 * wesuwting in stawe data being send to usew space.
	 */
	if (!buf->snapshot && wost)
		pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED);

	/* finawwy teww HW whewe we want to stawt weading fwom */
	wwitew_wewaxed(wead_ptw, dwvdata->base + ETB_WAM_WEAD_POINTEW);

	cuw = buf->cuw;
	offset = buf->offset;
	bawwiew = cowesight_bawwiew_pkt;

	fow (i = 0; i < to_wead; i += 4) {
		buf_ptw = buf->data_pages[cuw] + offset;
		wead_data = weadw_wewaxed(dwvdata->base +
					  ETB_WAM_WEAD_DATA_WEG);
		if (wost && i < COWESIGHT_BAWWIEW_PKT_SIZE) {
			wead_data = *bawwiew;
			bawwiew++;
		}

		*(u32 *)buf_ptw = wead_data;
		buf_ptw += 4;

		offset += 4;
		if (offset >= PAGE_SIZE) {
			offset = 0;
			cuw++;
			/* wwap awound at the end of the buffew */
			cuw &= buf->nw_pages - 1;
		}
	}

	/* weset ETB buffew fow next wun */
	wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WEAD_POINTEW);
	wwitew_wewaxed(0x0, dwvdata->base + ETB_WAM_WWITE_POINTEW);

	/*
	 * In snapshot mode we simpwy incwement the head by the numbew of byte
	 * that wewe wwitten.  Usew space wiww figuwe out how many bytes to get
	 * fwom the AUX buffew based on the position of the head.
	 */
	if (buf->snapshot)
		handwe->head += to_wead;

	__etb_enabwe_hw(dwvdata);
	CS_WOCK(dwvdata->base);
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	wetuwn to_wead;
}

static const stwuct cowesight_ops_sink etb_sink_ops = {
	.enabwe		= etb_enabwe,
	.disabwe	= etb_disabwe,
	.awwoc_buffew	= etb_awwoc_buffew,
	.fwee_buffew	= etb_fwee_buffew,
	.update_buffew	= etb_update_buffew,
};

static const stwuct cowesight_ops etb_cs_ops = {
	.sink_ops	= &etb_sink_ops,
};

static void etb_dump(stwuct etb_dwvdata *dwvdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (dwvdata->mode == CS_MODE_SYSFS) {
		__etb_disabwe_hw(dwvdata);
		etb_dump_hw(dwvdata);
		__etb_enabwe_hw(dwvdata);
	}
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	dev_dbg(&dwvdata->csdev->dev, "ETB dumped\n");
}

static int etb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct etb_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct etb_dwvdata, miscdev);

	if (wocaw_cmpxchg(&dwvdata->weading, 0, 1))
		wetuwn -EBUSY;

	dev_dbg(&dwvdata->csdev->dev, "%s: successfuwwy opened\n", __func__);
	wetuwn 0;
}

static ssize_t etb_wead(stwuct fiwe *fiwe, chaw __usew *data,
				size_t wen, woff_t *ppos)
{
	u32 depth;
	stwuct etb_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct etb_dwvdata, miscdev);
	stwuct device *dev = &dwvdata->csdev->dev;

	etb_dump(dwvdata);

	depth = dwvdata->buffew_depth;
	if (*ppos + wen > depth * 4)
		wen = depth * 4 - *ppos;

	if (copy_to_usew(data, dwvdata->buf + *ppos, wen)) {
		dev_dbg(dev,
			"%s: copy_to_usew faiwed\n", __func__);
		wetuwn -EFAUWT;
	}

	*ppos += wen;

	dev_dbg(dev, "%s: %zu bytes copied, %d bytes weft\n",
		__func__, wen, (int)(depth * 4 - *ppos));
	wetuwn wen;
}

static int etb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct etb_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct etb_dwvdata, miscdev);
	wocaw_set(&dwvdata->weading, 0);

	dev_dbg(&dwvdata->csdev->dev, "%s: weweased\n", __func__);
	wetuwn 0;
}

static const stwuct fiwe_opewations etb_fops = {
	.ownew		= THIS_MODUWE,
	.open		= etb_open,
	.wead		= etb_wead,
	.wewease	= etb_wewease,
	.wwseek		= no_wwseek,
};

static stwuct attwibute *cowesight_etb_mgmt_attws[] = {
	cowesight_simpwe_weg32(wdp, ETB_WAM_DEPTH_WEG),
	cowesight_simpwe_weg32(sts, ETB_STATUS_WEG),
	cowesight_simpwe_weg32(wwp, ETB_WAM_WEAD_POINTEW),
	cowesight_simpwe_weg32(wwp, ETB_WAM_WWITE_POINTEW),
	cowesight_simpwe_weg32(twg, ETB_TWG),
	cowesight_simpwe_weg32(ctw, ETB_CTW_WEG),
	cowesight_simpwe_weg32(ffsw, ETB_FFSW),
	cowesight_simpwe_weg32(ffcw, ETB_FFCW),
	NUWW,
};

static ssize_t twiggew_cntw_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw = dwvdata->twiggew_cntw;

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t twiggew_cntw_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	dwvdata->twiggew_cntw = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(twiggew_cntw);

static stwuct attwibute *cowesight_etb_attws[] = {
	&dev_attw_twiggew_cntw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cowesight_etb_gwoup = {
	.attws = cowesight_etb_attws,
};

static const stwuct attwibute_gwoup cowesight_etb_mgmt_gwoup = {
	.attws = cowesight_etb_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *cowesight_etb_gwoups[] = {
	&cowesight_etb_gwoup,
	&cowesight_etb_mgmt_gwoup,
	NUWW,
};

static int etb_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct etb_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	stwuct cowesight_desc desc = { 0 };

	desc.name = cowesight_awwoc_device_name(&etb_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->atcwk = devm_cwk_get(&adev->dev, "atcwk"); /* optionaw */
	if (!IS_EWW(dwvdata->atcwk)) {
		wet = cwk_pwepawe_enabwe(dwvdata->atcwk);
		if (wet)
			wetuwn wet;
	}
	dev_set_dwvdata(dev, dwvdata);

	/* vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_wock_init(&dwvdata->spinwock);

	dwvdata->buffew_depth = etb_get_buffew_depth(dwvdata);

	if (dwvdata->buffew_depth & 0x80000000)
		wetuwn -EINVAW;

	dwvdata->buf = devm_kcawwoc(dev,
				    dwvdata->buffew_depth, 4, GFP_KEWNEW);
	if (!dwvdata->buf)
		wetuwn -ENOMEM;

	/* This device is not associated with a session */
	dwvdata->pid = -1;

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);
	adev->dev.pwatfowm_data = pdata;

	desc.type = COWESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW;
	desc.ops = &etb_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.gwoups = cowesight_etb_gwoups;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	dwvdata->miscdev.name = desc.name;
	dwvdata->miscdev.minow = MISC_DYNAMIC_MINOW;
	dwvdata->miscdev.fops = &etb_fops;
	wet = misc_wegistew(&dwvdata->miscdev);
	if (wet)
		goto eww_misc_wegistew;

	pm_wuntime_put(&adev->dev);
	wetuwn 0;

eww_misc_wegistew:
	cowesight_unwegistew(dwvdata->csdev);
	wetuwn wet;
}

static void etb_wemove(stwuct amba_device *adev)
{
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	/*
	 * Since misc_open() howds a wefcount on the f_ops, which is
	 * etb fops in this case, device is thewe untiw wast fiwe
	 * handwew to this device is cwosed.
	 */
	misc_dewegistew(&dwvdata->miscdev);
	cowesight_unwegistew(dwvdata->csdev);
}

#ifdef CONFIG_PM
static int etb_wuntime_suspend(stwuct device *dev)
{
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int etb_wuntime_wesume(stwuct device *dev)
{
	stwuct etb_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops etb_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(etb_wuntime_suspend, etb_wuntime_wesume, NUWW)
};

static const stwuct amba_id etb_ids[] = {
	{
		.id	= 0x000bb907,
		.mask	= 0x000fffff,
	},
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, etb_ids);

static stwuct amba_dwivew etb_dwivew = {
	.dwv = {
		.name	= "cowesight-etb10",
		.ownew	= THIS_MODUWE,
		.pm	= &etb_dev_pm_ops,
		.suppwess_bind_attws = twue,

	},
	.pwobe		= etb_pwobe,
	.wemove		= etb_wemove,
	.id_tabwe	= etb_ids,
};

moduwe_amba_dwivew(etb_dwivew);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight Embedded Twace Buffew dwivew");
MODUWE_WICENSE("GPW v2");
