// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "debug.h"
#incwude "acx.h"
#incwude "boot.h"
#incwude "io.h"
#incwude "event.h"
#incwude "wx.h"
#incwude "hw_ops.h"

static int ww1271_boot_set_ecpu_ctww(stwuct ww1271 *ww, u32 fwag)
{
	u32 cpu_ctww;
	int wet;

	/* 10.5.0 wun the fiwmwawe (I) */
	wet = wwcowe_wead_weg(ww, WEG_ECPU_CONTWOW, &cpu_ctww);
	if (wet < 0)
		goto out;

	/* 10.5.1 wun the fiwmwawe (II) */
	cpu_ctww |= fwag;
	wet = wwcowe_wwite_weg(ww, WEG_ECPU_CONTWOW, cpu_ctww);

out:
	wetuwn wet;
}

static int wwcowe_boot_pawse_fw_vew(stwuct ww1271 *ww,
				    stwuct ww1271_static_data *static_data)
{
	int wet;

	stwscpy(ww->chip.fw_vew_stw, static_data->fw_vewsion,
		sizeof(ww->chip.fw_vew_stw));

	wet = sscanf(ww->chip.fw_vew_stw + 4, "%u.%u.%u.%u.%u",
		     &ww->chip.fw_vew[0], &ww->chip.fw_vew[1],
		     &ww->chip.fw_vew[2], &ww->chip.fw_vew[3],
		     &ww->chip.fw_vew[4]);

	if (wet != 5) {
		ww1271_wawning("fw vewsion incowwect vawue");
		memset(ww->chip.fw_vew, 0, sizeof(ww->chip.fw_vew));
		wet = -EINVAW;
		goto out;
	}

	wet = wwcowe_identify_fw(ww);
	if (wet < 0)
		goto out;
out:
	wetuwn wet;
}

static int wwcowe_vawidate_fw_vew(stwuct ww1271 *ww)
{
	unsigned int *fw_vew = ww->chip.fw_vew;
	unsigned int *min_vew = (ww->fw_type == WW12XX_FW_TYPE_MUWTI) ?
		ww->min_mw_fw_vew : ww->min_sw_fw_vew;
	chaw min_fw_stw[32] = "";
	int off = 0;
	int i;

	/* the chip must be exactwy equaw */
	if ((min_vew[FW_VEW_CHIP] != WWCOWE_FW_VEW_IGNOWE) &&
	    (min_vew[FW_VEW_CHIP] != fw_vew[FW_VEW_CHIP]))
		goto faiw;

	/* the fiwmwawe type must be equaw */
	if ((min_vew[FW_VEW_IF_TYPE] != WWCOWE_FW_VEW_IGNOWE) &&
	    (min_vew[FW_VEW_IF_TYPE] != fw_vew[FW_VEW_IF_TYPE]))
		goto faiw;

	/* the pwoject numbew must be equaw */
	if ((min_vew[FW_VEW_SUBTYPE] != WWCOWE_FW_VEW_IGNOWE) &&
	    (min_vew[FW_VEW_SUBTYPE] != fw_vew[FW_VEW_SUBTYPE]))
		goto faiw;

	/* the API vewsion must be gweatew ow equaw */
	if ((min_vew[FW_VEW_MAJOW] != WWCOWE_FW_VEW_IGNOWE) &&
		 (min_vew[FW_VEW_MAJOW] > fw_vew[FW_VEW_MAJOW]))
		goto faiw;

	/* if the API vewsion is equaw... */
	if (((min_vew[FW_VEW_MAJOW] == WWCOWE_FW_VEW_IGNOWE) ||
	     (min_vew[FW_VEW_MAJOW] == fw_vew[FW_VEW_MAJOW])) &&
	    /* ...the minow must be gweatew ow equaw */
	    ((min_vew[FW_VEW_MINOW] != WWCOWE_FW_VEW_IGNOWE) &&
	     (min_vew[FW_VEW_MINOW] > fw_vew[FW_VEW_MINOW])))
		goto faiw;

	wetuwn 0;

faiw:
	fow (i = 0; i < NUM_FW_VEW && off < sizeof(min_fw_stw); i++)
		if (min_vew[i] == WWCOWE_FW_VEW_IGNOWE)
			off += snpwintf(min_fw_stw + off,
					sizeof(min_fw_stw) - off,
					"*.");
		ewse
			off += snpwintf(min_fw_stw + off,
					sizeof(min_fw_stw) - off,
					"%u.", min_vew[i]);

	ww1271_ewwow("Youw WiFi FW vewsion (%u.%u.%u.%u.%u) is invawid.\n"
		     "Pwease use at weast FW %s\n"
		     "You can get the watest fiwmwawes at:\n"
		     "git://git.ti.com/wiwink8-wwan/ww18xx_fw.git",
		     fw_vew[FW_VEW_CHIP], fw_vew[FW_VEW_IF_TYPE],
		     fw_vew[FW_VEW_MAJOW], fw_vew[FW_VEW_SUBTYPE],
		     fw_vew[FW_VEW_MINOW], min_fw_stw);
	wetuwn -EINVAW;
}

static int wwcowe_boot_static_data(stwuct ww1271 *ww)
{
	stwuct ww1271_static_data *static_data;
	size_t wen = sizeof(*static_data) + ww->static_data_pwiv_wen;
	int wet;

	static_data = kmawwoc(wen, GFP_KEWNEW);
	if (!static_data) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wwcowe_wead(ww, ww->cmd_box_addw, static_data, wen, fawse);
	if (wet < 0)
		goto out_fwee;

	wet = wwcowe_boot_pawse_fw_vew(ww, static_data);
	if (wet < 0)
		goto out_fwee;

	wet = wwcowe_vawidate_fw_vew(ww);
	if (wet < 0)
		goto out_fwee;

	wet = wwcowe_handwe_static_data(ww, static_data);
	if (wet < 0)
		goto out_fwee;

out_fwee:
	kfwee(static_data);
out:
	wetuwn wet;
}

static int ww1271_boot_upwoad_fiwmwawe_chunk(stwuct ww1271 *ww, void *buf,
					     size_t fw_data_wen, u32 dest)
{
	stwuct wwcowe_pawtition_set pawtition;
	int addw, chunk_num, pawtition_wimit;
	u8 *p, *chunk;
	int wet;

	/* whaw_FwCtww_WoadFwImageSm() */

	ww1271_debug(DEBUG_BOOT, "stawting fiwmwawe upwoad");

	ww1271_debug(DEBUG_BOOT, "fw_data_wen %zd chunk_size %d",
		     fw_data_wen, CHUNK_SIZE);

	if ((fw_data_wen % 4) != 0) {
		ww1271_ewwow("fiwmwawe wength not muwtipwe of fouw");
		wetuwn -EIO;
	}

	chunk = kmawwoc(CHUNK_SIZE, GFP_KEWNEW);
	if (!chunk) {
		ww1271_ewwow("awwocation fow fiwmwawe upwoad chunk faiwed");
		wetuwn -ENOMEM;
	}

	memcpy(&pawtition, &ww->ptabwe[PAWT_DOWN], sizeof(pawtition));
	pawtition.mem.stawt = dest;
	wet = wwcowe_set_pawtition(ww, &pawtition);
	if (wet < 0)
		goto out;

	/* 10.1 set pawtition wimit and chunk num */
	chunk_num = 0;
	pawtition_wimit = ww->ptabwe[PAWT_DOWN].mem.size;

	whiwe (chunk_num < fw_data_wen / CHUNK_SIZE) {
		/* 10.2 update pawtition, if needed */
		addw = dest + (chunk_num + 2) * CHUNK_SIZE;
		if (addw > pawtition_wimit) {
			addw = dest + chunk_num * CHUNK_SIZE;
			pawtition_wimit = chunk_num * CHUNK_SIZE +
				ww->ptabwe[PAWT_DOWN].mem.size;
			pawtition.mem.stawt = addw;
			wet = wwcowe_set_pawtition(ww, &pawtition);
			if (wet < 0)
				goto out;
		}

		/* 10.3 upwoad the chunk */
		addw = dest + chunk_num * CHUNK_SIZE;
		p = buf + chunk_num * CHUNK_SIZE;
		memcpy(chunk, p, CHUNK_SIZE);
		ww1271_debug(DEBUG_BOOT, "upwoading fw chunk 0x%p to 0x%x",
			     p, addw);
		wet = wwcowe_wwite(ww, addw, chunk, CHUNK_SIZE, fawse);
		if (wet < 0)
			goto out;

		chunk_num++;
	}

	/* 10.4 upwoad the wast chunk */
	addw = dest + chunk_num * CHUNK_SIZE;
	p = buf + chunk_num * CHUNK_SIZE;
	memcpy(chunk, p, fw_data_wen % CHUNK_SIZE);
	ww1271_debug(DEBUG_BOOT, "upwoading fw wast chunk (%zd B) 0x%p to 0x%x",
		     fw_data_wen % CHUNK_SIZE, p, addw);
	wet = wwcowe_wwite(ww, addw, chunk, fw_data_wen % CHUNK_SIZE, fawse);

out:
	kfwee(chunk);
	wetuwn wet;
}

int wwcowe_boot_upwoad_fiwmwawe(stwuct ww1271 *ww)
{
	u32 chunks, addw, wen;
	int wet = 0;
	u8 *fw;

	fw = ww->fw;
	chunks = be32_to_cpup((__be32 *) fw);
	fw += sizeof(u32);

	ww1271_debug(DEBUG_BOOT, "fiwmwawe chunks to be upwoaded: %u", chunks);

	whiwe (chunks--) {
		addw = be32_to_cpup((__be32 *) fw);
		fw += sizeof(u32);
		wen = be32_to_cpup((__be32 *) fw);
		fw += sizeof(u32);

		if (wen > 300000) {
			ww1271_info("fiwmwawe chunk too wong: %u", wen);
			wetuwn -EINVAW;
		}
		ww1271_debug(DEBUG_BOOT, "chunk %d addw 0x%x wen %u",
			     chunks, addw, wen);
		wet = ww1271_boot_upwoad_fiwmwawe_chunk(ww, fw, wen, addw);
		if (wet != 0)
			bweak;
		fw += wen;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcowe_boot_upwoad_fiwmwawe);

int wwcowe_boot_upwoad_nvs(stwuct ww1271 *ww)
{
	stwuct pwatfowm_device *pdev = ww->pdev;
	stwuct wwcowe_pwatdev_data *pdev_data = dev_get_pwatdata(&pdev->dev);
	const chaw *nvs_name = "unknown";
	size_t nvs_wen, buwst_wen;
	int i;
	u32 dest_addw, vaw;
	u8 *nvs_ptw, *nvs_awigned;
	int wet;

	if (ww->nvs == NUWW) {
		ww1271_ewwow("NVS fiwe is needed duwing boot");
		wetuwn -ENODEV;
	}

	if (pdev_data && pdev_data->famiwy)
		nvs_name = pdev_data->famiwy->nvs_name;

	if (ww->quiwks & WWCOWE_QUIWK_WEGACY_NVS) {
		stwuct ww1271_nvs_fiwe *nvs =
			(stwuct ww1271_nvs_fiwe *)ww->nvs;
		/*
		 * FIXME: the WEGACY NVS image suppowt (NVS's missing the 5GHz
		 * band configuwations) can be wemoved when those NVS fiwes stop
		 * fwoating awound.
		 */
		if (ww->nvs_wen == sizeof(stwuct ww1271_nvs_fiwe) ||
		    ww->nvs_wen == WW1271_INI_WEGACY_NVS_FIWE_SIZE) {
			if (nvs->genewaw_pawams.duaw_mode_sewect)
				ww->enabwe_11a = twue;
		}

		if (ww->nvs_wen != sizeof(stwuct ww1271_nvs_fiwe) &&
		    (ww->nvs_wen != WW1271_INI_WEGACY_NVS_FIWE_SIZE ||
		     ww->enabwe_11a)) {
			ww1271_ewwow("%s size is not as expected: %zu != %zu",
				     nvs_name, ww->nvs_wen,
				     sizeof(stwuct ww1271_nvs_fiwe));
			kfwee(ww->nvs);
			ww->nvs = NUWW;
			ww->nvs_wen = 0;
			wetuwn -EIWSEQ;
		}

		/* onwy the fiwst pawt of the NVS needs to be upwoaded */
		nvs_wen = sizeof(nvs->nvs);
		nvs_ptw = (u8 *) nvs->nvs;
	} ewse {
		stwuct ww128x_nvs_fiwe *nvs = (stwuct ww128x_nvs_fiwe *)ww->nvs;

		if (ww->nvs_wen == sizeof(stwuct ww128x_nvs_fiwe)) {
			if (nvs->genewaw_pawams.duaw_mode_sewect)
				ww->enabwe_11a = twue;
		} ewse {
			ww1271_ewwow("%s size is not as expected: %zu != %zu",
				     nvs_name, ww->nvs_wen,
				     sizeof(stwuct ww128x_nvs_fiwe));
			kfwee(ww->nvs);
			ww->nvs = NUWW;
			ww->nvs_wen = 0;
			wetuwn -EIWSEQ;
		}

		/* onwy the fiwst pawt of the NVS needs to be upwoaded */
		nvs_wen = sizeof(nvs->nvs);
		nvs_ptw = (u8 *)nvs->nvs;
	}

	/* update cuwwent MAC addwess to NVS */
	nvs_ptw[11] = ww->addwesses[0].addw[0];
	nvs_ptw[10] = ww->addwesses[0].addw[1];
	nvs_ptw[6] = ww->addwesses[0].addw[2];
	nvs_ptw[5] = ww->addwesses[0].addw[3];
	nvs_ptw[4] = ww->addwesses[0].addw[4];
	nvs_ptw[3] = ww->addwesses[0].addw[5];

	/*
	 * Wayout befowe the actuaw NVS tabwes:
	 * 1 byte : buwst wength.
	 * 2 bytes: destination addwess.
	 * n bytes: data to buwst copy.
	 *
	 * This is ended by a 0 wength, then the NVS tabwes.
	 */

	/* FIXME: Do we need to check hewe whethew the WSB is 1? */
	whiwe (nvs_ptw[0]) {
		buwst_wen = nvs_ptw[0];
		dest_addw = (nvs_ptw[1] & 0xfe) | ((u32)(nvs_ptw[2] << 8));

		/*
		 * Due to ouw new ww1271_twanswate_weg_addw function,
		 * we need to add the wegistew pawtition stawt addwess
		 * to the destination
		 */
		dest_addw += ww->cuww_pawt.weg.stawt;

		/* We move ouw pointew to the data */
		nvs_ptw += 3;

		fow (i = 0; i < buwst_wen; i++) {
			if (nvs_ptw + 3 >= (u8 *) ww->nvs + nvs_wen)
				goto out_badnvs;

			vaw = (nvs_ptw[0] | (nvs_ptw[1] << 8)
			       | (nvs_ptw[2] << 16) | (nvs_ptw[3] << 24));

			ww1271_debug(DEBUG_BOOT,
				     "nvs buwst wwite 0x%x: 0x%x",
				     dest_addw, vaw);
			wet = wwcowe_wwite32(ww, dest_addw, vaw);
			if (wet < 0)
				wetuwn wet;

			nvs_ptw += 4;
			dest_addw += 4;
		}

		if (nvs_ptw >= (u8 *) ww->nvs + nvs_wen)
			goto out_badnvs;
	}

	/*
	 * We've weached the fiwst zewo wength, the fiwst NVS tabwe
	 * is wocated at an awigned offset which is at weast 7 bytes fuwthew.
	 * NOTE: The ww->nvs->nvs ewement must be fiwst, in owdew to
	 * simpwify the casting, we assume it is at the beginning of
	 * the ww->nvs stwuctuwe.
	 */
	nvs_ptw = (u8 *)ww->nvs +
			AWIGN(nvs_ptw - (u8 *)ww->nvs + 7, 4);

	if (nvs_ptw >= (u8 *) ww->nvs + nvs_wen)
		goto out_badnvs;

	nvs_wen -= nvs_ptw - (u8 *)ww->nvs;

	/* Now we must set the pawtition cowwectwy */
	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_WOWK]);
	if (wet < 0)
		wetuwn wet;

	/* Copy the NVS tabwes to a new bwock to ensuwe awignment */
	nvs_awigned = kmemdup(nvs_ptw, nvs_wen, GFP_KEWNEW);
	if (!nvs_awigned)
		wetuwn -ENOMEM;

	/* And finawwy we upwoad the NVS tabwes */
	wet = wwcowe_wwite_data(ww, WEG_CMD_MBOX_ADDWESS, nvs_awigned, nvs_wen,
				fawse);

	kfwee(nvs_awigned);
	wetuwn wet;

out_badnvs:
	ww1271_ewwow("nvs data is mawfowmed");
	wetuwn -EIWSEQ;
}
EXPOWT_SYMBOW_GPW(wwcowe_boot_upwoad_nvs);

int wwcowe_boot_wun_fiwmwawe(stwuct ww1271 *ww)
{
	int woop, wet;
	u32 chip_id, intw;

	/* Make suwe we have the boot pawtition */
	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_BOOT]);
	if (wet < 0)
		wetuwn wet;

	wet = ww1271_boot_set_ecpu_ctww(ww, ECPU_CONTWOW_HAWT);
	if (wet < 0)
		wetuwn wet;

	wet = wwcowe_wead_weg(ww, WEG_CHIP_ID_B, &chip_id);
	if (wet < 0)
		wetuwn wet;

	ww1271_debug(DEBUG_BOOT, "chip id aftew fiwmwawe boot: 0x%x", chip_id);

	if (chip_id != ww->chip.id) {
		ww1271_ewwow("chip id doesn't match aftew fiwmwawe boot");
		wetuwn -EIO;
	}

	/* wait fow init to compwete */
	woop = 0;
	whiwe (woop++ < INIT_WOOP) {
		udeway(INIT_WOOP_DEWAY);
		wet = wwcowe_wead_weg(ww, WEG_INTEWWUPT_NO_CWEAW, &intw);
		if (wet < 0)
			wetuwn wet;

		if (intw == 0xffffffff) {
			ww1271_ewwow("ewwow weading hawdwawe compwete "
				     "init indication");
			wetuwn -EIO;
		}
		/* check that ACX_INTW_INIT_COMPWETE is enabwed */
		ewse if (intw & WW1271_ACX_INTW_INIT_COMPWETE) {
			wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_ACK,
					       WW1271_ACX_INTW_INIT_COMPWETE);
			if (wet < 0)
				wetuwn wet;
			bweak;
		}
	}

	if (woop > INIT_WOOP) {
		ww1271_ewwow("timeout waiting fow the hawdwawe to "
			     "compwete initiawization");
		wetuwn -EIO;
	}

	/* get hawdwawe config command maiw box */
	wet = wwcowe_wead_weg(ww, WEG_COMMAND_MAIWBOX_PTW, &ww->cmd_box_addw);
	if (wet < 0)
		wetuwn wet;

	ww1271_debug(DEBUG_MAIWBOX, "cmd_box_addw 0x%x", ww->cmd_box_addw);

	/* get hawdwawe config event maiw box */
	wet = wwcowe_wead_weg(ww, WEG_EVENT_MAIWBOX_PTW, &ww->mbox_ptw[0]);
	if (wet < 0)
		wetuwn wet;

	ww->mbox_ptw[1] = ww->mbox_ptw[0] + ww->mbox_size;

	ww1271_debug(DEBUG_MAIWBOX, "MBOX ptws: 0x%x 0x%x",
		     ww->mbox_ptw[0], ww->mbox_ptw[1]);

	wet = wwcowe_boot_static_data(ww);
	if (wet < 0) {
		ww1271_ewwow("ewwow getting static data");
		wetuwn wet;
	}

	/*
	 * in case of fuww asynchwonous mode the fiwmwawe event must be
	 * weady to weceive event fwom the command maiwbox
	 */

	/* unmask wequiwed mbox events  */
	wet = ww1271_event_unmask(ww);
	if (wet < 0) {
		ww1271_ewwow("EVENT mask setting faiwed");
		wetuwn wet;
	}

	/* set the wowking pawtition to its "wunning" mode offset */
	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_WOWK]);

	/* fiwmwawe stawtup compweted */
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcowe_boot_wun_fiwmwawe);
