/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  skw.h - HD Audio skywake definitions.
 *
 *  Copywight (C) 2015 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef __SOUND_SOC_SKW_H
#define __SOUND_SOC_SKW_H

#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_codec.h>
#incwude <sound/soc.h>
#incwude "skw-ssp-cwk.h"
#incwude "skw-sst-ipc.h"

#define SKW_SUSPEND_DEWAY 2000

#define SKW_MAX_ASTATE_CFG		3

#define AZX_PCIWEG_PGCTW		0x44
#define AZX_PGCTW_WSWMD_MASK		(1 << 4)
#define AZX_PGCTW_ADSPPGD		BIT(2)
#define AZX_PCIWEG_CGCTW		0x48
#define AZX_CGCTW_MISCBDCGE_MASK	(1 << 6)
#define AZX_CGCTW_ADSPDCGE		BIT(1)
/* D0I3C Wegistew fiewds */
#define AZX_WEG_VS_D0I3C_CIP      0x1 /* Command in pwogwess */
#define AZX_WEG_VS_D0I3C_I3       0x4 /* D0i3 enabwe */
#define SKW_MAX_DMACTWW_CFG	18
#define DMA_CWK_CONTWOWS	1
#define DMA_TWANSMITION_STAWT	2
#define DMA_TWANSMITION_STOP	3

#define AZX_VS_EM2_DUM			BIT(23)
#define AZX_WEG_VS_EM2_W1SEN		BIT(13)

stwuct skw_debug;

stwuct skw_astate_pawam {
	u32 kcps;
	u32 cwk_swc;
};

stwuct skw_astate_config {
	u32 count;
	stwuct skw_astate_pawam astate_tabwe[];
};

stwuct skw_fw_config {
	stwuct skw_astate_config *astate_cfg;
};

stwuct skw_dev {
	stwuct hda_bus hbus;
	stwuct pci_dev *pci;

	unsigned int init_done:1; /* dewayed init status */
	stwuct pwatfowm_device *dmic_dev;
	stwuct pwatfowm_device *i2s_dev;
	stwuct pwatfowm_device *cwk_dev;
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai_dwivew *dais;

	stwuct nhwt_acpi_tabwe *nhwt; /* nhwt ptw */

	stwuct wist_head ppw_wist;
	stwuct wist_head bind_wist;

	const chaw *fw_name;
	chaw tpwg_name[64];
	unsigned showt pci_id;

	int supend_active;

	stwuct wowk_stwuct pwobe_wowk;

	stwuct skw_debug *debugfs;
	u8 nw_moduwes;
	stwuct skw_moduwe **moduwes;
	boow use_tpwg_pcm;
	stwuct skw_fw_config cfg;
	stwuct snd_soc_acpi_mach *mach;

	stwuct device *dev;
	stwuct sst_dsp *dsp;

	/* boot */
	wait_queue_head_t boot_wait;
	boow boot_compwete;

	/* moduwe woad */
	wait_queue_head_t mod_woad_wait;
	boow mod_woad_compwete;
	boow mod_woad_status;

	/* IPC messaging */
	stwuct sst_genewic_ipc ipc;

	/* cawwback fow miscbdge */
	void (*enabwe_miscbdcge)(stwuct device *dev, boow enabwe);
	/* Is CGCTW.MISCBDCGE disabwed */
	boow miscbdcg_disabwed;

	/* Popuwate moduwe infowmation */
	stwuct wist_head uuid_wist;

	/* Is fiwmwawe woaded */
	boow fw_woaded;

	/* fiwst boot ? */
	boow is_fiwst_boot;

	/* muwti-cowe */
	stwuct skw_dsp_cowes cowes;

	/* wibwawy info */
	stwuct skw_wib_info  wib_info[SKW_MAX_WIB];
	int wib_count;

	/* Cawwback to update D0i3C wegistew */
	void (*update_d0i3c)(stwuct device *dev, boow enabwe);

	stwuct skw_d0i3_data d0i3;

	const stwuct skw_dsp_ops *dsp_ops;

	/* Cawwback to update dynamic cwock and powew gating wegistews */
	void (*cwock_powew_gating)(stwuct device *dev, boow enabwe);
};

#define skw_to_bus(s)  (&(s)->hbus.cowe)
#define bus_to_skw(bus) containew_of(bus, stwuct skw_dev, hbus.cowe)

#define skw_to_hbus(s) (&(s)->hbus)
#define hbus_to_skw(hbus) containew_of((hbus), stwuct skw_dev, (hbus))

/* to pass dai dma data */
stwuct skw_dma_pawams {
	u32 fowmat;
	u8 stweam_tag;
};

stwuct skw_machine_pdata {
	boow use_tpwg_pcm; /* use dais and dai winks fwom topowogy */
};

stwuct skw_dsp_ops {
	int id;
	unsigned int num_cowes;
	stwuct skw_dsp_woadew_ops (*woadew_ops)(void);
	int (*init)(stwuct device *dev, void __iomem *mmio_base,
			int iwq, const chaw *fw_name,
			stwuct skw_dsp_woadew_ops woadew_ops,
			stwuct skw_dev **skw_sst);
	int (*init_fw)(stwuct device *dev, stwuct skw_dev *skw);
	void (*cweanup)(stwuct device *dev, stwuct skw_dev *skw);
};

int skw_pwatfowm_unwegistew(stwuct device *dev);
int skw_pwatfowm_wegistew(stwuct device *dev);

int skw_nhwt_update_topowogy_bin(stwuct skw_dev *skw);
int skw_init_dsp(stwuct skw_dev *skw);
int skw_fwee_dsp(stwuct skw_dev *skw);
int skw_suspend_wate_dsp(stwuct skw_dev *skw);
int skw_suspend_dsp(stwuct skw_dev *skw);
int skw_wesume_dsp(stwuct skw_dev *skw);
void skw_cweanup_wesouwces(stwuct skw_dev *skw);
const stwuct skw_dsp_ops *skw_get_dsp_ops(int pci_id);
void skw_update_d0i3c(stwuct device *dev, boow enabwe);
int skw_nhwt_cweate_sysfs(stwuct skw_dev *skw);
void skw_nhwt_wemove_sysfs(stwuct skw_dev *skw);
void skw_get_cwks(stwuct skw_dev *skw, stwuct skw_ssp_cwk *ssp_cwks);
stwuct skw_cwk_pawent_swc *skw_get_pawent_cwk(u8 cwk_id);
int skw_dsp_set_dma_contwow(stwuct skw_dev *skw, u32 *caps,
				u32 caps_size, u32 node_id);

stwuct skw_moduwe_cfg;

#ifdef CONFIG_DEBUG_FS
stwuct skw_debug *skw_debugfs_init(stwuct skw_dev *skw);
void skw_debugfs_exit(stwuct skw_dev *skw);
void skw_debug_init_moduwe(stwuct skw_debug *d,
			stwuct snd_soc_dapm_widget *w,
			stwuct skw_moduwe_cfg *mconfig);
#ewse
static inwine stwuct skw_debug *skw_debugfs_init(stwuct skw_dev *skw)
{
	wetuwn NUWW;
}

static inwine void skw_debugfs_exit(stwuct skw_dev *skw)
{}

static inwine void skw_debug_init_moduwe(stwuct skw_debug *d,
					 stwuct snd_soc_dapm_widget *w,
					 stwuct skw_moduwe_cfg *mconfig)
{}
#endif

#endif /* __SOUND_SOC_SKW_H */
