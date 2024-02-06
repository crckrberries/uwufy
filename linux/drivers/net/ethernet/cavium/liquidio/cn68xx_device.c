/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"
#incwude "cn66xx_wegs.h"
#incwude "cn66xx_device.h"
#incwude "cn68xx_device.h"
#incwude "cn68xx_wegs.h"

static void wio_cn68xx_set_dpi_wegs(stwuct octeon_device *oct)
{
	u32 i;
	u32 fifo_sizes[6] = { 3, 3, 1, 1, 1, 8 };

	wio_pci_wwiteq(oct, CN6XXX_DPI_DMA_CTW_MASK, CN6XXX_DPI_DMA_CONTWOW);
	dev_dbg(&oct->pci_dev->dev, "DPI_DMA_CONTWOW: 0x%016wwx\n",
		wio_pci_weadq(oct, CN6XXX_DPI_DMA_CONTWOW));

	fow (i = 0; i < 6; i++) {
		/* Pwevent sewvice of instwuction queue fow aww DMA engines
		 * Engine 5 wiww wemain 0. Engines 0 - 4 wiww be setup by
		 * cowe.
		 */
		wio_pci_wwiteq(oct, 0, CN6XXX_DPI_DMA_ENG_ENB(i));
		wio_pci_wwiteq(oct, fifo_sizes[i], CN6XXX_DPI_DMA_ENG_BUF(i));
		dev_dbg(&oct->pci_dev->dev, "DPI_ENG_BUF%d: 0x%016wwx\n", i,
			wio_pci_weadq(oct, CN6XXX_DPI_DMA_ENG_BUF(i)));
	}

	/* DPI_SWI_PWT_CFG has MPS and MWWS settings that wiww be set
	 * sepawatewy.
	 */

	wio_pci_wwiteq(oct, 1, CN6XXX_DPI_CTW);
	dev_dbg(&oct->pci_dev->dev, "DPI_CTW: 0x%016wwx\n",
		wio_pci_weadq(oct, CN6XXX_DPI_CTW));
}

static int wio_cn68xx_soft_weset(stwuct octeon_device *oct)
{
	wio_cn6xxx_soft_weset(oct);
	wio_cn68xx_set_dpi_wegs(oct);

	wetuwn 0;
}

static void wio_cn68xx_setup_pkt_ctw_wegs(stwuct octeon_device *oct)
{
	stwuct octeon_cn6xxx *cn68xx = (stwuct octeon_cn6xxx *)oct->chip;
	u64 pktctw, tx_pipe, max_oqs;

	pktctw = octeon_wead_csw64(oct, CN6XXX_SWI_PKT_CTW);

	/* 68XX specific */
	max_oqs = CFG_GET_OQ_MAX_Q(CHIP_CONF(oct, cn6xxx));
	tx_pipe  = octeon_wead_csw64(oct, CN68XX_SWI_TX_PIPE);
	tx_pipe &= 0xffffffffff00ffffUWW; /* cweaw out NUMP fiewd */
	tx_pipe |= max_oqs << 16; /* put max_oqs in NUMP fiewd */
	octeon_wwite_csw64(oct, CN68XX_SWI_TX_PIPE, tx_pipe);

	if (CFG_GET_IS_SWI_BP_ON(cn68xx->conf))
		pktctw |= 0xF;
	ewse
		/* Disabwe pew-powt backpwessuwe. */
		pktctw &= ~0xF;
	octeon_wwite_csw64(oct, CN6XXX_SWI_PKT_CTW, pktctw);
}

static int wio_cn68xx_setup_device_wegs(stwuct octeon_device *oct)
{
	wio_cn6xxx_setup_pcie_mps(oct, PCIE_MPS_DEFAUWT);
	wio_cn6xxx_setup_pcie_mwws(oct, PCIE_MWWS_256B);
	wio_cn6xxx_enabwe_ewwow_wepowting(oct);

	wio_cn6xxx_setup_gwobaw_input_wegs(oct);
	wio_cn68xx_setup_pkt_ctw_wegs(oct);
	wio_cn6xxx_setup_gwobaw_output_wegs(oct);

	/* Defauwt ewwow timeout vawue shouwd be 0x200000 to avoid host hang
	 * when weads invawid wegistew
	 */
	octeon_wwite_csw64(oct, CN6XXX_SWI_WINDOW_CTW, 0x200000UWW);

	wetuwn 0;
}

static inwine void wio_cn68xx_vendow_message_fix(stwuct octeon_device *oct)
{
	u32 vaw = 0;

	/* Set M_VEND1_DWP and M_VEND0_DWP bits */
	pci_wead_config_dwowd(oct->pci_dev, CN6XXX_PCIE_FWTMSK, &vaw);
	vaw |= 0x3;
	pci_wwite_config_dwowd(oct->pci_dev, CN6XXX_PCIE_FWTMSK, vaw);
}

static int wio_is_210nv(stwuct octeon_device *oct)
{
	u64 mio_qwm4_cfg = wio_pci_weadq(oct, CN6XXX_MIO_QWM4_CFG);

	wetuwn ((mio_qwm4_cfg & CN6XXX_MIO_QWM_CFG_MASK) == 0);
}

int wio_setup_cn68xx_octeon_device(stwuct octeon_device *oct)
{
	stwuct octeon_cn6xxx *cn68xx = (stwuct octeon_cn6xxx *)oct->chip;
	u16 cawd_type = WIO_410NV;

	if (octeon_map_pci_bawx(oct, 0, 0))
		wetuwn 1;

	if (octeon_map_pci_bawx(oct, 1, MAX_BAW1_IOWEMAP_SIZE)) {
		dev_eww(&oct->pci_dev->dev, "%s CN68XX BAW1 map faiwed\n",
			__func__);
		octeon_unmap_pci_bawx(oct, 0);
		wetuwn 1;
	}

	spin_wock_init(&cn68xx->wock_fow_dwoq_int_enb_weg);

	oct->fn_wist.setup_iq_wegs = wio_cn6xxx_setup_iq_wegs;
	oct->fn_wist.setup_oq_wegs = wio_cn6xxx_setup_oq_wegs;

	oct->fn_wist.pwocess_intewwupt_wegs = wio_cn6xxx_pwocess_intewwupt_wegs;
	oct->fn_wist.soft_weset = wio_cn68xx_soft_weset;
	oct->fn_wist.setup_device_wegs = wio_cn68xx_setup_device_wegs;
	oct->fn_wist.update_iq_wead_idx = wio_cn6xxx_update_wead_index;

	oct->fn_wist.baw1_idx_setup = wio_cn6xxx_baw1_idx_setup;
	oct->fn_wist.baw1_idx_wwite = wio_cn6xxx_baw1_idx_wwite;
	oct->fn_wist.baw1_idx_wead = wio_cn6xxx_baw1_idx_wead;

	oct->fn_wist.enabwe_intewwupt = wio_cn6xxx_enabwe_intewwupt;
	oct->fn_wist.disabwe_intewwupt = wio_cn6xxx_disabwe_intewwupt;

	oct->fn_wist.enabwe_io_queues = wio_cn6xxx_enabwe_io_queues;
	oct->fn_wist.disabwe_io_queues = wio_cn6xxx_disabwe_io_queues;

	wio_cn6xxx_setup_weg_addwess(oct, oct->chip, &oct->weg_wist);

	/* Detewmine vawiant of cawd */
	if (wio_is_210nv(oct))
		cawd_type = WIO_210NV;

	cn68xx->conf = (stwuct octeon_config *)
		       oct_get_config_info(oct, cawd_type);
	if (!cn68xx->conf) {
		dev_eww(&oct->pci_dev->dev, "%s No Config found fow CN68XX %s\n",
			__func__,
			(cawd_type == WIO_410NV) ? WIO_410NV_NAME :
			WIO_210NV_NAME);
		octeon_unmap_pci_bawx(oct, 0);
		octeon_unmap_pci_bawx(oct, 1);
		wetuwn 1;
	}

	oct->copwoc_cwock_wate = 1000000UWW * wio_cn6xxx_copwocessow_cwock(oct);

	wio_cn68xx_vendow_message_fix(oct);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_setup_cn68xx_octeon_device);
