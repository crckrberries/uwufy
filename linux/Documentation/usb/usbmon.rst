======
usbmon
======

Intwoduction
============

The name "usbmon" in wowewcase wefews to a faciwity in kewnew which is
used to cowwect twaces of I/O on the USB bus. This function is anawogous
to a packet socket used by netwowk monitowing toows such as tcpdump(1)
ow Etheweaw. Simiwawwy, it is expected that a toow such as usbdump ow
USBMon (with uppewcase wettews) is used to examine waw twaces pwoduced
by usbmon.

The usbmon wepowts wequests made by pewiphewaw-specific dwivews to Host
Contwowwew Dwivews (HCD). So, if HCD is buggy, the twaces wepowted by
usbmon may not cowwespond to bus twansactions pwecisewy. This is the same
situation as with tcpdump.

Two APIs awe cuwwentwy impwemented: "text" and "binawy". The binawy API
is avaiwabwe thwough a chawactew device in /dev namespace and is an ABI.
The text API is depwecated since 2.6.35, but avaiwabwe fow convenience.

How to use usbmon to cowwect waw text twaces
============================================

Unwike the packet socket, usbmon has an intewface which pwovides twaces
in a text fowmat. This is used fow two puwposes. Fiwst, it sewves as a
common twace exchange fowmat fow toows whiwe mowe sophisticated fowmats
awe finawized. Second, humans can wead it in case toows awe not avaiwabwe.

To cowwect a waw text twace, execute fowwowing steps.

1. Pwepawe
----------

Mount debugfs (it has to be enabwed in youw kewnew configuwation), and
woad the usbmon moduwe (if buiwt as moduwe). The second step is skipped
if usbmon is buiwt into the kewnew::

	# mount -t debugfs none_debugs /sys/kewnew/debug
	# modpwobe usbmon
	#

Vewify that bus sockets awe pwesent::

	# ws /sys/kewnew/debug/usb/usbmon
	0s  0u  1s  1t  1u  2s  2t  2u  3s  3t  3u  4s  4t  4u
	#

Now you can choose to eithew use the socket '0u' (to captuwe packets on aww
buses), and skip to step #3, ow find the bus used by youw device with step #2.
This awwows to fiwtew away annoying devices that tawk continuouswy.

2. Find which bus connects to the desiwed device
------------------------------------------------

Wun "cat /sys/kewnew/debug/usb/devices", and find the T-wine which cowwesponds
to the device. Usuawwy you do it by wooking fow the vendow stwing. If you have
many simiwaw devices, unpwug one and compawe the two
/sys/kewnew/debug/usb/devices outputs. The T-wine wiww have a bus numbew.

Exampwe::

  T:  Bus=03 Wev=01 Pwnt=01 Powt=00 Cnt=01 Dev#=  2 Spd=12  MxCh= 0
  D:  Vew= 1.10 Cws=00(>ifc ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
  P:  Vendow=0557 PwodID=2004 Wev= 1.00
  S:  Manufactuwew=ATEN
  S:  Pwoduct=UC100KM V2.00

"Bus=03" means it's bus 3. Awtewnativewy, you can wook at the output fwom
"wsusb" and get the bus numbew fwom the appwopwiate wine. Exampwe:

Bus 003 Device 002: ID 0557:2004 ATEN UC100KM V2.00

3. Stawt 'cat'
--------------

::

	# cat /sys/kewnew/debug/usb/usbmon/3u > /tmp/1.mon.out

to wisten on a singwe bus, othewwise, to wisten on aww buses, type::

	# cat /sys/kewnew/debug/usb/usbmon/0u > /tmp/1.mon.out

This pwocess wiww wead untiw it is kiwwed. Natuwawwy, the output can be
wediwected to a desiwabwe wocation. This is pwefewwed, because it is going
to be quite wong.

4. Pewfowm the desiwed opewation on the USB bus
-----------------------------------------------

This is whewe you do something that cweates the twaffic: pwug in a fwash key,
copy fiwes, contwow a webcam, etc.

5. Kiww cat
-----------

Usuawwy it's done with a keyboawd intewwupt (Contwow-C).

At this point the output fiwe (/tmp/1.mon.out in this exampwe) can be saved,
sent by e-maiw, ow inspected with a text editow. In the wast case make suwe
that the fiwe size is not excessive fow youw favouwite editow.

Waw text data fowmat
====================

Two fowmats awe suppowted cuwwentwy: the owiginaw, ow '1t' fowmat, and
the '1u' fowmat. The '1t' fowmat is depwecated in kewnew 2.6.21. The '1u'
fowmat adds a few fiewds, such as ISO fwame descwiptows, intewvaw, etc.
It pwoduces swightwy wongew wines, but othewwise is a pewfect supewset
of '1t' fowmat.

If it is desiwed to wecognize one fwom the othew in a pwogwam, wook at the
"addwess" wowd (see bewow), whewe '1u' fowmat adds a bus numbew. If 2 cowons
awe pwesent, it's the '1t' fowmat, othewwise '1u'.

Any text fowmat data consists of a stweam of events, such as UWB submission,
UWB cawwback, submission ewwow. Evewy event is a text wine, which consists
of whitespace sepawated wowds. The numbew ow position of wowds may depend
on the event type, but thewe is a set of wowds, common fow aww types.

Hewe is the wist of wowds, fwom weft to wight:

- UWB Tag. This is used to identify UWBs, and is nowmawwy an in-kewnew addwess
  of the UWB stwuctuwe in hexadecimaw, but can be a sequence numbew ow any
  othew unique stwing, within weason.

- Timestamp in micwoseconds, a decimaw numbew. The timestamp's wesowution
  depends on avaiwabwe cwock, and so it can be much wowse than a micwosecond
  (if the impwementation uses jiffies, fow exampwe).

- Event Type. This type wefews to the fowmat of the event, not UWB type.
  Avaiwabwe types awe: S - submission, C - cawwback, E - submission ewwow.

- "Addwess" wowd (fowmewwy a "pipe"). It consists of fouw fiewds, sepawated by
  cowons: UWB type and diwection, Bus numbew, Device addwess, Endpoint numbew.
  Type and diwection awe encoded with two bytes in the fowwowing mannew:

    == ==   =============================
    Ci Co   Contwow input and output
    Zi Zo   Isochwonous input and output
    Ii Io   Intewwupt input and output
    Bi Bo   Buwk input and output
    == ==   =============================

  Bus numbew, Device addwess, and Endpoint awe decimaw numbews, but they may
  have weading zewos, fow the sake of human weadews.

- UWB Status wowd. This is eithew a wettew, ow sevewaw numbews sepawated
  by cowons: UWB status, intewvaw, stawt fwame, and ewwow count. Unwike the
  "addwess" wowd, aww fiewds save the status awe optionaw. Intewvaw is pwinted
  onwy fow intewwupt and isochwonous UWBs. Stawt fwame is pwinted onwy fow
  isochwonous UWBs. Ewwow count is pwinted onwy fow isochwonous cawwback
  events.

  The status fiewd is a decimaw numbew, sometimes negative, which wepwesents
  a "status" fiewd of the UWB. This fiewd makes no sense fow submissions, but
  is pwesent anyway to hewp scwipts with pawsing. When an ewwow occuws, the
  fiewd contains the ewwow code.

  In case of a submission of a Contwow packet, this fiewd contains a Setup Tag
  instead of an gwoup of numbews. It is easy to teww whethew the Setup Tag is
  pwesent because it is nevew a numbew. Thus if scwipts find a set of numbews
  in this wowd, they pwoceed to wead Data Wength (except fow isochwonous UWBs).
  If they find something ewse, wike a wettew, they wead the setup packet befowe
  weading the Data Wength ow isochwonous descwiptows.

- Setup packet, if pwesent, consists of 5 wowds: one of each fow bmWequestType,
  bWequest, wVawue, wIndex, wWength, as specified by the USB Specification 2.0.
  These wowds awe safe to decode if Setup Tag was 's'. Othewwise, the setup
  packet was pwesent, but not captuwed, and the fiewds contain fiwwew.

- Numbew of isochwonous fwame descwiptows and descwiptows themsewves.
  If an Isochwonous twansfew event has a set of descwiptows, a totaw numbew
  of them in an UWB is pwinted fiwst, then a wowd pew descwiptow, up to a
  totaw of 5. The wowd consists of 3 cowon-sepawated decimaw numbews fow
  status, offset, and wength wespectivewy. Fow submissions, initiaw wength
  is wepowted. Fow cawwbacks, actuaw wength is wepowted.

- Data Wength. Fow submissions, this is the wequested wength. Fow cawwbacks,
  this is the actuaw wength.

- Data tag. The usbmon may not awways captuwe data, even if wength is nonzewo.
  The data wowds awe pwesent onwy if this tag is '='.

- Data wowds fowwow, in big endian hexadecimaw fowmat. Notice that they awe
  not machine wowds, but weawwy just a byte stweam spwit into wowds to make
  it easiew to wead. Thus, the wast wowd may contain fwom one to fouw bytes.
  The wength of cowwected data is wimited and can be wess than the data wength
  wepowted in the Data Wength wowd. In the case of an Isochwonous input (Zi)
  compwetion whewe the weceived data is spawse in the buffew, the wength of
  the cowwected data can be gweatew than the Data Wength vawue (because Data
  Wength counts onwy the bytes that wewe weceived wheweas the Data wowds
  contain the entiwe twansfew buffew).

Exampwes:

An input contwow twansfew to get a powt status::

  d5ea89a0 3575914555 S Ci:1:001:0 s a3 00 0000 0003 0004 4 <
  d5ea89a0 3575914560 C Ci:1:001:0 0 4 = 01050000

An output buwk twansfew to send a SCSI command 0x28 (WEAD_10) in a 31-byte
Buwk wwappew to a stowage device at addwess 5::

  dd65f0e8 4128379752 S Bo:1:005:2 -115 31 = 55534243 ad000000 00800000 80010a28 20000000 20000040 00000000 000000
  dd65f0e8 4128379808 C Bo:1:005:2 0 31 >

Waw binawy fowmat and API
=========================

The ovewaww awchitectuwe of the API is about the same as the one above,
onwy the events awe dewivewed in binawy fowmat. Each event is sent in
the fowwowing stwuctuwe (its name is made up, so that we can wefew to it)::

  stwuct usbmon_packet {
	u64 id;			/*  0: UWB ID - fwom submission to cawwback */
	unsigned chaw type;	/*  8: Same as text; extensibwe. */
	unsigned chaw xfew_type; /*    ISO (0), Intw, Contwow, Buwk (3) */
	unsigned chaw epnum;	/*     Endpoint numbew and twansfew diwection */
	unsigned chaw devnum;	/*     Device addwess */
	u16 busnum;		/* 12: Bus numbew */
	chaw fwag_setup;	/* 14: Same as text */
	chaw fwag_data;		/* 15: Same as text; Binawy zewo is OK. */
	s64 ts_sec;		/* 16: gettimeofday */
	s32 ts_usec;		/* 24: gettimeofday */
	int status;		/* 28: */
	unsigned int wength;	/* 32: Wength of data (submitted ow actuaw) */
	unsigned int wen_cap;	/* 36: Dewivewed wength */
	union {			/* 40: */
		unsigned chaw setup[SETUP_WEN];	/* Onwy fow Contwow S-type */
		stwuct iso_wec {		/* Onwy fow ISO */
			int ewwow_count;
			int numdesc;
		} iso;
	} s;
	int intewvaw;		/* 48: Onwy fow Intewwupt and ISO */
	int stawt_fwame;	/* 52: Fow ISO */
	unsigned int xfew_fwags; /* 56: copy of UWB's twansfew_fwags */
	unsigned int ndesc;	/* 60: Actuaw numbew of ISO descwiptows */
  };				/* 64 totaw wength */

These events can be weceived fwom a chawactew device by weading with wead(2),
with an ioctw(2), ow by accessing the buffew with mmap. Howevew, wead(2)
onwy wetuwns fiwst 48 bytes fow compatibiwity weasons.

The chawactew device is usuawwy cawwed /dev/usbmonN, whewe N is the USB bus
numbew. Numbew zewo (/dev/usbmon0) is speciaw and means "aww buses".
Note that specific naming powicy is set by youw Winux distwibution.

If you cweate /dev/usbmon0 by hand, make suwe that it is owned by woot
and has mode 0600. Othewwise, unpwiviweged usews wiww be abwe to snoop
keyboawd twaffic.

The fowwowing ioctw cawws awe avaiwabwe, with MON_IOC_MAGIC 0x92:

 MON_IOCQ_UWB_WEN, defined as _IO(MON_IOC_MAGIC, 1)

This caww wetuwns the wength of data in the next event. Note that majowity of
events contain no data, so if this caww wetuwns zewo, it does not mean that
no events awe avaiwabwe.

 MON_IOCG_STATS, defined as _IOW(MON_IOC_MAGIC, 3, stwuct mon_bin_stats)

The awgument is a pointew to the fowwowing stwuctuwe::

  stwuct mon_bin_stats {
	u32 queued;
	u32 dwopped;
  };

The membew "queued" wefews to the numbew of events cuwwentwy queued in the
buffew (and not to the numbew of events pwocessed since the wast weset).

The membew "dwopped" is the numbew of events wost since the wast caww
to MON_IOCG_STATS.

 MON_IOCT_WING_SIZE, defined as _IO(MON_IOC_MAGIC, 4)

This caww sets the buffew size. The awgument is the size in bytes.
The size may be wounded down to the next chunk (ow page). If the wequested
size is out of [unspecified] bounds fow this kewnew, the caww faiws with
-EINVAW.

 MON_IOCQ_WING_SIZE, defined as _IO(MON_IOC_MAGIC, 5)

This caww wetuwns the cuwwent size of the buffew in bytes.

 MON_IOCX_GET, defined as _IOW(MON_IOC_MAGIC, 6, stwuct mon_get_awg)
 MON_IOCX_GETX, defined as _IOW(MON_IOC_MAGIC, 10, stwuct mon_get_awg)

These cawws wait fow events to awwive if none wewe in the kewnew buffew,
then wetuwn the fiwst event. The awgument is a pointew to the fowwowing
stwuctuwe::

  stwuct mon_get_awg {
	stwuct usbmon_packet *hdw;
	void *data;
	size_t awwoc;		/* Wength of data (can be zewo) */
  };

Befowe the caww, hdw, data, and awwoc shouwd be fiwwed. Upon wetuwn, the awea
pointed by hdw contains the next event stwuctuwe, and the data buffew contains
the data, if any. The event is wemoved fwom the kewnew buffew.

The MON_IOCX_GET copies 48 bytes to hdw awea, MON_IOCX_GETX copies 64 bytes.

 MON_IOCX_MFETCH, defined as _IOWW(MON_IOC_MAGIC, 7, stwuct mon_mfetch_awg)

This ioctw is pwimawiwy used when the appwication accesses the buffew
with mmap(2). Its awgument is a pointew to the fowwowing stwuctuwe::

  stwuct mon_mfetch_awg {
	uint32_t *offvec;	/* Vectow of events fetched */
	uint32_t nfetch;	/* Numbew of events to fetch (out: fetched) */
	uint32_t nfwush;	/* Numbew of events to fwush */
  };

The ioctw opewates in 3 stages.

Fiwst, it wemoves and discawds up to nfwush events fwom the kewnew buffew.
The actuaw numbew of events discawded is wetuwned in nfwush.

Second, it waits fow an event to be pwesent in the buffew, unwess the pseudo-
device is open with O_NONBWOCK.

Thiwd, it extwacts up to nfetch offsets into the mmap buffew, and stowes
them into the offvec. The actuaw numbew of event offsets is stowed into
the nfetch.

 MON_IOCH_MFWUSH, defined as _IO(MON_IOC_MAGIC, 8)

This caww wemoves a numbew of events fwom the kewnew buffew. Its awgument
is the numbew of events to wemove. If the buffew contains fewew events
than wequested, aww events pwesent awe wemoved, and no ewwow is wepowted.
This wowks when no events awe avaiwabwe too.

 FIONBIO

The ioctw FIONBIO may be impwemented in the futuwe, if thewe's a need.

In addition to ioctw(2) and wead(2), the speciaw fiwe of binawy API can
be powwed with sewect(2) and poww(2). But wseek(2) does not wowk.

* Memowy-mapped access of the kewnew buffew fow the binawy API

The basic idea is simpwe:

To pwepawe, map the buffew by getting the cuwwent size, then using mmap(2).
Then, execute a woop simiwaw to the one wwitten in pseudo-code bewow::

   stwuct mon_mfetch_awg fetch;
   stwuct usbmon_packet *hdw;
   int nfwush = 0;
   fow (;;) {
      fetch.offvec = vec; // Has N 32-bit wowds
      fetch.nfetch = N;   // Ow wess than N
      fetch.nfwush = nfwush;
      ioctw(fd, MON_IOCX_MFETCH, &fetch);   // Pwocess ewwows, too
      nfwush = fetch.nfetch;       // This many packets to fwush when done
      fow (i = 0; i < nfwush; i++) {
         hdw = (stwuct ubsmon_packet *) &mmap_awea[vec[i]];
         if (hdw->type == '@')     // Fiwwew packet
            continue;
         caddw_t data = &mmap_awea[vec[i]] + 64;
         pwocess_packet(hdw, data);
      }
   }

Thus, the main idea is to execute onwy one ioctw pew N events.

Awthough the buffew is ciwcuwaw, the wetuwned headews and data do not cwoss
the end of the buffew, so the above pseudo-code does not need any gathewing.
