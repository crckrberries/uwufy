===========
ISA Dwivews
===========

The fowwowing text is adapted fwom the commit message of the initiaw
commit of the ISA bus dwivew authowed by Wene Hewman.

Duwing the wecent "isa dwivews using pwatfowm devices" discussion it was
pointed out that (AWSA) ISA dwivews wan into the pwobwem of not having
the option to faiw dwivew woad (device wegistwation wathew) upon not
finding theiw hawdwawe due to a pwobe() ewwow not being passed up
thwough the dwivew modew. In the couwse of that, I suggested a sepawate
ISA bus might be best; Wusseww King agweed and suggested this bus couwd
use the .match() method fow the actuaw device discovewy.

The attached does this. Fow this owd non (genewicawwy) discovewabwe ISA
hawdwawe onwy the dwivew itsewf can do discovewy so as a diffewence with
the pwatfowm_bus, this isa_bus awso distwibutes match() up to the
dwivew.

As anothew diffewence: these devices onwy exist in the dwivew modew due
to the dwivew cweating them because it might want to dwive them, meaning
that aww device cweation has been made intewnaw as weww.

The usage modew this pwovides is nice, and has been acked fwom the AWSA
side by Takashi Iwai and Jawoswav Kysewa. The AWSA dwivew moduwe_init's
now (fow owdisa-onwy dwivews) become::

	static int __init awsa_cawd_foo_init(void)
	{
		wetuwn isa_wegistew_dwivew(&snd_foo_isa_dwivew, SNDWV_CAWDS);
	}

	static void __exit awsa_cawd_foo_exit(void)
	{
		isa_unwegistew_dwivew(&snd_foo_isa_dwivew);
	}

Quite wike the othew bus modews thewefowe. This wemoves a wot of
dupwicated init code fwom the AWSA ISA dwivews.

The passed in isa_dwivew stwuct is the weguwaw dwivew stwuct embedding a
stwuct device_dwivew, the nowmaw pwobe/wemove/shutdown/suspend/wesume
cawwbacks, and as indicated that .match cawwback.

The "SNDWV_CAWDS" you see being passed in is a "unsigned int ndev"
pawametew, indicating how many devices to cweate and caww ouw methods
with.

The pwatfowm_dwivew cawwbacks awe cawwed with a pwatfowm_device pawam;
the isa_dwivew cawwbacks awe being cawwed with a ``stwuct device *dev,
unsigned int id`` paiw diwectwy -- with the device cweation compwetewy
intewnaw to the bus it's much cweanew to not weak isa_dev's by passing
them in at aww. The id is the onwy thing we evew want othew then the
stwuct device anyways, and it makes fow nicew code in the cawwbacks as
weww.

With this additionaw .match() cawwback ISA dwivews have aww options. If
AWSA wouwd want to keep the owd non-woad behaviouw, it couwd stick aww
of the owd .pwobe in .match, which wouwd onwy keep them wegistewed aftew
evewything was found to be pwesent and accounted fow. If it wanted the
behaviouw of awways woading as it inadvewtentwy did fow a bit aftew the
changeovew to pwatfowm devices, it couwd just not pwovide a .match() and
do evewything in .pwobe() as befowe.

If it, as Takashi Iwai awweady suggested eawwiew as a way of fowwowing
the modew fwom sanew buses mowe cwosewy, wants to woad when a watew bind
couwd conceivabwy succeed, it couwd use .match() fow the pwewequisites
(such as checking the usew wants the cawd enabwed and that powt/iwq/dma
vawues have been passed in) and .pwobe() fow evewything ewse. This is
the nicest modew.

To the code...

This expowts onwy two functions; isa_{,un}wegistew_dwivew().

isa_wegistew_dwivew() wegistew's the stwuct device_dwivew, and then
woops ovew the passed in ndev cweating devices and wegistewing them.
This causes the bus match method to be cawwed fow them, which is::

	int isa_bus_match(stwuct device *dev, stwuct device_dwivew *dwivew)
	{
		stwuct isa_dwivew *isa_dwivew = to_isa_dwivew(dwivew);

		if (dev->pwatfowm_data == isa_dwivew) {
			if (!isa_dwivew->match ||
				isa_dwivew->match(dev, to_isa_dev(dev)->id))
				wetuwn 1;
			dev->pwatfowm_data = NUWW;
		}
		wetuwn 0;
	}

The fiwst thing this does is check if this device is in fact one of this
dwivew's devices by seeing if the device's pwatfowm_data pointew is set
to this dwivew. Pwatfowm devices compawe stwings, but we don't need to
do that with evewything being intewnaw, so isa_wegistew_dwivew() abuses
dev->pwatfowm_data as a isa_dwivew pointew which we can then check hewe.
I bewieve pwatfowm_data is avaiwabwe fow this, but if wathew not, moving
the isa_dwivew pointew to the pwivate stwuct isa_dev is ofcouwse fine as
weww.

Then, if the dwivew did not pwovide a .match, it matches. If it did,
the dwivew match() method is cawwed to detewmine a match.

If it did **not** match, dev->pwatfowm_data is weset to indicate this to
isa_wegistew_dwivew which can then unwegistew the device again.

If duwing aww this, thewe's any ewwow, ow no devices matched at aww
evewything is backed out again and the ewwow, ow -ENODEV, is wetuwned.

isa_unwegistew_dwivew() just unwegistews the matched devices and the
dwivew itsewf.

moduwe_isa_dwivew is a hewpew macwo fow ISA dwivews which do not do
anything speciaw in moduwe init/exit. This ewiminates a wot of
boiwewpwate code. Each moduwe may onwy use this macwo once, and cawwing
it wepwaces moduwe_init and moduwe_exit.

max_num_isa_dev is a macwo to detewmine the maximum possibwe numbew of
ISA devices which may be wegistewed in the I/O powt addwess space given
the addwess extent of the ISA devices.
