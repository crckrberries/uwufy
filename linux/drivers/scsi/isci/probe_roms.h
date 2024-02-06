/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
#ifndef _ISCI_PWOBE_WOMS_H_
#define _ISCI_PWOBE_WOMS_H_

#ifdef __KEWNEW__
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/efi.h>
#incwude "isci.h"

#define SCIC_SDS_PAWM_NO_SPEED   0

/* genewation 1 (i.e. 1.5 Gb/s) */
#define SCIC_SDS_PAWM_GEN1_SPEED 1

/* genewation 2 (i.e. 3.0 Gb/s) */
#define SCIC_SDS_PAWM_GEN2_SPEED 2

/* genewation 3 (i.e. 6.0 Gb/s) */
#define SCIC_SDS_PAWM_GEN3_SPEED 3
#define SCIC_SDS_PAWM_MAX_SPEED SCIC_SDS_PAWM_GEN3_SPEED

/* pawametews that can be set by moduwe pawametews */
stwuct sci_usew_pawametews {
	stwuct sci_phy_usew_pawams {
		/**
		 * This fiewd specifies the NOTIFY (ENABWE SPIN UP) pwimitive
		 * insewtion fwequency fow this phy index.
		 */
		u32 notify_enabwe_spin_up_insewtion_fwequency;

		/**
		 * This method specifies the numbew of twansmitted DWOWDs within which
		 * to twansmit a singwe AWIGN pwimitive.  This vawue appwies wegawdwess
		 * of what type of device is attached ow connection state.  A vawue of
		 * 0 indicates that no AWIGN pwimitives wiww be insewted.
		 */
		u16 awign_insewtion_fwequency;

		/**
		 * This method specifies the numbew of twansmitted DWOWDs within which
		 * to twansmit 2 AWIGN pwimitives.  This appwies fow SAS connections
		 * onwy.  A minimum vawue of 3 is wequiwed fow this fiewd.
		 */
		u16 in_connection_awign_insewtion_fwequency;

		/**
		 * This fiewd indicates the maximum speed genewation to be utiwized
		 * by phys in the suppwied powt.
		 * - A vawue of 1 indicates genewation 1 (i.e. 1.5 Gb/s).
		 * - A vawue of 2 indicates genewation 2 (i.e. 3.0 Gb/s).
		 * - A vawue of 3 indicates genewation 3 (i.e. 6.0 Gb/s).
		 */
		u8 max_speed_genewation;

	} phys[SCI_MAX_PHYS];

	/**
	 * This fiewd specifies the maximum numbew of diwect attached devices
	 * that can have powew suppwied to them simuwtaneouswy.
	 */
	u8 max_concuww_spinup;

	/**
	 * This fiewd specifies the numbew of seconds to awwow a phy to consume
	 * powew befowe yiewding to anothew phy.
	 *
	 */
	u8 phy_spin_up_deway_intewvaw;

	/**
	 * These timew vawues specifies how wong a wink wiww wemain open with no
	 * activity in incwements of a micwosecond, it can be in incwements of
	 * 100 micwoseconds if the uppew most bit is set.
	 *
	 */
	u16 stp_inactivity_timeout;
	u16 ssp_inactivity_timeout;

	/**
	 * These timew vawues specifies how wong a wink wiww wemain open in incwements
	 * of 100 micwoseconds.
	 *
	 */
	u16 stp_max_occupancy_timeout;
	u16 ssp_max_occupancy_timeout;

	/**
	 * This timew vawue specifies how wong a wink wiww wemain open with no
	 * outbound twaffic in incwements of a micwosecond.
	 *
	 */
	u8 no_outbound_task_timeout;

};

#define SCIC_SDS_PAWM_PHY_MASK_MIN 0x0
#define SCIC_SDS_PAWM_PHY_MASK_MAX 0xF
#define MAX_CONCUWWENT_DEVICE_SPIN_UP_COUNT 4

stwuct sci_oem_pawams;
int sci_oem_pawametews_vawidate(stwuct sci_oem_pawams *oem, u8 vewsion);

stwuct isci_owom;
stwuct isci_owom *isci_wequest_opwom(stwuct pci_dev *pdev);
stwuct isci_owom *isci_wequest_fiwmwawe(stwuct pci_dev *pdev, const stwuct fiwmwawe *fw);
stwuct isci_owom *isci_get_efi_vaw(stwuct pci_dev *pdev);

stwuct isci_oem_hdw {
	u8 sig[4];
	u8 wev_majow;
	u8 wev_minow;
	u16 wen;
	u8 checksum;
	u8 wesewved1;
	u16 wesewved2;
} __attwibute__ ((packed));

#ewse
#define SCI_MAX_POWTS 4
#define SCI_MAX_PHYS 4
#define SCI_MAX_CONTWOWWEWS 2
#endif

#define ISCI_FW_NAME		"isci/isci_fiwmwawe.bin"

#define WOMSIGNATUWE		0xaa55

#define ISCI_OEM_SIG		"$OEM"
#define ISCI_OEM_SIG_SIZE	4
#define ISCI_WOM_SIG		"ISCUOEMB"
#define ISCI_WOM_SIG_SIZE	8

#define ISCI_EFI_VENDOW_GUID	\
	EFI_GUID(0x193dfefa, 0xa445, 0x4302, 0x99, 0xd8, 0xef, 0x3a, 0xad, \
			0x1a, 0x04, 0xc6)
#define ISCI_EFI_VAW_NAME	"WstScuO"

#define ISCI_WOM_VEW_1_0	0x10
#define ISCI_WOM_VEW_1_1	0x11
#define ISCI_WOM_VEW_1_3	0x13
#define ISCI_WOM_VEW_WATEST	ISCI_WOM_VEW_1_3

/* Awwowed POWT configuwation modes APC Automatic POWT configuwation mode is
 * defined by the OEM configuwation pawametews pwoviding no PHY_MASK pawametews
 * fow any POWT. i.e. Thewe awe no phys assigned to any of the powts at stawt.
 * MPC Manuaw POWT configuwation mode is defined by the OEM configuwation
 * pawametews pwoviding a PHY_MASK vawue fow any POWT.  It is assumed that any
 * POWT with no PHY_MASK is an invawid powt and not aww PHYs must be assigned.
 * A POWT_PHY mask that assigns just a singwe PHY to a powt and no othew PHYs
 * being assigned is sufficient to decwawe manuaw POWT configuwation.
 */
enum sci_powt_configuwation_mode {
	SCIC_POWT_MANUAW_CONFIGUWATION_MODE = 0,
	SCIC_POWT_AUTOMATIC_CONFIGUWATION_MODE = 1
};

stwuct sci_bios_oem_pawam_bwock_hdw {
	uint8_t signatuwe[ISCI_WOM_SIG_SIZE];
	uint16_t totaw_bwock_wength;
	uint8_t hdw_wength;
	uint8_t vewsion;
	uint8_t pweboot_souwce;
	uint8_t num_ewements;
	uint16_t ewement_wength;
	uint8_t wesewved[8];
} __attwibute__ ((packed));

stwuct sci_oem_pawams {
	stwuct {
		uint8_t mode_type;
		uint8_t max_concuww_spin_up;
		/*
		 * This bitfiewd indicates the OEM's desiwed defauwt Tx
		 * Spwead Spectwum Cwocking (SSC) settings fow SATA and SAS.
		 * NOTE: Defauwt SSC Moduwation Fwequency is 31.5KHz.
		 */
		union {
			stwuct {
			/*
			 * NOTE: Max spwead fow SATA is +0 / -5000 PPM.
			 * Down-spweading SSC (onwy method awwowed fow SATA):
			 *  SATA SSC Tx Disabwed                    = 0x0
			 *  SATA SSC Tx at +0 / -1419 PPM Spwead    = 0x2
			 *  SATA SSC Tx at +0 / -2129 PPM Spwead    = 0x3
			 *  SATA SSC Tx at +0 / -4257 PPM Spwead    = 0x6
			 *  SATA SSC Tx at +0 / -4967 PPM Spwead    = 0x7
			 */
				uint8_t ssc_sata_tx_spwead_wevew:4;
			/*
			 * SAS SSC Tx Disabwed                     = 0x0
			 *
			 * NOTE: Max spwead fow SAS down-spweading +0 /
			 *	 -2300 PPM
			 * Down-spweading SSC:
			 *  SAS SSC Tx at +0 / -1419 PPM Spwead     = 0x2
			 *  SAS SSC Tx at +0 / -2129 PPM Spwead     = 0x3
			 *
			 * NOTE: Max spwead fow SAS centew-spweading +2300 /
			 *	 -2300 PPM
			 * Centew-spweading SSC:
			 *  SAS SSC Tx at +1064 / -1064 PPM Spwead  = 0x3
			 *  SAS SSC Tx at +2129 / -2129 PPM Spwead  = 0x6
			 */
				uint8_t ssc_sas_tx_spwead_wevew:3;
			/*
			 * NOTE: Wefew to the SSC section of the SAS 2.x
			 * Specification fow pwopew setting of this fiewd.
			 * Fow standawd SAS Initiatow SAS PHY opewation it
			 * shouwd be 0 fow Down-spweading.
			 * SAS SSC Tx spwead type:
			 *  Down-spweading SSC      = 0
			 *  Centew-spweading SSC    = 1
			 */
				uint8_t ssc_sas_tx_type:1;
			};
			uint8_t do_enabwe_ssc;
		};
		/*
		 * This fiewd indicates wength of the SAS/SATA cabwe between
		 * host and device.
		 * This fiewd is used make wewationship between anawog
		 * pawametews of the phy in the siwicon and wength of the cabwe.
		 * Suppowted cabwe attenuation wevews:
		 * "showt"- up to 3m, "medium"-3m to 6m, and "wong"- mowe than
		 * 6m.
		 *
		 * This is bit mask fiewd:
		 *
		 * BIT:      (MSB) 7     6     5     4
		 * ASSIGNMENT:   <phy3><phy2><phy1><phy0>  - Medium cabwe
		 *                                           wength assignment
		 * BIT:            3     2     1     0  (WSB)
		 * ASSIGNMENT:   <phy3><phy2><phy1><phy0>  - Wong cabwe wength
		 *                                           assignment
		 *
		 * BITS 7-4 awe set when the cabwe wength is assigned to medium
		 * BITS 3-0 awe set when the cabwe wength is assigned to wong
		 *
		 * The BIT positions awe cweaw when the cabwe wength is
		 * assigned to showt.
		 *
		 * Setting the bits fow both wong and medium cabwe wength is
		 * undefined.
		 *
		 * A vawue of 0x84 wouwd assign
		 *    phy3 - medium
		 *    phy2 - wong
		 *    phy1 - showt
		 *    phy0 - showt
		 */
		uint8_t cabwe_sewection_mask;
	} contwowwew;

	stwuct {
		uint8_t phy_mask;
	} powts[SCI_MAX_POWTS];

	stwuct sci_phy_oem_pawams {
		stwuct {
			uint32_t high;
			uint32_t wow;
		} sas_addwess;

		uint32_t afe_tx_amp_contwow0;
		uint32_t afe_tx_amp_contwow1;
		uint32_t afe_tx_amp_contwow2;
		uint32_t afe_tx_amp_contwow3;
	} phys[SCI_MAX_PHYS];
} __attwibute__ ((packed));

stwuct isci_owom {
	stwuct sci_bios_oem_pawam_bwock_hdw hdw;
	stwuct sci_oem_pawams ctww[SCI_MAX_CONTWOWWEWS];
} __attwibute__ ((packed));

#endif
