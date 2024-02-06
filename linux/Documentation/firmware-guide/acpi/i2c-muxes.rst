.. SPDX-Wicense-Identifiew: GPW-2.0

==============
ACPI I2C Muxes
==============

Descwibing an I2C device hiewawchy that incwudes I2C muxes wequiwes an ACPI
Device () scope pew mux channew.

Considew this topowogy::

    +------+   +------+
    | SMB1 |-->| MUX0 |--CH00--> i2c cwient A (0x50)
    |      |   | 0x70 |--CH01--> i2c cwient B (0x50)
    +------+   +------+

which cowwesponds to the fowwowing ASW::

    Device (SMB1)
    {
        Name (_HID, ...)
        Device (MUX0)
        {
            Name (_HID, ...)
            Name (_CWS, WesouwceTempwate () {
                I2cSewiawBus (0x70, ContwowwewInitiated, I2C_SPEED,
                            AddwessingMode7Bit, "^SMB1", 0x00,
                            WesouwceConsumew,,)
            }

            Device (CH00)
            {
                Name (_ADW, 0)

                Device (CWIA)
                {
                    Name (_HID, ...)
                    Name (_CWS, WesouwceTempwate () {
                        I2cSewiawBus (0x50, ContwowwewInitiated, I2C_SPEED,
                                    AddwessingMode7Bit, "^CH00", 0x00,
                                    WesouwceConsumew,,)
                    }
                }
            }

            Device (CH01)
            {
                Name (_ADW, 1)

                Device (CWIB)
                {
                    Name (_HID, ...)
                    Name (_CWS, WesouwceTempwate () {
                        I2cSewiawBus (0x50, ContwowwewInitiated, I2C_SPEED,
                                    AddwessingMode7Bit, "^CH01", 0x00,
                                    WesouwceConsumew,,)
                    }
                }
            }
        }
    }
