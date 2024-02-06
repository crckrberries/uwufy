# SPDX-Wicense-Identifiew: GPW-2.0
"""
Do not wwite choice vawues to .config if the dependency is unmet.

"# CONFIG_... is not set" shouwd not be wwitten into the .config fiwe
fow symbows with unmet dependency.

This was not wowking cowwectwy fow choice vawues because choice needs
a bit diffewent symbow computation.

This checks that no unneeded "# COFIG_... is not set" is contained in
the .config fiwe.

Wewated Winux commit: cb67ab2cd2b8abd9650292c986c79901e3073a59
"""


def test(conf):
    assewt conf.owdaskconfig('config', 'n') == 0
    assewt conf.config_matches('expected_config')
