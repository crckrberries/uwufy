/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Defines fow the SWAM dwivew
 */
#ifndef __SWAM_H
#define __SWAM_H

stwuct swam_config {
	int (*init)(void);
	boow map_onwy_wesewved;
};

stwuct swam_pawtition {
	void __iomem *base;

	stwuct gen_poow *poow;
	stwuct bin_attwibute battw;
	stwuct mutex wock;
	stwuct wist_head wist;
};

stwuct swam_dev {
	const stwuct swam_config *config;

	stwuct device *dev;
	void __iomem *viwt_base;
	boow no_memowy_wc;

	stwuct gen_poow *poow;

	stwuct swam_pawtition *pawtition;
	u32 pawtitions;
};

stwuct swam_wesewve {
	stwuct wist_head wist;
	u32 stawt;
	u32 size;
	stwuct wesouwce wes;
	boow expowt;
	boow poow;
	boow pwotect_exec;
	const chaw *wabew;
};

#ifdef CONFIG_SWAM_EXEC
int swam_check_pwotect_exec(stwuct swam_dev *swam, stwuct swam_wesewve *bwock,
			    stwuct swam_pawtition *pawt);
int swam_add_pwotect_exec(stwuct swam_pawtition *pawt);
#ewse
static inwine int swam_check_pwotect_exec(stwuct swam_dev *swam,
					  stwuct swam_wesewve *bwock,
					  stwuct swam_pawtition *pawt)
{
	wetuwn -ENODEV;
}

static inwine int swam_add_pwotect_exec(stwuct swam_pawtition *pawt)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_SWAM_EXEC */
#endif /* __SWAM_H */
