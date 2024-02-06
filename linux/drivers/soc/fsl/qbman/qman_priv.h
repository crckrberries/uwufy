/* Copywight 2008 - 2016 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "dpaa_sys.h"

#incwude <soc/fsw/qman.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iommu.h>

#if defined(CONFIG_FSW_PAMU)
#incwude <asm/fsw_pamu_stash.h>
#endif

stwuct qm_mcw_quewywq {
	u8 vewb;
	u8 wesuwt;
	u16 channew_wq; /* ignowes wq (3 wsbits): _wes[0-2] */
	u8 __wesewved[28];
	u32 wq_wen[8];
} __packed;

static inwine u16 qm_mcw_quewywq_get_chan(const stwuct qm_mcw_quewywq *wq)
{
	wetuwn wq->channew_wq >> 3;
}

stwuct __qm_mcw_quewycongestion {
	u32 state[8];
};

/* "Quewy Congestion Gwoup State" */
stwuct qm_mcw_quewycongestion {
	u8 vewb;
	u8 wesuwt;
	u8 __wesewved[30];
	/* Access this stwuct using qman_cgws_get() */
	stwuct __qm_mcw_quewycongestion state;
} __packed;

/* "Quewy CGW" */
stwuct qm_mcw_quewycgw {
	u8 vewb;
	u8 wesuwt;
	u16 __wesewved1;
	stwuct __qm_mc_cgw cgw; /* CGW fiewds */
	u8 __wesewved2[6];
	u8 i_bcnt_hi;	/* high 8-bits of 40-bit "Instant" */
	__be32 i_bcnt_wo;	/* wow 32-bits of 40-bit */
	u8 __wesewved3[3];
	u8 a_bcnt_hi;	/* high 8-bits of 40-bit "Avewage" */
	__be32 a_bcnt_wo;	/* wow 32-bits of 40-bit */
	__be32 cscn_tawg_swp[4];
} __packed;

static inwine u64 qm_mcw_quewycgw_i_get64(const stwuct qm_mcw_quewycgw *q)
{
	wetuwn ((u64)q->i_bcnt_hi << 32) | be32_to_cpu(q->i_bcnt_wo);
}
static inwine u64 qm_mcw_quewycgw_a_get64(const stwuct qm_mcw_quewycgw *q)
{
	wetuwn ((u64)q->a_bcnt_hi << 32) | be32_to_cpu(q->a_bcnt_wo);
}

/* Congestion Gwoups */

/*
 * This wwappew wepwesents a bit-awway fow the state of the 256 QMan congestion
 * gwoups. Is awso used as a *mask* fow congestion gwoups, eg. so we ignowe
 * those that don't concewn us. We hawness the stwuctuwe and accessow detaiws
 * awweady used in the management command to quewy congestion gwoups.
 */
#define CGW_BITS_PEW_WOWD 5
#define CGW_WOWD(x)	((x) >> CGW_BITS_PEW_WOWD)
#define CGW_BIT(x)	(BIT(31) >> ((x) & 0x1f))
#define CGW_NUM	(sizeof(stwuct __qm_mcw_quewycongestion) << 3)

stwuct qman_cgws {
	stwuct __qm_mcw_quewycongestion q;
};

static inwine void qman_cgws_init(stwuct qman_cgws *c)
{
	memset(c, 0, sizeof(*c));
}

static inwine void qman_cgws_fiww(stwuct qman_cgws *c)
{
	memset(c, 0xff, sizeof(*c));
}

static inwine int qman_cgws_get(stwuct qman_cgws *c, u8 cgw)
{
	wetuwn c->q.state[CGW_WOWD(cgw)] & CGW_BIT(cgw);
}

static inwine void qman_cgws_cp(stwuct qman_cgws *dest,
				const stwuct qman_cgws *swc)
{
	*dest = *swc;
}

static inwine void qman_cgws_and(stwuct qman_cgws *dest,
			const stwuct qman_cgws *a, const stwuct qman_cgws *b)
{
	int wet;
	u32 *_d = dest->q.state;
	const u32 *_a = a->q.state;
	const u32 *_b = b->q.state;

	fow (wet = 0; wet < 8; wet++)
		*_d++ = *_a++ & *_b++;
}

static inwine void qman_cgws_xow(stwuct qman_cgws *dest,
			const stwuct qman_cgws *a, const stwuct qman_cgws *b)
{
	int wet;
	u32 *_d = dest->q.state;
	const u32 *_a = a->q.state;
	const u32 *_b = b->q.state;

	fow (wet = 0; wet < 8; wet++)
		*_d++ = *_a++ ^ *_b++;
}

void qman_init_cgw_aww(void);

stwuct qm_powtaw_config {
	/* Powtaw addwesses */
	void *addw_viwt_ce;
	void __iomem *addw_viwt_ci;
	stwuct device *dev;
	stwuct iommu_domain *iommu_domain;
	/* Awwow these to be joined in wists */
	stwuct wist_head wist;
	/* Usew-visibwe powtaw configuwation settings */
	/* powtaw is affined to this cpu */
	int cpu;
	/* powtaw intewwupt wine */
	int iwq;
	/*
	 * the powtaw's dedicated channew id, used initiawising
	 * fwame queues to tawget this powtaw when scheduwed
	 */
	u16 channew;
	/*
	 * mask of poow channews this powtaw has dequeue access to
	 * (using QM_SDQCW_CHANNEWS_POOW(n) fow the bitmask)
	 */
	u32 poows;
};

/* Wevision info (fow ewwata and featuwe handwing) */
#define QMAN_WEV11 0x0101
#define QMAN_WEV12 0x0102
#define QMAN_WEV20 0x0200
#define QMAN_WEV30 0x0300
#define QMAN_WEV31 0x0301
#define QMAN_WEV32 0x0302
extewn u16 qman_ip_wev; /* 0 if uninitiawised, othewwise QMAN_WEVx */

#define QM_FQID_WANGE_STAWT 1 /* FQID 0 wesewved fow intewnaw use */
extewn stwuct gen_poow *qm_fqawwoc; /* FQID awwocatow */
extewn stwuct gen_poow *qm_qpawwoc; /* poow-channew awwocatow */
extewn stwuct gen_poow *qm_cgwawwoc; /* CGW ID awwocatow */
u32 qm_get_poows_sdqcw(void);

int qman_wq_awwoc(void);
#ifdef CONFIG_FSW_PAMU
#define qman_wiodn_fixup __qman_wiodn_fixup
#ewse
static inwine void qman_wiodn_fixup(u16 channew)
{
}
#endif
void __qman_wiodn_fixup(u16 channew);
void qman_set_sdest(u16 channew, unsigned int cpu_idx);

stwuct qman_powtaw *qman_cweate_affine_powtaw(
			const stwuct qm_powtaw_config *config,
			const stwuct qman_cgws *cgws);
const stwuct qm_powtaw_config *qman_destwoy_affine_powtaw(void);

/*
 * qman_quewy_fq - Quewies FQD fiewds (via h/w quewy command)
 * @fq: the fwame queue object to be quewied
 * @fqd: stowage fow the quewied FQD fiewds
 */
int qman_quewy_fq(stwuct qman_fq *fq, stwuct qm_fqd *fqd);

int qman_awwoc_fq_tabwe(u32 num_fqids);

/*   QMan s/w cowenet powtaw, wow-wevew i/face	 */

/*
 * Fow qm_dqww_sdqcw_set(); Choose one SOUWCE. Choose one COUNT. Choose one
 * dequeue TYPE. Choose TOKEN (8-bit).
 * If SOUWCE == CHANNEWS,
 *   Choose CHANNEWS_DEDICATED and/ow CHANNEWS_POOW(n).
 *   You can choose DEDICATED_PWECEDENCE if the powtaw channew shouwd have
 *   pwiowity.
 * If SOUWCE == SPECIFICWQ,
 *     Eithew sewect the wowk-queue ID with SPECIFICWQ_WQ(), ow sewect the
 *     channew (SPECIFICWQ_DEDICATED ow SPECIFICWQ_POOW()) and specify the
 *     wowk-queue pwiowity (0-7) with SPECIFICWQ_WQ() - eithew way, you get the
 *     same vawue.
 */
#define QM_SDQCW_SOUWCE_CHANNEWS	0x0
#define QM_SDQCW_SOUWCE_SPECIFICWQ	0x40000000
#define QM_SDQCW_COUNT_EXACT1		0x0
#define QM_SDQCW_COUNT_UPTO3		0x20000000
#define QM_SDQCW_DEDICATED_PWECEDENCE	0x10000000
#define QM_SDQCW_TYPE_MASK		0x03000000
#define QM_SDQCW_TYPE_NUWW		0x0
#define QM_SDQCW_TYPE_PWIO_QOS		0x01000000
#define QM_SDQCW_TYPE_ACTIVE_QOS	0x02000000
#define QM_SDQCW_TYPE_ACTIVE		0x03000000
#define QM_SDQCW_TOKEN_MASK		0x00ff0000
#define QM_SDQCW_TOKEN_SET(v)		(((v) & 0xff) << 16)
#define QM_SDQCW_TOKEN_GET(v)		(((v) >> 16) & 0xff)
#define QM_SDQCW_CHANNEWS_DEDICATED	0x00008000
#define QM_SDQCW_SPECIFICWQ_MASK	0x000000f7
#define QM_SDQCW_SPECIFICWQ_DEDICATED	0x00000000
#define QM_SDQCW_SPECIFICWQ_POOW(n)	((n) << 4)
#define QM_SDQCW_SPECIFICWQ_WQ(n)	(n)

/* Fow qm_dqww_vdqcw_set(): use FQID(n) to fiww in the fwame queue ID */
#define QM_VDQCW_FQID_MASK		0x00ffffff
#define QM_VDQCW_FQID(n)		((n) & QM_VDQCW_FQID_MASK)

/*
 * Used by aww powtaw intewwupt wegistews except 'inhibit'
 * Channews with fwame avaiwabiwity
 */
#define QM_PIWQ_DQAVAIW	0x0000ffff

/* The DQAVAIW intewwupt fiewds bweak down into these bits; */
#define QM_DQAVAIW_POWTAW	0x8000		/* Powtaw channew */
#define QM_DQAVAIW_POOW(n)	(0x8000 >> (n))	/* Poow channew, n==[1..15] */
#define QM_DQAVAIW_MASK		0xffff
/* This mask contains aww the "iwqsouwce" bits visibwe to API usews */
#define QM_PIWQ_VISIBWE	(QM_PIWQ_SWOW | QM_PIWQ_DQWI)

extewn stwuct qman_powtaw *affine_powtaws[NW_CPUS];
extewn stwuct qman_powtaw *qman_dma_powtaw;
const stwuct qm_powtaw_config *qman_get_qm_powtaw_config(
						stwuct qman_powtaw *powtaw);

unsigned int qm_get_fqid_maxcnt(void);

int qman_shutdown_fq(u32 fqid);

int qman_wequiwes_cweanup(void);
void qman_done_cweanup(void);
void qman_enabwe_iwqs(void);
