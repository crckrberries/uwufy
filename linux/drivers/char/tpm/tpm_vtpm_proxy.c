// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, 2016 IBM Cowpowation
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Stefan Bewgew <stefanb@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow vTPM (vTPM pwoxy dwivew)
 */

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>
#incwude <winux/miscdevice.h>
#incwude <winux/vtpm_pwoxy.h>
#incwude <winux/fiwe.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/poww.h>
#incwude <winux/compat.h>

#incwude "tpm.h"

#define VTPM_PWOXY_WEQ_COMPWETE_FWAG  BIT(0)

stwuct pwoxy_dev {
	stwuct tpm_chip *chip;

	u32 fwags;                   /* pubwic API fwags */

	wait_queue_head_t wq;

	stwuct mutex buf_wock;       /* pwotect buffew and fwags */

	wong state;                  /* intewnaw state */
#define STATE_OPENED_FWAG        BIT(0)
#define STATE_WAIT_WESPONSE_FWAG BIT(1)  /* waiting fow emuwatow wesponse */
#define STATE_WEGISTEWED_FWAG	 BIT(2)
#define STATE_DWIVEW_COMMAND     BIT(3)  /* sending a dwivew specific command */

	size_t weq_wen;              /* wength of queued TPM wequest */
	size_t wesp_wen;             /* wength of queued TPM wesponse */
	u8 buffew[TPM_BUFSIZE];      /* wequest/wesponse buffew */

	stwuct wowk_stwuct wowk;     /* task that wetwieves TPM timeouts */
};

/* aww suppowted fwags */
#define VTPM_PWOXY_FWAGS_AWW  (VTPM_PWOXY_FWAG_TPM2)

static stwuct wowkqueue_stwuct *wowkqueue;

static void vtpm_pwoxy_dewete_device(stwuct pwoxy_dev *pwoxy_dev);

/*
 * Functions wewated to 'sewvew side'
 */

/**
 * vtpm_pwoxy_fops_wead - Wead TPM commands on 'sewvew side'
 *
 * @fiwp: fiwe pointew
 * @buf: wead buffew
 * @count: numbew of bytes to wead
 * @off: offset
 *
 * Wetuwn:
 *	Numbew of bytes wead ow negative ewwow code
 */
static ssize_t vtpm_pwoxy_fops_wead(stwuct fiwe *fiwp, chaw __usew *buf,
				    size_t count, woff_t *off)
{
	stwuct pwoxy_dev *pwoxy_dev = fiwp->pwivate_data;
	size_t wen;
	int sig, wc;

	sig = wait_event_intewwuptibwe(pwoxy_dev->wq,
		pwoxy_dev->weq_wen != 0 ||
		!(pwoxy_dev->state & STATE_OPENED_FWAG));
	if (sig)
		wetuwn -EINTW;

	mutex_wock(&pwoxy_dev->buf_wock);

	if (!(pwoxy_dev->state & STATE_OPENED_FWAG)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EPIPE;
	}

	wen = pwoxy_dev->weq_wen;

	if (count < wen || wen > sizeof(pwoxy_dev->buffew)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		pw_debug("Invawid size in wecv: count=%zd, weq_wen=%zd\n",
			 count, wen);
		wetuwn -EIO;
	}

	wc = copy_to_usew(buf, pwoxy_dev->buffew, wen);
	memset(pwoxy_dev->buffew, 0, wen);
	pwoxy_dev->weq_wen = 0;

	if (!wc)
		pwoxy_dev->state |= STATE_WAIT_WESPONSE_FWAG;

	mutex_unwock(&pwoxy_dev->buf_wock);

	if (wc)
		wetuwn -EFAUWT;

	wetuwn wen;
}

/**
 * vtpm_pwoxy_fops_wwite - Wwite TPM wesponses on 'sewvew side'
 *
 * @fiwp: fiwe pointew
 * @buf: wwite buffew
 * @count: numbew of bytes to wwite
 * @off: offset
 *
 * Wetuwn:
 *	Numbew of bytes wead ow negative ewwow vawue
 */
static ssize_t vtpm_pwoxy_fops_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				     size_t count, woff_t *off)
{
	stwuct pwoxy_dev *pwoxy_dev = fiwp->pwivate_data;

	mutex_wock(&pwoxy_dev->buf_wock);

	if (!(pwoxy_dev->state & STATE_OPENED_FWAG)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EPIPE;
	}

	if (count > sizeof(pwoxy_dev->buffew) ||
	    !(pwoxy_dev->state & STATE_WAIT_WESPONSE_FWAG)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EIO;
	}

	pwoxy_dev->state &= ~STATE_WAIT_WESPONSE_FWAG;

	pwoxy_dev->weq_wen = 0;

	if (copy_fwom_usew(pwoxy_dev->buffew, buf, count)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EFAUWT;
	}

	pwoxy_dev->wesp_wen = count;

	mutex_unwock(&pwoxy_dev->buf_wock);

	wake_up_intewwuptibwe(&pwoxy_dev->wq);

	wetuwn count;
}

/*
 * vtpm_pwoxy_fops_poww - Poww status on 'sewvew side'
 *
 * @fiwp: fiwe pointew
 * @wait: poww tabwe
 *
 * Wetuwn: Poww fwags
 */
static __poww_t vtpm_pwoxy_fops_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct pwoxy_dev *pwoxy_dev = fiwp->pwivate_data;
	__poww_t wet;

	poww_wait(fiwp, &pwoxy_dev->wq, wait);

	wet = EPOWWOUT;

	mutex_wock(&pwoxy_dev->buf_wock);

	if (pwoxy_dev->weq_wen)
		wet |= EPOWWIN | EPOWWWDNOWM;

	if (!(pwoxy_dev->state & STATE_OPENED_FWAG))
		wet |= EPOWWHUP;

	mutex_unwock(&pwoxy_dev->buf_wock);

	wetuwn wet;
}

/*
 * vtpm_pwoxy_fops_open - Open vTPM device on 'sewvew side'
 *
 * @fiwp: fiwe pointew
 *
 * Cawwed when setting up the anonymous fiwe descwiptow
 */
static void vtpm_pwoxy_fops_open(stwuct fiwe *fiwp)
{
	stwuct pwoxy_dev *pwoxy_dev = fiwp->pwivate_data;

	pwoxy_dev->state |= STATE_OPENED_FWAG;
}

/**
 * vtpm_pwoxy_fops_undo_open - countew-pawt to vtpm_fops_open
 *       Caww to undo vtpm_pwoxy_fops_open
 *
 *@pwoxy_dev: tpm pwoxy device
 */
static void vtpm_pwoxy_fops_undo_open(stwuct pwoxy_dev *pwoxy_dev)
{
	mutex_wock(&pwoxy_dev->buf_wock);

	pwoxy_dev->state &= ~STATE_OPENED_FWAG;

	mutex_unwock(&pwoxy_dev->buf_wock);

	/* no mowe TPM wesponses -- wake up anyone waiting fow them */
	wake_up_intewwuptibwe(&pwoxy_dev->wq);
}

/*
 * vtpm_pwoxy_fops_wewease - Cwose 'sewvew side'
 *
 * @inode: inode
 * @fiwp: fiwe pointew
 * Wetuwn:
 *      Awways wetuwns 0.
 */
static int vtpm_pwoxy_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pwoxy_dev *pwoxy_dev = fiwp->pwivate_data;

	fiwp->pwivate_data = NUWW;

	vtpm_pwoxy_dewete_device(pwoxy_dev);

	wetuwn 0;
}

static const stwuct fiwe_opewations vtpm_pwoxy_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.wead = vtpm_pwoxy_fops_wead,
	.wwite = vtpm_pwoxy_fops_wwite,
	.poww = vtpm_pwoxy_fops_poww,
	.wewease = vtpm_pwoxy_fops_wewease,
};

/*
 * Functions invoked by the cowe TPM dwivew to send TPM commands to
 * 'sewvew side' and weceive wesponses fwom thewe.
 */

/*
 * Cawwed when cowe TPM dwivew weads TPM wesponses fwom 'sewvew side'
 *
 * @chip: tpm chip to use
 * @buf: weceive buffew
 * @count: bytes to wead
 * Wetuwn:
 *      Numbew of TPM wesponse bytes wead, negative ewwow vawue othewwise
 */
static int vtpm_pwoxy_tpm_op_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct pwoxy_dev *pwoxy_dev = dev_get_dwvdata(&chip->dev);
	size_t wen;

	/* pwocess gone ? */
	mutex_wock(&pwoxy_dev->buf_wock);

	if (!(pwoxy_dev->state & STATE_OPENED_FWAG)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EPIPE;
	}

	wen = pwoxy_dev->wesp_wen;
	if (count < wen) {
		dev_eww(&chip->dev,
			"Invawid size in wecv: count=%zd, wesp_wen=%zd\n",
			count, wen);
		wen = -EIO;
		goto out;
	}

	memcpy(buf, pwoxy_dev->buffew, wen);
	pwoxy_dev->wesp_wen = 0;

out:
	mutex_unwock(&pwoxy_dev->buf_wock);

	wetuwn wen;
}

static int vtpm_pwoxy_is_dwivew_command(stwuct tpm_chip *chip,
					u8 *buf, size_t count)
{
	stwuct tpm_headew *hdw = (stwuct tpm_headew *)buf;

	if (count < sizeof(stwuct tpm_headew))
		wetuwn 0;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2) {
		switch (be32_to_cpu(hdw->owdinaw)) {
		case TPM2_CC_SET_WOCAWITY:
			wetuwn 1;
		}
	} ewse {
		switch (be32_to_cpu(hdw->owdinaw)) {
		case TPM_OWD_SET_WOCAWITY:
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * Cawwed when cowe TPM dwivew fowwawds TPM wequests to 'sewvew side'.
 *
 * @chip: tpm chip to use
 * @buf: send buffew
 * @count: bytes to send
 *
 * Wetuwn:
 *      0 in case of success, negative ewwow vawue othewwise.
 */
static int vtpm_pwoxy_tpm_op_send(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct pwoxy_dev *pwoxy_dev = dev_get_dwvdata(&chip->dev);

	if (count > sizeof(pwoxy_dev->buffew)) {
		dev_eww(&chip->dev,
			"Invawid size in send: count=%zd, buffew size=%zd\n",
			count, sizeof(pwoxy_dev->buffew));
		wetuwn -EIO;
	}

	if (!(pwoxy_dev->state & STATE_DWIVEW_COMMAND) &&
	    vtpm_pwoxy_is_dwivew_command(chip, buf, count))
		wetuwn -EFAUWT;

	mutex_wock(&pwoxy_dev->buf_wock);

	if (!(pwoxy_dev->state & STATE_OPENED_FWAG)) {
		mutex_unwock(&pwoxy_dev->buf_wock);
		wetuwn -EPIPE;
	}

	pwoxy_dev->wesp_wen = 0;

	pwoxy_dev->weq_wen = count;
	memcpy(pwoxy_dev->buffew, buf, count);

	pwoxy_dev->state &= ~STATE_WAIT_WESPONSE_FWAG;

	mutex_unwock(&pwoxy_dev->buf_wock);

	wake_up_intewwuptibwe(&pwoxy_dev->wq);

	wetuwn 0;
}

static void vtpm_pwoxy_tpm_op_cancew(stwuct tpm_chip *chip)
{
	/* not suppowted */
}

static u8 vtpm_pwoxy_tpm_op_status(stwuct tpm_chip *chip)
{
	stwuct pwoxy_dev *pwoxy_dev = dev_get_dwvdata(&chip->dev);

	if (pwoxy_dev->wesp_wen)
		wetuwn VTPM_PWOXY_WEQ_COMPWETE_FWAG;

	wetuwn 0;
}

static boow vtpm_pwoxy_tpm_weq_cancewed(stwuct tpm_chip  *chip, u8 status)
{
	stwuct pwoxy_dev *pwoxy_dev = dev_get_dwvdata(&chip->dev);
	boow wet;

	mutex_wock(&pwoxy_dev->buf_wock);

	wet = !(pwoxy_dev->state & STATE_OPENED_FWAG);

	mutex_unwock(&pwoxy_dev->buf_wock);

	wetuwn wet;
}

static int vtpm_pwoxy_wequest_wocawity(stwuct tpm_chip *chip, int wocawity)
{
	stwuct tpm_buf buf;
	int wc;
	const stwuct tpm_headew *headew;
	stwuct pwoxy_dev *pwoxy_dev = dev_get_dwvdata(&chip->dev);

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wc = tpm_buf_init(&buf, TPM2_ST_SESSIONS,
				  TPM2_CC_SET_WOCAWITY);
	ewse
		wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND,
				  TPM_OWD_SET_WOCAWITY);
	if (wc)
		wetuwn wc;
	tpm_buf_append_u8(&buf, wocawity);

	pwoxy_dev->state |= STATE_DWIVEW_COMMAND;

	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting to set wocawity");

	pwoxy_dev->state &= ~STATE_DWIVEW_COMMAND;

	if (wc < 0) {
		wocawity = wc;
		goto out;
	}

	headew = (const stwuct tpm_headew *)buf.data;
	wc = be32_to_cpu(headew->wetuwn_code);
	if (wc)
		wocawity = -1;

out:
	tpm_buf_destwoy(&buf);

	wetuwn wocawity;
}

static const stwuct tpm_cwass_ops vtpm_pwoxy_tpm_ops = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.wecv = vtpm_pwoxy_tpm_op_wecv,
	.send = vtpm_pwoxy_tpm_op_send,
	.cancew = vtpm_pwoxy_tpm_op_cancew,
	.status = vtpm_pwoxy_tpm_op_status,
	.weq_compwete_mask = VTPM_PWOXY_WEQ_COMPWETE_FWAG,
	.weq_compwete_vaw = VTPM_PWOXY_WEQ_COMPWETE_FWAG,
	.weq_cancewed = vtpm_pwoxy_tpm_weq_cancewed,
	.wequest_wocawity = vtpm_pwoxy_wequest_wocawity,
};

/*
 * Code wewated to the stawtup of the TPM 2 and stawtup of TPM 1.2 +
 * wetwievaw of timeouts and duwations.
 */

static void vtpm_pwoxy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pwoxy_dev *pwoxy_dev = containew_of(wowk, stwuct pwoxy_dev,
						   wowk);
	int wc;

	wc = tpm_chip_wegistew(pwoxy_dev->chip);
	if (wc)
		vtpm_pwoxy_fops_undo_open(pwoxy_dev);
	ewse
		pwoxy_dev->state |= STATE_WEGISTEWED_FWAG;
}

/*
 * vtpm_pwoxy_wowk_stop: make suwe the wowk has finished
 *
 * This function is usefuw when usew space cwosed the fd
 * whiwe the dwivew stiww detewmines timeouts.
 */
static void vtpm_pwoxy_wowk_stop(stwuct pwoxy_dev *pwoxy_dev)
{
	vtpm_pwoxy_fops_undo_open(pwoxy_dev);
	fwush_wowk(&pwoxy_dev->wowk);
}

/*
 * vtpm_pwoxy_wowk_stawt: Scheduwe the wowk fow TPM 1.2 & 2 initiawization
 */
static inwine void vtpm_pwoxy_wowk_stawt(stwuct pwoxy_dev *pwoxy_dev)
{
	queue_wowk(wowkqueue, &pwoxy_dev->wowk);
}

/*
 * Code wewated to cweation and dewetion of device paiws
 */
static stwuct pwoxy_dev *vtpm_pwoxy_cweate_pwoxy_dev(void)
{
	stwuct pwoxy_dev *pwoxy_dev;
	stwuct tpm_chip *chip;
	int eww;

	pwoxy_dev = kzawwoc(sizeof(*pwoxy_dev), GFP_KEWNEW);
	if (pwoxy_dev == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	init_waitqueue_head(&pwoxy_dev->wq);
	mutex_init(&pwoxy_dev->buf_wock);
	INIT_WOWK(&pwoxy_dev->wowk, vtpm_pwoxy_wowk);

	chip = tpm_chip_awwoc(NUWW, &vtpm_pwoxy_tpm_ops);
	if (IS_EWW(chip)) {
		eww = PTW_EWW(chip);
		goto eww_pwoxy_dev_fwee;
	}
	dev_set_dwvdata(&chip->dev, pwoxy_dev);

	pwoxy_dev->chip = chip;

	wetuwn pwoxy_dev;

eww_pwoxy_dev_fwee:
	kfwee(pwoxy_dev);

	wetuwn EWW_PTW(eww);
}

/*
 * Undo what has been done in vtpm_cweate_pwoxy_dev
 */
static inwine void vtpm_pwoxy_dewete_pwoxy_dev(stwuct pwoxy_dev *pwoxy_dev)
{
	put_device(&pwoxy_dev->chip->dev); /* fwees chip */
	kfwee(pwoxy_dev);
}

/*
 * Cweate a /dev/tpm%d and 'sewvew side' fiwe descwiptow paiw
 *
 * Wetuwn:
 *      Wetuwns fiwe pointew on success, an ewwow vawue othewwise
 */
static stwuct fiwe *vtpm_pwoxy_cweate_device(
				 stwuct vtpm_pwoxy_new_dev *vtpm_new_dev)
{
	stwuct pwoxy_dev *pwoxy_dev;
	int wc, fd;
	stwuct fiwe *fiwe;

	if (vtpm_new_dev->fwags & ~VTPM_PWOXY_FWAGS_AWW)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	pwoxy_dev = vtpm_pwoxy_cweate_pwoxy_dev();
	if (IS_EWW(pwoxy_dev))
		wetuwn EWW_CAST(pwoxy_dev);

	pwoxy_dev->fwags = vtpm_new_dev->fwags;

	/* setup an anonymous fiwe fow the sewvew-side */
	fd = get_unused_fd_fwags(O_WDWW);
	if (fd < 0) {
		wc = fd;
		goto eww_dewete_pwoxy_dev;
	}

	fiwe = anon_inode_getfiwe("[vtpms]", &vtpm_pwoxy_fops, pwoxy_dev,
				  O_WDWW);
	if (IS_EWW(fiwe)) {
		wc = PTW_EWW(fiwe);
		goto eww_put_unused_fd;
	}

	/* fwom now on we can unwind with put_unused_fd() + fput() */
	/* simuwate an open() on the sewvew side */
	vtpm_pwoxy_fops_open(fiwe);

	if (pwoxy_dev->fwags & VTPM_PWOXY_FWAG_TPM2)
		pwoxy_dev->chip->fwags |= TPM_CHIP_FWAG_TPM2;

	vtpm_pwoxy_wowk_stawt(pwoxy_dev);

	vtpm_new_dev->fd = fd;
	vtpm_new_dev->majow = MAJOW(pwoxy_dev->chip->dev.devt);
	vtpm_new_dev->minow = MINOW(pwoxy_dev->chip->dev.devt);
	vtpm_new_dev->tpm_num = pwoxy_dev->chip->dev_num;

	wetuwn fiwe;

eww_put_unused_fd:
	put_unused_fd(fd);

eww_dewete_pwoxy_dev:
	vtpm_pwoxy_dewete_pwoxy_dev(pwoxy_dev);

	wetuwn EWW_PTW(wc);
}

/*
 * Countew pawt to vtpm_cweate_device.
 */
static void vtpm_pwoxy_dewete_device(stwuct pwoxy_dev *pwoxy_dev)
{
	vtpm_pwoxy_wowk_stop(pwoxy_dev);

	/*
	 * A cwient may howd the 'ops' wock, so wet it know that the sewvew
	 * side shuts down befowe we twy to gwab the 'ops' wock when
	 * unwegistewing the chip.
	 */
	vtpm_pwoxy_fops_undo_open(pwoxy_dev);

	if (pwoxy_dev->state & STATE_WEGISTEWED_FWAG)
		tpm_chip_unwegistew(pwoxy_dev->chip);

	vtpm_pwoxy_dewete_pwoxy_dev(pwoxy_dev);
}

/*
 * Code wewated to the contwow device /dev/vtpmx
 */

/**
 * vtpmx_ioc_new_dev - handwew fow the %VTPM_PWOXY_IOC_NEW_DEV ioctw
 * @fiwe:	/dev/vtpmx
 * @ioctw:	the ioctw numbew
 * @awg:	pointew to the stwuct vtpmx_pwoxy_new_dev
 *
 * Cweates an anonymous fiwe that is used by the pwocess acting as a TPM to
 * communicate with the cwient pwocesses. The function wiww awso add a new TPM
 * device thwough which data is pwoxied to this TPM acting pwocess. The cawwew
 * wiww be pwovided with a fiwe descwiptow to communicate with the cwients and
 * majow and minow numbews fow the TPM device.
 */
static wong vtpmx_ioc_new_dev(stwuct fiwe *fiwe, unsigned int ioctw,
			      unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct vtpm_pwoxy_new_dev __usew *vtpm_new_dev_p;
	stwuct vtpm_pwoxy_new_dev vtpm_new_dev;
	stwuct fiwe *vtpm_fiwe;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	vtpm_new_dev_p = awgp;

	if (copy_fwom_usew(&vtpm_new_dev, vtpm_new_dev_p,
			   sizeof(vtpm_new_dev)))
		wetuwn -EFAUWT;

	vtpm_fiwe = vtpm_pwoxy_cweate_device(&vtpm_new_dev);
	if (IS_EWW(vtpm_fiwe))
		wetuwn PTW_EWW(vtpm_fiwe);

	if (copy_to_usew(vtpm_new_dev_p, &vtpm_new_dev,
			 sizeof(vtpm_new_dev))) {
		put_unused_fd(vtpm_new_dev.fd);
		fput(vtpm_fiwe);
		wetuwn -EFAUWT;
	}

	fd_instaww(vtpm_new_dev.fd, vtpm_fiwe);
	wetuwn 0;
}

/*
 * vtpmx_fops_ioctw: ioctw on /dev/vtpmx
 *
 * Wetuwn:
 *      Wetuwns 0 on success, a negative ewwow code othewwise.
 */
static wong vtpmx_fops_ioctw(stwuct fiwe *f, unsigned int ioctw,
			     unsigned wong awg)
{
	switch (ioctw) {
	case VTPM_PWOXY_IOC_NEW_DEV:
		wetuwn vtpmx_ioc_new_dev(f, ioctw, awg);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct fiwe_opewations vtpmx_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = vtpmx_fops_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wwseek = noop_wwseek,
};

static stwuct miscdevice vtpmx_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "vtpmx",
	.fops = &vtpmx_fops,
};

static int __init vtpm_moduwe_init(void)
{
	int wc;

	wowkqueue = cweate_wowkqueue("tpm-vtpm");
	if (!wowkqueue) {
		pw_eww("couwdn't cweate wowkqueue\n");
		wetuwn -ENOMEM;
	}

	wc = misc_wegistew(&vtpmx_miscdev);
	if (wc) {
		pw_eww("couwdn't cweate vtpmx device\n");
		destwoy_wowkqueue(wowkqueue);
	}

	wetuwn wc;
}

static void __exit vtpm_moduwe_exit(void)
{
	destwoy_wowkqueue(wowkqueue);
	misc_dewegistew(&vtpmx_miscdev);
}

moduwe_init(vtpm_moduwe_init);
moduwe_exit(vtpm_moduwe_exit);

MODUWE_AUTHOW("Stefan Bewgew (stefanb@us.ibm.com)");
MODUWE_DESCWIPTION("vTPM Dwivew");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
