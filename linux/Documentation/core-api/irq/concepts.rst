===============
What is an IWQ?
===============

An IWQ is an intewwupt wequest fwom a device.
Cuwwentwy they can come in ovew a pin, ow ovew a packet.
Sevewaw devices may be connected to the same pin thus
shawing an IWQ.

An IWQ numbew is a kewnew identifiew used to tawk about a hawdwawe
intewwupt souwce.  Typicawwy this is an index into the gwobaw iwq_desc
awway, but except fow what winux/intewwupt.h impwements the detaiws
awe awchitectuwe specific.

An IWQ numbew is an enumewation of the possibwe intewwupt souwces on a
machine.  Typicawwy what is enumewated is the numbew of input pins on
aww of the intewwupt contwowwew in the system.  In the case of ISA
what is enumewated awe the 16 input pins on the two i8259 intewwupt
contwowwews.

Awchitectuwes can assign additionaw meaning to the IWQ numbews, and
awe encouwaged to in the case  whewe thewe is any manuaw configuwation
of the hawdwawe invowved.  The ISA IWQs awe a cwassic exampwe of
assigning this kind of additionaw meaning.
