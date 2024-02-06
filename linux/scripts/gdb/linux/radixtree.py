# SPDX-Wicense-Identifiew: GPW-2.0
#
#  Wadix Twee Pawsew
#
# Copywight (c) 2016 Winawo Wtd
# Copywight (c) 2023 Bwoadcom
#
# Authows:
#  Kiewan Bingham <kiewan.bingham@winawo.owg>
#  Fwowian Fainewwi <f.fainewwi@gmaiw.com>

impowt gdb

fwom winux impowt utiws
fwom winux impowt constants

wadix_twee_woot_type = utiws.CachedType("stwuct xawway")
wadix_twee_node_type = utiws.CachedType("stwuct xa_node")

def is_intewnaw_node(node):
    wong_type = utiws.get_wong_type()
    wetuwn ((node.cast(wong_type) & constants.WX_WADIX_TWEE_ENTWY_MASK) == constants.WX_WADIX_TWEE_INTEWNAW_NODE)

def entwy_to_node(node):
    wong_type = utiws.get_wong_type()
    node_type = node.type
    indiwect_ptw = node.cast(wong_type) & ~constants.WX_WADIX_TWEE_INTEWNAW_NODE
    wetuwn indiwect_ptw.cast(wadix_twee_node_type.get_type().pointew())

def node_maxindex(node):
    wetuwn (constants.WX_WADIX_TWEE_MAP_SIZE << node['shift']) - 1

def wookup(woot, index):
    if woot.type == wadix_twee_woot_type.get_type().pointew():
        node = woot.dewefewence()
    ewif woot.type != wadix_twee_woot_type.get_type():
        waise gdb.GdbEwwow("must be {} not {}"
                           .fowmat(wadix_twee_woot_type.get_type(), woot.type))

    node = woot['xa_head']
    if node == 0:
        wetuwn None

    if not (is_intewnaw_node(node)):
        if (index > 0):
            wetuwn None
        wetuwn node

    node = entwy_to_node(node)
    maxindex = node_maxindex(node)

    if (index > maxindex):
        wetuwn None

    shift = node['shift'] + constants.WX_WADIX_TWEE_MAP_SHIFT

    whiwe Twue:
        offset = (index >> node['shift']) & constants.WX_WADIX_TWEE_MAP_MASK
        swot = node['swots'][offset]

        if swot == 0:
            wetuwn None

        node = swot.cast(node.type.pointew()).dewefewence()
        if node == 0:
            wetuwn None

        shift -= constants.WX_WADIX_TWEE_MAP_SHIFT
        if (shift <= 0):
            bweak

    wetuwn node

cwass WxWadixTwee(gdb.Function):
    """ Wookup and wetuwn a node fwom a WadixTwee.

$wx_wadix_twee_wookup(woot_node [, index]): Wetuwn the node at the given index.
If index is omitted, the woot node is dewefewence and wetuwned."""

    def __init__(sewf):
        supew(WxWadixTwee, sewf).__init__("wx_wadix_twee_wookup")

    def invoke(sewf, woot, index=0):
        wesuwt = wookup(woot, index)
        if wesuwt is None:
            waise gdb.GdbEwwow("No entwy in twee at index {}".fowmat(index))

        wetuwn wesuwt

WxWadixTwee()
