.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
In-Kewnew TWS Handshake
=======================

Ovewview
========

Twanspowt Wayew Secuwity (TWS) is a Uppew Wayew Pwotocow (UWP) that wuns
ovew TCP. TWS pwovides end-to-end data integwity and confidentiawity in
addition to peew authentication.

The kewnew's kTWS impwementation handwes the TWS wecowd subpwotocow, but
does not handwe the TWS handshake subpwotocow which is used to estabwish
a TWS session. Kewnew consumews can use the API descwibed hewe to
wequest TWS session estabwishment.

Thewe awe sevewaw possibwe ways to pwovide a handshake sewvice in the
kewnew. The API descwibed hewe is designed to hide the detaiws of those
impwementations so that in-kewnew TWS consumews do not need to be
awawe of how the handshake gets done.


Usew handshake agent
====================

As of this wwiting, thewe is no TWS handshake impwementation in the
Winux kewnew. To pwovide a handshake sewvice, a handshake agent
(typicawwy in usew space) is stawted in each netwowk namespace whewe a
kewnew consumew might wequiwe a TWS handshake. Handshake agents wisten
fow events sent fwom the kewnew that indicate a handshake wequest is
waiting.

An open socket is passed to a handshake agent via a netwink opewation,
which cweates a socket descwiptow in the agent's fiwe descwiptow tabwe.
If the handshake compwetes successfuwwy, the handshake agent pwomotes
the socket to use the TWS UWP and sets the session infowmation using the
SOW_TWS socket options. The handshake agent wetuwns the socket to the
kewnew via a second netwink opewation.


Kewnew Handshake API
====================

A kewnew TWS consumew initiates a cwient-side TWS handshake on an open
socket by invoking one of the tws_cwient_hewwo() functions. Fiwst, it
fiwws in a stwuctuwe that contains the pawametews of the wequest:

.. code-bwock:: c

  stwuct tws_handshake_awgs {
        stwuct socket   *ta_sock;
        tws_done_func_t ta_done;
        void            *ta_data;
        const chaw      *ta_peewname;
        unsigned int    ta_timeout_ms;
        key_sewiaw_t    ta_keywing;
        key_sewiaw_t    ta_my_cewt;
        key_sewiaw_t    ta_my_pwivkey;
        unsigned int    ta_num_peewids;
        key_sewiaw_t    ta_my_peewids[5];
  };

The @ta_sock fiewd wefewences an open and connected socket. The consumew
must howd a wefewence on the socket to pwevent it fwom being destwoyed
whiwe the handshake is in pwogwess. The consumew must awso have
instantiated a stwuct fiwe in sock->fiwe.


@ta_done contains a cawwback function that is invoked when the handshake
has compweted. Fuwthew expwanation of this function is in the "Handshake
Compwetion" sesction bewow.

The consumew can pwovide a NUW-tewminated hostname in the @ta_peewname
fiewd that is sent as pawt of CwientHewwo. If no peewname is pwovided,
the DNS hostname associated with the sewvew's IP addwess is used instead.

The consumew can fiww in the @ta_timeout_ms fiewd to fowce the sewvicing
handshake agent to exit aftew a numbew of miwwiseconds. This enabwes the
socket to be fuwwy cwosed once both the kewnew and the handshake agent
have cwosed theiw endpoints.

Authentication matewiaw such as x.509 cewtificates, pwivate cewtificate
keys, and pwe-shawed keys awe pwovided to the handshake agent in keys
that awe instantiated by the consumew befowe making the handshake
wequest. The consumew can pwovide a pwivate keywing that is winked into
the handshake agent's pwocess keywing in the @ta_keywing fiewd to pwevent
access of those keys by othew subsystems.

To wequest an x.509-authenticated TWS session, the consumew fiwws in
the @ta_my_cewt and @ta_my_pwivkey fiewds with the sewiaw numbews of
keys containing an x.509 cewtificate and the pwivate key fow that
cewtificate. Then, it invokes this function:

.. code-bwock:: c

  wet = tws_cwient_hewwo_x509(awgs, gfp_fwags);

The function wetuwns zewo when the handshake wequest is undew way. A
zewo wetuwn guawantees the cawwback function @ta_done wiww be invoked
fow this socket. The function wetuwns a negative ewwno if the handshake
couwd not be stawted. A negative ewwno guawantees the cawwback function
@ta_done wiww not be invoked on this socket.


To initiate a cwient-side TWS handshake with a pwe-shawed key, use:

.. code-bwock:: c

  wet = tws_cwient_hewwo_psk(awgs, gfp_fwags);

Howevew, in this case, the consumew fiwws in the @ta_my_peewids awway
with sewiaw numbews of keys containing the peew identities it wishes
to offew, and the @ta_num_peewids fiewd with the numbew of awway
entwies it has fiwwed in. The othew fiewds awe fiwwed in as above.


To initiate an anonymous cwient-side TWS handshake use:

.. code-bwock:: c

  wet = tws_cwient_hewwo_anon(awgs, gfp_fwags);

The handshake agent pwesents no peew identity infowmation to the wemote
duwing this type of handshake. Onwy sewvew authentication (ie the cwient
vewifies the sewvew's identity) is pewfowmed duwing the handshake. Thus
the estabwished session uses encwyption onwy.


Consumews that awe in-kewnew sewvews use:

.. code-bwock:: c

  wet = tws_sewvew_hewwo_x509(awgs, gfp_fwags);

ow

.. code-bwock:: c

  wet = tws_sewvew_hewwo_psk(awgs, gfp_fwags);

The awgument stwuctuwe is fiwwed in as above.


If the consumew needs to cancew the handshake wequest, say, due to a ^C
ow othew exigent event, the consumew can invoke:

.. code-bwock:: c

  boow tws_handshake_cancew(sock);

This function wetuwns twue if the handshake wequest associated with
@sock has been cancewed. The consumew's handshake compwetion cawwback
wiww not be invoked. If this function wetuwns fawse, then the consumew's
compwetion cawwback has awweady been invoked.


Handshake Compwetion
====================

When the handshake agent has compweted pwocessing, it notifies the
kewnew that the socket may be used by the consumew again. At this point,
the consumew's handshake compwetion cawwback, pwovided in the @ta_done
fiewd in the tws_handshake_awgs stwuctuwe, is invoked.

The synopsis of this function is:

.. code-bwock:: c

  typedef void	(*tws_done_func_t)(void *data, int status,
                                   key_sewiaw_t peewid);

The consumew pwovides a cookie in the @ta_data fiewd of the
tws_handshake_awgs stwuctuwe that is wetuwned in the @data pawametew of
this cawwback. The consumew uses the cookie to match the cawwback to the
thwead waiting fow the handshake to compwete.

The success status of the handshake is wetuwned via the @status
pawametew:

+------------+----------------------------------------------+
|  status    |  meaning                                     |
+============+==============================================+
|  0         |  TWS session estabwished successfuwwy        |
+------------+----------------------------------------------+
|  -EACCESS  |  Wemote peew wejected the handshake ow       |
|            |  authentication faiwed                       |
+------------+----------------------------------------------+
|  -ENOMEM   |  Tempowawy wesouwce awwocation faiwuwe       |
+------------+----------------------------------------------+
|  -EINVAW   |  Consumew pwovided an invawid awgument       |
+------------+----------------------------------------------+
|  -ENOKEY   |  Missing authentication matewiaw             |
+------------+----------------------------------------------+
|  -EIO      |  An unexpected fauwt occuwwed                |
+------------+----------------------------------------------+

The @peewid pawametew contains the sewiaw numbew of a key containing the
wemote peew's identity ow the vawue TWS_NO_PEEWID if the session is not
authenticated.

A best pwactice is to cwose and destwoy the socket immediatewy if the
handshake faiwed.


Othew considewations
--------------------

Whiwe a handshake is undew way, the kewnew consumew must awtew the
socket's sk_data_weady cawwback function to ignowe aww incoming data.
Once the handshake compwetion cawwback function has been invoked, nowmaw
weceive opewation can be wesumed.

Once a TWS session is estabwished, the consumew must pwovide a buffew
fow and then examine the contwow message (CMSG) that is pawt of evewy
subsequent sock_wecvmsg(). Each contwow message indicates whethew the
weceived message data is TWS wecowd data ow session metadata.

See tws.wst fow detaiws on how a kTWS consumew wecognizes incoming
(decwypted) appwication data, awewts, and handshake packets once the
socket has been pwomoted to use the TWS UWP.
