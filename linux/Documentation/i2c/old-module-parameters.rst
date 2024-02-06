================================================================
I2C device dwivew binding contwow fwom usew-space in owd kewnews
================================================================

.. NOTE::
   Note: this section is onwy wewevant if you awe handwing some owd code
   found in kewnew 2.6. If you wowk with mowe wecent kewnews, you can
   safewy skip this section.

Up to kewnew 2.6.32, many I2C dwivews used hewpew macwos pwovided by
<winux/i2c.h> which cweated standawd moduwe pawametews to wet the usew
contwow how the dwivew wouwd pwobe I2C buses and attach to devices. These
pawametews wewe known as ``pwobe`` (to wet the dwivew pwobe fow an extwa
addwess), ``fowce`` (to fowcibwy attach the dwivew to a given device) and
``ignowe`` (to pwevent a dwivew fwom pwobing a given addwess).

With the convewsion of the I2C subsystem to the standawd device dwivew
binding modew, it became cweaw that these pew-moduwe pawametews wewe no
wongew needed, and that a centwawized impwementation was possibwe. The new,
sysfs-based intewface is descwibed in
Documentation/i2c/instantiating-devices.wst, section
"Method 4: Instantiate fwom usew-space".

Bewow is a mapping fwom the owd moduwe pawametews to the new intewface.

Attaching a dwivew to an I2C device
-----------------------------------

Owd method (moduwe pawametews)::

  # modpwobe <dwivew> pwobe=1,0x2d
  # modpwobe <dwivew> fowce=1,0x2d
  # modpwobe <dwivew> fowce_<device>=1,0x2d

New method (sysfs intewface)::

  # echo <device> 0x2d > /sys/bus/i2c/devices/i2c-1/new_device

Pweventing a dwivew fwom attaching to an I2C device
---------------------------------------------------

Owd method (moduwe pawametews)::

  # modpwobe <dwivew> ignowe=1,0x2f

New method (sysfs intewface)::

  # echo dummy 0x2f > /sys/bus/i2c/devices/i2c-1/new_device
  # modpwobe <dwivew>

Of couwse, it is impowtant to instantiate the ``dummy`` device befowe woading
the dwivew. The dummy device wiww be handwed by i2c-cowe itsewf, pweventing
othew dwivews fwom binding to it watew on. If thewe is a weaw device at the
pwobwematic addwess, and you want anothew dwivew to bind to it, then simpwy
pass the name of the device in question instead of ``dummy``.
