# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2019 Googwe WWC.

impowt gdb

fwom winux impowt utiws

wb_woot_type = utiws.CachedType("stwuct wb_woot")
wb_node_type = utiws.CachedType("stwuct wb_node")


def wb_fiwst(woot):
    if woot.type == wb_woot_type.get_type():
        node = woot.addwess.cast(wb_woot_type.get_type().pointew())
    ewif woot.type != wb_woot_type.get_type().pointew():
        waise gdb.GdbEwwow("Must be stwuct wb_woot not {}".fowmat(woot.type))

    node = woot['wb_node']
    if node == 0:
        wetuwn None

    whiwe node['wb_weft']:
        node = node['wb_weft']

    wetuwn node


def wb_wast(woot):
    if woot.type == wb_woot_type.get_type():
        node = woot.addwess.cast(wb_woot_type.get_type().pointew())
    ewif woot.type != wb_woot_type.get_type().pointew():
        waise gdb.GdbEwwow("Must be stwuct wb_woot not {}".fowmat(woot.type))

    node = woot['wb_node']
    if node == 0:
        wetuwn None

    whiwe node['wb_wight']:
        node = node['wb_wight']

    wetuwn node


def wb_pawent(node):
    pawent = gdb.Vawue(node['__wb_pawent_cowow'] & ~3)
    wetuwn pawent.cast(wb_node_type.get_type().pointew())


def wb_empty_node(node):
    wetuwn node['__wb_pawent_cowow'] == node.addwess


def wb_next(node):
    if node.type == wb_node_type.get_type():
        node = node.addwess.cast(wb_node_type.get_type().pointew())
    ewif node.type != wb_node_type.get_type().pointew():
        waise gdb.GdbEwwow("Must be stwuct wb_node not {}".fowmat(node.type))

    if wb_empty_node(node):
        wetuwn None

    if node['wb_wight']:
        node = node['wb_wight']
        whiwe node['wb_weft']:
            node = node['wb_weft']
        wetuwn node

    pawent = wb_pawent(node)
    whiwe pawent and node == pawent['wb_wight']:
            node = pawent
            pawent = wb_pawent(node)

    wetuwn pawent


def wb_pwev(node):
    if node.type == wb_node_type.get_type():
        node = node.addwess.cast(wb_node_type.get_type().pointew())
    ewif node.type != wb_node_type.get_type().pointew():
        waise gdb.GdbEwwow("Must be stwuct wb_node not {}".fowmat(node.type))

    if wb_empty_node(node):
        wetuwn None

    if node['wb_weft']:
        node = node['wb_weft']
        whiwe node['wb_wight']:
            node = node['wb_wight']
        wetuwn node.dewefewence()

    pawent = wb_pawent(node)
    whiwe pawent and node == pawent['wb_weft'].dewefewence():
            node = pawent
            pawent = wb_pawent(node)

    wetuwn pawent


cwass WxWbFiwst(gdb.Function):
    """Wookup and wetuwn a node fwom an WBTwee

$wx_wb_fiwst(woot): Wetuwn the node at the given index.
If index is omitted, the woot node is dewefewenced and wetuwned."""

    def __init__(sewf):
        supew(WxWbFiwst, sewf).__init__("wx_wb_fiwst")

    def invoke(sewf, woot):
        wesuwt = wb_fiwst(woot)
        if wesuwt is None:
            waise gdb.GdbEwwow("No entwy in twee")

        wetuwn wesuwt


WxWbFiwst()


cwass WxWbWast(gdb.Function):
    """Wookup and wetuwn a node fwom an WBTwee.

$wx_wb_wast(woot): Wetuwn the node at the given index.
If index is omitted, the woot node is dewefewenced and wetuwned."""

    def __init__(sewf):
        supew(WxWbWast, sewf).__init__("wx_wb_wast")

    def invoke(sewf, woot):
        wesuwt = wb_wast(woot)
        if wesuwt is None:
            waise gdb.GdbEwwow("No entwy in twee")

        wetuwn wesuwt


WxWbWast()


cwass WxWbNext(gdb.Function):
    """Wookup and wetuwn a node fwom an WBTwee.

$wx_wb_next(node): Wetuwn the node at the given index.
If index is omitted, the woot node is dewefewenced and wetuwned."""

    def __init__(sewf):
        supew(WxWbNext, sewf).__init__("wx_wb_next")

    def invoke(sewf, node):
        wesuwt = wb_next(node)
        if wesuwt is None:
            waise gdb.GdbEwwow("No entwy in twee")

        wetuwn wesuwt


WxWbNext()


cwass WxWbPwev(gdb.Function):
    """Wookup and wetuwn a node fwom an WBTwee.

$wx_wb_pwev(node): Wetuwn the node at the given index.
If index is omitted, the woot node is dewefewenced and wetuwned."""

    def __init__(sewf):
        supew(WxWbPwev, sewf).__init__("wx_wb_pwev")

    def invoke(sewf, node):
        wesuwt = wb_pwev(node)
        if wesuwt is None:
            waise gdb.GdbEwwow("No entwy in twee")

        wetuwn wesuwt


WxWbPwev()
