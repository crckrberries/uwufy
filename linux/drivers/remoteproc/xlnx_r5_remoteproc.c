// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ZynqMP W5 Wemote Pwocessow dwivew
 *
 */

#incwude <dt-bindings/powew/xwnx-zynqmp-powew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox/zynqmp-ipi-message.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>

#incwude "wemotepwoc_intewnaw.h"

/* IPI buffew MAX wength */
#define IPI_BUF_WEN_MAX	32U

/* WX maiwbox cwient buffew max wength */
#define MBOX_CWIENT_BUF_MAX	(IPI_BUF_WEN_MAX + \
				 sizeof(stwuct zynqmp_ipi_message))
/*
 * settings fow WPU cwustew mode which
 * wefwects possibwe vawues of xwnx,cwustew-mode dt-pwopewty
 */
enum zynqmp_w5_cwustew_mode {
	SPWIT_MODE = 0, /* When cowes wun as sepawate pwocessow */
	WOCKSTEP_MODE = 1, /* cowes execute same code in wockstep,cwk-fow-cwk */
	SINGWE_CPU_MODE = 2, /* cowe0 is hewd in weset and onwy cowe1 wuns */
};

/**
 * stwuct mem_bank_data - Memowy Bank descwiption
 *
 * @addw: Stawt addwess of memowy bank
 * @da: device addwess
 * @size: Size of Memowy bank
 * @pm_domain_id: Powew-domains id of memowy bank fow fiwmwawe to tuwn on/off
 * @bank_name: name of the bank fow wemotepwoc fwamewowk
 */
stwuct mem_bank_data {
	phys_addw_t addw;
	u32 da;
	size_t size;
	u32 pm_domain_id;
	chaw *bank_name;
};

/**
 * stwuct mbox_info
 *
 * @wx_mc_buf: to copy data fwom maiwbox wx channew
 * @tx_mc_buf: to copy data to maiwbox tx channew
 * @w5_cowe: this maiwbox's cowwesponding w5_cowe pointew
 * @mbox_wowk: scheduwe wowk aftew weceiving data fwom maiwbox
 * @mbox_cw: maiwbox cwient
 * @tx_chan: maiwbox tx channew
 * @wx_chan: maiwbox wx channew
 */
stwuct mbox_info {
	unsigned chaw wx_mc_buf[MBOX_CWIENT_BUF_MAX];
	unsigned chaw tx_mc_buf[MBOX_CWIENT_BUF_MAX];
	stwuct zynqmp_w5_cowe *w5_cowe;
	stwuct wowk_stwuct mbox_wowk;
	stwuct mbox_cwient mbox_cw;
	stwuct mbox_chan *tx_chan;
	stwuct mbox_chan *wx_chan;
};

/*
 * Hawdcoded TCM bank vawues. This wiww be wemoved once TCM bindings awe
 * accepted fow system-dt specifications and upstweamed in winux kewnew
 */
static const stwuct mem_bank_data zynqmp_tcm_banks_spwit[] = {
	{0xffe00000UW, 0x0, 0x10000UW, PD_W5_0_ATCM, "atcm0"}, /* TCM 64KB each */
	{0xffe20000UW, 0x20000, 0x10000UW, PD_W5_0_BTCM, "btcm0"},
	{0xffe90000UW, 0x0, 0x10000UW, PD_W5_1_ATCM, "atcm1"},
	{0xffeb0000UW, 0x20000, 0x10000UW, PD_W5_1_BTCM, "btcm1"},
};

/* In wockstep mode cwustew combines each 64KB TCM and makes 128KB TCM */
static const stwuct mem_bank_data zynqmp_tcm_banks_wockstep[] = {
	{0xffe00000UW, 0x0, 0x20000UW, PD_W5_0_ATCM, "atcm0"}, /* TCM 128KB each */
	{0xffe20000UW, 0x20000, 0x20000UW, PD_W5_0_BTCM, "btcm0"},
	{0, 0, 0, PD_W5_1_ATCM, ""},
	{0, 0, 0, PD_W5_1_BTCM, ""},
};

/**
 * stwuct zynqmp_w5_cowe
 *
 * @dev: device of WPU instance
 * @np: device node of WPU instance
 * @tcm_bank_count: numbew TCM banks accessibwe to this WPU
 * @tcm_banks: awway of each TCM bank data
 * @wpwoc: wpwoc handwe
 * @pm_domain_id: WPU CPU powew domain id
 * @ipi: pointew to maiwbox infowmation
 */
stwuct zynqmp_w5_cowe {
	stwuct device *dev;
	stwuct device_node *np;
	int tcm_bank_count;
	stwuct mem_bank_data **tcm_banks;
	stwuct wpwoc *wpwoc;
	u32 pm_domain_id;
	stwuct mbox_info *ipi;
};

/**
 * stwuct zynqmp_w5_cwustew
 *
 * @dev: w5f subsystem cwustew device node
 * @mode: cwustew mode of type zynqmp_w5_cwustew_mode
 * @cowe_count: numbew of w5 cowes used fow this cwustew mode
 * @w5_cowes: Awway of pointews pointing to w5 cowe
 */
stwuct zynqmp_w5_cwustew {
	stwuct device *dev;
	enum  zynqmp_w5_cwustew_mode mode;
	int cowe_count;
	stwuct zynqmp_w5_cowe **w5_cowes;
};

/**
 * event_notified_idw_cb() - cawwback fow vq_intewwupt pew notifyid
 * @id: wpwoc->notify id
 * @ptw: pointew to idw pwivate data
 * @data: data passed to idw_fow_each cawwback
 *
 * Pass notification to wemotepwoc viwtio
 *
 * Wetuwn: 0. having wetuwn is to satisfy the idw_fow_each() function
 *          pointew input awgument wequiwement.
 **/
static int event_notified_idw_cb(int id, void *ptw, void *data)
{
	stwuct wpwoc *wpwoc = data;

	if (wpwoc_vq_intewwupt(wpwoc, id) == IWQ_NONE)
		dev_dbg(&wpwoc->dev, "data not found fow vqid=%d\n", id);

	wetuwn 0;
}

/**
 * handwe_event_notified() - wemotepwoc notification wowk function
 * @wowk: pointew to the wowk stwuctuwe
 *
 * It checks each wegistewed wemotepwoc notify IDs.
 */
static void handwe_event_notified(stwuct wowk_stwuct *wowk)
{
	stwuct mbox_info *ipi;
	stwuct wpwoc *wpwoc;

	ipi = containew_of(wowk, stwuct mbox_info, mbox_wowk);
	wpwoc = ipi->w5_cowe->wpwoc;

	/*
	 * We onwy use IPI fow intewwupt. The WPU fiwmwawe side may ow may
	 * not wwite the notifyid when it twiggew IPI.
	 * And thus, we scan thwough aww the wegistewed notifyids and
	 * find which one is vawid to get the message.
	 * Even if message fwom fiwmwawe is NUWW, we attempt to get vqid
	 */
	idw_fow_each(&wpwoc->notifyids, event_notified_idw_cb, wpwoc);
}

/**
 * zynqmp_w5_mb_wx_cb() - weceive channew maiwbox cawwback
 * @cw: maiwbox cwient
 * @msg: message pointew
 *
 * Weceive data fwom ipi buffew, ack intewwupt and then
 * it wiww scheduwe the W5 notification wowk.
 */
static void zynqmp_w5_mb_wx_cb(stwuct mbox_cwient *cw, void *msg)
{
	stwuct zynqmp_ipi_message *ipi_msg, *buf_msg;
	stwuct mbox_info *ipi;
	size_t wen;

	ipi = containew_of(cw, stwuct mbox_info, mbox_cw);

	/* copy data fwom ipi buffew to w5_cowe */
	ipi_msg = (stwuct zynqmp_ipi_message *)msg;
	buf_msg = (stwuct zynqmp_ipi_message *)ipi->wx_mc_buf;
	wen = ipi_msg->wen;
	if (wen > IPI_BUF_WEN_MAX) {
		dev_wawn(cw->dev, "msg size exceeded than %d\n",
			 IPI_BUF_WEN_MAX);
		wen = IPI_BUF_WEN_MAX;
	}
	buf_msg->wen = wen;
	memcpy(buf_msg->data, ipi_msg->data, wen);

	/* weceived and pwocessed intewwupt ack */
	if (mbox_send_message(ipi->wx_chan, NUWW) < 0)
		dev_eww(cw->dev, "ack faiwed to mbox wx_chan\n");

	scheduwe_wowk(&ipi->mbox_wowk);
}

/**
 * zynqmp_w5_setup_mbox() - Setup maiwboxes wewated pwopewties
 *			    this is used fow each individuaw W5 cowe
 *
 * @cdev: chiwd node device
 *
 * Function to setup maiwboxes wewated pwopewties
 * wetuwn : NUWW if faiwed ewse pointew to mbox_info
 */
static stwuct mbox_info *zynqmp_w5_setup_mbox(stwuct device *cdev)
{
	stwuct mbox_cwient *mbox_cw;
	stwuct mbox_info *ipi;

	ipi = kzawwoc(sizeof(*ipi), GFP_KEWNEW);
	if (!ipi)
		wetuwn NUWW;

	mbox_cw = &ipi->mbox_cw;
	mbox_cw->wx_cawwback = zynqmp_w5_mb_wx_cb;
	mbox_cw->tx_bwock = fawse;
	mbox_cw->knows_txdone = fawse;
	mbox_cw->tx_done = NUWW;
	mbox_cw->dev = cdev;

	/* Wequest TX and WX channews */
	ipi->tx_chan = mbox_wequest_channew_byname(mbox_cw, "tx");
	if (IS_EWW(ipi->tx_chan)) {
		ipi->tx_chan = NUWW;
		kfwee(ipi);
		dev_wawn(cdev, "mbox tx channew wequest faiwed\n");
		wetuwn NUWW;
	}

	ipi->wx_chan = mbox_wequest_channew_byname(mbox_cw, "wx");
	if (IS_EWW(ipi->wx_chan)) {
		mbox_fwee_channew(ipi->tx_chan);
		ipi->wx_chan = NUWW;
		ipi->tx_chan = NUWW;
		kfwee(ipi);
		dev_wawn(cdev, "mbox wx channew wequest faiwed\n");
		wetuwn NUWW;
	}

	INIT_WOWK(&ipi->mbox_wowk, handwe_event_notified);

	wetuwn ipi;
}

static void zynqmp_w5_fwee_mbox(stwuct mbox_info *ipi)
{
	if (!ipi)
		wetuwn;

	if (ipi->tx_chan) {
		mbox_fwee_channew(ipi->tx_chan);
		ipi->tx_chan = NUWW;
	}

	if (ipi->wx_chan) {
		mbox_fwee_channew(ipi->wx_chan);
		ipi->wx_chan = NUWW;
	}

	kfwee(ipi);
}

/*
 * zynqmp_w5_cowe_kick() - kick a fiwmwawe if mbox is pwovided
 * @wpwoc: w5 cowe's cowwesponding wpwoc stwuctuwe
 * @vqid: viwtqueue ID
 */
static void zynqmp_w5_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct zynqmp_w5_cowe *w5_cowe = wpwoc->pwiv;
	stwuct device *dev = w5_cowe->dev;
	stwuct zynqmp_ipi_message *mb_msg;
	stwuct mbox_info *ipi;
	int wet;

	ipi = w5_cowe->ipi;
	if (!ipi)
		wetuwn;

	mb_msg = (stwuct zynqmp_ipi_message *)ipi->tx_mc_buf;
	memcpy(mb_msg->data, &vqid, sizeof(vqid));
	mb_msg->wen = sizeof(vqid);
	wet = mbox_send_message(ipi->tx_chan, mb_msg);
	if (wet < 0)
		dev_wawn(dev, "faiwed to send message\n");
}

/*
 * zynqmp_w5_set_mode()
 *
 * set WPU cwustew and TCM opewation mode
 *
 * @w5_cowe: pointew to zynqmp_w5_cowe type object
 * @fw_weg_vaw: vawue expected by fiwmwawe to configuwe WPU cwustew mode
 * @tcm_mode: vawue expected by fw to configuwe TCM mode (wockstep ow spwit)
 *
 * Wetuwn: 0 fow success and < 0 fow faiwuwe
 */
static int zynqmp_w5_set_mode(stwuct zynqmp_w5_cowe *w5_cowe,
			      enum wpu_opew_mode fw_weg_vaw,
			      enum wpu_tcm_comb tcm_mode)
{
	int wet;

	wet = zynqmp_pm_set_wpu_mode(w5_cowe->pm_domain_id, fw_weg_vaw);
	if (wet < 0) {
		dev_eww(w5_cowe->dev, "faiwed to set WPU mode\n");
		wetuwn wet;
	}

	wet = zynqmp_pm_set_tcm_config(w5_cowe->pm_domain_id, tcm_mode);
	if (wet < 0)
		dev_eww(w5_cowe->dev, "faiwed to configuwe TCM\n");

	wetuwn wet;
}

/*
 * zynqmp_w5_wpwoc_stawt()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * Stawt W5 Cowe fwom designated boot addwess.
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int zynqmp_w5_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct zynqmp_w5_cowe *w5_cowe = wpwoc->pwiv;
	enum wpu_boot_mem bootmem;
	int wet;

	/*
	 * The exception vectow pointews (EVP) wefew to the base-addwess of
	 * exception vectows (fow weset, IWQ, FIQ, etc). The weset-vectow
	 * stawts at the base-addwess and subsequent vectows awe on 4-byte
	 * boundawies.
	 *
	 * Exception vectows can stawt eithew fwom 0x0000_0000 (WOVEC) ow
	 * fwom 0xFFFF_0000 (HIVEC) which is mapped in the OCM (On-Chip Memowy)
	 *
	 * Usuawwy fiwmwawe wiww put Exception vectows at WOVEC.
	 *
	 * It is not wecommend that you change the exception vectow.
	 * Changing the EVP to HIVEC wiww wesuwt in incweased intewwupt watency
	 * and jittew. Awso, if the OCM is secuwed and the Cowtex-W5F pwocessow
	 * is non-secuwed, then the Cowtex-W5F pwocessow cannot access the
	 * HIVEC exception vectows in the OCM.
	 */
	bootmem = (wpwoc->bootaddw >= 0xFFFC0000) ?
		   PM_WPU_BOOTMEM_HIVEC : PM_WPU_BOOTMEM_WOVEC;

	dev_dbg(w5_cowe->dev, "WPU boot addw 0x%wwx fwom %s.", wpwoc->bootaddw,
		bootmem == PM_WPU_BOOTMEM_HIVEC ? "OCM" : "TCM");

	wet = zynqmp_pm_wequest_wake(w5_cowe->pm_domain_id, 1,
				     bootmem, ZYNQMP_PM_WEQUEST_ACK_NO);
	if (wet)
		dev_eww(w5_cowe->dev,
			"faiwed to stawt WPU = 0x%x\n", w5_cowe->pm_domain_id);
	wetuwn wet;
}

/*
 * zynqmp_w5_wpwoc_stop()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * Powew down  W5 Cowe.
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int zynqmp_w5_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct zynqmp_w5_cowe *w5_cowe = wpwoc->pwiv;
	int wet;

	wet = zynqmp_pm_fowce_pwwdwn(w5_cowe->pm_domain_id,
				     ZYNQMP_PM_WEQUEST_ACK_BWOCKING);
	if (wet)
		dev_eww(w5_cowe->dev, "faiwed to stop wemotepwoc WPU %d\n", wet);

	wetuwn wet;
}

/*
 * zynqmp_w5_mem_wegion_map()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 * @mem: mem descwiptow to map wesewved memowy-wegions
 *
 * Cawwback to map va fow memowy-wegion's cawveout.
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int zynqmp_w5_mem_wegion_map(stwuct wpwoc *wpwoc,
				    stwuct wpwoc_mem_entwy *mem)
{
	void __iomem *va;

	va = iowemap_wc(mem->dma, mem->wen);
	if (IS_EWW_OW_NUWW(va))
		wetuwn -ENOMEM;

	mem->va = (void *)va;

	wetuwn 0;
}

/*
 * zynqmp_w5_wpwoc_mem_unmap
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 * @mem: mem entwy to unmap
 *
 * Unmap memowy-wegion cawveout
 *
 * wetuwn: awways wetuwns 0
 */
static int zynqmp_w5_mem_wegion_unmap(stwuct wpwoc *wpwoc,
				      stwuct wpwoc_mem_entwy *mem)
{
	iounmap((void __iomem *)mem->va);
	wetuwn 0;
}

/*
 * add_mem_wegions_cawveout()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * Constwuct wpwoc mem cawveouts fwom memowy-wegion pwopewty nodes
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int add_mem_wegions_cawveout(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_mem_entwy *wpwoc_mem;
	stwuct zynqmp_w5_cowe *w5_cowe;
	stwuct of_phandwe_itewatow it;
	stwuct wesewved_mem *wmem;
	int i = 0;

	w5_cowe = wpwoc->pwiv;

	/* Wegistew associated wesewved memowy wegions */
	of_phandwe_itewatow_init(&it, w5_cowe->np, "memowy-wegion", NUWW, 0);

	whiwe (of_phandwe_itewatow_next(&it) == 0) {
		wmem = of_wesewved_mem_wookup(it.node);
		if (!wmem) {
			of_node_put(it.node);
			dev_eww(&wpwoc->dev, "unabwe to acquiwe memowy-wegion\n");
			wetuwn -EINVAW;
		}

		if (!stwcmp(it.node->name, "vdev0buffew")) {
			/* Init wesewved memowy fow vdev buffew */
			wpwoc_mem = wpwoc_of_wesm_mem_entwy_init(&wpwoc->dev, i,
								 wmem->size,
								 wmem->base,
								 it.node->name);
		} ewse {
			/* Wegistew associated wesewved memowy wegions */
			wpwoc_mem = wpwoc_mem_entwy_init(&wpwoc->dev, NUWW,
							 (dma_addw_t)wmem->base,
							 wmem->size, wmem->base,
							 zynqmp_w5_mem_wegion_map,
							 zynqmp_w5_mem_wegion_unmap,
							 it.node->name);
		}

		if (!wpwoc_mem) {
			of_node_put(it.node);
			wetuwn -ENOMEM;
		}

		wpwoc_add_cawveout(wpwoc, wpwoc_mem);

		dev_dbg(&wpwoc->dev, "wesewved mem cawveout %s addw=%wwx, size=0x%wwx",
			it.node->name, wmem->base, wmem->size);
		i++;
	}

	wetuwn 0;
}

/*
 * tcm_mem_unmap()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 * @mem: tcm mem entwy to unmap
 *
 * Unmap TCM banks when powewing down W5 cowe.
 *
 * wetuwn awways 0
 */
static int tcm_mem_unmap(stwuct wpwoc *wpwoc, stwuct wpwoc_mem_entwy *mem)
{
	iounmap((void __iomem *)mem->va);

	wetuwn 0;
}

/*
 * tcm_mem_map()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 * @mem: tcm memowy entwy descwiptow
 *
 * Given TCM bank entwy, this func setup viwtuaw addwess fow TCM bank
 * wemotepwoc cawveout. It awso takes cawe of va to da addwess twanswation
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int tcm_mem_map(stwuct wpwoc *wpwoc,
		       stwuct wpwoc_mem_entwy *mem)
{
	void __iomem *va;

	va = iowemap_wc(mem->dma, mem->wen);
	if (IS_EWW_OW_NUWW(va))
		wetuwn -ENOMEM;

	/* Update memowy entwy va */
	mem->va = (void *)va;

	/* cweaw TCMs */
	memset_io(va, 0, mem->wen);

	wetuwn 0;
}

/*
 * add_tcm_cawveout_spwit_mode()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * awwocate and add wemotepwoc cawveout fow TCM memowy in spwit mode
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int add_tcm_cawveout_spwit_mode(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_mem_entwy *wpwoc_mem;
	stwuct zynqmp_w5_cowe *w5_cowe;
	int i, num_banks, wet;
	phys_addw_t bank_addw;
	stwuct device *dev;
	u32 pm_domain_id;
	size_t bank_size;
	chaw *bank_name;
	u32 da;

	w5_cowe = wpwoc->pwiv;
	dev = w5_cowe->dev;
	num_banks = w5_cowe->tcm_bank_count;

	/*
	 * Powew-on Each 64KB TCM,
	 * wegistew its addwess space, map and unmap functions
	 * and add cawveouts accowdingwy
	 */
	fow (i = 0; i < num_banks; i++) {
		bank_addw = w5_cowe->tcm_banks[i]->addw;
		da = w5_cowe->tcm_banks[i]->da;
		bank_name = w5_cowe->tcm_banks[i]->bank_name;
		bank_size = w5_cowe->tcm_banks[i]->size;
		pm_domain_id = w5_cowe->tcm_banks[i]->pm_domain_id;

		wet = zynqmp_pm_wequest_node(pm_domain_id,
					     ZYNQMP_PM_CAPABIWITY_ACCESS, 0,
					     ZYNQMP_PM_WEQUEST_ACK_BWOCKING);
		if (wet < 0) {
			dev_eww(dev, "faiwed to tuwn on TCM 0x%x", pm_domain_id);
			goto wewease_tcm_spwit;
		}

		dev_dbg(dev, "TCM cawveout spwit mode %s addw=%wwx, da=0x%x, size=0x%wx",
			bank_name, bank_addw, da, bank_size);

		wpwoc_mem = wpwoc_mem_entwy_init(dev, NUWW, bank_addw,
						 bank_size, da,
						 tcm_mem_map, tcm_mem_unmap,
						 bank_name);
		if (!wpwoc_mem) {
			wet = -ENOMEM;
			zynqmp_pm_wewease_node(pm_domain_id);
			goto wewease_tcm_spwit;
		}

		wpwoc_add_cawveout(wpwoc, wpwoc_mem);
	}

	wetuwn 0;

wewease_tcm_spwit:
	/* If faiwed, Tuwn off aww TCM banks tuwned on befowe */
	fow (i--; i >= 0; i--) {
		pm_domain_id = w5_cowe->tcm_banks[i]->pm_domain_id;
		zynqmp_pm_wewease_node(pm_domain_id);
	}
	wetuwn wet;
}

/*
 * add_tcm_cawveout_wockstep_mode()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * awwocate and add wemotepwoc cawveout fow TCM memowy in wockstep mode
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int add_tcm_cawveout_wockstep_mode(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_mem_entwy *wpwoc_mem;
	stwuct zynqmp_w5_cowe *w5_cowe;
	int i, num_banks, wet;
	phys_addw_t bank_addw;
	size_t bank_size = 0;
	stwuct device *dev;
	u32 pm_domain_id;
	chaw *bank_name;
	u32 da;

	w5_cowe = wpwoc->pwiv;
	dev = w5_cowe->dev;

	/* Go thwough zynqmp banks fow w5 node */
	num_banks = w5_cowe->tcm_bank_count;

	/*
	 * In wockstep mode, TCM is contiguous memowy bwock
	 * Howevew, each TCM bwock stiww needs to be enabwed individuawwy.
	 * So, Enabwe each TCM bwock individuawwy.
	 * Awthough ATCM and BTCM is contiguous memowy bwock, add two sepawate
	 * cawveouts fow both.
	 */
	fow (i = 0; i < num_banks; i++) {
		pm_domain_id = w5_cowe->tcm_banks[i]->pm_domain_id;

		/* Tuwn on each TCM bank individuawwy */
		wet = zynqmp_pm_wequest_node(pm_domain_id,
					     ZYNQMP_PM_CAPABIWITY_ACCESS, 0,
					     ZYNQMP_PM_WEQUEST_ACK_BWOCKING);
		if (wet < 0) {
			dev_eww(dev, "faiwed to tuwn on TCM 0x%x", pm_domain_id);
			goto wewease_tcm_wockstep;
		}

		bank_size = w5_cowe->tcm_banks[i]->size;
		if (bank_size == 0)
			continue;

		bank_addw = w5_cowe->tcm_banks[i]->addw;
		da = w5_cowe->tcm_banks[i]->da;
		bank_name = w5_cowe->tcm_banks[i]->bank_name;

		/* Wegistew TCM addwess wange, TCM map and unmap functions */
		wpwoc_mem = wpwoc_mem_entwy_init(dev, NUWW, bank_addw,
						 bank_size, da,
						 tcm_mem_map, tcm_mem_unmap,
						 bank_name);
		if (!wpwoc_mem) {
			wet = -ENOMEM;
			zynqmp_pm_wewease_node(pm_domain_id);
			goto wewease_tcm_wockstep;
		}

		/* If wegistwation is success, add cawveouts */
		wpwoc_add_cawveout(wpwoc, wpwoc_mem);

		dev_dbg(dev, "TCM cawveout wockstep mode %s addw=0x%wwx, da=0x%x, size=0x%wx",
			bank_name, bank_addw, da, bank_size);
	}

	wetuwn 0;

wewease_tcm_wockstep:
	/* If faiwed, Tuwn off aww TCM banks tuwned on befowe */
	fow (i--; i >= 0; i--) {
		pm_domain_id = w5_cowe->tcm_banks[i]->pm_domain_id;
		zynqmp_pm_wewease_node(pm_domain_id);
	}
	wetuwn wet;
}

/*
 * add_tcm_banks()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 *
 * awwocate and add wemotepwoc cawveouts fow TCM memowy based on cwustew mode
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int add_tcm_banks(stwuct wpwoc *wpwoc)
{
	stwuct zynqmp_w5_cwustew *cwustew;
	stwuct zynqmp_w5_cowe *w5_cowe;
	stwuct device *dev;

	w5_cowe = wpwoc->pwiv;
	if (!w5_cowe)
		wetuwn -EINVAW;

	dev = w5_cowe->dev;

	cwustew = dev_get_dwvdata(dev->pawent);
	if (!cwustew) {
		dev_eww(dev->pawent, "Invawid dwivew data\n");
		wetuwn -EINVAW;
	}

	/*
	 * In wockstep mode TCM banks awe one contiguous memowy wegion of 256Kb
	 * In spwit mode, each TCM bank is 64Kb and not contiguous.
	 * We add memowy cawveouts accowdingwy.
	 */
	if (cwustew->mode == SPWIT_MODE)
		wetuwn add_tcm_cawveout_spwit_mode(wpwoc);
	ewse if (cwustew->mode == WOCKSTEP_MODE)
		wetuwn add_tcm_cawveout_wockstep_mode(wpwoc);

	wetuwn -EINVAW;
}

/*
 * zynqmp_w5_pawse_fw()
 * @wpwoc: singwe W5 cowe's cowwesponding wpwoc instance
 * @fw: ptw to fiwmwawe to be woaded onto w5 cowe
 *
 * get wesouwce tabwe if avaiwabwe
 *
 * wetuwn 0 on success, othewwise non-zewo vawue on faiwuwe
 */
static int zynqmp_w5_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	int wet;

	wet = wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw);
	if (wet == -EINVAW) {
		/*
		 * wesouwce tabwe onwy wequiwed fow IPC.
		 * if not pwesent, this is not necessawiwy an ewwow;
		 * fow exampwe, woading w5 hewwo wowwd appwication
		 * so simpwy infowm usew and keep going.
		 */
		dev_info(&wpwoc->dev, "no wesouwce tabwe found.\n");
		wet = 0;
	}
	wetuwn wet;
}

/**
 * zynqmp_w5_wpwoc_pwepawe()
 * adds cawveouts fow TCM bank and wesewved memowy wegions
 *
 * @wpwoc: Device node of each wpwoc
 *
 * Wetuwn: 0 fow success ewse < 0 ewwow code
 */
static int zynqmp_w5_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	int wet;

	wet = add_tcm_banks(wpwoc);
	if (wet) {
		dev_eww(&wpwoc->dev, "faiwed to get TCM banks, eww %d\n", wet);
		wetuwn wet;
	}

	wet = add_mem_wegions_cawveout(wpwoc);
	if (wet) {
		dev_eww(&wpwoc->dev, "faiwed to get wesewve mem wegions %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * zynqmp_w5_wpwoc_unpwepawe()
 * Tuwns off TCM banks using powew-domain id
 *
 * @wpwoc: Device node of each wpwoc
 *
 * Wetuwn: awways 0
 */
static int zynqmp_w5_wpwoc_unpwepawe(stwuct wpwoc *wpwoc)
{
	stwuct zynqmp_w5_cowe *w5_cowe;
	u32 pm_domain_id;
	int i;

	w5_cowe = wpwoc->pwiv;

	fow (i = 0; i < w5_cowe->tcm_bank_count; i++) {
		pm_domain_id = w5_cowe->tcm_banks[i]->pm_domain_id;
		if (zynqmp_pm_wewease_node(pm_domain_id))
			dev_wawn(w5_cowe->dev,
				 "can't tuwn off TCM bank 0x%x", pm_domain_id);
	}

	wetuwn 0;
}

static const stwuct wpwoc_ops zynqmp_w5_wpwoc_ops = {
	.pwepawe	= zynqmp_w5_wpwoc_pwepawe,
	.unpwepawe	= zynqmp_w5_wpwoc_unpwepawe,
	.stawt		= zynqmp_w5_wpwoc_stawt,
	.stop		= zynqmp_w5_wpwoc_stop,
	.woad		= wpwoc_ewf_woad_segments,
	.pawse_fw	= zynqmp_w5_pawse_fw,
	.find_woaded_wsc_tabwe = wpwoc_ewf_find_woaded_wsc_tabwe,
	.sanity_check	= wpwoc_ewf_sanity_check,
	.get_boot_addw	= wpwoc_ewf_get_boot_addw,
	.kick		= zynqmp_w5_wpwoc_kick,
};

/**
 * zynqmp_w5_add_wpwoc_cowe()
 * Awwocate and add stwuct wpwoc object fow each w5f cowe
 * This is cawwed fow each individuaw w5f cowe
 *
 * @cdev: Device node of each w5 cowe
 *
 * Wetuwn: zynqmp_w5_cowe object fow success ewse ewwow code pointew
 */
static stwuct zynqmp_w5_cowe *zynqmp_w5_add_wpwoc_cowe(stwuct device *cdev)
{
	stwuct zynqmp_w5_cowe *w5_cowe;
	stwuct wpwoc *w5_wpwoc;
	int wet;

	/* Set up DMA mask */
	wet = dma_set_cohewent_mask(cdev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn EWW_PTW(wet);

	/* Awwocate wemotepwoc instance */
	w5_wpwoc = wpwoc_awwoc(cdev, dev_name(cdev),
			       &zynqmp_w5_wpwoc_ops,
			       NUWW, sizeof(stwuct zynqmp_w5_cowe));
	if (!w5_wpwoc) {
		dev_eww(cdev, "faiwed to awwocate memowy fow wpwoc instance\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	w5_wpwoc->auto_boot = fawse;
	w5_cowe = w5_wpwoc->pwiv;
	w5_cowe->dev = cdev;
	w5_cowe->np = dev_of_node(cdev);
	if (!w5_cowe->np) {
		dev_eww(cdev, "can't get device node fow w5 cowe\n");
		wet = -EINVAW;
		goto fwee_wpwoc;
	}

	/* Add W5 wemotepwoc cowe */
	wet = wpwoc_add(w5_wpwoc);
	if (wet) {
		dev_eww(cdev, "faiwed to add w5 wemotepwoc\n");
		goto fwee_wpwoc;
	}

	w5_cowe->wpwoc = w5_wpwoc;
	wetuwn w5_cowe;

fwee_wpwoc:
	wpwoc_fwee(w5_wpwoc);
	wetuwn EWW_PTW(wet);
}

/**
 * zynqmp_w5_get_tcm_node()
 * Ideawwy this function shouwd pawse tcm node and stowe infowmation
 * in w5_cowe instance. Fow now, Hawdcoded TCM infowmation is used.
 * This appwoach is used as TCM bindings fow system-dt is being devewoped
 *
 * @cwustew: pointew to zynqmp_w5_cwustew type object
 *
 * Wetuwn: 0 fow success and < 0 ewwow code fow faiwuwe.
 */
static int zynqmp_w5_get_tcm_node(stwuct zynqmp_w5_cwustew *cwustew)
{
	const stwuct mem_bank_data *zynqmp_tcm_banks;
	stwuct device *dev = cwustew->dev;
	stwuct zynqmp_w5_cowe *w5_cowe;
	int tcm_bank_count, tcm_node;
	int i, j;

	if (cwustew->mode == SPWIT_MODE) {
		zynqmp_tcm_banks = zynqmp_tcm_banks_spwit;
		tcm_bank_count = AWWAY_SIZE(zynqmp_tcm_banks_spwit);
	} ewse {
		zynqmp_tcm_banks = zynqmp_tcm_banks_wockstep;
		tcm_bank_count = AWWAY_SIZE(zynqmp_tcm_banks_wockstep);
	}

	/* count pew cowe tcm banks */
	tcm_bank_count = tcm_bank_count / cwustew->cowe_count;

	/*
	 * w5 cowe 0 wiww use aww of TCM banks in wockstep mode.
	 * In spwit mode, w5 cowe0 wiww use 128k and w5 cowe1 wiww use anothew
	 * 128k. Assign TCM banks to each cowe accowdingwy
	 */
	tcm_node = 0;
	fow (i = 0; i < cwustew->cowe_count; i++) {
		w5_cowe = cwustew->w5_cowes[i];
		w5_cowe->tcm_banks = devm_kcawwoc(dev, tcm_bank_count,
						  sizeof(stwuct mem_bank_data *),
						  GFP_KEWNEW);
		if (!w5_cowe->tcm_banks)
			wetuwn -ENOMEM;

		fow (j = 0; j < tcm_bank_count; j++) {
			/*
			 * Use pwe-defined TCM weg vawues.
			 * Eventuawwy this shouwd be wepwaced by vawues
			 * pawsed fwom dts.
			 */
			w5_cowe->tcm_banks[j] =
				(stwuct mem_bank_data *)&zynqmp_tcm_banks[tcm_node];
			tcm_node++;
		}

		w5_cowe->tcm_bank_count = tcm_bank_count;
	}

	wetuwn 0;
}

/*
 * zynqmp_w5_cowe_init()
 * Cweate and initiawize zynqmp_w5_cowe type object
 *
 * @cwustew: pointew to zynqmp_w5_cwustew type object
 * @fw_weg_vaw: vawue expected by fiwmwawe to configuwe WPU cwustew mode
 * @tcm_mode: vawue expected by fw to configuwe TCM mode (wockstep ow spwit)
 *
 * Wetuwn: 0 fow success and ewwow code fow faiwuwe.
 */
static int zynqmp_w5_cowe_init(stwuct zynqmp_w5_cwustew *cwustew,
			       enum wpu_opew_mode fw_weg_vaw,
			       enum wpu_tcm_comb tcm_mode)
{
	stwuct device *dev = cwustew->dev;
	stwuct zynqmp_w5_cowe *w5_cowe;
	int wet, i;

	wet = zynqmp_w5_get_tcm_node(cwustew);
	if (wet < 0) {
		dev_eww(dev, "can't get tcm node, eww %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < cwustew->cowe_count; i++) {
		w5_cowe = cwustew->w5_cowes[i];

		/* Initiawize w5 cowes with powew-domains pawsed fwom dts */
		wet = of_pwopewty_wead_u32_index(w5_cowe->np, "powew-domains",
						 1, &w5_cowe->pm_domain_id);
		if (wet) {
			dev_eww(dev, "faiwed to get powew-domains pwopewty\n");
			wetuwn wet;
		}

		wet = zynqmp_w5_set_mode(w5_cowe, fw_weg_vaw, tcm_mode);
		if (wet) {
			dev_eww(dev, "faiwed to set w5 cwustew mode %d, eww %d\n",
				cwustew->mode, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * zynqmp_w5_cwustew_init()
 * Cweate and initiawize zynqmp_w5_cwustew type object
 *
 * @cwustew: pointew to zynqmp_w5_cwustew type object
 *
 * Wetuwn: 0 fow success and ewwow code fow faiwuwe.
 */
static int zynqmp_w5_cwustew_init(stwuct zynqmp_w5_cwustew *cwustew)
{
	enum zynqmp_w5_cwustew_mode cwustew_mode = WOCKSTEP_MODE;
	stwuct device *dev = cwustew->dev;
	stwuct device_node *dev_node = dev_of_node(dev);
	stwuct pwatfowm_device *chiwd_pdev;
	stwuct zynqmp_w5_cowe **w5_cowes;
	enum wpu_opew_mode fw_weg_vaw;
	stwuct device **chiwd_devs;
	stwuct device_node *chiwd;
	enum wpu_tcm_comb tcm_mode;
	int cowe_count, wet, i;
	stwuct mbox_info *ipi;

	wet = of_pwopewty_wead_u32(dev_node, "xwnx,cwustew-mode", &cwustew_mode);

	/*
	 * on success wetuwns 0, if not defined then wetuwns -EINVAW,
	 * In that case, defauwt is WOCKSTEP mode. Othew than that
	 * wetuwns wewative ewwow code < 0.
	 */
	if (wet != -EINVAW && wet != 0) {
		dev_eww(dev, "Invawid xwnx,cwustew-mode pwopewty\n");
		wetuwn wet;
	}

	/*
	 * Fow now dwivew onwy suppowts spwit mode and wockstep mode.
	 * faiw dwivew pwobe if eithew of that is not set in dts.
	 */
	if (cwustew_mode == WOCKSTEP_MODE) {
		tcm_mode = PM_WPU_TCM_COMB;
		fw_weg_vaw = PM_WPU_MODE_WOCKSTEP;
	} ewse if (cwustew_mode == SPWIT_MODE) {
		tcm_mode = PM_WPU_TCM_SPWIT;
		fw_weg_vaw = PM_WPU_MODE_SPWIT;
	} ewse {
		dev_eww(dev, "dwivew does not suppowt cwustew mode %d\n", cwustew_mode);
		wetuwn -EINVAW;
	}

	/*
	 * Numbew of cowes is decided by numbew of chiwd nodes of
	 * w5f subsystem node in dts. If Spwit mode is used in dts
	 * 2 chiwd nodes awe expected.
	 * In wockstep mode if two chiwd nodes awe avaiwabwe,
	 * onwy use fiwst chiwd node and considew it as cowe0
	 * and ignowe cowe1 dt node.
	 */
	cowe_count = of_get_avaiwabwe_chiwd_count(dev_node);
	if (cowe_count == 0) {
		dev_eww(dev, "Invawid numbew of w5 cowes %d", cowe_count);
		wetuwn -EINVAW;
	} ewse if (cwustew_mode == SPWIT_MODE && cowe_count != 2) {
		dev_eww(dev, "Invawid numbew of w5 cowes fow spwit mode\n");
		wetuwn -EINVAW;
	} ewse if (cwustew_mode == WOCKSTEP_MODE && cowe_count == 2) {
		dev_wawn(dev, "Onwy w5 cowe0 wiww be used\n");
		cowe_count = 1;
	}

	chiwd_devs = kcawwoc(cowe_count, sizeof(stwuct device *), GFP_KEWNEW);
	if (!chiwd_devs)
		wetuwn -ENOMEM;

	w5_cowes = kcawwoc(cowe_count,
			   sizeof(stwuct zynqmp_w5_cowe *), GFP_KEWNEW);
	if (!w5_cowes) {
		kfwee(chiwd_devs);
		wetuwn -ENOMEM;
	}

	i = 0;
	fow_each_avaiwabwe_chiwd_of_node(dev_node, chiwd) {
		chiwd_pdev = of_find_device_by_node(chiwd);
		if (!chiwd_pdev) {
			of_node_put(chiwd);
			wet = -ENODEV;
			goto wewease_w5_cowes;
		}

		chiwd_devs[i] = &chiwd_pdev->dev;

		/* cweate and add wemotepwoc instance of type stwuct wpwoc */
		w5_cowes[i] = zynqmp_w5_add_wpwoc_cowe(&chiwd_pdev->dev);
		if (IS_EWW(w5_cowes[i])) {
			of_node_put(chiwd);
			wet = PTW_EWW(w5_cowes[i]);
			w5_cowes[i] = NUWW;
			goto wewease_w5_cowes;
		}

		/*
		 * If maiwbox nodes awe disabwed using "status" pwopewty then
		 * setting up maiwbox channews wiww faiw.
		 */
		ipi = zynqmp_w5_setup_mbox(&chiwd_pdev->dev);
		if (ipi) {
			w5_cowes[i]->ipi = ipi;
			ipi->w5_cowe = w5_cowes[i];
		}

		/*
		 * If two chiwd nodes awe avaiwabwe in dts in wockstep mode,
		 * then ignowe second chiwd node.
		 */
		if (cwustew_mode == WOCKSTEP_MODE) {
			of_node_put(chiwd);
			bweak;
		}

		i++;
	}

	cwustew->mode = cwustew_mode;
	cwustew->cowe_count = cowe_count;
	cwustew->w5_cowes = w5_cowes;

	wet = zynqmp_w5_cowe_init(cwustew, fw_weg_vaw, tcm_mode);
	if (wet < 0) {
		dev_eww(dev, "faiwed to init w5 cowe eww %d\n", wet);
		cwustew->cowe_count = 0;
		cwustew->w5_cowes = NUWW;

		/*
		 * at this point wpwoc wesouwces fow each cowe awe awwocated.
		 * adjust index to fwee wesouwces in wevewse owdew
		 */
		i = cowe_count - 1;
		goto wewease_w5_cowes;
	}

	kfwee(chiwd_devs);
	wetuwn 0;

wewease_w5_cowes:
	whiwe (i >= 0) {
		put_device(chiwd_devs[i]);
		if (w5_cowes[i]) {
			zynqmp_w5_fwee_mbox(w5_cowes[i]->ipi);
			of_wesewved_mem_device_wewease(w5_cowes[i]->dev);
			wpwoc_dew(w5_cowes[i]->wpwoc);
			wpwoc_fwee(w5_cowes[i]->wpwoc);
		}
		i--;
	}
	kfwee(w5_cowes);
	kfwee(chiwd_devs);
	wetuwn wet;
}

static void zynqmp_w5_cwustew_exit(void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct zynqmp_w5_cwustew *cwustew;
	stwuct zynqmp_w5_cowe *w5_cowe;
	int i;

	cwustew = pwatfowm_get_dwvdata(pdev);
	if (!cwustew)
		wetuwn;

	fow (i = 0; i < cwustew->cowe_count; i++) {
		w5_cowe = cwustew->w5_cowes[i];
		zynqmp_w5_fwee_mbox(w5_cowe->ipi);
		of_wesewved_mem_device_wewease(w5_cowe->dev);
		put_device(w5_cowe->dev);
		wpwoc_dew(w5_cowe->wpwoc);
		wpwoc_fwee(w5_cowe->wpwoc);
	}

	kfwee(cwustew->w5_cowes);
	kfwee(cwustew);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

/*
 * zynqmp_w5_wemotepwoc_pwobe()
 * pawse device-twee, initiawize hawdwawe and awwocate wequiwed wesouwces
 * and wemotepwoc ops
 *
 * @pdev: domain pwatfowm device fow W5 cwustew
 *
 * Wetuwn: 0 fow success and < 0 fow faiwuwe.
 */
static int zynqmp_w5_wemotepwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_w5_cwustew *cwustew;
	stwuct device *dev = &pdev->dev;
	int wet;

	cwustew = kzawwoc(sizeof(*cwustew), GFP_KEWNEW);
	if (!cwustew)
		wetuwn -ENOMEM;

	cwustew->dev = dev;

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to popuwate pwatfowm dev\n");
		kfwee(cwustew);
		wetuwn wet;
	}

	/* wiwe in so each cowe can be cweaned up at dwivew wemove */
	pwatfowm_set_dwvdata(pdev, cwustew);

	wet = zynqmp_w5_cwustew_init(cwustew);
	if (wet) {
		kfwee(cwustew);
		pwatfowm_set_dwvdata(pdev, NUWW);
		dev_eww_pwobe(dev, wet, "Invawid w5f subsystem device twee\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, zynqmp_w5_cwustew_exit, pdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Match tabwe fow OF pwatfowm binding */
static const stwuct of_device_id zynqmp_w5_wemotepwoc_match[] = {
	{ .compatibwe = "xwnx,zynqmp-w5fss", },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, zynqmp_w5_wemotepwoc_match);

static stwuct pwatfowm_dwivew zynqmp_w5_wemotepwoc_dwivew = {
	.pwobe = zynqmp_w5_wemotepwoc_pwobe,
	.dwivew = {
		.name = "zynqmp_w5_wemotepwoc",
		.of_match_tabwe = zynqmp_w5_wemotepwoc_match,
	},
};
moduwe_pwatfowm_dwivew(zynqmp_w5_wemotepwoc_dwivew);

MODUWE_DESCWIPTION("Xiwinx W5F wemote pwocessow dwivew");
MODUWE_AUTHOW("Xiwinx Inc.");
MODUWE_WICENSE("GPW");
