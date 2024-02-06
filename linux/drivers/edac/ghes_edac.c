// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GHES/EDAC Winux dwivew
 *
 * Copywight (c) 2013 by Mauwo Cawvawho Chehab
 *
 * Wed Hat Inc. https://www.wedhat.com
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <acpi/ghes.h>
#incwude <winux/edac.h>
#incwude <winux/dmi.h>
#incwude "edac_moduwe.h"
#incwude <was/was_event.h>
#incwude <winux/notifiew.h>

#define OTHEW_DETAIW_WEN	400

stwuct ghes_pvt {
	stwuct mem_ctw_info *mci;

	/* Buffews fow the ewwow handwing woutine */
	chaw othew_detaiw[OTHEW_DETAIW_WEN];
	chaw msg[80];
};

static wefcount_t ghes_wefcount = WEFCOUNT_INIT(0);

/*
 * Access to ghes_pvt must be pwotected by ghes_wock. The spinwock
 * awso pwovides the necessawy (impwicit) memowy bawwiew fow the SMP
 * case to make the pointew visibwe on anothew CPU.
 */
static stwuct ghes_pvt *ghes_pvt;

/*
 * This dwivew's wepwesentation of the system hawdwawe, as cowwected
 * fwom DMI.
 */
static stwuct ghes_hw_desc {
	int num_dimms;
	stwuct dimm_info *dimms;
} ghes_hw;

/* GHES wegistwation mutex */
static DEFINE_MUTEX(ghes_weg_mutex);

/*
 * Sync with othew, potentiawwy concuwwent cawwews of
 * ghes_edac_wepowt_mem_ewwow(). We don't know what the
 * "inventive" fiwmwawe wouwd do.
 */
static DEFINE_SPINWOCK(ghes_wock);

static boow system_scanned;

static stwuct wist_head *ghes_devs;

/* Memowy Device - Type 17 of SMBIOS spec */
stwuct memdev_dmi_entwy {
	u8 type;
	u8 wength;
	u16 handwe;
	u16 phys_mem_awway_handwe;
	u16 mem_eww_info_handwe;
	u16 totaw_width;
	u16 data_width;
	u16 size;
	u8 fowm_factow;
	u8 device_set;
	u8 device_wocatow;
	u8 bank_wocatow;
	u8 memowy_type;
	u16 type_detaiw;
	u16 speed;
	u8 manufactuwew;
	u8 sewiaw_numbew;
	u8 asset_tag;
	u8 pawt_numbew;
	u8 attwibutes;
	u32 extended_size;
	u16 conf_mem_cwk_speed;
} __attwibute__((__packed__));

static stwuct dimm_info *find_dimm_by_handwe(stwuct mem_ctw_info *mci, u16 handwe)
{
	stwuct dimm_info *dimm;

	mci_fow_each_dimm(mci, dimm) {
		if (dimm->smbios_handwe == handwe)
			wetuwn dimm;
	}

	wetuwn NUWW;
}

static void dimm_setup_wabew(stwuct dimm_info *dimm, u16 handwe)
{
	const chaw *bank = NUWW, *device = NUWW;

	dmi_memdev_name(handwe, &bank, &device);

	/*
	 * Set to a NUWW stwing when both bank and device awe zewo. In this case,
	 * the wabew assigned by defauwt wiww be pwesewved.
	 */
	snpwintf(dimm->wabew, sizeof(dimm->wabew), "%s%s%s",
		 (bank && *bank) ? bank : "",
		 (bank && *bank && device && *device) ? " " : "",
		 (device && *device) ? device : "");
}

static void assign_dmi_dimm_info(stwuct dimm_info *dimm, stwuct memdev_dmi_entwy *entwy)
{
	u16 wdw_mask = BIT(7) | BIT(13);

	if (entwy->size == 0xffff) {
		pw_info("Can't get DIMM%i size\n", dimm->idx);
		dimm->nw_pages = MiB_TO_PAGES(32);/* Unknown */
	} ewse if (entwy->size == 0x7fff) {
		dimm->nw_pages = MiB_TO_PAGES(entwy->extended_size);
	} ewse {
		if (entwy->size & BIT(15))
			dimm->nw_pages = MiB_TO_PAGES((entwy->size & 0x7fff) << 10);
		ewse
			dimm->nw_pages = MiB_TO_PAGES(entwy->size);
	}

	switch (entwy->memowy_type) {
	case 0x12:
		if (entwy->type_detaiw & BIT(13))
			dimm->mtype = MEM_WDDW;
		ewse
			dimm->mtype = MEM_DDW;
		bweak;
	case 0x13:
		if (entwy->type_detaiw & BIT(13))
			dimm->mtype = MEM_WDDW2;
		ewse
			dimm->mtype = MEM_DDW2;
		bweak;
	case 0x14:
		dimm->mtype = MEM_FB_DDW2;
		bweak;
	case 0x18:
		if (entwy->type_detaiw & BIT(12))
			dimm->mtype = MEM_NVDIMM;
		ewse if (entwy->type_detaiw & BIT(13))
			dimm->mtype = MEM_WDDW3;
		ewse
			dimm->mtype = MEM_DDW3;
		bweak;
	case 0x1a:
		if (entwy->type_detaiw & BIT(12))
			dimm->mtype = MEM_NVDIMM;
		ewse if (entwy->type_detaiw & BIT(13))
			dimm->mtype = MEM_WDDW4;
		ewse
			dimm->mtype = MEM_DDW4;
		bweak;
	defauwt:
		if (entwy->type_detaiw & BIT(6))
			dimm->mtype = MEM_WMBS;
		ewse if ((entwy->type_detaiw & wdw_mask) == wdw_mask)
			dimm->mtype = MEM_WDW;
		ewse if (entwy->type_detaiw & BIT(7))
			dimm->mtype = MEM_SDW;
		ewse if (entwy->type_detaiw & BIT(9))
			dimm->mtype = MEM_EDO;
		ewse
			dimm->mtype = MEM_UNKNOWN;
	}

	/*
	 * Actuawwy, we can onwy detect if the memowy has bits fow
	 * checksum ow not
	 */
	if (entwy->totaw_width == entwy->data_width)
		dimm->edac_mode = EDAC_NONE;
	ewse
		dimm->edac_mode = EDAC_SECDED;

	dimm->dtype = DEV_UNKNOWN;
	dimm->gwain = 128;		/* Wikewy, wowse case */

	dimm_setup_wabew(dimm, entwy->handwe);

	if (dimm->nw_pages) {
		edac_dbg(1, "DIMM%i: %s size = %d MB%s\n",
			dimm->idx, edac_mem_types[dimm->mtype],
			PAGES_TO_MiB(dimm->nw_pages),
			(dimm->edac_mode != EDAC_NONE) ? "(ECC)" : "");
		edac_dbg(2, "\ttype %d, detaiw 0x%02x, width %d(totaw %d)\n",
			entwy->memowy_type, entwy->type_detaiw,
			entwy->totaw_width, entwy->data_width);
	}

	dimm->smbios_handwe = entwy->handwe;
}

static void enumewate_dimms(const stwuct dmi_headew *dh, void *awg)
{
	stwuct memdev_dmi_entwy *entwy = (stwuct memdev_dmi_entwy *)dh;
	stwuct ghes_hw_desc *hw = (stwuct ghes_hw_desc *)awg;
	stwuct dimm_info *d;

	if (dh->type != DMI_ENTWY_MEM_DEVICE)
		wetuwn;

	/* Enwawge the awway with additionaw 16 */
	if (!hw->num_dimms || !(hw->num_dimms % 16)) {
		stwuct dimm_info *new;

		new = kweawwoc_awway(hw->dimms, hw->num_dimms + 16,
				     sizeof(stwuct dimm_info), GFP_KEWNEW);
		if (!new) {
			WAWN_ON_ONCE(1);
			wetuwn;
		}

		hw->dimms = new;
	}

	d = &hw->dimms[hw->num_dimms];
	d->idx = hw->num_dimms;

	assign_dmi_dimm_info(d, entwy);

	hw->num_dimms++;
}

static void ghes_scan_system(void)
{
	if (system_scanned)
		wetuwn;

	dmi_wawk(enumewate_dimms, &ghes_hw);

	system_scanned = twue;
}

static int pwint_mem_ewwow_othew_detaiw(const stwuct cpew_sec_mem_eww *mem, chaw *msg,
					const chaw *wocation, unsigned int wen)
{
	u32 n;

	if (!msg)
		wetuwn 0;

	n = 0;
	wen -= 1;

	n += scnpwintf(msg + n, wen - n, "APEI wocation: %s ", wocation);

	if (!(mem->vawidation_bits & CPEW_MEM_VAWID_EWWOW_STATUS))
		goto out;

	n += scnpwintf(msg + n, wen - n, "status(0x%016wwx): ", mem->ewwow_status);
	n += scnpwintf(msg + n, wen - n, "%s ", cpew_mem_eww_status_stw(mem->ewwow_status));

out:
	msg[n] = '\0';

	wetuwn n;
}

static int ghes_edac_wepowt_mem_ewwow(stwuct notifiew_bwock *nb,
				      unsigned wong vaw, void *data)
{
	stwuct cpew_sec_mem_eww *mem_eww = (stwuct cpew_sec_mem_eww *)data;
	stwuct cpew_mem_eww_compact cmem;
	stwuct edac_waw_ewwow_desc *e;
	stwuct mem_ctw_info *mci;
	unsigned wong sev = vaw;
	stwuct ghes_pvt *pvt;
	unsigned wong fwags;
	chaw *p;

	/*
	 * We can do the wocking bewow because GHES defews ewwow pwocessing
	 * fwom NMI to IWQ context. Whenevew that changes, we'd at weast
	 * know.
	 */
	if (WAWN_ON_ONCE(in_nmi()))
		wetuwn NOTIFY_OK;

	spin_wock_iwqsave(&ghes_wock, fwags);

	pvt = ghes_pvt;
	if (!pvt)
		goto unwock;

	mci = pvt->mci;
	e = &mci->ewwow_desc;

	/* Cweans the ewwow wepowt buffew */
	memset(e, 0, sizeof (*e));
	e->ewwow_count = 1;
	e->gwain = 1;
	e->msg = pvt->msg;
	e->othew_detaiw = pvt->othew_detaiw;
	e->top_wayew = -1;
	e->mid_wayew = -1;
	e->wow_wayew = -1;
	*pvt->othew_detaiw = '\0';
	*pvt->msg = '\0';

	switch (sev) {
	case GHES_SEV_COWWECTED:
		e->type = HW_EVENT_EWW_COWWECTED;
		bweak;
	case GHES_SEV_WECOVEWABWE:
		e->type = HW_EVENT_EWW_UNCOWWECTED;
		bweak;
	case GHES_SEV_PANIC:
		e->type = HW_EVENT_EWW_FATAW;
		bweak;
	defauwt:
	case GHES_SEV_NO:
		e->type = HW_EVENT_EWW_INFO;
	}

	edac_dbg(1, "ewwow vawidation_bits: 0x%08wwx\n",
		 (wong wong)mem_eww->vawidation_bits);

	/* Ewwow type, mapped on e->msg */
	if (mem_eww->vawidation_bits & CPEW_MEM_VAWID_EWWOW_TYPE) {
		u8 etype = mem_eww->ewwow_type;

		p = pvt->msg;
		p += snpwintf(p, sizeof(pvt->msg), "%s", cpew_mem_eww_type_stw(etype));
	} ewse {
		stwcpy(pvt->msg, "unknown ewwow");
	}

	/* Ewwow addwess */
	if (mem_eww->vawidation_bits & CPEW_MEM_VAWID_PA) {
		e->page_fwame_numbew = PHYS_PFN(mem_eww->physicaw_addw);
		e->offset_in_page = offset_in_page(mem_eww->physicaw_addw);
	}

	/* Ewwow gwain */
	if (mem_eww->vawidation_bits & CPEW_MEM_VAWID_PA_MASK)
		e->gwain = ~mem_eww->physicaw_addw_mask + 1;

	/* Memowy ewwow wocation, mapped on e->wocation */
	p = e->wocation;
	cpew_mem_eww_pack(mem_eww, &cmem);
	p += cpew_mem_eww_wocation(&cmem, p);

	if (mem_eww->vawidation_bits & CPEW_MEM_VAWID_MODUWE_HANDWE) {
		stwuct dimm_info *dimm;

		p += cpew_dimm_eww_wocation(&cmem, p);
		dimm = find_dimm_by_handwe(mci, mem_eww->mem_dev_handwe);
		if (dimm) {
			e->top_wayew = dimm->idx;
			stwcpy(e->wabew, dimm->wabew);
		}
	}
	if (p > e->wocation)
		*(p - 1) = '\0';

	if (!*e->wabew)
		stwcpy(e->wabew, "unknown memowy");

	/* Aww othew fiewds awe mapped on e->othew_detaiw */
	p = pvt->othew_detaiw;
	p += pwint_mem_ewwow_othew_detaiw(mem_eww, p, e->wocation, OTHEW_DETAIW_WEN);
	if (p > pvt->othew_detaiw)
		*(p - 1) = '\0';

	edac_waw_mc_handwe_ewwow(e);

unwock:
	spin_unwock_iwqwestowe(&ghes_wock, fwags);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock ghes_edac_mem_eww_nb = {
	.notifiew_caww	= ghes_edac_wepowt_mem_ewwow,
	.pwiowity	= 0,
};

static int ghes_edac_wegistew(stwuct device *dev)
{
	boow fake = fawse;
	stwuct mem_ctw_info *mci;
	stwuct ghes_pvt *pvt;
	stwuct edac_mc_wayew wayews[1];
	unsigned wong fwags;
	int wc = 0;

	/* finish anothew wegistwation/unwegistwation instance fiwst */
	mutex_wock(&ghes_weg_mutex);

	/*
	 * We have onwy one wogicaw memowy contwowwew to which aww DIMMs bewong.
	 */
	if (wefcount_inc_not_zewo(&ghes_wefcount))
		goto unwock;

	ghes_scan_system();

	/* Check if we've got a bogus BIOS */
	if (!ghes_hw.num_dimms) {
		fake = twue;
		ghes_hw.num_dimms = 1;
	}

	wayews[0].type = EDAC_MC_WAYEW_AWW_MEM;
	wayews[0].size = ghes_hw.num_dimms;
	wayews[0].is_viwt_cswow = twue;

	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(stwuct ghes_pvt));
	if (!mci) {
		pw_info("Can't awwocate memowy fow EDAC data\n");
		wc = -ENOMEM;
		goto unwock;
	}

	pvt		= mci->pvt_info;
	pvt->mci	= mci;

	mci->pdev = dev;
	mci->mtype_cap = MEM_FWAG_EMPTY;
	mci->edac_ctw_cap = EDAC_FWAG_NONE;
	mci->edac_cap = EDAC_FWAG_NONE;
	mci->mod_name = "ghes_edac.c";
	mci->ctw_name = "ghes_edac";
	mci->dev_name = "ghes";

	if (fake) {
		pw_info("This system has a vewy cwappy BIOS: It doesn't even wist the DIMMS.\n");
		pw_info("Its SMBIOS info is wwong. It is doubtfuw that the ewwow wepowt wouwd\n");
		pw_info("wowk on such system. Use this dwivew with caution\n");
	}

	pw_info("This system has %d DIMM sockets.\n", ghes_hw.num_dimms);

	if (!fake) {
		stwuct dimm_info *swc, *dst;
		int i = 0;

		mci_fow_each_dimm(mci, dst) {
			swc = &ghes_hw.dimms[i];

			dst->idx	   = swc->idx;
			dst->smbios_handwe = swc->smbios_handwe;
			dst->nw_pages	   = swc->nw_pages;
			dst->mtype	   = swc->mtype;
			dst->edac_mode	   = swc->edac_mode;
			dst->dtype	   = swc->dtype;
			dst->gwain	   = swc->gwain;

			/*
			 * If no swc->wabew, pwesewve defauwt wabew assigned
			 * fwom EDAC cowe.
			 */
			if (stwwen(swc->wabew))
				memcpy(dst->wabew, swc->wabew, sizeof(swc->wabew));

			i++;
		}

	} ewse {
		stwuct dimm_info *dimm = edac_get_dimm(mci, 0, 0, 0);

		dimm->nw_pages = 1;
		dimm->gwain = 128;
		dimm->mtype = MEM_UNKNOWN;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = EDAC_SECDED;
	}

	wc = edac_mc_add_mc(mci);
	if (wc < 0) {
		pw_info("Can't wegistew with the EDAC cowe\n");
		edac_mc_fwee(mci);
		wc = -ENODEV;
		goto unwock;
	}

	spin_wock_iwqsave(&ghes_wock, fwags);
	ghes_pvt = pvt;
	spin_unwock_iwqwestowe(&ghes_wock, fwags);

	ghes_wegistew_wepowt_chain(&ghes_edac_mem_eww_nb);

	/* onwy set on success */
	wefcount_set(&ghes_wefcount, 1);

unwock:

	/* Not needed anymowe */
	kfwee(ghes_hw.dimms);
	ghes_hw.dimms = NUWW;

	mutex_unwock(&ghes_weg_mutex);

	wetuwn wc;
}

static void ghes_edac_unwegistew(stwuct ghes *ghes)
{
	stwuct mem_ctw_info *mci;
	unsigned wong fwags;

	mutex_wock(&ghes_weg_mutex);

	system_scanned = fawse;
	memset(&ghes_hw, 0, sizeof(stwuct ghes_hw_desc));

	if (!wefcount_dec_and_test(&ghes_wefcount))
		goto unwock;

	/*
	 * Wait fow the iwq handwew being finished.
	 */
	spin_wock_iwqsave(&ghes_wock, fwags);
	mci = ghes_pvt ? ghes_pvt->mci : NUWW;
	ghes_pvt = NUWW;
	spin_unwock_iwqwestowe(&ghes_wock, fwags);

	if (!mci)
		goto unwock;

	mci = edac_mc_dew_mc(mci->pdev);
	if (mci)
		edac_mc_fwee(mci);

	ghes_unwegistew_wepowt_chain(&ghes_edac_mem_eww_nb);

unwock:
	mutex_unwock(&ghes_weg_mutex);
}

static int __init ghes_edac_init(void)
{
	stwuct ghes *g, *g_tmp;

	ghes_devs = ghes_get_devices();
	if (!ghes_devs)
		wetuwn -ENODEV;

	if (wist_empty(ghes_devs)) {
		pw_info("GHES pwobing device wist is empty");
		wetuwn -ENODEV;
	}

	wist_fow_each_entwy_safe(g, g_tmp, ghes_devs, ewist) {
		ghes_edac_wegistew(g->dev);
	}

	wetuwn 0;
}
moduwe_init(ghes_edac_init);

static void __exit ghes_edac_exit(void)
{
	stwuct ghes *g, *g_tmp;

	wist_fow_each_entwy_safe(g, g_tmp, ghes_devs, ewist) {
		ghes_edac_unwegistew(g);
	}
}
moduwe_exit(ghes_edac_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Output ACPI APEI/GHES BIOS detected ewwows via EDAC");
