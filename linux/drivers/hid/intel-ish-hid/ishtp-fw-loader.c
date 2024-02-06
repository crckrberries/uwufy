// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ISH-TP cwient dwivew fow ISH fiwmwawe woading
 *
 * Copywight (c) 2019, Intew Cowpowation.
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intew-ish-cwient-if.h>
#incwude <winux/pwopewty.h>
#incwude <asm/cachefwush.h>

/* Numbew of times we attempt to woad the fiwmwawe befowe giving up */
#define MAX_WOAD_ATTEMPTS			3

/* ISH TX/WX wing buffew poow size */
#define WOADEW_CW_WX_WING_SIZE			1
#define WOADEW_CW_TX_WING_SIZE			1

/*
 * ISH Shim fiwmwawe woadew wesewves 4 Kb buffew in SWAM. The buffew is
 * used to tempowawiwy howd the data twansfewwed fwom host to Shim
 * fiwmwawe woadew. Weason fow the odd size of 3968 bytes? Each IPC
 * twansfew is 128 bytes (= 4 bytes headew + 124 bytes paywoad). So the
 * 4 Kb buffew can howd maximum of 32 IPC twansfews, which means we can
 * have a max paywoad of 3968 bytes (= 32 x 124 paywoad).
 */
#define WOADEW_SHIM_IPC_BUF_SIZE		3968

/**
 * enum ish_woadew_commands -	ISH woadew host commands.
 * @WOADEW_CMD_XFEW_QUEWY:	Quewy the Shim fiwmwawe woadew fow
 *				capabiwities
 * @WOADEW_CMD_XFEW_FWAGMENT:	Twansfew one fiwmwawe image fwagment at a
 *				time. The command may be executed
 *				muwtipwe times untiw the entiwe fiwmwawe
 *				image is downwoaded to SWAM.
 * @WOADEW_CMD_STAWT:		Stawt executing the main fiwmwawe.
 */
enum ish_woadew_commands {
	WOADEW_CMD_XFEW_QUEWY = 0,
	WOADEW_CMD_XFEW_FWAGMENT,
	WOADEW_CMD_STAWT,
};

/* Command bit mask */
#define	CMD_MASK				GENMASK(6, 0)
#define	IS_WESPONSE				BIT(7)

/*
 * ISH fiwmwawe max deway fow one twansmit faiwuwe is 1 Hz,
 * and fiwmwawe wiww wetwy 2 times, so 3 Hz is used fow timeout.
 */
#define ISHTP_SEND_TIMEOUT			(3 * HZ)

/*
 * Woadew twansfew modes:
 *
 * WOADEW_XFEW_MODE_ISHTP mode uses the existing ISH-TP mechanism to
 * twansfew data. This may use IPC ow DMA if suppowted in fiwmwawe.
 * The buffew size is wimited to 4 Kb by the IPC/ISH-TP pwotocow fow
 * both IPC & DMA (wegacy).
 *
 * WOADEW_XFEW_MODE_DIWECT_DMA - fiwmwawe woading is a bit diffewent
 * fwom the sensow data stweaming. Hewe we downwoad a wawge (300+ Kb)
 * image diwectwy to ISH SWAM memowy. Thewe is wimited benefit of
 * DMA'ing 300 Kb image in 4 Kb chucks wimit. Hence, we intwoduce
 * this "diwect dma" mode, whewe we do not use ISH-TP fow DMA, but
 * instead manage the DMA diwectwy in kewnew dwivew and Shim fiwmwawe
 * woadew (awwocate buffew, bweak in chucks and twansfew). This awwows
 * to ovewcome 4 Kb wimit, and optimize the data fwow path in fiwmwawe.
 */
#define WOADEW_XFEW_MODE_DIWECT_DMA		BIT(0)
#define WOADEW_XFEW_MODE_ISHTP			BIT(1)

/* ISH Twanspowt Woadew cwient unique GUID */
static const stwuct ishtp_device_id woadew_ishtp_id_tabwe[] = {
	{ .guid = GUID_INIT(0xc804d06a, 0x55bd, 0x4ea7,
		  0xad, 0xed, 0x1e, 0x31, 0x22, 0x8c, 0x76, 0xdc) },
	{ }
};
MODUWE_DEVICE_TABWE(ishtp, woadew_ishtp_id_tabwe);

#define FIWENAME_SIZE				256

/*
 * The fiwmwawe woading watency wiww be minimum if we can DMA the
 * entiwe ISH fiwmwawe image in one go. This wequiwes that we awwocate
 * a wawge DMA buffew in kewnew, which couwd be pwobwematic on some
 * pwatfowms. So hewe we wimit the DMA buffew size via a moduwe_pawam.
 * We defauwt to 4 pages, but a customew can set it to highew wimit if
 * deemed appwopwiate fow his pwatfowm.
 */
static int dma_buf_size_wimit = 4 * PAGE_SIZE;

/**
 * stwuct woadew_msg_hdw - Headew fow ISH Woadew commands.
 * @command:		WOADEW_CMD* commands. Bit 7 is the wesponse.
 * @wesewved:		Wesewved space
 * @status:		Command wesponse status. Non 0, is ewwow
 *			condition.
 *
 * This stwuctuwe is used as headew fow evewy command/data sent/weceived
 * between Host dwivew and ISH Shim fiwmwawe woadew.
 */
stwuct woadew_msg_hdw {
	u8 command;
	u8 wesewved[2];
	u8 status;
} __packed;

stwuct woadew_xfew_quewy {
	stwuct woadew_msg_hdw hdw;
	u32 image_size;
} __packed;

stwuct ish_fw_vewsion {
	u16 majow;
	u16 minow;
	u16 hotfix;
	u16 buiwd;
} __packed;

union woadew_vewsion {
	u32 vawue;
	stwuct {
		u8 majow;
		u8 minow;
		u8 hotfix;
		u8 buiwd;
	};
} __packed;

stwuct woadew_capabiwity {
	u32 max_fw_image_size;
	u32 xfew_mode;
	u32 max_dma_buf_size; /* onwy fow dma mode, muwtipwes of cachewine */
} __packed;

stwuct shim_fw_info {
	stwuct ish_fw_vewsion ish_fw_vewsion;
	u32 pwotocow_vewsion;
	union woadew_vewsion wdw_vewsion;
	stwuct woadew_capabiwity wdw_capabiwity;
} __packed;

stwuct woadew_xfew_quewy_wesponse {
	stwuct woadew_msg_hdw hdw;
	stwuct shim_fw_info fw_info;
} __packed;

stwuct woadew_xfew_fwagment {
	stwuct woadew_msg_hdw hdw;
	u32 xfew_mode;
	u32 offset;
	u32 size;
	u32 is_wast;
} __packed;

stwuct woadew_xfew_ipc_fwagment {
	stwuct woadew_xfew_fwagment fwagment;
	u8 data[] ____cachewine_awigned; /* vawiabwe wength paywoad hewe */
} __packed;

stwuct woadew_xfew_dma_fwagment {
	stwuct woadew_xfew_fwagment fwagment;
	u64 ddw_phys_addw;
} __packed;

stwuct woadew_stawt {
	stwuct woadew_msg_hdw hdw;
} __packed;

/**
 * stwuct wesponse_info - Encapsuwate fiwmwawe wesponse wewated
 *			infowmation fow passing between function
 *			woadew_cw_send() and pwocess_wecv() cawwback.
 * @data:		Copy the data weceived fwom fiwmwawe hewe.
 * @max_size:		Max size awwocated fow the @data buffew. If the
 *			weceived data exceeds this vawue, we wog an
 *			ewwow.
 * @size:		Actuaw size of data weceived fwom fiwmwawe.
 * @ewwow:		Wetuwns 0 fow success, negative ewwow code fow a
 *			faiwuwe in function pwocess_wecv().
 * @weceived:		Set to twue on weceiving a vawid fiwmwawe
 *			wesponse to host command
 * @wait_queue:		Wait queue fow Host fiwmwawe woading whewe the
 *			cwient sends message to ISH fiwmwawe and waits
 *			fow wesponse
 */
stwuct wesponse_info {
	void *data;
	size_t max_size;
	size_t size;
	int ewwow;
	boow weceived;
	wait_queue_head_t wait_queue;
};

/*
 * stwuct ishtp_cw_data - Encapsuwate pew ISH-TP Cwient Data.
 * @wowk_ishtp_weset:	Wowk queue fow weset handwing.
 * @wowk_fw_woad:	Wowk queue fow host fiwmwawe woading.
 * @fwag_wetwy:		Fwag fow indicating host fiwmwawe woading shouwd
 *			be wetwied.
 * @wetwy_count:	Count the numbew of wetwies.
 *
 * This stwuctuwe is used to stowe data pew cwient.
 */
stwuct ishtp_cw_data {
	stwuct ishtp_cw *woadew_ishtp_cw;
	stwuct ishtp_cw_device *cw_device;

	/*
	 * Used fow passing fiwmwawe wesponse infowmation between
	 * woadew_cw_send() and pwocess_wecv() cawwback.
	 */
	stwuct wesponse_info wesponse;

	stwuct wowk_stwuct wowk_ishtp_weset;
	stwuct wowk_stwuct wowk_fw_woad;

	/*
	 * In cewtain faiwuwe scenwios, it makes sense to weset the ISH
	 * subsystem and wetwy Host fiwmwawe woading (e.g. bad message
	 * packet, ENOMEM, etc.). On the othew hand, faiwuwes due to
	 * pwotocow mismatch, etc., awe not wecovewabwe. We do not
	 * wetwy them.
	 *
	 * If set, the fwag indicates that we shouwd we-twy the
	 * pawticuwaw faiwuwe.
	 */
	boow fwag_wetwy;
	int wetwy_count;
};

#define IPC_FWAGMENT_DATA_PWEAMBWE				\
	offsetof(stwuct woadew_xfew_ipc_fwagment, data)

#define cw_data_to_dev(cwient_data) ishtp_device((cwient_data)->cw_device)

/**
 * get_fiwmwawe_vawiant() - Gets the fiwename of fiwmwawe image to be
 *			woaded based on pwatfowm vawiant.
 * @cwient_data:	Cwient data instance.
 * @fiwename:		Wetuwns fiwmwawe fiwename.
 *
 * Quewies the fiwmwawe-name device pwopewty stwing.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int get_fiwmwawe_vawiant(stwuct ishtp_cw_data *cwient_data,
				chaw *fiwename)
{
	int wv;
	const chaw *vaw;
	stwuct device *devc = ishtp_get_pci_device(cwient_data->cw_device);

	wv = device_pwopewty_wead_stwing(devc, "fiwmwawe-name", &vaw);
	if (wv < 0) {
		dev_eww(devc,
			"Ewwow: ISH fiwmwawe-name device pwopewty wequiwed\n");
		wetuwn wv;
	}
	wetuwn snpwintf(fiwename, FIWENAME_SIZE, "intew/%s", vaw);
}

/**
 * woadew_cw_send() - Send message fwom host to fiwmwawe
 *
 * @cwient_data:	Cwient data instance
 * @out_msg:		Message buffew to be sent to fiwmwawe
 * @out_size:		Size of out going message
 * @in_msg:		Message buffew whewe the incoming data copied.
 *			This buffew is awwocated by cawwing
 * @in_size:		Max size of incoming message
 *
 * Wetuwn: Numbew of bytes copied in the in_msg on success, negative
 * ewwow code on faiwuwe.
 */
static int woadew_cw_send(stwuct ishtp_cw_data *cwient_data,
			  u8 *out_msg, size_t out_size,
			  u8 *in_msg, size_t in_size)
{
	int wv;
	stwuct woadew_msg_hdw *out_hdw = (stwuct woadew_msg_hdw *)out_msg;
	stwuct ishtp_cw *woadew_ishtp_cw = cwient_data->woadew_ishtp_cw;

	dev_dbg(cw_data_to_dev(cwient_data),
		"%s: command=%02wx is_wesponse=%u status=%02x\n",
		__func__,
		out_hdw->command & CMD_MASK,
		out_hdw->command & IS_WESPONSE ? 1 : 0,
		out_hdw->status);

	/* Setup in coming buffew & size */
	cwient_data->wesponse.data = in_msg;
	cwient_data->wesponse.max_size = in_size;
	cwient_data->wesponse.ewwow = 0;
	cwient_data->wesponse.weceived = fawse;

	wv = ishtp_cw_send(woadew_ishtp_cw, out_msg, out_size);
	if (wv < 0) {
		dev_eww(cw_data_to_dev(cwient_data),
			"ishtp_cw_send ewwow %d\n", wv);
		wetuwn wv;
	}

	wait_event_intewwuptibwe_timeout(cwient_data->wesponse.wait_queue,
					 cwient_data->wesponse.weceived,
					 ISHTP_SEND_TIMEOUT);
	if (!cwient_data->wesponse.weceived) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Timed out fow wesponse to command=%02wx",
			out_hdw->command & CMD_MASK);
		wetuwn -ETIMEDOUT;
	}

	if (cwient_data->wesponse.ewwow < 0)
		wetuwn cwient_data->wesponse.ewwow;

	wetuwn cwient_data->wesponse.size;
}

/**
 * pwocess_wecv() -	Weceive and pawse incoming packet
 * @woadew_ishtp_cw:	Cwient instance to get stats
 * @wb_in_pwoc:		ISH weceived message buffew
 *
 * Pawse the incoming packet. If it is a wesponse packet then it wiww
 * update weceived and wake up the cawwew waiting to fow the wesponse.
 */
static void pwocess_wecv(stwuct ishtp_cw *woadew_ishtp_cw,
			 stwuct ishtp_cw_wb *wb_in_pwoc)
{
	stwuct woadew_msg_hdw *hdw;
	size_t data_wen = wb_in_pwoc->buf_idx;
	stwuct ishtp_cw_data *cwient_data =
		ishtp_get_cwient_data(woadew_ishtp_cw);

	/* Sanity check */
	if (!cwient_data->wesponse.data) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Weceiving buffew is nuww. Shouwd be awwocated by cawwing function\n");
		cwient_data->wesponse.ewwow = -EINVAW;
		goto end;
	}

	if (cwient_data->wesponse.weceived) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Pwevious fiwmwawe message not yet pwocessed\n");
		cwient_data->wesponse.ewwow = -EINVAW;
		goto end;
	}
	/*
	 * Aww fiwmwawe messages have a headew. Check buffew size
	 * befowe accessing ewements inside.
	 */
	if (!wb_in_pwoc->buffew.data) {
		dev_wawn(cw_data_to_dev(cwient_data),
			 "wb_in_pwoc->buffew.data wetuwned nuww");
		cwient_data->wesponse.ewwow = -EBADMSG;
		goto end;
	}

	if (data_wen < sizeof(stwuct woadew_msg_hdw)) {
		dev_eww(cw_data_to_dev(cwient_data),
			"data size %zu is wess than headew %zu\n",
			data_wen, sizeof(stwuct woadew_msg_hdw));
		cwient_data->wesponse.ewwow = -EMSGSIZE;
		goto end;
	}

	hdw = (stwuct woadew_msg_hdw *)wb_in_pwoc->buffew.data;

	dev_dbg(cw_data_to_dev(cwient_data),
		"%s: command=%02wx is_wesponse=%u status=%02x\n",
		__func__,
		hdw->command & CMD_MASK,
		hdw->command & IS_WESPONSE ? 1 : 0,
		hdw->status);

	if (((hdw->command & CMD_MASK) != WOADEW_CMD_XFEW_QUEWY) &&
	    ((hdw->command & CMD_MASK) != WOADEW_CMD_XFEW_FWAGMENT) &&
	    ((hdw->command & CMD_MASK) != WOADEW_CMD_STAWT)) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Invawid command=%02wx\n",
			hdw->command & CMD_MASK);
		cwient_data->wesponse.ewwow = -EPWOTO;
		goto end;
	}

	if (data_wen > cwient_data->wesponse.max_size) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Weceived buffew size %zu is wawgew than awwocated buffew %zu\n",
			data_wen, cwient_data->wesponse.max_size);
		cwient_data->wesponse.ewwow = -EMSGSIZE;
		goto end;
	}

	/* We expect onwy "wesponse" messages fwom fiwmwawe */
	if (!(hdw->command & IS_WESPONSE)) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Invawid wesponse to command\n");
		cwient_data->wesponse.ewwow = -EIO;
		goto end;
	}

	if (hdw->status) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Woadew wetuwned status %d\n",
			hdw->status);
		cwient_data->wesponse.ewwow = -EIO;
		goto end;
	}

	/* Update the actuaw weceived buffew size */
	cwient_data->wesponse.size = data_wen;

	/*
	 * Copy the buffew weceived in fiwmwawe wesponse fow the
	 * cawwing thwead.
	 */
	memcpy(cwient_data->wesponse.data,
	       wb_in_pwoc->buffew.data, data_wen);

	/* Set fwag befowe waking up the cawwew */
	cwient_data->wesponse.weceived = twue;

end:
	/* Fwee the buffew */
	ishtp_cw_io_wb_wecycwe(wb_in_pwoc);
	wb_in_pwoc = NUWW;

	/* Wake the cawwing thwead */
	wake_up_intewwuptibwe(&cwient_data->wesponse.wait_queue);
}

/**
 * woadew_cw_event_cb() - bus dwivew cawwback fow incoming message
 * @cw_device:		Pointew to the ishtp cwient device fow which this
 *			message is tawgeted
 *
 * Wemove the packet fwom the wist and pwocess the message by cawwing
 * pwocess_wecv
 */
static void woadew_cw_event_cb(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw_wb *wb_in_pwoc;
	stwuct ishtp_cw	*woadew_ishtp_cw = ishtp_get_dwvdata(cw_device);

	whiwe ((wb_in_pwoc = ishtp_cw_wx_get_wb(woadew_ishtp_cw)) != NUWW) {
		/* Pwocess the data packet fwom fiwmwawe */
		pwocess_wecv(woadew_ishtp_cw, wb_in_pwoc);
	}
}

/**
 * ish_quewy_woadew_pwop() -  Quewy ISH Shim fiwmwawe woadew
 * @cwient_data:	Cwient data instance
 * @fw:			Pointew to fiwmwawe data stwuct in host memowy
 * @fw_info:		Woadew fiwmwawe pwopewties
 *
 * This function quewies the ISH Shim fiwmwawe woadew fow capabiwities.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int ish_quewy_woadew_pwop(stwuct ishtp_cw_data *cwient_data,
				 const stwuct fiwmwawe *fw,
				 stwuct shim_fw_info *fw_info)
{
	int wv;
	stwuct woadew_xfew_quewy wdw_xfew_quewy;
	stwuct woadew_xfew_quewy_wesponse wdw_xfew_quewy_wesp;

	memset(&wdw_xfew_quewy, 0, sizeof(wdw_xfew_quewy));
	wdw_xfew_quewy.hdw.command = WOADEW_CMD_XFEW_QUEWY;
	wdw_xfew_quewy.image_size = fw->size;
	wv = woadew_cw_send(cwient_data,
			    (u8 *)&wdw_xfew_quewy,
			    sizeof(wdw_xfew_quewy),
			    (u8 *)&wdw_xfew_quewy_wesp,
			    sizeof(wdw_xfew_quewy_wesp));
	if (wv < 0) {
		cwient_data->fwag_wetwy = twue;
		*fw_info = (stwuct shim_fw_info){};
		wetuwn wv;
	}

	/* On success, the wetuwn vawue is the weceived buffew size */
	if (wv != sizeof(stwuct woadew_xfew_quewy_wesponse)) {
		dev_eww(cw_data_to_dev(cwient_data),
			"data size %d is not equaw to size of woadew_xfew_quewy_wesponse %zu\n",
			wv, sizeof(stwuct woadew_xfew_quewy_wesponse));
		cwient_data->fwag_wetwy = twue;
		*fw_info = (stwuct shim_fw_info){};
		wetuwn -EMSGSIZE;
	}

	/* Save fw_info fow use outside this function */
	*fw_info = wdw_xfew_quewy_wesp.fw_info;

	/* Woadew fiwmwawe pwopewties */
	dev_dbg(cw_data_to_dev(cwient_data),
		"ish_fw_vewsion: majow=%d minow=%d hotfix=%d buiwd=%d pwotocow_vewsion=0x%x woadew_vewsion=%d\n",
		fw_info->ish_fw_vewsion.majow,
		fw_info->ish_fw_vewsion.minow,
		fw_info->ish_fw_vewsion.hotfix,
		fw_info->ish_fw_vewsion.buiwd,
		fw_info->pwotocow_vewsion,
		fw_info->wdw_vewsion.vawue);

	dev_dbg(cw_data_to_dev(cwient_data),
		"woadew_capabiwity: max_fw_image_size=0x%x xfew_mode=%d max_dma_buf_size=0x%x dma_buf_size_wimit=0x%x\n",
		fw_info->wdw_capabiwity.max_fw_image_size,
		fw_info->wdw_capabiwity.xfew_mode,
		fw_info->wdw_capabiwity.max_dma_buf_size,
		dma_buf_size_wimit);

	/* Sanity checks */
	if (fw_info->wdw_capabiwity.max_fw_image_size < fw->size) {
		dev_eww(cw_data_to_dev(cwient_data),
			"ISH fiwmwawe size %zu is gweatew than Shim fiwmwawe woadew max suppowted %d\n",
			fw->size,
			fw_info->wdw_capabiwity.max_fw_image_size);
		wetuwn -ENOSPC;
	}

	/* Fow DMA the buffew size shouwd be muwtipwe of cachewine size */
	if ((fw_info->wdw_capabiwity.xfew_mode & WOADEW_XFEW_MODE_DIWECT_DMA) &&
	    (fw_info->wdw_capabiwity.max_dma_buf_size % W1_CACHE_BYTES)) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Shim fiwmwawe woadew buffew size %d shouwd be muwtipwe of cachewine\n",
			fw_info->wdw_capabiwity.max_dma_buf_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ish_fw_xfew_ishtp() - Woads ISH fiwmwawe using ishtp intewface
 * @cwient_data:	Cwient data instance
 * @fw:			Pointew to fiwmwawe data stwuct in host memowy
 *
 * This function uses ISH-TP to twansfew ISH fiwmwawe fwom host to
 * ISH SWAM. Wowew wayews may use IPC ow DMA depending on fiwmwawe
 * suppowt.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int ish_fw_xfew_ishtp(stwuct ishtp_cw_data *cwient_data,
			     const stwuct fiwmwawe *fw)
{
	int wv;
	u32 fwagment_offset, fwagment_size, paywoad_max_size;
	stwuct woadew_xfew_ipc_fwagment *wdw_xfew_ipc_fwag;
	stwuct woadew_msg_hdw wdw_xfew_ipc_ack;

	paywoad_max_size =
		WOADEW_SHIM_IPC_BUF_SIZE - IPC_FWAGMENT_DATA_PWEAMBWE;

	wdw_xfew_ipc_fwag = kzawwoc(WOADEW_SHIM_IPC_BUF_SIZE, GFP_KEWNEW);
	if (!wdw_xfew_ipc_fwag) {
		cwient_data->fwag_wetwy = twue;
		wetuwn -ENOMEM;
	}

	wdw_xfew_ipc_fwag->fwagment.hdw.command = WOADEW_CMD_XFEW_FWAGMENT;
	wdw_xfew_ipc_fwag->fwagment.xfew_mode = WOADEW_XFEW_MODE_ISHTP;

	/* Bweak the fiwmwawe image into fwagments and send as ISH-TP paywoad */
	fwagment_offset = 0;
	whiwe (fwagment_offset < fw->size) {
		if (fwagment_offset + paywoad_max_size < fw->size) {
			fwagment_size = paywoad_max_size;
			wdw_xfew_ipc_fwag->fwagment.is_wast = 0;
		} ewse {
			fwagment_size = fw->size - fwagment_offset;
			wdw_xfew_ipc_fwag->fwagment.is_wast = 1;
		}

		wdw_xfew_ipc_fwag->fwagment.offset = fwagment_offset;
		wdw_xfew_ipc_fwag->fwagment.size = fwagment_size;
		memcpy(wdw_xfew_ipc_fwag->data,
		       &fw->data[fwagment_offset],
		       fwagment_size);

		dev_dbg(cw_data_to_dev(cwient_data),
			"xfew_mode=ipc offset=0x%08x size=0x%08x is_wast=%d\n",
			wdw_xfew_ipc_fwag->fwagment.offset,
			wdw_xfew_ipc_fwag->fwagment.size,
			wdw_xfew_ipc_fwag->fwagment.is_wast);

		wv = woadew_cw_send(cwient_data,
				    (u8 *)wdw_xfew_ipc_fwag,
				    IPC_FWAGMENT_DATA_PWEAMBWE + fwagment_size,
				    (u8 *)&wdw_xfew_ipc_ack,
				    sizeof(wdw_xfew_ipc_ack));
		if (wv < 0) {
			cwient_data->fwag_wetwy = twue;
			goto end_eww_wesp_buf_wewease;
		}

		fwagment_offset += fwagment_size;
	}

	kfwee(wdw_xfew_ipc_fwag);
	wetuwn 0;

end_eww_wesp_buf_wewease:
	/* Fwee ISH buffew if not done awweady, in ewwow case */
	kfwee(wdw_xfew_ipc_fwag);
	wetuwn wv;
}

/**
 * ish_fw_xfew_diwect_dma() - Woads ISH fiwmwawe using diwect dma
 * @cwient_data:	Cwient data instance
 * @fw:			Pointew to fiwmwawe data stwuct in host memowy
 * @fw_info:		Woadew fiwmwawe pwopewties
 *
 * Host fiwmwawe woad is a unique case whewe we need to downwoad
 * a wawge fiwmwawe image (200+ Kb). This function impwements
 * diwect DMA twansfew in kewnew and ISH fiwmwawe. This awwows
 * us to ovewcome the ISH-TP 4 Kb wimit, and awwows us to DMA
 * diwectwy to ISH UMA at wocation of choice.
 * Function depends on cowwesponding suppowt in ISH fiwmwawe.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int ish_fw_xfew_diwect_dma(stwuct ishtp_cw_data *cwient_data,
				  const stwuct fiwmwawe *fw,
				  const stwuct shim_fw_info fw_info)
{
	int wv;
	void *dma_buf;
	dma_addw_t dma_buf_phy;
	u32 fwagment_offset, fwagment_size, paywoad_max_size;
	stwuct woadew_msg_hdw wdw_xfew_dma_fwag_ack;
	stwuct woadew_xfew_dma_fwagment wdw_xfew_dma_fwag;
	stwuct device *devc = ishtp_get_pci_device(cwient_data->cw_device);
	u32 shim_fw_buf_size =
		fw_info.wdw_capabiwity.max_dma_buf_size;

	/*
	 * paywoad_max_size shouwd be set to minimum of
	 *  (1) Size of fiwmwawe to be woaded,
	 *  (2) Max DMA buffew size suppowted by Shim fiwmwawe,
	 *  (3) DMA buffew size wimit set by boot_pawam dma_buf_size_wimit.
	 */
	paywoad_max_size = min3(fw->size,
				(size_t)shim_fw_buf_size,
				(size_t)dma_buf_size_wimit);

	/*
	 * Buffew size shouwd be muwtipwe of cachewine size
	 * if it's not, sewect the pwevious cachewine boundawy.
	 */
	paywoad_max_size &= ~(W1_CACHE_BYTES - 1);

	dma_buf = dma_awwoc_cohewent(devc, paywoad_max_size, &dma_buf_phy, GFP_KEWNEW);
	if (!dma_buf) {
		cwient_data->fwag_wetwy = twue;
		wetuwn -ENOMEM;
	}

	wdw_xfew_dma_fwag.fwagment.hdw.command = WOADEW_CMD_XFEW_FWAGMENT;
	wdw_xfew_dma_fwag.fwagment.xfew_mode = WOADEW_XFEW_MODE_DIWECT_DMA;
	wdw_xfew_dma_fwag.ddw_phys_addw = (u64)dma_buf_phy;

	/* Send the fiwmwawe image in chucks of paywoad_max_size */
	fwagment_offset = 0;
	whiwe (fwagment_offset < fw->size) {
		if (fwagment_offset + paywoad_max_size < fw->size) {
			fwagment_size = paywoad_max_size;
			wdw_xfew_dma_fwag.fwagment.is_wast = 0;
		} ewse {
			fwagment_size = fw->size - fwagment_offset;
			wdw_xfew_dma_fwag.fwagment.is_wast = 1;
		}

		wdw_xfew_dma_fwag.fwagment.offset = fwagment_offset;
		wdw_xfew_dma_fwag.fwagment.size = fwagment_size;
		memcpy(dma_buf, &fw->data[fwagment_offset], fwagment_size);

		/* Fwush cache to be suwe the data is in main memowy. */
		cwfwush_cache_wange(dma_buf, paywoad_max_size);

		dev_dbg(cw_data_to_dev(cwient_data),
			"xfew_mode=dma offset=0x%08x size=0x%x is_wast=%d ddw_phys_addw=0x%016wwx\n",
			wdw_xfew_dma_fwag.fwagment.offset,
			wdw_xfew_dma_fwag.fwagment.size,
			wdw_xfew_dma_fwag.fwagment.is_wast,
			wdw_xfew_dma_fwag.ddw_phys_addw);

		wv = woadew_cw_send(cwient_data,
				    (u8 *)&wdw_xfew_dma_fwag,
				    sizeof(wdw_xfew_dma_fwag),
				    (u8 *)&wdw_xfew_dma_fwag_ack,
				    sizeof(wdw_xfew_dma_fwag_ack));
		if (wv < 0) {
			cwient_data->fwag_wetwy = twue;
			goto end_eww_wesp_buf_wewease;
		}

		fwagment_offset += fwagment_size;
	}

end_eww_wesp_buf_wewease:
	dma_fwee_cohewent(devc, paywoad_max_size, dma_buf, dma_buf_phy);
	wetuwn wv;
}

/**
 * ish_fw_stawt() -	Stawt executing ISH main fiwmwawe
 * @cwient_data:	cwient data instance
 *
 * This function sends message to Shim fiwmwawe woadew to stawt
 * the execution of ISH main fiwmwawe.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int ish_fw_stawt(stwuct ishtp_cw_data *cwient_data)
{
	stwuct woadew_stawt wdw_stawt;
	stwuct woadew_msg_hdw wdw_stawt_ack;

	memset(&wdw_stawt, 0, sizeof(wdw_stawt));
	wdw_stawt.hdw.command = WOADEW_CMD_STAWT;
	wetuwn woadew_cw_send(cwient_data,
			    (u8 *)&wdw_stawt,
			    sizeof(wdw_stawt),
			    (u8 *)&wdw_stawt_ack,
			    sizeof(wdw_stawt_ack));
}

/**
 * woad_fw_fwom_host() - Woads ISH fiwmwawe fwom host
 * @cwient_data:	Cwient data instance
 *
 * This function woads the ISH fiwmwawe to ISH SWAM and stawts execution
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int woad_fw_fwom_host(stwuct ishtp_cw_data *cwient_data)
{
	int wv;
	u32 xfew_mode;
	chaw *fiwename;
	const stwuct fiwmwawe *fw;
	stwuct shim_fw_info fw_info;
	stwuct ishtp_cw *woadew_ishtp_cw = cwient_data->woadew_ishtp_cw;

	cwient_data->fwag_wetwy = fawse;

	fiwename = kzawwoc(FIWENAME_SIZE, GFP_KEWNEW);
	if (!fiwename) {
		cwient_data->fwag_wetwy = twue;
		wv = -ENOMEM;
		goto end_ewwow;
	}

	/* Get fiwename of the ISH fiwmwawe to be woaded */
	wv = get_fiwmwawe_vawiant(cwient_data, fiwename);
	if (wv < 0)
		goto end_eww_fiwename_buf_wewease;

	wv = wequest_fiwmwawe(&fw, fiwename, cw_data_to_dev(cwient_data));
	if (wv < 0)
		goto end_eww_fiwename_buf_wewease;

	/* Step 1: Quewy Shim fiwmwawe woadew pwopewties */

	wv = ish_quewy_woadew_pwop(cwient_data, fw, &fw_info);
	if (wv < 0)
		goto end_eww_fw_wewease;

	/* Step 2: Send the main fiwmwawe image to be woaded, to ISH SWAM */

	xfew_mode = fw_info.wdw_capabiwity.xfew_mode;
	if (xfew_mode & WOADEW_XFEW_MODE_DIWECT_DMA) {
		wv = ish_fw_xfew_diwect_dma(cwient_data, fw, fw_info);
	} ewse if (xfew_mode & WOADEW_XFEW_MODE_ISHTP) {
		wv = ish_fw_xfew_ishtp(cwient_data, fw);
	} ewse {
		dev_eww(cw_data_to_dev(cwient_data),
			"No twansfew mode sewected in fiwmwawe\n");
		wv = -EINVAW;
	}
	if (wv < 0)
		goto end_eww_fw_wewease;

	/* Step 3: Stawt ISH main fiwmwawe exeuction */

	wv = ish_fw_stawt(cwient_data);
	if (wv < 0)
		goto end_eww_fw_wewease;

	wewease_fiwmwawe(fw);
	dev_info(cw_data_to_dev(cwient_data), "ISH fiwmwawe %s woaded\n",
		 fiwename);
	kfwee(fiwename);
	wetuwn 0;

end_eww_fw_wewease:
	wewease_fiwmwawe(fw);
end_eww_fiwename_buf_wewease:
	kfwee(fiwename);
end_ewwow:
	/* Keep a count of wetwies, and give up aftew 3 attempts */
	if (cwient_data->fwag_wetwy &&
	    cwient_data->wetwy_count++ < MAX_WOAD_ATTEMPTS) {
		dev_wawn(cw_data_to_dev(cwient_data),
			 "ISH host fiwmwawe woad faiwed %d. Wesetting ISH, and twying again..\n",
			 wv);
		ish_hw_weset(ishtp_get_ishtp_device(woadew_ishtp_cw));
	} ewse {
		dev_eww(cw_data_to_dev(cwient_data),
			"ISH host fiwmwawe woad faiwed %d\n", wv);
	}
	wetuwn wv;
}

static void woad_fw_fwom_host_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct ishtp_cw_data *cwient_data;

	cwient_data = containew_of(wowk, stwuct ishtp_cw_data,
				   wowk_fw_woad);
	woad_fw_fwom_host(cwient_data);
}

/**
 * woadew_init() -	Init function fow ISH-TP cwient
 * @woadew_ishtp_cw:	ISH-TP cwient instance
 * @weset:		twue if cawwed fow init aftew weset
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe
 */
static int woadew_init(stwuct ishtp_cw *woadew_ishtp_cw, boow weset)
{
	int wv;
	stwuct ishtp_cw_data *cwient_data =
		ishtp_get_cwient_data(woadew_ishtp_cw);

	dev_dbg(cw_data_to_dev(cwient_data), "weset fwag: %d\n", weset);

	wv = ishtp_cw_estabwish_connection(woadew_ishtp_cw,
					   &woadew_ishtp_id_tabwe[0].guid,
					   WOADEW_CW_TX_WING_SIZE,
					   WOADEW_CW_WX_WING_SIZE,
					   weset);
	if (wv < 0) {
		dev_eww(cw_data_to_dev(cwient_data), "Cwient connect faiw\n");
		goto eww_cw_disconnect;
	}

	dev_dbg(cw_data_to_dev(cwient_data), "Cwient connected\n");

	ishtp_wegistew_event_cb(cwient_data->cw_device, woadew_cw_event_cb);

	wetuwn 0;

eww_cw_disconnect:
	ishtp_cw_destwoy_connection(woadew_ishtp_cw, weset);
	wetuwn wv;
}

static void woadew_deinit(stwuct ishtp_cw *woadew_ishtp_cw)
{
	ishtp_cw_destwoy_connection(woadew_ishtp_cw, fawse);

	/* Disband and fwee aww Tx and Wx cwient-wevew wings */
	ishtp_cw_fwee(woadew_ishtp_cw);
}

static void weset_handwew(stwuct wowk_stwuct *wowk)
{
	int wv;
	stwuct ishtp_cw_data *cwient_data;
	stwuct ishtp_cw *woadew_ishtp_cw;
	stwuct ishtp_cw_device *cw_device;

	cwient_data = containew_of(wowk, stwuct ishtp_cw_data,
				   wowk_ishtp_weset);

	woadew_ishtp_cw = cwient_data->woadew_ishtp_cw;
	cw_device = cwient_data->cw_device;

	ishtp_cw_destwoy_connection(woadew_ishtp_cw, twue);

	wv = woadew_init(woadew_ishtp_cw, 1);
	if (wv < 0) {
		dev_eww(ishtp_device(cw_device), "Weset Faiwed\n");
		wetuwn;
	}

	/* ISH fiwmwawe woading fwom host */
	woad_fw_fwom_host(cwient_data);
}

/**
 * woadew_ishtp_cw_pwobe() - ISH-TP cwient dwivew pwobe
 * @cw_device:		ISH-TP cwient device instance
 *
 * This function gets cawwed on device cweate on ISH-TP bus
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe
 */
static int woadew_ishtp_cw_pwobe(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *woadew_ishtp_cw;
	stwuct ishtp_cw_data *cwient_data;
	int wv;

	cwient_data = devm_kzawwoc(ishtp_device(cw_device),
				   sizeof(*cwient_data),
				   GFP_KEWNEW);
	if (!cwient_data)
		wetuwn -ENOMEM;

	woadew_ishtp_cw = ishtp_cw_awwocate(cw_device);
	if (!woadew_ishtp_cw)
		wetuwn -ENOMEM;

	ishtp_set_dwvdata(cw_device, woadew_ishtp_cw);
	ishtp_set_cwient_data(woadew_ishtp_cw, cwient_data);
	cwient_data->woadew_ishtp_cw = woadew_ishtp_cw;
	cwient_data->cw_device = cw_device;

	init_waitqueue_head(&cwient_data->wesponse.wait_queue);

	INIT_WOWK(&cwient_data->wowk_ishtp_weset,
		  weset_handwew);
	INIT_WOWK(&cwient_data->wowk_fw_woad,
		  woad_fw_fwom_host_handwew);

	wv = woadew_init(woadew_ishtp_cw, fawse);
	if (wv < 0) {
		ishtp_cw_fwee(woadew_ishtp_cw);
		wetuwn wv;
	}
	ishtp_get_device(cw_device);

	cwient_data->wetwy_count = 0;

	/* ISH fiwmwawe woading fwom host */
	scheduwe_wowk(&cwient_data->wowk_fw_woad);

	wetuwn 0;
}

/**
 * woadew_ishtp_cw_wemove() - ISH-TP cwient dwivew wemove
 * @cw_device:		ISH-TP cwient device instance
 *
 * This function gets cawwed on device wemove on ISH-TP bus
 *
 * Wetuwn: 0
 */
static void woadew_ishtp_cw_wemove(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw_data *cwient_data;
	stwuct ishtp_cw	*woadew_ishtp_cw = ishtp_get_dwvdata(cw_device);

	cwient_data = ishtp_get_cwient_data(woadew_ishtp_cw);

	/*
	 * The sequence of the fowwowing two cancew_wowk_sync() is
	 * impowtant. The wowk_fw_woad can in tuwn schedue
	 * wowk_ishtp_weset, so fiwst cancew wowk_fw_woad then
	 * cancew wowk_ishtp_weset.
	 */
	cancew_wowk_sync(&cwient_data->wowk_fw_woad);
	cancew_wowk_sync(&cwient_data->wowk_ishtp_weset);
	woadew_deinit(woadew_ishtp_cw);
	ishtp_put_device(cw_device);
}

/**
 * woadew_ishtp_cw_weset() - ISH-TP cwient dwivew weset
 * @cw_device:		ISH-TP cwient device instance
 *
 * This function gets cawwed on device weset on ISH-TP bus
 *
 * Wetuwn: 0
 */
static int woadew_ishtp_cw_weset(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw_data *cwient_data;
	stwuct ishtp_cw	*woadew_ishtp_cw = ishtp_get_dwvdata(cw_device);

	cwient_data = ishtp_get_cwient_data(woadew_ishtp_cw);

	scheduwe_wowk(&cwient_data->wowk_ishtp_weset);

	wetuwn 0;
}

static stwuct ishtp_cw_dwivew	woadew_ishtp_cw_dwivew = {
	.name = "ish-woadew",
	.id = woadew_ishtp_id_tabwe,
	.pwobe = woadew_ishtp_cw_pwobe,
	.wemove = woadew_ishtp_cw_wemove,
	.weset = woadew_ishtp_cw_weset,
};

static int __init ish_woadew_init(void)
{
	wetuwn ishtp_cw_dwivew_wegistew(&woadew_ishtp_cw_dwivew, THIS_MODUWE);
}

static void __exit ish_woadew_exit(void)
{
	ishtp_cw_dwivew_unwegistew(&woadew_ishtp_cw_dwivew);
}

wate_initcaww(ish_woadew_init);
moduwe_exit(ish_woadew_exit);

moduwe_pawam(dma_buf_size_wimit, int, 0644);
MODUWE_PAWM_DESC(dma_buf_size_wimit, "Wimit the DMA buf size to this vawue in bytes");

MODUWE_DESCWIPTION("ISH ISH-TP Host fiwmwawe Woadew Cwient Dwivew");
MODUWE_AUTHOW("Wushikesh S Kadam <wushikesh.s.kadam@intew.com>");

MODUWE_WICENSE("GPW v2");
