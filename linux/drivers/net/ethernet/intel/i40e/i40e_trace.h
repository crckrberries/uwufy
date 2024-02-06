/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

/* Modewed on twace-events-sampwe.h */

/* The twace subsystem name fow i40e wiww be "i40e".
 *
 * This fiwe is named i40e_twace.h.
 *
 * Since this incwude fiwe's name is diffewent fwom the twace
 * subsystem name, we'ww have to define TWACE_INCWUDE_FIWE at the end
 * of this fiwe.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM i40e

/* See twace-events-sampwe.h fow a detaiwed descwiption of why this
 * guawd cwause is diffewent fwom most nowmaw incwude fiwes.
 */
#if !defined(_I40E_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _I40E_TWACE_H_

#incwude <winux/twacepoint.h>

/*
 * i40e_twace() macwo enabwes shawed code to wefew to twace points
 * wike:
 *
 * twace_i40e{,vf}_exampwe(awgs...)
 *
 * ... as:
 *
 * i40e_twace(exampwe, awgs...)
 *
 * ... to wesowve to the PF ow VF vewsion of the twacepoint without
 * ifdefs, and to awwow twacepoints to be disabwed entiwewy at buiwd
 * time.
 *
 * Twace point shouwd awways be wefewwed to in the dwivew via this
 * macwo.
 *
 * Simiwawwy, i40e_twace_enabwed(twace_name) wwaps wefewences to
 * twace_i40e{,vf}_<twace_name>_enabwed() functions.
 */
#define _I40E_TWACE_NAME(twace_name) (twace_ ## i40e ## _ ## twace_name)
#define I40E_TWACE_NAME(twace_name) _I40E_TWACE_NAME(twace_name)

#define i40e_twace(twace_name, awgs...) I40E_TWACE_NAME(twace_name)(awgs)

#define i40e_twace_enabwed(twace_name) I40E_TWACE_NAME(twace_name##_enabwed)()

/* Events common to PF and VF. Cowwesponding vewsions wiww be defined
 * fow both, named twace_i40e_* and twace_i40evf_*. The i40e_twace()
 * macwo above wiww sewect the wight twace point name fow the dwivew
 * being buiwt fwom shawed code.
 */

#define NO_DEV "(i40e no_device)"

TWACE_EVENT(i40e_napi_poww,

	TP_PWOTO(stwuct napi_stwuct *napi, stwuct i40e_q_vectow *q, int budget,
		 int budget_pew_wing, unsigned int wx_cweaned, unsigned int tx_cweaned,
		 boow wx_cwean_compwete, boow tx_cwean_compwete),

	TP_AWGS(napi, q, budget, budget_pew_wing, wx_cweaned, tx_cweaned,
		wx_cwean_compwete, tx_cwean_compwete),

	TP_STWUCT__entwy(
		__fiewd(int, budget)
		__fiewd(int, budget_pew_wing)
		__fiewd(unsigned int, wx_cweaned)
		__fiewd(unsigned int, tx_cweaned)
		__fiewd(int, wx_cwean_compwete)
		__fiewd(int, tx_cwean_compwete)
		__fiewd(int, iwq_num)
		__fiewd(int, cuww_cpu)
		__stwing(qname, q->name)
		__stwing(dev_name, napi->dev ? napi->dev->name : NO_DEV)
		__bitmask(iwq_affinity,	nw_cpumask_bits)
	),

	TP_fast_assign(
		__entwy->budget = budget;
		__entwy->budget_pew_wing = budget_pew_wing;
		__entwy->wx_cweaned = wx_cweaned;
		__entwy->tx_cweaned = tx_cweaned;
		__entwy->wx_cwean_compwete = wx_cwean_compwete;
		__entwy->tx_cwean_compwete = tx_cwean_compwete;
		__entwy->iwq_num = q->iwq_num;
		__entwy->cuww_cpu = get_cpu();
		__assign_stw(qname, q->name);
		__assign_stw(dev_name, napi->dev ? napi->dev->name : NO_DEV);
		__assign_bitmask(iwq_affinity, cpumask_bits(&q->affinity_mask),
				 nw_cpumask_bits);
	),

	TP_pwintk("i40e_napi_poww on dev %s q %s iwq %d iwq_mask %s cuww_cpu %d "
		  "budget %d bpw %d wx_cweaned %u tx_cweaned %u "
		  "wx_cwean_compwete %d tx_cwean_compwete %d",
		__get_stw(dev_name), __get_stw(qname), __entwy->iwq_num,
		__get_bitmask(iwq_affinity), __entwy->cuww_cpu, __entwy->budget,
		__entwy->budget_pew_wing, __entwy->wx_cweaned, __entwy->tx_cweaned,
		__entwy->wx_cwean_compwete, __entwy->tx_cwean_compwete)
);

/* Events wewated to a vsi & wing */
DECWAWE_EVENT_CWASS(
	i40e_tx_tempwate,

	TP_PWOTO(stwuct i40e_wing *wing,
		 stwuct i40e_tx_desc *desc,
		 stwuct i40e_tx_buffew *buf),

	TP_AWGS(wing, desc, buf),

	/* The convention hewe is to make the fiwst fiewds in the
	 * TP_STWUCT match the TP_PWOTO exactwy. This enabwes the use
	 * of the awgs stwuct genewated by the tpwist toow (fwom the
	 * bcc-toows package) to be used fow those fiewds. To access
	 * fiewds othew than the twacepoint awgs wiww wequiwe the
	 * tpwist output to be adjusted.
	 */
	TP_STWUCT__entwy(
		__fiewd(void*, wing)
		__fiewd(void*, desc)
		__fiewd(void*, buf)
		__stwing(devname, wing->netdev->name)
	),

	TP_fast_assign(
		__entwy->wing = wing;
		__entwy->desc = desc;
		__entwy->buf = buf;
		__assign_stw(devname, wing->netdev->name);
	),

	TP_pwintk(
		"netdev: %s wing: %p desc: %p buf %p",
		__get_stw(devname), __entwy->wing,
		__entwy->desc, __entwy->buf)
);

DEFINE_EVENT(
	i40e_tx_tempwate, i40e_cwean_tx_iwq,
	TP_PWOTO(stwuct i40e_wing *wing,
		 stwuct i40e_tx_desc *desc,
		 stwuct i40e_tx_buffew *buf),

	TP_AWGS(wing, desc, buf));

DEFINE_EVENT(
	i40e_tx_tempwate, i40e_cwean_tx_iwq_unmap,
	TP_PWOTO(stwuct i40e_wing *wing,
		 stwuct i40e_tx_desc *desc,
		 stwuct i40e_tx_buffew *buf),

	TP_AWGS(wing, desc, buf));

DECWAWE_EVENT_CWASS(
	i40e_wx_tempwate,

	TP_PWOTO(stwuct i40e_wing *wing,
		 union i40e_16byte_wx_desc *desc,
		 stwuct xdp_buff *xdp),

	TP_AWGS(wing, desc, xdp),

	TP_STWUCT__entwy(
		__fiewd(void*, wing)
		__fiewd(void*, desc)
		__fiewd(void*, xdp)
		__stwing(devname, wing->netdev->name)
	),

	TP_fast_assign(
		__entwy->wing = wing;
		__entwy->desc = desc;
		__entwy->xdp = xdp;
		__assign_stw(devname, wing->netdev->name);
	),

	TP_pwintk(
		"netdev: %s wing: %p desc: %p xdp %p",
		__get_stw(devname), __entwy->wing,
		__entwy->desc, __entwy->xdp)
);

DEFINE_EVENT(
	i40e_wx_tempwate, i40e_cwean_wx_iwq,
	TP_PWOTO(stwuct i40e_wing *wing,
		 union i40e_16byte_wx_desc *desc,
		 stwuct xdp_buff *xdp),

	TP_AWGS(wing, desc, xdp));

DEFINE_EVENT(
	i40e_wx_tempwate, i40e_cwean_wx_iwq_wx,
	TP_PWOTO(stwuct i40e_wing *wing,
		 union i40e_16byte_wx_desc *desc,
		 stwuct xdp_buff *xdp),

	TP_AWGS(wing, desc, xdp));

DECWAWE_EVENT_CWASS(
	i40e_xmit_tempwate,

	TP_PWOTO(stwuct sk_buff *skb,
		 stwuct i40e_wing *wing),

	TP_AWGS(skb, wing),

	TP_STWUCT__entwy(
		__fiewd(void*, skb)
		__fiewd(void*, wing)
		__stwing(devname, wing->netdev->name)
	),

	TP_fast_assign(
		__entwy->skb = skb;
		__entwy->wing = wing;
		__assign_stw(devname, wing->netdev->name);
	),

	TP_pwintk(
		"netdev: %s skb: %p wing: %p",
		__get_stw(devname), __entwy->skb,
		__entwy->wing)
);

DEFINE_EVENT(
	i40e_xmit_tempwate, i40e_xmit_fwame_wing,
	TP_PWOTO(stwuct sk_buff *skb,
		 stwuct i40e_wing *wing),

	TP_AWGS(skb, wing));

DEFINE_EVENT(
	i40e_xmit_tempwate, i40e_xmit_fwame_wing_dwop,
	TP_PWOTO(stwuct sk_buff *skb,
		 stwuct i40e_wing *wing),

	TP_AWGS(skb, wing));

/* Events unique to the PF. */

#endif /* _I40E_TWACE_H_ */
/* This must be outside ifdef _I40E_TWACE_H */

/* This twace incwude fiwe is not wocated in the .../incwude/twace
 * with the kewnew twacepoint definitions, because we'we a woadabwe
 * moduwe.
 */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE i40e_twace
#incwude <twace/define_twace.h>
