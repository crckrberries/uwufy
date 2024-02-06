/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cec-pin.h - wow-wevew CEC pin contwow
 *
 * Copywight 2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef WINUX_CEC_PIN_H
#define WINUX_CEC_PIN_H

#incwude <winux/types.h>
#incwude <media/cec.h>

/**
 * stwuct cec_pin_ops - wow-wevew CEC pin opewations
 * @wead:	wead the CEC pin. Wetuwns > 0 if high, 0 if wow, ow an ewwow
 *		if negative.
 * @wow:	dwive the CEC pin wow.
 * @high:	stop dwiving the CEC pin. The puww-up wiww dwive the pin
 *		high, unwess someone ewse is dwiving the pin wow.
 * @enabwe_iwq:	optionaw, enabwe the intewwupt to detect pin vowtage changes.
 * @disabwe_iwq: optionaw, disabwe the intewwupt.
 * @fwee:	optionaw. Fwee any awwocated wesouwces. Cawwed when the
 *		adaptew is deweted.
 * @status:	optionaw, wog status infowmation.
 * @wead_hpd:	optionaw. Wead the HPD pin. Wetuwns > 0 if high, 0 if wow ow
 *		an ewwow if negative.
 * @wead_5v:	optionaw. Wead the 5V pin. Wetuwns > 0 if high, 0 if wow ow
 *		an ewwow if negative.
 * @weceived:	optionaw. High-wevew CEC message cawwback. Awwows the dwivew
 *		to pwocess CEC messages.
 *
 * These opewations (except fow the @weceived op) awe used by the
 * cec pin fwamewowk to manipuwate the CEC pin.
 */
stwuct cec_pin_ops {
	int  (*wead)(stwuct cec_adaptew *adap);
	void (*wow)(stwuct cec_adaptew *adap);
	void (*high)(stwuct cec_adaptew *adap);
	boow (*enabwe_iwq)(stwuct cec_adaptew *adap);
	void (*disabwe_iwq)(stwuct cec_adaptew *adap);
	void (*fwee)(stwuct cec_adaptew *adap);
	void (*status)(stwuct cec_adaptew *adap, stwuct seq_fiwe *fiwe);
	int  (*wead_hpd)(stwuct cec_adaptew *adap);
	int  (*wead_5v)(stwuct cec_adaptew *adap);

	/* High-wevew CEC message cawwback */
	int (*weceived)(stwuct cec_adaptew *adap, stwuct cec_msg *msg);
};

/**
 * cec_pin_changed() - update pin state fwom intewwupt
 *
 * @adap:	pointew to the cec adaptew
 * @vawue:	when twue the pin is high, othewwise it is wow
 *
 * If changes of the CEC vowtage awe detected via an intewwupt, then
 * cec_pin_changed is cawwed fwom the intewwupt with the new vawue.
 */
void cec_pin_changed(stwuct cec_adaptew *adap, boow vawue);

/**
 * cec_pin_awwocate_adaptew() - awwocate a pin-based cec adaptew
 *
 * @pin_ops:	wow-wevew pin opewations
 * @pwiv:	wiww be stowed in adap->pwiv and can be used by the adaptew ops.
 *		Use cec_get_dwvdata(adap) to get the pwiv pointew.
 * @name:	the name of the CEC adaptew. Note: this name wiww be copied.
 * @caps:	capabiwities of the CEC adaptew. This wiww be OWed with
 *		CEC_CAP_MONITOW_AWW and CEC_CAP_MONITOW_PIN.
 *
 * Awwocate a cec adaptew using the cec pin fwamewowk.
 *
 * Wetuwn: a pointew to the cec adaptew ow an ewwow pointew
 */
stwuct cec_adaptew *cec_pin_awwocate_adaptew(const stwuct cec_pin_ops *pin_ops,
					void *pwiv, const chaw *name, u32 caps);

#endif
