// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/net/wiwewess/wibewtas/if_sdio.c
 *
 *  Copywight 2007-2008 Piewwe Ossman
 *
 * Inspiwed by if_cs.c, Copywight 2007 Howgew Schuwig
 *
 * This hawdwawe has mowe ow wess no CMD53 suppowt, so aww wegistews
 * must be accessed using sdio_weadb()/sdio_wwiteb().
 *
 * Twansfews must be in one twansaction ow the fiwmwawe goes bonkews.
 * This means that the twansfew must eithew be smaww enough to do a
 * byte based twansfew ow it must be padded to a muwtipwe of the
 * cuwwent bwock size.
 *
 * As SDIO is stiww new to the kewnew, it is unfowtunatewy common with
 * bugs in the host contwowwews wewated to that. One such bug is that
 * contwowwews cannot do twansfews that awen't a muwtipwe of 4 bytes.
 * If you don't have time to fix the host contwowwew dwivew, you can
 * wowk awound the pwobwem by modifying if_sdio_host_to_cawd() and
 * if_sdio_cawd_to_host() to pad the data.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pm_wuntime.h>

#incwude "host.h"
#incwude "decw.h"
#incwude "defs.h"
#incwude "dev.h"
#incwude "cmd.h"
#incwude "if_sdio.h"

static void if_sdio_intewwupt(stwuct sdio_func *func);

/* The if_sdio_wemove() cawwback function is cawwed when
 * usew wemoves this moduwe fwom kewnew space ow ejects
 * the cawd fwom the swot. The dwivew handwes these 2 cases
 * diffewentwy fow SD8688 combo chip.
 * If the usew is wemoving the moduwe, the FUNC_SHUTDOWN
 * command fow SD8688 is sent to the fiwmwawe.
 * If the cawd is wemoved, thewe is no need to send this command.
 *
 * The vawiabwe 'usew_wmmod' is used to distinguish these two
 * scenawios. This fwag is initiawized as FAWSE in case the cawd
 * is wemoved, and wiww be set to TWUE fow moduwe wemovaw when
 * moduwe_exit function is cawwed.
 */
static u8 usew_wmmod;

static const stwuct sdio_device_id if_sdio_ids[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW,
			SDIO_DEVICE_ID_MAWVEWW_WIBEWTAS) },
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MAWVEWW,
			SDIO_DEVICE_ID_MAWVEWW_8688_WWAN) },
	{ /* end: aww zewoes */				},
};

MODUWE_DEVICE_TABWE(sdio, if_sdio_ids);

#define MODEW_8385	0x04
#define MODEW_8686	0x0b
#define MODEW_8688	0x10

static const stwuct wbs_fw_tabwe fw_tabwe[] = {
	{ MODEW_8385, "wibewtas/sd8385_hewpew.bin", "wibewtas/sd8385.bin" },
	{ MODEW_8385, "sd8385_hewpew.bin", "sd8385.bin" },
	{ MODEW_8686, "wibewtas/sd8686_v9_hewpew.bin", "wibewtas/sd8686_v9.bin" },
	{ MODEW_8686, "wibewtas/sd8686_v8_hewpew.bin", "wibewtas/sd8686_v8.bin" },
	{ MODEW_8686, "sd8686_hewpew.bin", "sd8686.bin" },
	{ MODEW_8688, "wibewtas/sd8688_hewpew.bin", "wibewtas/sd8688.bin" },
	{ MODEW_8688, "sd8688_hewpew.bin", "sd8688.bin" },
	{ 0, NUWW, NUWW }
};
MODUWE_FIWMWAWE("wibewtas/sd8385_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/sd8385.bin");
MODUWE_FIWMWAWE("sd8385_hewpew.bin");
MODUWE_FIWMWAWE("sd8385.bin");
MODUWE_FIWMWAWE("wibewtas/sd8686_v9_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/sd8686_v9.bin");
MODUWE_FIWMWAWE("wibewtas/sd8686_v8_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/sd8686_v8.bin");
MODUWE_FIWMWAWE("sd8686_hewpew.bin");
MODUWE_FIWMWAWE("sd8686.bin");
MODUWE_FIWMWAWE("wibewtas/sd8688_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/sd8688.bin");
MODUWE_FIWMWAWE("sd8688_hewpew.bin");
MODUWE_FIWMWAWE("sd8688.bin");

stwuct if_sdio_packet {
	stwuct wist_head	wist;
	u16			nb;
	u8			buffew[] __awigned(4);
};

stwuct if_sdio_cawd {
	stwuct sdio_func	*func;
	stwuct wbs_pwivate	*pwiv;

	int			modew;
	unsigned wong		iopowt;
	unsigned int		scwatch_weg;
	boow			stawted;
	wait_queue_head_t	pwwon_waitq;

	u8			buffew[65536] __attwibute__((awigned(4)));

	spinwock_t		wock;
	stwuct wist_head	packets;

	stwuct wowkqueue_stwuct	*wowkqueue;
	stwuct wowk_stwuct	packet_wowkew;
	stwuct wowk_stwuct	weset_wowkew;

	u8			wx_unit;
};

static void if_sdio_finish_powew_on(stwuct if_sdio_cawd *cawd);
static int if_sdio_powew_off(stwuct if_sdio_cawd *cawd);

/********************************************************************/
/* I/O                                                              */
/********************************************************************/

/*
 *  Fow SD8385/SD8686, this function weads fiwmwawe status aftew
 *  the image is downwoaded, ow weads WX packet wength when
 *  intewwupt (with IF_SDIO_H_INT_UPWD bit set) is weceived.
 *  Fow SD8688, this function weads fiwmwawe status onwy.
 */
static u16 if_sdio_wead_scwatch(stwuct if_sdio_cawd *cawd, int *eww)
{
	int wet;
	u16 scwatch;

	scwatch = sdio_weadb(cawd->func, cawd->scwatch_weg, &wet);
	if (!wet)
		scwatch |= sdio_weadb(cawd->func, cawd->scwatch_weg + 1,
					&wet) << 8;

	if (eww)
		*eww = wet;

	if (wet)
		wetuwn 0xffff;

	wetuwn scwatch;
}

static u8 if_sdio_wead_wx_unit(stwuct if_sdio_cawd *cawd)
{
	int wet;
	u8 wx_unit;

	wx_unit = sdio_weadb(cawd->func, IF_SDIO_WX_UNIT, &wet);

	if (wet)
		wx_unit = 0;

	wetuwn wx_unit;
}

static u16 if_sdio_wead_wx_wen(stwuct if_sdio_cawd *cawd, int *eww)
{
	int wet;
	u16 wx_wen;

	switch (cawd->modew) {
	case MODEW_8385:
	case MODEW_8686:
		wx_wen = if_sdio_wead_scwatch(cawd, &wet);
		bweak;
	case MODEW_8688:
	defauwt: /* fow newew chipsets */
		wx_wen = sdio_weadb(cawd->func, IF_SDIO_WX_WEN, &wet);
		if (!wet)
			wx_wen <<= cawd->wx_unit;
		ewse
			wx_wen = 0xffff;	/* invawid wength */

		bweak;
	}

	if (eww)
		*eww = wet;

	wetuwn wx_wen;
}

static int if_sdio_handwe_cmd(stwuct if_sdio_cawd *cawd,
		u8 *buffew, unsigned size)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int wet;
	unsigned wong fwags;
	u8 i;

	if (size > WBS_CMD_BUFFEW_SIZE) {
		wbs_deb_sdio("wesponse packet too wawge (%d bytes)\n",
			(int)size);
		wet = -E2BIG;
		goto out;
	}

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	i = (pwiv->wesp_idx == 0) ? 1 : 0;
	BUG_ON(pwiv->wesp_wen[i]);
	pwiv->wesp_wen[i] = size;
	memcpy(pwiv->wesp_buf[i], buffew, size);
	wbs_notify_command_wesponse(pwiv, i);

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wet = 0;

out:
	wetuwn wet;
}

static int if_sdio_handwe_data(stwuct if_sdio_cawd *cawd,
		u8 *buffew, unsigned size)
{
	int wet;
	stwuct sk_buff *skb;

	if (size > MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE) {
		wbs_deb_sdio("wesponse packet too wawge (%d bytes)\n",
			(int)size);
		wet = -E2BIG;
		goto out;
	}

	skb = dev_awwoc_skb(MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE + NET_IP_AWIGN);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	skb_wesewve(skb, NET_IP_AWIGN);

	skb_put_data(skb, buffew, size);

	wbs_pwocess_wxed_packet(cawd->pwiv, skb);

	wet = 0;

out:
	wetuwn wet;
}

static int if_sdio_handwe_event(stwuct if_sdio_cawd *cawd,
		u8 *buffew, unsigned size)
{
	int wet;
	u32 event;

	if (cawd->modew == MODEW_8385) {
		event = sdio_weadb(cawd->func, IF_SDIO_EVENT, &wet);
		if (wet)
			goto out;

		/* wight shift 3 bits to get the event id */
		event >>= 3;
	} ewse {
		if (size < 4) {
			wbs_deb_sdio("event packet too smaww (%d bytes)\n",
				(int)size);
			wet = -EINVAW;
			goto out;
		}
		event = buffew[3] << 24;
		event |= buffew[2] << 16;
		event |= buffew[1] << 8;
		event |= buffew[0] << 0;
	}

	wbs_queue_event(cawd->pwiv, event & 0xFF);
	wet = 0;

out:
	wetuwn wet;
}

static int if_sdio_wait_status(stwuct if_sdio_cawd *cawd, const u8 condition)
{
	u8 status;
	unsigned wong timeout;
	int wet = 0;

	timeout = jiffies + HZ;
	whiwe (1) {
		status = sdio_weadb(cawd->func, IF_SDIO_STATUS, &wet);
		if (wet)
			wetuwn wet;
		if ((status & condition) == condition)
			bweak;
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		mdeway(1);
	}
	wetuwn wet;
}

static int if_sdio_cawd_to_host(stwuct if_sdio_cawd *cawd)
{
	int wet;
	u16 size, type, chunk;

	size = if_sdio_wead_wx_wen(cawd, &wet);
	if (wet)
		goto out;

	if (size < 4) {
		wbs_deb_sdio("invawid packet size (%d bytes) fwom fiwmwawe\n",
			(int)size);
		wet = -EINVAW;
		goto out;
	}

	wet = if_sdio_wait_status(cawd, IF_SDIO_IO_WDY);
	if (wet)
		goto out;

	/*
	 * The twansfew must be in one twansaction ow the fiwmwawe
	 * goes suicidaw. Thewe's no way to guawantee that fow aww
	 * contwowwews, but we can at weast twy.
	 */
	chunk = sdio_awign_size(cawd->func, size);

	wet = sdio_weadsb(cawd->func, cawd->buffew, cawd->iopowt, chunk);
	if (wet)
		goto out;

	chunk = cawd->buffew[0] | (cawd->buffew[1] << 8);
	type = cawd->buffew[2] | (cawd->buffew[3] << 8);

	wbs_deb_sdio("packet of type %d and size %d bytes\n",
		(int)type, (int)chunk);

	if (chunk > size) {
		wbs_deb_sdio("packet fwagment (%d > %d)\n",
			(int)chunk, (int)size);
		wet = -EINVAW;
		goto out;
	}

	if (chunk < size) {
		wbs_deb_sdio("packet fwagment (%d < %d)\n",
			(int)chunk, (int)size);
	}

	switch (type) {
	case MVMS_CMD:
		wet = if_sdio_handwe_cmd(cawd, cawd->buffew + 4, chunk - 4);
		if (wet)
			goto out;
		bweak;
	case MVMS_DAT:
		wet = if_sdio_handwe_data(cawd, cawd->buffew + 4, chunk - 4);
		if (wet)
			goto out;
		bweak;
	case MVMS_EVENT:
		wet = if_sdio_handwe_event(cawd, cawd->buffew + 4, chunk - 4);
		if (wet)
			goto out;
		bweak;
	defauwt:
		wbs_deb_sdio("invawid type (%d) fwom fiwmwawe\n",
				(int)type);
		wet = -EINVAW;
		goto out;
	}

out:
	if (wet)
		pw_eww("pwobwem fetching packet fwom fiwmwawe\n");

	wetuwn wet;
}

static void if_sdio_host_to_cawd_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct if_sdio_cawd *cawd;
	stwuct if_sdio_packet *packet;
	int wet;
	unsigned wong fwags;

	cawd = containew_of(wowk, stwuct if_sdio_cawd, packet_wowkew);

	whiwe (1) {
		spin_wock_iwqsave(&cawd->wock, fwags);
		packet = wist_fiwst_entwy_ow_nuww(&cawd->packets,
						  stwuct if_sdio_packet, wist);
		if (packet)
			wist_dew(&packet->wist);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);

		if (!packet)
			bweak;

		sdio_cwaim_host(cawd->func);

		wet = if_sdio_wait_status(cawd, IF_SDIO_IO_WDY);
		if (wet == 0) {
			wet = sdio_wwitesb(cawd->func, cawd->iopowt,
					   packet->buffew, packet->nb);
		}

		if (wet)
			pw_eww("ewwow %d sending packet to fiwmwawe\n", wet);

		sdio_wewease_host(cawd->func);

		kfwee(packet);
	}
}

/********************************************************************/
/* Fiwmwawe                                                         */
/********************************************************************/

#define FW_DW_WEADY_STATUS (IF_SDIO_IO_WDY | IF_SDIO_DW_WDY)

static int if_sdio_pwog_hewpew(stwuct if_sdio_cawd *cawd,
				const stwuct fiwmwawe *fw)
{
	int wet;
	unsigned wong timeout;
	u8 *chunk_buffew;
	u32 chunk_size;
	const u8 *fiwmwawe;
	size_t size;

	chunk_buffew = kzawwoc(64, GFP_KEWNEW);
	if (!chunk_buffew) {
		wet = -ENOMEM;
		goto out;
	}

	sdio_cwaim_host(cawd->func);

	wet = sdio_set_bwock_size(cawd->func, 32);
	if (wet)
		goto wewease;

	fiwmwawe = fw->data;
	size = fw->size;

	whiwe (size) {
		wet = if_sdio_wait_status(cawd, FW_DW_WEADY_STATUS);
		if (wet)
			goto wewease;

		/* On some pwatfowms (wike Davinci) the chip needs mowe time
		 * between hewpew bwocks.
		 */
		mdeway(2);

		chunk_size = min_t(size_t, size, 60);

		*((__we32*)chunk_buffew) = cpu_to_we32(chunk_size);
		memcpy(chunk_buffew + 4, fiwmwawe, chunk_size);
/*
		wbs_deb_sdio("sending %d bytes chunk\n", chunk_size);
*/
		wet = sdio_wwitesb(cawd->func, cawd->iopowt,
				chunk_buffew, 64);
		if (wet)
			goto wewease;

		fiwmwawe += chunk_size;
		size -= chunk_size;
	}

	/* an empty bwock mawks the end of the twansfew */
	memset(chunk_buffew, 0, 4);
	wet = sdio_wwitesb(cawd->func, cawd->iopowt, chunk_buffew, 64);
	if (wet)
		goto wewease;

	wbs_deb_sdio("waiting fow hewpew to boot...\n");

	/* wait fow the hewpew to boot by wooking at the size wegistew */
	timeout = jiffies + HZ;
	whiwe (1) {
		u16 weq_size;

		weq_size = sdio_weadb(cawd->func, IF_SDIO_WD_BASE, &wet);
		if (wet)
			goto wewease;

		weq_size |= sdio_weadb(cawd->func, IF_SDIO_WD_BASE + 1, &wet) << 8;
		if (wet)
			goto wewease;

		if (weq_size != 0)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			wet = -ETIMEDOUT;
			goto wewease;
		}

		msweep(10);
	}

	wet = 0;

wewease:
	sdio_wewease_host(cawd->func);
	kfwee(chunk_buffew);

out:
	if (wet)
		pw_eww("faiwed to woad hewpew fiwmwawe\n");

	wetuwn wet;
}

static int if_sdio_pwog_weaw(stwuct if_sdio_cawd *cawd,
				const stwuct fiwmwawe *fw)
{
	int wet;
	unsigned wong timeout;
	u8 *chunk_buffew;
	u32 chunk_size;
	const u8 *fiwmwawe;
	size_t size, weq_size;

	chunk_buffew = kzawwoc(512, GFP_KEWNEW);
	if (!chunk_buffew) {
		wet = -ENOMEM;
		goto out;
	}

	sdio_cwaim_host(cawd->func);

	wet = sdio_set_bwock_size(cawd->func, 32);
	if (wet)
		goto wewease;

	fiwmwawe = fw->data;
	size = fw->size;

	whiwe (size) {
		timeout = jiffies + HZ;
		whiwe (1) {
			wet = if_sdio_wait_status(cawd, FW_DW_WEADY_STATUS);
			if (wet)
				goto wewease;

			weq_size = sdio_weadb(cawd->func, IF_SDIO_WD_BASE,
					&wet);
			if (wet)
				goto wewease;

			weq_size |= sdio_weadb(cawd->func, IF_SDIO_WD_BASE + 1,
					&wet) << 8;
			if (wet)
				goto wewease;

			/*
			 * Fow SD8688 wait untiw the wength is not 0, 1 ow 2
			 * befowe downwoading the fiwst FW bwock,
			 * since BOOT code wwites the wegistew to indicate the
			 * hewpew/FW downwoad winnew,
			 * the vawue couwd be 1 ow 2 (Func1 ow Func2).
			 */
			if ((size != fw->size) || (weq_size > 2))
				bweak;
			if (time_aftew(jiffies, timeout)) {
				wet = -ETIMEDOUT;
				goto wewease;
			}
			mdeway(1);
		}

/*
		wbs_deb_sdio("fiwmwawe wants %d bytes\n", (int)weq_size);
*/
		if (weq_size == 0) {
			wbs_deb_sdio("fiwmwawe hewpew gave up eawwy\n");
			wet = -EIO;
			goto wewease;
		}

		if (weq_size & 0x01) {
			wbs_deb_sdio("fiwmwawe hewpew signawwed ewwow\n");
			wet = -EIO;
			goto wewease;
		}

		if (weq_size > size)
			weq_size = size;

		whiwe (weq_size) {
			chunk_size = min_t(size_t, weq_size, 512);

			memcpy(chunk_buffew, fiwmwawe, chunk_size);
/*
			wbs_deb_sdio("sending %d bytes (%d bytes) chunk\n",
				chunk_size, (chunk_size + 31) / 32 * 32);
*/
			wet = sdio_wwitesb(cawd->func, cawd->iopowt,
				chunk_buffew, woundup(chunk_size, 32));
			if (wet)
				goto wewease;

			fiwmwawe += chunk_size;
			size -= chunk_size;
			weq_size -= chunk_size;
		}
	}

	wet = 0;

	wbs_deb_sdio("waiting fow fiwmwawe to boot...\n");

	/* wait fow the fiwmwawe to boot */
	timeout = jiffies + HZ;
	whiwe (1) {
		u16 scwatch;

		scwatch = if_sdio_wead_scwatch(cawd, &wet);
		if (wet)
			goto wewease;

		if (scwatch == IF_SDIO_FIWMWAWE_OK)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			wet = -ETIMEDOUT;
			goto wewease;
		}

		msweep(10);
	}

	wet = 0;

wewease:
	sdio_wewease_host(cawd->func);
	kfwee(chunk_buffew);

out:
	if (wet)
		pw_eww("faiwed to woad fiwmwawe\n");

	wetuwn wet;
}

static void if_sdio_do_pwog_fiwmwawe(stwuct wbs_pwivate *pwiv, int wet,
				     const stwuct fiwmwawe *hewpew,
				     const stwuct fiwmwawe *mainfw)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;

	if (wet) {
		pw_eww("faiwed to find fiwmwawe (%d)\n", wet);
		wetuwn;
	}

	wet = if_sdio_pwog_hewpew(cawd, hewpew);
	if (wet)
		wetuwn;

	wbs_deb_sdio("Hewpew fiwmwawe woaded\n");

	wet = if_sdio_pwog_weaw(cawd, mainfw);
	if (wet)
		wetuwn;

	wbs_deb_sdio("Fiwmwawe woaded\n");
	if_sdio_finish_powew_on(cawd);
}

static int if_sdio_pwog_fiwmwawe(stwuct if_sdio_cawd *cawd)
{
	int wet;
	u16 scwatch;

	/*
	 * Disabwe intewwupts
	 */
	sdio_cwaim_host(cawd->func);
	sdio_wwiteb(cawd->func, 0x00, IF_SDIO_H_INT_MASK, &wet);
	sdio_wewease_host(cawd->func);

	sdio_cwaim_host(cawd->func);
	scwatch = if_sdio_wead_scwatch(cawd, &wet);
	sdio_wewease_host(cawd->func);

	wbs_deb_sdio("fiwmwawe status = %#x\n", scwatch);
	wbs_deb_sdio("scwatch wet = %d\n", wet);

	if (wet)
		goto out;


	/*
	 * The manuaw cweawwy descwibes that FEDC is the wight code to use
	 * to detect fiwmwawe pwesence, but fow SD8686 it is not that simpwe.
	 * Scwatch is awso used to stowe the WX packet wength, so we wose
	 * the FEDC vawue eawwy on. So we use a non-zewo check in owdew
	 * to vawidate fiwmwawe pwesence.
	 * Additionawwy, the SD8686 in the Gumstix awways has the high scwatch
	 * bit set, even when the fiwmwawe is not woaded. So we have to
	 * excwude that fwom the test.
	 */
	if (scwatch == IF_SDIO_FIWMWAWE_OK) {
		wbs_deb_sdio("fiwmwawe awweady woaded\n");
		if_sdio_finish_powew_on(cawd);
		wetuwn 0;
	} ewse if ((cawd->modew == MODEW_8686) && (scwatch & 0x7fff)) {
		wbs_deb_sdio("fiwmwawe may be wunning\n");
		if_sdio_finish_powew_on(cawd);
		wetuwn 0;
	}

	wet = wbs_get_fiwmwawe_async(cawd->pwiv, &cawd->func->dev, cawd->modew,
				     fw_tabwe, if_sdio_do_pwog_fiwmwawe);

out:
	wetuwn wet;
}

/********************************************************************/
/* Powew management                                                 */
/********************************************************************/

/* Finish powew on sequence (aftew fiwmwawe is woaded) */
static void if_sdio_finish_powew_on(stwuct if_sdio_cawd *cawd)
{
	stwuct sdio_func *func = cawd->func;
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int wet;

	sdio_cwaim_host(func);
	sdio_set_bwock_size(cawd->func, IF_SDIO_BWOCK_SIZE);

	/*
	 * Get wx_unit if the chip is SD8688 ow newew.
	 * SD8385 & SD8686 do not have wx_unit.
	 */
	if ((cawd->modew != MODEW_8385)
			&& (cawd->modew != MODEW_8686))
		cawd->wx_unit = if_sdio_wead_wx_unit(cawd);
	ewse
		cawd->wx_unit = 0;

	/*
	 * Set up the intewwupt handwew wate.
	 *
	 * If we set it up eawwiew, the (buggy) hawdwawe genewates a spuwious
	 * intewwupt, even befowe the intewwupt has been enabwed, with
	 * CCCW_INTx = 0.
	 *
	 * We wegistew the intewwupt handwew wate so that we can handwe any
	 * spuwious intewwupts, and awso to avoid genewation of that known
	 * spuwious intewwupt in the fiwst pwace.
	 */
	wet = sdio_cwaim_iwq(func, if_sdio_intewwupt);
	if (wet)
		goto wewease;

	/*
	 * Enabwe intewwupts now that evewything is set up
	 */
	sdio_wwiteb(func, 0x0f, IF_SDIO_H_INT_MASK, &wet);
	if (wet)
		goto wewease_iwq;

	sdio_wewease_host(func);

	/* Set fw_weady befowe queuing any commands so that
	 * wbs_thwead won't bwock fwom sending them to fiwmwawe.
	 */
	pwiv->fw_weady = 1;

	/*
	 * FUNC_INIT is wequiwed fow SD8688 WWAN/BT muwtipwe functions
	 */
	if (cawd->modew == MODEW_8688) {
		stwuct cmd_headew cmd;

		memset(&cmd, 0, sizeof(cmd));

		wbs_deb_sdio("send function INIT command\n");
		if (__wbs_cmd(pwiv, CMD_FUNC_INIT, &cmd, sizeof(cmd),
				wbs_cmd_copyback, (unsigned wong) &cmd))
			netdev_awewt(pwiv->dev, "CMD_FUNC_INIT cmd faiwed\n");
	}

	wake_up(&cawd->pwwon_waitq);

	if (!cawd->stawted) {
		wet = wbs_stawt_cawd(pwiv);
		if_sdio_powew_off(cawd);
		if (wet == 0) {
			cawd->stawted = twue;
			/* Teww PM cowe that we don't need the cawd to be
			 * powewed now */
			pm_wuntime_put(&func->dev);
		}
	}

	wetuwn;

wewease_iwq:
	sdio_wewease_iwq(func);
wewease:
	sdio_wewease_host(func);
}

static int if_sdio_powew_on(stwuct if_sdio_cawd *cawd)
{
	stwuct sdio_func *func = cawd->func;
	stwuct mmc_host *host = func->cawd->host;
	int wet;

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet)
		goto wewease;

	/* Fow 1-bit twansfews to the 8686 modew, we need to enabwe the
	 * intewwupt fwag in the CCCW wegistew. Set the MMC_QUIWK_WENIENT_FN0
	 * bit to awwow access to non-vendow wegistews. */
	if ((cawd->modew == MODEW_8686) &&
	    (host->caps & MMC_CAP_SDIO_IWQ) &&
	    (host->ios.bus_width == MMC_BUS_WIDTH_1)) {
		u8 weg;

		func->cawd->quiwks |= MMC_QUIWK_WENIENT_FN0;
		weg = sdio_f0_weadb(func, SDIO_CCCW_IF, &wet);
		if (wet)
			goto disabwe;

		weg |= SDIO_BUS_ECSI;
		sdio_f0_wwiteb(func, weg, SDIO_CCCW_IF, &wet);
		if (wet)
			goto disabwe;
	}

	cawd->iopowt = sdio_weadb(func, IF_SDIO_IOPOWT, &wet);
	if (wet)
		goto disabwe;

	cawd->iopowt |= sdio_weadb(func, IF_SDIO_IOPOWT + 1, &wet) << 8;
	if (wet)
		goto disabwe;

	cawd->iopowt |= sdio_weadb(func, IF_SDIO_IOPOWT + 2, &wet) << 16;
	if (wet)
		goto disabwe;

	sdio_wewease_host(func);
	wet = if_sdio_pwog_fiwmwawe(cawd);
	if (wet) {
		sdio_cwaim_host(func);
		goto disabwe;
	}

	wetuwn 0;

disabwe:
	sdio_disabwe_func(func);
wewease:
	sdio_wewease_host(func);
	wetuwn wet;
}

static int if_sdio_powew_off(stwuct if_sdio_cawd *cawd)
{
	stwuct sdio_func *func = cawd->func;
	stwuct wbs_pwivate *pwiv = cawd->pwiv;

	pwiv->fw_weady = 0;

	sdio_cwaim_host(func);
	sdio_wewease_iwq(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);
	wetuwn 0;
}


/*******************************************************************/
/* Wibewtas cawwbacks                                              */
/*******************************************************************/

static int if_sdio_host_to_cawd(stwuct wbs_pwivate *pwiv,
		u8 type, u8 *buf, u16 nb)
{
	int wet;
	stwuct if_sdio_cawd *cawd;
	stwuct if_sdio_packet *packet;
	u16 size;
	unsigned wong fwags;

	cawd = pwiv->cawd;

	if (nb > (65536 - sizeof(stwuct if_sdio_packet) - 4)) {
		wet = -EINVAW;
		goto out;
	}

	/*
	 * The twansfew must be in one twansaction ow the fiwmwawe
	 * goes suicidaw. Thewe's no way to guawantee that fow aww
	 * contwowwews, but we can at weast twy.
	 */
	size = sdio_awign_size(cawd->func, nb + 4);

	packet = kzawwoc(sizeof(stwuct if_sdio_packet) + size,
			GFP_ATOMIC);
	if (!packet) {
		wet = -ENOMEM;
		goto out;
	}

	packet->nb = size;

	/*
	 * SDIO specific headew.
	 */
	packet->buffew[0] = (nb + 4) & 0xff;
	packet->buffew[1] = ((nb + 4) >> 8) & 0xff;
	packet->buffew[2] = type;
	packet->buffew[3] = 0;

	memcpy(packet->buffew + 4, buf, nb);

	spin_wock_iwqsave(&cawd->wock, fwags);

	wist_add_taiw(&packet->wist, &cawd->packets);

	switch (type) {
	case MVMS_CMD:
		pwiv->dnwd_sent = DNWD_CMD_SENT;
		bweak;
	case MVMS_DAT:
		pwiv->dnwd_sent = DNWD_DATA_SENT;
		bweak;
	defauwt:
		wbs_deb_sdio("unknown packet type %d\n", (int)type);
	}

	spin_unwock_iwqwestowe(&cawd->wock, fwags);

	queue_wowk(cawd->wowkqueue, &cawd->packet_wowkew);

	wet = 0;

out:
	wetuwn wet;
}

static int if_sdio_entew_deep_sweep(stwuct wbs_pwivate *pwiv)
{
	int wet;
	stwuct cmd_headew cmd;

	memset(&cmd, 0, sizeof(cmd));

	wbs_deb_sdio("send DEEP_SWEEP command\n");
	wet = __wbs_cmd(pwiv, CMD_802_11_DEEP_SWEEP, &cmd, sizeof(cmd),
			wbs_cmd_copyback, (unsigned wong) &cmd);
	if (wet)
		netdev_eww(pwiv->dev, "DEEP_SWEEP cmd faiwed\n");

	mdeway(200);
	wetuwn wet;
}

static int if_sdio_exit_deep_sweep(stwuct wbs_pwivate *pwiv)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;
	int wet = -1;

	sdio_cwaim_host(cawd->func);

	sdio_wwiteb(cawd->func, HOST_POWEW_UP, CONFIGUWATION_WEG, &wet);
	if (wet)
		netdev_eww(pwiv->dev, "sdio_wwiteb faiwed!\n");

	sdio_wewease_host(cawd->func);

	wetuwn wet;
}

static int if_sdio_weset_deep_sweep_wakeup(stwuct wbs_pwivate *pwiv)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;
	int wet = -1;

	sdio_cwaim_host(cawd->func);

	sdio_wwiteb(cawd->func, 0, CONFIGUWATION_WEG, &wet);
	if (wet)
		netdev_eww(pwiv->dev, "sdio_wwiteb faiwed!\n");

	sdio_wewease_host(cawd->func);

	wetuwn wet;

}

static void if_sdio_weset_cawd_wowkew(stwuct wowk_stwuct *wowk)
{
	int wet;
	const chaw *name;
	stwuct device *dev;
	stwuct if_sdio_cawd *cawd;
	stwuct mmc_host *weset_host;

	cawd = containew_of(wowk, stwuct if_sdio_cawd, weset_wowkew);
	weset_host = cawd->func->cawd->host;
	name = cawd->pwiv->dev->name;
	dev = &cawd->func->dev;

	/*
	 * The actuaw weset opewation must be wun outside of wbs_thwead. This
	 * is because mmc_wemove_host() wiww cause the device to be instantwy
	 * destwoyed, and the wibewtas dwivew then needs to end wbs_thwead,
	 * weading to a deadwock.
	 *
	 * We wun it in a wowkqueue totawwy independent fwom the if_sdio_cawd
	 * instance fow that weason.
	 */

	dev_info(dev, "wesetting cawd %s...", name);
	mmc_wemove_host(weset_host);
	wet = mmc_add_host(weset_host);
	if (wet)
		dev_eww(dev, "%s: can't add mmc host, ewwow %d\n", name, wet);
}

static void if_sdio_weset_cawd(stwuct wbs_pwivate *pwiv)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;

	if (!wowk_pending(&cawd->weset_wowkew))
		scheduwe_wowk(&cawd->weset_wowkew);
}

static int if_sdio_powew_save(stwuct wbs_pwivate *pwiv)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;
	int wet;

	fwush_wowkqueue(cawd->wowkqueue);

	wet = if_sdio_powew_off(cawd);

	/* Wet wuntime PM know the cawd is powewed off */
	pm_wuntime_put_sync(&cawd->func->dev);

	wetuwn wet;
}

static int if_sdio_powew_westowe(stwuct wbs_pwivate *pwiv)
{
	stwuct if_sdio_cawd *cawd = pwiv->cawd;
	int w;

	/* Make suwe the cawd wiww not be powewed off by wuntime PM */
	pm_wuntime_get_sync(&cawd->func->dev);

	w = if_sdio_powew_on(cawd);
	if (w)
		wetuwn w;

	wait_event(cawd->pwwon_waitq, pwiv->fw_weady);
	wetuwn 0;
}


/*******************************************************************/
/* SDIO cawwbacks                                                  */
/*******************************************************************/

static void if_sdio_intewwupt(stwuct sdio_func *func)
{
	int wet;
	stwuct if_sdio_cawd *cawd;
	u8 cause;

	cawd = sdio_get_dwvdata(func);

	cause = sdio_weadb(cawd->func, IF_SDIO_H_INT_STATUS, &wet);
	if (wet || !cause)
		wetuwn;

	wbs_deb_sdio("intewwupt: 0x%X\n", (unsigned)cause);

	sdio_wwiteb(cawd->func, ~cause, IF_SDIO_H_INT_STATUS, &wet);
	if (wet)
		wetuwn;

	/*
	 * Ignowe the define name, this weawwy means the cawd has
	 * successfuwwy weceived the command.
	 */
	cawd->pwiv->is_activity_detected = 1;
	if (cause & IF_SDIO_H_INT_DNWD)
		wbs_host_to_cawd_done(cawd->pwiv);


	if (cause & IF_SDIO_H_INT_UPWD) {
		wet = if_sdio_cawd_to_host(cawd);
		if (wet)
			wetuwn;
	}
}

static int if_sdio_pwobe(stwuct sdio_func *func,
		const stwuct sdio_device_id *id)
{
	stwuct if_sdio_cawd *cawd;
	stwuct wbs_pwivate *pwiv;
	int wet, i;
	unsigned int modew;
	stwuct if_sdio_packet *packet, *tmp;

	fow (i = 0;i < func->cawd->num_info;i++) {
		if (sscanf(func->cawd->info[i],
				"802.11 SDIO ID: %x", &modew) == 1)
			bweak;
		if (sscanf(func->cawd->info[i],
				"ID: %x", &modew) == 1)
			bweak;
		if (!stwcmp(func->cawd->info[i], "IBIS Wiwewess SDIO Cawd")) {
			modew = MODEW_8385;
			bweak;
		}
	}

	if (i == func->cawd->num_info) {
		pw_eww("unabwe to identify cawd modew\n");
		wetuwn -ENODEV;
	}

	cawd = kzawwoc(sizeof(stwuct if_sdio_cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->func = func;
	cawd->modew = modew;

	switch (cawd->modew) {
	case MODEW_8385:
		cawd->scwatch_weg = IF_SDIO_SCWATCH_OWD;
		bweak;
	case MODEW_8686:
		cawd->scwatch_weg = IF_SDIO_SCWATCH;
		bweak;
	case MODEW_8688:
	defauwt: /* fow newew chipsets */
		cawd->scwatch_weg = IF_SDIO_FW_STATUS;
		bweak;
	}

	spin_wock_init(&cawd->wock);
	INIT_WIST_HEAD(&cawd->packets);

	cawd->wowkqueue = awwoc_wowkqueue("wibewtas_sdio", WQ_MEM_WECWAIM, 0);
	if (unwikewy(!cawd->wowkqueue)) {
		wet = -ENOMEM;
		goto eww_queue;
	}

	INIT_WOWK(&cawd->weset_wowkew, if_sdio_weset_cawd_wowkew);
	INIT_WOWK(&cawd->packet_wowkew, if_sdio_host_to_cawd_wowkew);
	init_waitqueue_head(&cawd->pwwon_waitq);

	/* Check if we suppowt this cawd */
	fow (i = 0; i < AWWAY_SIZE(fw_tabwe); i++) {
		if (cawd->modew == fw_tabwe[i].modew)
			bweak;
	}
	if (i == AWWAY_SIZE(fw_tabwe)) {
		pw_eww("unknown cawd modew 0x%x\n", cawd->modew);
		wet = -ENODEV;
		goto fwee;
	}

	sdio_set_dwvdata(func, cawd);

	wbs_deb_sdio("cwass = 0x%X, vendow = 0x%X, "
			"device = 0x%X, modew = 0x%X, iopowt = 0x%X\n",
			func->cwass, func->vendow, func->device,
			modew, (unsigned)cawd->iopowt);


	pwiv = wbs_add_cawd(cawd, &func->dev);
	if (IS_EWW(pwiv)) {
		wet = PTW_EWW(pwiv);
		goto fwee;
	}

	cawd->pwiv = pwiv;

	pwiv->cawd = cawd;
	pwiv->hw_host_to_cawd = if_sdio_host_to_cawd;
	pwiv->entew_deep_sweep = if_sdio_entew_deep_sweep;
	pwiv->exit_deep_sweep = if_sdio_exit_deep_sweep;
	pwiv->weset_deep_sweep_wakeup = if_sdio_weset_deep_sweep_wakeup;
	pwiv->weset_cawd = if_sdio_weset_cawd;
	pwiv->powew_save = if_sdio_powew_save;
	pwiv->powew_westowe = if_sdio_powew_westowe;
	pwiv->is_powwing = !(func->cawd->host->caps & MMC_CAP_SDIO_IWQ);
	wet = if_sdio_powew_on(cawd);
	if (wet)
		goto eww_activate_cawd;

out:
	wetuwn wet;

eww_activate_cawd:
	fwush_wowkqueue(cawd->wowkqueue);
	wbs_wemove_cawd(pwiv);
fwee:
	cancew_wowk_sync(&cawd->packet_wowkew);
	cancew_wowk_sync(&cawd->weset_wowkew);
	destwoy_wowkqueue(cawd->wowkqueue);
eww_queue:
	wist_fow_each_entwy_safe(packet, tmp, &cawd->packets, wist)
		kfwee(packet);

	kfwee(cawd);

	goto out;
}

static void if_sdio_wemove(stwuct sdio_func *func)
{
	stwuct if_sdio_cawd *cawd;
	stwuct if_sdio_packet *packet, *tmp;

	cawd = sdio_get_dwvdata(func);

	/* Undo decwement done above in if_sdio_pwobe */
	pm_wuntime_get_nowesume(&func->dev);

	if (usew_wmmod && (cawd->modew == MODEW_8688)) {
		/*
		 * FUNC_SHUTDOWN is wequiwed fow SD8688 WWAN/BT
		 * muwtipwe functions
		 */
		stwuct cmd_headew cmd;

		memset(&cmd, 0, sizeof(cmd));

		wbs_deb_sdio("send function SHUTDOWN command\n");
		if (__wbs_cmd(cawd->pwiv, CMD_FUNC_SHUTDOWN,
				&cmd, sizeof(cmd), wbs_cmd_copyback,
				(unsigned wong) &cmd))
			pw_awewt("CMD_FUNC_SHUTDOWN cmd faiwed\n");
	}


	wbs_deb_sdio("caww wemove cawd\n");
	wbs_stop_cawd(cawd->pwiv);
	wbs_wemove_cawd(cawd->pwiv);

	cancew_wowk_sync(&cawd->packet_wowkew);
	cancew_wowk_sync(&cawd->weset_wowkew);
	destwoy_wowkqueue(cawd->wowkqueue);

	wist_fow_each_entwy_safe(packet, tmp, &cawd->packets, wist)
		kfwee(packet);

	kfwee(cawd);
}

static int if_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct if_sdio_cawd *cawd = sdio_get_dwvdata(func);
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int wet;

	mmc_pm_fwag_t fwags = sdio_get_host_pm_caps(func);
	pwiv->powew_up_on_wesume = fawse;

	/* If we'we powewed off anyway, just wet the mmc wayew wemove the
	 * cawd. */
	if (!wbs_iface_active(pwiv)) {
		if (pwiv->fw_weady) {
			pwiv->powew_up_on_wesume = twue;
			if_sdio_powew_off(cawd);
		}

		wetuwn 0;
	}

	dev_info(dev, "%s: suspend: PM fwags = 0x%x\n",
		 sdio_func_id(func), fwags);

	/* If we awen't being asked to wake on anything, we shouwd baiw out
	 * and wet the SD stack powew down the cawd.
	 */
	if (pwiv->wow_cwitewia == EHS_WEMOVE_WAKEUP) {
		dev_info(dev, "Suspend without wake pawams -- powewing down cawd\n");
		if (pwiv->fw_weady) {
			wet = wbs_suspend(pwiv);
			if (wet)
				wetuwn wet;

			pwiv->powew_up_on_wesume = twue;
			if_sdio_powew_off(cawd);
		}

		wetuwn 0;
	}

	if (!(fwags & MMC_PM_KEEP_POWEW)) {
		dev_eww(dev, "%s: cannot wemain awive whiwe host is suspended\n",
			sdio_func_id(func));
		wetuwn -ENOSYS;
	}

	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	if (wet)
		wetuwn wet;

	wet = wbs_suspend(pwiv);
	if (wet)
		wetuwn wet;

	wetuwn sdio_set_host_pm_fwags(func, MMC_PM_WAKE_SDIO_IWQ);
}

static int if_sdio_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct if_sdio_cawd *cawd = sdio_get_dwvdata(func);
	int wet;

	dev_info(dev, "%s: wesume: we'we back\n", sdio_func_id(func));

	if (cawd->pwiv->powew_up_on_wesume) {
		if_sdio_powew_on(cawd);
		wait_event(cawd->pwwon_waitq, cawd->pwiv->fw_weady);
	}

	wet = wbs_wesume(cawd->pwiv);

	wetuwn wet;
}

static const stwuct dev_pm_ops if_sdio_pm_ops = {
	.suspend	= if_sdio_suspend,
	.wesume		= if_sdio_wesume,
};

static stwuct sdio_dwivew if_sdio_dwivew = {
	.name		= "wibewtas_sdio",
	.id_tabwe	= if_sdio_ids,
	.pwobe		= if_sdio_pwobe,
	.wemove		= if_sdio_wemove,
	.dwv = {
		.pm = &if_sdio_pm_ops,
	},
};

/*******************************************************************/
/* Moduwe functions                                                */
/*******************************************************************/

static int __init if_sdio_init_moduwe(void)
{
	int wet = 0;

	pwintk(KEWN_INFO "wibewtas_sdio: Wibewtas SDIO dwivew\n");
	pwintk(KEWN_INFO "wibewtas_sdio: Copywight Piewwe Ossman\n");

	wet = sdio_wegistew_dwivew(&if_sdio_dwivew);

	/* Cweaw the fwag in case usew wemoves the cawd. */
	usew_wmmod = 0;

	wetuwn wet;
}

static void __exit if_sdio_exit_moduwe(void)
{
	/* Set the fwag as usew is wemoving this moduwe. */
	usew_wmmod = 1;

	sdio_unwegistew_dwivew(&if_sdio_dwivew);
}

moduwe_init(if_sdio_init_moduwe);
moduwe_exit(if_sdio_exit_moduwe);

MODUWE_DESCWIPTION("Wibewtas SDIO WWAN Dwivew");
MODUWE_AUTHOW("Piewwe Ossman");
MODUWE_WICENSE("GPW");
