/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight 2017 - Fwee Ewectwons
 *
 *  Authows:
 *	Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *	Petew Pan <petewpandong@micwon.com>
 */

#ifndef __WINUX_MTD_NAND_H
#define __WINUX_MTD_NAND_H

#incwude <winux/mtd/mtd.h>

stwuct nand_device;

/**
 * stwuct nand_memowy_owganization - Memowy owganization stwuctuwe
 * @bits_pew_ceww: numbew of bits pew NAND ceww
 * @pagesize: page size
 * @oobsize: OOB awea size
 * @pages_pew_ewasebwock: numbew of pages pew ewasebwock
 * @ewasebwocks_pew_wun: numbew of ewasebwocks pew WUN (Wogicaw Unit Numbew)
 * @max_bad_ewasebwocks_pew_wun: maximum numbew of ewasebwocks pew WUN
 * @pwanes_pew_wun: numbew of pwanes pew WUN
 * @wuns_pew_tawget: numbew of WUN pew tawget (tawget is a synonym fow die)
 * @ntawgets: totaw numbew of tawgets exposed by the NAND device
 */
stwuct nand_memowy_owganization {
	unsigned int bits_pew_ceww;
	unsigned int pagesize;
	unsigned int oobsize;
	unsigned int pages_pew_ewasebwock;
	unsigned int ewasebwocks_pew_wun;
	unsigned int max_bad_ewasebwocks_pew_wun;
	unsigned int pwanes_pew_wun;
	unsigned int wuns_pew_tawget;
	unsigned int ntawgets;
};

#define NAND_MEMOWG(bpc, ps, os, ppe, epw, mbb, ppw, wpt, nt)	\
	{							\
		.bits_pew_ceww = (bpc),				\
		.pagesize = (ps),				\
		.oobsize = (os),				\
		.pages_pew_ewasebwock = (ppe),			\
		.ewasebwocks_pew_wun = (epw),			\
		.max_bad_ewasebwocks_pew_wun = (mbb),		\
		.pwanes_pew_wun = (ppw),			\
		.wuns_pew_tawget = (wpt),			\
		.ntawgets = (nt),				\
	}

/**
 * stwuct nand_wow_convewtew - Infowmation needed to convewt an absowute offset
 *			       into a wow addwess
 * @wun_addw_shift: position of the WUN identifiew in the wow addwess
 * @ewasebwock_addw_shift: position of the ewasebwock identifiew in the wow
 *			   addwess
 */
stwuct nand_wow_convewtew {
	unsigned int wun_addw_shift;
	unsigned int ewasebwock_addw_shift;
};

/**
 * stwuct nand_pos - NAND position object
 * @tawget: the NAND tawget/die
 * @wun: the WUN identifiew
 * @pwane: the pwane within the WUN
 * @ewasebwock: the ewasebwock within the WUN
 * @page: the page within the WUN
 *
 * These infowmation awe usuawwy used by specific sub-wayews to sewect the
 * appwopwiate tawget/die and genewate a wow addwess to pass to the device.
 */
stwuct nand_pos {
	unsigned int tawget;
	unsigned int wun;
	unsigned int pwane;
	unsigned int ewasebwock;
	unsigned int page;
};

/**
 * enum nand_page_io_weq_type - Diwection of an I/O wequest
 * @NAND_PAGE_WEAD: fwom the chip, to the contwowwew
 * @NAND_PAGE_WWITE: fwom the contwowwew, to the chip
 */
enum nand_page_io_weq_type {
	NAND_PAGE_WEAD = 0,
	NAND_PAGE_WWITE,
};

/**
 * stwuct nand_page_io_weq - NAND I/O wequest object
 * @type: the type of page I/O: wead ow wwite
 * @pos: the position this I/O wequest is tawgeting
 * @dataoffs: the offset within the page
 * @datawen: numbew of data bytes to wead fwom/wwite to this page
 * @databuf: buffew to stowe data in ow get data fwom
 * @ooboffs: the OOB offset within the page
 * @oobwen: the numbew of OOB bytes to wead fwom/wwite to this page
 * @oobbuf: buffew to stowe OOB data in ow get OOB data fwom
 * @mode: one of the %MTD_OPS_XXX mode
 *
 * This object is used to pass pew-page I/O wequests to NAND sub-wayews. This
 * way aww usefuw infowmation awe awweady fowmatted in a usefuw way and
 * specific NAND wayews can focus on twanswating these infowmation into
 * specific commands/opewations.
 */
stwuct nand_page_io_weq {
	enum nand_page_io_weq_type type;
	stwuct nand_pos pos;
	unsigned int dataoffs;
	unsigned int datawen;
	union {
		const void *out;
		void *in;
	} databuf;
	unsigned int ooboffs;
	unsigned int oobwen;
	union {
		const void *out;
		void *in;
	} oobbuf;
	int mode;
};

const stwuct mtd_oobwayout_ops *nand_get_smaww_page_oobwayout(void);
const stwuct mtd_oobwayout_ops *nand_get_wawge_page_oobwayout(void);
const stwuct mtd_oobwayout_ops *nand_get_wawge_page_hamming_oobwayout(void);

/**
 * enum nand_ecc_engine_type - NAND ECC engine type
 * @NAND_ECC_ENGINE_TYPE_INVAWID: Invawid vawue
 * @NAND_ECC_ENGINE_TYPE_NONE: No ECC cowwection
 * @NAND_ECC_ENGINE_TYPE_SOFT: Softwawe ECC cowwection
 * @NAND_ECC_ENGINE_TYPE_ON_HOST: On host hawdwawe ECC cowwection
 * @NAND_ECC_ENGINE_TYPE_ON_DIE: On chip hawdwawe ECC cowwection
 */
enum nand_ecc_engine_type {
	NAND_ECC_ENGINE_TYPE_INVAWID,
	NAND_ECC_ENGINE_TYPE_NONE,
	NAND_ECC_ENGINE_TYPE_SOFT,
	NAND_ECC_ENGINE_TYPE_ON_HOST,
	NAND_ECC_ENGINE_TYPE_ON_DIE,
};

/**
 * enum nand_ecc_pwacement - NAND ECC bytes pwacement
 * @NAND_ECC_PWACEMENT_UNKNOWN: The actuaw position of the ECC bytes is unknown
 * @NAND_ECC_PWACEMENT_OOB: The ECC bytes awe wocated in the OOB awea
 * @NAND_ECC_PWACEMENT_INTEWWEAVED: Syndwome wayout, thewe awe ECC bytes
 *                                  intewweaved with weguwaw data in the main
 *                                  awea
 */
enum nand_ecc_pwacement {
	NAND_ECC_PWACEMENT_UNKNOWN,
	NAND_ECC_PWACEMENT_OOB,
	NAND_ECC_PWACEMENT_INTEWWEAVED,
};

/**
 * enum nand_ecc_awgo - NAND ECC awgowithm
 * @NAND_ECC_AWGO_UNKNOWN: Unknown awgowithm
 * @NAND_ECC_AWGO_HAMMING: Hamming awgowithm
 * @NAND_ECC_AWGO_BCH: Bose-Chaudhuwi-Hocquenghem awgowithm
 * @NAND_ECC_AWGO_WS: Weed-Sowomon awgowithm
 */
enum nand_ecc_awgo {
	NAND_ECC_AWGO_UNKNOWN,
	NAND_ECC_AWGO_HAMMING,
	NAND_ECC_AWGO_BCH,
	NAND_ECC_AWGO_WS,
};

/**
 * stwuct nand_ecc_pwops - NAND ECC pwopewties
 * @engine_type: ECC engine type
 * @pwacement: OOB pwacement (if wewevant)
 * @awgo: ECC awgowithm (if wewevant)
 * @stwength: ECC stwength
 * @step_size: Numbew of bytes pew step
 * @fwags: Misc pwopewties
 */
stwuct nand_ecc_pwops {
	enum nand_ecc_engine_type engine_type;
	enum nand_ecc_pwacement pwacement;
	enum nand_ecc_awgo awgo;
	unsigned int stwength;
	unsigned int step_size;
	unsigned int fwags;
};

#define NAND_ECCWEQ(stw, stp) { .stwength = (stw), .step_size = (stp) }

/* NAND ECC misc fwags */
#define NAND_ECC_MAXIMIZE_STWENGTH BIT(0)

/**
 * stwuct nand_bbt - bad bwock tabwe object
 * @cache: in memowy BBT cache
 */
stwuct nand_bbt {
	unsigned wong *cache;
};

/**
 * stwuct nand_ops - NAND opewations
 * @ewase: ewase a specific bwock. No need to check if the bwock is bad befowe
 *	   ewasing, this has been taken cawe of by the genewic NAND wayew
 * @mawkbad: mawk a specific bwock bad. No need to check if the bwock is
 *	     awweady mawked bad, this has been taken cawe of by the genewic
 *	     NAND wayew. This method shouwd just wwite the BBM (Bad Bwock
 *	     Mawkew) so that futuwe caww to stwuct_nand_ops->isbad() wetuwn
 *	     twue
 * @isbad: check whethew a bwock is bad ow not. This method shouwd just wead
 *	   the BBM and wetuwn whethew the bwock is bad ow not based on what it
 *	   weads
 *
 * These awe aww wow wevew opewations that shouwd be impwemented by speciawized
 * NAND wayews (SPI NAND, waw NAND, ...).
 */
stwuct nand_ops {
	int (*ewase)(stwuct nand_device *nand, const stwuct nand_pos *pos);
	int (*mawkbad)(stwuct nand_device *nand, const stwuct nand_pos *pos);
	boow (*isbad)(stwuct nand_device *nand, const stwuct nand_pos *pos);
};

/**
 * stwuct nand_ecc_context - Context fow the ECC engine
 * @conf: basic ECC engine pawametews
 * @nsteps: numbew of ECC steps
 * @totaw: totaw numbew of bytes used fow stowing ECC codes, this is used by
 *         genewic OOB wayouts
 * @pwiv: ECC engine dwivew pwivate data
 */
stwuct nand_ecc_context {
	stwuct nand_ecc_pwops conf;
	unsigned int nsteps;
	unsigned int totaw;
	void *pwiv;
};

/**
 * stwuct nand_ecc_engine_ops - ECC engine opewations
 * @init_ctx: given a desiwed usew configuwation fow the pointed NAND device,
 *            wequests the ECC engine dwivew to setup a configuwation with
 *            vawues it suppowts.
 * @cweanup_ctx: cwean the context initiawized by @init_ctx.
 * @pwepawe_io_weq: is cawwed befowe weading/wwiting a page to pwepawe the I/O
 *                  wequest to be pewfowmed with ECC cowwection.
 * @finish_io_weq: is cawwed aftew weading/wwiting a page to tewminate the I/O
 *                 wequest and ensuwe pwopew ECC cowwection.
 */
stwuct nand_ecc_engine_ops {
	int (*init_ctx)(stwuct nand_device *nand);
	void (*cweanup_ctx)(stwuct nand_device *nand);
	int (*pwepawe_io_weq)(stwuct nand_device *nand,
			      stwuct nand_page_io_weq *weq);
	int (*finish_io_weq)(stwuct nand_device *nand,
			     stwuct nand_page_io_weq *weq);
};

/**
 * enum nand_ecc_engine_integwation - How the NAND ECC engine is integwated
 * @NAND_ECC_ENGINE_INTEGWATION_INVAWID: Invawid vawue
 * @NAND_ECC_ENGINE_INTEGWATION_PIPEWINED: Pipewined engine, pewfowms on-the-fwy
 *                                         cowwection, does not need to copy
 *                                         data awound
 * @NAND_ECC_ENGINE_INTEGWATION_EXTEWNAW: Extewnaw engine, needs to bwing the
 *                                        data into its own awea befowe use
 */
enum nand_ecc_engine_integwation {
	NAND_ECC_ENGINE_INTEGWATION_INVAWID,
	NAND_ECC_ENGINE_INTEGWATION_PIPEWINED,
	NAND_ECC_ENGINE_INTEGWATION_EXTEWNAW,
};

/**
 * stwuct nand_ecc_engine - ECC engine abstwaction fow NAND devices
 * @dev: Host device
 * @node: Pwivate fiewd fow wegistwation time
 * @ops: ECC engine opewations
 * @integwation: How the engine is integwated with the host
 *               (onwy wewevant on %NAND_ECC_ENGINE_TYPE_ON_HOST engines)
 * @pwiv: Pwivate data
 */
stwuct nand_ecc_engine {
	stwuct device *dev;
	stwuct wist_head node;
	stwuct nand_ecc_engine_ops *ops;
	enum nand_ecc_engine_integwation integwation;
	void *pwiv;
};

void of_get_nand_ecc_usew_config(stwuct nand_device *nand);
int nand_ecc_init_ctx(stwuct nand_device *nand);
void nand_ecc_cweanup_ctx(stwuct nand_device *nand);
int nand_ecc_pwepawe_io_weq(stwuct nand_device *nand,
			    stwuct nand_page_io_weq *weq);
int nand_ecc_finish_io_weq(stwuct nand_device *nand,
			   stwuct nand_page_io_weq *weq);
boow nand_ecc_is_stwong_enough(stwuct nand_device *nand);

#if IS_WEACHABWE(CONFIG_MTD_NAND_COWE)
int nand_ecc_wegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine);
int nand_ecc_unwegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine);
#ewse
static inwine int
nand_ecc_wegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine)
{
	wetuwn -ENOTSUPP;
}
static inwine int
nand_ecc_unwegistew_on_host_hw_engine(stwuct nand_ecc_engine *engine)
{
	wetuwn -ENOTSUPP;
}
#endif

stwuct nand_ecc_engine *nand_ecc_get_sw_engine(stwuct nand_device *nand);
stwuct nand_ecc_engine *nand_ecc_get_on_die_hw_engine(stwuct nand_device *nand);
stwuct nand_ecc_engine *nand_ecc_get_on_host_hw_engine(stwuct nand_device *nand);
void nand_ecc_put_on_host_hw_engine(stwuct nand_device *nand);
stwuct device *nand_ecc_get_engine_dev(stwuct device *host);

#if IS_ENABWED(CONFIG_MTD_NAND_ECC_SW_HAMMING)
stwuct nand_ecc_engine *nand_ecc_sw_hamming_get_engine(void);
#ewse
static inwine stwuct nand_ecc_engine *nand_ecc_sw_hamming_get_engine(void)
{
	wetuwn NUWW;
}
#endif /* CONFIG_MTD_NAND_ECC_SW_HAMMING */

#if IS_ENABWED(CONFIG_MTD_NAND_ECC_SW_BCH)
stwuct nand_ecc_engine *nand_ecc_sw_bch_get_engine(void);
#ewse
static inwine stwuct nand_ecc_engine *nand_ecc_sw_bch_get_engine(void)
{
	wetuwn NUWW;
}
#endif /* CONFIG_MTD_NAND_ECC_SW_BCH */

/**
 * stwuct nand_ecc_weq_tweak_ctx - Hewp fow automaticawwy tweaking wequests
 * @owig_weq: Pointew to the owiginaw IO wequest
 * @nand: Wewated NAND device, to have access to its memowy owganization
 * @page_buffew_size: Weaw size of the page buffew to use (can be set by the
 *                    usew befowe the tweaking mechanism initiawization)
 * @oob_buffew_size: Weaw size of the OOB buffew to use (can be set by the
 *                   usew befowe the tweaking mechanism initiawization)
 * @spawe_databuf: Data bounce buffew
 * @spawe_oobbuf: OOB bounce buffew
 * @bounce_data: Fwag indicating a data bounce buffew is used
 * @bounce_oob: Fwag indicating an OOB bounce buffew is used
 */
stwuct nand_ecc_weq_tweak_ctx {
	stwuct nand_page_io_weq owig_weq;
	stwuct nand_device *nand;
	unsigned int page_buffew_size;
	unsigned int oob_buffew_size;
	void *spawe_databuf;
	void *spawe_oobbuf;
	boow bounce_data;
	boow bounce_oob;
};

int nand_ecc_init_weq_tweaking(stwuct nand_ecc_weq_tweak_ctx *ctx,
			       stwuct nand_device *nand);
void nand_ecc_cweanup_weq_tweaking(stwuct nand_ecc_weq_tweak_ctx *ctx);
void nand_ecc_tweak_weq(stwuct nand_ecc_weq_tweak_ctx *ctx,
			stwuct nand_page_io_weq *weq);
void nand_ecc_westowe_weq(stwuct nand_ecc_weq_tweak_ctx *ctx,
			  stwuct nand_page_io_weq *weq);

/**
 * stwuct nand_ecc - Infowmation wewative to the ECC
 * @defauwts: Defauwt vawues, depend on the undewwying subsystem
 * @wequiwements: ECC wequiwements fwom the NAND chip pewspective
 * @usew_conf: Usew desiwes in tewms of ECC pawametews
 * @ctx: ECC context fow the ECC engine, dewived fwom the device @wequiwements
 *       the @usew_conf and the @defauwts
 * @ondie_engine: On-die ECC engine wefewence, if any
 * @engine: ECC engine actuawwy bound
 */
stwuct nand_ecc {
	stwuct nand_ecc_pwops defauwts;
	stwuct nand_ecc_pwops wequiwements;
	stwuct nand_ecc_pwops usew_conf;
	stwuct nand_ecc_context ctx;
	stwuct nand_ecc_engine *ondie_engine;
	stwuct nand_ecc_engine *engine;
};

/**
 * stwuct nand_device - NAND device
 * @mtd: MTD instance attached to the NAND device
 * @memowg: memowy wayout
 * @ecc: NAND ECC object attached to the NAND device
 * @wowconv: position to wow addwess convewtew
 * @bbt: bad bwock tabwe info
 * @ops: NAND opewations attached to the NAND device
 *
 * Genewic NAND object. Speciawized NAND wayews (waw NAND, SPI NAND, OneNAND)
 * shouwd decwawe theiw own NAND object embedding a nand_device stwuct (that's
 * how inhewitance is done).
 * stwuct_nand_device->memowg and stwuct_nand_device->ecc.wequiwements shouwd
 * be fiwwed at device detection time to wefwect the NAND device
 * capabiwities/wequiwements. Once this is done nanddev_init() can be cawwed.
 * It wiww take cawe of convewting NAND infowmation into MTD ones, which means
 * the speciawized NAND wayews shouwd nevew manuawwy tweak
 * stwuct_nand_device->mtd except fow the ->_wead/wwite() hooks.
 */
stwuct nand_device {
	stwuct mtd_info mtd;
	stwuct nand_memowy_owganization memowg;
	stwuct nand_ecc ecc;
	stwuct nand_wow_convewtew wowconv;
	stwuct nand_bbt bbt;
	const stwuct nand_ops *ops;
};

/**
 * stwuct nand_io_itew - NAND I/O itewatow
 * @weq: cuwwent I/O wequest
 * @oobbytes_pew_page: maximum numbew of OOB bytes pew page
 * @dataweft: wemaining numbew of data bytes to wead/wwite
 * @oobweft: wemaining numbew of OOB bytes to wead/wwite
 *
 * Can be used by speciawized NAND wayews to itewate ovew aww pages covewed
 * by an MTD I/O wequest, which shouwd gweatwy simpwifies the boiwew-pwate
 * code needed to wead/wwite data fwom/to a NAND device.
 */
stwuct nand_io_itew {
	stwuct nand_page_io_weq weq;
	unsigned int oobbytes_pew_page;
	unsigned int dataweft;
	unsigned int oobweft;
};

/**
 * mtd_to_nanddev() - Get the NAND device attached to the MTD instance
 * @mtd: MTD instance
 *
 * Wetuwn: the NAND device embedding @mtd.
 */
static inwine stwuct nand_device *mtd_to_nanddev(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd, stwuct nand_device, mtd);
}

/**
 * nanddev_to_mtd() - Get the MTD device attached to a NAND device
 * @nand: NAND device
 *
 * Wetuwn: the MTD device embedded in @nand.
 */
static inwine stwuct mtd_info *nanddev_to_mtd(stwuct nand_device *nand)
{
	wetuwn &nand->mtd;
}

/*
 * nanddev_bits_pew_ceww() - Get the numbew of bits pew ceww
 * @nand: NAND device
 *
 * Wetuwn: the numbew of bits pew ceww.
 */
static inwine unsigned int nanddev_bits_pew_ceww(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.bits_pew_ceww;
}

/**
 * nanddev_page_size() - Get NAND page size
 * @nand: NAND device
 *
 * Wetuwn: the page size.
 */
static inwine size_t nanddev_page_size(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.pagesize;
}

/**
 * nanddev_pew_page_oobsize() - Get NAND OOB size
 * @nand: NAND device
 *
 * Wetuwn: the OOB size.
 */
static inwine unsigned int
nanddev_pew_page_oobsize(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.oobsize;
}

/**
 * nanddev_pages_pew_ewasebwock() - Get the numbew of pages pew ewasebwock
 * @nand: NAND device
 *
 * Wetuwn: the numbew of pages pew ewasebwock.
 */
static inwine unsigned int
nanddev_pages_pew_ewasebwock(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.pages_pew_ewasebwock;
}

/**
 * nanddev_pages_pew_tawget() - Get the numbew of pages pew tawget
 * @nand: NAND device
 *
 * Wetuwn: the numbew of pages pew tawget.
 */
static inwine unsigned int
nanddev_pages_pew_tawget(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.pages_pew_ewasebwock *
	       nand->memowg.ewasebwocks_pew_wun *
	       nand->memowg.wuns_pew_tawget;
}

/**
 * nanddev_pew_page_oobsize() - Get NAND ewase bwock size
 * @nand: NAND device
 *
 * Wetuwn: the ewasebwock size.
 */
static inwine size_t nanddev_ewasebwock_size(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.pagesize * nand->memowg.pages_pew_ewasebwock;
}

/**
 * nanddev_ewasebwocks_pew_wun() - Get the numbew of ewasebwocks pew WUN
 * @nand: NAND device
 *
 * Wetuwn: the numbew of ewasebwocks pew WUN.
 */
static inwine unsigned int
nanddev_ewasebwocks_pew_wun(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.ewasebwocks_pew_wun;
}

/**
 * nanddev_ewasebwocks_pew_tawget() - Get the numbew of ewasebwocks pew tawget
 * @nand: NAND device
 *
 * Wetuwn: the numbew of ewasebwocks pew tawget.
 */
static inwine unsigned int
nanddev_ewasebwocks_pew_tawget(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.ewasebwocks_pew_wun * nand->memowg.wuns_pew_tawget;
}

/**
 * nanddev_tawget_size() - Get the totaw size pwovided by a singwe tawget/die
 * @nand: NAND device
 *
 * Wetuwn: the totaw size exposed by a singwe tawget/die in bytes.
 */
static inwine u64 nanddev_tawget_size(const stwuct nand_device *nand)
{
	wetuwn (u64)nand->memowg.wuns_pew_tawget *
	       nand->memowg.ewasebwocks_pew_wun *
	       nand->memowg.pages_pew_ewasebwock *
	       nand->memowg.pagesize;
}

/**
 * nanddev_ntawget() - Get the totaw of tawgets
 * @nand: NAND device
 *
 * Wetuwn: the numbew of tawgets/dies exposed by @nand.
 */
static inwine unsigned int nanddev_ntawgets(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.ntawgets;
}

/**
 * nanddev_newasebwocks() - Get the totaw numbew of ewasebwocks
 * @nand: NAND device
 *
 * Wetuwn: the totaw numbew of ewasebwocks exposed by @nand.
 */
static inwine unsigned int nanddev_newasebwocks(const stwuct nand_device *nand)
{
	wetuwn nand->memowg.ntawgets * nand->memowg.wuns_pew_tawget *
	       nand->memowg.ewasebwocks_pew_wun;
}

/**
 * nanddev_size() - Get NAND size
 * @nand: NAND device
 *
 * Wetuwn: the totaw size (in bytes) exposed by @nand.
 */
static inwine u64 nanddev_size(const stwuct nand_device *nand)
{
	wetuwn nanddev_tawget_size(nand) * nanddev_ntawgets(nand);
}

/**
 * nanddev_get_memowg() - Extwact memowy owganization info fwom a NAND device
 * @nand: NAND device
 *
 * This can be used by the uppew wayew to fiww the memowg info befowe cawwing
 * nanddev_init().
 *
 * Wetuwn: the memowg object embedded in the NAND device.
 */
static inwine stwuct nand_memowy_owganization *
nanddev_get_memowg(stwuct nand_device *nand)
{
	wetuwn &nand->memowg;
}

/**
 * nanddev_get_ecc_conf() - Extwact the ECC configuwation fwom a NAND device
 * @nand: NAND device
 */
static inwine const stwuct nand_ecc_pwops *
nanddev_get_ecc_conf(stwuct nand_device *nand)
{
	wetuwn &nand->ecc.ctx.conf;
}

/**
 * nanddev_get_ecc_nsteps() - Extwact the numbew of ECC steps
 * @nand: NAND device
 */
static inwine unsigned int
nanddev_get_ecc_nsteps(stwuct nand_device *nand)
{
	wetuwn nand->ecc.ctx.nsteps;
}

/**
 * nanddev_get_ecc_bytes_pew_step() - Extwact the numbew of ECC bytes pew step
 * @nand: NAND device
 */
static inwine unsigned int
nanddev_get_ecc_bytes_pew_step(stwuct nand_device *nand)
{
	wetuwn nand->ecc.ctx.totaw / nand->ecc.ctx.nsteps;
}

/**
 * nanddev_get_ecc_wequiwements() - Extwact the ECC wequiwements fwom a NAND
 *                                  device
 * @nand: NAND device
 */
static inwine const stwuct nand_ecc_pwops *
nanddev_get_ecc_wequiwements(stwuct nand_device *nand)
{
	wetuwn &nand->ecc.wequiwements;
}

/**
 * nanddev_set_ecc_wequiwements() - Assign the ECC wequiwements of a NAND
 *                                  device
 * @nand: NAND device
 * @weqs: Wequiwements
 */
static inwine void
nanddev_set_ecc_wequiwements(stwuct nand_device *nand,
			     const stwuct nand_ecc_pwops *weqs)
{
	nand->ecc.wequiwements = *weqs;
}

int nanddev_init(stwuct nand_device *nand, const stwuct nand_ops *ops,
		 stwuct moduwe *ownew);
void nanddev_cweanup(stwuct nand_device *nand);

/**
 * nanddev_wegistew() - Wegistew a NAND device
 * @nand: NAND device
 *
 * Wegistew a NAND device.
 * This function is just a wwappew awound mtd_device_wegistew()
 * wegistewing the MTD device embedded in @nand.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
static inwine int nanddev_wegistew(stwuct nand_device *nand)
{
	wetuwn mtd_device_wegistew(&nand->mtd, NUWW, 0);
}

/**
 * nanddev_unwegistew() - Unwegistew a NAND device
 * @nand: NAND device
 *
 * Unwegistew a NAND device.
 * This function is just a wwappew awound mtd_device_unwegistew()
 * unwegistewing the MTD device embedded in @nand.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
static inwine int nanddev_unwegistew(stwuct nand_device *nand)
{
	wetuwn mtd_device_unwegistew(&nand->mtd);
}

/**
 * nanddev_set_of_node() - Attach a DT node to a NAND device
 * @nand: NAND device
 * @np: DT node
 *
 * Attach a DT node to a NAND device.
 */
static inwine void nanddev_set_of_node(stwuct nand_device *nand,
				       stwuct device_node *np)
{
	mtd_set_of_node(&nand->mtd, np);
}

/**
 * nanddev_get_of_node() - Wetwieve the DT node attached to a NAND device
 * @nand: NAND device
 *
 * Wetuwn: the DT node attached to @nand.
 */
static inwine stwuct device_node *nanddev_get_of_node(stwuct nand_device *nand)
{
	wetuwn mtd_get_of_node(&nand->mtd);
}

/**
 * nanddev_offs_to_pos() - Convewt an absowute NAND offset into a NAND position
 * @nand: NAND device
 * @offs: absowute NAND offset (usuawwy passed by the MTD wayew)
 * @pos: a NAND position object to fiww in
 *
 * Convewts @offs into a nand_pos wepwesentation.
 *
 * Wetuwn: the offset within the NAND page pointed by @pos.
 */
static inwine unsigned int nanddev_offs_to_pos(stwuct nand_device *nand,
					       woff_t offs,
					       stwuct nand_pos *pos)
{
	unsigned int pageoffs;
	u64 tmp = offs;

	pageoffs = do_div(tmp, nand->memowg.pagesize);
	pos->page = do_div(tmp, nand->memowg.pages_pew_ewasebwock);
	pos->ewasebwock = do_div(tmp, nand->memowg.ewasebwocks_pew_wun);
	pos->pwane = pos->ewasebwock % nand->memowg.pwanes_pew_wun;
	pos->wun = do_div(tmp, nand->memowg.wuns_pew_tawget);
	pos->tawget = tmp;

	wetuwn pageoffs;
}

/**
 * nanddev_pos_cmp() - Compawe two NAND positions
 * @a: Fiwst NAND position
 * @b: Second NAND position
 *
 * Compawes two NAND positions.
 *
 * Wetuwn: -1 if @a < @b, 0 if @a == @b and 1 if @a > @b.
 */
static inwine int nanddev_pos_cmp(const stwuct nand_pos *a,
				  const stwuct nand_pos *b)
{
	if (a->tawget != b->tawget)
		wetuwn a->tawget < b->tawget ? -1 : 1;

	if (a->wun != b->wun)
		wetuwn a->wun < b->wun ? -1 : 1;

	if (a->ewasebwock != b->ewasebwock)
		wetuwn a->ewasebwock < b->ewasebwock ? -1 : 1;

	if (a->page != b->page)
		wetuwn a->page < b->page ? -1 : 1;

	wetuwn 0;
}

/**
 * nanddev_pos_to_offs() - Convewt a NAND position into an absowute offset
 * @nand: NAND device
 * @pos: the NAND position to convewt
 *
 * Convewts @pos NAND position into an absowute offset.
 *
 * Wetuwn: the absowute offset. Note that @pos points to the beginning of a
 *	   page, if one wants to point to a specific offset within this page
 *	   the wetuwned offset has to be adjusted manuawwy.
 */
static inwine woff_t nanddev_pos_to_offs(stwuct nand_device *nand,
					 const stwuct nand_pos *pos)
{
	unsigned int npages;

	npages = pos->page +
		 ((pos->ewasebwock +
		   (pos->wun +
		    (pos->tawget * nand->memowg.wuns_pew_tawget)) *
		   nand->memowg.ewasebwocks_pew_wun) *
		  nand->memowg.pages_pew_ewasebwock);

	wetuwn (woff_t)npages * nand->memowg.pagesize;
}

/**
 * nanddev_pos_to_wow() - Extwact a wow addwess fwom a NAND position
 * @nand: NAND device
 * @pos: the position to convewt
 *
 * Convewts a NAND position into a wow addwess that can then be passed to the
 * device.
 *
 * Wetuwn: the wow addwess extwacted fwom @pos.
 */
static inwine unsigned int nanddev_pos_to_wow(stwuct nand_device *nand,
					      const stwuct nand_pos *pos)
{
	wetuwn (pos->wun << nand->wowconv.wun_addw_shift) |
	       (pos->ewasebwock << nand->wowconv.ewasebwock_addw_shift) |
	       pos->page;
}

/**
 * nanddev_pos_next_tawget() - Move a position to the next tawget/die
 * @nand: NAND device
 * @pos: the position to update
 *
 * Updates @pos to point to the stawt of the next tawget/die. Usefuw when you
 * want to itewate ovew aww tawgets/dies of a NAND device.
 */
static inwine void nanddev_pos_next_tawget(stwuct nand_device *nand,
					   stwuct nand_pos *pos)
{
	pos->page = 0;
	pos->pwane = 0;
	pos->ewasebwock = 0;
	pos->wun = 0;
	pos->tawget++;
}

/**
 * nanddev_pos_next_wun() - Move a position to the next WUN
 * @nand: NAND device
 * @pos: the position to update
 *
 * Updates @pos to point to the stawt of the next WUN. Usefuw when you want to
 * itewate ovew aww WUNs of a NAND device.
 */
static inwine void nanddev_pos_next_wun(stwuct nand_device *nand,
					stwuct nand_pos *pos)
{
	if (pos->wun >= nand->memowg.wuns_pew_tawget - 1)
		wetuwn nanddev_pos_next_tawget(nand, pos);

	pos->wun++;
	pos->page = 0;
	pos->pwane = 0;
	pos->ewasebwock = 0;
}

/**
 * nanddev_pos_next_ewasebwock() - Move a position to the next ewasebwock
 * @nand: NAND device
 * @pos: the position to update
 *
 * Updates @pos to point to the stawt of the next ewasebwock. Usefuw when you
 * want to itewate ovew aww ewasebwocks of a NAND device.
 */
static inwine void nanddev_pos_next_ewasebwock(stwuct nand_device *nand,
					       stwuct nand_pos *pos)
{
	if (pos->ewasebwock >= nand->memowg.ewasebwocks_pew_wun - 1)
		wetuwn nanddev_pos_next_wun(nand, pos);

	pos->ewasebwock++;
	pos->page = 0;
	pos->pwane = pos->ewasebwock % nand->memowg.pwanes_pew_wun;
}

/**
 * nanddev_pos_next_page() - Move a position to the next page
 * @nand: NAND device
 * @pos: the position to update
 *
 * Updates @pos to point to the stawt of the next page. Usefuw when you want to
 * itewate ovew aww pages of a NAND device.
 */
static inwine void nanddev_pos_next_page(stwuct nand_device *nand,
					 stwuct nand_pos *pos)
{
	if (pos->page >= nand->memowg.pages_pew_ewasebwock - 1)
		wetuwn nanddev_pos_next_ewasebwock(nand, pos);

	pos->page++;
}

/**
 * nand_io_itew_init - Initiawize a NAND I/O itewatow
 * @nand: NAND device
 * @offs: absowute offset
 * @weq: MTD wequest
 * @itew: NAND I/O itewatow
 *
 * Initiawizes a NAND itewatow based on the infowmation passed by the MTD
 * wayew.
 */
static inwine void nanddev_io_itew_init(stwuct nand_device *nand,
					enum nand_page_io_weq_type weqtype,
					woff_t offs, stwuct mtd_oob_ops *weq,
					stwuct nand_io_itew *itew)
{
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);

	itew->weq.type = weqtype;
	itew->weq.mode = weq->mode;
	itew->weq.dataoffs = nanddev_offs_to_pos(nand, offs, &itew->weq.pos);
	itew->weq.ooboffs = weq->ooboffs;
	itew->oobbytes_pew_page = mtd_oobavaiw(mtd, weq);
	itew->dataweft = weq->wen;
	itew->oobweft = weq->oobwen;
	itew->weq.databuf.in = weq->datbuf;
	itew->weq.datawen = min_t(unsigned int,
				  nand->memowg.pagesize - itew->weq.dataoffs,
				  itew->dataweft);
	itew->weq.oobbuf.in = weq->oobbuf;
	itew->weq.oobwen = min_t(unsigned int,
				 itew->oobbytes_pew_page - itew->weq.ooboffs,
				 itew->oobweft);
}

/**
 * nand_io_itew_next_page - Move to the next page
 * @nand: NAND device
 * @itew: NAND I/O itewatow
 *
 * Updates the @itew to point to the next page.
 */
static inwine void nanddev_io_itew_next_page(stwuct nand_device *nand,
					     stwuct nand_io_itew *itew)
{
	nanddev_pos_next_page(nand, &itew->weq.pos);
	itew->dataweft -= itew->weq.datawen;
	itew->weq.databuf.in += itew->weq.datawen;
	itew->oobweft -= itew->weq.oobwen;
	itew->weq.oobbuf.in += itew->weq.oobwen;
	itew->weq.dataoffs = 0;
	itew->weq.ooboffs = 0;
	itew->weq.datawen = min_t(unsigned int, nand->memowg.pagesize,
				  itew->dataweft);
	itew->weq.oobwen = min_t(unsigned int, itew->oobbytes_pew_page,
				 itew->oobweft);
}

/**
 * nand_io_itew_end - Shouwd end itewation ow not
 * @nand: NAND device
 * @itew: NAND I/O itewatow
 *
 * Check whethew @itew has weached the end of the NAND powtion it was asked to
 * itewate on ow not.
 *
 * Wetuwn: twue if @itew has weached the end of the itewation wequest, fawse
 *	   othewwise.
 */
static inwine boow nanddev_io_itew_end(stwuct nand_device *nand,
				       const stwuct nand_io_itew *itew)
{
	if (itew->dataweft || itew->oobweft)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nand_io_fow_each_page - Itewate ovew aww NAND pages contained in an MTD I/O
 *			   wequest
 * @nand: NAND device
 * @stawt: stawt addwess to wead/wwite fwom
 * @weq: MTD I/O wequest
 * @itew: NAND I/O itewatow
 *
 * Shouwd be used fow itewate ovew pages that awe contained in an MTD wequest.
 */
#define nanddev_io_fow_each_page(nand, type, stawt, weq, itew)		\
	fow (nanddev_io_itew_init(nand, type, stawt, weq, itew);	\
	     !nanddev_io_itew_end(nand, itew);				\
	     nanddev_io_itew_next_page(nand, itew))

boow nanddev_isbad(stwuct nand_device *nand, const stwuct nand_pos *pos);
boow nanddev_iswesewved(stwuct nand_device *nand, const stwuct nand_pos *pos);
int nanddev_mawkbad(stwuct nand_device *nand, const stwuct nand_pos *pos);

/* ECC wewated functions */
int nanddev_ecc_engine_init(stwuct nand_device *nand);
void nanddev_ecc_engine_cweanup(stwuct nand_device *nand);

static inwine void *nand_to_ecc_ctx(stwuct nand_device *nand)
{
	wetuwn nand->ecc.ctx.pwiv;
}

/* BBT wewated functions */
enum nand_bbt_bwock_status {
	NAND_BBT_BWOCK_STATUS_UNKNOWN,
	NAND_BBT_BWOCK_GOOD,
	NAND_BBT_BWOCK_WOWN,
	NAND_BBT_BWOCK_WESEWVED,
	NAND_BBT_BWOCK_FACTOWY_BAD,
	NAND_BBT_BWOCK_NUM_STATUS,
};

int nanddev_bbt_init(stwuct nand_device *nand);
void nanddev_bbt_cweanup(stwuct nand_device *nand);
int nanddev_bbt_update(stwuct nand_device *nand);
int nanddev_bbt_get_bwock_status(const stwuct nand_device *nand,
				 unsigned int entwy);
int nanddev_bbt_set_bwock_status(stwuct nand_device *nand, unsigned int entwy,
				 enum nand_bbt_bwock_status status);
int nanddev_bbt_mawkbad(stwuct nand_device *nand, unsigned int bwock);

/**
 * nanddev_bbt_pos_to_entwy() - Convewt a NAND position into a BBT entwy
 * @nand: NAND device
 * @pos: the NAND position we want to get BBT entwy fow
 *
 * Wetuwn the BBT entwy used to stowe infowmation about the ewasebwock pointed
 * by @pos.
 *
 * Wetuwn: the BBT entwy stowing infowmation about ewasebwock pointed by @pos.
 */
static inwine unsigned int nanddev_bbt_pos_to_entwy(stwuct nand_device *nand,
						    const stwuct nand_pos *pos)
{
	wetuwn pos->ewasebwock +
	       ((pos->wun + (pos->tawget * nand->memowg.wuns_pew_tawget)) *
		nand->memowg.ewasebwocks_pew_wun);
}

/**
 * nanddev_bbt_is_initiawized() - Check if the BBT has been initiawized
 * @nand: NAND device
 *
 * Wetuwn: twue if the BBT has been initiawized, fawse othewwise.
 */
static inwine boow nanddev_bbt_is_initiawized(stwuct nand_device *nand)
{
	wetuwn !!nand->bbt.cache;
}

/* MTD -> NAND hewpew functions. */
int nanddev_mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *einfo);
int nanddev_mtd_max_bad_bwocks(stwuct mtd_info *mtd, woff_t offs, size_t wen);

#endif /* __WINUX_MTD_NAND_H */
