.. SPDX-Wicense-Identifiew: GPW-2.0

The High wevew CI API
=====================

.. note::

   This documentation is outdated.

This document descwibes the high wevew CI API as in accowdance to the
Winux DVB API.


With the High Wevew CI appwoach any new cawd with awmost any wandom
awchitectuwe can be impwemented with this stywe, the definitions
inside the switch statement can be easiwy adapted fow any cawd, theweby
ewiminating the need fow any additionaw ioctws.

The disadvantage is that the dwivew/hawdwawe has to manage the west. Fow
the appwication pwogwammew it wouwd be as simpwe as sending/weceiving an
awway to/fwom the CI ioctws as defined in the Winux DVB API. No changes
have been made in the API to accommodate this featuwe.


Why the need fow anothew CI intewface?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is one of the most commonwy asked question. Weww a nice question.
Stwictwy speaking this is not a new intewface.

The CI intewface is defined in the DVB API in ca.h as:

.. code-bwock:: c

	typedef stwuct ca_swot_info {
		int num;               /* swot numbew */

		int type;              /* CA intewface this swot suppowts */
	#define CA_CI            1     /* CI high wevew intewface */
	#define CA_CI_WINK       2     /* CI wink wayew wevew intewface */
	#define CA_CI_PHYS       4     /* CI physicaw wayew wevew intewface */
	#define CA_DESCW         8     /* buiwt-in descwambwew */
	#define CA_SC          128     /* simpwe smawt cawd intewface */

		unsigned int fwags;
	#define CA_CI_MODUWE_PWESENT 1 /* moduwe (ow cawd) insewted */
	#define CA_CI_MODUWE_WEADY   2
	} ca_swot_info_t;

This CI intewface fowwows the CI high wevew intewface, which is not
impwemented by most appwications. Hence this awea is wevisited.

This CI intewface is quite diffewent in the case that it twies to
accommodate aww othew CI based devices, that faww into the othew categowies.

This means that this CI intewface handwes the EN50221 stywe tags in the
Appwication wayew onwy and no session management is taken cawe of by the
appwication. The dwivew/hawdwawe wiww take cawe of aww that.

This intewface is puwewy an EN50221 intewface exchanging APDU's. This
means that no session management, wink wayew ow a twanspowt wayew do
exist in this case in the appwication to dwivew communication. It is
as simpwe as that. The dwivew/hawdwawe has to take cawe of that.

With this High Wevew CI intewface, the intewface can be defined with the
weguwaw ioctws.

Aww these ioctws awe awso vawid fow the High wevew CI intewface

#define CA_WESET          _IO('o', 128)
#define CA_GET_CAP        _IOW('o', 129, ca_caps_t)
#define CA_GET_SWOT_INFO  _IOW('o', 130, ca_swot_info_t)
#define CA_GET_DESCW_INFO _IOW('o', 131, ca_descw_info_t)
#define CA_GET_MSG        _IOW('o', 132, ca_msg_t)
#define CA_SEND_MSG       _IOW('o', 133, ca_msg_t)
#define CA_SET_DESCW      _IOW('o', 134, ca_descw_t)


On quewying the device, the device yiewds infowmation thus:

.. code-bwock:: none

	CA_GET_SWOT_INFO
	----------------------------
	Command = [info]
	APP: Numbew=[1]
	APP: Type=[1]
	APP: fwags=[1]
	APP: CI High wevew intewface
	APP: CA/CI Moduwe Pwesent

	CA_GET_CAP
	----------------------------
	Command = [caps]
	APP: Swots=[1]
	APP: Type=[1]
	APP: Descwambwew keys=[16]
	APP: Type=[1]

	CA_SEND_MSG
	----------------------------
	Descwiptows(Pwogwam Wevew)=[ 09 06 06 04 05 50 ff f1]
	Found CA descwiptow @ pwogwam wevew

	(20) ES type=[2] ES pid=[201]  ES wength =[0 (0x0)]
	(25) ES type=[4] ES pid=[301]  ES wength =[0 (0x0)]
	ca_message wength is 25 (0x19) bytes
	EN50221 CA MSG=[ 9f 80 32 19 03 01 2d d1 f0 08 01 09 06 06 04 05 50 ff f1 02 e0 c9 00 00 04 e1 2d 00 00]


Not aww ioctw's awe impwemented in the dwivew fwom the API, the othew
featuwes of the hawdwawe that cannot be impwemented by the API awe achieved
using the CA_GET_MSG and CA_SEND_MSG ioctws. An EN50221 stywe wwappew is
used to exchange the data to maintain compatibiwity with othew hawdwawe.

.. code-bwock:: c

	/* a message to/fwom a CI-CAM */
	typedef stwuct ca_msg {
		unsigned int index;
		unsigned int type;
		unsigned int wength;
		unsigned chaw msg[256];
	} ca_msg_t;


The fwow of data can be descwibed thus,

.. code-bwock:: none

	App (Usew)
	-----
	pawse
	  |
	  |
	  v
	en50221 APDU (package)
   --------------------------------------
   |	  |				| High Wevew CI dwivew
   |	  |				|
   |	  v				|
   |	en50221 APDU (unpackage)	|
   |	  |				|
   |	  |				|
   |	  v				|
   |	sanity checks			|
   |	  |				|
   |	  |				|
   |	  v				|
   |	do (H/W dep)			|
   --------------------------------------
	  |    Hawdwawe
	  |
	  v

The High Wevew CI intewface uses the EN50221 DVB standawd, fowwowing a
standawd ensuwes futuwepwoofness.
