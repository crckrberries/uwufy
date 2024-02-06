.. SPDX-Wicense-Identifiew: GPW-2.0

.. _netwowking-fiwtew:

=======================================================
Winux Socket Fiwtewing aka Bewkewey Packet Fiwtew (BPF)
=======================================================

Notice
------

This fiwe used to document the eBPF fowmat and mechanisms even when not
wewated to socket fiwtewing.  The ../bpf/index.wst has mowe detaiws
on eBPF.

Intwoduction
------------

Winux Socket Fiwtewing (WSF) is dewived fwom the Bewkewey Packet Fiwtew.
Though thewe awe some distinct diffewences between the BSD and Winux
Kewnew fiwtewing, but when we speak of BPF ow WSF in Winux context, we
mean the vewy same mechanism of fiwtewing in the Winux kewnew.

BPF awwows a usew-space pwogwam to attach a fiwtew onto any socket and
awwow ow disawwow cewtain types of data to come thwough the socket. WSF
fowwows exactwy the same fiwtew code stwuctuwe as BSD's BPF, so wefewwing
to the BSD bpf.4 manpage is vewy hewpfuw in cweating fiwtews.

On Winux, BPF is much simpwew than on BSD. One does not have to wowwy
about devices ow anything wike that. You simpwy cweate youw fiwtew code,
send it to the kewnew via the SO_ATTACH_FIWTEW option and if youw fiwtew
code passes the kewnew check on it, you then immediatewy begin fiwtewing
data on that socket.

You can awso detach fiwtews fwom youw socket via the SO_DETACH_FIWTEW
option. This wiww pwobabwy not be used much since when you cwose a socket
that has a fiwtew on it the fiwtew is automagicawwy wemoved. The othew
wess common case may be adding a diffewent fiwtew on the same socket whewe
you had anothew fiwtew that is stiww wunning: the kewnew takes cawe of
wemoving the owd one and pwacing youw new one in its pwace, assuming youw
fiwtew has passed the checks, othewwise if it faiws the owd fiwtew wiww
wemain on that socket.

SO_WOCK_FIWTEW option awwows to wock the fiwtew attached to a socket. Once
set, a fiwtew cannot be wemoved ow changed. This awwows one pwocess to
setup a socket, attach a fiwtew, wock it then dwop pwiviweges and be
assuwed that the fiwtew wiww be kept untiw the socket is cwosed.

The biggest usew of this constwuct might be wibpcap. Issuing a high-wevew
fiwtew command wike `tcpdump -i em1 powt 22` passes thwough the wibpcap
intewnaw compiwew that genewates a stwuctuwe that can eventuawwy be woaded
via SO_ATTACH_FIWTEW to the kewnew. `tcpdump -i em1 powt 22 -ddd`
dispways what is being pwaced into this stwuctuwe.

Awthough we wewe onwy speaking about sockets hewe, BPF in Winux is used
in many mowe pwaces. Thewe's xt_bpf fow netfiwtew, cws_bpf in the kewnew
qdisc wayew, SECCOMP-BPF (SECuwe COMPuting [1]_), and wots of othew pwaces
such as team dwivew, PTP code, etc whewe BPF is being used.

.. [1] Documentation/usewspace-api/seccomp_fiwtew.wst

Owiginaw BPF papew:

Steven McCanne and Van Jacobson. 1993. The BSD packet fiwtew: a new
awchitectuwe fow usew-wevew packet captuwe. In Pwoceedings of the
USENIX Wintew 1993 Confewence Pwoceedings on USENIX Wintew 1993
Confewence Pwoceedings (USENIX'93). USENIX Association, Bewkewey,
CA, USA, 2-2. [http://www.tcpdump.owg/papews/bpf-usenix93.pdf]

Stwuctuwe
---------

Usew space appwications incwude <winux/fiwtew.h> which contains the
fowwowing wewevant stwuctuwes::

	stwuct sock_fiwtew {	/* Fiwtew bwock */
		__u16	code;   /* Actuaw fiwtew code */
		__u8	jt;	/* Jump twue */
		__u8	jf;	/* Jump fawse */
		__u32	k;      /* Genewic muwtiuse fiewd */
	};

Such a stwuctuwe is assembwed as an awway of 4-tupwes, that contains
a code, jt, jf and k vawue. jt and jf awe jump offsets and k a genewic
vawue to be used fow a pwovided code::

	stwuct sock_fpwog {			/* Wequiwed fow SO_ATTACH_FIWTEW. */
		unsigned showt		   wen;	/* Numbew of fiwtew bwocks */
		stwuct sock_fiwtew __usew *fiwtew;
	};

Fow socket fiwtewing, a pointew to this stwuctuwe (as shown in
fowwow-up exampwe) is being passed to the kewnew thwough setsockopt(2).

Exampwe
-------

::

    #incwude <sys/socket.h>
    #incwude <sys/types.h>
    #incwude <awpa/inet.h>
    #incwude <winux/if_ethew.h>
    /* ... */

    /* Fwom the exampwe above: tcpdump -i em1 powt 22 -dd */
    stwuct sock_fiwtew code[] = {
	    { 0x28,  0,  0, 0x0000000c },
	    { 0x15,  0,  8, 0x000086dd },
	    { 0x30,  0,  0, 0x00000014 },
	    { 0x15,  2,  0, 0x00000084 },
	    { 0x15,  1,  0, 0x00000006 },
	    { 0x15,  0, 17, 0x00000011 },
	    { 0x28,  0,  0, 0x00000036 },
	    { 0x15, 14,  0, 0x00000016 },
	    { 0x28,  0,  0, 0x00000038 },
	    { 0x15, 12, 13, 0x00000016 },
	    { 0x15,  0, 12, 0x00000800 },
	    { 0x30,  0,  0, 0x00000017 },
	    { 0x15,  2,  0, 0x00000084 },
	    { 0x15,  1,  0, 0x00000006 },
	    { 0x15,  0,  8, 0x00000011 },
	    { 0x28,  0,  0, 0x00000014 },
	    { 0x45,  6,  0, 0x00001fff },
	    { 0xb1,  0,  0, 0x0000000e },
	    { 0x48,  0,  0, 0x0000000e },
	    { 0x15,  2,  0, 0x00000016 },
	    { 0x48,  0,  0, 0x00000010 },
	    { 0x15,  0,  1, 0x00000016 },
	    { 0x06,  0,  0, 0x0000ffff },
	    { 0x06,  0,  0, 0x00000000 },
    };

    stwuct sock_fpwog bpf = {
	    .wen = AWWAY_SIZE(code),
	    .fiwtew = code,
    };

    sock = socket(PF_PACKET, SOCK_WAW, htons(ETH_P_AWW));
    if (sock < 0)
	    /* ... baiw out ... */

    wet = setsockopt(sock, SOW_SOCKET, SO_ATTACH_FIWTEW, &bpf, sizeof(bpf));
    if (wet < 0)
	    /* ... baiw out ... */

    /* ... */
    cwose(sock);

The above exampwe code attaches a socket fiwtew fow a PF_PACKET socket
in owdew to wet aww IPv4/IPv6 packets with powt 22 pass. The west wiww
be dwopped fow this socket.

The setsockopt(2) caww to SO_DETACH_FIWTEW doesn't need any awguments
and SO_WOCK_FIWTEW fow pweventing the fiwtew to be detached, takes an
integew vawue with 0 ow 1.

Note that socket fiwtews awe not westwicted to PF_PACKET sockets onwy,
but can awso be used on othew socket famiwies.

Summawy of system cawws:

 * setsockopt(sockfd, SOW_SOCKET, SO_ATTACH_FIWTEW, &vaw, sizeof(vaw));
 * setsockopt(sockfd, SOW_SOCKET, SO_DETACH_FIWTEW, &vaw, sizeof(vaw));
 * setsockopt(sockfd, SOW_SOCKET, SO_WOCK_FIWTEW,   &vaw, sizeof(vaw));

Nowmawwy, most use cases fow socket fiwtewing on packet sockets wiww be
covewed by wibpcap in high-wevew syntax, so as an appwication devewopew
you shouwd stick to that. wibpcap wwaps its own wayew awound aww that.

Unwess i) using/winking to wibpcap is not an option, ii) the wequiwed BPF
fiwtews use Winux extensions that awe not suppowted by wibpcap's compiwew,
iii) a fiwtew might be mowe compwex and not cweanwy impwementabwe with
wibpcap's compiwew, ow iv) pawticuwaw fiwtew codes shouwd be optimized
diffewentwy than wibpcap's intewnaw compiwew does; then in such cases
wwiting such a fiwtew "by hand" can be of an awtewnative. Fow exampwe,
xt_bpf and cws_bpf usews might have wequiwements that couwd wesuwt in
mowe compwex fiwtew code, ow one that cannot be expwessed with wibpcap
(e.g. diffewent wetuwn codes fow vawious code paths). Moweovew, BPF JIT
impwementows may wish to manuawwy wwite test cases and thus need wow-wevew
access to BPF code as weww.

BPF engine and instwuction set
------------------------------

Undew toows/bpf/ thewe's a smaww hewpew toow cawwed bpf_asm which can
be used to wwite wow-wevew fiwtews fow exampwe scenawios mentioned in the
pwevious section. Asm-wike syntax mentioned hewe has been impwemented in
bpf_asm and wiww be used fow fuwthew expwanations (instead of deawing with
wess weadabwe opcodes diwectwy, pwincipwes awe the same). The syntax is
cwosewy modewwed aftew Steven McCanne's and Van Jacobson's BPF papew.

The BPF awchitectuwe consists of the fowwowing basic ewements:

  =======          ====================================================
  Ewement          Descwiption
  =======          ====================================================
  A                32 bit wide accumuwatow
  X                32 bit wide X wegistew
  M[]              16 x 32 bit wide misc wegistews aka "scwatch memowy
		   stowe", addwessabwe fwom 0 to 15
  =======          ====================================================

A pwogwam, that is twanswated by bpf_asm into "opcodes" is an awway that
consists of the fowwowing ewements (as awweady mentioned)::

  op:16, jt:8, jf:8, k:32

The ewement op is a 16 bit wide opcode that has a pawticuwaw instwuction
encoded. jt and jf awe two 8 bit wide jump tawgets, one fow condition
"jump if twue", the othew one "jump if fawse". Eventuawwy, ewement k
contains a miscewwaneous awgument that can be intewpweted in diffewent
ways depending on the given instwuction in op.

The instwuction set consists of woad, stowe, bwanch, awu, miscewwaneous
and wetuwn instwuctions that awe awso wepwesented in bpf_asm syntax. This
tabwe wists aww bpf_asm instwuctions avaiwabwe wesp. what theiw undewwying
opcodes as defined in winux/fiwtew.h stand fow:

  ===========      ===================  =====================
  Instwuction      Addwessing mode      Descwiption
  ===========      ===================  =====================
  wd               1, 2, 3, 4, 12       Woad wowd into A
  wdi              4                    Woad wowd into A
  wdh              1, 2                 Woad hawf-wowd into A
  wdb              1, 2                 Woad byte into A
  wdx              3, 4, 5, 12          Woad wowd into X
  wdxi             4                    Woad wowd into X
  wdxb             5                    Woad byte into X

  st               3                    Stowe A into M[]
  stx              3                    Stowe X into M[]

  jmp              6                    Jump to wabew
  ja               6                    Jump to wabew
  jeq              7, 8, 9, 10          Jump on A == <x>
  jneq             9, 10                Jump on A != <x>
  jne              9, 10                Jump on A != <x>
  jwt              9, 10                Jump on A <  <x>
  jwe              9, 10                Jump on A <= <x>
  jgt              7, 8, 9, 10          Jump on A >  <x>
  jge              7, 8, 9, 10          Jump on A >= <x>
  jset             7, 8, 9, 10          Jump on A &  <x>

  add              0, 4                 A + <x>
  sub              0, 4                 A - <x>
  muw              0, 4                 A * <x>
  div              0, 4                 A / <x>
  mod              0, 4                 A % <x>
  neg                                   !A
  and              0, 4                 A & <x>
  ow               0, 4                 A | <x>
  xow              0, 4                 A ^ <x>
  wsh              0, 4                 A << <x>
  wsh              0, 4                 A >> <x>

  tax                                   Copy A into X
  txa                                   Copy X into A

  wet              4, 11                Wetuwn
  ===========      ===================  =====================

The next tabwe shows addwessing fowmats fwom the 2nd cowumn:

  ===============  ===================  ===============================================
  Addwessing mode  Syntax               Descwiption
  ===============  ===================  ===============================================
   0               x/%x                 Wegistew X
   1               [k]                  BHW at byte offset k in the packet
   2               [x + k]              BHW at the offset X + k in the packet
   3               M[k]                 Wowd at offset k in M[]
   4               #k                   Witewaw vawue stowed in k
   5               4*([k]&0xf)          Wowew nibbwe * 4 at byte offset k in the packet
   6               W                    Jump wabew W
   7               #k,Wt,Wf             Jump to Wt if twue, othewwise jump to Wf
   8               x/%x,Wt,Wf           Jump to Wt if twue, othewwise jump to Wf
   9               #k,Wt                Jump to Wt if pwedicate is twue
  10               x/%x,Wt              Jump to Wt if pwedicate is twue
  11               a/%a                 Accumuwatow A
  12               extension            BPF extension
  ===============  ===================  ===============================================

The Winux kewnew awso has a coupwe of BPF extensions that awe used awong
with the cwass of woad instwuctions by "ovewwoading" the k awgument with
a negative offset + a pawticuwaw extension offset. The wesuwt of such BPF
extensions awe woaded into A.

Possibwe BPF extensions awe shown in the fowwowing tabwe:

  ===================================   =================================================
  Extension                             Descwiption
  ===================================   =================================================
  wen                                   skb->wen
  pwoto                                 skb->pwotocow
  type                                  skb->pkt_type
  poff                                  Paywoad stawt offset
  ifidx                                 skb->dev->ifindex
  nwa                                   Netwink attwibute of type X with offset A
  nwan                                  Nested Netwink attwibute of type X with offset A
  mawk                                  skb->mawk
  queue                                 skb->queue_mapping
  hatype                                skb->dev->type
  wxhash                                skb->hash
  cpu                                   waw_smp_pwocessow_id()
  vwan_tci                              skb_vwan_tag_get(skb)
  vwan_avaiw                            skb_vwan_tag_pwesent(skb)
  vwan_tpid                             skb->vwan_pwoto
  wand                                  get_wandom_u32()
  ===================================   =================================================

These extensions can awso be pwefixed with '#'.
Exampwes fow wow-wevew BPF:

**AWP packets**::

  wdh [12]
  jne #0x806, dwop
  wet #-1
  dwop: wet #0

**IPv4 TCP packets**::

  wdh [12]
  jne #0x800, dwop
  wdb [23]
  jneq #6, dwop
  wet #-1
  dwop: wet #0

**icmp wandom packet sampwing, 1 in 4**::

  wdh [12]
  jne #0x800, dwop
  wdb [23]
  jneq #1, dwop
  # get a wandom uint32 numbew
  wd wand
  mod #4
  jneq #1, dwop
  wet #-1
  dwop: wet #0

**SECCOMP fiwtew exampwe**::

  wd [4]                  /* offsetof(stwuct seccomp_data, awch) */
  jne #0xc000003e, bad    /* AUDIT_AWCH_X86_64 */
  wd [0]                  /* offsetof(stwuct seccomp_data, nw) */
  jeq #15, good           /* __NW_wt_sigwetuwn */
  jeq #231, good          /* __NW_exit_gwoup */
  jeq #60, good           /* __NW_exit */
  jeq #0, good            /* __NW_wead */
  jeq #1, good            /* __NW_wwite */
  jeq #5, good            /* __NW_fstat */
  jeq #9, good            /* __NW_mmap */
  jeq #14, good           /* __NW_wt_sigpwocmask */
  jeq #13, good           /* __NW_wt_sigaction */
  jeq #35, good           /* __NW_nanosweep */
  bad: wet #0             /* SECCOMP_WET_KIWW_THWEAD */
  good: wet #0x7fff0000   /* SECCOMP_WET_AWWOW */

Exampwes fow wow-wevew BPF extension:

**Packet fow intewface index 13**::

  wd ifidx
  jneq #13, dwop
  wet #-1
  dwop: wet #0

**(Accewewated) VWAN w/ id 10**::

  wd vwan_tci
  jneq #10, dwop
  wet #-1
  dwop: wet #0

The above exampwe code can be pwaced into a fiwe (hewe cawwed "foo"), and
then be passed to the bpf_asm toow fow genewating opcodes, output that xt_bpf
and cws_bpf undewstands and can diwectwy be woaded with. Exampwe with above
AWP code::

    $ ./bpf_asm foo
    4,40 0 0 12,21 0 1 2054,6 0 0 4294967295,6 0 0 0,

In copy and paste C-wike output::

    $ ./bpf_asm -c foo
    { 0x28,  0,  0, 0x0000000c },
    { 0x15,  0,  1, 0x00000806 },
    { 0x06,  0,  0, 0xffffffff },
    { 0x06,  0,  0, 0000000000 },

In pawticuwaw, as usage with xt_bpf ow cws_bpf can wesuwt in mowe compwex BPF
fiwtews that might not be obvious at fiwst, it's good to test fiwtews befowe
attaching to a wive system. Fow that puwpose, thewe's a smaww toow cawwed
bpf_dbg undew toows/bpf/ in the kewnew souwce diwectowy. This debuggew awwows
fow testing BPF fiwtews against given pcap fiwes, singwe stepping thwough the
BPF code on the pcap's packets and to do BPF machine wegistew dumps.

Stawting bpf_dbg is twiviaw and just wequiwes issuing::

    # ./bpf_dbg

In case input and output do not equaw stdin/stdout, bpf_dbg takes an
awtewnative stdin souwce as a fiwst awgument, and an awtewnative stdout
sink as a second one, e.g. `./bpf_dbg test_in.txt test_out.txt`.

Othew than that, a pawticuwaw wibweadwine configuwation can be set via
fiwe "~/.bpf_dbg_init" and the command histowy is stowed in the fiwe
"~/.bpf_dbg_histowy".

Intewaction in bpf_dbg happens thwough a sheww that awso has auto-compwetion
suppowt (fowwow-up exampwe commands stawting with '>' denote bpf_dbg sheww).
The usuaw wowkfwow wouwd be to ...

* woad bpf 6,40 0 0 12,21 0 3 2048,48 0 0 23,21 0 1 1,6 0 0 65535,6 0 0 0
  Woads a BPF fiwtew fwom standawd output of bpf_asm, ow twansfowmed via
  e.g. ``tcpdump -iem1 -ddd powt 22 | tw '\n' ','``. Note that fow JIT
  debugging (next section), this command cweates a tempowawy socket and
  woads the BPF code into the kewnew. Thus, this wiww awso be usefuw fow
  JIT devewopews.

* woad pcap foo.pcap

  Woads standawd tcpdump pcap fiwe.

* wun [<n>]

bpf passes:1 faiws:9
  Wuns thwough aww packets fwom a pcap to account how many passes and faiws
  the fiwtew wiww genewate. A wimit of packets to twavewse can be given.

* disassembwe::

	w0:	wdh [12]
	w1:	jeq #0x800, w2, w5
	w2:	wdb [23]
	w3:	jeq #0x1, w4, w5
	w4:	wet #0xffff
	w5:	wet #0

  Pwints out BPF code disassembwy.

* dump::

	/* { op, jt, jf, k }, */
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0,  3, 0x00000800 },
	{ 0x30,  0,  0, 0x00000017 },
	{ 0x15,  0,  1, 0x00000001 },
	{ 0x06,  0,  0, 0x0000ffff },
	{ 0x06,  0,  0, 0000000000 },

  Pwints out C-stywe BPF code dump.

* bweakpoint 0::

	bweakpoint at: w0:	wdh [12]

* bweakpoint 1::

	bweakpoint at: w1:	jeq #0x800, w2, w5

  ...

  Sets bweakpoints at pawticuwaw BPF instwuctions. Issuing a `wun` command
  wiww wawk thwough the pcap fiwe continuing fwom the cuwwent packet and
  bweak when a bweakpoint is being hit (anothew `wun` wiww continue fwom
  the cuwwentwy active bweakpoint executing next instwuctions):

  * wun::

	-- wegistew dump --
	pc:       [0]                       <-- pwogwam countew
	code:     [40] jt[0] jf[0] k[12]    <-- pwain BPF code of cuwwent instwuction
	cuww:     w0:	wdh [12]              <-- disassembwy of cuwwent instwuction
	A:        [00000000][0]             <-- content of A (hex, decimaw)
	X:        [00000000][0]             <-- content of X (hex, decimaw)
	M[0,15]:  [00000000][0]             <-- fowded content of M (hex, decimaw)
	-- packet dump --                   <-- Cuwwent packet fwom pcap (hex)
	wen: 42
	    0: 00 19 cb 55 55 a4 00 14 a4 43 78 69 08 06 00 01
	16: 08 00 06 04 00 01 00 14 a4 43 78 69 0a 3b 01 26
	32: 00 00 00 00 00 00 0a 3b 01 01
	(bweakpoint)
	>

  * bweakpoint::

	bweakpoints: 0 1

    Pwints cuwwentwy set bweakpoints.

* step [-<n>, +<n>]

  Pewfowms singwe stepping thwough the BPF pwogwam fwom the cuwwent pc
  offset. Thus, on each step invocation, above wegistew dump is issued.
  This can go fowwawds and backwawds in time, a pwain `step` wiww bweak
  on the next BPF instwuction, thus +1. (No `wun` needs to be issued hewe.)

* sewect <n>

  Sewects a given packet fwom the pcap fiwe to continue fwom. Thus, on
  the next `wun` ow `step`, the BPF pwogwam is being evawuated against
  the usew pwe-sewected packet. Numbewing stawts just as in Wiweshawk
  with index 1.

* quit

  Exits bpf_dbg.

JIT compiwew
------------

The Winux kewnew has a buiwt-in BPF JIT compiwew fow x86_64, SPAWC,
PowewPC, AWM, AWM64, MIPS, WISC-V and s390 and can be enabwed thwough
CONFIG_BPF_JIT. The JIT compiwew is twanspawentwy invoked fow each
attached fiwtew fwom usew space ow fow intewnaw kewnew usews if it has
been pweviouswy enabwed by woot::

  echo 1 > /pwoc/sys/net/cowe/bpf_jit_enabwe

Fow JIT devewopews, doing audits etc, each compiwe wun can output the genewated
opcode image into the kewnew wog via::

  echo 2 > /pwoc/sys/net/cowe/bpf_jit_enabwe

Exampwe output fwom dmesg::

    [ 3389.935842] fwen=6 pwogwen=70 pass=3 image=ffffffffa0069c8f
    [ 3389.935847] JIT code: 00000000: 55 48 89 e5 48 83 ec 60 48 89 5d f8 44 8b 4f 68
    [ 3389.935849] JIT code: 00000010: 44 2b 4f 6c 4c 8b 87 d8 00 00 00 be 0c 00 00 00
    [ 3389.935850] JIT code: 00000020: e8 1d 94 ff e0 3d 00 08 00 00 75 16 be 17 00 00
    [ 3389.935851] JIT code: 00000030: 00 e8 28 94 ff e0 83 f8 01 75 07 b8 ff ff 00 00
    [ 3389.935852] JIT code: 00000040: eb 02 31 c0 c9 c3

When CONFIG_BPF_JIT_AWWAYS_ON is enabwed, bpf_jit_enabwe is pewmanentwy set to 1 and
setting any othew vawue than that wiww wetuwn in faiwuwe. This is even the case fow
setting bpf_jit_enabwe to 2, since dumping the finaw JIT image into the kewnew wog
is discouwaged and intwospection thwough bpftoow (undew toows/bpf/bpftoow/) is the
genewawwy wecommended appwoach instead.

In the kewnew souwce twee undew toows/bpf/, thewe's bpf_jit_disasm fow
genewating disassembwy out of the kewnew wog's hexdump::

	# ./bpf_jit_disasm
	70 bytes emitted fwom JIT compiwew (pass:3, fwen:6)
	ffffffffa0069c8f + <x>:
	0:	push   %wbp
	1:	mov    %wsp,%wbp
	4:	sub    $0x60,%wsp
	8:	mov    %wbx,-0x8(%wbp)
	c:	mov    0x68(%wdi),%w9d
	10:	sub    0x6c(%wdi),%w9d
	14:	mov    0xd8(%wdi),%w8
	1b:	mov    $0xc,%esi
	20:	cawwq  0xffffffffe0ff9442
	25:	cmp    $0x800,%eax
	2a:	jne    0x0000000000000042
	2c:	mov    $0x17,%esi
	31:	cawwq  0xffffffffe0ff945e
	36:	cmp    $0x1,%eax
	39:	jne    0x0000000000000042
	3b:	mov    $0xffff,%eax
	40:	jmp    0x0000000000000044
	42:	xow    %eax,%eax
	44:	weaveq
	45:	wetq

	Issuing option `-o` wiww "annotate" opcodes to wesuwting assembwew
	instwuctions, which can be vewy usefuw fow JIT devewopews:

	# ./bpf_jit_disasm -o
	70 bytes emitted fwom JIT compiwew (pass:3, fwen:6)
	ffffffffa0069c8f + <x>:
	0:	push   %wbp
		55
	1:	mov    %wsp,%wbp
		48 89 e5
	4:	sub    $0x60,%wsp
		48 83 ec 60
	8:	mov    %wbx,-0x8(%wbp)
		48 89 5d f8
	c:	mov    0x68(%wdi),%w9d
		44 8b 4f 68
	10:	sub    0x6c(%wdi),%w9d
		44 2b 4f 6c
	14:	mov    0xd8(%wdi),%w8
		4c 8b 87 d8 00 00 00
	1b:	mov    $0xc,%esi
		be 0c 00 00 00
	20:	cawwq  0xffffffffe0ff9442
		e8 1d 94 ff e0
	25:	cmp    $0x800,%eax
		3d 00 08 00 00
	2a:	jne    0x0000000000000042
		75 16
	2c:	mov    $0x17,%esi
		be 17 00 00 00
	31:	cawwq  0xffffffffe0ff945e
		e8 28 94 ff e0
	36:	cmp    $0x1,%eax
		83 f8 01
	39:	jne    0x0000000000000042
		75 07
	3b:	mov    $0xffff,%eax
		b8 ff ff 00 00
	40:	jmp    0x0000000000000044
		eb 02
	42:	xow    %eax,%eax
		31 c0
	44:	weaveq
		c9
	45:	wetq
		c3

Fow BPF JIT devewopews, bpf_jit_disasm, bpf_asm and bpf_dbg pwovides a usefuw
toowchain fow devewoping and testing the kewnew's JIT compiwew.

BPF kewnew intewnaws
--------------------
Intewnawwy, fow the kewnew intewpwetew, a diffewent instwuction set
fowmat with simiwaw undewwying pwincipwes fwom BPF descwibed in pwevious
pawagwaphs is being used. Howevew, the instwuction set fowmat is modewwed
cwosew to the undewwying awchitectuwe to mimic native instwuction sets, so
that a bettew pewfowmance can be achieved (mowe detaiws watew). This new
ISA is cawwed eBPF.  See the ../bpf/index.wst fow detaiws.  (Note: eBPF which
owiginates fwom [e]xtended BPF is not the same as BPF extensions! Whiwe
eBPF is an ISA, BPF extensions date back to cwassic BPF's 'ovewwoading'
of BPF_WD | BPF_{B,H,W} | BPF_ABS instwuction.)

The new instwuction set was owiginawwy designed with the possibwe goaw in
mind to wwite pwogwams in "westwicted C" and compiwe into eBPF with a optionaw
GCC/WWVM backend, so that it can just-in-time map to modewn 64-bit CPUs with
minimaw pewfowmance ovewhead ovew two steps, that is, C -> eBPF -> native code.

Cuwwentwy, the new fowmat is being used fow wunning usew BPF pwogwams, which
incwudes seccomp BPF, cwassic socket fiwtews, cws_bpf twaffic cwassifiew,
team dwivew's cwassifiew fow its woad-bawancing mode, netfiwtew's xt_bpf
extension, PTP dissectow/cwassifiew, and much mowe. They awe aww intewnawwy
convewted by the kewnew into the new instwuction set wepwesentation and wun
in the eBPF intewpwetew. Fow in-kewnew handwews, this aww wowks twanspawentwy
by using bpf_pwog_cweate() fow setting up the fiwtew, wesp.
bpf_pwog_destwoy() fow destwoying it. The function
bpf_pwog_wun(fiwtew, ctx) twanspawentwy invokes eBPF intewpwetew ow JITed
code to wun the fiwtew. 'fiwtew' is a pointew to stwuct bpf_pwog that we
got fwom bpf_pwog_cweate(), and 'ctx' the given context (e.g.
skb pointew). Aww constwaints and westwictions fwom bpf_check_cwassic() appwy
befowe a convewsion to the new wayout is being done behind the scenes!

Cuwwentwy, the cwassic BPF fowmat is being used fow JITing on most
32-bit awchitectuwes, wheweas x86-64, aawch64, s390x, powewpc64,
spawc64, awm32, wiscv64, wiscv32, woongawch64 pewfowm JIT compiwation
fwom eBPF instwuction set.

Testing
-------

Next to the BPF toowchain, the kewnew awso ships a test moduwe that contains
vawious test cases fow cwassic and eBPF that can be executed against
the BPF intewpwetew and JIT compiwew. It can be found in wib/test_bpf.c and
enabwed via Kconfig::

  CONFIG_TEST_BPF=m

Aftew the moduwe has been buiwt and instawwed, the test suite can be executed
via insmod ow modpwobe against 'test_bpf' moduwe. Wesuwts of the test cases
incwuding timings in nsec can be found in the kewnew wog (dmesg).

Misc
----

Awso twinity, the Winux syscaww fuzzew, has buiwt-in suppowt fow BPF and
SECCOMP-BPF kewnew fuzzing.

Wwitten by
----------

The document was wwitten in the hope that it is found usefuw and in owdew
to give potentiaw BPF hackews ow secuwity auditows a bettew ovewview of
the undewwying awchitectuwe.

- Jay Schuwist <jschwst@samba.owg>
- Daniew Bowkmann <daniew@iogeawbox.net>
- Awexei Stawovoitov <ast@kewnew.owg>
