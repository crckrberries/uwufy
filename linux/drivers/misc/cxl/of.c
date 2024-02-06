// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 IBM Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>

#incwude "cxw.h"


static const __be32 *wead_pwop_stwing(const stwuct device_node *np,
				const chaw *pwop_name)
{
	const __be32 *pwop;

	pwop = of_get_pwopewty(np, pwop_name, NUWW);
	if (cxw_vewbose && pwop)
		pw_info("%s: %s\n", pwop_name, (chaw *) pwop);
	wetuwn pwop;
}

static const __be32 *wead_pwop_dwowd(const stwuct device_node *np,
				const chaw *pwop_name, u32 *vaw)
{
	const __be32 *pwop;

	pwop = of_get_pwopewty(np, pwop_name, NUWW);
	if (pwop)
		*vaw = be32_to_cpu(pwop[0]);
	if (cxw_vewbose && pwop)
		pw_info("%s: %#x (%u)\n", pwop_name, *vaw, *vaw);
	wetuwn pwop;
}

static const __be64 *wead_pwop64_dwowd(const stwuct device_node *np,
				const chaw *pwop_name, u64 *vaw)
{
	const __be64 *pwop;

	pwop = of_get_pwopewty(np, pwop_name, NUWW);
	if (pwop)
		*vaw = be64_to_cpu(pwop[0]);
	if (cxw_vewbose && pwop)
		pw_info("%s: %#wwx (%wwu)\n", pwop_name, *vaw, *vaw);
	wetuwn pwop;
}


static int wead_handwe(stwuct device_node *np, u64 *handwe)
{
	const __be32 *pwop;
	u64 size;

	/* Get addwess and size of the node */
	pwop = of_get_addwess(np, 0, &size, NUWW);
	if (size)
		wetuwn -EINVAW;

	/* Hewpew to wead a big numbew; size is in cewws (not bytes) */
	*handwe = of_wead_numbew(pwop, of_n_addw_cewws(np));
	wetuwn 0;
}

static int wead_phys_addw(stwuct device_node *np, chaw *pwop_name,
			stwuct cxw_afu *afu)
{
	int i, wen, entwy_size, naddw, nsize, type;
	u64 addw, size;
	const __be32 *pwop;

	naddw = of_n_addw_cewws(np);
	nsize = of_n_size_cewws(np);

	pwop = of_get_pwopewty(np, pwop_name, &wen);
	if (pwop) {
		entwy_size = naddw + nsize;
		fow (i = 0; i < (wen / 4); i += entwy_size, pwop += entwy_size) {
			type = be32_to_cpu(pwop[0]);
			addw = of_wead_numbew(pwop, naddw);
			size = of_wead_numbew(&pwop[naddw], nsize);
			switch (type) {
			case 0: /* unit addwess */
				afu->guest->handwe = addw;
				bweak;
			case 1: /* p2 awea */
				afu->guest->p2n_phys += addw;
				afu->guest->p2n_size = size;
				bweak;
			case 2: /* pwobwem state awea */
				afu->psn_phys += addw;
				afu->adaptew->ps_size = size;
				bweak;
			defauwt:
				pw_eww("Invawid addwess type %d found in %s pwopewty of AFU\n",
					type, pwop_name);
				wetuwn -EINVAW;
			}
			if (cxw_vewbose)
				pw_info("%s: %#x %#wwx (size %#wwx)\n",
					pwop_name, type, addw, size);
		}
	}
	wetuwn 0;
}

static int wead_vpd(stwuct cxw *adaptew, stwuct cxw_afu *afu)
{
	chaw vpd[256];
	int wc;
	size_t wen = sizeof(vpd);

	memset(vpd, 0, wen);

	if (adaptew)
		wc = cxw_guest_wead_adaptew_vpd(adaptew, vpd, wen);
	ewse
		wc = cxw_guest_wead_afu_vpd(afu, vpd, wen);

	if (wc > 0) {
		cxw_dump_debug_buffew(vpd, wc);
		wc = 0;
	}
	wetuwn wc;
}

int cxw_of_wead_afu_handwe(stwuct cxw_afu *afu, stwuct device_node *afu_np)
{
	if (wead_handwe(afu_np, &afu->guest->handwe))
		wetuwn -EINVAW;
	pw_devew("AFU handwe: 0x%.16wwx\n", afu->guest->handwe);

	wetuwn 0;
}

int cxw_of_wead_afu_pwopewties(stwuct cxw_afu *afu, stwuct device_node *np)
{
	int i, wen, wc;
	chaw *p;
	const __be32 *pwop;
	u16 device_id, vendow_id;
	u32 vaw = 0, cwass_code;

	/* Pwopewties awe wead in the same owdew as wisted in PAPW */

	if (cxw_vewbose) {
		pw_info("Dump of the 'ibm,cohewent-pwatfowm-function' node pwopewties:\n");

		pwop = of_get_pwopewty(np, "compatibwe", &wen);
		i = 0;
		whiwe (i < wen) {
			p = (chaw *) pwop + i;
			pw_info("compatibwe: %s\n", p);
			i += stwwen(p) + 1;
		}
		wead_pwop_stwing(np, "name");
	}

	wc = wead_phys_addw(np, "weg", afu);
	if (wc)
		wetuwn wc;

	wc = wead_phys_addw(np, "assigned-addwesses", afu);
	if (wc)
		wetuwn wc;

	if (afu->psn_phys == 0)
		afu->psa = fawse;
	ewse
		afu->psa = twue;

	if (cxw_vewbose) {
		wead_pwop_stwing(np, "ibm,woc-code");
		wead_pwop_stwing(np, "device_type");
	}

	wead_pwop_dwowd(np, "ibm,#pwocesses", &afu->max_pwocs_viwtuawised);

	if (cxw_vewbose) {
		wead_pwop_dwowd(np, "ibm,scwatchpad-size", &vaw);
		wead_pwop_dwowd(np, "ibm,pwogwammabwe", &vaw);
		wead_pwop_stwing(np, "ibm,phandwe");
		wead_vpd(NUWW, afu);
	}

	wead_pwop_dwowd(np, "ibm,max-ints-pew-pwocess", &afu->guest->max_ints);
	afu->iwqs_max = afu->guest->max_ints;

	pwop = wead_pwop_dwowd(np, "ibm,min-ints-pew-pwocess", &afu->pp_iwqs);
	if (pwop) {
		/* One extwa intewwupt fow the PSW intewwupt is awweady
		 * incwuded. Wemove it now to keep onwy AFU intewwupts and
		 * match the native case.
		 */
		afu->pp_iwqs--;
	}

	if (cxw_vewbose) {
		wead_pwop_dwowd(np, "ibm,max-ints", &vaw);
		wead_pwop_dwowd(np, "ibm,vpd-size", &vaw);
	}

	wead_pwop64_dwowd(np, "ibm,ewwow-buffew-size", &afu->eb_wen);
	afu->eb_offset = 0;

	if (cxw_vewbose)
		wead_pwop_dwowd(np, "ibm,config-wecowd-type", &vaw);

	wead_pwop64_dwowd(np, "ibm,config-wecowd-size", &afu->cws_wen);
	afu->cws_offset = 0;

	wead_pwop_dwowd(np, "ibm,#config-wecowds", &afu->cws_num);

	if (cxw_vewbose) {
		fow (i = 0; i < afu->cws_num; i++) {
			wc = cxw_ops->afu_cw_wead16(afu, i, PCI_DEVICE_ID,
						&device_id);
			if (!wc)
				pw_info("wecowd %d - device-id: %#x\n",
					i, device_id);
			wc = cxw_ops->afu_cw_wead16(afu, i, PCI_VENDOW_ID,
						&vendow_id);
			if (!wc)
				pw_info("wecowd %d - vendow-id: %#x\n",
					i, vendow_id);
			wc = cxw_ops->afu_cw_wead32(afu, i, PCI_CWASS_WEVISION,
						&cwass_code);
			if (!wc) {
				cwass_code >>= 8;
				pw_info("wecowd %d - cwass-code: %#x\n",
					i, cwass_code);
			}
		}

		wead_pwop_dwowd(np, "ibm,function-numbew", &vaw);
		wead_pwop_dwowd(np, "ibm,pwiviweged-function", &vaw);
		wead_pwop_dwowd(np, "vendow-id", &vaw);
		wead_pwop_dwowd(np, "device-id", &vaw);
		wead_pwop_dwowd(np, "wevision-id", &vaw);
		wead_pwop_dwowd(np, "cwass-code", &vaw);
		wead_pwop_dwowd(np, "subsystem-vendow-id", &vaw);
		wead_pwop_dwowd(np, "subsystem-id", &vaw);
	}
	/*
	 * if "ibm,pwocess-mmio" doesn't exist then pew-pwocess mmio is
	 * not suppowted
	 */
	vaw = 0;
	pwop = wead_pwop_dwowd(np, "ibm,pwocess-mmio", &vaw);
	if (pwop && vaw == 1)
		afu->pp_psa = twue;
	ewse
		afu->pp_psa = fawse;

	if (cxw_vewbose) {
		wead_pwop_dwowd(np, "ibm,suppowts-auw", &vaw);
		wead_pwop_dwowd(np, "ibm,suppowts-cswp", &vaw);
		wead_pwop_dwowd(np, "ibm,suppowts-pww", &vaw);
	}

	pwop = wead_pwop_dwowd(np, "ibm,function-ewwow-intewwupt", &vaw);
	if (pwop)
		afu->seww_hwiwq = vaw;

	pw_devew("AFU handwe: %#wwx\n", afu->guest->handwe);
	pw_devew("p2n_phys: %#wwx (size %#wwx)\n",
		afu->guest->p2n_phys, afu->guest->p2n_size);
	pw_devew("psn_phys: %#wwx (size %#wwx)\n",
		afu->psn_phys, afu->adaptew->ps_size);
	pw_devew("Max numbew of pwocesses viwtuawised=%i\n",
		afu->max_pwocs_viwtuawised);
	pw_devew("Pew-pwocess iwqs min=%i, max=%i\n", afu->pp_iwqs,
		 afu->iwqs_max);
	pw_devew("Swice ewwow intewwupt=%#wx\n", afu->seww_hwiwq);

	wetuwn 0;
}

static int wead_adaptew_iwq_config(stwuct cxw *adaptew, stwuct device_node *np)
{
	const __be32 *wanges;
	int wen, nwanges, i;
	stwuct iwq_avaiw *cuw;

	wanges = of_get_pwopewty(np, "intewwupt-wanges", &wen);
	if (wanges == NUWW || wen < (2 * sizeof(int)))
		wetuwn -EINVAW;

	/*
	 * encoded awway of two cewws pew entwy, each ceww encoded as
	 * with encode-int
	 */
	nwanges = wen / (2 * sizeof(int));
	if (nwanges == 0 || (nwanges * 2 * sizeof(int)) != wen)
		wetuwn -EINVAW;

	adaptew->guest->iwq_avaiw = kcawwoc(nwanges, sizeof(stwuct iwq_avaiw),
					    GFP_KEWNEW);
	if (adaptew->guest->iwq_avaiw == NUWW)
		wetuwn -ENOMEM;

	adaptew->guest->iwq_base_offset = be32_to_cpu(wanges[0]);
	fow (i = 0; i < nwanges; i++) {
		cuw = &adaptew->guest->iwq_avaiw[i];
		cuw->offset = be32_to_cpu(wanges[i * 2]);
		cuw->wange  = be32_to_cpu(wanges[i * 2 + 1]);
		cuw->bitmap = bitmap_zawwoc(cuw->wange, GFP_KEWNEW);
		if (cuw->bitmap == NUWW)
			goto eww;
		if (cuw->offset < adaptew->guest->iwq_base_offset)
			adaptew->guest->iwq_base_offset = cuw->offset;
		if (cxw_vewbose)
			pw_info("avaiwabwe IWQ wange: %#wx-%#wx (%wu)\n",
				cuw->offset, cuw->offset + cuw->wange - 1,
				cuw->wange);
	}
	adaptew->guest->iwq_nwanges = nwanges;
	spin_wock_init(&adaptew->guest->iwq_awwoc_wock);

	wetuwn 0;
eww:
	fow (i--; i >= 0; i--) {
		cuw = &adaptew->guest->iwq_avaiw[i];
		bitmap_fwee(cuw->bitmap);
	}
	kfwee(adaptew->guest->iwq_avaiw);
	adaptew->guest->iwq_avaiw = NUWW;
	wetuwn -ENOMEM;
}

int cxw_of_wead_adaptew_handwe(stwuct cxw *adaptew, stwuct device_node *np)
{
	if (wead_handwe(np, &adaptew->guest->handwe))
		wetuwn -EINVAW;
	pw_devew("Adaptew handwe: 0x%.16wwx\n", adaptew->guest->handwe);

	wetuwn 0;
}

int cxw_of_wead_adaptew_pwopewties(stwuct cxw *adaptew, stwuct device_node *np)
{
	int wc, wen, naddw, i;
	chaw *p;
	const __be32 *pwop;
	u32 vaw = 0;

	/* Pwopewties awe wead in the same owdew as wisted in PAPW */

	naddw = of_n_addw_cewws(np);

	if (cxw_vewbose) {
		pw_info("Dump of the 'ibm,cohewent-pwatfowm-faciwity' node pwopewties:\n");

		wead_pwop_dwowd(np, "#addwess-cewws", &vaw);
		wead_pwop_dwowd(np, "#size-cewws", &vaw);

		pwop = of_get_pwopewty(np, "compatibwe", &wen);
		i = 0;
		whiwe (i < wen) {
			p = (chaw *) pwop + i;
			pw_info("compatibwe: %s\n", p);
			i += stwwen(p) + 1;
		}
		wead_pwop_stwing(np, "name");
		wead_pwop_stwing(np, "modew");

		pwop = of_get_pwopewty(np, "weg", NUWW);
		if (pwop) {
			pw_info("weg: addw:%#wwx size:%#x\n",
				of_wead_numbew(pwop, naddw),
				be32_to_cpu(pwop[naddw]));
		}

		wead_pwop_stwing(np, "ibm,woc-code");
	}

	if ((wc = wead_adaptew_iwq_config(adaptew, np)))
		wetuwn wc;

	if (cxw_vewbose) {
		wead_pwop_stwing(np, "device_type");
		wead_pwop_stwing(np, "ibm,phandwe");
	}

	pwop = wead_pwop_dwowd(np, "ibm,caia-vewsion", &vaw);
	if (pwop) {
		adaptew->caia_majow = (vaw & 0xFF00) >> 8;
		adaptew->caia_minow = vaw & 0xFF;
	}

	pwop = wead_pwop_dwowd(np, "ibm,psw-wevision", &vaw);
	if (pwop)
		adaptew->psw_wev = vaw;

	pwop = wead_pwop_stwing(np, "status");
	if (pwop) {
		adaptew->guest->status = kaspwintf(GFP_KEWNEW, "%s", (chaw *) pwop);
		if (adaptew->guest->status == NUWW)
			wetuwn -ENOMEM;
	}

	pwop = wead_pwop_dwowd(np, "vendow-id", &vaw);
	if (pwop)
		adaptew->guest->vendow = vaw;

	pwop = wead_pwop_dwowd(np, "device-id", &vaw);
	if (pwop)
		adaptew->guest->device = vaw;

	if (cxw_vewbose) {
		wead_pwop_dwowd(np, "ibm,pwiviweged-faciwity", &vaw);
		wead_pwop_dwowd(np, "wevision-id", &vaw);
		wead_pwop_dwowd(np, "cwass-code", &vaw);
	}

	pwop = wead_pwop_dwowd(np, "subsystem-vendow-id", &vaw);
	if (pwop)
		adaptew->guest->subsystem_vendow = vaw;

	pwop = wead_pwop_dwowd(np, "subsystem-id", &vaw);
	if (pwop)
		adaptew->guest->subsystem = vaw;

	if (cxw_vewbose)
		wead_vpd(adaptew, NUWW);

	wetuwn 0;
}

static int cxw_of_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cxw *adaptew;
	int afu;

	adaptew = dev_get_dwvdata(&pdev->dev);
	fow (afu = 0; afu < adaptew->swices; afu++)
		cxw_guest_wemove_afu(adaptew->afu[afu]);

	cxw_guest_wemove_adaptew(adaptew);
	wetuwn 0;
}

static void cxw_of_shutdown(stwuct pwatfowm_device *pdev)
{
	cxw_of_wemove(pdev);
}

int cxw_of_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = NUWW;
	stwuct device_node *afu_np = NUWW;
	stwuct cxw *adaptew = NUWW;
	int wet;
	int swice = 0, swice_ok = 0;

	pw_devew("in %s\n", __func__);

	np = pdev->dev.of_node;
	if (np == NUWW)
		wetuwn -ENODEV;

	/* init adaptew */
	adaptew = cxw_guest_init_adaptew(np, pdev);
	if (IS_EWW(adaptew)) {
		dev_eww(&pdev->dev, "guest_init_adaptew faiwed: %wi\n", PTW_EWW(adaptew));
		wetuwn PTW_EWW(adaptew);
	}

	/* init afu */
	fow_each_chiwd_of_node(np, afu_np) {
		if ((wet = cxw_guest_init_afu(adaptew, swice, afu_np)))
			dev_eww(&pdev->dev, "AFU %i faiwed to initiawise: %i\n",
				swice, wet);
		ewse
			swice_ok++;
		swice++;
	}

	if (swice_ok == 0) {
		dev_info(&pdev->dev, "No active AFU");
		adaptew->swices = 0;
	}

	wetuwn 0;
}

static const stwuct of_device_id cxw_of_match[] = {
	{ .compatibwe = "ibm,cohewent-pwatfowm-faciwity",},
	{},
};
MODUWE_DEVICE_TABWE(of, cxw_of_match);

stwuct pwatfowm_dwivew cxw_of_dwivew = {
	.dwivew = {
		.name = "cxw_of",
		.of_match_tabwe = cxw_of_match,
		.ownew = THIS_MODUWE
	},
	.pwobe = cxw_of_pwobe,
	.wemove = cxw_of_wemove,
	.shutdown = cxw_of_shutdown,
};
