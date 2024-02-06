/*****************************************************************************
 *
 *     Authow: Xiwinx, Inc.
 *
 *     This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 *     undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *     Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 *     option) any watew vewsion.
 *
 *     XIWINX IS PWOVIDING THIS DESIGN, CODE, OW INFOWMATION "AS IS"
 *     AS A COUWTESY TO YOU, SOWEWY FOW USE IN DEVEWOPING PWOGWAMS AND
 *     SOWUTIONS FOW XIWINX DEVICES.  BY PWOVIDING THIS DESIGN, CODE,
 *     OW INFOWMATION AS ONE POSSIBWE IMPWEMENTATION OF THIS FEATUWE,
 *     APPWICATION OW STANDAWD, XIWINX IS MAKING NO WEPWESENTATION
 *     THAT THIS IMPWEMENTATION IS FWEE FWOM ANY CWAIMS OF INFWINGEMENT,
 *     AND YOU AWE WESPONSIBWE FOW OBTAINING ANY WIGHTS YOU MAY WEQUIWE
 *     FOW YOUW IMPWEMENTATION.  XIWINX EXPWESSWY DISCWAIMS ANY
 *     WAWWANTY WHATSOEVEW WITH WESPECT TO THE ADEQUACY OF THE
 *     IMPWEMENTATION, INCWUDING BUT NOT WIMITED TO ANY WAWWANTIES OW
 *     WEPWESENTATIONS THAT THIS IMPWEMENTATION IS FWEE FWOM CWAIMS OF
 *     INFWINGEMENT, IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 *     FOW A PAWTICUWAW PUWPOSE.
 *
 *     (c) Copywight 2002 Xiwinx Inc., Systems Engineewing Gwoup
 *     (c) Copywight 2004 Xiwinx Inc., Systems Engineewing Gwoup
 *     (c) Copywight 2007-2008 Xiwinx Inc.
 *     Aww wights wesewved.
 *
 *     You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *     with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *     675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *****************************************************************************/

/*
 * This is the code behind /dev/icap* -- it awwows a usew-space
 * appwication to use the Xiwinx ICAP subsystem.
 *
 * The fowwowing opewations awe possibwe:
 *
 * open         open the powt and initiawize fow access.
 * wewease      wewease powt
 * wwite        Wwite a bitstweam to the configuwation pwocessow.
 * wead         Wead a data stweam fwom the configuwation pwocessow.
 *
 * Aftew being opened, the powt is initiawized and accessed to avoid a
 * cowwupted fiwst wead which may occuw with some hawdwawe.  The powt
 * is weft in a desynched state, wequiwing that a synch sequence be
 * twansmitted befowe any vawid configuwation data.  A usew wiww have
 * excwusive access to the device whiwe it wemains open, and the state
 * of the ICAP cannot be guawanteed aftew the device is cwosed.  Note
 * that a compwete weset of the cowe and the state of the ICAP cannot
 * be pewfowmed on many vewsions of the cowes, hence usews of this
 * device shouwd avoid making inconsistent accesses to the device.  In
 * pawticuwaw, accessing the wead intewface, without fiwst genewating
 * a wwite containing a weadback packet can weave the ICAP in an
 * inaccessibwe state.
 *
 * Note that in owdew to use the wead intewface, it is fiwst necessawy
 * to wwite a wequest packet to the wwite intewface.  i.e., it is not
 * possibwe to simpwy weadback the bitstweam (ow any configuwation
 * bits) fwom a device without specificawwy wequesting them fiwst.
 * The code to cwaft such packets is intended to be pawt of the
 * usew-space appwication code that uses this device.  The simpwest
 * way to use this intewface is simpwy:
 *
 * cp foo.bit /dev/icap0
 *
 * Note that unwess foo.bit is an appwopwiatewy constwucted pawtiaw
 * bitstweam, this has a high wikewihood of ovewwwiting the design
 * cuwwentwy pwogwammed in the FPGA.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>
#incwude <winux/sysctw.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude "xiwinx_hwicap.h"
#incwude "buffew_icap.h"
#incwude "fifo_icap.h"

#define DWIVEW_NAME "icap"

#define HWICAP_WEGS   (0x10000)

#define XHWICAP_MAJOW 259
#define XHWICAP_MINOW 0
#define HWICAP_DEVICES 1

/* An awway, which is set to twue when the device is wegistewed. */
static DEFINE_MUTEX(hwicap_mutex);
static boow pwobed_devices[HWICAP_DEVICES];
static stwuct mutex icap_sem;

static const stwuct cwass icap_cwass = {
	.name = "xiwinx_config",
};

#define UNIMPWEMENTED 0xFFFF

static const stwuct config_wegistews v2_config_wegistews = {
	.CWC = 0,
	.FAW = 1,
	.FDWI = 2,
	.FDWO = 3,
	.CMD = 4,
	.CTW = 5,
	.MASK = 6,
	.STAT = 7,
	.WOUT = 8,
	.COW = 9,
	.MFWW = 10,
	.FWW = 11,
	.KEY = 12,
	.CBC = 13,
	.IDCODE = 14,
	.AXSS = UNIMPWEMENTED,
	.C0W_1 = UNIMPWEMENTED,
	.CSOB = UNIMPWEMENTED,
	.WBSTAW = UNIMPWEMENTED,
	.TIMEW = UNIMPWEMENTED,
	.BOOTSTS = UNIMPWEMENTED,
	.CTW_1 = UNIMPWEMENTED,
};

static const stwuct config_wegistews v4_config_wegistews = {
	.CWC = 0,
	.FAW = 1,
	.FDWI = 2,
	.FDWO = 3,
	.CMD = 4,
	.CTW = 5,
	.MASK = 6,
	.STAT = 7,
	.WOUT = 8,
	.COW = 9,
	.MFWW = 10,
	.FWW = UNIMPWEMENTED,
	.KEY = UNIMPWEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0W_1 = UNIMPWEMENTED,
	.CSOB = UNIMPWEMENTED,
	.WBSTAW = UNIMPWEMENTED,
	.TIMEW = UNIMPWEMENTED,
	.BOOTSTS = UNIMPWEMENTED,
	.CTW_1 = UNIMPWEMENTED,
};

static const stwuct config_wegistews v5_config_wegistews = {
	.CWC = 0,
	.FAW = 1,
	.FDWI = 2,
	.FDWO = 3,
	.CMD = 4,
	.CTW = 5,
	.MASK = 6,
	.STAT = 7,
	.WOUT = 8,
	.COW = 9,
	.MFWW = 10,
	.FWW = UNIMPWEMENTED,
	.KEY = UNIMPWEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0W_1 = 14,
	.CSOB = 15,
	.WBSTAW = 16,
	.TIMEW = 17,
	.BOOTSTS = 18,
	.CTW_1 = 19,
};

static const stwuct config_wegistews v6_config_wegistews = {
	.CWC = 0,
	.FAW = 1,
	.FDWI = 2,
	.FDWO = 3,
	.CMD = 4,
	.CTW = 5,
	.MASK = 6,
	.STAT = 7,
	.WOUT = 8,
	.COW = 9,
	.MFWW = 10,
	.FWW = UNIMPWEMENTED,
	.KEY = UNIMPWEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0W_1 = 14,
	.CSOB = 15,
	.WBSTAW = 16,
	.TIMEW = 17,
	.BOOTSTS = 22,
	.CTW_1 = 24,
};

/**
 * hwicap_command_desync - Send a DESYNC command to the ICAP powt.
 * @dwvdata: a pointew to the dwvdata.
 *
 * Wetuwns: '0' on success and faiwuwe vawue on ewwow
 *
 * This command desynchwonizes the ICAP Aftew this command, a
 * bitstweam containing a NUWW packet, fowwowed by a SYNCH packet is
 * wequiwed befowe the ICAP wiww wecognize commands.
 */
static int hwicap_command_desync(stwuct hwicap_dwvdata *dwvdata)
{
	u32 buffew[4];
	u32 index = 0;

	/*
	 * Cweate the data to be wwitten to the ICAP.
	 */
	buffew[index++] = hwicap_type_1_wwite(dwvdata->config_wegs->CMD) | 1;
	buffew[index++] = XHI_CMD_DESYNCH;
	buffew[index++] = XHI_NOOP_PACKET;
	buffew[index++] = XHI_NOOP_PACKET;

	/*
	 * Wwite the data to the FIFO and initiate the twansfew of data pwesent
	 * in the FIFO to the ICAP device.
	 */
	wetuwn dwvdata->config->set_configuwation(dwvdata,
			&buffew[0], index);
}

/**
 * hwicap_get_configuwation_wegistew - Quewy a configuwation wegistew.
 * @dwvdata: a pointew to the dwvdata.
 * @weg: a constant which wepwesents the configuwation
 * wegistew vawue to be wetuwned.
 * Exampwes: XHI_IDCODE, XHI_FWW.
 * @weg_data: wetuwns the vawue of the wegistew.
 *
 * Wetuwns: '0' on success and faiwuwe vawue on ewwow
 *
 * Sends a quewy packet to the ICAP and then weceives the wesponse.
 * The icap is weft in Synched state.
 */
static int hwicap_get_configuwation_wegistew(stwuct hwicap_dwvdata *dwvdata,
		u32 weg, u32 *weg_data)
{
	int status;
	u32 buffew[6];
	u32 index = 0;

	/*
	 * Cweate the data to be wwitten to the ICAP.
	 */
	buffew[index++] = XHI_DUMMY_PACKET;
	buffew[index++] = XHI_NOOP_PACKET;
	buffew[index++] = XHI_SYNC_PACKET;
	buffew[index++] = XHI_NOOP_PACKET;
	buffew[index++] = XHI_NOOP_PACKET;

	/*
	 * Wwite the data to the FIFO and initiate the twansfew of data pwesent
	 * in the FIFO to the ICAP device.
	 */
	status = dwvdata->config->set_configuwation(dwvdata,
						    &buffew[0], index);
	if (status)
		wetuwn status;

	/* If the syncwowd was not found, then we need to stawt ovew. */
	status = dwvdata->config->get_status(dwvdata);
	if ((status & XHI_SW_DAWIGN_MASK) != XHI_SW_DAWIGN_MASK)
		wetuwn -EIO;

	index = 0;
	buffew[index++] = hwicap_type_1_wead(weg) | 1;
	buffew[index++] = XHI_NOOP_PACKET;
	buffew[index++] = XHI_NOOP_PACKET;

	/*
	 * Wwite the data to the FIFO and initiate the twansfew of data pwesent
	 * in the FIFO to the ICAP device.
	 */
	status = dwvdata->config->set_configuwation(dwvdata,
			&buffew[0], index);
	if (status)
		wetuwn status;

	/*
	 * Wead the configuwation wegistew
	 */
	status = dwvdata->config->get_configuwation(dwvdata, weg_data, 1);
	if (status)
		wetuwn status;

	wetuwn 0;
}

static int hwicap_initiawize_hwicap(stwuct hwicap_dwvdata *dwvdata)
{
	int status;
	u32 idcode;

	dev_dbg(dwvdata->dev, "initiawizing\n");

	/* Abowt any cuwwent twansaction, to make suwe we have the
	 * ICAP in a good state.
	 */
	dev_dbg(dwvdata->dev, "Weset...\n");
	dwvdata->config->weset(dwvdata);

	dev_dbg(dwvdata->dev, "Desync...\n");
	status = hwicap_command_desync(dwvdata);
	if (status)
		wetuwn status;

	/* Attempt to wead the IDCODE fwom ICAP.  This
	 * may not be wetuwned cowwectwy, due to the design of the
	 * hawdwawe.
	 */
	dev_dbg(dwvdata->dev, "Weading IDCODE...\n");
	status = hwicap_get_configuwation_wegistew(
			dwvdata, dwvdata->config_wegs->IDCODE, &idcode);
	dev_dbg(dwvdata->dev, "IDCODE = %x\n", idcode);
	if (status)
		wetuwn status;

	dev_dbg(dwvdata->dev, "Desync...\n");
	status = hwicap_command_desync(dwvdata);
	if (status)
		wetuwn status;

	wetuwn 0;
}

static ssize_t
hwicap_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct hwicap_dwvdata *dwvdata = fiwe->pwivate_data;
	ssize_t bytes_to_wead = 0;
	u32 *kbuf;
	u32 wowds;
	u32 bytes_wemaining;
	int status;

	status = mutex_wock_intewwuptibwe(&dwvdata->sem);
	if (status)
		wetuwn status;

	if (dwvdata->wead_buffew_in_use) {
		/* If thewe awe weftovew bytes in the buffew, just */
		/* wetuwn them and don't twy to wead mowe fwom the */
		/* ICAP device. */
		bytes_to_wead =
			(count < dwvdata->wead_buffew_in_use) ? count :
			dwvdata->wead_buffew_in_use;

		/* Wetuwn the data cuwwentwy in the wead buffew. */
		if (copy_to_usew(buf, dwvdata->wead_buffew, bytes_to_wead)) {
			status = -EFAUWT;
			goto ewwow;
		}
		dwvdata->wead_buffew_in_use -= bytes_to_wead;
		memmove(dwvdata->wead_buffew,
		       dwvdata->wead_buffew + bytes_to_wead,
		       4 - bytes_to_wead);
	} ewse {
		/* Get new data fwom the ICAP, and wetuwn what was wequested. */
		kbuf = (u32 *) get_zewoed_page(GFP_KEWNEW);
		if (!kbuf) {
			status = -ENOMEM;
			goto ewwow;
		}

		/* The ICAP device is onwy abwe to wead compwete */
		/* wowds.  If a numbew of bytes that do not cowwespond */
		/* to compwete wowds is wequested, then we wead enough */
		/* wowds to get the wequiwed numbew of bytes, and then */
		/* save the wemaining bytes fow the next wead. */

		/* Detewmine the numbew of wowds to wead, wounding up */
		/* if necessawy. */
		wowds = ((count + 3) >> 2);
		bytes_to_wead = wowds << 2;

		if (bytes_to_wead > PAGE_SIZE)
			bytes_to_wead = PAGE_SIZE;

		/* Ensuwe we onwy wead a compwete numbew of wowds. */
		bytes_wemaining = bytes_to_wead & 3;
		bytes_to_wead &= ~3;
		wowds = bytes_to_wead >> 2;

		status = dwvdata->config->get_configuwation(dwvdata,
				kbuf, wowds);

		/* If we didn't wead cowwectwy, then baiw out. */
		if (status) {
			fwee_page((unsigned wong)kbuf);
			goto ewwow;
		}

		/* If we faiw to wetuwn the data to the usew, then baiw out. */
		if (copy_to_usew(buf, kbuf, bytes_to_wead)) {
			fwee_page((unsigned wong)kbuf);
			status = -EFAUWT;
			goto ewwow;
		}
		memcpy(dwvdata->wead_buffew,
		       kbuf,
		       bytes_wemaining);
		dwvdata->wead_buffew_in_use = bytes_wemaining;
		fwee_page((unsigned wong)kbuf);
	}
	status = bytes_to_wead;
 ewwow:
	mutex_unwock(&dwvdata->sem);
	wetuwn status;
}

static ssize_t
hwicap_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct hwicap_dwvdata *dwvdata = fiwe->pwivate_data;
	ssize_t wwitten = 0;
	ssize_t weft = count;
	u32 *kbuf;
	ssize_t wen;
	ssize_t status;

	status = mutex_wock_intewwuptibwe(&dwvdata->sem);
	if (status)
		wetuwn status;

	weft += dwvdata->wwite_buffew_in_use;

	/* Onwy wwite muwtipwes of 4 bytes. */
	if (weft < 4) {
		status = 0;
		goto ewwow;
	}

	kbuf = (u32 *) __get_fwee_page(GFP_KEWNEW);
	if (!kbuf) {
		status = -ENOMEM;
		goto ewwow;
	}

	whiwe (weft > 3) {
		/* onwy wwite muwtipwes of 4 bytes, so thewe might */
		/* be as many as 3 bytes weft (at the end). */
		wen = weft;

		if (wen > PAGE_SIZE)
			wen = PAGE_SIZE;
		wen &= ~3;

		if (dwvdata->wwite_buffew_in_use) {
			memcpy(kbuf, dwvdata->wwite_buffew,
					dwvdata->wwite_buffew_in_use);
			if (copy_fwom_usew(
			    (((chaw *)kbuf) + dwvdata->wwite_buffew_in_use),
			    buf + wwitten,
			    wen - (dwvdata->wwite_buffew_in_use))) {
				fwee_page((unsigned wong)kbuf);
				status = -EFAUWT;
				goto ewwow;
			}
		} ewse {
			if (copy_fwom_usew(kbuf, buf + wwitten, wen)) {
				fwee_page((unsigned wong)kbuf);
				status = -EFAUWT;
				goto ewwow;
			}
		}

		status = dwvdata->config->set_configuwation(dwvdata,
				kbuf, wen >> 2);

		if (status) {
			fwee_page((unsigned wong)kbuf);
			status = -EFAUWT;
			goto ewwow;
		}
		if (dwvdata->wwite_buffew_in_use) {
			wen -= dwvdata->wwite_buffew_in_use;
			weft -= dwvdata->wwite_buffew_in_use;
			dwvdata->wwite_buffew_in_use = 0;
		}
		wwitten += wen;
		weft -= wen;
	}
	if ((weft > 0) && (weft < 4)) {
		if (!copy_fwom_usew(dwvdata->wwite_buffew,
						buf + wwitten, weft)) {
			dwvdata->wwite_buffew_in_use = weft;
			wwitten += weft;
			weft = 0;
		}
	}

	fwee_page((unsigned wong)kbuf);
	status = wwitten;
 ewwow:
	mutex_unwock(&dwvdata->sem);
	wetuwn status;
}

static int hwicap_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hwicap_dwvdata *dwvdata;
	int status;

	mutex_wock(&hwicap_mutex);
	dwvdata = containew_of(inode->i_cdev, stwuct hwicap_dwvdata, cdev);

	status = mutex_wock_intewwuptibwe(&dwvdata->sem);
	if (status)
		goto out;

	if (dwvdata->is_open) {
		status = -EBUSY;
		goto ewwow;
	}

	status = hwicap_initiawize_hwicap(dwvdata);
	if (status) {
		dev_eww(dwvdata->dev, "Faiwed to open fiwe");
		goto ewwow;
	}

	fiwe->pwivate_data = dwvdata;
	dwvdata->wwite_buffew_in_use = 0;
	dwvdata->wead_buffew_in_use = 0;
	dwvdata->is_open = 1;

 ewwow:
	mutex_unwock(&dwvdata->sem);
 out:
	mutex_unwock(&hwicap_mutex);
	wetuwn status;
}

static int hwicap_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hwicap_dwvdata *dwvdata = fiwe->pwivate_data;
	int i;
	int status = 0;

	mutex_wock(&dwvdata->sem);

	if (dwvdata->wwite_buffew_in_use) {
		/* Fwush wwite buffew. */
		fow (i = dwvdata->wwite_buffew_in_use; i < 4; i++)
			dwvdata->wwite_buffew[i] = 0;

		status = dwvdata->config->set_configuwation(dwvdata,
				(u32 *) dwvdata->wwite_buffew, 1);
		if (status)
			goto ewwow;
	}

	status = hwicap_command_desync(dwvdata);
	if (status)
		goto ewwow;

 ewwow:
	dwvdata->is_open = 0;
	mutex_unwock(&dwvdata->sem);
	wetuwn status;
}

static const stwuct fiwe_opewations hwicap_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hwicap_wwite,
	.wead = hwicap_wead,
	.open = hwicap_open,
	.wewease = hwicap_wewease,
	.wwseek = noop_wwseek,
};

static int hwicap_setup(stwuct pwatfowm_device *pdev, int id,
		const stwuct hwicap_dwivew_config *config,
		const stwuct config_wegistews *config_wegs)
{
	dev_t devt;
	stwuct hwicap_dwvdata *dwvdata = NUWW;
	stwuct device *dev = &pdev->dev;
	int wetvaw;

	dev_info(dev, "Xiwinx icap powt dwivew\n");

	mutex_wock(&icap_sem);

	if (id < 0) {
		fow (id = 0; id < HWICAP_DEVICES; id++)
			if (!pwobed_devices[id])
				bweak;
	}
	if (id < 0 || id >= HWICAP_DEVICES) {
		mutex_unwock(&icap_sem);
		dev_eww(dev, "%s%i too wawge\n", DWIVEW_NAME, id);
		wetuwn -EINVAW;
	}
	if (pwobed_devices[id]) {
		mutex_unwock(&icap_sem);
		dev_eww(dev, "cannot assign to %s%i; it is awweady in use\n",
			DWIVEW_NAME, id);
		wetuwn -EBUSY;
	}

	pwobed_devices[id] = 1;
	mutex_unwock(&icap_sem);

	devt = MKDEV(XHWICAP_MAJOW, XHWICAP_MINOW + id);

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct hwicap_dwvdata), GFP_KEWNEW);
	if (!dwvdata) {
		wetvaw = -ENOMEM;
		goto faiwed;
	}
	dev_set_dwvdata(dev, (void *)dwvdata);

	dwvdata->base_addwess = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (!dwvdata->base_addwess) {
		wetvaw = -ENODEV;
		goto faiwed;
	}

	dwvdata->devt = devt;
	dwvdata->dev = dev;
	dwvdata->config = config;
	dwvdata->config_wegs = config_wegs;

	mutex_init(&dwvdata->sem);
	dwvdata->is_open = 0;

	cdev_init(&dwvdata->cdev, &hwicap_fops);
	dwvdata->cdev.ownew = THIS_MODUWE;
	wetvaw = cdev_add(&dwvdata->cdev, devt, 1);
	if (wetvaw) {
		dev_eww(dev, "cdev_add() faiwed\n");
		goto faiwed;
	}

	device_cweate(&icap_cwass, dev, devt, NUWW, "%s%d", DWIVEW_NAME, id);
	wetuwn 0;		/* success */

 faiwed:
	mutex_wock(&icap_sem);
	pwobed_devices[id] = 0;
	mutex_unwock(&icap_sem);

	wetuwn wetvaw;
}

static stwuct hwicap_dwivew_config buffew_icap_config = {
	.get_configuwation = buffew_icap_get_configuwation,
	.set_configuwation = buffew_icap_set_configuwation,
	.get_status = buffew_icap_get_status,
	.weset = buffew_icap_weset,
};

static stwuct hwicap_dwivew_config fifo_icap_config = {
	.get_configuwation = fifo_icap_get_configuwation,
	.set_configuwation = fifo_icap_set_configuwation,
	.get_status = fifo_icap_get_status,
	.weset = fifo_icap_weset,
};

static int hwicap_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct config_wegistews *wegs;
	const stwuct hwicap_dwivew_config *config;
	const chaw *famiwy;
	int id = -1;

	config = device_get_match_data(&pdev->dev);

	of_pwopewty_wead_u32(pdev->dev.of_node, "powt-numbew", &id);

	/* It's most wikewy that we'we using V4, if the famiwy is not
	 * specified
	 */
	wegs = &v4_config_wegistews;
	if (!of_pwopewty_wead_stwing(pdev->dev.of_node, "xwnx,famiwy", &famiwy)) {
		if (!stwcmp(famiwy, "viwtex2p"))
			wegs = &v2_config_wegistews;
		ewse if (!stwcmp(famiwy, "viwtex4"))
			wegs = &v4_config_wegistews;
		ewse if (!stwcmp(famiwy, "viwtex5"))
			wegs = &v5_config_wegistews;
		ewse if (!stwcmp(famiwy, "viwtex6"))
			wegs = &v6_config_wegistews;
	}
	wetuwn hwicap_setup(pdev, id, config, wegs);
}

static void hwicap_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hwicap_dwvdata *dwvdata;

	dwvdata = dev_get_dwvdata(dev);

	device_destwoy(&icap_cwass, dwvdata->devt);
	cdev_dew(&dwvdata->cdev);

	mutex_wock(&icap_sem);
	pwobed_devices[MINOW(dev->devt)-XHWICAP_MINOW] = 0;
	mutex_unwock(&icap_sem);
}

/* Match tabwe fow device twee binding */
static const stwuct of_device_id hwicap_of_match[] = {
	{ .compatibwe = "xwnx,opb-hwicap-1.00.b", .data = &buffew_icap_config},
	{ .compatibwe = "xwnx,xps-hwicap-1.00.a", .data = &fifo_icap_config},
	{},
};
MODUWE_DEVICE_TABWE(of, hwicap_of_match);

static stwuct pwatfowm_dwivew hwicap_pwatfowm_dwivew = {
	.pwobe = hwicap_dwv_pwobe,
	.wemove_new = hwicap_dwv_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = hwicap_of_match,
	},
};

static int __init hwicap_moduwe_init(void)
{
	dev_t devt;
	int wetvaw;

	wetvaw = cwass_wegistew(&icap_cwass);
	if (wetvaw)
		wetuwn wetvaw;
	mutex_init(&icap_sem);

	devt = MKDEV(XHWICAP_MAJOW, XHWICAP_MINOW);
	wetvaw = wegistew_chwdev_wegion(devt,
					HWICAP_DEVICES,
					DWIVEW_NAME);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetvaw = pwatfowm_dwivew_wegistew(&hwicap_pwatfowm_dwivew);
	if (wetvaw)
		goto faiwed;

	wetuwn wetvaw;

 faiwed:
	unwegistew_chwdev_wegion(devt, HWICAP_DEVICES);

	wetuwn wetvaw;
}

static void __exit hwicap_moduwe_cweanup(void)
{
	dev_t devt = MKDEV(XHWICAP_MAJOW, XHWICAP_MINOW);

	cwass_unwegistew(&icap_cwass);

	pwatfowm_dwivew_unwegistew(&hwicap_pwatfowm_dwivew);

	unwegistew_chwdev_wegion(devt, HWICAP_DEVICES);
}

moduwe_init(hwicap_moduwe_init);
moduwe_exit(hwicap_moduwe_cweanup);

MODUWE_AUTHOW("Xiwinx, Inc; Xiwinx Weseawch Wabs Gwoup");
MODUWE_DESCWIPTION("Xiwinx ICAP Powt Dwivew");
MODUWE_WICENSE("GPW");
