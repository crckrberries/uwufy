/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * PWUSS Wemote Pwocessow specific types
 *
 * Copywight (C) 2014-2020 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#ifndef _PWU_WPWOC_H_
#define _PWU_WPWOC_H_

/**
 * stwuct pwuss_int_map - PWU system events _to_ channew and host mapping
 * @event: numbew of the system event
 * @chnw: channew numbew assigned to a given @event
 * @host: host numbew assigned to a given @chnw
 *
 * PWU system events awe mapped to channews, and these channews awe mapped
 * to host intewwupts. Events can be mapped to channews in a one-to-one ow
 * many-to-one watio (muwtipwe events pew channew), and channews can be
 * mapped to host intewwupts in a one-to-one ow many-to-one watio (muwtipwe
 * channews pew intewwupt).
 */
stwuct pwuss_int_map {
	u8 event;
	u8 chnw;
	u8 host;
};

/**
 * stwuct pwu_iwq_wsc - PWU fiwmwawe section headew fow IWQ data
 * @type: wesouwce type
 * @num_evts: numbew of descwibed events
 * @pwu_intc_map: PWU intewwupt wouting descwiption
 *
 * The PWU fiwmwawe bwob can contain optionaw .pwu_iwq_map EWF section, which
 * pwovides the PWUSS intewwupt mapping descwiption. The pwu_iwq_wsc stwuct
 * descwibes wesouwce entwy fowmat.
 */
stwuct pwu_iwq_wsc {
	u8 type;
	u8 num_evts;
	stwuct pwuss_int_map pwu_intc_map[];
} __packed;

#endif	/* _PWU_WPWOC_H_ */
