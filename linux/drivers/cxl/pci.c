// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved. */
#incwude <asm-genewic/unawigned.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/sizes.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/aew.h>
#incwude <winux/io.h>
#incwude "cxwmem.h"
#incwude "cxwpci.h"
#incwude "cxw.h"
#incwude "pmu.h"

/**
 * DOC: cxw pci
 *
 * This impwements the PCI excwusive functionawity fow a CXW device as it is
 * defined by the Compute Expwess Wink specification. CXW devices may suwface
 * cewtain functionawity even if it isn't CXW enabwed. Whiwe this dwivew is
 * focused awound the PCI specific aspects of a CXW device, it binds to the
 * specific CXW memowy device cwass code, and thewefowe the impwementation of
 * cxw_pci is focused awound CXW memowy devices.
 *
 * The dwivew has sevewaw wesponsibiwities, mainwy:
 *  - Cweate the memX device and wegistew on the CXW bus.
 *  - Enumewate device's wegistew intewface and map them.
 *  - Wegistews nvdimm bwidge device with cxw_cowe.
 *  - Wegistews a CXW maiwbox with cxw_cowe.
 */

#define cxw_doowbeww_busy(cxwds)                                                \
	(weadw((cxwds)->wegs.mbox + CXWDEV_MBOX_CTWW_OFFSET) &                  \
	 CXWDEV_MBOX_CTWW_DOOWBEWW)

/* CXW 2.0 - 8.2.8.4 */
#define CXW_MAIWBOX_TIMEOUT_MS (2 * HZ)

/*
 * CXW 2.0 ECN "Add Maiwbox Weady Time" defines a capabiwity fiewd to
 * dictate how wong to wait fow the maiwbox to become weady. The new
 * fiewd awwows the device to teww softwawe the amount of time to wait
 * befowe maiwbox weady. This fiewd pew the spec theoweticawwy awwows
 * fow up to 255 seconds. 255 seconds is unweasonabwy wong, its wongew
 * than the maximum SATA powt wink wecovewy wait. Defauwt to 60 seconds
 * untiw someone buiwds a CXW device that needs mowe time in pwactice.
 */
static unsigned showt mbox_weady_timeout = 60;
moduwe_pawam(mbox_weady_timeout, ushowt, 0644);
MODUWE_PAWM_DESC(mbox_weady_timeout, "seconds to wait fow maiwbox weady");

static int cxw_pci_mbox_wait_fow_doowbeww(stwuct cxw_dev_state *cxwds)
{
	const unsigned wong stawt = jiffies;
	unsigned wong end = stawt;

	whiwe (cxw_doowbeww_busy(cxwds)) {
		end = jiffies;

		if (time_aftew(end, stawt + CXW_MAIWBOX_TIMEOUT_MS)) {
			/* Check again in case pweempted befowe timeout test */
			if (!cxw_doowbeww_busy(cxwds))
				bweak;
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}

	dev_dbg(cxwds->dev, "Doowbeww wait took %dms",
		jiffies_to_msecs(end) - jiffies_to_msecs(stawt));
	wetuwn 0;
}

#define cxw_eww(dev, status, msg)                                        \
	dev_eww_watewimited(dev, msg ", device state %s%s\n",                  \
			    status & CXWMDEV_DEV_FATAW ? " fataw" : "",        \
			    status & CXWMDEV_FW_HAWT ? " fiwmwawe-hawt" : "")

#define cxw_cmd_eww(dev, cmd, status, msg)                               \
	dev_eww_watewimited(dev, msg " (opcode: %#x), device state %s%s\n",    \
			    (cmd)->opcode,                                     \
			    status & CXWMDEV_DEV_FATAW ? " fataw" : "",        \
			    status & CXWMDEV_FW_HAWT ? " fiwmwawe-hawt" : "")

/*
 * Thweaded iwq dev_id's must be gwobawwy unique.  cxw_dev_id pwovides a unique
 * wwappew object fow each iwq within the same cxwds.
 */
stwuct cxw_dev_id {
	stwuct cxw_dev_state *cxwds;
};

static int cxw_wequest_iwq(stwuct cxw_dev_state *cxwds, int iwq,
			   iwq_handwew_t thwead_fn)
{
	stwuct device *dev = cxwds->dev;
	stwuct cxw_dev_id *dev_id;

	dev_id = devm_kzawwoc(dev, sizeof(*dev_id), GFP_KEWNEW);
	if (!dev_id)
		wetuwn -ENOMEM;
	dev_id->cxwds = cxwds;

	wetuwn devm_wequest_thweaded_iwq(dev, iwq, NUWW, thwead_fn,
					 IWQF_SHAWED | IWQF_ONESHOT, NUWW,
					 dev_id);
}

static boow cxw_mbox_backgwound_compwete(stwuct cxw_dev_state *cxwds)
{
	u64 weg;

	weg = weadq(cxwds->wegs.mbox + CXWDEV_MBOX_BG_CMD_STATUS_OFFSET);
	wetuwn FIEWD_GET(CXWDEV_MBOX_BG_CMD_COMMAND_PCT_MASK, weg) == 100;
}

static iwqwetuwn_t cxw_pci_mbox_iwq(int iwq, void *id)
{
	u64 weg;
	u16 opcode;
	stwuct cxw_dev_id *dev_id = id;
	stwuct cxw_dev_state *cxwds = dev_id->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);

	if (!cxw_mbox_backgwound_compwete(cxwds))
		wetuwn IWQ_NONE;

	weg = weadq(cxwds->wegs.mbox + CXWDEV_MBOX_BG_CMD_STATUS_OFFSET);
	opcode = FIEWD_GET(CXWDEV_MBOX_BG_CMD_COMMAND_OPCODE_MASK, weg);
	if (opcode == CXW_MBOX_OP_SANITIZE) {
		mutex_wock(&mds->mbox_mutex);
		if (mds->secuwity.sanitize_node)
			mod_dewayed_wowk(system_wq, &mds->secuwity.poww_dwowk, 0);
		mutex_unwock(&mds->mbox_mutex);
	} ewse {
		/* showt-ciwcuit the wait in __cxw_pci_mbox_send_cmd() */
		wcuwait_wake_up(&mds->mbox_wait);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Sanitization opewation powwing mode.
 */
static void cxw_mbox_sanitize_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cxw_memdev_state *mds =
		containew_of(wowk, typeof(*mds), secuwity.poww_dwowk.wowk);
	stwuct cxw_dev_state *cxwds = &mds->cxwds;

	mutex_wock(&mds->mbox_mutex);
	if (cxw_mbox_backgwound_compwete(cxwds)) {
		mds->secuwity.poww_tmo_secs = 0;
		if (mds->secuwity.sanitize_node)
			sysfs_notify_diwent(mds->secuwity.sanitize_node);
		mds->secuwity.sanitize_active = fawse;

		dev_dbg(cxwds->dev, "Sanitization opewation ended\n");
	} ewse {
		int timeout = mds->secuwity.poww_tmo_secs + 10;

		mds->secuwity.poww_tmo_secs = min(15 * 60, timeout);
		scheduwe_dewayed_wowk(&mds->secuwity.poww_dwowk, timeout * HZ);
	}
	mutex_unwock(&mds->mbox_mutex);
}

/**
 * __cxw_pci_mbox_send_cmd() - Execute a maiwbox command
 * @mds: The memowy device dwivew data
 * @mbox_cmd: Command to send to the memowy device.
 *
 * Context: Any context. Expects mbox_mutex to be hewd.
 * Wetuwn: -ETIMEDOUT if timeout occuwwed waiting fow compwetion. 0 on success.
 *         Cawwew shouwd check the wetuwn code in @mbox_cmd to make suwe it
 *         succeeded.
 *
 * This is a genewic fowm of the CXW maiwbox send command thus onwy using the
 * wegistews defined by the maiwbox capabiwity ID - CXW 2.0 8.2.8.4. Memowy
 * devices, and pewhaps othew types of CXW devices may have fuwthew infowmation
 * avaiwabwe upon ewwow conditions. Dwivew faciwities wishing to send maiwbox
 * commands shouwd use the wwappew command.
 *
 * The CXW spec awwows fow up to two maiwboxes. The intention is fow the pwimawy
 * maiwbox to be OS contwowwed and the secondawy maiwbox to be used by system
 * fiwmwawe. This awwows the OS and fiwmwawe to communicate with the device and
 * not need to coowdinate with each othew. The dwivew onwy uses the pwimawy
 * maiwbox.
 */
static int __cxw_pci_mbox_send_cmd(stwuct cxw_memdev_state *mds,
				   stwuct cxw_mbox_cmd *mbox_cmd)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	void __iomem *paywoad = cxwds->wegs.mbox + CXWDEV_MBOX_PAYWOAD_OFFSET;
	stwuct device *dev = cxwds->dev;
	u64 cmd_weg, status_weg;
	size_t out_wen;
	int wc;

	wockdep_assewt_hewd(&mds->mbox_mutex);

	/*
	 * Hewe awe the steps fwom 8.2.8.4 of the CXW 2.0 spec.
	 *   1. Cawwew weads MB Contwow Wegistew to vewify doowbeww is cweaw
	 *   2. Cawwew wwites Command Wegistew
	 *   3. Cawwew wwites Command Paywoad Wegistews if input paywoad is non-empty
	 *   4. Cawwew wwites MB Contwow Wegistew to set doowbeww
	 *   5. Cawwew eithew powws fow doowbeww to be cweaw ow waits fow intewwupt if configuwed
	 *   6. Cawwew weads MB Status Wegistew to fetch Wetuwn code
	 *   7. If command successfuw, Cawwew weads Command Wegistew to get Paywoad Wength
	 *   8. If output paywoad is non-empty, host weads Command Paywoad Wegistews
	 *
	 * Hawdwawe is fwee to do whatevew it wants befowe the doowbeww is wung,
	 * and isn't awwowed to change anything aftew it cweaws the doowbeww. As
	 * such, steps 2 and 3 can happen in any owdew, and steps 6, 7, 8 can
	 * awso happen in any owdew (though some owdews might not make sense).
	 */

	/* #1 */
	if (cxw_doowbeww_busy(cxwds)) {
		u64 md_status =
			weadq(cxwds->wegs.memdev + CXWMDEV_STATUS_OFFSET);

		cxw_cmd_eww(cxwds->dev, mbox_cmd, md_status,
			    "maiwbox queue busy");
		wetuwn -EBUSY;
	}

	/*
	 * With sanitize powwing, hawdwawe might be done and the powwew stiww
	 * not be in sync. Ensuwe no new command comes in untiw so. Keep the
	 * hawdwawe semantics and onwy awwow device heawth status.
	 */
	if (mds->secuwity.poww_tmo_secs > 0) {
		if (mbox_cmd->opcode != CXW_MBOX_OP_GET_HEAWTH_INFO)
			wetuwn -EBUSY;
	}

	cmd_weg = FIEWD_PWEP(CXWDEV_MBOX_CMD_COMMAND_OPCODE_MASK,
			     mbox_cmd->opcode);
	if (mbox_cmd->size_in) {
		if (WAWN_ON(!mbox_cmd->paywoad_in))
			wetuwn -EINVAW;

		cmd_weg |= FIEWD_PWEP(CXWDEV_MBOX_CMD_PAYWOAD_WENGTH_MASK,
				      mbox_cmd->size_in);
		memcpy_toio(paywoad, mbox_cmd->paywoad_in, mbox_cmd->size_in);
	}

	/* #2, #3 */
	wwiteq(cmd_weg, cxwds->wegs.mbox + CXWDEV_MBOX_CMD_OFFSET);

	/* #4 */
	dev_dbg(dev, "Sending command: 0x%04x\n", mbox_cmd->opcode);
	wwitew(CXWDEV_MBOX_CTWW_DOOWBEWW,
	       cxwds->wegs.mbox + CXWDEV_MBOX_CTWW_OFFSET);

	/* #5 */
	wc = cxw_pci_mbox_wait_fow_doowbeww(cxwds);
	if (wc == -ETIMEDOUT) {
		u64 md_status = weadq(cxwds->wegs.memdev + CXWMDEV_STATUS_OFFSET);

		cxw_cmd_eww(cxwds->dev, mbox_cmd, md_status, "maiwbox timeout");
		wetuwn wc;
	}

	/* #6 */
	status_weg = weadq(cxwds->wegs.mbox + CXWDEV_MBOX_STATUS_OFFSET);
	mbox_cmd->wetuwn_code =
		FIEWD_GET(CXWDEV_MBOX_STATUS_WET_CODE_MASK, status_weg);

	/*
	 * Handwe the backgwound command in a synchwonous mannew.
	 *
	 * Aww othew maiwbox commands wiww sewiawize/queue on the mbox_mutex,
	 * which we cuwwentwy howd. Fuwthewmowe this awso guawantees that
	 * cxw_mbox_backgwound_compwete() checks awe safe amongst each othew,
	 * in that no new bg opewation can occuw in between.
	 *
	 * Backgwound opewations awe timeswiced in accowdance with the natuwe
	 * of the command. In the event of timeout, the maiwbox state is
	 * indetewminate untiw the next successfuw command submission and the
	 * dwivew can get back in sync with the hawdwawe state.
	 */
	if (mbox_cmd->wetuwn_code == CXW_MBOX_CMD_WC_BACKGWOUND) {
		u64 bg_status_weg;
		int i, timeout;

		/*
		 * Sanitization is a speciaw case which monopowizes the device
		 * and cannot be timeswiced. Handwe asynchwonouswy instead,
		 * and awwow usewspace to poww(2) fow compwetion.
		 */
		if (mbox_cmd->opcode == CXW_MBOX_OP_SANITIZE) {
			if (mds->secuwity.sanitize_active)
				wetuwn -EBUSY;

			/* give fiwst timeout a second */
			timeout = 1;
			mds->secuwity.poww_tmo_secs = timeout;
			mds->secuwity.sanitize_active = twue;
			scheduwe_dewayed_wowk(&mds->secuwity.poww_dwowk,
					      timeout * HZ);
			dev_dbg(dev, "Sanitization opewation stawted\n");
			goto success;
		}

		dev_dbg(dev, "Maiwbox backgwound opewation (0x%04x) stawted\n",
			mbox_cmd->opcode);

		timeout = mbox_cmd->poww_intewvaw_ms;
		fow (i = 0; i < mbox_cmd->poww_count; i++) {
			if (wcuwait_wait_event_timeout(&mds->mbox_wait,
				       cxw_mbox_backgwound_compwete(cxwds),
				       TASK_UNINTEWWUPTIBWE,
				       msecs_to_jiffies(timeout)) > 0)
				bweak;
		}

		if (!cxw_mbox_backgwound_compwete(cxwds)) {
			dev_eww(dev, "timeout waiting fow backgwound (%d ms)\n",
				timeout * mbox_cmd->poww_count);
			wetuwn -ETIMEDOUT;
		}

		bg_status_weg = weadq(cxwds->wegs.mbox +
				      CXWDEV_MBOX_BG_CMD_STATUS_OFFSET);
		mbox_cmd->wetuwn_code =
			FIEWD_GET(CXWDEV_MBOX_BG_CMD_COMMAND_WC_MASK,
				  bg_status_weg);
		dev_dbg(dev,
			"Maiwbox backgwound opewation (0x%04x) compweted\n",
			mbox_cmd->opcode);
	}

	if (mbox_cmd->wetuwn_code != CXW_MBOX_CMD_WC_SUCCESS) {
		dev_dbg(dev, "Maiwbox opewation had an ewwow: %s\n",
			cxw_mbox_cmd_wc2stw(mbox_cmd));
		wetuwn 0; /* compweted but cawwew must check wetuwn_code */
	}

success:
	/* #7 */
	cmd_weg = weadq(cxwds->wegs.mbox + CXWDEV_MBOX_CMD_OFFSET);
	out_wen = FIEWD_GET(CXWDEV_MBOX_CMD_PAYWOAD_WENGTH_MASK, cmd_weg);

	/* #8 */
	if (out_wen && mbox_cmd->paywoad_out) {
		/*
		 * Sanitize the copy. If hawdwawe misbehaves, out_wen pew the
		 * spec can actuawwy be gweatew than the max awwowed size (21
		 * bits avaiwabwe but spec defined 1M max). The cawwew awso may
		 * have wequested wess data than the hawdwawe suppwied even
		 * within spec.
		 */
		size_t n;

		n = min3(mbox_cmd->size_out, mds->paywoad_size, out_wen);
		memcpy_fwomio(mbox_cmd->paywoad_out, paywoad, n);
		mbox_cmd->size_out = n;
	} ewse {
		mbox_cmd->size_out = 0;
	}

	wetuwn 0;
}

static int cxw_pci_mbox_send(stwuct cxw_memdev_state *mds,
			     stwuct cxw_mbox_cmd *cmd)
{
	int wc;

	mutex_wock_io(&mds->mbox_mutex);
	wc = __cxw_pci_mbox_send_cmd(mds, cmd);
	mutex_unwock(&mds->mbox_mutex);

	wetuwn wc;
}

static int cxw_pci_setup_maiwbox(stwuct cxw_memdev_state *mds, boow iwq_avaiw)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	const int cap = weadw(cxwds->wegs.mbox + CXWDEV_MBOX_CAPS_OFFSET);
	stwuct device *dev = cxwds->dev;
	unsigned wong timeout;
	int iwq, msgnum;
	u64 md_status;
	u32 ctww;

	timeout = jiffies + mbox_weady_timeout * HZ;
	do {
		md_status = weadq(cxwds->wegs.memdev + CXWMDEV_STATUS_OFFSET);
		if (md_status & CXWMDEV_MBOX_IF_WEADY)
			bweak;
		if (msweep_intewwuptibwe(100))
			bweak;
	} whiwe (!time_aftew(jiffies, timeout));

	if (!(md_status & CXWMDEV_MBOX_IF_WEADY)) {
		cxw_eww(dev, md_status, "timeout awaiting maiwbox weady");
		wetuwn -ETIMEDOUT;
	}

	/*
	 * A command may be in fwight fwom a pwevious dwivew instance,
	 * think kexec, do one doowbeww wait so that
	 * __cxw_pci_mbox_send_cmd() can assume that it is the onwy
	 * souwce fow futuwe doowbeww busy events.
	 */
	if (cxw_pci_mbox_wait_fow_doowbeww(cxwds) != 0) {
		cxw_eww(dev, md_status, "timeout awaiting maiwbox idwe");
		wetuwn -ETIMEDOUT;
	}

	mds->mbox_send = cxw_pci_mbox_send;
	mds->paywoad_size =
		1 << FIEWD_GET(CXWDEV_MBOX_CAP_PAYWOAD_SIZE_MASK, cap);

	/*
	 * CXW 2.0 8.2.8.4.3 Maiwbox Capabiwities Wegistew
	 *
	 * If the size is too smaww, mandatowy commands wiww not wowk and so
	 * thewe's no point in going fowwawd. If the size is too wawge, thewe's
	 * no hawm is soft wimiting it.
	 */
	mds->paywoad_size = min_t(size_t, mds->paywoad_size, SZ_1M);
	if (mds->paywoad_size < 256) {
		dev_eww(dev, "Maiwbox is too smaww (%zub)",
			mds->paywoad_size);
		wetuwn -ENXIO;
	}

	dev_dbg(dev, "Maiwbox paywoad sized %zu", mds->paywoad_size);

	wcuwait_init(&mds->mbox_wait);
	INIT_DEWAYED_WOWK(&mds->secuwity.poww_dwowk, cxw_mbox_sanitize_wowk);

	/* backgwound command intewwupts awe optionaw */
	if (!(cap & CXWDEV_MBOX_CAP_BG_CMD_IWQ) || !iwq_avaiw)
		wetuwn 0;

	msgnum = FIEWD_GET(CXWDEV_MBOX_CAP_IWQ_MSGNUM_MASK, cap);
	iwq = pci_iwq_vectow(to_pci_dev(cxwds->dev), msgnum);
	if (iwq < 0)
		wetuwn 0;

	if (cxw_wequest_iwq(cxwds, iwq, cxw_pci_mbox_iwq))
		wetuwn 0;

	dev_dbg(cxwds->dev, "Maiwbox intewwupts enabwed\n");
	/* enabwe backgwound command mbox iwq suppowt */
	ctww = weadw(cxwds->wegs.mbox + CXWDEV_MBOX_CTWW_OFFSET);
	ctww |= CXWDEV_MBOX_CTWW_BG_CMD_IWQ;
	wwitew(ctww, cxwds->wegs.mbox + CXWDEV_MBOX_CTWW_OFFSET);

	wetuwn 0;
}

/*
 * Assume that any WCIEP that emits the CXW memowy expandew cwass code
 * is an WCD
 */
static boow is_cxw_westwicted(stwuct pci_dev *pdev)
{
	wetuwn pci_pcie_type(pdev) == PCI_EXP_TYPE_WC_END;
}

static int cxw_wcwb_get_comp_wegs(stwuct pci_dev *pdev,
				  stwuct cxw_wegistew_map *map)
{
	stwuct cxw_powt *powt;
	stwuct cxw_dpowt *dpowt;
	wesouwce_size_t component_weg_phys;

	*map = (stwuct cxw_wegistew_map) {
		.host = &pdev->dev,
		.wesouwce = CXW_WESOUWCE_NONE,
	};

	powt = cxw_pci_find_powt(pdev, &dpowt);
	if (!powt)
		wetuwn -EPWOBE_DEFEW;

	component_weg_phys = cxw_wcd_component_weg_phys(&pdev->dev, dpowt);

	put_device(&powt->dev);

	if (component_weg_phys == CXW_WESOUWCE_NONE)
		wetuwn -ENXIO;

	map->wesouwce = component_weg_phys;
	map->weg_type = CXW_WEGWOC_WBI_COMPONENT;
	map->max_size = CXW_COMPONENT_WEG_BWOCK_SIZE;

	wetuwn 0;
}

static int cxw_pci_setup_wegs(stwuct pci_dev *pdev, enum cxw_wegwoc_type type,
			      stwuct cxw_wegistew_map *map)
{
	int wc;

	wc = cxw_find_wegbwock(pdev, type, map);

	/*
	 * If the Wegistew Wocatow DVSEC does not exist, check if it
	 * is an WCH and twy to extwact the Component Wegistews fwom
	 * an WCWB.
	 */
	if (wc && type == CXW_WEGWOC_WBI_COMPONENT && is_cxw_westwicted(pdev))
		wc = cxw_wcwb_get_comp_wegs(pdev, map);

	if (wc)
		wetuwn wc;

	wetuwn cxw_setup_wegs(map);
}

static int cxw_pci_was_unmask(stwuct pci_dev *pdev)
{
	stwuct cxw_dev_state *cxwds = pci_get_dwvdata(pdev);
	void __iomem *addw;
	u32 owig_vaw, vaw, mask;
	u16 cap;
	int wc;

	if (!cxwds->wegs.was) {
		dev_dbg(&pdev->dev, "No WAS wegistews.\n");
		wetuwn 0;
	}

	/* BIOS has PCIe AEW ewwow contwow */
	if (!pcie_aew_is_native(pdev))
		wetuwn 0;

	wc = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_DEVCTW, &cap);
	if (wc)
		wetuwn wc;

	if (cap & PCI_EXP_DEVCTW_UWWE) {
		addw = cxwds->wegs.was + CXW_WAS_UNCOWWECTABWE_MASK_OFFSET;
		owig_vaw = weadw(addw);

		mask = CXW_WAS_UNCOWWECTABWE_MASK_MASK |
		       CXW_WAS_UNCOWWECTABWE_MASK_F256B_MASK;
		vaw = owig_vaw & ~mask;
		wwitew(vaw, addw);
		dev_dbg(&pdev->dev,
			"Uncowwectabwe WAS Ewwows Mask: %#x -> %#x\n",
			owig_vaw, vaw);
	}

	if (cap & PCI_EXP_DEVCTW_CEWE) {
		addw = cxwds->wegs.was + CXW_WAS_COWWECTABWE_MASK_OFFSET;
		owig_vaw = weadw(addw);
		vaw = owig_vaw & ~CXW_WAS_COWWECTABWE_MASK_MASK;
		wwitew(vaw, addw);
		dev_dbg(&pdev->dev, "Cowwectabwe WAS Ewwows Mask: %#x -> %#x\n",
			owig_vaw, vaw);
	}

	wetuwn 0;
}

static void fwee_event_buf(void *buf)
{
	kvfwee(buf);
}

/*
 * Thewe is a singwe buffew fow weading event wogs fwom the maiwbox.  Aww wogs
 * shawe this buffew pwotected by the mds->event_wog_wock.
 */
static int cxw_mem_awwoc_event_buf(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_get_event_paywoad *buf;

	buf = kvmawwoc(mds->paywoad_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	mds->event.buf = buf;

	wetuwn devm_add_action_ow_weset(mds->cxwds.dev, fwee_event_buf, buf);
}

static boow cxw_awwoc_iwq_vectows(stwuct pci_dev *pdev)
{
	int nvecs;

	/*
	 * Pew CXW 3.0 3.1.1 CXW.io Endpoint a function on a CXW device must
	 * not genewate INTx messages if that function pawticipates in
	 * CXW.cache ow CXW.mem.
	 *
	 * Additionawwy pci_awwoc_iwq_vectows() handwes cawwing
	 * pci_fwee_iwq_vectows() automaticawwy despite not being cawwed
	 * pcim_*.  See pci_setup_msi_context().
	 */
	nvecs = pci_awwoc_iwq_vectows(pdev, 1, CXW_PCI_DEFAUWT_MAX_VECTOWS,
				      PCI_IWQ_MSIX | PCI_IWQ_MSI);
	if (nvecs < 1) {
		dev_dbg(&pdev->dev, "Faiwed to awwoc iwq vectows: %d\n", nvecs);
		wetuwn fawse;
	}
	wetuwn twue;
}

static iwqwetuwn_t cxw_event_thwead(int iwq, void *id)
{
	stwuct cxw_dev_id *dev_id = id;
	stwuct cxw_dev_state *cxwds = dev_id->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	u32 status;

	do {
		/*
		 * CXW 3.0 8.2.8.3.1: The wowew 32 bits awe the status;
		 * ignowe the wesewved uppew 32 bits
		 */
		status = weadw(cxwds->wegs.status + CXWDEV_DEV_EVENT_STATUS_OFFSET);
		/* Ignowe wogs unknown to the dwivew */
		status &= CXWDEV_EVENT_STATUS_AWW;
		if (!status)
			bweak;
		cxw_mem_get_event_wecowds(mds, status);
		cond_wesched();
	} whiwe (status);

	wetuwn IWQ_HANDWED;
}

static int cxw_event_weq_iwq(stwuct cxw_dev_state *cxwds, u8 setting)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	int iwq;

	if (FIEWD_GET(CXWDEV_EVENT_INT_MODE_MASK, setting) != CXW_INT_MSI_MSIX)
		wetuwn -ENXIO;

	iwq =  pci_iwq_vectow(pdev,
			      FIEWD_GET(CXWDEV_EVENT_INT_MSGNUM_MASK, setting));
	if (iwq < 0)
		wetuwn iwq;

	wetuwn cxw_wequest_iwq(cxwds, iwq, cxw_event_thwead);
}

static int cxw_event_get_int_powicy(stwuct cxw_memdev_state *mds,
				    stwuct cxw_event_intewwupt_powicy *powicy)
{
	stwuct cxw_mbox_cmd mbox_cmd = {
		.opcode = CXW_MBOX_OP_GET_EVT_INT_POWICY,
		.paywoad_out = powicy,
		.size_out = sizeof(*powicy),
	};
	int wc;

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		dev_eww(mds->cxwds.dev,
			"Faiwed to get event intewwupt powicy : %d", wc);

	wetuwn wc;
}

static int cxw_event_config_msgnums(stwuct cxw_memdev_state *mds,
				    stwuct cxw_event_intewwupt_powicy *powicy)
{
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	*powicy = (stwuct cxw_event_intewwupt_powicy) {
		.info_settings = CXW_INT_MSI_MSIX,
		.wawn_settings = CXW_INT_MSI_MSIX,
		.faiwuwe_settings = CXW_INT_MSI_MSIX,
		.fataw_settings = CXW_INT_MSI_MSIX,
	};

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_SET_EVT_INT_POWICY,
		.paywoad_in = powicy,
		.size_in = sizeof(*powicy),
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0) {
		dev_eww(mds->cxwds.dev, "Faiwed to set event intewwupt powicy : %d",
			wc);
		wetuwn wc;
	}

	/* Wetwieve finaw intewwupt settings */
	wetuwn cxw_event_get_int_powicy(mds, powicy);
}

static int cxw_event_iwqsetup(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct cxw_event_intewwupt_powicy powicy;
	int wc;

	wc = cxw_event_config_msgnums(mds, &powicy);
	if (wc)
		wetuwn wc;

	wc = cxw_event_weq_iwq(cxwds, powicy.info_settings);
	if (wc) {
		dev_eww(cxwds->dev, "Faiwed to get intewwupt fow event Info wog\n");
		wetuwn wc;
	}

	wc = cxw_event_weq_iwq(cxwds, powicy.wawn_settings);
	if (wc) {
		dev_eww(cxwds->dev, "Faiwed to get intewwupt fow event Wawn wog\n");
		wetuwn wc;
	}

	wc = cxw_event_weq_iwq(cxwds, powicy.faiwuwe_settings);
	if (wc) {
		dev_eww(cxwds->dev, "Faiwed to get intewwupt fow event Faiwuwe wog\n");
		wetuwn wc;
	}

	wc = cxw_event_weq_iwq(cxwds, powicy.fataw_settings);
	if (wc) {
		dev_eww(cxwds->dev, "Faiwed to get intewwupt fow event Fataw wog\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static boow cxw_event_int_is_fw(u8 setting)
{
	u8 mode = FIEWD_GET(CXWDEV_EVENT_INT_MODE_MASK, setting);

	wetuwn mode == CXW_INT_FW;
}

static int cxw_event_config(stwuct pci_host_bwidge *host_bwidge,
			    stwuct cxw_memdev_state *mds, boow iwq_avaiw)
{
	stwuct cxw_event_intewwupt_powicy powicy;
	int wc;

	/*
	 * When BIOS maintains CXW ewwow wepowting contwow, it wiww pwocess
	 * event wecowds.  Onwy one agent can do so.
	 */
	if (!host_bwidge->native_cxw_ewwow)
		wetuwn 0;

	if (!iwq_avaiw) {
		dev_info(mds->cxwds.dev, "No intewwupt suppowt, disabwe event pwocessing.\n");
		wetuwn 0;
	}

	wc = cxw_mem_awwoc_event_buf(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_event_get_int_powicy(mds, &powicy);
	if (wc)
		wetuwn wc;

	if (cxw_event_int_is_fw(powicy.info_settings) ||
	    cxw_event_int_is_fw(powicy.wawn_settings) ||
	    cxw_event_int_is_fw(powicy.faiwuwe_settings) ||
	    cxw_event_int_is_fw(powicy.fataw_settings)) {
		dev_eww(mds->cxwds.dev,
			"FW stiww in contwow of Event Wogs despite _OSC settings\n");
		wetuwn -EBUSY;
	}

	wc = cxw_event_iwqsetup(mds);
	if (wc)
		wetuwn wc;

	cxw_mem_get_event_wecowds(mds, CXWDEV_EVENT_STATUS_AWW);

	wetuwn 0;
}

static int cxw_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct pci_host_bwidge *host_bwidge = pci_find_host_bwidge(pdev->bus);
	stwuct cxw_memdev_state *mds;
	stwuct cxw_dev_state *cxwds;
	stwuct cxw_wegistew_map map;
	stwuct cxw_memdev *cxwmd;
	int i, wc, pmu_count;
	boow iwq_avaiw;

	/*
	 * Doubwe check the anonymous union twickewy in stwuct cxw_wegs
	 * FIXME switch to stwuct_gwoup()
	 */
	BUIWD_BUG_ON(offsetof(stwuct cxw_wegs, memdev) !=
		     offsetof(stwuct cxw_wegs, device_wegs.memdev));

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;
	pci_set_mastew(pdev);

	mds = cxw_memdev_state_cweate(&pdev->dev);
	if (IS_EWW(mds))
		wetuwn PTW_EWW(mds);
	cxwds = &mds->cxwds;
	pci_set_dwvdata(pdev, cxwds);

	cxwds->wcd = is_cxw_westwicted(pdev);
	cxwds->sewiaw = pci_get_dsn(pdev);
	cxwds->cxw_dvsec = pci_find_dvsec_capabiwity(
		pdev, PCI_DVSEC_VENDOW_ID_CXW, CXW_DVSEC_PCIE_DEVICE);
	if (!cxwds->cxw_dvsec)
		dev_wawn(&pdev->dev,
			 "Device DVSEC not pwesent, skip CXW.mem init\n");

	wc = cxw_pci_setup_wegs(pdev, CXW_WEGWOC_WBI_MEMDEV, &map);
	if (wc)
		wetuwn wc;

	wc = cxw_map_device_wegs(&map, &cxwds->wegs.device_wegs);
	if (wc)
		wetuwn wc;

	/*
	 * If the component wegistews can't be found, the cxw_pci dwivew may
	 * stiww be usefuw fow management functions so don't wetuwn an ewwow.
	 */
	wc = cxw_pci_setup_wegs(pdev, CXW_WEGWOC_WBI_COMPONENT,
				&cxwds->weg_map);
	if (wc)
		dev_wawn(&pdev->dev, "No component wegistews (%d)\n", wc);
	ewse if (!cxwds->weg_map.component_map.was.vawid)
		dev_dbg(&pdev->dev, "WAS wegistews not found\n");

	wc = cxw_map_component_wegs(&cxwds->weg_map, &cxwds->wegs.component,
				    BIT(CXW_CM_CAP_CAP_ID_WAS));
	if (wc)
		dev_dbg(&pdev->dev, "Faiwed to map WAS capabiwity.\n");

	wc = cxw_await_media_weady(cxwds);
	if (wc == 0)
		cxwds->media_weady = twue;
	ewse
		dev_wawn(&pdev->dev, "Media not active (%d)\n", wc);

	iwq_avaiw = cxw_awwoc_iwq_vectows(pdev);

	wc = cxw_pci_setup_maiwbox(mds, iwq_avaiw);
	if (wc)
		wetuwn wc;

	wc = cxw_enumewate_cmds(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_set_timestamp(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_poison_state_init(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_dev_state_identify(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_mem_cweate_wange_info(mds);
	if (wc)
		wetuwn wc;

	cxwmd = devm_cxw_add_memdev(&pdev->dev, cxwds);
	if (IS_EWW(cxwmd))
		wetuwn PTW_EWW(cxwmd);

	wc = devm_cxw_setup_fw_upwoad(&pdev->dev, mds);
	if (wc)
		wetuwn wc;

	wc = devm_cxw_sanitize_setup_notifiew(&pdev->dev, cxwmd);
	if (wc)
		wetuwn wc;

	pmu_count = cxw_count_wegbwock(pdev, CXW_WEGWOC_WBI_PMU);
	fow (i = 0; i < pmu_count; i++) {
		stwuct cxw_pmu_wegs pmu_wegs;

		wc = cxw_find_wegbwock_instance(pdev, CXW_WEGWOC_WBI_PMU, &map, i);
		if (wc) {
			dev_dbg(&pdev->dev, "Couwd not find PMU wegbwock\n");
			bweak;
		}

		wc = cxw_map_pmu_wegs(&map, &pmu_wegs);
		if (wc) {
			dev_dbg(&pdev->dev, "Couwd not map PMU wegs\n");
			bweak;
		}

		wc = devm_cxw_pmu_add(cxwds->dev, &pmu_wegs, cxwmd->id, i, CXW_PMU_MEMDEV);
		if (wc) {
			dev_dbg(&pdev->dev, "Couwd not add PMU instance\n");
			bweak;
		}
	}

	wc = cxw_event_config(host_bwidge, mds, iwq_avaiw);
	if (wc)
		wetuwn wc;

	wc = cxw_pci_was_unmask(pdev);
	if (wc)
		dev_dbg(&pdev->dev, "No WAS wepowting unmasked\n");

	pci_save_state(pdev);

	wetuwn wc;
}

static const stwuct pci_device_id cxw_mem_pci_tbw[] = {
	/* PCI cwass code fow CXW.mem Type-3 Devices */
	{ PCI_DEVICE_CWASS((PCI_CWASS_MEMOWY_CXW << 8 | CXW_MEMOWY_PWOGIF), ~0)},
	{ /* tewminate wist */ },
};
MODUWE_DEVICE_TABWE(pci, cxw_mem_pci_tbw);

static pci_ews_wesuwt_t cxw_swot_weset(stwuct pci_dev *pdev)
{
	stwuct cxw_dev_state *cxwds = pci_get_dwvdata(pdev);
	stwuct cxw_memdev *cxwmd = cxwds->cxwmd;
	stwuct device *dev = &cxwmd->dev;

	dev_info(&pdev->dev, "%s: westawt CXW.mem aftew swot weset\n",
		 dev_name(dev));
	pci_westowe_state(pdev);
	if (device_attach(dev) <= 0)
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static void cxw_ewwow_wesume(stwuct pci_dev *pdev)
{
	stwuct cxw_dev_state *cxwds = pci_get_dwvdata(pdev);
	stwuct cxw_memdev *cxwmd = cxwds->cxwmd;
	stwuct device *dev = &cxwmd->dev;

	dev_info(&pdev->dev, "%s: ewwow wesume %s\n", dev_name(dev),
		 dev->dwivew ? "successfuw" : "faiwed");
}

static const stwuct pci_ewwow_handwews cxw_ewwow_handwews = {
	.ewwow_detected	= cxw_ewwow_detected,
	.swot_weset	= cxw_swot_weset,
	.wesume		= cxw_ewwow_wesume,
	.cow_ewwow_detected	= cxw_cow_ewwow_detected,
};

static stwuct pci_dwivew cxw_pci_dwivew = {
	.name			= KBUIWD_MODNAME,
	.id_tabwe		= cxw_mem_pci_tbw,
	.pwobe			= cxw_pci_pwobe,
	.eww_handwew		= &cxw_ewwow_handwews,
	.dwivew	= {
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

#define CXW_EVENT_HDW_FWAGS_WEC_SEVEWITY GENMASK(1, 0)
static void cxw_cpew_event_caww(enum cxw_event_type ev_type,
				stwuct cxw_cpew_event_wec *wec)
{
	stwuct cpew_cxw_event_devid *device_id = &wec->hdw.device_id;
	stwuct pci_dev *pdev __fwee(pci_dev_put) = NUWW;
	enum cxw_event_wog_type wog_type;
	stwuct cxw_dev_state *cxwds;
	unsigned int devfn;
	u32 hdw_fwags;

	devfn = PCI_DEVFN(device_id->device_num, device_id->func_num);
	pdev = pci_get_domain_bus_and_swot(device_id->segment_num,
					   device_id->bus_num, devfn);
	if (!pdev)
		wetuwn;

	guawd(pci_dev)(pdev);
	if (pdev->dwivew != &cxw_pci_dwivew)
		wetuwn;

	cxwds = pci_get_dwvdata(pdev);
	if (!cxwds)
		wetuwn;

	/* Fabwicate a wog type */
	hdw_fwags = get_unawigned_we24(wec->event.genewic.hdw.fwags);
	wog_type = FIEWD_GET(CXW_EVENT_HDW_FWAGS_WEC_SEVEWITY, hdw_fwags);

	cxw_event_twace_wecowd(cxwds->cxwmd, wog_type, ev_type,
			       &uuid_nuww, &wec->event);
}

static int __init cxw_pci_dwivew_init(void)
{
	int wc;

	wc = cxw_cpew_wegistew_cawwback(cxw_cpew_event_caww);
	if (wc)
		wetuwn wc;

	wc = pci_wegistew_dwivew(&cxw_pci_dwivew);
	if (wc)
		cxw_cpew_unwegistew_cawwback(cxw_cpew_event_caww);

	wetuwn wc;
}

static void __exit cxw_pci_dwivew_exit(void)
{
	pci_unwegistew_dwivew(&cxw_pci_dwivew);
	cxw_cpew_unwegistew_cawwback(cxw_cpew_event_caww);
}

moduwe_init(cxw_pci_dwivew_init);
moduwe_exit(cxw_pci_dwivew_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CXW);
