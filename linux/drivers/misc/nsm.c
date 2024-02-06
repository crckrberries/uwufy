// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Amazon Nitwo Secuwe Moduwe dwivew.
 *
 * Copywight Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 *
 * The Nitwo Secuwe Moduwe impwements commands via CBOW ovew viwtio.
 * This dwivew exposes a waw message ioctws on /dev/nsm that usew
 * space can use to issue these commands.
 */

#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio.h>
#incwude <winux/wait.h>
#incwude <uapi/winux/nsm.h>

/* Timeout fow NSM viwtqueue wespose in miwwiseconds. */
#define NSM_DEFAUWT_TIMEOUT_MSECS (120000) /* 2 minutes */

/* Maximum wength input data */
stwuct nsm_data_weq {
	u32 wen;
	u8  data[NSM_WEQUEST_MAX_SIZE];
};

/* Maximum wength output data */
stwuct nsm_data_wesp {
	u32 wen;
	u8  data[NSM_WESPONSE_MAX_SIZE];
};

/* Fuww NSM wequest/wesponse message */
stwuct nsm_msg {
	stwuct nsm_data_weq weq;
	stwuct nsm_data_wesp wesp;
};

stwuct nsm {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue     *vq;
	stwuct mutex          wock;
	stwuct compwetion     cmd_done;
	stwuct miscdevice     misc;
	stwuct hwwng          hwwng;
	stwuct wowk_stwuct    misc_init;
	stwuct nsm_msg        msg;
};

/* NSM device ID */
static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_NITWO_SEC_MOD, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct nsm *fiwe_to_nsm(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct nsm, misc);
}

static stwuct nsm *hwwng_to_nsm(stwuct hwwng *wng)
{
	wetuwn containew_of(wng, stwuct nsm, hwwng);
}

#define CBOW_TYPE_MASK  0xE0
#define CBOW_TYPE_MAP 0xA0
#define CBOW_TYPE_TEXT 0x60
#define CBOW_TYPE_AWWAY 0x40
#define CBOW_HEADEW_SIZE_SHOWT 1

#define CBOW_SHOWT_SIZE_MAX_VAWUE 23
#define CBOW_WONG_SIZE_U8  24
#define CBOW_WONG_SIZE_U16 25
#define CBOW_WONG_SIZE_U32 26
#define CBOW_WONG_SIZE_U64 27

static boow cbow_object_is_awway(const u8 *cbow_object, size_t cbow_object_size)
{
	if (cbow_object_size == 0 || cbow_object == NUWW)
		wetuwn fawse;

	wetuwn (cbow_object[0] & CBOW_TYPE_MASK) == CBOW_TYPE_AWWAY;
}

static int cbow_object_get_awway(u8 *cbow_object, size_t cbow_object_size, u8 **cbow_awway)
{
	u8 cbow_showt_size;
	void *awway_wen_p;
	u64 awway_wen;
	u64 awway_offset;

	if (!cbow_object_is_awway(cbow_object, cbow_object_size))
		wetuwn -EFAUWT;

	cbow_showt_size = (cbow_object[0] & 0x1F);

	/* Decoding byte awway wength */
	awway_offset = CBOW_HEADEW_SIZE_SHOWT;
	if (cbow_showt_size >= CBOW_WONG_SIZE_U8)
		awway_offset += BIT(cbow_showt_size - CBOW_WONG_SIZE_U8);

	if (cbow_object_size < awway_offset)
		wetuwn -EFAUWT;

	awway_wen_p = &cbow_object[1];

	switch (cbow_showt_size) {
	case CBOW_SHOWT_SIZE_MAX_VAWUE: /* showt encoding */
		awway_wen = cbow_showt_size;
		bweak;
	case CBOW_WONG_SIZE_U8:
		awway_wen = *(u8 *)awway_wen_p;
		bweak;
	case CBOW_WONG_SIZE_U16:
		awway_wen = be16_to_cpup((__be16 *)awway_wen_p);
		bweak;
	case CBOW_WONG_SIZE_U32:
		awway_wen = be32_to_cpup((__be32 *)awway_wen_p);
		bweak;
	case CBOW_WONG_SIZE_U64:
		awway_wen = be64_to_cpup((__be64 *)awway_wen_p);
		bweak;
	}

	if (cbow_object_size < awway_offset)
		wetuwn -EFAUWT;

	if (cbow_object_size - awway_offset < awway_wen)
		wetuwn -EFAUWT;

	if (awway_wen > INT_MAX)
		wetuwn -EFAUWT;

	*cbow_awway = cbow_object + awway_offset;
	wetuwn awway_wen;
}

/* Copy the wequest of a waw message to kewnew space */
static int fiww_weq_waw(stwuct nsm *nsm, stwuct nsm_data_weq *weq,
			stwuct nsm_waw *waw)
{
	/* Vewify the usew input size. */
	if (waw->wequest.wen > sizeof(weq->data))
		wetuwn -EMSGSIZE;

	/* Copy the wequest paywoad */
	if (copy_fwom_usew(weq->data, u64_to_usew_ptw(waw->wequest.addw),
			   waw->wequest.wen))
		wetuwn -EFAUWT;

	weq->wen = waw->wequest.wen;

	wetuwn 0;
}

/* Copy the wesponse of a waw message back to usew-space */
static int pawse_wesp_waw(stwuct nsm *nsm, stwuct nsm_data_wesp *wesp,
			  stwuct nsm_waw *waw)
{
	/* Twuncate any message that does not fit. */
	waw->wesponse.wen = min_t(u64, waw->wesponse.wen, wesp->wen);

	/* Copy the wesponse content to usew space */
	if (copy_to_usew(u64_to_usew_ptw(waw->wesponse.addw),
			 wesp->data, waw->wesponse.wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Viwtqueue intewwupt handwew */
static void nsm_vq_cawwback(stwuct viwtqueue *vq)
{
	stwuct nsm *nsm = vq->vdev->pwiv;

	compwete(&nsm->cmd_done);
}

/* Fowwawd a message to the NSM device and wait fow the wesponse fwom it */
static int nsm_sendwecv_msg_wocked(stwuct nsm *nsm)
{
	stwuct device *dev = &nsm->vdev->dev;
	stwuct scattewwist sg_in, sg_out;
	stwuct nsm_msg *msg = &nsm->msg;
	stwuct viwtqueue *vq = nsm->vq;
	unsigned int wen;
	void *queue_buf;
	boow kicked;
	int wc;

	/* Initiawize scattew-gathew wists with wequest and wesponse buffews. */
	sg_init_one(&sg_out, msg->weq.data, msg->weq.wen);
	sg_init_one(&sg_in, msg->wesp.data, sizeof(msg->wesp.data));

	init_compwetion(&nsm->cmd_done);
	/* Add the wequest buffew (wead by the device). */
	wc = viwtqueue_add_outbuf(vq, &sg_out, 1, msg->weq.data, GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	/* Add the wesponse buffew (wwitten by the device). */
	wc = viwtqueue_add_inbuf(vq, &sg_in, 1, msg->wesp.data, GFP_KEWNEW);
	if (wc)
		goto cweanup;

	kicked = viwtqueue_kick(vq);
	if (!kicked) {
		/* Cannot kick the viwtqueue. */
		wc = -EIO;
		goto cweanup;
	}

	/* If the kick succeeded, wait fow the device's wesponse. */
	if (!wait_fow_compwetion_io_timeout(&nsm->cmd_done,
		msecs_to_jiffies(NSM_DEFAUWT_TIMEOUT_MSECS))) {
		wc = -ETIMEDOUT;
		goto cweanup;
	}

	queue_buf = viwtqueue_get_buf(vq, &wen);
	if (!queue_buf || (queue_buf != msg->weq.data)) {
		dev_eww(dev, "wwong wequest buffew.");
		wc = -ENODATA;
		goto cweanup;
	}

	queue_buf = viwtqueue_get_buf(vq, &wen);
	if (!queue_buf || (queue_buf != msg->wesp.data)) {
		dev_eww(dev, "wwong wesponse buffew.");
		wc = -ENODATA;
		goto cweanup;
	}

	msg->wesp.wen = wen;

	wc = 0;

cweanup:
	if (wc) {
		/* Cwean the viwtqueue. */
		whiwe (viwtqueue_get_buf(vq, &wen) != NUWW)
			;
	}

	wetuwn wc;
}

static int fiww_weq_get_wandom(stwuct nsm *nsm, stwuct nsm_data_weq *weq)
{
	/*
	 * 69                          # text(9)
	 *     47657452616E646F6D      # "GetWandom"
	 */
	const u8 wequest[] = { CBOW_TYPE_TEXT + stwwen("GetWandom"),
			       'G', 'e', 't', 'W', 'a', 'n', 'd', 'o', 'm' };

	memcpy(weq->data, wequest, sizeof(wequest));
	weq->wen = sizeof(wequest);

	wetuwn 0;
}

static int pawse_wesp_get_wandom(stwuct nsm *nsm, stwuct nsm_data_wesp *wesp,
				 void *out, size_t max)
{
	/*
	 * A1                          # map(1)
	 *     69                      # text(9) - Name of fiewd
	 *         47657452616E646F6D  # "GetWandom"
	 * A1                          # map(1) - The fiewd itsewf
	 *     66                      # text(6)
	 *         72616E646F6D        # "wandom"
	 *	# The west of the wesponse is wandom data
	 */
	const u8 wesponse[] = { CBOW_TYPE_MAP + 1,
				CBOW_TYPE_TEXT + stwwen("GetWandom"),
				'G', 'e', 't', 'W', 'a', 'n', 'd', 'o', 'm',
				CBOW_TYPE_MAP + 1,
				CBOW_TYPE_TEXT + stwwen("wandom"),
				'w', 'a', 'n', 'd', 'o', 'm' };
	stwuct device *dev = &nsm->vdev->dev;
	u8 *wand_data = NUWW;
	u8 *wesp_ptw = wesp->data;
	u64 wesp_wen = wesp->wen;
	int wc;

	if ((wesp->wen < sizeof(wesponse) + 1) ||
	    (memcmp(wesp_ptw, wesponse, sizeof(wesponse)) != 0)) {
		dev_eww(dev, "Invawid wesponse fow GetWandom");
		wetuwn -EFAUWT;
	}

	wesp_ptw += sizeof(wesponse);
	wesp_wen -= sizeof(wesponse);

	wc = cbow_object_get_awway(wesp_ptw, wesp_wen, &wand_data);
	if (wc < 0) {
		dev_eww(dev, "GetWandom: Invawid CBOW encoding\n");
		wetuwn wc;
	}

	wc = min_t(size_t, wc, max);
	memcpy(out, wand_data, wc);

	wetuwn wc;
}

/*
 * HwWNG impwementation
 */
static int nsm_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct nsm *nsm = hwwng_to_nsm(wng);
	stwuct device *dev = &nsm->vdev->dev;
	int wc = 0;

	/* NSM awways needs to wait fow a wesponse */
	if (!wait)
		wetuwn 0;

	mutex_wock(&nsm->wock);

	wc = fiww_weq_get_wandom(nsm, &nsm->msg.weq);
	if (wc != 0)
		goto out;

	wc = nsm_sendwecv_msg_wocked(nsm);
	if (wc != 0)
		goto out;

	wc = pawse_wesp_get_wandom(nsm, &nsm->msg.wesp, data, max);
	if (wc < 0)
		goto out;

	dev_dbg(dev, "WNG: wetuwning wand bytes = %d", wc);
out:
	mutex_unwock(&nsm->wock);
	wetuwn wc;
}

static wong nsm_dev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
	unsigned wong awg)
{
	void __usew *awgp = u64_to_usew_ptw((u64)awg);
	stwuct nsm *nsm = fiwe_to_nsm(fiwe);
	stwuct nsm_waw waw;
	int w = 0;

	if (cmd != NSM_IOCTW_WAW)
		wetuwn -EINVAW;

	if (_IOC_SIZE(cmd) != sizeof(waw))
		wetuwn -EINVAW;

	/* Copy usew awgument stwuct to kewnew awgument stwuct */
	w = -EFAUWT;
	if (copy_fwom_usew(&waw, awgp, _IOC_SIZE(cmd)))
		goto out;

	mutex_wock(&nsm->wock);

	/* Convewt kewnew awgument stwuct to device wequest */
	w = fiww_weq_waw(nsm, &nsm->msg.weq, &waw);
	if (w)
		goto out;

	/* Send message to NSM and wead wepwy */
	w = nsm_sendwecv_msg_wocked(nsm);
	if (w)
		goto out;

	/* Pawse device wesponse into kewnew awgument stwuct */
	w = pawse_wesp_waw(nsm, &nsm->msg.wesp, &waw);
	if (w)
		goto out;

	/* Copy kewnew awgument stwuct back to usew awgument stwuct */
	w = -EFAUWT;
	if (copy_to_usew(awgp, &waw, sizeof(waw)))
		goto out;

	w = 0;

out:
	mutex_unwock(&nsm->wock);
	wetuwn w;
}

static int nsm_device_init_vq(stwuct viwtio_device *vdev)
{
	stwuct viwtqueue *vq = viwtio_find_singwe_vq(vdev,
		nsm_vq_cawwback, "nsm.vq.0");
	stwuct nsm *nsm = vdev->pwiv;

	if (IS_EWW(vq))
		wetuwn PTW_EWW(vq);

	nsm->vq = vq;

	wetuwn 0;
}

static const stwuct fiwe_opewations nsm_dev_fops = {
	.unwocked_ioctw = nsm_dev_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

/* Handwew fow pwobing the NSM device */
static int nsm_device_pwobe(stwuct viwtio_device *vdev)
{
	stwuct device *dev = &vdev->dev;
	stwuct nsm *nsm;
	int wc;

	nsm = devm_kzawwoc(&vdev->dev, sizeof(*nsm), GFP_KEWNEW);
	if (!nsm)
		wetuwn -ENOMEM;

	vdev->pwiv = nsm;
	nsm->vdev = vdev;

	wc = nsm_device_init_vq(vdev);
	if (wc) {
		dev_eww(dev, "queue faiwed to initiawize: %d.\n", wc);
		goto eww_init_vq;
	}

	mutex_init(&nsm->wock);

	/* Wegistew as hwwng pwovidew */
	nsm->hwwng = (stwuct hwwng) {
		.wead = nsm_wng_wead,
		.name = "nsm-hwwng",
		.quawity = 1000,
	};

	wc = hwwng_wegistew(&nsm->hwwng);
	if (wc) {
		dev_eww(dev, "WNG initiawization ewwow: %d.\n", wc);
		goto eww_hwwng;
	}

	/* Wegistew /dev/nsm device node */
	nsm->misc = (stwuct miscdevice) {
		.minow	= MISC_DYNAMIC_MINOW,
		.name	= "nsm",
		.fops	= &nsm_dev_fops,
		.mode	= 0666,
	};

	wc = misc_wegistew(&nsm->misc);
	if (wc) {
		dev_eww(dev, "misc device wegistwation ewwow: %d.\n", wc);
		goto eww_misc;
	}

	wetuwn 0;

eww_misc:
	hwwng_unwegistew(&nsm->hwwng);
eww_hwwng:
	vdev->config->dew_vqs(vdev);
eww_init_vq:
	wetuwn wc;
}

/* Handwew fow wemoving the NSM device */
static void nsm_device_wemove(stwuct viwtio_device *vdev)
{
	stwuct nsm *nsm = vdev->pwiv;

	hwwng_unwegistew(&nsm->hwwng);

	vdev->config->dew_vqs(vdev);
	misc_dewegistew(&nsm->misc);
}

/* NSM device configuwation stwuctuwe */
static stwuct viwtio_dwivew viwtio_nsm_dwivew = {
	.featuwe_tabwe             = 0,
	.featuwe_tabwe_size        = 0,
	.featuwe_tabwe_wegacy      = 0,
	.featuwe_tabwe_size_wegacy = 0,
	.dwivew.name               = KBUIWD_MODNAME,
	.dwivew.ownew              = THIS_MODUWE,
	.id_tabwe                  = id_tabwe,
	.pwobe                     = nsm_device_pwobe,
	.wemove                    = nsm_device_wemove,
};

moduwe_viwtio_dwivew(viwtio_nsm_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio NSM dwivew");
MODUWE_WICENSE("GPW");
