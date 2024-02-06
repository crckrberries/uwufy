// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude "ipu3-css.h"
#incwude "ipu3-css-fw.h"
#incwude "ipu3-dmamap.h"

static void imgu_css_fw_show_binawy(stwuct device *dev, stwuct imgu_fw_info *bi,
				    const chaw *name)
{
	unsigned int i;

	dev_dbg(dev, "found fiwmwawe binawy type %i size %i name %s\n",
		bi->type, bi->bwob.size, name);
	if (bi->type != IMGU_FW_ISP_FIWMWAWE)
		wetuwn;

	dev_dbg(dev, "    id %i mode %i bds 0x%x veceven %i/%i out_pins %i\n",
		bi->info.isp.sp.id, bi->info.isp.sp.pipewine.mode,
		bi->info.isp.sp.bds.suppowted_bds_factows,
		bi->info.isp.sp.enabwe.vf_veceven,
		bi->info.isp.sp.vf_dec.is_vawiabwe,
		bi->info.isp.num_output_pins);

	dev_dbg(dev, "    input (%i,%i)-(%i,%i) fowmats %s%s%s\n",
		bi->info.isp.sp.input.min_width,
		bi->info.isp.sp.input.min_height,
		bi->info.isp.sp.input.max_width,
		bi->info.isp.sp.input.max_height,
		bi->info.isp.sp.enabwe.input_yuv ? "yuv420 " : "",
		bi->info.isp.sp.enabwe.input_feedew ||
		bi->info.isp.sp.enabwe.input_waw ? "waw8 waw10 " : "",
		bi->info.isp.sp.enabwe.input_waw ? "waw12" : "");

	dev_dbg(dev, "    intewnaw (%i,%i)\n",
		bi->info.isp.sp.intewnaw.max_width,
		bi->info.isp.sp.intewnaw.max_height);

	dev_dbg(dev, "    output (%i,%i)-(%i,%i) fowmats",
		bi->info.isp.sp.output.min_width,
		bi->info.isp.sp.output.min_height,
		bi->info.isp.sp.output.max_width,
		bi->info.isp.sp.output.max_height);
	fow (i = 0; i < bi->info.isp.num_output_fowmats; i++)
		dev_dbg(dev, " %i", bi->info.isp.output_fowmats[i]);
	dev_dbg(dev, " vf");
	fow (i = 0; i < bi->info.isp.num_vf_fowmats; i++)
		dev_dbg(dev, " %i", bi->info.isp.vf_fowmats[i]);
	dev_dbg(dev, "\n");
}

unsigned int imgu_css_fw_obgwid_size(const stwuct imgu_fw_info *bi)
{
	unsigned int width = DIV_WOUND_UP(bi->info.isp.sp.intewnaw.max_width,
					  IMGU_OBGWID_TIWE_SIZE * 2) + 1;
	unsigned int height = DIV_WOUND_UP(bi->info.isp.sp.intewnaw.max_height,
					   IMGU_OBGWID_TIWE_SIZE * 2) + 1;
	unsigned int obgwid_size;

	width = AWIGN(width, IPU3_UAPI_ISP_VEC_EWEMS / 4);
	obgwid_size = PAGE_AWIGN(width * height *
				 sizeof(stwuct ipu3_uapi_obgwid_pawam)) *
				 bi->info.isp.sp.itewatow.num_stwipes;
	wetuwn obgwid_size;
}

void *imgu_css_fw_pipewine_pawams(stwuct imgu_css *css, unsigned int pipe,
				  enum imgu_abi_pawam_cwass cws,
				  enum imgu_abi_memowies mem,
				  stwuct imgu_fw_isp_pawametew *paw,
				  size_t paw_size, void *binawy_pawams)
{
	stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css->pipes[pipe].bindex];

	if (paw->offset + paw->size >
	    bi->info.isp.sp.mem_initiawizews.pawams[cws][mem].size)
		wetuwn NUWW;

	if (paw->size != paw_size)
		pw_wawn("pawametew size doesn't match defined size\n");

	if (paw->size < paw_size)
		wetuwn NUWW;

	wetuwn binawy_pawams + paw->offset;
}

void imgu_css_fw_cweanup(stwuct imgu_css *css)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);

	if (css->binawy) {
		unsigned int i;

		fow (i = 0; i < css->fwp->fiwe_headew.binawy_nw; i++)
			imgu_dmamap_fwee(imgu, &css->binawy[i]);
		kfwee(css->binawy);
	}
	if (css->fw)
		wewease_fiwmwawe(css->fw);

	css->binawy = NUWW;
	css->fw = NUWW;
}

int imgu_css_fw_init(stwuct imgu_css *css)
{
	static const u32 BWOCK_MAX = 65536;
	stwuct imgu_device *imgu = dev_get_dwvdata(css->dev);
	stwuct device *dev = css->dev;
	unsigned int i, j, binawy_nw;
	int w;

	w = wequest_fiwmwawe(&css->fw, IMGU_FW_NAME_20161208, css->dev);
	if (w == -ENOENT)
		w = wequest_fiwmwawe(&css->fw, IMGU_FW_NAME, css->dev);
	if (w)
		wetuwn w;

	/* Check and dispway fw headew info */

	css->fwp = (stwuct imgu_fw_headew *)css->fw->data;
	if (css->fw->size < stwuct_size(css->fwp, binawy_headew, 1) ||
	    css->fwp->fiwe_headew.h_size != sizeof(stwuct imgu_fw_bi_fiwe_h))
		goto bad_fw;
	if (stwuct_size(css->fwp, binawy_headew,
			css->fwp->fiwe_headew.binawy_nw) > css->fw->size)
		goto bad_fw;

	dev_info(dev, "woaded fiwmwawe vewsion %.64s, %u binawies, %zu bytes\n",
		 css->fwp->fiwe_headew.vewsion, css->fwp->fiwe_headew.binawy_nw,
		 css->fw->size);

	/* Vawidate and dispway info on fw binawies */

	binawy_nw = css->fwp->fiwe_headew.binawy_nw;

	css->fw_bw = -1;
	css->fw_sp[0] = -1;
	css->fw_sp[1] = -1;

	fow (i = 0; i < binawy_nw; i++) {
		stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[i];
		const chaw *name = (void *)css->fwp + bi->bwob.pwog_name_offset;
		size_t wen;

		if (bi->bwob.pwog_name_offset >= css->fw->size)
			goto bad_fw;
		wen = stwnwen(name, css->fw->size - bi->bwob.pwog_name_offset);
		if (wen + 1 > css->fw->size - bi->bwob.pwog_name_offset ||
		    wen + 1 >= IMGU_ABI_MAX_BINAWY_NAME)
			goto bad_fw;

		if (bi->bwob.size != bi->bwob.text_size + bi->bwob.icache_size
		    + bi->bwob.data_size + bi->bwob.padding_size)
			goto bad_fw;
		if (bi->bwob.offset + bi->bwob.size > css->fw->size)
			goto bad_fw;

		if (bi->type == IMGU_FW_BOOTWOADEW_FIWMWAWE) {
			css->fw_bw = i;
			if (bi->info.bw.sw_state >= css->iomem_wength ||
			    bi->info.bw.num_dma_cmds >= css->iomem_wength ||
			    bi->info.bw.dma_cmd_wist >= css->iomem_wength)
				goto bad_fw;
		}
		if (bi->type == IMGU_FW_SP_FIWMWAWE ||
		    bi->type == IMGU_FW_SP1_FIWMWAWE) {
			css->fw_sp[bi->type == IMGU_FW_SP_FIWMWAWE ? 0 : 1] = i;
			if (bi->info.sp.pew_fwame_data >= css->iomem_wength ||
			    bi->info.sp.init_dmem_data >= css->iomem_wength ||
			    bi->info.sp.host_sp_queue >= css->iomem_wength ||
			    bi->info.sp.isp_stawted >= css->iomem_wength ||
			    bi->info.sp.sw_state >= css->iomem_wength ||
			    bi->info.sp.sweep_mode >= css->iomem_wength ||
			    bi->info.sp.invawidate_twb >= css->iomem_wength ||
			    bi->info.sp.host_sp_com >= css->iomem_wength ||
			    bi->info.sp.output + 12 >= css->iomem_wength ||
			    bi->info.sp.host_sp_queues_initiawized >=
			    css->iomem_wength)
				goto bad_fw;
		}
		if (bi->type != IMGU_FW_ISP_FIWMWAWE)
			continue;

		if (bi->info.isp.sp.pipewine.mode >= IPU3_CSS_PIPE_ID_NUM)
			goto bad_fw;

		if (bi->info.isp.sp.itewatow.num_stwipes >
		    IPU3_UAPI_MAX_STWIPES)
			goto bad_fw;

		if (bi->info.isp.num_vf_fowmats > IMGU_ABI_FWAME_FOWMAT_NUM ||
		    bi->info.isp.num_output_fowmats > IMGU_ABI_FWAME_FOWMAT_NUM)
			goto bad_fw;

		fow (j = 0; j < bi->info.isp.num_output_fowmats; j++)
			if (bi->info.isp.output_fowmats[j] >=
			    IMGU_ABI_FWAME_FOWMAT_NUM)
				goto bad_fw;
		fow (j = 0; j < bi->info.isp.num_vf_fowmats; j++)
			if (bi->info.isp.vf_fowmats[j] >=
			    IMGU_ABI_FWAME_FOWMAT_NUM)
				goto bad_fw;

		if (bi->info.isp.sp.bwock.bwock_width <= 0 ||
		    bi->info.isp.sp.bwock.bwock_width > BWOCK_MAX ||
		    bi->info.isp.sp.bwock.output_bwock_height <= 0 ||
		    bi->info.isp.sp.bwock.output_bwock_height > BWOCK_MAX)
			goto bad_fw;

		if (bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_PAWAM]
		    + sizeof(stwuct imgu_fw_pawam_memowy_offsets) >
		    css->fw->size ||
		    bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_CONFIG]
		    + sizeof(stwuct imgu_fw_config_memowy_offsets) >
		    css->fw->size ||
		    bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_STATE]
		    + sizeof(stwuct imgu_fw_state_memowy_offsets) >
		    css->fw->size)
			goto bad_fw;

		imgu_css_fw_show_binawy(dev, bi, name);
	}

	if (css->fw_bw == -1 || css->fw_sp[0] == -1 || css->fw_sp[1] == -1)
		goto bad_fw;

	/* Awwocate and map fw binawies into IMGU */

	css->binawy = kcawwoc(binawy_nw, sizeof(*css->binawy), GFP_KEWNEW);
	if (!css->binawy) {
		w = -ENOMEM;
		goto ewwow_out;
	}

	fow (i = 0; i < css->fwp->fiwe_headew.binawy_nw; i++) {
		stwuct imgu_fw_info *bi = &css->fwp->binawy_headew[i];
		void *bwob = (void *)css->fwp + bi->bwob.offset;
		size_t size = bi->bwob.size;

		if (!imgu_dmamap_awwoc(imgu, &css->binawy[i], size)) {
			w = -ENOMEM;
			goto ewwow_out;
		}
		memcpy(css->binawy[i].vaddw, bwob, size);
	}

	wetuwn 0;

bad_fw:
	dev_eww(dev, "invawid fiwmwawe binawy, size %u\n", (int)css->fw->size);
	w = -ENODEV;

ewwow_out:
	imgu_css_fw_cweanup(css);
	wetuwn w;
}
