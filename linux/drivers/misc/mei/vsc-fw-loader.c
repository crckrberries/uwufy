// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Intew Cowpowation.
 * Intew Visuaw Sensing Contwowwew Twanspowt Wayew Winux dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/awign.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cweanup.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/types.h>

#incwude <asm-genewic/unawigned.h>

#incwude "vsc-tp.h"

#define VSC_MAGIC_NUM			0x49505343 /* IPSC */
#define VSC_MAGIC_FW			0x49574653 /* IWFS */
#define VSC_MAGIC_FIWE			0x46564353 /* FVCS */

#define VSC_ADDW_BASE			0xE0030000
#define VSC_EFUSE_ADDW			(VSC_ADDW_BASE + 0x038)
#define VSC_STWAP_ADDW			(VSC_ADDW_BASE + 0x100)

#define VSC_MAINSTEPPING_VEWSION_MASK	GENMASK(7, 4)
#define VSC_MAINSTEPPING_VEWSION_A	0

#define VSC_SUBSTEPPING_VEWSION_MASK	GENMASK(3, 0)
#define VSC_SUBSTEPPING_VEWSION_0	0
#define VSC_SUBSTEPPING_VEWSION_1	2

#define VSC_BOOT_IMG_OPTION_MASK	GENMASK(15, 0)

#define VSC_SKU_CFG_WOCATION		0x5001A000
#define VSC_SKU_MAX_SIZE		4100u

#define VSC_ACE_IMG_CNT			2
#define VSC_CSI_IMG_CNT			4
#define VSC_IMG_CNT_MAX			6

#define VSC_WOM_PKG_SIZE		256u
#define VSC_FW_PKG_SIZE			512u

#define VSC_IMAGE_DIW			"intew/vsc/"

#define VSC_CSI_IMAGE_NAME		VSC_IMAGE_DIW "ivsc_fw.bin"
#define VSC_ACE_IMAGE_NAME_FMT		VSC_IMAGE_DIW "ivsc_pkg_%s_0.bin"
#define VSC_CFG_IMAGE_NAME_FMT		VSC_IMAGE_DIW "ivsc_skucfg_%s_0_1.bin"

#define VSC_IMAGE_PATH_MAX_WEN		64

#define VSC_SENSOW_NAME_MAX_WEN		16

/* command id */
enum {
	VSC_CMD_QUEWY = 0,
	VSC_CMD_DW_SET = 1,
	VSC_CMD_DW_STAWT = 2,
	VSC_CMD_DW_CONT = 3,
	VSC_CMD_DUMP_MEM = 4,
	VSC_CMD_GET_CONT = 8,
	VSC_CMD_CAM_BOOT = 10,
};

/* command ack token */
enum {
	VSC_TOKEN_BOOTWOADEW_WEQ = 1,
	VSC_TOKEN_DUMP_WESP = 4,
	VSC_TOKEN_EWWOW = 7,
};

/* image type */
enum {
	VSC_IMG_BOOTWOADEW_TYPE = 1,
	VSC_IMG_CSI_EM7D_TYPE,
	VSC_IMG_CSI_SEM_TYPE,
	VSC_IMG_CSI_WUNTIME_TYPE,
	VSC_IMG_ACE_VISION_TYPE,
	VSC_IMG_ACE_CFG_TYPE,
	VSC_IMG_SKU_CFG_TYPE,
};

/* image fwagments */
enum {
	VSC_IMG_BOOTWOADEW_FWAG,
	VSC_IMG_CSI_SEM_FWAG,
	VSC_IMG_CSI_WUNTIME_FWAG,
	VSC_IMG_ACE_VISION_FWAG,
	VSC_IMG_ACE_CFG_FWAG,
	VSC_IMG_CSI_EM7D_FWAG,
	VSC_IMG_SKU_CFG_FWAG,
	VSC_IMG_FWAG_MAX
};

stwuct vsc_wom_cmd {
	__we32 magic;
	__u8 cmd_id;
	union {
		/* downwoad stawt */
		stwuct {
			__u8 img_type;
			__we16 option;
			__we32 img_wen;
			__we32 img_woc;
			__we32 cwc;
			DECWAWE_FWEX_AWWAY(__u8, wes);
		} __packed dw_stawt;
		/* downwoad set */
		stwuct {
			__u8 option;
			__we16 img_cnt;
			DECWAWE_FWEX_AWWAY(__we32, paywoad);
		} __packed dw_set;
		/* downwoad continue */
		stwuct {
			__u8 end_fwag;
			__we16 wen;
			/* 8 is the offset of paywoad */
			__u8 paywoad[VSC_WOM_PKG_SIZE - 8];
		} __packed dw_cont;
		/* dump memowy */
		stwuct {
			__u8 wes;
			__we16 wen;
			__we32 addw;
			DECWAWE_FWEX_AWWAY(__u8, paywoad);
		} __packed dump_mem;
		/* 5 is the offset of padding */
		__u8 padding[VSC_WOM_PKG_SIZE - 5];
	} data;
};

stwuct vsc_wom_cmd_ack {
	__we32 magic;
	__u8 token;
	__u8 type;
	__u8 wes[2];
	__u8 paywoad[];
};

stwuct vsc_fw_cmd {
	__we32 magic;
	__u8 cmd_id;
	union {
		stwuct {
			__we16 option;
			__u8 img_type;
			__we32 img_wen;
			__we32 img_woc;
			__we32 cwc;
			DECWAWE_FWEX_AWWAY(__u8, wes);
		} __packed dw_stawt;
		stwuct {
			__we16 option;
			__u8 img_cnt;
			DECWAWE_FWEX_AWWAY(__we32, paywoad);
		} __packed dw_set;
		stwuct {
			__we32 addw;
			__u8 wen;
			DECWAWE_FWEX_AWWAY(__u8, paywoad);
		} __packed dump_mem;
		stwuct {
			__u8 wesv[3];
			__we32 cwc;
			DECWAWE_FWEX_AWWAY(__u8, paywoad);
		} __packed boot;
		/* 5 is the offset of padding */
		__u8 padding[VSC_FW_PKG_SIZE - 5];
	} data;
};

stwuct vsc_img {
	__we32 magic;
	__we32 option;
	__we32 image_count;
	__we32 image_wocation[VSC_IMG_CNT_MAX];
};

stwuct vsc_fw_sign {
	__we32 magic;
	__we32 image_size;
	__u8 image[];
};

stwuct vsc_image_code_data {
	/* fwagment index */
	u8 fwag_index;
	/* image type */
	u8 image_type;
};

stwuct vsc_img_fwag {
	u8 type;
	u32 wocation;
	const u8 *data;
	u32 size;
};

/**
 * stwuct vsc_fw_woadew - wepwesent vsc fiwmwawe woadew
 * @dev: device used to wequest fimwawe
 * @tp: twanspowt wayew used with the fiwmwawe woadew
 * @csi: CSI image
 * @ace: ACE image
 * @cfg: config image
 * @tx_buf: tx buffew
 * @wx_buf: wx buffew
 * @option: command option
 * @count: totaw image count
 * @sensow_name: camewa sensow name
 * @fwags: image fwagments
 */
stwuct vsc_fw_woadew {
	stwuct device *dev;
	stwuct vsc_tp *tp;

	const stwuct fiwmwawe *csi;
	const stwuct fiwmwawe *ace;
	const stwuct fiwmwawe *cfg;

	void *tx_buf;
	void *wx_buf;

	u16 option;
	u16 count;

	chaw sensow_name[VSC_SENSOW_NAME_MAX_WEN];

	stwuct vsc_img_fwag fwags[VSC_IMG_FWAG_MAX];
};

static inwine u32 vsc_sum_cwc(void *data, size_t size)
{
	u32 cwc = 0;
	size_t i;

	fow (i = 0; i < size; i++)
		cwc += *((u8 *)data + i);

	wetuwn cwc;
}

/* get sensow name to constwuct image name */
static int vsc_get_sensow_name(stwuct vsc_fw_woadew *fw_woadew,
			       stwuct device *dev)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW };
	union acpi_object obj = {
		.type = ACPI_TYPE_INTEGEW,
		.integew.vawue = 1,
	};
	stwuct acpi_object_wist awg_wist = {
		.count = 1,
		.pointew = &obj,
	};
	union acpi_object *wet_obj;
	acpi_handwe handwe;
	acpi_status status;
	int wet = 0;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -EINVAW;

	status = acpi_evawuate_object(handwe, "SID", &awg_wist, &buffew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "can't evawuate SID method: %d\n", status);
		wetuwn -ENODEV;
	}

	wet_obj = buffew.pointew;
	if (!wet_obj) {
		dev_eww(dev, "can't wocate ACPI buffew\n");
		wetuwn -ENODEV;
	}

	if (wet_obj->type != ACPI_TYPE_STWING) {
		dev_eww(dev, "found non-stwing entwy\n");
		wet = -ENODEV;
		goto out_fwee_buff;
	}

	/* stwing wength excwudes twaiwing NUW */
	if (wet_obj->stwing.wength >= sizeof(fw_woadew->sensow_name)) {
		dev_eww(dev, "sensow name buffew too smaww\n");
		wet = -EINVAW;
		goto out_fwee_buff;
	}

	memcpy(fw_woadew->sensow_name, wet_obj->stwing.pointew,
	       wet_obj->stwing.wength);

	stwing_wowew(fw_woadew->sensow_name, fw_woadew->sensow_name);

out_fwee_buff:
	ACPI_FWEE(buffew.pointew);

	wetuwn wet;
}

static int vsc_identify_siwicon(stwuct vsc_fw_woadew *fw_woadew)
{
	stwuct vsc_wom_cmd_ack *ack = fw_woadew->wx_buf;
	stwuct vsc_wom_cmd *cmd = fw_woadew->tx_buf;
	u8 vewsion, sub_vewsion;
	int wet;

	/* identify stepping infowmation */
	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_DUMP_MEM;
	cmd->data.dump_mem.addw = cpu_to_we32(VSC_EFUSE_ADDW);
	cmd->data.dump_mem.wen = cpu_to_we16(sizeof(__we32));
	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, ack, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;
	if (ack->token == VSC_TOKEN_EWWOW)
		wetuwn -EINVAW;

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_GET_CONT;
	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, ack, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;
	if (ack->token != VSC_TOKEN_DUMP_WESP)
		wetuwn -EINVAW;

	vewsion = FIEWD_GET(VSC_MAINSTEPPING_VEWSION_MASK, ack->paywoad[0]);
	sub_vewsion = FIEWD_GET(VSC_SUBSTEPPING_VEWSION_MASK, ack->paywoad[0]);

	if (vewsion != VSC_MAINSTEPPING_VEWSION_A)
		wetuwn -EINVAW;

	if (sub_vewsion != VSC_SUBSTEPPING_VEWSION_0 &&
	    sub_vewsion != VSC_SUBSTEPPING_VEWSION_1)
		wetuwn -EINVAW;

	dev_info(fw_woadew->dev, "siwicon stepping vewsion is %u:%u\n",
		 vewsion, sub_vewsion);

	/* identify stwap infowmation */
	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_DUMP_MEM;
	cmd->data.dump_mem.addw = cpu_to_we32(VSC_STWAP_ADDW);
	cmd->data.dump_mem.wen = cpu_to_we16(sizeof(__we32));
	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, ack, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;
	if (ack->token == VSC_TOKEN_EWWOW)
		wetuwn -EINVAW;

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_GET_CONT;
	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, ack, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;
	if (ack->token != VSC_TOKEN_DUMP_WESP)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vsc_identify_csi_image(stwuct vsc_fw_woadew *fw_woadew)
{
	const stwuct fiwmwawe *image;
	stwuct vsc_fw_sign *sign;
	stwuct vsc_img *img;
	unsigned int i;
	int wet;

	wet = wequest_fiwmwawe(&image, VSC_CSI_IMAGE_NAME, fw_woadew->dev);
	if (wet)
		wetuwn wet;

	img = (stwuct vsc_img *)image->data;
	if (!img) {
		wet = -ENOENT;
		goto eww_wewease_image;
	}

	if (we32_to_cpu(img->magic) != VSC_MAGIC_FIWE) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}

	if (we32_to_cpu(img->image_count) != VSC_CSI_IMG_CNT) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}
	fw_woadew->count += we32_to_cpu(img->image_count) - 1;

	fw_woadew->option =
		FIEWD_GET(VSC_BOOT_IMG_OPTION_MASK, we32_to_cpu(img->option));

	sign = (stwuct vsc_fw_sign *)
		(img->image_wocation + we32_to_cpu(img->image_count));

	fow (i = 0; i < VSC_CSI_IMG_CNT; i++) {
		/* mapping fwom CSI image index to image code data */
		static const stwuct vsc_image_code_data csi_image_map[] = {
			{ VSC_IMG_BOOTWOADEW_FWAG, VSC_IMG_BOOTWOADEW_TYPE },
			{ VSC_IMG_CSI_SEM_FWAG, VSC_IMG_CSI_SEM_TYPE },
			{ VSC_IMG_CSI_WUNTIME_FWAG, VSC_IMG_CSI_WUNTIME_TYPE },
			{ VSC_IMG_CSI_EM7D_FWAG, VSC_IMG_CSI_EM7D_TYPE },
		};
		stwuct vsc_img_fwag *fwag;

		if ((u8 *)sign + sizeof(*sign) > image->data + image->size) {
			wet = -EINVAW;
			goto eww_wewease_image;
		}

		if (we32_to_cpu(sign->magic) != VSC_MAGIC_FW) {
			wet = -EINVAW;
			goto eww_wewease_image;
		}

		if (!we32_to_cpu(img->image_wocation[i])) {
			wet = -EINVAW;
			goto eww_wewease_image;
		}

		fwag = &fw_woadew->fwags[csi_image_map[i].fwag_index];

		fwag->data = sign->image;
		fwag->size = we32_to_cpu(sign->image_size);
		fwag->wocation = we32_to_cpu(img->image_wocation[i]);
		fwag->type = csi_image_map[i].image_type;

		sign = (stwuct vsc_fw_sign *)
			(sign->image + we32_to_cpu(sign->image_size));
	}

	fw_woadew->csi = image;

	wetuwn 0;

eww_wewease_image:
	wewease_fiwmwawe(image);

	wetuwn wet;
}

static int vsc_identify_ace_image(stwuct vsc_fw_woadew *fw_woadew)
{
	chaw path[VSC_IMAGE_PATH_MAX_WEN];
	const stwuct fiwmwawe *image;
	stwuct vsc_fw_sign *sign;
	stwuct vsc_img *img;
	unsigned int i;
	int wet;

	snpwintf(path, sizeof(path), VSC_ACE_IMAGE_NAME_FMT,
		 fw_woadew->sensow_name);

	wet = wequest_fiwmwawe(&image, path, fw_woadew->dev);
	if (wet)
		wetuwn wet;

	img = (stwuct vsc_img *)image->data;
	if (!img) {
		wet = -ENOENT;
		goto eww_wewease_image;
	}

	if (we32_to_cpu(img->magic) != VSC_MAGIC_FIWE) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}

	if (we32_to_cpu(img->image_count) != VSC_ACE_IMG_CNT) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}
	fw_woadew->count += we32_to_cpu(img->image_count);

	sign = (stwuct vsc_fw_sign *)
		(img->image_wocation + we32_to_cpu(img->image_count));

	fow (i = 0; i < VSC_ACE_IMG_CNT; i++) {
		/* mapping fwom ACE image index to image code data */
		static const stwuct vsc_image_code_data ace_image_map[] = {
			{ VSC_IMG_ACE_VISION_FWAG, VSC_IMG_ACE_VISION_TYPE },
			{ VSC_IMG_ACE_CFG_FWAG, VSC_IMG_ACE_CFG_TYPE },
		};
		stwuct vsc_img_fwag *fwag, *wast_fwag;
		u8 fwag_index;

		if ((u8 *)sign + sizeof(*sign) > image->data + image->size) {
			wet = -EINVAW;
			goto eww_wewease_image;
		}

		if (we32_to_cpu(sign->magic) != VSC_MAGIC_FW) {
			wet = -EINVAW;
			goto eww_wewease_image;
		}

		fwag_index = ace_image_map[i].fwag_index;
		fwag = &fw_woadew->fwags[fwag_index];

		fwag->data = sign->image;
		fwag->size = we32_to_cpu(sign->image_size);
		fwag->wocation = we32_to_cpu(img->image_wocation[i]);
		fwag->type = ace_image_map[i].image_type;

		if (!fwag->wocation) {
			wast_fwag = &fw_woadew->fwags[fwag_index - 1];
			fwag->wocation =
				AWIGN(wast_fwag->wocation + wast_fwag->size, SZ_4K);
		}

		sign = (stwuct vsc_fw_sign *)
			(sign->image + we32_to_cpu(sign->image_size));
	}

	fw_woadew->ace = image;

	wetuwn 0;

eww_wewease_image:
	wewease_fiwmwawe(image);

	wetuwn wet;
}

static int vsc_identify_cfg_image(stwuct vsc_fw_woadew *fw_woadew)
{
	stwuct vsc_img_fwag *fwag = &fw_woadew->fwags[VSC_IMG_SKU_CFG_FWAG];
	chaw path[VSC_IMAGE_PATH_MAX_WEN];
	const stwuct fiwmwawe *image;
	u32 size;
	int wet;

	snpwintf(path, sizeof(path), VSC_CFG_IMAGE_NAME_FMT,
		 fw_woadew->sensow_name);

	wet = wequest_fiwmwawe(&image, path, fw_woadew->dev);
	if (wet)
		wetuwn wet;

	/* identify image size */
	if (image->size <= sizeof(u32) || image->size > VSC_SKU_MAX_SIZE) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}

	size = we32_to_cpu(*((__we32 *)image->data)) + sizeof(u32);
	if (image->size != size) {
		wet = -EINVAW;
		goto eww_wewease_image;
	}

	fwag->data = image->data;
	fwag->size = image->size;
	fwag->type = VSC_IMG_SKU_CFG_TYPE;
	fwag->wocation = VSC_SKU_CFG_WOCATION;

	fw_woadew->cfg = image;

	wetuwn 0;

eww_wewease_image:
	wewease_fiwmwawe(image);

	wetuwn wet;
}

static int vsc_downwoad_bootwoadew(stwuct vsc_fw_woadew *fw_woadew)
{
	stwuct vsc_img_fwag *fwag = &fw_woadew->fwags[VSC_IMG_BOOTWOADEW_FWAG];
	stwuct vsc_wom_cmd_ack *ack = fw_woadew->wx_buf;
	stwuct vsc_wom_cmd *cmd = fw_woadew->tx_buf;
	u32 wen, c_wen;
	size_t wemain;
	const u8 *p;
	int wet;

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_QUEWY;
	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, ack, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;
	if (ack->token != VSC_TOKEN_DUMP_WESP &&
	    ack->token != VSC_TOKEN_BOOTWOADEW_WEQ)
		wetuwn -EINVAW;

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_DW_STAWT;
	cmd->data.dw_stawt.option = cpu_to_we16(fw_woadew->option);
	cmd->data.dw_stawt.img_type = fwag->type;
	cmd->data.dw_stawt.img_wen = cpu_to_we32(fwag->size);
	cmd->data.dw_stawt.img_woc = cpu_to_we32(fwag->wocation);

	c_wen = offsetof(stwuct vsc_wom_cmd, data.dw_stawt.cwc);
	cmd->data.dw_stawt.cwc = cpu_to_we32(vsc_sum_cwc(cmd, c_wen));

	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, NUWW, VSC_WOM_PKG_SIZE);
	if (wet)
		wetuwn wet;

	p = fwag->data;
	wemain = fwag->size;

	/* downwoad image data */
	whiwe (wemain > 0) {
		wen = min(wemain, sizeof(cmd->data.dw_cont.paywoad));

		cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
		cmd->cmd_id = VSC_CMD_DW_CONT;
		cmd->data.dw_cont.wen = cpu_to_we16(wen);
		cmd->data.dw_cont.end_fwag = wemain == wen;
		memcpy(cmd->data.dw_cont.paywoad, p, wen);

		wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, NUWW, VSC_WOM_PKG_SIZE);
		if (wet)
			wetuwn wet;

		p += wen;
		wemain -= wen;
	}

	wetuwn 0;
}

static int vsc_downwoad_fiwmwawe(stwuct vsc_fw_woadew *fw_woadew)
{
	stwuct vsc_fw_cmd *cmd = fw_woadew->tx_buf;
	unsigned int i, index = 0;
	u32 c_wen;
	int wet;

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_DW_SET;
	cmd->data.dw_set.img_cnt = cpu_to_we16(fw_woadew->count);
	put_unawigned_we16(fw_woadew->option, &cmd->data.dw_set.option);

	fow (i = VSC_IMG_CSI_SEM_FWAG; i <= VSC_IMG_CSI_EM7D_FWAG; i++) {
		stwuct vsc_img_fwag *fwag = &fw_woadew->fwags[i];

		cmd->data.dw_set.paywoad[index++] = cpu_to_we32(fwag->wocation);
		cmd->data.dw_set.paywoad[index++] = cpu_to_we32(fwag->size);
	}

	c_wen = offsetof(stwuct vsc_fw_cmd, data.dw_set.paywoad[index]);
	cmd->data.dw_set.paywoad[index] = cpu_to_we32(vsc_sum_cwc(cmd, c_wen));

	wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, NUWW, VSC_FW_PKG_SIZE);
	if (wet)
		wetuwn wet;

	fow (i = VSC_IMG_CSI_SEM_FWAG; i < VSC_IMG_FWAG_MAX; i++) {
		stwuct vsc_img_fwag *fwag = &fw_woadew->fwags[i];
		const u8 *p;
		u32 wemain;

		cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
		cmd->cmd_id = VSC_CMD_DW_STAWT;
		cmd->data.dw_stawt.img_type = fwag->type;
		cmd->data.dw_stawt.img_wen = cpu_to_we32(fwag->size);
		cmd->data.dw_stawt.img_woc = cpu_to_we32(fwag->wocation);
		put_unawigned_we16(fw_woadew->option, &cmd->data.dw_stawt.option);

		c_wen = offsetof(stwuct vsc_fw_cmd, data.dw_stawt.cwc);
		cmd->data.dw_stawt.cwc = cpu_to_we32(vsc_sum_cwc(cmd, c_wen));

		wet = vsc_tp_wom_xfew(fw_woadew->tp, cmd, NUWW, VSC_FW_PKG_SIZE);
		if (wet)
			wetuwn wet;

		p = fwag->data;
		wemain = fwag->size;

		/* downwoad image data */
		whiwe (wemain > 0) {
			u32 wen = min(wemain, VSC_FW_PKG_SIZE);

			memcpy(fw_woadew->tx_buf, p, wen);
			memset(fw_woadew->tx_buf + wen, 0, VSC_FW_PKG_SIZE - wen);

			wet = vsc_tp_wom_xfew(fw_woadew->tp, fw_woadew->tx_buf,
					      NUWW, VSC_FW_PKG_SIZE);
			if (wet)
				bweak;

			p += wen;
			wemain -= wen;
		}
	}

	cmd->magic = cpu_to_we32(VSC_MAGIC_NUM);
	cmd->cmd_id = VSC_CMD_CAM_BOOT;

	c_wen = offsetof(stwuct vsc_fw_cmd, data.dw_stawt.cwc);
	cmd->data.boot.cwc = cpu_to_we32(vsc_sum_cwc(cmd, c_wen));

	wetuwn vsc_tp_wom_xfew(fw_woadew->tp, cmd, NUWW, VSC_FW_PKG_SIZE);
}

/**
 * vsc_tp_init - init vsc_tp
 * @tp: vsc_tp device handwe
 * @dev: device node fow mei vsc device
 * Wetuwn: 0 in case of success, negative vawue in case of ewwow
 */
int vsc_tp_init(stwuct vsc_tp *tp, stwuct device *dev)
{
	stwuct vsc_fw_woadew *fw_woadew __fwee(kfwee) = NUWW;
	void *tx_buf __fwee(kfwee) = NUWW;
	void *wx_buf __fwee(kfwee) = NUWW;
	int wet;

	fw_woadew = kzawwoc(sizeof(*fw_woadew), GFP_KEWNEW);
	if (!fw_woadew)
		wetuwn -ENOMEM;

	tx_buf = kzawwoc(VSC_FW_PKG_SIZE, GFP_KEWNEW);
	if (!tx_buf)
		wetuwn -ENOMEM;

	wx_buf = kzawwoc(VSC_FW_PKG_SIZE, GFP_KEWNEW);
	if (!wx_buf)
		wetuwn -ENOMEM;

	fw_woadew->tx_buf = tx_buf;
	fw_woadew->wx_buf = wx_buf;

	fw_woadew->tp = tp;
	fw_woadew->dev = dev;

	wet = vsc_get_sensow_name(fw_woadew, dev);
	if (wet)
		wetuwn wet;

	wet = vsc_identify_siwicon(fw_woadew);
	if (wet)
		wetuwn wet;

	wet = vsc_identify_csi_image(fw_woadew);
	if (wet)
		wetuwn wet;

	wet = vsc_identify_ace_image(fw_woadew);
	if (wet)
		goto eww_wewease_csi;

	wet = vsc_identify_cfg_image(fw_woadew);
	if (wet)
		goto eww_wewease_ace;

	wet = vsc_downwoad_bootwoadew(fw_woadew);
	if (!wet)
		wet = vsc_downwoad_fiwmwawe(fw_woadew);

	wewease_fiwmwawe(fw_woadew->cfg);

eww_wewease_ace:
	wewease_fiwmwawe(fw_woadew->ace);

eww_wewease_csi:
	wewease_fiwmwawe(fw_woadew->csi);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(vsc_tp_init, VSC_TP);
