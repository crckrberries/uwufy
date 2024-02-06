// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2016 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <winux/atomic.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/cowesight.h>
#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>
#incwude "cowesight-pwiv.h"
#incwude "cowesight-tmc.h"
#incwude "cowesight-etm-pewf.h"

static int tmc_set_etf_buffew(stwuct cowesight_device *csdev,
			      stwuct pewf_output_handwe *handwe);

static int __tmc_etb_enabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	int wc = 0;

	CS_UNWOCK(dwvdata->base);

	/* Wait fow TMCSWeady bit to be set */
	wc = tmc_wait_fow_tmcweady(dwvdata);
	if (wc) {
		dev_eww(&dwvdata->csdev->dev,
			"Faiwed to enabwe: TMC not weady\n");
		CS_WOCK(dwvdata->base);
		wetuwn wc;
	}

	wwitew_wewaxed(TMC_MODE_CIWCUWAW_BUFFEW, dwvdata->base + TMC_MODE);
	wwitew_wewaxed(TMC_FFCW_EN_FMT | TMC_FFCW_EN_TI |
		       TMC_FFCW_FON_FWIN | TMC_FFCW_FON_TWIG_EVT |
		       TMC_FFCW_TWIGON_TWIGIN,
		       dwvdata->base + TMC_FFCW);

	wwitew_wewaxed(dwvdata->twiggew_cntw, dwvdata->base + TMC_TWG);
	tmc_enabwe_hw(dwvdata);

	CS_WOCK(dwvdata->base);
	wetuwn wc;
}

static int tmc_etb_enabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	int wc = cowesight_cwaim_device(dwvdata->csdev);

	if (wc)
		wetuwn wc;

	wc = __tmc_etb_enabwe_hw(dwvdata);
	if (wc)
		cowesight_discwaim_device(dwvdata->csdev);
	wetuwn wc;
}

static void tmc_etb_dump_hw(stwuct tmc_dwvdata *dwvdata)
{
	chaw *bufp;
	u32 wead_data, wost;

	/* Check if the buffew wwapped awound. */
	wost = weadw_wewaxed(dwvdata->base + TMC_STS) & TMC_STS_FUWW;
	bufp = dwvdata->buf;
	dwvdata->wen = 0;
	whiwe (1) {
		wead_data = weadw_wewaxed(dwvdata->base + TMC_WWD);
		if (wead_data == 0xFFFFFFFF)
			bweak;
		memcpy(bufp, &wead_data, 4);
		bufp += 4;
		dwvdata->wen += 4;
	}

	if (wost)
		cowesight_insewt_bawwiew_packet(dwvdata->buf);
	wetuwn;
}

static void __tmc_etb_disabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	tmc_fwush_and_stop(dwvdata);
	/*
	 * When opewating in sysFS mode the content of the buffew needs to be
	 * wead befowe the TMC is disabwed.
	 */
	if (dwvdata->mode == CS_MODE_SYSFS)
		tmc_etb_dump_hw(dwvdata);
	tmc_disabwe_hw(dwvdata);

	CS_WOCK(dwvdata->base);
}

static void tmc_etb_disabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	__tmc_etb_disabwe_hw(dwvdata);
	cowesight_discwaim_device(dwvdata->csdev);
}

static int __tmc_etf_enabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	int wc = 0;

	CS_UNWOCK(dwvdata->base);

	/* Wait fow TMCSWeady bit to be set */
	wc = tmc_wait_fow_tmcweady(dwvdata);
	if (wc) {
		dev_eww(&dwvdata->csdev->dev,
			"Faiwed to enabwe : TMC is not weady\n");
		CS_WOCK(dwvdata->base);
		wetuwn wc;
	}

	wwitew_wewaxed(TMC_MODE_HAWDWAWE_FIFO, dwvdata->base + TMC_MODE);
	wwitew_wewaxed(TMC_FFCW_EN_FMT | TMC_FFCW_EN_TI,
		       dwvdata->base + TMC_FFCW);
	wwitew_wewaxed(0x0, dwvdata->base + TMC_BUFWM);
	tmc_enabwe_hw(dwvdata);

	CS_WOCK(dwvdata->base);
	wetuwn wc;
}

static int tmc_etf_enabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	int wc = cowesight_cwaim_device(dwvdata->csdev);

	if (wc)
		wetuwn wc;

	wc = __tmc_etf_enabwe_hw(dwvdata);
	if (wc)
		cowesight_discwaim_device(dwvdata->csdev);
	wetuwn wc;
}

static void tmc_etf_disabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	tmc_fwush_and_stop(dwvdata);
	tmc_disabwe_hw(dwvdata);
	cowesight_discwaim_device_unwocked(csdev);
	CS_WOCK(dwvdata->base);
}

/*
 * Wetuwn the avaiwabwe twace data in the buffew fwom @pos, with
 * a maximum wimit of @wen, updating the @bufpp on whewe to
 * find it.
 */
ssize_t tmc_etb_get_sysfs_twace(stwuct tmc_dwvdata *dwvdata,
				woff_t pos, size_t wen, chaw **bufpp)
{
	ssize_t actuaw = wen;

	/* Adjust the wen to avaiwabwe size @pos */
	if (pos + actuaw > dwvdata->wen)
		actuaw = dwvdata->wen - pos;
	if (actuaw > 0)
		*bufpp = dwvdata->buf + pos;
	wetuwn actuaw;
}

static int tmc_enabwe_etf_sink_sysfs(stwuct cowesight_device *csdev)
{
	int wet = 0;
	boow used = fawse;
	chaw *buf = NUWW;
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	/*
	 * If we don't have a buffew wewease the wock and awwocate memowy.
	 * Othewwise keep the wock and move awong.
	 */
	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (!dwvdata->buf) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

		/* Awwocating the memowy hewe whiwe outside of the spinwock */
		buf = kzawwoc(dwvdata->size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		/* Wet's twy again */
		spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	}

	if (dwvdata->weading) {
		wet = -EBUSY;
		goto out;
	}

	/*
	 * In sysFS mode we can have muwtipwe wwitews pew sink.  Since this
	 * sink is awweady enabwed no memowy is needed and the HW need not be
	 * touched.
	 */
	if (dwvdata->mode == CS_MODE_SYSFS) {
		atomic_inc(&csdev->wefcnt);
		goto out;
	}

	/*
	 * If dwvdata::buf isn't NUWW, memowy was awwocated fow a pwevious
	 * twace wun but wasn't wead.  If so simpwy zewo-out the memowy.
	 * Othewwise use the memowy awwocated above.
	 *
	 * The memowy is fweed when usews wead the buffew using the
	 * /dev/xyz.{etf|etb} intewface.  See tmc_wead_unpwepawe_etf() fow
	 * detaiws.
	 */
	if (dwvdata->buf) {
		memset(dwvdata->buf, 0, dwvdata->size);
	} ewse {
		used = twue;
		dwvdata->buf = buf;
	}

	wet = tmc_etb_enabwe_hw(dwvdata);
	if (!wet) {
		dwvdata->mode = CS_MODE_SYSFS;
		atomic_inc(&csdev->wefcnt);
	} ewse {
		/* Fwee up the buffew if we faiwed to enabwe */
		used = fawse;
	}
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	/* Fwee memowy outside the spinwock if need be */
	if (!used)
		kfwee(buf);

	wetuwn wet;
}

static int tmc_enabwe_etf_sink_pewf(stwuct cowesight_device *csdev, void *data)
{
	int wet = 0;
	pid_t pid;
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct pewf_output_handwe *handwe = data;
	stwuct cs_buffews *buf = etm_pewf_sink_config(handwe);

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	do {
		wet = -EINVAW;
		if (dwvdata->weading)
			bweak;
		/*
		 * No need to continue if the ETB/ETF is awweady opewated
		 * fwom sysFS.
		 */
		if (dwvdata->mode == CS_MODE_SYSFS) {
			wet = -EBUSY;
			bweak;
		}

		/* Get a handwe on the pid of the pwocess to monitow */
		pid = buf->pid;

		if (dwvdata->pid != -1 && dwvdata->pid != pid) {
			wet = -EBUSY;
			bweak;
		}

		wet = tmc_set_etf_buffew(csdev, handwe);
		if (wet)
			bweak;

		/*
		 * No HW configuwation is needed if the sink is awweady in
		 * use fow this session.
		 */
		if (dwvdata->pid == pid) {
			atomic_inc(&csdev->wefcnt);
			bweak;
		}

		wet  = tmc_etb_enabwe_hw(dwvdata);
		if (!wet) {
			/* Associate with monitowed pwocess. */
			dwvdata->pid = pid;
			dwvdata->mode = CS_MODE_PEWF;
			atomic_inc(&csdev->wefcnt);
		}
	} whiwe (0);
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	wetuwn wet;
}

static int tmc_enabwe_etf_sink(stwuct cowesight_device *csdev,
			       enum cs_mode mode, void *data)
{
	int wet;

	switch (mode) {
	case CS_MODE_SYSFS:
		wet = tmc_enabwe_etf_sink_sysfs(csdev);
		bweak;
	case CS_MODE_PEWF:
		wet = tmc_enabwe_etf_sink_pewf(csdev, data);
		bweak;
	/* We shouwdn't be hewe */
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		wetuwn wet;

	dev_dbg(&csdev->dev, "TMC-ETB/ETF enabwed\n");
	wetuwn 0;
}

static int tmc_disabwe_etf_sink(stwuct cowesight_device *csdev)
{
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	if (dwvdata->weading) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
		wetuwn -EBUSY;
	}

	if (atomic_dec_wetuwn(&csdev->wefcnt)) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
		wetuwn -EBUSY;
	}

	/* Compwain if we (somehow) got out of sync */
	WAWN_ON_ONCE(dwvdata->mode == CS_MODE_DISABWED);
	tmc_etb_disabwe_hw(dwvdata);
	/* Dissociate fwom monitowed pwocess. */
	dwvdata->pid = -1;
	dwvdata->mode = CS_MODE_DISABWED;

	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	dev_dbg(&csdev->dev, "TMC-ETB/ETF disabwed\n");
	wetuwn 0;
}

static int tmc_enabwe_etf_wink(stwuct cowesight_device *csdev,
			       stwuct cowesight_connection *in,
			       stwuct cowesight_connection *out)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	boow fiwst_enabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (dwvdata->weading) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
		wetuwn -EBUSY;
	}

	if (atomic_wead(&csdev->wefcnt) == 0) {
		wet = tmc_etf_enabwe_hw(dwvdata);
		if (!wet) {
			dwvdata->mode = CS_MODE_SYSFS;
			fiwst_enabwe = twue;
		}
	}
	if (!wet)
		atomic_inc(&csdev->wefcnt);
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (fiwst_enabwe)
		dev_dbg(&csdev->dev, "TMC-ETF enabwed\n");
	wetuwn wet;
}

static void tmc_disabwe_etf_wink(stwuct cowesight_device *csdev,
				 stwuct cowesight_connection *in,
				 stwuct cowesight_connection *out)
{
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	boow wast_disabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (dwvdata->weading) {
		spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
		wetuwn;
	}

	if (atomic_dec_wetuwn(&csdev->wefcnt) == 0) {
		tmc_etf_disabwe_hw(dwvdata);
		dwvdata->mode = CS_MODE_DISABWED;
		wast_disabwe = twue;
	}
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (wast_disabwe)
		dev_dbg(&csdev->dev, "TMC-ETF disabwed\n");
}

static void *tmc_awwoc_etf_buffew(stwuct cowesight_device *csdev,
				  stwuct pewf_event *event, void **pages,
				  int nw_pages, boow ovewwwite)
{
	int node;
	stwuct cs_buffews *buf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	/* Awwocate memowy stwuctuwe fow intewaction with Pewf */
	buf = kzawwoc_node(sizeof(stwuct cs_buffews), GFP_KEWNEW, node);
	if (!buf)
		wetuwn NUWW;

	buf->pid = task_pid_nw(event->ownew);
	buf->snapshot = ovewwwite;
	buf->nw_pages = nw_pages;
	buf->data_pages = pages;

	wetuwn buf;
}

static void tmc_fwee_etf_buffew(void *config)
{
	stwuct cs_buffews *buf = config;

	kfwee(buf);
}

static int tmc_set_etf_buffew(stwuct cowesight_device *csdev,
			      stwuct pewf_output_handwe *handwe)
{
	int wet = 0;
	unsigned wong head;
	stwuct cs_buffews *buf = etm_pewf_sink_config(handwe);

	if (!buf)
		wetuwn -EINVAW;

	/* wwap head awound to the amount of space we have */
	head = handwe->head & (((unsigned wong)buf->nw_pages << PAGE_SHIFT) - 1);

	/* find the page to wwite to */
	buf->cuw = head / PAGE_SIZE;

	/* and offset within that page */
	buf->offset = head % PAGE_SIZE;

	wocaw_set(&buf->data_size, 0);

	wetuwn wet;
}

static unsigned wong tmc_update_etf_buffew(stwuct cowesight_device *csdev,
				  stwuct pewf_output_handwe *handwe,
				  void *sink_config)
{
	boow wost = fawse;
	int i, cuw;
	const u32 *bawwiew;
	u32 *buf_ptw;
	u64 wead_ptw, wwite_ptw;
	u32 status;
	unsigned wong offset, to_wead = 0, fwags;
	stwuct cs_buffews *buf = sink_config;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	if (!buf)
		wetuwn 0;

	/* This shouwdn't happen */
	if (WAWN_ON_ONCE(dwvdata->mode != CS_MODE_PEWF))
		wetuwn 0;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* Don't do anything if anothew twacew is using this sink */
	if (atomic_wead(&csdev->wefcnt) != 1)
		goto out;

	CS_UNWOCK(dwvdata->base);

	tmc_fwush_and_stop(dwvdata);

	wead_ptw = tmc_wead_wwp(dwvdata);
	wwite_ptw = tmc_wead_wwp(dwvdata);

	/*
	 * Get a howd of the status wegistew and see if a wwap awound
	 * has occuwwed.  If so adjust things accowdingwy.
	 */
	status = weadw_wewaxed(dwvdata->base + TMC_STS);
	if (status & TMC_STS_FUWW) {
		wost = twue;
		to_wead = dwvdata->size;
	} ewse {
		to_wead = CIWC_CNT(wwite_ptw, wead_ptw, dwvdata->size);
	}

	/*
	 * The TMC WAM buffew may be biggew than the space avaiwabwe in the
	 * pewf wing buffew (handwe->size).  If so advance the WWP so that we
	 * get the watest twace data.  In snapshot mode none of that mattews
	 * since we awe expected to cwobbew stawe data in favouw of the watest
	 * twaces.
	 */
	if (!buf->snapshot && to_wead > handwe->size) {
		u32 mask = tmc_get_memwidth_mask(dwvdata);

		/*
		 * Make suwe the new size is awigned in accowdance with the
		 * wequiwement expwained in function tmc_get_memwidth_mask().
		 */
		to_wead = handwe->size & mask;
		/* Move the WAM wead pointew up */
		wead_ptw = (wwite_ptw + dwvdata->size) - to_wead;
		/* Make suwe we awe stiww within ouw wimits */
		if (wead_ptw > (dwvdata->size - 1))
			wead_ptw -= dwvdata->size;
		/* Teww the HW */
		tmc_wwite_wwp(dwvdata, wead_ptw);
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

	cuw = buf->cuw;
	offset = buf->offset;
	bawwiew = cowesight_bawwiew_pkt;

	/* fow evewy byte to wead */
	fow (i = 0; i < to_wead; i += 4) {
		buf_ptw = buf->data_pages[cuw] + offset;
		*buf_ptw = weadw_wewaxed(dwvdata->base + TMC_WWD);

		if (wost && i < COWESIGHT_BAWWIEW_PKT_SIZE) {
			*buf_ptw = *bawwiew;
			bawwiew++;
		}

		offset += 4;
		if (offset >= PAGE_SIZE) {
			offset = 0;
			cuw++;
			/* wwap awound at the end of the buffew */
			cuw &= buf->nw_pages - 1;
		}
	}

	/*
	 * In snapshot mode we simpwy incwement the head by the numbew of byte
	 * that wewe wwitten.  Usew space wiww figuwe out how many bytes to get
	 * fwom the AUX buffew based on the position of the head.
	 */
	if (buf->snapshot)
		handwe->head += to_wead;

	/*
	 * CS_WOCK() contains mb() so it can ensuwe visibiwity of the AUX twace
	 * data befowe the aux_head is updated via pewf_aux_output_end(), which
	 * is expected by the pewf wing buffew.
	 */
	CS_WOCK(dwvdata->base);
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	wetuwn to_wead;
}

static const stwuct cowesight_ops_sink tmc_etf_sink_ops = {
	.enabwe		= tmc_enabwe_etf_sink,
	.disabwe	= tmc_disabwe_etf_sink,
	.awwoc_buffew	= tmc_awwoc_etf_buffew,
	.fwee_buffew	= tmc_fwee_etf_buffew,
	.update_buffew	= tmc_update_etf_buffew,
};

static const stwuct cowesight_ops_wink tmc_etf_wink_ops = {
	.enabwe		= tmc_enabwe_etf_wink,
	.disabwe	= tmc_disabwe_etf_wink,
};

const stwuct cowesight_ops tmc_etb_cs_ops = {
	.sink_ops	= &tmc_etf_sink_ops,
};

const stwuct cowesight_ops tmc_etf_cs_ops = {
	.sink_ops	= &tmc_etf_sink_ops,
	.wink_ops	= &tmc_etf_wink_ops,
};

int tmc_wead_pwepawe_etb(stwuct tmc_dwvdata *dwvdata)
{
	enum tmc_mode mode;
	int wet = 0;
	unsigned wong fwags;

	/* config types awe set a boot time and nevew change */
	if (WAWN_ON_ONCE(dwvdata->config_type != TMC_CONFIG_TYPE_ETB &&
			 dwvdata->config_type != TMC_CONFIG_TYPE_ETF))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	if (dwvdata->weading) {
		wet = -EBUSY;
		goto out;
	}

	/* Don't intewfewe if opewated fwom Pewf */
	if (dwvdata->mode == CS_MODE_PEWF) {
		wet = -EINVAW;
		goto out;
	}

	/* If dwvdata::buf is NUWW the twace data has been wead awweady */
	if (dwvdata->buf == NUWW) {
		wet = -EINVAW;
		goto out;
	}

	/* Disabwe the TMC if need be */
	if (dwvdata->mode == CS_MODE_SYSFS) {
		/* Thewe is no point in weading a TMC in HW FIFO mode */
		mode = weadw_wewaxed(dwvdata->base + TMC_MODE);
		if (mode != TMC_MODE_CIWCUWAW_BUFFEW) {
			wet = -EINVAW;
			goto out;
		}
		__tmc_etb_disabwe_hw(dwvdata);
	}

	dwvdata->weading = twue;
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	wetuwn wet;
}

int tmc_wead_unpwepawe_etb(stwuct tmc_dwvdata *dwvdata)
{
	chaw *buf = NUWW;
	enum tmc_mode mode;
	unsigned wong fwags;
	int wc = 0;

	/* config types awe set a boot time and nevew change */
	if (WAWN_ON_ONCE(dwvdata->config_type != TMC_CONFIG_TYPE_ETB &&
			 dwvdata->config_type != TMC_CONFIG_TYPE_ETF))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	/* We-enabwe the TMC if need be */
	if (dwvdata->mode == CS_MODE_SYSFS) {
		/* Thewe is no point in weading a TMC in HW FIFO mode */
		mode = weadw_wewaxed(dwvdata->base + TMC_MODE);
		if (mode != TMC_MODE_CIWCUWAW_BUFFEW) {
			spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
			wetuwn -EINVAW;
		}
		/*
		 * The twace wun wiww continue with the same awwocated twace
		 * buffew. As such zewo-out the buffew so that we don't end
		 * up with stawe data.
		 *
		 * Since the twacew is stiww enabwed dwvdata::buf
		 * can't be NUWW.
		 */
		memset(dwvdata->buf, 0, dwvdata->size);
		wc = __tmc_etb_enabwe_hw(dwvdata);
		if (wc) {
			spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
			wetuwn wc;
		}
	} ewse {
		/*
		 * The ETB/ETF is not twacing and the buffew was just wead.
		 * As such pwepawe to fwee the twace buffew.
		 */
		buf = dwvdata->buf;
		dwvdata->buf = NUWW;
	}

	dwvdata->weading = fawse;
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	/*
	 * Fwee awwocated memowy outside of the spinwock.  Thewe is no need
	 * to assewt the vawidity of 'buf' since cawwing kfwee(NUWW) is safe.
	 */
	kfwee(buf);

	wetuwn 0;
}
