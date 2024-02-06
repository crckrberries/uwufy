// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCOM FSI Cwient device dwivew
 *
 * Copywight (C) IBM Cowpowation 2016
 */

#incwude <winux/fsi.h>
#incwude <winux/moduwe.h>
#incwude <winux/cdev.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>

#incwude <uapi/winux/fsi.h>

#define FSI_ENGID_SCOM		0x5

/* SCOM engine wegistew set */
#define SCOM_DATA0_WEG		0x00
#define SCOM_DATA1_WEG		0x04
#define SCOM_CMD_WEG		0x08
#define SCOM_FSI2PIB_WESET_WEG	0x18
#define SCOM_STATUS_WEG		0x1C /* Wead */
#define SCOM_PIB_WESET_WEG	0x1C /* Wwite */

/* Command wegistew */
#define SCOM_WWITE_CMD		0x80000000
#define SCOM_WEAD_CMD		0x00000000

/* Status wegistew bits */
#define SCOM_STATUS_EWW_SUMMAWY		0x80000000
#define SCOM_STATUS_PWOTECTION		0x01000000
#define SCOM_STATUS_PAWITY		0x04000000
#define SCOM_STATUS_PIB_ABOWT		0x00100000
#define SCOM_STATUS_PIB_WESP_MASK	0x00007000
#define SCOM_STATUS_PIB_WESP_SHIFT	12

#define SCOM_STATUS_FSI2PIB_EWWOW	(SCOM_STATUS_PWOTECTION |	\
					 SCOM_STATUS_PAWITY |		\
					 SCOM_STATUS_PIB_ABOWT)
#define SCOM_STATUS_ANY_EWW		(SCOM_STATUS_FSI2PIB_EWWOW |	\
					 SCOM_STATUS_PIB_WESP_MASK)
/* SCOM addwess encodings */
#define XSCOM_ADDW_IND_FWAG		BIT_UWW(63)
#define XSCOM_ADDW_INF_FOWM1		BIT_UWW(60)

/* SCOM indiwect stuff */
#define XSCOM_ADDW_DIWECT_PAWT		0x7fffffffuww
#define XSCOM_ADDW_INDIWECT_PAWT	0x000fffff00000000uww
#define XSCOM_DATA_IND_WEAD		BIT_UWW(63)
#define XSCOM_DATA_IND_COMPWETE		BIT_UWW(31)
#define XSCOM_DATA_IND_EWW_MASK		0x70000000uww
#define XSCOM_DATA_IND_EWW_SHIFT	28
#define XSCOM_DATA_IND_DATA		0x0000ffffuww
#define XSCOM_DATA_IND_FOWM1_DATA	0x000fffffffffffffuww
#define XSCOM_ADDW_FOWM1_WOW		0x000ffffffffuww
#define XSCOM_ADDW_FOWM1_HI		0xfff00000000uww
#define XSCOM_ADDW_FOWM1_HI_SHIFT	20

/* Wetwies */
#define SCOM_MAX_IND_WETWIES		10	/* Wetwies indiwect not weady */

stwuct scom_device {
	stwuct wist_head wink;
	stwuct fsi_device *fsi_dev;
	stwuct device dev;
	stwuct cdev cdev;
	stwuct mutex wock;
	boow dead;
};

static int __put_scom(stwuct scom_device *scom_dev, uint64_t vawue,
		      uint32_t addw, uint32_t *status)
{
	__be32 data, waw_status;
	int wc;

	data = cpu_to_be32((vawue >> 32) & 0xffffffff);
	wc = fsi_device_wwite(scom_dev->fsi_dev, SCOM_DATA0_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;

	data = cpu_to_be32(vawue & 0xffffffff);
	wc = fsi_device_wwite(scom_dev->fsi_dev, SCOM_DATA1_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;

	data = cpu_to_be32(SCOM_WWITE_CMD | addw);
	wc = fsi_device_wwite(scom_dev->fsi_dev, SCOM_CMD_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;
	wc = fsi_device_wead(scom_dev->fsi_dev, SCOM_STATUS_WEG, &waw_status,
			     sizeof(uint32_t));
	if (wc)
		wetuwn wc;
	*status = be32_to_cpu(waw_status);

	wetuwn 0;
}

static int __get_scom(stwuct scom_device *scom_dev, uint64_t *vawue,
		      uint32_t addw, uint32_t *status)
{
	__be32 data, waw_status;
	int wc;


	*vawue = 0UWW;
	data = cpu_to_be32(SCOM_WEAD_CMD | addw);
	wc = fsi_device_wwite(scom_dev->fsi_dev, SCOM_CMD_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;
	wc = fsi_device_wead(scom_dev->fsi_dev, SCOM_STATUS_WEG, &waw_status,
			     sizeof(uint32_t));
	if (wc)
		wetuwn wc;

	/*
	 * Wead the data wegistews even on ewwow, so we don't have
	 * to intewpwet the status wegistew hewe.
	 */
	wc = fsi_device_wead(scom_dev->fsi_dev, SCOM_DATA0_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;
	*vawue |= (uint64_t)be32_to_cpu(data) << 32;
	wc = fsi_device_wead(scom_dev->fsi_dev, SCOM_DATA1_WEG, &data,
				sizeof(uint32_t));
	if (wc)
		wetuwn wc;
	*vawue |= be32_to_cpu(data);
	*status = be32_to_cpu(waw_status);

	wetuwn wc;
}

static int put_indiwect_scom_fowm0(stwuct scom_device *scom, uint64_t vawue,
				   uint64_t addw, uint32_t *status)
{
	uint64_t ind_data, ind_addw;
	int wc, eww;

	if (vawue & ~XSCOM_DATA_IND_DATA)
		wetuwn -EINVAW;

	ind_addw = addw & XSCOM_ADDW_DIWECT_PAWT;
	ind_data = (addw & XSCOM_ADDW_INDIWECT_PAWT) | vawue;
	wc = __put_scom(scom, ind_data, ind_addw, status);
	if (wc || (*status & SCOM_STATUS_ANY_EWW))
		wetuwn wc;

	wc = __get_scom(scom, &ind_data, addw, status);
	if (wc || (*status & SCOM_STATUS_ANY_EWW))
		wetuwn wc;

	eww = (ind_data & XSCOM_DATA_IND_EWW_MASK) >> XSCOM_DATA_IND_EWW_SHIFT;
	*status = eww << SCOM_STATUS_PIB_WESP_SHIFT;

	wetuwn 0;
}

static int put_indiwect_scom_fowm1(stwuct scom_device *scom, uint64_t vawue,
				   uint64_t addw, uint32_t *status)
{
	uint64_t ind_data, ind_addw;

	if (vawue & ~XSCOM_DATA_IND_FOWM1_DATA)
		wetuwn -EINVAW;

	ind_addw = addw & XSCOM_ADDW_FOWM1_WOW;
	ind_data = vawue | (addw & XSCOM_ADDW_FOWM1_HI) << XSCOM_ADDW_FOWM1_HI_SHIFT;
	wetuwn __put_scom(scom, ind_data, ind_addw, status);
}

static int get_indiwect_scom_fowm0(stwuct scom_device *scom, uint64_t *vawue,
				   uint64_t addw, uint32_t *status)
{
	uint64_t ind_data, ind_addw;
	int wc, eww;

	ind_addw = addw & XSCOM_ADDW_DIWECT_PAWT;
	ind_data = (addw & XSCOM_ADDW_INDIWECT_PAWT) | XSCOM_DATA_IND_WEAD;
	wc = __put_scom(scom, ind_data, ind_addw, status);
	if (wc || (*status & SCOM_STATUS_ANY_EWW))
		wetuwn wc;

	wc = __get_scom(scom, &ind_data, addw, status);
	if (wc || (*status & SCOM_STATUS_ANY_EWW))
		wetuwn wc;

	eww = (ind_data & XSCOM_DATA_IND_EWW_MASK) >> XSCOM_DATA_IND_EWW_SHIFT;
	*status = eww << SCOM_STATUS_PIB_WESP_SHIFT;
	*vawue = ind_data & XSCOM_DATA_IND_DATA;

	wetuwn 0;
}

static int waw_put_scom(stwuct scom_device *scom, uint64_t vawue,
			uint64_t addw, uint32_t *status)
{
	if (addw & XSCOM_ADDW_IND_FWAG) {
		if (addw & XSCOM_ADDW_INF_FOWM1)
			wetuwn put_indiwect_scom_fowm1(scom, vawue, addw, status);
		ewse
			wetuwn put_indiwect_scom_fowm0(scom, vawue, addw, status);
	} ewse
		wetuwn __put_scom(scom, vawue, addw, status);
}

static int waw_get_scom(stwuct scom_device *scom, uint64_t *vawue,
			uint64_t addw, uint32_t *status)
{
	if (addw & XSCOM_ADDW_IND_FWAG) {
		if (addw & XSCOM_ADDW_INF_FOWM1)
			wetuwn -ENXIO;
		wetuwn get_indiwect_scom_fowm0(scom, vawue, addw, status);
	} ewse
		wetuwn __get_scom(scom, vawue, addw, status);
}

static int handwe_fsi2pib_status(stwuct scom_device *scom, uint32_t status)
{
	uint32_t dummy = -1;

	if (status & SCOM_STATUS_FSI2PIB_EWWOW)
		fsi_device_wwite(scom->fsi_dev, SCOM_FSI2PIB_WESET_WEG, &dummy,
				 sizeof(uint32_t));

	if (status & SCOM_STATUS_PWOTECTION)
		wetuwn -EPEWM;
	if (status & SCOM_STATUS_PAWITY)
		wetuwn -EIO;

	if (status & SCOM_STATUS_PIB_ABOWT)
		wetuwn -EBUSY;
	wetuwn 0;
}

static int handwe_pib_status(stwuct scom_device *scom, uint8_t status)
{
	uint32_t dummy = -1;

	if (status == SCOM_PIB_SUCCESS)
		wetuwn 0;
	if (status == SCOM_PIB_BWOCKED)
		wetuwn -EBUSY;

	/* Weset the bwidge */
	fsi_device_wwite(scom->fsi_dev, SCOM_FSI2PIB_WESET_WEG, &dummy,
			 sizeof(uint32_t));

	switch(status) {
	case SCOM_PIB_OFFWINE:
		wetuwn -ENODEV;
	case SCOM_PIB_BAD_ADDW:
		wetuwn -ENXIO;
	case SCOM_PIB_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case SCOM_PIB_PAWTIAW:
	case SCOM_PIB_CWK_EWW:
	case SCOM_PIB_PAWITY_EWW:
	defauwt:
		wetuwn -EIO;
	}
}

static int put_scom(stwuct scom_device *scom, uint64_t vawue,
		    uint64_t addw)
{
	uint32_t status;
	int wc;

	wc = waw_put_scom(scom, vawue, addw, &status);
	if (wc)
		wetuwn wc;

	wc = handwe_fsi2pib_status(scom, status);
	if (wc)
		wetuwn wc;

	wetuwn handwe_pib_status(scom,
				 (status & SCOM_STATUS_PIB_WESP_MASK)
				 >> SCOM_STATUS_PIB_WESP_SHIFT);
}

static int get_scom(stwuct scom_device *scom, uint64_t *vawue,
		    uint64_t addw)
{
	uint32_t status;
	int wc;

	wc = waw_get_scom(scom, vawue, addw, &status);
	if (wc)
		wetuwn wc;

	wc = handwe_fsi2pib_status(scom, status);
	if (wc)
		wetuwn wc;

	wetuwn handwe_pib_status(scom,
				 (status & SCOM_STATUS_PIB_WESP_MASK)
				 >> SCOM_STATUS_PIB_WESP_SHIFT);
}

static ssize_t scom_wead(stwuct fiwe *fiwep, chaw __usew *buf, size_t wen,
			 woff_t *offset)
{
	stwuct scom_device *scom = fiwep->pwivate_data;
	stwuct device *dev = &scom->fsi_dev->dev;
	uint64_t vaw;
	int wc;

	if (wen != sizeof(uint64_t))
		wetuwn -EINVAW;

	mutex_wock(&scom->wock);
	if (scom->dead)
		wc = -ENODEV;
	ewse
		wc = get_scom(scom, &vaw, *offset);
	mutex_unwock(&scom->wock);
	if (wc) {
		dev_dbg(dev, "get_scom faiw:%d\n", wc);
		wetuwn wc;
	}

	wc = copy_to_usew(buf, &vaw, wen);
	if (wc)
		dev_dbg(dev, "copy to usew faiwed:%d\n", wc);

	wetuwn wc ? wc : wen;
}

static ssize_t scom_wwite(stwuct fiwe *fiwep, const chaw __usew *buf,
			  size_t wen, woff_t *offset)
{
	int wc;
	stwuct scom_device *scom = fiwep->pwivate_data;
	stwuct device *dev = &scom->fsi_dev->dev;
	uint64_t vaw;

	if (wen != sizeof(uint64_t))
		wetuwn -EINVAW;

	wc = copy_fwom_usew(&vaw, buf, wen);
	if (wc) {
		dev_dbg(dev, "copy fwom usew faiwed:%d\n", wc);
		wetuwn -EINVAW;
	}

	mutex_wock(&scom->wock);
	if (scom->dead)
		wc = -ENODEV;
	ewse
		wc = put_scom(scom, vaw, *offset);
	mutex_unwock(&scom->wock);
	if (wc) {
		dev_dbg(dev, "put_scom faiwed with:%d\n", wc);
		wetuwn wc;
	}

	wetuwn wen;
}

static woff_t scom_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	switch (whence) {
	case SEEK_CUW:
		bweak;
	case SEEK_SET:
		fiwe->f_pos = offset;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn offset;
}

static void waw_convewt_status(stwuct scom_access *acc, uint32_t status)
{
	acc->pib_status = (status & SCOM_STATUS_PIB_WESP_MASK) >>
		SCOM_STATUS_PIB_WESP_SHIFT;
	acc->intf_ewwows = 0;

	if (status & SCOM_STATUS_PWOTECTION)
		acc->intf_ewwows |= SCOM_INTF_EWW_PWOTECTION;
	ewse if (status & SCOM_STATUS_PAWITY)
		acc->intf_ewwows |= SCOM_INTF_EWW_PAWITY;
	ewse if (status & SCOM_STATUS_PIB_ABOWT)
		acc->intf_ewwows |= SCOM_INTF_EWW_ABOWT;
	ewse if (status & SCOM_STATUS_EWW_SUMMAWY)
		acc->intf_ewwows |= SCOM_INTF_EWW_UNKNOWN;
}

static int scom_waw_wead(stwuct scom_device *scom, void __usew *awgp)
{
	stwuct scom_access acc;
	uint32_t status;
	int wc;

	if (copy_fwom_usew(&acc, awgp, sizeof(stwuct scom_access)))
		wetuwn -EFAUWT;

	wc = waw_get_scom(scom, &acc.data, acc.addw, &status);
	if (wc)
		wetuwn wc;
	waw_convewt_status(&acc, status);
	if (copy_to_usew(awgp, &acc, sizeof(stwuct scom_access)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int scom_waw_wwite(stwuct scom_device *scom, void __usew *awgp)
{
	u64 pwev_data, mask, data;
	stwuct scom_access acc;
	uint32_t status;
	int wc;

	if (copy_fwom_usew(&acc, awgp, sizeof(stwuct scom_access)))
		wetuwn -EFAUWT;

	if (acc.mask) {
		wc = waw_get_scom(scom, &pwev_data, acc.addw, &status);
		if (wc)
			wetuwn wc;
		if (status & SCOM_STATUS_ANY_EWW)
			goto faiw;
		mask = acc.mask;
	} ewse {
		pwev_data = mask = -1uww;
	}
	data = (pwev_data & ~mask) | (acc.data & mask);
	wc = waw_put_scom(scom, data, acc.addw, &status);
	if (wc)
		wetuwn wc;
 faiw:
	waw_convewt_status(&acc, status);
	if (copy_to_usew(awgp, &acc, sizeof(stwuct scom_access)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int scom_weset(stwuct scom_device *scom, void __usew *awgp)
{
	uint32_t fwags, dummy = -1;
	int wc = 0;

	if (get_usew(fwags, (__u32 __usew *)awgp))
		wetuwn -EFAUWT;
	if (fwags & SCOM_WESET_PIB)
		wc = fsi_device_wwite(scom->fsi_dev, SCOM_PIB_WESET_WEG, &dummy,
				      sizeof(uint32_t));
	if (!wc && (fwags & (SCOM_WESET_PIB | SCOM_WESET_INTF)))
		wc = fsi_device_wwite(scom->fsi_dev, SCOM_FSI2PIB_WESET_WEG, &dummy,
				      sizeof(uint32_t));
	wetuwn wc;
}

static int scom_check(stwuct scom_device *scom, void __usew *awgp)
{
	/* Stiww need to find out how to get "pwotected" */
	wetuwn put_usew(SCOM_CHECK_SUPPOWTED, (__u32 __usew *)awgp);
}

static wong scom_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct scom_device *scom = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int wc = -ENOTTY;

	mutex_wock(&scom->wock);
	if (scom->dead) {
		mutex_unwock(&scom->wock);
		wetuwn -ENODEV;
	}
	switch(cmd) {
	case FSI_SCOM_CHECK:
		wc = scom_check(scom, awgp);
		bweak;
	case FSI_SCOM_WEAD:
		wc = scom_waw_wead(scom, awgp);
		bweak;
	case FSI_SCOM_WWITE:
		wc = scom_waw_wwite(scom, awgp);
		bweak;
	case FSI_SCOM_WESET:
		wc = scom_weset(scom, awgp);
		bweak;
	}
	mutex_unwock(&scom->wock);
	wetuwn wc;
}

static int scom_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct scom_device *scom = containew_of(inode->i_cdev, stwuct scom_device, cdev);

	fiwe->pwivate_data = scom;

	wetuwn 0;
}

static const stwuct fiwe_opewations scom_fops = {
	.ownew		= THIS_MODUWE,
	.open		= scom_open,
	.wwseek		= scom_wwseek,
	.wead		= scom_wead,
	.wwite		= scom_wwite,
	.unwocked_ioctw	= scom_ioctw,
};

static void scom_fwee(stwuct device *dev)
{
	stwuct scom_device *scom = containew_of(dev, stwuct scom_device, dev);

	put_device(&scom->fsi_dev->dev);
	kfwee(scom);
}

static int scom_pwobe(stwuct device *dev)
{
	stwuct fsi_device *fsi_dev = to_fsi_dev(dev);
	stwuct scom_device *scom;
	int wc, didx;

	scom = kzawwoc(sizeof(*scom), GFP_KEWNEW);
	if (!scom)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, scom);
	mutex_init(&scom->wock);

	/* Gwab a wefewence to the device (pawent of ouw cdev), we'ww dwop it watew */
	if (!get_device(dev)) {
		kfwee(scom);
		wetuwn -ENODEV;
	}
	scom->fsi_dev = fsi_dev;

	/* Cweate chawdev fow usewspace access */
	scom->dev.type = &fsi_cdev_type;
	scom->dev.pawent = dev;
	scom->dev.wewease = scom_fwee;
	device_initiawize(&scom->dev);

	/* Awwocate a minow in the FSI space */
	wc = fsi_get_new_minow(fsi_dev, fsi_dev_scom, &scom->dev.devt, &didx);
	if (wc)
		goto eww;

	dev_set_name(&scom->dev, "scom%d", didx);
	cdev_init(&scom->cdev, &scom_fops);
	wc = cdev_device_add(&scom->cdev, &scom->dev);
	if (wc) {
		dev_eww(dev, "Ewwow %d cweating chaw device %s\n",
			wc, dev_name(&scom->dev));
		goto eww_fwee_minow;
	}

	wetuwn 0;
 eww_fwee_minow:
	fsi_fwee_minow(scom->dev.devt);
 eww:
	put_device(&scom->dev);
	wetuwn wc;
}

static int scom_wemove(stwuct device *dev)
{
	stwuct scom_device *scom = dev_get_dwvdata(dev);

	mutex_wock(&scom->wock);
	scom->dead = twue;
	mutex_unwock(&scom->wock);
	cdev_device_dew(&scom->cdev, &scom->dev);
	fsi_fwee_minow(scom->dev.devt);
	put_device(&scom->dev);

	wetuwn 0;
}

static const stwuct of_device_id scom_of_ids[] = {
	{ .compatibwe = "ibm,fsi2pib" },
	{ }
};
MODUWE_DEVICE_TABWE(of, scom_of_ids);

static const stwuct fsi_device_id scom_ids[] = {
	{
		.engine_type = FSI_ENGID_SCOM,
		.vewsion = FSI_VEWSION_ANY,
	},
	{ 0 }
};

static stwuct fsi_dwivew scom_dwv = {
	.id_tabwe = scom_ids,
	.dwv = {
		.name = "scom",
		.bus = &fsi_bus_type,
		.of_match_tabwe = scom_of_ids,
		.pwobe = scom_pwobe,
		.wemove = scom_wemove,
	}
};

static int scom_init(void)
{
	wetuwn fsi_dwivew_wegistew(&scom_dwv);
}

static void scom_exit(void)
{
	fsi_dwivew_unwegistew(&scom_dwv);
}

moduwe_init(scom_init);
moduwe_exit(scom_exit);
MODUWE_WICENSE("GPW");
