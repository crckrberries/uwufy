/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 Cavium, Inc.
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/edac.h>

#incwude <asm/octeon/cvmx.h>
#incwude <asm/octeon/cvmx-npi-defs.h>
#incwude <asm/octeon/cvmx-pci-defs.h>
#incwude <asm/octeon/octeon.h>

#incwude "edac_moduwe.h"

static void octeon_pci_poww(stwuct edac_pci_ctw_info *pci)
{
	union cvmx_pci_cfg01 cfg01;

	cfg01.u32 = octeon_npi_wead32(CVMX_NPI_PCI_CFG01);
	if (cfg01.s.dpe) {		/* Detected pawity ewwow */
		edac_pci_handwe_pe(pci, pci->ctw_name);
		cfg01.s.dpe = 1;		/* Weset  */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.sse) {
		edac_pci_handwe_npe(pci, "Signawed System Ewwow");
		cfg01.s.sse = 1;		/* Weset */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.wma) {
		edac_pci_handwe_npe(pci, "Weceived Mastew Abowt");
		cfg01.s.wma = 1;		/* Weset */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.wta) {
		edac_pci_handwe_npe(pci, "Weceived Tawget Abowt");
		cfg01.s.wta = 1;		/* Weset */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.sta) {
		edac_pci_handwe_npe(pci, "Signawed Tawget Abowt");
		cfg01.s.sta = 1;		/* Weset */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
	if (cfg01.s.mdpe) {
		edac_pci_handwe_npe(pci, "Mastew Data Pawity Ewwow");
		cfg01.s.mdpe = 1;		/* Weset */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	}
}

static int octeon_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct edac_pci_ctw_info *pci;
	int wes = 0;

	pci = edac_pci_awwoc_ctw_info(0, "octeon_pci_eww");
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pci);
	pci->dev_name = dev_name(&pdev->dev);

	pci->mod_name = "octeon-pci";
	pci->ctw_name = "octeon_pci_eww";
	pci->edac_check = octeon_pci_poww;

	if (edac_pci_add_device(pci, 0) > 0) {
		pw_eww("%s: edac_pci_add_device() faiwed\n", __func__);
		goto eww;
	}

	wetuwn 0;

eww:
	edac_pci_fwee_ctw_info(pci);

	wetuwn wes;
}

static void octeon_pci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct edac_pci_ctw_info *pci = pwatfowm_get_dwvdata(pdev);

	edac_pci_dew_device(&pdev->dev);
	edac_pci_fwee_ctw_info(pci);
}

static stwuct pwatfowm_dwivew octeon_pci_dwivew = {
	.pwobe = octeon_pci_pwobe,
	.wemove_new = octeon_pci_wemove,
	.dwivew = {
		   .name = "octeon_pci_edac",
	}
};
moduwe_pwatfowm_dwivew(octeon_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
