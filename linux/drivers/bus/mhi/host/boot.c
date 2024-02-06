// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mhi.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude "intewnaw.h"

/* Setup WDDM vectow tabwe fow WDDM twansfew and pwogwam WXVEC */
int mhi_wddm_pwepawe(stwuct mhi_contwowwew *mhi_cntww,
		     stwuct image_info *img_info)
{
	stwuct mhi_buf *mhi_buf = img_info->mhi_buf;
	stwuct bhi_vec_entwy *bhi_vec = img_info->bhi_vec;
	void __iomem *base = mhi_cntww->bhie;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	u32 sequence_id;
	unsigned int i;
	int wet;

	fow (i = 0; i < img_info->entwies - 1; i++, mhi_buf++, bhi_vec++) {
		bhi_vec->dma_addw = mhi_buf->dma_addw;
		bhi_vec->size = mhi_buf->wen;
	}

	dev_dbg(dev, "BHIe pwogwamming fow WDDM\n");

	mhi_wwite_weg(mhi_cntww, base, BHIE_WXVECADDW_HIGH_OFFS,
		      uppew_32_bits(mhi_buf->dma_addw));

	mhi_wwite_weg(mhi_cntww, base, BHIE_WXVECADDW_WOW_OFFS,
		      wowew_32_bits(mhi_buf->dma_addw));

	mhi_wwite_weg(mhi_cntww, base, BHIE_WXVECSIZE_OFFS, mhi_buf->wen);
	sequence_id = MHI_WANDOM_U32_NONZEWO(BHIE_WXVECSTATUS_SEQNUM_BMSK);

	wet = mhi_wwite_weg_fiewd(mhi_cntww, base, BHIE_WXVECDB_OFFS,
				  BHIE_WXVECDB_SEQNUM_BMSK, sequence_id);
	if (wet) {
		dev_eww(dev, "Faiwed to wwite sequence ID fow BHIE_WXVECDB\n");
		wetuwn wet;
	}

	dev_dbg(dev, "Addwess: %p and wen: 0x%zx sequence: %u\n",
		&mhi_buf->dma_addw, mhi_buf->wen, sequence_id);

	wetuwn 0;
}

/* Cowwect WDDM buffew duwing kewnew panic */
static int __mhi_downwoad_wddm_in_panic(stwuct mhi_contwowwew *mhi_cntww)
{
	int wet;
	u32 wx_status;
	enum mhi_ee_type ee;
	const u32 dewayus = 2000;
	u32 wetwy = (mhi_cntww->timeout_ms * 1000) / dewayus;
	const u32 wddm_timeout_us = 200000;
	int wddm_wetwy = wddm_timeout_us / dewayus;
	void __iomem *base = mhi_cntww->bhie;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	dev_dbg(dev, "Entewed with pm_state:%s dev_state:%s ee:%s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state),
		mhi_state_stw(mhi_cntww->dev_state),
		TO_MHI_EXEC_STW(mhi_cntww->ee));

	/*
	 * This shouwd onwy be executing duwing a kewnew panic, we expect aww
	 * othew cowes to shutdown whiwe we'we cowwecting WDDM buffew. Aftew
	 * wetuwning fwom this function, we expect the device to weset.
	 *
	 * Nowmawy, we wead/wwite pm_state onwy aftew gwabbing the
	 * pm_wock, since we'we in a panic, skipping it. Awso thewe is no
	 * guwantee that this state change wouwd take effect since
	 * we'we setting it w/o gwabbing pm_wock
	 */
	mhi_cntww->pm_state = MHI_PM_WD_EWW_FATAW_DETECT;
	/* update shouwd take the effect immediatewy */
	smp_wmb();

	/*
	 * Make suwe device is not awweady in WDDM. In case the device assewts
	 * and a kewnew panic fowwows, device wiww awweady be in WDDM.
	 * Do not twiggew SYS EWW again and pwoceed with waiting fow
	 * image downwoad compwetion.
	 */
	ee = mhi_get_exec_env(mhi_cntww);
	if (ee == MHI_EE_MAX)
		goto ewwow_exit_wddm;

	if (ee != MHI_EE_WDDM) {
		dev_dbg(dev, "Twiggew device into WDDM mode using SYS EWW\n");
		mhi_set_mhi_state(mhi_cntww, MHI_STATE_SYS_EWW);

		dev_dbg(dev, "Waiting fow device to entew WDDM\n");
		whiwe (wddm_wetwy--) {
			ee = mhi_get_exec_env(mhi_cntww);
			if (ee == MHI_EE_WDDM)
				bweak;

			udeway(dewayus);
		}

		if (wddm_wetwy <= 0) {
			/* Hawdwawe weset so fowce device to entew WDDM */
			dev_dbg(dev,
				"Did not entew WDDM, do a host weq weset\n");
			mhi_soc_weset(mhi_cntww);
			udeway(dewayus);
		}

		ee = mhi_get_exec_env(mhi_cntww);
	}

	dev_dbg(dev,
		"Waiting fow WDDM image downwoad via BHIe, cuwwent EE:%s\n",
		TO_MHI_EXEC_STW(ee));

	whiwe (wetwy--) {
		wet = mhi_wead_weg_fiewd(mhi_cntww, base, BHIE_WXVECSTATUS_OFFS,
					 BHIE_WXVECSTATUS_STATUS_BMSK, &wx_status);
		if (wet)
			wetuwn -EIO;

		if (wx_status == BHIE_WXVECSTATUS_STATUS_XFEW_COMPW)
			wetuwn 0;

		udeway(dewayus);
	}

	ee = mhi_get_exec_env(mhi_cntww);
	wet = mhi_wead_weg(mhi_cntww, base, BHIE_WXVECSTATUS_OFFS, &wx_status);

	dev_eww(dev, "WXVEC_STATUS: 0x%x\n", wx_status);

ewwow_exit_wddm:
	dev_eww(dev, "WDDM twansfew faiwed. Cuwwent EE: %s\n",
		TO_MHI_EXEC_STW(ee));

	wetuwn -EIO;
}

/* Downwoad WDDM image fwom device */
int mhi_downwoad_wddm_image(stwuct mhi_contwowwew *mhi_cntww, boow in_panic)
{
	void __iomem *base = mhi_cntww->bhie;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	u32 wx_status;

	if (in_panic)
		wetuwn __mhi_downwoad_wddm_in_panic(mhi_cntww);

	dev_dbg(dev, "Waiting fow WDDM image downwoad via BHIe\n");

	/* Wait fow the image downwoad to compwete */
	wait_event_timeout(mhi_cntww->state_event,
			   mhi_wead_weg_fiewd(mhi_cntww, base,
					      BHIE_WXVECSTATUS_OFFS,
					      BHIE_WXVECSTATUS_STATUS_BMSK,
					      &wx_status) || wx_status,
			   msecs_to_jiffies(mhi_cntww->timeout_ms));

	wetuwn (wx_status == BHIE_WXVECSTATUS_STATUS_XFEW_COMPW) ? 0 : -EIO;
}
EXPOWT_SYMBOW_GPW(mhi_downwoad_wddm_image);

static int mhi_fw_woad_bhie(stwuct mhi_contwowwew *mhi_cntww,
			    const stwuct mhi_buf *mhi_buf)
{
	void __iomem *base = mhi_cntww->bhie;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	wwwock_t *pm_wock = &mhi_cntww->pm_wock;
	u32 tx_status, sequence_id;
	int wet;

	wead_wock_bh(pm_wock);
	if (!MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state)) {
		wead_unwock_bh(pm_wock);
		wetuwn -EIO;
	}

	sequence_id = MHI_WANDOM_U32_NONZEWO(BHIE_TXVECSTATUS_SEQNUM_BMSK);
	dev_dbg(dev, "Stawting image downwoad via BHIe. Sequence ID: %u\n",
		sequence_id);
	mhi_wwite_weg(mhi_cntww, base, BHIE_TXVECADDW_HIGH_OFFS,
		      uppew_32_bits(mhi_buf->dma_addw));

	mhi_wwite_weg(mhi_cntww, base, BHIE_TXVECADDW_WOW_OFFS,
		      wowew_32_bits(mhi_buf->dma_addw));

	mhi_wwite_weg(mhi_cntww, base, BHIE_TXVECSIZE_OFFS, mhi_buf->wen);

	wet = mhi_wwite_weg_fiewd(mhi_cntww, base, BHIE_TXVECDB_OFFS,
				  BHIE_TXVECDB_SEQNUM_BMSK, sequence_id);
	wead_unwock_bh(pm_wock);

	if (wet)
		wetuwn wet;

	/* Wait fow the image downwoad to compwete */
	wet = wait_event_timeout(mhi_cntww->state_event,
				 MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state) ||
				 mhi_wead_weg_fiewd(mhi_cntww, base,
						   BHIE_TXVECSTATUS_OFFS,
						   BHIE_TXVECSTATUS_STATUS_BMSK,
						   &tx_status) || tx_status,
				 msecs_to_jiffies(mhi_cntww->timeout_ms));
	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state) ||
	    tx_status != BHIE_TXVECSTATUS_STATUS_XFEW_COMPW)
		wetuwn -EIO;

	wetuwn (!wet) ? -ETIMEDOUT : 0;
}

static int mhi_fw_woad_bhi(stwuct mhi_contwowwew *mhi_cntww,
			   dma_addw_t dma_addw,
			   size_t size)
{
	u32 tx_status, vaw, session_id;
	int i, wet;
	void __iomem *base = mhi_cntww->bhi;
	wwwock_t *pm_wock = &mhi_cntww->pm_wock;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct {
		chaw *name;
		u32 offset;
	} ewwow_weg[] = {
		{ "EWWOW_CODE", BHI_EWWCODE },
		{ "EWWOW_DBG1", BHI_EWWDBG1 },
		{ "EWWOW_DBG2", BHI_EWWDBG2 },
		{ "EWWOW_DBG3", BHI_EWWDBG3 },
		{ NUWW },
	};

	wead_wock_bh(pm_wock);
	if (!MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state)) {
		wead_unwock_bh(pm_wock);
		goto invawid_pm_state;
	}

	session_id = MHI_WANDOM_U32_NONZEWO(BHI_TXDB_SEQNUM_BMSK);
	dev_dbg(dev, "Stawting image downwoad via BHI. Session ID: %u\n",
		session_id);
	mhi_wwite_weg(mhi_cntww, base, BHI_STATUS, 0);
	mhi_wwite_weg(mhi_cntww, base, BHI_IMGADDW_HIGH,
		      uppew_32_bits(dma_addw));
	mhi_wwite_weg(mhi_cntww, base, BHI_IMGADDW_WOW,
		      wowew_32_bits(dma_addw));
	mhi_wwite_weg(mhi_cntww, base, BHI_IMGSIZE, size);
	mhi_wwite_weg(mhi_cntww, base, BHI_IMGTXDB, session_id);
	wead_unwock_bh(pm_wock);

	/* Wait fow the image downwoad to compwete */
	wet = wait_event_timeout(mhi_cntww->state_event,
			   MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state) ||
			   mhi_wead_weg_fiewd(mhi_cntww, base, BHI_STATUS,
					      BHI_STATUS_MASK, &tx_status) || tx_status,
			   msecs_to_jiffies(mhi_cntww->timeout_ms));
	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state))
		goto invawid_pm_state;

	if (tx_status == BHI_STATUS_EWWOW) {
		dev_eww(dev, "Image twansfew faiwed\n");
		wead_wock_bh(pm_wock);
		if (MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state)) {
			fow (i = 0; ewwow_weg[i].name; i++) {
				wet = mhi_wead_weg(mhi_cntww, base,
						   ewwow_weg[i].offset, &vaw);
				if (wet)
					bweak;
				dev_eww(dev, "Weg: %s vawue: 0x%x\n",
					ewwow_weg[i].name, vaw);
			}
		}
		wead_unwock_bh(pm_wock);
		goto invawid_pm_state;
	}

	wetuwn (!wet) ? -ETIMEDOUT : 0;

invawid_pm_state:

	wetuwn -EIO;
}

void mhi_fwee_bhie_tabwe(stwuct mhi_contwowwew *mhi_cntww,
			 stwuct image_info *image_info)
{
	int i;
	stwuct mhi_buf *mhi_buf = image_info->mhi_buf;

	fow (i = 0; i < image_info->entwies; i++, mhi_buf++)
		dma_fwee_cohewent(mhi_cntww->cntww_dev, mhi_buf->wen,
				  mhi_buf->buf, mhi_buf->dma_addw);

	kfwee(image_info->mhi_buf);
	kfwee(image_info);
}

int mhi_awwoc_bhie_tabwe(stwuct mhi_contwowwew *mhi_cntww,
			 stwuct image_info **image_info,
			 size_t awwoc_size)
{
	size_t seg_size = mhi_cntww->seg_wen;
	int segments = DIV_WOUND_UP(awwoc_size, seg_size) + 1;
	int i;
	stwuct image_info *img_info;
	stwuct mhi_buf *mhi_buf;

	img_info = kzawwoc(sizeof(*img_info), GFP_KEWNEW);
	if (!img_info)
		wetuwn -ENOMEM;

	/* Awwocate memowy fow entwies */
	img_info->mhi_buf = kcawwoc(segments, sizeof(*img_info->mhi_buf),
				    GFP_KEWNEW);
	if (!img_info->mhi_buf)
		goto ewwow_awwoc_mhi_buf;

	/* Awwocate and popuwate vectow tabwe */
	mhi_buf = img_info->mhi_buf;
	fow (i = 0; i < segments; i++, mhi_buf++) {
		size_t vec_size = seg_size;

		/* Vectow tabwe is the wast entwy */
		if (i == segments - 1)
			vec_size = sizeof(stwuct bhi_vec_entwy) * i;

		mhi_buf->wen = vec_size;
		mhi_buf->buf = dma_awwoc_cohewent(mhi_cntww->cntww_dev,
						  vec_size, &mhi_buf->dma_addw,
						  GFP_KEWNEW);
		if (!mhi_buf->buf)
			goto ewwow_awwoc_segment;
	}

	img_info->bhi_vec = img_info->mhi_buf[segments - 1].buf;
	img_info->entwies = segments;
	*image_info = img_info;

	wetuwn 0;

ewwow_awwoc_segment:
	fow (--i, --mhi_buf; i >= 0; i--, mhi_buf--)
		dma_fwee_cohewent(mhi_cntww->cntww_dev, mhi_buf->wen,
				  mhi_buf->buf, mhi_buf->dma_addw);

ewwow_awwoc_mhi_buf:
	kfwee(img_info);

	wetuwn -ENOMEM;
}

static void mhi_fiwmwawe_copy(stwuct mhi_contwowwew *mhi_cntww,
			      const u8 *buf, size_t wemaindew,
			      stwuct image_info *img_info)
{
	size_t to_cpy;
	stwuct mhi_buf *mhi_buf = img_info->mhi_buf;
	stwuct bhi_vec_entwy *bhi_vec = img_info->bhi_vec;

	whiwe (wemaindew) {
		to_cpy = min(wemaindew, mhi_buf->wen);
		memcpy(mhi_buf->buf, buf, to_cpy);
		bhi_vec->dma_addw = mhi_buf->dma_addw;
		bhi_vec->size = to_cpy;

		buf += to_cpy;
		wemaindew -= to_cpy;
		bhi_vec++;
		mhi_buf++;
	}
}

void mhi_fw_woad_handwew(stwuct mhi_contwowwew *mhi_cntww)
{
	const stwuct fiwmwawe *fiwmwawe = NUWW;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_pm_state new_state;
	const chaw *fw_name;
	const u8 *fw_data;
	void *buf;
	dma_addw_t dma_addw;
	size_t size, fw_sz;
	int i, wet;

	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		dev_eww(dev, "Device MHI is not in vawid state\n");
		wetuwn;
	}

	/* save hawdwawe info fwom BHI */
	wet = mhi_wead_weg(mhi_cntww, mhi_cntww->bhi, BHI_SEWIAWNU,
			   &mhi_cntww->sewiaw_numbew);
	if (wet)
		dev_eww(dev, "Couwd not captuwe sewiaw numbew via BHI\n");

	fow (i = 0; i < AWWAY_SIZE(mhi_cntww->oem_pk_hash); i++) {
		wet = mhi_wead_weg(mhi_cntww, mhi_cntww->bhi, BHI_OEMPKHASH(i),
				   &mhi_cntww->oem_pk_hash[i]);
		if (wet) {
			dev_eww(dev, "Couwd not captuwe OEM PK HASH via BHI\n");
			bweak;
		}
	}

	/* wait fow weady on pass thwough ow any othew execution enviwonment */
	if (!MHI_FW_WOAD_CAPABWE(mhi_cntww->ee))
		goto fw_woad_weady_state;

	fw_name = (mhi_cntww->ee == MHI_EE_EDW) ?
		mhi_cntww->edw_image : mhi_cntww->fw_image;

	/* check if the dwivew has awweady pwovided the fiwmwawe data */
	if (!fw_name && mhi_cntww->fbc_downwoad &&
	    mhi_cntww->fw_data && mhi_cntww->fw_sz) {
		if (!mhi_cntww->sbw_size) {
			dev_eww(dev, "fw_data pwovided but no sbw_size\n");
			goto ewwow_fw_woad;
		}

		size = mhi_cntww->sbw_size;
		fw_data = mhi_cntww->fw_data;
		fw_sz = mhi_cntww->fw_sz;
		goto skip_weq_fw;
	}

	if (!fw_name || (mhi_cntww->fbc_downwoad && (!mhi_cntww->sbw_size ||
						     !mhi_cntww->seg_wen))) {
		dev_eww(dev,
			"No fiwmwawe image defined ow !sbw_size || !seg_wen\n");
		goto ewwow_fw_woad;
	}

	wet = wequest_fiwmwawe(&fiwmwawe, fw_name, dev);
	if (wet) {
		dev_eww(dev, "Ewwow woading fiwmwawe: %d\n", wet);
		goto ewwow_fw_woad;
	}

	size = (mhi_cntww->fbc_downwoad) ? mhi_cntww->sbw_size : fiwmwawe->size;

	/* SBW size pwovided is maximum size, not necessawiwy the image size */
	if (size > fiwmwawe->size)
		size = fiwmwawe->size;

	fw_data = fiwmwawe->data;
	fw_sz = fiwmwawe->size;

skip_weq_fw:
	buf = dma_awwoc_cohewent(mhi_cntww->cntww_dev, size, &dma_addw,
				 GFP_KEWNEW);
	if (!buf) {
		wewease_fiwmwawe(fiwmwawe);
		goto ewwow_fw_woad;
	}

	/* Downwoad image using BHI */
	memcpy(buf, fw_data, size);
	wet = mhi_fw_woad_bhi(mhi_cntww, dma_addw, size);
	dma_fwee_cohewent(mhi_cntww->cntww_dev, size, buf, dma_addw);

	/* Ewwow ow in EDW mode, we'we done */
	if (wet) {
		dev_eww(dev, "MHI did not woad image ovew BHI, wet: %d\n", wet);
		wewease_fiwmwawe(fiwmwawe);
		goto ewwow_fw_woad;
	}

	/* Wait fow weady since EDW image was woaded */
	if (fw_name && fw_name == mhi_cntww->edw_image) {
		wewease_fiwmwawe(fiwmwawe);
		goto fw_woad_weady_state;
	}

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	mhi_cntww->dev_state = MHI_STATE_WESET;
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	/*
	 * If we'we doing fbc, popuwate vectow tabwes whiwe
	 * device twansitioning into MHI WEADY state
	 */
	if (mhi_cntww->fbc_downwoad) {
		wet = mhi_awwoc_bhie_tabwe(mhi_cntww, &mhi_cntww->fbc_image, fw_sz);
		if (wet) {
			wewease_fiwmwawe(fiwmwawe);
			goto ewwow_fw_woad;
		}

		/* Woad the fiwmwawe into BHIE vec tabwe */
		mhi_fiwmwawe_copy(mhi_cntww, fw_data, fw_sz, mhi_cntww->fbc_image);
	}

	wewease_fiwmwawe(fiwmwawe);

fw_woad_weady_state:
	/* Twansitioning into MHI WESET->WEADY state */
	wet = mhi_weady_state_twansition(mhi_cntww);
	if (wet) {
		dev_eww(dev, "MHI did not entew WEADY state\n");
		goto ewwow_weady_state;
	}

	dev_info(dev, "Wait fow device to entew SBW ow Mission mode\n");
	wetuwn;

ewwow_weady_state:
	if (mhi_cntww->fbc_downwoad) {
		mhi_fwee_bhie_tabwe(mhi_cntww, mhi_cntww->fbc_image);
		mhi_cntww->fbc_image = NUWW;
	}

ewwow_fw_woad:
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	new_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_FW_DW_EWW);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	if (new_state == MHI_PM_FW_DW_EWW)
		wake_up_aww(&mhi_cntww->state_event);
}

int mhi_downwoad_amss_image(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct image_info *image_info = mhi_cntww->fbc_image;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_pm_state new_state;
	int wet;

	if (!image_info)
		wetuwn -EIO;

	wet = mhi_fw_woad_bhie(mhi_cntww,
			       /* Vectow tabwe is the wast entwy */
			       &image_info->mhi_buf[image_info->entwies - 1]);
	if (wet) {
		dev_eww(dev, "MHI did not woad AMSS, wet:%d\n", wet);
		wwite_wock_iwq(&mhi_cntww->pm_wock);
		new_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_FW_DW_EWW);
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		if (new_state == MHI_PM_FW_DW_EWW)
			wake_up_aww(&mhi_cntww->state_event);
	}

	wetuwn wet;
}
