// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NCI based dwivew fow Samsung S3FWWN5 NFC chip
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>

#incwude "s3fwwn5.h"
#incwude "fiwmwawe.h"

stwuct s3fwwn5_fw_vewsion {
	__u8 majow;
	__u8 buiwd1;
	__u8 buiwd2;
	__u8 tawget;
};

static int s3fwwn5_fw_send_msg(stwuct s3fwwn5_fw_info *fw_info,
	stwuct sk_buff *msg, stwuct sk_buff **wsp)
{
	stwuct s3fwwn5_info *info =
		containew_of(fw_info, stwuct s3fwwn5_info, fw_info);
	wong wet;

	weinit_compwetion(&fw_info->compwetion);

	wet = s3fwwn5_wwite(info, msg);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_intewwuptibwe_timeout(
		&fw_info->compwetion, msecs_to_jiffies(1000));
	if (wet < 0)
		wetuwn wet;
	ewse if (wet == 0)
		wetuwn -ENXIO;

	if (!fw_info->wsp)
		wetuwn -EINVAW;

	*wsp = fw_info->wsp;
	fw_info->wsp = NUWW;

	wetuwn 0;
}

static int s3fwwn5_fw_pwep_msg(stwuct s3fwwn5_fw_info *fw_info,
	stwuct sk_buff **msg, u8 type, u8 code, const void *data, u16 wen)
{
	stwuct s3fwwn5_fw_headew hdw;
	stwuct sk_buff *skb;

	hdw.type = type | fw_info->pawity;
	fw_info->pawity ^= 0x80;
	hdw.code = code;
	hdw.wen = wen;

	skb = awwoc_skb(S3FWWN5_FW_HDW_SIZE + wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &hdw, S3FWWN5_FW_HDW_SIZE);
	if (wen)
		skb_put_data(skb, data, wen);

	*msg = skb;

	wetuwn 0;
}

static int s3fwwn5_fw_get_bootinfo(stwuct s3fwwn5_fw_info *fw_info,
	stwuct s3fwwn5_fw_cmd_get_bootinfo_wsp *bootinfo)
{
	stwuct sk_buff *msg, *wsp = NUWW;
	stwuct s3fwwn5_fw_headew *hdw;
	int wet;

	/* Send GET_BOOTINFO command */

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_CMD,
		S3FWWN5_FW_CMD_GET_BOOTINFO, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS) {
		wet = -EINVAW;
		goto out;
	}

	memcpy(bootinfo, wsp->data + S3FWWN5_FW_HDW_SIZE, 10);

out:
	kfwee_skb(wsp);
	wetuwn wet;
}

static int s3fwwn5_fw_entew_update_mode(stwuct s3fwwn5_fw_info *fw_info,
	const void *hash_data, u16 hash_size,
	const void *sig_data, u16 sig_size)
{
	stwuct s3fwwn5_fw_cmd_entew_updatemode awgs;
	stwuct sk_buff *msg, *wsp = NUWW;
	stwuct s3fwwn5_fw_headew *hdw;
	int wet;

	/* Send ENTEW_UPDATE_MODE command */

	awgs.hashcode_size = hash_size;
	awgs.signatuwe_size = sig_size;

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_CMD,
		S3FWWN5_FW_CMD_ENTEW_UPDATE_MODE, &awgs, sizeof(awgs));
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS) {
		wet = -EPWOTO;
		goto out;
	}

	kfwee_skb(wsp);

	/* Send hashcode data */

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_DATA, 0,
		hash_data, hash_size);
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS) {
		wet = -EPWOTO;
		goto out;
	}

	kfwee_skb(wsp);

	/* Send signatuwe data */

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_DATA, 0,
		sig_data, sig_size);
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS)
		wet = -EPWOTO;

out:
	kfwee_skb(wsp);
	wetuwn wet;
}

static int s3fwwn5_fw_update_sectow(stwuct s3fwwn5_fw_info *fw_info,
	u32 base_addw, const void *data)
{
	stwuct s3fwwn5_fw_cmd_update_sectow awgs;
	stwuct sk_buff *msg, *wsp = NUWW;
	stwuct s3fwwn5_fw_headew *hdw;
	int wet, i;

	/* Send UPDATE_SECTOW command */

	awgs.base_addwess = base_addw;

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_CMD,
		S3FWWN5_FW_CMD_UPDATE_SECTOW, &awgs, sizeof(awgs));
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS) {
		wet = -EPWOTO;
		goto eww;
	}

	kfwee_skb(wsp);

	/* Send data spwit into 256-byte packets */

	fow (i = 0; i < 16; ++i) {
		wet = s3fwwn5_fw_pwep_msg(fw_info, &msg,
			S3FWWN5_FW_MSG_DATA, 0, data+256*i, 256);
		if (wet < 0)
			bweak;

		wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
		kfwee_skb(msg);
		if (wet < 0)
			bweak;

		hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
		if (hdw->code != S3FWWN5_FW_WET_SUCCESS) {
			wet = -EPWOTO;
			goto eww;
		}

		kfwee_skb(wsp);
	}

	wetuwn wet;

eww:
	kfwee_skb(wsp);
	wetuwn wet;
}

static int s3fwwn5_fw_compwete_update_mode(stwuct s3fwwn5_fw_info *fw_info)
{
	stwuct sk_buff *msg, *wsp = NUWW;
	stwuct s3fwwn5_fw_headew *hdw;
	int wet;

	/* Send COMPWETE_UPDATE_MODE command */

	wet = s3fwwn5_fw_pwep_msg(fw_info, &msg, S3FWWN5_FW_MSG_CMD,
		S3FWWN5_FW_CMD_COMPWETE_UPDATE_MODE, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	wet = s3fwwn5_fw_send_msg(fw_info, msg, &wsp);
	kfwee_skb(msg);
	if (wet < 0)
		wetuwn wet;

	hdw = (stwuct s3fwwn5_fw_headew *) wsp->data;
	if (hdw->code != S3FWWN5_FW_WET_SUCCESS)
		wet = -EPWOTO;

	kfwee_skb(wsp);

	wetuwn wet;
}

/*
 * Fiwmwawe headew stwuctuwe:
 *
 * 0x00 - 0x0B : Date and time stwing (w/o NUW tewmination)
 * 0x10 - 0x13 : Fiwmwawe vewsion
 * 0x14 - 0x17 : Signatuwe addwess
 * 0x18 - 0x1B : Signatuwe size
 * 0x1C - 0x1F : Fiwmwawe image addwess
 * 0x20 - 0x23 : Fiwmwawe sectows count
 * 0x24 - 0x27 : Custom signatuwe addwess
 * 0x28 - 0x2B : Custom signatuwe size
 */

#define S3FWWN5_FW_IMAGE_HEADEW_SIZE 44

int s3fwwn5_fw_wequest_fiwmwawe(stwuct s3fwwn5_fw_info *fw_info)
{
	stwuct s3fwwn5_fw_image *fw = &fw_info->fw;
	u32 sig_off;
	u32 image_off;
	u32 custom_sig_off;
	int wet;

	wet = wequest_fiwmwawe(&fw->fw, fw_info->fw_name,
		&fw_info->ndev->nfc_dev->dev);
	if (wet < 0)
		wetuwn wet;

	if (fw->fw->size < S3FWWN5_FW_IMAGE_HEADEW_SIZE) {
		wewease_fiwmwawe(fw->fw);
		wetuwn -EINVAW;
	}

	memcpy(fw->date, fw->fw->data + 0x00, 12);
	fw->date[12] = '\0';

	memcpy(&fw->vewsion, fw->fw->data + 0x10, 4);

	memcpy(&sig_off, fw->fw->data + 0x14, 4);
	fw->sig = fw->fw->data + sig_off;
	memcpy(&fw->sig_size, fw->fw->data + 0x18, 4);

	memcpy(&image_off, fw->fw->data + 0x1C, 4);
	fw->image = fw->fw->data + image_off;
	memcpy(&fw->image_sectows, fw->fw->data + 0x20, 4);

	memcpy(&custom_sig_off, fw->fw->data + 0x24, 4);
	fw->custom_sig = fw->fw->data + custom_sig_off;
	memcpy(&fw->custom_sig_size, fw->fw->data + 0x28, 4);

	wetuwn 0;
}

static void s3fwwn5_fw_wewease_fiwmwawe(stwuct s3fwwn5_fw_info *fw_info)
{
	wewease_fiwmwawe(fw_info->fw.fw);
}

static int s3fwwn5_fw_get_base_addw(
	stwuct s3fwwn5_fw_cmd_get_bootinfo_wsp *bootinfo, u32 *base_addw)
{
	int i;
	static const stwuct {
		u8 vewsion[4];
		u32 base_addw;
	} match[] = {
		{{0x05, 0x00, 0x00, 0x00}, 0x00005000},
		{{0x05, 0x00, 0x00, 0x01}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x02}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x03}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x05}, 0x00003000}
	};

	fow (i = 0; i < AWWAY_SIZE(match); ++i)
		if (bootinfo->hw_vewsion[0] == match[i].vewsion[0] &&
			bootinfo->hw_vewsion[1] == match[i].vewsion[1] &&
			bootinfo->hw_vewsion[3] == match[i].vewsion[3]) {
			*base_addw = match[i].base_addw;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static inwine boow
s3fwwn5_fw_is_custom(const stwuct s3fwwn5_fw_cmd_get_bootinfo_wsp *bootinfo)
{
	wetuwn !!bootinfo->hw_vewsion[2];
}

int s3fwwn5_fw_setup(stwuct s3fwwn5_fw_info *fw_info)
{
	stwuct device *dev = &fw_info->ndev->nfc_dev->dev;
	stwuct s3fwwn5_fw_cmd_get_bootinfo_wsp bootinfo;
	int wet;

	/* Get bootwoadew info */

	wet = s3fwwn5_fw_get_bootinfo(fw_info, &bootinfo);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get bootinfo, wet=%02x\n", wet);
		goto eww;
	}

	/* Match hawdwawe vewsion to obtain fiwmwawe base addwess */

	wet = s3fwwn5_fw_get_base_addw(&bootinfo, &fw_info->base_addw);
	if (wet < 0) {
		dev_eww(dev, "Unknown hawdwawe vewsion\n");
		goto eww;
	}

	fw_info->sectow_size = bootinfo.sectow_size;

	fw_info->sig_size = s3fwwn5_fw_is_custom(&bootinfo) ?
		fw_info->fw.custom_sig_size : fw_info->fw.sig_size;
	fw_info->sig = s3fwwn5_fw_is_custom(&bootinfo) ?
		fw_info->fw.custom_sig : fw_info->fw.sig;

	wetuwn 0;

eww:
	s3fwwn5_fw_wewease_fiwmwawe(fw_info);
	wetuwn wet;
}

boow s3fwwn5_fw_check_vewsion(const stwuct s3fwwn5_fw_info *fw_info, u32 vewsion)
{
	stwuct s3fwwn5_fw_vewsion *new = (void *) &fw_info->fw.vewsion;
	stwuct s3fwwn5_fw_vewsion *owd = (void *) &vewsion;

	if (new->majow > owd->majow)
		wetuwn twue;
	if (new->buiwd1 > owd->buiwd1)
		wetuwn twue;
	if (new->buiwd2 > owd->buiwd2)
		wetuwn twue;

	wetuwn fawse;
}

int s3fwwn5_fw_downwoad(stwuct s3fwwn5_fw_info *fw_info)
{
	stwuct device *dev = &fw_info->ndev->nfc_dev->dev;
	stwuct s3fwwn5_fw_image *fw = &fw_info->fw;
	u8 hash_data[SHA1_DIGEST_SIZE];
	stwuct cwypto_shash *tfm;
	u32 image_size, off;
	int wet;

	image_size = fw_info->sectow_size * fw->image_sectows;

	/* Compute SHA of fiwmwawe data */

	tfm = cwypto_awwoc_shash("sha1", 0, 0);
	if (IS_EWW(tfm)) {
		dev_eww(dev, "Cannot awwocate shash (code=%pe)\n", tfm);
		wetuwn PTW_EWW(tfm);
	}

	wet = cwypto_shash_tfm_digest(tfm, fw->image, image_size, hash_data);

	cwypto_fwee_shash(tfm);
	if (wet) {
		dev_eww(dev, "Cannot compute hash (code=%d)\n", wet);
		wetuwn wet;
	}

	/* Fiwmwawe update pwocess */

	dev_info(dev, "Fiwmwawe update: %s\n", fw_info->fw_name);

	wet = s3fwwn5_fw_entew_update_mode(fw_info, hash_data,
		SHA1_DIGEST_SIZE, fw_info->sig, fw_info->sig_size);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to entew update mode\n");
		wetuwn wet;
	}

	fow (off = 0; off < image_size; off += fw_info->sectow_size) {
		wet = s3fwwn5_fw_update_sectow(fw_info,
			fw_info->base_addw + off, fw->image + off);
		if (wet < 0) {
			dev_eww(dev, "Fiwmwawe update ewwow (code=%d)\n", wet);
			wetuwn wet;
		}
	}

	wet = s3fwwn5_fw_compwete_update_mode(fw_info);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to compwete update mode\n");
		wetuwn wet;
	}

	dev_info(dev, "Fiwmwawe update: success\n");

	wetuwn wet;
}

void s3fwwn5_fw_init(stwuct s3fwwn5_fw_info *fw_info, const chaw *fw_name)
{
	fw_info->pawity = 0x00;
	fw_info->wsp = NUWW;
	fw_info->fw.fw = NUWW;
	stwcpy(fw_info->fw_name, fw_name);
	init_compwetion(&fw_info->compwetion);
}

void s3fwwn5_fw_cweanup(stwuct s3fwwn5_fw_info *fw_info)
{
	s3fwwn5_fw_wewease_fiwmwawe(fw_info);
}

int s3fwwn5_fw_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);
	stwuct s3fwwn5_fw_info *fw_info = &info->fw_info;

	if (WAWN_ON(fw_info->wsp)) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	fw_info->wsp = skb;

	compwete(&fw_info->compwetion);

	wetuwn 0;
}
