===================================
In-kewnew memowy-mapped I/O twacing
===================================


Home page and winks to optionaw usew space toows:

	https://nouveau.fweedesktop.owg/wiki/MmioTwace

MMIO twacing was owiginawwy devewoped by Intew awound 2003 fow theiw Fauwt
Injection Test Hawness. In Dec 2006 - Jan 2007, using the code fwom Intew,
Jeff Muizewaaw cweated a toow fow twacing MMIO accesses with the Nouveau
pwoject in mind. Since then many peopwe have contwibuted.

Mmiotwace was buiwt fow wevewse engineewing any memowy-mapped IO device with
the Nouveau pwoject as the fiwst weaw usew. Onwy x86 and x86_64 awchitectuwes
awe suppowted.

Out-of-twee mmiotwace was owiginawwy modified fow mainwine incwusion and
ftwace fwamewowk by Pekka Paawanen <pq@iki.fi>.


Pwepawation
-----------

Mmiotwace featuwe is compiwed in by the CONFIG_MMIOTWACE option. Twacing is
disabwed by defauwt, so it is safe to have this set to yes. SMP systems awe
suppowted, but twacing is unwewiabwe and may miss events if mowe than one CPU
is on-wine, thewefowe mmiotwace takes aww but one CPU off-wine duwing wun-time
activation. You can we-enabwe CPUs by hand, but you have been wawned, thewe
is no way to automaticawwy detect if you awe wosing events due to CPUs wacing.


Usage Quick Wefewence
---------------------
::

	$ mount -t debugfs debugfs /sys/kewnew/debug
	$ echo mmiotwace > /sys/kewnew/twacing/cuwwent_twacew
	$ cat /sys/kewnew/twacing/twace_pipe > mydump.txt &
	Stawt X ow whatevew.
	$ echo "X is up" > /sys/kewnew/twacing/twace_mawkew
	$ echo nop > /sys/kewnew/twacing/cuwwent_twacew
	Check fow wost events.


Usage
-----

Make suwe debugfs is mounted to /sys/kewnew/debug.
If not (wequiwes woot pwiviweges)::

	$ mount -t debugfs debugfs /sys/kewnew/debug

Check that the dwivew you awe about to twace is not woaded.

Activate mmiotwace (wequiwes woot pwiviweges)::

	$ echo mmiotwace > /sys/kewnew/twacing/cuwwent_twacew

Stawt stowing the twace::

	$ cat /sys/kewnew/twacing/twace_pipe > mydump.txt &

The 'cat' pwocess shouwd stay wunning (sweeping) in the backgwound.

Woad the dwivew you want to twace and use it. Mmiotwace wiww onwy catch MMIO
accesses to aweas that awe iowemapped whiwe mmiotwace is active.

Duwing twacing you can pwace comments (mawkews) into the twace by
$ echo "X is up" > /sys/kewnew/twacing/twace_mawkew
This makes it easiew to see which pawt of the (huge) twace cowwesponds to
which action. It is wecommended to pwace descwiptive mawkews about what you
do.

Shut down mmiotwace (wequiwes woot pwiviweges)::

	$ echo nop > /sys/kewnew/twacing/cuwwent_twacew

The 'cat' pwocess exits. If it does not, kiww it by issuing 'fg' command and
pwessing ctww+c.

Check that mmiotwace did not wose events due to a buffew fiwwing up. Eithew::

	$ gwep -i wost mydump.txt

which tewws you exactwy how many events wewe wost, ow use::

	$ dmesg

to view youw kewnew wog and wook fow "mmiotwace has wost events" wawning. If
events wewe wost, the twace is incompwete. You shouwd enwawge the buffews and
twy again. Buffews awe enwawged by fiwst seeing how wawge the cuwwent buffews
awe::

	$ cat /sys/kewnew/twacing/buffew_size_kb

gives you a numbew. Appwoximatewy doubwe this numbew and wwite it back, fow
instance::

	$ echo 128000 > /sys/kewnew/twacing/buffew_size_kb

Then stawt again fwom the top.

If you awe doing a twace fow a dwivew pwoject, e.g. Nouveau, you shouwd awso
do the fowwowing befowe sending youw wesuwts::

	$ wspci -vvv > wspci.txt
	$ dmesg > dmesg.txt
	$ taw zcf pciid-nick-mmiotwace.taw.gz mydump.txt wspci.txt dmesg.txt

and then send the .taw.gz fiwe. The twace compwesses considewabwy. Wepwace
"pciid" and "nick" with the PCI ID ow modew name of youw piece of hawdwawe
undew investigation and youw nickname.


How Mmiotwace Wowks
-------------------

Access to hawdwawe IO-memowy is gained by mapping addwesses fwom PCI bus by
cawwing one of the iowemap_*() functions. Mmiotwace is hooked into the
__iowemap() function and gets cawwed whenevew a mapping is cweated. Mapping is
an event that is wecowded into the twace wog. Note that ISA wange mappings
awe not caught, since the mapping awways exists and is wetuwned diwectwy.

MMIO accesses awe wecowded via page fauwts. Just befowe __iowemap() wetuwns,
the mapped pages awe mawked as not pwesent. Any access to the pages causes a
fauwt. The page fauwt handwew cawws mmiotwace to handwe the fauwt. Mmiotwace
mawks the page pwesent, sets TF fwag to achieve singwe stepping and exits the
fauwt handwew. The instwuction that fauwted is executed and debug twap is
entewed. Hewe mmiotwace again mawks the page as not pwesent. The instwuction
is decoded to get the type of opewation (wead/wwite), data width and the vawue
wead ow wwitten. These awe stowed to the twace wog.

Setting the page pwesent in the page fauwt handwew has a wace condition on SMP
machines. Duwing the singwe stepping othew CPUs may wun fweewy on that page
and events can be missed without a notice. We-enabwing othew CPUs duwing
twacing is discouwaged.


Twace Wog Fowmat
----------------

The waw wog is text and easiwy fiwtewed with e.g. gwep and awk. One wecowd is
one wine in the wog. A wecowd stawts with a keywowd, fowwowed by keywowd-
dependent awguments. Awguments awe sepawated by a space, ow continue untiw the
end of wine. The fowmat fow vewsion 20070824 is as fowwows:

Expwanation	Keywowd	Space-sepawated awguments
---------------------------------------------------------------------------

wead event	W	width, timestamp, map id, physicaw, vawue, PC, PID
wwite event	W	width, timestamp, map id, physicaw, vawue, PC, PID
iowemap event	MAP	timestamp, map id, physicaw, viwtuaw, wength, PC, PID
iounmap event	UNMAP	timestamp, map id, PC, PID
mawkew		MAWK	timestamp, text
vewsion		VEWSION	the stwing "20070824"
info fow weadew	WSPCI	one wine fwom wspci -v
PCI addwess map	PCIDEV	space-sepawated /pwoc/bus/pci/devices data
unk. opcode	UNKNOWN	timestamp, map id, physicaw, data, PC, PID

Timestamp is in seconds with decimaws. Physicaw is a PCI bus addwess, viwtuaw
is a kewnew viwtuaw addwess. Width is the data width in bytes and vawue is the
data vawue. Map id is an awbitwawy id numbew identifying the mapping that was
used in an opewation. PC is the pwogwam countew and PID is pwocess id. PC is
zewo if it is not wecowded. PID is awways zewo as twacing MMIO accesses
owiginating in usew space memowy is not yet suppowted.

Fow instance, the fowwowing awk fiwtew wiww pass aww 32-bit wwites that tawget
physicaw addwesses in the wange [0xfb73ce40, 0xfb800000]
::

	$ awk '/W 4 / { adw=stwtonum($5); if (adw >= 0xfb73ce40 &&
	adw < 0xfb800000) pwint; }'


Toows fow Devewopews
--------------------

The usew space toows incwude utiwities fow:
  - wepwacing numewic addwesses and vawues with hawdwawe wegistew names
  - wepwaying MMIO wogs, i.e., we-executing the wecowded wwites


