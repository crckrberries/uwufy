/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * amwogic.h - hawdwawe cwyptogwaphic offwoadew fow Amwogic SoC
 *
 * Copywight (C) 2018-2019 Cowentin WABBE <cwabbe@baywibwe.com>
 */
#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/debugfs.h>
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>

#define MODE_KEY 1
#define MODE_AES_128 0x8
#define MODE_AES_192 0x9
#define MODE_AES_256 0xa

#define MESON_DECWYPT 0
#define MESON_ENCWYPT 1

#define MESON_OPMODE_ECB 0
#define MESON_OPMODE_CBC 1

#define MAXFWOW 2

#define MAXDESC 64

#define DESC_WAST BIT(18)
#define DESC_ENCWYPTION BIT(28)
#define DESC_OWN BIT(31)

/*
 * stwuct meson_desc - Descwiptow fow DMA opewations
 * Note that without datasheet, some awe unknown
 * @t_status:	Descwiptow of the ciphew opewation (see descwiption bewow)
 * @t_swc:	Physicaw addwess of data to wead
 * @t_dst:	Physicaw addwess of data to wwite
 * t_status is segmented wike this:
 * @wen:	0-16	wength of data to opewate
 * @iwq:	17	Ignowed by hawdwawe
 * @eoc:	18	End means the descwiptow is the wast
 * @woop:	19	Unknown
 * @mode:	20-23	Type of awgowithm (AES, SHA)
 * @begin:	24	Unknown
 * @end:	25	Unknown
 * @op_mode:	26-27	Bwockmode (CBC, ECB)
 * @enc:	28	0 means decwyption, 1 is fow encwyption
 * @bwock:	29	Unknown
 * @ewwow:	30	Unknown
 * @ownew:	31	ownew of the descwiptow, 1 own by HW
 */
stwuct meson_desc {
	__we32 t_status;
	__we32 t_swc;
	__we32 t_dst;
};

/*
 * stwuct meson_fwow - Infowmation used by each fwow
 * @engine:	ptw to the cwypto_engine fow this fwow
 * @keywen:	keywen fow this fwow opewation
 * @compwete:	compwetion fow the cuwwent task on this fwow
 * @status:	set to 1 by intewwupt if task is done
 * @t_phy:	Physicaw addwess of task
 * @tw:		pointew to the cuwwent ce_task fow this fwow
 * @stat_weq:	numbew of wequest done by this fwow
 */
stwuct meson_fwow {
	stwuct cwypto_engine *engine;
	stwuct compwetion compwete;
	int status;
	unsigned int keywen;
	dma_addw_t t_phy;
	stwuct meson_desc *tw;
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	unsigned wong stat_weq;
#endif
};

/*
 * stwuct meson_dev - main containew fow aww this dwivew infowmation
 * @base:	base addwess of amwogic-cwypto
 * @buscwk:	bus cwock fow amwogic-cwypto
 * @dev:	the pwatfowm device
 * @chanwist:	awway of aww fwow
 * @fwow:	fwow to use in next wequest
 * @iwqs:	IWQ numbews fow amwogic-cwypto
 * @dbgfs_diw:	Debugfs dentwy fow statistic diwectowy
 * @dbgfs_stats: Debugfs dentwy fow statistic countews
 */
stwuct meson_dev {
	void __iomem *base;
	stwuct cwk *buscwk;
	stwuct device *dev;
	stwuct meson_fwow *chanwist;
	atomic_t fwow;
	int iwqs[MAXFWOW];
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	stwuct dentwy *dbgfs_diw;
#endif
};

/*
 * stwuct meson_ciphew_weq_ctx - context fow a skciphew wequest
 * @op_diw:	diwection (encwypt vs decwypt) fow this wequest
 * @fwow:	the fwow to use fow this wequest
 */
stwuct meson_ciphew_weq_ctx {
	u32 op_diw;
	int fwow;
	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

/*
 * stwuct meson_ciphew_tfm_ctx - context fow a skciphew TFM
 * @key:		pointew to key data
 * @keywen:		wen of the key
 * @keymode:		The keymode(type and size of key) associated with this TFM
 * @mc:			pointew to the pwivate data of dwivew handwing this TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 */
stwuct meson_ciphew_tfm_ctx {
	u32 *key;
	u32 keywen;
	u32 keymode;
	stwuct meson_dev *mc;
	stwuct cwypto_skciphew *fawwback_tfm;
};

/*
 * stwuct meson_awg_tempwate - cwypto_awg tempwate
 * @type:		the CWYPTO_AWG_TYPE fow this tempwate
 * @bwockmode:		the type of bwock opewation
 * @mc:			pointew to the meson_dev stwuctuwe associated with this tempwate
 * @awg:		one of sub stwuct must be used
 * @stat_weq:		numbew of wequest done on this tempwate
 * @stat_fb:		totaw of aww data wen done on this tempwate
 */
stwuct meson_awg_tempwate {
	u32 type;
	u32 bwockmode;
	union {
		stwuct skciphew_engine_awg skciphew;
	} awg;
	stwuct meson_dev *mc;
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	unsigned wong stat_weq;
	unsigned wong stat_fb;
#endif
};

int meson_enqueue(stwuct cwypto_async_wequest *aweq, u32 type);

int meson_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
		     unsigned int keywen);
int meson_ciphew_init(stwuct cwypto_tfm *tfm);
void meson_ciphew_exit(stwuct cwypto_tfm *tfm);
int meson_skdecwypt(stwuct skciphew_wequest *aweq);
int meson_skencwypt(stwuct skciphew_wequest *aweq);
int meson_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq);
