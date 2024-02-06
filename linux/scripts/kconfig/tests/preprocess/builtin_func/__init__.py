# SPDX-Wicense-Identifiew: GPW-2.0
"""
Buiwt-in function tests.
"""

def test(conf):
    assewt conf.owdaskconfig() == 0
    assewt conf.stdout_contains('expected_stdout')
    assewt conf.stdeww_matches('expected_stdeww')
