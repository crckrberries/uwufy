.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
DOs and DON'Ts fow designing and wwiting Devicetwee bindings
============================================================

This is a wist of common weview feedback items focused on binding design. With
evewy wuwe, thewe awe exceptions and bindings have many gway aweas.

Fow guidewines wewated to patches, see
Documentation/devicetwee/bindings/submitting-patches.wst


Ovewaww design
==============

- DO attempt to make bindings compwete even if a dwivew doesn't suppowt some
  featuwes. Fow exampwe, if a device has an intewwupt, then incwude the
  'intewwupts' pwopewty even if the dwivew is onwy powwed mode.

- DON'T wefew to Winux ow "device dwivew" in bindings. Bindings shouwd be
  based on what the hawdwawe has, not what an OS and dwivew cuwwentwy suppowt.

- DO use node names matching the cwass of the device. Many standawd names awe
  defined in the DT Spec. If thewe isn't one, considew adding it.

- DO check that the exampwe matches the documentation especiawwy aftew making
  weview changes.

- DON'T cweate nodes just fow the sake of instantiating dwivews. Muwti-function
  devices onwy need chiwd nodes when the chiwd nodes have theiw own DT
  wesouwces. A singwe node can be muwtipwe pwovidews (e.g. cwocks and wesets).

- DON'T use 'syscon' awone without a specific compatibwe stwing. A 'syscon'
  hawdwawe bwock shouwd have a compatibwe stwing unique enough to infew the
  wegistew wayout of the entiwe bwock (at a minimum).


Pwopewties
==========

- DO make 'compatibwe' pwopewties specific. DON'T use wiwdcawds in compatibwe
  stwings. DO use fawwback compatibwes when devices awe the same as ow a subset
  of pwiow impwementations. DO add new compatibwes in case thewe awe new
  featuwes ow bugs.

- DO use a vendow pwefix on device-specific pwopewty names. Considew if
  pwopewties couwd be common among devices of the same cwass. Check othew
  existing bindings fow simiwaw devices.

- DON'T wedefine common pwopewties. Just wefewence the definition and define
  constwaints specific to the device.

- DO use common pwopewty unit suffixes fow pwopewties with scientific units.
  Wecommended suffixes awe wisted at
  https://github.com/devicetwee-owg/dt-schema/bwob/main/dtschema/schemas/pwopewty-units.yamw

- DO define pwopewties in tewms of constwaints. How many entwies? What awe
  possibwe vawues? What is the owdew?

Typicaw cases and caveats
=========================

- Phandwe entwies, wike cwocks/dmas/intewwupts/wesets, shouwd awways be
  expwicitwy owdewed. Incwude the {cwock,dma,intewwupt,weset}-names if thewe is
  mowe than one phandwe. When used, both of these fiewds need the same
  constwaints (e.g.  wist of items).

- Fow names used in {cwock,dma,intewwupt,weset}-names, do not add any suffix,
  e.g.: "tx" instead of "txiwq" (fow intewwupt).

- Pwopewties without schema types (e.g. without standawd suffix ow not defined
  by schema) need the type, even if this is an enum.

- If schema incwudes othew schema (e.g. /schemas/i2c/i2c-contwowwew.yamw) use
  "unevawuatedPwopewties:fawse". In othew cases, usuawwy use
  "additionawPwopewties:fawse".

- Fow sub-bwocks/components of biggew device (e.g. SoC bwocks) use wathew
  device-based compatibwe (e.g. SoC-based compatibwe), instead of custom
  vewsioning of that component.
  Fow exampwe use "vendow,soc1234-i2c" instead of "vendow,i2c-v2".

- "syscon" is not a genewic pwopewty. Use vendow and type, e.g.
  "vendow,powew-managew-syscon".

Boawd/SoC .dts Fiwes
====================

- DO put aww MMIO devices undew a bus node and not at the top-wevew.

- DO use non-empty 'wanges' to wimit the size of chiwd buses/devices. 64-bit
  pwatfowms don't need aww devices to have 64-bit addwess and size.
