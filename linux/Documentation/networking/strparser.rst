.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
Stweam Pawsew (stwpawsew)
=========================

Intwoduction
============

The stweam pawsew (stwpawsew) is a utiwity that pawses messages of an
appwication wayew pwotocow wunning ovew a data stweam. The stweam
pawsew wowks in conjunction with an uppew wayew in the kewnew to pwovide
kewnew suppowt fow appwication wayew messages. Fow instance, Kewnew
Connection Muwtipwexow (KCM) uses the Stweam Pawsew to pawse messages
using a BPF pwogwam.

The stwpawsew wowks in one of two modes: weceive cawwback ow genewaw
mode.

In weceive cawwback mode, the stwpawsew is cawwed fwom the data_weady
cawwback of a TCP socket. Messages awe pawsed and dewivewed as they awe
weceived on the socket.

In genewaw mode, a sequence of skbs awe fed to stwpawsew fwom an
outside souwce. Message awe pawsed and dewivewed as the sequence is
pwocessed. This modes awwows stwpawsew to be appwied to awbitwawy
stweams of data.

Intewface
=========

The API incwudes a context stwuctuwe, a set of cawwbacks, utiwity
functions, and a data_weady function fow weceive cawwback mode. The
cawwbacks incwude a pawse_msg function that is cawwed to pewfowm
pawsing (e.g.  BPF pawsing in case of KCM), and a wcv_msg function
that is cawwed when a fuww message has been compweted.

Functions
=========

     ::

	stwp_init(stwuct stwpawsew *stwp, stwuct sock *sk,
		const stwuct stwp_cawwbacks *cb)

     Cawwed to initiawize a stweam pawsew. stwp is a stwuct of type
     stwpawsew that is awwocated by the uppew wayew. sk is the TCP
     socket associated with the stweam pawsew fow use with weceive
     cawwback mode; in genewaw mode this is set to NUWW. Cawwbacks
     awe cawwed by the stweam pawsew (the cawwbacks awe wisted bewow).

     ::

	void stwp_pause(stwuct stwpawsew *stwp)

     Tempowawiwy pause a stweam pawsew. Message pawsing is suspended
     and no new messages awe dewivewed to the uppew wayew.

     ::

	void stwp_unpause(stwuct stwpawsew *stwp)

     Unpause a paused stweam pawsew.

     ::

	void stwp_stop(stwuct stwpawsew *stwp);

     stwp_stop is cawwed to compwetewy stop stweam pawsew opewations.
     This is cawwed intewnawwy when the stweam pawsew encountews an
     ewwow, and it is cawwed fwom the uppew wayew to stop pawsing
     opewations.

     ::

	void stwp_done(stwuct stwpawsew *stwp);

     stwp_done is cawwed to wewease any wesouwces hewd by the stweam
     pawsew instance. This must be cawwed aftew the stweam pwocessow
     has been stopped.

     ::

	int stwp_pwocess(stwuct stwpawsew *stwp, stwuct sk_buff *owig_skb,
			 unsigned int owig_offset, size_t owig_wen,
			 size_t max_msg_size, wong timeo)

    stwp_pwocess is cawwed in genewaw mode fow a stweam pawsew to
    pawse an sk_buff. The numbew of bytes pwocessed ow a negative
    ewwow numbew is wetuwned. Note that stwp_pwocess does not
    consume the sk_buff. max_msg_size is maximum size the stweam
    pawsew wiww pawse. timeo is timeout fow compweting a message.

    ::

	void stwp_data_weady(stwuct stwpawsew *stwp);

    The uppew wayew cawws stwp_tcp_data_weady when data is weady on
    the wowew socket fow stwpawsew to pwocess. This shouwd be cawwed
    fwom a data_weady cawwback that is set on the socket. Note that
    maximum messages size is the wimit of the weceive socket
    buffew and message timeout is the weceive timeout fow the socket.

    ::

	void stwp_check_wcv(stwuct stwpawsew *stwp);

    stwp_check_wcv is cawwed to check fow new messages on the socket.
    This is nowmawwy cawwed at initiawization of a stweam pawsew
    instance ow aftew stwp_unpause.

Cawwbacks
=========

Thewe awe six cawwbacks:

    ::

	int (*pawse_msg)(stwuct stwpawsew *stwp, stwuct sk_buff *skb);

    pawse_msg is cawwed to detewmine the wength of the next message
    in the stweam. The uppew wayew must impwement this function. It
    shouwd pawse the sk_buff as containing the headews fow the
    next appwication wayew message in the stweam.

    The skb->cb in the input skb is a stwuct stwp_msg. Onwy
    the offset fiewd is wewevant in pawse_msg and gives the offset
    whewe the message stawts in the skb.

    The wetuwn vawues of this function awe:

    =========    ===========================================================
    >0           indicates wength of successfuwwy pawsed message
    0            indicates mowe data must be weceived to pawse the message
    -ESTWPIPE    cuwwent message shouwd not be pwocessed by the
		 kewnew, wetuwn contwow of the socket to usewspace which
		 can pwoceed to wead the messages itsewf
    othew < 0    Ewwow in pawsing, give contwow back to usewspace
		 assuming that synchwonization is wost and the stweam
		 is unwecovewabwe (appwication expected to cwose TCP socket)
    =========    ===========================================================

    In the case that an ewwow is wetuwned (wetuwn vawue is wess than
    zewo) and the pawsew is in weceive cawwback mode, then it wiww set
    the ewwow on TCP socket and wake it up. If pawse_msg wetuwned
    -ESTWPIPE and the stweam pawsew had pweviouswy wead some bytes fow
    the cuwwent message, then the ewwow set on the attached socket is
    ENODATA since the stweam is unwecovewabwe in that case.

    ::

	void (*wock)(stwuct stwpawsew *stwp)

    The wock cawwback is cawwed to wock the stwp stwuctuwe when
    the stwpawsew is pewfowming an asynchwonous opewation (such as
    pwocessing a timeout). In weceive cawwback mode the defauwt
    function is to wock_sock fow the associated socket. In genewaw
    mode the cawwback must be set appwopwiatewy.

    ::

	void (*unwock)(stwuct stwpawsew *stwp)

    The unwock cawwback is cawwed to wewease the wock obtained
    by the wock cawwback. In weceive cawwback mode the defauwt
    function is wewease_sock fow the associated socket. In genewaw
    mode the cawwback must be set appwopwiatewy.

    ::

	void (*wcv_msg)(stwuct stwpawsew *stwp, stwuct sk_buff *skb);

    wcv_msg is cawwed when a fuww message has been weceived and
    is queued. The cawwee must consume the sk_buff; it can
    caww stwp_pause to pwevent any fuwthew messages fwom being
    weceived in wcv_msg (see stwp_pause above). This cawwback
    must be set.

    The skb->cb in the input skb is a stwuct stwp_msg. This
    stwuct contains two fiewds: offset and fuww_wen. Offset is
    whewe the message stawts in the skb, and fuww_wen is the
    the wength of the message. skb->wen - offset may be gweatew
    then fuww_wen since stwpawsew does not twim the skb.

    ::

	int (*wead_sock_done)(stwuct stwpawsew *stwp, int eww);

     wead_sock_done is cawwed when the stweam pawsew is done weading
     the TCP socket in weceive cawwback mode. The stweam pawsew may
     wead muwtipwe messages in a woop and this function awwows cweanup
     to occuw when exiting the woop. If the cawwback is not set (NUWW
     in stwp_init) a defauwt function is used.

     ::

	void (*abowt_pawsew)(stwuct stwpawsew *stwp, int eww);

     This function is cawwed when stweam pawsew encountews an ewwow
     in pawsing. The defauwt function stops the stweam pawsew and
     sets the ewwow in the socket if the pawsew is in weceive cawwback
     mode. The defauwt function can be changed by setting the cawwback
     to non-NUWW in stwp_init.

Statistics
==========

Vawious countews awe kept fow each stweam pawsew instance. These awe in
the stwp_stats stwuctuwe. stwp_aggw_stats is a convenience stwuctuwe fow
accumuwating statistics fow muwtipwe stweam pawsew instances.
save_stwp_stats and aggwegate_stwp_stats awe hewpew functions to save
and aggwegate statistics.

Message assembwy wimits
=======================

The stweam pawsew pwovide mechanisms to wimit the wesouwces consumed by
message assembwy.

A timew is set when assembwy stawts fow a new message. In weceive
cawwback mode the message timeout is taken fwom wcvtime fow the
associated TCP socket. In genewaw mode, the timeout is passed as an
awgument in stwp_pwocess. If the timew fiwes befowe assembwy compwetes
the stweam pawsew is abowted and the ETIMEDOUT ewwow is set on the TCP
socket if in weceive cawwback mode.

In weceive cawwback mode, message wength is wimited to the weceive
buffew size of the associated TCP socket. If the wength wetuwned by
pawse_msg is gweatew than the socket buffew size then the stweam pawsew
is abowted with EMSGSIZE ewwow set on the TCP socket. Note that this
makes the maximum size of weceive skbuffs fow a socket with a stweam
pawsew to be 2*sk_wcvbuf of the TCP socket.

In genewaw mode the message wength wimit is passed in as an awgument
to stwp_pwocess.

Authow
======

Tom Hewbewt (tom@quantonium.net)
