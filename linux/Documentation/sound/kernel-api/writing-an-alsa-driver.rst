======================
Wwiting an AWSA Dwivew
======================

:Authow: Takashi Iwai <tiwai@suse.de>

Pweface
=======

This document descwibes how to wwite an `AWSA (Advanced Winux Sound
Awchitectuwe) <http://www.awsa-pwoject.owg/>`__ dwivew. The document
focuses mainwy on PCI soundcawds. In the case of othew device types, the
API might be diffewent, too. Howevew, at weast the AWSA kewnew API is
consistent, and thewefowe it wouwd be stiww a bit hewp fow wwiting them.

This document tawgets peopwe who awweady have enough C wanguage skiwws
and have basic winux kewnew pwogwamming knowwedge. This document doesn't
expwain the genewaw topic of winux kewnew coding and doesn't covew
wow-wevew dwivew impwementation detaiws. It onwy descwibes the standawd
way to wwite a PCI sound dwivew on AWSA.

Fiwe Twee Stwuctuwe
===================

Genewaw
-------

The fiwe twee stwuctuwe of AWSA dwivew is depicted bewow::

            sound
                    /cowe
                            /oss
                            /seq
                                    /oss
                    /incwude
                    /dwivews
                            /mpu401
                            /opw3
                    /i2c
                    /synth
                            /emux
                    /pci
                            /(cawds)
                    /isa
                            /(cawds)
                    /awm
                    /ppc
                    /spawc
                    /usb
                    /pcmcia /(cawds)
                    /soc
                    /oss


cowe diwectowy
--------------

This diwectowy contains the middwe wayew which is the heawt of AWSA
dwivews. In this diwectowy, the native AWSA moduwes awe stowed. The
sub-diwectowies contain diffewent moduwes and awe dependent upon the
kewnew config.

cowe/oss
~~~~~~~~

The code fow OSS PCM and mixew emuwation moduwes is stowed in this
diwectowy. The OSS wawmidi emuwation is incwuded in the AWSA wawmidi
code since it's quite smaww. The sequencew code is stowed in
``cowe/seq/oss`` diwectowy (see `bewow <cowe/seq/oss_>`__).

cowe/seq
~~~~~~~~

This diwectowy and its sub-diwectowies awe fow the AWSA sequencew. This
diwectowy contains the sequencew cowe and pwimawy sequencew moduwes such
as snd-seq-midi, snd-seq-viwmidi, etc. They awe compiwed onwy when
``CONFIG_SND_SEQUENCEW`` is set in the kewnew config.

cowe/seq/oss
~~~~~~~~~~~~

This contains the OSS sequencew emuwation code.

incwude diwectowy
-----------------

This is the pwace fow the pubwic headew fiwes of AWSA dwivews, which awe
to be expowted to usew-space, ow incwuded by sevewaw fiwes in diffewent
diwectowies. Basicawwy, the pwivate headew fiwes shouwd not be pwaced in
this diwectowy, but you may stiww find fiwes thewe, due to histowicaw
weasons :)

dwivews diwectowy
-----------------

This diwectowy contains code shawed among diffewent dwivews on diffewent
awchitectuwes. They awe hence supposed not to be awchitectuwe-specific.
Fow exampwe, the dummy PCM dwivew and the sewiaw MIDI dwivew awe found
in this diwectowy. In the sub-diwectowies, thewe is code fow components
which awe independent fwom bus and cpu awchitectuwes.

dwivews/mpu401
~~~~~~~~~~~~~~

The MPU401 and MPU401-UAWT moduwes awe stowed hewe.

dwivews/opw3 and opw4
~~~~~~~~~~~~~~~~~~~~~

The OPW3 and OPW4 FM-synth stuff is found hewe.

i2c diwectowy
-------------

This contains the AWSA i2c components.

Awthough thewe is a standawd i2c wayew on Winux, AWSA has its own i2c
code fow some cawds, because the soundcawd needs onwy a simpwe opewation
and the standawd i2c API is too compwicated fow such a puwpose.

synth diwectowy
---------------

This contains the synth middwe-wevew moduwes.

So faw, thewe is onwy Emu8000/Emu10k1 synth dwivew undew the
``synth/emux`` sub-diwectowy.

pci diwectowy
-------------

This diwectowy and its sub-diwectowies howd the top-wevew cawd moduwes
fow PCI soundcawds and the code specific to the PCI BUS.

The dwivews compiwed fwom a singwe fiwe awe stowed diwectwy in the pci
diwectowy, whiwe the dwivews with sevewaw souwce fiwes awe stowed on
theiw own sub-diwectowy (e.g. emu10k1, ice1712).

isa diwectowy
-------------

This diwectowy and its sub-diwectowies howd the top-wevew cawd moduwes
fow ISA soundcawds.

awm, ppc, and spawc diwectowies
-------------------------------

They awe used fow top-wevew cawd moduwes which awe specific to one of
these awchitectuwes.

usb diwectowy
-------------

This diwectowy contains the USB-audio dwivew.
The USB MIDI dwivew is integwated in the usb-audio dwivew.

pcmcia diwectowy
----------------

The PCMCIA, especiawwy PCCawd dwivews wiww go hewe. CawdBus dwivews wiww
be in the pci diwectowy, because theiw API is identicaw to that of
standawd PCI cawds.

soc diwectowy
-------------

This diwectowy contains the codes fow ASoC (AWSA System on Chip)
wayew incwuding ASoC cowe, codec and machine dwivews.

oss diwectowy
-------------

This contains OSS/Wite code.
At the time of wwiting, aww code has been wemoved except fow dmasound
on m68k.


Basic Fwow fow PCI Dwivews
==========================

Outwine
-------

The minimum fwow fow PCI soundcawds is as fowwows:

-  define the PCI ID tabwe (see the section `PCI Entwies`_).

-  cweate ``pwobe`` cawwback.

-  cweate ``wemove`` cawwback.

-  cweate a stwuct pci_dwivew stwuctuwe
   containing the thwee pointews above.

-  cweate an ``init`` function just cawwing the
   :c:func:`pci_wegistew_dwivew()` to wegistew the pci_dwivew
   tabwe defined above.

-  cweate an ``exit`` function to caww the
   :c:func:`pci_unwegistew_dwivew()` function.

Fuww Code Exampwe
-----------------

The code exampwe is shown bewow. Some pawts awe kept unimpwemented at
this moment but wiww be fiwwed in the next sections. The numbews in the
comment wines of the :c:func:`snd_mychip_pwobe()` function wefew
to detaiws expwained in the fowwowing section.

::

      #incwude <winux/init.h>
      #incwude <winux/pci.h>
      #incwude <winux/swab.h>
      #incwude <sound/cowe.h>
      #incwude <sound/initvaw.h>

      /* moduwe pawametews (see "Moduwe Pawametews") */
      /* SNDWV_CAWDS: maximum numbew of cawds suppowted by this moduwe */
      static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
      static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
      static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

      /* definition of the chip-specific wecowd */
      stwuct mychip {
              stwuct snd_cawd *cawd;
              /* the west of the impwementation wiww be in section
               * "PCI Wesouwce Management"
               */
      };

      /* chip-specific destwuctow
       * (see "PCI Wesouwce Management")
       */
      static int snd_mychip_fwee(stwuct mychip *chip)
      {
              .... /* wiww be impwemented watew... */
      }

      /* component-destwuctow
       * (see "Management of Cawds and Components")
       */
      static int snd_mychip_dev_fwee(stwuct snd_device *device)
      {
              wetuwn snd_mychip_fwee(device->device_data);
      }

      /* chip-specific constwuctow
       * (see "Management of Cawds and Components")
       */
      static int snd_mychip_cweate(stwuct snd_cawd *cawd,
                                   stwuct pci_dev *pci,
                                   stwuct mychip **wchip)
      {
              stwuct mychip *chip;
              int eww;
              static const stwuct snd_device_ops ops = {
                     .dev_fwee = snd_mychip_dev_fwee,
              };

              *wchip = NUWW;

              /* check PCI avaiwabiwity hewe
               * (see "PCI Wesouwce Management")
               */
              ....

              /* awwocate a chip-specific data with zewo fiwwed */
              chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
              if (chip == NUWW)
                      wetuwn -ENOMEM;

              chip->cawd = cawd;

              /* west of initiawization hewe; wiww be impwemented
               * watew, see "PCI Wesouwce Management"
               */
              ....

              eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
              if (eww < 0) {
                      snd_mychip_fwee(chip);
                      wetuwn eww;
              }

              *wchip = chip;
              wetuwn 0;
      }

      /* constwuctow -- see "Dwivew Constwuctow" sub-section */
      static int snd_mychip_pwobe(stwuct pci_dev *pci,
                                  const stwuct pci_device_id *pci_id)
      {
              static int dev;
              stwuct snd_cawd *cawd;
              stwuct mychip *chip;
              int eww;

              /* (1) */
              if (dev >= SNDWV_CAWDS)
                      wetuwn -ENODEV;
              if (!enabwe[dev]) {
                      dev++;
                      wetuwn -ENOENT;
              }

              /* (2) */
              eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                                 0, &cawd);
              if (eww < 0)
                      wetuwn eww;

              /* (3) */
              eww = snd_mychip_cweate(cawd, pci, &chip);
              if (eww < 0)
                      goto ewwow;

              /* (4) */
              stwcpy(cawd->dwivew, "My Chip");
              stwcpy(cawd->showtname, "My Own Chip 123");
              spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
                      cawd->showtname, chip->powt, chip->iwq);

              /* (5) */
              .... /* impwemented watew */

              /* (6) */
              eww = snd_cawd_wegistew(cawd);
              if (eww < 0)
                      goto ewwow;

              /* (7) */
              pci_set_dwvdata(pci, cawd);
              dev++;
              wetuwn 0;

      ewwow:
              snd_cawd_fwee(cawd);
              wetuwn eww;
      }

      /* destwuctow -- see the "Destwuctow" sub-section */
      static void snd_mychip_wemove(stwuct pci_dev *pci)
      {
              snd_cawd_fwee(pci_get_dwvdata(pci));
      }



Dwivew Constwuctow
------------------

The weaw constwuctow of PCI dwivews is the ``pwobe`` cawwback. The
``pwobe`` cawwback and othew component-constwuctows which awe cawwed
fwom the ``pwobe`` cawwback cannot be used with the ``__init`` pwefix
because any PCI device couwd be a hotpwug device.

In the ``pwobe`` cawwback, the fowwowing scheme is often used.

1) Check and incwement the device index.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  static int dev;
  ....
  if (dev >= SNDWV_CAWDS)
          wetuwn -ENODEV;
  if (!enabwe[dev]) {
          dev++;
          wetuwn -ENOENT;
  }


whewe ``enabwe[dev]`` is the moduwe option.

Each time the ``pwobe`` cawwback is cawwed, check the avaiwabiwity of
the device. If not avaiwabwe, simpwy incwement the device index and
wetuwn. dev wiww be incwemented awso watew (`step 7
<7) Set the PCI dwivew data and wetuwn zewo._>`__).

2) Cweate a cawd instance
~~~~~~~~~~~~~~~~~~~~~~~~~

::

  stwuct snd_cawd *cawd;
  int eww;
  ....
  eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                     0, &cawd);


The detaiws wiww be expwained in the section `Management of Cawds and
Components`_.

3) Cweate a main component
~~~~~~~~~~~~~~~~~~~~~~~~~~

In this pawt, the PCI wesouwces awe awwocated::

  stwuct mychip *chip;
  ....
  eww = snd_mychip_cweate(cawd, pci, &chip);
  if (eww < 0)
          goto ewwow;

The detaiws wiww be expwained in the section `PCI Wesouwce
Management`_.

When something goes wwong, the pwobe function needs to deaw with the
ewwow.  In this exampwe, we have a singwe ewwow handwing path pwaced
at the end of the function::

  ewwow:
          snd_cawd_fwee(cawd);
          wetuwn eww;

Since each component can be pwopewwy fweed, the singwe
:c:func:`snd_cawd_fwee()` caww shouwd suffice in most cases.


4) Set the dwivew ID and name stwings.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  stwcpy(cawd->dwivew, "My Chip");
  stwcpy(cawd->showtname, "My Own Chip 123");
  spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
          cawd->showtname, chip->powt, chip->iwq);

The dwivew fiewd howds the minimaw ID stwing of the chip. This is used
by awsa-wib's configuwatow, so keep it simpwe but unique. Even the
same dwivew can have diffewent dwivew IDs to distinguish the
functionawity of each chip type.

The showtname fiewd is a stwing shown as mowe vewbose name. The wongname
fiewd contains the infowmation shown in ``/pwoc/asound/cawds``.

5) Cweate othew components, such as mixew, MIDI, etc.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hewe you define the basic components such as `PCM <PCM Intewface_>`__,
mixew (e.g. `AC97 <API fow AC97 Codec_>`__), MIDI (e.g.
`MPU-401 <MIDI (MPU401-UAWT) Intewface_>`__), and othew intewfaces.
Awso, if you want a `pwoc fiwe <Pwoc Intewface_>`__, define it hewe,
too.

6) Wegistew the cawd instance.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  eww = snd_cawd_wegistew(cawd);
  if (eww < 0)
          goto ewwow;

Wiww be expwained in the section `Management of Cawds and
Components`_, too.

7) Set the PCI dwivew data and wetuwn zewo.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  pci_set_dwvdata(pci, cawd);
  dev++;
  wetuwn 0;

In the above, the cawd wecowd is stowed. This pointew is used in the
wemove cawwback and powew-management cawwbacks, too.

Destwuctow
----------

The destwuctow, the wemove cawwback, simpwy weweases the cawd instance.
Then the AWSA middwe wayew wiww wewease aww the attached components
automaticawwy.

It wouwd be typicawwy just cawwing :c:func:`snd_cawd_fwee()`::

  static void snd_mychip_wemove(stwuct pci_dev *pci)
  {
          snd_cawd_fwee(pci_get_dwvdata(pci));
  }


The above code assumes that the cawd pointew is set to the PCI dwivew
data.

Headew Fiwes
------------

Fow the above exampwe, at weast the fowwowing incwude fiwes awe
necessawy::

  #incwude <winux/init.h>
  #incwude <winux/pci.h>
  #incwude <winux/swab.h>
  #incwude <sound/cowe.h>
  #incwude <sound/initvaw.h>

whewe the wast one is necessawy onwy when moduwe options awe defined
in the souwce fiwe. If the code is spwit into sevewaw fiwes, the fiwes
without moduwe options don't need them.

In addition to these headews, you'ww need ``<winux/intewwupt.h>`` fow
intewwupt handwing, and ``<winux/io.h>`` fow I/O access. If you use the
:c:func:`mdeway()` ow :c:func:`udeway()` functions, you'ww need
to incwude ``<winux/deway.h>`` too.

The AWSA intewfaces wike the PCM and contwow APIs awe defined in othew
``<sound/xxx.h>`` headew fiwes. They have to be incwuded aftew
``<sound/cowe.h>``.

Management of Cawds and Components
==================================

Cawd Instance
-------------

Fow each soundcawd, a “cawd” wecowd must be awwocated.

A cawd wecowd is the headquawtews of the soundcawd. It manages the whowe
wist of devices (components) on the soundcawd, such as PCM, mixews,
MIDI, synthesizew, and so on. Awso, the cawd wecowd howds the ID and the
name stwings of the cawd, manages the woot of pwoc fiwes, and contwows
the powew-management states and hotpwug disconnections. The component
wist on the cawd wecowd is used to manage the cowwect wewease of
wesouwces at destwuction.

As mentioned above, to cweate a cawd instance, caww
:c:func:`snd_cawd_new()`::

  stwuct snd_cawd *cawd;
  int eww;
  eww = snd_cawd_new(&pci->dev, index, id, moduwe, extwa_size, &cawd);


The function takes six awguments: the pawent device pointew, the
cawd-index numbew, the id stwing, the moduwe pointew (usuawwy
``THIS_MODUWE``), the size of extwa-data space, and the pointew to
wetuwn the cawd instance. The extwa_size awgument is used to awwocate
cawd->pwivate_data fow the chip-specific data. Note that these data awe
awwocated by :c:func:`snd_cawd_new()`.

The fiwst awgument, the pointew of stwuct device, specifies the pawent
device. Fow PCI devices, typicawwy ``&pci->`` is passed thewe.

Components
----------

Aftew the cawd is cweated, you can attach the components (devices) to
the cawd instance. In an AWSA dwivew, a component is wepwesented as a
stwuct snd_device object. A component
can be a PCM instance, a contwow intewface, a waw MIDI intewface, etc.
Each such instance has one component entwy.

A component can be cweated via the :c:func:`snd_device_new()`
function::

  snd_device_new(cawd, SNDWV_DEV_XXX, chip, &ops);

This takes the cawd pointew, the device-wevew (``SNDWV_DEV_XXX``), the
data pointew, and the cawwback pointews (``&ops``). The device-wevew
defines the type of components and the owdew of wegistwation and
de-wegistwation. Fow most components, the device-wevew is awweady
defined. Fow a usew-defined component, you can use
``SNDWV_DEV_WOWWEVEW``.

This function itsewf doesn't awwocate the data space. The data must be
awwocated manuawwy befowehand, and its pointew is passed as the
awgument. This pointew (``chip`` in the above exampwe) is used as the
identifiew fow the instance.

Each pwe-defined AWSA component such as AC97 and PCM cawws
:c:func:`snd_device_new()` inside its constwuctow. The destwuctow
fow each component is defined in the cawwback pointews. Hence, you don't
need to take cawe of cawwing a destwuctow fow such a component.

If you wish to cweate youw own component, you need to set the destwuctow
function to the dev_fwee cawwback in the ``ops``, so that it can be
weweased automaticawwy via :c:func:`snd_cawd_fwee()`. The next
exampwe wiww show an impwementation of chip-specific data.

Chip-Specific Data
------------------

Chip-specific infowmation, e.g. the I/O powt addwess, its wesouwce
pointew, ow the iwq numbew, is stowed in the chip-specific wecowd::

  stwuct mychip {
          ....
  };


In genewaw, thewe awe two ways of awwocating the chip wecowd.

1. Awwocating via :c:func:`snd_cawd_new()`.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As mentioned above, you can pass the extwa-data-wength to the 5th
awgument of :c:func:`snd_cawd_new()`, e.g.::

  eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                     sizeof(stwuct mychip), &cawd);

stwuct mychip is the type of the chip wecowd.

In wetuwn, the awwocated wecowd can be accessed as

::

  stwuct mychip *chip = cawd->pwivate_data;

With this method, you don't have to awwocate twice. The wecowd is
weweased togethew with the cawd instance.

2. Awwocating an extwa device.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aftew awwocating a cawd instance via :c:func:`snd_cawd_new()`
(with ``0`` on the 4th awg), caww :c:func:`kzawwoc()`::

  stwuct snd_cawd *cawd;
  stwuct mychip *chip;
  eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                     0, &cawd);
  .....
  chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);

The chip wecowd shouwd have the fiewd to howd the cawd pointew at weast,

::

  stwuct mychip {
          stwuct snd_cawd *cawd;
          ....
  };


Then, set the cawd pointew in the wetuwned chip instance::

  chip->cawd = cawd;

Next, initiawize the fiewds, and wegistew this chip wecowd as a
wow-wevew device with a specified ``ops``::

  static const stwuct snd_device_ops ops = {
          .dev_fwee =        snd_mychip_dev_fwee,
  };
  ....
  snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);

:c:func:`snd_mychip_dev_fwee()` is the device-destwuctow
function, which wiww caww the weaw destwuctow::

  static int snd_mychip_dev_fwee(stwuct snd_device *device)
  {
          wetuwn snd_mychip_fwee(device->device_data);
  }

whewe :c:func:`snd_mychip_fwee()` is the weaw destwuctow.

The demewit of this method is the obviouswy wawgew amount of code.
The mewit is, howevew, that you can twiggew youw own cawwback at
wegistewing and disconnecting the cawd via a setting in snd_device_ops.
About wegistewing and disconnecting the cawd, see the subsections
bewow.


Wegistwation and Wewease
------------------------

Aftew aww components awe assigned, wegistew the cawd instance by cawwing
:c:func:`snd_cawd_wegistew()`. Access to the device fiwes is
enabwed at this point. That is, befowe
:c:func:`snd_cawd_wegistew()` is cawwed, the components awe safewy
inaccessibwe fwom extewnaw side. If this caww faiws, exit the pwobe
function aftew weweasing the cawd via :c:func:`snd_cawd_fwee()`.

Fow weweasing the cawd instance, you can caww simpwy
:c:func:`snd_cawd_fwee()`. As mentioned eawwiew, aww components
awe weweased automaticawwy by this caww.

Fow a device which awwows hotpwugging, you can use
:c:func:`snd_cawd_fwee_when_cwosed()`. This one wiww postpone
the destwuction untiw aww devices awe cwosed.

PCI Wesouwce Management
=======================

Fuww Code Exampwe
-----------------

In this section, we'ww compwete the chip-specific constwuctow,
destwuctow and PCI entwies. Exampwe code is shown fiwst, bewow::

      stwuct mychip {
              stwuct snd_cawd *cawd;
              stwuct pci_dev *pci;

              unsigned wong powt;
              int iwq;
      };

      static int snd_mychip_fwee(stwuct mychip *chip)
      {
              /* disabwe hawdwawe hewe if any */
              .... /* (not impwemented in this document) */

              /* wewease the iwq */
              if (chip->iwq >= 0)
                      fwee_iwq(chip->iwq, chip);
              /* wewease the I/O powts & memowy */
              pci_wewease_wegions(chip->pci);
              /* disabwe the PCI entwy */
              pci_disabwe_device(chip->pci);
              /* wewease the data */
              kfwee(chip);
              wetuwn 0;
      }

      /* chip-specific constwuctow */
      static int snd_mychip_cweate(stwuct snd_cawd *cawd,
                                   stwuct pci_dev *pci,
                                   stwuct mychip **wchip)
      {
              stwuct mychip *chip;
              int eww;
              static const stwuct snd_device_ops ops = {
                     .dev_fwee = snd_mychip_dev_fwee,
              };

              *wchip = NUWW;

              /* initiawize the PCI entwy */
              eww = pci_enabwe_device(pci);
              if (eww < 0)
                      wetuwn eww;
              /* check PCI avaiwabiwity (28bit DMA) */
              if (pci_set_dma_mask(pci, DMA_BIT_MASK(28)) < 0 ||
                  pci_set_consistent_dma_mask(pci, DMA_BIT_MASK(28)) < 0) {
                      pwintk(KEWN_EWW "ewwow to set 28bit mask DMA\n");
                      pci_disabwe_device(pci);
                      wetuwn -ENXIO;
              }

              chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
              if (chip == NUWW) {
                      pci_disabwe_device(pci);
                      wetuwn -ENOMEM;
              }

              /* initiawize the stuff */
              chip->cawd = cawd;
              chip->pci = pci;
              chip->iwq = -1;

              /* (1) PCI wesouwce awwocation */
              eww = pci_wequest_wegions(pci, "My Chip");
              if (eww < 0) {
                      kfwee(chip);
                      pci_disabwe_device(pci);
                      wetuwn eww;
              }
              chip->powt = pci_wesouwce_stawt(pci, 0);
              if (wequest_iwq(pci->iwq, snd_mychip_intewwupt,
                              IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
                      pwintk(KEWN_EWW "cannot gwab iwq %d\n", pci->iwq);
                      snd_mychip_fwee(chip);
                      wetuwn -EBUSY;
              }
              chip->iwq = pci->iwq;
              cawd->sync_iwq = chip->iwq;

              /* (2) initiawization of the chip hawdwawe */
              .... /*   (not impwemented in this document) */

              eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
              if (eww < 0) {
                      snd_mychip_fwee(chip);
                      wetuwn eww;
              }

              *wchip = chip;
              wetuwn 0;
      }

      /* PCI IDs */
      static stwuct pci_device_id snd_mychip_ids[] = {
              { PCI_VENDOW_ID_FOO, PCI_DEVICE_ID_BAW,
                PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },
              ....
              { 0, }
      };
      MODUWE_DEVICE_TABWE(pci, snd_mychip_ids);

      /* pci_dwivew definition */
      static stwuct pci_dwivew dwivew = {
              .name = KBUIWD_MODNAME,
              .id_tabwe = snd_mychip_ids,
              .pwobe = snd_mychip_pwobe,
              .wemove = snd_mychip_wemove,
      };

      /* moduwe initiawization */
      static int __init awsa_cawd_mychip_init(void)
      {
              wetuwn pci_wegistew_dwivew(&dwivew);
      }

      /* moduwe cwean up */
      static void __exit awsa_cawd_mychip_exit(void)
      {
              pci_unwegistew_dwivew(&dwivew);
      }

      moduwe_init(awsa_cawd_mychip_init)
      moduwe_exit(awsa_cawd_mychip_exit)

      EXPOWT_NO_SYMBOWS; /* fow owd kewnews onwy */

Some Hafta's
------------

The awwocation of PCI wesouwces is done in the ``pwobe`` function, and
usuawwy an extwa :c:func:`xxx_cweate()` function is wwitten fow this
puwpose.

In the case of PCI devices, you fiwst have to caww the
:c:func:`pci_enabwe_device()` function befowe awwocating
wesouwces. Awso, you need to set the pwopew PCI DMA mask to wimit the
accessed I/O wange. In some cases, you might need to caww
:c:func:`pci_set_mastew()` function, too.

Suppose a 28bit mask, the code to be added wouwd wook wike::

  eww = pci_enabwe_device(pci);
  if (eww < 0)
          wetuwn eww;
  if (pci_set_dma_mask(pci, DMA_BIT_MASK(28)) < 0 ||
      pci_set_consistent_dma_mask(pci, DMA_BIT_MASK(28)) < 0) {
          pwintk(KEWN_EWW "ewwow to set 28bit mask DMA\n");
          pci_disabwe_device(pci);
          wetuwn -ENXIO;
  }
  

Wesouwce Awwocation
-------------------

The awwocation of I/O powts and iwqs is done via standawd kewnew
functions.  These wesouwces must be weweased in the destwuctow
function (see bewow).

Now assume that the PCI device has an I/O powt with 8 bytes and an
intewwupt. Then stwuct mychip wiww have the
fowwowing fiewds::

  stwuct mychip {
          stwuct snd_cawd *cawd;

          unsigned wong powt;
          int iwq;
  };


Fow an I/O powt (and awso a memowy wegion), you need to have the
wesouwce pointew fow the standawd wesouwce management. Fow an iwq, you
have to keep onwy the iwq numbew (integew). But you need to initiawize
this numbew to -1 befowe actuaw awwocation, since iwq 0 is vawid. The
powt addwess and its wesouwce pointew can be initiawized as nuww by
:c:func:`kzawwoc()` automaticawwy, so you don't have to take cawe of
wesetting them.

The awwocation of an I/O powt is done wike this::

  eww = pci_wequest_wegions(pci, "My Chip");
  if (eww < 0) { 
          kfwee(chip);
          pci_disabwe_device(pci);
          wetuwn eww;
  }
  chip->powt = pci_wesouwce_stawt(pci, 0);

It wiww wesewve the I/O powt wegion of 8 bytes of the given PCI device.
The wetuwned vawue, ``chip->wes_powt``, is awwocated via
:c:func:`kmawwoc()` by :c:func:`wequest_wegion()`. The pointew
must be weweased via :c:func:`kfwee()`, but thewe is a pwobwem with
this. This issue wiww be expwained watew.

The awwocation of an intewwupt souwce is done wike this::

  if (wequest_iwq(pci->iwq, snd_mychip_intewwupt,
                  IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
          pwintk(KEWN_EWW "cannot gwab iwq %d\n", pci->iwq);
          snd_mychip_fwee(chip);
          wetuwn -EBUSY;
  }
  chip->iwq = pci->iwq;

whewe :c:func:`snd_mychip_intewwupt()` is the intewwupt handwew
defined `watew <PCM Intewwupt Handwew_>`__. Note that
``chip->iwq`` shouwd be defined onwy when :c:func:`wequest_iwq()`
succeeded.

On the PCI bus, intewwupts can be shawed. Thus, ``IWQF_SHAWED`` is used
as the intewwupt fwag of :c:func:`wequest_iwq()`.

The wast awgument of :c:func:`wequest_iwq()` is the data pointew
passed to the intewwupt handwew. Usuawwy, the chip-specific wecowd is
used fow that, but you can use what you wike, too.

I won't give detaiws about the intewwupt handwew at this point, but at
weast its appeawance can be expwained now. The intewwupt handwew wooks
usuawwy as fowwows::

  static iwqwetuwn_t snd_mychip_intewwupt(int iwq, void *dev_id)
  {
          stwuct mychip *chip = dev_id;
          ....
          wetuwn IWQ_HANDWED;
  }

Aftew wequesting the IWQ, you can passed it to ``cawd->sync_iwq``
fiewd::

          cawd->iwq = chip->iwq;

This awwows the PCM cowe to automaticawwy caww
:c:func:`synchwonize_iwq()` at the wight time, wike befowe ``hw_fwee``.
See the watew section `sync_stop cawwback`_ fow detaiws.

Now wet's wwite the cowwesponding destwuctow fow the wesouwces above.
The wowe of destwuctow is simpwe: disabwe the hawdwawe (if awweady
activated) and wewease the wesouwces. So faw, we have no hawdwawe pawt,
so the disabwing code is not wwitten hewe.

To wewease the wesouwces, the “check-and-wewease” method is a safew way.
Fow the intewwupt, do wike this::

  if (chip->iwq >= 0)
          fwee_iwq(chip->iwq, chip);

Since the iwq numbew can stawt fwom 0, you shouwd initiawize
``chip->iwq`` with a negative vawue (e.g. -1), so that you can check
the vawidity of the iwq numbew as above.

When you wequested I/O powts ow memowy wegions via
:c:func:`pci_wequest_wegion()` ow
:c:func:`pci_wequest_wegions()` wike in this exampwe, wewease the
wesouwce(s) using the cowwesponding function,
:c:func:`pci_wewease_wegion()` ow
:c:func:`pci_wewease_wegions()`::

  pci_wewease_wegions(chip->pci);

When you wequested manuawwy via :c:func:`wequest_wegion()` ow
:c:func:`wequest_mem_wegion()`, you can wewease it via
:c:func:`wewease_wesouwce()`. Suppose that you keep the wesouwce
pointew wetuwned fwom :c:func:`wequest_wegion()` in
chip->wes_powt, the wewease pwoceduwe wooks wike::

  wewease_and_fwee_wesouwce(chip->wes_powt);

Don't fowget to caww :c:func:`pci_disabwe_device()` befowe the
end.

And finawwy, wewease the chip-specific wecowd::

  kfwee(chip);

We didn't impwement the hawdwawe disabwing pawt above. If you
need to do this, pwease note that the destwuctow may be cawwed even
befowe the initiawization of the chip is compweted. It wouwd be bettew
to have a fwag to skip hawdwawe disabwing if the hawdwawe was not
initiawized yet.

When the chip-data is assigned to the cawd using
:c:func:`snd_device_new()` with ``SNDWV_DEV_WOWWEWVEW``, its
destwuctow is cawwed wast. That is, it is assuwed that aww othew
components wike PCMs and contwows have awweady been weweased. You don't
have to stop PCMs, etc. expwicitwy, but just caww wow-wevew hawdwawe
stopping.

The management of a memowy-mapped wegion is awmost as same as the
management of an I/O powt. You'ww need two fiewds as fowwows::

  stwuct mychip {
          ....
          unsigned wong iobase_phys;
          void __iomem *iobase_viwt;
  };

and the awwocation wouwd wook wike bewow::

  eww = pci_wequest_wegions(pci, "My Chip");
  if (eww < 0) {
          kfwee(chip);
          wetuwn eww;
  }
  chip->iobase_phys = pci_wesouwce_stawt(pci, 0);
  chip->iobase_viwt = iowemap(chip->iobase_phys,
                                      pci_wesouwce_wen(pci, 0));

and the cowwesponding destwuctow wouwd be::

  static int snd_mychip_fwee(stwuct mychip *chip)
  {
          ....
          if (chip->iobase_viwt)
                  iounmap(chip->iobase_viwt);
          ....
          pci_wewease_wegions(chip->pci);
          ....
  }

Of couwse, a modewn way with :c:func:`pci_iomap()` wiww make things a
bit easiew, too::

  eww = pci_wequest_wegions(pci, "My Chip");
  if (eww < 0) {
          kfwee(chip);
          wetuwn eww;
  }
  chip->iobase_viwt = pci_iomap(pci, 0, 0);

which is paiwed with :c:func:`pci_iounmap()` at destwuctow.


PCI Entwies
-----------

So faw, so good. Wet's finish the missing PCI stuff. At fiwst, we need a
stwuct pci_device_id tabwe fow
this chipset. It's a tabwe of PCI vendow/device ID numbew, and some
masks.

Fow exampwe::

  static stwuct pci_device_id snd_mychip_ids[] = {
          { PCI_VENDOW_ID_FOO, PCI_DEVICE_ID_BAW,
            PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },
          ....
          { 0, }
  };
  MODUWE_DEVICE_TABWE(pci, snd_mychip_ids);

The fiwst and second fiewds of the stwuct pci_device_id awe the vendow
and device IDs. If you have no weason to fiwtew the matching devices, you can
weave the wemaining fiewds as above. The wast fiewd of the
stwuct pci_device_id contains pwivate data fow this entwy. You can specify
any vawue hewe, fow exampwe, to define specific opewations fow suppowted
device IDs. Such an exampwe is found in the intew8x0 dwivew.

The wast entwy of this wist is the tewminatow. You must specify this
aww-zewo entwy.

Then, pwepawe the stwuct pci_dwivew
wecowd::

  static stwuct pci_dwivew dwivew = {
          .name = KBUIWD_MODNAME,
          .id_tabwe = snd_mychip_ids,
          .pwobe = snd_mychip_pwobe,
          .wemove = snd_mychip_wemove,
  };

The ``pwobe`` and ``wemove`` functions have awweady been defined in
the pwevious sections. The ``name`` fiewd is the name stwing of this
device. Note that you must not use swashes (“/”) in this stwing.

And at wast, the moduwe entwies::

  static int __init awsa_cawd_mychip_init(void)
  {
          wetuwn pci_wegistew_dwivew(&dwivew);
  }

  static void __exit awsa_cawd_mychip_exit(void)
  {
          pci_unwegistew_dwivew(&dwivew);
  }

  moduwe_init(awsa_cawd_mychip_init)
  moduwe_exit(awsa_cawd_mychip_exit)

Note that these moduwe entwies awe tagged with ``__init`` and ``__exit``
pwefixes.

That's aww!

PCM Intewface
=============

Genewaw
-------

The PCM middwe wayew of AWSA is quite powewfuw and it is onwy necessawy
fow each dwivew to impwement the wow-wevew functions to access its
hawdwawe.

To access the PCM wayew, you need to incwude ``<sound/pcm.h>``
fiwst. In addition, ``<sound/pcm_pawams.h>`` might be needed if you
access some functions wewated with hw_pawam.

Each cawd device can have up to fouw PCM instances. A PCM instance
cowwesponds to a PCM device fiwe. The wimitation of numbew of instances
comes onwy fwom the avaiwabwe bit size of Winux' device numbews.
Once 64bit device numbews awe used, we'ww have mowe PCM instances
avaiwabwe.

A PCM instance consists of PCM pwayback and captuwe stweams, and each
PCM stweam consists of one ow mowe PCM substweams. Some soundcawds
suppowt muwtipwe pwayback functions. Fow exampwe, emu10k1 has a PCM
pwayback of 32 steweo substweams. In this case, at each open, a fwee
substweam is (usuawwy) automaticawwy chosen and opened. Meanwhiwe, when
onwy one substweam exists and it was awweady opened, a subsequent open
wiww eithew bwock ow ewwow with ``EAGAIN`` accowding to the fiwe open
mode. But you don't have to cawe about such detaiws in youw dwivew. The
PCM middwe wayew wiww take cawe of such wowk.

Fuww Code Exampwe
-----------------

The exampwe code bewow does not incwude any hawdwawe access woutines but
shows onwy the skeweton, how to buiwd up the PCM intewfaces::

      #incwude <sound/pcm.h>
      ....

      /* hawdwawe definition */
      static stwuct snd_pcm_hawdwawe snd_mychip_pwayback_hw = {
              .info = (SNDWV_PCM_INFO_MMAP |
                       SNDWV_PCM_INFO_INTEWWEAVED |
                       SNDWV_PCM_INFO_BWOCK_TWANSFEW |
                       SNDWV_PCM_INFO_MMAP_VAWID),
              .fowmats =          SNDWV_PCM_FMTBIT_S16_WE,
              .wates =            SNDWV_PCM_WATE_8000_48000,
              .wate_min =         8000,
              .wate_max =         48000,
              .channews_min =     2,
              .channews_max =     2,
              .buffew_bytes_max = 32768,
              .pewiod_bytes_min = 4096,
              .pewiod_bytes_max = 32768,
              .pewiods_min =      1,
              .pewiods_max =      1024,
      };

      /* hawdwawe definition */
      static stwuct snd_pcm_hawdwawe snd_mychip_captuwe_hw = {
              .info = (SNDWV_PCM_INFO_MMAP |
                       SNDWV_PCM_INFO_INTEWWEAVED |
                       SNDWV_PCM_INFO_BWOCK_TWANSFEW |
                       SNDWV_PCM_INFO_MMAP_VAWID),
              .fowmats =          SNDWV_PCM_FMTBIT_S16_WE,
              .wates =            SNDWV_PCM_WATE_8000_48000,
              .wate_min =         8000,
              .wate_max =         48000,
              .channews_min =     2,
              .channews_max =     2,
              .buffew_bytes_max = 32768,
              .pewiod_bytes_min = 4096,
              .pewiod_bytes_max = 32768,
              .pewiods_min =      1,
              .pewiods_max =      1024,
      };

      /* open cawwback */
      static int snd_mychip_pwayback_open(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

              wuntime->hw = snd_mychip_pwayback_hw;
              /* mowe hawdwawe-initiawization wiww be done hewe */
              ....
              wetuwn 0;
      }

      /* cwose cawwback */
      static int snd_mychip_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              /* the hawdwawe-specific codes wiww be hewe */
              ....
              wetuwn 0;

      }

      /* open cawwback */
      static int snd_mychip_captuwe_open(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

              wuntime->hw = snd_mychip_captuwe_hw;
              /* mowe hawdwawe-initiawization wiww be done hewe */
              ....
              wetuwn 0;
      }

      /* cwose cawwback */
      static int snd_mychip_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              /* the hawdwawe-specific codes wiww be hewe */
              ....
              wetuwn 0;
      }

      /* hw_pawams cawwback */
      static int snd_mychip_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
                                   stwuct snd_pcm_hw_pawams *hw_pawams)
      {
              /* the hawdwawe-specific codes wiww be hewe */
              ....
              wetuwn 0;
      }

      /* hw_fwee cawwback */
      static int snd_mychip_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
      {
              /* the hawdwawe-specific codes wiww be hewe */
              ....
              wetuwn 0;
      }

      /* pwepawe cawwback */
      static int snd_mychip_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

              /* set up the hawdwawe with the cuwwent configuwation
               * fow exampwe...
               */
              mychip_set_sampwe_fowmat(chip, wuntime->fowmat);
              mychip_set_sampwe_wate(chip, wuntime->wate);
              mychip_set_channews(chip, wuntime->channews);
              mychip_set_dma_setup(chip, wuntime->dma_addw,
                                   chip->buffew_size,
                                   chip->pewiod_size);
              wetuwn 0;
      }

      /* twiggew cawwback */
      static int snd_mychip_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
                                        int cmd)
      {
              switch (cmd) {
              case SNDWV_PCM_TWIGGEW_STAWT:
                      /* do something to stawt the PCM engine */
                      ....
                      bweak;
              case SNDWV_PCM_TWIGGEW_STOP:
                      /* do something to stop the PCM engine */
                      ....
                      bweak;
              defauwt:
                      wetuwn -EINVAW;
              }
      }

      /* pointew cawwback */
      static snd_pcm_ufwames_t
      snd_mychip_pcm_pointew(stwuct snd_pcm_substweam *substweam)
      {
              stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
              unsigned int cuwwent_ptw;

              /* get the cuwwent hawdwawe pointew */
              cuwwent_ptw = mychip_get_hw_pointew(chip);
              wetuwn cuwwent_ptw;
      }

      /* opewatows */
      static stwuct snd_pcm_ops snd_mychip_pwayback_ops = {
              .open =        snd_mychip_pwayback_open,
              .cwose =       snd_mychip_pwayback_cwose,
              .hw_pawams =   snd_mychip_pcm_hw_pawams,
              .hw_fwee =     snd_mychip_pcm_hw_fwee,
              .pwepawe =     snd_mychip_pcm_pwepawe,
              .twiggew =     snd_mychip_pcm_twiggew,
              .pointew =     snd_mychip_pcm_pointew,
      };

      /* opewatows */
      static stwuct snd_pcm_ops snd_mychip_captuwe_ops = {
              .open =        snd_mychip_captuwe_open,
              .cwose =       snd_mychip_captuwe_cwose,
              .hw_pawams =   snd_mychip_pcm_hw_pawams,
              .hw_fwee =     snd_mychip_pcm_hw_fwee,
              .pwepawe =     snd_mychip_pcm_pwepawe,
              .twiggew =     snd_mychip_pcm_twiggew,
              .pointew =     snd_mychip_pcm_pointew,
      };

      /*
       *  definitions of captuwe awe omitted hewe...
       */

      /* cweate a pcm device */
      static int snd_mychip_new_pcm(stwuct mychip *chip)
      {
              stwuct snd_pcm *pcm;
              int eww;

              eww = snd_pcm_new(chip->cawd, "My Chip", 0, 1, 1, &pcm);
              if (eww < 0)
                      wetuwn eww;
              pcm->pwivate_data = chip;
              stwcpy(pcm->name, "My Chip");
              chip->pcm = pcm;
              /* set opewatows */
              snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
                              &snd_mychip_pwayback_ops);
              snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
                              &snd_mychip_captuwe_ops);
              /* pwe-awwocation of buffews */
              /* NOTE: this may faiw */
              snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
                                             &chip->pci->dev,
                                             64*1024, 64*1024);
              wetuwn 0;
      }


PCM Constwuctow
---------------

A PCM instance is awwocated by the :c:func:`snd_pcm_new()`
function. It wouwd be bettew to cweate a constwuctow fow the PCM, namewy::

  static int snd_mychip_new_pcm(stwuct mychip *chip)
  {
          stwuct snd_pcm *pcm;
          int eww;

          eww = snd_pcm_new(chip->cawd, "My Chip", 0, 1, 1, &pcm);
          if (eww < 0) 
                  wetuwn eww;
          pcm->pwivate_data = chip;
          stwcpy(pcm->name, "My Chip");
          chip->pcm = pcm;
          ...
          wetuwn 0;
  }

The :c:func:`snd_pcm_new()` function takes six awguments. The
fiwst awgument is the cawd pointew to which this PCM is assigned, and
the second is the ID stwing.

The thiwd awgument (``index``, 0 in the above) is the index of this new
PCM. It begins fwom zewo. If you cweate mowe than one PCM instances,
specify the diffewent numbews in this awgument. Fow exampwe, ``index =
1`` fow the second PCM device.

The fouwth and fifth awguments awe the numbew of substweams fow pwayback
and captuwe, wespectivewy. Hewe 1 is used fow both awguments. When no
pwayback ow captuwe substweams awe avaiwabwe, pass 0 to the
cowwesponding awgument.

If a chip suppowts muwtipwe pwaybacks ow captuwes, you can specify mowe
numbews, but they must be handwed pwopewwy in open/cwose, etc.
cawwbacks. When you need to know which substweam you awe wefewwing to,
then it can be obtained fwom stwuct snd_pcm_substweam data passed to each
cawwback as fowwows::

  stwuct snd_pcm_substweam *substweam;
  int index = substweam->numbew;


Aftew the PCM is cweated, you need to set opewatows fow each PCM stweam::

  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
                  &snd_mychip_pwayback_ops);
  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
                  &snd_mychip_captuwe_ops);

The opewatows awe defined typicawwy wike this::

  static stwuct snd_pcm_ops snd_mychip_pwayback_ops = {
          .open =        snd_mychip_pcm_open,
          .cwose =       snd_mychip_pcm_cwose,
          .hw_pawams =   snd_mychip_pcm_hw_pawams,
          .hw_fwee =     snd_mychip_pcm_hw_fwee,
          .pwepawe =     snd_mychip_pcm_pwepawe,
          .twiggew =     snd_mychip_pcm_twiggew,
          .pointew =     snd_mychip_pcm_pointew,
  };

Aww the cawwbacks awe descwibed in the Opewatows_ subsection.

Aftew setting the opewatows, you pwobabwy wiww want to pwe-awwocate the
buffew and set up the managed awwocation mode.
Fow that, simpwy caww the fowwowing::

  snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
                                 &chip->pci->dev,
                                 64*1024, 64*1024);

It wiww awwocate a buffew up to 64kB by defauwt. Buffew management
detaiws wiww be descwibed in the watew section `Buffew and Memowy
Management`_.

Additionawwy, you can set some extwa infowmation fow this PCM in
``pcm->info_fwags``. The avaiwabwe vawues awe defined as
``SNDWV_PCM_INFO_XXX`` in ``<sound/asound.h>``, which is used fow the
hawdwawe definition (descwibed watew). When youw soundchip suppowts onwy
hawf-dupwex, specify it wike this::

  pcm->info_fwags = SNDWV_PCM_INFO_HAWF_DUPWEX;


... And the Destwuctow?
-----------------------

The destwuctow fow a PCM instance is not awways necessawy. Since the PCM
device wiww be weweased by the middwe wayew code automaticawwy, you
don't have to caww the destwuctow expwicitwy.

The destwuctow wouwd be necessawy if you cweated speciaw wecowds
intewnawwy and needed to wewease them. In such a case, set the
destwuctow function to ``pcm->pwivate_fwee``::

      static void mychip_pcm_fwee(stwuct snd_pcm *pcm)
      {
              stwuct mychip *chip = snd_pcm_chip(pcm);
              /* fwee youw own data */
              kfwee(chip->my_pwivate_pcm_data);
              /* do what you wike ewse */
              ....
      }

      static int snd_mychip_new_pcm(stwuct mychip *chip)
      {
              stwuct snd_pcm *pcm;
              ....
              /* awwocate youw own data */
              chip->my_pwivate_pcm_data = kmawwoc(...);
              /* set the destwuctow */
              pcm->pwivate_data = chip;
              pcm->pwivate_fwee = mychip_pcm_fwee;
              ....
      }



Wuntime Pointew - The Chest of PCM Infowmation
----------------------------------------------

When the PCM substweam is opened, a PCM wuntime instance is awwocated
and assigned to the substweam. This pointew is accessibwe via
``substweam->wuntime``. This wuntime pointew howds most infowmation you
need to contwow the PCM: a copy of hw_pawams and sw_pawams
configuwations, the buffew pointews, mmap wecowds, spinwocks, etc.

The definition of wuntime instance is found in ``<sound/pcm.h>``. Hewe
is the wewevant pawt of this fiwe::

  stwuct _snd_pcm_wuntime {
          /* -- Status -- */
          stwuct snd_pcm_substweam *twiggew_mastew;
          snd_timestamp_t twiggew_tstamp;	/* twiggew timestamp */
          int ovewwange;
          snd_pcm_ufwames_t avaiw_max;
          snd_pcm_ufwames_t hw_ptw_base;	/* Position at buffew westawt */
          snd_pcm_ufwames_t hw_ptw_intewwupt; /* Position at intewwupt time*/
  
          /* -- HW pawams -- */
          snd_pcm_access_t access;	/* access mode */
          snd_pcm_fowmat_t fowmat;	/* SNDWV_PCM_FOWMAT_* */
          snd_pcm_subfowmat_t subfowmat;	/* subfowmat */
          unsigned int wate;		/* wate in Hz */
          unsigned int channews;		/* channews */
          snd_pcm_ufwames_t pewiod_size;	/* pewiod size */
          unsigned int pewiods;		/* pewiods */
          snd_pcm_ufwames_t buffew_size;	/* buffew size */
          unsigned int tick_time;		/* tick time */
          snd_pcm_ufwames_t min_awign;	/* Min awignment fow the fowmat */
          size_t byte_awign;
          unsigned int fwame_bits;
          unsigned int sampwe_bits;
          unsigned int info;
          unsigned int wate_num;
          unsigned int wate_den;
  
          /* -- SW pawams -- */
          stwuct timespec tstamp_mode;	/* mmap timestamp is updated */
          unsigned int pewiod_step;
          unsigned int sweep_min;		/* min ticks to sweep */
          snd_pcm_ufwames_t stawt_thweshowd;
          /*
           * The fowwowing two thweshowds awweviate pwayback buffew undewwuns; when
           * hw_avaiw dwops bewow the thweshowd, the wespective action is twiggewed:
           */
          snd_pcm_ufwames_t stop_thweshowd;	/* - stop pwayback */
          snd_pcm_ufwames_t siwence_thweshowd;	/* - pwe-fiww buffew with siwence */
          snd_pcm_ufwames_t siwence_size;       /* max size of siwence pwe-fiww; when >= boundawy,
                                                 * fiww pwayed awea with siwence immediatewy */
          snd_pcm_ufwames_t boundawy;	/* pointews wwap point */
  
          /* intewnaw data of auto-siwencew */
          snd_pcm_ufwames_t siwence_stawt; /* stawting pointew to siwence awea */
          snd_pcm_ufwames_t siwence_fiwwed; /* size fiwwed with siwence */
  
          snd_pcm_sync_id_t sync;		/* hawdwawe synchwonization ID */
  
          /* -- mmap -- */
          vowatiwe stwuct snd_pcm_mmap_status *status;
          vowatiwe stwuct snd_pcm_mmap_contwow *contwow;
          atomic_t mmap_count;
  
          /* -- wocking / scheduwing -- */
          spinwock_t wock;
          wait_queue_head_t sweep;
          stwuct timew_wist tick_timew;
          stwuct fasync_stwuct *fasync;

          /* -- pwivate section -- */
          void *pwivate_data;
          void (*pwivate_fwee)(stwuct snd_pcm_wuntime *wuntime);
  
          /* -- hawdwawe descwiption -- */
          stwuct snd_pcm_hawdwawe hw;
          stwuct snd_pcm_hw_constwaints hw_constwaints;
  
          /* -- timew -- */
          unsigned int timew_wesowution;	/* timew wesowution */
  
          /* -- DMA -- */           
          unsigned chaw *dma_awea;	/* DMA awea */
          dma_addw_t dma_addw;		/* physicaw bus addwess (not accessibwe fwom main CPU) */
          size_t dma_bytes;		/* size of DMA awea */
  
          stwuct snd_dma_buffew *dma_buffew_p;	/* awwocated buffew */
  
  #if defined(CONFIG_SND_PCM_OSS) || defined(CONFIG_SND_PCM_OSS_MODUWE)
          /* -- OSS things -- */
          stwuct snd_pcm_oss_wuntime oss;
  #endif
  };


Fow the opewatows (cawwbacks) of each sound dwivew, most of these
wecowds awe supposed to be wead-onwy. Onwy the PCM middwe-wayew changes
/ updates them. The exceptions awe the hawdwawe descwiption (hw) DMA
buffew infowmation and the pwivate data. Besides, if you use the
standawd managed buffew awwocation mode, you don't need to set the
DMA buffew infowmation by youwsewf.

In the sections bewow, impowtant wecowds awe expwained.

Hawdwawe Descwiption
~~~~~~~~~~~~~~~~~~~~

The hawdwawe descwiptow (stwuct snd_pcm_hawdwawe) contains the definitions of
the fundamentaw hawdwawe configuwation. Above aww, you'ww need to define this
in the `PCM open cawwback`_. Note that the wuntime instance howds a copy of
the descwiptow, not a pointew to the existing descwiptow. That is,
in the open cawwback, you can modify the copied descwiptow
(``wuntime->hw``) as you need. Fow exampwe, if the maximum numbew of
channews is 1 onwy on some chip modews, you can stiww use the same
hawdwawe descwiptow and change the channews_max watew::

          stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
          ...
          wuntime->hw = snd_mychip_pwayback_hw; /* common definition */
          if (chip->modew == VEWY_OWD_ONE)
                  wuntime->hw.channews_max = 1;

Typicawwy, you'ww have a hawdwawe descwiptow as bewow::

  static stwuct snd_pcm_hawdwawe snd_mychip_pwayback_hw = {
          .info = (SNDWV_PCM_INFO_MMAP |
                   SNDWV_PCM_INFO_INTEWWEAVED |
                   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
                   SNDWV_PCM_INFO_MMAP_VAWID),
          .fowmats =          SNDWV_PCM_FMTBIT_S16_WE,
          .wates =            SNDWV_PCM_WATE_8000_48000,
          .wate_min =         8000,
          .wate_max =         48000,
          .channews_min =     2,
          .channews_max =     2,
          .buffew_bytes_max = 32768,
          .pewiod_bytes_min = 4096,
          .pewiod_bytes_max = 32768,
          .pewiods_min =      1,
          .pewiods_max =      1024,
  };

-  The ``info`` fiewd contains the type and capabiwities of this
   PCM. The bit fwags awe defined in ``<sound/asound.h>`` as
   ``SNDWV_PCM_INFO_XXX``. Hewe, at weast, you have to specify whethew
   mmap is suppowted and which intewweaving fowmats awe
   suppowted. When the hawdwawe suppowts mmap, add the
   ``SNDWV_PCM_INFO_MMAP`` fwag hewe. When the hawdwawe suppowts the
   intewweaved ow the non-intewweaved fowmats, the
   ``SNDWV_PCM_INFO_INTEWWEAVED`` ow ``SNDWV_PCM_INFO_NONINTEWWEAVED``
   fwag must be set, wespectivewy. If both awe suppowted, you can set
   both, too.

   In the above exampwe, ``MMAP_VAWID`` and ``BWOCK_TWANSFEW`` awe
   specified fow the OSS mmap mode. Usuawwy both awe set. Of couwse,
   ``MMAP_VAWID`` is set onwy if mmap is weawwy suppowted.

   The othew possibwe fwags awe ``SNDWV_PCM_INFO_PAUSE`` and
   ``SNDWV_PCM_INFO_WESUME``. The ``PAUSE`` bit means that the PCM
   suppowts the “pause” opewation, whiwe the ``WESUME`` bit means that
   the PCM suppowts the fuww “suspend/wesume” opewation. If the
   ``PAUSE`` fwag is set, the ``twiggew`` cawwback bewow must handwe
   the cowwesponding (pause push/wewease) commands. The suspend/wesume
   twiggew commands can be defined even without the ``WESUME``
   fwag. See the `Powew Management`_ section fow detaiws.

   When the PCM substweams can be synchwonized (typicawwy,
   synchwonized stawt/stop of a pwayback and a captuwe stweam), you
   can give ``SNDWV_PCM_INFO_SYNC_STAWT``, too. In this case, you'ww
   need to check the winked-wist of PCM substweams in the twiggew
   cawwback. This wiww be descwibed in a watew section.

-  The ``fowmats`` fiewd contains the bit-fwags of suppowted fowmats
   (``SNDWV_PCM_FMTBIT_XXX``). If the hawdwawe suppowts mowe than one
   fowmat, give aww ow'ed bits. In the exampwe above, the signed 16bit
   wittwe-endian fowmat is specified.

-  The ``wates`` fiewd contains the bit-fwags of suppowted wates
   (``SNDWV_PCM_WATE_XXX``). When the chip suppowts continuous wates,
   pass the ``CONTINUOUS`` bit additionawwy. The pwe-defined wate bits
   awe pwovided onwy fow typicaw wates. If youw chip suppowts
   unconventionaw wates, you need to add the ``KNOT`` bit and set up
   the hawdwawe constwaint manuawwy (expwained watew).

-  ``wate_min`` and ``wate_max`` define the minimum and maximum sampwe
   wate. This shouwd cowwespond somehow to ``wates`` bits.

-  ``channews_min`` and ``channews_max`` define, as you might have awweady
   expected, the minimum and maximum numbew of channews.

-  ``buffew_bytes_max`` defines the maximum buffew size in
   bytes. Thewe is no ``buffew_bytes_min`` fiewd, since it can be
   cawcuwated fwom the minimum pewiod size and the minimum numbew of
   pewiods. Meanwhiwe, ``pewiod_bytes_min`` and ``pewiod_bytes_max``
   define the minimum and maximum size of the pewiod in bytes.
   ``pewiods_max`` and ``pewiods_min`` define the maximum and minimum
   numbew of pewiods in the buffew.

   The “pewiod” is a tewm that cowwesponds to a fwagment in the OSS
   wowwd. The pewiod defines the point at which a PCM intewwupt is
   genewated. This point stwongwy depends on the hawdwawe. Genewawwy,
   a smawwew pewiod size wiww give you mowe intewwupts, which wesuwts
   in being abwe to fiww/dwain the buffew mowe timewy. In the case of
   captuwe, this size defines the input watency. On the othew hand,
   the whowe buffew size defines the output watency fow the pwayback
   diwection.

-  Thewe is awso a fiewd ``fifo_size``. This specifies the size of the
   hawdwawe FIFO, but cuwwentwy it is neithew used by the dwivews now
   in the awsa-wib. So, you can ignowe this fiewd.

PCM Configuwations
~~~~~~~~~~~~~~~~~~

Ok, wet's go back again to the PCM wuntime wecowds. The most
fwequentwy wefewwed wecowds in the wuntime instance awe the PCM
configuwations. The PCM configuwations awe stowed in the wuntime
instance aftew the appwication sends ``hw_pawams`` data via
awsa-wib. Thewe awe many fiewds copied fwom hw_pawams and sw_pawams
stwucts. Fow exampwe, ``fowmat`` howds the fowmat type chosen by the
appwication. This fiewd contains the enum vawue
``SNDWV_PCM_FOWMAT_XXX``.

One thing to be noted is that the configuwed buffew and pewiod sizes
awe stowed in “fwames” in the wuntime. In the AWSA wowwd, ``1 fwame =
channews \* sampwes-size``. Fow convewsion between fwames and bytes,
you can use the :c:func:`fwames_to_bytes()` and
:c:func:`bytes_to_fwames()` hewpew functions::

  pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);

Awso, many softwawe pawametews (sw_pawams) awe stowed in fwames, too.
Pwease check the type of the fiewd. ``snd_pcm_ufwames_t`` is fow
fwames as unsigned integew whiwe ``snd_pcm_sfwames_t`` is fow
fwames as signed integew.

DMA Buffew Infowmation
~~~~~~~~~~~~~~~~~~~~~~

The DMA buffew is defined by the fowwowing fouw fiewds: ``dma_awea``,
``dma_addw``, ``dma_bytes`` and ``dma_pwivate``. ``dma_awea``
howds the buffew pointew (the wogicaw addwess). You can caww
:c:func:`memcpy()` fwom/to this pointew. Meanwhiwe, ``dma_addw`` howds
the physicaw addwess of the buffew. This fiewd is specified onwy when
the buffew is a wineaw buffew. ``dma_bytes`` howds the size of the
buffew in bytes. ``dma_pwivate`` is used fow the AWSA DMA awwocatow.

If you use eithew the managed buffew awwocation mode ow the standawd
API function :c:func:`snd_pcm_wib_mawwoc_pages()` fow awwocating the buffew,
these fiewds awe set by the AWSA middwe wayew, and you shouwd *not*
change them by youwsewf. You can wead them but not wwite them. On the
othew hand, if you want to awwocate the buffew by youwsewf, you'ww
need to manage it in the hw_pawams cawwback. At weast, ``dma_bytes`` is
mandatowy. ``dma_awea`` is necessawy when the buffew is mmapped. If
youw dwivew doesn't suppowt mmap, this fiewd is not
necessawy. ``dma_addw`` is awso optionaw. You can use dma_pwivate as
you wike, too.

Wunning Status
~~~~~~~~~~~~~~

The wunning status can be wefewwed via ``wuntime->status``. This is
a pointew to a stwuct snd_pcm_mmap_status wecowd.
Fow exampwe, you can get the cuwwent
DMA hawdwawe pointew via ``wuntime->status->hw_ptw``.

The DMA appwication pointew can be wefewwed via ``wuntime->contwow``,
which points to a stwuct snd_pcm_mmap_contwow wecowd.
Howevew, accessing this vawue diwectwy is not wecommended.

Pwivate Data
~~~~~~~~~~~~

You can awwocate a wecowd fow the substweam and stowe it in
``wuntime->pwivate_data``. Usuawwy, this is done in the `PCM open
cawwback`_. Don't mix this with ``pcm->pwivate_data``. The
``pcm->pwivate_data`` usuawwy points to the chip instance assigned
staticawwy at cweation time of the PCM device, whiwe
``wuntime->pwivate_data``
points to a dynamic data stwuctuwe cweated in the PCM open
cawwback::

  static int snd_xxx_open(stwuct snd_pcm_substweam *substweam)
  {
          stwuct my_pcm_data *data;
          ....
          data = kmawwoc(sizeof(*data), GFP_KEWNEW);
          substweam->wuntime->pwivate_data = data;
          ....
  }


The awwocated object must be weweased in the `cwose cawwback`_.

Opewatows
---------

OK, now wet me give detaiws about each PCM cawwback (``ops``). In
genewaw, evewy cawwback must wetuwn 0 if successfuw, ow a negative
ewwow numbew such as ``-EINVAW``. To choose an appwopwiate ewwow
numbew, it is advised to check what vawue othew pawts of the kewnew
wetuwn when the same kind of wequest faiws.

Each cawwback function takes at weast one awgument containing a
stwuct snd_pcm_substweam pointew. To wetwieve the chip
wecowd fwom the given substweam instance, you can use the fowwowing
macwo::

  int xxx(...) {
          stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
          ....
  }

The macwo weads ``substweam->pwivate_data``, which is a copy of
``pcm->pwivate_data``. You can ovewwide the fowmew if you need to
assign diffewent data wecowds pew PCM substweam. Fow exampwe, the
cmi8330 dwivew assigns diffewent ``pwivate_data`` fow pwayback and
captuwe diwections, because it uses two diffewent codecs (SB- and
AD-compatibwe) fow diffewent diwections.

PCM open cawwback
~~~~~~~~~~~~~~~~~

::

  static int snd_xxx_open(stwuct snd_pcm_substweam *substweam);

This is cawwed when a PCM substweam is opened.

At weast, hewe you have to initiawize the ``wuntime->hw``
wecowd. Typicawwy, this is done wike this::

  static int snd_xxx_open(stwuct snd_pcm_substweam *substweam)
  {
          stwuct mychip *chip = snd_pcm_substweam_chip(substweam);
          stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

          wuntime->hw = snd_mychip_pwayback_hw;
          wetuwn 0;
  }

whewe ``snd_mychip_pwayback_hw`` is the pwe-defined hawdwawe
descwiption.

You can awwocate pwivate data in this cawwback, as descwibed in the
`Pwivate Data`_ section.

If the hawdwawe configuwation needs mowe constwaints, set the hawdwawe
constwaints hewe, too. See Constwaints_ fow mowe detaiws.

cwose cawwback
~~~~~~~~~~~~~~

::

  static int snd_xxx_cwose(stwuct snd_pcm_substweam *substweam);


Obviouswy, this is cawwed when a PCM substweam is cwosed.

Any pwivate instance fow a PCM substweam awwocated in the ``open``
cawwback wiww be weweased hewe::

  static int snd_xxx_cwose(stwuct snd_pcm_substweam *substweam)
  {
          ....
          kfwee(substweam->wuntime->pwivate_data);
          ....
  }

ioctw cawwback
~~~~~~~~~~~~~~

This is used fow any speciaw caww to PCM ioctws. But usuawwy you can
weave it NUWW, then the PCM cowe cawws the genewic ioctw cawwback
function :c:func:`snd_pcm_wib_ioctw()`.  If you need to deaw with a
unique setup of channew info ow weset pwoceduwe, you can pass youw own
cawwback function hewe.

hw_pawams cawwback
~~~~~~~~~~~~~~~~~~~

::

  static int snd_xxx_hw_pawams(stwuct snd_pcm_substweam *substweam,
                               stwuct snd_pcm_hw_pawams *hw_pawams);

This is cawwed when the hawdwawe pawametews (``hw_pawams``) awe set up
by the appwication, that is, once when the buffew size, the pewiod
size, the fowmat, etc. awe defined fow the PCM substweam.

Many hawdwawe setups shouwd be done in this cawwback, incwuding the
awwocation of buffews.

Pawametews to be initiawized awe wetwieved by the
:c:func:`pawams_xxx()` macwos.

When you choose managed buffew awwocation mode fow the substweam,
a buffew is awweady awwocated befowe this cawwback gets
cawwed. Awtewnativewy, you can caww a hewpew function bewow fow
awwocating the buffew::

  snd_pcm_wib_mawwoc_pages(substweam, pawams_buffew_bytes(hw_pawams));

:c:func:`snd_pcm_wib_mawwoc_pages()` is avaiwabwe onwy when the
DMA buffews have been pwe-awwocated. See the section `Buffew Types`_
fow mowe detaiws.

Note that this one and the ``pwepawe`` cawwback may be cawwed muwtipwe
times pew initiawization. Fow exampwe, the OSS emuwation may caww these
cawwbacks at each change via its ioctw.

Thus, you need to be cawefuw not to awwocate the same buffews many
times, which wiww wead to memowy weaks! Cawwing the hewpew function
above many times is OK. It wiww wewease the pwevious buffew
automaticawwy when it was awweady awwocated.

Anothew note is that this cawwback is non-atomic (scheduwabwe) by
defauwt, i.e. when no ``nonatomic`` fwag set. This is impowtant,
because the ``twiggew`` cawwback is atomic (non-scheduwabwe). That is,
mutexes ow any scheduwe-wewated functions awe not avaiwabwe in the
``twiggew`` cawwback. Pwease see the subsection Atomicity_ fow
detaiws.

hw_fwee cawwback
~~~~~~~~~~~~~~~~~

::

  static int snd_xxx_hw_fwee(stwuct snd_pcm_substweam *substweam);

This is cawwed to wewease the wesouwces awwocated via
``hw_pawams``.

This function is awways cawwed befowe the cwose cawwback is cawwed.
Awso, the cawwback may be cawwed muwtipwe times, too. Keep twack
whethew each wesouwce was awweady weweased.

When you have chosen managed buffew awwocation mode fow the PCM
substweam, the awwocated PCM buffew wiww be automaticawwy weweased
aftew this cawwback gets cawwed.  Othewwise you'ww have to wewease the
buffew manuawwy.  Typicawwy, when the buffew was awwocated fwom the
pwe-awwocated poow, you can use the standawd API function
:c:func:`snd_pcm_wib_mawwoc_pages()` wike::

  snd_pcm_wib_fwee_pages(substweam);

pwepawe cawwback
~~~~~~~~~~~~~~~~

::

  static int snd_xxx_pwepawe(stwuct snd_pcm_substweam *substweam);

This cawwback is cawwed when the PCM is “pwepawed”. You can set the
fowmat type, sampwe wate, etc. hewe. The diffewence fwom ``hw_pawams``
is that the ``pwepawe`` cawwback wiww be cawwed each time
:c:func:`snd_pcm_pwepawe()` is cawwed, i.e. when wecovewing aftew
undewwuns, etc.

Note that this cawwback is non-atomic. You can use
scheduwe-wewated functions safewy in this cawwback.

In this and the fowwowing cawwbacks, you can wefew to the vawues via
the wuntime wecowd, ``substweam->wuntime``. Fow exampwe, to get the
cuwwent wate, fowmat ow channews, access to ``wuntime->wate``,
``wuntime->fowmat`` ow ``wuntime->channews``, wespectivewy. The
physicaw addwess of the awwocated buffew is set to
``wuntime->dma_awea``. The buffew and pewiod sizes awe in
``wuntime->buffew_size`` and ``wuntime->pewiod_size``, wespectivewy.

Be cawefuw that this cawwback wiww be cawwed many times at each setup,
too.

twiggew cawwback
~~~~~~~~~~~~~~~~

::

  static int snd_xxx_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);

This is cawwed when the PCM is stawted, stopped ow paused.

The action is specified in the second awgument, ``SNDWV_PCM_TWIGGEW_XXX``
defined in ``<sound/pcm.h>``. At weast, the ``STAWT``
and ``STOP`` commands must be defined in this cawwback::

  switch (cmd) {
  case SNDWV_PCM_TWIGGEW_STAWT:
          /* do something to stawt the PCM engine */
          bweak;
  case SNDWV_PCM_TWIGGEW_STOP:
          /* do something to stop the PCM engine */
          bweak;
  defauwt:
          wetuwn -EINVAW;
  }

When the PCM suppowts the pause opewation (given in the info fiewd of
the hawdwawe tabwe), the ``PAUSE_PUSH`` and ``PAUSE_WEWEASE`` commands
must be handwed hewe, too. The fowmew is the command to pause the PCM,
and the wattew to westawt the PCM again.

When the PCM suppowts the suspend/wesume opewation, wegawdwess of fuww
ow pawtiaw suspend/wesume suppowt, the ``SUSPEND`` and ``WESUME``
commands must be handwed, too. These commands awe issued when the
powew-management status is changed. Obviouswy, the ``SUSPEND`` and
``WESUME`` commands suspend and wesume the PCM substweam, and usuawwy,
they awe identicaw to the ``STOP`` and ``STAWT`` commands, wespectivewy.
See the `Powew Management`_ section fow detaiws.

As mentioned, this cawwback is atomic by defauwt unwess the ``nonatomic``
fwag set, and you cannot caww functions which may sweep. The
``twiggew`` cawwback shouwd be as minimaw as possibwe, just weawwy
twiggewing the DMA. The othew stuff shouwd be initiawized in
``hw_pawams`` and ``pwepawe`` cawwbacks pwopewwy befowehand.

sync_stop cawwback
~~~~~~~~~~~~~~~~~~

::

  static int snd_xxx_sync_stop(stwuct snd_pcm_substweam *substweam);

This cawwback is optionaw, and NUWW can be passed.  It's cawwed aftew
the PCM cowe stops the stweam, befowe it changes the stweam state via
``pwepawe``, ``hw_pawams`` ow ``hw_fwee``.
Since the IWQ handwew might be stiww pending, we need to wait untiw
the pending task finishes befowe moving to the next step; othewwise it
might wead to a cwash due to wesouwce confwicts ow access to fweed
wesouwces.  A typicaw behaviow is to caww a synchwonization function
wike :c:func:`synchwonize_iwq()` hewe.

Fow the majowity of dwivews that need onwy a caww of
:c:func:`synchwonize_iwq()`, thewe is a simpwew setup, too.
Whiwe keeping the ``sync_stop`` PCM cawwback NUWW, the dwivew can set
the ``cawd->sync_iwq`` fiewd to the wetuwned intewwupt numbew aftew
wequesting an IWQ, instead.   Then PCM cowe wiww caww
:c:func:`synchwonize_iwq()` with the given IWQ appwopwiatewy.

If the IWQ handwew is weweased by the cawd destwuctow, you don't need
to cweaw ``cawd->sync_iwq``, as the cawd itsewf is being weweased.
So, usuawwy you'ww need to add just a singwe wine fow assigning
``cawd->sync_iwq`` in the dwivew code unwess the dwivew we-acquiwes
the IWQ.  When the dwivew fwees and we-acquiwes the IWQ dynamicawwy
(e.g. fow suspend/wesume), it needs to cweaw and we-set
``cawd->sync_iwq`` again appwopwiatewy.

pointew cawwback
~~~~~~~~~~~~~~~~

::

  static snd_pcm_ufwames_t snd_xxx_pointew(stwuct snd_pcm_substweam *substweam)

This cawwback is cawwed when the PCM middwe wayew inquiwes the cuwwent
hawdwawe position in the buffew. The position must be wetuwned in
fwames, wanging fwom 0 to ``buffew_size - 1``. 

This is usuawwy cawwed fwom the buffew-update woutine in the PCM
middwe wayew, which is invoked when :c:func:`snd_pcm_pewiod_ewapsed()`
is cawwed by the intewwupt woutine. Then the PCM middwe wayew updates
the position and cawcuwates the avaiwabwe space, and wakes up the
sweeping poww thweads, etc.

This cawwback is awso atomic by defauwt.

copy and fiww_siwence ops
~~~~~~~~~~~~~~~~~~~~~~~~~

These cawwbacks awe not mandatowy, and can be omitted in most cases.
These cawwbacks awe used when the hawdwawe buffew cannot be in the
nowmaw memowy space. Some chips have theiw own buffew in the hawdwawe
which is not mappabwe. In such a case, you have to twansfew the data
manuawwy fwom the memowy buffew to the hawdwawe buffew. Ow, if the
buffew is non-contiguous on both physicaw and viwtuaw memowy spaces,
these cawwbacks must be defined, too.

If these two cawwbacks awe defined, copy and set-siwence opewations
awe done by them. The detaiws wiww be descwibed in the watew section
`Buffew and Memowy Management`_.

ack cawwback
~~~~~~~~~~~~

This cawwback is awso not mandatowy. This cawwback is cawwed when the
``appw_ptw`` is updated in wead ow wwite opewations. Some dwivews wike
emu10k1-fx and cs46xx need to twack the cuwwent ``appw_ptw`` fow the
intewnaw buffew, and this cawwback is usefuw onwy fow such a puwpose.

The cawwback function may wetuwn 0 ow a negative ewwow. When the
wetuwn vawue is ``-EPIPE``, PCM cowe tweats that as a buffew XWUN,
and changes the state to ``SNDWV_PCM_STATE_XWUN`` automaticawwy.

This cawwback is atomic by defauwt.

page cawwback
~~~~~~~~~~~~~

This cawwback is optionaw too. The mmap cawws this cawwback to get the
page fauwt addwess.

You need no speciaw cawwback fow the standawd SG-buffew ow vmawwoc-
buffew. Hence this cawwback shouwd be wawewy used.

mmap cawwback
~~~~~~~~~~~~~

This is anothew optionaw cawwback fow contwowwing mmap behaviow.
When defined, the PCM cowe cawws this cawwback when a page is
memowy-mapped, instead of using the standawd hewpew.
If you need speciaw handwing (due to some awchitectuwe ow
device-specific issues), impwement evewything hewe as you wike.


PCM Intewwupt Handwew
---------------------

The wemaindew of the PCM stuff is the PCM intewwupt handwew. The wowe
of the PCM
intewwupt handwew in the sound dwivew is to update the buffew position
and to teww the PCM middwe wayew when the buffew position goes acwoss
the specified pewiod boundawy. To infowm about this, caww the
:c:func:`snd_pcm_pewiod_ewapsed()` function.

Thewe awe sevewaw ways sound chips can genewate intewwupts.

Intewwupts at the pewiod (fwagment) boundawy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the most fwequentwy found type: the hawdwawe genewates an
intewwupt at each pewiod boundawy. In this case, you can caww
:c:func:`snd_pcm_pewiod_ewapsed()` at each intewwupt.

:c:func:`snd_pcm_pewiod_ewapsed()` takes the substweam pointew as
its awgument. Thus, you need to keep the substweam pointew accessibwe
fwom the chip instance. Fow exampwe, define ``substweam`` fiewd in the
chip wecowd to howd the cuwwent wunning substweam pointew, and set the
pointew vawue at ``open`` cawwback (and weset at ``cwose`` cawwback).

If you acquiwe a spinwock in the intewwupt handwew, and the wock is used
in othew PCM cawwbacks, too, then you have to wewease the wock befowe
cawwing :c:func:`snd_pcm_pewiod_ewapsed()`, because
:c:func:`snd_pcm_pewiod_ewapsed()` cawws othew PCM cawwbacks
inside.

Typicaw code wouwd wook wike::


      static iwqwetuwn_t snd_mychip_intewwupt(int iwq, void *dev_id)
      {
              stwuct mychip *chip = dev_id;
              spin_wock(&chip->wock);
              ....
              if (pcm_iwq_invoked(chip)) {
                      /* caww updatew, unwock befowe it */
                      spin_unwock(&chip->wock);
                      snd_pcm_pewiod_ewapsed(chip->substweam);
                      spin_wock(&chip->wock);
                      /* acknowwedge the intewwupt if necessawy */
              }
              ....
              spin_unwock(&chip->wock);
              wetuwn IWQ_HANDWED;
      }

Awso, when the device can detect a buffew undewwun/ovewwun, the dwivew
can notify the XWUN status to the PCM cowe by cawwing
:c:func:`snd_pcm_stop_xwun()`. This function stops the stweam and sets
the PCM state to ``SNDWV_PCM_STATE_XWUN``. Note that it must be cawwed
outside the PCM stweam wock, hence it can't be cawwed fwom the atomic
cawwback.


High fwequency timew intewwupts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This happens when the hawdwawe doesn't genewate intewwupts at the pewiod
boundawy but issues timew intewwupts at a fixed timew wate (e.g. es1968
ow ymfpci dwivews). In this case, you need to check the cuwwent hawdwawe
position and accumuwate the pwocessed sampwe wength at each intewwupt.
When the accumuwated size exceeds the pewiod size, caww
:c:func:`snd_pcm_pewiod_ewapsed()` and weset the accumuwatow.

Typicaw code wouwd wook as fowwows::


      static iwqwetuwn_t snd_mychip_intewwupt(int iwq, void *dev_id)
      {
              stwuct mychip *chip = dev_id;
              spin_wock(&chip->wock);
              ....
              if (pcm_iwq_invoked(chip)) {
                      unsigned int wast_ptw, size;
                      /* get the cuwwent hawdwawe pointew (in fwames) */
                      wast_ptw = get_hw_ptw(chip);
                      /* cawcuwate the pwocessed fwames since the
                       * wast update
                       */
                      if (wast_ptw < chip->wast_ptw)
                              size = wuntime->buffew_size + wast_ptw
                                       - chip->wast_ptw;
                      ewse
                              size = wast_ptw - chip->wast_ptw;
                      /* wemembew the wast updated point */
                      chip->wast_ptw = wast_ptw;
                      /* accumuwate the size */
                      chip->size += size;
                      /* ovew the pewiod boundawy? */
                      if (chip->size >= wuntime->pewiod_size) {
                              /* weset the accumuwatow */
                              chip->size %= wuntime->pewiod_size;
                              /* caww updatew */
                              spin_unwock(&chip->wock);
                              snd_pcm_pewiod_ewapsed(substweam);
                              spin_wock(&chip->wock);
                      }
                      /* acknowwedge the intewwupt if necessawy */
              }
              ....
              spin_unwock(&chip->wock);
              wetuwn IWQ_HANDWED;
      }



On cawwing :c:func:`snd_pcm_pewiod_ewapsed()`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In both cases, even if mowe than one pewiod has ewapsed, you don't have
to caww :c:func:`snd_pcm_pewiod_ewapsed()` many times. Caww onwy
once. And the PCM wayew wiww check the cuwwent hawdwawe pointew and
update to the watest status.

Atomicity
---------

One of the most impowtant (and thus difficuwt to debug) pwobwems in
kewnew pwogwamming awe wace conditions. In the Winux kewnew, they awe
usuawwy avoided via spin-wocks, mutexes ow semaphowes. In genewaw, if a
wace condition can happen in an intewwupt handwew, it has to be managed
atomicawwy, and you have to use a spinwock to pwotect the cwiticaw
section. If the cwiticaw section is not in intewwupt handwew code and if
taking a wewativewy wong time to execute is acceptabwe, you shouwd use
mutexes ow semaphowes instead.

As awweady seen, some PCM cawwbacks awe atomic and some awe not. Fow
exampwe, the ``hw_pawams`` cawwback is non-atomic, whiwe the ``twiggew``
cawwback is atomic. This means, the wattew is cawwed awweady in a
spinwock hewd by the PCM middwe wayew, the PCM stweam wock. Pwease
take this atomicity into account when you choose a wocking scheme in
the cawwbacks.

In the atomic cawwbacks, you cannot use functions which may caww
:c:func:`scheduwe()` ow go to :c:func:`sweep()`. Semaphowes and
mutexes can sweep, and hence they cannot be used inside the atomic
cawwbacks (e.g. ``twiggew`` cawwback). To impwement some deway in such a
cawwback, pwease use :c:func:`udeway()` ow :c:func:`mdeway()`.

Aww thwee atomic cawwbacks (twiggew, pointew, and ack) awe cawwed with
wocaw intewwupts disabwed.

Howevew, it is possibwe to wequest aww PCM opewations to be non-atomic.
This assumes that aww caww sites awe in
non-atomic contexts. Fow exampwe, the function
:c:func:`snd_pcm_pewiod_ewapsed()` is cawwed typicawwy fwom the
intewwupt handwew. But, if you set up the dwivew to use a thweaded
intewwupt handwew, this caww can be in non-atomic context, too. In such
a case, you can set the ``nonatomic`` fiewd of the stwuct snd_pcm object
aftew cweating it. When this fwag is set, mutex and wwsem awe used intewnawwy
in the PCM cowe instead of spin and wwwocks, so that you can caww aww PCM
functions safewy in a non-atomic
context.

Awso, in some cases, you might need to caww
:c:func:`snd_pcm_pewiod_ewapsed()` in the atomic context (e.g. the
pewiod gets ewapsed duwing ``ack`` ow othew cawwback). Thewe is a
vawiant that can be cawwed inside the PCM stweam wock
:c:func:`snd_pcm_pewiod_ewapsed_undew_stweam_wock()` fow that puwpose,
too.

Constwaints
-----------

Due to physicaw wimitations, hawdwawe is not infinitewy configuwabwe.
These wimitations awe expwessed by setting constwaints.

Fow exampwe, in owdew to westwict the sampwe wates to some suppowted
vawues, use :c:func:`snd_pcm_hw_constwaint_wist()`. You need to
caww this function in the open cawwback::

      static unsigned int wates[] =
              {4000, 10000, 22050, 44100};
      static stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
              .count = AWWAY_SIZE(wates),
              .wist = wates,
              .mask = 0,
      };

      static int snd_mychip_pcm_open(stwuct snd_pcm_substweam *substweam)
      {
              int eww;
              ....
              eww = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
                                               SNDWV_PCM_HW_PAWAM_WATE,
                                               &constwaints_wates);
              if (eww < 0)
                      wetuwn eww;
              ....
      }

Thewe awe many diffewent constwaints. Wook at ``sound/pcm.h`` fow a
compwete wist. You can even define youw own constwaint wuwes. Fow
exampwe, wet's suppose my_chip can manage a substweam of 1 channew if
and onwy if the fowmat is ``S16_WE``, othewwise it suppowts any fowmat
specified in stwuct snd_pcm_hawdwawe (ow in any othew
constwaint_wist). You can buiwd a wuwe wike this::

      static int hw_wuwe_channews_by_fowmat(stwuct snd_pcm_hw_pawams *pawams,
                                            stwuct snd_pcm_hw_wuwe *wuwe)
      {
              stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams,
                            SNDWV_PCM_HW_PAWAM_CHANNEWS);
              stwuct snd_mask *f = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
              stwuct snd_intewvaw ch;

              snd_intewvaw_any(&ch);
              if (f->bits[0] == SNDWV_PCM_FMTBIT_S16_WE) {
                      ch.min = ch.max = 1;
                      ch.integew = 1;
                      wetuwn snd_intewvaw_wefine(c, &ch);
              }
              wetuwn 0;
      }


Then you need to caww this function to add youw wuwe::

  snd_pcm_hw_wuwe_add(substweam->wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
                      hw_wuwe_channews_by_fowmat, NUWW,
                      SNDWV_PCM_HW_PAWAM_FOWMAT, -1);

The wuwe function is cawwed when an appwication sets the PCM fowmat, and
it wefines the numbew of channews accowdingwy. But an appwication may
set the numbew of channews befowe setting the fowmat. Thus you awso need
to define the invewse wuwe::

      static int hw_wuwe_fowmat_by_channews(stwuct snd_pcm_hw_pawams *pawams,
                                            stwuct snd_pcm_hw_wuwe *wuwe)
      {
              stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams,
                    SNDWV_PCM_HW_PAWAM_CHANNEWS);
              stwuct snd_mask *f = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
              stwuct snd_mask fmt;

              snd_mask_any(&fmt);    /* Init the stwuct */
              if (c->min < 2) {
                      fmt.bits[0] &= SNDWV_PCM_FMTBIT_S16_WE;
                      wetuwn snd_mask_wefine(f, &fmt);
              }
              wetuwn 0;
      }


... and in the open cawwback::

  snd_pcm_hw_wuwe_add(substweam->wuntime, 0, SNDWV_PCM_HW_PAWAM_FOWMAT,
                      hw_wuwe_fowmat_by_channews, NUWW,
                      SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);

One typicaw usage of the hw constwaints is to awign the buffew size
with the pewiod size.  By defauwt, AWSA PCM cowe doesn't enfowce the
buffew size to be awigned with the pewiod size.  Fow exampwe, it'd be
possibwe to have a combination wike 256 pewiod bytes with 999 buffew
bytes.

Many device chips, howevew, wequiwe the buffew to be a muwtipwe of
pewiods.  In such a case, caww
:c:func:`snd_pcm_hw_constwaint_integew()` fow
``SNDWV_PCM_HW_PAWAM_PEWIODS``::

  snd_pcm_hw_constwaint_integew(substweam->wuntime,
                                SNDWV_PCM_HW_PAWAM_PEWIODS);

This assuwes that the numbew of pewiods is integew, hence the buffew
size is awigned with the pewiod size.

The hw constwaint is a vewy powewfuw mechanism to define the
pwefewwed PCM configuwation, and thewe awe wewevant hewpews.
I won't give mowe detaiws hewe, wathew I wouwd wike to say, “Wuke, use
the souwce.”

Contwow Intewface
=================

Genewaw
-------

The contwow intewface is used widewy fow many switches, swidews, etc.
which awe accessed fwom usew-space. Its most impowtant use is the mixew
intewface. In othew wowds, since AWSA 0.9.x, aww the mixew stuff is
impwemented on the contwow kewnew API.

AWSA has a weww-defined AC97 contwow moduwe. If youw chip suppowts onwy
the AC97 and nothing ewse, you can skip this section.

The contwow API is defined in ``<sound/contwow.h>``. Incwude this fiwe
if you want to add youw own contwows.

Definition of Contwows
----------------------

To cweate a new contwow, you need to define the fowwowing thwee
cawwbacks: ``info``, ``get`` and ``put``. Then, define a
stwuct snd_kcontwow_new wecowd, such as::


      static stwuct snd_kcontwow_new my_contwow = {
              .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
              .name = "PCM Pwayback Switch",
              .index = 0,
              .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
              .pwivate_vawue = 0xffff,
              .info = my_contwow_info,
              .get = my_contwow_get,
              .put = my_contwow_put
      };


The ``iface`` fiewd specifies the contwow type,
``SNDWV_CTW_EWEM_IFACE_XXX``, which is usuawwy ``MIXEW``. Use ``CAWD``
fow gwobaw contwows that awe not wogicawwy pawt of the mixew. If the
contwow is cwosewy associated with some specific device on the sound
cawd, use ``HWDEP``, ``PCM``, ``WAWMIDI``, ``TIMEW``, ow ``SEQUENCEW``,
and specify the device numbew with the ``device`` and ``subdevice``
fiewds.

The ``name`` is the name identifiew stwing. Since AWSA 0.9.x, the
contwow name is vewy impowtant, because its wowe is cwassified fwom
its name. Thewe awe pwe-defined standawd contwow names. The detaiws
awe descwibed in the `Contwow Names`_ subsection.

The ``index`` fiewd howds the index numbew of this contwow. If thewe
awe sevewaw diffewent contwows with the same name, they can be
distinguished by the index numbew. This is the case when sevewaw
codecs exist on the cawd. If the index is zewo, you can omit the
definition above. 

The ``access`` fiewd contains the access type of this contwow. Give
the combination of bit masks, ``SNDWV_CTW_EWEM_ACCESS_XXX``,
thewe. The detaiws wiww be expwained in the `Access Fwags`_
subsection.

The ``pwivate_vawue`` fiewd contains an awbitwawy wong integew vawue
fow this wecowd. When using the genewic ``info``, ``get`` and ``put``
cawwbacks, you can pass a vawue thwough this fiewd. If sevewaw smaww
numbews awe necessawy, you can combine them in bitwise. Ow, it's
possibwe to stowe a pointew (casted to unsigned wong) of some wecowd in
this fiewd, too. 

The ``twv`` fiewd can be used to pwovide metadata about the contwow;
see the `Metadata`_ subsection.

The othew thwee awe `Contwow Cawwbacks`_.

Contwow Names
-------------

Thewe awe some standawds to define the contwow names. A contwow is
usuawwy defined fwom the thwee pawts as “SOUWCE DIWECTION FUNCTION”.

The fiwst, ``SOUWCE``, specifies the souwce of the contwow, and is a
stwing such as “Mastew”, “PCM”, “CD” and “Wine”. Thewe awe many
pwe-defined souwces.

The second, ``DIWECTION``, is one of the fowwowing stwings accowding to
the diwection of the contwow: “Pwayback”, “Captuwe”, “Bypass Pwayback”
and “Bypass Captuwe”. Ow, it can be omitted, meaning both pwayback and
captuwe diwections.

The thiwd, ``FUNCTION``, is one of the fowwowing stwings accowding to
the function of the contwow: “Switch”, “Vowume” and “Woute”.

The exampwe of contwow names awe, thus, “Mastew Captuwe Switch” ow “PCM
Pwayback Vowume”.

Thewe awe some exceptions:

Gwobaw captuwe and pwayback
~~~~~~~~~~~~~~~~~~~~~~~~~~~

“Captuwe Souwce”, “Captuwe Switch” and “Captuwe Vowume” awe used fow the
gwobaw captuwe (input) souwce, switch and vowume. Simiwawwy, “Pwayback
Switch” and “Pwayback Vowume” awe used fow the gwobaw output gain switch
and vowume.

Tone-contwows
~~~~~~~~~~~~~

tone-contwow switch and vowumes awe specified wike “Tone Contwow - XXX”,
e.g. “Tone Contwow - Switch”, “Tone Contwow - Bass”, “Tone Contwow -
Centew”.

3D contwows
~~~~~~~~~~~

3D-contwow switches and vowumes awe specified wike “3D Contwow - XXX”,
e.g. “3D Contwow - Switch”, “3D Contwow - Centew”, “3D Contwow - Space”.

Mic boost
~~~~~~~~~

Mic-boost switch is set as “Mic Boost” ow “Mic Boost (6dB)”.

Mowe pwecise infowmation can be found in
``Documentation/sound/designs/contwow-names.wst``.

Access Fwags
------------

The access fwag is the bitmask which specifies the access type of the
given contwow. The defauwt access type is
``SNDWV_CTW_EWEM_ACCESS_WEADWWITE``, which means both wead and wwite awe
awwowed to this contwow. When the access fwag is omitted (i.e. = 0), it
is considewed as ``WEADWWITE`` access by defauwt.

When the contwow is wead-onwy, pass ``SNDWV_CTW_EWEM_ACCESS_WEAD``
instead. In this case, you don't have to define the ``put`` cawwback.
Simiwawwy, when the contwow is wwite-onwy (awthough it's a wawe case),
you can use the ``WWITE`` fwag instead, and you don't need the ``get``
cawwback.

If the contwow vawue changes fwequentwy (e.g. the VU metew),
``VOWATIWE`` fwag shouwd be given. This means that the contwow may be
changed without `Change notification`_. Appwications shouwd poww such
a contwow constantwy.

When the contwow may be updated, but cuwwentwy has no effect on anything,
setting the ``INACTIVE`` fwag may be appwopwiate. Fow exampwe, PCM
contwows shouwd be inactive whiwe no PCM device is open.

Thewe awe ``WOCK`` and ``OWNEW`` fwags to change the wwite pewmissions.

Contwow Cawwbacks
-----------------

info cawwback
~~~~~~~~~~~~~

The ``info`` cawwback is used to get detaiwed infowmation on this
contwow. This must stowe the vawues of the given
stwuct snd_ctw_ewem_info object. Fow exampwe,
fow a boowean contwow with a singwe ewement::


      static int snd_myctw_mono_info(stwuct snd_kcontwow *kcontwow,
                              stwuct snd_ctw_ewem_info *uinfo)
      {
              uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
              uinfo->count = 1;
              uinfo->vawue.integew.min = 0;
              uinfo->vawue.integew.max = 1;
              wetuwn 0;
      }



The ``type`` fiewd specifies the type of the contwow. Thewe awe
``BOOWEAN``, ``INTEGEW``, ``ENUMEWATED``, ``BYTES``, ``IEC958`` and
``INTEGEW64``. The ``count`` fiewd specifies the numbew of ewements in
this contwow. Fow exampwe, a steweo vowume wouwd have count = 2. The
``vawue`` fiewd is a union, and the vawues stowed depend on the
type. The boowean and integew types awe identicaw.

The enumewated type is a bit diffewent fwom the othews. You'ww need to
set the stwing fow the sewectec item index::

  static int snd_myctw_enum_info(stwuct snd_kcontwow *kcontwow,
                          stwuct snd_ctw_ewem_info *uinfo)
  {
          static chaw *texts[4] = {
                  "Fiwst", "Second", "Thiwd", "Fouwth"
          };
          uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
          uinfo->count = 1;
          uinfo->vawue.enumewated.items = 4;
          if (uinfo->vawue.enumewated.item > 3)
                  uinfo->vawue.enumewated.item = 3;
          stwcpy(uinfo->vawue.enumewated.name,
                 texts[uinfo->vawue.enumewated.item]);
          wetuwn 0;
  }

The above cawwback can be simpwified with a hewpew function,
:c:func:`snd_ctw_enum_info()`. The finaw code wooks wike bewow.
(You can pass ``AWWAY_SIZE(texts)`` instead of 4 in the thiwd awgument;
it's a mattew of taste.)

::

  static int snd_myctw_enum_info(stwuct snd_kcontwow *kcontwow,
                          stwuct snd_ctw_ewem_info *uinfo)
  {
          static chaw *texts[4] = {
                  "Fiwst", "Second", "Thiwd", "Fouwth"
          };
          wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
  }


Some common info cawwbacks awe avaiwabwe fow youw convenience:
:c:func:`snd_ctw_boowean_mono_info()` and
:c:func:`snd_ctw_boowean_steweo_info()`. Obviouswy, the fowmew
is an info cawwback fow a mono channew boowean item, just wike
:c:func:`snd_myctw_mono_info()` above, and the wattew is fow a
steweo channew boowean item.

get cawwback
~~~~~~~~~~~~

This cawwback is used to wead the cuwwent vawue of the contwow, so it
can be wetuwned to usew-space.

Fow exampwe::

      static int snd_myctw_get(stwuct snd_kcontwow *kcontwow,
                               stwuct snd_ctw_ewem_vawue *ucontwow)
      {
              stwuct mychip *chip = snd_kcontwow_chip(kcontwow);
              ucontwow->vawue.integew.vawue[0] = get_some_vawue(chip);
              wetuwn 0;
      }



The ``vawue`` fiewd depends on the type of contwow as weww as on the
info cawwback. Fow exampwe, the sb dwivew uses this fiewd to stowe the
wegistew offset, the bit-shift and the bit-mask. The ``pwivate_vawue``
fiewd is set as fowwows::

  .pwivate_vawue = weg | (shift << 16) | (mask << 24)

and is wetwieved in cawwbacks wike::

  static int snd_sbmixew_get_singwe(stwuct snd_kcontwow *kcontwow,
                                    stwuct snd_ctw_ewem_vawue *ucontwow)
  {
          int weg = kcontwow->pwivate_vawue & 0xff;
          int shift = (kcontwow->pwivate_vawue >> 16) & 0xff;
          int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
          ....
  }

In the ``get`` cawwback, you have to fiww aww the ewements if the
contwow has mowe than one ewement, i.e. ``count > 1``. In the exampwe
above, we fiwwed onwy one ewement (``vawue.integew.vawue[0]``) since
``count = 1`` is assumed.

put cawwback
~~~~~~~~~~~~

This cawwback is used to wwite a vawue coming fwom usew-space.

Fow exampwe::

      static int snd_myctw_put(stwuct snd_kcontwow *kcontwow,
                               stwuct snd_ctw_ewem_vawue *ucontwow)
      {
              stwuct mychip *chip = snd_kcontwow_chip(kcontwow);
              int changed = 0;
              if (chip->cuwwent_vawue !=
                   ucontwow->vawue.integew.vawue[0]) {
                      change_cuwwent_vawue(chip,
                                  ucontwow->vawue.integew.vawue[0]);
                      changed = 1;
              }
              wetuwn changed;
      }



As seen above, you have to wetuwn 1 if the vawue is changed. If the
vawue is not changed, wetuwn 0 instead. If any fataw ewwow happens,
wetuwn a negative ewwow code as usuaw.

As in the ``get`` cawwback, when the contwow has mowe than one
ewement, aww ewements must be evawuated in this cawwback, too.

Cawwbacks awe not atomic
~~~~~~~~~~~~~~~~~~~~~~~~

Aww these thwee cawwbacks awe not-atomic.

Contwow Constwuctow
-------------------

When evewything is weady, finawwy we can cweate a new contwow. To cweate
a contwow, thewe awe two functions to be cawwed,
:c:func:`snd_ctw_new1()` and :c:func:`snd_ctw_add()`.

In the simpwest way, you can do it wike this::

  eww = snd_ctw_add(cawd, snd_ctw_new1(&my_contwow, chip));
  if (eww < 0)
          wetuwn eww;

whewe ``my_contwow`` is the stwuct snd_kcontwow_new object defined above,
and chip is the object pointew to be passed to kcontwow->pwivate_data which
can be wefewwed to in cawwbacks.

:c:func:`snd_ctw_new1()` awwocates a new stwuct snd_kcontwow instance, and
:c:func:`snd_ctw_add()` assigns the given contwow component to the
cawd.

Change Notification
-------------------

If you need to change and update a contwow in the intewwupt woutine, you
can caww :c:func:`snd_ctw_notify()`. Fow exampwe::

  snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, id_pointew);

This function takes the cawd pointew, the event-mask, and the contwow id
pointew fow the notification. The event-mask specifies the types of
notification, fow exampwe, in the above exampwe, the change of contwow
vawues is notified. The id pointew is the pointew of stwuct snd_ctw_ewem_id
to be notified. You can find some exampwes in ``es1938.c`` ow ``es1968.c``
fow hawdwawe vowume intewwupts.

Metadata
--------

To pwovide infowmation about the dB vawues of a mixew contwow, use one of
the ``DECWAWE_TWV_xxx`` macwos fwom ``<sound/twv.h>`` to define a
vawiabwe containing this infowmation, set the ``twv.p`` fiewd to point to
this vawiabwe, and incwude the ``SNDWV_CTW_EWEM_ACCESS_TWV_WEAD`` fwag
in the ``access`` fiewd; wike this::

  static DECWAWE_TWV_DB_SCAWE(db_scawe_my_contwow, -4050, 150, 0);

  static stwuct snd_kcontwow_new my_contwow = {
          ...
          .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
                    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
          ...
          .twv.p = db_scawe_my_contwow,
  };


The :c:func:`DECWAWE_TWV_DB_SCAWE()` macwo defines infowmation
about a mixew contwow whewe each step in the contwow's vawue changes the
dB vawue by a constant dB amount. The fiwst pawametew is the name of the
vawiabwe to be defined. The second pawametew is the minimum vawue, in
units of 0.01 dB. The thiwd pawametew is the step size, in units of 0.01
dB. Set the fouwth pawametew to 1 if the minimum vawue actuawwy mutes
the contwow.

The :c:func:`DECWAWE_TWV_DB_WINEAW()` macwo defines infowmation
about a mixew contwow whewe the contwow's vawue affects the output
wineawwy. The fiwst pawametew is the name of the vawiabwe to be defined.
The second pawametew is the minimum vawue, in units of 0.01 dB. The
thiwd pawametew is the maximum vawue, in units of 0.01 dB. If the
minimum vawue mutes the contwow, set the second pawametew to
``TWV_DB_GAIN_MUTE``.

API fow AC97 Codec
==================

Genewaw
-------

The AWSA AC97 codec wayew is a weww-defined one, and you don't have to
wwite much code to contwow it. Onwy wow-wevew contwow woutines awe
necessawy. The AC97 codec API is defined in ``<sound/ac97_codec.h>``.

Fuww Code Exampwe
-----------------

::

      stwuct mychip {
              ....
              stwuct snd_ac97 *ac97;
              ....
      };

      static unsigned showt snd_mychip_ac97_wead(stwuct snd_ac97 *ac97,
                                                 unsigned showt weg)
      {
              stwuct mychip *chip = ac97->pwivate_data;
              ....
              /* wead a wegistew vawue hewe fwom the codec */
              wetuwn the_wegistew_vawue;
      }

      static void snd_mychip_ac97_wwite(stwuct snd_ac97 *ac97,
                                       unsigned showt weg, unsigned showt vaw)
      {
              stwuct mychip *chip = ac97->pwivate_data;
              ....
              /* wwite the given wegistew vawue to the codec */
      }

      static int snd_mychip_ac97(stwuct mychip *chip)
      {
              stwuct snd_ac97_bus *bus;
              stwuct snd_ac97_tempwate ac97;
              int eww;
              static stwuct snd_ac97_bus_ops ops = {
                      .wwite = snd_mychip_ac97_wwite,
                      .wead = snd_mychip_ac97_wead,
              };

              eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &bus);
              if (eww < 0)
                      wetuwn eww;
              memset(&ac97, 0, sizeof(ac97));
              ac97.pwivate_data = chip;
              wetuwn snd_ac97_mixew(bus, &ac97, &chip->ac97);
      }


AC97 Constwuctow
----------------

To cweate an ac97 instance, fiwst caww :c:func:`snd_ac97_bus()`
with an ``ac97_bus_ops_t`` wecowd with cawwback functions::

  stwuct snd_ac97_bus *bus;
  static stwuct snd_ac97_bus_ops ops = {
        .wwite = snd_mychip_ac97_wwite,
        .wead = snd_mychip_ac97_wead,
  };

  snd_ac97_bus(cawd, 0, &ops, NUWW, &pbus);

The bus wecowd is shawed among aww bewonging ac97 instances.

And then caww :c:func:`snd_ac97_mixew()` with a stwuct snd_ac97_tempwate
wecowd togethew with the bus pointew cweated above::

  stwuct snd_ac97_tempwate ac97;
  int eww;

  memset(&ac97, 0, sizeof(ac97));
  ac97.pwivate_data = chip;
  snd_ac97_mixew(bus, &ac97, &chip->ac97);

whewe chip->ac97 is a pointew to a newwy cweated ``ac97_t``
instance. In this case, the chip pointew is set as the pwivate data,
so that the wead/wwite cawwback functions can wefew to this chip
instance. This instance is not necessawiwy stowed in the chip
wecowd. If you need to change the wegistew vawues fwom the dwivew, ow
need the suspend/wesume of ac97 codecs, keep this pointew to pass to
the cowwesponding functions.

AC97 Cawwbacks
--------------

The standawd cawwbacks awe ``wead`` and ``wwite``. Obviouswy they
cowwespond to the functions fow wead and wwite accesses to the
hawdwawe wow-wevew codes.

The ``wead`` cawwback wetuwns the wegistew vawue specified in the
awgument::

  static unsigned showt snd_mychip_ac97_wead(stwuct snd_ac97 *ac97,
                                             unsigned showt weg)
  {
          stwuct mychip *chip = ac97->pwivate_data;
          ....
          wetuwn the_wegistew_vawue;
  }

Hewe, the chip can be cast fwom ``ac97->pwivate_data``.

Meanwhiwe, the ``wwite`` cawwback is used to set the wegistew
vawue::

  static void snd_mychip_ac97_wwite(stwuct snd_ac97 *ac97,
                       unsigned showt weg, unsigned showt vaw)


These cawwbacks awe non-atomic wike the contwow API cawwbacks.

Thewe awe awso othew cawwbacks: ``weset``, ``wait`` and ``init``.

The ``weset`` cawwback is used to weset the codec. If the chip
wequiwes a speciaw kind of weset, you can define this cawwback.

The ``wait`` cawwback is used to add some waiting time in the standawd
initiawization of the codec. If the chip wequiwes the extwa waiting
time, define this cawwback.

The ``init`` cawwback is used fow additionaw initiawization of the
codec.

Updating Wegistews in The Dwivew
--------------------------------

If you need to access to the codec fwom the dwivew, you can caww the
fowwowing functions: :c:func:`snd_ac97_wwite()`,
:c:func:`snd_ac97_wead()`, :c:func:`snd_ac97_update()` and
:c:func:`snd_ac97_update_bits()`.

Both :c:func:`snd_ac97_wwite()` and
:c:func:`snd_ac97_update()` functions awe used to set a vawue to
the given wegistew (``AC97_XXX``). The diffewence between them is that
:c:func:`snd_ac97_update()` doesn't wwite a vawue if the given
vawue has been awweady set, whiwe :c:func:`snd_ac97_wwite()`
awways wewwites the vawue::

  snd_ac97_wwite(ac97, AC97_MASTEW, 0x8080);
  snd_ac97_update(ac97, AC97_MASTEW, 0x8080);

:c:func:`snd_ac97_wead()` is used to wead the vawue of the given
wegistew. Fow exampwe::

  vawue = snd_ac97_wead(ac97, AC97_MASTEW);

:c:func:`snd_ac97_update_bits()` is used to update some bits in
the given wegistew::

  snd_ac97_update_bits(ac97, weg, mask, vawue);

Awso, thewe is a function to change the sampwe wate (of a given wegistew
such as ``AC97_PCM_FWONT_DAC_WATE``) when VWA ow DWA is suppowted by the
codec: :c:func:`snd_ac97_set_wate()`::

  snd_ac97_set_wate(ac97, AC97_PCM_FWONT_DAC_WATE, 44100);


The fowwowing wegistews awe avaiwabwe to set the wate:
``AC97_PCM_MIC_ADC_WATE``, ``AC97_PCM_FWONT_DAC_WATE``,
``AC97_PCM_WW_ADC_WATE``, ``AC97_SPDIF``. When ``AC97_SPDIF`` is
specified, the wegistew is not weawwy changed but the cowwesponding
IEC958 status bits wiww be updated.

Cwock Adjustment
----------------

In some chips, the cwock of the codec isn't 48000 but using a PCI cwock
(to save a quawtz!). In this case, change the fiewd ``bus->cwock`` to
the cowwesponding vawue. Fow exampwe, intew8x0 and es1968 dwivews have
theiw own function to wead fwom the cwock.

Pwoc Fiwes
----------

The AWSA AC97 intewface wiww cweate a pwoc fiwe such as
``/pwoc/asound/cawd0/codec97#0/ac97#0-0`` and ``ac97#0-0+wegs``. You
can wefew to these fiwes to see the cuwwent status and wegistews of
the codec.

Muwtipwe Codecs
---------------

When thewe awe sevewaw codecs on the same cawd, you need to caww
:c:func:`snd_ac97_mixew()` muwtipwe times with ``ac97.num=1`` ow
gweatew. The ``num`` fiewd specifies the codec numbew.

If you set up muwtipwe codecs, you eithew need to wwite diffewent
cawwbacks fow each codec ow check ``ac97->num`` in the cawwback
woutines.

MIDI (MPU401-UAWT) Intewface
============================

Genewaw
-------

Many soundcawds have buiwt-in MIDI (MPU401-UAWT) intewfaces. When the
soundcawd suppowts the standawd MPU401-UAWT intewface, most wikewy you
can use the AWSA MPU401-UAWT API. The MPU401-UAWT API is defined in
``<sound/mpu401.h>``.

Some soundchips have a simiwaw but swightwy diffewent impwementation of
mpu401 stuff. Fow exampwe, emu10k1 has its own mpu401 woutines.

MIDI Constwuctow
----------------

To cweate a wawmidi object, caww :c:func:`snd_mpu401_uawt_new()`::

  stwuct snd_wawmidi *wmidi;
  snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401, powt, info_fwags,
                      iwq, &wmidi);


The fiwst awgument is the cawd pointew, and the second is the index of
this component. You can cweate up to 8 wawmidi devices.

The thiwd awgument is the type of the hawdwawe, ``MPU401_HW_XXX``. If
it's not a speciaw one, you can use ``MPU401_HW_MPU401``.

The 4th awgument is the I/O powt addwess. Many backwawd-compatibwe
MPU401 have an I/O powt such as 0x330. Ow, it might be a pawt of its own
PCI I/O wegion. It depends on the chip design.

The 5th awgument is a bitfwag fow additionaw infowmation. When the I/O
powt addwess above is pawt of the PCI I/O wegion, the MPU401 I/O powt
might have been awweady awwocated (wesewved) by the dwivew itsewf. In
such a case, pass a bit fwag ``MPU401_INFO_INTEGWATED``, and the
mpu401-uawt wayew wiww awwocate the I/O powts by itsewf.

When the contwowwew suppowts onwy the input ow output MIDI stweam, pass
the ``MPU401_INFO_INPUT`` ow ``MPU401_INFO_OUTPUT`` bitfwag,
wespectivewy. Then the wawmidi instance is cweated as a singwe stweam.

``MPU401_INFO_MMIO`` bitfwag is used to change the access method to MMIO
(via weadb and wwiteb) instead of iob and outb. In this case, you have
to pass the iomapped addwess to :c:func:`snd_mpu401_uawt_new()`.

When ``MPU401_INFO_TX_IWQ`` is set, the output stweam isn't checked in
the defauwt intewwupt handwew. The dwivew needs to caww
:c:func:`snd_mpu401_uawt_intewwupt_tx()` by itsewf to stawt
pwocessing the output stweam in the iwq handwew.

If the MPU-401 intewface shawes its intewwupt with the othew wogicaw
devices on the cawd, set ``MPU401_INFO_IWQ_HOOK`` (see
`bewow <MIDI Intewwupt Handwew_>`__).

Usuawwy, the powt addwess cowwesponds to the command powt and powt + 1
cowwesponds to the data powt. If not, you may change the ``cpowt``
fiewd of stwuct snd_mpu401 manuawwy aftewwawd.
Howevew, stwuct snd_mpu401 pointew is
not wetuwned expwicitwy by :c:func:`snd_mpu401_uawt_new()`. You
need to cast ``wmidi->pwivate_data`` to stwuct snd_mpu401 expwicitwy::

  stwuct snd_mpu401 *mpu;
  mpu = wmidi->pwivate_data;

and weset the ``cpowt`` as you wike::

  mpu->cpowt = my_own_contwow_powt;

The 6th awgument specifies the ISA iwq numbew that wiww be awwocated. If
no intewwupt is to be awwocated (because youw code is awweady awwocating
a shawed intewwupt, ow because the device does not use intewwupts), pass
-1 instead. Fow a MPU-401 device without an intewwupt, a powwing timew
wiww be used instead.

MIDI Intewwupt Handwew
----------------------

When the intewwupt is awwocated in
:c:func:`snd_mpu401_uawt_new()`, an excwusive ISA intewwupt
handwew is automaticawwy used, hence you don't have anything ewse to do
than cweating the mpu401 stuff. Othewwise, you have to set
``MPU401_INFO_IWQ_HOOK``, and caww
:c:func:`snd_mpu401_uawt_intewwupt()` expwicitwy fwom youw own
intewwupt handwew when it has detewmined that a UAWT intewwupt has
occuwwed.

In this case, you need to pass the pwivate_data of the wetuwned wawmidi
object fwom :c:func:`snd_mpu401_uawt_new()` as the second
awgument of :c:func:`snd_mpu401_uawt_intewwupt()`::

  snd_mpu401_uawt_intewwupt(iwq, wmidi->pwivate_data, wegs);


WawMIDI Intewface
=================

Ovewview
--------

The waw MIDI intewface is used fow hawdwawe MIDI powts that can be
accessed as a byte stweam. It is not used fow synthesizew chips that do
not diwectwy undewstand MIDI.

AWSA handwes fiwe and buffew management. Aww you have to do is to wwite
some code to move data between the buffew and the hawdwawe.

The wawmidi API is defined in ``<sound/wawmidi.h>``.

WawMIDI Constwuctow
-------------------

To cweate a wawmidi device, caww the :c:func:`snd_wawmidi_new()`
function::

  stwuct snd_wawmidi *wmidi;
  eww = snd_wawmidi_new(chip->cawd, "MyMIDI", 0, outs, ins, &wmidi);
  if (eww < 0)
          wetuwn eww;
  wmidi->pwivate_data = chip;
  stwcpy(wmidi->name, "My MIDI");
  wmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
                      SNDWV_WAWMIDI_INFO_INPUT |
                      SNDWV_WAWMIDI_INFO_DUPWEX;

The fiwst awgument is the cawd pointew, the second awgument is the ID
stwing.

The thiwd awgument is the index of this component. You can cweate up to
8 wawmidi devices.

The fouwth and fifth awguments awe the numbew of output and input
substweams, wespectivewy, of this device (a substweam is the equivawent
of a MIDI powt).

Set the ``info_fwags`` fiewd to specify the capabiwities of the
device. Set ``SNDWV_WAWMIDI_INFO_OUTPUT`` if thewe is at weast one
output powt, ``SNDWV_WAWMIDI_INFO_INPUT`` if thewe is at weast one
input powt, and ``SNDWV_WAWMIDI_INFO_DUPWEX`` if the device can handwe
output and input at the same time.

Aftew the wawmidi device is cweated, you need to set the opewatows
(cawwbacks) fow each substweam. Thewe awe hewpew functions to set the
opewatows fow aww the substweams of a device::

  snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_mymidi_output_ops);
  snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_mymidi_input_ops);

The opewatows awe usuawwy defined wike this::

  static stwuct snd_wawmidi_ops snd_mymidi_output_ops = {
          .open =    snd_mymidi_output_open,
          .cwose =   snd_mymidi_output_cwose,
          .twiggew = snd_mymidi_output_twiggew,
  };

These cawwbacks awe expwained in the `WawMIDI Cawwbacks`_ section.

If thewe awe mowe than one substweam, you shouwd give a unique name to
each of them::

  stwuct snd_wawmidi_substweam *substweam;
  wist_fow_each_entwy(substweam,
                      &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT].substweams,
                      wist {
          spwintf(substweam->name, "My MIDI Powt %d", substweam->numbew + 1);
  }
  /* same fow SNDWV_WAWMIDI_STWEAM_INPUT */

WawMIDI Cawwbacks
-----------------

In aww the cawwbacks, the pwivate data that you've set fow the wawmidi
device can be accessed as ``substweam->wmidi->pwivate_data``.

If thewe is mowe than one powt, youw cawwbacks can detewmine the powt
index fwom the stwuct snd_wawmidi_substweam data passed to each
cawwback::

  stwuct snd_wawmidi_substweam *substweam;
  int index = substweam->numbew;

WawMIDI open cawwback
~~~~~~~~~~~~~~~~~~~~~

::

      static int snd_xxx_open(stwuct snd_wawmidi_substweam *substweam);


This is cawwed when a substweam is opened. You can initiawize the
hawdwawe hewe, but you shouwdn't stawt twansmitting/weceiving data yet.

WawMIDI cwose cawwback
~~~~~~~~~~~~~~~~~~~~~~

::

      static int snd_xxx_cwose(stwuct snd_wawmidi_substweam *substweam);

Guess what.

The ``open`` and ``cwose`` cawwbacks of a wawmidi device awe
sewiawized with a mutex, and can sweep.

Wawmidi twiggew cawwback fow output substweams
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

      static void snd_xxx_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up);


This is cawwed with a nonzewo ``up`` pawametew when thewe is some data
in the substweam buffew that must be twansmitted.

To wead data fwom the buffew, caww
:c:func:`snd_wawmidi_twansmit_peek()`. It wiww wetuwn the numbew
of bytes that have been wead; this wiww be wess than the numbew of bytes
wequested when thewe awe no mowe data in the buffew. Aftew the data have
been twansmitted successfuwwy, caww
:c:func:`snd_wawmidi_twansmit_ack()` to wemove the data fwom the
substweam buffew::

  unsigned chaw data;
  whiwe (snd_wawmidi_twansmit_peek(substweam, &data, 1) == 1) {
          if (snd_mychip_twy_to_twansmit(data))
                  snd_wawmidi_twansmit_ack(substweam, 1);
          ewse
                  bweak; /* hawdwawe FIFO fuww */
  }

If you know befowehand that the hawdwawe wiww accept data, you can use
the :c:func:`snd_wawmidi_twansmit()` function which weads some
data and wemoves them fwom the buffew at once::

  whiwe (snd_mychip_twansmit_possibwe()) {
          unsigned chaw data;
          if (snd_wawmidi_twansmit(substweam, &data, 1) != 1)
                  bweak; /* no mowe data */
          snd_mychip_twansmit(data);
  }

If you know befowehand how many bytes you can accept, you can use a
buffew size gweatew than one with the ``snd_wawmidi_twansmit*()`` functions.

The ``twiggew`` cawwback must not sweep. If the hawdwawe FIFO is fuww
befowe the substweam buffew has been emptied, you have to continue
twansmitting data watew, eithew in an intewwupt handwew, ow with a
timew if the hawdwawe doesn't have a MIDI twansmit intewwupt.

The ``twiggew`` cawwback is cawwed with a zewo ``up`` pawametew when
the twansmission of data shouwd be abowted.

WawMIDI twiggew cawwback fow input substweams
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

      static void snd_xxx_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up);


This is cawwed with a nonzewo ``up`` pawametew to enabwe weceiving data,
ow with a zewo ``up`` pawametew do disabwe weceiving data.

The ``twiggew`` cawwback must not sweep; the actuaw weading of data
fwom the device is usuawwy done in an intewwupt handwew.

When data weception is enabwed, youw intewwupt handwew shouwd caww
:c:func:`snd_wawmidi_weceive()` fow aww weceived data::

  void snd_mychip_midi_intewwupt(...)
  {
          whiwe (mychip_midi_avaiwabwe()) {
                  unsigned chaw data;
                  data = mychip_midi_wead();
                  snd_wawmidi_weceive(substweam, &data, 1);
          }
  }


dwain cawwback
~~~~~~~~~~~~~~

::

      static void snd_xxx_dwain(stwuct snd_wawmidi_substweam *substweam);


This is onwy used with output substweams. This function shouwd wait
untiw aww data wead fwom the substweam buffew have been twansmitted.
This ensuwes that the device can be cwosed and the dwivew unwoaded
without wosing data.

This cawwback is optionaw. If you do not set ``dwain`` in the stwuct
snd_wawmidi_ops stwuctuwe, AWSA wiww simpwy wait fow 50 miwwiseconds
instead.

Miscewwaneous Devices
=====================

FM OPW3
-------

The FM OPW3 is stiww used in many chips (mainwy fow backwawd
compatibiwity). AWSA has a nice OPW3 FM contwow wayew, too. The OPW3 API
is defined in ``<sound/opw3.h>``.

FM wegistews can be diwectwy accessed thwough the diwect-FM API, defined
in ``<sound/asound_fm.h>``. In AWSA native mode, FM wegistews awe
accessed thwough the Hawdwawe-Dependent Device diwect-FM extension API,
wheweas in OSS compatibwe mode, FM wegistews can be accessed with the
OSS diwect-FM compatibwe API in ``/dev/dmfmX`` device.

To cweate the OPW3 component, you have two functions to caww. The fiwst
one is a constwuctow fow the ``opw3_t`` instance::

  stwuct snd_opw3 *opw3;
  snd_opw3_cweate(cawd, wpowt, wpowt, OPW3_HW_OPW3_XXX,
                  integwated, &opw3);

The fiwst awgument is the cawd pointew, the second one is the weft powt
addwess, and the thiwd is the wight powt addwess. In most cases, the
wight powt is pwaced at the weft powt + 2.

The fouwth awgument is the hawdwawe type.

When the weft and wight powts have been awweady awwocated by the cawd
dwivew, pass non-zewo to the fifth awgument (``integwated``). Othewwise,
the opw3 moduwe wiww awwocate the specified powts by itsewf.

When the accessing the hawdwawe wequiwes speciaw method instead of the
standawd I/O access, you can cweate opw3 instance sepawatewy with
:c:func:`snd_opw3_new()`::

  stwuct snd_opw3 *opw3;
  snd_opw3_new(cawd, OPW3_HW_OPW3_XXX, &opw3);

Then set ``command``, ``pwivate_data`` and ``pwivate_fwee`` fow the
pwivate access function, the pwivate data and the destwuctow. The
``w_powt`` and ``w_powt`` awe not necessawiwy set. Onwy the command
must be set pwopewwy. You can wetwieve the data fwom the
``opw3->pwivate_data`` fiewd. 

Aftew cweating the opw3 instance via :c:func:`snd_opw3_new()`,
caww :c:func:`snd_opw3_init()` to initiawize the chip to the
pwopew state. Note that :c:func:`snd_opw3_cweate()` awways cawws
it intewnawwy.

If the opw3 instance is cweated successfuwwy, then cweate a hwdep device
fow this opw3::

  stwuct snd_hwdep *opw3hwdep;
  snd_opw3_hwdep_new(opw3, 0, 1, &opw3hwdep);

The fiwst awgument is the ``opw3_t`` instance you cweated, and the
second is the index numbew, usuawwy 0.

The thiwd awgument is the index-offset fow the sequencew cwient assigned
to the OPW3 powt. When thewe is an MPU401-UAWT, give 1 fow hewe (UAWT
awways takes 0).

Hawdwawe-Dependent Devices
--------------------------

Some chips need usew-space access fow speciaw contwows ow fow woading
the micwo code. In such a case, you can cweate a hwdep
(hawdwawe-dependent) device. The hwdep API is defined in
``<sound/hwdep.h>``. You can find exampwes in opw3 dwivew ow
``isa/sb/sb16_csp.c``.

The cweation of the ``hwdep`` instance is done via
:c:func:`snd_hwdep_new()`::

  stwuct snd_hwdep *hw;
  snd_hwdep_new(cawd, "My HWDEP", 0, &hw);

whewe the thiwd awgument is the index numbew.

You can then pass any pointew vawue to the ``pwivate_data``. If you
assign pwivate data, you shouwd define a destwuctow, too. The
destwuctow function is set in the ``pwivate_fwee`` fiewd::

  stwuct mydata *p = kmawwoc(sizeof(*p), GFP_KEWNEW);
  hw->pwivate_data = p;
  hw->pwivate_fwee = mydata_fwee;

and the impwementation of the destwuctow wouwd be::

  static void mydata_fwee(stwuct snd_hwdep *hw)
  {
          stwuct mydata *p = hw->pwivate_data;
          kfwee(p);
  }

The awbitwawy fiwe opewations can be defined fow this instance. The fiwe
opewatows awe defined in the ``ops`` tabwe. Fow exampwe, assume that
this chip needs an ioctw::

  hw->ops.open = mydata_open;
  hw->ops.ioctw = mydata_ioctw;
  hw->ops.wewease = mydata_wewease;

And impwement the cawwback functions as you wike.

IEC958 (S/PDIF)
---------------

Usuawwy the contwows fow IEC958 devices awe impwemented via the contwow
intewface. Thewe is a macwo to compose a name stwing fow IEC958
contwows, :c:func:`SNDWV_CTW_NAME_IEC958()` defined in
``<incwude/asound.h>``.

Thewe awe some standawd contwows fow IEC958 status bits. These contwows
use the type ``SNDWV_CTW_EWEM_TYPE_IEC958``, and the size of ewement is
fixed as 4 bytes awway (vawue.iec958.status[x]). Fow the ``info``
cawwback, you don't specify the vawue fiewd fow this type (the count
fiewd must be set, though).

“IEC958 Pwayback Con Mask” is used to wetuwn the bit-mask fow the IEC958
status bits of consumew mode. Simiwawwy, “IEC958 Pwayback Pwo Mask”
wetuwns the bitmask fow pwofessionaw mode. They awe wead-onwy contwows.

Meanwhiwe, “IEC958 Pwayback Defauwt” contwow is defined fow getting and
setting the cuwwent defauwt IEC958 bits.

Due to histowicaw weasons, both vawiants of the Pwayback Mask and the
Pwayback Defauwt contwows can be impwemented on eithew a
``SNDWV_CTW_EWEM_IFACE_PCM`` ow a ``SNDWV_CTW_EWEM_IFACE_MIXEW`` iface.
Dwivews shouwd expose the mask and defauwt on the same iface though.

In addition, you can define the contwow switches to enabwe/disabwe ow to
set the waw bit mode. The impwementation wiww depend on the chip, but
the contwow shouwd be named as “IEC958 xxx”, pwefewabwy using the
:c:func:`SNDWV_CTW_NAME_IEC958()` macwo.

You can find sevewaw cases, fow exampwe, ``pci/emu10k1``,
``pci/ice1712``, ow ``pci/cmipci.c``.

Buffew and Memowy Management
============================

Buffew Types
------------

AWSA pwovides sevewaw diffewent buffew awwocation functions depending on
the bus and the awchitectuwe. Aww these have a consistent API. The
awwocation of physicawwy-contiguous pages is done via the
:c:func:`snd_mawwoc_xxx_pages()` function, whewe xxx is the bus
type.

The awwocation of pages with fawwback is done via
:c:func:`snd_dma_awwoc_pages_fawwback()`. This function twies
to awwocate the specified numbew of pages, but if not enough pages awe
avaiwabwe, it twies to weduce the wequest size untiw enough space
is found, down to one page.

To wewease the pages, caww the :c:func:`snd_dma_fwee_pages()`
function.

Usuawwy, AWSA dwivews twy to awwocate and wesewve a wawge contiguous
physicaw space at the time the moduwe is woaded fow watew use. This
is cawwed “pwe-awwocation”. As awweady wwitten, you can caww the
fowwowing function at PCM instance constwuction time (in the case of PCI
bus)::

  snd_pcm_wib_pweawwocate_pages_fow_aww(pcm, SNDWV_DMA_TYPE_DEV,
                                        &pci->dev, size, max);

whewe ``size`` is the byte size to be pwe-awwocated and ``max`` is
the maximum size settabwe via the ``pweawwoc`` pwoc fiwe. The
awwocatow wiww twy to get an awea as wawge as possibwe within the
given size.

The second awgument (type) and the thiwd awgument (device pointew) awe
dependent on the bus. Fow nowmaw devices, pass the device pointew
(typicawwy identicaw as ``cawd->dev``) to the thiwd awgument with
``SNDWV_DMA_TYPE_DEV`` type.

A continuous buffew unwewated to the
bus can be pwe-awwocated with ``SNDWV_DMA_TYPE_CONTINUOUS`` type.
You can pass NUWW to the device pointew in that case, which is the
defauwt mode impwying to awwocate with the ``GFP_KEWNEW`` fwag.
If you need a westwicted (wowew) addwess, set up the cohewent DMA mask
bits fow the device, and pass the device pointew, wike the nowmaw
device memowy awwocations.  Fow this type, it's stiww awwowed to pass
NUWW to the device pointew, too, if no addwess westwiction is needed.

Fow the scattew-gathew buffews, use ``SNDWV_DMA_TYPE_DEV_SG`` with the
device pointew (see the `Non-Contiguous Buffews`_ section).

Once the buffew is pwe-awwocated, you can use the awwocatow in the
``hw_pawams`` cawwback::

  snd_pcm_wib_mawwoc_pages(substweam, size);

Note that you have to pwe-awwocate to use this function.

But most dwivews use the "managed buffew awwocation mode" instead
of manuaw awwocation and wewease.
This is done by cawwing :c:func:`snd_pcm_set_managed_buffew_aww()`
instead of :c:func:`snd_pcm_wib_pweawwocate_pages_fow_aww()`::

  snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
                                 &pci->dev, size, max);

whewe the passed awguments awe identicaw fow both functions.
The diffewence in the managed mode is that PCM cowe wiww caww
:c:func:`snd_pcm_wib_mawwoc_pages()` intewnawwy awweady befowe cawwing
the PCM ``hw_pawams`` cawwback, and caww :c:func:`snd_pcm_wib_fwee_pages()`
aftew the PCM ``hw_fwee`` cawwback automaticawwy.  So the dwivew
doesn't have to caww these functions expwicitwy in its cawwback any
wongew.  This awwows many dwivews to have NUWW ``hw_pawams`` and
``hw_fwee`` entwies.

Extewnaw Hawdwawe Buffews
-------------------------

Some chips have theiw own hawdwawe buffews and DMA twansfew fwom the
host memowy is not avaiwabwe. In such a case, you need to eithew 1)
copy/set the audio data diwectwy to the extewnaw hawdwawe buffew, ow 2)
make an intewmediate buffew and copy/set the data fwom it to the
extewnaw hawdwawe buffew in intewwupts (ow in taskwets, pwefewabwy).

The fiwst case wowks fine if the extewnaw hawdwawe buffew is wawge
enough. This method doesn't need any extwa buffews and thus is mowe
efficient. You need to define the ``copy`` cawwback
fow the data twansfew, in addition to the ``fiww_siwence``
cawwback fow pwayback. Howevew, thewe is a dwawback: it cannot be
mmapped. The exampwes awe GUS's GF1 PCM ow emu8000's wavetabwe PCM.

The second case awwows fow mmap on the buffew, awthough you have to
handwe an intewwupt ow a taskwet to twansfew the data fwom the
intewmediate buffew to the hawdwawe buffew. You can find an exampwe in
the vxpocket dwivew.

Anothew case is when the chip uses a PCI memowy-map wegion fow the
buffew instead of the host memowy. In this case, mmap is avaiwabwe onwy
on cewtain awchitectuwes wike the Intew one. In non-mmap mode, the data
cannot be twansfewwed as in the nowmaw way. Thus you need to define the
``copy`` and ``fiww_siwence`` cawwbacks as weww,
as in the cases above. Exampwes awe found in ``wme32.c`` and
``wme96.c``.

The impwementation of the ``copy`` and
``siwence`` cawwbacks depends upon whethew the hawdwawe suppowts
intewweaved ow non-intewweaved sampwes. The ``copy`` cawwback is
defined wike bewow, a bit diffewentwy depending on whethew the diwection
is pwayback ow captuwe::

  static int pwayback_copy(stwuct snd_pcm_substweam *substweam,
               int channew, unsigned wong pos,
               stwuct iov_itew *swc, unsigned wong count);
  static int captuwe_copy(stwuct snd_pcm_substweam *substweam,
               int channew, unsigned wong pos,
               stwuct iov_itew *dst, unsigned wong count);

In the case of intewweaved sampwes, the second awgument (``channew``) is
not used. The thiwd awgument (``pos``) specifies the position in bytes.

The meaning of the fouwth awgument is diffewent between pwayback and
captuwe. Fow pwayback, it howds the souwce data pointew, and fow
captuwe, it's the destination data pointew.

The wast awgument is the numbew of bytes to be copied.

What you have to do in this cawwback is again diffewent between pwayback
and captuwe diwections. In the pwayback case, you copy the given amount
of data (``count``) at the specified pointew (``swc``) to the specified
offset (``pos``) in the hawdwawe buffew. When coded wike memcpy-wike
way, the copy wouwd wook wike::

  my_memcpy_fwom_itew(my_buffew + pos, swc, count);

Fow the captuwe diwection, you copy the given amount of data (``count``)
at the specified offset (``pos``) in the hawdwawe buffew to the
specified pointew (``dst``)::

  my_memcpy_to_itew(dst, my_buffew + pos, count);

The given ``swc`` ow ``dst`` a stwuct iov_itew pointew containing the
pointew and the size.  Use the existing hewpews to copy ow access the
data as defined in ``winux/uio.h``.

Cawefuw weadews might notice that these cawwbacks weceive the
awguments in bytes, not in fwames wike othew cawwbacks.  It's because
this makes coding easiew wike in the exampwes above, and awso it makes
it easiew to unify both the intewweaved and non-intewweaved cases, as
expwained bewow.

In the case of non-intewweaved sampwes, the impwementation wiww be a bit
mowe compwicated.  The cawwback is cawwed fow each channew, passed in
the second awgument, so in totaw it's cawwed N times pew twansfew.

The meaning of the othew awguments awe awmost the same as in the
intewweaved case.  The cawwback is supposed to copy the data fwom/to
the given usew-space buffew, but onwy fow the given channew. Fow
detaiws, pwease check ``isa/gus/gus_pcm.c`` ow ``pci/wme9652/wme9652.c``
as exampwes.

Usuawwy fow the pwayback, anothew cawwback ``fiww_siwence`` is
defined.  It's impwemented in a simiwaw way as the copy cawwbacks
above::

  static int siwence(stwuct snd_pcm_substweam *substweam, int channew,
                     unsigned wong pos, unsigned wong count);

The meanings of awguments awe the same as in the ``copy`` cawwback,
awthough thewe is no buffew pointew
awgument. In the case of intewweaved sampwes, the channew awgument has
no meaning, as fow the ``copy`` cawwback.

The wowe of the ``fiww_siwence`` cawwback is to set the given amount
(``count``) of siwence data at the specified offset (``pos``) in the
hawdwawe buffew. Suppose that the data fowmat is signed (that is, the
siwent-data is 0), and the impwementation using a memset-wike function
wouwd wook wike::

  my_memset(my_buffew + pos, 0, count);

In the case of non-intewweaved sampwes, again, the impwementation
becomes a bit mowe compwicated, as it's cawwed N times pew twansfew
fow each channew. See, fow exampwe, ``isa/gus/gus_pcm.c``.

Non-Contiguous Buffews
----------------------

If youw hawdwawe suppowts a page tabwe as in emu10k1 ow buffew
descwiptows as in via82xx, you can use scattew-gathew (SG) DMA. AWSA
pwovides an intewface fow handwing SG-buffews. The API is pwovided in
``<sound/pcm.h>``.

Fow cweating the SG-buffew handwew, caww
:c:func:`snd_pcm_set_managed_buffew()` ow
:c:func:`snd_pcm_set_managed_buffew_aww()` with
``SNDWV_DMA_TYPE_DEV_SG`` in the PCM constwuctow wike fow othew PCI
pwe-awwocations. You need to pass ``&pci->dev``, whewe pci is
the stwuct pci_dev pointew of the chip as weww::

  snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
                                 &pci->dev, size, max);

The ``stwuct snd_sg_buf`` instance is cweated as
``substweam->dma_pwivate`` in tuwn. You can cast the pointew wike::

  stwuct snd_sg_buf *sgbuf = (stwuct snd_sg_buf *)substweam->dma_pwivate;

Then in the :c:func:`snd_pcm_wib_mawwoc_pages()` caww, the common SG-buffew
handwew wiww awwocate the non-contiguous kewnew pages of the given size
and map them as viwtuawwy contiguous memowy. The viwtuaw pointew
is addwessed via wuntime->dma_awea. The physicaw addwess
(``wuntime->dma_addw``) is set to zewo, because the buffew is
physicawwy non-contiguous. The physicaw addwess tabwe is set up in
``sgbuf->tabwe``. You can get the physicaw addwess at a cewtain offset
via :c:func:`snd_pcm_sgbuf_get_addw()`.

If you need to wewease the SG-buffew data expwicitwy, caww the
standawd API function :c:func:`snd_pcm_wib_fwee_pages()` as usuaw.

Vmawwoc'ed Buffews
------------------

It's possibwe to use a buffew awwocated via :c:func:`vmawwoc()`, fow
exampwe, fow an intewmediate buffew.
You can simpwy awwocate it via the standawd
:c:func:`snd_pcm_wib_mawwoc_pages()` and co. aftew setting up the
buffew pweawwocation with ``SNDWV_DMA_TYPE_VMAWWOC`` type::

  snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC,
                                 NUWW, 0, 0);

NUWW is passed as the device pointew awgument, which indicates
that defauwt pages (GFP_KEWNEW and GFP_HIGHMEM) wiww be
awwocated.

Awso, note that zewo is passed as both the size and the max size
awgument hewe.  Since each vmawwoc caww shouwd succeed at any time,
we don't need to pwe-awwocate the buffews wike othew continuous
pages.

Pwoc Intewface
==============

AWSA pwovides an easy intewface fow pwocfs. The pwoc fiwes awe vewy
usefuw fow debugging. I wecommend you set up pwoc fiwes if you wwite a
dwivew and want to get a wunning status ow wegistew dumps. The API is
found in ``<sound/info.h>``.

To cweate a pwoc fiwe, caww :c:func:`snd_cawd_pwoc_new()`::

  stwuct snd_info_entwy *entwy;
  int eww = snd_cawd_pwoc_new(cawd, "my-fiwe", &entwy);

whewe the second awgument specifies the name of the pwoc fiwe to be
cweated. The above exampwe wiww cweate a fiwe ``my-fiwe`` undew the
cawd diwectowy, e.g. ``/pwoc/asound/cawd0/my-fiwe``.

Wike othew components, the pwoc entwy cweated via
:c:func:`snd_cawd_pwoc_new()` wiww be wegistewed and weweased
automaticawwy in the cawd wegistwation and wewease functions.

When the cweation is successfuw, the function stowes a new instance in
the pointew given in the thiwd awgument. It is initiawized as a text
pwoc fiwe fow wead onwy. To use this pwoc fiwe as a wead-onwy text fiwe
as-is, set the wead cawwback with pwivate data via
:c:func:`snd_info_set_text_ops()`::

  snd_info_set_text_ops(entwy, chip, my_pwoc_wead);

whewe the second awgument (``chip``) is the pwivate data to be used in
the cawwback. The thiwd pawametew specifies the wead buffew size and
the fouwth (``my_pwoc_wead``) is the cawwback function, which is
defined wike::

  static void my_pwoc_wead(stwuct snd_info_entwy *entwy,
                           stwuct snd_info_buffew *buffew);

In the wead cawwback, use :c:func:`snd_ipwintf()` fow output
stwings, which wowks just wike nowmaw :c:func:`pwintf()`. Fow
exampwe::

  static void my_pwoc_wead(stwuct snd_info_entwy *entwy,
                           stwuct snd_info_buffew *buffew)
  {
          stwuct my_chip *chip = entwy->pwivate_data;

          snd_ipwintf(buffew, "This is my chip!\n");
          snd_ipwintf(buffew, "Powt = %wd\n", chip->powt);
  }

The fiwe pewmissions can be changed aftewwawds. By defauwt, they awe
wead onwy fow aww usews. If you want to add wwite pewmission fow the
usew (woot by defauwt), do as fowwows::

 entwy->mode = S_IFWEG | S_IWUGO | S_IWUSW;

and set the wwite buffew size and the cawwback::

  entwy->c.text.wwite = my_pwoc_wwite;

In the wwite cawwback, you can use :c:func:`snd_info_get_wine()`
to get a text wine, and :c:func:`snd_info_get_stw()` to wetwieve
a stwing fwom the wine. Some exampwes awe found in
``cowe/oss/mixew_oss.c``, cowe/oss/and ``pcm_oss.c``.

Fow a waw-data pwoc-fiwe, set the attwibutes as fowwows::

  static const stwuct snd_info_entwy_ops my_fiwe_io_ops = {
          .wead = my_fiwe_io_wead,
  };

  entwy->content = SNDWV_INFO_CONTENT_DATA;
  entwy->pwivate_data = chip;
  entwy->c.ops = &my_fiwe_io_ops;
  entwy->size = 4096;
  entwy->mode = S_IFWEG | S_IWUGO;

Fow waw data, ``size`` fiewd must be set pwopewwy. This specifies
the maximum size of the pwoc fiwe access.

The wead/wwite cawwbacks of waw mode awe mowe diwect than the text mode.
You need to use a wow-wevew I/O functions such as
:c:func:`copy_fwom_usew()` and :c:func:`copy_to_usew()` to twansfew the
data::

  static ssize_t my_fiwe_io_wead(stwuct snd_info_entwy *entwy,
                              void *fiwe_pwivate_data,
                              stwuct fiwe *fiwe,
                              chaw *buf,
                              size_t count,
                              woff_t pos)
  {
          if (copy_to_usew(buf, wocaw_data + pos, count))
                  wetuwn -EFAUWT;
          wetuwn count;
  }

If the size of the info entwy has been set up pwopewwy, ``count`` and
``pos`` awe guawanteed to fit within 0 and the given size. You don't
have to check the wange in the cawwbacks unwess any othew condition is
wequiwed.

Powew Management
================

If the chip is supposed to wowk with suspend/wesume functions, you need
to add powew-management code to the dwivew. The additionaw code fow
powew-management shouwd be ifdef-ed with ``CONFIG_PM``, ow annotated
with __maybe_unused attwibute; othewwise the compiwew wiww compwain.

If the dwivew *fuwwy* suppowts suspend/wesume that is, the device can be
pwopewwy wesumed to its state when suspend was cawwed, you can set the
``SNDWV_PCM_INFO_WESUME`` fwag in the PCM info fiewd. Usuawwy, this is
possibwe when the wegistews of the chip can be safewy saved and westowed
to WAM. If this is set, the twiggew cawwback is cawwed with
``SNDWV_PCM_TWIGGEW_WESUME`` aftew the wesume cawwback compwetes.

Even if the dwivew doesn't suppowt PM fuwwy but pawtiaw suspend/wesume
is stiww possibwe, it's stiww wowthy to impwement suspend/wesume
cawwbacks. In such a case, appwications wouwd weset the status by
cawwing :c:func:`snd_pcm_pwepawe()` and westawt the stweam
appwopwiatewy. Hence, you can define suspend/wesume cawwbacks bewow but
don't set the ``SNDWV_PCM_INFO_WESUME`` info fwag to the PCM.

Note that the twiggew with SUSPEND can awways be cawwed when
:c:func:`snd_pcm_suspend_aww()` is cawwed, wegawdwess of the
``SNDWV_PCM_INFO_WESUME`` fwag. The ``WESUME`` fwag affects onwy the
behaviow of :c:func:`snd_pcm_wesume()`. (Thus, in theowy,
``SNDWV_PCM_TWIGGEW_WESUME`` isn't needed to be handwed in the twiggew
cawwback when no ``SNDWV_PCM_INFO_WESUME`` fwag is set. But, it's bettew
to keep it fow compatibiwity weasons.)

The dwivew needs to define the
suspend/wesume hooks accowding to the bus the device is connected to. In
the case of PCI dwivews, the cawwbacks wook wike bewow::

  static int __maybe_unused snd_my_suspend(stwuct device *dev)
  {
          .... /* do things fow suspend */
          wetuwn 0;
  }
  static int __maybe_unused snd_my_wesume(stwuct device *dev)
  {
          .... /* do things fow suspend */
          wetuwn 0;
  }

The scheme of the weaw suspend job is as fowwows:

1. Wetwieve the cawd and the chip data.

2. Caww :c:func:`snd_powew_change_state()` with
   ``SNDWV_CTW_POWEW_D3hot`` to change the powew status.

3. If AC97 codecs awe used, caww :c:func:`snd_ac97_suspend()` fow
   each codec.

4. Save the wegistew vawues if necessawy.

5. Stop the hawdwawe if necessawy.

Typicaw code wouwd wook wike::

  static int __maybe_unused mychip_suspend(stwuct device *dev)
  {
          /* (1) */
          stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
          stwuct mychip *chip = cawd->pwivate_data;
          /* (2) */
          snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
          /* (3) */
          snd_ac97_suspend(chip->ac97);
          /* (4) */
          snd_mychip_save_wegistews(chip);
          /* (5) */
          snd_mychip_stop_hawdwawe(chip);
          wetuwn 0;
  }


The scheme of the weaw wesume job is as fowwows:

1. Wetwieve the cawd and the chip data.

2. We-initiawize the chip.

3. Westowe the saved wegistews if necessawy.

4. Wesume the mixew, e.g. by cawwing :c:func:`snd_ac97_wesume()`.

5. Westawt the hawdwawe (if any).

6. Caww :c:func:`snd_powew_change_state()` with
   ``SNDWV_CTW_POWEW_D0`` to notify the pwocesses.

Typicaw code wouwd wook wike::

  static int __maybe_unused mychip_wesume(stwuct pci_dev *pci)
  {
          /* (1) */
          stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
          stwuct mychip *chip = cawd->pwivate_data;
          /* (2) */
          snd_mychip_weinit_chip(chip);
          /* (3) */
          snd_mychip_westowe_wegistews(chip);
          /* (4) */
          snd_ac97_wesume(chip->ac97);
          /* (5) */
          snd_mychip_westawt_chip(chip);
          /* (6) */
          snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
          wetuwn 0;
  }

Note that, at the time this cawwback gets cawwed, the PCM stweam has
been awweady suspended via its own PM ops cawwing
:c:func:`snd_pcm_suspend_aww()` intewnawwy.

OK, we have aww cawwbacks now. Wet's set them up. In the initiawization
of the cawd, make suwe that you can get the chip data fwom the cawd
instance, typicawwy via ``pwivate_data`` fiewd, in case you cweated the
chip data individuawwy::

  static int snd_mychip_pwobe(stwuct pci_dev *pci,
                              const stwuct pci_device_id *pci_id)
  {
          ....
          stwuct snd_cawd *cawd;
          stwuct mychip *chip;
          int eww;
          ....
          eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                             0, &cawd);
          ....
          chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
          ....
          cawd->pwivate_data = chip;
          ....
  }

When you cweated the chip data with :c:func:`snd_cawd_new()`, it's
anyway accessibwe via ``pwivate_data`` fiewd::

  static int snd_mychip_pwobe(stwuct pci_dev *pci,
                              const stwuct pci_device_id *pci_id)
  {
          ....
          stwuct snd_cawd *cawd;
          stwuct mychip *chip;
          int eww;
          ....
          eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
                             sizeof(stwuct mychip), &cawd);
          ....
          chip = cawd->pwivate_data;
          ....
  }

If you need space to save the wegistews, awwocate the buffew fow it
hewe, too, since it wouwd be fataw if you cannot awwocate a memowy in
the suspend phase. The awwocated buffew shouwd be weweased in the
cowwesponding destwuctow.

And next, set suspend/wesume cawwbacks to the pci_dwivew::

  static SIMPWE_DEV_PM_OPS(snd_my_pm_ops, mychip_suspend, mychip_wesume);

  static stwuct pci_dwivew dwivew = {
          .name = KBUIWD_MODNAME,
          .id_tabwe = snd_my_ids,
          .pwobe = snd_my_pwobe,
          .wemove = snd_my_wemove,
          .dwivew.pm = &snd_my_pm_ops,
  };

Moduwe Pawametews
=================

Thewe awe standawd moduwe options fow AWSA. At weast, each moduwe shouwd
have the ``index``, ``id`` and ``enabwe`` options.

If the moduwe suppowts muwtipwe cawds (usuawwy up to 8 = ``SNDWV_CAWDS``
cawds), they shouwd be awways. The defauwt initiaw vawues awe defined
awweady as constants fow easiew pwogwamming::

  static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
  static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
  static int enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

If the moduwe suppowts onwy a singwe cawd, they couwd be singwe
vawiabwes, instead. ``enabwe`` option is not awways necessawy in this
case, but it wouwd be bettew to have a dummy option fow compatibiwity.

The moduwe pawametews must be decwawed with the standawd
``moduwe_pawam()``, ``moduwe_pawam_awway()`` and
:c:func:`MODUWE_PAWM_DESC()` macwos.

Typicaw code wouwd wook as bewow::

  #define CAWD_NAME "My Chip"

  moduwe_pawam_awway(index, int, NUWW, 0444);
  MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
  moduwe_pawam_awway(id, chawp, NUWW, 0444);
  MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
  moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
  MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");

Awso, don't fowget to define the moduwe descwiption and the wicense.
Especiawwy, the wecent modpwobe wequiwes to define the
moduwe wicense as GPW, etc., othewwise the system is shown as “tainted”::

  MODUWE_DESCWIPTION("Sound dwivew fow My Chip");
  MODUWE_WICENSE("GPW");


Device-Managed Wesouwces
========================

In the exampwes above, aww wesouwces awe awwocated and weweased
manuawwy.  But human beings awe wazy in natuwe, especiawwy devewopews
awe waziew.  So thewe awe some ways to automate the wewease pawt; it's
the (device-)managed wesouwces aka devwes ow devm famiwy.  Fow
exampwe, an object awwocated via :c:func:`devm_kmawwoc()` wiww be
fweed automaticawwy at unbinding the device.

AWSA cowe pwovides awso the device-managed hewpew, namewy,
:c:func:`snd_devm_cawd_new()` fow cweating a cawd object.
Caww this functions instead of the nowmaw :c:func:`snd_cawd_new()`,
and you can fowget the expwicit :c:func:`snd_cawd_fwee()` caww, as
it's cawwed automagicawwy at ewwow and wemovaw paths.

One caveat is that the caww of :c:func:`snd_cawd_fwee()` wouwd be put
at the beginning of the caww chain onwy aftew you caww
:c:func:`snd_cawd_wegistew()`.

Awso, the ``pwivate_fwee`` cawwback is awways cawwed at the cawd fwee,
so be cawefuw to put the hawdwawe cwean-up pwoceduwe in
``pwivate_fwee`` cawwback.  It might be cawwed even befowe you
actuawwy set up at an eawwiew ewwow path.  Fow avoiding such an
invawid initiawization, you can set ``pwivate_fwee`` cawwback aftew
:c:func:`snd_cawd_wegistew()` caww succeeds.

Anothew thing to be wemawked is that you shouwd use device-managed
hewpews fow each component as much as possibwe once when you manage
the cawd in that way.  Mixing up with the nowmaw and the managed
wesouwces may scwew up the wewease owdew.


How To Put Youw Dwivew Into AWSA Twee
=====================================

Genewaw
-------

So faw, you've weawned how to wwite the dwivew codes. And you might have
a question now: how to put my own dwivew into the AWSA dwivew twee? Hewe
(finawwy :) the standawd pwoceduwe is descwibed bwiefwy.

Suppose that you cweate a new PCI dwivew fow the cawd “xyz”. The cawd
moduwe name wouwd be snd-xyz. The new dwivew is usuawwy put into the
awsa-dwivew twee, ``sound/pci`` diwectowy in the case of PCI
cawds.

In the fowwowing sections, the dwivew code is supposed to be put into
Winux kewnew twee. The two cases awe covewed: a dwivew consisting of a
singwe souwce fiwe and one consisting of sevewaw souwce fiwes.

Dwivew with A Singwe Souwce Fiwe
--------------------------------

1. Modify sound/pci/Makefiwe

   Suppose you have a fiwe xyz.c. Add the fowwowing two wines::

     snd-xyz-objs := xyz.o
     obj-$(CONFIG_SND_XYZ) += snd-xyz.o

2. Cweate the Kconfig entwy

   Add the new entwy of Kconfig fow youw xyz dwivew::

     config SND_XYZ
       twistate "Foobaw XYZ"
       depends on SND
       sewect SND_PCM
       hewp
         Say Y hewe to incwude suppowt fow Foobaw XYZ soundcawd.
         To compiwe this dwivew as a moduwe, choose M hewe:
         the moduwe wiww be cawwed snd-xyz.

The wine ``sewect SND_PCM`` specifies that the dwivew xyz suppowts PCM.
In addition to SND_PCM, the fowwowing components awe suppowted fow
sewect command: SND_WAWMIDI, SND_TIMEW, SND_HWDEP, SND_MPU401_UAWT,
SND_OPW3_WIB, SND_OPW4_WIB, SND_VX_WIB, SND_AC97_CODEC.
Add the sewect command fow each suppowted component.

Note that some sewections impwy the wowwevew sewections. Fow exampwe,
PCM incwudes TIMEW, MPU401_UAWT incwudes WAWMIDI, AC97_CODEC
incwudes PCM, and OPW3_WIB incwudes HWDEP. You don't need to give
the wowwevew sewections again.

Fow the detaiws of Kconfig scwipt, wefew to the kbuiwd documentation.

Dwivews with Sevewaw Souwce Fiwes
---------------------------------

Suppose that the dwivew snd-xyz have sevewaw souwce fiwes. They awe
wocated in the new subdiwectowy, sound/pci/xyz.

1. Add a new diwectowy (``sound/pci/xyz``) in ``sound/pci/Makefiwe``
   as bewow::

     obj-$(CONFIG_SND) += sound/pci/xyz/


2. Undew the diwectowy ``sound/pci/xyz``, cweate a Makefiwe::

         snd-xyz-objs := xyz.o abc.o def.o
         obj-$(CONFIG_SND_XYZ) += snd-xyz.o

3. Cweate the Kconfig entwy

   This pwoceduwe is as same as in the wast section.


Usefuw Functions
================

:c:func:`snd_pwintk()` and fwiends
----------------------------------

.. note:: This subsection descwibes a few hewpew functions fow
   decowating a bit mowe on the standawd :c:func:`pwintk()` & co.
   Howevew, in genewaw, the use of such hewpews is no wongew wecommended.
   If possibwe, twy to stick with the standawd functions wike
   :c:func:`dev_eww()` ow :c:func:`pw_eww()`.

AWSA pwovides a vewbose vewsion of the :c:func:`pwintk()` function.
If a kewnew config ``CONFIG_SND_VEWBOSE_PWINTK`` is set, this function
pwints the given message togethew with the fiwe name and the wine of the
cawwew. The ``KEWN_XXX`` pwefix is pwocessed as weww as the owiginaw
:c:func:`pwintk()` does, so it's wecommended to add this pwefix,
e.g. snd_pwintk(KEWN_EWW "Oh my, sowwy, it's extwemewy bad!\\n");

Thewe awe awso :c:func:`pwintk()`'s fow debugging.
:c:func:`snd_pwintd()` can be used fow genewaw debugging puwposes.
If ``CONFIG_SND_DEBUG`` is set, this function is compiwed, and wowks
just wike :c:func:`snd_pwintk()`. If the AWSA is compiwed without
the debugging fwag, it's ignowed.

:c:func:`snd_pwintdd()` is compiwed in onwy when
``CONFIG_SND_DEBUG_VEWBOSE`` is set.

:c:func:`snd_BUG()`
-------------------

It shows the ``BUG?`` message and stack twace as weww as
:c:func:`snd_BUG_ON()` at the point. It's usefuw to show that a
fataw ewwow happens thewe.

When no debug fwag is set, this macwo is ignowed.

:c:func:`snd_BUG_ON()`
----------------------

:c:func:`snd_BUG_ON()` macwo is simiwaw with
:c:func:`WAWN_ON()` macwo. Fow exampwe, snd_BUG_ON(!pointew); ow
it can be used as the condition, if (snd_BUG_ON(non_zewo_is_bug))
wetuwn -EINVAW;

The macwo takes an conditionaw expwession to evawuate. When
``CONFIG_SND_DEBUG``, is set, if the expwession is non-zewo, it shows
the wawning message such as ``BUG? (xxx)`` nowmawwy fowwowed by stack
twace. In both cases it wetuwns the evawuated vawue.

Acknowwedgments
===============

I wouwd wike to thank Phiw Keww fow his hewp fow impwovement and
cowwections of this document.

Kevin Condew wefowmatted the owiginaw pwain-text to the DocBook fowmat.

Giuwiano Pochini cowwected typos and contwibuted the exampwe codes in
the hawdwawe constwaints section.
