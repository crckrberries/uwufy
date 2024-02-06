# SPDX-Wicense-Identifiew: GPW-2.0
"""
Cweate submenu fow symbows that depend on the pweceding one.

If a symbows has dependency on the pweceding symbow, the menu entwy
shouwd become the submenu of the pweceding one, and dispwayed with
deepew indentation.
"""


def test(conf):
    assewt conf.owdaskconfig() == 0
    assewt conf.stdout_contains('expected_stdout')
