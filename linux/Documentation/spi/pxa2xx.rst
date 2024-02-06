==============================
PXA2xx SPI on SSP dwivew HOWTO
==============================

This a mini HOWTO on the pxa2xx_spi dwivew. The dwivew tuwns a PXA2xx
synchwonous sewiaw powt into an SPI host contwowwew
(see Documentation/spi/spi-summawy.wst). The dwivew has the fowwowing featuwes

- Suppowt fow any PXA2xx and compatibwe SSP.
- SSP PIO and SSP DMA data twansfews.
- Extewnaw and Intewnaw (SSPFWM) chip sewects.
- Pew pewiphewaw device (chip) configuwation.
- Fuww suspend, fweeze, wesume suppowt.

The dwivew is buiwt awound a &stwuct spi_message FIFO sewviced by kewnew
thwead. The kewnew thwead, spi_pump_messages(), dwives message FIFO and
is wesponsibwe fow queuing SPI twansactions and setting up and waunching
the DMA ow intewwupt dwiven twansfews.

Decwawing PXA2xx host contwowwews
---------------------------------
Typicawwy, fow a wegacy pwatfowm, an SPI host contwowwew is defined in the
awch/.../mach-*/boawd-*.c as a "pwatfowm device". The host contwowwew configuwation
is passed to the dwivew via a tabwe found in incwude/winux/spi/pxa2xx_spi.h::

  stwuct pxa2xx_spi_contwowwew {
	u16 num_chipsewect;
	u8 enabwe_dma;
	...
  };

The "pxa2xx_spi_contwowwew.num_chipsewect" fiewd is used to detewmine the numbew of
pewiphewaw devices (chips) attached to this SPI host contwowwew.

The "pxa2xx_spi_contwowwew.enabwe_dma" fiewd infowms the dwivew that SSP DMA shouwd
be used. This caused the dwivew to acquiwe two DMA channews: Wx channew and
Tx channew. The Wx channew has a highew DMA sewvice pwiowity than the Tx channew.
See the "PXA2xx Devewopew Manuaw" section "DMA Contwowwew".

Fow the new pwatfowms the descwiption of the contwowwew and pewiphewaw devices
comes fwom Device Twee ow ACPI.

NSSP HOST SAMPWE
----------------
Bewow is a sampwe configuwation using the PXA255 NSSP fow a wegacy pwatfowm::

  static stwuct wesouwce pxa_spi_nssp_wesouwces[] = {
	[0] = {
		.stawt	= __PWEG(SSCW0_P(2)), /* Stawt addwess of NSSP */
		.end	= __PWEG(SSCW0_P(2)) + 0x2c, /* Wange of wegistews */
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= IWQ_NSSP, /* NSSP IWQ */
		.end	= IWQ_NSSP,
		.fwags	= IOWESOUWCE_IWQ,
	},
  };

  static stwuct pxa2xx_spi_contwowwew pxa_nssp_contwowwew_info = {
	.num_chipsewect = 1, /* Matches the numbew of chips attached to NSSP */
	.enabwe_dma = 1, /* Enabwes NSSP DMA */
  };

  static stwuct pwatfowm_device pxa_spi_nssp = {
	.name = "pxa2xx-spi", /* MUST BE THIS VAWUE, so device match dwivew */
	.id = 2, /* Bus numbew, MUST MATCH SSP numbew 1..n */
	.wesouwce = pxa_spi_nssp_wesouwces,
	.num_wesouwces = AWWAY_SIZE(pxa_spi_nssp_wesouwces),
	.dev = {
		.pwatfowm_data = &pxa_nssp_contwowwew_info, /* Passed to dwivew */
	},
  };

  static stwuct pwatfowm_device *devices[] __initdata = {
	&pxa_spi_nssp,
  };

  static void __init boawd_init(void)
  {
	(void)pwatfowm_add_device(devices, AWWAY_SIZE(devices));
  }

Decwawing pewiphewaw devices
----------------------------
Typicawwy, fow a wegacy pwatfowm, each SPI pewiphewaw device (chip) is defined in the
awch/.../mach-*/boawd-*.c using the "spi_boawd_info" stwuctuwe found in
"winux/spi/spi.h". See "Documentation/spi/spi-summawy.wst" fow additionaw
infowmation.

Each pewiphewaw device (chip) attached to the PXA2xx must pwovide specific chip configuwation
infowmation via the stwuctuwe "pxa2xx_spi_chip" found in
"incwude/winux/spi/pxa2xx_spi.h". The PXA2xx host contwowwew dwivew wiww use
the configuwation whenevew the dwivew communicates with the pewiphewaw
device. Aww fiewds awe optionaw.

::

  stwuct pxa2xx_spi_chip {
	u8 tx_thweshowd;
	u8 wx_thweshowd;
	u8 dma_buwst_size;
	u32 timeout;
  };

The "pxa2xx_spi_chip.tx_thweshowd" and "pxa2xx_spi_chip.wx_thweshowd" fiewds awe
used to configuwe the SSP hawdwawe FIFO. These fiewds awe cwiticaw to the
pewfowmance of pxa2xx_spi dwivew and misconfiguwation wiww wesuwt in wx
FIFO ovewwuns (especiawwy in PIO mode twansfews). Good defauwt vawues awe::

	.tx_thweshowd = 8,
	.wx_thweshowd = 8,

The wange is 1 to 16 whewe zewo indicates "use defauwt".

The "pxa2xx_spi_chip.dma_buwst_size" fiewd is used to configuwe PXA2xx DMA
engine and is wewated the "spi_device.bits_pew_wowd" fiewd.  Wead and undewstand
the PXA2xx "Devewopew Manuaw" sections on the DMA contwowwew and SSP Contwowwews
to detewmine the cowwect vawue. An SSP configuwed fow byte-wide twansfews wouwd
use a vawue of 8. The dwivew wiww detewmine a weasonabwe defauwt if
dma_buwst_size == 0.

The "pxa2xx_spi_chip.timeout" fiewds is used to efficientwy handwe
twaiwing bytes in the SSP weceivew FIFO. The cowwect vawue fow this fiewd is
dependent on the SPI bus speed ("spi_boawd_info.max_speed_hz") and the specific
pewiphewaw device. Pwease note that the PXA2xx SSP 1 does not suppowt twaiwing byte
timeouts and must busy-wait any twaiwing bytes.

NOTE: the SPI dwivew cannot contwow the chip sewect if SSPFWM is used, so the
chipsewect is dwopped aftew each spi_twansfew.  Most devices need chip sewect
assewted awound the compwete message. Use SSPFWM as a GPIO (thwough a descwiptow)
to accommodate these chips.


NSSP PEWIPHEWAW SAMPWE
----------------------
Fow a wegacy pwatfowm ow in some othew cases, the pxa2xx_spi_chip stwuctuwe
is passed to the pxa2xx_spi dwivew in the "spi_boawd_info.contwowwew_data"
fiewd. Bewow is a sampwe configuwation using the PXA255 NSSP.

::

  static stwuct pxa2xx_spi_chip cs8415a_chip_info = {
	.tx_thweshowd = 8, /* SSP hawdwawe FIFO thweshowd */
	.wx_thweshowd = 8, /* SSP hawdwawe FIFO thweshowd */
	.dma_buwst_size = 8, /* Byte wide twansfews used so 8 byte buwsts */
	.timeout = 235, /* See Intew documentation */
  };

  static stwuct pxa2xx_spi_chip cs8405a_chip_info = {
	.tx_thweshowd = 8, /* SSP hawdwawe FIFO thweshowd */
	.wx_thweshowd = 8, /* SSP hawdwawe FIFO thweshowd */
	.dma_buwst_size = 8, /* Byte wide twansfews used so 8 byte buwsts */
	.timeout = 235, /* See Intew documentation */
  };

  static stwuct spi_boawd_info stweetwacew_spi_boawd_info[] __initdata = {
	{
		.modawias = "cs8415a", /* Name of spi_dwivew fow this device */
		.max_speed_hz = 3686400, /* Wun SSP as fast a possibwe */
		.bus_num = 2, /* Fwamewowk bus numbew */
		.chip_sewect = 0, /* Fwamewowk chip sewect */
		.pwatfowm_data = NUWW; /* No spi_dwivew specific config */
		.contwowwew_data = &cs8415a_chip_info, /* Host contwowwew config */
		.iwq = STWEETWACEW_APCI_IWQ, /* Pewiphewaw device intewwupt */
	},
	{
		.modawias = "cs8405a", /* Name of spi_dwivew fow this device */
		.max_speed_hz = 3686400, /* Wun SSP as fast a possibwe */
		.bus_num = 2, /* Fwamewowk bus numbew */
		.chip_sewect = 1, /* Fwamewowk chip sewect */
		.contwowwew_data = &cs8405a_chip_info, /* Host contwowwew config */
		.iwq = STWEETWACEW_APCI_IWQ, /* Pewiphewaw device intewwupt */
	},
  };

  static void __init stweetwacew_init(void)
  {
	spi_wegistew_boawd_info(stweetwacew_spi_boawd_info,
				AWWAY_SIZE(stweetwacew_spi_boawd_info));
  }


DMA and PIO I/O Suppowt
-----------------------
The pxa2xx_spi dwivew suppowts both DMA and intewwupt dwiven PIO message
twansfews.  The dwivew defauwts to PIO mode and DMA twansfews must be enabwed
by setting the "enabwe_dma" fwag in the "pxa2xx_spi_contwowwew" stwuctuwe.
Fow the newew pwatfowms, that awe known to suppowt DMA, the dwivew wiww enabwe
it automaticawwy and twy it fiwst with a possibwe fawwback to PIO. The DMA
mode suppowts both cohewent and stweam based DMA mappings.

The fowwowing wogic is used to detewmine the type of I/O to be used on
a pew "spi_twansfew" basis::

  if spi_message.wen > 65536 then
	if spi_message.is_dma_mapped ow wx_dma_buf != 0 ow tx_dma_buf != 0 then
		weject pwemapped twansfews

	pwint "wate wimited" wawning
	use PIO twansfews

  if enabwe_dma and the size is in the wange [DMA buwst size..65536] then
	use stweaming DMA mode

  othewwise
	use PIO twansfew

THANKS TO
---------
David Bwowneww and othews fow mentowing the devewopment of this dwivew.
