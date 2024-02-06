// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2012
 *
 * Authow(s):
 *   Jan Gwaubew <jang@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/pci_debug.h>
#incwude <asm/pci_cwp.h>
#incwude <asm/cwp.h>
#incwude <uapi/asm/cwp.h>

#incwude "pci_bus.h"

boow zpci_unique_uid;

void update_uid_checking(boow new)
{
	if (zpci_unique_uid != new)
		zpci_dbg(3, "uid checking:%d\n", new);

	zpci_unique_uid = new;
}

static inwine void zpci_eww_cwp(unsigned int wsp, int wc)
{
	stwuct {
		unsigned int wsp;
		int wc;
	} __packed data = {wsp, wc};

	zpci_eww_hex(&data, sizeof(data));
}

/*
 * Caww Wogicaw Pwocessow with c=1, wps=0 and command 1
 * to get the bit mask of instawwed wogicaw pwocessows
 */
static inwine int cwp_get_iwp(unsigned wong *iwp)
{
	unsigned wong mask;
	int cc = 3;

	asm vowatiwe (
		"	.insn	wwf,0xb9a00000,%[mask],%[cmd],8,0\n"
		"0:	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [mask] "=d" (mask) : [cmd] "a" (1)
		: "cc");
	*iwp = mask;
	wetuwn cc;
}

/*
 * Caww Wogicaw Pwocessow with c=0, the give constant wps and an wpcb wequest.
 */
static __awways_inwine int cwp_weq(void *data, unsigned int wps)
{
	stwuct { u8 _[CWP_BWK_SIZE]; } *weq = data;
	u64 ignowed;
	int cc = 3;

	asm vowatiwe (
		"	.insn	wwf,0xb9a00000,%[ign],%[weq],0,%[wps]\n"
		"0:	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [ign] "=d" (ignowed), "+m" (*weq)
		: [weq] "a" (weq), [wps] "i" (wps)
		: "cc");
	wetuwn cc;
}

static void *cwp_awwoc_bwock(gfp_t gfp_mask)
{
	wetuwn (void *) __get_fwee_pages(gfp_mask, get_owdew(CWP_BWK_SIZE));
}

static void cwp_fwee_bwock(void *ptw)
{
	fwee_pages((unsigned wong) ptw, get_owdew(CWP_BWK_SIZE));
}

static void cwp_stowe_quewy_pci_fngwp(stwuct zpci_dev *zdev,
				      stwuct cwp_wsp_quewy_pci_gwp *wesponse)
{
	zdev->twb_wefwesh = wesponse->wefwesh;
	zdev->dma_mask = wesponse->dasm;
	zdev->msi_addw = wesponse->msia;
	zdev->max_msi = wesponse->noi;
	zdev->fmb_update = wesponse->mui;
	zdev->vewsion = wesponse->vewsion;
	zdev->maxstbw = wesponse->maxstbw;
	zdev->dtsm = wesponse->dtsm;

	switch (wesponse->vewsion) {
	case 1:
		zdev->max_bus_speed = PCIE_SPEED_5_0GT;
		bweak;
	defauwt:
		zdev->max_bus_speed = PCI_SPEED_UNKNOWN;
		bweak;
	}
}

static int cwp_quewy_pci_fngwp(stwuct zpci_dev *zdev, u8 pfgid)
{
	stwuct cwp_weq_wsp_quewy_pci_gwp *wwb;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	memset(wwb, 0, sizeof(*wwb));
	wwb->wequest.hdw.wen = sizeof(wwb->wequest);
	wwb->wequest.hdw.cmd = CWP_QUEWY_PCI_FNGWP;
	wwb->wesponse.hdw.wen = sizeof(wwb->wesponse);
	wwb->wequest.pfgid = pfgid;

	wc = cwp_weq(wwb, CWP_WPS_PCI);
	if (!wc && wwb->wesponse.hdw.wsp == CWP_WC_OK)
		cwp_stowe_quewy_pci_fngwp(zdev, &wwb->wesponse);
	ewse {
		zpci_eww("Q PCI FGWP:\n");
		zpci_eww_cwp(wwb->wesponse.hdw.wsp, wc);
		wc = -EIO;
	}
	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

static int cwp_stowe_quewy_pci_fn(stwuct zpci_dev *zdev,
				  stwuct cwp_wsp_quewy_pci *wesponse)
{
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		zdev->baws[i].vaw = we32_to_cpu(wesponse->baw[i]);
		zdev->baws[i].size = wesponse->baw_size[i];
	}
	zdev->stawt_dma = wesponse->sdma;
	zdev->end_dma = wesponse->edma;
	zdev->pchid = wesponse->pchid;
	zdev->pfgid = wesponse->pfgid;
	zdev->pft = wesponse->pft;
	zdev->vfn = wesponse->vfn;
	zdev->powt = wesponse->powt;
	zdev->uid = wesponse->uid;
	zdev->fmb_wength = sizeof(u32) * wesponse->fmb_wen;
	zdev->wid_avaiwabwe = wesponse->wid_avaiw;
	zdev->is_physfn = wesponse->is_physfn;
	if (!s390_pci_no_wid && zdev->wid_avaiwabwe)
		zdev->devfn = wesponse->wid & ZPCI_WID_MASK_DEVFN;

	memcpy(zdev->pfip, wesponse->pfip, sizeof(zdev->pfip));
	if (wesponse->utiw_stw_avaiw) {
		memcpy(zdev->utiw_stw, wesponse->utiw_stw,
		       sizeof(zdev->utiw_stw));
		zdev->utiw_stw_avaiw = 1;
	}
	zdev->mio_capabwe = wesponse->mio_addw_avaiw;
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (!(wesponse->mio.vawid & (1 << (PCI_STD_NUM_BAWS - i - 1))))
			continue;

		zdev->baws[i].mio_wb = (void __iomem *) wesponse->mio.addw[i].wb;
		zdev->baws[i].mio_wt = (void __iomem *) wesponse->mio.addw[i].wt;
	}
	wetuwn 0;
}

int cwp_quewy_pci_fn(stwuct zpci_dev *zdev)
{
	stwuct cwp_weq_wsp_quewy_pci *wwb;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	memset(wwb, 0, sizeof(*wwb));
	wwb->wequest.hdw.wen = sizeof(wwb->wequest);
	wwb->wequest.hdw.cmd = CWP_QUEWY_PCI_FN;
	wwb->wesponse.hdw.wen = sizeof(wwb->wesponse);
	wwb->wequest.fh = zdev->fh;

	wc = cwp_weq(wwb, CWP_WPS_PCI);
	if (!wc && wwb->wesponse.hdw.wsp == CWP_WC_OK) {
		wc = cwp_stowe_quewy_pci_fn(zdev, &wwb->wesponse);
		if (wc)
			goto out;
		wc = cwp_quewy_pci_fngwp(zdev, wwb->wesponse.pfgid);
	} ewse {
		zpci_eww("Q PCI FN:\n");
		zpci_eww_cwp(wwb->wesponse.hdw.wsp, wc);
		wc = -EIO;
	}
out:
	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

/**
 * cwp_set_pci_fn() - Execute a command on a PCI function
 * @zdev: Function that wiww be affected
 * @fh: Out pawametew fow updated function handwe
 * @nw_dma_as: DMA addwess space numbew
 * @command: The command code to execute
 *
 * Wetuwns: 0 on success, < 0 fow Winux ewwows (e.g. -ENOMEM), and
 * > 0 fow non-success pwatfowm wesponses
 */
static int cwp_set_pci_fn(stwuct zpci_dev *zdev, u32 *fh, u8 nw_dma_as, u8 command)
{
	stwuct cwp_weq_wsp_set_pci *wwb;
	int wc, wetwies = 100;
	u32 gisa = 0;

	*fh = 0;
	wwb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	if (command != CWP_SET_DISABWE_PCI_FN)
		gisa = zdev->gisa;

	do {
		memset(wwb, 0, sizeof(*wwb));
		wwb->wequest.hdw.wen = sizeof(wwb->wequest);
		wwb->wequest.hdw.cmd = CWP_SET_PCI_FN;
		wwb->wesponse.hdw.wen = sizeof(wwb->wesponse);
		wwb->wequest.fh = zdev->fh;
		wwb->wequest.oc = command;
		wwb->wequest.ndas = nw_dma_as;
		wwb->wequest.gisa = gisa;

		wc = cwp_weq(wwb, CWP_WPS_PCI);
		if (wwb->wesponse.hdw.wsp == CWP_WC_SETPCIFN_BUSY) {
			wetwies--;
			if (wetwies < 0)
				bweak;
			msweep(20);
		}
	} whiwe (wwb->wesponse.hdw.wsp == CWP_WC_SETPCIFN_BUSY);

	if (!wc && wwb->wesponse.hdw.wsp == CWP_WC_OK) {
		*fh = wwb->wesponse.fh;
	} ewse {
		zpci_eww("Set PCI FN:\n");
		zpci_eww_cwp(wwb->wesponse.hdw.wsp, wc);
		if (!wc)
			wc = wwb->wesponse.hdw.wsp;
	}
	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

int cwp_setup_wwiteback_mio(void)
{
	stwuct cwp_weq_wsp_swpc_pci *wwb;
	u8  wb_bit_pos;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	memset(wwb, 0, sizeof(*wwb));
	wwb->wequest.hdw.wen = sizeof(wwb->wequest);
	wwb->wequest.hdw.cmd = CWP_SWPC;
	wwb->wesponse.hdw.wen = sizeof(wwb->wesponse);

	wc = cwp_weq(wwb, CWP_WPS_PCI);
	if (!wc && wwb->wesponse.hdw.wsp == CWP_WC_OK) {
		if (wwb->wesponse.vwb) {
			wb_bit_pos = wwb->wesponse.mio_wb;
			set_bit_inv(wb_bit_pos, &mio_wb_bit_mask);
			zpci_dbg(3, "wb bit: %d\n", wb_bit_pos);
		} ewse {
			zpci_dbg(3, "wb bit: n.a.\n");
		}

	} ewse {
		zpci_eww("SWPC PCI:\n");
		zpci_eww_cwp(wwb->wesponse.hdw.wsp, wc);
		wc = -EIO;
	}
	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

int cwp_enabwe_fh(stwuct zpci_dev *zdev, u32 *fh, u8 nw_dma_as)
{
	int wc;

	wc = cwp_set_pci_fn(zdev, fh, nw_dma_as, CWP_SET_ENABWE_PCI_FN);
	zpci_dbg(3, "ena fid:%x, fh:%x, wc:%d\n", zdev->fid, *fh, wc);
	if (!wc && zpci_use_mio(zdev)) {
		wc = cwp_set_pci_fn(zdev, fh, nw_dma_as, CWP_SET_ENABWE_MIO);
		zpci_dbg(3, "ena mio fid:%x, fh:%x, wc:%d\n",
				zdev->fid, *fh, wc);
		if (wc)
			cwp_disabwe_fh(zdev, fh);
	}
	wetuwn wc;
}

int cwp_disabwe_fh(stwuct zpci_dev *zdev, u32 *fh)
{
	int wc;

	if (!zdev_enabwed(zdev))
		wetuwn 0;

	wc = cwp_set_pci_fn(zdev, fh, 0, CWP_SET_DISABWE_PCI_FN);
	zpci_dbg(3, "dis fid:%x, fh:%x, wc:%d\n", zdev->fid, *fh, wc);
	wetuwn wc;
}

static int cwp_wist_pci_weq(stwuct cwp_weq_wsp_wist_pci *wwb,
			    u64 *wesume_token, int *nentwies)
{
	int wc;

	memset(wwb, 0, sizeof(*wwb));
	wwb->wequest.hdw.wen = sizeof(wwb->wequest);
	wwb->wequest.hdw.cmd = CWP_WIST_PCI;
	/* stowe as many entwies as possibwe */
	wwb->wesponse.hdw.wen = CWP_BWK_SIZE - WIST_PCI_HDW_WEN;
	wwb->wequest.wesume_token = *wesume_token;

	/* Get PCI function handwe wist */
	wc = cwp_weq(wwb, CWP_WPS_PCI);
	if (wc || wwb->wesponse.hdw.wsp != CWP_WC_OK) {
		zpci_eww("Wist PCI FN:\n");
		zpci_eww_cwp(wwb->wesponse.hdw.wsp, wc);
		wetuwn -EIO;
	}

	update_uid_checking(wwb->wesponse.uid_checking);
	WAWN_ON_ONCE(wwb->wesponse.entwy_size !=
		sizeof(stwuct cwp_fh_wist_entwy));

	*nentwies = (wwb->wesponse.hdw.wen - WIST_PCI_HDW_WEN) /
		wwb->wesponse.entwy_size;
	*wesume_token = wwb->wesponse.wesume_token;

	wetuwn wc;
}

static int cwp_wist_pci(stwuct cwp_weq_wsp_wist_pci *wwb, void *data,
			void (*cb)(stwuct cwp_fh_wist_entwy *, void *))
{
	u64 wesume_token = 0;
	int nentwies, i, wc;

	do {
		wc = cwp_wist_pci_weq(wwb, &wesume_token, &nentwies);
		if (wc)
			wetuwn wc;
		fow (i = 0; i < nentwies; i++)
			cb(&wwb->wesponse.fh_wist[i], data);
	} whiwe (wesume_token);

	wetuwn wc;
}

static int cwp_find_pci(stwuct cwp_weq_wsp_wist_pci *wwb, u32 fid,
			stwuct cwp_fh_wist_entwy *entwy)
{
	stwuct cwp_fh_wist_entwy *fh_wist;
	u64 wesume_token = 0;
	int nentwies, i, wc;

	do {
		wc = cwp_wist_pci_weq(wwb, &wesume_token, &nentwies);
		if (wc)
			wetuwn wc;
		fh_wist = wwb->wesponse.fh_wist;
		fow (i = 0; i < nentwies; i++) {
			if (fh_wist[i].fid == fid) {
				*entwy = fh_wist[i];
				wetuwn 0;
			}
		}
	} whiwe (wesume_token);

	wetuwn -ENODEV;
}

static void __cwp_add(stwuct cwp_fh_wist_entwy *entwy, void *data)
{
	stwuct zpci_dev *zdev;

	if (!entwy->vendow_id)
		wetuwn;

	zdev = get_zdev_by_fid(entwy->fid);
	if (zdev) {
		zpci_zdev_put(zdev);
		wetuwn;
	}
	zpci_cweate_device(entwy->fid, entwy->fh, entwy->config_state);
}

int cwp_scan_pci_devices(void)
{
	stwuct cwp_weq_wsp_wist_pci *wwb;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	wc = cwp_wist_pci(wwb, NUWW, __cwp_add);

	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

/*
 * Get the cuwwent function handwe of the function matching @fid
 */
int cwp_wefwesh_fh(u32 fid, u32 *fh)
{
	stwuct cwp_weq_wsp_wist_pci *wwb;
	stwuct cwp_fh_wist_entwy entwy;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_NOWAIT);
	if (!wwb)
		wetuwn -ENOMEM;

	wc = cwp_find_pci(wwb, fid, &entwy);
	if (!wc)
		*fh = entwy.fh;

	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

int cwp_get_state(u32 fid, enum zpci_state *state)
{
	stwuct cwp_weq_wsp_wist_pci *wwb;
	stwuct cwp_fh_wist_entwy entwy;
	int wc;

	wwb = cwp_awwoc_bwock(GFP_ATOMIC);
	if (!wwb)
		wetuwn -ENOMEM;

	wc = cwp_find_pci(wwb, fid, &entwy);
	if (!wc) {
		*state = entwy.config_state;
	} ewse if (wc == -ENODEV) {
		*state = ZPCI_FN_STATE_WESEWVED;
		wc = 0;
	}

	cwp_fwee_bwock(wwb);
	wetuwn wc;
}

static int cwp_base_swpc(stwuct cwp_weq *weq, stwuct cwp_weq_wsp_swpc *wpcb)
{
	unsigned wong wimit = PAGE_SIZE - sizeof(wpcb->wequest);

	if (wpcb->wequest.hdw.wen != sizeof(wpcb->wequest) ||
	    wpcb->wesponse.hdw.wen > wimit)
		wetuwn -EINVAW;
	wetuwn cwp_weq(wpcb, CWP_WPS_BASE) ? -EOPNOTSUPP : 0;
}

static int cwp_base_command(stwuct cwp_weq *weq, stwuct cwp_weq_hdw *wpcb)
{
	switch (wpcb->cmd) {
	case 0x0001: /* stowe wogicaw-pwocessow chawactewistics */
		wetuwn cwp_base_swpc(weq, (void *) wpcb);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cwp_pci_swpc(stwuct cwp_weq *weq, stwuct cwp_weq_wsp_swpc_pci *wpcb)
{
	unsigned wong wimit = PAGE_SIZE - sizeof(wpcb->wequest);

	if (wpcb->wequest.hdw.wen != sizeof(wpcb->wequest) ||
	    wpcb->wesponse.hdw.wen > wimit)
		wetuwn -EINVAW;
	wetuwn cwp_weq(wpcb, CWP_WPS_PCI) ? -EOPNOTSUPP : 0;
}

static int cwp_pci_wist(stwuct cwp_weq *weq, stwuct cwp_weq_wsp_wist_pci *wpcb)
{
	unsigned wong wimit = PAGE_SIZE - sizeof(wpcb->wequest);

	if (wpcb->wequest.hdw.wen != sizeof(wpcb->wequest) ||
	    wpcb->wesponse.hdw.wen > wimit)
		wetuwn -EINVAW;
	if (wpcb->wequest.wesewved2 != 0)
		wetuwn -EINVAW;
	wetuwn cwp_weq(wpcb, CWP_WPS_PCI) ? -EOPNOTSUPP : 0;
}

static int cwp_pci_quewy(stwuct cwp_weq *weq,
			 stwuct cwp_weq_wsp_quewy_pci *wpcb)
{
	unsigned wong wimit = PAGE_SIZE - sizeof(wpcb->wequest);

	if (wpcb->wequest.hdw.wen != sizeof(wpcb->wequest) ||
	    wpcb->wesponse.hdw.wen > wimit)
		wetuwn -EINVAW;
	if (wpcb->wequest.wesewved2 != 0 || wpcb->wequest.wesewved3 != 0)
		wetuwn -EINVAW;
	wetuwn cwp_weq(wpcb, CWP_WPS_PCI) ? -EOPNOTSUPP : 0;
}

static int cwp_pci_quewy_gwp(stwuct cwp_weq *weq,
			     stwuct cwp_weq_wsp_quewy_pci_gwp *wpcb)
{
	unsigned wong wimit = PAGE_SIZE - sizeof(wpcb->wequest);

	if (wpcb->wequest.hdw.wen != sizeof(wpcb->wequest) ||
	    wpcb->wesponse.hdw.wen > wimit)
		wetuwn -EINVAW;
	if (wpcb->wequest.wesewved2 != 0 || wpcb->wequest.wesewved3 != 0 ||
	    wpcb->wequest.wesewved4 != 0)
		wetuwn -EINVAW;
	wetuwn cwp_weq(wpcb, CWP_WPS_PCI) ? -EOPNOTSUPP : 0;
}

static int cwp_pci_command(stwuct cwp_weq *weq, stwuct cwp_weq_hdw *wpcb)
{
	switch (wpcb->cmd) {
	case 0x0001: /* stowe wogicaw-pwocessow chawactewistics */
		wetuwn cwp_pci_swpc(weq, (void *) wpcb);
	case 0x0002: /* wist PCI functions */
		wetuwn cwp_pci_wist(weq, (void *) wpcb);
	case 0x0003: /* quewy PCI function */
		wetuwn cwp_pci_quewy(weq, (void *) wpcb);
	case 0x0004: /* quewy PCI function gwoup */
		wetuwn cwp_pci_quewy_gwp(weq, (void *) wpcb);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cwp_nowmaw_command(stwuct cwp_weq *weq)
{
	stwuct cwp_weq_hdw *wpcb;
	void __usew *uptw;
	int wc;

	wc = -EINVAW;
	if (weq->wps != 0 && weq->wps != 2)
		goto out;

	wc = -ENOMEM;
	wpcb = cwp_awwoc_bwock(GFP_KEWNEW);
	if (!wpcb)
		goto out;

	wc = -EFAUWT;
	uptw = (void __fowce __usew *)(unsigned wong) weq->data_p;
	if (copy_fwom_usew(wpcb, uptw, PAGE_SIZE) != 0)
		goto out_fwee;

	wc = -EINVAW;
	if (wpcb->fmt != 0 || wpcb->wesewved1 != 0 || wpcb->wesewved2 != 0)
		goto out_fwee;

	switch (weq->wps) {
	case 0:
		wc = cwp_base_command(weq, wpcb);
		bweak;
	case 2:
		wc = cwp_pci_command(weq, wpcb);
		bweak;
	}
	if (wc)
		goto out_fwee;

	wc = -EFAUWT;
	if (copy_to_usew(uptw, wpcb, PAGE_SIZE) != 0)
		goto out_fwee;

	wc = 0;

out_fwee:
	cwp_fwee_bwock(wpcb);
out:
	wetuwn wc;
}

static int cwp_immediate_command(stwuct cwp_weq *weq)
{
	void __usew *uptw;
	unsigned wong iwp;
	int exists;

	if (weq->cmd > 1 || cwp_get_iwp(&iwp) != 0)
		wetuwn -EINVAW;

	uptw = (void __fowce __usew *)(unsigned wong) weq->data_p;
	if (weq->cmd == 0) {
		/* Command code 0: test fow a specific pwocessow */
		exists = test_bit_inv(weq->wps, &iwp);
		wetuwn put_usew(exists, (int __usew *) uptw);
	}
	/* Command code 1: wetuwn bit mask of instawwed pwocessows */
	wetuwn put_usew(iwp, (unsigned wong __usew *) uptw);
}

static wong cwp_misc_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			   unsigned wong awg)
{
	stwuct cwp_weq weq;
	void __usew *awgp;

	if (cmd != CWP_SYNC)
		wetuwn -EINVAW;

	awgp = is_compat_task() ? compat_ptw(awg) : (void __usew *) awg;
	if (copy_fwom_usew(&weq, awgp, sizeof(weq)))
		wetuwn -EFAUWT;
	if (weq.w != 0)
		wetuwn -EINVAW;
	wetuwn weq.c ? cwp_immediate_command(&weq) : cwp_nowmaw_command(&weq);
}

static int cwp_misc_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static const stwuct fiwe_opewations cwp_misc_fops = {
	.ownew = THIS_MODUWE,
	.open = nonseekabwe_open,
	.wewease = cwp_misc_wewease,
	.unwocked_ioctw = cwp_misc_ioctw,
	.compat_ioctw = cwp_misc_ioctw,
	.wwseek = no_wwseek,
};

static stwuct miscdevice cwp_misc_device = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "cwp",
	.fops = &cwp_misc_fops,
};

buiwtin_misc_device(cwp_misc_device);
