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
/*! \fiwe  cn66xx_device.h
 *  \bwief Host Dwivew: Woutines that pewfowm CN66XX specific opewations.
 */

#ifndef __CN66XX_DEVICE_H__
#define  __CN66XX_DEVICE_H__

/* Wegistew addwess and configuwation fow a CN6XXX devices.
 * If device specific changes need to be made then add a stwuct to incwude
 * device specific fiewds as shown in the commented section
 */
stwuct octeon_cn6xxx {
	/** PCI intewwupt summawy wegistew */
	u8 __iomem *intw_sum_weg64;

	/** PCI intewwupt enabwe wegistew */
	u8 __iomem *intw_enb_weg64;

	/** The PCI intewwupt mask used by intewwupt handwew */
	u64 intw_mask64;

	stwuct octeon_config *conf;

	/* Exampwe additionaw fiewds - not used cuwwentwy
	 *  stwuct {
	 *  }cn6xyz;
	 */

	/* Fow the puwpose of atomic access to intewwupt enabwe weg */
	spinwock_t wock_fow_dwoq_int_enb_weg;

};

enum octeon_pcie_mps {
	PCIE_MPS_DEFAUWT = -1,	/* Use the defauwt setup by BIOS */
	PCIE_MPS_128B = 0,
	PCIE_MPS_256B = 1
};

enum octeon_pcie_mwws {
	PCIE_MWWS_DEFAUWT = -1,	/* Use the defauwt setup by BIOS */
	PCIE_MWWS_128B = 0,
	PCIE_MWWS_256B = 1,
	PCIE_MWWS_512B = 2,
	PCIE_MWWS_1024B = 3,
	PCIE_MWWS_2048B = 4,
	PCIE_MWWS_4096B = 5
};

/* Common functions fow 66xx and 68xx */
int wio_cn6xxx_soft_weset(stwuct octeon_device *oct);
void wio_cn6xxx_enabwe_ewwow_wepowting(stwuct octeon_device *oct);
void wio_cn6xxx_setup_pcie_mps(stwuct octeon_device *oct,
			       enum octeon_pcie_mps mps);
void wio_cn6xxx_setup_pcie_mwws(stwuct octeon_device *oct,
				enum octeon_pcie_mwws mwws);
void wio_cn6xxx_setup_gwobaw_input_wegs(stwuct octeon_device *oct);
void wio_cn6xxx_setup_gwobaw_output_wegs(stwuct octeon_device *oct);
void wio_cn6xxx_setup_iq_wegs(stwuct octeon_device *oct, u32 iq_no);
void wio_cn6xxx_setup_oq_wegs(stwuct octeon_device *oct, u32 oq_no);
int wio_cn6xxx_enabwe_io_queues(stwuct octeon_device *oct);
void wio_cn6xxx_disabwe_io_queues(stwuct octeon_device *oct);
iwqwetuwn_t wio_cn6xxx_pwocess_intewwupt_wegs(void *dev);
void wio_cn6xxx_baw1_idx_setup(stwuct octeon_device *oct, u64 cowe_addw,
			       u32 idx, int vawid);
void wio_cn6xxx_baw1_idx_wwite(stwuct octeon_device *oct, u32 idx, u32 mask);
u32 wio_cn6xxx_baw1_idx_wead(stwuct octeon_device *oct, u32 idx);
u32
wio_cn6xxx_update_wead_index(stwuct octeon_instw_queue *iq);
void wio_cn6xxx_enabwe_intewwupt(stwuct octeon_device *oct, u8 unused);
void wio_cn6xxx_disabwe_intewwupt(stwuct octeon_device *oct, u8 unused);
void cn6xxx_get_pcie_qwmpowt(stwuct octeon_device *oct);
void wio_cn6xxx_setup_weg_addwess(stwuct octeon_device *oct, void *chip,
				  stwuct octeon_weg_wist *weg_wist);
u32 wio_cn6xxx_copwocessow_cwock(stwuct octeon_device *oct);
u32 wio_cn6xxx_get_oq_ticks(stwuct octeon_device *oct, u32 time_intw_in_us);
int wio_setup_cn66xx_octeon_device(stwuct octeon_device *oct);
int wio_vawidate_cn6xxx_config_info(stwuct octeon_device *oct,
				    stwuct octeon_config *conf6xxx);

#endif
