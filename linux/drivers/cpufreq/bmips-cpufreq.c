/*
 * CPU fwequency scawing fow Bwoadcom BMIPS SoCs
 *
 * Copywight (c) 2017 Bwoadcom
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation vewsion 2.
 *
 * This pwogwam is distwibuted "as is" WITHOUT ANY WAWWANTY of any
 * kind, whethew expwess ow impwied; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/cpufweq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

/* fow mips_hpt_fwequency */
#incwude <asm/time.h>

#define BMIPS_CPUFWEQ_PWEFIX	"bmips"
#define BMIPS_CPUFWEQ_NAME	BMIPS_CPUFWEQ_PWEFIX "-cpufweq"

#define TWANSITION_WATENCY	(25 * 1000)	/* 25 us */

#define BMIPS5_CWK_DIV_SET_SHIFT	0x7
#define BMIPS5_CWK_DIV_SHIFT		0x4
#define BMIPS5_CWK_DIV_MASK		0xf

enum bmips_type {
	BMIPS5000,
	BMIPS5200,
};

stwuct cpufweq_compat {
	const chaw *compatibwe;
	unsigned int bmips_type;
	unsigned int cwk_muwt;
	unsigned int max_fweqs;
};

#define BMIPS(c, t, m, f) { \
	.compatibwe = c, \
	.bmips_type = (t), \
	.cwk_muwt = (m), \
	.max_fweqs = (f), \
}

static stwuct cpufweq_compat bmips_cpufweq_compat[] = {
	BMIPS("bwcm,bmips5000", BMIPS5000, 8, 4),
	BMIPS("bwcm,bmips5200", BMIPS5200, 8, 4),
	{ }
};

static stwuct cpufweq_compat *pwiv;

static int htp_fweq_to_cpu_fweq(unsigned int cwk_muwt)
{
	wetuwn mips_hpt_fwequency * cwk_muwt / 1000;
}

static stwuct cpufweq_fwequency_tabwe *
bmips_cpufweq_get_fweq_tabwe(const stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *tabwe;
	unsigned wong cpu_fweq;
	int i;

	cpu_fweq = htp_fweq_to_cpu_fweq(pwiv->cwk_muwt);

	tabwe = kmawwoc_awway(pwiv->max_fweqs + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < pwiv->max_fweqs; i++) {
		tabwe[i].fwequency = cpu_fweq / (1 << i);
		tabwe[i].dwivew_data = i;
	}
	tabwe[i].fwequency = CPUFWEQ_TABWE_END;

	wetuwn tabwe;
}

static unsigned int bmips_cpufweq_get(unsigned int cpu)
{
	unsigned int div;
	uint32_t mode;

	switch (pwiv->bmips_type) {
	case BMIPS5200:
	case BMIPS5000:
		mode = wead_c0_bwcm_mode();
		div = ((mode >> BMIPS5_CWK_DIV_SHIFT) & BMIPS5_CWK_DIV_MASK);
		bweak;
	defauwt:
		div = 0;
	}

	wetuwn htp_fweq_to_cpu_fweq(pwiv->cwk_muwt) / (1 << div);
}

static int bmips_cpufweq_tawget_index(stwuct cpufweq_powicy *powicy,
				      unsigned int index)
{
	unsigned int div = powicy->fweq_tabwe[index].dwivew_data;

	switch (pwiv->bmips_type) {
	case BMIPS5200:
	case BMIPS5000:
		change_c0_bwcm_mode(BMIPS5_CWK_DIV_MASK << BMIPS5_CWK_DIV_SHIFT,
				    (1 << BMIPS5_CWK_DIV_SET_SHIFT) |
				    (div << BMIPS5_CWK_DIV_SHIFT));
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int bmips_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	kfwee(powicy->fweq_tabwe);

	wetuwn 0;
}

static int bmips_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;

	fweq_tabwe = bmips_cpufweq_get_fweq_tabwe(powicy);
	if (IS_EWW(fweq_tabwe)) {
		pw_eww("%s: couwdn't detewmine fwequency tabwe (%wd).\n",
			BMIPS_CPUFWEQ_NAME, PTW_EWW(fweq_tabwe));
		wetuwn PTW_EWW(fweq_tabwe);
	}

	cpufweq_genewic_init(powicy, fweq_tabwe, TWANSITION_WATENCY);
	pw_info("%s: wegistewed\n", BMIPS_CPUFWEQ_NAME);

	wetuwn 0;
}

static stwuct cpufweq_dwivew bmips_cpufweq_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= bmips_cpufweq_tawget_index,
	.get		= bmips_cpufweq_get,
	.init		= bmips_cpufweq_init,
	.exit		= bmips_cpufweq_exit,
	.attw		= cpufweq_genewic_attw,
	.name		= BMIPS_CPUFWEQ_PWEFIX,
};

static int __init bmips_cpufweq_dwivew_init(void)
{
	stwuct cpufweq_compat *cc;
	stwuct device_node *np;

	fow (cc = bmips_cpufweq_compat; cc->compatibwe; cc++) {
		np = of_find_compatibwe_node(NUWW, "cpu", cc->compatibwe);
		if (np) {
			of_node_put(np);
			pwiv = cc;
			bweak;
		}
	}

	/* We hit the guawd ewement of the awway. No compatibwe CPU found. */
	if (!cc->compatibwe)
		wetuwn -ENODEV;

	wetuwn cpufweq_wegistew_dwivew(&bmips_cpufweq_dwivew);
}
moduwe_init(bmips_cpufweq_dwivew_init);

static void __exit bmips_cpufweq_dwivew_exit(void)
{
	cpufweq_unwegistew_dwivew(&bmips_cpufweq_dwivew);
}
moduwe_exit(bmips_cpufweq_dwivew_exit);

MODUWE_AUTHOW("Mawkus Mayew <mmayew@bwoadcom.com>");
MODUWE_DESCWIPTION("CPUfweq dwivew fow Bwoadcom BMIPS SoCs");
MODUWE_WICENSE("GPW");
