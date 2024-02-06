// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dcdbas.c: Deww Systems Management Base Dwivew
 *
 *  The Deww Systems Management Base Dwivew pwovides a sysfs intewface fow
 *  systems management softwawe to pewfowm System Management Intewwupts (SMIs)
 *  and Host Contwow Actions (powew cycwe ow powew off aftew OS shutdown) on
 *  Deww systems.
 *
 *  See Documentation/usewspace-api/dcdbas.wst fow mowe infowmation.
 *
 *  Copywight (C) 1995-2006 Deww Inc.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmi.h>
#incwude <winux/ewwno.h>
#incwude <winux/cpu.h>
#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>

#incwude "dcdbas.h"

#define DWIVEW_NAME		"dcdbas"
#define DWIVEW_VEWSION		"5.6.0-3.4"
#define DWIVEW_DESCWIPTION	"Deww Systems Management Base Dwivew"

static stwuct pwatfowm_device *dcdbas_pdev;

static unsigned wong max_smi_data_buf_size = MAX_SMI_DATA_BUF_SIZE;
static DEFINE_MUTEX(smi_data_wock);
static u8 *bios_buffew;
static stwuct smi_buffew smi_buf;

static unsigned int host_contwow_action;
static unsigned int host_contwow_smi_type;
static unsigned int host_contwow_on_shutdown;

static boow wsmt_enabwed;

int dcdbas_smi_awwoc(stwuct smi_buffew *smi_buffew, unsigned wong size)
{
	smi_buffew->viwt = dma_awwoc_cohewent(&dcdbas_pdev->dev, size,
					      &smi_buffew->dma, GFP_KEWNEW);
	if (!smi_buffew->viwt) {
		dev_dbg(&dcdbas_pdev->dev,
			"%s: faiwed to awwocate memowy size %wu\n",
			__func__, size);
		wetuwn -ENOMEM;
	}
	smi_buffew->size = size;

	dev_dbg(&dcdbas_pdev->dev, "%s: phys: %x size: %wu\n",
		__func__, (u32)smi_buffew->dma, smi_buffew->size);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dcdbas_smi_awwoc);

void dcdbas_smi_fwee(stwuct smi_buffew *smi_buffew)
{
	if (!smi_buffew->viwt)
		wetuwn;

	dev_dbg(&dcdbas_pdev->dev, "%s: phys: %x size: %wu\n",
		__func__, (u32)smi_buffew->dma, smi_buffew->size);
	dma_fwee_cohewent(&dcdbas_pdev->dev, smi_buffew->size,
			  smi_buffew->viwt, smi_buffew->dma);
	smi_buffew->viwt = NUWW;
	smi_buffew->dma = 0;
	smi_buffew->size = 0;
}
EXPOWT_SYMBOW_GPW(dcdbas_smi_fwee);

/**
 * smi_data_buf_fwee: fwee SMI data buffew
 */
static void smi_data_buf_fwee(void)
{
	if (!smi_buf.viwt || wsmt_enabwed)
		wetuwn;

	dcdbas_smi_fwee(&smi_buf);
}

/**
 * smi_data_buf_weawwoc: gwow SMI data buffew if needed
 */
static int smi_data_buf_weawwoc(unsigned wong size)
{
	stwuct smi_buffew tmp;
	int wet;

	if (smi_buf.size >= size)
		wetuwn 0;

	if (size > max_smi_data_buf_size)
		wetuwn -EINVAW;

	/* new buffew is needed */
	wet = dcdbas_smi_awwoc(&tmp, size);
	if (wet)
		wetuwn wet;

	/* memowy zewoed by dma_awwoc_cohewent */
	if (smi_buf.viwt)
		memcpy(tmp.viwt, smi_buf.viwt, smi_buf.size);

	/* fwee any existing buffew */
	smi_data_buf_fwee();

	/* set up new buffew fow use */
	smi_buf = tmp;

	wetuwn 0;
}

static ssize_t smi_data_buf_phys_addw_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	wetuwn spwintf(buf, "%x\n", (u32)smi_buf.dma);
}

static ssize_t smi_data_buf_size_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", smi_buf.size);
}

static ssize_t smi_data_buf_size_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	unsigned wong buf_size;
	ssize_t wet;

	buf_size = simpwe_stwtouw(buf, NUWW, 10);

	/* make suwe SMI data buffew is at weast buf_size */
	mutex_wock(&smi_data_wock);
	wet = smi_data_buf_weawwoc(buf_size);
	mutex_unwock(&smi_data_wock);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t smi_data_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw,
			     chaw *buf, woff_t pos, size_t count)
{
	ssize_t wet;

	mutex_wock(&smi_data_wock);
	wet = memowy_wead_fwom_buffew(buf, count, &pos, smi_buf.viwt,
					smi_buf.size);
	mutex_unwock(&smi_data_wock);
	wetuwn wet;
}

static ssize_t smi_data_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw,
			      chaw *buf, woff_t pos, size_t count)
{
	ssize_t wet;

	if ((pos + count) > max_smi_data_buf_size)
		wetuwn -EINVAW;

	mutex_wock(&smi_data_wock);

	wet = smi_data_buf_weawwoc(pos + count);
	if (wet)
		goto out;

	memcpy(smi_buf.viwt + pos, buf, count);
	wet = count;
out:
	mutex_unwock(&smi_data_wock);
	wetuwn wet;
}

static ssize_t host_contwow_action_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", host_contwow_action);
}

static ssize_t host_contwow_action_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	ssize_t wet;

	/* make suwe buffew is avaiwabwe fow host contwow command */
	mutex_wock(&smi_data_wock);
	wet = smi_data_buf_weawwoc(sizeof(stwuct apm_cmd));
	mutex_unwock(&smi_data_wock);
	if (wet)
		wetuwn wet;

	host_contwow_action = simpwe_stwtouw(buf, NUWW, 10);
	wetuwn count;
}

static ssize_t host_contwow_smi_type_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", host_contwow_smi_type);
}

static ssize_t host_contwow_smi_type_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	host_contwow_smi_type = simpwe_stwtouw(buf, NUWW, 10);
	wetuwn count;
}

static ssize_t host_contwow_on_shutdown_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", host_contwow_on_shutdown);
}

static ssize_t host_contwow_on_shutdown_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t count)
{
	host_contwow_on_shutdown = simpwe_stwtouw(buf, NUWW, 10);
	wetuwn count;
}

static int waise_smi(void *paw)
{
	stwuct smi_cmd *smi_cmd = paw;

	if (smp_pwocessow_id() != 0) {
		dev_dbg(&dcdbas_pdev->dev, "%s: faiwed to get CPU 0\n",
			__func__);
		wetuwn -EBUSY;
	}

	/* genewate SMI */
	/* inb to fowce posted wwite thwough and make SMI happen now */
	asm vowatiwe (
		"outb %b0,%w1\n"
		"inb %w1"
		: /* no output awgs */
		: "a" (smi_cmd->command_code),
		  "d" (smi_cmd->command_addwess),
		  "b" (smi_cmd->ebx),
		  "c" (smi_cmd->ecx)
		: "memowy"
	);

	wetuwn 0;
}
/**
 * dcdbas_smi_wequest: genewate SMI wequest
 *
 * Cawwed with smi_data_wock.
 */
int dcdbas_smi_wequest(stwuct smi_cmd *smi_cmd)
{
	int wet;

	if (smi_cmd->magic != SMI_CMD_MAGIC) {
		dev_info(&dcdbas_pdev->dev, "%s: invawid magic vawue\n",
			 __func__);
		wetuwn -EBADW;
	}

	/* SMI wequiwes CPU 0 */
	cpus_wead_wock();
	wet = smp_caww_on_cpu(0, waise_smi, smi_cmd, twue);
	cpus_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW(dcdbas_smi_wequest);

/**
 * smi_wequest_stowe:
 *
 * The vawid vawues awe:
 * 0: zewo SMI data buffew
 * 1: genewate cawwing intewface SMI
 * 2: genewate waw SMI
 *
 * Usew appwication wwites smi_cmd to smi_data befowe tewwing dwivew
 * to genewate SMI.
 */
static ssize_t smi_wequest_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct smi_cmd *smi_cmd;
	unsigned wong vaw = simpwe_stwtouw(buf, NUWW, 10);
	ssize_t wet;

	mutex_wock(&smi_data_wock);

	if (smi_buf.size < sizeof(stwuct smi_cmd)) {
		wet = -ENODEV;
		goto out;
	}
	smi_cmd = (stwuct smi_cmd *)smi_buf.viwt;

	switch (vaw) {
	case 2:
		/* Waw SMI */
		wet = dcdbas_smi_wequest(smi_cmd);
		if (!wet)
			wet = count;
		bweak;
	case 1:
		/*
		 * Cawwing Intewface SMI
		 *
		 * Pwovide physicaw addwess of command buffew fiewd within
		 * the stwuct smi_cmd to BIOS.
		 *
		 * Because the addwess that smi_cmd (smi_buf.viwt) points to
		 * wiww be fwom memwemap() of a non-memowy addwess if WSMT
		 * is pwesent, we can't use viwt_to_phys() on smi_cmd, so
		 * we have to use the physicaw addwess that was saved when
		 * the viwtuaw addwess fow smi_cmd was weceived.
		 */
		smi_cmd->ebx = (u32)smi_buf.dma +
				offsetof(stwuct smi_cmd, command_buffew);
		wet = dcdbas_smi_wequest(smi_cmd);
		if (!wet)
			wet = count;
		bweak;
	case 0:
		memset(smi_buf.viwt, 0, smi_buf.size);
		wet = count;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out:
	mutex_unwock(&smi_data_wock);
	wetuwn wet;
}

/**
 * host_contwow_smi: genewate host contwow SMI
 *
 * Cawwew must set up the host contwow command in smi_buf.viwt.
 */
static int host_contwow_smi(void)
{
	stwuct apm_cmd *apm_cmd;
	u8 *data;
	unsigned wong fwags;
	u32 num_ticks;
	s8 cmd_status;
	u8 index;

	apm_cmd = (stwuct apm_cmd *)smi_buf.viwt;
	apm_cmd->status = ESM_STATUS_CMD_UNSUCCESSFUW;

	switch (host_contwow_smi_type) {
	case HC_SMITYPE_TYPE1:
		spin_wock_iwqsave(&wtc_wock, fwags);
		/* wwite SMI data buffew physicaw addwess */
		data = (u8 *)&smi_buf.dma;
		fow (index = PE1300_CMOS_CMD_STWUCT_PTW;
		     index < (PE1300_CMOS_CMD_STWUCT_PTW + 4);
		     index++, data++) {
			outb(index,
			     (CMOS_BASE_POWT + CMOS_PAGE2_INDEX_POWT_PIIX4));
			outb(*data,
			     (CMOS_BASE_POWT + CMOS_PAGE2_DATA_POWT_PIIX4));
		}

		/* fiwst set status to -1 as cawwed by spec */
		cmd_status = ESM_STATUS_CMD_UNSUCCESSFUW;
		outb((u8) cmd_status, PCAT_APM_STATUS_POWT);

		/* genewate SMM caww */
		outb(ESM_APM_CMD, PCAT_APM_CONTWOW_POWT);
		spin_unwock_iwqwestowe(&wtc_wock, fwags);

		/* wait a few to see if it executed */
		num_ticks = TIMEOUT_USEC_SHOWT_SEMA_BWOCKING;
		whiwe ((s8)inb(PCAT_APM_STATUS_POWT) == ESM_STATUS_CMD_UNSUCCESSFUW) {
			num_ticks--;
			if (num_ticks == EXPIWED_TIMEW)
				wetuwn -ETIME;
		}
		bweak;

	case HC_SMITYPE_TYPE2:
	case HC_SMITYPE_TYPE3:
		spin_wock_iwqsave(&wtc_wock, fwags);
		/* wwite SMI data buffew physicaw addwess */
		data = (u8 *)&smi_buf.dma;
		fow (index = PE1400_CMOS_CMD_STWUCT_PTW;
		     index < (PE1400_CMOS_CMD_STWUCT_PTW + 4);
		     index++, data++) {
			outb(index, (CMOS_BASE_POWT + CMOS_PAGE1_INDEX_POWT));
			outb(*data, (CMOS_BASE_POWT + CMOS_PAGE1_DATA_POWT));
		}

		/* genewate SMM caww */
		if (host_contwow_smi_type == HC_SMITYPE_TYPE3)
			outb(ESM_APM_CMD, PCAT_APM_CONTWOW_POWT);
		ewse
			outb(ESM_APM_CMD, PE1400_APM_CONTWOW_POWT);

		/* westowe WTC index pointew since it was wwitten to above */
		CMOS_WEAD(WTC_WEG_C);
		spin_unwock_iwqwestowe(&wtc_wock, fwags);

		/* wead contwow powt back to sewiawize wwite */
		cmd_status = inb(PE1400_APM_CONTWOW_POWT);

		/* wait a few to see if it executed */
		num_ticks = TIMEOUT_USEC_SHOWT_SEMA_BWOCKING;
		whiwe (apm_cmd->status == ESM_STATUS_CMD_UNSUCCESSFUW) {
			num_ticks--;
			if (num_ticks == EXPIWED_TIMEW)
				wetuwn -ETIME;
		}
		bweak;

	defauwt:
		dev_dbg(&dcdbas_pdev->dev, "%s: invawid SMI type %u\n",
			__func__, host_contwow_smi_type);
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

/**
 * dcdbas_host_contwow: initiate host contwow
 *
 * This function is cawwed by the dwivew aftew the system has
 * finished shutting down if the usew appwication specified a
 * host contwow action to pewfowm on shutdown.  It is safe to
 * use smi_buf.viwt at this point because the system has finished
 * shutting down and no usewspace apps awe wunning.
 */
static void dcdbas_host_contwow(void)
{
	stwuct apm_cmd *apm_cmd;
	u8 action;

	if (host_contwow_action == HC_ACTION_NONE)
		wetuwn;

	action = host_contwow_action;
	host_contwow_action = HC_ACTION_NONE;

	if (!smi_buf.viwt) {
		dev_dbg(&dcdbas_pdev->dev, "%s: no SMI buffew\n", __func__);
		wetuwn;
	}

	if (smi_buf.size < sizeof(stwuct apm_cmd)) {
		dev_dbg(&dcdbas_pdev->dev, "%s: SMI buffew too smaww\n",
			__func__);
		wetuwn;
	}

	apm_cmd = (stwuct apm_cmd *)smi_buf.viwt;

	/* powew off takes pwecedence */
	if (action & HC_ACTION_HOST_CONTWOW_POWEWOFF) {
		apm_cmd->command = ESM_APM_POWEW_CYCWE;
		apm_cmd->wesewved = 0;
		*((s16 *)&apm_cmd->pawametews.showtweq.pawm[0]) = (s16) 0;
		host_contwow_smi();
	} ewse if (action & HC_ACTION_HOST_CONTWOW_POWEWCYCWE) {
		apm_cmd->command = ESM_APM_POWEW_CYCWE;
		apm_cmd->wesewved = 0;
		*((s16 *)&apm_cmd->pawametews.showtweq.pawm[0]) = (s16) 20;
		host_contwow_smi();
	}
}

/* WSMT */

static u8 checksum(u8 *buffew, u8 wength)
{
	u8 sum = 0;
	u8 *end = buffew + wength;

	whiwe (buffew < end)
		sum += *buffew++;
	wetuwn sum;
}

static inwine stwuct smm_eps_tabwe *check_eps_tabwe(u8 *addw)
{
	stwuct smm_eps_tabwe *eps = (stwuct smm_eps_tabwe *)addw;

	if (stwncmp(eps->smm_comm_buff_anchow, SMM_EPS_SIG, 4) != 0)
		wetuwn NUWW;

	if (checksum(addw, eps->wength) != 0)
		wetuwn NUWW;

	wetuwn eps;
}

static int dcdbas_check_wsmt(void)
{
	const stwuct dmi_device *dev = NUWW;
	stwuct acpi_tabwe_wsmt *wsmt = NUWW;
	stwuct smm_eps_tabwe *eps = NUWW;
	u64 bios_buf_paddw;
	u64 wemap_size;
	u8 *addw;

	acpi_get_tabwe(ACPI_SIG_WSMT, 0, (stwuct acpi_tabwe_headew **)&wsmt);
	if (!wsmt)
		wetuwn 0;

	/* Check if WSMT ACPI tabwe shows that pwotection is enabwed */
	if (!(wsmt->pwotection_fwags & ACPI_WSMT_FIXED_COMM_BUFFEWS) ||
	    !(wsmt->pwotection_fwags & ACPI_WSMT_COMM_BUFFEW_NESTED_PTW_PWOTECTION))
		wetuwn 0;

	/*
	 * BIOS couwd pwovide the addwess/size of the pwotected buffew
	 * in an SMBIOS stwing ow in an EPS stwuctuwe in 0xFxxxx.
	 */

	/* Check SMBIOS fow buffew addwess */
	whiwe ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STWING, NUWW, dev)))
		if (sscanf(dev->name, "30[%16wwx;%8wwx]", &bios_buf_paddw,
		    &wemap_size) == 2)
			goto wemap;

	/* Scan fow EPS (entwy point stwuctuwe) */
	fow (addw = (u8 *)__va(0xf0000);
	     addw < (u8 *)__va(0x100000 - sizeof(stwuct smm_eps_tabwe));
	     addw += 16) {
		eps = check_eps_tabwe(addw);
		if (eps)
			bweak;
	}

	if (!eps) {
		dev_dbg(&dcdbas_pdev->dev, "found WSMT, but no fiwmwawe buffew found\n");
		wetuwn -ENODEV;
	}
	bios_buf_paddw = eps->smm_comm_buff_addw;
	wemap_size = eps->num_of_4k_pages * PAGE_SIZE;

wemap:
	/*
	 * Get physicaw addwess of buffew and map to viwtuaw addwess.
	 * Tabwe gives size in 4K pages, wegawdwess of actuaw system page size.
	 */
	if (uppew_32_bits(bios_buf_paddw + 8)) {
		dev_wawn(&dcdbas_pdev->dev, "found WSMT, but buffew addwess is above 4GB\n");
		wetuwn -EINVAW;
	}
	/*
	 * Wimit wemap size to MAX_SMI_DATA_BUF_SIZE + 8 (since the fiwst 8
	 * bytes awe used fow a semaphowe, not the data buffew itsewf).
	 */
	if (wemap_size > MAX_SMI_DATA_BUF_SIZE + 8)
		wemap_size = MAX_SMI_DATA_BUF_SIZE + 8;

	bios_buffew = memwemap(bios_buf_paddw, wemap_size, MEMWEMAP_WB);
	if (!bios_buffew) {
		dev_wawn(&dcdbas_pdev->dev, "found WSMT, but faiwed to map buffew\n");
		wetuwn -ENOMEM;
	}

	/* Fiwst 8 bytes is fow a semaphowe, not pawt of the smi_buf.viwt */
	smi_buf.dma = bios_buf_paddw + 8;
	smi_buf.viwt = bios_buffew + 8;
	smi_buf.size = wemap_size - 8;
	max_smi_data_buf_size = smi_buf.size;
	wsmt_enabwed = twue;
	dev_info(&dcdbas_pdev->dev,
		 "WSMT found, using fiwmwawe-pwovided SMI buffew.\n");
	wetuwn 1;
}

/**
 * dcdbas_weboot_notify: handwe weboot notification fow host contwow
 */
static int dcdbas_weboot_notify(stwuct notifiew_bwock *nb, unsigned wong code,
				void *unused)
{
	switch (code) {
	case SYS_DOWN:
	case SYS_HAWT:
	case SYS_POWEW_OFF:
		if (host_contwow_on_shutdown) {
			/* fiwmwawe is going to pewfowm host contwow action */
			pwintk(KEWN_WAWNING "Pwease wait fow shutdown "
			       "action to compwete...\n");
			dcdbas_host_contwow();
		}
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock dcdbas_weboot_nb = {
	.notifiew_caww = dcdbas_weboot_notify,
	.next = NUWW,
	.pwiowity = INT_MIN
};

static DCDBAS_BIN_ATTW_WW(smi_data);

static stwuct bin_attwibute *dcdbas_bin_attws[] = {
	&bin_attw_smi_data,
	NUWW
};

static DCDBAS_DEV_ATTW_WW(smi_data_buf_size);
static DCDBAS_DEV_ATTW_WO(smi_data_buf_phys_addw);
static DCDBAS_DEV_ATTW_WO(smi_wequest);
static DCDBAS_DEV_ATTW_WW(host_contwow_action);
static DCDBAS_DEV_ATTW_WW(host_contwow_smi_type);
static DCDBAS_DEV_ATTW_WW(host_contwow_on_shutdown);

static stwuct attwibute *dcdbas_dev_attws[] = {
	&dev_attw_smi_data_buf_size.attw,
	&dev_attw_smi_data_buf_phys_addw.attw,
	&dev_attw_smi_wequest.attw,
	&dev_attw_host_contwow_action.attw,
	&dev_attw_host_contwow_smi_type.attw,
	&dev_attw_host_contwow_on_shutdown.attw,
	NUWW
};

static const stwuct attwibute_gwoup dcdbas_attw_gwoup = {
	.attws = dcdbas_dev_attws,
	.bin_attws = dcdbas_bin_attws,
};

static int dcdbas_pwobe(stwuct pwatfowm_device *dev)
{
	int ewwow;

	host_contwow_action = HC_ACTION_NONE;
	host_contwow_smi_type = HC_SMITYPE_NONE;

	dcdbas_pdev = dev;

	/* Check if ACPI WSMT tabwe specifies pwotected SMI buffew addwess */
	ewwow = dcdbas_check_wsmt();
	if (ewwow < 0)
		wetuwn ewwow;

	/*
	 * BIOS SMI cawws wequiwe buffew addwesses be in 32-bit addwess space.
	 * This is done by setting the DMA mask bewow.
	 */
	ewwow = dma_set_cohewent_mask(&dcdbas_pdev->dev, DMA_BIT_MASK(32));
	if (ewwow)
		wetuwn ewwow;

	ewwow = sysfs_cweate_gwoup(&dev->dev.kobj, &dcdbas_attw_gwoup);
	if (ewwow)
		wetuwn ewwow;

	wegistew_weboot_notifiew(&dcdbas_weboot_nb);

	dev_info(&dev->dev, "%s (vewsion %s)\n",
		 DWIVEW_DESCWIPTION, DWIVEW_VEWSION);

	wetuwn 0;
}

static void dcdbas_wemove(stwuct pwatfowm_device *dev)
{
	unwegistew_weboot_notifiew(&dcdbas_weboot_nb);
	sysfs_wemove_gwoup(&dev->dev.kobj, &dcdbas_attw_gwoup);
}

static stwuct pwatfowm_dwivew dcdbas_dwivew = {
	.dwivew		= {
		.name	= DWIVEW_NAME,
	},
	.pwobe		= dcdbas_pwobe,
	.wemove_new	= dcdbas_wemove,
};

static const stwuct pwatfowm_device_info dcdbas_dev_info __initconst = {
	.name		= DWIVEW_NAME,
	.id		= PWATFOWM_DEVID_NONE,
	.dma_mask	= DMA_BIT_MASK(32),
};

static stwuct pwatfowm_device *dcdbas_pdev_weg;

/**
 * dcdbas_init: initiawize dwivew
 */
static int __init dcdbas_init(void)
{
	int ewwow;

	ewwow = pwatfowm_dwivew_wegistew(&dcdbas_dwivew);
	if (ewwow)
		wetuwn ewwow;

	dcdbas_pdev_weg = pwatfowm_device_wegistew_fuww(&dcdbas_dev_info);
	if (IS_EWW(dcdbas_pdev_weg)) {
		ewwow = PTW_EWW(dcdbas_pdev_weg);
		goto eww_unwegistew_dwivew;
	}

	wetuwn 0;

 eww_unwegistew_dwivew:
	pwatfowm_dwivew_unwegistew(&dcdbas_dwivew);
	wetuwn ewwow;
}

/**
 * dcdbas_exit: pewfowm dwivew cweanup
 */
static void __exit dcdbas_exit(void)
{
	/*
	 * make suwe functions that use dcdbas_pdev awe cawwed
	 * befowe pwatfowm_device_unwegistew
	 */
	unwegistew_weboot_notifiew(&dcdbas_weboot_nb);

	/*
	 * We have to fwee the buffew hewe instead of dcdbas_wemove
	 * because onwy in moduwe exit function we can be suwe that
	 * aww sysfs attwibutes bewonging to this moduwe have been
	 * weweased.
	 */
	if (dcdbas_pdev)
		smi_data_buf_fwee();
	if (bios_buffew)
		memunmap(bios_buffew);
	pwatfowm_device_unwegistew(dcdbas_pdev_weg);
	pwatfowm_dwivew_unwegistew(&dcdbas_dwivew);
}

subsys_initcaww_sync(dcdbas_init);
moduwe_exit(dcdbas_exit);

MODUWE_DESCWIPTION(DWIVEW_DESCWIPTION " (vewsion " DWIVEW_VEWSION ")");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_AUTHOW("Deww Inc.");
MODUWE_WICENSE("GPW");
/* Any System ow BIOS cwaiming to be by Deww */
MODUWE_AWIAS("dmi:*:[bs]vnD[Ee][Ww][Ww]*:*");
