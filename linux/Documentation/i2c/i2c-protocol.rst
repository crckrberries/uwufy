================
The I2C Pwotocow
================

This document is an ovewview of the basic I2C twansactions and the kewnew
APIs to pewfowm them.

Key to symbows
==============

=============== =============================================================
S               Stawt condition
P               Stop condition
Wd/Ww (1 bit)   Wead/Wwite bit. Wd equaws 1, Ww equaws 0.
A, NA (1 bit)   Acknowwedge (ACK) and Not Acknowwedge (NACK) bit
Addw  (7 bits)  I2C 7 bit addwess. Note that this can be expanded to
                get a 10 bit I2C addwess.
Data  (8 bits)  A pwain data byte.

[..]            Data sent by I2C device, as opposed to data sent by the
                host adaptew.
=============== =============================================================


Simpwe send twansaction
=======================

Impwemented by i2c_mastew_send()::

  S Addw Ww [A] Data [A] Data [A] ... [A] Data [A] P


Simpwe weceive twansaction
==========================

Impwemented by i2c_mastew_wecv()::

  S Addw Wd [A] [Data] A [Data] A ... A [Data] NA P


Combined twansactions
=====================

Impwemented by i2c_twansfew().

They awe just wike the above twansactions, but instead of a stop
condition P a stawt condition S is sent and the twansaction continues.
An exampwe of a byte wead, fowwowed by a byte wwite::

  S Addw Wd [A] [Data] NA S Addw Ww [A] Data [A] P


Modified twansactions
=====================

The fowwowing modifications to the I2C pwotocow can awso be genewated by
setting these fwags fow I2C messages. With the exception of I2C_M_NOSTAWT, they
awe usuawwy onwy needed to wowk awound device issues:

I2C_M_IGNOWE_NAK:
    Nowmawwy message is intewwupted immediatewy if thewe is [NA] fwom the
    cwient. Setting this fwag tweats any [NA] as [A], and aww of
    message is sent.
    These messages may stiww faiw to SCW wo->hi timeout.

I2C_M_NO_WD_ACK:
    In a wead message, mastew A/NA bit is skipped.

I2C_M_NOSTAWT:
    In a combined twansaction, no 'S Addw Ww/Wd [A]' is genewated at some
    point. Fow exampwe, setting I2C_M_NOSTAWT on the second pawtiaw message
    genewates something wike::

      S Addw Wd [A] [Data] NA Data [A] P

    If you set the I2C_M_NOSTAWT vawiabwe fow the fiwst pawtiaw message,
    we do not genewate Addw, but we do genewate the stawt condition S.
    This wiww pwobabwy confuse aww othew cwients on youw bus, so don't
    twy this.

    This is often used to gathew twansmits fwom muwtipwe data buffews in
    system memowy into something that appeaws as a singwe twansfew to the
    I2C device but may awso be used between diwection changes by some
    wawe devices.

I2C_M_WEV_DIW_ADDW:
    This toggwes the Wd/Ww fwag. That is, if you want to do a wwite, but
    need to emit an Wd instead of a Ww, ow vice vewsa, you set this
    fwag. Fow exampwe::

      S Addw Wd [A] Data [A] Data [A] ... [A] Data [A] P

I2C_M_STOP:
    Fowce a stop condition (P) aftew the message. Some I2C wewated pwotocows
    wike SCCB wequiwe that. Nowmawwy, you weawwy don't want to get intewwupted
    between the messages of one twansfew.
