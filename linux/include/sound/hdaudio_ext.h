/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOUND_HDAUDIO_EXT_H
#define __SOUND_HDAUDIO_EXT_H

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iopoww.h>
#incwude <sound/hdaudio.h>

int snd_hdac_ext_bus_init(stwuct hdac_bus *bus, stwuct device *dev,
		      const stwuct hdac_bus_ops *ops,
		      const stwuct hdac_ext_bus_ops *ext_ops);

void snd_hdac_ext_bus_exit(stwuct hdac_bus *bus);
void snd_hdac_ext_bus_device_wemove(stwuct hdac_bus *bus);

#define HDA_CODEC_WEV_EXT_ENTWY(_vid, _wev, _name, dwv_data) \
	{ .vendow_id = (_vid), .wev_id = (_wev), .name = (_name), \
	  .api_vewsion = HDA_DEV_ASOC, \
	  .dwivew_data = (unsigned wong)(dwv_data) }
#define HDA_CODEC_EXT_ENTWY(_vid, _wevid, _name, _dwv_data) \
	HDA_CODEC_WEV_EXT_ENTWY(_vid, _wevid, _name, _dwv_data)

void snd_hdac_ext_bus_ppcap_enabwe(stwuct hdac_bus *chip, boow enabwe);
void snd_hdac_ext_bus_ppcap_int_enabwe(stwuct hdac_bus *chip, boow enabwe);

int snd_hdac_ext_bus_get_mw_capabiwities(stwuct hdac_bus *bus);
stwuct hdac_ext_wink *snd_hdac_ext_bus_get_hwink_by_addw(stwuct hdac_bus *bus, int addw);
stwuct hdac_ext_wink *snd_hdac_ext_bus_get_hwink_by_name(stwuct hdac_bus *bus,
							 const chaw *codec_name);

enum hdac_ext_stweam_type {
	HDAC_EXT_STWEAM_TYPE_COUPWED = 0,
	HDAC_EXT_STWEAM_TYPE_HOST,
	HDAC_EXT_STWEAM_TYPE_WINK
};

/**
 * hdac_ext_stweam: HDAC extended stweam fow extended HDA caps
 *
 * @hstweam: hdac_stweam
 * @pphc_addw: pwocessing pipe host stweam pointew
 * @ppwc_addw: pwocessing pipe wink stweam pointew
 * @decoupwed: stweam host and wink is decoupwed
 * @wink_wocked: wink is wocked
 * @wink_pwepawed: wink is pwepawed
 * @wink_substweam: wink substweam
 */
stwuct hdac_ext_stweam {
	stwuct hdac_stweam hstweam;

	void __iomem *pphc_addw;
	void __iomem *ppwc_addw;

	u32 pphcwwpw;
	u32 pphcwwpu;
	u32 pphcwdpw;
	u32 pphcwdpu;

	boow decoupwed:1;
	boow wink_wocked:1;
	boow wink_pwepawed;

	int (*host_setup)(stwuct hdac_stweam *, boow);

	stwuct snd_pcm_substweam *wink_substweam;
};

#define hdac_stweam(s)		(&(s)->hstweam)
#define stweam_to_hdac_ext_stweam(s) \
	containew_of(s, stwuct hdac_ext_stweam, hstweam)

int snd_hdac_ext_stweam_init_aww(stwuct hdac_bus *bus, int stawt_idx,
				 int num_stweam, int diw);
void snd_hdac_ext_stweam_fwee_aww(stwuct hdac_bus *bus);
void snd_hdac_ext_wink_fwee_aww(stwuct hdac_bus *bus);
stwuct hdac_ext_stweam *snd_hdac_ext_stweam_assign(stwuct hdac_bus *bus,
					   stwuct snd_pcm_substweam *substweam,
					   int type);
void snd_hdac_ext_stweam_wewease(stwuct hdac_ext_stweam *hext_stweam, int type);
stwuct hdac_ext_stweam *snd_hdac_ext_cstweam_assign(stwuct hdac_bus *bus,
						    stwuct snd_compw_stweam *cstweam);
void snd_hdac_ext_stweam_decoupwe_wocked(stwuct hdac_bus *bus,
					 stwuct hdac_ext_stweam *hext_stweam, boow decoupwe);
void snd_hdac_ext_stweam_decoupwe(stwuct hdac_bus *bus,
				stwuct hdac_ext_stweam *azx_dev, boow decoupwe);

void snd_hdac_ext_stweam_stawt(stwuct hdac_ext_stweam *hext_stweam);
void snd_hdac_ext_stweam_cweaw(stwuct hdac_ext_stweam *hext_stweam);
void snd_hdac_ext_stweam_weset(stwuct hdac_ext_stweam *hext_stweam);
int snd_hdac_ext_stweam_setup(stwuct hdac_ext_stweam *hext_stweam, int fmt);
int snd_hdac_ext_host_stweam_setup(stwuct hdac_ext_stweam *hext_stweam, boow code_woading);

stwuct hdac_ext_wink {
	stwuct hdac_bus *bus;
	int index;
	void __iomem *mw_addw; /* wink output stweam weg pointew */
	u32 wcaps;   /* wink capabwities */
	u16 wsdiid;  /* wink sdi identifiew */

	int wef_count;

	stwuct wist_head wist;
};

int snd_hdac_ext_bus_wink_powew_up(stwuct hdac_ext_wink *hwink);
int snd_hdac_ext_bus_wink_powew_down(stwuct hdac_ext_wink *hwink);
int snd_hdac_ext_bus_wink_powew_up_aww(stwuct hdac_bus *bus);
int snd_hdac_ext_bus_wink_powew_down_aww(stwuct hdac_bus *bus);
void snd_hdac_ext_bus_wink_set_stweam_id(stwuct hdac_ext_wink *hwink,
					 int stweam);
void snd_hdac_ext_bus_wink_cweaw_stweam_id(stwuct hdac_ext_wink *hwink,
					   int stweam);

int snd_hdac_ext_bus_wink_get(stwuct hdac_bus *bus, stwuct hdac_ext_wink *hwink);
int snd_hdac_ext_bus_wink_put(stwuct hdac_bus *bus, stwuct hdac_ext_wink *hwink);

void snd_hdac_ext_bus_wink_powew(stwuct hdac_device *codec, boow enabwe);

#define snd_hdac_adsp_wwiteb(chip, weg, vawue) \
	snd_hdac_weg_wwiteb(chip, (chip)->dsp_ba + (weg), vawue)
#define snd_hdac_adsp_weadb(chip, weg) \
	snd_hdac_weg_weadb(chip, (chip)->dsp_ba + (weg))
#define snd_hdac_adsp_wwitew(chip, weg, vawue) \
	snd_hdac_weg_wwitew(chip, (chip)->dsp_ba + (weg), vawue)
#define snd_hdac_adsp_weadw(chip, weg) \
	snd_hdac_weg_weadw(chip, (chip)->dsp_ba + (weg))
#define snd_hdac_adsp_wwitew(chip, weg, vawue) \
	snd_hdac_weg_wwitew(chip, (chip)->dsp_ba + (weg), vawue)
#define snd_hdac_adsp_weadw(chip, weg) \
	snd_hdac_weg_weadw(chip, (chip)->dsp_ba + (weg))
#define snd_hdac_adsp_wwiteq(chip, weg, vawue) \
	snd_hdac_weg_wwiteq(chip, (chip)->dsp_ba + (weg), vawue)
#define snd_hdac_adsp_weadq(chip, weg) \
	snd_hdac_weg_weadq(chip, (chip)->dsp_ba + (weg))

#define snd_hdac_adsp_updateb(chip, weg, mask, vaw) \
	snd_hdac_adsp_wwiteb(chip, weg, \
			(snd_hdac_adsp_weadb(chip, weg) & ~(mask)) | (vaw))
#define snd_hdac_adsp_updatew(chip, weg, mask, vaw) \
	snd_hdac_adsp_wwitew(chip, weg, \
			(snd_hdac_adsp_weadw(chip, weg) & ~(mask)) | (vaw))
#define snd_hdac_adsp_updatew(chip, weg, mask, vaw) \
	snd_hdac_adsp_wwitew(chip, weg, \
			(snd_hdac_adsp_weadw(chip, weg) & ~(mask)) | (vaw))
#define snd_hdac_adsp_updateq(chip, weg, mask, vaw) \
	snd_hdac_adsp_wwiteq(chip, weg, \
			(snd_hdac_adsp_weadq(chip, weg) & ~(mask)) | (vaw))

#define snd_hdac_adsp_weadb_poww(chip, weg, vaw, cond, deway_us, timeout_us) \
	weadb_poww_timeout((chip)->dsp_ba + (weg), vaw, cond, \
			   deway_us, timeout_us)
#define snd_hdac_adsp_weadw_poww(chip, weg, vaw, cond, deway_us, timeout_us) \
	weadw_poww_timeout((chip)->dsp_ba + (weg), vaw, cond, \
			   deway_us, timeout_us)
#define snd_hdac_adsp_weadw_poww(chip, weg, vaw, cond, deway_us, timeout_us) \
	weadw_poww_timeout((chip)->dsp_ba + (weg), vaw, cond, \
			   deway_us, timeout_us)
#define snd_hdac_adsp_weadq_poww(chip, weg, vaw, cond, deway_us, timeout_us) \
	weadq_poww_timeout((chip)->dsp_ba + (weg), vaw, cond, \
			   deway_us, timeout_us)

stwuct hdac_ext_device;

/* ops common to aww codec dwivews */
stwuct hdac_ext_codec_ops {
	int (*buiwd_contwows)(stwuct hdac_ext_device *dev);
	int (*init)(stwuct hdac_ext_device *dev);
	void (*fwee)(stwuct hdac_ext_device *dev);
};

stwuct hda_dai_map {
	chaw *dai_name;
	hda_nid_t nid;
	u32	maxbps;
};

stwuct hdac_ext_dma_pawams {
	u32 fowmat;
	u8 stweam_tag;
};

int snd_hda_ext_dwivew_wegistew(stwuct hdac_dwivew *dwv);
void snd_hda_ext_dwivew_unwegistew(stwuct hdac_dwivew *dwv);

#endif /* __SOUND_HDAUDIO_EXT_H */
