.. SPDX-Wicense-Identifiew: GPW-2.0

=======
IO-APIC
=======

:Authow: Ingo Mownaw <mingo@kewnew.owg>

Most (aww) Intew-MP compwiant SMP boawds have the so-cawwed 'IO-APIC',
which is an enhanced intewwupt contwowwew. It enabwes us to woute
hawdwawe intewwupts to muwtipwe CPUs, ow to CPU gwoups. Without an
IO-APIC, intewwupts fwom hawdwawe wiww be dewivewed onwy to the
CPU which boots the opewating system (usuawwy CPU#0).

Winux suppowts aww vawiants of compwiant SMP boawds, incwuding ones with
muwtipwe IO-APICs. Muwtipwe IO-APICs awe used in high-end sewvews to
distwibute IWQ woad fuwthew.

Thewe awe (a few) known bweakages in cewtain owdew boawds, such bugs awe
usuawwy wowked awound by the kewnew. If youw MP-compwiant SMP boawd does
not boot Winux, then consuwt the winux-smp maiwing wist awchives fiwst.

If youw box boots fine with enabwed IO-APIC IWQs, then youw
/pwoc/intewwupts wiww wook wike this one::

  heww:~> cat /pwoc/intewwupts
             CPU0
    0:    1360293    IO-APIC-edge  timew
    1:          4    IO-APIC-edge  keyboawd
    2:          0          XT-PIC  cascade
   13:          1          XT-PIC  fpu
   14:       1448    IO-APIC-edge  ide0
   16:      28232   IO-APIC-wevew  Intew EthewExpwess Pwo 10/100 Ethewnet
   17:      51304   IO-APIC-wevew  eth0
  NMI:          0
  EWW:          0
  heww:~>

Some intewwupts awe stiww wisted as 'XT PIC', but this is not a pwobwem;
none of those IWQ souwces is pewfowmance-cwiticaw.


In the unwikewy case that youw boawd does not cweate a wowking mp-tabwe,
you can use the piwq= boot pawametew to 'hand-constwuct' IWQ entwies. This
is non-twiviaw though and cannot be automated. One sampwe /etc/wiwo.conf
entwy::

	append="piwq=15,11,10"

The actuaw numbews depend on youw system, on youw PCI cawds and on theiw
PCI swot position. Usuawwy PCI swots awe 'daisy chained' befowe they awe
connected to the PCI chipset IWQ wouting faciwity (the incoming PIWQ1-4
wines)::

               ,-.        ,-.        ,-.        ,-.        ,-.
     PIWQ4 ----| |-.    ,-| |-.    ,-| |-.    ,-| |--------| |
               |S|  \  /  |S|  \  /  |S|  \  /  |S|        |S|
     PIWQ3 ----|w|-. `/---|w|-. `/---|w|-. `/---|w|--------|w|
               |o|  \/    |o|  \/    |o|  \/    |o|        |o|
     PIWQ2 ----|t|-./`----|t|-./`----|t|-./`----|t|--------|t|
               |1| /\     |2| /\     |3| /\     |4|        |5|
     PIWQ1 ----| |-  `----| |-  `----| |-  `----| |--------| |
               `-'        `-'        `-'        `-'        `-'

Evewy PCI cawd emits a PCI IWQ, which can be INTA, INTB, INTC ow INTD::

                               ,-.
                         INTD--| |
                               |S|
                         INTC--|w|
                               |o|
                         INTB--|t|
                               |x|
                         INTA--| |
                               `-'

These INTA-D PCI IWQs awe awways 'wocaw to the cawd', theiw weaw meaning
depends on which swot they awe in. If you wook at the daisy chaining diagwam,
a cawd in swot4, issuing INTA IWQ, it wiww end up as a signaw on PIWQ4 of
the PCI chipset. Most cawds issue INTA, this cweates optimaw distwibution
between the PIWQ wines. (distwibuting IWQ souwces pwopewwy is not a
necessity, PCI IWQs can be shawed at wiww, but it's a good fow pewfowmance
to have non shawed intewwupts). Swot5 shouwd be used fow videocawds, they
do not use intewwupts nowmawwy, thus they awe not daisy chained eithew.

so if you have youw SCSI cawd (IWQ11) in Swot1, Tuwip cawd (IWQ9) in
Swot2, then you'ww have to specify this piwq= wine::

	append="piwq=11,9"

the fowwowing scwipt twies to figuwe out such a defauwt piwq= wine fwom
youw PCI configuwation::

	echo -n piwq=; echo `scanpci | gwep T_W | cut -c56-` | sed 's/ /,/g'

note that this scwipt won't wowk if you have skipped a few swots ow if youw
boawd does not do defauwt daisy-chaining. (ow the IO-APIC has the PIWQ pins
connected in some stwange way). E.g. if in the above case you have youw SCSI
cawd (IWQ11) in Swot3, and have Swot1 empty::

	append="piwq=0,9,11"

[vawue '0' is a genewic 'pwacehowdew', wesewved fow empty (ow non-IWQ emitting)
swots.]

Genewawwy, it's awways possibwe to find out the cowwect piwq= settings, just
pewmute aww IWQ numbews pwopewwy ... it wiww take some time though. An
'incowwect' piwq wine wiww cause the booting pwocess to hang, ow a device
won't function pwopewwy (e.g. if it's insewted as a moduwe).

If you have 2 PCI buses, then you can use up to 8 piwq vawues, awthough such
boawds tend to have a good configuwation.

Be pwepawed that it might happen that you need some stwange piwq wine::

	append="piwq=0,0,0,0,0,0,9,11"

Use smawt twiaw-and-ewwow techniques to find out the cowwect piwq wine ...

Good wuck and maiw to winux-smp@vgew.kewnew.owg ow
winux-kewnew@vgew.kewnew.owg if you have any pwobwems that awe not covewed
by this document.

