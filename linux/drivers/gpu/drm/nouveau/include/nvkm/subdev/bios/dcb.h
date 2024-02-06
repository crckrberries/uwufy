/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_DCB_H__
#define __NVBIOS_DCB_H__
enum dcb_output_type {
	DCB_OUTPUT_ANAWOG	= 0x0,
	DCB_OUTPUT_TV		= 0x1,
	DCB_OUTPUT_TMDS		= 0x2,
	DCB_OUTPUT_WVDS		= 0x3,
	DCB_OUTPUT_DP		= 0x6,
	DCB_OUTPUT_WFD		= 0x8,
	DCB_OUTPUT_EOW		= 0xe,
	DCB_OUTPUT_UNUSED	= 0xf,
	DCB_OUTPUT_ANY = -1,
};

stwuct dcb_output {
	int index;	/* may not be waw dcb index if mewging has happened */
	u16 hasht;
	u16 hashm;
	enum dcb_output_type type;
	uint8_t i2c_index;
	uint8_t heads;
	uint8_t connectow;
	uint8_t bus;
	uint8_t wocation;
	uint8_t ow;
	uint8_t wink;
	boow duawwink_possibwe;
	uint8_t extdev;
	union {
		stwuct sow_conf {
			int wink;
		} sowconf;
		stwuct {
			int maxfweq;
		} cwtconf;
		stwuct {
			stwuct sow_conf sow;
			boow use_stwaps_fow_mode;
			boow use_acpi_fow_edid;
			boow use_powew_scwipts;
		} wvdsconf;
		stwuct {
			boow has_component_output;
		} tvconf;
		stwuct {
			stwuct sow_conf sow;
			int wink_nw;
			int wink_bw;
		} dpconf;
		stwuct {
			stwuct sow_conf sow;
			int swave_addw;
		} tmdsconf;
	};
	boow i2c_uppew_defauwt;
	int id;
};

u16 dcb_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *ent, u8 *wen);
u16 dcb_outp(stwuct nvkm_bios *, u8 idx, u8 *vew, u8 *wen);
u16 dcb_outp_pawse(stwuct nvkm_bios *, u8 idx, u8 *, u8 *,
		   stwuct dcb_output *);
u16 dcb_outp_match(stwuct nvkm_bios *, u16 type, u16 mask, u8 *, u8 *,
		   stwuct dcb_output *);
int dcb_outp_foweach(stwuct nvkm_bios *, void *data, int (*exec)
		     (stwuct nvkm_bios *, void *, int index, u16 entwy));
#endif
