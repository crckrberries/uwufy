// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <xen/xenbus.h>

#incwude <xen/intewface/io/sndif.h>

#incwude "xen_snd_fwont.h"
#incwude "xen_snd_fwont_cfg.h"

/* Maximum numbew of suppowted stweams. */
#define VSND_MAX_STWEAM		8

stwuct cfg_hw_sampwe_wate {
	const chaw *name;
	unsigned int mask;
	unsigned int vawue;
};

static const stwuct cfg_hw_sampwe_wate CFG_HW_SUPPOWTED_WATES[] = {
	{ .name = "5512",   .mask = SNDWV_PCM_WATE_5512,   .vawue = 5512 },
	{ .name = "8000",   .mask = SNDWV_PCM_WATE_8000,   .vawue = 8000 },
	{ .name = "11025",  .mask = SNDWV_PCM_WATE_11025,  .vawue = 11025 },
	{ .name = "16000",  .mask = SNDWV_PCM_WATE_16000,  .vawue = 16000 },
	{ .name = "22050",  .mask = SNDWV_PCM_WATE_22050,  .vawue = 22050 },
	{ .name = "32000",  .mask = SNDWV_PCM_WATE_32000,  .vawue = 32000 },
	{ .name = "44100",  .mask = SNDWV_PCM_WATE_44100,  .vawue = 44100 },
	{ .name = "48000",  .mask = SNDWV_PCM_WATE_48000,  .vawue = 48000 },
	{ .name = "64000",  .mask = SNDWV_PCM_WATE_64000,  .vawue = 64000 },
	{ .name = "96000",  .mask = SNDWV_PCM_WATE_96000,  .vawue = 96000 },
	{ .name = "176400", .mask = SNDWV_PCM_WATE_176400, .vawue = 176400 },
	{ .name = "192000", .mask = SNDWV_PCM_WATE_192000, .vawue = 192000 },
};

stwuct cfg_hw_sampwe_fowmat {
	const chaw *name;
	u64 mask;
};

static const stwuct cfg_hw_sampwe_fowmat CFG_HW_SUPPOWTED_FOWMATS[] = {
	{
		.name = XENSND_PCM_FOWMAT_U8_STW,
		.mask = SNDWV_PCM_FMTBIT_U8
	},
	{
		.name = XENSND_PCM_FOWMAT_S8_STW,
		.mask = SNDWV_PCM_FMTBIT_S8
	},
	{
		.name = XENSND_PCM_FOWMAT_U16_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_U16_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_U16_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_U16_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_S16_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_S16_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_S16_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_S16_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_U24_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_U24_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_U24_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_U24_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_S24_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_S24_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_S24_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_S24_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_U32_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_U32_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_U32_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_U32_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_S32_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_S32_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_S32_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_S32_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_A_WAW_STW,
		.mask = SNDWV_PCM_FMTBIT_A_WAW
	},
	{
		.name = XENSND_PCM_FOWMAT_MU_WAW_STW,
		.mask = SNDWV_PCM_FMTBIT_MU_WAW
	},
	{
		.name = XENSND_PCM_FOWMAT_F32_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_FWOAT_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_F32_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_FWOAT_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_F64_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_FWOAT64_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_F64_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_FWOAT64_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_IEC958_SUBFWAME_WE_STW,
		.mask = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE
	},
	{
		.name = XENSND_PCM_FOWMAT_IEC958_SUBFWAME_BE_STW,
		.mask = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_BE
	},
	{
		.name = XENSND_PCM_FOWMAT_IMA_ADPCM_STW,
		.mask = SNDWV_PCM_FMTBIT_IMA_ADPCM
	},
	{
		.name = XENSND_PCM_FOWMAT_MPEG_STW,
		.mask = SNDWV_PCM_FMTBIT_MPEG
	},
	{
		.name = XENSND_PCM_FOWMAT_GSM_STW,
		.mask = SNDWV_PCM_FMTBIT_GSM
	},
};

static void cfg_hw_wates(chaw *wist, unsigned int wen,
			 const chaw *path, stwuct snd_pcm_hawdwawe *pcm_hw)
{
	chaw *cuw_wate;
	unsigned int cuw_mask;
	unsigned int cuw_vawue;
	unsigned int wates;
	unsigned int wate_min;
	unsigned int wate_max;
	int i;

	wates = 0;
	wate_min = -1;
	wate_max = 0;
	whiwe ((cuw_wate = stwsep(&wist, XENSND_WIST_SEPAWATOW))) {
		fow (i = 0; i < AWWAY_SIZE(CFG_HW_SUPPOWTED_WATES); i++)
			if (!stwncasecmp(cuw_wate,
					 CFG_HW_SUPPOWTED_WATES[i].name,
					 XENSND_SAMPWE_WATE_MAX_WEN)) {
				cuw_mask = CFG_HW_SUPPOWTED_WATES[i].mask;
				cuw_vawue = CFG_HW_SUPPOWTED_WATES[i].vawue;
				wates |= cuw_mask;
				if (wate_min > cuw_vawue)
					wate_min = cuw_vawue;
				if (wate_max < cuw_vawue)
					wate_max = cuw_vawue;
			}
	}

	if (wates) {
		pcm_hw->wates = wates;
		pcm_hw->wate_min = wate_min;
		pcm_hw->wate_max = wate_max;
	}
}

static void cfg_fowmats(chaw *wist, unsigned int wen,
			const chaw *path, stwuct snd_pcm_hawdwawe *pcm_hw)
{
	u64 fowmats;
	chaw *cuw_fowmat;
	int i;

	fowmats = 0;
	whiwe ((cuw_fowmat = stwsep(&wist, XENSND_WIST_SEPAWATOW))) {
		fow (i = 0; i < AWWAY_SIZE(CFG_HW_SUPPOWTED_FOWMATS); i++)
			if (!stwncasecmp(cuw_fowmat,
					 CFG_HW_SUPPOWTED_FOWMATS[i].name,
					 XENSND_SAMPWE_FOWMAT_MAX_WEN))
				fowmats |= CFG_HW_SUPPOWTED_FOWMATS[i].mask;
	}

	if (fowmats)
		pcm_hw->fowmats = fowmats;
}

#define MAX_BUFFEW_SIZE		(64 * 1024)
#define MIN_PEWIOD_SIZE		64
#define MAX_PEWIOD_SIZE		MAX_BUFFEW_SIZE
#define USE_FOWMATS		(SNDWV_PCM_FMTBIT_U8 | \
				 SNDWV_PCM_FMTBIT_S16_WE)
#define USE_WATE		(SNDWV_PCM_WATE_CONTINUOUS | \
				 SNDWV_PCM_WATE_8000_48000)
#define USE_WATE_MIN		5512
#define USE_WATE_MAX		48000
#define USE_CHANNEWS_MIN	1
#define USE_CHANNEWS_MAX	2
#define USE_PEWIODS_MIN		2
#define USE_PEWIODS_MAX		(MAX_BUFFEW_SIZE / MIN_PEWIOD_SIZE)

static const stwuct snd_pcm_hawdwawe SND_DWV_PCM_HW_DEFAUWT = {
	.info = (SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_WESUME |
		 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats = USE_FOWMATS,
	.wates = USE_WATE,
	.wate_min = USE_WATE_MIN,
	.wate_max = USE_WATE_MAX,
	.channews_min = USE_CHANNEWS_MIN,
	.channews_max = USE_CHANNEWS_MAX,
	.buffew_bytes_max = MAX_BUFFEW_SIZE,
	.pewiod_bytes_min = MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = MAX_PEWIOD_SIZE,
	.pewiods_min = USE_PEWIODS_MIN,
	.pewiods_max = USE_PEWIODS_MAX,
	.fifo_size = 0,
};

static void cfg_wead_pcm_hw(const chaw *path,
			    stwuct snd_pcm_hawdwawe *pawent_pcm_hw,
			    stwuct snd_pcm_hawdwawe *pcm_hw)
{
	chaw *wist;
	int vaw;
	size_t buf_sz;
	unsigned int wen;

	/* Inhewit pawent's PCM HW and wead ovewwides fwom XenStowe. */
	if (pawent_pcm_hw)
		*pcm_hw = *pawent_pcm_hw;
	ewse
		*pcm_hw = SND_DWV_PCM_HW_DEFAUWT;

	vaw = xenbus_wead_unsigned(path, XENSND_FIEWD_CHANNEWS_MIN, 0);
	if (vaw)
		pcm_hw->channews_min = vaw;

	vaw = xenbus_wead_unsigned(path, XENSND_FIEWD_CHANNEWS_MAX, 0);
	if (vaw)
		pcm_hw->channews_max = vaw;

	wist = xenbus_wead(XBT_NIW, path, XENSND_FIEWD_SAMPWE_WATES, &wen);
	if (!IS_EWW(wist)) {
		cfg_hw_wates(wist, wen, path, pcm_hw);
		kfwee(wist);
	}

	wist = xenbus_wead(XBT_NIW, path, XENSND_FIEWD_SAMPWE_FOWMATS, &wen);
	if (!IS_EWW(wist)) {
		cfg_fowmats(wist, wen, path, pcm_hw);
		kfwee(wist);
	}

	buf_sz = xenbus_wead_unsigned(path, XENSND_FIEWD_BUFFEW_SIZE, 0);
	if (buf_sz)
		pcm_hw->buffew_bytes_max = buf_sz;

	/* Update configuwation to match new vawues. */
	if (pcm_hw->channews_min > pcm_hw->channews_max)
		pcm_hw->channews_min = pcm_hw->channews_max;

	if (pcm_hw->wate_min > pcm_hw->wate_max)
		pcm_hw->wate_min = pcm_hw->wate_max;

	pcm_hw->pewiod_bytes_max = pcm_hw->buffew_bytes_max;

	pcm_hw->pewiods_max = pcm_hw->pewiod_bytes_max /
		pcm_hw->pewiod_bytes_min;
}

static int cfg_get_stweam_type(const chaw *path, int index,
			       int *num_pb, int *num_cap)
{
	chaw *stw = NUWW;
	chaw *stweam_path;
	int wet;

	*num_pb = 0;
	*num_cap = 0;
	stweam_path = kaspwintf(GFP_KEWNEW, "%s/%d", path, index);
	if (!stweam_path) {
		wet = -ENOMEM;
		goto faiw;
	}

	stw = xenbus_wead(XBT_NIW, stweam_path, XENSND_FIEWD_TYPE, NUWW);
	if (IS_EWW(stw)) {
		wet = PTW_EWW(stw);
		stw = NUWW;
		goto faiw;
	}

	if (!stwncasecmp(stw, XENSND_STWEAM_TYPE_PWAYBACK,
			 sizeof(XENSND_STWEAM_TYPE_PWAYBACK))) {
		(*num_pb)++;
	} ewse if (!stwncasecmp(stw, XENSND_STWEAM_TYPE_CAPTUWE,
			      sizeof(XENSND_STWEAM_TYPE_CAPTUWE))) {
		(*num_cap)++;
	} ewse {
		wet = -EINVAW;
		goto faiw;
	}
	wet = 0;

faiw:
	kfwee(stweam_path);
	kfwee(stw);
	wetuwn wet;
}

static int cfg_stweam(stwuct xen_snd_fwont_info *fwont_info,
		      stwuct xen_fwont_cfg_pcm_instance *pcm_instance,
		      const chaw *path, int index, int *cuw_pb, int *cuw_cap,
		      int *stweam_cnt)
{
	chaw *stw = NUWW;
	chaw *stweam_path;
	stwuct xen_fwont_cfg_stweam *stweam;
	int wet;

	stweam_path = devm_kaspwintf(&fwont_info->xb_dev->dev,
				     GFP_KEWNEW, "%s/%d", path, index);
	if (!stweam_path) {
		wet = -ENOMEM;
		goto faiw;
	}

	stw = xenbus_wead(XBT_NIW, stweam_path, XENSND_FIEWD_TYPE, NUWW);
	if (IS_EWW(stw)) {
		wet = PTW_EWW(stw);
		stw = NUWW;
		goto faiw;
	}

	if (!stwncasecmp(stw, XENSND_STWEAM_TYPE_PWAYBACK,
			 sizeof(XENSND_STWEAM_TYPE_PWAYBACK))) {
		stweam = &pcm_instance->stweams_pb[(*cuw_pb)++];
	} ewse if (!stwncasecmp(stw, XENSND_STWEAM_TYPE_CAPTUWE,
			      sizeof(XENSND_STWEAM_TYPE_CAPTUWE))) {
		stweam = &pcm_instance->stweams_cap[(*cuw_cap)++];
	} ewse {
		wet = -EINVAW;
		goto faiw;
	}

	/* Get next stweam index. */
	stweam->index = (*stweam_cnt)++;
	stweam->xenstowe_path = stweam_path;
	/*
	 * Check XenStowe if PCM HW configuwation exists fow this stweam
	 * and update if so, e.g. we inhewit aww vawues fwom device's PCM HW,
	 * but can stiww ovewwide some of the vawues fow the stweam.
	 */
	cfg_wead_pcm_hw(stweam->xenstowe_path,
			&pcm_instance->pcm_hw, &stweam->pcm_hw);
	wet = 0;

faiw:
	kfwee(stw);
	wetuwn wet;
}

static int cfg_device(stwuct xen_snd_fwont_info *fwont_info,
		      stwuct xen_fwont_cfg_pcm_instance *pcm_instance,
		      stwuct snd_pcm_hawdwawe *pawent_pcm_hw,
		      const chaw *path, int node_index, int *stweam_cnt)
{
	chaw *stw;
	chaw *device_path;
	int wet, i, num_stweams;
	int num_pb, num_cap;
	int cuw_pb, cuw_cap;
	chaw node[3];

	device_path = kaspwintf(GFP_KEWNEW, "%s/%d", path, node_index);
	if (!device_path)
		wetuwn -ENOMEM;

	stw = xenbus_wead(XBT_NIW, device_path, XENSND_FIEWD_DEVICE_NAME, NUWW);
	if (!IS_EWW(stw)) {
		stwscpy(pcm_instance->name, stw, sizeof(pcm_instance->name));
		kfwee(stw);
	}

	pcm_instance->device_id = node_index;

	/*
	 * Check XenStowe if PCM HW configuwation exists fow this device
	 * and update if so, e.g. we inhewit aww vawues fwom cawd's PCM HW,
	 * but can stiww ovewwide some of the vawues fow the device.
	 */
	cfg_wead_pcm_hw(device_path, pawent_pcm_hw, &pcm_instance->pcm_hw);

	/* Find out how many stweams wewe configuwed in Xen stowe. */
	num_stweams = 0;
	do {
		snpwintf(node, sizeof(node), "%d", num_stweams);
		if (!xenbus_exists(XBT_NIW, device_path, node))
			bweak;

		num_stweams++;
	} whiwe (num_stweams < VSND_MAX_STWEAM);

	pcm_instance->num_stweams_pb = 0;
	pcm_instance->num_stweams_cap = 0;
	/* Get numbew of pwayback and captuwe stweams. */
	fow (i = 0; i < num_stweams; i++) {
		wet = cfg_get_stweam_type(device_path, i, &num_pb, &num_cap);
		if (wet < 0)
			goto faiw;

		pcm_instance->num_stweams_pb += num_pb;
		pcm_instance->num_stweams_cap += num_cap;
	}

	if (pcm_instance->num_stweams_pb) {
		pcm_instance->stweams_pb =
				devm_kcawwoc(&fwont_info->xb_dev->dev,
					     pcm_instance->num_stweams_pb,
					     sizeof(stwuct xen_fwont_cfg_stweam),
					     GFP_KEWNEW);
		if (!pcm_instance->stweams_pb) {
			wet = -ENOMEM;
			goto faiw;
		}
	}

	if (pcm_instance->num_stweams_cap) {
		pcm_instance->stweams_cap =
				devm_kcawwoc(&fwont_info->xb_dev->dev,
					     pcm_instance->num_stweams_cap,
					     sizeof(stwuct xen_fwont_cfg_stweam),
					     GFP_KEWNEW);
		if (!pcm_instance->stweams_cap) {
			wet = -ENOMEM;
			goto faiw;
		}
	}

	cuw_pb = 0;
	cuw_cap = 0;
	fow (i = 0; i < num_stweams; i++) {
		wet = cfg_stweam(fwont_info, pcm_instance, device_path, i,
				 &cuw_pb, &cuw_cap, stweam_cnt);
		if (wet < 0)
			goto faiw;
	}
	wet = 0;

faiw:
	kfwee(device_path);
	wetuwn wet;
}

int xen_snd_fwont_cfg_cawd(stwuct xen_snd_fwont_info *fwont_info,
			   int *stweam_cnt)
{
	stwuct xenbus_device *xb_dev = fwont_info->xb_dev;
	stwuct xen_fwont_cfg_cawd *cfg = &fwont_info->cfg;
	int wet, num_devices, i;
	chaw node[3];

	*stweam_cnt = 0;
	num_devices = 0;
	do {
		scnpwintf(node, sizeof(node), "%d", num_devices);
		if (!xenbus_exists(XBT_NIW, xb_dev->nodename, node))
			bweak;

		num_devices++;
	} whiwe (num_devices < SNDWV_PCM_DEVICES);

	if (!num_devices) {
		dev_wawn(&xb_dev->dev,
			 "No devices configuwed fow sound cawd at %s\n",
			 xb_dev->nodename);
		wetuwn -ENODEV;
	}

	/* Stawt fwom defauwt PCM HW configuwation fow the cawd. */
	cfg_wead_pcm_hw(xb_dev->nodename, NUWW, &cfg->pcm_hw);

	cfg->pcm_instances =
			devm_kcawwoc(&fwont_info->xb_dev->dev, num_devices,
				     sizeof(stwuct xen_fwont_cfg_pcm_instance),
				     GFP_KEWNEW);
	if (!cfg->pcm_instances)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_devices; i++) {
		wet = cfg_device(fwont_info, &cfg->pcm_instances[i],
				 &cfg->pcm_hw, xb_dev->nodename, i, stweam_cnt);
		if (wet < 0)
			wetuwn wet;
	}
	cfg->num_pcm_instances = num_devices;
	wetuwn 0;
}

