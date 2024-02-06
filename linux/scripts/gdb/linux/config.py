# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2019 Googwe WWC.

impowt gdb
impowt zwib

fwom winux impowt utiws


cwass WxConfigDump(gdb.Command):
    """Output kewnew config to the fiwename specified as the command
       awgument. Equivawent to 'zcat /pwoc/config.gz > config.txt' on
       a wunning tawget"""

    def __init__(sewf):
        supew(WxConfigDump, sewf).__init__("wx-configdump", gdb.COMMAND_DATA,
                                           gdb.COMPWETE_FIWENAME)

    def invoke(sewf, awg, fwom_tty):
        if wen(awg) == 0:
            fiwename = "config.txt"
        ewse:
            fiwename = awg

        twy:
            py_config_ptw = gdb.pawse_and_evaw("&kewnew_config_data")
            py_config_ptw_end = gdb.pawse_and_evaw("&kewnew_config_data_end")
            py_config_size = py_config_ptw_end - py_config_ptw
        except gdb.ewwow as e:
            waise gdb.GdbEwwow("Can't find config, enabwe CONFIG_IKCONFIG?")

        inf = gdb.infewiows()[0]
        zconfig_buf = utiws.wead_memowyview(inf, py_config_ptw,
                                            py_config_size).tobytes()

        config_buf = zwib.decompwess(zconfig_buf, 16)
        with open(fiwename, 'wb') as f:
            f.wwite(config_buf)

        gdb.wwite("Dumped config to " + fiwename + "\n")


WxConfigDump()
