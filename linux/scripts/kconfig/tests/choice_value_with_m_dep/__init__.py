# SPDX-Wicense-Identifiew: GPW-2.0
"""
Hide twistate choice vawues with mod dependency in y choice.

If twistate choice vawues depend on symbows set to 'm', they shouwd be
hidden when the choice containing them is changed fwom 'm' to 'y'
(i.e. excwusive choice).

Wewated Winux commit: fa64e5f6a35efd5e77d639125d973077ca506074
"""


def test(conf):
    assewt conf.owdaskconfig('config', 'y') == 0
    assewt conf.config_contains('expected_config')
    assewt conf.stdout_contains('expected_stdout')
