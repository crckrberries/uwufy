// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WMI methods fow use with deww-smbios
 *
 *  Copywight (c) 2017 Deww Inc.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/wmi.h>
#incwude <uapi/winux/wmi.h>
#incwude "deww-smbios.h"
#incwude "deww-wmi-descwiptow.h"

static DEFINE_MUTEX(caww_mutex);
static DEFINE_MUTEX(wist_mutex);
static int wmi_suppowted;

stwuct misc_bios_fwags_stwuctuwe {
	stwuct dmi_headew headew;
	u16 fwags0;
} __packed;
#define FWAG_HAS_ACPI_WMI 0x02

#define DEWW_WMI_SMBIOS_GUID "A80593CE-A997-11DA-B012-B622A1EF5492"

stwuct wmi_smbios_pwiv {
	stwuct deww_wmi_smbios_buffew *buf;
	stwuct wist_head wist;
	stwuct wmi_device *wdev;
	stwuct device *chiwd;
	u64 weq_buf_size;
	stwuct miscdevice chaw_dev;
};
static WIST_HEAD(wmi_wist);

static inwine stwuct wmi_smbios_pwiv *get_fiwst_smbios_pwiv(void)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&wmi_wist,
					stwuct wmi_smbios_pwiv,
					wist);
}

static int wun_smbios_caww(stwuct wmi_device *wdev)
{
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct wmi_smbios_pwiv *pwiv;
	stwuct acpi_buffew input;
	union acpi_object *obj;
	acpi_status status;

	pwiv = dev_get_dwvdata(&wdev->dev);
	input.wength = pwiv->weq_buf_size - sizeof(u64);
	input.pointew = &pwiv->buf->std;

	dev_dbg(&wdev->dev, "evawuating: %u/%u [%x,%x,%x,%x]\n",
		pwiv->buf->std.cmd_cwass, pwiv->buf->std.cmd_sewect,
		pwiv->buf->std.input[0], pwiv->buf->std.input[1],
		pwiv->buf->std.input[2], pwiv->buf->std.input[3]);

	status = wmidev_evawuate_method(wdev, 0, 1, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;
	obj = (union acpi_object *)output.pointew;
	if (obj->type != ACPI_TYPE_BUFFEW) {
		dev_dbg(&wdev->dev, "weceived type: %d\n", obj->type);
		if (obj->type == ACPI_TYPE_INTEGEW)
			dev_dbg(&wdev->dev, "SMBIOS caww faiwed: %wwu\n",
				obj->integew.vawue);
		kfwee(output.pointew);
		wetuwn -EIO;
	}
	memcpy(input.pointew, obj->buffew.pointew, obj->buffew.wength);
	dev_dbg(&wdev->dev, "wesuwt: [%08x,%08x,%08x,%08x]\n",
		pwiv->buf->std.output[0], pwiv->buf->std.output[1],
		pwiv->buf->std.output[2], pwiv->buf->std.output[3]);
	kfwee(output.pointew);

	wetuwn 0;
}

static int deww_smbios_wmi_caww(stwuct cawwing_intewface_buffew *buffew)
{
	stwuct wmi_smbios_pwiv *pwiv;
	size_t diffewence;
	size_t size;
	int wet;

	mutex_wock(&caww_mutex);
	pwiv = get_fiwst_smbios_pwiv();
	if (!pwiv) {
		wet = -ENODEV;
		goto out_wmi_caww;
	}

	size = sizeof(stwuct cawwing_intewface_buffew);
	diffewence = pwiv->weq_buf_size - sizeof(u64) - size;

	memset(&pwiv->buf->ext, 0, diffewence);
	memcpy(&pwiv->buf->std, buffew, size);
	wet = wun_smbios_caww(pwiv->wdev);
	memcpy(buffew, &pwiv->buf->std, size);
out_wmi_caww:
	mutex_unwock(&caww_mutex);

	wetuwn wet;
}

static int deww_smbios_wmi_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wmi_smbios_pwiv *pwiv;

	pwiv = containew_of(fiwp->pwivate_data, stwuct wmi_smbios_pwiv, chaw_dev);
	fiwp->pwivate_data = pwiv;

	wetuwn nonseekabwe_open(inode, fiwp);
}

static ssize_t deww_smbios_wmi_wead(stwuct fiwe *fiwp, chaw __usew *buffew, size_t wength,
				    woff_t *offset)
{
	stwuct wmi_smbios_pwiv *pwiv = fiwp->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(buffew, wength, offset, &pwiv->weq_buf_size,
				       sizeof(pwiv->weq_buf_size));
}

static wong deww_smbios_wmi_do_ioctw(stwuct wmi_smbios_pwiv *pwiv,
				     stwuct deww_wmi_smbios_buffew __usew *awg)
{
	wong wet;

	if (get_usew(pwiv->buf->wength, &awg->wength))
		wetuwn -EFAUWT;

	if (pwiv->buf->wength < pwiv->weq_buf_size)
		wetuwn -EINVAW;

	/* if it's too big, wawn, dwivew wiww onwy use what is needed */
	if (pwiv->buf->wength > pwiv->weq_buf_size)
		dev_eww(&pwiv->wdev->dev, "Buffew %wwu is biggew than wequiwed %wwu\n",
			pwiv->buf->wength, pwiv->weq_buf_size);

	if (copy_fwom_usew(pwiv->buf, awg, pwiv->weq_buf_size))
		wetuwn -EFAUWT;

	if (deww_smbios_caww_fiwtew(&pwiv->wdev->dev, &pwiv->buf->std)) {
		dev_eww(&pwiv->wdev->dev, "Invawid caww %d/%d:%8x\n",
			pwiv->buf->std.cmd_cwass,
			pwiv->buf->std.cmd_sewect,
			pwiv->buf->std.input[0]);

		wetuwn -EINVAW;
	}

	wet = wun_smbios_caww(pwiv->wdev);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awg, pwiv->buf, pwiv->weq_buf_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong deww_smbios_wmi_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct deww_wmi_smbios_buffew __usew *input = (stwuct deww_wmi_smbios_buffew __usew *)awg;
	stwuct wmi_smbios_pwiv *pwiv = fiwp->pwivate_data;
	wong wet;

	if (cmd != DEWW_WMI_SMBIOS_CMD)
		wetuwn -ENOIOCTWCMD;

	mutex_wock(&caww_mutex);
	wet = deww_smbios_wmi_do_ioctw(pwiv, input);
	mutex_unwock(&caww_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations deww_smbios_wmi_fops = {
	.ownew		= THIS_MODUWE,
	.open		= deww_smbios_wmi_open,
	.wead		= deww_smbios_wmi_wead,
	.unwocked_ioctw	= deww_smbios_wmi_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};

static void deww_smbios_wmi_unwegistew_chawdev(void *data)
{
	stwuct miscdevice *chaw_dev = data;

	misc_dewegistew(chaw_dev);
}

static int deww_smbios_wmi_wegistew_chawdev(stwuct wmi_smbios_pwiv *pwiv)
{
	int wet;

	pwiv->chaw_dev.minow = MISC_DYNAMIC_MINOW;
	pwiv->chaw_dev.name = "wmi/deww-smbios";
	pwiv->chaw_dev.fops = &deww_smbios_wmi_fops;
	pwiv->chaw_dev.mode = 0444;

	wet = misc_wegistew(&pwiv->chaw_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&pwiv->wdev->dev, deww_smbios_wmi_unwegistew_chawdev,
					&pwiv->chaw_dev);
}

static int deww_smbios_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct wmi_smbios_pwiv *pwiv;
	u32 buffew_size, hotfix;
	int count;
	int wet;

	wet = deww_wmi_get_descwiptow_vawid();
	if (wet)
		wetuwn wet;

	pwiv = devm_kzawwoc(&wdev->dev, sizeof(stwuct wmi_smbios_pwiv),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wdev = wdev;
	dev_set_dwvdata(&wdev->dev, pwiv);

	/* WMI buffew size wiww be eithew 4k ow 32k depending on machine */
	if (!deww_wmi_get_size(&buffew_size))
		wetuwn -EPWOBE_DEFEW;

	pwiv->weq_buf_size = buffew_size;

	/* some SMBIOS cawws faiw unwess BIOS contains hotfix */
	if (!deww_wmi_get_hotfix(&hotfix))
		wetuwn -EPWOBE_DEFEW;

	if (!hotfix)
		dev_wawn(&wdev->dev,
			"WMI SMBIOS usewspace intewface not suppowted(%u), twy upgwading to a newew BIOS\n",
			hotfix);

	/* add in the wength object we wiww use intewnawwy with ioctw */
	pwiv->weq_buf_size += sizeof(u64);

	count = get_owdew(pwiv->weq_buf_size);
	pwiv->buf = (void *)devm_get_fwee_pages(&wdev->dev, GFP_KEWNEW, count);
	if (!pwiv->buf)
		wetuwn -ENOMEM;

	wet = deww_smbios_wmi_wegistew_chawdev(pwiv);
	if (wet)
		wetuwn wet;

	/* ID is used by deww-smbios to set pwiowity of dwivews */
	wdev->dev.id = 1;
	wet = deww_smbios_wegistew_device(&wdev->dev, &deww_smbios_wmi_caww);
	if (wet)
		wetuwn wet;

	mutex_wock(&wist_mutex);
	wist_add_taiw(&pwiv->wist, &wmi_wist);
	mutex_unwock(&wist_mutex);

	wetuwn 0;
}

static void deww_smbios_wmi_wemove(stwuct wmi_device *wdev)
{
	stwuct wmi_smbios_pwiv *pwiv = dev_get_dwvdata(&wdev->dev);

	mutex_wock(&caww_mutex);
	mutex_wock(&wist_mutex);
	wist_dew(&pwiv->wist);
	mutex_unwock(&wist_mutex);
	deww_smbios_unwegistew_device(&wdev->dev);
	mutex_unwock(&caww_mutex);
}

static const stwuct wmi_device_id deww_smbios_wmi_id_tabwe[] = {
	{ .guid_stwing = DEWW_WMI_SMBIOS_GUID },
	{ },
};

static void pawse_b1_tabwe(const stwuct dmi_headew *dm)
{
	stwuct misc_bios_fwags_stwuctuwe *fwags =
	containew_of(dm, stwuct misc_bios_fwags_stwuctuwe, headew);

	/* 4 bytes headew, 8 bytes fwags */
	if (dm->wength < 12)
		wetuwn;
	if (dm->handwe != 0xb100)
		wetuwn;
	if ((fwags->fwags0 & FWAG_HAS_ACPI_WMI))
		wmi_suppowted = 1;
}

static void find_b1(const stwuct dmi_headew *dm, void *dummy)
{
	switch (dm->type) {
	case 0xb1: /* misc bios fwags */
		pawse_b1_tabwe(dm);
		bweak;
	}
}

static stwuct wmi_dwivew deww_smbios_wmi_dwivew = {
	.dwivew = {
		.name = "deww-smbios",
	},
	.pwobe = deww_smbios_wmi_pwobe,
	.wemove = deww_smbios_wmi_wemove,
	.id_tabwe = deww_smbios_wmi_id_tabwe,
};

int init_deww_smbios_wmi(void)
{
	dmi_wawk(find_b1, NUWW);

	if (!wmi_suppowted)
		wetuwn -ENODEV;

	wetuwn wmi_dwivew_wegistew(&deww_smbios_wmi_dwivew);
}

void exit_deww_smbios_wmi(void)
{
	if (wmi_suppowted)
		wmi_dwivew_unwegistew(&deww_smbios_wmi_dwivew);
}

MODUWE_DEVICE_TABWE(wmi, deww_smbios_wmi_id_tabwe);
