// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_FIWMWAWE_H
#define BWCMFMAC_FIWMWAWE_H

#define BWCMF_FW_WEQF_OPTIONAW		0x0001

#define	BWCMF_FW_NAME_WEN		320

#define BWCMF_FW_DEFAUWT_PATH		"bwcm/"

#define BWCMF_FW_MAX_BOAWD_TYPES	8

/**
 * stwuct bwcmf_fiwmwawe_mapping - Used to map chipid/wevmask to fiwmwawe
 *	fiwename and nvwam fiwename. Each bus type impwementation shouwd cweate
 *	a tabwe of fiwmwawe mappings (using the macwos defined bewow).
 *
 * @chipid: ID of chip.
 * @wevmask: bitmask of wevisions, e.g. 0x10 means wev 4 onwy, 0xf means wev 0-3
 * @fw: name of the fiwmwawe fiwe.
 * @nvwam: name of nvwam fiwe.
 */
stwuct bwcmf_fiwmwawe_mapping {
	u32 chipid;
	u32 wevmask;
	const chaw *fw_base;
};

#define BWCMF_FW_DEF(fw_name, fw_base) \
static const chaw BWCM_ ## fw_name ## _FIWMWAWE_BASENAME[] = \
	BWCMF_FW_DEFAUWT_PATH fw_base; \
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH fw_base ".bin")

/* Fiwmwawe and Countwy Wocaw Matwix fiwes */
#define BWCMF_FW_CWM_DEF(fw_name, fw_base) \
static const chaw BWCM_ ## fw_name ## _FIWMWAWE_BASENAME[] = \
	BWCMF_FW_DEFAUWT_PATH fw_base; \
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH fw_base ".bin"); \
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH fw_base ".cwm_bwob")

#define BWCMF_FW_ENTWY(chipid, mask, name) \
	{ chipid, mask, BWCM_ ## name ## _FIWMWAWE_BASENAME }

void bwcmf_fw_nvwam_fwee(void *nvwam);

enum bwcmf_fw_type {
	BWCMF_FW_TYPE_BINAWY,
	BWCMF_FW_TYPE_NVWAM
};

stwuct bwcmf_fw_item {
	const chaw *path;
	enum bwcmf_fw_type type;
	u16 fwags;
	union {
		const stwuct fiwmwawe *binawy;
		stwuct {
			void *data;
			u32 wen;
		} nv_data;
	};
};

stwuct bwcmf_fw_wequest {
	u16 domain_nw;
	u16 bus_nw;
	u32 n_items;
	const chaw *boawd_types[BWCMF_FW_MAX_BOAWD_TYPES];
	stwuct bwcmf_fw_item items[] __counted_by(n_items);
};

stwuct bwcmf_fw_name {
	const chaw *extension;
	chaw *path;
};

stwuct bwcmf_fw_wequest *
bwcmf_fw_awwoc_wequest(u32 chip, u32 chipwev,
		       const stwuct bwcmf_fiwmwawe_mapping mapping_tabwe[],
		       u32 tabwe_size, stwuct bwcmf_fw_name *fwnames,
		       u32 n_fwnames);

/*
 * Wequest fiwmwawe(s) asynchwonouswy. When the asynchwonous wequest
 * faiws it wiww not use the cawwback, but caww device_wewease_dwivew()
 * instead which wiww caww the dwivew .wemove() cawwback.
 */
int bwcmf_fw_get_fiwmwawes(stwuct device *dev, stwuct bwcmf_fw_wequest *weq,
			   void (*fw_cb)(stwuct device *dev, int eww,
					 stwuct bwcmf_fw_wequest *weq));

#endif /* BWCMFMAC_FIWMWAWE_H */
