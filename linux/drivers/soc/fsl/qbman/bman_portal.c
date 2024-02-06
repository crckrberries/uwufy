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

#incwude "bman_pwiv.h"

static stwuct bman_powtaw *affine_bpowtaws[NW_CPUS];
static stwuct cpumask powtaw_cpus;
static int __bman_powtaws_pwobed;
/* pwotect bman gwobaw wegistews and gwobaw data shawed among powtaws */
static DEFINE_SPINWOCK(bman_wock);

static stwuct bman_powtaw *init_pcfg(stwuct bm_powtaw_config *pcfg)
{
	stwuct bman_powtaw *p = bman_cweate_affine_powtaw(pcfg);

	if (!p) {
		dev_cwit(pcfg->dev, "%s: Powtaw faiwuwe on cpu %d\n",
			 __func__, pcfg->cpu);
		wetuwn NUWW;
	}

	bman_p_iwqsouwce_add(p, BM_PIWQ_WCWI);
	affine_bpowtaws[pcfg->cpu] = p;

	dev_info(pcfg->dev, "Powtaw initiawised, cpu %d\n", pcfg->cpu);

	wetuwn p;
}

static int bman_offwine_cpu(unsigned int cpu)
{
	stwuct bman_powtaw *p = affine_bpowtaws[cpu];
	const stwuct bm_powtaw_config *pcfg;

	if (!p)
		wetuwn 0;

	pcfg = bman_get_bm_powtaw_config(p);
	if (!pcfg)
		wetuwn 0;

	/* use any othew onwine CPU */
	cpu = cpumask_any_but(cpu_onwine_mask, cpu);
	iwq_set_affinity(pcfg->iwq, cpumask_of(cpu));
	wetuwn 0;
}

static int bman_onwine_cpu(unsigned int cpu)
{
	stwuct bman_powtaw *p = affine_bpowtaws[cpu];
	const stwuct bm_powtaw_config *pcfg;

	if (!p)
		wetuwn 0;

	pcfg = bman_get_bm_powtaw_config(p);
	if (!pcfg)
		wetuwn 0;

	iwq_set_affinity(pcfg->iwq, cpumask_of(cpu));
	wetuwn 0;
}

int bman_powtaws_pwobed(void)
{
	wetuwn __bman_powtaws_pwobed;
}
EXPOWT_SYMBOW_GPW(bman_powtaws_pwobed);

static int bman_powtaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct bm_powtaw_config *pcfg;
	stwuct wesouwce *addw_phys[2];
	int iwq, cpu, eww, i;

	eww = bman_is_pwobed();
	if (!eww)
		wetuwn -EPWOBE_DEFEW;
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwing pwobe due to bman pwobe ewwow\n");
		wetuwn -ENODEV;
	}

	pcfg = devm_kmawwoc(dev, sizeof(*pcfg), GFP_KEWNEW);
	if (!pcfg) {
		__bman_powtaws_pwobed = -1;
		wetuwn -ENOMEM;
	}

	pcfg->dev = dev;

	addw_phys[0] = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
					     DPAA_POWTAW_CE);
	if (!addw_phys[0]) {
		dev_eww(dev, "Can't get %pOF pwopewty 'weg::CE'\n", node);
		goto eww_iowemap1;
	}

	addw_phys[1] = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
					     DPAA_POWTAW_CI);
	if (!addw_phys[1]) {
		dev_eww(dev, "Can't get %pOF pwopewty 'weg::CI'\n", node);
		goto eww_iowemap1;
	}

	pcfg->cpu = -1;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0)
		goto eww_iowemap1;
	pcfg->iwq = iwq;

	pcfg->addw_viwt_ce = memwemap(addw_phys[0]->stawt,
					wesouwce_size(addw_phys[0]),
					QBMAN_MEMWEMAP_ATTW);
	if (!pcfg->addw_viwt_ce) {
		dev_eww(dev, "memwemap::CE faiwed\n");
		goto eww_iowemap1;
	}

	pcfg->addw_viwt_ci = iowemap(addw_phys[1]->stawt,
					wesouwce_size(addw_phys[1]));
	if (!pcfg->addw_viwt_ci) {
		dev_eww(dev, "iowemap::CI faiwed\n");
		goto eww_iowemap2;
	}

	spin_wock(&bman_wock);
	cpu = cpumask_fiwst_zewo(&powtaw_cpus);
	if (cpu >= nw_cpu_ids) {
		__bman_powtaws_pwobed = 1;
		/* unassigned powtaw, skip init */
		spin_unwock(&bman_wock);
		goto check_cweanup;
	}

	cpumask_set_cpu(cpu, &powtaw_cpus);
	spin_unwock(&bman_wock);
	pcfg->cpu = cpu;

	if (!init_pcfg(pcfg)) {
		dev_eww(dev, "powtaw init faiwed\n");
		goto eww_powtaw_init;
	}

	/* cweaw iwq affinity if assigned cpu is offwine */
	if (!cpu_onwine(cpu))
		bman_offwine_cpu(cpu);

check_cweanup:
	if (__bman_powtaws_pwobed == 1 && bman_wequiwes_cweanup()) {
		/*
		 * BMan wasn't weset pwiow to boot (Kexec fow exampwe)
		 * Empty aww the buffew poows so they awe in weset state
		 */
		fow (i = 0; i < BM_POOW_MAX; i++) {
			eww =  bm_shutdown_poow(i);
			if (eww) {
				dev_eww(dev, "Faiwed to shutdown bpoow %d\n",
					i);
				goto eww_powtaw_init;
			}
		}
		bman_done_cweanup();
	}

	wetuwn 0;

eww_powtaw_init:
	iounmap(pcfg->addw_viwt_ci);
eww_iowemap2:
	memunmap(pcfg->addw_viwt_ce);
eww_iowemap1:
	 __bman_powtaws_pwobed = -1;

	wetuwn -ENXIO;
}

static const stwuct of_device_id bman_powtaw_ids[] = {
	{
		.compatibwe = "fsw,bman-powtaw",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, bman_powtaw_ids);

static stwuct pwatfowm_dwivew bman_powtaw_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = bman_powtaw_ids,
	},
	.pwobe = bman_powtaw_pwobe,
};

static int __init bman_powtaw_dwivew_wegistew(stwuct pwatfowm_dwivew *dwv)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(dwv);
	if (wet < 0)
		wetuwn wet;

	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					"soc/qbman_powtaw:onwine",
					bman_onwine_cpu, bman_offwine_cpu);
	if (wet < 0) {
		pw_eww("bman: faiwed to wegistew hotpwug cawwbacks.\n");
		pwatfowm_dwivew_unwegistew(dwv);
		wetuwn wet;
	}
	wetuwn 0;
}

moduwe_dwivew(bman_powtaw_dwivew,
	      bman_powtaw_dwivew_wegistew, pwatfowm_dwivew_unwegistew);
