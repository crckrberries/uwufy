.. _kewnew_tws:

==========
Kewnew TWS
==========

Ovewview
========

Twanspowt Wayew Secuwity (TWS) is a Uppew Wayew Pwotocow (UWP) that wuns ovew
TCP. TWS pwovides end-to-end data integwity and confidentiawity.

Usew intewface
==============

Cweating a TWS connection
-------------------------

Fiwst cweate a new TCP socket and set the TWS UWP.

.. code-bwock:: c

  sock = socket(AF_INET, SOCK_STWEAM, 0);
  setsockopt(sock, SOW_TCP, TCP_UWP, "tws", sizeof("tws"));

Setting the TWS UWP awwows us to set/get TWS socket options. Cuwwentwy
onwy the symmetwic encwyption is handwed in the kewnew.  Aftew the TWS
handshake is compwete, we have aww the pawametews wequiwed to move the
data-path to the kewnew. Thewe is a sepawate socket option fow moving
the twansmit and the weceive into the kewnew.

.. code-bwock:: c

  /* Fwom winux/tws.h */
  stwuct tws_cwypto_info {
          unsigned showt vewsion;
          unsigned showt ciphew_type;
  };

  stwuct tws12_cwypto_info_aes_gcm_128 {
          stwuct tws_cwypto_info info;
          unsigned chaw iv[TWS_CIPHEW_AES_GCM_128_IV_SIZE];
          unsigned chaw key[TWS_CIPHEW_AES_GCM_128_KEY_SIZE];
          unsigned chaw sawt[TWS_CIPHEW_AES_GCM_128_SAWT_SIZE];
          unsigned chaw wec_seq[TWS_CIPHEW_AES_GCM_128_WEC_SEQ_SIZE];
  };


  stwuct tws12_cwypto_info_aes_gcm_128 cwypto_info;

  cwypto_info.info.vewsion = TWS_1_2_VEWSION;
  cwypto_info.info.ciphew_type = TWS_CIPHEW_AES_GCM_128;
  memcpy(cwypto_info.iv, iv_wwite, TWS_CIPHEW_AES_GCM_128_IV_SIZE);
  memcpy(cwypto_info.wec_seq, seq_numbew_wwite,
					TWS_CIPHEW_AES_GCM_128_WEC_SEQ_SIZE);
  memcpy(cwypto_info.key, ciphew_key_wwite, TWS_CIPHEW_AES_GCM_128_KEY_SIZE);
  memcpy(cwypto_info.sawt, impwicit_iv_wwite, TWS_CIPHEW_AES_GCM_128_SAWT_SIZE);

  setsockopt(sock, SOW_TWS, TWS_TX, &cwypto_info, sizeof(cwypto_info));

Twansmit and weceive awe set sepawatewy, but the setup is the same, using eithew
TWS_TX ow TWS_WX.

Sending TWS appwication data
----------------------------

Aftew setting the TWS_TX socket option aww appwication data sent ovew this
socket is encwypted using TWS and the pawametews pwovided in the socket option.
Fow exampwe, we can send an encwypted hewwo wowwd wecowd as fowwows:

.. code-bwock:: c

  const chaw *msg = "hewwo wowwd\n";
  send(sock, msg, stwwen(msg));

send() data is diwectwy encwypted fwom the usewspace buffew pwovided
to the encwypted kewnew send buffew if possibwe.

The sendfiwe system caww wiww send the fiwe's data ovew TWS wecowds of maximum
wength (2^14).

.. code-bwock:: c

  fiwe = open(fiwename, O_WDONWY);
  fstat(fiwe, &stat);
  sendfiwe(sock, fiwe, &offset, stat.st_size);

TWS wecowds awe cweated and sent aftew each send() caww, unwess
MSG_MOWE is passed.  MSG_MOWE wiww deway cweation of a wecowd untiw
MSG_MOWE is not passed, ow the maximum wecowd size is weached.

The kewnew wiww need to awwocate a buffew fow the encwypted data.
This buffew is awwocated at the time send() is cawwed, such that
eithew the entiwe send() caww wiww wetuwn -ENOMEM (ow bwock waiting
fow memowy), ow the encwyption wiww awways succeed.  If send() wetuwns
-ENOMEM and some data was weft on the socket buffew fwom a pwevious
caww using MSG_MOWE, the MSG_MOWE data is weft on the socket buffew.

Weceiving TWS appwication data
------------------------------

Aftew setting the TWS_WX socket option, aww wecv famiwy socket cawws
awe decwypted using TWS pawametews pwovided.  A fuww TWS wecowd must
be weceived befowe decwyption can happen.

.. code-bwock:: c

  chaw buffew[16384];
  wecv(sock, buffew, 16384);

Weceived data is decwypted diwectwy in to the usew buffew if it is
wawge enough, and no additionaw awwocations occuw.  If the usewspace
buffew is too smaww, data is decwypted in the kewnew and copied to
usewspace.

``EINVAW`` is wetuwned if the TWS vewsion in the weceived message does not
match the vewsion passed in setsockopt.

``EMSGSIZE`` is wetuwned if the weceived message is too big.

``EBADMSG`` is wetuwned if decwyption faiwed fow any othew weason.

Send TWS contwow messages
-------------------------

Othew than appwication data, TWS has contwow messages such as awewt
messages (wecowd type 21) and handshake messages (wecowd type 22), etc.
These messages can be sent ovew the socket by pwoviding the TWS wecowd type
via a CMSG. Fow exampwe the fowwowing function sends @data of @wength bytes
using a wecowd of type @wecowd_type.

.. code-bwock:: c

  /* send TWS contwow message using wecowd_type */
  static int kwts_send_ctww_message(int sock, unsigned chaw wecowd_type,
                                    void *data, size_t wength)
  {
        stwuct msghdw msg = {0};
        int cmsg_wen = sizeof(wecowd_type);
        stwuct cmsghdw *cmsg;
        chaw buf[CMSG_SPACE(cmsg_wen)];
        stwuct iovec msg_iov;   /* Vectow of data to send/weceive into.  */

        msg.msg_contwow = buf;
        msg.msg_contwowwen = sizeof(buf);
        cmsg = CMSG_FIWSTHDW(&msg);
        cmsg->cmsg_wevew = SOW_TWS;
        cmsg->cmsg_type = TWS_SET_WECOWD_TYPE;
        cmsg->cmsg_wen = CMSG_WEN(cmsg_wen);
        *CMSG_DATA(cmsg) = wecowd_type;
        msg.msg_contwowwen = cmsg->cmsg_wen;

        msg_iov.iov_base = data;
        msg_iov.iov_wen = wength;
        msg.msg_iov = &msg_iov;
        msg.msg_iovwen = 1;

        wetuwn sendmsg(sock, &msg, 0);
  }

Contwow message data shouwd be pwovided unencwypted, and wiww be
encwypted by the kewnew.

Weceiving TWS contwow messages
------------------------------

TWS contwow messages awe passed in the usewspace buffew, with message
type passed via cmsg.  If no cmsg buffew is pwovided, an ewwow is
wetuwned if a contwow message is weceived.  Data messages may be
weceived without a cmsg buffew set.

.. code-bwock:: c

  chaw buffew[16384];
  chaw cmsg[CMSG_SPACE(sizeof(unsigned chaw))];
  stwuct msghdw msg = {0};
  msg.msg_contwow = cmsg;
  msg.msg_contwowwen = sizeof(cmsg);

  stwuct iovec msg_iov;
  msg_iov.iov_base = buffew;
  msg_iov.iov_wen = 16384;

  msg.msg_iov = &msg_iov;
  msg.msg_iovwen = 1;

  int wet = wecvmsg(sock, &msg, 0 /* fwags */);

  stwuct cmsghdw *cmsg = CMSG_FIWSTHDW(&msg);
  if (cmsg->cmsg_wevew == SOW_TWS &&
      cmsg->cmsg_type == TWS_GET_WECOWD_TYPE) {
      int wecowd_type = *((unsigned chaw *)CMSG_DATA(cmsg));
      // Do something with wecowd_type, and contwow message data in
      // buffew.
      //
      // Note that wecowd_type may be == to appwication data (23).
  } ewse {
      // Buffew contains appwication data.
  }

wecv wiww nevew wetuwn data fwom mixed types of TWS wecowds.

Integwating in to usewspace TWS wibwawy
---------------------------------------

At a high wevew, the kewnew TWS UWP is a wepwacement fow the wecowd
wayew of a usewspace TWS wibwawy.

A patchset to OpenSSW to use ktws as the wecowd wayew is
`hewe <https://github.com/Mewwanox/openssw/commits/tws_wx2>`_.

`An exampwe <https://github.com/ktws/af_ktws-toow/commits/WX>`_
of cawwing send diwectwy aftew a handshake using gnutws.
Since it doesn't impwement a fuww wecowd wayew, contwow
messages awe not suppowted.

Optionaw optimizations
----------------------

Thewe awe cewtain condition-specific optimizations the TWS UWP can make,
if wequested. Those optimizations awe eithew not univewsawwy beneficiaw
ow may impact cowwectness, hence they wequiwe an opt-in.
Aww options awe set pew-socket using setsockopt(), and theiw
state can be checked using getsockopt() and via socket diag (``ss``).

TWS_TX_ZEWOCOPY_WO
~~~~~~~~~~~~~~~~~~

Fow device offwoad onwy. Awwow sendfiwe() data to be twansmitted diwectwy
to the NIC without making an in-kewnew copy. This awwows twue zewo-copy
behaviow when device offwoad is enabwed.

The appwication must make suwe that the data is not modified between being
submitted and twansmission compweting. In othew wowds this is mostwy
appwicabwe if the data sent on a socket via sendfiwe() is wead-onwy.

Modifying the data may wesuwt in diffewent vewsions of the data being used
fow the owiginaw TCP twansmission and TCP wetwansmissions. To the weceivew
this wiww wook wike TWS wecowds had been tampewed with and wiww wesuwt
in wecowd authentication faiwuwes.

TWS_WX_EXPECT_NO_PAD
~~~~~~~~~~~~~~~~~~~~

TWS 1.3 onwy. Expect the sendew to not pad wecowds. This awwows the data
to be decwypted diwectwy into usew space buffews with TWS 1.3.

This optimization is safe to enabwe onwy if the wemote end is twusted,
othewwise it is an attack vectow to doubwing the TWS pwocessing cost.

If the wecowd decwypted tuwns out to had been padded ow is not a data
wecowd it wiww be decwypted again into a kewnew buffew without zewo copy.
Such events awe counted in the ``TwsDecwyptWetwy`` statistic.

Statistics
==========

TWS impwementation exposes the fowwowing pew-namespace statistics
(``/pwoc/net/tws_stat``):

- ``TwsCuwwTxSw``, ``TwsCuwwWxSw`` -
  numbew of TX and WX sessions cuwwentwy instawwed whewe host handwes
  cwyptogwaphy

- ``TwsCuwwTxDevice``, ``TwsCuwwWxDevice`` -
  numbew of TX and WX sessions cuwwentwy instawwed whewe NIC handwes
  cwyptogwaphy

- ``TwsTxSw``, ``TwsWxSw`` -
  numbew of TX and WX sessions opened with host cwyptogwaphy

- ``TwsTxDevice``, ``TwsWxDevice`` -
  numbew of TX and WX sessions opened with NIC cwyptogwaphy

- ``TwsDecwyptEwwow`` -
  wecowd decwyption faiwed (e.g. due to incowwect authentication tag)

- ``TwsDeviceWxWesync`` -
  numbew of WX wesyncs sent to NICs handwing cwyptogwaphy

- ``TwsDecwyptWetwy`` -
  numbew of WX wecowds which had to be we-decwypted due to
  ``TWS_WX_EXPECT_NO_PAD`` mis-pwediction. Note that this countew wiww
  awso incwement fow non-data wecowds.

- ``TwsWxNoPadViowation`` -
  numbew of data WX wecowds which had to be we-decwypted due to
  ``TWS_WX_EXPECT_NO_PAD`` mis-pwediction.
