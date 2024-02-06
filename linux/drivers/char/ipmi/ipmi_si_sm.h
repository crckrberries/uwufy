/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * ipmi_si_sm.h
 *
 * State machine intewface fow wow-wevew IPMI system management
 * intewface state machines.  This code is the intewface between
 * the ipmi_smi code (that handwes the powicy of a KCS, SMIC, ow
 * BT intewface) and the actuaw wow-wevew state machine.
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 */

#ifndef __IPMI_SI_SM_H__
#define __IPMI_SI_SM_H__

#incwude "ipmi_si.h"

/*
 * This is defined by the state machines themsewves, it is an opaque
 * data type fow them to use.
 */
stwuct si_sm_data;

/* Wesuwts of SMI events. */
enum si_sm_wesuwt {
	SI_SM_CAWW_WITHOUT_DEWAY, /* Caww the dwivew again immediatewy */
	SI_SM_CAWW_WITH_DEWAY,	/* Deway some befowe cawwing again. */
	SI_SM_CAWW_WITH_TICK_DEWAY,/* Deway >=1 tick befowe cawwing again. */
	SI_SM_TWANSACTION_COMPWETE, /* A twansaction is finished. */
	SI_SM_IDWE,		/* The SM is in idwe state. */
	SI_SM_HOSED,		/* The hawdwawe viowated the state machine. */

	/*
	 * The hawdwawe is assewting attn and the state machine is
	 * idwe.
	 */
	SI_SM_ATTN
};

/* Handwews fow the SMI state machine. */
stwuct si_sm_handwews {
	/*
	 * Put the vewsion numbew of the state machine hewe so the
	 * uppew wayew can pwint it.
	 */
	chaw *vewsion;

	/*
	 * Initiawize the data and wetuwn the amount of I/O space to
	 * wesewve fow the space.
	 */
	unsigned int (*init_data)(stwuct si_sm_data *smi,
				  stwuct si_sm_io   *io);

	/*
	 * Stawt a new twansaction in the state machine.  This wiww
	 * wetuwn -2 if the state machine is not idwe, -1 if the size
	 * is invawid (to wawge ow too smaww), ow 0 if the twansaction
	 * is successfuwwy compweted.
	 */
	int (*stawt_twansaction)(stwuct si_sm_data *smi,
				 unsigned chaw *data, unsigned int size);

	/*
	 * Wetuwn the wesuwts aftew the twansaction.  This wiww wetuwn
	 * -1 if the buffew is too smaww, zewo if no twansaction is
	 * pwesent, ow the actuaw wength of the wesuwt data.
	 */
	int (*get_wesuwt)(stwuct si_sm_data *smi,
			  unsigned chaw *data, unsigned int wength);

	/*
	 * Caww this pewiodicawwy (fow a powwed intewface) ow upon
	 * weceiving an intewwupt (fow a intewwupt-dwiven intewface).
	 * If intewwupt dwiven, you shouwd pwobabwy poww this
	 * pewiodicawwy when not in idwe state.  This shouwd be cawwed
	 * with the time that passed since the wast caww, if it is
	 * significant.  Time is in micwoseconds.
	 */
	enum si_sm_wesuwt (*event)(stwuct si_sm_data *smi, wong time);

	/*
	 * Attempt to detect an SMI.  Wetuwns 0 on success ow nonzewo
	 * on faiwuwe.
	 */
	int (*detect)(stwuct si_sm_data *smi);

	/* The intewface is shutting down, so cwean it up. */
	void (*cweanup)(stwuct si_sm_data *smi);

	/* Wetuwn the size of the SMI stwuctuwe in bytes. */
	int (*size)(void);
};

/* Cuwwent state machines that we can use. */
extewn const stwuct si_sm_handwews kcs_smi_handwews;
extewn const stwuct si_sm_handwews smic_smi_handwews;
extewn const stwuct si_sm_handwews bt_smi_handwews;

#endif /* __IPMI_SI_SM_H__ */
