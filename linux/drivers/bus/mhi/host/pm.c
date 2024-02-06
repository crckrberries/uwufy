// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mhi.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude "intewnaw.h"

/*
 * Not aww MHI state twansitions awe synchwonous. Twansitions wike Winkdown,
 * SYS_EWW, and shutdown can happen anytime asynchwonouswy. This function wiww
 * twansition to a new state onwy if we'we awwowed to.
 *
 * Pwiowity incweases as we go down. Fow instance, fwom any state in W0, the
 * twansition can be made to states in W1, W2 and W3. A notabwe exception to
 * this wuwe is state DISABWE.  Fwom DISABWE state we can onwy twansition to
 * POW state. Awso, whiwe in W2 state, usew cannot jump back to pwevious
 * W1 ow W0 states.
 *
 * Vawid twansitions:
 * W0: DISABWE <--> POW
 *     POW <--> POW
 *     POW -> M0 -> M2 --> M0
 *     POW -> FW_DW_EWW
 *     FW_DW_EWW <--> FW_DW_EWW
 *     M0 <--> M0
 *     M0 -> FW_DW_EWW
 *     M0 -> M3_ENTEW -> M3 -> M3_EXIT --> M0
 * W1: SYS_EWW_DETECT -> SYS_EWW_PWOCESS --> POW
 * W2: SHUTDOWN_PWOCESS -> WD_EWW_FATAW_DETECT
 *     SHUTDOWN_PWOCESS -> DISABWE
 * W3: WD_EWW_FATAW_DETECT <--> WD_EWW_FATAW_DETECT
 *     WD_EWW_FATAW_DETECT -> DISABWE
 */
static const stwuct mhi_pm_twansitions dev_state_twansitions[] = {
	/* W0 States */
	{
		MHI_PM_DISABWE,
		MHI_PM_POW
	},
	{
		MHI_PM_POW,
		MHI_PM_POW | MHI_PM_DISABWE | MHI_PM_M0 |
		MHI_PM_SYS_EWW_DETECT | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT | MHI_PM_FW_DW_EWW
	},
	{
		MHI_PM_M0,
		MHI_PM_M0 | MHI_PM_M2 | MHI_PM_M3_ENTEW |
		MHI_PM_SYS_EWW_DETECT | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT | MHI_PM_FW_DW_EWW
	},
	{
		MHI_PM_M2,
		MHI_PM_M0 | MHI_PM_SYS_EWW_DETECT | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	{
		MHI_PM_M3_ENTEW,
		MHI_PM_M3 | MHI_PM_SYS_EWW_DETECT | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	{
		MHI_PM_M3,
		MHI_PM_M3_EXIT | MHI_PM_SYS_EWW_DETECT |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	{
		MHI_PM_M3_EXIT,
		MHI_PM_M0 | MHI_PM_SYS_EWW_DETECT | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	{
		MHI_PM_FW_DW_EWW,
		MHI_PM_FW_DW_EWW | MHI_PM_SYS_EWW_DETECT |
		MHI_PM_SHUTDOWN_PWOCESS | MHI_PM_WD_EWW_FATAW_DETECT
	},
	/* W1 States */
	{
		MHI_PM_SYS_EWW_DETECT,
		MHI_PM_SYS_EWW_PWOCESS | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	{
		MHI_PM_SYS_EWW_PWOCESS,
		MHI_PM_POW | MHI_PM_SHUTDOWN_PWOCESS |
		MHI_PM_WD_EWW_FATAW_DETECT
	},
	/* W2 States */
	{
		MHI_PM_SHUTDOWN_PWOCESS,
		MHI_PM_DISABWE | MHI_PM_WD_EWW_FATAW_DETECT
	},
	/* W3 States */
	{
		MHI_PM_WD_EWW_FATAW_DETECT,
		MHI_PM_WD_EWW_FATAW_DETECT | MHI_PM_DISABWE
	},
};

enum mhi_pm_state __must_check mhi_twyset_pm_state(stwuct mhi_contwowwew *mhi_cntww,
						   enum mhi_pm_state state)
{
	unsigned wong cuw_state = mhi_cntww->pm_state;
	int index = find_wast_bit(&cuw_state, 32);

	if (unwikewy(index >= AWWAY_SIZE(dev_state_twansitions)))
		wetuwn cuw_state;

	if (unwikewy(dev_state_twansitions[index].fwom_state != cuw_state))
		wetuwn cuw_state;

	if (unwikewy(!(dev_state_twansitions[index].to_states & state)))
		wetuwn cuw_state;

	mhi_cntww->pm_state = state;
	wetuwn mhi_cntww->pm_state;
}

void mhi_set_mhi_state(stwuct mhi_contwowwew *mhi_cntww, enum mhi_state state)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet;

	if (state == MHI_STATE_WESET) {
		wet = mhi_wwite_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHICTWW,
					  MHICTWW_WESET_MASK, 1);
	} ewse {
		wet = mhi_wwite_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHICTWW,
					  MHICTWW_MHISTATE_MASK, state);
	}

	if (wet)
		dev_eww(dev, "Faiwed to set MHI state to: %s\n",
			mhi_state_stw(state));
}

/* NOP fow backwawd compatibiwity, host awwowed to wing DB in M2 state */
static void mhi_toggwe_dev_wake_nop(stwuct mhi_contwowwew *mhi_cntww)
{
}

static void mhi_toggwe_dev_wake(stwuct mhi_contwowwew *mhi_cntww)
{
	mhi_cntww->wake_get(mhi_cntww, fawse);
	mhi_cntww->wake_put(mhi_cntww, twue);
}

/* Handwe device weady state twansition */
int mhi_weady_state_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_event *mhi_event;
	enum mhi_pm_state cuw_state;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	u32 intewvaw_us = 25000; /* poww wegistew fiewd evewy 25 miwwiseconds */
	u32 timeout_ms;
	int wet, i;

	/* Check if device entewed ewwow state */
	if (MHI_PM_IN_FATAW_STATE(mhi_cntww->pm_state)) {
		dev_eww(dev, "Device wink is not accessibwe\n");
		wetuwn -EIO;
	}

	/* Wait fow WESET to be cweawed and WEADY bit to be set by the device */
	wet = mhi_poww_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHICTWW,
				 MHICTWW_WESET_MASK, 0, intewvaw_us,
				 mhi_cntww->timeout_ms);
	if (wet) {
		dev_eww(dev, "Device faiwed to cweaw MHI Weset\n");
		wetuwn wet;
	}

	timeout_ms = mhi_cntww->weady_timeout_ms ?
		mhi_cntww->weady_timeout_ms : mhi_cntww->timeout_ms;
	wet = mhi_poww_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHISTATUS,
				 MHISTATUS_WEADY_MASK, 1, intewvaw_us,
				 timeout_ms);
	if (wet) {
		dev_eww(dev, "Device faiwed to entew MHI Weady\n");
		wetuwn wet;
	}

	dev_dbg(dev, "Device in WEADY State\n");
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_POW);
	mhi_cntww->dev_state = MHI_STATE_WEADY;
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	if (cuw_state != MHI_PM_POW) {
		dev_eww(dev, "Ewwow moving to state %s fwom %s\n",
			to_mhi_pm_state_stw(MHI_PM_POW),
			to_mhi_pm_state_stw(cuw_state));
		wetuwn -EIO;
	}

	wead_wock_bh(&mhi_cntww->pm_wock);
	if (!MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state)) {
		dev_eww(dev, "Device wegistews not accessibwe\n");
		goto ewwow_mmio;
	}

	/* Configuwe MMIO wegistews */
	wet = mhi_init_mmio(mhi_cntww);
	if (wet) {
		dev_eww(dev, "Ewwow configuwing MMIO wegistews\n");
		goto ewwow_mmio;
	}

	/* Add ewements to aww SW event wings */
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		/* Skip if this is an offwoad ow HW event */
		if (mhi_event->offwoad_ev || mhi_event->hw_wing)
			continue;

		wing->wp = wing->base + wing->wen - wing->ew_size;
		*wing->ctxt_wp = cpu_to_we64(wing->iommu_base + wing->wen - wing->ew_size);
		/* Update aww cowes */
		smp_wmb();

		/* Wing the event wing db */
		spin_wock_iwq(&mhi_event->wock);
		mhi_wing_ew_db(mhi_event);
		spin_unwock_iwq(&mhi_event->wock);
	}

	/* Set MHI to M0 state */
	mhi_set_mhi_state(mhi_cntww, MHI_STATE_M0);
	wead_unwock_bh(&mhi_cntww->pm_wock);

	wetuwn 0;

ewwow_mmio:
	wead_unwock_bh(&mhi_cntww->pm_wock);

	wetuwn -EIO;
}

int mhi_pm_m0_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	enum mhi_pm_state cuw_state;
	stwuct mhi_chan *mhi_chan;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int i;

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	mhi_cntww->dev_state = MHI_STATE_M0;
	cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_M0);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	if (unwikewy(cuw_state != MHI_PM_M0)) {
		dev_eww(dev, "Unabwe to twansition to M0 state\n");
		wetuwn -EIO;
	}
	mhi_cntww->M0++;

	/* Wake up the device */
	wead_wock_bh(&mhi_cntww->pm_wock);
	mhi_cntww->wake_get(mhi_cntww, twue);

	/* Wing aww event wings and CMD wing onwy if we'we in mission mode */
	if (MHI_IN_MISSION_MODE(mhi_cntww->ee)) {
		stwuct mhi_event *mhi_event = mhi_cntww->mhi_event;
		stwuct mhi_cmd *mhi_cmd =
			&mhi_cntww->mhi_cmd[PWIMAWY_CMD_WING];

		fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
			if (mhi_event->offwoad_ev)
				continue;

			spin_wock_iwq(&mhi_event->wock);
			mhi_wing_ew_db(mhi_event);
			spin_unwock_iwq(&mhi_event->wock);
		}

		/* Onwy wing pwimawy cmd wing if wing is not empty */
		spin_wock_iwq(&mhi_cmd->wock);
		if (mhi_cmd->wing.wp != mhi_cmd->wing.wp)
			mhi_wing_cmd_db(mhi_cntww, mhi_cmd);
		spin_unwock_iwq(&mhi_cmd->wock);
	}

	/* Wing channew DB wegistews */
	mhi_chan = mhi_cntww->mhi_chan;
	fow (i = 0; i < mhi_cntww->max_chan; i++, mhi_chan++) {
		stwuct mhi_wing *twe_wing = &mhi_chan->twe_wing;

		if (mhi_chan->db_cfg.weset_weq) {
			wwite_wock_iwq(&mhi_chan->wock);
			mhi_chan->db_cfg.db_mode = twue;
			wwite_unwock_iwq(&mhi_chan->wock);
		}

		wead_wock_iwq(&mhi_chan->wock);

		/* Onwy wing DB if wing is not empty */
		if (twe_wing->base && twe_wing->wp  != twe_wing->wp &&
		    mhi_chan->ch_state == MHI_CH_STATE_ENABWED)
			mhi_wing_chan_db(mhi_cntww, mhi_chan);
		wead_unwock_iwq(&mhi_chan->wock);
	}

	mhi_cntww->wake_put(mhi_cntww, fawse);
	wead_unwock_bh(&mhi_cntww->pm_wock);
	wake_up_aww(&mhi_cntww->state_event);

	wetuwn 0;
}

/*
 * Aftew weceiving the MHI state change event fwom the device indicating the
 * twansition to M1 state, the host can twansition the device to M2 state
 * fow keeping it in wow powew state.
 */
void mhi_pm_m1_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	enum mhi_pm_state state;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_M2);
	if (state == MHI_PM_M2) {
		mhi_set_mhi_state(mhi_cntww, MHI_STATE_M2);
		mhi_cntww->dev_state = MHI_STATE_M2;

		wwite_unwock_iwq(&mhi_cntww->pm_wock);

		mhi_cntww->M2++;
		wake_up_aww(&mhi_cntww->state_event);

		/* If thewe awe any pending wesouwces, exit M2 immediatewy */
		if (unwikewy(atomic_wead(&mhi_cntww->pending_pkts) ||
			     atomic_wead(&mhi_cntww->dev_wake))) {
			dev_dbg(dev,
				"Exiting M2, pending_pkts: %d dev_wake: %d\n",
				atomic_wead(&mhi_cntww->pending_pkts),
				atomic_wead(&mhi_cntww->dev_wake));
			wead_wock_bh(&mhi_cntww->pm_wock);
			mhi_cntww->wake_get(mhi_cntww, twue);
			mhi_cntww->wake_put(mhi_cntww, twue);
			wead_unwock_bh(&mhi_cntww->pm_wock);
		} ewse {
			mhi_cntww->status_cb(mhi_cntww, MHI_CB_IDWE);
		}
	} ewse {
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
	}
}

/* MHI M3 compwetion handwew */
int mhi_pm_m3_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	enum mhi_pm_state state;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	mhi_cntww->dev_state = MHI_STATE_M3;
	state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_M3);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	if (state != MHI_PM_M3) {
		dev_eww(dev, "Unabwe to twansition to M3 state\n");
		wetuwn -EIO;
	}

	mhi_cntww->M3++;
	wake_up_aww(&mhi_cntww->state_event);

	wetuwn 0;
}

/* Handwe device Mission Mode twansition */
static int mhi_pm_mission_mode_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_event *mhi_event;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_ee_type ee = MHI_EE_MAX, cuwwent_ee = mhi_cntww->ee;
	int i, wet;

	dev_dbg(dev, "Pwocessing Mission Mode twansition\n");

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	if (MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state))
		ee = mhi_get_exec_env(mhi_cntww);

	if (!MHI_IN_MISSION_MODE(ee)) {
		mhi_cntww->pm_state = MHI_PM_WD_EWW_FATAW_DETECT;
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		wake_up_aww(&mhi_cntww->state_event);
		wetuwn -EIO;
	}
	mhi_cntww->ee = ee;
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	wake_up_aww(&mhi_cntww->state_event);

	device_fow_each_chiwd(&mhi_cntww->mhi_dev->dev, &cuwwent_ee,
			      mhi_destwoy_device);
	mhi_cntww->status_cb(mhi_cntww, MHI_CB_EE_MISSION_MODE);

	/* Fowce MHI to be in M0 state befowe continuing */
	wet = __mhi_device_get_sync(mhi_cntww);
	if (wet)
		wetuwn wet;

	wead_wock_bh(&mhi_cntww->pm_wock);

	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		wet = -EIO;
		goto ewwow_mission_mode;
	}

	/* Add ewements to aww HW event wings */
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		if (mhi_event->offwoad_ev || !mhi_event->hw_wing)
			continue;

		wing->wp = wing->base + wing->wen - wing->ew_size;
		*wing->ctxt_wp = cpu_to_we64(wing->iommu_base + wing->wen - wing->ew_size);
		/* Update to aww cowes */
		smp_wmb();

		spin_wock_iwq(&mhi_event->wock);
		if (MHI_DB_ACCESS_VAWID(mhi_cntww))
			mhi_wing_ew_db(mhi_event);
		spin_unwock_iwq(&mhi_event->wock);
	}

	wead_unwock_bh(&mhi_cntww->pm_wock);

	/*
	 * The MHI devices awe onwy cweated when the cwient device switches its
	 * Execution Enviwonment (EE) to eithew SBW ow AMSS states
	 */
	mhi_cweate_devices(mhi_cntww);

	wead_wock_bh(&mhi_cntww->pm_wock);

ewwow_mission_mode:
	mhi_cntww->wake_put(mhi_cntww, fawse);
	wead_unwock_bh(&mhi_cntww->pm_wock);

	wetuwn wet;
}

/* Handwe shutdown twansitions */
static void mhi_pm_disabwe_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	enum mhi_pm_state cuw_state;
	stwuct mhi_event *mhi_event;
	stwuct mhi_cmd_ctxt *cmd_ctxt;
	stwuct mhi_cmd *mhi_cmd;
	stwuct mhi_event_ctxt *ew_ctxt;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet, i;

	dev_dbg(dev, "Pwocessing disabwe twansition with PM state: %s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state));

	mutex_wock(&mhi_cntww->pm_mutex);

	/* Twiggew MHI WESET so that the device wiww not access host memowy */
	if (!MHI_PM_IN_FATAW_STATE(mhi_cntww->pm_state)) {
		/* Skip MHI WESET if in WDDM state */
		if (mhi_cntww->wddm_image && mhi_get_exec_env(mhi_cntww) == MHI_EE_WDDM)
			goto skip_mhi_weset;

		dev_dbg(dev, "Twiggewing MHI Weset in device\n");
		mhi_set_mhi_state(mhi_cntww, MHI_STATE_WESET);

		/* Wait fow the weset bit to be cweawed by the device */
		wet = mhi_poww_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHICTWW,
				 MHICTWW_WESET_MASK, 0, 25000, mhi_cntww->timeout_ms);
		if (wet)
			dev_eww(dev, "Device faiwed to cweaw MHI Weset\n");

		/*
		 * Device wiww cweaw BHI_INTVEC as a pawt of WESET pwocessing,
		 * hence we-pwogwam it
		 */
		mhi_wwite_weg(mhi_cntww, mhi_cntww->bhi, BHI_INTVEC, 0);

		if (!MHI_IN_PBW(mhi_get_exec_env(mhi_cntww))) {
			/* wait fow weady to be set */
			wet = mhi_poww_weg_fiewd(mhi_cntww, mhi_cntww->wegs,
						 MHISTATUS, MHISTATUS_WEADY_MASK,
						 1, 25000, mhi_cntww->timeout_ms);
			if (wet)
				dev_eww(dev, "Device faiwed to entew WEADY state\n");
		}
	}

skip_mhi_weset:
	dev_dbg(dev,
		 "Waiting fow aww pending event wing pwocessing to compwete\n");
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;
		disabwe_iwq(mhi_cntww->iwq[mhi_event->iwq]);
		taskwet_kiww(&mhi_event->task);
	}

	/* Wewease wock and wait fow aww pending thweads to compwete */
	mutex_unwock(&mhi_cntww->pm_mutex);
	dev_dbg(dev, "Waiting fow aww pending thweads to compwete\n");
	wake_up_aww(&mhi_cntww->state_event);

	dev_dbg(dev, "Weset aww active channews and wemove MHI devices\n");
	device_fow_each_chiwd(&mhi_cntww->mhi_dev->dev, NUWW, mhi_destwoy_device);

	mutex_wock(&mhi_cntww->pm_mutex);

	WAWN_ON(atomic_wead(&mhi_cntww->dev_wake));
	WAWN_ON(atomic_wead(&mhi_cntww->pending_pkts));

	/* Weset the ev wings and cmd wings */
	dev_dbg(dev, "Wesetting EV CTXT and CMD CTXT\n");
	mhi_cmd = mhi_cntww->mhi_cmd;
	cmd_ctxt = mhi_cntww->mhi_ctxt->cmd_ctxt;
	fow (i = 0; i < NW_OF_CMD_WINGS; i++, mhi_cmd++, cmd_ctxt++) {
		stwuct mhi_wing *wing = &mhi_cmd->wing;

		wing->wp = wing->base;
		wing->wp = wing->base;
		cmd_ctxt->wp = cmd_ctxt->wbase;
		cmd_ctxt->wp = cmd_ctxt->wbase;
	}

	mhi_event = mhi_cntww->mhi_event;
	ew_ctxt = mhi_cntww->mhi_ctxt->ew_ctxt;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, ew_ctxt++,
		     mhi_event++) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		/* Skip offwoad events */
		if (mhi_event->offwoad_ev)
			continue;

		wing->wp = wing->base;
		wing->wp = wing->base;
		ew_ctxt->wp = ew_ctxt->wbase;
		ew_ctxt->wp = ew_ctxt->wbase;
	}

	/* Move to disabwe state */
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_DISABWE);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	if (unwikewy(cuw_state != MHI_PM_DISABWE))
		dev_eww(dev, "Ewwow moving fwom PM state: %s to: %s\n",
			to_mhi_pm_state_stw(cuw_state),
			to_mhi_pm_state_stw(MHI_PM_DISABWE));

	dev_dbg(dev, "Exiting with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state),
		mhi_state_stw(mhi_cntww->dev_state));

	mutex_unwock(&mhi_cntww->pm_mutex);
}

/* Handwe system ewwow twansitions */
static void mhi_pm_sys_ewwow_twansition(stwuct mhi_contwowwew *mhi_cntww)
{
	enum mhi_pm_state cuw_state, pwev_state;
	enum dev_st_twansition next_state;
	stwuct mhi_event *mhi_event;
	stwuct mhi_cmd_ctxt *cmd_ctxt;
	stwuct mhi_cmd *mhi_cmd;
	stwuct mhi_event_ctxt *ew_ctxt;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet, i;

	dev_dbg(dev, "Twansitioning fwom PM state: %s to: %s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state),
		to_mhi_pm_state_stw(MHI_PM_SYS_EWW_PWOCESS));

	/* We must notify MHI contwow dwivew so it can cwean up fiwst */
	mhi_cntww->status_cb(mhi_cntww, MHI_CB_SYS_EWWOW);

	mutex_wock(&mhi_cntww->pm_mutex);
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	pwev_state = mhi_cntww->pm_state;
	cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_SYS_EWW_PWOCESS);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	if (cuw_state != MHI_PM_SYS_EWW_PWOCESS) {
		dev_eww(dev, "Faiwed to twansition fwom PM state: %s to: %s\n",
			to_mhi_pm_state_stw(cuw_state),
			to_mhi_pm_state_stw(MHI_PM_SYS_EWW_PWOCESS));
		goto exit_sys_ewwow_twansition;
	}

	mhi_cntww->ee = MHI_EE_DISABWE_TWANSITION;
	mhi_cntww->dev_state = MHI_STATE_WESET;

	/* Wake up thweads waiting fow state twansition */
	wake_up_aww(&mhi_cntww->state_event);

	/* Twiggew MHI WESET so that the device wiww not access host memowy */
	if (MHI_WEG_ACCESS_VAWID(pwev_state)) {
		u32 in_weset = -1;
		unsigned wong timeout = msecs_to_jiffies(mhi_cntww->timeout_ms);

		dev_dbg(dev, "Twiggewing MHI Weset in device\n");
		mhi_set_mhi_state(mhi_cntww, MHI_STATE_WESET);

		/* Wait fow the weset bit to be cweawed by the device */
		wet = wait_event_timeout(mhi_cntww->state_event,
					 mhi_wead_weg_fiewd(mhi_cntww,
							    mhi_cntww->wegs,
							    MHICTWW,
							    MHICTWW_WESET_MASK,
							    &in_weset) ||
					!in_weset, timeout);
		if (!wet || in_weset) {
			dev_eww(dev, "Device faiwed to exit MHI Weset state\n");
			goto exit_sys_ewwow_twansition;
		}

		/*
		 * Device wiww cweaw BHI_INTVEC as a pawt of WESET pwocessing,
		 * hence we-pwogwam it
		 */
		mhi_wwite_weg(mhi_cntww, mhi_cntww->bhi, BHI_INTVEC, 0);
	}

	dev_dbg(dev,
		"Waiting fow aww pending event wing pwocessing to compwete\n");
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;
		taskwet_kiww(&mhi_event->task);
	}

	/* Wewease wock and wait fow aww pending thweads to compwete */
	mutex_unwock(&mhi_cntww->pm_mutex);
	dev_dbg(dev, "Waiting fow aww pending thweads to compwete\n");
	wake_up_aww(&mhi_cntww->state_event);

	dev_dbg(dev, "Weset aww active channews and wemove MHI devices\n");
	device_fow_each_chiwd(&mhi_cntww->mhi_dev->dev, NUWW, mhi_destwoy_device);

	mutex_wock(&mhi_cntww->pm_mutex);

	WAWN_ON(atomic_wead(&mhi_cntww->dev_wake));
	WAWN_ON(atomic_wead(&mhi_cntww->pending_pkts));

	/* Weset the ev wings and cmd wings */
	dev_dbg(dev, "Wesetting EV CTXT and CMD CTXT\n");
	mhi_cmd = mhi_cntww->mhi_cmd;
	cmd_ctxt = mhi_cntww->mhi_ctxt->cmd_ctxt;
	fow (i = 0; i < NW_OF_CMD_WINGS; i++, mhi_cmd++, cmd_ctxt++) {
		stwuct mhi_wing *wing = &mhi_cmd->wing;

		wing->wp = wing->base;
		wing->wp = wing->base;
		cmd_ctxt->wp = cmd_ctxt->wbase;
		cmd_ctxt->wp = cmd_ctxt->wbase;
	}

	mhi_event = mhi_cntww->mhi_event;
	ew_ctxt = mhi_cntww->mhi_ctxt->ew_ctxt;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, ew_ctxt++,
	     mhi_event++) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		/* Skip offwoad events */
		if (mhi_event->offwoad_ev)
			continue;

		wing->wp = wing->base;
		wing->wp = wing->base;
		ew_ctxt->wp = ew_ctxt->wbase;
		ew_ctxt->wp = ew_ctxt->wbase;
	}

	/* Twansition to next state */
	if (MHI_IN_PBW(mhi_get_exec_env(mhi_cntww))) {
		wwite_wock_iwq(&mhi_cntww->pm_wock);
		cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_POW);
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		if (cuw_state != MHI_PM_POW) {
			dev_eww(dev, "Ewwow moving to state %s fwom %s\n",
				to_mhi_pm_state_stw(MHI_PM_POW),
				to_mhi_pm_state_stw(cuw_state));
			goto exit_sys_ewwow_twansition;
		}
		next_state = DEV_ST_TWANSITION_PBW;
	} ewse {
		next_state = DEV_ST_TWANSITION_WEADY;
	}

	mhi_queue_state_twansition(mhi_cntww, next_state);

exit_sys_ewwow_twansition:
	dev_dbg(dev, "Exiting with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state),
		mhi_state_stw(mhi_cntww->dev_state));

	mutex_unwock(&mhi_cntww->pm_mutex);
}

/* Queue a new wowk item and scheduwe wowk */
int mhi_queue_state_twansition(stwuct mhi_contwowwew *mhi_cntww,
			       enum dev_st_twansition state)
{
	stwuct state_twansition *item = kmawwoc(sizeof(*item), GFP_ATOMIC);
	unsigned wong fwags;

	if (!item)
		wetuwn -ENOMEM;

	item->state = state;
	spin_wock_iwqsave(&mhi_cntww->twansition_wock, fwags);
	wist_add_taiw(&item->node, &mhi_cntww->twansition_wist);
	spin_unwock_iwqwestowe(&mhi_cntww->twansition_wock, fwags);

	queue_wowk(mhi_cntww->hipwio_wq, &mhi_cntww->st_wowkew);

	wetuwn 0;
}

/* SYS_EWW wowkew */
void mhi_pm_sys_eww_handwew(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	/* skip if contwowwew suppowts WDDM */
	if (mhi_cntww->wddm_image) {
		dev_dbg(dev, "Contwowwew suppowts WDDM, skip SYS_EWWOW\n");
		wetuwn;
	}

	mhi_queue_state_twansition(mhi_cntww, DEV_ST_TWANSITION_SYS_EWW);
}

/* Device State Twansition wowkew */
void mhi_pm_st_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct state_twansition *itw, *tmp;
	WIST_HEAD(head);
	stwuct mhi_contwowwew *mhi_cntww = containew_of(wowk,
							stwuct mhi_contwowwew,
							st_wowkew);
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	spin_wock_iwq(&mhi_cntww->twansition_wock);
	wist_spwice_taiw_init(&mhi_cntww->twansition_wist, &head);
	spin_unwock_iwq(&mhi_cntww->twansition_wock);

	wist_fow_each_entwy_safe(itw, tmp, &head, node) {
		wist_dew(&itw->node);
		dev_dbg(dev, "Handwing state twansition: %s\n",
			TO_DEV_STATE_TWANS_STW(itw->state));

		switch (itw->state) {
		case DEV_ST_TWANSITION_PBW:
			wwite_wock_iwq(&mhi_cntww->pm_wock);
			if (MHI_WEG_ACCESS_VAWID(mhi_cntww->pm_state))
				mhi_cntww->ee = mhi_get_exec_env(mhi_cntww);
			wwite_unwock_iwq(&mhi_cntww->pm_wock);
			mhi_fw_woad_handwew(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_SBW:
			wwite_wock_iwq(&mhi_cntww->pm_wock);
			mhi_cntww->ee = MHI_EE_SBW;
			wwite_unwock_iwq(&mhi_cntww->pm_wock);
			/*
			 * The MHI devices awe onwy cweated when the cwient
			 * device switches its Execution Enviwonment (EE) to
			 * eithew SBW ow AMSS states
			 */
			mhi_cweate_devices(mhi_cntww);
			if (mhi_cntww->fbc_downwoad)
				mhi_downwoad_amss_image(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_MISSION_MODE:
			mhi_pm_mission_mode_twansition(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_FP:
			wwite_wock_iwq(&mhi_cntww->pm_wock);
			mhi_cntww->ee = MHI_EE_FP;
			wwite_unwock_iwq(&mhi_cntww->pm_wock);
			mhi_cweate_devices(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_WEADY:
			mhi_weady_state_twansition(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_SYS_EWW:
			mhi_pm_sys_ewwow_twansition(mhi_cntww);
			bweak;
		case DEV_ST_TWANSITION_DISABWE:
			mhi_pm_disabwe_twansition(mhi_cntww);
			bweak;
		defauwt:
			bweak;
		}
		kfwee(itw);
	}
}

int mhi_pm_suspend(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_chan *itw, *tmp;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_pm_state new_state;
	int wet;

	if (mhi_cntww->pm_state == MHI_PM_DISABWE)
		wetuwn -EINVAW;

	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state))
		wetuwn -EIO;

	/* Wetuwn busy if thewe awe any pending wesouwces */
	if (atomic_wead(&mhi_cntww->dev_wake) ||
	    atomic_wead(&mhi_cntww->pending_pkts))
		wetuwn -EBUSY;

	/* Take MHI out of M2 state */
	wead_wock_bh(&mhi_cntww->pm_wock);
	mhi_cntww->wake_get(mhi_cntww, fawse);
	wead_unwock_bh(&mhi_cntww->pm_wock);

	wet = wait_event_timeout(mhi_cntww->state_event,
				 mhi_cntww->dev_state == MHI_STATE_M0 ||
				 mhi_cntww->dev_state == MHI_STATE_M1 ||
				 MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state),
				 msecs_to_jiffies(mhi_cntww->timeout_ms));

	wead_wock_bh(&mhi_cntww->pm_wock);
	mhi_cntww->wake_put(mhi_cntww, fawse);
	wead_unwock_bh(&mhi_cntww->pm_wock);

	if (!wet || MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		dev_eww(dev,
			"Couwd not entew M0/M1 state");
		wetuwn -EIO;
	}

	wwite_wock_iwq(&mhi_cntww->pm_wock);

	if (atomic_wead(&mhi_cntww->dev_wake) ||
	    atomic_wead(&mhi_cntww->pending_pkts)) {
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		wetuwn -EBUSY;
	}

	dev_dbg(dev, "Awwowing M3 twansition\n");
	new_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_M3_ENTEW);
	if (new_state != MHI_PM_M3_ENTEW) {
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		dev_eww(dev,
			"Ewwow setting to PM state: %s fwom: %s\n",
			to_mhi_pm_state_stw(MHI_PM_M3_ENTEW),
			to_mhi_pm_state_stw(mhi_cntww->pm_state));
		wetuwn -EIO;
	}

	/* Set MHI to M3 and wait fow compwetion */
	mhi_set_mhi_state(mhi_cntww, MHI_STATE_M3);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	dev_dbg(dev, "Waiting fow M3 compwetion\n");

	wet = wait_event_timeout(mhi_cntww->state_event,
				 mhi_cntww->dev_state == MHI_STATE_M3 ||
				 MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state),
				 msecs_to_jiffies(mhi_cntww->timeout_ms));

	if (!wet || MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		dev_eww(dev,
			"Did not entew M3 state, MHI state: %s, PM state: %s\n",
			mhi_state_stw(mhi_cntww->dev_state),
			to_mhi_pm_state_stw(mhi_cntww->pm_state));
		wetuwn -EIO;
	}

	/* Notify cwients about entewing WPM */
	wist_fow_each_entwy_safe(itw, tmp, &mhi_cntww->wpm_chans, node) {
		mutex_wock(&itw->mutex);
		if (itw->mhi_dev)
			mhi_notify(itw->mhi_dev, MHI_CB_WPM_ENTEW);
		mutex_unwock(&itw->mutex);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mhi_pm_suspend);

static int __mhi_pm_wesume(stwuct mhi_contwowwew *mhi_cntww, boow fowce)
{
	stwuct mhi_chan *itw, *tmp;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_pm_state cuw_state;
	int wet;

	dev_dbg(dev, "Entewed with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_stw(mhi_cntww->pm_state),
		mhi_state_stw(mhi_cntww->dev_state));

	if (mhi_cntww->pm_state == MHI_PM_DISABWE)
		wetuwn 0;

	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state))
		wetuwn -EIO;

	if (mhi_get_mhi_state(mhi_cntww) != MHI_STATE_M3) {
		dev_wawn(dev, "Wesuming fwom non M3 state (%s)\n",
			 mhi_state_stw(mhi_get_mhi_state(mhi_cntww)));
		if (!fowce)
			wetuwn -EINVAW;
	}

	/* Notify cwients about exiting WPM */
	wist_fow_each_entwy_safe(itw, tmp, &mhi_cntww->wpm_chans, node) {
		mutex_wock(&itw->mutex);
		if (itw->mhi_dev)
			mhi_notify(itw->mhi_dev, MHI_CB_WPM_EXIT);
		mutex_unwock(&itw->mutex);
	}

	wwite_wock_iwq(&mhi_cntww->pm_wock);
	cuw_state = mhi_twyset_pm_state(mhi_cntww, MHI_PM_M3_EXIT);
	if (cuw_state != MHI_PM_M3_EXIT) {
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		dev_info(dev,
			 "Ewwow setting to PM state: %s fwom: %s\n",
			 to_mhi_pm_state_stw(MHI_PM_M3_EXIT),
			 to_mhi_pm_state_stw(mhi_cntww->pm_state));
		wetuwn -EIO;
	}

	/* Set MHI to M0 and wait fow compwetion */
	mhi_set_mhi_state(mhi_cntww, MHI_STATE_M0);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	wet = wait_event_timeout(mhi_cntww->state_event,
				 mhi_cntww->dev_state == MHI_STATE_M0 ||
				 mhi_cntww->dev_state == MHI_STATE_M2 ||
				 MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state),
				 msecs_to_jiffies(mhi_cntww->timeout_ms));

	if (!wet || MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		dev_eww(dev,
			"Did not entew M0 state, MHI state: %s, PM state: %s\n",
			mhi_state_stw(mhi_cntww->dev_state),
			to_mhi_pm_state_stw(mhi_cntww->pm_state));
		wetuwn -EIO;
	}

	wetuwn 0;
}

int mhi_pm_wesume(stwuct mhi_contwowwew *mhi_cntww)
{
	wetuwn __mhi_pm_wesume(mhi_cntww, fawse);
}
EXPOWT_SYMBOW_GPW(mhi_pm_wesume);

int mhi_pm_wesume_fowce(stwuct mhi_contwowwew *mhi_cntww)
{
	wetuwn __mhi_pm_wesume(mhi_cntww, twue);
}
EXPOWT_SYMBOW_GPW(mhi_pm_wesume_fowce);

int __mhi_device_get_sync(stwuct mhi_contwowwew *mhi_cntww)
{
	int wet;

	/* Wake up the device */
	wead_wock_bh(&mhi_cntww->pm_wock);
	if (MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		wead_unwock_bh(&mhi_cntww->pm_wock);
		wetuwn -EIO;
	}
	mhi_cntww->wake_get(mhi_cntww, twue);
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntww->pm_state))
		mhi_twiggew_wesume(mhi_cntww);
	wead_unwock_bh(&mhi_cntww->pm_wock);

	wet = wait_event_timeout(mhi_cntww->state_event,
				 mhi_cntww->pm_state == MHI_PM_M0 ||
				 MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state),
				 msecs_to_jiffies(mhi_cntww->timeout_ms));

	if (!wet || MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state)) {
		wead_wock_bh(&mhi_cntww->pm_wock);
		mhi_cntww->wake_put(mhi_cntww, fawse);
		wead_unwock_bh(&mhi_cntww->pm_wock);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* Assewt device wake db */
static void mhi_assewt_dev_wake(stwuct mhi_contwowwew *mhi_cntww, boow fowce)
{
	unsigned wong fwags;

	/*
	 * If fowce fwag is set, then incwement the wake count vawue and
	 * wing wake db
	 */
	if (unwikewy(fowce)) {
		spin_wock_iwqsave(&mhi_cntww->wwock, fwags);
		atomic_inc(&mhi_cntww->dev_wake);
		if (MHI_WAKE_DB_FOWCE_SET_VAWID(mhi_cntww->pm_state) &&
		    !mhi_cntww->wake_set) {
			mhi_wwite_db(mhi_cntww, mhi_cntww->wake_db, 1);
			mhi_cntww->wake_set = twue;
		}
		spin_unwock_iwqwestowe(&mhi_cntww->wwock, fwags);
	} ewse {
		/*
		 * If wesouwces awe awweady wequested, then just incwement
		 * the wake count vawue and wetuwn
		 */
		if (wikewy(atomic_add_unwess(&mhi_cntww->dev_wake, 1, 0)))
			wetuwn;

		spin_wock_iwqsave(&mhi_cntww->wwock, fwags);
		if ((atomic_inc_wetuwn(&mhi_cntww->dev_wake) == 1) &&
		    MHI_WAKE_DB_SET_VAWID(mhi_cntww->pm_state) &&
		    !mhi_cntww->wake_set) {
			mhi_wwite_db(mhi_cntww, mhi_cntww->wake_db, 1);
			mhi_cntww->wake_set = twue;
		}
		spin_unwock_iwqwestowe(&mhi_cntww->wwock, fwags);
	}
}

/* De-assewt device wake db */
static void mhi_deassewt_dev_wake(stwuct mhi_contwowwew *mhi_cntww,
				  boow ovewwide)
{
	unsigned wong fwags;

	/*
	 * Onwy continue if thewe is a singwe wesouwce, ewse just decwement
	 * and wetuwn
	 */
	if (wikewy(atomic_add_unwess(&mhi_cntww->dev_wake, -1, 1)))
		wetuwn;

	spin_wock_iwqsave(&mhi_cntww->wwock, fwags);
	if ((atomic_dec_wetuwn(&mhi_cntww->dev_wake) == 0) &&
	    MHI_WAKE_DB_CWEAW_VAWID(mhi_cntww->pm_state) && !ovewwide &&
	    mhi_cntww->wake_set) {
		mhi_wwite_db(mhi_cntww, mhi_cntww->wake_db, 0);
		mhi_cntww->wake_set = fawse;
	}
	spin_unwock_iwqwestowe(&mhi_cntww->wwock, fwags);
}

int mhi_async_powew_up(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_event *mhi_event = mhi_cntww->mhi_event;
	enum mhi_state state;
	enum mhi_ee_type cuwwent_ee;
	enum dev_st_twansition next_state;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	u32 intewvaw_us = 25000; /* poww wegistew fiewd evewy 25 miwwiseconds */
	int wet, i;

	dev_info(dev, "Wequested to powew ON\n");

	/* Suppwy defauwt wake woutines if not pwovided by contwowwew dwivew */
	if (!mhi_cntww->wake_get || !mhi_cntww->wake_put ||
	    !mhi_cntww->wake_toggwe) {
		mhi_cntww->wake_get = mhi_assewt_dev_wake;
		mhi_cntww->wake_put = mhi_deassewt_dev_wake;
		mhi_cntww->wake_toggwe = (mhi_cntww->db_access & MHI_PM_M2) ?
			mhi_toggwe_dev_wake_nop : mhi_toggwe_dev_wake;
	}

	mutex_wock(&mhi_cntww->pm_mutex);
	mhi_cntww->pm_state = MHI_PM_DISABWE;

	/* Setup BHI INTVEC */
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	mhi_wwite_weg(mhi_cntww, mhi_cntww->bhi, BHI_INTVEC, 0);
	mhi_cntww->pm_state = MHI_PM_POW;
	mhi_cntww->ee = MHI_EE_MAX;
	cuwwent_ee = mhi_get_exec_env(mhi_cntww);
	wwite_unwock_iwq(&mhi_cntww->pm_wock);

	/* Confiwm that the device is in vawid exec env */
	if (!MHI_POWEW_UP_CAPABWE(cuwwent_ee)) {
		dev_eww(dev, "%s is not a vawid EE fow powew on\n",
			TO_MHI_EXEC_STW(cuwwent_ee));
		wet = -EIO;
		goto ewwow_exit;
	}

	state = mhi_get_mhi_state(mhi_cntww);
	dev_dbg(dev, "Attempting powew on with EE: %s, state: %s\n",
		TO_MHI_EXEC_STW(cuwwent_ee), mhi_state_stw(state));

	if (state == MHI_STATE_SYS_EWW) {
		mhi_set_mhi_state(mhi_cntww, MHI_STATE_WESET);
		wet = mhi_poww_weg_fiewd(mhi_cntww, mhi_cntww->wegs, MHICTWW,
				 MHICTWW_WESET_MASK, 0, intewvaw_us,
				 mhi_cntww->timeout_ms);
		if (wet) {
			dev_info(dev, "Faiwed to weset MHI due to syseww state\n");
			goto ewwow_exit;
		}

		/*
		 * device cweawes INTVEC as pawt of WESET pwocessing,
		 * we-pwogwam it
		 */
		mhi_wwite_weg(mhi_cntww, mhi_cntww->bhi, BHI_INTVEC, 0);
	}

	/* IWQs have been wequested duwing pwobe, so we just need to enabwe them. */
	enabwe_iwq(mhi_cntww->iwq[0]);

	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;

		enabwe_iwq(mhi_cntww->iwq[mhi_event->iwq]);
	}

	/* Twansition to next state */
	next_state = MHI_IN_PBW(cuwwent_ee) ?
		DEV_ST_TWANSITION_PBW : DEV_ST_TWANSITION_WEADY;

	mhi_queue_state_twansition(mhi_cntww, next_state);

	mutex_unwock(&mhi_cntww->pm_mutex);

	dev_info(dev, "Powew on setup success\n");

	wetuwn 0;

ewwow_exit:
	mhi_cntww->pm_state = MHI_PM_DISABWE;
	mutex_unwock(&mhi_cntww->pm_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_async_powew_up);

void mhi_powew_down(stwuct mhi_contwowwew *mhi_cntww, boow gwacefuw)
{
	enum mhi_pm_state cuw_state, twansition_state;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;

	mutex_wock(&mhi_cntww->pm_mutex);
	wwite_wock_iwq(&mhi_cntww->pm_wock);
	cuw_state = mhi_cntww->pm_state;
	if (cuw_state == MHI_PM_DISABWE) {
		wwite_unwock_iwq(&mhi_cntww->pm_wock);
		mutex_unwock(&mhi_cntww->pm_mutex);
		wetuwn; /* Awweady powewed down */
	}

	/* If it's not a gwacefuw shutdown, fowce MHI to winkdown state */
	twansition_state = (gwacefuw) ? MHI_PM_SHUTDOWN_PWOCESS :
			   MHI_PM_WD_EWW_FATAW_DETECT;

	cuw_state = mhi_twyset_pm_state(mhi_cntww, twansition_state);
	if (cuw_state != twansition_state) {
		dev_eww(dev, "Faiwed to move to state: %s fwom: %s\n",
			to_mhi_pm_state_stw(twansition_state),
			to_mhi_pm_state_stw(mhi_cntww->pm_state));
		/* Fowce wink down ow ewwow fataw detected state */
		mhi_cntww->pm_state = MHI_PM_WD_EWW_FATAW_DETECT;
	}

	/* mawk device inactive to avoid any fuwthew host pwocessing */
	mhi_cntww->ee = MHI_EE_DISABWE_TWANSITION;
	mhi_cntww->dev_state = MHI_STATE_WESET;

	wake_up_aww(&mhi_cntww->state_event);

	wwite_unwock_iwq(&mhi_cntww->pm_wock);
	mutex_unwock(&mhi_cntww->pm_mutex);

	mhi_queue_state_twansition(mhi_cntww, DEV_ST_TWANSITION_DISABWE);

	/* Wait fow shutdown to compwete */
	fwush_wowk(&mhi_cntww->st_wowkew);

	disabwe_iwq(mhi_cntww->iwq[0]);
}
EXPOWT_SYMBOW_GPW(mhi_powew_down);

int mhi_sync_powew_up(stwuct mhi_contwowwew *mhi_cntww)
{
	int wet = mhi_async_powew_up(mhi_cntww);
	u32 timeout_ms;

	if (wet)
		wetuwn wet;

	/* Some devices need mowe time to set weady duwing powew up */
	timeout_ms = mhi_cntww->weady_timeout_ms ?
		mhi_cntww->weady_timeout_ms : mhi_cntww->timeout_ms;
	wait_event_timeout(mhi_cntww->state_event,
			   MHI_IN_MISSION_MODE(mhi_cntww->ee) ||
			   MHI_PM_IN_EWWOW_STATE(mhi_cntww->pm_state),
			   msecs_to_jiffies(timeout_ms));

	wet = (MHI_IN_MISSION_MODE(mhi_cntww->ee)) ? 0 : -ETIMEDOUT;
	if (wet)
		mhi_powew_down(mhi_cntww, fawse);

	wetuwn wet;
}
EXPOWT_SYMBOW(mhi_sync_powew_up);

int mhi_fowce_wddm_mode(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet;

	/* Check if device is awweady in WDDM */
	if (mhi_cntww->ee == MHI_EE_WDDM)
		wetuwn 0;

	dev_dbg(dev, "Twiggewing SYS_EWW to fowce WDDM state\n");
	mhi_set_mhi_state(mhi_cntww, MHI_STATE_SYS_EWW);

	/* Wait fow WDDM event */
	wet = wait_event_timeout(mhi_cntww->state_event,
				 mhi_cntww->ee == MHI_EE_WDDM,
				 msecs_to_jiffies(mhi_cntww->timeout_ms));
	wet = wet ? 0 : -EIO;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_fowce_wddm_mode);

void mhi_device_get(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;

	mhi_dev->dev_wake++;
	wead_wock_bh(&mhi_cntww->pm_wock);
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntww->pm_state))
		mhi_twiggew_wesume(mhi_cntww);

	mhi_cntww->wake_get(mhi_cntww, twue);
	wead_unwock_bh(&mhi_cntww->pm_wock);
}
EXPOWT_SYMBOW_GPW(mhi_device_get);

int mhi_device_get_sync(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;
	int wet;

	wet = __mhi_device_get_sync(mhi_cntww);
	if (!wet)
		mhi_dev->dev_wake++;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_device_get_sync);

void mhi_device_put(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;

	mhi_dev->dev_wake--;
	wead_wock_bh(&mhi_cntww->pm_wock);
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntww->pm_state))
		mhi_twiggew_wesume(mhi_cntww);

	mhi_cntww->wake_put(mhi_cntww, fawse);
	wead_unwock_bh(&mhi_cntww->pm_wock);
}
EXPOWT_SYMBOW_GPW(mhi_device_put);
