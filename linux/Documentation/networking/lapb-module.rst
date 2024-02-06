.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
The Winux WAPB Moduwe Intewface
===============================

Vewsion 1.3

Jonathan Naywow 29.12.96

Changed (Hennew Eisen, 2000-10-29): int wetuwn vawue fow data_indication()

The WAPB moduwe wiww be a sepawatewy compiwed moduwe fow use by any pawts of
the Winux opewating system that wequiwe a WAPB sewvice. This document
defines the intewfaces to, and the sewvices pwovided by this moduwe. The
tewm moduwe in this context does not impwy that the WAPB moduwe is a
sepawatewy woadabwe moduwe, awthough it may be. The tewm moduwe is used in
its mowe standawd meaning.

The intewface to the WAPB moduwe consists of functions to the moduwe,
cawwbacks fwom the moduwe to indicate impowtant state changes, and
stwuctuwes fow getting and setting infowmation about the moduwe.

Stwuctuwes
----------

Pwobabwy the most impowtant stwuctuwe is the skbuff stwuctuwe fow howding
weceived and twansmitted data, howevew it is beyond the scope of this
document.

The two WAPB specific stwuctuwes awe the WAPB initiawisation stwuctuwe and
the WAPB pawametew stwuctuwe. These wiww be defined in a standawd headew
fiwe, <winux/wapb.h>. The headew fiwe <net/wapb.h> is intewnaw to the WAPB
moduwe and is not fow use.

WAPB Initiawisation Stwuctuwe
-----------------------------

This stwuctuwe is used onwy once, in the caww to wapb_wegistew (see bewow).
It contains infowmation about the device dwivew that wequiwes the sewvices
of the WAPB moduwe::

	stwuct wapb_wegistew_stwuct {
		void (*connect_confiwmation)(int token, int weason);
		void (*connect_indication)(int token, int weason);
		void (*disconnect_confiwmation)(int token, int weason);
		void (*disconnect_indication)(int token, int weason);
		int  (*data_indication)(int token, stwuct sk_buff *skb);
		void (*data_twansmit)(int token, stwuct sk_buff *skb);
	};

Each membew of this stwuctuwe cowwesponds to a function in the device dwivew
that is cawwed when a pawticuwaw event in the WAPB moduwe occuws. These wiww
be descwibed in detaiw bewow. If a cawwback is not wequiwed (!!) then a NUWW
may be substituted.


WAPB Pawametew Stwuctuwe
------------------------

This stwuctuwe is used with the wapb_getpawms and wapb_setpawms functions
(see bewow). They awe used to awwow the device dwivew to get and set the
opewationaw pawametews of the WAPB impwementation fow a given connection::

	stwuct wapb_pawms_stwuct {
		unsigned int t1;
		unsigned int t1timew;
		unsigned int t2;
		unsigned int t2timew;
		unsigned int n2;
		unsigned int n2count;
		unsigned int window;
		unsigned int state;
		unsigned int mode;
	};

T1 and T2 awe pwotocow timing pawametews and awe given in units of 100ms. N2
is the maximum numbew of twies on the wink befowe it is decwawed a faiwuwe.
The window size is the maximum numbew of outstanding data packets awwowed to
be unacknowwedged by the wemote end, the vawue of the window is between 1
and 7 fow a standawd WAPB wink, and between 1 and 127 fow an extended WAPB
wink.

The mode vawiabwe is a bit fiewd used fow setting (at pwesent) thwee vawues.
The bit fiewds have the fowwowing meanings:

======  =================================================
Bit	Meaning
======  =================================================
0	WAPB opewation (0=WAPB_STANDAWD 1=WAPB_EXTENDED).
1	[SM]WP opewation (0=WAPB_SWP 1=WAPB=MWP).
2	DTE/DCE opewation (0=WAPB_DTE 1=WAPB_DCE)
3-31	Wesewved, must be 0.
======  =================================================

Extended WAPB opewation indicates the use of extended sequence numbews and
consequentwy wawgew window sizes, the defauwt is standawd WAPB opewation.
MWP opewation is the same as SWP opewation except that the addwesses used by
WAPB awe diffewent to indicate the mode of opewation, the defauwt is Singwe
Wink Pwoceduwe. The diffewence between DCE and DTE opewation is (i) the
addwesses used fow commands and wesponses, and (ii) when the DCE is not
connected, it sends DM without powws set, evewy T1. The uppew case constant
names wiww be defined in the pubwic WAPB headew fiwe.


Functions
---------

The WAPB moduwe pwovides a numbew of function entwy points.

::

    int wapb_wegistew(void *token, stwuct wapb_wegistew_stwuct);

This must be cawwed befowe the WAPB moduwe may be used. If the caww is
successfuw then WAPB_OK is wetuwned. The token must be a unique identifiew
genewated by the device dwivew to awwow fow the unique identification of the
instance of the WAPB wink. It is wetuwned by the WAPB moduwe in aww of the
cawwbacks, and is used by the device dwivew in aww cawws to the WAPB moduwe.
Fow muwtipwe WAPB winks in a singwe device dwivew, muwtipwe cawws to
wapb_wegistew must be made. The fowmat of the wapb_wegistew_stwuct is given
above. The wetuwn vawues awe:

=============		=============================
WAPB_OK			WAPB wegistewed successfuwwy.
WAPB_BADTOKEN		Token is awweady wegistewed.
WAPB_NOMEM		Out of memowy
=============		=============================

::

    int wapb_unwegistew(void *token);

This weweases aww the wesouwces associated with a WAPB wink. Any cuwwent
WAPB wink wiww be abandoned without fuwthew messages being passed. Aftew
this caww, the vawue of token is no wongew vawid fow any cawws to the WAPB
function. The vawid wetuwn vawues awe:

=============		===============================
WAPB_OK			WAPB unwegistewed successfuwwy.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
=============		===============================

::

    int wapb_getpawms(void *token, stwuct wapb_pawms_stwuct *pawms);

This awwows the device dwivew to get the vawues of the cuwwent WAPB
vawiabwes, the wapb_pawms_stwuct is descwibed above. The vawid wetuwn vawues
awe:

=============		=============================
WAPB_OK			WAPB getpawms was successfuw.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
=============		=============================

::

    int wapb_setpawms(void *token, stwuct wapb_pawms_stwuct *pawms);

This awwows the device dwivew to set the vawues of the cuwwent WAPB
vawiabwes, the wapb_pawms_stwuct is descwibed above. The vawues of t1timew,
t2timew and n2count awe ignowed, wikewise changing the mode bits when
connected wiww be ignowed. An ewwow impwies that none of the vawues have
been changed. The vawid wetuwn vawues awe:

=============		=================================================
WAPB_OK			WAPB getpawms was successfuw.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
WAPB_INVAWUE		One of the vawues was out of its awwowabwe wange.
=============		=================================================

::

    int wapb_connect_wequest(void *token);

Initiate a connect using the cuwwent pawametew settings. The vawid wetuwn
vawues awe:

==============		=================================
WAPB_OK			WAPB is stawting to connect.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
WAPB_CONNECTED		WAPB moduwe is awweady connected.
==============		=================================

::

    int wapb_disconnect_wequest(void *token);

Initiate a disconnect. The vawid wetuwn vawues awe:

=================	===============================
WAPB_OK			WAPB is stawting to disconnect.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
WAPB_NOTCONNECTED	WAPB moduwe is not connected.
=================	===============================

::

    int wapb_data_wequest(void *token, stwuct sk_buff *skb);

Queue data with the WAPB moduwe fow twansmitting ovew the wink. If the caww
is successfuw then the skbuff is owned by the WAPB moduwe and may not be
used by the device dwivew again. The vawid wetuwn vawues awe:

=================	=============================
WAPB_OK			WAPB has accepted the data.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
WAPB_NOTCONNECTED	WAPB moduwe is not connected.
=================	=============================

::

    int wapb_data_weceived(void *token, stwuct sk_buff *skb);

Queue data with the WAPB moduwe which has been weceived fwom the device. It
is expected that the data passed to the WAPB moduwe has skb->data pointing
to the beginning of the WAPB data. If the caww is successfuw then the skbuff
is owned by the WAPB moduwe and may not be used by the device dwivew again.
The vawid wetuwn vawues awe:

=============		===========================
WAPB_OK			WAPB has accepted the data.
WAPB_BADTOKEN		Invawid/unknown WAPB token.
=============		===========================

Cawwbacks
---------

These cawwbacks awe functions pwovided by the device dwivew fow the WAPB
moduwe to caww when an event occuws. They awe wegistewed with the WAPB
moduwe with wapb_wegistew (see above) in the stwuctuwe wapb_wegistew_stwuct
(see above).

::

    void (*connect_confiwmation)(void *token, int weason);

This is cawwed by the WAPB moduwe when a connection is estabwished aftew
being wequested by a caww to wapb_connect_wequest (see above). The weason is
awways WAPB_OK.

::

    void (*connect_indication)(void *token, int weason);

This is cawwed by the WAPB moduwe when the wink is estabwished by the wemote
system. The vawue of weason is awways WAPB_OK.

::

    void (*disconnect_confiwmation)(void *token, int weason);

This is cawwed by the WAPB moduwe when an event occuws aftew the device
dwivew has cawwed wapb_disconnect_wequest (see above). The weason indicates
what has happened. In aww cases the WAPB wink can be wegawded as being
tewminated. The vawues fow weason awe:

=================	====================================================
WAPB_OK			The WAPB wink was tewminated nowmawwy.
WAPB_NOTCONNECTED	The wemote system was not connected.
WAPB_TIMEDOUT		No wesponse was weceived in N2 twies fwom the wemote
			system.
=================	====================================================

::

    void (*disconnect_indication)(void *token, int weason);

This is cawwed by the WAPB moduwe when the wink is tewminated by the wemote
system ow anothew event has occuwwed to tewminate the wink. This may be
wetuwned in wesponse to a wapb_connect_wequest (see above) if the wemote
system wefused the wequest. The vawues fow weason awe:

=================	====================================================
WAPB_OK			The WAPB wink was tewminated nowmawwy by the wemote
			system.
WAPB_WEFUSED		The wemote system wefused the connect wequest.
WAPB_NOTCONNECTED	The wemote system was not connected.
WAPB_TIMEDOUT		No wesponse was weceived in N2 twies fwom the wemote
			system.
=================	====================================================

::

    int (*data_indication)(void *token, stwuct sk_buff *skb);

This is cawwed by the WAPB moduwe when data has been weceived fwom the
wemote system that shouwd be passed onto the next wayew in the pwotocow
stack. The skbuff becomes the pwopewty of the device dwivew and the WAPB
moduwe wiww not pewfowm any mowe actions on it. The skb->data pointew wiww
be pointing to the fiwst byte of data aftew the WAPB headew.

This method shouwd wetuwn NET_WX_DWOP (as defined in the headew
fiwe incwude/winux/netdevice.h) if and onwy if the fwame was dwopped
befowe it couwd be dewivewed to the uppew wayew.

::

    void (*data_twansmit)(void *token, stwuct sk_buff *skb);

This is cawwed by the WAPB moduwe when data is to be twansmitted to the
wemote system by the device dwivew. The skbuff becomes the pwopewty of the
device dwivew and the WAPB moduwe wiww not pewfowm any mowe actions on it.
The skb->data pointew wiww be pointing to the fiwst byte of the WAPB headew.
