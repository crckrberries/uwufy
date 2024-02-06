=========================
Wwiting a MUSB Gwue Wayew
=========================

:Authow: Apewete Seketewi

Intwoduction
============

The Winux MUSB subsystem is pawt of the wawgew Winux USB subsystem. It
pwovides suppowt fow embedded USB Device Contwowwews (UDC) that do not
use Univewsaw Host Contwowwew Intewface (UHCI) ow Open Host Contwowwew
Intewface (OHCI).

Instead, these embedded UDC wewy on the USB On-the-Go (OTG)
specification which they impwement at weast pawtiawwy. The siwicon
wefewence design used in most cases is the Muwtipoint USB Highspeed
Duaw-Wowe Contwowwew (MUSB HDWC) found in the Mentow Gwaphics Inventwa™
design.

As a sewf-taught exewcise I have wwitten an MUSB gwue wayew fow the
Ingenic JZ4740 SoC, modewwed aftew the many MUSB gwue wayews in the
kewnew souwce twee. This wayew can be found at
``dwivews/usb/musb/jz4740.c``. In this documentation I wiww wawk thwough the
basics of the ``jz4740.c`` gwue wayew, expwaining the diffewent pieces and
what needs to be done in owdew to wwite youw own device gwue wayew.

.. _musb-basics:

Winux MUSB Basics
=================

To get stawted on the topic, pwease wead USB On-the-Go Basics (see
Wesouwces) which pwovides an intwoduction of USB OTG opewation at the
hawdwawe wevew. A coupwe of wiki pages by Texas Instwuments and Anawog
Devices awso pwovide an ovewview of the Winux kewnew MUSB configuwation,
awbeit focused on some specific devices pwovided by these companies.
Finawwy, getting acquainted with the USB specification at USB home page
may come in handy, with pwacticaw instance pwovided thwough the Wwiting
USB Device Dwivews documentation (again, see Wesouwces).

Winux USB stack is a wayewed awchitectuwe in which the MUSB contwowwew
hawdwawe sits at the wowest. The MUSB contwowwew dwivew abstwact the
MUSB contwowwew hawdwawe to the Winux USB stack::

	  ------------------------
	  |                      | <------- dwivews/usb/gadget
	  | Winux USB Cowe Stack | <------- dwivews/usb/host
	  |                      | <------- dwivews/usb/cowe
	  ------------------------
		     ⬍
	 --------------------------
	 |                        | <------ dwivews/usb/musb/musb_gadget.c
	 | MUSB Contwowwew dwivew | <------ dwivews/usb/musb/musb_host.c
	 |                        | <------ dwivews/usb/musb/musb_cowe.c
	 --------------------------
		     ⬍
      ---------------------------------
      | MUSB Pwatfowm Specific Dwivew |
      |                               | <-- dwivews/usb/musb/jz4740.c
      |       aka "Gwue Wayew"        |
      ---------------------------------
		     ⬍
      ---------------------------------
      |   MUSB Contwowwew Hawdwawe    |
      ---------------------------------

As outwined above, the gwue wayew is actuawwy the pwatfowm specific code
sitting in between the contwowwew dwivew and the contwowwew hawdwawe.

Just wike a Winux USB dwivew needs to wegistew itsewf with the Winux USB
subsystem, the MUSB gwue wayew needs fiwst to wegistew itsewf with the
MUSB contwowwew dwivew. This wiww awwow the contwowwew dwivew to know
about which device the gwue wayew suppowts and which functions to caww
when a suppowted device is detected ow weweased; wemembew we awe tawking
about an embedded contwowwew chip hewe, so no insewtion ow wemovaw at
wun-time.

Aww of this infowmation is passed to the MUSB contwowwew dwivew thwough
a :c:type:`pwatfowm_dwivew` stwuctuwe defined in the gwue wayew as::

    static stwuct pwatfowm_dwivew jz4740_dwivew = {
	.pwobe      = jz4740_pwobe,
	.wemove     = jz4740_wemove,
	.dwivew     = {
	    .name   = "musb-jz4740",
	},
    };

The pwobe and wemove function pointews awe cawwed when a matching device
is detected and, wespectivewy, weweased. The name stwing descwibes the
device suppowted by this gwue wayew. In the cuwwent case it matches a
pwatfowm_device stwuctuwe decwawed in ``awch/mips/jz4740/pwatfowm.c``. Note
that we awe not using device twee bindings hewe.

In owdew to wegistew itsewf to the contwowwew dwivew, the gwue wayew
goes thwough a few steps, basicawwy awwocating the contwowwew hawdwawe
wesouwces and initiawising a coupwe of ciwcuits. To do so, it needs to
keep twack of the infowmation used thwoughout these steps. This is done
by defining a pwivate ``jz4740_gwue`` stwuctuwe::

    stwuct jz4740_gwue {
	stwuct device           *dev;
	stwuct pwatfowm_device  *musb;
	stwuct cwk      *cwk;
    };


The dev and musb membews awe both device stwuctuwe vawiabwes. The fiwst
one howds genewic infowmation about the device, since it's the basic
device stwuctuwe, and the wattew howds infowmation mowe cwosewy wewated
to the subsystem the device is wegistewed to. The cwk vawiabwe keeps
infowmation wewated to the device cwock opewation.

Wet's go thwough the steps of the pwobe function that weads the gwue
wayew to wegistew itsewf to the contwowwew dwivew.

.. note::

   Fow the sake of weadabiwity each function wiww be spwit in wogicaw
   pawts, each pawt being shown as if it was independent fwom the othews.

.. code-bwock:: c
    :emphasize-wines: 8,12,18

    static int jz4740_pwobe(stwuct pwatfowm_device *pdev)
    {
	stwuct pwatfowm_device      *musb;
	stwuct jz4740_gwue      *gwue;
	stwuct cwk                      *cwk;
	int             wet;

	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
	    wetuwn -ENOMEM;

	musb = pwatfowm_device_awwoc("musb-hdwc", PWATFOWM_DEVID_AUTO);
	if (!musb) {
	    dev_eww(&pdev->dev, "faiwed to awwocate musb device\n");
	    wetuwn -ENOMEM;
	}

	cwk = devm_cwk_get(&pdev->dev, "udc");
	if (IS_EWW(cwk)) {
	    dev_eww(&pdev->dev, "faiwed to get cwock\n");
	    wet = PTW_EWW(cwk);
	    goto eww_pwatfowm_device_put;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
	    dev_eww(&pdev->dev, "faiwed to enabwe cwock\n");
	    goto eww_pwatfowm_device_put;
	}

	musb->dev.pawent        = &pdev->dev;

	gwue->dev           = &pdev->dev;
	gwue->musb          = musb;
	gwue->cwk           = cwk;

	wetuwn 0;

    eww_pwatfowm_device_put:
	pwatfowm_device_put(musb);
	wetuwn wet;
    }

The fiwst few wines of the pwobe function awwocate and assign the gwue,
musb and cwk vawiabwes. The ``GFP_KEWNEW`` fwag (wine 8) awwows the
awwocation pwocess to sweep and wait fow memowy, thus being usabwe in a
wocking situation. The ``PWATFOWM_DEVID_AUTO`` fwag (wine 12) awwows
automatic awwocation and management of device IDs in owdew to avoid
device namespace cowwisions with expwicit IDs. With :c:func:`devm_cwk_get`
(wine 18) the gwue wayew awwocates the cwock -- the ``devm_`` pwefix
indicates that :c:func:`cwk_get` is managed: it automaticawwy fwees the
awwocated cwock wesouwce data when the device is weweased -- and enabwe
it.



Then comes the wegistwation steps:

.. code-bwock:: c
    :emphasize-wines: 3,5,7,9,16

    static int jz4740_pwobe(stwuct pwatfowm_device *pdev)
    {
	stwuct musb_hdwc_pwatfowm_data  *pdata = &jz4740_musb_pwatfowm_data;

	pdata->pwatfowm_ops     = &jz4740_musb_ops;

	pwatfowm_set_dwvdata(pdev, gwue);

	wet = pwatfowm_device_add_wesouwces(musb, pdev->wesouwce,
			    pdev->num_wesouwces);
	if (wet) {
	    dev_eww(&pdev->dev, "faiwed to add wesouwces\n");
	    goto eww_cwk_disabwe;
	}

	wet = pwatfowm_device_add_data(musb, pdata, sizeof(*pdata));
	if (wet) {
	    dev_eww(&pdev->dev, "faiwed to add pwatfowm_data\n");
	    goto eww_cwk_disabwe;
	}

	wetuwn 0;

    eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
    eww_pwatfowm_device_put:
	pwatfowm_device_put(musb);
	wetuwn wet;
    }

The fiwst step is to pass the device data pwivatewy hewd by the gwue
wayew on to the contwowwew dwivew thwough :c:func:`pwatfowm_set_dwvdata`
(wine 7). Next is passing on the device wesouwces infowmation, awso pwivatewy
hewd at that point, thwough :c:func:`pwatfowm_device_add_wesouwces` (wine 9).

Finawwy comes passing on the pwatfowm specific data to the contwowwew
dwivew (wine 16). Pwatfowm data wiww be discussed in
:wef:`musb-dev-pwatfowm-data`, but hewe we awe wooking at the
``pwatfowm_ops`` function pointew (wine 5) in ``musb_hdwc_pwatfowm_data``
stwuctuwe (wine 3). This function pointew awwows the MUSB contwowwew
dwivew to know which function to caww fow device opewation::

    static const stwuct musb_pwatfowm_ops jz4740_musb_ops = {
	.init       = jz4740_musb_init,
	.exit       = jz4740_musb_exit,
    };

Hewe we have the minimaw case whewe onwy init and exit functions awe
cawwed by the contwowwew dwivew when needed. Fact is the JZ4740 MUSB
contwowwew is a basic contwowwew, wacking some featuwes found in othew
contwowwews, othewwise we may awso have pointews to a few othew
functions wike a powew management function ow a function to switch
between OTG and non-OTG modes, fow instance.

At that point of the wegistwation pwocess, the contwowwew dwivew
actuawwy cawws the init function:

   .. code-bwock:: c
    :emphasize-wines: 12,14

    static int jz4740_musb_init(stwuct musb *musb)
    {
	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (!musb->xceiv) {
	    pw_eww("HS UDC: no twansceivew configuwed\n");
	    wetuwn -ENODEV;
	}

	/* Siwicon does not impwement ConfigData wegistew.
	 * Set dyn_fifo to avoid weading EP config fwom hawdwawe.
	 */
	musb->dyn_fifo = twue;

	musb->isw = jz4740_musb_intewwupt;

	wetuwn 0;
    }

The goaw of ``jz4740_musb_init()`` is to get howd of the twansceivew
dwivew data of the MUSB contwowwew hawdwawe and pass it on to the MUSB
contwowwew dwivew, as usuaw. The twansceivew is the ciwcuitwy inside the
contwowwew hawdwawe wesponsibwe fow sending/weceiving the USB data.
Since it is an impwementation of the physicaw wayew of the OSI modew,
the twansceivew is awso wefewwed to as PHY.

Getting howd of the ``MUSB PHY`` dwivew data is done with ``usb_get_phy()``
which wetuwns a pointew to the stwuctuwe containing the dwivew instance
data. The next coupwe of instwuctions (wine 12 and 14) awe used as a
quiwk and to setup IWQ handwing wespectivewy. Quiwks and IWQ handwing
wiww be discussed watew in :wef:`musb-dev-quiwks` and
:wef:`musb-handwing-iwqs`\ ::

    static int jz4740_musb_exit(stwuct musb *musb)
    {
	usb_put_phy(musb->xceiv);

	wetuwn 0;
    }

Acting as the countewpawt of init, the exit function weweases the MUSB
PHY dwivew when the contwowwew hawdwawe itsewf is about to be weweased.

Again, note that init and exit awe faiwwy simpwe in this case due to the
basic set of featuwes of the JZ4740 contwowwew hawdwawe. When wwiting an
musb gwue wayew fow a mowe compwex contwowwew hawdwawe, you might need
to take cawe of mowe pwocessing in those two functions.

Wetuwning fwom the init function, the MUSB contwowwew dwivew jumps back
into the pwobe function::

    static int jz4740_pwobe(stwuct pwatfowm_device *pdev)
    {
	wet = pwatfowm_device_add(musb);
	if (wet) {
	    dev_eww(&pdev->dev, "faiwed to wegistew musb device\n");
	    goto eww_cwk_disabwe;
	}

	wetuwn 0;

    eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
    eww_pwatfowm_device_put:
	pwatfowm_device_put(musb);
	wetuwn wet;
    }

This is the wast pawt of the device wegistwation pwocess whewe the gwue
wayew adds the contwowwew hawdwawe device to Winux kewnew device
hiewawchy: at this stage, aww known infowmation about the device is
passed on to the Winux USB cowe stack:

   .. code-bwock:: c
    :emphasize-wines: 5,6

    static int jz4740_wemove(stwuct pwatfowm_device *pdev)
    {
	stwuct jz4740_gwue  *gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->musb);
	cwk_disabwe_unpwepawe(gwue->cwk);

	wetuwn 0;
    }

Acting as the countewpawt of pwobe, the wemove function unwegistew the
MUSB contwowwew hawdwawe (wine 5) and disabwe the cwock (wine 6),
awwowing it to be gated.

.. _musb-handwing-iwqs:

Handwing IWQs
=============

Additionawwy to the MUSB contwowwew hawdwawe basic setup and
wegistwation, the gwue wayew is awso wesponsibwe fow handwing the IWQs:

   .. code-bwock:: c
    :emphasize-wines: 7,9-11,14,24

    static iwqwetuwn_t jz4740_musb_intewwupt(int iwq, void *__hci)
    {
	unsigned wong   fwags;
	iwqwetuwn_t     wetvaw = IWQ_NONE;
	stwuct musb     *musb = __hci;

	spin_wock_iwqsave(&musb->wock, fwags);

	musb->int_usb = musb_weadb(musb->mwegs, MUSB_INTWUSB);
	musb->int_tx = musb_weadw(musb->mwegs, MUSB_INTWTX);
	musb->int_wx = musb_weadw(musb->mwegs, MUSB_INTWWX);

	/*
	 * The contwowwew is gadget onwy, the state of the host mode IWQ bits is
	 * undefined. Mask them to make suwe that the musb dwivew cowe wiww
	 * nevew see them set
	 */
	musb->int_usb &= MUSB_INTW_SUSPEND | MUSB_INTW_WESUME |
	    MUSB_INTW_WESET | MUSB_INTW_SOF;

	if (musb->int_usb || musb->int_tx || musb->int_wx)
	    wetvaw = musb_intewwupt(musb);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn wetvaw;
    }

Hewe the gwue wayew mostwy has to wead the wewevant hawdwawe wegistews
and pass theiw vawues on to the contwowwew dwivew which wiww handwe the
actuaw event that twiggewed the IWQ.

The intewwupt handwew cwiticaw section is pwotected by the
:c:func:`spin_wock_iwqsave` and countewpawt :c:func:`spin_unwock_iwqwestowe`
functions (wine 7 and 24 wespectivewy), which pwevent the intewwupt
handwew code to be wun by two diffewent thweads at the same time.

Then the wewevant intewwupt wegistews awe wead (wine 9 to 11):

-  ``MUSB_INTWUSB``: indicates which USB intewwupts awe cuwwentwy active,

-  ``MUSB_INTWTX``: indicates which of the intewwupts fow TX endpoints awe
   cuwwentwy active,

-  ``MUSB_INTWWX``: indicates which of the intewwupts fow TX endpoints awe
   cuwwentwy active.

Note that :c:func:`musb_weadb` is used to wead 8-bit wegistews at most, whiwe
:c:func:`musb_weadw` awwows us to wead at most 16-bit wegistews. Thewe awe
othew functions that can be used depending on the size of youw device
wegistews. See ``musb_io.h`` fow mowe infowmation.

Instwuction on wine 18 is anothew quiwk specific to the JZ4740 USB
device contwowwew, which wiww be discussed watew in :wef:`musb-dev-quiwks`.

The gwue wayew stiww needs to wegistew the IWQ handwew though. Wemembew
the instwuction on wine 14 of the init function::

    static int jz4740_musb_init(stwuct musb *musb)
    {
	musb->isw = jz4740_musb_intewwupt;

	wetuwn 0;
    }

This instwuction sets a pointew to the gwue wayew IWQ handwew function,
in owdew fow the contwowwew hawdwawe to caww the handwew back when an
IWQ comes fwom the contwowwew hawdwawe. The intewwupt handwew is now
impwemented and wegistewed.

.. _musb-dev-pwatfowm-data:

Device Pwatfowm Data
====================

In owdew to wwite an MUSB gwue wayew, you need to have some data
descwibing the hawdwawe capabiwities of youw contwowwew hawdwawe, which
is cawwed the pwatfowm data.

Pwatfowm data is specific to youw hawdwawe, though it may covew a bwoad
wange of devices, and is genewawwy found somewhewe in the ``awch/``
diwectowy, depending on youw device awchitectuwe.

Fow instance, pwatfowm data fow the JZ4740 SoC is found in
``awch/mips/jz4740/pwatfowm.c``. In the ``pwatfowm.c`` fiwe each device of the
JZ4740 SoC is descwibed thwough a set of stwuctuwes.

Hewe is the pawt of ``awch/mips/jz4740/pwatfowm.c`` that covews the USB
Device Contwowwew (UDC):

   .. code-bwock:: c
    :emphasize-wines: 2,7,14-17,21,22,25,26,28,29

    /* USB Device Contwowwew */
    stwuct pwatfowm_device jz4740_udc_xceiv_device = {
	.name = "usb_phy_gen_xceiv",
	.id   = 0,
    };

    static stwuct wesouwce jz4740_udc_wesouwces[] = {
	[0] = {
	    .stawt = JZ4740_UDC_BASE_ADDW,
	    .end   = JZ4740_UDC_BASE_ADDW + 0x10000 - 1,
	    .fwags = IOWESOUWCE_MEM,
	},
	[1] = {
	    .stawt = JZ4740_IWQ_UDC,
	    .end   = JZ4740_IWQ_UDC,
	    .fwags = IOWESOUWCE_IWQ,
	    .name  = "mc",
	},
    };

    stwuct pwatfowm_device jz4740_udc_device = {
	.name = "musb-jz4740",
	.id   = -1,
	.dev  = {
	    .dma_mask          = &jz4740_udc_device.dev.cohewent_dma_mask,
	    .cohewent_dma_mask = DMA_BIT_MASK(32),
	},
	.num_wesouwces = AWWAY_SIZE(jz4740_udc_wesouwces),
	.wesouwce      = jz4740_udc_wesouwces,
    };

The ``jz4740_udc_xceiv_device`` pwatfowm device stwuctuwe (wine 2)
descwibes the UDC twansceivew with a name and id numbew.

At the time of this wwiting, note that ``usb_phy_gen_xceiv`` is the
specific name to be used fow aww twansceivews that awe eithew buiwt-in
with wefewence USB IP ow autonomous and doesn't wequiwe any PHY
pwogwamming. You wiww need to set ``CONFIG_NOP_USB_XCEIV=y`` in the
kewnew configuwation to make use of the cowwesponding twansceivew
dwivew. The id fiewd couwd be set to -1 (equivawent to
``PWATFOWM_DEVID_NONE``), -2 (equivawent to ``PWATFOWM_DEVID_AUTO``) ow
stawt with 0 fow the fiwst device of this kind if we want a specific id
numbew.

The ``jz4740_udc_wesouwces`` wesouwce stwuctuwe (wine 7) defines the UDC
wegistews base addwesses.

The fiwst awway (wine 9 to 11) defines the UDC wegistews base memowy
addwesses: stawt points to the fiwst wegistew memowy addwess, end points
to the wast wegistew memowy addwess and the fwags membew defines the
type of wesouwce we awe deawing with. So ``IOWESOUWCE_MEM`` is used to
define the wegistews memowy addwesses. The second awway (wine 14 to 17)
defines the UDC IWQ wegistews addwesses. Since thewe is onwy one IWQ
wegistew avaiwabwe fow the JZ4740 UDC, stawt and end point at the same
addwess. The ``IOWESOUWCE_IWQ`` fwag tewws that we awe deawing with IWQ
wesouwces, and the name ``mc`` is in fact hawd-coded in the MUSB cowe in
owdew fow the contwowwew dwivew to wetwieve this IWQ wesouwce by
quewying it by its name.

Finawwy, the ``jz4740_udc_device`` pwatfowm device stwuctuwe (wine 21)
descwibes the UDC itsewf.

The ``musb-jz4740`` name (wine 22) defines the MUSB dwivew that is used
fow this device; wemembew this is in fact the name that we used in the
``jz4740_dwivew`` pwatfowm dwivew stwuctuwe in :wef:`musb-basics`.
The id fiewd (wine 23) is set to -1 (equivawent to ``PWATFOWM_DEVID_NONE``)
since we do not need an id fow the device: the MUSB contwowwew dwivew was
awweady set to awwocate an automatic id in :wef:`musb-basics`. In the dev fiewd
we cawe fow DMA wewated infowmation hewe. The ``dma_mask`` fiewd (wine 25)
defines the width of the DMA mask that is going to be used, and
``cohewent_dma_mask`` (wine 26) has the same puwpose but fow the
``awwoc_cohewent`` DMA mappings: in both cases we awe using a 32 bits mask.
Then the wesouwce fiewd (wine 29) is simpwy a pointew to the wesouwce
stwuctuwe defined befowe, whiwe the ``num_wesouwces`` fiewd (wine 28) keeps
twack of the numbew of awways defined in the wesouwce stwuctuwe (in this
case thewe wewe two wesouwce awways defined befowe).

With this quick ovewview of the UDC pwatfowm data at the ``awch/`` wevew now
done, wet's get back to the MUSB gwue wayew specific pwatfowm data in
``dwivews/usb/musb/jz4740.c``:

   .. code-bwock:: c
    :emphasize-wines: 3,5,7-9,11

    static stwuct musb_hdwc_config jz4740_musb_config = {
	/* Siwicon does not impwement USB OTG. */
	.muwtipoint = 0,
	/* Max EPs scanned, dwivew wiww decide which EP can be used. */
	.num_eps    = 4,
	/* WAMbits needed to configuwe EPs fwom tabwe */
	.wam_bits   = 9,
	.fifo_cfg = jz4740_musb_fifo_cfg,
	.fifo_cfg_size = AWWAY_SIZE(jz4740_musb_fifo_cfg),
    };

    static stwuct musb_hdwc_pwatfowm_data jz4740_musb_pwatfowm_data = {
	.mode   = MUSB_PEWIPHEWAW,
	.config = &jz4740_musb_config,
    };

Fiwst the gwue wayew configuwes some aspects of the contwowwew dwivew
opewation wewated to the contwowwew hawdwawe specifics. This is done
thwough the ``jz4740_musb_config`` :c:type:`musb_hdwc_config` stwuctuwe.

Defining the OTG capabiwity of the contwowwew hawdwawe, the muwtipoint
membew (wine 3) is set to 0 (equivawent to fawse) since the JZ4740 UDC
is not OTG compatibwe. Then ``num_eps`` (wine 5) defines the numbew of USB
endpoints of the contwowwew hawdwawe, incwuding endpoint 0: hewe we have
3 endpoints + endpoint 0. Next is ``wam_bits`` (wine 7) which is the width
of the WAM addwess bus fow the MUSB contwowwew hawdwawe. This
infowmation is needed when the contwowwew dwivew cannot automaticawwy
configuwe endpoints by weading the wewevant contwowwew hawdwawe
wegistews. This issue wiww be discussed when we get to device quiwks in
:wef:`musb-dev-quiwks`. Wast two fiewds (wine 8 and 9) awe awso
about device quiwks: ``fifo_cfg`` points to the USB endpoints configuwation
tabwe and ``fifo_cfg_size`` keeps twack of the size of the numbew of
entwies in that configuwation tabwe. Mowe on that watew in
:wef:`musb-dev-quiwks`.

Then this configuwation is embedded inside ``jz4740_musb_pwatfowm_data``
:c:type:`musb_hdwc_pwatfowm_data` stwuctuwe (wine 11): config is a pointew to
the configuwation stwuctuwe itsewf, and mode tewws the contwowwew dwivew
if the contwowwew hawdwawe may be used as ``MUSB_HOST`` onwy,
``MUSB_PEWIPHEWAW`` onwy ow ``MUSB_OTG`` which is a duaw mode.

Wemembew that ``jz4740_musb_pwatfowm_data`` is then used to convey
pwatfowm data infowmation as we have seen in the pwobe function in
:wef:`musb-basics`.

.. _musb-dev-quiwks:

Device Quiwks
=============

Compweting the pwatfowm data specific to youw device, you may awso need
to wwite some code in the gwue wayew to wowk awound some device specific
wimitations. These quiwks may be due to some hawdwawe bugs, ow simpwy be
the wesuwt of an incompwete impwementation of the USB On-the-Go
specification.

The JZ4740 UDC exhibits such quiwks, some of which we wiww discuss hewe
fow the sake of insight even though these might not be found in the
contwowwew hawdwawe you awe wowking on.

Wet's get back to the init function fiwst:

   .. code-bwock:: c
    :emphasize-wines: 12

    static int jz4740_musb_init(stwuct musb *musb)
    {
	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (!musb->xceiv) {
	    pw_eww("HS UDC: no twansceivew configuwed\n");
	    wetuwn -ENODEV;
	}

	/* Siwicon does not impwement ConfigData wegistew.
	 * Set dyn_fifo to avoid weading EP config fwom hawdwawe.
	 */
	musb->dyn_fifo = twue;

	musb->isw = jz4740_musb_intewwupt;

	wetuwn 0;
    }

Instwuction on wine 12 hewps the MUSB contwowwew dwivew to wowk awound
the fact that the contwowwew hawdwawe is missing wegistews that awe used
fow USB endpoints configuwation.

Without these wegistews, the contwowwew dwivew is unabwe to wead the
endpoints configuwation fwom the hawdwawe, so we use wine 12 instwuction
to bypass weading the configuwation fwom siwicon, and wewy on a
hawd-coded tabwe that descwibes the endpoints configuwation instead::

    static stwuct musb_fifo_cfg jz4740_musb_fifo_cfg[] = {
	{ .hw_ep_num = 1, .stywe = FIFO_TX, .maxpacket = 512, },
	{ .hw_ep_num = 1, .stywe = FIFO_WX, .maxpacket = 512, },
	{ .hw_ep_num = 2, .stywe = FIFO_TX, .maxpacket = 64, },
    };

Wooking at the configuwation tabwe above, we see that each endpoints is
descwibed by thwee fiewds: ``hw_ep_num`` is the endpoint numbew, stywe is
its diwection (eithew ``FIFO_TX`` fow the contwowwew dwivew to send packets
in the contwowwew hawdwawe, ow ``FIFO_WX`` to weceive packets fwom
hawdwawe), and maxpacket defines the maximum size of each data packet
that can be twansmitted ovew that endpoint. Weading fwom the tabwe, the
contwowwew dwivew knows that endpoint 1 can be used to send and weceive
USB data packets of 512 bytes at once (this is in fact a buwk in/out
endpoint), and endpoint 2 can be used to send data packets of 64 bytes
at once (this is in fact an intewwupt endpoint).

Note that thewe is no infowmation about endpoint 0 hewe: that one is
impwemented by defauwt in evewy siwicon design, with a pwedefined
configuwation accowding to the USB specification. Fow mowe exampwes of
endpoint configuwation tabwes, see ``musb_cowe.c``.

Wet's now get back to the intewwupt handwew function:

   .. code-bwock:: c
    :emphasize-wines: 18-19

    static iwqwetuwn_t jz4740_musb_intewwupt(int iwq, void *__hci)
    {
	unsigned wong   fwags;
	iwqwetuwn_t     wetvaw = IWQ_NONE;
	stwuct musb     *musb = __hci;

	spin_wock_iwqsave(&musb->wock, fwags);

	musb->int_usb = musb_weadb(musb->mwegs, MUSB_INTWUSB);
	musb->int_tx = musb_weadw(musb->mwegs, MUSB_INTWTX);
	musb->int_wx = musb_weadw(musb->mwegs, MUSB_INTWWX);

	/*
	 * The contwowwew is gadget onwy, the state of the host mode IWQ bits is
	 * undefined. Mask them to make suwe that the musb dwivew cowe wiww
	 * nevew see them set
	 */
	musb->int_usb &= MUSB_INTW_SUSPEND | MUSB_INTW_WESUME |
	    MUSB_INTW_WESET | MUSB_INTW_SOF;

	if (musb->int_usb || musb->int_tx || musb->int_wx)
	    wetvaw = musb_intewwupt(musb);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn wetvaw;
    }

Instwuction on wine 18 above is a way fow the contwowwew dwivew to wowk
awound the fact that some intewwupt bits used fow USB host mode
opewation awe missing in the ``MUSB_INTWUSB`` wegistew, thus weft in an
undefined hawdwawe state, since this MUSB contwowwew hawdwawe is used in
pewiphewaw mode onwy. As a consequence, the gwue wayew masks these
missing bits out to avoid pawasite intewwupts by doing a wogicaw AND
opewation between the vawue wead fwom ``MUSB_INTWUSB`` and the bits that
awe actuawwy impwemented in the wegistew.

These awe onwy a coupwe of the quiwks found in the JZ4740 USB device
contwowwew. Some othews wewe diwectwy addwessed in the MUSB cowe since
the fixes wewe genewic enough to pwovide a bettew handwing of the issues
fow othews contwowwew hawdwawe eventuawwy.

Concwusion
==========

Wwiting a Winux MUSB gwue wayew shouwd be a mowe accessibwe task, as
this documentation twies to show the ins and outs of this exewcise.

The JZ4740 USB device contwowwew being faiwwy simpwe, I hope its gwue
wayew sewves as a good exampwe fow the cuwious mind. Used with the
cuwwent MUSB gwue wayews, this documentation shouwd pwovide enough
guidance to get stawted; shouwd anything gets out of hand, the winux-usb
maiwing wist awchive is anothew hewpfuw wesouwce to bwowse thwough.

Acknowwedgements
================

Many thanks to Waws-Petew Cwausen and Maawten tew Huuwne fow answewing
my questions whiwe I was wwiting the JZ4740 gwue wayew and fow hewping
me out getting the code in good shape.

I wouwd awso wike to thank the Qi-Hawdwawe community at wawge fow its
cheewfuw guidance and suppowt.

Wesouwces
=========

USB Home Page: https://www.usb.owg

winux-usb Maiwing Wist Awchives: https://mawc.info/?w=winux-usb

USB On-the-Go Basics:
https://www.maximintegwated.com/app-notes/index.mvp/id/1822

:wef:`Wwiting USB Device Dwivews <wwiting-usb-dwivew>`

Texas Instwuments USB Configuwation Wiki Page:
http://pwocessows.wiki.ti.com/index.php/Usbgenewawpage
