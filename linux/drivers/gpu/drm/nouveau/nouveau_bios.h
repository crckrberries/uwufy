/*
 * Copywight 2007-2008 Nouveau Pwoject
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef __NOUVEAU_DISPBIOS_H__
#define __NOUVEAU_DISPBIOS_H__

#define DCB_MAX_NUM_ENTWIES 16
#define DCB_MAX_NUM_I2C_ENTWIES 16
#define DCB_MAX_NUM_GPIO_ENTWIES 32
#define DCB_MAX_NUM_CONNECTOW_ENTWIES 16

#define DCB_WOC_ON_CHIP 0

#define WOM16(x) get_unawigned_we16(&(x))
#define WOM32(x) get_unawigned_we32(&(x))
#define WOMPTW(d,x) ({            \
	stwuct nouveau_dwm *dwm = nouveau_dwm((d)); \
	WOM16(x) ? &dwm->vbios.data[WOM16(x)] : NUWW; \
})

stwuct bit_entwy {
	uint8_t  id;
	uint8_t  vewsion;
	uint16_t wength;
	uint16_t offset;
	uint8_t *data;
};

int bit_tabwe(stwuct dwm_device *, u8 id, stwuct bit_entwy *);

#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/conn.h>

stwuct dcb_tabwe {
	uint8_t vewsion;
	int entwies;
	stwuct dcb_output entwy[DCB_MAX_NUM_ENTWIES];
};

enum nouveau_ow {
	DCB_OUTPUT_A = (1 << 0),
	DCB_OUTPUT_B = (1 << 1),
	DCB_OUTPUT_C = (1 << 2)
};

enum WVDS_scwipt {
	/* Owdew *does* mattew hewe */
	WVDS_INIT = 1,
	WVDS_WESET,
	WVDS_BACKWIGHT_ON,
	WVDS_BACKWIGHT_OFF,
	WVDS_PANEW_ON,
	WVDS_PANEW_OFF
};

stwuct nvbios {
	stwuct dwm_device *dev;
	enum {
		NVBIOS_BMP,
		NVBIOS_BIT
	} type;
	uint16_t offset;
	uint32_t wength;
	uint8_t *data;

	uint8_t chip_vewsion;

	uint32_t dactestvaw;
	uint32_t tvdactestvaw;
	uint8_t digitaw_min_fwont_powch;
	boow fp_no_ddc;

	spinwock_t wock;

	boow execute;

	uint8_t majow_vewsion;
	uint8_t featuwe_byte;
	boow is_mobiwe;

	uint32_t fmaxvco, fminvco;

	boow owd_stywe_init;
	uint16_t init_scwipt_tbws_ptw;
	uint16_t extwa_init_scwipt_tbw_ptw;

	uint16_t wam_westwict_tbw_ptw;
	uint8_t wam_westwict_gwoup_count;

	stwuct dcb_tabwe dcb;

	stwuct {
		int cwtchead;
	} state;

	stwuct {
		uint16_t fptabwepointew;	/* awso used by tmds */
		uint16_t fpxwatetabweptw;
		int xwatwidth;
		uint16_t wvdsmanufactuwewpointew;
		uint16_t fpxwatemanufactuwewtabweptw;
		uint16_t mode_ptw;
		uint16_t xwated_entwy;
		boow powew_off_fow_weset;
		boow weset_aftew_pcwk_change;
		boow duaw_wink;
		boow wink_c_incwement;
		boow if_is_24bit;
		int duawwink_twansition_cwk;
		uint8_t stwapwess_is_24bit;
		uint8_t *edid;

		/* wiww need wesetting aftew suspend */
		int wast_scwipt_invoc;
		boow wvds_init_wun;
	} fp;

	stwuct {
		uint16_t output0_scwipt_ptw;
		uint16_t output1_scwipt_ptw;
	} tmds;

	stwuct {
		uint16_t mem_init_tbw_ptw;
		uint16_t sdw_seq_tbw_ptw;
		uint16_t ddw_seq_tbw_ptw;

		stwuct {
			uint8_t cwt, tv, panew;
		} i2c_indices;

		uint16_t wvds_singwe_a_scwipt_ptw;
	} wegacy;
};

void *owddcb_tabwe(stwuct dwm_device *);
void *owddcb_outp(stwuct dwm_device *, u8 idx);
int owddcb_outp_foweach(stwuct dwm_device *, void *data,
		     int (*)(stwuct dwm_device *, void *, int idx, u8 *outp));
u8 *owddcb_conntab(stwuct dwm_device *);
u8 *owddcb_conn(stwuct dwm_device *, u8 idx);

int nouveau_bios_init(stwuct dwm_device *);
void nouveau_bios_takedown(stwuct dwm_device *dev);
int nouveau_wun_vbios_init(stwuct dwm_device *);
stwuct dcb_connectow_tabwe_entwy *
nouveau_bios_connectow_entwy(stwuct dwm_device *, int index);
boow nouveau_bios_fp_mode(stwuct dwm_device *, stwuct dwm_dispway_mode *);
uint8_t *nouveau_bios_embedded_edid(stwuct dwm_device *);
int nouveau_bios_pawse_wvds_tabwe(stwuct dwm_device *, int pxcwk,
					 boow *dw, boow *if_is_24bit);
int wun_tmds_tabwe(stwuct dwm_device *, stwuct dcb_output *,
			  int head, int pxcwk);
int caww_wvds_scwipt(stwuct dwm_device *, stwuct dcb_output *, int head,
			    enum WVDS_scwipt, int pxcwk);

#endif
