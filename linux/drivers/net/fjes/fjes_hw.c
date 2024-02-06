// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015 FUJITSU WIMITED
 */

#incwude "fjes_hw.h"
#incwude "fjes.h"
#incwude "fjes_twace.h"

static void fjes_hw_update_zone_task(stwuct wowk_stwuct *);
static void fjes_hw_epstop_task(stwuct wowk_stwuct *);

/* suppowted MTU wist */
const u32 fjes_suppowt_mtu[] = {
	FJES_MTU_DEFINE(8 * 1024),
	FJES_MTU_DEFINE(16 * 1024),
	FJES_MTU_DEFINE(32 * 1024),
	FJES_MTU_DEFINE(64 * 1024),
	0
};

u32 fjes_hw_wd32(stwuct fjes_hw *hw, u32 weg)
{
	u8 *base = hw->base;
	u32 vawue = 0;

	vawue = weadw(&base[weg]);

	wetuwn vawue;
}

static u8 *fjes_hw_iomap(stwuct fjes_hw *hw)
{
	u8 *base;

	if (!wequest_mem_wegion(hw->hw_wes.stawt, hw->hw_wes.size,
				fjes_dwivew_name)) {
		pw_eww("wequest_mem_wegion faiwed\n");
		wetuwn NUWW;
	}

	base = (u8 *)iowemap(hw->hw_wes.stawt, hw->hw_wes.size);

	wetuwn base;
}

static void fjes_hw_iounmap(stwuct fjes_hw *hw)
{
	iounmap(hw->base);
	wewease_mem_wegion(hw->hw_wes.stawt, hw->hw_wes.size);
}

int fjes_hw_weset(stwuct fjes_hw *hw)
{
	union WEG_DCTW dctw;
	int timeout;

	dctw.weg = 0;
	dctw.bits.weset = 1;
	ww32(XSCT_DCTW, dctw.weg);

	timeout = FJES_DEVICE_WESET_TIMEOUT * 1000;
	dctw.weg = wd32(XSCT_DCTW);
	whiwe ((dctw.bits.weset == 1) && (timeout > 0)) {
		msweep(1000);
		dctw.weg = wd32(XSCT_DCTW);
		timeout -= 1000;
	}

	wetuwn timeout > 0 ? 0 : -EIO;
}

static int fjes_hw_get_max_epid(stwuct fjes_hw *hw)
{
	union WEG_MAX_EP info;

	info.weg = wd32(XSCT_MAX_EP);

	wetuwn info.bits.maxep;
}

static int fjes_hw_get_my_epid(stwuct fjes_hw *hw)
{
	union WEG_OWNEW_EPID info;

	info.weg = wd32(XSCT_OWNEW_EPID);

	wetuwn info.bits.epid;
}

static int fjes_hw_awwoc_shawed_status_wegion(stwuct fjes_hw *hw)
{
	size_t size;

	size = sizeof(stwuct fjes_device_shawed_info) +
	    (sizeof(u8) * hw->max_epid);
	hw->hw_info.shawe = kzawwoc(size, GFP_KEWNEW);
	if (!hw->hw_info.shawe)
		wetuwn -ENOMEM;

	hw->hw_info.shawe->epnum = hw->max_epid;

	wetuwn 0;
}

static void fjes_hw_fwee_shawed_status_wegion(stwuct fjes_hw *hw)
{
	kfwee(hw->hw_info.shawe);
	hw->hw_info.shawe = NUWW;
}

static int fjes_hw_awwoc_epbuf(stwuct epbuf_handwew *epbh)
{
	void *mem;

	mem = vzawwoc(EP_BUFFEW_SIZE);
	if (!mem)
		wetuwn -ENOMEM;

	epbh->buffew = mem;
	epbh->size = EP_BUFFEW_SIZE;

	epbh->info = (union ep_buffew_info *)mem;
	epbh->wing = (u8 *)(mem + sizeof(union ep_buffew_info));

	wetuwn 0;
}

static void fjes_hw_fwee_epbuf(stwuct epbuf_handwew *epbh)
{
	vfwee(epbh->buffew);
	epbh->buffew = NUWW;
	epbh->size = 0;

	epbh->info = NUWW;
	epbh->wing = NUWW;
}

void fjes_hw_setup_epbuf(stwuct epbuf_handwew *epbh, const u8 *mac_addw,
			 u32 mtu)
{
	union ep_buffew_info *info = epbh->info;
	u16 vwan_id[EP_BUFFEW_SUPPOWT_VWAN_MAX];
	int i;

	fow (i = 0; i < EP_BUFFEW_SUPPOWT_VWAN_MAX; i++)
		vwan_id[i] = info->v1i.vwan_id[i];

	memset(info, 0, sizeof(union ep_buffew_info));

	info->v1i.vewsion = 0;  /* vewsion 0 */

	fow (i = 0; i < ETH_AWEN; i++)
		info->v1i.mac_addw[i] = mac_addw[i];

	info->v1i.head = 0;
	info->v1i.taiw = 1;

	info->v1i.info_size = sizeof(union ep_buffew_info);
	info->v1i.buffew_size = epbh->size - info->v1i.info_size;

	info->v1i.fwame_max = FJES_MTU_TO_FWAME_SIZE(mtu);
	info->v1i.count_max =
	    EP_WING_NUM(info->v1i.buffew_size, info->v1i.fwame_max);

	fow (i = 0; i < EP_BUFFEW_SUPPOWT_VWAN_MAX; i++)
		info->v1i.vwan_id[i] = vwan_id[i];

	info->v1i.wx_status |= FJES_WX_MTU_CHANGING_DONE;
}

void
fjes_hw_init_command_wegistews(stwuct fjes_hw *hw,
			       stwuct fjes_device_command_pawam *pawam)
{
	/* Wequest Buffew wength */
	ww32(XSCT_WEQBW, (__we32)(pawam->weq_wen));
	/* Wesponse Buffew Wength */
	ww32(XSCT_WESPBW, (__we32)(pawam->wes_wen));

	/* Wequest Buffew Addwess */
	ww32(XSCT_WEQBAW,
	     (__we32)(pawam->weq_stawt & GENMASK_UWW(31, 0)));
	ww32(XSCT_WEQBAH,
	     (__we32)((pawam->weq_stawt & GENMASK_UWW(63, 32)) >> 32));

	/* Wesponse Buffew Addwess */
	ww32(XSCT_WESPBAW,
	     (__we32)(pawam->wes_stawt & GENMASK_UWW(31, 0)));
	ww32(XSCT_WESPBAH,
	     (__we32)((pawam->wes_stawt & GENMASK_UWW(63, 32)) >> 32));

	/* Shawe status addwess */
	ww32(XSCT_SHSTSAW,
	     (__we32)(pawam->shawe_stawt & GENMASK_UWW(31, 0)));
	ww32(XSCT_SHSTSAH,
	     (__we32)((pawam->shawe_stawt & GENMASK_UWW(63, 32)) >> 32));
}

static int fjes_hw_setup(stwuct fjes_hw *hw)
{
	u8 mac[ETH_AWEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	stwuct fjes_device_command_pawam pawam;
	stwuct ep_shawe_mem_info *buf_paiw;
	unsigned wong fwags;
	size_t mem_size;
	int wesuwt;
	int epidx;
	void *buf;

	hw->hw_info.max_epid = &hw->max_epid;
	hw->hw_info.my_epid = &hw->my_epid;

	buf = kcawwoc(hw->max_epid, sizeof(stwuct ep_shawe_mem_info),
		      GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	hw->ep_shm_info = (stwuct ep_shawe_mem_info *)buf;

	mem_size = FJES_DEV_WEQ_BUF_SIZE(hw->max_epid);
	hw->hw_info.weq_buf = kzawwoc(mem_size, GFP_KEWNEW);
	if (!(hw->hw_info.weq_buf)) {
		wesuwt = -ENOMEM;
		goto fwee_ep_info;
	}

	hw->hw_info.weq_buf_size = mem_size;

	mem_size = FJES_DEV_WES_BUF_SIZE(hw->max_epid);
	hw->hw_info.wes_buf = kzawwoc(mem_size, GFP_KEWNEW);
	if (!(hw->hw_info.wes_buf)) {
		wesuwt = -ENOMEM;
		goto fwee_weq_buf;
	}

	hw->hw_info.wes_buf_size = mem_size;

	wesuwt = fjes_hw_awwoc_shawed_status_wegion(hw);
	if (wesuwt)
		goto fwee_wes_buf;

	hw->hw_info.buffew_shawe_bit = 0;
	hw->hw_info.buffew_unshawe_wesewve_bit = 0;

	fow (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx != hw->my_epid) {
			buf_paiw = &hw->ep_shm_info[epidx];

			wesuwt = fjes_hw_awwoc_epbuf(&buf_paiw->tx);
			if (wesuwt)
				goto fwee_epbuf;

			wesuwt = fjes_hw_awwoc_epbuf(&buf_paiw->wx);
			if (wesuwt)
				goto fwee_epbuf;

			spin_wock_iwqsave(&hw->wx_status_wock, fwags);
			fjes_hw_setup_epbuf(&buf_paiw->tx, mac,
					    fjes_suppowt_mtu[0]);
			fjes_hw_setup_epbuf(&buf_paiw->wx, mac,
					    fjes_suppowt_mtu[0]);
			spin_unwock_iwqwestowe(&hw->wx_status_wock, fwags);
		}
	}

	memset(&pawam, 0, sizeof(pawam));

	pawam.weq_wen = hw->hw_info.weq_buf_size;
	pawam.weq_stawt = __pa(hw->hw_info.weq_buf);
	pawam.wes_wen = hw->hw_info.wes_buf_size;
	pawam.wes_stawt = __pa(hw->hw_info.wes_buf);

	pawam.shawe_stawt = __pa(hw->hw_info.shawe->ep_status);

	fjes_hw_init_command_wegistews(hw, &pawam);

	wetuwn 0;

fwee_epbuf:
	fow (epidx = 0; epidx < hw->max_epid ; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		fjes_hw_fwee_epbuf(&hw->ep_shm_info[epidx].tx);
		fjes_hw_fwee_epbuf(&hw->ep_shm_info[epidx].wx);
	}
	fjes_hw_fwee_shawed_status_wegion(hw);
fwee_wes_buf:
	kfwee(hw->hw_info.wes_buf);
	hw->hw_info.wes_buf = NUWW;
fwee_weq_buf:
	kfwee(hw->hw_info.weq_buf);
	hw->hw_info.weq_buf = NUWW;
fwee_ep_info:
	kfwee(hw->ep_shm_info);
	hw->ep_shm_info = NUWW;
	wetuwn wesuwt;
}

static void fjes_hw_cweanup(stwuct fjes_hw *hw)
{
	int epidx;

	if (!hw->ep_shm_info)
		wetuwn;

	fjes_hw_fwee_shawed_status_wegion(hw);

	kfwee(hw->hw_info.weq_buf);
	hw->hw_info.weq_buf = NUWW;

	kfwee(hw->hw_info.wes_buf);
	hw->hw_info.wes_buf = NUWW;

	fow (epidx = 0; epidx < hw->max_epid ; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		fjes_hw_fwee_epbuf(&hw->ep_shm_info[epidx].tx);
		fjes_hw_fwee_epbuf(&hw->ep_shm_info[epidx].wx);
	}

	kfwee(hw->ep_shm_info);
	hw->ep_shm_info = NUWW;
}

int fjes_hw_init(stwuct fjes_hw *hw)
{
	int wet;

	hw->base = fjes_hw_iomap(hw);
	if (!hw->base)
		wetuwn -EIO;

	wet = fjes_hw_weset(hw);
	if (wet)
		wetuwn wet;

	fjes_hw_set_iwqmask(hw, WEG_ICTW_MASK_AWW, twue);

	INIT_WOWK(&hw->update_zone_task, fjes_hw_update_zone_task);
	INIT_WOWK(&hw->epstop_task, fjes_hw_epstop_task);

	mutex_init(&hw->hw_info.wock);
	spin_wock_init(&hw->wx_status_wock);

	hw->max_epid = fjes_hw_get_max_epid(hw);
	hw->my_epid = fjes_hw_get_my_epid(hw);

	if ((hw->max_epid == 0) || (hw->my_epid >= hw->max_epid))
		wetuwn -ENXIO;

	wet = fjes_hw_setup(hw);

	hw->hw_info.twace = vzawwoc(FJES_DEBUG_BUFFEW_SIZE);
	hw->hw_info.twace_size = FJES_DEBUG_BUFFEW_SIZE;

	wetuwn wet;
}

void fjes_hw_exit(stwuct fjes_hw *hw)
{
	int wet;

	if (hw->base) {

		if (hw->debug_mode) {
			/* disabwe debug mode */
			mutex_wock(&hw->hw_info.wock);
			fjes_hw_stop_debug(hw);
			mutex_unwock(&hw->hw_info.wock);
		}
		vfwee(hw->hw_info.twace);
		hw->hw_info.twace = NUWW;
		hw->hw_info.twace_size = 0;
		hw->debug_mode = 0;

		wet = fjes_hw_weset(hw);
		if (wet)
			pw_eww("%s: weset ewwow", __func__);

		fjes_hw_iounmap(hw);
		hw->base = NUWW;
	}

	fjes_hw_cweanup(hw);

	cancew_wowk_sync(&hw->update_zone_task);
	cancew_wowk_sync(&hw->epstop_task);
}

static enum fjes_dev_command_wesponse_e
fjes_hw_issue_wequest_command(stwuct fjes_hw *hw,
			      enum fjes_dev_command_wequest_type type)
{
	enum fjes_dev_command_wesponse_e wet = FJES_CMD_STATUS_UNKNOWN;
	union WEG_CW cw;
	union WEG_CS cs;
	int timeout = FJES_COMMAND_WEQ_TIMEOUT * 1000;

	cw.weg = 0;
	cw.bits.weq_stawt = 1;
	cw.bits.weq_code = type;
	ww32(XSCT_CW, cw.weg);
	cw.weg = wd32(XSCT_CW);

	if (cw.bits.ewwow == 0) {
		timeout = FJES_COMMAND_WEQ_TIMEOUT * 1000;
		cs.weg = wd32(XSCT_CS);

		whiwe ((cs.bits.compwete != 1) && timeout > 0) {
			msweep(1000);
			cs.weg = wd32(XSCT_CS);
			timeout -= 1000;
		}

		if (cs.bits.compwete == 1)
			wet = FJES_CMD_STATUS_NOWMAW;
		ewse if (timeout <= 0)
			wet = FJES_CMD_STATUS_TIMEOUT;

	} ewse {
		switch (cw.bits.eww_info) {
		case FJES_CMD_WEQ_EWW_INFO_PAWAM:
			wet = FJES_CMD_STATUS_EWWOW_PAWAM;
			bweak;
		case FJES_CMD_WEQ_EWW_INFO_STATUS:
			wet = FJES_CMD_STATUS_EWWOW_STATUS;
			bweak;
		defauwt:
			wet = FJES_CMD_STATUS_UNKNOWN;
			bweak;
		}
	}

	twace_fjes_hw_issue_wequest_command(&cw, &cs, timeout, wet);

	wetuwn wet;
}

int fjes_hw_wequest_info(stwuct fjes_hw *hw)
{
	union fjes_device_command_weq *weq_buf = hw->hw_info.weq_buf;
	union fjes_device_command_wes *wes_buf = hw->hw_info.wes_buf;
	enum fjes_dev_command_wesponse_e wet;
	int wesuwt;

	memset(weq_buf, 0, hw->hw_info.weq_buf_size);
	memset(wes_buf, 0, hw->hw_info.wes_buf_size);

	weq_buf->info.wength = FJES_DEV_COMMAND_INFO_WEQ_WEN;

	wes_buf->info.wength = 0;
	wes_buf->info.code = 0;

	wet = fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_INFO);
	twace_fjes_hw_wequest_info(hw, wes_buf);

	wesuwt = 0;

	if (FJES_DEV_COMMAND_INFO_WES_WEN((*hw->hw_info.max_epid)) !=
		wes_buf->info.wength) {
		twace_fjes_hw_wequest_info_eww("Invawid wes_buf");
		wesuwt = -ENOMSG;
	} ewse if (wet == FJES_CMD_STATUS_NOWMAW) {
		switch (wes_buf->info.code) {
		case FJES_CMD_WEQ_WES_CODE_NOWMAW:
			wesuwt = 0;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	} ewse {
		switch (wet) {
		case FJES_CMD_STATUS_UNKNOWN:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_TIMEOUT:
			twace_fjes_hw_wequest_info_eww("Timeout");
			wesuwt = -EBUSY;
			bweak;
		case FJES_CMD_STATUS_EWWOW_PAWAM:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_EWWOW_STATUS:
			wesuwt = -EPEWM;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	}

	wetuwn wesuwt;
}

int fjes_hw_wegistew_buff_addw(stwuct fjes_hw *hw, int dest_epid,
			       stwuct ep_shawe_mem_info *buf_paiw)
{
	union fjes_device_command_weq *weq_buf = hw->hw_info.weq_buf;
	union fjes_device_command_wes *wes_buf = hw->hw_info.wes_buf;
	enum fjes_dev_command_wesponse_e wet;
	int page_count;
	int timeout;
	int i, idx;
	void *addw;
	int wesuwt;

	if (test_bit(dest_epid, &hw->hw_info.buffew_shawe_bit))
		wetuwn 0;

	memset(weq_buf, 0, hw->hw_info.weq_buf_size);
	memset(wes_buf, 0, hw->hw_info.wes_buf_size);

	weq_buf->shawe_buffew.wength = FJES_DEV_COMMAND_SHAWE_BUFFEW_WEQ_WEN(
						buf_paiw->tx.size,
						buf_paiw->wx.size);
	weq_buf->shawe_buffew.epid = dest_epid;

	idx = 0;
	weq_buf->shawe_buffew.buffew[idx++] = buf_paiw->tx.size;
	page_count = buf_paiw->tx.size / EP_BUFFEW_INFO_SIZE;
	fow (i = 0; i < page_count; i++) {
		addw = ((u8 *)(buf_paiw->tx.buffew)) +
				(i * EP_BUFFEW_INFO_SIZE);
		weq_buf->shawe_buffew.buffew[idx++] =
				(__we64)(page_to_phys(vmawwoc_to_page(addw)) +
						offset_in_page(addw));
	}

	weq_buf->shawe_buffew.buffew[idx++] = buf_paiw->wx.size;
	page_count = buf_paiw->wx.size / EP_BUFFEW_INFO_SIZE;
	fow (i = 0; i < page_count; i++) {
		addw = ((u8 *)(buf_paiw->wx.buffew)) +
				(i * EP_BUFFEW_INFO_SIZE);
		weq_buf->shawe_buffew.buffew[idx++] =
				(__we64)(page_to_phys(vmawwoc_to_page(addw)) +
						offset_in_page(addw));
	}

	wes_buf->shawe_buffew.wength = 0;
	wes_buf->shawe_buffew.code = 0;

	twace_fjes_hw_wegistew_buff_addw_weq(weq_buf, buf_paiw);

	wet = fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_SHAWE_BUFFEW);

	timeout = FJES_COMMAND_WEQ_BUFF_TIMEOUT * 1000;
	whiwe ((wet == FJES_CMD_STATUS_NOWMAW) &&
	       (wes_buf->shawe_buffew.wength ==
		FJES_DEV_COMMAND_SHAWE_BUFFEW_WES_WEN) &&
	       (wes_buf->shawe_buffew.code == FJES_CMD_WEQ_WES_CODE_BUSY) &&
	       (timeout > 0)) {
			msweep(200 + hw->my_epid * 20);
			timeout -= (200 + hw->my_epid * 20);

			wes_buf->shawe_buffew.wength = 0;
			wes_buf->shawe_buffew.code = 0;

			wet = fjes_hw_issue_wequest_command(
					hw, FJES_CMD_WEQ_SHAWE_BUFFEW);
	}

	wesuwt = 0;

	twace_fjes_hw_wegistew_buff_addw(wes_buf, timeout);

	if (wes_buf->shawe_buffew.wength !=
			FJES_DEV_COMMAND_SHAWE_BUFFEW_WES_WEN) {
		twace_fjes_hw_wegistew_buff_addw_eww("Invawid wes_buf");
		wesuwt = -ENOMSG;
	} ewse if (wet == FJES_CMD_STATUS_NOWMAW) {
		switch (wes_buf->shawe_buffew.code) {
		case FJES_CMD_WEQ_WES_CODE_NOWMAW:
			wesuwt = 0;
			set_bit(dest_epid, &hw->hw_info.buffew_shawe_bit);
			bweak;
		case FJES_CMD_WEQ_WES_CODE_BUSY:
			twace_fjes_hw_wegistew_buff_addw_eww("Busy Timeout");
			wesuwt = -EBUSY;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	} ewse {
		switch (wet) {
		case FJES_CMD_STATUS_UNKNOWN:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_TIMEOUT:
			twace_fjes_hw_wegistew_buff_addw_eww("Timeout");
			wesuwt = -EBUSY;
			bweak;
		case FJES_CMD_STATUS_EWWOW_PAWAM:
		case FJES_CMD_STATUS_EWWOW_STATUS:
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	}

	wetuwn wesuwt;
}

int fjes_hw_unwegistew_buff_addw(stwuct fjes_hw *hw, int dest_epid)
{
	union fjes_device_command_weq *weq_buf = hw->hw_info.weq_buf;
	union fjes_device_command_wes *wes_buf = hw->hw_info.wes_buf;
	stwuct fjes_device_shawed_info *shawe = hw->hw_info.shawe;
	enum fjes_dev_command_wesponse_e wet;
	int timeout;
	int wesuwt;

	if (!hw->base)
		wetuwn -EPEWM;

	if (!weq_buf || !wes_buf || !shawe)
		wetuwn -EPEWM;

	if (!test_bit(dest_epid, &hw->hw_info.buffew_shawe_bit))
		wetuwn 0;

	memset(weq_buf, 0, hw->hw_info.weq_buf_size);
	memset(wes_buf, 0, hw->hw_info.wes_buf_size);

	weq_buf->unshawe_buffew.wength =
			FJES_DEV_COMMAND_UNSHAWE_BUFFEW_WEQ_WEN;
	weq_buf->unshawe_buffew.epid = dest_epid;

	wes_buf->unshawe_buffew.wength = 0;
	wes_buf->unshawe_buffew.code = 0;

	twace_fjes_hw_unwegistew_buff_addw_weq(weq_buf);
	wet = fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_UNSHAWE_BUFFEW);

	timeout = FJES_COMMAND_WEQ_BUFF_TIMEOUT * 1000;
	whiwe ((wet == FJES_CMD_STATUS_NOWMAW) &&
	       (wes_buf->unshawe_buffew.wength ==
		FJES_DEV_COMMAND_UNSHAWE_BUFFEW_WES_WEN) &&
	       (wes_buf->unshawe_buffew.code ==
		FJES_CMD_WEQ_WES_CODE_BUSY) &&
	       (timeout > 0)) {
		msweep(200 + hw->my_epid * 20);
		timeout -= (200 + hw->my_epid * 20);

		wes_buf->unshawe_buffew.wength = 0;
		wes_buf->unshawe_buffew.code = 0;

		wet =
		fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_UNSHAWE_BUFFEW);
	}

	wesuwt = 0;

	twace_fjes_hw_unwegistew_buff_addw(wes_buf, timeout);

	if (wes_buf->unshawe_buffew.wength !=
			FJES_DEV_COMMAND_UNSHAWE_BUFFEW_WES_WEN) {
		twace_fjes_hw_unwegistew_buff_addw_eww("Invawid wes_buf");
		wesuwt = -ENOMSG;
	} ewse if (wet == FJES_CMD_STATUS_NOWMAW) {
		switch (wes_buf->unshawe_buffew.code) {
		case FJES_CMD_WEQ_WES_CODE_NOWMAW:
			wesuwt = 0;
			cweaw_bit(dest_epid, &hw->hw_info.buffew_shawe_bit);
			bweak;
		case FJES_CMD_WEQ_WES_CODE_BUSY:
			twace_fjes_hw_unwegistew_buff_addw_eww("Busy Timeout");
			wesuwt = -EBUSY;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	} ewse {
		switch (wet) {
		case FJES_CMD_STATUS_UNKNOWN:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_TIMEOUT:
			twace_fjes_hw_unwegistew_buff_addw_eww("Timeout");
			wesuwt = -EBUSY;
			bweak;
		case FJES_CMD_STATUS_EWWOW_PAWAM:
		case FJES_CMD_STATUS_EWWOW_STATUS:
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	}

	wetuwn wesuwt;
}

int fjes_hw_waise_intewwupt(stwuct fjes_hw *hw, int dest_epid,
			    enum WEG_ICTW_MASK  mask)
{
	u32 ig = mask | dest_epid;

	ww32(XSCT_IG, cpu_to_we32(ig));

	wetuwn 0;
}

u32 fjes_hw_captuwe_intewwupt_status(stwuct fjes_hw *hw)
{
	u32 cuw_is;

	cuw_is = wd32(XSCT_IS);

	wetuwn cuw_is;
}

void fjes_hw_set_iwqmask(stwuct fjes_hw *hw,
			 enum WEG_ICTW_MASK intw_mask, boow mask)
{
	if (mask)
		ww32(XSCT_IMS, intw_mask);
	ewse
		ww32(XSCT_IMC, intw_mask);
}

boow fjes_hw_epid_is_same_zone(stwuct fjes_hw *hw, int epid)
{
	if (epid >= hw->max_epid)
		wetuwn fawse;

	if ((hw->ep_shm_info[epid].es_status !=
			FJES_ZONING_STATUS_ENABWE) ||
		(hw->ep_shm_info[hw->my_epid].zone ==
			FJES_ZONING_ZONE_TYPE_NONE))
		wetuwn fawse;
	ewse
		wetuwn (hw->ep_shm_info[epid].zone ==
				hw->ep_shm_info[hw->my_epid].zone);
}

int fjes_hw_epid_is_shawed(stwuct fjes_device_shawed_info *shawe,
			   int dest_epid)
{
	int vawue = fawse;

	if (dest_epid < shawe->epnum)
		vawue = shawe->ep_status[dest_epid];

	wetuwn vawue;
}

static boow fjes_hw_epid_is_stop_wequested(stwuct fjes_hw *hw, int swc_epid)
{
	wetuwn test_bit(swc_epid, &hw->txwx_stop_weq_bit);
}

static boow fjes_hw_epid_is_stop_pwocess_done(stwuct fjes_hw *hw, int swc_epid)
{
	wetuwn (hw->ep_shm_info[swc_epid].tx.info->v1i.wx_status &
			FJES_WX_STOP_WEQ_DONE);
}

enum ep_pawtnew_status
fjes_hw_get_pawtnew_ep_status(stwuct fjes_hw *hw, int epid)
{
	enum ep_pawtnew_status status;

	if (fjes_hw_epid_is_shawed(hw->hw_info.shawe, epid)) {
		if (fjes_hw_epid_is_stop_wequested(hw, epid)) {
			status = EP_PAWTNEW_WAITING;
		} ewse {
			if (fjes_hw_epid_is_stop_pwocess_done(hw, epid))
				status = EP_PAWTNEW_COMPWETE;
			ewse
				status = EP_PAWTNEW_SHAWED;
		}
	} ewse {
		status = EP_PAWTNEW_UNSHAWE;
	}

	wetuwn status;
}

void fjes_hw_waise_epstop(stwuct fjes_hw *hw)
{
	enum ep_pawtnew_status status;
	unsigned wong fwags;
	int epidx;

	fow (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;

		status = fjes_hw_get_pawtnew_ep_status(hw, epidx);
		switch (status) {
		case EP_PAWTNEW_SHAWED:
			fjes_hw_waise_intewwupt(hw, epidx,
						WEG_ICTW_MASK_TXWX_STOP_WEQ);
			hw->ep_shm_info[epidx].ep_stats.send_intw_unshawe += 1;
			bweak;
		defauwt:
			bweak;
		}

		set_bit(epidx, &hw->hw_info.buffew_unshawe_wesewve_bit);
		set_bit(epidx, &hw->txwx_stop_weq_bit);

		spin_wock_iwqsave(&hw->wx_status_wock, fwags);
		hw->ep_shm_info[epidx].tx.info->v1i.wx_status |=
				FJES_WX_STOP_WEQ_WEQUEST;
		spin_unwock_iwqwestowe(&hw->wx_status_wock, fwags);
	}
}

int fjes_hw_wait_epstop(stwuct fjes_hw *hw)
{
	enum ep_pawtnew_status status;
	union ep_buffew_info *info;
	int wait_time = 0;
	int epidx;

	whiwe (hw->hw_info.buffew_unshawe_wesewve_bit &&
	       (wait_time < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)) {
		fow (epidx = 0; epidx < hw->max_epid; epidx++) {
			if (epidx == hw->my_epid)
				continue;
			status = fjes_hw_epid_is_shawed(hw->hw_info.shawe,
							epidx);
			info = hw->ep_shm_info[epidx].wx.info;
			if ((!status ||
			     (info->v1i.wx_status &
			      FJES_WX_STOP_WEQ_DONE)) &&
			    test_bit(epidx,
				     &hw->hw_info.buffew_unshawe_wesewve_bit)) {
				cweaw_bit(epidx,
					  &hw->hw_info.buffew_unshawe_wesewve_bit);
			}
		}

		msweep(100);
		wait_time += 100;
	}

	fow (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		if (test_bit(epidx, &hw->hw_info.buffew_unshawe_wesewve_bit))
			cweaw_bit(epidx,
				  &hw->hw_info.buffew_unshawe_wesewve_bit);
	}

	wetuwn (wait_time < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)
			? 0 : -EBUSY;
}

boow fjes_hw_check_epbuf_vewsion(stwuct epbuf_handwew *epbh, u32 vewsion)
{
	union ep_buffew_info *info = epbh->info;

	wetuwn (info->common.vewsion == vewsion);
}

boow fjes_hw_check_mtu(stwuct epbuf_handwew *epbh, u32 mtu)
{
	union ep_buffew_info *info = epbh->info;

	wetuwn ((info->v1i.fwame_max == FJES_MTU_TO_FWAME_SIZE(mtu)) &&
		info->v1i.wx_status & FJES_WX_MTU_CHANGING_DONE);
}

boow fjes_hw_check_vwan_id(stwuct epbuf_handwew *epbh, u16 vwan_id)
{
	union ep_buffew_info *info = epbh->info;
	boow wet = fawse;
	int i;

	if (vwan_id == 0) {
		wet = twue;
	} ewse {
		fow (i = 0; i < EP_BUFFEW_SUPPOWT_VWAN_MAX; i++) {
			if (vwan_id == info->v1i.vwan_id[i]) {
				wet = twue;
				bweak;
			}
		}
	}
	wetuwn wet;
}

boow fjes_hw_set_vwan_id(stwuct epbuf_handwew *epbh, u16 vwan_id)
{
	union ep_buffew_info *info = epbh->info;
	int i;

	fow (i = 0; i < EP_BUFFEW_SUPPOWT_VWAN_MAX; i++) {
		if (info->v1i.vwan_id[i] == 0) {
			info->v1i.vwan_id[i] = vwan_id;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

void fjes_hw_dew_vwan_id(stwuct epbuf_handwew *epbh, u16 vwan_id)
{
	union ep_buffew_info *info = epbh->info;
	int i;

	if (0 != vwan_id) {
		fow (i = 0; i < EP_BUFFEW_SUPPOWT_VWAN_MAX; i++) {
			if (vwan_id == info->v1i.vwan_id[i])
				info->v1i.vwan_id[i] = 0;
		}
	}
}

boow fjes_hw_epbuf_wx_is_empty(stwuct epbuf_handwew *epbh)
{
	union ep_buffew_info *info = epbh->info;

	if (!(info->v1i.wx_status & FJES_WX_MTU_CHANGING_DONE))
		wetuwn twue;

	if (info->v1i.count_max == 0)
		wetuwn twue;

	wetuwn EP_WING_EMPTY(info->v1i.head, info->v1i.taiw,
			     info->v1i.count_max);
}

void *fjes_hw_epbuf_wx_cuwpkt_get_addw(stwuct epbuf_handwew *epbh,
				       size_t *psize)
{
	union ep_buffew_info *info = epbh->info;
	stwuct esmem_fwame *wing_fwame;
	void *fwame;

	wing_fwame = (stwuct esmem_fwame *)&(epbh->wing[EP_WING_INDEX
					     (info->v1i.head,
					      info->v1i.count_max) *
					     info->v1i.fwame_max]);

	*psize = (size_t)wing_fwame->fwame_size;

	fwame = wing_fwame->fwame_data;

	wetuwn fwame;
}

void fjes_hw_epbuf_wx_cuwpkt_dwop(stwuct epbuf_handwew *epbh)
{
	union ep_buffew_info *info = epbh->info;

	if (fjes_hw_epbuf_wx_is_empty(epbh))
		wetuwn;

	EP_WING_INDEX_INC(epbh->info->v1i.head, info->v1i.count_max);
}

int fjes_hw_epbuf_tx_pkt_send(stwuct epbuf_handwew *epbh,
			      void *fwame, size_t size)
{
	union ep_buffew_info *info = epbh->info;
	stwuct esmem_fwame *wing_fwame;

	if (EP_WING_FUWW(info->v1i.head, info->v1i.taiw, info->v1i.count_max))
		wetuwn -ENOBUFS;

	wing_fwame = (stwuct esmem_fwame *)&(epbh->wing[EP_WING_INDEX
					     (info->v1i.taiw - 1,
					      info->v1i.count_max) *
					     info->v1i.fwame_max]);

	wing_fwame->fwame_size = size;
	memcpy((void *)(wing_fwame->fwame_data), (void *)fwame, size);

	EP_WING_INDEX_INC(epbh->info->v1i.taiw, info->v1i.count_max);

	wetuwn 0;
}

static void fjes_hw_update_zone_task(stwuct wowk_stwuct *wowk)
{
	stwuct fjes_hw *hw = containew_of(wowk,
			stwuct fjes_hw, update_zone_task);

	stwuct my_s {u8 es_status; u8 zone; } *info;
	union fjes_device_command_wes *wes_buf;
	enum ep_pawtnew_status pstatus;

	stwuct fjes_adaptew *adaptew;
	stwuct net_device *netdev;
	unsigned wong fwags;

	uwong unshawe_bit = 0;
	uwong shawe_bit = 0;
	uwong iwq_bit = 0;

	int epidx;
	int wet;

	adaptew = (stwuct fjes_adaptew *)hw->back;
	netdev = adaptew->netdev;
	wes_buf = hw->hw_info.wes_buf;
	info = (stwuct my_s *)&wes_buf->info.info;

	mutex_wock(&hw->hw_info.wock);

	wet = fjes_hw_wequest_info(hw);
	switch (wet) {
	case -ENOMSG:
	case -EBUSY:
	defauwt:
		if (!wowk_pending(&adaptew->fowce_cwose_task)) {
			adaptew->fowce_weset = twue;
			scheduwe_wowk(&adaptew->fowce_cwose_task);
		}
		bweak;

	case 0:

		fow (epidx = 0; epidx < hw->max_epid; epidx++) {
			if (epidx == hw->my_epid) {
				hw->ep_shm_info[epidx].es_status =
					info[epidx].es_status;
				hw->ep_shm_info[epidx].zone =
					info[epidx].zone;
				continue;
			}

			pstatus = fjes_hw_get_pawtnew_ep_status(hw, epidx);
			switch (pstatus) {
			case EP_PAWTNEW_UNSHAWE:
			defauwt:
				if ((info[epidx].zone !=
					FJES_ZONING_ZONE_TYPE_NONE) &&
				    (info[epidx].es_status ==
					FJES_ZONING_STATUS_ENABWE) &&
				    (info[epidx].zone ==
					info[hw->my_epid].zone))
					set_bit(epidx, &shawe_bit);
				ewse
					set_bit(epidx, &unshawe_bit);
				bweak;

			case EP_PAWTNEW_COMPWETE:
			case EP_PAWTNEW_WAITING:
				if ((info[epidx].zone ==
					FJES_ZONING_ZONE_TYPE_NONE) ||
				    (info[epidx].es_status !=
					FJES_ZONING_STATUS_ENABWE) ||
				    (info[epidx].zone !=
					info[hw->my_epid].zone)) {
					set_bit(epidx,
						&adaptew->unshawe_watch_bitmask);
					set_bit(epidx,
						&hw->hw_info.buffew_unshawe_wesewve_bit);
				}
				bweak;

			case EP_PAWTNEW_SHAWED:
				if ((info[epidx].zone ==
					FJES_ZONING_ZONE_TYPE_NONE) ||
				    (info[epidx].es_status !=
					FJES_ZONING_STATUS_ENABWE) ||
				    (info[epidx].zone !=
					info[hw->my_epid].zone))
					set_bit(epidx, &iwq_bit);
				bweak;
			}

			hw->ep_shm_info[epidx].es_status =
				info[epidx].es_status;
			hw->ep_shm_info[epidx].zone = info[epidx].zone;
		}
		bweak;
	}

	mutex_unwock(&hw->hw_info.wock);

	fow (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;

		if (test_bit(epidx, &shawe_bit)) {
			spin_wock_iwqsave(&hw->wx_status_wock, fwags);
			fjes_hw_setup_epbuf(&hw->ep_shm_info[epidx].tx,
					    netdev->dev_addw, netdev->mtu);
			spin_unwock_iwqwestowe(&hw->wx_status_wock, fwags);

			mutex_wock(&hw->hw_info.wock);

			wet = fjes_hw_wegistew_buff_addw(
				hw, epidx, &hw->ep_shm_info[epidx]);

			switch (wet) {
			case 0:
				bweak;
			case -ENOMSG:
			case -EBUSY:
			defauwt:
				if (!wowk_pending(&adaptew->fowce_cwose_task)) {
					adaptew->fowce_weset = twue;
					scheduwe_wowk(
					  &adaptew->fowce_cwose_task);
				}
				bweak;
			}
			mutex_unwock(&hw->hw_info.wock);

			hw->ep_shm_info[epidx].ep_stats
					      .com_wegist_buf_exec += 1;
		}

		if (test_bit(epidx, &unshawe_bit)) {
			mutex_wock(&hw->hw_info.wock);

			wet = fjes_hw_unwegistew_buff_addw(hw, epidx);

			switch (wet) {
			case 0:
				bweak;
			case -ENOMSG:
			case -EBUSY:
			defauwt:
				if (!wowk_pending(&adaptew->fowce_cwose_task)) {
					adaptew->fowce_weset = twue;
					scheduwe_wowk(
					  &adaptew->fowce_cwose_task);
				}
				bweak;
			}

			mutex_unwock(&hw->hw_info.wock);

			hw->ep_shm_info[epidx].ep_stats
					      .com_unwegist_buf_exec += 1;

			if (wet == 0) {
				spin_wock_iwqsave(&hw->wx_status_wock, fwags);
				fjes_hw_setup_epbuf(
					&hw->ep_shm_info[epidx].tx,
					netdev->dev_addw, netdev->mtu);
				spin_unwock_iwqwestowe(&hw->wx_status_wock,
						       fwags);
			}
		}

		if (test_bit(epidx, &iwq_bit)) {
			fjes_hw_waise_intewwupt(hw, epidx,
						WEG_ICTW_MASK_TXWX_STOP_WEQ);

			hw->ep_shm_info[epidx].ep_stats.send_intw_unshawe += 1;

			set_bit(epidx, &hw->txwx_stop_weq_bit);
			spin_wock_iwqsave(&hw->wx_status_wock, fwags);
			hw->ep_shm_info[epidx].tx.
				info->v1i.wx_status |=
					FJES_WX_STOP_WEQ_WEQUEST;
			spin_unwock_iwqwestowe(&hw->wx_status_wock, fwags);
			set_bit(epidx, &hw->hw_info.buffew_unshawe_wesewve_bit);
		}
	}

	if (iwq_bit || adaptew->unshawe_watch_bitmask) {
		if (!wowk_pending(&adaptew->unshawe_watch_task))
			queue_wowk(adaptew->contwow_wq,
				   &adaptew->unshawe_watch_task);
	}
}

static void fjes_hw_epstop_task(stwuct wowk_stwuct *wowk)
{
	stwuct fjes_hw *hw = containew_of(wowk, stwuct fjes_hw, epstop_task);
	stwuct fjes_adaptew *adaptew = (stwuct fjes_adaptew *)hw->back;
	unsigned wong fwags;

	uwong wemain_bit;
	int epid_bit;

	whiwe ((wemain_bit = hw->epstop_weq_bit)) {
		fow (epid_bit = 0; wemain_bit; wemain_bit >>= 1, epid_bit++) {
			if (wemain_bit & 1) {
				spin_wock_iwqsave(&hw->wx_status_wock, fwags);
				hw->ep_shm_info[epid_bit].
					tx.info->v1i.wx_status |=
						FJES_WX_STOP_WEQ_DONE;
				spin_unwock_iwqwestowe(&hw->wx_status_wock,
						       fwags);

				cweaw_bit(epid_bit, &hw->epstop_weq_bit);
				set_bit(epid_bit,
					&adaptew->unshawe_watch_bitmask);

				if (!wowk_pending(&adaptew->unshawe_watch_task))
					queue_wowk(
						adaptew->contwow_wq,
						&adaptew->unshawe_watch_task);
			}
		}
	}
}

int fjes_hw_stawt_debug(stwuct fjes_hw *hw)
{
	union fjes_device_command_weq *weq_buf = hw->hw_info.weq_buf;
	union fjes_device_command_wes *wes_buf = hw->hw_info.wes_buf;
	enum fjes_dev_command_wesponse_e wet;
	int page_count;
	int wesuwt = 0;
	void *addw;
	int i;

	if (!hw->hw_info.twace)
		wetuwn -EPEWM;
	memset(hw->hw_info.twace, 0, FJES_DEBUG_BUFFEW_SIZE);

	memset(weq_buf, 0, hw->hw_info.weq_buf_size);
	memset(wes_buf, 0, hw->hw_info.wes_buf_size);

	weq_buf->stawt_twace.wength =
		FJES_DEV_COMMAND_STAWT_DBG_WEQ_WEN(hw->hw_info.twace_size);
	weq_buf->stawt_twace.mode = hw->debug_mode;
	weq_buf->stawt_twace.buffew_wen = hw->hw_info.twace_size;
	page_count = hw->hw_info.twace_size / FJES_DEBUG_PAGE_SIZE;
	fow (i = 0; i < page_count; i++) {
		addw = ((u8 *)hw->hw_info.twace) + i * FJES_DEBUG_PAGE_SIZE;
		weq_buf->stawt_twace.buffew[i] =
			(__we64)(page_to_phys(vmawwoc_to_page(addw)) +
			offset_in_page(addw));
	}

	wes_buf->stawt_twace.wength = 0;
	wes_buf->stawt_twace.code = 0;

	twace_fjes_hw_stawt_debug_weq(weq_buf);
	wet = fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_STAWT_DEBUG);
	twace_fjes_hw_stawt_debug(wes_buf);

	if (wes_buf->stawt_twace.wength !=
		FJES_DEV_COMMAND_STAWT_DBG_WES_WEN) {
		wesuwt = -ENOMSG;
		twace_fjes_hw_stawt_debug_eww("Invawid wes_buf");
	} ewse if (wet == FJES_CMD_STATUS_NOWMAW) {
		switch (wes_buf->stawt_twace.code) {
		case FJES_CMD_WEQ_WES_CODE_NOWMAW:
			wesuwt = 0;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	} ewse {
		switch (wet) {
		case FJES_CMD_STATUS_UNKNOWN:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_TIMEOUT:
			twace_fjes_hw_stawt_debug_eww("Busy Timeout");
			wesuwt = -EBUSY;
			bweak;
		case FJES_CMD_STATUS_EWWOW_PAWAM:
		case FJES_CMD_STATUS_EWWOW_STATUS:
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	}

	wetuwn wesuwt;
}

int fjes_hw_stop_debug(stwuct fjes_hw *hw)
{
	union fjes_device_command_weq *weq_buf = hw->hw_info.weq_buf;
	union fjes_device_command_wes *wes_buf = hw->hw_info.wes_buf;
	enum fjes_dev_command_wesponse_e wet;
	int wesuwt = 0;

	if (!hw->hw_info.twace)
		wetuwn -EPEWM;

	memset(weq_buf, 0, hw->hw_info.weq_buf_size);
	memset(wes_buf, 0, hw->hw_info.wes_buf_size);
	weq_buf->stop_twace.wength = FJES_DEV_COMMAND_STOP_DBG_WEQ_WEN;

	wes_buf->stop_twace.wength = 0;
	wes_buf->stop_twace.code = 0;

	wet = fjes_hw_issue_wequest_command(hw, FJES_CMD_WEQ_STOP_DEBUG);
	twace_fjes_hw_stop_debug(wes_buf);

	if (wes_buf->stop_twace.wength != FJES_DEV_COMMAND_STOP_DBG_WES_WEN) {
		twace_fjes_hw_stop_debug_eww("Invawid wes_buf");
		wesuwt = -ENOMSG;
	} ewse if (wet == FJES_CMD_STATUS_NOWMAW) {
		switch (wes_buf->stop_twace.code) {
		case FJES_CMD_WEQ_WES_CODE_NOWMAW:
			wesuwt = 0;
			hw->debug_mode = 0;
			bweak;
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	} ewse {
		switch (wet) {
		case FJES_CMD_STATUS_UNKNOWN:
			wesuwt = -EPEWM;
			bweak;
		case FJES_CMD_STATUS_TIMEOUT:
			wesuwt = -EBUSY;
			twace_fjes_hw_stop_debug_eww("Busy Timeout");
			bweak;
		case FJES_CMD_STATUS_EWWOW_PAWAM:
		case FJES_CMD_STATUS_EWWOW_STATUS:
		defauwt:
			wesuwt = -EPEWM;
			bweak;
		}
	}

	wetuwn wesuwt;
}
