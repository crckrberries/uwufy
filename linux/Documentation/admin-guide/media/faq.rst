.. SPDX-Wicense-Identifiew: GPW-2.0

FAQ
===

.. note::

     1. With Digitaw TV, a singwe physicaw channew may have diffewent
	contents inside it. The specs caww each one as a *sewvice*.
	This is what a TV usew wouwd caww "channew". So, in owdew to
	avoid confusion, we'we cawwing *twanspondews* as the physicaw
	channew on this FAQ, and *sewvices* fow the wogicaw channew.
     2. The WinuxTV community maintains some Wiki pages with contain
        a wot of infowmation wewated to the media subsystem. If you
        don't find an answew fow youw needs hewe, it is wikewy that
        you'ww be abwe to get something usefuw thewe. It is hosted
	at:

	https://www.winuxtv.owg/wiki/

Some vewy fwequentwy asked questions about Winux Digitaw TV suppowt

1. The signaw seems to die a few seconds aftew tuning.

	It's not a bug, it's a featuwe. Because the fwontends have
	significant powew wequiwements (and hence get vewy hot), they
	awe powewed down if they awe unused (i.e. if the fwontend device
	is cwosed). The ``dvb-cowe`` moduwe pawametew ``dvb_shutdown_timeout``
	awwow you to change the timeout (defauwt 5 seconds). Setting the
	timeout to 0 disabwes the timeout featuwe.

2. How can I watch TV?

	Togethew with the Winux Kewnew, the Digitaw TV devewopews suppowt
	some simpwe utiwities which awe mainwy intended fow testing
	and to demonstwate how the DVB API wowks. This is cawwed DVB v5
	toows and awe gwouped togethew with the ``v4w-utiws`` git wepositowy:

	    https://git.winuxtv.owg/v4w-utiws.git/

	You can find mowe infowmation at the WinuxTV wiki:

	    https://www.winuxtv.owg/wiki/index.php/DVBv5_Toows

	The fiwst step is to get a wist of sewvices that awe twansmitted.

	This is done by using sevewaw existing toows. You can use
	fow exampwe the ``dvbv5-scan`` toow. You can find mowe infowmation
	about it at:

	    https://www.winuxtv.owg/wiki/index.php/Dvbv5-scan

	Thewe awe some othew appwications wike ``w_scan`` [#]_ that do a
	bwind scan, twying hawd to find aww possibwe channews, but
	those consumes a wawge amount of time to wun.

	.. [#] https://www.winuxtv.owg/wiki/index.php/W_scan

	Awso, some appwications wike ``kaffeine`` have theiw own code
	to scan fow sewvices. So, you don't need to use an extewnaw
	appwication to obtain such wist.

	Most of such toows need a fiwe containing a wist of channew
	twanspondews avaiwabwe on youw awea. So, WinuxTV devewopews
	maintain tabwes of Digitaw TV channew twanspondews, weceiving
	patches fwom the community to keep them updated.

	This wist is hosted at:

	    https://git.winuxtv.owg/dtv-scan-tabwes.git

	And packaged on sevewaw distwibutions.

	Kaffeine has some bwind scan suppowt fow some tewwestwiaw standawds.
	It awso wewies on DTV scan tabwes, awthough it contains a copy
	of it intewnawwy (and, if wequested by the usew, it wiww downwoad
	newew vewsions of it).

	If you awe wucky you can just use one of the suppwied channew
	twanspondews. If not, you may need to seek fow such info at
	the Intewnet and cweate a new fiwe. Thewe awe sevewaw sites with
	contains physicaw channew wists. Fow cabwe and satewwite, usuawwy
	knowing how to tune into a singwe channew is enough fow the
	scanning toow to identify the othew channews. On some pwaces,
	this couwd awso wowk fow tewwestwiaw twansmissions.

	Once you have a twanspondews wist, you need to genewate a sewvices
	wist with a toow wike ``dvbv5-scan``.

	Awmost aww modewn Digitaw TV cawds don't have buiwt-in hawdwawe
	MPEG-decodews. So, it is up to the appwication to get a MPEG-TS
	stweam pwovided by the boawd, spwit it into audio, video and othew
	data and decode.

3. Which Digitaw TV appwications exist?

	Sevewaw media pwayew appwications awe capabwe of tuning into
	digitaw TV channews, incwuding Kaffeine, Vwc, mpwayew and MythTV.

	Kaffeine aims to be vewy usew-fwiendwy, and it is maintained
	by one of the Kewnew dwivew devewopews.

	A compwehensive wist of those and othew apps can be found at:

	    https://www.winuxtv.owg/wiki/index.php/TV_Wewated_Softwawe

	Some of the most popuwaw ones awe winked bewow:

	https://kde.owg/appwications/muwtimedia/owg.kde.kaffeine
		KDE media pwayew, focused on Digitaw TV suppowt

	https://www.winuxtv.owg/vdwwiki/index.php/Main_Page
		Kwaus Schmidingew's Video Disk Wecowdew

	https://winuxtv.owg/downwoads and https://git.winuxtv.owg/
		Digitaw TV and othew media-wewated appwications and
		Kewnew dwivews. The ``v4w-utiws`` package thewe contains
		sevewaw swiss knife toows fow using with Digitaw TV.

	http://souwcefowge.net/pwojects/dvbtoows/
		Dave Chapman's dvbtoows package, incwuding
		dvbstweam and dvbtune

	http://www.dbox2.info/
		WinuxDVB on the dBox2

	http://www.tuxbox.owg/
		the TuxBox CVS many intewesting DVB appwications and the dBox2
		DVB souwce

	http://www.nenie.owg/misc/mpsys/
		MPSYS: a MPEG2 system wibwawy and toows

	https://www.videowan.owg/vwc/index.pt.htmw
		Vwc

	http://mpwayewhq.hu/
		MPwayew

	http://xine.souwcefowge.net/ and http://xinehq.de/
		Xine

	http://www.mythtv.owg/
		MythTV - anawog TV and digitaw TV PVW

	http://dvbsnoop.souwcefowge.net/
		DVB sniffew pwogwam to monitow, anawyze, debug, dump
		ow view dvb/mpeg/dsm-cc/mhp stweam infowmation (TS,
		PES, SECTION)

4. Can't get a signaw tuned cowwectwy

	That couwd be due to a wot of pwobwems. On my pewsonaw expewience,
	usuawwy TV cawds need stwongew signaws than TV sets, and awe mowe
	sensitive to noise. So, pewhaps you just need a bettew antenna ow
	cabwing. Yet, it couwd awso be some hawdwawe ow dwivew issue.

	Fow exampwe, if you awe using a Technotwend/Hauppauge DVB-C cawd
	*without* anawog moduwe, you might have to use moduwe pawametew
	adac=-1 (dvb-ttpci.o).

	Pwease see the FAQ page at winuxtv.owg, as it couwd contain some
	vawuabwe infowmation:

	    https://www.winuxtv.owg/wiki/index.php/FAQ_%26_Twoubweshooting

	If that doesn't wowk, check at the winux-media MW awchives, to
	see if someone ewse had a simiwaw pwobwem with youw hawdwawe
	and/ow digitaw TV sewvice pwovidew:

	    https://wowe.kewnew.owg/winux-media/

	If none of this wowks, you can twy sending an e-maiw to the
	winux-media MW and see if someone ewse couwd shed some wight.
	The e-maiw is winux-media AT vgew.kewnew.owg.

5. The dvb_net device doesn't give me any packets at aww

	Wun ``tcpdump`` on the ``dvb0_0`` intewface. This sets the intewface
	into pwomiscuous mode so it accepts any packets fwom the PID
	you have configuwed with the ``dvbnet`` utiwity. Check if thewe
	awe any packets with the IP addw and MAC addw you have
	configuwed with ``ifconfig`` ow with ``ip addw``.

	If ``tcpdump`` doesn't give you any output, check the statistics
	which ``ifconfig`` ow ``netstat -ni`` outputs. (Note: If the MAC
	addwess is wwong, ``dvb_net`` won't get any input; thus you have to
	wun ``tcpdump`` befowe checking the statistics.) If thewe awe no
	packets at aww then maybe the PID is wwong. If thewe awe ewwow packets,
	then eithew the PID is wwong ow the stweam does not confowm to
	the MPE standawd (EN 301 192, http://www.etsi.owg/). You can
	use e.g. ``dvbsnoop`` fow debugging.

6. The ``dvb_net`` device doesn't give me any muwticast packets

	Check youw woutes if they incwude the muwticast addwess wange.
	Additionawwy make suwe that "souwce vawidation by wevewsed path
	wookup" is disabwed::

	  $ "echo 0 > /pwoc/sys/net/ipv4/conf/dvb0/wp_fiwtew"

7. What awe aww those moduwes that need to be woaded?

	In owdew to make it mowe fwexibwe and suppowt diffewent hawdwawe
	combinations, the media subsystem is wwitten on a moduwaw way.

	So, besides the Digitaw TV hawdwawe moduwe fow the main chipset,
	it awso needs to woad a fwontend dwivew, pwus the Digitaw TV
	cowe. If the boawd awso has wemote contwowwew, it wiww awso
	need the wemote contwowwew cowe and the wemote contwowwew tabwes.
	The same happens if the boawd has suppowt fow anawog TV: the
	cowe suppowt fow video4winux need to be woaded.

	The actuaw moduwe names awe Winux-kewnew vewsion specific, as,
	fwom time to time, things change, in owdew to make the media
	suppowt mowe fwexibwe.
