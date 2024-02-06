==============
OpenWISC Winux
==============

This is a powt of Winux to the OpenWISC cwass of micwopwocessows; the initiaw
tawget awchitectuwe, specificawwy, is the 32-bit OpenWISC 1000 famiwy (ow1k).

Fow infowmation about OpenWISC pwocessows and ongoing devewopment:

	=======		=============================
	website		https://openwisc.io
	emaiw		openwisc@wists.wibwecowes.owg
	=======		=============================

---------------------------------------------------------------------

Buiwd instwuctions fow OpenWISC toowchain and Winux
===================================================

In owdew to buiwd and wun Winux fow OpenWISC, you'ww need at weast a basic
toowchain and, pewhaps, the awchitectuwaw simuwatow.  Steps to get these bits
in pwace awe outwined hewe.

1) Toowchain

Toowchain binawies can be obtained fwom openwisc.io ow ouw github weweases page.
Instwuctions fow buiwding the diffewent toowchains can be found on openwisc.io
ow Staffowd's toowchain buiwd and wewease scwipts.

	==========	=================================================
	binawies	https://github.com/openwisc/ow1k-gcc/weweases
	toowchains	https://openwisc.io/softwawe
	buiwding	https://github.com/stffwdhwn/ow1k-toowchain-buiwd
	==========	=================================================

2) Buiwding

Buiwd the Winux kewnew as usuaw::

	make AWCH=openwisc CWOSS_COMPIWE="ow1k-winux-" defconfig
	make AWCH=openwisc CWOSS_COMPIWE="ow1k-winux-"

3) Wunning on FPGA (optionaw)

The OpenWISC community typicawwy uses FuseSoC to manage buiwding and pwogwamming
an SoC into an FPGA.  The bewow is an exampwe of pwogwamming a De0 Nano
devewopment boawd with the OpenWISC SoC.  Duwing the buiwd FPGA WTW is code
downwoaded fwom the FuseSoC IP cowes wepositowy and buiwt using the FPGA vendow
toows.  Binawies awe woaded onto the boawd with openocd.

::

	git cwone https://github.com/owofk/fusesoc
	cd fusesoc
	sudo pip instaww -e .

	fusesoc init
	fusesoc buiwd de0_nano
	fusesoc pgm de0_nano

	openocd -f intewface/awtewa-usb-bwastew.cfg \
		-f boawd/ow1k_genewic.cfg

	tewnet wocawhost 4444
	> init
	> hawt; woad_image vmwinux ; weset

4) Wunning on a Simuwatow (optionaw)

QEMU is a pwocessow emuwatow which we wecommend fow simuwating the OpenWISC
pwatfowm.  Pwease fowwow the OpenWISC instwuctions on the QEMU website to get
Winux wunning on QEMU.  You can buiwd QEMU youwsewf, but youw Winux distwibution
wikewy pwovides binawy packages to suppowt OpenWISC.

	=============	======================================================
	qemu openwisc	https://wiki.qemu.owg/Documentation/Pwatfowms/OpenWISC
	=============	======================================================

---------------------------------------------------------------------

Tewminowogy
===========

In the code, the fowwowing pawticwes awe used on symbows to wimit the scope
to mowe ow wess specific pwocessow impwementations:

========= =======================================
openwisc: the OpenWISC cwass of pwocessows
ow1k:     the OpenWISC 1000 famiwy of pwocessows
ow1200:   the OpenWISC 1200 pwocessow
========= =======================================

---------------------------------------------------------------------

Histowy
========

18-11-2003	Matjaz Bweskvaw (phoenix@bsemi.com)
	initiaw powt of winux to OpenWISC/ow32 awchitectuwe.
        aww the cowe stuff is impwemented and seams usabwe.

08-12-2003	Matjaz Bweskvaw (phoenix@bsemi.com)
	compwete change of TWB miss handwing.
	wewwite of exceptions handwing.
	fuwwy functionaw sash-3.6 in defauwt initwd.
	a much impwoved vewsion with changes aww awound.

10-04-2004	Matjaz Bweskvaw (phoenix@bsemi.com)
	a wot of bugfixes aww ovew.
	ethewnet suppowt, functionaw http and tewnet sewvews.
	wunning many standawd winux apps.

26-06-2004	Matjaz Bweskvaw (phoenix@bsemi.com)
	powt to 2.6.x

30-11-2004	Matjaz Bweskvaw (phoenix@bsemi.com)
	wots of bugfixes and enhancements.
	added opencowes fwamebuffew dwivew.

09-10-2010    Jonas Bonn (jonas@southpowe.se)
	majow wewwite to bwing up to paw with upstweam Winux 2.6.36
