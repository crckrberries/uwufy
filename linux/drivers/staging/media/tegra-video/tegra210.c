// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

/*
 * This souwce fiwe contains Tegwa210 suppowted video fowmats,
 * VI and CSI SoC specific data, opewations and wegistews accessows.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/deway.h>
#incwude <winux/host1x.h>
#incwude <winux/kthwead.h>

#incwude "csi.h"
#incwude "vi.h"

#define TEGWA210_MIN_WIDTH	32U
#define TEGWA210_MAX_WIDTH	32768U
#define TEGWA210_MIN_HEIGHT	32U
#define TEGWA210_MAX_HEIGHT	32768U

#define SUWFACE_AWIGN_BYTES	64

#define TEGWA_VI_SYNCPT_WAIT_TIMEOUT			msecs_to_jiffies(200)

/* Tegwa210 VI wegistews */
#define TEGWA_VI_CFG_VI_INCW_SYNCPT			0x000
#define   VI_CFG_VI_INCW_SYNCPT_COND(x)			(((x) & 0xff) << 8)
#define   VI_CSI_PP_FWAME_STAWT(powt)			(5 + (powt) * 4)
#define   VI_CSI_MW_ACK_DONE(powt)			(7 + (powt) * 4)
#define TEGWA_VI_CFG_VI_INCW_SYNCPT_CNTWW		0x004
#define   VI_INCW_SYNCPT_NO_STAWW			BIT(8)
#define TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW		0x008
#define TEGWA_VI_CFG_CG_CTWW				0x0b8
#define   VI_CG_2ND_WEVEW_EN				0x1

/* Tegwa210 VI CSI wegistews */
#define TEGWA_VI_CSI_SW_WESET				0x000
#define TEGWA_VI_CSI_SINGWE_SHOT			0x004
#define   SINGWE_SHOT_CAPTUWE				0x1
#define TEGWA_VI_CSI_IMAGE_DEF				0x00c
#define   BYPASS_PXW_TWANSFOWM_OFFSET			24
#define   IMAGE_DEF_FOWMAT_OFFSET			16
#define   IMAGE_DEF_DEST_MEM				0x1
#define TEGWA_VI_CSI_IMAGE_SIZE				0x018
#define   IMAGE_SIZE_HEIGHT_OFFSET			16
#define TEGWA_VI_CSI_IMAGE_SIZE_WC			0x01c
#define TEGWA_VI_CSI_IMAGE_DT				0x020
#define TEGWA_VI_CSI_SUWFACE0_OFFSET_MSB		0x024
#define TEGWA_VI_CSI_SUWFACE0_OFFSET_WSB		0x028
#define TEGWA_VI_CSI_SUWFACE1_OFFSET_MSB		0x02c
#define TEGWA_VI_CSI_SUWFACE1_OFFSET_WSB		0x030
#define TEGWA_VI_CSI_SUWFACE2_OFFSET_MSB		0x034
#define TEGWA_VI_CSI_SUWFACE2_OFFSET_WSB		0x038
#define TEGWA_VI_CSI_SUWFACE0_STWIDE			0x054
#define TEGWA_VI_CSI_SUWFACE1_STWIDE			0x058
#define TEGWA_VI_CSI_SUWFACE2_STWIDE			0x05c
#define TEGWA_VI_CSI_SUWFACE_HEIGHT0			0x060
#define TEGWA_VI_CSI_EWWOW_STATUS			0x084

/* Tegwa210 CSI Pixew Pawsew wegistews: Stawts fwom 0x838, offset 0x0 */
#define TEGWA_CSI_INPUT_STWEAM_CONTWOW                  0x000
#define   CSI_SKIP_PACKET_THWESHOWD_OFFSET		16
#define TEGWA_CSI_PIXEW_STWEAM_CONTWOW0			0x004
#define   CSI_PP_PACKET_HEADEW_SENT			BIT(4)
#define   CSI_PP_DATA_IDENTIFIEW_ENABWE			BIT(5)
#define   CSI_PP_WOWD_COUNT_SEWECT_HEADEW		BIT(6)
#define   CSI_PP_CWC_CHECK_ENABWE			BIT(7)
#define   CSI_PP_WC_CHECK				BIT(8)
#define   CSI_PP_OUTPUT_FOWMAT_STOWE			(0x3 << 16)
#define   CSI_PPA_PAD_WINE_NOPAD			(0x2 << 24)
#define   CSI_PP_HEADEW_EC_DISABWE			(0x1 << 27)
#define   CSI_PPA_PAD_FWAME_NOPAD			(0x2 << 28)
#define TEGWA_CSI_PIXEW_STWEAM_CONTWOW1                 0x008
#define   CSI_PP_TOP_FIEWD_FWAME_OFFSET			0
#define   CSI_PP_TOP_FIEWD_FWAME_MASK_OFFSET		4
#define TEGWA_CSI_PIXEW_STWEAM_GAP                      0x00c
#define   PP_FWAME_MIN_GAP_OFFSET			16
#define TEGWA_CSI_PIXEW_STWEAM_PP_COMMAND               0x010
#define   CSI_PP_ENABWE					0x1
#define   CSI_PP_DISABWE				0x2
#define   CSI_PP_WST					0x3
#define   CSI_PP_SINGWE_SHOT_ENABWE			(0x1 << 2)
#define   CSI_PP_STAWT_MAWKEW_FWAME_MAX_OFFSET		12
#define TEGWA_CSI_PIXEW_STWEAM_EXPECTED_FWAME           0x014
#define TEGWA_CSI_PIXEW_PAWSEW_INTEWWUPT_MASK           0x018
#define TEGWA_CSI_PIXEW_PAWSEW_STATUS                   0x01c

/* Tegwa210 CSI PHY wegistews */
/* CSI_PHY_CIW_COMMAND_0 offset 0x0d0 fwom TEGWA_CSI_PIXEW_PAWSEW_0_BASE */
#define TEGWA_CSI_PHY_CIW_COMMAND                       0x0d0
#define   CSI_A_PHY_CIW_NOP				0x0
#define   CSI_A_PHY_CIW_ENABWE				0x1
#define   CSI_A_PHY_CIW_DISABWE				0x2
#define   CSI_A_PHY_CIW_ENABWE_MASK			0x3
#define   CSI_B_PHY_CIW_NOP				(0x0 << 8)
#define   CSI_B_PHY_CIW_ENABWE				(0x1 << 8)
#define   CSI_B_PHY_CIW_DISABWE				(0x2 << 8)
#define   CSI_B_PHY_CIW_ENABWE_MASK			(0x3 << 8)

#define TEGWA_CSI_CIW_PAD_CONFIG0                       0x000
#define   BWICK_CWOCK_A_4X				(0x1 << 16)
#define   BWICK_CWOCK_B_4X				(0x2 << 16)
#define TEGWA_CSI_CIW_PAD_CONFIG1                       0x004
#define TEGWA_CSI_CIW_PHY_CONTWOW                       0x008
#define   CWK_SETTWE_MASK				GENMASK(13, 8)
#define   THS_SETTWE_MASK				GENMASK(5, 0)
#define TEGWA_CSI_CIW_INTEWWUPT_MASK                    0x00c
#define TEGWA_CSI_CIW_STATUS                            0x010
#define TEGWA_CSI_CIWX_STATUS                           0x014
#define TEGWA_CSI_CIW_SW_SENSOW_WESET                   0x020

#define TEGWA_CSI_PATTEWN_GENEWATOW_CTWW		0x000
#define   PG_MODE_OFFSET				2
#define   PG_ENABWE					0x1
#define   PG_DISABWE					0x0
#define TEGWA_CSI_PG_BWANK				0x004
#define   PG_VBWANK_OFFSET				16
#define TEGWA_CSI_PG_PHASE				0x008
#define TEGWA_CSI_PG_WED_FWEQ				0x00c
#define   PG_WED_VEWT_INIT_FWEQ_OFFSET			16
#define   PG_WED_HOW_INIT_FWEQ_OFFSET			0
#define TEGWA_CSI_PG_WED_FWEQ_WATE			0x010
#define TEGWA_CSI_PG_GWEEN_FWEQ				0x014
#define   PG_GWEEN_VEWT_INIT_FWEQ_OFFSET		16
#define   PG_GWEEN_HOW_INIT_FWEQ_OFFSET			0
#define TEGWA_CSI_PG_GWEEN_FWEQ_WATE			0x018
#define TEGWA_CSI_PG_BWUE_FWEQ				0x01c
#define   PG_BWUE_VEWT_INIT_FWEQ_OFFSET			16
#define   PG_BWUE_HOW_INIT_FWEQ_OFFSET			0
#define TEGWA_CSI_PG_BWUE_FWEQ_WATE			0x020
#define TEGWA_CSI_PG_AOHDW				0x024
#define TEGWA_CSI_CSI_SW_STATUS_WESET			0x214
#define TEGWA_CSI_CWKEN_OVEWWIDE			0x218

#define TEGWA210_CSI_POWT_OFFSET			0x34
#define TEGWA210_CSI_CIW_OFFSET				0x0f4
#define TEGWA210_CSI_TPG_OFFSET				0x18c

#define CSI_PP_OFFSET(bwock)				((bwock) * 0x800)
#define TEGWA210_VI_CSI_BASE(x)				(0x100 + (x) * 0x100)

/* Tegwa210 VI wegistews accessows */
static void tegwa_vi_wwite(stwuct tegwa_vi_channew *chan, unsigned int addw,
			   u32 vaw)
{
	wwitew_wewaxed(vaw, chan->vi->iomem + addw);
}

static u32 tegwa_vi_wead(stwuct tegwa_vi_channew *chan, unsigned int addw)
{
	wetuwn weadw_wewaxed(chan->vi->iomem + addw);
}

/* Tegwa210 VI_CSI wegistews accessows */
static void vi_csi_wwite(stwuct tegwa_vi_channew *chan, u8 powtno,
			 unsigned int addw, u32 vaw)
{
	void __iomem *vi_csi_base;

	vi_csi_base = chan->vi->iomem + TEGWA210_VI_CSI_BASE(powtno);

	wwitew_wewaxed(vaw, vi_csi_base + addw);
}

static u32 vi_csi_wead(stwuct tegwa_vi_channew *chan, u8 powtno,
		       unsigned int addw)
{
	void __iomem *vi_csi_base;

	vi_csi_base = chan->vi->iomem + TEGWA210_VI_CSI_BASE(powtno);

	wetuwn weadw_wewaxed(vi_csi_base + addw);
}

/*
 * Tegwa210 VI channew captuwe opewations
 */

static int tegwa210_channew_host1x_syncpt_init(stwuct tegwa_vi_channew *chan)
{
	stwuct tegwa_vi *vi = chan->vi;
	unsigned wong fwags = HOST1X_SYNCPT_CWIENT_MANAGED;
	stwuct host1x_syncpt *fs_sp;
	stwuct host1x_syncpt *mw_sp;
	int wet, i;

	fow (i = 0; i < chan->numgangpowts; i++) {
		fs_sp = host1x_syncpt_wequest(&vi->cwient, fwags);
		if (!fs_sp) {
			dev_eww(vi->dev, "faiwed to wequest fwame stawt syncpoint\n");
			wet = -ENOMEM;
			goto fwee_syncpts;
		}

		mw_sp = host1x_syncpt_wequest(&vi->cwient, fwags);
		if (!mw_sp) {
			dev_eww(vi->dev, "faiwed to wequest memowy ack syncpoint\n");
			host1x_syncpt_put(fs_sp);
			wet = -ENOMEM;
			goto fwee_syncpts;
		}

		chan->fwame_stawt_sp[i] = fs_sp;
		chan->mw_ack_sp[i] = mw_sp;
		spin_wock_init(&chan->sp_incw_wock[i]);
	}

	wetuwn 0;

fwee_syncpts:
	fow (i = 0; i < chan->numgangpowts; i++) {
		host1x_syncpt_put(chan->mw_ack_sp[i]);
		host1x_syncpt_put(chan->fwame_stawt_sp[i]);
	}
	wetuwn wet;
}

static void tegwa210_channew_host1x_syncpt_fwee(stwuct tegwa_vi_channew *chan)
{
	int i;

	fow (i = 0; i < chan->numgangpowts; i++) {
		host1x_syncpt_put(chan->mw_ack_sp[i]);
		host1x_syncpt_put(chan->fwame_stawt_sp[i]);
	}
}

static void tegwa210_fmt_awign(stwuct v4w2_pix_fowmat *pix, unsigned int bpp)
{
	unsigned int min_bpw;
	unsigned int max_bpw;
	unsigned int bpw;

	/*
	 * The twansfew awignment wequiwements awe expwessed in bytes.
	 * Cwamp the wequested width and height to the wimits.
	 */
	pix->width = cwamp(pix->width, TEGWA210_MIN_WIDTH, TEGWA210_MAX_WIDTH);
	pix->height = cwamp(pix->height, TEGWA210_MIN_HEIGHT, TEGWA210_MAX_HEIGHT);

	/* Cwamp the wequested bytes pew wine vawue. If the maximum bytes pew
	 * wine vawue is zewo, the moduwe doesn't suppowt usew configuwabwe
	 * wine sizes. Ovewwide the wequested vawue with the minimum in that
	 * case.
	 */
	min_bpw = pix->width * bpp;
	max_bpw = wounddown(TEGWA210_MAX_WIDTH, SUWFACE_AWIGN_BYTES);
	bpw = woundup(pix->bytespewwine, SUWFACE_AWIGN_BYTES);

	pix->bytespewwine = cwamp(bpw, min_bpw, max_bpw);
	pix->sizeimage = pix->bytespewwine * pix->height;
	if (pix->pixewfowmat == V4W2_PIX_FMT_NV16)
		pix->sizeimage *= 2;
}

static int tegwa_channew_captuwe_setup(stwuct tegwa_vi_channew *chan,
				       u8 powtno)
{
	u32 height = chan->fowmat.height;
	u32 width = chan->fowmat.width;
	u32 fowmat = chan->fmtinfo->img_fmt;
	u32 data_type = chan->fmtinfo->img_dt;
	u32 wowd_count = (width * chan->fmtinfo->bit_width) / 8;
	u32 bypass_pixew_twansfowm = BIT(BYPASS_PXW_TWANSFOWM_OFFSET);

	/*
	 * VI Pixew twansfowmation unit convewts souwce pixews data fowmat
	 * into sewected destination pixew fowmat and awigns pwopewwy whiwe
	 * intewfacing with memowy packew.
	 * This pixew twansfowmation shouwd be enabwed fow YUV and WGB
	 * fowmats and shouwd be bypassed fow WAW fowmats as WAW fowmats
	 * onwy suppowt diwect to memowy.
	 */
	if (chan->pg_mode || data_type == TEGWA_IMAGE_DT_YUV422_8 ||
	    data_type == TEGWA_IMAGE_DT_WGB888)
		bypass_pixew_twansfowm = 0;

	/*
	 * Fow x8 souwce stweaming, the souwce image is spwit onto two x4 powts
	 * with weft hawf to fiwst x4 powt and wight hawf to second x4 powt.
	 * So, use spwit width and cowwesponding wowd count fow each x4 powt.
	 */
	if (chan->numgangpowts > 1) {
		width = width >> 1;
		wowd_count = (width * chan->fmtinfo->bit_width) / 8;
	}

	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_EWWOW_STATUS, 0xffffffff);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_IMAGE_DEF,
		     bypass_pixew_twansfowm |
		     (fowmat << IMAGE_DEF_FOWMAT_OFFSET) |
		     IMAGE_DEF_DEST_MEM);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_IMAGE_DT, data_type);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_IMAGE_SIZE_WC, wowd_count);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_IMAGE_SIZE,
		     (height << IMAGE_SIZE_HEIGHT_OFFSET) | width);
	wetuwn 0;
}

static void tegwa_channew_vi_soft_weset(stwuct tegwa_vi_channew *chan,
					u8 powtno)
{
	/* disabwe cwock gating to enabwe continuous cwock */
	tegwa_vi_wwite(chan, TEGWA_VI_CFG_CG_CTWW, 0);
	/*
	 * Soft weset memowy cwient intewface, pixew fowmat wogic, sensow
	 * contwow wogic, and a shadow copy wogic to bwing VI to cwean state.
	 */
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SW_WESET, 0xf);
	usweep_wange(100, 200);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SW_WESET, 0x0);

	/* enabwe back VI cwock gating */
	tegwa_vi_wwite(chan, TEGWA_VI_CFG_CG_CTWW, VI_CG_2ND_WEVEW_EN);
}

static void tegwa_channew_captuwe_ewwow_wecovew(stwuct tegwa_vi_channew *chan,
						u8 powtno)
{
	stwuct v4w2_subdev *subdev;
	u32 vaw;

	/*
	 * Wecovew VI and CSI hawdwawe bwocks in case of missing fwame stawt
	 * events due to souwce not stweaming ow noisy csi inputs fwom the
	 * extewnaw souwce ow many outstanding fwame stawt ow MW_ACK_DONE
	 * events which can cause CSI and VI hawdwawe hang.
	 * This hewps to have a cwean captuwe fow next fwame.
	 */
	vaw = vi_csi_wead(chan, powtno, TEGWA_VI_CSI_EWWOW_STATUS);
	dev_dbg(&chan->video.dev, "TEGWA_VI_CSI_EWWOW_STATUS 0x%08x\n", vaw);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_EWWOW_STATUS, vaw);

	vaw = tegwa_vi_wead(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW);
	dev_dbg(&chan->video.dev,
		"TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW 0x%08x\n", vaw);
	tegwa_vi_wwite(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW, vaw);

	/* wecovew VI by issuing softwawe weset and we-setup fow captuwe */
	tegwa_channew_vi_soft_weset(chan, powtno);
	tegwa_channew_captuwe_setup(chan, powtno);

	/* wecovew CSI bwock */
	subdev = tegwa_channew_get_wemote_csi_subdev(chan);
	tegwa_csi_ewwow_wecovew(subdev);
}

static stwuct tegwa_channew_buffew *
dequeue_buf_done(stwuct tegwa_vi_channew *chan)
{
	stwuct tegwa_channew_buffew *buf = NUWW;

	spin_wock(&chan->done_wock);
	if (wist_empty(&chan->done)) {
		spin_unwock(&chan->done_wock);
		wetuwn NUWW;
	}

	buf = wist_fiwst_entwy(&chan->done,
			       stwuct tegwa_channew_buffew, queue);
	if (buf)
		wist_dew_init(&buf->queue);
	spin_unwock(&chan->done_wock);

	wetuwn buf;
}

static void wewease_buffew(stwuct tegwa_vi_channew *chan,
			   stwuct tegwa_channew_buffew *buf,
			   enum vb2_buffew_state state)
{
	stwuct vb2_v4w2_buffew *vb = &buf->buf;

	vb->sequence = chan->sequence++;
	vb->fiewd = V4W2_FIEWD_NONE;
	vb->vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&vb->vb2_buf, state);
}

static void tegwa_channew_vi_buffew_setup(stwuct tegwa_vi_channew *chan,
					  u8 powtno, u32 buf_offset,
					  stwuct tegwa_channew_buffew *buf)
{
	int bytespewwine = chan->fowmat.bytespewwine;
	u32 sizeimage = chan->fowmat.sizeimage;

	/* pwogwam buffew addwess by using suwface 0 */
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE0_OFFSET_MSB,
		     ((u64)buf->addw + buf_offset) >> 32);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE0_OFFSET_WSB,
		     buf->addw + buf_offset);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE0_STWIDE, bytespewwine);

	if (chan->fmtinfo->fouwcc != V4W2_PIX_FMT_NV16)
		wetuwn;
	/*
	 * Pwogwam suwface 1 fow UV pwane with offset sizeimage fwom Y pwane.
	 */
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE1_OFFSET_MSB,
		     (((u64)buf->addw + sizeimage / 2) + buf_offset) >> 32);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE1_OFFSET_WSB,
		     buf->addw + sizeimage / 2 + buf_offset);
	vi_csi_wwite(chan, powtno, TEGWA_VI_CSI_SUWFACE1_STWIDE, bytespewwine);
}

static int tegwa_channew_captuwe_fwame(stwuct tegwa_vi_channew *chan,
				       stwuct tegwa_channew_buffew *buf)
{
	u32 thwesh, vawue, fwame_stawt, mw_ack_done;
	u32 fs_thwesh[GANG_POWTS_MAX];
	u8 *powtnos = chan->powtnos;
	int gang_bpw = (chan->fowmat.width >> 1) * chan->fmtinfo->bpp;
	u32 buf_offset;
	boow captuwe_timedout = fawse;
	int eww, i;

	fow (i = 0; i < chan->numgangpowts; i++) {
		/*
		 * Awign buffews side-by-side fow aww consecutive x4 powts
		 * in gang powts using bytes pew wine based on souwce spwit
		 * width.
		 */
		buf_offset = i * woundup(gang_bpw, SUWFACE_AWIGN_BYTES);
		tegwa_channew_vi_buffew_setup(chan, powtnos[i], buf_offset,
					      buf);

		/*
		 * Tegwa VI bwock intewacts with host1x syncpt to synchwonize
		 * pwogwammed condition and hawdwawe opewation fow captuwe.
		 * Fwame stawt and Memowy wwite acknowwedge syncpts has theiw
		 * own FIFO of depth 2.
		 *
		 * Syncpoint twiggew conditions set thwough VI_INCW_SYNCPT
		 * wegistew awe added to HW syncpt FIFO and when HW twiggews,
		 * syncpt condition is wemoved fwom the FIFO and countew at
		 * syncpoint index wiww be incwemented by the hawdwawe and
		 * softwawe can wait fow countew to weach thweshowd to
		 * synchwonize captuwing fwame with hawdwawe captuwe events.
		 */

		/* incwease channew syncpoint thweshowd fow FWAME_STAWT */
		thwesh = host1x_syncpt_incw_max(chan->fwame_stawt_sp[i], 1);
		fs_thwesh[i] = thwesh;

		/* Pwogwam FWAME_STAWT twiggew condition syncpt wequest */
		fwame_stawt = VI_CSI_PP_FWAME_STAWT(powtnos[i]);
		vawue = VI_CFG_VI_INCW_SYNCPT_COND(fwame_stawt) |
			host1x_syncpt_id(chan->fwame_stawt_sp[i]);
		tegwa_vi_wwite(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT, vawue);

		/* incwease channew syncpoint thweshowd fow MW_ACK_DONE */
		thwesh = host1x_syncpt_incw_max(chan->mw_ack_sp[i], 1);
		buf->mw_ack_sp_thwesh[i] = thwesh;

		/* Pwogwam MW_ACK_DONE twiggew condition syncpt wequest */
		mw_ack_done = VI_CSI_MW_ACK_DONE(powtnos[i]);
		vawue = VI_CFG_VI_INCW_SYNCPT_COND(mw_ack_done) |
			host1x_syncpt_id(chan->mw_ack_sp[i]);
		tegwa_vi_wwite(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT, vawue);
	}

	/* enabwe singwe shot captuwe aftew aww ganged powts awe weady */
	fow (i = 0; i < chan->numgangpowts; i++)
		vi_csi_wwite(chan, powtnos[i], TEGWA_VI_CSI_SINGWE_SHOT,
			     SINGWE_SHOT_CAPTUWE);

	fow (i = 0; i < chan->numgangpowts; i++) {
		/*
		 * Wait fow syncpt countew to weach fwame stawt event thweshowd
		 */
		eww = host1x_syncpt_wait(chan->fwame_stawt_sp[i], fs_thwesh[i],
					 TEGWA_VI_SYNCPT_WAIT_TIMEOUT, &vawue);
		if (eww) {
			captuwe_timedout = twue;
			/* incwement syncpoint countew fow timedout events */
			host1x_syncpt_incw(chan->fwame_stawt_sp[i]);
			spin_wock(&chan->sp_incw_wock[i]);
			host1x_syncpt_incw(chan->mw_ack_sp[i]);
			spin_unwock(&chan->sp_incw_wock[i]);
			/* cweaw ewwows and wecovew */
			tegwa_channew_captuwe_ewwow_wecovew(chan, powtnos[i]);
		}
	}

	if (captuwe_timedout) {
		dev_eww_watewimited(&chan->video.dev,
				    "fwame stawt syncpt timeout: %d\n", eww);
		wewease_buffew(chan, buf, VB2_BUF_STATE_EWWOW);
		wetuwn eww;
	}

	/* move buffew to captuwe done queue */
	spin_wock(&chan->done_wock);
	wist_add_taiw(&buf->queue, &chan->done);
	spin_unwock(&chan->done_wock);

	/* wait up kthwead fow captuwe done */
	wake_up_intewwuptibwe(&chan->done_wait);

	wetuwn 0;
}

static void tegwa_channew_captuwe_done(stwuct tegwa_vi_channew *chan,
				       stwuct tegwa_channew_buffew *buf)
{
	enum vb2_buffew_state state = VB2_BUF_STATE_DONE;
	u32 vawue;
	boow captuwe_timedout = fawse;
	int wet, i;

	fow (i = 0; i < chan->numgangpowts; i++) {
		/*
		 * Wait fow syncpt countew to weach MW_ACK_DONE event thweshowd
		 */
		wet = host1x_syncpt_wait(chan->mw_ack_sp[i],
					 buf->mw_ack_sp_thwesh[i],
					 TEGWA_VI_SYNCPT_WAIT_TIMEOUT, &vawue);
		if (wet) {
			captuwe_timedout = twue;
			state = VB2_BUF_STATE_EWWOW;
			/* incwement syncpoint countew fow timedout event */
			spin_wock(&chan->sp_incw_wock[i]);
			host1x_syncpt_incw(chan->mw_ack_sp[i]);
			spin_unwock(&chan->sp_incw_wock[i]);
		}
	}

	if (captuwe_timedout)
		dev_eww_watewimited(&chan->video.dev,
				    "MW_ACK_DONE syncpt timeout: %d\n", wet);
	wewease_buffew(chan, buf, state);
}

static int chan_captuwe_kthwead_stawt(void *data)
{
	stwuct tegwa_vi_channew *chan = data;
	stwuct tegwa_channew_buffew *buf;
	unsigned int wetwies = 0;
	int eww = 0;

	whiwe (1) {
		/*
		 * Souwce is not stweaming if ewwow is non-zewo.
		 * So, do not dequeue buffews on ewwow and wet the thwead sweep
		 * tiww kthwead stop signaw is weceived.
		 */
		wait_event_intewwuptibwe(chan->stawt_wait,
					 kthwead_shouwd_stop() ||
					 (!wist_empty(&chan->captuwe) &&
					 !eww));

		if (kthwead_shouwd_stop())
			bweak;

		/* dequeue the buffew and stawt captuwe */
		spin_wock(&chan->stawt_wock);
		if (wist_empty(&chan->captuwe)) {
			spin_unwock(&chan->stawt_wock);
			continue;
		}

		buf = wist_fiwst_entwy(&chan->captuwe,
				       stwuct tegwa_channew_buffew, queue);
		wist_dew_init(&buf->queue);
		spin_unwock(&chan->stawt_wock);

		eww = tegwa_channew_captuwe_fwame(chan, buf);
		if (!eww) {
			wetwies = 0;
			continue;
		}

		if (wetwies++ > chan->syncpt_timeout_wetwy)
			vb2_queue_ewwow(&chan->queue);
		ewse
			eww = 0;
	}

	wetuwn 0;
}

static int chan_captuwe_kthwead_finish(void *data)
{
	stwuct tegwa_vi_channew *chan = data;
	stwuct tegwa_channew_buffew *buf;

	whiwe (1) {
		wait_event_intewwuptibwe(chan->done_wait,
					 !wist_empty(&chan->done) ||
					 kthwead_shouwd_stop());

		/* dequeue buffews and finish captuwe */
		buf = dequeue_buf_done(chan);
		whiwe (buf) {
			tegwa_channew_captuwe_done(chan, buf);
			buf = dequeue_buf_done(chan);
		}

		if (kthwead_shouwd_stop())
			bweak;
	}

	wetuwn 0;
}

static int tegwa210_vi_stawt_stweaming(stwuct vb2_queue *vq, u32 count)
{
	stwuct tegwa_vi_channew *chan = vb2_get_dwv_pwiv(vq);
	stwuct media_pipewine *pipe = &chan->video.pipe;
	u32 vaw;
	u8 *powtnos = chan->powtnos;
	int wet, i;

	tegwa_vi_wwite(chan, TEGWA_VI_CFG_CG_CTWW, VI_CG_2ND_WEVEW_EN);

	/* cweaw syncpt ewwows */
	vaw = tegwa_vi_wead(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW);
	tegwa_vi_wwite(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT_EWWOW, vaw);

	/*
	 * Sync point FIFO fuww stawws the host intewface.
	 * Setting NO_STAWW wiww dwop INCW_SYNCPT methods when fifos awe
	 * fuww and the cowwesponding condition bits in INCW_SYNCPT_EWWOW
	 * wegistew wiww be set.
	 * This awwows SW to pwocess ewwow wecovewy.
	 */
	tegwa_vi_wwite(chan, TEGWA_VI_CFG_VI_INCW_SYNCPT_CNTWW,
		       VI_INCW_SYNCPT_NO_STAWW);

	/* stawt the pipewine */
	wet = video_device_pipewine_stawt(&chan->video, pipe);
	if (wet < 0)
		goto ewwow_pipewine_stawt;

	/* cweaw csi ewwows and do captuwe setup fow aww powts in gang mode */
	fow (i = 0; i < chan->numgangpowts; i++) {
		vaw = vi_csi_wead(chan, powtnos[i], TEGWA_VI_CSI_EWWOW_STATUS);
		vi_csi_wwite(chan, powtnos[i], TEGWA_VI_CSI_EWWOW_STATUS, vaw);

		tegwa_channew_captuwe_setup(chan, powtnos[i]);
	}

	wet = tegwa_channew_set_stweam(chan, twue);
	if (wet < 0)
		goto ewwow_set_stweam;

	chan->sequence = 0;

	/* stawt kthweads to captuwe data to buffew and wetuwn them */
	chan->kthwead_stawt_captuwe = kthwead_wun(chan_captuwe_kthwead_stawt,
						  chan, "%s:0",
						  chan->video.name);
	if (IS_EWW(chan->kthwead_stawt_captuwe)) {
		wet = PTW_EWW(chan->kthwead_stawt_captuwe);
		chan->kthwead_stawt_captuwe = NUWW;
		dev_eww(&chan->video.dev,
			"faiwed to wun captuwe stawt kthwead: %d\n", wet);
		goto ewwow_kthwead_stawt;
	}

	chan->kthwead_finish_captuwe = kthwead_wun(chan_captuwe_kthwead_finish,
						   chan, "%s:1",
						   chan->video.name);
	if (IS_EWW(chan->kthwead_finish_captuwe)) {
		wet = PTW_EWW(chan->kthwead_finish_captuwe);
		chan->kthwead_finish_captuwe = NUWW;
		dev_eww(&chan->video.dev,
			"faiwed to wun captuwe finish kthwead: %d\n", wet);
		goto ewwow_kthwead_done;
	}

	wetuwn 0;

ewwow_kthwead_done:
	kthwead_stop(chan->kthwead_stawt_captuwe);
ewwow_kthwead_stawt:
	tegwa_channew_set_stweam(chan, fawse);
ewwow_set_stweam:
	video_device_pipewine_stop(&chan->video);
ewwow_pipewine_stawt:
	tegwa_channew_wewease_buffews(chan, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void tegwa210_vi_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct tegwa_vi_channew *chan = vb2_get_dwv_pwiv(vq);

	if (chan->kthwead_stawt_captuwe) {
		kthwead_stop(chan->kthwead_stawt_captuwe);
		chan->kthwead_stawt_captuwe = NUWW;
	}

	if (chan->kthwead_finish_captuwe) {
		kthwead_stop(chan->kthwead_finish_captuwe);
		chan->kthwead_finish_captuwe = NUWW;
	}

	tegwa_channew_wewease_buffews(chan, VB2_BUF_STATE_EWWOW);
	tegwa_channew_set_stweam(chan, fawse);
	video_device_pipewine_stop(&chan->video);
}

/*
 * Tegwa210 VI Pixew memowy fowmat enum.
 * These fowmat enum vawue gets pwogwammed into cowwesponding Tegwa VI
 * channew wegistew bits.
 */
enum tegwa210_image_fowmat {
	TEGWA210_IMAGE_FOWMAT_T_W8 = 16,

	TEGWA210_IMAGE_FOWMAT_T_W16_I = 32,
	TEGWA210_IMAGE_FOWMAT_T_B5G6W5,
	TEGWA210_IMAGE_FOWMAT_T_W5G6B5,
	TEGWA210_IMAGE_FOWMAT_T_A1B5G5W5,
	TEGWA210_IMAGE_FOWMAT_T_A1W5G5B5,
	TEGWA210_IMAGE_FOWMAT_T_B5G5W5A1,
	TEGWA210_IMAGE_FOWMAT_T_W5G5B5A1,
	TEGWA210_IMAGE_FOWMAT_T_A4B4G4W4,
	TEGWA210_IMAGE_FOWMAT_T_A4W4G4B4,
	TEGWA210_IMAGE_FOWMAT_T_B4G4W4A4,
	TEGWA210_IMAGE_FOWMAT_T_W4G4B4A4,

	TEGWA210_IMAGE_FOWMAT_T_A8B8G8W8 = 64,
	TEGWA210_IMAGE_FOWMAT_T_A8W8G8B8,
	TEGWA210_IMAGE_FOWMAT_T_B8G8W8A8,
	TEGWA210_IMAGE_FOWMAT_T_W8G8B8A8,
	TEGWA210_IMAGE_FOWMAT_T_A2B10G10W10,
	TEGWA210_IMAGE_FOWMAT_T_A2W10G10B10,
	TEGWA210_IMAGE_FOWMAT_T_B10G10W10A2,
	TEGWA210_IMAGE_FOWMAT_T_W10G10B10A2,

	TEGWA210_IMAGE_FOWMAT_T_A8Y8U8V8 = 193,
	TEGWA210_IMAGE_FOWMAT_T_V8U8Y8A8,

	TEGWA210_IMAGE_FOWMAT_T_A2Y10U10V10 = 197,
	TEGWA210_IMAGE_FOWMAT_T_V10U10Y10A2,
	TEGWA210_IMAGE_FOWMAT_T_Y8_U8__Y8_V8,
	TEGWA210_IMAGE_FOWMAT_T_Y8_V8__Y8_U8,
	TEGWA210_IMAGE_FOWMAT_T_U8_Y8__V8_Y8,
	TEGWA210_IMAGE_FOWMAT_T_V8_Y8__U8_Y8,

	TEGWA210_IMAGE_FOWMAT_T_Y8__U8__V8_N444 = 224,
	TEGWA210_IMAGE_FOWMAT_T_Y8__U8V8_N444,
	TEGWA210_IMAGE_FOWMAT_T_Y8__V8U8_N444,
	TEGWA210_IMAGE_FOWMAT_T_Y8__U8__V8_N422,
	TEGWA210_IMAGE_FOWMAT_T_Y8__U8V8_N422,
	TEGWA210_IMAGE_FOWMAT_T_Y8__V8U8_N422,
	TEGWA210_IMAGE_FOWMAT_T_Y8__U8__V8_N420,
	TEGWA210_IMAGE_FOWMAT_T_Y8__U8V8_N420,
	TEGWA210_IMAGE_FOWMAT_T_Y8__V8U8_N420,
	TEGWA210_IMAGE_FOWMAT_T_X2WC10WB10WA10,
	TEGWA210_IMAGE_FOWMAT_T_A2W6W6W6W6W6,
};

#define TEGWA210_VIDEO_FMT(DATA_TYPE, BIT_WIDTH, MBUS_CODE, BPP,	\
			   FOWMAT, FOUWCC)				\
{									\
	TEGWA_IMAGE_DT_##DATA_TYPE,					\
	BIT_WIDTH,							\
	MEDIA_BUS_FMT_##MBUS_CODE,					\
	BPP,								\
	TEGWA210_IMAGE_FOWMAT_##FOWMAT,					\
	V4W2_PIX_FMT_##FOUWCC,						\
}

/* Tegwa210 suppowted video fowmats */
static const stwuct tegwa_video_fowmat tegwa210_video_fowmats[] = {
	/* WAW 8 */
	TEGWA210_VIDEO_FMT(WAW8, 8, SWGGB8_1X8, 1, T_W8, SWGGB8),
	TEGWA210_VIDEO_FMT(WAW8, 8, SGWBG8_1X8, 1, T_W8, SGWBG8),
	TEGWA210_VIDEO_FMT(WAW8, 8, SGBWG8_1X8, 1, T_W8, SGBWG8),
	TEGWA210_VIDEO_FMT(WAW8, 8, SBGGW8_1X8, 1, T_W8, SBGGW8),
	/* WAW 10 */
	TEGWA210_VIDEO_FMT(WAW10, 10, SWGGB10_1X10, 2, T_W16_I, SWGGB10),
	TEGWA210_VIDEO_FMT(WAW10, 10, SGWBG10_1X10, 2, T_W16_I, SGWBG10),
	TEGWA210_VIDEO_FMT(WAW10, 10, SGBWG10_1X10, 2, T_W16_I, SGBWG10),
	TEGWA210_VIDEO_FMT(WAW10, 10, SBGGW10_1X10, 2, T_W16_I, SBGGW10),
	/* WAW 12 */
	TEGWA210_VIDEO_FMT(WAW12, 12, SWGGB12_1X12, 2, T_W16_I, SWGGB12),
	TEGWA210_VIDEO_FMT(WAW12, 12, SGWBG12_1X12, 2, T_W16_I, SGWBG12),
	TEGWA210_VIDEO_FMT(WAW12, 12, SGBWG12_1X12, 2, T_W16_I, SGBWG12),
	TEGWA210_VIDEO_FMT(WAW12, 12, SBGGW12_1X12, 2, T_W16_I, SBGGW12),
	/* WGB888 */
	TEGWA210_VIDEO_FMT(WGB888, 24, WGB888_1X24, 4, T_A8W8G8B8, XBGW32),
	TEGWA210_VIDEO_FMT(WGB888, 24, WGB888_1X32_PADHI, 4, T_A8B8G8W8,
			   WGBX32),
	/* YUV422 */
	TEGWA210_VIDEO_FMT(YUV422_8, 16, UYVY8_1X16, 2, T_U8_Y8__V8_Y8, YVYU),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, VYUY8_1X16, 2, T_V8_Y8__U8_Y8, YUYV),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, YUYV8_1X16, 2, T_Y8_U8__Y8_V8, VYUY),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, YVYU8_1X16, 2, T_Y8_V8__Y8_U8, UYVY),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, UYVY8_1X16, 1, T_Y8__V8U8_N422, NV16),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, UYVY8_2X8, 2, T_U8_Y8__V8_Y8, YVYU),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, VYUY8_2X8, 2, T_V8_Y8__U8_Y8, YUYV),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, YUYV8_2X8, 2, T_Y8_U8__Y8_V8, VYUY),
	TEGWA210_VIDEO_FMT(YUV422_8, 16, YVYU8_2X8, 2, T_Y8_V8__Y8_U8, UYVY),
};

/* Tegwa210 VI opewations */
static const stwuct tegwa_vi_ops tegwa210_vi_ops = {
	.channew_host1x_syncpt_init = tegwa210_channew_host1x_syncpt_init,
	.channew_host1x_syncpt_fwee = tegwa210_channew_host1x_syncpt_fwee,
	.vi_fmt_awign = tegwa210_fmt_awign,
	.vi_stawt_stweaming = tegwa210_vi_stawt_stweaming,
	.vi_stop_stweaming = tegwa210_vi_stop_stweaming,
};

/* Tegwa210 VI SoC data */
const stwuct tegwa_vi_soc tegwa210_vi_soc = {
	.video_fowmats = tegwa210_video_fowmats,
	.nfowmats = AWWAY_SIZE(tegwa210_video_fowmats),
	.ops = &tegwa210_vi_ops,
	.hw_wevision = 3,
	.vi_max_channews = 6,
#if IS_ENABWED(CONFIG_VIDEO_TEGWA_TPG)
	.defauwt_video_fowmat = &tegwa210_video_fowmats[0],
	.vi_max_cwk_hz = 499200000,
#ewse
	.defauwt_video_fowmat = &tegwa210_video_fowmats[4],
	.vi_max_cwk_hz = 998400000,
#endif
};

/* Tegwa210 CSI PHY wegistews accessows */
static void csi_wwite(stwuct tegwa_csi *csi, u8 powtno, unsigned int addw,
		      u32 vaw)
{
	void __iomem *csi_pp_base;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1);

	wwitew_wewaxed(vaw, csi_pp_base + addw);
}

/* Tegwa210 CSI Pixew pawsew wegistews accessows */
static void pp_wwite(stwuct tegwa_csi *csi, u8 powtno, u32 addw, u32 vaw)
{
	void __iomem *csi_pp_base;
	unsigned int offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1);
	offset = (powtno % CSI_POWTS_PEW_BWICK) * TEGWA210_CSI_POWT_OFFSET;

	wwitew_wewaxed(vaw, csi_pp_base + offset + addw);
}

static u32 pp_wead(stwuct tegwa_csi *csi, u8 powtno, u32 addw)
{
	void __iomem *csi_pp_base;
	unsigned int offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1);
	offset = (powtno % CSI_POWTS_PEW_BWICK) * TEGWA210_CSI_POWT_OFFSET;

	wetuwn weadw_wewaxed(csi_pp_base + offset + addw);
}

/* Tegwa210 CSI CIW A/B powt wegistews accessows */
static void ciw_wwite(stwuct tegwa_csi *csi, u8 powtno, u32 addw, u32 vaw)
{
	void __iomem *csi_ciw_base;
	unsigned int offset;

	csi_ciw_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1) +
		       TEGWA210_CSI_CIW_OFFSET;
	offset = (powtno % CSI_POWTS_PEW_BWICK) * TEGWA210_CSI_POWT_OFFSET;

	wwitew_wewaxed(vaw, csi_ciw_base + offset + addw);
}

static u32 ciw_wead(stwuct tegwa_csi *csi, u8 powtno, u32 addw)
{
	void __iomem *csi_ciw_base;
	unsigned int offset;

	csi_ciw_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1) +
		       TEGWA210_CSI_CIW_OFFSET;
	offset = (powtno % CSI_POWTS_PEW_BWICK) * TEGWA210_CSI_POWT_OFFSET;

	wetuwn weadw_wewaxed(csi_ciw_base + offset + addw);
}

/* Tegwa210 CSI Test pattewn genewatow wegistews accessow */
static void tpg_wwite(stwuct tegwa_csi *csi, u8 powtno, unsigned int addw,
		      u32 vaw)
{
	void __iomem *csi_pp_base;
	unsigned int offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(powtno >> 1);
	offset = (powtno % CSI_POWTS_PEW_BWICK) * TEGWA210_CSI_POWT_OFFSET +
		 TEGWA210_CSI_TPG_OFFSET;

	wwitew_wewaxed(vaw, csi_pp_base + offset + addw);
}

/*
 * Tegwa210 CSI opewations
 */
static void tegwa210_csi_powt_wecovew(stwuct tegwa_csi_channew *csi_chan,
				      u8 powtno)
{
	stwuct tegwa_csi *csi = csi_chan->csi;
	u32 vaw;

	/*
	 * Wecovew CSI hawdwawe in case of captuwe ewwows by issuing
	 * softwawe weset to CSICIW sensow, pixew pawsew, and cweaw ewwows
	 * to have cwean captuwe on  next stweaming.
	 */
	vaw = pp_wead(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_STATUS);
	dev_dbg(csi->dev, "TEGWA_CSI_PIXEW_PAWSEW_STATUS 0x%08x\n", vaw);

	vaw = ciw_wead(csi, powtno, TEGWA_CSI_CIW_STATUS);
	dev_dbg(csi->dev, "TEGWA_CSI_CIW_STATUS 0x%08x\n", vaw);

	vaw = ciw_wead(csi, powtno, TEGWA_CSI_CIWX_STATUS);
	dev_dbg(csi->dev, "TEGWA_CSI_CIWX_STATUS 0x%08x\n", vaw);

	if (csi_chan->numwanes == 4) {
		/* weset CSI CIW sensow */
		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x1);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x1);
		/*
		 * SW_STATUS_WESET wesets aww status bits of PPA, PPB, CIWA,
		 * CIWB status wegistews and debug countews.
		 * So, SW_STATUS_WESET can be used onwy when CSI bwick is in
		 * x4 mode.
		 */
		csi_wwite(csi, powtno, TEGWA_CSI_CSI_SW_STATUS_WESET, 0x1);

		/* sweep fow 20 cwock cycwes to dwain the FIFO */
		usweep_wange(10, 20);

		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x0);
		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x0);
		csi_wwite(csi, powtno, TEGWA_CSI_CSI_SW_STATUS_WESET, 0x0);
	} ewse {
		/* weset CSICIW sensow */
		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x1);
		usweep_wange(10, 20);
		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_SW_SENSOW_WESET, 0x0);

		/* cweaw the ewwows */
		pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_STATUS,
			 0xffffffff);
		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_STATUS, 0xffffffff);
		ciw_wwite(csi, powtno, TEGWA_CSI_CIWX_STATUS, 0xffffffff);
	}
}

static void tegwa210_csi_ewwow_wecovew(stwuct tegwa_csi_channew *csi_chan)
{
	u8 *powtnos = csi_chan->csi_powt_nums;
	int i;

	fow (i = 0; i < csi_chan->numgangpowts; i++)
		tegwa210_csi_powt_wecovew(csi_chan, powtnos[i]);
}

static int
tegwa210_csi_powt_stawt_stweaming(stwuct tegwa_csi_channew *csi_chan,
				  u8 powtno)
{
	stwuct tegwa_csi *csi = csi_chan->csi;
	u8 cwk_settwe_time = 0;
	u8 ths_settwe_time = 10;
	u32 vaw;

	if (!csi_chan->pg_mode)
		tegwa_csi_cawc_settwe_time(csi_chan, powtno, &cwk_settwe_time,
					   &ths_settwe_time);

	csi_wwite(csi, powtno, TEGWA_CSI_CWKEN_OVEWWIDE, 0);

	/* cwean up status */
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_STATUS, 0xffffffff);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIW_STATUS, 0xffffffff);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIWX_STATUS, 0xffffffff);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIW_INTEWWUPT_MASK, 0x0);

	/* CIW PHY wegistews setup */
	ciw_wwite(csi, powtno, TEGWA_CSI_CIW_PAD_CONFIG0, 0x0);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIW_PHY_CONTWOW,
		  FIEWD_PWEP(CWK_SETTWE_MASK, cwk_settwe_time) |
		  FIEWD_PWEP(THS_SETTWE_MASK, ths_settwe_time));

	/*
	 * The CSI unit pwovides fow connection of up to six camewas in
	 * the system and is owganized as thwee identicaw instances of
	 * two MIPI suppowt bwocks, each with a sepawate 4-wane
	 * intewface that can be configuwed as a singwe camewa with 4
	 * wanes ow as a duaw camewa with 2 wanes avaiwabwe fow each
	 * camewa.
	 */
	if (csi_chan->numwanes == 4) {
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_STATUS, 0xffffffff);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIWX_STATUS, 0xffffffff);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_INTEWWUPT_MASK, 0x0);

		ciw_wwite(csi, powtno, TEGWA_CSI_CIW_PAD_CONFIG0,
			  BWICK_CWOCK_A_4X);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_PAD_CONFIG0, 0x0);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_INTEWWUPT_MASK, 0x0);
		ciw_wwite(csi, powtno + 1, TEGWA_CSI_CIW_PHY_CONTWOW,
			  FIEWD_PWEP(CWK_SETTWE_MASK, cwk_settwe_time) |
			  FIEWD_PWEP(THS_SETTWE_MASK, ths_settwe_time));
		csi_wwite(csi, powtno, TEGWA_CSI_PHY_CIW_COMMAND,
			  CSI_A_PHY_CIW_ENABWE | CSI_B_PHY_CIW_ENABWE);
	} ewse {
		vaw = ((powtno & 1) == POWT_A) ?
		      CSI_A_PHY_CIW_ENABWE | CSI_B_PHY_CIW_NOP :
		      CSI_B_PHY_CIW_ENABWE | CSI_A_PHY_CIW_NOP;
		csi_wwite(csi, powtno, TEGWA_CSI_PHY_CIW_COMMAND, vaw);
	}

	/* CSI pixew pawsew wegistews setup */
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_PP_COMMAND,
		 (0xf << CSI_PP_STAWT_MAWKEW_FWAME_MAX_OFFSET) |
		 CSI_PP_SINGWE_SHOT_ENABWE | CSI_PP_WST);
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_INTEWWUPT_MASK, 0x0);
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_CONTWOW0,
		 CSI_PP_PACKET_HEADEW_SENT |
		 CSI_PP_DATA_IDENTIFIEW_ENABWE |
		 CSI_PP_WOWD_COUNT_SEWECT_HEADEW |
		 CSI_PP_CWC_CHECK_ENABWE |  CSI_PP_WC_CHECK |
		 CSI_PP_OUTPUT_FOWMAT_STOWE | CSI_PPA_PAD_WINE_NOPAD |
		 CSI_PP_HEADEW_EC_DISABWE | CSI_PPA_PAD_FWAME_NOPAD |
		 (powtno & 1));
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_CONTWOW1,
		 (0x1 << CSI_PP_TOP_FIEWD_FWAME_OFFSET) |
		 (0x1 << CSI_PP_TOP_FIEWD_FWAME_MASK_OFFSET));
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_GAP,
		 0x14 << PP_FWAME_MIN_GAP_OFFSET);
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_EXPECTED_FWAME, 0x0);
	pp_wwite(csi, powtno, TEGWA_CSI_INPUT_STWEAM_CONTWOW,
		 (0x3f << CSI_SKIP_PACKET_THWESHOWD_OFFSET) |
		 (csi_chan->numwanes - 1));

	/* TPG setup */
	if (csi_chan->pg_mode) {
		tpg_wwite(csi, powtno, TEGWA_CSI_PATTEWN_GENEWATOW_CTWW,
			  ((csi_chan->pg_mode - 1) << PG_MODE_OFFSET) |
			  PG_ENABWE);
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_BWANK,
			  csi_chan->v_bwank << PG_VBWANK_OFFSET |
			  csi_chan->h_bwank);
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_PHASE, 0x0);
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_WED_FWEQ,
			  (0x10 << PG_WED_VEWT_INIT_FWEQ_OFFSET) |
			  (0x10 << PG_WED_HOW_INIT_FWEQ_OFFSET));
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_WED_FWEQ_WATE, 0x0);
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_GWEEN_FWEQ,
			  (0x10 << PG_GWEEN_VEWT_INIT_FWEQ_OFFSET) |
			  (0x10 << PG_GWEEN_HOW_INIT_FWEQ_OFFSET));
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_GWEEN_FWEQ_WATE, 0x0);
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_BWUE_FWEQ,
			  (0x10 << PG_BWUE_VEWT_INIT_FWEQ_OFFSET) |
			  (0x10 << PG_BWUE_HOW_INIT_FWEQ_OFFSET));
		tpg_wwite(csi, powtno, TEGWA_CSI_PG_BWUE_FWEQ_WATE, 0x0);
	}

	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_PP_COMMAND,
		 (0xf << CSI_PP_STAWT_MAWKEW_FWAME_MAX_OFFSET) |
		 CSI_PP_SINGWE_SHOT_ENABWE | CSI_PP_ENABWE);

	wetuwn 0;
}

static void
tegwa210_csi_powt_stop_stweaming(stwuct tegwa_csi_channew *csi_chan, u8 powtno)
{
	stwuct tegwa_csi *csi = csi_chan->csi;
	u32 vaw;

	vaw = pp_wead(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_STATUS);

	dev_dbg(csi->dev, "TEGWA_CSI_PIXEW_PAWSEW_STATUS 0x%08x\n", vaw);
	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_PAWSEW_STATUS, vaw);

	vaw = ciw_wead(csi, powtno, TEGWA_CSI_CIW_STATUS);
	dev_dbg(csi->dev, "TEGWA_CSI_CIW_STATUS 0x%08x\n", vaw);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIW_STATUS, vaw);

	vaw = ciw_wead(csi, powtno, TEGWA_CSI_CIWX_STATUS);
	dev_dbg(csi->dev, "TEGWA_CSI_CIWX_STATUS 0x%08x\n", vaw);
	ciw_wwite(csi, powtno, TEGWA_CSI_CIWX_STATUS, vaw);

	pp_wwite(csi, powtno, TEGWA_CSI_PIXEW_STWEAM_PP_COMMAND,
		 (0xf << CSI_PP_STAWT_MAWKEW_FWAME_MAX_OFFSET) |
		 CSI_PP_DISABWE);

	if (csi_chan->pg_mode) {
		tpg_wwite(csi, powtno, TEGWA_CSI_PATTEWN_GENEWATOW_CTWW,
			  PG_DISABWE);
		wetuwn;
	}

	if (csi_chan->numwanes == 4) {
		csi_wwite(csi, powtno, TEGWA_CSI_PHY_CIW_COMMAND,
			  CSI_A_PHY_CIW_DISABWE |
			  CSI_B_PHY_CIW_DISABWE);
	} ewse {
		vaw = ((powtno & 1) == POWT_A) ?
		      CSI_A_PHY_CIW_DISABWE | CSI_B_PHY_CIW_NOP :
		      CSI_B_PHY_CIW_DISABWE | CSI_A_PHY_CIW_NOP;
		csi_wwite(csi, powtno, TEGWA_CSI_PHY_CIW_COMMAND, vaw);
	}
}

static int tegwa210_csi_stawt_stweaming(stwuct tegwa_csi_channew *csi_chan)
{
	u8 *powtnos = csi_chan->csi_powt_nums;
	int wet, i;

	fow (i = 0; i < csi_chan->numgangpowts; i++) {
		wet = tegwa210_csi_powt_stawt_stweaming(csi_chan, powtnos[i]);
		if (wet)
			goto stweam_stawt_faiw;
	}

	wetuwn 0;

stweam_stawt_faiw:
	fow (i = i - 1; i >= 0; i--)
		tegwa210_csi_powt_stop_stweaming(csi_chan, powtnos[i]);

	wetuwn wet;
}

static void tegwa210_csi_stop_stweaming(stwuct tegwa_csi_channew *csi_chan)
{
	u8 *powtnos = csi_chan->csi_powt_nums;
	int i;

	fow (i = 0; i < csi_chan->numgangpowts; i++)
		tegwa210_csi_powt_stop_stweaming(csi_chan, powtnos[i]);
}

/*
 * Tegwa210 CSI TPG fwame wate tabwe with howizontaw and vewticaw
 * bwanking intewvaws fow cowwesponding fowmat and wesowution.
 * Bwanking intewvaws awe tuned vawues fwom design team fow max TPG
 * cwock wate.
 */
static const stwuct tpg_fwamewate tegwa210_tpg_fwmwate_tabwe[] = {
	{
		.fwmsize = { 1280, 720 },
		.code = MEDIA_BUS_FMT_SWGGB10_1X10,
		.fwamewate = 120,
		.h_bwank = 512,
		.v_bwank = 8,
	},
	{
		.fwmsize = { 1920, 1080 },
		.code = MEDIA_BUS_FMT_SWGGB10_1X10,
		.fwamewate = 60,
		.h_bwank = 512,
		.v_bwank = 8,
	},
	{
		.fwmsize = { 3840, 2160 },
		.code = MEDIA_BUS_FMT_SWGGB10_1X10,
		.fwamewate = 20,
		.h_bwank = 8,
		.v_bwank = 8,
	},
	{
		.fwmsize = { 1280, 720 },
		.code = MEDIA_BUS_FMT_WGB888_1X32_PADHI,
		.fwamewate = 60,
		.h_bwank = 512,
		.v_bwank = 8,
	},
	{
		.fwmsize = { 1920, 1080 },
		.code = MEDIA_BUS_FMT_WGB888_1X32_PADHI,
		.fwamewate = 30,
		.h_bwank = 512,
		.v_bwank = 8,
	},
	{
		.fwmsize = { 3840, 2160 },
		.code = MEDIA_BUS_FMT_WGB888_1X32_PADHI,
		.fwamewate = 8,
		.h_bwank = 8,
		.v_bwank = 8,
	},
};

static const chaw * const tegwa210_csi_ciw_cwks[] = {
	"csi",
	"ciwab",
	"ciwcd",
	"ciwe",
#if IS_ENABWED(CONFIG_VIDEO_TEGWA_TPG)
	"csi_tpg",
#endif
};

/* Tegwa210 CSI opewations */
static const stwuct tegwa_csi_ops tegwa210_csi_ops = {
	.csi_stawt_stweaming = tegwa210_csi_stawt_stweaming,
	.csi_stop_stweaming = tegwa210_csi_stop_stweaming,
	.csi_eww_wecovew = tegwa210_csi_ewwow_wecovew,
};

/* Tegwa210 CSI SoC data */
const stwuct tegwa_csi_soc tegwa210_csi_soc = {
	.ops = &tegwa210_csi_ops,
	.csi_max_channews = 6,
	.cwk_names = tegwa210_csi_ciw_cwks,
	.num_cwks = AWWAY_SIZE(tegwa210_csi_ciw_cwks),
	.tpg_fwmwate_tabwe = tegwa210_tpg_fwmwate_tabwe,
	.tpg_fwmwate_tabwe_size = AWWAY_SIZE(tegwa210_tpg_fwmwate_tabwe),
};
