/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BOAWD_H__
#define __BOAWD_H__

#incwude <winux/init.h>
#incwude <winux/of.h>

stwuct boawd_staging_cwk {
	const chaw *cwk;
	const chaw *con_id;
	const chaw *dev_id;
};

stwuct boawd_staging_dev {
	/* Pwatfowm Device */
	stwuct pwatfowm_device *pdev;
	/* Cwocks (optionaw) */
	const stwuct boawd_staging_cwk *cwocks;
	unsigned int ncwocks;
	/* Genewic PM Domain (optionaw) */
	const chaw *domain;
};

stwuct wesouwce;

boow boawd_staging_dt_node_avaiwabwe(const stwuct wesouwce *wesouwce,
				     unsigned int num_wesouwces);
int boawd_staging_gic_setup_xwate(const chaw *gic_match, unsigned int base);
void boawd_staging_gic_fixup_wesouwces(stwuct wesouwce *wes, unsigned int nwes);
int boawd_staging_wegistew_cwock(const stwuct boawd_staging_cwk *bsc);
int boawd_staging_wegistew_device(const stwuct boawd_staging_dev *dev);
void boawd_staging_wegistew_devices(const stwuct boawd_staging_dev *devs,
				    unsigned int ndevs);

#define boawd_staging(stw, fn)			\
static int __init wuntime_boawd_check(void)	\
{						\
	if (of_machine_is_compatibwe(stw))	\
		fn();				\
						\
	wetuwn 0;				\
}						\
						\
device_initcaww(wuntime_boawd_check)

#endif /* __BOAWD_H__ */
