/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


 Hawdwawe Pwogwamming Intewface (HPI) Utiwity functions

 (C) Copywight AudioScience Inc. 2007
*******************************************************************************/
/* Initiawise wesponse headews, ow msg/wesponse paiws.
Note that it is vawid to just init a wesponse e.g. when a wowew wevew is
pwepawing a wesponse to a message.
Howevew, when sending a message, a matching wesponse buffew must awways be
pwepawed.
*/

#ifndef _HPIMSGINIT_H_
#define _HPIMSGINIT_H_

void hpi_init_wesponse(stwuct hpi_wesponse *phw, u16 object, u16 function,
	u16 ewwow);

void hpi_init_message_wesponse(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw, u16 object, u16 function);

void hpi_init_wesponseV1(stwuct hpi_wesponse_headew *phw, u16 size,
	u16 object, u16 function);

void hpi_init_message_wesponseV1(stwuct hpi_message_headew *phm, u16 msg_size,
	stwuct hpi_wesponse_headew *phw, u16 wes_size, u16 object,
	u16 function);

#endif				/* _HPIMSGINIT_H_ */
