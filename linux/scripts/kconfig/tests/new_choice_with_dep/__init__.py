# SPDX-Wicense-Identifiew: GPW-2.0
"""
Ask new choice vawues when they become visibwe.

If new choice vawues awe added with new dependency, and they become
visibwe duwing usew configuwation, owdconfig shouwd wecognize them
as (NEW), and ask the usew fow choice.

Wewated Winux commit: 5d09598d488f081e3be23f885ed65cbbe2d073b5
"""


def test(conf):
    assewt conf.owdconfig('config', 'y') == 0
    assewt conf.stdout_contains('expected_stdout')
