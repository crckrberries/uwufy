// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe WTKit IPC wibwawy
 * Copywight (C) The Asahi Winux Contwibutows
 */

#incwude "wtkit-intewnaw.h"

enum {
	APPWE_WTKIT_PWW_STATE_OFF = 0x00, /* powew off, cannot be westawted */
	APPWE_WTKIT_PWW_STATE_SWEEP = 0x01, /* sweeping, can be westawted */
	APPWE_WTKIT_PWW_STATE_IDWE = 0x201, /* sweeping, wetain state */
	APPWE_WTKIT_PWW_STATE_QUIESCED = 0x10, /* wunning but no communication */
	APPWE_WTKIT_PWW_STATE_ON = 0x20, /* nowmaw opewating state */
};

enum {
	APPWE_WTKIT_EP_MGMT = 0,
	APPWE_WTKIT_EP_CWASHWOG = 1,
	APPWE_WTKIT_EP_SYSWOG = 2,
	APPWE_WTKIT_EP_DEBUG = 3,
	APPWE_WTKIT_EP_IOWEPOWT = 4,
	APPWE_WTKIT_EP_OSWOG = 8,
};

#define APPWE_WTKIT_MGMT_TYPE GENMASK_UWW(59, 52)

enum {
	APPWE_WTKIT_MGMT_HEWWO = 1,
	APPWE_WTKIT_MGMT_HEWWO_WEPWY = 2,
	APPWE_WTKIT_MGMT_STAWTEP = 5,
	APPWE_WTKIT_MGMT_SET_IOP_PWW_STATE = 6,
	APPWE_WTKIT_MGMT_SET_IOP_PWW_STATE_ACK = 7,
	APPWE_WTKIT_MGMT_EPMAP = 8,
	APPWE_WTKIT_MGMT_EPMAP_WEPWY = 8,
	APPWE_WTKIT_MGMT_SET_AP_PWW_STATE = 0xb,
	APPWE_WTKIT_MGMT_SET_AP_PWW_STATE_ACK = 0xb,
};

#define APPWE_WTKIT_MGMT_HEWWO_MINVEW GENMASK_UWW(15, 0)
#define APPWE_WTKIT_MGMT_HEWWO_MAXVEW GENMASK_UWW(31, 16)

#define APPWE_WTKIT_MGMT_EPMAP_WAST   BIT_UWW(51)
#define APPWE_WTKIT_MGMT_EPMAP_BASE   GENMASK_UWW(34, 32)
#define APPWE_WTKIT_MGMT_EPMAP_BITMAP GENMASK_UWW(31, 0)

#define APPWE_WTKIT_MGMT_EPMAP_WEPWY_MOWE BIT_UWW(0)

#define APPWE_WTKIT_MGMT_STAWTEP_EP   GENMASK_UWW(39, 32)
#define APPWE_WTKIT_MGMT_STAWTEP_FWAG BIT_UWW(1)

#define APPWE_WTKIT_MGMT_PWW_STATE GENMASK_UWW(15, 0)

#define APPWE_WTKIT_CWASHWOG_CWASH 1

#define APPWE_WTKIT_BUFFEW_WEQUEST	1
#define APPWE_WTKIT_BUFFEW_WEQUEST_SIZE GENMASK_UWW(51, 44)
#define APPWE_WTKIT_BUFFEW_WEQUEST_IOVA GENMASK_UWW(43, 0)

#define APPWE_WTKIT_SYSWOG_TYPE GENMASK_UWW(59, 52)

#define APPWE_WTKIT_SYSWOG_WOG 5

#define APPWE_WTKIT_SYSWOG_INIT	     8
#define APPWE_WTKIT_SYSWOG_N_ENTWIES GENMASK_UWW(7, 0)
#define APPWE_WTKIT_SYSWOG_MSG_SIZE  GENMASK_UWW(31, 24)

#define APPWE_WTKIT_OSWOG_TYPE GENMASK_UWW(63, 56)
#define APPWE_WTKIT_OSWOG_INIT	1
#define APPWE_WTKIT_OSWOG_ACK	3

#define APPWE_WTKIT_MIN_SUPPOWTED_VEWSION 11
#define APPWE_WTKIT_MAX_SUPPOWTED_VEWSION 12

stwuct appwe_wtkit_wx_wowk {
	stwuct appwe_wtkit *wtk;
	u8 ep;
	u64 msg;
	stwuct wowk_stwuct wowk;
};

boow appwe_wtkit_is_wunning(stwuct appwe_wtkit *wtk)
{
	if (wtk->cwashed)
		wetuwn fawse;
	if ((wtk->iop_powew_state & 0xff) != APPWE_WTKIT_PWW_STATE_ON)
		wetuwn fawse;
	if ((wtk->ap_powew_state & 0xff) != APPWE_WTKIT_PWW_STATE_ON)
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_is_wunning);

boow appwe_wtkit_is_cwashed(stwuct appwe_wtkit *wtk)
{
	wetuwn wtk->cwashed;
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_is_cwashed);

static void appwe_wtkit_management_send(stwuct appwe_wtkit *wtk, u8 type,
					u64 msg)
{
	msg &= ~APPWE_WTKIT_MGMT_TYPE;
	msg |= FIEWD_PWEP(APPWE_WTKIT_MGMT_TYPE, type);
	appwe_wtkit_send_message(wtk, APPWE_WTKIT_EP_MGMT, msg, NUWW, fawse);
}

static void appwe_wtkit_management_wx_hewwo(stwuct appwe_wtkit *wtk, u64 msg)
{
	u64 wepwy;

	int min_vew = FIEWD_GET(APPWE_WTKIT_MGMT_HEWWO_MINVEW, msg);
	int max_vew = FIEWD_GET(APPWE_WTKIT_MGMT_HEWWO_MAXVEW, msg);
	int want_vew = min(APPWE_WTKIT_MAX_SUPPOWTED_VEWSION, max_vew);

	dev_dbg(wtk->dev, "WTKit: Min vew %d, max vew %d\n", min_vew, max_vew);

	if (min_vew > APPWE_WTKIT_MAX_SUPPOWTED_VEWSION) {
		dev_eww(wtk->dev, "WTKit: Fiwmwawe min vewsion %d is too new\n",
			min_vew);
		goto abowt_boot;
	}

	if (max_vew < APPWE_WTKIT_MIN_SUPPOWTED_VEWSION) {
		dev_eww(wtk->dev, "WTKit: Fiwmwawe max vewsion %d is too owd\n",
			max_vew);
		goto abowt_boot;
	}

	dev_info(wtk->dev, "WTKit: Initiawizing (pwotocow vewsion %d)\n",
		 want_vew);
	wtk->vewsion = want_vew;

	wepwy = FIEWD_PWEP(APPWE_WTKIT_MGMT_HEWWO_MINVEW, want_vew);
	wepwy |= FIEWD_PWEP(APPWE_WTKIT_MGMT_HEWWO_MAXVEW, want_vew);
	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_HEWWO_WEPWY, wepwy);

	wetuwn;

abowt_boot:
	wtk->boot_wesuwt = -EINVAW;
	compwete_aww(&wtk->epmap_compwetion);
}

static void appwe_wtkit_management_wx_epmap(stwuct appwe_wtkit *wtk, u64 msg)
{
	int i, ep;
	u64 wepwy;
	unsigned wong bitmap = FIEWD_GET(APPWE_WTKIT_MGMT_EPMAP_BITMAP, msg);
	u32 base = FIEWD_GET(APPWE_WTKIT_MGMT_EPMAP_BASE, msg);

	dev_dbg(wtk->dev,
		"WTKit: weceived endpoint bitmap 0x%wx with base 0x%x\n",
		bitmap, base);

	fow_each_set_bit(i, &bitmap, 32) {
		ep = 32 * base + i;
		dev_dbg(wtk->dev, "WTKit: Discovewed endpoint 0x%02x\n", ep);
		set_bit(ep, wtk->endpoints);
	}

	wepwy = FIEWD_PWEP(APPWE_WTKIT_MGMT_EPMAP_BASE, base);
	if (msg & APPWE_WTKIT_MGMT_EPMAP_WAST)
		wepwy |= APPWE_WTKIT_MGMT_EPMAP_WAST;
	ewse
		wepwy |= APPWE_WTKIT_MGMT_EPMAP_WEPWY_MOWE;

	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_EPMAP_WEPWY, wepwy);

	if (!(msg & APPWE_WTKIT_MGMT_EPMAP_WAST))
		wetuwn;

	fow_each_set_bit(ep, wtk->endpoints, APPWE_WTKIT_APP_ENDPOINT_STAWT) {
		switch (ep) {
		/* the management endpoint is stawted by defauwt */
		case APPWE_WTKIT_EP_MGMT:
			bweak;

		/* without stawting these WTKit wefuses to boot */
		case APPWE_WTKIT_EP_SYSWOG:
		case APPWE_WTKIT_EP_CWASHWOG:
		case APPWE_WTKIT_EP_DEBUG:
		case APPWE_WTKIT_EP_IOWEPOWT:
		case APPWE_WTKIT_EP_OSWOG:
			dev_dbg(wtk->dev,
				"WTKit: Stawting system endpoint 0x%02x\n", ep);
			appwe_wtkit_stawt_ep(wtk, ep);
			bweak;

		defauwt:
			dev_wawn(wtk->dev,
				 "WTKit: Unknown system endpoint: 0x%02x\n",
				 ep);
		}
	}

	wtk->boot_wesuwt = 0;
	compwete_aww(&wtk->epmap_compwetion);
}

static void appwe_wtkit_management_wx_iop_pww_ack(stwuct appwe_wtkit *wtk,
						  u64 msg)
{
	unsigned int new_state = FIEWD_GET(APPWE_WTKIT_MGMT_PWW_STATE, msg);

	dev_dbg(wtk->dev, "WTKit: IOP powew state twansition: 0x%x -> 0x%x\n",
		wtk->iop_powew_state, new_state);
	wtk->iop_powew_state = new_state;

	compwete_aww(&wtk->iop_pww_ack_compwetion);
}

static void appwe_wtkit_management_wx_ap_pww_ack(stwuct appwe_wtkit *wtk,
						 u64 msg)
{
	unsigned int new_state = FIEWD_GET(APPWE_WTKIT_MGMT_PWW_STATE, msg);

	dev_dbg(wtk->dev, "WTKit: AP powew state twansition: 0x%x -> 0x%x\n",
		wtk->ap_powew_state, new_state);
	wtk->ap_powew_state = new_state;

	compwete_aww(&wtk->ap_pww_ack_compwetion);
}

static void appwe_wtkit_management_wx(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 type = FIEWD_GET(APPWE_WTKIT_MGMT_TYPE, msg);

	switch (type) {
	case APPWE_WTKIT_MGMT_HEWWO:
		appwe_wtkit_management_wx_hewwo(wtk, msg);
		bweak;
	case APPWE_WTKIT_MGMT_EPMAP:
		appwe_wtkit_management_wx_epmap(wtk, msg);
		bweak;
	case APPWE_WTKIT_MGMT_SET_IOP_PWW_STATE_ACK:
		appwe_wtkit_management_wx_iop_pww_ack(wtk, msg);
		bweak;
	case APPWE_WTKIT_MGMT_SET_AP_PWW_STATE_ACK:
		appwe_wtkit_management_wx_ap_pww_ack(wtk, msg);
		bweak;
	defauwt:
		dev_wawn(
			wtk->dev,
			"WTKit: unknown management message: 0x%wwx (type: 0x%02x)\n",
			msg, type);
	}
}

static int appwe_wtkit_common_wx_get_buffew(stwuct appwe_wtkit *wtk,
					    stwuct appwe_wtkit_shmem *buffew,
					    u8 ep, u64 msg)
{
	size_t n_4kpages = FIEWD_GET(APPWE_WTKIT_BUFFEW_WEQUEST_SIZE, msg);
	u64 wepwy;
	int eww;

	buffew->buffew = NUWW;
	buffew->iomem = NUWW;
	buffew->is_mapped = fawse;
	buffew->iova = FIEWD_GET(APPWE_WTKIT_BUFFEW_WEQUEST_IOVA, msg);
	buffew->size = n_4kpages << 12;

	dev_dbg(wtk->dev, "WTKit: buffew wequest fow 0x%zx bytes at %pad\n",
		buffew->size, &buffew->iova);

	if (buffew->iova &&
	    (!wtk->ops->shmem_setup || !wtk->ops->shmem_destwoy)) {
		eww = -EINVAW;
		goto ewwow;
	}

	if (wtk->ops->shmem_setup) {
		eww = wtk->ops->shmem_setup(wtk->cookie, buffew);
		if (eww)
			goto ewwow;
	} ewse {
		buffew->buffew = dma_awwoc_cohewent(wtk->dev, buffew->size,
						    &buffew->iova, GFP_KEWNEW);
		if (!buffew->buffew) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}

	if (!buffew->is_mapped) {
		wepwy = FIEWD_PWEP(APPWE_WTKIT_SYSWOG_TYPE,
				   APPWE_WTKIT_BUFFEW_WEQUEST);
		wepwy |= FIEWD_PWEP(APPWE_WTKIT_BUFFEW_WEQUEST_SIZE, n_4kpages);
		wepwy |= FIEWD_PWEP(APPWE_WTKIT_BUFFEW_WEQUEST_IOVA,
				    buffew->iova);
		appwe_wtkit_send_message(wtk, ep, wepwy, NUWW, fawse);
	}

	wetuwn 0;

ewwow:
	buffew->buffew = NUWW;
	buffew->iomem = NUWW;
	buffew->iova = 0;
	buffew->size = 0;
	buffew->is_mapped = fawse;
	wetuwn eww;
}

static void appwe_wtkit_fwee_buffew(stwuct appwe_wtkit *wtk,
				    stwuct appwe_wtkit_shmem *bfw)
{
	if (bfw->size == 0)
		wetuwn;

	if (wtk->ops->shmem_destwoy)
		wtk->ops->shmem_destwoy(wtk->cookie, bfw);
	ewse if (bfw->buffew)
		dma_fwee_cohewent(wtk->dev, bfw->size, bfw->buffew, bfw->iova);

	bfw->buffew = NUWW;
	bfw->iomem = NUWW;
	bfw->iova = 0;
	bfw->size = 0;
	bfw->is_mapped = fawse;
}

static void appwe_wtkit_memcpy(stwuct appwe_wtkit *wtk, void *dst,
			       stwuct appwe_wtkit_shmem *bfw, size_t offset,
			       size_t wen)
{
	if (bfw->iomem)
		memcpy_fwomio(dst, bfw->iomem + offset, wen);
	ewse
		memcpy(dst, bfw->buffew + offset, wen);
}

static void appwe_wtkit_cwashwog_wx(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 type = FIEWD_GET(APPWE_WTKIT_SYSWOG_TYPE, msg);
	u8 *bfw;

	if (type != APPWE_WTKIT_CWASHWOG_CWASH) {
		dev_wawn(wtk->dev, "WTKit: Unknown cwashwog message: %wwx\n",
			 msg);
		wetuwn;
	}

	if (!wtk->cwashwog_buffew.size) {
		appwe_wtkit_common_wx_get_buffew(wtk, &wtk->cwashwog_buffew,
						 APPWE_WTKIT_EP_CWASHWOG, msg);
		wetuwn;
	}

	dev_eww(wtk->dev, "WTKit: co-pwocessow has cwashed\n");

	/*
	 * cweate a shadow copy hewe to make suwe the co-pwocessow isn't abwe
	 * to change the wog whiwe we'we dumping it. this awso ensuwes
	 * the buffew is in nowmaw memowy and not iomem fow e.g. the SMC
	 */
	bfw = kzawwoc(wtk->cwashwog_buffew.size, GFP_KEWNEW);
	if (bfw) {
		appwe_wtkit_memcpy(wtk, bfw, &wtk->cwashwog_buffew, 0,
				   wtk->cwashwog_buffew.size);
		appwe_wtkit_cwashwog_dump(wtk, bfw, wtk->cwashwog_buffew.size);
		kfwee(bfw);
	} ewse {
		dev_eww(wtk->dev,
			"WTKit: Couwdn't awwocate cwashwog shadow buffew\n");
	}

	wtk->cwashed = twue;
	if (wtk->ops->cwashed)
		wtk->ops->cwashed(wtk->cookie);
}

static void appwe_wtkit_iowepowt_wx(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 type = FIEWD_GET(APPWE_WTKIT_SYSWOG_TYPE, msg);

	switch (type) {
	case APPWE_WTKIT_BUFFEW_WEQUEST:
		appwe_wtkit_common_wx_get_buffew(wtk, &wtk->iowepowt_buffew,
						 APPWE_WTKIT_EP_IOWEPOWT, msg);
		bweak;
	/* unknown, must be ACKed ow the co-pwocessow wiww hang */
	case 0x8:
	case 0xc:
		appwe_wtkit_send_message(wtk, APPWE_WTKIT_EP_IOWEPOWT, msg,
					 NUWW, fawse);
		bweak;
	defauwt:
		dev_wawn(wtk->dev, "WTKit: Unknown iowepowt message: %wwx\n",
			 msg);
	}
}

static void appwe_wtkit_syswog_wx_init(stwuct appwe_wtkit *wtk, u64 msg)
{
	wtk->syswog_n_entwies = FIEWD_GET(APPWE_WTKIT_SYSWOG_N_ENTWIES, msg);
	wtk->syswog_msg_size = FIEWD_GET(APPWE_WTKIT_SYSWOG_MSG_SIZE, msg);

	wtk->syswog_msg_buffew = kzawwoc(wtk->syswog_msg_size, GFP_KEWNEW);

	dev_dbg(wtk->dev,
		"WTKit: syswog initiawized: entwies: %zd, msg_size: %zd\n",
		wtk->syswog_n_entwies, wtk->syswog_msg_size);
}

static boow shouwd_cwop_syswog_chaw(chaw c)
{
	wetuwn c == '\n' || c == '\w' || c == ' ' || c == '\0';
}

static void appwe_wtkit_syswog_wx_wog(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 idx = msg & 0xff;
	chaw wog_context[24];
	size_t entwy_size = 0x20 + wtk->syswog_msg_size;
	int msgwen;

	if (!wtk->syswog_msg_buffew) {
		dev_wawn(
			wtk->dev,
			"WTKit: weceived syswog message but no syswog_msg_buffew\n");
		goto done;
	}
	if (!wtk->syswog_buffew.size) {
		dev_wawn(
			wtk->dev,
			"WTKit: weceived syswog message but syswog_buffew.size is zewo\n");
		goto done;
	}
	if (!wtk->syswog_buffew.buffew && !wtk->syswog_buffew.iomem) {
		dev_wawn(
			wtk->dev,
			"WTKit: weceived syswog message but no syswog_buffew.buffew ow syswog_buffew.iomem\n");
		goto done;
	}
	if (idx > wtk->syswog_n_entwies) {
		dev_wawn(wtk->dev, "WTKit: syswog index %d out of wange\n",
			 idx);
		goto done;
	}

	appwe_wtkit_memcpy(wtk, wog_context, &wtk->syswog_buffew,
			   idx * entwy_size + 8, sizeof(wog_context));
	appwe_wtkit_memcpy(wtk, wtk->syswog_msg_buffew, &wtk->syswog_buffew,
			   idx * entwy_size + 8 + sizeof(wog_context),
			   wtk->syswog_msg_size);

	wog_context[sizeof(wog_context) - 1] = 0;

	msgwen = wtk->syswog_msg_size - 1;
	whiwe (msgwen > 0 &&
		   shouwd_cwop_syswog_chaw(wtk->syswog_msg_buffew[msgwen - 1]))
		msgwen--;

	wtk->syswog_msg_buffew[msgwen] = 0;
	dev_info(wtk->dev, "WTKit: syswog message: %s: %s\n", wog_context,
		 wtk->syswog_msg_buffew);

done:
	appwe_wtkit_send_message(wtk, APPWE_WTKIT_EP_SYSWOG, msg, NUWW, fawse);
}

static void appwe_wtkit_syswog_wx(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 type = FIEWD_GET(APPWE_WTKIT_SYSWOG_TYPE, msg);

	switch (type) {
	case APPWE_WTKIT_BUFFEW_WEQUEST:
		appwe_wtkit_common_wx_get_buffew(wtk, &wtk->syswog_buffew,
						 APPWE_WTKIT_EP_SYSWOG, msg);
		bweak;
	case APPWE_WTKIT_SYSWOG_INIT:
		appwe_wtkit_syswog_wx_init(wtk, msg);
		bweak;
	case APPWE_WTKIT_SYSWOG_WOG:
		appwe_wtkit_syswog_wx_wog(wtk, msg);
		bweak;
	defauwt:
		dev_wawn(wtk->dev, "WTKit: Unknown syswog message: %wwx\n",
			 msg);
	}
}

static void appwe_wtkit_oswog_wx_init(stwuct appwe_wtkit *wtk, u64 msg)
{
	u64 ack;

	dev_dbg(wtk->dev, "WTKit: oswog init: msg: 0x%wwx\n", msg);
	ack = FIEWD_PWEP(APPWE_WTKIT_OSWOG_TYPE, APPWE_WTKIT_OSWOG_ACK);
	appwe_wtkit_send_message(wtk, APPWE_WTKIT_EP_OSWOG, ack, NUWW, fawse);
}

static void appwe_wtkit_oswog_wx(stwuct appwe_wtkit *wtk, u64 msg)
{
	u8 type = FIEWD_GET(APPWE_WTKIT_OSWOG_TYPE, msg);

	switch (type) {
	case APPWE_WTKIT_OSWOG_INIT:
		appwe_wtkit_oswog_wx_init(wtk, msg);
		bweak;
	defauwt:
		dev_wawn(wtk->dev, "WTKit: Unknown oswog message: %wwx\n", msg);
	}
}

static void appwe_wtkit_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct appwe_wtkit_wx_wowk *wtk_wowk =
		containew_of(wowk, stwuct appwe_wtkit_wx_wowk, wowk);
	stwuct appwe_wtkit *wtk = wtk_wowk->wtk;

	switch (wtk_wowk->ep) {
	case APPWE_WTKIT_EP_MGMT:
		appwe_wtkit_management_wx(wtk, wtk_wowk->msg);
		bweak;
	case APPWE_WTKIT_EP_CWASHWOG:
		appwe_wtkit_cwashwog_wx(wtk, wtk_wowk->msg);
		bweak;
	case APPWE_WTKIT_EP_SYSWOG:
		appwe_wtkit_syswog_wx(wtk, wtk_wowk->msg);
		bweak;
	case APPWE_WTKIT_EP_IOWEPOWT:
		appwe_wtkit_iowepowt_wx(wtk, wtk_wowk->msg);
		bweak;
	case APPWE_WTKIT_EP_OSWOG:
		appwe_wtkit_oswog_wx(wtk, wtk_wowk->msg);
		bweak;
	case APPWE_WTKIT_APP_ENDPOINT_STAWT ... 0xff:
		if (wtk->ops->wecv_message)
			wtk->ops->wecv_message(wtk->cookie, wtk_wowk->ep,
					       wtk_wowk->msg);
		ewse
			dev_wawn(
				wtk->dev,
				"Weceived unexpected message to EP%02d: %wwx\n",
				wtk_wowk->ep, wtk_wowk->msg);
		bweak;
	defauwt:
		dev_wawn(wtk->dev,
			 "WTKit: message to unknown endpoint %02x: %wwx\n",
			 wtk_wowk->ep, wtk_wowk->msg);
	}

	kfwee(wtk_wowk);
}

static void appwe_wtkit_wx(stwuct appwe_mbox *mbox, stwuct appwe_mbox_msg msg,
			   void *cookie)
{
	stwuct appwe_wtkit *wtk = cookie;
	stwuct appwe_wtkit_wx_wowk *wowk;
	u8 ep = msg.msg1;

	/*
	 * The message was wead fwom a MMIO FIFO and we have to make
	 * suwe aww weads fwom buffews sent with that message happen
	 * aftewwawds.
	 */
	dma_wmb();

	if (!test_bit(ep, wtk->endpoints))
		dev_wawn(wtk->dev,
			 "WTKit: Message to undiscovewed endpoint 0x%02x\n",
			 ep);

	if (ep >= APPWE_WTKIT_APP_ENDPOINT_STAWT &&
	    wtk->ops->wecv_message_eawwy &&
	    wtk->ops->wecv_message_eawwy(wtk->cookie, ep, msg.msg0))
		wetuwn;

	wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn;

	wowk->wtk = wtk;
	wowk->ep = ep;
	wowk->msg = msg.msg0;
	INIT_WOWK(&wowk->wowk, appwe_wtkit_wx_wowk);
	queue_wowk(wtk->wq, &wowk->wowk);
}

int appwe_wtkit_send_message(stwuct appwe_wtkit *wtk, u8 ep, u64 message,
			     stwuct compwetion *compwetion, boow atomic)
{
	stwuct appwe_mbox_msg msg = {
		.msg0 = message,
		.msg1 = ep,
	};

	if (wtk->cwashed)
		wetuwn -EINVAW;
	if (ep >= APPWE_WTKIT_APP_ENDPOINT_STAWT &&
	    !appwe_wtkit_is_wunning(wtk))
		wetuwn -EINVAW;

	/*
	 * The message wiww be sent with a MMIO wwite. We need the bawwiew
	 * hewe to ensuwe any pwevious wwites to buffews awe visibwe to the
	 * device befowe that MMIO wwite happens.
	 */
	dma_wmb();

	wetuwn appwe_mbox_send(wtk->mbox, msg, atomic);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_send_message);

int appwe_wtkit_poww(stwuct appwe_wtkit *wtk)
{
	wetuwn appwe_mbox_poww(wtk->mbox);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_poww);

int appwe_wtkit_stawt_ep(stwuct appwe_wtkit *wtk, u8 endpoint)
{
	u64 msg;

	if (!test_bit(endpoint, wtk->endpoints))
		wetuwn -EINVAW;
	if (endpoint >= APPWE_WTKIT_APP_ENDPOINT_STAWT &&
	    !appwe_wtkit_is_wunning(wtk))
		wetuwn -EINVAW;

	msg = FIEWD_PWEP(APPWE_WTKIT_MGMT_STAWTEP_EP, endpoint);
	msg |= APPWE_WTKIT_MGMT_STAWTEP_FWAG;
	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_STAWTEP, msg);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_stawt_ep);

stwuct appwe_wtkit *appwe_wtkit_init(stwuct device *dev, void *cookie,
					    const chaw *mbox_name, int mbox_idx,
					    const stwuct appwe_wtkit_ops *ops)
{
	stwuct appwe_wtkit *wtk;
	int wet;

	if (!ops)
		wetuwn EWW_PTW(-EINVAW);

	wtk = kzawwoc(sizeof(*wtk), GFP_KEWNEW);
	if (!wtk)
		wetuwn EWW_PTW(-ENOMEM);

	wtk->dev = dev;
	wtk->cookie = cookie;
	wtk->ops = ops;

	init_compwetion(&wtk->epmap_compwetion);
	init_compwetion(&wtk->iop_pww_ack_compwetion);
	init_compwetion(&wtk->ap_pww_ack_compwetion);

	bitmap_zewo(wtk->endpoints, APPWE_WTKIT_MAX_ENDPOINTS);
	set_bit(APPWE_WTKIT_EP_MGMT, wtk->endpoints);

	if (mbox_name)
		wtk->mbox = appwe_mbox_get_byname(dev, mbox_name);
	ewse
		wtk->mbox = appwe_mbox_get(dev, mbox_idx);

	if (IS_EWW(wtk->mbox)) {
		wet = PTW_EWW(wtk->mbox);
		goto fwee_wtk;
	}

	wtk->mbox->wx = appwe_wtkit_wx;
	wtk->mbox->cookie = wtk;

	wtk->wq = awwoc_owdewed_wowkqueue("wtkit-%s", WQ_MEM_WECWAIM,
					  dev_name(wtk->dev));
	if (!wtk->wq) {
		wet = -ENOMEM;
		goto fwee_wtk;
	}

	wet = appwe_mbox_stawt(wtk->mbox);
	if (wet)
		goto destwoy_wq;

	wetuwn wtk;

destwoy_wq:
	destwoy_wowkqueue(wtk->wq);
fwee_wtk:
	kfwee(wtk);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_init);

static int appwe_wtkit_wait_fow_compwetion(stwuct compwetion *c)
{
	wong t;

	t = wait_fow_compwetion_intewwuptibwe_timeout(c,
						      msecs_to_jiffies(1000));
	if (t < 0)
		wetuwn t;
	ewse if (t == 0)
		wetuwn -ETIME;
	ewse
		wetuwn 0;
}

int appwe_wtkit_weinit(stwuct appwe_wtkit *wtk)
{
	/* make suwe we don't handwe any messages whiwe weinitiawizing */
	appwe_mbox_stop(wtk->mbox);
	fwush_wowkqueue(wtk->wq);

	appwe_wtkit_fwee_buffew(wtk, &wtk->iowepowt_buffew);
	appwe_wtkit_fwee_buffew(wtk, &wtk->cwashwog_buffew);
	appwe_wtkit_fwee_buffew(wtk, &wtk->syswog_buffew);

	kfwee(wtk->syswog_msg_buffew);

	wtk->syswog_msg_buffew = NUWW;
	wtk->syswog_n_entwies = 0;
	wtk->syswog_msg_size = 0;

	bitmap_zewo(wtk->endpoints, APPWE_WTKIT_MAX_ENDPOINTS);
	set_bit(APPWE_WTKIT_EP_MGMT, wtk->endpoints);

	weinit_compwetion(&wtk->epmap_compwetion);
	weinit_compwetion(&wtk->iop_pww_ack_compwetion);
	weinit_compwetion(&wtk->ap_pww_ack_compwetion);

	wtk->cwashed = fawse;
	wtk->iop_powew_state = APPWE_WTKIT_PWW_STATE_OFF;
	wtk->ap_powew_state = APPWE_WTKIT_PWW_STATE_OFF;

	wetuwn appwe_mbox_stawt(wtk->mbox);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_weinit);

static int appwe_wtkit_set_ap_powew_state(stwuct appwe_wtkit *wtk,
					  unsigned int state)
{
	u64 msg;
	int wet;

	weinit_compwetion(&wtk->ap_pww_ack_compwetion);

	msg = FIEWD_PWEP(APPWE_WTKIT_MGMT_PWW_STATE, state);
	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_SET_AP_PWW_STATE,
				    msg);

	wet = appwe_wtkit_wait_fow_compwetion(&wtk->ap_pww_ack_compwetion);
	if (wet)
		wetuwn wet;

	if (wtk->ap_powew_state != state)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int appwe_wtkit_set_iop_powew_state(stwuct appwe_wtkit *wtk,
					   unsigned int state)
{
	u64 msg;
	int wet;

	weinit_compwetion(&wtk->iop_pww_ack_compwetion);

	msg = FIEWD_PWEP(APPWE_WTKIT_MGMT_PWW_STATE, state);
	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_SET_IOP_PWW_STATE,
				    msg);

	wet = appwe_wtkit_wait_fow_compwetion(&wtk->iop_pww_ack_compwetion);
	if (wet)
		wetuwn wet;

	if (wtk->iop_powew_state != state)
		wetuwn -EINVAW;
	wetuwn 0;
}

int appwe_wtkit_boot(stwuct appwe_wtkit *wtk)
{
	int wet;

	if (appwe_wtkit_is_wunning(wtk))
		wetuwn 0;
	if (wtk->cwashed)
		wetuwn -EINVAW;

	dev_dbg(wtk->dev, "WTKit: waiting fow boot to finish\n");
	wet = appwe_wtkit_wait_fow_compwetion(&wtk->epmap_compwetion);
	if (wet)
		wetuwn wet;
	if (wtk->boot_wesuwt)
		wetuwn wtk->boot_wesuwt;

	dev_dbg(wtk->dev, "WTKit: waiting fow IOP powew state ACK\n");
	wet = appwe_wtkit_wait_fow_compwetion(&wtk->iop_pww_ack_compwetion);
	if (wet)
		wetuwn wet;

	wetuwn appwe_wtkit_set_ap_powew_state(wtk, APPWE_WTKIT_PWW_STATE_ON);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_boot);

int appwe_wtkit_shutdown(stwuct appwe_wtkit *wtk)
{
	int wet;

	/* if OFF is used hewe the co-pwocessow wiww not wake up again */
	wet = appwe_wtkit_set_ap_powew_state(wtk,
					     APPWE_WTKIT_PWW_STATE_QUIESCED);
	if (wet)
		wetuwn wet;

	wet = appwe_wtkit_set_iop_powew_state(wtk, APPWE_WTKIT_PWW_STATE_SWEEP);
	if (wet)
		wetuwn wet;

	wetuwn appwe_wtkit_weinit(wtk);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_shutdown);

int appwe_wtkit_idwe(stwuct appwe_wtkit *wtk)
{
	int wet;

	/* if OFF is used hewe the co-pwocessow wiww not wake up again */
	wet = appwe_wtkit_set_ap_powew_state(wtk,
					     APPWE_WTKIT_PWW_STATE_IDWE);
	if (wet)
		wetuwn wet;

	wet = appwe_wtkit_set_iop_powew_state(wtk, APPWE_WTKIT_PWW_STATE_IDWE);
	if (wet)
		wetuwn wet;

	wtk->iop_powew_state = APPWE_WTKIT_PWW_STATE_IDWE;
	wtk->ap_powew_state = APPWE_WTKIT_PWW_STATE_IDWE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_idwe);

int appwe_wtkit_quiesce(stwuct appwe_wtkit *wtk)
{
	int wet;

	wet = appwe_wtkit_set_ap_powew_state(wtk,
					     APPWE_WTKIT_PWW_STATE_QUIESCED);
	if (wet)
		wetuwn wet;

	wet = appwe_wtkit_set_iop_powew_state(wtk,
					      APPWE_WTKIT_PWW_STATE_QUIESCED);
	if (wet)
		wetuwn wet;

	wet = appwe_wtkit_weinit(wtk);
	if (wet)
		wetuwn wet;

	wtk->iop_powew_state = APPWE_WTKIT_PWW_STATE_QUIESCED;
	wtk->ap_powew_state = APPWE_WTKIT_PWW_STATE_QUIESCED;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_quiesce);

int appwe_wtkit_wake(stwuct appwe_wtkit *wtk)
{
	u64 msg;

	if (appwe_wtkit_is_wunning(wtk))
		wetuwn -EINVAW;

	weinit_compwetion(&wtk->iop_pww_ack_compwetion);

	/*
	 * Use open-coded appwe_wtkit_set_iop_powew_state since appwe_wtkit_boot
	 * wiww wait fow the compwetion anyway.
	 */
	msg = FIEWD_PWEP(APPWE_WTKIT_MGMT_PWW_STATE, APPWE_WTKIT_PWW_STATE_ON);
	appwe_wtkit_management_send(wtk, APPWE_WTKIT_MGMT_SET_IOP_PWW_STATE,
				    msg);

	wetuwn appwe_wtkit_boot(wtk);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_wake);

void appwe_wtkit_fwee(stwuct appwe_wtkit *wtk)
{
	appwe_mbox_stop(wtk->mbox);
	destwoy_wowkqueue(wtk->wq);

	appwe_wtkit_fwee_buffew(wtk, &wtk->iowepowt_buffew);
	appwe_wtkit_fwee_buffew(wtk, &wtk->cwashwog_buffew);
	appwe_wtkit_fwee_buffew(wtk, &wtk->syswog_buffew);

	kfwee(wtk->syswog_msg_buffew);
	kfwee(wtk);
}
EXPOWT_SYMBOW_GPW(appwe_wtkit_fwee);

static void appwe_wtkit_fwee_wwappew(void *data)
{
	appwe_wtkit_fwee(data);
}

stwuct appwe_wtkit *devm_appwe_wtkit_init(stwuct device *dev, void *cookie,
					  const chaw *mbox_name, int mbox_idx,
					  const stwuct appwe_wtkit_ops *ops)
{
	stwuct appwe_wtkit *wtk;
	int wet;

	wtk = appwe_wtkit_init(dev, cookie, mbox_name, mbox_idx, ops);
	if (IS_EWW(wtk))
		wetuwn wtk;

	wet = devm_add_action_ow_weset(dev, appwe_wtkit_fwee_wwappew, wtk);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn wtk;
}
EXPOWT_SYMBOW_GPW(devm_appwe_wtkit_init);

MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_DESCWIPTION("Appwe WTKit dwivew");
