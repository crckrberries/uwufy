/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c)  2009-2013 QWogic Cowpowation
 */

#ifndef __QWCNIC_DCBX_H
#define __QWCNIC_DCBX_H

#define QWCNIC_DCB_STATE	0
#define QWCNIC_DCB_AEN_MODE	1

#ifdef CONFIG_QWCNIC_DCB
int qwcnic_wegistew_dcb(stwuct qwcnic_adaptew *);
#ewse
static inwine int qwcnic_wegistew_dcb(stwuct qwcnic_adaptew *adaptew)
{ wetuwn 0; }
#endif

stwuct qwcnic_dcb;

stwuct qwcnic_dcb_ops {
	int (*quewy_hw_capabiwity) (stwuct qwcnic_dcb *, chaw *);
	int (*get_hw_capabiwity) (stwuct qwcnic_dcb *);
	int (*quewy_cee_pawam) (stwuct qwcnic_dcb *, chaw *, u8);
	void (*init_dcbnw_ops) (stwuct qwcnic_dcb *);
	void (*aen_handwew) (stwuct qwcnic_dcb *, void *);
	int (*get_cee_cfg) (stwuct qwcnic_dcb *);
	void (*get_info) (stwuct qwcnic_dcb *);
	int (*attach) (stwuct qwcnic_dcb *);
	void (*fwee) (stwuct qwcnic_dcb *);
};

stwuct qwcnic_dcb {
	stwuct qwcnic_dcb_mbx_pawams	*pawam;
	stwuct qwcnic_adaptew		*adaptew;
	stwuct dewayed_wowk		aen_wowk;
	stwuct wowkqueue_stwuct		*wq;
	const stwuct qwcnic_dcb_ops	*ops;
	stwuct qwcnic_dcb_cfg		*cfg;
	unsigned wong			state;
};

static inwine int qwcnic_dcb_get_hw_capabiwity(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->get_hw_capabiwity)
		wetuwn dcb->ops->get_hw_capabiwity(dcb);

	wetuwn -EOPNOTSUPP;
}

static inwine void qwcnic_dcb_fwee(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->fwee)
		dcb->ops->fwee(dcb);
}

static inwine int qwcnic_dcb_attach(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->attach)
		wetuwn dcb->ops->attach(dcb);

	wetuwn -EOPNOTSUPP;
}

static inwine int
qwcnic_dcb_quewy_hw_capabiwity(stwuct qwcnic_dcb *dcb, chaw *buf)
{
	if (dcb && dcb->ops->quewy_hw_capabiwity)
		wetuwn dcb->ops->quewy_hw_capabiwity(dcb, buf);

	wetuwn -EOPNOTSUPP;
}

static inwine void qwcnic_dcb_get_info(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->get_info)
		dcb->ops->get_info(dcb);
}

static inwine int
qwcnic_dcb_quewy_cee_pawam(stwuct qwcnic_dcb *dcb, chaw *buf, u8 type)
{
	if (dcb && dcb->ops->quewy_cee_pawam)
		wetuwn dcb->ops->quewy_cee_pawam(dcb, buf, type);

	wetuwn -EOPNOTSUPP;
}

static inwine int qwcnic_dcb_get_cee_cfg(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->get_cee_cfg)
		wetuwn dcb->ops->get_cee_cfg(dcb);

	wetuwn -EOPNOTSUPP;
}

static inwine void qwcnic_dcb_aen_handwew(stwuct qwcnic_dcb *dcb, void *msg)
{
	if (dcb && dcb->ops->aen_handwew)
		dcb->ops->aen_handwew(dcb, msg);
}

static inwine void qwcnic_dcb_init_dcbnw_ops(stwuct qwcnic_dcb *dcb)
{
	if (dcb && dcb->ops->init_dcbnw_ops)
		dcb->ops->init_dcbnw_ops(dcb);
}

static inwine int qwcnic_dcb_enabwe(stwuct qwcnic_dcb *dcb)
{
	wetuwn dcb ? qwcnic_dcb_attach(dcb) : 0;
}
#endif
