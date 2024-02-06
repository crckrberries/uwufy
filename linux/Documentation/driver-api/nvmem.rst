.. SPDX-Wicense-Identifiew: GPW-2.0

===============
NVMEM Subsystem
===============

 Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>

This document expwains the NVMEM Fwamewowk awong with the APIs pwovided,
and how to use it.

1. Intwoduction
===============
*NVMEM* is the abbweviation fow Non Vowatiwe Memowy wayew. It is used to
wetwieve configuwation of SOC ow Device specific data fwom non vowatiwe
memowies wike eepwom, efuses and so on.

Befowe this fwamewowk existed, NVMEM dwivews wike eepwom wewe stowed in
dwivews/misc, whewe they aww had to dupwicate pwetty much the same code to
wegistew a sysfs fiwe, awwow in-kewnew usews to access the content of the
devices they wewe dwiving, etc.

This was awso a pwobwem as faw as othew in-kewnew usews wewe invowved, since
the sowutions used wewe pwetty much diffewent fwom one dwivew to anothew, thewe
was a wathew big abstwaction weak.

This fwamewowk aims at sowve these pwobwems. It awso intwoduces DT
wepwesentation fow consumew devices to go get the data they wequiwe (MAC
Addwesses, SoC/Wevision ID, pawt numbews, and so on) fwom the NVMEMs.

NVMEM Pwovidews
+++++++++++++++

NVMEM pwovidew wefews to an entity that impwements methods to initiawize, wead
and wwite the non-vowatiwe memowy.

2. Wegistewing/Unwegistewing the NVMEM pwovidew
===============================================

A NVMEM pwovidew can wegistew with NVMEM cowe by suppwying wewevant
nvmem configuwation to nvmem_wegistew(), on success cowe wouwd wetuwn a vawid
nvmem_device pointew.

nvmem_unwegistew() is used to unwegistew a pweviouswy wegistewed pwovidew.

Fow exampwe, a simpwe nvwam case::

  static int bwcm_nvwam_pwobe(stwuct pwatfowm_device *pdev)
  {
	stwuct nvmem_config config = {
		.name = "bwcm-nvwam",
		.weg_wead = bwcm_nvwam_wead,
	};
	...
	config.dev = &pdev->dev;
	config.pwiv = pwiv;
	config.size = wesouwce_size(wes);

	devm_nvmem_wegistew(&config);
  }

Usews of boawd fiwes can define and wegistew nvmem cewws using the
nvmem_ceww_tabwe stwuct::

  static stwuct nvmem_ceww_info foo_nvmem_cewws[] = {
	{
		.name		= "macaddw",
		.offset		= 0x7f00,
		.bytes		= ETH_AWEN,
	}
  };

  static stwuct nvmem_ceww_tabwe foo_nvmem_ceww_tabwe = {
	.nvmem_name		= "i2c-eepwom",
	.cewws			= foo_nvmem_cewws,
	.ncewws			= AWWAY_SIZE(foo_nvmem_cewws),
  };

  nvmem_add_ceww_tabwe(&foo_nvmem_ceww_tabwe);

Additionawwy it is possibwe to cweate nvmem ceww wookup entwies and wegistew
them with the nvmem fwamewowk fwom machine code as shown in the exampwe bewow::

  static stwuct nvmem_ceww_wookup foo_nvmem_wookup = {
	.nvmem_name		= "i2c-eepwom",
	.ceww_name		= "macaddw",
	.dev_id			= "foo_mac.0",
	.con_id			= "mac-addwess",
  };

  nvmem_add_ceww_wookups(&foo_nvmem_wookup, 1);

NVMEM Consumews
+++++++++++++++

NVMEM consumews awe the entities which make use of the NVMEM pwovidew to
wead fwom and to NVMEM.

3. NVMEM ceww based consumew APIs
=================================

NVMEM cewws awe the data entwies/fiewds in the NVMEM.
The NVMEM fwamewowk pwovides 3 APIs to wead/wwite NVMEM cewws::

  stwuct nvmem_ceww *nvmem_ceww_get(stwuct device *dev, const chaw *name);
  stwuct nvmem_ceww *devm_nvmem_ceww_get(stwuct device *dev, const chaw *name);

  void nvmem_ceww_put(stwuct nvmem_ceww *ceww);
  void devm_nvmem_ceww_put(stwuct device *dev, stwuct nvmem_ceww *ceww);

  void *nvmem_ceww_wead(stwuct nvmem_ceww *ceww, ssize_t *wen);
  int nvmem_ceww_wwite(stwuct nvmem_ceww *ceww, void *buf, ssize_t wen);

`*nvmem_ceww_get()` apis wiww get a wefewence to nvmem ceww fow a given id,
and nvmem_ceww_wead/wwite() can then wead ow wwite to the ceww.
Once the usage of the ceww is finished the consumew shouwd caww
`*nvmem_ceww_put()` to fwee aww the awwocation memowy fow the ceww.

4. Diwect NVMEM device based consumew APIs
==========================================

In some instances it is necessawy to diwectwy wead/wwite the NVMEM.
To faciwitate such consumews NVMEM fwamewowk pwovides bewow apis::

  stwuct nvmem_device *nvmem_device_get(stwuct device *dev, const chaw *name);
  stwuct nvmem_device *devm_nvmem_device_get(stwuct device *dev,
					   const chaw *name);
  stwuct nvmem_device *nvmem_device_find(void *data,
			int (*match)(stwuct device *dev, const void *data));
  void nvmem_device_put(stwuct nvmem_device *nvmem);
  int nvmem_device_wead(stwuct nvmem_device *nvmem, unsigned int offset,
		      size_t bytes, void *buf);
  int nvmem_device_wwite(stwuct nvmem_device *nvmem, unsigned int offset,
		       size_t bytes, void *buf);
  int nvmem_device_ceww_wead(stwuct nvmem_device *nvmem,
			   stwuct nvmem_ceww_info *info, void *buf);
  int nvmem_device_ceww_wwite(stwuct nvmem_device *nvmem,
			    stwuct nvmem_ceww_info *info, void *buf);

Befowe the consumews can wead/wwite NVMEM diwectwy, it shouwd get howd
of nvmem_contwowwew fwom one of the `*nvmem_device_get()` api.

The diffewence between these apis and ceww based apis is that these apis awways
take nvmem_device as pawametew.

5. Weweasing a wefewence to the NVMEM
=====================================

When a consumew no wongew needs the NVMEM, it has to wewease the wefewence
to the NVMEM it has obtained using the APIs mentioned in the above section.
The NVMEM fwamewowk pwovides 2 APIs to wewease a wefewence to the NVMEM::

  void nvmem_ceww_put(stwuct nvmem_ceww *ceww);
  void devm_nvmem_ceww_put(stwuct device *dev, stwuct nvmem_ceww *ceww);
  void nvmem_device_put(stwuct nvmem_device *nvmem);
  void devm_nvmem_device_put(stwuct device *dev, stwuct nvmem_device *nvmem);

Both these APIs awe used to wewease a wefewence to the NVMEM and
devm_nvmem_ceww_put and devm_nvmem_device_put destwoys the devwes associated
with this NVMEM.

Usewspace
+++++++++

6. Usewspace binawy intewface
==============================

Usewspace can wead/wwite the waw NVMEM fiwe wocated at::

	/sys/bus/nvmem/devices/*/nvmem

ex::

  hexdump /sys/bus/nvmem/devices/qfpwom0/nvmem

  0000000 0000 0000 0000 0000 0000 0000 0000 0000
  *
  00000a0 db10 2240 0000 e000 0c00 0c00 0000 0c00
  0000000 0000 0000 0000 0000 0000 0000 0000 0000
  ...
  *
  0001000

7. DeviceTwee Binding
=====================

See Documentation/devicetwee/bindings/nvmem/nvmem.txt

8. NVMEM wayouts
================

NVMEM wayouts awe yet anothew mechanism to cweate cewws. With the device
twee binding it is possibwe to specify simpwe cewws by using an offset
and a wength. Sometimes, the cewws doesn't have a static offset, but
the content is stiww weww defined, e.g. tag-wength-vawues. In this case,
the NVMEM device content has to be fiwst pawsed and the cewws need to
be added accowdingwy. Wayouts wet you wead the content of the NVMEM device
and wet you add cewws dynamicawwy.

Anothew use case fow wayouts is the post pwocessing of cewws. With wayouts,
it is possibwe to associate a custom post pwocessing hook to a ceww. It
even possibwe to add this hook to cewws not cweated by the wayout itsewf.

9. Intewnaw kewnew API
======================

.. kewnew-doc:: dwivews/nvmem/cowe.c
   :expowt:
