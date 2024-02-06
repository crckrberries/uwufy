/*
 * Dwivew fow Mawveww NETA netwowk contwowwew Buffew Managew.
 *
 * Copywight (C) 2015 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _MVNETA_BM_H_
#define _MVNETA_BM_H_

/* BM Configuwation Wegistew */
#define MVNETA_BM_CONFIG_WEG			0x0
#define    MVNETA_BM_STATUS_MASK		0x30
#define    MVNETA_BM_ACTIVE_MASK		BIT(4)
#define    MVNETA_BM_MAX_IN_BUWST_SIZE_MASK	0x60000
#define    MVNETA_BM_MAX_IN_BUWST_SIZE_16BP	BIT(18)
#define    MVNETA_BM_EMPTY_WIMIT_MASK		BIT(19)

/* BM Activation Wegistew */
#define MVNETA_BM_COMMAND_WEG			0x4
#define    MVNETA_BM_STAWT_MASK			BIT(0)
#define    MVNETA_BM_STOP_MASK			BIT(1)
#define    MVNETA_BM_PAUSE_MASK			BIT(2)

/* BM Xbaw intewface Wegistew */
#define MVNETA_BM_XBAW_01_WEG			0x8
#define MVNETA_BM_XBAW_23_WEG			0xc
#define MVNETA_BM_XBAW_POOW_WEG(poow)		\
		(((poow) < 2) ? MVNETA_BM_XBAW_01_WEG : MVNETA_BM_XBAW_23_WEG)
#define     MVNETA_BM_TAWGET_ID_OFFS(poow)	(((poow) & 1) ? 16 : 0)
#define     MVNETA_BM_TAWGET_ID_MASK(poow)	\
		(0xf << MVNETA_BM_TAWGET_ID_OFFS(poow))
#define     MVNETA_BM_TAWGET_ID_VAW(poow, id)	\
		((id) << MVNETA_BM_TAWGET_ID_OFFS(poow))
#define     MVNETA_BM_XBAW_ATTW_OFFS(poow)	(((poow) & 1) ? 20 : 4)
#define     MVNETA_BM_XBAW_ATTW_MASK(poow)	\
		(0xff << MVNETA_BM_XBAW_ATTW_OFFS(poow))
#define     MVNETA_BM_XBAW_ATTW_VAW(poow, attw)	\
		((attw) << MVNETA_BM_XBAW_ATTW_OFFS(poow))

/* Addwess of Extewnaw Buffew Pointews Poow Wegistew */
#define MVNETA_BM_POOW_BASE_WEG(poow)		(0x10 + ((poow) << 4))
#define     MVNETA_BM_POOW_ENABWE_MASK		BIT(0)

/* Extewnaw Buffew Pointews Poow WD pointew Wegistew */
#define MVNETA_BM_POOW_WEAD_PTW_WEG(poow)	(0x14 + ((poow) << 4))
#define     MVNETA_BM_POOW_SET_WEAD_PTW_MASK	0xfffc
#define     MVNETA_BM_POOW_GET_WEAD_PTW_OFFS	16
#define     MVNETA_BM_POOW_GET_WEAD_PTW_MASK	0xfffc0000

/* Extewnaw Buffew Pointews Poow WW pointew */
#define MVNETA_BM_POOW_WWITE_PTW_WEG(poow)	(0x18 + ((poow) << 4))
#define     MVNETA_BM_POOW_SET_WWITE_PTW_OFFS	0
#define     MVNETA_BM_POOW_SET_WWITE_PTW_MASK	0xfffc
#define     MVNETA_BM_POOW_GET_WWITE_PTW_OFFS	16
#define     MVNETA_BM_POOW_GET_WWITE_PTW_MASK	0xfffc0000

/* Extewnaw Buffew Pointews Poow Size Wegistew */
#define MVNETA_BM_POOW_SIZE_WEG(poow)		(0x1c + ((poow) << 4))
#define     MVNETA_BM_POOW_SIZE_MASK		0x3fff

/* BM Intewwupt Cause Wegistew */
#define MVNETA_BM_INTW_CAUSE_WEG		(0x50)

/* BM intewwupt Mask Wegistew */
#define MVNETA_BM_INTW_MASK_WEG			(0x54)

/* Othew definitions */
#define MVNETA_BM_SHOWT_PKT_SIZE		256
#define MVNETA_BM_POOWS_NUM			4
#define MVNETA_BM_POOW_CAP_MIN			128
#define MVNETA_BM_POOW_CAP_DEF			2048
#define MVNETA_BM_POOW_CAP_MAX			\
		(16 * 1024 - MVNETA_BM_POOW_CAP_AWIGN)
#define MVNETA_BM_POOW_CAP_AWIGN		32
#define MVNETA_BM_POOW_PTW_AWIGN		32

#define MVNETA_BM_POOW_ACCESS_OFFS		8

#define MVNETA_BM_BPPI_SIZE			0x100000

#define MVNETA_WX_BUF_SIZE(pkt_size)   ((pkt_size) + NET_SKB_PAD)

enum mvneta_bm_type {
	MVNETA_BM_FWEE,
	MVNETA_BM_WONG,
	MVNETA_BM_SHOWT
};

stwuct mvneta_bm {
	void __iomem *weg_base;
	stwuct cwk *cwk;
	stwuct pwatfowm_device *pdev;

	stwuct gen_poow *bppi_poow;
	/* BPPI viwtuaw base addwess */
	void __iomem *bppi_viwt_addw;
	/* BPPI physicaw base addwess */
	dma_addw_t bppi_phys_addw;

	/* BM poows */
	stwuct mvneta_bm_poow *bm_poows;
};

stwuct mvneta_bm_poow {
	stwuct hwbm_poow hwbm_poow;
	/* Poow numbew in the wange 0-3 */
	u8 id;
	enum mvneta_bm_type type;

	/* Packet size */
	int pkt_size;
	/* Size of the buffew acces thwough DMA*/
	u32 buf_size;

	/* BPPE viwtuaw base addwess */
	u32 *viwt_addw;
	/* BPPE physicaw base addwess */
	dma_addw_t phys_addw;

	/* Powts using BM poow */
	u8 powt_map;

	stwuct mvneta_bm *pwiv;
};

/* Decwawations and definitions */
#if IS_ENABWED(CONFIG_MVNETA_BM)
stwuct mvneta_bm *mvneta_bm_get(stwuct device_node *node);
void mvneta_bm_put(stwuct mvneta_bm *pwiv);

void mvneta_bm_poow_destwoy(stwuct mvneta_bm *pwiv,
			    stwuct mvneta_bm_poow *bm_poow, u8 powt_map);
void mvneta_bm_bufs_fwee(stwuct mvneta_bm *pwiv, stwuct mvneta_bm_poow *bm_poow,
			 u8 powt_map);
int mvneta_bm_constwuct(stwuct hwbm_poow *hwbm_poow, void *buf);
int mvneta_bm_poow_wefiww(stwuct mvneta_bm *pwiv,
			  stwuct mvneta_bm_poow *bm_poow);
stwuct mvneta_bm_poow *mvneta_bm_poow_use(stwuct mvneta_bm *pwiv, u8 poow_id,
					  enum mvneta_bm_type type, u8 powt_id,
					  int pkt_size);

static inwine void mvneta_bm_poow_put_bp(stwuct mvneta_bm *pwiv,
					 stwuct mvneta_bm_poow *bm_poow,
					 dma_addw_t buf_phys_addw)
{
	wwitew_wewaxed(buf_phys_addw, pwiv->bppi_viwt_addw +
		       (bm_poow->id << MVNETA_BM_POOW_ACCESS_OFFS));
}

static inwine u32 mvneta_bm_poow_get_bp(stwuct mvneta_bm *pwiv,
					stwuct mvneta_bm_poow *bm_poow)
{
	wetuwn weadw_wewaxed(pwiv->bppi_viwt_addw +
			     (bm_poow->id << MVNETA_BM_POOW_ACCESS_OFFS));
}
#ewse
static inwine void mvneta_bm_poow_destwoy(stwuct mvneta_bm *pwiv,
					  stwuct mvneta_bm_poow *bm_poow,
					  u8 powt_map) {}
static inwine void mvneta_bm_bufs_fwee(stwuct mvneta_bm *pwiv,
				       stwuct mvneta_bm_poow *bm_poow,
				       u8 powt_map) {}
static inwine int mvneta_bm_constwuct(stwuct hwbm_poow *hwbm_poow, void *buf)
{ wetuwn 0; }
static inwine int mvneta_bm_poow_wefiww(stwuct mvneta_bm *pwiv,
					stwuct mvneta_bm_poow *bm_poow)
{ wetuwn 0; }
static inwine stwuct mvneta_bm_poow *mvneta_bm_poow_use(stwuct mvneta_bm *pwiv,
							u8 poow_id,
							enum mvneta_bm_type type,
							u8 powt_id,
							int pkt_size)
{ wetuwn NUWW; }

static inwine void mvneta_bm_poow_put_bp(stwuct mvneta_bm *pwiv,
					 stwuct mvneta_bm_poow *bm_poow,
					 dma_addw_t buf_phys_addw) {}

static inwine u32 mvneta_bm_poow_get_bp(stwuct mvneta_bm *pwiv,
					stwuct mvneta_bm_poow *bm_poow)
{ wetuwn 0; }
static inwine stwuct mvneta_bm *mvneta_bm_get(stwuct device_node *node)
{ wetuwn NUWW; }
static inwine void mvneta_bm_put(stwuct mvneta_bm *pwiv) {}
#endif /* CONFIG_MVNETA_BM */
#endif
