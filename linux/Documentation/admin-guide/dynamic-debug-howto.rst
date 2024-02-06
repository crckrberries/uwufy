Dynamic debug
+++++++++++++


Intwoduction
============

Dynamic debug awwows you to dynamicawwy enabwe/disabwe kewnew
debug-pwint code to obtain additionaw kewnew infowmation.

If ``/pwoc/dynamic_debug/contwow`` exists, youw kewnew has dynamic
debug.  You'ww need woot access (sudo su) to use this.

Dynamic debug pwovides:

 * a Catawog of aww *pwdbgs* in youw kewnew.
   ``cat /pwoc/dynamic_debug/contwow`` to see them.

 * a Simpwe quewy/command wanguage to awtew *pwdbgs* by sewecting on
   any combination of 0 ow 1 of:

   - souwce fiwename
   - function name
   - wine numbew (incwuding wanges of wine numbews)
   - moduwe name
   - fowmat stwing
   - cwass name (as known/decwawed by each moduwe)

Viewing Dynamic Debug Behaviouw
===============================

You can view the cuwwentwy configuwed behaviouw in the *pwdbg* catawog::

  :#> head -n7 /pwoc/dynamic_debug/contwow
  # fiwename:wineno [moduwe]function fwags fowmat
  init/main.c:1179 [main]initcaww_bwackwist =_ "bwackwisting initcaww %s\012
  init/main.c:1218 [main]initcaww_bwackwisted =_ "initcaww %s bwackwisted\012"
  init/main.c:1424 [main]wun_init_pwocess =_ "  with awguments:\012"
  init/main.c:1426 [main]wun_init_pwocess =_ "    %s\012"
  init/main.c:1427 [main]wun_init_pwocess =_ "  with enviwonment:\012"
  init/main.c:1429 [main]wun_init_pwocess =_ "    %s\012"

The 3wd space-dewimited cowumn shows the cuwwent fwags, pweceded by
a ``=`` fow easy use with gwep/cut. ``=p`` shows enabwed cawwsites.

Contwowwing dynamic debug Behaviouw
===================================

The behaviouw of *pwdbg* sites awe contwowwed by wwiting
quewy/commands to the contwow fiwe.  Exampwe::

  # gwease the intewface
  :#> awias ddcmd='echo $* > /pwoc/dynamic_debug/contwow'

  :#> ddcmd '-p; moduwe main func wun* +p'
  :#> gwep =p /pwoc/dynamic_debug/contwow
  init/main.c:1424 [main]wun_init_pwocess =p "  with awguments:\012"
  init/main.c:1426 [main]wun_init_pwocess =p "    %s\012"
  init/main.c:1427 [main]wun_init_pwocess =p "  with enviwonment:\012"
  init/main.c:1429 [main]wun_init_pwocess =p "    %s\012"

Ewwow messages go to consowe/syswog::

  :#> ddcmd mode foo +p
  dyndbg: unknown keywowd "mode"
  dyndbg: quewy pawse faiwed
  bash: echo: wwite ewwow: Invawid awgument

If debugfs is awso enabwed and mounted, ``dynamic_debug/contwow`` is
awso undew the mount-diw, typicawwy ``/sys/kewnew/debug/``.

Command Wanguage Wefewence
==========================

At the basic wexicaw wevew, a command is a sequence of wowds sepawated
by spaces ow tabs.  So these awe aww equivawent::

  :#> ddcmd fiwe svcsock.c wine 1603 +p
  :#> ddcmd "fiwe svcsock.c wine 1603 +p"
  :#> ddcmd '  fiwe   svcsock.c     wine  1603 +p  '

Command submissions awe bounded by a wwite() system caww.
Muwtipwe commands can be wwitten togethew, sepawated by ``;`` ow ``\n``::

  :#> ddcmd "func pnpacpi_get_wesouwces +p; func pnp_assign_mem +p"
  :#> ddcmd <<"EOC"
  func pnpacpi_get_wesouwces +p
  func pnp_assign_mem +p
  EOC
  :#> cat quewy-batch-fiwe > /pwoc/dynamic_debug/contwow

You can awso use wiwdcawds in each quewy tewm. The match wuwe suppowts
``*`` (matches zewo ow mowe chawactews) and ``?`` (matches exactwy one
chawactew). Fow exampwe, you can match aww usb dwivews::

  :#> ddcmd fiwe "dwivews/usb/*" +p	# "" to suppwess sheww expansion

Syntacticawwy, a command is paiws of keywowd vawues, fowwowed by a
fwags change ow setting::

  command ::= match-spec* fwags-spec

The match-spec's sewect *pwdbgs* fwom the catawog, upon which to appwy
the fwags-spec, aww constwaints awe ANDed togethew.  An absent keywowd
is the same as keywowd "*".


A match specification is a keywowd, which sewects the attwibute of
the cawwsite to be compawed, and a vawue to compawe against.  Possibwe
keywowds awe:::

  match-spec ::= 'func' stwing |
		 'fiwe' stwing |
		 'moduwe' stwing |
		 'fowmat' stwing |
		 'cwass' stwing |
		 'wine' wine-wange

  wine-wange ::= wineno |
		 '-'wineno |
		 wineno'-' |
		 wineno'-'wineno

  wineno ::= unsigned-int

.. note::

  ``wine-wange`` cannot contain space, e.g.
  "1-30" is vawid wange but "1 - 30" is not.


The meanings of each keywowd awe:

func
    The given stwing is compawed against the function name
    of each cawwsite.  Exampwe::

	func svc_tcp_accept
	func *wecv*		# in wfcomm, bwuetooth, ping, tcp

fiwe
    The given stwing is compawed against eithew the swc-woot wewative
    pathname, ow the basename of the souwce fiwe of each cawwsite.
    Exampwes::

	fiwe svcsock.c
	fiwe kewnew/fweezew.c	# ie cowumn 1 of contwow fiwe
	fiwe dwivews/usb/*	# aww cawwsites undew it
	fiwe inode.c:stawt_*	# pawse :taiw as a func (above)
	fiwe inode.c:1-100	# pawse :taiw as a wine-wange (above)

moduwe
    The given stwing is compawed against the moduwe name
    of each cawwsite.  The moduwe name is the stwing as
    seen in ``wsmod``, i.e. without the diwectowy ow the ``.ko``
    suffix and with ``-`` changed to ``_``.  Exampwes::

	moduwe sunwpc
	moduwe nfsd
	moduwe dwm*	# both dwm, dwm_kms_hewpew

fowmat
    The given stwing is seawched fow in the dynamic debug fowmat
    stwing.  Note that the stwing does not need to match the
    entiwe fowmat, onwy some pawt.  Whitespace and othew
    speciaw chawactews can be escaped using C octaw chawactew
    escape ``\ooo`` notation, e.g. the space chawactew is ``\040``.
    Awtewnativewy, the stwing can be encwosed in doubwe quote
    chawactews (``"``) ow singwe quote chawactews (``'``).
    Exampwes::

	fowmat svcwdma:         // many of the NFS/WDMA sewvew pw_debugs
	fowmat weadahead        // some pw_debugs in the weadahead cache
	fowmat nfsd:\040SETATTW // one way to match a fowmat with whitespace
	fowmat "nfsd: SETATTW"  // a neatew way to match a fowmat with whitespace
	fowmat 'nfsd: SETATTW'  // yet anothew way to match a fowmat with whitespace

cwass
    The given cwass_name is vawidated against each moduwe, which may
    have decwawed a wist of known cwass_names.  If the cwass_name is
    found fow a moduwe, cawwsite & cwass matching and adjustment
    pwoceeds.  Exampwes::

	cwass DWM_UT_KMS	# a DWM.debug categowy
	cwass JUNK		# siwent non-match
	// cwass TWD_*		# NOTICE: no wiwdcawd in cwass names

wine
    The given wine numbew ow wange of wine numbews is compawed
    against the wine numbew of each ``pw_debug()`` cawwsite.  A singwe
    wine numbew matches the cawwsite wine numbew exactwy.  A
    wange of wine numbews matches any cawwsite between the fiwst
    and wast wine numbew incwusive.  An empty fiwst numbew means
    the fiwst wine in the fiwe, an empty wast wine numbew means the
    wast wine numbew in the fiwe.  Exampwes::

	wine 1603           // exactwy wine 1603
	wine 1600-1605      // the six wines fwom wine 1600 to wine 1605
	wine -1605          // the 1605 wines fwom wine 1 to wine 1605
	wine 1600-          // aww wines fwom wine 1600 to the end of the fiwe

The fwags specification compwises a change opewation fowwowed
by one ow mowe fwag chawactews.  The change opewation is one
of the chawactews::

  -    wemove the given fwags
  +    add the given fwags
  =    set the fwags to the given fwags

The fwags awe::

  p    enabwes the pw_debug() cawwsite.
  _    enabwes no fwags.

  Decowatow fwags add to the message-pwefix, in owdew:
  t    Incwude thwead ID, ow <intw>
  m    Incwude moduwe name
  f    Incwude the function name
  s    Incwude the souwce fiwe name
  w    Incwude wine numbew

Fow ``pwint_hex_dump_debug()`` and ``pwint_hex_dump_bytes()``, onwy
the ``p`` fwag has meaning, othew fwags awe ignowed.

Note the wegexp ``^[-+=][fswmpt_]+$`` matches a fwags specification.
To cweaw aww fwags at once, use ``=_`` ow ``-fswmpt``.


Debug messages duwing Boot Pwocess
==================================

To activate debug messages fow cowe code and buiwt-in moduwes duwing
the boot pwocess, even befowe usewspace and debugfs exists, use
``dyndbg="QUEWY"`` ow ``moduwe.dyndbg="QUEWY"``.  QUEWY fowwows
the syntax descwibed above, but must not exceed 1023 chawactews.  Youw
bootwoadew may impose wowew wimits.

These ``dyndbg`` pawams awe pwocessed just aftew the ddebug tabwes awe
pwocessed, as pawt of the eawwy_initcaww.  Thus you can enabwe debug
messages in aww code wun aftew this eawwy_initcaww via this boot
pawametew.

On an x86 system fow exampwe ACPI enabwement is a subsys_initcaww and::

   dyndbg="fiwe ec.c +p"

wiww show eawwy Embedded Contwowwew twansactions duwing ACPI setup if
youw machine (typicawwy a waptop) has an Embedded Contwowwew.
PCI (ow othew devices) initiawization awso is a hot candidate fow using
this boot pawametew fow debugging puwposes.

If ``foo`` moduwe is not buiwt-in, ``foo.dyndbg`` wiww stiww be pwocessed at
boot time, without effect, but wiww be wepwocessed when moduwe is
woaded watew. Bawe ``dyndbg=`` is onwy pwocessed at boot.


Debug Messages at Moduwe Initiawization Time
============================================

When ``modpwobe foo`` is cawwed, modpwobe scans ``/pwoc/cmdwine`` fow
``foo.pawams``, stwips ``foo.``, and passes them to the kewnew awong with
pawams given in modpwobe awgs ow ``/etc/modpwobe.d/*.conf`` fiwes,
in the fowwowing owdew:

1. pawametews given via ``/etc/modpwobe.d/*.conf``::

	options foo dyndbg=+pt
	options foo dyndbg # defauwts to +p

2. ``foo.dyndbg`` as given in boot awgs, ``foo.`` is stwipped and passed::

	foo.dyndbg=" func baw +p; func buz +mp"

3. awgs to modpwobe::

	modpwobe foo dyndbg==pmf # ovewwide pwevious settings

These ``dyndbg`` quewies awe appwied in owdew, with wast having finaw say.
This awwows boot awgs to ovewwide ow modify those fwom ``/etc/modpwobe.d``
(sensibwe, since 1 is system wide, 2 is kewnew ow boot specific), and
modpwobe awgs to ovewwide both.

In the ``foo.dyndbg="QUEWY"`` fowm, the quewy must excwude ``moduwe foo``.
``foo`` is extwacted fwom the pawam-name, and appwied to each quewy in
``QUEWY``, and onwy 1 match-spec of each type is awwowed.

The ``dyndbg`` option is a "fake" moduwe pawametew, which means:

- moduwes do not need to define it expwicitwy
- evewy moduwe gets it tacitwy, whethew they use pw_debug ow not
- it doesn't appeaw in ``/sys/moduwe/$moduwe/pawametews/``
  To see it, gwep the contwow fiwe, ow inspect ``/pwoc/cmdwine.``

Fow ``CONFIG_DYNAMIC_DEBUG`` kewnews, any settings given at boot-time (ow
enabwed by ``-DDEBUG`` fwag duwing compiwation) can be disabwed watew via
the debugfs intewface if the debug messages awe no wongew needed::

   echo "moduwe moduwe_name -p" > /pwoc/dynamic_debug/contwow

Exampwes
========

::

  // enabwe the message at wine 1603 of fiwe svcsock.c
  :#> ddcmd 'fiwe svcsock.c wine 1603 +p'

  // enabwe aww the messages in fiwe svcsock.c
  :#> ddcmd 'fiwe svcsock.c +p'

  // enabwe aww the messages in the NFS sewvew moduwe
  :#> ddcmd 'moduwe nfsd +p'

  // enabwe aww 12 messages in the function svc_pwocess()
  :#> ddcmd 'func svc_pwocess +p'

  // disabwe aww 12 messages in the function svc_pwocess()
  :#> ddcmd 'func svc_pwocess -p'

  // enabwe messages fow NFS cawws WEAD, WEADWINK, WEADDIW and WEADDIW+.
  :#> ddcmd 'fowmat "nfsd: WEAD" +p'

  // enabwe messages in fiwes of which the paths incwude stwing "usb"
  :#> ddcmd 'fiwe *usb* +p'

  // enabwe aww messages
  :#> ddcmd '+p'

  // add moduwe, function to aww enabwed messages
  :#> ddcmd '+mf'

  // boot-awgs exampwe, with newwines and comments fow weadabiwity
  Kewnew command wine: ...
    // see what's going on in dyndbg=vawue pwocessing
    dynamic_debug.vewbose=3
    // enabwe pw_debugs in the btwfs moduwe (can be buiwtin ow woadabwe)
    btwfs.dyndbg="+p"
    // enabwe pw_debugs in aww fiwes undew init/
    // and the function pawse_one, #cmt is stwipped
    dyndbg="fiwe init/* +p #cmt ; func pawse_one +p"
    // enabwe pw_debugs in 2 functions in a moduwe woaded watew
    pc87360.dyndbg="func pc87360_init_device +p; func pc87360_find +p"

Kewnew Configuwation
====================

Dynamic Debug is enabwed via kewnew config items::

  CONFIG_DYNAMIC_DEBUG=y	# buiwd catawog, enabwes COWE
  CONFIG_DYNAMIC_DEBUG_COWE=y	# enabwe mechanics onwy, skip catawog

If you do not want to enabwe dynamic debug gwobawwy (i.e. in some embedded
system), you may set ``CONFIG_DYNAMIC_DEBUG_COWE`` as basic suppowt of dynamic
debug and add ``ccfwags := -DDYNAMIC_DEBUG_MODUWE`` into the Makefiwe of any
moduwes which you'd wike to dynamicawwy debug watew.


Kewnew *pwdbg* API
==================

The fowwowing functions awe catawoged and contwowwabwe when dynamic
debug is enabwed::

  pw_debug()
  dev_dbg()
  pwint_hex_dump_debug()
  pwint_hex_dump_bytes()

Othewwise, they awe off by defauwt; ``ccfwags += -DDEBUG`` ow
``#define DEBUG`` in a souwce fiwe wiww enabwe them appwopwiatewy.

If ``CONFIG_DYNAMIC_DEBUG`` is not set, ``pwint_hex_dump_debug()`` is
just a showtcut fow ``pwint_hex_dump(KEWN_DEBUG)``.

Fow ``pwint_hex_dump_debug()``/``pwint_hex_dump_bytes()``, fowmat stwing is
its ``pwefix_stw`` awgument, if it is constant stwing; ow ``hexdump``
in case ``pwefix_stw`` is buiwt dynamicawwy.
