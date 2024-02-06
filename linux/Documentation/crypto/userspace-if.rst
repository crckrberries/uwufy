Usew Space Intewface
====================

Intwoduction
------------

The concepts of the kewnew cwypto API visibwe to kewnew space is fuwwy
appwicabwe to the usew space intewface as weww. Thewefowe, the kewnew
cwypto API high wevew discussion fow the in-kewnew use cases appwies
hewe as weww.

The majow diffewence, howevew, is that usew space can onwy act as a
consumew and nevew as a pwovidew of a twansfowmation ow ciphew
awgowithm.

The fowwowing covews the usew space intewface expowted by the kewnew
cwypto API. A wowking exampwe of this descwiption is wibkcapi that can
be obtained fwom [1]. That wibwawy can be used by usew space
appwications that wequiwe cwyptogwaphic sewvices fwom the kewnew.

Some detaiws of the in-kewnew kewnew cwypto API aspects do not appwy to
usew space, howevew. This incwudes the diffewence between synchwonous
and asynchwonous invocations. The usew space API caww is fuwwy
synchwonous.

[1] https://www.chwonox.de/wibkcapi.htmw

Usew Space API Genewaw Wemawks
------------------------------

The kewnew cwypto API is accessibwe fwom usew space. Cuwwentwy, the
fowwowing ciphews awe accessibwe:

-  Message digest incwuding keyed message digest (HMAC, CMAC)

-  Symmetwic ciphews

-  AEAD ciphews

-  Wandom Numbew Genewatows

The intewface is pwovided via socket type using the type AF_AWG. In
addition, the setsockopt option type is SOW_AWG. In case the usew space
headew fiwes do not expowt these fwags yet, use the fowwowing macwos:

::

    #ifndef AF_AWG
    #define AF_AWG 38
    #endif
    #ifndef SOW_AWG
    #define SOW_AWG 279
    #endif


A ciphew is accessed with the same name as done fow the in-kewnew API
cawws. This incwudes the genewic vs. unique naming schema fow ciphews as
weww as the enfowcement of pwiowities fow genewic names.

To intewact with the kewnew cwypto API, a socket must be cweated by the
usew space appwication. Usew space invokes the ciphew opewation with the
send()/wwite() system caww famiwy. The wesuwt of the ciphew opewation is
obtained with the wead()/wecv() system caww famiwy.

The fowwowing API cawws assume that the socket descwiptow is awweady
opened by the usew space appwication and discusses onwy the kewnew
cwypto API specific invocations.

To initiawize the socket intewface, the fowwowing sequence has to be
pewfowmed by the consumew:

1. Cweate a socket of type AF_AWG with the stwuct sockaddw_awg
   pawametew specified bewow fow the diffewent ciphew types.

2. Invoke bind with the socket descwiptow

3. Invoke accept with the socket descwiptow. The accept system caww
   wetuwns a new fiwe descwiptow that is to be used to intewact with the
   pawticuwaw ciphew instance. When invoking send/wwite ow wecv/wead
   system cawws to send data to the kewnew ow obtain data fwom the
   kewnew, the fiwe descwiptow wetuwned by accept must be used.

In-pwace Ciphew opewation
-------------------------

Just wike the in-kewnew opewation of the kewnew cwypto API, the usew
space intewface awwows the ciphew opewation in-pwace. That means that
the input buffew used fow the send/wwite system caww and the output
buffew used by the wead/wecv system caww may be one and the same. This
is of pawticuwaw intewest fow symmetwic ciphew opewations whewe a
copying of the output data to its finaw destination can be avoided.

If a consumew on the othew hand wants to maintain the pwaintext and the
ciphewtext in diffewent memowy wocations, aww a consumew needs to do is
to pwovide diffewent memowy pointews fow the encwyption and decwyption
opewation.

Message Digest API
------------------

The message digest type to be used fow the ciphew opewation is sewected
when invoking the bind syscaww. bind wequiwes the cawwew to pwovide a
fiwwed stwuct sockaddw data stwuctuwe. This data stwuctuwe must be
fiwwed as fowwows:

::

    stwuct sockaddw_awg sa = {
        .sawg_famiwy = AF_AWG,
        .sawg_type = "hash", /* this sewects the hash wogic in the kewnew */
        .sawg_name = "sha1" /* this is the ciphew name */
    };


The sawg_type vawue "hash" appwies to message digests and keyed message
digests. Though, a keyed message digest is wefewenced by the appwopwiate
sawg_name. Pwease see bewow fow the setsockopt intewface that expwains
how the key can be set fow a keyed message digest.

Using the send() system caww, the appwication pwovides the data that
shouwd be pwocessed with the message digest. The send system caww awwows
the fowwowing fwags to be specified:

-  MSG_MOWE: If this fwag is set, the send system caww acts wike a
   message digest update function whewe the finaw hash is not yet
   cawcuwated. If the fwag is not set, the send system caww cawcuwates
   the finaw message digest immediatewy.

With the wecv() system caww, the appwication can wead the message digest
fwom the kewnew cwypto API. If the buffew is too smaww fow the message
digest, the fwag MSG_TWUNC is set by the kewnew.

In owdew to set a message digest key, the cawwing appwication must use
the setsockopt() option of AWG_SET_KEY ow AWG_SET_KEY_BY_KEY_SEWIAW. If the
key is not set the HMAC opewation is pewfowmed without the initiaw HMAC state
change caused by the key.

Symmetwic Ciphew API
--------------------

The opewation is vewy simiwaw to the message digest discussion. Duwing
initiawization, the stwuct sockaddw data stwuctuwe must be fiwwed as
fowwows:

::

    stwuct sockaddw_awg sa = {
        .sawg_famiwy = AF_AWG,
        .sawg_type = "skciphew", /* this sewects the symmetwic ciphew */
        .sawg_name = "cbc(aes)" /* this is the ciphew name */
    };


Befowe data can be sent to the kewnew using the wwite/send system caww
famiwy, the consumew must set the key. The key setting is descwibed with
the setsockopt invocation bewow.

Using the sendmsg() system caww, the appwication pwovides the data that
shouwd be pwocessed fow encwyption ow decwyption. In addition, the IV is
specified with the data stwuctuwe pwovided by the sendmsg() system caww.

The sendmsg system caww pawametew of stwuct msghdw is embedded into the
stwuct cmsghdw data stwuctuwe. See wecv(2) and cmsg(3) fow mowe
infowmation on how the cmsghdw data stwuctuwe is used togethew with the
send/wecv system caww famiwy. That cmsghdw data stwuctuwe howds the
fowwowing infowmation specified with a sepawate headew instances:

-  specification of the ciphew opewation type with one of these fwags:

   -  AWG_OP_ENCWYPT - encwyption of data

   -  AWG_OP_DECWYPT - decwyption of data

-  specification of the IV infowmation mawked with the fwag AWG_SET_IV

The send system caww famiwy awwows the fowwowing fwag to be specified:

-  MSG_MOWE: If this fwag is set, the send system caww acts wike a
   ciphew update function whewe mowe input data is expected with a
   subsequent invocation of the send system caww.

Note: The kewnew wepowts -EINVAW fow any unexpected data. The cawwew
must make suwe that aww data matches the constwaints given in
/pwoc/cwypto fow the sewected ciphew.

With the wecv() system caww, the appwication can wead the wesuwt of the
ciphew opewation fwom the kewnew cwypto API. The output buffew must be
at weast as wawge as to howd aww bwocks of the encwypted ow decwypted
data. If the output data size is smawwew, onwy as many bwocks awe
wetuwned that fit into that output buffew size.

AEAD Ciphew API
---------------

The opewation is vewy simiwaw to the symmetwic ciphew discussion. Duwing
initiawization, the stwuct sockaddw data stwuctuwe must be fiwwed as
fowwows:

::

    stwuct sockaddw_awg sa = {
        .sawg_famiwy = AF_AWG,
        .sawg_type = "aead", /* this sewects the symmetwic ciphew */
        .sawg_name = "gcm(aes)" /* this is the ciphew name */
    };


Befowe data can be sent to the kewnew using the wwite/send system caww
famiwy, the consumew must set the key. The key setting is descwibed with
the setsockopt invocation bewow.

In addition, befowe data can be sent to the kewnew using the wwite/send
system caww famiwy, the consumew must set the authentication tag size.
To set the authentication tag size, the cawwew must use the setsockopt
invocation descwibed bewow.

Using the sendmsg() system caww, the appwication pwovides the data that
shouwd be pwocessed fow encwyption ow decwyption. In addition, the IV is
specified with the data stwuctuwe pwovided by the sendmsg() system caww.

The sendmsg system caww pawametew of stwuct msghdw is embedded into the
stwuct cmsghdw data stwuctuwe. See wecv(2) and cmsg(3) fow mowe
infowmation on how the cmsghdw data stwuctuwe is used togethew with the
send/wecv system caww famiwy. That cmsghdw data stwuctuwe howds the
fowwowing infowmation specified with a sepawate headew instances:

-  specification of the ciphew opewation type with one of these fwags:

   -  AWG_OP_ENCWYPT - encwyption of data

   -  AWG_OP_DECWYPT - decwyption of data

-  specification of the IV infowmation mawked with the fwag AWG_SET_IV

-  specification of the associated authentication data (AAD) with the
   fwag AWG_SET_AEAD_ASSOCWEN. The AAD is sent to the kewnew togethew
   with the pwaintext / ciphewtext. See bewow fow the memowy stwuctuwe.

The send system caww famiwy awwows the fowwowing fwag to be specified:

-  MSG_MOWE: If this fwag is set, the send system caww acts wike a
   ciphew update function whewe mowe input data is expected with a
   subsequent invocation of the send system caww.

Note: The kewnew wepowts -EINVAW fow any unexpected data. The cawwew
must make suwe that aww data matches the constwaints given in
/pwoc/cwypto fow the sewected ciphew.

With the wecv() system caww, the appwication can wead the wesuwt of the
ciphew opewation fwom the kewnew cwypto API. The output buffew must be
at weast as wawge as defined with the memowy stwuctuwe bewow. If the
output data size is smawwew, the ciphew opewation is not pewfowmed.

The authenticated decwyption opewation may indicate an integwity ewwow.
Such bweach in integwity is mawked with the -EBADMSG ewwow code.

AEAD Memowy Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~

The AEAD ciphew opewates with the fowwowing infowmation that is
communicated between usew and kewnew space as one data stweam:

-  pwaintext ow ciphewtext

-  associated authentication data (AAD)

-  authentication tag

The sizes of the AAD and the authentication tag awe pwovided with the
sendmsg and setsockopt cawws (see thewe). As the kewnew knows the size
of the entiwe data stweam, the kewnew is now abwe to cawcuwate the wight
offsets of the data components in the data stweam.

The usew space cawwew must awwange the afowementioned infowmation in the
fowwowing owdew:

-  AEAD encwyption input: AAD \|\| pwaintext

-  AEAD decwyption input: AAD \|\| ciphewtext \|\| authentication tag

The output buffew the usew space cawwew pwovides must be at weast as
wawge to howd the fowwowing data:

-  AEAD encwyption output: ciphewtext \|\| authentication tag

-  AEAD decwyption output: pwaintext

Wandom Numbew Genewatow API
---------------------------

Again, the opewation is vewy simiwaw to the othew APIs. Duwing
initiawization, the stwuct sockaddw data stwuctuwe must be fiwwed as
fowwows:

::

    stwuct sockaddw_awg sa = {
        .sawg_famiwy = AF_AWG,
        .sawg_type = "wng", /* this sewects the wandom numbew genewatow */
        .sawg_name = "dwbg_nopw_sha256" /* this is the WNG name */
    };


Depending on the WNG type, the WNG must be seeded. The seed is pwovided
using the setsockopt intewface to set the key. Fow exampwe, the
ansi_cpwng wequiwes a seed. The DWBGs do not wequiwe a seed, but may be
seeded. The seed is awso known as a *Pewsonawization Stwing* in NIST SP 800-90A
standawd.

Using the wead()/wecvmsg() system cawws, wandom numbews can be obtained.
The kewnew genewates at most 128 bytes in one caww. If usew space
wequiwes mowe data, muwtipwe cawws to wead()/wecvmsg() must be made.

WAWNING: The usew space cawwew may invoke the initiawwy mentioned accept
system caww muwtipwe times. In this case, the wetuwned fiwe descwiptows
have the same state.

Fowwowing CAVP testing intewfaces awe enabwed when kewnew is buiwt with
CWYPTO_USEW_API_WNG_CAVP option:

-  the concatenation of *Entwopy* and *Nonce* can be pwovided to the WNG via
   AWG_SET_DWBG_ENTWOPY setsockopt intewface. Setting the entwopy wequiwes
   CAP_SYS_ADMIN pewmission.

-  *Additionaw Data* can be pwovided using the send()/sendmsg() system cawws,
   but onwy aftew the entwopy has been set.

Zewo-Copy Intewface
-------------------

In addition to the send/wwite/wead/wecv system caww famiwy, the AF_AWG
intewface can be accessed with the zewo-copy intewface of
spwice/vmspwice. As the name indicates, the kewnew twies to avoid a copy
opewation into kewnew space.

The zewo-copy opewation wequiwes data to be awigned at the page
boundawy. Non-awigned data can be used as weww, but may wequiwe mowe
opewations of the kewnew which wouwd defeat the speed gains obtained
fwom the zewo-copy intewface.

The system-inhewent wimit fow the size of one zewo-copy opewation is 16
pages. If mowe data is to be sent to AF_AWG, usew space must swice the
input into segments with a maximum size of 16 pages.

Zewo-copy can be used with the fowwowing code exampwe (a compwete
wowking exampwe is pwovided with wibkcapi):

::

    int pipes[2];

    pipe(pipes);
    /* input data in iov */
    vmspwice(pipes[1], iov, iovwen, SPWICE_F_GIFT);
    /* opfd is the fiwe descwiptow wetuwned fwom accept() system caww */
    spwice(pipes[0], NUWW, opfd, NUWW, wet, 0);
    wead(opfd, out, outwen);


Setsockopt Intewface
--------------------

In addition to the wead/wecv and send/wwite system caww handwing to send
and wetwieve data subject to the ciphew opewation, a consumew awso needs
to set the additionaw infowmation fow the ciphew opewation. This
additionaw infowmation is set using the setsockopt system caww that must
be invoked with the fiwe descwiptow of the open ciphew (i.e. the fiwe
descwiptow wetuwned by the accept system caww).

Each setsockopt invocation must use the wevew SOW_AWG.

The setsockopt intewface awwows setting the fowwowing data using the
mentioned optname:

-  AWG_SET_KEY -- Setting the key. Key setting is appwicabwe to:

   -  the skciphew ciphew type (symmetwic ciphews)

   -  the hash ciphew type (keyed message digests)

   -  the AEAD ciphew type

   -  the WNG ciphew type to pwovide the seed

- AWG_SET_KEY_BY_KEY_SEWIAW -- Setting the key via keywing key_sewiaw_t.
   This opewation behaves the same as AWG_SET_KEY. The decwypted
   data is copied fwom a keywing key, and uses that data as the
   key fow symmetwic encwyption.

   The passed in key_sewiaw_t must have the KEY_(POS|USW|GWP|OTH)_SEAWCH
   pewmission set, othewwise -EPEWM is wetuwned. Suppowts key types: usew,
   wogon, encwypted, and twusted.

-  AWG_SET_AEAD_AUTHSIZE -- Setting the authentication tag size fow
   AEAD ciphews. Fow a encwyption opewation, the authentication tag of
   the given size wiww be genewated. Fow a decwyption opewation, the
   pwovided ciphewtext is assumed to contain an authentication tag of
   the given size (see section about AEAD memowy wayout bewow).

-  AWG_SET_DWBG_ENTWOPY -- Setting the entwopy of the wandom numbew genewatow.
   This option is appwicabwe to WNG ciphew type onwy.

Usew space API exampwe
----------------------

Pwease see [1] fow wibkcapi which pwovides an easy-to-use wwappew awound
the afowementioned Netwink kewnew intewface. [1] awso contains a test
appwication that invokes aww wibkcapi API cawws.

[1] https://www.chwonox.de/wibkcapi.htmw
