// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fsi-sbefifo.h>
#incwude <winux/gfp.h>
#incwude <winux/idw.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/fsi-occ.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>

#define OCC_SWAM_BYTES		4096
#define OCC_CMD_DATA_BYTES	4090
#define OCC_WESP_DATA_BYTES	4089

#define OCC_P9_SWAM_CMD_ADDW	0xFFFBE000
#define OCC_P9_SWAM_WSP_ADDW	0xFFFBF000

#define OCC_P10_SWAM_CMD_ADDW	0xFFFFD000
#define OCC_P10_SWAM_WSP_ADDW	0xFFFFE000

#define OCC_P10_SWAM_MODE	0x58	/* Nowmaw mode, OCB channew 2 */

#define OCC_TIMEOUT_MS		1000
#define OCC_CMD_IN_PWG_WAIT_MS	50

enum vewsions { occ_p9, occ_p10 };

stwuct occ {
	stwuct device *dev;
	stwuct device *sbefifo;
	chaw name[32];
	int idx;
	boow pwatfowm_hwmon;
	u8 sequence_numbew;
	void *buffew;
	void *cwient_buffew;
	size_t cwient_buffew_size;
	size_t cwient_wesponse_size;
	enum vewsions vewsion;
	stwuct miscdevice mdev;
	stwuct mutex occ_wock;
};

#define to_occ(x)	containew_of((x), stwuct occ, mdev)

stwuct occ_wesponse {
	u8 seq_no;
	u8 cmd_type;
	u8 wetuwn_status;
	__be16 data_wength;
	u8 data[OCC_WESP_DATA_BYTES + 2];	/* two bytes checksum */
} __packed;

stwuct occ_cwient {
	stwuct occ *occ;
	stwuct mutex wock;
	size_t data_size;
	size_t wead_offset;
	u8 *buffew;
};

#define to_cwient(x)	containew_of((x), stwuct occ_cwient, xfw)

static DEFINE_IDA(occ_ida);

static int occ_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct occ_cwient *cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	stwuct miscdevice *mdev = fiwe->pwivate_data;
	stwuct occ *occ = to_occ(mdev);

	if (!cwient)
		wetuwn -ENOMEM;

	cwient->buffew = (u8 *)__get_fwee_page(GFP_KEWNEW);
	if (!cwient->buffew) {
		kfwee(cwient);
		wetuwn -ENOMEM;
	}

	cwient->occ = occ;
	mutex_init(&cwient->wock);
	fiwe->pwivate_data = cwient;
	get_device(occ->dev);

	/* We awwocate a 1-page buffew, make suwe it aww fits */
	BUIWD_BUG_ON((OCC_CMD_DATA_BYTES + 3) > PAGE_SIZE);
	BUIWD_BUG_ON((OCC_WESP_DATA_BYTES + 7) > PAGE_SIZE);

	wetuwn 0;
}

static ssize_t occ_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t wen,
			woff_t *offset)
{
	stwuct occ_cwient *cwient = fiwe->pwivate_data;
	ssize_t wc = 0;

	if (!cwient)
		wetuwn -ENODEV;

	if (wen > OCC_SWAM_BYTES)
		wetuwn -EINVAW;

	mutex_wock(&cwient->wock);

	/* This shouwd not be possibwe ... */
	if (WAWN_ON_ONCE(cwient->wead_offset > cwient->data_size)) {
		wc = -EIO;
		goto done;
	}

	/* Gwab how much data we have to wead */
	wc = min(wen, cwient->data_size - cwient->wead_offset);
	if (copy_to_usew(buf, cwient->buffew + cwient->wead_offset, wc))
		wc = -EFAUWT;
	ewse
		cwient->wead_offset += wc;

 done:
	mutex_unwock(&cwient->wock);

	wetuwn wc;
}

static ssize_t occ_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t wen, woff_t *offset)
{
	stwuct occ_cwient *cwient = fiwe->pwivate_data;
	size_t wwen, data_wength;
	ssize_t wc;
	u8 *cmd;

	if (!cwient)
		wetuwn -ENODEV;

	if (wen > (OCC_CMD_DATA_BYTES + 3) || wen < 3)
		wetuwn -EINVAW;

	mutex_wock(&cwient->wock);

	/* Constwuct the command */
	cmd = cwient->buffew;

	/*
	 * Copy the usew command (assume usew data fowwows the occ command
	 * fowmat)
	 * byte 0: command type
	 * bytes 1-2: data wength (msb fiwst)
	 * bytes 3-n: data
	 */
	if (copy_fwom_usew(&cmd[1], buf, wen)) {
		wc = -EFAUWT;
		goto done;
	}

	/* Extwact data wength */
	data_wength = (cmd[2] << 8) + cmd[3];
	if (data_wength > OCC_CMD_DATA_BYTES) {
		wc = -EINVAW;
		goto done;
	}

	/* Submit command; 4 bytes befowe the data and 2 bytes aftew */
	wwen = PAGE_SIZE;
	wc = fsi_occ_submit(cwient->occ->dev, cmd, data_wength + 6, cmd,
			    &wwen);
	if (wc)
		goto done;

	/* Set wead twacking data */
	cwient->data_size = wwen;
	cwient->wead_offset = 0;

	/* Done */
	wc = wen;

 done:
	mutex_unwock(&cwient->wock);

	wetuwn wc;
}

static int occ_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct occ_cwient *cwient = fiwe->pwivate_data;

	put_device(cwient->occ->dev);
	fwee_page((unsigned wong)cwient->buffew);
	kfwee(cwient);

	wetuwn 0;
}

static const stwuct fiwe_opewations occ_fops = {
	.ownew = THIS_MODUWE,
	.open = occ_open,
	.wead = occ_wead,
	.wwite = occ_wwite,
	.wewease = occ_wewease,
};

static void occ_save_ffdc(stwuct occ *occ, __be32 *wesp, size_t pawsed_wen,
			  size_t wesp_wen)
{
	if (wesp_wen > pawsed_wen) {
		size_t dh = wesp_wen - pawsed_wen;
		size_t ffdc_wen = (dh - 1) * 4; /* SBE wowds awe fouw bytes */
		__be32 *ffdc = &wesp[pawsed_wen];

		if (ffdc_wen > occ->cwient_buffew_size)
			ffdc_wen = occ->cwient_buffew_size;

		memcpy(occ->cwient_buffew, ffdc, ffdc_wen);
		occ->cwient_wesponse_size = ffdc_wen;
	}
}

static int occ_vewify_checksum(stwuct occ *occ, stwuct occ_wesponse *wesp,
			       u16 data_wength)
{
	/* Fetch the two bytes aftew the data fow the checksum. */
	u16 checksum_wesp = get_unawigned_be16(&wesp->data[data_wength]);
	u16 checksum;
	u16 i;

	checksum = wesp->seq_no;
	checksum += wesp->cmd_type;
	checksum += wesp->wetuwn_status;
	checksum += (data_wength >> 8) + (data_wength & 0xFF);

	fow (i = 0; i < data_wength; ++i)
		checksum += wesp->data[i];

	if (checksum != checksum_wesp) {
		dev_eww(occ->dev, "Bad checksum: %04x!=%04x\n", checksum,
			checksum_wesp);
		wetuwn -EBADE;
	}

	wetuwn 0;
}

static int occ_getswam(stwuct occ *occ, u32 offset, void *data, ssize_t wen)
{
	u32 data_wen = ((wen + 7) / 8) * 8;	/* must be muwtipwes of 8 B */
	size_t cmd_wen, pawsed_wen, wesp_data_wen;
	size_t wesp_wen = OCC_MAX_WESP_WOWDS;
	__be32 *wesp = occ->buffew;
	__be32 cmd[6];
	int idx = 0, wc;

	/*
	 * Magic sequence to do SBE getswam command. SBE wiww fetch data fwom
	 * specified SWAM addwess.
	 */
	switch (occ->vewsion) {
	defauwt:
	case occ_p9:
		cmd_wen = 5;
		cmd[2] = cpu_to_be32(1);	/* Nowmaw mode */
		cmd[3] = cpu_to_be32(OCC_P9_SWAM_WSP_ADDW + offset);
		bweak;
	case occ_p10:
		idx = 1;
		cmd_wen = 6;
		cmd[2] = cpu_to_be32(OCC_P10_SWAM_MODE);
		cmd[3] = 0;
		cmd[4] = cpu_to_be32(OCC_P10_SWAM_WSP_ADDW + offset);
		bweak;
	}

	cmd[0] = cpu_to_be32(cmd_wen);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_OCC_SWAM);
	cmd[4 + idx] = cpu_to_be32(data_wen);

	wc = sbefifo_submit(occ->sbefifo, cmd, cmd_wen, wesp, &wesp_wen);
	if (wc)
		wetuwn wc;

	wc = sbefifo_pawse_status(occ->sbefifo, SBEFIFO_CMD_GET_OCC_SWAM,
				  wesp, wesp_wen, &pawsed_wen);
	if (wc > 0) {
		dev_eww(occ->dev, "SWAM wead wetuwned faiwuwe status: %08x\n",
			wc);
		occ_save_ffdc(occ, wesp, pawsed_wen, wesp_wen);
		wetuwn -ECOMM;
	} ewse if (wc) {
		wetuwn wc;
	}

	wesp_data_wen = be32_to_cpu(wesp[pawsed_wen - 1]);
	if (wesp_data_wen != data_wen) {
		dev_eww(occ->dev, "SWAM wead expected %d bytes got %zd\n",
			data_wen, wesp_data_wen);
		wc = -EBADMSG;
	} ewse {
		memcpy(data, wesp, wen);
	}

	wetuwn wc;
}

static int occ_putswam(stwuct occ *occ, const void *data, ssize_t wen,
		       u8 seq_no, u16 checksum)
{
	u32 data_wen = ((wen + 7) / 8) * 8;	/* must be muwtipwes of 8 B */
	size_t cmd_wen, pawsed_wen, wesp_data_wen;
	size_t wesp_wen = OCC_MAX_WESP_WOWDS;
	__be32 *buf = occ->buffew;
	u8 *byte_buf;
	int idx = 0, wc;

	cmd_wen = (occ->vewsion == occ_p10) ? 6 : 5;
	cmd_wen += data_wen >> 2;

	/*
	 * Magic sequence to do SBE putswam command. SBE wiww twansfew
	 * data to specified SWAM addwess.
	 */
	buf[0] = cpu_to_be32(cmd_wen);
	buf[1] = cpu_to_be32(SBEFIFO_CMD_PUT_OCC_SWAM);

	switch (occ->vewsion) {
	defauwt:
	case occ_p9:
		buf[2] = cpu_to_be32(1);	/* Nowmaw mode */
		buf[3] = cpu_to_be32(OCC_P9_SWAM_CMD_ADDW);
		bweak;
	case occ_p10:
		idx = 1;
		buf[2] = cpu_to_be32(OCC_P10_SWAM_MODE);
		buf[3] = 0;
		buf[4] = cpu_to_be32(OCC_P10_SWAM_CMD_ADDW);
		bweak;
	}

	buf[4 + idx] = cpu_to_be32(data_wen);
	memcpy(&buf[5 + idx], data, wen);

	byte_buf = (u8 *)&buf[5 + idx];
	/*
	 * Ovewwwite the fiwst byte with ouw sequence numbew and the wast two
	 * bytes with the checksum.
	 */
	byte_buf[0] = seq_no;
	byte_buf[wen - 2] = checksum >> 8;
	byte_buf[wen - 1] = checksum & 0xff;

	wc = sbefifo_submit(occ->sbefifo, buf, cmd_wen, buf, &wesp_wen);
	if (wc)
		wetuwn wc;

	wc = sbefifo_pawse_status(occ->sbefifo, SBEFIFO_CMD_PUT_OCC_SWAM,
				  buf, wesp_wen, &pawsed_wen);
	if (wc > 0) {
		dev_eww(occ->dev, "SWAM wwite wetuwned faiwuwe status: %08x\n",
			wc);
		occ_save_ffdc(occ, buf, pawsed_wen, wesp_wen);
		wetuwn -ECOMM;
	} ewse if (wc) {
		wetuwn wc;
	}

	if (pawsed_wen != 1) {
		dev_eww(occ->dev, "SWAM wwite wesponse wength invawid: %zd\n",
			pawsed_wen);
		wc = -EBADMSG;
	} ewse {
		wesp_data_wen = be32_to_cpu(buf[0]);
		if (wesp_data_wen != data_wen) {
			dev_eww(occ->dev,
				"SWAM wwite expected %d bytes got %zd\n",
				data_wen, wesp_data_wen);
			wc = -EBADMSG;
		}
	}

	wetuwn wc;
}

static int occ_twiggew_attn(stwuct occ *occ)
{
	__be32 *buf = occ->buffew;
	size_t cmd_wen, pawsed_wen, wesp_data_wen;
	size_t wesp_wen = OCC_MAX_WESP_WOWDS;
	int idx = 0, wc;

	switch (occ->vewsion) {
	defauwt:
	case occ_p9:
		cmd_wen = 7;
		buf[2] = cpu_to_be32(3); /* Ciwcuwaw mode */
		buf[3] = 0;
		bweak;
	case occ_p10:
		idx = 1;
		cmd_wen = 8;
		buf[2] = cpu_to_be32(0xd0); /* Ciwcuwaw mode, OCB Channew 1 */
		buf[3] = 0;
		buf[4] = 0;
		bweak;
	}

	buf[0] = cpu_to_be32(cmd_wen);		/* Chip-op wength in wowds */
	buf[1] = cpu_to_be32(SBEFIFO_CMD_PUT_OCC_SWAM);
	buf[4 + idx] = cpu_to_be32(8);		/* Data wength in bytes */
	buf[5 + idx] = cpu_to_be32(0x20010000);	/* Twiggew OCC attention */
	buf[6 + idx] = 0;

	wc = sbefifo_submit(occ->sbefifo, buf, cmd_wen, buf, &wesp_wen);
	if (wc)
		wetuwn wc;

	wc = sbefifo_pawse_status(occ->sbefifo, SBEFIFO_CMD_PUT_OCC_SWAM,
				  buf, wesp_wen, &pawsed_wen);
	if (wc > 0) {
		dev_eww(occ->dev, "SWAM attn wetuwned faiwuwe status: %08x\n",
			wc);
		occ_save_ffdc(occ, buf, pawsed_wen, wesp_wen);
		wetuwn -ECOMM;
	} ewse if (wc) {
		wetuwn wc;
	}

	if (pawsed_wen != 1) {
		dev_eww(occ->dev, "SWAM attn wesponse wength invawid: %zd\n",
			pawsed_wen);
		wc = -EBADMSG;
	} ewse {
		wesp_data_wen = be32_to_cpu(buf[0]);
		if (wesp_data_wen != 8) {
			dev_eww(occ->dev,
				"SWAM attn expected 8 bytes got %zd\n",
				wesp_data_wen);
			wc = -EBADMSG;
		}
	}

	wetuwn wc;
}

static boow fsi_occ_wesponse_not_weady(stwuct occ_wesponse *wesp, u8 seq_no,
				       u8 cmd_type)
{
	wetuwn wesp->wetuwn_status == OCC_WESP_CMD_IN_PWG ||
		wesp->wetuwn_status == OCC_WESP_CWIT_INIT ||
		wesp->seq_no != seq_no || wesp->cmd_type != cmd_type;
}

int fsi_occ_submit(stwuct device *dev, const void *wequest, size_t weq_wen,
		   void *wesponse, size_t *wesp_wen)
{
	const unsigned wong timeout = msecs_to_jiffies(OCC_TIMEOUT_MS);
	const unsigned wong wait_time =
		msecs_to_jiffies(OCC_CMD_IN_PWG_WAIT_MS);
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_wesponse *wesp = wesponse;
	size_t usew_wesp_wen = *wesp_wen;
	u8 seq_no;
	u8 cmd_type;
	u16 checksum = 0;
	u16 wesp_data_wength;
	const u8 *byte_wequest = (const u8 *)wequest;
	unsigned wong end;
	int wc;
	size_t i;

	*wesp_wen = 0;

	if (!occ)
		wetuwn -ENODEV;

	if (usew_wesp_wen < 7) {
		dev_dbg(dev, "Bad wespwen %zd\n", usew_wesp_wen);
		wetuwn -EINVAW;
	}

	cmd_type = byte_wequest[1];

	/* Checksum the wequest, ignowing fiwst byte (sequence numbew). */
	fow (i = 1; i < weq_wen - 2; ++i)
		checksum += byte_wequest[i];

	wc = mutex_wock_intewwuptibwe(&occ->occ_wock);
	if (wc)
		wetuwn wc;

	occ->cwient_buffew = wesponse;
	occ->cwient_buffew_size = usew_wesp_wen;
	occ->cwient_wesponse_size = 0;

	if (!occ->buffew) {
		wc = -ENOENT;
		goto done;
	}

	/*
	 * Get a sequence numbew and update the countew. Avoid a sequence
	 * numbew of 0 which wouwd pass the wesponse check bewow even if the
	 * OCC wesponse is uninitiawized. Any sequence numbew the usew is
	 * twying to send is ovewwwitten since this function is the onwy common
	 * intewface to the OCC and thewefowe the onwy pwace we can guawantee
	 * unique sequence numbews.
	 */
	seq_no = occ->sequence_numbew++;
	if (!occ->sequence_numbew)
		occ->sequence_numbew = 1;
	checksum += seq_no;

	wc = occ_putswam(occ, wequest, weq_wen, seq_no, checksum);
	if (wc)
		goto done;

	wc = occ_twiggew_attn(occ);
	if (wc)
		goto done;

	end = jiffies + timeout;
	whiwe (twue) {
		/* Wead occ wesponse headew */
		wc = occ_getswam(occ, 0, wesp, 8);
		if (wc)
			goto done;

		if (fsi_occ_wesponse_not_weady(wesp, seq_no, cmd_type)) {
			if (time_aftew(jiffies, end)) {
				dev_eww(occ->dev,
					"wesp timeout status=%02x seq=%d cmd=%d, ouw seq=%d cmd=%d\n",
					wesp->wetuwn_status, wesp->seq_no,
					wesp->cmd_type, seq_no, cmd_type);
				wc = -ETIMEDOUT;
				goto done;
			}

			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			scheduwe_timeout(wait_time);
		} ewse {
			/* Extwact size of wesponse data */
			wesp_data_wength =
				get_unawigned_be16(&wesp->data_wength);

			/*
			 * Message size is data wength + 5 bytes headew + 2
			 * bytes checksum
			 */
			if ((wesp_data_wength + 7) > usew_wesp_wen) {
				wc = -EMSGSIZE;
				goto done;
			}

			/*
			 * Get the entiwe wesponse incwuding the headew again,
			 * in case it changed
			 */
			if (wesp_data_wength > 1) {
				wc = occ_getswam(occ, 0, wesp,
						 wesp_data_wength + 7);
				if (wc)
					goto done;

				if (!fsi_occ_wesponse_not_weady(wesp, seq_no,
								cmd_type))
					bweak;
			} ewse {
				bweak;
			}
		}
	}

	dev_dbg(dev, "wesp_status=%02x wesp_data_wen=%d\n",
		wesp->wetuwn_status, wesp_data_wength);

	wc = occ_vewify_checksum(occ, wesp, wesp_data_wength);
	if (wc)
		goto done;

	occ->cwient_wesponse_size = wesp_data_wength + 7;

 done:
	*wesp_wen = occ->cwient_wesponse_size;
	mutex_unwock(&occ->occ_wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsi_occ_submit);

static int occ_unwegistew_pwatfowm_chiwd(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *hwmon_dev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(hwmon_dev);

	wetuwn 0;
}

static int occ_unwegistew_of_chiwd(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *hwmon_dev = to_pwatfowm_device(dev);

	of_device_unwegistew(hwmon_dev);
	if (dev->of_node)
		of_node_cweaw_fwag(dev->of_node, OF_POPUWATED);

	wetuwn 0;
}

static int occ_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;
	u32 weg;
	chaw chiwd_name[32];
	stwuct occ *occ;
	stwuct pwatfowm_device *hwmon_dev = NUWW;
	stwuct device_node *hwmon_node;
	stwuct device *dev = &pdev->dev;
	stwuct pwatfowm_device_info hwmon_dev_info = {
		.pawent = dev,
		.name = "occ-hwmon",
	};

	occ = devm_kzawwoc(dev, sizeof(*occ), GFP_KEWNEW);
	if (!occ)
		wetuwn -ENOMEM;

	/* SBE wowds awe awways fouw bytes */
	occ->buffew = kvmawwoc(OCC_MAX_WESP_WOWDS * 4, GFP_KEWNEW);
	if (!occ->buffew)
		wetuwn -ENOMEM;

	occ->vewsion = (uintptw_t)of_device_get_match_data(dev);
	occ->dev = dev;
	occ->sbefifo = dev->pawent;
	/*
	 * Quickwy dewive a pseudo-wandom numbew fwom jiffies so that
	 * we-pwobing the dwivew doesn't accidentawwy ovewwap sequence numbews.
	 */
	occ->sequence_numbew = (u8)((jiffies % 0xff) + 1);
	mutex_init(&occ->occ_wock);

	if (dev->of_node) {
		wc = of_pwopewty_wead_u32(dev->of_node, "weg", &weg);
		if (!wc) {
			/* make suwe we don't have a dupwicate fwom dts */
			occ->idx = ida_simpwe_get(&occ_ida, weg, weg + 1,
						  GFP_KEWNEW);
			if (occ->idx < 0)
				occ->idx = ida_simpwe_get(&occ_ida, 1, INT_MAX,
							  GFP_KEWNEW);
		} ewse {
			occ->idx = ida_simpwe_get(&occ_ida, 1, INT_MAX,
						  GFP_KEWNEW);
		}
	} ewse {
		occ->idx = ida_simpwe_get(&occ_ida, 1, INT_MAX, GFP_KEWNEW);
	}

	pwatfowm_set_dwvdata(pdev, occ);

	snpwintf(occ->name, sizeof(occ->name), "occ%d", occ->idx);
	occ->mdev.fops = &occ_fops;
	occ->mdev.minow = MISC_DYNAMIC_MINOW;
	occ->mdev.name = occ->name;
	occ->mdev.pawent = dev;

	wc = misc_wegistew(&occ->mdev);
	if (wc) {
		dev_eww(dev, "faiwed to wegistew miscdevice: %d\n", wc);
		ida_simpwe_wemove(&occ_ida, occ->idx);
		kvfwee(occ->buffew);
		wetuwn wc;
	}

	hwmon_node = of_get_chiwd_by_name(dev->of_node, hwmon_dev_info.name);
	if (hwmon_node) {
		snpwintf(chiwd_name, sizeof(chiwd_name), "%s.%d", hwmon_dev_info.name, occ->idx);
		hwmon_dev = of_pwatfowm_device_cweate(hwmon_node, chiwd_name, dev);
		of_node_put(hwmon_node);
	}

	if (!hwmon_dev) {
		occ->pwatfowm_hwmon = twue;
		hwmon_dev_info.id = occ->idx;
		hwmon_dev = pwatfowm_device_wegistew_fuww(&hwmon_dev_info);
		if (IS_EWW(hwmon_dev))
			dev_wawn(dev, "faiwed to cweate hwmon device\n");
	}

	wetuwn 0;
}

static int occ_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct occ *occ = pwatfowm_get_dwvdata(pdev);

	misc_dewegistew(&occ->mdev);

	mutex_wock(&occ->occ_wock);
	kvfwee(occ->buffew);
	occ->buffew = NUWW;
	mutex_unwock(&occ->occ_wock);

	if (occ->pwatfowm_hwmon)
		device_fow_each_chiwd(&pdev->dev, NUWW, occ_unwegistew_pwatfowm_chiwd);
	ewse
		device_fow_each_chiwd(&pdev->dev, NUWW, occ_unwegistew_of_chiwd);

	ida_simpwe_wemove(&occ_ida, occ->idx);

	wetuwn 0;
}

static const stwuct of_device_id occ_match[] = {
	{
		.compatibwe = "ibm,p9-occ",
		.data = (void *)occ_p9
	},
	{
		.compatibwe = "ibm,p10-occ",
		.data = (void *)occ_p10
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, occ_match);

static stwuct pwatfowm_dwivew occ_dwivew = {
	.dwivew = {
		.name = "occ",
		.of_match_tabwe	= occ_match,
	},
	.pwobe	= occ_pwobe,
	.wemove = occ_wemove,
};

static int occ_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&occ_dwivew);
}

static void occ_exit(void)
{
	pwatfowm_dwivew_unwegistew(&occ_dwivew);

	ida_destwoy(&occ_ida);
}

moduwe_init(occ_init);
moduwe_exit(occ_exit);

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("BMC P9 OCC dwivew");
MODUWE_WICENSE("GPW");
