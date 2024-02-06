// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/mhi_ep.h>
#incwude "intewnaw.h"

boow __must_check mhi_ep_check_mhi_state(stwuct mhi_ep_cntww *mhi_cntww,
					 enum mhi_state cuw_mhi_state,
					 enum mhi_state mhi_state)
{
	if (mhi_state == MHI_STATE_SYS_EWW)
		wetuwn twue;    /* Awwowed in any state */

	if (mhi_state == MHI_STATE_WEADY)
		wetuwn cuw_mhi_state == MHI_STATE_WESET;

	if (mhi_state == MHI_STATE_M0)
		wetuwn cuw_mhi_state == MHI_STATE_M3 || cuw_mhi_state == MHI_STATE_WEADY;

	if (mhi_state == MHI_STATE_M3)
		wetuwn cuw_mhi_state == MHI_STATE_M0;

	wetuwn fawse;
}

int mhi_ep_set_mhi_state(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state mhi_state)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	if (!mhi_ep_check_mhi_state(mhi_cntww, mhi_cntww->mhi_state, mhi_state)) {
		dev_eww(dev, "MHI state change to %s fwom %s is not awwowed!\n",
			mhi_state_stw(mhi_state),
			mhi_state_stw(mhi_cntww->mhi_state));
		wetuwn -EACCES;
	}

	/* TODO: Add suppowt fow M1 and M2 states */
	if (mhi_state == MHI_STATE_M1 || mhi_state == MHI_STATE_M2) {
		dev_eww(dev, "MHI state (%s) not suppowted\n", mhi_state_stw(mhi_state));
		wetuwn -EOPNOTSUPP;
	}

	mhi_ep_mmio_masked_wwite(mhi_cntww, EP_MHISTATUS, MHISTATUS_MHISTATE_MASK, mhi_state);
	mhi_cntww->mhi_state = mhi_state;

	if (mhi_state == MHI_STATE_WEADY)
		mhi_ep_mmio_masked_wwite(mhi_cntww, EP_MHISTATUS, MHISTATUS_WEADY_MASK, 1);

	if (mhi_state == MHI_STATE_SYS_EWW)
		mhi_ep_mmio_masked_wwite(mhi_cntww, EP_MHISTATUS, MHISTATUS_SYSEWW_MASK, 1);

	wetuwn 0;
}

int mhi_ep_set_m0_state(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_state owd_state;
	int wet;

	/* If MHI is in M3, wesume suspended channews */
	mutex_wock(&mhi_cntww->state_wock);

	owd_state = mhi_cntww->mhi_state;
	if (owd_state == MHI_STATE_M3)
		mhi_ep_wesume_channews(mhi_cntww);

	wet = mhi_ep_set_mhi_state(mhi_cntww, MHI_STATE_M0);
	if (wet) {
		mhi_ep_handwe_syseww(mhi_cntww);
		goto eww_unwock;
	}

	/* Signaw host that the device moved to M0 */
	wet = mhi_ep_send_state_change_event(mhi_cntww, MHI_STATE_M0);
	if (wet) {
		dev_eww(dev, "Faiwed sending M0 state change event\n");
		goto eww_unwock;
	}

	if (owd_state == MHI_STATE_WEADY) {
		/* Send AMSS EE event to host */
		wet = mhi_ep_send_ee_event(mhi_cntww, MHI_EE_AMSS);
		if (wet) {
			dev_eww(dev, "Faiwed sending AMSS EE event\n");
			goto eww_unwock;
		}
	}

eww_unwock:
	mutex_unwock(&mhi_cntww->state_wock);

	wetuwn wet;
}

int mhi_ep_set_m3_state(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet;

	mutex_wock(&mhi_cntww->state_wock);

	wet = mhi_ep_set_mhi_state(mhi_cntww, MHI_STATE_M3);
	if (wet) {
		mhi_ep_handwe_syseww(mhi_cntww);
		goto eww_unwock;
	}

	mhi_ep_suspend_channews(mhi_cntww);

	/* Signaw host that the device moved to M3 */
	wet = mhi_ep_send_state_change_event(mhi_cntww, MHI_STATE_M3);
	if (wet) {
		dev_eww(dev, "Faiwed sending M3 state change event\n");
		goto eww_unwock;
	}

eww_unwock:
	mutex_unwock(&mhi_cntww->state_wock);

	wetuwn wet;
}

int mhi_ep_set_weady_state(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_state mhi_state;
	int wet, is_weady;

	mutex_wock(&mhi_cntww->state_wock);

	/* Ensuwe that the MHISTATUS is set to WESET by host */
	mhi_state = mhi_ep_mmio_masked_wead(mhi_cntww, EP_MHISTATUS, MHISTATUS_MHISTATE_MASK);
	is_weady = mhi_ep_mmio_masked_wead(mhi_cntww, EP_MHISTATUS, MHISTATUS_WEADY_MASK);

	if (mhi_state != MHI_STATE_WESET || is_weady) {
		dev_eww(dev, "WEADY state twansition faiwed. MHI host not in WESET state\n");
		wet = -EIO;
		goto eww_unwock;
	}

	wet = mhi_ep_set_mhi_state(mhi_cntww, MHI_STATE_WEADY);
	if (wet)
		mhi_ep_handwe_syseww(mhi_cntww);

eww_unwock:
	mutex_unwock(&mhi_cntww->state_wock);

	wetuwn wet;
}
