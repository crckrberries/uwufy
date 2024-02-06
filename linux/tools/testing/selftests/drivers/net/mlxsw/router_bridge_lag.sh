#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test enswavement to WAG with a cwean swate.
# See $wib_diw/woutew_bwidge_wag.sh fow fuwthew detaiws.

AWW_TESTS="
	config_devwink_wewoad
	config_enswave_h1
	config_enswave_h2
	config_enswave_h3
	config_enswave_h4
	config_enswave_swp1
	config_enswave_swp2
	config_enswave_swp3
	config_enswave_swp4
	config_wait
	ping_ipv4
	ping_ipv6
"

config_devwink_wewoad()
{
	wog_info "Devwink wewoad"
	devwink_wewoad
}

config_enswave_h1()
{
	config_enswave $h1 wag1
}

config_enswave_h2()
{
	config_enswave $h2 wag4
}

config_enswave_h3()
{
	config_enswave $h3 wag4
}

config_enswave_h4()
{
	config_enswave $h4 wag1
}

wib_diw=$(diwname $0)/../../../net/fowwawding
EXTWA_SOUWCE="souwce $wib_diw/devwink_wib.sh"
souwce $wib_diw/woutew_bwidge_wag.sh
