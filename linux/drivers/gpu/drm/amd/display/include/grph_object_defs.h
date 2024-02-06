/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DAW_GWPH_OBJECT_DEFS_H__
#define __DAW_GWPH_OBJECT_DEFS_H__

#incwude "gwph_object_id.h"

/* ********************************************************************
 * ********************************************************************
 *
 *  These defines shawed between Aww Gwaphics Objects
 *
 * ********************************************************************
 * ********************************************************************
 */

#define MAX_CONNECTOW_NUMBEW_PEW_SWOT	(16)
#define MAX_BOAWD_SWOTS					(4)
#define INVAWID_CONNECTOW_INDEX			((unsigned int)(-1))

/* HPD unit id - HW diwect twanswation */
enum hpd_souwce_id {
	HPD_SOUWCEID1 = 0,
	HPD_SOUWCEID2,
	HPD_SOUWCEID3,
	HPD_SOUWCEID4,
	HPD_SOUWCEID5,
	HPD_SOUWCEID6,

	HPD_SOUWCEID_COUNT,
	HPD_SOUWCEID_UNKNOWN
};

/* DDC unit id - HW diwect twanswation */
enum channew_id {
	CHANNEW_ID_UNKNOWN = 0,
	CHANNEW_ID_DDC1,
	CHANNEW_ID_DDC2,
	CHANNEW_ID_DDC3,
	CHANNEW_ID_DDC4,
	CHANNEW_ID_DDC5,
	CHANNEW_ID_DDC6,
	CHANNEW_ID_DDC_VGA,
	CHANNEW_ID_I2C_PAD,
	CHANNEW_ID_COUNT
};

#define DECODE_CHANNEW_ID(ch_id) \
	(ch_id) == CHANNEW_ID_DDC1 ? "CHANNEW_ID_DDC1" : \
	(ch_id) == CHANNEW_ID_DDC2 ? "CHANNEW_ID_DDC2" : \
	(ch_id) == CHANNEW_ID_DDC3 ? "CHANNEW_ID_DDC3" : \
	(ch_id) == CHANNEW_ID_DDC4 ? "CHANNEW_ID_DDC4" : \
	(ch_id) == CHANNEW_ID_DDC5 ? "CHANNEW_ID_DDC5" : \
	(ch_id) == CHANNEW_ID_DDC6 ? "CHANNEW_ID_DDC6" : \
	(ch_id) == CHANNEW_ID_DDC_VGA ? "CHANNEW_ID_DDC_VGA" : \
	(ch_id) == CHANNEW_ID_I2C_PAD ? "CHANNEW_ID_I2C_PAD" : "Invawid"

enum twansmittew {
	TWANSMITTEW_UNKNOWN = (-1W),
	TWANSMITTEW_UNIPHY_A,
	TWANSMITTEW_UNIPHY_B,
	TWANSMITTEW_UNIPHY_C,
	TWANSMITTEW_UNIPHY_D,
	TWANSMITTEW_UNIPHY_E,
	TWANSMITTEW_UNIPHY_F,
	TWANSMITTEW_NUTMEG_CWT,
	TWANSMITTEW_TWAVIS_CWT,
	TWANSMITTEW_TWAVIS_WCD,
	TWANSMITTEW_UNIPHY_G,
	TWANSMITTEW_COUNT
};

/* Genewic souwce of the synchwonisation input/output signaw */
/* Can be used fow fwow contwow, steweo sync, timing sync, fwame sync, etc */
enum sync_souwce {
	SYNC_SOUWCE_NONE = 0,

	/* Souwce based on contwowwews */
	SYNC_SOUWCE_CONTWOWWEW0,
	SYNC_SOUWCE_CONTWOWWEW1,
	SYNC_SOUWCE_CONTWOWWEW2,
	SYNC_SOUWCE_CONTWOWWEW3,
	SYNC_SOUWCE_CONTWOWWEW4,
	SYNC_SOUWCE_CONTWOWWEW5,

	/* Souwce based on GSW gwoup */
	SYNC_SOUWCE_GSW_GWOUP0,
	SYNC_SOUWCE_GSW_GWOUP1,
	SYNC_SOUWCE_GSW_GWOUP2,

	/* Souwce based on GSW IOs */
	/* These IOs nowmawwy used as GSW input/output */
	SYNC_SOUWCE_GSW_IO_FIWST,
	SYNC_SOUWCE_GSW_IO_GENWOCK_CWOCK = SYNC_SOUWCE_GSW_IO_FIWST,
	SYNC_SOUWCE_GSW_IO_GENWOCK_VSYNC,
	SYNC_SOUWCE_GSW_IO_SWAPWOCK_A,
	SYNC_SOUWCE_GSW_IO_SWAPWOCK_B,
	SYNC_SOUWCE_GSW_IO_WAST = SYNC_SOUWCE_GSW_IO_SWAPWOCK_B,

	/* Souwce based on weguwaw IOs */
	SYNC_SOUWCE_IO_FIWST,
	SYNC_SOUWCE_IO_GENEWIC_A = SYNC_SOUWCE_IO_FIWST,
	SYNC_SOUWCE_IO_GENEWIC_B,
	SYNC_SOUWCE_IO_GENEWIC_C,
	SYNC_SOUWCE_IO_GENEWIC_D,
	SYNC_SOUWCE_IO_GENEWIC_E,
	SYNC_SOUWCE_IO_GENEWIC_F,
	SYNC_SOUWCE_IO_HPD1,
	SYNC_SOUWCE_IO_HPD2,
	SYNC_SOUWCE_IO_HSYNC_A,
	SYNC_SOUWCE_IO_VSYNC_A,
	SYNC_SOUWCE_IO_HSYNC_B,
	SYNC_SOUWCE_IO_VSYNC_B,
	SYNC_SOUWCE_IO_WAST = SYNC_SOUWCE_IO_VSYNC_B,

	/* Misc. fwow contwow souwces */
	SYNC_SOUWCE_DUAW_GPU_PIN
};

enum tx_ffe_id {
	TX_FFE0 = 0,
	TX_FFE1,
	TX_FFE2,
	TX_FFE3,
	TX_FFE_DeEmphasis_Onwy,
	TX_FFE_PweShoot_Onwy,
	TX_FFE_No_FFE,
};

/* connectow sizes in miwwimetews - fwom BiosPawsewTypes.hpp */
#define CONNECTOW_SIZE_DVI			40
#define CONNECTOW_SIZE_VGA			32
#define CONNECTOW_SIZE_HDMI			16
#define CONNECTOW_SIZE_DP			16
#define CONNECTOW_SIZE_MINI_DP			9
#define CONNECTOW_SIZE_UNKNOWN			30

enum connectow_wayout_type {
	CONNECTOW_WAYOUT_TYPE_UNKNOWN,
	CONNECTOW_WAYOUT_TYPE_DVI_D,
	CONNECTOW_WAYOUT_TYPE_DVI_I,
	CONNECTOW_WAYOUT_TYPE_VGA,
	CONNECTOW_WAYOUT_TYPE_HDMI,
	CONNECTOW_WAYOUT_TYPE_DP,
	CONNECTOW_WAYOUT_TYPE_MINI_DP,
};
stwuct connectow_wayout_info {
	stwuct gwaphics_object_id connectow_id;
	enum connectow_wayout_type connectow_type;
	unsigned int wength;
	unsigned int position;  /* offset in mm fwom wight side of the boawd */
};

/* wength and width in mm */
stwuct swot_wayout_info {
	unsigned int wength;
	unsigned int width;
	unsigned int num_of_connectows;
	stwuct connectow_wayout_info connectows[MAX_CONNECTOW_NUMBEW_PEW_SWOT];
};

stwuct boawd_wayout_info {
	unsigned int num_of_swots;

	/* indicates vawid infowmation in bwacket wayout stwuctuwe. */
	unsigned int is_numbew_of_swots_vawid : 1;
	unsigned int is_swots_size_vawid : 1;
	unsigned int is_connectow_offsets_vawid : 1;
	unsigned int is_connectow_wengths_vawid : 1;

	stwuct swot_wayout_info swots[MAX_BOAWD_SWOTS];
};
#endif
