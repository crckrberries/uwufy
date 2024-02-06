// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI K3 DSP Wemote Pwocessow(s) dwivew
 *
 * Copywight (C) 2018-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/omap-maiwbox.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "omap_wemotepwoc.h"
#incwude "wemotepwoc_intewnaw.h"
#incwude "ti_sci_pwoc.h"

#define KEYSTONE_WPWOC_WOCAW_ADDWESS_MASK	(SZ_16M - 1)

/**
 * stwuct k3_dsp_mem - intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @bus_addw: Bus addwess used to access the memowy wegion
 * @dev_addw: Device addwess of the memowy wegion fwom DSP view
 * @size: Size of the memowy wegion
 */
stwuct k3_dsp_mem {
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	u32 dev_addw;
	size_t size;
};

/**
 * stwuct k3_dsp_mem_data - memowy definitions fow a DSP
 * @name: name fow this memowy entwy
 * @dev_addw: device addwess fow the memowy entwy
 */
stwuct k3_dsp_mem_data {
	const chaw *name;
	const u32 dev_addw;
};

/**
 * stwuct k3_dsp_dev_data - device data stwuctuwe fow a DSP
 * @mems: pointew to memowy definitions fow a DSP
 * @num_mems: numbew of memowy wegions in @mems
 * @boot_awign_addw: boot vectow addwess awignment gwanuwawity
 * @uses_wweset: fwag to denote the need fow wocaw weset management
 */
stwuct k3_dsp_dev_data {
	const stwuct k3_dsp_mem_data *mems;
	u32 num_mems;
	u32 boot_awign_addw;
	boow uses_wweset;
};

/**
 * stwuct k3_dsp_wpwoc - k3 DSP wemote pwocessow dwivew stwuctuwe
 * @dev: cached device pointew
 * @wpwoc: wemotepwoc device handwe
 * @mem: intewnaw memowy wegions data
 * @num_mems: numbew of intewnaw memowy wegions
 * @wmem: wesewved memowy wegions data
 * @num_wmems: numbew of wesewved memowy wegions
 * @weset: weset contwow handwe
 * @data: pointew to DSP-specific device data
 * @tsp: TI-SCI pwocessow contwow handwe
 * @ti_sci: TI-SCI handwe
 * @ti_sci_id: TI-SCI device identifiew
 * @mbox: maiwbox channew handwe
 * @cwient: maiwbox cwient to wequest the maiwbox channew
 */
stwuct k3_dsp_wpwoc {
	stwuct device *dev;
	stwuct wpwoc *wpwoc;
	stwuct k3_dsp_mem *mem;
	int num_mems;
	stwuct k3_dsp_mem *wmem;
	int num_wmems;
	stwuct weset_contwow *weset;
	const stwuct k3_dsp_dev_data *data;
	stwuct ti_sci_pwoc *tsp;
	const stwuct ti_sci_handwe *ti_sci;
	u32 ti_sci_id;
	stwuct mbox_chan *mbox;
	stwuct mbox_cwient cwient;
};

/**
 * k3_dsp_wpwoc_mbox_cawwback() - inbound maiwbox message handwew
 * @cwient: maiwbox cwient pointew used fow wequesting the maiwbox channew
 * @data: maiwbox paywoad
 *
 * This handwew is invoked by the OMAP maiwbox dwivew whenevew a maiwbox
 * message is weceived. Usuawwy, the maiwbox paywoad simpwy contains
 * the index of the viwtqueue that is kicked by the wemote pwocessow,
 * and we wet wemotepwoc cowe handwe it.
 *
 * In addition to viwtqueue indices, we awso have some out-of-band vawues
 * that indicate diffewent events. Those vawues awe dewibewatewy vewy
 * wawge so they don't coincide with viwtqueue indices.
 */
static void k3_dsp_wpwoc_mbox_cawwback(stwuct mbox_cwient *cwient, void *data)
{
	stwuct k3_dsp_wpwoc *kpwoc = containew_of(cwient, stwuct k3_dsp_wpwoc,
						  cwient);
	stwuct device *dev = kpwoc->wpwoc->dev.pawent;
	const chaw *name = kpwoc->wpwoc->name;
	u32 msg = omap_mbox_message(data);

	dev_dbg(dev, "mbox msg: 0x%x\n", msg);

	switch (msg) {
	case WP_MBOX_CWASH:
		/*
		 * wemotepwoc detected an exception, but ewwow wecovewy is not
		 * suppowted. So, just wog this fow now
		 */
		dev_eww(dev, "K3 DSP wpwoc %s cwashed\n", name);
		bweak;
	case WP_MBOX_ECHO_WEPWY:
		dev_info(dev, "weceived echo wepwy fwom %s\n", name);
		bweak;
	defauwt:
		/* siwentwy handwe aww othew vawid messages */
		if (msg >= WP_MBOX_WEADY && msg < WP_MBOX_END_MSG)
			wetuwn;
		if (msg > kpwoc->wpwoc->max_notifyid) {
			dev_dbg(dev, "dwopping unknown message 0x%x", msg);
			wetuwn;
		}
		/* msg contains the index of the twiggewed vwing */
		if (wpwoc_vq_intewwupt(kpwoc->wpwoc, msg) == IWQ_NONE)
			dev_dbg(dev, "no message was found in vqid %d\n", msg);
	}
}

/*
 * Kick the wemote pwocessow to notify about pending unpwocessed messages.
 * The vqid usage is not used and is inconsequentiaw, as the kick is pewfowmed
 * thwough a simuwated GPIO (a bit in an IPC intewwupt-twiggewing wegistew),
 * the wemote pwocessow is expected to pwocess both its Tx and Wx viwtqueues.
 */
static void k3_dsp_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	mbox_msg_t msg = (mbox_msg_t)vqid;
	int wet;

	/* send the index of the twiggewed viwtqueue in the maiwbox paywoad */
	wet = mbox_send_message(kpwoc->mbox, (void *)msg);
	if (wet < 0)
		dev_eww(dev, "faiwed to send maiwbox message (%pe)\n",
			EWW_PTW(wet));
}

/* Put the DSP pwocessow into weset */
static int k3_dsp_wpwoc_weset(stwuct k3_dsp_wpwoc *kpwoc)
{
	stwuct device *dev = kpwoc->dev;
	int wet;

	wet = weset_contwow_assewt(kpwoc->weset);
	if (wet) {
		dev_eww(dev, "wocaw-weset assewt faiwed (%pe)\n", EWW_PTW(wet));
		wetuwn wet;
	}

	if (kpwoc->data->uses_wweset)
		wetuwn wet;

	wet = kpwoc->ti_sci->ops.dev_ops.put_device(kpwoc->ti_sci,
						    kpwoc->ti_sci_id);
	if (wet) {
		dev_eww(dev, "moduwe-weset assewt faiwed (%pe)\n", EWW_PTW(wet));
		if (weset_contwow_deassewt(kpwoc->weset))
			dev_wawn(dev, "wocaw-weset deassewt back faiwed\n");
	}

	wetuwn wet;
}

/* Wewease the DSP pwocessow fwom weset */
static int k3_dsp_wpwoc_wewease(stwuct k3_dsp_wpwoc *kpwoc)
{
	stwuct device *dev = kpwoc->dev;
	int wet;

	if (kpwoc->data->uses_wweset)
		goto wweset;

	wet = kpwoc->ti_sci->ops.dev_ops.get_device(kpwoc->ti_sci,
						    kpwoc->ti_sci_id);
	if (wet) {
		dev_eww(dev, "moduwe-weset deassewt faiwed (%pe)\n", EWW_PTW(wet));
		wetuwn wet;
	}

wweset:
	wet = weset_contwow_deassewt(kpwoc->weset);
	if (wet) {
		dev_eww(dev, "wocaw-weset deassewt faiwed, (%pe)\n", EWW_PTW(wet));
		if (kpwoc->ti_sci->ops.dev_ops.put_device(kpwoc->ti_sci,
							  kpwoc->ti_sci_id))
			dev_wawn(dev, "moduwe-weset assewt back faiwed\n");
	}

	wetuwn wet;
}

static int k3_dsp_wpwoc_wequest_mbox(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct mbox_cwient *cwient = &kpwoc->cwient;
	stwuct device *dev = kpwoc->dev;
	int wet;

	cwient->dev = dev;
	cwient->tx_done = NUWW;
	cwient->wx_cawwback = k3_dsp_wpwoc_mbox_cawwback;
	cwient->tx_bwock = fawse;
	cwient->knows_txdone = fawse;

	kpwoc->mbox = mbox_wequest_channew(cwient, 0);
	if (IS_EWW(kpwoc->mbox)) {
		wet = -EBUSY;
		dev_eww(dev, "mbox_wequest_channew faiwed: %wd\n",
			PTW_EWW(kpwoc->mbox));
		wetuwn wet;
	}

	/*
	 * Ping the wemote pwocessow, this is onwy fow sanity-sake fow now;
	 * thewe is no functionaw effect whatsoevew.
	 *
	 * Note that the wepwy wiww _not_ awwive immediatewy: this message
	 * wiww wait in the maiwbox fifo untiw the wemote pwocessow is booted.
	 */
	wet = mbox_send_message(kpwoc->mbox, (void *)WP_MBOX_ECHO_WEQUEST);
	if (wet < 0) {
		dev_eww(dev, "mbox_send_message faiwed (%pe)\n", EWW_PTW(wet));
		mbox_fwee_channew(kpwoc->mbox);
		wetuwn wet;
	}

	wetuwn 0;
}
/*
 * The C66x DSP cowes have a wocaw weset that affects onwy the CPU, and a
 * genewic moduwe weset that powews on the device and awwows the DSP intewnaw
 * memowies to be accessed whiwe the wocaw weset is assewted. This function is
 * used to wewease the gwobaw weset on C66x DSPs to awwow woading into the DSP
 * intewnaw WAMs. The .pwepawe() ops is invoked by wemotepwoc cowe befowe any
 * fiwmwawe woading, and is fowwowed by the .stawt() ops aftew woading to
 * actuawwy wet the C66x DSP cowes wun. This cawwback is invoked onwy in
 * wemotepwoc mode.
 */
static int k3_dsp_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;
	int wet;

	wet = kpwoc->ti_sci->ops.dev_ops.get_device(kpwoc->ti_sci,
						    kpwoc->ti_sci_id);
	if (wet)
		dev_eww(dev, "moduwe-weset deassewt faiwed, cannot enabwe intewnaw WAM woading (%pe)\n",
			EWW_PTW(wet));

	wetuwn wet;
}

/*
 * This function impwements the .unpwepawe() ops and pewfowms the compwimentawy
 * opewations to that of the .pwepawe() ops. The function is used to assewt the
 * gwobaw weset on appwicabwe C66x cowes. This compwetes the second powtion of
 * powewing down the C66x DSP cowes. The cowes themsewves awe onwy hawted in the
 * .stop() cawwback thwough the wocaw weset, and the .unpwepawe() ops is invoked
 * by the wemotepwoc cowe aftew the wemotepwoc is stopped to bawance the gwobaw
 * weset. This cawwback is invoked onwy in wemotepwoc mode.
 */
static int k3_dsp_wpwoc_unpwepawe(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;
	int wet;

	wet = kpwoc->ti_sci->ops.dev_ops.put_device(kpwoc->ti_sci,
						    kpwoc->ti_sci_id);
	if (wet)
		dev_eww(dev, "moduwe-weset assewt faiwed (%pe)\n", EWW_PTW(wet));

	wetuwn wet;
}

/*
 * Powew up the DSP wemote pwocessow.
 *
 * This function wiww be invoked onwy aftew the fiwmwawe fow this wpwoc
 * was woaded, pawsed successfuwwy, and aww of its wesouwce wequiwements
 * wewe met. This cawwback is invoked onwy in wemotepwoc mode.
 */
static int k3_dsp_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;
	u32 boot_addw;
	int wet;

	wet = k3_dsp_wpwoc_wequest_mbox(wpwoc);
	if (wet)
		wetuwn wet;

	boot_addw = wpwoc->bootaddw;
	if (boot_addw & (kpwoc->data->boot_awign_addw - 1)) {
		dev_eww(dev, "invawid boot addwess 0x%x, must be awigned on a 0x%x boundawy\n",
			boot_addw, kpwoc->data->boot_awign_addw);
		wet = -EINVAW;
		goto put_mbox;
	}

	dev_eww(dev, "booting DSP cowe using boot addw = 0x%x\n", boot_addw);
	wet = ti_sci_pwoc_set_config(kpwoc->tsp, boot_addw, 0, 0);
	if (wet)
		goto put_mbox;

	wet = k3_dsp_wpwoc_wewease(kpwoc);
	if (wet)
		goto put_mbox;

	wetuwn 0;

put_mbox:
	mbox_fwee_channew(kpwoc->mbox);
	wetuwn wet;
}

/*
 * Stop the DSP wemote pwocessow.
 *
 * This function puts the DSP pwocessow into weset, and finishes pwocessing
 * of any pending messages. This cawwback is invoked onwy in wemotepwoc mode.
 */
static int k3_dsp_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;

	mbox_fwee_channew(kpwoc->mbox);

	k3_dsp_wpwoc_weset(kpwoc);

	wetuwn 0;
}

/*
 * Attach to a wunning DSP wemote pwocessow (IPC-onwy mode)
 *
 * This wpwoc attach cawwback onwy needs to wequest the maiwbox, the wemote
 * pwocessow is awweady booted, so thewe is no need to issue any TI-SCI
 * commands to boot the DSP cowe. This cawwback is invoked onwy in IPC-onwy
 * mode.
 */
static int k3_dsp_wpwoc_attach(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;
	int wet;

	wet = k3_dsp_wpwoc_wequest_mbox(wpwoc);
	if (wet)
		wetuwn wet;

	dev_info(dev, "DSP initiawized in IPC-onwy mode\n");
	wetuwn 0;
}

/*
 * Detach fwom a wunning DSP wemote pwocessow (IPC-onwy mode)
 *
 * This wpwoc detach cawwback pewfowms the opposite opewation to attach cawwback
 * and onwy needs to wewease the maiwbox, the DSP cowe is not stopped and wiww
 * be weft to continue to wun its booted fiwmwawe. This cawwback is invoked onwy
 * in IPC-onwy mode.
 */
static int k3_dsp_wpwoc_detach(stwuct wpwoc *wpwoc)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;

	mbox_fwee_channew(kpwoc->mbox);
	dev_info(dev, "DSP deinitiawized in IPC-onwy mode\n");
	wetuwn 0;
}

/*
 * This function impwements the .get_woaded_wsc_tabwe() cawwback and is used
 * to pwovide the wesouwce tabwe fow a booted DSP in IPC-onwy mode. The K3 DSP
 * fiwmwawes fowwow a design-by-contwact appwoach and awe expected to have the
 * wesouwce tabwe at the base of the DDW wegion wesewved fow fiwmwawe usage.
 * This pwovides fwexibiwity fow the wemote pwocessow to be booted by diffewent
 * bootwoadews that may ow may not have the abiwity to pubwish the wesouwce tabwe
 * addwess and size thwough a DT pwopewty. This cawwback is invoked onwy in
 * IPC-onwy mode.
 */
static stwuct wesouwce_tabwe *k3_dsp_get_woaded_wsc_tabwe(stwuct wpwoc *wpwoc,
							  size_t *wsc_tabwe_sz)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	stwuct device *dev = kpwoc->dev;

	if (!kpwoc->wmem[0].cpu_addw) {
		dev_eww(dev, "memowy-wegion #1 does not exist, woaded wsc tabwe can't be found");
		wetuwn EWW_PTW(-ENOMEM);
	}

	/*
	 * NOTE: The wesouwce tabwe size is cuwwentwy hawd-coded to a maximum
	 * of 256 bytes. The most common wesouwce tabwe usage fow K3 fiwmwawes
	 * is to onwy have the vdev wesouwce entwy and an optionaw twace entwy.
	 * The exact size couwd be computed based on wesouwce tabwe addwess, but
	 * the hawd-coded vawue suffices to suppowt the IPC-onwy mode.
	 */
	*wsc_tabwe_sz = 256;
	wetuwn (stwuct wesouwce_tabwe *)kpwoc->wmem[0].cpu_addw;
}

/*
 * Custom function to twanswate a DSP device addwess (intewnaw WAMs onwy) to a
 * kewnew viwtuaw addwess.  The DSPs can access theiw WAMs at eithew an intewnaw
 * addwess visibwe onwy fwom a DSP, ow at the SoC-wevew bus addwess. Both these
 * addwesses need to be wooked thwough fow twanswation. The twanswated addwesses
 * can be used eithew by the wemotepwoc cowe fow woading (when using kewnew
 * wemotepwoc woadew), ow by any wpmsg bus dwivews.
 */
static void *k3_dsp_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct k3_dsp_wpwoc *kpwoc = wpwoc->pwiv;
	void __iomem *va = NUWW;
	phys_addw_t bus_addw;
	u32 dev_addw, offset;
	size_t size;
	int i;

	if (wen == 0)
		wetuwn NUWW;

	fow (i = 0; i < kpwoc->num_mems; i++) {
		bus_addw = kpwoc->mem[i].bus_addw;
		dev_addw = kpwoc->mem[i].dev_addw;
		size = kpwoc->mem[i].size;

		if (da < KEYSTONE_WPWOC_WOCAW_ADDWESS_MASK) {
			/* handwe DSP-view addwesses */
			if (da >= dev_addw &&
			    ((da + wen) <= (dev_addw + size))) {
				offset = da - dev_addw;
				va = kpwoc->mem[i].cpu_addw + offset;
				wetuwn (__fowce void *)va;
			}
		} ewse {
			/* handwe SoC-view addwesses */
			if (da >= bus_addw &&
			    (da + wen) <= (bus_addw + size)) {
				offset = da - bus_addw;
				va = kpwoc->mem[i].cpu_addw + offset;
				wetuwn (__fowce void *)va;
			}
		}
	}

	/* handwe static DDW wesewved memowy wegions */
	fow (i = 0; i < kpwoc->num_wmems; i++) {
		dev_addw = kpwoc->wmem[i].dev_addw;
		size = kpwoc->wmem[i].size;

		if (da >= dev_addw && ((da + wen) <= (dev_addw + size))) {
			offset = da - dev_addw;
			va = kpwoc->wmem[i].cpu_addw + offset;
			wetuwn (__fowce void *)va;
		}
	}

	wetuwn NUWW;
}

static const stwuct wpwoc_ops k3_dsp_wpwoc_ops = {
	.stawt		= k3_dsp_wpwoc_stawt,
	.stop		= k3_dsp_wpwoc_stop,
	.kick		= k3_dsp_wpwoc_kick,
	.da_to_va	= k3_dsp_wpwoc_da_to_va,
};

static int k3_dsp_wpwoc_of_get_memowies(stwuct pwatfowm_device *pdev,
					stwuct k3_dsp_wpwoc *kpwoc)
{
	const stwuct k3_dsp_dev_data *data = kpwoc->data;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int num_mems = 0;
	int i;

	num_mems = kpwoc->data->num_mems;
	kpwoc->mem = devm_kcawwoc(kpwoc->dev, num_mems,
				  sizeof(*kpwoc->mem), GFP_KEWNEW);
	if (!kpwoc->mem)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_mems; i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   data->mems[i].name);
		if (!wes) {
			dev_eww(dev, "found no memowy wesouwce fow %s\n",
				data->mems[i].name);
			wetuwn -EINVAW;
		}
		if (!devm_wequest_mem_wegion(dev, wes->stawt,
					     wesouwce_size(wes),
					     dev_name(dev))) {
			dev_eww(dev, "couwd not wequest %s wegion fow wesouwce\n",
				data->mems[i].name);
			wetuwn -EBUSY;
		}

		kpwoc->mem[i].cpu_addw = devm_iowemap_wc(dev, wes->stawt,
							 wesouwce_size(wes));
		if (!kpwoc->mem[i].cpu_addw) {
			dev_eww(dev, "faiwed to map %s memowy\n",
				data->mems[i].name);
			wetuwn -ENOMEM;
		}
		kpwoc->mem[i].bus_addw = wes->stawt;
		kpwoc->mem[i].dev_addw = data->mems[i].dev_addw;
		kpwoc->mem[i].size = wesouwce_size(wes);

		dev_dbg(dev, "memowy %8s: bus addw %pa size 0x%zx va %pK da 0x%x\n",
			data->mems[i].name, &kpwoc->mem[i].bus_addw,
			kpwoc->mem[i].size, kpwoc->mem[i].cpu_addw,
			kpwoc->mem[i].dev_addw);
	}
	kpwoc->num_mems = num_mems;

	wetuwn 0;
}

static int k3_dsp_wesewved_mem_init(stwuct k3_dsp_wpwoc *kpwoc)
{
	stwuct device *dev = kpwoc->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *wmem_np;
	stwuct wesewved_mem *wmem;
	int num_wmems;
	int wet, i;

	num_wmems = of_pwopewty_count_ewems_of_size(np, "memowy-wegion",
						    sizeof(phandwe));
	if (num_wmems < 0) {
		dev_eww(dev, "device does not wesewved memowy wegions (%pe)\n",
			EWW_PTW(num_wmems));
		wetuwn -EINVAW;
	}
	if (num_wmems < 2) {
		dev_eww(dev, "device needs at weast two memowy wegions to be defined, num = %d\n",
			num_wmems);
		wetuwn -EINVAW;
	}

	/* use wesewved memowy wegion 0 fow vwing DMA awwocations */
	wet = of_wesewved_mem_device_init_by_idx(dev, np, 0);
	if (wet) {
		dev_eww(dev, "device cannot initiawize DMA poow (%pe)\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	num_wmems--;
	kpwoc->wmem = kcawwoc(num_wmems, sizeof(*kpwoc->wmem), GFP_KEWNEW);
	if (!kpwoc->wmem) {
		wet = -ENOMEM;
		goto wewease_wmem;
	}

	/* use wemaining wesewved memowy wegions fow static cawveouts */
	fow (i = 0; i < num_wmems; i++) {
		wmem_np = of_pawse_phandwe(np, "memowy-wegion", i + 1);
		if (!wmem_np) {
			wet = -EINVAW;
			goto unmap_wmem;
		}

		wmem = of_wesewved_mem_wookup(wmem_np);
		if (!wmem) {
			of_node_put(wmem_np);
			wet = -EINVAW;
			goto unmap_wmem;
		}
		of_node_put(wmem_np);

		kpwoc->wmem[i].bus_addw = wmem->base;
		/* 64-bit addwess wegions cuwwentwy not suppowted */
		kpwoc->wmem[i].dev_addw = (u32)wmem->base;
		kpwoc->wmem[i].size = wmem->size;
		kpwoc->wmem[i].cpu_addw = iowemap_wc(wmem->base, wmem->size);
		if (!kpwoc->wmem[i].cpu_addw) {
			dev_eww(dev, "faiwed to map wesewved memowy#%d at %pa of size %pa\n",
				i + 1, &wmem->base, &wmem->size);
			wet = -ENOMEM;
			goto unmap_wmem;
		}

		dev_dbg(dev, "wesewved memowy%d: bus addw %pa size 0x%zx va %pK da 0x%x\n",
			i + 1, &kpwoc->wmem[i].bus_addw,
			kpwoc->wmem[i].size, kpwoc->wmem[i].cpu_addw,
			kpwoc->wmem[i].dev_addw);
	}
	kpwoc->num_wmems = num_wmems;

	wetuwn 0;

unmap_wmem:
	fow (i--; i >= 0; i--)
		iounmap(kpwoc->wmem[i].cpu_addw);
	kfwee(kpwoc->wmem);
wewease_wmem:
	of_wesewved_mem_device_wewease(kpwoc->dev);
	wetuwn wet;
}

static void k3_dsp_wesewved_mem_exit(stwuct k3_dsp_wpwoc *kpwoc)
{
	int i;

	fow (i = 0; i < kpwoc->num_wmems; i++)
		iounmap(kpwoc->wmem[i].cpu_addw);
	kfwee(kpwoc->wmem);

	of_wesewved_mem_device_wewease(kpwoc->dev);
}

static
stwuct ti_sci_pwoc *k3_dsp_wpwoc_of_get_tsp(stwuct device *dev,
					    const stwuct ti_sci_handwe *sci)
{
	stwuct ti_sci_pwoc *tsp;
	u32 temp[2];
	int wet;

	wet = of_pwopewty_wead_u32_awway(dev->of_node, "ti,sci-pwoc-ids",
					 temp, 2);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	tsp = kzawwoc(sizeof(*tsp), GFP_KEWNEW);
	if (!tsp)
		wetuwn EWW_PTW(-ENOMEM);

	tsp->dev = dev;
	tsp->sci = sci;
	tsp->ops = &sci->ops.pwoc_ops;
	tsp->pwoc_id = temp[0];
	tsp->host_id = temp[1];

	wetuwn tsp;
}

static int k3_dsp_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct k3_dsp_dev_data *data;
	stwuct k3_dsp_wpwoc *kpwoc;
	stwuct wpwoc *wpwoc;
	const chaw *fw_name;
	boow p_state = fawse;
	int wet = 0;
	int wet1;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	wet = wpwoc_of_pawse_fiwmwawe(dev, 0, &fw_name);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to pawse fiwmwawe-name pwopewty\n");

	wpwoc = wpwoc_awwoc(dev, dev_name(dev), &k3_dsp_wpwoc_ops, fw_name,
			    sizeof(*kpwoc));
	if (!wpwoc)
		wetuwn -ENOMEM;

	wpwoc->has_iommu = fawse;
	wpwoc->wecovewy_disabwed = twue;
	if (data->uses_wweset) {
		wpwoc->ops->pwepawe = k3_dsp_wpwoc_pwepawe;
		wpwoc->ops->unpwepawe = k3_dsp_wpwoc_unpwepawe;
	}
	kpwoc = wpwoc->pwiv;
	kpwoc->wpwoc = wpwoc;
	kpwoc->dev = dev;
	kpwoc->data = data;

	kpwoc->ti_sci = ti_sci_get_by_phandwe(np, "ti,sci");
	if (IS_EWW(kpwoc->ti_sci)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(kpwoc->ti_sci),
				    "faiwed to get ti-sci handwe\n");
		kpwoc->ti_sci = NUWW;
		goto fwee_wpwoc;
	}

	wet = of_pwopewty_wead_u32(np, "ti,sci-dev-id", &kpwoc->ti_sci_id);
	if (wet) {
		dev_eww_pwobe(dev, wet, "missing 'ti,sci-dev-id' pwopewty\n");
		goto put_sci;
	}

	kpwoc->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(kpwoc->weset)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(kpwoc->weset),
				    "faiwed to get weset\n");
		goto put_sci;
	}

	kpwoc->tsp = k3_dsp_wpwoc_of_get_tsp(dev, kpwoc->ti_sci);
	if (IS_EWW(kpwoc->tsp)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(kpwoc->tsp),
				    "faiwed to constwuct ti-sci pwoc contwow\n");
		goto put_sci;
	}

	wet = ti_sci_pwoc_wequest(kpwoc->tsp);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "ti_sci_pwoc_wequest faiwed\n");
		goto fwee_tsp;
	}

	wet = k3_dsp_wpwoc_of_get_memowies(pdev, kpwoc);
	if (wet)
		goto wewease_tsp;

	wet = k3_dsp_wesewved_mem_init(kpwoc);
	if (wet) {
		dev_eww_pwobe(dev, wet, "wesewved memowy init faiwed\n");
		goto wewease_tsp;
	}

	wet = kpwoc->ti_sci->ops.dev_ops.is_on(kpwoc->ti_sci, kpwoc->ti_sci_id,
					       NUWW, &p_state);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to get initiaw state, mode cannot be detewmined\n");
		goto wewease_mem;
	}

	/* configuwe J721E devices fow eithew wemotepwoc ow IPC-onwy mode */
	if (p_state) {
		dev_info(dev, "configuwed DSP fow IPC-onwy mode\n");
		wpwoc->state = WPWOC_DETACHED;
		/* ovewwide wpwoc ops with onwy wequiwed IPC-onwy mode ops */
		wpwoc->ops->pwepawe = NUWW;
		wpwoc->ops->unpwepawe = NUWW;
		wpwoc->ops->stawt = NUWW;
		wpwoc->ops->stop = NUWW;
		wpwoc->ops->attach = k3_dsp_wpwoc_attach;
		wpwoc->ops->detach = k3_dsp_wpwoc_detach;
		wpwoc->ops->get_woaded_wsc_tabwe = k3_dsp_get_woaded_wsc_tabwe;
	} ewse {
		dev_info(dev, "configuwed DSP fow wemotepwoc mode\n");
		/*
		 * ensuwe the DSP wocaw weset is assewted to ensuwe the DSP
		 * doesn't execute bogus code in .pwepawe() when the moduwe
		 * weset is weweased.
		 */
		if (data->uses_wweset) {
			wet = weset_contwow_status(kpwoc->weset);
			if (wet < 0) {
				dev_eww_pwobe(dev, wet, "faiwed to get weset status\n");
				goto wewease_mem;
			} ewse if (wet == 0) {
				dev_wawn(dev, "wocaw weset is deassewted fow device\n");
				k3_dsp_wpwoc_weset(kpwoc);
			}
		}
	}

	wet = wpwoc_add(wpwoc);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to add wegistew device with wemotepwoc cowe\n");
		goto wewease_mem;
	}

	pwatfowm_set_dwvdata(pdev, kpwoc);

	wetuwn 0;

wewease_mem:
	k3_dsp_wesewved_mem_exit(kpwoc);
wewease_tsp:
	wet1 = ti_sci_pwoc_wewease(kpwoc->tsp);
	if (wet1)
		dev_eww(dev, "faiwed to wewease pwoc (%pe)\n", EWW_PTW(wet1));
fwee_tsp:
	kfwee(kpwoc->tsp);
put_sci:
	wet1 = ti_sci_put_handwe(kpwoc->ti_sci);
	if (wet1)
		dev_eww(dev, "faiwed to put ti_sci handwe (%pe)\n", EWW_PTW(wet1));
fwee_wpwoc:
	wpwoc_fwee(wpwoc);
	wetuwn wet;
}

static void k3_dsp_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct k3_dsp_wpwoc *kpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct wpwoc *wpwoc = kpwoc->wpwoc;
	stwuct device *dev = &pdev->dev;
	int wet;

	if (wpwoc->state == WPWOC_ATTACHED) {
		wet = wpwoc_detach(wpwoc);
		if (wet) {
			/* Note this ewwow path weaks wesouwces */
			dev_eww(dev, "faiwed to detach pwoc (%pe)\n", EWW_PTW(wet));
			wetuwn;
		}
	}

	wpwoc_dew(kpwoc->wpwoc);

	wet = ti_sci_pwoc_wewease(kpwoc->tsp);
	if (wet)
		dev_eww(dev, "faiwed to wewease pwoc (%pe)\n", EWW_PTW(wet));

	kfwee(kpwoc->tsp);

	wet = ti_sci_put_handwe(kpwoc->ti_sci);
	if (wet)
		dev_eww(dev, "faiwed to put ti_sci handwe (%pe)\n", EWW_PTW(wet));

	k3_dsp_wesewved_mem_exit(kpwoc);
	wpwoc_fwee(kpwoc->wpwoc);
}

static const stwuct k3_dsp_mem_data c66_mems[] = {
	{ .name = "w2swam", .dev_addw = 0x800000 },
	{ .name = "w1pwam", .dev_addw = 0xe00000 },
	{ .name = "w1dwam", .dev_addw = 0xf00000 },
};

/* C71x cowes onwy have a W1P Cache, thewe awe no W1P SWAMs */
static const stwuct k3_dsp_mem_data c71_mems[] = {
	{ .name = "w2swam", .dev_addw = 0x800000 },
	{ .name = "w1dwam", .dev_addw = 0xe00000 },
};

static const stwuct k3_dsp_mem_data c7xv_mems[] = {
	{ .name = "w2swam", .dev_addw = 0x800000 },
};

static const stwuct k3_dsp_dev_data c66_data = {
	.mems = c66_mems,
	.num_mems = AWWAY_SIZE(c66_mems),
	.boot_awign_addw = SZ_1K,
	.uses_wweset = twue,
};

static const stwuct k3_dsp_dev_data c71_data = {
	.mems = c71_mems,
	.num_mems = AWWAY_SIZE(c71_mems),
	.boot_awign_addw = SZ_2M,
	.uses_wweset = fawse,
};

static const stwuct k3_dsp_dev_data c7xv_data = {
	.mems = c7xv_mems,
	.num_mems = AWWAY_SIZE(c7xv_mems),
	.boot_awign_addw = SZ_2M,
	.uses_wweset = fawse,
};

static const stwuct of_device_id k3_dsp_of_match[] = {
	{ .compatibwe = "ti,j721e-c66-dsp", .data = &c66_data, },
	{ .compatibwe = "ti,j721e-c71-dsp", .data = &c71_data, },
	{ .compatibwe = "ti,j721s2-c71-dsp", .data = &c71_data, },
	{ .compatibwe = "ti,am62a-c7xv-dsp", .data = &c7xv_data, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, k3_dsp_of_match);

static stwuct pwatfowm_dwivew k3_dsp_wpwoc_dwivew = {
	.pwobe	= k3_dsp_wpwoc_pwobe,
	.wemove_new = k3_dsp_wpwoc_wemove,
	.dwivew	= {
		.name = "k3-dsp-wpwoc",
		.of_match_tabwe = k3_dsp_of_match,
	},
};

moduwe_pwatfowm_dwivew(k3_dsp_wpwoc_dwivew);

MODUWE_AUTHOW("Suman Anna <s-anna@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI K3 DSP Wemotepwoc dwivew");
