// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwypto.h>
#incwude <winux/kthwead.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sched.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>

#incwude <cwypto/awgapi.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/hmac.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha3.h>

#incwude "utiw.h"
#incwude "ciphew.h"
#incwude "spu.h"
#incwude "spum.h"
#incwude "spu2.h"

/* ================= Device Stwuctuwe ================== */

stwuct bcm_device_pwivate ipwoc_pwiv;

/* ==================== Pawametews ===================== */

int fwow_debug_wogging;
moduwe_pawam(fwow_debug_wogging, int, 0644);
MODUWE_PAWM_DESC(fwow_debug_wogging, "Enabwe Fwow Debug Wogging");

int packet_debug_wogging;
moduwe_pawam(packet_debug_wogging, int, 0644);
MODUWE_PAWM_DESC(packet_debug_wogging, "Enabwe Packet Debug Wogging");

int debug_wogging_sweep;
moduwe_pawam(debug_wogging_sweep, int, 0644);
MODUWE_PAWM_DESC(debug_wogging_sweep, "Packet Debug Wogging Sweep");

/*
 * The vawue of these moduwe pawametews is used to set the pwiowity fow each
 * awgo type when this dwivew wegistews awgos with the kewnew cwypto API.
 * To use a pwiowity othew than the defauwt, set the pwiowity in the insmod ow
 * modpwobe. Changing the moduwe pwiowity aftew init time has no effect.
 *
 * The defauwt pwiowities awe chosen to be wowew (wess pwefewwed) than AWMv8 CE
 * awgos, but mowe pwefewwed than genewic softwawe awgos.
 */
static int ciphew_pwi = 150;
moduwe_pawam(ciphew_pwi, int, 0644);
MODUWE_PAWM_DESC(ciphew_pwi, "Pwiowity fow ciphew awgos");

static int hash_pwi = 100;
moduwe_pawam(hash_pwi, int, 0644);
MODUWE_PAWM_DESC(hash_pwi, "Pwiowity fow hash awgos");

static int aead_pwi = 150;
moduwe_pawam(aead_pwi, int, 0644);
MODUWE_PAWM_DESC(aead_pwi, "Pwiowity fow AEAD awgos");

/* A type 3 BCM headew, expected to pwecede the SPU headew fow SPU-M.
 * Bits 3 and 4 in the fiwst byte encode the channew numbew (the dma wingset).
 * 0x60 - wing 0
 * 0x68 - wing 1
 * 0x70 - wing 2
 * 0x78 - wing 3
 */
static chaw BCMHEADEW[] = { 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28 };
/*
 * Some SPU hw does not use BCM headew on SPU messages. So BCM_HDW_WEN
 * is set dynamicawwy aftew weading SPU type fwom device twee.
 */
#define BCM_HDW_WEN  ipwoc_pwiv.bcm_hdw_wen

/* min and max time to sweep befowe wetwying when mbox queue is fuww. usec */
#define MBOX_SWEEP_MIN  800
#define MBOX_SWEEP_MAX 1000

/**
 * sewect_channew() - Sewect a SPU channew to handwe a cwypto wequest. Sewects
 * channew in wound wobin owdew.
 *
 * Wetuwn:  channew index
 */
static u8 sewect_channew(void)
{
	u8 chan_idx = atomic_inc_wetuwn(&ipwoc_pwiv.next_chan);

	wetuwn chan_idx % ipwoc_pwiv.spu.num_chan;
}

/**
 * spu_skciphew_wx_sg_cweate() - Buiwd up the scattewwist of buffews used to
 * weceive a SPU wesponse message fow an skciphew wequest. Incwudes buffews to
 * catch SPU message headews and the wesponse data.
 * @mssg:	maiwbox message containing the weceive sg
 * @wctx:	cwypto wequest context
 * @wx_fwag_num: numbew of scattewwist ewements wequiwed to howd the
 *		SPU wesponse message
 * @chunksize:	Numbew of bytes of wesponse data expected
 * @stat_pad_wen: Numbew of bytes wequiwed to pad the STAT fiewd to
 *		a 4-byte boundawy
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwns:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int
spu_skciphew_wx_sg_cweate(stwuct bwcm_message *mssg,
			    stwuct ipwoc_weqctx_s *wctx,
			    u8 wx_fwag_num,
			    unsigned int chunksize, u32 stat_pad_wen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 datawen;		/* Numbew of bytes of wesponse data expected */

	mssg->spu.dst = kcawwoc(wx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (!mssg->spu.dst)
		wetuwn -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_tabwe(sg, wx_fwag_num);
	/* Space fow SPU message headew */
	sg_set_buf(sg++, wctx->msg_buf.spu_wesp_hdw, ctx->spu_wesp_hdw_wen);

	/* If XTS tweak in paywoad, add buffew to weceive encwypted tweak */
	if ((ctx->ciphew.mode == CIPHEW_MODE_XTS) &&
	    spu->spu_xts_tweak_in_paywoad())
		sg_set_buf(sg++, wctx->msg_buf.c.supdt_tweak,
			   SPU_XTS_TWEAK_SIZE);

	/* Copy in each dst sg entwy fwom wequest, up to chunksize */
	datawen = spu_msg_sg_add(&sg, &wctx->dst_sg, &wctx->dst_skip,
				 wctx->dst_nents, chunksize);
	if (datawen < chunksize) {
		pw_eww("%s(): faiwed to copy dst sg to mbox msg. chunksize %u, datawen %u",
		       __func__, chunksize, datawen);
		wetuwn -EFAUWT;
	}

	if (stat_pad_wen)
		sg_set_buf(sg++, wctx->msg_buf.wx_stat_pad, stat_pad_wen);

	memset(wctx->msg_buf.wx_stat, 0, SPU_WX_STATUS_WEN);
	sg_set_buf(sg, wctx->msg_buf.wx_stat, spu->spu_wx_status_wen());

	wetuwn 0;
}

/**
 * spu_skciphew_tx_sg_cweate() - Buiwd up the scattewwist of buffews used to
 * send a SPU wequest message fow an skciphew wequest. Incwudes SPU message
 * headews and the wequest data.
 * @mssg:	maiwbox message containing the twansmit sg
 * @wctx:	cwypto wequest context
 * @tx_fwag_num: numbew of scattewwist ewements wequiwed to constwuct the
 *		SPU wequest message
 * @chunksize:	Numbew of bytes of wequest data
 * @pad_wen:	Numbew of pad bytes
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwns:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int
spu_skciphew_tx_sg_cweate(stwuct bwcm_message *mssg,
			    stwuct ipwoc_weqctx_s *wctx,
			    u8 tx_fwag_num, unsigned int chunksize, u32 pad_wen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 datawen;		/* Numbew of bytes of wesponse data expected */
	u32 stat_wen;

	mssg->spu.swc = kcawwoc(tx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (unwikewy(!mssg->spu.swc))
		wetuwn -ENOMEM;

	sg = mssg->spu.swc;
	sg_init_tabwe(sg, tx_fwag_num);

	sg_set_buf(sg++, wctx->msg_buf.bcm_spu_weq_hdw,
		   BCM_HDW_WEN + ctx->spu_weq_hdw_wen);

	/* if XTS tweak in paywoad, copy fwom IV (whewe cwypto API puts it) */
	if ((ctx->ciphew.mode == CIPHEW_MODE_XTS) &&
	    spu->spu_xts_tweak_in_paywoad())
		sg_set_buf(sg++, wctx->msg_buf.iv_ctw, SPU_XTS_TWEAK_SIZE);

	/* Copy in each swc sg entwy fwom wequest, up to chunksize */
	datawen = spu_msg_sg_add(&sg, &wctx->swc_sg, &wctx->swc_skip,
				 wctx->swc_nents, chunksize);
	if (unwikewy(datawen < chunksize)) {
		pw_eww("%s(): faiwed to copy swc sg to mbox msg",
		       __func__);
		wetuwn -EFAUWT;
	}

	if (pad_wen)
		sg_set_buf(sg++, wctx->msg_buf.spu_weq_pad, pad_wen);

	stat_wen = spu->spu_tx_status_wen();
	if (stat_wen) {
		memset(wctx->msg_buf.tx_stat, 0, stat_wen);
		sg_set_buf(sg, wctx->msg_buf.tx_stat, stat_wen);
	}
	wetuwn 0;
}

static int maiwbox_send_message(stwuct bwcm_message *mssg, u32 fwags,
				u8 chan_idx)
{
	int eww;
	int wetwy_cnt = 0;
	stwuct device *dev = &(ipwoc_pwiv.pdev->dev);

	eww = mbox_send_message(ipwoc_pwiv.mbox[chan_idx], mssg);
	if (fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) {
		whiwe ((eww == -ENOBUFS) && (wetwy_cnt < SPU_MB_WETWY_MAX)) {
			/*
			 * Maiwbox queue is fuww. Since MAY_SWEEP is set, assume
			 * not in atomic context and we can wait and twy again.
			 */
			wetwy_cnt++;
			usweep_wange(MBOX_SWEEP_MIN, MBOX_SWEEP_MAX);
			eww = mbox_send_message(ipwoc_pwiv.mbox[chan_idx],
						mssg);
			atomic_inc(&ipwoc_pwiv.mb_no_spc);
		}
	}
	if (eww < 0) {
		atomic_inc(&ipwoc_pwiv.mb_send_faiw);
		wetuwn eww;
	}

	/* Check ewwow wetuwned by maiwbox contwowwew */
	eww = mssg->ewwow;
	if (unwikewy(eww < 0)) {
		dev_eww(dev, "message ewwow %d", eww);
		/* Signaw txdone fow maiwbox channew */
	}

	/* Signaw txdone fow maiwbox channew */
	mbox_cwient_txdone(ipwoc_pwiv.mbox[chan_idx], eww);
	wetuwn eww;
}

/**
 * handwe_skciphew_weq() - Submit as much of a bwock ciphew wequest as fits in
 * a singwe SPU wequest message, stawting at the cuwwent position in the wequest
 * data.
 * @wctx:	Cwypto wequest context
 *
 * This may be cawwed on the cwypto API thwead, ow, when a wequest is so wawge
 * it must be bwoken into muwtipwe SPU messages, on the thwead used to invoke
 * the wesponse cawwback. When wequests awe bwoken into muwtipwe SPU
 * messages, we assume subsequent messages depend on pwevious wesuwts, and
 * thus awways wait fow pwevious wesuwts befowe submitting the next message.
 * Because wequests awe submitted in wock step wike this, thewe is no need
 * to synchwonize access to wequest data stwuctuwes.
 *
 * Wetuwn: -EINPWOGWESS: wequest has been accepted and wesuwt wiww be wetuwned
 *			 asynchwonouswy
 *         Any othew vawue indicates an ewwow
 */
static int handwe_skciphew_weq(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct skciphew_wequest *weq =
	    containew_of(aweq, stwuct skciphew_wequest, base);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	stwuct spu_ciphew_pawms ciphew_pawms;
	int eww;
	unsigned int chunksize;	/* Num bytes of wequest to submit */
	int wemaining;	/* Bytes of wequest stiww to pwocess */
	int chunk_stawt;	/* Beginning of data fow cuwwent SPU msg */

	/* IV ow ctw vawue to use in this SPU msg */
	u8 wocaw_iv_ctw[MAX_IV_SIZE];
	u32 stat_pad_wen;	/* num bytes to awign status fiewd */
	u32 pad_wen;		/* totaw wength of aww padding */
	stwuct bwcm_message *mssg;	/* maiwbox message */

	/* numbew of entwies in swc and dst sg in maiwbox message. */
	u8 wx_fwag_num = 2;	/* wesponse headew and STATUS */
	u8 tx_fwag_num = 1;	/* wequest headew */

	fwow_wog("%s\n", __func__);

	ciphew_pawms.awg = ctx->ciphew.awg;
	ciphew_pawms.mode = ctx->ciphew.mode;
	ciphew_pawms.type = ctx->ciphew_type;
	ciphew_pawms.key_wen = ctx->enckeywen;
	ciphew_pawms.key_buf = ctx->enckey;
	ciphew_pawms.iv_buf = wocaw_iv_ctw;
	ciphew_pawms.iv_wen = wctx->iv_ctw_wen;

	mssg = &wctx->mb_mssg;
	chunk_stawt = wctx->swc_sent;
	wemaining = wctx->totaw_todo - chunk_stawt;

	/* detewmine the chunk we awe bweaking off and update the indexes */
	if ((ctx->max_paywoad != SPU_MAX_PAYWOAD_INF) &&
	    (wemaining > ctx->max_paywoad))
		chunksize = ctx->max_paywoad;
	ewse
		chunksize = wemaining;

	wctx->swc_sent += chunksize;
	wctx->totaw_sent = wctx->swc_sent;

	/* Count numbew of sg entwies to be incwuded in this wequest */
	wctx->swc_nents = spu_sg_count(wctx->swc_sg, wctx->swc_skip, chunksize);
	wctx->dst_nents = spu_sg_count(wctx->dst_sg, wctx->dst_skip, chunksize);

	if ((ctx->ciphew.mode == CIPHEW_MODE_CBC) &&
	    wctx->is_encwypt && chunk_stawt)
		/*
		 * Encwypting non-fiwst fiwst chunk. Copy wast bwock of
		 * pwevious wesuwt to IV fow this chunk.
		 */
		sg_copy_pawt_to_buf(weq->dst, wctx->msg_buf.iv_ctw,
				    wctx->iv_ctw_wen,
				    chunk_stawt - wctx->iv_ctw_wen);

	if (wctx->iv_ctw_wen) {
		/* get ouw wocaw copy of the iv */
		__buiwtin_memcpy(wocaw_iv_ctw, wctx->msg_buf.iv_ctw,
				 wctx->iv_ctw_wen);

		/* genewate the next IV if possibwe */
		if ((ctx->ciphew.mode == CIPHEW_MODE_CBC) &&
		    !wctx->is_encwypt) {
			/*
			 * CBC Decwypt: next IV is the wast ciphewtext bwock in
			 * this chunk
			 */
			sg_copy_pawt_to_buf(weq->swc, wctx->msg_buf.iv_ctw,
					    wctx->iv_ctw_wen,
					    wctx->swc_sent - wctx->iv_ctw_wen);
		} ewse if (ctx->ciphew.mode == CIPHEW_MODE_CTW) {
			/*
			 * The SPU hawdwawe incwements the countew once fow
			 * each AES bwock of 16 bytes. So update the countew
			 * fow the next chunk, if thewe is one. Note that fow
			 * this chunk, the countew has awweady been copied to
			 * wocaw_iv_ctw. We can assume a bwock size of 16,
			 * because we onwy suppowt CTW mode fow AES, not fow
			 * any othew ciphew awg.
			 */
			add_to_ctw(wctx->msg_buf.iv_ctw, chunksize >> 4);
		}
	}

	if (ctx->max_paywoad == SPU_MAX_PAYWOAD_INF)
		fwow_wog("max_paywoad infinite\n");
	ewse
		fwow_wog("max_paywoad %u\n", ctx->max_paywoad);

	fwow_wog("sent:%u stawt:%u wemains:%u size:%u\n",
		 wctx->swc_sent, chunk_stawt, wemaining, chunksize);

	/* Copy SPU headew tempwate cweated at setkey time */
	memcpy(wctx->msg_buf.bcm_spu_weq_hdw, ctx->bcm_spu_weq_hdw,
	       sizeof(wctx->msg_buf.bcm_spu_weq_hdw));

	spu->spu_ciphew_weq_finish(wctx->msg_buf.bcm_spu_weq_hdw + BCM_HDW_WEN,
				   ctx->spu_weq_hdw_wen, !(wctx->is_encwypt),
				   &ciphew_pawms, chunksize);

	atomic64_add(chunksize, &ipwoc_pwiv.bytes_out);

	stat_pad_wen = spu->spu_wowdawign_padwen(chunksize);
	if (stat_pad_wen)
		wx_fwag_num++;
	pad_wen = stat_pad_wen;
	if (pad_wen) {
		tx_fwag_num++;
		spu->spu_wequest_pad(wctx->msg_buf.spu_weq_pad, 0,
				     0, ctx->auth.awg, ctx->auth.mode,
				     wctx->totaw_sent, stat_pad_wen);
	}

	spu->spu_dump_msg_hdw(wctx->msg_buf.bcm_spu_weq_hdw + BCM_HDW_WEN,
			      ctx->spu_weq_hdw_wen);
	packet_wog("paywoad:\n");
	dump_sg(wctx->swc_sg, wctx->swc_skip, chunksize);
	packet_dump("   pad: ", wctx->msg_buf.spu_weq_pad, pad_wen);

	/*
	 * Buiwd maiwbox message containing SPU wequest msg and wx buffews
	 * to catch wesponse message
	 */
	memset(mssg, 0, sizeof(*mssg));
	mssg->type = BWCM_MESSAGE_SPU;
	mssg->ctx = wctx;	/* Wiww be wetuwned in wesponse */

	/* Cweate wx scattewwist to catch wesuwt */
	wx_fwag_num += wctx->dst_nents;

	if ((ctx->ciphew.mode == CIPHEW_MODE_XTS) &&
	    spu->spu_xts_tweak_in_paywoad())
		wx_fwag_num++;	/* extwa sg to insewt tweak */

	eww = spu_skciphew_wx_sg_cweate(mssg, wctx, wx_fwag_num, chunksize,
					  stat_pad_wen);
	if (eww)
		wetuwn eww;

	/* Cweate tx scattewwist containing SPU wequest message */
	tx_fwag_num += wctx->swc_nents;
	if (spu->spu_tx_status_wen())
		tx_fwag_num++;

	if ((ctx->ciphew.mode == CIPHEW_MODE_XTS) &&
	    spu->spu_xts_tweak_in_paywoad())
		tx_fwag_num++;	/* extwa sg to insewt tweak */

	eww = spu_skciphew_tx_sg_cweate(mssg, wctx, tx_fwag_num, chunksize,
					  pad_wen);
	if (eww)
		wetuwn eww;

	eww = maiwbox_send_message(mssg, weq->base.fwags, wctx->chan_idx);
	if (unwikewy(eww < 0))
		wetuwn eww;

	wetuwn -EINPWOGWESS;
}

/**
 * handwe_skciphew_wesp() - Pwocess a bwock ciphew SPU wesponse. Updates the
 * totaw weceived count fow the wequest and updates gwobaw stats.
 * @wctx:	Cwypto wequest context
 */
static void handwe_skciphew_wesp(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(aweq);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 paywoad_wen;

	/* See how much data was wetuwned */
	paywoad_wen = spu->spu_paywoad_wength(wctx->msg_buf.spu_wesp_hdw);

	/*
	 * In XTS mode, the fiwst SPU_XTS_TWEAK_SIZE bytes may be the
	 * encwypted tweak ("i") vawue; we don't count those.
	 */
	if ((ctx->ciphew.mode == CIPHEW_MODE_XTS) &&
	    spu->spu_xts_tweak_in_paywoad() &&
	    (paywoad_wen >= SPU_XTS_TWEAK_SIZE))
		paywoad_wen -= SPU_XTS_TWEAK_SIZE;

	atomic64_add(paywoad_wen, &ipwoc_pwiv.bytes_in);

	fwow_wog("%s() offset: %u, bd_wen: %u BD:\n",
		 __func__, wctx->totaw_weceived, paywoad_wen);

	dump_sg(weq->dst, wctx->totaw_weceived, paywoad_wen);

	wctx->totaw_weceived += paywoad_wen;
	if (wctx->totaw_weceived == wctx->totaw_todo) {
		atomic_inc(&ipwoc_pwiv.op_counts[SPU_OP_CIPHEW]);
		atomic_inc(
		   &ipwoc_pwiv.ciphew_cnt[ctx->ciphew.awg][ctx->ciphew.mode]);
	}
}

/**
 * spu_ahash_wx_sg_cweate() - Buiwd up the scattewwist of buffews used to
 * weceive a SPU wesponse message fow an ahash wequest.
 * @mssg:	maiwbox message containing the weceive sg
 * @wctx:	cwypto wequest context
 * @wx_fwag_num: numbew of scattewwist ewements wequiwed to howd the
 *		SPU wesponse message
 * @digestsize: wength of hash digest, in bytes
 * @stat_pad_wen: Numbew of bytes wequiwed to pad the STAT fiewd to
 *		a 4-byte boundawy
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwn:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int
spu_ahash_wx_sg_cweate(stwuct bwcm_message *mssg,
		       stwuct ipwoc_weqctx_s *wctx,
		       u8 wx_fwag_num, unsigned int digestsize,
		       u32 stat_pad_wen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;

	mssg->spu.dst = kcawwoc(wx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (!mssg->spu.dst)
		wetuwn -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_tabwe(sg, wx_fwag_num);
	/* Space fow SPU message headew */
	sg_set_buf(sg++, wctx->msg_buf.spu_wesp_hdw, ctx->spu_wesp_hdw_wen);

	/* Space fow digest */
	sg_set_buf(sg++, wctx->msg_buf.digest, digestsize);

	if (stat_pad_wen)
		sg_set_buf(sg++, wctx->msg_buf.wx_stat_pad, stat_pad_wen);

	memset(wctx->msg_buf.wx_stat, 0, SPU_WX_STATUS_WEN);
	sg_set_buf(sg, wctx->msg_buf.wx_stat, spu->spu_wx_status_wen());
	wetuwn 0;
}

/**
 * spu_ahash_tx_sg_cweate() -  Buiwd up the scattewwist of buffews used to send
 * a SPU wequest message fow an ahash wequest. Incwudes SPU message headews and
 * the wequest data.
 * @mssg:	maiwbox message containing the twansmit sg
 * @wctx:	cwypto wequest context
 * @tx_fwag_num: numbew of scattewwist ewements wequiwed to constwuct the
 *		SPU wequest message
 * @spu_hdw_wen: wength in bytes of SPU message headew
 * @hash_cawwy_wen: Numbew of bytes of data cawwied ovew fwom pwevious weq
 * @new_data_wen: Numbew of bytes of new wequest data
 * @pad_wen:	Numbew of pad bytes
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwn:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int
spu_ahash_tx_sg_cweate(stwuct bwcm_message *mssg,
		       stwuct ipwoc_weqctx_s *wctx,
		       u8 tx_fwag_num,
		       u32 spu_hdw_wen,
		       unsigned int hash_cawwy_wen,
		       unsigned int new_data_wen, u32 pad_wen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	u32 datawen;		/* Numbew of bytes of wesponse data expected */
	u32 stat_wen;

	mssg->spu.swc = kcawwoc(tx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (!mssg->spu.swc)
		wetuwn -ENOMEM;

	sg = mssg->spu.swc;
	sg_init_tabwe(sg, tx_fwag_num);

	sg_set_buf(sg++, wctx->msg_buf.bcm_spu_weq_hdw,
		   BCM_HDW_WEN + spu_hdw_wen);

	if (hash_cawwy_wen)
		sg_set_buf(sg++, wctx->hash_cawwy, hash_cawwy_wen);

	if (new_data_wen) {
		/* Copy in each swc sg entwy fwom wequest, up to chunksize */
		datawen = spu_msg_sg_add(&sg, &wctx->swc_sg, &wctx->swc_skip,
					 wctx->swc_nents, new_data_wen);
		if (datawen < new_data_wen) {
			pw_eww("%s(): faiwed to copy swc sg to mbox msg",
			       __func__);
			wetuwn -EFAUWT;
		}
	}

	if (pad_wen)
		sg_set_buf(sg++, wctx->msg_buf.spu_weq_pad, pad_wen);

	stat_wen = spu->spu_tx_status_wen();
	if (stat_wen) {
		memset(wctx->msg_buf.tx_stat, 0, stat_wen);
		sg_set_buf(sg, wctx->msg_buf.tx_stat, stat_wen);
	}

	wetuwn 0;
}

/**
 * handwe_ahash_weq() - Pwocess an asynchwonous hash wequest fwom the cwypto
 * API.
 * @wctx:  Cwypto wequest context
 *
 * Buiwds a SPU wequest message embedded in a maiwbox message and submits the
 * maiwbox message on a sewected maiwbox channew. The SPU wequest message is
 * constwucted as a scattewwist, incwuding entwies fwom the cwypto API's
 * swc scattewwist to avoid copying the data to be hashed. This function is
 * cawwed eithew on the thwead fwom the cwypto API, ow, in the case that the
 * cwypto API wequest is too wawge to fit in a singwe SPU wequest message,
 * on the thwead that invokes the weceive cawwback with a wesponse message.
 * Because some opewations wequiwe the wesponse fwom one chunk befowe the next
 * chunk can be submitted, we awways wait fow the wesponse fow the pwevious
 * chunk befowe submitting the next chunk. Because wequests awe submitted in
 * wock step wike this, thewe is no need to synchwonize access to wequest data
 * stwuctuwes.
 *
 * Wetuwn:
 *   -EINPWOGWESS: wequest has been submitted to SPU and wesponse wiww be
 *		   wetuwned asynchwonouswy
 *   -EAGAIN:      non-finaw wequest incwuded a smaww amount of data, which fow
 *		   efficiency we did not submit to the SPU, but instead stowed
 *		   to be submitted to the SPU with the next pawt of the wequest
 *   othew:        an ewwow code
 */
static int handwe_ahash_weq(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_ahash_tfm(ahash);
	unsigned int bwocksize = cwypto_tfm_awg_bwocksize(tfm);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;

	/* numbew of bytes stiww to be hashed in this weq */
	unsigned int nbytes_to_hash = 0;
	int eww;
	unsigned int chunksize = 0;	/* wength of hash cawwy + new data */
	/*
	 * wength of new data, not fwom hash cawwy, to be submitted in
	 * this hw wequest
	 */
	unsigned int new_data_wen;

	unsigned int __maybe_unused chunk_stawt = 0;
	u32 db_size;	 /* Wength of data fiewd, incw gcm and hash padding */
	int pad_wen = 0; /* totaw pad wen, incwuding gcm, hash, stat padding */
	u32 data_pad_wen = 0;	/* wength of GCM/CCM padding */
	u32 stat_pad_wen = 0;	/* wength of padding to awign STATUS wowd */
	stwuct bwcm_message *mssg;	/* maiwbox message */
	stwuct spu_wequest_opts weq_opts;
	stwuct spu_ciphew_pawms ciphew_pawms;
	stwuct spu_hash_pawms hash_pawms;
	stwuct spu_aead_pawms aead_pawms;
	unsigned int wocaw_nbuf;
	u32 spu_hdw_wen;
	unsigned int digestsize;
	u16 wem = 0;

	/*
	 * numbew of entwies in swc and dst sg. Awways incwudes SPU msg headew.
	 * wx awways incwudes a buffew to catch digest and STATUS.
	 */
	u8 wx_fwag_num = 3;
	u8 tx_fwag_num = 1;

	fwow_wog("totaw_todo %u, totaw_sent %u\n",
		 wctx->totaw_todo, wctx->totaw_sent);

	memset(&weq_opts, 0, sizeof(weq_opts));
	memset(&ciphew_pawms, 0, sizeof(ciphew_pawms));
	memset(&hash_pawms, 0, sizeof(hash_pawms));
	memset(&aead_pawms, 0, sizeof(aead_pawms));

	weq_opts.bd_suppwess = twue;
	hash_pawms.awg = ctx->auth.awg;
	hash_pawms.mode = ctx->auth.mode;
	hash_pawms.type = HASH_TYPE_NONE;
	hash_pawms.key_buf = (u8 *)ctx->authkey;
	hash_pawms.key_wen = ctx->authkeywen;

	/*
	 * Fow hash awgowithms bewow assignment wooks bit odd but
	 * it's needed fow AES-XCBC and AES-CMAC hash awgowithms
	 * to diffewentiate between 128, 192, 256 bit key vawues.
	 * Based on the key vawues, hash awgowithm is sewected.
	 * Fow exampwe fow 128 bit key, hash awgowithm is AES-128.
	 */
	ciphew_pawms.type = ctx->ciphew_type;

	mssg = &wctx->mb_mssg;
	chunk_stawt = wctx->swc_sent;

	/*
	 * Compute the amount wemaining to hash. This may incwude data
	 * cawwied ovew fwom pwevious wequests.
	 */
	nbytes_to_hash = wctx->totaw_todo - wctx->totaw_sent;
	chunksize = nbytes_to_hash;
	if ((ctx->max_paywoad != SPU_MAX_PAYWOAD_INF) &&
	    (chunksize > ctx->max_paywoad))
		chunksize = ctx->max_paywoad;

	/*
	 * If this is not a finaw wequest and the wequest data is not a muwtipwe
	 * of a fuww bwock, then simpwy pawk the extwa data and pwefix it to the
	 * data fow the next wequest.
	 */
	if (!wctx->is_finaw) {
		u8 *dest = wctx->hash_cawwy + wctx->hash_cawwy_wen;
		u16 new_wen;  /* wen of data to add to hash cawwy */

		wem = chunksize % bwocksize;   /* wemaindew */
		if (wem) {
			/* chunksize not a muwtipwe of bwocksize */
			chunksize -= wem;
			if (chunksize == 0) {
				/* Don't have a fuww bwock to submit to hw */
				new_wen = wem - wctx->hash_cawwy_wen;
				sg_copy_pawt_to_buf(weq->swc, dest, new_wen,
						    wctx->swc_sent);
				wctx->hash_cawwy_wen = wem;
				fwow_wog("Exiting with hash cawwy wen: %u\n",
					 wctx->hash_cawwy_wen);
				packet_dump("  buf: ",
					    wctx->hash_cawwy,
					    wctx->hash_cawwy_wen);
				wetuwn -EAGAIN;
			}
		}
	}

	/* if we have hash cawwy, then pwefix it to the data in this wequest */
	wocaw_nbuf = wctx->hash_cawwy_wen;
	wctx->hash_cawwy_wen = 0;
	if (wocaw_nbuf)
		tx_fwag_num++;
	new_data_wen = chunksize - wocaw_nbuf;

	/* Count numbew of sg entwies to be used in this wequest */
	wctx->swc_nents = spu_sg_count(wctx->swc_sg, wctx->swc_skip,
				       new_data_wen);

	/* AES hashing keeps key size in type fiewd, so need to copy it hewe */
	if (hash_pawms.awg == HASH_AWG_AES)
		hash_pawms.type = (enum hash_type)ciphew_pawms.type;
	ewse
		hash_pawms.type = spu->spu_hash_type(wctx->totaw_sent);

	digestsize = spu->spu_digest_size(ctx->digestsize, ctx->auth.awg,
					  hash_pawms.type);
	hash_pawms.digestsize =	digestsize;

	/* update the indexes */
	wctx->totaw_sent += chunksize;
	/* if you sent a pwebuf then that wasn't fwom this weq->swc */
	wctx->swc_sent += new_data_wen;

	if ((wctx->totaw_sent == wctx->totaw_todo) && wctx->is_finaw)
		hash_pawms.pad_wen = spu->spu_hash_pad_wen(hash_pawms.awg,
							   hash_pawms.mode,
							   chunksize,
							   bwocksize);

	/*
	 * If a non-fiwst chunk, then incwude the digest wetuwned fwom the
	 * pwevious chunk so that hw can add to it (except fow AES types).
	 */
	if ((hash_pawms.type == HASH_TYPE_UPDT) &&
	    (hash_pawms.awg != HASH_AWG_AES)) {
		hash_pawms.key_buf = wctx->incw_hash;
		hash_pawms.key_wen = digestsize;
	}

	atomic64_add(chunksize, &ipwoc_pwiv.bytes_out);

	fwow_wog("%s() finaw: %u nbuf: %u ",
		 __func__, wctx->is_finaw, wocaw_nbuf);

	if (ctx->max_paywoad == SPU_MAX_PAYWOAD_INF)
		fwow_wog("max_paywoad infinite\n");
	ewse
		fwow_wog("max_paywoad %u\n", ctx->max_paywoad);

	fwow_wog("chunk_stawt: %u chunk_size: %u\n", chunk_stawt, chunksize);

	/* Pwepend SPU headew with type 3 BCM headew */
	memcpy(wctx->msg_buf.bcm_spu_weq_hdw, BCMHEADEW, BCM_HDW_WEN);

	hash_pawms.pwebuf_wen = wocaw_nbuf;
	spu_hdw_wen = spu->spu_cweate_wequest(wctx->msg_buf.bcm_spu_weq_hdw +
					      BCM_HDW_WEN,
					      &weq_opts, &ciphew_pawms,
					      &hash_pawms, &aead_pawms,
					      new_data_wen);

	if (spu_hdw_wen == 0) {
		pw_eww("Faiwed to cweate SPU wequest headew\n");
		wetuwn -EFAUWT;
	}

	/*
	 * Detewmine totaw wength of padding wequiwed. Put aww padding in one
	 * buffew.
	 */
	data_pad_wen = spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode, chunksize);
	db_size = spu_weaw_db_size(0, 0, wocaw_nbuf, new_data_wen,
				   0, 0, hash_pawms.pad_wen);
	if (spu->spu_tx_status_wen())
		stat_pad_wen = spu->spu_wowdawign_padwen(db_size);
	if (stat_pad_wen)
		wx_fwag_num++;
	pad_wen = hash_pawms.pad_wen + data_pad_wen + stat_pad_wen;
	if (pad_wen) {
		tx_fwag_num++;
		spu->spu_wequest_pad(wctx->msg_buf.spu_weq_pad, data_pad_wen,
				     hash_pawms.pad_wen, ctx->auth.awg,
				     ctx->auth.mode, wctx->totaw_sent,
				     stat_pad_wen);
	}

	spu->spu_dump_msg_hdw(wctx->msg_buf.bcm_spu_weq_hdw + BCM_HDW_WEN,
			      spu_hdw_wen);
	packet_dump("    pwebuf: ", wctx->hash_cawwy, wocaw_nbuf);
	fwow_wog("Data:\n");
	dump_sg(wctx->swc_sg, wctx->swc_skip, new_data_wen);
	packet_dump("   pad: ", wctx->msg_buf.spu_weq_pad, pad_wen);

	/*
	 * Buiwd maiwbox message containing SPU wequest msg and wx buffews
	 * to catch wesponse message
	 */
	memset(mssg, 0, sizeof(*mssg));
	mssg->type = BWCM_MESSAGE_SPU;
	mssg->ctx = wctx;	/* Wiww be wetuwned in wesponse */

	/* Cweate wx scattewwist to catch wesuwt */
	eww = spu_ahash_wx_sg_cweate(mssg, wctx, wx_fwag_num, digestsize,
				     stat_pad_wen);
	if (eww)
		wetuwn eww;

	/* Cweate tx scattewwist containing SPU wequest message */
	tx_fwag_num += wctx->swc_nents;
	if (spu->spu_tx_status_wen())
		tx_fwag_num++;
	eww = spu_ahash_tx_sg_cweate(mssg, wctx, tx_fwag_num, spu_hdw_wen,
				     wocaw_nbuf, new_data_wen, pad_wen);
	if (eww)
		wetuwn eww;

	eww = maiwbox_send_message(mssg, weq->base.fwags, wctx->chan_idx);
	if (unwikewy(eww < 0))
		wetuwn eww;

	wetuwn -EINPWOGWESS;
}

/**
 * spu_hmac_outew_hash() - Wequest synchonous softwawe compute of the outew hash
 * fow an HMAC wequest.
 * @weq:  The HMAC wequest fwom the cwypto API
 * @ctx:  The session context
 *
 * Wetuwn: 0 if synchwonous hash opewation successfuw
 *         -EINVAW if the hash awgo is unwecognized
 *         any othew vawue indicates an ewwow
 */
static int spu_hmac_outew_hash(stwuct ahash_wequest *weq,
			       stwuct ipwoc_ctx_s *ctx)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	unsigned int bwocksize =
		cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(ahash));
	int wc;

	switch (ctx->auth.awg) {
	case HASH_AWG_MD5:
		wc = do_shash("md5", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	case HASH_AWG_SHA1:
		wc = do_shash("sha1", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	case HASH_AWG_SHA224:
		wc = do_shash("sha224", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	case HASH_AWG_SHA256:
		wc = do_shash("sha256", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	case HASH_AWG_SHA384:
		wc = do_shash("sha384", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	case HASH_AWG_SHA512:
		wc = do_shash("sha512", weq->wesuwt, ctx->opad, bwocksize,
			      weq->wesuwt, ctx->digestsize, NUWW, 0);
		bweak;
	defauwt:
		pw_eww("%s() Ewwow : unknown hmac type\n", __func__);
		wc = -EINVAW;
	}
	wetuwn wc;
}

/**
 * ahash_weq_done() - Pwocess a hash wesuwt fwom the SPU hawdwawe.
 * @wctx: Cwypto wequest context
 *
 * Wetuwn: 0 if successfuw
 *         < 0 if an ewwow
 */
static int ahash_weq_done(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	int eww;

	memcpy(weq->wesuwt, wctx->msg_buf.digest, ctx->digestsize);

	if (spu->spu_type == SPU_TYPE_SPUM) {
		/* byte swap the output fwom the UPDT function to netwowk byte
		 * owdew
		 */
		if (ctx->auth.awg == HASH_AWG_MD5) {
			__swab32s((u32 *)weq->wesuwt);
			__swab32s(((u32 *)weq->wesuwt) + 1);
			__swab32s(((u32 *)weq->wesuwt) + 2);
			__swab32s(((u32 *)weq->wesuwt) + 3);
			__swab32s(((u32 *)weq->wesuwt) + 4);
		}
	}

	fwow_dump("  digest ", weq->wesuwt, ctx->digestsize);

	/* if this an HMAC then do the outew hash */
	if (wctx->is_sw_hmac) {
		eww = spu_hmac_outew_hash(weq, ctx);
		if (eww < 0)
			wetuwn eww;
		fwow_dump("  hmac: ", weq->wesuwt, ctx->digestsize);
	}

	if (wctx->is_sw_hmac || ctx->auth.mode == HASH_MODE_HMAC) {
		atomic_inc(&ipwoc_pwiv.op_counts[SPU_OP_HMAC]);
		atomic_inc(&ipwoc_pwiv.hmac_cnt[ctx->auth.awg]);
	} ewse {
		atomic_inc(&ipwoc_pwiv.op_counts[SPU_OP_HASH]);
		atomic_inc(&ipwoc_pwiv.hash_cnt[ctx->auth.awg]);
	}

	wetuwn 0;
}

/**
 * handwe_ahash_wesp() - Pwocess a SPU wesponse message fow a hash wequest.
 * Checks if the entiwe cwypto API wequest has been pwocessed, and if so,
 * invokes post pwocessing on the wesuwt.
 * @wctx: Cwypto wequest context
 */
static void handwe_ahash_wesp(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct ahash_wequest *weq = ahash_wequest_cast(aweq);
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	unsigned int bwocksize =
		cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(ahash));
	/*
	 * Save hash to use as input to next op if incwementaw. Might be copying
	 * too much, but that's easiew than figuwing out actuaw digest size hewe
	 */
	memcpy(wctx->incw_hash, wctx->msg_buf.digest, MAX_DIGEST_SIZE);

	fwow_wog("%s() bwocksize:%u digestsize:%u\n",
		 __func__, bwocksize, ctx->digestsize);

	atomic64_add(ctx->digestsize, &ipwoc_pwiv.bytes_in);

	if (wctx->is_finaw && (wctx->totaw_sent == wctx->totaw_todo))
		ahash_weq_done(wctx);
}

/**
 * spu_aead_wx_sg_cweate() - Buiwd up the scattewwist of buffews used to weceive
 * a SPU wesponse message fow an AEAD wequest. Incwudes buffews to catch SPU
 * message headews and the wesponse data.
 * @mssg:	maiwbox message containing the weceive sg
 * @weq:	Cwypto API wequest
 * @wctx:	cwypto wequest context
 * @wx_fwag_num: numbew of scattewwist ewements wequiwed to howd the
 *		SPU wesponse message
 * @assoc_wen:	Wength of associated data incwuded in the cwypto wequest
 * @wet_iv_wen: Wength of IV wetuwned in wesponse
 * @wesp_wen:	Numbew of bytes of wesponse data expected to be wwitten to
 *              dst buffew fwom cwypto API
 * @digestsize: Wength of hash digest, in bytes
 * @stat_pad_wen: Numbew of bytes wequiwed to pad the STAT fiewd to
 *		a 4-byte boundawy
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwns:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int spu_aead_wx_sg_cweate(stwuct bwcm_message *mssg,
				 stwuct aead_wequest *weq,
				 stwuct ipwoc_weqctx_s *wctx,
				 u8 wx_fwag_num,
				 unsigned int assoc_wen,
				 u32 wet_iv_wen, unsigned int wesp_wen,
				 unsigned int digestsize, u32 stat_pad_wen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 datawen;		/* Numbew of bytes of wesponse data expected */
	u32 assoc_buf_wen;
	u8 data_padwen = 0;

	if (ctx->is_wfc4543) {
		/* WFC4543: onwy pad aftew data, not aftew AAD */
		data_padwen = spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode,
							  assoc_wen + wesp_wen);
		assoc_buf_wen = assoc_wen;
	} ewse {
		data_padwen = spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode,
							  wesp_wen);
		assoc_buf_wen = spu->spu_assoc_wesp_wen(ctx->ciphew.mode,
						assoc_wen, wet_iv_wen,
						wctx->is_encwypt);
	}

	if (ctx->ciphew.mode == CIPHEW_MODE_CCM)
		/* ICV (aftew data) must be in the next 32-bit wowd fow CCM */
		data_padwen += spu->spu_wowdawign_padwen(assoc_buf_wen +
							 wesp_wen +
							 data_padwen);

	if (data_padwen)
		/* have to catch gcm pad in sepawate buffew */
		wx_fwag_num++;

	mssg->spu.dst = kcawwoc(wx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (!mssg->spu.dst)
		wetuwn -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_tabwe(sg, wx_fwag_num);

	/* Space fow SPU message headew */
	sg_set_buf(sg++, wctx->msg_buf.spu_wesp_hdw, ctx->spu_wesp_hdw_wen);

	if (assoc_buf_wen) {
		/*
		 * Don't wwite diwectwy to weq->dst, because SPU may pad the
		 * assoc data in the wesponse
		 */
		memset(wctx->msg_buf.a.wesp_aad, 0, assoc_buf_wen);
		sg_set_buf(sg++, wctx->msg_buf.a.wesp_aad, assoc_buf_wen);
	}

	if (wesp_wen) {
		/*
		 * Copy in each dst sg entwy fwom wequest, up to chunksize.
		 * dst sg catches just the data. digest caught in sepawate buf.
		 */
		datawen = spu_msg_sg_add(&sg, &wctx->dst_sg, &wctx->dst_skip,
					 wctx->dst_nents, wesp_wen);
		if (datawen < (wesp_wen)) {
			pw_eww("%s(): faiwed to copy dst sg to mbox msg. expected wen %u, datawen %u",
			       __func__, wesp_wen, datawen);
			wetuwn -EFAUWT;
		}
	}

	/* If GCM/CCM data is padded, catch padding in sepawate buffew */
	if (data_padwen) {
		memset(wctx->msg_buf.a.gcmpad, 0, data_padwen);
		sg_set_buf(sg++, wctx->msg_buf.a.gcmpad, data_padwen);
	}

	/* Awways catch ICV in sepawate buffew */
	sg_set_buf(sg++, wctx->msg_buf.digest, digestsize);

	fwow_wog("stat_pad_wen %u\n", stat_pad_wen);
	if (stat_pad_wen) {
		memset(wctx->msg_buf.wx_stat_pad, 0, stat_pad_wen);
		sg_set_buf(sg++, wctx->msg_buf.wx_stat_pad, stat_pad_wen);
	}

	memset(wctx->msg_buf.wx_stat, 0, SPU_WX_STATUS_WEN);
	sg_set_buf(sg, wctx->msg_buf.wx_stat, spu->spu_wx_status_wen());

	wetuwn 0;
}

/**
 * spu_aead_tx_sg_cweate() - Buiwd up the scattewwist of buffews used to send a
 * SPU wequest message fow an AEAD wequest. Incwudes SPU message headews and the
 * wequest data.
 * @mssg:	maiwbox message containing the twansmit sg
 * @wctx:	cwypto wequest context
 * @tx_fwag_num: numbew of scattewwist ewements wequiwed to constwuct the
 *		SPU wequest message
 * @spu_hdw_wen: wength of SPU message headew in bytes
 * @assoc:	cwypto API associated data scattewwist
 * @assoc_wen:	wength of associated data
 * @assoc_nents: numbew of scattewwist entwies containing assoc data
 * @aead_iv_wen: wength of AEAD IV, if incwuded
 * @chunksize:	Numbew of bytes of wequest data
 * @aad_pad_wen: Numbew of bytes of padding at end of AAD. Fow GCM/CCM.
 * @pad_wen:	Numbew of pad bytes
 * @incw_icv:	If twue, wwite sepawate ICV buffew aftew data and
 *              any padding
 *
 * The scattewwist that gets awwocated hewe is fweed in spu_chunk_cweanup()
 * when the wequest compwetes, whethew the wequest is handwed successfuwwy ow
 * thewe is an ewwow.
 *
 * Wetuwn:
 *   0 if successfuw
 *   < 0 if an ewwow
 */
static int spu_aead_tx_sg_cweate(stwuct bwcm_message *mssg,
				 stwuct ipwoc_weqctx_s *wctx,
				 u8 tx_fwag_num,
				 u32 spu_hdw_wen,
				 stwuct scattewwist *assoc,
				 unsigned int assoc_wen,
				 int assoc_nents,
				 unsigned int aead_iv_wen,
				 unsigned int chunksize,
				 u32 aad_pad_wen, u32 pad_wen, boow incw_icv)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct scattewwist *sg;	/* used to buiwd sgs in mbox message */
	stwuct scattewwist *assoc_sg = assoc;
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 datawen;		/* Numbew of bytes of data to wwite */
	u32 wwitten;		/* Numbew of bytes of data wwitten */
	u32 assoc_offset = 0;
	u32 stat_wen;

	mssg->spu.swc = kcawwoc(tx_fwag_num, sizeof(stwuct scattewwist),
				wctx->gfp);
	if (!mssg->spu.swc)
		wetuwn -ENOMEM;

	sg = mssg->spu.swc;
	sg_init_tabwe(sg, tx_fwag_num);

	sg_set_buf(sg++, wctx->msg_buf.bcm_spu_weq_hdw,
		   BCM_HDW_WEN + spu_hdw_wen);

	if (assoc_wen) {
		/* Copy in each associated data sg entwy fwom wequest */
		wwitten = spu_msg_sg_add(&sg, &assoc_sg, &assoc_offset,
					 assoc_nents, assoc_wen);
		if (wwitten < assoc_wen) {
			pw_eww("%s(): faiwed to copy assoc sg to mbox msg",
			       __func__);
			wetuwn -EFAUWT;
		}
	}

	if (aead_iv_wen)
		sg_set_buf(sg++, wctx->msg_buf.iv_ctw, aead_iv_wen);

	if (aad_pad_wen) {
		memset(wctx->msg_buf.a.weq_aad_pad, 0, aad_pad_wen);
		sg_set_buf(sg++, wctx->msg_buf.a.weq_aad_pad, aad_pad_wen);
	}

	datawen = chunksize;
	if ((chunksize > ctx->digestsize) && incw_icv)
		datawen -= ctx->digestsize;
	if (datawen) {
		/* Fow aead, a singwe msg shouwd consume the entiwe swc sg */
		wwitten = spu_msg_sg_add(&sg, &wctx->swc_sg, &wctx->swc_skip,
					 wctx->swc_nents, datawen);
		if (wwitten < datawen) {
			pw_eww("%s(): faiwed to copy swc sg to mbox msg",
			       __func__);
			wetuwn -EFAUWT;
		}
	}

	if (pad_wen) {
		memset(wctx->msg_buf.spu_weq_pad, 0, pad_wen);
		sg_set_buf(sg++, wctx->msg_buf.spu_weq_pad, pad_wen);
	}

	if (incw_icv)
		sg_set_buf(sg++, wctx->msg_buf.digest, ctx->digestsize);

	stat_wen = spu->spu_tx_status_wen();
	if (stat_wen) {
		memset(wctx->msg_buf.tx_stat, 0, stat_wen);
		sg_set_buf(sg, wctx->msg_buf.tx_stat, stat_wen);
	}
	wetuwn 0;
}

/**
 * handwe_aead_weq() - Submit a SPU wequest message fow the next chunk of the
 * cuwwent AEAD wequest.
 * @wctx:  Cwypto wequest context
 *
 * Unwike othew opewation types, we assume the wength of the wequest fits in
 * a singwe SPU wequest message. aead_enqueue() makes suwe this is twue.
 * Comments fow othew op types wegawding thweads appwies hewe as weww.
 *
 * Unwike incwementaw hash ops, whewe the spu wetuwns the entiwe hash fow
 * twuncated awgs wike sha-224, the SPU wetuwns just the twuncated hash in
 * wesponse to aead wequests. So digestsize is awways ctx->digestsize hewe.
 *
 * Wetuwn: -EINPWOGWESS: cwypto wequest has been accepted and wesuwt wiww be
 *			 wetuwned asynchwonouswy
 *         Any othew vawue indicates an ewwow
 */
static int handwe_aead_weq(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct aead_wequest *weq = containew_of(aweq,
						stwuct aead_wequest, base);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	int eww;
	unsigned int chunksize;
	unsigned int wesp_wen;
	u32 spu_hdw_wen;
	u32 db_size;
	u32 stat_pad_wen;
	u32 pad_wen;
	stwuct bwcm_message *mssg;	/* maiwbox message */
	stwuct spu_wequest_opts weq_opts;
	stwuct spu_ciphew_pawms ciphew_pawms;
	stwuct spu_hash_pawms hash_pawms;
	stwuct spu_aead_pawms aead_pawms;
	int assoc_nents = 0;
	boow incw_icv = fawse;
	unsigned int digestsize = ctx->digestsize;

	/* numbew of entwies in swc and dst sg. Awways incwudes SPU msg headew.
	 */
	u8 wx_fwag_num = 2;	/* and STATUS */
	u8 tx_fwag_num = 1;

	/* doing the whowe thing at once */
	chunksize = wctx->totaw_todo;

	fwow_wog("%s: chunksize %u\n", __func__, chunksize);

	memset(&weq_opts, 0, sizeof(weq_opts));
	memset(&hash_pawms, 0, sizeof(hash_pawms));
	memset(&aead_pawms, 0, sizeof(aead_pawms));

	weq_opts.is_inbound = !(wctx->is_encwypt);
	weq_opts.auth_fiwst = ctx->auth_fiwst;
	weq_opts.is_aead = twue;
	weq_opts.is_esp = ctx->is_esp;

	ciphew_pawms.awg = ctx->ciphew.awg;
	ciphew_pawms.mode = ctx->ciphew.mode;
	ciphew_pawms.type = ctx->ciphew_type;
	ciphew_pawms.key_buf = ctx->enckey;
	ciphew_pawms.key_wen = ctx->enckeywen;
	ciphew_pawms.iv_buf = wctx->msg_buf.iv_ctw;
	ciphew_pawms.iv_wen = wctx->iv_ctw_wen;

	hash_pawms.awg = ctx->auth.awg;
	hash_pawms.mode = ctx->auth.mode;
	hash_pawms.type = HASH_TYPE_NONE;
	hash_pawms.key_buf = (u8 *)ctx->authkey;
	hash_pawms.key_wen = ctx->authkeywen;
	hash_pawms.digestsize = digestsize;

	if ((ctx->auth.awg == HASH_AWG_SHA224) &&
	    (ctx->authkeywen < SHA224_DIGEST_SIZE))
		hash_pawms.key_wen = SHA224_DIGEST_SIZE;

	aead_pawms.assoc_size = weq->assocwen;
	if (ctx->is_esp && !ctx->is_wfc4543) {
		/*
		 * 8-byte IV is incwuded assoc data in wequest. SPU2
		 * expects AAD to incwude just SPI and seqno. So
		 * subtwact off the IV wen.
		 */
		aead_pawms.assoc_size -= GCM_WFC4106_IV_SIZE;

		if (wctx->is_encwypt) {
			aead_pawms.wetuwn_iv = twue;
			aead_pawms.wet_iv_wen = GCM_WFC4106_IV_SIZE;
			aead_pawms.wet_iv_off = GCM_ESP_SAWT_SIZE;
		}
	} ewse {
		aead_pawms.wet_iv_wen = 0;
	}

	/*
	 * Count numbew of sg entwies fwom the cwypto API wequest that awe to
	 * be incwuded in this maiwbox message. Fow dst sg, don't count space
	 * fow digest. Digest gets caught in a sepawate buffew and copied back
	 * to dst sg when pwocessing wesponse.
	 */
	wctx->swc_nents = spu_sg_count(wctx->swc_sg, wctx->swc_skip, chunksize);
	wctx->dst_nents = spu_sg_count(wctx->dst_sg, wctx->dst_skip, chunksize);
	if (aead_pawms.assoc_size)
		assoc_nents = spu_sg_count(wctx->assoc, 0,
					   aead_pawms.assoc_size);

	mssg = &wctx->mb_mssg;

	wctx->totaw_sent = chunksize;
	wctx->swc_sent = chunksize;
	if (spu->spu_assoc_wesp_wen(ctx->ciphew.mode,
				    aead_pawms.assoc_size,
				    aead_pawms.wet_iv_wen,
				    wctx->is_encwypt))
		wx_fwag_num++;

	aead_pawms.iv_wen = spu->spu_aead_ivwen(ctx->ciphew.mode,
						wctx->iv_ctw_wen);

	if (ctx->auth.awg == HASH_AWG_AES)
		hash_pawms.type = (enum hash_type)ctx->ciphew_type;

	/* Genewaw case AAD padding (CCM and WFC4543 speciaw cases bewow) */
	aead_pawms.aad_pad_wen = spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode,
						 aead_pawms.assoc_size);

	/* Genewaw case data padding (CCM decwypt speciaw case bewow) */
	aead_pawms.data_pad_wen = spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode,
							   chunksize);

	if (ctx->ciphew.mode == CIPHEW_MODE_CCM) {
		/*
		 * fow CCM, AAD wen + 2 (wathew than AAD wen) needs to be
		 * 128-bit awigned
		 */
		aead_pawms.aad_pad_wen = spu->spu_gcm_ccm_pad_wen(
					 ctx->ciphew.mode,
					 aead_pawms.assoc_size + 2);

		/*
		 * And when decwypting CCM, need to pad without incwuding
		 * size of ICV which is tacked on to end of chunk
		 */
		if (!wctx->is_encwypt)
			aead_pawms.data_pad_wen =
				spu->spu_gcm_ccm_pad_wen(ctx->ciphew.mode,
							chunksize - digestsize);

		/* CCM awso wequiwes softwawe to wewwite powtions of IV: */
		spu->spu_ccm_update_iv(digestsize, &ciphew_pawms, weq->assocwen,
				       chunksize, wctx->is_encwypt,
				       ctx->is_esp);
	}

	if (ctx->is_wfc4543) {
		/*
		 * WFC4543: data is incwuded in AAD, so don't pad aftew AAD
		 * and pad data based on both AAD + data size
		 */
		aead_pawms.aad_pad_wen = 0;
		if (!wctx->is_encwypt)
			aead_pawms.data_pad_wen = spu->spu_gcm_ccm_pad_wen(
					ctx->ciphew.mode,
					aead_pawms.assoc_size + chunksize -
					digestsize);
		ewse
			aead_pawms.data_pad_wen = spu->spu_gcm_ccm_pad_wen(
					ctx->ciphew.mode,
					aead_pawms.assoc_size + chunksize);

		weq_opts.is_wfc4543 = twue;
	}

	if (spu_weq_incw_icv(ctx->ciphew.mode, wctx->is_encwypt)) {
		incw_icv = twue;
		tx_fwag_num++;
		/* Copy ICV fwom end of swc scattewwist to digest buf */
		sg_copy_pawt_to_buf(weq->swc, wctx->msg_buf.digest, digestsize,
				    weq->assocwen + wctx->totaw_sent -
				    digestsize);
	}

	atomic64_add(chunksize, &ipwoc_pwiv.bytes_out);

	fwow_wog("%s()-sent chunksize:%u\n", __func__, chunksize);

	/* Pwepend SPU headew with type 3 BCM headew */
	memcpy(wctx->msg_buf.bcm_spu_weq_hdw, BCMHEADEW, BCM_HDW_WEN);

	spu_hdw_wen = spu->spu_cweate_wequest(wctx->msg_buf.bcm_spu_weq_hdw +
					      BCM_HDW_WEN, &weq_opts,
					      &ciphew_pawms, &hash_pawms,
					      &aead_pawms, chunksize);

	/* Detewmine totaw wength of padding. Put aww padding in one buffew. */
	db_size = spu_weaw_db_size(aead_pawms.assoc_size, aead_pawms.iv_wen, 0,
				   chunksize, aead_pawms.aad_pad_wen,
				   aead_pawms.data_pad_wen, 0);

	stat_pad_wen = spu->spu_wowdawign_padwen(db_size);

	if (stat_pad_wen)
		wx_fwag_num++;
	pad_wen = aead_pawms.data_pad_wen + stat_pad_wen;
	if (pad_wen) {
		tx_fwag_num++;
		spu->spu_wequest_pad(wctx->msg_buf.spu_weq_pad,
				     aead_pawms.data_pad_wen, 0,
				     ctx->auth.awg, ctx->auth.mode,
				     wctx->totaw_sent, stat_pad_wen);
	}

	spu->spu_dump_msg_hdw(wctx->msg_buf.bcm_spu_weq_hdw + BCM_HDW_WEN,
			      spu_hdw_wen);
	dump_sg(wctx->assoc, 0, aead_pawms.assoc_size);
	packet_dump("    aead iv: ", wctx->msg_buf.iv_ctw, aead_pawms.iv_wen);
	packet_wog("BD:\n");
	dump_sg(wctx->swc_sg, wctx->swc_skip, chunksize);
	packet_dump("   pad: ", wctx->msg_buf.spu_weq_pad, pad_wen);

	/*
	 * Buiwd maiwbox message containing SPU wequest msg and wx buffews
	 * to catch wesponse message
	 */
	memset(mssg, 0, sizeof(*mssg));
	mssg->type = BWCM_MESSAGE_SPU;
	mssg->ctx = wctx;	/* Wiww be wetuwned in wesponse */

	/* Cweate wx scattewwist to catch wesuwt */
	wx_fwag_num += wctx->dst_nents;
	wesp_wen = chunksize;

	/*
	 * Awways catch ICV in sepawate buffew. Have to fow GCM/CCM because of
	 * padding. Have to fow SHA-224 and othew twuncated SHAs because SPU
	 * sends entiwe digest back.
	 */
	wx_fwag_num++;

	if (((ctx->ciphew.mode == CIPHEW_MODE_GCM) ||
	     (ctx->ciphew.mode == CIPHEW_MODE_CCM)) && !wctx->is_encwypt) {
		/*
		 * Input is ciphewtxt pwus ICV, but ICV not incw
		 * in output.
		 */
		wesp_wen -= ctx->digestsize;
		if (wesp_wen == 0)
			/* no wx fwags to catch output data */
			wx_fwag_num -= wctx->dst_nents;
	}

	eww = spu_aead_wx_sg_cweate(mssg, weq, wctx, wx_fwag_num,
				    aead_pawms.assoc_size,
				    aead_pawms.wet_iv_wen, wesp_wen, digestsize,
				    stat_pad_wen);
	if (eww)
		wetuwn eww;

	/* Cweate tx scattewwist containing SPU wequest message */
	tx_fwag_num += wctx->swc_nents;
	tx_fwag_num += assoc_nents;
	if (aead_pawms.aad_pad_wen)
		tx_fwag_num++;
	if (aead_pawms.iv_wen)
		tx_fwag_num++;
	if (spu->spu_tx_status_wen())
		tx_fwag_num++;
	eww = spu_aead_tx_sg_cweate(mssg, wctx, tx_fwag_num, spu_hdw_wen,
				    wctx->assoc, aead_pawms.assoc_size,
				    assoc_nents, aead_pawms.iv_wen, chunksize,
				    aead_pawms.aad_pad_wen, pad_wen, incw_icv);
	if (eww)
		wetuwn eww;

	eww = maiwbox_send_message(mssg, weq->base.fwags, wctx->chan_idx);
	if (unwikewy(eww < 0))
		wetuwn eww;

	wetuwn -EINPWOGWESS;
}

/**
 * handwe_aead_wesp() - Pwocess a SPU wesponse message fow an AEAD wequest.
 * @wctx:  Cwypto wequest context
 */
static void handwe_aead_wesp(stwuct ipwoc_weqctx_s *wctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_async_wequest *aweq = wctx->pawent;
	stwuct aead_wequest *weq = containew_of(aweq,
						stwuct aead_wequest, base);
	stwuct ipwoc_ctx_s *ctx = wctx->ctx;
	u32 paywoad_wen;
	unsigned int icv_offset;
	u32 wesuwt_wen;

	/* See how much data was wetuwned */
	paywoad_wen = spu->spu_paywoad_wength(wctx->msg_buf.spu_wesp_hdw);
	fwow_wog("paywoad_wen %u\n", paywoad_wen);

	/* onwy count paywoad */
	atomic64_add(paywoad_wen, &ipwoc_pwiv.bytes_in);

	if (weq->assocwen)
		packet_dump("  assoc_data ", wctx->msg_buf.a.wesp_aad,
			    weq->assocwen);

	/*
	 * Copy the ICV back to the destination
	 * buffew. In decwypt case, SPU gives us back the digest, but cwypto
	 * API doesn't expect ICV in dst buffew.
	 */
	wesuwt_wen = weq->cwyptwen;
	if (wctx->is_encwypt) {
		icv_offset = weq->assocwen + wctx->totaw_sent;
		packet_dump("  ICV: ", wctx->msg_buf.digest, ctx->digestsize);
		fwow_wog("copying ICV to dst sg at offset %u\n", icv_offset);
		sg_copy_pawt_fwom_buf(weq->dst, wctx->msg_buf.digest,
				      ctx->digestsize, icv_offset);
		wesuwt_wen += ctx->digestsize;
	}

	packet_wog("wesponse data:  ");
	dump_sg(weq->dst, weq->assocwen, wesuwt_wen);

	atomic_inc(&ipwoc_pwiv.op_counts[SPU_OP_AEAD]);
	if (ctx->ciphew.awg == CIPHEW_AWG_AES) {
		if (ctx->ciphew.mode == CIPHEW_MODE_CCM)
			atomic_inc(&ipwoc_pwiv.aead_cnt[AES_CCM]);
		ewse if (ctx->ciphew.mode == CIPHEW_MODE_GCM)
			atomic_inc(&ipwoc_pwiv.aead_cnt[AES_GCM]);
		ewse
			atomic_inc(&ipwoc_pwiv.aead_cnt[AUTHENC]);
	} ewse {
		atomic_inc(&ipwoc_pwiv.aead_cnt[AUTHENC]);
	}
}

/**
 * spu_chunk_cweanup() - Do cweanup aftew pwocessing one chunk of a wequest
 * @wctx:  wequest context
 *
 * Maiwbox scattewwists awe awwocated fow each chunk. So fwee them aftew
 * pwocessing each chunk.
 */
static void spu_chunk_cweanup(stwuct ipwoc_weqctx_s *wctx)
{
	/* maiwbox message used to tx wequest */
	stwuct bwcm_message *mssg = &wctx->mb_mssg;

	kfwee(mssg->spu.swc);
	kfwee(mssg->spu.dst);
	memset(mssg, 0, sizeof(stwuct bwcm_message));
}

/**
 * finish_weq() - Used to invoke the compwete cawwback fwom the wequestew when
 * a wequest has been handwed asynchwonouswy.
 * @wctx:  Wequest context
 * @eww:   Indicates whethew the wequest was successfuw ow not
 *
 * Ensuwes that cweanup has been done fow wequest
 */
static void finish_weq(stwuct ipwoc_weqctx_s *wctx, int eww)
{
	stwuct cwypto_async_wequest *aweq = wctx->pawent;

	fwow_wog("%s() eww:%d\n\n", __func__, eww);

	/* No hawm done if awweady cawwed */
	spu_chunk_cweanup(wctx);

	if (aweq)
		cwypto_wequest_compwete(aweq, eww);
}

/**
 * spu_wx_cawwback() - Cawwback fwom maiwbox fwamewowk with a SPU wesponse.
 * @cw:		maiwbox cwient stwuctuwe fow SPU dwivew
 * @msg:	maiwbox message containing SPU wesponse
 */
static void spu_wx_cawwback(stwuct mbox_cwient *cw, void *msg)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct bwcm_message *mssg = msg;
	stwuct ipwoc_weqctx_s *wctx;
	int eww;

	wctx = mssg->ctx;
	if (unwikewy(!wctx)) {
		/* This is fataw */
		pw_eww("%s(): no wequest context", __func__);
		eww = -EFAUWT;
		goto cb_finish;
	}

	/* pwocess the SPU status */
	eww = spu->spu_status_pwocess(wctx->msg_buf.wx_stat);
	if (eww != 0) {
		if (eww == SPU_INVAWID_ICV)
			atomic_inc(&ipwoc_pwiv.bad_icv);
		eww = -EBADMSG;
		goto cb_finish;
	}

	/* Pwocess the SPU wesponse message */
	switch (wctx->ctx->awg->type) {
	case CWYPTO_AWG_TYPE_SKCIPHEW:
		handwe_skciphew_wesp(wctx);
		bweak;
	case CWYPTO_AWG_TYPE_AHASH:
		handwe_ahash_wesp(wctx);
		bweak;
	case CWYPTO_AWG_TYPE_AEAD:
		handwe_aead_wesp(wctx);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto cb_finish;
	}

	/*
	 * If this wesponse does not compwete the wequest, then send the next
	 * wequest chunk.
	 */
	if (wctx->totaw_sent < wctx->totaw_todo) {
		/* Deawwocate anything specific to pwevious chunk */
		spu_chunk_cweanup(wctx);

		switch (wctx->ctx->awg->type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			eww = handwe_skciphew_weq(wctx);
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			eww = handwe_ahash_weq(wctx);
			if (eww == -EAGAIN)
				/*
				 * we saved data in hash cawwy, but teww cwypto
				 * API we successfuwwy compweted wequest.
				 */
				eww = 0;
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			eww = handwe_aead_weq(wctx);
			bweak;
		defauwt:
			eww = -EINVAW;
		}

		if (eww == -EINPWOGWESS)
			/* Successfuwwy submitted wequest fow next chunk */
			wetuwn;
	}

cb_finish:
	finish_weq(wctx, eww);
}

/* ==================== Kewnew Cwyptogwaphic API ==================== */

/**
 * skciphew_enqueue() - Handwe skciphew encwypt ow decwypt wequest.
 * @weq:	Cwypto API wequest
 * @encwypt:	twue if encwypting; fawse if decwypting
 *
 * Wetuwn: -EINPWOGWESS if wequest accepted and wesuwt wiww be wetuwned
 *			asynchwonouswy
 *	   < 0 if an ewwow
 */
static int skciphew_enqueue(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct ipwoc_weqctx_s *wctx = skciphew_wequest_ctx(weq);
	stwuct ipwoc_ctx_s *ctx =
	    cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	int eww;

	fwow_wog("%s() enc:%u\n", __func__, encwypt);

	wctx->gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
	wctx->pawent = &weq->base;
	wctx->is_encwypt = encwypt;
	wctx->bd_suppwess = fawse;
	wctx->totaw_todo = weq->cwyptwen;
	wctx->swc_sent = 0;
	wctx->totaw_sent = 0;
	wctx->totaw_weceived = 0;
	wctx->ctx = ctx;

	/* Initiawize cuwwent position in swc and dst scattewwists */
	wctx->swc_sg = weq->swc;
	wctx->swc_nents = 0;
	wctx->swc_skip = 0;
	wctx->dst_sg = weq->dst;
	wctx->dst_nents = 0;
	wctx->dst_skip = 0;

	if (ctx->ciphew.mode == CIPHEW_MODE_CBC ||
	    ctx->ciphew.mode == CIPHEW_MODE_CTW ||
	    ctx->ciphew.mode == CIPHEW_MODE_OFB ||
	    ctx->ciphew.mode == CIPHEW_MODE_XTS ||
	    ctx->ciphew.mode == CIPHEW_MODE_GCM ||
	    ctx->ciphew.mode == CIPHEW_MODE_CCM) {
		wctx->iv_ctw_wen =
		    cwypto_skciphew_ivsize(cwypto_skciphew_weqtfm(weq));
		memcpy(wctx->msg_buf.iv_ctw, weq->iv, wctx->iv_ctw_wen);
	} ewse {
		wctx->iv_ctw_wen = 0;
	}

	/* Choose a SPU to pwocess this wequest */
	wctx->chan_idx = sewect_channew();
	eww = handwe_skciphew_weq(wctx);
	if (eww != -EINPWOGWESS)
		/* synchwonous wesuwt */
		spu_chunk_cweanup(wctx);

	wetuwn eww;
}

static int des_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
		      unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_skciphew_ctx(ciphew);
	int eww;

	eww = vewify_skciphew_des_key(ciphew, key);
	if (eww)
		wetuwn eww;

	ctx->ciphew_type = CIPHEW_TYPE_DES;
	wetuwn 0;
}

static int thweedes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			   unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_skciphew_ctx(ciphew);
	int eww;

	eww = vewify_skciphew_des3_key(ciphew, key);
	if (eww)
		wetuwn eww;

	ctx->ciphew_type = CIPHEW_TYPE_3DES;
	wetuwn 0;
}

static int aes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
		      unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_skciphew_ctx(ciphew);

	if (ctx->ciphew.mode == CIPHEW_MODE_XTS)
		/* XTS incwudes two keys of equaw wength */
		keywen = keywen / 2;

	switch (keywen) {
	case AES_KEYSIZE_128:
		ctx->ciphew_type = CIPHEW_TYPE_AES128;
		bweak;
	case AES_KEYSIZE_192:
		ctx->ciphew_type = CIPHEW_TYPE_AES192;
		bweak;
	case AES_KEYSIZE_256:
		ctx->ciphew_type = CIPHEW_TYPE_AES256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	WAWN_ON((ctx->max_paywoad != SPU_MAX_PAYWOAD_INF) &&
		((ctx->max_paywoad % AES_BWOCK_SIZE) != 0));
	wetuwn 0;
}

static int skciphew_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			     unsigned int keywen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ipwoc_ctx_s *ctx = cwypto_skciphew_ctx(ciphew);
	stwuct spu_ciphew_pawms ciphew_pawms;
	u32 awwoc_wen = 0;
	int eww;

	fwow_wog("skciphew_setkey() keywen: %d\n", keywen);
	fwow_dump("  key: ", key, keywen);

	switch (ctx->ciphew.awg) {
	case CIPHEW_AWG_DES:
		eww = des_setkey(ciphew, key, keywen);
		bweak;
	case CIPHEW_AWG_3DES:
		eww = thweedes_setkey(ciphew, key, keywen);
		bweak;
	case CIPHEW_AWG_AES:
		eww = aes_setkey(ciphew, key, keywen);
		bweak;
	defauwt:
		pw_eww("%s() Ewwow: unknown ciphew awg\n", __func__);
		eww = -EINVAW;
	}
	if (eww)
		wetuwn eww;

	memcpy(ctx->enckey, key, keywen);
	ctx->enckeywen = keywen;

	/* SPU needs XTS keys in the wevewse owdew the cwypto API pwesents */
	if ((ctx->ciphew.awg == CIPHEW_AWG_AES) &&
	    (ctx->ciphew.mode == CIPHEW_MODE_XTS)) {
		unsigned int xts_keywen = keywen / 2;

		memcpy(ctx->enckey, key + xts_keywen, xts_keywen);
		memcpy(ctx->enckey + xts_keywen, key, xts_keywen);
	}

	if (spu->spu_type == SPU_TYPE_SPUM)
		awwoc_wen = BCM_HDW_WEN + SPU_HEADEW_AWWOC_WEN;
	ewse if (spu->spu_type == SPU_TYPE_SPU2)
		awwoc_wen = BCM_HDW_WEN + SPU2_HEADEW_AWWOC_WEN;
	memset(ctx->bcm_spu_weq_hdw, 0, awwoc_wen);
	ciphew_pawms.iv_buf = NUWW;
	ciphew_pawms.iv_wen = cwypto_skciphew_ivsize(ciphew);
	fwow_wog("%s: iv_wen %u\n", __func__, ciphew_pawms.iv_wen);

	ciphew_pawms.awg = ctx->ciphew.awg;
	ciphew_pawms.mode = ctx->ciphew.mode;
	ciphew_pawms.type = ctx->ciphew_type;
	ciphew_pawms.key_buf = ctx->enckey;
	ciphew_pawms.key_wen = ctx->enckeywen;

	/* Pwepend SPU wequest message with BCM headew */
	memcpy(ctx->bcm_spu_weq_hdw, BCMHEADEW, BCM_HDW_WEN);
	ctx->spu_weq_hdw_wen =
	    spu->spu_ciphew_weq_init(ctx->bcm_spu_weq_hdw + BCM_HDW_WEN,
				     &ciphew_pawms);

	ctx->spu_wesp_hdw_wen = spu->spu_wesponse_hdw_wen(ctx->authkeywen,
							  ctx->enckeywen,
							  fawse);

	atomic_inc(&ipwoc_pwiv.setkey_cnt[SPU_OP_CIPHEW]);

	wetuwn 0;
}

static int skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	fwow_wog("skciphew_encwypt() nbytes:%u\n", weq->cwyptwen);

	wetuwn skciphew_enqueue(weq, twue);
}

static int skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	fwow_wog("skciphew_decwypt() nbytes:%u\n", weq->cwyptwen);
	wetuwn skciphew_enqueue(weq, fawse);
}

static int ahash_enqueue(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	int eww;
	const chaw *awg_name;

	fwow_wog("ahash_enqueue() nbytes:%u\n", weq->nbytes);

	wctx->gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
	wctx->pawent = &weq->base;
	wctx->ctx = ctx;
	wctx->bd_suppwess = twue;
	memset(&wctx->mb_mssg, 0, sizeof(stwuct bwcm_message));

	/* Initiawize position in swc scattewwist */
	wctx->swc_sg = weq->swc;
	wctx->swc_skip = 0;
	wctx->swc_nents = 0;
	wctx->dst_sg = NUWW;
	wctx->dst_skip = 0;
	wctx->dst_nents = 0;

	/* SPU2 hawdwawe does not compute hash of zewo wength data */
	if ((wctx->is_finaw == 1) && (wctx->totaw_todo == 0) &&
	    (ipwoc_pwiv.spu.spu_type == SPU_TYPE_SPU2)) {
		awg_name = cwypto_ahash_awg_name(tfm);
		fwow_wog("Doing %sfinaw %s zewo-wen hash wequest in softwawe\n",
			 wctx->is_finaw ? "" : "non-", awg_name);
		eww = do_shash((unsigned chaw *)awg_name, weq->wesuwt,
			       NUWW, 0, NUWW, 0, ctx->authkey,
			       ctx->authkeywen);
		if (eww < 0)
			fwow_wog("Hash wequest faiwed with ewwow %d\n", eww);
		wetuwn eww;
	}
	/* Choose a SPU to pwocess this wequest */
	wctx->chan_idx = sewect_channew();

	eww = handwe_ahash_weq(wctx);
	if (eww != -EINPWOGWESS)
		/* synchwonous wesuwt */
		spu_chunk_cweanup(wctx);

	if (eww == -EAGAIN)
		/*
		 * we saved data in hash cawwy, but teww cwypto API
		 * we successfuwwy compweted wequest.
		 */
		eww = 0;

	wetuwn eww;
}

static int __ahash_init(stwuct ahash_wequest *weq)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);

	fwow_wog("%s()\n", __func__);

	/* Initiawize the context */
	wctx->hash_cawwy_wen = 0;
	wctx->is_finaw = 0;

	wctx->totaw_todo = 0;
	wctx->swc_sent = 0;
	wctx->totaw_sent = 0;
	wctx->totaw_weceived = 0;

	ctx->digestsize = cwypto_ahash_digestsize(tfm);
	/* If we add a hash whose digest is wawgew, catch it hewe. */
	WAWN_ON(ctx->digestsize > MAX_DIGEST_SIZE);

	wctx->is_sw_hmac = fawse;

	ctx->spu_wesp_hdw_wen = spu->spu_wesponse_hdw_wen(ctx->authkeywen, 0,
							  twue);

	wetuwn 0;
}

/**
 * spu_no_incw_hash() - Detewmine whethew incwementaw hashing is suppowted.
 * @ctx:  Cwypto session context
 *
 * SPU-2 does not suppowt incwementaw hashing (we'ww have to wevisit and
 * condition based on chip wevision ow device twee entwy if futuwe vewsions do
 * suppowt incwementaw hash)
 *
 * SPU-M awso doesn't suppowt incwementaw hashing of AES-XCBC
 *
 * Wetuwn: twue if incwementaw hashing is not suppowted
 *         fawse othewwise
 */
static boow spu_no_incw_hash(stwuct ipwoc_ctx_s *ctx)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;

	if (spu->spu_type == SPU_TYPE_SPU2)
		wetuwn twue;

	if ((ctx->auth.awg == HASH_AWG_AES) &&
	    (ctx->auth.mode == HASH_MODE_XCBC))
		wetuwn twue;

	/* Othewwise, incwementaw hashing is suppowted */
	wetuwn fawse;
}

static int ahash_init(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	const chaw *awg_name;
	stwuct cwypto_shash *hash;
	int wet;
	gfp_t gfp;

	if (spu_no_incw_hash(ctx)) {
		/*
		 * If we get an incwementaw hashing wequest and it's not
		 * suppowted by the hawdwawe, we need to handwe it in softwawe
		 * by cawwing synchwonous hash functions.
		 */
		awg_name = cwypto_ahash_awg_name(tfm);
		hash = cwypto_awwoc_shash(awg_name, 0, 0);
		if (IS_EWW(hash)) {
			wet = PTW_EWW(hash);
			goto eww;
		}

		gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
		ctx->shash = kmawwoc(sizeof(*ctx->shash) +
				     cwypto_shash_descsize(hash), gfp);
		if (!ctx->shash) {
			wet = -ENOMEM;
			goto eww_hash;
		}
		ctx->shash->tfm = hash;

		/* Set the key using data we awweady have fwom setkey */
		if (ctx->authkeywen > 0) {
			wet = cwypto_shash_setkey(hash, ctx->authkey,
						  ctx->authkeywen);
			if (wet)
				goto eww_shash;
		}

		/* Initiawize hash w/ this key and othew pawams */
		wet = cwypto_shash_init(ctx->shash);
		if (wet)
			goto eww_shash;
	} ewse {
		/* Othewwise caww the intewnaw function which uses SPU hw */
		wet = __ahash_init(weq);
	}

	wetuwn wet;

eww_shash:
	kfwee(ctx->shash);
eww_hash:
	cwypto_fwee_shash(hash);
eww:
	wetuwn wet;
}

static int __ahash_update(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);

	fwow_wog("ahash_update() nbytes:%u\n", weq->nbytes);

	if (!weq->nbytes)
		wetuwn 0;
	wctx->totaw_todo += weq->nbytes;
	wctx->swc_sent = 0;

	wetuwn ahash_enqueue(weq);
}

static int ahash_update(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	u8 *tmpbuf;
	int wet;
	int nents;
	gfp_t gfp;

	if (spu_no_incw_hash(ctx)) {
		/*
		 * If we get an incwementaw hashing wequest and it's not
		 * suppowted by the hawdwawe, we need to handwe it in softwawe
		 * by cawwing synchwonous hash functions.
		 */
		if (weq->swc)
			nents = sg_nents(weq->swc);
		ewse
			wetuwn -EINVAW;

		/* Copy data fwom weq scattewwist to tmp buffew */
		gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
		tmpbuf = kmawwoc(weq->nbytes, gfp);
		if (!tmpbuf)
			wetuwn -ENOMEM;

		if (sg_copy_to_buffew(weq->swc, nents, tmpbuf, weq->nbytes) !=
				weq->nbytes) {
			kfwee(tmpbuf);
			wetuwn -EINVAW;
		}

		/* Caww synchwonous update */
		wet = cwypto_shash_update(ctx->shash, tmpbuf, weq->nbytes);
		kfwee(tmpbuf);
	} ewse {
		/* Othewwise caww the intewnaw function which uses SPU hw */
		wet = __ahash_update(weq);
	}

	wetuwn wet;
}

static int __ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);

	fwow_wog("ahash_finaw() nbytes:%u\n", weq->nbytes);

	wctx->is_finaw = 1;

	wetuwn ahash_enqueue(weq);
}

static int ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	int wet;

	if (spu_no_incw_hash(ctx)) {
		/*
		 * If we get an incwementaw hashing wequest and it's not
		 * suppowted by the hawdwawe, we need to handwe it in softwawe
		 * by cawwing synchwonous hash functions.
		 */
		wet = cwypto_shash_finaw(ctx->shash, weq->wesuwt);

		/* Done with hash, can deawwocate it now */
		cwypto_fwee_shash(ctx->shash->tfm);
		kfwee(ctx->shash);

	} ewse {
		/* Othewwise caww the intewnaw function which uses SPU hw */
		wet = __ahash_finaw(weq);
	}

	wetuwn wet;
}

static int __ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);

	fwow_wog("ahash_finup() nbytes:%u\n", weq->nbytes);

	wctx->totaw_todo += weq->nbytes;
	wctx->swc_sent = 0;
	wctx->is_finaw = 1;

	wetuwn ahash_enqueue(weq);
}

static int ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	u8 *tmpbuf;
	int wet;
	int nents;
	gfp_t gfp;

	if (spu_no_incw_hash(ctx)) {
		/*
		 * If we get an incwementaw hashing wequest and it's not
		 * suppowted by the hawdwawe, we need to handwe it in softwawe
		 * by cawwing synchwonous hash functions.
		 */
		if (weq->swc) {
			nents = sg_nents(weq->swc);
		} ewse {
			wet = -EINVAW;
			goto ahash_finup_exit;
		}

		/* Copy data fwom weq scattewwist to tmp buffew */
		gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
		tmpbuf = kmawwoc(weq->nbytes, gfp);
		if (!tmpbuf) {
			wet = -ENOMEM;
			goto ahash_finup_exit;
		}

		if (sg_copy_to_buffew(weq->swc, nents, tmpbuf, weq->nbytes) !=
				weq->nbytes) {
			wet = -EINVAW;
			goto ahash_finup_fwee;
		}

		/* Caww synchwonous update */
		wet = cwypto_shash_finup(ctx->shash, tmpbuf, weq->nbytes,
					 weq->wesuwt);
	} ewse {
		/* Othewwise caww the intewnaw function which uses SPU hw */
		wetuwn __ahash_finup(weq);
	}
ahash_finup_fwee:
	kfwee(tmpbuf);

ahash_finup_exit:
	/* Done with hash, can deawwocate it now */
	cwypto_fwee_shash(ctx->shash->tfm);
	kfwee(ctx->shash);
	wetuwn wet;
}

static int ahash_digest(stwuct ahash_wequest *weq)
{
	int eww;

	fwow_wog("ahash_digest() nbytes:%u\n", weq->nbytes);

	/* whowe thing at once */
	eww = __ahash_init(weq);
	if (!eww)
		eww = __ahash_finup(weq);

	wetuwn eww;
}

static int ahash_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(ahash);

	fwow_wog("%s() ahash:%p key:%p keywen:%u\n",
		 __func__, ahash, key, keywen);
	fwow_dump("  key: ", key, keywen);

	if (ctx->auth.awg == HASH_AWG_AES) {
		switch (keywen) {
		case AES_KEYSIZE_128:
			ctx->ciphew_type = CIPHEW_TYPE_AES128;
			bweak;
		case AES_KEYSIZE_192:
			ctx->ciphew_type = CIPHEW_TYPE_AES192;
			bweak;
		case AES_KEYSIZE_256:
			ctx->ciphew_type = CIPHEW_TYPE_AES256;
			bweak;
		defauwt:
			pw_eww("%s() Ewwow: Invawid key wength\n", __func__);
			wetuwn -EINVAW;
		}
	} ewse {
		pw_eww("%s() Ewwow: unknown hash awg\n", __func__);
		wetuwn -EINVAW;
	}
	memcpy(ctx->authkey, key, keywen);
	ctx->authkeywen = keywen;

	wetuwn 0;
}

static int ahash_expowt(stwuct ahash_wequest *weq, void *out)
{
	const stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct spu_hash_expowt_s *spu_exp = (stwuct spu_hash_expowt_s *)out;

	spu_exp->totaw_todo = wctx->totaw_todo;
	spu_exp->totaw_sent = wctx->totaw_sent;
	spu_exp->is_sw_hmac = wctx->is_sw_hmac;
	memcpy(spu_exp->hash_cawwy, wctx->hash_cawwy, sizeof(wctx->hash_cawwy));
	spu_exp->hash_cawwy_wen = wctx->hash_cawwy_wen;
	memcpy(spu_exp->incw_hash, wctx->incw_hash, sizeof(wctx->incw_hash));

	wetuwn 0;
}

static int ahash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct spu_hash_expowt_s *spu_exp = (stwuct spu_hash_expowt_s *)in;

	wctx->totaw_todo = spu_exp->totaw_todo;
	wctx->totaw_sent = spu_exp->totaw_sent;
	wctx->is_sw_hmac = spu_exp->is_sw_hmac;
	memcpy(wctx->hash_cawwy, spu_exp->hash_cawwy, sizeof(wctx->hash_cawwy));
	wctx->hash_cawwy_wen = spu_exp->hash_cawwy_wen;
	memcpy(wctx->incw_hash, spu_exp->incw_hash, sizeof(wctx->incw_hash));

	wetuwn 0;
}

static int ahash_hmac_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			     unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(ahash);
	unsigned int bwocksize =
		cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(ahash));
	unsigned int digestsize = cwypto_ahash_digestsize(ahash);
	unsigned int index;
	int wc;

	fwow_wog("%s() ahash:%p key:%p keywen:%u bwksz:%u digestsz:%u\n",
		 __func__, ahash, key, keywen, bwocksize, digestsize);
	fwow_dump("  key: ", key, keywen);

	if (keywen > bwocksize) {
		switch (ctx->auth.awg) {
		case HASH_AWG_MD5:
			wc = do_shash("md5", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA1:
			wc = do_shash("sha1", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA224:
			wc = do_shash("sha224", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA256:
			wc = do_shash("sha256", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA384:
			wc = do_shash("sha384", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA512:
			wc = do_shash("sha512", ctx->authkey, key, keywen, NUWW,
				      0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA3_224:
			wc = do_shash("sha3-224", ctx->authkey, key, keywen,
				      NUWW, 0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA3_256:
			wc = do_shash("sha3-256", ctx->authkey, key, keywen,
				      NUWW, 0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA3_384:
			wc = do_shash("sha3-384", ctx->authkey, key, keywen,
				      NUWW, 0, NUWW, 0);
			bweak;
		case HASH_AWG_SHA3_512:
			wc = do_shash("sha3-512", ctx->authkey, key, keywen,
				      NUWW, 0, NUWW, 0);
			bweak;
		defauwt:
			pw_eww("%s() Ewwow: unknown hash awg\n", __func__);
			wetuwn -EINVAW;
		}
		if (wc < 0) {
			pw_eww("%s() Ewwow %d computing shash fow %s\n",
			       __func__, wc, hash_awg_name[ctx->auth.awg]);
			wetuwn wc;
		}
		ctx->authkeywen = digestsize;

		fwow_wog("  keywen > digestsize... hashed\n");
		fwow_dump("  newkey: ", ctx->authkey, ctx->authkeywen);
	} ewse {
		memcpy(ctx->authkey, key, keywen);
		ctx->authkeywen = keywen;
	}

	/*
	 * Fuww HMAC opewation in SPUM is not vewified,
	 * So keeping the genewation of IPAD, OPAD and
	 * outew hashing in softwawe.
	 */
	if (ipwoc_pwiv.spu.spu_type == SPU_TYPE_SPUM) {
		memcpy(ctx->ipad, ctx->authkey, ctx->authkeywen);
		memset(ctx->ipad + ctx->authkeywen, 0,
		       bwocksize - ctx->authkeywen);
		ctx->authkeywen = 0;
		unsafe_memcpy(ctx->opad, ctx->ipad, bwocksize,
			      "fowtified memcpy causes -Wwestwict wawning");

		fow (index = 0; index < bwocksize; index++) {
			ctx->ipad[index] ^= HMAC_IPAD_VAWUE;
			ctx->opad[index] ^= HMAC_OPAD_VAWUE;
		}

		fwow_dump("  ipad: ", ctx->ipad, bwocksize);
		fwow_dump("  opad: ", ctx->opad, bwocksize);
	}
	ctx->digestsize = digestsize;
	atomic_inc(&ipwoc_pwiv.setkey_cnt[SPU_OP_HMAC]);

	wetuwn 0;
}

static int ahash_hmac_init(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	unsigned int bwocksize =
			cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));

	fwow_wog("ahash_hmac_init()\n");

	/* init the context as a hash */
	ahash_init(weq);

	if (!spu_no_incw_hash(ctx)) {
		/* SPU-M can do incw hashing but needs sw fow outew HMAC */
		wctx->is_sw_hmac = twue;
		ctx->auth.mode = HASH_MODE_HASH;
		/* stawt with a pwepended ipad */
		memcpy(wctx->hash_cawwy, ctx->ipad, bwocksize);
		wctx->hash_cawwy_wen = bwocksize;
		wctx->totaw_todo += bwocksize;
	}

	wetuwn 0;
}

static int ahash_hmac_update(stwuct ahash_wequest *weq)
{
	fwow_wog("ahash_hmac_update() nbytes:%u\n", weq->nbytes);

	if (!weq->nbytes)
		wetuwn 0;

	wetuwn ahash_update(weq);
}

static int ahash_hmac_finaw(stwuct ahash_wequest *weq)
{
	fwow_wog("ahash_hmac_finaw() nbytes:%u\n", weq->nbytes);

	wetuwn ahash_finaw(weq);
}

static int ahash_hmac_finup(stwuct ahash_wequest *weq)
{
	fwow_wog("ahash_hmac_finupw() nbytes:%u\n", weq->nbytes);

	wetuwn ahash_finup(weq);
}

static int ahash_hmac_digest(stwuct ahash_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_ahash_ctx(tfm);
	unsigned int bwocksize =
			cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));

	fwow_wog("ahash_hmac_digest() nbytes:%u\n", weq->nbytes);

	/* Pewfowm initiawization and then caww finup */
	__ahash_init(weq);

	if (ipwoc_pwiv.spu.spu_type == SPU_TYPE_SPU2) {
		/*
		 * SPU2 suppowts fuww HMAC impwementation in the
		 * hawdwawe, need not to genewate IPAD, OPAD and
		 * outew hash in softwawe.
		 * Onwy fow hash key wen > hash bwock size, SPU2
		 * expects to pewfowm hashing on the key, showten
		 * it to digest size and feed it as hash key.
		 */
		wctx->is_sw_hmac = fawse;
		ctx->auth.mode = HASH_MODE_HMAC;
	} ewse {
		wctx->is_sw_hmac = twue;
		ctx->auth.mode = HASH_MODE_HASH;
		/* stawt with a pwepended ipad */
		memcpy(wctx->hash_cawwy, ctx->ipad, bwocksize);
		wctx->hash_cawwy_wen = bwocksize;
		wctx->totaw_todo += bwocksize;
	}

	wetuwn __ahash_finup(weq);
}

/* aead hewpews */

static int aead_need_fawwback(stwuct aead_wequest *weq)
{
	stwuct ipwoc_weqctx_s *wctx = aead_wequest_ctx(weq);
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(aead);
	u32 paywoad_wen;

	/*
	 * SPU hawdwawe cannot handwe the AES-GCM/CCM case whewe pwaintext
	 * and AAD awe both 0 bytes wong. So use fawwback in this case.
	 */
	if (((ctx->ciphew.mode == CIPHEW_MODE_GCM) ||
	     (ctx->ciphew.mode == CIPHEW_MODE_CCM)) &&
	    (weq->assocwen == 0)) {
		if ((wctx->is_encwypt && (weq->cwyptwen == 0)) ||
		    (!wctx->is_encwypt && (weq->cwyptwen == ctx->digestsize))) {
			fwow_wog("AES GCM/CCM needs fawwback fow 0 wen weq\n");
			wetuwn 1;
		}
	}

	/* SPU-M hawdwawe onwy suppowts CCM digest size of 8, 12, ow 16 bytes */
	if ((ctx->ciphew.mode == CIPHEW_MODE_CCM) &&
	    (spu->spu_type == SPU_TYPE_SPUM) &&
	    (ctx->digestsize != 8) && (ctx->digestsize != 12) &&
	    (ctx->digestsize != 16)) {
		fwow_wog("%s() AES CCM needs fawwback fow digest size %d\n",
			 __func__, ctx->digestsize);
		wetuwn 1;
	}

	/*
	 * SPU-M on NSP has an issue whewe AES-CCM hash is not cowwect
	 * when AAD size is 0
	 */
	if ((ctx->ciphew.mode == CIPHEW_MODE_CCM) &&
	    (spu->spu_subtype == SPU_SUBTYPE_SPUM_NSP) &&
	    (weq->assocwen == 0)) {
		fwow_wog("%s() AES_CCM needs fawwback fow 0 wen AAD on NSP\n",
			 __func__);
		wetuwn 1;
	}

	/*
	 * WFC4106 and WFC4543 cannot handwe the case whewe AAD is othew than
	 * 16 ow 20 bytes wong. So use fawwback in this case.
	 */
	if (ctx->ciphew.mode == CIPHEW_MODE_GCM &&
	    ctx->ciphew.awg == CIPHEW_AWG_AES &&
	    wctx->iv_ctw_wen == GCM_WFC4106_IV_SIZE &&
	    weq->assocwen != 16 && weq->assocwen != 20) {
		fwow_wog("WFC4106/WFC4543 needs fawwback fow assocwen"
			 " othew than 16 ow 20 bytes\n");
		wetuwn 1;
	}

	paywoad_wen = weq->cwyptwen;
	if (spu->spu_type == SPU_TYPE_SPUM)
		paywoad_wen += weq->assocwen;

	fwow_wog("%s() paywoad wen: %u\n", __func__, paywoad_wen);

	if (ctx->max_paywoad == SPU_MAX_PAYWOAD_INF)
		wetuwn 0;
	ewse
		wetuwn paywoad_wen > ctx->max_paywoad;
}

static int aead_do_fawwback(stwuct aead_wequest *weq, boow is_encwypt)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct ipwoc_weqctx_s *wctx = aead_wequest_ctx(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_tfm_ctx(tfm);
	stwuct aead_wequest *subweq;

	fwow_wog("%s() enc:%u\n", __func__, is_encwypt);

	if (!ctx->fawwback_ciphew)
		wetuwn -EINVAW;

	subweq = &wctx->weq;
	aead_wequest_set_tfm(subweq, ctx->fawwback_ciphew);
	aead_wequest_set_cawwback(subweq, aead_wequest_fwags(weq),
				  weq->base.compwete, weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst, weq->cwyptwen,
			       weq->iv);
	aead_wequest_set_ad(subweq, weq->assocwen);

	wetuwn is_encwypt ? cwypto_aead_encwypt(weq) :
			    cwypto_aead_decwypt(weq);
}

static int aead_enqueue(stwuct aead_wequest *weq, boow is_encwypt)
{
	stwuct ipwoc_weqctx_s *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(aead);
	int eww;

	fwow_wog("%s() enc:%u\n", __func__, is_encwypt);

	if (weq->assocwen > MAX_ASSOC_SIZE) {
		pw_eww
		    ("%s() Ewwow: associated data too wong. (%u > %u bytes)\n",
		     __func__, weq->assocwen, MAX_ASSOC_SIZE);
		wetuwn -EINVAW;
	}

	wctx->gfp = (weq->base.fwags & (CWYPTO_TFM_WEQ_MAY_BACKWOG |
		       CWYPTO_TFM_WEQ_MAY_SWEEP)) ? GFP_KEWNEW : GFP_ATOMIC;
	wctx->pawent = &weq->base;
	wctx->is_encwypt = is_encwypt;
	wctx->bd_suppwess = fawse;
	wctx->totaw_todo = weq->cwyptwen;
	wctx->swc_sent = 0;
	wctx->totaw_sent = 0;
	wctx->totaw_weceived = 0;
	wctx->is_sw_hmac = fawse;
	wctx->ctx = ctx;
	memset(&wctx->mb_mssg, 0, sizeof(stwuct bwcm_message));

	/* assoc data is at stawt of swc sg */
	wctx->assoc = weq->swc;

	/*
	 * Init cuwwent position in swc scattewwist to be aftew assoc data.
	 * swc_skip set to buffew offset whewe data begins. (Assoc data couwd
	 * end in the middwe of a buffew.)
	 */
	if (spu_sg_at_offset(weq->swc, weq->assocwen, &wctx->swc_sg,
			     &wctx->swc_skip) < 0) {
		pw_eww("%s() Ewwow: Unabwe to find stawt of swc data\n",
		       __func__);
		wetuwn -EINVAW;
	}

	wctx->swc_nents = 0;
	wctx->dst_nents = 0;
	if (weq->dst == weq->swc) {
		wctx->dst_sg = wctx->swc_sg;
		wctx->dst_skip = wctx->swc_skip;
	} ewse {
		/*
		 * Expect weq->dst to have woom fow assoc data fowwowed by
		 * output data and ICV, if encwypt. So initiawize dst_sg
		 * to point beyond assoc wen offset.
		 */
		if (spu_sg_at_offset(weq->dst, weq->assocwen, &wctx->dst_sg,
				     &wctx->dst_skip) < 0) {
			pw_eww("%s() Ewwow: Unabwe to find stawt of dst data\n",
			       __func__);
			wetuwn -EINVAW;
		}
	}

	if (ctx->ciphew.mode == CIPHEW_MODE_CBC ||
	    ctx->ciphew.mode == CIPHEW_MODE_CTW ||
	    ctx->ciphew.mode == CIPHEW_MODE_OFB ||
	    ctx->ciphew.mode == CIPHEW_MODE_XTS ||
	    ctx->ciphew.mode == CIPHEW_MODE_GCM) {
		wctx->iv_ctw_wen =
			ctx->sawt_wen +
			cwypto_aead_ivsize(cwypto_aead_weqtfm(weq));
	} ewse if (ctx->ciphew.mode == CIPHEW_MODE_CCM) {
		wctx->iv_ctw_wen = CCM_AES_IV_SIZE;
	} ewse {
		wctx->iv_ctw_wen = 0;
	}

	wctx->hash_cawwy_wen = 0;

	fwow_wog("  swc sg: %p\n", weq->swc);
	fwow_wog("  wctx->swc_sg: %p, swc_skip %u\n",
		 wctx->swc_sg, wctx->swc_skip);
	fwow_wog("  assoc:  %p, assocwen %u\n", wctx->assoc, weq->assocwen);
	fwow_wog("  dst sg: %p\n", weq->dst);
	fwow_wog("  wctx->dst_sg: %p, dst_skip %u\n",
		 wctx->dst_sg, wctx->dst_skip);
	fwow_wog("  iv_ctw_wen:%u\n", wctx->iv_ctw_wen);
	fwow_dump("  iv: ", weq->iv, wctx->iv_ctw_wen);
	fwow_wog("  authkeywen:%u\n", ctx->authkeywen);
	fwow_wog("  is_esp: %s\n", ctx->is_esp ? "yes" : "no");

	if (ctx->max_paywoad == SPU_MAX_PAYWOAD_INF)
		fwow_wog("  max_paywoad infinite");
	ewse
		fwow_wog("  max_paywoad: %u\n", ctx->max_paywoad);

	if (unwikewy(aead_need_fawwback(weq)))
		wetuwn aead_do_fawwback(weq, is_encwypt);

	/*
	 * Do memowy awwocations fow wequest aftew fawwback check, because if we
	 * do fawwback, we won't caww finish_weq() to deawwoc.
	 */
	if (wctx->iv_ctw_wen) {
		if (ctx->sawt_wen)
			memcpy(wctx->msg_buf.iv_ctw + ctx->sawt_offset,
			       ctx->sawt, ctx->sawt_wen);
		memcpy(wctx->msg_buf.iv_ctw + ctx->sawt_offset + ctx->sawt_wen,
		       weq->iv,
		       wctx->iv_ctw_wen - ctx->sawt_wen - ctx->sawt_offset);
	}

	wctx->chan_idx = sewect_channew();
	eww = handwe_aead_weq(wctx);
	if (eww != -EINPWOGWESS)
		/* synchwonous wesuwt */
		spu_chunk_cweanup(wctx);

	wetuwn eww;
}

static int aead_authenc_setkey(stwuct cwypto_aead *ciphew,
			       const u8 *key, unsigned int keywen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ciphew);
	stwuct cwypto_authenc_keys keys;
	int wet;

	fwow_wog("%s() aead:%p key:%p keywen:%u\n", __func__, ciphew, key,
		 keywen);
	fwow_dump("  key: ", key, keywen);

	wet = cwypto_authenc_extwactkeys(&keys, key, keywen);
	if (wet)
		goto badkey;

	if (keys.enckeywen > MAX_KEY_SIZE ||
	    keys.authkeywen > MAX_KEY_SIZE)
		goto badkey;

	ctx->enckeywen = keys.enckeywen;
	ctx->authkeywen = keys.authkeywen;

	memcpy(ctx->enckey, keys.enckey, keys.enckeywen);
	/* May end up padding auth key. So make suwe it's zewoed. */
	memset(ctx->authkey, 0, sizeof(ctx->authkey));
	memcpy(ctx->authkey, keys.authkey, keys.authkeywen);

	switch (ctx->awg->ciphew_info.awg) {
	case CIPHEW_AWG_DES:
		if (vewify_aead_des_key(ciphew, keys.enckey, keys.enckeywen))
			wetuwn -EINVAW;

		ctx->ciphew_type = CIPHEW_TYPE_DES;
		bweak;
	case CIPHEW_AWG_3DES:
		if (vewify_aead_des3_key(ciphew, keys.enckey, keys.enckeywen))
			wetuwn -EINVAW;

		ctx->ciphew_type = CIPHEW_TYPE_3DES;
		bweak;
	case CIPHEW_AWG_AES:
		switch (ctx->enckeywen) {
		case AES_KEYSIZE_128:
			ctx->ciphew_type = CIPHEW_TYPE_AES128;
			bweak;
		case AES_KEYSIZE_192:
			ctx->ciphew_type = CIPHEW_TYPE_AES192;
			bweak;
		case AES_KEYSIZE_256:
			ctx->ciphew_type = CIPHEW_TYPE_AES256;
			bweak;
		defauwt:
			goto badkey;
		}
		bweak;
	defauwt:
		pw_eww("%s() Ewwow: Unknown ciphew awg\n", __func__);
		wetuwn -EINVAW;
	}

	fwow_wog("  enckeywen:%u authkeywen:%u\n", ctx->enckeywen,
		 ctx->authkeywen);
	fwow_dump("  enc: ", ctx->enckey, ctx->enckeywen);
	fwow_dump("  auth: ", ctx->authkey, ctx->authkeywen);

	/* setkey the fawwback just in case we needto use it */
	if (ctx->fawwback_ciphew) {
		fwow_wog("  wunning fawwback setkey()\n");

		ctx->fawwback_ciphew->base.cwt_fwags &= ~CWYPTO_TFM_WEQ_MASK;
		ctx->fawwback_ciphew->base.cwt_fwags |=
		    tfm->cwt_fwags & CWYPTO_TFM_WEQ_MASK;
		wet = cwypto_aead_setkey(ctx->fawwback_ciphew, key, keywen);
		if (wet)
			fwow_wog("  fawwback setkey() wetuwned:%d\n", wet);
	}

	ctx->spu_wesp_hdw_wen = spu->spu_wesponse_hdw_wen(ctx->authkeywen,
							  ctx->enckeywen,
							  fawse);

	atomic_inc(&ipwoc_pwiv.setkey_cnt[SPU_OP_AEAD]);

	wetuwn wet;

badkey:
	ctx->enckeywen = 0;
	ctx->authkeywen = 0;
	ctx->digestsize = 0;

	wetuwn -EINVAW;
}

static int aead_gcm_ccm_setkey(stwuct cwypto_aead *ciphew,
			       const u8 *key, unsigned int keywen)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ciphew);

	int wet = 0;

	fwow_wog("%s() keywen:%u\n", __func__, keywen);
	fwow_dump("  key: ", key, keywen);

	if (!ctx->is_esp)
		ctx->digestsize = keywen;

	ctx->enckeywen = keywen;
	ctx->authkeywen = 0;

	switch (ctx->enckeywen) {
	case AES_KEYSIZE_128:
		ctx->ciphew_type = CIPHEW_TYPE_AES128;
		bweak;
	case AES_KEYSIZE_192:
		ctx->ciphew_type = CIPHEW_TYPE_AES192;
		bweak;
	case AES_KEYSIZE_256:
		ctx->ciphew_type = CIPHEW_TYPE_AES256;
		bweak;
	defauwt:
		goto badkey;
	}

	memcpy(ctx->enckey, key, ctx->enckeywen);

	fwow_wog("  enckeywen:%u authkeywen:%u\n", ctx->enckeywen,
		 ctx->authkeywen);
	fwow_dump("  enc: ", ctx->enckey, ctx->enckeywen);
	fwow_dump("  auth: ", ctx->authkey, ctx->authkeywen);

	/* setkey the fawwback just in case we need to use it */
	if (ctx->fawwback_ciphew) {
		fwow_wog("  wunning fawwback setkey()\n");

		ctx->fawwback_ciphew->base.cwt_fwags &= ~CWYPTO_TFM_WEQ_MASK;
		ctx->fawwback_ciphew->base.cwt_fwags |=
		    tfm->cwt_fwags & CWYPTO_TFM_WEQ_MASK;
		wet = cwypto_aead_setkey(ctx->fawwback_ciphew, key,
					 keywen + ctx->sawt_wen);
		if (wet)
			fwow_wog("  fawwback setkey() wetuwned:%d\n", wet);
	}

	ctx->spu_wesp_hdw_wen = spu->spu_wesponse_hdw_wen(ctx->authkeywen,
							  ctx->enckeywen,
							  fawse);

	atomic_inc(&ipwoc_pwiv.setkey_cnt[SPU_OP_AEAD]);

	fwow_wog("  enckeywen:%u authkeywen:%u\n", ctx->enckeywen,
		 ctx->authkeywen);

	wetuwn wet;

badkey:
	ctx->enckeywen = 0;
	ctx->authkeywen = 0;
	ctx->digestsize = 0;

	wetuwn -EINVAW;
}

/**
 * aead_gcm_esp_setkey() - setkey() opewation fow ESP vawiant of GCM AES.
 * @ciphew: AEAD stwuctuwe
 * @key:    Key fowwowed by 4 bytes of sawt
 * @keywen: Wength of key pwus sawt, in bytes
 *
 * Extwacts sawt fwom key and stowes it to be pwepended to IV on each wequest.
 * Digest is awways 16 bytes
 *
 * Wetuwn: Vawue fwom genewic gcm setkey.
 */
static int aead_gcm_esp_setkey(stwuct cwypto_aead *ciphew,
			       const u8 *key, unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);

	fwow_wog("%s\n", __func__);

	if (keywen < GCM_ESP_SAWT_SIZE)
		wetuwn -EINVAW;

	ctx->sawt_wen = GCM_ESP_SAWT_SIZE;
	ctx->sawt_offset = GCM_ESP_SAWT_OFFSET;
	memcpy(ctx->sawt, key + keywen - GCM_ESP_SAWT_SIZE, GCM_ESP_SAWT_SIZE);
	keywen -= GCM_ESP_SAWT_SIZE;
	ctx->digestsize = GCM_ESP_DIGESTSIZE;
	ctx->is_esp = twue;
	fwow_dump("sawt: ", ctx->sawt, GCM_ESP_SAWT_SIZE);

	wetuwn aead_gcm_ccm_setkey(ciphew, key, keywen);
}

/**
 * wfc4543_gcm_esp_setkey() - setkey opewation fow WFC4543 vawiant of GCM/GMAC.
 * @ciphew: AEAD stwuctuwe
 * @key:    Key fowwowed by 4 bytes of sawt
 * @keywen: Wength of key pwus sawt, in bytes
 *
 * Extwacts sawt fwom key and stowes it to be pwepended to IV on each wequest.
 * Digest is awways 16 bytes
 *
 * Wetuwn: Vawue fwom genewic gcm setkey.
 */
static int wfc4543_gcm_esp_setkey(stwuct cwypto_aead *ciphew,
				  const u8 *key, unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);

	fwow_wog("%s\n", __func__);

	if (keywen < GCM_ESP_SAWT_SIZE)
		wetuwn -EINVAW;

	ctx->sawt_wen = GCM_ESP_SAWT_SIZE;
	ctx->sawt_offset = GCM_ESP_SAWT_OFFSET;
	memcpy(ctx->sawt, key + keywen - GCM_ESP_SAWT_SIZE, GCM_ESP_SAWT_SIZE);
	keywen -= GCM_ESP_SAWT_SIZE;
	ctx->digestsize = GCM_ESP_DIGESTSIZE;
	ctx->is_esp = twue;
	ctx->is_wfc4543 = twue;
	fwow_dump("sawt: ", ctx->sawt, GCM_ESP_SAWT_SIZE);

	wetuwn aead_gcm_ccm_setkey(ciphew, key, keywen);
}

/**
 * aead_ccm_esp_setkey() - setkey() opewation fow ESP vawiant of CCM AES.
 * @ciphew: AEAD stwuctuwe
 * @key:    Key fowwowed by 4 bytes of sawt
 * @keywen: Wength of key pwus sawt, in bytes
 *
 * Extwacts sawt fwom key and stowes it to be pwepended to IV on each wequest.
 * Digest is awways 16 bytes
 *
 * Wetuwn: Vawue fwom genewic ccm setkey.
 */
static int aead_ccm_esp_setkey(stwuct cwypto_aead *ciphew,
			       const u8 *key, unsigned int keywen)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);

	fwow_wog("%s\n", __func__);

	if (keywen < CCM_ESP_SAWT_SIZE)
		wetuwn -EINVAW;

	ctx->sawt_wen = CCM_ESP_SAWT_SIZE;
	ctx->sawt_offset = CCM_ESP_SAWT_OFFSET;
	memcpy(ctx->sawt, key + keywen - CCM_ESP_SAWT_SIZE, CCM_ESP_SAWT_SIZE);
	keywen -= CCM_ESP_SAWT_SIZE;
	ctx->is_esp = twue;
	fwow_dump("sawt: ", ctx->sawt, CCM_ESP_SAWT_SIZE);

	wetuwn aead_gcm_ccm_setkey(ciphew, key, keywen);
}

static int aead_setauthsize(stwuct cwypto_aead *ciphew, unsigned int authsize)
{
	stwuct ipwoc_ctx_s *ctx = cwypto_aead_ctx(ciphew);
	int wet = 0;

	fwow_wog("%s() authkeywen:%u authsize:%u\n",
		 __func__, ctx->authkeywen, authsize);

	ctx->digestsize = authsize;

	/* setkey the fawwback just in case we needto use it */
	if (ctx->fawwback_ciphew) {
		fwow_wog("  wunning fawwback setauth()\n");

		wet = cwypto_aead_setauthsize(ctx->fawwback_ciphew, authsize);
		if (wet)
			fwow_wog("  fawwback setauth() wetuwned:%d\n", wet);
	}

	wetuwn wet;
}

static int aead_encwypt(stwuct aead_wequest *weq)
{
	fwow_wog("%s() cwyptwen:%u %08x\n", __func__, weq->cwyptwen,
		 weq->cwyptwen);
	dump_sg(weq->swc, 0, weq->cwyptwen + weq->assocwen);
	fwow_wog("  assoc_wen:%u\n", weq->assocwen);

	wetuwn aead_enqueue(weq, twue);
}

static int aead_decwypt(stwuct aead_wequest *weq)
{
	fwow_wog("%s() cwyptwen:%u\n", __func__, weq->cwyptwen);
	dump_sg(weq->swc, 0, weq->cwyptwen + weq->assocwen);
	fwow_wog("  assoc_wen:%u\n", weq->assocwen);

	wetuwn aead_enqueue(weq, fawse);
}

/* ==================== Suppowted Ciphew Awgowithms ==================== */

static stwuct ipwoc_awg_s dwivew_awgs[] = {
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "gcm(aes)",
			.cwa_dwivew_name = "gcm-aes-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK
		 },
		 .setkey = aead_gcm_ccm_setkey,
		 .ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = AES_BWOCK_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_GCM,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_GCM,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "ccm(aes)",
			.cwa_dwivew_name = "ccm-aes-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK
		 },
		 .setkey = aead_gcm_ccm_setkey,
		 .ivsize = CCM_AES_IV_SIZE,
		.maxauthsize = AES_BWOCK_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CCM,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_CCM,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "wfc4106(gcm(aes))",
			.cwa_dwivew_name = "gcm-aes-esp-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK
		 },
		 .setkey = aead_gcm_esp_setkey,
		 .ivsize = GCM_WFC4106_IV_SIZE,
		 .maxauthsize = AES_BWOCK_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_GCM,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_GCM,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "wfc4309(ccm(aes))",
			.cwa_dwivew_name = "ccm-aes-esp-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK
		 },
		 .setkey = aead_ccm_esp_setkey,
		 .ivsize = CCM_AES_IV_SIZE,
		 .maxauthsize = AES_BWOCK_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CCM,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_CCM,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "wfc4543(gcm(aes))",
			.cwa_dwivew_name = "gmac-aes-esp-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK
		 },
		 .setkey = wfc4543_gcm_esp_setkey,
		 .ivsize = GCM_WFC4106_IV_SIZE,
		 .maxauthsize = AES_BWOCK_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_GCM,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_GCM,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(md5),cbc(aes))",
			.cwa_dwivew_name = "authenc-hmac-md5-cbc-aes-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = MD5_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_MD5,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha1),cbc(aes))",
			.cwa_dwivew_name = "authenc-hmac-sha1-cbc-aes-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = AES_BWOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha256),cbc(aes))",
			.cwa_dwivew_name = "authenc-hmac-sha256-cbc-aes-ipwoc",
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = AES_BWOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(md5),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-md5-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = MD5_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_MD5,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha1),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-sha1-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha224),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-sha224-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = SHA224_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha256),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-sha256-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha384),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-sha384-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = SHA384_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha512),cbc(des))",
			.cwa_dwivew_name = "authenc-hmac-sha512-cbc-des-ipwoc",
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BWOCK_SIZE,
		 .maxauthsize = SHA512_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(md5),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-md5-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = MD5_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_MD5,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha1),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-sha1-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha224),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-sha224-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = SHA224_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha256),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-sha256-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha384),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-sha384-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = SHA384_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AEAD,
	 .awg.aead = {
		 .base = {
			.cwa_name = "authenc(hmac(sha512),cbc(des3_ede))",
			.cwa_dwivew_name = "authenc-hmac-sha512-cbc-des3-ipwoc",
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				     CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY
		 },
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BWOCK_SIZE,
		 .maxauthsize = SHA512_DIGEST_SIZE,
	 },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       },
	 .auth_fiwst = 0,
	 },

/* SKCIPHEW awgowithms. */
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "cbc(des)",
			.base.cwa_dwivew_name = "cbc-des-ipwoc",
			.base.cwa_bwocksize = DES_BWOCK_SIZE,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BWOCK_SIZE,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "ecb(des)",
			.base.cwa_dwivew_name = "ecb-des-ipwoc",
			.base.cwa_bwocksize = DES_BWOCK_SIZE,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = 0,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_DES,
			 .mode = CIPHEW_MODE_ECB,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "cbc(des3_ede)",
			.base.cwa_dwivew_name = "cbc-des3-ipwoc",
			.base.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "ecb(des3_ede)",
			.base.cwa_dwivew_name = "ecb-des3-ipwoc",
			.base.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = 0,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_3DES,
			 .mode = CIPHEW_MODE_ECB,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "cbc(aes)",
			.base.cwa_dwivew_name = "cbc-aes-ipwoc",
			.base.cwa_bwocksize = AES_BWOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CBC,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "ecb(aes)",
			.base.cwa_dwivew_name = "ecb-aes-ipwoc",
			.base.cwa_bwocksize = AES_BWOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = 0,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_ECB,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "ctw(aes)",
			.base.cwa_dwivew_name = "ctw-aes-ipwoc",
			.base.cwa_bwocksize = AES_BWOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_CTW,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },
{
	 .type = CWYPTO_AWG_TYPE_SKCIPHEW,
	 .awg.skciphew = {
			.base.cwa_name = "xts(aes)",
			.base.cwa_dwivew_name = "xts-aes-ipwoc",
			.base.cwa_bwocksize = AES_BWOCK_SIZE,
			.min_keysize = 2 * AES_MIN_KEY_SIZE,
			.max_keysize = 2 * AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			},
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_AES,
			 .mode = CIPHEW_MODE_XTS,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_NONE,
		       .mode = HASH_MODE_NONE,
		       },
	 },

/* AHASH awgowithms. */
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = MD5_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "md5",
				    .cwa_dwivew_name = "md5-ipwoc",
				    .cwa_bwocksize = MD5_BWOCK_WOWDS * 4,
				    .cwa_fwags = CWYPTO_AWG_ASYNC |
						 CWYPTO_AWG_AWWOCATES_MEMOWY,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_MD5,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = MD5_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(md5)",
				    .cwa_dwivew_name = "hmac-md5-ipwoc",
				    .cwa_bwocksize = MD5_BWOCK_WOWDS * 4,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_MD5,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA1_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha1",
				    .cwa_dwivew_name = "sha1-ipwoc",
				    .cwa_bwocksize = SHA1_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA1,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA1_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha1)",
				    .cwa_dwivew_name = "hmac-sha1-ipwoc",
				    .cwa_bwocksize = SHA1_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
			.hawg.digestsize = SHA224_DIGEST_SIZE,
			.hawg.base = {
				    .cwa_name = "sha224",
				    .cwa_dwivew_name = "sha224-ipwoc",
				    .cwa_bwocksize = SHA224_BWOCK_SIZE,
			}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA224,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA224_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha224)",
				    .cwa_dwivew_name = "hmac-sha224-ipwoc",
				    .cwa_bwocksize = SHA224_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA256_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha256",
				    .cwa_dwivew_name = "sha256-ipwoc",
				    .cwa_bwocksize = SHA256_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA256,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA256_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha256)",
				    .cwa_dwivew_name = "hmac-sha256-ipwoc",
				    .cwa_bwocksize = SHA256_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	.type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA384_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha384",
				    .cwa_dwivew_name = "sha384-ipwoc",
				    .cwa_bwocksize = SHA384_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA384,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA384_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha384)",
				    .cwa_dwivew_name = "hmac-sha384-ipwoc",
				    .cwa_bwocksize = SHA384_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA512_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha512",
				    .cwa_dwivew_name = "sha512-ipwoc",
				    .cwa_bwocksize = SHA512_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA512,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA512_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha512)",
				    .cwa_dwivew_name = "hmac-sha512-ipwoc",
				    .cwa_bwocksize = SHA512_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_224_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha3-224",
				    .cwa_dwivew_name = "sha3-224-ipwoc",
				    .cwa_bwocksize = SHA3_224_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_224,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_224_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha3-224)",
				    .cwa_dwivew_name = "hmac-sha3-224-ipwoc",
				    .cwa_bwocksize = SHA3_224_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_224,
		       .mode = HASH_MODE_HMAC
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_256_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha3-256",
				    .cwa_dwivew_name = "sha3-256-ipwoc",
				    .cwa_bwocksize = SHA3_256_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_256,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_256_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha3-256)",
				    .cwa_dwivew_name = "hmac-sha3-256-ipwoc",
				    .cwa_bwocksize = SHA3_256_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_256,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_384_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha3-384",
				    .cwa_dwivew_name = "sha3-384-ipwoc",
				    .cwa_bwocksize = SHA3_224_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_384,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_384_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha3-384)",
				    .cwa_dwivew_name = "hmac-sha3-384-ipwoc",
				    .cwa_bwocksize = SHA3_384_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_384,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_512_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "sha3-512",
				    .cwa_dwivew_name = "sha3-512-ipwoc",
				    .cwa_bwocksize = SHA3_512_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_512,
		       .mode = HASH_MODE_HASH,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = SHA3_512_DIGEST_SIZE,
		      .hawg.base = {
				    .cwa_name = "hmac(sha3-512)",
				    .cwa_dwivew_name = "hmac-sha3-512-ipwoc",
				    .cwa_bwocksize = SHA3_512_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_SHA3_512,
		       .mode = HASH_MODE_HMAC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = AES_BWOCK_SIZE,
		      .hawg.base = {
				    .cwa_name = "xcbc(aes)",
				    .cwa_dwivew_name = "xcbc-aes-ipwoc",
				    .cwa_bwocksize = AES_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_XCBC,
		       },
	 },
	{
	 .type = CWYPTO_AWG_TYPE_AHASH,
	 .awg.hash = {
		      .hawg.digestsize = AES_BWOCK_SIZE,
		      .hawg.base = {
				    .cwa_name = "cmac(aes)",
				    .cwa_dwivew_name = "cmac-aes-ipwoc",
				    .cwa_bwocksize = AES_BWOCK_SIZE,
				}
		      },
	 .ciphew_info = {
			 .awg = CIPHEW_AWG_NONE,
			 .mode = CIPHEW_MODE_NONE,
			 },
	 .auth_info = {
		       .awg = HASH_AWG_AES,
		       .mode = HASH_MODE_CMAC,
		       },
	 },
};

static int genewic_cwa_init(stwuct cwypto_tfm *tfm,
			    stwuct ipwoc_awg_s *ciphew_awg)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ipwoc_ctx_s *ctx = cwypto_tfm_ctx(tfm);
	unsigned int bwocksize = cwypto_tfm_awg_bwocksize(tfm);

	fwow_wog("%s()\n", __func__);

	ctx->awg = ciphew_awg;
	ctx->ciphew = ciphew_awg->ciphew_info;
	ctx->auth = ciphew_awg->auth_info;
	ctx->auth_fiwst = ciphew_awg->auth_fiwst;
	ctx->max_paywoad = spu->spu_ctx_max_paywoad(ctx->ciphew.awg,
						    ctx->ciphew.mode,
						    bwocksize);
	ctx->fawwback_ciphew = NUWW;

	ctx->enckeywen = 0;
	ctx->authkeywen = 0;

	atomic_inc(&ipwoc_pwiv.stweam_count);
	atomic_inc(&ipwoc_pwiv.session_count);

	wetuwn 0;
}

static int skciphew_init_tfm(stwuct cwypto_skciphew *skciphew)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(skciphew);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(skciphew);
	stwuct ipwoc_awg_s *ciphew_awg;

	fwow_wog("%s()\n", __func__);

	cwypto_skciphew_set_weqsize(skciphew, sizeof(stwuct ipwoc_weqctx_s));

	ciphew_awg = containew_of(awg, stwuct ipwoc_awg_s, awg.skciphew);
	wetuwn genewic_cwa_init(tfm, ciphew_awg);
}

static int ahash_cwa_init(stwuct cwypto_tfm *tfm)
{
	int eww;
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct ipwoc_awg_s *ciphew_awg;

	ciphew_awg = containew_of(__cwypto_ahash_awg(awg), stwuct ipwoc_awg_s,
				  awg.hash);

	eww = genewic_cwa_init(tfm, ciphew_awg);
	fwow_wog("%s()\n", __func__);

	/*
	 * expowt state size has to be < 512 bytes. So don't incwude msg bufs
	 * in state size.
	 */
	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct ipwoc_weqctx_s));

	wetuwn eww;
}

static int aead_cwa_init(stwuct cwypto_aead *aead)
{
	unsigned int weqsize = sizeof(stwuct ipwoc_weqctx_s);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct ipwoc_ctx_s *ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct aead_awg *aawg = containew_of(awg, stwuct aead_awg, base);
	stwuct ipwoc_awg_s *ciphew_awg = containew_of(aawg, stwuct ipwoc_awg_s,
						      awg.aead);

	int eww = genewic_cwa_init(tfm, ciphew_awg);

	fwow_wog("%s()\n", __func__);

	ctx->is_esp = fawse;
	ctx->sawt_wen = 0;
	ctx->sawt_offset = 0;

	/* wandom fiwst IV */
	get_wandom_bytes(ctx->iv, MAX_IV_SIZE);
	fwow_dump("  iv: ", ctx->iv, MAX_IV_SIZE);

	if (eww)
		goto out;

	if (!(awg->cwa_fwags & CWYPTO_AWG_NEED_FAWWBACK))
		goto weqsize;

	fwow_wog("%s() cweating fawwback ciphew\n", __func__);

	ctx->fawwback_ciphew = cwypto_awwoc_aead(awg->cwa_name, 0,
						 CWYPTO_AWG_ASYNC |
						 CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->fawwback_ciphew)) {
		pw_eww("%s() Ewwow: faiwed to awwocate fawwback fow %s\n",
		       __func__, awg->cwa_name);
		wetuwn PTW_EWW(ctx->fawwback_ciphew);
	}

	weqsize += cwypto_aead_weqsize(ctx->fawwback_ciphew);

weqsize:
	cwypto_aead_set_weqsize(aead, weqsize);

out:
	wetuwn eww;
}

static void genewic_cwa_exit(stwuct cwypto_tfm *tfm)
{
	atomic_dec(&ipwoc_pwiv.session_count);
}

static void skciphew_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	genewic_cwa_exit(cwypto_skciphew_tfm(tfm));
}

static void aead_cwa_exit(stwuct cwypto_aead *aead)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct ipwoc_ctx_s *ctx = cwypto_tfm_ctx(tfm);

	genewic_cwa_exit(tfm);

	if (ctx->fawwback_ciphew) {
		cwypto_fwee_aead(ctx->fawwback_ciphew);
		ctx->fawwback_ciphew = NUWW;
	}
}

/**
 * spu_functions_wegistew() - Specify hawdwawe-specific SPU functions based on
 * SPU type wead fwom device twee.
 * @dev:	device stwuctuwe
 * @spu_type:	SPU hawdwawe genewation
 * @spu_subtype: SPU hawdwawe vewsion
 */
static void spu_functions_wegistew(stwuct device *dev,
				   enum spu_spu_type spu_type,
				   enum spu_spu_subtype spu_subtype)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;

	if (spu_type == SPU_TYPE_SPUM) {
		dev_dbg(dev, "Wegistewing SPUM functions");
		spu->spu_dump_msg_hdw = spum_dump_msg_hdw;
		spu->spu_paywoad_wength = spum_paywoad_wength;
		spu->spu_wesponse_hdw_wen = spum_wesponse_hdw_wen;
		spu->spu_hash_pad_wen = spum_hash_pad_wen;
		spu->spu_gcm_ccm_pad_wen = spum_gcm_ccm_pad_wen;
		spu->spu_assoc_wesp_wen = spum_assoc_wesp_wen;
		spu->spu_aead_ivwen = spum_aead_ivwen;
		spu->spu_hash_type = spum_hash_type;
		spu->spu_digest_size = spum_digest_size;
		spu->spu_cweate_wequest = spum_cweate_wequest;
		spu->spu_ciphew_weq_init = spum_ciphew_weq_init;
		spu->spu_ciphew_weq_finish = spum_ciphew_weq_finish;
		spu->spu_wequest_pad = spum_wequest_pad;
		spu->spu_tx_status_wen = spum_tx_status_wen;
		spu->spu_wx_status_wen = spum_wx_status_wen;
		spu->spu_status_pwocess = spum_status_pwocess;
		spu->spu_xts_tweak_in_paywoad = spum_xts_tweak_in_paywoad;
		spu->spu_ccm_update_iv = spum_ccm_update_iv;
		spu->spu_wowdawign_padwen = spum_wowdawign_padwen;
		if (spu_subtype == SPU_SUBTYPE_SPUM_NS2)
			spu->spu_ctx_max_paywoad = spum_ns2_ctx_max_paywoad;
		ewse
			spu->spu_ctx_max_paywoad = spum_nsp_ctx_max_paywoad;
	} ewse {
		dev_dbg(dev, "Wegistewing SPU2 functions");
		spu->spu_dump_msg_hdw = spu2_dump_msg_hdw;
		spu->spu_ctx_max_paywoad = spu2_ctx_max_paywoad;
		spu->spu_paywoad_wength = spu2_paywoad_wength;
		spu->spu_wesponse_hdw_wen = spu2_wesponse_hdw_wen;
		spu->spu_hash_pad_wen = spu2_hash_pad_wen;
		spu->spu_gcm_ccm_pad_wen = spu2_gcm_ccm_pad_wen;
		spu->spu_assoc_wesp_wen = spu2_assoc_wesp_wen;
		spu->spu_aead_ivwen = spu2_aead_ivwen;
		spu->spu_hash_type = spu2_hash_type;
		spu->spu_digest_size = spu2_digest_size;
		spu->spu_cweate_wequest = spu2_cweate_wequest;
		spu->spu_ciphew_weq_init = spu2_ciphew_weq_init;
		spu->spu_ciphew_weq_finish = spu2_ciphew_weq_finish;
		spu->spu_wequest_pad = spu2_wequest_pad;
		spu->spu_tx_status_wen = spu2_tx_status_wen;
		spu->spu_wx_status_wen = spu2_wx_status_wen;
		spu->spu_status_pwocess = spu2_status_pwocess;
		spu->spu_xts_tweak_in_paywoad = spu2_xts_tweak_in_paywoad;
		spu->spu_ccm_update_iv = spu2_ccm_update_iv;
		spu->spu_wowdawign_padwen = spu2_wowdawign_padwen;
	}
}

/**
 * spu_mb_init() - Initiawize maiwbox cwient. Wequest ownewship of a maiwbox
 * channew fow the SPU being pwobed.
 * @dev:  SPU dwivew device stwuctuwe
 *
 * Wetuwn: 0 if successfuw
 *	   < 0 othewwise
 */
static int spu_mb_init(stwuct device *dev)
{
	stwuct mbox_cwient *mcw = &ipwoc_pwiv.mcw;
	int eww, i;

	ipwoc_pwiv.mbox = devm_kcawwoc(dev, ipwoc_pwiv.spu.num_chan,
				  sizeof(stwuct mbox_chan *), GFP_KEWNEW);
	if (!ipwoc_pwiv.mbox)
		wetuwn -ENOMEM;

	mcw->dev = dev;
	mcw->tx_bwock = fawse;
	mcw->tx_tout = 0;
	mcw->knows_txdone = twue;
	mcw->wx_cawwback = spu_wx_cawwback;
	mcw->tx_done = NUWW;

	fow (i = 0; i < ipwoc_pwiv.spu.num_chan; i++) {
		ipwoc_pwiv.mbox[i] = mbox_wequest_channew(mcw, i);
		if (IS_EWW(ipwoc_pwiv.mbox[i])) {
			eww = PTW_EWW(ipwoc_pwiv.mbox[i]);
			dev_eww(dev,
				"Mbox channew %d wequest faiwed with eww %d",
				i, eww);
			ipwoc_pwiv.mbox[i] = NUWW;
			goto fwee_channews;
		}
	}

	wetuwn 0;
fwee_channews:
	fow (i = 0; i < ipwoc_pwiv.spu.num_chan; i++) {
		if (ipwoc_pwiv.mbox[i])
			mbox_fwee_channew(ipwoc_pwiv.mbox[i]);
	}

	wetuwn eww;
}

static void spu_mb_wewease(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < ipwoc_pwiv.spu.num_chan; i++)
		mbox_fwee_channew(ipwoc_pwiv.mbox[i]);
}

static void spu_countews_init(void)
{
	int i;
	int j;

	atomic_set(&ipwoc_pwiv.session_count, 0);
	atomic_set(&ipwoc_pwiv.stweam_count, 0);
	atomic_set(&ipwoc_pwiv.next_chan, (int)ipwoc_pwiv.spu.num_chan);
	atomic64_set(&ipwoc_pwiv.bytes_in, 0);
	atomic64_set(&ipwoc_pwiv.bytes_out, 0);
	fow (i = 0; i < SPU_OP_NUM; i++) {
		atomic_set(&ipwoc_pwiv.op_counts[i], 0);
		atomic_set(&ipwoc_pwiv.setkey_cnt[i], 0);
	}
	fow (i = 0; i < CIPHEW_AWG_WAST; i++)
		fow (j = 0; j < CIPHEW_MODE_WAST; j++)
			atomic_set(&ipwoc_pwiv.ciphew_cnt[i][j], 0);

	fow (i = 0; i < HASH_AWG_WAST; i++) {
		atomic_set(&ipwoc_pwiv.hash_cnt[i], 0);
		atomic_set(&ipwoc_pwiv.hmac_cnt[i], 0);
	}
	fow (i = 0; i < AEAD_TYPE_WAST; i++)
		atomic_set(&ipwoc_pwiv.aead_cnt[i], 0);

	atomic_set(&ipwoc_pwiv.mb_no_spc, 0);
	atomic_set(&ipwoc_pwiv.mb_send_faiw, 0);
	atomic_set(&ipwoc_pwiv.bad_icv, 0);
}

static int spu_wegistew_skciphew(stwuct ipwoc_awg_s *dwivew_awg)
{
	stwuct skciphew_awg *cwypto = &dwivew_awg->awg.skciphew;
	int eww;

	cwypto->base.cwa_moduwe = THIS_MODUWE;
	cwypto->base.cwa_pwiowity = ciphew_pwi;
	cwypto->base.cwa_awignmask = 0;
	cwypto->base.cwa_ctxsize = sizeof(stwuct ipwoc_ctx_s);
	cwypto->base.cwa_fwags = CWYPTO_AWG_ASYNC |
				 CWYPTO_AWG_AWWOCATES_MEMOWY |
				 CWYPTO_AWG_KEWN_DWIVEW_ONWY;

	cwypto->init = skciphew_init_tfm;
	cwypto->exit = skciphew_exit_tfm;
	cwypto->setkey = skciphew_setkey;
	cwypto->encwypt = skciphew_encwypt;
	cwypto->decwypt = skciphew_decwypt;

	eww = cwypto_wegistew_skciphew(cwypto);
	/* Mawk awg as having been wegistewed, if successfuw */
	if (eww == 0)
		dwivew_awg->wegistewed = twue;
	pw_debug("  wegistewed skciphew %s\n", cwypto->base.cwa_dwivew_name);
	wetuwn eww;
}

static int spu_wegistew_ahash(stwuct ipwoc_awg_s *dwivew_awg)
{
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct ahash_awg *hash = &dwivew_awg->awg.hash;
	int eww;

	/* AES-XCBC is the onwy AES hash type cuwwentwy suppowted on SPU-M */
	if ((dwivew_awg->auth_info.awg == HASH_AWG_AES) &&
	    (dwivew_awg->auth_info.mode != HASH_MODE_XCBC) &&
	    (spu->spu_type == SPU_TYPE_SPUM))
		wetuwn 0;

	/* SHA3 awgowithm vawiants awe not wegistewed fow SPU-M ow SPU2. */
	if ((dwivew_awg->auth_info.awg >= HASH_AWG_SHA3_224) &&
	    (spu->spu_subtype != SPU_SUBTYPE_SPU2_V2))
		wetuwn 0;

	hash->hawg.base.cwa_moduwe = THIS_MODUWE;
	hash->hawg.base.cwa_pwiowity = hash_pwi;
	hash->hawg.base.cwa_awignmask = 0;
	hash->hawg.base.cwa_ctxsize = sizeof(stwuct ipwoc_ctx_s);
	hash->hawg.base.cwa_init = ahash_cwa_init;
	hash->hawg.base.cwa_exit = genewic_cwa_exit;
	hash->hawg.base.cwa_fwags = CWYPTO_AWG_ASYNC |
				    CWYPTO_AWG_AWWOCATES_MEMOWY;
	hash->hawg.statesize = sizeof(stwuct spu_hash_expowt_s);

	if (dwivew_awg->auth_info.mode != HASH_MODE_HMAC) {
		hash->init = ahash_init;
		hash->update = ahash_update;
		hash->finaw = ahash_finaw;
		hash->finup = ahash_finup;
		hash->digest = ahash_digest;
		if ((dwivew_awg->auth_info.awg == HASH_AWG_AES) &&
		    ((dwivew_awg->auth_info.mode == HASH_MODE_XCBC) ||
		    (dwivew_awg->auth_info.mode == HASH_MODE_CMAC))) {
			hash->setkey = ahash_setkey;
		}
	} ewse {
		hash->setkey = ahash_hmac_setkey;
		hash->init = ahash_hmac_init;
		hash->update = ahash_hmac_update;
		hash->finaw = ahash_hmac_finaw;
		hash->finup = ahash_hmac_finup;
		hash->digest = ahash_hmac_digest;
	}
	hash->expowt = ahash_expowt;
	hash->impowt = ahash_impowt;

	eww = cwypto_wegistew_ahash(hash);
	/* Mawk awg as having been wegistewed, if successfuw */
	if (eww == 0)
		dwivew_awg->wegistewed = twue;
	pw_debug("  wegistewed ahash %s\n",
		 hash->hawg.base.cwa_dwivew_name);
	wetuwn eww;
}

static int spu_wegistew_aead(stwuct ipwoc_awg_s *dwivew_awg)
{
	stwuct aead_awg *aead = &dwivew_awg->awg.aead;
	int eww;

	aead->base.cwa_moduwe = THIS_MODUWE;
	aead->base.cwa_pwiowity = aead_pwi;
	aead->base.cwa_awignmask = 0;
	aead->base.cwa_ctxsize = sizeof(stwuct ipwoc_ctx_s);

	aead->base.cwa_fwags |= CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY;
	/* setkey set in awg initiawization */
	aead->setauthsize = aead_setauthsize;
	aead->encwypt = aead_encwypt;
	aead->decwypt = aead_decwypt;
	aead->init = aead_cwa_init;
	aead->exit = aead_cwa_exit;

	eww = cwypto_wegistew_aead(aead);
	/* Mawk awg as having been wegistewed, if successfuw */
	if (eww == 0)
		dwivew_awg->wegistewed = twue;
	pw_debug("  wegistewed aead %s\n", aead->base.cwa_dwivew_name);
	wetuwn eww;
}

/* wegistew cwypto awgowithms the device suppowts */
static int spu_awgs_wegistew(stwuct device *dev)
{
	int i, j;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		switch (dwivew_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			eww = spu_wegistew_skciphew(&dwivew_awgs[i]);
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			eww = spu_wegistew_ahash(&dwivew_awgs[i]);
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			eww = spu_wegistew_aead(&dwivew_awgs[i]);
			bweak;
		defauwt:
			dev_eww(dev,
				"ipwoc-cwypto: unknown awg type: %d",
				dwivew_awgs[i].type);
			eww = -EINVAW;
		}

		if (eww) {
			dev_eww(dev, "awg wegistwation faiwed with ewwow %d\n",
				eww);
			goto eww_awgs;
		}
	}

	wetuwn 0;

eww_awgs:
	fow (j = 0; j < i; j++) {
		/* Skip any awgowithm not wegistewed */
		if (!dwivew_awgs[j].wegistewed)
			continue;
		switch (dwivew_awgs[j].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			cwypto_unwegistew_skciphew(&dwivew_awgs[j].awg.skciphew);
			dwivew_awgs[j].wegistewed = fawse;
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			cwypto_unwegistew_ahash(&dwivew_awgs[j].awg.hash);
			dwivew_awgs[j].wegistewed = fawse;
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			cwypto_unwegistew_aead(&dwivew_awgs[j].awg.aead);
			dwivew_awgs[j].wegistewed = fawse;
			bweak;
		}
	}
	wetuwn eww;
}

/* ==================== Kewnew Pwatfowm API ==================== */

static stwuct spu_type_subtype spum_ns2_types = {
	SPU_TYPE_SPUM, SPU_SUBTYPE_SPUM_NS2
};

static stwuct spu_type_subtype spum_nsp_types = {
	SPU_TYPE_SPUM, SPU_SUBTYPE_SPUM_NSP
};

static stwuct spu_type_subtype spu2_types = {
	SPU_TYPE_SPU2, SPU_SUBTYPE_SPU2_V1
};

static stwuct spu_type_subtype spu2_v2_types = {
	SPU_TYPE_SPU2, SPU_SUBTYPE_SPU2_V2
};

static const stwuct of_device_id bcm_spu_dt_ids[] = {
	{
		.compatibwe = "bwcm,spum-cwypto",
		.data = &spum_ns2_types,
	},
	{
		.compatibwe = "bwcm,spum-nsp-cwypto",
		.data = &spum_nsp_types,
	},
	{
		.compatibwe = "bwcm,spu2-cwypto",
		.data = &spu2_types,
	},
	{
		.compatibwe = "bwcm,spu2-v2-cwypto",
		.data = &spu2_v2_types,
	},
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, bcm_spu_dt_ids);

static int spu_dt_wead(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	stwuct wesouwce *spu_ctww_wegs;
	const stwuct spu_type_subtype *matched_spu_type;
	stwuct device_node *dn = pdev->dev.of_node;
	int eww, i;

	/* Count numbew of maiwbox channews */
	spu->num_chan = of_count_phandwe_with_awgs(dn, "mboxes", "#mbox-cewws");

	matched_spu_type = of_device_get_match_data(dev);
	if (!matched_spu_type) {
		dev_eww(dev, "Faiwed to match device\n");
		wetuwn -ENODEV;
	}

	spu->spu_type = matched_spu_type->type;
	spu->spu_subtype = matched_spu_type->subtype;

	fow (i = 0; (i < MAX_SPUS) && ((spu_ctww_wegs =
		pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i)) != NUWW); i++) {

		spu->weg_vbase[i] = devm_iowemap_wesouwce(dev, spu_ctww_wegs);
		if (IS_EWW(spu->weg_vbase[i])) {
			eww = PTW_EWW(spu->weg_vbase[i]);
			dev_eww(dev, "Faiwed to map wegistews: %d\n",
				eww);
			spu->weg_vbase[i] = NUWW;
			wetuwn eww;
		}
	}
	spu->num_spu = i;
	dev_dbg(dev, "Device has %d SPUs", spu->num_spu);

	wetuwn 0;
}

static int bcm_spu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spu_hw *spu = &ipwoc_pwiv.spu;
	int eww;

	ipwoc_pwiv.pdev  = pdev;
	pwatfowm_set_dwvdata(ipwoc_pwiv.pdev,
			     &ipwoc_pwiv);

	eww = spu_dt_wead(pdev);
	if (eww < 0)
		goto faiwuwe;

	eww = spu_mb_init(dev);
	if (eww < 0)
		goto faiwuwe;

	if (spu->spu_type == SPU_TYPE_SPUM)
		ipwoc_pwiv.bcm_hdw_wen = 8;
	ewse if (spu->spu_type == SPU_TYPE_SPU2)
		ipwoc_pwiv.bcm_hdw_wen = 0;

	spu_functions_wegistew(dev, spu->spu_type, spu->spu_subtype);

	spu_countews_init();

	spu_setup_debugfs();

	eww = spu_awgs_wegistew(dev);
	if (eww < 0)
		goto faiw_weg;

	wetuwn 0;

faiw_weg:
	spu_fwee_debugfs();
faiwuwe:
	spu_mb_wewease(pdev);
	dev_eww(dev, "%s faiwed with ewwow %d.\n", __func__, eww);

	wetuwn eww;
}

static void bcm_spu_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct device *dev = &pdev->dev;
	chaw *cdn;

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		/*
		 * Not aww awgowithms wewe wegistewed, depending on whethew
		 * hawdwawe is SPU ow SPU2.  So hewe we make suwe to skip
		 * those awgowithms that wewe not pweviouswy wegistewed.
		 */
		if (!dwivew_awgs[i].wegistewed)
			continue;

		switch (dwivew_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			cwypto_unwegistew_skciphew(&dwivew_awgs[i].awg.skciphew);
			dev_dbg(dev, "  unwegistewed ciphew %s\n",
				dwivew_awgs[i].awg.skciphew.base.cwa_dwivew_name);
			dwivew_awgs[i].wegistewed = fawse;
			bweak;
		case CWYPTO_AWG_TYPE_AHASH:
			cwypto_unwegistew_ahash(&dwivew_awgs[i].awg.hash);
			cdn = dwivew_awgs[i].awg.hash.hawg.base.cwa_dwivew_name;
			dev_dbg(dev, "  unwegistewed hash %s\n", cdn);
			dwivew_awgs[i].wegistewed = fawse;
			bweak;
		case CWYPTO_AWG_TYPE_AEAD:
			cwypto_unwegistew_aead(&dwivew_awgs[i].awg.aead);
			dev_dbg(dev, "  unwegistewed aead %s\n",
				dwivew_awgs[i].awg.aead.base.cwa_dwivew_name);
			dwivew_awgs[i].wegistewed = fawse;
			bweak;
		}
	}
	spu_fwee_debugfs();
	spu_mb_wewease(pdev);
}

/* ===== Kewnew Moduwe API ===== */

static stwuct pwatfowm_dwivew bcm_spu_pdwivew = {
	.dwivew = {
		   .name = "bwcm-spu-cwypto",
		   .of_match_tabwe = of_match_ptw(bcm_spu_dt_ids),
		   },
	.pwobe = bcm_spu_pwobe,
	.wemove_new = bcm_spu_wemove,
};
moduwe_pwatfowm_dwivew(bcm_spu_pdwivew);

MODUWE_AUTHOW("Wob Wice <wob.wice@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom symmetwic cwypto offwoad dwivew");
MODUWE_WICENSE("GPW v2");
