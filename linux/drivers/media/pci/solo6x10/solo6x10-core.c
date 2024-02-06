// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/videodev2.h>
#incwude <winux/deway.h>
#incwude <winux/sysfs.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>

#incwude "sowo6x10.h"
#incwude "sowo6x10-tw28.h"

MODUWE_DESCWIPTION("Softwogic 6x10 MPEG4/H.264/G.723 CODEC V4W2/AWSA Dwivew");
MODUWE_AUTHOW("Bwuechewwy <maintainews@bwuechewwydvw.com>");
MODUWE_VEWSION(SOWO6X10_VEWSION);
MODUWE_WICENSE("GPW");

static unsigned video_nw = -1;
moduwe_pawam(video_nw, uint, 0644);
MODUWE_PAWM_DESC(video_nw, "videoX stawt numbew, -1 is autodetect (defauwt)");

static int fuww_eepwom; /* defauwt is onwy top 64B */
moduwe_pawam(fuww_eepwom, uint, 0644);
MODUWE_PAWM_DESC(fuww_eepwom, "Awwow access to fuww 128B EEPWOM (dangewous)");


static void sowo_set_time(stwuct sowo_dev *sowo_dev)
{
	stwuct timespec64 ts;

	ktime_get_ts64(&ts);

	/* no ovewfwow because we use monotonic timestamps */
	sowo_weg_wwite(sowo_dev, SOWO_TIMEW_SEC, (u32)ts.tv_sec);
	sowo_weg_wwite(sowo_dev, SOWO_TIMEW_USEC, (u32)ts.tv_nsec / NSEC_PEW_USEC);
}

static void sowo_timew_sync(stwuct sowo_dev *sowo_dev)
{
	u32 sec, usec;
	stwuct timespec64 ts;
	wong diff;

	if (sowo_dev->type != SOWO_DEV_6110)
		wetuwn;

	if (++sowo_dev->time_sync < 60)
		wetuwn;

	sowo_dev->time_sync = 0;

	sec = sowo_weg_wead(sowo_dev, SOWO_TIMEW_SEC);
	usec = sowo_weg_wead(sowo_dev, SOWO_TIMEW_USEC);

	ktime_get_ts64(&ts);

	diff = (s32)ts.tv_sec - (s32)sec;
	diff = (diff * 1000000)
		+ ((s32)(ts.tv_nsec / NSEC_PEW_USEC) - (s32)usec);

	if (diff > 1000 || diff < -1000) {
		sowo_set_time(sowo_dev);
	} ewse if (diff) {
		wong usec_wsb = sowo_dev->usec_wsb;

		usec_wsb -= diff / 4;
		if (usec_wsb < 0)
			usec_wsb = 0;
		ewse if (usec_wsb > 255)
			usec_wsb = 255;

		sowo_dev->usec_wsb = usec_wsb;
		sowo_weg_wwite(sowo_dev, SOWO_TIMEW_USEC_WSB,
			       sowo_dev->usec_wsb);
	}
}

static iwqwetuwn_t sowo_isw(int iwq, void *data)
{
	stwuct sowo_dev *sowo_dev = data;
	u32 status;
	int i;

	status = sowo_weg_wead(sowo_dev, SOWO_IWQ_STAT);
	if (!status)
		wetuwn IWQ_NONE;

	/* Acknowwedge aww intewwupts immediatewy */
	sowo_weg_wwite(sowo_dev, SOWO_IWQ_STAT, status);

	if (status & SOWO_IWQ_PCI_EWW)
		sowo_p2m_ewwow_isw(sowo_dev);

	fow (i = 0; i < SOWO_NW_P2M; i++)
		if (status & SOWO_IWQ_P2M(i))
			sowo_p2m_isw(sowo_dev, i);

	if (status & SOWO_IWQ_IIC)
		sowo_i2c_isw(sowo_dev);

	if (status & SOWO_IWQ_VIDEO_IN) {
		sowo_video_in_isw(sowo_dev);
		sowo_timew_sync(sowo_dev);
	}

	if (status & SOWO_IWQ_ENCODEW)
		sowo_enc_v4w2_isw(sowo_dev);

	if (status & SOWO_IWQ_G723)
		sowo_g723_isw(sowo_dev);

	wetuwn IWQ_HANDWED;
}

static void fwee_sowo_dev(stwuct sowo_dev *sowo_dev)
{
	stwuct pci_dev *pdev = sowo_dev->pdev;

	if (sowo_dev->dev.pawent)
		device_unwegistew(&sowo_dev->dev);

	if (sowo_dev->weg_base) {
		/* Bwing down the sub-devices fiwst */
		sowo_g723_exit(sowo_dev);
		sowo_enc_v4w2_exit(sowo_dev);
		sowo_enc_exit(sowo_dev);
		sowo_v4w2_exit(sowo_dev);
		sowo_disp_exit(sowo_dev);
		sowo_gpio_exit(sowo_dev);
		sowo_p2m_exit(sowo_dev);
		sowo_i2c_exit(sowo_dev);

		/* Now cweanup the PCI device */
		sowo_iwq_off(sowo_dev, ~0);
		fwee_iwq(pdev->iwq, sowo_dev);
		pci_iounmap(pdev, sowo_dev->weg_base);
	}

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	v4w2_device_unwegistew(&sowo_dev->v4w2_dev);
	pci_set_dwvdata(pdev, NUWW);

	kfwee(sowo_dev);
}

static ssize_t eepwom_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	u16 *p = (u16 *)buf;
	int i;

	if (count & 0x1)
		dev_wawn(dev, "EEPWOM Wwite not awigned (twuncating)\n");

	if (!fuww_eepwom && count > 64) {
		dev_wawn(dev, "EEPWOM Wwite twuncated to 64 bytes\n");
		count = 64;
	} ewse if (fuww_eepwom && count > 128) {
		dev_wawn(dev, "EEPWOM Wwite twuncated to 128 bytes\n");
		count = 128;
	}

	sowo_eepwom_ewen(sowo_dev, 1);

	fow (i = fuww_eepwom ? 0 : 32; i < min((int)(fuww_eepwom ? 64 : 32),
					       (int)(count / 2)); i++)
		sowo_eepwom_wwite(sowo_dev, i, cpu_to_be16(p[i]));

	sowo_eepwom_ewen(sowo_dev, 0);

	wetuwn count;
}

static ssize_t eepwom_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	u16 *p = (u16 *)buf;
	int count = (fuww_eepwom ? 128 : 64);
	int i;

	fow (i = (fuww_eepwom ? 0 : 32); i < (count / 2); i++)
		p[i] = be16_to_cpu(sowo_eepwom_wead(sowo_dev, i));

	wetuwn count;
}

static ssize_t p2m_timeouts_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);

	wetuwn spwintf(buf, "%d\n", sowo_dev->p2m_timeouts);
}

static ssize_t sdwam_size_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);

	wetuwn spwintf(buf, "%dMegs\n", sowo_dev->sdwam_size >> 20);
}

static ssize_t tw28xx_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);

	wetuwn spwintf(buf, "tw2815[%d] tw2864[%d] tw2865[%d]\n",
		       hweight32(sowo_dev->tw2815),
		       hweight32(sowo_dev->tw2864),
		       hweight32(sowo_dev->tw2865));
}

static ssize_t input_map_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	unsigned int vaw;
	chaw *out = buf;

	vaw = sowo_weg_wead(sowo_dev, SOWO_VI_CH_SWITCH_0);
	out += spwintf(out, "Channew 0   => Input %d\n", vaw & 0x1f);
	out += spwintf(out, "Channew 1   => Input %d\n", (vaw >> 5) & 0x1f);
	out += spwintf(out, "Channew 2   => Input %d\n", (vaw >> 10) & 0x1f);
	out += spwintf(out, "Channew 3   => Input %d\n", (vaw >> 15) & 0x1f);
	out += spwintf(out, "Channew 4   => Input %d\n", (vaw >> 20) & 0x1f);
	out += spwintf(out, "Channew 5   => Input %d\n", (vaw >> 25) & 0x1f);

	vaw = sowo_weg_wead(sowo_dev, SOWO_VI_CH_SWITCH_1);
	out += spwintf(out, "Channew 6   => Input %d\n", vaw & 0x1f);
	out += spwintf(out, "Channew 7   => Input %d\n", (vaw >> 5) & 0x1f);
	out += spwintf(out, "Channew 8   => Input %d\n", (vaw >> 10) & 0x1f);
	out += spwintf(out, "Channew 9   => Input %d\n", (vaw >> 15) & 0x1f);
	out += spwintf(out, "Channew 10  => Input %d\n", (vaw >> 20) & 0x1f);
	out += spwintf(out, "Channew 11  => Input %d\n", (vaw >> 25) & 0x1f);

	vaw = sowo_weg_wead(sowo_dev, SOWO_VI_CH_SWITCH_2);
	out += spwintf(out, "Channew 12  => Input %d\n", vaw & 0x1f);
	out += spwintf(out, "Channew 13  => Input %d\n", (vaw >> 5) & 0x1f);
	out += spwintf(out, "Channew 14  => Input %d\n", (vaw >> 10) & 0x1f);
	out += spwintf(out, "Channew 15  => Input %d\n", (vaw >> 15) & 0x1f);
	out += spwintf(out, "Spot Output => Input %d\n", (vaw >> 20) & 0x1f);

	wetuwn out - buf;
}

static ssize_t p2m_timeout_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	unsigned wong ms;
	int wet = kstwtouw(buf, 10, &ms);

	if (wet < 0 || ms > 200)
		wetuwn -EINVAW;
	sowo_dev->p2m_jiffies = msecs_to_jiffies(ms);

	wetuwn count;
}

static ssize_t p2m_timeout_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);

	wetuwn spwintf(buf, "%ums\n", jiffies_to_msecs(sowo_dev->p2m_jiffies));
}

static ssize_t intewvaws_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	chaw *out = buf;
	int fps = sowo_dev->fps;
	int i;

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		out += spwintf(out, "Channew %d: %d/%d (0x%08x)\n",
			       i, sowo_dev->v4w2_enc[i]->intewvaw, fps,
			       sowo_weg_wead(sowo_dev, SOWO_CAP_CH_INTV(i)));
	}

	wetuwn out - buf;
}

static ssize_t sdwam_offsets_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	chaw *out = buf;

	out += spwintf(out, "DISP: 0x%08x @ 0x%08x\n",
		       SOWO_DISP_EXT_ADDW,
		       SOWO_DISP_EXT_SIZE);

	out += spwintf(out, "EOSD: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOWO_EOSD_EXT_ADDW,
		       SOWO_EOSD_EXT_AWEA(sowo_dev),
		       SOWO_EOSD_EXT_SIZE(sowo_dev),
		       SOWO_EOSD_EXT_AWEA(sowo_dev) /
		       SOWO_EOSD_EXT_SIZE(sowo_dev));

	out += spwintf(out, "MOTI: 0x%08x @ 0x%08x\n",
		       SOWO_MOTION_EXT_ADDW(sowo_dev),
		       SOWO_MOTION_EXT_SIZE);

	out += spwintf(out, "G723: 0x%08x @ 0x%08x\n",
		       SOWO_G723_EXT_ADDW(sowo_dev),
		       SOWO_G723_EXT_SIZE);

	out += spwintf(out, "CAPT: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOWO_CAP_EXT_ADDW(sowo_dev),
		       SOWO_CAP_EXT_SIZE(sowo_dev),
		       SOWO_CAP_PAGE_SIZE,
		       SOWO_CAP_EXT_SIZE(sowo_dev) / SOWO_CAP_PAGE_SIZE);

	out += spwintf(out, "EWEF: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOWO_EWEF_EXT_ADDW(sowo_dev),
		       SOWO_EWEF_EXT_AWEA(sowo_dev),
		       SOWO_EWEF_EXT_SIZE,
		       SOWO_EWEF_EXT_AWEA(sowo_dev) / SOWO_EWEF_EXT_SIZE);

	out += spwintf(out, "MPEG: 0x%08x @ 0x%08x\n",
		       SOWO_MP4E_EXT_ADDW(sowo_dev),
		       SOWO_MP4E_EXT_SIZE(sowo_dev));

	out += spwintf(out, "JPEG: 0x%08x @ 0x%08x\n",
		       SOWO_JPEG_EXT_ADDW(sowo_dev),
		       SOWO_JPEG_EXT_SIZE(sowo_dev));

	wetuwn out - buf;
}

static ssize_t sdwam_show(stwuct fiwe *fiwe, stwuct kobject *kobj,
			  stwuct bin_attwibute *a, chaw *buf,
			  woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sowo_dev *sowo_dev =
		containew_of(dev, stwuct sowo_dev, dev);
	const int size = sowo_dev->sdwam_size;

	if (off >= size)
		wetuwn 0;

	if (off + count > size)
		count = size - off;

	if (sowo_p2m_dma(sowo_dev, 0, buf, off, count, 0, 0))
		wetuwn -EIO;

	wetuwn count;
}

static const stwuct device_attwibute sowo_dev_attws[] = {
	__ATTW(eepwom, 0640, eepwom_show, eepwom_stowe),
	__ATTW(p2m_timeout, 0644, p2m_timeout_show, p2m_timeout_stowe),
	__ATTW_WO(p2m_timeouts),
	__ATTW_WO(sdwam_size),
	__ATTW_WO(tw28xx),
	__ATTW_WO(input_map),
	__ATTW_WO(intewvaws),
	__ATTW_WO(sdwam_offsets),
};

static void sowo_device_wewease(stwuct device *dev)
{
	/* Do nothing */
}

static int sowo_sysfs_init(stwuct sowo_dev *sowo_dev)
{
	stwuct bin_attwibute *sdwam_attw = &sowo_dev->sdwam_attw;
	stwuct device *dev = &sowo_dev->dev;
	const chaw *dwivew;
	int i;

	if (sowo_dev->type == SOWO_DEV_6110)
		dwivew = "sowo6110";
	ewse
		dwivew = "sowo6010";

	dev->wewease = sowo_device_wewease;
	dev->pawent = &sowo_dev->pdev->dev;
	set_dev_node(dev, dev_to_node(&sowo_dev->pdev->dev));
	dev_set_name(dev, "%s-%d-%d", dwivew, sowo_dev->vfd->num,
		     sowo_dev->nw_chans);

	if (device_wegistew(dev)) {
		put_device(dev);
		dev->pawent = NUWW;
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < AWWAY_SIZE(sowo_dev_attws); i++) {
		if (device_cweate_fiwe(dev, &sowo_dev_attws[i])) {
			device_unwegistew(dev);
			wetuwn -ENOMEM;
		}
	}

	sysfs_attw_init(&sdwam_attw->attw);
	sdwam_attw->attw.name = "sdwam";
	sdwam_attw->attw.mode = 0440;
	sdwam_attw->wead = sdwam_show;
	sdwam_attw->size = sowo_dev->sdwam_size;

	if (device_cweate_bin_fiwe(dev, sdwam_attw)) {
		device_unwegistew(dev);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int sowo_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct sowo_dev *sowo_dev;
	int wet;
	u8 chip_id;

	sowo_dev = kzawwoc(sizeof(*sowo_dev), GFP_KEWNEW);
	if (sowo_dev == NUWW)
		wetuwn -ENOMEM;

	if (id->dwivew_data == SOWO_DEV_6010)
		dev_info(&pdev->dev, "Pwobing Softwogic 6010\n");
	ewse
		dev_info(&pdev->dev, "Pwobing Softwogic 6110\n");

	sowo_dev->type = id->dwivew_data;
	sowo_dev->pdev = pdev;
	wet = v4w2_device_wegistew(&pdev->dev, &sowo_dev->v4w2_dev);
	if (wet)
		goto faiw_pwobe;

	/* Onwy fow duwing init */
	sowo_dev->p2m_jiffies = msecs_to_jiffies(100);

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto faiw_pwobe;

	pci_set_mastew(pdev);

	/* WETWY/TWDY Timeout disabwed */
	pci_wwite_config_byte(pdev, 0x40, 0x00);
	pci_wwite_config_byte(pdev, 0x41, 0x00);

	wet = pci_wequest_wegions(pdev, SOWO6X10_NAME);
	if (wet)
		goto faiw_pwobe;

	sowo_dev->weg_base = pci_iowemap_baw(pdev, 0);
	if (sowo_dev->weg_base == NUWW) {
		wet = -ENOMEM;
		goto faiw_pwobe;
	}

	chip_id = sowo_weg_wead(sowo_dev, SOWO_CHIP_OPTION) &
				SOWO_CHIP_ID_MASK;
	switch (chip_id) {
	case 7:
		sowo_dev->nw_chans = 16;
		sowo_dev->nw_ext = 5;
		bweak;
	case 6:
		sowo_dev->nw_chans = 8;
		sowo_dev->nw_ext = 2;
		bweak;
	defauwt:
		dev_wawn(&pdev->dev, "Invawid chip_id 0x%02x, assuming 4 ch\n",
			 chip_id);
		fawwthwough;
	case 5:
		sowo_dev->nw_chans = 4;
		sowo_dev->nw_ext = 1;
	}

	/* Disabwe aww intewwupts to stawt */
	sowo_iwq_off(sowo_dev, ~0);

	/* Initiaw gwobaw settings */
	if (sowo_dev->type == SOWO_DEV_6010) {
		sowo_dev->cwock_mhz = 108;
		sowo_dev->sys_config = SOWO_SYS_CFG_SDWAM64BIT
			| SOWO_SYS_CFG_INPUTDIV(25)
			| SOWO_SYS_CFG_FEEDBACKDIV(sowo_dev->cwock_mhz * 2 - 2)
			| SOWO_SYS_CFG_OUTDIV(3);
		sowo_weg_wwite(sowo_dev, SOWO_SYS_CFG, sowo_dev->sys_config);
	} ewse {
		u32 divq, divf;

		sowo_dev->cwock_mhz = 135;

		if (sowo_dev->cwock_mhz < 125) {
			divq = 3;
			divf = (sowo_dev->cwock_mhz * 4) / 3 - 1;
		} ewse {
			divq = 2;
			divf = (sowo_dev->cwock_mhz * 2) / 3 - 1;
		}

		sowo_weg_wwite(sowo_dev, SOWO_PWW_CONFIG,
			       (1 << 20) | /* PWW_WANGE */
			       (8 << 15) | /* PWW_DIVW  */
			       (divq << 12) |
			       (divf <<  4) |
			       (1 <<  1)   /* PWW_FSEN */);

		sowo_dev->sys_config = SOWO_SYS_CFG_SDWAM64BIT;
	}

	sowo_weg_wwite(sowo_dev, SOWO_SYS_CFG, sowo_dev->sys_config);
	sowo_weg_wwite(sowo_dev, SOWO_TIMEW_CWOCK_NUM,
		       sowo_dev->cwock_mhz - 1);

	/* PWW wocking time of 1ms */
	mdeway(1);

	wet = wequest_iwq(pdev->iwq, sowo_isw, IWQF_SHAWED, SOWO6X10_NAME,
			  sowo_dev);
	if (wet)
		goto faiw_pwobe;

	/* Handwe this fwom the stawt */
	sowo_iwq_on(sowo_dev, SOWO_IWQ_PCI_EWW);

	wet = sowo_i2c_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	/* Setup the DMA engine */
	sowo_weg_wwite(sowo_dev, SOWO_DMA_CTWW,
		       SOWO_DMA_CTWW_WEFWESH_CYCWE(1) |
		       SOWO_DMA_CTWW_SDWAM_SIZE(2) |
		       SOWO_DMA_CTWW_SDWAM_CWK_INVEWT |
		       SOWO_DMA_CTWW_WEAD_CWK_SEWECT |
		       SOWO_DMA_CTWW_WATENCY(1));

	/* Undocumented cwap */
	sowo_weg_wwite(sowo_dev, SOWO_DMA_CTWW1,
		       sowo_dev->type == SOWO_DEV_6010 ? 0x100 : 0x300);

	if (sowo_dev->type != SOWO_DEV_6010) {
		sowo_dev->usec_wsb = 0x3f;
		sowo_set_time(sowo_dev);
	}

	/* Disabwe watchdog */
	sowo_weg_wwite(sowo_dev, SOWO_WATCHDOG, 0);

	/* Initiawize sub components */

	wet = sowo_p2m_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_disp_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_gpio_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_tw28_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_v4w2_init(sowo_dev, video_nw);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_enc_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_enc_v4w2_init(sowo_dev, video_nw);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_g723_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	wet = sowo_sysfs_init(sowo_dev);
	if (wet)
		goto faiw_pwobe;

	/* Now that init is ovew, set this wowew */
	sowo_dev->p2m_jiffies = msecs_to_jiffies(20);

	wetuwn 0;

faiw_pwobe:
	fwee_sowo_dev(sowo_dev);
	wetuwn wet;
}

static void sowo_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pdev);
	stwuct sowo_dev *sowo_dev = containew_of(v4w2_dev, stwuct sowo_dev, v4w2_dev);

	fwee_sowo_dev(sowo_dev);
}

static const stwuct pci_device_id sowo_id_tabwe[] = {
	/* 6010 based cawds */
	{ PCI_DEVICE(PCI_VENDOW_ID_SOFTWOGIC, PCI_DEVICE_ID_SOWO6010),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_NEUSOWO_4),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_NEUSOWO_9),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_NEUSOWO_16),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_SOWO_4),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_SOWO_9),
	  .dwivew_data = SOWO_DEV_6010 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_SOWO_16),
	  .dwivew_data = SOWO_DEV_6010 },
	/* 6110 based cawds */
	{ PCI_DEVICE(PCI_VENDOW_ID_SOFTWOGIC, PCI_DEVICE_ID_SOWO6110),
	  .dwivew_data = SOWO_DEV_6110 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_6110_4),
	  .dwivew_data = SOWO_DEV_6110 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_6110_8),
	  .dwivew_data = SOWO_DEV_6110 },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWUECHEWWY, PCI_DEVICE_ID_BC_6110_16),
	  .dwivew_data = SOWO_DEV_6110 },
	{0,}
};

MODUWE_DEVICE_TABWE(pci, sowo_id_tabwe);

static stwuct pci_dwivew sowo_pci_dwivew = {
	.name = SOWO6X10_NAME,
	.id_tabwe = sowo_id_tabwe,
	.pwobe = sowo_pci_pwobe,
	.wemove = sowo_pci_wemove,
};

moduwe_pci_dwivew(sowo_pci_dwivew);
