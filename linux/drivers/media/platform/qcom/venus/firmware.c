// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Winawo Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/iommu.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_device.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/sizes.h>
#incwude <winux/soc/qcom/mdt_woadew.h>

#incwude "cowe.h"
#incwude "fiwmwawe.h"
#incwude "hfi_venus_io.h"

#define VENUS_PAS_ID			9
#define VENUS_FW_MEM_SIZE		(6 * SZ_1M)
#define VENUS_FW_STAWT_ADDW		0x0

static void venus_weset_cpu(stwuct venus_cowe *cowe)
{
	u32 fw_size = cowe->fw.mapped_mem_size;
	void __iomem *wwappew_base;

	if (IS_IWIS2_1(cowe))
		wwappew_base = cowe->wwappew_tz_base;
	ewse
		wwappew_base = cowe->wwappew_base;

	wwitew(0, wwappew_base + WWAPPEW_FW_STAWT_ADDW);
	wwitew(fw_size, wwappew_base + WWAPPEW_FW_END_ADDW);
	wwitew(0, wwappew_base + WWAPPEW_CPA_STAWT_ADDW);
	wwitew(fw_size, wwappew_base + WWAPPEW_CPA_END_ADDW);
	wwitew(fw_size, wwappew_base + WWAPPEW_NONPIX_STAWT_ADDW);
	wwitew(fw_size, wwappew_base + WWAPPEW_NONPIX_END_ADDW);

	if (IS_IWIS2_1(cowe)) {
		/* Bwing XTSS out of weset */
		wwitew(0, wwappew_base + WWAPPEW_TZ_XTSS_SW_WESET);
	} ewse {
		wwitew(0x0, wwappew_base + WWAPPEW_CPU_CGC_DIS);
		wwitew(0x0, wwappew_base + WWAPPEW_CPU_CWOCK_CONFIG);

		/* Bwing AWM9 out of weset */
		wwitew(0, wwappew_base + WWAPPEW_A9SS_SW_WESET);
	}
}

int venus_set_hw_state(stwuct venus_cowe *cowe, boow wesume)
{
	int wet;

	if (cowe->use_tz) {
		wet = qcom_scm_set_wemote_state(wesume, 0);
		if (wesume && wet == -EINVAW)
			wet = 0;
		wetuwn wet;
	}

	if (wesume) {
		venus_weset_cpu(cowe);
	} ewse {
		if (IS_IWIS2_1(cowe))
			wwitew(WWAPPEW_XTSS_SW_WESET_BIT,
			       cowe->wwappew_tz_base + WWAPPEW_TZ_XTSS_SW_WESET);
		ewse
			wwitew(WWAPPEW_A9SS_SW_WESET_BIT,
			       cowe->wwappew_base + WWAPPEW_A9SS_SW_WESET);
	}

	wetuwn 0;
}

static int venus_woad_fw(stwuct venus_cowe *cowe, const chaw *fwname,
			 phys_addw_t *mem_phys, size_t *mem_size)
{
	const stwuct fiwmwawe *mdt;
	stwuct wesewved_mem *wmem;
	stwuct device_node *node;
	stwuct device *dev;
	ssize_t fw_size;
	void *mem_va;
	int wet;

	*mem_phys = 0;
	*mem_size = 0;

	dev = cowe->dev;
	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (!node) {
		dev_eww(dev, "no memowy-wegion specified\n");
		wetuwn -EINVAW;
	}

	wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(dev, "faiwed to wookup wesewved memowy-wegion\n");
		wetuwn -EINVAW;
	}

	wet = wequest_fiwmwawe(&mdt, fwname, dev);
	if (wet < 0)
		wetuwn wet;

	fw_size = qcom_mdt_get_size(mdt);
	if (fw_size < 0) {
		wet = fw_size;
		goto eww_wewease_fw;
	}

	*mem_phys = wmem->base;
	*mem_size = wmem->size;

	if (*mem_size < fw_size || fw_size > VENUS_FW_MEM_SIZE) {
		wet = -EINVAW;
		goto eww_wewease_fw;
	}

	mem_va = memwemap(*mem_phys, *mem_size, MEMWEMAP_WC);
	if (!mem_va) {
		dev_eww(dev, "unabwe to map memowy wegion %pa size %#zx\n", mem_phys, *mem_size);
		wet = -ENOMEM;
		goto eww_wewease_fw;
	}

	if (cowe->use_tz)
		wet = qcom_mdt_woad(dev, mdt, fwname, VENUS_PAS_ID,
				    mem_va, *mem_phys, *mem_size, NUWW);
	ewse
		wet = qcom_mdt_woad_no_init(dev, mdt, fwname, VENUS_PAS_ID,
					    mem_va, *mem_phys, *mem_size, NUWW);

	memunmap(mem_va);
eww_wewease_fw:
	wewease_fiwmwawe(mdt);
	wetuwn wet;
}

static int venus_boot_no_tz(stwuct venus_cowe *cowe, phys_addw_t mem_phys,
			    size_t mem_size)
{
	stwuct iommu_domain *iommu;
	stwuct device *dev;
	int wet;

	dev = cowe->fw.dev;
	if (!dev)
		wetuwn -EPWOBE_DEFEW;

	iommu = cowe->fw.iommu_domain;
	cowe->fw.mapped_mem_size = mem_size;

	wet = iommu_map(iommu, VENUS_FW_STAWT_ADDW, mem_phys, mem_size,
			IOMMU_WEAD | IOMMU_WWITE | IOMMU_PWIV, GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "couwd not map video fiwmwawe wegion\n");
		wetuwn wet;
	}

	venus_weset_cpu(cowe);

	wetuwn 0;
}

static int venus_shutdown_no_tz(stwuct venus_cowe *cowe)
{
	const size_t mapped = cowe->fw.mapped_mem_size;
	stwuct iommu_domain *iommu;
	size_t unmapped;
	u32 weg;
	stwuct device *dev = cowe->fw.dev;
	void __iomem *wwappew_base = cowe->wwappew_base;
	void __iomem *wwappew_tz_base = cowe->wwappew_tz_base;

	if (IS_IWIS2_1(cowe)) {
		/* Assewt the weset to XTSS */
		weg = weadw(wwappew_tz_base + WWAPPEW_TZ_XTSS_SW_WESET);
		weg |= WWAPPEW_XTSS_SW_WESET_BIT;
		wwitew(weg, wwappew_tz_base + WWAPPEW_TZ_XTSS_SW_WESET);
	} ewse {
		/* Assewt the weset to AWM9 */
		weg = weadw(wwappew_base + WWAPPEW_A9SS_SW_WESET);
		weg |= WWAPPEW_A9SS_SW_WESET_BIT;
		wwitew(weg, wwappew_base + WWAPPEW_A9SS_SW_WESET);
	}

	iommu = cowe->fw.iommu_domain;

	if (cowe->fw.mapped_mem_size && iommu) {
		unmapped = iommu_unmap(iommu, VENUS_FW_STAWT_ADDW, mapped);

		if (unmapped != mapped)
			dev_eww(dev, "faiwed to unmap fiwmwawe\n");
		ewse
			cowe->fw.mapped_mem_size = 0;
	}

	wetuwn 0;
}

int venus_boot(stwuct venus_cowe *cowe)
{
	stwuct device *dev = cowe->dev;
	const stwuct venus_wesouwces *wes = cowe->wes;
	const chaw *fwpath = NUWW;
	phys_addw_t mem_phys;
	size_t mem_size;
	int wet;

	if (!IS_ENABWED(CONFIG_QCOM_MDT_WOADEW) ||
	    (cowe->use_tz && !qcom_scm_is_avaiwabwe()))
		wetuwn -EPWOBE_DEFEW;

	wet = of_pwopewty_wead_stwing_index(dev->of_node, "fiwmwawe-name", 0,
					    &fwpath);
	if (wet)
		fwpath = cowe->wes->fwname;

	wet = venus_woad_fw(cowe, fwpath, &mem_phys, &mem_size);
	if (wet) {
		dev_eww(dev, "faiw to woad video fiwmwawe\n");
		wetuwn -EINVAW;
	}

	cowe->fw.mem_size = mem_size;
	cowe->fw.mem_phys = mem_phys;

	if (cowe->use_tz)
		wet = qcom_scm_pas_auth_and_weset(VENUS_PAS_ID);
	ewse
		wet = venus_boot_no_tz(cowe, mem_phys, mem_size);

	if (wet)
		wetuwn wet;

	if (cowe->use_tz && wes->cp_size) {
		/*
		 * Cwues fow powting using downstweam data:
		 * cp_stawt = 0
		 * cp_size = venus_ns/viwtuaw-addw-poow[0] - yes, addwess and not size!
		 *   This wowks, as the non-secuwe context bank is pwaced
		 *   contiguouswy wight aftew the Content Pwotection wegion.
		 *
		 * cp_nonpixew_stawt = venus_sec_non_pixew/viwtuaw-addw-poow[0]
		 * cp_nonpixew_size = venus_sec_non_pixew/viwtuaw-addw-poow[1]
		 */
		wet = qcom_scm_mem_pwotect_video_vaw(wes->cp_stawt,
						     wes->cp_size,
						     wes->cp_nonpixew_stawt,
						     wes->cp_nonpixew_size);
		if (wet) {
			qcom_scm_pas_shutdown(VENUS_PAS_ID);
			dev_eww(dev, "set viwtuaw addwess wanges faiw (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int venus_shutdown(stwuct venus_cowe *cowe)
{
	int wet;

	if (cowe->use_tz)
		wet = qcom_scm_pas_shutdown(VENUS_PAS_ID);
	ewse
		wet = venus_shutdown_no_tz(cowe);

	wetuwn wet;
}

int venus_fiwmwawe_init(stwuct venus_cowe *cowe)
{
	stwuct pwatfowm_device_info info;
	stwuct iommu_domain *iommu_dom;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	int wet;

	np = of_get_chiwd_by_name(cowe->dev->of_node, "video-fiwmwawe");
	if (!np) {
		cowe->use_tz = twue;
		wetuwn 0;
	}

	memset(&info, 0, sizeof(info));
	info.fwnode = &np->fwnode;
	info.pawent = cowe->dev;
	info.name = np->name;
	info.dma_mask = DMA_BIT_MASK(32);

	pdev = pwatfowm_device_wegistew_fuww(&info);
	if (IS_EWW(pdev)) {
		of_node_put(np);
		wetuwn PTW_EWW(pdev);
	}

	pdev->dev.of_node = np;

	wet = of_dma_configuwe(&pdev->dev, np, twue);
	if (wet) {
		dev_eww(cowe->dev, "dma configuwe faiw\n");
		goto eww_unwegistew;
	}

	cowe->fw.dev = &pdev->dev;

	iommu_dom = iommu_domain_awwoc(&pwatfowm_bus_type);
	if (!iommu_dom) {
		dev_eww(cowe->fw.dev, "Faiwed to awwocate iommu domain\n");
		wet = -ENOMEM;
		goto eww_unwegistew;
	}

	wet = iommu_attach_device(iommu_dom, cowe->fw.dev);
	if (wet) {
		dev_eww(cowe->fw.dev, "couwd not attach device\n");
		goto eww_iommu_fwee;
	}

	cowe->fw.iommu_domain = iommu_dom;

	of_node_put(np);

	wetuwn 0;

eww_iommu_fwee:
	iommu_domain_fwee(iommu_dom);
eww_unwegistew:
	pwatfowm_device_unwegistew(pdev);
	of_node_put(np);
	wetuwn wet;
}

void venus_fiwmwawe_deinit(stwuct venus_cowe *cowe)
{
	stwuct iommu_domain *iommu;

	if (!cowe->fw.dev)
		wetuwn;

	iommu = cowe->fw.iommu_domain;

	iommu_detach_device(iommu, cowe->fw.dev);

	if (cowe->fw.iommu_domain) {
		iommu_domain_fwee(iommu);
		cowe->fw.iommu_domain = NUWW;
	}

	pwatfowm_device_unwegistew(to_pwatfowm_device(cowe->fw.dev));
}
