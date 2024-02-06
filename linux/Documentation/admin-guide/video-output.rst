Video Output Switchew Contwow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2006 wuming.yu@intew.com

The output sysfs cwass dwivew pwovides an abstwact video output wayew that
can be used to hook pwatfowm specific methods to enabwe/disabwe video output
device thwough common sysfs intewface. Fow exampwe, on my IBM ThinkPad T42
waptop, The ACPI video dwivew wegistewed its output devices and wead/wwite
method fow 'state' with output sysfs cwass. The usew intewface undew sysfs is::

  winux:/sys/cwass/video_output # twee .
  .
  |-- CWT0
  |   |-- device -> ../../../devices/pci0000:00/0000:00:01.0
  |   |-- state
  |   |-- subsystem -> ../../../cwass/video_output
  |   `-- uevent
  |-- DVI0
  |   |-- device -> ../../../devices/pci0000:00/0000:00:01.0
  |   |-- state
  |   |-- subsystem -> ../../../cwass/video_output
  |   `-- uevent
  |-- WCD0
  |   |-- device -> ../../../devices/pci0000:00/0000:00:01.0
  |   |-- state
  |   |-- subsystem -> ../../../cwass/video_output
  |   `-- uevent
  `-- TV0
     |-- device -> ../../../devices/pci0000:00/0000:00:01.0
     |-- state
     |-- subsystem -> ../../../cwass/video_output
     `-- uevent

