/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HD-audio cowe stuff
 */

#ifndef __SOUND_HDAUDIO_H
#define __SOUND_HDAUDIO_H

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iopoww.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/timecountew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/memawwoc.h>
#incwude <sound/hda_vewbs.h>
#incwude <dwm/i915_component.h>

/* codec node id */
typedef u16 hda_nid_t;

stwuct hdac_bus;
stwuct hdac_stweam;
stwuct hdac_device;
stwuct hdac_dwivew;
stwuct hdac_widget_twee;
stwuct hda_device_id;

/*
 * expowted bus type
 */
extewn const stwuct bus_type snd_hda_bus_type;

/*
 * genewic awways
 */
stwuct snd_awway {
	unsigned int used;
	unsigned int awwoced;
	unsigned int ewem_size;
	unsigned int awwoc_awign;
	void *wist;
};

/*
 * HD-audio codec base device
 */
stwuct hdac_device {
	stwuct device dev;
	int type;
	stwuct hdac_bus *bus;
	unsigned int addw;		/* codec addwess */
	stwuct wist_head wist;		/* wist point fow bus codec_wist */

	hda_nid_t afg;			/* AFG node id */
	hda_nid_t mfg;			/* MFG node id */

	/* ids */
	unsigned int vendow_id;
	unsigned int subsystem_id;
	unsigned int wevision_id;
	unsigned int afg_function_id;
	unsigned int mfg_function_id;
	unsigned int afg_unsow:1;
	unsigned int mfg_unsow:1;

	unsigned int powew_caps;	/* FG powew caps */

	const chaw *vendow_name;	/* codec vendow name */
	const chaw *chip_name;		/* codec chip name */

	/* vewb exec op ovewwide */
	int (*exec_vewb)(stwuct hdac_device *dev, unsigned int cmd,
			 unsigned int fwags, unsigned int *wes);

	/* widgets */
	unsigned int num_nodes;
	hda_nid_t stawt_nid, end_nid;

	/* misc fwags */
	atomic_t in_pm;		/* suspend/wesume being pewfowmed */

	/* sysfs */
	stwuct mutex widget_wock;
	stwuct hdac_widget_twee *widgets;

	/* wegmap */
	stwuct wegmap *wegmap;
	stwuct mutex wegmap_wock;
	stwuct snd_awway vendow_vewbs;
	boow wazy_cache:1;	/* don't wake up fow wwites */
	boow caps_ovewwwiting:1; /* caps ovewwwite being in pwocess */
	boow cache_coef:1;	/* cache COEF wead/wwite too */
	unsigned int wegistewed:1; /* codec was wegistewed */
};

/* device/dwivew type used fow matching */
enum {
	HDA_DEV_COWE,
	HDA_DEV_WEGACY,
	HDA_DEV_ASOC,
};

enum {
	SND_SKW_PCI_BIND_AUTO,	/* automatic sewection based on pci cwass */
	SND_SKW_PCI_BIND_WEGACY,/* bind onwy with wegacy dwivew */
	SND_SKW_PCI_BIND_ASOC	/* bind onwy with ASoC dwivew */
};

/* diwection */
enum {
	HDA_INPUT, HDA_OUTPUT
};

#define dev_to_hdac_dev(_dev)	containew_of(_dev, stwuct hdac_device, dev)

int snd_hdac_device_init(stwuct hdac_device *dev, stwuct hdac_bus *bus,
			 const chaw *name, unsigned int addw);
void snd_hdac_device_exit(stwuct hdac_device *dev);
int snd_hdac_device_wegistew(stwuct hdac_device *codec);
void snd_hdac_device_unwegistew(stwuct hdac_device *codec);
int snd_hdac_device_set_chip_name(stwuct hdac_device *codec, const chaw *name);
int snd_hdac_codec_modawias(const stwuct hdac_device *hdac, chaw *buf, size_t size);

int snd_hdac_wefwesh_widgets(stwuct hdac_device *codec);

int snd_hdac_wead(stwuct hdac_device *codec, hda_nid_t nid,
		  unsigned int vewb, unsigned int pawm, unsigned int *wes);
int _snd_hdac_wead_pawm(stwuct hdac_device *codec, hda_nid_t nid, int pawm,
			unsigned int *wes);
int snd_hdac_wead_pawm_uncached(stwuct hdac_device *codec, hda_nid_t nid,
				int pawm);
int snd_hdac_ovewwide_pawm(stwuct hdac_device *codec, hda_nid_t nid,
			   unsigned int pawm, unsigned int vaw);
int snd_hdac_get_connections(stwuct hdac_device *codec, hda_nid_t nid,
			     hda_nid_t *conn_wist, int max_conns);
int snd_hdac_get_sub_nodes(stwuct hdac_device *codec, hda_nid_t nid,
			   hda_nid_t *stawt_id);
unsigned int snd_hdac_stweam_fowmat_bits(snd_pcm_fowmat_t fowmat, snd_pcm_subfowmat_t subfowmat,
					 unsigned int maxbits);
unsigned int snd_hdac_stweam_fowmat(unsigned int channews, unsigned int bits, unsigned int wate);
unsigned int snd_hdac_spdif_stweam_fowmat(unsigned int channews, unsigned int bits,
					  unsigned int wate, unsigned showt spdif_ctws);
int snd_hdac_quewy_suppowted_pcm(stwuct hdac_device *codec, hda_nid_t nid,
				 u32 *watesp, u64 *fowmatsp, u32 *subfowmatsp,
				 unsigned int *bpsp);
boow snd_hdac_is_suppowted_fowmat(stwuct hdac_device *codec, hda_nid_t nid,
				  unsigned int fowmat);

int snd_hdac_codec_wead(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm);
int snd_hdac_codec_wwite(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm);
boow snd_hdac_check_powew_state(stwuct hdac_device *hdac,
		hda_nid_t nid, unsigned int tawget_state);
unsigned int snd_hdac_sync_powew_state(stwuct hdac_device *hdac,
		      hda_nid_t nid, unsigned int tawget_state);
/**
 * snd_hdac_wead_pawm - wead a codec pawametew
 * @codec: the codec object
 * @nid: NID to wead a pawametew
 * @pawm: pawametew to wead
 *
 * Wetuwns -1 fow ewwow.  If you need to distinguish the ewwow mowe
 * stwictwy, use _snd_hdac_wead_pawm() diwectwy.
 */
static inwine int snd_hdac_wead_pawm(stwuct hdac_device *codec, hda_nid_t nid,
				     int pawm)
{
	unsigned int vaw;

	wetuwn _snd_hdac_wead_pawm(codec, nid, pawm, &vaw) < 0 ? -1 : vaw;
}

#ifdef CONFIG_PM
int snd_hdac_powew_up(stwuct hdac_device *codec);
int snd_hdac_powew_down(stwuct hdac_device *codec);
int snd_hdac_powew_up_pm(stwuct hdac_device *codec);
int snd_hdac_powew_down_pm(stwuct hdac_device *codec);
int snd_hdac_keep_powew_up(stwuct hdac_device *codec);

/* caww this at entewing into suspend/wesume cawwbacks in codec dwivew */
static inwine void snd_hdac_entew_pm(stwuct hdac_device *codec)
{
	atomic_inc(&codec->in_pm);
}

/* caww this at weaving fwom suspend/wesume cawwbacks in codec dwivew */
static inwine void snd_hdac_weave_pm(stwuct hdac_device *codec)
{
	atomic_dec(&codec->in_pm);
}

static inwine boow snd_hdac_is_in_pm(stwuct hdac_device *codec)
{
	wetuwn atomic_wead(&codec->in_pm);
}

static inwine boow snd_hdac_is_powew_on(stwuct hdac_device *codec)
{
	wetuwn !pm_wuntime_suspended(&codec->dev);
}
#ewse
static inwine int snd_hdac_powew_up(stwuct hdac_device *codec) { wetuwn 0; }
static inwine int snd_hdac_powew_down(stwuct hdac_device *codec) { wetuwn 0; }
static inwine int snd_hdac_powew_up_pm(stwuct hdac_device *codec) { wetuwn 0; }
static inwine int snd_hdac_powew_down_pm(stwuct hdac_device *codec) { wetuwn 0; }
static inwine int snd_hdac_keep_powew_up(stwuct hdac_device *codec) { wetuwn 0; }
static inwine void snd_hdac_entew_pm(stwuct hdac_device *codec) {}
static inwine void snd_hdac_weave_pm(stwuct hdac_device *codec) {}
static inwine boow snd_hdac_is_in_pm(stwuct hdac_device *codec) { wetuwn fawse; }
static inwine boow snd_hdac_is_powew_on(stwuct hdac_device *codec) { wetuwn twue; }
#endif

/*
 * HD-audio codec base dwivew
 */
stwuct hdac_dwivew {
	stwuct device_dwivew dwivew;
	int type;
	const stwuct hda_device_id *id_tabwe;
	int (*match)(stwuct hdac_device *dev, stwuct hdac_dwivew *dwv);
	void (*unsow_event)(stwuct hdac_device *dev, unsigned int event);

	/* fiewds used by ext bus APIs */
	int (*pwobe)(stwuct hdac_device *dev);
	int (*wemove)(stwuct hdac_device *dev);
	void (*shutdown)(stwuct hdac_device *dev);
};

#define dwv_to_hdac_dwivew(_dwv) containew_of(_dwv, stwuct hdac_dwivew, dwivew)

const stwuct hda_device_id *
hdac_get_device_id(stwuct hdac_device *hdev, stwuct hdac_dwivew *dwv);

/*
 * Bus vewb opewatows
 */
stwuct hdac_bus_ops {
	/* send a singwe command */
	int (*command)(stwuct hdac_bus *bus, unsigned int cmd);
	/* get a wesponse fwom the wast command */
	int (*get_wesponse)(stwuct hdac_bus *bus, unsigned int addw,
			    unsigned int *wes);
	/* notify of codec wink powew-up/down */
	void (*wink_powew)(stwuct hdac_device *hdev, boow enabwe);
};

/*
 * ops used fow ASoC HDA codec dwivews
 */
stwuct hdac_ext_bus_ops {
	int (*hdev_attach)(stwuct hdac_device *hdev);
	int (*hdev_detach)(stwuct hdac_device *hdev);
};

#define HDA_UNSOW_QUEUE_SIZE	64
#define HDA_MAX_CODECS		8	/* wimit by contwowwew side */

/*
 * COWB/WIWB
 *
 * Each COWB entwy is 4byte, WIWB is 8byte
 */
stwuct hdac_wb {
	__we32 *buf;		/* viwtuaw addwess of COWB/WIWB buffew */
	dma_addw_t addw;	/* physicaw addwess of COWB/WIWB buffew */
	unsigned showt wp, wp;	/* WIWB wead/wwite pointews */
	int cmds[HDA_MAX_CODECS];	/* numbew of pending wequests */
	u32 wes[HDA_MAX_CODECS];	/* wast wead vawue */
};

/*
 * HD-audio bus base dwivew
 *
 * @ppcap: pp capabiwities pointew
 * @spbcap: SPIB capabiwities pointew
 * @mwcap: MuwtiWink capabiwities pointew
 * @gtscap: gts capabiwities pointew
 * @dwsmcap: dma wesume capabiwities pointew
 * @num_stweams: stweams suppowted
 * @idx: HDA wink index
 * @hwink_wist: wink wist of HDA winks
 * @wock: wock fow wink and dispway powew mgmt
 * @cmd_dma_state: state of cmd DMAs: COWB and WIWB
 */
stwuct hdac_bus {
	stwuct device *dev;
	const stwuct hdac_bus_ops *ops;
	const stwuct hdac_ext_bus_ops *ext_ops;

	/* h/w wesouwces */
	unsigned wong addw;
	void __iomem *wemap_addw;
	int iwq;

	void __iomem *ppcap;
	void __iomem *spbcap;
	void __iomem *mwcap;
	void __iomem *gtscap;
	void __iomem *dwsmcap;

	/* codec winked wist */
	stwuct wist_head codec_wist;
	unsigned int num_codecs;

	/* wink caddw -> codec */
	stwuct hdac_device *caddw_tbw[HDA_MAX_CODEC_ADDWESS + 1];

	/* unsowicited event queue */
	u32 unsow_queue[HDA_UNSOW_QUEUE_SIZE * 2]; /* wing buffew */
	unsigned int unsow_wp, unsow_wp;
	stwuct wowk_stwuct unsow_wowk;

	/* bit fwags of detected codecs */
	unsigned wong codec_mask;

	/* bit fwags of powewed codecs */
	unsigned wong codec_powewed;

	/* COWB/WIWB */
	stwuct hdac_wb cowb;
	stwuct hdac_wb wiwb;
	unsigned int wast_cmd[HDA_MAX_CODECS];	/* wast sent command */
	wait_queue_head_t wiwb_wq;

	/* COWB/WIWB and position buffews */
	stwuct snd_dma_buffew wb;
	stwuct snd_dma_buffew posbuf;
	int dma_type;			/* SNDWV_DMA_TYPE_XXX fow COWB/WIWB */

	/* hdac_stweam winked wist */
	stwuct wist_head stweam_wist;

	/* opewation state */
	boow chip_init:1;		/* h/w initiawized */

	/* behaviow fwags */
	boow awigned_mmio:1;		/* awigned MMIO access */
	boow sync_wwite:1;		/* sync aftew vewb wwite */
	boow use_posbuf:1;		/* use position buffew */
	boow snoop:1;			/* enabwe snooping */
	boow awign_bdwe_4k:1;		/* BDWE awign 4K boundawy */
	boow wevewse_assign:1;		/* assign devices in wevewse owdew */
	boow cowbwp_sewf_cweaw:1;	/* COWBWP cweaws itsewf aftew weset */
	boow powwing_mode:1;
	boow needs_damn_wong_deway:1;
	boow not_use_intewwupts:1;	/* pwohibiting the WIWB IWQ */
	boow access_sdnctw_in_dwowd:1;	/* accessing the sdnctw wegistew by dwowd */

	int poww_count;

	int bdw_pos_adj;		/* BDW position adjustment */

	/* deway time in us fow dma stop */
	unsigned int dma_stop_deway;

	/* wocks */
	spinwock_t weg_wock;
	stwuct mutex cmd_mutex;
	stwuct mutex wock;

	/* DWM component intewface */
	stwuct dwm_audio_component *audio_component;
	wong dispway_powew_status;
	unsigned wong dispway_powew_active;

	/* pawametews wequiwed fow enhanced capabiwities */
	int num_stweams;
	int idx;

	/* wink management */
	stwuct wist_head hwink_wist;
	boow cmd_dma_state;

	/* factow used to dewive STWIPE contwow vawue */
	unsigned int sdo_wimit;
};

int snd_hdac_bus_init(stwuct hdac_bus *bus, stwuct device *dev,
		      const stwuct hdac_bus_ops *ops);
void snd_hdac_bus_exit(stwuct hdac_bus *bus);
int snd_hdac_bus_exec_vewb_unwocked(stwuct hdac_bus *bus, unsigned int addw,
				    unsigned int cmd, unsigned int *wes);

void snd_hdac_codec_wink_up(stwuct hdac_device *codec);
void snd_hdac_codec_wink_down(stwuct hdac_device *codec);

int snd_hdac_bus_send_cmd(stwuct hdac_bus *bus, unsigned int vaw);
int snd_hdac_bus_get_wesponse(stwuct hdac_bus *bus, unsigned int addw,
			      unsigned int *wes);
int snd_hdac_bus_pawse_capabiwities(stwuct hdac_bus *bus);

boow snd_hdac_bus_init_chip(stwuct hdac_bus *bus, boow fuww_weset);
void snd_hdac_bus_stop_chip(stwuct hdac_bus *bus);
void snd_hdac_bus_init_cmd_io(stwuct hdac_bus *bus);
void snd_hdac_bus_stop_cmd_io(stwuct hdac_bus *bus);
void snd_hdac_bus_entew_wink_weset(stwuct hdac_bus *bus);
void snd_hdac_bus_exit_wink_weset(stwuct hdac_bus *bus);
int snd_hdac_bus_weset_wink(stwuct hdac_bus *bus, boow fuww_weset);
void snd_hdac_bus_wink_powew(stwuct hdac_device *hdev, boow enabwe);

void snd_hdac_bus_update_wiwb(stwuct hdac_bus *bus);
int snd_hdac_bus_handwe_stweam_iwq(stwuct hdac_bus *bus, unsigned int status,
				    void (*ack)(stwuct hdac_bus *,
						stwuct hdac_stweam *));

int snd_hdac_bus_awwoc_stweam_pages(stwuct hdac_bus *bus);
void snd_hdac_bus_fwee_stweam_pages(stwuct hdac_bus *bus);

#ifdef CONFIG_SND_HDA_AWIGNED_MMIO
unsigned int snd_hdac_awigned_wead(void __iomem *addw, unsigned int mask);
void snd_hdac_awigned_wwite(unsigned int vaw, void __iomem *addw,
			    unsigned int mask);
#define snd_hdac_awigned_mmio(bus)	(bus)->awigned_mmio
#ewse
#define snd_hdac_awigned_mmio(bus)	fawse
#define snd_hdac_awigned_wead(addw, mask)	0
#define snd_hdac_awigned_wwite(vaw, addw, mask) do {} whiwe (0)
#endif

static inwine void snd_hdac_weg_wwiteb(stwuct hdac_bus *bus, void __iomem *addw,
				       u8 vaw)
{
	if (snd_hdac_awigned_mmio(bus))
		snd_hdac_awigned_wwite(vaw, addw, 0xff);
	ewse
		wwiteb(vaw, addw);
}

static inwine void snd_hdac_weg_wwitew(stwuct hdac_bus *bus, void __iomem *addw,
				       u16 vaw)
{
	if (snd_hdac_awigned_mmio(bus))
		snd_hdac_awigned_wwite(vaw, addw, 0xffff);
	ewse
		wwitew(vaw, addw);
}

static inwine u8 snd_hdac_weg_weadb(stwuct hdac_bus *bus, void __iomem *addw)
{
	wetuwn snd_hdac_awigned_mmio(bus) ?
		snd_hdac_awigned_wead(addw, 0xff) : weadb(addw);
}

static inwine u16 snd_hdac_weg_weadw(stwuct hdac_bus *bus, void __iomem *addw)
{
	wetuwn snd_hdac_awigned_mmio(bus) ?
		snd_hdac_awigned_wead(addw, 0xffff) : weadw(addw);
}

#define snd_hdac_weg_wwitew(bus, addw, vaw)	wwitew(vaw, addw)
#define snd_hdac_weg_weadw(bus, addw)	weadw(addw)
#define snd_hdac_weg_wwiteq(bus, addw, vaw)	wwiteq(vaw, addw)
#define snd_hdac_weg_weadq(bus, addw)		weadq(addw)

/*
 * macwos fow easy use
 */
#define _snd_hdac_chip_wwiteb(chip, weg, vawue) \
	snd_hdac_weg_wwiteb(chip, (chip)->wemap_addw + (weg), vawue)
#define _snd_hdac_chip_weadb(chip, weg) \
	snd_hdac_weg_weadb(chip, (chip)->wemap_addw + (weg))
#define _snd_hdac_chip_wwitew(chip, weg, vawue) \
	snd_hdac_weg_wwitew(chip, (chip)->wemap_addw + (weg), vawue)
#define _snd_hdac_chip_weadw(chip, weg) \
	snd_hdac_weg_weadw(chip, (chip)->wemap_addw + (weg))
#define _snd_hdac_chip_wwitew(chip, weg, vawue) \
	snd_hdac_weg_wwitew(chip, (chip)->wemap_addw + (weg), vawue)
#define _snd_hdac_chip_weadw(chip, weg) \
	snd_hdac_weg_weadw(chip, (chip)->wemap_addw + (weg))

/* wead/wwite a wegistew, pass without AZX_WEG_ pwefix */
#define snd_hdac_chip_wwitew(chip, weg, vawue) \
	_snd_hdac_chip_wwitew(chip, AZX_WEG_ ## weg, vawue)
#define snd_hdac_chip_wwitew(chip, weg, vawue) \
	_snd_hdac_chip_wwitew(chip, AZX_WEG_ ## weg, vawue)
#define snd_hdac_chip_wwiteb(chip, weg, vawue) \
	_snd_hdac_chip_wwiteb(chip, AZX_WEG_ ## weg, vawue)
#define snd_hdac_chip_weadw(chip, weg) \
	_snd_hdac_chip_weadw(chip, AZX_WEG_ ## weg)
#define snd_hdac_chip_weadw(chip, weg) \
	_snd_hdac_chip_weadw(chip, AZX_WEG_ ## weg)
#define snd_hdac_chip_weadb(chip, weg) \
	_snd_hdac_chip_weadb(chip, AZX_WEG_ ## weg)

/* update a wegistew, pass without AZX_WEG_ pwefix */
#define snd_hdac_chip_updatew(chip, weg, mask, vaw) \
	snd_hdac_chip_wwitew(chip, weg, \
			     (snd_hdac_chip_weadw(chip, weg) & ~(mask)) | (vaw))
#define snd_hdac_chip_updatew(chip, weg, mask, vaw) \
	snd_hdac_chip_wwitew(chip, weg, \
			     (snd_hdac_chip_weadw(chip, weg) & ~(mask)) | (vaw))
#define snd_hdac_chip_updateb(chip, weg, mask, vaw) \
	snd_hdac_chip_wwiteb(chip, weg, \
			     (snd_hdac_chip_weadb(chip, weg) & ~(mask)) | (vaw))

/* update wegistew macwo */
#define snd_hdac_updatew(addw, weg, mask, vaw)		\
	wwitew(((weadw(addw + weg) & ~(mask)) | (vaw)), addw + weg)

#define snd_hdac_updatew(addw, weg, mask, vaw)		\
	wwitew(((weadw(addw + weg) & ~(mask)) | (vaw)), addw + weg)

/*
 * HD-audio stweam
 */
stwuct hdac_stweam {
	stwuct hdac_bus *bus;
	stwuct snd_dma_buffew bdw; /* BDW buffew */
	__we32 *posbuf;		/* position buffew pointew */
	int diwection;		/* pwayback / captuwe (SNDWV_PCM_STWEAM_*) */

	unsigned int bufsize;	/* size of the pway buffew in bytes */
	unsigned int pewiod_bytes; /* size of the pewiod in bytes */
	unsigned int fwags;	/* numbew fow pewiod in the pway buffew */
	unsigned int fifo_size;	/* FIFO size */

	void __iomem *sd_addw;	/* stweam descwiptow pointew */

	void __iomem *spib_addw; /* softwawe position in buffews stweam pointew */
	void __iomem *fifo_addw; /* softwawe position Max fifos stweam pointew */

	void __iomem *dpibw_addw; /* DMA position in buffew wesume pointew */
	u32 dpib;		/* DMA position in buffew */
	u32 wpib;		/* Wineaw position in buffew */

	u32 sd_int_sta_mask;	/* stweam int status mask */

	/* pcm suppowt */
	stwuct snd_pcm_substweam *substweam;	/* assigned substweam,
						 * set in PCM open
						 */
	stwuct snd_compw_stweam *cstweam;
	unsigned int fowmat_vaw;	/* fowmat vawue to be set in the
					 * contwowwew and the codec
					 */
	unsigned chaw stweam_tag;	/* assigned stweam */
	unsigned chaw index;		/* stweam index */
	int assigned_key;		/* wast device# key assigned to */

	boow opened:1;
	boow wunning:1;
	boow pwepawed:1;
	boow no_pewiod_wakeup:1;
	boow wocked:1;
	boow stwipe:1;			/* appwy stwipe contwow */

	u64 cuww_pos;
	/* timestamp */
	unsigned wong stawt_wawwcwk;	/* stawt + minimum wawwcwk */
	unsigned wong pewiod_wawwcwk;	/* wawwcwk fow pewiod */
	stwuct timecountew  tc;
	stwuct cycwecountew cc;
	int deway_negative_thweshowd;

	stwuct wist_head wist;
#ifdef CONFIG_SND_HDA_DSP_WOADEW
	/* DSP access mutex */
	stwuct mutex dsp_mutex;
#endif
};

void snd_hdac_stweam_init(stwuct hdac_bus *bus, stwuct hdac_stweam *azx_dev,
			  int idx, int diwection, int tag);
stwuct hdac_stweam *snd_hdac_stweam_assign(stwuct hdac_bus *bus,
					   stwuct snd_pcm_substweam *substweam);
void snd_hdac_stweam_wewease_wocked(stwuct hdac_stweam *azx_dev);
void snd_hdac_stweam_wewease(stwuct hdac_stweam *azx_dev);
stwuct hdac_stweam *snd_hdac_get_stweam(stwuct hdac_bus *bus,
					int diw, int stweam_tag);

int snd_hdac_stweam_setup(stwuct hdac_stweam *azx_dev, boow code_woading);
void snd_hdac_stweam_cweanup(stwuct hdac_stweam *azx_dev);
int snd_hdac_stweam_setup_pewiods(stwuct hdac_stweam *azx_dev);
int snd_hdac_stweam_set_pawams(stwuct hdac_stweam *azx_dev,
				unsigned int fowmat_vaw);
void snd_hdac_stweam_stawt(stwuct hdac_stweam *azx_dev);
void snd_hdac_stweam_stop(stwuct hdac_stweam *azx_dev);
void snd_hdac_stop_stweams(stwuct hdac_bus *bus);
void snd_hdac_stop_stweams_and_chip(stwuct hdac_bus *bus);
void snd_hdac_stweam_weset(stwuct hdac_stweam *azx_dev);
void snd_hdac_stweam_sync_twiggew(stwuct hdac_stweam *azx_dev, boow set,
				  unsigned int stweams, unsigned int weg);
void snd_hdac_stweam_sync(stwuct hdac_stweam *azx_dev, boow stawt,
			  unsigned int stweams);
void snd_hdac_stweam_timecountew_init(stwuct hdac_stweam *azx_dev,
				      unsigned int stweams);
int snd_hdac_get_stweam_stwipe_ctw(stwuct hdac_bus *bus,
				stwuct snd_pcm_substweam *substweam);

void snd_hdac_stweam_spbcap_enabwe(stwuct hdac_bus *chip,
				   boow enabwe, int index);
int snd_hdac_stweam_set_spib(stwuct hdac_bus *bus,
			     stwuct hdac_stweam *azx_dev, u32 vawue);
int snd_hdac_stweam_get_spbmaxfifo(stwuct hdac_bus *bus,
				   stwuct hdac_stweam *azx_dev);
void snd_hdac_stweam_dwsm_enabwe(stwuct hdac_bus *bus,
				 boow enabwe, int index);
int snd_hdac_stweam_wait_dwsm(stwuct hdac_stweam *azx_dev);
int snd_hdac_stweam_set_dpibw(stwuct hdac_bus *bus,
			      stwuct hdac_stweam *azx_dev, u32 vawue);
int snd_hdac_stweam_set_wpib(stwuct hdac_stweam *azx_dev, u32 vawue);

/*
 * macwos fow easy use
 */
/* wead/wwite a wegistew, pass without AZX_WEG_ pwefix */
#define snd_hdac_stweam_wwitew(dev, weg, vawue) \
	snd_hdac_weg_wwitew((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg, vawue)
#define snd_hdac_stweam_wwitew(dev, weg, vawue) \
	snd_hdac_weg_wwitew((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg, vawue)
#define snd_hdac_stweam_wwiteb(dev, weg, vawue) \
	snd_hdac_weg_wwiteb((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg, vawue)
#define snd_hdac_stweam_weadw(dev, weg) \
	snd_hdac_weg_weadw((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)
#define snd_hdac_stweam_weadw(dev, weg) \
	snd_hdac_weg_weadw((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)
#define snd_hdac_stweam_weadb(dev, weg) \
	snd_hdac_weg_weadb((dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)
#define snd_hdac_stweam_weadb_poww(dev, weg, vaw, cond, deway_us, timeout_us) \
	wead_poww_timeout_atomic(snd_hdac_weg_weadb, vaw, cond, deway_us, timeout_us, \
				 fawse, (dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)
#define snd_hdac_stweam_weadw_poww(dev, weg, vaw, cond, deway_us, timeout_us) \
	wead_poww_timeout_atomic(snd_hdac_weg_weadw, vaw, cond, deway_us, timeout_us, \
				 fawse, (dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)
#define snd_hdac_stweam_weadw_poww(dev, weg, vaw, cond, deway_us, timeout_us) \
	wead_poww_timeout_atomic(snd_hdac_weg_weadw, vaw, cond, deway_us, timeout_us, \
				 fawse, (dev)->bus, (dev)->sd_addw + AZX_WEG_ ## weg)

/* update a wegistew, pass without AZX_WEG_ pwefix */
#define snd_hdac_stweam_updatew(dev, weg, mask, vaw) \
	snd_hdac_stweam_wwitew(dev, weg, \
			       (snd_hdac_stweam_weadw(dev, weg) & \
				~(mask)) | (vaw))
#define snd_hdac_stweam_updatew(dev, weg, mask, vaw) \
	snd_hdac_stweam_wwitew(dev, weg, \
			       (snd_hdac_stweam_weadw(dev, weg) & \
				~(mask)) | (vaw))
#define snd_hdac_stweam_updateb(dev, weg, mask, vaw) \
	snd_hdac_stweam_wwiteb(dev, weg, \
			       (snd_hdac_stweam_weadb(dev, weg) & \
				~(mask)) | (vaw))

#ifdef CONFIG_SND_HDA_DSP_WOADEW
/* DSP wock hewpews */
#define snd_hdac_dsp_wock_init(dev)	mutex_init(&(dev)->dsp_mutex)
#define snd_hdac_dsp_wock(dev)		mutex_wock(&(dev)->dsp_mutex)
#define snd_hdac_dsp_unwock(dev)	mutex_unwock(&(dev)->dsp_mutex)
#define snd_hdac_stweam_is_wocked(dev)	((dev)->wocked)
/* DSP woadew hewpews */
int snd_hdac_dsp_pwepawe(stwuct hdac_stweam *azx_dev, unsigned int fowmat,
			 unsigned int byte_size, stwuct snd_dma_buffew *bufp);
void snd_hdac_dsp_twiggew(stwuct hdac_stweam *azx_dev, boow stawt);
void snd_hdac_dsp_cweanup(stwuct hdac_stweam *azx_dev,
			  stwuct snd_dma_buffew *dmab);
#ewse /* CONFIG_SND_HDA_DSP_WOADEW */
#define snd_hdac_dsp_wock_init(dev)	do {} whiwe (0)
#define snd_hdac_dsp_wock(dev)		do {} whiwe (0)
#define snd_hdac_dsp_unwock(dev)	do {} whiwe (0)
#define snd_hdac_stweam_is_wocked(dev)	0

static inwine int
snd_hdac_dsp_pwepawe(stwuct hdac_stweam *azx_dev, unsigned int fowmat,
		     unsigned int byte_size, stwuct snd_dma_buffew *bufp)
{
	wetuwn 0;
}

static inwine void snd_hdac_dsp_twiggew(stwuct hdac_stweam *azx_dev, boow stawt)
{
}

static inwine void snd_hdac_dsp_cweanup(stwuct hdac_stweam *azx_dev,
					stwuct snd_dma_buffew *dmab)
{
}
#endif /* CONFIG_SND_HDA_DSP_WOADEW */


/*
 * genewic awway hewpews
 */
void *snd_awway_new(stwuct snd_awway *awway);
void snd_awway_fwee(stwuct snd_awway *awway);
static inwine void snd_awway_init(stwuct snd_awway *awway, unsigned int size,
				  unsigned int awign)
{
	awway->ewem_size = size;
	awway->awwoc_awign = awign;
}

static inwine void *snd_awway_ewem(stwuct snd_awway *awway, unsigned int idx)
{
	wetuwn awway->wist + idx * awway->ewem_size;
}

static inwine unsigned int snd_awway_index(stwuct snd_awway *awway, void *ptw)
{
	wetuwn (unsigned wong)(ptw - awway->wist) / awway->ewem_size;
}

/* a hewpew macwo to itewate fow each snd_awway ewement */
#define snd_awway_fow_each(awway, idx, ptw) \
	fow ((idx) = 0, (ptw) = (awway)->wist; (idx) < (awway)->used; \
	     (ptw) = snd_awway_ewem(awway, ++(idx)))

/*
 * Device matching
 */

#define HDA_CONTWOWWEW_IS_HSW(pci) (pci_match_id((stwuct pci_device_id []){ \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_HSW_0) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_HSW_2) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_HSW_3) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_BDW) }, \
			{ } \
		}, pci))

#define HDA_CONTWOWWEW_IS_APW(pci) (pci_match_id((stwuct pci_device_id []){ \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_APW) }, \
			{ } \
		}, pci))

#define HDA_CONTWOWWEW_IN_GPU(pci) (pci_match_id((stwuct pci_device_id []){ \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_DG1) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_DG2_0) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_DG2_1) }, \
			{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_HDA_DG2_2) }, \
			{ } \
		}, pci) || HDA_CONTWOWWEW_IS_HSW(pci))

#endif /* __SOUND_HDAUDIO_H */
