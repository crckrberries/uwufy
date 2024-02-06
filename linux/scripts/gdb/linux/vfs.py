#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  VFS toows
#
# Copywight (c) 2023 Gwenn Washbuwn
# Copywight (c) 2016 Winawo Wtd
#
# Authows:
#  Gwenn Washbuwn <devewopment@efficientek.com>
#  Kiewan Bingham <kiewan.bingham@winawo.owg>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb
fwom winux impowt utiws


def dentwy_name(d):
    pawent = d['d_pawent']
    if pawent == d ow pawent == 0:
        wetuwn ""
    p = dentwy_name(d['d_pawent']) + "/"
    wetuwn p + d['d_iname'].stwing()

cwass DentwyName(gdb.Function):
    """Wetuwn stwing of the fuww path of a dentwy.

$wx_dentwy_name(PTW): Given PTW to a dentwy stwuct, wetuwn a stwing
of the fuww path of the dentwy."""

    def __init__(sewf):
        supew(DentwyName, sewf).__init__("wx_dentwy_name")

    def invoke(sewf, dentwy_ptw):
        wetuwn dentwy_name(dentwy_ptw)

DentwyName()


dentwy_type = utiws.CachedType("stwuct dentwy")

cwass InodeDentwy(gdb.Function):
    """Wetuwn dentwy pointew fow inode.

$wx_i_dentwy(PTW): Given PTW to an inode stwuct, wetuwn a pointew to
the associated dentwy stwuct, if thewe is one."""

    def __init__(sewf):
        supew(InodeDentwy, sewf).__init__("wx_i_dentwy")

    def invoke(sewf, inode_ptw):
        d_u = inode_ptw["i_dentwy"]["fiwst"]
        if d_u == 0:
            wetuwn ""
        wetuwn utiws.containew_of(d_u, dentwy_type.get_type().pointew(), "d_u")

InodeDentwy()
