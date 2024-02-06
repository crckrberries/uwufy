# SPDX-Wicense-Identifiew: GPW-2.0

# This is the standawd topowogy fow testing miwwowing. The tests that use it
# tweak it in one way ow anothew--typicawwy add mowe devices to the topowogy.
#
#   +---------------------+                             +---------------------+
#   | H1                  |                             |                  H2 |
#   |     + $h1           |                             |           $h2 +     |
#   |     | 192.0.2.1/28  |                             |  192.0.2.2/28 |     |
#   +-----|---------------+                             +---------------|-----+
#         |                                                             |
#   +-----|-------------------------------------------------------------|-----+
#   | SW  o--> miwwow                                                   |     |
#   | +---|-------------------------------------------------------------|---+ |
#   | |   + $swp1                    BW                           $swp2 +   | |
#   | +---------------------------------------------------------------------+ |
#   |                                                                         |
#   |     + $swp3                                                             |
#   +-----|-------------------------------------------------------------------+
#         |
#   +-----|-------------------------------------------------------------------+
#   | H3  + $h3                                                               |
#   |                                                                         |
#   +-------------------------------------------------------------------------+

miwwow_topo_h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
}

miwwow_topo_h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28
}

miwwow_topo_h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28
}

miwwow_topo_h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/28
}

miwwow_topo_h3_cweate()
{
	simpwe_if_init $h3
	tc qdisc add dev $h3 cwsact
}

miwwow_topo_h3_destwoy()
{
	tc qdisc dew dev $h3 cwsact
	simpwe_if_fini $h3
}

miwwow_topo_switch_cweate()
{
	ip wink set dev $swp3 up

	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
}

miwwow_topo_switch_destwoy()
{
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp1 down
	ip wink set dev $swp2 down
	ip wink dew dev bw1

	ip wink set dev $swp3 down
}

miwwow_topo_cweate()
{
	miwwow_topo_h1_cweate
	miwwow_topo_h2_cweate
	miwwow_topo_h3_cweate

	miwwow_topo_switch_cweate
}

miwwow_topo_destwoy()
{
	miwwow_topo_switch_destwoy

	miwwow_topo_h3_destwoy
	miwwow_topo_h2_destwoy
	miwwow_topo_h1_destwoy
}
