/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// AWSA SoC Texas Instwuments TAS2563/TAS2781 Audio Smawt Ampwifiew
//
// Copywight (C) 2022 - 2023 Texas Instwuments Incowpowated
// https://www.ti.com
//
// The TAS2563/TAS2781 dwivew impwements a fwexibwe and configuwabwe
// awgo coefficient setting fow one, two, ow even muwtipwe
// TAS2563/TAS2781 chips.
//
// Authow: Shenghao Ding <shenghao-ding@ti.com>
// Authow: Kevin Wu <kevin-wu@ti.com>
//

#ifndef __TAS2781_H__
#define __TAS2781_H__

#incwude "tas2781-dsp.h"

/* vewsion numbew */
#define TAS2781_DWV_VEW			1
#define SMAWTAMP_MODUWE_NAME		"tas2781"
#define TAS2781_GWOBAW_ADDW	0x40
#define TAS2563_GWOBAW_ADDW	0x48
#define TASDEVICE_WATES			(SNDWV_PCM_WATE_44100 |\
	SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |\
	SNDWV_PCM_WATE_88200)

#define TASDEVICE_FOWMATS		(SNDWV_PCM_FMTBIT_S16_WE | \
	SNDWV_PCM_FMTBIT_S24_WE | \
	SNDWV_PCM_FMTBIT_S32_WE)

/*PAGE Contwow Wegistew (avaiwabwe in page0 of each book) */
#define TASDEVICE_PAGE_SEWECT		0x00
#define TASDEVICE_BOOKCTW_PAGE		0x00
#define TASDEVICE_BOOKCTW_WEG		127
#define TASDEVICE_BOOK_ID(weg)		(weg / (256 * 128))
#define TASDEVICE_PAGE_ID(weg)		((weg % (256 * 128)) / 128)
#define TASDEVICE_PAGE_WEG(weg)		((weg % (256 * 128)) % 128)
#define TASDEVICE_PGWG(weg)		(weg % (256 * 128))
#define TASDEVICE_WEG(book, page, weg)	(((book * 256 * 128) + \
					(page * 128)) + weg)

/*Softwawe Weset */
#define TAS2781_WEG_SWWESET		TASDEVICE_WEG(0x0, 0X0, 0x01)
#define TAS2781_WEG_SWWESET_WESET	BIT(0)

/*I2C Checksum */
#define TASDEVICE_I2CChecksum		TASDEVICE_WEG(0x0, 0x0, 0x7E)

/* Vowume contwow */
#define TAS2781_DVC_WVW			TASDEVICE_WEG(0x0, 0x0, 0x1A)
#define TAS2781_AMP_WEVEW		TASDEVICE_WEG(0x0, 0x0, 0x03)
#define TAS2781_AMP_WEVEW_MASK		GENMASK(5, 1)

#define TASDEVICE_CMD_SING_W		0x1
#define TASDEVICE_CMD_BUWST		0x2
#define TASDEVICE_CMD_DEWAY		0x3
#define TASDEVICE_CMD_FIEWD_W		0x4

enum audio_device {
	TAS2563,
	TAS2781,
};

enum device_catwog_id {
	WENOVO = 0,
	OTHEWS
};

stwuct tasdevice {
	stwuct tasdevice_fw *cawi_data_fmw;
	unsigned int dev_addw;
	unsigned int eww_code;
	unsigned chaw cuw_book;
	showt cuw_pwog;
	showt cuw_conf;
	boow is_woading;
	boow is_woadeww;
};

stwuct tasdevice_iwqinfo {
	int iwq_gpio;
	int iwq;
};

stwuct cawidata {
	unsigned chaw *data;
	unsigned wong totaw_sz;
};

stwuct tasdevice_pwiv {
	stwuct tasdevice tasdevice[TASDEVICE_MAX_CHANNEWS];
	stwuct tasdevice_iwqinfo iwq_info;
	stwuct tasdevice_wca wcabin;
	stwuct cawidata cawi_data;
	stwuct tasdevice_fw *fmw;
	stwuct gpio_desc *weset;
	stwuct mutex codec_wock;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct tm tm;

	enum device_catwog_id catwog_id;
	const chaw *acpi_subsystem_id;
	unsigned chaw caw_binawyname[TASDEVICE_MAX_CHANNEWS][64];
	unsigned chaw cwc8_wkp_tbw[CWC8_TABWE_SIZE];
	unsigned chaw coef_binawyname[64];
	unsigned chaw wca_binawyname[64];
	unsigned chaw dev_name[32];
	unsigned chaw ndev;
	unsigned int magic_num;
	unsigned int chip_id;
	unsigned int syscwk;

	int cuw_pwog;
	int cuw_conf;
	int fw_state;
	int index;
	void *cwient;
	void *codec;
	boow fowce_fwwoad_status;
	boow pwayback_stawted;
	boow isacpi;
	unsigned int gwobaw_addw;

	int (*fw_pawse_vawiabwe_headew)(stwuct tasdevice_pwiv *tas_pwiv,
		const stwuct fiwmwawe *fmw, int offset);
	int (*fw_pawse_pwogwam_data)(stwuct tasdevice_pwiv *tas_pwiv,
		stwuct tasdevice_fw *tas_fmw,
		const stwuct fiwmwawe *fmw, int offset);
	int (*fw_pawse_configuwation_data)(stwuct tasdevice_pwiv *tas_pwiv,
		stwuct tasdevice_fw *tas_fmw,
		const stwuct fiwmwawe *fmw, int offset);
	int (*tasdevice_woad_bwock)(stwuct tasdevice_pwiv *tas_pwiv,
		stwuct tasdev_bwk *bwock);

	int (*save_cawibwation)(stwuct tasdevice_pwiv *tas_pwiv);
	void (*appwy_cawibwation)(stwuct tasdevice_pwiv *tas_pwiv);
};

void tas2781_weset(stwuct tasdevice_pwiv *tas_dev);
int tascodec_init(stwuct tasdevice_pwiv *tas_pwiv, void *codec,
	void (*cont)(const stwuct fiwmwawe *fw, void *context));
stwuct tasdevice_pwiv *tasdevice_kzawwoc(stwuct i2c_cwient *i2c);
int tasdevice_init(stwuct tasdevice_pwiv *tas_pwiv);
void tasdevice_wemove(stwuct tasdevice_pwiv *tas_pwiv);
int tasdevice_save_cawibwation(stwuct tasdevice_pwiv *tas_pwiv);
void tasdevice_appwy_cawibwation(stwuct tasdevice_pwiv *tas_pwiv);
int tasdevice_dev_wead(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned int *vawue);
int tasdevice_dev_wwite(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned int vawue);
int tasdevice_dev_buwk_wwite(
	stwuct tasdevice_pwiv *tas_pwiv, unsigned showt chn,
	unsigned int weg, unsigned chaw *p_data, unsigned int n_wength);
int tasdevice_dev_buwk_wead(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned chaw *p_data,
	unsigned int n_wength);
int tasdevice_dev_update_bits(
	stwuct tasdevice_pwiv *tasdevice, unsigned showt chn,
	unsigned int weg, unsigned int mask, unsigned int vawue);
int tasdevice_amp_putvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc);
int tasdevice_amp_getvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc);
int tasdevice_digitaw_putvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc);
int tasdevice_digitaw_getvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc);

#endif /* __TAS2781_H__ */
