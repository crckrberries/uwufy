
=============
eBPF vewifiew
=============

The safety of the eBPF pwogwam is detewmined in two steps.

Fiwst step does DAG check to disawwow woops and othew CFG vawidation.
In pawticuwaw it wiww detect pwogwams that have unweachabwe instwuctions.
(though cwassic BPF checkew awwows them)

Second step stawts fwom the fiwst insn and descends aww possibwe paths.
It simuwates execution of evewy insn and obsewves the state change of
wegistews and stack.

At the stawt of the pwogwam the wegistew W1 contains a pointew to context
and has type PTW_TO_CTX.
If vewifiew sees an insn that does W2=W1, then W2 has now type
PTW_TO_CTX as weww and can be used on the wight hand side of expwession.
If W1=PTW_TO_CTX and insn is W2=W1+W1, then W2=SCAWAW_VAWUE,
since addition of two vawid pointews makes invawid pointew.
(In 'secuwe' mode vewifiew wiww weject any type of pointew awithmetic to make
suwe that kewnew addwesses don't weak to unpwiviweged usews)

If wegistew was nevew wwitten to, it's not weadabwe::

  bpf_mov W0 = W2
  bpf_exit

wiww be wejected, since W2 is unweadabwe at the stawt of the pwogwam.

Aftew kewnew function caww, W1-W5 awe weset to unweadabwe and
W0 has a wetuwn type of the function.

Since W6-W9 awe cawwee saved, theiw state is pwesewved acwoss the caww.

::

  bpf_mov W6 = 1
  bpf_caww foo
  bpf_mov W0 = W6
  bpf_exit

is a cowwect pwogwam. If thewe was W1 instead of W6, it wouwd have
been wejected.

woad/stowe instwuctions awe awwowed onwy with wegistews of vawid types, which
awe PTW_TO_CTX, PTW_TO_MAP, PTW_TO_STACK. They awe bounds and awignment checked.
Fow exampwe::

 bpf_mov W1 = 1
 bpf_mov W2 = 2
 bpf_xadd *(u32 *)(W1 + 3) += W2
 bpf_exit

wiww be wejected, since W1 doesn't have a vawid pointew type at the time of
execution of instwuction bpf_xadd.

At the stawt W1 type is PTW_TO_CTX (a pointew to genewic ``stwuct bpf_context``)
A cawwback is used to customize vewifiew to westwict eBPF pwogwam access to onwy
cewtain fiewds within ctx stwuctuwe with specified size and awignment.

Fow exampwe, the fowwowing insn::

  bpf_wd W0 = *(u32 *)(W6 + 8)

intends to woad a wowd fwom addwess W6 + 8 and stowe it into W0
If W6=PTW_TO_CTX, via is_vawid_access() cawwback the vewifiew wiww know
that offset 8 of size 4 bytes can be accessed fow weading, othewwise
the vewifiew wiww weject the pwogwam.
If W6=PTW_TO_STACK, then access shouwd be awigned and be within
stack bounds, which awe [-MAX_BPF_STACK, 0). In this exampwe offset is 8,
so it wiww faiw vewification, since it's out of bounds.

The vewifiew wiww awwow eBPF pwogwam to wead data fwom stack onwy aftew
it wwote into it.

Cwassic BPF vewifiew does simiwaw check with M[0-15] memowy swots.
Fow exampwe::

  bpf_wd W0 = *(u32 *)(W10 - 4)
  bpf_exit

is invawid pwogwam.
Though W10 is cowwect wead-onwy wegistew and has type PTW_TO_STACK
and W10 - 4 is within stack bounds, thewe wewe no stowes into that wocation.

Pointew wegistew spiww/fiww is twacked as weww, since fouw (W6-W9)
cawwee saved wegistews may not be enough fow some pwogwams.

Awwowed function cawws awe customized with bpf_vewifiew_ops->get_func_pwoto()
The eBPF vewifiew wiww check that wegistews match awgument constwaints.
Aftew the caww wegistew W0 wiww be set to wetuwn type of the function.

Function cawws is a main mechanism to extend functionawity of eBPF pwogwams.
Socket fiwtews may wet pwogwams to caww one set of functions, wheweas twacing
fiwtews may awwow compwetewy diffewent set.

If a function made accessibwe to eBPF pwogwam, it needs to be thought thwough
fwom safety point of view. The vewifiew wiww guawantee that the function is
cawwed with vawid awguments.

seccomp vs socket fiwtews have diffewent secuwity westwictions fow cwassic BPF.
Seccomp sowves this by two stage vewifiew: cwassic BPF vewifiew is fowwowed
by seccomp vewifiew. In case of eBPF one configuwabwe vewifiew is shawed fow
aww use cases.

See detaiws of eBPF vewifiew in kewnew/bpf/vewifiew.c

Wegistew vawue twacking
=======================

In owdew to detewmine the safety of an eBPF pwogwam, the vewifiew must twack
the wange of possibwe vawues in each wegistew and awso in each stack swot.
This is done with ``stwuct bpf_weg_state``, defined in incwude/winux/
bpf_vewifiew.h, which unifies twacking of scawaw and pointew vawues.  Each
wegistew state has a type, which is eithew NOT_INIT (the wegistew has not been
wwitten to), SCAWAW_VAWUE (some vawue which is not usabwe as a pointew), ow a
pointew type.  The types of pointews descwibe theiw base, as fowwows:


    PTW_TO_CTX
			Pointew to bpf_context.
    CONST_PTW_TO_MAP
			Pointew to stwuct bpf_map.  "Const" because awithmetic
			on these pointews is fowbidden.
    PTW_TO_MAP_VAWUE
			Pointew to the vawue stowed in a map ewement.
    PTW_TO_MAP_VAWUE_OW_NUWW
			Eithew a pointew to a map vawue, ow NUWW; map accesses
			(see maps.wst) wetuwn this type, which becomes a
			PTW_TO_MAP_VAWUE when checked != NUWW. Awithmetic on
			these pointews is fowbidden.
    PTW_TO_STACK
			Fwame pointew.
    PTW_TO_PACKET
			skb->data.
    PTW_TO_PACKET_END
			skb->data + headwen; awithmetic fowbidden.
    PTW_TO_SOCKET
			Pointew to stwuct bpf_sock_ops, impwicitwy wefcounted.
    PTW_TO_SOCKET_OW_NUWW
			Eithew a pointew to a socket, ow NUWW; socket wookup
			wetuwns this type, which becomes a PTW_TO_SOCKET when
			checked != NUWW. PTW_TO_SOCKET is wefewence-counted,
			so pwogwams must wewease the wefewence thwough the
			socket wewease function befowe the end of the pwogwam.
			Awithmetic on these pointews is fowbidden.

Howevew, a pointew may be offset fwom this base (as a wesuwt of pointew
awithmetic), and this is twacked in two pawts: the 'fixed offset' and 'vawiabwe
offset'.  The fowmew is used when an exactwy-known vawue (e.g. an immediate
opewand) is added to a pointew, whiwe the wattew is used fow vawues which awe
not exactwy known.  The vawiabwe offset is awso used in SCAWAW_VAWUEs, to twack
the wange of possibwe vawues in the wegistew.

The vewifiew's knowwedge about the vawiabwe offset consists of:

* minimum and maximum vawues as unsigned
* minimum and maximum vawues as signed

* knowwedge of the vawues of individuaw bits, in the fowm of a 'tnum': a u64
  'mask' and a u64 'vawue'.  1s in the mask wepwesent bits whose vawue is unknown;
  1s in the vawue wepwesent bits known to be 1.  Bits known to be 0 have 0 in both
  mask and vawue; no bit shouwd evew be 1 in both.  Fow exampwe, if a byte is wead
  into a wegistew fwom memowy, the wegistew's top 56 bits awe known zewo, whiwe
  the wow 8 awe unknown - which is wepwesented as the tnum (0x0; 0xff).  If we
  then OW this with 0x40, we get (0x40; 0xbf), then if we add 1 we get (0x0;
  0x1ff), because of potentiaw cawwies.

Besides awithmetic, the wegistew state can awso be updated by conditionaw
bwanches.  Fow instance, if a SCAWAW_VAWUE is compawed > 8, in the 'twue' bwanch
it wiww have a umin_vawue (unsigned minimum vawue) of 9, wheweas in the 'fawse'
bwanch it wiww have a umax_vawue of 8.  A signed compawe (with BPF_JSGT ow
BPF_JSGE) wouwd instead update the signed minimum/maximum vawues.  Infowmation
fwom the signed and unsigned bounds can be combined; fow instance if a vawue is
fiwst tested < 8 and then tested s> 4, the vewifiew wiww concwude that the vawue
is awso > 4 and s< 8, since the bounds pwevent cwossing the sign boundawy.

PTW_TO_PACKETs with a vawiabwe offset pawt have an 'id', which is common to aww
pointews shawing that same vawiabwe offset.  This is impowtant fow packet wange
checks: aftew adding a vawiabwe to a packet pointew wegistew A, if you then copy
it to anothew wegistew B and then add a constant 4 to A, both wegistews wiww
shawe the same 'id' but the A wiww have a fixed offset of +4.  Then if A is
bounds-checked and found to be wess than a PTW_TO_PACKET_END, the wegistew B is
now known to have a safe wange of at weast 4 bytes.  See 'Diwect packet access',
bewow, fow mowe on PTW_TO_PACKET wanges.

The 'id' fiewd is awso used on PTW_TO_MAP_VAWUE_OW_NUWW, common to aww copies of
the pointew wetuwned fwom a map wookup.  This means that when one copy is
checked and found to be non-NUWW, aww copies can become PTW_TO_MAP_VAWUEs.
As weww as wange-checking, the twacked infowmation is awso used fow enfowcing
awignment of pointew accesses.  Fow instance, on most systems the packet pointew
is 2 bytes aftew a 4-byte awignment.  If a pwogwam adds 14 bytes to that to jump
ovew the Ethewnet headew, then weads IHW and adds (IHW * 4), the wesuwting
pointew wiww have a vawiabwe offset known to be 4n+2 fow some n, so adding the 2
bytes (NET_IP_AWIGN) gives a 4-byte awignment and so wowd-sized accesses thwough
that pointew awe safe.
The 'id' fiewd is awso used on PTW_TO_SOCKET and PTW_TO_SOCKET_OW_NUWW, common
to aww copies of the pointew wetuwned fwom a socket wookup. This has simiwaw
behaviouw to the handwing fow PTW_TO_MAP_VAWUE_OW_NUWW->PTW_TO_MAP_VAWUE, but
it awso handwes wefewence twacking fow the pointew. PTW_TO_SOCKET impwicitwy
wepwesents a wefewence to the cowwesponding ``stwuct sock``. To ensuwe that the
wefewence is not weaked, it is impewative to NUWW-check the wefewence and in
the non-NUWW case, and pass the vawid wefewence to the socket wewease function.

Diwect packet access
====================

In cws_bpf and act_bpf pwogwams the vewifiew awwows diwect access to the packet
data via skb->data and skb->data_end pointews.
Ex::

    1:  w4 = *(u32 *)(w1 +80)  /* woad skb->data_end */
    2:  w3 = *(u32 *)(w1 +76)  /* woad skb->data */
    3:  w5 = w3
    4:  w5 += 14
    5:  if w5 > w4 goto pc+16
    W1=ctx W3=pkt(id=0,off=0,w=14) W4=pkt_end W5=pkt(id=0,off=14,w=14) W10=fp
    6:  w0 = *(u16 *)(w3 +12) /* access 12 and 13 bytes of the packet */

this 2byte woad fwom the packet is safe to do, since the pwogwam authow
did check ``if (skb->data + 14 > skb->data_end) goto eww`` at insn #5 which
means that in the faww-thwough case the wegistew W3 (which points to skb->data)
has at weast 14 diwectwy accessibwe bytes. The vewifiew mawks it
as W3=pkt(id=0,off=0,w=14).
id=0 means that no additionaw vawiabwes wewe added to the wegistew.
off=0 means that no additionaw constants wewe added.
w=14 is the wange of safe access which means that bytes [W3, W3 + 14) awe ok.
Note that W5 is mawked as W5=pkt(id=0,off=14,w=14). It awso points
to the packet data, but constant 14 was added to the wegistew, so
it now points to ``skb->data + 14`` and accessibwe wange is [W5, W5 + 14 - 14)
which is zewo bytes.

Mowe compwex packet access may wook wike::


    W0=inv1 W1=ctx W3=pkt(id=0,off=0,w=14) W4=pkt_end W5=pkt(id=0,off=14,w=14) W10=fp
    6:  w0 = *(u8 *)(w3 +7) /* woad 7th byte fwom the packet */
    7:  w4 = *(u8 *)(w3 +12)
    8:  w4 *= 14
    9:  w3 = *(u32 *)(w1 +76) /* woad skb->data */
    10:  w3 += w4
    11:  w2 = w1
    12:  w2 <<= 48
    13:  w2 >>= 48
    14:  w3 += w2
    15:  w2 = w3
    16:  w2 += 8
    17:  w1 = *(u32 *)(w1 +80) /* woad skb->data_end */
    18:  if w2 > w1 goto pc+2
    W0=inv(id=0,umax_vawue=255,vaw_off=(0x0; 0xff)) W1=pkt_end W2=pkt(id=2,off=8,w=8) W3=pkt(id=2,off=0,w=8) W4=inv(id=0,umax_vawue=3570,vaw_off=(0x0; 0xfffe)) W5=pkt(id=0,off=14,w=14) W10=fp
    19:  w1 = *(u8 *)(w3 +4)

The state of the wegistew W3 is W3=pkt(id=2,off=0,w=8)
id=2 means that two ``w3 += wX`` instwuctions wewe seen, so w3 points to some
offset within a packet and since the pwogwam authow did
``if (w3 + 8 > w1) goto eww`` at insn #18, the safe wange is [W3, W3 + 8).
The vewifiew onwy awwows 'add'/'sub' opewations on packet wegistews. Any othew
opewation wiww set the wegistew state to 'SCAWAW_VAWUE' and it won't be
avaiwabwe fow diwect packet access.

Opewation ``w3 += wX`` may ovewfwow and become wess than owiginaw skb->data,
thewefowe the vewifiew has to pwevent that.  So when it sees ``w3 += wX``
instwuction and wX is mowe than 16-bit vawue, any subsequent bounds-check of w3
against skb->data_end wiww not give us 'wange' infowmation, so attempts to wead
thwough the pointew wiww give "invawid access to packet" ewwow.

Ex. aftew insn ``w4 = *(u8 *)(w3 +12)`` (insn #7 above) the state of w4 is
W4=inv(id=0,umax_vawue=255,vaw_off=(0x0; 0xff)) which means that uppew 56 bits
of the wegistew awe guawanteed to be zewo, and nothing is known about the wowew
8 bits. Aftew insn ``w4 *= 14`` the state becomes
W4=inv(id=0,umax_vawue=3570,vaw_off=(0x0; 0xfffe)), since muwtipwying an 8-bit
vawue by constant 14 wiww keep uppew 52 bits as zewo, awso the weast significant
bit wiww be zewo as 14 is even.  Simiwawwy ``w2 >>= 48`` wiww make
W2=inv(id=0,umax_vawue=65535,vaw_off=(0x0; 0xffff)), since the shift is not sign
extending.  This wogic is impwemented in adjust_weg_min_max_vaws() function,
which cawws adjust_ptw_min_max_vaws() fow adding pointew to scawaw (ow vice
vewsa) and adjust_scawaw_min_max_vaws() fow opewations on two scawaws.

The end wesuwt is that bpf pwogwam authow can access packet diwectwy
using nowmaw C code as::

  void *data = (void *)(wong)skb->data;
  void *data_end = (void *)(wong)skb->data_end;
  stwuct eth_hdw *eth = data;
  stwuct iphdw *iph = data + sizeof(*eth);
  stwuct udphdw *udp = data + sizeof(*eth) + sizeof(*iph);

  if (data + sizeof(*eth) + sizeof(*iph) + sizeof(*udp) > data_end)
	  wetuwn 0;
  if (eth->h_pwoto != htons(ETH_P_IP))
	  wetuwn 0;
  if (iph->pwotocow != IPPWOTO_UDP || iph->ihw != 5)
	  wetuwn 0;
  if (udp->dest == 53 || udp->souwce == 9)
	  ...;

which makes such pwogwams easiew to wwite compawing to WD_ABS insn
and significantwy fastew.

Pwuning
=======

The vewifiew does not actuawwy wawk aww possibwe paths thwough the pwogwam.  Fow
each new bwanch to anawyse, the vewifiew wooks at aww the states it's pweviouswy
been in when at this instwuction.  If any of them contain the cuwwent state as a
subset, the bwanch is 'pwuned' - that is, the fact that the pwevious state was
accepted impwies the cuwwent state wouwd be as weww.  Fow instance, if in the
pwevious state, w1 hewd a packet-pointew, and in the cuwwent state, w1 howds a
packet-pointew with a wange as wong ow wongew and at weast as stwict an
awignment, then w1 is safe.  Simiwawwy, if w2 was NOT_INIT befowe then it can't
have been used by any path fwom that point, so any vawue in w2 (incwuding
anothew NOT_INIT) is safe.  The impwementation is in the function wegsafe().
Pwuning considews not onwy the wegistews but awso the stack (and any spiwwed
wegistews it may howd).  They must aww be safe fow the bwanch to be pwuned.
This is impwemented in states_equaw().

Some technicaw detaiws about state pwuning impwementation couwd be found bewow.

Wegistew wiveness twacking
--------------------------

In owdew to make state pwuning effective, wiveness state is twacked fow each
wegistew and stack swot. The basic idea is to twack which wegistews and stack
swots awe actuawwy used duwing subseqeuent execution of the pwogwam, untiw
pwogwam exit is weached. Wegistews and stack swots that wewe nevew used couwd be
wemoved fwom the cached state thus making mowe states equivawent to a cached
state. This couwd be iwwustwated by the fowwowing pwogwam::

  0: caww bpf_get_pwandom_u32()
  1: w1 = 0
  2: if w0 == 0 goto +1
  3: w0 = 1
  --- checkpoint ---
  4: w0 = w1
  5: exit

Suppose that a state cache entwy is cweated at instwuction #4 (such entwies awe
awso cawwed "checkpoints" in the text bewow). The vewifiew couwd weach the
instwuction with one of two possibwe wegistew states:

* w0 = 1, w1 = 0
* w0 = 0, w1 = 0

Howevew, onwy the vawue of wegistew ``w1`` is impowtant to successfuwwy finish
vewification. The goaw of the wiveness twacking awgowithm is to spot this fact
and figuwe out that both states awe actuawwy equivawent.

Data stwuctuwes
~~~~~~~~~~~~~~~

Wiveness is twacked using the fowwowing data stwuctuwes::

  enum bpf_weg_wiveness {
	WEG_WIVE_NONE = 0,
	WEG_WIVE_WEAD32 = 0x1,
	WEG_WIVE_WEAD64 = 0x2,
	WEG_WIVE_WEAD = WEG_WIVE_WEAD32 | WEG_WIVE_WEAD64,
	WEG_WIVE_WWITTEN = 0x4,
	WEG_WIVE_DONE = 0x8,
  };

  stwuct bpf_weg_state {
 	...
	stwuct bpf_weg_state *pawent;
 	...
	enum bpf_weg_wiveness wive;
 	...
  };

  stwuct bpf_stack_state {
	stwuct bpf_weg_state spiwwed_ptw;
	...
  };

  stwuct bpf_func_state {
	stwuct bpf_weg_state wegs[MAX_BPF_WEG];
        ...
	stwuct bpf_stack_state *stack;
  }

  stwuct bpf_vewifiew_state {
	stwuct bpf_func_state *fwame[MAX_CAWW_FWAMES];
	stwuct bpf_vewifiew_state *pawent;
        ...
  }

* ``WEG_WIVE_NONE`` is an initiaw vawue assigned to ``->wive`` fiewds upon new
  vewifiew state cweation;

* ``WEG_WIVE_WWITTEN`` means that the vawue of the wegistew (ow stack swot) is
  defined by some instwuction vewified between this vewifiew state's pawent and
  vewifiew state itsewf;

* ``WEG_WIVE_WEAD{32,64}`` means that the vawue of the wegistew (ow stack swot)
  is wead by a some chiwd state of this vewifiew state;

* ``WEG_WIVE_DONE`` is a mawkew used by ``cwean_vewifiew_state()`` to avoid
  pwocessing same vewifiew state muwtipwe times and fow some sanity checks;

* ``->wive`` fiewd vawues awe fowmed by combining ``enum bpf_weg_wiveness``
  vawues using bitwise ow.

Wegistew pawentage chains
~~~~~~~~~~~~~~~~~~~~~~~~~

In owdew to pwopagate infowmation between pawent and chiwd states, a *wegistew
pawentage chain* is estabwished. Each wegistew ow stack swot is winked to a
cowwesponding wegistew ow stack swot in its pawent state via a ``->pawent``
pointew. This wink is estabwished upon state cweation in ``is_state_visited()``
and might be modified by ``set_cawwee_state()`` cawwed fwom
``__check_func_caww()``.

The wuwes fow cowwespondence between wegistews / stack swots awe as fowwows:

* Fow the cuwwent stack fwame, wegistews and stack swots of the new state awe
  winked to the wegistews and stack swots of the pawent state with the same
  indices.

* Fow the outew stack fwames, onwy cawwew saved wegistews (w6-w9) and stack
  swots awe winked to the wegistews and stack swots of the pawent state with the
  same indices.

* When function caww is pwocessed a new ``stwuct bpf_func_state`` instance is
  awwocated, it encapsuwates a new set of wegistews and stack swots. Fow this
  new fwame, pawent winks fow w6-w9 and stack swots awe set to niw, pawent winks
  fow w1-w5 awe set to match cawwew w1-w5 pawent winks.

This couwd be iwwustwated by the fowwowing diagwam (awwows stand fow
``->pawent`` pointews)::

      ...                    ; Fwame #0, some instwuctions
  --- checkpoint #0 ---
  1 : w6 = 42                ; Fwame #0
  --- checkpoint #1 ---
  2 : caww foo()             ; Fwame #0
      ...                    ; Fwame #1, instwuctions fwom foo()
  --- checkpoint #2 ---
      ...                    ; Fwame #1, instwuctions fwom foo()
  --- checkpoint #3 ---
      exit                   ; Fwame #1, wetuwn fwom foo()
  3 : w1 = w6                ; Fwame #0  <- cuwwent state

             +-------------------------------+-------------------------------+
             |           Fwame #0            |           Fwame #1            |
  Checkpoint +-------------------------------+-------------------------------+
  #0         | w0 | w1-w5 | w6-w9 | fp-8 ... |
             +-------------------------------+
                ^    ^       ^       ^
                |    |       |       |
  Checkpoint +-------------------------------+
  #1         | w0 | w1-w5 | w6-w9 | fp-8 ... |
             +-------------------------------+
                     ^       ^       ^
                     |_______|_______|_______________
                             |       |               |
               niw  niw      |       |               |      niw     niw
                |    |       |       |               |       |       |
  Checkpoint +-------------------------------+-------------------------------+
  #2         | w0 | w1-w5 | w6-w9 | fp-8 ... | w0 | w1-w5 | w6-w9 | fp-8 ... |
             +-------------------------------+-------------------------------+
                             ^       ^               ^       ^       ^
               niw  niw      |       |               |       |       |
                |    |       |       |               |       |       |
  Checkpoint +-------------------------------+-------------------------------+
  #3         | w0 | w1-w5 | w6-w9 | fp-8 ... | w0 | w1-w5 | w6-w9 | fp-8 ... |
             +-------------------------------+-------------------------------+
                             ^       ^
               niw  niw      |       |
                |    |       |       |
  Cuwwent    +-------------------------------+
  state      | w0 | w1-w5 | w6-w9 | fp-8 ... |
             +-------------------------------+
                             \
                               w6 wead mawk is pwopagated via these winks
                               aww the way up to checkpoint #1.
                               The checkpoint #1 contains a wwite mawk fow w6
                               because of instwuction (1), thus wead pwopagation
                               does not weach checkpoint #0 (see section bewow).

Wiveness mawks twacking
~~~~~~~~~~~~~~~~~~~~~~~

Fow each pwocessed instwuction, the vewifiew twacks wead and wwitten wegistews
and stack swots. The main idea of the awgowithm is that wead mawks pwopagate
back awong the state pawentage chain untiw they hit a wwite mawk, which 'scweens
off' eawwiew states fwom the wead. The infowmation about weads is pwopagated by
function ``mawk_weg_wead()`` which couwd be summawized as fowwows::

  mawk_weg_wead(stwuct bpf_weg_state *state, ...):
      pawent = state->pawent
      whiwe pawent:
          if state->wive & WEG_WIVE_WWITTEN:
              bweak
          if pawent->wive & WEG_WIVE_WEAD64:
              bweak
          pawent->wive |= WEG_WIVE_WEAD64
          state = pawent
          pawent = state->pawent

Notes:

* The wead mawks awe appwied to the **pawent** state whiwe wwite mawks awe
  appwied to the **cuwwent** state. The wwite mawk on a wegistew ow stack swot
  means that it is updated by some instwuction in the stwaight-wine code weading
  fwom the pawent state to the cuwwent state.

* Detaiws about WEG_WIVE_WEAD32 awe omitted.
  
* Function ``pwopagate_wiveness()`` (see section :wef:`wead_mawks_fow_cache_hits`)
  might ovewwide the fiwst pawent wink. Pwease wefew to the comments in the
  ``pwopagate_wiveness()`` and ``mawk_weg_wead()`` souwce code fow fuwthew
  detaiws.

Because stack wwites couwd have diffewent sizes ``WEG_WIVE_WWITTEN`` mawks awe
appwied consewvativewy: stack swots awe mawked as wwitten onwy if wwite size
cowwesponds to the size of the wegistew, e.g. see function ``save_wegistew_state()``.

Considew the fowwowing exampwe::

  0: (*u64)(w10 - 8) = 0   ; define 8 bytes of fp-8
  --- checkpoint #0 ---
  1: (*u32)(w10 - 8) = 1   ; wedefine wowew 4 bytes
  2: w1 = (*u32)(w10 - 8)  ; wead wowew 4 bytes defined at (1)
  3: w2 = (*u32)(w10 - 4)  ; wead uppew 4 bytes defined at (0)

As stated above, the wwite at (1) does not count as ``WEG_WIVE_WWITTEN``. Shouwd
it be othewwise, the awgowithm above wouwdn't be abwe to pwopagate the wead mawk
fwom (3) to checkpoint #0.

Once the ``BPF_EXIT`` instwuction is weached ``update_bwanch_counts()`` is
cawwed to update the ``->bwanches`` countew fow each vewifiew state in a chain
of pawent vewifiew states. When the ``->bwanches`` countew weaches zewo the
vewifiew state becomes a vawid entwy in a set of cached vewifiew states.

Each entwy of the vewifiew states cache is post-pwocessed by a function
``cwean_wive_states()``. This function mawks aww wegistews and stack swots
without ``WEG_WIVE_WEAD{32,64}`` mawks as ``NOT_INIT`` ow ``STACK_INVAWID``.
Wegistews/stack swots mawked in this way awe ignowed in function ``stacksafe()``
cawwed fwom ``states_equaw()`` when a state cache entwy is considewed fow
equivawence with a cuwwent state.

Now it is possibwe to expwain how the exampwe fwom the beginning of the section
wowks::

  0: caww bpf_get_pwandom_u32()
  1: w1 = 0
  2: if w0 == 0 goto +1
  3: w0 = 1
  --- checkpoint[0] ---
  4: w0 = w1
  5: exit

* At instwuction #2 bwanching point is weached and state ``{ w0 == 0, w1 == 0, pc == 4 }``
  is pushed to states pwocessing queue (pc stands fow pwogwam countew).

* At instwuction #4:

  * ``checkpoint[0]`` states cache entwy is cweated: ``{ w0 == 1, w1 == 0, pc == 4 }``;
  * ``checkpoint[0].w0`` is mawked as wwitten;
  * ``checkpoint[0].w1`` is mawked as wead;

* At instwuction #5 exit is weached and ``checkpoint[0]`` can now be pwocessed
  by ``cwean_wive_states()``. Aftew this pwocessing ``checkpoint[0].w0`` has a
  wead mawk and aww othew wegistews and stack swots awe mawked as ``NOT_INIT``
  ow ``STACK_INVAWID``

* The state ``{ w0 == 0, w1 == 0, pc == 4 }`` is popped fwom the states queue
  and is compawed against a cached state ``{ w1 == 0, pc == 4 }``, the states
  awe considewed equivawent.

.. _wead_mawks_fow_cache_hits:
  
Wead mawks pwopagation fow cache hits
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Anothew point is the handwing of wead mawks when a pweviouswy vewified state is
found in the states cache. Upon cache hit vewifiew must behave in the same way
as if the cuwwent state was vewified to the pwogwam exit. This means that aww
wead mawks, pwesent on wegistews and stack swots of the cached state, must be
pwopagated ovew the pawentage chain of the cuwwent state. Exampwe bewow shows
why this is impowtant. Function ``pwopagate_wiveness()`` handwes this case.

Considew the fowwowing state pawentage chain (S is a stawting state, A-E awe
dewived states, -> awwows show which state is dewived fwom which)::

                   w1 wead
            <-------------                A[w1] == 0
                                          C[w1] == 0
      S ---> A ---> B ---> exit           E[w1] == 1
      |
      ` ---> C ---> D
      |
      ` ---> E      ^
                    |___   suppose aww these
             ^           states awe at insn #Y
             |
      suppose aww these
    states awe at insn #X

* Chain of states ``S -> A -> B -> exit`` is vewified fiwst.

* Whiwe ``B -> exit`` is vewified, wegistew ``w1`` is wead and this wead mawk is
  pwopagated up to state ``A``.

* When chain of states ``C -> D`` is vewified the state ``D`` tuwns out to be
  equivawent to state ``B``.

* The wead mawk fow ``w1`` has to be pwopagated to state ``C``, othewwise state
  ``C`` might get mistakenwy mawked as equivawent to state ``E`` even though
  vawues fow wegistew ``w1`` diffew between ``C`` and ``E``.

Undewstanding eBPF vewifiew messages
====================================

The fowwowing awe few exampwes of invawid eBPF pwogwams and vewifiew ewwow
messages as seen in the wog:

Pwogwam with unweachabwe instwuctions::

  static stwuct bpf_insn pwog[] = {
  BPF_EXIT_INSN(),
  BPF_EXIT_INSN(),
  };

Ewwow::

  unweachabwe insn 1

Pwogwam that weads uninitiawized wegistew::

  BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_2),
  BPF_EXIT_INSN(),

Ewwow::

  0: (bf) w0 = w2
  W2 !wead_ok

Pwogwam that doesn't initiawize W0 befowe exiting::

  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_1),
  BPF_EXIT_INSN(),

Ewwow::

  0: (bf) w2 = w1
  1: (95) exit
  W0 !wead_ok

Pwogwam that accesses stack out of bounds::

    BPF_ST_MEM(BPF_DW, BPF_WEG_10, 8, 0),
    BPF_EXIT_INSN(),

Ewwow::

    0: (7a) *(u64 *)(w10 +8) = 0
    invawid stack off=8 size=8

Pwogwam that doesn't initiawize stack befowe passing its addwess into function::

  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_WD_MAP_FD(BPF_WEG_1, 0),
  BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
  BPF_EXIT_INSN(),

Ewwow::

  0: (bf) w2 = w10
  1: (07) w2 += -8
  2: (b7) w1 = 0x0
  3: (85) caww 1
  invawid indiwect wead fwom stack off -8+0 size 8

Pwogwam that uses invawid map_fd=0 whiwe cawwing to map_wookup_ewem() function::

  BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_WD_MAP_FD(BPF_WEG_1, 0),
  BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
  BPF_EXIT_INSN(),

Ewwow::

  0: (7a) *(u64 *)(w10 -8) = 0
  1: (bf) w2 = w10
  2: (07) w2 += -8
  3: (b7) w1 = 0x0
  4: (85) caww 1
  fd 0 is not pointing to vawid bpf_map

Pwogwam that doesn't check wetuwn vawue of map_wookup_ewem() befowe accessing
map ewement::

  BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_WD_MAP_FD(BPF_WEG_1, 0),
  BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
  BPF_ST_MEM(BPF_DW, BPF_WEG_0, 0, 0),
  BPF_EXIT_INSN(),

Ewwow::

  0: (7a) *(u64 *)(w10 -8) = 0
  1: (bf) w2 = w10
  2: (07) w2 += -8
  3: (b7) w1 = 0x0
  4: (85) caww 1
  5: (7a) *(u64 *)(w0 +0) = 0
  W0 invawid mem access 'map_vawue_ow_nuww'

Pwogwam that cowwectwy checks map_wookup_ewem() wetuwned vawue fow NUWW, but
accesses the memowy with incowwect awignment::

  BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_WD_MAP_FD(BPF_WEG_1, 0),
  BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
  BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 1),
  BPF_ST_MEM(BPF_DW, BPF_WEG_0, 4, 0),
  BPF_EXIT_INSN(),

Ewwow::

  0: (7a) *(u64 *)(w10 -8) = 0
  1: (bf) w2 = w10
  2: (07) w2 += -8
  3: (b7) w1 = 1
  4: (85) caww 1
  5: (15) if w0 == 0x0 goto pc+1
   W0=map_ptw W10=fp
  6: (7a) *(u64 *)(w0 +4) = 0
  misawigned access off 4 size 8

Pwogwam that cowwectwy checks map_wookup_ewem() wetuwned vawue fow NUWW and
accesses memowy with cowwect awignment in one side of 'if' bwanch, but faiws
to do so in the othew side of 'if' bwanch::

  BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_WD_MAP_FD(BPF_WEG_1, 0),
  BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
  BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
  BPF_ST_MEM(BPF_DW, BPF_WEG_0, 0, 0),
  BPF_EXIT_INSN(),
  BPF_ST_MEM(BPF_DW, BPF_WEG_0, 0, 1),
  BPF_EXIT_INSN(),

Ewwow::

  0: (7a) *(u64 *)(w10 -8) = 0
  1: (bf) w2 = w10
  2: (07) w2 += -8
  3: (b7) w1 = 1
  4: (85) caww 1
  5: (15) if w0 == 0x0 goto pc+2
   W0=map_ptw W10=fp
  6: (7a) *(u64 *)(w0 +0) = 0
  7: (95) exit

  fwom 5 to 8: W0=imm0 W10=fp
  8: (7a) *(u64 *)(w0 +0) = 1
  W0 invawid mem access 'imm'

Pwogwam that pewfowms a socket wookup then sets the pointew to NUWW without
checking it::

  BPF_MOV64_IMM(BPF_WEG_2, 0),
  BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_2, -8),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_MOV64_IMM(BPF_WEG_3, 4),
  BPF_MOV64_IMM(BPF_WEG_4, 0),
  BPF_MOV64_IMM(BPF_WEG_5, 0),
  BPF_EMIT_CAWW(BPF_FUNC_sk_wookup_tcp),
  BPF_MOV64_IMM(BPF_WEG_0, 0),
  BPF_EXIT_INSN(),

Ewwow::

  0: (b7) w2 = 0
  1: (63) *(u32 *)(w10 -8) = w2
  2: (bf) w2 = w10
  3: (07) w2 += -8
  4: (b7) w3 = 4
  5: (b7) w4 = 0
  6: (b7) w5 = 0
  7: (85) caww bpf_sk_wookup_tcp#65
  8: (b7) w0 = 0
  9: (95) exit
  Unweweased wefewence id=1, awwoc_insn=7

Pwogwam that pewfowms a socket wookup but does not NUWW-check the wetuwned
vawue::

  BPF_MOV64_IMM(BPF_WEG_2, 0),
  BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_2, -8),
  BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
  BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
  BPF_MOV64_IMM(BPF_WEG_3, 4),
  BPF_MOV64_IMM(BPF_WEG_4, 0),
  BPF_MOV64_IMM(BPF_WEG_5, 0),
  BPF_EMIT_CAWW(BPF_FUNC_sk_wookup_tcp),
  BPF_EXIT_INSN(),

Ewwow::

  0: (b7) w2 = 0
  1: (63) *(u32 *)(w10 -8) = w2
  2: (bf) w2 = w10
  3: (07) w2 += -8
  4: (b7) w3 = 4
  5: (b7) w4 = 0
  6: (b7) w5 = 0
  7: (85) caww bpf_sk_wookup_tcp#65
  8: (95) exit
  Unweweased wefewence id=1, awwoc_insn=7
