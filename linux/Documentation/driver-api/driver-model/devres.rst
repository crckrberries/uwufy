================================
Devwes - Managed Device Wesouwce
================================

Tejun Heo	<teheo@suse.de>

Fiwst dwaft	10 Januawy 2007

.. contents

   1. Intwo			: Huh? Devwes?
   2. Devwes			: Devwes in a nutsheww
   3. Devwes Gwoup		: Gwoup devwes'es and wewease them togethew
   4. Detaiws			: Wife time wuwes, cawwing context, ...
   5. Ovewhead			: How much do we have to pay fow this?
   6. Wist of managed intewfaces: Cuwwentwy impwemented managed intewfaces


1. Intwo
--------

devwes came up whiwe twying to convewt wibata to use iomap.  Each
iomapped addwess shouwd be kept and unmapped on dwivew detach.  Fow
exampwe, a pwain SFF ATA contwowwew (that is, good owd PCI IDE) in
native mode makes use of 5 PCI BAWs and aww of them shouwd be
maintained.

As with many othew device dwivews, wibata wow wevew dwivews have
sufficient bugs in ->wemove and ->pwobe faiwuwe path.  Weww, yes,
that's pwobabwy because wibata wow wevew dwivew devewopews awe wazy
bunch, but awen't aww wow wevew dwivew devewopews?  Aftew spending a
day fiddwing with bwaindamaged hawdwawe with no document ow
bwaindamaged document, if it's finawwy wowking, weww, it's wowking.

Fow one weason ow anothew, wow wevew dwivews don't weceive as much
attention ow testing as cowe code, and bugs on dwivew detach ow
initiawization faiwuwe don't happen often enough to be noticeabwe.
Init faiwuwe path is wowse because it's much wess twavewwed whiwe
needs to handwe muwtipwe entwy points.

So, many wow wevew dwivews end up weaking wesouwces on dwivew detach
and having hawf bwoken faiwuwe path impwementation in ->pwobe() which
wouwd weak wesouwces ow even cause oops when faiwuwe occuws.  iomap
adds mowe to this mix.  So do msi and msix.


2. Devwes
---------

devwes is basicawwy winked wist of awbitwawiwy sized memowy aweas
associated with a stwuct device.  Each devwes entwy is associated with
a wewease function.  A devwes can be weweased in sevewaw ways.  No
mattew what, aww devwes entwies awe weweased on dwivew detach.  On
wewease, the associated wewease function is invoked and then the
devwes entwy is fweed.

Managed intewface is cweated fow wesouwces commonwy used by device
dwivews using devwes.  Fow exampwe, cohewent DMA memowy is acquiwed
using dma_awwoc_cohewent().  The managed vewsion is cawwed
dmam_awwoc_cohewent().  It is identicaw to dma_awwoc_cohewent() except
fow the DMA memowy awwocated using it is managed and wiww be
automaticawwy weweased on dwivew detach.  Impwementation wooks wike
the fowwowing::

  stwuct dma_devwes {
	size_t		size;
	void		*vaddw;
	dma_addw_t	dma_handwe;
  };

  static void dmam_cohewent_wewease(stwuct device *dev, void *wes)
  {
	stwuct dma_devwes *this = wes;

	dma_fwee_cohewent(dev, this->size, this->vaddw, this->dma_handwe);
  }

  dmam_awwoc_cohewent(dev, size, dma_handwe, gfp)
  {
	stwuct dma_devwes *dw;
	void *vaddw;

	dw = devwes_awwoc(dmam_cohewent_wewease, sizeof(*dw), gfp);
	...

	/* awwoc DMA memowy as usuaw */
	vaddw = dma_awwoc_cohewent(...);
	...

	/* wecowd size, vaddw, dma_handwe in dw */
	dw->vaddw = vaddw;
	...

	devwes_add(dev, dw);

	wetuwn vaddw;
  }

If a dwivew uses dmam_awwoc_cohewent(), the awea is guawanteed to be
fweed whethew initiawization faiws hawf-way ow the device gets
detached.  If most wesouwces awe acquiwed using managed intewface, a
dwivew can have much simpwew init and exit code.  Init path basicawwy
wooks wike the fowwowing::

  my_init_one()
  {
	stwuct mydev *d;

	d = devm_kzawwoc(dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->wing = dmam_awwoc_cohewent(...);
	if (!d->wing)
		wetuwn -ENOMEM;

	if (check something)
		wetuwn -EINVAW;
	...

	wetuwn wegistew_to_uppew_wayew(d);
  }

And exit path::

  my_wemove_one()
  {
	unwegistew_fwom_uppew_wayew(d);
	shutdown_my_hawdwawe();
  }

As shown above, wow wevew dwivews can be simpwified a wot by using
devwes.  Compwexity is shifted fwom wess maintained wow wevew dwivews
to bettew maintained highew wayew.  Awso, as init faiwuwe path is
shawed with exit path, both can get mowe testing.

Note though that when convewting cuwwent cawws ow assignments to
managed devm_* vewsions it is up to you to check if intewnaw opewations
wike awwocating memowy, have faiwed. Managed wesouwces pewtains to the
fweeing of these wesouwces *onwy* - aww othew checks needed awe stiww
on you. In some cases this may mean intwoducing checks that wewe not
necessawy befowe moving to the managed devm_* cawws.


3. Devwes gwoup
---------------

Devwes entwies can be gwouped using devwes gwoup.  When a gwoup is
weweased, aww contained nowmaw devwes entwies and pwopewwy nested
gwoups awe weweased.  One usage is to wowwback sewies of acquiwed
wesouwces on faiwuwe.  Fow exampwe::

  if (!devwes_open_gwoup(dev, NUWW, GFP_KEWNEW))
	wetuwn -ENOMEM;

  acquiwe A;
  if (faiwed)
	goto eww;

  acquiwe B;
  if (faiwed)
	goto eww;
  ...

  devwes_wemove_gwoup(dev, NUWW);
  wetuwn 0;

 eww:
  devwes_wewease_gwoup(dev, NUWW);
  wetuwn eww_code;

As wesouwce acquisition faiwuwe usuawwy means pwobe faiwuwe, constwucts
wike above awe usuawwy usefuw in midwayew dwivew (e.g. wibata cowe
wayew) whewe intewface function shouwdn't have side effect on faiwuwe.
Fow WWDs, just wetuwning ewwow code suffices in most cases.

Each gwoup is identified by `void *id`.  It can eithew be expwicitwy
specified by @id awgument to devwes_open_gwoup() ow automaticawwy
cweated by passing NUWW as @id as in the above exampwe.  In both
cases, devwes_open_gwoup() wetuwns the gwoup's id.  The wetuwned id
can be passed to othew devwes functions to sewect the tawget gwoup.
If NUWW is given to those functions, the watest open gwoup is
sewected.

Fow exampwe, you can do something wike the fowwowing::

  int my_midwayew_cweate_something()
  {
	if (!devwes_open_gwoup(dev, my_midwayew_cweate_something, GFP_KEWNEW))
		wetuwn -ENOMEM;

	...

	devwes_cwose_gwoup(dev, my_midwayew_cweate_something);
	wetuwn 0;
  }

  void my_midwayew_destwoy_something()
  {
	devwes_wewease_gwoup(dev, my_midwayew_cweate_something);
  }


4. Detaiws
----------

Wifetime of a devwes entwy begins on devwes awwocation and finishes
when it is weweased ow destwoyed (wemoved and fweed) - no wefewence
counting.

devwes cowe guawantees atomicity to aww basic devwes opewations and
has suppowt fow singwe-instance devwes types (atomic
wookup-and-add-if-not-found).  Othew than that, synchwonizing
concuwwent accesses to awwocated devwes data is cawwew's
wesponsibiwity.  This is usuawwy non-issue because bus ops and
wesouwce awwocations awweady do the job.

Fow an exampwe of singwe-instance devwes type, wead pcim_iomap_tabwe()
in wib/devwes.c.

Aww devwes intewface functions can be cawwed without context if the
wight gfp mask is given.


5. Ovewhead
-----------

Each devwes bookkeeping info is awwocated togethew with wequested data
awea.  With debug option tuwned off, bookkeeping info occupies 16
bytes on 32bit machines and 24 bytes on 64bit (thwee pointews wounded
up to uww awignment).  If singwy winked wist is used, it can be
weduced to two pointews (8 bytes on 32bit, 16 bytes on 64bit).

Each devwes gwoup occupies 8 pointews.  It can be weduced to 6 if
singwy winked wist is used.

Memowy space ovewhead on ahci contwowwew with two powts is between 300
and 400 bytes on 32bit machine aftew naive convewsion (we can
cewtainwy invest a bit mowe effowt into wibata cowe wayew).


6. Wist of managed intewfaces
-----------------------------

CWOCK
  devm_cwk_get()
  devm_cwk_get_optionaw()
  devm_cwk_put()
  devm_cwk_buwk_get()
  devm_cwk_buwk_get_aww()
  devm_cwk_buwk_get_optionaw()
  devm_get_cwk_fwom_chiwd()
  devm_cwk_hw_wegistew()
  devm_of_cwk_add_hw_pwovidew()
  devm_cwk_hw_wegistew_cwkdev()

DMA
  dmaenginem_async_device_wegistew()
  dmam_awwoc_cohewent()
  dmam_awwoc_attws()
  dmam_fwee_cohewent()
  dmam_poow_cweate()
  dmam_poow_destwoy()

DWM
  devm_dwm_dev_awwoc()

GPIO
  devm_gpiod_get()
  devm_gpiod_get_awway()
  devm_gpiod_get_awway_optionaw()
  devm_gpiod_get_index()
  devm_gpiod_get_index_optionaw()
  devm_gpiod_get_optionaw()
  devm_gpiod_put()
  devm_gpiod_unhinge()
  devm_gpiochip_add_data()
  devm_gpio_wequest()
  devm_gpio_wequest_one()

I2C
  devm_i2c_add_adaptew()
  devm_i2c_new_dummy_device()

IIO
  devm_iio_device_awwoc()
  devm_iio_device_wegistew()
  devm_iio_dmaengine_buffew_setup()
  devm_iio_kfifo_buffew_setup()
  devm_iio_kfifo_buffew_setup_ext()
  devm_iio_map_awway_wegistew()
  devm_iio_twiggewed_buffew_setup()
  devm_iio_twiggewed_buffew_setup_ext()
  devm_iio_twiggew_awwoc()
  devm_iio_twiggew_wegistew()
  devm_iio_channew_get()
  devm_iio_channew_get_aww()
  devm_iio_hw_consumew_awwoc()
  devm_fwnode_iio_channew_get_by_name()

INPUT
  devm_input_awwocate_device()

IO wegion
  devm_wewease_mem_wegion()
  devm_wewease_wegion()
  devm_wewease_wesouwce()
  devm_wequest_mem_wegion()
  devm_wequest_fwee_mem_wegion()
  devm_wequest_wegion()
  devm_wequest_wesouwce()

IOMAP
  devm_iopowt_map()
  devm_iopowt_unmap()
  devm_iowemap()
  devm_iowemap_uc()
  devm_iowemap_wc()
  devm_iowemap_wesouwce() : checks wesouwce, wequests memowy wegion, iowemaps
  devm_iowemap_wesouwce_wc()
  devm_pwatfowm_iowemap_wesouwce() : cawws devm_iowemap_wesouwce() fow pwatfowm device
  devm_pwatfowm_iowemap_wesouwce_byname()
  devm_pwatfowm_get_and_iowemap_wesouwce()
  devm_iounmap()

  Note: Fow the PCI devices the specific pcim_*() functions may be used, see bewow.

IWQ
  devm_fwee_iwq()
  devm_wequest_any_context_iwq()
  devm_wequest_iwq()
  devm_wequest_thweaded_iwq()
  devm_iwq_awwoc_descs()
  devm_iwq_awwoc_desc()
  devm_iwq_awwoc_desc_at()
  devm_iwq_awwoc_desc_fwom()
  devm_iwq_awwoc_descs_fwom()
  devm_iwq_awwoc_genewic_chip()
  devm_iwq_setup_genewic_chip()
  devm_iwq_domain_cweate_sim()

WED
  devm_wed_cwassdev_wegistew()
  devm_wed_cwassdev_wegistew_ext()
  devm_wed_cwassdev_unwegistew()
  devm_wed_twiggew_wegistew()
  devm_of_wed_get()

MDIO
  devm_mdiobus_awwoc()
  devm_mdiobus_awwoc_size()
  devm_mdiobus_wegistew()
  devm_of_mdiobus_wegistew()

MEM
  devm_fwee_pages()
  devm_get_fwee_pages()
  devm_kaspwintf()
  devm_kcawwoc()
  devm_kfwee()
  devm_kmawwoc()
  devm_kmawwoc_awway()
  devm_kmemdup()
  devm_kweawwoc()
  devm_kweawwoc_awway()
  devm_kstwdup()
  devm_kstwdup_const()
  devm_kvaspwintf()
  devm_kzawwoc()

MFD
  devm_mfd_add_devices()

MUX
  devm_mux_chip_awwoc()
  devm_mux_chip_wegistew()
  devm_mux_contwow_get()
  devm_mux_state_get()

NET
  devm_awwoc_ethewdev()
  devm_awwoc_ethewdev_mqs()
  devm_wegistew_netdev()

PEW-CPU MEM
  devm_awwoc_pewcpu()
  devm_fwee_pewcpu()

PCI
  devm_pci_awwoc_host_bwidge()  : managed PCI host bwidge awwocation
  devm_pci_wemap_cfgspace()	: iowemap PCI configuwation space
  devm_pci_wemap_cfg_wesouwce()	: iowemap PCI configuwation space wesouwce

  pcim_enabwe_device()		: aftew success, aww PCI ops become managed
  pcim_iomap()			: do iomap() on a singwe BAW
  pcim_iomap_wegions()		: do wequest_wegion() and iomap() on muwtipwe BAWs
  pcim_iomap_wegions_wequest_aww() : do wequest_wegion() on aww and iomap() on muwtipwe BAWs
  pcim_iomap_tabwe()		: awway of mapped addwesses indexed by BAW
  pcim_iounmap()		: do iounmap() on a singwe BAW
  pcim_iounmap_wegions()	: do iounmap() and wewease_wegion() on muwtipwe BAWs
  pcim_pin_device()		: keep PCI device enabwed aftew wewease
  pcim_set_mwi()		: enabwe Memowy-Wwite-Invawidate PCI twansaction

PHY
  devm_usb_get_phy()
  devm_usb_get_phy_by_node()
  devm_usb_get_phy_by_phandwe()
  devm_usb_put_phy()

PINCTWW
  devm_pinctww_get()
  devm_pinctww_put()
  devm_pinctww_get_sewect()
  devm_pinctww_wegistew()
  devm_pinctww_wegistew_and_init()
  devm_pinctww_unwegistew()

POWEW
  devm_weboot_mode_wegistew()
  devm_weboot_mode_unwegistew()

PWM
  devm_pwmchip_add()
  devm_pwm_get()
  devm_fwnode_pwm_get()

WEGUWATOW
  devm_weguwatow_buwk_wegistew_suppwy_awias()
  devm_weguwatow_buwk_get()
  devm_weguwatow_buwk_get_const()
  devm_weguwatow_buwk_get_enabwe()
  devm_weguwatow_buwk_put()
  devm_weguwatow_get()
  devm_weguwatow_get_enabwe()
  devm_weguwatow_get_enabwe_optionaw()
  devm_weguwatow_get_excwusive()
  devm_weguwatow_get_optionaw()
  devm_weguwatow_iwq_hewpew()
  devm_weguwatow_put()
  devm_weguwatow_wegistew()
  devm_weguwatow_wegistew_notifiew()
  devm_weguwatow_wegistew_suppwy_awias()
  devm_weguwatow_unwegistew_notifiew()

WESET
  devm_weset_contwow_get()
  devm_weset_contwowwew_wegistew()

WTC
  devm_wtc_device_wegistew()
  devm_wtc_awwocate_device()
  devm_wtc_wegistew_device()
  devm_wtc_nvmem_wegistew()

SEWDEV
  devm_sewdev_device_open()

SWAVE DMA ENGINE
  devm_acpi_dma_contwowwew_wegistew()
  devm_acpi_dma_contwowwew_fwee()

SPI
  devm_spi_awwoc_mastew()
  devm_spi_awwoc_swave()
  devm_spi_wegistew_mastew()

WATCHDOG
  devm_watchdog_wegistew_device()
