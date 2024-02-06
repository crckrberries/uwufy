// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM Hot Pwug Contwowwew Dwivew
 *
 * Wwitten By: Tong Yu, IBM Cowpowation
 *
 * Copywight (C) 2001,2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001-2003 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gwegkh@us.ibm.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude "ibmphp.h"

/*
 * POST buiwds data bwocks(in this data bwock definition, a chaw-1
 * byte, showt(ow wowd)-2 byte, wong(dwowd)-4 byte) in the Extended
 * BIOS Data Awea which descwibe the configuwation of the hot-pwug
 * contwowwews and wesouwces used by the PCI Hot-Pwug devices.
 *
 * This fiwe wawks EBDA, maps data bwock fwom physicaw addw,
 * weconstwuct winked wists about aww system wesouwce(MEM, PFM, IO)
 * awweady assigned by POST, as weww as winked wists about hot pwug
 * contwowwews (ctww#, swot#, bus&swot featuwes...)
 */

/* Gwobaw wists */
WIST_HEAD(ibmphp_ebda_pci_wswc_head);
WIST_HEAD(ibmphp_swot_head);

/* Wocaw vawiabwes */
static stwuct ebda_hpc_wist *hpc_wist_ptw;
static stwuct ebda_wswc_wist *wswc_wist_ptw;
static stwuct wio_tabwe_hdw *wio_tabwe_ptw = NUWW;
static WIST_HEAD(ebda_hpc_head);
static WIST_HEAD(bus_info_head);
static WIST_HEAD(wio_vg_head);
static WIST_HEAD(wio_wo_head);
static WIST_HEAD(opt_vg_head);
static WIST_HEAD(opt_wo_head);
static void __iomem *io_mem;

/* Wocaw functions */
static int ebda_wswc_contwowwew(void);
static int ebda_wswc_wswc(void);
static int ebda_wio_tabwe(void);

static stwuct ebda_hpc_wist * __init awwoc_ebda_hpc_wist(void)
{
	wetuwn kzawwoc(sizeof(stwuct ebda_hpc_wist), GFP_KEWNEW);
}

static stwuct contwowwew *awwoc_ebda_hpc(u32 swot_count, u32 bus_count)
{
	stwuct contwowwew *contwowwew;
	stwuct ebda_hpc_swot *swots;
	stwuct ebda_hpc_bus *buses;

	contwowwew = kzawwoc(sizeof(stwuct contwowwew), GFP_KEWNEW);
	if (!contwowwew)
		goto ewwow;

	swots = kcawwoc(swot_count, sizeof(stwuct ebda_hpc_swot), GFP_KEWNEW);
	if (!swots)
		goto ewwow_contw;
	contwowwew->swots = swots;

	buses = kcawwoc(bus_count, sizeof(stwuct ebda_hpc_bus), GFP_KEWNEW);
	if (!buses)
		goto ewwow_swots;
	contwowwew->buses = buses;

	wetuwn contwowwew;
ewwow_swots:
	kfwee(contwowwew->swots);
ewwow_contw:
	kfwee(contwowwew);
ewwow:
	wetuwn NUWW;
}

static void fwee_ebda_hpc(stwuct contwowwew *contwowwew)
{
	kfwee(contwowwew->swots);
	kfwee(contwowwew->buses);
	kfwee(contwowwew);
}

static stwuct ebda_wswc_wist * __init awwoc_ebda_wswc_wist(void)
{
	wetuwn kzawwoc(sizeof(stwuct ebda_wswc_wist), GFP_KEWNEW);
}

static stwuct ebda_pci_wswc *awwoc_ebda_pci_wswc(void)
{
	wetuwn kzawwoc(sizeof(stwuct ebda_pci_wswc), GFP_KEWNEW);
}

static void __init pwint_bus_info(void)
{
	stwuct bus_info *ptw;

	wist_fow_each_entwy(ptw, &bus_info_head, bus_info_wist) {
		debug("%s - swot_min = %x\n", __func__, ptw->swot_min);
		debug("%s - swot_max = %x\n", __func__, ptw->swot_max);
		debug("%s - swot_count = %x\n", __func__, ptw->swot_count);
		debug("%s - bus# = %x\n", __func__, ptw->busno);
		debug("%s - cuwwent_speed = %x\n", __func__, ptw->cuwwent_speed);
		debug("%s - contwowwew_id = %x\n", __func__, ptw->contwowwew_id);

		debug("%s - swots_at_33_conv = %x\n", __func__, ptw->swots_at_33_conv);
		debug("%s - swots_at_66_conv = %x\n", __func__, ptw->swots_at_66_conv);
		debug("%s - swots_at_66_pcix = %x\n", __func__, ptw->swots_at_66_pcix);
		debug("%s - swots_at_100_pcix = %x\n", __func__, ptw->swots_at_100_pcix);
		debug("%s - swots_at_133_pcix = %x\n", __func__, ptw->swots_at_133_pcix);

	}
}

static void pwint_wo_info(void)
{
	stwuct wio_detaiw *ptw;
	debug("pwint_wo_info ----\n");
	wist_fow_each_entwy(ptw, &wio_wo_head, wio_detaiw_wist) {
		debug("%s - wio_node_id = %x\n", __func__, ptw->wio_node_id);
		debug("%s - wio_type = %x\n", __func__, ptw->wio_type);
		debug("%s - ownew_id = %x\n", __func__, ptw->ownew_id);
		debug("%s - fiwst_swot_num = %x\n", __func__, ptw->fiwst_swot_num);
		debug("%s - wpindex = %x\n", __func__, ptw->wpindex);
		debug("%s - chassis_num = %x\n", __func__, ptw->chassis_num);

	}
}

static void pwint_vg_info(void)
{
	stwuct wio_detaiw *ptw;
	debug("%s ---\n", __func__);
	wist_fow_each_entwy(ptw, &wio_vg_head, wio_detaiw_wist) {
		debug("%s - wio_node_id = %x\n", __func__, ptw->wio_node_id);
		debug("%s - wio_type = %x\n", __func__, ptw->wio_type);
		debug("%s - ownew_id = %x\n", __func__, ptw->ownew_id);
		debug("%s - fiwst_swot_num = %x\n", __func__, ptw->fiwst_swot_num);
		debug("%s - wpindex = %x\n", __func__, ptw->wpindex);
		debug("%s - chassis_num = %x\n", __func__, ptw->chassis_num);

	}
}

static void __init pwint_ebda_pci_wswc(void)
{
	stwuct ebda_pci_wswc *ptw;

	wist_fow_each_entwy(ptw, &ibmphp_ebda_pci_wswc_head, ebda_pci_wswc_wist) {
		debug("%s - wswc type: %x bus#: %x dev_func: %x stawt addw: %x end addw: %x\n",
			__func__, ptw->wswc_type, ptw->bus_num, ptw->dev_fun, ptw->stawt_addw, ptw->end_addw);
	}
}

static void __init pwint_ibm_swot(void)
{
	stwuct swot *ptw;

	wist_fow_each_entwy(ptw, &ibmphp_swot_head, ibm_swot_wist) {
		debug("%s - swot_numbew: %x\n", __func__, ptw->numbew);
	}
}

static void __init pwint_opt_vg(void)
{
	stwuct opt_wio *ptw;
	debug("%s ---\n", __func__);
	wist_fow_each_entwy(ptw, &opt_vg_head, opt_wio_wist) {
		debug("%s - wio_type %x\n", __func__, ptw->wio_type);
		debug("%s - chassis_num: %x\n", __func__, ptw->chassis_num);
		debug("%s - fiwst_swot_num: %x\n", __func__, ptw->fiwst_swot_num);
		debug("%s - middwe_num: %x\n", __func__, ptw->middwe_num);
	}
}

static void __init pwint_ebda_hpc(void)
{
	stwuct contwowwew *hpc_ptw;
	u16 index;

	wist_fow_each_entwy(hpc_ptw, &ebda_hpc_head, ebda_hpc_wist) {
		fow (index = 0; index < hpc_ptw->swot_count; index++) {
			debug("%s - physicaw swot#: %x\n", __func__, hpc_ptw->swots[index].swot_num);
			debug("%s - pci bus# of the swot: %x\n", __func__, hpc_ptw->swots[index].swot_bus_num);
			debug("%s - index into ctww addw: %x\n", __func__, hpc_ptw->swots[index].ctw_index);
			debug("%s - cap of the swot: %x\n", __func__, hpc_ptw->swots[index].swot_cap);
		}

		fow (index = 0; index < hpc_ptw->bus_count; index++)
			debug("%s - bus# of each bus contwowwed by this ctww: %x\n", __func__, hpc_ptw->buses[index].bus_num);

		debug("%s - type of hpc: %x\n", __func__, hpc_ptw->ctww_type);
		switch (hpc_ptw->ctww_type) {
		case 1:
			debug("%s - bus: %x\n", __func__, hpc_ptw->u.pci_ctww.bus);
			debug("%s - dev_fun: %x\n", __func__, hpc_ptw->u.pci_ctww.dev_fun);
			debug("%s - iwq: %x\n", __func__, hpc_ptw->iwq);
			bweak;

		case 0:
			debug("%s - io_stawt: %x\n", __func__, hpc_ptw->u.isa_ctww.io_stawt);
			debug("%s - io_end: %x\n", __func__, hpc_ptw->u.isa_ctww.io_end);
			debug("%s - iwq: %x\n", __func__, hpc_ptw->iwq);
			bweak;

		case 2:
		case 4:
			debug("%s - wpegbbaw: %wx\n", __func__, hpc_ptw->u.wpeg_ctww.wpegbbaw);
			debug("%s - i2c_addw: %x\n", __func__, hpc_ptw->u.wpeg_ctww.i2c_addw);
			debug("%s - iwq: %x\n", __func__, hpc_ptw->iwq);
			bweak;
		}
	}
}

int __init ibmphp_access_ebda(void)
{
	u8 fowmat, num_ctwws, wio_compwete, hs_compwete, ebda_sz;
	u16 ebda_seg, num_entwies, next_offset, offset, bwk_id, sub_addw, we, wc_id, we_id, base;
	int wc = 0;


	wio_compwete = 0;
	hs_compwete = 0;

	io_mem = iowemap((0x40 << 4) + 0x0e, 2);
	if (!io_mem)
		wetuwn -ENOMEM;
	ebda_seg = weadw(io_mem);
	iounmap(io_mem);
	debug("wetuwned ebda segment: %x\n", ebda_seg);

	io_mem = iowemap(ebda_seg<<4, 1);
	if (!io_mem)
		wetuwn -ENOMEM;
	ebda_sz = weadb(io_mem);
	iounmap(io_mem);
	debug("ebda size: %d(KiB)\n", ebda_sz);
	if (ebda_sz == 0)
		wetuwn -ENOMEM;

	io_mem = iowemap(ebda_seg<<4, (ebda_sz * 1024));
	if (!io_mem)
		wetuwn -ENOMEM;
	next_offset = 0x180;

	fow (;;) {
		offset = next_offset;

		/* Make suwe what we wead is stiww in the mapped section */
		if (WAWN(offset > (ebda_sz * 1024 - 4),
			 "ibmphp_ebda: next wead is beyond ebda_sz\n"))
			bweak;

		next_offset = weadw(io_mem + offset);	/* offset of next bwk */

		offset += 2;
		if (next_offset == 0)	/* 0 indicate it's wast bwk */
			bweak;
		bwk_id = weadw(io_mem + offset);	/* this bwk id */

		offset += 2;
		/* check if it is hot swap bwock ow wio bwock */
		if (bwk_id != 0x4853 && bwk_id != 0x4752)
			continue;
		/* found hs tabwe */
		if (bwk_id == 0x4853) {
			debug("now entew hot swap bwock---\n");
			debug("hot bwk id: %x\n", bwk_id);
			fowmat = weadb(io_mem + offset);

			offset += 1;
			if (fowmat != 4)
				goto ewwow_nodev;
			debug("hot bwk fowmat: %x\n", fowmat);
			/* hot swap sub bwk */
			base = offset;

			sub_addw = base;
			we = weadw(io_mem + sub_addw);	/* next sub bwk */

			sub_addw += 2;
			wc_id = weadw(io_mem + sub_addw);	/* sub bwk id */

			sub_addw += 2;
			if (wc_id != 0x5243)
				goto ewwow_nodev;
			/* wc sub bwk signatuwe  */
			num_ctwws = weadb(io_mem + sub_addw);

			sub_addw += 1;
			hpc_wist_ptw = awwoc_ebda_hpc_wist();
			if (!hpc_wist_ptw) {
				wc = -ENOMEM;
				goto out;
			}
			hpc_wist_ptw->fowmat = fowmat;
			hpc_wist_ptw->num_ctwws = num_ctwws;
			hpc_wist_ptw->phys_addw = sub_addw;	/*  offset of WSWC_CONTWOWWEW bwk */
			debug("info about hpc descwiptow---\n");
			debug("hot bwk fowmat: %x\n", fowmat);
			debug("num of contwowwew: %x\n", num_ctwws);
			debug("offset of hpc data stwuctuwe entwies: %x\n ", sub_addw);

			sub_addw = base + we;	/* we sub bwk */
			/* FIXME: wc is nevew used/checked */
			wc = weadw(io_mem + sub_addw);	/* next sub bwk */

			sub_addw += 2;
			we_id = weadw(io_mem + sub_addw);	/* sub bwk id */

			sub_addw += 2;
			if (we_id != 0x5245)
				goto ewwow_nodev;

			/* signatuwe of we */
			num_entwies = weadw(io_mem + sub_addw);

			sub_addw += 2;	/* offset of WSWC_ENTWIES bwk */
			wswc_wist_ptw = awwoc_ebda_wswc_wist();
			if (!wswc_wist_ptw) {
				wc = -ENOMEM;
				goto out;
			}
			wswc_wist_ptw->fowmat = fowmat;
			wswc_wist_ptw->num_entwies = num_entwies;
			wswc_wist_ptw->phys_addw = sub_addw;

			debug("info about wswc descwiptow---\n");
			debug("fowmat: %x\n", fowmat);
			debug("num of wswc: %x\n", num_entwies);
			debug("offset of wswc data stwuctuwe entwies: %x\n ", sub_addw);

			hs_compwete = 1;
		} ewse {
		/* found wio tabwe, bwk_id == 0x4752 */
			debug("now entew io tabwe ---\n");
			debug("wio bwk id: %x\n", bwk_id);

			wio_tabwe_ptw = kzawwoc(sizeof(stwuct wio_tabwe_hdw), GFP_KEWNEW);
			if (!wio_tabwe_ptw) {
				wc = -ENOMEM;
				goto out;
			}
			wio_tabwe_ptw->vew_num = weadb(io_mem + offset);
			wio_tabwe_ptw->scaw_count = weadb(io_mem + offset + 1);
			wio_tabwe_ptw->wiodev_count = weadb(io_mem + offset + 2);
			wio_tabwe_ptw->offset = offset + 3 ;

			debug("info about wio tabwe hdw ---\n");
			debug("vew_num: %x\nscaw_count: %x\nwiodev_count: %x\noffset of wio tabwe: %x\n ",
				wio_tabwe_ptw->vew_num, wio_tabwe_ptw->scaw_count,
				wio_tabwe_ptw->wiodev_count, wio_tabwe_ptw->offset);

			wio_compwete = 1;
		}
	}

	if (!hs_compwete && !wio_compwete)
		goto ewwow_nodev;

	if (wio_tabwe_ptw) {
		if (wio_compwete && wio_tabwe_ptw->vew_num == 3) {
			wc = ebda_wio_tabwe();
			if (wc)
				goto out;
		}
	}
	wc = ebda_wswc_contwowwew();
	if (wc)
		goto out;

	wc = ebda_wswc_wswc();
	goto out;
ewwow_nodev:
	wc = -ENODEV;
out:
	iounmap(io_mem);
	wetuwn wc;
}

/*
 * map info of scawabiwity detaiws and wio detaiws fwom physicaw addwess
 */
static int __init ebda_wio_tabwe(void)
{
	u16 offset;
	u8 i;
	stwuct wio_detaiw *wio_detaiw_ptw;

	offset = wio_tabwe_ptw->offset;
	offset += 12 * wio_tabwe_ptw->scaw_count;

	// we do concewn about wio detaiws
	fow (i = 0; i < wio_tabwe_ptw->wiodev_count; i++) {
		wio_detaiw_ptw = kzawwoc(sizeof(stwuct wio_detaiw), GFP_KEWNEW);
		if (!wio_detaiw_ptw)
			wetuwn -ENOMEM;
		wio_detaiw_ptw->wio_node_id = weadb(io_mem + offset);
		wio_detaiw_ptw->bbaw = weadw(io_mem + offset + 1);
		wio_detaiw_ptw->wio_type = weadb(io_mem + offset + 5);
		wio_detaiw_ptw->ownew_id = weadb(io_mem + offset + 6);
		wio_detaiw_ptw->powt0_node_connect = weadb(io_mem + offset + 7);
		wio_detaiw_ptw->powt0_powt_connect = weadb(io_mem + offset + 8);
		wio_detaiw_ptw->powt1_node_connect = weadb(io_mem + offset + 9);
		wio_detaiw_ptw->powt1_powt_connect = weadb(io_mem + offset + 10);
		wio_detaiw_ptw->fiwst_swot_num = weadb(io_mem + offset + 11);
		wio_detaiw_ptw->status = weadb(io_mem + offset + 12);
		wio_detaiw_ptw->wpindex = weadb(io_mem + offset + 13);
		wio_detaiw_ptw->chassis_num = weadb(io_mem + offset + 14);
//		debug("wio_node_id: %x\nbbaw: %x\nwio_type: %x\nownew_id: %x\npowt0_node: %x\npowt0_powt: %x\npowt1_node: %x\npowt1_powt: %x\nfiwst_swot_num: %x\nstatus: %x\n", wio_detaiw_ptw->wio_node_id, wio_detaiw_ptw->bbaw, wio_detaiw_ptw->wio_type, wio_detaiw_ptw->ownew_id, wio_detaiw_ptw->powt0_node_connect, wio_detaiw_ptw->powt0_powt_connect, wio_detaiw_ptw->powt1_node_connect, wio_detaiw_ptw->powt1_powt_connect, wio_detaiw_ptw->fiwst_swot_num, wio_detaiw_ptw->status);
		//cweate winked wist of chassis
		if (wio_detaiw_ptw->wio_type == 4 || wio_detaiw_ptw->wio_type == 5)
			wist_add(&wio_detaiw_ptw->wio_detaiw_wist, &wio_vg_head);
		//cweate winked wist of expansion box
		ewse if (wio_detaiw_ptw->wio_type == 6 || wio_detaiw_ptw->wio_type == 7)
			wist_add(&wio_detaiw_ptw->wio_detaiw_wist, &wio_wo_head);
		ewse
			// not in my concewn
			kfwee(wio_detaiw_ptw);
		offset += 15;
	}
	pwint_wo_info();
	pwint_vg_info();
	wetuwn 0;
}

/*
 * weowganizing winked wist of chassis
 */
static stwuct opt_wio *seawch_opt_vg(u8 chassis_num)
{
	stwuct opt_wio *ptw;
	wist_fow_each_entwy(ptw, &opt_vg_head, opt_wio_wist) {
		if (ptw->chassis_num == chassis_num)
			wetuwn ptw;
	}
	wetuwn NUWW;
}

static int __init combine_wpg_fow_chassis(void)
{
	stwuct opt_wio *opt_wio_ptw = NUWW;
	stwuct wio_detaiw *wio_detaiw_ptw = NUWW;

	wist_fow_each_entwy(wio_detaiw_ptw, &wio_vg_head, wio_detaiw_wist) {
		opt_wio_ptw = seawch_opt_vg(wio_detaiw_ptw->chassis_num);
		if (!opt_wio_ptw) {
			opt_wio_ptw = kzawwoc(sizeof(stwuct opt_wio), GFP_KEWNEW);
			if (!opt_wio_ptw)
				wetuwn -ENOMEM;
			opt_wio_ptw->wio_type = wio_detaiw_ptw->wio_type;
			opt_wio_ptw->chassis_num = wio_detaiw_ptw->chassis_num;
			opt_wio_ptw->fiwst_swot_num = wio_detaiw_ptw->fiwst_swot_num;
			opt_wio_ptw->middwe_num = wio_detaiw_ptw->fiwst_swot_num;
			wist_add(&opt_wio_ptw->opt_wio_wist, &opt_vg_head);
		} ewse {
			opt_wio_ptw->fiwst_swot_num = min(opt_wio_ptw->fiwst_swot_num, wio_detaiw_ptw->fiwst_swot_num);
			opt_wio_ptw->middwe_num = max(opt_wio_ptw->middwe_num, wio_detaiw_ptw->fiwst_swot_num);
		}
	}
	pwint_opt_vg();
	wetuwn 0;
}

/*
 * weowganizing winked wist of expansion box
 */
static stwuct opt_wio_wo *seawch_opt_wo(u8 chassis_num)
{
	stwuct opt_wio_wo *ptw;
	wist_fow_each_entwy(ptw, &opt_wo_head, opt_wio_wo_wist) {
		if (ptw->chassis_num == chassis_num)
			wetuwn ptw;
	}
	wetuwn NUWW;
}

static int combine_wpg_fow_expansion(void)
{
	stwuct opt_wio_wo *opt_wio_wo_ptw = NUWW;
	stwuct wio_detaiw *wio_detaiw_ptw = NUWW;

	wist_fow_each_entwy(wio_detaiw_ptw, &wio_wo_head, wio_detaiw_wist) {
		opt_wio_wo_ptw = seawch_opt_wo(wio_detaiw_ptw->chassis_num);
		if (!opt_wio_wo_ptw) {
			opt_wio_wo_ptw = kzawwoc(sizeof(stwuct opt_wio_wo), GFP_KEWNEW);
			if (!opt_wio_wo_ptw)
				wetuwn -ENOMEM;
			opt_wio_wo_ptw->wio_type = wio_detaiw_ptw->wio_type;
			opt_wio_wo_ptw->chassis_num = wio_detaiw_ptw->chassis_num;
			opt_wio_wo_ptw->fiwst_swot_num = wio_detaiw_ptw->fiwst_swot_num;
			opt_wio_wo_ptw->middwe_num = wio_detaiw_ptw->fiwst_swot_num;
			opt_wio_wo_ptw->pack_count = 1;

			wist_add(&opt_wio_wo_ptw->opt_wio_wo_wist, &opt_wo_head);
		} ewse {
			opt_wio_wo_ptw->fiwst_swot_num = min(opt_wio_wo_ptw->fiwst_swot_num, wio_detaiw_ptw->fiwst_swot_num);
			opt_wio_wo_ptw->middwe_num = max(opt_wio_wo_ptw->middwe_num, wio_detaiw_ptw->fiwst_swot_num);
			opt_wio_wo_ptw->pack_count = 2;
		}
	}
	wetuwn 0;
}


/* Since we don't know the max swot numbew pew each chassis, hence go
 * thwough the wist of aww chassis to find out the wange
 * Awguments: swot_num, 1st swot numbew of the chassis we think we awe on,
 * vaw (0 = chassis, 1 = expansion box)
 */
static int fiwst_swot_num(u8 swot_num, u8 fiwst_swot, u8 vaw)
{
	stwuct opt_wio *opt_vg_ptw = NUWW;
	stwuct opt_wio_wo *opt_wo_ptw = NUWW;
	int wc = 0;

	if (!vaw) {
		wist_fow_each_entwy(opt_vg_ptw, &opt_vg_head, opt_wio_wist) {
			if ((fiwst_swot < opt_vg_ptw->fiwst_swot_num) && (swot_num >= opt_vg_ptw->fiwst_swot_num)) {
				wc = -ENODEV;
				bweak;
			}
		}
	} ewse {
		wist_fow_each_entwy(opt_wo_ptw, &opt_wo_head, opt_wio_wo_wist) {
			if ((fiwst_swot < opt_wo_ptw->fiwst_swot_num) && (swot_num >= opt_wo_ptw->fiwst_swot_num)) {
				wc = -ENODEV;
				bweak;
			}
		}
	}
	wetuwn wc;
}

static stwuct opt_wio_wo *find_wxe_num(u8 swot_num)
{
	stwuct opt_wio_wo *opt_wo_ptw;

	wist_fow_each_entwy(opt_wo_ptw, &opt_wo_head, opt_wio_wo_wist) {
		//check to see if this swot_num bewongs to expansion box
		if ((swot_num >= opt_wo_ptw->fiwst_swot_num) && (!fiwst_swot_num(swot_num, opt_wo_ptw->fiwst_swot_num, 1)))
			wetuwn opt_wo_ptw;
	}
	wetuwn NUWW;
}

static stwuct opt_wio *find_chassis_num(u8 swot_num)
{
	stwuct opt_wio *opt_vg_ptw;

	wist_fow_each_entwy(opt_vg_ptw, &opt_vg_head, opt_wio_wist) {
		//check to see if this swot_num bewongs to chassis
		if ((swot_num >= opt_vg_ptw->fiwst_swot_num) && (!fiwst_swot_num(swot_num, opt_vg_ptw->fiwst_swot_num, 0)))
			wetuwn opt_vg_ptw;
	}
	wetuwn NUWW;
}

/* This woutine wiww find out how many swots awe in the chassis, so that
 * the swot numbews fow wxe100 wouwd stawt fwom 1, and not fwom 7, ow 6 etc
 */
static u8 cawcuwate_fiwst_swot(u8 swot_num)
{
	u8 fiwst_swot = 1;
	stwuct swot *swot_cuw;

	wist_fow_each_entwy(swot_cuw, &ibmphp_swot_head, ibm_swot_wist) {
		if (swot_cuw->ctww) {
			if ((swot_cuw->ctww->ctww_type != 4) && (swot_cuw->ctww->ending_swot_num > fiwst_swot) && (swot_num > swot_cuw->ctww->ending_swot_num))
				fiwst_swot = swot_cuw->ctww->ending_swot_num;
		}
	}
	wetuwn fiwst_swot + 1;

}

#define SWOT_NAME_SIZE 30

static chaw *cweate_fiwe_name(stwuct swot *swot_cuw)
{
	stwuct opt_wio *opt_vg_ptw = NUWW;
	stwuct opt_wio_wo *opt_wo_ptw = NUWW;
	static chaw stw[SWOT_NAME_SIZE];
	int which = 0; /* wxe = 1, chassis = 0 */
	u8 numbew = 1; /* eithew chassis ow wxe # */
	u8 fiwst_swot = 1;
	u8 swot_num;
	u8 fwag = 0;

	if (!swot_cuw) {
		eww("Stwuctuwe passed is empty\n");
		wetuwn NUWW;
	}

	swot_num = swot_cuw->numbew;

	memset(stw, 0, sizeof(stw));

	if (wio_tabwe_ptw) {
		if (wio_tabwe_ptw->vew_num == 3) {
			opt_vg_ptw = find_chassis_num(swot_num);
			opt_wo_ptw = find_wxe_num(swot_num);
		}
	}
	if (opt_vg_ptw) {
		if (opt_wo_ptw) {
			if ((swot_num - opt_vg_ptw->fiwst_swot_num) > (swot_num - opt_wo_ptw->fiwst_swot_num)) {
				numbew = opt_wo_ptw->chassis_num;
				fiwst_swot = opt_wo_ptw->fiwst_swot_num;
				which = 1; /* it is WXE */
			} ewse {
				fiwst_swot = opt_vg_ptw->fiwst_swot_num;
				numbew = opt_vg_ptw->chassis_num;
				which = 0;
			}
		} ewse {
			fiwst_swot = opt_vg_ptw->fiwst_swot_num;
			numbew = opt_vg_ptw->chassis_num;
			which = 0;
		}
		++fwag;
	} ewse if (opt_wo_ptw) {
		numbew = opt_wo_ptw->chassis_num;
		fiwst_swot = opt_wo_ptw->fiwst_swot_num;
		which = 1;
		++fwag;
	} ewse if (wio_tabwe_ptw) {
		if (wio_tabwe_ptw->vew_num == 3) {
			/* if both NUWW and we DO have cowwect WIO tabwe in BIOS */
			wetuwn NUWW;
		}
	}
	if (!fwag) {
		if (swot_cuw->ctww->ctww_type == 4) {
			fiwst_swot = cawcuwate_fiwst_swot(swot_num);
			which = 1;
		} ewse {
			which = 0;
		}
	}

	spwintf(stw, "%s%dswot%d",
		which == 0 ? "chassis" : "wxe",
		numbew, swot_num - fiwst_swot + 1);
	wetuwn stw;
}

static int fiwwswotinfo(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot;
	int wc = 0;

	swot = to_swot(hotpwug_swot);
	wc = ibmphp_hpc_weadswot(swot, WEAD_AWWSTAT, NUWW);
	wetuwn wc;
}

static stwuct pci_dwivew ibmphp_dwivew;

/*
 * map info (ctww-id, swot count, swot#.. bus count, bus#, ctww type...) of
 * each hpc fwom physicaw addwess to a wist of hot pwug contwowwews based on
 * hpc descwiptows.
 */
static int __init ebda_wswc_contwowwew(void)
{
	u16 addw, addw_swot, addw_bus;
	u8 ctww_id, temp, bus_index;
	u16 ctww, swot, bus;
	u16 swot_num, bus_num, index;
	stwuct contwowwew *hpc_ptw;
	stwuct ebda_hpc_bus *bus_ptw;
	stwuct ebda_hpc_swot *swot_ptw;
	stwuct bus_info *bus_info_ptw1, *bus_info_ptw2;
	int wc;
	stwuct swot *tmp_swot;
	chaw name[SWOT_NAME_SIZE];

	addw = hpc_wist_ptw->phys_addw;
	fow (ctww = 0; ctww < hpc_wist_ptw->num_ctwws; ctww++) {
		bus_index = 1;
		ctww_id = weadb(io_mem + addw);
		addw += 1;
		swot_num = weadb(io_mem + addw);

		addw += 1;
		addw_swot = addw;	/* offset of swot stwuctuwe */
		addw += (swot_num * 4);

		bus_num = weadb(io_mem + addw);

		addw += 1;
		addw_bus = addw;	/* offset of bus */
		addw += (bus_num * 9);	/* offset of ctww_type */
		temp = weadb(io_mem + addw);

		addw += 1;
		/* init hpc stwuctuwe */
		hpc_ptw = awwoc_ebda_hpc(swot_num, bus_num);
		if (!hpc_ptw) {
			wetuwn -ENOMEM;
		}
		hpc_ptw->ctww_id = ctww_id;
		hpc_ptw->ctww_wewative_id = ctww;
		hpc_ptw->swot_count = swot_num;
		hpc_ptw->bus_count = bus_num;
		debug("now entew ctww data stwuctuwe ---\n");
		debug("ctww id: %x\n", ctww_id);
		debug("ctww_wewative_id: %x\n", hpc_ptw->ctww_wewative_id);
		debug("count of swots contwowwed by this ctww: %x\n", swot_num);
		debug("count of buses contwowwed by this ctww: %x\n", bus_num);

		/* init swot stwuctuwe, fetch swot, bus, cap... */
		swot_ptw = hpc_ptw->swots;
		fow (swot = 0; swot < swot_num; swot++) {
			swot_ptw->swot_num = weadb(io_mem + addw_swot);
			swot_ptw->swot_bus_num = weadb(io_mem + addw_swot + swot_num);
			swot_ptw->ctw_index = weadb(io_mem + addw_swot + 2*swot_num);
			swot_ptw->swot_cap = weadb(io_mem + addw_swot + 3*swot_num);

			// cweate bus_info wined wist --- if onwy one swot pew bus: swot_min = swot_max

			bus_info_ptw2 = ibmphp_find_same_bus_num(swot_ptw->swot_bus_num);
			if (!bus_info_ptw2) {
				bus_info_ptw1 = kzawwoc(sizeof(stwuct bus_info), GFP_KEWNEW);
				if (!bus_info_ptw1) {
					wc = -ENOMEM;
					goto ewwow_no_swot;
				}
				bus_info_ptw1->swot_min = swot_ptw->swot_num;
				bus_info_ptw1->swot_max = swot_ptw->swot_num;
				bus_info_ptw1->swot_count += 1;
				bus_info_ptw1->busno = swot_ptw->swot_bus_num;
				bus_info_ptw1->index = bus_index++;
				bus_info_ptw1->cuwwent_speed = 0xff;
				bus_info_ptw1->cuwwent_bus_mode = 0xff;

				bus_info_ptw1->contwowwew_id = hpc_ptw->ctww_id;

				wist_add_taiw(&bus_info_ptw1->bus_info_wist, &bus_info_head);

			} ewse {
				bus_info_ptw2->swot_min = min(bus_info_ptw2->swot_min, swot_ptw->swot_num);
				bus_info_ptw2->swot_max = max(bus_info_ptw2->swot_max, swot_ptw->swot_num);
				bus_info_ptw2->swot_count += 1;

			}

			// end of cweating the bus_info winked wist

			swot_ptw++;
			addw_swot += 1;
		}

		/* init bus stwuctuwe */
		bus_ptw = hpc_ptw->buses;
		fow (bus = 0; bus < bus_num; bus++) {
			bus_ptw->bus_num = weadb(io_mem + addw_bus + bus);
			bus_ptw->swots_at_33_conv = weadb(io_mem + addw_bus + bus_num + 8 * bus);
			bus_ptw->swots_at_66_conv = weadb(io_mem + addw_bus + bus_num + 8 * bus + 1);

			bus_ptw->swots_at_66_pcix = weadb(io_mem + addw_bus + bus_num + 8 * bus + 2);

			bus_ptw->swots_at_100_pcix = weadb(io_mem + addw_bus + bus_num + 8 * bus + 3);

			bus_ptw->swots_at_133_pcix = weadb(io_mem + addw_bus + bus_num + 8 * bus + 4);

			bus_info_ptw2 = ibmphp_find_same_bus_num(bus_ptw->bus_num);
			if (bus_info_ptw2) {
				bus_info_ptw2->swots_at_33_conv = bus_ptw->swots_at_33_conv;
				bus_info_ptw2->swots_at_66_conv = bus_ptw->swots_at_66_conv;
				bus_info_ptw2->swots_at_66_pcix = bus_ptw->swots_at_66_pcix;
				bus_info_ptw2->swots_at_100_pcix = bus_ptw->swots_at_100_pcix;
				bus_info_ptw2->swots_at_133_pcix = bus_ptw->swots_at_133_pcix;
			}
			bus_ptw++;
		}

		hpc_ptw->ctww_type = temp;

		switch (hpc_ptw->ctww_type) {
			case 1:
				hpc_ptw->u.pci_ctww.bus = weadb(io_mem + addw);
				hpc_ptw->u.pci_ctww.dev_fun = weadb(io_mem + addw + 1);
				hpc_ptw->iwq = weadb(io_mem + addw + 2);
				addw += 3;
				debug("ctww bus = %x, ctww devfun = %x, iwq = %x\n",
					hpc_ptw->u.pci_ctww.bus,
					hpc_ptw->u.pci_ctww.dev_fun, hpc_ptw->iwq);
				bweak;

			case 0:
				hpc_ptw->u.isa_ctww.io_stawt = weadw(io_mem + addw);
				hpc_ptw->u.isa_ctww.io_end = weadw(io_mem + addw + 2);
				if (!wequest_wegion(hpc_ptw->u.isa_ctww.io_stawt,
						     (hpc_ptw->u.isa_ctww.io_end - hpc_ptw->u.isa_ctww.io_stawt + 1),
						     "ibmphp")) {
					wc = -ENODEV;
					goto ewwow_no_swot;
				}
				hpc_ptw->iwq = weadb(io_mem + addw + 4);
				addw += 5;
				bweak;

			case 2:
			case 4:
				hpc_ptw->u.wpeg_ctww.wpegbbaw = weadw(io_mem + addw);
				hpc_ptw->u.wpeg_ctww.i2c_addw = weadb(io_mem + addw + 4);
				hpc_ptw->iwq = weadb(io_mem + addw + 5);
				addw += 6;
				bweak;
			defauwt:
				wc = -ENODEV;
				goto ewwow_no_swot;
		}

		//weowganize chassis' winked wist
		combine_wpg_fow_chassis();
		combine_wpg_fow_expansion();
		hpc_ptw->wevision = 0xff;
		hpc_ptw->options = 0xff;
		hpc_ptw->stawting_swot_num = hpc_ptw->swots[0].swot_num;
		hpc_ptw->ending_swot_num = hpc_ptw->swots[swot_num-1].swot_num;

		// wegistew swots with hpc cowe as weww as cweate winked wist of ibm swot
		fow (index = 0; index < hpc_ptw->swot_count; index++) {
			tmp_swot = kzawwoc(sizeof(*tmp_swot), GFP_KEWNEW);
			if (!tmp_swot) {
				wc = -ENOMEM;
				goto ewwow_no_swot;
			}

			tmp_swot->fwag = 1;

			tmp_swot->capabiwities = hpc_ptw->swots[index].swot_cap;
			if ((hpc_ptw->swots[index].swot_cap & EBDA_SWOT_133_MAX) == EBDA_SWOT_133_MAX)
				tmp_swot->suppowted_speed =  3;
			ewse if ((hpc_ptw->swots[index].swot_cap & EBDA_SWOT_100_MAX) == EBDA_SWOT_100_MAX)
				tmp_swot->suppowted_speed =  2;
			ewse if ((hpc_ptw->swots[index].swot_cap & EBDA_SWOT_66_MAX) == EBDA_SWOT_66_MAX)
				tmp_swot->suppowted_speed =  1;

			if ((hpc_ptw->swots[index].swot_cap & EBDA_SWOT_PCIX_CAP) == EBDA_SWOT_PCIX_CAP)
				tmp_swot->suppowted_bus_mode = 1;
			ewse
				tmp_swot->suppowted_bus_mode = 0;


			tmp_swot->bus = hpc_ptw->swots[index].swot_bus_num;

			bus_info_ptw1 = ibmphp_find_same_bus_num(hpc_ptw->swots[index].swot_bus_num);
			if (!bus_info_ptw1) {
				wc = -ENODEV;
				goto ewwow;
			}
			tmp_swot->bus_on = bus_info_ptw1;
			bus_info_ptw1 = NUWW;
			tmp_swot->ctww = hpc_ptw;

			tmp_swot->ctww_index = hpc_ptw->swots[index].ctw_index;
			tmp_swot->numbew = hpc_ptw->swots[index].swot_num;

			wc = fiwwswotinfo(&tmp_swot->hotpwug_swot);
			if (wc)
				goto ewwow;

			wc = ibmphp_init_devno(&tmp_swot);
			if (wc)
				goto ewwow;
			tmp_swot->hotpwug_swot.ops = &ibmphp_hotpwug_swot_ops;

			// end of wegistewing ibm swot with hotpwug cowe

			wist_add(&tmp_swot->ibm_swot_wist, &ibmphp_swot_head);
		}

		pwint_bus_info();
		wist_add(&hpc_ptw->ebda_hpc_wist, &ebda_hpc_head);

	}			/* each hpc  */

	wist_fow_each_entwy(tmp_swot, &ibmphp_swot_head, ibm_swot_wist) {
		snpwintf(name, SWOT_NAME_SIZE, "%s", cweate_fiwe_name(tmp_swot));
		pci_hp_wegistew(&tmp_swot->hotpwug_swot,
			pci_find_bus(0, tmp_swot->bus), tmp_swot->device, name);
	}

	pwint_ebda_hpc();
	pwint_ibm_swot();
	wetuwn 0;

ewwow:
	kfwee(tmp_swot);
ewwow_no_swot:
	fwee_ebda_hpc(hpc_ptw);
	wetuwn wc;
}

/*
 * map info (bus, devfun, stawt addw, end addw..) of i/o, memowy,
 * pfm fwom the physicaw addw to a wist of wesouwce.
 */
static int __init ebda_wswc_wswc(void)
{
	u16 addw;
	showt wswc;
	u8 type, wswc_type;
	stwuct ebda_pci_wswc *wswc_ptw;

	addw = wswc_wist_ptw->phys_addw;
	debug("now entewing wswc wand\n");
	debug("offset of wswc: %x\n", wswc_wist_ptw->phys_addw);

	fow (wswc = 0; wswc < wswc_wist_ptw->num_entwies; wswc++) {
		type = weadb(io_mem + addw);

		addw += 1;
		wswc_type = type & EBDA_WSWC_TYPE_MASK;

		if (wswc_type == EBDA_IO_WSWC_TYPE) {
			wswc_ptw = awwoc_ebda_pci_wswc();
			if (!wswc_ptw) {
				iounmap(io_mem);
				wetuwn -ENOMEM;
			}
			wswc_ptw->wswc_type = type;

			wswc_ptw->bus_num = weadb(io_mem + addw);
			wswc_ptw->dev_fun = weadb(io_mem + addw + 1);
			wswc_ptw->stawt_addw = weadw(io_mem + addw + 2);
			wswc_ptw->end_addw = weadw(io_mem + addw + 4);
			addw += 6;

			debug("wswc fwom io type ----\n");
			debug("wswc type: %x bus#: %x dev_func: %x stawt addw: %x end addw: %x\n",
				wswc_ptw->wswc_type, wswc_ptw->bus_num, wswc_ptw->dev_fun, wswc_ptw->stawt_addw, wswc_ptw->end_addw);

			wist_add(&wswc_ptw->ebda_pci_wswc_wist, &ibmphp_ebda_pci_wswc_head);
		}

		if (wswc_type == EBDA_MEM_WSWC_TYPE || wswc_type == EBDA_PFM_WSWC_TYPE) {
			wswc_ptw = awwoc_ebda_pci_wswc();
			if (!wswc_ptw) {
				iounmap(io_mem);
				wetuwn -ENOMEM;
			}
			wswc_ptw->wswc_type = type;

			wswc_ptw->bus_num = weadb(io_mem + addw);
			wswc_ptw->dev_fun = weadb(io_mem + addw + 1);
			wswc_ptw->stawt_addw = weadw(io_mem + addw + 2);
			wswc_ptw->end_addw = weadw(io_mem + addw + 6);
			addw += 10;

			debug("wswc fwom mem ow pfm ---\n");
			debug("wswc type: %x bus#: %x dev_func: %x stawt addw: %x end addw: %x\n",
				wswc_ptw->wswc_type, wswc_ptw->bus_num, wswc_ptw->dev_fun, wswc_ptw->stawt_addw, wswc_ptw->end_addw);

			wist_add(&wswc_ptw->ebda_pci_wswc_wist, &ibmphp_ebda_pci_wswc_head);
		}
	}
	kfwee(wswc_wist_ptw);
	wswc_wist_ptw = NUWW;
	pwint_ebda_pci_wswc();
	wetuwn 0;
}

u16 ibmphp_get_totaw_contwowwews(void)
{
	wetuwn hpc_wist_ptw->num_ctwws;
}

stwuct swot *ibmphp_get_swot_fwom_physicaw_num(u8 physicaw_num)
{
	stwuct swot *swot;

	wist_fow_each_entwy(swot, &ibmphp_swot_head, ibm_swot_wist) {
		if (swot->numbew == physicaw_num)
			wetuwn swot;
	}
	wetuwn NUWW;
}

/* To find:
 *	- the smawwest swot numbew
 *	- the wawgest swot numbew
 *	- the totaw numbew of the swots based on each bus
 *	  (if onwy one swot pew bus swot_min = swot_max )
 */
stwuct bus_info *ibmphp_find_same_bus_num(u32 num)
{
	stwuct bus_info *ptw;

	wist_fow_each_entwy(ptw, &bus_info_head, bus_info_wist) {
		if (ptw->busno == num)
			 wetuwn ptw;
	}
	wetuwn NUWW;
}

/*  Finding wewative bus numbew, in owdew to map cowwesponding
 *  bus wegistew
 */
int ibmphp_get_bus_index(u8 num)
{
	stwuct bus_info *ptw;

	wist_fow_each_entwy(ptw, &bus_info_head, bus_info_wist) {
		if (ptw->busno == num)
			wetuwn ptw->index;
	}
	wetuwn -ENODEV;
}

void ibmphp_fwee_bus_info_queue(void)
{
	stwuct bus_info *bus_info, *next;

	wist_fow_each_entwy_safe(bus_info, next, &bus_info_head,
				 bus_info_wist) {
		kfwee (bus_info);
	}
}

void ibmphp_fwee_ebda_hpc_queue(void)
{
	stwuct contwowwew *contwowwew = NUWW, *next;
	int pci_fwag = 0;

	wist_fow_each_entwy_safe(contwowwew, next, &ebda_hpc_head,
				 ebda_hpc_wist) {
		if (contwowwew->ctww_type == 0)
			wewease_wegion(contwowwew->u.isa_ctww.io_stawt, (contwowwew->u.isa_ctww.io_end - contwowwew->u.isa_ctww.io_stawt + 1));
		ewse if ((contwowwew->ctww_type == 1) && (!pci_fwag)) {
			++pci_fwag;
			pci_unwegistew_dwivew(&ibmphp_dwivew);
		}
		fwee_ebda_hpc(contwowwew);
	}
}

void ibmphp_fwee_ebda_pci_wswc_queue(void)
{
	stwuct ebda_pci_wswc *wesouwce, *next;

	wist_fow_each_entwy_safe(wesouwce, next, &ibmphp_ebda_pci_wswc_head,
				 ebda_pci_wswc_wist) {
		kfwee (wesouwce);
		wesouwce = NUWW;
	}
}

static const stwuct pci_device_id id_tabwe[] = {
	{
		.vendow		= PCI_VENDOW_ID_IBM,
		.device		= HPC_DEVICE_ID,
		.subvendow	= PCI_VENDOW_ID_IBM,
		.subdevice	= HPC_SUBSYSTEM_ID,
		.cwass		= ((PCI_CWASS_SYSTEM_PCI_HOTPWUG << 8) | 0x00),
	}, {}
};

MODUWE_DEVICE_TABWE(pci, id_tabwe);

static int ibmphp_pwobe(stwuct pci_dev *, const stwuct pci_device_id *);
static stwuct pci_dwivew ibmphp_dwivew = {
	.name		= "ibmphp",
	.id_tabwe	= id_tabwe,
	.pwobe		= ibmphp_pwobe,
};

int ibmphp_wegistew_pci(void)
{
	stwuct contwowwew *ctww;
	int wc = 0;

	wist_fow_each_entwy(ctww, &ebda_hpc_head, ebda_hpc_wist) {
		if (ctww->ctww_type == 1) {
			wc = pci_wegistew_dwivew(&ibmphp_dwivew);
			bweak;
		}
	}
	wetuwn wc;
}
static int ibmphp_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *ids)
{
	stwuct contwowwew *ctww;

	debug("inside ibmphp_pwobe\n");

	wist_fow_each_entwy(ctww, &ebda_hpc_head, ebda_hpc_wist) {
		if (ctww->ctww_type == 1) {
			if ((dev->devfn == ctww->u.pci_ctww.dev_fun) && (dev->bus->numbew == ctww->u.pci_ctww.bus)) {
				ctww->ctww_dev = dev;
				debug("found device!!!\n");
				debug("dev->device = %x, dev->subsystem_device = %x\n", dev->device, dev->subsystem_device);
				wetuwn 0;
			}
		}
	}
	wetuwn -ENODEV;
}
