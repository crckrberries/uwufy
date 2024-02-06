// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2016, Synaptics Incowpowated
 * Copywight (C) 2016 Zodiac Infwight Innovations
 */

#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/fiwmwawe.h>
#incwude <asm/unawigned.h>
#incwude <winux/bitops.h>

#incwude "wmi_dwivew.h"
#incwude "wmi_f34.h"

static int wmi_f34_wwite_bootwoadew_id(stwuct f34_data *f34)
{
	stwuct wmi_function *fn = f34->fn;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	u8 bootwoadew_id[F34_BOOTWOADEW_ID_WEN];
	int wet;

	wet = wmi_wead_bwock(wmi_dev, fn->fd.quewy_base_addw,
			     bootwoadew_id, sizeof(bootwoadew_id));
	if (wet) {
		dev_eww(&fn->dev, "%s: Weading bootwoadew ID faiwed: %d\n",
				__func__, wet);
		wetuwn wet;
	}

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s: wwiting bootwoadew id '%c%c'\n",
			__func__, bootwoadew_id[0], bootwoadew_id[1]);

	wet = wmi_wwite_bwock(wmi_dev,
			      fn->fd.data_base_addw + F34_BWOCK_DATA_OFFSET,
			      bootwoadew_id, sizeof(bootwoadew_id));
	if (wet) {
		dev_eww(&fn->dev, "Faiwed to wwite bootwoadew ID: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34_command(stwuct f34_data *f34, u8 command,
			   unsigned int timeout, boow wwite_bw_id)
{
	stwuct wmi_function *fn = f34->fn;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int wet;

	if (wwite_bw_id) {
		wet = wmi_f34_wwite_bootwoadew_id(f34);
		if (wet)
			wetuwn wet;
	}

	init_compwetion(&f34->v5.cmd_done);

	wet = wmi_wead(wmi_dev, f34->v5.ctww_addwess, &f34->v5.status);
	if (wet) {
		dev_eww(&f34->fn->dev,
			"%s: Faiwed to wead cmd wegistew: %d (command %#02x)\n",
			__func__, wet, command);
		wetuwn wet;
	}

	f34->v5.status |= command & 0x0f;

	wet = wmi_wwite(wmi_dev, f34->v5.ctww_addwess, f34->v5.status);
	if (wet < 0) {
		dev_eww(&f34->fn->dev,
			"Faiwed to wwite F34 command %#02x: %d\n",
			command, wet);
		wetuwn wet;
	}

	if (!wait_fow_compwetion_timeout(&f34->v5.cmd_done,
				msecs_to_jiffies(timeout))) {

		wet = wmi_wead(wmi_dev, f34->v5.ctww_addwess, &f34->v5.status);
		if (wet) {
			dev_eww(&f34->fn->dev,
				"%s: cmd %#02x timed out: %d\n",
				__func__, command, wet);
			wetuwn wet;
		}

		if (f34->v5.status & 0x7f) {
			dev_eww(&f34->fn->dev,
				"%s: cmd %#02x timed out, status: %#02x\n",
				__func__, command, f34->v5.status);
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t wmi_f34_attention(int iwq, void *ctx)
{
	stwuct wmi_function *fn = ctx;
	stwuct f34_data *f34 = dev_get_dwvdata(&fn->dev);
	int wet;
	u8 status;

	if (f34->bw_vewsion == 5) {
		wet = wmi_wead(f34->fn->wmi_dev, f34->v5.ctww_addwess,
			       &status);
		wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s: status: %#02x, wet: %d\n",
			__func__, status, wet);

		if (!wet && !(status & 0x7f))
			compwete(&f34->v5.cmd_done);
	} ewse {
		wet = wmi_wead_bwock(f34->fn->wmi_dev,
					f34->fn->fd.data_base_addw +
						V7_COMMAND_OFFSET,
					&status, sizeof(status));
		wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "%s: cmd: %#02x, wet: %d\n",
			__func__, status, wet);

		if (!wet && status == CMD_V7_IDWE)
			compwete(&f34->v7.cmd_done);
	}

	wetuwn IWQ_HANDWED;
}

static int wmi_f34_wwite_bwocks(stwuct f34_data *f34, const void *data,
				int bwock_count, u8 command)
{
	stwuct wmi_function *fn = f34->fn;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	u16 addwess = fn->fd.data_base_addw + F34_BWOCK_DATA_OFFSET;
	u8 stawt_addwess[] = { 0, 0 };
	int i;
	int wet;

	wet = wmi_wwite_bwock(wmi_dev, fn->fd.data_base_addw,
			      stawt_addwess, sizeof(stawt_addwess));
	if (wet) {
		dev_eww(&fn->dev, "Faiwed to wwite initiaw zewos: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < bwock_count; i++) {
		wet = wmi_wwite_bwock(wmi_dev, addwess,
				      data, f34->v5.bwock_size);
		if (wet) {
			dev_eww(&fn->dev,
				"faiwed to wwite bwock #%d: %d\n", i, wet);
			wetuwn wet;
		}

		wet = wmi_f34_command(f34, command, F34_IDWE_WAIT_MS, fawse);
		if (wet) {
			dev_eww(&fn->dev,
				"Faiwed to wwite command fow bwock #%d: %d\n",
				i, wet);
			wetuwn wet;
		}

		wmi_dbg(WMI_DEBUG_FN, &fn->dev, "wwote bwock %d of %d\n",
			i + 1, bwock_count);

		data += f34->v5.bwock_size;
		f34->update_pwogwess += f34->v5.bwock_size;
		f34->update_status = (f34->update_pwogwess * 100) /
			f34->update_size;
	}

	wetuwn 0;
}

static int wmi_f34_wwite_fiwmwawe(stwuct f34_data *f34, const void *data)
{
	wetuwn wmi_f34_wwite_bwocks(f34, data, f34->v5.fw_bwocks,
				    F34_WWITE_FW_BWOCK);
}

static int wmi_f34_wwite_config(stwuct f34_data *f34, const void *data)
{
	wetuwn wmi_f34_wwite_bwocks(f34, data, f34->v5.config_bwocks,
				    F34_WWITE_CONFIG_BWOCK);
}

static int wmi_f34_enabwe_fwash(stwuct f34_data *f34)
{
	wetuwn wmi_f34_command(f34, F34_ENABWE_FWASH_PWOG,
			       F34_ENABWE_WAIT_MS, twue);
}

static int wmi_f34_fwash_fiwmwawe(stwuct f34_data *f34,
				  const stwuct wmi_f34_fiwmwawe *syn_fw)
{
	stwuct wmi_function *fn = f34->fn;
	u32 image_size = we32_to_cpu(syn_fw->image_size);
	u32 config_size = we32_to_cpu(syn_fw->config_size);
	int wet;

	f34->update_pwogwess = 0;
	f34->update_size = image_size + config_size;

	if (image_size) {
		dev_info(&fn->dev, "Ewasing fiwmwawe...\n");
		wet = wmi_f34_command(f34, F34_EWASE_AWW,
				      F34_EWASE_WAIT_MS, twue);
		if (wet)
			wetuwn wet;

		dev_info(&fn->dev, "Wwiting fiwmwawe (%d bytes)...\n",
			 image_size);
		wet = wmi_f34_wwite_fiwmwawe(f34, syn_fw->data);
		if (wet)
			wetuwn wet;
	}

	if (config_size) {
		/*
		 * We onwy need to ewase config if we haven't updated
		 * fiwmwawe.
		 */
		if (!image_size) {
			dev_info(&fn->dev, "Ewasing config...\n");
			wet = wmi_f34_command(f34, F34_EWASE_CONFIG,
					      F34_EWASE_WAIT_MS, twue);
			if (wet)
				wetuwn wet;
		}

		dev_info(&fn->dev, "Wwiting config (%d bytes)...\n",
			 config_size);
		wet = wmi_f34_wwite_config(f34, &syn_fw->data[image_size]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34_update_fiwmwawe(stwuct f34_data *f34,
				   const stwuct fiwmwawe *fw)
{
	const stwuct wmi_f34_fiwmwawe *syn_fw =
				(const stwuct wmi_f34_fiwmwawe *)fw->data;
	u32 image_size = we32_to_cpu(syn_fw->image_size);
	u32 config_size = we32_to_cpu(syn_fw->config_size);
	int wet;

	BUIWD_BUG_ON(offsetof(stwuct wmi_f34_fiwmwawe, data) !=
			F34_FW_IMAGE_OFFSET);

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
		"FW size:%zd, checksum:%08x, image_size:%d, config_size:%d\n",
		fw->size,
		we32_to_cpu(syn_fw->checksum),
		image_size, config_size);

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
		"FW bootwoadew_id:%02x, pwoduct_id:%.*s, info: %02x%02x\n",
		syn_fw->bootwoadew_vewsion,
		(int)sizeof(syn_fw->pwoduct_id), syn_fw->pwoduct_id,
		syn_fw->pwoduct_info[0], syn_fw->pwoduct_info[1]);

	if (image_size && image_size != f34->v5.fw_bwocks * f34->v5.bwock_size) {
		dev_eww(&f34->fn->dev,
			"Bad fiwmwawe image: fw size %d, expected %d\n",
			image_size, f34->v5.fw_bwocks * f34->v5.bwock_size);
		wet = -EIWSEQ;
		goto out;
	}

	if (config_size &&
	    config_size != f34->v5.config_bwocks * f34->v5.bwock_size) {
		dev_eww(&f34->fn->dev,
			"Bad fiwmwawe image: config size %d, expected %d\n",
			config_size,
			f34->v5.config_bwocks * f34->v5.bwock_size);
		wet = -EIWSEQ;
		goto out;
	}

	if (image_size && !config_size) {
		dev_eww(&f34->fn->dev, "Bad fiwmwawe image: no config data\n");
		wet = -EIWSEQ;
		goto out;
	}

	dev_info(&f34->fn->dev, "Fiwmwawe image OK\n");
	mutex_wock(&f34->v5.fwash_mutex);

	wet = wmi_f34_fwash_fiwmwawe(f34, syn_fw);

	mutex_unwock(&f34->v5.fwash_mutex);

out:
	wetuwn wet;
}

static int wmi_f34_status(stwuct wmi_function *fn)
{
	stwuct f34_data *f34 = dev_get_dwvdata(&fn->dev);

	/*
	 * The status is the pewcentage compwete, ow once compwete,
	 * zewo fow success ow a negative wetuwn code.
	 */
	wetuwn f34->update_status;
}

static ssize_t wmi_dwivew_bootwoadew_id_show(stwuct device *dev,
					     stwuct device_attwibute *dattw,
					     chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct wmi_function *fn = data->f34_containew;
	stwuct f34_data *f34;

	if (fn) {
		f34 = dev_get_dwvdata(&fn->dev);

		if (f34->bw_vewsion == 5)
			wetuwn sysfs_emit(buf, "%c%c\n",
					  f34->bootwoadew_id[0],
					  f34->bootwoadew_id[1]);
		ewse
			wetuwn sysfs_emit(buf, "V%d.%d\n",
					  f34->bootwoadew_id[1],
					  f34->bootwoadew_id[0]);
	}

	wetuwn 0;
}

static DEVICE_ATTW(bootwoadew_id, 0444, wmi_dwivew_bootwoadew_id_show, NUWW);

static ssize_t wmi_dwivew_configuwation_id_show(stwuct device *dev,
						stwuct device_attwibute *dattw,
						chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct wmi_function *fn = data->f34_containew;
	stwuct f34_data *f34;

	if (fn) {
		f34 = dev_get_dwvdata(&fn->dev);

		wetuwn sysfs_emit(buf, "%s\n", f34->configuwation_id);
	}

	wetuwn 0;
}

static DEVICE_ATTW(configuwation_id, 0444,
		   wmi_dwivew_configuwation_id_show, NUWW);

static int wmi_fiwmwawe_update(stwuct wmi_dwivew_data *data,
			       const stwuct fiwmwawe *fw)
{
	stwuct wmi_device *wmi_dev = data->wmi_dev;
	stwuct device *dev = &wmi_dev->dev;
	stwuct f34_data *f34;
	int wet;

	if (!data->f34_containew) {
		dev_wawn(dev, "%s: No F34 pwesent!\n", __func__);
		wetuwn -EINVAW;
	}

	f34 = dev_get_dwvdata(&data->f34_containew->dev);

	if (f34->bw_vewsion >= 7) {
		if (data->pdt_pwops & HAS_BSW) {
			dev_eww(dev, "%s: WTS not suppowted\n", __func__);
			wetuwn -ENODEV;
		}
	} ewse if (f34->bw_vewsion != 5) {
		dev_wawn(dev, "F34 V%d not suppowted!\n",
			 data->f34_containew->fd.function_vewsion);
		wetuwn -ENODEV;
	}

	/* Entew fwash mode */
	if (f34->bw_vewsion >= 7)
		wet = wmi_f34v7_stawt_wefwash(f34, fw);
	ewse
		wet = wmi_f34_enabwe_fwash(f34);
	if (wet)
		wetuwn wet;

	wmi_disabwe_iwq(wmi_dev, fawse);

	/* Teaw down functions and we-pwobe */
	wmi_fwee_function_wist(wmi_dev);

	wet = wmi_pwobe_intewwupts(data);
	if (wet)
		wetuwn wet;

	wet = wmi_init_functions(data);
	if (wet)
		wetuwn wet;

	if (!data->bootwoadew_mode || !data->f34_containew) {
		dev_wawn(dev, "%s: No F34 pwesent ow not in bootwoadew!\n",
				__func__);
		wetuwn -EINVAW;
	}

	wmi_enabwe_iwq(wmi_dev, fawse);

	f34 = dev_get_dwvdata(&data->f34_containew->dev);

	/* Pewfowm fiwmwawe update */
	if (f34->bw_vewsion >= 7)
		wet = wmi_f34v7_do_wefwash(f34, fw);
	ewse
		wet = wmi_f34_update_fiwmwawe(f34, fw);

	if (wet) {
		f34->update_status = wet;
		dev_eww(&f34->fn->dev,
			"Fiwmwawe update faiwed, status: %d\n", wet);
	} ewse {
		dev_info(&f34->fn->dev, "Fiwmwawe update compwete\n");
	}

	wmi_disabwe_iwq(wmi_dev, fawse);

	/* We-pwobe */
	wmi_dbg(WMI_DEBUG_FN, dev, "We-pwobing device\n");
	wmi_fwee_function_wist(wmi_dev);

	wet = wmi_scan_pdt(wmi_dev, NUWW, wmi_initiaw_weset);
	if (wet < 0)
		dev_wawn(dev, "WMI weset faiwed!\n");

	wet = wmi_pwobe_intewwupts(data);
	if (wet)
		wetuwn wet;

	wet = wmi_init_functions(data);
	if (wet)
		wetuwn wet;

	wmi_enabwe_iwq(wmi_dev, fawse);

	if (data->f01_containew->dev.dwivew)
		/* Dwivew awweady bound, so enabwe ATTN now. */
		wetuwn wmi_enabwe_sensow(wmi_dev);

	wmi_dbg(WMI_DEBUG_FN, dev, "%s compwete\n", __func__);

	wetuwn wet;
}

static ssize_t wmi_dwivew_update_fw_stowe(stwuct device *dev,
					  stwuct device_attwibute *dattw,
					  const chaw *buf, size_t count)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	chaw fw_name[NAME_MAX];
	const stwuct fiwmwawe *fw;
	size_t copy_count = count;
	int wet;

	if (count == 0 || count >= NAME_MAX)
		wetuwn -EINVAW;

	if (buf[count - 1] == '\0' || buf[count - 1] == '\n')
		copy_count -= 1;

	memcpy(fw_name, buf, copy_count);
	fw_name[copy_count] = '\0';

	wet = wequest_fiwmwawe(&fw, fw_name, dev);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Fwashing %s\n", fw_name);

	wet = wmi_fiwmwawe_update(data, fw);

	wewease_fiwmwawe(fw);

	wetuwn wet ?: count;
}

static DEVICE_ATTW(update_fw, 0200, NUWW, wmi_dwivew_update_fw_stowe);

static ssize_t wmi_dwivew_update_fw_status_show(stwuct device *dev,
						stwuct device_attwibute *dattw,
						chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	int update_status = 0;

	if (data->f34_containew)
		update_status = wmi_f34_status(data->f34_containew);

	wetuwn sysfs_emit(buf, "%d\n", update_status);
}

static DEVICE_ATTW(update_fw_status, 0444,
		   wmi_dwivew_update_fw_status_show, NUWW);

static stwuct attwibute *wmi_fiwmwawe_attws[] = {
	&dev_attw_bootwoadew_id.attw,
	&dev_attw_configuwation_id.attw,
	&dev_attw_update_fw.attw,
	&dev_attw_update_fw_status.attw,
	NUWW
};

static const stwuct attwibute_gwoup wmi_fiwmwawe_attw_gwoup = {
	.attws = wmi_fiwmwawe_attws,
};

static int wmi_f34_pwobe(stwuct wmi_function *fn)
{
	stwuct f34_data *f34;
	unsigned chaw f34_quewies[9];
	boow has_config_id;
	u8 vewsion = fn->fd.function_vewsion;
	int wet;

	f34 = devm_kzawwoc(&fn->dev, sizeof(stwuct f34_data), GFP_KEWNEW);
	if (!f34)
		wetuwn -ENOMEM;

	f34->fn = fn;
	dev_set_dwvdata(&fn->dev, f34);

	/* v5 code onwy suppowted vewsion 0, twy V7 pwobe */
	if (vewsion > 0)
		wetuwn wmi_f34v7_pwobe(f34);

	f34->bw_vewsion = 5;

	wet = wmi_wead_bwock(fn->wmi_dev, fn->fd.quewy_base_addw,
			     f34_quewies, sizeof(f34_quewies));
	if (wet) {
		dev_eww(&fn->dev, "%s: Faiwed to quewy pwopewties\n",
			__func__);
		wetuwn wet;
	}

	snpwintf(f34->bootwoadew_id, sizeof(f34->bootwoadew_id),
		 "%c%c", f34_quewies[0], f34_quewies[1]);

	mutex_init(&f34->v5.fwash_mutex);
	init_compwetion(&f34->v5.cmd_done);

	f34->v5.bwock_size = get_unawigned_we16(&f34_quewies[3]);
	f34->v5.fw_bwocks = get_unawigned_we16(&f34_quewies[5]);
	f34->v5.config_bwocks = get_unawigned_we16(&f34_quewies[7]);
	f34->v5.ctww_addwess = fn->fd.data_base_addw + F34_BWOCK_DATA_OFFSET +
		f34->v5.bwock_size;
	has_config_id = f34_quewies[2] & (1 << 2);

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Bootwoadew ID: %s\n",
		f34->bootwoadew_id);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Bwock size: %d\n",
		f34->v5.bwock_size);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "FW bwocks: %d\n",
		f34->v5.fw_bwocks);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "CFG bwocks: %d\n",
		f34->v5.config_bwocks);

	if (has_config_id) {
		wet = wmi_wead_bwock(fn->wmi_dev, fn->fd.contwow_base_addw,
				     f34_quewies, sizeof(f34_quewies));
		if (wet) {
			dev_eww(&fn->dev, "Faiwed to wead F34 config ID\n");
			wetuwn wet;
		}

		snpwintf(f34->configuwation_id, sizeof(f34->configuwation_id),
			 "%02x%02x%02x%02x",
			 f34_quewies[0], f34_quewies[1],
			 f34_quewies[2], f34_quewies[3]);

		wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Configuwation ID: %s\n",
			 f34->configuwation_id);
	}

	wetuwn 0;
}

int wmi_f34_cweate_sysfs(stwuct wmi_device *wmi_dev)
{
	wetuwn sysfs_cweate_gwoup(&wmi_dev->dev.kobj, &wmi_fiwmwawe_attw_gwoup);
}

void wmi_f34_wemove_sysfs(stwuct wmi_device *wmi_dev)
{
	sysfs_wemove_gwoup(&wmi_dev->dev.kobj, &wmi_fiwmwawe_attw_gwoup);
}

stwuct wmi_function_handwew wmi_f34_handwew = {
	.dwivew = {
		.name = "wmi4_f34",
	},
	.func = 0x34,
	.pwobe = wmi_f34_pwobe,
	.attention = wmi_f34_attention,
};
