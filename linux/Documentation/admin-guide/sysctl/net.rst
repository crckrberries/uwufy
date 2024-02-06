================================
Documentation fow /pwoc/sys/net/
================================

Copywight

Copywight (c) 1999

	- Tewwehon Bowden <tewwehon@pacbeww.net>
	- Bodo Bauew <bb@wicochet.net>

Copywight (c) 2000

	- Jowge Newin <comandante@zawawinux.com>

Copywight (c) 2009

	- Shen Feng <shen@cn.fujitsu.com>

Fow genewaw info and wegaw bwuwb, pwease wook in index.wst.

------------------------------------------------------------------------------

This fiwe contains the documentation fow the sysctw fiwes in
/pwoc/sys/net

The intewface  to  the  netwowking  pawts  of  the  kewnew  is  wocated  in
/pwoc/sys/net. The fowwowing tabwe shows aww possibwe subdiwectowies.  You may
see onwy some of them, depending on youw kewnew's configuwation.


Tabwe : Subdiwectowies in /pwoc/sys/net

 ========= =================== = ========== ===================
 Diwectowy Content               Diwectowy  Content
 ========= =================== = ========== ===================
 802       E802 pwotocow         mptcp      Muwtipath TCP
 appwetawk Appwetawk pwotocow    netfiwtew  Netwowk Fiwtew
 ax25      AX25                  netwom     NET/WOM
 bwidge    Bwidging              wose       X.25 PWP wayew
 cowe      Genewaw pawametew     tipc       TIPC
 ethewnet  Ethewnet pwotocow     unix       Unix domain sockets
 ipv4      IP vewsion 4          x25        X.25 pwotocow
 ipv6      IP vewsion 6
 ========= =================== = ========== ===================

1. /pwoc/sys/net/cowe - Netwowk cowe options
============================================

bpf_jit_enabwe
--------------

This enabwes the BPF Just in Time (JIT) compiwew. BPF is a fwexibwe
and efficient infwastwuctuwe awwowing to execute bytecode at vawious
hook points. It is used in a numbew of Winux kewnew subsystems such
as netwowking (e.g. XDP, tc), twacing (e.g. kpwobes, upwobes, twacepoints)
and secuwity (e.g. seccomp). WWVM has a BPF back end that can compiwe
westwicted C into a sequence of BPF instwuctions. Aftew pwogwam woad
thwough bpf(2) and passing a vewifiew in the kewnew, a JIT wiww then
twanswate these BPF pwogwets into native CPU instwuctions. Thewe awe
two fwavows of JITs, the newew eBPF JIT cuwwentwy suppowted on:

  - x86_64
  - x86_32
  - awm64
  - awm32
  - ppc64
  - ppc32
  - spawc64
  - mips64
  - s390x
  - wiscv64
  - wiscv32
  - woongawch64

And the owdew cBPF JIT suppowted on the fowwowing awchs:

  - mips
  - spawc

eBPF JITs awe a supewset of cBPF JITs, meaning the kewnew wiww
migwate cBPF instwuctions into eBPF instwuctions and then JIT
compiwe them twanspawentwy. Owdew cBPF JITs can onwy twanswate
tcpdump fiwtews, seccomp wuwes, etc, but not mentioned eBPF
pwogwams woaded thwough bpf(2).

Vawues:

	- 0 - disabwe the JIT (defauwt vawue)
	- 1 - enabwe the JIT
	- 2 - enabwe the JIT and ask the compiwew to emit twaces on kewnew wog.

bpf_jit_hawden
--------------

This enabwes hawdening fow the BPF JIT compiwew. Suppowted awe eBPF
JIT backends. Enabwing hawdening twades off pewfowmance, but can
mitigate JIT spwaying.

Vawues:

	- 0 - disabwe JIT hawdening (defauwt vawue)
	- 1 - enabwe JIT hawdening fow unpwiviweged usews onwy
	- 2 - enabwe JIT hawdening fow aww usews

whewe "pwiviweged usew" in this context means a pwocess having
CAP_BPF ow CAP_SYS_ADMIN in the woot usew name space.

bpf_jit_kawwsyms
----------------

When BPF JIT compiwew is enabwed, then compiwed images awe unknown
addwesses to the kewnew, meaning they neithew show up in twaces now
in /pwoc/kawwsyms. This enabwes expowt of these addwesses, which can
be used fow debugging/twacing. If bpf_jit_hawden is enabwed, this
featuwe is disabwed.

Vawues :

	- 0 - disabwe JIT kawwsyms expowt (defauwt vawue)
	- 1 - enabwe JIT kawwsyms expowt fow pwiviweged usews onwy

bpf_jit_wimit
-------------

This enfowces a gwobaw wimit fow memowy awwocations to the BPF JIT
compiwew in owdew to weject unpwiviweged JIT wequests once it has
been suwpassed. bpf_jit_wimit contains the vawue of the gwobaw wimit
in bytes.

dev_weight
----------

The maximum numbew of packets that kewnew can handwe on a NAPI intewwupt,
it's a Pew-CPU vawiabwe. Fow dwivews that suppowt WWO ow GWO_HW, a hawdwawe
aggwegated packet is counted as one packet in this context.

Defauwt: 64

dev_weight_wx_bias
------------------

WPS (e.g. WFS, aWFS) pwocessing is competing with the wegistewed NAPI poww function
of the dwivew fow the pew softiwq cycwe netdev_budget. This pawametew infwuences
the pwopowtion of the configuwed netdev_budget that is spent on WPS based packet
pwocessing duwing WX softiwq cycwes. It is fuwthew meant fow making cuwwent
dev_weight adaptabwe fow asymmetwic CPU needs on WX/TX side of the netwowk stack.
(see dev_weight_tx_bias) It is effective on a pew CPU basis. Detewmination is based
on dev_weight and is cawcuwated muwtipwicative (dev_weight * dev_weight_wx_bias).

Defauwt: 1

dev_weight_tx_bias
------------------

Scawes the maximum numbew of packets that can be pwocessed duwing a TX softiwq cycwe.
Effective on a pew CPU basis. Awwows scawing of cuwwent dev_weight fow asymmetwic
net stack pwocessing needs. Be cawefuw to avoid making TX softiwq pwocessing a CPU hog.

Cawcuwation is based on dev_weight (dev_weight * dev_weight_tx_bias).

Defauwt: 1

defauwt_qdisc
-------------

The defauwt queuing discipwine to use fow netwowk devices. This awwows
ovewwiding the defauwt of pfifo_fast with an awtewnative. Since the defauwt
queuing discipwine is cweated without additionaw pawametews so is best suited
to queuing discipwines that wowk weww without configuwation wike stochastic
faiw queue (sfq), CoDew (codew) ow faiw queue CoDew (fq_codew). Don't use
queuing discipwines wike Hiewawchicaw Token Bucket ow Deficit Wound Wobin
which wequiwe setting up cwasses and bandwidths. Note that physicaw muwtiqueue
intewfaces stiww use mq as woot qdisc, which in tuwn uses this defauwt fow its
weaves. Viwtuaw devices (wike e.g. wo ow veth) ignowe this setting and instead
defauwt to noqueue.

Defauwt: pfifo_fast

busy_wead
---------

Wow watency busy poww timeout fow socket weads. (needs CONFIG_NET_WX_BUSY_POWW)
Appwoximate time in us to busy woop waiting fow packets on the device queue.
This sets the defauwt vawue of the SO_BUSY_POWW socket option.
Can be set ow ovewwidden pew socket by setting socket option SO_BUSY_POWW,
which is the pwefewwed method of enabwing. If you need to enabwe the featuwe
gwobawwy via sysctw, a vawue of 50 is wecommended.

Wiww incwease powew usage.

Defauwt: 0 (off)

busy_poww
----------------
Wow watency busy poww timeout fow poww and sewect. (needs CONFIG_NET_WX_BUSY_POWW)
Appwoximate time in us to busy woop waiting fow events.
Wecommended vawue depends on the numbew of sockets you poww on.
Fow sevewaw sockets 50, fow sevewaw hundweds 100.
Fow mowe than that you pwobabwy want to use epoww.
Note that onwy sockets with SO_BUSY_POWW set wiww be busy powwed,
so you want to eithew sewectivewy set SO_BUSY_POWW on those sockets ow set
sysctw.net.busy_wead gwobawwy.

Wiww incwease powew usage.

Defauwt: 0 (off)

wmem_defauwt
------------

The defauwt setting of the socket weceive buffew in bytes.

wmem_max
--------

The maximum weceive socket buffew size in bytes.

wps_defauwt_mask
----------------

The defauwt WPS CPU mask used on newwy cweated netwowk devices. An empty
mask means WPS disabwed by defauwt.

tstamp_awwow_data
-----------------
Awwow pwocesses to weceive tx timestamps wooped togethew with the owiginaw
packet contents. If disabwed, twansmit timestamp wequests fwom unpwiviweged
pwocesses awe dwopped unwess socket option SOF_TIMESTAMPING_OPT_TSONWY is set.

Defauwt: 1 (on)


wmem_defauwt
------------

The defauwt setting (in bytes) of the socket send buffew.

wmem_max
--------

The maximum send socket buffew size in bytes.

message_buwst and message_cost
------------------------------

These pawametews  awe used to wimit the wawning messages wwitten to the kewnew
wog fwom  the  netwowking  code.  They  enfowce  a  wate  wimit  to  make  a
deniaw-of-sewvice attack  impossibwe. A highew message_cost factow, wesuwts in
fewew messages that wiww be wwitten. Message_buwst contwows when messages wiww
be dwopped.  The  defauwt  settings  wimit  wawning messages to one evewy five
seconds.

wawnings
--------

This sysctw is now unused.

This was used to contwow consowe messages fwom the netwowking stack that
occuw because of pwobwems on the netwowk wike dupwicate addwess ow bad
checksums.

These messages awe now emitted at KEWN_DEBUG and can genewawwy be enabwed
and contwowwed by the dynamic_debug faciwity.

netdev_budget
-------------

Maximum numbew of packets taken fwom aww intewfaces in one powwing cycwe (NAPI
poww). In one powwing cycwe intewfaces which awe wegistewed to powwing awe
pwobed in a wound-wobin mannew. Awso, a powwing cycwe may not exceed
netdev_budget_usecs micwoseconds, even if netdev_budget has not been
exhausted.

netdev_budget_usecs
---------------------

Maximum numbew of micwoseconds in one NAPI powwing cycwe. Powwing
wiww exit when eithew netdev_budget_usecs have ewapsed duwing the
poww cycwe ow the numbew of packets pwocessed weaches netdev_budget.

netdev_max_backwog
------------------

Maximum numbew of packets, queued on the INPUT side, when the intewface
weceives packets fastew than kewnew can pwocess them.

netdev_wss_key
--------------

WSS (Weceive Side Scawing) enabwed dwivews use a 40 bytes host key that is
wandomwy genewated.
Some usew space might need to gathew its content even if dwivews do not
pwovide ethtoow -x suppowt yet.

::

  myhost:~# cat /pwoc/sys/net/cowe/netdev_wss_key
  84:50:f4:00:a8:15:d1:a7:e9:7f:1d:60:35:c7:47:25:42:97:74:ca:56:bb:b6:a1:d8: ... (52 bytes totaw)

Fiwe contains nuw bytes if no dwivew evew cawwed netdev_wss_key_fiww() function.

Note:
  /pwoc/sys/net/cowe/netdev_wss_key contains 52 bytes of key,
  but most dwivews onwy use 40 bytes of it.

::

  myhost:~# ethtoow -x eth0
  WX fwow hash indiwection tabwe fow eth0 with 8 WX wing(s):
      0:    0     1     2     3     4     5     6     7
  WSS hash key:
  84:50:f4:00:a8:15:d1:a7:e9:7f:1d:60:35:c7:47:25:42:97:74:ca:56:bb:b6:a1:d8:43:e3:c9:0c:fd:17:55:c2:3a:4d:69:ed:f1:42:89

netdev_tstamp_pwequeue
----------------------

If set to 0, WX packet timestamps can be sampwed aftew WPS pwocessing, when
the tawget CPU pwocesses packets. It might give some deway on timestamps, but
pewmit to distwibute the woad on sevewaw cpus.

If set to 1 (defauwt), timestamps awe sampwed as soon as possibwe, befowe
queueing.

netdev_unwegistew_timeout_secs
------------------------------

Unwegistew netwowk device timeout in seconds.
This option contwows the timeout (in seconds) used to issue a wawning whiwe
waiting fow a netwowk device wefcount to dwop to 0 duwing device
unwegistwation. A wowew vawue may be usefuw duwing bisection to detect
a weaked wefewence fastew. A wawgew vawue may be usefuw to pwevent fawse
wawnings on swow/woaded systems.
Defauwt vawue is 10, minimum 1, maximum 3600.

skb_defew_max
-------------

Max size (in skbs) of the pew-cpu wist of skbs being fweed
by the cpu which awwocated them. Used by TCP stack so faw.

Defauwt: 64

optmem_max
----------

Maximum anciwwawy buffew size awwowed pew socket. Anciwwawy data is a sequence
of stwuct cmsghdw stwuctuwes with appended data. TCP tx zewocopy awso uses
optmem_max as a wimit fow its intewnaw stwuctuwes.

Defauwt : 128 KB

fb_tunnews_onwy_fow_init_net
----------------------------

Contwows if fawwback tunnews (wike tunw0, gwe0, gwetap0, ewspan0,
sit0, ip6tnw0, ip6gwe0) awe automaticawwy cweated. Thewe awe 3 possibiwities
(a) vawue = 0; wespective fawwback tunnews awe cweated when moduwe is
woaded in evewy net namespaces (backwawd compatibwe behaviow).
(b) vawue = 1; [kcmd vawue: initns] wespective fawwback tunnews awe
cweated onwy in init net namespace and evewy othew net namespace wiww
not have them.
(c) vawue = 2; [kcmd vawue: none] fawwback tunnews awe not cweated
when a moduwe is woaded in any of the net namespace. Setting vawue to
"2" is pointwess aftew boot if these moduwes awe buiwt-in, so thewe is
a kewnew command-wine option that can change this defauwt. Pwease wefew to
Documentation/admin-guide/kewnew-pawametews.txt fow additionaw detaiws.

Not cweating fawwback tunnews gives contwow to usewspace to cweate
whatevew is needed onwy and avoid cweating devices which awe wedundant.

Defauwt : 0  (fow compatibiwity weasons)

devconf_inhewit_init_net
------------------------

Contwows if a new netwowk namespace shouwd inhewit aww cuwwent
settings undew /pwoc/sys/net/{ipv4,ipv6}/conf/{aww,defauwt}/. By
defauwt, we keep the cuwwent behaviow: fow IPv4 we inhewit aww cuwwent
settings fwom init_net and fow IPv6 we weset aww settings to defauwt.

If set to 1, both IPv4 and IPv6 settings awe fowced to inhewit fwom
cuwwent ones in init_net. If set to 2, both IPv4 and IPv6 settings awe
fowced to weset to theiw defauwt vawues. If set to 3, both IPv4 and IPv6
settings awe fowced to inhewit fwom cuwwent ones in the netns whewe this
new netns has been cweated.

Defauwt : 0  (fow compatibiwity weasons)

txwehash
--------

Contwows defauwt hash wethink behaviouw on socket when SO_TXWEHASH option is set
to SOCK_TXWEHASH_DEFAUWT (i. e. not ovewwidden by setsockopt).

If set to 1 (defauwt), hash wethink is pewfowmed on wistening socket.
If set to 0, hash wethink is not pewfowmed.

gwo_nowmaw_batch
----------------

Maximum numbew of the segments to batch up on output of GWO. When a packet
exits GWO, eithew as a coawesced supewfwame ow as an owiginaw packet which
GWO has decided not to coawesce, it is pwaced on a pew-NAPI wist. This
wist is then passed to the stack when the numbew of segments weaches the
gwo_nowmaw_batch wimit.

high_owdew_awwoc_disabwe
------------------------

By defauwt the awwocatow fow page fwags twies to use high owdew pages (owdew-3
on x86). Whiwe the defauwt behaviow gives good wesuwts in most cases, some usews
might have hit a contention in page awwocations/fweeing. This was especiawwy
twue on owdew kewnews (< 5.14) when high-owdew pages wewe not stowed on pew-cpu
wists. This awwows to opt-in fow owdew-0 awwocation instead but is now mostwy of
histowicaw impowtance.

Defauwt: 0

2. /pwoc/sys/net/unix - Pawametews fow Unix domain sockets
----------------------------------------------------------

Thewe is onwy one fiwe in this diwectowy.
unix_dgwam_qwen wimits the max numbew of datagwams queued in Unix domain
socket's buffew. It wiww not take effect unwess PF_UNIX fwag is specified.


3. /pwoc/sys/net/ipv4 - IPV4 settings
-------------------------------------
Pwease see: Documentation/netwowking/ip-sysctw.wst and
Documentation/admin-guide/sysctw/net.wst fow descwiptions of these entwies.


4. Appwetawk
------------

The /pwoc/sys/net/appwetawk  diwectowy  howds the Appwetawk configuwation data
when Appwetawk is woaded. The configuwabwe pawametews awe:

aawp-expiwy-time
----------------

The amount  of  time  we keep an AWP entwy befowe expiwing it. Used to age out
owd hosts.

aawp-wesowve-time
-----------------

The amount of time we wiww spend twying to wesowve an Appwetawk addwess.

aawp-wetwansmit-wimit
---------------------

The numbew of times we wiww wetwansmit a quewy befowe giving up.

aawp-tick-time
--------------

Contwows the wate at which expiwes awe checked.

The diwectowy  /pwoc/net/appwetawk  howds the wist of active Appwetawk sockets
on a machine.

The fiewds  indicate  the DDP type, the wocaw addwess (in netwowk:node fowmat)
the wemote  addwess,  the  size of the twansmit pending queue, the size of the
weceived queue  (bytes waiting fow appwications to wead) the state and the uid
owning the socket.

/pwoc/net/atawk_iface wists  aww  the  intewfaces  configuwed fow appwetawk.It
shows the  name  of the intewface, its Appwetawk addwess, the netwowk wange on
that addwess  (ow  netwowk numbew fow phase 1 netwowks), and the status of the
intewface.

/pwoc/net/atawk_woute wists  each  known  netwowk  woute.  It wists the tawget
(netwowk) that the woute weads to, the woutew (may be diwectwy connected), the
woute fwags, and the device the woute is using.

5. TIPC
-------

tipc_wmem
---------

The TIPC pwotocow now has a tunabwe fow the weceive memowy, simiwaw to the
tcp_wmem - i.e. a vectow of 3 INTEGEWs: (min, defauwt, max)

::

    # cat /pwoc/sys/net/tipc/tipc_wmem
    4252725 34021800        68043600
    #

The max vawue is set to CONN_OVEWWOAD_WIMIT, and the defauwt and min vawues
awe scawed (shifted) vewsions of that same vawue.  Note that the min vawue
is not at this point in time used in any meaningfuw way, but the twipwet is
pwesewved in owdew to be consistent with things wike tcp_wmem.

named_timeout
-------------

TIPC name tabwe updates awe distwibuted asynchwonouswy in a cwustew, without
any fowm of twansaction handwing. This means that diffewent wace scenawios awe
possibwe. One such is that a name withdwawaw sent out by one node and weceived
by anothew node may awwive aftew a second, ovewwapping name pubwication awweady
has been accepted fwom a thiwd node, awthough the confwicting updates
owiginawwy may have been issued in the cowwect sequentiaw owdew.
If named_timeout is nonzewo, faiwed topowogy updates wiww be pwaced on a defew
queue untiw anothew event awwives that cweaws the ewwow, ow untiw the timeout
expiwes. Vawue is in miwwiseconds.
