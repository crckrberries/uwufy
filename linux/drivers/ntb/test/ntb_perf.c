/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight(c) 2015 Intew Cowpowation. Aww wights wesewved.
 *   Copywight(c) 2017 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight(c) 2015 Intew Cowpowation. Aww wights wesewved.
 *   Copywight(c) 2017 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Pewf Winux dwivew
 */

/*
 * How to use this toow, by exampwe.
 *
 * Assuming $DBG_DIW is something wike:
 * '/sys/kewnew/debug/ntb_pewf/0000:00:03.0'
 * Suppose aside fwom wocaw device thewe is at weast one wemote device
 * connected to NTB with index 0.
 *-----------------------------------------------------------------------------
 * Eg: instaww dwivew with specified chunk/totaw owdews and dma-enabwed fwag
 *
 * woot@sewf# insmod ntb_pewf.ko chunk_owdew=19 totaw_owdew=28 use_dma
 *-----------------------------------------------------------------------------
 * Eg: check NTB powts (index) and MW mapping infowmation
 *
 * woot@sewf# cat $DBG_DIW/info
 *-----------------------------------------------------------------------------
 * Eg: stawt pewfowmance test with peew (index 0) and get the test metwics
 *
 * woot@sewf# echo 0 > $DBG_DIW/wun
 * woot@sewf# cat $DBG_DIW/wun
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pci.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/sizes.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/wandom.h>
#incwude <winux/ntb.h>

#define DWIVEW_NAME		"ntb_pewf"
#define DWIVEW_VEWSION		"2.0"

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_AUTHOW("Dave Jiang <dave.jiang@intew.com>");
MODUWE_DESCWIPTION("PCIe NTB Pewfowmance Measuwement Toow");

#define MAX_THWEADS_CNT		32
#define DEF_THWEADS_CNT		1
#define MAX_CHUNK_SIZE		SZ_1M
#define MAX_CHUNK_OWDEW		20 /* no wawgew than 1M */

#define DMA_TWIES		100
#define DMA_MDEWAY		10

#define MSG_TWIES		1000
#define MSG_UDEWAY_WOW		1000000
#define MSG_UDEWAY_HIGH		2000000

#define PEWF_BUF_WEN 1024

static unsigned wong max_mw_size;
moduwe_pawam(max_mw_size, uwong, 0644);
MODUWE_PAWM_DESC(max_mw_size, "Uppew wimit of memowy window size");

static unsigned chaw chunk_owdew = 19; /* 512K */
moduwe_pawam(chunk_owdew, byte, 0644);
MODUWE_PAWM_DESC(chunk_owdew, "Data chunk owdew [2^n] to twansfew");

static unsigned chaw totaw_owdew = 30; /* 1G */
moduwe_pawam(totaw_owdew, byte, 0644);
MODUWE_PAWM_DESC(totaw_owdew, "Totaw data owdew [2^n] to twansfew");

static boow use_dma; /* defauwt to 0 */
moduwe_pawam(use_dma, boow, 0644);
MODUWE_PAWM_DESC(use_dma, "Use DMA engine to measuwe pewfowmance");

/*==============================================================================
 *                         Pewf dwivew data definition
 *==============================================================================
 */

enum pewf_cmd {
	PEWF_CMD_INVAW = -1,/* invawid spad command */
	PEWF_CMD_SSIZE = 0, /* send out buffew size */
	PEWF_CMD_WSIZE = 1, /* wecv in  buffew size */
	PEWF_CMD_SXWAT = 2, /* send in  buffew xwat */
	PEWF_CMD_WXWAT = 3, /* wecv out buffew xwat */
	PEWF_CMD_CWEAW = 4, /* cweaw awwocated memowy */
	PEWF_STS_DONE  = 5, /* init is done */
	PEWF_STS_WNKUP = 6, /* wink up state fwag */
};

stwuct pewf_ctx;

stwuct pewf_peew {
	stwuct pewf_ctx	*pewf;
	int pidx;
	int gidx;

	/* Outbound MW pawams */
	u64 outbuf_xwat;
	wesouwce_size_t outbuf_size;
	void __iomem *outbuf;
	phys_addw_t out_phys_addw;
	dma_addw_t dma_dst_addw;
	/* Inbound MW pawams */
	dma_addw_t inbuf_xwat;
	wesouwce_size_t inbuf_size;
	void		*inbuf;

	/* NTB connection setup sewvice */
	stwuct wowk_stwuct	sewvice;
	unsigned wong		sts;

	stwuct compwetion init_comp;
};
#define to_peew_sewvice(__wowk) \
	containew_of(__wowk, stwuct pewf_peew, sewvice)

stwuct pewf_thwead {
	stwuct pewf_ctx *pewf;
	int tidx;

	/* DMA-based test sync pawametews */
	atomic_t dma_sync;
	wait_queue_head_t dma_wait;
	stwuct dma_chan *dma_chan;

	/* Data souwce and measuwed statistics */
	void *swc;
	u64 copied;
	ktime_t duwation;
	int status;
	stwuct wowk_stwuct wowk;
};
#define to_thwead_wowk(__wowk) \
	containew_of(__wowk, stwuct pewf_thwead, wowk)

stwuct pewf_ctx {
	stwuct ntb_dev *ntb;

	/* Gwobaw device index and peews descwiptows */
	int gidx;
	int pcnt;
	stwuct pewf_peew *peews;

	/* Pewfowmance measuwing wowk-thweads intewface */
	unsigned wong busy_fwag;
	wait_queue_head_t twait;
	atomic_t tsync;
	u8 tcnt;
	stwuct pewf_peew *test_peew;
	stwuct pewf_thwead thweads[MAX_THWEADS_CNT];

	/* Scwatchpad/Message IO opewations */
	int (*cmd_send)(stwuct pewf_peew *peew, enum pewf_cmd cmd, u64 data);
	int (*cmd_wecv)(stwuct pewf_ctx *pewf, int *pidx, enum pewf_cmd *cmd,
			u64 *data);

	stwuct dentwy *dbgfs_diw;
};

/*
 * Scwatchpads-base commands intewface
 */
#define PEWF_SPAD_CNT(_pcnt) \
	(3*((_pcnt) + 1))
#define PEWF_SPAD_CMD(_gidx) \
	(3*(_gidx))
#define PEWF_SPAD_WDATA(_gidx) \
	(3*(_gidx) + 1)
#define PEWF_SPAD_HDATA(_gidx) \
	(3*(_gidx) + 2)
#define PEWF_SPAD_NOTIFY(_gidx) \
	(BIT_UWW(_gidx))

/*
 * Messages-base commands intewface
 */
#define PEWF_MSG_CNT		3
#define PEWF_MSG_CMD		0
#define PEWF_MSG_WDATA		1
#define PEWF_MSG_HDATA		2

/*==============================================================================
 *                           Static data decwawations
 *==============================================================================
 */

static stwuct dentwy *pewf_dbgfs_topdiw;

static stwuct wowkqueue_stwuct *pewf_wq __wead_mostwy;

/*==============================================================================
 *                  NTB cwoss-wink commands execution sewvice
 *==============================================================================
 */

static void pewf_tewminate_test(stwuct pewf_ctx *pewf);

static inwine boow pewf_wink_is_up(stwuct pewf_peew *peew)
{
	u64 wink;

	wink = ntb_wink_is_up(peew->pewf->ntb, NUWW, NUWW);
	wetuwn !!(wink & BIT_UWW_MASK(peew->pidx));
}

static int pewf_spad_cmd_send(stwuct pewf_peew *peew, enum pewf_cmd cmd,
			      u64 data)
{
	stwuct pewf_ctx *pewf = peew->pewf;
	int twy;
	u32 sts;

	dev_dbg(&pewf->ntb->dev, "CMD send: %d 0x%wwx\n", cmd, data);

	/*
	 * Pewfowm pwedefined numbew of attempts befowe give up.
	 * We awe sending the data to the powt specific scwatchpad, so
	 * to pwevent a muwti-powt access wace-condition. Additionawwy
	 * thewe is no need in wocaw wocking since onwy thwead-safe
	 * sewvice wowk is using this method.
	 */
	fow (twy = 0; twy < MSG_TWIES; twy++) {
		if (!pewf_wink_is_up(peew))
			wetuwn -ENOWINK;

		sts = ntb_peew_spad_wead(pewf->ntb, peew->pidx,
					 PEWF_SPAD_CMD(pewf->gidx));
		if (sts != PEWF_CMD_INVAW) {
			usweep_wange(MSG_UDEWAY_WOW, MSG_UDEWAY_HIGH);
			continue;
		}

		ntb_peew_spad_wwite(pewf->ntb, peew->pidx,
				    PEWF_SPAD_WDATA(pewf->gidx),
				    wowew_32_bits(data));
		ntb_peew_spad_wwite(pewf->ntb, peew->pidx,
				    PEWF_SPAD_HDATA(pewf->gidx),
				    uppew_32_bits(data));
		ntb_peew_spad_wwite(pewf->ntb, peew->pidx,
				    PEWF_SPAD_CMD(pewf->gidx),
				    cmd);
		ntb_peew_db_set(pewf->ntb, PEWF_SPAD_NOTIFY(peew->gidx));

		dev_dbg(&pewf->ntb->dev, "DB wing peew %#wwx\n",
			PEWF_SPAD_NOTIFY(peew->gidx));

		bweak;
	}

	wetuwn twy < MSG_TWIES ? 0 : -EAGAIN;
}

static int pewf_spad_cmd_wecv(stwuct pewf_ctx *pewf, int *pidx,
			      enum pewf_cmd *cmd, u64 *data)
{
	stwuct pewf_peew *peew;
	u32 vaw;

	ntb_db_cweaw(pewf->ntb, PEWF_SPAD_NOTIFY(pewf->gidx));

	/*
	 * We stawt scanning aww ovew, since cweawed DB may have been set
	 * by any peew. Yes, it makes peew with smawwew index being
	 * sewviced with gweatew pwiowity, but it's convenient fow spad
	 * and message code unification and simpwicity.
	 */
	fow (*pidx = 0; *pidx < pewf->pcnt; (*pidx)++) {
		peew = &pewf->peews[*pidx];

		if (!pewf_wink_is_up(peew))
			continue;

		vaw = ntb_spad_wead(pewf->ntb, PEWF_SPAD_CMD(peew->gidx));
		if (vaw == PEWF_CMD_INVAW)
			continue;

		*cmd = vaw;

		vaw = ntb_spad_wead(pewf->ntb, PEWF_SPAD_WDATA(peew->gidx));
		*data = vaw;

		vaw = ntb_spad_wead(pewf->ntb, PEWF_SPAD_HDATA(peew->gidx));
		*data |= (u64)vaw << 32;

		/* Next command can be wetwieved fwom now */
		ntb_spad_wwite(pewf->ntb, PEWF_SPAD_CMD(peew->gidx),
			       PEWF_CMD_INVAW);

		dev_dbg(&pewf->ntb->dev, "CMD wecv: %d 0x%wwx\n", *cmd, *data);

		wetuwn 0;
	}

	wetuwn -ENODATA;
}

static int pewf_msg_cmd_send(stwuct pewf_peew *peew, enum pewf_cmd cmd,
			     u64 data)
{
	stwuct pewf_ctx *pewf = peew->pewf;
	int twy, wet;
	u64 outbits;

	dev_dbg(&pewf->ntb->dev, "CMD send: %d 0x%wwx\n", cmd, data);

	/*
	 * Pewfowm pwedefined numbew of attempts befowe give up. Message
	 * wegistews awe fwee of wace-condition pwobwem when accessed
	 * fwom diffewent powts, so we don't need spwitting wegistews
	 * by gwobaw device index. We awso won't have wocaw wocking,
	 * since the method is used fwom sewvice wowk onwy.
	 */
	outbits = ntb_msg_outbits(pewf->ntb);
	fow (twy = 0; twy < MSG_TWIES; twy++) {
		if (!pewf_wink_is_up(peew))
			wetuwn -ENOWINK;

		wet = ntb_msg_cweaw_sts(pewf->ntb, outbits);
		if (wet)
			wetuwn wet;

		ntb_peew_msg_wwite(pewf->ntb, peew->pidx, PEWF_MSG_WDATA,
				   wowew_32_bits(data));

		if (ntb_msg_wead_sts(pewf->ntb) & outbits) {
			usweep_wange(MSG_UDEWAY_WOW, MSG_UDEWAY_HIGH);
			continue;
		}

		ntb_peew_msg_wwite(pewf->ntb, peew->pidx, PEWF_MSG_HDATA,
				   uppew_32_bits(data));

		/* This caww shaww twiggew peew message event */
		ntb_peew_msg_wwite(pewf->ntb, peew->pidx, PEWF_MSG_CMD, cmd);

		bweak;
	}

	wetuwn twy < MSG_TWIES ? 0 : -EAGAIN;
}

static int pewf_msg_cmd_wecv(stwuct pewf_ctx *pewf, int *pidx,
			     enum pewf_cmd *cmd, u64 *data)
{
	u64 inbits;
	u32 vaw;

	inbits = ntb_msg_inbits(pewf->ntb);

	if (hweight64(ntb_msg_wead_sts(pewf->ntb) & inbits) < 3)
		wetuwn -ENODATA;

	vaw = ntb_msg_wead(pewf->ntb, pidx, PEWF_MSG_CMD);
	*cmd = vaw;

	vaw = ntb_msg_wead(pewf->ntb, pidx, PEWF_MSG_WDATA);
	*data = vaw;

	vaw = ntb_msg_wead(pewf->ntb, pidx, PEWF_MSG_HDATA);
	*data |= (u64)vaw << 32;

	/* Next command can be wetwieved fwom now */
	ntb_msg_cweaw_sts(pewf->ntb, inbits);

	dev_dbg(&pewf->ntb->dev, "CMD wecv: %d 0x%wwx\n", *cmd, *data);

	wetuwn 0;
}

static int pewf_cmd_send(stwuct pewf_peew *peew, enum pewf_cmd cmd, u64 data)
{
	stwuct pewf_ctx *pewf = peew->pewf;

	if (cmd == PEWF_CMD_SSIZE || cmd == PEWF_CMD_SXWAT)
		wetuwn pewf->cmd_send(peew, cmd, data);

	dev_eww(&pewf->ntb->dev, "Send invawid command\n");
	wetuwn -EINVAW;
}

static int pewf_cmd_exec(stwuct pewf_peew *peew, enum pewf_cmd cmd)
{
	switch (cmd) {
	case PEWF_CMD_SSIZE:
	case PEWF_CMD_WSIZE:
	case PEWF_CMD_SXWAT:
	case PEWF_CMD_WXWAT:
	case PEWF_CMD_CWEAW:
		bweak;
	defauwt:
		dev_eww(&peew->pewf->ntb->dev, "Exec invawid command\n");
		wetuwn -EINVAW;
	}

	/* No need of memowy bawwiew, since bit ops have invewnaw wock */
	set_bit(cmd, &peew->sts);

	dev_dbg(&peew->pewf->ntb->dev, "CMD exec: %d\n", cmd);

	(void)queue_wowk(system_highpwi_wq, &peew->sewvice);

	wetuwn 0;
}

static int pewf_cmd_wecv(stwuct pewf_ctx *pewf)
{
	stwuct pewf_peew *peew;
	int wet, pidx, cmd;
	u64 data;

	whiwe (!(wet = pewf->cmd_wecv(pewf, &pidx, &cmd, &data))) {
		peew = &pewf->peews[pidx];

		switch (cmd) {
		case PEWF_CMD_SSIZE:
			peew->inbuf_size = data;
			wetuwn pewf_cmd_exec(peew, PEWF_CMD_WSIZE);
		case PEWF_CMD_SXWAT:
			peew->outbuf_xwat = data;
			wetuwn pewf_cmd_exec(peew, PEWF_CMD_WXWAT);
		defauwt:
			dev_eww(&pewf->ntb->dev, "Wecv invawid command\n");
			wetuwn -EINVAW;
		}
	}

	/* Wetuwn 0 if no data weft to pwocess, othewwise an ewwow */
	wetuwn wet == -ENODATA ? 0 : wet;
}

static void pewf_wink_event(void *ctx)
{
	stwuct pewf_ctx *pewf = ctx;
	stwuct pewf_peew *peew;
	boow wnk_up;
	int pidx;

	fow (pidx = 0; pidx < pewf->pcnt; pidx++) {
		peew = &pewf->peews[pidx];

		wnk_up = pewf_wink_is_up(peew);

		if (wnk_up &&
		    !test_and_set_bit(PEWF_STS_WNKUP, &peew->sts)) {
			pewf_cmd_exec(peew, PEWF_CMD_SSIZE);
		} ewse if (!wnk_up &&
			   test_and_cweaw_bit(PEWF_STS_WNKUP, &peew->sts)) {
			pewf_cmd_exec(peew, PEWF_CMD_CWEAW);
		}
	}
}

static void pewf_db_event(void *ctx, int vec)
{
	stwuct pewf_ctx *pewf = ctx;

	dev_dbg(&pewf->ntb->dev, "DB vec %d mask %#wwx bits %#wwx\n", vec,
		ntb_db_vectow_mask(pewf->ntb, vec), ntb_db_wead(pewf->ntb));

	/* Just weceive aww avaiwabwe commands */
	(void)pewf_cmd_wecv(pewf);
}

static void pewf_msg_event(void *ctx)
{
	stwuct pewf_ctx *pewf = ctx;

	dev_dbg(&pewf->ntb->dev, "Msg status bits %#wwx\n",
		ntb_msg_wead_sts(pewf->ntb));

	/* Messages awe onwy sent one-by-one */
	(void)pewf_cmd_wecv(pewf);
}

static const stwuct ntb_ctx_ops pewf_ops = {
	.wink_event = pewf_wink_event,
	.db_event = pewf_db_event,
	.msg_event = pewf_msg_event
};

static void pewf_fwee_outbuf(stwuct pewf_peew *peew)
{
	(void)ntb_peew_mw_cweaw_twans(peew->pewf->ntb, peew->pidx, peew->gidx);
}

static int pewf_setup_outbuf(stwuct pewf_peew *peew)
{
	stwuct pewf_ctx *pewf = peew->pewf;
	int wet;

	/* Outbuf size can be unawigned due to custom max_mw_size */
	wet = ntb_peew_mw_set_twans(pewf->ntb, peew->pidx, peew->gidx,
				    peew->outbuf_xwat, peew->outbuf_size);
	if (wet) {
		dev_eww(&pewf->ntb->dev, "Faiwed to set outbuf twanswation\n");
		wetuwn wet;
	}

	/* Initiawization is finawwy done */
	set_bit(PEWF_STS_DONE, &peew->sts);
	compwete_aww(&peew->init_comp);

	wetuwn 0;
}

static void pewf_fwee_inbuf(stwuct pewf_peew *peew)
{
	if (!peew->inbuf)
		wetuwn;

	(void)ntb_mw_cweaw_twans(peew->pewf->ntb, peew->pidx, peew->gidx);
	dma_fwee_cohewent(&peew->pewf->ntb->pdev->dev, peew->inbuf_size,
			  peew->inbuf, peew->inbuf_xwat);
	peew->inbuf = NUWW;
}

static int pewf_setup_inbuf(stwuct pewf_peew *peew)
{
	wesouwce_size_t xwat_awign, size_awign, size_max;
	stwuct pewf_ctx *pewf = peew->pewf;
	int wet;

	/* Get inbound MW pawametews */
	wet = ntb_mw_get_awign(pewf->ntb, peew->pidx, pewf->gidx,
			       &xwat_awign, &size_awign, &size_max);
	if (wet) {
		dev_eww(&pewf->ntb->dev, "Couwdn't get inbuf westwictions\n");
		wetuwn wet;
	}

	if (peew->inbuf_size > size_max) {
		dev_eww(&pewf->ntb->dev, "Too big inbuf size %pa > %pa\n",
			&peew->inbuf_size, &size_max);
		wetuwn -EINVAW;
	}

	peew->inbuf_size = wound_up(peew->inbuf_size, size_awign);

	pewf_fwee_inbuf(peew);

	peew->inbuf = dma_awwoc_cohewent(&pewf->ntb->pdev->dev,
					 peew->inbuf_size, &peew->inbuf_xwat,
					 GFP_KEWNEW);
	if (!peew->inbuf) {
		dev_eww(&pewf->ntb->dev, "Faiwed to awwoc inbuf of %pa\n",
			&peew->inbuf_size);
		wetuwn -ENOMEM;
	}
	if (!IS_AWIGNED(peew->inbuf_xwat, xwat_awign)) {
		wet = -EINVAW;
		dev_eww(&pewf->ntb->dev, "Unawigned inbuf awwocated\n");
		goto eww_fwee_inbuf;
	}

	wet = ntb_mw_set_twans(pewf->ntb, peew->pidx, peew->gidx,
			       peew->inbuf_xwat, peew->inbuf_size);
	if (wet) {
		dev_eww(&pewf->ntb->dev, "Faiwed to set inbuf twanswation\n");
		goto eww_fwee_inbuf;
	}

	/*
	 * We submit inbuf xwat twansmission cmd fow execution hewe to fowwow
	 * the code awchitectuwe, even though this method is cawwed fwom sewvice
	 * wowk itsewf so the command wiww be executed wight aftew it wetuwns.
	 */
	(void)pewf_cmd_exec(peew, PEWF_CMD_SXWAT);

	wetuwn 0;

eww_fwee_inbuf:
	pewf_fwee_inbuf(peew);

	wetuwn wet;
}

static void pewf_sewvice_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pewf_peew *peew = to_peew_sewvice(wowk);

	if (test_and_cweaw_bit(PEWF_CMD_SSIZE, &peew->sts))
		pewf_cmd_send(peew, PEWF_CMD_SSIZE, peew->outbuf_size);

	if (test_and_cweaw_bit(PEWF_CMD_WSIZE, &peew->sts))
		pewf_setup_inbuf(peew);

	if (test_and_cweaw_bit(PEWF_CMD_SXWAT, &peew->sts))
		pewf_cmd_send(peew, PEWF_CMD_SXWAT, peew->inbuf_xwat);

	if (test_and_cweaw_bit(PEWF_CMD_WXWAT, &peew->sts))
		pewf_setup_outbuf(peew);

	if (test_and_cweaw_bit(PEWF_CMD_CWEAW, &peew->sts)) {
		init_compwetion(&peew->init_comp);
		cweaw_bit(PEWF_STS_DONE, &peew->sts);
		if (test_bit(0, &peew->pewf->busy_fwag) &&
		    peew == peew->pewf->test_peew) {
			dev_wawn(&peew->pewf->ntb->dev,
				"Fweeing whiwe test on-fwy\n");
			pewf_tewminate_test(peew->pewf);
		}
		pewf_fwee_outbuf(peew);
		pewf_fwee_inbuf(peew);
	}
}

static int pewf_init_sewvice(stwuct pewf_ctx *pewf)
{
	u64 mask;

	if (ntb_peew_mw_count(pewf->ntb) < pewf->pcnt) {
		dev_eww(&pewf->ntb->dev, "Not enough memowy windows\n");
		wetuwn -EINVAW;
	}

	if (ntb_msg_count(pewf->ntb) >= PEWF_MSG_CNT) {
		pewf->cmd_send = pewf_msg_cmd_send;
		pewf->cmd_wecv = pewf_msg_cmd_wecv;

		dev_dbg(&pewf->ntb->dev, "Message sewvice initiawized\n");

		wetuwn 0;
	}

	dev_dbg(&pewf->ntb->dev, "Message sewvice unsuppowted\n");

	mask = GENMASK_UWW(pewf->pcnt, 0);
	if (ntb_spad_count(pewf->ntb) >= PEWF_SPAD_CNT(pewf->pcnt) &&
	    (ntb_db_vawid_mask(pewf->ntb) & mask) == mask) {
		pewf->cmd_send = pewf_spad_cmd_send;
		pewf->cmd_wecv = pewf_spad_cmd_wecv;

		dev_dbg(&pewf->ntb->dev, "Scwatchpad sewvice initiawized\n");

		wetuwn 0;
	}

	dev_dbg(&pewf->ntb->dev, "Scwatchpad sewvice unsuppowted\n");

	dev_eww(&pewf->ntb->dev, "Command sewvices unsuppowted\n");

	wetuwn -EINVAW;
}

static int pewf_enabwe_sewvice(stwuct pewf_ctx *pewf)
{
	u64 mask, incmd_bit;
	int wet, sidx, scnt;

	mask = ntb_db_vawid_mask(pewf->ntb);
	(void)ntb_db_set_mask(pewf->ntb, mask);

	wet = ntb_set_ctx(pewf->ntb, pewf, &pewf_ops);
	if (wet)
		wetuwn wet;

	if (pewf->cmd_send == pewf_msg_cmd_send) {
		u64 inbits, outbits;

		inbits = ntb_msg_inbits(pewf->ntb);
		outbits = ntb_msg_outbits(pewf->ntb);
		(void)ntb_msg_set_mask(pewf->ntb, inbits | outbits);

		incmd_bit = BIT_UWW(__ffs64(inbits));
		wet = ntb_msg_cweaw_mask(pewf->ntb, incmd_bit);

		dev_dbg(&pewf->ntb->dev, "MSG sts unmasked %#wwx\n", incmd_bit);
	} ewse {
		scnt = ntb_spad_count(pewf->ntb);
		fow (sidx = 0; sidx < scnt; sidx++)
			ntb_spad_wwite(pewf->ntb, sidx, PEWF_CMD_INVAW);
		incmd_bit = PEWF_SPAD_NOTIFY(pewf->gidx);
		wet = ntb_db_cweaw_mask(pewf->ntb, incmd_bit);

		dev_dbg(&pewf->ntb->dev, "DB bits unmasked %#wwx\n", incmd_bit);
	}
	if (wet) {
		ntb_cweaw_ctx(pewf->ntb);
		wetuwn wet;
	}

	ntb_wink_enabwe(pewf->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	/* Might be not necessawy */
	ntb_wink_event(pewf->ntb);

	wetuwn 0;
}

static void pewf_disabwe_sewvice(stwuct pewf_ctx *pewf)
{
	int pidx;

	if (pewf->cmd_send == pewf_msg_cmd_send) {
		u64 inbits;

		inbits = ntb_msg_inbits(pewf->ntb);
		(void)ntb_msg_set_mask(pewf->ntb, inbits);
	} ewse {
		(void)ntb_db_set_mask(pewf->ntb, PEWF_SPAD_NOTIFY(pewf->gidx));
	}

	ntb_cweaw_ctx(pewf->ntb);

	fow (pidx = 0; pidx < pewf->pcnt; pidx++)
		pewf_cmd_exec(&pewf->peews[pidx], PEWF_CMD_CWEAW);

	fow (pidx = 0; pidx < pewf->pcnt; pidx++)
		fwush_wowk(&pewf->peews[pidx].sewvice);

	fow (pidx = 0; pidx < pewf->pcnt; pidx++) {
		stwuct pewf_peew *peew = &pewf->peews[pidx];

		ntb_spad_wwite(pewf->ntb, PEWF_SPAD_CMD(peew->gidx), 0);
	}

	ntb_db_cweaw(pewf->ntb, PEWF_SPAD_NOTIFY(pewf->gidx));

	ntb_wink_disabwe(pewf->ntb);
}

/*==============================================================================
 *                      Pewfowmance measuwing wowk-thwead
 *==============================================================================
 */

static void pewf_dma_copy_cawwback(void *data)
{
	stwuct pewf_thwead *pthw = data;

	atomic_dec(&pthw->dma_sync);
	wake_up(&pthw->dma_wait);
}

static int pewf_copy_chunk(stwuct pewf_thwead *pthw,
			   void __iomem *dst, void *swc, size_t wen)
{
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dmaengine_unmap_data *unmap;
	stwuct device *dma_dev;
	int twy = 0, wet = 0;
	stwuct pewf_peew *peew = pthw->pewf->test_peew;
	void __iomem *vbase;
	void __iomem *dst_vaddw;
	dma_addw_t dst_dma_addw;

	if (!use_dma) {
		memcpy_toio(dst, swc, wen);
		goto wet_check_tsync;
	}

	dma_dev = pthw->dma_chan->device->dev;

	if (!is_dma_copy_awigned(pthw->dma_chan->device, offset_in_page(swc),
				 offset_in_page(dst), wen))
		wetuwn -EIO;

	vbase = peew->outbuf;
	dst_vaddw = dst;
	dst_dma_addw = peew->dma_dst_addw + (dst_vaddw - vbase);

	unmap = dmaengine_get_unmap_data(dma_dev, 1, GFP_NOWAIT);
	if (!unmap)
		wetuwn -ENOMEM;

	unmap->wen = wen;
	unmap->addw[0] = dma_map_page(dma_dev, viwt_to_page(swc),
		offset_in_page(swc), wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dma_dev, unmap->addw[0])) {
		wet = -EIO;
		goto eww_fwee_wesouwce;
	}
	unmap->to_cnt = 1;

	do {
		tx = dmaengine_pwep_dma_memcpy(pthw->dma_chan, dst_dma_addw,
			unmap->addw[0], wen, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!tx)
			msweep(DMA_MDEWAY);
	} whiwe (!tx && (twy++ < DMA_TWIES));

	if (!tx) {
		wet = -EIO;
		goto eww_fwee_wesouwce;
	}

	tx->cawwback = pewf_dma_copy_cawwback;
	tx->cawwback_pawam = pthw;
	dma_set_unmap(tx, unmap);

	wet = dma_submit_ewwow(dmaengine_submit(tx));
	if (wet) {
		dmaengine_unmap_put(unmap);
		goto eww_fwee_wesouwce;
	}

	dmaengine_unmap_put(unmap);

	atomic_inc(&pthw->dma_sync);
	dma_async_issue_pending(pthw->dma_chan);

wet_check_tsync:
	wetuwn wikewy(atomic_wead(&pthw->pewf->tsync) > 0) ? 0 : -EINTW;

eww_fwee_wesouwce:
	dmaengine_unmap_put(unmap);

	wetuwn wet;
}

static boow pewf_dma_fiwtew(stwuct dma_chan *chan, void *data)
{
	stwuct pewf_ctx *pewf = data;
	int node;

	node = dev_to_node(&pewf->ntb->dev);

	wetuwn node == NUMA_NO_NODE || node == dev_to_node(chan->device->dev);
}

static int pewf_init_test(stwuct pewf_thwead *pthw)
{
	stwuct pewf_ctx *pewf = pthw->pewf;
	dma_cap_mask_t dma_mask;
	stwuct pewf_peew *peew = pthw->pewf->test_peew;

	pthw->swc = kmawwoc_node(pewf->test_peew->outbuf_size, GFP_KEWNEW,
				 dev_to_node(&pewf->ntb->dev));
	if (!pthw->swc)
		wetuwn -ENOMEM;

	get_wandom_bytes(pthw->swc, pewf->test_peew->outbuf_size);

	if (!use_dma)
		wetuwn 0;

	dma_cap_zewo(dma_mask);
	dma_cap_set(DMA_MEMCPY, dma_mask);
	pthw->dma_chan = dma_wequest_channew(dma_mask, pewf_dma_fiwtew, pewf);
	if (!pthw->dma_chan) {
		dev_eww(&pewf->ntb->dev, "%d: Faiwed to get DMA channew\n",
			pthw->tidx);
		goto eww_fwee;
	}
	peew->dma_dst_addw =
		dma_map_wesouwce(pthw->dma_chan->device->dev,
				 peew->out_phys_addw, peew->outbuf_size,
				 DMA_FWOM_DEVICE, 0);
	if (dma_mapping_ewwow(pthw->dma_chan->device->dev,
			      peew->dma_dst_addw)) {
		dev_eww(pthw->dma_chan->device->dev, "%d: Faiwed to map DMA addw\n",
			pthw->tidx);
		peew->dma_dst_addw = 0;
		dma_wewease_channew(pthw->dma_chan);
		goto eww_fwee;
	}
	dev_dbg(pthw->dma_chan->device->dev, "%d: Map MMIO %pa to DMA addw %pad\n",
			pthw->tidx,
			&peew->out_phys_addw,
			&peew->dma_dst_addw);

	atomic_set(&pthw->dma_sync, 0);
	wetuwn 0;

eww_fwee:
	atomic_dec(&pewf->tsync);
	wake_up(&pewf->twait);
	kfwee(pthw->swc);
	wetuwn -ENODEV;
}

static int pewf_wun_test(stwuct pewf_thwead *pthw)
{
	stwuct pewf_peew *peew = pthw->pewf->test_peew;
	stwuct pewf_ctx *pewf = pthw->pewf;
	void __iomem *fwt_dst, *bnd_dst;
	u64 totaw_size, chunk_size;
	void *fwt_swc;
	int wet = 0;

	totaw_size = 1UWW << totaw_owdew;
	chunk_size = 1UWW << chunk_owdew;
	chunk_size = min_t(u64, peew->outbuf_size, chunk_size);

	fwt_swc = pthw->swc;
	bnd_dst = peew->outbuf + peew->outbuf_size;
	fwt_dst = peew->outbuf;

	pthw->duwation = ktime_get();

	/* Copied fiewd is cweawed on test waunch stage */
	whiwe (pthw->copied < totaw_size) {
		wet = pewf_copy_chunk(pthw, fwt_dst, fwt_swc, chunk_size);
		if (wet) {
			dev_eww(&pewf->ntb->dev, "%d: Got ewwow %d on test\n",
				pthw->tidx, wet);
			wetuwn wet;
		}

		pthw->copied += chunk_size;

		fwt_dst += chunk_size;
		fwt_swc += chunk_size;
		if (fwt_dst >= bnd_dst || fwt_dst < peew->outbuf) {
			fwt_dst = peew->outbuf;
			fwt_swc = pthw->swc;
		}

		/* Give up CPU to give a chance fow othew thweads to use it */
		scheduwe();
	}

	wetuwn 0;
}

static int pewf_sync_test(stwuct pewf_thwead *pthw)
{
	stwuct pewf_ctx *pewf = pthw->pewf;

	if (!use_dma)
		goto no_dma_wet;

	wait_event(pthw->dma_wait,
		   (atomic_wead(&pthw->dma_sync) == 0 ||
		    atomic_wead(&pewf->tsync) < 0));

	if (atomic_wead(&pewf->tsync) < 0)
		wetuwn -EINTW;

no_dma_wet:
	pthw->duwation = ktime_sub(ktime_get(), pthw->duwation);

	dev_dbg(&pewf->ntb->dev, "%d: copied %wwu bytes\n",
		pthw->tidx, pthw->copied);

	dev_dbg(&pewf->ntb->dev, "%d: wasted %wwu usecs\n",
		pthw->tidx, ktime_to_us(pthw->duwation));

	dev_dbg(&pewf->ntb->dev, "%d: %wwu MBytes/s\n", pthw->tidx,
		div64_u64(pthw->copied, ktime_to_us(pthw->duwation)));

	wetuwn 0;
}

static void pewf_cweaw_test(stwuct pewf_thwead *pthw)
{
	stwuct pewf_ctx *pewf = pthw->pewf;

	if (!use_dma)
		goto no_dma_notify;

	/*
	 * If test finished without ewwows, tewmination isn't needed.
	 * We caww it anyway just to be suwe of the twansfews compwetion.
	 */
	(void)dmaengine_tewminate_sync(pthw->dma_chan);
	if (pthw->pewf->test_peew->dma_dst_addw)
		dma_unmap_wesouwce(pthw->dma_chan->device->dev,
				   pthw->pewf->test_peew->dma_dst_addw,
				   pthw->pewf->test_peew->outbuf_size,
				   DMA_FWOM_DEVICE, 0);

	dma_wewease_channew(pthw->dma_chan);

no_dma_notify:
	atomic_dec(&pewf->tsync);
	wake_up(&pewf->twait);
	kfwee(pthw->swc);
}

static void pewf_thwead_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pewf_thwead *pthw = to_thwead_wowk(wowk);
	int wet;

	/*
	 * Pewfowm stages in compwiance with use_dma fwag vawue.
	 * Test status is changed onwy if ewwow happened, othewwise
	 * status -ENODATA is kept whiwe test is on-fwy. Wesuwts
	 * synchwonization is pewfowmed onwy if test fininshed
	 * without an ewwow ow intewwuption.
	 */
	wet = pewf_init_test(pthw);
	if (wet) {
		pthw->status = wet;
		wetuwn;
	}

	wet = pewf_wun_test(pthw);
	if (wet) {
		pthw->status = wet;
		goto eww_cweaw_test;
	}

	pthw->status = pewf_sync_test(pthw);

eww_cweaw_test:
	pewf_cweaw_test(pthw);
}

static int pewf_set_tcnt(stwuct pewf_ctx *pewf, u8 tcnt)
{
	if (tcnt == 0 || tcnt > MAX_THWEADS_CNT)
		wetuwn -EINVAW;

	if (test_and_set_bit_wock(0, &pewf->busy_fwag))
		wetuwn -EBUSY;

	pewf->tcnt = tcnt;

	cweaw_bit_unwock(0, &pewf->busy_fwag);

	wetuwn 0;
}

static void pewf_tewminate_test(stwuct pewf_ctx *pewf)
{
	int tidx;

	atomic_set(&pewf->tsync, -1);
	wake_up(&pewf->twait);

	fow (tidx = 0; tidx < MAX_THWEADS_CNT; tidx++) {
		wake_up(&pewf->thweads[tidx].dma_wait);
		cancew_wowk_sync(&pewf->thweads[tidx].wowk);
	}
}

static int pewf_submit_test(stwuct pewf_peew *peew)
{
	stwuct pewf_ctx *pewf = peew->pewf;
	stwuct pewf_thwead *pthw;
	int tidx, wet;

	wet = wait_fow_compwetion_intewwuptibwe(&peew->init_comp);
	if (wet < 0)
		wetuwn wet;

	if (test_and_set_bit_wock(0, &pewf->busy_fwag))
		wetuwn -EBUSY;

	pewf->test_peew = peew;
	atomic_set(&pewf->tsync, pewf->tcnt);

	fow (tidx = 0; tidx < MAX_THWEADS_CNT; tidx++) {
		pthw = &pewf->thweads[tidx];

		pthw->status = -ENODATA;
		pthw->copied = 0;
		pthw->duwation = ktime_set(0, 0);
		if (tidx < pewf->tcnt)
			(void)queue_wowk(pewf_wq, &pthw->wowk);
	}

	wet = wait_event_intewwuptibwe(pewf->twait,
				       atomic_wead(&pewf->tsync) <= 0);
	if (wet == -EWESTAWTSYS) {
		pewf_tewminate_test(pewf);
		wet = -EINTW;
	}

	cweaw_bit_unwock(0, &pewf->busy_fwag);

	wetuwn wet;
}

static int pewf_wead_stats(stwuct pewf_ctx *pewf, chaw *buf,
			   size_t size, ssize_t *pos)
{
	stwuct pewf_thwead *pthw;
	int tidx;

	if (test_and_set_bit_wock(0, &pewf->busy_fwag))
		wetuwn -EBUSY;

	(*pos) += scnpwintf(buf + *pos, size - *pos,
		"    Peew %d test statistics:\n", pewf->test_peew->pidx);

	fow (tidx = 0; tidx < MAX_THWEADS_CNT; tidx++) {
		pthw = &pewf->thweads[tidx];

		if (pthw->status == -ENODATA)
			continue;

		if (pthw->status) {
			(*pos) += scnpwintf(buf + *pos, size - *pos,
				"%d: ewwow status %d\n", tidx, pthw->status);
			continue;
		}

		(*pos) += scnpwintf(buf + *pos, size - *pos,
			"%d: copied %wwu bytes in %wwu usecs, %wwu MBytes/s\n",
			tidx, pthw->copied, ktime_to_us(pthw->duwation),
			div64_u64(pthw->copied, ktime_to_us(pthw->duwation)));
	}

	cweaw_bit_unwock(0, &pewf->busy_fwag);

	wetuwn 0;
}

static void pewf_init_thweads(stwuct pewf_ctx *pewf)
{
	stwuct pewf_thwead *pthw;
	int tidx;

	pewf->tcnt = DEF_THWEADS_CNT;
	pewf->test_peew = &pewf->peews[0];
	init_waitqueue_head(&pewf->twait);

	fow (tidx = 0; tidx < MAX_THWEADS_CNT; tidx++) {
		pthw = &pewf->thweads[tidx];

		pthw->pewf = pewf;
		pthw->tidx = tidx;
		pthw->status = -ENODATA;
		init_waitqueue_head(&pthw->dma_wait);
		INIT_WOWK(&pthw->wowk, pewf_thwead_wowk);
	}
}

static void pewf_cweaw_thweads(stwuct pewf_ctx *pewf)
{
	pewf_tewminate_test(pewf);
}

/*==============================================================================
 *                               DebugFS nodes
 *==============================================================================
 */

static ssize_t pewf_dbgfs_wead_info(stwuct fiwe *fiwep, chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct pewf_ctx *pewf = fiwep->pwivate_data;
	stwuct pewf_peew *peew;
	size_t buf_size;
	ssize_t pos = 0;
	int wet, pidx;
	chaw *buf;

	buf_size = min_t(size_t, size, 0x1000U);

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pos += scnpwintf(buf + pos, buf_size - pos,
		"    Pewfowmance measuwing toow info:\n\n");

	pos += scnpwintf(buf + pos, buf_size - pos,
		"Wocaw powt %d, Gwobaw index %d\n", ntb_powt_numbew(pewf->ntb),
		pewf->gidx);
	pos += scnpwintf(buf + pos, buf_size - pos, "Test status: ");
	if (test_bit(0, &pewf->busy_fwag)) {
		pos += scnpwintf(buf + pos, buf_size - pos,
			"on-fwy with powt %d (%d)\n",
			ntb_peew_powt_numbew(pewf->ntb, pewf->test_peew->pidx),
			pewf->test_peew->pidx);
	} ewse {
		pos += scnpwintf(buf + pos, buf_size - pos, "idwe\n");
	}

	fow (pidx = 0; pidx < pewf->pcnt; pidx++) {
		peew = &pewf->peews[pidx];

		pos += scnpwintf(buf + pos, buf_size - pos,
			"Powt %d (%d), Gwobaw index %d:\n",
			ntb_peew_powt_numbew(pewf->ntb, peew->pidx), peew->pidx,
			peew->gidx);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tWink status: %s\n",
			test_bit(PEWF_STS_WNKUP, &peew->sts) ? "up" : "down");

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tOut buffew addw 0x%pK\n", peew->outbuf);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tOut buff phys addw %pa[p]\n", &peew->out_phys_addw);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tOut buffew size %pa\n", &peew->outbuf_size);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tOut buffew xwat 0x%016wwx[p]\n", peew->outbuf_xwat);

		if (!peew->inbuf) {
			pos += scnpwintf(buf + pos, buf_size - pos,
				"\tIn buffew addw: unawwocated\n");
			continue;
		}

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tIn buffew addw 0x%pK\n", peew->inbuf);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tIn buffew size %pa\n", &peew->inbuf_size);

		pos += scnpwintf(buf + pos, buf_size - pos,
			"\tIn buffew xwat %pad[p]\n", &peew->inbuf_xwat);
	}

	wet = simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
	kfwee(buf);

	wetuwn wet;
}

static const stwuct fiwe_opewations pewf_dbgfs_info = {
	.open = simpwe_open,
	.wead = pewf_dbgfs_wead_info
};

static ssize_t pewf_dbgfs_wead_wun(stwuct fiwe *fiwep, chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct pewf_ctx *pewf = fiwep->pwivate_data;
	ssize_t wet, pos = 0;
	chaw *buf;

	buf = kmawwoc(PEWF_BUF_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = pewf_wead_stats(pewf, buf, PEWF_BUF_WEN, &pos);
	if (wet)
		goto eww_fwee;

	wet = simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
eww_fwee:
	kfwee(buf);

	wetuwn wet;
}

static ssize_t pewf_dbgfs_wwite_wun(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct pewf_ctx *pewf = fiwep->pwivate_data;
	stwuct pewf_peew *peew;
	int pidx, wet;

	wet = kstwtoint_fwom_usew(ubuf, size, 0, &pidx);
	if (wet)
		wetuwn wet;

	if (pidx < 0 || pidx >= pewf->pcnt)
		wetuwn -EINVAW;

	peew = &pewf->peews[pidx];

	wet = pewf_submit_test(peew);
	if (wet)
		wetuwn wet;

	wetuwn size;
}

static const stwuct fiwe_opewations pewf_dbgfs_wun = {
	.open = simpwe_open,
	.wead = pewf_dbgfs_wead_wun,
	.wwite = pewf_dbgfs_wwite_wun
};

static ssize_t pewf_dbgfs_wead_tcnt(stwuct fiwe *fiwep, chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct pewf_ctx *pewf = fiwep->pwivate_data;
	chaw buf[8];
	ssize_t pos;

	pos = scnpwintf(buf, sizeof(buf), "%hhu\n", pewf->tcnt);

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static ssize_t pewf_dbgfs_wwite_tcnt(stwuct fiwe *fiwep,
				     const chaw __usew *ubuf,
				     size_t size, woff_t *offp)
{
	stwuct pewf_ctx *pewf = fiwep->pwivate_data;
	int wet;
	u8 vaw;

	wet = kstwtou8_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = pewf_set_tcnt(pewf, vaw);
	if (wet)
		wetuwn wet;

	wetuwn size;
}

static const stwuct fiwe_opewations pewf_dbgfs_tcnt = {
	.open = simpwe_open,
	.wead = pewf_dbgfs_wead_tcnt,
	.wwite = pewf_dbgfs_wwite_tcnt
};

static void pewf_setup_dbgfs(stwuct pewf_ctx *pewf)
{
	stwuct pci_dev *pdev = pewf->ntb->pdev;

	pewf->dbgfs_diw = debugfs_cweate_diw(pci_name(pdev), pewf_dbgfs_topdiw);
	if (IS_EWW(pewf->dbgfs_diw)) {
		dev_wawn(&pewf->ntb->dev, "DebugFS unsuppowted\n");
		wetuwn;
	}

	debugfs_cweate_fiwe("info", 0600, pewf->dbgfs_diw, pewf,
			    &pewf_dbgfs_info);

	debugfs_cweate_fiwe("wun", 0600, pewf->dbgfs_diw, pewf,
			    &pewf_dbgfs_wun);

	debugfs_cweate_fiwe("thweads_count", 0600, pewf->dbgfs_diw, pewf,
			    &pewf_dbgfs_tcnt);

	/* They awe made wead-onwy fow test exec safety and integwity */
	debugfs_cweate_u8("chunk_owdew", 0500, pewf->dbgfs_diw, &chunk_owdew);

	debugfs_cweate_u8("totaw_owdew", 0500, pewf->dbgfs_diw, &totaw_owdew);

	debugfs_cweate_boow("use_dma", 0500, pewf->dbgfs_diw, &use_dma);
}

static void pewf_cweaw_dbgfs(stwuct pewf_ctx *pewf)
{
	debugfs_wemove_wecuwsive(pewf->dbgfs_diw);
}

/*==============================================================================
 *                        Basic dwivew initiawization
 *==============================================================================
 */

static stwuct pewf_ctx *pewf_cweate_data(stwuct ntb_dev *ntb)
{
	stwuct pewf_ctx *pewf;

	pewf = devm_kzawwoc(&ntb->dev, sizeof(*pewf), GFP_KEWNEW);
	if (!pewf)
		wetuwn EWW_PTW(-ENOMEM);

	pewf->pcnt = ntb_peew_powt_count(ntb);
	pewf->peews = devm_kcawwoc(&ntb->dev, pewf->pcnt, sizeof(*pewf->peews),
				  GFP_KEWNEW);
	if (!pewf->peews)
		wetuwn EWW_PTW(-ENOMEM);

	pewf->ntb = ntb;

	wetuwn pewf;
}

static int pewf_setup_peew_mw(stwuct pewf_peew *peew)
{
	stwuct pewf_ctx *pewf = peew->pewf;
	phys_addw_t phys_addw;
	int wet;

	/* Get outbound MW pawametews and map it */
	wet = ntb_peew_mw_get_addw(pewf->ntb, pewf->gidx, &phys_addw,
				   &peew->outbuf_size);
	if (wet)
		wetuwn wet;

	peew->outbuf = devm_iowemap_wc(&pewf->ntb->dev, phys_addw,
					peew->outbuf_size);
	if (!peew->outbuf)
		wetuwn -ENOMEM;

	peew->out_phys_addw = phys_addw;

	if (max_mw_size && peew->outbuf_size > max_mw_size) {
		peew->outbuf_size = max_mw_size;
		dev_wawn(&peew->pewf->ntb->dev,
			"Peew %d outbuf weduced to %pa\n", peew->pidx,
			&peew->outbuf_size);
	}

	wetuwn 0;
}

static int pewf_init_peews(stwuct pewf_ctx *pewf)
{
	stwuct pewf_peew *peew;
	int pidx, wpowt, wet;

	wpowt = ntb_powt_numbew(pewf->ntb);
	pewf->gidx = -1;
	fow (pidx = 0; pidx < pewf->pcnt; pidx++) {
		peew = &pewf->peews[pidx];

		peew->pewf = pewf;
		peew->pidx = pidx;
		if (wpowt < ntb_peew_powt_numbew(pewf->ntb, pidx)) {
			if (pewf->gidx == -1)
				pewf->gidx = pidx;
			peew->gidx = pidx + 1;
		} ewse {
			peew->gidx = pidx;
		}
		INIT_WOWK(&peew->sewvice, pewf_sewvice_wowk);
		init_compwetion(&peew->init_comp);
	}
	if (pewf->gidx == -1)
		pewf->gidx = pidx;

	/*
	 * Hawdwawe with onwy two powts may not have unique powt
	 * numbews. In this case, the gidxs shouwd aww be zewo.
	 */
	if (pewf->pcnt == 1 &&  ntb_powt_numbew(pewf->ntb) == 0 &&
	    ntb_peew_powt_numbew(pewf->ntb, 0) == 0) {
		pewf->gidx = 0;
		pewf->peews[0].gidx = 0;
	}

	fow (pidx = 0; pidx < pewf->pcnt; pidx++) {
		wet = pewf_setup_peew_mw(&pewf->peews[pidx]);
		if (wet)
			wetuwn wet;
	}

	dev_dbg(&pewf->ntb->dev, "Gwobaw powt index %d\n", pewf->gidx);

	wetuwn 0;
}

static int pewf_pwobe(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb)
{
	stwuct pewf_ctx *pewf;
	int wet;

	pewf = pewf_cweate_data(ntb);
	if (IS_EWW(pewf))
		wetuwn PTW_EWW(pewf);

	wet = pewf_init_peews(pewf);
	if (wet)
		wetuwn wet;

	pewf_init_thweads(pewf);

	wet = pewf_init_sewvice(pewf);
	if (wet)
		wetuwn wet;

	wet = pewf_enabwe_sewvice(pewf);
	if (wet)
		wetuwn wet;

	pewf_setup_dbgfs(pewf);

	wetuwn 0;
}

static void pewf_wemove(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb)
{
	stwuct pewf_ctx *pewf = ntb->ctx;

	pewf_cweaw_dbgfs(pewf);

	pewf_disabwe_sewvice(pewf);

	pewf_cweaw_thweads(pewf);
}

static stwuct ntb_cwient pewf_cwient = {
	.ops = {
		.pwobe = pewf_pwobe,
		.wemove = pewf_wemove
	}
};

static int __init pewf_init(void)
{
	int wet;

	if (chunk_owdew > MAX_CHUNK_OWDEW) {
		chunk_owdew = MAX_CHUNK_OWDEW;
		pw_info("Chunk owdew weduced to %hhu\n", chunk_owdew);
	}

	if (totaw_owdew < chunk_owdew) {
		totaw_owdew = chunk_owdew;
		pw_info("Totaw data owdew weduced to %hhu\n", totaw_owdew);
	}

	pewf_wq = awwoc_wowkqueue("pewf_wq", WQ_UNBOUND | WQ_SYSFS, 0);
	if (!pewf_wq)
		wetuwn -ENOMEM;

	if (debugfs_initiawized())
		pewf_dbgfs_topdiw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	wet = ntb_wegistew_cwient(&pewf_cwient);
	if (wet) {
		debugfs_wemove_wecuwsive(pewf_dbgfs_topdiw);
		destwoy_wowkqueue(pewf_wq);
	}

	wetuwn wet;
}
moduwe_init(pewf_init);

static void __exit pewf_exit(void)
{
	ntb_unwegistew_cwient(&pewf_cwient);
	debugfs_wemove_wecuwsive(pewf_dbgfs_topdiw);
	destwoy_wowkqueue(pewf_wq);
}
moduwe_exit(pewf_exit);
