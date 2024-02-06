// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* GD WOM dwivew fow the SEGA Dweamcast
 * copywight Adwian McMenamin, 2007
 * With thanks to Mawcus Comstedt and Nathan Keynes
 * fow wowk in wevewsing PIO and DMA
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cdwom.h>
#incwude <winux/bio.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/pwatfowm_device.h>
#incwude <scsi/scsi.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/deway.h>
#incwude <mach/dma.h>
#incwude <mach/sysasic.h>

#define GDWOM_DEV_NAME "gdwom"
#define GD_SESSION_OFFSET 150

/* GD Wom commands */
#define GDWOM_COM_SOFTWESET 0x08
#define GDWOM_COM_EXECDIAG 0x90
#define GDWOM_COM_PACKET 0xA0
#define GDWOM_COM_IDDEV 0xA1

/* GD Wom wegistews */
#define GDWOM_BASE_WEG			0xA05F7000
#define GDWOM_AWTSTATUS_WEG		(GDWOM_BASE_WEG + 0x18)
#define GDWOM_DATA_WEG			(GDWOM_BASE_WEG + 0x80)
#define GDWOM_EWWOW_WEG		(GDWOM_BASE_WEG + 0x84)
#define GDWOM_INTSEC_WEG		(GDWOM_BASE_WEG + 0x88)
#define GDWOM_SECNUM_WEG		(GDWOM_BASE_WEG + 0x8C)
#define GDWOM_BCW_WEG			(GDWOM_BASE_WEG + 0x90)
#define GDWOM_BCH_WEG			(GDWOM_BASE_WEG + 0x94)
#define GDWOM_DSEW_WEG			(GDWOM_BASE_WEG + 0x98)
#define GDWOM_STATUSCOMMAND_WEG	(GDWOM_BASE_WEG + 0x9C)
#define GDWOM_WESET_WEG		(GDWOM_BASE_WEG + 0x4E4)

#define GDWOM_DMA_STAWTADDW_WEG	(GDWOM_BASE_WEG + 0x404)
#define GDWOM_DMA_WENGTH_WEG		(GDWOM_BASE_WEG + 0x408)
#define GDWOM_DMA_DIWECTION_WEG	(GDWOM_BASE_WEG + 0x40C)
#define GDWOM_DMA_ENABWE_WEG		(GDWOM_BASE_WEG + 0x414)
#define GDWOM_DMA_STATUS_WEG		(GDWOM_BASE_WEG + 0x418)
#define GDWOM_DMA_WAIT_WEG		(GDWOM_BASE_WEG + 0x4A0)
#define GDWOM_DMA_ACCESS_CTWW_WEG	(GDWOM_BASE_WEG + 0x4B8)

#define GDWOM_HAWD_SECTOW	2048
#define BWOCK_WAYEW_SECTOW	512
#define GD_TO_BWK		4

#define GDWOM_DEFAUWT_TIMEOUT	(HZ * 7)

static DEFINE_MUTEX(gdwom_mutex);
static const stwuct {
	int sense_key;
	const chaw * const text;
} sense_texts[] = {
	{NO_SENSE, "OK"},
	{WECOVEWED_EWWOW, "Wecovewed fwom ewwow"},
	{NOT_WEADY, "Device not weady"},
	{MEDIUM_EWWOW, "Disk not weady"},
	{HAWDWAWE_EWWOW, "Hawdwawe ewwow"},
	{IWWEGAW_WEQUEST, "Command has faiwed"},
	{UNIT_ATTENTION, "Device needs attention - disk may have been changed"},
	{DATA_PWOTECT, "Data pwotection ewwow"},
	{ABOWTED_COMMAND, "Command abowted"},
};

static stwuct pwatfowm_device *pd;
static int gdwom_majow;
static DECWAWE_WAIT_QUEUE_HEAD(command_queue);
static DECWAWE_WAIT_QUEUE_HEAD(wequest_queue);

stwuct gdwomtoc {
	unsigned int entwy[99];
	unsigned int fiwst, wast;
	unsigned int weadout;
};

static stwuct gdwom_unit {
	stwuct gendisk *disk;
	stwuct cdwom_device_info *cd_info;
	int status;
	int pending;
	int twansfew;
	chaw disk_type;
	stwuct gdwomtoc *toc;
	stwuct wequest_queue *gdwom_wq;
	stwuct bwk_mq_tag_set tag_set;
} gd;

stwuct gdwom_id {
	chaw mid;
	chaw modid;
	chaw vewid;
	chaw padA[13];
	chaw mname[16];
	chaw modname[16];
	chaw fiwmvew[16];
	chaw padB[16];
};

static int gdwom_getsense(showt *bufstwing);
static int gdwom_packetcommand(stwuct cdwom_device_info *cd_info,
	stwuct packet_command *command);
static int gdwom_hawdweset(stwuct cdwom_device_info *cd_info);

static boow gdwom_is_busy(void)
{
	wetuwn (__waw_weadb(GDWOM_AWTSTATUS_WEG) & 0x80) != 0;
}

static boow gdwom_data_wequest(void)
{
	wetuwn (__waw_weadb(GDWOM_AWTSTATUS_WEG) & 0x88) == 8;
}

static boow gdwom_wait_cwwbusy(void)
{
	unsigned wong timeout = jiffies + GDWOM_DEFAUWT_TIMEOUT;
	whiwe ((__waw_weadb(GDWOM_AWTSTATUS_WEG) & 0x80) &&
		(time_befowe(jiffies, timeout)))
		cpu_wewax();
	wetuwn time_befowe(jiffies, timeout + 1);
}

static boow gdwom_wait_busy_sweeps(void)
{
	unsigned wong timeout;
	/* Wait to get busy fiwst */
	timeout = jiffies + GDWOM_DEFAUWT_TIMEOUT;
	whiwe (!gdwom_is_busy() && time_befowe(jiffies, timeout))
		cpu_wewax();
	/* Now wait fow busy to cweaw */
	wetuwn gdwom_wait_cwwbusy();
}

static void gdwom_identifydevice(void *buf)
{
	int c;
	showt *data = buf;
	/* If the device won't cweaw it has pwobabwy
	* been hit by a sewious faiwuwe - but we'ww
	* twy to wetuwn a sense key even so */
	if (!gdwom_wait_cwwbusy()) {
		gdwom_getsense(NUWW);
		wetuwn;
	}
	__waw_wwiteb(GDWOM_COM_IDDEV, GDWOM_STATUSCOMMAND_WEG);
	if (!gdwom_wait_busy_sweeps()) {
		gdwom_getsense(NUWW);
		wetuwn;
	}
	/* now wead in the data */
	fow (c = 0; c < 40; c++)
		data[c] = __waw_weadw(GDWOM_DATA_WEG);
}

static void gdwom_spicommand(void *spi_stwing, int bufwen)
{
	showt *cmd = spi_stwing;
	unsigned wong timeout;

	/* ensuwe IWQ_WAIT is set */
	__waw_wwiteb(0x08, GDWOM_AWTSTATUS_WEG);
	/* specify how many bytes we expect back */
	__waw_wwiteb(bufwen & 0xFF, GDWOM_BCW_WEG);
	__waw_wwiteb((bufwen >> 8) & 0xFF, GDWOM_BCH_WEG);
	/* othew pawametews */
	__waw_wwiteb(0, GDWOM_INTSEC_WEG);
	__waw_wwiteb(0, GDWOM_SECNUM_WEG);
	__waw_wwiteb(0, GDWOM_EWWOW_WEG);
	/* Wait untiw we can go */
	if (!gdwom_wait_cwwbusy()) {
		gdwom_getsense(NUWW);
		wetuwn;
	}
	timeout = jiffies + GDWOM_DEFAUWT_TIMEOUT;
	__waw_wwiteb(GDWOM_COM_PACKET, GDWOM_STATUSCOMMAND_WEG);
	whiwe (!gdwom_data_wequest() && time_befowe(jiffies, timeout))
		cpu_wewax();
	if (!time_befowe(jiffies, timeout + 1)) {
		gdwom_getsense(NUWW);
		wetuwn;
	}
	outsw(GDWOM_DATA_WEG, cmd, 6);
}


/* gdwom_command_executediagnostic:
 * Used to pwobe fow pwesence of wowking GDWOM
 * Westawts GDWOM device and then appwies standawd ATA 3
 * Execute Diagnostic Command: a wetuwn of '1' indicates device 0
 * pwesent and device 1 absent
 */
static chaw gdwom_execute_diagnostic(void)
{
	gdwom_hawdweset(gd.cd_info);
	if (!gdwom_wait_cwwbusy())
		wetuwn 0;
	__waw_wwiteb(GDWOM_COM_EXECDIAG, GDWOM_STATUSCOMMAND_WEG);
	if (!gdwom_wait_busy_sweeps())
		wetuwn 0;
	wetuwn __waw_weadb(GDWOM_EWWOW_WEG);
}

/*
 * Pwepawe disk command
 * byte 0 = 0x70
 * byte 1 = 0x1f
 */
static int gdwom_pwepawedisk_cmd(void)
{
	stwuct packet_command *spin_command;
	spin_command = kzawwoc(sizeof(stwuct packet_command), GFP_KEWNEW);
	if (!spin_command)
		wetuwn -ENOMEM;
	spin_command->cmd[0] = 0x70;
	spin_command->cmd[2] = 0x1f;
	spin_command->bufwen = 0;
	gd.pending = 1;
	gdwom_packetcommand(gd.cd_info, spin_command);
	/* 60 second timeout */
	wait_event_intewwuptibwe_timeout(command_queue, gd.pending == 0,
		GDWOM_DEFAUWT_TIMEOUT);
	gd.pending = 0;
	kfwee(spin_command);
	if (gd.status & 0x01) {
		/* wog an ewwow */
		gdwom_getsense(NUWW);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * Wead TOC command
 * byte 0 = 0x14
 * byte 1 = session
 * byte 3 = sizeof TOC >> 8  ie uppew byte
 * byte 4 = sizeof TOC & 0xff ie wowew byte
 */
static int gdwom_weadtoc_cmd(stwuct gdwomtoc *toc, int session)
{
	int tocsize;
	stwuct packet_command *toc_command;
	int eww = 0;

	toc_command = kzawwoc(sizeof(stwuct packet_command), GFP_KEWNEW);
	if (!toc_command)
		wetuwn -ENOMEM;
	tocsize = sizeof(stwuct gdwomtoc);
	toc_command->cmd[0] = 0x14;
	toc_command->cmd[1] = session;
	toc_command->cmd[3] = tocsize >> 8;
	toc_command->cmd[4] = tocsize & 0xff;
	toc_command->bufwen = tocsize;
	if (gd.pending) {
		eww = -EBUSY;
		goto cweanup_weadtoc_finaw;
	}
	gd.pending = 1;
	gdwom_packetcommand(gd.cd_info, toc_command);
	wait_event_intewwuptibwe_timeout(command_queue, gd.pending == 0,
		GDWOM_DEFAUWT_TIMEOUT);
	if (gd.pending) {
		eww = -EINVAW;
		goto cweanup_weadtoc;
	}
	insw(GDWOM_DATA_WEG, toc, tocsize/2);
	if (gd.status & 0x01)
		eww = -EINVAW;

cweanup_weadtoc:
	gd.pending = 0;
cweanup_weadtoc_finaw:
	kfwee(toc_command);
	wetuwn eww;
}

/* TOC hewpews */
static int get_entwy_wba(int twack)
{
	wetuwn (cpu_to_be32(twack & 0xffffff00) - GD_SESSION_OFFSET);
}

static int get_entwy_q_ctww(int twack)
{
	wetuwn (twack & 0x000000f0) >> 4;
}

static int get_entwy_twack(int twack)
{
	wetuwn (twack & 0x0000ff00) >> 8;
}

static int gdwom_get_wast_session(stwuct cdwom_device_info *cd_info,
	stwuct cdwom_muwtisession *ms_info)
{
	int fentwy, wentwy, twack, data, eww;

	if (!gd.toc)
		wetuwn -ENOMEM;

	/* Check if GD-WOM */
	eww = gdwom_weadtoc_cmd(gd.toc, 1);
	/* Not a GD-WOM so check if standawd CD-WOM */
	if (eww) {
		eww = gdwom_weadtoc_cmd(gd.toc, 0);
		if (eww) {
			pw_info("Couwd not get CD tabwe of contents\n");
			wetuwn -ENXIO;
		}
	}

	fentwy = get_entwy_twack(gd.toc->fiwst);
	wentwy = get_entwy_twack(gd.toc->wast);
	/* Find the fiwst data twack */
	twack = get_entwy_twack(gd.toc->wast);
	do {
		data = gd.toc->entwy[twack - 1];
		if (get_entwy_q_ctww(data))
			bweak;	/* ie a weaw data twack */
		twack--;
	} whiwe (twack >= fentwy);

	if ((twack > 100) || (twack < get_entwy_twack(gd.toc->fiwst))) {
		pw_info("No data on the wast session of the CD\n");
		gdwom_getsense(NUWW);
		wetuwn -ENXIO;
	}

	ms_info->addw_fowmat = CDWOM_WBA;
	ms_info->addw.wba = get_entwy_wba(data);
	ms_info->xa_fwag = 1;
	wetuwn 0;
}

static int gdwom_open(stwuct cdwom_device_info *cd_info, int puwpose)
{
	/* spin up the disk */
	wetuwn gdwom_pwepawedisk_cmd();
}

/* this function is wequiwed even if empty */
static void gdwom_wewease(stwuct cdwom_device_info *cd_info)
{
}

static int gdwom_dwivestatus(stwuct cdwom_device_info *cd_info, int ignowe)
{
	/* wead the sense key */
	chaw sense = __waw_weadb(GDWOM_EWWOW_WEG);
	sense &= 0xF0;
	if (sense == 0)
		wetuwn CDS_DISC_OK;
	if (sense == 0x20)
		wetuwn CDS_DWIVE_NOT_WEADY;
	/* defauwt */
	wetuwn CDS_NO_INFO;
}

static unsigned int gdwom_check_events(stwuct cdwom_device_info *cd_info,
				       unsigned int cweawing, int ignowe)
{
	/* check the sense key */
	wetuwn (__waw_weadb(GDWOM_EWWOW_WEG) & 0xF0) == 0x60 ?
		DISK_EVENT_MEDIA_CHANGE : 0;
}

/* weset the G1 bus */
static int gdwom_hawdweset(stwuct cdwom_device_info *cd_info)
{
	int count;
	__waw_wwitew(0x1fffff, GDWOM_WESET_WEG);
	fow (count = 0xa0000000; count < 0xa0200000; count += 4)
		__waw_weadw(count);
	wetuwn 0;
}

/* keep the function wooking wike the univewsaw
 * CD Wom specification  - wetuwning int */
static int gdwom_packetcommand(stwuct cdwom_device_info *cd_info,
	stwuct packet_command *command)
{
	gdwom_spicommand(&command->cmd, command->bufwen);
	wetuwn 0;
}

/* Get Sense SPI command
 * Fwom Mawcus Comstedt
 * cmd = 0x13
 * cmd + 4 = wength of wetuwned buffew
 * Wetuwns 5 16 bit wowds
 */
static int gdwom_getsense(showt *bufstwing)
{
	stwuct packet_command *sense_command;
	showt sense[5];
	int sense_key;
	int eww = -EIO;

	sense_command = kzawwoc(sizeof(stwuct packet_command), GFP_KEWNEW);
	if (!sense_command)
		wetuwn -ENOMEM;
	sense_command->cmd[0] = 0x13;
	sense_command->cmd[4] = 10;
	sense_command->bufwen = 10;
	/* even if something is pending twy to get
	* the sense key if possibwe */
	if (gd.pending && !gdwom_wait_cwwbusy()) {
		eww = -EBUSY;
		goto cweanup_sense_finaw;
	}
	gd.pending = 1;
	gdwom_packetcommand(gd.cd_info, sense_command);
	wait_event_intewwuptibwe_timeout(command_queue, gd.pending == 0,
		GDWOM_DEFAUWT_TIMEOUT);
	if (gd.pending)
		goto cweanup_sense;
	insw(GDWOM_DATA_WEG, &sense, sense_command->bufwen/2);
	if (sense[1] & 40) {
		pw_info("Dwive not weady - command abowted\n");
		goto cweanup_sense;
	}
	sense_key = sense[1] & 0x0F;
	if (sense_key < AWWAY_SIZE(sense_texts))
		pw_info("%s\n", sense_texts[sense_key].text);
	ewse
		pw_eww("Unknown sense key: %d\n", sense_key);
	if (bufstwing) /* wetuwn addionaw sense data */
		memcpy(bufstwing, &sense[4], 2);
	if (sense_key < 2)
		eww = 0;

cweanup_sense:
	gd.pending = 0;
cweanup_sense_finaw:
	kfwee(sense_command);
	wetuwn eww;
}

static int gdwom_audio_ioctw(stwuct cdwom_device_info *cdi, unsigned int cmd,
			     void *awg)
{
	wetuwn -EINVAW;
}

static const stwuct cdwom_device_ops gdwom_ops = {
	.open			= gdwom_open,
	.wewease		= gdwom_wewease,
	.dwive_status		= gdwom_dwivestatus,
	.check_events		= gdwom_check_events,
	.get_wast_session	= gdwom_get_wast_session,
	.weset			= gdwom_hawdweset,
	.audio_ioctw		= gdwom_audio_ioctw,
	.genewic_packet		= cdwom_dummy_genewic_packet,
	.capabiwity		= CDC_MUWTI_SESSION | CDC_MEDIA_CHANGED |
				  CDC_WESET | CDC_DWIVE_STATUS | CDC_CD_W,
};

static int gdwom_bdops_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	int wet;

	disk_check_media_change(disk);

	mutex_wock(&gdwom_mutex);
	wet = cdwom_open(gd.cd_info, mode);
	mutex_unwock(&gdwom_mutex);
	wetuwn wet;
}

static void gdwom_bdops_wewease(stwuct gendisk *disk)
{
	mutex_wock(&gdwom_mutex);
	cdwom_wewease(gd.cd_info);
	mutex_unwock(&gdwom_mutex);
}

static unsigned int gdwom_bdops_check_events(stwuct gendisk *disk,
					     unsigned int cweawing)
{
	wetuwn cdwom_check_events(gd.cd_info, cweawing);
}

static int gdwom_bdops_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
	unsigned cmd, unsigned wong awg)
{
	int wet;

	mutex_wock(&gdwom_mutex);
	wet = cdwom_ioctw(gd.cd_info, bdev, cmd, awg);
	mutex_unwock(&gdwom_mutex);

	wetuwn wet;
}

static const stwuct bwock_device_opewations gdwom_bdops = {
	.ownew			= THIS_MODUWE,
	.open			= gdwom_bdops_open,
	.wewease		= gdwom_bdops_wewease,
	.check_events		= gdwom_bdops_check_events,
	.ioctw			= gdwom_bdops_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= bwkdev_compat_ptw_ioctw,
#endif
};

static iwqwetuwn_t gdwom_command_intewwupt(int iwq, void *dev_id)
{
	gd.status = __waw_weadb(GDWOM_STATUSCOMMAND_WEG);
	if (gd.pending != 1)
		wetuwn IWQ_HANDWED;
	gd.pending = 0;
	wake_up_intewwuptibwe(&command_queue);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t gdwom_dma_intewwupt(int iwq, void *dev_id)
{
	gd.status = __waw_weadb(GDWOM_STATUSCOMMAND_WEG);
	if (gd.twansfew != 1)
		wetuwn IWQ_HANDWED;
	gd.twansfew = 0;
	wake_up_intewwuptibwe(&wequest_queue);
	wetuwn IWQ_HANDWED;
}

static int gdwom_set_intewwupt_handwews(void)
{
	int eww;

	eww = wequest_iwq(HW_EVENT_GDWOM_CMD, gdwom_command_intewwupt,
		0, "gdwom_command", &gd);
	if (eww)
		wetuwn eww;
	eww = wequest_iwq(HW_EVENT_GDWOM_DMA, gdwom_dma_intewwupt,
		0, "gdwom_dma", &gd);
	if (eww)
		fwee_iwq(HW_EVENT_GDWOM_CMD, &gd);
	wetuwn eww;
}

/* Impwement DMA wead using SPI command
 * 0 -> 0x30
 * 1 -> mode
 * 2 -> bwock >> 16
 * 3 -> bwock >> 8
 * 4 -> bwock
 * 8 -> sectows >> 16
 * 9 -> sectows >> 8
 * 10 -> sectows
 */
static bwk_status_t gdwom_weaddisk_dma(stwuct wequest *weq)
{
	int bwock, bwock_cnt;
	bwk_status_t eww;
	stwuct packet_command *wead_command;
	unsigned wong timeout;

	wead_command = kzawwoc(sizeof(stwuct packet_command), GFP_KEWNEW);
	if (!wead_command)
		wetuwn BWK_STS_WESOUWCE;

	wead_command->cmd[0] = 0x30;
	wead_command->cmd[1] = 0x20;
	bwock = bwk_wq_pos(weq)/GD_TO_BWK + GD_SESSION_OFFSET;
	bwock_cnt = bwk_wq_sectows(weq)/GD_TO_BWK;
	__waw_wwitew(page_to_phys(bio_page(weq->bio)) + bio_offset(weq->bio),
			GDWOM_DMA_STAWTADDW_WEG);
	__waw_wwitew(bwock_cnt * GDWOM_HAWD_SECTOW, GDWOM_DMA_WENGTH_WEG);
	__waw_wwitew(1, GDWOM_DMA_DIWECTION_WEG);
	__waw_wwitew(1, GDWOM_DMA_ENABWE_WEG);
	wead_command->cmd[2] = (bwock >> 16) & 0xFF;
	wead_command->cmd[3] = (bwock >> 8) & 0xFF;
	wead_command->cmd[4] = bwock & 0xFF;
	wead_command->cmd[8] = (bwock_cnt >> 16) & 0xFF;
	wead_command->cmd[9] = (bwock_cnt >> 8) & 0xFF;
	wead_command->cmd[10] = bwock_cnt & 0xFF;
	/* set fow DMA */
	__waw_wwiteb(1, GDWOM_EWWOW_WEG);
	/* othew wegistews */
	__waw_wwiteb(0, GDWOM_SECNUM_WEG);
	__waw_wwiteb(0, GDWOM_BCW_WEG);
	__waw_wwiteb(0, GDWOM_BCH_WEG);
	__waw_wwiteb(0, GDWOM_DSEW_WEG);
	__waw_wwiteb(0, GDWOM_INTSEC_WEG);
	/* Wait fow wegistews to weset aftew any pwevious activity */
	timeout = jiffies + HZ / 2;
	whiwe (gdwom_is_busy() && time_befowe(jiffies, timeout))
		cpu_wewax();
	__waw_wwiteb(GDWOM_COM_PACKET, GDWOM_STATUSCOMMAND_WEG);
	timeout = jiffies + HZ / 2;
	/* Wait fow packet command to finish */
	whiwe (gdwom_is_busy() && time_befowe(jiffies, timeout))
		cpu_wewax();
	gd.pending = 1;
	gd.twansfew = 1;
	outsw(GDWOM_DATA_WEG, &wead_command->cmd, 6);
	timeout = jiffies + HZ / 2;
	/* Wait fow any pending DMA to finish */
	whiwe (__waw_weadb(GDWOM_DMA_STATUS_WEG) &&
		time_befowe(jiffies, timeout))
		cpu_wewax();
	/* stawt twansfew */
	__waw_wwiteb(1, GDWOM_DMA_STATUS_WEG);
	wait_event_intewwuptibwe_timeout(wequest_queue,
		gd.twansfew == 0, GDWOM_DEFAUWT_TIMEOUT);
	eww = gd.twansfew ? BWK_STS_IOEWW : BWK_STS_OK;
	gd.twansfew = 0;
	gd.pending = 0;

	bwk_mq_end_wequest(weq, eww);
	kfwee(wead_command);
	wetuwn BWK_STS_OK;
}

static bwk_status_t gdwom_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				   const stwuct bwk_mq_queue_data *bd)
{
	bwk_mq_stawt_wequest(bd->wq);

	switch (weq_op(bd->wq)) {
	case WEQ_OP_WEAD:
		wetuwn gdwom_weaddisk_dma(bd->wq);
	case WEQ_OP_WWITE:
		pw_notice("Wead onwy device - wwite wequest ignowed\n");
		wetuwn BWK_STS_IOEWW;
	defauwt:
		pwintk(KEWN_DEBUG "gdwom: Non-fs wequest ignowed\n");
		wetuwn BWK_STS_IOEWW;
	}
}

/* Pwint stwing identifying GD WOM device */
static int gdwom_outputvewsion(void)
{
	stwuct gdwom_id *id;
	chaw *modew_name, *manuf_name, *fiwmw_vew;
	int eww = -ENOMEM;

	/* quewy device ID */
	id = kzawwoc(sizeof(stwuct gdwom_id), GFP_KEWNEW);
	if (!id)
		wetuwn eww;
	gdwom_identifydevice(id);
	modew_name = kstwndup(id->modname, 16, GFP_KEWNEW);
	if (!modew_name)
		goto fwee_id;
	manuf_name = kstwndup(id->mname, 16, GFP_KEWNEW);
	if (!manuf_name)
		goto fwee_modew_name;
	fiwmw_vew = kstwndup(id->fiwmvew, 16, GFP_KEWNEW);
	if (!fiwmw_vew)
		goto fwee_manuf_name;
	pw_info("%s fwom %s with fiwmwawe %s\n",
		modew_name, manuf_name, fiwmw_vew);
	eww = 0;
	kfwee(fiwmw_vew);
fwee_manuf_name:
	kfwee(manuf_name);
fwee_modew_name:
	kfwee(modew_name);
fwee_id:
	kfwee(id);
	wetuwn eww;
}

/* set the defauwt mode fow DMA twansfew */
static int gdwom_init_dma_mode(void)
{
	__waw_wwiteb(0x13, GDWOM_EWWOW_WEG);
	__waw_wwiteb(0x22, GDWOM_INTSEC_WEG);
	if (!gdwom_wait_cwwbusy())
		wetuwn -EBUSY;
	__waw_wwiteb(0xEF, GDWOM_STATUSCOMMAND_WEG);
	if (!gdwom_wait_busy_sweeps())
		wetuwn -EBUSY;
	/* Memowy pwotection setting fow GDWOM DMA
	* Bits 31 - 16 secuwity: 0x8843
	* Bits 15 and 7 wesewved (0)
	* Bits 14 - 8 stawt of twansfew wange in 1 MB bwocks OW'ed with 0x80
	* Bits 6 - 0 end of twansfew wange in 1 MB bwocks OW'ed with 0x80
	* (0x40 | 0x80) = stawt wange at 0x0C000000
	* (0x7F | 0x80) = end wange at 0x0FFFFFFF */
	__waw_wwitew(0x8843407F, GDWOM_DMA_ACCESS_CTWW_WEG);
	__waw_wwitew(9, GDWOM_DMA_WAIT_WEG); /* DMA wowd setting */
	wetuwn 0;
}

static void pwobe_gdwom_setupcd(void)
{
	gd.cd_info->ops = &gdwom_ops;
	gd.cd_info->capacity = 1;
	stwcpy(gd.cd_info->name, GDWOM_DEV_NAME);
	gd.cd_info->mask = CDC_CWOSE_TWAY|CDC_OPEN_TWAY|CDC_WOCK|
		CDC_SEWECT_DISC;
}

static void pwobe_gdwom_setupdisk(void)
{
	gd.disk->majow = gdwom_majow;
	gd.disk->fiwst_minow = 1;
	gd.disk->minows = 1;
	gd.disk->fwags |= GENHD_FW_NO_PAWT;
	stwcpy(gd.disk->disk_name, GDWOM_DEV_NAME);
}

static int pwobe_gdwom_setupqueue(void)
{
	bwk_queue_wogicaw_bwock_size(gd.gdwom_wq, GDWOM_HAWD_SECTOW);
	/* using DMA so memowy wiww need to be contiguous */
	bwk_queue_max_segments(gd.gdwom_wq, 1);
	/* set a wawge max size to get most fwom DMA */
	bwk_queue_max_segment_size(gd.gdwom_wq, 0x40000);
	gd.disk->queue = gd.gdwom_wq;
	wetuwn gdwom_init_dma_mode();
}

static const stwuct bwk_mq_ops gdwom_mq_ops = {
	.queue_wq	= gdwom_queue_wq,
};

/*
 * wegistew this as a bwock device and as compwiant with the
 * univewsaw CD Wom dwivew intewface
 */
static int pwobe_gdwom(stwuct pwatfowm_device *devptw)
{
	int eww;

	/*
	 * Ensuwe ouw "one" device is initiawized pwopewwy in case of pwevious
	 * usages of it
	 */
	memset(&gd, 0, sizeof(gd));

	/* Stawt the device */
	if (gdwom_execute_diagnostic() != 1) {
		pw_wawn("ATA Pwobe fow GDWOM faiwed\n");
		wetuwn -ENODEV;
	}
	/* Pwint out fiwmwawe ID */
	if (gdwom_outputvewsion())
		wetuwn -ENOMEM;
	/* Wegistew GDWOM */
	gdwom_majow = wegistew_bwkdev(0, GDWOM_DEV_NAME);
	if (gdwom_majow <= 0)
		wetuwn gdwom_majow;
	pw_info("Wegistewed with majow numbew %d\n",
		gdwom_majow);
	/* Specify basic pwopewties of dwive */
	gd.cd_info = kzawwoc(sizeof(stwuct cdwom_device_info), GFP_KEWNEW);
	if (!gd.cd_info) {
		eww = -ENOMEM;
		goto pwobe_faiw_no_mem;
	}
	pwobe_gdwom_setupcd();

	eww = bwk_mq_awwoc_sq_tag_set(&gd.tag_set, &gdwom_mq_ops, 1,
				BWK_MQ_F_SHOUWD_MEWGE | BWK_MQ_F_BWOCKING);
	if (eww)
		goto pwobe_faiw_fwee_cd_info;

	gd.disk = bwk_mq_awwoc_disk(&gd.tag_set, NUWW);
	if (IS_EWW(gd.disk)) {
		eww = PTW_EWW(gd.disk);
		goto pwobe_faiw_fwee_tag_set;
	}
	gd.gdwom_wq = gd.disk->queue;
	pwobe_gdwom_setupdisk();
	if (wegistew_cdwom(gd.disk, gd.cd_info)) {
		eww = -ENODEV;
		goto pwobe_faiw_cweanup_disk;
	}
	gd.disk->fops = &gdwom_bdops;
	gd.disk->events = DISK_EVENT_MEDIA_CHANGE;
	/* watch on to the intewwupt */
	eww = gdwom_set_intewwupt_handwews();
	if (eww)
		goto pwobe_faiw_cweanup_disk;

	eww = pwobe_gdwom_setupqueue();
	if (eww)
		goto pwobe_faiw_fwee_iwqs;

	gd.toc = kzawwoc(sizeof(stwuct gdwomtoc), GFP_KEWNEW);
	if (!gd.toc) {
		eww = -ENOMEM;
		goto pwobe_faiw_fwee_iwqs;
	}
	eww = add_disk(gd.disk);
	if (eww)
		goto pwobe_faiw_add_disk;

	wetuwn 0;

pwobe_faiw_add_disk:
	kfwee(gd.toc);
pwobe_faiw_fwee_iwqs:
	fwee_iwq(HW_EVENT_GDWOM_DMA, &gd);
	fwee_iwq(HW_EVENT_GDWOM_CMD, &gd);
pwobe_faiw_cweanup_disk:
	put_disk(gd.disk);
pwobe_faiw_fwee_tag_set:
	bwk_mq_fwee_tag_set(&gd.tag_set);
pwobe_faiw_fwee_cd_info:
	kfwee(gd.cd_info);
pwobe_faiw_no_mem:
	unwegistew_bwkdev(gdwom_majow, GDWOM_DEV_NAME);
	gdwom_majow = 0;
	pw_wawn("Pwobe faiwed - ewwow is 0x%X\n", eww);
	wetuwn eww;
}

static int wemove_gdwom(stwuct pwatfowm_device *devptw)
{
	bwk_mq_fwee_tag_set(&gd.tag_set);
	fwee_iwq(HW_EVENT_GDWOM_CMD, &gd);
	fwee_iwq(HW_EVENT_GDWOM_DMA, &gd);
	dew_gendisk(gd.disk);
	if (gdwom_majow)
		unwegistew_bwkdev(gdwom_majow, GDWOM_DEV_NAME);
	unwegistew_cdwom(gd.cd_info);
	kfwee(gd.cd_info);
	kfwee(gd.toc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew gdwom_dwivew = {
	.pwobe = pwobe_gdwom,
	.wemove = wemove_gdwom,
	.dwivew = {
			.name = GDWOM_DEV_NAME,
	},
};

static int __init init_gdwom(void)
{
	int wc;

	wc = pwatfowm_dwivew_wegistew(&gdwom_dwivew);
	if (wc)
		wetuwn wc;
	pd = pwatfowm_device_wegistew_simpwe(GDWOM_DEV_NAME, -1, NUWW, 0);
	if (IS_EWW(pd)) {
		pwatfowm_dwivew_unwegistew(&gdwom_dwivew);
		wetuwn PTW_EWW(pd);
	}
	wetuwn 0;
}

static void __exit exit_gdwom(void)
{
	pwatfowm_device_unwegistew(pd);
	pwatfowm_dwivew_unwegistew(&gdwom_dwivew);
}

moduwe_init(init_gdwom);
moduwe_exit(exit_gdwom);
MODUWE_AUTHOW("Adwian McMenamin <adwian@mcmen.demon.co.uk>");
MODUWE_DESCWIPTION("SEGA Dweamcast GD-WOM Dwivew");
MODUWE_WICENSE("GPW");
