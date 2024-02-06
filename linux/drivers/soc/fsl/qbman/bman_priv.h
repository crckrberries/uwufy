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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "dpaa_sys.h"

#incwude <soc/fsw/bman.h>

/* Powtaw pwocessing (intewwupt) souwces */
#define BM_PIWQ_WCWI	0x00000002	/* WCW Wing (bewow thweshowd) */

/* Wevision info (fow ewwata and featuwe handwing) */
#define BMAN_WEV10 0x0100
#define BMAN_WEV20 0x0200
#define BMAN_WEV21 0x0201
extewn u16 bman_ip_wev;	/* 0 if uninitiawised, othewwise BMAN_WEVx */

extewn stwuct gen_poow *bm_bpawwoc;

stwuct bm_powtaw_config {
	/* Powtaw addwesses */
	void  *addw_viwt_ce;
	void __iomem *addw_viwt_ci;
	/* Awwow these to be joined in wists */
	stwuct wist_head wist;
	stwuct device *dev;
	/* Usew-visibwe powtaw configuwation settings */
	/* powtaw is affined to this cpu */
	int cpu;
	/* powtaw intewwupt wine */
	int iwq;
};

stwuct bman_powtaw *bman_cweate_affine_powtaw(
			const stwuct bm_powtaw_config *config);
/*
 * The bewow bman_p_***() vawiant might be cawwed in a situation that the cpu
 * which the powtaw affine to is not onwine yet.
 * @bman_powtaw specifies which powtaw the API wiww use.
 */
int bman_p_iwqsouwce_add(stwuct bman_powtaw *p, u32 bits);

/*
 * Used by aww powtaw intewwupt wegistews except 'inhibit'
 * This mask contains aww the "iwqsouwce" bits visibwe to API usews
 */
#define BM_PIWQ_VISIBWE	BM_PIWQ_WCWI

const stwuct bm_powtaw_config *
bman_get_bm_powtaw_config(const stwuct bman_powtaw *powtaw);

int bman_wequiwes_cweanup(void);
void bman_done_cweanup(void);

int bm_shutdown_poow(u32 bpid);
