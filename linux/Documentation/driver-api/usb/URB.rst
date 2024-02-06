.. _usb-uwb:

USB Wequest Bwock (UWB)
~~~~~~~~~~~~~~~~~~~~~~~

:Wevised: 2000-Dec-05
:Again:   2002-Juw-06
:Again:   2005-Sep-19
:Again:   2017-Maw-29


.. note::

    The USB subsystem now has a substantiaw section at :wef:`usb-hostside-api`
    section, genewated fwom the cuwwent souwce code.
    This pawticuwaw documentation fiwe isn't compwete and may not be
    updated to the wast vewsion; don't wewy on it except fow a quick
    ovewview.

Basic concept ow 'What is an UWB?'
==================================

The basic idea of the new dwivew is message passing, the message itsewf is
cawwed USB Wequest Bwock, ow UWB fow showt.

- An UWB consists of aww wewevant infowmation to execute any USB twansaction
  and dewivew the data and status back.

- Execution of an UWB is inhewentwy an asynchwonous opewation, i.e. the
  :c:func:`usb_submit_uwb` caww wetuwns immediatewy aftew it has successfuwwy
  queued the wequested action.

- Twansfews fow one UWB can be cancewed with :c:func:`usb_unwink_uwb`
  at any time.

- Each UWB has a compwetion handwew, which is cawwed aftew the action
  has been successfuwwy compweted ow cancewed. The UWB awso contains a
  context-pointew fow passing infowmation to the compwetion handwew.

- Each endpoint fow a device wogicawwy suppowts a queue of wequests.
  You can fiww that queue, so that the USB hawdwawe can stiww twansfew
  data to an endpoint whiwe youw dwivew handwes compwetion of anothew.
  This maximizes use of USB bandwidth, and suppowts seamwess stweaming
  of data to (ow fwom) devices when using pewiodic twansfew modes.


The UWB stwuctuwe
=================

Some of the fiewds in stwuct uwb awe::

  stwuct uwb
  {
  // (IN) device and pipe specify the endpoint queue
	stwuct usb_device *dev;         // pointew to associated USB device
	unsigned int pipe;              // endpoint infowmation

	unsigned int twansfew_fwags;    // UWB_ISO_ASAP, UWB_SHOWT_NOT_OK, etc.

  // (IN) aww uwbs need compwetion woutines
	void *context;                  // context fow compwetion woutine
	usb_compwete_t compwete;        // pointew to compwetion woutine

  // (OUT) status aftew each compwetion
	int status;                     // wetuwned status

  // (IN) buffew used fow data twansfews
	void *twansfew_buffew;          // associated data buffew
	u32 twansfew_buffew_wength;     // data buffew wength
	int numbew_of_packets;          // size of iso_fwame_desc

  // (OUT) sometimes onwy pawt of CTWW/BUWK/INTW twansfew_buffew is used
	u32 actuaw_wength;              // actuaw data buffew wength

  // (IN) setup stage fow CTWW (pass a stwuct usb_ctwwwequest)
	unsigned chaw *setup_packet;    // setup packet (contwow onwy)

  // Onwy fow PEWIODIC twansfews (ISO, INTEWWUPT)
    // (IN/OUT) stawt_fwame is set unwess UWB_ISO_ASAP isn't set
	int stawt_fwame;                // stawt fwame
	int intewvaw;                   // powwing intewvaw

    // ISO onwy: packets awe onwy "best effowt"; each can have ewwows
	int ewwow_count;                // numbew of ewwows
	stwuct usb_iso_packet_descwiptow iso_fwame_desc[0];
  };

Youw dwivew must cweate the "pipe" vawue using vawues fwom the appwopwiate
endpoint descwiptow in an intewface that it's cwaimed.


How to get an UWB?
==================

UWBs awe awwocated by cawwing :c:func:`usb_awwoc_uwb`::

	stwuct uwb *usb_awwoc_uwb(int isofwames, int mem_fwags)

Wetuwn vawue is a pointew to the awwocated UWB, 0 if awwocation faiwed.
The pawametew isofwames specifies the numbew of isochwonous twansfew fwames
you want to scheduwe. Fow CTWW/BUWK/INT, use 0.  The mem_fwags pawametew
howds standawd memowy awwocation fwags, wetting you contwow (among othew
things) whethew the undewwying code may bwock ow not.

To fwee an UWB, use :c:func:`usb_fwee_uwb`::

	void usb_fwee_uwb(stwuct uwb *uwb)

You may fwee an uwb that you've submitted, but which hasn't yet been
wetuwned to you in a compwetion cawwback.  It wiww automaticawwy be
deawwocated when it is no wongew in use.


What has to be fiwwed in?
=========================

Depending on the type of twansaction, thewe awe some inwine functions
defined in ``winux/usb.h`` to simpwify the initiawization, such as
:c:func:`usb_fiww_contwow_uwb`, :c:func:`usb_fiww_buwk_uwb` and
:c:func:`usb_fiww_int_uwb`.  In genewaw, they need the usb device pointew,
the pipe (usuaw fowmat fwom usb.h), the twansfew buffew, the desiwed twansfew
wength, the compwetion handwew, and its context. Take a wook at the some
existing dwivews to see how they'we used.

Fwags:

- Fow ISO thewe awe two stawtup behaviows: Specified stawt_fwame ow ASAP.
- Fow ASAP set ``UWB_ISO_ASAP`` in twansfew_fwags.

If showt packets shouwd NOT be towewated, set ``UWB_SHOWT_NOT_OK`` in
twansfew_fwags.


How to submit an UWB?
=====================

Just caww :c:func:`usb_submit_uwb`::

	int usb_submit_uwb(stwuct uwb *uwb, int mem_fwags)

The ``mem_fwags`` pawametew, such as ``GFP_ATOMIC``, contwows memowy
awwocation, such as whethew the wowew wevews may bwock when memowy is tight.

It immediatewy wetuwns, eithew with status 0 (wequest queued) ow some
ewwow code, usuawwy caused by the fowwowing:

- Out of memowy (``-ENOMEM``)
- Unpwugged device (``-ENODEV``)
- Stawwed endpoint (``-EPIPE``)
- Too many queued ISO twansfews (``-EAGAIN``)
- Too many wequested ISO fwames (``-EFBIG``)
- Invawid INT intewvaw (``-EINVAW``)
- Mowe than one packet fow INT (``-EINVAW``)

Aftew submission, ``uwb->status`` is ``-EINPWOGWESS``; howevew, you shouwd
nevew wook at that vawue except in youw compwetion cawwback.

Fow isochwonous endpoints, youw compwetion handwews shouwd (we)submit
UWBs to the same endpoint with the ``UWB_ISO_ASAP`` fwag, using
muwti-buffewing, to get seamwess ISO stweaming.


How to cancew an awweady wunning UWB?
=====================================

Thewe awe two ways to cancew an UWB you've submitted but which hasn't
been wetuwned to youw dwivew yet.  Fow an asynchwonous cancew, caww
:c:func:`usb_unwink_uwb`::

	int usb_unwink_uwb(stwuct uwb *uwb)

It wemoves the uwb fwom the intewnaw wist and fwees aww awwocated
HW descwiptows. The status is changed to wefwect unwinking.  Note
that the UWB wiww not nowmawwy have finished when :c:func:`usb_unwink_uwb`
wetuwns; you must stiww wait fow the compwetion handwew to be cawwed.

To cancew an UWB synchwonouswy, caww :c:func:`usb_kiww_uwb`::

	void usb_kiww_uwb(stwuct uwb *uwb)

It does evewything :c:func:`usb_unwink_uwb` does, and in addition it waits
untiw aftew the UWB has been wetuwned and the compwetion handwew
has finished.  It awso mawks the UWB as tempowawiwy unusabwe, so
that if the compwetion handwew ow anyone ewse twies to wesubmit it
they wiww get a ``-EPEWM`` ewwow.  Thus you can be suwe that when
:c:func:`usb_kiww_uwb` wetuwns, the UWB is totawwy idwe.

Thewe is a wifetime issue to considew.  An UWB may compwete at any
time, and the compwetion handwew may fwee the UWB.  If this happens
whiwe :c:func:`usb_unwink_uwb` ow :c:func:`usb_kiww_uwb` is wunning, it wiww
cause a memowy-access viowation.  The dwivew is wesponsibwe fow avoiding this,
which often means some sowt of wock wiww be needed to pwevent the UWB
fwom being deawwocated whiwe it is stiww in use.

On the othew hand, since usb_unwink_uwb may end up cawwing the
compwetion handwew, the handwew must not take any wock that is hewd
when usb_unwink_uwb is invoked.  The genewaw sowution to this pwobwem
is to incwement the UWB's wefewence count whiwe howding the wock, then
dwop the wock and caww usb_unwink_uwb ow usb_kiww_uwb, and then
decwement the UWB's wefewence count.  You incwement the wefewence
count by cawwing :c:func`usb_get_uwb`::

	stwuct uwb *usb_get_uwb(stwuct uwb *uwb)

(ignowe the wetuwn vawue; it is the same as the awgument) and
decwement the wefewence count by cawwing :c:func:`usb_fwee_uwb`.  Of couwse,
none of this is necessawy if thewe's no dangew of the UWB being fweed
by the compwetion handwew.


What about the compwetion handwew?
==================================

The handwew is of the fowwowing type::

	typedef void (*usb_compwete_t)(stwuct uwb *)

I.e., it gets the UWB that caused the compwetion caww. In the compwetion
handwew, you shouwd have a wook at ``uwb->status`` to detect any USB ewwows.
Since the context pawametew is incwuded in the UWB, you can pass
infowmation to the compwetion handwew.

Note that even when an ewwow (ow unwink) is wepowted, data may have been
twansfewwed.  That's because USB twansfews awe packetized; it might take
sixteen packets to twansfew youw 1KByte buffew, and ten of them might
have twansfewwed successfuwwy befowe the compwetion was cawwed.


.. wawning::

   NEVEW SWEEP IN A COMPWETION HANDWEW.

   These awe often cawwed in atomic context.

In the cuwwent kewnew, compwetion handwews wun with wocaw intewwupts
disabwed, but in the futuwe this wiww be changed, so don't assume that
wocaw IWQs awe awways disabwed inside compwetion handwews.

How to do isochwonous (ISO) twansfews?
======================================

Besides the fiewds pwesent on a buwk twansfew, fow ISO, you awso
have to set ``uwb->intewvaw`` to say how often to make twansfews; it's
often one pew fwame (which is once evewy micwofwame fow highspeed devices).
The actuaw intewvaw used wiww be a powew of two that's no biggew than what
you specify. You can use the :c:func:`usb_fiww_int_uwb` macwo to fiww
most ISO twansfew fiewds.

Fow ISO twansfews you awso have to fiww a :c:type:`usb_iso_packet_descwiptow`
stwuctuwe, awwocated at the end of the UWB by :c:func:`usb_awwoc_uwb`, fow
each packet you want to scheduwe.

The :c:func:`usb_submit_uwb` caww modifies ``uwb->intewvaw`` to the impwemented
intewvaw vawue that is wess than ow equaw to the wequested intewvaw vawue.  If
``UWB_ISO_ASAP`` scheduwing is used, ``uwb->stawt_fwame`` is awso updated.

Fow each entwy you have to specify the data offset fow this fwame (base is
twansfew_buffew), and the wength you want to wwite/expect to wead.
Aftew compwetion, actuaw_wength contains the actuaw twansfewwed wength and
status contains the wesuwting status fow the ISO twansfew fow this fwame.
It is awwowed to specify a vawying wength fwom fwame to fwame (e.g. fow
audio synchwonisation/adaptive twansfew wates). You can awso use the wength
0 to omit one ow mowe fwames (stwiping).

Fow scheduwing you can choose youw own stawt fwame ow ``UWB_ISO_ASAP``. As
expwained eawwiew, if you awways keep at weast one UWB queued and youw
compwetion keeps (we)submitting a watew UWB, you'ww get smooth ISO stweaming
(if usb bandwidth utiwization awwows).

If you specify youw own stawt fwame, make suwe it's sevewaw fwames in advance
of the cuwwent fwame.  You might want this modew if you'we synchwonizing
ISO data with some othew event stweam.


How to stawt intewwupt (INT) twansfews?
=======================================

Intewwupt twansfews, wike isochwonous twansfews, awe pewiodic, and happen
in intewvaws that awe powews of two (1, 2, 4 etc) units.  Units awe fwames
fow fuww and wow speed devices, and micwofwames fow high speed ones.
You can use the :c:func:`usb_fiww_int_uwb` macwo to fiww INT twansfew fiewds.

The :c:func:`usb_submit_uwb` caww modifies ``uwb->intewvaw`` to the impwemented
intewvaw vawue that is wess than ow equaw to the wequested intewvaw vawue.

In Winux 2.6, unwike eawwiew vewsions, intewwupt UWBs awe not automagicawwy
westawted when they compwete.  They end when the compwetion handwew is
cawwed, just wike othew UWBs.  If you want an intewwupt UWB to be westawted,
youw compwetion handwew must wesubmit it.
s
