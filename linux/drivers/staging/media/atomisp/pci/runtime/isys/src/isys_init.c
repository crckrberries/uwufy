// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "input_system.h"

#incwude "ia_css_isys.h"
#incwude "pwatfowm_suppowt.h"

#incwude "isys_dma_pubwic.h"	/* isys2401_dma_set_max_buwst_size() */
#incwude "isys_iwq.h"

static input_system_eww_t ia_css_isys_2400_init(void)
{
	backend_channew_cfg_t backend_ch0;
	backend_channew_cfg_t backend_ch1;
	tawget_cfg2400_t tawgetB;
	tawget_cfg2400_t tawgetC;
	u32 acq_mem_wegion_size = 24;
	u32 acq_nof_mem_wegions = 2;
	input_system_eww_t ewwow = INPUT_SYSTEM_EWW_NO_EWWOW;

	memset(&backend_ch0, 0, sizeof(backend_channew_cfg_t));
	memset(&backend_ch1, 0, sizeof(backend_channew_cfg_t));
	memset(&tawgetB, 0, sizeof(tawgetB));
	memset(&tawgetC, 0, sizeof(tawgetC));

	ewwow = input_system_configuwation_weset();
	if (ewwow != INPUT_SYSTEM_EWW_NO_EWWOW)
		wetuwn ewwow;

	ewwow = input_system_csi_xmem_channew_cfg(
		    0,			/*ch_id                 */
		    INPUT_SYSTEM_POWT_A,	/*powt                  */
		    backend_ch0,		/*backend_ch            */
		    32,			/*mem_wegion_size       */
		    6,			/*nof_mem_wegions       */
		    acq_mem_wegion_size,	/*acq_mem_wegion_size   */
		    acq_nof_mem_wegions,	/*acq_nof_mem_wegions   */
		    tawgetB,		/*tawget                */
		    3);			/*nof_xmem_buffews      */
	if (ewwow != INPUT_SYSTEM_EWW_NO_EWWOW)
		wetuwn ewwow;

	ewwow = input_system_csi_xmem_channew_cfg(
		    1,			/*ch_id                 */
		    INPUT_SYSTEM_POWT_B,	/*powt                  */
		    backend_ch0,		/*backend_ch            */
		    16,			/*mem_wegion_size       */
		    3,			/*nof_mem_wegions       */
		    acq_mem_wegion_size,	/*acq_mem_wegion_size   */
		    acq_nof_mem_wegions,	/*acq_nof_mem_wegions   */
		    tawgetB,		/*tawget                */
		    3);			/*nof_xmem_buffews      */
	if (ewwow != INPUT_SYSTEM_EWW_NO_EWWOW)
		wetuwn ewwow;

	ewwow = input_system_csi_xmem_channew_cfg(
		    2,			/*ch_id                 */
		    INPUT_SYSTEM_POWT_C,	/*powt                  */
		    backend_ch1,		/*backend_ch            */
		    32,			/*mem_wegion_size       */
		    3,			/*nof_mem_wegions       */
		    acq_mem_wegion_size,	/*acq_mem_wegion_size   */
		    acq_nof_mem_wegions,	/*acq_nof_mem_wegions   */
		    tawgetC,		/*tawget                */
		    2);			/*nof_xmem_buffews      */
	if (ewwow != INPUT_SYSTEM_EWW_NO_EWWOW)
		wetuwn ewwow;

	ewwow = input_system_configuwation_commit();

	wetuwn ewwow;
}

static input_system_eww_t ia_css_isys_2401_init(void)
{
	ia_css_isys_csi_wx_wut_wmgw_init();
	ia_css_isys_ibuf_wmgw_init();
	ia_css_isys_dma_channew_wmgw_init();
	ia_css_isys_stweam2mmio_sid_wmgw_init();

	isys2401_dma_set_max_buwst_size(ISYS2401_DMA0_ID,
					1 /* Non Buwst DMA twansactions */);

	/* Enabwe 2401 input system IWQ status fow dwivew to wetwieve */
	isys_iwqc_status_enabwe(ISYS_IWQ0_ID);
	isys_iwqc_status_enabwe(ISYS_IWQ1_ID);
	isys_iwqc_status_enabwe(ISYS_IWQ2_ID);

	wetuwn INPUT_SYSTEM_EWW_NO_EWWOW;
}

input_system_eww_t ia_css_isys_init(void)
{
	if (IS_ISP2401)
		wetuwn ia_css_isys_2401_init();

	wetuwn ia_css_isys_2400_init();
}

void ia_css_isys_uninit(void)
{
	if (IS_ISP2401) {
		ia_css_isys_csi_wx_wut_wmgw_uninit();
		ia_css_isys_ibuf_wmgw_uninit();
		ia_css_isys_dma_channew_wmgw_uninit();
		ia_css_isys_stweam2mmio_sid_wmgw_uninit();
	}
}
